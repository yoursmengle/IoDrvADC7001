/**
 * <interfacename>SysMsgQ</interfacename>
 * <description> 
 *	<p>The SysMsgQ interface is projected to get access to the message queue of an operating system.
 *	A message queue can be used for inter task respectively thread communication.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysMsgQ')

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
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysMsgQCreate',`(int iMaxMsgs, int iMaxMsgLength, int iOptions, RTS_RESULT *pResult)')

/**
 * <description>Function to delete a message queue</description>
 * <param name="hMsgQ" type="IN">Handle to the message queue</param>
 * <result>error code</result>
 */
DEF_DELETEITF_API(`RTS_RESULT',`CDECL',`SysMsgQDelete',`(RTS_HANDLE hMsgQ)')

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
DEF_HANDLEITF_API(`int',`CDECL',`SysMsgQSend',`(RTS_HANDLE hMsgQ, unsigned char *pbySendMsg, int iSendMsgLen, unsigned long ulTimeout, int iPriority, RTS_RESULT *pResult)')

/**
 * <description> Function to receive a message via a message queue </description>
 * <param name="hMsgQ" type="IN">Handle to the message queue</param>
 * <param name="pbyRecvMsg" type="IN">Pointer to receive message</param>
 * <param name="iMaxMsgLen" type="IN">Maximum number of bytes to receive</param>
 * <param name="ulTimeout" type="IN">Timeout to sent (see category Message Queue Timeouts)</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of bytes received, 0 if failed</result>
 */
DEF_HANDLEITF_API(`int',`CDECL',`SysMsgQRecv',`(RTS_HANDLE hMsgQ, unsigned char *pbyRecvMsg, int iMaxMsgLen, unsigned long ulTimeout, RTS_RESULT *pResult)')

/**
 * <description>Function to check number of messages actual in the queue</description>
 * <param name="hMsgQ" type="IN">Handle to the message queue</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of message in the queue</result>
 */
DEF_HANDLEITF_API(`int',`CDECL',`SysMsgQGetNumOfMsgs',`(RTS_HANDLE hMsgQ, RTS_RESULT *pResult)')

#ifdef __cplusplus
}
#endif
