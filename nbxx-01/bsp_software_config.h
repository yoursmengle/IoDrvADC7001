/** 
  ******************************************************************************
  * @文件   bsp_software_config.h
  * @作者   罗桂发
  * @版本   V1.0.0
  * @日期   2017-05-03 
  * @说明   
  ********  利尔达科技集团股份有限公司  www.lierda.com ***********************           
  *
***/


#ifndef __BSP_SOFTWARE_CONFIG_H
#define __BSP_SOFTWARE_CONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif


#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "stdarg.h"



#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
#define  BUFFSIZE  512
  /* Size of Trasmission buffer */
#define TXBUFFERSIZE                      BUFFSIZE //(COUNTOF(aTxBuffer) - 1)
  /* Size of Reception buffer */
#define RXBUFFERSIZE                      BUFFSIZE //TXBUFFERSIZE  





#define BigtoLittle16(A)   (( ((uint16_t)(A) & 0xff00) >> 8)    |  (( (uint16_t)(A) & 0x00ff) << 8))  


 
#define BigtoLittle32(A)   ((( (uint32_t)(A) & 0xff000000) >> 24) | \
                                       (( (uint32_t)(A) & 0x00ff0000) >> 8)   | \
                                         (( (uint32_t)(A) & 0x0000ff00) << 8)   | \
                                       (( (uint32_t)(A) & 0x000000ff) << 24))  
 
#define BigtoLittle64(A)              ((( (uint64_t)(A) & 0xff00000000000000) >> 56) | \
                                       (( (uint64_t)(A) & 0x00ff000000000000) >> 40)   | \
                                       (( (uint64_t)(A) & 0x0000ff0000000000) >> 24)   | \
                                       (( (uint64_t)(A) & 0x000000ff00000000) >> 8) |  \
                                       (( (uint64_t)(A) & 0x00000000ff000000) << 8)  |           \
                                       (( (uint64_t)(A) & 0x0000000000ff0000) << 24)   |         \
                                       (( (uint64_t)(A) & 0x000000000000ff00) << 40)   |         \
                                       (( (uint64_t)(A) & 0x00000000000000ff) << 56))  
 

typedef enum {
  MEMS_SUCCESS				=		0x01,
  MEMS_ERROR				=		0x00	
} status_t;

typedef enum {
  MEMS_ENABLE				=		0x01,
  MEMS_DISABLE				=		0x00	
} State_t;


typedef enum {
  pdPASS				=		0x01,
  pdFAIL				=		0x00	
} BaseType_t;

typedef struct
{
  uint16_t Max_Len;     //最大数据长度
  uint16_t Data_Len;    //当前数据长度
  uint16_t Buffer_State; //Buffer状态
  uint8_t *Data_Buffer; //Buffer缓存区
}USER_BUFFER_Typedef;




typedef enum
{
  IDLE_STATE = 0,
  BUSY_STATE
}USER_BUFFER_STATE;

#define BIT0  0x01
#define BIT1  BIT0<<1
#define BIT2  BIT0<<2
#define BIT3  BIT0<<3
#define BIT4  BIT0<<4
#define BIT5  BIT0<<5
#define BIT6  BIT0<<6
#define BIT7  BIT0<<7


#ifdef __cplusplus
}
#endif



#endif

