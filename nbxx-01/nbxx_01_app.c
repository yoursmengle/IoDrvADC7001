/** 
  ******************************************************************************
  * @文件   nbxx_01_app.c
  * @作者   罗桂发
  * @版本   V1.0.0
  * @日期   2017-05-03 
  * @说明   
  ********  利尔达科技集团股份有限公司  www.lierda.com ***********************            
  *
***/

#include "common.h"

///static uint8_t sever_ip[]={185.,4,11,209};

static uint8_t send_cnt=0;

NB_UE_STATISTICS_T nbiot_ue_statistics; 

/* Buffer used for transmission */
uint8_t aTxBuffer[BUFFSIZE];



Nb_to_sever_package Nb_to_sever_data_package;

uint8_t IMEI_code[16]={0};
uint8_t IMSI_code[16]={0};


 

static void addSendCnt(void);
uint8_t uart_NBxx_01_send(const uint8_t *fmt, uint16_t len);

bool find_imei(uint16_t len);
bool find_imsi(uint16_t len);


//SendStatus send_at_cmd(const char *data,uint16_t len,char *ackdata,uint16_t timeout);

int at_get_words(char *ATcmd,char *srcStr,uint16_t total_len, char *word);
void  hexToAscs(uint8_t hex,char *ascs);
uint16_t HexsToAscs(uint8_t *hexs,char * ascs,uint16_t length);

void setPeriodReportTime(uint16_t Period)  //UNIT:S
{ 
   Sys_parameters_working.report_period=Period;
   set_timer_report_period(Sys_parameters_working.report_period);
}
/**
* 获取AT命令响应后每一个参数值，适用格式： 命令：参数
*
* @author qhq
*
* @param srcStr 指向AT命令响应的内容
* @param word  保存每一个参数值
*              
*
* @return int  返回实际word数
*/
int at_get_words(char *ATcmd,char *srcStr,uint16_t total_len, char *word)
{
  int index = 0;
  uint16_t i = 0,j=0,m=0; 
  char *str = srcStr;
  
  while(i<total_len)
  {
     if(*(str + i)==*(ATcmd+j)) 
     {
        j++;
        if((*(ATcmd+j)=='\0')&&(*(str + i+1)==':'))
        {
           m=i+2;
           while(*(str+m)!='\r')
           {
              word[index]=*(str+m);
              m++;
              index++;
              if(m>=total_len)
              {
                break;
              }
              if(index>=9)
              {
                break;
              }
           }
           word[index]='\0';
           return index;
        }
     }
     else
     {
        j=0; 
     }
     i++;
  }
  return 0;
/*  while (i < total_len)
  {
    if (*(str + i) == chop)
    {
      //strncmp(word[index], str, i);
      word[index] = str;
      word[index++][i] = '\0';
      str = (str + i + 1);
      i = -1;
    }
    
    if (*(str + i) == '\r')
    {
      word[index] = str;
      word[index++][i] = '\0';
      str = (str + i);
      i = 0;
      
      break;
    }
    
    if (index >= size)
    {
      return index;
    }
    
    i++;
  }
  
  if (strlen(str) > 0)
  {
    word[index++] = str;
  }
  
  return index;*/
}
/**
* 获取AT命令响应后每一个参数值，适用格式： 参数，参数，参数，...
*
* @author qhq
*
* @param srcStr 指向AT命令响应的内容
* @param word  保存每一个参数值
* @param size  word的个数
*
* @return int  返回实际word数
*/
int at_get_para(char chop,char *srcStr, char **word, int size)
{
  int index = 0;
  int i = 0;
  char *str = srcStr;
  
  while (*(str + i) != '\0')
  {
    if (*(str + i) == chop)
    { 
      word[index] = str;
      word[index++][i] = '\0';
      str = (str + i + 1);
      i = -1;
    }
    
    else if((*(str + i) == '\r')||(*(str + i) == '\n'))
    {
     // word[index] = str;
     // word[index++][i] = '\0';
     // str = (str + i);
     // i = 0;
      str=(str+i);
      i=0;
     // break;
    }
    if (index >= size)
    {
      return index;
    }
    i++;
  }
  
  if (strlen(str) > 0)
  {
    word[index++] = str;
  }
  
  return index;
}

void initNetWork(void)
{
  Net_type type;
 
  Nb_to_sever_data_package.package.start=BigtoLittle16(0xffaa);
  Nb_to_sever_data_package.package.cmd  =BigtoLittle16(0xd0d0);
  
  init_sys_parameters();
  type=get_net_type();
  if(type ==Net_type_UDP){
    initUdp((uint8_t *)Sys_parameters_working.server_ip  ,atoi(Sys_parameters_working.server_port));  //初始化UDP数据发送的任务
  }
  else if(type==Net_type_TCP)
  {
   // initTCP(sever_ip,port); 
  }
  else if(type==Net_type_COAP)
  {
   // initCoap(); 
  }
  setPeriodReportTime(30);//(Report_Period);//默认定时上报

}



 
void bs_connect(void)
{
 // char temp[64]; 
  uint16_t rty_cnt=0;
  unsigned char i=0; 
 
   log_s("start init NB_IOT \n");
   for(i=0;i<=NB_AT_CGPADDR;)
   { 
     if(i==NB_AT_CSCON1)
     {
       setConnect(Conn_trying);
     }
     send_data_to_nb(i,nbiot_cmd_data[i].cmdstr);
     if(nbiot_cmd_data[i].revresult == BACK_TIMEOUT)
     {
        rty_cnt++;
        if(rty_cnt==nbiot_cmd_data[i].rty_num)
        {
           rty_cnt=0;
           if(i==NB_AT_CGPADDR)
           {
             i=0;
             continue;
           }
           i++;
        }
     }
     else if(nbiot_cmd_data[i].revresult == BACK_TRUE)
     {
        if(i==NB_AT_CGSN)
        {
            if(find_imei(get_nbdata_revlen())==true)
            {
               i++;
               rty_cnt=0;
            }
            else
            {
               rty_cnt++;
               if(rty_cnt==nbiot_cmd_data[i].rty_num)
               {
                  rty_cnt=0;
                  i++;
               }
            }
        }
        else if(i==NB_AT_CIMI)
        {
            if(find_imsi(get_nbdata_revlen())==true)
            {
               i++;
               rty_cnt=0;
            }
            else
            {
               rty_cnt++;
               if(rty_cnt==nbiot_cmd_data[i].rty_num)
               {
                  rty_cnt=0;
                  i++;
               }
            }
        }
     
        else if(i==NB_AT_CGPADDR)
        {
           setConnect(Conn_on);
           rty_cnt=0;
           i++;
        }
        else
        {
          rty_cnt=0;
          i++;
        }
     }
   }
}
void report(void)
{
  if(get_net_type()==Net_type_UDP){     
    report_udp();    
  }else if(get_net_type()==Net_type_TCP){
     ;
  }else if(get_net_type()==Net_type_COAP){
     ;
  }
  
  
  
}
uint8_t get_imei(uint8_t *data)
{
   uint8_t i;
   for(i=0;i<15;i++)
   {
      data[i]=IMEI_code[i];
   }
   return 15;
}

bool find_imei(uint16_t len)
{
      uint8_t j=0,m=0;
      if(len>=15)
      {
         for(j=0;j<len;j++)
         {
           if((aRxBuffer[j]>=0x30)&&(aRxBuffer[j]<=0x39))
           {
              IMEI_code[m]=aRxBuffer[j];
              m++;
              if(m==15)
              {
                return true;
              }
           }
           else
           {
              m=0;
           }
         }
         return false;
      }
      else
      {
        return false;
      }
}
bool find_imsi(uint16_t len)
{
     uint8_t j=0,m=0;
      if(len>=15)
      {
         for(j=0;j<len;j++)
         {
           if((aRxBuffer[j]>=0x30)&&(aRxBuffer[j]<=0x39))
           {
              IMSI_code[m]=aRxBuffer[j];
              m++;
              if(m==15)
              {
                return true;
              }
           }
           else
           {
              m=0;
           }
         }
         return false;
      }
      else
      {
        return false;
      }
}

void updateNbLed(void)
{ 
  Leds_TypeDef led;
  int16_t signal_power=nbiot_ue_statistics.signal_power;
  int16_t sinr_value=nbiot_ue_statistics.snr;
  if(Sys_parameters_working.rsrpthreshold !=0)
  {//如果有设置门限值
    if(signal_power>Sys_parameters_working.rsrpthreshold &&sinr_value>Sys_parameters_working.sinrthreshold )
    {
       led=LED23G;
    }
    else
    {
       led=LED23R;
       printf("signal_power=%d,sinr=%d\r\n",signal_power,sinr_value);
    }
  }
  else
  {
    if(getCoverLevel() ==0)
    {
       led=LED23G;
    }
    else 
    {
       led=LED23R;
    }
  }
  
  if(getNbLed()!=led){
    LED_Off(getNbLed());
    setNBLed(led);
    LED_On(led);
  }
}
uint8_t send_data_to_nb(uint8_t NB_CMD,char *fmt,...)
{
  
  uint8_t back_result;
 // uint16_t timeout;
  char *needfindstr;
  uint8_t *result;
  int len=0;
  va_list ap;
  char *ptr=(char *)aTxBuffer;
  va_start(ap,fmt); 
  len=vsprintf(ptr,fmt,ap);
  va_end(ap); 
   
   // timeout=nbiot_cmd_data[current_NB_cmd].revtimeout;
    needfindstr=nbiot_cmd_data[NB_CMD].cmdtruebackstr;
    result=(uint8_t *)&nbiot_cmd_data[NB_CMD].revresult;
    
    memset(aRxBuffer,0,BUFFSIZE);
    nbiot_cmd_data[NB_CMD].revresult = NO_BACK;
    set_nb_found_result(NB_CMD,needfindstr,result);
   
   sendInnerAtToNB(ptr,len); 
   
   while(NO_BACK == nbiot_cmd_data[NB_CMD].revresult );//此处可替换为低功耗进入
   back_result = nbiot_cmd_data[NB_CMD].revresult;
   return back_result;
}
void send_data_to_server(uint8_t NB_CMD,char *fmt,...)
{ 
 // uint8_t back_result;
 // uint16_t timeout;
  char *needfindstr;
  uint8_t *result;
  int len=0;
  va_list ap;
  char *ptr=(char *)aTxBuffer;
  va_start(ap,fmt); 
  len=vsprintf(ptr,fmt,ap);
  va_end(ap); 
    
    needfindstr=nbiot_cmd_data[NB_CMD].cmdtruebackstr;
    result=(uint8_t *)&nbiot_cmd_data[NB_CMD].revresult;
    
    memset(aRxBuffer,0,BUFFSIZE);
    nbiot_cmd_data[NB_CMD].revresult = NO_BACK;
    set_nb_found_result(NB_CMD,needfindstr,result);
   
    sendInnerAtToNB(ptr,len); 
   
   while(NO_BACK == nbiot_cmd_data[NB_CMD].revresult );//此处可替换为低功耗进入
   //发送成功，等待服务器应答
    memset(aRxBuffer,0,BUFFSIZE);
    needfindstr=nbiot_cmd_data[NB_SEND_DATA_ACK].cmdtruebackstr;
    result=(uint8_t *)&nbiot_cmd_data[NB_SEND_DATA_ACK].revresult;
    nbiot_cmd_data[NB_SEND_DATA_ACK].revresult = NO_BACK;
    set_nb_found_result(NB_SEND_DATA_ACK,needfindstr,result);
 //  back_result = nbiot_cmd_data[NB_CMD].revresult;
 //  return back_result;
}
/*
SendStatus send_at_cmd( char *ackdata,uint16_t *revdatalen,uint16_t timeout,char *fmt,...)
{
 // char temp[64];
  int len=0;
  uint8_t findflag=0;
 // uint16_t rev_length=0;
   *revdatalen=0;
 //  memset(aTxBuffer,0,BUFFSIZE);
  
  va_list ap;
  char *ptr=(char *)aTxBuffer;
  va_start(ap,fmt); 
  len=vsprintf(ptr,fmt,ap);
  va_end(ap); 
  sendInnerAtToNB(ptr,len); 
//  memset(aRxBuffer,0,BUFFSIZE);
   while(timeout>0)
  {
    timeout--;
    HAL_Delay(1);  
    if(nb_rec_buffer.rec_data_finish_flag == DATA_REC_FINISH)
    {
      nb_rec_buffer.rec_data_finish_flag = DATA_REC_NO_FINISH;
      *revdatalen=uart_NBxx_01_read(aRxBuffer);
      if(check_strstr((char *)aRxBuffer,ackdata,*revdatalen)==true)
      {
        findflag=1;
        break;
      }
    }
  }
  if(findflag==1)
     return RESPONSE_SUCCESS;
  else
     return RESPONSE_FAILD;
 
}*/

 
void sendInnerAtToNB(const char *data,uint16_t len)
{
  //每次开始上传数据之前，把接收缓冲区链表清空，指针操作
  clear_chains();
  sendAtToNB(data, len); 
}

uint16_t getRspr(void)
{
   return nbiot_ue_statistics.signal_power;
}
uint16_t getSinr(void)
{
   return nbiot_ue_statistics.snr;
}
uint8_t getCoverLevel(void)
{
  return nbiot_ue_statistics.ecl;
}
void clear_chains(void)
{
  nb_rec_buffer.p_read=nb_rec_buffer.p_write;
  nb_rec_buffer.rec_data_finish_flag = DATA_REC_NO_FINISH;
}

void sendAtToNB(const char *data,uint16_t len)
{
  addSendCnt(); 
  uart_NBxx_01_send((const uint8_t *) data,  len);
}

static void addSendCnt(void)
{
  if(send_cnt++>NO_RETURN_CNT){
  //  log_e("can not connect to NB!!!\r\n");
  }
}

uint8_t uart_NBxx_01_send(const uint8_t *fmt, uint16_t len)
{ 
  log_s("NB_SEND:%s",fmt);
  uart_data_send(&UartHandle_NBxx_01, fmt, len);
  return 1; //lgf0503
}

void  hexToAscs(uint8_t hex,char *ascs)
{
  
  uint8_t h,l;
  h=(hex>>4)&0x0f;
  l=(hex&0x0f);
  
  
  if(h<=9)   //lgf0503  ((h>=0)&&(h<=9))
    ascs[0]=h+0x30;
  else if((h>=10)&&(h<=15)){
    ascs[0]=h+0x41-10;
  }else{
    ascs[0]=0xff;
  }
  
  if(l<=9)   //lgf0503   ((l>=0)&&(l<=9))
    ascs[1]=l+0x30;
  else if((l>=10)&&(l<=15)){
    ascs[1]=l+0x41-10;
  }else{
    ascs[1]=0xff;
  }  
  
  
}
uint16_t HexsToAscs(uint8_t *hexs,char * ascs,uint16_t length)
{
  uint16_t j=0;
  for(uint16_t i=0;i<length;i++){
    hexToAscs(hexs[i],ascs+j);
    j+=2;
  } 
  return j;
}
uint8_t charsToHex(char *asc)
{
  
  uint8_t hex=0;
  if((asc[0]>='0')&&(asc[0]<='9')){
    hex=asc[0]-0x30;
  }
  else if((asc[0]>='a')&&(asc[0]<='f')){
    hex=asc[0]-'a'+0xa;
  }
  else if((asc[0]>='A')&&(asc[0]<='F')){
    hex=asc[0]-'A'+0xa;
  }
  
  hex=hex<<4;
  
  if((asc[1]>='0')&&(asc[1]<='9')){
    hex+=(asc[1]-0x30);
  }
  else if((asc[1]>='a')&&(asc[1]<='f')){
    hex+=(asc[1]-'a'+0xa);
  }
  else if((asc[1]>='A')&&(asc[1]<='F')){
    hex+=(asc[1]-'A'+0xa);
  } 
  
  return hex;
}
uint16_t  ascsToHexs(char *ascs,uint8_t * hexs,uint16_t length)
{
  uint16_t j=0;
  for(uint16_t i=0;i<length;i+=2){
    
    hexs[j++]=charsToHex(ascs+i);
    //hexs[i]=charToHex(ascs[i]);   
  } 
  return j;
}
void querySignal(void)
{ 
  uint16_t rev_len;
  char words[10];
  if(BACK_TRUE==send_data_to_nb(NB_AT_GETSIGNAL,nbiot_cmd_data[NB_AT_GETSIGNAL].cmdstr ))  // 查询网络信道状态
  {
     rev_len=get_nbdata_revlen(); 
     if(at_get_words("Signal power", (char *)aRxBuffer,rev_len, words)>1) 
     {
          nbiot_ue_statistics.signal_power  =atoi(words);//atoi(words[1]);
     }
     if(at_get_words("Total power",(char *) aRxBuffer,rev_len, words)>1)
     {
            nbiot_ue_statistics.total_power=atoi(words);//atoi(words[1]); //!!!!!!!!!!! 
     }
     if(at_get_words("Cell ID", (char *)aRxBuffer,rev_len, words)>1)
     {
           nbiot_ue_statistics.cell_id=atol(words);//atol(words[1]);
     }
     if(at_get_words("ECL",(char *) aRxBuffer,rev_len, words)>1)
     {
           nbiot_ue_statistics.ecl=atoi(words);//atoi(words[1]);
     }
     if(at_get_words("SNR",(char *) aRxBuffer,rev_len, words)>1)
     {
           nbiot_ue_statistics.snr  =atoi(words);//atoi(words[1]);
     }
     if(at_get_words("EARFCN",(char *) aRxBuffer,rev_len, words)>1)
     {
           nbiot_ue_statistics.earfcn  =atoi(words);//atoi(words[1]);
     }
     if(at_get_words("PCI",(char *) aRxBuffer,rev_len, words)>1)
     {
          nbiot_ue_statistics.pci  =atoi(words);//atoi(words[1]);
          updateNbLed();
     }
  }
}

uint8_t checkSum(uint8_t *buf,uint16_t len)
{
   uint8_t result=0;
   uint16_t i;
   for(i=0;i<len;i++)
   {
      result+=buf[i]; 
   }
   return result;
}

