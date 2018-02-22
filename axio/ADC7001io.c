
#include "IoDrvInc.h"

uint32 iosInit(void)
{
	uint32 mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
	
	if (mem_fd > 0) 	{
		printf("Success to open /dev/mem fd=0x%08x\n", mem_fd);
	} 	else {
		printf("Fail to open /dev/mem fd=0x%08x\n", mem_fd);
	}


	if(init_DI_DO(mem_fd) > 0) {
		return ERR_GPIO_INIT;
	}

	if (init_AI(mem_fd) > 0 ) {
		return ERR_AI_INIT;
	}

	if(init_PWM(mem_fd) > 0) {

		return ERR_PWM_INIT;

	}
/*
	if(init_i2c()<=0) {
		return ERR_I2C_INIT;
	}

	if(init_gsensor() <= 0) {
		return ERR_GSENSOR_INIT;
	}

	if(init_NB_IOT() <=0) {
		return ERR_NB_IOT_INIT;
	}
*/
	return 0;
}


