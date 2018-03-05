/*
   * pwm.c
   *
   *
   * Copyright (c) 2014-2017 Hiden Tech Ltd.
   *		File: pwm.c
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
#include "pwm.h"
#include "hw_types.h"
#include "ti-pwm.h"
#include "soc_AM335x.h"

static void EHRPWMConfigure(void);
uint32 g_all_PWMs[MAX_PWM_NUM];
uchar* g_pwm_base_addr=NULL;
int g_pwm_mem_fd = 0; 
uint32 PWM_OFFSET[MAX_PWM_NUM] = {
	0x10*4,
	0x11*4,
	0x12*4,
	0x13*4,
	0x14*4,
	0x15*4,
	0x16*4
};

uint32 init_PWM(uint32 mem_fd)
{
	uint32 i;
	
	printf("Starting pwm init.\n");

    PWMSSModuleClkConfig(2);

    EPWM2PinMuxSetup();

    /* Enable Clock for EHRPWM in PWM sub system */
    EHRPWMClockEnable(SOC_PWMSS2_REGS);

    /* Enable Timer Base Module Clock in control module */
    PWMSSTBClkEnable(2);

    /* EHRPWM is configured to generate PWM waveform on EPWMBxB Pin*/
    EHRPWMConfigure();

    return 0;
}

void write_pwm(uint32 PWM_no, uint32 value)
{
	return;
}

void write_all_PWMs(void)
{
	uint32 i,val;
	for(i=0; i<MAX_PWM_NUM; i++) {
		val = g_all_PWMs[i]*4096/10000;
		if(val > 4096) val = 4096;
		write_pwm(i,val);
	}
	return;
}

#define CLOCK_DIV_VAL                 (10)
#define SOC_EHRPWM_2_MODULE_FREQ      (100000000)

static void EHRPWMConfigure(void)
{
  
    /* TimeBase configuration */
    /* Configure the clock frequency */
    EHRPWMTimebaseClkConfig(SOC_EPWM_2_REGS,
                            SOC_EHRPWM_2_MODULE_FREQ/CLOCK_DIV_VAL,
                            SOC_EHRPWM_2_MODULE_FREQ);

    /* Configure the period of the output waveform */
    EHRPWMPWMOpFreqSet(SOC_EPWM_2_REGS,
                       SOC_EHRPWM_2_MODULE_FREQ/CLOCK_DIV_VAL,
                       (unsigned int)(SOC_EHRPWM_2_MODULE_FREQ/CLOCK_DIV_VAL)/0xFF,
                       (unsigned int)EHRPWM_COUNT_UP,
                       (bool)EHRPWM_SHADOW_WRITE_DISABLE);

    /* Disable synchronization*/
    EHRPWMTimebaseSyncDisable(SOC_EPWM_2_REGS);

    /* Disable syncout*/
    EHRPWMSyncOutModeSet(SOC_EPWM_2_REGS, EHRPWM_SYNCOUT_DISABLE);

    /* Configure the emulation behaviour*/
    EHRPWMTBEmulationModeSet(SOC_EPWM_2_REGS, EHRPWM_STOP_AFTER_NEXT_TB_INCREMENT);

    /* Configure Counter compare cub-module */
    /* Load Compare A value */
    EHRPWMLoadCMPA(SOC_EPWM_2_REGS,
                   50,
                   (bool)EHRPWM_SHADOW_WRITE_DISABLE,
                   (unsigned int)EHRPWM_COMPA_NO_LOAD,
                   (bool)EHRPWM_CMPCTL_OVERWR_SH_FL);

    /* Load Compare B value */
    EHRPWMLoadCMPB(SOC_EPWM_2_REGS,
                   200,
                   (bool)EHRPWM_SHADOW_WRITE_DISABLE,
                   (unsigned int) EHRPWM_COMPB_NO_LOAD,
                   (bool)EHRPWM_CMPCTL_OVERWR_SH_FL);

    /* Configure Action qualifier */
    /* Toggle when CTR = CMPA */
    EHRPWMConfigureAQActionOnB(SOC_EPWM_2_REGS,
                               EHRPWM_AQCTLB_ZRO_DONOTHING,
                               EHRPWM_AQCTLB_PRD_DONOTHING,
                               EHRPWM_AQCTLB_CAU_EPWMXBTOGGLE,
                               EHRPWM_AQCTLB_CAD_DONOTHING,
                               EHRPWM_AQCTLB_CBU_DONOTHING,
                               EHRPWM_AQCTLB_CBD_DONOTHING,
                               EHRPWM_AQSFRC_ACTSFB_DONOTHING);

    /* Bypass dead band sub-module */
    EHRPWMDBOutput(SOC_EPWM_2_REGS, EHRPWM_DBCTL_OUT_MODE_BYPASS);

    /* Disable Chopper sub-module */
    EHRPWMChopperDisable(SOC_EPWM_2_REGS);

    /* Disable trip events */
    EHRPWMTZTripEventDisable(SOC_EPWM_2_REGS,(bool)EHRPWM_TZ_ONESHOT);
    EHRPWMTZTripEventDisable(SOC_EPWM_2_REGS,(bool)EHRPWM_TZ_CYCLEBYCYCLE);

    /* Event trigger */
    /* Generate interrupt every 3rd occurance of the event */
    EHRPWMETIntPrescale(SOC_EPWM_2_REGS, EHRPWM_ETPS_INTPRD_THIRDEVENT);
    /* Generate event when CTR = CMPB */
    EHRPWMETIntSourceSelect(SOC_EPWM_2_REGS, EHRPWM_ETSEL_INTSEL_TBCTREQUCMPBINC);

    /* Disable High resolution capability */
    EHRPWMHRDisable(SOC_EPWM_2_REGS);

}


