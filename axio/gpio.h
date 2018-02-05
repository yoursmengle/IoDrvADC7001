/*
  * gpio.h
  *
  * Copyright (c) 2014-2017 Hiden Tech Ltd.
  * 	   File: gpio.h
  * 	   Date: 2016/11/3
  * 	 Author: riguang peng
  * Description: A program to show how to read io from user-space.
*/
#ifndef _GPIO_H_
#define _GPIO_H_
#include "common.h"


#define GPIO_BASE_ADDR  		(0xe000a000)
#define GPIO_ALLOC_SIZE      	((size_t)0x1000)


#define DIR_OUT	        (1)
#define DIR_IN	        (0)
#define MAX_GPIO 		118
uint32 init_gpio();
uint32 init_DI_DO(void);
uint32 read_all_DIs();
uint32 write_all_DOs();	
uint32 write_all_LEDs();	

void write_pin(uint32 pin, uint32 data);
uint32 read_pin(uint32 pin);
void set_pin_dir(uint32 pin, uint32 dir);
void enable_pin(uint32 pin);
void set_select(uint32 chan);   //  xadc 4in1 chan select

#endif /* _GPIO_H_ */
