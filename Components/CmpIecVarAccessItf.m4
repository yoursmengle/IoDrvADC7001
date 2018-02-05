/**
 * <interfacename>CmpIecVarAccess</interfacename>
 * <description> 
 *	Interface of the IEC variable access component.
 *
 *	The expoted symbols of an application are generated in a separate child application, e.g.:
 *		Application1			// Application, which symbols are exported
 *		Application1.__Symbols	// Application, that contains the symbols
 *
 *	Each symbolic variable is generated as a separate function block, here called leaf node.
 *	Each part of the namespace of a symbol is generated as a separate function block too, here called branch node.
 *	Each data type is generated globally as a separate typenode functionblock.
 *	Each leaf node has a reference to its typenode to describe the datatype.
 *
 *	Example:
 *	Branch node
 *	     |    Branch node
 *	     |         | Leaf node
 *	     |         |  |
 *	"Application1.GVL.A"			// Variable A in the global variable list
 *	"Application1.PLC_PRG.B"		// Variable B in the main program PLC_PRG
 *	"Application1.PLC_PRG.C[5]"		// Array index 5 of the array C in the main program PLC_PRG
 *	"Application1.PLC_PRG.D.E"		// Element E of the structure D in main program PLC_PRG
 *
 *	TypeNode1=BYTE
 *	TypeNode2=INT
 *	TypeNode3=WORD
 *	TypeNode4=DWORD
 *	TypeNode5=ARRAY [0..14] OF TypeNode1
 *	TypeNode6=STRUCT{E=TypeNode3, EE=TypeNode7,EEE=TypeNode2};
 *	TypeNode7=REAL
 *
 *	Application1.GVL.A:			TypeNode1
 *	Application1.PLC_PRG.B:		TypeNode4
 *	Application1.PLC_PRG.C:		TypeNode5
 *	Application1.PLC_PRG.C[5]: 	TypeNode1
 *	Application1.PLC_PRG.D:		TypeNode6
 *	Application1.PLC_PRG.D.E:	TypeNode3
 *
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpIecVarAccess')

#include "CmpItf.h"
REF_ITF(`SysInternalLibItf.m4')
REF_ITF(`SysTimeItf.m4')
REF_ITF(`SysTimeRtcItf.m4')
REF_ITF(`CmpSrvItf.m4')
REF_ITF(`IecVarAccess_ItfsItf.m4')

#ifdef CMPIECVARACCESS3_NOTIMPLEMENTED
	#define CMPIECVARACCESS_NOTIMPLEMENTED
#endif

#ifndef IECVARACCESS_NUM_OF_STATIC_APP
	#define IECVARACCESS_NUM_OF_STATIC_APP	4
#endif

#define IECVARACCESS_ROOT_NODE		"ROOT__NODE"

/**
 * <category>Compiler switch</category>
 * <description>
 *	Compiler switches to enable/disable single features in the component.
 * </description>
 * <element name="CMPIECVARACCESS_INVALIDATENODE_SYNC">Compiler switch to activate synchronous invalidating nodes at online change. This is only
 *	for backward compatibility to the behaviour before v3.5.5.0.</element>
 * <element name="CMPIECVARACCESS_NUM_OF_STATIC_VARLISTS">Number of static variable lists statically allocated</element>
 * <element name="CMPIECVARACCESS_NUM_OF_STATIC_VARS">Number of static variables statically allocated</element>
 * <element name="CMPIECVARACCESS_NUM_OF_STATIC_BROWSEINFOS">Number of static browse infos statically allocated</element>
 */
#ifndef IECVARACCESS_NUM_OF_STATIC_VARLISTS
	#define IECVARACCESS_NUM_OF_STATIC_VARLISTS			10
#endif
#ifndef IECVARACCESS_NUM_OF_STATIC_VARS
	#define	IECVARACCESS_NUM_OF_STATIC_VARS				1000
#endif
#ifndef CMPIECVARACCESS_NUM_OF_STATIC_VARLISTS
	#define CMPIECVARACCESS_NUM_OF_STATIC_VARLISTS		IECVARACCESS_NUM_OF_STATIC_VARLISTS
#endif
#ifndef CMPIECVARACCESS_NUM_OF_STATIC_VARS
	#define CMPIECVARACCESS_NUM_OF_STATIC_VARS			IECVARACCESS_NUM_OF_STATIC_VARS
#endif
#ifndef CMPIECVARACCESS_NUM_OF_STATIC_BROWSEINFOS
	#define CMPIECVARACCESS_NUM_OF_STATIC_BROWSEINFOS	10
#endif


/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *  Obsolete: Should not be used anymore!
 *  Consistency is now configured by the client using the VLF_* varlist flags during definition of the variable list!
 *	Setting to enable/disable task consistent monitoring of all variables.
 *	1: All variables should be monitored task consistent
 *	0: No task consistency needed
 *  If enabled the communication task tries to read the variables in the background, which fit into one communication buffer. 
 *  If it is not possible to read all variables without interruption of the IEC tasks during the consistancy timeout the read 
 *  request is denied. For requests/variable lists exceeding the communication buffer there is no overall consistency ensured!
 * </description>
 */
#define IECVARACC_INT_CONSISTENCY_MONITORING				"ConsistencyMonitoring.Enable"
#ifndef IECVARACC_INT_CONSISTENCY_MONITORING_DEFAULT
	#define IECVARACC_INT_CONSISTENCY_MONITORING_DEFAULT	0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to configure the timeout in ms for consistent monitoring.
 *  The timeout is used for all kinds of consistent monitoring using CmpIecVarAccess:
 *  #1. Obsolete global setting "ConsistencyMonitoring.Enable" (see above)
 *  #2. Client setting VLF_CONSISTENT_BACKGROUND_READ
 *  #3. Client setting VLF_CONSISTENT_SYNCHRONIZED_READ 
 *  #4. Client setting VLF_CONSISTENT_SYNCHRONIZED_WRITE
 *  For #1 and #2 all the values are copied without synchronization of the IEC tasks by the low priority
 *  communication task. At the end of the loop there is an detection, if meanwhile an IEC task was scheduled.
 *  If that is true, the copy operation is started again from the beginning. The runtime system returns an
 *  error, if it was not possible to copy the values without an interruption by IEC tasks within the
 *  the "ConsistencyMonitoring.Timeout".
 *  For #3 and #4 the communication task waits for the "ConsistencyMonitoring.Timeout" to find a gap
 *  without a running IEC task. If no gap was found during this timeout, the runtime system returns an
 *  error. If a gap was found, the IEC tasks are blocked by a semaphore until copying the values is
 *  finished.
 * </description>
 */
#define IECVARACC_INT_CONSISTENCY_MONITORING_TIMEOUT				"ConsistencyMonitoring.Timeout"
#ifndef IECVARACC_INT_CONSISTENCY_MONITORING_TIMEOUT_DEFAULT
	#define IECVARACC_INT_CONSISTENCY_MONITORING_TIMEOUT_DEFAULT	1000
#endif

/**
 * <category>Event parameter</category>
 * <element name="hInterface" type="IN">Handle to the symbolic interface</element>
 * <element name="hNode" type="IN">Handle to the symbolic node</element>
 * <element name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by IecVarAccGetNode3</element>
 * <element name="ulSessionId" type="IN">Channel SessionId of the logged in client</element>
 * <element name="ulSize" type="IN">Number of bytes to write</element>
 * <element name="pValue" type="IN">Pointer to data to write</element>
 * <element name="bDeny" type="OUT">Can be set to by the event handler: 1=Write operation is denied, 0 [Default]=Write operation is possible</element>
 * <element name="cmpId" type="OUT">ComponentID of the EventHandler, that denied the operation (if bDeny=1)</element>
 */
typedef struct EVTPARAM_CmpIecVarAccess_WriteVar_
{
	RTS_HANDLE hInterface;
	RTS_HANDLE hNode;
	VariableInformationStruct2 *pVariableInformation;
	RTS_UI32 ulSessionId;
	RTS_SIZE ulSize;
	void* pValue;
	RTS_I32 bDeny;
	CMPID cmpId;
} EVTPARAM_CmpIecVarAccess_WriteVar;
#define EVTPARAMID_CmpIecVarAccess_WriteVar	0x0001
#define EVTVERSION_CmpIecVarAccess_WriteVar	0x0001

/**
 * <category>Events</category>
 * <description>Event is sent to prepare the write operation to a variable</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpIecVarAccess_WriteVar</param>
 */
#define EVT_CmpIecVarAccess_PrepareWriteVariable				MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Events</category>
 * <description>Event is sent after the write operation to a variable was done</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpIecVarAccess_WriteVar</param>
 */
#define EVT_CmpIecVarAccess_WriteVariableDone					MAKE_EVENTID(EVTCLASS_INFO, 2)


/**
 * <category>Category online services</category>
 *	<element name=""></element>
 */
#define SRV_IECVARACC_REGISTER_VAR_LIST		0x01
#define SRV_IECVARACC_UNREGISTER_VAR_LIST	0x02
#define SRV_IECVARACC_READ_VAR_LIST			0x03
#define SRV_IECVARACC_WRITE_VAR_LIST		0x04
#define SRV_IECVARACC_READ_VARS				0x05
#define SRV_IECVARACC_WRITE_VARS			0x06
#define SRV_IECVARACC_BROWSE_GET_ROOT_NODES	0x07
#define SRV_IECVARACC_BROWSE_GET_CHILDREN	0x08
#define SRV_IECVARACC_BROWSE_GET_TYPE_DESCS	0x09
#define SRV_IECVARACC_GET_ADDRESS_INFO		0x0A
#define SRV_IECVARACC_REMOVE_VARS_FROM_LIST	0x0B


/**
 * <category>Category online tags</category>
 *	<element name=""></element>
 */
#define TAG_IECVARACC_VARLIST_HANDLE		0x10
#define TAG_IECVARACC_PEERADDRESS			0x81
#define TAG_IECVARACC_PEERADDRESS_INFO		0x11
#define TAG_IECVARACC_PEERADDRESS_COMPONENT	0x12
#define TAG_IECVARACC_FLAGS					0x13
#define TAG_IECVARACC_RESULT				0x14
#define TAG_IECVARACC_NAME_LEN				0x15
#define TAG_IECVARACC_NAME					0x16
#define TAG_IECVARACC_UPDATERATE			0x17
#define TAG_IECVARACC_NUM_OF_VARS			0x18
#define TAG_IECVARACC_VAR					0x19
#define TAG_IECVARACC_VAR2					0x1A
#define TAG_IECVARACC_VAR_ACCESS_INFO		0x1B
#define TAG_IECVARACC_VAR_ERROR				0x1C
#define TAG_IECVARACC_VAR_READ				0x1D
#define TAG_IECVARACC_VAR_WRITE				0x1E
#define TAG_IECVARACC_VAR_HANDLE			0x1F
#define TAG_IECVARACC_VAR_RESULT			0x20
#define TAG_IECVARACC_VAR_NAME				0x21
#define TAG_IECVARACC_TIMESTAMP				0x22
#define TAG_IECVARACC_VAR_CLIENTHANDLE		0x23
#define TAG_IECVARACC_NAMELIST_OPT			0x24
#define TAG_IECVARACC_FIRST_VAR_HANDLE		0x25
#define TAG_IECVARACC_COMPLETE_VAR_DESC		0x26

#define TAG_IECVARACC_BROWSE_BRANCH_NODE	0x30
#define TAG_IECVARACC_BROWSE_LEAF_NODE		0x31
#define TAG_IECVARACC_BROWSE_BEGIN_INDEX	0x32
#define TAG_IECVARACC_BROWSE_TYPE_NODE		0x33
#define TAG_IECVARACC_TYPE_DESC				0xB4
#define TAG_IECVARACC_TYPE					0x35
#define TAG_IECVARACC_TYPE_INFO				0x36
#define TAG_IECVARACC_TYPE_ERROR			0x37
#define TAG_IECVARACC_INTERFACE_GUID		0x38
#define TAG_IECVARACC_INTERFACE				0x39
#define TAG_IECVARACC_CONFIG_CHANGED_TIMESTAMP 0x3A
#define TAG_IECVARACC_ADDRESS_INFO			0x3B
#define TAG_IECVARACC_APP_NAME_PREFIX		0x3C
#define TAG_IECVARACC_BROWSE_NEXT_INDEX		0x3D

#define TAG_IECVARACC_CLIENT_OPTIONS		0x40
#define TAG_IECVARACC_VAR_DESC				0x41
#define TAG_IECVARACC_VAR_OFFSET			0x42
#define TAG_IECVARACC_VAR_SIZE				0x43
#define TAG_IECVARACC_VAR_FLAGS				0x44
#define TAG_IECVARACC_VAR_PIECE_OFFSET		0x45
#define TAG_IECVARACC_VAR_PIECE_SIZE		0x46

/**
 * <category>Client options</category>
 *	<element name="CO_CLIENT_ADDRESS_RESOLUTION">Address resolution is done in client</element>
 *	<element name="CO_DIRECT_ADDRESS_INFO">Direct address info for each leaf node necessary</element>
 */
#define CO_CLIENT_ADDRESS_RESOLUTION	0x00000001
#define CO_DIRECT_ADDRESS_INFO			0x00000002


/**
 * <category>Varlist flags</category>
 *	<element name="VLF_MOTOROLA_BYTE_ORDER">Motorola byte order (big endian)</element>
 *	<element name="VLF_CONSISTENT_BACKGROUND_READ">Communication task tries to read the variables in the background. If it is not possible to read all variables 
 *  without interruption of the IEC tasks during the consistancy timeout the read request is denied with an error result ERR_NO_CONSISTENCY!</element>
 *	<element name="VLF_DATA_CHANGE">Only variables, which values changed, are transmitted</element>
 *	<element name="VLF_EXTENDABLE">Client requests to work with varlists, which can extend the comm buffer</element>
 *	<element name="VLF_EXTENDABLE_SUPPORTED">PLC supports varlists, which can extend the comm buffer</element>
 *	<element name="VLF_ACCESS_BY_VARHANDLE">Client accesses not the complete list, but only the specified vars of the list</element>
 *	<element name="VLF_SPLIT_HUGE_VARIABLES">Client can also read variables, which are larger than the communication buffer</element>
 *	<element name="VLF_CONSISTENT_SYNCHRONIZED_READ">Communication task waits for an IEC task gap and blocks the IEC tasks until the values are copied from the IEC variables to the cache</element>
 *	<element name="VLF_CONSISTENT_SYNCHRONIZED_WRITE">Communication task waits for an IEC task gap and blocks the IEC tasks until the values are copied from the cache into the IEC variables</element>
 *	<element name="VLF_CONSISTENCY_SUPPORTED">PLC supports the requested consistency (VLF_CONSISTENT_BACKGROUND_READ, VLF_CONSISTENT_SYNCHRONIZED_READ or VLF_CONSISTENT_SYNCHRONIZED_WRITE)</element>
 *	<element name="VLF_EXECUTE_CONSISTENT_READ">Flag to mark the first read service of a variable list to read in all values consistent in the cache</element>
 *	<element name="VLF_EXECUTE_CONSISTENT_WRITE">Flag to mark the last write service of a variable list to write out all values consistent from the cache into the IEC variables</element>
 *	<element name="VLF_RETURN_VARINFO">Return complete VarInfo to client, to let the client retrieve the variable the next time by varinfo instead of name</element>
 *	<element name="VLF_TIMESTAMP_UTC">Timestamp in UTC (Universal Time Coordinated), at which the values are read</element>
 *	<element name="VLF_TIMESTAMP_MS">Timestamp in millisecond, at which the values are read</element>
 *	<element name="VLF_TIMESTAMP_US">Timestamp in microseconds, at which the values are read</element>
 *	<element name="VLF_TIMESTAMP_NS">Timestamp in nanoseconds, at which the values are read</element>
 */
#define VLF_MOTOROLA_BYTE_ORDER				0x00000001
#define VLF_CONSISTENT_BACKGROUND_READ		0x00000002
#define VLF_CONSISTENT						VLF_CONSISTENT_BACKGROUND_READ
#define VLF_DATA_CHANGE						0x00000004
#define VLF_EXTENDABLE						0x00000008
#define VLF_EXTENDABLE_SUPPORTED 			0x00000010
#define VLF_ACCESS_BY_VARHANDLE				0x00000020
#define VLF_SPLIT_HUGE_VARIABLES			0x00000040
#define VLF_CONSISTENT_SYNCHRONIZED_READ	0x00000080
#define VLF_CONSISTENT_SYNCHRONIZED_WRITE	0x00000100
#define VLF_CONSISTENCY_SUPPORTED			0x00000200
#define VLF_EXECUTE_CONSISTENT_READ			0x00000400
#define VLF_EXECUTE_CONSISTENT_WRITE		0x00000800
#define VLF_RETURN_VARINFO					0x00001000
#define VLF_TIMESTAMP_UTC					0x00010000
#define VLF_TIMESTAMP_TIMEDATE				0x00020000
#define VLF_TIMESTAMP_MS					0x00040000
#define VLF_TIMESTAMP_US					0x00080000
#define VLF_TIMESTAMP_NS					0x00100000

typedef struct
{
	unsigned short usNameLen;
	char *pszName;
	RTS_HANDLE ulInterface;
} BrowseBranchNode;


/**
 * <category>Branch leaf node flags</category>
 *	<element name="BLNF_DIRECTADDRESS">The leaf node has a direct address (%M, %I, %Q)</element>
 */
#define BLNF_DIRECTADDRESS			0x00000001

typedef struct
{
	unsigned short usNameLen;
	TypeClass3 typeClass;
	AccessRights accessRights;
	RTS_SIZE ulSize;
	RTS_HANDLE ulInterface;
	RTS_HANDLE ulTypeNode;
	char *pszName;
	RTS_HANDLE ulNode;
	RTS_SIZE ulOffset;
	RTS_UI32 ulFlags;
} BrowseLeafNode;

typedef struct
{
	TypeClass3 type;
	RTS_UI32 ulSize;
	RTS_HANDLE hVar;
} VarAccessInfo;

typedef struct
{
	RTS_UI32 ulFlags;
	RTS_UI32 ulUpdateRateMs;
	RTS_UI32 ulVars;
} RegisterVarList;

typedef struct
{
	unsigned short usNameLen;
	char *pszVars;
} RegisterVar;

typedef struct
{
	unsigned short usNameLen;
	char *pszVars;
	RTS_UI32 hClientHandle;
} RegisterVar2;

typedef struct
{
	RTS_HANDLE hVarList;
	RTS_UI32 ulFlags;
	PEERADDRESS ProxyNetworkAddress;
	short sResult;
} RegisterVarListReply;

typedef struct
{
	RTS_HANDLE hVar;
	TypeClass3 type;
	RTS_UI32 ulSize;
} RegisterVarReply;

typedef struct
{
	RTS_UI32 ulFlags;
	RTS_UI32 ulAlignDummy;
	union
	{
		RTS_SYSTIME stTimestamp;
		RTS_UI32 ulTimestamp;
		RTS_SYSTIMEDATE dateTimestamp;
	} Timestamp;
	short sResult;
} VarListReply;

/**
 * <category>Quality</category>
 *	<element name="QUALITY_GOOD">Value could be read with no error</element>
 *	<element name="QUALITY_NOT_CONNECTED">No connection to the target (for remote symbol access)</element>
 *	<element name="QUALITY_NOT_AVAILABLE">Variable is not available</element>
 *	<element name="QUALITY_NO_ACCESS_RIGHT">No access right to the variable</element>
 */
#define QUALITY_GOOD				0
#define QUALITY_NOT_CONNECTED		1
#define QUALITY_NOT_AVAILABLE		2
#define QUALITY_NO_ACCESS_RIGHT		3

typedef struct
{
	RTS_UI32 ulQuality;
	void *pValue;

	RTS_HANDLE hVar;
	RTS_UI32 hClientHandle;
} VarValueReply;

/**
 * <description>TypeClassFlags: Flags for VarAccGetTypeClassFromType</description>
 * <element name="TCF_GET_TYPE">Get the native TypeClass3:
 *	- For an array you get TYPE3_ARRAY
 *	- For an structure/FB you get TYPE3_USERDEF
 *	- For simple types you get the native TypeClass3 entry
 * </element>
 * <element name="TCF_GET_TYPE">Return the default type class (as returned in IecVarAccGetTypeClass().</element>
 * <element name="TCF_GET_BASE_TYPE">Get the base type of an array as TypeClass3. E.g. for an ARRAY [] OF BYTE you get TYPE3_BYTE.</element>
 * <element name="TCF_GET_POU_TYPE">Get the POUType of a userdef type (TYPE3_USERDEF). See POUTypeClass.</element>
 * <element name="TCF_GET_ENUM_TYPE">Return TYPE3_ENUM if the type is an enum. See TypeClass3 in SysInternalLibItf.h for details.</element>
 */
#define TCF_GET_TYPE			0
#define TCF_GET_BASE_TYPE		1
#define TCF_GET_POU_TYPE		2
#define TCF_GET_ENUM_TYPE		4

/**
 * <category>POUTypeClass. This is an extension in the hiword of TypeClass3</category>
 * <element name="TYPE_POU_FUNCTION">POU type function</element>
 * <element name="TYPE_POU_FUNCTION_BLOCK">POU type function block</element>
 * <element name="TYPE_POU_PROGRAM">POU type program</element>
 * <element name="TYPE_POU_STRUCTURE">POU type structure</element>
 */
#define TYPE_POU_FUNCTION			0x0100
#define TYPE_POU_FUNCTION_BLOCK		0x0200
#define TYPE_POU_PROGRAM			0x0300
#define TYPE_POU_STRUCTURE			0x0400

/**
 * <category>POUClass</category>
 * <element name="POU_CLASS_NONE">Simple data type</element>
 * <element name="POU_CLASS_NONE">POU type function</element>
 * <element name="POU_CLASS_FUNCTION">POU type function block</element>
 * <element name="POU_CLASS_FUNCTION_BLOCK">POU type program</element>
 * <element name="POU_CLASS_STRUCTURE">POU type structure</element>
 */
typedef enum _POUClass
{
	POU_CLASS_NONE = 0,
	POU_CLASS_FUNCTION = TYPE_POU_FUNCTION,
	POU_CLASS_FUNCTION_BLOCK = TYPE_POU_FUNCTION_BLOCK,
	POU_CLASS_PROGRAM = TYPE_POU_PROGRAM,
	POU_CLASS_STRUCTURE = TYPE_POU_STRUCTURE,
} POUClass;

/**
 * <category>NodeFlags</category>
 *	<element name="LTNF_NONE">native data (e.g. global variable)</element>
 *	<element name="LTNF_VAR">local variable</element>
 *	<element name="LTNF_VAR_INPUT">input variable</element>
 *	<element name="LTNF_VAR_OUTPUT">output variable</element>
 *	<element name="LTNF_VAR_IN_OUT">in_out variable</element>
 *	<element name="LTNF_VAR_EXEC">Executable member (representing __Main(), method, action etc...)</element>
 *	<element name="LTNF_VAR_PROP">Property with monitoring-type "variable"</element>
 *	<element name="LTNF_CALL_PROP">Property with monitoring-type "call"</element>
 *	<element name="LTNF_INHERITED_MEMBER">The member is inherited from a base type.</element>
 */
#define LTNF_NONE				0x00000000
#define LTNF_VAR				0x00000001
#define LTNF_VAR_INPUT			0x00000002
#define LTNF_VAR_OUTPUT			0x00000004
#define LTNF_VAR_IN_OUT			0x00000008
#define LTNF_VAR_EXEC           0x00000010
#define LTNF_VAR_PROP           0x00000020
#define LTNF_CALL_PROP          0x00000040
#define LTNF_INHERITED_MEMBER   0x00010000


typedef IIecVarAccess_Itfs_C	IIecVarAccess;
typedef IIecVarAccess_Itfs_C	IIecVarAccess2;
typedef IIecVarAccess_Itfs_C	IIecVarAccess3;


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>iecvaraccbrowsedown2</description>
 */
typedef struct tagiecvaraccbrowsedown2_struct
{
	RTS_IEC_HANDLE hInterface;			/* VAR_INPUT */	
	IBaseTreeNode *hNode;				/* VAR_INPUT */	
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	IBaseTreeNode *IecVarAccBrowseDown2;	/* VAR_OUTPUT */	
} iecvaraccbrowsedown2_struct;

DEF_API(`void',`CDECL',`iecvaraccbrowsedown2',`(iecvaraccbrowsedown2_struct *p)',1,0,0x03050A00)

/**
 * <description>iecvaraccbrowsegetnext2</description>
 */
typedef struct tagiecvaraccbrowsegetnext2_struct
{
	RTS_IEC_HANDLE hInterface;			/* VAR_INPUT */	
	IBaseTreeNode *hNode;				/* VAR_INPUT */	
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	IBaseTreeNode *IecVarAccBrowseGetNext2;	/* VAR_OUTPUT */	
} iecvaraccbrowsegetnext2_struct;

DEF_API(`void',`CDECL',`iecvaraccbrowsegetnext2',`(iecvaraccbrowsegetnext2_struct *p)',1,0,0x03050A00)

/**
 * <description>iecvaraccbrowserecursive</description>
 */
typedef struct tagiecvaraccbrowserecursive_struct
{
	RTS_IEC_HANDLE hInterface;			/* VAR_INPUT */	
	IBaseTreeNode *hNode;				/* VAR_INPUT */	
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_BYTE *pfBrowseCallback;		/* VAR_INPUT */	
	RTS_IEC_BYTE *pUserParameter;		/* VAR_INPUT */	
	RTS_IEC_RESULT IecVarAccBrowseRecursive;	/* VAR_OUTPUT */	
} iecvaraccbrowserecursive_struct;

DEF_API(`void',`CDECL',`iecvaraccbrowserecursive',`(iecvaraccbrowserecursive_struct *p)',1,0,0x03050A00)

/**
 * <description>iecvaraccbrowseup2</description>
 */
typedef struct tagiecvaraccbrowseup2_struct
{
	RTS_IEC_HANDLE hInterface;			/* VAR_INPUT */	
	IBaseTreeNode *hNode;				/* VAR_INPUT */	
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	IBaseTreeNode *IecVarAccBrowseUp2;	/* VAR_OUTPUT */	
} iecvaraccbrowseup2_struct;

DEF_API(`void',`CDECL',`iecvaraccbrowseup2',`(iecvaraccbrowseup2_struct *p)',1,0,0x03050A00)

/**
 * <description>iecvaraccexitvarinfo</description>
 */
typedef struct tagiecvaraccexitvarinfo_struct
{
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT IecVarAccExitVarInfo;	/* VAR_OUTPUT */	
} iecvaraccexitvarinfo_struct;

DEF_API(`void',`CDECL',`iecvaraccexitvarinfo',`(iecvaraccexitvarinfo_struct *p)',1,0,0x03050A00)

/**
 * <description>iecvaraccgetfirstinterface</description>
 */
typedef struct tagiecvaraccgetfirstinterface_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	IIecVarAccess3 *IecVarAccGetFirstInterface;	/* VAR_OUTPUT */	
} iecvaraccgetfirstinterface_struct;

DEF_API(`void',`CDECL',`iecvaraccgetfirstinterface',`(iecvaraccgetfirstinterface_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xDAF18C6C),0x03050A00)

/**
 * <description>iecvaraccgetfirstinterface2</description>
 */
typedef struct tagiecvaraccgetfirstinterface2_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	IBase *IecVarAccGetFirstInterface2;	/* VAR_OUTPUT */	
} iecvaraccgetfirstinterface2_struct;

DEF_API(`void',`CDECL',`iecvaraccgetfirstinterface2',`(iecvaraccgetfirstinterface2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x35A559A4),0x03050A00)

/**
 * <description>iecvaraccgetnextinterface</description>
 */
typedef struct tagiecvaraccgetnextinterface_struct
{
	IIecVarAccess3 *pIPrev;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	IIecVarAccess3 *IecVarAccGetNextInterface;	/* VAR_OUTPUT */	
} iecvaraccgetnextinterface_struct;

DEF_API(`void',`CDECL',`iecvaraccgetnextinterface',`(iecvaraccgetnextinterface_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x7143BBE4),0x03050A00)

/**
 * <description>iecvaraccgetnextinterface2</description>
 */
typedef struct tagiecvaraccgetnextinterface2_struct
{
	IBase *pIPrev;						/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	IBase *IecVarAccGetNextInterface2;	/* VAR_OUTPUT */	
} iecvaraccgetnextinterface2_struct;

DEF_API(`void',`CDECL',`iecvaraccgetnextinterface2',`(iecvaraccgetnextinterface2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xDCA77F90),0x03050A00)

/**
 * <description>iecvaraccgetnode4</description>
 */
typedef struct tagiecvaraccgetnode4_struct
{
	RTS_IEC_STRING *pszPath;			/* VAR_INPUT */	
	RTS_IEC_HANDLE *phInterface;		/* VAR_INPUT */	
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	IBaseTreeNode *IecVarAccGetNode4;	/* VAR_OUTPUT */	
} iecvaraccgetnode4_struct;

DEF_API(`void',`CDECL',`iecvaraccgetnode4',`(iecvaraccgetnode4_struct *p)',1,0,0x03050A00)

/**
 * <description>iecvaraccgetnodefullpath4</description>
 */
typedef struct tagiecvaraccgetnodefullpath4_struct
{
	RTS_IEC_HANDLE hInterface;			/* VAR_INPUT */	
	IBaseTreeNode *hNode;				/* VAR_INPUT */	
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_STRING *pszPath;			/* VAR_INPUT */	
	RTS_IEC_DINT iMaxPath;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_DINT IecVarAccGetNodeFullPath4;	/* VAR_OUTPUT */	
} iecvaraccgetnodefullpath4_struct;

DEF_API(`void',`CDECL',`iecvaraccgetnodefullpath4',`(iecvaraccgetnodefullpath4_struct *p)',1,0,0x03050A00)

/**
 * <description>iecvaraccgetnodename4</description>
 */
typedef struct tagiecvaraccgetnodename4_struct
{
	RTS_IEC_HANDLE hInterface;			/* VAR_INPUT */	
	IBaseTreeNode *hNode;				/* VAR_INPUT */	
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_STRING *pszNodeName;		/* VAR_INPUT */	
	RTS_IEC_UDINT nNodeNameLen;			/* VAR_INPUT */	
	RTS_IEC_RESULT IecVarAccGetNodeName4;	/* VAR_OUTPUT */	
} iecvaraccgetnodename4_struct;

DEF_API(`void',`CDECL',`iecvaraccgetnodename4',`(iecvaraccgetnodename4_struct *p)',1,0,0x03050A00)

/**
 * <description>iecvaraccinitvarinfo</description>
 */
typedef struct tagiecvaraccinitvarinfo_struct
{
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_UINT nSizeOfVarInfo;		/* VAR_INPUT */	
	RTS_IEC_RESULT IecVarAccInitVarInfo;	/* VAR_OUTPUT */	
} iecvaraccinitvarinfo_struct;

DEF_API(`void',`CDECL',`iecvaraccinitvarinfo',`(iecvaraccinitvarinfo_struct *p)',1,0,0x03050A00)

/**
 * <description>iecvaraccinvalidatenode</description>
 */
typedef struct tagiecvaraccinvalidatenode_struct
{
	RTS_IEC_HANDLE hNode;				/* VAR_INPUT */	
	RTS_IEC_RESULT IecVarAccInvalidateNode;	/* VAR_OUTPUT */	
} iecvaraccinvalidatenode_struct;

DEF_API(`void',`CDECL',`iecvaraccinvalidatenode',`(iecvaraccinvalidatenode_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0C905F23),0x03050A00)

/**
 * <description>iecvaraccnodeinfoaddreference</description>
 */
typedef struct tagiecvaraccnodeinfoaddreference_struct
{
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	/* Pointer to the variable information. */
	RTS_IEC_BYTE *pReferenceInfoData;	/* VAR_INPUT */	/* If this pointer is non-null, the runtime will copy the data into the new buffer.
 If this pointer is null, the new buffer memory will be cleared to zero. */
	RTS_IEC_XWORD nInfoSize;			/* VAR_INPUT */	/* The size of the memory to allocate. */
	RTS_IEC_BYTE **pNewReferenceInfo;	/* VAR_INPUT */	/* If this pointer is non-null, the runtime will store the address of
 the allocated block in this pointer. (This is the same as a subsequent
 call to VarAccNodeInfoGetReference() shall return.) */
	RTS_IEC_RESULT IecVarAccNodeInfoAddReference;	/* VAR_OUTPUT */	
} iecvaraccnodeinfoaddreference_struct;

DEF_API(`void',`CDECL',`iecvaraccnodeinfoaddreference',`(iecvaraccnodeinfoaddreference_struct *p)',1,RTSITF_GET_SIGNATURE(0xB66D74DC, 0x54D1E739),0x03050A00)

/**
 * <description>iecvaraccnodeinfogetreference</description>
 */
typedef struct tagiecvaraccnodeinfogetreference_struct
{
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_BYTE *IecVarAccNodeInfoGetReference;	/* VAR_OUTPUT */	
} iecvaraccnodeinfogetreference_struct;

DEF_API(`void',`CDECL',`iecvaraccnodeinfogetreference',`(iecvaraccnodeinfogetreference_struct *p)',1,RTSITF_GET_SIGNATURE(0x4ABE0CEB, 0x84253FCA),0x03050A00)

/**
 * <description>iecvaraccnodeinforemovereference</description>
 */
typedef struct tagiecvaraccnodeinforemovereference_struct
{
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT IecVarAccNodeInfoRemoveReference;	/* VAR_OUTPUT */	
} iecvaraccnodeinforemovereference_struct;

DEF_API(`void',`CDECL',`iecvaraccnodeinforemovereference',`(iecvaraccnodeinforemovereference_struct *p)',1,RTSITF_GET_SIGNATURE(0xAAD90063, 0x725A147D),0x03050A00)

/**
 * <description>iecvaraccregisterinstance</description>
 */
typedef struct tagiecvaraccregisterinstance_struct
{
	IIecVarAccess *pIIecVarAccess;		/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE IecVarAccRegisterInstance;	/* VAR_OUTPUT */	
} iecvaraccregisterinstance_struct;

DEF_API(`void',`CDECL',`iecvaraccregisterinstance',`(iecvaraccregisterinstance_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x2838418D),0x03050A00)

/**
 * <description>iecvaraccregisterinstance2</description>
 */
typedef struct tagiecvaraccregisterinstance2_struct
{
	IIecVarAccess2 *pIIecVarAccess2;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE IecVarAccRegisterInstance2;	/* VAR_OUTPUT */	
} iecvaraccregisterinstance2_struct;

DEF_API(`void',`CDECL',`iecvaraccregisterinstance2',`(iecvaraccregisterinstance2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x12CBCF4F),0x03050A00)

/**
 * <description>iecvaraccregisterinstance3</description>
 */
typedef struct tagiecvaraccregisterinstance3_struct
{
	IIecVarAccess3 *pIIecVarAccess3;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE IecVarAccRegisterInstance3;	/* VAR_OUTPUT */	
} iecvaraccregisterinstance3_struct;

DEF_API(`void',`CDECL',`iecvaraccregisterinstance3',`(iecvaraccregisterinstance3_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC1E3F2D6),0x03050A00)

/**
 * <description>iecvaraccregisterinstancebase</description>
 */
typedef struct tagiecvaraccregisterinstancebase_struct
{
	IBase *pIBase;						/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE IecVarAccRegisterInstanceBase;	/* VAR_OUTPUT */	
} iecvaraccregisterinstancebase_struct;

DEF_API(`void',`CDECL',`iecvaraccregisterinstancebase',`(iecvaraccregisterinstancebase_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCD8685B0),0x03050A00)

/**
 * <description>iecvaraccsetsymbolconfigcrc</description>
 */
typedef struct tagiecvaraccsetsymbolconfigcrc_struct
{
	RTS_IEC_HANDLE hInstance;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiCrc;				/* VAR_INPUT */	
	RTS_IEC_RESULT IecVarAccSetSymbolconfigCrc;	/* VAR_OUTPUT */	
} iecvaraccsetsymbolconfigcrc_struct;

DEF_API(`void',`CDECL',`iecvaraccsetsymbolconfigcrc',`(iecvaraccsetsymbolconfigcrc_struct *p)',1,0xFDCEC8DA,0x03050A00)

/**
 * <description>iecvaraccunregisterinstance</description>
 */
typedef struct tagiecvaraccunregisterinstance_struct
{
	RTS_IEC_HANDLE hInstance;			/* VAR_INPUT */	
	RTS_IEC_RESULT IecVarAccUnregisterInstance;	/* VAR_OUTPUT */	
} iecvaraccunregisterinstance_struct;

DEF_API(`void',`CDECL',`iecvaraccunregisterinstance',`(iecvaraccunregisterinstance_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xEDB8227D),0x03050A00)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

typedef enum _IecVarAccBrowseDirection
{
	BROWSEDIRECTION_ROOT,
	BROWSEDIRECTION_DOWN,
	BROWSEDIRECTION_NEXT,
	BROWSEDIRECTION_UP
} IecVarAccBrowseDirection;

typedef struct _IecVarAccBrowseCallback
{
	RTS_HANDLE hInterface;
	RTS_HANDLE hNode;
	VariableInformationStruct3 *pVarInfo;
	IecVarAccBrowseDirection bd;
	void *pUserParameter;
} IecVarAccBrowseCallback;

/**
 * <description> Callback function </description>
 * <param name="pEventParam" type="IN">Pointer to the event parameter.</param>
 * <result></result>
 */
typedef void (CDECL *PF_IECVARACC_BROWSECALLBACK)(IecVarAccBrowseCallback *pBrowseParam);

/**
 * <description>Initialize the VarInfo.
 *	NOTE:
 *	You can cast a VariableInformationStruct3 to VariableInformationStruct2, but the nSizeOfVarInfo must match the real VariableInformationStruct3!</description>
 * <param name="pVarInfo" type="IN">Pointer to varinfo to intialize</param>
 * <param name="nSizeOfVarInfo" type="IN">Size of the varinfo</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecVarAccInitVarInfo',`(VariableInformationStruct2 *pVarInfo, RTS_UI16 nSizeOfVarInfo)')

/**
 * <description>Release the VarInfo.
 *	NOTE:
 *	You can cast a VariableInformationStruct3 to VariableInformationStruct2, but the nSizeOfVarInfo must match the real VariableInformationStruct3!</description>
 * <param name="pVarInfo" type="IN">Pointer to varinfo to release</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecVarAccExitVarInfo',`(VariableInformationStruct2 *pVarInfo)')

/**
 * <description>Copy content of VarInfo.
 *	NOTE:
 *	pVariableInformationDest must be initialized with IecVarAccInitVarInfo() before calling this function!
 * </description>
 * <param name="pVariableInformationDest" type="INOUT">Pointer to destination varinfo to copy to</param>
 * <param name="pVariableInformationSrc" type="IN">Pointer to source varinfo to copy from</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecVarAccCopyVarInfo',`(VariableInformationStruct2 *pVariableInformationDest, VariableInformationStruct2 *pVariableInformationSrc)')

/**
 * <description>Get the first symbolic interface. Each symbolic application is called here an interface.</description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the first symbolic interface (symbolic application, called hInterface)</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecVarAccGetFirstInterface',`(RTS_RESULT *pResult)')

/**
 * <description>Get the next symbolic interface</description>
 * <param name="hPrevInterface" type="IN">Handle to the previous interface</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the next symbolic interface (symbolic application)</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecVarAccGetNextInterface',`(RTS_HANDLE hPrevInterface, RTS_RESULT *pResult)')

/**
 * <description>Get the application name of the specified interface</description>
 * <param name="hInterface" type="IN">Handle to the interface</param>
 * <param name="pszApplicationName" type="OUT">Pointer to return application name</param>
 * <param name="nMaxLen" type="IN">Maximum string length</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecVarAccGetApplicationName',`(RTS_HANDLE hInterface, char *pszApplicationName, int nMaxLen)')


/**
 * <description>Create variable list. A variable list can be used to add variables and to access and handle all these
 *	variables with only one handle.</description>
 * <param name="ulChannelId" type="IN">Online channelid to attach the variable list to a valid online connection of the channel server</param>
 * <param name="ulFlags" type="IN">Optional flags for the variable list, see category (Varlist flags)</param>
 * <param name="ulUpdateRateMs" type="IN">Requested update rate for the complete variable list in milliseconds</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the variable list (called hVarList)</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecVarAccCreateVarList',`(RTS_UI32 ulChannelId, RTS_UI32 ulFlags, RTS_UI32 ulUpdateRateMs, RTS_RESULT *pResult)')

/**
 * <description>Delete the specified variable list</description>
 * <param name="hVarList" type="IN">Handle to the variable list</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecVarAccDeleteVarList',`(RTS_HANDLE hVarList)')

/**
 * <description>Delete all variable lists that are assigned to the specified sessionid</description>
 * <param name="ulChannelId" type="IN">Online channelid of a valid online connection of the channel server</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecVarAccDeleteVarLists',`(RTS_UI32 ulChannelId)')

/**
 * <description>Delete all variable lists</description>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecVarAccDeleteAllLists',`(void)')

/**
 * <description>Get the flags that are assigned to the variable list</description>
 * <param name="hVarList" type="IN">Handle to the variable list</param>
 * <param name="pulFlags" type="OUT">Pointer to get the flags</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecVarAccVarListGetFlags',`(RTS_HANDLE hVarList, RTS_UI32 *pulFlags)')

/**
 * <description>Append variable to the variable list</description>
 * <param name="hVarList" type="IN">Handle to the variable list</param>
 * <param name="pszVar" type="IN">Pointer to the variable name to add to the variable list</param>
 * <param name="ulSize" type="IN">Requested size to read. 0xFFFFFFFF: Use real variable size</param>
 * <param name="hClientHandle" type="IN">Private handle of the client. For client internal use only</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the appended variable (called hVar)</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecVarAccAppendVar',`(RTS_HANDLE hVarList, char *pszVar, RTS_SIZE ulSize, RTS_UI32 hClientHandle, RTS_RESULT *pResult)')

/**
 * <description>Remove a variable from the specified variable list</description>
 * <param name="hVarList" type="IN">Handle to the variable list</param>
 * <param name="hVar" type="IN">Handle to the variable</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecVarAccRemoveVar',`(RTS_HANDLE hVarList, RTS_HANDLE hVar)')

/**
 * <description>Get the first variable of the specified variable list</description>
 * <param name="hVarList" type="IN">Handle to the variable list</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the first variable in the variable list (called hVar)</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecVarAccGetFirstVar',`(RTS_HANDLE hVarList, RTS_RESULT *pResult)')

/**
 * <description>Get the next variable of the specified variable list</description>
 * <param name="hVarList" type="IN">Handle to the variable list</param>
 * <param name="hPrevVar" type="IN">Handle to the previous variable</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the next variable in the variable list (called hVar)</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecVarAccGetNextVar',`(RTS_HANDLE hVarList, RTS_HANDLE hPrevVar, RTS_RESULT *pResult)')


/**
 * <description>Invalidate variable to disable access</description>
 * <param name="hVarList" type="IN">Handle to the variable list</param>
 * <param name="hVar" type="IN">Handle to the variable</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecVarAccInvalidateVar',`(RTS_HANDLE hVarList, RTS_HANDLE hVar)')

/**
 * <description>Read value of a single specified variable</description>
 * <param name="hVar" type="IN">Handle to the variable</param>
 * <param name="pData" type="IN">Pointer to get the value</param>
 * <param name="ulLen" type="IN">Length of data in bytes to read. 0xFFFFFFFF: Real size of the node is read</param>
 * <param name="pulQuality" type="OUT">Pointer to get quality of the read request</param>
 * <param name="varFlags" type="IN">Variable flags, see category "Varlist flags"for details</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of bytes read</result>
 */
DEF_ITF_API(`RTS_SIZE',`CDECL',`IecVarAccReadVar',`(RTS_HANDLE hVar, void *pData, RTS_SIZE ulLen, RTS_UI32 *pulQuality, int varFlags, RTS_RESULT *pResult)')

/**
 * <description>Write value to a single specified variable</description>
 * <param name="hVar" type="IN">Handle to the variable</param>
 * <param name="pData" type="IN">Pointer to write value</param>
 * <param name="ulLen" type="IN">Number of bytes to write</param>
 * <param name="varFlags" type="IN">Variable flags, see category "Varlist flags"for details</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of bytes written</result>
 */
DEF_ITF_API(`RTS_SIZE',`CDECL',`IecVarAccWriteVar',`(RTS_HANDLE hVar, void *pData, RTS_SIZE ulLen, int varFlags, RTS_RESULT *pResult)')

/**
 * <description>Write value to a single specified variable</description>
 * <param name="hVar" type="IN">Handle to the variable</param>
 * <param name="pData" type="IN">Pointer to write value</param>
 * <param name="ulLen" type="IN">Number of bytes to write</param>
 * <param name="varFlags" type="IN">Variable flags, see category "Varlist flags"for details</param>
 * <param name="ulSessionId" type="IN">Device session ID of the logged in client</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of bytes written</result>
 */
DEF_ITF_API(`RTS_SIZE',`CDECL',`IecVarAccWriteVar2',`(RTS_HANDLE hVar, void *pData, RTS_SIZE ulLen, int varFlags, RTS_UI32 ulSessionId, RTS_RESULT *pResult)')

/* The following routines access directly the symbolic application */

/**
 * <description>Begin the variable configuration. This is used, to enter a new configuration for an optional data server!</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="bBlocking" type="IN">1=if the access to the variable configuration should be blocking for other threads, 0=no blocking</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecVarAccBeginVariableConfiguration',`(RTS_HANDLE hInterface, int bBlocking)')

/**
 * <description>Append a variable to the symbolic interface. This is used, to register a variable at an optional data server!</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the symbolic node</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecVarAccAppendVariable',`(RTS_HANDLE hInterface, RTS_HANDLE hNode)')

/**
 * <description>Append a variable to the symbolic interface. This is used, to register a variable at an optional data server!</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the symbolic node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by IecVarAccGetNode3</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecVarAccAppendVariable3',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation)')

/**
 * <description>Remove a variable from the symbolic interface. This is used, to unregister a variable at an optional data server!</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the symbolic node</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecVarAccRemoveVariable',`(RTS_HANDLE hInterface, RTS_HANDLE hNode)')

/**
 * <description>Remove a variable from the symbolic interface. This is used, to unregister a variable at an optional data server!</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the symbolic node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by IecVarAccGetNode3</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecVarAccRemoveVariable3',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation)')

/**
 * <description>End the variable configuration. This is used, to leave a new configuration for an optional data server!</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecVarAccEndVariableConfiguration',`(RTS_HANDLE hInterface)')


/**
 * <description>Browse routine to go through the complete symbolic tree of an interface. At every node you get a callback in your specified pfBrowseCallback function.</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface or RTS_INVALID_HANDLE to start at the first interface</param>
 * <param name="hNode" type="IN">Handle to the starting node or RTS_INVALID_HANDLE to start at the first node</param>
 * <param name="pVariableInformation" type="IN">Pointer to var info or NULL to start at the first node</param>
 * <param name="pfBrowseCallback" type="IN">Function pointer to register the browse callback function</param>
 * <param name="bIecCallback" type="IN">TRUE=If function pointer is an IEC-function; FALSE=If function pointer is a C-function</param>
 * <param name="pUserParameter" type="IN">User parameter pointer that is retrieved for the callback. Can be NULL.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecVarAccBrowseRecursive',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, PF_IECVARACC_BROWSECALLBACK pfBrowseCallback, RTS_BOOL bIecCallback, void *pUserParameter)')

/**
 * <description>Browse routine to get the symbolic root branch node (e.g. "Application1")</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the root node (called hNode)</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecVarAccBrowseGetRoot',`(RTS_HANDLE hInterface, RTS_RESULT *pResult)')

/**
 * <description>Browse routine to browse down to the child node (e.g. "Application1.GVL")</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the parent node</param>
 * <result>Handle to the child node (called hNode)</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecVarAccBrowseDown',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult)')

/**
 * <description>Browse routine to browse down to the child node (e.g. "Application1.GVL")</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the parent node</param>
 * <param name="pVariableInformation" type="INOUT">Pointer to the variable information3 to get complete browseinfo!
 *
 *	NOTE:
 *	Please initialize this structure with IecVarAccInitVarInfo() the first time calling this function and deinitialize the this structure with IecVarAccExitVarInfo() 
 *	if you finish browsing!
 *
 *	NOTE:
 *	You can use this as VariableInformation2 for any other interface function like IecVarAccGetValue3() etc.! This is compatible. The only thing is you have to do is to cast explicit:
 *	(VariableInformation2 *)pVariableInformation
 *
 * </param>
 * <result>Handle to the child node (called hNode)</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecVarAccBrowseDown2',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, RTS_RESULT *pResult)')

/**
 * <description>Browse routine to browse up to the parent node</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the child node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the parent node (called hNode)</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecVarAccBrowseUp',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult)')

/**
 * <description>Browse routine to browse up to the parent node</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the child node</param>
 * <param name="pVariableInformation" type="INOUT">Pointer to the variable information3 to get complete browseinfo!
 *
 *	NOTE:
 *	You can use this as VariableInformation2 for any other interface function like IecVarAccGetValue3() etc.! This is compatible. The only thing is you have to do is to cast explicit:
 *	(VariableInformation2 *)pVariableInformation
 *
 * </param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the parent node (called hNode)</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecVarAccBrowseUp2',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, RTS_RESULT *pResult)')

/**
 * <description>Browse routine to get the next sibling node</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the predecessor node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the next sibling node (called hNode)</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecVarAccBrowseGetNext',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult)')

/**
 * <description>Browse routine to get the next sibling node</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the predecessor node</param>
 * <param name="pVariableInformation" type="INOUT">Pointer to the variable information3 to get complete browseinfo!
 *
 *	NOTE:
 *	You can use this as VariableInformation2 for any other interface function like IecVarAccGetValue3() etc.! This is compatible. The only thing is you have to do is to cast explicit:
 *	(VariableInformation2 *)pVariableInformation
 *
 * </param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the next sibling node (called hNode)</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecVarAccBrowseGetNext2',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, RTS_RESULT *pResult)')

/**
 * <description>Browse routine to get a child node by index. Can be used instead of IecVarAccBrowseDown/IecVarAccBrowseGetNext.</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the parent node</param>
 * <param name="ulIndex" type="IN">Index of the requested child note node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the requested child node (called hNode)</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecVarAccBrowseGetChildByIndex',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_UI32 ulIndex, RTS_RESULT *pResult)')

/**
 * <description>Get the leaf node handle of a specified variable</description>
 * <param name="pszPath" type="IN">Name of the variable including the complete namespace/path</param>
 * <param name="pulOffset" type="OUT">Offset of the variable to the leaf node (e.g. for structure/FB or array access)</param>
 * <param name="phInterface" type="INOUT">Pointer to specify or to return the symbolic interface handle.
 *		Content must be initialized with RTS_INVALID_HANDLE, if it is not specified!</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the node (called hNode)</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecVarAccGetNode',`(char *pszPath, RTS_SIZE *pulOffset, RTS_HANDLE *phInterface, RTS_RESULT *pResult)')

/**
 * <description>Get the leaf node handle of a specified variable</description>
 * <param name="pszPath" type="IN">Name of the variable including the complete namespace/path</param>
 * <param name="phInterface" type="INOUT">Pointer to specify or to return the symbolic interface handle.
 *		Content must be initialized with RTS_INVALID_HANDLE, if it is not specified!</param>
 * <param name="pVariableInformation" type="OUT">Pointer to the variable information that is retrieved by IecVarAccGetNode3</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the node (called hNode)</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecVarAccGetNode3',`(char *pszPath, RTS_HANDLE *phInterface, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult)')

/**
 * <description>Get the leaf node handle and varinfo (with browseinfo) of the specified variable.
 *	NOTE:
 *	This function addtionally adds the browse info to the VariableInformationStruct3 structure! So this is a time consuming process.
 *	But with this you can use the following functions with this info:
 *	- IecVarAccBrowseDown2
 *	- IecVarAccBrowseGetNext2
 *	- IecVarAccBrowseUp2
 *	- IecVarAccGetNode4
 *	- IecVarAccGetNodeName4
 *	- IecVarAccGetNodeFullPath4
 *
 *	ATTENTION: If you don't need these functions, you should use IecVarAccGetNode3() instead to increase performance!
 * </description>
 * <param name="pszPath" type="IN">Name of the variable including the complete namespace/path</param>
 * <param name="phInterface" type="INOUT">Pointer to specify or to return the symbolic interface handle.
 *		Content must be initialized with RTS_INVALID_HANDLE, if it is not specified!</param>
 * <param name="pVariableInformation" type="INOUT">Pointer to the variable information3.
 *
 *	NOTE:
 *	Please initialize this structure with IecVarAccInitVarInfo() before calling this function and deinitialize the this structure with IecVarAccExitVarInfo() 
 *	if you never access the node!
 *
 *	NOTE:
 *	You can use this as VariableInformation2 for any other interface function like IecVarAccGetValue3() etc.! This is compatible. The only thing is you have to do is to cast explicit:
 *	(VariableInformation2 *)pVariableInformation
 *
 * </param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the node (called hNode)</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecVarAccGetNode4',`(char *pszPath, RTS_HANDLE *phInterface, VariableInformationStruct3 *pVariableInformation, RTS_RESULT *pResult)')

/**
 * <description>Get full namespace/path of the specified node (e.g. "Application1.GVL.A"</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pszPath" type="OUT">Pointer to get full path. Can be NULL to retrieve the lenght of the path.</param>
 * <param name="iMaxPath" type="IN">Max length of pszPath</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of characters copied to pszPath:
 *	<ul>
 *		<li> greater 0: Successful</li>
 *		<li> 0 or -1: Error</li>
 *	</ul>
 * </result>
 */
DEF_ITF_API(`int',`CDECL',`IecVarAccGetNodeFullPath',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, char *pszPath, int iMaxPath, RTS_RESULT *pResult)')

/**
 * <description>Get full namespace/path of the specified node (e.g. "Application1.GVL.A").
 *	NOTE:
 *	This works _not_ in Structures/FBs or Arrays!
 * </description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by IecVarAccGetNode3</param>
 * <param name="pszPath" type="IN">Pointer to get full path</param>
 * <param name="iMaxPath" type="IN">Max length of pszPath</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of characters copied to pszPath (not including NUL termination):
 *	<ul>
 *		<li> greater 0: Successful</li>
 *		<li> 0 or -1: Error</li>
 *	</ul>
 * </result>
 */
DEF_ITF_API(`int',`CDECL',`IecVarAccGetNodeFullPath3',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, char *pszPath, int iMaxPath, RTS_RESULT *pResult)')

/**
 * <description>Get full namespace/path of the specified node (e.g. "Application1.GVL.A").
  *	NOTE:
 *	This works in Structures/FBs or Arrays!
 * </description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by all functions with VariableInformationStruct3 as a parameter!</param>
 * <param name="pszPath" type="IN">Pointer to get full path</param>
 * <param name="iMaxPath" type="IN">Max length of pszPath</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of characters copied to pszPath (not including NUL termination):
 *	<ul>
 *		<li> greater 0: Successful</li>
 *		<li> 0 or -1: Error</li>
 *	</ul>
 * </result>
 */
DEF_ITF_API(`int',`CDECL',`IecVarAccGetNodeFullPath4',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, char *pszPath, int iMaxPath, RTS_RESULT *pResult)')

/**
 * <description>Get name of the specified node (e.g. "A")</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to node name</result>
 */
DEF_ITF_API(`char*',`CDECL',`IecVarAccGetNodeName',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult)')

/**
 * <description>Get name of the specified node (e.g. "A")</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by IecVarAccGetNode3</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to node name</result>
 */
DEF_ITF_API(`char*',`CDECL',`IecVarAccGetNodeName3',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult)')

/**
 * <description>Get name of the specified node (e.g. "A")</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information3 that is retrieved by all functions with VariableInformationStruct3 as a parameter!</param>
 * <param name="pszNodeName" type="IN">Pointer to get nodename</param>
 * <param name="nNodeNameLen" type="IN">Max nodename length</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecVarAccGetNodeName4',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, char *pszNodeName, RTS_UI32 nNodeNameLen)')

/**
 * <description>Get access rights of the specified symbolic node</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Access rights</result>
 */
DEF_ITF_API(`AccessRights',`CDECL',`IecVarAccGetAccessRights',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult)')

/**
 * <description>Get address of the variable value
 * WARNINGS:
 *	- Use this function only for diagnostic usages!
 *	- Don't use it to read/write values of a symbol!!! This can lead to unpredictable effects and can damage
 *	  your system!
 * </description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to address of the variable value</result>
 */
DEF_ITF_API(`void*',`CDECL',`IecVarAccGetAddress',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult)')

/**
 * <description>Get address of the variable value (including the offset, e.g. for array elements)</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="ulOffset" type="IN">Offset of the node, that is retrieved by IecVarAccGetNode</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to address of the variable value</result>
 */
DEF_ITF_API(`void*',`CDECL',`IecVarAccGetAddress2',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_SIZE ulOffset, RTS_RESULT *pResult)')

/**
 * <description>Get address of the variable value (including the offset, e.g. for array elements)</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by IecVarAccGetNode3</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to address of the variable value</result>
 */
DEF_ITF_API(`void*',`CDECL',`IecVarAccGetAddress3',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult)')

/**
 * <description>Get node type of the specified node (leaf or branch node)</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Node type</result>
 */
DEF_ITF_API(`TreeNodeType',`CDECL',`IecVarAccGetNodeType',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult)')

/**
 * <description>Get the value size in bytes of the specified node. If it is an array, it returns the complete size
 *	of the array (e.g. "C[5]": Returns 15 if it is a byte array with 15 elements)</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Size in bytes of the value</result>
 */
DEF_ITF_API(`RTS_SIZE',`CDECL',`IecVarAccGetSize',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult)')

/**
 * <description>Get the value size in bytes of the specified node. It returns always the real size of the node value
 *	(e.g. "C[5]": Returns 1 if it is a byte array)</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="ulOffset" type="IN">Offset of the node (is retrieved by IecVarAccGetNode)</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Size in bytes of the value</result>
 */
DEF_ITF_API(`RTS_SIZE',`CDECL',`IecVarAccGetSize2',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_SIZE ulOffset, RTS_RESULT *pResult)')

/**
 * <description>Get the value size in bytes of the specified node. It returns always the real size of the node value
 *	(e.g. "C[5]": Returns 1 if it is a byte array)</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by IecVarAccGetNode3</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Size in bytes of the value of the specified node</result>
 */
DEF_ITF_API(`RTS_SIZE',`CDECL',`IecVarAccGetSize3',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult)')

/**
 * <description>Get the swap size of the specified node (can be used to change the byte order)</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Swap size:	8/4/2/1</result>
 */
DEF_ITF_API(`RTS_SIZE',`CDECL',`IecVarAccGetSwapSize',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult)')

/**
 * <description>Get the type class of the specified node</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Type class</result>
 */
DEF_ITF_API(`TypeClass3',`CDECL',`IecVarAccGetTypeClass',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult)')

/**
 * <description>Get the type class of the specified node</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by IecVarAccGetNode3</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Type class</result>
 */
DEF_ITF_API(`TypeClass3',`CDECL',`IecVarAccGetTypeClass3',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult)')

/**
 * <description>Read the value of the specified node</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pDest" type="OUT">Pointer to destination buffer to read the value</param>
 * <param name="ulOffset" type="IN">Offset of the node (is retrieved by IecVarAccGetNode)</param>
 * <param name="ulSize" type="IN">Number of bytes to read</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of byte read</result>
 */
DEF_ITF_API(`RTS_SIZE',`CDECL',`IecVarAccGetValue',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, void *pDest, RTS_SIZE ulOffset, RTS_SIZE ulSize, RTS_RESULT *pResult)')

/**
 * <description>Read the value of the specified node</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by IecVarAccGetNode3</param>
 * <param name="pDest" type="OUT">Pointer to destination buffer to read the value</param>
 * <param name="ulSize" type="IN">Number of bytes to read</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of byte read</result>
 */
DEF_ITF_API(`RTS_SIZE',`CDECL',`IecVarAccGetValue3',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, void *pDest, RTS_SIZE ulSize, RTS_RESULT *pResult)')

/**
 * <description>Write a value to the specified node</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pSrc" type="IN">Pointer to source buffer of value to write</param>
 * <param name="ulOffset" type="IN">Offset of the node (is retrieved by IecVarAccGetNode)</param>
 * <param name="ulSize" type="IN">Number of bytes to write</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of byte written</result>
 */
DEF_ITF_API(`RTS_SIZE',`CDECL',`IecVarAccSetValue',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, void *pSrc, RTS_SIZE ulOffset, RTS_SIZE ulSize, RTS_RESULT *pResult)')

/**
 * <description>Write a value to the specified node</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by IecVarAccGetNode3</param>
 * <param name="pSrc" type="IN">Pointer to source buffer of value to write</param>
 * <param name="ulSize" type="IN">Number of bytes to write</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of byte written</result>
 */
DEF_ITF_API(`RTS_SIZE',`CDECL',`IecVarAccSetValue3',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, void *pSrc, RTS_SIZE ulSize, RTS_RESULT *pResult)')

/**
 * <description>Swap the byte order of specified node and the specified data buffer</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pData" type="IN">Pointer to data buffer to swap</param>
 * <param name="ulSize" type="IN">Number of bytes to swap</param>
 * <param name="bMotorola" type="IN">1=Motorola format (big endian), 0=Intel format (little endian)</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of bytes swapped</result>
 */
DEF_ITF_API(`RTS_SIZE',`CDECL',`IecVarAccSwap',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, void *pData, RTS_SIZE ulSize, int bMotorola, RTS_RESULT *pResult)')

/**
 * <description>Swap the byte order of specified node and the specified data buffer</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pData" type="IN">Pointer to data buffer to swap</param>
 * <param name="ulSize" type="IN">Number of bytes to swap</param>
 * <param name="bMotorola" type="IN">1=Motorola format (big endian), 0=Intel format (little endian)</param>
 * <param name="ulOffset" type="IN">Offset of the node (is retrieved by IecVarAccGetNode)</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of bytes swapped</result>
 */
DEF_ITF_API(`RTS_SIZE',`CDECL',`IecVarAccSwap2',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, void *pData, RTS_SIZE ulSize, int bMotorola, RTS_SIZE ulOffset, RTS_RESULT *pResult)')

/**
 * <description>Swap the byte order of specified node and the specified data buffer</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by IecVarAccGetNode3</param>
 * <param name="pData" type="IN">Pointer to data buffer to swap</param>
 * <param name="ulSize" type="IN">Number of bytes to swap</param>
 * <param name="bMotorola" type="IN">1=Motorola format (big endian), 0=Intel format (little endian)</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of bytes swapped</result>
 */
DEF_ITF_API(`RTS_SIZE',`CDECL',`IecVarAccSwap3',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, void *pData, RTS_SIZE ulSize, int bMotorola, RTS_RESULT *pResult)')

/**
 * <description>Get the type node of the specified symbolic node. For arays, only the array type is retrieved!</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the type node (called hTypeNode)</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecVarAccGetTypeNode',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult)')

/**
 * <description>Get the type node of the specified symbolic node (worked for all types of node!)</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="ulOffset" type="IN">Offset of the node (is retrieved by IecVarAccGetNode)</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the type node (called hTypeNode)</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecVarAccGetTypeNode2',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_SIZE ulOffset, RTS_RESULT *pResult)')

/**
 * <description>Get the type node of the specified symbolic node (worked for all types of node!)</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by IecVarAccGetNode3</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the type node (called hTypeNode)</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecVarAccGetTypeNode3',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult)')

/**
 * <description>Get the type description as a C-structure from the specified type node</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hTypeNode" type="IN">Handle to the type node (is retrieved by IecVarAccGetTypeNode or IecVarAccGetTypeNode2)</param>
 * <param name="pTypeDesc" type="OUT">Pointer to get type description as a C-structure.
 *	NOTE:
 *	You can call this function the first time by setting all members of pTypeDesc to 0. Then you get for user defined types (structures or functionblocks)
 *	the number of the member variables. This is retreived in pTypeDesc-&amp;gt;_union._struct._Components. Then you can allocate an array with the number of member elements
 *	and can call IecVarAccGetTypeDesc() a second time.
 *	Example:
 *		TypeDescAsUnion typeDesc;
 *		memset(&amp;typeDesc, 0, sizeof(typeDesc));
 *		IecVarAccGetTypeDesc(hInterface, hTypeNode, &amp;typeDesc);
 *		if (typeDesc._typeClass == TYPE3_USERDEF &amp;&amp; typeDesc._union._struct._iComponents &amp;gt; 0)
 *		{
 *			typeDesc._union._struct._Components = (IBaseTreeNode **)CAL_SysMemAllocData(COMPONENT_NAME, typeDesc._union._struct._iComponents * sizeof(IBaseTreeNode*), NULL);
 *			IecVarAccGetTypeDesc(hInterface, hTypeNode, &amp;typeDesc);
 *			...
 *			CAL_SysMemFreeData(COMPONENT_NAME, typeDesc._union._struct._Components);
 *		}
 *	
 * </param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecVarAccGetTypeDesc',`(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, TypeDescAsUnion *pTypeDesc)')

/**
 * <description>Get the address information of a variable, (if available). This is for all data with direct addresses (%M, %Q or %I)</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by IecVarAccGetNode3</param>
 * <param name="pszAdressInfo" type="OUT">Pointer to the string to get the address info.
 *	NOTE:
 *		 - All address infos are calclulated out of its physical addresses! So the offset is correct but must not be identical to the
 *			declared address as in CoDeSys!
 *			Examples:
 *				o w AT "%IB2" : WORD	==> "%IW1"
 *				o b AT "%IW4" : BYTE	==> "%IB8" 
 *		- Target setting "memory-layout\byte-addressing" is recognized in the address!
 *			Example:
 *				o w AT "%IB4" : WORD	==> "%IW4"
 *		- Target setting "memory-layout\bit-word-addressing" is recognized in the address!
 *			Example:
 *				o x AT "%IX1.13" : BOOL	==> "%IX1.13"
 * </param>
 * <param name="pnAddressInfoLen" type="INOUT">Pointer to the max length of the address info string. The real length is returned</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecVarAccGetAddressInfo',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, char *pszAdressInfo, int *pnAddressInfoLen)')


/*#### OPC UA interfaces ####*/

/**
 * <description>Get the number of defined data types.
 *	NOTE:
 *	Only supported if OPC UA support is activated in the symbolconfiguration in CODESYS!</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of defined data types</result>
 */
DEF_ITF_API(`RTS_I32',`CDECL',`IecVarAccGetNumOfTypes',`(RTS_HANDLE hInterface, RTS_RESULT *pResult)')

/**
 * <description>Get the type node handle specified by type index.
 *	NOTE:
 *	Only supported if OPC UA support is activated in the symbolconfiguration in CODESYS!
 * </description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="nIndex" type="IN">Type index</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the type node (called hTypeNode)</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecVarAccGetTypeNodeByIndex',`(RTS_HANDLE hInterface, RTS_I32 nIndex, RTS_RESULT *pResult)')

/**
 * <description>Get the type name, if it is a userdefined type (structure or function block).
 *	NOTE:
 *	Only supported if OPC UA support is activated in the symbolconfiguration in CODESYS!
 * </description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hTypeNode" type="IN">Handle to the type node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to type name</result>
 */
DEF_ITF_API(`char*',`CDECL',`IecVarAccGetTypeName',`(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_RESULT *pResult)')

/**
 * <description>Get the type class of the specified type!
 *	NOTE:
 *	In the HiWord of the TypeClass, the POU types are encoded (see POUTypeClass).
 * </description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hTypeNode" type="IN">Handle to the type node</param>
 * <param name="dwFlags" type="IN">Flags to control the result of the TypeClass. See TypeClassFlags for details.</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>TypeClass3</result>
 */
DEF_ITF_API(`TypeClass3',`CDECL',`IecVarAccGetTypeClassFromType',`(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_IEC_DWORD dwFlags, RTS_RESULT *pResult)')

/**
 * <description>Get the POU class of the specified type</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hTypeNode" type="IN">Handle to the type node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>POUClass</result>
 */
DEF_ITF_API(`POUClass',`CDECL',`IecVarAccGetPOUClass',`(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_RESULT *pResult)')

/**
 * <description>Get the node flags of a specified node. Is typically used in memmer node of a struct/functionblock etc. to get the storage class info (VAR_INPUT, VAR_OUTPUT, etc.)</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>NodeFlags. See NodeFlags for details</result>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`IecVarAccGetNodeFlags',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult)')

/**
 * <description>Get the number of attributes defined at this symbolic node.
 *	NOTE:
 *	An attribute is defined at the declaration part in CODESYS, e.g.:
 *		{attribute 'symbol' := 'readwrite'}
 *	This can be accessed here the following way, e.g.:
 *		"symbol := readwrite"

 * </description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of specified attributes at this symblic node</result>
 */
DEF_ITF_API(`RTS_UI16',`CDECL',`IecVarAccGetNumOfAttributes',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult)')

/**
 * <description>Get access to the defined attributes at this symbolic node.
 *	NOTE:
 *	An attribute is defined at the declaration part in CODESYS, e.g.:
 *		{attribute 'symbol' := 'readwrite'}
 *	This can be accessed here the following way, e.g.:
 *		"symbol := readwrite"
 * </description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="ui16Index" type="IN">Index of the attribute</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the attribute specified by index</result>
 */
DEF_ITF_API(`char*',`CDECL',`IecVarAccGetAttributeByIndex',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_UI16 ui16Index, RTS_RESULT *pResult)')

/**
 * <description>Get the enum values of an IEC Enum type</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hTypeNode" type="IN">Handle to the type node (is retrieved by IecVarAccGetTypeNode or IecVarAccGetTypeNode2)</param>
 * <param name="pui16NumOfEnums" type="OUT">Pointer to the number of enum values in the returned array</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the array of enum values or NULL if it is not supported or this is no enum type</result>
 */
DEF_ITF_API(`EnumValues*',`CDECL',`IecVarAccGetEnumValues',`(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_I16 *pi16NumOfEnums, RTS_RESULT *pResult)')

/**
 * <description>Get the base type of a derived FB or structure</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hTypeNode" type="IN">Handle to the type node (is retrieved by IecVarAccGetTypeNode or IecVarAccGetTypeNode2)</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Derive information available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter (one of the handles invalid)</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No derive information available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">IecVarAccess interface in IEC code not available</errorcode>
 * <result>Return a handle to the base type or RTS_INVALID_HANDLE if no base type is available</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IecVarAccGetDerivedBaseType',`(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_RESULT *pResult)')

/**
 * <description>Check if the FB or structure is derived from a base type</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hTypeNode" type="IN">Handle to the type node (is retrieved by IecVarAccGetTypeNode or IecVarAccGetTypeNode2)</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Derive information available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter (one of the handles invalid)</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">IecVarAccess interface in IEC code not available</errorcode>
 * <result>TRUE if it is a derived type or FALSE if not</result>
 */
DEF_ITF_API(`RTS_BOOL',`CDECL',`IecVarAccIsDerivedType',`(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_RESULT *pResult)')

/**
 * <description>Return the client offset of a variable. This can be different to the physical IEC memory offset!</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Client offset available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter (one of the handles invalid)</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">IecVarAccess interface in IEC code not available</errorcode>
 * <result>Return the client offset of the node</result>
 */
DEF_ITF_API(`RTS_SIZE',`CDECL',`IecVarAccGetClientOffset',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult)')

/**
 * <description>
 *	Return the namespace node flags of a specified node. See "NAMESPACENODEFLAGS_" definitions in IecVarAccess_ItfsItf.h.
 *	NOTE:
 *	Please use the appropriate macros defined in "NamespaceNodeFlags macros" in IecVarAccess_ItfsItf.h to separate Application, GVL, Program, Variable or
 *	ExplicitNamespace nodes (e.g. IsApplicationNode(namespaceNodeFlags) to check if it is an application node).
 * </description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Namespace node flags available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter (one of the handles invalid)</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">IecVarAccess interface in IEC code not available</errorcode>
 * <result>Return the namespace node flags. Please use the appropriate macros defined in "NamespaceNodeFlags macros" in IecVarAccess_ItfsItf.h to separate Application, GVL, Program, Variable or
 *	ExplicitNamespace nodes</result>
 */
DEF_ITF_API(`NAMESPACENODEFLAGS',`CDECL',`IecVarAccGetNamespaceNodeFlags',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult)')

/**
 * <description>Return the native size of a node. This is the physical memory size in IEC!
 *	WARNINGS:
 *	- Use this function only for diagnostic usages!
 *	- Don't use it to read/write values via address of a symbol!!! This can lead to unpredictable effects and can damage
 *	  your system!
 * </description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the symbolic node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by IecVarAccGetNode3</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Namespace node flags available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter (one of the handles is invalid)</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">IecVarAccess interface in IEC code not available</errorcode>
 * <result>Native/IEC size in bytes of a symbolic node</result>
 */
DEF_ITF_API(`RTS_SIZE',`CDECL',`IecVarAccGetNativeSize',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult)')

/**
 * <description>Get the attributes of single enum values.
 * Attention: The pAttributes member of the EnumAttributes return value is basically not a char*** but a char**
 * Use a construct like this to get the attributes: EnumAttributes[i].pAttributes[j] 
 * </description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hTypeNode" type="IN">Handle to the symbolic type node</param>
 * <param name="pnNumOfEnumValues" type="OUT">Number of elements in the returned array.</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Attributes of enum values are available.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter (one of the handles is invalid)</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">IecVarAccess interface in IEC code not available</errorcode>
 * <result>Pointer to an array of attributes of enum values.</result>
 */
DEF_ITF_API(`EnumAttributes*',`CDECL',`IecVarAccGetEnumMemberAttributeList',`(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_I16* pnNumOfEnumValues, RTS_RESULT* pResult)')

/**
 * <description>Get the number of available attributes of a type node</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hTypeNode" type="IN">Handle to the symbolic type node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Attributes of enum values are available.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter (one of the handles is invalid)</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">IecVarAccess interface in IEC code not available</errorcode>
 * <result>Number of available attributes</result>
 */
DEF_ITF_API(`RTS_UI16',`CDECL',`IecVarAccGetNumOfTypeAttributes',`(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_RESULT* pResult)')

/**
 * <description>Get a specific attribute a type node</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hTypeNode" type="IN">Handle to the symbolic type node</param>
 * <param name="wIndex" type="IN">Index of the attribute to get. Use IecVarAccGetNumOfTypeAttributes to get the maximum index.</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Attributes of enum values are available.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter (one of the handles is invalid)</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">IecVarAccess interface in IEC code not available</errorcode>
 * <result>Content of attributes</result>
 */
DEF_ITF_API(`char*',`CDECL',`IecVarAccGetTypeAttributeByIndex',`(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_UI16 wIndex, RTS_RESULT* pResult)')

/**
 * <description>Get the upper and lower bounds of a subrange type.</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hTypeNode" type="IN">Handle to the symbolic type node</param>
 * <param name="pLower" type="OUT">Pointer where to store the minimum accepted value.</param>
 * <param name="pUpper" type="OUT">Pointer where to store the maximum accepted value.</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Attributes of enum values are available.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter (one of the handles is invalid)</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">IecVarAccess interface in IEC code not available</errorcode>
 * <result>Content of attributes</result>
 */
DEF_ITF_API(`RTS_BOOL',`CDECL',`IecVarAccGetRange',`(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_UI64* pLower, RTS_UI64* pUpper, RTS_RESULT* pResult)')

/**
 * <description>Gets the content feature flags.</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="pContentFeatureFlags" type="OUT">Pointer to the destination variable. May be 0 to just query whether the flags are set or not.</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">if pContentFeatureFlags is not 0, it will be set to the feature flags.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The code generator did not set the flag value.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">IecVarAccess interface in IEC code not available</errorcode>
 * <result>Content of attributes</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecVarAccGetContentFeatureFlags',`(RTS_HANDLE hInterface, CONTENTFEATUREFLAGS* pContentFeatureFlags)')

/**
 * <description>Call a callable node. This can be a Program, FB, method or function.</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by IecVarAccGetNode3 or IecVarAccGetNode4</param>
 * <param name="pArgumentBuffer" type="IN">Pointer to the parameter structuer of the object to call.</param>
 * <param name="nArgumentBufferSize" type="IN">Size of the parameter structure</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was successful.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">One of the parameters was invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">Symbolconfiguration not initialized</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Internal error.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">IecVarAccess interface in IEC code not available</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IecVarAccExecuteCall',`(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_UI8 *pArgumentBuffer, RTS_SIZE nArgumentBufferSize)')

#ifdef __cplusplus
}
#endif
