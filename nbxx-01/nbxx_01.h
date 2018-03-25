/** 
  ******************************************************************************
  * @文件   bsp_nbxx_01.h
  * @作者   罗桂发
  * @版本   V1.0.0
  * @日期   2017-05-03 
  * @说明   
  ********  利尔达科技集团股份有限公司  www.lierda.com ***********************           
  *
***/

#ifndef __BSP_NBXX_01_H
#define __BSP_NBXX_01_H

#ifdef __cplusplus
 extern "C" {
#endif

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

#define DATA_REC_NO_FINISH  0
#define DATA_REC_IS_ING     1
#define DATA_REC_FINISH     2

   
   
   
   
#define NB_AT_CFUN0    0
#define NB_AT_CGSN     1
#define NB_AT_NRB      2 
#define NB_AT_CFUN1    3     
#define NB_AT_CIMI     4
#define NB_AT_CMEE     5
#define NB_AT_CGDCONT  6  
#define NB_AT_NNMI     7
#define NB_AT_CGATT    8
#define NB_AT_CSCON1   9
#define NB_AT_CGPADDR  10
#define NB_AT_GETSIGNAL 11
#define NB_AT_NSOCL    12
#define NB_AT_NSOCR    13
#define NB_SEND_DATA   14
#define NB_SEND_DATA_ACK 15
#define NB_AT_NSORF    16
    
/*
typedef enum
{
  NO_BACK=0,
  BACK_TIMEOUT,
  BACK_TRUE,
}NB_back_result; 
*/
#define NO_BACK  0x00
#define BACK_TIMEOUT  0x01
#define BACK_TRUE  0x02

#define NB_back_result  uint8_t
  
   
   
   
#pragma  pack(push)  //保存对齐状态  
#pragma  pack(1) 
typedef struct{
  char *cmdstr;
  uint16_t revtimeout;
  char *cmdtruebackstr;
  NB_back_result  revresult;
  uint8_t rty_num;
}NBIOT_CMD_Data_t;    
   
#pragma  pack(1)    
typedef struct {
  char rec_buffer[BUFFSIZE*3];
  char *p_read;
  char *p_write;
  uint8_t rec_data_finish_flag;
  uint16_t max_len;
}Nb_rec_buffer;


#pragma pack(pop)



extern Nb_rec_buffer nb_rec_buffer;

extern uint8_t aRxBuffer[];

extern volatile NBIOT_CMD_Data_t nbiot_cmd_data[];

uint8_t get_NB_RF_DATA_NUM(void);
void set_NB_RF_DATA_NUM_down_1(void);
void initNbRecBuffer(void);
bool check_strstr(char *data1,char *data2,uint16_t len);
uint8_t get_current_NBcmdnum(void);
void set_nb_found_result(uint8_t cmdnum,char *findstr,NB_back_result *result);
void NBIOT_data_reveive(void);
void nb_rev_timeout_process(void);
uint16_t get_nbdata_revlen(void);
void bs_connect(void);

#ifdef __cplusplus
}
#endif


#endif

