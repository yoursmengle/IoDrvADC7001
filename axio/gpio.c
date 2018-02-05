/*
   * do_gpio.c
   *
   *
   * Copyright (c) 2014-2017 Hiden Tech Ltd.
   *		File: tsensor-test.c
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
#include "gpio.h"
#include "i2c.h"

uint32 g_all_DIs[MAX_DI_NUM];
uint32 g_all_DOs[MAX_DO_NUM];
uint32 g_old_DOs[MAX_DO_NUM];
uint32 g_all_LEDs[MAX_LED_NUM];
uint32 g_old_LEDs[MAX_LED_NUM];

//  DO ports 0 ~ 15
uint32 DO_GPIO_PORT[MAX_DO_NUM] = {	4*32 + 10, \
						4*32 + 13, \
						5*32 + 7, \
						5*32 + 4, \
						5*32 + 5, \
						5*32 + 2, \
						5*32 + 1, \
						3*32 + 14, \
						2*32 + 15, \
						2*32 + 17, \
						4*32 + 26, \
						4*32 + 27, \
						0*32 + 0, \
						1*32 + 18, \
						1*32 + 24, \
						0*32 + 20, \
							};
//LED ports  0 ~ 2

uint32 LED_GPIO_PORT[MAX_LED_NUM*2] = {2*32+ 22, \   
						2*32+23, \
						3*32+1, \
						2*32+25, \
						2*32+24, \
						5*32+8};


int export_port(unsigned int port_num)
{
	char cmd[80];
	sprintf(cmd, "echo %d > /sys/class/gpio/export \n",port_num);
	FILE *fp = popen(cmd, "r");
	pclose(fp);
		printf(cmd);
	return 0;
}
int output_high(unsigned int port_num)
{
	char cmd[80];
	sprintf(cmd, "echo out > /sys/class/gpio/gpio%d/direction \n", port_num);
	FILE *fp = popen(cmd, "r");
	pclose(fp);

	sprintf(cmd, "echo 1 > /sys/class/gpio/gpio%d/value \n", port_num);
	fp = popen(cmd, "r");
	pclose(fp);
		printf(cmd);
	return 0;
}

int output_low(unsigned int port_num)
{
	char cmd[80];
	sprintf(cmd, "echo out > /sys/class/gpio/gpio%d/direction \n", port_num);
	FILE *fp = popen(cmd, "r");
	pclose(fp);

	sprintf(cmd, "echo 0 > /sys/class/gpio/gpio%d/value \n", port_num);
	fp = popen(cmd, "r");
	pclose(fp);
		printf(cmd);
	return 0;
}

int input_port(unsigned int port_num)
{
	char cmd[80];
	sprintf(cmd, "echo in > /sys/class/gpio/gpio%d/direction \n", port_num);
	FILE *fp = popen(cmd, "r");
	pclose(fp);
		printf(cmd);
	return 0;
}



uint32 init_LED(void)
{
	uint32 i;
	printf("starting Init the LEDs...\n");

/************************************* for test jhzhou*/
	for(i = 0; i<MAX_LED_NUM*2; i++) {
		uint32 port_no = LED_GPIO_PORT[i];
		export_port(port_no);
		output_high(port_no);
	}
	for(i = 0; i< MAX_LED_NUM; i++) {
		g_all_LEDs[i] = 0;
		g_old_LEDs[i] = 0;
	}

	return 0;
/************************************* for test jhzhou*/
}
uint32 init_gpio(void)
{
	printf("starting Init the GPIO...\n");

	return 0;
}

uint32 init_DI_DO(void)
{
	uint32 i;
	init_gpio();

	init_LED();
/*
	for(i = 0; i<MAX_LED_NUM; i++) {
		uint32 port_no = LED_GPIO_PORT[i];
		export_port(port_no);
		output_low(port_no);
		g_all_LEDs[i] = 0;
		g_old_LEDs[i] = 0;
	}
*/
	return 0;
}

uint32 read_DI(uint32 DI_no)
{
	
	return (DI_no%2);
}

uint32 read_all_DIs(void)
{
	uint32 i=0;
	for (i = 0; i < MAX_DI_NUM; i++) {
		g_all_DIs[i]=read_DI(i);
	}
	
	return i;
}


uint32 write_DO(uint32 DO_no, uint32 val)
{

	return 0;
}

uint32 write_all_DOs()
{
	uint32 i=0,val=0,ret=0;
	for (i = 0; i < MAX_DO_NUM; i++) {
		val = g_all_DOs[i];
		if(val != g_old_DOs[i]) {
			ret = write_DO(i,val);
		}
		g_old_DOs[i] = g_all_DOs[i];
	}
	return i;
}

uint32 write_LED(uint32 LED_no, uint32 val)
{
	uint32 port1 = LED_GPIO_PORT[LED_no];
	uint32 port2 = LED_GPIO_PORT[LED_no+MAX_LED_NUM];
	if(val==0) {
		output_high(port1);
		output_high(port2);
	} else {
		output_low(port1);
		output_low(port2);
	}
	return 0;
}

uint32 write_all_LEDs()
{
	uint32 i=0;
	uint32 ret;
	for(i=0; i< MAX_LED_NUM; i++) {
		uint32 val = g_all_LEDs[i];
		if(val != g_old_LEDs[i]) {
			ret = write_LED(i, val);
		}
		g_old_LEDs[i] = g_all_LEDs[i];
	}
	return i;
}


