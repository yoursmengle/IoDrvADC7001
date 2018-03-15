   
//串口相关的头文件  
#include<stdio.h>      /*标准输入输出定义*/  
#include<stdlib.h>     /*标准函数库定义*/  
#include<unistd.h>     /*Unix 标准函数定义*/  
#include<sys/types.h>   
#include<sys/stat.h>     
#include<fcntl.h>      /*文件控制定义*/  
#include<termios.h>    /*PPSIX 终端控制定义*/  
#include<errno.h>      /*错误号定义*/  
#include<string.h>  
#include <sys/time.h>  

   
//宏定义  
#define FALSE  -1  
#define TRUE   0  
   
/******************************************************************* 
* 名称：                  open_uart 
* 功能：                打开串口并返回串口设备文件描述 
* 入口参数：             port :串口号(ttyS0,ttyS1,ttyS2) 
* 出口参数：          fd    :串口文件描述符
*******************************************************************/  
int open_uart(char* port)  
{  
    int fd = open( port, O_RDWR|O_NOCTTY|O_NDELAY);  
    if (FALSE == fd) {  
        printf("Can't Open Serial Port:%s", port);  
        return(FALSE);  
      }  
     //恢复串口为阻塞状态                                 
    if(fcntl(fd, F_SETFL, 0) < 0) {  
        printf("fcntl failed!\n");  
        return(FALSE);  
    } else {  
        printf("fcntl=%d\n",fcntl(fd, F_SETFL,0));  
     }  
     //测试是否为终端设备      
    if(0 == isatty(STDIN_FILENO)) {  
        printf("standard input is not a terminal device\n");  
        return(FALSE);  
    } else {  
        printf("isatty success!\n");  
     }                
    printf("fd->open=%d\n",fd);  
    return fd;  
}  
/******************************************************************* 
* 名称：                close_uart 
* 功能：                关闭串口
* 入口参数：        fd    :文件描述符     
* 出口参数：        void 
*******************************************************************/  
   
void close_uart(int fd)  
{  
    close(fd);  
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
        if(speed == name_arr[i])  {               
            cfsetispeed(&options, speed_arr[i]);   
            cfsetospeed(&options, speed_arr[i]);    
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
              break;     
        
    case 1 ://使用硬件流控制  
              options.c_cflag |= CRTSCTS;  
              break;  
    case 2 ://使用软件流控制  
              options.c_cflag |= IXON | IXOFF | IXANY;  
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
    //设置校验位  
    switch (parity)  {    
    case 'n':  
    case 'N': //无奇偶校验位。  
                 options.c_cflag &= ~PARENB;   
                 options.c_iflag &= ~INPCK;      
                 break;   
    case 'o':    
    case 'O'://设置为奇校验      
                 options.c_cflag |= (PARODD | PARENB);   
                 options.c_iflag |= INPCK;               
                 break;   
    case 'e':   
    case 'E'://设置为偶校验    
                 options.c_cflag |= PARENB;         
                 options.c_cflag &= ~PARODD;         
                 options.c_iflag |= INPCK;        
                 break;  
    case 's':  
    case 'S': //设置为空格   
                 options.c_cflag &= ~PARENB;  
                 options.c_cflag &= ~CSTOPB;  
                 break;   
    default:    
                 fprintf(stderr,"Unsupported parity\n");      
                 return (FALSE);   
    }   
    // 设置停止位   
    switch (stopbits)  {    
    case 1:     
           options.c_cflag &= ~CSTOPB; 
           break;   
    case 2:     
           options.c_cflag |= CSTOPB; 
           break;  
    default:     
           fprintf(stderr,"Unsupported stop bits\n");   
           return (FALSE);  
    }  
     
  //修改输出模式，原始数据输出  
  options.c_oflag &= ~OPOST;  
    
  options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);//我加的  
//options.c_lflag &= ~(ISIG | ICANON);  
     
    //设置等待时间和最小接收字符  
    options.c_cc[VTIME] = 1; /* 读取一个字符等待1*(1/10)s */    
    options.c_cc[VMIN] = 1; /* 读取字符的最少个数为1 */  
     
    //如果发生数据溢出，接收数据，但是不再读取 刷新收到的数据但是不读  
    tcflush(fd,TCIFLUSH);  
     
    //激活配置 (将修改后的termios数据设置到串口中）  
    if (tcsetattr(fd,TCSANOW,&options) != 0)  {  
         perror("com set error!\n");    
         return (FALSE);   
     }  
    return (TRUE);   
}  
/******************************************************************* 
* 名称：                init_uart() 
* 功能：                串口初始化 
* 入口参数：        fd       :  文件描述符    
*               speed  :  串口速度 
*               flow_ctrl  数据流控制 
*               databits   数据位   取值为 7 或者8 
*                           stopbits   停止位   取值为 1 或者2 
*                           parity     效验类型 取值为N,E,O,,S 
*                       
* 出口参数：        正确返回为1，错误返回为0 
*******************************************************************/  
int init_uart(int fd, int speed,int flow_ctrl,int databits,int stopbits,int parity)  
{  
    int err;  
    //设置串口数据帧格式  
    if (set_uart(fd,19200,0,8,1,'N') == FALSE) {                                                           
        return FALSE;  
    }  else  {  
       return  TRUE;  
     }  
}  
   
/******************************************************************* 
* 名称：                  recv_uart 
* 功能：                接收串口数据 
* 入口参数：        fd                  :文件描述符     
*                              rcv_buf     :接收串口中数据存入rcv_buf缓冲区中 
*                              data_len    :一帧数据的长度 
* 出口参数：        正确返回为1，错误返回为0 
*******************************************************************/  
int recv_uart(int fd, char *rcv_buf,int data_len)  
{  
    int len,fs_sel;  
    fd_set fs_read;  
     
    struct timeval time;  
     
    FD_ZERO(&fs_read);  
    FD_SET(fd,&fs_read);  
     
    time.tv_sec = 10;  
    time.tv_usec = 0;  
     
    //使用select实现串口的多路通信  
    fs_sel = select(fd+1,&fs_read,NULL,NULL,&time);  
    if(fs_sel)  {  
       len = read(fd,rcv_buf,data_len);  
       printf("I am right!(version1.2) len = %d fs_sel = %d\n",len,fs_sel);  
       return len;  
    }  else  {  
       printf("Sorry,I am wrong!");  
       return FALSE;  
     }       
}  
/******************************************************************** 
* 名称：                  send_uart 
* 功能：                发送数据 
* 入口参数：        fd                  :文件描述符     
*                              send_buf    :存放串口发送数据 
*                              data_len    :一帧数据的个数 
* 出口参数：        正确返回为1，错误返回为0 
*******************************************************************/  
int send_uart(int fd, char *send_buf,int data_len)  
{  
    int len = 0;  
     
    len = write(fd,send_buf,data_len);  
    if (len == data_len )  {  
       return len;  
    } else{  
       tcflush(fd,TCOFLUSH);  
       return FALSE;  
     }  
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

   
/*uasge: testuart /dev/ttySx
 * print chars from the port ttySx on terminal, and send chars which user type in terminal to the port
*/   
int main(int argc, char **argv)  
{  
    int fd;                            //文件描述符  
    int err;                           //返回调用函数的状态  
    int len;                          
    int i;  
    char rcv_buf[100];    
    char uart_dev[20] = "/dev/ttyS0";     
    char send_buf[20]="tiger john";  
    char kb_buf[20];

    if(argc = 2) {  
         strcpy(uart_dev, argv[1]);         
     }  
    printf("Using uart port: %s\n", uart_dev);

    fd = open_uart(argv[1]); //打开串口，返回文件描述符  
    if(fd == FALSE) {
        printf("Failed to open uart port: %s \n", uart_dev);
        return FALSE;
    }
   
   do{  
       err = init_uart(fd,9600,0,8,1,'N');  
       printf("Set Port Exactly!\n");  
    }while(FALSE == err || FALSE == fd);  

    while (1){
        len = recv_uart(fd, rcv_buf,99);  
        if(len > 0) {
            printf(rcv_buf);
         }
       if(kbhit()) {
            kb_buf[0]=getchar(); 
            kb_buf[1] = 0;  
            printf(kb_buf);
            send_uart(fd,kb_buf,1);
        }         

    }    

}  
