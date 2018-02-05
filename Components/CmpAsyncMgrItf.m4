/**
 * <interfacename>CmpAsyncMgr</interfacename>
 * <description> 
 *	<p>Interface of the asynchronous job manager. This job manager enables, to execute synchronous jobs
 *	asynchronously.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpAsyncMgr')

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
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

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

DEF_API(`void',`CDECL',`asyncadd',`(asyncadd_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x10FA73A4),0x03050500)

/**
 * <description>asyncgetjobreturnvalue</description>
 */
typedef struct tagasyncgetjobreturnvalue_struct
{
	RTS_IEC_HANDLE hJob;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pulReturnVal;		/* VAR_INPUT */	
	RTS_IEC_RESULT AsyncGetJobReturnValue;	/* VAR_OUTPUT */	
} asyncgetjobreturnvalue_struct;

DEF_API(`void',`CDECL',`asyncgetjobreturnvalue',`(asyncgetjobreturnvalue_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xFD4D0A88),0x03050500)

/**
 * <description>asynckill</description>
 */
typedef struct tagasynckill_struct
{
	RTS_IEC_HANDLE hJob;				/* VAR_INPUT */	
	RTS_IEC_RESULT AsyncKill;			/* VAR_OUTPUT */	
} asynckill_struct;

DEF_API(`void',`CDECL',`asynckill',`(asynckill_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xAE42472A),0x03050500)

/**
 * <description>asyncremove</description>
 */
typedef struct tagasyncremove_struct
{
	RTS_IEC_HANDLE hJob;				/* VAR_INPUT */	
	RTS_IEC_RESULT AsyncRemove;			/* VAR_OUTPUT */	
} asyncremove_struct;

DEF_API(`void',`CDECL',`asyncremove',`(asyncremove_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCD84446E),0x03050500)

/**
 * <description>asyncremoveall</description>
 */
typedef struct tagasyncremoveall_struct
{
	RTS_IEC_RESULT AsyncRemoveAll;		/* VAR_OUTPUT */	
} asyncremoveall_struct;

DEF_API(`void',`CDECL',`asyncremoveall',`(asyncremoveall_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x17DBEEFC),0x03050500)

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
DEF_ITF_API(`RTS_HANDLE', `CDECL', `AsyncAdd', `(PFASYNCJOBFUNCTION pfAsyncJobFunc, void* pParam, void* pInstance, RTS_UI32* pulState, RTS_I32 bIecFunc, RTS_UI32 ulType, RTS_UI32 ulTimeout, ASYNCJOB_PARAM* pAsyncJobParam, RTS_RESULT *pResult)')

/**
 * <description> This function adds a new async job in a jobqueue. This function must be used, if the job is removed in the job handler!</description>
 * <param name="pJobInfo" type="IN">Pointer to job info with all parameters</param>
 * <param name="phJob" type="OUT">Job handle</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AsyncAdd2', `(ASYNCJOB_INFO2 *pJob)')

/**
 * <description> This function adds a new async job in a jobqueue. This function must be used, if the job is removed in the job handler!</description>
 * <param name="pJobInfo" type="IN">Pointer to job info with all parameters</param>
 * <param name="phJob" type="OUT">Job handle</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AsyncAdd3', `(ASYNCJOB_INFO3 *pJob)')

/**
 * <description> This function removes on async job of a job queue</description>
 * <param name="hJob" type="IN">Handle to the job</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AsyncRemove', `(RTS_HANDLE hJob)')

/**
 * <description> This function removes on async job of a job queue</description>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AsyncRemoveAll', `(void)')

/**
 * <description> This function retrieves the return value of the job function</description>
 * <param name="hJob" type="IN">Handle to the job</param>
 * <param name="pulReturnVal" type="IN">Pointer to the return value</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AsyncGetJobReturnValue', `(RTS_HANDLE hJob, RTS_UI32* pulRetVal)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `AsyncKill', `(RTS_HANDLE hJob)')

#ifdef __cplusplus
}
#endif
