/** 
  ******************************************************************************
  * @�ļ�   App_config.h
  * @����   �޹�
  * @�汾   V1.0.0
  * @����   2017-05-03 
  * @˵��    �ļ�
  ********  ������Ƽ����Źɷ����޹�˾  www.lierda.com ***********************           
  *
***/
#ifndef __APP_CONFIG_H
#define __APP_CONFIG_H


#ifdef __cplusplus
 extern "C" {
#endif


typedef enum{
  Conn_off=0,
  Conn_trying=1,
  Conn_on=2,
}ConnState;   



typedef enum {
  Net_type_UDP,
  Net_type_TCP,
  Net_type_COAP
}Net_type;

/**
 * ���ñ�ṹ��
 */
#define ENV_PARAM_USED_SIZE        (4+1+1+8+1+4 + 118)
typedef struct env_parameters
{
    /**
     * ���������кţ����������ram�У��˲������ᱻ�õ�������flash��    
     * �˲��������˴˲����������µĲ������ñ��˱���Խ�󣬲���Խ��
     *
     */
    uint32_t sequence_num;  // 4
 
    uint8_t crc_checksum; // 1
 
     /********* ����Ϊ����ʱ���������  **********************/
    char   net_type[5]; // ͨ��Э�� UDP/TCP/CoAP
    char   server_ip[16+1];   // ��������ַ
    char   server_port[6];  // �������˿ں�
     
    int16_t rsrpthreshold;
    int16_t sinrthreshold;
    
    uint32_t report_period;  //��ʱ�ϱ����ڣ��룩
}env_parameters;

#if !defined(ENV_SIZE)
#define ENV_SIZE                     (sizeof(env_parameters))
#endif










 
extern volatile ConnState isConn;
extern  env_parameters Sys_parameters_working;

void init_sys_parameters(void);
Net_type get_net_type(void);
void setConnect(ConnState state);
ConnState getConnectState(void);
void updata_sensor(void);

void setMaxRetryCnt(uint8_t rty_max_num);
void ClearCurrent_rty_num(void);
uint8_t getCurrent_rty_num(void);
uint8_t getMax_rty_num(void);
void current_rty_num_add_1(void);

bool isFirstPowerOn(void);
void set_FirstPowerOn_flag(void);
void clearFirstPowerOn_flag(void);






#ifdef __cplusplus
 }
#endif

#endif


