
//串口相关的头文件  
#include "common.h"
#include "nbxx_01.h"



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

void bs_connect(void)
{
 // char temp[64]; 
  uint16_t rty_cnt=0;
  unsigned char i=0; 
 
   printf("start init NB_IOT \n");
   for(i=0;i<=NB_AT_CGPADDR;)
   { 
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
