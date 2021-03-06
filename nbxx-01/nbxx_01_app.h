/** 
  ******************************************************************************
  * @文件   nbxx_01_app.h
  * @作者   罗桂发
  * @版本   V1.0.0
  * @日期   2017-05-03 
  * @说明   bsp头文件
  ********  利尔达科技集团股份有限公司  www.lierda.com ***********************           
  *
***/
#ifndef __NBXX_01_APP_H
#define __NBXX_01_APP_H

#include "common.h"

#ifdef __cplusplus
 extern "C" {
#endif
   

#define  OPENLAB   1
   
//直送
  
#define INIT_TRY_CNT            60
#define NO_RETURN_CNT           20
//#define NB_INIT_SEND_GAP        1000
   
typedef enum
{
  RESPONSE_FAILD = 0,
  RESPONSE_SUCCESS = !RESPONSE_FAILD
} SendStatus,RevStatus;   
   
//#define RevStatus SendStatus;
 
#pragma  pack(push)  //保存对齐状态  
 
#pragma  pack(1) 
typedef struct{
  uint16_t len;
  char data[BUFFSIZE];
}NB_Raw_Data;  

#pragma  pack(1) 
typedef union
{
 uint8_t package_data[49];
 struct 
 { 
  uint16_t start; 
  uint16_t cmd;  
  uint8_t version;//00:period data;01:one key test;02:wdt
  uint16_t  len; //package len
  uint8_t device_sn_len; //
  uint8_t device_sn[15]; // 设备编号是可变长度
  uint32_t mesg_send_num;
  uint32_t mesg_acked_num;
  uint64_t unix_time;
  int16_t RSPR;
  int16_t SINR;
  uint8_t cover_level;
  uint16_t repat_num;
  uint8_t  flag;
  //--------------------填充数据-----------------------------
  uint16_t ap_data_len; //填充数据长度
 
 }package;  
}Nb_to_sever_package;

typedef struct{
  int16_t signal_power;
  int16_t total_power ;
  int16_t tx_power;
  uint32_t tx_time;
  uint32_t rx_time;
  uint32_t cell_id;
  uint8_t dl_mcs;
  uint8_t ul_mcs;
  uint8_t dci_mcs;
  uint8_t ecl;
  int16_t snr;
  uint16_t earfcn;
  uint16_t pci;
}NB_UE_STATISTICS_T;   
  
#pragma pack(pop)

extern NB_UE_STATISTICS_T nbiot_ue_statistics; 

extern uint8_t aTxBuffer[];
extern uint8_t aRxBuffer[];
 
void setPeriodReportTime(uint16_t Period);
void initNetWork(void);   
void report(void);
  
void bs_connect(void);   
void sendInnerAtToNB(const char *data,uint16_t len);
void clear_chains(void);
void senAtToNB(const char *data,uint16_t len);
void updateNbLed(void);
void  hexToAscs(uint8_t hex,char *ascs);
uint16_t  ascsToHexs(char *ascs,uint8_t * hexs,uint16_t length);
uint8_t charsToHex(char *asc);
uint16_t HexsToAscs(uint8_t *hexs,char * ascs,uint16_t length);
void querySignal(void);
uint16_t getRspr(void);
uint16_t getSinr(void);
uint8_t getCoverLevel(void);
uint8_t checkSum(uint8_t *buf,uint16_t len);
uint8_t get_imei(uint8_t *data);
int at_get_para(char chop,char *srcStr, char **word, int size);
uint8_t send_data_to_nb(uint8_t NB_CMD,char *fmt,...);

void send_data_to_server(uint8_t NB_CMD,char *fmt,...);
#ifdef __cplusplus
 }
#endif
  
   
   
#endif   
   
