/*
   * gsensor.c
   *
   *
   * Copyright (c) 2014-2017 Hiden Tech Ltd.
   *		File: gsensor.c
   *		Date: 2016/11/3
   *	  Author: riguang peng
   * Description: A program to show how to read and write i2c.
   */
   
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <linux/input.h>
#include "gsensor.h"

#define ERR_MSG(fmt, args...)	fprintf(stderr, fmt, ##args)
#define DBG_MSG(fmt, args...)	fprintf(stdout, fmt, ##args)


uint32 g_gsensor_fd = 0;


uint32 init_gsensor()
{

	/* Open button device */
	g_gsensor_fd = open(GSENSOR_DEV, O_RDONLY);
	
	if (g_gsensor_fd < 0) 
	{
		ERR_MSG("open %s failed!\n", GSENSOR_DEV);
	}

	return g_gsensor_fd;
}


void un_init_gsensor()
{
	if (g_gsensor_fd > 0)
	{
		close(g_gsensor_fd);
	}
}

uint32 read_gsensor(uint32 *x, uint32 *y, uint32 *z)
{
	uint32 retval = -1, fd = -1;
	struct input_event ev;
	struct timeval tv = {0};
	fd_set rdfds;

	/* use select function to read button events */
	for (;;) 
	{
		fd  = g_gsensor_fd;
		FD_ZERO(&rdfds);
		FD_SET(fd, &rdfds);
		tv.tv_sec = 3; /* Set timeout to 3 seconds */
		tv.tv_usec = 0;
		retval = select(fd+1, &rdfds, NULL, NULL, &tv);
		
		if (retval < 0) 
		{ 	
			/* select error */
			ERR_MSG("select error!!\n");
			close(fd);
			return retval;
		} 
		else if ( retval == 0) 
		{ 
			/* timeout */
			DBG_MSG("Polling ...\n");
		} 
		else 
		{
			memset(&ev, 0, sizeof(ev));
			retval = read(fd, &ev, sizeof(struct input_event));
			
			if (retval != sizeof(struct input_event)) 
			{
				ERR_MSG("Read input event failed! retval:%d\n", retval);
				return -1;
			} 
			else 
			{
				if (ev.type == EV_SYN) 
				{
					//DBG_MSG("[%.6lf] X:%4d,\tY:%4d,\tZ:%4d\n", ev.time.tv_sec+ev.time.tv_usec/1000000.0, *x, *y, *z);

					return 0;
				} 
				else if (ev.type == EV_ABS) 
				{
					switch (ev.code) 
					{
						case ABS_X:
							*x = ev.value;
							break;
						case ABS_Y:
							*y = ev.value;
							break;
						case ABS_Z:
							*z = ev.value;
							break;
						default:
							break;
					}
				}
			}
		}
	}
	
	return 0;
}


