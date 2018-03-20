   
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
#include <string.h>

int export_port(unsigned int port_num)
{
	char cmd[80];
      char file[80] = "/sys/class/gpio/gpio111/value";   //for port111 test only
    
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
}

void disable_nb05(void)
{
	export_port(PORT_ENA_NB05);
	output_low(PORT_ENA_NB05);
}
   
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
            printf("set baudrit to: %d\n", speed);
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
    len = write(fd, kb_buf, strlen(kb_buf));
    printf("write %d bytes to %s \n", len, uart_dev);

    for(i=0; i<100000; i++);
    
    uart_noblock(fd);
    len = read(fd,rcv_buf,99);  
    printf("rec %d bytes from %s \n", len, uart_dev);

    if(len > 0) {
        printf(rcv_buf);
     }
    

    while (1){
        //uart_noblock(fd);
        len = read(fd,rcv_buf,99);  
        printf("rec %d bytes from %s \n", len, uart_dev);
        if(len > 0) {
            printf(rcv_buf);
         }

       strcpy(kb_buf, "at+cgmr\r\n");

       for(i=0; i<100000; i++);
       len = write(fd, kb_buf, strlen(kb_buf));
       printf("write %d bytes to %s \n", len, uart_dev);
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
