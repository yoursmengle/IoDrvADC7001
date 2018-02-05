#ifndef __COMMON_H_
#define  __COMMON_H_

typedef unsigned int uint32;
typedef int int32;
typedef unsigned short uint16;
typedef unsigned char uchar;

#define RD_WR_REG32(reg) ( *((volatile uint32 *) (reg)) )

/* Our I/O Area */
#define MAX_AI_NUM 	32
#define MAX_DI_NUM  	18
#define MAX_PI_NUM       14
#define MAX_AO_NUM	0
#define MAX_DO_NUM  	18
#define MAX_PWM_NUM 	14
#define MAX_LED_NUM	4

#define MAX_IN		(MAX_AI_NUM+MAX_DI_NUM+MAX_PI_NUM)
#define MAX_OUT		(MAX_AO_NUM+MAX_DO_NUM+MAX_PWM_NUM+MAX_LED_NUM)
#define MAX_CHANNELS 	(MAX_IN+MAX_OUT)
#define MAX_DRIVERS 1

//data offset in s_ulyIO[]
#define BASE_AI	0
#define BASE_DI	(BASE_AI+MAX_AI_NUM)
#define BASE_PI	(BASE_DI+MAX_DI_NUM)
#define BASE_AO	0
#define BASE_DO	(BASE_AO+MAX_AO_NUM)
#define BASE_PWM	(BASE_DO+MAX_DO_NUM)
#define BASE_LED	(BASE_PWM+MAX_PWM_NUM)

#endif  // __COMMON_H_
