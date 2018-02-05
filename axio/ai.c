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

uchar* g_ai_base_addr=NULL;
uint32 g_ai_mem_fd = 0;

uint32 init_AI()
{
	uint32 i;
	
	printf("Starting ai init.\n");

    return 0;
}

uint32 read_AI(uint32 AI_no)
{
		
	return AI_no+2000; 
}


void read_all_AIs()
{
	uint32 i;

	for (i = 0; i < MAX_AI_NUM; i++) {
		g_all_AIs[i]=read_AI(i);
	}

}



