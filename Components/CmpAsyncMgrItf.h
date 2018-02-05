 /**
 * <interfacename>CmpAsyncMgr</interfacename>
 * <description> 
 *	<p>Interface of the asynchronous job manager. This job manager enables, to execute synchronous jobs
 *	asynchronously.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPASYNCMGRITF_H_
#define _CMPASYNCMGRITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"

/* Type of an async job*/
#define ASYNCJOB_TASK					0
#define ASYNCJOB_EVENT					1
#define ASYNCJOB_HOOK					2

/* State of an async job*/
#define ASYNCSTATE_INVALID				UINT32_MAX
#define ASYNCSTATE_PENDING				0
#define ASYNCSTATE_ACTIVE				1
#define ASYNCSTATE_READY				2
#define ASYNCSTATE_ERROR				3
#define ASYNCSTATE_TIMEOUT				4
/*#define ASYNCSTATE_READY_TO_REMOVE		5	*//* Do not use! Will be removed again in future! */
#define ASYNCSTATE_CANCELED				6

#define ASYNC_TIMEOUT_INFINITE			0 

#ifndef ASYNCMGR_NUM_OF_STATIC_JOBS
	#define ASYNCMGR_NUM_OF_STATIC_JOBS		10
#endif                      


typedef void HUGEPTR(CDECL *PFASYNCJOBFUNCTION)(void *pParam);

/**
 * <description>Callback if the asyncjob caused an exception.</description>
 * <param name="pAsynFunction" type="IN">Functionpointer of the asyncjob.</param>
 * <param name="pParam" type="IN">Parameter used by the asynyjob causing the exception.</param>
 * <param name="ulException" type="IN">Exception caused by the asyncjob. See SysTaskItf for details.</param>
 * <param name="Context" type="IN">Context of the exception. See SysTaskItf for details.</param>
 */
typedef void (CDECL *PFASYNCMGREXCEPTIONHANDLER)(PFASYNCJOBFUNCTION pAsynFunction, void* pParam, RTS_UI32 ulException, RegContext Context);

typedef struct
{
	void* pInstance;
	void* pParam;
	RTS_RESULT out;
} ASYNCJOB_IECCALLPARAM_METH;

typedef struct
{
	void* pParam;
	RTS_RESULT out;
} ASYNCJOB_IECCALLPARAM_FUNC;

typedef struct
{
	char*			pszTaskname; 
	RTS_UI32		ulTaskpriority;
	RTS_UI32		ulTaskSleepTime; 
	RTS_HANDLE		hTaskHandle; 
	int				bEndTaskAfterJob;
} ASYNCJOB_TASKPARAM;

typedef struct
{
	RTS_UI32		ulEventId;
	RTS_UI32		ulEventClass;
	RTS_UI32		ulCmpId;
	RTS_HANDLE		hEvent;
} ASYNCJOB_EVENTPARAM;

typedef struct
{
	RTS_UI32		ulHookId;
} ASYNCJOB_HOOKPARAM;

typedef union 
{
	ASYNCJOB_TASKPARAM	tTaskParam;
	ASYNCJOB_EVENTPARAM	tEventParam;
	ASYNCJOB_HOOKPARAM	tHookParam;
} ASYNCJOB_PARAM;

typedef struct
{
	RTS_HANDLE			hJob;
	PFASYNCJOBFUNCTION	pfJob;
	void*				pParam;
	void*				pInstance;
	RTS_UI32*			pulState;
	int					bIecFunc;
	RTS_UI32			ulType;
	RTS_UI32			ulTimeout;
	ASYNCJOB_PARAM*		pJobParam;
	RTS_UI32			ulJobReturnVal;
	RTS_UI32			ulStartTime;
} ASYNCJOB_INFO;

/**
 * <category>Async job info 2</category>
 * <element name="pfJob" type="IN">Pointer to the job function, which is executed asynchronously</element>
 * <element name="pParam" type="IN">Pointer to the parameters for the function</element>
 * <element name="pInstance" type="IN">Optional pointer to the instance (IEC function block or class). Can be NULL.</element>
 * <element name="pulState" type="IN">Pointer to actual state of the async job. 
 *									  NOTE: Can be NULL for fire and forget jobs, which are released automatically at the end of job execution</element>
 * <element name="bIECFunc" type="IN">TRUE=pfJob is an IEC function, FALSE=pfJob is a C-function</element>
 * <element name="ulType" type="IN">Type of async job (task, event or hook driven)</element>
 * <element name="ulTimeout" type="IN">Timeout for executing the job</element>
 * <element name="pJobParam" type="IN">Specific Parameters for the job types (task, event or hook driven)</element>
 * <element name="ulJobReturnVal" type="IN">Return code of the job if finished</element>
 * <element name="ulStartTime" type="IN">Start time of the job (in ms by SysTimeGetMs)</element>
 * <element name="pfExceptionHandler" type="IN">Optional exception handle which is called, if an exception occurred during asynchronous job execution.</element>
 * <element name="phJob" type="OUT">Pointer to the handle of the job. Is returned in AsyncAdd2.</element>
 */
typedef struct
{
	PFASYNCJOBFUNCTION	pfJob;
	void*				pParam;
	void*				pInstance;
	RTS_UI32*			pulState;
	int					bIecFunc;
	RTS_UI32			ulType;
	RTS_UI32			ulTimeout;
	ASYNCJOB_PARAM*		pJobParam;
	RTS_UI32			ulJobReturnVal;
	RTS_UI32			ulStartTime;
	PFTASKEXCEPTIONHANDLER pfExceptionHandler;
	RTS_HANDLE			*phJob;
} ASYNCJOB_INFO2;

/**
 * <category>Async job info 2</category>
 * <element name="pfJob" type="IN">Pointer to the job function, which is executed asynchronously</element>
 * <element name="pParam" type="IN">Pointer to the parameters for the function</element>
 * <element name="pInstance" type="IN">Optional pointer to the instance (IEC function block or class). Can be NULL.</element>
 * <element name="pulState" type="IN">Pointer to actual state of the async job. 
 *									  NOTE: Can be NULL for fire and forget jobs, which are released automatically at the end of job execution</element>
 * <element name="bIECFunc" type="IN">TRUE=pfJob is an IEC function, FALSE=pfJob is a C-function</element>
 * <element name="ulType" type="IN">Type of async job (task, event or hook driven)</element>
 * <element name="ulTimeout" type="IN">Timeout for executing the job</element>
 * <element name="pJobParam" type="IN">Specific Parameters for the job types (task, event or hook driven)</element>
 * <element name="ulJobReturnVal" type="IN">Return code of the job if finished</element>
 * <element name="ulStartTime" type="IN">Start time of the job (in ms by SysTimeGetMs)</element>
 * <element name="pfExceptionHandler" type="IN">Optional exception handle which is called, if an exception occurred during asynchronous job execution.</element>
 * <element name="phJob" type="OUT">Pointer to the handle of the job. Is returned in AsyncAdd2.</element>
 * <element name="pfAsyncMgrExceptionHandler" type="IN">Optional exception handler which is called, if an exception occurred during asynchronous job execution. This exception handler is called with the parameters of the job which caused the exception.</element>
 */
typedef struct
{
	PFASYNCJOBFUNCTION	pfJob;
	void*				pParam;
	void*				pInstance;
	RTS_UI32*			pulState;
	int					bIecFunc;
	RTS_UI32			ulType;
	RTS_UI32			ulTimeout;
	ASYNCJOB_PARAM*		pJobParam;
	RTS_UI32			ulJobReturnVal;
	RTS_UI32			ulStartTime;
	PFTASKEXCEPTIONHANDLER pfExceptionHandler;
	RTS_HANDLE			*phJob;
    PFASYNCMGREXCEPTIONHANDLER pfAsyncMgrExceptionHandler;
} ASYNCJOB_INFO3;

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>asyncadd</description>
 */
typedef struct tagasyncadd_struct
{
	RTS_IEC_BYTE *pfJobFunc;			/* VAR_INPUT */	
	RTS_IEC_BYTE *pParam;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pInstance;			/* VAR_INPUT */	
	RTS_IEC_UDINT *pulState;			/* VAR_INPUT */	
	RTS_IEC_UDINT ulIecFunc;			/* VAR_INPUT */	
	RTS_IEC_UDINT ulType;				/* VAR_INPUT */	
	RTS_IEC_UDINT ulTimeout;			/* VAR_INPUT */	
	ASYNCJOB_PARAM *pAsyncJobParam;		/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE AsyncAdd;			/* VAR_OUTPUT */	
} asyncadd_struct;

void CDECL CDECL_EXT asyncadd(asyncadd_struct *p);
typedef void (CDECL CDECL_EXT* PFASYNCADD_IEC) (asyncadd_struct *p);
#if defined(CMPASYNCMGR_NOTIMPLEMENTED) || defined(ASYNCADD_NOTIMPLEMENTED)
	#define USE_asyncadd
	#define EXT_asyncadd
	#define GET_asyncadd(fl)  ERR_NOTIMPLEMENTED
	#define CAL_asyncadd(p0) 
	#define CHK_asyncadd  FALSE
	#define EXP_asyncadd  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_asyncadd
	#define EXT_asyncadd
	#define GET_asyncadd(fl)  CAL_CMGETAPI( "asyncadd" ) 
	#define CAL_asyncadd  asyncadd
	#define CHK_asyncadd  TRUE
	#define EXP_asyncadd  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asyncadd", (RTS_UINTPTR)asyncadd, 1, RTSITF_GET_SIGNATURE(0, 0x10FA73A4), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPASYNCMGR_EXTERNAL)
	#define USE_asyncadd
	#define EXT_asyncadd
	#define GET_asyncadd(fl)  CAL_CMGETAPI( "asyncadd" ) 
	#define CAL_asyncadd  asyncadd
	#define CHK_asyncadd  TRUE
	#define EXP_asyncadd  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asyncadd", (RTS_UINTPTR)asyncadd, 1, RTSITF_GET_SIGNATURE(0, 0x10FA73A4), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAsyncMgrasyncadd
	#define EXT_CmpAsyncMgrasyncadd
	#define GET_CmpAsyncMgrasyncadd  ERR_OK
	#define CAL_CmpAsyncMgrasyncadd  asyncadd
	#define CHK_CmpAsyncMgrasyncadd  TRUE
	#define EXP_CmpAsyncMgrasyncadd  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asyncadd", (RTS_UINTPTR)asyncadd, 1, RTSITF_GET_SIGNATURE(0, 0x10FA73A4), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_asyncadd
	#define EXT_asyncadd
	#define GET_asyncadd(fl)  CAL_CMGETAPI( "asyncadd" ) 
	#define CAL_asyncadd  asyncadd
	#define CHK_asyncadd  TRUE
	#define EXP_asyncadd  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asyncadd", (RTS_UINTPTR)asyncadd, 1, RTSITF_GET_SIGNATURE(0, 0x10FA73A4), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_asyncadd  PFASYNCADD_IEC pfasyncadd;
	#define EXT_asyncadd  extern PFASYNCADD_IEC pfasyncadd;
	#define GET_asyncadd(fl)  s_pfCMGetAPI2( "asyncadd", (RTS_VOID_FCTPTR *)&pfasyncadd, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x10FA73A4), 0x03050500)
	#define CAL_asyncadd  pfasyncadd
	#define CHK_asyncadd  (pfasyncadd != NULL)
	#define EXP_asyncadd   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asyncadd", (RTS_UINTPTR)asyncadd, 1, RTSITF_GET_SIGNATURE(0, 0x10FA73A4), 0x03050500) 
#endif


/**
 * <description>asyncgetjobreturnvalue</description>
 */
typedef struct tagasyncgetjobreturnvalue_struct
{
	RTS_IEC_HANDLE hJob;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pulReturnVal;		/* VAR_INPUT */	
	RTS_IEC_RESULT AsyncGetJobReturnValue;	/* VAR_OUTPUT */	
} asyncgetjobreturnvalue_struct;

void CDECL CDECL_EXT asyncgetjobreturnvalue(asyncgetjobreturnvalue_struct *p);
typedef void (CDECL CDECL_EXT* PFASYNCGETJOBRETURNVALUE_IEC) (asyncgetjobreturnvalue_struct *p);
#if defined(CMPASYNCMGR_NOTIMPLEMENTED) || defined(ASYNCGETJOBRETURNVALUE_NOTIMPLEMENTED)
	#define USE_asyncgetjobreturnvalue
	#define EXT_asyncgetjobreturnvalue
	#define GET_asyncgetjobreturnvalue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_asyncgetjobreturnvalue(p0) 
	#define CHK_asyncgetjobreturnvalue  FALSE
	#define EXP_asyncgetjobreturnvalue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_asyncgetjobreturnvalue
	#define EXT_asyncgetjobreturnvalue
	#define GET_asyncgetjobreturnvalue(fl)  CAL_CMGETAPI( "asyncgetjobreturnvalue" ) 
	#define CAL_asyncgetjobreturnvalue  asyncgetjobreturnvalue
	#define CHK_asyncgetjobreturnvalue  TRUE
	#define EXP_asyncgetjobreturnvalue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asyncgetjobreturnvalue", (RTS_UINTPTR)asyncgetjobreturnvalue, 1, RTSITF_GET_SIGNATURE(0, 0xFD4D0A88), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPASYNCMGR_EXTERNAL)
	#define USE_asyncgetjobreturnvalue
	#define EXT_asyncgetjobreturnvalue
	#define GET_asyncgetjobreturnvalue(fl)  CAL_CMGETAPI( "asyncgetjobreturnvalue" ) 
	#define CAL_asyncgetjobreturnvalue  asyncgetjobreturnvalue
	#define CHK_asyncgetjobreturnvalue  TRUE
	#define EXP_asyncgetjobreturnvalue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asyncgetjobreturnvalue", (RTS_UINTPTR)asyncgetjobreturnvalue, 1, RTSITF_GET_SIGNATURE(0, 0xFD4D0A88), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAsyncMgrasyncgetjobreturnvalue
	#define EXT_CmpAsyncMgrasyncgetjobreturnvalue
	#define GET_CmpAsyncMgrasyncgetjobreturnvalue  ERR_OK
	#define CAL_CmpAsyncMgrasyncgetjobreturnvalue  asyncgetjobreturnvalue
	#define CHK_CmpAsyncMgrasyncgetjobreturnvalue  TRUE
	#define EXP_CmpAsyncMgrasyncgetjobreturnvalue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asyncgetjobreturnvalue", (RTS_UINTPTR)asyncgetjobreturnvalue, 1, RTSITF_GET_SIGNATURE(0, 0xFD4D0A88), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_asyncgetjobreturnvalue
	#define EXT_asyncgetjobreturnvalue
	#define GET_asyncgetjobreturnvalue(fl)  CAL_CMGETAPI( "asyncgetjobreturnvalue" ) 
	#define CAL_asyncgetjobreturnvalue  asyncgetjobreturnvalue
	#define CHK_asyncgetjobreturnvalue  TRUE
	#define EXP_asyncgetjobreturnvalue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asyncgetjobreturnvalue", (RTS_UINTPTR)asyncgetjobreturnvalue, 1, RTSITF_GET_SIGNATURE(0, 0xFD4D0A88), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_asyncgetjobreturnvalue  PFASYNCGETJOBRETURNVALUE_IEC pfasyncgetjobreturnvalue;
	#define EXT_asyncgetjobreturnvalue  extern PFASYNCGETJOBRETURNVALUE_IEC pfasyncgetjobreturnvalue;
	#define GET_asyncgetjobreturnvalue(fl)  s_pfCMGetAPI2( "asyncgetjobreturnvalue", (RTS_VOID_FCTPTR *)&pfasyncgetjobreturnvalue, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xFD4D0A88), 0x03050500)
	#define CAL_asyncgetjobreturnvalue  pfasyncgetjobreturnvalue
	#define CHK_asyncgetjobreturnvalue  (pfasyncgetjobreturnvalue != NULL)
	#define EXP_asyncgetjobreturnvalue   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asyncgetjobreturnvalue", (RTS_UINTPTR)asyncgetjobreturnvalue, 1, RTSITF_GET_SIGNATURE(0, 0xFD4D0A88), 0x03050500) 
#endif


/**
 * <description>asynckill</description>
 */
typedef struct tagasynckill_struct
{
	RTS_IEC_HANDLE hJob;				/* VAR_INPUT */	
	RTS_IEC_RESULT AsyncKill;			/* VAR_OUTPUT */	
} asynckill_struct;

void CDECL CDECL_EXT asynckill(asynckill_struct *p);
typedef void (CDECL CDECL_EXT* PFASYNCKILL_IEC) (asynckill_struct *p);
#if defined(CMPASYNCMGR_NOTIMPLEMENTED) || defined(ASYNCKILL_NOTIMPLEMENTED)
	#define USE_asynckill
	#define EXT_asynckill
	#define GET_asynckill(fl)  ERR_NOTIMPLEMENTED
	#define CAL_asynckill(p0) 
	#define CHK_asynckill  FALSE
	#define EXP_asynckill  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_asynckill
	#define EXT_asynckill
	#define GET_asynckill(fl)  CAL_CMGETAPI( "asynckill" ) 
	#define CAL_asynckill  asynckill
	#define CHK_asynckill  TRUE
	#define EXP_asynckill  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asynckill", (RTS_UINTPTR)asynckill, 1, RTSITF_GET_SIGNATURE(0, 0xAE42472A), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPASYNCMGR_EXTERNAL)
	#define USE_asynckill
	#define EXT_asynckill
	#define GET_asynckill(fl)  CAL_CMGETAPI( "asynckill" ) 
	#define CAL_asynckill  asynckill
	#define CHK_asynckill  TRUE
	#define EXP_asynckill  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asynckill", (RTS_UINTPTR)asynckill, 1, RTSITF_GET_SIGNATURE(0, 0xAE42472A), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAsyncMgrasynckill
	#define EXT_CmpAsyncMgrasynckill
	#define GET_CmpAsyncMgrasynckill  ERR_OK
	#define CAL_CmpAsyncMgrasynckill  asynckill
	#define CHK_CmpAsyncMgrasynckill  TRUE
	#define EXP_CmpAsyncMgrasynckill  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asynckill", (RTS_UINTPTR)asynckill, 1, RTSITF_GET_SIGNATURE(0, 0xAE42472A), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_asynckill
	#define EXT_asynckill
	#define GET_asynckill(fl)  CAL_CMGETAPI( "asynckill" ) 
	#define CAL_asynckill  asynckill
	#define CHK_asynckill  TRUE
	#define EXP_asynckill  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asynckill", (RTS_UINTPTR)asynckill, 1, RTSITF_GET_SIGNATURE(0, 0xAE42472A), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_asynckill  PFASYNCKILL_IEC pfasynckill;
	#define EXT_asynckill  extern PFASYNCKILL_IEC pfasynckill;
	#define GET_asynckill(fl)  s_pfCMGetAPI2( "asynckill", (RTS_VOID_FCTPTR *)&pfasynckill, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xAE42472A), 0x03050500)
	#define CAL_asynckill  pfasynckill
	#define CHK_asynckill  (pfasynckill != NULL)
	#define EXP_asynckill   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asynckill", (RTS_UINTPTR)asynckill, 1, RTSITF_GET_SIGNATURE(0, 0xAE42472A), 0x03050500) 
#endif


/**
 * <description>asyncremove</description>
 */
typedef struct tagasyncremove_struct
{
	RTS_IEC_HANDLE hJob;				/* VAR_INPUT */	
	RTS_IEC_RESULT AsyncRemove;			/* VAR_OUTPUT */	
} asyncremove_struct;

void CDECL CDECL_EXT asyncremove(asyncremove_struct *p);
typedef void (CDECL CDECL_EXT* PFASYNCREMOVE_IEC) (asyncremove_struct *p);
#if defined(CMPASYNCMGR_NOTIMPLEMENTED) || defined(ASYNCREMOVE_NOTIMPLEMENTED)
	#define USE_asyncremove
	#define EXT_asyncremove
	#define GET_asyncremove(fl)  ERR_NOTIMPLEMENTED
	#define CAL_asyncremove(p0) 
	#define CHK_asyncremove  FALSE
	#define EXP_asyncremove  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_asyncremove
	#define EXT_asyncremove
	#define GET_asyncremove(fl)  CAL_CMGETAPI( "asyncremove" ) 
	#define CAL_asyncremove  asyncremove
	#define CHK_asyncremove  TRUE
	#define EXP_asyncremove  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asyncremove", (RTS_UINTPTR)asyncremove, 1, RTSITF_GET_SIGNATURE(0, 0xCD84446E), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPASYNCMGR_EXTERNAL)
	#define USE_asyncremove
	#define EXT_asyncremove
	#define GET_asyncremove(fl)  CAL_CMGETAPI( "asyncremove" ) 
	#define CAL_asyncremove  asyncremove
	#define CHK_asyncremove  TRUE
	#define EXP_asyncremove  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asyncremove", (RTS_UINTPTR)asyncremove, 1, RTSITF_GET_SIGNATURE(0, 0xCD84446E), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAsyncMgrasyncremove
	#define EXT_CmpAsyncMgrasyncremove
	#define GET_CmpAsyncMgrasyncremove  ERR_OK
	#define CAL_CmpAsyncMgrasyncremove  asyncremove
	#define CHK_CmpAsyncMgrasyncremove  TRUE
	#define EXP_CmpAsyncMgrasyncremove  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asyncremove", (RTS_UINTPTR)asyncremove, 1, RTSITF_GET_SIGNATURE(0, 0xCD84446E), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_asyncremove
	#define EXT_asyncremove
	#define GET_asyncremove(fl)  CAL_CMGETAPI( "asyncremove" ) 
	#define CAL_asyncremove  asyncremove
	#define CHK_asyncremove  TRUE
	#define EXP_asyncremove  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asyncremove", (RTS_UINTPTR)asyncremove, 1, RTSITF_GET_SIGNATURE(0, 0xCD84446E), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_asyncremove  PFASYNCREMOVE_IEC pfasyncremove;
	#define EXT_asyncremove  extern PFASYNCREMOVE_IEC pfasyncremove;
	#define GET_asyncremove(fl)  s_pfCMGetAPI2( "asyncremove", (RTS_VOID_FCTPTR *)&pfasyncremove, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xCD84446E), 0x03050500)
	#define CAL_asyncremove  pfasyncremove
	#define CHK_asyncremove  (pfasyncremove != NULL)
	#define EXP_asyncremove   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asyncremove", (RTS_UINTPTR)asyncremove, 1, RTSITF_GET_SIGNATURE(0, 0xCD84446E), 0x03050500) 
#endif


/**
 * <description>asyncremoveall</description>
 */
typedef struct tagasyncremoveall_struct
{
	RTS_IEC_RESULT AsyncRemoveAll;		/* VAR_OUTPUT */	
} asyncremoveall_struct;

void CDECL CDECL_EXT asyncremoveall(asyncremoveall_struct *p);
typedef void (CDECL CDECL_EXT* PFASYNCREMOVEALL_IEC) (asyncremoveall_struct *p);
#if defined(CMPASYNCMGR_NOTIMPLEMENTED) || defined(ASYNCREMOVEALL_NOTIMPLEMENTED)
	#define USE_asyncremoveall
	#define EXT_asyncremoveall
	#define GET_asyncremoveall(fl)  ERR_NOTIMPLEMENTED
	#define CAL_asyncremoveall(p0) 
	#define CHK_asyncremoveall  FALSE
	#define EXP_asyncremoveall  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_asyncremoveall
	#define EXT_asyncremoveall
	#define GET_asyncremoveall(fl)  CAL_CMGETAPI( "asyncremoveall" ) 
	#define CAL_asyncremoveall  asyncremoveall
	#define CHK_asyncremoveall  TRUE
	#define EXP_asyncremoveall  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asyncremoveall", (RTS_UINTPTR)asyncremoveall, 1, RTSITF_GET_SIGNATURE(0, 0x17DBEEFC), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPASYNCMGR_EXTERNAL)
	#define USE_asyncremoveall
	#define EXT_asyncremoveall
	#define GET_asyncremoveall(fl)  CAL_CMGETAPI( "asyncremoveall" ) 
	#define CAL_asyncremoveall  asyncremoveall
	#define CHK_asyncremoveall  TRUE
	#define EXP_asyncremoveall  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asyncremoveall", (RTS_UINTPTR)asyncremoveall, 1, RTSITF_GET_SIGNATURE(0, 0x17DBEEFC), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAsyncMgrasyncremoveall
	#define EXT_CmpAsyncMgrasyncremoveall
	#define GET_CmpAsyncMgrasyncremoveall  ERR_OK
	#define CAL_CmpAsyncMgrasyncremoveall  asyncremoveall
	#define CHK_CmpAsyncMgrasyncremoveall  TRUE
	#define EXP_CmpAsyncMgrasyncremoveall  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asyncremoveall", (RTS_UINTPTR)asyncremoveall, 1, RTSITF_GET_SIGNATURE(0, 0x17DBEEFC), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_asyncremoveall
	#define EXT_asyncremoveall
	#define GET_asyncremoveall(fl)  CAL_CMGETAPI( "asyncremoveall" ) 
	#define CAL_asyncremoveall  asyncremoveall
	#define CHK_asyncremoveall  TRUE
	#define EXP_asyncremoveall  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asyncremoveall", (RTS_UINTPTR)asyncremoveall, 1, RTSITF_GET_SIGNATURE(0, 0x17DBEEFC), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_asyncremoveall  PFASYNCREMOVEALL_IEC pfasyncremoveall;
	#define EXT_asyncremoveall  extern PFASYNCREMOVEALL_IEC pfasyncremoveall;
	#define GET_asyncremoveall(fl)  s_pfCMGetAPI2( "asyncremoveall", (RTS_VOID_FCTPTR *)&pfasyncremoveall, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x17DBEEFC), 0x03050500)
	#define CAL_asyncremoveall  pfasyncremoveall
	#define CHK_asyncremoveall  (pfasyncremoveall != NULL)
	#define EXP_asyncremoveall   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"asyncremoveall", (RTS_UINTPTR)asyncremoveall, 1, RTSITF_GET_SIGNATURE(0, 0x17DBEEFC), 0x03050500) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description> This function adds a new async job in a jobqueue</description>
 * <param name="pfAsyncJobFunc" type="IN">Pointer to the job function, which is executed asynchronously</param>
 * <param name="pParam" type="IN">Pointer to the parameters for the function</param>
 * <param name="pulState" type="IN">Pointer to actual state of the async job. 
 *									NOTE: Can be NULL for fire and forget jobs, which are released automatically at the end of job execution!</param>
 * <param name="bIECFunc" type="IN">TRUE=pfAsyncJobFunc is an IEC function, FALSE=pfAsyncJobFunc is a C-function</param>
 * <param name="ulType" type="IN">Type of Async Job (task, event or hook driven)</param>
 * <param name="tAsyncJobParam" type="IN">Specific Parameters for the job types (task, event or hook driven)</param>
 * <param name="pResult" type="OUT">Error code</param>
 * <result>Handle to the jog object</result>
 */
RTS_HANDLE CDECL AsyncAdd(PFASYNCJOBFUNCTION pfAsyncJobFunc, void* pParam, void* pInstance, RTS_UI32* pulState, RTS_I32 bIecFunc, RTS_UI32 ulType, RTS_UI32 ulTimeout, ASYNCJOB_PARAM* pAsyncJobParam, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFASYNCADD) (PFASYNCJOBFUNCTION pfAsyncJobFunc, void* pParam, void* pInstance, RTS_UI32* pulState, RTS_I32 bIecFunc, RTS_UI32 ulType, RTS_UI32 ulTimeout, ASYNCJOB_PARAM* pAsyncJobParam, RTS_RESULT *pResult);
#if defined(CMPASYNCMGR_NOTIMPLEMENTED) || defined(ASYNCADD_NOTIMPLEMENTED)
	#define USE_AsyncAdd
	#define EXT_AsyncAdd
	#define GET_AsyncAdd(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AsyncAdd(p0,p1,p2,p3,p4,p5,p6,p7,p8)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_AsyncAdd  FALSE
	#define EXP_AsyncAdd  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AsyncAdd
	#define EXT_AsyncAdd
	#define GET_AsyncAdd(fl)  CAL_CMGETAPI( "AsyncAdd" ) 
	#define CAL_AsyncAdd  AsyncAdd
	#define CHK_AsyncAdd  TRUE
	#define EXP_AsyncAdd  CAL_CMEXPAPI( "AsyncAdd" ) 
#elif defined(MIXED_LINK) && !defined(CMPASYNCMGR_EXTERNAL)
	#define USE_AsyncAdd
	#define EXT_AsyncAdd
	#define GET_AsyncAdd(fl)  CAL_CMGETAPI( "AsyncAdd" ) 
	#define CAL_AsyncAdd  AsyncAdd
	#define CHK_AsyncAdd  TRUE
	#define EXP_AsyncAdd  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AsyncAdd", (RTS_UINTPTR)AsyncAdd, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAsyncMgrAsyncAdd
	#define EXT_CmpAsyncMgrAsyncAdd
	#define GET_CmpAsyncMgrAsyncAdd  ERR_OK
	#define CAL_CmpAsyncMgrAsyncAdd pICmpAsyncMgr->IAsyncAdd
	#define CHK_CmpAsyncMgrAsyncAdd (pICmpAsyncMgr != NULL)
	#define EXP_CmpAsyncMgrAsyncAdd  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AsyncAdd
	#define EXT_AsyncAdd
	#define GET_AsyncAdd(fl)  CAL_CMGETAPI( "AsyncAdd" ) 
	#define CAL_AsyncAdd pICmpAsyncMgr->IAsyncAdd
	#define CHK_AsyncAdd (pICmpAsyncMgr != NULL)
	#define EXP_AsyncAdd  CAL_CMEXPAPI( "AsyncAdd" ) 
#else /* DYNAMIC_LINK */
	#define USE_AsyncAdd  PFASYNCADD pfAsyncAdd;
	#define EXT_AsyncAdd  extern PFASYNCADD pfAsyncAdd;
	#define GET_AsyncAdd(fl)  s_pfCMGetAPI2( "AsyncAdd", (RTS_VOID_FCTPTR *)&pfAsyncAdd, (fl), 0, 0)
	#define CAL_AsyncAdd  pfAsyncAdd
	#define CHK_AsyncAdd  (pfAsyncAdd != NULL)
	#define EXP_AsyncAdd  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AsyncAdd", (RTS_UINTPTR)AsyncAdd, 0, 0) 
#endif




/**
 * <description> This function adds a new async job in a jobqueue. This function must be used, if the job is removed in the job handler!</description>
 * <param name="pJobInfo" type="IN">Pointer to job info with all parameters</param>
 * <param name="phJob" type="OUT">Job handle</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AsyncAdd2(ASYNCJOB_INFO2 *pJob);
typedef RTS_RESULT (CDECL * PFASYNCADD2) (ASYNCJOB_INFO2 *pJob);
#if defined(CMPASYNCMGR_NOTIMPLEMENTED) || defined(ASYNCADD2_NOTIMPLEMENTED)
	#define USE_AsyncAdd2
	#define EXT_AsyncAdd2
	#define GET_AsyncAdd2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AsyncAdd2(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AsyncAdd2  FALSE
	#define EXP_AsyncAdd2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AsyncAdd2
	#define EXT_AsyncAdd2
	#define GET_AsyncAdd2(fl)  CAL_CMGETAPI( "AsyncAdd2" ) 
	#define CAL_AsyncAdd2  AsyncAdd2
	#define CHK_AsyncAdd2  TRUE
	#define EXP_AsyncAdd2  CAL_CMEXPAPI( "AsyncAdd2" ) 
#elif defined(MIXED_LINK) && !defined(CMPASYNCMGR_EXTERNAL)
	#define USE_AsyncAdd2
	#define EXT_AsyncAdd2
	#define GET_AsyncAdd2(fl)  CAL_CMGETAPI( "AsyncAdd2" ) 
	#define CAL_AsyncAdd2  AsyncAdd2
	#define CHK_AsyncAdd2  TRUE
	#define EXP_AsyncAdd2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AsyncAdd2", (RTS_UINTPTR)AsyncAdd2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAsyncMgrAsyncAdd2
	#define EXT_CmpAsyncMgrAsyncAdd2
	#define GET_CmpAsyncMgrAsyncAdd2  ERR_OK
	#define CAL_CmpAsyncMgrAsyncAdd2 pICmpAsyncMgr->IAsyncAdd2
	#define CHK_CmpAsyncMgrAsyncAdd2 (pICmpAsyncMgr != NULL)
	#define EXP_CmpAsyncMgrAsyncAdd2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AsyncAdd2
	#define EXT_AsyncAdd2
	#define GET_AsyncAdd2(fl)  CAL_CMGETAPI( "AsyncAdd2" ) 
	#define CAL_AsyncAdd2 pICmpAsyncMgr->IAsyncAdd2
	#define CHK_AsyncAdd2 (pICmpAsyncMgr != NULL)
	#define EXP_AsyncAdd2  CAL_CMEXPAPI( "AsyncAdd2" ) 
#else /* DYNAMIC_LINK */
	#define USE_AsyncAdd2  PFASYNCADD2 pfAsyncAdd2;
	#define EXT_AsyncAdd2  extern PFASYNCADD2 pfAsyncAdd2;
	#define GET_AsyncAdd2(fl)  s_pfCMGetAPI2( "AsyncAdd2", (RTS_VOID_FCTPTR *)&pfAsyncAdd2, (fl), 0, 0)
	#define CAL_AsyncAdd2  pfAsyncAdd2
	#define CHK_AsyncAdd2  (pfAsyncAdd2 != NULL)
	#define EXP_AsyncAdd2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AsyncAdd2", (RTS_UINTPTR)AsyncAdd2, 0, 0) 
#endif




/**
 * <description> This function adds a new async job in a jobqueue. This function must be used, if the job is removed in the job handler!</description>
 * <param name="pJobInfo" type="IN">Pointer to job info with all parameters</param>
 * <param name="phJob" type="OUT">Job handle</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AsyncAdd3(ASYNCJOB_INFO3 *pJob);
typedef RTS_RESULT (CDECL * PFASYNCADD3) (ASYNCJOB_INFO3 *pJob);
#if defined(CMPASYNCMGR_NOTIMPLEMENTED) || defined(ASYNCADD3_NOTIMPLEMENTED)
	#define USE_AsyncAdd3
	#define EXT_AsyncAdd3
	#define GET_AsyncAdd3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AsyncAdd3(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AsyncAdd3  FALSE
	#define EXP_AsyncAdd3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AsyncAdd3
	#define EXT_AsyncAdd3
	#define GET_AsyncAdd3(fl)  CAL_CMGETAPI( "AsyncAdd3" ) 
	#define CAL_AsyncAdd3  AsyncAdd3
	#define CHK_AsyncAdd3  TRUE
	#define EXP_AsyncAdd3  CAL_CMEXPAPI( "AsyncAdd3" ) 
#elif defined(MIXED_LINK) && !defined(CMPASYNCMGR_EXTERNAL)
	#define USE_AsyncAdd3
	#define EXT_AsyncAdd3
	#define GET_AsyncAdd3(fl)  CAL_CMGETAPI( "AsyncAdd3" ) 
	#define CAL_AsyncAdd3  AsyncAdd3
	#define CHK_AsyncAdd3  TRUE
	#define EXP_AsyncAdd3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AsyncAdd3", (RTS_UINTPTR)AsyncAdd3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAsyncMgrAsyncAdd3
	#define EXT_CmpAsyncMgrAsyncAdd3
	#define GET_CmpAsyncMgrAsyncAdd3  ERR_OK
	#define CAL_CmpAsyncMgrAsyncAdd3 pICmpAsyncMgr->IAsyncAdd3
	#define CHK_CmpAsyncMgrAsyncAdd3 (pICmpAsyncMgr != NULL)
	#define EXP_CmpAsyncMgrAsyncAdd3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AsyncAdd3
	#define EXT_AsyncAdd3
	#define GET_AsyncAdd3(fl)  CAL_CMGETAPI( "AsyncAdd3" ) 
	#define CAL_AsyncAdd3 pICmpAsyncMgr->IAsyncAdd3
	#define CHK_AsyncAdd3 (pICmpAsyncMgr != NULL)
	#define EXP_AsyncAdd3  CAL_CMEXPAPI( "AsyncAdd3" ) 
#else /* DYNAMIC_LINK */
	#define USE_AsyncAdd3  PFASYNCADD3 pfAsyncAdd3;
	#define EXT_AsyncAdd3  extern PFASYNCADD3 pfAsyncAdd3;
	#define GET_AsyncAdd3(fl)  s_pfCMGetAPI2( "AsyncAdd3", (RTS_VOID_FCTPTR *)&pfAsyncAdd3, (fl), 0, 0)
	#define CAL_AsyncAdd3  pfAsyncAdd3
	#define CHK_AsyncAdd3  (pfAsyncAdd3 != NULL)
	#define EXP_AsyncAdd3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AsyncAdd3", (RTS_UINTPTR)AsyncAdd3, 0, 0) 
#endif




/**
 * <description> This function removes on async job of a job queue</description>
 * <param name="hJob" type="IN">Handle to the job</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AsyncRemove(RTS_HANDLE hJob);
typedef RTS_RESULT (CDECL * PFASYNCREMOVE) (RTS_HANDLE hJob);
#if defined(CMPASYNCMGR_NOTIMPLEMENTED) || defined(ASYNCREMOVE_NOTIMPLEMENTED)
	#define USE_AsyncRemove
	#define EXT_AsyncRemove
	#define GET_AsyncRemove(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AsyncRemove(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AsyncRemove  FALSE
	#define EXP_AsyncRemove  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AsyncRemove
	#define EXT_AsyncRemove
	#define GET_AsyncRemove(fl)  CAL_CMGETAPI( "AsyncRemove" ) 
	#define CAL_AsyncRemove  AsyncRemove
	#define CHK_AsyncRemove  TRUE
	#define EXP_AsyncRemove  CAL_CMEXPAPI( "AsyncRemove" ) 
#elif defined(MIXED_LINK) && !defined(CMPASYNCMGR_EXTERNAL)
	#define USE_AsyncRemove
	#define EXT_AsyncRemove
	#define GET_AsyncRemove(fl)  CAL_CMGETAPI( "AsyncRemove" ) 
	#define CAL_AsyncRemove  AsyncRemove
	#define CHK_AsyncRemove  TRUE
	#define EXP_AsyncRemove  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AsyncRemove", (RTS_UINTPTR)AsyncRemove, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAsyncMgrAsyncRemove
	#define EXT_CmpAsyncMgrAsyncRemove
	#define GET_CmpAsyncMgrAsyncRemove  ERR_OK
	#define CAL_CmpAsyncMgrAsyncRemove pICmpAsyncMgr->IAsyncRemove
	#define CHK_CmpAsyncMgrAsyncRemove (pICmpAsyncMgr != NULL)
	#define EXP_CmpAsyncMgrAsyncRemove  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AsyncRemove
	#define EXT_AsyncRemove
	#define GET_AsyncRemove(fl)  CAL_CMGETAPI( "AsyncRemove" ) 
	#define CAL_AsyncRemove pICmpAsyncMgr->IAsyncRemove
	#define CHK_AsyncRemove (pICmpAsyncMgr != NULL)
	#define EXP_AsyncRemove  CAL_CMEXPAPI( "AsyncRemove" ) 
#else /* DYNAMIC_LINK */
	#define USE_AsyncRemove  PFASYNCREMOVE pfAsyncRemove;
	#define EXT_AsyncRemove  extern PFASYNCREMOVE pfAsyncRemove;
	#define GET_AsyncRemove(fl)  s_pfCMGetAPI2( "AsyncRemove", (RTS_VOID_FCTPTR *)&pfAsyncRemove, (fl), 0, 0)
	#define CAL_AsyncRemove  pfAsyncRemove
	#define CHK_AsyncRemove  (pfAsyncRemove != NULL)
	#define EXP_AsyncRemove  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AsyncRemove", (RTS_UINTPTR)AsyncRemove, 0, 0) 
#endif




/**
 * <description> This function removes on async job of a job queue</description>
 * <result>error code</result>
 */
RTS_RESULT CDECL AsyncRemoveAll(void);
typedef RTS_RESULT (CDECL * PFASYNCREMOVEALL) (void);
#if defined(CMPASYNCMGR_NOTIMPLEMENTED) || defined(ASYNCREMOVEALL_NOTIMPLEMENTED)
	#define USE_AsyncRemoveAll
	#define EXT_AsyncRemoveAll
	#define GET_AsyncRemoveAll(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AsyncRemoveAll()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AsyncRemoveAll  FALSE
	#define EXP_AsyncRemoveAll  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AsyncRemoveAll
	#define EXT_AsyncRemoveAll
	#define GET_AsyncRemoveAll(fl)  CAL_CMGETAPI( "AsyncRemoveAll" ) 
	#define CAL_AsyncRemoveAll  AsyncRemoveAll
	#define CHK_AsyncRemoveAll  TRUE
	#define EXP_AsyncRemoveAll  CAL_CMEXPAPI( "AsyncRemoveAll" ) 
#elif defined(MIXED_LINK) && !defined(CMPASYNCMGR_EXTERNAL)
	#define USE_AsyncRemoveAll
	#define EXT_AsyncRemoveAll
	#define GET_AsyncRemoveAll(fl)  CAL_CMGETAPI( "AsyncRemoveAll" ) 
	#define CAL_AsyncRemoveAll  AsyncRemoveAll
	#define CHK_AsyncRemoveAll  TRUE
	#define EXP_AsyncRemoveAll  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AsyncRemoveAll", (RTS_UINTPTR)AsyncRemoveAll, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAsyncMgrAsyncRemoveAll
	#define EXT_CmpAsyncMgrAsyncRemoveAll
	#define GET_CmpAsyncMgrAsyncRemoveAll  ERR_OK
	#define CAL_CmpAsyncMgrAsyncRemoveAll pICmpAsyncMgr->IAsyncRemoveAll
	#define CHK_CmpAsyncMgrAsyncRemoveAll (pICmpAsyncMgr != NULL)
	#define EXP_CmpAsyncMgrAsyncRemoveAll  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AsyncRemoveAll
	#define EXT_AsyncRemoveAll
	#define GET_AsyncRemoveAll(fl)  CAL_CMGETAPI( "AsyncRemoveAll" ) 
	#define CAL_AsyncRemoveAll pICmpAsyncMgr->IAsyncRemoveAll
	#define CHK_AsyncRemoveAll (pICmpAsyncMgr != NULL)
	#define EXP_AsyncRemoveAll  CAL_CMEXPAPI( "AsyncRemoveAll" ) 
#else /* DYNAMIC_LINK */
	#define USE_AsyncRemoveAll  PFASYNCREMOVEALL pfAsyncRemoveAll;
	#define EXT_AsyncRemoveAll  extern PFASYNCREMOVEALL pfAsyncRemoveAll;
	#define GET_AsyncRemoveAll(fl)  s_pfCMGetAPI2( "AsyncRemoveAll", (RTS_VOID_FCTPTR *)&pfAsyncRemoveAll, (fl), 0, 0)
	#define CAL_AsyncRemoveAll  pfAsyncRemoveAll
	#define CHK_AsyncRemoveAll  (pfAsyncRemoveAll != NULL)
	#define EXP_AsyncRemoveAll  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AsyncRemoveAll", (RTS_UINTPTR)AsyncRemoveAll, 0, 0) 
#endif




/**
 * <description> This function retrieves the return value of the job function</description>
 * <param name="hJob" type="IN">Handle to the job</param>
 * <param name="pulReturnVal" type="IN">Pointer to the return value</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AsyncGetJobReturnValue(RTS_HANDLE hJob, RTS_UI32* pulRetVal);
typedef RTS_RESULT (CDECL * PFASYNCGETJOBRETURNVALUE) (RTS_HANDLE hJob, RTS_UI32* pulRetVal);
#if defined(CMPASYNCMGR_NOTIMPLEMENTED) || defined(ASYNCGETJOBRETURNVALUE_NOTIMPLEMENTED)
	#define USE_AsyncGetJobReturnValue
	#define EXT_AsyncGetJobReturnValue
	#define GET_AsyncGetJobReturnValue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AsyncGetJobReturnValue(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AsyncGetJobReturnValue  FALSE
	#define EXP_AsyncGetJobReturnValue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AsyncGetJobReturnValue
	#define EXT_AsyncGetJobReturnValue
	#define GET_AsyncGetJobReturnValue(fl)  CAL_CMGETAPI( "AsyncGetJobReturnValue" ) 
	#define CAL_AsyncGetJobReturnValue  AsyncGetJobReturnValue
	#define CHK_AsyncGetJobReturnValue  TRUE
	#define EXP_AsyncGetJobReturnValue  CAL_CMEXPAPI( "AsyncGetJobReturnValue" ) 
#elif defined(MIXED_LINK) && !defined(CMPASYNCMGR_EXTERNAL)
	#define USE_AsyncGetJobReturnValue
	#define EXT_AsyncGetJobReturnValue
	#define GET_AsyncGetJobReturnValue(fl)  CAL_CMGETAPI( "AsyncGetJobReturnValue" ) 
	#define CAL_AsyncGetJobReturnValue  AsyncGetJobReturnValue
	#define CHK_AsyncGetJobReturnValue  TRUE
	#define EXP_AsyncGetJobReturnValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AsyncGetJobReturnValue", (RTS_UINTPTR)AsyncGetJobReturnValue, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAsyncMgrAsyncGetJobReturnValue
	#define EXT_CmpAsyncMgrAsyncGetJobReturnValue
	#define GET_CmpAsyncMgrAsyncGetJobReturnValue  ERR_OK
	#define CAL_CmpAsyncMgrAsyncGetJobReturnValue pICmpAsyncMgr->IAsyncGetJobReturnValue
	#define CHK_CmpAsyncMgrAsyncGetJobReturnValue (pICmpAsyncMgr != NULL)
	#define EXP_CmpAsyncMgrAsyncGetJobReturnValue  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AsyncGetJobReturnValue
	#define EXT_AsyncGetJobReturnValue
	#define GET_AsyncGetJobReturnValue(fl)  CAL_CMGETAPI( "AsyncGetJobReturnValue" ) 
	#define CAL_AsyncGetJobReturnValue pICmpAsyncMgr->IAsyncGetJobReturnValue
	#define CHK_AsyncGetJobReturnValue (pICmpAsyncMgr != NULL)
	#define EXP_AsyncGetJobReturnValue  CAL_CMEXPAPI( "AsyncGetJobReturnValue" ) 
#else /* DYNAMIC_LINK */
	#define USE_AsyncGetJobReturnValue  PFASYNCGETJOBRETURNVALUE pfAsyncGetJobReturnValue;
	#define EXT_AsyncGetJobReturnValue  extern PFASYNCGETJOBRETURNVALUE pfAsyncGetJobReturnValue;
	#define GET_AsyncGetJobReturnValue(fl)  s_pfCMGetAPI2( "AsyncGetJobReturnValue", (RTS_VOID_FCTPTR *)&pfAsyncGetJobReturnValue, (fl), 0, 0)
	#define CAL_AsyncGetJobReturnValue  pfAsyncGetJobReturnValue
	#define CHK_AsyncGetJobReturnValue  (pfAsyncGetJobReturnValue != NULL)
	#define EXP_AsyncGetJobReturnValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AsyncGetJobReturnValue", (RTS_UINTPTR)AsyncGetJobReturnValue, 0, 0) 
#endif




/**
 * <description> 
 * This function kills a job in any case. Be careful, this could lead to a unsafe condition.
 * This functionality is available for tasks only.
 * NOTE:
 * After killing the job, AsyncRemove must be called to remove the job from the management!
 * </description>
 * <param name="hJob" type="IN">Handle to the job</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL AsyncKill(RTS_HANDLE hJob);
typedef RTS_RESULT (CDECL * PFASYNCKILL) (RTS_HANDLE hJob);
#if defined(CMPASYNCMGR_NOTIMPLEMENTED) || defined(ASYNCKILL_NOTIMPLEMENTED)
	#define USE_AsyncKill
	#define EXT_AsyncKill
	#define GET_AsyncKill(fl)  ERR_NOTIMPLEMENTED
	#define CAL_AsyncKill(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_AsyncKill  FALSE
	#define EXP_AsyncKill  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_AsyncKill
	#define EXT_AsyncKill
	#define GET_AsyncKill(fl)  CAL_CMGETAPI( "AsyncKill" ) 
	#define CAL_AsyncKill  AsyncKill
	#define CHK_AsyncKill  TRUE
	#define EXP_AsyncKill  CAL_CMEXPAPI( "AsyncKill" ) 
#elif defined(MIXED_LINK) && !defined(CMPASYNCMGR_EXTERNAL)
	#define USE_AsyncKill
	#define EXT_AsyncKill
	#define GET_AsyncKill(fl)  CAL_CMGETAPI( "AsyncKill" ) 
	#define CAL_AsyncKill  AsyncKill
	#define CHK_AsyncKill  TRUE
	#define EXP_AsyncKill  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AsyncKill", (RTS_UINTPTR)AsyncKill, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpAsyncMgrAsyncKill
	#define EXT_CmpAsyncMgrAsyncKill
	#define GET_CmpAsyncMgrAsyncKill  ERR_OK
	#define CAL_CmpAsyncMgrAsyncKill pICmpAsyncMgr->IAsyncKill
	#define CHK_CmpAsyncMgrAsyncKill (pICmpAsyncMgr != NULL)
	#define EXP_CmpAsyncMgrAsyncKill  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_AsyncKill
	#define EXT_AsyncKill
	#define GET_AsyncKill(fl)  CAL_CMGETAPI( "AsyncKill" ) 
	#define CAL_AsyncKill pICmpAsyncMgr->IAsyncKill
	#define CHK_AsyncKill (pICmpAsyncMgr != NULL)
	#define EXP_AsyncKill  CAL_CMEXPAPI( "AsyncKill" ) 
#else /* DYNAMIC_LINK */
	#define USE_AsyncKill  PFASYNCKILL pfAsyncKill;
	#define EXT_AsyncKill  extern PFASYNCKILL pfAsyncKill;
	#define GET_AsyncKill(fl)  s_pfCMGetAPI2( "AsyncKill", (RTS_VOID_FCTPTR *)&pfAsyncKill, (fl), 0, 0)
	#define CAL_AsyncKill  pfAsyncKill
	#define CHK_AsyncKill  (pfAsyncKill != NULL)
	#define EXP_AsyncKill  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"AsyncKill", (RTS_UINTPTR)AsyncKill, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFASYNCADD IAsyncAdd;
 	PFASYNCADD2 IAsyncAdd2;
 	PFASYNCADD3 IAsyncAdd3;
 	PFASYNCREMOVE IAsyncRemove;
 	PFASYNCREMOVEALL IAsyncRemoveAll;
 	PFASYNCGETJOBRETURNVALUE IAsyncGetJobReturnValue;
 	PFASYNCKILL IAsyncKill;
 } ICmpAsyncMgr_C;

#ifdef CPLUSPLUS
class ICmpAsyncMgr : public IBase
{
	public:
		virtual RTS_HANDLE CDECL IAsyncAdd(PFASYNCJOBFUNCTION pfAsyncJobFunc, void* pParam, void* pInstance, RTS_UI32* pulState, RTS_I32 bIecFunc, RTS_UI32 ulType, RTS_UI32 ulTimeout, ASYNCJOB_PARAM* pAsyncJobParam, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IAsyncAdd2(ASYNCJOB_INFO2 *pJob) =0;
		virtual RTS_RESULT CDECL IAsyncAdd3(ASYNCJOB_INFO3 *pJob) =0;
		virtual RTS_RESULT CDECL IAsyncRemove(RTS_HANDLE hJob) =0;
		virtual RTS_RESULT CDECL IAsyncRemoveAll(void) =0;
		virtual RTS_RESULT CDECL IAsyncGetJobReturnValue(RTS_HANDLE hJob, RTS_UI32* pulRetVal) =0;
		virtual RTS_RESULT CDECL IAsyncKill(RTS_HANDLE hJob) =0;
};
	#ifndef ITF_CmpAsyncMgr
		#define ITF_CmpAsyncMgr static ICmpAsyncMgr *pICmpAsyncMgr = NULL;
	#endif
	#define EXTITF_CmpAsyncMgr
#else	/*CPLUSPLUS*/
	typedef ICmpAsyncMgr_C		ICmpAsyncMgr;
	#ifndef ITF_CmpAsyncMgr
		#define ITF_CmpAsyncMgr
	#endif
	#define EXTITF_CmpAsyncMgr
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPASYNCMGRITF_H_*/
