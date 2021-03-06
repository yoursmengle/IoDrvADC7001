   
//串口相关的头文件  
#include "common.h"
#include "nbxx_01.h"

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

uint16_t  uart_NBxx_01_read(uint8_t *fmt)
{
  char *p=nb_rec_buffer.p_read;
  char *m=nb_rec_buffer.p_write;
  bool complete=false;
  uint16_t i=0;
  if(p<m){
    while(p<m){
      *(fmt+i)=*p;
      
     /* if(*p=='\n'){
        p++;
        i++;
        complete=true;
        break;
      }*/
      p++;
      i++;
      if(i>=BUFFSIZE){ //缓存满
        break;
      }
      
    }
    complete=true;
  }
  else if(p>m){//写指针回去了
    while(p<nb_rec_buffer.rec_buffer+nb_rec_buffer.max_len){
      *(fmt+i)=*(p);
      
     /* if(*p=='\n'){
        p++;
        i++;
        complete=true;
        break;
      }*/
      p++;
      i++;
      if(i>=BUFFSIZE){ //缓存满
        break;
      }
      
    }
    if(complete==false&&i<BUFFSIZE){//读指针回头
      p=nb_rec_buffer.rec_buffer;
      while(i<BUFFSIZE){
        //  i++; //这里可能导致问题

        *(fmt+i)=*(p);
        
        /*if(*p=='\n'){
          p++;
          i++;
          complete=true;
          break;
        }*/
        p++;
        i++;
        if(p==m)
        {
          complete=true;
          break;
        }
      }
    }
  }
  if(complete){
    nb_rec_buffer.p_read=p;
    //log_s("NB_REC:%s",fmt);
    return i;
  }
  return 0;
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


void NBIOT_data_receive(void)
{ 
   revlen=uart_NBxx_01_read(aRxBuffer);
   if(check_strstr((char *)aRxBuffer,foundstr,revlen)==true)
   {
      *foundresult=BACK_TRUE;
      //hal_DISABLE_TIMER(&TimHandle_NB_REV_TIMEOUT);
   }
   if(check_strstr((char *)aRxBuffer,"NSONMI",revlen)==true) //如果NB接收到服务器数据，通知主循环读出
   {
      if((current_NB_cmd==NB_SEND_DATA_ACK)&&(*foundresult==NO_BACK))//如果当前正在等待接收服务器数据
      {
        *foundresult=NO_BACK; // 仅起通知作用 
        //hal_DISABLE_TIMER(&TimHandle_NB_REV_TIMEOUT);
      }
      NB_RF_DATA_NUM++;  
   }
   
}


int export_port(unsigned int port_num)
{
	char cmd[80];
      char file[80]; //= "/sys/class/gpio/gpio111/value";  
      sprintf(file, "/sys/class/gpio/gpio%d/value",port_num);
 
      int file_ok = access(file, F_OK);
      if(file_ok != -1) {
          printf("the port has exported!\n");
          return -1;
        }
	sprintf(cmd, "echo %d > /sys/class/gpio/export \n",port_num);
	FILE *fp = popen(cmd, "r");
	pclose(fp);
	return 0;
}

int output_high(unsigned int port_num)
{
	char cmd[80];
	sprintf(cmd, "echo out > /sys/class/gpio/gpio%d/direction \n", port_num);
	FILE *fp = popen(cmd, "r");
	pclose(fp);

	sprintf(cmd, "echo 1 > /sys/class/gpio/gpio%d/value \n", port_num);
	fp = popen(cmd, "r");
	pclose(fp);
	return 0;
}

int output_low(unsigned int port_num)
{
	char cmd[80];
	sprintf(cmd, "echo out > /sys/class/gpio/gpio%d/direction \n", port_num);
	FILE *fp = popen(cmd, "r");
	pclose(fp);

	sprintf(cmd, "echo 0 > /sys/class/gpio/gpio%d/value \n", port_num);
	fp = popen(cmd, "r");
	pclose(fp);
	return 0;
}

#define PORT_ENA_NB05  111
void enable_nb05(void)
{
    export_port(PORT_ENA_NB05);
    output_high(PORT_ENA_NB05);
    printf("Set nb05_01 power ON.\n");
}

#define PORT_RST_NB05  112
void reset_nb05(void)
{
    export_port(PORT_RST_NB05);
    output_high(PORT_RST_NB05);
    for(int i=0;i<20000;i++);
    output_low(PORT_RST_NB05);
    printf("nb05_01 has been reseted!\n");
}

void disable_nb05(void)
{
    export_port(PORT_ENA_NB05);
    output_low(PORT_ENA_NB05);
    printf("Set nb05_01 power Off.\n");
}

/*   
//宏定义  
#define FALSE  -1  
#define TRUE   0  
*/
 
/******************************************************************* 
* 名称：                  open_uart 
* 功能：                打开串口并返回串口设备文件描述 
* 入口参数：             port :串口号(ttyS0,ttyS1,ttyS2) 
* 出口参数：          fd    :串口文件描述符
*******************************************************************/  
int open_uart(char* port)  
{  
    int fd = open( port, O_RDWR);    //|O_NOCTTY|O_NDELAY
    if (FALSE == fd) {  
        printf("Can't Open Serial Port:%s", port);  
        return(FALSE);  
      }  
               
    printf("%s is ready: fd= %d\n",port,fd);  
    return fd;  
}  

void uart_noblock(int fd)
{
    int flags = fcntl(fd,F_GETFL,0);
    flags |= O_NONBLOCK;
    fcntl(fd,F_SETFL,flags);
}

void uart_block(int fd)
{
    int flags = fcntl(fd,F_GETFL,0);
    flags &= ~O_NONBLOCK;
    fcntl(fd,F_SETFL,flags);  
}
/******************************************************************* 
* 名称：                set_uart 
* 功能：                设置串口数据位，停止位和效验位 
* 入口参数：        fd        串口文件描述符 
*                              speed     串口速度 
*                              flow_ctrl   数据流控制 
*                           databits   数据位   取值为 7 或者8 
*                           stopbits   停止位   取值为 1 或者2 
*                           parity     效验类型 取值为N,E,O,,S 
*出口参数：          正确返回为1，错误返回为0 
*******************************************************************/  
int set_uart(int fd,int speed,int flow_ctrl,int databits,int stopbits,int parity)  
{  
     
     int   i;  
     int   status;  
     int   speed_arr[] = { B115200, B19200, B9600, B4800, B2400, B1200, B300};  
     int   name_arr[] = {115200,  19200,  9600,  4800,  2400,  1200,  300};  
           
    struct termios options;  
     
    /*tcgetattr(fd,&options)得到与fd指向对象的相关参数，并将它们保存于options,该函数还可以测试配置是否正确，该串口是否可用等。若调用成功，函数返回值为0，若调用失败，函数返回值为1. 
    */  
    if  ( tcgetattr( fd,&options)  !=  0) {  
          perror("SetupSerial 1");      
          return(FALSE);   
     }  
    
    //设置串口输入波特率和输出波特率  
    for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)  {  
        if(speed == name_arr[i]) {               
            cfsetispeed(&options, speed_arr[i]);   
            cfsetospeed(&options, speed_arr[i]);    
            printf("set baudrate to: %d\n", speed);
          }  
     }       
     
    //修改控制模式，保证程序不会占用串口  
    options.c_cflag |= CLOCAL;  
    //修改控制模式，使得能够从串口中读取输入数据  
    options.c_cflag |= CREAD;  
    
    //设置数据流控制  
    switch(flow_ctrl) {  
    case 0 ://不使用流控制  
              options.c_cflag &= ~CRTSCTS;  
              printf("no flow ctrl\n");
              break;     
        
    case 1 ://使用硬件流控制  
              options.c_cflag |= CRTSCTS;  
              printf("hardware flow ctrl\n");
              break;  
    case 2 ://使用软件流控制  
              options.c_cflag |= IXON | IXOFF | IXANY;  
              printf("software flow ctrl\n");
              break;  
     default:
            break;
    }  
    //设置数据位  
    //屏蔽其他标志位  
    options.c_cflag &= ~CSIZE;  
    switch (databits)  {    
    case 5    :  
           options.c_cflag |= CS5;  
           break;  
    case 6    :  
           options.c_cflag |= CS6;  
           break;  
    case 7    :      
           options.c_cflag |= CS7;  
           break;  
    case 8:      
           options.c_cflag |= CS8;  
           break;    
    default:     
           fprintf(stderr,"Unsupported data size\n");  
           return (FALSE);   
    }  
    printf("set databits to: %d\n",databits);

    //设置校验位  
    switch (parity)  {    
    case 'n':  
    case 'N': //无奇偶校验位。  
                 options.c_cflag &= ~PARENB;   
                 options.c_iflag &= ~INPCK;   
                 printf("No parity\n");   
                 break;   
    case 'o':    
    case 'O'://设置为奇校验      
                 options.c_cflag |= (PARODD | PARENB);   
                 options.c_iflag |= INPCK;       
                 printf("odd parity\n");           
                 break;   
    case 'e':   
    case 'E'://设置为偶校验    
                 options.c_cflag |= PARENB;         
                 options.c_cflag &= ~PARODD;         
                 options.c_iflag |= INPCK;      
                 printf("even parity\n");     
                 break;  
    case 's':  
    case 'S': //设置为空格   
                 options.c_cflag &= ~PARENB;  
                 options.c_cflag &= ~CSTOPB; 
                 printf("set with space \n");    
                 break;   
    default:    
                 fprintf(stderr,"Unsupported parity\n");      
                 return (FALSE);   
    }   
    // 设置停止位   
    switch (stopbits)  {    
    case 1:     
           options.c_cflag &= ~CSTOPB; 
           printf("stopbits = 1\n");   
           break;   
    case 2:     
           options.c_cflag |= CSTOPB;
           printf("stopbits = 2\n");
           break;  
    default:     
           fprintf(stderr,"Unsupported stop bits\n");   
           return (FALSE);  
    }  

     /*
  //修改输出模式，原始数据输出  
  options.c_oflag &= ~OPOST;  
    
  options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);//我加的  
//options.c_lflag &= ~(ISIG | ICANON);  
     
    //设置等待时间和最小接收字符  
    options.c_cc[VTIME] = 1; // 读取一个字符等待1*(1/10)s     
    options.c_cc[VMIN] = 1; // 读取字符的最少个数为1   
     
    //如果发生数据溢出，接收数据，但是不再读取 刷新收到的数据但是不读  
    tcflush(fd,TCIFLUSH);  
     */

    //激活配置 (将修改后的termios数据设置到串口中）  
    if (tcsetattr(fd,TCSANOW,&options) != 0)  {  
         perror("com set error!\n");    
         return (FALSE);   
     }  

    printf("set port OK!\n");
    return (TRUE);   
}  
   
/* Detect the press of keyboard
*/
static __inline  
int kbhit(void)  
{  
                    
        fd_set rfds;  
        struct timeval tv;  
        int retval;  
  
        /* Watch stdin (fd 0) to see when it has input. */  
        FD_ZERO(&rfds);  
        FD_SET(0, &rfds);  
        /* Wait up to five seconds. */  
        tv.tv_sec  = 0;  
        tv.tv_usec = 0;  
  
        retval = select(1, &rfds, NULL, NULL, &tv);  
        /* Don't rely on the value of tv now! */  
  
        if (retval == -1) {  
                perror("select()");  
                return 0;  
        } else if (retval)  
                return 1;  
        /* FD_ISSET(0, &rfds) will be true. */  
        else  
                return 0;  
        return 0;  
}  
   
/*uasge: testuart /dev/ttyOx
 * print chars from the port ttySx on terminal, and send chars which user type in terminal to the port
*/   
int main(int argc, char **argv)  
{  
    int fd;                            //文件描述符  
    int err;                           //返回调用函数的状态  
    int len;                          
    int i;  
    char rcv_buf[100];    
    char uart_dev[20] = "/dev/ttyO1";     
    char kb_buf[20]="AT+NRB\r\n";
    int speed = 9600;
    printf("Usage: %s [dev_name/default:/dev/ttyO1] [baud_rate/default:9600]\n", argv[0]);

    if(argc >1) {  
         strcpy(uart_dev, argv[1]);         
     }  

    if(argc >2) {  
         speed = atoi(argv[2]);         
     }

    printf("Using uart port: %s\n", uart_dev);

    fd = open_uart(uart_dev); //打开串口，返回文件描述符  
    if(fd == FALSE) {
        printf("Failed to open uart port: %s \n", uart_dev);
        return FALSE;
    }
   
    int ret = set_uart(fd,speed,0,8,1,'N');  
    if(FALSE == ret) return FALSE;

    enable_nb05();
    reset_nb05();

    strcpy(kb_buf,"AT+CFUN=0\r\n");
    len = write(fd, kb_buf, strlen(kb_buf));
    printf("write %d bytes to %s \n", len, uart_dev);


    for(i=0; i<100000; i++);
    uart_noblock(fd);

    for(i=0; i< 1000; i++) {
	  len = read(fd,rcv_buf,99);  
        if(len != -1)
	    printf("rec %d bytes from %s \n", len, uart_dev);

	  if(len > 0) {
	    printf(rcv_buf);
	  }
    }
     
    //bs_connect();

    while (1){
       uart_noblock(fd);
       len = read(fd,rcv_buf,99);  
       if(len != -1)
	    printf("rec %d bytes from %s \n", len, uart_dev);
       if(len > 0) {
           printf("received data: %s\n",rcv_buf);
         }

       strcpy(kb_buf, "at+cgmr\r\n");

       for(i=0; i<100000; i++);
       len = write(fd, kb_buf, strlen(kb_buf));
       //printf("write %d bytes to %s \n", len, uart_dev);
       for(i=0; i<1000000; i++);
/*
       if(kbhit()) {
            kb_buf[0]=getchar(); 
            kb_buf[1] = 0;  
            //printf(kb_buf);
            uart_block(fd);
            write(fd,kb_buf,1);
        }         
*/
    }    

}  
