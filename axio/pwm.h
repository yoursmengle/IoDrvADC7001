/*
  * pwm.h
  *
  * Copyright (c) 2014-2017 Hiden Tech Ltd.
  * 	   File: pwm.h
  * 	   Date: 2016/11/3
  * 	 Author: riguang peng
  * Description: A program to show how to read io from user-space.
*/
#ifndef PWM_H_
#define PWM_H_
#include "common.h"

#define PWM_BASE_ADDR  (0x43c00000)
#define PWM_ALLOC_SIZE      ((size_t)0x10000)

uint32 init_PWM(void);
void un_init_pwm(void);
void write_pwm(uint32 pwm_no, uint32 value);


//extern uchar* g_pwm_base_addr;

#endif /* PWM_H_ */

