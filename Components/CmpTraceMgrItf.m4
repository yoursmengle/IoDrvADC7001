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

SET_INTERFACE_NAME(`CmpTraceMgr')

REF_ITF(`SysInternalLibItf.m4')
REF_ITF(`SysTimeItf.m4')
REF_ITF(`CmpMemPoolItf.m4')
REF_ITF(`CmpIecVarAccessItf.m4')
REF_ITF(`CmpAppItf.m4')

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
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

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

DEF_API(`void',`CDECL',`tracemgrgetconfigfromfile',`(tracemgrgetconfigfromfile_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x6FE07E94),0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrgetconfigfromfilerelease',`(tracemgrgetconfigfromfilerelease_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1E24AEEF),0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketchecktrigger',`(tracemgrpacketchecktrigger_struct *p)',1,0xD2E54704,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketclose',`(tracemgrpacketclose_struct *p)',1,0xBF67CDD5,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketcomplete',`(tracemgrpacketcomplete_struct *p)',1,0x77ED2847,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketcreate',`(tracemgrpacketcreate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x9F6D0ED7),0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketdelete',`(tracemgrpacketdelete_struct *p)',1,0x0BCF729C,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketdisable',`(tracemgrpacketdisable_struct *p)',1,0x05DBBAFD,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketdisabletrigger',`(tracemgrpacketdisabletrigger_struct *p)',1,0x293C8EA4,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketenable',`(tracemgrpacketenable_struct *p)',1,0x3B8A1A22,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketenabletrigger',`(tracemgrpacketenabletrigger_struct *p)',1,0x9E0738EB,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketgetabsolutestarttime',`(tracemgrpacketgetabsolutestarttime_struct *p)',1,0x4D6D7E87,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketgetchangetimestamp',`(tracemgrpacketgetchangetimestamp_struct *p)',1,0x47F49777,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketgetconfig',`(tracemgrpacketgetconfig_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF96CF7C8),0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketgetfirst',`(tracemgrpacketgetfirst_struct *p)',1,0xA4D19325,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketgetnext',`(tracemgrpacketgetnext_struct *p)',1,0x1E3AD1B8,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketgetstarttime',`(tracemgrpacketgetstarttime_struct *p)',1,0x8FC2D61B,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketgetstate',`(tracemgrpacketgetstate_struct *p)',1,0x998E4A5E,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketopen',`(tracemgrpacketopen_struct *p)',1,0x32667B41,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketreadbegin',`(tracemgrpacketreadbegin_struct *p)',1,0xDD2F3F8A,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketreadend',`(tracemgrpacketreadend_struct *p)',1,0x96F691B2,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketreadfirst',`(tracemgrpacketreadfirst_struct *p)',1,0x074AB535,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketreadfirst2',`(tracemgrpacketreadfirst2_struct *p)',1,0x8F85D7AF,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketreadnext',`(tracemgrpacketreadnext_struct *p)',1,0xDA5B316F,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketreadnext2',`(tracemgrpacketreadnext2_struct *p)',1,0xE91DB9CD,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketresettrigger',`(tracemgrpacketresettrigger_struct *p)',1,0xE73A7FCC,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketrestart',`(tracemgrpacketrestart_struct *p)',1,0xAD7F1200,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketrestore',`(tracemgrpacketrestore_struct *p)',1,0xE1899ACC,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketstart',`(tracemgrpacketstart_struct *p)',1,0xDCA4F311,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketstop',`(tracemgrpacketstop_struct *p)',1,0x3C28C22F,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrpacketstore',`(tracemgrpacketstore_struct *p)',1,0x705D2F68,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrrecordadd',`(tracemgrrecordadd_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x68ACB311),0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrrecordgetconfig',`(tracemgrrecordgetconfig_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xDAF803A5),0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrrecordgetfirst',`(tracemgrrecordgetfirst_struct *p)',1,0xDE6CF5CE,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrrecordgetnext',`(tracemgrrecordgetnext_struct *p)',1,0xA7463D33,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrrecordremove',`(tracemgrrecordremove_struct *p)',1,0xA0864F53,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrrecordupdate',`(tracemgrrecordupdate_struct *p)',1,0xD9B5E571,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrrecordupdate2',`(tracemgrrecordupdate2_struct *p)',1,0x3FE213B2,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrrecordupdate3',`(tracemgrrecordupdate3_struct *p)',1,0xA5C60449,0x03050B00)

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

DEF_API(`void',`CDECL',`tracemgrrecordupdate4',`(tracemgrrecordupdate4_struct *p)',1,0x72F1828D,0x03050B00)

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
DEF_ITF_API(`RTS_HANDLE', `CDECL', `TraceMgrPacketCreate', `(TracePacketConfiguration *pConfiguration, RTS_RESULT *pResult)')

/**
 * <description>Function to delete trace packet specified by handle</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketDelete', `(RTS_HANDLE hPacket)')


/**
 * <description>Open a trace packet specified by name</description>
 * <param name="pszName" type="IN">Handle to the trace packet</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the trace packet</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `TraceMgrPacketOpen', `(char *pszName, RTS_RESULT *pResult)')

/**
 * <description>Function closed a trace packet specified by handle</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketClose', `(RTS_HANDLE hPacket)')


/**
 * <description>Complete a trace packet to finish configuration</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketComplete', `(RTS_HANDLE hPacket)')

/**
 * <description>Get the configuration of a specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="pConfiguration" type="OUT">Pointer to the trace packet configuration</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketGetConfig', `(RTS_HANDLE hPacket, TracePacketConfiguration *pConfiguration)')

/**
 * <description>Get the start time of a trace packet. 0 if trace packet is not started.</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="pStartTime" type="OUT">Pointer to start time</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketGetStartTime', `(RTS_HANDLE hPacket, RTS_SYSTIME *pStartTime)')

/**
 * <description>Get the absolute start time of a trace packet. 0 if trace packet is not started.</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="pStartTime" type="OUT">Pointer to start time</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketGetAbsoluteStartTime', `(RTS_HANDLE hPacket, RTS_SYSTIME *pStartTime)')

/**
 * <description>Returns the timestamp of a trace packet's last modification.</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="pdwTimestamp" type="OUT">Pointer to timestamp</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketGetChangeTimestamp', `(RTS_HANDLE hPacket, RTS_UI32 *pdwTimestamp)')

/**
 * <description>Get the first registered trace packet</description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the trace packet</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `TraceMgrPacketGetFirst', `(RTS_RESULT *pResult)')

/**
 * <description>Get the next registered trace packet</description>
 * <param name="hPrevPacket" type="IN">Handle to the previous trace packet</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the trace packet</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `TraceMgrPacketGetNext', `(RTS_HANDLE hPrevPacket, RTS_RESULT *pResult)')

/**
 * <description>Start the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketStart', `(RTS_HANDLE hPacket)')

/**
 * <description>Stop the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketStop', `(RTS_HANDLE hPacket)')

/**
 * <description>Restart the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketRestart', `(RTS_HANDLE hPacket)')

/**
 * <description>Get the state of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="pState" type="OUT">Pointer to trace packet state</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketGetState', `(RTS_HANDLE hPacket, TraceState *pState)')

/**
 * <description>Set the trigger state of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="ptsTriggerState" type="IN">Pointer to trigger state to set</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketSetTriggerState', `(RTS_HANDLE hPacket, TriggerState *ptsTriggerState)')

/**
 * <description>Enable trigger of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketEnableTrigger', `(RTS_HANDLE hPacket)')

/**
 * <description>Disable trigger of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketDisableTrigger', `(RTS_HANDLE hPacket)')

/**
 * <description>Reset trigger of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketResetTrigger', `(RTS_HANDLE hPacket)')

/**
 * <description>Enable specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketEnable', `(RTS_HANDLE hPacket)')

/**
 * <description>Disable specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketDisable', `(RTS_HANDLE hPacket)')

/**
 * <description>Function at start reading trace packet (is used for online access of the trace editor)</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketReadBegin', `(RTS_HANDLE hPacket)')

/**
 * <description>Read first record out of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="pTraceBuffer" type="INOUT">Pointer to the trace buffer to copy the record values</param>
 * <param name="pulReadBytes" type="INOUT">Max size of the trace buffer [IN] and number of bytes copied [OUT]</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the actual read trace record</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `TraceMgrPacketReadFirst', `(RTS_HANDLE hPacket, TraceRecordEntry *pTraceBuffer, RTS_UI32 *pulReadBytes, RTS_RESULT *pResult)')

/**
 * <description>Read first record out of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="pTraceBuffer" type="INOUT">Pointer to the trace buffer to copy the record values</param>
 * <param name="ulTimestamp" type="IN">Timestamp to begin reading. Can be 0 [Reading from begin]</param>
 * <param name="pulReadBytes" type="INOUT">Max size of the trace buffer [IN] and number of bytes copied [OUT]</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the actual read trace record</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `TraceMgrPacketReadFirst2', `(RTS_HANDLE hPacket, TraceRecordEntry *pTraceBuffer, RTS_UI32 ulTimestamp, RTS_UI32 *pulReadBytes, RTS_RESULT *pResult)')

/**
 * <description>Read next record out of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="hPrevRecord" type="IN">Handle to the previous record</param>
 * <param name="pTraceBuffer" type="INOUT">Pointer to the trace buffer to copy the record values</param>
 * <param name="pulReadBytes" type="INOUT">Max size of the trace buffer [IN] and number of bytes copied [OUT]</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the actual read trace record</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `TraceMgrPacketReadNext', `(RTS_HANDLE hPacket, RTS_HANDLE hPrevRecord, TraceRecordEntry *pTraceBuffer, RTS_UI32 *pulReadBytes, RTS_RESULT *pResult)')

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
DEF_ITF_API(`RTS_HANDLE', `CDECL', `TraceMgrPacketReadNext2', `(RTS_HANDLE hPacket, RTS_HANDLE hPrevRecord, TraceRecordEntry *pTraceBuffer, RTS_UI32 ulTimestamp, RTS_UI32 *pulReadBytes, RTS_RESULT *pResult)')

/**
 * <description>Read specified record out of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="hRecord" type="IN">Handle to the previous record</param>
 * <param name="pTraceBuffer" type="INOUT">Pointer to the trace buffer to copy the record values</param>
 * <param name="pulReadBytes" type="INOUT">Max size of the trace buffer [IN] and number of bytes copied [OUT]</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketRead', `(RTS_HANDLE hPacket, RTS_HANDLE hRecord, TraceRecordEntry *pTraceBuffer, RTS_UI32 *pulReadBytes)')

/**
 * <description>Read specified record out of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="hRecord" type="IN">Handle to the previous record</param>
 * <param name="pTraceBuffer" type="INOUT">Pointer to the trace buffer to copy the record values</param>
 * <param name="ulTimestamp" type="IN">Timestamp to begin reading. Can be 0 [Reading from begin]</param>
 * <param name="pulReadBytes" type="INOUT">Max size of the trace buffer [IN] and number of bytes copied [OUT]</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketRead2', `(RTS_HANDLE hPacket, RTS_HANDLE hRecord, TraceRecordEntry *pTraceBuffer, RTS_UI32 ulTimestamp, RTS_UI32 *pulReadBytes)')

/**
 * <description>Function at end reading trace packet (is used for online access of the trace editor)</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketReadEnd', `(RTS_HANDLE hPacket)')

/**
 * <description>Function to store the specified trace packet in a tracefile</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="pszFileName" type="IN">File name to store trace packet</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketStore', `(RTS_HANDLE hPacket, char *pszFileName)')

/**
 * <description>Function to restore a packet from a trace file</description>
 * <param name="pszFileName" type="IN">File name to restore trace packet</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the trace packet</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `TraceMgrPacketRestore', `(char *pszFileName, RTS_RESULT *pResult)')

/**
 * <description>Function to load a given trace file and to return the configuration it contains</description>
 * <param name="pszFileName" type="IN">File name to load</param>
 * <param name="pPacketConfiguration" type="IN">Points to a TracePacketConfiguration variable, where the packet configuration will be returned</param>
 * <param name="pRecordConfiguration" type="IN">Points to an array of TraceRecordConfiguration variables, where the trace record configuration will be returned.</param>
 * <param name="iMaxRecordCount" type="IN">Contains the maximum number of records, that can be stored in the array pRecordConfiguration</param>
 * <param name="piEffectiveRecordCount" type="OUT">Returns the effective number of records read</param>
 * <result>The error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrGetConfigFromFile', `(char *pszFileName, TracePacketConfiguration *pPacketConfiguration, TraceRecordConfiguration *pRecordConfiguration, RTS_I32 iMaxRecordCount, RTS_I32 *piEffectiveRecordCount)')

/**
 * <description>Function to free memory allocated by function TraceMgrGetConfigFromFile</description>
 * <param name="pPacketConfiguration" type="IN">Points to a TracePacketConfiguration variable, where the packet configuration was stored</param>
 * <param name="pRecordConfiguration" type="IN">Points to an array of TraceRecordConfiguration variables, where the trace record configuration was stored</param>
 * <param name="iRecordCount" type="IN">The real number of records</param>
 * <result>The error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrGetConfigFromFileRelease', `(TracePacketConfiguration *pPacketConfiguration, TraceRecordConfiguration *pRecordConfiguration, RTS_I32 iRecordCount)')

/**
 * <description>Check the trigger condition of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <result>Trigger state: ERR_OK=Trigger reached, ERR_FAILED=Trigger not reached</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrPacketCheckTrigger', `(RTS_HANDLE hPacket)')

/**
 * <description>Add a new record to a specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="pConfiguration" type="IN">Pointer to the record configuration</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the new added record</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `TraceMgrRecordAdd', `(RTS_HANDLE hPacket, TraceRecordConfiguration *pConfiguration, RTS_RESULT *pResult)')

/**
 * <description>Remove a record from a specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="hRecord" type="IN">Handle to the trace record</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrRecordRemove', `(RTS_HANDLE hPacket, RTS_HANDLE hRecord)')

/**
 * <description>Get the configuration of the specified trace record</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="hRecord" type="IN">Handle to the trace record</param>
 * <param name="pConfiguration" type="OUT">Pointer to the record configuration</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrRecordGetConfig', `(RTS_HANDLE hPacket, RTS_HANDLE hRecord, TraceRecordConfiguration *pConfiguration)')

/**
 * <description>Get the first record of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the first record</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `TraceMgrRecordGetFirst', `(RTS_HANDLE hPacket, RTS_RESULT *pResult)')

/**
 * <description>Get the next record of the specified trace packet</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="hPrevRecord" type="IN">Handle to the previous trace record</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the next record</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `TraceMgrRecordGetNext', `(RTS_HANDLE hPacket, RTS_HANDLE hPrevRecord, RTS_RESULT *pResult)')

/**
 * <description>Update values of a trace record (sample)</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="hRecord" type="IN">Handle to the trace record</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrRecordUpdate', `(RTS_HANDLE hPacket, RTS_HANDLE hRecord)')

/**
 * <description>Update values of a trace record with external stored trace values</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="hRecord" type="IN">Handle to the trace record</param>
 * <param name="pBuffer" type="IN">Pointer to the external trace buffer. NOTE: This is an array of structure TraceRecordEntry!</param>
 * <param name="ulLen" type="IN">Size in bytes of the specified pBuffer</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrRecordUpdate2', `(RTS_HANDLE hPacket, RTS_HANDLE hRecord, TraceRecordEntry *pBuffer, RTS_UI32 ulLen)')

/**
 * <description>Update single value in the trace record</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="hRecord" type="IN">Handle to the trace record</param>
 * <param name="pData" type="IN">Pointer to the single record value</param>
 * <param name="ulLen" type="IN">Size of the single record value. NOTE: Must fit with the real size of the record variable!</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrRecordUpdate3', `(RTS_HANDLE hPacket, RTS_HANDLE hRecord, void *pData, RTS_UI32 ulLen)')

/**
 * <description>Update multiple values with seperate timestamps in the trace record</description>
 * <param name="hPacket" type="IN">Handle to the trace packet</param>
 * <param name="hRecord" type="IN">Handle to the trace record</param>
 * <param name="pTimestamps" type="IN">Pointer to the array of timestamps</param>
 * <param name="pDataValues" type="IN">Pointer to the array of record values</param>
 * <param name="ulEntries" type="IN">Number of timestamp and value pairs</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrRecordUpdate4', `(RTS_HANDLE hPacket, RTS_HANDLE hRecord, RTS_UI32 *pTimestamps, void *pDataValues, RTS_UI32 ulEntries)')

/**
 * <description>Update all trace packets at the task specified by name</description>
 * <param name="pszTaskName" type="IN">Pointer to the task name</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `TraceMgrDeviceTaskUpdate', `(char *pszTaskName)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`TraceMgrHasFeature',`(RTS_UI32 ulFeatures)')

#ifdef __cplusplus
}
#endif
