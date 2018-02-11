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
#include <sys/mman.h>
#include "ai.h"
#include "gpio.h"
#include "pwm.h"


//t_all_input m_t_all_input;
uint32 g_all_AIs[MAX_AI_NUM];

uchar* g_ai_vir_addr=NULL;
uint32 g_ai_mem_fd = 0;


/* Configures the step */
void StepConfigure(unsigned int stepSel, unsigned int fifo,
                   unsigned int positiveInpChannel)
{
    /* Configure ADC to Single ended operation mode */
    TSCADCTSStepOperationModeControl(SOC_ADC_TSC_0_REGS,
                                  TSCADC_SINGLE_ENDED_OPER_MODE, stepSel);

    /* Configure step to select Channel, refernce voltages */
    TSCADCTSStepConfig(SOC_ADC_TSC_0_REGS, stepSel, TSCADC_NEGATIVE_REF_VSSA,
                    positiveInpChannel, TSCADC_NEGATIVE_INP_CHANNEL1, TSCADC_POSITIVE_REF_VDDA);

    /* XPPSW Pin is on, Which pull up the AN0 line*/
    TSCADCTSStepAnalogSupplyConfig(SOC_ADC_TSC_0_REGS, TSCADC_XPPSW_PIN_ON, TSCADC_XNPSW_PIN_OFF,
                                TSCADC_YPPSW_PIN_OFF, stepSel);

    /* XNNSW Pin is on, Which pull down the AN1 line*/
    TSCADCTSStepAnalogGroundConfig(SOC_ADC_TSC_0_REGS, TSCADC_XNNSW_PIN_ON, TSCADC_YPNSW_PIN_OFF,
                                TSCADC_YNNSW_PIN_OFF,  TSCADC_WPNSW_PIN_OFF, stepSel);

    /* select fifo 0 or 1*/
    TSCADCTSStepFIFOSelConfig(SOC_ADC_TSC_0_REGS, stepSel, fifo);

    /* Configure ADC to one short mode */
    TSCADCTSStepModeConfig(SOC_ADC_TSC_0_REGS, stepSel,  TSCADC_ONE_SHOT_SOFTWARE_ENABLED);
}
/* ADC is configured */
static void ADCConfigure(void)
{
    /* Enable the clock for touch screen */
    TSCADCModuleClkConfig();

    TSCADCPinMuxSetUp();

    /* Configures ADC to 3Mhz */
    TSCADCConfigureAFEClock(SOC_ADC_TSC_0_REGS, 24000000, 3000000);

    /* Enable Transistor bias */
    TSCADCTSTransistorConfig(SOC_ADC_TSC_0_REGS, TSCADC_TRANSISTOR_ENABLE);

    TSCADCStepIDTagConfig(SOC_ADC_TSC_0_REGS, 1);

    /* Disable Write Protection of Step Configuration regs*/
    TSCADCStepConfigProtectionDisable(SOC_ADC_TSC_0_REGS);

    /* Configure step 1 for channel 1(AN0)*/
    StepConfigure(0, TSCADC_FIFO_0, TSCADC_POSITIVE_INP_CHANNEL1);

    /* Configure step 2 for channel 2(AN1)*/
    StepConfigure(1, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL2);

    /* General purpose inputs */
    TSCADCTSModeConfig(SOC_ADC_TSC_0_REGS, TSCADC_GENERAL_PURPOSE_MODE);

    /* Enable step 1 */
    TSCADCConfigureStepEnable(SOC_ADC_TSC_0_REGS, 1, 1);

    /* Enable step 2 */
    TSCADCConfigureStepEnable(SOC_ADC_TSC_0_REGS, 2, 1);

    /* Clear the status of all interrupts */
    CleanUpInterrupts();

    /* End of sequence interrupt is enable */
    TSCADCEventInterruptEnable(SOC_ADC_TSC_0_REGS, TSCADC_END_OF_SEQUENCE_INT);

    /* Enable the TSC_ADC_SS module*/
    TSCADCModuleStateSet(SOC_ADC_TSC_0_REGS, TSCADC_MODULE_ENABLE);
}



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

uint32 init_AI()
{
	uint32 i;
	
	printf("Starting ai init.\n");

	if(g_ai_mem_fd == 0) {
		g_ai_mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
	}
	
	if (g_ai_mem_fd > 0) 	{
		printf("Success to open ADC memery /dev/mem fd=0x%08x\n", g_ai_mem_fd);
	} 	else {
		printf("Fail to open /dev/mem fd=0x%08x\n", g_ai_mem_fd);
		return 0xffffffff;
	}
	g_ai_vir_addr = mmap(NULL, AI_ALLOC_SIZE, PROT_READ+PROT_WRITE, MAP_SHARED, g_ai_mem_fd, (uint32)AI_BASE_ADDR);
	printf("The virtual address of ADC is 0x%08x \n", (uint32)g_ai_vir_addr);
	

	if (g_ai_vir_addr == (void*)0xffffffff) 	{
		printf("ADC mmap failed.\n");
		close(g_ai_mem_fd);
		return 0xffffffff;
	}
	
//	TSCADCSetADCPowerDown(g_ai_vir_addr); //just for test
	return 0;
}

uint32 read_AI(uint32 AI_no)
{
	uint32 val=0;
	if(AI_no < 6) {
		return read_ai_raw(AI_no);	
	}else if(AI_no ==6){
		val = (RD_WR_REG32(g_ai_vir_addr+0x100))&0x0fff; //fifo-0
		if(val < 4096) return val;
		else return 4096;
	}else if(AI_no ==7) {
		val = (RD_WR_REG32(g_ai_vir_addr+0x200))&0x0fff;  //fifo-1
		if(val < 4096) return val;
		else return 4096;
	}else {
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



