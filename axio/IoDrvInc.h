#ifndef __IODRVINC_H__
#define __IODRVINC_H__
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include "ai.h"
#include "ao.h"
#include "pi.h"
#include "pwm.h"
#include "gpio.h"
#include "i2c.h"
#include "gsensor.h"

//#define ERR_OK 		(0)  //codesys has defined it 
#define ERR_AI_INIT 	(1)
#define ERR_PWM_INIT 	(2)
#define ERR_GPIO_INIT	(3)
#define ERR_I2C_INIT	(4)
#define ERR_GSENSOR_INIT	(5)
#define ERR_LED_INIT	(6)

uint32 iosInit(void);

extern uint32 g_all_AIs[MAX_AI_NUM];
extern uint32 g_all_DIs[MAX_DI_NUM];
extern uint32 g_all_PIs[MAX_PI_NUM];

extern uint32 g_all_AOs[MAX_AO_NUM];

extern uint32 g_all_DOs[MAX_DO_NUM];
extern uint32 g_old_DOs[MAX_DO_NUM];

extern uint32 g_all_PWMs[MAX_PWM_NUM];
extern uint32 g_old_PWMs[MAX_PWM_NUM];

extern uint32 g_all_LEDs[MAX_LED_NUM];
extern uint32 g_old_LEDs[MAX_LED_NUM];

#endif  //__IODRVINC_H__

