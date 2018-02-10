
#include "IoDrvInc.h"


uint32 iosInit(void)
{
	if (init_AI() > 0 ) {
		return ERR_AI_INIT;
	}

	if(init_DI_DO() > 0) {
		return ERR_GPIO_INIT;
	}

	if(init_PWM() > 0) {

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


