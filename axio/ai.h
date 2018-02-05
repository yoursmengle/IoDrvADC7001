/*
  * ai.h
  *
  * Copyright (c) 2014-2017 Hiden Tech Ltd.
  * 	   File: ai.h
  * 	   Date: 2016/11/3
  * 	 Author: riguang peng
  * Description: A program to show how to read io from user-space.
*/
#ifndef AI_H_
#define AI_H_
#include "common.h"

#define AI_BASE_ADDR  (0x43c00000)
#define AI_ALLOC_SIZE      ((size_t)0x10000)


/*
#define AO_OFFSET 
#define AI1_OFFSET  (0X18*4)   //JP1-27
#define AI2_OFFSET  (0X10*4)
#define AI3_OFFSET  (0X14*4)
#define AI4_OFFSET  (0X1C*4)
#define AI5_OFFSET  (0X1D*4)
#define AI6_OFFSET  (0X1B*4)
#define AI7_OFFSET  (0X15*4)
#define AI8_OFFSET  (0X13*4)  //JP1-20
#define AI9_OFFSET  (0X12*4)  //JP1-19/17/15/13
#define AI10_OFFSET (0X17*4)  //JP1-18/16/14/12
#define AI11_OFFSET (0X1A*4)
#define AI12_OFFSET (0X1E*4)
*/


uint32  init_AI();
uint32 read_AI(uint32 AI_no);
void read_all_AIs();

//extern uchar* g_ai_base_addr;
//extern t_all_input m_t_all_input;


#endif /* AI_H_ */

