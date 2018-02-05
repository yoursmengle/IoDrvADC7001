 /**
 * <interfacename>Redundancy</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _CMPREDUNDANCYITF_H_
#define _CMPREDUNDANCYITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"

/**
 * <description>Redundancy service Ids</description>
 */
#define RDCY_SRV_WRITESETT				0x01
#define RDCY_SRV_READSETT				0x02
#define RDCY_SRV_READETHERCATNICSETTING 0x03
#define RDCY_SRV_READRDCYSTATE			0x04
#define RDCY_SRV_SWITCHOVER				0x05
#define RDCY_SRV_SYNCHRONIZE			0x06
#define RDCY_SRV_SETSIMULATIONMODE		0x07
#define RDCY_SRV_SWITCHTOSTANDALONE		0x08
#define RDCY_SRV_SWITCHTOACTIVE			0x09

/**
 * <description>Redundancy service tag Ids</description>
 */
#define TAG_SESSION_ID						0x10
#define TAG_SETT_IPADDRESSLOCAL_FIRSTLINK	0x11
#define TAG_SETT_IPADDRESSPEER_FIRSTLINK	0x12
#define TAG_SETT_PORT_FIRSTLINK				0x13
#define TAG_SETT_USESECONDLINK				0x14
#define TAG_SETT_IPADDRESSLOCAL_SECONDLINK	0x15
#define TAG_SETT_IPADDRESSPEER_SECONDLINK	0x16
#define TAG_SETT_PORT_SECONDLINK			0x17
#define TAG_SETT_BOOTUPWAITTIME				0x18
#define TAG_SETT_TCPWAITTIME				0x19
#define TAG_SETT_STANDBYWAITTIME			0x1A
#define TAG_SETT_LOCKTIMEOUT				0x1B
#define TAG_SETT_BOOTPROJECTNAME			0x1C
#define TAG_SETT_REDUNDANCYTASKNAME			0x1D
#define TAG_SETT_SERVICEWAITTIME			0x1E
#define TAG_SETT_SERVICE					0x1F
#define TAG_SETT_FIELDBUSES					0x20
#define TAG_SETT_ETHERCATNICSETTING			0x21
#define TAG_SETT_MACADDRESSLOCAL_FIRSTLINK	0x22
#define TAG_SETT_REDUNDANCYFRAMEWAITTIME	0x23
#define TAG_SETT_GETFRAMESLEEPTIME			0x24
#define TAG_SETT_DATAVIASYNCWAITTIME		0x25
#define TAG_SETT_DATAVIASYNCLEEPTIME		0x26
#define RDCY_ACK							0x81
#define TAG_SETT_RDCYCONNECTION				0x82
#define TAG_RDCY_SUCCESS					0x2A
#define TAG_RDCY_ERROR						0x2B
#define TAG_RDCY_STATE						0x2C

/**
 * <description>Redundancy settings names and default values</description>
 */
#define RDCYKEY_INT_BOOTUPWAITTIME							"BootupWaitTime"
#define RDCYVALUE_INT_BOOTUPWAITTIME_DEFAULT				5000

#define RDCYKEY_INT_TCPWAITTIME								"TcpWaitTime"
#define RDCYVALUE_INT_TCPWAITTIME_DEFAULT					2000

#define RDCYKEY_INT_RECONNECTWAITTIME						"ReconnectWaitTime"
#define RDCYVALUE_INT_RECONNECTWAITTIME_DEFAULT				5000

#define RDCYKEY_INT_STANDBYWAITTIME							"StandbyWaitTime"
#define RDCYVALUE_INT_STANDBYWAITTIME_DEFAULT				30

#define RDCYKEY_INT_LOCKTIMEOUT								"LockTimeout"
#define RDCYVALUE_INT_LOCKTIMEOUT_DEFAULT					50

#define RDCYKEY_STRING_BOOTPROJECTNAME						"Bootproject"
#define RDCYVALUE_STRING_BOOTPROJECTNAME_DEFAULT			""

#define RDCYKEY_STRING_REDUNDANCYMAINTASKNAME				"RedundancyTaskName"
#define RDCYVALUE_STRING_REDUNDANCYMAINTASKNAME_DEFAULT		""

#define RDCYKEY_INT_SERVICEWAITTIME							"Service.WaitTime"
#define RDCYVALUE_INT_SERVICEWAITTIME_DEFAULT				1000

#define RDCYKEY_INT_EVTTRGSTARTENDCALL						"EvtTrgStartEndCall"
#define RDCYVALUE_INT_EVTTRGSTARTENDCALL_DEFAULT			TRUE

#define RDCYKEY_INT_PROFIBUS								"Profibus"
#define RDCYVALUE_INT_PROFIBUS_DEFAULT						FALSE

#define RDCYKEY_INT_ETHERCAT								"Ethercat"
#define RDCYVALUE_INT_ETHERCAT_DEFAULT						FALSE

#define RDCYKEY_INT_DEBUGMESSAGES							"DebugMessages"
#define RDCYVALUE_INT_DEBUGMESSAGES_DEFAULT					FALSE

#define RDCYKEY_INT_DEBUGMESSAGESTASKTIME					"DebugMessagesTaskTime"
#define RDCYVALUE_INT_DEBUGMESSAGESTASKTIME_DEFAULT			FALSE

#define RDCYKEY_INT_CALLVFINIT								"CallVfInit"
#define RDCYVALUE_INT_CALLVFINIT_DEFAULT					TRUE

#define RDCYKEY_INT_SIMULATION								"Simulation"
#define RDCYVALUE_INT_SIMULATION_DEFAULT					FALSE

#define RDCYKEY_INT_SYNCHROPHASELENGTH						"SynchroPhaseLength"
#define RDCYVALUE_INT_SYNCHROPHASELENGTH_DEFAULT			0

#define RDCYKEY_INT_EXTRASTANDBYWAITTIME					"ExtraStandbyWaitTime"
#define RDCYVALUE_INT_EXTRASTANDBYWAITTIME_DEFAULT			0

#define RDCYKEY_INT_STANDALONEAFTERSTANDBY					"StandaloneAfterStandby"
#define RDCYVALUE_INT_STANDALONEAFTERSTANDBY_DEFAULT		2

#define RDCYKEY_INT_INPUTAREACRCCHECK						"InputAreaCrcCheck"
#define RDCYVALUE_INT_INPUTAREACRCCHECK_DEFAULT				FALSE

#define RDCYKEY_INT_CMPSRV_SERVICEWAITTIME					"Service.WaitTime"
#define RDCYVALUE_INT_CMPSRV_SERVICEWAITTIME_DEFAULT		1000

#define EVTPARAMID_CmpRedundancy_vfInit		0x0001
#define EVTVERSION_CmpRedundancy_vfInit		0x0001
#define EVT_CmpRedundancy_vfInit			MAKE_EVENTID(EVTCLASS_INFO, 1)

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Typedef for redundancy state</description>
 */
typedef enum
{
	RS_START = 0,
	RS_SYNCHRO = 1,
	RS_CYCLE_ACTIVE = 2,
	RS_CYCLE_STANDBY = 3,
	RS_CYCLE_STANDALONE = 4,
	RS_CYCLE_ERROR = 5,
	RS_SIMULATION = 6,
	RS_BOOTUP_ERROR = 7,
	RS_SHUTDOWN_ACTIVE = 8,
	RS_SHUTDOWN_STANDBY = 9,
	RS_SYNCHRO_ERROR = 10,
	RS_SIMULATION_START = 11,
	RS_NO_LICENSE = 12
} RDCY_STATE;

/**
 * <description>Typedef for redundancy error</description>
 */
typedef enum
{
	RDCY_NO_ERROR = 0,
	RDCY_ERR_FAILED = 1,
	RDCY_BOOTUP_ERROR = 2,
	RDCY_SYNCHRO_ERROR = 3,
	RDCY_CYCLE_ERROR = 4,
	RDCY_LINK_ERROR = 5,
	RDCY_FIELDBUS_ERROR = 6,
	RDCY_RECEIVEMESSAGE_ERROR = 7,
	RDCY_NOMESSAGE_ERROR = 8,
	RDCY_WRONGMESSAGE_ERROR = 9,
	RDCY_CONFIG_ERROR = 10,
	RDCY_INPUTAREACRC_ERROR = 11,
	RDCY_NO_LICENSE_ERROR = 12
} RDCY_ERROR;

/**
 * <description>Typedef for redundancy area type</description>
 */
typedef enum
{
	AREA_NONE = 0,
	AREA_INPUT = 1,
	AREA_SYNCHRO = 2,
	AREA_OUTPUT = 3
} RDCY_AREA_TYPE;

/**
 * <description>Typedef for redundancy state information</description>
 */
typedef struct tagRedundancyState
{
	RDCY_STATE eRedundancyState;
	RDCY_ERROR eRedundancyError;
	RTS_IEC_STRING stRedundancyError[81];
} RedundancyState;

typedef struct tagRedundancyTlgHeader
{
	RTS_UI32 dwIdentity; /* Telegram identity */
	RTS_UI16 wID; /* Redundancy message id */
	RTS_UI16 wFlags; /* Message flag (FLAG_FIRST_MESSAGE/FLAG_LAST_MESSAGE) */
	RTS_UI32 dwOwnIpAddress; /* Sender IP address */
	RTS_UI32 dwCRC; /* CRCs of input/output data areas */
	RTS_BOOL bCrcMismatch; /* CRC mismatch flag */
	RTS_UI32 dwTick; /* Tick */
	RTS_UI32 dwLen; /* Telegram length -> Header + Data */
} RedundancyTlgHeader;

/**
 * <description>Typedef for redundancy communication modes</description>
 */
typedef enum
{
	RCOM_SyncReceive = 0,	/* Sync messages (UDP) */
	RCOM_SyncSend = 1,		/* Sync messages (UDP) */
	RCOM_DataClient = 2,	/* Data messages (TCP) */
	RCOM_DataServer = 3,	/* Data messages (TCP) */
	RCOM_DataWork = 4,		/* Data messages (TCP), special mode to re-init server */
} REDUNDANCY_COMM_MODE;

/**
 * <description>Typedef for client reply</description>
 */
typedef struct tagCLIENT_REPLY
{
	RTS_UI32 dwBytesReceived;
	RTS_UI32 dwIPAddress;
	char stIPAddressTransmitter[21];
} CLIENT_REPLY;

/**
 * <description>arearegister</description>
 */
typedef struct tagarearegister_struct
{
	RTS_IEC_BYTE *pArea;				/* VAR_INPUT */
	RTS_IEC_UDINT udiSize;				/* VAR_INPUT */
	RDCY_AREA_TYPE eType;				/* VAR_INPUT */
	RTS_IEC_BOOL AreaRegister;			/* VAR_OUTPUT */
} arearegister_struct;

void CDECL CDECL_EXT arearegister(arearegister_struct *p);
typedef void (CDECL CDECL_EXT* PFAREAREGISTER_IEC) (arearegister_struct *p);
#if defined(CMPREDUNDANCY_NOTIMPLEMENTED) || defined(AREAREGISTER_NOTIMPLEMENTED)
	#define USE_arearegister
	#define EXT_arearegister
	#define GET_arearegister(fl)  ERR_NOTIMPLEMENTED
	#define CAL_arearegister(p0) 
	#define CHK_arearegister  FALSE
	#define EXP_arearegister  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_arearegister
	#define EXT_arearegister
	#define GET_arearegister(fl)  CAL_CMGETAPI( "arearegister" ) 
	#define CAL_arearegister  arearegister
	#define CHK_arearegister  TRUE
	#define EXP_arearegister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"arearegister", (RTS_UINTPTR)arearegister, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCY_EXTERNAL)
	#define USE_arearegister
	#define EXT_arearegister
	#define GET_arearegister(fl)  CAL_CMGETAPI( "arearegister" ) 
	#define CAL_arearegister  arearegister
	#define CHK_arearegister  TRUE
	#define EXP_arearegister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"arearegister", (RTS_UINTPTR)arearegister, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyarearegister
	#define EXT_CmpRedundancyarearegister
	#define GET_CmpRedundancyarearegister  ERR_OK
	#define CAL_CmpRedundancyarearegister  arearegister
	#define CHK_CmpRedundancyarearegister  TRUE
	#define EXP_CmpRedundancyarearegister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"arearegister", (RTS_UINTPTR)arearegister, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_arearegister
	#define EXT_arearegister
	#define GET_arearegister(fl)  CAL_CMGETAPI( "arearegister" ) 
	#define CAL_arearegister  arearegister
	#define CHK_arearegister  TRUE
	#define EXP_arearegister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"arearegister", (RTS_UINTPTR)arearegister, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_arearegister  PFAREAREGISTER_IEC pfarearegister;
	#define EXT_arearegister  extern PFAREAREGISTER_IEC pfarearegister;
	#define GET_arearegister(fl)  s_pfCMGetAPI2( "arearegister", (RTS_VOID_FCTPTR *)&pfarearegister, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_arearegister  pfarearegister
	#define CHK_arearegister  (pfarearegister != NULL)
	#define EXP_arearegister   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"arearegister", (RTS_UINTPTR)arearegister, 1, 0x0, 0x0) 
#endif


/**
 * <description>arearegistersegment</description>
 */
typedef struct tagarearegistersegment_struct
{
	RTS_IEC_UINT usSegment;					/* VAR_INPUT */
	RDCY_AREA_TYPE eType;				/* VAR_INPUT */
	RTS_IEC_BOOL AreaRegisterSegment;	/* VAR_OUTPUT */
} arearegistersegment_struct;

void CDECL CDECL_EXT arearegistersegment(arearegistersegment_struct *p);
typedef void (CDECL CDECL_EXT* PFAREAREGISTERSEGMENT_IEC) (arearegistersegment_struct *p);
#if defined(CMPREDUNDANCY_NOTIMPLEMENTED) || defined(AREAREGISTERSEGMENT_NOTIMPLEMENTED)
	#define USE_arearegistersegment
	#define EXT_arearegistersegment
	#define GET_arearegistersegment(fl)  ERR_NOTIMPLEMENTED
	#define CAL_arearegistersegment(p0) 
	#define CHK_arearegistersegment  FALSE
	#define EXP_arearegistersegment  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_arearegistersegment
	#define EXT_arearegistersegment
	#define GET_arearegistersegment(fl)  CAL_CMGETAPI( "arearegistersegment" ) 
	#define CAL_arearegistersegment  arearegistersegment
	#define CHK_arearegistersegment  TRUE
	#define EXP_arearegistersegment  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"arearegistersegment", (RTS_UINTPTR)arearegistersegment, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCY_EXTERNAL)
	#define USE_arearegistersegment
	#define EXT_arearegistersegment
	#define GET_arearegistersegment(fl)  CAL_CMGETAPI( "arearegistersegment" ) 
	#define CAL_arearegistersegment  arearegistersegment
	#define CHK_arearegistersegment  TRUE
	#define EXP_arearegistersegment  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"arearegistersegment", (RTS_UINTPTR)arearegistersegment, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyarearegistersegment
	#define EXT_CmpRedundancyarearegistersegment
	#define GET_CmpRedundancyarearegistersegment  ERR_OK
	#define CAL_CmpRedundancyarearegistersegment  arearegistersegment
	#define CHK_CmpRedundancyarearegistersegment  TRUE
	#define EXP_CmpRedundancyarearegistersegment  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"arearegistersegment", (RTS_UINTPTR)arearegistersegment, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_arearegistersegment
	#define EXT_arearegistersegment
	#define GET_arearegistersegment(fl)  CAL_CMGETAPI( "arearegistersegment" ) 
	#define CAL_arearegistersegment  arearegistersegment
	#define CHK_arearegistersegment  TRUE
	#define EXP_arearegistersegment  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"arearegistersegment", (RTS_UINTPTR)arearegistersegment, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_arearegistersegment  PFAREAREGISTERSEGMENT_IEC pfarearegistersegment;
	#define EXT_arearegistersegment  extern PFAREAREGISTERSEGMENT_IEC pfarearegistersegment;
	#define GET_arearegistersegment(fl)  s_pfCMGetAPI2( "arearegistersegment", (RTS_VOID_FCTPTR *)&pfarearegistersegment, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_arearegistersegment  pfarearegistersegment
	#define CHK_arearegistersegment  (pfarearegistersegment != NULL)
	#define EXP_arearegistersegment   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"arearegistersegment", (RTS_UINTPTR)arearegistersegment, 1, 0x0, 0x0) 
#endif


/**
 * <description>redundancycycleend</description>
 */
typedef struct tagredundancycycleend_struct
{
	RTS_IEC_BOOL RedundancyCycleEnd;	/* VAR_OUTPUT */
} redundancycycleend_struct;

/**
 * <description>unregisterareas</description>
 */
typedef struct tagunregisterareas_struct
{
	RTS_IEC_BOOL UnregisterAreas;		/* VAR_OUTPUT */
} unregisterareas_struct;

void CDECL CDECL_EXT unregisterareas(unregisterareas_struct *p);
typedef void (CDECL CDECL_EXT* PFUNREGISTERAREAS_IEC) (unregisterareas_struct *p);
#if defined(CMPREDUNDANCY_NOTIMPLEMENTED) || defined(UNREGISTERAREAS_NOTIMPLEMENTED)
	#define USE_unregisterareas
	#define EXT_unregisterareas
	#define GET_unregisterareas(fl)  ERR_NOTIMPLEMENTED
	#define CAL_unregisterareas(p0) 
	#define CHK_unregisterareas  FALSE
	#define EXP_unregisterareas  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_unregisterareas
	#define EXT_unregisterareas
	#define GET_unregisterareas(fl)  CAL_CMGETAPI( "unregisterareas" ) 
	#define CAL_unregisterareas  unregisterareas
	#define CHK_unregisterareas  TRUE
	#define EXP_unregisterareas  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"unregisterareas", (RTS_UINTPTR)unregisterareas, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCY_EXTERNAL)
	#define USE_unregisterareas
	#define EXT_unregisterareas
	#define GET_unregisterareas(fl)  CAL_CMGETAPI( "unregisterareas" ) 
	#define CAL_unregisterareas  unregisterareas
	#define CHK_unregisterareas  TRUE
	#define EXP_unregisterareas  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"unregisterareas", (RTS_UINTPTR)unregisterareas, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyunregisterareas
	#define EXT_CmpRedundancyunregisterareas
	#define GET_CmpRedundancyunregisterareas  ERR_OK
	#define CAL_CmpRedundancyunregisterareas  unregisterareas
	#define CHK_CmpRedundancyunregisterareas  TRUE
	#define EXP_CmpRedundancyunregisterareas  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"unregisterareas", (RTS_UINTPTR)unregisterareas, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_unregisterareas
	#define EXT_unregisterareas
	#define GET_unregisterareas(fl)  CAL_CMGETAPI( "unregisterareas" ) 
	#define CAL_unregisterareas  unregisterareas
	#define CHK_unregisterareas  TRUE
	#define EXP_unregisterareas  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"unregisterareas", (RTS_UINTPTR)unregisterareas, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_unregisterareas  PFUNREGISTERAREAS_IEC pfunregisterareas;
	#define EXT_unregisterareas  extern PFUNREGISTERAREAS_IEC pfunregisterareas;
	#define GET_unregisterareas(fl)  s_pfCMGetAPI2( "unregisterareas", (RTS_VOID_FCTPTR *)&pfunregisterareas, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_unregisterareas  pfunregisterareas
	#define CHK_unregisterareas  (pfunregisterareas != NULL)
	#define EXP_unregisterareas   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"unregisterareas", (RTS_UINTPTR)unregisterareas, 1, 0x0, 0x0) 
#endif


void CDECL CDECL_EXT redundancycycleend(redundancycycleend_struct *p);
typedef void (CDECL CDECL_EXT* PFREDUNDANCYCYCLEEND_IEC) (redundancycycleend_struct *p);
#if defined(CMPREDUNDANCY_NOTIMPLEMENTED) || defined(REDUNDANCYCYCLEEND_NOTIMPLEMENTED)
	#define USE_redundancycycleend
	#define EXT_redundancycycleend
	#define GET_redundancycycleend(fl)  ERR_NOTIMPLEMENTED
	#define CAL_redundancycycleend(p0) 
	#define CHK_redundancycycleend  FALSE
	#define EXP_redundancycycleend  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_redundancycycleend
	#define EXT_redundancycycleend
	#define GET_redundancycycleend(fl)  CAL_CMGETAPI( "redundancycycleend" ) 
	#define CAL_redundancycycleend  redundancycycleend
	#define CHK_redundancycycleend  TRUE
	#define EXP_redundancycycleend  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"redundancycycleend", (RTS_UINTPTR)redundancycycleend, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCY_EXTERNAL)
	#define USE_redundancycycleend
	#define EXT_redundancycycleend
	#define GET_redundancycycleend(fl)  CAL_CMGETAPI( "redundancycycleend" ) 
	#define CAL_redundancycycleend  redundancycycleend
	#define CHK_redundancycycleend  TRUE
	#define EXP_redundancycycleend  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"redundancycycleend", (RTS_UINTPTR)redundancycycleend, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyredundancycycleend
	#define EXT_CmpRedundancyredundancycycleend
	#define GET_CmpRedundancyredundancycycleend  ERR_OK
	#define CAL_CmpRedundancyredundancycycleend  redundancycycleend
	#define CHK_CmpRedundancyredundancycycleend  TRUE
	#define EXP_CmpRedundancyredundancycycleend  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"redundancycycleend", (RTS_UINTPTR)redundancycycleend, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_redundancycycleend
	#define EXT_redundancycycleend
	#define GET_redundancycycleend(fl)  CAL_CMGETAPI( "redundancycycleend" ) 
	#define CAL_redundancycycleend  redundancycycleend
	#define CHK_redundancycycleend  TRUE
	#define EXP_redundancycycleend  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"redundancycycleend", (RTS_UINTPTR)redundancycycleend, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_redundancycycleend  PFREDUNDANCYCYCLEEND_IEC pfredundancycycleend;
	#define EXT_redundancycycleend  extern PFREDUNDANCYCYCLEEND_IEC pfredundancycycleend;
	#define GET_redundancycycleend(fl)  s_pfCMGetAPI2( "redundancycycleend", (RTS_VOID_FCTPTR *)&pfredundancycycleend, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_redundancycycleend  pfredundancycycleend
	#define CHK_redundancycycleend  (pfredundancycycleend != NULL)
	#define EXP_redundancycycleend   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"redundancycycleend", (RTS_UINTPTR)redundancycycleend, 1, 0x0, 0x0) 
#endif


/**
 * <description>redundancycyclestart</description>
 */
typedef struct tagredundancycyclestart_struct
{
	RTS_IEC_BOOL RedundancyCycleStart;	/* VAR_OUTPUT */
} redundancycyclestart_struct;

void CDECL CDECL_EXT redundancycyclestart(redundancycyclestart_struct *p);
typedef void (CDECL CDECL_EXT* PFREDUNDANCYCYCLESTART_IEC) (redundancycyclestart_struct *p);
#if defined(CMPREDUNDANCY_NOTIMPLEMENTED) || defined(REDUNDANCYCYCLESTART_NOTIMPLEMENTED)
	#define USE_redundancycyclestart
	#define EXT_redundancycyclestart
	#define GET_redundancycyclestart(fl)  ERR_NOTIMPLEMENTED
	#define CAL_redundancycyclestart(p0) 
	#define CHK_redundancycyclestart  FALSE
	#define EXP_redundancycyclestart  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_redundancycyclestart
	#define EXT_redundancycyclestart
	#define GET_redundancycyclestart(fl)  CAL_CMGETAPI( "redundancycyclestart" ) 
	#define CAL_redundancycyclestart  redundancycyclestart
	#define CHK_redundancycyclestart  TRUE
	#define EXP_redundancycyclestart  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"redundancycyclestart", (RTS_UINTPTR)redundancycyclestart, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCY_EXTERNAL)
	#define USE_redundancycyclestart
	#define EXT_redundancycyclestart
	#define GET_redundancycyclestart(fl)  CAL_CMGETAPI( "redundancycyclestart" ) 
	#define CAL_redundancycyclestart  redundancycyclestart
	#define CHK_redundancycyclestart  TRUE
	#define EXP_redundancycyclestart  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"redundancycyclestart", (RTS_UINTPTR)redundancycyclestart, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyredundancycyclestart
	#define EXT_CmpRedundancyredundancycyclestart
	#define GET_CmpRedundancyredundancycyclestart  ERR_OK
	#define CAL_CmpRedundancyredundancycyclestart  redundancycyclestart
	#define CHK_CmpRedundancyredundancycyclestart  TRUE
	#define EXP_CmpRedundancyredundancycyclestart  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"redundancycyclestart", (RTS_UINTPTR)redundancycyclestart, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_redundancycyclestart
	#define EXT_redundancycyclestart
	#define GET_redundancycyclestart(fl)  CAL_CMGETAPI( "redundancycyclestart" ) 
	#define CAL_redundancycyclestart  redundancycyclestart
	#define CHK_redundancycyclestart  TRUE
	#define EXP_redundancycyclestart  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"redundancycyclestart", (RTS_UINTPTR)redundancycyclestart, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_redundancycyclestart  PFREDUNDANCYCYCLESTART_IEC pfredundancycyclestart;
	#define EXT_redundancycyclestart  extern PFREDUNDANCYCYCLESTART_IEC pfredundancycyclestart;
	#define GET_redundancycyclestart(fl)  s_pfCMGetAPI2( "redundancycyclestart", (RTS_VOID_FCTPTR *)&pfredundancycyclestart, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_redundancycyclestart  pfredundancycyclestart
	#define CHK_redundancycyclestart  (pfredundancycyclestart != NULL)
	#define EXP_redundancycyclestart   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"redundancycyclestart", (RTS_UINTPTR)redundancycyclestart, 1, 0x0, 0x0) 
#endif


/**
 * <description>getredundancystate</description>
 */
typedef struct taggetredundancystate_struct
{
	RedundancyState *pState;			/* VAR_INPUT */
	RTS_IEC_BOOL GetRedundancyState;	/* VAR_OUTPUT */
} getredundancystate_struct;

void CDECL CDECL_EXT getredundancystate(getredundancystate_struct *p);
typedef void (CDECL CDECL_EXT* PFGETREDUNDANCYSTATE_IEC) (getredundancystate_struct *p);
#if defined(CMPREDUNDANCY_NOTIMPLEMENTED) || defined(GETREDUNDANCYSTATE_NOTIMPLEMENTED)
	#define USE_getredundancystate
	#define EXT_getredundancystate
	#define GET_getredundancystate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_getredundancystate(p0) 
	#define CHK_getredundancystate  FALSE
	#define EXP_getredundancystate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_getredundancystate
	#define EXT_getredundancystate
	#define GET_getredundancystate(fl)  CAL_CMGETAPI( "getredundancystate" ) 
	#define CAL_getredundancystate  getredundancystate
	#define CHK_getredundancystate  TRUE
	#define EXP_getredundancystate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"getredundancystate", (RTS_UINTPTR)getredundancystate, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCY_EXTERNAL)
	#define USE_getredundancystate
	#define EXT_getredundancystate
	#define GET_getredundancystate(fl)  CAL_CMGETAPI( "getredundancystate" ) 
	#define CAL_getredundancystate  getredundancystate
	#define CHK_getredundancystate  TRUE
	#define EXP_getredundancystate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"getredundancystate", (RTS_UINTPTR)getredundancystate, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancygetredundancystate
	#define EXT_CmpRedundancygetredundancystate
	#define GET_CmpRedundancygetredundancystate  ERR_OK
	#define CAL_CmpRedundancygetredundancystate  getredundancystate
	#define CHK_CmpRedundancygetredundancystate  TRUE
	#define EXP_CmpRedundancygetredundancystate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"getredundancystate", (RTS_UINTPTR)getredundancystate, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_getredundancystate
	#define EXT_getredundancystate
	#define GET_getredundancystate(fl)  CAL_CMGETAPI( "getredundancystate" ) 
	#define CAL_getredundancystate  getredundancystate
	#define CHK_getredundancystate  TRUE
	#define EXP_getredundancystate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"getredundancystate", (RTS_UINTPTR)getredundancystate, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_getredundancystate  PFGETREDUNDANCYSTATE_IEC pfgetredundancystate;
	#define EXT_getredundancystate  extern PFGETREDUNDANCYSTATE_IEC pfgetredundancystate;
	#define GET_getredundancystate(fl)  s_pfCMGetAPI2( "getredundancystate", (RTS_VOID_FCTPTR *)&pfgetredundancystate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_getredundancystate  pfgetredundancystate
	#define CHK_getredundancystate  (pfgetredundancystate != NULL)
	#define EXP_getredundancystate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"getredundancystate", (RTS_UINTPTR)getredundancystate, 1, 0x0, 0x0) 
#endif


/**
 * <description>switchtosimulation</description>
 */
typedef struct tagswitchtosimulation_struct
{
	RTS_IEC_BOOL SwitchToSimulation;	/* VAR_OUTPUT */
} switchtosimulation_struct;

void CDECL CDECL_EXT switchtosimulation(switchtosimulation_struct *p);
typedef void (CDECL CDECL_EXT* PFSWITCHTOSIMULATION_IEC) (switchtosimulation_struct *p);
#if defined(CMPREDUNDANCY_NOTIMPLEMENTED) || defined(SWITCHTOSIMULATION_NOTIMPLEMENTED)
	#define USE_switchtosimulation
	#define EXT_switchtosimulation
	#define GET_switchtosimulation(fl)  ERR_NOTIMPLEMENTED
	#define CAL_switchtosimulation(p0) 
	#define CHK_switchtosimulation  FALSE
	#define EXP_switchtosimulation  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_switchtosimulation
	#define EXT_switchtosimulation
	#define GET_switchtosimulation(fl)  CAL_CMGETAPI( "switchtosimulation" ) 
	#define CAL_switchtosimulation  switchtosimulation
	#define CHK_switchtosimulation  TRUE
	#define EXP_switchtosimulation  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"switchtosimulation", (RTS_UINTPTR)switchtosimulation, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCY_EXTERNAL)
	#define USE_switchtosimulation
	#define EXT_switchtosimulation
	#define GET_switchtosimulation(fl)  CAL_CMGETAPI( "switchtosimulation" ) 
	#define CAL_switchtosimulation  switchtosimulation
	#define CHK_switchtosimulation  TRUE
	#define EXP_switchtosimulation  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"switchtosimulation", (RTS_UINTPTR)switchtosimulation, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyswitchtosimulation
	#define EXT_CmpRedundancyswitchtosimulation
	#define GET_CmpRedundancyswitchtosimulation  ERR_OK
	#define CAL_CmpRedundancyswitchtosimulation  switchtosimulation
	#define CHK_CmpRedundancyswitchtosimulation  TRUE
	#define EXP_CmpRedundancyswitchtosimulation  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"switchtosimulation", (RTS_UINTPTR)switchtosimulation, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_switchtosimulation
	#define EXT_switchtosimulation
	#define GET_switchtosimulation(fl)  CAL_CMGETAPI( "switchtosimulation" ) 
	#define CAL_switchtosimulation  switchtosimulation
	#define CHK_switchtosimulation  TRUE
	#define EXP_switchtosimulation  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"switchtosimulation", (RTS_UINTPTR)switchtosimulation, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_switchtosimulation  PFSWITCHTOSIMULATION_IEC pfswitchtosimulation;
	#define EXT_switchtosimulation  extern PFSWITCHTOSIMULATION_IEC pfswitchtosimulation;
	#define GET_switchtosimulation(fl)  s_pfCMGetAPI2( "switchtosimulation", (RTS_VOID_FCTPTR *)&pfswitchtosimulation, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_switchtosimulation  pfswitchtosimulation
	#define CHK_switchtosimulation  (pfswitchtosimulation != NULL)
	#define EXP_switchtosimulation   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"switchtosimulation", (RTS_UINTPTR)switchtosimulation, 1, 0x0, 0x0) 
#endif


/**
 * <description>switchtostandalone</description>
 */
typedef struct tagswitchtostandalone_struct
{
	RTS_IEC_BOOL SwitchToStandalone;	/* VAR_OUTPUT */	
} switchtostandalone_struct;

void CDECL CDECL_EXT switchtostandalone(switchtostandalone_struct *p);
typedef void (CDECL CDECL_EXT* PFSWITCHTOSTANDALONE_IEC) (switchtostandalone_struct *p);
#if defined(CMPREDUNDANCY_NOTIMPLEMENTED) || defined(SWITCHTOSTANDALONE_NOTIMPLEMENTED)
	#define USE_switchtostandalone
	#define EXT_switchtostandalone
	#define GET_switchtostandalone(fl)  ERR_NOTIMPLEMENTED
	#define CAL_switchtostandalone(p0) 
	#define CHK_switchtostandalone  FALSE
	#define EXP_switchtostandalone  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_switchtostandalone
	#define EXT_switchtostandalone
	#define GET_switchtostandalone(fl)  CAL_CMGETAPI( "switchtostandalone" ) 
	#define CAL_switchtostandalone  switchtostandalone
	#define CHK_switchtostandalone  TRUE
	#define EXP_switchtostandalone  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"switchtostandalone", (RTS_UINTPTR)switchtostandalone, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCY_EXTERNAL)
	#define USE_switchtostandalone
	#define EXT_switchtostandalone
	#define GET_switchtostandalone(fl)  CAL_CMGETAPI( "switchtostandalone" ) 
	#define CAL_switchtostandalone  switchtostandalone
	#define CHK_switchtostandalone  TRUE
	#define EXP_switchtostandalone  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"switchtostandalone", (RTS_UINTPTR)switchtostandalone, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyswitchtostandalone
	#define EXT_CmpRedundancyswitchtostandalone
	#define GET_CmpRedundancyswitchtostandalone  ERR_OK
	#define CAL_CmpRedundancyswitchtostandalone  switchtostandalone
	#define CHK_CmpRedundancyswitchtostandalone  TRUE
	#define EXP_CmpRedundancyswitchtostandalone  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"switchtostandalone", (RTS_UINTPTR)switchtostandalone, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_switchtostandalone
	#define EXT_switchtostandalone
	#define GET_switchtostandalone(fl)  CAL_CMGETAPI( "switchtostandalone" ) 
	#define CAL_switchtostandalone  switchtostandalone
	#define CHK_switchtostandalone  TRUE
	#define EXP_switchtostandalone  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"switchtostandalone", (RTS_UINTPTR)switchtostandalone, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_switchtostandalone  PFSWITCHTOSTANDALONE_IEC pfswitchtostandalone;
	#define EXT_switchtostandalone  extern PFSWITCHTOSTANDALONE_IEC pfswitchtostandalone;
	#define GET_switchtostandalone(fl)  s_pfCMGetAPI2( "switchtostandalone", (RTS_VOID_FCTPTR *)&pfswitchtostandalone, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_switchtostandalone  pfswitchtostandalone
	#define CHK_switchtostandalone  (pfswitchtostandalone != NULL)
	#define EXP_switchtostandalone   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"switchtostandalone", (RTS_UINTPTR)switchtostandalone, 1, 0x0, 0x0) 
#endif


/**
 * <description>switchtostandby</description>
 */
typedef struct tagswitchtostandby_struct
{
	RTS_IEC_BOOL SwitchToStandby;		/* VAR_OUTPUT */
} switchtostandby_struct;

void CDECL CDECL_EXT switchtostandby(switchtostandby_struct *p);
typedef void (CDECL CDECL_EXT* PFSWITCHTOSTANDBY_IEC) (switchtostandby_struct *p);
#if defined(CMPREDUNDANCY_NOTIMPLEMENTED) || defined(SWITCHTOSTANDBY_NOTIMPLEMENTED)
	#define USE_switchtostandby
	#define EXT_switchtostandby
	#define GET_switchtostandby(fl)  ERR_NOTIMPLEMENTED
	#define CAL_switchtostandby(p0) 
	#define CHK_switchtostandby  FALSE
	#define EXP_switchtostandby  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_switchtostandby
	#define EXT_switchtostandby
	#define GET_switchtostandby(fl)  CAL_CMGETAPI( "switchtostandby" ) 
	#define CAL_switchtostandby  switchtostandby
	#define CHK_switchtostandby  TRUE
	#define EXP_switchtostandby  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"switchtostandby", (RTS_UINTPTR)switchtostandby, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCY_EXTERNAL)
	#define USE_switchtostandby
	#define EXT_switchtostandby
	#define GET_switchtostandby(fl)  CAL_CMGETAPI( "switchtostandby" ) 
	#define CAL_switchtostandby  switchtostandby
	#define CHK_switchtostandby  TRUE
	#define EXP_switchtostandby  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"switchtostandby", (RTS_UINTPTR)switchtostandby, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyswitchtostandby
	#define EXT_CmpRedundancyswitchtostandby
	#define GET_CmpRedundancyswitchtostandby  ERR_OK
	#define CAL_CmpRedundancyswitchtostandby  switchtostandby
	#define CHK_CmpRedundancyswitchtostandby  TRUE
	#define EXP_CmpRedundancyswitchtostandby  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"switchtostandby", (RTS_UINTPTR)switchtostandby, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_switchtostandby
	#define EXT_switchtostandby
	#define GET_switchtostandby(fl)  CAL_CMGETAPI( "switchtostandby" ) 
	#define CAL_switchtostandby  switchtostandby
	#define CHK_switchtostandby  TRUE
	#define EXP_switchtostandby  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"switchtostandby", (RTS_UINTPTR)switchtostandby, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_switchtostandby  PFSWITCHTOSTANDBY_IEC pfswitchtostandby;
	#define EXT_switchtostandby  extern PFSWITCHTOSTANDBY_IEC pfswitchtostandby;
	#define GET_switchtostandby(fl)  s_pfCMGetAPI2( "switchtostandby", (RTS_VOID_FCTPTR *)&pfswitchtostandby, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_switchtostandby  pfswitchtostandby
	#define CHK_switchtostandby  (pfswitchtostandby != NULL)
	#define EXP_switchtostandby   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"switchtostandby", (RTS_UINTPTR)switchtostandby, 1, 0x0, 0x0) 
#endif


/**
 * <description>switchtoactive</description>
 */
typedef struct tagswitchtoactive_struct
{
	RTS_IEC_BOOL SwitchToActive;		/* VAR_OUTPUT */
} switchtoactive_struct;

void CDECL CDECL_EXT switchtoactive(switchtoactive_struct *p);
typedef void (CDECL CDECL_EXT* PFSWITCHTOACTIVE_IEC) (switchtoactive_struct *p);
#if defined(CMPREDUNDANCY_NOTIMPLEMENTED) || defined(SWITCHTOACTIVE_NOTIMPLEMENTED)
	#define USE_switchtoactive
	#define EXT_switchtoactive
	#define GET_switchtoactive(fl)  ERR_NOTIMPLEMENTED
	#define CAL_switchtoactive(p0) 
	#define CHK_switchtoactive  FALSE
	#define EXP_switchtoactive  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_switchtoactive
	#define EXT_switchtoactive
	#define GET_switchtoactive(fl)  CAL_CMGETAPI( "switchtoactive" ) 
	#define CAL_switchtoactive  switchtoactive
	#define CHK_switchtoactive  TRUE
	#define EXP_switchtoactive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"switchtoactive", (RTS_UINTPTR)switchtoactive, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCY_EXTERNAL)
	#define USE_switchtoactive
	#define EXT_switchtoactive
	#define GET_switchtoactive(fl)  CAL_CMGETAPI( "switchtoactive" ) 
	#define CAL_switchtoactive  switchtoactive
	#define CHK_switchtoactive  TRUE
	#define EXP_switchtoactive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"switchtoactive", (RTS_UINTPTR)switchtoactive, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyswitchtoactive
	#define EXT_CmpRedundancyswitchtoactive
	#define GET_CmpRedundancyswitchtoactive  ERR_OK
	#define CAL_CmpRedundancyswitchtoactive  switchtoactive
	#define CHK_CmpRedundancyswitchtoactive  TRUE
	#define EXP_CmpRedundancyswitchtoactive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"switchtoactive", (RTS_UINTPTR)switchtoactive, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_switchtoactive
	#define EXT_switchtoactive
	#define GET_switchtoactive(fl)  CAL_CMGETAPI( "switchtoactive" ) 
	#define CAL_switchtoactive  switchtoactive
	#define CHK_switchtoactive  TRUE
	#define EXP_switchtoactive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"switchtoactive", (RTS_UINTPTR)switchtoactive, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_switchtoactive  PFSWITCHTOACTIVE_IEC pfswitchtoactive;
	#define EXT_switchtoactive  extern PFSWITCHTOACTIVE_IEC pfswitchtoactive;
	#define GET_switchtoactive(fl)  s_pfCMGetAPI2( "switchtoactive", (RTS_VOID_FCTPTR *)&pfswitchtoactive, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_switchtoactive  pfswitchtoactive
	#define CHK_switchtoactive  (pfswitchtoactive != NULL)
	#define EXP_switchtoactive   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"switchtoactive", (RTS_UINTPTR)switchtoactive, 1, 0x0, 0x0) 
#endif


/**
 * <description>synchronize</description>
 */
typedef struct tagsynchronize_struct
{
	RTS_IEC_BOOL Synchronize;			/* VAR_OUTPUT */
} synchronize_struct;

void CDECL CDECL_EXT synchronize(synchronize_struct *p);
typedef void (CDECL CDECL_EXT* PFSYNCHRONIZE_IEC) (synchronize_struct *p);
#if defined(CMPREDUNDANCY_NOTIMPLEMENTED) || defined(SYNCHRONIZE_NOTIMPLEMENTED)
	#define USE_synchronize
	#define EXT_synchronize
	#define GET_synchronize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_synchronize(p0) 
	#define CHK_synchronize  FALSE
	#define EXP_synchronize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_synchronize
	#define EXT_synchronize
	#define GET_synchronize(fl)  CAL_CMGETAPI( "synchronize" ) 
	#define CAL_synchronize  synchronize
	#define CHK_synchronize  TRUE
	#define EXP_synchronize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"synchronize", (RTS_UINTPTR)synchronize, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCY_EXTERNAL)
	#define USE_synchronize
	#define EXT_synchronize
	#define GET_synchronize(fl)  CAL_CMGETAPI( "synchronize" ) 
	#define CAL_synchronize  synchronize
	#define CHK_synchronize  TRUE
	#define EXP_synchronize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"synchronize", (RTS_UINTPTR)synchronize, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancysynchronize
	#define EXT_CmpRedundancysynchronize
	#define GET_CmpRedundancysynchronize  ERR_OK
	#define CAL_CmpRedundancysynchronize  synchronize
	#define CHK_CmpRedundancysynchronize  TRUE
	#define EXP_CmpRedundancysynchronize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"synchronize", (RTS_UINTPTR)synchronize, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_synchronize
	#define EXT_synchronize
	#define GET_synchronize(fl)  CAL_CMGETAPI( "synchronize" ) 
	#define CAL_synchronize  synchronize
	#define CHK_synchronize  TRUE
	#define EXP_synchronize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"synchronize", (RTS_UINTPTR)synchronize, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_synchronize  PFSYNCHRONIZE_IEC pfsynchronize;
	#define EXT_synchronize  extern PFSYNCHRONIZE_IEC pfsynchronize;
	#define GET_synchronize(fl)  s_pfCMGetAPI2( "synchronize", (RTS_VOID_FCTPTR *)&pfsynchronize, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_synchronize  pfsynchronize
	#define CHK_synchronize  (pfsynchronize != NULL)
	#define EXP_synchronize   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"synchronize", (RTS_UINTPTR)synchronize, 1, 0x0, 0x0) 
#endif


/**
 * <description>This function registers the memory area as redundant area</description>
 * <param name="pbyArea" type="IN">Start address</param>
 * <param name="ulSize" type="IN">Size</param>
 * <param name="eType" type="IN">Redundancy area type</param>
 * <result>TRUE in case of success, otherwise FALSE</result>
 */
RTS_IEC_BOOL CDECL RedundancyAreaRegister(unsigned char *pbyArea, RTS_UI32 ulSize, RDCY_AREA_TYPE eType);
typedef RTS_IEC_BOOL (CDECL * PFREDUNDANCYAREAREGISTER) (unsigned char *pbyArea, RTS_UI32 ulSize, RDCY_AREA_TYPE eType);
#if defined(CMPREDUNDANCY_NOTIMPLEMENTED) || defined(REDUNDANCYAREAREGISTER_NOTIMPLEMENTED)
	#define USE_RedundancyAreaRegister
	#define EXT_RedundancyAreaRegister
	#define GET_RedundancyAreaRegister(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RedundancyAreaRegister(p0,p1,p2)  (RTS_IEC_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_RedundancyAreaRegister  FALSE
	#define EXP_RedundancyAreaRegister  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RedundancyAreaRegister
	#define EXT_RedundancyAreaRegister
	#define GET_RedundancyAreaRegister(fl)  CAL_CMGETAPI( "RedundancyAreaRegister" ) 
	#define CAL_RedundancyAreaRegister  RedundancyAreaRegister
	#define CHK_RedundancyAreaRegister  TRUE
	#define EXP_RedundancyAreaRegister  CAL_CMEXPAPI( "RedundancyAreaRegister" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCY_EXTERNAL)
	#define USE_RedundancyAreaRegister
	#define EXT_RedundancyAreaRegister
	#define GET_RedundancyAreaRegister(fl)  CAL_CMGETAPI( "RedundancyAreaRegister" ) 
	#define CAL_RedundancyAreaRegister  RedundancyAreaRegister
	#define CHK_RedundancyAreaRegister  TRUE
	#define EXP_RedundancyAreaRegister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancyAreaRegister", (RTS_UINTPTR)RedundancyAreaRegister, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyRedundancyAreaRegister
	#define EXT_CmpRedundancyRedundancyAreaRegister
	#define GET_CmpRedundancyRedundancyAreaRegister  ERR_OK
	#define CAL_CmpRedundancyRedundancyAreaRegister pICmpRedundancy->IRedundancyAreaRegister
	#define CHK_CmpRedundancyRedundancyAreaRegister (pICmpRedundancy != NULL)
	#define EXP_CmpRedundancyRedundancyAreaRegister  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RedundancyAreaRegister
	#define EXT_RedundancyAreaRegister
	#define GET_RedundancyAreaRegister(fl)  CAL_CMGETAPI( "RedundancyAreaRegister" ) 
	#define CAL_RedundancyAreaRegister pICmpRedundancy->IRedundancyAreaRegister
	#define CHK_RedundancyAreaRegister (pICmpRedundancy != NULL)
	#define EXP_RedundancyAreaRegister  CAL_CMEXPAPI( "RedundancyAreaRegister" ) 
#else /* DYNAMIC_LINK */
	#define USE_RedundancyAreaRegister  PFREDUNDANCYAREAREGISTER pfRedundancyAreaRegister;
	#define EXT_RedundancyAreaRegister  extern PFREDUNDANCYAREAREGISTER pfRedundancyAreaRegister;
	#define GET_RedundancyAreaRegister(fl)  s_pfCMGetAPI2( "RedundancyAreaRegister", (RTS_VOID_FCTPTR *)&pfRedundancyAreaRegister, (fl), 0, 0)
	#define CAL_RedundancyAreaRegister  pfRedundancyAreaRegister
	#define CHK_RedundancyAreaRegister  (pfRedundancyAreaRegister != NULL)
	#define EXP_RedundancyAreaRegister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancyAreaRegister", (RTS_UINTPTR)RedundancyAreaRegister, 0, 0) 
#endif




/**
 * <description>This function registers a memory area segment as redundant area</description>
 * <param name="usSegment" type="IN">Segment type</param>
 * <param name="eType" type="IN">Redundancy area type</param>
 * <result>TRUE in case of success, otherwise FALSE</result>
 */
RTS_IEC_BOOL CDECL RedundancyAreaRegisterSegment(RTS_UI16 usSegment, RDCY_AREA_TYPE eType);
typedef RTS_IEC_BOOL (CDECL * PFREDUNDANCYAREAREGISTERSEGMENT) (RTS_UI16 usSegment, RDCY_AREA_TYPE eType);
#if defined(CMPREDUNDANCY_NOTIMPLEMENTED) || defined(REDUNDANCYAREAREGISTERSEGMENT_NOTIMPLEMENTED)
	#define USE_RedundancyAreaRegisterSegment
	#define EXT_RedundancyAreaRegisterSegment
	#define GET_RedundancyAreaRegisterSegment(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RedundancyAreaRegisterSegment(p0,p1)  (RTS_IEC_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_RedundancyAreaRegisterSegment  FALSE
	#define EXP_RedundancyAreaRegisterSegment  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RedundancyAreaRegisterSegment
	#define EXT_RedundancyAreaRegisterSegment
	#define GET_RedundancyAreaRegisterSegment(fl)  CAL_CMGETAPI( "RedundancyAreaRegisterSegment" ) 
	#define CAL_RedundancyAreaRegisterSegment  RedundancyAreaRegisterSegment
	#define CHK_RedundancyAreaRegisterSegment  TRUE
	#define EXP_RedundancyAreaRegisterSegment  CAL_CMEXPAPI( "RedundancyAreaRegisterSegment" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCY_EXTERNAL)
	#define USE_RedundancyAreaRegisterSegment
	#define EXT_RedundancyAreaRegisterSegment
	#define GET_RedundancyAreaRegisterSegment(fl)  CAL_CMGETAPI( "RedundancyAreaRegisterSegment" ) 
	#define CAL_RedundancyAreaRegisterSegment  RedundancyAreaRegisterSegment
	#define CHK_RedundancyAreaRegisterSegment  TRUE
	#define EXP_RedundancyAreaRegisterSegment  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancyAreaRegisterSegment", (RTS_UINTPTR)RedundancyAreaRegisterSegment, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyRedundancyAreaRegisterSegment
	#define EXT_CmpRedundancyRedundancyAreaRegisterSegment
	#define GET_CmpRedundancyRedundancyAreaRegisterSegment  ERR_OK
	#define CAL_CmpRedundancyRedundancyAreaRegisterSegment pICmpRedundancy->IRedundancyAreaRegisterSegment
	#define CHK_CmpRedundancyRedundancyAreaRegisterSegment (pICmpRedundancy != NULL)
	#define EXP_CmpRedundancyRedundancyAreaRegisterSegment  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RedundancyAreaRegisterSegment
	#define EXT_RedundancyAreaRegisterSegment
	#define GET_RedundancyAreaRegisterSegment(fl)  CAL_CMGETAPI( "RedundancyAreaRegisterSegment" ) 
	#define CAL_RedundancyAreaRegisterSegment pICmpRedundancy->IRedundancyAreaRegisterSegment
	#define CHK_RedundancyAreaRegisterSegment (pICmpRedundancy != NULL)
	#define EXP_RedundancyAreaRegisterSegment  CAL_CMEXPAPI( "RedundancyAreaRegisterSegment" ) 
#else /* DYNAMIC_LINK */
	#define USE_RedundancyAreaRegisterSegment  PFREDUNDANCYAREAREGISTERSEGMENT pfRedundancyAreaRegisterSegment;
	#define EXT_RedundancyAreaRegisterSegment  extern PFREDUNDANCYAREAREGISTERSEGMENT pfRedundancyAreaRegisterSegment;
	#define GET_RedundancyAreaRegisterSegment(fl)  s_pfCMGetAPI2( "RedundancyAreaRegisterSegment", (RTS_VOID_FCTPTR *)&pfRedundancyAreaRegisterSegment, (fl), 0, 0)
	#define CAL_RedundancyAreaRegisterSegment  pfRedundancyAreaRegisterSegment
	#define CHK_RedundancyAreaRegisterSegment  (pfRedundancyAreaRegisterSegment != NULL)
	#define EXP_RedundancyAreaRegisterSegment  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancyAreaRegisterSegment", (RTS_UINTPTR)RedundancyAreaRegisterSegment, 0, 0) 
#endif




/**
 * <description>This function unregisters all redundancy areas</description>
 * <result>TRUE in case of success, otherwise FALSE</result>
 */
RTS_IEC_BOOL CDECL RedundancyUnregisterAreas(void);
typedef RTS_IEC_BOOL (CDECL * PFREDUNDANCYUNREGISTERAREAS) (void);
#if defined(CMPREDUNDANCY_NOTIMPLEMENTED) || defined(REDUNDANCYUNREGISTERAREAS_NOTIMPLEMENTED)
	#define USE_RedundancyUnregisterAreas
	#define EXT_RedundancyUnregisterAreas
	#define GET_RedundancyUnregisterAreas(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RedundancyUnregisterAreas()  (RTS_IEC_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_RedundancyUnregisterAreas  FALSE
	#define EXP_RedundancyUnregisterAreas  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RedundancyUnregisterAreas
	#define EXT_RedundancyUnregisterAreas
	#define GET_RedundancyUnregisterAreas(fl)  CAL_CMGETAPI( "RedundancyUnregisterAreas" ) 
	#define CAL_RedundancyUnregisterAreas  RedundancyUnregisterAreas
	#define CHK_RedundancyUnregisterAreas  TRUE
	#define EXP_RedundancyUnregisterAreas  CAL_CMEXPAPI( "RedundancyUnregisterAreas" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCY_EXTERNAL)
	#define USE_RedundancyUnregisterAreas
	#define EXT_RedundancyUnregisterAreas
	#define GET_RedundancyUnregisterAreas(fl)  CAL_CMGETAPI( "RedundancyUnregisterAreas" ) 
	#define CAL_RedundancyUnregisterAreas  RedundancyUnregisterAreas
	#define CHK_RedundancyUnregisterAreas  TRUE
	#define EXP_RedundancyUnregisterAreas  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancyUnregisterAreas", (RTS_UINTPTR)RedundancyUnregisterAreas, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyRedundancyUnregisterAreas
	#define EXT_CmpRedundancyRedundancyUnregisterAreas
	#define GET_CmpRedundancyRedundancyUnregisterAreas  ERR_OK
	#define CAL_CmpRedundancyRedundancyUnregisterAreas pICmpRedundancy->IRedundancyUnregisterAreas
	#define CHK_CmpRedundancyRedundancyUnregisterAreas (pICmpRedundancy != NULL)
	#define EXP_CmpRedundancyRedundancyUnregisterAreas  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RedundancyUnregisterAreas
	#define EXT_RedundancyUnregisterAreas
	#define GET_RedundancyUnregisterAreas(fl)  CAL_CMGETAPI( "RedundancyUnregisterAreas" ) 
	#define CAL_RedundancyUnregisterAreas pICmpRedundancy->IRedundancyUnregisterAreas
	#define CHK_RedundancyUnregisterAreas (pICmpRedundancy != NULL)
	#define EXP_RedundancyUnregisterAreas  CAL_CMEXPAPI( "RedundancyUnregisterAreas" ) 
#else /* DYNAMIC_LINK */
	#define USE_RedundancyUnregisterAreas  PFREDUNDANCYUNREGISTERAREAS pfRedundancyUnregisterAreas;
	#define EXT_RedundancyUnregisterAreas  extern PFREDUNDANCYUNREGISTERAREAS pfRedundancyUnregisterAreas;
	#define GET_RedundancyUnregisterAreas(fl)  s_pfCMGetAPI2( "RedundancyUnregisterAreas", (RTS_VOID_FCTPTR *)&pfRedundancyUnregisterAreas, (fl), 0, 0)
	#define CAL_RedundancyUnregisterAreas  pfRedundancyUnregisterAreas
	#define CHK_RedundancyUnregisterAreas  (pfRedundancyUnregisterAreas != NULL)
	#define EXP_RedundancyUnregisterAreas  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancyUnregisterAreas", (RTS_UINTPTR)RedundancyUnregisterAreas, 0, 0) 
#endif




/**
 * <description>This function is called at end of a cycle of the redundancy task</description>
 * <result>TRUE in case of success, otherwise FALSE</result>
 */
RTS_IEC_BOOL CDECL RedundancyCycleEnd(void);
typedef RTS_IEC_BOOL (CDECL * PFREDUNDANCYCYCLEEND) (void);
#if defined(CMPREDUNDANCY_NOTIMPLEMENTED) || defined(REDUNDANCYCYCLEEND_NOTIMPLEMENTED)
	#define USE_RedundancyCycleEnd
	#define EXT_RedundancyCycleEnd
	#define GET_RedundancyCycleEnd(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RedundancyCycleEnd()  (RTS_IEC_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_RedundancyCycleEnd  FALSE
	#define EXP_RedundancyCycleEnd  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RedundancyCycleEnd
	#define EXT_RedundancyCycleEnd
	#define GET_RedundancyCycleEnd(fl)  CAL_CMGETAPI( "RedundancyCycleEnd" ) 
	#define CAL_RedundancyCycleEnd  RedundancyCycleEnd
	#define CHK_RedundancyCycleEnd  TRUE
	#define EXP_RedundancyCycleEnd  CAL_CMEXPAPI( "RedundancyCycleEnd" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCY_EXTERNAL)
	#define USE_RedundancyCycleEnd
	#define EXT_RedundancyCycleEnd
	#define GET_RedundancyCycleEnd(fl)  CAL_CMGETAPI( "RedundancyCycleEnd" ) 
	#define CAL_RedundancyCycleEnd  RedundancyCycleEnd
	#define CHK_RedundancyCycleEnd  TRUE
	#define EXP_RedundancyCycleEnd  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancyCycleEnd", (RTS_UINTPTR)RedundancyCycleEnd, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyRedundancyCycleEnd
	#define EXT_CmpRedundancyRedundancyCycleEnd
	#define GET_CmpRedundancyRedundancyCycleEnd  ERR_OK
	#define CAL_CmpRedundancyRedundancyCycleEnd pICmpRedundancy->IRedundancyCycleEnd
	#define CHK_CmpRedundancyRedundancyCycleEnd (pICmpRedundancy != NULL)
	#define EXP_CmpRedundancyRedundancyCycleEnd  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RedundancyCycleEnd
	#define EXT_RedundancyCycleEnd
	#define GET_RedundancyCycleEnd(fl)  CAL_CMGETAPI( "RedundancyCycleEnd" ) 
	#define CAL_RedundancyCycleEnd pICmpRedundancy->IRedundancyCycleEnd
	#define CHK_RedundancyCycleEnd (pICmpRedundancy != NULL)
	#define EXP_RedundancyCycleEnd  CAL_CMEXPAPI( "RedundancyCycleEnd" ) 
#else /* DYNAMIC_LINK */
	#define USE_RedundancyCycleEnd  PFREDUNDANCYCYCLEEND pfRedundancyCycleEnd;
	#define EXT_RedundancyCycleEnd  extern PFREDUNDANCYCYCLEEND pfRedundancyCycleEnd;
	#define GET_RedundancyCycleEnd(fl)  s_pfCMGetAPI2( "RedundancyCycleEnd", (RTS_VOID_FCTPTR *)&pfRedundancyCycleEnd, (fl), 0, 0)
	#define CAL_RedundancyCycleEnd  pfRedundancyCycleEnd
	#define CHK_RedundancyCycleEnd  (pfRedundancyCycleEnd != NULL)
	#define EXP_RedundancyCycleEnd  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancyCycleEnd", (RTS_UINTPTR)RedundancyCycleEnd, 0, 0) 
#endif




/**
 * <description>This function is called at beginning of a cycle of the redundancy task</description>
 * <result>TRUE in case of success, otherwise FALSE</result>
 */
RTS_IEC_BOOL CDECL RedundancyCycleStart(void);
typedef RTS_IEC_BOOL (CDECL * PFREDUNDANCYCYCLESTART) (void);
#if defined(CMPREDUNDANCY_NOTIMPLEMENTED) || defined(REDUNDANCYCYCLESTART_NOTIMPLEMENTED)
	#define USE_RedundancyCycleStart
	#define EXT_RedundancyCycleStart
	#define GET_RedundancyCycleStart(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RedundancyCycleStart()  (RTS_IEC_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_RedundancyCycleStart  FALSE
	#define EXP_RedundancyCycleStart  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RedundancyCycleStart
	#define EXT_RedundancyCycleStart
	#define GET_RedundancyCycleStart(fl)  CAL_CMGETAPI( "RedundancyCycleStart" ) 
	#define CAL_RedundancyCycleStart  RedundancyCycleStart
	#define CHK_RedundancyCycleStart  TRUE
	#define EXP_RedundancyCycleStart  CAL_CMEXPAPI( "RedundancyCycleStart" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCY_EXTERNAL)
	#define USE_RedundancyCycleStart
	#define EXT_RedundancyCycleStart
	#define GET_RedundancyCycleStart(fl)  CAL_CMGETAPI( "RedundancyCycleStart" ) 
	#define CAL_RedundancyCycleStart  RedundancyCycleStart
	#define CHK_RedundancyCycleStart  TRUE
	#define EXP_RedundancyCycleStart  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancyCycleStart", (RTS_UINTPTR)RedundancyCycleStart, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyRedundancyCycleStart
	#define EXT_CmpRedundancyRedundancyCycleStart
	#define GET_CmpRedundancyRedundancyCycleStart  ERR_OK
	#define CAL_CmpRedundancyRedundancyCycleStart pICmpRedundancy->IRedundancyCycleStart
	#define CHK_CmpRedundancyRedundancyCycleStart (pICmpRedundancy != NULL)
	#define EXP_CmpRedundancyRedundancyCycleStart  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RedundancyCycleStart
	#define EXT_RedundancyCycleStart
	#define GET_RedundancyCycleStart(fl)  CAL_CMGETAPI( "RedundancyCycleStart" ) 
	#define CAL_RedundancyCycleStart pICmpRedundancy->IRedundancyCycleStart
	#define CHK_RedundancyCycleStart (pICmpRedundancy != NULL)
	#define EXP_RedundancyCycleStart  CAL_CMEXPAPI( "RedundancyCycleStart" ) 
#else /* DYNAMIC_LINK */
	#define USE_RedundancyCycleStart  PFREDUNDANCYCYCLESTART pfRedundancyCycleStart;
	#define EXT_RedundancyCycleStart  extern PFREDUNDANCYCYCLESTART pfRedundancyCycleStart;
	#define GET_RedundancyCycleStart(fl)  s_pfCMGetAPI2( "RedundancyCycleStart", (RTS_VOID_FCTPTR *)&pfRedundancyCycleStart, (fl), 0, 0)
	#define CAL_RedundancyCycleStart  pfRedundancyCycleStart
	#define CHK_RedundancyCycleStart  (pfRedundancyCycleStart != NULL)
	#define EXP_RedundancyCycleStart  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancyCycleStart", (RTS_UINTPTR)RedundancyCycleStart, 0, 0) 
#endif




/**
 * <description>This function returns the current redundancy state</description>
 * <param name="pState" type="OUT">Pointer to redundancy state structure to return the redundancy state.</param>
 * <result>TRUE in case of success, otherwise FALSE</result>
 */
RTS_IEC_BOOL CDECL RedundancyGetState(RedundancyState *pState);
typedef RTS_IEC_BOOL (CDECL * PFREDUNDANCYGETSTATE) (RedundancyState *pState);
#if defined(CMPREDUNDANCY_NOTIMPLEMENTED) || defined(REDUNDANCYGETSTATE_NOTIMPLEMENTED)
	#define USE_RedundancyGetState
	#define EXT_RedundancyGetState
	#define GET_RedundancyGetState(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RedundancyGetState(p0)  (RTS_IEC_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_RedundancyGetState  FALSE
	#define EXP_RedundancyGetState  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RedundancyGetState
	#define EXT_RedundancyGetState
	#define GET_RedundancyGetState(fl)  CAL_CMGETAPI( "RedundancyGetState" ) 
	#define CAL_RedundancyGetState  RedundancyGetState
	#define CHK_RedundancyGetState  TRUE
	#define EXP_RedundancyGetState  CAL_CMEXPAPI( "RedundancyGetState" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCY_EXTERNAL)
	#define USE_RedundancyGetState
	#define EXT_RedundancyGetState
	#define GET_RedundancyGetState(fl)  CAL_CMGETAPI( "RedundancyGetState" ) 
	#define CAL_RedundancyGetState  RedundancyGetState
	#define CHK_RedundancyGetState  TRUE
	#define EXP_RedundancyGetState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancyGetState", (RTS_UINTPTR)RedundancyGetState, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyRedundancyGetState
	#define EXT_CmpRedundancyRedundancyGetState
	#define GET_CmpRedundancyRedundancyGetState  ERR_OK
	#define CAL_CmpRedundancyRedundancyGetState pICmpRedundancy->IRedundancyGetState
	#define CHK_CmpRedundancyRedundancyGetState (pICmpRedundancy != NULL)
	#define EXP_CmpRedundancyRedundancyGetState  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RedundancyGetState
	#define EXT_RedundancyGetState
	#define GET_RedundancyGetState(fl)  CAL_CMGETAPI( "RedundancyGetState" ) 
	#define CAL_RedundancyGetState pICmpRedundancy->IRedundancyGetState
	#define CHK_RedundancyGetState (pICmpRedundancy != NULL)
	#define EXP_RedundancyGetState  CAL_CMEXPAPI( "RedundancyGetState" ) 
#else /* DYNAMIC_LINK */
	#define USE_RedundancyGetState  PFREDUNDANCYGETSTATE pfRedundancyGetState;
	#define EXT_RedundancyGetState  extern PFREDUNDANCYGETSTATE pfRedundancyGetState;
	#define GET_RedundancyGetState(fl)  s_pfCMGetAPI2( "RedundancyGetState", (RTS_VOID_FCTPTR *)&pfRedundancyGetState, (fl), 0, 0)
	#define CAL_RedundancyGetState  pfRedundancyGetState
	#define CHK_RedundancyGetState  (pfRedundancyGetState != NULL)
	#define EXP_RedundancyGetState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancyGetState", (RTS_UINTPTR)RedundancyGetState, 0, 0) 
#endif




/**
 * <description>This function switches a plc in redundancy state RS_CYCLE_STANDBY to RS_SIMULATION</description>
 * <result>TRUE in case of success, otherwise FALSE</result>
 */
RTS_IEC_BOOL CDECL RedundancySwitchToSimulation(void);
typedef RTS_IEC_BOOL (CDECL * PFREDUNDANCYSWITCHTOSIMULATION) (void);
#if defined(CMPREDUNDANCY_NOTIMPLEMENTED) || defined(REDUNDANCYSWITCHTOSIMULATION_NOTIMPLEMENTED)
	#define USE_RedundancySwitchToSimulation
	#define EXT_RedundancySwitchToSimulation
	#define GET_RedundancySwitchToSimulation(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RedundancySwitchToSimulation()  (RTS_IEC_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_RedundancySwitchToSimulation  FALSE
	#define EXP_RedundancySwitchToSimulation  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RedundancySwitchToSimulation
	#define EXT_RedundancySwitchToSimulation
	#define GET_RedundancySwitchToSimulation(fl)  CAL_CMGETAPI( "RedundancySwitchToSimulation" ) 
	#define CAL_RedundancySwitchToSimulation  RedundancySwitchToSimulation
	#define CHK_RedundancySwitchToSimulation  TRUE
	#define EXP_RedundancySwitchToSimulation  CAL_CMEXPAPI( "RedundancySwitchToSimulation" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCY_EXTERNAL)
	#define USE_RedundancySwitchToSimulation
	#define EXT_RedundancySwitchToSimulation
	#define GET_RedundancySwitchToSimulation(fl)  CAL_CMGETAPI( "RedundancySwitchToSimulation" ) 
	#define CAL_RedundancySwitchToSimulation  RedundancySwitchToSimulation
	#define CHK_RedundancySwitchToSimulation  TRUE
	#define EXP_RedundancySwitchToSimulation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancySwitchToSimulation", (RTS_UINTPTR)RedundancySwitchToSimulation, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyRedundancySwitchToSimulation
	#define EXT_CmpRedundancyRedundancySwitchToSimulation
	#define GET_CmpRedundancyRedundancySwitchToSimulation  ERR_OK
	#define CAL_CmpRedundancyRedundancySwitchToSimulation pICmpRedundancy->IRedundancySwitchToSimulation
	#define CHK_CmpRedundancyRedundancySwitchToSimulation (pICmpRedundancy != NULL)
	#define EXP_CmpRedundancyRedundancySwitchToSimulation  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RedundancySwitchToSimulation
	#define EXT_RedundancySwitchToSimulation
	#define GET_RedundancySwitchToSimulation(fl)  CAL_CMGETAPI( "RedundancySwitchToSimulation" ) 
	#define CAL_RedundancySwitchToSimulation pICmpRedundancy->IRedundancySwitchToSimulation
	#define CHK_RedundancySwitchToSimulation (pICmpRedundancy != NULL)
	#define EXP_RedundancySwitchToSimulation  CAL_CMEXPAPI( "RedundancySwitchToSimulation" ) 
#else /* DYNAMIC_LINK */
	#define USE_RedundancySwitchToSimulation  PFREDUNDANCYSWITCHTOSIMULATION pfRedundancySwitchToSimulation;
	#define EXT_RedundancySwitchToSimulation  extern PFREDUNDANCYSWITCHTOSIMULATION pfRedundancySwitchToSimulation;
	#define GET_RedundancySwitchToSimulation(fl)  s_pfCMGetAPI2( "RedundancySwitchToSimulation", (RTS_VOID_FCTPTR *)&pfRedundancySwitchToSimulation, (fl), 0, 0)
	#define CAL_RedundancySwitchToSimulation  pfRedundancySwitchToSimulation
	#define CHK_RedundancySwitchToSimulation  (pfRedundancySwitchToSimulation != NULL)
	#define EXP_RedundancySwitchToSimulation  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancySwitchToSimulation", (RTS_UINTPTR)RedundancySwitchToSimulation, 0, 0) 
#endif




/**
 * <description>This function switches a plc in redundancy state RS_SIMULATION_START to RS_CYLCE_STANDALONE</description>
 * <result>TRUE in case of success, otherwise FALSE</result>
 */
RTS_IEC_BOOL CDECL RedundancySwitchToStandalone(void);
typedef RTS_IEC_BOOL (CDECL * PFREDUNDANCYSWITCHTOSTANDALONE) (void);
#if defined(CMPREDUNDANCY_NOTIMPLEMENTED) || defined(REDUNDANCYSWITCHTOSTANDALONE_NOTIMPLEMENTED)
	#define USE_RedundancySwitchToStandalone
	#define EXT_RedundancySwitchToStandalone
	#define GET_RedundancySwitchToStandalone(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RedundancySwitchToStandalone()  (RTS_IEC_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_RedundancySwitchToStandalone  FALSE
	#define EXP_RedundancySwitchToStandalone  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RedundancySwitchToStandalone
	#define EXT_RedundancySwitchToStandalone
	#define GET_RedundancySwitchToStandalone(fl)  CAL_CMGETAPI( "RedundancySwitchToStandalone" ) 
	#define CAL_RedundancySwitchToStandalone  RedundancySwitchToStandalone
	#define CHK_RedundancySwitchToStandalone  TRUE
	#define EXP_RedundancySwitchToStandalone  CAL_CMEXPAPI( "RedundancySwitchToStandalone" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCY_EXTERNAL)
	#define USE_RedundancySwitchToStandalone
	#define EXT_RedundancySwitchToStandalone
	#define GET_RedundancySwitchToStandalone(fl)  CAL_CMGETAPI( "RedundancySwitchToStandalone" ) 
	#define CAL_RedundancySwitchToStandalone  RedundancySwitchToStandalone
	#define CHK_RedundancySwitchToStandalone  TRUE
	#define EXP_RedundancySwitchToStandalone  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancySwitchToStandalone", (RTS_UINTPTR)RedundancySwitchToStandalone, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyRedundancySwitchToStandalone
	#define EXT_CmpRedundancyRedundancySwitchToStandalone
	#define GET_CmpRedundancyRedundancySwitchToStandalone  ERR_OK
	#define CAL_CmpRedundancyRedundancySwitchToStandalone pICmpRedundancy->IRedundancySwitchToStandalone
	#define CHK_CmpRedundancyRedundancySwitchToStandalone (pICmpRedundancy != NULL)
	#define EXP_CmpRedundancyRedundancySwitchToStandalone  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RedundancySwitchToStandalone
	#define EXT_RedundancySwitchToStandalone
	#define GET_RedundancySwitchToStandalone(fl)  CAL_CMGETAPI( "RedundancySwitchToStandalone" ) 
	#define CAL_RedundancySwitchToStandalone pICmpRedundancy->IRedundancySwitchToStandalone
	#define CHK_RedundancySwitchToStandalone (pICmpRedundancy != NULL)
	#define EXP_RedundancySwitchToStandalone  CAL_CMEXPAPI( "RedundancySwitchToStandalone" ) 
#else /* DYNAMIC_LINK */
	#define USE_RedundancySwitchToStandalone  PFREDUNDANCYSWITCHTOSTANDALONE pfRedundancySwitchToStandalone;
	#define EXT_RedundancySwitchToStandalone  extern PFREDUNDANCYSWITCHTOSTANDALONE pfRedundancySwitchToStandalone;
	#define GET_RedundancySwitchToStandalone(fl)  s_pfCMGetAPI2( "RedundancySwitchToStandalone", (RTS_VOID_FCTPTR *)&pfRedundancySwitchToStandalone, (fl), 0, 0)
	#define CAL_RedundancySwitchToStandalone  pfRedundancySwitchToStandalone
	#define CHK_RedundancySwitchToStandalone  (pfRedundancySwitchToStandalone != NULL)
	#define EXP_RedundancySwitchToStandalone  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancySwitchToStandalone", (RTS_UINTPTR)RedundancySwitchToStandalone, 0, 0) 
#endif




/**
 * <description>This function switches a plc in redundancy state RS_CYCLE_ACTIVE to RS_CYCLE_STANDBY</description>
 * <result>TRUE in case of success, otherwise FALSE</result>
 */
RTS_IEC_BOOL CDECL RedundancySwitchToStandby(void);
typedef RTS_IEC_BOOL (CDECL * PFREDUNDANCYSWITCHTOSTANDBY) (void);
#if defined(CMPREDUNDANCY_NOTIMPLEMENTED) || defined(REDUNDANCYSWITCHTOSTANDBY_NOTIMPLEMENTED)
	#define USE_RedundancySwitchToStandby
	#define EXT_RedundancySwitchToStandby
	#define GET_RedundancySwitchToStandby(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RedundancySwitchToStandby()  (RTS_IEC_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_RedundancySwitchToStandby  FALSE
	#define EXP_RedundancySwitchToStandby  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RedundancySwitchToStandby
	#define EXT_RedundancySwitchToStandby
	#define GET_RedundancySwitchToStandby(fl)  CAL_CMGETAPI( "RedundancySwitchToStandby" ) 
	#define CAL_RedundancySwitchToStandby  RedundancySwitchToStandby
	#define CHK_RedundancySwitchToStandby  TRUE
	#define EXP_RedundancySwitchToStandby  CAL_CMEXPAPI( "RedundancySwitchToStandby" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCY_EXTERNAL)
	#define USE_RedundancySwitchToStandby
	#define EXT_RedundancySwitchToStandby
	#define GET_RedundancySwitchToStandby(fl)  CAL_CMGETAPI( "RedundancySwitchToStandby" ) 
	#define CAL_RedundancySwitchToStandby  RedundancySwitchToStandby
	#define CHK_RedundancySwitchToStandby  TRUE
	#define EXP_RedundancySwitchToStandby  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancySwitchToStandby", (RTS_UINTPTR)RedundancySwitchToStandby, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyRedundancySwitchToStandby
	#define EXT_CmpRedundancyRedundancySwitchToStandby
	#define GET_CmpRedundancyRedundancySwitchToStandby  ERR_OK
	#define CAL_CmpRedundancyRedundancySwitchToStandby pICmpRedundancy->IRedundancySwitchToStandby
	#define CHK_CmpRedundancyRedundancySwitchToStandby (pICmpRedundancy != NULL)
	#define EXP_CmpRedundancyRedundancySwitchToStandby  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RedundancySwitchToStandby
	#define EXT_RedundancySwitchToStandby
	#define GET_RedundancySwitchToStandby(fl)  CAL_CMGETAPI( "RedundancySwitchToStandby" ) 
	#define CAL_RedundancySwitchToStandby pICmpRedundancy->IRedundancySwitchToStandby
	#define CHK_RedundancySwitchToStandby (pICmpRedundancy != NULL)
	#define EXP_RedundancySwitchToStandby  CAL_CMEXPAPI( "RedundancySwitchToStandby" ) 
#else /* DYNAMIC_LINK */
	#define USE_RedundancySwitchToStandby  PFREDUNDANCYSWITCHTOSTANDBY pfRedundancySwitchToStandby;
	#define EXT_RedundancySwitchToStandby  extern PFREDUNDANCYSWITCHTOSTANDBY pfRedundancySwitchToStandby;
	#define GET_RedundancySwitchToStandby(fl)  s_pfCMGetAPI2( "RedundancySwitchToStandby", (RTS_VOID_FCTPTR *)&pfRedundancySwitchToStandby, (fl), 0, 0)
	#define CAL_RedundancySwitchToStandby  pfRedundancySwitchToStandby
	#define CHK_RedundancySwitchToStandby  (pfRedundancySwitchToStandby != NULL)
	#define EXP_RedundancySwitchToStandby  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancySwitchToStandby", (RTS_UINTPTR)RedundancySwitchToStandby, 0, 0) 
#endif




/**
 * <description>This function switches a plc in redundancy state RS_SIMULATION to RS_CYCLE_ACTIVE (if the second redundancy plc is running) or RS_CYCLE_STANDALONE (if the second redundancy plc is not running)</description>
 * <result>TRUE in case of success, otherwise FALSE</result>
 */
RTS_IEC_BOOL CDECL RedundancySwitchToActive(void);
typedef RTS_IEC_BOOL (CDECL * PFREDUNDANCYSWITCHTOACTIVE) (void);
#if defined(CMPREDUNDANCY_NOTIMPLEMENTED) || defined(REDUNDANCYSWITCHTOACTIVE_NOTIMPLEMENTED)
	#define USE_RedundancySwitchToActive
	#define EXT_RedundancySwitchToActive
	#define GET_RedundancySwitchToActive(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RedundancySwitchToActive()  (RTS_IEC_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_RedundancySwitchToActive  FALSE
	#define EXP_RedundancySwitchToActive  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RedundancySwitchToActive
	#define EXT_RedundancySwitchToActive
	#define GET_RedundancySwitchToActive(fl)  CAL_CMGETAPI( "RedundancySwitchToActive" ) 
	#define CAL_RedundancySwitchToActive  RedundancySwitchToActive
	#define CHK_RedundancySwitchToActive  TRUE
	#define EXP_RedundancySwitchToActive  CAL_CMEXPAPI( "RedundancySwitchToActive" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCY_EXTERNAL)
	#define USE_RedundancySwitchToActive
	#define EXT_RedundancySwitchToActive
	#define GET_RedundancySwitchToActive(fl)  CAL_CMGETAPI( "RedundancySwitchToActive" ) 
	#define CAL_RedundancySwitchToActive  RedundancySwitchToActive
	#define CHK_RedundancySwitchToActive  TRUE
	#define EXP_RedundancySwitchToActive  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancySwitchToActive", (RTS_UINTPTR)RedundancySwitchToActive, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyRedundancySwitchToActive
	#define EXT_CmpRedundancyRedundancySwitchToActive
	#define GET_CmpRedundancyRedundancySwitchToActive  ERR_OK
	#define CAL_CmpRedundancyRedundancySwitchToActive pICmpRedundancy->IRedundancySwitchToActive
	#define CHK_CmpRedundancyRedundancySwitchToActive (pICmpRedundancy != NULL)
	#define EXP_CmpRedundancyRedundancySwitchToActive  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RedundancySwitchToActive
	#define EXT_RedundancySwitchToActive
	#define GET_RedundancySwitchToActive(fl)  CAL_CMGETAPI( "RedundancySwitchToActive" ) 
	#define CAL_RedundancySwitchToActive pICmpRedundancy->IRedundancySwitchToActive
	#define CHK_RedundancySwitchToActive (pICmpRedundancy != NULL)
	#define EXP_RedundancySwitchToActive  CAL_CMEXPAPI( "RedundancySwitchToActive" ) 
#else /* DYNAMIC_LINK */
	#define USE_RedundancySwitchToActive  PFREDUNDANCYSWITCHTOACTIVE pfRedundancySwitchToActive;
	#define EXT_RedundancySwitchToActive  extern PFREDUNDANCYSWITCHTOACTIVE pfRedundancySwitchToActive;
	#define GET_RedundancySwitchToActive(fl)  s_pfCMGetAPI2( "RedundancySwitchToActive", (RTS_VOID_FCTPTR *)&pfRedundancySwitchToActive, (fl), 0, 0)
	#define CAL_RedundancySwitchToActive  pfRedundancySwitchToActive
	#define CHK_RedundancySwitchToActive  (pfRedundancySwitchToActive != NULL)
	#define EXP_RedundancySwitchToActive  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancySwitchToActive", (RTS_UINTPTR)RedundancySwitchToActive, 0, 0) 
#endif




/**
 * <description>This function synchronizes a plc in redundancy state RS_START, RS_BOOTUP_ERROR, RS_SYNCHRO_ERROR, RS_CYCLE_ERROR, RS_CYCLE_STANDALONE, RS_SIMULATION or RS_SIMULATION_START</description>
 * <result>TRUE in case of success, otherwise FALSE</result>
 */
RTS_IEC_BOOL CDECL RedundancySynchronize(void);
typedef RTS_IEC_BOOL (CDECL * PFREDUNDANCYSYNCHRONIZE) (void);
#if defined(CMPREDUNDANCY_NOTIMPLEMENTED) || defined(REDUNDANCYSYNCHRONIZE_NOTIMPLEMENTED)
	#define USE_RedundancySynchronize
	#define EXT_RedundancySynchronize
	#define GET_RedundancySynchronize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RedundancySynchronize()  (RTS_IEC_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_RedundancySynchronize  FALSE
	#define EXP_RedundancySynchronize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RedundancySynchronize
	#define EXT_RedundancySynchronize
	#define GET_RedundancySynchronize(fl)  CAL_CMGETAPI( "RedundancySynchronize" ) 
	#define CAL_RedundancySynchronize  RedundancySynchronize
	#define CHK_RedundancySynchronize  TRUE
	#define EXP_RedundancySynchronize  CAL_CMEXPAPI( "RedundancySynchronize" ) 
#elif defined(MIXED_LINK) && !defined(CMPREDUNDANCY_EXTERNAL)
	#define USE_RedundancySynchronize
	#define EXT_RedundancySynchronize
	#define GET_RedundancySynchronize(fl)  CAL_CMGETAPI( "RedundancySynchronize" ) 
	#define CAL_RedundancySynchronize  RedundancySynchronize
	#define CHK_RedundancySynchronize  TRUE
	#define EXP_RedundancySynchronize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancySynchronize", (RTS_UINTPTR)RedundancySynchronize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRedundancyRedundancySynchronize
	#define EXT_CmpRedundancyRedundancySynchronize
	#define GET_CmpRedundancyRedundancySynchronize  ERR_OK
	#define CAL_CmpRedundancyRedundancySynchronize pICmpRedundancy->IRedundancySynchronize
	#define CHK_CmpRedundancyRedundancySynchronize (pICmpRedundancy != NULL)
	#define EXP_CmpRedundancyRedundancySynchronize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RedundancySynchronize
	#define EXT_RedundancySynchronize
	#define GET_RedundancySynchronize(fl)  CAL_CMGETAPI( "RedundancySynchronize" ) 
	#define CAL_RedundancySynchronize pICmpRedundancy->IRedundancySynchronize
	#define CHK_RedundancySynchronize (pICmpRedundancy != NULL)
	#define EXP_RedundancySynchronize  CAL_CMEXPAPI( "RedundancySynchronize" ) 
#else /* DYNAMIC_LINK */
	#define USE_RedundancySynchronize  PFREDUNDANCYSYNCHRONIZE pfRedundancySynchronize;
	#define EXT_RedundancySynchronize  extern PFREDUNDANCYSYNCHRONIZE pfRedundancySynchronize;
	#define GET_RedundancySynchronize(fl)  s_pfCMGetAPI2( "RedundancySynchronize", (RTS_VOID_FCTPTR *)&pfRedundancySynchronize, (fl), 0, 0)
	#define CAL_RedundancySynchronize  pfRedundancySynchronize
	#define CHK_RedundancySynchronize  (pfRedundancySynchronize != NULL)
	#define EXP_RedundancySynchronize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RedundancySynchronize", (RTS_UINTPTR)RedundancySynchronize, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif




typedef struct
{
	IBase_C *pBase;
	PFREDUNDANCYAREAREGISTER IRedundancyAreaRegister;
 	PFREDUNDANCYAREAREGISTERSEGMENT IRedundancyAreaRegisterSegment;
 	PFREDUNDANCYUNREGISTERAREAS IRedundancyUnregisterAreas;
 	PFREDUNDANCYCYCLEEND IRedundancyCycleEnd;
 	PFREDUNDANCYCYCLESTART IRedundancyCycleStart;
 	PFREDUNDANCYGETSTATE IRedundancyGetState;
 	PFREDUNDANCYSWITCHTOSIMULATION IRedundancySwitchToSimulation;
 	PFREDUNDANCYSWITCHTOSTANDALONE IRedundancySwitchToStandalone;
 	PFREDUNDANCYSWITCHTOSTANDBY IRedundancySwitchToStandby;
 	PFREDUNDANCYSWITCHTOACTIVE IRedundancySwitchToActive;
 	PFREDUNDANCYSYNCHRONIZE IRedundancySynchronize;
 } ICmpRedundancy_C;

#ifdef CPLUSPLUS
class ICmpRedundancy : public IBase
{
	public:
		virtual RTS_IEC_BOOL CDECL IRedundancyAreaRegister(unsigned char *pbyArea, RTS_UI32 ulSize, RDCY_AREA_TYPE eType) =0;
		virtual RTS_IEC_BOOL CDECL IRedundancyAreaRegisterSegment(RTS_UI16 usSegment, RDCY_AREA_TYPE eType) =0;
		virtual RTS_IEC_BOOL CDECL IRedundancyUnregisterAreas(void) =0;
		virtual RTS_IEC_BOOL CDECL IRedundancyCycleEnd(void) =0;
		virtual RTS_IEC_BOOL CDECL IRedundancyCycleStart(void) =0;
		virtual RTS_IEC_BOOL CDECL IRedundancyGetState(RedundancyState *pState) =0;
		virtual RTS_IEC_BOOL CDECL IRedundancySwitchToSimulation(void) =0;
		virtual RTS_IEC_BOOL CDECL IRedundancySwitchToStandalone(void) =0;
		virtual RTS_IEC_BOOL CDECL IRedundancySwitchToStandby(void) =0;
		virtual RTS_IEC_BOOL CDECL IRedundancySwitchToActive(void) =0;
		virtual RTS_IEC_BOOL CDECL IRedundancySynchronize(void) =0;
};
	#ifndef ITF_CmpRedundancy
		#define ITF_CmpRedundancy static ICmpRedundancy *pICmpRedundancy = NULL;
	#endif
	#define EXTITF_CmpRedundancy
#else	/*CPLUSPLUS*/
	typedef ICmpRedundancy_C		ICmpRedundancy;
	#ifndef ITF_CmpRedundancy
		#define ITF_CmpRedundancy
	#endif
	#define EXTITF_CmpRedundancy
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPREDUNDANCYITF_H_*/
