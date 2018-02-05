/*
  * i2c.h
  *
  * Copyright (c) 2014-2017 Hiden Tech Ltd.
  * 	   File: hiden_i2c.h
  * 	   Date: 2016/11/3
  * 	 Author: riguang peng
  * Description: 
*/
#ifndef _HIDEN_I2C_H_
#define _HIDEN_I2C_H_
#include "common.h"


#define MAX_I2C_PORT 16
#define SLAVE_I2C_ADD 0X20

int32 init_i2c();
int32 write_i2c(uint32 i2c_port, uint32 value);

int32 init_pca9555(void);
int32 write_rly(uint32 chan, uint32 val);
int32 write_sel(uint32 chan, uint32 val);
int32 write_run_light(uint32 val);


#endif /* _HIDEN_I2C_H_ */

