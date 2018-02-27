/*
   * ai.c
   *
   *
   * Copyright (c) 2014-2017 Hiden Tech Ltd.
   *		File: ai.c
   *		Date: 2016/11/3
   *	  Author: riguang peng
   * Description: A program to show how to read io from user-space.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <byteswap.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <stdint.h>
#include <errno.h>
#include <sys/io.h>
#include <sys/mman.h>
#include "ai.h"
#include "gpio.h"
#include "pwm.h"


//t_all_input m_t_all_input;
uint32 g_all_AIs[MAX_AI_NUM];

uint32 g_ai_vir_addr=(uint32)NULL;
uint32 g_ai_mem_fd = 0;
uint32 SOC_CONTROL_REGS=(uint32)NULL;

/* Clear status of all interrupts */
static void CleanUpInterrupts(void)
{
    TSCADCIntStatusClear(g_ai_vir_addr, 0x7FF);
    TSCADCIntStatusClear(g_ai_vir_addr ,0x7FF);
    TSCADCIntStatusClear(g_ai_vir_addr, 0x7FF);
}

/* Configures the step */
void StepConfigure(uint32 base_addr, unsigned int stepSel, unsigned int fifo,
                   unsigned int positiveInpChannel)
{
    /* Configure ADC to Single ended operation mode */
    TSCADCTSStepOperationModeControl(base_addr,
                                  TSCADC_SINGLE_ENDED_OPER_MODE, stepSel);

    /* Configure step to select Channel, refernce voltages */
    TSCADCTSStepConfig(base_addr, stepSel, TSCADC_NEGATIVE_REF_VSSA,
                    positiveInpChannel, TSCADC_NEGATIVE_INP_CHANNEL1, TSCADC_POSITIVE_REF_VDDA);

    /* XPPSW Pin is on, Which pull up the AN0 line*/
    TSCADCTSStepAnalogSupplyConfig(base_addr, TSCADC_XPPSW_PIN_ON, TSCADC_XNPSW_PIN_OFF,
                                TSCADC_YPPSW_PIN_OFF, stepSel);

    /* XNNSW Pin is on, Which pull down the AN1 line*/
    TSCADCTSStepAnalogGroundConfig(base_addr, TSCADC_XNNSW_PIN_ON, TSCADC_YPNSW_PIN_OFF,
                                TSCADC_YNNSW_PIN_OFF,  TSCADC_WPNSW_PIN_OFF, stepSel);
     /*TSCADC_EIGHT_SAMPLES_AVG      */
    TSCADCTSStepAverageConfig(base_addr,stepSel,TSCADC_EIGHT_SAMPLES_AVG);

    /* select fifo 0 or 1*/
    TSCADCTSStepFIFOSelConfig(base_addr, stepSel, fifo);

    /* Configure ADC to one shot mode */
    TSCADCTSStepModeConfig(base_addr, stepSel,  TSCADC_ONE_SHOT_SOFTWARE_ENABLED);
}
void EnableSteps(uint32 base_addr)
{
    TSCADCConfigureStepEnable(base_addr, 1, 1);
    TSCADCConfigureStepEnable(base_addr, 2, 1);
    TSCADCConfigureStepEnable(base_addr, 3, 1);
    TSCADCConfigureStepEnable(base_addr, 4, 1);
    TSCADCConfigureStepEnable(base_addr, 5, 1);
    TSCADCConfigureStepEnable(base_addr, 6, 1);
}

/* ADC is configured */
static void ADCConfigure(uint32 base_addr)
{
    TSCADCModuleStateSet(base_addr, TSCADC_MODULE_DISABLE);
    TSCADCPinMuxSetUp();
    /* Configures ADC to 3Mhz */
    TSCADCConfigureAFEClock(base_addr, 24000000, 3000000);
    /* Enable Transistor bias */
    TSCADCTSTransistorConfig(base_addr, TSCADC_TRANSISTOR_ENABLE);
    TSCADCStepIDTagConfig(base_addr, 1);
    /* Disable Write Protection of Step Configuration regs*/
    TSCADCStepConfigProtectionDisable(base_addr);
    /* Configure step 1~6 for channel 1(AN0)~6(AN5)*/
    StepConfigure(base_addr, 0, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL1);
    StepConfigure(base_addr, 1, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL1);
    StepConfigure(base_addr, 2, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL2);
    StepConfigure(base_addr, 3, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL2);
    StepConfigure(base_addr, 4, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL3);
    StepConfigure(base_addr, 5, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL3);
    StepConfigure(base_addr, 6, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL4);
    StepConfigure(base_addr, 7, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL4);
    StepConfigure(base_addr, 8, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL5);
    StepConfigure(base_addr, 9, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL5);
    StepConfigure(base_addr, 10, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL6);
    StepConfigure(base_addr, 11, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL6);

    /* General purpose inputs */
    TSCADCTSModeConfig(base_addr, TSCADC_GENERAL_PURPOSE_MODE);

    /* Enable step 1~6 */
    EnableSteps(base_addr);

    /* Clear the status of all interrupts */
    CleanUpInterrupts();

    /* End of sequence interrupt is enable */
 //   TSCADCEventInterruptEnable(SOC_ADC_TSC_0_REGS, TSCADC_END_OF_SEQUENCE_INT);

    /* Enable the TSC_ADC_SS module*/
    TSCADCModuleStateSet(base_addr, TSCADC_MODULE_ENABLE);

}
/*
uint32 read_ai_raw(uint32 port_num)
{
	char cmd[80];
	char val[8]="";
	sprintf(cmd, "cat /sys/bus/iio/devices/iio:device0/in_voltage%d_raw\n",port_num);
	FILE *fp = popen(cmd, "r");
	fgets(val,8,fp);
	pclose(fp);
	return atoi(val);
}
*/

uint32 read_ai_raw(uint32 port_num)
{	
	static uint32 raw_data[6];
	//printf("starting read ADC data......\n");
	if(port_num==0) {
		//uint32 ret = TSCADCIntStatusRead(g_ai_vir_addr,TSCADC_END_OF_SEQUENCE_INT);
		//printf("get status:%d\n", ret);
		//if(ret > 0) {  //ADC succeed
			for(uint32 i=0; i<6; i++) {
				raw_data[i] = TSCADCFIFOADCDataRead(g_ai_vir_addr,1);
				raw_data[i] += TSCADCFIFOADCDataRead(g_ai_vir_addr,1);
				raw_data[i] /=2;
				
			}
			
		//}
		EnableSteps(g_ai_vir_addr); //single shot mode, restart ADC after every sequence
	}
	
	if(port_num < 6) {
		return raw_data[port_num];
	} else {
		return port_num+2000;
	}

}

uint32 init_AI(uint32 mem_fd)
{
	uint32 i;
	
	printf("Starting ai init.\n");

	g_ai_mem_fd = mem_fd;

	printf("memsize = %d\n", AI_ALLOC_SIZE);
	g_ai_vir_addr = (uint32)mmap(NULL, AI_ALLOC_SIZE, PROT_READ+PROT_WRITE, MAP_SHARED, g_ai_mem_fd, (uint32)AI_BASE_ADDR);
	printf("The virtual address of ADC is 0x%08x \n", g_ai_vir_addr);

	if (g_ai_vir_addr == 0xffffffff) 	{
		printf("ADC mmap failed.\n");
		close(g_ai_mem_fd);
		return 0xffffffff;
	}
	SOC_CONTROL_REGS = g_ai_vir_addr;
	
	ADCConfigure(g_ai_vir_addr);
	return 0;
}

uint32 read_AI(uint32 AI_no)
{
	uint32 val=0;
	if(AI_no < 6) {
		return read_ai_raw(AI_no);	
/*	}else if(AI_no ==6){
		val = (RD_WR_REG32(g_ai_vir_addr+0x100))&0x0fff; //fifo-0
		if(val < 4096) return val;
		else return 4096;
	}else if(AI_no ==7) {
		val = (RD_WR_REG32(g_ai_vir_addr+0x200))&0x0fff;  //fifo-1
		if(val < 4096) return val;
		else return 4096;
*/	}else {
		return AI_no + 2000;
	}
}


void read_all_AIs()
{
	uint32 i;
	uint32 val;
	for (i = 0; i < MAX_AI_NUM; i++) {
		val = read_AI(i);
		if(val < 4096) 
			g_all_AIs[i] = val;
	}

}



