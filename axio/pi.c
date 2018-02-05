#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <byteswap.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 

#include <stdint.h>
#include <errno.h>
#include <sys/mman.h>
#include "pi.h"


uint32 g_all_PIs[MAX_PI_NUM];

int init_PI()
{
	uint32 i;

	/*code here*/
	return 0;
}



uint32 read_pi(uint32 Pi_no)
{
	/*code here*/
	return 0;
}

uint32 read_all_PIs(void)
{
	uint32 i;
	for(i=0; i<MAX_PI_NUM; i++) {
		g_all_PIs[i] = read_pi(i);
	}
	return i;
}



