/** 
  ******************************************************************************
  * @�ļ�   App_config.c
  * @����   �޹�
  * @�汾   V1.0.0
  * @����   2017-05-03 
  * @˵��   
  ********  ������Ƽ����Źɷ����޹�˾  www.lierda.com ***********************         
  *
***/

#include "common.h"

static bool  FirstPowerOn=true;
static uint8_t MAX_retry_Num=3;
static uint8_t current_retry_Num=0;
env_parameters Sys_parameters_working;
 

Net_type net_type;
volatile ConnState isConn=Conn_off;


void init_sys_parameters(void)
{
   Sys_parameters_working.sequence_num = 0;
   Sys_parameters_working.crc_checksum = 0;
   Sys_parameters_working.rsrpthreshold = -1000;//��10
   Sys_parameters_working.sinrthreshold = 10;   //��10
   strcpy(Sys_parameters_working.net_type, "UDP");
   strcpy(Sys_parameters_working.server_ip, "54.223.248.94");
   strcpy(Sys_parameters_working.server_port, "9502");
   Sys_parameters_working.report_period=30;
   setPeriodReportTime(Sys_parameters_working.report_period);  //UNIT:S
}

Net_type get_net_type(void)
{
  char *type=Sys_parameters_working.net_type; 
  if(strstr(type, "UDP") != NULL){
    net_type=Net_type_UDP;
  }else  if(strstr(type, "TCP") != NULL){
    net_type=Net_type_TCP;
  }else  if(strstr(type, "COAP") != NULL){
    net_type=Net_type_COAP;
  }else{
    
  }
  return  net_type;
}
void setConnect(ConnState state)
{
  isConn=state;
  if(isConn==Conn_on)
  { 
      LED_On(getNbLed());
  }
  else if(isConn==Conn_trying)
  {
     LED_flash_pro(getNbLed(),1000,1000);  
  }
  else
  {
     LED_flash_pro(getNbLed(),300,300); 
  }
}

ConnState getConnectState(void)
{ 
  return isConn;
}

void updata_sensor(void)
{
   HDC1000_UpdateInfo();
   LIS3DHUpdateInfo();
   READ_MPL3115_Barometer();
   GetLuxValue();
   battery_process();
   updata_to_lierda_server_package();
}

void setMaxRetryCnt(uint8_t rty_max_num)
{
    MAX_retry_Num=rty_max_num;
}

void ClearCurrent_rty_num(void)
{
   current_retry_Num=0;
}
uint8_t getCurrent_rty_num(void)
{
   return current_retry_Num;
}
uint8_t getMax_rty_num(void)
{
   return MAX_retry_Num; 
}
void current_rty_num_add_1(void)
{
   current_retry_Num++;  
}


bool isFirstPowerOn(void)
{
   return FirstPowerOn;
}

void set_FirstPowerOn_flag(void)
{
  FirstPowerOn=true;
}
void clearFirstPowerOn_flag(void)
{
  FirstPowerOn=false;
}




