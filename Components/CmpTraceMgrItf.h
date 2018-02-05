 /**
 * <interfacename>CmpTraceMgr</interfacename>
 * <description> 
 *	<p>This is the interface of the trace manager. The trace manager handles trace packets, that are defined from:
 *	<ul>
 *		<li>Trace editor in CoDeSys</li>
 *		<li>A runtime system component</li>
 *		<li>An IEC program</li>
 *	</ul>
 *	</p>
 *	<p>
 *	A trace packet is the container for trace variables, which are named as records.
 *	A trace packet is is always identified by its name. This must be unique!
 *	A trace record contains the trace of a single variable. So the record contains the trace buffer in which the trace values are stored.
 *	</p>
 *	<p>
 *	This is the sequence of typical handling of the trace manager:
 *	1. Packet create	(->event is sent)
 *	2. Add records		(->event is sent)
 *	3. Complete packet	(->event is sent)
 *	4. Start trace		(->event is sent)
 *	5. Optional: Set trigger state: Extern/Intern (->event is sent)
 *  6. Standard variables are recorded automatically. For system variables, the corresponding component or IEC program is responsible for
 *		recording!
 *	7. Stop: Extern/Intern (->event is sent)
 *	8. Restart / start / delete packet
 *	...
 *	</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPTRACEMGRITF_H_
#define _CMPTRACEMGRITF_H_

#include "CmpStd.h"

 

 




#include "SysInternalLibItf.h"
#include "SysTimeItf.h"
#include "CmpMemPoolItf.h"
#include "CmpIecVarAccessItf.h"
#include "CmpAppItf.h"

/**
 * <category>Compiler switch</category>
 * <description>
 *	Compiler switches to enable/disable single features in the component.
 * </description>
 * <element name="TRACEMGR_DISABLE_PERSISTENT_STORAGE">Switch to disable persistent storing of trace configuration in file</element>
 * <element name="TRACEMGR_DISABLE_SYMBOLIC_VARACCESS">Switch to disable support for symbolic access of variables (see address flag TRACE_VAR_ADDRESS_FLAGS_SYMBOLIC))</element>
 */
 /* for backward compatibility */
 #ifdef TACEMGR_DISABLE_PERSISTENT_STORAGE
	#define TRACEMGR_DISABLE_PERSISTENT_STORAGE
#endif
 #ifdef TACEMGR_DISABLE_SYMBOLIC_VARACCESS
	#define TRACEMGR_DISABLE_SYMBOLIC_VARACCESS
#endif

/**
 * <category>Static defines</category>
 * <description>Maximum length of a trace packet or trace variable name</description>
 */
#ifndef TRACE_MAX_NAME_LEN
	#define TRACE_MAX_NAME_LEN					32
#endif

/**
 * <category>Static defines</category>
 * <description>Number of static packets</description>
 */
#ifndef TRACE_NUM_OF_STATIC_PACKETS
	#define TRACE_NUM_OF_STATIC_PACKETS			1
#endif

/**
 * <category>Static defines</category>
 * <description>Number of static records</description>
 */
#ifndef TRACE_NUM_OF_STATIC_RECORDS
	#define TRACE_NUM_OF_STATIC_RECORDS			8
#endif


#define EVTPARAMID_CmpTraceMgr_Packet	0x0001
#define EVTVERSION_CmpTraceMgr_Packet	0x0001

#define EVTPARAMID_CmpTraceMgr_Record	0x0002
#define EVTVERSION_CmpTraceMgr_Record	0x0001

/**
 * <category>Events</category>
 * <description>Event is sent after a new trace packet is created</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpTraceMgr_Packet</param>
 */
#define EVT_TRACEMGR_PACKET_CREATE				MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Events</category>
 * <description>Event is sent before a trace packet is deleted</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpTraceMgr_Packet</param>
 */
#define EVT_TRACEMGR_PACKET_DELETE				MAKE_EVENTID(EVTCLASS_INFO, 2)

/**
 * <category>Events</category>
 * <description>Event is sent after a new record was added to a trace packet</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpTraceMgr_Record</param>
 */
#define EVT_TRACEMGR_ADD_RECORD					MAKE_EVENTID(EVTCLASS_INFO, 3)

/**
 * <category>Events</category>
 * <description>Event is sent before a record is removed from a trace packet</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpTraceMgr_Record</param>
 */
#define EVT_TRACEMGR_REMOVE_RECORD				MAKE_EVENTID(EVTCLASS_INFO, 4)

/**
 * <category>Events</category>
 * <description>Event is sent after a trace packet was completed</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpTraceMgr_Packet</param>
 */
#define EVT_TRACEMGR_PACKET_COMPLETE			MAKE_EVENTID(EVTCLASS_INFO, 5)

/**
 * <category>Events</category>
 * <description>Event is sent after the state of a trace packet has changed</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpTraceMgr_Packet</param>
 */
#define EVT_TRACEMGR_PACKET_STATE_CHANGED		MAKE_EVENTID(EVTCLASS_INFO, 6)

/**
 * <category>Events</category>
 * <description>Event is sent to update the the values in the specified trace record. This is event is cyclically sent out of the trace task!</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpTraceMgr_Record</param>
 */
#define EVT_TRACEMGR_UPDATE_RECORD				MAKE_EVENTID(EVTCLASS_INFO, 7)

/**
 * <category>Events</category>
 * <description>Event is sent if the trigger condition of the specified trace packet was reached</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpTraceMgr_Packet</param>
 */
#define EVT_TRACEMGR_PACKET_TRIGGER				MAKE_EVENTID(EVTCLASS_INFO, 8)

/**
 * <category>Events</category>
 * <description>Event is sent, if the trace was read by the trace editor to inform all trace handlers to provide all data</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpTraceMgr_Packet</param>
 */
#define EVT_TRACEMGR_PACKET_SAMPLE				MAKE_EVENTID(EVTCLASS_INFO, 9)


/**
 * <category>Online services</category>
 * <element name="SRV_TRACE_PACKET_READ_LIST" type="IN">Read list of all trace packets</element>
 * <element name="SRV_TRACE_PACKET_CREATE" type="IN">Create a trace packet</element>
 * <element name="SRV_TRACE_PACKET_DELETE" type="IN">Delete a trace packet</element>
 * <element name="SRV_TRACE_PACKET_COMPLETE" type="IN">Complete a trace packet</element>
 * <element name="SRV_TRACE_PACKET_OPEN" type="IN">Open an existing trace packet</element>
 * <element name="SRV_TRACE_PACKET_CLOSE" type="IN">Close an existing trace packet</element>
 * <element name="SRV_TRACE_PACKET_READ" type="IN">Read a trace packet</element>
 * <element name="SRV_TRACE_PACKET_GET_STATE" type="IN">Get the state of a trace packet</element>
 * <element name="SRV_TRACE_PACKET_GET_CONFIG" type="IN">Get the configuration of a trace packet</element>
 * <element name="SRV_TRACE_PACKET_START" type="IN">Start a trace packet</element>
 * <element name="SRV_TRACE_PACKET_STOP" type="IN">Stop a trace packet</element>
 * <element name="SRV_TRACE_PACKET_RESTART" type="IN">Restart a trace packet</element>
 * <element name="SRV_TRACE_RECORD_ADD" type="IN">Add a record to a specified trace packet</element>
 * <element name="SRV_TRACE_RECORD_REMOVE" type="IN">Remove a record to a specified trace packet</element>
 * <element name="SRV_TRACE_RECORD_GET_CONFIG" type="IN">Get the configuration of a trace record</element>
 * <element name="SRV_TRACE_PACKET_RESET_TRIGGER" type="IN">Reset the trigger of a trace packet</element>
 * <element name="SRV_TRACE_PACKET_STORE" type="IN">Saves a trace packet to a file</element>
 * <element name="SRV_TRACE_PACKET_RESTORE" type="IN">Loads a trace packet from a file</element>
 * <element name="SRV_TRACE_GET_CONFIG_FROM_FILE" type="IN">Read a trace packet configuration from a file</element>
 */
#define SRV_TRACE_PACKET_READ_LIST				0x01
#define SRV_TRACE_PACKET_CREATE					0x02
#define SRV_TRACE_PACKET_DELETE					0x03
#define SRV_TRACE_PACKET_COMPLETE				0x04
#define SRV_TRACE_PACKET_OPEN					0x05
#define SRV_TRACE_PACKET_CLOSE					0x06
#define SRV_TRACE_PACKET_READ					0x07
#define SRV_TRACE_PACKET_GET_STATE				0x08
#define SRV_TRACE_PACKET_GET_CONFIG				0x09
#define SRV_TRACE_PACKET_START					0x0A
#define SRV_TRACE_PACKET_STOP					0x0B
#define SRV_TRACE_PACKET_RESTART				0x0C
#define SRV_TRACE_RECORD_ADD					0x0D
#define SRV_TRACE_RECORD_REMOVE					0x0E
#define SRV_TRACE_RECORD_GET_CONFIG				0x0F
#define SRV_TRACE_PACKET_RESET_TRIGGER			0x10
#define SRV_TRACE_PACKET_STORE					0x11
#define SRV_TRACE_PACKET_RESTORE				0x12
#define SRV_TRACE_GET_CONFIG_FROM_FILE			0x13

/**
 * <category>Online service tags</category>
 */
#define TAGNEST_TRACE_REPLY_PACKET				0x81
#define TAG_TRACE_REPLY_NAME					0x01

#define TAG_TRACE_PACKET_NAME					0x10
#define TAG_TRACE_PACKET_APPLICATION_NAME		0x11
#define TAG_TRACE_PACKET_IECTASK_NAME			0x12
#define TAG_TRACE_PACKET_EVERYNCYCLES			0x13
#define TAG_TRACE_PACKET_BUFFERENTRIES			0x14
#define TAG_TRACE_PACKET_FLAGS					0x15
#define TAG_TRACE_PACKET_COMMENT				0x16
/* TAGNEST_TRACE_TRIGGER */
/* TAGNEST_TRACE_CONDITION */

#define TAGNEST_TRACE_VARIABLE						0x83
#define TAGNEST_TRACE_RECORD_CONFIGURATION			0x84
#define TAGNEST_TRACE_CONDITION						0x85
#define TAG_TRACE_VARIABLE_NAME						0x20
#define TAG_TRACE_VARIABLE_ADDRESS_FLAGS			0x21
#define TAG_TRACE_VARIABLE_ADDRESS_POINTER			0x22
#define TAG_TRACE_VARIABLE_ADDRESS_AREA				0x23
#define TAG_TRACE_VARIABLE_ADDRESS_OFFSET			0x24
#define TAG_TRACE_VARIABLE_TYPECLASS				0x25
#define TAG_TRACE_VARIABLE_SIZE						0x26
#define TAG_TRACE_VARIABLE_GRAPHTYPE				0x27
#define TAG_TRACE_VARIABLE_GRAPHCOLOR				0x28
#define TAG_TRACE_PARAMETER_ID						0x29
#define TAG_TRACE_PARAMETER_MODULE_TYPE				0x30
#define TAG_TRACE_PARAMETER_INSTANCE				0x31
#define TAG_TRACE_VARIABLE_ACTIVATE_MIN_WARNING		0x32
#define TAG_TRACE_VARIABLE_CRITICAL_LOWER_LIMIT		0x33
#define TAG_TRACE_VARIABLE_MIN_WARNING_COLOR		0x34
#define TAG_TRACE_VARIABLE_ACTIVATE_MAX_WARNING		0x35
#define TAG_TRACE_VARIABLE_CRITICAL_UPPER_LIMIT		0x36
#define TAG_TRACE_VARIABLE_MAX_WARNING_COLOR		0x37
#define TAB_TRACE_VARIABLE_SECOND_YAXIS				0x38
#define TAG_TRACE_PACKET_HANDLE						0x40
#define TAG_TRACE_RECORD_HANDLE						0x41
#define TAG_TRACE_RECORD_BUFFER						0x42

#define TAG_TRACE_VARIABLE_INSTANCE_AREA			0x43
#define TAG_TRACE_VARIABLE_INSTANCE_OFFSET			0x44
#define TAG_TRACE_VARIABLE_PROPERTY_AREA			0x45
#define TAG_TRACE_VARIABLE_PROPERTY_OFFSET			0x46

#define TAG_TRACE_RECORD_RESULT						0x47
#define TAG_TRACE_RECORD_LAST_TIMESTAMP				0x48
#define TAG_TRACE_RECORD_ENTRIES					0x49
#define TAG_TRACE_PACKET_TIMESTAMP					0x4A

#define TAG_TRACE_VARIABLE_MONITORING_SERVICE		0x4B
/* Name of the file to save the trace to resp. load from. */
#define TAG_TRACE_FILENAME							0x4C
#define TAG_TRACE_VARIABLE_MONITORING2_BYTECODE     0x4D
#define TAG_TRACE_VARIABLE_MONITORING2_SIZE_BYTES   0x4E

#define TAGNEST_TRACE_TRIGGER					0x86
#define TAG_TRACE_TRIGGER_LEVEL					0x30
#define TAG_TRACE_TRIGGER_EDGE					0x31
#define TAG_TRACE_TRIGGER_POSITION				0x32
#define TAG_TRACE_TRIGGER_FLAGS					0x33
#define TAG_TRACE_TRIGGER_UPDATESAFTERTRIGGER	0x34
/* TAGNEST_TRACE_VARIABLE */

#define TAGNEST_TRACE_STATE						0x87
#define TAG_TRACE_STATE							0x50
#define TAG_TRACE_START_TIME					0x51
#define TAG_TRACE_TRIGGER_STATE					0x52
#define TAG_TRACE_TRIGGER_REACHED_TIMESTAMP		0x53
#define TAG_TRACE_TRIGGER_REACHED_DATE			0x54
/* The timestamp, when the packet was modified (e.g. record added, record deleted) last time. */
#define TAG_TRACE_CHANGED_TIME					0x55
/* The absolute timestamp, when the packet was started. */
#define TAG_TRACE_ABSOLUTE_START_TIME			0x56

/**
 * <category>Trace packet flags</category>
 * <element name="TRACE_PACKET_FLAGS_NOT_INITIALIZED" type="IN">Trace packet is not initialized</element>
 * <element name="TRACE_PACKET_FLAGS_COMPLETED" type="IN">Sign, that the trace packet is completed (all records added)</element>
 * <element name="TRACE_PACKET_FLAGS_AUTOSTART" type="IN">Persistent storage of the trace, an automatic start of the trace after reboot or to restore only on request</element>
 * <element name="TRACE_PACKET_FLAGS_CONDITION" type="IN">Optional boolean condition for the trace packet specified</element>
 * <element name="TRACE_PACKET_FLAGS_TIMESTAMP_MS" type="IN">Timestamp for the trace values have milliseonds reaolution (ticks)</element>
 * <element name="TRACE_PACKET_FLAGS_TIMESTAMP_US" type="IN">Timestamp for the trace values have microseonds reaolution (ticks)</element>
 * <element name="TRACE_PACKET_FLAGS_STORE_IN_FILE" type="IN">Is used to initiate to store trace persistent in file. Only used, if TRACE_PACKET_FLAGS_AUTOSTART is set.</element>
 * <element name="TRACE_PACKET_FLAGS_SYSTEM_TRACE" type="IN">Is used to mark a trace as system trace.</element>
 */
#define TRACE_PACKET_FLAGS_NOT_INITIALIZED			0x00000000
#define TRACE_PACKET_FLAGS_COMPLETED				0x00000001
#define TRACE_PACKET_FLAGS_AUTOSTART				0x00000002
#define TRACE_PACKET_FLAGS_CONDITION				0x00000004
#define TRACE_PACKET_FLAGS_TIMESTAMP_MS				0x00000010
#define TRACE_PACKET_FLAGS_TIMESTAMP_US				0x00000020
#define TRACE_PACKET_FLAGS_STORE_IN_FILE			0x00000040
#define TRACE_PACKET_FLAGS_SYSTEM_TRACE				0x00010000


/**
 * <category>Trace state</category>
 * <element name="TRACE_PACKET_STATE_NO_CONFIG" type="IN">Trace packet: No configuration</element>
 * <element name="TRACE_PACKET_STATE_DISABLED" type="IN">Trace packet disabled</element>
 * <element name="TRACE_PACKET_STATE_ENABLED" type="IN">Trace packet enabled</element>
 * <element name="TRACE_PACKET_STATE_STARTED" type="IN">Trace packet started</element>
 * <element name="TRACE_PACKET_STATE_STOPPED" type="IN">Trace packet stopped</element>
 */
#define TRACE_PACKET_STATE_NO_CONFIG				0x00000000
#define TRACE_PACKET_STATE_DISABLED					0x00000001
#define TRACE_PACKET_STATE_ENABLED					0x00000002
#define TRACE_PACKET_STATE_STARTED					0x00000003
#define TRACE_PACKET_STATE_STOPPED					0x00000004


/**
 * <category>Trigger edge</category>
 * <element name="TRIGGER_EDGE_NONE" type="IN">No trigger edge specified</element>
 * <element name="TRIGGER_EDGE_RISING" type="IN">Rising trigger edge specified</element>
 * <element name="TRIGGER_EDGE_TRAILING" type="IN">Trailing trigger edge specified</element>
 * <element name="TRIGGER_EDGE_BOTH" type="IN">Both trigger edges specified (rising and trailing)</element>
 */
#define TRIGGER_EDGE_NONE		0
#define TRIGGER_EDGE_RISING		1
#define TRIGGER_EDGE_TRAILING	2
#define TRIGGER_EDGE_BOTH		3


/**
 * <category>Trigger state</category>
 * <element name="TRACE_TRIGGER_STATE_DISABLED" type="IN">Trigger disabled</element>
 * <element name="TRACE_TRIGGER_STATE_ENABLED" type="IN">Trigger enabled</element>
 * <element name="TRACE_TRIGGER_STATE_WAIT_FOR_TRIGGER" type="IN">Waiting for trigger</element>
 * <element name="TRACE_TRIGGER_STATE_TRIGGER_REACHED" type="IN">Trigger reached</element>
 */
#define TRACE_TRIGGER_STATE_DISABLED				0x00000000
#define TRACE_TRIGGER_STATE_ENABLED					0x00000001
#define TRACE_TRIGGER_STATE_WAIT_FOR_TRIGGER		0x00000002
#define TRACE_TRIGGER_STATE_TRIGGER_REACHED			0x00000003


/**
 * <category>Trigger flags</category>
 * <element name="TRACE_TRIGGER_FLAGS_UNDEFINED" type="IN">Trigger undefined</element>
 * <element name="TRACE_TRIGGER_FLAGS_DEFINED" type="IN">Trigger defined</element>
 * <element name="TRACE_TRIGGER_FLAGS_UPDATESAFTERTRIGGER" type="IN">UpdatesAfterTrigger is used instead of TriggerPosition</element>
 */
#define TRACE_TRIGGER_FLAGS_UNDEFINED				0x00000000
#define TRACE_TRIGGER_FLAGS_DEFINED					0x00000001
#define TRACE_TRIGGER_FLAGS_UPDATESAFTERTRIGGER		0x00000004

/**
 * <category>Trace variable address flags</category>
 * <description>
 *	Trace variable address flags.
 *
 *	Usage: The flags mus be used in combination. Here are some typical combinations:
 *		ulFlags = TRACE_VAR_ADDRESS_FLAGS_IEC | TRACE_VAR_ADDRESS_FLAGS_AREA_OFFSET;
 *		ulFlags = TRACE_VAR_ADDRESS_FLAGS_IEC | TRACE_VAR_ADDRESS_FLAGS_PROPERTY;
 *		ulFlags = TRACE_VAR_ADDRESS_FLAGS_IEC | TRACE_VAR_ADDRESS_FLAGS_POINTER;
 *		ulFlags = TRACE_VAR_ADDRESS_FLAGS_IEC | TRACE_VAR_ADDRESS_FLAGS_MONITORING;
 *		ulFlags = TRACE_VAR_ADDRESS_FLAGS_IOCONFIG;
 *		ulFlags = TRACE_VAR_ADDRESS_FLAGS_SYSTEM;
 *		
 * </description>
 * <element name="TRACE_VAR_ADDRESS_FLAGS_IEC" type="IN">IEC variable (automatic update)</element>
 * <element name="TRACE_VAR_ADDRESS_FLAGS_IOCONFIG" type="IN">IO-Config variable (automatic update)</element>
 * <element name="TRACE_VAR_ADDRESS_FLAGS_SYSTEM" type="IN">System variable (update must do the system or IEC program!)</element>
 * <element name="TRACE_VAR_ADDRESS_FLAGS_POINTER" type="IN">Address specified by a pointer</element>
 * <element name="TRACE_VAR_ADDRESS_FLAGS_AREA_OFFSET" type="IN">Address specified by area/offset (IEC)</element>
 * <element name="TRACE_VAR_ADDRESS_FLAGS_PROPERTY" type="IN">Address is a property variable (IEC)</element>
 * <element name="TRACE_VAR_ADDRESS_FLAGS_MONITORING" type="IN">Address is an item with a monitoring request (IEC)</element>
 * <element name="TRACE_VAR_ADDRESS_FLAGS_SYMBOLIC" type="IN">The variable will be accessed using the symbol configuration based on its name</element>
 * <element name="TRACE_VAR_ADDRESS_FLAGS_MONITORING2" type="IN">Address is an item with a monitoring request for CmpMonitor2 (IEC)</element>
 */
#define TRACE_VAR_ADDRESS_FLAGS_IEC				0x00000001
#define TRACE_VAR_ADDRESS_FLAGS_IOCONFIG		0x00000002
#define TRACE_VAR_ADDRESS_FLAGS_SYSTEM			0x00000004
#define TRACE_VAR_ADDRESS_FLAGS_POINTER			0x00000010
#define TRACE_VAR_ADDRESS_FLAGS_AREA_OFFSET		0x00000020
#define TRACE_VAR_ADDRESS_FLAGS_PROPERTY		0x00000040
#define TRACE_VAR_ADDRESS_FLAGS_MONITORING		0x00000080
#define TRACE_VAR_ADDRESS_FLAGS_SYMBOLIC        0x00000100
#define TRACE_VAR_ADDRESS_FLAGS_MONITORING2     0x00000200

/**
 * <category>Graph types</category>
 * <element name="TRACE_RECORD_GRAPHTYPE_NONE" type="IN"></element>
 * <element name="TRACE_RECORD_GRAPHTYPE_LINE" type="IN"></element>
 * <element name="TRACE_RECORD_GRAPHTYPE_CROSS" type="IN"></element>
 * <element name="TRACE_RECORD_GRAPHTYPE_STEP" type="IN"></element>
 * <element name="TRACE_RECORD_GRAPHTYPE_POINT" type="IN"></element>
 * <element name="TRACE_RECORD_GRAPHTYPE_LINES_NO_POINTS" type="IN"></element>
 * <element name="TRACE_RECORD_GRAPHTYPE_STEPS_NO_POINTS" type="IN"></element>
 * <element name="TRACE_RECORD_GRAPHTYPE_LINES_POINTS" type="IN"></element>
 * <element name="TRACE_RECORD_GRAPHTYPE_STEPS_POINTS" type="IN"></element>
 */
#define TRACE_RECORD_GRAPHTYPE_NONE				0
#define TRACE_RECORD_GRAPHTYPE_LINE				1
#define TRACE_RECORD_GRAPHTYPE_CROSS			2
#define TRACE_RECORD_GRAPHTYPE_STEP				4
#define TRACE_RECORD_GRAPHTYPE_POINT			5
#define TRACE_RECORD_GRAPHTYPE_LINES_NO_POINTS  8
#define TRACE_RECORD_GRAPHTYPE_STEPS_NO_POINTS  9
#define TRACE_RECORD_GRAPHTYPE_LINES_POINTS    10
#define TRACE_RECORD_GRAPHTYPE_STEPS_POINTS    11

/**
 * <category>Monitoring2 byte code constants</category>
 * <element name="TRACE_MONITORING2_STATIC_BYTECODE_SIZE_CHARS" type="IN">The size of the static storage for byte code in the union Monitoring2ByteCodeUnion</element>
 */
#define TRACE_MONITORING2_STATIC_BYTECODE_SIZE_CHARS 16

struct tagTraceTrigger;
struct tagTraceVariable;

/**
 * Configuration of a trace packet
 */
typedef struct tagTracePacketConfiguration
{
	RTS_IEC_STRING *pszName;		/* The name of the trace packet */
	RTS_IEC_STRING *pszApplicationName;		/* The name of the application (optional) */
	RTS_IEC_STRING *pszIecTaskName;		/* IEC-task name in which the samples are recorded (optional) */
	RTS_IEC_STRING *pszComment;		/* A comment for the packet (optional) */
	struct tagTraceTrigger *pttTrigger;		/* Pointer to a trigger description (optional) */
	struct tagTraceVariable *ptvCondition;		/* A pointer to the description of a boolean variable. If given, samples are recorded only if the variable has value true. (optional, must be present if TRACE_PACKET_FLAGS_CONDITION is set in ulFlags) */
	RTS_IEC_UDINT ulEveryNCycles;		/* Record samples every ulEveryNCycles cycles.  Must be > 0. (Default: 1) */
	RTS_IEC_UDINT ulBufferEntries;		/* The number of samples that the trace buffer can hold. */
	RTS_IEC_UDINT ulFlags;		/* Trace packet flags.  See TRACE_PACKET_FLAGS. */
	/* The interface, starting from here is only used in C and not
	 * exported to IEC.
	 */
	RTS_GUID ApplicationDataGuid;
} TracePacketConfiguration;


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Description of an IEC address
 */
typedef struct tagAddressArea
{
	RTS_IEC_UDINT ulOffset;		/* Offset in an area of the memory segment in an IEC-application */
	RTS_IEC_WORD usArea;		/* Area number of the memory segment in an IEC-application */
} AddressArea;

/**
 * Parameter type for trace manager packet events
 */
typedef struct tagEVTPARAM_CmpTraceMgr_Packet
{
	RTS_IEC_HANDLE hPacket;		/* Handle to a trace packet */
} EVTPARAM_CmpTraceMgr_Packet;

/**
 * Parameter type for trace manager record events
 */
typedef struct tagEVTPARAM_CmpTraceMgr_Record
{
	RTS_IEC_HANDLE hPacket;		/* Handle to a trace packet */
	RTS_IEC_HANDLE hRecord;		/* Handle to a trace record */
} EVTPARAM_CmpTraceMgr_Record;

/**
 * <description>Monitoring2ByteCodeUnion</description>
 */
typedef union
{
	RTS_IEC_BYTE *pbyByteCode;		
	RTS_IEC_BYTE aByteCode[TRACE_MONITORING2_STATIC_BYTECODE_SIZE_CHARS];		/* see: |TRACE_MONITORING2_STATIC_BYTECODE_SIZE_CHARS| */
} Monitoring2ByteCodeUnion;

/**
 * <description>Monitoring2ByteCode</description>
 */
typedef struct tagMonitoring2ByteCode
{
	Monitoring2ByteCodeUnion byteCode;		
	RTS_IEC_DWORD ulSizeInBytes;		
} Monitoring2ByteCode;

/**
 * <description>MonitoringService</description>
 */
typedef struct tagMonitoringService
{
	RTS_IEC_BYTE *pbyService;		
	RTS_IEC_DWORD ulSize;		
} MonitoringService;

/**
 * <description>PropertyLocation</description>
 */
typedef struct tagPropertyLocation
{
	AddressArea adrInstance;		
	AddressArea adrPropertyFunction;		
} PropertyLocation;

/**
 * <description>TraceVarInfo</description>
 */
typedef union
{
	VariableInformationStruct info;		
	VariableInformationStruct2 *pInfo;		
} TraceVarInfo;

/**
 * <description>SymVarAccess</description>
 */
typedef struct tagSymVarAccess
{
	RTS_IEC_HANDLE hInterface;		
	RTS_IEC_HANDLE hNode;		
	TraceVarInfo varInfo;		
} SymVarAccess;

/**
 * Description of an IO-config device parameter
 */
typedef struct tagSystemParameter
{
	RTS_IEC_UDINT ulID;		/* ParameterID */
	RTS_IEC_UDINT ulOffset;		/* Offset of the subelement */
	RTS_IEC_UDINT ulModuleType;		/* Module type which contains the parameter */
	RTS_IEC_UDINT ulInstance;		/* Instance number of the module instance */
} SystemParameter;

/**
 * Address of a trace variable
 */
typedef union
{
	RTS_IEC_BYTE *pbyAddress;		/* Pointer to the trace variable */
	AddressArea Area;		/* Area/Offset of an IEC variable */
	SystemParameter systemParameter;		/* Parameter of a system variable (e.g. device parameter) */
	PropertyLocation propertyLocation;		/* Only used for property monitoring */
	MonitoringService monitoringService;		/* Only used by monitoring service */
	SymVarAccess symVarAccess;		/* Use for symbolic variable tracing */
	Monitoring2ByteCode monitoring2ByteCode;		/* Reserved */
} TraceAddress;

/**
 * Address description of a single trace variable
 */
typedef struct tagTraceVariableAddress
{
	RTS_IEC_UDINT ulAddressFlags;		/* Address flags. See |TRACE_VAR_ADDRESS_FLAGS| */
	TraceAddress taAddress;		/* Trace address definition */
} TraceVariableAddress;

/**
 * Definition of a single trace variable
 */
typedef struct tagTraceVariable
{
	RTS_IEC_STRING *pszName;		/* Name of the variable */
	TraceVariableAddress tvaAddress;		/* Address definition of the variable */
	RTS_IEC_UDINT tcClass;		/* Type class of the variable. See enum IBase.TypeClass for the possible values. */
	RTS_IEC_UDINT ulSize;		/* Size in bytes of a sample value */
} TraceVariable;

/**
 * An union for all possible types of trigger values
 */
typedef union
{
	RTS_IEC_SINT b;		
	RTS_IEC_BYTE uc;		
	RTS_IEC_INT si;		
	RTS_IEC_WORD usi;		
	RTS_IEC_DINT l;		
	RTS_IEC_UDINT ul;		
	RTS_IEC_REAL f;		
	RTS_IEC_LINT ll;		
	RTS_IEC_LWORD ull;		
	RTS_IEC_LREAL d;		
} TriggerValue;

/**
 * Configuration of the trace trigger
 */
typedef struct tagTraceTrigger
{
	TraceVariable tvVariable;		/* Specification of the trigger variable */
	TriggerValue ttvLevel;		/* Holds the trigger level for analog (i.e. non-boolean) triggers */
	RTS_IEC_UDINT ulFlags;		/* Trigger flags. See |TRACE_TRIGGER_FLAGS|. */
	RTS_IEC_BYTE byEdge;		/* Trigger edge. See |TRACE_TRIGGER_EDGE|. */
	RTS_IEC_BYTE byPosition;		/* Number of samples to record after the trigger has fired in percent (0..100) of the buffer size.  Deprecated, use ulUpdatesAfterTrigger instead. */
	RTS_IEC_WORD wAlignmentDummy;		/* Alignment bytes */
	RTS_IEC_UDINT ulUpdatesAfterTrigger;		/* Number of samples to record after the trigger has fired. Note: |TRACE_TRIGGER_FLAGS_UPDATESAFTERTRIGGER| must be set in ulFlags, if this entry is used instead of byPosition. */
} TraceTrigger;

/**
 * Trace record configuration
 *
 * The colors (ulGraphColor, ulMinWarningColor, ulMaxWarningColor)
 * and are encoded in UDINTs in the ARGB format: the most significand
 * byte is the alpha value, the next byte the red value, followed by
 * green and blue.  Each color component takes a value between 0 and FF.
 * So 0xFF000000 is white, 0xFFFFFFFF is black, 0xFFFF0000 is red,
 * 0xFF00FF00 is green, and 0xFF0000FF is blue.
 */
typedef struct tagTraceRecordConfiguration
{
	RTS_IEC_STRING *pszVariable;		/* Name of the variable */
	TraceVariableAddress tvaAddress;		/* Address definition of the variable */
	RTS_IEC_UDINT tcClass;		/* Type class of the variable. See enum IBase.TypeClass for the possible values. */
	RTS_IEC_UDINT ulSize;		/* Size in bytes of a single sample */
	RTS_IEC_UDINT ulGraphColor;		/* Color in which the trace curve for the variable should be displayed */
	RTS_IEC_UDINT ulGraphType;		/* | Graph type:
 | 1: line (with points)    
 | 2: cross    
 | 4: step (with points)    
 | 5: point    
 | 8: line (without points)    
 | 9: step (without points)    
 | 10: line (with crosses)    
 | 11: steps (with crosses)) */
	RTS_IEC_UDINT ulMinWarningColor;		/* Color to use if a sample is <= fCriticalLowerLimit */
	RTS_IEC_UDINT ulMaxWarningColor;		/* Color to use if a sample is >= fCriticalUpperLimit */
	RTS_IEC_REAL fCriticalLowerLimit;		/* The lower limit */
	RTS_IEC_REAL fCriticalUpperLimit;		/* The upper limit */
	RTS_IEC_BOOL bActivateMinWarning;		/* If set, the trace  will be displayed in the color ulMinWarningColor as soon as a sample is <= fCriticalLowerLimit */
	RTS_IEC_BOOL bActivateMaxWarning;		/* If set, the trace  will be displayed in the color ulMaxWarningColor as soon as a sample is >= fCriticalUpperLimit */
	RTS_IEC_BYTE byYAxis;		/* Not used */
} TraceRecordConfiguration;

/**
 * A single entry recorded for a trace variable consisting of a relative time stamp
 * and a (variable-size) data part.  The size of the data depends on the type class
 * of the trace variable.
 */
typedef struct tagTraceRecordEntry
{
	RTS_IEC_UDINT ulTimeRelative;		/* The relative time stamp (since the trace was first started, see TraceState.tStartTime) in the resolution configured for the trace packet */
	RTS_IEC_BYTE Data;		/* A (variable size) data portion for the sample value */
} TraceRecordEntry;

/**
 * The state of the trigger
 */
typedef struct tagTriggerState
{
	RTS_IEC_UDINT ulState;		/* The state. See |TRACE_TRIGGER_STATE| */
	RTS_IEC_UDINT dtTriggerDate;		/* The date of the trigger event (in UTC) */
	RTS_IEC_ULINT tTriggerReached;		/* The time of the trigger event */
} TriggerState;

/**
 * The state of a trace packet
 */
typedef struct tagTraceState
{
	RTS_IEC_UDINT ulState;		/* The state.  See |TRACE_PACKET_STATE| */
	RTS_IEC_UDINT ulFillLevel;		/* The number of recorded samples */
	RTS_IEC_ULINT tStartTime;		/* The time of the first start of the trace, all time stamps are relative to this value. */
	TriggerState tsTriggerState;		/* The state of the trigger. */
} TraceState;

/**
 * Loads a given trace file and returns the configuration it contains. After this function
 * call a call to function |TraceMgrGetConfigFromFileRelease| is necessary to free the dynamically allocated
 * memory.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if pszFileName is not a valid file path
 *   - ERR_NOMEMORY if the memory is not sufficient for opening the file
 *   - ERR_NOT_SUPPORTED if reading from files is not supported by the runtime system
 *     or if an addressing mode is not supported (e.g. symbolic access)
 *   - ERR_NO_OBJECT if opening the file failed
 *   - ERR_FAILED if opening the file failed
 *   - ERR_END_OF_OBJECT if either the packet configuration or the record configuration is incomplete
 *   - ERR_NO_CHANGE if a NULL pointer was passed to parameter
 *   - ERR_OUT_OF_LIMITS if the parameters ``pRecordConfiguration`` and ``iMaxRecordCount``
 *     do not have enough memory to hold all the records from the file
 */
typedef struct tagtracemgrgetconfigfromfile_struct
{
	RTS_IEC_STRING *pszFileName;		/* VAR_INPUT */	/* The file path (in) */
	TracePacketConfiguration *pPacketConfiguration;	/* VAR_INPUT */	/* Points to a TracePacketConfiguration variable, where the packet configuration will be returned (out) */
	TraceRecordConfiguration *pRecordConfiguration;	/* VAR_INPUT */	/* Points to a TraceRecordConfiguration variable (or an array of TraceRecordConfiguration variables), 
 where the trace record configuration will be returned. (out)
 If a NULL pointer is passed this function only determines the number of records in the file. */
	RTS_IEC_DINT iMaxRecordCount;		/* VAR_INPUT */	/* Contains the maximum number of records, that can be stored in the array pRecordConfiguration (in) */
	RTS_IEC_DINT *piEffectiveRecordCount;	/* VAR_IN_OUT */	/* Returns the effective number of records read (out).
 In case of return code ERR_NO_CHANGE this variable contains the number of records in the file. */
	RTS_IEC_RESULT TraceMgrGetConfigFromFile;	/* VAR_OUTPUT */	/* The result code */
} tracemgrgetconfigfromfile_struct;

void CDECL CDECL_EXT tracemgrgetconfigfromfile(tracemgrgetconfigfromfile_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRGETCONFIGFROMFILE_IEC) (tracemgrgetconfigfromfile_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRGETCONFIGFROMFILE_NOTIMPLEMENTED)
	#define USE_tracemgrgetconfigfromfile
	#define EXT_tracemgrgetconfigfromfile
	#define GET_tracemgrgetconfigfromfile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrgetconfigfromfile(p0) 
	#define CHK_tracemgrgetconfigfromfile  FALSE
	#define EXP_tracemgrgetconfigfromfile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrgetconfigfromfile
	#define EXT_tracemgrgetconfigfromfile
	#define GET_tracemgrgetconfigfromfile(fl)  CAL_CMGETAPI( "tracemgrgetconfigfromfile" ) 
	#define CAL_tracemgrgetconfigfromfile  tracemgrgetconfigfromfile
	#define CHK_tracemgrgetconfigfromfile  TRUE
	#define EXP_tracemgrgetconfigfromfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrgetconfigfromfile", (RTS_UINTPTR)tracemgrgetconfigfromfile, 1, RTSITF_GET_SIGNATURE(0, 0x6FE07E94), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrgetconfigfromfile
	#define EXT_tracemgrgetconfigfromfile
	#define GET_tracemgrgetconfigfromfile(fl)  CAL_CMGETAPI( "tracemgrgetconfigfromfile" ) 
	#define CAL_tracemgrgetconfigfromfile  tracemgrgetconfigfromfile
	#define CHK_tracemgrgetconfigfromfile  TRUE
	#define EXP_tracemgrgetconfigfromfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrgetconfigfromfile", (RTS_UINTPTR)tracemgrgetconfigfromfile, 1, RTSITF_GET_SIGNATURE(0, 0x6FE07E94), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrgetconfigfromfile
	#define EXT_CmpTraceMgrtracemgrgetconfigfromfile
	#define GET_CmpTraceMgrtracemgrgetconfigfromfile  ERR_OK
	#define CAL_CmpTraceMgrtracemgrgetconfigfromfile  tracemgrgetconfigfromfile
	#define CHK_CmpTraceMgrtracemgrgetconfigfromfile  TRUE
	#define EXP_CmpTraceMgrtracemgrgetconfigfromfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrgetconfigfromfile", (RTS_UINTPTR)tracemgrgetconfigfromfile, 1, RTSITF_GET_SIGNATURE(0, 0x6FE07E94), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrgetconfigfromfile
	#define EXT_tracemgrgetconfigfromfile
	#define GET_tracemgrgetconfigfromfile(fl)  CAL_CMGETAPI( "tracemgrgetconfigfromfile" ) 
	#define CAL_tracemgrgetconfigfromfile  tracemgrgetconfigfromfile
	#define CHK_tracemgrgetconfigfromfile  TRUE
	#define EXP_tracemgrgetconfigfromfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrgetconfigfromfile", (RTS_UINTPTR)tracemgrgetconfigfromfile, 1, RTSITF_GET_SIGNATURE(0, 0x6FE07E94), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrgetconfigfromfile  PFTRACEMGRGETCONFIGFROMFILE_IEC pftracemgrgetconfigfromfile;
	#define EXT_tracemgrgetconfigfromfile  extern PFTRACEMGRGETCONFIGFROMFILE_IEC pftracemgrgetconfigfromfile;
	#define GET_tracemgrgetconfigfromfile(fl)  s_pfCMGetAPI2( "tracemgrgetconfigfromfile", (RTS_VOID_FCTPTR *)&pftracemgrgetconfigfromfile, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x6FE07E94), 0x03050B00)
	#define CAL_tracemgrgetconfigfromfile  pftracemgrgetconfigfromfile
	#define CHK_tracemgrgetconfigfromfile  (pftracemgrgetconfigfromfile != NULL)
	#define EXP_tracemgrgetconfigfromfile   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrgetconfigfromfile", (RTS_UINTPTR)tracemgrgetconfigfromfile, 1, RTSITF_GET_SIGNATURE(0, 0x6FE07E94), 0x03050B00) 
#endif


/**
 * This function has to be called after |TraceMgrGetConfigFromFile|. It frees
 * the dynamically allocated memory for the strings of the packet resp. record configuration.
 * :return: Returns the runtime system error code (see CmpErrors.library) 
 */
typedef struct tagtracemgrgetconfigfromfilerelease_struct
{
	TracePacketConfiguration *pPacketConfiguration;	/* VAR_INPUT */	/* Points to a TracePacketConfiguration variable, where the packet configuration was stored (in) */
	TraceRecordConfiguration *pRecordConfiguration;	/* VAR_INPUT */	/* Points to a TraceRecordConfiguration variable (or an array of TraceRecordConfiguration variables), 
 where the trace record configuration was stored. (in) */
	RTS_IEC_DINT iRecordCount;			/* VAR_INPUT */	/* Contains real number of records, that are stored in the array pRecordConfiguration (in) */
	RTS_IEC_RESULT TraceMgrGetConfigFromFileRelease;	/* VAR_OUTPUT */	/* The result code */
} tracemgrgetconfigfromfilerelease_struct;

void CDECL CDECL_EXT tracemgrgetconfigfromfilerelease(tracemgrgetconfigfromfilerelease_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRGETCONFIGFROMFILERELEASE_IEC) (tracemgrgetconfigfromfilerelease_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRGETCONFIGFROMFILERELEASE_NOTIMPLEMENTED)
	#define USE_tracemgrgetconfigfromfilerelease
	#define EXT_tracemgrgetconfigfromfilerelease
	#define GET_tracemgrgetconfigfromfilerelease(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrgetconfigfromfilerelease(p0) 
	#define CHK_tracemgrgetconfigfromfilerelease  FALSE
	#define EXP_tracemgrgetconfigfromfilerelease  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrgetconfigfromfilerelease
	#define EXT_tracemgrgetconfigfromfilerelease
	#define GET_tracemgrgetconfigfromfilerelease(fl)  CAL_CMGETAPI( "tracemgrgetconfigfromfilerelease" ) 
	#define CAL_tracemgrgetconfigfromfilerelease  tracemgrgetconfigfromfilerelease
	#define CHK_tracemgrgetconfigfromfilerelease  TRUE
	#define EXP_tracemgrgetconfigfromfilerelease  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrgetconfigfromfilerelease", (RTS_UINTPTR)tracemgrgetconfigfromfilerelease, 1, RTSITF_GET_SIGNATURE(0, 0x1E24AEEF), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrgetconfigfromfilerelease
	#define EXT_tracemgrgetconfigfromfilerelease
	#define GET_tracemgrgetconfigfromfilerelease(fl)  CAL_CMGETAPI( "tracemgrgetconfigfromfilerelease" ) 
	#define CAL_tracemgrgetconfigfromfilerelease  tracemgrgetconfigfromfilerelease
	#define CHK_tracemgrgetconfigfromfilerelease  TRUE
	#define EXP_tracemgrgetconfigfromfilerelease  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrgetconfigfromfilerelease", (RTS_UINTPTR)tracemgrgetconfigfromfilerelease, 1, RTSITF_GET_SIGNATURE(0, 0x1E24AEEF), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrgetconfigfromfilerelease
	#define EXT_CmpTraceMgrtracemgrgetconfigfromfilerelease
	#define GET_CmpTraceMgrtracemgrgetconfigfromfilerelease  ERR_OK
	#define CAL_CmpTraceMgrtracemgrgetconfigfromfilerelease  tracemgrgetconfigfromfilerelease
	#define CHK_CmpTraceMgrtracemgrgetconfigfromfilerelease  TRUE
	#define EXP_CmpTraceMgrtracemgrgetconfigfromfilerelease  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrgetconfigfromfilerelease", (RTS_UINTPTR)tracemgrgetconfigfromfilerelease, 1, RTSITF_GET_SIGNATURE(0, 0x1E24AEEF), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrgetconfigfromfilerelease
	#define EXT_tracemgrgetconfigfromfilerelease
	#define GET_tracemgrgetconfigfromfilerelease(fl)  CAL_CMGETAPI( "tracemgrgetconfigfromfilerelease" ) 
	#define CAL_tracemgrgetconfigfromfilerelease  tracemgrgetconfigfromfilerelease
	#define CHK_tracemgrgetconfigfromfilerelease  TRUE
	#define EXP_tracemgrgetconfigfromfilerelease  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrgetconfigfromfilerelease", (RTS_UINTPTR)tracemgrgetconfigfromfilerelease, 1, RTSITF_GET_SIGNATURE(0, 0x1E24AEEF), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrgetconfigfromfilerelease  PFTRACEMGRGETCONFIGFROMFILERELEASE_IEC pftracemgrgetconfigfromfilerelease;
	#define EXT_tracemgrgetconfigfromfilerelease  extern PFTRACEMGRGETCONFIGFROMFILERELEASE_IEC pftracemgrgetconfigfromfilerelease;
	#define GET_tracemgrgetconfigfromfilerelease(fl)  s_pfCMGetAPI2( "tracemgrgetconfigfromfilerelease", (RTS_VOID_FCTPTR *)&pftracemgrgetconfigfromfilerelease, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x1E24AEEF), 0x03050B00)
	#define CAL_tracemgrgetconfigfromfilerelease  pftracemgrgetconfigfromfilerelease
	#define CHK_tracemgrgetconfigfromfilerelease  (pftracemgrgetconfigfromfilerelease != NULL)
	#define EXP_tracemgrgetconfigfromfilerelease   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrgetconfigfromfilerelease", (RTS_UINTPTR)tracemgrgetconfigfromfilerelease, 1, RTSITF_GET_SIGNATURE(0, 0x1E24AEEF), 0x03050B00) 
#endif


/**
 * Checks if the trigger fires this cycle and sets the trigger state
 * accordingly.
 *
 * If the trigger is already reached, ERR_OK is returned.
 *
 * Note: this function is called cyclically by CmpTraceMgr and should normally 
 * not be called from an application.  Use TraceMgrPacketGetState instead to
 * query the current trigger state.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid trace packet
 *   - ERR_NOTINITIALIZED if no trigger is defined or if the trigger is disabled
 *   - ERR_FAILED if the check fails
 */
typedef struct tagtracemgrpacketchecktrigger_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_RESULT TraceMgrPacketCheckTrigger;	/* VAR_OUTPUT */	/* The result code */
} tracemgrpacketchecktrigger_struct;

void CDECL CDECL_EXT tracemgrpacketchecktrigger(tracemgrpacketchecktrigger_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETCHECKTRIGGER_IEC) (tracemgrpacketchecktrigger_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETCHECKTRIGGER_NOTIMPLEMENTED)
	#define USE_tracemgrpacketchecktrigger
	#define EXT_tracemgrpacketchecktrigger
	#define GET_tracemgrpacketchecktrigger(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketchecktrigger(p0) 
	#define CHK_tracemgrpacketchecktrigger  FALSE
	#define EXP_tracemgrpacketchecktrigger  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketchecktrigger
	#define EXT_tracemgrpacketchecktrigger
	#define GET_tracemgrpacketchecktrigger(fl)  CAL_CMGETAPI( "tracemgrpacketchecktrigger" ) 
	#define CAL_tracemgrpacketchecktrigger  tracemgrpacketchecktrigger
	#define CHK_tracemgrpacketchecktrigger  TRUE
	#define EXP_tracemgrpacketchecktrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketchecktrigger", (RTS_UINTPTR)tracemgrpacketchecktrigger, 1, 0xD2E54704, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketchecktrigger
	#define EXT_tracemgrpacketchecktrigger
	#define GET_tracemgrpacketchecktrigger(fl)  CAL_CMGETAPI( "tracemgrpacketchecktrigger" ) 
	#define CAL_tracemgrpacketchecktrigger  tracemgrpacketchecktrigger
	#define CHK_tracemgrpacketchecktrigger  TRUE
	#define EXP_tracemgrpacketchecktrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketchecktrigger", (RTS_UINTPTR)tracemgrpacketchecktrigger, 1, 0xD2E54704, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketchecktrigger
	#define EXT_CmpTraceMgrtracemgrpacketchecktrigger
	#define GET_CmpTraceMgrtracemgrpacketchecktrigger  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketchecktrigger  tracemgrpacketchecktrigger
	#define CHK_CmpTraceMgrtracemgrpacketchecktrigger  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketchecktrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketchecktrigger", (RTS_UINTPTR)tracemgrpacketchecktrigger, 1, 0xD2E54704, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketchecktrigger
	#define EXT_tracemgrpacketchecktrigger
	#define GET_tracemgrpacketchecktrigger(fl)  CAL_CMGETAPI( "tracemgrpacketchecktrigger" ) 
	#define CAL_tracemgrpacketchecktrigger  tracemgrpacketchecktrigger
	#define CHK_tracemgrpacketchecktrigger  TRUE
	#define EXP_tracemgrpacketchecktrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketchecktrigger", (RTS_UINTPTR)tracemgrpacketchecktrigger, 1, 0xD2E54704, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketchecktrigger  PFTRACEMGRPACKETCHECKTRIGGER_IEC pftracemgrpacketchecktrigger;
	#define EXT_tracemgrpacketchecktrigger  extern PFTRACEMGRPACKETCHECKTRIGGER_IEC pftracemgrpacketchecktrigger;
	#define GET_tracemgrpacketchecktrigger(fl)  s_pfCMGetAPI2( "tracemgrpacketchecktrigger", (RTS_VOID_FCTPTR *)&pftracemgrpacketchecktrigger, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xD2E54704, 0x03050B00)
	#define CAL_tracemgrpacketchecktrigger  pftracemgrpacketchecktrigger
	#define CHK_tracemgrpacketchecktrigger  (pftracemgrpacketchecktrigger != NULL)
	#define EXP_tracemgrpacketchecktrigger   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketchecktrigger", (RTS_UINTPTR)tracemgrpacketchecktrigger, 1, 0xD2E54704, 0x03050B00) 
#endif


/**
 * Closes a handle opened by TraceMgrPacketOpen.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid handle
 */
typedef struct tagtracemgrpacketclose_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_RESULT TraceMgrPacketClose;	/* VAR_OUTPUT */	/* The result code */
} tracemgrpacketclose_struct;

void CDECL CDECL_EXT tracemgrpacketclose(tracemgrpacketclose_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETCLOSE_IEC) (tracemgrpacketclose_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETCLOSE_NOTIMPLEMENTED)
	#define USE_tracemgrpacketclose
	#define EXT_tracemgrpacketclose
	#define GET_tracemgrpacketclose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketclose(p0) 
	#define CHK_tracemgrpacketclose  FALSE
	#define EXP_tracemgrpacketclose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketclose
	#define EXT_tracemgrpacketclose
	#define GET_tracemgrpacketclose(fl)  CAL_CMGETAPI( "tracemgrpacketclose" ) 
	#define CAL_tracemgrpacketclose  tracemgrpacketclose
	#define CHK_tracemgrpacketclose  TRUE
	#define EXP_tracemgrpacketclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketclose", (RTS_UINTPTR)tracemgrpacketclose, 1, 0xBF67CDD5, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketclose
	#define EXT_tracemgrpacketclose
	#define GET_tracemgrpacketclose(fl)  CAL_CMGETAPI( "tracemgrpacketclose" ) 
	#define CAL_tracemgrpacketclose  tracemgrpacketclose
	#define CHK_tracemgrpacketclose  TRUE
	#define EXP_tracemgrpacketclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketclose", (RTS_UINTPTR)tracemgrpacketclose, 1, 0xBF67CDD5, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketclose
	#define EXT_CmpTraceMgrtracemgrpacketclose
	#define GET_CmpTraceMgrtracemgrpacketclose  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketclose  tracemgrpacketclose
	#define CHK_CmpTraceMgrtracemgrpacketclose  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketclose", (RTS_UINTPTR)tracemgrpacketclose, 1, 0xBF67CDD5, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketclose
	#define EXT_tracemgrpacketclose
	#define GET_tracemgrpacketclose(fl)  CAL_CMGETAPI( "tracemgrpacketclose" ) 
	#define CAL_tracemgrpacketclose  tracemgrpacketclose
	#define CHK_tracemgrpacketclose  TRUE
	#define EXP_tracemgrpacketclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketclose", (RTS_UINTPTR)tracemgrpacketclose, 1, 0xBF67CDD5, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketclose  PFTRACEMGRPACKETCLOSE_IEC pftracemgrpacketclose;
	#define EXT_tracemgrpacketclose  extern PFTRACEMGRPACKETCLOSE_IEC pftracemgrpacketclose;
	#define GET_tracemgrpacketclose(fl)  s_pfCMGetAPI2( "tracemgrpacketclose", (RTS_VOID_FCTPTR *)&pftracemgrpacketclose, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xBF67CDD5, 0x03050B00)
	#define CAL_tracemgrpacketclose  pftracemgrpacketclose
	#define CHK_tracemgrpacketclose  (pftracemgrpacketclose != NULL)
	#define EXP_tracemgrpacketclose   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketclose", (RTS_UINTPTR)tracemgrpacketclose, 1, 0xBF67CDD5, 0x03050B00) 
#endif


/**
 * Completes a trace packet and finishes the configuration.
 * This function must be called after all records have been added to the packet.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid handle
 */
typedef struct tagtracemgrpacketcomplete_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_RESULT TraceMgrPacketComplete;	/* VAR_OUTPUT */	/* The result code */
} tracemgrpacketcomplete_struct;

void CDECL CDECL_EXT tracemgrpacketcomplete(tracemgrpacketcomplete_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETCOMPLETE_IEC) (tracemgrpacketcomplete_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETCOMPLETE_NOTIMPLEMENTED)
	#define USE_tracemgrpacketcomplete
	#define EXT_tracemgrpacketcomplete
	#define GET_tracemgrpacketcomplete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketcomplete(p0) 
	#define CHK_tracemgrpacketcomplete  FALSE
	#define EXP_tracemgrpacketcomplete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketcomplete
	#define EXT_tracemgrpacketcomplete
	#define GET_tracemgrpacketcomplete(fl)  CAL_CMGETAPI( "tracemgrpacketcomplete" ) 
	#define CAL_tracemgrpacketcomplete  tracemgrpacketcomplete
	#define CHK_tracemgrpacketcomplete  TRUE
	#define EXP_tracemgrpacketcomplete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketcomplete", (RTS_UINTPTR)tracemgrpacketcomplete, 1, 0x77ED2847, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketcomplete
	#define EXT_tracemgrpacketcomplete
	#define GET_tracemgrpacketcomplete(fl)  CAL_CMGETAPI( "tracemgrpacketcomplete" ) 
	#define CAL_tracemgrpacketcomplete  tracemgrpacketcomplete
	#define CHK_tracemgrpacketcomplete  TRUE
	#define EXP_tracemgrpacketcomplete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketcomplete", (RTS_UINTPTR)tracemgrpacketcomplete, 1, 0x77ED2847, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketcomplete
	#define EXT_CmpTraceMgrtracemgrpacketcomplete
	#define GET_CmpTraceMgrtracemgrpacketcomplete  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketcomplete  tracemgrpacketcomplete
	#define CHK_CmpTraceMgrtracemgrpacketcomplete  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketcomplete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketcomplete", (RTS_UINTPTR)tracemgrpacketcomplete, 1, 0x77ED2847, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketcomplete
	#define EXT_tracemgrpacketcomplete
	#define GET_tracemgrpacketcomplete(fl)  CAL_CMGETAPI( "tracemgrpacketcomplete" ) 
	#define CAL_tracemgrpacketcomplete  tracemgrpacketcomplete
	#define CHK_tracemgrpacketcomplete  TRUE
	#define EXP_tracemgrpacketcomplete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketcomplete", (RTS_UINTPTR)tracemgrpacketcomplete, 1, 0x77ED2847, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketcomplete  PFTRACEMGRPACKETCOMPLETE_IEC pftracemgrpacketcomplete;
	#define EXT_tracemgrpacketcomplete  extern PFTRACEMGRPACKETCOMPLETE_IEC pftracemgrpacketcomplete;
	#define GET_tracemgrpacketcomplete(fl)  s_pfCMGetAPI2( "tracemgrpacketcomplete", (RTS_VOID_FCTPTR *)&pftracemgrpacketcomplete, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x77ED2847, 0x03050B00)
	#define CAL_tracemgrpacketcomplete  pftracemgrpacketcomplete
	#define CHK_tracemgrpacketcomplete  (pftracemgrpacketcomplete != NULL)
	#define EXP_tracemgrpacketcomplete   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketcomplete", (RTS_UINTPTR)tracemgrpacketcomplete, 1, 0x77ED2847, 0x03050B00) 
#endif


/**
 * Creates a new trace packet.  The returned handle must be deleted with
 * TraceMgrPacketDelete when the packet is no longer needed.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *  - ERR_PARAMETER if pConfiguration.pszName is 0
 *  - ERR_DUPLICATE if a packet with the given name already exists
 *  - ERR_NOMEMORY if the available memory is not sufficient to create the packet
 */
typedef struct tagtracemgrpacketcreate_struct
{
	TracePacketConfiguration *pConfiguration;	/* VAR_IN_OUT */	/* The trace packet configuration (in) */
	RTS_IEC_RESULT *pResult;			/* VAR_IN_OUT */	/* The result code (out) */
	RTS_IEC_HANDLE TraceMgrPacketCreate;	/* VAR_OUTPUT */	/* The trace packet handle or RTS_INVALID_HANDLE on failure */
} tracemgrpacketcreate_struct;

void CDECL CDECL_EXT tracemgrpacketcreate(tracemgrpacketcreate_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETCREATE_IEC) (tracemgrpacketcreate_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETCREATE_NOTIMPLEMENTED)
	#define USE_tracemgrpacketcreate
	#define EXT_tracemgrpacketcreate
	#define GET_tracemgrpacketcreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketcreate(p0) 
	#define CHK_tracemgrpacketcreate  FALSE
	#define EXP_tracemgrpacketcreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketcreate
	#define EXT_tracemgrpacketcreate
	#define GET_tracemgrpacketcreate(fl)  CAL_CMGETAPI( "tracemgrpacketcreate" ) 
	#define CAL_tracemgrpacketcreate  tracemgrpacketcreate
	#define CHK_tracemgrpacketcreate  TRUE
	#define EXP_tracemgrpacketcreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketcreate", (RTS_UINTPTR)tracemgrpacketcreate, 1, RTSITF_GET_SIGNATURE(0, 0x9F6D0ED7), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketcreate
	#define EXT_tracemgrpacketcreate
	#define GET_tracemgrpacketcreate(fl)  CAL_CMGETAPI( "tracemgrpacketcreate" ) 
	#define CAL_tracemgrpacketcreate  tracemgrpacketcreate
	#define CHK_tracemgrpacketcreate  TRUE
	#define EXP_tracemgrpacketcreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketcreate", (RTS_UINTPTR)tracemgrpacketcreate, 1, RTSITF_GET_SIGNATURE(0, 0x9F6D0ED7), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketcreate
	#define EXT_CmpTraceMgrtracemgrpacketcreate
	#define GET_CmpTraceMgrtracemgrpacketcreate  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketcreate  tracemgrpacketcreate
	#define CHK_CmpTraceMgrtracemgrpacketcreate  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketcreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketcreate", (RTS_UINTPTR)tracemgrpacketcreate, 1, RTSITF_GET_SIGNATURE(0, 0x9F6D0ED7), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketcreate
	#define EXT_tracemgrpacketcreate
	#define GET_tracemgrpacketcreate(fl)  CAL_CMGETAPI( "tracemgrpacketcreate" ) 
	#define CAL_tracemgrpacketcreate  tracemgrpacketcreate
	#define CHK_tracemgrpacketcreate  TRUE
	#define EXP_tracemgrpacketcreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketcreate", (RTS_UINTPTR)tracemgrpacketcreate, 1, RTSITF_GET_SIGNATURE(0, 0x9F6D0ED7), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketcreate  PFTRACEMGRPACKETCREATE_IEC pftracemgrpacketcreate;
	#define EXT_tracemgrpacketcreate  extern PFTRACEMGRPACKETCREATE_IEC pftracemgrpacketcreate;
	#define GET_tracemgrpacketcreate(fl)  s_pfCMGetAPI2( "tracemgrpacketcreate", (RTS_VOID_FCTPTR *)&pftracemgrpacketcreate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x9F6D0ED7), 0x03050B00)
	#define CAL_tracemgrpacketcreate  pftracemgrpacketcreate
	#define CHK_tracemgrpacketcreate  (pftracemgrpacketcreate != NULL)
	#define EXP_tracemgrpacketcreate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketcreate", (RTS_UINTPTR)tracemgrpacketcreate, 1, RTSITF_GET_SIGNATURE(0, 0x9F6D0ED7), 0x03050B00) 
#endif


/**
 * Deletes an existing handle.  The handle must have been created with
 * TraceMgrPacketCreate.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid packet handle
 */
typedef struct tagtracemgrpacketdelete_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_RESULT TraceMgrPacketDelete;	/* VAR_OUTPUT */	/* The result code */
} tracemgrpacketdelete_struct;

void CDECL CDECL_EXT tracemgrpacketdelete(tracemgrpacketdelete_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETDELETE_IEC) (tracemgrpacketdelete_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETDELETE_NOTIMPLEMENTED)
	#define USE_tracemgrpacketdelete
	#define EXT_tracemgrpacketdelete
	#define GET_tracemgrpacketdelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketdelete(p0) 
	#define CHK_tracemgrpacketdelete  FALSE
	#define EXP_tracemgrpacketdelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketdelete
	#define EXT_tracemgrpacketdelete
	#define GET_tracemgrpacketdelete(fl)  CAL_CMGETAPI( "tracemgrpacketdelete" ) 
	#define CAL_tracemgrpacketdelete  tracemgrpacketdelete
	#define CHK_tracemgrpacketdelete  TRUE
	#define EXP_tracemgrpacketdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketdelete", (RTS_UINTPTR)tracemgrpacketdelete, 1, 0x0BCF729C, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketdelete
	#define EXT_tracemgrpacketdelete
	#define GET_tracemgrpacketdelete(fl)  CAL_CMGETAPI( "tracemgrpacketdelete" ) 
	#define CAL_tracemgrpacketdelete  tracemgrpacketdelete
	#define CHK_tracemgrpacketdelete  TRUE
	#define EXP_tracemgrpacketdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketdelete", (RTS_UINTPTR)tracemgrpacketdelete, 1, 0x0BCF729C, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketdelete
	#define EXT_CmpTraceMgrtracemgrpacketdelete
	#define GET_CmpTraceMgrtracemgrpacketdelete  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketdelete  tracemgrpacketdelete
	#define CHK_CmpTraceMgrtracemgrpacketdelete  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketdelete", (RTS_UINTPTR)tracemgrpacketdelete, 1, 0x0BCF729C, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketdelete
	#define EXT_tracemgrpacketdelete
	#define GET_tracemgrpacketdelete(fl)  CAL_CMGETAPI( "tracemgrpacketdelete" ) 
	#define CAL_tracemgrpacketdelete  tracemgrpacketdelete
	#define CHK_tracemgrpacketdelete  TRUE
	#define EXP_tracemgrpacketdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketdelete", (RTS_UINTPTR)tracemgrpacketdelete, 1, 0x0BCF729C, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketdelete  PFTRACEMGRPACKETDELETE_IEC pftracemgrpacketdelete;
	#define EXT_tracemgrpacketdelete  extern PFTRACEMGRPACKETDELETE_IEC pftracemgrpacketdelete;
	#define GET_tracemgrpacketdelete(fl)  s_pfCMGetAPI2( "tracemgrpacketdelete", (RTS_VOID_FCTPTR *)&pftracemgrpacketdelete, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0BCF729C, 0x03050B00)
	#define CAL_tracemgrpacketdelete  pftracemgrpacketdelete
	#define CHK_tracemgrpacketdelete  (pftracemgrpacketdelete != NULL)
	#define EXP_tracemgrpacketdelete   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketdelete", (RTS_UINTPTR)tracemgrpacketdelete, 1, 0x0BCF729C, 0x03050B00) 
#endif


/**
 * Disables a trace packet.  Does nothing if the trace packet is
 * disabled.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid packet handle
 */
typedef struct tagtracemgrpacketdisable_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_RESULT TraceMgrPacketDisable;	/* VAR_OUTPUT */	/* The result code */
} tracemgrpacketdisable_struct;

void CDECL CDECL_EXT tracemgrpacketdisable(tracemgrpacketdisable_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETDISABLE_IEC) (tracemgrpacketdisable_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETDISABLE_NOTIMPLEMENTED)
	#define USE_tracemgrpacketdisable
	#define EXT_tracemgrpacketdisable
	#define GET_tracemgrpacketdisable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketdisable(p0) 
	#define CHK_tracemgrpacketdisable  FALSE
	#define EXP_tracemgrpacketdisable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketdisable
	#define EXT_tracemgrpacketdisable
	#define GET_tracemgrpacketdisable(fl)  CAL_CMGETAPI( "tracemgrpacketdisable" ) 
	#define CAL_tracemgrpacketdisable  tracemgrpacketdisable
	#define CHK_tracemgrpacketdisable  TRUE
	#define EXP_tracemgrpacketdisable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketdisable", (RTS_UINTPTR)tracemgrpacketdisable, 1, 0x05DBBAFD, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketdisable
	#define EXT_tracemgrpacketdisable
	#define GET_tracemgrpacketdisable(fl)  CAL_CMGETAPI( "tracemgrpacketdisable" ) 
	#define CAL_tracemgrpacketdisable  tracemgrpacketdisable
	#define CHK_tracemgrpacketdisable  TRUE
	#define EXP_tracemgrpacketdisable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketdisable", (RTS_UINTPTR)tracemgrpacketdisable, 1, 0x05DBBAFD, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketdisable
	#define EXT_CmpTraceMgrtracemgrpacketdisable
	#define GET_CmpTraceMgrtracemgrpacketdisable  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketdisable  tracemgrpacketdisable
	#define CHK_CmpTraceMgrtracemgrpacketdisable  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketdisable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketdisable", (RTS_UINTPTR)tracemgrpacketdisable, 1, 0x05DBBAFD, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketdisable
	#define EXT_tracemgrpacketdisable
	#define GET_tracemgrpacketdisable(fl)  CAL_CMGETAPI( "tracemgrpacketdisable" ) 
	#define CAL_tracemgrpacketdisable  tracemgrpacketdisable
	#define CHK_tracemgrpacketdisable  TRUE
	#define EXP_tracemgrpacketdisable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketdisable", (RTS_UINTPTR)tracemgrpacketdisable, 1, 0x05DBBAFD, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketdisable  PFTRACEMGRPACKETDISABLE_IEC pftracemgrpacketdisable;
	#define EXT_tracemgrpacketdisable  extern PFTRACEMGRPACKETDISABLE_IEC pftracemgrpacketdisable;
	#define GET_tracemgrpacketdisable(fl)  s_pfCMGetAPI2( "tracemgrpacketdisable", (RTS_VOID_FCTPTR *)&pftracemgrpacketdisable, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x05DBBAFD, 0x03050B00)
	#define CAL_tracemgrpacketdisable  pftracemgrpacketdisable
	#define CHK_tracemgrpacketdisable  (pftracemgrpacketdisable != NULL)
	#define EXP_tracemgrpacketdisable   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketdisable", (RTS_UINTPTR)tracemgrpacketdisable, 1, 0x05DBBAFD, 0x03050B00) 
#endif


/**
 * Disables the trigger of a trace packet.
 * 
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid packet handle
 */
typedef struct tagtracemgrpacketdisabletrigger_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_RESULT TraceMgrPacketDisableTrigger;	/* VAR_OUTPUT */	/* The result code */
} tracemgrpacketdisabletrigger_struct;

void CDECL CDECL_EXT tracemgrpacketdisabletrigger(tracemgrpacketdisabletrigger_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETDISABLETRIGGER_IEC) (tracemgrpacketdisabletrigger_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETDISABLETRIGGER_NOTIMPLEMENTED)
	#define USE_tracemgrpacketdisabletrigger
	#define EXT_tracemgrpacketdisabletrigger
	#define GET_tracemgrpacketdisabletrigger(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketdisabletrigger(p0) 
	#define CHK_tracemgrpacketdisabletrigger  FALSE
	#define EXP_tracemgrpacketdisabletrigger  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketdisabletrigger
	#define EXT_tracemgrpacketdisabletrigger
	#define GET_tracemgrpacketdisabletrigger(fl)  CAL_CMGETAPI( "tracemgrpacketdisabletrigger" ) 
	#define CAL_tracemgrpacketdisabletrigger  tracemgrpacketdisabletrigger
	#define CHK_tracemgrpacketdisabletrigger  TRUE
	#define EXP_tracemgrpacketdisabletrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketdisabletrigger", (RTS_UINTPTR)tracemgrpacketdisabletrigger, 1, 0x293C8EA4, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketdisabletrigger
	#define EXT_tracemgrpacketdisabletrigger
	#define GET_tracemgrpacketdisabletrigger(fl)  CAL_CMGETAPI( "tracemgrpacketdisabletrigger" ) 
	#define CAL_tracemgrpacketdisabletrigger  tracemgrpacketdisabletrigger
	#define CHK_tracemgrpacketdisabletrigger  TRUE
	#define EXP_tracemgrpacketdisabletrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketdisabletrigger", (RTS_UINTPTR)tracemgrpacketdisabletrigger, 1, 0x293C8EA4, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketdisabletrigger
	#define EXT_CmpTraceMgrtracemgrpacketdisabletrigger
	#define GET_CmpTraceMgrtracemgrpacketdisabletrigger  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketdisabletrigger  tracemgrpacketdisabletrigger
	#define CHK_CmpTraceMgrtracemgrpacketdisabletrigger  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketdisabletrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketdisabletrigger", (RTS_UINTPTR)tracemgrpacketdisabletrigger, 1, 0x293C8EA4, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketdisabletrigger
	#define EXT_tracemgrpacketdisabletrigger
	#define GET_tracemgrpacketdisabletrigger(fl)  CAL_CMGETAPI( "tracemgrpacketdisabletrigger" ) 
	#define CAL_tracemgrpacketdisabletrigger  tracemgrpacketdisabletrigger
	#define CHK_tracemgrpacketdisabletrigger  TRUE
	#define EXP_tracemgrpacketdisabletrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketdisabletrigger", (RTS_UINTPTR)tracemgrpacketdisabletrigger, 1, 0x293C8EA4, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketdisabletrigger  PFTRACEMGRPACKETDISABLETRIGGER_IEC pftracemgrpacketdisabletrigger;
	#define EXT_tracemgrpacketdisabletrigger  extern PFTRACEMGRPACKETDISABLETRIGGER_IEC pftracemgrpacketdisabletrigger;
	#define GET_tracemgrpacketdisabletrigger(fl)  s_pfCMGetAPI2( "tracemgrpacketdisabletrigger", (RTS_VOID_FCTPTR *)&pftracemgrpacketdisabletrigger, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x293C8EA4, 0x03050B00)
	#define CAL_tracemgrpacketdisabletrigger  pftracemgrpacketdisabletrigger
	#define CHK_tracemgrpacketdisabletrigger  (pftracemgrpacketdisabletrigger != NULL)
	#define EXP_tracemgrpacketdisabletrigger   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketdisabletrigger", (RTS_UINTPTR)tracemgrpacketdisabletrigger, 1, 0x293C8EA4, 0x03050B00) 
#endif


/**
 * Enables a trace packet.  Does nothing if the trace packet is
 * enabled.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid packet handle
 */
typedef struct tagtracemgrpacketenable_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_RESULT TraceMgrPacketEnable;	/* VAR_OUTPUT */	/* The result code */
} tracemgrpacketenable_struct;

void CDECL CDECL_EXT tracemgrpacketenable(tracemgrpacketenable_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETENABLE_IEC) (tracemgrpacketenable_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETENABLE_NOTIMPLEMENTED)
	#define USE_tracemgrpacketenable
	#define EXT_tracemgrpacketenable
	#define GET_tracemgrpacketenable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketenable(p0) 
	#define CHK_tracemgrpacketenable  FALSE
	#define EXP_tracemgrpacketenable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketenable
	#define EXT_tracemgrpacketenable
	#define GET_tracemgrpacketenable(fl)  CAL_CMGETAPI( "tracemgrpacketenable" ) 
	#define CAL_tracemgrpacketenable  tracemgrpacketenable
	#define CHK_tracemgrpacketenable  TRUE
	#define EXP_tracemgrpacketenable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketenable", (RTS_UINTPTR)tracemgrpacketenable, 1, 0x3B8A1A22, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketenable
	#define EXT_tracemgrpacketenable
	#define GET_tracemgrpacketenable(fl)  CAL_CMGETAPI( "tracemgrpacketenable" ) 
	#define CAL_tracemgrpacketenable  tracemgrpacketenable
	#define CHK_tracemgrpacketenable  TRUE
	#define EXP_tracemgrpacketenable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketenable", (RTS_UINTPTR)tracemgrpacketenable, 1, 0x3B8A1A22, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketenable
	#define EXT_CmpTraceMgrtracemgrpacketenable
	#define GET_CmpTraceMgrtracemgrpacketenable  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketenable  tracemgrpacketenable
	#define CHK_CmpTraceMgrtracemgrpacketenable  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketenable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketenable", (RTS_UINTPTR)tracemgrpacketenable, 1, 0x3B8A1A22, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketenable
	#define EXT_tracemgrpacketenable
	#define GET_tracemgrpacketenable(fl)  CAL_CMGETAPI( "tracemgrpacketenable" ) 
	#define CAL_tracemgrpacketenable  tracemgrpacketenable
	#define CHK_tracemgrpacketenable  TRUE
	#define EXP_tracemgrpacketenable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketenable", (RTS_UINTPTR)tracemgrpacketenable, 1, 0x3B8A1A22, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketenable  PFTRACEMGRPACKETENABLE_IEC pftracemgrpacketenable;
	#define EXT_tracemgrpacketenable  extern PFTRACEMGRPACKETENABLE_IEC pftracemgrpacketenable;
	#define GET_tracemgrpacketenable(fl)  s_pfCMGetAPI2( "tracemgrpacketenable", (RTS_VOID_FCTPTR *)&pftracemgrpacketenable, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x3B8A1A22, 0x03050B00)
	#define CAL_tracemgrpacketenable  pftracemgrpacketenable
	#define CHK_tracemgrpacketenable  (pftracemgrpacketenable != NULL)
	#define EXP_tracemgrpacketenable   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketenable", (RTS_UINTPTR)tracemgrpacketenable, 1, 0x3B8A1A22, 0x03050B00) 
#endif


/**
 * Enables the trigger of a trace packet.
 * 
 * .. note:: This function should be called if the trigger is currently disabled.
 *    If the trigger has already fired, call |TraceMgrPacketResetTrigger|
 *    to reset the trigger, instead.
 * 
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid packet handle
 */
typedef struct tagtracemgrpacketenabletrigger_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_RESULT TraceMgrPacketEnableTrigger;	/* VAR_OUTPUT */	/* The result code */
} tracemgrpacketenabletrigger_struct;

void CDECL CDECL_EXT tracemgrpacketenabletrigger(tracemgrpacketenabletrigger_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETENABLETRIGGER_IEC) (tracemgrpacketenabletrigger_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETENABLETRIGGER_NOTIMPLEMENTED)
	#define USE_tracemgrpacketenabletrigger
	#define EXT_tracemgrpacketenabletrigger
	#define GET_tracemgrpacketenabletrigger(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketenabletrigger(p0) 
	#define CHK_tracemgrpacketenabletrigger  FALSE
	#define EXP_tracemgrpacketenabletrigger  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketenabletrigger
	#define EXT_tracemgrpacketenabletrigger
	#define GET_tracemgrpacketenabletrigger(fl)  CAL_CMGETAPI( "tracemgrpacketenabletrigger" ) 
	#define CAL_tracemgrpacketenabletrigger  tracemgrpacketenabletrigger
	#define CHK_tracemgrpacketenabletrigger  TRUE
	#define EXP_tracemgrpacketenabletrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketenabletrigger", (RTS_UINTPTR)tracemgrpacketenabletrigger, 1, 0x9E0738EB, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketenabletrigger
	#define EXT_tracemgrpacketenabletrigger
	#define GET_tracemgrpacketenabletrigger(fl)  CAL_CMGETAPI( "tracemgrpacketenabletrigger" ) 
	#define CAL_tracemgrpacketenabletrigger  tracemgrpacketenabletrigger
	#define CHK_tracemgrpacketenabletrigger  TRUE
	#define EXP_tracemgrpacketenabletrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketenabletrigger", (RTS_UINTPTR)tracemgrpacketenabletrigger, 1, 0x9E0738EB, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketenabletrigger
	#define EXT_CmpTraceMgrtracemgrpacketenabletrigger
	#define GET_CmpTraceMgrtracemgrpacketenabletrigger  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketenabletrigger  tracemgrpacketenabletrigger
	#define CHK_CmpTraceMgrtracemgrpacketenabletrigger  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketenabletrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketenabletrigger", (RTS_UINTPTR)tracemgrpacketenabletrigger, 1, 0x9E0738EB, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketenabletrigger
	#define EXT_tracemgrpacketenabletrigger
	#define GET_tracemgrpacketenabletrigger(fl)  CAL_CMGETAPI( "tracemgrpacketenabletrigger" ) 
	#define CAL_tracemgrpacketenabletrigger  tracemgrpacketenabletrigger
	#define CHK_tracemgrpacketenabletrigger  TRUE
	#define EXP_tracemgrpacketenabletrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketenabletrigger", (RTS_UINTPTR)tracemgrpacketenabletrigger, 1, 0x9E0738EB, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketenabletrigger  PFTRACEMGRPACKETENABLETRIGGER_IEC pftracemgrpacketenabletrigger;
	#define EXT_tracemgrpacketenabletrigger  extern PFTRACEMGRPACKETENABLETRIGGER_IEC pftracemgrpacketenabletrigger;
	#define GET_tracemgrpacketenabletrigger(fl)  s_pfCMGetAPI2( "tracemgrpacketenabletrigger", (RTS_VOID_FCTPTR *)&pftracemgrpacketenabletrigger, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x9E0738EB, 0x03050B00)
	#define CAL_tracemgrpacketenabletrigger  pftracemgrpacketenabletrigger
	#define CHK_tracemgrpacketenabletrigger  (pftracemgrpacketenabletrigger != NULL)
	#define EXP_tracemgrpacketenabletrigger   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketenabletrigger", (RTS_UINTPTR)tracemgrpacketenabletrigger, 1, 0x9E0738EB, 0x03050B00) 
#endif


/**
 * Returns the absolute start time of a trace packet or 0 if trace packet has not
 * been started yet.
 *
 * .. note:: The start time is the time when the packet was started for the first time.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid handle
 */
typedef struct tagtracemgrpacketgetabsolutestarttime_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_ULINT *pStartTime;			/* VAR_IN_OUT */	/* The start time (out) */
	RTS_IEC_RESULT TraceMgrPacketGetAbsoluteStartTime;	/* VAR_OUTPUT */	/* The result code */
} tracemgrpacketgetabsolutestarttime_struct;

void CDECL CDECL_EXT tracemgrpacketgetabsolutestarttime(tracemgrpacketgetabsolutestarttime_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETGETABSOLUTESTARTTIME_IEC) (tracemgrpacketgetabsolutestarttime_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETGETABSOLUTESTARTTIME_NOTIMPLEMENTED)
	#define USE_tracemgrpacketgetabsolutestarttime
	#define EXT_tracemgrpacketgetabsolutestarttime
	#define GET_tracemgrpacketgetabsolutestarttime(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketgetabsolutestarttime(p0) 
	#define CHK_tracemgrpacketgetabsolutestarttime  FALSE
	#define EXP_tracemgrpacketgetabsolutestarttime  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketgetabsolutestarttime
	#define EXT_tracemgrpacketgetabsolutestarttime
	#define GET_tracemgrpacketgetabsolutestarttime(fl)  CAL_CMGETAPI( "tracemgrpacketgetabsolutestarttime" ) 
	#define CAL_tracemgrpacketgetabsolutestarttime  tracemgrpacketgetabsolutestarttime
	#define CHK_tracemgrpacketgetabsolutestarttime  TRUE
	#define EXP_tracemgrpacketgetabsolutestarttime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetabsolutestarttime", (RTS_UINTPTR)tracemgrpacketgetabsolutestarttime, 1, 0x4D6D7E87, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketgetabsolutestarttime
	#define EXT_tracemgrpacketgetabsolutestarttime
	#define GET_tracemgrpacketgetabsolutestarttime(fl)  CAL_CMGETAPI( "tracemgrpacketgetabsolutestarttime" ) 
	#define CAL_tracemgrpacketgetabsolutestarttime  tracemgrpacketgetabsolutestarttime
	#define CHK_tracemgrpacketgetabsolutestarttime  TRUE
	#define EXP_tracemgrpacketgetabsolutestarttime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetabsolutestarttime", (RTS_UINTPTR)tracemgrpacketgetabsolutestarttime, 1, 0x4D6D7E87, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketgetabsolutestarttime
	#define EXT_CmpTraceMgrtracemgrpacketgetabsolutestarttime
	#define GET_CmpTraceMgrtracemgrpacketgetabsolutestarttime  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketgetabsolutestarttime  tracemgrpacketgetabsolutestarttime
	#define CHK_CmpTraceMgrtracemgrpacketgetabsolutestarttime  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketgetabsolutestarttime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetabsolutestarttime", (RTS_UINTPTR)tracemgrpacketgetabsolutestarttime, 1, 0x4D6D7E87, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketgetabsolutestarttime
	#define EXT_tracemgrpacketgetabsolutestarttime
	#define GET_tracemgrpacketgetabsolutestarttime(fl)  CAL_CMGETAPI( "tracemgrpacketgetabsolutestarttime" ) 
	#define CAL_tracemgrpacketgetabsolutestarttime  tracemgrpacketgetabsolutestarttime
	#define CHK_tracemgrpacketgetabsolutestarttime  TRUE
	#define EXP_tracemgrpacketgetabsolutestarttime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetabsolutestarttime", (RTS_UINTPTR)tracemgrpacketgetabsolutestarttime, 1, 0x4D6D7E87, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketgetabsolutestarttime  PFTRACEMGRPACKETGETABSOLUTESTARTTIME_IEC pftracemgrpacketgetabsolutestarttime;
	#define EXT_tracemgrpacketgetabsolutestarttime  extern PFTRACEMGRPACKETGETABSOLUTESTARTTIME_IEC pftracemgrpacketgetabsolutestarttime;
	#define GET_tracemgrpacketgetabsolutestarttime(fl)  s_pfCMGetAPI2( "tracemgrpacketgetabsolutestarttime", (RTS_VOID_FCTPTR *)&pftracemgrpacketgetabsolutestarttime, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x4D6D7E87, 0x03050B00)
	#define CAL_tracemgrpacketgetabsolutestarttime  pftracemgrpacketgetabsolutestarttime
	#define CHK_tracemgrpacketgetabsolutestarttime  (pftracemgrpacketgetabsolutestarttime != NULL)
	#define EXP_tracemgrpacketgetabsolutestarttime   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetabsolutestarttime", (RTS_UINTPTR)tracemgrpacketgetabsolutestarttime, 1, 0x4D6D7E87, 0x03050B00) 
#endif


/**
 * Returns the timestamp of a trace packet's last modification.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid packet handle
 */
typedef struct tagtracemgrpacketgetchangetimestamp_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_DWORD *pdwTimestamp;		/* VAR_IN_OUT */	/* The modification timestamp (out) */
	RTS_IEC_RESULT TraceMgrPacketGetChangeTimestamp;	/* VAR_OUTPUT */	/* The result code */
} tracemgrpacketgetchangetimestamp_struct;

void CDECL CDECL_EXT tracemgrpacketgetchangetimestamp(tracemgrpacketgetchangetimestamp_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETGETCHANGETIMESTAMP_IEC) (tracemgrpacketgetchangetimestamp_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETGETCHANGETIMESTAMP_NOTIMPLEMENTED)
	#define USE_tracemgrpacketgetchangetimestamp
	#define EXT_tracemgrpacketgetchangetimestamp
	#define GET_tracemgrpacketgetchangetimestamp(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketgetchangetimestamp(p0) 
	#define CHK_tracemgrpacketgetchangetimestamp  FALSE
	#define EXP_tracemgrpacketgetchangetimestamp  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketgetchangetimestamp
	#define EXT_tracemgrpacketgetchangetimestamp
	#define GET_tracemgrpacketgetchangetimestamp(fl)  CAL_CMGETAPI( "tracemgrpacketgetchangetimestamp" ) 
	#define CAL_tracemgrpacketgetchangetimestamp  tracemgrpacketgetchangetimestamp
	#define CHK_tracemgrpacketgetchangetimestamp  TRUE
	#define EXP_tracemgrpacketgetchangetimestamp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetchangetimestamp", (RTS_UINTPTR)tracemgrpacketgetchangetimestamp, 1, 0x47F49777, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketgetchangetimestamp
	#define EXT_tracemgrpacketgetchangetimestamp
	#define GET_tracemgrpacketgetchangetimestamp(fl)  CAL_CMGETAPI( "tracemgrpacketgetchangetimestamp" ) 
	#define CAL_tracemgrpacketgetchangetimestamp  tracemgrpacketgetchangetimestamp
	#define CHK_tracemgrpacketgetchangetimestamp  TRUE
	#define EXP_tracemgrpacketgetchangetimestamp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetchangetimestamp", (RTS_UINTPTR)tracemgrpacketgetchangetimestamp, 1, 0x47F49777, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketgetchangetimestamp
	#define EXT_CmpTraceMgrtracemgrpacketgetchangetimestamp
	#define GET_CmpTraceMgrtracemgrpacketgetchangetimestamp  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketgetchangetimestamp  tracemgrpacketgetchangetimestamp
	#define CHK_CmpTraceMgrtracemgrpacketgetchangetimestamp  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketgetchangetimestamp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetchangetimestamp", (RTS_UINTPTR)tracemgrpacketgetchangetimestamp, 1, 0x47F49777, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketgetchangetimestamp
	#define EXT_tracemgrpacketgetchangetimestamp
	#define GET_tracemgrpacketgetchangetimestamp(fl)  CAL_CMGETAPI( "tracemgrpacketgetchangetimestamp" ) 
	#define CAL_tracemgrpacketgetchangetimestamp  tracemgrpacketgetchangetimestamp
	#define CHK_tracemgrpacketgetchangetimestamp  TRUE
	#define EXP_tracemgrpacketgetchangetimestamp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetchangetimestamp", (RTS_UINTPTR)tracemgrpacketgetchangetimestamp, 1, 0x47F49777, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketgetchangetimestamp  PFTRACEMGRPACKETGETCHANGETIMESTAMP_IEC pftracemgrpacketgetchangetimestamp;
	#define EXT_tracemgrpacketgetchangetimestamp  extern PFTRACEMGRPACKETGETCHANGETIMESTAMP_IEC pftracemgrpacketgetchangetimestamp;
	#define GET_tracemgrpacketgetchangetimestamp(fl)  s_pfCMGetAPI2( "tracemgrpacketgetchangetimestamp", (RTS_VOID_FCTPTR *)&pftracemgrpacketgetchangetimestamp, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x47F49777, 0x03050B00)
	#define CAL_tracemgrpacketgetchangetimestamp  pftracemgrpacketgetchangetimestamp
	#define CHK_tracemgrpacketgetchangetimestamp  (pftracemgrpacketgetchangetimestamp != NULL)
	#define EXP_tracemgrpacketgetchangetimestamp   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetchangetimestamp", (RTS_UINTPTR)tracemgrpacketgetchangetimestamp, 1, 0x47F49777, 0x03050B00) 
#endif


/**
 * Queries the configuration of a trace packet.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid handle
 */
typedef struct tagtracemgrpacketgetconfig_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	TracePacketConfiguration *pConfiguration;	/* VAR_IN_OUT */	/* The packet configuration (out) */
	RTS_IEC_RESULT TraceMgrPacketGetConfig;	/* VAR_OUTPUT */	/* The result code */
} tracemgrpacketgetconfig_struct;

void CDECL CDECL_EXT tracemgrpacketgetconfig(tracemgrpacketgetconfig_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETGETCONFIG_IEC) (tracemgrpacketgetconfig_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETGETCONFIG_NOTIMPLEMENTED)
	#define USE_tracemgrpacketgetconfig
	#define EXT_tracemgrpacketgetconfig
	#define GET_tracemgrpacketgetconfig(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketgetconfig(p0) 
	#define CHK_tracemgrpacketgetconfig  FALSE
	#define EXP_tracemgrpacketgetconfig  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketgetconfig
	#define EXT_tracemgrpacketgetconfig
	#define GET_tracemgrpacketgetconfig(fl)  CAL_CMGETAPI( "tracemgrpacketgetconfig" ) 
	#define CAL_tracemgrpacketgetconfig  tracemgrpacketgetconfig
	#define CHK_tracemgrpacketgetconfig  TRUE
	#define EXP_tracemgrpacketgetconfig  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetconfig", (RTS_UINTPTR)tracemgrpacketgetconfig, 1, RTSITF_GET_SIGNATURE(0, 0xF96CF7C8), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketgetconfig
	#define EXT_tracemgrpacketgetconfig
	#define GET_tracemgrpacketgetconfig(fl)  CAL_CMGETAPI( "tracemgrpacketgetconfig" ) 
	#define CAL_tracemgrpacketgetconfig  tracemgrpacketgetconfig
	#define CHK_tracemgrpacketgetconfig  TRUE
	#define EXP_tracemgrpacketgetconfig  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetconfig", (RTS_UINTPTR)tracemgrpacketgetconfig, 1, RTSITF_GET_SIGNATURE(0, 0xF96CF7C8), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketgetconfig
	#define EXT_CmpTraceMgrtracemgrpacketgetconfig
	#define GET_CmpTraceMgrtracemgrpacketgetconfig  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketgetconfig  tracemgrpacketgetconfig
	#define CHK_CmpTraceMgrtracemgrpacketgetconfig  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketgetconfig  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetconfig", (RTS_UINTPTR)tracemgrpacketgetconfig, 1, RTSITF_GET_SIGNATURE(0, 0xF96CF7C8), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketgetconfig
	#define EXT_tracemgrpacketgetconfig
	#define GET_tracemgrpacketgetconfig(fl)  CAL_CMGETAPI( "tracemgrpacketgetconfig" ) 
	#define CAL_tracemgrpacketgetconfig  tracemgrpacketgetconfig
	#define CHK_tracemgrpacketgetconfig  TRUE
	#define EXP_tracemgrpacketgetconfig  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetconfig", (RTS_UINTPTR)tracemgrpacketgetconfig, 1, RTSITF_GET_SIGNATURE(0, 0xF96CF7C8), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketgetconfig  PFTRACEMGRPACKETGETCONFIG_IEC pftracemgrpacketgetconfig;
	#define EXT_tracemgrpacketgetconfig  extern PFTRACEMGRPACKETGETCONFIG_IEC pftracemgrpacketgetconfig;
	#define GET_tracemgrpacketgetconfig(fl)  s_pfCMGetAPI2( "tracemgrpacketgetconfig", (RTS_VOID_FCTPTR *)&pftracemgrpacketgetconfig, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xF96CF7C8), 0x03050B00)
	#define CAL_tracemgrpacketgetconfig  pftracemgrpacketgetconfig
	#define CHK_tracemgrpacketgetconfig  (pftracemgrpacketgetconfig != NULL)
	#define EXP_tracemgrpacketgetconfig   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetconfig", (RTS_UINTPTR)tracemgrpacketgetconfig, 1, RTSITF_GET_SIGNATURE(0, 0xF96CF7C8), 0x03050B00) 
#endif


/**
 * Returns the first trace packet.
 * This function can be used together with |TraceMgrPacketGetNext| to iterate
 * through all trace packets.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_NO_OBJECT if there is no trace packet
 */
typedef struct tagtracemgrpacketgetfirst_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_IN_OUT */	/* The result code (out) */
	RTS_IEC_HANDLE TraceMgrPacketGetFirst;	/* VAR_OUTPUT */	/* The packet handle or RTS_INVALID_HANDLE if there is no packet */
} tracemgrpacketgetfirst_struct;

void CDECL CDECL_EXT tracemgrpacketgetfirst(tracemgrpacketgetfirst_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETGETFIRST_IEC) (tracemgrpacketgetfirst_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETGETFIRST_NOTIMPLEMENTED)
	#define USE_tracemgrpacketgetfirst
	#define EXT_tracemgrpacketgetfirst
	#define GET_tracemgrpacketgetfirst(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketgetfirst(p0) 
	#define CHK_tracemgrpacketgetfirst  FALSE
	#define EXP_tracemgrpacketgetfirst  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketgetfirst
	#define EXT_tracemgrpacketgetfirst
	#define GET_tracemgrpacketgetfirst(fl)  CAL_CMGETAPI( "tracemgrpacketgetfirst" ) 
	#define CAL_tracemgrpacketgetfirst  tracemgrpacketgetfirst
	#define CHK_tracemgrpacketgetfirst  TRUE
	#define EXP_tracemgrpacketgetfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetfirst", (RTS_UINTPTR)tracemgrpacketgetfirst, 1, 0xA4D19325, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketgetfirst
	#define EXT_tracemgrpacketgetfirst
	#define GET_tracemgrpacketgetfirst(fl)  CAL_CMGETAPI( "tracemgrpacketgetfirst" ) 
	#define CAL_tracemgrpacketgetfirst  tracemgrpacketgetfirst
	#define CHK_tracemgrpacketgetfirst  TRUE
	#define EXP_tracemgrpacketgetfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetfirst", (RTS_UINTPTR)tracemgrpacketgetfirst, 1, 0xA4D19325, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketgetfirst
	#define EXT_CmpTraceMgrtracemgrpacketgetfirst
	#define GET_CmpTraceMgrtracemgrpacketgetfirst  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketgetfirst  tracemgrpacketgetfirst
	#define CHK_CmpTraceMgrtracemgrpacketgetfirst  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketgetfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetfirst", (RTS_UINTPTR)tracemgrpacketgetfirst, 1, 0xA4D19325, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketgetfirst
	#define EXT_tracemgrpacketgetfirst
	#define GET_tracemgrpacketgetfirst(fl)  CAL_CMGETAPI( "tracemgrpacketgetfirst" ) 
	#define CAL_tracemgrpacketgetfirst  tracemgrpacketgetfirst
	#define CHK_tracemgrpacketgetfirst  TRUE
	#define EXP_tracemgrpacketgetfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetfirst", (RTS_UINTPTR)tracemgrpacketgetfirst, 1, 0xA4D19325, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketgetfirst  PFTRACEMGRPACKETGETFIRST_IEC pftracemgrpacketgetfirst;
	#define EXT_tracemgrpacketgetfirst  extern PFTRACEMGRPACKETGETFIRST_IEC pftracemgrpacketgetfirst;
	#define GET_tracemgrpacketgetfirst(fl)  s_pfCMGetAPI2( "tracemgrpacketgetfirst", (RTS_VOID_FCTPTR *)&pftracemgrpacketgetfirst, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xA4D19325, 0x03050B00)
	#define CAL_tracemgrpacketgetfirst  pftracemgrpacketgetfirst
	#define CHK_tracemgrpacketgetfirst  (pftracemgrpacketgetfirst != NULL)
	#define EXP_tracemgrpacketgetfirst   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetfirst", (RTS_UINTPTR)tracemgrpacketgetfirst, 1, 0xA4D19325, 0x03050B00) 
#endif


/**
 * Returns the next trace packet.
 * This function can be used together with |TraceMgrPacketGetFirst| to iterate
 * through all trace packets.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPrevPacket is not a valid handle
 *   - ERR_NO_OBJECT if hPrevPacket is the last trace packet
 */
typedef struct tagtracemgrpacketgetnext_struct
{
	RTS_IEC_HANDLE hPrevPacket;			/* VAR_INPUT */	/* The packet handle of the current trace packet */
	RTS_IEC_RESULT *pResult;			/* VAR_IN_OUT */	/* The result code */
	RTS_IEC_HANDLE TraceMgrPacketGetNext;	/* VAR_OUTPUT */	/* The packet handle or RTS_INVALID_HANDLE if there is no further packet */
} tracemgrpacketgetnext_struct;

void CDECL CDECL_EXT tracemgrpacketgetnext(tracemgrpacketgetnext_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETGETNEXT_IEC) (tracemgrpacketgetnext_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETGETNEXT_NOTIMPLEMENTED)
	#define USE_tracemgrpacketgetnext
	#define EXT_tracemgrpacketgetnext
	#define GET_tracemgrpacketgetnext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketgetnext(p0) 
	#define CHK_tracemgrpacketgetnext  FALSE
	#define EXP_tracemgrpacketgetnext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketgetnext
	#define EXT_tracemgrpacketgetnext
	#define GET_tracemgrpacketgetnext(fl)  CAL_CMGETAPI( "tracemgrpacketgetnext" ) 
	#define CAL_tracemgrpacketgetnext  tracemgrpacketgetnext
	#define CHK_tracemgrpacketgetnext  TRUE
	#define EXP_tracemgrpacketgetnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetnext", (RTS_UINTPTR)tracemgrpacketgetnext, 1, 0x1E3AD1B8, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketgetnext
	#define EXT_tracemgrpacketgetnext
	#define GET_tracemgrpacketgetnext(fl)  CAL_CMGETAPI( "tracemgrpacketgetnext" ) 
	#define CAL_tracemgrpacketgetnext  tracemgrpacketgetnext
	#define CHK_tracemgrpacketgetnext  TRUE
	#define EXP_tracemgrpacketgetnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetnext", (RTS_UINTPTR)tracemgrpacketgetnext, 1, 0x1E3AD1B8, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketgetnext
	#define EXT_CmpTraceMgrtracemgrpacketgetnext
	#define GET_CmpTraceMgrtracemgrpacketgetnext  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketgetnext  tracemgrpacketgetnext
	#define CHK_CmpTraceMgrtracemgrpacketgetnext  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketgetnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetnext", (RTS_UINTPTR)tracemgrpacketgetnext, 1, 0x1E3AD1B8, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketgetnext
	#define EXT_tracemgrpacketgetnext
	#define GET_tracemgrpacketgetnext(fl)  CAL_CMGETAPI( "tracemgrpacketgetnext" ) 
	#define CAL_tracemgrpacketgetnext  tracemgrpacketgetnext
	#define CHK_tracemgrpacketgetnext  TRUE
	#define EXP_tracemgrpacketgetnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetnext", (RTS_UINTPTR)tracemgrpacketgetnext, 1, 0x1E3AD1B8, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketgetnext  PFTRACEMGRPACKETGETNEXT_IEC pftracemgrpacketgetnext;
	#define EXT_tracemgrpacketgetnext  extern PFTRACEMGRPACKETGETNEXT_IEC pftracemgrpacketgetnext;
	#define GET_tracemgrpacketgetnext(fl)  s_pfCMGetAPI2( "tracemgrpacketgetnext", (RTS_VOID_FCTPTR *)&pftracemgrpacketgetnext, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x1E3AD1B8, 0x03050B00)
	#define CAL_tracemgrpacketgetnext  pftracemgrpacketgetnext
	#define CHK_tracemgrpacketgetnext  (pftracemgrpacketgetnext != NULL)
	#define EXP_tracemgrpacketgetnext   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetnext", (RTS_UINTPTR)tracemgrpacketgetnext, 1, 0x1E3AD1B8, 0x03050B00) 
#endif


/**
 * Returns the start time of a trace packet or 0 if trace packet has not
 * been started yet.
 *
 * .. note:: the start time is the time when the packet was started for the first time.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid handle
 */
typedef struct tagtracemgrpacketgetstarttime_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_ULINT *pStartTime;			/* VAR_IN_OUT */	/* The start time (out) */
	RTS_IEC_RESULT TraceMgrPacketGetStartTime;	/* VAR_OUTPUT */	/* The result code */
} tracemgrpacketgetstarttime_struct;

void CDECL CDECL_EXT tracemgrpacketgetstarttime(tracemgrpacketgetstarttime_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETGETSTARTTIME_IEC) (tracemgrpacketgetstarttime_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETGETSTARTTIME_NOTIMPLEMENTED)
	#define USE_tracemgrpacketgetstarttime
	#define EXT_tracemgrpacketgetstarttime
	#define GET_tracemgrpacketgetstarttime(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketgetstarttime(p0) 
	#define CHK_tracemgrpacketgetstarttime  FALSE
	#define EXP_tracemgrpacketgetstarttime  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketgetstarttime
	#define EXT_tracemgrpacketgetstarttime
	#define GET_tracemgrpacketgetstarttime(fl)  CAL_CMGETAPI( "tracemgrpacketgetstarttime" ) 
	#define CAL_tracemgrpacketgetstarttime  tracemgrpacketgetstarttime
	#define CHK_tracemgrpacketgetstarttime  TRUE
	#define EXP_tracemgrpacketgetstarttime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetstarttime", (RTS_UINTPTR)tracemgrpacketgetstarttime, 1, 0x8FC2D61B, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketgetstarttime
	#define EXT_tracemgrpacketgetstarttime
	#define GET_tracemgrpacketgetstarttime(fl)  CAL_CMGETAPI( "tracemgrpacketgetstarttime" ) 
	#define CAL_tracemgrpacketgetstarttime  tracemgrpacketgetstarttime
	#define CHK_tracemgrpacketgetstarttime  TRUE
	#define EXP_tracemgrpacketgetstarttime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetstarttime", (RTS_UINTPTR)tracemgrpacketgetstarttime, 1, 0x8FC2D61B, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketgetstarttime
	#define EXT_CmpTraceMgrtracemgrpacketgetstarttime
	#define GET_CmpTraceMgrtracemgrpacketgetstarttime  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketgetstarttime  tracemgrpacketgetstarttime
	#define CHK_CmpTraceMgrtracemgrpacketgetstarttime  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketgetstarttime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetstarttime", (RTS_UINTPTR)tracemgrpacketgetstarttime, 1, 0x8FC2D61B, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketgetstarttime
	#define EXT_tracemgrpacketgetstarttime
	#define GET_tracemgrpacketgetstarttime(fl)  CAL_CMGETAPI( "tracemgrpacketgetstarttime" ) 
	#define CAL_tracemgrpacketgetstarttime  tracemgrpacketgetstarttime
	#define CHK_tracemgrpacketgetstarttime  TRUE
	#define EXP_tracemgrpacketgetstarttime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetstarttime", (RTS_UINTPTR)tracemgrpacketgetstarttime, 1, 0x8FC2D61B, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketgetstarttime  PFTRACEMGRPACKETGETSTARTTIME_IEC pftracemgrpacketgetstarttime;
	#define EXT_tracemgrpacketgetstarttime  extern PFTRACEMGRPACKETGETSTARTTIME_IEC pftracemgrpacketgetstarttime;
	#define GET_tracemgrpacketgetstarttime(fl)  s_pfCMGetAPI2( "tracemgrpacketgetstarttime", (RTS_VOID_FCTPTR *)&pftracemgrpacketgetstarttime, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x8FC2D61B, 0x03050B00)
	#define CAL_tracemgrpacketgetstarttime  pftracemgrpacketgetstarttime
	#define CHK_tracemgrpacketgetstarttime  (pftracemgrpacketgetstarttime != NULL)
	#define EXP_tracemgrpacketgetstarttime   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetstarttime", (RTS_UINTPTR)tracemgrpacketgetstarttime, 1, 0x8FC2D61B, 0x03050B00) 
#endif


/**
 * Returns the state of a trace packet.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid packet handle
 */
typedef struct tagtracemgrpacketgetstate_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	TraceState *pState;					/* VAR_IN_OUT */	/* The packet state (out) */
	RTS_IEC_RESULT TraceMgrPacketGetState;	/* VAR_OUTPUT */	/* The result code */
} tracemgrpacketgetstate_struct;

void CDECL CDECL_EXT tracemgrpacketgetstate(tracemgrpacketgetstate_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETGETSTATE_IEC) (tracemgrpacketgetstate_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETGETSTATE_NOTIMPLEMENTED)
	#define USE_tracemgrpacketgetstate
	#define EXT_tracemgrpacketgetstate
	#define GET_tracemgrpacketgetstate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketgetstate(p0) 
	#define CHK_tracemgrpacketgetstate  FALSE
	#define EXP_tracemgrpacketgetstate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketgetstate
	#define EXT_tracemgrpacketgetstate
	#define GET_tracemgrpacketgetstate(fl)  CAL_CMGETAPI( "tracemgrpacketgetstate" ) 
	#define CAL_tracemgrpacketgetstate  tracemgrpacketgetstate
	#define CHK_tracemgrpacketgetstate  TRUE
	#define EXP_tracemgrpacketgetstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetstate", (RTS_UINTPTR)tracemgrpacketgetstate, 1, 0x998E4A5E, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketgetstate
	#define EXT_tracemgrpacketgetstate
	#define GET_tracemgrpacketgetstate(fl)  CAL_CMGETAPI( "tracemgrpacketgetstate" ) 
	#define CAL_tracemgrpacketgetstate  tracemgrpacketgetstate
	#define CHK_tracemgrpacketgetstate  TRUE
	#define EXP_tracemgrpacketgetstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetstate", (RTS_UINTPTR)tracemgrpacketgetstate, 1, 0x998E4A5E, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketgetstate
	#define EXT_CmpTraceMgrtracemgrpacketgetstate
	#define GET_CmpTraceMgrtracemgrpacketgetstate  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketgetstate  tracemgrpacketgetstate
	#define CHK_CmpTraceMgrtracemgrpacketgetstate  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketgetstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetstate", (RTS_UINTPTR)tracemgrpacketgetstate, 1, 0x998E4A5E, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketgetstate
	#define EXT_tracemgrpacketgetstate
	#define GET_tracemgrpacketgetstate(fl)  CAL_CMGETAPI( "tracemgrpacketgetstate" ) 
	#define CAL_tracemgrpacketgetstate  tracemgrpacketgetstate
	#define CHK_tracemgrpacketgetstate  TRUE
	#define EXP_tracemgrpacketgetstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetstate", (RTS_UINTPTR)tracemgrpacketgetstate, 1, 0x998E4A5E, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketgetstate  PFTRACEMGRPACKETGETSTATE_IEC pftracemgrpacketgetstate;
	#define EXT_tracemgrpacketgetstate  extern PFTRACEMGRPACKETGETSTATE_IEC pftracemgrpacketgetstate;
	#define GET_tracemgrpacketgetstate(fl)  s_pfCMGetAPI2( "tracemgrpacketgetstate", (RTS_VOID_FCTPTR *)&pftracemgrpacketgetstate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x998E4A5E, 0x03050B00)
	#define CAL_tracemgrpacketgetstate  pftracemgrpacketgetstate
	#define CHK_tracemgrpacketgetstate  (pftracemgrpacketgetstate != NULL)
	#define EXP_tracemgrpacketgetstate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketgetstate", (RTS_UINTPTR)tracemgrpacketgetstate, 1, 0x998E4A5E, 0x03050B00) 
#endif


/**
 * Opens a trace packet specified by name.
 *
 * .. note:: Comparison of packet names is case-insensitive.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_NO_OBJECT if no packet with the given name is found. 
 */
typedef struct tagtracemgrpacketopen_struct
{
	RTS_IEC_STRING *pszName;			/* VAR_IN_OUT */	/* The name of the trace packet to open (in) */
	RTS_IEC_RESULT *pResult;			/* VAR_IN_OUT */	/* The result code (out) */
	RTS_IEC_HANDLE TraceMgrPacketOpen;	/* VAR_OUTPUT */	/* The packet handle if found, RTS_INVALID_HANDLE otherwise */
} tracemgrpacketopen_struct;

void CDECL CDECL_EXT tracemgrpacketopen(tracemgrpacketopen_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETOPEN_IEC) (tracemgrpacketopen_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETOPEN_NOTIMPLEMENTED)
	#define USE_tracemgrpacketopen
	#define EXT_tracemgrpacketopen
	#define GET_tracemgrpacketopen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketopen(p0) 
	#define CHK_tracemgrpacketopen  FALSE
	#define EXP_tracemgrpacketopen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketopen
	#define EXT_tracemgrpacketopen
	#define GET_tracemgrpacketopen(fl)  CAL_CMGETAPI( "tracemgrpacketopen" ) 
	#define CAL_tracemgrpacketopen  tracemgrpacketopen
	#define CHK_tracemgrpacketopen  TRUE
	#define EXP_tracemgrpacketopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketopen", (RTS_UINTPTR)tracemgrpacketopen, 1, 0x32667B41, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketopen
	#define EXT_tracemgrpacketopen
	#define GET_tracemgrpacketopen(fl)  CAL_CMGETAPI( "tracemgrpacketopen" ) 
	#define CAL_tracemgrpacketopen  tracemgrpacketopen
	#define CHK_tracemgrpacketopen  TRUE
	#define EXP_tracemgrpacketopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketopen", (RTS_UINTPTR)tracemgrpacketopen, 1, 0x32667B41, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketopen
	#define EXT_CmpTraceMgrtracemgrpacketopen
	#define GET_CmpTraceMgrtracemgrpacketopen  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketopen  tracemgrpacketopen
	#define CHK_CmpTraceMgrtracemgrpacketopen  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketopen", (RTS_UINTPTR)tracemgrpacketopen, 1, 0x32667B41, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketopen
	#define EXT_tracemgrpacketopen
	#define GET_tracemgrpacketopen(fl)  CAL_CMGETAPI( "tracemgrpacketopen" ) 
	#define CAL_tracemgrpacketopen  tracemgrpacketopen
	#define CHK_tracemgrpacketopen  TRUE
	#define EXP_tracemgrpacketopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketopen", (RTS_UINTPTR)tracemgrpacketopen, 1, 0x32667B41, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketopen  PFTRACEMGRPACKETOPEN_IEC pftracemgrpacketopen;
	#define EXT_tracemgrpacketopen  extern PFTRACEMGRPACKETOPEN_IEC pftracemgrpacketopen;
	#define GET_tracemgrpacketopen(fl)  s_pfCMGetAPI2( "tracemgrpacketopen", (RTS_VOID_FCTPTR *)&pftracemgrpacketopen, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x32667B41, 0x03050B00)
	#define CAL_tracemgrpacketopen  pftracemgrpacketopen
	#define CHK_tracemgrpacketopen  (pftracemgrpacketopen != NULL)
	#define EXP_tracemgrpacketopen   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketopen", (RTS_UINTPTR)tracemgrpacketopen, 1, 0x32667B41, 0x03050B00) 
#endif


/**
 * Start reading trace packet.
 * 
 * The purpose of this function is to trigger the event
 * EVT_TRACEMGR_PACKET_SAMPLE.
 * In response to the event, any outstanding trace samples will be written
 * by runtime system components and IEC applications that provide trace
 * values for system parameters.
 *
 * .. note:: Normally, there is no need to call this function. It should be
 *    called before |TraceMgrPacketReadFirst| and |TraceMgrPacketReadFirst2| to
 *    make sure all trace values are present before reading.  When finished
 *    with reading, TraceMgrPacketReadEnd should be called.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid packet handle
 *   - ERR_NOTINITIALIZED if hPacket is not complete and started
 */
typedef struct tagtracemgrpacketreadbegin_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_RESULT TraceMgrPacketReadBegin;	/* VAR_OUTPUT */	/* The result code */
} tracemgrpacketreadbegin_struct;

void CDECL CDECL_EXT tracemgrpacketreadbegin(tracemgrpacketreadbegin_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETREADBEGIN_IEC) (tracemgrpacketreadbegin_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETREADBEGIN_NOTIMPLEMENTED)
	#define USE_tracemgrpacketreadbegin
	#define EXT_tracemgrpacketreadbegin
	#define GET_tracemgrpacketreadbegin(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketreadbegin(p0) 
	#define CHK_tracemgrpacketreadbegin  FALSE
	#define EXP_tracemgrpacketreadbegin  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketreadbegin
	#define EXT_tracemgrpacketreadbegin
	#define GET_tracemgrpacketreadbegin(fl)  CAL_CMGETAPI( "tracemgrpacketreadbegin" ) 
	#define CAL_tracemgrpacketreadbegin  tracemgrpacketreadbegin
	#define CHK_tracemgrpacketreadbegin  TRUE
	#define EXP_tracemgrpacketreadbegin  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadbegin", (RTS_UINTPTR)tracemgrpacketreadbegin, 1, 0xDD2F3F8A, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketreadbegin
	#define EXT_tracemgrpacketreadbegin
	#define GET_tracemgrpacketreadbegin(fl)  CAL_CMGETAPI( "tracemgrpacketreadbegin" ) 
	#define CAL_tracemgrpacketreadbegin  tracemgrpacketreadbegin
	#define CHK_tracemgrpacketreadbegin  TRUE
	#define EXP_tracemgrpacketreadbegin  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadbegin", (RTS_UINTPTR)tracemgrpacketreadbegin, 1, 0xDD2F3F8A, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketreadbegin
	#define EXT_CmpTraceMgrtracemgrpacketreadbegin
	#define GET_CmpTraceMgrtracemgrpacketreadbegin  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketreadbegin  tracemgrpacketreadbegin
	#define CHK_CmpTraceMgrtracemgrpacketreadbegin  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketreadbegin  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadbegin", (RTS_UINTPTR)tracemgrpacketreadbegin, 1, 0xDD2F3F8A, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketreadbegin
	#define EXT_tracemgrpacketreadbegin
	#define GET_tracemgrpacketreadbegin(fl)  CAL_CMGETAPI( "tracemgrpacketreadbegin" ) 
	#define CAL_tracemgrpacketreadbegin  tracemgrpacketreadbegin
	#define CHK_tracemgrpacketreadbegin  TRUE
	#define EXP_tracemgrpacketreadbegin  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadbegin", (RTS_UINTPTR)tracemgrpacketreadbegin, 1, 0xDD2F3F8A, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketreadbegin  PFTRACEMGRPACKETREADBEGIN_IEC pftracemgrpacketreadbegin;
	#define EXT_tracemgrpacketreadbegin  extern PFTRACEMGRPACKETREADBEGIN_IEC pftracemgrpacketreadbegin;
	#define GET_tracemgrpacketreadbegin(fl)  s_pfCMGetAPI2( "tracemgrpacketreadbegin", (RTS_VOID_FCTPTR *)&pftracemgrpacketreadbegin, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xDD2F3F8A, 0x03050B00)
	#define CAL_tracemgrpacketreadbegin  pftracemgrpacketreadbegin
	#define CHK_tracemgrpacketreadbegin  (pftracemgrpacketreadbegin != NULL)
	#define EXP_tracemgrpacketreadbegin   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadbegin", (RTS_UINTPTR)tracemgrpacketreadbegin, 1, 0xDD2F3F8A, 0x03050B00) 
#endif


/**
 * End reading trace packet.
 *
 * See description of function |TraceMgrPacketReadBegin|.
 * 
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid packet handle
 *   - ERR_NOTINITIALIZED if hPacket is not complete and started
 */
typedef struct tagtracemgrpacketreadend_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_RESULT TraceMgrPacketReadEnd;	/* VAR_OUTPUT */	/* The result code */
} tracemgrpacketreadend_struct;

void CDECL CDECL_EXT tracemgrpacketreadend(tracemgrpacketreadend_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETREADEND_IEC) (tracemgrpacketreadend_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETREADEND_NOTIMPLEMENTED)
	#define USE_tracemgrpacketreadend
	#define EXT_tracemgrpacketreadend
	#define GET_tracemgrpacketreadend(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketreadend(p0) 
	#define CHK_tracemgrpacketreadend  FALSE
	#define EXP_tracemgrpacketreadend  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketreadend
	#define EXT_tracemgrpacketreadend
	#define GET_tracemgrpacketreadend(fl)  CAL_CMGETAPI( "tracemgrpacketreadend" ) 
	#define CAL_tracemgrpacketreadend  tracemgrpacketreadend
	#define CHK_tracemgrpacketreadend  TRUE
	#define EXP_tracemgrpacketreadend  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadend", (RTS_UINTPTR)tracemgrpacketreadend, 1, 0x96F691B2, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketreadend
	#define EXT_tracemgrpacketreadend
	#define GET_tracemgrpacketreadend(fl)  CAL_CMGETAPI( "tracemgrpacketreadend" ) 
	#define CAL_tracemgrpacketreadend  tracemgrpacketreadend
	#define CHK_tracemgrpacketreadend  TRUE
	#define EXP_tracemgrpacketreadend  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadend", (RTS_UINTPTR)tracemgrpacketreadend, 1, 0x96F691B2, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketreadend
	#define EXT_CmpTraceMgrtracemgrpacketreadend
	#define GET_CmpTraceMgrtracemgrpacketreadend  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketreadend  tracemgrpacketreadend
	#define CHK_CmpTraceMgrtracemgrpacketreadend  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketreadend  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadend", (RTS_UINTPTR)tracemgrpacketreadend, 1, 0x96F691B2, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketreadend
	#define EXT_tracemgrpacketreadend
	#define GET_tracemgrpacketreadend(fl)  CAL_CMGETAPI( "tracemgrpacketreadend" ) 
	#define CAL_tracemgrpacketreadend  tracemgrpacketreadend
	#define CHK_tracemgrpacketreadend  TRUE
	#define EXP_tracemgrpacketreadend  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadend", (RTS_UINTPTR)tracemgrpacketreadend, 1, 0x96F691B2, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketreadend  PFTRACEMGRPACKETREADEND_IEC pftracemgrpacketreadend;
	#define EXT_tracemgrpacketreadend  extern PFTRACEMGRPACKETREADEND_IEC pftracemgrpacketreadend;
	#define GET_tracemgrpacketreadend(fl)  s_pfCMGetAPI2( "tracemgrpacketreadend", (RTS_VOID_FCTPTR *)&pftracemgrpacketreadend, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x96F691B2, 0x03050B00)
	#define CAL_tracemgrpacketreadend  pftracemgrpacketreadend
	#define CHK_tracemgrpacketreadend  (pftracemgrpacketreadend != NULL)
	#define EXP_tracemgrpacketreadend   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadend", (RTS_UINTPTR)tracemgrpacketreadend, 1, 0x96F691B2, 0x03050B00) 
#endif


/**
 * Reads the contents of the first record.
 *
 * .. note:: if the result code is ERR_ENTRIES_REMAINING, data has been
 *    successfully copied to pTraceBuffer, but more data can be read
 *    by a subsequent call.  (Either because the destination buffer was
 *    too small, or because new data has been recorded in the mean time.)
 *
 * .. note:: You should call |TraceMgrPacketReadBegin| before calling
 *    this function, to make sure any outstanding trace values are written
 *    to the trace buffers.
 * 
 * .. note:: Data is always returned in little endian byte order even if 
 *    the device has big endian byte order.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid packet handle
 *   - ERR_NO_OBJECT if the packet does not have a single record
 *   - ERR_NOTINITIALIZED if the packet is not complete
 *   - ERR_TIMEOUT if reading took too long
 *   - ERR_ENTRIES_REMAINING if more data can be read by a subsequent call (this is not an error)
 */
typedef struct tagtracemgrpacketreadfirst_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	TraceRecordEntry *pTraceBuffer;		/* VAR_IN_OUT */	/* Pointer to the destination buffer */
	RTS_IEC_UDINT *pulReadBytes;		/* VAR_IN_OUT */	/* Size of the destination buffer in bytes (in), number of bytes copied (out) */
	RTS_IEC_RESULT *pResult;			/* VAR_IN_OUT */	/* The result code */
	RTS_IEC_HANDLE TraceMgrPacketReadFirst;	/* VAR_OUTPUT */	/* The handle of the first trace record or RTS_INVALID_HANLDE on error */
} tracemgrpacketreadfirst_struct;

void CDECL CDECL_EXT tracemgrpacketreadfirst(tracemgrpacketreadfirst_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETREADFIRST_IEC) (tracemgrpacketreadfirst_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETREADFIRST_NOTIMPLEMENTED)
	#define USE_tracemgrpacketreadfirst
	#define EXT_tracemgrpacketreadfirst
	#define GET_tracemgrpacketreadfirst(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketreadfirst(p0) 
	#define CHK_tracemgrpacketreadfirst  FALSE
	#define EXP_tracemgrpacketreadfirst  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketreadfirst
	#define EXT_tracemgrpacketreadfirst
	#define GET_tracemgrpacketreadfirst(fl)  CAL_CMGETAPI( "tracemgrpacketreadfirst" ) 
	#define CAL_tracemgrpacketreadfirst  tracemgrpacketreadfirst
	#define CHK_tracemgrpacketreadfirst  TRUE
	#define EXP_tracemgrpacketreadfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadfirst", (RTS_UINTPTR)tracemgrpacketreadfirst, 1, 0x074AB535, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketreadfirst
	#define EXT_tracemgrpacketreadfirst
	#define GET_tracemgrpacketreadfirst(fl)  CAL_CMGETAPI( "tracemgrpacketreadfirst" ) 
	#define CAL_tracemgrpacketreadfirst  tracemgrpacketreadfirst
	#define CHK_tracemgrpacketreadfirst  TRUE
	#define EXP_tracemgrpacketreadfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadfirst", (RTS_UINTPTR)tracemgrpacketreadfirst, 1, 0x074AB535, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketreadfirst
	#define EXT_CmpTraceMgrtracemgrpacketreadfirst
	#define GET_CmpTraceMgrtracemgrpacketreadfirst  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketreadfirst  tracemgrpacketreadfirst
	#define CHK_CmpTraceMgrtracemgrpacketreadfirst  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketreadfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadfirst", (RTS_UINTPTR)tracemgrpacketreadfirst, 1, 0x074AB535, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketreadfirst
	#define EXT_tracemgrpacketreadfirst
	#define GET_tracemgrpacketreadfirst(fl)  CAL_CMGETAPI( "tracemgrpacketreadfirst" ) 
	#define CAL_tracemgrpacketreadfirst  tracemgrpacketreadfirst
	#define CHK_tracemgrpacketreadfirst  TRUE
	#define EXP_tracemgrpacketreadfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadfirst", (RTS_UINTPTR)tracemgrpacketreadfirst, 1, 0x074AB535, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketreadfirst  PFTRACEMGRPACKETREADFIRST_IEC pftracemgrpacketreadfirst;
	#define EXT_tracemgrpacketreadfirst  extern PFTRACEMGRPACKETREADFIRST_IEC pftracemgrpacketreadfirst;
	#define GET_tracemgrpacketreadfirst(fl)  s_pfCMGetAPI2( "tracemgrpacketreadfirst", (RTS_VOID_FCTPTR *)&pftracemgrpacketreadfirst, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x074AB535, 0x03050B00)
	#define CAL_tracemgrpacketreadfirst  pftracemgrpacketreadfirst
	#define CHK_tracemgrpacketreadfirst  (pftracemgrpacketreadfirst != NULL)
	#define EXP_tracemgrpacketreadfirst   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadfirst", (RTS_UINTPTR)tracemgrpacketreadfirst, 1, 0x074AB535, 0x03050B00) 
#endif


/**
 * Reads the contents of the first record, starting at a given time stamp.
 *
 * Only entries with a time stamp greater than or equal to ulTimestamp are
 * copied.  If the time stamp is zero, the function behaves like
 * |TraceMgrPacketReadFirst|.
 *
 * .. note:: if the result code is ERR_ENTRIES_REMAINING, data has been
 *    successfully copied to pTraceBuffer, but more data can be read
 *    by a subsequent call.  (Either because the destination buffer was
 *    too small, or because new data has been recorded in the mean time.)
 *
 * .. note:: You should call |TraceMgrPacketReadBegin| before calling
 *    this function, to make sure any outstanding trace values are written
 *    to the trace buffers.
 *
 * .. note:: Data is always returned in little endian byte order even if
 *    the device has big endian byte order.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid packet handle
 *   - ERR_NO_OBJECT if the packet does not have a single record
 *   - ERR_NOTINITIALIZED if the packet is not complete
 *   - ERR_TIMEOUT if reading took too long
 *   - ERR_ENTRIES_REMAINING if more data can be read by a subsequent call (this is not an error)
 */
typedef struct tagtracemgrpacketreadfirst2_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_UDINT ulTimestamp;			/* VAR_INPUT */	/* The time stamp (relative to the trace start time) from where to start copying */
	TraceRecordEntry *pTraceBuffer;		/* VAR_IN_OUT */	/* Pointer to the destination buffer */
	RTS_IEC_UDINT *pulReadBytes;		/* VAR_IN_OUT */	/* Size of the destination buffer in bytes (in), number of bytes copied (out) */
	RTS_IEC_RESULT *pResult;			/* VAR_IN_OUT */	/* The result code */
	RTS_IEC_HANDLE TraceMgrPacketReadFirst2;	/* VAR_OUTPUT */	/* The handle of the first trace record or RTS_INVALID_HANLDE on error */
} tracemgrpacketreadfirst2_struct;

void CDECL CDECL_EXT tracemgrpacketreadfirst2(tracemgrpacketreadfirst2_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETREADFIRST2_IEC) (tracemgrpacketreadfirst2_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETREADFIRST2_NOTIMPLEMENTED)
	#define USE_tracemgrpacketreadfirst2
	#define EXT_tracemgrpacketreadfirst2
	#define GET_tracemgrpacketreadfirst2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketreadfirst2(p0) 
	#define CHK_tracemgrpacketreadfirst2  FALSE
	#define EXP_tracemgrpacketreadfirst2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketreadfirst2
	#define EXT_tracemgrpacketreadfirst2
	#define GET_tracemgrpacketreadfirst2(fl)  CAL_CMGETAPI( "tracemgrpacketreadfirst2" ) 
	#define CAL_tracemgrpacketreadfirst2  tracemgrpacketreadfirst2
	#define CHK_tracemgrpacketreadfirst2  TRUE
	#define EXP_tracemgrpacketreadfirst2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadfirst2", (RTS_UINTPTR)tracemgrpacketreadfirst2, 1, 0x8F85D7AF, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketreadfirst2
	#define EXT_tracemgrpacketreadfirst2
	#define GET_tracemgrpacketreadfirst2(fl)  CAL_CMGETAPI( "tracemgrpacketreadfirst2" ) 
	#define CAL_tracemgrpacketreadfirst2  tracemgrpacketreadfirst2
	#define CHK_tracemgrpacketreadfirst2  TRUE
	#define EXP_tracemgrpacketreadfirst2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadfirst2", (RTS_UINTPTR)tracemgrpacketreadfirst2, 1, 0x8F85D7AF, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketreadfirst2
	#define EXT_CmpTraceMgrtracemgrpacketreadfirst2
	#define GET_CmpTraceMgrtracemgrpacketreadfirst2  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketreadfirst2  tracemgrpacketreadfirst2
	#define CHK_CmpTraceMgrtracemgrpacketreadfirst2  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketreadfirst2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadfirst2", (RTS_UINTPTR)tracemgrpacketreadfirst2, 1, 0x8F85D7AF, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketreadfirst2
	#define EXT_tracemgrpacketreadfirst2
	#define GET_tracemgrpacketreadfirst2(fl)  CAL_CMGETAPI( "tracemgrpacketreadfirst2" ) 
	#define CAL_tracemgrpacketreadfirst2  tracemgrpacketreadfirst2
	#define CHK_tracemgrpacketreadfirst2  TRUE
	#define EXP_tracemgrpacketreadfirst2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadfirst2", (RTS_UINTPTR)tracemgrpacketreadfirst2, 1, 0x8F85D7AF, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketreadfirst2  PFTRACEMGRPACKETREADFIRST2_IEC pftracemgrpacketreadfirst2;
	#define EXT_tracemgrpacketreadfirst2  extern PFTRACEMGRPACKETREADFIRST2_IEC pftracemgrpacketreadfirst2;
	#define GET_tracemgrpacketreadfirst2(fl)  s_pfCMGetAPI2( "tracemgrpacketreadfirst2", (RTS_VOID_FCTPTR *)&pftracemgrpacketreadfirst2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x8F85D7AF, 0x03050B00)
	#define CAL_tracemgrpacketreadfirst2  pftracemgrpacketreadfirst2
	#define CHK_tracemgrpacketreadfirst2  (pftracemgrpacketreadfirst2 != NULL)
	#define EXP_tracemgrpacketreadfirst2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadfirst2", (RTS_UINTPTR)tracemgrpacketreadfirst2, 1, 0x8F85D7AF, 0x03050B00) 
#endif


/**
 * Reads the contents of the next record.
 *
 * .. note:: if the result code is ERR_ENTRIES_REMAINING, data has been
 *    successfully copied to pTraceBuffer, but more data can be read
 *    by a subsequent call.  (Either because the destination buffer was
 *    too small, or because new data has been recorded in the mean time.)
 *
 * .. note:: Data is always returned in little endian byte order even if
 *    the device has big endian byte order.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid packet handle or if hPrevRecord is not a valid record handle
 *   - ERR_NO_OBJECT if there is no next record
 *   - ERR_NOTINITIALIZED if the packet is not complete
 *   - ERR_TIMEOUT if reading took too long
 *   - ERR_ENTRIES_REMAINING if more data can be read by a subsequent call (this is not an error)
 */
typedef struct tagtracemgrpacketreadnext_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_HANDLE hPrevRecord;			/* VAR_INPUT */	/* The trace record handle of the current record */
	TraceRecordEntry *pTraceBuffer;		/* VAR_IN_OUT */	/* Pointer to the destination buffer */
	RTS_IEC_UDINT *pulReadBytes;		/* VAR_IN_OUT */	/* Size of the destination buffer in bytes (in), number of bytes copied (out) */
	RTS_IEC_RESULT *pResult;			/* VAR_IN_OUT */	/* The result code */
	RTS_IEC_HANDLE TraceMgrPacketReadNext;	/* VAR_OUTPUT */	/* The handle of the next trace record or RTS_INVALID_HANLDE on error */
} tracemgrpacketreadnext_struct;

void CDECL CDECL_EXT tracemgrpacketreadnext(tracemgrpacketreadnext_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETREADNEXT_IEC) (tracemgrpacketreadnext_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETREADNEXT_NOTIMPLEMENTED)
	#define USE_tracemgrpacketreadnext
	#define EXT_tracemgrpacketreadnext
	#define GET_tracemgrpacketreadnext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketreadnext(p0) 
	#define CHK_tracemgrpacketreadnext  FALSE
	#define EXP_tracemgrpacketreadnext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketreadnext
	#define EXT_tracemgrpacketreadnext
	#define GET_tracemgrpacketreadnext(fl)  CAL_CMGETAPI( "tracemgrpacketreadnext" ) 
	#define CAL_tracemgrpacketreadnext  tracemgrpacketreadnext
	#define CHK_tracemgrpacketreadnext  TRUE
	#define EXP_tracemgrpacketreadnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadnext", (RTS_UINTPTR)tracemgrpacketreadnext, 1, 0xDA5B316F, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketreadnext
	#define EXT_tracemgrpacketreadnext
	#define GET_tracemgrpacketreadnext(fl)  CAL_CMGETAPI( "tracemgrpacketreadnext" ) 
	#define CAL_tracemgrpacketreadnext  tracemgrpacketreadnext
	#define CHK_tracemgrpacketreadnext  TRUE
	#define EXP_tracemgrpacketreadnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadnext", (RTS_UINTPTR)tracemgrpacketreadnext, 1, 0xDA5B316F, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketreadnext
	#define EXT_CmpTraceMgrtracemgrpacketreadnext
	#define GET_CmpTraceMgrtracemgrpacketreadnext  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketreadnext  tracemgrpacketreadnext
	#define CHK_CmpTraceMgrtracemgrpacketreadnext  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketreadnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadnext", (RTS_UINTPTR)tracemgrpacketreadnext, 1, 0xDA5B316F, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketreadnext
	#define EXT_tracemgrpacketreadnext
	#define GET_tracemgrpacketreadnext(fl)  CAL_CMGETAPI( "tracemgrpacketreadnext" ) 
	#define CAL_tracemgrpacketreadnext  tracemgrpacketreadnext
	#define CHK_tracemgrpacketreadnext  TRUE
	#define EXP_tracemgrpacketreadnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadnext", (RTS_UINTPTR)tracemgrpacketreadnext, 1, 0xDA5B316F, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketreadnext  PFTRACEMGRPACKETREADNEXT_IEC pftracemgrpacketreadnext;
	#define EXT_tracemgrpacketreadnext  extern PFTRACEMGRPACKETREADNEXT_IEC pftracemgrpacketreadnext;
	#define GET_tracemgrpacketreadnext(fl)  s_pfCMGetAPI2( "tracemgrpacketreadnext", (RTS_VOID_FCTPTR *)&pftracemgrpacketreadnext, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xDA5B316F, 0x03050B00)
	#define CAL_tracemgrpacketreadnext  pftracemgrpacketreadnext
	#define CHK_tracemgrpacketreadnext  (pftracemgrpacketreadnext != NULL)
	#define EXP_tracemgrpacketreadnext   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadnext", (RTS_UINTPTR)tracemgrpacketreadnext, 1, 0xDA5B316F, 0x03050B00) 
#endif


/**
 * Reads the contents of the next record, starting at a given time stamp.
 *
 * Only entries with a time stamp greater than or equal to ulTimestamp are
 * copied.  If the time stamp is zero, the function behaves like
 * |TraceMgrPacketReadNext|.
 *
 * .. note:: if the result code is ERR_ENTRIES_REMAINING, data has been
 *    successfully copied to pTraceBuffer, but more data can be read
 *    by a subsequent call.  (Either because the destination buffer was
 *    too small, or because new data has been recorded in the mean time.)
 *
 * .. note:: Data is always returned in little endian byte order even if
 *    the device has big endian byte order.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid packet handle or if hPrevRecord is not a valid record handle
 *   - ERR_NO_OBJECT if there is no next record
 *   - ERR_NOTINITIALIZED if the packet is not complete
 *   - ERR_TIMEOUT if reading took too long
 *   - ERR_ENTRIES_REMAINING if more data can be read by a subsequent call (this is not an error)
 */
typedef struct tagtracemgrpacketreadnext2_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_HANDLE hPrevRecord;			/* VAR_INPUT */	/* The trace record handle of the current record */
	RTS_IEC_UDINT ulTimestamp;			/* VAR_INPUT */	/* The time stamp (relative to the trace start time) from where to start copying */
	TraceRecordEntry *pTraceBuffer;		/* VAR_IN_OUT */	/* Pointer to the destination buffer */
	RTS_IEC_UDINT *pulReadBytes;		/* VAR_IN_OUT */	/* Size of the destination buffer in bytes (in), number of bytes copied (out) */
	RTS_IEC_RESULT *pResult;			/* VAR_IN_OUT */	/* The result code */
	RTS_IEC_HANDLE TraceMgrPacketReadNext2;	/* VAR_OUTPUT */	/* The handle of the next trace record or RTS_INVALID_HANLDE on error */
} tracemgrpacketreadnext2_struct;

void CDECL CDECL_EXT tracemgrpacketreadnext2(tracemgrpacketreadnext2_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETREADNEXT2_IEC) (tracemgrpacketreadnext2_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETREADNEXT2_NOTIMPLEMENTED)
	#define USE_tracemgrpacketreadnext2
	#define EXT_tracemgrpacketreadnext2
	#define GET_tracemgrpacketreadnext2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketreadnext2(p0) 
	#define CHK_tracemgrpacketreadnext2  FALSE
	#define EXP_tracemgrpacketreadnext2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketreadnext2
	#define EXT_tracemgrpacketreadnext2
	#define GET_tracemgrpacketreadnext2(fl)  CAL_CMGETAPI( "tracemgrpacketreadnext2" ) 
	#define CAL_tracemgrpacketreadnext2  tracemgrpacketreadnext2
	#define CHK_tracemgrpacketreadnext2  TRUE
	#define EXP_tracemgrpacketreadnext2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadnext2", (RTS_UINTPTR)tracemgrpacketreadnext2, 1, 0xE91DB9CD, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketreadnext2
	#define EXT_tracemgrpacketreadnext2
	#define GET_tracemgrpacketreadnext2(fl)  CAL_CMGETAPI( "tracemgrpacketreadnext2" ) 
	#define CAL_tracemgrpacketreadnext2  tracemgrpacketreadnext2
	#define CHK_tracemgrpacketreadnext2  TRUE
	#define EXP_tracemgrpacketreadnext2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadnext2", (RTS_UINTPTR)tracemgrpacketreadnext2, 1, 0xE91DB9CD, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketreadnext2
	#define EXT_CmpTraceMgrtracemgrpacketreadnext2
	#define GET_CmpTraceMgrtracemgrpacketreadnext2  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketreadnext2  tracemgrpacketreadnext2
	#define CHK_CmpTraceMgrtracemgrpacketreadnext2  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketreadnext2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadnext2", (RTS_UINTPTR)tracemgrpacketreadnext2, 1, 0xE91DB9CD, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketreadnext2
	#define EXT_tracemgrpacketreadnext2
	#define GET_tracemgrpacketreadnext2(fl)  CAL_CMGETAPI( "tracemgrpacketreadnext2" ) 
	#define CAL_tracemgrpacketreadnext2  tracemgrpacketreadnext2
	#define CHK_tracemgrpacketreadnext2  TRUE
	#define EXP_tracemgrpacketreadnext2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadnext2", (RTS_UINTPTR)tracemgrpacketreadnext2, 1, 0xE91DB9CD, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketreadnext2  PFTRACEMGRPACKETREADNEXT2_IEC pftracemgrpacketreadnext2;
	#define EXT_tracemgrpacketreadnext2  extern PFTRACEMGRPACKETREADNEXT2_IEC pftracemgrpacketreadnext2;
	#define GET_tracemgrpacketreadnext2(fl)  s_pfCMGetAPI2( "tracemgrpacketreadnext2", (RTS_VOID_FCTPTR *)&pftracemgrpacketreadnext2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xE91DB9CD, 0x03050B00)
	#define CAL_tracemgrpacketreadnext2  pftracemgrpacketreadnext2
	#define CHK_tracemgrpacketreadnext2  (pftracemgrpacketreadnext2 != NULL)
	#define EXP_tracemgrpacketreadnext2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketreadnext2", (RTS_UINTPTR)tracemgrpacketreadnext2, 1, 0xE91DB9CD, 0x03050B00) 
#endif


/**
 * Resets the trigger of a trace packet.  The start time and date of
 * of the trigger is reset to 0 and the trigger is set to state enabled
 * (if it is not disabled).
 * 
 * .. note: if the trigger is currently disabled, it stays disabled.  To enable
 *    it, call TraceMgrPacketEnableTrigger.
 * 
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid packet handle
 */
typedef struct tagtracemgrpacketresettrigger_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_RESULT TraceMgrPacketResetTrigger;	/* VAR_OUTPUT */	/* The result code */
} tracemgrpacketresettrigger_struct;

void CDECL CDECL_EXT tracemgrpacketresettrigger(tracemgrpacketresettrigger_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETRESETTRIGGER_IEC) (tracemgrpacketresettrigger_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETRESETTRIGGER_NOTIMPLEMENTED)
	#define USE_tracemgrpacketresettrigger
	#define EXT_tracemgrpacketresettrigger
	#define GET_tracemgrpacketresettrigger(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketresettrigger(p0) 
	#define CHK_tracemgrpacketresettrigger  FALSE
	#define EXP_tracemgrpacketresettrigger  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketresettrigger
	#define EXT_tracemgrpacketresettrigger
	#define GET_tracemgrpacketresettrigger(fl)  CAL_CMGETAPI( "tracemgrpacketresettrigger" ) 
	#define CAL_tracemgrpacketresettrigger  tracemgrpacketresettrigger
	#define CHK_tracemgrpacketresettrigger  TRUE
	#define EXP_tracemgrpacketresettrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketresettrigger", (RTS_UINTPTR)tracemgrpacketresettrigger, 1, 0xE73A7FCC, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketresettrigger
	#define EXT_tracemgrpacketresettrigger
	#define GET_tracemgrpacketresettrigger(fl)  CAL_CMGETAPI( "tracemgrpacketresettrigger" ) 
	#define CAL_tracemgrpacketresettrigger  tracemgrpacketresettrigger
	#define CHK_tracemgrpacketresettrigger  TRUE
	#define EXP_tracemgrpacketresettrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketresettrigger", (RTS_UINTPTR)tracemgrpacketresettrigger, 1, 0xE73A7FCC, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketresettrigger
	#define EXT_CmpTraceMgrtracemgrpacketresettrigger
	#define GET_CmpTraceMgrtracemgrpacketresettrigger  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketresettrigger  tracemgrpacketresettrigger
	#define CHK_CmpTraceMgrtracemgrpacketresettrigger  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketresettrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketresettrigger", (RTS_UINTPTR)tracemgrpacketresettrigger, 1, 0xE73A7FCC, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketresettrigger
	#define EXT_tracemgrpacketresettrigger
	#define GET_tracemgrpacketresettrigger(fl)  CAL_CMGETAPI( "tracemgrpacketresettrigger" ) 
	#define CAL_tracemgrpacketresettrigger  tracemgrpacketresettrigger
	#define CHK_tracemgrpacketresettrigger  TRUE
	#define EXP_tracemgrpacketresettrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketresettrigger", (RTS_UINTPTR)tracemgrpacketresettrigger, 1, 0xE73A7FCC, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketresettrigger  PFTRACEMGRPACKETRESETTRIGGER_IEC pftracemgrpacketresettrigger;
	#define EXT_tracemgrpacketresettrigger  extern PFTRACEMGRPACKETRESETTRIGGER_IEC pftracemgrpacketresettrigger;
	#define GET_tracemgrpacketresettrigger(fl)  s_pfCMGetAPI2( "tracemgrpacketresettrigger", (RTS_VOID_FCTPTR *)&pftracemgrpacketresettrigger, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xE73A7FCC, 0x03050B00)
	#define CAL_tracemgrpacketresettrigger  pftracemgrpacketresettrigger
	#define CHK_tracemgrpacketresettrigger  (pftracemgrpacketresettrigger != NULL)
	#define EXP_tracemgrpacketresettrigger   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketresettrigger", (RTS_UINTPTR)tracemgrpacketresettrigger, 1, 0xE73A7FCC, 0x03050B00) 
#endif


/**
 * Restarts a trace packet and resets the start time and the trigger.
 *
 * In contrast to TraceMgrPacketStart, the trace is stopped and
 * the start time is reset to the current time before it is
 * started again.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid packet handle
 */
typedef struct tagtracemgrpacketrestart_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_RESULT TraceMgrPacketRestart;	/* VAR_OUTPUT */	/* The result code */
} tracemgrpacketrestart_struct;

void CDECL CDECL_EXT tracemgrpacketrestart(tracemgrpacketrestart_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETRESTART_IEC) (tracemgrpacketrestart_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETRESTART_NOTIMPLEMENTED)
	#define USE_tracemgrpacketrestart
	#define EXT_tracemgrpacketrestart
	#define GET_tracemgrpacketrestart(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketrestart(p0) 
	#define CHK_tracemgrpacketrestart  FALSE
	#define EXP_tracemgrpacketrestart  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketrestart
	#define EXT_tracemgrpacketrestart
	#define GET_tracemgrpacketrestart(fl)  CAL_CMGETAPI( "tracemgrpacketrestart" ) 
	#define CAL_tracemgrpacketrestart  tracemgrpacketrestart
	#define CHK_tracemgrpacketrestart  TRUE
	#define EXP_tracemgrpacketrestart  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketrestart", (RTS_UINTPTR)tracemgrpacketrestart, 1, 0xAD7F1200, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketrestart
	#define EXT_tracemgrpacketrestart
	#define GET_tracemgrpacketrestart(fl)  CAL_CMGETAPI( "tracemgrpacketrestart" ) 
	#define CAL_tracemgrpacketrestart  tracemgrpacketrestart
	#define CHK_tracemgrpacketrestart  TRUE
	#define EXP_tracemgrpacketrestart  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketrestart", (RTS_UINTPTR)tracemgrpacketrestart, 1, 0xAD7F1200, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketrestart
	#define EXT_CmpTraceMgrtracemgrpacketrestart
	#define GET_CmpTraceMgrtracemgrpacketrestart  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketrestart  tracemgrpacketrestart
	#define CHK_CmpTraceMgrtracemgrpacketrestart  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketrestart  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketrestart", (RTS_UINTPTR)tracemgrpacketrestart, 1, 0xAD7F1200, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketrestart
	#define EXT_tracemgrpacketrestart
	#define GET_tracemgrpacketrestart(fl)  CAL_CMGETAPI( "tracemgrpacketrestart" ) 
	#define CAL_tracemgrpacketrestart  tracemgrpacketrestart
	#define CHK_tracemgrpacketrestart  TRUE
	#define EXP_tracemgrpacketrestart  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketrestart", (RTS_UINTPTR)tracemgrpacketrestart, 1, 0xAD7F1200, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketrestart  PFTRACEMGRPACKETRESTART_IEC pftracemgrpacketrestart;
	#define EXT_tracemgrpacketrestart  extern PFTRACEMGRPACKETRESTART_IEC pftracemgrpacketrestart;
	#define GET_tracemgrpacketrestart(fl)  s_pfCMGetAPI2( "tracemgrpacketrestart", (RTS_VOID_FCTPTR *)&pftracemgrpacketrestart, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xAD7F1200, 0x03050B00)
	#define CAL_tracemgrpacketrestart  pftracemgrpacketrestart
	#define CHK_tracemgrpacketrestart  (pftracemgrpacketrestart != NULL)
	#define EXP_tracemgrpacketrestart   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketrestart", (RTS_UINTPTR)tracemgrpacketrestart, 1, 0xAD7F1200, 0x03050B00) 
#endif


/**
 * Loads a trace packet from a trace file.
 * Both the trace configuration and the current trace values are restored.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid handle, or if pszFileName is not a valid file path
 *   - ERR_NOMEMORY if the memory is not sufficient for opening the file
 *   - ERR_NOT_SUPPORTED if reading from files is not supported by the runtime system
 *     or if an addressing mode is not supported (e.g. symbolic access)
 *   - ERR_NO_OBJECT if opening the file failed
 *   - ERR_FAILED if opening the file failed
 */
typedef struct tagtracemgrpacketrestore_struct
{
	RTS_IEC_STRING *pszFileName;		/* VAR_IN_OUT */	/* The file path (in) */
	RTS_IEC_RESULT *pResult;			/* VAR_IN_OUT */	/* The result code (out) */
	RTS_IEC_HANDLE TraceMgrPacketRestore;	/* VAR_OUTPUT */	/* The result code */
} tracemgrpacketrestore_struct;

void CDECL CDECL_EXT tracemgrpacketrestore(tracemgrpacketrestore_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETRESTORE_IEC) (tracemgrpacketrestore_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETRESTORE_NOTIMPLEMENTED)
	#define USE_tracemgrpacketrestore
	#define EXT_tracemgrpacketrestore
	#define GET_tracemgrpacketrestore(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketrestore(p0) 
	#define CHK_tracemgrpacketrestore  FALSE
	#define EXP_tracemgrpacketrestore  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketrestore
	#define EXT_tracemgrpacketrestore
	#define GET_tracemgrpacketrestore(fl)  CAL_CMGETAPI( "tracemgrpacketrestore" ) 
	#define CAL_tracemgrpacketrestore  tracemgrpacketrestore
	#define CHK_tracemgrpacketrestore  TRUE
	#define EXP_tracemgrpacketrestore  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketrestore", (RTS_UINTPTR)tracemgrpacketrestore, 1, 0xE1899ACC, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketrestore
	#define EXT_tracemgrpacketrestore
	#define GET_tracemgrpacketrestore(fl)  CAL_CMGETAPI( "tracemgrpacketrestore" ) 
	#define CAL_tracemgrpacketrestore  tracemgrpacketrestore
	#define CHK_tracemgrpacketrestore  TRUE
	#define EXP_tracemgrpacketrestore  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketrestore", (RTS_UINTPTR)tracemgrpacketrestore, 1, 0xE1899ACC, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketrestore
	#define EXT_CmpTraceMgrtracemgrpacketrestore
	#define GET_CmpTraceMgrtracemgrpacketrestore  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketrestore  tracemgrpacketrestore
	#define CHK_CmpTraceMgrtracemgrpacketrestore  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketrestore  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketrestore", (RTS_UINTPTR)tracemgrpacketrestore, 1, 0xE1899ACC, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketrestore
	#define EXT_tracemgrpacketrestore
	#define GET_tracemgrpacketrestore(fl)  CAL_CMGETAPI( "tracemgrpacketrestore" ) 
	#define CAL_tracemgrpacketrestore  tracemgrpacketrestore
	#define CHK_tracemgrpacketrestore  TRUE
	#define EXP_tracemgrpacketrestore  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketrestore", (RTS_UINTPTR)tracemgrpacketrestore, 1, 0xE1899ACC, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketrestore  PFTRACEMGRPACKETRESTORE_IEC pftracemgrpacketrestore;
	#define EXT_tracemgrpacketrestore  extern PFTRACEMGRPACKETRESTORE_IEC pftracemgrpacketrestore;
	#define GET_tracemgrpacketrestore(fl)  s_pfCMGetAPI2( "tracemgrpacketrestore", (RTS_VOID_FCTPTR *)&pftracemgrpacketrestore, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xE1899ACC, 0x03050B00)
	#define CAL_tracemgrpacketrestore  pftracemgrpacketrestore
	#define CHK_tracemgrpacketrestore  (pftracemgrpacketrestore != NULL)
	#define EXP_tracemgrpacketrestore   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketrestore", (RTS_UINTPTR)tracemgrpacketrestore, 1, 0xE1899ACC, 0x03050B00) 
#endif


/**
 * Starts a trace packet and resets the trigger.
 *
 * .. note:: if the packet is started for the first time, the start
 *    time of the packet is set to the current time. See: |TraceMgrPacketGetStartTime|.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid packet handle
 */
typedef struct tagtracemgrpacketstart_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle (in) */
	RTS_IEC_RESULT TraceMgrPacketStart;	/* VAR_OUTPUT */	/* The result code */
} tracemgrpacketstart_struct;

void CDECL CDECL_EXT tracemgrpacketstart(tracemgrpacketstart_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETSTART_IEC) (tracemgrpacketstart_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETSTART_NOTIMPLEMENTED)
	#define USE_tracemgrpacketstart
	#define EXT_tracemgrpacketstart
	#define GET_tracemgrpacketstart(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketstart(p0) 
	#define CHK_tracemgrpacketstart  FALSE
	#define EXP_tracemgrpacketstart  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketstart
	#define EXT_tracemgrpacketstart
	#define GET_tracemgrpacketstart(fl)  CAL_CMGETAPI( "tracemgrpacketstart" ) 
	#define CAL_tracemgrpacketstart  tracemgrpacketstart
	#define CHK_tracemgrpacketstart  TRUE
	#define EXP_tracemgrpacketstart  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketstart", (RTS_UINTPTR)tracemgrpacketstart, 1, 0xDCA4F311, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketstart
	#define EXT_tracemgrpacketstart
	#define GET_tracemgrpacketstart(fl)  CAL_CMGETAPI( "tracemgrpacketstart" ) 
	#define CAL_tracemgrpacketstart  tracemgrpacketstart
	#define CHK_tracemgrpacketstart  TRUE
	#define EXP_tracemgrpacketstart  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketstart", (RTS_UINTPTR)tracemgrpacketstart, 1, 0xDCA4F311, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketstart
	#define EXT_CmpTraceMgrtracemgrpacketstart
	#define GET_CmpTraceMgrtracemgrpacketstart  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketstart  tracemgrpacketstart
	#define CHK_CmpTraceMgrtracemgrpacketstart  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketstart  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketstart", (RTS_UINTPTR)tracemgrpacketstart, 1, 0xDCA4F311, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketstart
	#define EXT_tracemgrpacketstart
	#define GET_tracemgrpacketstart(fl)  CAL_CMGETAPI( "tracemgrpacketstart" ) 
	#define CAL_tracemgrpacketstart  tracemgrpacketstart
	#define CHK_tracemgrpacketstart  TRUE
	#define EXP_tracemgrpacketstart  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketstart", (RTS_UINTPTR)tracemgrpacketstart, 1, 0xDCA4F311, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketstart  PFTRACEMGRPACKETSTART_IEC pftracemgrpacketstart;
	#define EXT_tracemgrpacketstart  extern PFTRACEMGRPACKETSTART_IEC pftracemgrpacketstart;
	#define GET_tracemgrpacketstart(fl)  s_pfCMGetAPI2( "tracemgrpacketstart", (RTS_VOID_FCTPTR *)&pftracemgrpacketstart, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xDCA4F311, 0x03050B00)
	#define CAL_tracemgrpacketstart  pftracemgrpacketstart
	#define CHK_tracemgrpacketstart  (pftracemgrpacketstart != NULL)
	#define EXP_tracemgrpacketstart   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketstart", (RTS_UINTPTR)tracemgrpacketstart, 1, 0xDCA4F311, 0x03050B00) 
#endif


/**
 * Stops a trace packet.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid packet handle
 */
typedef struct tagtracemgrpacketstop_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_RESULT TraceMgrPacketStop;	/* VAR_OUTPUT */	/* The result code */
} tracemgrpacketstop_struct;

void CDECL CDECL_EXT tracemgrpacketstop(tracemgrpacketstop_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETSTOP_IEC) (tracemgrpacketstop_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETSTOP_NOTIMPLEMENTED)
	#define USE_tracemgrpacketstop
	#define EXT_tracemgrpacketstop
	#define GET_tracemgrpacketstop(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketstop(p0) 
	#define CHK_tracemgrpacketstop  FALSE
	#define EXP_tracemgrpacketstop  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketstop
	#define EXT_tracemgrpacketstop
	#define GET_tracemgrpacketstop(fl)  CAL_CMGETAPI( "tracemgrpacketstop" ) 
	#define CAL_tracemgrpacketstop  tracemgrpacketstop
	#define CHK_tracemgrpacketstop  TRUE
	#define EXP_tracemgrpacketstop  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketstop", (RTS_UINTPTR)tracemgrpacketstop, 1, 0x3C28C22F, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketstop
	#define EXT_tracemgrpacketstop
	#define GET_tracemgrpacketstop(fl)  CAL_CMGETAPI( "tracemgrpacketstop" ) 
	#define CAL_tracemgrpacketstop  tracemgrpacketstop
	#define CHK_tracemgrpacketstop  TRUE
	#define EXP_tracemgrpacketstop  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketstop", (RTS_UINTPTR)tracemgrpacketstop, 1, 0x3C28C22F, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketstop
	#define EXT_CmpTraceMgrtracemgrpacketstop
	#define GET_CmpTraceMgrtracemgrpacketstop  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketstop  tracemgrpacketstop
	#define CHK_CmpTraceMgrtracemgrpacketstop  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketstop  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketstop", (RTS_UINTPTR)tracemgrpacketstop, 1, 0x3C28C22F, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketstop
	#define EXT_tracemgrpacketstop
	#define GET_tracemgrpacketstop(fl)  CAL_CMGETAPI( "tracemgrpacketstop" ) 
	#define CAL_tracemgrpacketstop  tracemgrpacketstop
	#define CHK_tracemgrpacketstop  TRUE
	#define EXP_tracemgrpacketstop  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketstop", (RTS_UINTPTR)tracemgrpacketstop, 1, 0x3C28C22F, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketstop  PFTRACEMGRPACKETSTOP_IEC pftracemgrpacketstop;
	#define EXT_tracemgrpacketstop  extern PFTRACEMGRPACKETSTOP_IEC pftracemgrpacketstop;
	#define GET_tracemgrpacketstop(fl)  s_pfCMGetAPI2( "tracemgrpacketstop", (RTS_VOID_FCTPTR *)&pftracemgrpacketstop, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x3C28C22F, 0x03050B00)
	#define CAL_tracemgrpacketstop  pftracemgrpacketstop
	#define CHK_tracemgrpacketstop  (pftracemgrpacketstop != NULL)
	#define EXP_tracemgrpacketstop   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketstop", (RTS_UINTPTR)tracemgrpacketstop, 1, 0x3C28C22F, 0x03050B00) 
#endif


/**
 * Stores a trace packet to a trace file.
 * Both the trace configuration and the current trace values are stored.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid handle, or if pszFileName is not a valid file path
 *   - ERR_NOMEMORY if the memory is not sufficient for opening the file
 *   - ERR_NOT_SUPPORTED if writing to files is not supported by the runtime system
 *   - ERR_NO_OBJECT if opening the file failed
 *   - ERR_FAILED if creating or writing to the file failed
 */
typedef struct tagtracemgrpacketstore_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_STRING *pszFileName;		/* VAR_IN_OUT */	/* The file path */
	RTS_IEC_RESULT TraceMgrPacketStore;	/* VAR_OUTPUT */	/* The result code */
} tracemgrpacketstore_struct;

void CDECL CDECL_EXT tracemgrpacketstore(tracemgrpacketstore_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRPACKETSTORE_IEC) (tracemgrpacketstore_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETSTORE_NOTIMPLEMENTED)
	#define USE_tracemgrpacketstore
	#define EXT_tracemgrpacketstore
	#define GET_tracemgrpacketstore(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrpacketstore(p0) 
	#define CHK_tracemgrpacketstore  FALSE
	#define EXP_tracemgrpacketstore  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrpacketstore
	#define EXT_tracemgrpacketstore
	#define GET_tracemgrpacketstore(fl)  CAL_CMGETAPI( "tracemgrpacketstore" ) 
	#define CAL_tracemgrpacketstore  tracemgrpacketstore
	#define CHK_tracemgrpacketstore  TRUE
	#define EXP_tracemgrpacketstore  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketstore", (RTS_UINTPTR)tracemgrpacketstore, 1, 0x705D2F68, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrpacketstore
	#define EXT_tracemgrpacketstore
	#define GET_tracemgrpacketstore(fl)  CAL_CMGETAPI( "tracemgrpacketstore" ) 
	#define CAL_tracemgrpacketstore  tracemgrpacketstore
	#define CHK_tracemgrpacketstore  TRUE
	#define EXP_tracemgrpacketstore  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketstore", (RTS_UINTPTR)tracemgrpacketstore, 1, 0x705D2F68, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrpacketstore
	#define EXT_CmpTraceMgrtracemgrpacketstore
	#define GET_CmpTraceMgrtracemgrpacketstore  ERR_OK
	#define CAL_CmpTraceMgrtracemgrpacketstore  tracemgrpacketstore
	#define CHK_CmpTraceMgrtracemgrpacketstore  TRUE
	#define EXP_CmpTraceMgrtracemgrpacketstore  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketstore", (RTS_UINTPTR)tracemgrpacketstore, 1, 0x705D2F68, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrpacketstore
	#define EXT_tracemgrpacketstore
	#define GET_tracemgrpacketstore(fl)  CAL_CMGETAPI( "tracemgrpacketstore" ) 
	#define CAL_tracemgrpacketstore  tracemgrpacketstore
	#define CHK_tracemgrpacketstore  TRUE
	#define EXP_tracemgrpacketstore  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketstore", (RTS_UINTPTR)tracemgrpacketstore, 1, 0x705D2F68, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrpacketstore  PFTRACEMGRPACKETSTORE_IEC pftracemgrpacketstore;
	#define EXT_tracemgrpacketstore  extern PFTRACEMGRPACKETSTORE_IEC pftracemgrpacketstore;
	#define GET_tracemgrpacketstore(fl)  s_pfCMGetAPI2( "tracemgrpacketstore", (RTS_VOID_FCTPTR *)&pftracemgrpacketstore, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x705D2F68, 0x03050B00)
	#define CAL_tracemgrpacketstore  pftracemgrpacketstore
	#define CHK_tracemgrpacketstore  (pftracemgrpacketstore != NULL)
	#define EXP_tracemgrpacketstore   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrpacketstore", (RTS_UINTPTR)tracemgrpacketstore, 1, 0x705D2F68, 0x03050B00) 
#endif


/**
 * Adds a new record to a trace packet
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid packet handle, if the variable name is not set, or if the variable type is not supported
 *   - ERR_NOMEMORY if there is not enough free memory to create the record
 */
typedef struct tagtracemgrrecordadd_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	TraceRecordConfiguration *pConfiguration;	/* VAR_IN_OUT */	/* The record configuration (in) */
	RTS_IEC_RESULT *pResult;			/* VAR_IN_OUT */	/* The result code (out) */
	RTS_IEC_HANDLE TraceMgrRecordAdd;	/* VAR_OUTPUT */	/* The record handle or RTS_INVALID_HANDLE on failure */
} tracemgrrecordadd_struct;

void CDECL CDECL_EXT tracemgrrecordadd(tracemgrrecordadd_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRRECORDADD_IEC) (tracemgrrecordadd_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRRECORDADD_NOTIMPLEMENTED)
	#define USE_tracemgrrecordadd
	#define EXT_tracemgrrecordadd
	#define GET_tracemgrrecordadd(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrrecordadd(p0) 
	#define CHK_tracemgrrecordadd  FALSE
	#define EXP_tracemgrrecordadd  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrrecordadd
	#define EXT_tracemgrrecordadd
	#define GET_tracemgrrecordadd(fl)  CAL_CMGETAPI( "tracemgrrecordadd" ) 
	#define CAL_tracemgrrecordadd  tracemgrrecordadd
	#define CHK_tracemgrrecordadd  TRUE
	#define EXP_tracemgrrecordadd  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordadd", (RTS_UINTPTR)tracemgrrecordadd, 1, RTSITF_GET_SIGNATURE(0, 0x68ACB311), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrrecordadd
	#define EXT_tracemgrrecordadd
	#define GET_tracemgrrecordadd(fl)  CAL_CMGETAPI( "tracemgrrecordadd" ) 
	#define CAL_tracemgrrecordadd  tracemgrrecordadd
	#define CHK_tracemgrrecordadd  TRUE
	#define EXP_tracemgrrecordadd  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordadd", (RTS_UINTPTR)tracemgrrecordadd, 1, RTSITF_GET_SIGNATURE(0, 0x68ACB311), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrrecordadd
	#define EXT_CmpTraceMgrtracemgrrecordadd
	#define GET_CmpTraceMgrtracemgrrecordadd  ERR_OK
	#define CAL_CmpTraceMgrtracemgrrecordadd  tracemgrrecordadd
	#define CHK_CmpTraceMgrtracemgrrecordadd  TRUE
	#define EXP_CmpTraceMgrtracemgrrecordadd  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordadd", (RTS_UINTPTR)tracemgrrecordadd, 1, RTSITF_GET_SIGNATURE(0, 0x68ACB311), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrrecordadd
	#define EXT_tracemgrrecordadd
	#define GET_tracemgrrecordadd(fl)  CAL_CMGETAPI( "tracemgrrecordadd" ) 
	#define CAL_tracemgrrecordadd  tracemgrrecordadd
	#define CHK_tracemgrrecordadd  TRUE
	#define EXP_tracemgrrecordadd  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordadd", (RTS_UINTPTR)tracemgrrecordadd, 1, RTSITF_GET_SIGNATURE(0, 0x68ACB311), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrrecordadd  PFTRACEMGRRECORDADD_IEC pftracemgrrecordadd;
	#define EXT_tracemgrrecordadd  extern PFTRACEMGRRECORDADD_IEC pftracemgrrecordadd;
	#define GET_tracemgrrecordadd(fl)  s_pfCMGetAPI2( "tracemgrrecordadd", (RTS_VOID_FCTPTR *)&pftracemgrrecordadd, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x68ACB311), 0x03050B00)
	#define CAL_tracemgrrecordadd  pftracemgrrecordadd
	#define CHK_tracemgrrecordadd  (pftracemgrrecordadd != NULL)
	#define EXP_tracemgrrecordadd   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordadd", (RTS_UINTPTR)tracemgrrecordadd, 1, RTSITF_GET_SIGNATURE(0, 0x68ACB311), 0x03050B00) 
#endif


/**
 * Queries the configuration of a trace record.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket or hRecord is not a valid handle
 */
typedef struct tagtracemgrrecordgetconfig_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_HANDLE hRecord;				/* VAR_INPUT */	/* The trace record handle */
	TraceRecordConfiguration *pConfiguration;	/* VAR_IN_OUT */	/* The trace record configuration (out) */
	RTS_IEC_RESULT TraceMgrRecordGetConfig;	/* VAR_OUTPUT */	/* The result code */
} tracemgrrecordgetconfig_struct;

void CDECL CDECL_EXT tracemgrrecordgetconfig(tracemgrrecordgetconfig_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRRECORDGETCONFIG_IEC) (tracemgrrecordgetconfig_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRRECORDGETCONFIG_NOTIMPLEMENTED)
	#define USE_tracemgrrecordgetconfig
	#define EXT_tracemgrrecordgetconfig
	#define GET_tracemgrrecordgetconfig(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrrecordgetconfig(p0) 
	#define CHK_tracemgrrecordgetconfig  FALSE
	#define EXP_tracemgrrecordgetconfig  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrrecordgetconfig
	#define EXT_tracemgrrecordgetconfig
	#define GET_tracemgrrecordgetconfig(fl)  CAL_CMGETAPI( "tracemgrrecordgetconfig" ) 
	#define CAL_tracemgrrecordgetconfig  tracemgrrecordgetconfig
	#define CHK_tracemgrrecordgetconfig  TRUE
	#define EXP_tracemgrrecordgetconfig  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordgetconfig", (RTS_UINTPTR)tracemgrrecordgetconfig, 1, RTSITF_GET_SIGNATURE(0, 0xDAF803A5), 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrrecordgetconfig
	#define EXT_tracemgrrecordgetconfig
	#define GET_tracemgrrecordgetconfig(fl)  CAL_CMGETAPI( "tracemgrrecordgetconfig" ) 
	#define CAL_tracemgrrecordgetconfig  tracemgrrecordgetconfig
	#define CHK_tracemgrrecordgetconfig  TRUE
	#define EXP_tracemgrrecordgetconfig  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordgetconfig", (RTS_UINTPTR)tracemgrrecordgetconfig, 1, RTSITF_GET_SIGNATURE(0, 0xDAF803A5), 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrrecordgetconfig
	#define EXT_CmpTraceMgrtracemgrrecordgetconfig
	#define GET_CmpTraceMgrtracemgrrecordgetconfig  ERR_OK
	#define CAL_CmpTraceMgrtracemgrrecordgetconfig  tracemgrrecordgetconfig
	#define CHK_CmpTraceMgrtracemgrrecordgetconfig  TRUE
	#define EXP_CmpTraceMgrtracemgrrecordgetconfig  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordgetconfig", (RTS_UINTPTR)tracemgrrecordgetconfig, 1, RTSITF_GET_SIGNATURE(0, 0xDAF803A5), 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrrecordgetconfig
	#define EXT_tracemgrrecordgetconfig
	#define GET_tracemgrrecordgetconfig(fl)  CAL_CMGETAPI( "tracemgrrecordgetconfig" ) 
	#define CAL_tracemgrrecordgetconfig  tracemgrrecordgetconfig
	#define CHK_tracemgrrecordgetconfig  TRUE
	#define EXP_tracemgrrecordgetconfig  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordgetconfig", (RTS_UINTPTR)tracemgrrecordgetconfig, 1, RTSITF_GET_SIGNATURE(0, 0xDAF803A5), 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrrecordgetconfig  PFTRACEMGRRECORDGETCONFIG_IEC pftracemgrrecordgetconfig;
	#define EXT_tracemgrrecordgetconfig  extern PFTRACEMGRRECORDGETCONFIG_IEC pftracemgrrecordgetconfig;
	#define GET_tracemgrrecordgetconfig(fl)  s_pfCMGetAPI2( "tracemgrrecordgetconfig", (RTS_VOID_FCTPTR *)&pftracemgrrecordgetconfig, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xDAF803A5), 0x03050B00)
	#define CAL_tracemgrrecordgetconfig  pftracemgrrecordgetconfig
	#define CHK_tracemgrrecordgetconfig  (pftracemgrrecordgetconfig != NULL)
	#define EXP_tracemgrrecordgetconfig   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordgetconfig", (RTS_UINTPTR)tracemgrrecordgetconfig, 1, RTSITF_GET_SIGNATURE(0, 0xDAF803A5), 0x03050B00) 
#endif


/**
 * Returns the first trace record of a trace packet.
 * This function can be used together with |TraceMgrRecordGetNext| to iterate
 * through all trace records of a packet.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket is not a valid packet handle
 *   - ERR_NO_OBJECT if the packet has no trace record
 */
typedef struct tagtracemgrrecordgetfirst_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_RESULT *pResult;			/* VAR_IN_OUT */	/* The result code (out) */
	RTS_IEC_HANDLE TraceMgrRecordGetFirst;	/* VAR_OUTPUT */	/* The record handle, or RTS_INVALID_HANDLE on failure */
} tracemgrrecordgetfirst_struct;

void CDECL CDECL_EXT tracemgrrecordgetfirst(tracemgrrecordgetfirst_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRRECORDGETFIRST_IEC) (tracemgrrecordgetfirst_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRRECORDGETFIRST_NOTIMPLEMENTED)
	#define USE_tracemgrrecordgetfirst
	#define EXT_tracemgrrecordgetfirst
	#define GET_tracemgrrecordgetfirst(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrrecordgetfirst(p0) 
	#define CHK_tracemgrrecordgetfirst  FALSE
	#define EXP_tracemgrrecordgetfirst  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrrecordgetfirst
	#define EXT_tracemgrrecordgetfirst
	#define GET_tracemgrrecordgetfirst(fl)  CAL_CMGETAPI( "tracemgrrecordgetfirst" ) 
	#define CAL_tracemgrrecordgetfirst  tracemgrrecordgetfirst
	#define CHK_tracemgrrecordgetfirst  TRUE
	#define EXP_tracemgrrecordgetfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordgetfirst", (RTS_UINTPTR)tracemgrrecordgetfirst, 1, 0xDE6CF5CE, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrrecordgetfirst
	#define EXT_tracemgrrecordgetfirst
	#define GET_tracemgrrecordgetfirst(fl)  CAL_CMGETAPI( "tracemgrrecordgetfirst" ) 
	#define CAL_tracemgrrecordgetfirst  tracemgrrecordgetfirst
	#define CHK_tracemgrrecordgetfirst  TRUE
	#define EXP_tracemgrrecordgetfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordgetfirst", (RTS_UINTPTR)tracemgrrecordgetfirst, 1, 0xDE6CF5CE, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrrecordgetfirst
	#define EXT_CmpTraceMgrtracemgrrecordgetfirst
	#define GET_CmpTraceMgrtracemgrrecordgetfirst  ERR_OK
	#define CAL_CmpTraceMgrtracemgrrecordgetfirst  tracemgrrecordgetfirst
	#define CHK_CmpTraceMgrtracemgrrecordgetfirst  TRUE
	#define EXP_CmpTraceMgrtracemgrrecordgetfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordgetfirst", (RTS_UINTPTR)tracemgrrecordgetfirst, 1, 0xDE6CF5CE, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrrecordgetfirst
	#define EXT_tracemgrrecordgetfirst
	#define GET_tracemgrrecordgetfirst(fl)  CAL_CMGETAPI( "tracemgrrecordgetfirst" ) 
	#define CAL_tracemgrrecordgetfirst  tracemgrrecordgetfirst
	#define CHK_tracemgrrecordgetfirst  TRUE
	#define EXP_tracemgrrecordgetfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordgetfirst", (RTS_UINTPTR)tracemgrrecordgetfirst, 1, 0xDE6CF5CE, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrrecordgetfirst  PFTRACEMGRRECORDGETFIRST_IEC pftracemgrrecordgetfirst;
	#define EXT_tracemgrrecordgetfirst  extern PFTRACEMGRRECORDGETFIRST_IEC pftracemgrrecordgetfirst;
	#define GET_tracemgrrecordgetfirst(fl)  s_pfCMGetAPI2( "tracemgrrecordgetfirst", (RTS_VOID_FCTPTR *)&pftracemgrrecordgetfirst, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xDE6CF5CE, 0x03050B00)
	#define CAL_tracemgrrecordgetfirst  pftracemgrrecordgetfirst
	#define CHK_tracemgrrecordgetfirst  (pftracemgrrecordgetfirst != NULL)
	#define EXP_tracemgrrecordgetfirst   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordgetfirst", (RTS_UINTPTR)tracemgrrecordgetfirst, 1, 0xDE6CF5CE, 0x03050B00) 
#endif


/**
 * Returns the next trace record of a trace packet.
 * This function can be used together with |TraceMgrRecordGetFirst| to iterate
 * through all trace records of a packet.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket or hPrevRecord is not a valid handle
 *   - ERR_NO_OBJECT if the packet has no next trace record
 */
typedef struct tagtracemgrrecordgetnext_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_HANDLE hPrevRecord;			/* VAR_INPUT */	/* The trace record handle of the current record */
	RTS_IEC_RESULT *pResult;			/* VAR_IN_OUT */	/* The result code (out) */
	RTS_IEC_HANDLE TraceMgrRecordGetNext;	/* VAR_OUTPUT */	/* The handle of the next record or RTS_INVALID_HANDLE on failure */
} tracemgrrecordgetnext_struct;

void CDECL CDECL_EXT tracemgrrecordgetnext(tracemgrrecordgetnext_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRRECORDGETNEXT_IEC) (tracemgrrecordgetnext_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRRECORDGETNEXT_NOTIMPLEMENTED)
	#define USE_tracemgrrecordgetnext
	#define EXT_tracemgrrecordgetnext
	#define GET_tracemgrrecordgetnext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrrecordgetnext(p0) 
	#define CHK_tracemgrrecordgetnext  FALSE
	#define EXP_tracemgrrecordgetnext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrrecordgetnext
	#define EXT_tracemgrrecordgetnext
	#define GET_tracemgrrecordgetnext(fl)  CAL_CMGETAPI( "tracemgrrecordgetnext" ) 
	#define CAL_tracemgrrecordgetnext  tracemgrrecordgetnext
	#define CHK_tracemgrrecordgetnext  TRUE
	#define EXP_tracemgrrecordgetnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordgetnext", (RTS_UINTPTR)tracemgrrecordgetnext, 1, 0xA7463D33, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrrecordgetnext
	#define EXT_tracemgrrecordgetnext
	#define GET_tracemgrrecordgetnext(fl)  CAL_CMGETAPI( "tracemgrrecordgetnext" ) 
	#define CAL_tracemgrrecordgetnext  tracemgrrecordgetnext
	#define CHK_tracemgrrecordgetnext  TRUE
	#define EXP_tracemgrrecordgetnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordgetnext", (RTS_UINTPTR)tracemgrrecordgetnext, 1, 0xA7463D33, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrrecordgetnext
	#define EXT_CmpTraceMgrtracemgrrecordgetnext
	#define GET_CmpTraceMgrtracemgrrecordgetnext  ERR_OK
	#define CAL_CmpTraceMgrtracemgrrecordgetnext  tracemgrrecordgetnext
	#define CHK_CmpTraceMgrtracemgrrecordgetnext  TRUE
	#define EXP_CmpTraceMgrtracemgrrecordgetnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordgetnext", (RTS_UINTPTR)tracemgrrecordgetnext, 1, 0xA7463D33, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrrecordgetnext
	#define EXT_tracemgrrecordgetnext
	#define GET_tracemgrrecordgetnext(fl)  CAL_CMGETAPI( "tracemgrrecordgetnext" ) 
	#define CAL_tracemgrrecordgetnext  tracemgrrecordgetnext
	#define CHK_tracemgrrecordgetnext  TRUE
	#define EXP_tracemgrrecordgetnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordgetnext", (RTS_UINTPTR)tracemgrrecordgetnext, 1, 0xA7463D33, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrrecordgetnext  PFTRACEMGRRECORDGETNEXT_IEC pftracemgrrecordgetnext;
	#define EXT_tracemgrrecordgetnext  extern PFTRACEMGRRECORDGETNEXT_IEC pftracemgrrecordgetnext;
	#define GET_tracemgrrecordgetnext(fl)  s_pfCMGetAPI2( "tracemgrrecordgetnext", (RTS_VOID_FCTPTR *)&pftracemgrrecordgetnext, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xA7463D33, 0x03050B00)
	#define CAL_tracemgrrecordgetnext  pftracemgrrecordgetnext
	#define CHK_tracemgrrecordgetnext  (pftracemgrrecordgetnext != NULL)
	#define EXP_tracemgrrecordgetnext   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordgetnext", (RTS_UINTPTR)tracemgrrecordgetnext, 1, 0xA7463D33, 0x03050B00) 
#endif


/**
 * Removes a trace record from a trace packet.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if the packet handle or the record handle is invalid
 */
typedef struct tagtracemgrrecordremove_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The packet handle */
	RTS_IEC_HANDLE hRecord;				/* VAR_INPUT */	/* The record handle */
	RTS_IEC_RESULT TraceMgrRecordRemove;	/* VAR_OUTPUT */	/* The result code */
} tracemgrrecordremove_struct;

void CDECL CDECL_EXT tracemgrrecordremove(tracemgrrecordremove_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRRECORDREMOVE_IEC) (tracemgrrecordremove_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRRECORDREMOVE_NOTIMPLEMENTED)
	#define USE_tracemgrrecordremove
	#define EXT_tracemgrrecordremove
	#define GET_tracemgrrecordremove(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrrecordremove(p0) 
	#define CHK_tracemgrrecordremove  FALSE
	#define EXP_tracemgrrecordremove  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrrecordremove
	#define EXT_tracemgrrecordremove
	#define GET_tracemgrrecordremove(fl)  CAL_CMGETAPI( "tracemgrrecordremove" ) 
	#define CAL_tracemgrrecordremove  tracemgrrecordremove
	#define CHK_tracemgrrecordremove  TRUE
	#define EXP_tracemgrrecordremove  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordremove", (RTS_UINTPTR)tracemgrrecordremove, 1, 0xA0864F53, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrrecordremove
	#define EXT_tracemgrrecordremove
	#define GET_tracemgrrecordremove(fl)  CAL_CMGETAPI( "tracemgrrecordremove" ) 
	#define CAL_tracemgrrecordremove  tracemgrrecordremove
	#define CHK_tracemgrrecordremove  TRUE
	#define EXP_tracemgrrecordremove  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordremove", (RTS_UINTPTR)tracemgrrecordremove, 1, 0xA0864F53, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrrecordremove
	#define EXT_CmpTraceMgrtracemgrrecordremove
	#define GET_CmpTraceMgrtracemgrrecordremove  ERR_OK
	#define CAL_CmpTraceMgrtracemgrrecordremove  tracemgrrecordremove
	#define CHK_CmpTraceMgrtracemgrrecordremove  TRUE
	#define EXP_CmpTraceMgrtracemgrrecordremove  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordremove", (RTS_UINTPTR)tracemgrrecordremove, 1, 0xA0864F53, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrrecordremove
	#define EXT_tracemgrrecordremove
	#define GET_tracemgrrecordremove(fl)  CAL_CMGETAPI( "tracemgrrecordremove" ) 
	#define CAL_tracemgrrecordremove  tracemgrrecordremove
	#define CHK_tracemgrrecordremove  TRUE
	#define EXP_tracemgrrecordremove  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordremove", (RTS_UINTPTR)tracemgrrecordremove, 1, 0xA0864F53, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrrecordremove  PFTRACEMGRRECORDREMOVE_IEC pftracemgrrecordremove;
	#define EXT_tracemgrrecordremove  extern PFTRACEMGRRECORDREMOVE_IEC pftracemgrrecordremove;
	#define GET_tracemgrrecordremove(fl)  s_pfCMGetAPI2( "tracemgrrecordremove", (RTS_VOID_FCTPTR *)&pftracemgrrecordremove, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xA0864F53, 0x03050B00)
	#define CAL_tracemgrrecordremove  pftracemgrrecordremove
	#define CHK_tracemgrrecordremove  (pftracemgrrecordremove != NULL)
	#define EXP_tracemgrrecordremove   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordremove", (RTS_UINTPTR)tracemgrrecordremove, 1, 0xA0864F53, 0x03050B00) 
#endif


/**
 * Records the current value of the trace variable of a record
 * together with the current time stamp.
 *
 * .. note:: This function is called cyclically by CmpTraceMgr.  It
 *    should not be called by the application.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket or hPrevRecord is not a valid handle
 *   - ERR_NOTINITIALIZED if the packet is not currently recording (not started, trigger reached, ...)
 *   - ERR_PENDING if no value is recorded for this cycle due to TracePacketConfiguration.ulEveryNCycles
 *   - ERR_FAILED if reading the value of the trace variable failed
 */
typedef struct tagtracemgrrecordupdate_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_HANDLE hRecord;				/* VAR_INPUT */	/* The trace record handle */
	RTS_IEC_RESULT TraceMgrRecordUpdate;	/* VAR_OUTPUT */	/* The result code */
} tracemgrrecordupdate_struct;

void CDECL CDECL_EXT tracemgrrecordupdate(tracemgrrecordupdate_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRRECORDUPDATE_IEC) (tracemgrrecordupdate_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRRECORDUPDATE_NOTIMPLEMENTED)
	#define USE_tracemgrrecordupdate
	#define EXT_tracemgrrecordupdate
	#define GET_tracemgrrecordupdate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrrecordupdate(p0) 
	#define CHK_tracemgrrecordupdate  FALSE
	#define EXP_tracemgrrecordupdate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrrecordupdate
	#define EXT_tracemgrrecordupdate
	#define GET_tracemgrrecordupdate(fl)  CAL_CMGETAPI( "tracemgrrecordupdate" ) 
	#define CAL_tracemgrrecordupdate  tracemgrrecordupdate
	#define CHK_tracemgrrecordupdate  TRUE
	#define EXP_tracemgrrecordupdate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordupdate", (RTS_UINTPTR)tracemgrrecordupdate, 1, 0xD9B5E571, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrrecordupdate
	#define EXT_tracemgrrecordupdate
	#define GET_tracemgrrecordupdate(fl)  CAL_CMGETAPI( "tracemgrrecordupdate" ) 
	#define CAL_tracemgrrecordupdate  tracemgrrecordupdate
	#define CHK_tracemgrrecordupdate  TRUE
	#define EXP_tracemgrrecordupdate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordupdate", (RTS_UINTPTR)tracemgrrecordupdate, 1, 0xD9B5E571, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrrecordupdate
	#define EXT_CmpTraceMgrtracemgrrecordupdate
	#define GET_CmpTraceMgrtracemgrrecordupdate  ERR_OK
	#define CAL_CmpTraceMgrtracemgrrecordupdate  tracemgrrecordupdate
	#define CHK_CmpTraceMgrtracemgrrecordupdate  TRUE
	#define EXP_CmpTraceMgrtracemgrrecordupdate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordupdate", (RTS_UINTPTR)tracemgrrecordupdate, 1, 0xD9B5E571, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrrecordupdate
	#define EXT_tracemgrrecordupdate
	#define GET_tracemgrrecordupdate(fl)  CAL_CMGETAPI( "tracemgrrecordupdate" ) 
	#define CAL_tracemgrrecordupdate  tracemgrrecordupdate
	#define CHK_tracemgrrecordupdate  TRUE
	#define EXP_tracemgrrecordupdate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordupdate", (RTS_UINTPTR)tracemgrrecordupdate, 1, 0xD9B5E571, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrrecordupdate  PFTRACEMGRRECORDUPDATE_IEC pftracemgrrecordupdate;
	#define EXT_tracemgrrecordupdate  extern PFTRACEMGRRECORDUPDATE_IEC pftracemgrrecordupdate;
	#define GET_tracemgrrecordupdate(fl)  s_pfCMGetAPI2( "tracemgrrecordupdate", (RTS_VOID_FCTPTR *)&pftracemgrrecordupdate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xD9B5E571, 0x03050B00)
	#define CAL_tracemgrrecordupdate  pftracemgrrecordupdate
	#define CHK_tracemgrrecordupdate  (pftracemgrrecordupdate != NULL)
	#define EXP_tracemgrrecordupdate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordupdate", (RTS_UINTPTR)tracemgrrecordupdate, 1, 0xD9B5E571, 0x03050B00) 
#endif


/**
 * Stores entries in the ring buffer of a trace record.
 *
 * This function can be used to provide the data for so called system parameters
 * from the IEC application. (See |TRACE_VAR_ADDRESS_FLAGS_SYSTEM|.)
 * If only a single entry is to be added, consider using |TraceMgrRecordUpdate3|
 * instead.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket or hPrevRecord is not a valid handle
 *   - ERR_NOTINITIALIZED if the packet is not currently recording (not started, trigger reached, ...)
 *   - ERR_PENDING if no value is recorded for this cycle due to TracePacketConfiguration.ulEveryNCycles
 *   - ERR_FAILED if ulLen is not a multiple of the entry size (size of a time stamp plus a sample value) 
 */
typedef struct tagtracemgrrecordupdate2_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_HANDLE hRecord;				/* VAR_INPUT */	/* The trace record handle */
	TraceRecordEntry *pBuffer;			/* VAR_IN_OUT */	/* A pointer to the buffer of trace entries */
	RTS_IEC_UDINT ulLen;				/* VAR_INPUT */	/* The number of bytes to copy from pBuffer */
	RTS_IEC_RESULT TraceMgrRecordUpdate2;	/* VAR_OUTPUT */	/* The result code */
} tracemgrrecordupdate2_struct;

void CDECL CDECL_EXT tracemgrrecordupdate2(tracemgrrecordupdate2_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRRECORDUPDATE2_IEC) (tracemgrrecordupdate2_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRRECORDUPDATE2_NOTIMPLEMENTED)
	#define USE_tracemgrrecordupdate2
	#define EXT_tracemgrrecordupdate2
	#define GET_tracemgrrecordupdate2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrrecordupdate2(p0) 
	#define CHK_tracemgrrecordupdate2  FALSE
	#define EXP_tracemgrrecordupdate2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrrecordupdate2
	#define EXT_tracemgrrecordupdate2
	#define GET_tracemgrrecordupdate2(fl)  CAL_CMGETAPI( "tracemgrrecordupdate2" ) 
	#define CAL_tracemgrrecordupdate2  tracemgrrecordupdate2
	#define CHK_tracemgrrecordupdate2  TRUE
	#define EXP_tracemgrrecordupdate2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordupdate2", (RTS_UINTPTR)tracemgrrecordupdate2, 1, 0x3FE213B2, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrrecordupdate2
	#define EXT_tracemgrrecordupdate2
	#define GET_tracemgrrecordupdate2(fl)  CAL_CMGETAPI( "tracemgrrecordupdate2" ) 
	#define CAL_tracemgrrecordupdate2  tracemgrrecordupdate2
	#define CHK_tracemgrrecordupdate2  TRUE
	#define EXP_tracemgrrecordupdate2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordupdate2", (RTS_UINTPTR)tracemgrrecordupdate2, 1, 0x3FE213B2, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrrecordupdate2
	#define EXT_CmpTraceMgrtracemgrrecordupdate2
	#define GET_CmpTraceMgrtracemgrrecordupdate2  ERR_OK
	#define CAL_CmpTraceMgrtracemgrrecordupdate2  tracemgrrecordupdate2
	#define CHK_CmpTraceMgrtracemgrrecordupdate2  TRUE
	#define EXP_CmpTraceMgrtracemgrrecordupdate2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordupdate2", (RTS_UINTPTR)tracemgrrecordupdate2, 1, 0x3FE213B2, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrrecordupdate2
	#define EXT_tracemgrrecordupdate2
	#define GET_tracemgrrecordupdate2(fl)  CAL_CMGETAPI( "tracemgrrecordupdate2" ) 
	#define CAL_tracemgrrecordupdate2  tracemgrrecordupdate2
	#define CHK_tracemgrrecordupdate2  TRUE
	#define EXP_tracemgrrecordupdate2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordupdate2", (RTS_UINTPTR)tracemgrrecordupdate2, 1, 0x3FE213B2, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrrecordupdate2  PFTRACEMGRRECORDUPDATE2_IEC pftracemgrrecordupdate2;
	#define EXT_tracemgrrecordupdate2  extern PFTRACEMGRRECORDUPDATE2_IEC pftracemgrrecordupdate2;
	#define GET_tracemgrrecordupdate2(fl)  s_pfCMGetAPI2( "tracemgrrecordupdate2", (RTS_VOID_FCTPTR *)&pftracemgrrecordupdate2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x3FE213B2, 0x03050B00)
	#define CAL_tracemgrrecordupdate2  pftracemgrrecordupdate2
	#define CHK_tracemgrrecordupdate2  (pftracemgrrecordupdate2 != NULL)
	#define EXP_tracemgrrecordupdate2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordupdate2", (RTS_UINTPTR)tracemgrrecordupdate2, 1, 0x3FE213B2, 0x03050B00) 
#endif


/**
 * Stores one entry in the ring buffer of a trace record.
 *
 * This function can be used to provide the data for so called system parameters
 * from the IEC application. (See |TRACE_VAR_ADDRESS_FLAGS_SYSTEM|.)
 * If more than one single entry is to be added, consider using |TraceMgrRecordUpdate2|
 * instead.
 *
 * .. note:: in contrast to |TraceMgrRecordUpdate2|, the time stamp of the entry is not
 *    provided by the caller but set inside |TraceMgrRecordUpdate3|.
 *
 * .. note:: If pData is 0, the current value of the trace variable is read, i.e. the
 *    function behaves TraceMgrRecordUpdate.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket or hPrevRecord is not a valid handle, or if ulLen differs from the size of the trace variable
 *   - ERR_NOTINITIALIZED if the packet is not currently recording (not started, trigger reached, ...)
 *   - ERR_PENDING if no value is recorded for this cycle due to TracePacketConfiguration.ulEveryNCycles
 *   - ERR_FAILED if pData is 0 and the current value of the trace variable cannot be read
 */
typedef struct tagtracemgrrecordupdate3_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_HANDLE hRecord;				/* VAR_INPUT */	/* The trace record handle */
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	/* The address of the variable value to copy, if pData is null the function behaves like |TraceMgrRecordUpdate| */
	RTS_IEC_UDINT ulLen;				/* VAR_INPUT */	/* The length (in bytes) of the variable value */
	RTS_IEC_RESULT TraceMgrRecordUpdate3;	/* VAR_OUTPUT */	/* The result code */
} tracemgrrecordupdate3_struct;

void CDECL CDECL_EXT tracemgrrecordupdate3(tracemgrrecordupdate3_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRRECORDUPDATE3_IEC) (tracemgrrecordupdate3_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRRECORDUPDATE3_NOTIMPLEMENTED)
	#define USE_tracemgrrecordupdate3
	#define EXT_tracemgrrecordupdate3
	#define GET_tracemgrrecordupdate3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrrecordupdate3(p0) 
	#define CHK_tracemgrrecordupdate3  FALSE
	#define EXP_tracemgrrecordupdate3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrrecordupdate3
	#define EXT_tracemgrrecordupdate3
	#define GET_tracemgrrecordupdate3(fl)  CAL_CMGETAPI( "tracemgrrecordupdate3" ) 
	#define CAL_tracemgrrecordupdate3  tracemgrrecordupdate3
	#define CHK_tracemgrrecordupdate3  TRUE
	#define EXP_tracemgrrecordupdate3  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordupdate3", (RTS_UINTPTR)tracemgrrecordupdate3, 1, 0xA5C60449, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrrecordupdate3
	#define EXT_tracemgrrecordupdate3
	#define GET_tracemgrrecordupdate3(fl)  CAL_CMGETAPI( "tracemgrrecordupdate3" ) 
	#define CAL_tracemgrrecordupdate3  tracemgrrecordupdate3
	#define CHK_tracemgrrecordupdate3  TRUE
	#define EXP_tracemgrrecordupdate3  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordupdate3", (RTS_UINTPTR)tracemgrrecordupdate3, 1, 0xA5C60449, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrrecordupdate3
	#define EXT_CmpTraceMgrtracemgrrecordupdate3
	#define GET_CmpTraceMgrtracemgrrecordupdate3  ERR_OK
	#define CAL_CmpTraceMgrtracemgrrecordupdate3  tracemgrrecordupdate3
	#define CHK_CmpTraceMgrtracemgrrecordupdate3  TRUE
	#define EXP_CmpTraceMgrtracemgrrecordupdate3  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordupdate3", (RTS_UINTPTR)tracemgrrecordupdate3, 1, 0xA5C60449, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrrecordupdate3
	#define EXT_tracemgrrecordupdate3
	#define GET_tracemgrrecordupdate3(fl)  CAL_CMGETAPI( "tracemgrrecordupdate3" ) 
	#define CAL_tracemgrrecordupdate3  tracemgrrecordupdate3
	#define CHK_tracemgrrecordupdate3  TRUE
	#define EXP_tracemgrrecordupdate3  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordupdate3", (RTS_UINTPTR)tracemgrrecordupdate3, 1, 0xA5C60449, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrrecordupdate3  PFTRACEMGRRECORDUPDATE3_IEC pftracemgrrecordupdate3;
	#define EXT_tracemgrrecordupdate3  extern PFTRACEMGRRECORDUPDATE3_IEC pftracemgrrecordupdate3;
	#define GET_tracemgrrecordupdate3(fl)  s_pfCMGetAPI2( "tracemgrrecordupdate3", (RTS_VOID_FCTPTR *)&pftracemgrrecordupdate3, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xA5C60449, 0x03050B00)
	#define CAL_tracemgrrecordupdate3  pftracemgrrecordupdate3
	#define CHK_tracemgrrecordupdate3  (pftracemgrrecordupdate3 != NULL)
	#define EXP_tracemgrrecordupdate3   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordupdate3", (RTS_UINTPTR)tracemgrrecordupdate3, 1, 0xA5C60449, 0x03050B00) 
#endif


/**
 * Stores multiple values with seperate timestamps in the ring buffer of a trace record.
 *
 * This function can be used to provide the data for so called system parameters
 * from the IEC application. (See |TRACE_VAR_ADDRESS_FLAGS_SYSTEM|.)
 *
 * .. note:: in contrast to |TraceMgrRecordUpdate2|, the timestamp of the values and the
 *    values itself are provided in seperate lists by the caller.
 *
 * .. note:: the number of timestamps must be the same as the number of data values. ulEntries must match to this number.
 *
 * :return: Returns the runtime system error code (see CmpErrors.library):
 *   - ERR_PARAMETER if hPacket or hPrevRecord is not a valid handle
 *   - ERR_NOTINITIALIZED if the packet is not currently recording (not started, trigger reached, ...)
 *   - ERR_PENDING if no value is recorded for this cycle due to TracePacketConfiguration.ulEveryNCycles
 */
typedef struct tagtracemgrrecordupdate4_struct
{
	RTS_IEC_HANDLE hPacket;				/* VAR_INPUT */	/* The trace packet handle */
	RTS_IEC_HANDLE hRecord;				/* VAR_INPUT */	/* The trace record handle */
	RTS_IEC_UDINT *pTimestamps;			/* VAR_INPUT */	/* The address of the first timestamp of the variable values */
	RTS_IEC_BYTE *pDataValues;			/* VAR_INPUT */	/* The address of the first variable value of the list to copy */
	RTS_IEC_UDINT ulEntries;			/* VAR_INPUT */	/* The number of variables to be updated */
	RTS_IEC_RESULT TraceMgrRecordUpdate4;	/* VAR_OUTPUT */	/* The result code */
} tracemgrrecordupdate4_struct;

void CDECL CDECL_EXT tracemgrrecordupdate4(tracemgrrecordupdate4_struct *p);
typedef void (CDECL CDECL_EXT* PFTRACEMGRRECORDUPDATE4_IEC) (tracemgrrecordupdate4_struct *p);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRRECORDUPDATE4_NOTIMPLEMENTED)
	#define USE_tracemgrrecordupdate4
	#define EXT_tracemgrrecordupdate4
	#define GET_tracemgrrecordupdate4(fl)  ERR_NOTIMPLEMENTED
	#define CAL_tracemgrrecordupdate4(p0) 
	#define CHK_tracemgrrecordupdate4  FALSE
	#define EXP_tracemgrrecordupdate4  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_tracemgrrecordupdate4
	#define EXT_tracemgrrecordupdate4
	#define GET_tracemgrrecordupdate4(fl)  CAL_CMGETAPI( "tracemgrrecordupdate4" ) 
	#define CAL_tracemgrrecordupdate4  tracemgrrecordupdate4
	#define CHK_tracemgrrecordupdate4  TRUE
	#define EXP_tracemgrrecordupdate4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordupdate4", (RTS_UINTPTR)tracemgrrecordupdate4, 1, 0x72F1828D, 0x03050B00) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_tracemgrrecordupdate4
	#define EXT_tracemgrrecordupdate4
	#define GET_tracemgrrecordupdate4(fl)  CAL_CMGETAPI( "tracemgrrecordupdate4" ) 
	#define CAL_tracemgrrecordupdate4  tracemgrrecordupdate4
	#define CHK_tracemgrrecordupdate4  TRUE
	#define EXP_tracemgrrecordupdate4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordupdate4", (RTS_UINTPTR)tracemgrrecordupdate4, 1, 0x72F1828D, 0x03050B00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrtracemgrrecordupdate4
	#define EXT_CmpTraceMgrtracemgrrecordupdate4
	#define GET_CmpTraceMgrtracemgrrecordupdate4  ERR_OK
	#define CAL_CmpTraceMgrtracemgrrecordupdate4  tracemgrrecordupdate4
	#define CHK_CmpTraceMgrtracemgrrecordupdate4  TRUE
	#define EXP_CmpTraceMgrtracemgrrecordupdate4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordupdate4", (RTS_UINTPTR)tracemgrrecordupdate4, 1, 0x72F1828D, 0x03050B00) 
#elif defined(CPLUSPLUS)
	#define USE_tracemgrrecordupdate4
	#define EXT_tracemgrrecordupdate4
	#define GET_tracemgrrecordupdate4(fl)  CAL_CMGETAPI( "tracemgrrecordupdate4" ) 
	#define CAL_tracemgrrecordupdate4  tracemgrrecordupdate4
	#define CHK_tracemgrrecordupdate4  TRUE
	#define EXP_tracemgrrecordupdate4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordupdate4", (RTS_UINTPTR)tracemgrrecordupdate4, 1, 0x72F1828D, 0x03050B00) 
#else /* DYNAMIC_LINK */
	#define USE_tracemgrrecordupdate4  PFTRACEMGRRECORDUPDATE4_IEC pftracemgrrecordupdate4;
	#define EXT_tracemgrrecordupdate4  extern PFTRACEMGRRECORDUPDATE4_IEC pftracemgrrecordupdate4;
	#define GET_tracemgrrecordupdate4(fl)  s_pfCMGetAPI2( "tracemgrrecordupdate4", (RTS_VOID_FCTPTR *)&pftracemgrrecordupdate4, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x72F1828D, 0x03050B00)
	#define CAL_tracemgrrecordupdate4  pftracemgrrecordupdate4
	#define CHK_tracemgrrecordupdate4  (pftracemgrrecordupdate4 != NULL)
	#define EXP_tracemgrrecordupdate4   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"tracemgrrecordupdate4", (RTS_UINTPTR)tracemgrrecordupdate4, 1, 0x72F1828D, 0x03050B00) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


/**
 * <category>TraceString</category>
 * <description>String handling of a name</description>
 * <element name="psz" type="IN">Pointer to the string value, if it is larger than TRACE_MAX_NAME_LEN</element>
 * <element name="sz" type="IN">String value, if the name is shorter than TRACE_MAX_NAME_LEN</element>
 */
typedef union tagTraceString
{
	char *psz;	
	char sz[TRACE_MAX_NAME_LEN];
} TraceString;

/**
 * <category>TraceName</category>
 * <description>Name handling</description>
 * <element name="bDynamic" type="IN">1=String.psz contains the name, 0=String.sz contains the name</element>
 * <element name="sz" type="IN">String value, if the name is shorter than TRACE_MAX_NAME_LEN</element>
 */
typedef struct tagTraceName
{
	RTS_UI32 bDynamic;
	TraceString String;
} TraceName;

/**
 * <category>TraceIecScope</category>
 * <description>Full scope of a trace in IEC</description>
 * <element name="hIecTask" type="IN">Handle to the IEC, in which context the trace is recorded</element>
 * <element name="pApp" type="IN">Application in which context the IEC-trace is started</element>
 * <element name="tnIecTaskName" type="IN">IEC-task name, in which context the trace is recorded</element>
 */
typedef struct tagTraceIecScope
{
	RTS_HANDLE hIecTask;
	APPLICATION *pApp;
	TraceName tnIecTaskName;
} TraceIecScope;

/**
 * <category>TracePacket</category>
 * <description>Internal usage</description>
 */
typedef struct tagTracePacket
{
	TraceName tnName;
	TraceTrigger ttTrigger;
	TraceState tsState;
	/* Timestamp, when the packet was modified (e.g. record added, record deleted) last time. */
	RTS_UI32 ulModificationTimestamp;
	/* Absolute timestamp, when the packet was started. */
	RTS_UI64 ulAbsoluteStartTimestamp;
	TraceIecScope tisScope;
	RTS_UI32 ulEveryNCycles;
	TraceVariable tvCondition;
	RTS_UI32 ulFlags;
	RTS_UI32 ulBufferEntries;
	RTS_UI32 ulUpdatesAfterTrigger;

	TriggerValue ttvOldTriggerValue;
	TraceName tnTrigger;
	TraceName tnCondition;
	TraceName tnComment;
	RTS_HANDLE hRecordPool;
	unsigned char byRecordPool[MEM_GET_STATIC_LEN_(0,0)];
	TraceName tnFileName;
} TracePacket;

/**
 * <category>Trace record flags</category>
 * <element name="TRACE_RECORD_FLAGS_SYNC" type="IN">Only used for atomar synchronization of writing and reading the record</element>
 */
#define TRACE_RECORD_FLAGS_SYNC						0x00000001


/**
 * <category>TraceRecord</category>
 * <description>Internal usage</description>
 */
typedef struct tagTraceRecord
{
	TraceVariable tvVariable;
	TraceName tnVariable;
	RTS_UI32 ulState;
	RTS_UI32 ulCurrentPos;
	RTS_UI32 ulEndPos;
	RTS_UI32 ulEntrySize;
	RTS_UI32 ulBufferSize;
	RTS_UI32 ulCountUpdatesAfterTrigger;
	TraceRecordEntry *pBuffer;
	RTS_UI32 ulGraphColor;
	RTS_UI32 ulGraphType;
	RTS_UI32 ulMinWarningColor;
	RTS_UI32 ulMaxWarningColor;
	RTS_UI32 ulCycles;
	float fCriticalLowerLimit;
	float fCriticalUpperLimit;
	RTS_UI8 bActivateMinWarning;
	RTS_UI8 bActivateMaxWarning;
	RTS_UI8 byYAxis;
	RTS_UI32 ulFlags;
} TraceRecord;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Function to create a new trace packet</description>
 * <param name="pConfiguration" type="IN">Pointer to the trace packet configuration. See category "TracePacketConfiguration" for details.</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the created trace packet</result>
 */
RTS_HANDLE CDECL TraceMgrPacketCreate(TracePacketConfiguration *pConfiguration, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFTRACEMGRPACKETCREATE) (TracePacketConfiguration *pConfiguration, RTS_RESULT *pResult);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETCREATE_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketCreate
	#define EXT_TraceMgrPacketCreate
	#define GET_TraceMgrPacketCreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketCreate(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_TraceMgrPacketCreate  FALSE
	#define EXP_TraceMgrPacketCreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketCreate
	#define EXT_TraceMgrPacketCreate
	#define GET_TraceMgrPacketCreate(fl)  CAL_CMGETAPI( "TraceMgrPacketCreate" ) 
	#define CAL_TraceMgrPacketCreate  TraceMgrPacketCreate
	#define CHK_TraceMgrPacketCreate  TRUE
	#define EXP_TraceMgrPacketCreate  CAL_CMEXPAPI( "TraceMgrPacketCreate" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketCreate
	#define EXT_TraceMgrPacketCreate
	#define GET_TraceMgrPacketCreate(fl)  CAL_CMGETAPI( "TraceMgrPacketCreate" ) 
	#define CAL_TraceMgrPacketCreate  TraceMgrPacketCreate
	#define CHK_TraceMgrPacketCreate  TRUE
	#define EXP_TraceMgrPacketCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketCreate", (RTS_UINTPTR)TraceMgrPacketCreate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketCreate
	#define EXT_CmpTraceMgrTraceMgrPacketCreate
	#define GET_CmpTraceMgrTraceMgrPacketCreate  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketCreate pICmpTraceMgr->ITraceMgrPacketCreate
	#define CHK_CmpTraceMgrTraceMgrPacketCreate (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketCreate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketCreate
	#define EXT_TraceMgrPacketCreate
	#define GET_TraceMgrPacketCreate(fl)  CAL_CMGETAPI( "TraceMgrPacketCreate" ) 
	#define CAL_TraceMgrPacketCreate pICmpTraceMgr->ITraceMgrPacketCreate
	#define CHK_TraceMgrPacketCreate (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketCreate  CAL_CMEXPAPI( "TraceMgrPacketCreate" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketCreate  PFTRACEMGRPACKETCREATE pfTraceMgrPacketCreate;
	#define EXT_TraceMgrPacketCreate  extern PFTRACEMGRPACKETCREATE pfTraceMgrPacketCreate;
	#define GET_TraceMgrPacketCreate(fl)  s_pfCMGetAPI2( "TraceMgrPacketCreate", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketCreate, (fl), 0, 0)
	#define CAL_TraceMgrPacketCreate  pfTraceMgrPacketCreate
	#define CHK_TraceMgrPacketCreate  (pfTraceMgrPacketCreate != NULL)
	#define EXP_TraceMgrPacketCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketCreate", (RTS_UINTPTR)TraceMgrPacketCreate, 0, 0) 
#endif




/**
 * <description>Function to delete trace packet specified by handle</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrPacketDelete(RTS_HANDLE hPacket);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETDELETE) (RTS_HANDLE hPacket);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETDELETE_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketDelete
	#define EXT_TraceMgrPacketDelete
	#define GET_TraceMgrPacketDelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketDelete(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketDelete  FALSE
	#define EXP_TraceMgrPacketDelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketDelete
	#define EXT_TraceMgrPacketDelete
	#define GET_TraceMgrPacketDelete(fl)  CAL_CMGETAPI( "TraceMgrPacketDelete" ) 
	#define CAL_TraceMgrPacketDelete  TraceMgrPacketDelete
	#define CHK_TraceMgrPacketDelete  TRUE
	#define EXP_TraceMgrPacketDelete  CAL_CMEXPAPI( "TraceMgrPacketDelete" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketDelete
	#define EXT_TraceMgrPacketDelete
	#define GET_TraceMgrPacketDelete(fl)  CAL_CMGETAPI( "TraceMgrPacketDelete" ) 
	#define CAL_TraceMgrPacketDelete  TraceMgrPacketDelete
	#define CHK_TraceMgrPacketDelete  TRUE
	#define EXP_TraceMgrPacketDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketDelete", (RTS_UINTPTR)TraceMgrPacketDelete, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketDelete
	#define EXT_CmpTraceMgrTraceMgrPacketDelete
	#define GET_CmpTraceMgrTraceMgrPacketDelete  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketDelete pICmpTraceMgr->ITraceMgrPacketDelete
	#define CHK_CmpTraceMgrTraceMgrPacketDelete (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketDelete  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketDelete
	#define EXT_TraceMgrPacketDelete
	#define GET_TraceMgrPacketDelete(fl)  CAL_CMGETAPI( "TraceMgrPacketDelete" ) 
	#define CAL_TraceMgrPacketDelete pICmpTraceMgr->ITraceMgrPacketDelete
	#define CHK_TraceMgrPacketDelete (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketDelete  CAL_CMEXPAPI( "TraceMgrPacketDelete" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketDelete  PFTRACEMGRPACKETDELETE pfTraceMgrPacketDelete;
	#define EXT_TraceMgrPacketDelete  extern PFTRACEMGRPACKETDELETE pfTraceMgrPacketDelete;
	#define GET_TraceMgrPacketDelete(fl)  s_pfCMGetAPI2( "TraceMgrPacketDelete", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketDelete, (fl), 0, 0)
	#define CAL_TraceMgrPacketDelete  pfTraceMgrPacketDelete
	#define CHK_TraceMgrPacketDelete  (pfTraceMgrPacketDelete != NULL)
	#define EXP_TraceMgrPacketDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketDelete", (RTS_UINTPTR)TraceMgrPacketDelete, 0, 0) 
#endif





/**
 * <description>Open a trace packet specified by name</description>
 * <param name="pszName" type="IN">Handle to the trace packet</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the trace packet</result>
 */
RTS_HANDLE CDECL TraceMgrPacketOpen(char *pszName, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFTRACEMGRPACKETOPEN) (char *pszName, RTS_RESULT *pResult);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETOPEN_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketOpen
	#define EXT_TraceMgrPacketOpen
	#define GET_TraceMgrPacketOpen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketOpen(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_TraceMgrPacketOpen  FALSE
	#define EXP_TraceMgrPacketOpen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketOpen
	#define EXT_TraceMgrPacketOpen
	#define GET_TraceMgrPacketOpen(fl)  CAL_CMGETAPI( "TraceMgrPacketOpen" ) 
	#define CAL_TraceMgrPacketOpen  TraceMgrPacketOpen
	#define CHK_TraceMgrPacketOpen  TRUE
	#define EXP_TraceMgrPacketOpen  CAL_CMEXPAPI( "TraceMgrPacketOpen" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketOpen
	#define EXT_TraceMgrPacketOpen
	#define GET_TraceMgrPacketOpen(fl)  CAL_CMGETAPI( "TraceMgrPacketOpen" ) 
	#define CAL_TraceMgrPacketOpen  TraceMgrPacketOpen
	#define CHK_TraceMgrPacketOpen  TRUE
	#define EXP_TraceMgrPacketOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketOpen", (RTS_UINTPTR)TraceMgrPacketOpen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketOpen
	#define EXT_CmpTraceMgrTraceMgrPacketOpen
	#define GET_CmpTraceMgrTraceMgrPacketOpen  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketOpen pICmpTraceMgr->ITraceMgrPacketOpen
	#define CHK_CmpTraceMgrTraceMgrPacketOpen (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketOpen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketOpen
	#define EXT_TraceMgrPacketOpen
	#define GET_TraceMgrPacketOpen(fl)  CAL_CMGETAPI( "TraceMgrPacketOpen" ) 
	#define CAL_TraceMgrPacketOpen pICmpTraceMgr->ITraceMgrPacketOpen
	#define CHK_TraceMgrPacketOpen (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketOpen  CAL_CMEXPAPI( "TraceMgrPacketOpen" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketOpen  PFTRACEMGRPACKETOPEN pfTraceMgrPacketOpen;
	#define EXT_TraceMgrPacketOpen  extern PFTRACEMGRPACKETOPEN pfTraceMgrPacketOpen;
	#define GET_TraceMgrPacketOpen(fl)  s_pfCMGetAPI2( "TraceMgrPacketOpen", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketOpen, (fl), 0, 0)
	#define CAL_TraceMgrPacketOpen  pfTraceMgrPacketOpen
	#define CHK_TraceMgrPacketOpen  (pfTraceMgrPacketOpen != NULL)
	#define EXP_TraceMgrPacketOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketOpen", (RTS_UINTPTR)TraceMgrPacketOpen, 0, 0) 
#endif




/**
 * <description>Function closed a trace packet specified by handle</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrPacketClose(RTS_HANDLE hPacket);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETCLOSE) (RTS_HANDLE hPacket);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETCLOSE_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketClose
	#define EXT_TraceMgrPacketClose
	#define GET_TraceMgrPacketClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketClose(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketClose  FALSE
	#define EXP_TraceMgrPacketClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketClose
	#define EXT_TraceMgrPacketClose
	#define GET_TraceMgrPacketClose(fl)  CAL_CMGETAPI( "TraceMgrPacketClose" ) 
	#define CAL_TraceMgrPacketClose  TraceMgrPacketClose
	#define CHK_TraceMgrPacketClose  TRUE
	#define EXP_TraceMgrPacketClose  CAL_CMEXPAPI( "TraceMgrPacketClose" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketClose
	#define EXT_TraceMgrPacketClose
	#define GET_TraceMgrPacketClose(fl)  CAL_CMGETAPI( "TraceMgrPacketClose" ) 
	#define CAL_TraceMgrPacketClose  TraceMgrPacketClose
	#define CHK_TraceMgrPacketClose  TRUE
	#define EXP_TraceMgrPacketClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketClose", (RTS_UINTPTR)TraceMgrPacketClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketClose
	#define EXT_CmpTraceMgrTraceMgrPacketClose
	#define GET_CmpTraceMgrTraceMgrPacketClose  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketClose pICmpTraceMgr->ITraceMgrPacketClose
	#define CHK_CmpTraceMgrTraceMgrPacketClose (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketClose
	#define EXT_TraceMgrPacketClose
	#define GET_TraceMgrPacketClose(fl)  CAL_CMGETAPI( "TraceMgrPacketClose" ) 
	#define CAL_TraceMgrPacketClose pICmpTraceMgr->ITraceMgrPacketClose
	#define CHK_TraceMgrPacketClose (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketClose  CAL_CMEXPAPI( "TraceMgrPacketClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketClose  PFTRACEMGRPACKETCLOSE pfTraceMgrPacketClose;
	#define EXT_TraceMgrPacketClose  extern PFTRACEMGRPACKETCLOSE pfTraceMgrPacketClose;
	#define GET_TraceMgrPacketClose(fl)  s_pfCMGetAPI2( "TraceMgrPacketClose", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketClose, (fl), 0, 0)
	#define CAL_TraceMgrPacketClose  pfTraceMgrPacketClose
	#define CHK_TraceMgrPacketClose  (pfTraceMgrPacketClose != NULL)
	#define EXP_TraceMgrPacketClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketClose", (RTS_UINTPTR)TraceMgrPacketClose, 0, 0) 
#endif





/**
 * <description>Complete a trace packet to finish configuration</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrPacketComplete(RTS_HANDLE hPacket);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETCOMPLETE) (RTS_HANDLE hPacket);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETCOMPLETE_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketComplete
	#define EXT_TraceMgrPacketComplete
	#define GET_TraceMgrPacketComplete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketComplete(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketComplete  FALSE
	#define EXP_TraceMgrPacketComplete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketComplete
	#define EXT_TraceMgrPacketComplete
	#define GET_TraceMgrPacketComplete(fl)  CAL_CMGETAPI( "TraceMgrPacketComplete" ) 
	#define CAL_TraceMgrPacketComplete  TraceMgrPacketComplete
	#define CHK_TraceMgrPacketComplete  TRUE
	#define EXP_TraceMgrPacketComplete  CAL_CMEXPAPI( "TraceMgrPacketComplete" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketComplete
	#define EXT_TraceMgrPacketComplete
	#define GET_TraceMgrPacketComplete(fl)  CAL_CMGETAPI( "TraceMgrPacketComplete" ) 
	#define CAL_TraceMgrPacketComplete  TraceMgrPacketComplete
	#define CHK_TraceMgrPacketComplete  TRUE
	#define EXP_TraceMgrPacketComplete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketComplete", (RTS_UINTPTR)TraceMgrPacketComplete, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketComplete
	#define EXT_CmpTraceMgrTraceMgrPacketComplete
	#define GET_CmpTraceMgrTraceMgrPacketComplete  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketComplete pICmpTraceMgr->ITraceMgrPacketComplete
	#define CHK_CmpTraceMgrTraceMgrPacketComplete (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketComplete  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketComplete
	#define EXT_TraceMgrPacketComplete
	#define GET_TraceMgrPacketComplete(fl)  CAL_CMGETAPI( "TraceMgrPacketComplete" ) 
	#define CAL_TraceMgrPacketComplete pICmpTraceMgr->ITraceMgrPacketComplete
	#define CHK_TraceMgrPacketComplete (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketComplete  CAL_CMEXPAPI( "TraceMgrPacketComplete" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketComplete  PFTRACEMGRPACKETCOMPLETE pfTraceMgrPacketComplete;
	#define EXT_TraceMgrPacketComplete  extern PFTRACEMGRPACKETCOMPLETE pfTraceMgrPacketComplete;
	#define GET_TraceMgrPacketComplete(fl)  s_pfCMGetAPI2( "TraceMgrPacketComplete", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketComplete, (fl), 0, 0)
	#define CAL_TraceMgrPacketComplete  pfTraceMgrPacketComplete
	#define CHK_TraceMgrPacketComplete  (pfTraceMgrPacketComplete != NULL)
	#define EXP_TraceMgrPacketComplete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketComplete", (RTS_UINTPTR)TraceMgrPacketComplete, 0, 0) 
#endif




/**
 * <description>Get the configuration of a specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="pConfiguration" type="OUT">Pointer to the trace packet configuration</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrPacketGetConfig(RTS_HANDLE hPacket, TracePacketConfiguration *pConfiguration);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETGETCONFIG) (RTS_HANDLE hPacket, TracePacketConfiguration *pConfiguration);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETGETCONFIG_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketGetConfig
	#define EXT_TraceMgrPacketGetConfig
	#define GET_TraceMgrPacketGetConfig(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketGetConfig(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketGetConfig  FALSE
	#define EXP_TraceMgrPacketGetConfig  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketGetConfig
	#define EXT_TraceMgrPacketGetConfig
	#define GET_TraceMgrPacketGetConfig(fl)  CAL_CMGETAPI( "TraceMgrPacketGetConfig" ) 
	#define CAL_TraceMgrPacketGetConfig  TraceMgrPacketGetConfig
	#define CHK_TraceMgrPacketGetConfig  TRUE
	#define EXP_TraceMgrPacketGetConfig  CAL_CMEXPAPI( "TraceMgrPacketGetConfig" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketGetConfig
	#define EXT_TraceMgrPacketGetConfig
	#define GET_TraceMgrPacketGetConfig(fl)  CAL_CMGETAPI( "TraceMgrPacketGetConfig" ) 
	#define CAL_TraceMgrPacketGetConfig  TraceMgrPacketGetConfig
	#define CHK_TraceMgrPacketGetConfig  TRUE
	#define EXP_TraceMgrPacketGetConfig  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketGetConfig", (RTS_UINTPTR)TraceMgrPacketGetConfig, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketGetConfig
	#define EXT_CmpTraceMgrTraceMgrPacketGetConfig
	#define GET_CmpTraceMgrTraceMgrPacketGetConfig  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketGetConfig pICmpTraceMgr->ITraceMgrPacketGetConfig
	#define CHK_CmpTraceMgrTraceMgrPacketGetConfig (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketGetConfig  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketGetConfig
	#define EXT_TraceMgrPacketGetConfig
	#define GET_TraceMgrPacketGetConfig(fl)  CAL_CMGETAPI( "TraceMgrPacketGetConfig" ) 
	#define CAL_TraceMgrPacketGetConfig pICmpTraceMgr->ITraceMgrPacketGetConfig
	#define CHK_TraceMgrPacketGetConfig (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketGetConfig  CAL_CMEXPAPI( "TraceMgrPacketGetConfig" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketGetConfig  PFTRACEMGRPACKETGETCONFIG pfTraceMgrPacketGetConfig;
	#define EXT_TraceMgrPacketGetConfig  extern PFTRACEMGRPACKETGETCONFIG pfTraceMgrPacketGetConfig;
	#define GET_TraceMgrPacketGetConfig(fl)  s_pfCMGetAPI2( "TraceMgrPacketGetConfig", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketGetConfig, (fl), 0, 0)
	#define CAL_TraceMgrPacketGetConfig  pfTraceMgrPacketGetConfig
	#define CHK_TraceMgrPacketGetConfig  (pfTraceMgrPacketGetConfig != NULL)
	#define EXP_TraceMgrPacketGetConfig  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketGetConfig", (RTS_UINTPTR)TraceMgrPacketGetConfig, 0, 0) 
#endif




/**
 * <description>Get the start time of a trace packet. 0 if trace packet is not started.</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="pStartTime" type="OUT">Pointer to start time</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrPacketGetStartTime(RTS_HANDLE hPacket, RTS_SYSTIME *pStartTime);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETGETSTARTTIME) (RTS_HANDLE hPacket, RTS_SYSTIME *pStartTime);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETGETSTARTTIME_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketGetStartTime
	#define EXT_TraceMgrPacketGetStartTime
	#define GET_TraceMgrPacketGetStartTime(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketGetStartTime(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketGetStartTime  FALSE
	#define EXP_TraceMgrPacketGetStartTime  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketGetStartTime
	#define EXT_TraceMgrPacketGetStartTime
	#define GET_TraceMgrPacketGetStartTime(fl)  CAL_CMGETAPI( "TraceMgrPacketGetStartTime" ) 
	#define CAL_TraceMgrPacketGetStartTime  TraceMgrPacketGetStartTime
	#define CHK_TraceMgrPacketGetStartTime  TRUE
	#define EXP_TraceMgrPacketGetStartTime  CAL_CMEXPAPI( "TraceMgrPacketGetStartTime" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketGetStartTime
	#define EXT_TraceMgrPacketGetStartTime
	#define GET_TraceMgrPacketGetStartTime(fl)  CAL_CMGETAPI( "TraceMgrPacketGetStartTime" ) 
	#define CAL_TraceMgrPacketGetStartTime  TraceMgrPacketGetStartTime
	#define CHK_TraceMgrPacketGetStartTime  TRUE
	#define EXP_TraceMgrPacketGetStartTime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketGetStartTime", (RTS_UINTPTR)TraceMgrPacketGetStartTime, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketGetStartTime
	#define EXT_CmpTraceMgrTraceMgrPacketGetStartTime
	#define GET_CmpTraceMgrTraceMgrPacketGetStartTime  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketGetStartTime pICmpTraceMgr->ITraceMgrPacketGetStartTime
	#define CHK_CmpTraceMgrTraceMgrPacketGetStartTime (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketGetStartTime  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketGetStartTime
	#define EXT_TraceMgrPacketGetStartTime
	#define GET_TraceMgrPacketGetStartTime(fl)  CAL_CMGETAPI( "TraceMgrPacketGetStartTime" ) 
	#define CAL_TraceMgrPacketGetStartTime pICmpTraceMgr->ITraceMgrPacketGetStartTime
	#define CHK_TraceMgrPacketGetStartTime (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketGetStartTime  CAL_CMEXPAPI( "TraceMgrPacketGetStartTime" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketGetStartTime  PFTRACEMGRPACKETGETSTARTTIME pfTraceMgrPacketGetStartTime;
	#define EXT_TraceMgrPacketGetStartTime  extern PFTRACEMGRPACKETGETSTARTTIME pfTraceMgrPacketGetStartTime;
	#define GET_TraceMgrPacketGetStartTime(fl)  s_pfCMGetAPI2( "TraceMgrPacketGetStartTime", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketGetStartTime, (fl), 0, 0)
	#define CAL_TraceMgrPacketGetStartTime  pfTraceMgrPacketGetStartTime
	#define CHK_TraceMgrPacketGetStartTime  (pfTraceMgrPacketGetStartTime != NULL)
	#define EXP_TraceMgrPacketGetStartTime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketGetStartTime", (RTS_UINTPTR)TraceMgrPacketGetStartTime, 0, 0) 
#endif




/**
 * <description>Get the absolute start time of a trace packet. 0 if trace packet is not started.</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="pStartTime" type="OUT">Pointer to start time</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrPacketGetAbsoluteStartTime(RTS_HANDLE hPacket, RTS_SYSTIME *pStartTime);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETGETABSOLUTESTARTTIME) (RTS_HANDLE hPacket, RTS_SYSTIME *pStartTime);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETGETABSOLUTESTARTTIME_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketGetAbsoluteStartTime
	#define EXT_TraceMgrPacketGetAbsoluteStartTime
	#define GET_TraceMgrPacketGetAbsoluteStartTime(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketGetAbsoluteStartTime(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketGetAbsoluteStartTime  FALSE
	#define EXP_TraceMgrPacketGetAbsoluteStartTime  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketGetAbsoluteStartTime
	#define EXT_TraceMgrPacketGetAbsoluteStartTime
	#define GET_TraceMgrPacketGetAbsoluteStartTime(fl)  CAL_CMGETAPI( "TraceMgrPacketGetAbsoluteStartTime" ) 
	#define CAL_TraceMgrPacketGetAbsoluteStartTime  TraceMgrPacketGetAbsoluteStartTime
	#define CHK_TraceMgrPacketGetAbsoluteStartTime  TRUE
	#define EXP_TraceMgrPacketGetAbsoluteStartTime  CAL_CMEXPAPI( "TraceMgrPacketGetAbsoluteStartTime" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketGetAbsoluteStartTime
	#define EXT_TraceMgrPacketGetAbsoluteStartTime
	#define GET_TraceMgrPacketGetAbsoluteStartTime(fl)  CAL_CMGETAPI( "TraceMgrPacketGetAbsoluteStartTime" ) 
	#define CAL_TraceMgrPacketGetAbsoluteStartTime  TraceMgrPacketGetAbsoluteStartTime
	#define CHK_TraceMgrPacketGetAbsoluteStartTime  TRUE
	#define EXP_TraceMgrPacketGetAbsoluteStartTime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketGetAbsoluteStartTime", (RTS_UINTPTR)TraceMgrPacketGetAbsoluteStartTime, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketGetAbsoluteStartTime
	#define EXT_CmpTraceMgrTraceMgrPacketGetAbsoluteStartTime
	#define GET_CmpTraceMgrTraceMgrPacketGetAbsoluteStartTime  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketGetAbsoluteStartTime pICmpTraceMgr->ITraceMgrPacketGetAbsoluteStartTime
	#define CHK_CmpTraceMgrTraceMgrPacketGetAbsoluteStartTime (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketGetAbsoluteStartTime  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketGetAbsoluteStartTime
	#define EXT_TraceMgrPacketGetAbsoluteStartTime
	#define GET_TraceMgrPacketGetAbsoluteStartTime(fl)  CAL_CMGETAPI( "TraceMgrPacketGetAbsoluteStartTime" ) 
	#define CAL_TraceMgrPacketGetAbsoluteStartTime pICmpTraceMgr->ITraceMgrPacketGetAbsoluteStartTime
	#define CHK_TraceMgrPacketGetAbsoluteStartTime (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketGetAbsoluteStartTime  CAL_CMEXPAPI( "TraceMgrPacketGetAbsoluteStartTime" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketGetAbsoluteStartTime  PFTRACEMGRPACKETGETABSOLUTESTARTTIME pfTraceMgrPacketGetAbsoluteStartTime;
	#define EXT_TraceMgrPacketGetAbsoluteStartTime  extern PFTRACEMGRPACKETGETABSOLUTESTARTTIME pfTraceMgrPacketGetAbsoluteStartTime;
	#define GET_TraceMgrPacketGetAbsoluteStartTime(fl)  s_pfCMGetAPI2( "TraceMgrPacketGetAbsoluteStartTime", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketGetAbsoluteStartTime, (fl), 0, 0)
	#define CAL_TraceMgrPacketGetAbsoluteStartTime  pfTraceMgrPacketGetAbsoluteStartTime
	#define CHK_TraceMgrPacketGetAbsoluteStartTime  (pfTraceMgrPacketGetAbsoluteStartTime != NULL)
	#define EXP_TraceMgrPacketGetAbsoluteStartTime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketGetAbsoluteStartTime", (RTS_UINTPTR)TraceMgrPacketGetAbsoluteStartTime, 0, 0) 
#endif




/**
 * <description>Returns the timestamp of a trace packet's last modification.</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="pdwTimestamp" type="OUT">Pointer to timestamp</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrPacketGetChangeTimestamp(RTS_HANDLE hPacket, RTS_UI32 *pdwTimestamp);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETGETCHANGETIMESTAMP) (RTS_HANDLE hPacket, RTS_UI32 *pdwTimestamp);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETGETCHANGETIMESTAMP_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketGetChangeTimestamp
	#define EXT_TraceMgrPacketGetChangeTimestamp
	#define GET_TraceMgrPacketGetChangeTimestamp(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketGetChangeTimestamp(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketGetChangeTimestamp  FALSE
	#define EXP_TraceMgrPacketGetChangeTimestamp  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketGetChangeTimestamp
	#define EXT_TraceMgrPacketGetChangeTimestamp
	#define GET_TraceMgrPacketGetChangeTimestamp(fl)  CAL_CMGETAPI( "TraceMgrPacketGetChangeTimestamp" ) 
	#define CAL_TraceMgrPacketGetChangeTimestamp  TraceMgrPacketGetChangeTimestamp
	#define CHK_TraceMgrPacketGetChangeTimestamp  TRUE
	#define EXP_TraceMgrPacketGetChangeTimestamp  CAL_CMEXPAPI( "TraceMgrPacketGetChangeTimestamp" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketGetChangeTimestamp
	#define EXT_TraceMgrPacketGetChangeTimestamp
	#define GET_TraceMgrPacketGetChangeTimestamp(fl)  CAL_CMGETAPI( "TraceMgrPacketGetChangeTimestamp" ) 
	#define CAL_TraceMgrPacketGetChangeTimestamp  TraceMgrPacketGetChangeTimestamp
	#define CHK_TraceMgrPacketGetChangeTimestamp  TRUE
	#define EXP_TraceMgrPacketGetChangeTimestamp  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketGetChangeTimestamp", (RTS_UINTPTR)TraceMgrPacketGetChangeTimestamp, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketGetChangeTimestamp
	#define EXT_CmpTraceMgrTraceMgrPacketGetChangeTimestamp
	#define GET_CmpTraceMgrTraceMgrPacketGetChangeTimestamp  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketGetChangeTimestamp pICmpTraceMgr->ITraceMgrPacketGetChangeTimestamp
	#define CHK_CmpTraceMgrTraceMgrPacketGetChangeTimestamp (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketGetChangeTimestamp  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketGetChangeTimestamp
	#define EXT_TraceMgrPacketGetChangeTimestamp
	#define GET_TraceMgrPacketGetChangeTimestamp(fl)  CAL_CMGETAPI( "TraceMgrPacketGetChangeTimestamp" ) 
	#define CAL_TraceMgrPacketGetChangeTimestamp pICmpTraceMgr->ITraceMgrPacketGetChangeTimestamp
	#define CHK_TraceMgrPacketGetChangeTimestamp (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketGetChangeTimestamp  CAL_CMEXPAPI( "TraceMgrPacketGetChangeTimestamp" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketGetChangeTimestamp  PFTRACEMGRPACKETGETCHANGETIMESTAMP pfTraceMgrPacketGetChangeTimestamp;
	#define EXT_TraceMgrPacketGetChangeTimestamp  extern PFTRACEMGRPACKETGETCHANGETIMESTAMP pfTraceMgrPacketGetChangeTimestamp;
	#define GET_TraceMgrPacketGetChangeTimestamp(fl)  s_pfCMGetAPI2( "TraceMgrPacketGetChangeTimestamp", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketGetChangeTimestamp, (fl), 0, 0)
	#define CAL_TraceMgrPacketGetChangeTimestamp  pfTraceMgrPacketGetChangeTimestamp
	#define CHK_TraceMgrPacketGetChangeTimestamp  (pfTraceMgrPacketGetChangeTimestamp != NULL)
	#define EXP_TraceMgrPacketGetChangeTimestamp  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketGetChangeTimestamp", (RTS_UINTPTR)TraceMgrPacketGetChangeTimestamp, 0, 0) 
#endif




/**
 * <description>Get the first registered trace packet</description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the trace packet</result>
 */
RTS_HANDLE CDECL TraceMgrPacketGetFirst(RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFTRACEMGRPACKETGETFIRST) (RTS_RESULT *pResult);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETGETFIRST_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketGetFirst
	#define EXT_TraceMgrPacketGetFirst
	#define GET_TraceMgrPacketGetFirst(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketGetFirst(p0)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_TraceMgrPacketGetFirst  FALSE
	#define EXP_TraceMgrPacketGetFirst  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketGetFirst
	#define EXT_TraceMgrPacketGetFirst
	#define GET_TraceMgrPacketGetFirst(fl)  CAL_CMGETAPI( "TraceMgrPacketGetFirst" ) 
	#define CAL_TraceMgrPacketGetFirst  TraceMgrPacketGetFirst
	#define CHK_TraceMgrPacketGetFirst  TRUE
	#define EXP_TraceMgrPacketGetFirst  CAL_CMEXPAPI( "TraceMgrPacketGetFirst" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketGetFirst
	#define EXT_TraceMgrPacketGetFirst
	#define GET_TraceMgrPacketGetFirst(fl)  CAL_CMGETAPI( "TraceMgrPacketGetFirst" ) 
	#define CAL_TraceMgrPacketGetFirst  TraceMgrPacketGetFirst
	#define CHK_TraceMgrPacketGetFirst  TRUE
	#define EXP_TraceMgrPacketGetFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketGetFirst", (RTS_UINTPTR)TraceMgrPacketGetFirst, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketGetFirst
	#define EXT_CmpTraceMgrTraceMgrPacketGetFirst
	#define GET_CmpTraceMgrTraceMgrPacketGetFirst  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketGetFirst pICmpTraceMgr->ITraceMgrPacketGetFirst
	#define CHK_CmpTraceMgrTraceMgrPacketGetFirst (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketGetFirst  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketGetFirst
	#define EXT_TraceMgrPacketGetFirst
	#define GET_TraceMgrPacketGetFirst(fl)  CAL_CMGETAPI( "TraceMgrPacketGetFirst" ) 
	#define CAL_TraceMgrPacketGetFirst pICmpTraceMgr->ITraceMgrPacketGetFirst
	#define CHK_TraceMgrPacketGetFirst (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketGetFirst  CAL_CMEXPAPI( "TraceMgrPacketGetFirst" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketGetFirst  PFTRACEMGRPACKETGETFIRST pfTraceMgrPacketGetFirst;
	#define EXT_TraceMgrPacketGetFirst  extern PFTRACEMGRPACKETGETFIRST pfTraceMgrPacketGetFirst;
	#define GET_TraceMgrPacketGetFirst(fl)  s_pfCMGetAPI2( "TraceMgrPacketGetFirst", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketGetFirst, (fl), 0, 0)
	#define CAL_TraceMgrPacketGetFirst  pfTraceMgrPacketGetFirst
	#define CHK_TraceMgrPacketGetFirst  (pfTraceMgrPacketGetFirst != NULL)
	#define EXP_TraceMgrPacketGetFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketGetFirst", (RTS_UINTPTR)TraceMgrPacketGetFirst, 0, 0) 
#endif




/**
 * <description>Get the next registered trace packet</description>
 * <param name="hPrevPacket" type="IN">Handle to the previous trace packet</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the trace packet</result>
 */
RTS_HANDLE CDECL TraceMgrPacketGetNext(RTS_HANDLE hPrevPacket, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFTRACEMGRPACKETGETNEXT) (RTS_HANDLE hPrevPacket, RTS_RESULT *pResult);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETGETNEXT_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketGetNext
	#define EXT_TraceMgrPacketGetNext
	#define GET_TraceMgrPacketGetNext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketGetNext(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_TraceMgrPacketGetNext  FALSE
	#define EXP_TraceMgrPacketGetNext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketGetNext
	#define EXT_TraceMgrPacketGetNext
	#define GET_TraceMgrPacketGetNext(fl)  CAL_CMGETAPI( "TraceMgrPacketGetNext" ) 
	#define CAL_TraceMgrPacketGetNext  TraceMgrPacketGetNext
	#define CHK_TraceMgrPacketGetNext  TRUE
	#define EXP_TraceMgrPacketGetNext  CAL_CMEXPAPI( "TraceMgrPacketGetNext" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketGetNext
	#define EXT_TraceMgrPacketGetNext
	#define GET_TraceMgrPacketGetNext(fl)  CAL_CMGETAPI( "TraceMgrPacketGetNext" ) 
	#define CAL_TraceMgrPacketGetNext  TraceMgrPacketGetNext
	#define CHK_TraceMgrPacketGetNext  TRUE
	#define EXP_TraceMgrPacketGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketGetNext", (RTS_UINTPTR)TraceMgrPacketGetNext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketGetNext
	#define EXT_CmpTraceMgrTraceMgrPacketGetNext
	#define GET_CmpTraceMgrTraceMgrPacketGetNext  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketGetNext pICmpTraceMgr->ITraceMgrPacketGetNext
	#define CHK_CmpTraceMgrTraceMgrPacketGetNext (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketGetNext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketGetNext
	#define EXT_TraceMgrPacketGetNext
	#define GET_TraceMgrPacketGetNext(fl)  CAL_CMGETAPI( "TraceMgrPacketGetNext" ) 
	#define CAL_TraceMgrPacketGetNext pICmpTraceMgr->ITraceMgrPacketGetNext
	#define CHK_TraceMgrPacketGetNext (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketGetNext  CAL_CMEXPAPI( "TraceMgrPacketGetNext" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketGetNext  PFTRACEMGRPACKETGETNEXT pfTraceMgrPacketGetNext;
	#define EXT_TraceMgrPacketGetNext  extern PFTRACEMGRPACKETGETNEXT pfTraceMgrPacketGetNext;
	#define GET_TraceMgrPacketGetNext(fl)  s_pfCMGetAPI2( "TraceMgrPacketGetNext", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketGetNext, (fl), 0, 0)
	#define CAL_TraceMgrPacketGetNext  pfTraceMgrPacketGetNext
	#define CHK_TraceMgrPacketGetNext  (pfTraceMgrPacketGetNext != NULL)
	#define EXP_TraceMgrPacketGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketGetNext", (RTS_UINTPTR)TraceMgrPacketGetNext, 0, 0) 
#endif




/**
 * <description>Start the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrPacketStart(RTS_HANDLE hPacket);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETSTART) (RTS_HANDLE hPacket);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETSTART_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketStart
	#define EXT_TraceMgrPacketStart
	#define GET_TraceMgrPacketStart(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketStart(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketStart  FALSE
	#define EXP_TraceMgrPacketStart  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketStart
	#define EXT_TraceMgrPacketStart
	#define GET_TraceMgrPacketStart(fl)  CAL_CMGETAPI( "TraceMgrPacketStart" ) 
	#define CAL_TraceMgrPacketStart  TraceMgrPacketStart
	#define CHK_TraceMgrPacketStart  TRUE
	#define EXP_TraceMgrPacketStart  CAL_CMEXPAPI( "TraceMgrPacketStart" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketStart
	#define EXT_TraceMgrPacketStart
	#define GET_TraceMgrPacketStart(fl)  CAL_CMGETAPI( "TraceMgrPacketStart" ) 
	#define CAL_TraceMgrPacketStart  TraceMgrPacketStart
	#define CHK_TraceMgrPacketStart  TRUE
	#define EXP_TraceMgrPacketStart  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketStart", (RTS_UINTPTR)TraceMgrPacketStart, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketStart
	#define EXT_CmpTraceMgrTraceMgrPacketStart
	#define GET_CmpTraceMgrTraceMgrPacketStart  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketStart pICmpTraceMgr->ITraceMgrPacketStart
	#define CHK_CmpTraceMgrTraceMgrPacketStart (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketStart  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketStart
	#define EXT_TraceMgrPacketStart
	#define GET_TraceMgrPacketStart(fl)  CAL_CMGETAPI( "TraceMgrPacketStart" ) 
	#define CAL_TraceMgrPacketStart pICmpTraceMgr->ITraceMgrPacketStart
	#define CHK_TraceMgrPacketStart (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketStart  CAL_CMEXPAPI( "TraceMgrPacketStart" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketStart  PFTRACEMGRPACKETSTART pfTraceMgrPacketStart;
	#define EXT_TraceMgrPacketStart  extern PFTRACEMGRPACKETSTART pfTraceMgrPacketStart;
	#define GET_TraceMgrPacketStart(fl)  s_pfCMGetAPI2( "TraceMgrPacketStart", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketStart, (fl), 0, 0)
	#define CAL_TraceMgrPacketStart  pfTraceMgrPacketStart
	#define CHK_TraceMgrPacketStart  (pfTraceMgrPacketStart != NULL)
	#define EXP_TraceMgrPacketStart  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketStart", (RTS_UINTPTR)TraceMgrPacketStart, 0, 0) 
#endif




/**
 * <description>Stop the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrPacketStop(RTS_HANDLE hPacket);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETSTOP) (RTS_HANDLE hPacket);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETSTOP_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketStop
	#define EXT_TraceMgrPacketStop
	#define GET_TraceMgrPacketStop(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketStop(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketStop  FALSE
	#define EXP_TraceMgrPacketStop  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketStop
	#define EXT_TraceMgrPacketStop
	#define GET_TraceMgrPacketStop(fl)  CAL_CMGETAPI( "TraceMgrPacketStop" ) 
	#define CAL_TraceMgrPacketStop  TraceMgrPacketStop
	#define CHK_TraceMgrPacketStop  TRUE
	#define EXP_TraceMgrPacketStop  CAL_CMEXPAPI( "TraceMgrPacketStop" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketStop
	#define EXT_TraceMgrPacketStop
	#define GET_TraceMgrPacketStop(fl)  CAL_CMGETAPI( "TraceMgrPacketStop" ) 
	#define CAL_TraceMgrPacketStop  TraceMgrPacketStop
	#define CHK_TraceMgrPacketStop  TRUE
	#define EXP_TraceMgrPacketStop  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketStop", (RTS_UINTPTR)TraceMgrPacketStop, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketStop
	#define EXT_CmpTraceMgrTraceMgrPacketStop
	#define GET_CmpTraceMgrTraceMgrPacketStop  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketStop pICmpTraceMgr->ITraceMgrPacketStop
	#define CHK_CmpTraceMgrTraceMgrPacketStop (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketStop  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketStop
	#define EXT_TraceMgrPacketStop
	#define GET_TraceMgrPacketStop(fl)  CAL_CMGETAPI( "TraceMgrPacketStop" ) 
	#define CAL_TraceMgrPacketStop pICmpTraceMgr->ITraceMgrPacketStop
	#define CHK_TraceMgrPacketStop (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketStop  CAL_CMEXPAPI( "TraceMgrPacketStop" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketStop  PFTRACEMGRPACKETSTOP pfTraceMgrPacketStop;
	#define EXT_TraceMgrPacketStop  extern PFTRACEMGRPACKETSTOP pfTraceMgrPacketStop;
	#define GET_TraceMgrPacketStop(fl)  s_pfCMGetAPI2( "TraceMgrPacketStop", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketStop, (fl), 0, 0)
	#define CAL_TraceMgrPacketStop  pfTraceMgrPacketStop
	#define CHK_TraceMgrPacketStop  (pfTraceMgrPacketStop != NULL)
	#define EXP_TraceMgrPacketStop  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketStop", (RTS_UINTPTR)TraceMgrPacketStop, 0, 0) 
#endif




/**
 * <description>Restart the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrPacketRestart(RTS_HANDLE hPacket);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETRESTART) (RTS_HANDLE hPacket);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETRESTART_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketRestart
	#define EXT_TraceMgrPacketRestart
	#define GET_TraceMgrPacketRestart(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketRestart(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketRestart  FALSE
	#define EXP_TraceMgrPacketRestart  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketRestart
	#define EXT_TraceMgrPacketRestart
	#define GET_TraceMgrPacketRestart(fl)  CAL_CMGETAPI( "TraceMgrPacketRestart" ) 
	#define CAL_TraceMgrPacketRestart  TraceMgrPacketRestart
	#define CHK_TraceMgrPacketRestart  TRUE
	#define EXP_TraceMgrPacketRestart  CAL_CMEXPAPI( "TraceMgrPacketRestart" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketRestart
	#define EXT_TraceMgrPacketRestart
	#define GET_TraceMgrPacketRestart(fl)  CAL_CMGETAPI( "TraceMgrPacketRestart" ) 
	#define CAL_TraceMgrPacketRestart  TraceMgrPacketRestart
	#define CHK_TraceMgrPacketRestart  TRUE
	#define EXP_TraceMgrPacketRestart  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketRestart", (RTS_UINTPTR)TraceMgrPacketRestart, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketRestart
	#define EXT_CmpTraceMgrTraceMgrPacketRestart
	#define GET_CmpTraceMgrTraceMgrPacketRestart  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketRestart pICmpTraceMgr->ITraceMgrPacketRestart
	#define CHK_CmpTraceMgrTraceMgrPacketRestart (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketRestart  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketRestart
	#define EXT_TraceMgrPacketRestart
	#define GET_TraceMgrPacketRestart(fl)  CAL_CMGETAPI( "TraceMgrPacketRestart" ) 
	#define CAL_TraceMgrPacketRestart pICmpTraceMgr->ITraceMgrPacketRestart
	#define CHK_TraceMgrPacketRestart (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketRestart  CAL_CMEXPAPI( "TraceMgrPacketRestart" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketRestart  PFTRACEMGRPACKETRESTART pfTraceMgrPacketRestart;
	#define EXT_TraceMgrPacketRestart  extern PFTRACEMGRPACKETRESTART pfTraceMgrPacketRestart;
	#define GET_TraceMgrPacketRestart(fl)  s_pfCMGetAPI2( "TraceMgrPacketRestart", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketRestart, (fl), 0, 0)
	#define CAL_TraceMgrPacketRestart  pfTraceMgrPacketRestart
	#define CHK_TraceMgrPacketRestart  (pfTraceMgrPacketRestart != NULL)
	#define EXP_TraceMgrPacketRestart  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketRestart", (RTS_UINTPTR)TraceMgrPacketRestart, 0, 0) 
#endif




/**
 * <description>Get the state of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="pState" type="OUT">Pointer to trace packet state</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrPacketGetState(RTS_HANDLE hPacket, TraceState *pState);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETGETSTATE) (RTS_HANDLE hPacket, TraceState *pState);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETGETSTATE_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketGetState
	#define EXT_TraceMgrPacketGetState
	#define GET_TraceMgrPacketGetState(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketGetState(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketGetState  FALSE
	#define EXP_TraceMgrPacketGetState  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketGetState
	#define EXT_TraceMgrPacketGetState
	#define GET_TraceMgrPacketGetState(fl)  CAL_CMGETAPI( "TraceMgrPacketGetState" ) 
	#define CAL_TraceMgrPacketGetState  TraceMgrPacketGetState
	#define CHK_TraceMgrPacketGetState  TRUE
	#define EXP_TraceMgrPacketGetState  CAL_CMEXPAPI( "TraceMgrPacketGetState" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketGetState
	#define EXT_TraceMgrPacketGetState
	#define GET_TraceMgrPacketGetState(fl)  CAL_CMGETAPI( "TraceMgrPacketGetState" ) 
	#define CAL_TraceMgrPacketGetState  TraceMgrPacketGetState
	#define CHK_TraceMgrPacketGetState  TRUE
	#define EXP_TraceMgrPacketGetState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketGetState", (RTS_UINTPTR)TraceMgrPacketGetState, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketGetState
	#define EXT_CmpTraceMgrTraceMgrPacketGetState
	#define GET_CmpTraceMgrTraceMgrPacketGetState  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketGetState pICmpTraceMgr->ITraceMgrPacketGetState
	#define CHK_CmpTraceMgrTraceMgrPacketGetState (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketGetState  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketGetState
	#define EXT_TraceMgrPacketGetState
	#define GET_TraceMgrPacketGetState(fl)  CAL_CMGETAPI( "TraceMgrPacketGetState" ) 
	#define CAL_TraceMgrPacketGetState pICmpTraceMgr->ITraceMgrPacketGetState
	#define CHK_TraceMgrPacketGetState (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketGetState  CAL_CMEXPAPI( "TraceMgrPacketGetState" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketGetState  PFTRACEMGRPACKETGETSTATE pfTraceMgrPacketGetState;
	#define EXT_TraceMgrPacketGetState  extern PFTRACEMGRPACKETGETSTATE pfTraceMgrPacketGetState;
	#define GET_TraceMgrPacketGetState(fl)  s_pfCMGetAPI2( "TraceMgrPacketGetState", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketGetState, (fl), 0, 0)
	#define CAL_TraceMgrPacketGetState  pfTraceMgrPacketGetState
	#define CHK_TraceMgrPacketGetState  (pfTraceMgrPacketGetState != NULL)
	#define EXP_TraceMgrPacketGetState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketGetState", (RTS_UINTPTR)TraceMgrPacketGetState, 0, 0) 
#endif




/**
 * <description>Set the trigger state of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="ptsTriggerState" type="IN">Pointer to trigger state to set</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrPacketSetTriggerState(RTS_HANDLE hPacket, TriggerState *ptsTriggerState);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETSETTRIGGERSTATE) (RTS_HANDLE hPacket, TriggerState *ptsTriggerState);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETSETTRIGGERSTATE_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketSetTriggerState
	#define EXT_TraceMgrPacketSetTriggerState
	#define GET_TraceMgrPacketSetTriggerState(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketSetTriggerState(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketSetTriggerState  FALSE
	#define EXP_TraceMgrPacketSetTriggerState  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketSetTriggerState
	#define EXT_TraceMgrPacketSetTriggerState
	#define GET_TraceMgrPacketSetTriggerState(fl)  CAL_CMGETAPI( "TraceMgrPacketSetTriggerState" ) 
	#define CAL_TraceMgrPacketSetTriggerState  TraceMgrPacketSetTriggerState
	#define CHK_TraceMgrPacketSetTriggerState  TRUE
	#define EXP_TraceMgrPacketSetTriggerState  CAL_CMEXPAPI( "TraceMgrPacketSetTriggerState" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketSetTriggerState
	#define EXT_TraceMgrPacketSetTriggerState
	#define GET_TraceMgrPacketSetTriggerState(fl)  CAL_CMGETAPI( "TraceMgrPacketSetTriggerState" ) 
	#define CAL_TraceMgrPacketSetTriggerState  TraceMgrPacketSetTriggerState
	#define CHK_TraceMgrPacketSetTriggerState  TRUE
	#define EXP_TraceMgrPacketSetTriggerState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketSetTriggerState", (RTS_UINTPTR)TraceMgrPacketSetTriggerState, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketSetTriggerState
	#define EXT_CmpTraceMgrTraceMgrPacketSetTriggerState
	#define GET_CmpTraceMgrTraceMgrPacketSetTriggerState  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketSetTriggerState pICmpTraceMgr->ITraceMgrPacketSetTriggerState
	#define CHK_CmpTraceMgrTraceMgrPacketSetTriggerState (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketSetTriggerState  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketSetTriggerState
	#define EXT_TraceMgrPacketSetTriggerState
	#define GET_TraceMgrPacketSetTriggerState(fl)  CAL_CMGETAPI( "TraceMgrPacketSetTriggerState" ) 
	#define CAL_TraceMgrPacketSetTriggerState pICmpTraceMgr->ITraceMgrPacketSetTriggerState
	#define CHK_TraceMgrPacketSetTriggerState (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketSetTriggerState  CAL_CMEXPAPI( "TraceMgrPacketSetTriggerState" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketSetTriggerState  PFTRACEMGRPACKETSETTRIGGERSTATE pfTraceMgrPacketSetTriggerState;
	#define EXT_TraceMgrPacketSetTriggerState  extern PFTRACEMGRPACKETSETTRIGGERSTATE pfTraceMgrPacketSetTriggerState;
	#define GET_TraceMgrPacketSetTriggerState(fl)  s_pfCMGetAPI2( "TraceMgrPacketSetTriggerState", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketSetTriggerState, (fl), 0, 0)
	#define CAL_TraceMgrPacketSetTriggerState  pfTraceMgrPacketSetTriggerState
	#define CHK_TraceMgrPacketSetTriggerState  (pfTraceMgrPacketSetTriggerState != NULL)
	#define EXP_TraceMgrPacketSetTriggerState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketSetTriggerState", (RTS_UINTPTR)TraceMgrPacketSetTriggerState, 0, 0) 
#endif




/**
 * <description>Enable trigger of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrPacketEnableTrigger(RTS_HANDLE hPacket);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETENABLETRIGGER) (RTS_HANDLE hPacket);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETENABLETRIGGER_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketEnableTrigger
	#define EXT_TraceMgrPacketEnableTrigger
	#define GET_TraceMgrPacketEnableTrigger(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketEnableTrigger(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketEnableTrigger  FALSE
	#define EXP_TraceMgrPacketEnableTrigger  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketEnableTrigger
	#define EXT_TraceMgrPacketEnableTrigger
	#define GET_TraceMgrPacketEnableTrigger(fl)  CAL_CMGETAPI( "TraceMgrPacketEnableTrigger" ) 
	#define CAL_TraceMgrPacketEnableTrigger  TraceMgrPacketEnableTrigger
	#define CHK_TraceMgrPacketEnableTrigger  TRUE
	#define EXP_TraceMgrPacketEnableTrigger  CAL_CMEXPAPI( "TraceMgrPacketEnableTrigger" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketEnableTrigger
	#define EXT_TraceMgrPacketEnableTrigger
	#define GET_TraceMgrPacketEnableTrigger(fl)  CAL_CMGETAPI( "TraceMgrPacketEnableTrigger" ) 
	#define CAL_TraceMgrPacketEnableTrigger  TraceMgrPacketEnableTrigger
	#define CHK_TraceMgrPacketEnableTrigger  TRUE
	#define EXP_TraceMgrPacketEnableTrigger  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketEnableTrigger", (RTS_UINTPTR)TraceMgrPacketEnableTrigger, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketEnableTrigger
	#define EXT_CmpTraceMgrTraceMgrPacketEnableTrigger
	#define GET_CmpTraceMgrTraceMgrPacketEnableTrigger  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketEnableTrigger pICmpTraceMgr->ITraceMgrPacketEnableTrigger
	#define CHK_CmpTraceMgrTraceMgrPacketEnableTrigger (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketEnableTrigger  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketEnableTrigger
	#define EXT_TraceMgrPacketEnableTrigger
	#define GET_TraceMgrPacketEnableTrigger(fl)  CAL_CMGETAPI( "TraceMgrPacketEnableTrigger" ) 
	#define CAL_TraceMgrPacketEnableTrigger pICmpTraceMgr->ITraceMgrPacketEnableTrigger
	#define CHK_TraceMgrPacketEnableTrigger (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketEnableTrigger  CAL_CMEXPAPI( "TraceMgrPacketEnableTrigger" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketEnableTrigger  PFTRACEMGRPACKETENABLETRIGGER pfTraceMgrPacketEnableTrigger;
	#define EXT_TraceMgrPacketEnableTrigger  extern PFTRACEMGRPACKETENABLETRIGGER pfTraceMgrPacketEnableTrigger;
	#define GET_TraceMgrPacketEnableTrigger(fl)  s_pfCMGetAPI2( "TraceMgrPacketEnableTrigger", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketEnableTrigger, (fl), 0, 0)
	#define CAL_TraceMgrPacketEnableTrigger  pfTraceMgrPacketEnableTrigger
	#define CHK_TraceMgrPacketEnableTrigger  (pfTraceMgrPacketEnableTrigger != NULL)
	#define EXP_TraceMgrPacketEnableTrigger  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketEnableTrigger", (RTS_UINTPTR)TraceMgrPacketEnableTrigger, 0, 0) 
#endif




/**
 * <description>Disable trigger of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrPacketDisableTrigger(RTS_HANDLE hPacket);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETDISABLETRIGGER) (RTS_HANDLE hPacket);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETDISABLETRIGGER_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketDisableTrigger
	#define EXT_TraceMgrPacketDisableTrigger
	#define GET_TraceMgrPacketDisableTrigger(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketDisableTrigger(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketDisableTrigger  FALSE
	#define EXP_TraceMgrPacketDisableTrigger  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketDisableTrigger
	#define EXT_TraceMgrPacketDisableTrigger
	#define GET_TraceMgrPacketDisableTrigger(fl)  CAL_CMGETAPI( "TraceMgrPacketDisableTrigger" ) 
	#define CAL_TraceMgrPacketDisableTrigger  TraceMgrPacketDisableTrigger
	#define CHK_TraceMgrPacketDisableTrigger  TRUE
	#define EXP_TraceMgrPacketDisableTrigger  CAL_CMEXPAPI( "TraceMgrPacketDisableTrigger" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketDisableTrigger
	#define EXT_TraceMgrPacketDisableTrigger
	#define GET_TraceMgrPacketDisableTrigger(fl)  CAL_CMGETAPI( "TraceMgrPacketDisableTrigger" ) 
	#define CAL_TraceMgrPacketDisableTrigger  TraceMgrPacketDisableTrigger
	#define CHK_TraceMgrPacketDisableTrigger  TRUE
	#define EXP_TraceMgrPacketDisableTrigger  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketDisableTrigger", (RTS_UINTPTR)TraceMgrPacketDisableTrigger, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketDisableTrigger
	#define EXT_CmpTraceMgrTraceMgrPacketDisableTrigger
	#define GET_CmpTraceMgrTraceMgrPacketDisableTrigger  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketDisableTrigger pICmpTraceMgr->ITraceMgrPacketDisableTrigger
	#define CHK_CmpTraceMgrTraceMgrPacketDisableTrigger (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketDisableTrigger  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketDisableTrigger
	#define EXT_TraceMgrPacketDisableTrigger
	#define GET_TraceMgrPacketDisableTrigger(fl)  CAL_CMGETAPI( "TraceMgrPacketDisableTrigger" ) 
	#define CAL_TraceMgrPacketDisableTrigger pICmpTraceMgr->ITraceMgrPacketDisableTrigger
	#define CHK_TraceMgrPacketDisableTrigger (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketDisableTrigger  CAL_CMEXPAPI( "TraceMgrPacketDisableTrigger" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketDisableTrigger  PFTRACEMGRPACKETDISABLETRIGGER pfTraceMgrPacketDisableTrigger;
	#define EXT_TraceMgrPacketDisableTrigger  extern PFTRACEMGRPACKETDISABLETRIGGER pfTraceMgrPacketDisableTrigger;
	#define GET_TraceMgrPacketDisableTrigger(fl)  s_pfCMGetAPI2( "TraceMgrPacketDisableTrigger", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketDisableTrigger, (fl), 0, 0)
	#define CAL_TraceMgrPacketDisableTrigger  pfTraceMgrPacketDisableTrigger
	#define CHK_TraceMgrPacketDisableTrigger  (pfTraceMgrPacketDisableTrigger != NULL)
	#define EXP_TraceMgrPacketDisableTrigger  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketDisableTrigger", (RTS_UINTPTR)TraceMgrPacketDisableTrigger, 0, 0) 
#endif




/**
 * <description>Reset trigger of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrPacketResetTrigger(RTS_HANDLE hPacket);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETRESETTRIGGER) (RTS_HANDLE hPacket);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETRESETTRIGGER_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketResetTrigger
	#define EXT_TraceMgrPacketResetTrigger
	#define GET_TraceMgrPacketResetTrigger(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketResetTrigger(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketResetTrigger  FALSE
	#define EXP_TraceMgrPacketResetTrigger  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketResetTrigger
	#define EXT_TraceMgrPacketResetTrigger
	#define GET_TraceMgrPacketResetTrigger(fl)  CAL_CMGETAPI( "TraceMgrPacketResetTrigger" ) 
	#define CAL_TraceMgrPacketResetTrigger  TraceMgrPacketResetTrigger
	#define CHK_TraceMgrPacketResetTrigger  TRUE
	#define EXP_TraceMgrPacketResetTrigger  CAL_CMEXPAPI( "TraceMgrPacketResetTrigger" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketResetTrigger
	#define EXT_TraceMgrPacketResetTrigger
	#define GET_TraceMgrPacketResetTrigger(fl)  CAL_CMGETAPI( "TraceMgrPacketResetTrigger" ) 
	#define CAL_TraceMgrPacketResetTrigger  TraceMgrPacketResetTrigger
	#define CHK_TraceMgrPacketResetTrigger  TRUE
	#define EXP_TraceMgrPacketResetTrigger  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketResetTrigger", (RTS_UINTPTR)TraceMgrPacketResetTrigger, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketResetTrigger
	#define EXT_CmpTraceMgrTraceMgrPacketResetTrigger
	#define GET_CmpTraceMgrTraceMgrPacketResetTrigger  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketResetTrigger pICmpTraceMgr->ITraceMgrPacketResetTrigger
	#define CHK_CmpTraceMgrTraceMgrPacketResetTrigger (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketResetTrigger  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketResetTrigger
	#define EXT_TraceMgrPacketResetTrigger
	#define GET_TraceMgrPacketResetTrigger(fl)  CAL_CMGETAPI( "TraceMgrPacketResetTrigger" ) 
	#define CAL_TraceMgrPacketResetTrigger pICmpTraceMgr->ITraceMgrPacketResetTrigger
	#define CHK_TraceMgrPacketResetTrigger (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketResetTrigger  CAL_CMEXPAPI( "TraceMgrPacketResetTrigger" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketResetTrigger  PFTRACEMGRPACKETRESETTRIGGER pfTraceMgrPacketResetTrigger;
	#define EXT_TraceMgrPacketResetTrigger  extern PFTRACEMGRPACKETRESETTRIGGER pfTraceMgrPacketResetTrigger;
	#define GET_TraceMgrPacketResetTrigger(fl)  s_pfCMGetAPI2( "TraceMgrPacketResetTrigger", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketResetTrigger, (fl), 0, 0)
	#define CAL_TraceMgrPacketResetTrigger  pfTraceMgrPacketResetTrigger
	#define CHK_TraceMgrPacketResetTrigger  (pfTraceMgrPacketResetTrigger != NULL)
	#define EXP_TraceMgrPacketResetTrigger  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketResetTrigger", (RTS_UINTPTR)TraceMgrPacketResetTrigger, 0, 0) 
#endif




/**
 * <description>Enable specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrPacketEnable(RTS_HANDLE hPacket);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETENABLE) (RTS_HANDLE hPacket);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETENABLE_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketEnable
	#define EXT_TraceMgrPacketEnable
	#define GET_TraceMgrPacketEnable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketEnable(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketEnable  FALSE
	#define EXP_TraceMgrPacketEnable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketEnable
	#define EXT_TraceMgrPacketEnable
	#define GET_TraceMgrPacketEnable(fl)  CAL_CMGETAPI( "TraceMgrPacketEnable" ) 
	#define CAL_TraceMgrPacketEnable  TraceMgrPacketEnable
	#define CHK_TraceMgrPacketEnable  TRUE
	#define EXP_TraceMgrPacketEnable  CAL_CMEXPAPI( "TraceMgrPacketEnable" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketEnable
	#define EXT_TraceMgrPacketEnable
	#define GET_TraceMgrPacketEnable(fl)  CAL_CMGETAPI( "TraceMgrPacketEnable" ) 
	#define CAL_TraceMgrPacketEnable  TraceMgrPacketEnable
	#define CHK_TraceMgrPacketEnable  TRUE
	#define EXP_TraceMgrPacketEnable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketEnable", (RTS_UINTPTR)TraceMgrPacketEnable, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketEnable
	#define EXT_CmpTraceMgrTraceMgrPacketEnable
	#define GET_CmpTraceMgrTraceMgrPacketEnable  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketEnable pICmpTraceMgr->ITraceMgrPacketEnable
	#define CHK_CmpTraceMgrTraceMgrPacketEnable (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketEnable  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketEnable
	#define EXT_TraceMgrPacketEnable
	#define GET_TraceMgrPacketEnable(fl)  CAL_CMGETAPI( "TraceMgrPacketEnable" ) 
	#define CAL_TraceMgrPacketEnable pICmpTraceMgr->ITraceMgrPacketEnable
	#define CHK_TraceMgrPacketEnable (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketEnable  CAL_CMEXPAPI( "TraceMgrPacketEnable" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketEnable  PFTRACEMGRPACKETENABLE pfTraceMgrPacketEnable;
	#define EXT_TraceMgrPacketEnable  extern PFTRACEMGRPACKETENABLE pfTraceMgrPacketEnable;
	#define GET_TraceMgrPacketEnable(fl)  s_pfCMGetAPI2( "TraceMgrPacketEnable", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketEnable, (fl), 0, 0)
	#define CAL_TraceMgrPacketEnable  pfTraceMgrPacketEnable
	#define CHK_TraceMgrPacketEnable  (pfTraceMgrPacketEnable != NULL)
	#define EXP_TraceMgrPacketEnable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketEnable", (RTS_UINTPTR)TraceMgrPacketEnable, 0, 0) 
#endif




/**
 * <description>Disable specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrPacketDisable(RTS_HANDLE hPacket);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETDISABLE) (RTS_HANDLE hPacket);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETDISABLE_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketDisable
	#define EXT_TraceMgrPacketDisable
	#define GET_TraceMgrPacketDisable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketDisable(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketDisable  FALSE
	#define EXP_TraceMgrPacketDisable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketDisable
	#define EXT_TraceMgrPacketDisable
	#define GET_TraceMgrPacketDisable(fl)  CAL_CMGETAPI( "TraceMgrPacketDisable" ) 
	#define CAL_TraceMgrPacketDisable  TraceMgrPacketDisable
	#define CHK_TraceMgrPacketDisable  TRUE
	#define EXP_TraceMgrPacketDisable  CAL_CMEXPAPI( "TraceMgrPacketDisable" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketDisable
	#define EXT_TraceMgrPacketDisable
	#define GET_TraceMgrPacketDisable(fl)  CAL_CMGETAPI( "TraceMgrPacketDisable" ) 
	#define CAL_TraceMgrPacketDisable  TraceMgrPacketDisable
	#define CHK_TraceMgrPacketDisable  TRUE
	#define EXP_TraceMgrPacketDisable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketDisable", (RTS_UINTPTR)TraceMgrPacketDisable, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketDisable
	#define EXT_CmpTraceMgrTraceMgrPacketDisable
	#define GET_CmpTraceMgrTraceMgrPacketDisable  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketDisable pICmpTraceMgr->ITraceMgrPacketDisable
	#define CHK_CmpTraceMgrTraceMgrPacketDisable (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketDisable  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketDisable
	#define EXT_TraceMgrPacketDisable
	#define GET_TraceMgrPacketDisable(fl)  CAL_CMGETAPI( "TraceMgrPacketDisable" ) 
	#define CAL_TraceMgrPacketDisable pICmpTraceMgr->ITraceMgrPacketDisable
	#define CHK_TraceMgrPacketDisable (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketDisable  CAL_CMEXPAPI( "TraceMgrPacketDisable" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketDisable  PFTRACEMGRPACKETDISABLE pfTraceMgrPacketDisable;
	#define EXT_TraceMgrPacketDisable  extern PFTRACEMGRPACKETDISABLE pfTraceMgrPacketDisable;
	#define GET_TraceMgrPacketDisable(fl)  s_pfCMGetAPI2( "TraceMgrPacketDisable", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketDisable, (fl), 0, 0)
	#define CAL_TraceMgrPacketDisable  pfTraceMgrPacketDisable
	#define CHK_TraceMgrPacketDisable  (pfTraceMgrPacketDisable != NULL)
	#define EXP_TraceMgrPacketDisable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketDisable", (RTS_UINTPTR)TraceMgrPacketDisable, 0, 0) 
#endif




/**
 * <description>Function at start reading trace packet (is used for online access of the trace editor)</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrPacketReadBegin(RTS_HANDLE hPacket);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETREADBEGIN) (RTS_HANDLE hPacket);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETREADBEGIN_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketReadBegin
	#define EXT_TraceMgrPacketReadBegin
	#define GET_TraceMgrPacketReadBegin(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketReadBegin(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketReadBegin  FALSE
	#define EXP_TraceMgrPacketReadBegin  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketReadBegin
	#define EXT_TraceMgrPacketReadBegin
	#define GET_TraceMgrPacketReadBegin(fl)  CAL_CMGETAPI( "TraceMgrPacketReadBegin" ) 
	#define CAL_TraceMgrPacketReadBegin  TraceMgrPacketReadBegin
	#define CHK_TraceMgrPacketReadBegin  TRUE
	#define EXP_TraceMgrPacketReadBegin  CAL_CMEXPAPI( "TraceMgrPacketReadBegin" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketReadBegin
	#define EXT_TraceMgrPacketReadBegin
	#define GET_TraceMgrPacketReadBegin(fl)  CAL_CMGETAPI( "TraceMgrPacketReadBegin" ) 
	#define CAL_TraceMgrPacketReadBegin  TraceMgrPacketReadBegin
	#define CHK_TraceMgrPacketReadBegin  TRUE
	#define EXP_TraceMgrPacketReadBegin  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketReadBegin", (RTS_UINTPTR)TraceMgrPacketReadBegin, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketReadBegin
	#define EXT_CmpTraceMgrTraceMgrPacketReadBegin
	#define GET_CmpTraceMgrTraceMgrPacketReadBegin  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketReadBegin pICmpTraceMgr->ITraceMgrPacketReadBegin
	#define CHK_CmpTraceMgrTraceMgrPacketReadBegin (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketReadBegin  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketReadBegin
	#define EXT_TraceMgrPacketReadBegin
	#define GET_TraceMgrPacketReadBegin(fl)  CAL_CMGETAPI( "TraceMgrPacketReadBegin" ) 
	#define CAL_TraceMgrPacketReadBegin pICmpTraceMgr->ITraceMgrPacketReadBegin
	#define CHK_TraceMgrPacketReadBegin (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketReadBegin  CAL_CMEXPAPI( "TraceMgrPacketReadBegin" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketReadBegin  PFTRACEMGRPACKETREADBEGIN pfTraceMgrPacketReadBegin;
	#define EXT_TraceMgrPacketReadBegin  extern PFTRACEMGRPACKETREADBEGIN pfTraceMgrPacketReadBegin;
	#define GET_TraceMgrPacketReadBegin(fl)  s_pfCMGetAPI2( "TraceMgrPacketReadBegin", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketReadBegin, (fl), 0, 0)
	#define CAL_TraceMgrPacketReadBegin  pfTraceMgrPacketReadBegin
	#define CHK_TraceMgrPacketReadBegin  (pfTraceMgrPacketReadBegin != NULL)
	#define EXP_TraceMgrPacketReadBegin  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketReadBegin", (RTS_UINTPTR)TraceMgrPacketReadBegin, 0, 0) 
#endif




/**
 * <description>Read first record out of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="pTraceBuffer" type="INOUT">Pointer to the trace buffer to copy the record values</param>
 * <param name="pulReadBytes" type="INOUT">Max size of the trace buffer [IN] and number of bytes copied [OUT]</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the actual read trace record</result>
 */
RTS_HANDLE CDECL TraceMgrPacketReadFirst(RTS_HANDLE hPacket, TraceRecordEntry *pTraceBuffer, RTS_UI32 *pulReadBytes, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFTRACEMGRPACKETREADFIRST) (RTS_HANDLE hPacket, TraceRecordEntry *pTraceBuffer, RTS_UI32 *pulReadBytes, RTS_RESULT *pResult);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETREADFIRST_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketReadFirst
	#define EXT_TraceMgrPacketReadFirst
	#define GET_TraceMgrPacketReadFirst(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketReadFirst(p0,p1,p2,p3)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_TraceMgrPacketReadFirst  FALSE
	#define EXP_TraceMgrPacketReadFirst  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketReadFirst
	#define EXT_TraceMgrPacketReadFirst
	#define GET_TraceMgrPacketReadFirst(fl)  CAL_CMGETAPI( "TraceMgrPacketReadFirst" ) 
	#define CAL_TraceMgrPacketReadFirst  TraceMgrPacketReadFirst
	#define CHK_TraceMgrPacketReadFirst  TRUE
	#define EXP_TraceMgrPacketReadFirst  CAL_CMEXPAPI( "TraceMgrPacketReadFirst" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketReadFirst
	#define EXT_TraceMgrPacketReadFirst
	#define GET_TraceMgrPacketReadFirst(fl)  CAL_CMGETAPI( "TraceMgrPacketReadFirst" ) 
	#define CAL_TraceMgrPacketReadFirst  TraceMgrPacketReadFirst
	#define CHK_TraceMgrPacketReadFirst  TRUE
	#define EXP_TraceMgrPacketReadFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketReadFirst", (RTS_UINTPTR)TraceMgrPacketReadFirst, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketReadFirst
	#define EXT_CmpTraceMgrTraceMgrPacketReadFirst
	#define GET_CmpTraceMgrTraceMgrPacketReadFirst  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketReadFirst pICmpTraceMgr->ITraceMgrPacketReadFirst
	#define CHK_CmpTraceMgrTraceMgrPacketReadFirst (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketReadFirst  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketReadFirst
	#define EXT_TraceMgrPacketReadFirst
	#define GET_TraceMgrPacketReadFirst(fl)  CAL_CMGETAPI( "TraceMgrPacketReadFirst" ) 
	#define CAL_TraceMgrPacketReadFirst pICmpTraceMgr->ITraceMgrPacketReadFirst
	#define CHK_TraceMgrPacketReadFirst (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketReadFirst  CAL_CMEXPAPI( "TraceMgrPacketReadFirst" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketReadFirst  PFTRACEMGRPACKETREADFIRST pfTraceMgrPacketReadFirst;
	#define EXT_TraceMgrPacketReadFirst  extern PFTRACEMGRPACKETREADFIRST pfTraceMgrPacketReadFirst;
	#define GET_TraceMgrPacketReadFirst(fl)  s_pfCMGetAPI2( "TraceMgrPacketReadFirst", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketReadFirst, (fl), 0, 0)
	#define CAL_TraceMgrPacketReadFirst  pfTraceMgrPacketReadFirst
	#define CHK_TraceMgrPacketReadFirst  (pfTraceMgrPacketReadFirst != NULL)
	#define EXP_TraceMgrPacketReadFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketReadFirst", (RTS_UINTPTR)TraceMgrPacketReadFirst, 0, 0) 
#endif




/**
 * <description>Read first record out of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="pTraceBuffer" type="INOUT">Pointer to the trace buffer to copy the record values</param>
 * <param name="ulTimestamp" type="IN">Timestamp to begin reading. Can be 0 [Reading from begin]</param>
 * <param name="pulReadBytes" type="INOUT">Max size of the trace buffer [IN] and number of bytes copied [OUT]</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the actual read trace record</result>
 */
RTS_HANDLE CDECL TraceMgrPacketReadFirst2(RTS_HANDLE hPacket, TraceRecordEntry *pTraceBuffer, RTS_UI32 ulTimestamp, RTS_UI32 *pulReadBytes, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFTRACEMGRPACKETREADFIRST2) (RTS_HANDLE hPacket, TraceRecordEntry *pTraceBuffer, RTS_UI32 ulTimestamp, RTS_UI32 *pulReadBytes, RTS_RESULT *pResult);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETREADFIRST2_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketReadFirst2
	#define EXT_TraceMgrPacketReadFirst2
	#define GET_TraceMgrPacketReadFirst2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketReadFirst2(p0,p1,p2,p3,p4)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_TraceMgrPacketReadFirst2  FALSE
	#define EXP_TraceMgrPacketReadFirst2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketReadFirst2
	#define EXT_TraceMgrPacketReadFirst2
	#define GET_TraceMgrPacketReadFirst2(fl)  CAL_CMGETAPI( "TraceMgrPacketReadFirst2" ) 
	#define CAL_TraceMgrPacketReadFirst2  TraceMgrPacketReadFirst2
	#define CHK_TraceMgrPacketReadFirst2  TRUE
	#define EXP_TraceMgrPacketReadFirst2  CAL_CMEXPAPI( "TraceMgrPacketReadFirst2" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketReadFirst2
	#define EXT_TraceMgrPacketReadFirst2
	#define GET_TraceMgrPacketReadFirst2(fl)  CAL_CMGETAPI( "TraceMgrPacketReadFirst2" ) 
	#define CAL_TraceMgrPacketReadFirst2  TraceMgrPacketReadFirst2
	#define CHK_TraceMgrPacketReadFirst2  TRUE
	#define EXP_TraceMgrPacketReadFirst2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketReadFirst2", (RTS_UINTPTR)TraceMgrPacketReadFirst2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketReadFirst2
	#define EXT_CmpTraceMgrTraceMgrPacketReadFirst2
	#define GET_CmpTraceMgrTraceMgrPacketReadFirst2  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketReadFirst2 pICmpTraceMgr->ITraceMgrPacketReadFirst2
	#define CHK_CmpTraceMgrTraceMgrPacketReadFirst2 (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketReadFirst2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketReadFirst2
	#define EXT_TraceMgrPacketReadFirst2
	#define GET_TraceMgrPacketReadFirst2(fl)  CAL_CMGETAPI( "TraceMgrPacketReadFirst2" ) 
	#define CAL_TraceMgrPacketReadFirst2 pICmpTraceMgr->ITraceMgrPacketReadFirst2
	#define CHK_TraceMgrPacketReadFirst2 (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketReadFirst2  CAL_CMEXPAPI( "TraceMgrPacketReadFirst2" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketReadFirst2  PFTRACEMGRPACKETREADFIRST2 pfTraceMgrPacketReadFirst2;
	#define EXT_TraceMgrPacketReadFirst2  extern PFTRACEMGRPACKETREADFIRST2 pfTraceMgrPacketReadFirst2;
	#define GET_TraceMgrPacketReadFirst2(fl)  s_pfCMGetAPI2( "TraceMgrPacketReadFirst2", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketReadFirst2, (fl), 0, 0)
	#define CAL_TraceMgrPacketReadFirst2  pfTraceMgrPacketReadFirst2
	#define CHK_TraceMgrPacketReadFirst2  (pfTraceMgrPacketReadFirst2 != NULL)
	#define EXP_TraceMgrPacketReadFirst2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketReadFirst2", (RTS_UINTPTR)TraceMgrPacketReadFirst2, 0, 0) 
#endif




/**
 * <description>Read next record out of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="hPrevRecord" type="IN">Handle to the previous record</param>
 * <param name="pTraceBuffer" type="INOUT">Pointer to the trace buffer to copy the record values</param>
 * <param name="pulReadBytes" type="INOUT">Max size of the trace buffer [IN] and number of bytes copied [OUT]</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the actual read trace record</result>
 */
RTS_HANDLE CDECL TraceMgrPacketReadNext(RTS_HANDLE hPacket, RTS_HANDLE hPrevRecord, TraceRecordEntry *pTraceBuffer, RTS_UI32 *pulReadBytes, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFTRACEMGRPACKETREADNEXT) (RTS_HANDLE hPacket, RTS_HANDLE hPrevRecord, TraceRecordEntry *pTraceBuffer, RTS_UI32 *pulReadBytes, RTS_RESULT *pResult);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETREADNEXT_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketReadNext
	#define EXT_TraceMgrPacketReadNext
	#define GET_TraceMgrPacketReadNext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketReadNext(p0,p1,p2,p3,p4)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_TraceMgrPacketReadNext  FALSE
	#define EXP_TraceMgrPacketReadNext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketReadNext
	#define EXT_TraceMgrPacketReadNext
	#define GET_TraceMgrPacketReadNext(fl)  CAL_CMGETAPI( "TraceMgrPacketReadNext" ) 
	#define CAL_TraceMgrPacketReadNext  TraceMgrPacketReadNext
	#define CHK_TraceMgrPacketReadNext  TRUE
	#define EXP_TraceMgrPacketReadNext  CAL_CMEXPAPI( "TraceMgrPacketReadNext" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketReadNext
	#define EXT_TraceMgrPacketReadNext
	#define GET_TraceMgrPacketReadNext(fl)  CAL_CMGETAPI( "TraceMgrPacketReadNext" ) 
	#define CAL_TraceMgrPacketReadNext  TraceMgrPacketReadNext
	#define CHK_TraceMgrPacketReadNext  TRUE
	#define EXP_TraceMgrPacketReadNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketReadNext", (RTS_UINTPTR)TraceMgrPacketReadNext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketReadNext
	#define EXT_CmpTraceMgrTraceMgrPacketReadNext
	#define GET_CmpTraceMgrTraceMgrPacketReadNext  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketReadNext pICmpTraceMgr->ITraceMgrPacketReadNext
	#define CHK_CmpTraceMgrTraceMgrPacketReadNext (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketReadNext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketReadNext
	#define EXT_TraceMgrPacketReadNext
	#define GET_TraceMgrPacketReadNext(fl)  CAL_CMGETAPI( "TraceMgrPacketReadNext" ) 
	#define CAL_TraceMgrPacketReadNext pICmpTraceMgr->ITraceMgrPacketReadNext
	#define CHK_TraceMgrPacketReadNext (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketReadNext  CAL_CMEXPAPI( "TraceMgrPacketReadNext" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketReadNext  PFTRACEMGRPACKETREADNEXT pfTraceMgrPacketReadNext;
	#define EXT_TraceMgrPacketReadNext  extern PFTRACEMGRPACKETREADNEXT pfTraceMgrPacketReadNext;
	#define GET_TraceMgrPacketReadNext(fl)  s_pfCMGetAPI2( "TraceMgrPacketReadNext", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketReadNext, (fl), 0, 0)
	#define CAL_TraceMgrPacketReadNext  pfTraceMgrPacketReadNext
	#define CHK_TraceMgrPacketReadNext  (pfTraceMgrPacketReadNext != NULL)
	#define EXP_TraceMgrPacketReadNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketReadNext", (RTS_UINTPTR)TraceMgrPacketReadNext, 0, 0) 
#endif




/**
 * <description>Read next record out of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="hPrevRecord" type="IN">Handle to the previous record</param>
 * <param name="pTraceBuffer" type="INOUT">Pointer to the trace buffer to copy the record values</param>
 * <param name="ulTimestamp" type="IN">Timestamp to begin reading. Can be 0 [Reading from begin]</param>
 * <param name="pulReadBytes" type="INOUT">Max size of the trace buffer [IN] and number of bytes copied [OUT]</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the actual read trace record</result>
 */
RTS_HANDLE CDECL TraceMgrPacketReadNext2(RTS_HANDLE hPacket, RTS_HANDLE hPrevRecord, TraceRecordEntry *pTraceBuffer, RTS_UI32 ulTimestamp, RTS_UI32 *pulReadBytes, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFTRACEMGRPACKETREADNEXT2) (RTS_HANDLE hPacket, RTS_HANDLE hPrevRecord, TraceRecordEntry *pTraceBuffer, RTS_UI32 ulTimestamp, RTS_UI32 *pulReadBytes, RTS_RESULT *pResult);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETREADNEXT2_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketReadNext2
	#define EXT_TraceMgrPacketReadNext2
	#define GET_TraceMgrPacketReadNext2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketReadNext2(p0,p1,p2,p3,p4,p5)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_TraceMgrPacketReadNext2  FALSE
	#define EXP_TraceMgrPacketReadNext2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketReadNext2
	#define EXT_TraceMgrPacketReadNext2
	#define GET_TraceMgrPacketReadNext2(fl)  CAL_CMGETAPI( "TraceMgrPacketReadNext2" ) 
	#define CAL_TraceMgrPacketReadNext2  TraceMgrPacketReadNext2
	#define CHK_TraceMgrPacketReadNext2  TRUE
	#define EXP_TraceMgrPacketReadNext2  CAL_CMEXPAPI( "TraceMgrPacketReadNext2" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketReadNext2
	#define EXT_TraceMgrPacketReadNext2
	#define GET_TraceMgrPacketReadNext2(fl)  CAL_CMGETAPI( "TraceMgrPacketReadNext2" ) 
	#define CAL_TraceMgrPacketReadNext2  TraceMgrPacketReadNext2
	#define CHK_TraceMgrPacketReadNext2  TRUE
	#define EXP_TraceMgrPacketReadNext2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketReadNext2", (RTS_UINTPTR)TraceMgrPacketReadNext2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketReadNext2
	#define EXT_CmpTraceMgrTraceMgrPacketReadNext2
	#define GET_CmpTraceMgrTraceMgrPacketReadNext2  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketReadNext2 pICmpTraceMgr->ITraceMgrPacketReadNext2
	#define CHK_CmpTraceMgrTraceMgrPacketReadNext2 (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketReadNext2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketReadNext2
	#define EXT_TraceMgrPacketReadNext2
	#define GET_TraceMgrPacketReadNext2(fl)  CAL_CMGETAPI( "TraceMgrPacketReadNext2" ) 
	#define CAL_TraceMgrPacketReadNext2 pICmpTraceMgr->ITraceMgrPacketReadNext2
	#define CHK_TraceMgrPacketReadNext2 (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketReadNext2  CAL_CMEXPAPI( "TraceMgrPacketReadNext2" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketReadNext2  PFTRACEMGRPACKETREADNEXT2 pfTraceMgrPacketReadNext2;
	#define EXT_TraceMgrPacketReadNext2  extern PFTRACEMGRPACKETREADNEXT2 pfTraceMgrPacketReadNext2;
	#define GET_TraceMgrPacketReadNext2(fl)  s_pfCMGetAPI2( "TraceMgrPacketReadNext2", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketReadNext2, (fl), 0, 0)
	#define CAL_TraceMgrPacketReadNext2  pfTraceMgrPacketReadNext2
	#define CHK_TraceMgrPacketReadNext2  (pfTraceMgrPacketReadNext2 != NULL)
	#define EXP_TraceMgrPacketReadNext2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketReadNext2", (RTS_UINTPTR)TraceMgrPacketReadNext2, 0, 0) 
#endif




/**
 * <description>Read specified record out of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="hRecord" type="IN">Handle to the previous record</param>
 * <param name="pTraceBuffer" type="INOUT">Pointer to the trace buffer to copy the record values</param>
 * <param name="pulReadBytes" type="INOUT">Max size of the trace buffer [IN] and number of bytes copied [OUT]</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrPacketRead(RTS_HANDLE hPacket, RTS_HANDLE hRecord, TraceRecordEntry *pTraceBuffer, RTS_UI32 *pulReadBytes);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETREAD) (RTS_HANDLE hPacket, RTS_HANDLE hRecord, TraceRecordEntry *pTraceBuffer, RTS_UI32 *pulReadBytes);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETREAD_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketRead
	#define EXT_TraceMgrPacketRead
	#define GET_TraceMgrPacketRead(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketRead(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketRead  FALSE
	#define EXP_TraceMgrPacketRead  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketRead
	#define EXT_TraceMgrPacketRead
	#define GET_TraceMgrPacketRead(fl)  CAL_CMGETAPI( "TraceMgrPacketRead" ) 
	#define CAL_TraceMgrPacketRead  TraceMgrPacketRead
	#define CHK_TraceMgrPacketRead  TRUE
	#define EXP_TraceMgrPacketRead  CAL_CMEXPAPI( "TraceMgrPacketRead" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketRead
	#define EXT_TraceMgrPacketRead
	#define GET_TraceMgrPacketRead(fl)  CAL_CMGETAPI( "TraceMgrPacketRead" ) 
	#define CAL_TraceMgrPacketRead  TraceMgrPacketRead
	#define CHK_TraceMgrPacketRead  TRUE
	#define EXP_TraceMgrPacketRead  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketRead", (RTS_UINTPTR)TraceMgrPacketRead, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketRead
	#define EXT_CmpTraceMgrTraceMgrPacketRead
	#define GET_CmpTraceMgrTraceMgrPacketRead  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketRead pICmpTraceMgr->ITraceMgrPacketRead
	#define CHK_CmpTraceMgrTraceMgrPacketRead (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketRead  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketRead
	#define EXT_TraceMgrPacketRead
	#define GET_TraceMgrPacketRead(fl)  CAL_CMGETAPI( "TraceMgrPacketRead" ) 
	#define CAL_TraceMgrPacketRead pICmpTraceMgr->ITraceMgrPacketRead
	#define CHK_TraceMgrPacketRead (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketRead  CAL_CMEXPAPI( "TraceMgrPacketRead" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketRead  PFTRACEMGRPACKETREAD pfTraceMgrPacketRead;
	#define EXT_TraceMgrPacketRead  extern PFTRACEMGRPACKETREAD pfTraceMgrPacketRead;
	#define GET_TraceMgrPacketRead(fl)  s_pfCMGetAPI2( "TraceMgrPacketRead", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketRead, (fl), 0, 0)
	#define CAL_TraceMgrPacketRead  pfTraceMgrPacketRead
	#define CHK_TraceMgrPacketRead  (pfTraceMgrPacketRead != NULL)
	#define EXP_TraceMgrPacketRead  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketRead", (RTS_UINTPTR)TraceMgrPacketRead, 0, 0) 
#endif




/**
 * <description>Read specified record out of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="hRecord" type="IN">Handle to the previous record</param>
 * <param name="pTraceBuffer" type="INOUT">Pointer to the trace buffer to copy the record values</param>
 * <param name="ulTimestamp" type="IN">Timestamp to begin reading. Can be 0 [Reading from begin]</param>
 * <param name="pulReadBytes" type="INOUT">Max size of the trace buffer [IN] and number of bytes copied [OUT]</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrPacketRead2(RTS_HANDLE hPacket, RTS_HANDLE hRecord, TraceRecordEntry *pTraceBuffer, RTS_UI32 ulTimestamp, RTS_UI32 *pulReadBytes);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETREAD2) (RTS_HANDLE hPacket, RTS_HANDLE hRecord, TraceRecordEntry *pTraceBuffer, RTS_UI32 ulTimestamp, RTS_UI32 *pulReadBytes);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETREAD2_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketRead2
	#define EXT_TraceMgrPacketRead2
	#define GET_TraceMgrPacketRead2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketRead2(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketRead2  FALSE
	#define EXP_TraceMgrPacketRead2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketRead2
	#define EXT_TraceMgrPacketRead2
	#define GET_TraceMgrPacketRead2(fl)  CAL_CMGETAPI( "TraceMgrPacketRead2" ) 
	#define CAL_TraceMgrPacketRead2  TraceMgrPacketRead2
	#define CHK_TraceMgrPacketRead2  TRUE
	#define EXP_TraceMgrPacketRead2  CAL_CMEXPAPI( "TraceMgrPacketRead2" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketRead2
	#define EXT_TraceMgrPacketRead2
	#define GET_TraceMgrPacketRead2(fl)  CAL_CMGETAPI( "TraceMgrPacketRead2" ) 
	#define CAL_TraceMgrPacketRead2  TraceMgrPacketRead2
	#define CHK_TraceMgrPacketRead2  TRUE
	#define EXP_TraceMgrPacketRead2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketRead2", (RTS_UINTPTR)TraceMgrPacketRead2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketRead2
	#define EXT_CmpTraceMgrTraceMgrPacketRead2
	#define GET_CmpTraceMgrTraceMgrPacketRead2  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketRead2 pICmpTraceMgr->ITraceMgrPacketRead2
	#define CHK_CmpTraceMgrTraceMgrPacketRead2 (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketRead2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketRead2
	#define EXT_TraceMgrPacketRead2
	#define GET_TraceMgrPacketRead2(fl)  CAL_CMGETAPI( "TraceMgrPacketRead2" ) 
	#define CAL_TraceMgrPacketRead2 pICmpTraceMgr->ITraceMgrPacketRead2
	#define CHK_TraceMgrPacketRead2 (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketRead2  CAL_CMEXPAPI( "TraceMgrPacketRead2" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketRead2  PFTRACEMGRPACKETREAD2 pfTraceMgrPacketRead2;
	#define EXT_TraceMgrPacketRead2  extern PFTRACEMGRPACKETREAD2 pfTraceMgrPacketRead2;
	#define GET_TraceMgrPacketRead2(fl)  s_pfCMGetAPI2( "TraceMgrPacketRead2", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketRead2, (fl), 0, 0)
	#define CAL_TraceMgrPacketRead2  pfTraceMgrPacketRead2
	#define CHK_TraceMgrPacketRead2  (pfTraceMgrPacketRead2 != NULL)
	#define EXP_TraceMgrPacketRead2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketRead2", (RTS_UINTPTR)TraceMgrPacketRead2, 0, 0) 
#endif




/**
 * <description>Function at end reading trace packet (is used for online access of the trace editor)</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrPacketReadEnd(RTS_HANDLE hPacket);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETREADEND) (RTS_HANDLE hPacket);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETREADEND_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketReadEnd
	#define EXT_TraceMgrPacketReadEnd
	#define GET_TraceMgrPacketReadEnd(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketReadEnd(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketReadEnd  FALSE
	#define EXP_TraceMgrPacketReadEnd  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketReadEnd
	#define EXT_TraceMgrPacketReadEnd
	#define GET_TraceMgrPacketReadEnd(fl)  CAL_CMGETAPI( "TraceMgrPacketReadEnd" ) 
	#define CAL_TraceMgrPacketReadEnd  TraceMgrPacketReadEnd
	#define CHK_TraceMgrPacketReadEnd  TRUE
	#define EXP_TraceMgrPacketReadEnd  CAL_CMEXPAPI( "TraceMgrPacketReadEnd" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketReadEnd
	#define EXT_TraceMgrPacketReadEnd
	#define GET_TraceMgrPacketReadEnd(fl)  CAL_CMGETAPI( "TraceMgrPacketReadEnd" ) 
	#define CAL_TraceMgrPacketReadEnd  TraceMgrPacketReadEnd
	#define CHK_TraceMgrPacketReadEnd  TRUE
	#define EXP_TraceMgrPacketReadEnd  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketReadEnd", (RTS_UINTPTR)TraceMgrPacketReadEnd, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketReadEnd
	#define EXT_CmpTraceMgrTraceMgrPacketReadEnd
	#define GET_CmpTraceMgrTraceMgrPacketReadEnd  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketReadEnd pICmpTraceMgr->ITraceMgrPacketReadEnd
	#define CHK_CmpTraceMgrTraceMgrPacketReadEnd (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketReadEnd  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketReadEnd
	#define EXT_TraceMgrPacketReadEnd
	#define GET_TraceMgrPacketReadEnd(fl)  CAL_CMGETAPI( "TraceMgrPacketReadEnd" ) 
	#define CAL_TraceMgrPacketReadEnd pICmpTraceMgr->ITraceMgrPacketReadEnd
	#define CHK_TraceMgrPacketReadEnd (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketReadEnd  CAL_CMEXPAPI( "TraceMgrPacketReadEnd" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketReadEnd  PFTRACEMGRPACKETREADEND pfTraceMgrPacketReadEnd;
	#define EXT_TraceMgrPacketReadEnd  extern PFTRACEMGRPACKETREADEND pfTraceMgrPacketReadEnd;
	#define GET_TraceMgrPacketReadEnd(fl)  s_pfCMGetAPI2( "TraceMgrPacketReadEnd", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketReadEnd, (fl), 0, 0)
	#define CAL_TraceMgrPacketReadEnd  pfTraceMgrPacketReadEnd
	#define CHK_TraceMgrPacketReadEnd  (pfTraceMgrPacketReadEnd != NULL)
	#define EXP_TraceMgrPacketReadEnd  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketReadEnd", (RTS_UINTPTR)TraceMgrPacketReadEnd, 0, 0) 
#endif




/**
 * <description>Function to store the specified trace packet in a tracefile</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="pszFileName" type="IN">File name to store trace packet</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrPacketStore(RTS_HANDLE hPacket, char *pszFileName);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETSTORE) (RTS_HANDLE hPacket, char *pszFileName);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETSTORE_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketStore
	#define EXT_TraceMgrPacketStore
	#define GET_TraceMgrPacketStore(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketStore(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketStore  FALSE
	#define EXP_TraceMgrPacketStore  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketStore
	#define EXT_TraceMgrPacketStore
	#define GET_TraceMgrPacketStore(fl)  CAL_CMGETAPI( "TraceMgrPacketStore" ) 
	#define CAL_TraceMgrPacketStore  TraceMgrPacketStore
	#define CHK_TraceMgrPacketStore  TRUE
	#define EXP_TraceMgrPacketStore  CAL_CMEXPAPI( "TraceMgrPacketStore" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketStore
	#define EXT_TraceMgrPacketStore
	#define GET_TraceMgrPacketStore(fl)  CAL_CMGETAPI( "TraceMgrPacketStore" ) 
	#define CAL_TraceMgrPacketStore  TraceMgrPacketStore
	#define CHK_TraceMgrPacketStore  TRUE
	#define EXP_TraceMgrPacketStore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketStore", (RTS_UINTPTR)TraceMgrPacketStore, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketStore
	#define EXT_CmpTraceMgrTraceMgrPacketStore
	#define GET_CmpTraceMgrTraceMgrPacketStore  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketStore pICmpTraceMgr->ITraceMgrPacketStore
	#define CHK_CmpTraceMgrTraceMgrPacketStore (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketStore  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketStore
	#define EXT_TraceMgrPacketStore
	#define GET_TraceMgrPacketStore(fl)  CAL_CMGETAPI( "TraceMgrPacketStore" ) 
	#define CAL_TraceMgrPacketStore pICmpTraceMgr->ITraceMgrPacketStore
	#define CHK_TraceMgrPacketStore (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketStore  CAL_CMEXPAPI( "TraceMgrPacketStore" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketStore  PFTRACEMGRPACKETSTORE pfTraceMgrPacketStore;
	#define EXT_TraceMgrPacketStore  extern PFTRACEMGRPACKETSTORE pfTraceMgrPacketStore;
	#define GET_TraceMgrPacketStore(fl)  s_pfCMGetAPI2( "TraceMgrPacketStore", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketStore, (fl), 0, 0)
	#define CAL_TraceMgrPacketStore  pfTraceMgrPacketStore
	#define CHK_TraceMgrPacketStore  (pfTraceMgrPacketStore != NULL)
	#define EXP_TraceMgrPacketStore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketStore", (RTS_UINTPTR)TraceMgrPacketStore, 0, 0) 
#endif




/**
 * <description>Function to restore a packet from a trace file</description>
 * <param name="pszFileName" type="IN">File name to restore trace packet</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the trace packet</result>
 */
RTS_HANDLE CDECL TraceMgrPacketRestore(char *pszFileName, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFTRACEMGRPACKETRESTORE) (char *pszFileName, RTS_RESULT *pResult);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETRESTORE_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketRestore
	#define EXT_TraceMgrPacketRestore
	#define GET_TraceMgrPacketRestore(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketRestore(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_TraceMgrPacketRestore  FALSE
	#define EXP_TraceMgrPacketRestore  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketRestore
	#define EXT_TraceMgrPacketRestore
	#define GET_TraceMgrPacketRestore(fl)  CAL_CMGETAPI( "TraceMgrPacketRestore" ) 
	#define CAL_TraceMgrPacketRestore  TraceMgrPacketRestore
	#define CHK_TraceMgrPacketRestore  TRUE
	#define EXP_TraceMgrPacketRestore  CAL_CMEXPAPI( "TraceMgrPacketRestore" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketRestore
	#define EXT_TraceMgrPacketRestore
	#define GET_TraceMgrPacketRestore(fl)  CAL_CMGETAPI( "TraceMgrPacketRestore" ) 
	#define CAL_TraceMgrPacketRestore  TraceMgrPacketRestore
	#define CHK_TraceMgrPacketRestore  TRUE
	#define EXP_TraceMgrPacketRestore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketRestore", (RTS_UINTPTR)TraceMgrPacketRestore, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketRestore
	#define EXT_CmpTraceMgrTraceMgrPacketRestore
	#define GET_CmpTraceMgrTraceMgrPacketRestore  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketRestore pICmpTraceMgr->ITraceMgrPacketRestore
	#define CHK_CmpTraceMgrTraceMgrPacketRestore (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketRestore  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketRestore
	#define EXT_TraceMgrPacketRestore
	#define GET_TraceMgrPacketRestore(fl)  CAL_CMGETAPI( "TraceMgrPacketRestore" ) 
	#define CAL_TraceMgrPacketRestore pICmpTraceMgr->ITraceMgrPacketRestore
	#define CHK_TraceMgrPacketRestore (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketRestore  CAL_CMEXPAPI( "TraceMgrPacketRestore" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketRestore  PFTRACEMGRPACKETRESTORE pfTraceMgrPacketRestore;
	#define EXT_TraceMgrPacketRestore  extern PFTRACEMGRPACKETRESTORE pfTraceMgrPacketRestore;
	#define GET_TraceMgrPacketRestore(fl)  s_pfCMGetAPI2( "TraceMgrPacketRestore", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketRestore, (fl), 0, 0)
	#define CAL_TraceMgrPacketRestore  pfTraceMgrPacketRestore
	#define CHK_TraceMgrPacketRestore  (pfTraceMgrPacketRestore != NULL)
	#define EXP_TraceMgrPacketRestore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketRestore", (RTS_UINTPTR)TraceMgrPacketRestore, 0, 0) 
#endif




/**
 * <description>Function to load a given trace file and to return the configuration it contains</description>
 * <param name="pszFileName" type="IN">File name to load</param>
 * <param name="pPacketConfiguration" type="IN">Points to a TracePacketConfiguration variable, where the packet configuration will be returned</param>
 * <param name="pRecordConfiguration" type="IN">Points to an array of TraceRecordConfiguration variables, where the trace record configuration will be returned.</param>
 * <param name="iMaxRecordCount" type="IN">Contains the maximum number of records, that can be stored in the array pRecordConfiguration</param>
 * <param name="piEffectiveRecordCount" type="OUT">Returns the effective number of records read</param>
 * <result>The error code</result>
 */
RTS_RESULT CDECL TraceMgrGetConfigFromFile(char *pszFileName, TracePacketConfiguration *pPacketConfiguration, TraceRecordConfiguration *pRecordConfiguration, RTS_I32 iMaxRecordCount, RTS_I32 *piEffectiveRecordCount);
typedef RTS_RESULT (CDECL * PFTRACEMGRGETCONFIGFROMFILE) (char *pszFileName, TracePacketConfiguration *pPacketConfiguration, TraceRecordConfiguration *pRecordConfiguration, RTS_I32 iMaxRecordCount, RTS_I32 *piEffectiveRecordCount);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRGETCONFIGFROMFILE_NOTIMPLEMENTED)
	#define USE_TraceMgrGetConfigFromFile
	#define EXT_TraceMgrGetConfigFromFile
	#define GET_TraceMgrGetConfigFromFile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrGetConfigFromFile(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrGetConfigFromFile  FALSE
	#define EXP_TraceMgrGetConfigFromFile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrGetConfigFromFile
	#define EXT_TraceMgrGetConfigFromFile
	#define GET_TraceMgrGetConfigFromFile(fl)  CAL_CMGETAPI( "TraceMgrGetConfigFromFile" ) 
	#define CAL_TraceMgrGetConfigFromFile  TraceMgrGetConfigFromFile
	#define CHK_TraceMgrGetConfigFromFile  TRUE
	#define EXP_TraceMgrGetConfigFromFile  CAL_CMEXPAPI( "TraceMgrGetConfigFromFile" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrGetConfigFromFile
	#define EXT_TraceMgrGetConfigFromFile
	#define GET_TraceMgrGetConfigFromFile(fl)  CAL_CMGETAPI( "TraceMgrGetConfigFromFile" ) 
	#define CAL_TraceMgrGetConfigFromFile  TraceMgrGetConfigFromFile
	#define CHK_TraceMgrGetConfigFromFile  TRUE
	#define EXP_TraceMgrGetConfigFromFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrGetConfigFromFile", (RTS_UINTPTR)TraceMgrGetConfigFromFile, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrGetConfigFromFile
	#define EXT_CmpTraceMgrTraceMgrGetConfigFromFile
	#define GET_CmpTraceMgrTraceMgrGetConfigFromFile  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrGetConfigFromFile pICmpTraceMgr->ITraceMgrGetConfigFromFile
	#define CHK_CmpTraceMgrTraceMgrGetConfigFromFile (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrGetConfigFromFile  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrGetConfigFromFile
	#define EXT_TraceMgrGetConfigFromFile
	#define GET_TraceMgrGetConfigFromFile(fl)  CAL_CMGETAPI( "TraceMgrGetConfigFromFile" ) 
	#define CAL_TraceMgrGetConfigFromFile pICmpTraceMgr->ITraceMgrGetConfigFromFile
	#define CHK_TraceMgrGetConfigFromFile (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrGetConfigFromFile  CAL_CMEXPAPI( "TraceMgrGetConfigFromFile" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrGetConfigFromFile  PFTRACEMGRGETCONFIGFROMFILE pfTraceMgrGetConfigFromFile;
	#define EXT_TraceMgrGetConfigFromFile  extern PFTRACEMGRGETCONFIGFROMFILE pfTraceMgrGetConfigFromFile;
	#define GET_TraceMgrGetConfigFromFile(fl)  s_pfCMGetAPI2( "TraceMgrGetConfigFromFile", (RTS_VOID_FCTPTR *)&pfTraceMgrGetConfigFromFile, (fl), 0, 0)
	#define CAL_TraceMgrGetConfigFromFile  pfTraceMgrGetConfigFromFile
	#define CHK_TraceMgrGetConfigFromFile  (pfTraceMgrGetConfigFromFile != NULL)
	#define EXP_TraceMgrGetConfigFromFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrGetConfigFromFile", (RTS_UINTPTR)TraceMgrGetConfigFromFile, 0, 0) 
#endif




/**
 * <description>Function to free memory allocated by function TraceMgrGetConfigFromFile</description>
 * <param name="pPacketConfiguration" type="IN">Points to a TracePacketConfiguration variable, where the packet configuration was stored</param>
 * <param name="pRecordConfiguration" type="IN">Points to an array of TraceRecordConfiguration variables, where the trace record configuration was stored</param>
 * <param name="iRecordCount" type="IN">The real number of records</param>
 * <result>The error code</result>
 */
RTS_RESULT CDECL TraceMgrGetConfigFromFileRelease(TracePacketConfiguration *pPacketConfiguration, TraceRecordConfiguration *pRecordConfiguration, RTS_I32 iRecordCount);
typedef RTS_RESULT (CDECL * PFTRACEMGRGETCONFIGFROMFILERELEASE) (TracePacketConfiguration *pPacketConfiguration, TraceRecordConfiguration *pRecordConfiguration, RTS_I32 iRecordCount);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRGETCONFIGFROMFILERELEASE_NOTIMPLEMENTED)
	#define USE_TraceMgrGetConfigFromFileRelease
	#define EXT_TraceMgrGetConfigFromFileRelease
	#define GET_TraceMgrGetConfigFromFileRelease(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrGetConfigFromFileRelease(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrGetConfigFromFileRelease  FALSE
	#define EXP_TraceMgrGetConfigFromFileRelease  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrGetConfigFromFileRelease
	#define EXT_TraceMgrGetConfigFromFileRelease
	#define GET_TraceMgrGetConfigFromFileRelease(fl)  CAL_CMGETAPI( "TraceMgrGetConfigFromFileRelease" ) 
	#define CAL_TraceMgrGetConfigFromFileRelease  TraceMgrGetConfigFromFileRelease
	#define CHK_TraceMgrGetConfigFromFileRelease  TRUE
	#define EXP_TraceMgrGetConfigFromFileRelease  CAL_CMEXPAPI( "TraceMgrGetConfigFromFileRelease" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrGetConfigFromFileRelease
	#define EXT_TraceMgrGetConfigFromFileRelease
	#define GET_TraceMgrGetConfigFromFileRelease(fl)  CAL_CMGETAPI( "TraceMgrGetConfigFromFileRelease" ) 
	#define CAL_TraceMgrGetConfigFromFileRelease  TraceMgrGetConfigFromFileRelease
	#define CHK_TraceMgrGetConfigFromFileRelease  TRUE
	#define EXP_TraceMgrGetConfigFromFileRelease  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrGetConfigFromFileRelease", (RTS_UINTPTR)TraceMgrGetConfigFromFileRelease, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrGetConfigFromFileRelease
	#define EXT_CmpTraceMgrTraceMgrGetConfigFromFileRelease
	#define GET_CmpTraceMgrTraceMgrGetConfigFromFileRelease  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrGetConfigFromFileRelease pICmpTraceMgr->ITraceMgrGetConfigFromFileRelease
	#define CHK_CmpTraceMgrTraceMgrGetConfigFromFileRelease (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrGetConfigFromFileRelease  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrGetConfigFromFileRelease
	#define EXT_TraceMgrGetConfigFromFileRelease
	#define GET_TraceMgrGetConfigFromFileRelease(fl)  CAL_CMGETAPI( "TraceMgrGetConfigFromFileRelease" ) 
	#define CAL_TraceMgrGetConfigFromFileRelease pICmpTraceMgr->ITraceMgrGetConfigFromFileRelease
	#define CHK_TraceMgrGetConfigFromFileRelease (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrGetConfigFromFileRelease  CAL_CMEXPAPI( "TraceMgrGetConfigFromFileRelease" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrGetConfigFromFileRelease  PFTRACEMGRGETCONFIGFROMFILERELEASE pfTraceMgrGetConfigFromFileRelease;
	#define EXT_TraceMgrGetConfigFromFileRelease  extern PFTRACEMGRGETCONFIGFROMFILERELEASE pfTraceMgrGetConfigFromFileRelease;
	#define GET_TraceMgrGetConfigFromFileRelease(fl)  s_pfCMGetAPI2( "TraceMgrGetConfigFromFileRelease", (RTS_VOID_FCTPTR *)&pfTraceMgrGetConfigFromFileRelease, (fl), 0, 0)
	#define CAL_TraceMgrGetConfigFromFileRelease  pfTraceMgrGetConfigFromFileRelease
	#define CHK_TraceMgrGetConfigFromFileRelease  (pfTraceMgrGetConfigFromFileRelease != NULL)
	#define EXP_TraceMgrGetConfigFromFileRelease  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrGetConfigFromFileRelease", (RTS_UINTPTR)TraceMgrGetConfigFromFileRelease, 0, 0) 
#endif




/**
 * <description>Check the trigger condition of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>Trigger state: ERR_OK=Trigger reached, ERR_FAILED=Trigger not reached</result>
 */
RTS_RESULT CDECL TraceMgrPacketCheckTrigger(RTS_HANDLE hPacket);
typedef RTS_RESULT (CDECL * PFTRACEMGRPACKETCHECKTRIGGER) (RTS_HANDLE hPacket);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRPACKETCHECKTRIGGER_NOTIMPLEMENTED)
	#define USE_TraceMgrPacketCheckTrigger
	#define EXT_TraceMgrPacketCheckTrigger
	#define GET_TraceMgrPacketCheckTrigger(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrPacketCheckTrigger(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrPacketCheckTrigger  FALSE
	#define EXP_TraceMgrPacketCheckTrigger  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrPacketCheckTrigger
	#define EXT_TraceMgrPacketCheckTrigger
	#define GET_TraceMgrPacketCheckTrigger(fl)  CAL_CMGETAPI( "TraceMgrPacketCheckTrigger" ) 
	#define CAL_TraceMgrPacketCheckTrigger  TraceMgrPacketCheckTrigger
	#define CHK_TraceMgrPacketCheckTrigger  TRUE
	#define EXP_TraceMgrPacketCheckTrigger  CAL_CMEXPAPI( "TraceMgrPacketCheckTrigger" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrPacketCheckTrigger
	#define EXT_TraceMgrPacketCheckTrigger
	#define GET_TraceMgrPacketCheckTrigger(fl)  CAL_CMGETAPI( "TraceMgrPacketCheckTrigger" ) 
	#define CAL_TraceMgrPacketCheckTrigger  TraceMgrPacketCheckTrigger
	#define CHK_TraceMgrPacketCheckTrigger  TRUE
	#define EXP_TraceMgrPacketCheckTrigger  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketCheckTrigger", (RTS_UINTPTR)TraceMgrPacketCheckTrigger, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrPacketCheckTrigger
	#define EXT_CmpTraceMgrTraceMgrPacketCheckTrigger
	#define GET_CmpTraceMgrTraceMgrPacketCheckTrigger  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrPacketCheckTrigger pICmpTraceMgr->ITraceMgrPacketCheckTrigger
	#define CHK_CmpTraceMgrTraceMgrPacketCheckTrigger (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrPacketCheckTrigger  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrPacketCheckTrigger
	#define EXT_TraceMgrPacketCheckTrigger
	#define GET_TraceMgrPacketCheckTrigger(fl)  CAL_CMGETAPI( "TraceMgrPacketCheckTrigger" ) 
	#define CAL_TraceMgrPacketCheckTrigger pICmpTraceMgr->ITraceMgrPacketCheckTrigger
	#define CHK_TraceMgrPacketCheckTrigger (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrPacketCheckTrigger  CAL_CMEXPAPI( "TraceMgrPacketCheckTrigger" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrPacketCheckTrigger  PFTRACEMGRPACKETCHECKTRIGGER pfTraceMgrPacketCheckTrigger;
	#define EXT_TraceMgrPacketCheckTrigger  extern PFTRACEMGRPACKETCHECKTRIGGER pfTraceMgrPacketCheckTrigger;
	#define GET_TraceMgrPacketCheckTrigger(fl)  s_pfCMGetAPI2( "TraceMgrPacketCheckTrigger", (RTS_VOID_FCTPTR *)&pfTraceMgrPacketCheckTrigger, (fl), 0, 0)
	#define CAL_TraceMgrPacketCheckTrigger  pfTraceMgrPacketCheckTrigger
	#define CHK_TraceMgrPacketCheckTrigger  (pfTraceMgrPacketCheckTrigger != NULL)
	#define EXP_TraceMgrPacketCheckTrigger  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrPacketCheckTrigger", (RTS_UINTPTR)TraceMgrPacketCheckTrigger, 0, 0) 
#endif




/**
 * <description>Add a new record to a specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="pConfiguration" type="IN">Pointer to the record configuration</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the new added record</result>
 */
RTS_HANDLE CDECL TraceMgrRecordAdd(RTS_HANDLE hPacket, TraceRecordConfiguration *pConfiguration, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFTRACEMGRRECORDADD) (RTS_HANDLE hPacket, TraceRecordConfiguration *pConfiguration, RTS_RESULT *pResult);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRRECORDADD_NOTIMPLEMENTED)
	#define USE_TraceMgrRecordAdd
	#define EXT_TraceMgrRecordAdd
	#define GET_TraceMgrRecordAdd(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrRecordAdd(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_TraceMgrRecordAdd  FALSE
	#define EXP_TraceMgrRecordAdd  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrRecordAdd
	#define EXT_TraceMgrRecordAdd
	#define GET_TraceMgrRecordAdd(fl)  CAL_CMGETAPI( "TraceMgrRecordAdd" ) 
	#define CAL_TraceMgrRecordAdd  TraceMgrRecordAdd
	#define CHK_TraceMgrRecordAdd  TRUE
	#define EXP_TraceMgrRecordAdd  CAL_CMEXPAPI( "TraceMgrRecordAdd" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrRecordAdd
	#define EXT_TraceMgrRecordAdd
	#define GET_TraceMgrRecordAdd(fl)  CAL_CMGETAPI( "TraceMgrRecordAdd" ) 
	#define CAL_TraceMgrRecordAdd  TraceMgrRecordAdd
	#define CHK_TraceMgrRecordAdd  TRUE
	#define EXP_TraceMgrRecordAdd  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrRecordAdd", (RTS_UINTPTR)TraceMgrRecordAdd, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrRecordAdd
	#define EXT_CmpTraceMgrTraceMgrRecordAdd
	#define GET_CmpTraceMgrTraceMgrRecordAdd  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrRecordAdd pICmpTraceMgr->ITraceMgrRecordAdd
	#define CHK_CmpTraceMgrTraceMgrRecordAdd (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrRecordAdd  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrRecordAdd
	#define EXT_TraceMgrRecordAdd
	#define GET_TraceMgrRecordAdd(fl)  CAL_CMGETAPI( "TraceMgrRecordAdd" ) 
	#define CAL_TraceMgrRecordAdd pICmpTraceMgr->ITraceMgrRecordAdd
	#define CHK_TraceMgrRecordAdd (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrRecordAdd  CAL_CMEXPAPI( "TraceMgrRecordAdd" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrRecordAdd  PFTRACEMGRRECORDADD pfTraceMgrRecordAdd;
	#define EXT_TraceMgrRecordAdd  extern PFTRACEMGRRECORDADD pfTraceMgrRecordAdd;
	#define GET_TraceMgrRecordAdd(fl)  s_pfCMGetAPI2( "TraceMgrRecordAdd", (RTS_VOID_FCTPTR *)&pfTraceMgrRecordAdd, (fl), 0, 0)
	#define CAL_TraceMgrRecordAdd  pfTraceMgrRecordAdd
	#define CHK_TraceMgrRecordAdd  (pfTraceMgrRecordAdd != NULL)
	#define EXP_TraceMgrRecordAdd  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrRecordAdd", (RTS_UINTPTR)TraceMgrRecordAdd, 0, 0) 
#endif




/**
 * <description>Remove a record from a specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="hRecord" type="IN">Handle to the trace record</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrRecordRemove(RTS_HANDLE hPacket, RTS_HANDLE hRecord);
typedef RTS_RESULT (CDECL * PFTRACEMGRRECORDREMOVE) (RTS_HANDLE hPacket, RTS_HANDLE hRecord);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRRECORDREMOVE_NOTIMPLEMENTED)
	#define USE_TraceMgrRecordRemove
	#define EXT_TraceMgrRecordRemove
	#define GET_TraceMgrRecordRemove(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrRecordRemove(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrRecordRemove  FALSE
	#define EXP_TraceMgrRecordRemove  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrRecordRemove
	#define EXT_TraceMgrRecordRemove
	#define GET_TraceMgrRecordRemove(fl)  CAL_CMGETAPI( "TraceMgrRecordRemove" ) 
	#define CAL_TraceMgrRecordRemove  TraceMgrRecordRemove
	#define CHK_TraceMgrRecordRemove  TRUE
	#define EXP_TraceMgrRecordRemove  CAL_CMEXPAPI( "TraceMgrRecordRemove" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrRecordRemove
	#define EXT_TraceMgrRecordRemove
	#define GET_TraceMgrRecordRemove(fl)  CAL_CMGETAPI( "TraceMgrRecordRemove" ) 
	#define CAL_TraceMgrRecordRemove  TraceMgrRecordRemove
	#define CHK_TraceMgrRecordRemove  TRUE
	#define EXP_TraceMgrRecordRemove  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrRecordRemove", (RTS_UINTPTR)TraceMgrRecordRemove, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrRecordRemove
	#define EXT_CmpTraceMgrTraceMgrRecordRemove
	#define GET_CmpTraceMgrTraceMgrRecordRemove  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrRecordRemove pICmpTraceMgr->ITraceMgrRecordRemove
	#define CHK_CmpTraceMgrTraceMgrRecordRemove (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrRecordRemove  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrRecordRemove
	#define EXT_TraceMgrRecordRemove
	#define GET_TraceMgrRecordRemove(fl)  CAL_CMGETAPI( "TraceMgrRecordRemove" ) 
	#define CAL_TraceMgrRecordRemove pICmpTraceMgr->ITraceMgrRecordRemove
	#define CHK_TraceMgrRecordRemove (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrRecordRemove  CAL_CMEXPAPI( "TraceMgrRecordRemove" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrRecordRemove  PFTRACEMGRRECORDREMOVE pfTraceMgrRecordRemove;
	#define EXT_TraceMgrRecordRemove  extern PFTRACEMGRRECORDREMOVE pfTraceMgrRecordRemove;
	#define GET_TraceMgrRecordRemove(fl)  s_pfCMGetAPI2( "TraceMgrRecordRemove", (RTS_VOID_FCTPTR *)&pfTraceMgrRecordRemove, (fl), 0, 0)
	#define CAL_TraceMgrRecordRemove  pfTraceMgrRecordRemove
	#define CHK_TraceMgrRecordRemove  (pfTraceMgrRecordRemove != NULL)
	#define EXP_TraceMgrRecordRemove  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrRecordRemove", (RTS_UINTPTR)TraceMgrRecordRemove, 0, 0) 
#endif




/**
 * <description>Get the configuration of the specified trace record</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="hRecord" type="IN">Handle to the trace record</param>
 * <param name="pConfiguration" type="OUT">Pointer to the record configuration</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrRecordGetConfig(RTS_HANDLE hPacket, RTS_HANDLE hRecord, TraceRecordConfiguration *pConfiguration);
typedef RTS_RESULT (CDECL * PFTRACEMGRRECORDGETCONFIG) (RTS_HANDLE hPacket, RTS_HANDLE hRecord, TraceRecordConfiguration *pConfiguration);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRRECORDGETCONFIG_NOTIMPLEMENTED)
	#define USE_TraceMgrRecordGetConfig
	#define EXT_TraceMgrRecordGetConfig
	#define GET_TraceMgrRecordGetConfig(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrRecordGetConfig(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrRecordGetConfig  FALSE
	#define EXP_TraceMgrRecordGetConfig  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrRecordGetConfig
	#define EXT_TraceMgrRecordGetConfig
	#define GET_TraceMgrRecordGetConfig(fl)  CAL_CMGETAPI( "TraceMgrRecordGetConfig" ) 
	#define CAL_TraceMgrRecordGetConfig  TraceMgrRecordGetConfig
	#define CHK_TraceMgrRecordGetConfig  TRUE
	#define EXP_TraceMgrRecordGetConfig  CAL_CMEXPAPI( "TraceMgrRecordGetConfig" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrRecordGetConfig
	#define EXT_TraceMgrRecordGetConfig
	#define GET_TraceMgrRecordGetConfig(fl)  CAL_CMGETAPI( "TraceMgrRecordGetConfig" ) 
	#define CAL_TraceMgrRecordGetConfig  TraceMgrRecordGetConfig
	#define CHK_TraceMgrRecordGetConfig  TRUE
	#define EXP_TraceMgrRecordGetConfig  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrRecordGetConfig", (RTS_UINTPTR)TraceMgrRecordGetConfig, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrRecordGetConfig
	#define EXT_CmpTraceMgrTraceMgrRecordGetConfig
	#define GET_CmpTraceMgrTraceMgrRecordGetConfig  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrRecordGetConfig pICmpTraceMgr->ITraceMgrRecordGetConfig
	#define CHK_CmpTraceMgrTraceMgrRecordGetConfig (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrRecordGetConfig  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrRecordGetConfig
	#define EXT_TraceMgrRecordGetConfig
	#define GET_TraceMgrRecordGetConfig(fl)  CAL_CMGETAPI( "TraceMgrRecordGetConfig" ) 
	#define CAL_TraceMgrRecordGetConfig pICmpTraceMgr->ITraceMgrRecordGetConfig
	#define CHK_TraceMgrRecordGetConfig (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrRecordGetConfig  CAL_CMEXPAPI( "TraceMgrRecordGetConfig" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrRecordGetConfig  PFTRACEMGRRECORDGETCONFIG pfTraceMgrRecordGetConfig;
	#define EXT_TraceMgrRecordGetConfig  extern PFTRACEMGRRECORDGETCONFIG pfTraceMgrRecordGetConfig;
	#define GET_TraceMgrRecordGetConfig(fl)  s_pfCMGetAPI2( "TraceMgrRecordGetConfig", (RTS_VOID_FCTPTR *)&pfTraceMgrRecordGetConfig, (fl), 0, 0)
	#define CAL_TraceMgrRecordGetConfig  pfTraceMgrRecordGetConfig
	#define CHK_TraceMgrRecordGetConfig  (pfTraceMgrRecordGetConfig != NULL)
	#define EXP_TraceMgrRecordGetConfig  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrRecordGetConfig", (RTS_UINTPTR)TraceMgrRecordGetConfig, 0, 0) 
#endif




/**
 * <description>Get the first record of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the first record</result>
 */
RTS_HANDLE CDECL TraceMgrRecordGetFirst(RTS_HANDLE hPacket, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFTRACEMGRRECORDGETFIRST) (RTS_HANDLE hPacket, RTS_RESULT *pResult);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRRECORDGETFIRST_NOTIMPLEMENTED)
	#define USE_TraceMgrRecordGetFirst
	#define EXT_TraceMgrRecordGetFirst
	#define GET_TraceMgrRecordGetFirst(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrRecordGetFirst(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_TraceMgrRecordGetFirst  FALSE
	#define EXP_TraceMgrRecordGetFirst  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrRecordGetFirst
	#define EXT_TraceMgrRecordGetFirst
	#define GET_TraceMgrRecordGetFirst(fl)  CAL_CMGETAPI( "TraceMgrRecordGetFirst" ) 
	#define CAL_TraceMgrRecordGetFirst  TraceMgrRecordGetFirst
	#define CHK_TraceMgrRecordGetFirst  TRUE
	#define EXP_TraceMgrRecordGetFirst  CAL_CMEXPAPI( "TraceMgrRecordGetFirst" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrRecordGetFirst
	#define EXT_TraceMgrRecordGetFirst
	#define GET_TraceMgrRecordGetFirst(fl)  CAL_CMGETAPI( "TraceMgrRecordGetFirst" ) 
	#define CAL_TraceMgrRecordGetFirst  TraceMgrRecordGetFirst
	#define CHK_TraceMgrRecordGetFirst  TRUE
	#define EXP_TraceMgrRecordGetFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrRecordGetFirst", (RTS_UINTPTR)TraceMgrRecordGetFirst, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrRecordGetFirst
	#define EXT_CmpTraceMgrTraceMgrRecordGetFirst
	#define GET_CmpTraceMgrTraceMgrRecordGetFirst  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrRecordGetFirst pICmpTraceMgr->ITraceMgrRecordGetFirst
	#define CHK_CmpTraceMgrTraceMgrRecordGetFirst (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrRecordGetFirst  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrRecordGetFirst
	#define EXT_TraceMgrRecordGetFirst
	#define GET_TraceMgrRecordGetFirst(fl)  CAL_CMGETAPI( "TraceMgrRecordGetFirst" ) 
	#define CAL_TraceMgrRecordGetFirst pICmpTraceMgr->ITraceMgrRecordGetFirst
	#define CHK_TraceMgrRecordGetFirst (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrRecordGetFirst  CAL_CMEXPAPI( "TraceMgrRecordGetFirst" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrRecordGetFirst  PFTRACEMGRRECORDGETFIRST pfTraceMgrRecordGetFirst;
	#define EXT_TraceMgrRecordGetFirst  extern PFTRACEMGRRECORDGETFIRST pfTraceMgrRecordGetFirst;
	#define GET_TraceMgrRecordGetFirst(fl)  s_pfCMGetAPI2( "TraceMgrRecordGetFirst", (RTS_VOID_FCTPTR *)&pfTraceMgrRecordGetFirst, (fl), 0, 0)
	#define CAL_TraceMgrRecordGetFirst  pfTraceMgrRecordGetFirst
	#define CHK_TraceMgrRecordGetFirst  (pfTraceMgrRecordGetFirst != NULL)
	#define EXP_TraceMgrRecordGetFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrRecordGetFirst", (RTS_UINTPTR)TraceMgrRecordGetFirst, 0, 0) 
#endif




/**
 * <description>Get the next record of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="hPrevRecord" type="IN">Handle to the previous trace record</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the next record</result>
 */
RTS_HANDLE CDECL TraceMgrRecordGetNext(RTS_HANDLE hPacket, RTS_HANDLE hPrevRecord, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFTRACEMGRRECORDGETNEXT) (RTS_HANDLE hPacket, RTS_HANDLE hPrevRecord, RTS_RESULT *pResult);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRRECORDGETNEXT_NOTIMPLEMENTED)
	#define USE_TraceMgrRecordGetNext
	#define EXT_TraceMgrRecordGetNext
	#define GET_TraceMgrRecordGetNext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrRecordGetNext(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_TraceMgrRecordGetNext  FALSE
	#define EXP_TraceMgrRecordGetNext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrRecordGetNext
	#define EXT_TraceMgrRecordGetNext
	#define GET_TraceMgrRecordGetNext(fl)  CAL_CMGETAPI( "TraceMgrRecordGetNext" ) 
	#define CAL_TraceMgrRecordGetNext  TraceMgrRecordGetNext
	#define CHK_TraceMgrRecordGetNext  TRUE
	#define EXP_TraceMgrRecordGetNext  CAL_CMEXPAPI( "TraceMgrRecordGetNext" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrRecordGetNext
	#define EXT_TraceMgrRecordGetNext
	#define GET_TraceMgrRecordGetNext(fl)  CAL_CMGETAPI( "TraceMgrRecordGetNext" ) 
	#define CAL_TraceMgrRecordGetNext  TraceMgrRecordGetNext
	#define CHK_TraceMgrRecordGetNext  TRUE
	#define EXP_TraceMgrRecordGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrRecordGetNext", (RTS_UINTPTR)TraceMgrRecordGetNext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrRecordGetNext
	#define EXT_CmpTraceMgrTraceMgrRecordGetNext
	#define GET_CmpTraceMgrTraceMgrRecordGetNext  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrRecordGetNext pICmpTraceMgr->ITraceMgrRecordGetNext
	#define CHK_CmpTraceMgrTraceMgrRecordGetNext (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrRecordGetNext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrRecordGetNext
	#define EXT_TraceMgrRecordGetNext
	#define GET_TraceMgrRecordGetNext(fl)  CAL_CMGETAPI( "TraceMgrRecordGetNext" ) 
	#define CAL_TraceMgrRecordGetNext pICmpTraceMgr->ITraceMgrRecordGetNext
	#define CHK_TraceMgrRecordGetNext (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrRecordGetNext  CAL_CMEXPAPI( "TraceMgrRecordGetNext" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrRecordGetNext  PFTRACEMGRRECORDGETNEXT pfTraceMgrRecordGetNext;
	#define EXT_TraceMgrRecordGetNext  extern PFTRACEMGRRECORDGETNEXT pfTraceMgrRecordGetNext;
	#define GET_TraceMgrRecordGetNext(fl)  s_pfCMGetAPI2( "TraceMgrRecordGetNext", (RTS_VOID_FCTPTR *)&pfTraceMgrRecordGetNext, (fl), 0, 0)
	#define CAL_TraceMgrRecordGetNext  pfTraceMgrRecordGetNext
	#define CHK_TraceMgrRecordGetNext  (pfTraceMgrRecordGetNext != NULL)
	#define EXP_TraceMgrRecordGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrRecordGetNext", (RTS_UINTPTR)TraceMgrRecordGetNext, 0, 0) 
#endif




/**
 * <description>Update values of a trace record (sample)</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="hRecord" type="IN">Handle to the trace record</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrRecordUpdate(RTS_HANDLE hPacket, RTS_HANDLE hRecord);
typedef RTS_RESULT (CDECL * PFTRACEMGRRECORDUPDATE) (RTS_HANDLE hPacket, RTS_HANDLE hRecord);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRRECORDUPDATE_NOTIMPLEMENTED)
	#define USE_TraceMgrRecordUpdate
	#define EXT_TraceMgrRecordUpdate
	#define GET_TraceMgrRecordUpdate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrRecordUpdate(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrRecordUpdate  FALSE
	#define EXP_TraceMgrRecordUpdate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrRecordUpdate
	#define EXT_TraceMgrRecordUpdate
	#define GET_TraceMgrRecordUpdate(fl)  CAL_CMGETAPI( "TraceMgrRecordUpdate" ) 
	#define CAL_TraceMgrRecordUpdate  TraceMgrRecordUpdate
	#define CHK_TraceMgrRecordUpdate  TRUE
	#define EXP_TraceMgrRecordUpdate  CAL_CMEXPAPI( "TraceMgrRecordUpdate" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrRecordUpdate
	#define EXT_TraceMgrRecordUpdate
	#define GET_TraceMgrRecordUpdate(fl)  CAL_CMGETAPI( "TraceMgrRecordUpdate" ) 
	#define CAL_TraceMgrRecordUpdate  TraceMgrRecordUpdate
	#define CHK_TraceMgrRecordUpdate  TRUE
	#define EXP_TraceMgrRecordUpdate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrRecordUpdate", (RTS_UINTPTR)TraceMgrRecordUpdate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrRecordUpdate
	#define EXT_CmpTraceMgrTraceMgrRecordUpdate
	#define GET_CmpTraceMgrTraceMgrRecordUpdate  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrRecordUpdate pICmpTraceMgr->ITraceMgrRecordUpdate
	#define CHK_CmpTraceMgrTraceMgrRecordUpdate (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrRecordUpdate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrRecordUpdate
	#define EXT_TraceMgrRecordUpdate
	#define GET_TraceMgrRecordUpdate(fl)  CAL_CMGETAPI( "TraceMgrRecordUpdate" ) 
	#define CAL_TraceMgrRecordUpdate pICmpTraceMgr->ITraceMgrRecordUpdate
	#define CHK_TraceMgrRecordUpdate (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrRecordUpdate  CAL_CMEXPAPI( "TraceMgrRecordUpdate" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrRecordUpdate  PFTRACEMGRRECORDUPDATE pfTraceMgrRecordUpdate;
	#define EXT_TraceMgrRecordUpdate  extern PFTRACEMGRRECORDUPDATE pfTraceMgrRecordUpdate;
	#define GET_TraceMgrRecordUpdate(fl)  s_pfCMGetAPI2( "TraceMgrRecordUpdate", (RTS_VOID_FCTPTR *)&pfTraceMgrRecordUpdate, (fl), 0, 0)
	#define CAL_TraceMgrRecordUpdate  pfTraceMgrRecordUpdate
	#define CHK_TraceMgrRecordUpdate  (pfTraceMgrRecordUpdate != NULL)
	#define EXP_TraceMgrRecordUpdate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrRecordUpdate", (RTS_UINTPTR)TraceMgrRecordUpdate, 0, 0) 
#endif




/**
 * <description>Update values of a trace record with external stored trace values</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="hRecord" type="IN">Handle to the trace record</param>
 * <param name="pBuffer" type="IN">Pointer to the external trace buffer. NOTE: This is an array of structure TraceRecordEntry!</param>
 * <param name="ulLen" type="IN">Size in bytes of the specified pBuffer</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrRecordUpdate2(RTS_HANDLE hPacket, RTS_HANDLE hRecord, TraceRecordEntry *pBuffer, RTS_UI32 ulLen);
typedef RTS_RESULT (CDECL * PFTRACEMGRRECORDUPDATE2) (RTS_HANDLE hPacket, RTS_HANDLE hRecord, TraceRecordEntry *pBuffer, RTS_UI32 ulLen);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRRECORDUPDATE2_NOTIMPLEMENTED)
	#define USE_TraceMgrRecordUpdate2
	#define EXT_TraceMgrRecordUpdate2
	#define GET_TraceMgrRecordUpdate2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrRecordUpdate2(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrRecordUpdate2  FALSE
	#define EXP_TraceMgrRecordUpdate2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrRecordUpdate2
	#define EXT_TraceMgrRecordUpdate2
	#define GET_TraceMgrRecordUpdate2(fl)  CAL_CMGETAPI( "TraceMgrRecordUpdate2" ) 
	#define CAL_TraceMgrRecordUpdate2  TraceMgrRecordUpdate2
	#define CHK_TraceMgrRecordUpdate2  TRUE
	#define EXP_TraceMgrRecordUpdate2  CAL_CMEXPAPI( "TraceMgrRecordUpdate2" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrRecordUpdate2
	#define EXT_TraceMgrRecordUpdate2
	#define GET_TraceMgrRecordUpdate2(fl)  CAL_CMGETAPI( "TraceMgrRecordUpdate2" ) 
	#define CAL_TraceMgrRecordUpdate2  TraceMgrRecordUpdate2
	#define CHK_TraceMgrRecordUpdate2  TRUE
	#define EXP_TraceMgrRecordUpdate2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrRecordUpdate2", (RTS_UINTPTR)TraceMgrRecordUpdate2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrRecordUpdate2
	#define EXT_CmpTraceMgrTraceMgrRecordUpdate2
	#define GET_CmpTraceMgrTraceMgrRecordUpdate2  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrRecordUpdate2 pICmpTraceMgr->ITraceMgrRecordUpdate2
	#define CHK_CmpTraceMgrTraceMgrRecordUpdate2 (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrRecordUpdate2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrRecordUpdate2
	#define EXT_TraceMgrRecordUpdate2
	#define GET_TraceMgrRecordUpdate2(fl)  CAL_CMGETAPI( "TraceMgrRecordUpdate2" ) 
	#define CAL_TraceMgrRecordUpdate2 pICmpTraceMgr->ITraceMgrRecordUpdate2
	#define CHK_TraceMgrRecordUpdate2 (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrRecordUpdate2  CAL_CMEXPAPI( "TraceMgrRecordUpdate2" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrRecordUpdate2  PFTRACEMGRRECORDUPDATE2 pfTraceMgrRecordUpdate2;
	#define EXT_TraceMgrRecordUpdate2  extern PFTRACEMGRRECORDUPDATE2 pfTraceMgrRecordUpdate2;
	#define GET_TraceMgrRecordUpdate2(fl)  s_pfCMGetAPI2( "TraceMgrRecordUpdate2", (RTS_VOID_FCTPTR *)&pfTraceMgrRecordUpdate2, (fl), 0, 0)
	#define CAL_TraceMgrRecordUpdate2  pfTraceMgrRecordUpdate2
	#define CHK_TraceMgrRecordUpdate2  (pfTraceMgrRecordUpdate2 != NULL)
	#define EXP_TraceMgrRecordUpdate2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrRecordUpdate2", (RTS_UINTPTR)TraceMgrRecordUpdate2, 0, 0) 
#endif




/**
 * <description>Update single value in the trace record</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="hRecord" type="IN">Handle to the trace record</param>
 * <param name="pData" type="IN">Pointer to the single record value</param>
 * <param name="ulLen" type="IN">Size of the single record value. NOTE: Must fit with the real size of the record variable!</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrRecordUpdate3(RTS_HANDLE hPacket, RTS_HANDLE hRecord, void *pData, RTS_UI32 ulLen);
typedef RTS_RESULT (CDECL * PFTRACEMGRRECORDUPDATE3) (RTS_HANDLE hPacket, RTS_HANDLE hRecord, void *pData, RTS_UI32 ulLen);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRRECORDUPDATE3_NOTIMPLEMENTED)
	#define USE_TraceMgrRecordUpdate3
	#define EXT_TraceMgrRecordUpdate3
	#define GET_TraceMgrRecordUpdate3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrRecordUpdate3(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrRecordUpdate3  FALSE
	#define EXP_TraceMgrRecordUpdate3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrRecordUpdate3
	#define EXT_TraceMgrRecordUpdate3
	#define GET_TraceMgrRecordUpdate3(fl)  CAL_CMGETAPI( "TraceMgrRecordUpdate3" ) 
	#define CAL_TraceMgrRecordUpdate3  TraceMgrRecordUpdate3
	#define CHK_TraceMgrRecordUpdate3  TRUE
	#define EXP_TraceMgrRecordUpdate3  CAL_CMEXPAPI( "TraceMgrRecordUpdate3" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrRecordUpdate3
	#define EXT_TraceMgrRecordUpdate3
	#define GET_TraceMgrRecordUpdate3(fl)  CAL_CMGETAPI( "TraceMgrRecordUpdate3" ) 
	#define CAL_TraceMgrRecordUpdate3  TraceMgrRecordUpdate3
	#define CHK_TraceMgrRecordUpdate3  TRUE
	#define EXP_TraceMgrRecordUpdate3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrRecordUpdate3", (RTS_UINTPTR)TraceMgrRecordUpdate3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrRecordUpdate3
	#define EXT_CmpTraceMgrTraceMgrRecordUpdate3
	#define GET_CmpTraceMgrTraceMgrRecordUpdate3  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrRecordUpdate3 pICmpTraceMgr->ITraceMgrRecordUpdate3
	#define CHK_CmpTraceMgrTraceMgrRecordUpdate3 (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrRecordUpdate3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrRecordUpdate3
	#define EXT_TraceMgrRecordUpdate3
	#define GET_TraceMgrRecordUpdate3(fl)  CAL_CMGETAPI( "TraceMgrRecordUpdate3" ) 
	#define CAL_TraceMgrRecordUpdate3 pICmpTraceMgr->ITraceMgrRecordUpdate3
	#define CHK_TraceMgrRecordUpdate3 (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrRecordUpdate3  CAL_CMEXPAPI( "TraceMgrRecordUpdate3" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrRecordUpdate3  PFTRACEMGRRECORDUPDATE3 pfTraceMgrRecordUpdate3;
	#define EXT_TraceMgrRecordUpdate3  extern PFTRACEMGRRECORDUPDATE3 pfTraceMgrRecordUpdate3;
	#define GET_TraceMgrRecordUpdate3(fl)  s_pfCMGetAPI2( "TraceMgrRecordUpdate3", (RTS_VOID_FCTPTR *)&pfTraceMgrRecordUpdate3, (fl), 0, 0)
	#define CAL_TraceMgrRecordUpdate3  pfTraceMgrRecordUpdate3
	#define CHK_TraceMgrRecordUpdate3  (pfTraceMgrRecordUpdate3 != NULL)
	#define EXP_TraceMgrRecordUpdate3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrRecordUpdate3", (RTS_UINTPTR)TraceMgrRecordUpdate3, 0, 0) 
#endif




/**
 * <description>Update multiple values with seperate timestamps in the trace record</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="hRecord" type="IN">Handle to the trace record</param>
 * <param name="pTimestamps" type="IN">Pointer to the array of timestamps</param>
 * <param name="pDataValues" type="IN">Pointer to the array of record values</param>
 * <param name="ulEntries" type="IN">Number of timestamp and value pairs</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrRecordUpdate4(RTS_HANDLE hPacket, RTS_HANDLE hRecord, RTS_UI32 *pTimestamps, void *pDataValues, RTS_UI32 ulEntries);
typedef RTS_RESULT (CDECL * PFTRACEMGRRECORDUPDATE4) (RTS_HANDLE hPacket, RTS_HANDLE hRecord, RTS_UI32 *pTimestamps, void *pDataValues, RTS_UI32 ulEntries);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRRECORDUPDATE4_NOTIMPLEMENTED)
	#define USE_TraceMgrRecordUpdate4
	#define EXT_TraceMgrRecordUpdate4
	#define GET_TraceMgrRecordUpdate4(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrRecordUpdate4(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrRecordUpdate4  FALSE
	#define EXP_TraceMgrRecordUpdate4  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrRecordUpdate4
	#define EXT_TraceMgrRecordUpdate4
	#define GET_TraceMgrRecordUpdate4(fl)  CAL_CMGETAPI( "TraceMgrRecordUpdate4" ) 
	#define CAL_TraceMgrRecordUpdate4  TraceMgrRecordUpdate4
	#define CHK_TraceMgrRecordUpdate4  TRUE
	#define EXP_TraceMgrRecordUpdate4  CAL_CMEXPAPI( "TraceMgrRecordUpdate4" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrRecordUpdate4
	#define EXT_TraceMgrRecordUpdate4
	#define GET_TraceMgrRecordUpdate4(fl)  CAL_CMGETAPI( "TraceMgrRecordUpdate4" ) 
	#define CAL_TraceMgrRecordUpdate4  TraceMgrRecordUpdate4
	#define CHK_TraceMgrRecordUpdate4  TRUE
	#define EXP_TraceMgrRecordUpdate4  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrRecordUpdate4", (RTS_UINTPTR)TraceMgrRecordUpdate4, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrRecordUpdate4
	#define EXT_CmpTraceMgrTraceMgrRecordUpdate4
	#define GET_CmpTraceMgrTraceMgrRecordUpdate4  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrRecordUpdate4 pICmpTraceMgr->ITraceMgrRecordUpdate4
	#define CHK_CmpTraceMgrTraceMgrRecordUpdate4 (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrRecordUpdate4  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrRecordUpdate4
	#define EXT_TraceMgrRecordUpdate4
	#define GET_TraceMgrRecordUpdate4(fl)  CAL_CMGETAPI( "TraceMgrRecordUpdate4" ) 
	#define CAL_TraceMgrRecordUpdate4 pICmpTraceMgr->ITraceMgrRecordUpdate4
	#define CHK_TraceMgrRecordUpdate4 (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrRecordUpdate4  CAL_CMEXPAPI( "TraceMgrRecordUpdate4" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrRecordUpdate4  PFTRACEMGRRECORDUPDATE4 pfTraceMgrRecordUpdate4;
	#define EXT_TraceMgrRecordUpdate4  extern PFTRACEMGRRECORDUPDATE4 pfTraceMgrRecordUpdate4;
	#define GET_TraceMgrRecordUpdate4(fl)  s_pfCMGetAPI2( "TraceMgrRecordUpdate4", (RTS_VOID_FCTPTR *)&pfTraceMgrRecordUpdate4, (fl), 0, 0)
	#define CAL_TraceMgrRecordUpdate4  pfTraceMgrRecordUpdate4
	#define CHK_TraceMgrRecordUpdate4  (pfTraceMgrRecordUpdate4 != NULL)
	#define EXP_TraceMgrRecordUpdate4  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrRecordUpdate4", (RTS_UINTPTR)TraceMgrRecordUpdate4, 0, 0) 
#endif




/**
 * <description>Update all trace packets at the task specified by name</description>
 * <param name="pszTaskName" type="IN">Pointer to the task name</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL TraceMgrDeviceTaskUpdate(char *pszTaskName);
typedef RTS_RESULT (CDECL * PFTRACEMGRDEVICETASKUPDATE) (char *pszTaskName);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRDEVICETASKUPDATE_NOTIMPLEMENTED)
	#define USE_TraceMgrDeviceTaskUpdate
	#define EXT_TraceMgrDeviceTaskUpdate
	#define GET_TraceMgrDeviceTaskUpdate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrDeviceTaskUpdate(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrDeviceTaskUpdate  FALSE
	#define EXP_TraceMgrDeviceTaskUpdate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrDeviceTaskUpdate
	#define EXT_TraceMgrDeviceTaskUpdate
	#define GET_TraceMgrDeviceTaskUpdate(fl)  CAL_CMGETAPI( "TraceMgrDeviceTaskUpdate" ) 
	#define CAL_TraceMgrDeviceTaskUpdate  TraceMgrDeviceTaskUpdate
	#define CHK_TraceMgrDeviceTaskUpdate  TRUE
	#define EXP_TraceMgrDeviceTaskUpdate  CAL_CMEXPAPI( "TraceMgrDeviceTaskUpdate" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrDeviceTaskUpdate
	#define EXT_TraceMgrDeviceTaskUpdate
	#define GET_TraceMgrDeviceTaskUpdate(fl)  CAL_CMGETAPI( "TraceMgrDeviceTaskUpdate" ) 
	#define CAL_TraceMgrDeviceTaskUpdate  TraceMgrDeviceTaskUpdate
	#define CHK_TraceMgrDeviceTaskUpdate  TRUE
	#define EXP_TraceMgrDeviceTaskUpdate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrDeviceTaskUpdate", (RTS_UINTPTR)TraceMgrDeviceTaskUpdate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrDeviceTaskUpdate
	#define EXT_CmpTraceMgrTraceMgrDeviceTaskUpdate
	#define GET_CmpTraceMgrTraceMgrDeviceTaskUpdate  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrDeviceTaskUpdate pICmpTraceMgr->ITraceMgrDeviceTaskUpdate
	#define CHK_CmpTraceMgrTraceMgrDeviceTaskUpdate (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrDeviceTaskUpdate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrDeviceTaskUpdate
	#define EXT_TraceMgrDeviceTaskUpdate
	#define GET_TraceMgrDeviceTaskUpdate(fl)  CAL_CMGETAPI( "TraceMgrDeviceTaskUpdate" ) 
	#define CAL_TraceMgrDeviceTaskUpdate pICmpTraceMgr->ITraceMgrDeviceTaskUpdate
	#define CHK_TraceMgrDeviceTaskUpdate (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrDeviceTaskUpdate  CAL_CMEXPAPI( "TraceMgrDeviceTaskUpdate" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrDeviceTaskUpdate  PFTRACEMGRDEVICETASKUPDATE pfTraceMgrDeviceTaskUpdate;
	#define EXT_TraceMgrDeviceTaskUpdate  extern PFTRACEMGRDEVICETASKUPDATE pfTraceMgrDeviceTaskUpdate;
	#define GET_TraceMgrDeviceTaskUpdate(fl)  s_pfCMGetAPI2( "TraceMgrDeviceTaskUpdate", (RTS_VOID_FCTPTR *)&pfTraceMgrDeviceTaskUpdate, (fl), 0, 0)
	#define CAL_TraceMgrDeviceTaskUpdate  pfTraceMgrDeviceTaskUpdate
	#define CHK_TraceMgrDeviceTaskUpdate  (pfTraceMgrDeviceTaskUpdate != NULL)
	#define EXP_TraceMgrDeviceTaskUpdate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrDeviceTaskUpdate", (RTS_UINTPTR)TraceMgrDeviceTaskUpdate, 0, 0) 
#endif




/**
 * <category>Features</category>
 * <type>Int</type>
 * <description>
 *	Whether address flag TRACE_VAR_ADDRESS_FLAGS_MONITORING2 is supported.
 * </description>
 */
#define TRACE_FEATURE_SUPPORTS_MONITORING2		0x00000001

/**
 * <description>
 *	Routine to check whether the trace manager component has the specified feature.
 * </description>
 * <param name="ulFeatures" type="IN">Feature flags, See corresponding category "Features".</param>
 * <result>ERR_OK if the flags are supported, an error code otherwise</result>
 */
RTS_RESULT CDECL TraceMgrHasFeature(RTS_UI32 ulFeatures);
typedef RTS_RESULT (CDECL * PFTRACEMGRHASFEATURE) (RTS_UI32 ulFeatures);
#if defined(CMPTRACEMGR_NOTIMPLEMENTED) || defined(TRACEMGRHASFEATURE_NOTIMPLEMENTED)
	#define USE_TraceMgrHasFeature
	#define EXT_TraceMgrHasFeature
	#define GET_TraceMgrHasFeature(fl)  ERR_NOTIMPLEMENTED
	#define CAL_TraceMgrHasFeature(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_TraceMgrHasFeature  FALSE
	#define EXP_TraceMgrHasFeature  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_TraceMgrHasFeature
	#define EXT_TraceMgrHasFeature
	#define GET_TraceMgrHasFeature(fl)  CAL_CMGETAPI( "TraceMgrHasFeature" ) 
	#define CAL_TraceMgrHasFeature  TraceMgrHasFeature
	#define CHK_TraceMgrHasFeature  TRUE
	#define EXP_TraceMgrHasFeature  CAL_CMEXPAPI( "TraceMgrHasFeature" ) 
#elif defined(MIXED_LINK) && !defined(CMPTRACEMGR_EXTERNAL)
	#define USE_TraceMgrHasFeature
	#define EXT_TraceMgrHasFeature
	#define GET_TraceMgrHasFeature(fl)  CAL_CMGETAPI( "TraceMgrHasFeature" ) 
	#define CAL_TraceMgrHasFeature  TraceMgrHasFeature
	#define CHK_TraceMgrHasFeature  TRUE
	#define EXP_TraceMgrHasFeature  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrHasFeature", (RTS_UINTPTR)TraceMgrHasFeature, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTraceMgrTraceMgrHasFeature
	#define EXT_CmpTraceMgrTraceMgrHasFeature
	#define GET_CmpTraceMgrTraceMgrHasFeature  ERR_OK
	#define CAL_CmpTraceMgrTraceMgrHasFeature pICmpTraceMgr->ITraceMgrHasFeature
	#define CHK_CmpTraceMgrTraceMgrHasFeature (pICmpTraceMgr != NULL)
	#define EXP_CmpTraceMgrTraceMgrHasFeature  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_TraceMgrHasFeature
	#define EXT_TraceMgrHasFeature
	#define GET_TraceMgrHasFeature(fl)  CAL_CMGETAPI( "TraceMgrHasFeature" ) 
	#define CAL_TraceMgrHasFeature pICmpTraceMgr->ITraceMgrHasFeature
	#define CHK_TraceMgrHasFeature (pICmpTraceMgr != NULL)
	#define EXP_TraceMgrHasFeature  CAL_CMEXPAPI( "TraceMgrHasFeature" ) 
#else /* DYNAMIC_LINK */
	#define USE_TraceMgrHasFeature  PFTRACEMGRHASFEATURE pfTraceMgrHasFeature;
	#define EXT_TraceMgrHasFeature  extern PFTRACEMGRHASFEATURE pfTraceMgrHasFeature;
	#define GET_TraceMgrHasFeature(fl)  s_pfCMGetAPI2( "TraceMgrHasFeature", (RTS_VOID_FCTPTR *)&pfTraceMgrHasFeature, (fl), 0, 0)
	#define CAL_TraceMgrHasFeature  pfTraceMgrHasFeature
	#define CHK_TraceMgrHasFeature  (pfTraceMgrHasFeature != NULL)
	#define EXP_TraceMgrHasFeature  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"TraceMgrHasFeature", (RTS_UINTPTR)TraceMgrHasFeature, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFTRACEMGRPACKETCREATE ITraceMgrPacketCreate;
 	PFTRACEMGRPACKETDELETE ITraceMgrPacketDelete;
 	PFTRACEMGRPACKETOPEN ITraceMgrPacketOpen;
 	PFTRACEMGRPACKETCLOSE ITraceMgrPacketClose;
 	PFTRACEMGRPACKETCOMPLETE ITraceMgrPacketComplete;
 	PFTRACEMGRPACKETGETCONFIG ITraceMgrPacketGetConfig;
 	PFTRACEMGRPACKETGETSTARTTIME ITraceMgrPacketGetStartTime;
 	PFTRACEMGRPACKETGETABSOLUTESTARTTIME ITraceMgrPacketGetAbsoluteStartTime;
 	PFTRACEMGRPACKETGETCHANGETIMESTAMP ITraceMgrPacketGetChangeTimestamp;
 	PFTRACEMGRPACKETGETFIRST ITraceMgrPacketGetFirst;
 	PFTRACEMGRPACKETGETNEXT ITraceMgrPacketGetNext;
 	PFTRACEMGRPACKETSTART ITraceMgrPacketStart;
 	PFTRACEMGRPACKETSTOP ITraceMgrPacketStop;
 	PFTRACEMGRPACKETRESTART ITraceMgrPacketRestart;
 	PFTRACEMGRPACKETGETSTATE ITraceMgrPacketGetState;
 	PFTRACEMGRPACKETSETTRIGGERSTATE ITraceMgrPacketSetTriggerState;
 	PFTRACEMGRPACKETENABLETRIGGER ITraceMgrPacketEnableTrigger;
 	PFTRACEMGRPACKETDISABLETRIGGER ITraceMgrPacketDisableTrigger;
 	PFTRACEMGRPACKETRESETTRIGGER ITraceMgrPacketResetTrigger;
 	PFTRACEMGRPACKETENABLE ITraceMgrPacketEnable;
 	PFTRACEMGRPACKETDISABLE ITraceMgrPacketDisable;
 	PFTRACEMGRPACKETREADBEGIN ITraceMgrPacketReadBegin;
 	PFTRACEMGRPACKETREADFIRST ITraceMgrPacketReadFirst;
 	PFTRACEMGRPACKETREADFIRST2 ITraceMgrPacketReadFirst2;
 	PFTRACEMGRPACKETREADNEXT ITraceMgrPacketReadNext;
 	PFTRACEMGRPACKETREADNEXT2 ITraceMgrPacketReadNext2;
 	PFTRACEMGRPACKETREAD ITraceMgrPacketRead;
 	PFTRACEMGRPACKETREAD2 ITraceMgrPacketRead2;
 	PFTRACEMGRPACKETREADEND ITraceMgrPacketReadEnd;
 	PFTRACEMGRPACKETSTORE ITraceMgrPacketStore;
 	PFTRACEMGRPACKETRESTORE ITraceMgrPacketRestore;
 	PFTRACEMGRGETCONFIGFROMFILE ITraceMgrGetConfigFromFile;
 	PFTRACEMGRGETCONFIGFROMFILERELEASE ITraceMgrGetConfigFromFileRelease;
 	PFTRACEMGRPACKETCHECKTRIGGER ITraceMgrPacketCheckTrigger;
 	PFTRACEMGRRECORDADD ITraceMgrRecordAdd;
 	PFTRACEMGRRECORDREMOVE ITraceMgrRecordRemove;
 	PFTRACEMGRRECORDGETCONFIG ITraceMgrRecordGetConfig;
 	PFTRACEMGRRECORDGETFIRST ITraceMgrRecordGetFirst;
 	PFTRACEMGRRECORDGETNEXT ITraceMgrRecordGetNext;
 	PFTRACEMGRRECORDUPDATE ITraceMgrRecordUpdate;
 	PFTRACEMGRRECORDUPDATE2 ITraceMgrRecordUpdate2;
 	PFTRACEMGRRECORDUPDATE3 ITraceMgrRecordUpdate3;
 	PFTRACEMGRRECORDUPDATE4 ITraceMgrRecordUpdate4;
 	PFTRACEMGRDEVICETASKUPDATE ITraceMgrDeviceTaskUpdate;
 	PFTRACEMGRHASFEATURE ITraceMgrHasFeature;
 } ICmpTraceMgr_C;

#ifdef CPLUSPLUS
class ICmpTraceMgr : public IBase
{
	public:
		virtual RTS_HANDLE CDECL ITraceMgrPacketCreate(TracePacketConfiguration *pConfiguration, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketDelete(RTS_HANDLE hPacket) =0;
		virtual RTS_HANDLE CDECL ITraceMgrPacketOpen(char *pszName, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketClose(RTS_HANDLE hPacket) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketComplete(RTS_HANDLE hPacket) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketGetConfig(RTS_HANDLE hPacket, TracePacketConfiguration *pConfiguration) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketGetStartTime(RTS_HANDLE hPacket, RTS_SYSTIME *pStartTime) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketGetAbsoluteStartTime(RTS_HANDLE hPacket, RTS_SYSTIME *pStartTime) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketGetChangeTimestamp(RTS_HANDLE hPacket, RTS_UI32 *pdwTimestamp) =0;
		virtual RTS_HANDLE CDECL ITraceMgrPacketGetFirst(RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL ITraceMgrPacketGetNext(RTS_HANDLE hPrevPacket, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketStart(RTS_HANDLE hPacket) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketStop(RTS_HANDLE hPacket) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketRestart(RTS_HANDLE hPacket) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketGetState(RTS_HANDLE hPacket, TraceState *pState) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketSetTriggerState(RTS_HANDLE hPacket, TriggerState *ptsTriggerState) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketEnableTrigger(RTS_HANDLE hPacket) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketDisableTrigger(RTS_HANDLE hPacket) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketResetTrigger(RTS_HANDLE hPacket) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketEnable(RTS_HANDLE hPacket) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketDisable(RTS_HANDLE hPacket) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketReadBegin(RTS_HANDLE hPacket) =0;
		virtual RTS_HANDLE CDECL ITraceMgrPacketReadFirst(RTS_HANDLE hPacket, TraceRecordEntry *pTraceBuffer, RTS_UI32 *pulReadBytes, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL ITraceMgrPacketReadFirst2(RTS_HANDLE hPacket, TraceRecordEntry *pTraceBuffer, RTS_UI32 ulTimestamp, RTS_UI32 *pulReadBytes, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL ITraceMgrPacketReadNext(RTS_HANDLE hPacket, RTS_HANDLE hPrevRecord, TraceRecordEntry *pTraceBuffer, RTS_UI32 *pulReadBytes, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL ITraceMgrPacketReadNext2(RTS_HANDLE hPacket, RTS_HANDLE hPrevRecord, TraceRecordEntry *pTraceBuffer, RTS_UI32 ulTimestamp, RTS_UI32 *pulReadBytes, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketRead(RTS_HANDLE hPacket, RTS_HANDLE hRecord, TraceRecordEntry *pTraceBuffer, RTS_UI32 *pulReadBytes) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketRead2(RTS_HANDLE hPacket, RTS_HANDLE hRecord, TraceRecordEntry *pTraceBuffer, RTS_UI32 ulTimestamp, RTS_UI32 *pulReadBytes) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketReadEnd(RTS_HANDLE hPacket) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketStore(RTS_HANDLE hPacket, char *pszFileName) =0;
		virtual RTS_HANDLE CDECL ITraceMgrPacketRestore(char *pszFileName, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ITraceMgrGetConfigFromFile(char *pszFileName, TracePacketConfiguration *pPacketConfiguration, TraceRecordConfiguration *pRecordConfiguration, RTS_I32 iMaxRecordCount, RTS_I32 *piEffectiveRecordCount) =0;
		virtual RTS_RESULT CDECL ITraceMgrGetConfigFromFileRelease(TracePacketConfiguration *pPacketConfiguration, TraceRecordConfiguration *pRecordConfiguration, RTS_I32 iRecordCount) =0;
		virtual RTS_RESULT CDECL ITraceMgrPacketCheckTrigger(RTS_HANDLE hPacket) =0;
		virtual RTS_HANDLE CDECL ITraceMgrRecordAdd(RTS_HANDLE hPacket, TraceRecordConfiguration *pConfiguration, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ITraceMgrRecordRemove(RTS_HANDLE hPacket, RTS_HANDLE hRecord) =0;
		virtual RTS_RESULT CDECL ITraceMgrRecordGetConfig(RTS_HANDLE hPacket, RTS_HANDLE hRecord, TraceRecordConfiguration *pConfiguration) =0;
		virtual RTS_HANDLE CDECL ITraceMgrRecordGetFirst(RTS_HANDLE hPacket, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL ITraceMgrRecordGetNext(RTS_HANDLE hPacket, RTS_HANDLE hPrevRecord, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ITraceMgrRecordUpdate(RTS_HANDLE hPacket, RTS_HANDLE hRecord) =0;
		virtual RTS_RESULT CDECL ITraceMgrRecordUpdate2(RTS_HANDLE hPacket, RTS_HANDLE hRecord, TraceRecordEntry *pBuffer, RTS_UI32 ulLen) =0;
		virtual RTS_RESULT CDECL ITraceMgrRecordUpdate3(RTS_HANDLE hPacket, RTS_HANDLE hRecord, void *pData, RTS_UI32 ulLen) =0;
		virtual RTS_RESULT CDECL ITraceMgrRecordUpdate4(RTS_HANDLE hPacket, RTS_HANDLE hRecord, RTS_UI32 *pTimestamps, void *pDataValues, RTS_UI32 ulEntries) =0;
		virtual RTS_RESULT CDECL ITraceMgrDeviceTaskUpdate(char *pszTaskName) =0;
		virtual RTS_RESULT CDECL ITraceMgrHasFeature(RTS_UI32 ulFeatures) =0;
};
	#ifndef ITF_CmpTraceMgr
		#define ITF_CmpTraceMgr static ICmpTraceMgr *pICmpTraceMgr = NULL;
	#endif
	#define EXTITF_CmpTraceMgr
#else	/*CPLUSPLUS*/
	typedef ICmpTraceMgr_C		ICmpTraceMgr;
	#ifndef ITF_CmpTraceMgr
		#define ITF_CmpTraceMgr
	#endif
	#define EXTITF_CmpTraceMgr
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPTRACEMGRITF_H_*/
