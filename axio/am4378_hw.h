#ifndef __AM4378_HW_H__
#define __AM4378_HW_H__

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

typedef unsigned int uint32;
typedef int int32;
typedef unsigned short uint16;
typedef unsigned char uchar;

#include "hw_control_AM335x.h"


#define RD_WR_REG32(reg) (*((volatile uint32 *) (reg)))
#define HWREG(reg) 	(*((volatile uint32 *) (reg)))

//GPIO 
#define GPIO_BANKS_NUM	6
#define GPIO_ALLOC_SIZE  4096

#define GPIO_0_BASE_ADDR		((void*)0x44e07000)
#define GPIO_1_BASE_ADDR		((void*)0x4804c000)
#define GPIO_2_BASE_ADDR		((void*)0x481ac000)
#define GPIO_3_BASE_ADDR		((void*)0x481ae000)
#define GPIO_4_BASE_ADDR		((void*)0x48320000)
#define GPIO_5_BASE_ADDR		((void*)0x48322000)

#define GPIO_DATAIN  		0x0138
#define GPIO_DATAOUT 		0x013c
#define GPIO_CLEAR_DATAOUT 	0x0190
#define GPIO_SET_DATAOUT 	0x0194
#define GPIO_DIRECTION		0x0134

//ADC0
#define AI_BASE_ADDR  		(0x44e0d000)
#define AI_ALLOC_SIZE      	((size_t)0x1000)


#define BIT(nr)	((uint32)(1 << (nr)))

//registers of AM437x ADC0
#define TSCADC_REG_IRQEOI		0x020
#define TSCADC_REG_RAWIRQSTATUS	0x024
#define TSCADC_REG_IRQSTATUS		0x028
#define TSCADC_REG_IRQENABLE		0x02C
#define TSCADC_REG_IRQCLR		0x030
#define TSCADC_REG_IRQWAKEUP		0x034
#define TSCADC_REG_CTRL			0x040
#define TSCADC_REG_ADCFSM		0x044
#define TSCADC_REG_CLKDIV		0x04C
#define TSCADC_REG_SE			0x054
#define TSCADC_REG_IDLECONFIG		0x058
#define TSCADC_REG_CHARGECONFIG	0x05C
#define TSCADC_REG_CHARGEDELAY		0x060
#define TSCADC_REG_STEPCONFIG(n)	(0x64 + ((n-1) * 8))
#define TSCADC_REG_STEPDELAY(n)	(0x68 + ((n-1) * 8))
#define TSCADC_REG_STEPCONFIG13	0x0C4
#define TSCADC_REG_STEPDELAY13		0x0C8
#define TSCADC_REG_STEPCONFIG14	0x0CC
#define TSCADC_REG_STEPDELAY14		0x0D0
#define TSCADC_REG_FIFO0CNT		0xE4
#define TSCADC_REG_FIFO0THR		0xE8
#define TSCADC_REG_FIFO1CNT		0xF0
#define TSCADC_REG_FIFO1THR		0xF4
#define TSCADC_REG_FIFO0			0x100
#define TSCADC_REG_FIFO1			0x200

/*	Register Bitfields	*/
#define TSCADC_IRQWKUP_ENB		BIT(0)
#define TSCADC_IRQWKUP_DISABLE		0x00
#define TSCADC_STPENB_STEPENB		0x7FFF
#define TSCADC_IRQENB_FIFO0THRES	BIT(2)

#define ADC_STPENB_STEPENB		0x1FE 
#define TSCADC_IRQENB_STEPEND		BIT(1) 
#define TSCADC_IRQENB_FIFO1THRES	BIT(5)
#define TSCADC_IRQENB_PENUP		BIT(9)
#define TSCADC_IRQENB_HW_PEN		BIT(0)
#define TSCADC_STEPCONFIG_MODE_HWSYNC	0x2
#define TSCADC_STEPCONFIG_2SAMPLES_AVG	(1 << 4)
#define TSCADC_STEPCONFIG_XPP		BIT(5)
#define TSCADC_STEPCONFIG_XNN		BIT(6)
#define TSCADC_STEPCONFIG_YPP		BIT(7)
#define TSCADC_STEPCONFIG_YNN		BIT(8)
#define TSCADC_STEPCONFIG_XNP		BIT(9)
#define TSCADC_STEPCONFIG_YPN		BIT(10)

#define TSCADC_STEPCONFIG_1_NEGATIVE_INP 	(0)		
#define TSCADC_STEPCONFIG_1_INP		(0) 
#define TSCADC_STEPCONFIG_2_INP		BIT(19) 
#define TSCADC_STEPCONFIG_3_INP		BIT(20) 
#define TSCADC_STEPCONFIG_4_INP		(BIT(19)|BIT(20)) 
#define TSCADC_STEPCONFIG_5_INP		BIT(21) 
#define TSCADC_STEPCONFIG_6_INP		(BIT(19)|BIT(21))  
#define TSCADC_STEPCONFIG_7_INP		(BIT(21)|BIT(20))  
#define TSCADC_STEPCONFIG_8_INP		(BIT(19)|BIT(20)|BIT(21))
#define TSCADC_STEPCONFIG_REFP			(BIT(12)|BIT(13))

#define TSCADC_STEPCONFIG_RFM				((1 << 23)|(1 << 24)) 
#define TSCADC_STEPCONFIG_SINGLE_ENDED_OPER_MODE (0 <<25)
#define TSCADC_STEPCONFIG_MODE   	(0)
#define TSCADC_STEPCONFIG_RFP		(1 << 12)
#define TSCADC_STEPCONFIG_INM		(1 << 18)
#define TSCADC_STEPCONFIG_INP_4	(1 << 19)
#define TSCADC_STEPCONFIG_INP		(1 << 20)
#define TSCADC_STEPCONFIG_INP_5	(1 << 21)
#define TSCADC_STEPCONFIG_FIFO1	(1 << 26)
#define TSCADC_STEPCONFIG_IDLE_INP	(1 << 22)
#define TSCADC_STEPCONFIG_OPENDLY	0x0
#define TSCADC_STEPCONFIG_SAMPLEDLY	0x0

#define TSCADC_STEPCONFIG_Z1		(3 << 19)

#define TSCADC_CNTRLREG_TSCSSENB	BIT(0)
#define TSCADC_CNTRLREG_STEPID		BIT(1)
#define TSCADC_CNTRLREG_STEPCONFIGWRT	BIT(2)
#define TSCADC_CNTRLREG_TSCENB		BIT(7)
#define TSCADC_CNTRLREG_4WIRE		(0x1 << 5)
#define TSCADC_CNTRLREG_5WIRE		(0x1 << 6)
#define TSCADC_CNTRLREG_8WIRE		(0x3 << 5)
#define TSCADC_ADCFSM_STEPID		0x10
#define TSCADC_ADCFSM_FSM		BIT(5)

#define ADC_CLK				3000000

#define MAX_12BIT                       ((1 << 12) - 1)


#endif //__AM4378_HW_H__
