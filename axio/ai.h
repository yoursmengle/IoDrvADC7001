/*
  * ai.h
  *
  * Copyright (c) 2014-2017 Hiden Tech Ltd.
  * 	   File: ai.h
  * 	   Date: 2016/11/3
  * 	 Author: riguang peng
  * Description: A program to show how to read io from user-space.
*/
#ifndef __AI_H_
#define __AI_H_
#include "common.h"
#include "ti_adc.h"

uint32  init_AI();
uint32 read_AI(uint32 AI_no);
void read_all_AIs();

//extern uchar* g_ai_base_addr;
//extern t_all_input m_t_all_input;


#endif /* AI_H_ */

