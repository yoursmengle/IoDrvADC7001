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

//   DI  ports 0~17
uint32 DI_GPIO_PORT[MAX_DI_NUM] = {
						0*32 + 7,	3*32 + 17,	2*32 + 11,	4*32 + 7, \
						4*32 + 5, 	4*32 + 3, 	4*32 + 24,	4*32 + 28, \
						0*32 + 1,	5*32 + 13, 	1*32 + 28,	1*32 + 19, \
						0*32 + 19,	2*32 + 1,	2*32 + 29,	2*32 + 28, \
						2*32 + 27, 	2*32 + 26
					};

//  DO ports 0 ~ 15
uint32 DO_GPIO_PORT[MAX_DO_NUM] = {	
						4*32 + 10,	4*32 + 13,	5*32 + 7,	5*32 + 4, \
						5*32 + 5, 	5*32 + 2, 	5*32 + 1,	3*32 + 14, \
						2*32 + 15,	2*32 + 17, 	4*32 + 26,	4*32 + 27, \
						0*32 + 0,	1*32 + 18,	1*32 + 24,	0*32 + 20 \
					};
//LED ports  0 ~ 2
// Drive by 2 channels
uint32 LED_GPIO_PORT[MAX_LED_NUM*2] = {
						2*32+25,	2*32+24,	5*32+8,\
						2*32+ 22,	2*32+23,	3*32+1
						};
						

uint32 export_port(uint32 port_num)
{
	char cmd[80];
	sprintf(cmd, "echo %d > /sys/class/gpio/export \n",port_num);
	FILE *fp = popen(cmd, "r");
	pclose(fp);
//		printf(cmd);
	return 0;
}
uint32 set_output(uint32 port_num)
{
	char cmd[80];
	sprintf(cmd, "echo out > /sys/class/gpio/gpio%d/direction \n", port_num);
	FILE *fp = popen(cmd, "r");
	pclose(fp);
//		printf(cmd);
	return 0;
}

uint32 read_input(uint32 port_num)
{
	char cmd[80];
	char val[4]="9999";
	sprintf(cmd, "cat /sys/class/gpio/gpio%d/value \n", port_num);
	FILE *fp = popen(cmd, "r");
	fgets(val,3,fp);
	printf("*>");
	printf(val);
	printf("<*");
	pclose(fp);
	if(val[0] == '1') {
		return 1;
	} else {
		return 0;
	}
}

uint32 set_input(uint32 port_num)
{
	char cmd[80];
	sprintf(cmd, "echo in > /sys/class/gpio/gpio%d/direction \n", port_num);
	FILE *fp = popen(cmd, "r");
	pclose(fp);
//		printf(cmd);
	return 0;
}

uint32 output_high(uint32 port_num)
{
	char cmd[80];
	sprintf(cmd, "echo 1 > /sys/class/gpio/gpio%d/value \n", port_num);
	FILE *fp = popen(cmd, "r");
	pclose(fp);
//		printf(cmd);
	return 0;
}

uint32 output_low(uint32 port_num)
{
	char cmd[80];

	sprintf(cmd, "echo 0 > /sys/class/gpio/gpio%d/value \n", port_num);
	FILE *fp = popen(cmd, "r");
	pclose(fp);
//		printf(cmd);
	return 0;
}

uint32 init_LED(void)
{
	uint32 i;
	printf("starting Init the LEDs...\n");
	for(i = 0; i<MAX_LED_NUM; i++) {
		g_all_LEDs[i] = 0;
		g_old_LEDs[i] = 0;

		uint32 port_no = LED_GPIO_PORT[i];
		export_port(port_no);
		set_output(port_no);
		output_high(port_no);  //gpio high will set the light off
		
		port_no+=MAX_LED_NUM;
		export_port(port_no);
		set_output(port_no);
		output_high(port_no);  //gpio high will set the light off
	}

	return 0;
}
uint32 init_DI(void)
{

	
	printf("starting Init the DIs...\n");
	for(uint32 i = 0; i< MAX_DI_NUM; i++) {
		g_all_DIs[i] = 0;
		uint32 port_no = DI_GPIO_PORT[i];
		export_port(port_no);
		set_input(port_no);
	}

	return 0;
}

uint32 init_DO(void)
{
	printf("starting Init the DOs...\n");
	for(uint32 i = 0; i< MAX_DO_NUM; i++) {
		g_all_DOs[i] = 0;
		g_old_DOs[i] = 0;
		uint32 port_no = DO_GPIO_PORT[i];
		export_port(port_no);
		set_output(port_no);
		output_low(port_no);
	}
	return 0;
}

uint32 init_DI_DO(void)
{
	uint32 i;
	init_DO();
	init_DI();
	init_LED();

	return 0;
}

uint32 read_DI(uint32 DI_no)
{
	uint32 port_no = DI_GPIO_PORT[DI_no];
	return read_input(port_no);
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
	uint32 port_no = DO_GPIO_PORT[DO_no];
	if(val) {
		output_high(port_no);
	} else {
		output_low(port_no);
	}
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


