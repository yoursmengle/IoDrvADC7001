 /**
 * <interfacename>SysMsgQ</interfacename>
 * <description> 
 *	<p>The SysMsgQ interface is projected to get access to the message queue of an operating system.
 *	A message queue can be used for inter task respectively thread communication.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSMSGQITF_H_
#define _SYSMSGQITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"


/**
 * <category>Message Queue Options</category>
 * <description>Type of the message queue</description>
 */
#define MSGQ_FIFO			0
#define MSGQ_PRIORITY		1

/**
 * <category>Message Queue Entry Priority</category>
 * <description>Priority of a message queue entry</description>
 */
#define MSGQ_PRIO_LOW		0
#define MSGQ_PRIO_NORMAL	1
#define MSGQ_PRIO_HIGH		2

/**
 * <category>Message Queue Timeouts</category>
 * <description>Timeouts for operations</description>
 */
#define MSGQ_TIMEOUT_NO_WAIT		0
#define MSGQ_TIMEOUT_INFINITE		UINT32_MAX

#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysMsgQOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysMsgQOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>Function to create a new message queue</description>
 * <param name="iMaxMsgs" type="IN">Maximum number of entries in the message queue</param>
 * <param name="iOptions" type="IN">Options of the message queue (see category Message Queue Options)</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the message queue or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL SysMsgQCreate(int iMaxMsgs, int iMaxMsgLength, int iOptions, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSMSGQCREATE) (int iMaxMsgs, int iMaxMsgLength, int iOptions, RTS_RESULT *pResult);
#if defined(SYSMSGQ_NOTIMPLEMENTED) || defined(SYSMSGQCREATE_NOTIMPLEMENTED)
	#define USE_SysMsgQCreate
	#define EXT_SysMsgQCreate
	#define GET_SysMsgQCreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMsgQCreate(p0,p1,p2,p3)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysMsgQCreate  FALSE
	#define EXP_SysMsgQCreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMsgQCreate
	#define EXT_SysMsgQCreate
	#define GET_SysMsgQCreate(fl)  CAL_CMGETAPI( "SysMsgQCreate" ) 
	#define CAL_SysMsgQCreate  SysMsgQCreate
	#define CHK_SysMsgQCreate  TRUE
	#define EXP_SysMsgQCreate  CAL_CMEXPAPI( "SysMsgQCreate" ) 
#elif defined(MIXED_LINK) && !defined(SYSMSGQ_EXTERNAL)
	#define USE_SysMsgQCreate
	#define EXT_SysMsgQCreate
	#define GET_SysMsgQCreate(fl)  CAL_CMGETAPI( "SysMsgQCreate" ) 
	#define CAL_SysMsgQCreate  SysMsgQCreate
	#define CHK_SysMsgQCreate  TRUE
	#define EXP_SysMsgQCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMsgQCreate", (RTS_UINTPTR)SysMsgQCreate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysMsgQSysMsgQCreate
	#define EXT_SysMsgQSysMsgQCreate
	#define GET_SysMsgQSysMsgQCreate  ERR_OK
	#define CAL_SysMsgQSysMsgQCreate  ((ISysMsgQ*)s_pfCMCreateInstance(CLASSID_CSysMsgQ, NULL))->ISysMsgQCreate
	#define CHK_SysMsgQSysMsgQCreate	(s_pfCMCreateInstance != NULL && pISysMsgQ != NULL)
	#define EXP_SysMsgQSysMsgQCreate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMsgQCreate
	#define EXT_SysMsgQCreate
	#define GET_SysMsgQCreate(fl)  CAL_CMGETAPI( "SysMsgQCreate" ) 
	#define CAL_SysMsgQCreate  ((ISysMsgQ*)s_pfCMCreateInstance(CLASSID_CSysMsgQ, NULL))->ISysMsgQCreate
	#define CHK_SysMsgQCreate	(s_pfCMCreateInstance != NULL && pISysMsgQ != NULL)
	#define EXP_SysMsgQCreate  CAL_CMEXPAPI( "SysMsgQCreate" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMsgQCreate  PFSYSMSGQCREATE pfSysMsgQCreate;
	#define EXT_SysMsgQCreate  extern PFSYSMSGQCREATE pfSysMsgQCreate;
	#define GET_SysMsgQCreate(fl)  s_pfCMGetAPI2( "SysMsgQCreate", (RTS_VOID_FCTPTR *)&pfSysMsgQCreate, (fl), 0, 0)
	#define CAL_SysMsgQCreate  pfSysMsgQCreate
	#define CHK_SysMsgQCreate  (pfSysMsgQCreate != NULL)
	#define EXP_SysMsgQCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMsgQCreate", (RTS_UINTPTR)SysMsgQCreate, 0, 0) 
#endif




/**
 * <description>Function to delete a message queue</description>
 * <param name="hMsgQ" type="IN">Handle to the message queue</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysMsgQDelete(RTS_HANDLE hMsgQ);
typedef RTS_RESULT (CDECL * PFSYSMSGQDELETE) (RTS_HANDLE hMsgQ);
#if defined(SYSMSGQ_NOTIMPLEMENTED) || defined(SYSMSGQDELETE_NOTIMPLEMENTED)
	#define USE_SysMsgQDelete
	#define EXT_SysMsgQDelete
	#define GET_SysMsgQDelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMsgQDelete(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMsgQDelete  FALSE
	#define EXP_SysMsgQDelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMsgQDelete
	#define EXT_SysMsgQDelete
	#define GET_SysMsgQDelete(fl)  CAL_CMGETAPI( "SysMsgQDelete" ) 
	#define CAL_SysMsgQDelete  SysMsgQDelete
	#define CHK_SysMsgQDelete  TRUE
	#define EXP_SysMsgQDelete  CAL_CMEXPAPI( "SysMsgQDelete" ) 
#elif defined(MIXED_LINK) && !defined(SYSMSGQ_EXTERNAL)
	#define USE_SysMsgQDelete
	#define EXT_SysMsgQDelete
	#define GET_SysMsgQDelete(fl)  CAL_CMGETAPI( "SysMsgQDelete" ) 
	#define CAL_SysMsgQDelete  SysMsgQDelete
	#define CHK_SysMsgQDelete  TRUE
	#define EXP_SysMsgQDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMsgQDelete", (RTS_UINTPTR)SysMsgQDelete, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysMsgQSysMsgQDelete
	#define EXT_SysMsgQSysMsgQDelete
	#define GET_SysMsgQSysMsgQDelete  ERR_OK
	#define CAL_SysMsgQSysMsgQDelete(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ISysMsgQ*)p0)->ISysMsgQDelete())
	#define CHK_SysMsgQSysMsgQDelete  TRUE
	#define EXP_SysMsgQSysMsgQDelete  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMsgQDelete
	#define EXT_SysMsgQDelete
	#define GET_SysMsgQDelete(fl)  CAL_CMGETAPI( "SysMsgQDelete" ) 
	#define CAL_SysMsgQDelete(p0) (((RTS_HANDLE)p0 == NULL || (RTS_HANDLE)p0 == RTS_INVALID_HANDLE) ? ERR_PARAMETER : ((ISysMsgQ*)p0)->ISysMsgQDelete())
	#define CHK_SysMsgQDelete  TRUE
	#define EXP_SysMsgQDelete  CAL_CMEXPAPI( "SysMsgQDelete" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMsgQDelete  PFSYSMSGQDELETE pfSysMsgQDelete;
	#define EXT_SysMsgQDelete  extern PFSYSMSGQDELETE pfSysMsgQDelete;
	#define GET_SysMsgQDelete(fl)  s_pfCMGetAPI2( "SysMsgQDelete", (RTS_VOID_FCTPTR *)&pfSysMsgQDelete, (fl), 0, 0)
	#define CAL_SysMsgQDelete  pfSysMsgQDelete
	#define CHK_SysMsgQDelete  (pfSysMsgQDelete != NULL)
	#define EXP_SysMsgQDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMsgQDelete", (RTS_UINTPTR)SysMsgQDelete, 0, 0) 
#endif




/**
 * <description>Function to send a message via a message queue</description>
 * <param name="hMsgQ" type="IN">Handle to the message queue</param>
 * <param name="pbySendMsg" type="IN">Pointer to the message to sent</param>
 * <param name="iSendMsgLen" type="IN">Number of bytes to sent</param>
 * <param name="ulTimeout" type="IN">Timeout to sent (see category Message Queue Timeouts)</param>
 * <param name="iPriority" type="IN">Priority to sent (see category Message Queue Priorities)</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of bytes sent, 0 if failed</result>
 */
int CDECL SysMsgQSend(RTS_HANDLE hMsgQ, unsigned char *pbySendMsg, int iSendMsgLen, unsigned long ulTimeout, int iPriority, RTS_RESULT *pResult);
typedef int (CDECL * PFSYSMSGQSEND) (RTS_HANDLE hMsgQ, unsigned char *pbySendMsg, int iSendMsgLen, unsigned long ulTimeout, int iPriority, RTS_RESULT *pResult);
#if defined(SYSMSGQ_NOTIMPLEMENTED) || defined(SYSMSGQSEND_NOTIMPLEMENTED)
	#define USE_SysMsgQSend
	#define EXT_SysMsgQSend
	#define GET_SysMsgQSend(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMsgQSend(p0,p1,p2,p3,p4,p5)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysMsgQSend  FALSE
	#define EXP_SysMsgQSend  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMsgQSend
	#define EXT_SysMsgQSend
	#define GET_SysMsgQSend(fl)  CAL_CMGETAPI( "SysMsgQSend" ) 
	#define CAL_SysMsgQSend  SysMsgQSend
	#define CHK_SysMsgQSend  TRUE
	#define EXP_SysMsgQSend  CAL_CMEXPAPI( "SysMsgQSend" ) 
#elif defined(MIXED_LINK) && !defined(SYSMSGQ_EXTERNAL)
	#define USE_SysMsgQSend
	#define EXT_SysMsgQSend
	#define GET_SysMsgQSend(fl)  CAL_CMGETAPI( "SysMsgQSend" ) 
	#define CAL_SysMsgQSend  SysMsgQSend
	#define CHK_SysMsgQSend  TRUE
	#define EXP_SysMsgQSend  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMsgQSend", (RTS_UINTPTR)SysMsgQSend, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysMsgQSysMsgQSend
	#define EXT_SysMsgQSysMsgQSend
	#define GET_SysMsgQSysMsgQSend  ERR_OK
	#define CAL_SysMsgQSysMsgQSend(p0,p1,p2,p3,p4,p5)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysMsgQ->ISysMsgQSend(p1,p2,p3,p4,p5) : ((ISysMsgQ*)p0)->ISysMsgQSend(p1,p2,p3,p4,p5))
	#define CHK_SysMsgQSysMsgQSend  (pISysMsgQ != NULL)
	#define EXP_SysMsgQSysMsgQSend  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMsgQSend
	#define EXT_SysMsgQSend
	#define GET_SysMsgQSend(fl)  CAL_CMGETAPI( "SysMsgQSend" ) 
	#define CAL_SysMsgQSend(p0,p1,p2,p3,p4,p5)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysMsgQ->ISysMsgQSend(p1,p2,p3,p4,p5) : ((ISysMsgQ*)p0)->ISysMsgQSend(p1,p2,p3,p4,p5))
	#define CHK_SysMsgQSend  (pISysMsgQ != NULL)
	#define EXP_SysMsgQSend  CAL_CMEXPAPI( "SysMsgQSend" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMsgQSend  PFSYSMSGQSEND pfSysMsgQSend;
	#define EXT_SysMsgQSend  extern PFSYSMSGQSEND pfSysMsgQSend;
	#define GET_SysMsgQSend(fl)  s_pfCMGetAPI2( "SysMsgQSend", (RTS_VOID_FCTPTR *)&pfSysMsgQSend, (fl), 0, 0)
	#define CAL_SysMsgQSend  pfSysMsgQSend
	#define CHK_SysMsgQSend  (pfSysMsgQSend != NULL)
	#define EXP_SysMsgQSend  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMsgQSend", (RTS_UINTPTR)SysMsgQSend, 0, 0) 
#endif




/**
 * <description> Function to receive a message via a message queue </description>
 * <param name="hMsgQ" type="IN">Handle to the message queue</param>
 * <param name="pbyRecvMsg" type="IN">Pointer to receive message</param>
 * <param name="iMaxMsgLen" type="IN">Maximum number of bytes to receive</param>
 * <param name="ulTimeout" type="IN">Timeout to sent (see category Message Queue Timeouts)</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of bytes received, 0 if failed</result>
 */
int CDECL SysMsgQRecv(RTS_HANDLE hMsgQ, unsigned char *pbyRecvMsg, int iMaxMsgLen, unsigned long ulTimeout, RTS_RESULT *pResult);
typedef int (CDECL * PFSYSMSGQRECV) (RTS_HANDLE hMsgQ, unsigned char *pbyRecvMsg, int iMaxMsgLen, unsigned long ulTimeout, RTS_RESULT *pResult);
#if defined(SYSMSGQ_NOTIMPLEMENTED) || defined(SYSMSGQRECV_NOTIMPLEMENTED)
	#define USE_SysMsgQRecv
	#define EXT_SysMsgQRecv
	#define GET_SysMsgQRecv(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMsgQRecv(p0,p1,p2,p3,p4)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysMsgQRecv  FALSE
	#define EXP_SysMsgQRecv  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMsgQRecv
	#define EXT_SysMsgQRecv
	#define GET_SysMsgQRecv(fl)  CAL_CMGETAPI( "SysMsgQRecv" ) 
	#define CAL_SysMsgQRecv  SysMsgQRecv
	#define CHK_SysMsgQRecv  TRUE
	#define EXP_SysMsgQRecv  CAL_CMEXPAPI( "SysMsgQRecv" ) 
#elif defined(MIXED_LINK) && !defined(SYSMSGQ_EXTERNAL)
	#define USE_SysMsgQRecv
	#define EXT_SysMsgQRecv
	#define GET_SysMsgQRecv(fl)  CAL_CMGETAPI( "SysMsgQRecv" ) 
	#define CAL_SysMsgQRecv  SysMsgQRecv
	#define CHK_SysMsgQRecv  TRUE
	#define EXP_SysMsgQRecv  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMsgQRecv", (RTS_UINTPTR)SysMsgQRecv, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysMsgQSysMsgQRecv
	#define EXT_SysMsgQSysMsgQRecv
	#define GET_SysMsgQSysMsgQRecv  ERR_OK
	#define CAL_SysMsgQSysMsgQRecv(p0,p1,p2,p3,p4)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysMsgQ->ISysMsgQRecv(p1,p2,p3,p4) : ((ISysMsgQ*)p0)->ISysMsgQRecv(p1,p2,p3,p4))
	#define CHK_SysMsgQSysMsgQRecv  (pISysMsgQ != NULL)
	#define EXP_SysMsgQSysMsgQRecv  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMsgQRecv
	#define EXT_SysMsgQRecv
	#define GET_SysMsgQRecv(fl)  CAL_CMGETAPI( "SysMsgQRecv" ) 
	#define CAL_SysMsgQRecv(p0,p1,p2,p3,p4)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysMsgQ->ISysMsgQRecv(p1,p2,p3,p4) : ((ISysMsgQ*)p0)->ISysMsgQRecv(p1,p2,p3,p4))
	#define CHK_SysMsgQRecv  (pISysMsgQ != NULL)
	#define EXP_SysMsgQRecv  CAL_CMEXPAPI( "SysMsgQRecv" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMsgQRecv  PFSYSMSGQRECV pfSysMsgQRecv;
	#define EXT_SysMsgQRecv  extern PFSYSMSGQRECV pfSysMsgQRecv;
	#define GET_SysMsgQRecv(fl)  s_pfCMGetAPI2( "SysMsgQRecv", (RTS_VOID_FCTPTR *)&pfSysMsgQRecv, (fl), 0, 0)
	#define CAL_SysMsgQRecv  pfSysMsgQRecv
	#define CHK_SysMsgQRecv  (pfSysMsgQRecv != NULL)
	#define EXP_SysMsgQRecv  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMsgQRecv", (RTS_UINTPTR)SysMsgQRecv, 0, 0) 
#endif




/**
 * <description>Function to check number of messages actual in the queue</description>
 * <param name="hMsgQ" type="IN">Handle to the message queue</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of message in the queue</result>
 */
int CDECL SysMsgQGetNumOfMsgs(RTS_HANDLE hMsgQ, RTS_RESULT *pResult);
typedef int (CDECL * PFSYSMSGQGETNUMOFMSGS) (RTS_HANDLE hMsgQ, RTS_RESULT *pResult);
#if defined(SYSMSGQ_NOTIMPLEMENTED) || defined(SYSMSGQGETNUMOFMSGS_NOTIMPLEMENTED)
	#define USE_SysMsgQGetNumOfMsgs
	#define EXT_SysMsgQGetNumOfMsgs
	#define GET_SysMsgQGetNumOfMsgs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMsgQGetNumOfMsgs(p0,p1)  (int)ERR_NOTIMPLEMENTED
	#define CHK_SysMsgQGetNumOfMsgs  FALSE
	#define EXP_SysMsgQGetNumOfMsgs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMsgQGetNumOfMsgs
	#define EXT_SysMsgQGetNumOfMsgs
	#define GET_SysMsgQGetNumOfMsgs(fl)  CAL_CMGETAPI( "SysMsgQGetNumOfMsgs" ) 
	#define CAL_SysMsgQGetNumOfMsgs  SysMsgQGetNumOfMsgs
	#define CHK_SysMsgQGetNumOfMsgs  TRUE
	#define EXP_SysMsgQGetNumOfMsgs  CAL_CMEXPAPI( "SysMsgQGetNumOfMsgs" ) 
#elif defined(MIXED_LINK) && !defined(SYSMSGQ_EXTERNAL)
	#define USE_SysMsgQGetNumOfMsgs
	#define EXT_SysMsgQGetNumOfMsgs
	#define GET_SysMsgQGetNumOfMsgs(fl)  CAL_CMGETAPI( "SysMsgQGetNumOfMsgs" ) 
	#define CAL_SysMsgQGetNumOfMsgs  SysMsgQGetNumOfMsgs
	#define CHK_SysMsgQGetNumOfMsgs  TRUE
	#define EXP_SysMsgQGetNumOfMsgs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMsgQGetNumOfMsgs", (RTS_UINTPTR)SysMsgQGetNumOfMsgs, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysMsgQSysMsgQGetNumOfMsgs
	#define EXT_SysMsgQSysMsgQGetNumOfMsgs
	#define GET_SysMsgQSysMsgQGetNumOfMsgs  ERR_OK
	#define CAL_SysMsgQSysMsgQGetNumOfMsgs(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysMsgQ->ISysMsgQGetNumOfMsgs(p1) : ((ISysMsgQ*)p0)->ISysMsgQGetNumOfMsgs(p1))
	#define CHK_SysMsgQSysMsgQGetNumOfMsgs  (pISysMsgQ != NULL)
	#define EXP_SysMsgQSysMsgQGetNumOfMsgs  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMsgQGetNumOfMsgs
	#define EXT_SysMsgQGetNumOfMsgs
	#define GET_SysMsgQGetNumOfMsgs(fl)  CAL_CMGETAPI( "SysMsgQGetNumOfMsgs" ) 
	#define CAL_SysMsgQGetNumOfMsgs(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysMsgQ->ISysMsgQGetNumOfMsgs(p1) : ((ISysMsgQ*)p0)->ISysMsgQGetNumOfMsgs(p1))
	#define CHK_SysMsgQGetNumOfMsgs  (pISysMsgQ != NULL)
	#define EXP_SysMsgQGetNumOfMsgs  CAL_CMEXPAPI( "SysMsgQGetNumOfMsgs" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMsgQGetNumOfMsgs  PFSYSMSGQGETNUMOFMSGS pfSysMsgQGetNumOfMsgs;
	#define EXT_SysMsgQGetNumOfMsgs  extern PFSYSMSGQGETNUMOFMSGS pfSysMsgQGetNumOfMsgs;
	#define GET_SysMsgQGetNumOfMsgs(fl)  s_pfCMGetAPI2( "SysMsgQGetNumOfMsgs", (RTS_VOID_FCTPTR *)&pfSysMsgQGetNumOfMsgs, (fl), 0, 0)
	#define CAL_SysMsgQGetNumOfMsgs  pfSysMsgQGetNumOfMsgs
	#define CHK_SysMsgQGetNumOfMsgs  (pfSysMsgQGetNumOfMsgs != NULL)
	#define EXP_SysMsgQGetNumOfMsgs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMsgQGetNumOfMsgs", (RTS_UINTPTR)SysMsgQGetNumOfMsgs, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSMSGQCREATE ISysMsgQCreate;
 	PFSYSMSGQDELETE ISysMsgQDelete;
 	PFSYSMSGQSEND ISysMsgQSend;
 	PFSYSMSGQRECV ISysMsgQRecv;
 	PFSYSMSGQGETNUMOFMSGS ISysMsgQGetNumOfMsgs;
 } ISysMsgQ_C;

#ifdef CPLUSPLUS
class ISysMsgQ : public IBase
{
	public:
		virtual RTS_HANDLE CDECL ISysMsgQCreate(int iMaxMsgs, int iMaxMsgLength, int iOptions, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISysMsgQDelete(void) =0;
		virtual int CDECL ISysMsgQSend(unsigned char *pbySendMsg, int iSendMsgLen, unsigned long ulTimeout, int iPriority, RTS_RESULT *pResult) =0;
		virtual int CDECL ISysMsgQRecv(unsigned char *pbyRecvMsg, int iMaxMsgLen, unsigned long ulTimeout, RTS_RESULT *pResult) =0;
		virtual int CDECL ISysMsgQGetNumOfMsgs(RTS_RESULT *pResult) =0;
};
	#ifndef ITF_SysMsgQ
		#define ITF_SysMsgQ static ISysMsgQ *pISysMsgQ = NULL;
	#endif
	#define EXTITF_SysMsgQ
#else	/*CPLUSPLUS*/
	typedef ISysMsgQ_C		ISysMsgQ;
	#ifndef ITF_SysMsgQ
		#define ITF_SysMsgQ
	#endif
	#define EXTITF_SysMsgQ
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSMSGQITF_H_*/
