SET_INTERFACE_NAME(`CmpCAACanL2')

#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAACanL2.h"
#include "CAACanL2I.h"
#include "CAACanMiniDriver.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Global setting for all CAN Networks. If 1 Baudrate used in DriverOpen will be saved to Net.X.DefaultBaudrate.
 * </description>
 */
#define CANL2KEY_INT_PERSISTENTBAUDRATE			"PersistentBaudrate"
#ifndef CANL2KEY_INT_PERSISTENTBAUDRATE_DEFAULT
	#define CANL2KEY_INT_PERSISTENTBAUDRATE_DEFAULT		0
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting prefix for CANL2 Networks.</description>
 */
#define CANL2_STRING_NET						"Net"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Default Baudrate in kbit/s which should be used if CAN interface will be opened with baudrate 0.
 * Example: Net.0.Baudrate = 1000
 * </description>
 */
#define CANL2KEY_INT_BAUDRATE					"DefaultBaudrate"
#ifndef CANL2KEY_INT_BAUDRATE_DEFAULT
	#define CANL2KEY_INT_BAUDRATE_DEFAULT		0
#endif


/* Basic Functions */
DEF_ITF_API(`CAA_HANDLE',`CDECL',`CL2_DriverOpenH',`(unsigned char ucNetId, unsigned short usBaudrate, CAA_BOOL xSupport29Bit, CAA_COUNT ctMessages, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_SIZE',`CDECL',`CL2_DriverGetSize',`(unsigned char ucNetId, CAA_BOOL xSupport29Bit, CAA_COUNT ctMessages, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`CL2_DriverOpenP',`(unsigned char ucNetId, unsigned short usBaudrate, CAA_BOOL xSupport29Bit, CAA_SIZE szMemSize, CAA_PVOID pMemory, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`CL2_DriverClose',`(CAA_HANDLE hDriver)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`CL2_CreateMessage',`(CAA_HANDLE hDriver, CL2I_COBID cobId, unsigned char ucLength, CAA_BOOL xRTR, CAA_BOOL x29BitId, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`CL2_FreeMessage',`(CAA_HANDLE hMessage)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`CL2_CloneMessage',`(CAA_HANDLE hMessage, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`CL2_CreateSingleIdReceiver',`(CAA_HANDLE hDriver, CL2I_COBID cobId, CAA_BOOL xRTR, CAA_BOOL x29BitId, CAA_BOOL xTransmit, CAA_BOOL xAlwaysNewest, CAA_ENUM eEvent, CAA_BOOL xEnableSyncWindow, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`CL2_CreateIdAreaReceiver',`(CAA_HANDLE hDriver, CAA_BOOL xAlwaysNewest, CAA_ENUM eEvent, CAA_BOOL xEnableSyncWindow, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`CL2_CreateIdAreaReceiverEx',`(CAA_HANDLE hDriver, CAA_BOOL xAlwaysNewest, CAA_BOOL xReverse, CAA_ENUM eEvent, CAA_BOOL xEnableSyncWindow, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`CL2_RegisterIdArea',`(CAA_HANDLE hReceiverId, CL2I_COBID cobIdStart, CL2I_COBID cobIdEnd, CAA_BOOL xRTRValue, CAA_BOOL xRTRMask, CAA_BOOL x29BitIdValue, CAA_BOOL x29BitIdMask, CAA_BOOL xTransmitValue, CAA_BOOL xTransmitMask)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`CL2_UnregisterIdArea',`(CAA_HANDLE hReceiverId, CL2I_COBID cobIdStart, CL2I_COBID cobIdEnd,  CAA_BOOL xRTRValue, CAA_BOOL xRTRMask, CAA_BOOL x29BitIdValue, CAA_BOOL x29BitIdMask, CAA_BOOL xTransmitValue, CAA_BOOL xTransmitMask)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`CL2_CreateMaskReceiver',`(CAA_HANDLE hDriver, CL2I_COBID cobIdValue, CL2I_COBID cobIdMask, CAA_BOOL xRTRValue, CAA_BOOL xRTRMask, CAA_BOOL x29BitIdValue, CAA_BOOL x29BitIdMask, CAA_BOOL xTransmitValue, CAA_BOOL xTransmitMask, CAA_BOOL xAlwaysNewest, CAA_ENUM eEvent, CAA_BOOL xEnableSyncWindow, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`CL2_CreateArrayReceiver',`(CAA_HANDLE hDriver, CL2I_ARRAYRECV_ENTRY* paSortedCOBIDs, CAA_COUNT ctCOBIDs, CAA_ENUM eEvent, CAA_BOOL xEnableSyncWindow, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`CL2_DeleteReceiver',`(CAA_HANDLE hReceiverId)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`CL2_Read',`(CAA_HANDLE hReceiverId, CAA_COUNT* pctMsgLeft, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`CL2_ReadArrayReceiver',`(CAA_HANDLE hArrayReceiver, CAA_COUNT ctIndex, CAA_COUNT* pctMsgLeft, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`CL2_Write',`(CAA_HANDLE hDriver, CAA_HANDLE hMessage, unsigned char ucPrio, CAA_BOOL xEnableSyncWindow)')

/* Cyclic Custom Services */
DEF_ITF_API(`CAA_HANDLE',`CDECL',`CL2_CstCycleOpen',`(CAA_HANDLE hDriver, CAA_ENUM eCstEvent, unsigned short usPrio, CAA_BOOL xEnableSyncWindow, CAA_UDINT ulCstCycle, CAA_UDINT ulCstForewarnTime, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`CL2_CstCycleUpdate',`(CAA_HANDLE hCstCycle, CAA_HANDLE hMessage, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`CL2_CstCycleStart',`(CAA_HANDLE hCstCycle)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`CL2_CstCycleStop',`(CAA_HANDLE hCstCycle)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`CL2_CstCycleClose',`(CAA_HANDLE hCstCycle, CAA_ERROR* peError)')

/* Diagnostic Information */
DEF_ITF_API(`unsigned short',`CDECL',`CL2_GetBaudrate',`(CAA_HANDLE hDriver, CAA_ERROR* peError)')
DEF_ITF_API(`unsigned short',`CDECL',`CL2_GetBusload',`(CAA_HANDLE hDriver, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ENUM',`CDECL',`CL2_GetBusState',`(CAA_HANDLE hDriver, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_COUNT',`CDECL',`CL2_GetReceiveCounter',`(CAA_HANDLE hDriver, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_COUNT',`CDECL',`CL2_GetLostCounter',`(CAA_HANDLE hDriver, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_COUNT',`CDECL',`CL2_GetTransmitCounter',`(CAA_HANDLE hDriver, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_COUNT',`CDECL',`CL2_GetTransmitErrorCounter',`(CAA_HANDLE hDriver, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_COUNT',`CDECL',`CL2_GetReceiveErrorCounter',`(CAA_HANDLE hDriver, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`CL2_IsSendingActive',`(CAA_HANDLE hDriver, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`CL2_GetBusAlarm',`(CAA_HANDLE hDriver, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`CL2_ResetBusAlarm',`(CAA_HANDLE hDriver)')
DEF_ITF_API(`CAA_COUNT',`CDECL',`CL2_GetTransmitQueueLength',`(CAA_HANDLE hDriver, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_COUNT',`CDECL',`CL2_GetReceiveQueueLength',`(CAA_HANDLE hDriver, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_COUNT',`CDECL',`CL2_GetTransmitPoolSize',`(CAA_HANDLE hDriver, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_COUNT',`CDECL',`CL2_GetReceivePoolSize',`(CAA_HANDLE hDriver, CAA_ERROR* peError)')

/* Extended Functionality */
DEF_ITF_API(`CAA_ERROR',`CDECL',`CL2_DisableSyncService',`(CAA_HANDLE hDriver)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`CL2_DisableTimeService',`(CAA_HANDLE hDriver)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`CL2_EnableSyncService',`(CAA_HANDLE hDriver, CL2I_COBID cobId, CAA_BOOL xSyncProducer, CAA_BOOL xEnableSyncEvent, CAA_UDINT ulSyncCycle, CAA_UDINT ulSyncWindowLength, CAA_UDINT ulSyncForewarnTime)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`CL2_EnableTimeService',`(CAA_HANDLE hDriver, CL2I_COBID cobId, CAA_BOOL xTimeProducer, CAA_BOOL xEnableTimeEvent, CAA_UDINT ulTimeCycle, CAA_UDINT ulTimeForewarnTime)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`CL2_UpdateTimeService',`(CAA_HANDLE hDriver, CAA_UDINT ulTime, CAA_UDINT ulDate)')

/* Message Information */
DEF_ITF_API(`CL2I_DATA*',`CDECL',`CL2_GetMessageDataPointer',`(CAA_HANDLE hMessage, CAA_ERROR* peError)')
DEF_ITF_API(`CL2I_COBID',`CDECL',`CL2_GetMessageId',`(CAA_HANDLE hMessage, CAA_ERROR* peError)')
DEF_ITF_API(`unsigned char',`CDECL',`CL2_GetMessageLength',`(CAA_HANDLE hMessage, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_UDINT',`CDECL',`CL2_GetTimeStamp',`(CAA_HANDLE hMessage, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`CL2_Is29BitIdMessage',`(CAA_HANDLE hMessage, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`CL2_IsRTRMessage',`(CAA_HANDLE hMessage, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`CL2_IsTransmitMessage',`(CAA_HANDLE hMessage, CAA_ERROR* peError)')
DEF_ITF_API(`unsigned char',`CDECL',`CL2_GetNetId',`(CAA_HANDLE hMessage, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_COUNT',`CDECL',`CL2_LostMessages',`(CAA_HANDLE hReceiverId, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_COUNT',`CDECL',`CL2_GetMsgCount',`(CAA_HANDLE hReceiverId, CAA_ERROR* peError)')

/* CiA 303 Indicator services */
DEF_ITF_API(`unsigned char',`CDECL',`CL2_GetCiAState',`(CAA_HANDLE hDriver, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`CL2_SetCiAState',`(CAA_HANDLE hDriver, unsigned char byState)')

/* Properties */
DEF_ITF_API(`CAA_UDINT',`CDECL',`CL2_GetProperty',`(unsigned short usPropery)')

/* Services for Can Mini Driver */
DEF_ITF_API(`CAA_ERROR',`CDECL',`CL2_CmdRegister',`(unsigned char ucNetId, CMD_CMDRV* pCMDRV, CAA_COUNT ctMessages, CL2I_INFO** ppInfo)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`CL2_CmdUnRegister',`(unsigned char ucNetId)')

/**
 * <description> 
 *	This function can be used to determine the current number of messages in Tx Queue of a specific CAN network.
 *	It is also the number of following CMD_Send calls (if driver returns no error). So it can be used for Tx message bundling in CMD_Send.
 * </description>
 * <param name="ucNetId" type="IN">CAN Network ID</param>
 * <param name="peError" type="IN">Pointer to error</param>
 * <result>Number of messages in Tx queue</result>
 */
DEF_ITF_API(`CAA_COUNT',`CDECL',`CL2_GetTxQueueLength',`(unsigned char ucNetId, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`CL2_MsgAlloc',`(unsigned char ucNetId, CAA_ERROR* peError)')
DEF_ITF_API(`CL2I_BLOCK*',`CDECL',`CL2_MsgGetData',`(CAA_HANDLE hBlock)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`CL2_MsgFree',`(unsigned char ucNetId, CAA_HANDLE hBlock)')

/**
 * <description> 
 *	After a message has been sent successfully, the block transmitted to the CAN Mini Driver has to be returned to the CL2 layer. 
 *	This is done using the function CL2_MsgSendAcknIRQ or CL2_MsgSendAcknNoIRQ. 
 *	CL2_MsgSendAcknIRQ is designed to be used in interrupt context (e.g. Tx IRQ). The implementation is optimized for optimal chip utilization.
 *  If there are still messages in Tx Queue, CMD_Send is triggered as long as the driver signals an error (e.g. chip not ready) or Tx queue is empty. 
 *	Afterwards hBlock is processed if unequal CAA_hINVALID. After calling the function hBlock should not be used anymore by driver.
 *  
 *	Note:
 *	With 3.5 SP7 CL2_MsgSendAckn was renamed to CL2_MsgSendAcknIRQ. 
 *  CL2_MsgSendAcknNoIRQ provides a new implementation optimized for using outside interrupt context.
 * </description>
 * <param name="ucNetId" type="IN">CAN Network ID</param>
 * <param name="hBlock" type="IN">Handle of successfully sent message</param>
 * <result>error code</result>
 */
DEF_ITF_API(`CAA_ERROR',`CDECL',`CL2_MsgSendAcknIRQ',`(unsigned char ucNetId, CAA_HANDLE hBlock)')

/**
 * <description> 
 *	After a message has been sent successfully, the block transmitted to the CAN Mini Driver has to be returned to the CL2 layer. 
 *	This is done using the function CL2_MsgSendAcknIRQ or CL2_MsgSendAcknNoIRQ. 
 *	CL2_MsgSendAcknNoIRQ is designed to be used outside interrupt context (e.g. CMD_Send). Function behaviour depends on hBlock:
 *	If hBlock is unequal CAA_hINVALID: hBlock is processed by CL2. After calling the function hBlock should not be used anymore.
 *	No further CMD_Send is triggered (difference to CL2_MsgSendAcknNoIRQ)!
 *	If hBlock is CAA_hINVALID: The function checks for messages in Tx Queue and tries sending them by calling CMD_Send. A call with
 *	CAA_hINVALID is only needed afterwards CMD_Send returning an error.
 *  
 *	Note:
 *	With 3.5 SP7 CL2_MsgSendAckn was renamed to CL2_MsgSendAcknIRQ. 
 *  CL2_MsgSendAcknNoIRQ provides a new implementation optimized for using outside interrupt context.
 * </description>
 * <param name="ucNetId" type="IN">CAN Network ID</param>
 * <param name="hBlock" type="IN">Handle of successfully sent message</param>
 * <result>error code</result>
 */
DEF_ITF_API(`CAA_ERROR',`CDECL',`CL2_MsgSendAcknNoIRQ',`(unsigned char ucNetId, CAA_HANDLE hBlock)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`CL2_MsgPutRQueue',`(unsigned char ucNetId, CAA_HANDLE hBlock)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`CL2_MsgClone',`(unsigned char ucNetId, CAA_HANDLE hBlock, CAA_ERROR* peError)')

DEF_ITF_API(`unsigned short',`CDECL',`CL2_GetSupplierVersion',`(CAA_BOOL xDummy)')

/**
 * <description>cl2_driveropenp</description>
 */
typedef struct tagcl2_driveropenp_struct
{
	RTS_IEC_USINT usiNetId;				/* VAR_INPUT */
	RTS_IEC_UINT uiBaudrate;			/* VAR_INPUT */
	CAA_BOOL xSupport29Bits;			/* VAR_INPUT */
	CAA_SIZE szMemSize;					/* VAR_INPUT */
	CAA_PVOID* pMemory;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE DriverOpenP;				/* VAR_OUTPUT */
} cl2_driveropenp_struct;

DEF_API(`void',`CDECL',`cl2_driveropenp',`(cl2_driveropenp_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_cstcyclestart</description>
 */
typedef struct tagcl2_cstcyclestart_struct
{
	CAA_HANDLE hCstCycle;				/* VAR_INPUT */
	CAA_ERROR CstCycleStart;			/* VAR_OUTPUT */
} cl2_cstcyclestart_struct;

DEF_API(`void',`CDECL',`cl2_cstcyclestart',`(cl2_cstcyclestart_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_updatetimeservice</description>
 */
typedef struct tagcl2_updatetimeservice_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	RTS_IEC_TIME_OF_DAY todTime;		/* VAR_INPUT */
	RTS_IEC_DATE datDate;				/* VAR_INPUT */
	CAA_ERROR UpdateTimeService;		/* VAR_OUTPUT */
} cl2_updatetimeservice_struct;

DEF_API(`void',`CDECL',`cl2_updatetimeservice',`(cl2_updatetimeservice_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_getmsgcount</description>
 */
typedef struct tagcl2_getmsgcount_struct
{
	CAA_HANDLE hReceiverId;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_COUNT GetMsgCount;				/* VAR_OUTPUT */
} cl2_getmsgcount_struct;

DEF_API(`void',`CDECL',`cl2_getmsgcount',`(cl2_getmsgcount_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_enablesyncservice</description>
 */
typedef struct tagenablesyncservice_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CL2I_COBID cobID;						/* VAR_INPUT */
	CAA_BOOL xSyncProducer;				/* VAR_INPUT */
	CAA_BOOL xEnableSyncEvent;			/* VAR_INPUT */
	RTS_IEC_UDINT udiSyncCycle;			/* VAR_INPUT */
	RTS_IEC_UDINT udiSyncWindowLength;	/* VAR_INPUT */
	RTS_IEC_UDINT udiSyncForewarnTime;	/* VAR_INPUT */
	CAA_ERROR EnableSyncService;		/* VAR_OUTPUT */
} cl2_enablesyncservice_struct;

DEF_API(`void',`CDECL',`cl2_enablesyncservice',`(cl2_enablesyncservice_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_disabletimeservice</description>
 */
typedef struct tagcl2_disabletimeservice_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR DisableTimeService;		/* VAR_OUTPUT */
} cl2_disabletimeservice_struct;

DEF_API(`void',`CDECL',`cl2_disabletimeservice',`(cl2_disabletimeservice_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_enabletimeservice</description>
 */
typedef struct tagcl2_enabletimeservice_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CL2I_COBID cobID;						/* VAR_INPUT */
	CAA_BOOL xTimeProducer;				/* VAR_INPUT */
	CAA_BOOL xEnableTimeEvent;			/* VAR_INPUT */
	RTS_IEC_UDINT udiTimeCycle;			/* VAR_INPUT */
	RTS_IEC_UDINT udiTimeForewarnTime;	/* VAR_INPUT */
	CAA_ERROR EnableTimeService;		/* VAR_OUTPUT */
} cl2_enabletimeservice_struct;

DEF_API(`void',`CDECL',`cl2_enabletimeservice',`(cl2_enabletimeservice_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_isrtrmessage</description>
 */
typedef struct tagcl2_isrtrmessage_struct
{
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_BOOL IsRTRMessage;				/* VAR_OUTPUT */
} cl2_isrtrmessage_struct;

DEF_API(`void',`CDECL',`cl2_isrtrmessage',`(cl2_isrtrmessage_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_cstcycleupdate</description>
 */
typedef struct tagcl2_cstcycleupdate_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE CstCycleUpdate;			/* VAR_OUTPUT */
} cl2_cstcycleupdate_struct;

DEF_API(`void',`CDECL',`cl2_cstcycleupdate',`(cl2_cstcycleupdate_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_createsingleidreceiver</description>
 */
typedef struct tagcl2_createsingleidreceiver_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CL2I_COBID cobId;						/* VAR_INPUT */
	CAA_BOOL xRTR;							/* VAR_INPUT */
	CAA_BOOL x29BitId;					/* VAR_INPUT */
	CAA_BOOL xTransmit;					/* VAR_INPUT */
	CAA_BOOL xAlwaysNewest;				/* VAR_INPUT */
	CAA_ENUM eEvent;						/* VAR_INPUT */
	CAA_BOOL xEnableSyncWindow;		/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE CreateSingleIdReceiver;	/* VAR_OUTPUT */
} cl2_createsingleidreceiver_struct;

DEF_API(`void',`CDECL',`cl2_createsingleidreceiver',`(cl2_createsingleidreceiver_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_gettimestamp</description>
 */
typedef struct tagcl2_gettimestamp_struct
{
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	RTS_IEC_UDINT GetTimeStamp;			/* VAR_OUTPUT */
} cl2_gettimestamp_struct;

DEF_API(`void',`CDECL',`cl2_gettimestamp',`(cl2_gettimestamp_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_cstcyclestop</description>
 */
typedef struct tagcl2_cstcyclestop_struct
{
	CAA_HANDLE hCstCycle;				/* VAR_INPUT */
	CAA_ERROR CstCycleStop;				/* VAR_OUTPUT */
} cl2_cstcyclestop_struct;

DEF_API(`void',`CDECL',`cl2_cstcyclestop',`(cl2_cstcyclestop_struct *p)',1,0x0,0x0)

/**
 * <description>disablesyncservice</description>
 */
typedef struct tagcl2_disablesyncservice_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR DisableSyncService;		/* VAR_OUTPUT */
} cl2_disablesyncservice_struct;

DEF_API(`void',`CDECL',`cl2_disablesyncservice',`(cl2_disablesyncservice_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_write</description>
 */
typedef struct tagcl2_write_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	RTS_IEC_USINT usiPriority;			/* VAR_INPUT */
	CAA_BOOL xEnableSyncWindow;			/* VAR_INPUT */
	CAA_ERROR Write;					/* VAR_OUTPUT */
} cl2_write_struct;

DEF_API(`void',`CDECL',`cl2_write',`(cl2_write_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_getnetid</description>
 */
typedef struct tagcl2_getnetid_struct
{
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	RTS_IEC_USINT GetNetId;				/* VAR_OUTPUT */
} cl2_getnetid_struct;

DEF_API(`void',`CDECL',`cl2_getnetid',`(cl2_getnetid_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_getsupplierversion</description>
 */
typedef struct tagcl2_getsupplierversion_struct
{
	CAA_BOOL xDummy; /* VAR_INPUT */
	RTS_IEC_WORD GetSupplierVersion;	/* VAR_OUTPUT */
} cl2_getsupplierversion_struct;

DEF_API(`void',`CDECL',`cl2_getsupplierversion',`(cl2_getsupplierversion_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_cstcycleclose</description>
 */
typedef struct tagcl2_cstcycleclose_struct
{
	CAA_HANDLE hCstCycle;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE CstCycleClose;			/* VAR_OUTPUT */
} cl2_cstcycleclose_struct;

DEF_API(`void',`CDECL',`cl2_cstcycleclose',`(cl2_cstcycleclose_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_createmaskreceiver</description>
 */
typedef struct tagcl2_createmaskreceiver_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CL2I_COBID cobIdValue;				/* VAR_INPUT */
	CL2I_COBID cobIdMask;				/* VAR_INPUT */
	CAA_BOOL xRTRValue;					/* VAR_INPUT */
	CAA_BOOL xRTRMask;					/* VAR_INPUT */
	CAA_BOOL x29BitIdValue;				/* VAR_INPUT */
	CAA_BOOL x29BitIdMask;				/* VAR_INPUT */
	CAA_BOOL xTransmitValue;			/* VAR_INPUT */
	CAA_BOOL xTransmitMask;				/* VAR_INPUT */
	CAA_BOOL xAlwaysNewest;				/* VAR_INPUT */
	CAA_ENUM eEvent;						/* VAR_INPUT */
	CAA_BOOL xEnableSyncWindow;		/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE CreateMaskReceiver;	/* VAR_OUTPUT */
} cl2_createmaskreceiver_struct;

DEF_API(`void',`CDECL',`cl2_createmaskreceiver',`(cl2_createmaskreceiver_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_createarrayreceiver</description>
 */
typedef struct tagcl2_createarrayreceiver_struct
{
	CAA_HANDLE hDriver;						/* VAR_INPUT */
	CL2I_ARRAYRECV_ENTRY* paSortedCOBIDs;	/* VAR_INPUT */
	CAA_COUNT ctCOBIDs;						/* VAR_INPUT */
	CAA_ENUM eEvent;						/* VAR_INPUT */
	CAA_BOOL xEnableSyncWindow;				/* VAR_INPUT */
	CAA_ERROR* peError;						/* VAR_INPUT */
	CAA_HANDLE CreateArrayReceiver;			/* VAR_OUTPUT */
} cl2_createarrayreceiver_struct;

DEF_API(`void',`CDECL',`cl2_createarrayreceiver',`(cl2_createarrayreceiver_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_freemessage</description>
 */
typedef struct tagcl2_freemessage_struct
{
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	CAA_ERROR FreeMessage;				/* VAR_OUTPUT */
} cl2_freemessage_struct;

DEF_API(`void',`CDECL',`cl2_freemessage',`(cl2_freemessage_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_getmessageid</description>
 */
typedef struct tagcl2_getmessageid_struct
{
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	CAA_ERROR* peError;				/* VAR_INPUT */
	CL2I_COBID GetMessageId;		/* VAR_OUTPUT */
} cl2_getmessageid_struct;

DEF_API(`void',`CDECL',`cl2_getmessageid',`(cl2_getmessageid_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_lostmessages</description>
 */
typedef struct tagcl2_lostmessages_struct
{
	CAA_HANDLE hReceiverId;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_COUNT LostMessages;			/* VAR_OUTPUT */
} cl2_lostmessages_struct;

DEF_API(`void',`CDECL',`cl2_lostmessages',`(cl2_lostmessages_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_getbusload</description>
 */
typedef struct tagcl2_getbusload_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	unsigned short GetBusload;			/* VAR_OUTPUT */
} cl2_getbusload_struct;

DEF_API(`void',`CDECL',`cl2_getbusload',`(cl2_getbusload_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_getmessagedatapointer</description>
 */
typedef struct tagcl2_getmessagedatapointer_struct
{
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CL2I_DATA* GetMessageDataPointer;		/* VAR_OUTPUT */
} cl2_getmessagedatapointer_struct;

DEF_API(`void',`CDECL',`cl2_getmessagedatapointer',`(cl2_getmessagedatapointer_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_unregisteridarea</description>
 */
typedef struct tagcl2_unregisteridarea_struct
{
	CAA_HANDLE hReceiverId;				/* VAR_INPUT */
	CL2I_COBID cobIdStart;				/* VAR_INPUT */
	CL2I_COBID cobIdEnd;					/* VAR_INPUT */
	CAA_BOOL xRTRValue;					/* VAR_INPUT */
	CAA_BOOL xRTRMask;					/* VAR_INPUT */
	CAA_BOOL x29BitIdValue;				/* VAR_INPUT */
	CAA_BOOL x29BitIdMask;				/* VAR_INPUT */
	CAA_BOOL xTransmitValue;			/* VAR_INPUT */
	CAA_BOOL xTransmitMask;				/* VAR_INPUT */
	CAA_ERROR UnregisterIdArea;		/* VAR_OUTPUT */
} cl2_unregisteridarea_struct;

DEF_API(`void',`CDECL',`cl2_unregisteridarea',`(cl2_unregisteridarea_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_gettransmitcounter</description>
 */
typedef struct tagcl2_gettransmitcounter_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_COUNT GetTransmitCounter;			/* VAR_OUTPUT */
} cl2_gettransmitcounter_struct;

DEF_API(`void',`CDECL',`cl2_gettransmitcounter',`(cl2_gettransmitcounter_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_createidareareceiver</description>
 */
typedef struct tagcl2_createidareareceiver_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_BOOL xAlwaysNewest;				/* VAR_INPUT */
	CAA_ENUM eEvent;					/* VAR_INPUT */
	CAA_BOOL xEnableSyncWindow;			/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE CreateIdAreaReceiver;	/* VAR_OUTPUT */
} cl2_createidareareceiver_struct;

DEF_API(`void',`CDECL',`cl2_createidareareceiver',`(cl2_createidareareceiver_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_createidareareceiverex</description>
 */
typedef struct tagcl2_createidareareceiverex_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_BOOL xAlwaysNewest;				/* VAR_INPUT */
	CAA_BOOL xReverse;					/* VAR_INPUT */
	CAA_ENUM eEvent;					/* VAR_INPUT */
	CAA_BOOL xEnableSyncWindow;			/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE CreateIdAreaReceiverEx;	/* VAR_OUTPUT */
} cl2_createidareareceiverex_struct;

DEF_API(`void',`CDECL',`cl2_createidareareceiverex',`(cl2_createidareareceiverex_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_createmessage</description>
 */
typedef struct tagcl2_createmessage_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CL2I_COBID cobID;						/* VAR_INPUT */
	RTS_IEC_USINT usiLength;			/* VAR_INPUT */
	CAA_BOOL xRTR;							/* VAR_INPUT */
	CAA_BOOL x29BitID;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE CreateMessage;			/* VAR_OUTPUT */
} cl2_createmessage_struct;

DEF_API(`void',`CDECL',`cl2_createmessage',`(cl2_createmessage_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_registeridarea</description>
 */
typedef struct tagcl2_registeridarea_struct
{
	CAA_HANDLE hReceiverId;				/* VAR_INPUT */
	CL2I_COBID cobIdStart;				/* VAR_INPUT */
	CL2I_COBID cobIdEnd;					/* VAR_INPUT */
	CAA_BOOL xRTRValue;					/* VAR_INPUT */
	CAA_BOOL xRTRMask;					/* VAR_INPUT */
	CAA_BOOL x29BitIdValue;				/* VAR_INPUT */
	CAA_BOOL x29BitIdMask;				/* VAR_INPUT */
	CAA_BOOL xTransmitValue;			/* VAR_INPUT */
	CAA_BOOL xTransmitMask;				/* VAR_INPUT */
	CAA_ERROR RegisterIdArea;			/* VAR_OUTPUT */
} cl2_registeridarea_struct;

DEF_API(`void',`CDECL',`cl2_registeridarea',`(cl2_registeridarea_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_driverclose</description>
 */
typedef struct tagcl2_driverclose_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR DriverClose;				/* VAR_OUTPUT */
} cl2_driverclose_struct;

DEF_API(`void',`CDECL',`cl2_driverclose',`(cl2_driverclose_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_clonemessage</description>
 */
typedef struct tagcl2_clonemessage_struct
{
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE CloneMessage;			/* VAR_OUTPUT */
} cl2_clonemessage_struct;

DEF_API(`void',`CDECL',`cl2_clonemessage',`(cl2_clonemessage_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_getbusstate</description>
 */
typedef struct tagcl2_getbusstate_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_ENUM GetBusState;				/* VAR_OUTPUT */
} cl2_getbusstate_struct;

DEF_API(`void',`CDECL',`cl2_getbusstate',`(cl2_getbusstate_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_issendingactive</description>
 */
typedef struct tagcl2_issendingactive_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_BOOL IsSendingActive;			/* VAR_OUTPUT */
} cl2_issendingactive_struct;

DEF_API(`void',`CDECL',`cl2_issendingactive',`(cl2_issendingactive_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_read</description>
 */
typedef struct tagcl2_read_struct
{
	CAA_HANDLE hReceiverId;				/* VAR_INPUT */
	CAA_COUNT* pctMsgLeft;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE Read;					/* VAR_OUTPUT */
} cl2_read_struct;

DEF_API(`void',`CDECL',`cl2_read',`(cl2_read_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_readarrayreceiver</description>
 */
typedef struct tagcl2_readarrayreceiver_struct
{
	CAA_HANDLE hArrayReceiver;			/* VAR_INPUT */
	CAA_COUNT  ctIndex;					/* VAR_INPUT */
	CAA_COUNT* pctMsgLeft;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE ReadArrayReceiver;		/* VAR_OUTPUT */
} cl2_readarrayreceiver_struct;

DEF_API(`void',`CDECL',`cl2_readarrayreceiver',`(cl2_readarrayreceiver_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_getbaudrate</description>
 */
typedef struct tagcl2_getbaudrate_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	RTS_IEC_UINT GetBaudrate;			/* VAR_OUTPUT */
} cl2_getbaudrate_struct;

DEF_API(`void',`CDECL',`cl2_getbaudrate',`(cl2_getbaudrate_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_getproperty</description>
 */
typedef struct tagcl2_getproperty_struct
{
	RTS_IEC_UINT uiProperty;			/* VAR_INPUT */
	RTS_IEC_UDINT GetProperty;			/* VAR_OUTPUT */
} cl2_getproperty_struct;

DEF_API(`void',`CDECL',`cl2_getproperty',`(cl2_getproperty_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_istransmitmessage</description>
 */
typedef struct tagcl2_istransmitmessage_struct
{
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_BOOL IsTransmitMessage;			/* VAR_OUTPUT */
} cl2_istransmitmessage_struct;

DEF_API(`void',`CDECL',`cl2_istransmitmessage',`(cl2_istransmitmessage_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_is29bitidmessage</description>
 */
typedef struct tagcl2_is29bitidmessage_struct
{
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_BOOL Is29BitIdMessage;			/* VAR_OUTPUT */
} cl2_is29bitidmessage_struct;

DEF_API(`void',`CDECL',`cl2_is29bitidmessage',`(cl2_is29bitidmessage_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_getmessagelength</description>
 */
typedef struct tagcl2_getmessagelength_struct
{
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	RTS_IEC_USINT GetMessageLength;		/* VAR_OUTPUT */
} cl2_getmessagelength_struct;

DEF_API(`void',`CDECL',`cl2_getmessagelength',`(cl2_getmessagelength_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_deletereceiver</description>
 */
typedef struct tagcl2_deletereceiver_struct
{
	CAA_HANDLE hReceiverId;				/* VAR_INPUT */
	CAA_ERROR DeleteReceiver;			/* VAR_OUTPUT */
} cl2_deletereceiver_struct;

DEF_API(`void',`CDECL',`cl2_deletereceiver',`(cl2_deletereceiver_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_cstcycleopen</description>
 */
typedef struct tagcl2_cstcycleopen_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ENUM eCstEvent;					/* VAR_INPUT */
	RTS_IEC_USINT usiPriority;			/* VAR_INPUT */
	CAA_BOOL xEnableSyncWindow;			/* VAR_INPUT */
	RTS_IEC_UDINT udiCstCycle;			/* VAR_INPUT */
	RTS_IEC_UDINT udiCstForewarnTime;	/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE CstCycleOpen;			/* VAR_OUTPUT */
} cl2_cstcycleopen_struct;

DEF_API(`void',`CDECL',`cl2_cstcycleopen',`(cl2_cstcycleopen_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_getreceivecounter</description>
 */
typedef struct tagcl2_getreceivecounter_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_COUNT GetReceiveCounter;		/* VAR_OUTPUT */
} cl2_getreceivecounter_struct;

DEF_API(`void',`CDECL',`cl2_getreceivecounter',`(cl2_getreceivecounter_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_driveropenh</description>
 */
typedef struct tagcl2_driveropenh_struct
{
	RTS_IEC_USINT usiNetId;				/* VAR_INPUT */
	RTS_IEC_UINT uiBaudrate;			/* VAR_INPUT */
	CAA_BOOL xSupport29Bits;			/* VAR_INPUT */
	CAA_COUNT ctMessages;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE DriverOpenH;				/* VAR_OUTPUT */
} cl2_driveropenh_struct;

DEF_API(`void',`CDECL',`cl2_driveropenh',`(cl2_driveropenh_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_getlostcounter</description>
 */
typedef struct tagcl2_getlostcounter_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_COUNT GetLostCounter;			/* VAR_OUTPUT */
} cl2_getlostcounter_struct;

DEF_API(`void',`CDECL',`cl2_getlostcounter',`(cl2_getlostcounter_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_getbusalarm</description>
 */
typedef struct tagcl2_getbusalarm_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_BOOL GetBusAlarm;				/* VAR_OUTPUT */
} cl2_getbusalarm_struct;

DEF_API(`void',`CDECL',`cl2_getbusalarm',`(cl2_getbusalarm_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_getreceiveerrorcounter</description>
 */
typedef struct tagcl2_getreceiveerrorcounter_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR *peError;					/* VAR_INPUT */
	CAA_COUNT GetReceiveErrorCounter;	/* VAR_OUTPUT */
} cl2_getreceiveerrorcounter_struct;

DEF_API(`void',`CDECL',`cl2_getreceiveerrorcounter',`(cl2_getreceiveerrorcounter_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_gettransmiterrorcounter</description>
 */
typedef struct tagcl2_gettransmiterrorcounter_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_COUNT GetTransmitErrorCounter;	/* VAR_OUTPUT */
} cl2_gettransmiterrorcounter_struct;

DEF_API(`void',`CDECL',`cl2_gettransmiterrorcounter',`(cl2_gettransmiterrorcounter_struct *p)',1,0x0,0x0)

/**
 * <description>cl2_resetbusalarm</description>
 */
typedef struct tagcl2_resetbusalarm_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR ResetBusAlarm;			/* VAR_OUTPUT */
} cl2_resetbusalarm_struct;

DEF_API(`void',`CDECL',`cl2_resetbusalarm',`(cl2_resetbusalarm_struct *p)',1,0x0,0x0)

typedef struct tagcl2_getciastate_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	unsigned char GetCiAState;			/* VAR_OUTPUT */
} cl2_getciastate_struct;

DEF_API(`void',`CDECL',`cl2_getciastate',`(cl2_getciastate_struct *p)',1,0x0,0x0)

typedef struct tagcl2_setciastate_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	unsigned char byState;				/* VAR_INPUT */
    CAA_ERROR SetCiAState;			    /* VAR_OUTPUT */
} cl2_setciastate_struct;

DEF_API(`void',`CDECL',`cl2_setciastate',`(cl2_setciastate_struct *p)',1,0x0,0x0)

typedef struct tagcl2_gettransmitqueuelength_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
    CAA_COUNT GetTransmitQueueLength;   /* VAR_OUTPUT */
} cl2_gettransmitqueuelength_struct;

DEF_API(`void',`CDECL',`cl2_gettransmitqueuelength',`(cl2_gettransmitqueuelength_struct *p)',1,0x0,0x0)

typedef struct tagcl2_getreceivequeuelength_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
    CAA_COUNT GetReceiveQueueLength;    /* VAR_OUTPUT */
} cl2_getreceivequeuelength_struct;

DEF_API(`void',`CDECL',`cl2_getreceivequeuelength',`(cl2_getreceivequeuelength_struct *p)',1,0x0,0x0)

typedef struct tagcl2_gettransmitpoolsize_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
    CAA_COUNT GetTransmitPoolSize;      /* VAR_OUTPUT */
} cl2_gettransmitpoolsize_struct;

DEF_API(`void',`CDECL',`cl2_gettransmitpoolsize',`(cl2_gettransmitpoolsize_struct *p)',1,0x0,0x0)

typedef struct tagcl2_getreceivepoolsize_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
    CAA_COUNT GetReceivePoolSize;       /* VAR_OUTPUT */
} cl2_getreceivepoolsize_struct;

DEF_API(`void',`CDECL',`cl2_getreceivepoolsize',`(cl2_getreceivepoolsize_struct *p)',1,0x0,0x0)

#ifdef __cplusplus
}
#endif
