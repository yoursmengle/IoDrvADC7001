#ifndef __AM4378_HW_H__
#define __AM4378_HW_H__


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


#endif //__AM4378_HW_H__
