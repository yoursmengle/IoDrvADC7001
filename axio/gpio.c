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

#define GPIO_DATAIN  		0x0138
#define GPIO_DATAOUT 		0x013c
//#define GPIO_CLEAR_DATAOUT 	0x0190
//#define GPIO_SET_DATAOUT 	0x0194
#define GPIO_DIRECTION		0x0134


void* gpio_phy_addr[GPIO_BANKS_NUM] = { 	0x44e07000,	0x4804c000,	0x481ac000,	0x481ae000,	0x48320000,	0x48322000 };
void* gpio_vir_addr[GPIO_BANKS_NUM] = {	NULL,		NULL,		NULL,		NULL,		NULL,		NULL};  //映射后赋值	

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
uint32 LED_GPIO_PORT[MAX_LED_NUM] = { 2*32+ 22,	2*32+23,	3*32+1};

//						2*32+ 22,	2*32+23,	3*32+1,\
//						2*32+25,	2*32+24,	5*32+8
						


void* g_gpio_base_addr=NULL;
uint32 g_gpio_mem_fd = 0;

uint32 init_gpio(void)
{
	printf("starting Init the GPIO...\n");

	if(g_gpio_mem_fd == 0) {
		g_gpio_mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
	}
	
	if (g_gpio_mem_fd > 0) 	{
		printf("Success to open GPIO /dev/mem fd=0x%08x\n", g_gpio_mem_fd);
	} 	else {
		printf("Fail to open /dev/mem fd=0x%08x\n", g_gpio_mem_fd);
		return 0xffffffff;
	}

	for(uint32 i = 0; i<GPIO_BANKS_NUM; i++) {
		gpio_vir_addr[i] = mmap(NULL, GPIO_ALLOC_SIZE, PROT_READ+PROT_WRITE, MAP_SHARED, g_gpio_mem_fd, gpio_phy_addr[i]);
		printf("The virtual address of GPIO PORT%d is 0x%08x \n", i, gpio_vir_addr[i]);
	}	

	if (gpio_vir_addr[0] == 0xffffffff) 	{
		printf("mmap failed.\n");
		close(g_gpio_mem_fd);
		return 0xffffffff;
	}

	return 0;
}						

uint32 set_dir_output(uint32 port_num)
{
	uint32 bank = port_num/32;
	uint32 pin = port_num - bank*32;
	uint32 mask = 0x1<<pin;
	uint32 addr_direction = gpio_vir_addr[bank]+GPIO_DIRECTION;
	uint32 old_direction = RD_WR_REG32(addr_direction);
	uint32 new_direction = old_direction & (~mask);   //clear the bit to enable output
	RD_WR_REG32(addr_direction) = new_direction;
	printf("set GPIO port %d output!\n",port_num);
	return 0;
}

uint32 set_dir_input(uint32 port_num)
{
	uint32 bank = port_num/32;
	uint32 pin = port_num - bank*32;
	uint32 mask = 0x1<<pin;
	uint32 addr_direction = gpio_vir_addr[bank]+GPIO_DIRECTION;
	uint32 old_direction = RD_WR_REG32(addr_direction);
	uint32 new_direction = old_direction | mask;   //set the bit to enable input
	RD_WR_REG32(addr_direction) = new_direction;
	printf("set GPIO port %d input!\n",port_num);
	return 0;
}

uint32 read_input(uint32 port_num)
{
	uint32 bank = port_num/32;
	uint32 pin = port_num - bank*32;
	uint32 mask = 0x1<<pin;
	uint32 addr_datain = gpio_vir_addr[bank]+GPIO_DATAIN;

	uint32 val = RD_WR_REG32(addr_datain);

	if(val&mask)	return 1;
	else			return 0;

}


uint32 write_output(uint32 port_num, uint32 value)
{
	uint32 bank = port_num/32;
	uint32 pin = port_num - bank*32;
	uint32 mask = 0x1<<pin;
	uint32 addr_dataout = gpio_vir_addr[bank]+GPIO_DATAOUT;
	uint32 old_dataout = RD_WR_REG32(addr_dataout);
	uint32 new_dataout;
	
	if(value) 	new_dataout = old_dataout | mask;   
	else		new_dataout = old_dataout &(~mask);
	
	RD_WR_REG32(addr_dataout) = new_dataout;
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
		set_dir_output(port_no);
		write_output(port_no,HIGH);  //gpio high will set the light off
		
//		port_no+=MAX_LED_NUM;
//		export_port(port_no);
//		set_output(port_no);
//		output_high(port_no);  //gpio high will set the light off
	}

	return 0;
}
uint32 init_DI(void)
{
	printf("starting Init the DIs...\n");
	for(uint32 i = 0; i< MAX_DI_NUM; i++) {
		g_all_DIs[i] = 0;
		uint32 port_no = DI_GPIO_PORT[i];
		set_dir_input(port_no);
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
		set_dir_output(port_no);
		write_output(port_no,LOW);
	}
	return 0;
}

uint32 init_DI_DO(void)
{
	uint32 i;
	init_gpio();
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
		write_output(port_no,1);
	} else {
		write_output(port_no,0);
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
	if(val==0) {
		write_output(port1,HIGH);
	} else {
		write_output(port1,LOW);
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


