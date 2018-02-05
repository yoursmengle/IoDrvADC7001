/**
 * <interfacename>Redundancy</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`CmpRedundancy')

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

DEF_API(`void',`CDECL',`arearegister',`(arearegister_struct *p)',1,0x0,0x0)

/**
 * <description>arearegistersegment</description>
 */
typedef struct tagarearegistersegment_struct
{
	RTS_IEC_UINT usSegment;					/* VAR_INPUT */
	RDCY_AREA_TYPE eType;				/* VAR_INPUT */
	RTS_IEC_BOOL AreaRegisterSegment;	/* VAR_OUTPUT */
} arearegistersegment_struct;

DEF_API(`void',`CDECL',`arearegistersegment',`(arearegistersegment_struct *p)',1,0x0,0x0)

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

DEF_API(`void',`CDECL',`unregisterareas',`(unregisterareas_struct *p)',1,0x0,0x0)

DEF_API(`void',`CDECL',`redundancycycleend',`(redundancycycleend_struct *p)',1,0x0,0x0)

/**
 * <description>redundancycyclestart</description>
 */
typedef struct tagredundancycyclestart_struct
{
	RTS_IEC_BOOL RedundancyCycleStart;	/* VAR_OUTPUT */
} redundancycyclestart_struct;

DEF_API(`void',`CDECL',`redundancycyclestart',`(redundancycyclestart_struct *p)',1,0x0,0x0)

/**
 * <description>getredundancystate</description>
 */
typedef struct taggetredundancystate_struct
{
	RedundancyState *pState;			/* VAR_INPUT */
	RTS_IEC_BOOL GetRedundancyState;	/* VAR_OUTPUT */
} getredundancystate_struct;

DEF_API(`void',`CDECL',`getredundancystate',`(getredundancystate_struct *p)',1,0x0,0x0)

/**
 * <description>switchtosimulation</description>
 */
typedef struct tagswitchtosimulation_struct
{
	RTS_IEC_BOOL SwitchToSimulation;	/* VAR_OUTPUT */
} switchtosimulation_struct;

DEF_API(`void',`CDECL',`switchtosimulation',`(switchtosimulation_struct *p)',1,0x0,0x0)

/**
 * <description>switchtostandalone</description>
 */
typedef struct tagswitchtostandalone_struct
{
	RTS_IEC_BOOL SwitchToStandalone;	/* VAR_OUTPUT */	
} switchtostandalone_struct;

DEF_API(`void',`CDECL',`switchtostandalone',`(switchtostandalone_struct *p)',1,0x0,0x0)

/**
 * <description>switchtostandby</description>
 */
typedef struct tagswitchtostandby_struct
{
	RTS_IEC_BOOL SwitchToStandby;		/* VAR_OUTPUT */
} switchtostandby_struct;

DEF_API(`void',`CDECL',`switchtostandby',`(switchtostandby_struct *p)',1,0x0,0x0)

/**
 * <description>switchtoactive</description>
 */
typedef struct tagswitchtoactive_struct
{
	RTS_IEC_BOOL SwitchToActive;		/* VAR_OUTPUT */
} switchtoactive_struct;

DEF_API(`void',`CDECL',`switchtoactive',`(switchtoactive_struct *p)',1,0x0,0x0)

/**
 * <description>synchronize</description>
 */
typedef struct tagsynchronize_struct
{
	RTS_IEC_BOOL Synchronize;			/* VAR_OUTPUT */
} synchronize_struct;

DEF_API(`void',`CDECL',`synchronize',`(synchronize_struct *p)',1,0x0,0x0)

/**
 * <description>This function registers the memory area as redundant area</description>
 * <param name="pbyArea" type="IN">Start address</param>
 * <param name="ulSize" type="IN">Size</param>
 * <param name="eType" type="IN">Redundancy area type</param>
 * <result>TRUE in case of success, otherwise FALSE</result>
 */
DEF_ITF_API(`RTS_IEC_BOOL',`CDECL',`RedundancyAreaRegister',`(unsigned char *pbyArea, RTS_UI32 ulSize, RDCY_AREA_TYPE eType)')

/**
 * <description>This function registers a memory area segment as redundant area</description>
 * <param name="usSegment" type="IN">Segment type</param>
 * <param name="eType" type="IN">Redundancy area type</param>
 * <result>TRUE in case of success, otherwise FALSE</result>
 */
DEF_ITF_API(`RTS_IEC_BOOL',`CDECL',`RedundancyAreaRegisterSegment',`(RTS_UI16 usSegment, RDCY_AREA_TYPE eType)')

/**
 * <description>This function unregisters all redundancy areas</description>
 * <result>TRUE in case of success, otherwise FALSE</result>
 */
DEF_ITF_API(`RTS_IEC_BOOL',`CDECL',`RedundancyUnregisterAreas',`(void)')

/**
 * <description>This function is called at end of a cycle of the redundancy task</description>
 * <result>TRUE in case of success, otherwise FALSE</result>
 */
DEF_ITF_API(`RTS_IEC_BOOL',`CDECL',`RedundancyCycleEnd',`(void)')

/**
 * <description>This function is called at beginning of a cycle of the redundancy task</description>
 * <result>TRUE in case of success, otherwise FALSE</result>
 */
DEF_ITF_API(`RTS_IEC_BOOL',`CDECL',`RedundancyCycleStart',`(void)')

/**
 * <description>This function returns the current redundancy state</description>
 * <param name="pState" type="OUT">Pointer to redundancy state structure to return the redundancy state.</param>
 * <result>TRUE in case of success, otherwise FALSE</result>
 */
DEF_ITF_API(`RTS_IEC_BOOL',`CDECL',`RedundancyGetState',`(RedundancyState *pState)')

/**
 * <description>This function switches a plc in redundancy state RS_CYCLE_STANDBY to RS_SIMULATION</description>
 * <result>TRUE in case of success, otherwise FALSE</result>
 */
DEF_ITF_API(`RTS_IEC_BOOL',`CDECL',`RedundancySwitchToSimulation',`(void)')

/**
 * <description>This function switches a plc in redundancy state RS_SIMULATION_START to RS_CYLCE_STANDALONE</description>
 * <result>TRUE in case of success, otherwise FALSE</result>
 */
DEF_ITF_API(`RTS_IEC_BOOL',`CDECL',`RedundancySwitchToStandalone',`(void)')

/**
 * <description>This function switches a plc in redundancy state RS_CYCLE_ACTIVE to RS_CYCLE_STANDBY</description>
 * <result>TRUE in case of success, otherwise FALSE</result>
 */
DEF_ITF_API(`RTS_IEC_BOOL',`CDECL',`RedundancySwitchToStandby',`(void)')

/**
 * <description>This function switches a plc in redundancy state RS_SIMULATION to RS_CYCLE_ACTIVE (if the second redundancy plc is running) or RS_CYCLE_STANDALONE (if the second redundancy plc is not running)</description>
 * <result>TRUE in case of success, otherwise FALSE</result>
 */
DEF_ITF_API(`RTS_IEC_BOOL',`CDECL',`RedundancySwitchToActive',`(void)')

/**
 * <description>This function synchronizes a plc in redundancy state RS_START, RS_BOOTUP_ERROR, RS_SYNCHRO_ERROR, RS_CYCLE_ERROR, RS_CYCLE_STANDALONE, RS_SIMULATION or RS_SIMULATION_START</description>
 * <result>TRUE in case of success, otherwise FALSE</result>
 */
DEF_ITF_API(`RTS_IEC_BOOL',`CDECL',`RedundancySynchronize',`(void)')

#ifdef __cplusplus
}
#endif

