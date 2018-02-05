/*****************************************************************************
 * Copyright (c) 2014-2017 Hiden Tech Ltd.
 *        File: main-test.c
 *        Date: 2016/11/3
 *      Author: riguang peng
 * Description: A program to show how to read io from user-space.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include "ai.h"
#include "pwm.h"
#include "gpio.h"
#include "i2c.h"
#include "gsensor.h"

#define READ_DELAY_US	(1000*1000) /* 1s */

int main(int argc, const char *argv[])
{
	uint32 ai_value;
	uint32 pwm_value;
	uint32 gpio_value;
	int x, y, z;

	sscanf(argv[1], "%u", &pwm_value);
	printf("pwm value: %u\n", pwm_value);

#if 0

	if (init_ai() > 0)
	{
		read_all_ais();
		
		
		//ai_value = read_ai(AI1_OFFSET);
		//printf("ai-%d value: %d\n", AI1_OFFSET, ai_value);

		//ai_value = read_ai(AI9_OFFSET);
		//printf("ai-%d value: %d\n", AI9_OFFSET, ai_value);

		//ai_value = read_ai(AI12_OFFSET);
		//printf("ai-%d value: %d\n", AI12_OFFSET, ai_value);
	}

	
	if (init_PWM() > 0)
	{
		write_pwm(PWM0_OFFSET, pwm_value);
		write_pwm(PWM1_OFFSET, pwm_value);
		write_pwm(PWM2_OFFSET, pwm_value);
		write_pwm(PWM3_OFFSET, pwm_value);
		write_pwm(PWM4_OFFSET, pwm_value);
		write_pwm(PWM5_OFFSET, pwm_value);
		write_pwm(PWM6_OFFSET, pwm_value);
	}

	





	if (init_gpio() > 0)
	{
		set_pin_dir(GPIO_PIN_54, DIR_OUT);
		set_pin_dir(GPIO_PIN_55, DIR_OUT);
		set_pin_dir(GPIO_PIN_56, DIR_OUT);
		set_pin_dir(GPIO_PIN_57, DIR_OUT);
		set_pin_dir(GPIO_PIN_58, DIR_OUT);
		set_pin_dir(GPIO_PIN_59, DIR_OUT);
		set_pin_dir(GPIO_PIN_60, DIR_OUT);
		set_pin_dir(GPIO_PIN_61, DIR_OUT);
		set_pin_dir(GPIO_PIN_78, DIR_OUT);
		set_pin_dir(GPIO_PIN_79, DIR_OUT);
		
		
		enable_pin(GPIO_PIN_54);
		enable_pin(GPIO_PIN_55);
		enable_pin(GPIO_PIN_56);
		enable_pin(GPIO_PIN_57);
		enable_pin(GPIO_PIN_58);
		enable_pin(GPIO_PIN_59);
		enable_pin(GPIO_PIN_60);
		enable_pin(GPIO_PIN_61);
		enable_pin(GPIO_PIN_78);
		enable_pin(GPIO_PIN_79);
		
		write_pin(GPIO_PIN_54, 0);
		write_pin(GPIO_PIN_55, 0);
		write_pin(GPIO_PIN_56, 0);
		write_pin(GPIO_PIN_57, 0);
		write_pin(GPIO_PIN_58, 0);
		write_pin(GPIO_PIN_59, 0);
		write_pin(GPIO_PIN_60, 0);
		write_pin(GPIO_PIN_61, 0);

		
		write_pin(GPIO_PIN_78, 1);
		write_pin(GPIO_PIN_79, 1);
		
		
		
		set_pin_dir(GPIO_PIN_62, DIR_IN);
		set_pin_dir(GPIO_PIN_63, DIR_IN);
		set_pin_dir(GPIO_PIN_64, DIR_IN);
		set_pin_dir(GPIO_PIN_65, DIR_IN);
		set_pin_dir(GPIO_PIN_66, DIR_IN);
		set_pin_dir(GPIO_PIN_67, DIR_IN);
		set_pin_dir(GPIO_PIN_68, DIR_IN);
		set_pin_dir(GPIO_PIN_69, DIR_IN);
		
		enable_pin(GPIO_PIN_62);
		enable_pin(GPIO_PIN_63);
		enable_pin(GPIO_PIN_64);
		enable_pin(GPIO_PIN_65);
		enable_pin(GPIO_PIN_66);
		enable_pin(GPIO_PIN_67);
		enable_pin(GPIO_PIN_68);
		enable_pin(GPIO_PIN_69);
		
		
		gpio_value = read_pin(GPIO_PIN_62);
		printf("pin%d value: %d\n", GPIO_PIN_62, gpio_value);
		
		gpio_value = read_pin(GPIO_PIN_63);
		printf("pin%d value: %d\n", GPIO_PIN_63, gpio_value);
		
		gpio_value = read_pin(GPIO_PIN_64);
		printf("pin%d value: %d\n", GPIO_PIN_64, gpio_value);
		
		gpio_value = read_pin(GPIO_PIN_65);
		printf("pin%d value: %d\n", GPIO_PIN_65, gpio_value);
		
		
		gpio_value = read_pin(GPIO_PIN_66);
		printf("pin%d value: %d\n", GPIO_PIN_66, gpio_value);
		
		gpio_value = read_pin(GPIO_PIN_67);
		printf("pin%d value: %d\n", GPIO_PIN_67, gpio_value);
		
		
		gpio_value = read_pin(GPIO_PIN_68);
		printf("pin%d value: %d\n", GPIO_PIN_68, gpio_value);
		
		gpio_value = read_pin(GPIO_PIN_69);
		printf("pin%d value: %d\n", GPIO_PIN_69, gpio_value);
	}
#endif



	if (init_i2c() > 0)
	{
		write_i2c(0, 1);
		write_i2c(1, 1);
		write_i2c(2, 1);
		write_i2c(3, 1);
		write_i2c(4, 1);
		write_i2c(5, 1);
		write_i2c(6, 1);
		write_i2c(7, 1);
		write_i2c(8, 1);
		write_i2c(9, 0);
		write_i2c(10, 1);
		write_i2c(11, 1);
		write_i2c(12, 1);
		write_i2c(13, 1);
		write_i2c(14, 1);
		write_i2c(15, 1);
	}

	if (init_gsensor() > 0)
	{
		read_gsensor(&x, &y, &z);	
		printf("x: %d, y: %d, z: %d\n", x, y, z);
	}



	usleep(READ_DELAY_US);

	//un_init_ai();
	//un_init_pwm();
	//un_init_gpio();
	un_init_i2c();
	//un_init_gsensor();

	return 0;
}
