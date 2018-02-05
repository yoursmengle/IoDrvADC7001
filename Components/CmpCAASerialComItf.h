 
	
	
#ifndef _CMPCAASERIALCOMITF_H_
#define _CMPCAASERIALCOMITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAASerialCom.h"
#include "CAAAsyncMan.h"
#include "CAAMemBlockMan.h"

#ifdef __cplusplus
extern "C" {
#endif

CAA_ERROR CDECL COM_WorkerInit(void);
typedef CAA_ERROR (CDECL * PFCOM_WORKERINIT) (void);
#if defined(CMPCAASERIALCOM_NOTIMPLEMENTED) || defined(COM_WORKERINIT_NOTIMPLEMENTED)
	#define USE_COM_WorkerInit
	#define EXT_COM_WorkerInit
	#define GET_COM_WorkerInit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_COM_WorkerInit()  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_COM_WorkerInit  FALSE
	#define EXP_COM_WorkerInit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_COM_WorkerInit
	#define EXT_COM_WorkerInit
	#define GET_COM_WorkerInit(fl)  CAL_CMGETAPI( "COM_WorkerInit" ) 
	#define CAL_COM_WorkerInit  COM_WorkerInit
	#define CHK_COM_WorkerInit  TRUE
	#define EXP_COM_WorkerInit  CAL_CMEXPAPI( "COM_WorkerInit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASERIALCOM_EXTERNAL)
	#define USE_COM_WorkerInit
	#define EXT_COM_WorkerInit
	#define GET_COM_WorkerInit(fl)  CAL_CMGETAPI( "COM_WorkerInit" ) 
	#define CAL_COM_WorkerInit  COM_WorkerInit
	#define CHK_COM_WorkerInit  TRUE
	#define EXP_COM_WorkerInit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"COM_WorkerInit", (RTS_UINTPTR)COM_WorkerInit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASerialComCOM_WorkerInit
	#define EXT_CmpCAASerialComCOM_WorkerInit
	#define GET_CmpCAASerialComCOM_WorkerInit  ERR_OK
	#define CAL_CmpCAASerialComCOM_WorkerInit pICmpCAASerialCom->ICOM_WorkerInit
	#define CHK_CmpCAASerialComCOM_WorkerInit (pICmpCAASerialCom != NULL)
	#define EXP_CmpCAASerialComCOM_WorkerInit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_COM_WorkerInit
	#define EXT_COM_WorkerInit
	#define GET_COM_WorkerInit(fl)  CAL_CMGETAPI( "COM_WorkerInit" ) 
	#define CAL_COM_WorkerInit pICmpCAASerialCom->ICOM_WorkerInit
	#define CHK_COM_WorkerInit (pICmpCAASerialCom != NULL)
	#define EXP_COM_WorkerInit  CAL_CMEXPAPI( "COM_WorkerInit" ) 
#else /* DYNAMIC_LINK */
	#define USE_COM_WorkerInit  PFCOM_WORKERINIT pfCOM_WorkerInit;
	#define EXT_COM_WorkerInit  extern PFCOM_WORKERINIT pfCOM_WorkerInit;
	#define GET_COM_WorkerInit(fl)  s_pfCMGetAPI2( "COM_WorkerInit", (RTS_VOID_FCTPTR *)&pfCOM_WorkerInit, (fl), 0, 0)
	#define CAL_COM_WorkerInit  pfCOM_WorkerInit
	#define CHK_COM_WorkerInit  (pfCOM_WorkerInit != NULL)
	#define EXP_COM_WorkerInit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"COM_WorkerInit", (RTS_UINTPTR)COM_WorkerInit, 0, 0) 
#endif



CAA_ERROR CDECL COM_WorkerExit(void);
typedef CAA_ERROR (CDECL * PFCOM_WORKEREXIT) (void);
#if defined(CMPCAASERIALCOM_NOTIMPLEMENTED) || defined(COM_WORKEREXIT_NOTIMPLEMENTED)
	#define USE_COM_WorkerExit
	#define EXT_COM_WorkerExit
	#define GET_COM_WorkerExit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_COM_WorkerExit()  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_COM_WorkerExit  FALSE
	#define EXP_COM_WorkerExit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_COM_WorkerExit
	#define EXT_COM_WorkerExit
	#define GET_COM_WorkerExit(fl)  CAL_CMGETAPI( "COM_WorkerExit" ) 
	#define CAL_COM_WorkerExit  COM_WorkerExit
	#define CHK_COM_WorkerExit  TRUE
	#define EXP_COM_WorkerExit  CAL_CMEXPAPI( "COM_WorkerExit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASERIALCOM_EXTERNAL)
	#define USE_COM_WorkerExit
	#define EXT_COM_WorkerExit
	#define GET_COM_WorkerExit(fl)  CAL_CMGETAPI( "COM_WorkerExit" ) 
	#define CAL_COM_WorkerExit  COM_WorkerExit
	#define CHK_COM_WorkerExit  TRUE
	#define EXP_COM_WorkerExit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"COM_WorkerExit", (RTS_UINTPTR)COM_WorkerExit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASerialComCOM_WorkerExit
	#define EXT_CmpCAASerialComCOM_WorkerExit
	#define GET_CmpCAASerialComCOM_WorkerExit  ERR_OK
	#define CAL_CmpCAASerialComCOM_WorkerExit pICmpCAASerialCom->ICOM_WorkerExit
	#define CHK_CmpCAASerialComCOM_WorkerExit (pICmpCAASerialCom != NULL)
	#define EXP_CmpCAASerialComCOM_WorkerExit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_COM_WorkerExit
	#define EXT_COM_WorkerExit
	#define GET_COM_WorkerExit(fl)  CAL_CMGETAPI( "COM_WorkerExit" ) 
	#define CAL_COM_WorkerExit pICmpCAASerialCom->ICOM_WorkerExit
	#define CHK_COM_WorkerExit (pICmpCAASerialCom != NULL)
	#define EXP_COM_WorkerExit  CAL_CMEXPAPI( "COM_WorkerExit" ) 
#else /* DYNAMIC_LINK */
	#define USE_COM_WorkerExit  PFCOM_WORKEREXIT pfCOM_WorkerExit;
	#define EXT_COM_WorkerExit  extern PFCOM_WORKEREXIT pfCOM_WorkerExit;
	#define GET_COM_WorkerExit(fl)  s_pfCMGetAPI2( "COM_WorkerExit", (RTS_VOID_FCTPTR *)&pfCOM_WorkerExit, (fl), 0, 0)
	#define CAL_COM_WorkerExit  pfCOM_WorkerExit
	#define CHK_COM_WorkerExit  (pfCOM_WorkerExit != NULL)
	#define EXP_COM_WorkerExit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"COM_WorkerExit", (RTS_UINTPTR)COM_WorkerExit, 0, 0) 
#endif




#define	COM_SETTINGS_PORT				0x01
#define	COM_SETTINGS_STOPBIT			0x02
#define	COM_SETTINGS_PARITY				0x03
#define	COM_SETTINGS_BAUDRATE			0x04
#define	COM_SETTINGS_TIMEOUT			0x05
#define	COM_SETTINGS_BUFFERSIZE			0x06
#define	COM_SETTINGS_BYTESIZE			0x07
#define	COM_SETTINGS_BINARY				0x08
#define	COM_SETTINGS_OUTXCTSFLOW		0x09
#define	COM_SETTINGS_OUTXDSRFLOW		0x0A
#define	COM_SETTINGS_DTRCONTROL			0x0B
#define	COM_SETTINGS_DSRSENSITIVITY		0x0C
#define	COM_SETTINGS_RTSCONTROL			0x0D
#define	COM_SETTINGS_TXCONTINUEONXOFF	0x0E
#define	COM_SETTINGS_OUTX				0x0F
#define	COM_SETTINGS_INX				0x10
#define	COM_SETTINGS_XONCHAR			0x11
#define	COM_SETTINGS_XOFFCHAR			0x12
#define	COM_SETTINGS_XONLIM				0x13
#define	COM_SETTINGS_XOFFLIM			0x14

#ifdef __cplusplus
}
#endif


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Closes the serial port synchonously. Only to be called by SerialClass.Close in FB_Exit. 
 */
typedef struct tagcom_close_struct
{
	CAA_HANDLE hCom;					/* VAR_INPUT */	
	CAA_ERROR COM_Close;				/* VAR_OUTPUT */	
} com_close_struct;

void CDECL CDECL_EXT com_close(com_close_struct *p);
typedef void (CDECL CDECL_EXT* PFCOM_CLOSE_IEC) (com_close_struct *p);
#if defined(CMPCAASERIALCOM_NOTIMPLEMENTED) || defined(COM_CLOSE_NOTIMPLEMENTED)
	#define USE_com_close
	#define EXT_com_close
	#define GET_com_close(fl)  ERR_NOTIMPLEMENTED
	#define CAL_com_close(p0) 
	#define CHK_com_close  FALSE
	#define EXP_com_close  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_com_close
	#define EXT_com_close
	#define GET_com_close(fl)  CAL_CMGETAPI( "com_close" ) 
	#define CAL_com_close  com_close
	#define CHK_com_close  TRUE
	#define EXP_com_close  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"com_close", (RTS_UINTPTR)com_close, 1, RTSITF_GET_SIGNATURE(0x14BED712, 0xE3A6D576), 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPCAASERIALCOM_EXTERNAL)
	#define USE_com_close
	#define EXT_com_close
	#define GET_com_close(fl)  CAL_CMGETAPI( "com_close" ) 
	#define CAL_com_close  com_close
	#define CHK_com_close  TRUE
	#define EXP_com_close  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"com_close", (RTS_UINTPTR)com_close, 1, RTSITF_GET_SIGNATURE(0x14BED712, 0xE3A6D576), 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAASerialComcom_close
	#define EXT_CmpCAASerialComcom_close
	#define GET_CmpCAASerialComcom_close  ERR_OK
	#define CAL_CmpCAASerialComcom_close  com_close
	#define CHK_CmpCAASerialComcom_close  TRUE
	#define EXP_CmpCAASerialComcom_close  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"com_close", (RTS_UINTPTR)com_close, 1, RTSITF_GET_SIGNATURE(0x14BED712, 0xE3A6D576), 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_com_close
	#define EXT_com_close
	#define GET_com_close(fl)  CAL_CMGETAPI( "com_close" ) 
	#define CAL_com_close  com_close
	#define CHK_com_close  TRUE
	#define EXP_com_close  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"com_close", (RTS_UINTPTR)com_close, 1, RTSITF_GET_SIGNATURE(0x14BED712, 0xE3A6D576), 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_com_close  PFCOM_CLOSE_IEC pfcom_close;
	#define EXT_com_close  extern PFCOM_CLOSE_IEC pfcom_close;
	#define GET_com_close(fl)  s_pfCMGetAPI2( "com_close", (RTS_VOID_FCTPTR *)&pfcom_close, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0x14BED712, 0xE3A6D576), 0x03050600)
	#define CAL_com_close  pfcom_close
	#define CHK_com_close  (pfcom_close != NULL)
	#define EXP_com_close   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"com_close", (RTS_UINTPTR)com_close, 1, RTSITF_GET_SIGNATURE(0x14BED712, 0xE3A6D576), 0x03050600) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/



typedef struct
{
	IBase_C *pBase;
	PFCOM_WORKERINIT ICOM_WorkerInit;
 	PFCOM_WORKEREXIT ICOM_WorkerExit;
 } ICmpCAASerialCom_C;

#ifdef CPLUSPLUS
class ICmpCAASerialCom : public IBase
{
	public:
		virtual CAA_ERROR CDECL ICOM_WorkerInit(void) =0;
		virtual CAA_ERROR CDECL ICOM_WorkerExit(void) =0;
};
	#ifndef ITF_CmpCAASerialCom
		#define ITF_CmpCAASerialCom static ICmpCAASerialCom *pICmpCAASerialCom = NULL;
	#endif
	#define EXTITF_CmpCAASerialCom
#else	/*CPLUSPLUS*/
	typedef ICmpCAASerialCom_C		ICmpCAASerialCom;
	#ifndef ITF_CmpCAASerialCom
		#define ITF_CmpCAASerialCom
	#endif
	#define EXTITF_CmpCAASerialCom
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCAASERIALCOMITF_H_*/
