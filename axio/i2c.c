/*
   * i2c.c
   *
   *
   * Copyright (c) 2014-2017 Hiden Tech Ltd.
   *		File: i2c.c
   *		Date: 2016/11/3
   *	  Author: riguang peng
   * Description: A program to show how to read and write i2c.
   */
   
#include<stdio.h>
#include <string.h> 
#include<stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include<fcntl.h>
#include<linux/i2c-dev.h>
#include<linux/i2c.h>
#include "i2c.h"

static int32 g_i2c_fd = -1;

const uint32 RLY_OFFSET[] = {
	15,
	14,
	13,
	12,
};

const uint32 SEL_OFFSET[] = {
	11,
	10,
};

const uint32 RUN_LIGHT_OFFSET = 9;


int32 init_i2c()
{
	if((g_i2c_fd = open("/dev/i2c-1",O_RDWR)) < 0) {
		printf("error opening device!");
	} else {
		ioctl(g_i2c_fd, I2C_TIMEOUT, 2);
   		ioctl(g_i2c_fd, I2C_RETRIES, 1);
	}
	
   	return g_i2c_fd;
}

/*
void un_init_i2c()
{
	if (g_i2c_fd > 0)
	{
		close(g_i2c_fd);
	}
}
*/
int32 write_i2c_zero(void)  //I2C clear all 16 bits
{
	 int32 ret;
	 uchar data[3]={0}; 
	 uchar command = 0;
	 struct i2c_rdwr_ioctl_data work_queue;
	 struct i2c_msg OutMsg[2] ;

	 // Ð´Êä³ö¶Ë¿Ú¼Ä´æÆ÷
	 command=0x02;
	 OutMsg[0].addr=SLAVE_I2C_ADD;
	 OutMsg[0].flags=0; //write
	 OutMsg[0].len=1;
	 OutMsg[0].buf=&command;
 
	 OutMsg[1].addr=SLAVE_I2C_ADD;
	 OutMsg[1].flags=0; //write
	 OutMsg[1].len=2;
	 OutMsg[1].buf=data;
 
	 data[0]= 0;
	 data[1]= 0;

	 work_queue.msgs=OutMsg;
	 work_queue.nmsgs=2;
 
	 ret = ioctl(g_i2c_fd, I2C_RDWR, (unsigned long)&work_queue);
	 if(ret<0) {
		 printf("Error during I2C_RDWR ioctl with error code: %d\n",ret);
		 close(g_i2c_fd);
		 g_i2c_fd = -1;
		 return -2;
	 }	 	 

	 return 0;
 }
int32 init_pca9555(void)
{
	 int32 ret;
	 uchar data[3]={0}; 
	 uchar command = 0;
	 struct i2c_rdwr_ioctl_data work_queue;
	 struct i2c_msg OutMsg ;

	if(g_i2c_fd < 0) {
		init_i2c();
	}

	write_i2c_zero(); //clear the output data register

	 // ÅäÖÃ0x06·½ÏòÅäÖÃ¼Ä´æÆ÷£¬p0.0~p0.7 are all inputs
	 command = 0x06;
	 OutMsg.addr=SLAVE_I2C_ADD;
	 OutMsg.flags=0; //write
	 OutMsg.len=2;
	 OutMsg.buf = data;
	 OutMsg.buf[0]=command;
	 OutMsg.buf[1]=0xFF;  //input

 	 work_queue.msgs=&OutMsg;
	 work_queue.nmsgs=1;

	 ret = ioctl(g_i2c_fd, I2C_RDWR, (unsigned long)&work_queue);
	 if(ret<0) {
		 printf("Error during I2C_RDWR ioctl with error code: %d\n",ret);
		 close(g_i2c_fd);
		 g_i2c_fd = -1;
		 return -1;
	 }

	 // ÅäÖÃ0x07·½ÏòÅäÖÃ¼Ä´æÆ÷£¬p1.0~p1.2 is inputs , p1.3~p0.7 are outputs
	 command = 0x07;
	 OutMsg.addr=SLAVE_I2C_ADD;
	 OutMsg.flags=0; //write
	 OutMsg.len=2;
	 OutMsg.buf = data;
	 OutMsg.buf[0]=command;
	 OutMsg.buf[1]=0x0D;  //3 input, 5 outputs set to:"0B0000 1101"

	 work_queue.msgs=&OutMsg;
	 work_queue.nmsgs=1;

	 ret = ioctl(g_i2c_fd, I2C_RDWR, (unsigned long)&work_queue);
	 if(ret<0) {
		 printf("Error during I2C_RDWR ioctl with error code: %d\n",ret);
		 close(g_i2c_fd);
		 g_i2c_fd = -1;
		 return -1;
	 }  

	return 0;
}

int32 write_i2c(uint32 i2c_port, uint32 value)
{
	 static uint16 i2c_out_value = 0;
	 static uint16 i2c_out_value_old = 0;
	 int32 ret;
	 uchar data[3]={0}; 
	 uchar command = 0;
	 struct i2c_rdwr_ioctl_data work_queue;
	 struct i2c_msg OutMsg[2] ;
	 static uint32 cntr = 0;

	if (value > 0) {
		i2c_out_value |=  (1 << i2c_port);
	} else {
		i2c_out_value &= (~(1 << i2c_port));
	} 

	if(i2c_out_value_old == i2c_out_value) {  //no change, return;
		if(cntr++ < 200) {  //time out , force output
			return 0;
		}
	}
	i2c_out_value_old = i2c_out_value;
 	cntr = 0;  //write iic timeout counter.

	 // Ð´Êä³ö¶Ë¿Ú¼Ä´æÆ÷
	 command=0x02;
	 OutMsg[0].addr=SLAVE_I2C_ADD;
	 OutMsg[0].flags=0; //write
	 OutMsg[0].len=1;
	 OutMsg[0].buf=&command;
 
	 OutMsg[1].addr=SLAVE_I2C_ADD;
	 OutMsg[1].flags=0; //write
	 OutMsg[1].len=2;
	 OutMsg[1].buf=data;

	 data[0]= i2c_out_value & 0xff;
	 data[1]= i2c_out_value >> 8;
 
	 work_queue.msgs=OutMsg;
	 work_queue.nmsgs=2;
 
	 ret = ioctl(g_i2c_fd, I2C_RDWR, (unsigned long)&work_queue);
	 if(ret<0) {
		 printf("Error during I2C_RDWR ioctl with error code: %d\n",ret);
		 close(g_i2c_fd);
		 g_i2c_fd = -1;
		 return -2;
	 }	 	 

	 return 0;
 }

int32 write_rly(uint32 chan, uint32 val)
{
	if(chan > 3) {
		return -1;
	}
	
	return write_i2c(RLY_OFFSET[chan], val);	
}


int32 write_run_light(uint32 val)
{
	return write_i2c(RUN_LIGHT_OFFSET, val);	
}





