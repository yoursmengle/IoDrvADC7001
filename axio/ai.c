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
		val = RD_WR_REG32(g_ai_vir_addr+0x100); //fifo-0
		if(val < 4096) return val;
		else return 4096;
	}else if(AI_no ==7) {
		val = RD_WR_REG32(g_ai_vir_addr+0x200);  //fifo-1
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



