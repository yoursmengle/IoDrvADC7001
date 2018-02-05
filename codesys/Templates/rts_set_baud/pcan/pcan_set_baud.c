#include <fcntl.h>    // O_RDWR
#include <errno.h>
#include <linux/types.h>
#include <linux/ioctl.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
  __u16 wBTR0BTR1;        // merged BTR0 and BTR1 register of the SJA1000
  __u8 ucCANMsgType;     // 11 or 29 bits - put MSGTYPE_... in here
  __u8 ucListenOnly;     // listen only mode when != 0
} TPCANInit;

#define CAN_BAUD_1M     0x0014  //   1 MBit/s
#define CAN_BAUD_500K   0x001C  // 500 kBit/s
#define CAN_BAUD_250K   0x011C  // 250 kBit/s
#define CAN_BAUD_125K   0x031C  // 125 kBit/s
#define CAN_BAUD_100K   0x432F  // 100 kBit/s
#define CAN_BAUD_50K    0x472F  //  50 kBit/s
#define CAN_BAUD_20K    0x532F  //  20 kBit/s
#define CAN_BAUD_10K    0x672F  //  10 kBit/s
#define CAN_BAUD_5K     0x7F7F  //   5 kBit/s

#define PCAN_MAGIC_NUMBER 'z'
#define MYSEQ_START 0x80
#define MSGTYPE_STANDARD 0x00     // marks a standard frame
#define PCAN_INIT           _IOWR(PCAN_MAGIC_NUMBER, MYSEQ_START,     TPCANInit)

static char s_device_file[80];

int pcan_switch_baudrate(int baudrate)
{
    __u16 wBTR0BTR1 = CAN_BAUD_500K;
    int err = 1;
    int nFileNo;
    TPCANInit init;
    
    switch( baudrate )
    {
        case 5:
            wBTR0BTR1 = CAN_BAUD_5K;
        break;
        case 10:
            wBTR0BTR1 = CAN_BAUD_10K;
        break;
        case 20:
            wBTR0BTR1 = CAN_BAUD_20K;
        break;
        case 50:
            wBTR0BTR1 = CAN_BAUD_50K;
        break;
        case 100:
            wBTR0BTR1 = CAN_BAUD_100K;
        break;
        case 125:
            wBTR0BTR1 = CAN_BAUD_125K;
        break;
        case 250:
            wBTR0BTR1 = CAN_BAUD_250K;
        break;
        case 500:
            wBTR0BTR1 = CAN_BAUD_500K;
        break;
        case 1000:
            wBTR0BTR1 = CAN_BAUD_1M;
        break;
        default:
            printf("ERROR: Unknown baudrate\n");
        break;
    }
    printf("INFO: Setting the baudrate to: %d (%d)\n", baudrate, (int)wBTR0BTR1);

    nFileNo = open(s_device_file, O_RDWR);
    errno = err;

    init.wBTR0BTR1    = wBTR0BTR1;    // combined BTR0 and BTR1 register of the SJA100
    init.ucCANMsgType = MSGTYPE_STANDARD;  // 11 or 29 bits
    init.ucListenOnly = 0;            // listen only mode when != 0

    if ((err = ioctl(nFileNo, PCAN_INIT, &init)) < 0)
    {
        printf("%s\n", strerror(errno));
        return err;
    }
    
    return err;
}

int main(int argc, char *argv[])
{
    int canbaud = 500;
    char dummy[] = "1000";
    
    if (argc >= 2)
    {
        strcpy(dummy, *(argv+2));
        canbaud = atoi(dummy);
    }
    else
    {
        printf("Use with: ./pcan <device> <baudrate>\n\
            e.g.: ./pcan /dev/pcanusb0 500\n");
        return 1;
    }

    memset(s_device_file, 0, sizeof(s_device_file));
    strncpy(s_device_file, *(argv+1), strlen(*(argv+1)));
    
    pcan_switch_baudrate(canbaud);
    return 0;
}
