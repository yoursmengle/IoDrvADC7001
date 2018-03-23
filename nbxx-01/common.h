#ifndef __COMMON_H_NBXX_01
#define __COMMON_H_NBXX_01

#include <stdio.h>      /*标准输入输出定义*/  
#include <stdlib.h>     /*标准函数库定义*/  
#include <unistd.h>     /*Unix 标准函数定义*/  
#include <sys/types.h>   
#include <sys/stat.h>     
#include <fcntl.h>      /*文件控制定义*/  
#include <termios.h>    /*PPSIX 终端控制定义*/  
#include <errno.h>      /*错误号定义*/  
#include <string.h>  
#include <sys/time.h>  

#include "bsp_nbxx_01.h"
#include "app_config.h"
#include "nbxx_01_app.h"
#include "nbxx_01_udp.h"
#include "lierda_server.h"


typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef int int32_t;

#ifndef bool
typedef unsigned char bool;
#endif

#ifndef TRUE
#define TRUE (0)
#endif

#ifndef FALSE
#define FALSE (-1)
#endif

#ifndef true
#define true (0)
#endif

#ifndef false
#define false (-1)
#endif

#endif //__COMMON_H_NBXX_01
