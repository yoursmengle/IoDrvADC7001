/** 
  ******************************************************************************
  * @文件   bsp_nbxx_01.c
  * @作者   罗桂发
  * @版本   V1.0.0
  * @日期   2017-05-03 
  * @说明   
  ********  利尔达科技集团股份有限公司  www.lierda.com ***********************           
  *
***/


#include "bsp_config.h"

  
static uint16_t foundstr_timeout=0;
static char *foundstr;
static uint8_t *foundresult;
static uint16_t revlen=0; 
static uint8_t current_NB_cmd=NB_AT_CFUN0;
static uint8_t NB_RF_DATA_NUM=0;

uint8_t aRxBuffer[BUFFSIZE];

Nb_rec_buffer nb_rec_buffer={
  {0},
  NULL,
  NULL,
  DATA_REC_NO_FINISH,
  BUFFSIZE*3
};

volatile NBIOT_CMD_Data_t nbiot_cmd_data[20]=
{
//cmdstr,    revtimeout(s),   cmdtruebackstr,   revresult
  {"AT+CFUN=0\r\n",  5,       "OK" ,NO_BACK,1},           
  {"AT+CGSN=1\r\n",  2,       "OK" ,NO_BACK,3}, 
  {"AT+NRB\r\n",     10,      "OK" ,NO_BACK,1}, 
  {"AT+CFUN=1\r\n",  6,      "OK" ,NO_BACK,3}, 
  {"AT+CIMI\r\n",    2,        "OK" ,NO_BACK,3}, 
  {"AT+CMEE=1\r\n",  2,        "OK" ,NO_BACK,1}, 
  {"AT+CGDCONT=1,\"IP\",\"ctnet\"\r\n",  2,        "OK" ,NO_BACK,1}, 
  {"AT+NNMI=1\r\n",  2,        "OK" ,NO_BACK,1}, 
  {"AT+CGATT=1\r\n",  2,        "OK" ,NO_BACK,1}, 
  {"AT+CSCON=1\r\n",  20,        "+CSCON:1" ,NO_BACK,1}, 
  {"AT+CGPADDR=1\r\n", 3,        "+CGPADDR:1," ,NO_BACK,60}, 
  {"AT+NUESTATS\r\n" ,  2,        "OK" ,NO_BACK,1},
  {"CMDSTR_NOUSE",  2,        "OK" ,NO_BACK,1}, 
 // {"AT+NSOCL=1",  2,        "OK" ,NO_BACK,1}, 
   
  {"CMDSTR_NOUSE",  2,         "OK" ,NO_BACK,1}, //AT+NSOCR  CMD
  {"CMDSTR_NOUSE",  5,        "OK" ,NO_BACK,1},//NB_SEND_DATA  CMD
  {"CMDSTR_NOUSE",  8,       "NSONMI" ,NO_BACK,1},//NB_SEND_DATA with ack  CMD
  {"CMDSTR_NOUSE",  10,       "OK" ,NO_BACK,1},//REV_NB_DATA CMD  NB_AT_NSORF
};

uint8_t get_current_NBcmdnum(void)
{
  return current_NB_cmd;
}
void set_NB_RF_DATA_NUM_down_1(void)
{
   if(get_NB_RF_DATA_NUM())
   {
      NB_RF_DATA_NUM--;
   }
}
uint8_t get_NB_RF_DATA_NUM(void)
{
  return NB_RF_DATA_NUM;
}
void initNbRecBuffer(void){
  nb_rec_buffer.rec_data_finish_flag =DATA_REC_NO_FINISH;
  nb_rec_buffer.p_read=nb_rec_buffer.rec_buffer;
  nb_rec_buffer.p_write=nb_rec_buffer.rec_buffer;
}
bool check_strstr(char *data1,char *data2,uint16_t len)
{
   uint16_t i=0;
   char *p;
   p=data2;
   do
   {
      if(*data1==*p)
      { 
         p++;
         if(*p=='\0')
         {
            return true;
         }
         
      }
      else
      { 
        p=data2;
      }
      data1++;
      if(*data1=='\0')
      {
         return false;
      }
      i++;
   }while(i<len);
   return false;
}
void set_nb_found_result(uint8_t cmdnum,char *findstr,NB_back_result *result)
{
   current_NB_cmd=cmdnum;
   foundstr_timeout=nbiot_cmd_data[cmdnum].revtimeout  ;
   set_timer_nb_ack_timeout(foundstr_timeout);
   foundstr=findstr;
   foundresult=result;
}
void NBIOT_data_reveive(void)
{ 
   revlen=uart_NBxx_01_read(aRxBuffer);
   if(check_strstr((char *)aRxBuffer,foundstr,revlen)==true)
   {
      *foundresult=BACK_TRUE;
      hal_DISABLE_TIMER(&TimHandle_NB_REV_TIMEOUT);
   }
   if(check_strstr((char *)aRxBuffer,"NSONMI",revlen)==true) //如果NB接收到服务器数据，通知主循环读出
   {
      if((current_NB_cmd==NB_SEND_DATA_ACK)&&(*foundresult==NO_BACK))//如果当前正在等待接收服务器数据
      {
        *foundresult=NO_BACK; // 仅起通知作用 
        hal_DISABLE_TIMER(&TimHandle_NB_REV_TIMEOUT);
      }
      NB_RF_DATA_NUM++;  
   }
   
}
void nb_rev_timeout_process(void)
{
   *foundresult = BACK_TIMEOUT;
}
uint16_t get_nbdata_revlen(void)
{
   return revlen;
}


















