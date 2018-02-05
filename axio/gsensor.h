/*
  * gsensor.h
  *
  * Copyright (c) 2014-2017 Hiden Tech Ltd.
  * 	   File: gsensor.h
  * 	   Date: 2016/11/3
  * 	 Author: riguang peng
  * Description: 
*/
#ifndef _GSENSOR_H_
#define _GSENSOR_H_
#include "common.h"

#define GSENSOR_DEV	"/dev/input/event0"

uint32 init_gsensor();
void un_init_gsensor();
uint32 read_gsensor(uint32 *x, uint32 *y, uint32 *z);


#endif /* _GSENSOR_H_ */




