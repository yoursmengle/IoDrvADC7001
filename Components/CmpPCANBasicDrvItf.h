 
	
	
#ifndef _CMPPCANBASICDRVITF_H_
#define _CMPPCANBASICDRVITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "CAATypes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _pcanhwinfotag_
{
	char szName[32];
	CAA_DWORD dwDeviceNumber;
	RTS_UI16 PCANHandle;
	CAA_BYTE byCANControllerNumber; /*0 for CAN0, 1 for CAN1,...*/
	CAA_BOOL xOpened;
	CAA_BOOL bTxError;
}PCAN_HW_INFO;

typedef struct _pcaninfotag_
{
	RTS_HANDLE hSem;
	PCAN_HW_INFO hwInfo;
	CAA_WORD wBaudrate;
	unsigned long reset_current;
	unsigned long reset_last;

}PCAN_INFO;

#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
} ICmpPCANBasicDrv_C;

#ifdef CPLUSPLUS
class ICmpPCANBasicDrv : public IBase
{
	public:
};
	#ifndef ITF_CmpPCANBasicDrv
		#define ITF_CmpPCANBasicDrv static ICmpPCANBasicDrv *pICmpPCANBasicDrv = NULL;
	#endif
	#define EXTITF_CmpPCANBasicDrv
#else	/*CPLUSPLUS*/
	typedef ICmpPCANBasicDrv_C		ICmpPCANBasicDrv;
	#ifndef ITF_CmpPCANBasicDrv
		#define ITF_CmpPCANBasicDrv
	#endif
	#define EXTITF_CmpPCANBasicDrv
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPPCANBASICDRVITF_H_*/
