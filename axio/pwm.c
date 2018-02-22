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



