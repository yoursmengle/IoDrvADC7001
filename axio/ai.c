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

uint32 g_cur_chan_no = 0;
uint32 set_ai_channel(uint32 chan_no);

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
    TSCADCConfigureStepEnable(base_addr, 7, 1);
    TSCADCConfigureStepEnable(base_addr, 8, 1);
    TSCADCConfigureStepEnable(base_addr, 9, 1);
    TSCADCConfigureStepEnable(base_addr, 10, 1);
    TSCADCConfigureStepEnable(base_addr, 11, 1);
    TSCADCConfigureStepEnable(base_addr, 12, 1);
    TSCADCConfigureStepEnable(base_addr, 13, 1);
    TSCADCConfigureStepEnable(base_addr, 14, 1);
    TSCADCConfigureStepEnable(base_addr, 15, 1);
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

    /* Configure step 1~12 for channel 1(AN0)~6(AN5)*/
    StepConfigure(base_addr, TSC_ADC_SS_ADCSTAT_STEPID_STEP1, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL3);
    StepConfigure(base_addr, TSC_ADC_SS_ADCSTAT_STEPID_STEP2, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL3);
    StepConfigure(base_addr, TSC_ADC_SS_ADCSTAT_STEPID_STEP3, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL3);
    StepConfigure(base_addr, TSC_ADC_SS_ADCSTAT_STEPID_STEP4, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL3);
    StepConfigure(base_addr, TSC_ADC_SS_ADCSTAT_STEPID_STEP5, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL5);
    StepConfigure(base_addr, TSC_ADC_SS_ADCSTAT_STEPID_STEP6, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL5);
    StepConfigure(base_addr, TSC_ADC_SS_ADCSTAT_STEPID_STEP7, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL5);
    StepConfigure(base_addr, TSC_ADC_SS_ADCSTAT_STEPID_STEP8, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL5);
    StepConfigure(base_addr, TSC_ADC_SS_ADCSTAT_STEPID_STEP9, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL6);
    StepConfigure(base_addr, TSC_ADC_SS_ADCSTAT_STEPID_STEP10, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL6);
    StepConfigure(base_addr, TSC_ADC_SS_ADCSTAT_STEPID_STEP11, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL6);
    StepConfigure(base_addr, TSC_ADC_SS_ADCSTAT_STEPID_STEP12, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL6);
    StepConfigure(base_addr, TSC_ADC_SS_ADCSTAT_STEPID_STEP13, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL4);
    StepConfigure(base_addr, TSC_ADC_SS_ADCSTAT_STEPID_STEP14, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL2);
    StepConfigure(base_addr, TSC_ADC_SS_ADCSTAT_STEPID_STEP15, TSCADC_FIFO_1, TSCADC_POSITIVE_INP_CHANNEL1);

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
	set_ai_channel(g_cur_chan_no);
	ADCConfigure(g_ai_vir_addr);
	return 0;
}

uint32 g_raw_data[6];
void read_ai_raw(void)
{	
	g_raw_data[2] = TSCADCFIFOADCDataRead(g_ai_vir_addr,1);//discarded
	g_raw_data[2] = TSCADCFIFOADCDataRead(g_ai_vir_addr,1);//discarded
	g_raw_data[2] = TSCADCFIFOADCDataRead(g_ai_vir_addr,1);
	g_raw_data[2] += TSCADCFIFOADCDataRead(g_ai_vir_addr,1);
	g_raw_data[2] /=2;

	g_raw_data[4] = TSCADCFIFOADCDataRead(g_ai_vir_addr,1);//discarded
	g_raw_data[4] = TSCADCFIFOADCDataRead(g_ai_vir_addr,1);//discarded
	g_raw_data[4] = TSCADCFIFOADCDataRead(g_ai_vir_addr,1);
	g_raw_data[4] += TSCADCFIFOADCDataRead(g_ai_vir_addr,1);
	g_raw_data[4] /=2;

	g_raw_data[5] = TSCADCFIFOADCDataRead(g_ai_vir_addr,1); //discarded
	g_raw_data[5] = TSCADCFIFOADCDataRead(g_ai_vir_addr,1);//discarded
	g_raw_data[5] = TSCADCFIFOADCDataRead(g_ai_vir_addr,1);
	g_raw_data[5] += TSCADCFIFOADCDataRead(g_ai_vir_addr,1);
	g_raw_data[5] /=2;

	g_raw_data[3] = TSCADCFIFOADCDataRead(g_ai_vir_addr,1);
	g_raw_data[1] = TSCADCFIFOADCDataRead(g_ai_vir_addr,1);
	g_raw_data[0] = TSCADCFIFOADCDataRead(g_ai_vir_addr,1);

	EnableSteps(g_ai_vir_addr); //single shot mode, restart ADC after every sequence
}

void read_AI(void)
{
	uint32 val=0;
	switch(g_cur_chan_no) {
	case 0:
		g_all_AIs[4] = g_raw_data[2];
		g_all_AIs[10] = g_raw_data[4];
		g_all_AIs[16] = g_raw_data[5];	
		break;
	case 1:
		g_all_AIs[5] = g_raw_data[2];
		g_all_AIs[11] = g_raw_data[4];
		g_all_AIs[17] = g_raw_data[5];	
		break;	
	case 3:
		g_all_AIs[3] = g_raw_data[2];
		g_all_AIs[9] = g_raw_data[4];
		g_all_AIs[15] = g_raw_data[5];	
		break;	
	case 4:
		g_all_AIs[0] = g_raw_data[2];
		g_all_AIs[6] = g_raw_data[4];
		g_all_AIs[12] = g_raw_data[5];	
		break;
	case 6:
		g_all_AIs[1] = g_raw_data[2];
		g_all_AIs[7] = g_raw_data[4];
		g_all_AIs[13] = g_raw_data[5];	
		break;
	case 7:
		g_all_AIs[2] = g_raw_data[2];
		g_all_AIs[8] = g_raw_data[4];
		g_all_AIs[14] = g_raw_data[5];	
		break;
	default:
		break;		
	}

	g_all_AIs[18] = g_raw_data[3];
	g_all_AIs[19] = g_raw_data[1];
	g_all_AIs[20] = g_raw_data[0];
}

void read_all_AIs()
{
	uint32 i;
	uint32 val;

	read_ai_raw();
	read_AI();

	g_cur_chan_no++;  //switch channel of ADC
	if(g_cur_chan_no> 7) {
		g_cur_chan_no = 0;
	}
	set_ai_channel(g_cur_chan_no);
}



