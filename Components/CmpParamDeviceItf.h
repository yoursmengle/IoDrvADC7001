 
	
	
#ifndef _CMPPARAMDEVICEITF_H_
#define _CMPPARAMDEVICEITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"


#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
} ICmpParamDevice_C;

#ifdef CPLUSPLUS
class ICmpParamDevice : public IBase
{
	public:
};
	#ifndef ITF_CmpParamDevice
		#define ITF_CmpParamDevice static ICmpParamDevice *pICmpParamDevice = NULL;
	#endif
	#define EXTITF_CmpParamDevice
#else	/*CPLUSPLUS*/
	typedef ICmpParamDevice_C		ICmpParamDevice;
	#ifndef ITF_CmpParamDevice
		#define ITF_CmpParamDevice
	#endif
	#define EXTITF_CmpParamDevice
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPPARAMDEVICEITF_H_*/
