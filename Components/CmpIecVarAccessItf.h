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


	
	
#ifndef _CMPIECVARACCESSITF_H_
#define _CMPIECVARACCESSITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "SysInternalLibItf.h"
#include "SysTimeItf.h"
#include "SysTimeRtcItf.h"
#include "CmpSrvItf.h"
#include "IecVarAccess_ItfsItf.h"

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
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

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

void CDECL CDECL_EXT iecvaraccbrowsedown2(iecvaraccbrowsedown2_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCBROWSEDOWN2_IEC) (iecvaraccbrowsedown2_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCBROWSEDOWN2_NOTIMPLEMENTED)
	#define USE_iecvaraccbrowsedown2
	#define EXT_iecvaraccbrowsedown2
	#define GET_iecvaraccbrowsedown2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccbrowsedown2(p0) 
	#define CHK_iecvaraccbrowsedown2  FALSE
	#define EXP_iecvaraccbrowsedown2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccbrowsedown2
	#define EXT_iecvaraccbrowsedown2
	#define GET_iecvaraccbrowsedown2(fl)  CAL_CMGETAPI( "iecvaraccbrowsedown2" ) 
	#define CAL_iecvaraccbrowsedown2  iecvaraccbrowsedown2
	#define CHK_iecvaraccbrowsedown2  TRUE
	#define EXP_iecvaraccbrowsedown2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccbrowsedown2", (RTS_UINTPTR)iecvaraccbrowsedown2, 1, 0, 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccbrowsedown2
	#define EXT_iecvaraccbrowsedown2
	#define GET_iecvaraccbrowsedown2(fl)  CAL_CMGETAPI( "iecvaraccbrowsedown2" ) 
	#define CAL_iecvaraccbrowsedown2  iecvaraccbrowsedown2
	#define CHK_iecvaraccbrowsedown2  TRUE
	#define EXP_iecvaraccbrowsedown2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccbrowsedown2", (RTS_UINTPTR)iecvaraccbrowsedown2, 1, 0, 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccbrowsedown2
	#define EXT_CmpIecVarAccessiecvaraccbrowsedown2
	#define GET_CmpIecVarAccessiecvaraccbrowsedown2  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccbrowsedown2  iecvaraccbrowsedown2
	#define CHK_CmpIecVarAccessiecvaraccbrowsedown2  TRUE
	#define EXP_CmpIecVarAccessiecvaraccbrowsedown2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccbrowsedown2", (RTS_UINTPTR)iecvaraccbrowsedown2, 1, 0, 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccbrowsedown2
	#define EXT_iecvaraccbrowsedown2
	#define GET_iecvaraccbrowsedown2(fl)  CAL_CMGETAPI( "iecvaraccbrowsedown2" ) 
	#define CAL_iecvaraccbrowsedown2  iecvaraccbrowsedown2
	#define CHK_iecvaraccbrowsedown2  TRUE
	#define EXP_iecvaraccbrowsedown2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccbrowsedown2", (RTS_UINTPTR)iecvaraccbrowsedown2, 1, 0, 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccbrowsedown2  PFIECVARACCBROWSEDOWN2_IEC pfiecvaraccbrowsedown2;
	#define EXT_iecvaraccbrowsedown2  extern PFIECVARACCBROWSEDOWN2_IEC pfiecvaraccbrowsedown2;
	#define GET_iecvaraccbrowsedown2(fl)  s_pfCMGetAPI2( "iecvaraccbrowsedown2", (RTS_VOID_FCTPTR *)&pfiecvaraccbrowsedown2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0x03050A00)
	#define CAL_iecvaraccbrowsedown2  pfiecvaraccbrowsedown2
	#define CHK_iecvaraccbrowsedown2  (pfiecvaraccbrowsedown2 != NULL)
	#define EXP_iecvaraccbrowsedown2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccbrowsedown2", (RTS_UINTPTR)iecvaraccbrowsedown2, 1, 0, 0x03050A00) 
#endif


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

void CDECL CDECL_EXT iecvaraccbrowsegetnext2(iecvaraccbrowsegetnext2_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCBROWSEGETNEXT2_IEC) (iecvaraccbrowsegetnext2_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCBROWSEGETNEXT2_NOTIMPLEMENTED)
	#define USE_iecvaraccbrowsegetnext2
	#define EXT_iecvaraccbrowsegetnext2
	#define GET_iecvaraccbrowsegetnext2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccbrowsegetnext2(p0) 
	#define CHK_iecvaraccbrowsegetnext2  FALSE
	#define EXP_iecvaraccbrowsegetnext2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccbrowsegetnext2
	#define EXT_iecvaraccbrowsegetnext2
	#define GET_iecvaraccbrowsegetnext2(fl)  CAL_CMGETAPI( "iecvaraccbrowsegetnext2" ) 
	#define CAL_iecvaraccbrowsegetnext2  iecvaraccbrowsegetnext2
	#define CHK_iecvaraccbrowsegetnext2  TRUE
	#define EXP_iecvaraccbrowsegetnext2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccbrowsegetnext2", (RTS_UINTPTR)iecvaraccbrowsegetnext2, 1, 0, 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccbrowsegetnext2
	#define EXT_iecvaraccbrowsegetnext2
	#define GET_iecvaraccbrowsegetnext2(fl)  CAL_CMGETAPI( "iecvaraccbrowsegetnext2" ) 
	#define CAL_iecvaraccbrowsegetnext2  iecvaraccbrowsegetnext2
	#define CHK_iecvaraccbrowsegetnext2  TRUE
	#define EXP_iecvaraccbrowsegetnext2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccbrowsegetnext2", (RTS_UINTPTR)iecvaraccbrowsegetnext2, 1, 0, 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccbrowsegetnext2
	#define EXT_CmpIecVarAccessiecvaraccbrowsegetnext2
	#define GET_CmpIecVarAccessiecvaraccbrowsegetnext2  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccbrowsegetnext2  iecvaraccbrowsegetnext2
	#define CHK_CmpIecVarAccessiecvaraccbrowsegetnext2  TRUE
	#define EXP_CmpIecVarAccessiecvaraccbrowsegetnext2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccbrowsegetnext2", (RTS_UINTPTR)iecvaraccbrowsegetnext2, 1, 0, 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccbrowsegetnext2
	#define EXT_iecvaraccbrowsegetnext2
	#define GET_iecvaraccbrowsegetnext2(fl)  CAL_CMGETAPI( "iecvaraccbrowsegetnext2" ) 
	#define CAL_iecvaraccbrowsegetnext2  iecvaraccbrowsegetnext2
	#define CHK_iecvaraccbrowsegetnext2  TRUE
	#define EXP_iecvaraccbrowsegetnext2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccbrowsegetnext2", (RTS_UINTPTR)iecvaraccbrowsegetnext2, 1, 0, 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccbrowsegetnext2  PFIECVARACCBROWSEGETNEXT2_IEC pfiecvaraccbrowsegetnext2;
	#define EXT_iecvaraccbrowsegetnext2  extern PFIECVARACCBROWSEGETNEXT2_IEC pfiecvaraccbrowsegetnext2;
	#define GET_iecvaraccbrowsegetnext2(fl)  s_pfCMGetAPI2( "iecvaraccbrowsegetnext2", (RTS_VOID_FCTPTR *)&pfiecvaraccbrowsegetnext2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0x03050A00)
	#define CAL_iecvaraccbrowsegetnext2  pfiecvaraccbrowsegetnext2
	#define CHK_iecvaraccbrowsegetnext2  (pfiecvaraccbrowsegetnext2 != NULL)
	#define EXP_iecvaraccbrowsegetnext2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccbrowsegetnext2", (RTS_UINTPTR)iecvaraccbrowsegetnext2, 1, 0, 0x03050A00) 
#endif


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

void CDECL CDECL_EXT iecvaraccbrowserecursive(iecvaraccbrowserecursive_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCBROWSERECURSIVE_IEC) (iecvaraccbrowserecursive_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCBROWSERECURSIVE_NOTIMPLEMENTED)
	#define USE_iecvaraccbrowserecursive
	#define EXT_iecvaraccbrowserecursive
	#define GET_iecvaraccbrowserecursive(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccbrowserecursive(p0) 
	#define CHK_iecvaraccbrowserecursive  FALSE
	#define EXP_iecvaraccbrowserecursive  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccbrowserecursive
	#define EXT_iecvaraccbrowserecursive
	#define GET_iecvaraccbrowserecursive(fl)  CAL_CMGETAPI( "iecvaraccbrowserecursive" ) 
	#define CAL_iecvaraccbrowserecursive  iecvaraccbrowserecursive
	#define CHK_iecvaraccbrowserecursive  TRUE
	#define EXP_iecvaraccbrowserecursive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccbrowserecursive", (RTS_UINTPTR)iecvaraccbrowserecursive, 1, 0, 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccbrowserecursive
	#define EXT_iecvaraccbrowserecursive
	#define GET_iecvaraccbrowserecursive(fl)  CAL_CMGETAPI( "iecvaraccbrowserecursive" ) 
	#define CAL_iecvaraccbrowserecursive  iecvaraccbrowserecursive
	#define CHK_iecvaraccbrowserecursive  TRUE
	#define EXP_iecvaraccbrowserecursive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccbrowserecursive", (RTS_UINTPTR)iecvaraccbrowserecursive, 1, 0, 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccbrowserecursive
	#define EXT_CmpIecVarAccessiecvaraccbrowserecursive
	#define GET_CmpIecVarAccessiecvaraccbrowserecursive  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccbrowserecursive  iecvaraccbrowserecursive
	#define CHK_CmpIecVarAccessiecvaraccbrowserecursive  TRUE
	#define EXP_CmpIecVarAccessiecvaraccbrowserecursive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccbrowserecursive", (RTS_UINTPTR)iecvaraccbrowserecursive, 1, 0, 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccbrowserecursive
	#define EXT_iecvaraccbrowserecursive
	#define GET_iecvaraccbrowserecursive(fl)  CAL_CMGETAPI( "iecvaraccbrowserecursive" ) 
	#define CAL_iecvaraccbrowserecursive  iecvaraccbrowserecursive
	#define CHK_iecvaraccbrowserecursive  TRUE
	#define EXP_iecvaraccbrowserecursive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccbrowserecursive", (RTS_UINTPTR)iecvaraccbrowserecursive, 1, 0, 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccbrowserecursive  PFIECVARACCBROWSERECURSIVE_IEC pfiecvaraccbrowserecursive;
	#define EXT_iecvaraccbrowserecursive  extern PFIECVARACCBROWSERECURSIVE_IEC pfiecvaraccbrowserecursive;
	#define GET_iecvaraccbrowserecursive(fl)  s_pfCMGetAPI2( "iecvaraccbrowserecursive", (RTS_VOID_FCTPTR *)&pfiecvaraccbrowserecursive, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0x03050A00)
	#define CAL_iecvaraccbrowserecursive  pfiecvaraccbrowserecursive
	#define CHK_iecvaraccbrowserecursive  (pfiecvaraccbrowserecursive != NULL)
	#define EXP_iecvaraccbrowserecursive   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccbrowserecursive", (RTS_UINTPTR)iecvaraccbrowserecursive, 1, 0, 0x03050A00) 
#endif


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

void CDECL CDECL_EXT iecvaraccbrowseup2(iecvaraccbrowseup2_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCBROWSEUP2_IEC) (iecvaraccbrowseup2_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCBROWSEUP2_NOTIMPLEMENTED)
	#define USE_iecvaraccbrowseup2
	#define EXT_iecvaraccbrowseup2
	#define GET_iecvaraccbrowseup2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccbrowseup2(p0) 
	#define CHK_iecvaraccbrowseup2  FALSE
	#define EXP_iecvaraccbrowseup2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccbrowseup2
	#define EXT_iecvaraccbrowseup2
	#define GET_iecvaraccbrowseup2(fl)  CAL_CMGETAPI( "iecvaraccbrowseup2" ) 
	#define CAL_iecvaraccbrowseup2  iecvaraccbrowseup2
	#define CHK_iecvaraccbrowseup2  TRUE
	#define EXP_iecvaraccbrowseup2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccbrowseup2", (RTS_UINTPTR)iecvaraccbrowseup2, 1, 0, 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccbrowseup2
	#define EXT_iecvaraccbrowseup2
	#define GET_iecvaraccbrowseup2(fl)  CAL_CMGETAPI( "iecvaraccbrowseup2" ) 
	#define CAL_iecvaraccbrowseup2  iecvaraccbrowseup2
	#define CHK_iecvaraccbrowseup2  TRUE
	#define EXP_iecvaraccbrowseup2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccbrowseup2", (RTS_UINTPTR)iecvaraccbrowseup2, 1, 0, 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccbrowseup2
	#define EXT_CmpIecVarAccessiecvaraccbrowseup2
	#define GET_CmpIecVarAccessiecvaraccbrowseup2  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccbrowseup2  iecvaraccbrowseup2
	#define CHK_CmpIecVarAccessiecvaraccbrowseup2  TRUE
	#define EXP_CmpIecVarAccessiecvaraccbrowseup2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccbrowseup2", (RTS_UINTPTR)iecvaraccbrowseup2, 1, 0, 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccbrowseup2
	#define EXT_iecvaraccbrowseup2
	#define GET_iecvaraccbrowseup2(fl)  CAL_CMGETAPI( "iecvaraccbrowseup2" ) 
	#define CAL_iecvaraccbrowseup2  iecvaraccbrowseup2
	#define CHK_iecvaraccbrowseup2  TRUE
	#define EXP_iecvaraccbrowseup2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccbrowseup2", (RTS_UINTPTR)iecvaraccbrowseup2, 1, 0, 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccbrowseup2  PFIECVARACCBROWSEUP2_IEC pfiecvaraccbrowseup2;
	#define EXT_iecvaraccbrowseup2  extern PFIECVARACCBROWSEUP2_IEC pfiecvaraccbrowseup2;
	#define GET_iecvaraccbrowseup2(fl)  s_pfCMGetAPI2( "iecvaraccbrowseup2", (RTS_VOID_FCTPTR *)&pfiecvaraccbrowseup2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0x03050A00)
	#define CAL_iecvaraccbrowseup2  pfiecvaraccbrowseup2
	#define CHK_iecvaraccbrowseup2  (pfiecvaraccbrowseup2 != NULL)
	#define EXP_iecvaraccbrowseup2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccbrowseup2", (RTS_UINTPTR)iecvaraccbrowseup2, 1, 0, 0x03050A00) 
#endif


/**
 * <description>iecvaraccexitvarinfo</description>
 */
typedef struct tagiecvaraccexitvarinfo_struct
{
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT IecVarAccExitVarInfo;	/* VAR_OUTPUT */	
} iecvaraccexitvarinfo_struct;

void CDECL CDECL_EXT iecvaraccexitvarinfo(iecvaraccexitvarinfo_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCEXITVARINFO_IEC) (iecvaraccexitvarinfo_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCEXITVARINFO_NOTIMPLEMENTED)
	#define USE_iecvaraccexitvarinfo
	#define EXT_iecvaraccexitvarinfo
	#define GET_iecvaraccexitvarinfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccexitvarinfo(p0) 
	#define CHK_iecvaraccexitvarinfo  FALSE
	#define EXP_iecvaraccexitvarinfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccexitvarinfo
	#define EXT_iecvaraccexitvarinfo
	#define GET_iecvaraccexitvarinfo(fl)  CAL_CMGETAPI( "iecvaraccexitvarinfo" ) 
	#define CAL_iecvaraccexitvarinfo  iecvaraccexitvarinfo
	#define CHK_iecvaraccexitvarinfo  TRUE
	#define EXP_iecvaraccexitvarinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccexitvarinfo", (RTS_UINTPTR)iecvaraccexitvarinfo, 1, 0, 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccexitvarinfo
	#define EXT_iecvaraccexitvarinfo
	#define GET_iecvaraccexitvarinfo(fl)  CAL_CMGETAPI( "iecvaraccexitvarinfo" ) 
	#define CAL_iecvaraccexitvarinfo  iecvaraccexitvarinfo
	#define CHK_iecvaraccexitvarinfo  TRUE
	#define EXP_iecvaraccexitvarinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccexitvarinfo", (RTS_UINTPTR)iecvaraccexitvarinfo, 1, 0, 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccexitvarinfo
	#define EXT_CmpIecVarAccessiecvaraccexitvarinfo
	#define GET_CmpIecVarAccessiecvaraccexitvarinfo  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccexitvarinfo  iecvaraccexitvarinfo
	#define CHK_CmpIecVarAccessiecvaraccexitvarinfo  TRUE
	#define EXP_CmpIecVarAccessiecvaraccexitvarinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccexitvarinfo", (RTS_UINTPTR)iecvaraccexitvarinfo, 1, 0, 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccexitvarinfo
	#define EXT_iecvaraccexitvarinfo
	#define GET_iecvaraccexitvarinfo(fl)  CAL_CMGETAPI( "iecvaraccexitvarinfo" ) 
	#define CAL_iecvaraccexitvarinfo  iecvaraccexitvarinfo
	#define CHK_iecvaraccexitvarinfo  TRUE
	#define EXP_iecvaraccexitvarinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccexitvarinfo", (RTS_UINTPTR)iecvaraccexitvarinfo, 1, 0, 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccexitvarinfo  PFIECVARACCEXITVARINFO_IEC pfiecvaraccexitvarinfo;
	#define EXT_iecvaraccexitvarinfo  extern PFIECVARACCEXITVARINFO_IEC pfiecvaraccexitvarinfo;
	#define GET_iecvaraccexitvarinfo(fl)  s_pfCMGetAPI2( "iecvaraccexitvarinfo", (RTS_VOID_FCTPTR *)&pfiecvaraccexitvarinfo, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0x03050A00)
	#define CAL_iecvaraccexitvarinfo  pfiecvaraccexitvarinfo
	#define CHK_iecvaraccexitvarinfo  (pfiecvaraccexitvarinfo != NULL)
	#define EXP_iecvaraccexitvarinfo   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccexitvarinfo", (RTS_UINTPTR)iecvaraccexitvarinfo, 1, 0, 0x03050A00) 
#endif


/**
 * <description>iecvaraccgetfirstinterface</description>
 */
typedef struct tagiecvaraccgetfirstinterface_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	IIecVarAccess3 *IecVarAccGetFirstInterface;	/* VAR_OUTPUT */	
} iecvaraccgetfirstinterface_struct;

void CDECL CDECL_EXT iecvaraccgetfirstinterface(iecvaraccgetfirstinterface_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCGETFIRSTINTERFACE_IEC) (iecvaraccgetfirstinterface_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETFIRSTINTERFACE_NOTIMPLEMENTED)
	#define USE_iecvaraccgetfirstinterface
	#define EXT_iecvaraccgetfirstinterface
	#define GET_iecvaraccgetfirstinterface(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccgetfirstinterface(p0) 
	#define CHK_iecvaraccgetfirstinterface  FALSE
	#define EXP_iecvaraccgetfirstinterface  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccgetfirstinterface
	#define EXT_iecvaraccgetfirstinterface
	#define GET_iecvaraccgetfirstinterface(fl)  CAL_CMGETAPI( "iecvaraccgetfirstinterface" ) 
	#define CAL_iecvaraccgetfirstinterface  iecvaraccgetfirstinterface
	#define CHK_iecvaraccgetfirstinterface  TRUE
	#define EXP_iecvaraccgetfirstinterface  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetfirstinterface", (RTS_UINTPTR)iecvaraccgetfirstinterface, 1, RTSITF_GET_SIGNATURE(0, 0xDAF18C6C), 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccgetfirstinterface
	#define EXT_iecvaraccgetfirstinterface
	#define GET_iecvaraccgetfirstinterface(fl)  CAL_CMGETAPI( "iecvaraccgetfirstinterface" ) 
	#define CAL_iecvaraccgetfirstinterface  iecvaraccgetfirstinterface
	#define CHK_iecvaraccgetfirstinterface  TRUE
	#define EXP_iecvaraccgetfirstinterface  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetfirstinterface", (RTS_UINTPTR)iecvaraccgetfirstinterface, 1, RTSITF_GET_SIGNATURE(0, 0xDAF18C6C), 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccgetfirstinterface
	#define EXT_CmpIecVarAccessiecvaraccgetfirstinterface
	#define GET_CmpIecVarAccessiecvaraccgetfirstinterface  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccgetfirstinterface  iecvaraccgetfirstinterface
	#define CHK_CmpIecVarAccessiecvaraccgetfirstinterface  TRUE
	#define EXP_CmpIecVarAccessiecvaraccgetfirstinterface  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetfirstinterface", (RTS_UINTPTR)iecvaraccgetfirstinterface, 1, RTSITF_GET_SIGNATURE(0, 0xDAF18C6C), 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccgetfirstinterface
	#define EXT_iecvaraccgetfirstinterface
	#define GET_iecvaraccgetfirstinterface(fl)  CAL_CMGETAPI( "iecvaraccgetfirstinterface" ) 
	#define CAL_iecvaraccgetfirstinterface  iecvaraccgetfirstinterface
	#define CHK_iecvaraccgetfirstinterface  TRUE
	#define EXP_iecvaraccgetfirstinterface  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetfirstinterface", (RTS_UINTPTR)iecvaraccgetfirstinterface, 1, RTSITF_GET_SIGNATURE(0, 0xDAF18C6C), 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccgetfirstinterface  PFIECVARACCGETFIRSTINTERFACE_IEC pfiecvaraccgetfirstinterface;
	#define EXT_iecvaraccgetfirstinterface  extern PFIECVARACCGETFIRSTINTERFACE_IEC pfiecvaraccgetfirstinterface;
	#define GET_iecvaraccgetfirstinterface(fl)  s_pfCMGetAPI2( "iecvaraccgetfirstinterface", (RTS_VOID_FCTPTR *)&pfiecvaraccgetfirstinterface, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xDAF18C6C), 0x03050A00)
	#define CAL_iecvaraccgetfirstinterface  pfiecvaraccgetfirstinterface
	#define CHK_iecvaraccgetfirstinterface  (pfiecvaraccgetfirstinterface != NULL)
	#define EXP_iecvaraccgetfirstinterface   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetfirstinterface", (RTS_UINTPTR)iecvaraccgetfirstinterface, 1, RTSITF_GET_SIGNATURE(0, 0xDAF18C6C), 0x03050A00) 
#endif


/**
 * <description>iecvaraccgetfirstinterface2</description>
 */
typedef struct tagiecvaraccgetfirstinterface2_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	IBase *IecVarAccGetFirstInterface2;	/* VAR_OUTPUT */	
} iecvaraccgetfirstinterface2_struct;

void CDECL CDECL_EXT iecvaraccgetfirstinterface2(iecvaraccgetfirstinterface2_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCGETFIRSTINTERFACE2_IEC) (iecvaraccgetfirstinterface2_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETFIRSTINTERFACE2_NOTIMPLEMENTED)
	#define USE_iecvaraccgetfirstinterface2
	#define EXT_iecvaraccgetfirstinterface2
	#define GET_iecvaraccgetfirstinterface2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccgetfirstinterface2(p0) 
	#define CHK_iecvaraccgetfirstinterface2  FALSE
	#define EXP_iecvaraccgetfirstinterface2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccgetfirstinterface2
	#define EXT_iecvaraccgetfirstinterface2
	#define GET_iecvaraccgetfirstinterface2(fl)  CAL_CMGETAPI( "iecvaraccgetfirstinterface2" ) 
	#define CAL_iecvaraccgetfirstinterface2  iecvaraccgetfirstinterface2
	#define CHK_iecvaraccgetfirstinterface2  TRUE
	#define EXP_iecvaraccgetfirstinterface2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetfirstinterface2", (RTS_UINTPTR)iecvaraccgetfirstinterface2, 1, RTSITF_GET_SIGNATURE(0, 0x35A559A4), 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccgetfirstinterface2
	#define EXT_iecvaraccgetfirstinterface2
	#define GET_iecvaraccgetfirstinterface2(fl)  CAL_CMGETAPI( "iecvaraccgetfirstinterface2" ) 
	#define CAL_iecvaraccgetfirstinterface2  iecvaraccgetfirstinterface2
	#define CHK_iecvaraccgetfirstinterface2  TRUE
	#define EXP_iecvaraccgetfirstinterface2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetfirstinterface2", (RTS_UINTPTR)iecvaraccgetfirstinterface2, 1, RTSITF_GET_SIGNATURE(0, 0x35A559A4), 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccgetfirstinterface2
	#define EXT_CmpIecVarAccessiecvaraccgetfirstinterface2
	#define GET_CmpIecVarAccessiecvaraccgetfirstinterface2  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccgetfirstinterface2  iecvaraccgetfirstinterface2
	#define CHK_CmpIecVarAccessiecvaraccgetfirstinterface2  TRUE
	#define EXP_CmpIecVarAccessiecvaraccgetfirstinterface2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetfirstinterface2", (RTS_UINTPTR)iecvaraccgetfirstinterface2, 1, RTSITF_GET_SIGNATURE(0, 0x35A559A4), 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccgetfirstinterface2
	#define EXT_iecvaraccgetfirstinterface2
	#define GET_iecvaraccgetfirstinterface2(fl)  CAL_CMGETAPI( "iecvaraccgetfirstinterface2" ) 
	#define CAL_iecvaraccgetfirstinterface2  iecvaraccgetfirstinterface2
	#define CHK_iecvaraccgetfirstinterface2  TRUE
	#define EXP_iecvaraccgetfirstinterface2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetfirstinterface2", (RTS_UINTPTR)iecvaraccgetfirstinterface2, 1, RTSITF_GET_SIGNATURE(0, 0x35A559A4), 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccgetfirstinterface2  PFIECVARACCGETFIRSTINTERFACE2_IEC pfiecvaraccgetfirstinterface2;
	#define EXT_iecvaraccgetfirstinterface2  extern PFIECVARACCGETFIRSTINTERFACE2_IEC pfiecvaraccgetfirstinterface2;
	#define GET_iecvaraccgetfirstinterface2(fl)  s_pfCMGetAPI2( "iecvaraccgetfirstinterface2", (RTS_VOID_FCTPTR *)&pfiecvaraccgetfirstinterface2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x35A559A4), 0x03050A00)
	#define CAL_iecvaraccgetfirstinterface2  pfiecvaraccgetfirstinterface2
	#define CHK_iecvaraccgetfirstinterface2  (pfiecvaraccgetfirstinterface2 != NULL)
	#define EXP_iecvaraccgetfirstinterface2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetfirstinterface2", (RTS_UINTPTR)iecvaraccgetfirstinterface2, 1, RTSITF_GET_SIGNATURE(0, 0x35A559A4), 0x03050A00) 
#endif


/**
 * <description>iecvaraccgetnextinterface</description>
 */
typedef struct tagiecvaraccgetnextinterface_struct
{
	IIecVarAccess3 *pIPrev;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	IIecVarAccess3 *IecVarAccGetNextInterface;	/* VAR_OUTPUT */	
} iecvaraccgetnextinterface_struct;

void CDECL CDECL_EXT iecvaraccgetnextinterface(iecvaraccgetnextinterface_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCGETNEXTINTERFACE_IEC) (iecvaraccgetnextinterface_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNEXTINTERFACE_NOTIMPLEMENTED)
	#define USE_iecvaraccgetnextinterface
	#define EXT_iecvaraccgetnextinterface
	#define GET_iecvaraccgetnextinterface(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccgetnextinterface(p0) 
	#define CHK_iecvaraccgetnextinterface  FALSE
	#define EXP_iecvaraccgetnextinterface  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccgetnextinterface
	#define EXT_iecvaraccgetnextinterface
	#define GET_iecvaraccgetnextinterface(fl)  CAL_CMGETAPI( "iecvaraccgetnextinterface" ) 
	#define CAL_iecvaraccgetnextinterface  iecvaraccgetnextinterface
	#define CHK_iecvaraccgetnextinterface  TRUE
	#define EXP_iecvaraccgetnextinterface  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnextinterface", (RTS_UINTPTR)iecvaraccgetnextinterface, 1, RTSITF_GET_SIGNATURE(0, 0x7143BBE4), 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccgetnextinterface
	#define EXT_iecvaraccgetnextinterface
	#define GET_iecvaraccgetnextinterface(fl)  CAL_CMGETAPI( "iecvaraccgetnextinterface" ) 
	#define CAL_iecvaraccgetnextinterface  iecvaraccgetnextinterface
	#define CHK_iecvaraccgetnextinterface  TRUE
	#define EXP_iecvaraccgetnextinterface  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnextinterface", (RTS_UINTPTR)iecvaraccgetnextinterface, 1, RTSITF_GET_SIGNATURE(0, 0x7143BBE4), 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccgetnextinterface
	#define EXT_CmpIecVarAccessiecvaraccgetnextinterface
	#define GET_CmpIecVarAccessiecvaraccgetnextinterface  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccgetnextinterface  iecvaraccgetnextinterface
	#define CHK_CmpIecVarAccessiecvaraccgetnextinterface  TRUE
	#define EXP_CmpIecVarAccessiecvaraccgetnextinterface  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnextinterface", (RTS_UINTPTR)iecvaraccgetnextinterface, 1, RTSITF_GET_SIGNATURE(0, 0x7143BBE4), 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccgetnextinterface
	#define EXT_iecvaraccgetnextinterface
	#define GET_iecvaraccgetnextinterface(fl)  CAL_CMGETAPI( "iecvaraccgetnextinterface" ) 
	#define CAL_iecvaraccgetnextinterface  iecvaraccgetnextinterface
	#define CHK_iecvaraccgetnextinterface  TRUE
	#define EXP_iecvaraccgetnextinterface  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnextinterface", (RTS_UINTPTR)iecvaraccgetnextinterface, 1, RTSITF_GET_SIGNATURE(0, 0x7143BBE4), 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccgetnextinterface  PFIECVARACCGETNEXTINTERFACE_IEC pfiecvaraccgetnextinterface;
	#define EXT_iecvaraccgetnextinterface  extern PFIECVARACCGETNEXTINTERFACE_IEC pfiecvaraccgetnextinterface;
	#define GET_iecvaraccgetnextinterface(fl)  s_pfCMGetAPI2( "iecvaraccgetnextinterface", (RTS_VOID_FCTPTR *)&pfiecvaraccgetnextinterface, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x7143BBE4), 0x03050A00)
	#define CAL_iecvaraccgetnextinterface  pfiecvaraccgetnextinterface
	#define CHK_iecvaraccgetnextinterface  (pfiecvaraccgetnextinterface != NULL)
	#define EXP_iecvaraccgetnextinterface   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnextinterface", (RTS_UINTPTR)iecvaraccgetnextinterface, 1, RTSITF_GET_SIGNATURE(0, 0x7143BBE4), 0x03050A00) 
#endif


/**
 * <description>iecvaraccgetnextinterface2</description>
 */
typedef struct tagiecvaraccgetnextinterface2_struct
{
	IBase *pIPrev;						/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	IBase *IecVarAccGetNextInterface2;	/* VAR_OUTPUT */	
} iecvaraccgetnextinterface2_struct;

void CDECL CDECL_EXT iecvaraccgetnextinterface2(iecvaraccgetnextinterface2_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCGETNEXTINTERFACE2_IEC) (iecvaraccgetnextinterface2_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNEXTINTERFACE2_NOTIMPLEMENTED)
	#define USE_iecvaraccgetnextinterface2
	#define EXT_iecvaraccgetnextinterface2
	#define GET_iecvaraccgetnextinterface2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccgetnextinterface2(p0) 
	#define CHK_iecvaraccgetnextinterface2  FALSE
	#define EXP_iecvaraccgetnextinterface2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccgetnextinterface2
	#define EXT_iecvaraccgetnextinterface2
	#define GET_iecvaraccgetnextinterface2(fl)  CAL_CMGETAPI( "iecvaraccgetnextinterface2" ) 
	#define CAL_iecvaraccgetnextinterface2  iecvaraccgetnextinterface2
	#define CHK_iecvaraccgetnextinterface2  TRUE
	#define EXP_iecvaraccgetnextinterface2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnextinterface2", (RTS_UINTPTR)iecvaraccgetnextinterface2, 1, RTSITF_GET_SIGNATURE(0, 0xDCA77F90), 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccgetnextinterface2
	#define EXT_iecvaraccgetnextinterface2
	#define GET_iecvaraccgetnextinterface2(fl)  CAL_CMGETAPI( "iecvaraccgetnextinterface2" ) 
	#define CAL_iecvaraccgetnextinterface2  iecvaraccgetnextinterface2
	#define CHK_iecvaraccgetnextinterface2  TRUE
	#define EXP_iecvaraccgetnextinterface2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnextinterface2", (RTS_UINTPTR)iecvaraccgetnextinterface2, 1, RTSITF_GET_SIGNATURE(0, 0xDCA77F90), 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccgetnextinterface2
	#define EXT_CmpIecVarAccessiecvaraccgetnextinterface2
	#define GET_CmpIecVarAccessiecvaraccgetnextinterface2  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccgetnextinterface2  iecvaraccgetnextinterface2
	#define CHK_CmpIecVarAccessiecvaraccgetnextinterface2  TRUE
	#define EXP_CmpIecVarAccessiecvaraccgetnextinterface2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnextinterface2", (RTS_UINTPTR)iecvaraccgetnextinterface2, 1, RTSITF_GET_SIGNATURE(0, 0xDCA77F90), 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccgetnextinterface2
	#define EXT_iecvaraccgetnextinterface2
	#define GET_iecvaraccgetnextinterface2(fl)  CAL_CMGETAPI( "iecvaraccgetnextinterface2" ) 
	#define CAL_iecvaraccgetnextinterface2  iecvaraccgetnextinterface2
	#define CHK_iecvaraccgetnextinterface2  TRUE
	#define EXP_iecvaraccgetnextinterface2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnextinterface2", (RTS_UINTPTR)iecvaraccgetnextinterface2, 1, RTSITF_GET_SIGNATURE(0, 0xDCA77F90), 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccgetnextinterface2  PFIECVARACCGETNEXTINTERFACE2_IEC pfiecvaraccgetnextinterface2;
	#define EXT_iecvaraccgetnextinterface2  extern PFIECVARACCGETNEXTINTERFACE2_IEC pfiecvaraccgetnextinterface2;
	#define GET_iecvaraccgetnextinterface2(fl)  s_pfCMGetAPI2( "iecvaraccgetnextinterface2", (RTS_VOID_FCTPTR *)&pfiecvaraccgetnextinterface2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xDCA77F90), 0x03050A00)
	#define CAL_iecvaraccgetnextinterface2  pfiecvaraccgetnextinterface2
	#define CHK_iecvaraccgetnextinterface2  (pfiecvaraccgetnextinterface2 != NULL)
	#define EXP_iecvaraccgetnextinterface2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnextinterface2", (RTS_UINTPTR)iecvaraccgetnextinterface2, 1, RTSITF_GET_SIGNATURE(0, 0xDCA77F90), 0x03050A00) 
#endif


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

void CDECL CDECL_EXT iecvaraccgetnode4(iecvaraccgetnode4_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCGETNODE4_IEC) (iecvaraccgetnode4_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNODE4_NOTIMPLEMENTED)
	#define USE_iecvaraccgetnode4
	#define EXT_iecvaraccgetnode4
	#define GET_iecvaraccgetnode4(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccgetnode4(p0) 
	#define CHK_iecvaraccgetnode4  FALSE
	#define EXP_iecvaraccgetnode4  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccgetnode4
	#define EXT_iecvaraccgetnode4
	#define GET_iecvaraccgetnode4(fl)  CAL_CMGETAPI( "iecvaraccgetnode4" ) 
	#define CAL_iecvaraccgetnode4  iecvaraccgetnode4
	#define CHK_iecvaraccgetnode4  TRUE
	#define EXP_iecvaraccgetnode4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnode4", (RTS_UINTPTR)iecvaraccgetnode4, 1, 0, 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccgetnode4
	#define EXT_iecvaraccgetnode4
	#define GET_iecvaraccgetnode4(fl)  CAL_CMGETAPI( "iecvaraccgetnode4" ) 
	#define CAL_iecvaraccgetnode4  iecvaraccgetnode4
	#define CHK_iecvaraccgetnode4  TRUE
	#define EXP_iecvaraccgetnode4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnode4", (RTS_UINTPTR)iecvaraccgetnode4, 1, 0, 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccgetnode4
	#define EXT_CmpIecVarAccessiecvaraccgetnode4
	#define GET_CmpIecVarAccessiecvaraccgetnode4  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccgetnode4  iecvaraccgetnode4
	#define CHK_CmpIecVarAccessiecvaraccgetnode4  TRUE
	#define EXP_CmpIecVarAccessiecvaraccgetnode4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnode4", (RTS_UINTPTR)iecvaraccgetnode4, 1, 0, 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccgetnode4
	#define EXT_iecvaraccgetnode4
	#define GET_iecvaraccgetnode4(fl)  CAL_CMGETAPI( "iecvaraccgetnode4" ) 
	#define CAL_iecvaraccgetnode4  iecvaraccgetnode4
	#define CHK_iecvaraccgetnode4  TRUE
	#define EXP_iecvaraccgetnode4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnode4", (RTS_UINTPTR)iecvaraccgetnode4, 1, 0, 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccgetnode4  PFIECVARACCGETNODE4_IEC pfiecvaraccgetnode4;
	#define EXT_iecvaraccgetnode4  extern PFIECVARACCGETNODE4_IEC pfiecvaraccgetnode4;
	#define GET_iecvaraccgetnode4(fl)  s_pfCMGetAPI2( "iecvaraccgetnode4", (RTS_VOID_FCTPTR *)&pfiecvaraccgetnode4, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0x03050A00)
	#define CAL_iecvaraccgetnode4  pfiecvaraccgetnode4
	#define CHK_iecvaraccgetnode4  (pfiecvaraccgetnode4 != NULL)
	#define EXP_iecvaraccgetnode4   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnode4", (RTS_UINTPTR)iecvaraccgetnode4, 1, 0, 0x03050A00) 
#endif


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

void CDECL CDECL_EXT iecvaraccgetnodefullpath4(iecvaraccgetnodefullpath4_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCGETNODEFULLPATH4_IEC) (iecvaraccgetnodefullpath4_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNODEFULLPATH4_NOTIMPLEMENTED)
	#define USE_iecvaraccgetnodefullpath4
	#define EXT_iecvaraccgetnodefullpath4
	#define GET_iecvaraccgetnodefullpath4(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccgetnodefullpath4(p0) 
	#define CHK_iecvaraccgetnodefullpath4  FALSE
	#define EXP_iecvaraccgetnodefullpath4  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccgetnodefullpath4
	#define EXT_iecvaraccgetnodefullpath4
	#define GET_iecvaraccgetnodefullpath4(fl)  CAL_CMGETAPI( "iecvaraccgetnodefullpath4" ) 
	#define CAL_iecvaraccgetnodefullpath4  iecvaraccgetnodefullpath4
	#define CHK_iecvaraccgetnodefullpath4  TRUE
	#define EXP_iecvaraccgetnodefullpath4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnodefullpath4", (RTS_UINTPTR)iecvaraccgetnodefullpath4, 1, 0, 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccgetnodefullpath4
	#define EXT_iecvaraccgetnodefullpath4
	#define GET_iecvaraccgetnodefullpath4(fl)  CAL_CMGETAPI( "iecvaraccgetnodefullpath4" ) 
	#define CAL_iecvaraccgetnodefullpath4  iecvaraccgetnodefullpath4
	#define CHK_iecvaraccgetnodefullpath4  TRUE
	#define EXP_iecvaraccgetnodefullpath4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnodefullpath4", (RTS_UINTPTR)iecvaraccgetnodefullpath4, 1, 0, 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccgetnodefullpath4
	#define EXT_CmpIecVarAccessiecvaraccgetnodefullpath4
	#define GET_CmpIecVarAccessiecvaraccgetnodefullpath4  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccgetnodefullpath4  iecvaraccgetnodefullpath4
	#define CHK_CmpIecVarAccessiecvaraccgetnodefullpath4  TRUE
	#define EXP_CmpIecVarAccessiecvaraccgetnodefullpath4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnodefullpath4", (RTS_UINTPTR)iecvaraccgetnodefullpath4, 1, 0, 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccgetnodefullpath4
	#define EXT_iecvaraccgetnodefullpath4
	#define GET_iecvaraccgetnodefullpath4(fl)  CAL_CMGETAPI( "iecvaraccgetnodefullpath4" ) 
	#define CAL_iecvaraccgetnodefullpath4  iecvaraccgetnodefullpath4
	#define CHK_iecvaraccgetnodefullpath4  TRUE
	#define EXP_iecvaraccgetnodefullpath4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnodefullpath4", (RTS_UINTPTR)iecvaraccgetnodefullpath4, 1, 0, 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccgetnodefullpath4  PFIECVARACCGETNODEFULLPATH4_IEC pfiecvaraccgetnodefullpath4;
	#define EXT_iecvaraccgetnodefullpath4  extern PFIECVARACCGETNODEFULLPATH4_IEC pfiecvaraccgetnodefullpath4;
	#define GET_iecvaraccgetnodefullpath4(fl)  s_pfCMGetAPI2( "iecvaraccgetnodefullpath4", (RTS_VOID_FCTPTR *)&pfiecvaraccgetnodefullpath4, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0x03050A00)
	#define CAL_iecvaraccgetnodefullpath4  pfiecvaraccgetnodefullpath4
	#define CHK_iecvaraccgetnodefullpath4  (pfiecvaraccgetnodefullpath4 != NULL)
	#define EXP_iecvaraccgetnodefullpath4   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnodefullpath4", (RTS_UINTPTR)iecvaraccgetnodefullpath4, 1, 0, 0x03050A00) 
#endif


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

void CDECL CDECL_EXT iecvaraccgetnodename4(iecvaraccgetnodename4_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCGETNODENAME4_IEC) (iecvaraccgetnodename4_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNODENAME4_NOTIMPLEMENTED)
	#define USE_iecvaraccgetnodename4
	#define EXT_iecvaraccgetnodename4
	#define GET_iecvaraccgetnodename4(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccgetnodename4(p0) 
	#define CHK_iecvaraccgetnodename4  FALSE
	#define EXP_iecvaraccgetnodename4  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccgetnodename4
	#define EXT_iecvaraccgetnodename4
	#define GET_iecvaraccgetnodename4(fl)  CAL_CMGETAPI( "iecvaraccgetnodename4" ) 
	#define CAL_iecvaraccgetnodename4  iecvaraccgetnodename4
	#define CHK_iecvaraccgetnodename4  TRUE
	#define EXP_iecvaraccgetnodename4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnodename4", (RTS_UINTPTR)iecvaraccgetnodename4, 1, 0, 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccgetnodename4
	#define EXT_iecvaraccgetnodename4
	#define GET_iecvaraccgetnodename4(fl)  CAL_CMGETAPI( "iecvaraccgetnodename4" ) 
	#define CAL_iecvaraccgetnodename4  iecvaraccgetnodename4
	#define CHK_iecvaraccgetnodename4  TRUE
	#define EXP_iecvaraccgetnodename4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnodename4", (RTS_UINTPTR)iecvaraccgetnodename4, 1, 0, 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccgetnodename4
	#define EXT_CmpIecVarAccessiecvaraccgetnodename4
	#define GET_CmpIecVarAccessiecvaraccgetnodename4  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccgetnodename4  iecvaraccgetnodename4
	#define CHK_CmpIecVarAccessiecvaraccgetnodename4  TRUE
	#define EXP_CmpIecVarAccessiecvaraccgetnodename4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnodename4", (RTS_UINTPTR)iecvaraccgetnodename4, 1, 0, 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccgetnodename4
	#define EXT_iecvaraccgetnodename4
	#define GET_iecvaraccgetnodename4(fl)  CAL_CMGETAPI( "iecvaraccgetnodename4" ) 
	#define CAL_iecvaraccgetnodename4  iecvaraccgetnodename4
	#define CHK_iecvaraccgetnodename4  TRUE
	#define EXP_iecvaraccgetnodename4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnodename4", (RTS_UINTPTR)iecvaraccgetnodename4, 1, 0, 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccgetnodename4  PFIECVARACCGETNODENAME4_IEC pfiecvaraccgetnodename4;
	#define EXT_iecvaraccgetnodename4  extern PFIECVARACCGETNODENAME4_IEC pfiecvaraccgetnodename4;
	#define GET_iecvaraccgetnodename4(fl)  s_pfCMGetAPI2( "iecvaraccgetnodename4", (RTS_VOID_FCTPTR *)&pfiecvaraccgetnodename4, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0x03050A00)
	#define CAL_iecvaraccgetnodename4  pfiecvaraccgetnodename4
	#define CHK_iecvaraccgetnodename4  (pfiecvaraccgetnodename4 != NULL)
	#define EXP_iecvaraccgetnodename4   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccgetnodename4", (RTS_UINTPTR)iecvaraccgetnodename4, 1, 0, 0x03050A00) 
#endif


/**
 * <description>iecvaraccinitvarinfo</description>
 */
typedef struct tagiecvaraccinitvarinfo_struct
{
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_UINT nSizeOfVarInfo;		/* VAR_INPUT */	
	RTS_IEC_RESULT IecVarAccInitVarInfo;	/* VAR_OUTPUT */	
} iecvaraccinitvarinfo_struct;

void CDECL CDECL_EXT iecvaraccinitvarinfo(iecvaraccinitvarinfo_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCINITVARINFO_IEC) (iecvaraccinitvarinfo_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCINITVARINFO_NOTIMPLEMENTED)
	#define USE_iecvaraccinitvarinfo
	#define EXT_iecvaraccinitvarinfo
	#define GET_iecvaraccinitvarinfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccinitvarinfo(p0) 
	#define CHK_iecvaraccinitvarinfo  FALSE
	#define EXP_iecvaraccinitvarinfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccinitvarinfo
	#define EXT_iecvaraccinitvarinfo
	#define GET_iecvaraccinitvarinfo(fl)  CAL_CMGETAPI( "iecvaraccinitvarinfo" ) 
	#define CAL_iecvaraccinitvarinfo  iecvaraccinitvarinfo
	#define CHK_iecvaraccinitvarinfo  TRUE
	#define EXP_iecvaraccinitvarinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccinitvarinfo", (RTS_UINTPTR)iecvaraccinitvarinfo, 1, 0, 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccinitvarinfo
	#define EXT_iecvaraccinitvarinfo
	#define GET_iecvaraccinitvarinfo(fl)  CAL_CMGETAPI( "iecvaraccinitvarinfo" ) 
	#define CAL_iecvaraccinitvarinfo  iecvaraccinitvarinfo
	#define CHK_iecvaraccinitvarinfo  TRUE
	#define EXP_iecvaraccinitvarinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccinitvarinfo", (RTS_UINTPTR)iecvaraccinitvarinfo, 1, 0, 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccinitvarinfo
	#define EXT_CmpIecVarAccessiecvaraccinitvarinfo
	#define GET_CmpIecVarAccessiecvaraccinitvarinfo  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccinitvarinfo  iecvaraccinitvarinfo
	#define CHK_CmpIecVarAccessiecvaraccinitvarinfo  TRUE
	#define EXP_CmpIecVarAccessiecvaraccinitvarinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccinitvarinfo", (RTS_UINTPTR)iecvaraccinitvarinfo, 1, 0, 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccinitvarinfo
	#define EXT_iecvaraccinitvarinfo
	#define GET_iecvaraccinitvarinfo(fl)  CAL_CMGETAPI( "iecvaraccinitvarinfo" ) 
	#define CAL_iecvaraccinitvarinfo  iecvaraccinitvarinfo
	#define CHK_iecvaraccinitvarinfo  TRUE
	#define EXP_iecvaraccinitvarinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccinitvarinfo", (RTS_UINTPTR)iecvaraccinitvarinfo, 1, 0, 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccinitvarinfo  PFIECVARACCINITVARINFO_IEC pfiecvaraccinitvarinfo;
	#define EXT_iecvaraccinitvarinfo  extern PFIECVARACCINITVARINFO_IEC pfiecvaraccinitvarinfo;
	#define GET_iecvaraccinitvarinfo(fl)  s_pfCMGetAPI2( "iecvaraccinitvarinfo", (RTS_VOID_FCTPTR *)&pfiecvaraccinitvarinfo, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0x03050A00)
	#define CAL_iecvaraccinitvarinfo  pfiecvaraccinitvarinfo
	#define CHK_iecvaraccinitvarinfo  (pfiecvaraccinitvarinfo != NULL)
	#define EXP_iecvaraccinitvarinfo   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccinitvarinfo", (RTS_UINTPTR)iecvaraccinitvarinfo, 1, 0, 0x03050A00) 
#endif


/**
 * <description>iecvaraccinvalidatenode</description>
 */
typedef struct tagiecvaraccinvalidatenode_struct
{
	RTS_IEC_HANDLE hNode;				/* VAR_INPUT */	
	RTS_IEC_RESULT IecVarAccInvalidateNode;	/* VAR_OUTPUT */	
} iecvaraccinvalidatenode_struct;

void CDECL CDECL_EXT iecvaraccinvalidatenode(iecvaraccinvalidatenode_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCINVALIDATENODE_IEC) (iecvaraccinvalidatenode_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCINVALIDATENODE_NOTIMPLEMENTED)
	#define USE_iecvaraccinvalidatenode
	#define EXT_iecvaraccinvalidatenode
	#define GET_iecvaraccinvalidatenode(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccinvalidatenode(p0) 
	#define CHK_iecvaraccinvalidatenode  FALSE
	#define EXP_iecvaraccinvalidatenode  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccinvalidatenode
	#define EXT_iecvaraccinvalidatenode
	#define GET_iecvaraccinvalidatenode(fl)  CAL_CMGETAPI( "iecvaraccinvalidatenode" ) 
	#define CAL_iecvaraccinvalidatenode  iecvaraccinvalidatenode
	#define CHK_iecvaraccinvalidatenode  TRUE
	#define EXP_iecvaraccinvalidatenode  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccinvalidatenode", (RTS_UINTPTR)iecvaraccinvalidatenode, 1, RTSITF_GET_SIGNATURE(0, 0x0C905F23), 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccinvalidatenode
	#define EXT_iecvaraccinvalidatenode
	#define GET_iecvaraccinvalidatenode(fl)  CAL_CMGETAPI( "iecvaraccinvalidatenode" ) 
	#define CAL_iecvaraccinvalidatenode  iecvaraccinvalidatenode
	#define CHK_iecvaraccinvalidatenode  TRUE
	#define EXP_iecvaraccinvalidatenode  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccinvalidatenode", (RTS_UINTPTR)iecvaraccinvalidatenode, 1, RTSITF_GET_SIGNATURE(0, 0x0C905F23), 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccinvalidatenode
	#define EXT_CmpIecVarAccessiecvaraccinvalidatenode
	#define GET_CmpIecVarAccessiecvaraccinvalidatenode  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccinvalidatenode  iecvaraccinvalidatenode
	#define CHK_CmpIecVarAccessiecvaraccinvalidatenode  TRUE
	#define EXP_CmpIecVarAccessiecvaraccinvalidatenode  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccinvalidatenode", (RTS_UINTPTR)iecvaraccinvalidatenode, 1, RTSITF_GET_SIGNATURE(0, 0x0C905F23), 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccinvalidatenode
	#define EXT_iecvaraccinvalidatenode
	#define GET_iecvaraccinvalidatenode(fl)  CAL_CMGETAPI( "iecvaraccinvalidatenode" ) 
	#define CAL_iecvaraccinvalidatenode  iecvaraccinvalidatenode
	#define CHK_iecvaraccinvalidatenode  TRUE
	#define EXP_iecvaraccinvalidatenode  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccinvalidatenode", (RTS_UINTPTR)iecvaraccinvalidatenode, 1, RTSITF_GET_SIGNATURE(0, 0x0C905F23), 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccinvalidatenode  PFIECVARACCINVALIDATENODE_IEC pfiecvaraccinvalidatenode;
	#define EXT_iecvaraccinvalidatenode  extern PFIECVARACCINVALIDATENODE_IEC pfiecvaraccinvalidatenode;
	#define GET_iecvaraccinvalidatenode(fl)  s_pfCMGetAPI2( "iecvaraccinvalidatenode", (RTS_VOID_FCTPTR *)&pfiecvaraccinvalidatenode, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x0C905F23), 0x03050A00)
	#define CAL_iecvaraccinvalidatenode  pfiecvaraccinvalidatenode
	#define CHK_iecvaraccinvalidatenode  (pfiecvaraccinvalidatenode != NULL)
	#define EXP_iecvaraccinvalidatenode   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccinvalidatenode", (RTS_UINTPTR)iecvaraccinvalidatenode, 1, RTSITF_GET_SIGNATURE(0, 0x0C905F23), 0x03050A00) 
#endif


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

void CDECL CDECL_EXT iecvaraccnodeinfoaddreference(iecvaraccnodeinfoaddreference_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCNODEINFOADDREFERENCE_IEC) (iecvaraccnodeinfoaddreference_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCNODEINFOADDREFERENCE_NOTIMPLEMENTED)
	#define USE_iecvaraccnodeinfoaddreference
	#define EXT_iecvaraccnodeinfoaddreference
	#define GET_iecvaraccnodeinfoaddreference(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccnodeinfoaddreference(p0) 
	#define CHK_iecvaraccnodeinfoaddreference  FALSE
	#define EXP_iecvaraccnodeinfoaddreference  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccnodeinfoaddreference
	#define EXT_iecvaraccnodeinfoaddreference
	#define GET_iecvaraccnodeinfoaddreference(fl)  CAL_CMGETAPI( "iecvaraccnodeinfoaddreference" ) 
	#define CAL_iecvaraccnodeinfoaddreference  iecvaraccnodeinfoaddreference
	#define CHK_iecvaraccnodeinfoaddreference  TRUE
	#define EXP_iecvaraccnodeinfoaddreference  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccnodeinfoaddreference", (RTS_UINTPTR)iecvaraccnodeinfoaddreference, 1, RTSITF_GET_SIGNATURE(0xB66D74DC, 0x54D1E739), 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccnodeinfoaddreference
	#define EXT_iecvaraccnodeinfoaddreference
	#define GET_iecvaraccnodeinfoaddreference(fl)  CAL_CMGETAPI( "iecvaraccnodeinfoaddreference" ) 
	#define CAL_iecvaraccnodeinfoaddreference  iecvaraccnodeinfoaddreference
	#define CHK_iecvaraccnodeinfoaddreference  TRUE
	#define EXP_iecvaraccnodeinfoaddreference  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccnodeinfoaddreference", (RTS_UINTPTR)iecvaraccnodeinfoaddreference, 1, RTSITF_GET_SIGNATURE(0xB66D74DC, 0x54D1E739), 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccnodeinfoaddreference
	#define EXT_CmpIecVarAccessiecvaraccnodeinfoaddreference
	#define GET_CmpIecVarAccessiecvaraccnodeinfoaddreference  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccnodeinfoaddreference  iecvaraccnodeinfoaddreference
	#define CHK_CmpIecVarAccessiecvaraccnodeinfoaddreference  TRUE
	#define EXP_CmpIecVarAccessiecvaraccnodeinfoaddreference  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccnodeinfoaddreference", (RTS_UINTPTR)iecvaraccnodeinfoaddreference, 1, RTSITF_GET_SIGNATURE(0xB66D74DC, 0x54D1E739), 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccnodeinfoaddreference
	#define EXT_iecvaraccnodeinfoaddreference
	#define GET_iecvaraccnodeinfoaddreference(fl)  CAL_CMGETAPI( "iecvaraccnodeinfoaddreference" ) 
	#define CAL_iecvaraccnodeinfoaddreference  iecvaraccnodeinfoaddreference
	#define CHK_iecvaraccnodeinfoaddreference  TRUE
	#define EXP_iecvaraccnodeinfoaddreference  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccnodeinfoaddreference", (RTS_UINTPTR)iecvaraccnodeinfoaddreference, 1, RTSITF_GET_SIGNATURE(0xB66D74DC, 0x54D1E739), 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccnodeinfoaddreference  PFIECVARACCNODEINFOADDREFERENCE_IEC pfiecvaraccnodeinfoaddreference;
	#define EXT_iecvaraccnodeinfoaddreference  extern PFIECVARACCNODEINFOADDREFERENCE_IEC pfiecvaraccnodeinfoaddreference;
	#define GET_iecvaraccnodeinfoaddreference(fl)  s_pfCMGetAPI2( "iecvaraccnodeinfoaddreference", (RTS_VOID_FCTPTR *)&pfiecvaraccnodeinfoaddreference, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0xB66D74DC, 0x54D1E739), 0x03050A00)
	#define CAL_iecvaraccnodeinfoaddreference  pfiecvaraccnodeinfoaddreference
	#define CHK_iecvaraccnodeinfoaddreference  (pfiecvaraccnodeinfoaddreference != NULL)
	#define EXP_iecvaraccnodeinfoaddreference   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccnodeinfoaddreference", (RTS_UINTPTR)iecvaraccnodeinfoaddreference, 1, RTSITF_GET_SIGNATURE(0xB66D74DC, 0x54D1E739), 0x03050A00) 
#endif


/**
 * <description>iecvaraccnodeinfogetreference</description>
 */
typedef struct tagiecvaraccnodeinfogetreference_struct
{
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_BYTE *IecVarAccNodeInfoGetReference;	/* VAR_OUTPUT */	
} iecvaraccnodeinfogetreference_struct;

void CDECL CDECL_EXT iecvaraccnodeinfogetreference(iecvaraccnodeinfogetreference_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCNODEINFOGETREFERENCE_IEC) (iecvaraccnodeinfogetreference_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCNODEINFOGETREFERENCE_NOTIMPLEMENTED)
	#define USE_iecvaraccnodeinfogetreference
	#define EXT_iecvaraccnodeinfogetreference
	#define GET_iecvaraccnodeinfogetreference(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccnodeinfogetreference(p0) 
	#define CHK_iecvaraccnodeinfogetreference  FALSE
	#define EXP_iecvaraccnodeinfogetreference  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccnodeinfogetreference
	#define EXT_iecvaraccnodeinfogetreference
	#define GET_iecvaraccnodeinfogetreference(fl)  CAL_CMGETAPI( "iecvaraccnodeinfogetreference" ) 
	#define CAL_iecvaraccnodeinfogetreference  iecvaraccnodeinfogetreference
	#define CHK_iecvaraccnodeinfogetreference  TRUE
	#define EXP_iecvaraccnodeinfogetreference  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccnodeinfogetreference", (RTS_UINTPTR)iecvaraccnodeinfogetreference, 1, RTSITF_GET_SIGNATURE(0x4ABE0CEB, 0x84253FCA), 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccnodeinfogetreference
	#define EXT_iecvaraccnodeinfogetreference
	#define GET_iecvaraccnodeinfogetreference(fl)  CAL_CMGETAPI( "iecvaraccnodeinfogetreference" ) 
	#define CAL_iecvaraccnodeinfogetreference  iecvaraccnodeinfogetreference
	#define CHK_iecvaraccnodeinfogetreference  TRUE
	#define EXP_iecvaraccnodeinfogetreference  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccnodeinfogetreference", (RTS_UINTPTR)iecvaraccnodeinfogetreference, 1, RTSITF_GET_SIGNATURE(0x4ABE0CEB, 0x84253FCA), 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccnodeinfogetreference
	#define EXT_CmpIecVarAccessiecvaraccnodeinfogetreference
	#define GET_CmpIecVarAccessiecvaraccnodeinfogetreference  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccnodeinfogetreference  iecvaraccnodeinfogetreference
	#define CHK_CmpIecVarAccessiecvaraccnodeinfogetreference  TRUE
	#define EXP_CmpIecVarAccessiecvaraccnodeinfogetreference  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccnodeinfogetreference", (RTS_UINTPTR)iecvaraccnodeinfogetreference, 1, RTSITF_GET_SIGNATURE(0x4ABE0CEB, 0x84253FCA), 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccnodeinfogetreference
	#define EXT_iecvaraccnodeinfogetreference
	#define GET_iecvaraccnodeinfogetreference(fl)  CAL_CMGETAPI( "iecvaraccnodeinfogetreference" ) 
	#define CAL_iecvaraccnodeinfogetreference  iecvaraccnodeinfogetreference
	#define CHK_iecvaraccnodeinfogetreference  TRUE
	#define EXP_iecvaraccnodeinfogetreference  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccnodeinfogetreference", (RTS_UINTPTR)iecvaraccnodeinfogetreference, 1, RTSITF_GET_SIGNATURE(0x4ABE0CEB, 0x84253FCA), 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccnodeinfogetreference  PFIECVARACCNODEINFOGETREFERENCE_IEC pfiecvaraccnodeinfogetreference;
	#define EXT_iecvaraccnodeinfogetreference  extern PFIECVARACCNODEINFOGETREFERENCE_IEC pfiecvaraccnodeinfogetreference;
	#define GET_iecvaraccnodeinfogetreference(fl)  s_pfCMGetAPI2( "iecvaraccnodeinfogetreference", (RTS_VOID_FCTPTR *)&pfiecvaraccnodeinfogetreference, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0x4ABE0CEB, 0x84253FCA), 0x03050A00)
	#define CAL_iecvaraccnodeinfogetreference  pfiecvaraccnodeinfogetreference
	#define CHK_iecvaraccnodeinfogetreference  (pfiecvaraccnodeinfogetreference != NULL)
	#define EXP_iecvaraccnodeinfogetreference   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccnodeinfogetreference", (RTS_UINTPTR)iecvaraccnodeinfogetreference, 1, RTSITF_GET_SIGNATURE(0x4ABE0CEB, 0x84253FCA), 0x03050A00) 
#endif


/**
 * <description>iecvaraccnodeinforemovereference</description>
 */
typedef struct tagiecvaraccnodeinforemovereference_struct
{
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT IecVarAccNodeInfoRemoveReference;	/* VAR_OUTPUT */	
} iecvaraccnodeinforemovereference_struct;

void CDECL CDECL_EXT iecvaraccnodeinforemovereference(iecvaraccnodeinforemovereference_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCNODEINFOREMOVEREFERENCE_IEC) (iecvaraccnodeinforemovereference_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCNODEINFOREMOVEREFERENCE_NOTIMPLEMENTED)
	#define USE_iecvaraccnodeinforemovereference
	#define EXT_iecvaraccnodeinforemovereference
	#define GET_iecvaraccnodeinforemovereference(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccnodeinforemovereference(p0) 
	#define CHK_iecvaraccnodeinforemovereference  FALSE
	#define EXP_iecvaraccnodeinforemovereference  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccnodeinforemovereference
	#define EXT_iecvaraccnodeinforemovereference
	#define GET_iecvaraccnodeinforemovereference(fl)  CAL_CMGETAPI( "iecvaraccnodeinforemovereference" ) 
	#define CAL_iecvaraccnodeinforemovereference  iecvaraccnodeinforemovereference
	#define CHK_iecvaraccnodeinforemovereference  TRUE
	#define EXP_iecvaraccnodeinforemovereference  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccnodeinforemovereference", (RTS_UINTPTR)iecvaraccnodeinforemovereference, 1, RTSITF_GET_SIGNATURE(0xAAD90063, 0x725A147D), 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccnodeinforemovereference
	#define EXT_iecvaraccnodeinforemovereference
	#define GET_iecvaraccnodeinforemovereference(fl)  CAL_CMGETAPI( "iecvaraccnodeinforemovereference" ) 
	#define CAL_iecvaraccnodeinforemovereference  iecvaraccnodeinforemovereference
	#define CHK_iecvaraccnodeinforemovereference  TRUE
	#define EXP_iecvaraccnodeinforemovereference  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccnodeinforemovereference", (RTS_UINTPTR)iecvaraccnodeinforemovereference, 1, RTSITF_GET_SIGNATURE(0xAAD90063, 0x725A147D), 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccnodeinforemovereference
	#define EXT_CmpIecVarAccessiecvaraccnodeinforemovereference
	#define GET_CmpIecVarAccessiecvaraccnodeinforemovereference  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccnodeinforemovereference  iecvaraccnodeinforemovereference
	#define CHK_CmpIecVarAccessiecvaraccnodeinforemovereference  TRUE
	#define EXP_CmpIecVarAccessiecvaraccnodeinforemovereference  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccnodeinforemovereference", (RTS_UINTPTR)iecvaraccnodeinforemovereference, 1, RTSITF_GET_SIGNATURE(0xAAD90063, 0x725A147D), 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccnodeinforemovereference
	#define EXT_iecvaraccnodeinforemovereference
	#define GET_iecvaraccnodeinforemovereference(fl)  CAL_CMGETAPI( "iecvaraccnodeinforemovereference" ) 
	#define CAL_iecvaraccnodeinforemovereference  iecvaraccnodeinforemovereference
	#define CHK_iecvaraccnodeinforemovereference  TRUE
	#define EXP_iecvaraccnodeinforemovereference  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccnodeinforemovereference", (RTS_UINTPTR)iecvaraccnodeinforemovereference, 1, RTSITF_GET_SIGNATURE(0xAAD90063, 0x725A147D), 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccnodeinforemovereference  PFIECVARACCNODEINFOREMOVEREFERENCE_IEC pfiecvaraccnodeinforemovereference;
	#define EXT_iecvaraccnodeinforemovereference  extern PFIECVARACCNODEINFOREMOVEREFERENCE_IEC pfiecvaraccnodeinforemovereference;
	#define GET_iecvaraccnodeinforemovereference(fl)  s_pfCMGetAPI2( "iecvaraccnodeinforemovereference", (RTS_VOID_FCTPTR *)&pfiecvaraccnodeinforemovereference, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0xAAD90063, 0x725A147D), 0x03050A00)
	#define CAL_iecvaraccnodeinforemovereference  pfiecvaraccnodeinforemovereference
	#define CHK_iecvaraccnodeinforemovereference  (pfiecvaraccnodeinforemovereference != NULL)
	#define EXP_iecvaraccnodeinforemovereference   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccnodeinforemovereference", (RTS_UINTPTR)iecvaraccnodeinforemovereference, 1, RTSITF_GET_SIGNATURE(0xAAD90063, 0x725A147D), 0x03050A00) 
#endif


/**
 * <description>iecvaraccregisterinstance</description>
 */
typedef struct tagiecvaraccregisterinstance_struct
{
	IIecVarAccess *pIIecVarAccess;		/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE IecVarAccRegisterInstance;	/* VAR_OUTPUT */	
} iecvaraccregisterinstance_struct;

void CDECL CDECL_EXT iecvaraccregisterinstance(iecvaraccregisterinstance_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCREGISTERINSTANCE_IEC) (iecvaraccregisterinstance_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCREGISTERINSTANCE_NOTIMPLEMENTED)
	#define USE_iecvaraccregisterinstance
	#define EXT_iecvaraccregisterinstance
	#define GET_iecvaraccregisterinstance(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccregisterinstance(p0) 
	#define CHK_iecvaraccregisterinstance  FALSE
	#define EXP_iecvaraccregisterinstance  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccregisterinstance
	#define EXT_iecvaraccregisterinstance
	#define GET_iecvaraccregisterinstance(fl)  CAL_CMGETAPI( "iecvaraccregisterinstance" ) 
	#define CAL_iecvaraccregisterinstance  iecvaraccregisterinstance
	#define CHK_iecvaraccregisterinstance  TRUE
	#define EXP_iecvaraccregisterinstance  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccregisterinstance", (RTS_UINTPTR)iecvaraccregisterinstance, 1, RTSITF_GET_SIGNATURE(0, 0x2838418D), 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccregisterinstance
	#define EXT_iecvaraccregisterinstance
	#define GET_iecvaraccregisterinstance(fl)  CAL_CMGETAPI( "iecvaraccregisterinstance" ) 
	#define CAL_iecvaraccregisterinstance  iecvaraccregisterinstance
	#define CHK_iecvaraccregisterinstance  TRUE
	#define EXP_iecvaraccregisterinstance  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccregisterinstance", (RTS_UINTPTR)iecvaraccregisterinstance, 1, RTSITF_GET_SIGNATURE(0, 0x2838418D), 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccregisterinstance
	#define EXT_CmpIecVarAccessiecvaraccregisterinstance
	#define GET_CmpIecVarAccessiecvaraccregisterinstance  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccregisterinstance  iecvaraccregisterinstance
	#define CHK_CmpIecVarAccessiecvaraccregisterinstance  TRUE
	#define EXP_CmpIecVarAccessiecvaraccregisterinstance  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccregisterinstance", (RTS_UINTPTR)iecvaraccregisterinstance, 1, RTSITF_GET_SIGNATURE(0, 0x2838418D), 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccregisterinstance
	#define EXT_iecvaraccregisterinstance
	#define GET_iecvaraccregisterinstance(fl)  CAL_CMGETAPI( "iecvaraccregisterinstance" ) 
	#define CAL_iecvaraccregisterinstance  iecvaraccregisterinstance
	#define CHK_iecvaraccregisterinstance  TRUE
	#define EXP_iecvaraccregisterinstance  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccregisterinstance", (RTS_UINTPTR)iecvaraccregisterinstance, 1, RTSITF_GET_SIGNATURE(0, 0x2838418D), 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccregisterinstance  PFIECVARACCREGISTERINSTANCE_IEC pfiecvaraccregisterinstance;
	#define EXT_iecvaraccregisterinstance  extern PFIECVARACCREGISTERINSTANCE_IEC pfiecvaraccregisterinstance;
	#define GET_iecvaraccregisterinstance(fl)  s_pfCMGetAPI2( "iecvaraccregisterinstance", (RTS_VOID_FCTPTR *)&pfiecvaraccregisterinstance, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x2838418D), 0x03050A00)
	#define CAL_iecvaraccregisterinstance  pfiecvaraccregisterinstance
	#define CHK_iecvaraccregisterinstance  (pfiecvaraccregisterinstance != NULL)
	#define EXP_iecvaraccregisterinstance   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccregisterinstance", (RTS_UINTPTR)iecvaraccregisterinstance, 1, RTSITF_GET_SIGNATURE(0, 0x2838418D), 0x03050A00) 
#endif


/**
 * <description>iecvaraccregisterinstance2</description>
 */
typedef struct tagiecvaraccregisterinstance2_struct
{
	IIecVarAccess2 *pIIecVarAccess2;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE IecVarAccRegisterInstance2;	/* VAR_OUTPUT */	
} iecvaraccregisterinstance2_struct;

void CDECL CDECL_EXT iecvaraccregisterinstance2(iecvaraccregisterinstance2_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCREGISTERINSTANCE2_IEC) (iecvaraccregisterinstance2_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCREGISTERINSTANCE2_NOTIMPLEMENTED)
	#define USE_iecvaraccregisterinstance2
	#define EXT_iecvaraccregisterinstance2
	#define GET_iecvaraccregisterinstance2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccregisterinstance2(p0) 
	#define CHK_iecvaraccregisterinstance2  FALSE
	#define EXP_iecvaraccregisterinstance2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccregisterinstance2
	#define EXT_iecvaraccregisterinstance2
	#define GET_iecvaraccregisterinstance2(fl)  CAL_CMGETAPI( "iecvaraccregisterinstance2" ) 
	#define CAL_iecvaraccregisterinstance2  iecvaraccregisterinstance2
	#define CHK_iecvaraccregisterinstance2  TRUE
	#define EXP_iecvaraccregisterinstance2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccregisterinstance2", (RTS_UINTPTR)iecvaraccregisterinstance2, 1, RTSITF_GET_SIGNATURE(0, 0x12CBCF4F), 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccregisterinstance2
	#define EXT_iecvaraccregisterinstance2
	#define GET_iecvaraccregisterinstance2(fl)  CAL_CMGETAPI( "iecvaraccregisterinstance2" ) 
	#define CAL_iecvaraccregisterinstance2  iecvaraccregisterinstance2
	#define CHK_iecvaraccregisterinstance2  TRUE
	#define EXP_iecvaraccregisterinstance2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccregisterinstance2", (RTS_UINTPTR)iecvaraccregisterinstance2, 1, RTSITF_GET_SIGNATURE(0, 0x12CBCF4F), 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccregisterinstance2
	#define EXT_CmpIecVarAccessiecvaraccregisterinstance2
	#define GET_CmpIecVarAccessiecvaraccregisterinstance2  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccregisterinstance2  iecvaraccregisterinstance2
	#define CHK_CmpIecVarAccessiecvaraccregisterinstance2  TRUE
	#define EXP_CmpIecVarAccessiecvaraccregisterinstance2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccregisterinstance2", (RTS_UINTPTR)iecvaraccregisterinstance2, 1, RTSITF_GET_SIGNATURE(0, 0x12CBCF4F), 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccregisterinstance2
	#define EXT_iecvaraccregisterinstance2
	#define GET_iecvaraccregisterinstance2(fl)  CAL_CMGETAPI( "iecvaraccregisterinstance2" ) 
	#define CAL_iecvaraccregisterinstance2  iecvaraccregisterinstance2
	#define CHK_iecvaraccregisterinstance2  TRUE
	#define EXP_iecvaraccregisterinstance2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccregisterinstance2", (RTS_UINTPTR)iecvaraccregisterinstance2, 1, RTSITF_GET_SIGNATURE(0, 0x12CBCF4F), 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccregisterinstance2  PFIECVARACCREGISTERINSTANCE2_IEC pfiecvaraccregisterinstance2;
	#define EXT_iecvaraccregisterinstance2  extern PFIECVARACCREGISTERINSTANCE2_IEC pfiecvaraccregisterinstance2;
	#define GET_iecvaraccregisterinstance2(fl)  s_pfCMGetAPI2( "iecvaraccregisterinstance2", (RTS_VOID_FCTPTR *)&pfiecvaraccregisterinstance2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x12CBCF4F), 0x03050A00)
	#define CAL_iecvaraccregisterinstance2  pfiecvaraccregisterinstance2
	#define CHK_iecvaraccregisterinstance2  (pfiecvaraccregisterinstance2 != NULL)
	#define EXP_iecvaraccregisterinstance2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccregisterinstance2", (RTS_UINTPTR)iecvaraccregisterinstance2, 1, RTSITF_GET_SIGNATURE(0, 0x12CBCF4F), 0x03050A00) 
#endif


/**
 * <description>iecvaraccregisterinstance3</description>
 */
typedef struct tagiecvaraccregisterinstance3_struct
{
	IIecVarAccess3 *pIIecVarAccess3;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE IecVarAccRegisterInstance3;	/* VAR_OUTPUT */	
} iecvaraccregisterinstance3_struct;

void CDECL CDECL_EXT iecvaraccregisterinstance3(iecvaraccregisterinstance3_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCREGISTERINSTANCE3_IEC) (iecvaraccregisterinstance3_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCREGISTERINSTANCE3_NOTIMPLEMENTED)
	#define USE_iecvaraccregisterinstance3
	#define EXT_iecvaraccregisterinstance3
	#define GET_iecvaraccregisterinstance3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccregisterinstance3(p0) 
	#define CHK_iecvaraccregisterinstance3  FALSE
	#define EXP_iecvaraccregisterinstance3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccregisterinstance3
	#define EXT_iecvaraccregisterinstance3
	#define GET_iecvaraccregisterinstance3(fl)  CAL_CMGETAPI( "iecvaraccregisterinstance3" ) 
	#define CAL_iecvaraccregisterinstance3  iecvaraccregisterinstance3
	#define CHK_iecvaraccregisterinstance3  TRUE
	#define EXP_iecvaraccregisterinstance3  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccregisterinstance3", (RTS_UINTPTR)iecvaraccregisterinstance3, 1, RTSITF_GET_SIGNATURE(0, 0xC1E3F2D6), 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccregisterinstance3
	#define EXT_iecvaraccregisterinstance3
	#define GET_iecvaraccregisterinstance3(fl)  CAL_CMGETAPI( "iecvaraccregisterinstance3" ) 
	#define CAL_iecvaraccregisterinstance3  iecvaraccregisterinstance3
	#define CHK_iecvaraccregisterinstance3  TRUE
	#define EXP_iecvaraccregisterinstance3  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccregisterinstance3", (RTS_UINTPTR)iecvaraccregisterinstance3, 1, RTSITF_GET_SIGNATURE(0, 0xC1E3F2D6), 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccregisterinstance3
	#define EXT_CmpIecVarAccessiecvaraccregisterinstance3
	#define GET_CmpIecVarAccessiecvaraccregisterinstance3  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccregisterinstance3  iecvaraccregisterinstance3
	#define CHK_CmpIecVarAccessiecvaraccregisterinstance3  TRUE
	#define EXP_CmpIecVarAccessiecvaraccregisterinstance3  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccregisterinstance3", (RTS_UINTPTR)iecvaraccregisterinstance3, 1, RTSITF_GET_SIGNATURE(0, 0xC1E3F2D6), 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccregisterinstance3
	#define EXT_iecvaraccregisterinstance3
	#define GET_iecvaraccregisterinstance3(fl)  CAL_CMGETAPI( "iecvaraccregisterinstance3" ) 
	#define CAL_iecvaraccregisterinstance3  iecvaraccregisterinstance3
	#define CHK_iecvaraccregisterinstance3  TRUE
	#define EXP_iecvaraccregisterinstance3  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccregisterinstance3", (RTS_UINTPTR)iecvaraccregisterinstance3, 1, RTSITF_GET_SIGNATURE(0, 0xC1E3F2D6), 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccregisterinstance3  PFIECVARACCREGISTERINSTANCE3_IEC pfiecvaraccregisterinstance3;
	#define EXT_iecvaraccregisterinstance3  extern PFIECVARACCREGISTERINSTANCE3_IEC pfiecvaraccregisterinstance3;
	#define GET_iecvaraccregisterinstance3(fl)  s_pfCMGetAPI2( "iecvaraccregisterinstance3", (RTS_VOID_FCTPTR *)&pfiecvaraccregisterinstance3, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xC1E3F2D6), 0x03050A00)
	#define CAL_iecvaraccregisterinstance3  pfiecvaraccregisterinstance3
	#define CHK_iecvaraccregisterinstance3  (pfiecvaraccregisterinstance3 != NULL)
	#define EXP_iecvaraccregisterinstance3   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccregisterinstance3", (RTS_UINTPTR)iecvaraccregisterinstance3, 1, RTSITF_GET_SIGNATURE(0, 0xC1E3F2D6), 0x03050A00) 
#endif


/**
 * <description>iecvaraccregisterinstancebase</description>
 */
typedef struct tagiecvaraccregisterinstancebase_struct
{
	IBase *pIBase;						/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE IecVarAccRegisterInstanceBase;	/* VAR_OUTPUT */	
} iecvaraccregisterinstancebase_struct;

void CDECL CDECL_EXT iecvaraccregisterinstancebase(iecvaraccregisterinstancebase_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCREGISTERINSTANCEBASE_IEC) (iecvaraccregisterinstancebase_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCREGISTERINSTANCEBASE_NOTIMPLEMENTED)
	#define USE_iecvaraccregisterinstancebase
	#define EXT_iecvaraccregisterinstancebase
	#define GET_iecvaraccregisterinstancebase(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccregisterinstancebase(p0) 
	#define CHK_iecvaraccregisterinstancebase  FALSE
	#define EXP_iecvaraccregisterinstancebase  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccregisterinstancebase
	#define EXT_iecvaraccregisterinstancebase
	#define GET_iecvaraccregisterinstancebase(fl)  CAL_CMGETAPI( "iecvaraccregisterinstancebase" ) 
	#define CAL_iecvaraccregisterinstancebase  iecvaraccregisterinstancebase
	#define CHK_iecvaraccregisterinstancebase  TRUE
	#define EXP_iecvaraccregisterinstancebase  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccregisterinstancebase", (RTS_UINTPTR)iecvaraccregisterinstancebase, 1, RTSITF_GET_SIGNATURE(0, 0xCD8685B0), 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccregisterinstancebase
	#define EXT_iecvaraccregisterinstancebase
	#define GET_iecvaraccregisterinstancebase(fl)  CAL_CMGETAPI( "iecvaraccregisterinstancebase" ) 
	#define CAL_iecvaraccregisterinstancebase  iecvaraccregisterinstancebase
	#define CHK_iecvaraccregisterinstancebase  TRUE
	#define EXP_iecvaraccregisterinstancebase  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccregisterinstancebase", (RTS_UINTPTR)iecvaraccregisterinstancebase, 1, RTSITF_GET_SIGNATURE(0, 0xCD8685B0), 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccregisterinstancebase
	#define EXT_CmpIecVarAccessiecvaraccregisterinstancebase
	#define GET_CmpIecVarAccessiecvaraccregisterinstancebase  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccregisterinstancebase  iecvaraccregisterinstancebase
	#define CHK_CmpIecVarAccessiecvaraccregisterinstancebase  TRUE
	#define EXP_CmpIecVarAccessiecvaraccregisterinstancebase  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccregisterinstancebase", (RTS_UINTPTR)iecvaraccregisterinstancebase, 1, RTSITF_GET_SIGNATURE(0, 0xCD8685B0), 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccregisterinstancebase
	#define EXT_iecvaraccregisterinstancebase
	#define GET_iecvaraccregisterinstancebase(fl)  CAL_CMGETAPI( "iecvaraccregisterinstancebase" ) 
	#define CAL_iecvaraccregisterinstancebase  iecvaraccregisterinstancebase
	#define CHK_iecvaraccregisterinstancebase  TRUE
	#define EXP_iecvaraccregisterinstancebase  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccregisterinstancebase", (RTS_UINTPTR)iecvaraccregisterinstancebase, 1, RTSITF_GET_SIGNATURE(0, 0xCD8685B0), 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccregisterinstancebase  PFIECVARACCREGISTERINSTANCEBASE_IEC pfiecvaraccregisterinstancebase;
	#define EXT_iecvaraccregisterinstancebase  extern PFIECVARACCREGISTERINSTANCEBASE_IEC pfiecvaraccregisterinstancebase;
	#define GET_iecvaraccregisterinstancebase(fl)  s_pfCMGetAPI2( "iecvaraccregisterinstancebase", (RTS_VOID_FCTPTR *)&pfiecvaraccregisterinstancebase, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xCD8685B0), 0x03050A00)
	#define CAL_iecvaraccregisterinstancebase  pfiecvaraccregisterinstancebase
	#define CHK_iecvaraccregisterinstancebase  (pfiecvaraccregisterinstancebase != NULL)
	#define EXP_iecvaraccregisterinstancebase   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccregisterinstancebase", (RTS_UINTPTR)iecvaraccregisterinstancebase, 1, RTSITF_GET_SIGNATURE(0, 0xCD8685B0), 0x03050A00) 
#endif


/**
 * <description>iecvaraccsetsymbolconfigcrc</description>
 */
typedef struct tagiecvaraccsetsymbolconfigcrc_struct
{
	RTS_IEC_HANDLE hInstance;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiCrc;				/* VAR_INPUT */	
	RTS_IEC_RESULT IecVarAccSetSymbolconfigCrc;	/* VAR_OUTPUT */	
} iecvaraccsetsymbolconfigcrc_struct;

void CDECL CDECL_EXT iecvaraccsetsymbolconfigcrc(iecvaraccsetsymbolconfigcrc_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCSETSYMBOLCONFIGCRC_IEC) (iecvaraccsetsymbolconfigcrc_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCSETSYMBOLCONFIGCRC_NOTIMPLEMENTED)
	#define USE_iecvaraccsetsymbolconfigcrc
	#define EXT_iecvaraccsetsymbolconfigcrc
	#define GET_iecvaraccsetsymbolconfigcrc(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccsetsymbolconfigcrc(p0) 
	#define CHK_iecvaraccsetsymbolconfigcrc  FALSE
	#define EXP_iecvaraccsetsymbolconfigcrc  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccsetsymbolconfigcrc
	#define EXT_iecvaraccsetsymbolconfigcrc
	#define GET_iecvaraccsetsymbolconfigcrc(fl)  CAL_CMGETAPI( "iecvaraccsetsymbolconfigcrc" ) 
	#define CAL_iecvaraccsetsymbolconfigcrc  iecvaraccsetsymbolconfigcrc
	#define CHK_iecvaraccsetsymbolconfigcrc  TRUE
	#define EXP_iecvaraccsetsymbolconfigcrc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccsetsymbolconfigcrc", (RTS_UINTPTR)iecvaraccsetsymbolconfigcrc, 1, 0xFDCEC8DA, 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccsetsymbolconfigcrc
	#define EXT_iecvaraccsetsymbolconfigcrc
	#define GET_iecvaraccsetsymbolconfigcrc(fl)  CAL_CMGETAPI( "iecvaraccsetsymbolconfigcrc" ) 
	#define CAL_iecvaraccsetsymbolconfigcrc  iecvaraccsetsymbolconfigcrc
	#define CHK_iecvaraccsetsymbolconfigcrc  TRUE
	#define EXP_iecvaraccsetsymbolconfigcrc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccsetsymbolconfigcrc", (RTS_UINTPTR)iecvaraccsetsymbolconfigcrc, 1, 0xFDCEC8DA, 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccsetsymbolconfigcrc
	#define EXT_CmpIecVarAccessiecvaraccsetsymbolconfigcrc
	#define GET_CmpIecVarAccessiecvaraccsetsymbolconfigcrc  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccsetsymbolconfigcrc  iecvaraccsetsymbolconfigcrc
	#define CHK_CmpIecVarAccessiecvaraccsetsymbolconfigcrc  TRUE
	#define EXP_CmpIecVarAccessiecvaraccsetsymbolconfigcrc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccsetsymbolconfigcrc", (RTS_UINTPTR)iecvaraccsetsymbolconfigcrc, 1, 0xFDCEC8DA, 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccsetsymbolconfigcrc
	#define EXT_iecvaraccsetsymbolconfigcrc
	#define GET_iecvaraccsetsymbolconfigcrc(fl)  CAL_CMGETAPI( "iecvaraccsetsymbolconfigcrc" ) 
	#define CAL_iecvaraccsetsymbolconfigcrc  iecvaraccsetsymbolconfigcrc
	#define CHK_iecvaraccsetsymbolconfigcrc  TRUE
	#define EXP_iecvaraccsetsymbolconfigcrc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccsetsymbolconfigcrc", (RTS_UINTPTR)iecvaraccsetsymbolconfigcrc, 1, 0xFDCEC8DA, 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccsetsymbolconfigcrc  PFIECVARACCSETSYMBOLCONFIGCRC_IEC pfiecvaraccsetsymbolconfigcrc;
	#define EXT_iecvaraccsetsymbolconfigcrc  extern PFIECVARACCSETSYMBOLCONFIGCRC_IEC pfiecvaraccsetsymbolconfigcrc;
	#define GET_iecvaraccsetsymbolconfigcrc(fl)  s_pfCMGetAPI2( "iecvaraccsetsymbolconfigcrc", (RTS_VOID_FCTPTR *)&pfiecvaraccsetsymbolconfigcrc, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xFDCEC8DA, 0x03050A00)
	#define CAL_iecvaraccsetsymbolconfigcrc  pfiecvaraccsetsymbolconfigcrc
	#define CHK_iecvaraccsetsymbolconfigcrc  (pfiecvaraccsetsymbolconfigcrc != NULL)
	#define EXP_iecvaraccsetsymbolconfigcrc   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccsetsymbolconfigcrc", (RTS_UINTPTR)iecvaraccsetsymbolconfigcrc, 1, 0xFDCEC8DA, 0x03050A00) 
#endif


/**
 * <description>iecvaraccunregisterinstance</description>
 */
typedef struct tagiecvaraccunregisterinstance_struct
{
	RTS_IEC_HANDLE hInstance;			/* VAR_INPUT */	
	RTS_IEC_RESULT IecVarAccUnregisterInstance;	/* VAR_OUTPUT */	
} iecvaraccunregisterinstance_struct;

void CDECL CDECL_EXT iecvaraccunregisterinstance(iecvaraccunregisterinstance_struct *p);
typedef void (CDECL CDECL_EXT* PFIECVARACCUNREGISTERINSTANCE_IEC) (iecvaraccunregisterinstance_struct *p);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCUNREGISTERINSTANCE_NOTIMPLEMENTED)
	#define USE_iecvaraccunregisterinstance
	#define EXT_iecvaraccunregisterinstance
	#define GET_iecvaraccunregisterinstance(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iecvaraccunregisterinstance(p0) 
	#define CHK_iecvaraccunregisterinstance  FALSE
	#define EXP_iecvaraccunregisterinstance  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iecvaraccunregisterinstance
	#define EXT_iecvaraccunregisterinstance
	#define GET_iecvaraccunregisterinstance(fl)  CAL_CMGETAPI( "iecvaraccunregisterinstance" ) 
	#define CAL_iecvaraccunregisterinstance  iecvaraccunregisterinstance
	#define CHK_iecvaraccunregisterinstance  TRUE
	#define EXP_iecvaraccunregisterinstance  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccunregisterinstance", (RTS_UINTPTR)iecvaraccunregisterinstance, 1, RTSITF_GET_SIGNATURE(0, 0xEDB8227D), 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_iecvaraccunregisterinstance
	#define EXT_iecvaraccunregisterinstance
	#define GET_iecvaraccunregisterinstance(fl)  CAL_CMGETAPI( "iecvaraccunregisterinstance" ) 
	#define CAL_iecvaraccunregisterinstance  iecvaraccunregisterinstance
	#define CHK_iecvaraccunregisterinstance  TRUE
	#define EXP_iecvaraccunregisterinstance  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccunregisterinstance", (RTS_UINTPTR)iecvaraccunregisterinstance, 1, RTSITF_GET_SIGNATURE(0, 0xEDB8227D), 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessiecvaraccunregisterinstance
	#define EXT_CmpIecVarAccessiecvaraccunregisterinstance
	#define GET_CmpIecVarAccessiecvaraccunregisterinstance  ERR_OK
	#define CAL_CmpIecVarAccessiecvaraccunregisterinstance  iecvaraccunregisterinstance
	#define CHK_CmpIecVarAccessiecvaraccunregisterinstance  TRUE
	#define EXP_CmpIecVarAccessiecvaraccunregisterinstance  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccunregisterinstance", (RTS_UINTPTR)iecvaraccunregisterinstance, 1, RTSITF_GET_SIGNATURE(0, 0xEDB8227D), 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_iecvaraccunregisterinstance
	#define EXT_iecvaraccunregisterinstance
	#define GET_iecvaraccunregisterinstance(fl)  CAL_CMGETAPI( "iecvaraccunregisterinstance" ) 
	#define CAL_iecvaraccunregisterinstance  iecvaraccunregisterinstance
	#define CHK_iecvaraccunregisterinstance  TRUE
	#define EXP_iecvaraccunregisterinstance  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccunregisterinstance", (RTS_UINTPTR)iecvaraccunregisterinstance, 1, RTSITF_GET_SIGNATURE(0, 0xEDB8227D), 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_iecvaraccunregisterinstance  PFIECVARACCUNREGISTERINSTANCE_IEC pfiecvaraccunregisterinstance;
	#define EXT_iecvaraccunregisterinstance  extern PFIECVARACCUNREGISTERINSTANCE_IEC pfiecvaraccunregisterinstance;
	#define GET_iecvaraccunregisterinstance(fl)  s_pfCMGetAPI2( "iecvaraccunregisterinstance", (RTS_VOID_FCTPTR *)&pfiecvaraccunregisterinstance, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xEDB8227D), 0x03050A00)
	#define CAL_iecvaraccunregisterinstance  pfiecvaraccunregisterinstance
	#define CHK_iecvaraccunregisterinstance  (pfiecvaraccunregisterinstance != NULL)
	#define EXP_iecvaraccunregisterinstance   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iecvaraccunregisterinstance", (RTS_UINTPTR)iecvaraccunregisterinstance, 1, RTSITF_GET_SIGNATURE(0, 0xEDB8227D), 0x03050A00) 
#endif


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
RTS_RESULT CDECL IecVarAccInitVarInfo(VariableInformationStruct2 *pVarInfo, RTS_UI16 nSizeOfVarInfo);
typedef RTS_RESULT (CDECL * PFIECVARACCINITVARINFO) (VariableInformationStruct2 *pVarInfo, RTS_UI16 nSizeOfVarInfo);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCINITVARINFO_NOTIMPLEMENTED)
	#define USE_IecVarAccInitVarInfo
	#define EXT_IecVarAccInitVarInfo
	#define GET_IecVarAccInitVarInfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccInitVarInfo(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccInitVarInfo  FALSE
	#define EXP_IecVarAccInitVarInfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccInitVarInfo
	#define EXT_IecVarAccInitVarInfo
	#define GET_IecVarAccInitVarInfo(fl)  CAL_CMGETAPI( "IecVarAccInitVarInfo" ) 
	#define CAL_IecVarAccInitVarInfo  IecVarAccInitVarInfo
	#define CHK_IecVarAccInitVarInfo  TRUE
	#define EXP_IecVarAccInitVarInfo  CAL_CMEXPAPI( "IecVarAccInitVarInfo" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccInitVarInfo
	#define EXT_IecVarAccInitVarInfo
	#define GET_IecVarAccInitVarInfo(fl)  CAL_CMGETAPI( "IecVarAccInitVarInfo" ) 
	#define CAL_IecVarAccInitVarInfo  IecVarAccInitVarInfo
	#define CHK_IecVarAccInitVarInfo  TRUE
	#define EXP_IecVarAccInitVarInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccInitVarInfo", (RTS_UINTPTR)IecVarAccInitVarInfo, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccInitVarInfo
	#define EXT_CmpIecVarAccessIecVarAccInitVarInfo
	#define GET_CmpIecVarAccessIecVarAccInitVarInfo  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccInitVarInfo pICmpIecVarAccess->IIecVarAccInitVarInfo
	#define CHK_CmpIecVarAccessIecVarAccInitVarInfo (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccInitVarInfo  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccInitVarInfo
	#define EXT_IecVarAccInitVarInfo
	#define GET_IecVarAccInitVarInfo(fl)  CAL_CMGETAPI( "IecVarAccInitVarInfo" ) 
	#define CAL_IecVarAccInitVarInfo pICmpIecVarAccess->IIecVarAccInitVarInfo
	#define CHK_IecVarAccInitVarInfo (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccInitVarInfo  CAL_CMEXPAPI( "IecVarAccInitVarInfo" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccInitVarInfo  PFIECVARACCINITVARINFO pfIecVarAccInitVarInfo;
	#define EXT_IecVarAccInitVarInfo  extern PFIECVARACCINITVARINFO pfIecVarAccInitVarInfo;
	#define GET_IecVarAccInitVarInfo(fl)  s_pfCMGetAPI2( "IecVarAccInitVarInfo", (RTS_VOID_FCTPTR *)&pfIecVarAccInitVarInfo, (fl), 0, 0)
	#define CAL_IecVarAccInitVarInfo  pfIecVarAccInitVarInfo
	#define CHK_IecVarAccInitVarInfo  (pfIecVarAccInitVarInfo != NULL)
	#define EXP_IecVarAccInitVarInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccInitVarInfo", (RTS_UINTPTR)IecVarAccInitVarInfo, 0, 0) 
#endif




/**
 * <description>Release the VarInfo.
 *	NOTE:
 *	You can cast a VariableInformationStruct3 to VariableInformationStruct2, but the nSizeOfVarInfo must match the real VariableInformationStruct3!</description>
 * <param name="pVarInfo" type="IN">Pointer to varinfo to release</param>
 * <result>Error code</result>
 */
RTS_RESULT CDECL IecVarAccExitVarInfo(VariableInformationStruct2 *pVarInfo);
typedef RTS_RESULT (CDECL * PFIECVARACCEXITVARINFO) (VariableInformationStruct2 *pVarInfo);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCEXITVARINFO_NOTIMPLEMENTED)
	#define USE_IecVarAccExitVarInfo
	#define EXT_IecVarAccExitVarInfo
	#define GET_IecVarAccExitVarInfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccExitVarInfo(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccExitVarInfo  FALSE
	#define EXP_IecVarAccExitVarInfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccExitVarInfo
	#define EXT_IecVarAccExitVarInfo
	#define GET_IecVarAccExitVarInfo(fl)  CAL_CMGETAPI( "IecVarAccExitVarInfo" ) 
	#define CAL_IecVarAccExitVarInfo  IecVarAccExitVarInfo
	#define CHK_IecVarAccExitVarInfo  TRUE
	#define EXP_IecVarAccExitVarInfo  CAL_CMEXPAPI( "IecVarAccExitVarInfo" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccExitVarInfo
	#define EXT_IecVarAccExitVarInfo
	#define GET_IecVarAccExitVarInfo(fl)  CAL_CMGETAPI( "IecVarAccExitVarInfo" ) 
	#define CAL_IecVarAccExitVarInfo  IecVarAccExitVarInfo
	#define CHK_IecVarAccExitVarInfo  TRUE
	#define EXP_IecVarAccExitVarInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccExitVarInfo", (RTS_UINTPTR)IecVarAccExitVarInfo, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccExitVarInfo
	#define EXT_CmpIecVarAccessIecVarAccExitVarInfo
	#define GET_CmpIecVarAccessIecVarAccExitVarInfo  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccExitVarInfo pICmpIecVarAccess->IIecVarAccExitVarInfo
	#define CHK_CmpIecVarAccessIecVarAccExitVarInfo (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccExitVarInfo  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccExitVarInfo
	#define EXT_IecVarAccExitVarInfo
	#define GET_IecVarAccExitVarInfo(fl)  CAL_CMGETAPI( "IecVarAccExitVarInfo" ) 
	#define CAL_IecVarAccExitVarInfo pICmpIecVarAccess->IIecVarAccExitVarInfo
	#define CHK_IecVarAccExitVarInfo (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccExitVarInfo  CAL_CMEXPAPI( "IecVarAccExitVarInfo" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccExitVarInfo  PFIECVARACCEXITVARINFO pfIecVarAccExitVarInfo;
	#define EXT_IecVarAccExitVarInfo  extern PFIECVARACCEXITVARINFO pfIecVarAccExitVarInfo;
	#define GET_IecVarAccExitVarInfo(fl)  s_pfCMGetAPI2( "IecVarAccExitVarInfo", (RTS_VOID_FCTPTR *)&pfIecVarAccExitVarInfo, (fl), 0, 0)
	#define CAL_IecVarAccExitVarInfo  pfIecVarAccExitVarInfo
	#define CHK_IecVarAccExitVarInfo  (pfIecVarAccExitVarInfo != NULL)
	#define EXP_IecVarAccExitVarInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccExitVarInfo", (RTS_UINTPTR)IecVarAccExitVarInfo, 0, 0) 
#endif




/**
 * <description>Copy content of VarInfo.
 *	NOTE:
 *	pVariableInformationDest must be initialized with IecVarAccInitVarInfo() before calling this function!
 * </description>
 * <param name="pVariableInformationDest" type="INOUT">Pointer to destination varinfo to copy to</param>
 * <param name="pVariableInformationSrc" type="IN">Pointer to source varinfo to copy from</param>
 * <result>Error code</result>
 */
RTS_RESULT CDECL IecVarAccCopyVarInfo(VariableInformationStruct2 *pVariableInformationDest, VariableInformationStruct2 *pVariableInformationSrc);
typedef RTS_RESULT (CDECL * PFIECVARACCCOPYVARINFO) (VariableInformationStruct2 *pVariableInformationDest, VariableInformationStruct2 *pVariableInformationSrc);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCCOPYVARINFO_NOTIMPLEMENTED)
	#define USE_IecVarAccCopyVarInfo
	#define EXT_IecVarAccCopyVarInfo
	#define GET_IecVarAccCopyVarInfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccCopyVarInfo(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccCopyVarInfo  FALSE
	#define EXP_IecVarAccCopyVarInfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccCopyVarInfo
	#define EXT_IecVarAccCopyVarInfo
	#define GET_IecVarAccCopyVarInfo(fl)  CAL_CMGETAPI( "IecVarAccCopyVarInfo" ) 
	#define CAL_IecVarAccCopyVarInfo  IecVarAccCopyVarInfo
	#define CHK_IecVarAccCopyVarInfo  TRUE
	#define EXP_IecVarAccCopyVarInfo  CAL_CMEXPAPI( "IecVarAccCopyVarInfo" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccCopyVarInfo
	#define EXT_IecVarAccCopyVarInfo
	#define GET_IecVarAccCopyVarInfo(fl)  CAL_CMGETAPI( "IecVarAccCopyVarInfo" ) 
	#define CAL_IecVarAccCopyVarInfo  IecVarAccCopyVarInfo
	#define CHK_IecVarAccCopyVarInfo  TRUE
	#define EXP_IecVarAccCopyVarInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccCopyVarInfo", (RTS_UINTPTR)IecVarAccCopyVarInfo, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccCopyVarInfo
	#define EXT_CmpIecVarAccessIecVarAccCopyVarInfo
	#define GET_CmpIecVarAccessIecVarAccCopyVarInfo  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccCopyVarInfo pICmpIecVarAccess->IIecVarAccCopyVarInfo
	#define CHK_CmpIecVarAccessIecVarAccCopyVarInfo (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccCopyVarInfo  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccCopyVarInfo
	#define EXT_IecVarAccCopyVarInfo
	#define GET_IecVarAccCopyVarInfo(fl)  CAL_CMGETAPI( "IecVarAccCopyVarInfo" ) 
	#define CAL_IecVarAccCopyVarInfo pICmpIecVarAccess->IIecVarAccCopyVarInfo
	#define CHK_IecVarAccCopyVarInfo (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccCopyVarInfo  CAL_CMEXPAPI( "IecVarAccCopyVarInfo" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccCopyVarInfo  PFIECVARACCCOPYVARINFO pfIecVarAccCopyVarInfo;
	#define EXT_IecVarAccCopyVarInfo  extern PFIECVARACCCOPYVARINFO pfIecVarAccCopyVarInfo;
	#define GET_IecVarAccCopyVarInfo(fl)  s_pfCMGetAPI2( "IecVarAccCopyVarInfo", (RTS_VOID_FCTPTR *)&pfIecVarAccCopyVarInfo, (fl), 0, 0)
	#define CAL_IecVarAccCopyVarInfo  pfIecVarAccCopyVarInfo
	#define CHK_IecVarAccCopyVarInfo  (pfIecVarAccCopyVarInfo != NULL)
	#define EXP_IecVarAccCopyVarInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccCopyVarInfo", (RTS_UINTPTR)IecVarAccCopyVarInfo, 0, 0) 
#endif




/**
 * <description>Get the first symbolic interface. Each symbolic application is called here an interface.</description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the first symbolic interface (symbolic application, called hInterface)</result>
 */
RTS_HANDLE CDECL IecVarAccGetFirstInterface(RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECVARACCGETFIRSTINTERFACE) (RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETFIRSTINTERFACE_NOTIMPLEMENTED)
	#define USE_IecVarAccGetFirstInterface
	#define EXT_IecVarAccGetFirstInterface
	#define GET_IecVarAccGetFirstInterface(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetFirstInterface(p0)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecVarAccGetFirstInterface  FALSE
	#define EXP_IecVarAccGetFirstInterface  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetFirstInterface
	#define EXT_IecVarAccGetFirstInterface
	#define GET_IecVarAccGetFirstInterface(fl)  CAL_CMGETAPI( "IecVarAccGetFirstInterface" ) 
	#define CAL_IecVarAccGetFirstInterface  IecVarAccGetFirstInterface
	#define CHK_IecVarAccGetFirstInterface  TRUE
	#define EXP_IecVarAccGetFirstInterface  CAL_CMEXPAPI( "IecVarAccGetFirstInterface" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetFirstInterface
	#define EXT_IecVarAccGetFirstInterface
	#define GET_IecVarAccGetFirstInterface(fl)  CAL_CMGETAPI( "IecVarAccGetFirstInterface" ) 
	#define CAL_IecVarAccGetFirstInterface  IecVarAccGetFirstInterface
	#define CHK_IecVarAccGetFirstInterface  TRUE
	#define EXP_IecVarAccGetFirstInterface  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetFirstInterface", (RTS_UINTPTR)IecVarAccGetFirstInterface, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetFirstInterface
	#define EXT_CmpIecVarAccessIecVarAccGetFirstInterface
	#define GET_CmpIecVarAccessIecVarAccGetFirstInterface  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetFirstInterface pICmpIecVarAccess->IIecVarAccGetFirstInterface
	#define CHK_CmpIecVarAccessIecVarAccGetFirstInterface (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetFirstInterface  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetFirstInterface
	#define EXT_IecVarAccGetFirstInterface
	#define GET_IecVarAccGetFirstInterface(fl)  CAL_CMGETAPI( "IecVarAccGetFirstInterface" ) 
	#define CAL_IecVarAccGetFirstInterface pICmpIecVarAccess->IIecVarAccGetFirstInterface
	#define CHK_IecVarAccGetFirstInterface (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetFirstInterface  CAL_CMEXPAPI( "IecVarAccGetFirstInterface" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetFirstInterface  PFIECVARACCGETFIRSTINTERFACE pfIecVarAccGetFirstInterface;
	#define EXT_IecVarAccGetFirstInterface  extern PFIECVARACCGETFIRSTINTERFACE pfIecVarAccGetFirstInterface;
	#define GET_IecVarAccGetFirstInterface(fl)  s_pfCMGetAPI2( "IecVarAccGetFirstInterface", (RTS_VOID_FCTPTR *)&pfIecVarAccGetFirstInterface, (fl), 0, 0)
	#define CAL_IecVarAccGetFirstInterface  pfIecVarAccGetFirstInterface
	#define CHK_IecVarAccGetFirstInterface  (pfIecVarAccGetFirstInterface != NULL)
	#define EXP_IecVarAccGetFirstInterface  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetFirstInterface", (RTS_UINTPTR)IecVarAccGetFirstInterface, 0, 0) 
#endif




/**
 * <description>Get the next symbolic interface</description>
 * <param name="hPrevInterface" type="IN">Handle to the previous interface</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the next symbolic interface (symbolic application)</result>
 */
RTS_HANDLE CDECL IecVarAccGetNextInterface(RTS_HANDLE hPrevInterface, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECVARACCGETNEXTINTERFACE) (RTS_HANDLE hPrevInterface, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNEXTINTERFACE_NOTIMPLEMENTED)
	#define USE_IecVarAccGetNextInterface
	#define EXT_IecVarAccGetNextInterface
	#define GET_IecVarAccGetNextInterface(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetNextInterface(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecVarAccGetNextInterface  FALSE
	#define EXP_IecVarAccGetNextInterface  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetNextInterface
	#define EXT_IecVarAccGetNextInterface
	#define GET_IecVarAccGetNextInterface(fl)  CAL_CMGETAPI( "IecVarAccGetNextInterface" ) 
	#define CAL_IecVarAccGetNextInterface  IecVarAccGetNextInterface
	#define CHK_IecVarAccGetNextInterface  TRUE
	#define EXP_IecVarAccGetNextInterface  CAL_CMEXPAPI( "IecVarAccGetNextInterface" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetNextInterface
	#define EXT_IecVarAccGetNextInterface
	#define GET_IecVarAccGetNextInterface(fl)  CAL_CMGETAPI( "IecVarAccGetNextInterface" ) 
	#define CAL_IecVarAccGetNextInterface  IecVarAccGetNextInterface
	#define CHK_IecVarAccGetNextInterface  TRUE
	#define EXP_IecVarAccGetNextInterface  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNextInterface", (RTS_UINTPTR)IecVarAccGetNextInterface, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetNextInterface
	#define EXT_CmpIecVarAccessIecVarAccGetNextInterface
	#define GET_CmpIecVarAccessIecVarAccGetNextInterface  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetNextInterface pICmpIecVarAccess->IIecVarAccGetNextInterface
	#define CHK_CmpIecVarAccessIecVarAccGetNextInterface (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetNextInterface  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetNextInterface
	#define EXT_IecVarAccGetNextInterface
	#define GET_IecVarAccGetNextInterface(fl)  CAL_CMGETAPI( "IecVarAccGetNextInterface" ) 
	#define CAL_IecVarAccGetNextInterface pICmpIecVarAccess->IIecVarAccGetNextInterface
	#define CHK_IecVarAccGetNextInterface (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetNextInterface  CAL_CMEXPAPI( "IecVarAccGetNextInterface" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetNextInterface  PFIECVARACCGETNEXTINTERFACE pfIecVarAccGetNextInterface;
	#define EXT_IecVarAccGetNextInterface  extern PFIECVARACCGETNEXTINTERFACE pfIecVarAccGetNextInterface;
	#define GET_IecVarAccGetNextInterface(fl)  s_pfCMGetAPI2( "IecVarAccGetNextInterface", (RTS_VOID_FCTPTR *)&pfIecVarAccGetNextInterface, (fl), 0, 0)
	#define CAL_IecVarAccGetNextInterface  pfIecVarAccGetNextInterface
	#define CHK_IecVarAccGetNextInterface  (pfIecVarAccGetNextInterface != NULL)
	#define EXP_IecVarAccGetNextInterface  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNextInterface", (RTS_UINTPTR)IecVarAccGetNextInterface, 0, 0) 
#endif




/**
 * <description>Get the application name of the specified interface</description>
 * <param name="hInterface" type="IN">Handle to the interface</param>
 * <param name="pszApplicationName" type="OUT">Pointer to return application name</param>
 * <param name="nMaxLen" type="IN">Maximum string length</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL IecVarAccGetApplicationName(RTS_HANDLE hInterface, char *pszApplicationName, int nMaxLen);
typedef RTS_RESULT (CDECL * PFIECVARACCGETAPPLICATIONNAME) (RTS_HANDLE hInterface, char *pszApplicationName, int nMaxLen);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETAPPLICATIONNAME_NOTIMPLEMENTED)
	#define USE_IecVarAccGetApplicationName
	#define EXT_IecVarAccGetApplicationName
	#define GET_IecVarAccGetApplicationName(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetApplicationName(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetApplicationName  FALSE
	#define EXP_IecVarAccGetApplicationName  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetApplicationName
	#define EXT_IecVarAccGetApplicationName
	#define GET_IecVarAccGetApplicationName(fl)  CAL_CMGETAPI( "IecVarAccGetApplicationName" ) 
	#define CAL_IecVarAccGetApplicationName  IecVarAccGetApplicationName
	#define CHK_IecVarAccGetApplicationName  TRUE
	#define EXP_IecVarAccGetApplicationName  CAL_CMEXPAPI( "IecVarAccGetApplicationName" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetApplicationName
	#define EXT_IecVarAccGetApplicationName
	#define GET_IecVarAccGetApplicationName(fl)  CAL_CMGETAPI( "IecVarAccGetApplicationName" ) 
	#define CAL_IecVarAccGetApplicationName  IecVarAccGetApplicationName
	#define CHK_IecVarAccGetApplicationName  TRUE
	#define EXP_IecVarAccGetApplicationName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetApplicationName", (RTS_UINTPTR)IecVarAccGetApplicationName, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetApplicationName
	#define EXT_CmpIecVarAccessIecVarAccGetApplicationName
	#define GET_CmpIecVarAccessIecVarAccGetApplicationName  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetApplicationName pICmpIecVarAccess->IIecVarAccGetApplicationName
	#define CHK_CmpIecVarAccessIecVarAccGetApplicationName (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetApplicationName  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetApplicationName
	#define EXT_IecVarAccGetApplicationName
	#define GET_IecVarAccGetApplicationName(fl)  CAL_CMGETAPI( "IecVarAccGetApplicationName" ) 
	#define CAL_IecVarAccGetApplicationName pICmpIecVarAccess->IIecVarAccGetApplicationName
	#define CHK_IecVarAccGetApplicationName (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetApplicationName  CAL_CMEXPAPI( "IecVarAccGetApplicationName" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetApplicationName  PFIECVARACCGETAPPLICATIONNAME pfIecVarAccGetApplicationName;
	#define EXT_IecVarAccGetApplicationName  extern PFIECVARACCGETAPPLICATIONNAME pfIecVarAccGetApplicationName;
	#define GET_IecVarAccGetApplicationName(fl)  s_pfCMGetAPI2( "IecVarAccGetApplicationName", (RTS_VOID_FCTPTR *)&pfIecVarAccGetApplicationName, (fl), 0, 0)
	#define CAL_IecVarAccGetApplicationName  pfIecVarAccGetApplicationName
	#define CHK_IecVarAccGetApplicationName  (pfIecVarAccGetApplicationName != NULL)
	#define EXP_IecVarAccGetApplicationName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetApplicationName", (RTS_UINTPTR)IecVarAccGetApplicationName, 0, 0) 
#endif





/**
 * <description>Create variable list. A variable list can be used to add variables and to access and handle all these
 *	variables with only one handle.</description>
 * <param name="ulChannelId" type="IN">Online channelid to attach the variable list to a valid online connection of the channel server</param>
 * <param name="ulFlags" type="IN">Optional flags for the variable list, see category (Varlist flags)</param>
 * <param name="ulUpdateRateMs" type="IN">Requested update rate for the complete variable list in milliseconds</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the variable list (called hVarList)</result>
 */
RTS_HANDLE CDECL IecVarAccCreateVarList(RTS_UI32 ulChannelId, RTS_UI32 ulFlags, RTS_UI32 ulUpdateRateMs, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECVARACCCREATEVARLIST) (RTS_UI32 ulChannelId, RTS_UI32 ulFlags, RTS_UI32 ulUpdateRateMs, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCCREATEVARLIST_NOTIMPLEMENTED)
	#define USE_IecVarAccCreateVarList
	#define EXT_IecVarAccCreateVarList
	#define GET_IecVarAccCreateVarList(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccCreateVarList(p0,p1,p2,p3)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecVarAccCreateVarList  FALSE
	#define EXP_IecVarAccCreateVarList  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccCreateVarList
	#define EXT_IecVarAccCreateVarList
	#define GET_IecVarAccCreateVarList(fl)  CAL_CMGETAPI( "IecVarAccCreateVarList" ) 
	#define CAL_IecVarAccCreateVarList  IecVarAccCreateVarList
	#define CHK_IecVarAccCreateVarList  TRUE
	#define EXP_IecVarAccCreateVarList  CAL_CMEXPAPI( "IecVarAccCreateVarList" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccCreateVarList
	#define EXT_IecVarAccCreateVarList
	#define GET_IecVarAccCreateVarList(fl)  CAL_CMGETAPI( "IecVarAccCreateVarList" ) 
	#define CAL_IecVarAccCreateVarList  IecVarAccCreateVarList
	#define CHK_IecVarAccCreateVarList  TRUE
	#define EXP_IecVarAccCreateVarList  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccCreateVarList", (RTS_UINTPTR)IecVarAccCreateVarList, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccCreateVarList
	#define EXT_CmpIecVarAccessIecVarAccCreateVarList
	#define GET_CmpIecVarAccessIecVarAccCreateVarList  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccCreateVarList pICmpIecVarAccess->IIecVarAccCreateVarList
	#define CHK_CmpIecVarAccessIecVarAccCreateVarList (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccCreateVarList  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccCreateVarList
	#define EXT_IecVarAccCreateVarList
	#define GET_IecVarAccCreateVarList(fl)  CAL_CMGETAPI( "IecVarAccCreateVarList" ) 
	#define CAL_IecVarAccCreateVarList pICmpIecVarAccess->IIecVarAccCreateVarList
	#define CHK_IecVarAccCreateVarList (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccCreateVarList  CAL_CMEXPAPI( "IecVarAccCreateVarList" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccCreateVarList  PFIECVARACCCREATEVARLIST pfIecVarAccCreateVarList;
	#define EXT_IecVarAccCreateVarList  extern PFIECVARACCCREATEVARLIST pfIecVarAccCreateVarList;
	#define GET_IecVarAccCreateVarList(fl)  s_pfCMGetAPI2( "IecVarAccCreateVarList", (RTS_VOID_FCTPTR *)&pfIecVarAccCreateVarList, (fl), 0, 0)
	#define CAL_IecVarAccCreateVarList  pfIecVarAccCreateVarList
	#define CHK_IecVarAccCreateVarList  (pfIecVarAccCreateVarList != NULL)
	#define EXP_IecVarAccCreateVarList  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccCreateVarList", (RTS_UINTPTR)IecVarAccCreateVarList, 0, 0) 
#endif




/**
 * <description>Delete the specified variable list</description>
 * <param name="hVarList" type="IN">Handle to the variable list</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL IecVarAccDeleteVarList(RTS_HANDLE hVarList);
typedef RTS_RESULT (CDECL * PFIECVARACCDELETEVARLIST) (RTS_HANDLE hVarList);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCDELETEVARLIST_NOTIMPLEMENTED)
	#define USE_IecVarAccDeleteVarList
	#define EXT_IecVarAccDeleteVarList
	#define GET_IecVarAccDeleteVarList(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccDeleteVarList(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccDeleteVarList  FALSE
	#define EXP_IecVarAccDeleteVarList  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccDeleteVarList
	#define EXT_IecVarAccDeleteVarList
	#define GET_IecVarAccDeleteVarList(fl)  CAL_CMGETAPI( "IecVarAccDeleteVarList" ) 
	#define CAL_IecVarAccDeleteVarList  IecVarAccDeleteVarList
	#define CHK_IecVarAccDeleteVarList  TRUE
	#define EXP_IecVarAccDeleteVarList  CAL_CMEXPAPI( "IecVarAccDeleteVarList" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccDeleteVarList
	#define EXT_IecVarAccDeleteVarList
	#define GET_IecVarAccDeleteVarList(fl)  CAL_CMGETAPI( "IecVarAccDeleteVarList" ) 
	#define CAL_IecVarAccDeleteVarList  IecVarAccDeleteVarList
	#define CHK_IecVarAccDeleteVarList  TRUE
	#define EXP_IecVarAccDeleteVarList  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccDeleteVarList", (RTS_UINTPTR)IecVarAccDeleteVarList, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccDeleteVarList
	#define EXT_CmpIecVarAccessIecVarAccDeleteVarList
	#define GET_CmpIecVarAccessIecVarAccDeleteVarList  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccDeleteVarList pICmpIecVarAccess->IIecVarAccDeleteVarList
	#define CHK_CmpIecVarAccessIecVarAccDeleteVarList (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccDeleteVarList  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccDeleteVarList
	#define EXT_IecVarAccDeleteVarList
	#define GET_IecVarAccDeleteVarList(fl)  CAL_CMGETAPI( "IecVarAccDeleteVarList" ) 
	#define CAL_IecVarAccDeleteVarList pICmpIecVarAccess->IIecVarAccDeleteVarList
	#define CHK_IecVarAccDeleteVarList (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccDeleteVarList  CAL_CMEXPAPI( "IecVarAccDeleteVarList" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccDeleteVarList  PFIECVARACCDELETEVARLIST pfIecVarAccDeleteVarList;
	#define EXT_IecVarAccDeleteVarList  extern PFIECVARACCDELETEVARLIST pfIecVarAccDeleteVarList;
	#define GET_IecVarAccDeleteVarList(fl)  s_pfCMGetAPI2( "IecVarAccDeleteVarList", (RTS_VOID_FCTPTR *)&pfIecVarAccDeleteVarList, (fl), 0, 0)
	#define CAL_IecVarAccDeleteVarList  pfIecVarAccDeleteVarList
	#define CHK_IecVarAccDeleteVarList  (pfIecVarAccDeleteVarList != NULL)
	#define EXP_IecVarAccDeleteVarList  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccDeleteVarList", (RTS_UINTPTR)IecVarAccDeleteVarList, 0, 0) 
#endif




/**
 * <description>Delete all variable lists that are assigned to the specified sessionid</description>
 * <param name="ulChannelId" type="IN">Online channelid of a valid online connection of the channel server</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL IecVarAccDeleteVarLists(RTS_UI32 ulChannelId);
typedef RTS_RESULT (CDECL * PFIECVARACCDELETEVARLISTS) (RTS_UI32 ulChannelId);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCDELETEVARLISTS_NOTIMPLEMENTED)
	#define USE_IecVarAccDeleteVarLists
	#define EXT_IecVarAccDeleteVarLists
	#define GET_IecVarAccDeleteVarLists(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccDeleteVarLists(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccDeleteVarLists  FALSE
	#define EXP_IecVarAccDeleteVarLists  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccDeleteVarLists
	#define EXT_IecVarAccDeleteVarLists
	#define GET_IecVarAccDeleteVarLists(fl)  CAL_CMGETAPI( "IecVarAccDeleteVarLists" ) 
	#define CAL_IecVarAccDeleteVarLists  IecVarAccDeleteVarLists
	#define CHK_IecVarAccDeleteVarLists  TRUE
	#define EXP_IecVarAccDeleteVarLists  CAL_CMEXPAPI( "IecVarAccDeleteVarLists" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccDeleteVarLists
	#define EXT_IecVarAccDeleteVarLists
	#define GET_IecVarAccDeleteVarLists(fl)  CAL_CMGETAPI( "IecVarAccDeleteVarLists" ) 
	#define CAL_IecVarAccDeleteVarLists  IecVarAccDeleteVarLists
	#define CHK_IecVarAccDeleteVarLists  TRUE
	#define EXP_IecVarAccDeleteVarLists  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccDeleteVarLists", (RTS_UINTPTR)IecVarAccDeleteVarLists, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccDeleteVarLists
	#define EXT_CmpIecVarAccessIecVarAccDeleteVarLists
	#define GET_CmpIecVarAccessIecVarAccDeleteVarLists  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccDeleteVarLists pICmpIecVarAccess->IIecVarAccDeleteVarLists
	#define CHK_CmpIecVarAccessIecVarAccDeleteVarLists (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccDeleteVarLists  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccDeleteVarLists
	#define EXT_IecVarAccDeleteVarLists
	#define GET_IecVarAccDeleteVarLists(fl)  CAL_CMGETAPI( "IecVarAccDeleteVarLists" ) 
	#define CAL_IecVarAccDeleteVarLists pICmpIecVarAccess->IIecVarAccDeleteVarLists
	#define CHK_IecVarAccDeleteVarLists (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccDeleteVarLists  CAL_CMEXPAPI( "IecVarAccDeleteVarLists" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccDeleteVarLists  PFIECVARACCDELETEVARLISTS pfIecVarAccDeleteVarLists;
	#define EXT_IecVarAccDeleteVarLists  extern PFIECVARACCDELETEVARLISTS pfIecVarAccDeleteVarLists;
	#define GET_IecVarAccDeleteVarLists(fl)  s_pfCMGetAPI2( "IecVarAccDeleteVarLists", (RTS_VOID_FCTPTR *)&pfIecVarAccDeleteVarLists, (fl), 0, 0)
	#define CAL_IecVarAccDeleteVarLists  pfIecVarAccDeleteVarLists
	#define CHK_IecVarAccDeleteVarLists  (pfIecVarAccDeleteVarLists != NULL)
	#define EXP_IecVarAccDeleteVarLists  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccDeleteVarLists", (RTS_UINTPTR)IecVarAccDeleteVarLists, 0, 0) 
#endif




/**
 * <description>Delete all variable lists</description>
 * <result>error code</result>
 */
RTS_RESULT CDECL IecVarAccDeleteAllLists(void);
typedef RTS_RESULT (CDECL * PFIECVARACCDELETEALLLISTS) (void);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCDELETEALLLISTS_NOTIMPLEMENTED)
	#define USE_IecVarAccDeleteAllLists
	#define EXT_IecVarAccDeleteAllLists
	#define GET_IecVarAccDeleteAllLists(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccDeleteAllLists()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccDeleteAllLists  FALSE
	#define EXP_IecVarAccDeleteAllLists  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccDeleteAllLists
	#define EXT_IecVarAccDeleteAllLists
	#define GET_IecVarAccDeleteAllLists(fl)  CAL_CMGETAPI( "IecVarAccDeleteAllLists" ) 
	#define CAL_IecVarAccDeleteAllLists  IecVarAccDeleteAllLists
	#define CHK_IecVarAccDeleteAllLists  TRUE
	#define EXP_IecVarAccDeleteAllLists  CAL_CMEXPAPI( "IecVarAccDeleteAllLists" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccDeleteAllLists
	#define EXT_IecVarAccDeleteAllLists
	#define GET_IecVarAccDeleteAllLists(fl)  CAL_CMGETAPI( "IecVarAccDeleteAllLists" ) 
	#define CAL_IecVarAccDeleteAllLists  IecVarAccDeleteAllLists
	#define CHK_IecVarAccDeleteAllLists  TRUE
	#define EXP_IecVarAccDeleteAllLists  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccDeleteAllLists", (RTS_UINTPTR)IecVarAccDeleteAllLists, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccDeleteAllLists
	#define EXT_CmpIecVarAccessIecVarAccDeleteAllLists
	#define GET_CmpIecVarAccessIecVarAccDeleteAllLists  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccDeleteAllLists pICmpIecVarAccess->IIecVarAccDeleteAllLists
	#define CHK_CmpIecVarAccessIecVarAccDeleteAllLists (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccDeleteAllLists  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccDeleteAllLists
	#define EXT_IecVarAccDeleteAllLists
	#define GET_IecVarAccDeleteAllLists(fl)  CAL_CMGETAPI( "IecVarAccDeleteAllLists" ) 
	#define CAL_IecVarAccDeleteAllLists pICmpIecVarAccess->IIecVarAccDeleteAllLists
	#define CHK_IecVarAccDeleteAllLists (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccDeleteAllLists  CAL_CMEXPAPI( "IecVarAccDeleteAllLists" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccDeleteAllLists  PFIECVARACCDELETEALLLISTS pfIecVarAccDeleteAllLists;
	#define EXT_IecVarAccDeleteAllLists  extern PFIECVARACCDELETEALLLISTS pfIecVarAccDeleteAllLists;
	#define GET_IecVarAccDeleteAllLists(fl)  s_pfCMGetAPI2( "IecVarAccDeleteAllLists", (RTS_VOID_FCTPTR *)&pfIecVarAccDeleteAllLists, (fl), 0, 0)
	#define CAL_IecVarAccDeleteAllLists  pfIecVarAccDeleteAllLists
	#define CHK_IecVarAccDeleteAllLists  (pfIecVarAccDeleteAllLists != NULL)
	#define EXP_IecVarAccDeleteAllLists  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccDeleteAllLists", (RTS_UINTPTR)IecVarAccDeleteAllLists, 0, 0) 
#endif




/**
 * <description>Get the flags that are assigned to the variable list</description>
 * <param name="hVarList" type="IN">Handle to the variable list</param>
 * <param name="pulFlags" type="OUT">Pointer to get the flags</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL IecVarAccVarListGetFlags(RTS_HANDLE hVarList, RTS_UI32 *pulFlags);
typedef RTS_RESULT (CDECL * PFIECVARACCVARLISTGETFLAGS) (RTS_HANDLE hVarList, RTS_UI32 *pulFlags);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCVARLISTGETFLAGS_NOTIMPLEMENTED)
	#define USE_IecVarAccVarListGetFlags
	#define EXT_IecVarAccVarListGetFlags
	#define GET_IecVarAccVarListGetFlags(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccVarListGetFlags(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccVarListGetFlags  FALSE
	#define EXP_IecVarAccVarListGetFlags  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccVarListGetFlags
	#define EXT_IecVarAccVarListGetFlags
	#define GET_IecVarAccVarListGetFlags(fl)  CAL_CMGETAPI( "IecVarAccVarListGetFlags" ) 
	#define CAL_IecVarAccVarListGetFlags  IecVarAccVarListGetFlags
	#define CHK_IecVarAccVarListGetFlags  TRUE
	#define EXP_IecVarAccVarListGetFlags  CAL_CMEXPAPI( "IecVarAccVarListGetFlags" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccVarListGetFlags
	#define EXT_IecVarAccVarListGetFlags
	#define GET_IecVarAccVarListGetFlags(fl)  CAL_CMGETAPI( "IecVarAccVarListGetFlags" ) 
	#define CAL_IecVarAccVarListGetFlags  IecVarAccVarListGetFlags
	#define CHK_IecVarAccVarListGetFlags  TRUE
	#define EXP_IecVarAccVarListGetFlags  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccVarListGetFlags", (RTS_UINTPTR)IecVarAccVarListGetFlags, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccVarListGetFlags
	#define EXT_CmpIecVarAccessIecVarAccVarListGetFlags
	#define GET_CmpIecVarAccessIecVarAccVarListGetFlags  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccVarListGetFlags pICmpIecVarAccess->IIecVarAccVarListGetFlags
	#define CHK_CmpIecVarAccessIecVarAccVarListGetFlags (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccVarListGetFlags  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccVarListGetFlags
	#define EXT_IecVarAccVarListGetFlags
	#define GET_IecVarAccVarListGetFlags(fl)  CAL_CMGETAPI( "IecVarAccVarListGetFlags" ) 
	#define CAL_IecVarAccVarListGetFlags pICmpIecVarAccess->IIecVarAccVarListGetFlags
	#define CHK_IecVarAccVarListGetFlags (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccVarListGetFlags  CAL_CMEXPAPI( "IecVarAccVarListGetFlags" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccVarListGetFlags  PFIECVARACCVARLISTGETFLAGS pfIecVarAccVarListGetFlags;
	#define EXT_IecVarAccVarListGetFlags  extern PFIECVARACCVARLISTGETFLAGS pfIecVarAccVarListGetFlags;
	#define GET_IecVarAccVarListGetFlags(fl)  s_pfCMGetAPI2( "IecVarAccVarListGetFlags", (RTS_VOID_FCTPTR *)&pfIecVarAccVarListGetFlags, (fl), 0, 0)
	#define CAL_IecVarAccVarListGetFlags  pfIecVarAccVarListGetFlags
	#define CHK_IecVarAccVarListGetFlags  (pfIecVarAccVarListGetFlags != NULL)
	#define EXP_IecVarAccVarListGetFlags  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccVarListGetFlags", (RTS_UINTPTR)IecVarAccVarListGetFlags, 0, 0) 
#endif




/**
 * <description>Append variable to the variable list</description>
 * <param name="hVarList" type="IN">Handle to the variable list</param>
 * <param name="pszVar" type="IN">Pointer to the variable name to add to the variable list</param>
 * <param name="ulSize" type="IN">Requested size to read. 0xFFFFFFFF: Use real variable size</param>
 * <param name="hClientHandle" type="IN">Private handle of the client. For client internal use only</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the appended variable (called hVar)</result>
 */
RTS_HANDLE CDECL IecVarAccAppendVar(RTS_HANDLE hVarList, char *pszVar, RTS_SIZE ulSize, RTS_UI32 hClientHandle, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECVARACCAPPENDVAR) (RTS_HANDLE hVarList, char *pszVar, RTS_SIZE ulSize, RTS_UI32 hClientHandle, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCAPPENDVAR_NOTIMPLEMENTED)
	#define USE_IecVarAccAppendVar
	#define EXT_IecVarAccAppendVar
	#define GET_IecVarAccAppendVar(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccAppendVar(p0,p1,p2,p3,p4)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecVarAccAppendVar  FALSE
	#define EXP_IecVarAccAppendVar  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccAppendVar
	#define EXT_IecVarAccAppendVar
	#define GET_IecVarAccAppendVar(fl)  CAL_CMGETAPI( "IecVarAccAppendVar" ) 
	#define CAL_IecVarAccAppendVar  IecVarAccAppendVar
	#define CHK_IecVarAccAppendVar  TRUE
	#define EXP_IecVarAccAppendVar  CAL_CMEXPAPI( "IecVarAccAppendVar" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccAppendVar
	#define EXT_IecVarAccAppendVar
	#define GET_IecVarAccAppendVar(fl)  CAL_CMGETAPI( "IecVarAccAppendVar" ) 
	#define CAL_IecVarAccAppendVar  IecVarAccAppendVar
	#define CHK_IecVarAccAppendVar  TRUE
	#define EXP_IecVarAccAppendVar  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccAppendVar", (RTS_UINTPTR)IecVarAccAppendVar, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccAppendVar
	#define EXT_CmpIecVarAccessIecVarAccAppendVar
	#define GET_CmpIecVarAccessIecVarAccAppendVar  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccAppendVar pICmpIecVarAccess->IIecVarAccAppendVar
	#define CHK_CmpIecVarAccessIecVarAccAppendVar (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccAppendVar  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccAppendVar
	#define EXT_IecVarAccAppendVar
	#define GET_IecVarAccAppendVar(fl)  CAL_CMGETAPI( "IecVarAccAppendVar" ) 
	#define CAL_IecVarAccAppendVar pICmpIecVarAccess->IIecVarAccAppendVar
	#define CHK_IecVarAccAppendVar (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccAppendVar  CAL_CMEXPAPI( "IecVarAccAppendVar" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccAppendVar  PFIECVARACCAPPENDVAR pfIecVarAccAppendVar;
	#define EXT_IecVarAccAppendVar  extern PFIECVARACCAPPENDVAR pfIecVarAccAppendVar;
	#define GET_IecVarAccAppendVar(fl)  s_pfCMGetAPI2( "IecVarAccAppendVar", (RTS_VOID_FCTPTR *)&pfIecVarAccAppendVar, (fl), 0, 0)
	#define CAL_IecVarAccAppendVar  pfIecVarAccAppendVar
	#define CHK_IecVarAccAppendVar  (pfIecVarAccAppendVar != NULL)
	#define EXP_IecVarAccAppendVar  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccAppendVar", (RTS_UINTPTR)IecVarAccAppendVar, 0, 0) 
#endif




/**
 * <description>Remove a variable from the specified variable list</description>
 * <param name="hVarList" type="IN">Handle to the variable list</param>
 * <param name="hVar" type="IN">Handle to the variable</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL IecVarAccRemoveVar(RTS_HANDLE hVarList, RTS_HANDLE hVar);
typedef RTS_RESULT (CDECL * PFIECVARACCREMOVEVAR) (RTS_HANDLE hVarList, RTS_HANDLE hVar);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCREMOVEVAR_NOTIMPLEMENTED)
	#define USE_IecVarAccRemoveVar
	#define EXT_IecVarAccRemoveVar
	#define GET_IecVarAccRemoveVar(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccRemoveVar(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccRemoveVar  FALSE
	#define EXP_IecVarAccRemoveVar  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccRemoveVar
	#define EXT_IecVarAccRemoveVar
	#define GET_IecVarAccRemoveVar(fl)  CAL_CMGETAPI( "IecVarAccRemoveVar" ) 
	#define CAL_IecVarAccRemoveVar  IecVarAccRemoveVar
	#define CHK_IecVarAccRemoveVar  TRUE
	#define EXP_IecVarAccRemoveVar  CAL_CMEXPAPI( "IecVarAccRemoveVar" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccRemoveVar
	#define EXT_IecVarAccRemoveVar
	#define GET_IecVarAccRemoveVar(fl)  CAL_CMGETAPI( "IecVarAccRemoveVar" ) 
	#define CAL_IecVarAccRemoveVar  IecVarAccRemoveVar
	#define CHK_IecVarAccRemoveVar  TRUE
	#define EXP_IecVarAccRemoveVar  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccRemoveVar", (RTS_UINTPTR)IecVarAccRemoveVar, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccRemoveVar
	#define EXT_CmpIecVarAccessIecVarAccRemoveVar
	#define GET_CmpIecVarAccessIecVarAccRemoveVar  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccRemoveVar pICmpIecVarAccess->IIecVarAccRemoveVar
	#define CHK_CmpIecVarAccessIecVarAccRemoveVar (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccRemoveVar  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccRemoveVar
	#define EXT_IecVarAccRemoveVar
	#define GET_IecVarAccRemoveVar(fl)  CAL_CMGETAPI( "IecVarAccRemoveVar" ) 
	#define CAL_IecVarAccRemoveVar pICmpIecVarAccess->IIecVarAccRemoveVar
	#define CHK_IecVarAccRemoveVar (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccRemoveVar  CAL_CMEXPAPI( "IecVarAccRemoveVar" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccRemoveVar  PFIECVARACCREMOVEVAR pfIecVarAccRemoveVar;
	#define EXT_IecVarAccRemoveVar  extern PFIECVARACCREMOVEVAR pfIecVarAccRemoveVar;
	#define GET_IecVarAccRemoveVar(fl)  s_pfCMGetAPI2( "IecVarAccRemoveVar", (RTS_VOID_FCTPTR *)&pfIecVarAccRemoveVar, (fl), 0, 0)
	#define CAL_IecVarAccRemoveVar  pfIecVarAccRemoveVar
	#define CHK_IecVarAccRemoveVar  (pfIecVarAccRemoveVar != NULL)
	#define EXP_IecVarAccRemoveVar  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccRemoveVar", (RTS_UINTPTR)IecVarAccRemoveVar, 0, 0) 
#endif




/**
 * <description>Get the first variable of the specified variable list</description>
 * <param name="hVarList" type="IN">Handle to the variable list</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the first variable in the variable list (called hVar)</result>
 */
RTS_HANDLE CDECL IecVarAccGetFirstVar(RTS_HANDLE hVarList, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECVARACCGETFIRSTVAR) (RTS_HANDLE hVarList, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETFIRSTVAR_NOTIMPLEMENTED)
	#define USE_IecVarAccGetFirstVar
	#define EXT_IecVarAccGetFirstVar
	#define GET_IecVarAccGetFirstVar(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetFirstVar(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecVarAccGetFirstVar  FALSE
	#define EXP_IecVarAccGetFirstVar  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetFirstVar
	#define EXT_IecVarAccGetFirstVar
	#define GET_IecVarAccGetFirstVar(fl)  CAL_CMGETAPI( "IecVarAccGetFirstVar" ) 
	#define CAL_IecVarAccGetFirstVar  IecVarAccGetFirstVar
	#define CHK_IecVarAccGetFirstVar  TRUE
	#define EXP_IecVarAccGetFirstVar  CAL_CMEXPAPI( "IecVarAccGetFirstVar" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetFirstVar
	#define EXT_IecVarAccGetFirstVar
	#define GET_IecVarAccGetFirstVar(fl)  CAL_CMGETAPI( "IecVarAccGetFirstVar" ) 
	#define CAL_IecVarAccGetFirstVar  IecVarAccGetFirstVar
	#define CHK_IecVarAccGetFirstVar  TRUE
	#define EXP_IecVarAccGetFirstVar  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetFirstVar", (RTS_UINTPTR)IecVarAccGetFirstVar, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetFirstVar
	#define EXT_CmpIecVarAccessIecVarAccGetFirstVar
	#define GET_CmpIecVarAccessIecVarAccGetFirstVar  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetFirstVar pICmpIecVarAccess->IIecVarAccGetFirstVar
	#define CHK_CmpIecVarAccessIecVarAccGetFirstVar (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetFirstVar  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetFirstVar
	#define EXT_IecVarAccGetFirstVar
	#define GET_IecVarAccGetFirstVar(fl)  CAL_CMGETAPI( "IecVarAccGetFirstVar" ) 
	#define CAL_IecVarAccGetFirstVar pICmpIecVarAccess->IIecVarAccGetFirstVar
	#define CHK_IecVarAccGetFirstVar (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetFirstVar  CAL_CMEXPAPI( "IecVarAccGetFirstVar" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetFirstVar  PFIECVARACCGETFIRSTVAR pfIecVarAccGetFirstVar;
	#define EXT_IecVarAccGetFirstVar  extern PFIECVARACCGETFIRSTVAR pfIecVarAccGetFirstVar;
	#define GET_IecVarAccGetFirstVar(fl)  s_pfCMGetAPI2( "IecVarAccGetFirstVar", (RTS_VOID_FCTPTR *)&pfIecVarAccGetFirstVar, (fl), 0, 0)
	#define CAL_IecVarAccGetFirstVar  pfIecVarAccGetFirstVar
	#define CHK_IecVarAccGetFirstVar  (pfIecVarAccGetFirstVar != NULL)
	#define EXP_IecVarAccGetFirstVar  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetFirstVar", (RTS_UINTPTR)IecVarAccGetFirstVar, 0, 0) 
#endif




/**
 * <description>Get the next variable of the specified variable list</description>
 * <param name="hVarList" type="IN">Handle to the variable list</param>
 * <param name="hPrevVar" type="IN">Handle to the previous variable</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the next variable in the variable list (called hVar)</result>
 */
RTS_HANDLE CDECL IecVarAccGetNextVar(RTS_HANDLE hVarList, RTS_HANDLE hPrevVar, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECVARACCGETNEXTVAR) (RTS_HANDLE hVarList, RTS_HANDLE hPrevVar, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNEXTVAR_NOTIMPLEMENTED)
	#define USE_IecVarAccGetNextVar
	#define EXT_IecVarAccGetNextVar
	#define GET_IecVarAccGetNextVar(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetNextVar(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecVarAccGetNextVar  FALSE
	#define EXP_IecVarAccGetNextVar  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetNextVar
	#define EXT_IecVarAccGetNextVar
	#define GET_IecVarAccGetNextVar(fl)  CAL_CMGETAPI( "IecVarAccGetNextVar" ) 
	#define CAL_IecVarAccGetNextVar  IecVarAccGetNextVar
	#define CHK_IecVarAccGetNextVar  TRUE
	#define EXP_IecVarAccGetNextVar  CAL_CMEXPAPI( "IecVarAccGetNextVar" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetNextVar
	#define EXT_IecVarAccGetNextVar
	#define GET_IecVarAccGetNextVar(fl)  CAL_CMGETAPI( "IecVarAccGetNextVar" ) 
	#define CAL_IecVarAccGetNextVar  IecVarAccGetNextVar
	#define CHK_IecVarAccGetNextVar  TRUE
	#define EXP_IecVarAccGetNextVar  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNextVar", (RTS_UINTPTR)IecVarAccGetNextVar, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetNextVar
	#define EXT_CmpIecVarAccessIecVarAccGetNextVar
	#define GET_CmpIecVarAccessIecVarAccGetNextVar  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetNextVar pICmpIecVarAccess->IIecVarAccGetNextVar
	#define CHK_CmpIecVarAccessIecVarAccGetNextVar (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetNextVar  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetNextVar
	#define EXT_IecVarAccGetNextVar
	#define GET_IecVarAccGetNextVar(fl)  CAL_CMGETAPI( "IecVarAccGetNextVar" ) 
	#define CAL_IecVarAccGetNextVar pICmpIecVarAccess->IIecVarAccGetNextVar
	#define CHK_IecVarAccGetNextVar (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetNextVar  CAL_CMEXPAPI( "IecVarAccGetNextVar" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetNextVar  PFIECVARACCGETNEXTVAR pfIecVarAccGetNextVar;
	#define EXT_IecVarAccGetNextVar  extern PFIECVARACCGETNEXTVAR pfIecVarAccGetNextVar;
	#define GET_IecVarAccGetNextVar(fl)  s_pfCMGetAPI2( "IecVarAccGetNextVar", (RTS_VOID_FCTPTR *)&pfIecVarAccGetNextVar, (fl), 0, 0)
	#define CAL_IecVarAccGetNextVar  pfIecVarAccGetNextVar
	#define CHK_IecVarAccGetNextVar  (pfIecVarAccGetNextVar != NULL)
	#define EXP_IecVarAccGetNextVar  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNextVar", (RTS_UINTPTR)IecVarAccGetNextVar, 0, 0) 
#endif





/**
 * <description>Invalidate variable to disable access</description>
 * <param name="hVarList" type="IN">Handle to the variable list</param>
 * <param name="hVar" type="IN">Handle to the variable</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL IecVarAccInvalidateVar(RTS_HANDLE hVarList, RTS_HANDLE hVar);
typedef RTS_RESULT (CDECL * PFIECVARACCINVALIDATEVAR) (RTS_HANDLE hVarList, RTS_HANDLE hVar);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCINVALIDATEVAR_NOTIMPLEMENTED)
	#define USE_IecVarAccInvalidateVar
	#define EXT_IecVarAccInvalidateVar
	#define GET_IecVarAccInvalidateVar(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccInvalidateVar(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccInvalidateVar  FALSE
	#define EXP_IecVarAccInvalidateVar  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccInvalidateVar
	#define EXT_IecVarAccInvalidateVar
	#define GET_IecVarAccInvalidateVar(fl)  CAL_CMGETAPI( "IecVarAccInvalidateVar" ) 
	#define CAL_IecVarAccInvalidateVar  IecVarAccInvalidateVar
	#define CHK_IecVarAccInvalidateVar  TRUE
	#define EXP_IecVarAccInvalidateVar  CAL_CMEXPAPI( "IecVarAccInvalidateVar" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccInvalidateVar
	#define EXT_IecVarAccInvalidateVar
	#define GET_IecVarAccInvalidateVar(fl)  CAL_CMGETAPI( "IecVarAccInvalidateVar" ) 
	#define CAL_IecVarAccInvalidateVar  IecVarAccInvalidateVar
	#define CHK_IecVarAccInvalidateVar  TRUE
	#define EXP_IecVarAccInvalidateVar  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccInvalidateVar", (RTS_UINTPTR)IecVarAccInvalidateVar, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccInvalidateVar
	#define EXT_CmpIecVarAccessIecVarAccInvalidateVar
	#define GET_CmpIecVarAccessIecVarAccInvalidateVar  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccInvalidateVar pICmpIecVarAccess->IIecVarAccInvalidateVar
	#define CHK_CmpIecVarAccessIecVarAccInvalidateVar (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccInvalidateVar  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccInvalidateVar
	#define EXT_IecVarAccInvalidateVar
	#define GET_IecVarAccInvalidateVar(fl)  CAL_CMGETAPI( "IecVarAccInvalidateVar" ) 
	#define CAL_IecVarAccInvalidateVar pICmpIecVarAccess->IIecVarAccInvalidateVar
	#define CHK_IecVarAccInvalidateVar (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccInvalidateVar  CAL_CMEXPAPI( "IecVarAccInvalidateVar" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccInvalidateVar  PFIECVARACCINVALIDATEVAR pfIecVarAccInvalidateVar;
	#define EXT_IecVarAccInvalidateVar  extern PFIECVARACCINVALIDATEVAR pfIecVarAccInvalidateVar;
	#define GET_IecVarAccInvalidateVar(fl)  s_pfCMGetAPI2( "IecVarAccInvalidateVar", (RTS_VOID_FCTPTR *)&pfIecVarAccInvalidateVar, (fl), 0, 0)
	#define CAL_IecVarAccInvalidateVar  pfIecVarAccInvalidateVar
	#define CHK_IecVarAccInvalidateVar  (pfIecVarAccInvalidateVar != NULL)
	#define EXP_IecVarAccInvalidateVar  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccInvalidateVar", (RTS_UINTPTR)IecVarAccInvalidateVar, 0, 0) 
#endif




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
RTS_SIZE CDECL IecVarAccReadVar(RTS_HANDLE hVar, void *pData, RTS_SIZE ulLen, RTS_UI32 *pulQuality, int varFlags, RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFIECVARACCREADVAR) (RTS_HANDLE hVar, void *pData, RTS_SIZE ulLen, RTS_UI32 *pulQuality, int varFlags, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCREADVAR_NOTIMPLEMENTED)
	#define USE_IecVarAccReadVar
	#define EXT_IecVarAccReadVar
	#define GET_IecVarAccReadVar(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccReadVar(p0,p1,p2,p3,p4,p5)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccReadVar  FALSE
	#define EXP_IecVarAccReadVar  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccReadVar
	#define EXT_IecVarAccReadVar
	#define GET_IecVarAccReadVar(fl)  CAL_CMGETAPI( "IecVarAccReadVar" ) 
	#define CAL_IecVarAccReadVar  IecVarAccReadVar
	#define CHK_IecVarAccReadVar  TRUE
	#define EXP_IecVarAccReadVar  CAL_CMEXPAPI( "IecVarAccReadVar" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccReadVar
	#define EXT_IecVarAccReadVar
	#define GET_IecVarAccReadVar(fl)  CAL_CMGETAPI( "IecVarAccReadVar" ) 
	#define CAL_IecVarAccReadVar  IecVarAccReadVar
	#define CHK_IecVarAccReadVar  TRUE
	#define EXP_IecVarAccReadVar  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccReadVar", (RTS_UINTPTR)IecVarAccReadVar, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccReadVar
	#define EXT_CmpIecVarAccessIecVarAccReadVar
	#define GET_CmpIecVarAccessIecVarAccReadVar  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccReadVar pICmpIecVarAccess->IIecVarAccReadVar
	#define CHK_CmpIecVarAccessIecVarAccReadVar (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccReadVar  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccReadVar
	#define EXT_IecVarAccReadVar
	#define GET_IecVarAccReadVar(fl)  CAL_CMGETAPI( "IecVarAccReadVar" ) 
	#define CAL_IecVarAccReadVar pICmpIecVarAccess->IIecVarAccReadVar
	#define CHK_IecVarAccReadVar (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccReadVar  CAL_CMEXPAPI( "IecVarAccReadVar" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccReadVar  PFIECVARACCREADVAR pfIecVarAccReadVar;
	#define EXT_IecVarAccReadVar  extern PFIECVARACCREADVAR pfIecVarAccReadVar;
	#define GET_IecVarAccReadVar(fl)  s_pfCMGetAPI2( "IecVarAccReadVar", (RTS_VOID_FCTPTR *)&pfIecVarAccReadVar, (fl), 0, 0)
	#define CAL_IecVarAccReadVar  pfIecVarAccReadVar
	#define CHK_IecVarAccReadVar  (pfIecVarAccReadVar != NULL)
	#define EXP_IecVarAccReadVar  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccReadVar", (RTS_UINTPTR)IecVarAccReadVar, 0, 0) 
#endif




/**
 * <description>Write value to a single specified variable</description>
 * <param name="hVar" type="IN">Handle to the variable</param>
 * <param name="pData" type="IN">Pointer to write value</param>
 * <param name="ulLen" type="IN">Number of bytes to write</param>
 * <param name="varFlags" type="IN">Variable flags, see category "Varlist flags"for details</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of bytes written</result>
 */
RTS_SIZE CDECL IecVarAccWriteVar(RTS_HANDLE hVar, void *pData, RTS_SIZE ulLen, int varFlags, RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFIECVARACCWRITEVAR) (RTS_HANDLE hVar, void *pData, RTS_SIZE ulLen, int varFlags, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCWRITEVAR_NOTIMPLEMENTED)
	#define USE_IecVarAccWriteVar
	#define EXT_IecVarAccWriteVar
	#define GET_IecVarAccWriteVar(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccWriteVar(p0,p1,p2,p3,p4)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccWriteVar  FALSE
	#define EXP_IecVarAccWriteVar  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccWriteVar
	#define EXT_IecVarAccWriteVar
	#define GET_IecVarAccWriteVar(fl)  CAL_CMGETAPI( "IecVarAccWriteVar" ) 
	#define CAL_IecVarAccWriteVar  IecVarAccWriteVar
	#define CHK_IecVarAccWriteVar  TRUE
	#define EXP_IecVarAccWriteVar  CAL_CMEXPAPI( "IecVarAccWriteVar" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccWriteVar
	#define EXT_IecVarAccWriteVar
	#define GET_IecVarAccWriteVar(fl)  CAL_CMGETAPI( "IecVarAccWriteVar" ) 
	#define CAL_IecVarAccWriteVar  IecVarAccWriteVar
	#define CHK_IecVarAccWriteVar  TRUE
	#define EXP_IecVarAccWriteVar  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccWriteVar", (RTS_UINTPTR)IecVarAccWriteVar, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccWriteVar
	#define EXT_CmpIecVarAccessIecVarAccWriteVar
	#define GET_CmpIecVarAccessIecVarAccWriteVar  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccWriteVar pICmpIecVarAccess->IIecVarAccWriteVar
	#define CHK_CmpIecVarAccessIecVarAccWriteVar (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccWriteVar  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccWriteVar
	#define EXT_IecVarAccWriteVar
	#define GET_IecVarAccWriteVar(fl)  CAL_CMGETAPI( "IecVarAccWriteVar" ) 
	#define CAL_IecVarAccWriteVar pICmpIecVarAccess->IIecVarAccWriteVar
	#define CHK_IecVarAccWriteVar (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccWriteVar  CAL_CMEXPAPI( "IecVarAccWriteVar" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccWriteVar  PFIECVARACCWRITEVAR pfIecVarAccWriteVar;
	#define EXT_IecVarAccWriteVar  extern PFIECVARACCWRITEVAR pfIecVarAccWriteVar;
	#define GET_IecVarAccWriteVar(fl)  s_pfCMGetAPI2( "IecVarAccWriteVar", (RTS_VOID_FCTPTR *)&pfIecVarAccWriteVar, (fl), 0, 0)
	#define CAL_IecVarAccWriteVar  pfIecVarAccWriteVar
	#define CHK_IecVarAccWriteVar  (pfIecVarAccWriteVar != NULL)
	#define EXP_IecVarAccWriteVar  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccWriteVar", (RTS_UINTPTR)IecVarAccWriteVar, 0, 0) 
#endif




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
RTS_SIZE CDECL IecVarAccWriteVar2(RTS_HANDLE hVar, void *pData, RTS_SIZE ulLen, int varFlags, RTS_UI32 ulSessionId, RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFIECVARACCWRITEVAR2) (RTS_HANDLE hVar, void *pData, RTS_SIZE ulLen, int varFlags, RTS_UI32 ulSessionId, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCWRITEVAR2_NOTIMPLEMENTED)
	#define USE_IecVarAccWriteVar2
	#define EXT_IecVarAccWriteVar2
	#define GET_IecVarAccWriteVar2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccWriteVar2(p0,p1,p2,p3,p4,p5)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccWriteVar2  FALSE
	#define EXP_IecVarAccWriteVar2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccWriteVar2
	#define EXT_IecVarAccWriteVar2
	#define GET_IecVarAccWriteVar2(fl)  CAL_CMGETAPI( "IecVarAccWriteVar2" ) 
	#define CAL_IecVarAccWriteVar2  IecVarAccWriteVar2
	#define CHK_IecVarAccWriteVar2  TRUE
	#define EXP_IecVarAccWriteVar2  CAL_CMEXPAPI( "IecVarAccWriteVar2" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccWriteVar2
	#define EXT_IecVarAccWriteVar2
	#define GET_IecVarAccWriteVar2(fl)  CAL_CMGETAPI( "IecVarAccWriteVar2" ) 
	#define CAL_IecVarAccWriteVar2  IecVarAccWriteVar2
	#define CHK_IecVarAccWriteVar2  TRUE
	#define EXP_IecVarAccWriteVar2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccWriteVar2", (RTS_UINTPTR)IecVarAccWriteVar2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccWriteVar2
	#define EXT_CmpIecVarAccessIecVarAccWriteVar2
	#define GET_CmpIecVarAccessIecVarAccWriteVar2  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccWriteVar2 pICmpIecVarAccess->IIecVarAccWriteVar2
	#define CHK_CmpIecVarAccessIecVarAccWriteVar2 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccWriteVar2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccWriteVar2
	#define EXT_IecVarAccWriteVar2
	#define GET_IecVarAccWriteVar2(fl)  CAL_CMGETAPI( "IecVarAccWriteVar2" ) 
	#define CAL_IecVarAccWriteVar2 pICmpIecVarAccess->IIecVarAccWriteVar2
	#define CHK_IecVarAccWriteVar2 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccWriteVar2  CAL_CMEXPAPI( "IecVarAccWriteVar2" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccWriteVar2  PFIECVARACCWRITEVAR2 pfIecVarAccWriteVar2;
	#define EXT_IecVarAccWriteVar2  extern PFIECVARACCWRITEVAR2 pfIecVarAccWriteVar2;
	#define GET_IecVarAccWriteVar2(fl)  s_pfCMGetAPI2( "IecVarAccWriteVar2", (RTS_VOID_FCTPTR *)&pfIecVarAccWriteVar2, (fl), 0, 0)
	#define CAL_IecVarAccWriteVar2  pfIecVarAccWriteVar2
	#define CHK_IecVarAccWriteVar2  (pfIecVarAccWriteVar2 != NULL)
	#define EXP_IecVarAccWriteVar2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccWriteVar2", (RTS_UINTPTR)IecVarAccWriteVar2, 0, 0) 
#endif




/* The following routines access directly the symbolic application */

/**
 * <description>Begin the variable configuration. This is used, to enter a new configuration for an optional data server!</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="bBlocking" type="IN">1=if the access to the variable configuration should be blocking for other threads, 0=no blocking</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL IecVarAccBeginVariableConfiguration(RTS_HANDLE hInterface, int bBlocking);
typedef RTS_RESULT (CDECL * PFIECVARACCBEGINVARIABLECONFIGURATION) (RTS_HANDLE hInterface, int bBlocking);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCBEGINVARIABLECONFIGURATION_NOTIMPLEMENTED)
	#define USE_IecVarAccBeginVariableConfiguration
	#define EXT_IecVarAccBeginVariableConfiguration
	#define GET_IecVarAccBeginVariableConfiguration(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccBeginVariableConfiguration(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccBeginVariableConfiguration  FALSE
	#define EXP_IecVarAccBeginVariableConfiguration  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccBeginVariableConfiguration
	#define EXT_IecVarAccBeginVariableConfiguration
	#define GET_IecVarAccBeginVariableConfiguration(fl)  CAL_CMGETAPI( "IecVarAccBeginVariableConfiguration" ) 
	#define CAL_IecVarAccBeginVariableConfiguration  IecVarAccBeginVariableConfiguration
	#define CHK_IecVarAccBeginVariableConfiguration  TRUE
	#define EXP_IecVarAccBeginVariableConfiguration  CAL_CMEXPAPI( "IecVarAccBeginVariableConfiguration" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccBeginVariableConfiguration
	#define EXT_IecVarAccBeginVariableConfiguration
	#define GET_IecVarAccBeginVariableConfiguration(fl)  CAL_CMGETAPI( "IecVarAccBeginVariableConfiguration" ) 
	#define CAL_IecVarAccBeginVariableConfiguration  IecVarAccBeginVariableConfiguration
	#define CHK_IecVarAccBeginVariableConfiguration  TRUE
	#define EXP_IecVarAccBeginVariableConfiguration  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccBeginVariableConfiguration", (RTS_UINTPTR)IecVarAccBeginVariableConfiguration, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccBeginVariableConfiguration
	#define EXT_CmpIecVarAccessIecVarAccBeginVariableConfiguration
	#define GET_CmpIecVarAccessIecVarAccBeginVariableConfiguration  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccBeginVariableConfiguration pICmpIecVarAccess->IIecVarAccBeginVariableConfiguration
	#define CHK_CmpIecVarAccessIecVarAccBeginVariableConfiguration (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccBeginVariableConfiguration  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccBeginVariableConfiguration
	#define EXT_IecVarAccBeginVariableConfiguration
	#define GET_IecVarAccBeginVariableConfiguration(fl)  CAL_CMGETAPI( "IecVarAccBeginVariableConfiguration" ) 
	#define CAL_IecVarAccBeginVariableConfiguration pICmpIecVarAccess->IIecVarAccBeginVariableConfiguration
	#define CHK_IecVarAccBeginVariableConfiguration (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccBeginVariableConfiguration  CAL_CMEXPAPI( "IecVarAccBeginVariableConfiguration" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccBeginVariableConfiguration  PFIECVARACCBEGINVARIABLECONFIGURATION pfIecVarAccBeginVariableConfiguration;
	#define EXT_IecVarAccBeginVariableConfiguration  extern PFIECVARACCBEGINVARIABLECONFIGURATION pfIecVarAccBeginVariableConfiguration;
	#define GET_IecVarAccBeginVariableConfiguration(fl)  s_pfCMGetAPI2( "IecVarAccBeginVariableConfiguration", (RTS_VOID_FCTPTR *)&pfIecVarAccBeginVariableConfiguration, (fl), 0, 0)
	#define CAL_IecVarAccBeginVariableConfiguration  pfIecVarAccBeginVariableConfiguration
	#define CHK_IecVarAccBeginVariableConfiguration  (pfIecVarAccBeginVariableConfiguration != NULL)
	#define EXP_IecVarAccBeginVariableConfiguration  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccBeginVariableConfiguration", (RTS_UINTPTR)IecVarAccBeginVariableConfiguration, 0, 0) 
#endif




/**
 * <description>Append a variable to the symbolic interface. This is used, to register a variable at an optional data server!</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the symbolic node</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL IecVarAccAppendVariable(RTS_HANDLE hInterface, RTS_HANDLE hNode);
typedef RTS_RESULT (CDECL * PFIECVARACCAPPENDVARIABLE) (RTS_HANDLE hInterface, RTS_HANDLE hNode);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCAPPENDVARIABLE_NOTIMPLEMENTED)
	#define USE_IecVarAccAppendVariable
	#define EXT_IecVarAccAppendVariable
	#define GET_IecVarAccAppendVariable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccAppendVariable(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccAppendVariable  FALSE
	#define EXP_IecVarAccAppendVariable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccAppendVariable
	#define EXT_IecVarAccAppendVariable
	#define GET_IecVarAccAppendVariable(fl)  CAL_CMGETAPI( "IecVarAccAppendVariable" ) 
	#define CAL_IecVarAccAppendVariable  IecVarAccAppendVariable
	#define CHK_IecVarAccAppendVariable  TRUE
	#define EXP_IecVarAccAppendVariable  CAL_CMEXPAPI( "IecVarAccAppendVariable" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccAppendVariable
	#define EXT_IecVarAccAppendVariable
	#define GET_IecVarAccAppendVariable(fl)  CAL_CMGETAPI( "IecVarAccAppendVariable" ) 
	#define CAL_IecVarAccAppendVariable  IecVarAccAppendVariable
	#define CHK_IecVarAccAppendVariable  TRUE
	#define EXP_IecVarAccAppendVariable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccAppendVariable", (RTS_UINTPTR)IecVarAccAppendVariable, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccAppendVariable
	#define EXT_CmpIecVarAccessIecVarAccAppendVariable
	#define GET_CmpIecVarAccessIecVarAccAppendVariable  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccAppendVariable pICmpIecVarAccess->IIecVarAccAppendVariable
	#define CHK_CmpIecVarAccessIecVarAccAppendVariable (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccAppendVariable  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccAppendVariable
	#define EXT_IecVarAccAppendVariable
	#define GET_IecVarAccAppendVariable(fl)  CAL_CMGETAPI( "IecVarAccAppendVariable" ) 
	#define CAL_IecVarAccAppendVariable pICmpIecVarAccess->IIecVarAccAppendVariable
	#define CHK_IecVarAccAppendVariable (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccAppendVariable  CAL_CMEXPAPI( "IecVarAccAppendVariable" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccAppendVariable  PFIECVARACCAPPENDVARIABLE pfIecVarAccAppendVariable;
	#define EXT_IecVarAccAppendVariable  extern PFIECVARACCAPPENDVARIABLE pfIecVarAccAppendVariable;
	#define GET_IecVarAccAppendVariable(fl)  s_pfCMGetAPI2( "IecVarAccAppendVariable", (RTS_VOID_FCTPTR *)&pfIecVarAccAppendVariable, (fl), 0, 0)
	#define CAL_IecVarAccAppendVariable  pfIecVarAccAppendVariable
	#define CHK_IecVarAccAppendVariable  (pfIecVarAccAppendVariable != NULL)
	#define EXP_IecVarAccAppendVariable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccAppendVariable", (RTS_UINTPTR)IecVarAccAppendVariable, 0, 0) 
#endif




/**
 * <description>Append a variable to the symbolic interface. This is used, to register a variable at an optional data server!</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the symbolic node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by IecVarAccGetNode3</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL IecVarAccAppendVariable3(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation);
typedef RTS_RESULT (CDECL * PFIECVARACCAPPENDVARIABLE3) (RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCAPPENDVARIABLE3_NOTIMPLEMENTED)
	#define USE_IecVarAccAppendVariable3
	#define EXT_IecVarAccAppendVariable3
	#define GET_IecVarAccAppendVariable3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccAppendVariable3(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccAppendVariable3  FALSE
	#define EXP_IecVarAccAppendVariable3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccAppendVariable3
	#define EXT_IecVarAccAppendVariable3
	#define GET_IecVarAccAppendVariable3(fl)  CAL_CMGETAPI( "IecVarAccAppendVariable3" ) 
	#define CAL_IecVarAccAppendVariable3  IecVarAccAppendVariable3
	#define CHK_IecVarAccAppendVariable3  TRUE
	#define EXP_IecVarAccAppendVariable3  CAL_CMEXPAPI( "IecVarAccAppendVariable3" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccAppendVariable3
	#define EXT_IecVarAccAppendVariable3
	#define GET_IecVarAccAppendVariable3(fl)  CAL_CMGETAPI( "IecVarAccAppendVariable3" ) 
	#define CAL_IecVarAccAppendVariable3  IecVarAccAppendVariable3
	#define CHK_IecVarAccAppendVariable3  TRUE
	#define EXP_IecVarAccAppendVariable3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccAppendVariable3", (RTS_UINTPTR)IecVarAccAppendVariable3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccAppendVariable3
	#define EXT_CmpIecVarAccessIecVarAccAppendVariable3
	#define GET_CmpIecVarAccessIecVarAccAppendVariable3  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccAppendVariable3 pICmpIecVarAccess->IIecVarAccAppendVariable3
	#define CHK_CmpIecVarAccessIecVarAccAppendVariable3 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccAppendVariable3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccAppendVariable3
	#define EXT_IecVarAccAppendVariable3
	#define GET_IecVarAccAppendVariable3(fl)  CAL_CMGETAPI( "IecVarAccAppendVariable3" ) 
	#define CAL_IecVarAccAppendVariable3 pICmpIecVarAccess->IIecVarAccAppendVariable3
	#define CHK_IecVarAccAppendVariable3 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccAppendVariable3  CAL_CMEXPAPI( "IecVarAccAppendVariable3" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccAppendVariable3  PFIECVARACCAPPENDVARIABLE3 pfIecVarAccAppendVariable3;
	#define EXT_IecVarAccAppendVariable3  extern PFIECVARACCAPPENDVARIABLE3 pfIecVarAccAppendVariable3;
	#define GET_IecVarAccAppendVariable3(fl)  s_pfCMGetAPI2( "IecVarAccAppendVariable3", (RTS_VOID_FCTPTR *)&pfIecVarAccAppendVariable3, (fl), 0, 0)
	#define CAL_IecVarAccAppendVariable3  pfIecVarAccAppendVariable3
	#define CHK_IecVarAccAppendVariable3  (pfIecVarAccAppendVariable3 != NULL)
	#define EXP_IecVarAccAppendVariable3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccAppendVariable3", (RTS_UINTPTR)IecVarAccAppendVariable3, 0, 0) 
#endif




/**
 * <description>Remove a variable from the symbolic interface. This is used, to unregister a variable at an optional data server!</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the symbolic node</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL IecVarAccRemoveVariable(RTS_HANDLE hInterface, RTS_HANDLE hNode);
typedef RTS_RESULT (CDECL * PFIECVARACCREMOVEVARIABLE) (RTS_HANDLE hInterface, RTS_HANDLE hNode);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCREMOVEVARIABLE_NOTIMPLEMENTED)
	#define USE_IecVarAccRemoveVariable
	#define EXT_IecVarAccRemoveVariable
	#define GET_IecVarAccRemoveVariable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccRemoveVariable(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccRemoveVariable  FALSE
	#define EXP_IecVarAccRemoveVariable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccRemoveVariable
	#define EXT_IecVarAccRemoveVariable
	#define GET_IecVarAccRemoveVariable(fl)  CAL_CMGETAPI( "IecVarAccRemoveVariable" ) 
	#define CAL_IecVarAccRemoveVariable  IecVarAccRemoveVariable
	#define CHK_IecVarAccRemoveVariable  TRUE
	#define EXP_IecVarAccRemoveVariable  CAL_CMEXPAPI( "IecVarAccRemoveVariable" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccRemoveVariable
	#define EXT_IecVarAccRemoveVariable
	#define GET_IecVarAccRemoveVariable(fl)  CAL_CMGETAPI( "IecVarAccRemoveVariable" ) 
	#define CAL_IecVarAccRemoveVariable  IecVarAccRemoveVariable
	#define CHK_IecVarAccRemoveVariable  TRUE
	#define EXP_IecVarAccRemoveVariable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccRemoveVariable", (RTS_UINTPTR)IecVarAccRemoveVariable, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccRemoveVariable
	#define EXT_CmpIecVarAccessIecVarAccRemoveVariable
	#define GET_CmpIecVarAccessIecVarAccRemoveVariable  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccRemoveVariable pICmpIecVarAccess->IIecVarAccRemoveVariable
	#define CHK_CmpIecVarAccessIecVarAccRemoveVariable (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccRemoveVariable  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccRemoveVariable
	#define EXT_IecVarAccRemoveVariable
	#define GET_IecVarAccRemoveVariable(fl)  CAL_CMGETAPI( "IecVarAccRemoveVariable" ) 
	#define CAL_IecVarAccRemoveVariable pICmpIecVarAccess->IIecVarAccRemoveVariable
	#define CHK_IecVarAccRemoveVariable (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccRemoveVariable  CAL_CMEXPAPI( "IecVarAccRemoveVariable" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccRemoveVariable  PFIECVARACCREMOVEVARIABLE pfIecVarAccRemoveVariable;
	#define EXT_IecVarAccRemoveVariable  extern PFIECVARACCREMOVEVARIABLE pfIecVarAccRemoveVariable;
	#define GET_IecVarAccRemoveVariable(fl)  s_pfCMGetAPI2( "IecVarAccRemoveVariable", (RTS_VOID_FCTPTR *)&pfIecVarAccRemoveVariable, (fl), 0, 0)
	#define CAL_IecVarAccRemoveVariable  pfIecVarAccRemoveVariable
	#define CHK_IecVarAccRemoveVariable  (pfIecVarAccRemoveVariable != NULL)
	#define EXP_IecVarAccRemoveVariable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccRemoveVariable", (RTS_UINTPTR)IecVarAccRemoveVariable, 0, 0) 
#endif




/**
 * <description>Remove a variable from the symbolic interface. This is used, to unregister a variable at an optional data server!</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the symbolic node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by IecVarAccGetNode3</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL IecVarAccRemoveVariable3(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation);
typedef RTS_RESULT (CDECL * PFIECVARACCREMOVEVARIABLE3) (RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCREMOVEVARIABLE3_NOTIMPLEMENTED)
	#define USE_IecVarAccRemoveVariable3
	#define EXT_IecVarAccRemoveVariable3
	#define GET_IecVarAccRemoveVariable3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccRemoveVariable3(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccRemoveVariable3  FALSE
	#define EXP_IecVarAccRemoveVariable3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccRemoveVariable3
	#define EXT_IecVarAccRemoveVariable3
	#define GET_IecVarAccRemoveVariable3(fl)  CAL_CMGETAPI( "IecVarAccRemoveVariable3" ) 
	#define CAL_IecVarAccRemoveVariable3  IecVarAccRemoveVariable3
	#define CHK_IecVarAccRemoveVariable3  TRUE
	#define EXP_IecVarAccRemoveVariable3  CAL_CMEXPAPI( "IecVarAccRemoveVariable3" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccRemoveVariable3
	#define EXT_IecVarAccRemoveVariable3
	#define GET_IecVarAccRemoveVariable3(fl)  CAL_CMGETAPI( "IecVarAccRemoveVariable3" ) 
	#define CAL_IecVarAccRemoveVariable3  IecVarAccRemoveVariable3
	#define CHK_IecVarAccRemoveVariable3  TRUE
	#define EXP_IecVarAccRemoveVariable3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccRemoveVariable3", (RTS_UINTPTR)IecVarAccRemoveVariable3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccRemoveVariable3
	#define EXT_CmpIecVarAccessIecVarAccRemoveVariable3
	#define GET_CmpIecVarAccessIecVarAccRemoveVariable3  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccRemoveVariable3 pICmpIecVarAccess->IIecVarAccRemoveVariable3
	#define CHK_CmpIecVarAccessIecVarAccRemoveVariable3 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccRemoveVariable3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccRemoveVariable3
	#define EXT_IecVarAccRemoveVariable3
	#define GET_IecVarAccRemoveVariable3(fl)  CAL_CMGETAPI( "IecVarAccRemoveVariable3" ) 
	#define CAL_IecVarAccRemoveVariable3 pICmpIecVarAccess->IIecVarAccRemoveVariable3
	#define CHK_IecVarAccRemoveVariable3 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccRemoveVariable3  CAL_CMEXPAPI( "IecVarAccRemoveVariable3" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccRemoveVariable3  PFIECVARACCREMOVEVARIABLE3 pfIecVarAccRemoveVariable3;
	#define EXT_IecVarAccRemoveVariable3  extern PFIECVARACCREMOVEVARIABLE3 pfIecVarAccRemoveVariable3;
	#define GET_IecVarAccRemoveVariable3(fl)  s_pfCMGetAPI2( "IecVarAccRemoveVariable3", (RTS_VOID_FCTPTR *)&pfIecVarAccRemoveVariable3, (fl), 0, 0)
	#define CAL_IecVarAccRemoveVariable3  pfIecVarAccRemoveVariable3
	#define CHK_IecVarAccRemoveVariable3  (pfIecVarAccRemoveVariable3 != NULL)
	#define EXP_IecVarAccRemoveVariable3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccRemoveVariable3", (RTS_UINTPTR)IecVarAccRemoveVariable3, 0, 0) 
#endif




/**
 * <description>End the variable configuration. This is used, to leave a new configuration for an optional data server!</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL IecVarAccEndVariableConfiguration(RTS_HANDLE hInterface);
typedef RTS_RESULT (CDECL * PFIECVARACCENDVARIABLECONFIGURATION) (RTS_HANDLE hInterface);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCENDVARIABLECONFIGURATION_NOTIMPLEMENTED)
	#define USE_IecVarAccEndVariableConfiguration
	#define EXT_IecVarAccEndVariableConfiguration
	#define GET_IecVarAccEndVariableConfiguration(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccEndVariableConfiguration(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccEndVariableConfiguration  FALSE
	#define EXP_IecVarAccEndVariableConfiguration  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccEndVariableConfiguration
	#define EXT_IecVarAccEndVariableConfiguration
	#define GET_IecVarAccEndVariableConfiguration(fl)  CAL_CMGETAPI( "IecVarAccEndVariableConfiguration" ) 
	#define CAL_IecVarAccEndVariableConfiguration  IecVarAccEndVariableConfiguration
	#define CHK_IecVarAccEndVariableConfiguration  TRUE
	#define EXP_IecVarAccEndVariableConfiguration  CAL_CMEXPAPI( "IecVarAccEndVariableConfiguration" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccEndVariableConfiguration
	#define EXT_IecVarAccEndVariableConfiguration
	#define GET_IecVarAccEndVariableConfiguration(fl)  CAL_CMGETAPI( "IecVarAccEndVariableConfiguration" ) 
	#define CAL_IecVarAccEndVariableConfiguration  IecVarAccEndVariableConfiguration
	#define CHK_IecVarAccEndVariableConfiguration  TRUE
	#define EXP_IecVarAccEndVariableConfiguration  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccEndVariableConfiguration", (RTS_UINTPTR)IecVarAccEndVariableConfiguration, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccEndVariableConfiguration
	#define EXT_CmpIecVarAccessIecVarAccEndVariableConfiguration
	#define GET_CmpIecVarAccessIecVarAccEndVariableConfiguration  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccEndVariableConfiguration pICmpIecVarAccess->IIecVarAccEndVariableConfiguration
	#define CHK_CmpIecVarAccessIecVarAccEndVariableConfiguration (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccEndVariableConfiguration  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccEndVariableConfiguration
	#define EXT_IecVarAccEndVariableConfiguration
	#define GET_IecVarAccEndVariableConfiguration(fl)  CAL_CMGETAPI( "IecVarAccEndVariableConfiguration" ) 
	#define CAL_IecVarAccEndVariableConfiguration pICmpIecVarAccess->IIecVarAccEndVariableConfiguration
	#define CHK_IecVarAccEndVariableConfiguration (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccEndVariableConfiguration  CAL_CMEXPAPI( "IecVarAccEndVariableConfiguration" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccEndVariableConfiguration  PFIECVARACCENDVARIABLECONFIGURATION pfIecVarAccEndVariableConfiguration;
	#define EXT_IecVarAccEndVariableConfiguration  extern PFIECVARACCENDVARIABLECONFIGURATION pfIecVarAccEndVariableConfiguration;
	#define GET_IecVarAccEndVariableConfiguration(fl)  s_pfCMGetAPI2( "IecVarAccEndVariableConfiguration", (RTS_VOID_FCTPTR *)&pfIecVarAccEndVariableConfiguration, (fl), 0, 0)
	#define CAL_IecVarAccEndVariableConfiguration  pfIecVarAccEndVariableConfiguration
	#define CHK_IecVarAccEndVariableConfiguration  (pfIecVarAccEndVariableConfiguration != NULL)
	#define EXP_IecVarAccEndVariableConfiguration  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccEndVariableConfiguration", (RTS_UINTPTR)IecVarAccEndVariableConfiguration, 0, 0) 
#endif





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
RTS_RESULT CDECL IecVarAccBrowseRecursive(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, PF_IECVARACC_BROWSECALLBACK pfBrowseCallback, RTS_BOOL bIecCallback, void *pUserParameter);
typedef RTS_RESULT (CDECL * PFIECVARACCBROWSERECURSIVE) (RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, PF_IECVARACC_BROWSECALLBACK pfBrowseCallback, RTS_BOOL bIecCallback, void *pUserParameter);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCBROWSERECURSIVE_NOTIMPLEMENTED)
	#define USE_IecVarAccBrowseRecursive
	#define EXT_IecVarAccBrowseRecursive
	#define GET_IecVarAccBrowseRecursive(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccBrowseRecursive(p0,p1,p2,p3,p4,p5)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccBrowseRecursive  FALSE
	#define EXP_IecVarAccBrowseRecursive  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccBrowseRecursive
	#define EXT_IecVarAccBrowseRecursive
	#define GET_IecVarAccBrowseRecursive(fl)  CAL_CMGETAPI( "IecVarAccBrowseRecursive" ) 
	#define CAL_IecVarAccBrowseRecursive  IecVarAccBrowseRecursive
	#define CHK_IecVarAccBrowseRecursive  TRUE
	#define EXP_IecVarAccBrowseRecursive  CAL_CMEXPAPI( "IecVarAccBrowseRecursive" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccBrowseRecursive
	#define EXT_IecVarAccBrowseRecursive
	#define GET_IecVarAccBrowseRecursive(fl)  CAL_CMGETAPI( "IecVarAccBrowseRecursive" ) 
	#define CAL_IecVarAccBrowseRecursive  IecVarAccBrowseRecursive
	#define CHK_IecVarAccBrowseRecursive  TRUE
	#define EXP_IecVarAccBrowseRecursive  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccBrowseRecursive", (RTS_UINTPTR)IecVarAccBrowseRecursive, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccBrowseRecursive
	#define EXT_CmpIecVarAccessIecVarAccBrowseRecursive
	#define GET_CmpIecVarAccessIecVarAccBrowseRecursive  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccBrowseRecursive pICmpIecVarAccess->IIecVarAccBrowseRecursive
	#define CHK_CmpIecVarAccessIecVarAccBrowseRecursive (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccBrowseRecursive  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccBrowseRecursive
	#define EXT_IecVarAccBrowseRecursive
	#define GET_IecVarAccBrowseRecursive(fl)  CAL_CMGETAPI( "IecVarAccBrowseRecursive" ) 
	#define CAL_IecVarAccBrowseRecursive pICmpIecVarAccess->IIecVarAccBrowseRecursive
	#define CHK_IecVarAccBrowseRecursive (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccBrowseRecursive  CAL_CMEXPAPI( "IecVarAccBrowseRecursive" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccBrowseRecursive  PFIECVARACCBROWSERECURSIVE pfIecVarAccBrowseRecursive;
	#define EXT_IecVarAccBrowseRecursive  extern PFIECVARACCBROWSERECURSIVE pfIecVarAccBrowseRecursive;
	#define GET_IecVarAccBrowseRecursive(fl)  s_pfCMGetAPI2( "IecVarAccBrowseRecursive", (RTS_VOID_FCTPTR *)&pfIecVarAccBrowseRecursive, (fl), 0, 0)
	#define CAL_IecVarAccBrowseRecursive  pfIecVarAccBrowseRecursive
	#define CHK_IecVarAccBrowseRecursive  (pfIecVarAccBrowseRecursive != NULL)
	#define EXP_IecVarAccBrowseRecursive  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccBrowseRecursive", (RTS_UINTPTR)IecVarAccBrowseRecursive, 0, 0) 
#endif




/**
 * <description>Browse routine to get the symbolic root branch node (e.g. "Application1")</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the root node (called hNode)</result>
 */
RTS_HANDLE CDECL IecVarAccBrowseGetRoot(RTS_HANDLE hInterface, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECVARACCBROWSEGETROOT) (RTS_HANDLE hInterface, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCBROWSEGETROOT_NOTIMPLEMENTED)
	#define USE_IecVarAccBrowseGetRoot
	#define EXT_IecVarAccBrowseGetRoot
	#define GET_IecVarAccBrowseGetRoot(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccBrowseGetRoot(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecVarAccBrowseGetRoot  FALSE
	#define EXP_IecVarAccBrowseGetRoot  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccBrowseGetRoot
	#define EXT_IecVarAccBrowseGetRoot
	#define GET_IecVarAccBrowseGetRoot(fl)  CAL_CMGETAPI( "IecVarAccBrowseGetRoot" ) 
	#define CAL_IecVarAccBrowseGetRoot  IecVarAccBrowseGetRoot
	#define CHK_IecVarAccBrowseGetRoot  TRUE
	#define EXP_IecVarAccBrowseGetRoot  CAL_CMEXPAPI( "IecVarAccBrowseGetRoot" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccBrowseGetRoot
	#define EXT_IecVarAccBrowseGetRoot
	#define GET_IecVarAccBrowseGetRoot(fl)  CAL_CMGETAPI( "IecVarAccBrowseGetRoot" ) 
	#define CAL_IecVarAccBrowseGetRoot  IecVarAccBrowseGetRoot
	#define CHK_IecVarAccBrowseGetRoot  TRUE
	#define EXP_IecVarAccBrowseGetRoot  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccBrowseGetRoot", (RTS_UINTPTR)IecVarAccBrowseGetRoot, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccBrowseGetRoot
	#define EXT_CmpIecVarAccessIecVarAccBrowseGetRoot
	#define GET_CmpIecVarAccessIecVarAccBrowseGetRoot  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccBrowseGetRoot pICmpIecVarAccess->IIecVarAccBrowseGetRoot
	#define CHK_CmpIecVarAccessIecVarAccBrowseGetRoot (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccBrowseGetRoot  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccBrowseGetRoot
	#define EXT_IecVarAccBrowseGetRoot
	#define GET_IecVarAccBrowseGetRoot(fl)  CAL_CMGETAPI( "IecVarAccBrowseGetRoot" ) 
	#define CAL_IecVarAccBrowseGetRoot pICmpIecVarAccess->IIecVarAccBrowseGetRoot
	#define CHK_IecVarAccBrowseGetRoot (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccBrowseGetRoot  CAL_CMEXPAPI( "IecVarAccBrowseGetRoot" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccBrowseGetRoot  PFIECVARACCBROWSEGETROOT pfIecVarAccBrowseGetRoot;
	#define EXT_IecVarAccBrowseGetRoot  extern PFIECVARACCBROWSEGETROOT pfIecVarAccBrowseGetRoot;
	#define GET_IecVarAccBrowseGetRoot(fl)  s_pfCMGetAPI2( "IecVarAccBrowseGetRoot", (RTS_VOID_FCTPTR *)&pfIecVarAccBrowseGetRoot, (fl), 0, 0)
	#define CAL_IecVarAccBrowseGetRoot  pfIecVarAccBrowseGetRoot
	#define CHK_IecVarAccBrowseGetRoot  (pfIecVarAccBrowseGetRoot != NULL)
	#define EXP_IecVarAccBrowseGetRoot  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccBrowseGetRoot", (RTS_UINTPTR)IecVarAccBrowseGetRoot, 0, 0) 
#endif




/**
 * <description>Browse routine to browse down to the child node (e.g. "Application1.GVL")</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the parent node</param>
 * <result>Handle to the child node (called hNode)</result>
 */
RTS_HANDLE CDECL IecVarAccBrowseDown(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECVARACCBROWSEDOWN) (RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCBROWSEDOWN_NOTIMPLEMENTED)
	#define USE_IecVarAccBrowseDown
	#define EXT_IecVarAccBrowseDown
	#define GET_IecVarAccBrowseDown(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccBrowseDown(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecVarAccBrowseDown  FALSE
	#define EXP_IecVarAccBrowseDown  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccBrowseDown
	#define EXT_IecVarAccBrowseDown
	#define GET_IecVarAccBrowseDown(fl)  CAL_CMGETAPI( "IecVarAccBrowseDown" ) 
	#define CAL_IecVarAccBrowseDown  IecVarAccBrowseDown
	#define CHK_IecVarAccBrowseDown  TRUE
	#define EXP_IecVarAccBrowseDown  CAL_CMEXPAPI( "IecVarAccBrowseDown" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccBrowseDown
	#define EXT_IecVarAccBrowseDown
	#define GET_IecVarAccBrowseDown(fl)  CAL_CMGETAPI( "IecVarAccBrowseDown" ) 
	#define CAL_IecVarAccBrowseDown  IecVarAccBrowseDown
	#define CHK_IecVarAccBrowseDown  TRUE
	#define EXP_IecVarAccBrowseDown  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccBrowseDown", (RTS_UINTPTR)IecVarAccBrowseDown, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccBrowseDown
	#define EXT_CmpIecVarAccessIecVarAccBrowseDown
	#define GET_CmpIecVarAccessIecVarAccBrowseDown  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccBrowseDown pICmpIecVarAccess->IIecVarAccBrowseDown
	#define CHK_CmpIecVarAccessIecVarAccBrowseDown (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccBrowseDown  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccBrowseDown
	#define EXT_IecVarAccBrowseDown
	#define GET_IecVarAccBrowseDown(fl)  CAL_CMGETAPI( "IecVarAccBrowseDown" ) 
	#define CAL_IecVarAccBrowseDown pICmpIecVarAccess->IIecVarAccBrowseDown
	#define CHK_IecVarAccBrowseDown (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccBrowseDown  CAL_CMEXPAPI( "IecVarAccBrowseDown" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccBrowseDown  PFIECVARACCBROWSEDOWN pfIecVarAccBrowseDown;
	#define EXT_IecVarAccBrowseDown  extern PFIECVARACCBROWSEDOWN pfIecVarAccBrowseDown;
	#define GET_IecVarAccBrowseDown(fl)  s_pfCMGetAPI2( "IecVarAccBrowseDown", (RTS_VOID_FCTPTR *)&pfIecVarAccBrowseDown, (fl), 0, 0)
	#define CAL_IecVarAccBrowseDown  pfIecVarAccBrowseDown
	#define CHK_IecVarAccBrowseDown  (pfIecVarAccBrowseDown != NULL)
	#define EXP_IecVarAccBrowseDown  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccBrowseDown", (RTS_UINTPTR)IecVarAccBrowseDown, 0, 0) 
#endif




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
RTS_HANDLE CDECL IecVarAccBrowseDown2(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECVARACCBROWSEDOWN2) (RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCBROWSEDOWN2_NOTIMPLEMENTED)
	#define USE_IecVarAccBrowseDown2
	#define EXT_IecVarAccBrowseDown2
	#define GET_IecVarAccBrowseDown2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccBrowseDown2(p0,p1,p2,p3)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecVarAccBrowseDown2  FALSE
	#define EXP_IecVarAccBrowseDown2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccBrowseDown2
	#define EXT_IecVarAccBrowseDown2
	#define GET_IecVarAccBrowseDown2(fl)  CAL_CMGETAPI( "IecVarAccBrowseDown2" ) 
	#define CAL_IecVarAccBrowseDown2  IecVarAccBrowseDown2
	#define CHK_IecVarAccBrowseDown2  TRUE
	#define EXP_IecVarAccBrowseDown2  CAL_CMEXPAPI( "IecVarAccBrowseDown2" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccBrowseDown2
	#define EXT_IecVarAccBrowseDown2
	#define GET_IecVarAccBrowseDown2(fl)  CAL_CMGETAPI( "IecVarAccBrowseDown2" ) 
	#define CAL_IecVarAccBrowseDown2  IecVarAccBrowseDown2
	#define CHK_IecVarAccBrowseDown2  TRUE
	#define EXP_IecVarAccBrowseDown2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccBrowseDown2", (RTS_UINTPTR)IecVarAccBrowseDown2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccBrowseDown2
	#define EXT_CmpIecVarAccessIecVarAccBrowseDown2
	#define GET_CmpIecVarAccessIecVarAccBrowseDown2  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccBrowseDown2 pICmpIecVarAccess->IIecVarAccBrowseDown2
	#define CHK_CmpIecVarAccessIecVarAccBrowseDown2 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccBrowseDown2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccBrowseDown2
	#define EXT_IecVarAccBrowseDown2
	#define GET_IecVarAccBrowseDown2(fl)  CAL_CMGETAPI( "IecVarAccBrowseDown2" ) 
	#define CAL_IecVarAccBrowseDown2 pICmpIecVarAccess->IIecVarAccBrowseDown2
	#define CHK_IecVarAccBrowseDown2 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccBrowseDown2  CAL_CMEXPAPI( "IecVarAccBrowseDown2" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccBrowseDown2  PFIECVARACCBROWSEDOWN2 pfIecVarAccBrowseDown2;
	#define EXT_IecVarAccBrowseDown2  extern PFIECVARACCBROWSEDOWN2 pfIecVarAccBrowseDown2;
	#define GET_IecVarAccBrowseDown2(fl)  s_pfCMGetAPI2( "IecVarAccBrowseDown2", (RTS_VOID_FCTPTR *)&pfIecVarAccBrowseDown2, (fl), 0, 0)
	#define CAL_IecVarAccBrowseDown2  pfIecVarAccBrowseDown2
	#define CHK_IecVarAccBrowseDown2  (pfIecVarAccBrowseDown2 != NULL)
	#define EXP_IecVarAccBrowseDown2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccBrowseDown2", (RTS_UINTPTR)IecVarAccBrowseDown2, 0, 0) 
#endif




/**
 * <description>Browse routine to browse up to the parent node</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the child node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the parent node (called hNode)</result>
 */
RTS_HANDLE CDECL IecVarAccBrowseUp(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECVARACCBROWSEUP) (RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCBROWSEUP_NOTIMPLEMENTED)
	#define USE_IecVarAccBrowseUp
	#define EXT_IecVarAccBrowseUp
	#define GET_IecVarAccBrowseUp(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccBrowseUp(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecVarAccBrowseUp  FALSE
	#define EXP_IecVarAccBrowseUp  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccBrowseUp
	#define EXT_IecVarAccBrowseUp
	#define GET_IecVarAccBrowseUp(fl)  CAL_CMGETAPI( "IecVarAccBrowseUp" ) 
	#define CAL_IecVarAccBrowseUp  IecVarAccBrowseUp
	#define CHK_IecVarAccBrowseUp  TRUE
	#define EXP_IecVarAccBrowseUp  CAL_CMEXPAPI( "IecVarAccBrowseUp" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccBrowseUp
	#define EXT_IecVarAccBrowseUp
	#define GET_IecVarAccBrowseUp(fl)  CAL_CMGETAPI( "IecVarAccBrowseUp" ) 
	#define CAL_IecVarAccBrowseUp  IecVarAccBrowseUp
	#define CHK_IecVarAccBrowseUp  TRUE
	#define EXP_IecVarAccBrowseUp  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccBrowseUp", (RTS_UINTPTR)IecVarAccBrowseUp, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccBrowseUp
	#define EXT_CmpIecVarAccessIecVarAccBrowseUp
	#define GET_CmpIecVarAccessIecVarAccBrowseUp  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccBrowseUp pICmpIecVarAccess->IIecVarAccBrowseUp
	#define CHK_CmpIecVarAccessIecVarAccBrowseUp (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccBrowseUp  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccBrowseUp
	#define EXT_IecVarAccBrowseUp
	#define GET_IecVarAccBrowseUp(fl)  CAL_CMGETAPI( "IecVarAccBrowseUp" ) 
	#define CAL_IecVarAccBrowseUp pICmpIecVarAccess->IIecVarAccBrowseUp
	#define CHK_IecVarAccBrowseUp (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccBrowseUp  CAL_CMEXPAPI( "IecVarAccBrowseUp" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccBrowseUp  PFIECVARACCBROWSEUP pfIecVarAccBrowseUp;
	#define EXT_IecVarAccBrowseUp  extern PFIECVARACCBROWSEUP pfIecVarAccBrowseUp;
	#define GET_IecVarAccBrowseUp(fl)  s_pfCMGetAPI2( "IecVarAccBrowseUp", (RTS_VOID_FCTPTR *)&pfIecVarAccBrowseUp, (fl), 0, 0)
	#define CAL_IecVarAccBrowseUp  pfIecVarAccBrowseUp
	#define CHK_IecVarAccBrowseUp  (pfIecVarAccBrowseUp != NULL)
	#define EXP_IecVarAccBrowseUp  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccBrowseUp", (RTS_UINTPTR)IecVarAccBrowseUp, 0, 0) 
#endif




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
RTS_HANDLE CDECL IecVarAccBrowseUp2(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECVARACCBROWSEUP2) (RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCBROWSEUP2_NOTIMPLEMENTED)
	#define USE_IecVarAccBrowseUp2
	#define EXT_IecVarAccBrowseUp2
	#define GET_IecVarAccBrowseUp2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccBrowseUp2(p0,p1,p2,p3)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecVarAccBrowseUp2  FALSE
	#define EXP_IecVarAccBrowseUp2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccBrowseUp2
	#define EXT_IecVarAccBrowseUp2
	#define GET_IecVarAccBrowseUp2(fl)  CAL_CMGETAPI( "IecVarAccBrowseUp2" ) 
	#define CAL_IecVarAccBrowseUp2  IecVarAccBrowseUp2
	#define CHK_IecVarAccBrowseUp2  TRUE
	#define EXP_IecVarAccBrowseUp2  CAL_CMEXPAPI( "IecVarAccBrowseUp2" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccBrowseUp2
	#define EXT_IecVarAccBrowseUp2
	#define GET_IecVarAccBrowseUp2(fl)  CAL_CMGETAPI( "IecVarAccBrowseUp2" ) 
	#define CAL_IecVarAccBrowseUp2  IecVarAccBrowseUp2
	#define CHK_IecVarAccBrowseUp2  TRUE
	#define EXP_IecVarAccBrowseUp2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccBrowseUp2", (RTS_UINTPTR)IecVarAccBrowseUp2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccBrowseUp2
	#define EXT_CmpIecVarAccessIecVarAccBrowseUp2
	#define GET_CmpIecVarAccessIecVarAccBrowseUp2  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccBrowseUp2 pICmpIecVarAccess->IIecVarAccBrowseUp2
	#define CHK_CmpIecVarAccessIecVarAccBrowseUp2 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccBrowseUp2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccBrowseUp2
	#define EXT_IecVarAccBrowseUp2
	#define GET_IecVarAccBrowseUp2(fl)  CAL_CMGETAPI( "IecVarAccBrowseUp2" ) 
	#define CAL_IecVarAccBrowseUp2 pICmpIecVarAccess->IIecVarAccBrowseUp2
	#define CHK_IecVarAccBrowseUp2 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccBrowseUp2  CAL_CMEXPAPI( "IecVarAccBrowseUp2" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccBrowseUp2  PFIECVARACCBROWSEUP2 pfIecVarAccBrowseUp2;
	#define EXT_IecVarAccBrowseUp2  extern PFIECVARACCBROWSEUP2 pfIecVarAccBrowseUp2;
	#define GET_IecVarAccBrowseUp2(fl)  s_pfCMGetAPI2( "IecVarAccBrowseUp2", (RTS_VOID_FCTPTR *)&pfIecVarAccBrowseUp2, (fl), 0, 0)
	#define CAL_IecVarAccBrowseUp2  pfIecVarAccBrowseUp2
	#define CHK_IecVarAccBrowseUp2  (pfIecVarAccBrowseUp2 != NULL)
	#define EXP_IecVarAccBrowseUp2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccBrowseUp2", (RTS_UINTPTR)IecVarAccBrowseUp2, 0, 0) 
#endif




/**
 * <description>Browse routine to get the next sibling node</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the predecessor node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the next sibling node (called hNode)</result>
 */
RTS_HANDLE CDECL IecVarAccBrowseGetNext(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECVARACCBROWSEGETNEXT) (RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCBROWSEGETNEXT_NOTIMPLEMENTED)
	#define USE_IecVarAccBrowseGetNext
	#define EXT_IecVarAccBrowseGetNext
	#define GET_IecVarAccBrowseGetNext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccBrowseGetNext(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecVarAccBrowseGetNext  FALSE
	#define EXP_IecVarAccBrowseGetNext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccBrowseGetNext
	#define EXT_IecVarAccBrowseGetNext
	#define GET_IecVarAccBrowseGetNext(fl)  CAL_CMGETAPI( "IecVarAccBrowseGetNext" ) 
	#define CAL_IecVarAccBrowseGetNext  IecVarAccBrowseGetNext
	#define CHK_IecVarAccBrowseGetNext  TRUE
	#define EXP_IecVarAccBrowseGetNext  CAL_CMEXPAPI( "IecVarAccBrowseGetNext" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccBrowseGetNext
	#define EXT_IecVarAccBrowseGetNext
	#define GET_IecVarAccBrowseGetNext(fl)  CAL_CMGETAPI( "IecVarAccBrowseGetNext" ) 
	#define CAL_IecVarAccBrowseGetNext  IecVarAccBrowseGetNext
	#define CHK_IecVarAccBrowseGetNext  TRUE
	#define EXP_IecVarAccBrowseGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccBrowseGetNext", (RTS_UINTPTR)IecVarAccBrowseGetNext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccBrowseGetNext
	#define EXT_CmpIecVarAccessIecVarAccBrowseGetNext
	#define GET_CmpIecVarAccessIecVarAccBrowseGetNext  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccBrowseGetNext pICmpIecVarAccess->IIecVarAccBrowseGetNext
	#define CHK_CmpIecVarAccessIecVarAccBrowseGetNext (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccBrowseGetNext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccBrowseGetNext
	#define EXT_IecVarAccBrowseGetNext
	#define GET_IecVarAccBrowseGetNext(fl)  CAL_CMGETAPI( "IecVarAccBrowseGetNext" ) 
	#define CAL_IecVarAccBrowseGetNext pICmpIecVarAccess->IIecVarAccBrowseGetNext
	#define CHK_IecVarAccBrowseGetNext (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccBrowseGetNext  CAL_CMEXPAPI( "IecVarAccBrowseGetNext" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccBrowseGetNext  PFIECVARACCBROWSEGETNEXT pfIecVarAccBrowseGetNext;
	#define EXT_IecVarAccBrowseGetNext  extern PFIECVARACCBROWSEGETNEXT pfIecVarAccBrowseGetNext;
	#define GET_IecVarAccBrowseGetNext(fl)  s_pfCMGetAPI2( "IecVarAccBrowseGetNext", (RTS_VOID_FCTPTR *)&pfIecVarAccBrowseGetNext, (fl), 0, 0)
	#define CAL_IecVarAccBrowseGetNext  pfIecVarAccBrowseGetNext
	#define CHK_IecVarAccBrowseGetNext  (pfIecVarAccBrowseGetNext != NULL)
	#define EXP_IecVarAccBrowseGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccBrowseGetNext", (RTS_UINTPTR)IecVarAccBrowseGetNext, 0, 0) 
#endif




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
RTS_HANDLE CDECL IecVarAccBrowseGetNext2(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECVARACCBROWSEGETNEXT2) (RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCBROWSEGETNEXT2_NOTIMPLEMENTED)
	#define USE_IecVarAccBrowseGetNext2
	#define EXT_IecVarAccBrowseGetNext2
	#define GET_IecVarAccBrowseGetNext2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccBrowseGetNext2(p0,p1,p2,p3)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecVarAccBrowseGetNext2  FALSE
	#define EXP_IecVarAccBrowseGetNext2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccBrowseGetNext2
	#define EXT_IecVarAccBrowseGetNext2
	#define GET_IecVarAccBrowseGetNext2(fl)  CAL_CMGETAPI( "IecVarAccBrowseGetNext2" ) 
	#define CAL_IecVarAccBrowseGetNext2  IecVarAccBrowseGetNext2
	#define CHK_IecVarAccBrowseGetNext2  TRUE
	#define EXP_IecVarAccBrowseGetNext2  CAL_CMEXPAPI( "IecVarAccBrowseGetNext2" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccBrowseGetNext2
	#define EXT_IecVarAccBrowseGetNext2
	#define GET_IecVarAccBrowseGetNext2(fl)  CAL_CMGETAPI( "IecVarAccBrowseGetNext2" ) 
	#define CAL_IecVarAccBrowseGetNext2  IecVarAccBrowseGetNext2
	#define CHK_IecVarAccBrowseGetNext2  TRUE
	#define EXP_IecVarAccBrowseGetNext2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccBrowseGetNext2", (RTS_UINTPTR)IecVarAccBrowseGetNext2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccBrowseGetNext2
	#define EXT_CmpIecVarAccessIecVarAccBrowseGetNext2
	#define GET_CmpIecVarAccessIecVarAccBrowseGetNext2  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccBrowseGetNext2 pICmpIecVarAccess->IIecVarAccBrowseGetNext2
	#define CHK_CmpIecVarAccessIecVarAccBrowseGetNext2 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccBrowseGetNext2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccBrowseGetNext2
	#define EXT_IecVarAccBrowseGetNext2
	#define GET_IecVarAccBrowseGetNext2(fl)  CAL_CMGETAPI( "IecVarAccBrowseGetNext2" ) 
	#define CAL_IecVarAccBrowseGetNext2 pICmpIecVarAccess->IIecVarAccBrowseGetNext2
	#define CHK_IecVarAccBrowseGetNext2 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccBrowseGetNext2  CAL_CMEXPAPI( "IecVarAccBrowseGetNext2" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccBrowseGetNext2  PFIECVARACCBROWSEGETNEXT2 pfIecVarAccBrowseGetNext2;
	#define EXT_IecVarAccBrowseGetNext2  extern PFIECVARACCBROWSEGETNEXT2 pfIecVarAccBrowseGetNext2;
	#define GET_IecVarAccBrowseGetNext2(fl)  s_pfCMGetAPI2( "IecVarAccBrowseGetNext2", (RTS_VOID_FCTPTR *)&pfIecVarAccBrowseGetNext2, (fl), 0, 0)
	#define CAL_IecVarAccBrowseGetNext2  pfIecVarAccBrowseGetNext2
	#define CHK_IecVarAccBrowseGetNext2  (pfIecVarAccBrowseGetNext2 != NULL)
	#define EXP_IecVarAccBrowseGetNext2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccBrowseGetNext2", (RTS_UINTPTR)IecVarAccBrowseGetNext2, 0, 0) 
#endif




/**
 * <description>Browse routine to get a child node by index. Can be used instead of IecVarAccBrowseDown/IecVarAccBrowseGetNext.</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the parent node</param>
 * <param name="ulIndex" type="IN">Index of the requested child note node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the requested child node (called hNode)</result>
 */
RTS_HANDLE CDECL IecVarAccBrowseGetChildByIndex(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_UI32 ulIndex, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECVARACCBROWSEGETCHILDBYINDEX) (RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_UI32 ulIndex, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCBROWSEGETCHILDBYINDEX_NOTIMPLEMENTED)
	#define USE_IecVarAccBrowseGetChildByIndex
	#define EXT_IecVarAccBrowseGetChildByIndex
	#define GET_IecVarAccBrowseGetChildByIndex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccBrowseGetChildByIndex(p0,p1,p2,p3)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecVarAccBrowseGetChildByIndex  FALSE
	#define EXP_IecVarAccBrowseGetChildByIndex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccBrowseGetChildByIndex
	#define EXT_IecVarAccBrowseGetChildByIndex
	#define GET_IecVarAccBrowseGetChildByIndex(fl)  CAL_CMGETAPI( "IecVarAccBrowseGetChildByIndex" ) 
	#define CAL_IecVarAccBrowseGetChildByIndex  IecVarAccBrowseGetChildByIndex
	#define CHK_IecVarAccBrowseGetChildByIndex  TRUE
	#define EXP_IecVarAccBrowseGetChildByIndex  CAL_CMEXPAPI( "IecVarAccBrowseGetChildByIndex" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccBrowseGetChildByIndex
	#define EXT_IecVarAccBrowseGetChildByIndex
	#define GET_IecVarAccBrowseGetChildByIndex(fl)  CAL_CMGETAPI( "IecVarAccBrowseGetChildByIndex" ) 
	#define CAL_IecVarAccBrowseGetChildByIndex  IecVarAccBrowseGetChildByIndex
	#define CHK_IecVarAccBrowseGetChildByIndex  TRUE
	#define EXP_IecVarAccBrowseGetChildByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccBrowseGetChildByIndex", (RTS_UINTPTR)IecVarAccBrowseGetChildByIndex, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccBrowseGetChildByIndex
	#define EXT_CmpIecVarAccessIecVarAccBrowseGetChildByIndex
	#define GET_CmpIecVarAccessIecVarAccBrowseGetChildByIndex  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccBrowseGetChildByIndex pICmpIecVarAccess->IIecVarAccBrowseGetChildByIndex
	#define CHK_CmpIecVarAccessIecVarAccBrowseGetChildByIndex (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccBrowseGetChildByIndex  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccBrowseGetChildByIndex
	#define EXT_IecVarAccBrowseGetChildByIndex
	#define GET_IecVarAccBrowseGetChildByIndex(fl)  CAL_CMGETAPI( "IecVarAccBrowseGetChildByIndex" ) 
	#define CAL_IecVarAccBrowseGetChildByIndex pICmpIecVarAccess->IIecVarAccBrowseGetChildByIndex
	#define CHK_IecVarAccBrowseGetChildByIndex (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccBrowseGetChildByIndex  CAL_CMEXPAPI( "IecVarAccBrowseGetChildByIndex" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccBrowseGetChildByIndex  PFIECVARACCBROWSEGETCHILDBYINDEX pfIecVarAccBrowseGetChildByIndex;
	#define EXT_IecVarAccBrowseGetChildByIndex  extern PFIECVARACCBROWSEGETCHILDBYINDEX pfIecVarAccBrowseGetChildByIndex;
	#define GET_IecVarAccBrowseGetChildByIndex(fl)  s_pfCMGetAPI2( "IecVarAccBrowseGetChildByIndex", (RTS_VOID_FCTPTR *)&pfIecVarAccBrowseGetChildByIndex, (fl), 0, 0)
	#define CAL_IecVarAccBrowseGetChildByIndex  pfIecVarAccBrowseGetChildByIndex
	#define CHK_IecVarAccBrowseGetChildByIndex  (pfIecVarAccBrowseGetChildByIndex != NULL)
	#define EXP_IecVarAccBrowseGetChildByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccBrowseGetChildByIndex", (RTS_UINTPTR)IecVarAccBrowseGetChildByIndex, 0, 0) 
#endif




/**
 * <description>Get the leaf node handle of a specified variable</description>
 * <param name="pszPath" type="IN">Name of the variable including the complete namespace/path</param>
 * <param name="pulOffset" type="OUT">Offset of the variable to the leaf node (e.g. for structure/FB or array access)</param>
 * <param name="phInterface" type="INOUT">Pointer to specify or to return the symbolic interface handle.
 *		Content must be initialized with RTS_INVALID_HANDLE, if it is not specified!</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the node (called hNode)</result>
 */
RTS_HANDLE CDECL IecVarAccGetNode(char *pszPath, RTS_SIZE *pulOffset, RTS_HANDLE *phInterface, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECVARACCGETNODE) (char *pszPath, RTS_SIZE *pulOffset, RTS_HANDLE *phInterface, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNODE_NOTIMPLEMENTED)
	#define USE_IecVarAccGetNode
	#define EXT_IecVarAccGetNode
	#define GET_IecVarAccGetNode(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetNode(p0,p1,p2,p3)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecVarAccGetNode  FALSE
	#define EXP_IecVarAccGetNode  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetNode
	#define EXT_IecVarAccGetNode
	#define GET_IecVarAccGetNode(fl)  CAL_CMGETAPI( "IecVarAccGetNode" ) 
	#define CAL_IecVarAccGetNode  IecVarAccGetNode
	#define CHK_IecVarAccGetNode  TRUE
	#define EXP_IecVarAccGetNode  CAL_CMEXPAPI( "IecVarAccGetNode" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetNode
	#define EXT_IecVarAccGetNode
	#define GET_IecVarAccGetNode(fl)  CAL_CMGETAPI( "IecVarAccGetNode" ) 
	#define CAL_IecVarAccGetNode  IecVarAccGetNode
	#define CHK_IecVarAccGetNode  TRUE
	#define EXP_IecVarAccGetNode  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNode", (RTS_UINTPTR)IecVarAccGetNode, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetNode
	#define EXT_CmpIecVarAccessIecVarAccGetNode
	#define GET_CmpIecVarAccessIecVarAccGetNode  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetNode pICmpIecVarAccess->IIecVarAccGetNode
	#define CHK_CmpIecVarAccessIecVarAccGetNode (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetNode  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetNode
	#define EXT_IecVarAccGetNode
	#define GET_IecVarAccGetNode(fl)  CAL_CMGETAPI( "IecVarAccGetNode" ) 
	#define CAL_IecVarAccGetNode pICmpIecVarAccess->IIecVarAccGetNode
	#define CHK_IecVarAccGetNode (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetNode  CAL_CMEXPAPI( "IecVarAccGetNode" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetNode  PFIECVARACCGETNODE pfIecVarAccGetNode;
	#define EXT_IecVarAccGetNode  extern PFIECVARACCGETNODE pfIecVarAccGetNode;
	#define GET_IecVarAccGetNode(fl)  s_pfCMGetAPI2( "IecVarAccGetNode", (RTS_VOID_FCTPTR *)&pfIecVarAccGetNode, (fl), 0, 0)
	#define CAL_IecVarAccGetNode  pfIecVarAccGetNode
	#define CHK_IecVarAccGetNode  (pfIecVarAccGetNode != NULL)
	#define EXP_IecVarAccGetNode  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNode", (RTS_UINTPTR)IecVarAccGetNode, 0, 0) 
#endif




/**
 * <description>Get the leaf node handle of a specified variable</description>
 * <param name="pszPath" type="IN">Name of the variable including the complete namespace/path</param>
 * <param name="phInterface" type="INOUT">Pointer to specify or to return the symbolic interface handle.
 *		Content must be initialized with RTS_INVALID_HANDLE, if it is not specified!</param>
 * <param name="pVariableInformation" type="OUT">Pointer to the variable information that is retrieved by IecVarAccGetNode3</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the node (called hNode)</result>
 */
RTS_HANDLE CDECL IecVarAccGetNode3(char *pszPath, RTS_HANDLE *phInterface, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECVARACCGETNODE3) (char *pszPath, RTS_HANDLE *phInterface, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNODE3_NOTIMPLEMENTED)
	#define USE_IecVarAccGetNode3
	#define EXT_IecVarAccGetNode3
	#define GET_IecVarAccGetNode3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetNode3(p0,p1,p2,p3)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecVarAccGetNode3  FALSE
	#define EXP_IecVarAccGetNode3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetNode3
	#define EXT_IecVarAccGetNode3
	#define GET_IecVarAccGetNode3(fl)  CAL_CMGETAPI( "IecVarAccGetNode3" ) 
	#define CAL_IecVarAccGetNode3  IecVarAccGetNode3
	#define CHK_IecVarAccGetNode3  TRUE
	#define EXP_IecVarAccGetNode3  CAL_CMEXPAPI( "IecVarAccGetNode3" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetNode3
	#define EXT_IecVarAccGetNode3
	#define GET_IecVarAccGetNode3(fl)  CAL_CMGETAPI( "IecVarAccGetNode3" ) 
	#define CAL_IecVarAccGetNode3  IecVarAccGetNode3
	#define CHK_IecVarAccGetNode3  TRUE
	#define EXP_IecVarAccGetNode3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNode3", (RTS_UINTPTR)IecVarAccGetNode3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetNode3
	#define EXT_CmpIecVarAccessIecVarAccGetNode3
	#define GET_CmpIecVarAccessIecVarAccGetNode3  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetNode3 pICmpIecVarAccess->IIecVarAccGetNode3
	#define CHK_CmpIecVarAccessIecVarAccGetNode3 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetNode3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetNode3
	#define EXT_IecVarAccGetNode3
	#define GET_IecVarAccGetNode3(fl)  CAL_CMGETAPI( "IecVarAccGetNode3" ) 
	#define CAL_IecVarAccGetNode3 pICmpIecVarAccess->IIecVarAccGetNode3
	#define CHK_IecVarAccGetNode3 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetNode3  CAL_CMEXPAPI( "IecVarAccGetNode3" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetNode3  PFIECVARACCGETNODE3 pfIecVarAccGetNode3;
	#define EXT_IecVarAccGetNode3  extern PFIECVARACCGETNODE3 pfIecVarAccGetNode3;
	#define GET_IecVarAccGetNode3(fl)  s_pfCMGetAPI2( "IecVarAccGetNode3", (RTS_VOID_FCTPTR *)&pfIecVarAccGetNode3, (fl), 0, 0)
	#define CAL_IecVarAccGetNode3  pfIecVarAccGetNode3
	#define CHK_IecVarAccGetNode3  (pfIecVarAccGetNode3 != NULL)
	#define EXP_IecVarAccGetNode3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNode3", (RTS_UINTPTR)IecVarAccGetNode3, 0, 0) 
#endif




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
RTS_HANDLE CDECL IecVarAccGetNode4(char *pszPath, RTS_HANDLE *phInterface, VariableInformationStruct3 *pVariableInformation, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECVARACCGETNODE4) (char *pszPath, RTS_HANDLE *phInterface, VariableInformationStruct3 *pVariableInformation, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNODE4_NOTIMPLEMENTED)
	#define USE_IecVarAccGetNode4
	#define EXT_IecVarAccGetNode4
	#define GET_IecVarAccGetNode4(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetNode4(p0,p1,p2,p3)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecVarAccGetNode4  FALSE
	#define EXP_IecVarAccGetNode4  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetNode4
	#define EXT_IecVarAccGetNode4
	#define GET_IecVarAccGetNode4(fl)  CAL_CMGETAPI( "IecVarAccGetNode4" ) 
	#define CAL_IecVarAccGetNode4  IecVarAccGetNode4
	#define CHK_IecVarAccGetNode4  TRUE
	#define EXP_IecVarAccGetNode4  CAL_CMEXPAPI( "IecVarAccGetNode4" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetNode4
	#define EXT_IecVarAccGetNode4
	#define GET_IecVarAccGetNode4(fl)  CAL_CMGETAPI( "IecVarAccGetNode4" ) 
	#define CAL_IecVarAccGetNode4  IecVarAccGetNode4
	#define CHK_IecVarAccGetNode4  TRUE
	#define EXP_IecVarAccGetNode4  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNode4", (RTS_UINTPTR)IecVarAccGetNode4, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetNode4
	#define EXT_CmpIecVarAccessIecVarAccGetNode4
	#define GET_CmpIecVarAccessIecVarAccGetNode4  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetNode4 pICmpIecVarAccess->IIecVarAccGetNode4
	#define CHK_CmpIecVarAccessIecVarAccGetNode4 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetNode4  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetNode4
	#define EXT_IecVarAccGetNode4
	#define GET_IecVarAccGetNode4(fl)  CAL_CMGETAPI( "IecVarAccGetNode4" ) 
	#define CAL_IecVarAccGetNode4 pICmpIecVarAccess->IIecVarAccGetNode4
	#define CHK_IecVarAccGetNode4 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetNode4  CAL_CMEXPAPI( "IecVarAccGetNode4" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetNode4  PFIECVARACCGETNODE4 pfIecVarAccGetNode4;
	#define EXT_IecVarAccGetNode4  extern PFIECVARACCGETNODE4 pfIecVarAccGetNode4;
	#define GET_IecVarAccGetNode4(fl)  s_pfCMGetAPI2( "IecVarAccGetNode4", (RTS_VOID_FCTPTR *)&pfIecVarAccGetNode4, (fl), 0, 0)
	#define CAL_IecVarAccGetNode4  pfIecVarAccGetNode4
	#define CHK_IecVarAccGetNode4  (pfIecVarAccGetNode4 != NULL)
	#define EXP_IecVarAccGetNode4  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNode4", (RTS_UINTPTR)IecVarAccGetNode4, 0, 0) 
#endif




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
int CDECL IecVarAccGetNodeFullPath(RTS_HANDLE hInterface, RTS_HANDLE hNode, char *pszPath, int iMaxPath, RTS_RESULT *pResult);
typedef int (CDECL * PFIECVARACCGETNODEFULLPATH) (RTS_HANDLE hInterface, RTS_HANDLE hNode, char *pszPath, int iMaxPath, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNODEFULLPATH_NOTIMPLEMENTED)
	#define USE_IecVarAccGetNodeFullPath
	#define EXT_IecVarAccGetNodeFullPath
	#define GET_IecVarAccGetNodeFullPath(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetNodeFullPath(p0,p1,p2,p3,p4)  (int)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetNodeFullPath  FALSE
	#define EXP_IecVarAccGetNodeFullPath  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetNodeFullPath
	#define EXT_IecVarAccGetNodeFullPath
	#define GET_IecVarAccGetNodeFullPath(fl)  CAL_CMGETAPI( "IecVarAccGetNodeFullPath" ) 
	#define CAL_IecVarAccGetNodeFullPath  IecVarAccGetNodeFullPath
	#define CHK_IecVarAccGetNodeFullPath  TRUE
	#define EXP_IecVarAccGetNodeFullPath  CAL_CMEXPAPI( "IecVarAccGetNodeFullPath" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetNodeFullPath
	#define EXT_IecVarAccGetNodeFullPath
	#define GET_IecVarAccGetNodeFullPath(fl)  CAL_CMGETAPI( "IecVarAccGetNodeFullPath" ) 
	#define CAL_IecVarAccGetNodeFullPath  IecVarAccGetNodeFullPath
	#define CHK_IecVarAccGetNodeFullPath  TRUE
	#define EXP_IecVarAccGetNodeFullPath  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNodeFullPath", (RTS_UINTPTR)IecVarAccGetNodeFullPath, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetNodeFullPath
	#define EXT_CmpIecVarAccessIecVarAccGetNodeFullPath
	#define GET_CmpIecVarAccessIecVarAccGetNodeFullPath  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetNodeFullPath pICmpIecVarAccess->IIecVarAccGetNodeFullPath
	#define CHK_CmpIecVarAccessIecVarAccGetNodeFullPath (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetNodeFullPath  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetNodeFullPath
	#define EXT_IecVarAccGetNodeFullPath
	#define GET_IecVarAccGetNodeFullPath(fl)  CAL_CMGETAPI( "IecVarAccGetNodeFullPath" ) 
	#define CAL_IecVarAccGetNodeFullPath pICmpIecVarAccess->IIecVarAccGetNodeFullPath
	#define CHK_IecVarAccGetNodeFullPath (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetNodeFullPath  CAL_CMEXPAPI( "IecVarAccGetNodeFullPath" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetNodeFullPath  PFIECVARACCGETNODEFULLPATH pfIecVarAccGetNodeFullPath;
	#define EXT_IecVarAccGetNodeFullPath  extern PFIECVARACCGETNODEFULLPATH pfIecVarAccGetNodeFullPath;
	#define GET_IecVarAccGetNodeFullPath(fl)  s_pfCMGetAPI2( "IecVarAccGetNodeFullPath", (RTS_VOID_FCTPTR *)&pfIecVarAccGetNodeFullPath, (fl), 0, 0)
	#define CAL_IecVarAccGetNodeFullPath  pfIecVarAccGetNodeFullPath
	#define CHK_IecVarAccGetNodeFullPath  (pfIecVarAccGetNodeFullPath != NULL)
	#define EXP_IecVarAccGetNodeFullPath  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNodeFullPath", (RTS_UINTPTR)IecVarAccGetNodeFullPath, 0, 0) 
#endif




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
int CDECL IecVarAccGetNodeFullPath3(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, char *pszPath, int iMaxPath, RTS_RESULT *pResult);
typedef int (CDECL * PFIECVARACCGETNODEFULLPATH3) (RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, char *pszPath, int iMaxPath, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNODEFULLPATH3_NOTIMPLEMENTED)
	#define USE_IecVarAccGetNodeFullPath3
	#define EXT_IecVarAccGetNodeFullPath3
	#define GET_IecVarAccGetNodeFullPath3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetNodeFullPath3(p0,p1,p2,p3,p4,p5)  (int)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetNodeFullPath3  FALSE
	#define EXP_IecVarAccGetNodeFullPath3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetNodeFullPath3
	#define EXT_IecVarAccGetNodeFullPath3
	#define GET_IecVarAccGetNodeFullPath3(fl)  CAL_CMGETAPI( "IecVarAccGetNodeFullPath3" ) 
	#define CAL_IecVarAccGetNodeFullPath3  IecVarAccGetNodeFullPath3
	#define CHK_IecVarAccGetNodeFullPath3  TRUE
	#define EXP_IecVarAccGetNodeFullPath3  CAL_CMEXPAPI( "IecVarAccGetNodeFullPath3" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetNodeFullPath3
	#define EXT_IecVarAccGetNodeFullPath3
	#define GET_IecVarAccGetNodeFullPath3(fl)  CAL_CMGETAPI( "IecVarAccGetNodeFullPath3" ) 
	#define CAL_IecVarAccGetNodeFullPath3  IecVarAccGetNodeFullPath3
	#define CHK_IecVarAccGetNodeFullPath3  TRUE
	#define EXP_IecVarAccGetNodeFullPath3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNodeFullPath3", (RTS_UINTPTR)IecVarAccGetNodeFullPath3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetNodeFullPath3
	#define EXT_CmpIecVarAccessIecVarAccGetNodeFullPath3
	#define GET_CmpIecVarAccessIecVarAccGetNodeFullPath3  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetNodeFullPath3 pICmpIecVarAccess->IIecVarAccGetNodeFullPath3
	#define CHK_CmpIecVarAccessIecVarAccGetNodeFullPath3 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetNodeFullPath3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetNodeFullPath3
	#define EXT_IecVarAccGetNodeFullPath3
	#define GET_IecVarAccGetNodeFullPath3(fl)  CAL_CMGETAPI( "IecVarAccGetNodeFullPath3" ) 
	#define CAL_IecVarAccGetNodeFullPath3 pICmpIecVarAccess->IIecVarAccGetNodeFullPath3
	#define CHK_IecVarAccGetNodeFullPath3 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetNodeFullPath3  CAL_CMEXPAPI( "IecVarAccGetNodeFullPath3" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetNodeFullPath3  PFIECVARACCGETNODEFULLPATH3 pfIecVarAccGetNodeFullPath3;
	#define EXT_IecVarAccGetNodeFullPath3  extern PFIECVARACCGETNODEFULLPATH3 pfIecVarAccGetNodeFullPath3;
	#define GET_IecVarAccGetNodeFullPath3(fl)  s_pfCMGetAPI2( "IecVarAccGetNodeFullPath3", (RTS_VOID_FCTPTR *)&pfIecVarAccGetNodeFullPath3, (fl), 0, 0)
	#define CAL_IecVarAccGetNodeFullPath3  pfIecVarAccGetNodeFullPath3
	#define CHK_IecVarAccGetNodeFullPath3  (pfIecVarAccGetNodeFullPath3 != NULL)
	#define EXP_IecVarAccGetNodeFullPath3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNodeFullPath3", (RTS_UINTPTR)IecVarAccGetNodeFullPath3, 0, 0) 
#endif




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
int CDECL IecVarAccGetNodeFullPath4(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, char *pszPath, int iMaxPath, RTS_RESULT *pResult);
typedef int (CDECL * PFIECVARACCGETNODEFULLPATH4) (RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, char *pszPath, int iMaxPath, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNODEFULLPATH4_NOTIMPLEMENTED)
	#define USE_IecVarAccGetNodeFullPath4
	#define EXT_IecVarAccGetNodeFullPath4
	#define GET_IecVarAccGetNodeFullPath4(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetNodeFullPath4(p0,p1,p2,p3,p4,p5)  (int)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetNodeFullPath4  FALSE
	#define EXP_IecVarAccGetNodeFullPath4  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetNodeFullPath4
	#define EXT_IecVarAccGetNodeFullPath4
	#define GET_IecVarAccGetNodeFullPath4(fl)  CAL_CMGETAPI( "IecVarAccGetNodeFullPath4" ) 
	#define CAL_IecVarAccGetNodeFullPath4  IecVarAccGetNodeFullPath4
	#define CHK_IecVarAccGetNodeFullPath4  TRUE
	#define EXP_IecVarAccGetNodeFullPath4  CAL_CMEXPAPI( "IecVarAccGetNodeFullPath4" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetNodeFullPath4
	#define EXT_IecVarAccGetNodeFullPath4
	#define GET_IecVarAccGetNodeFullPath4(fl)  CAL_CMGETAPI( "IecVarAccGetNodeFullPath4" ) 
	#define CAL_IecVarAccGetNodeFullPath4  IecVarAccGetNodeFullPath4
	#define CHK_IecVarAccGetNodeFullPath4  TRUE
	#define EXP_IecVarAccGetNodeFullPath4  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNodeFullPath4", (RTS_UINTPTR)IecVarAccGetNodeFullPath4, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetNodeFullPath4
	#define EXT_CmpIecVarAccessIecVarAccGetNodeFullPath4
	#define GET_CmpIecVarAccessIecVarAccGetNodeFullPath4  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetNodeFullPath4 pICmpIecVarAccess->IIecVarAccGetNodeFullPath4
	#define CHK_CmpIecVarAccessIecVarAccGetNodeFullPath4 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetNodeFullPath4  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetNodeFullPath4
	#define EXT_IecVarAccGetNodeFullPath4
	#define GET_IecVarAccGetNodeFullPath4(fl)  CAL_CMGETAPI( "IecVarAccGetNodeFullPath4" ) 
	#define CAL_IecVarAccGetNodeFullPath4 pICmpIecVarAccess->IIecVarAccGetNodeFullPath4
	#define CHK_IecVarAccGetNodeFullPath4 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetNodeFullPath4  CAL_CMEXPAPI( "IecVarAccGetNodeFullPath4" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetNodeFullPath4  PFIECVARACCGETNODEFULLPATH4 pfIecVarAccGetNodeFullPath4;
	#define EXT_IecVarAccGetNodeFullPath4  extern PFIECVARACCGETNODEFULLPATH4 pfIecVarAccGetNodeFullPath4;
	#define GET_IecVarAccGetNodeFullPath4(fl)  s_pfCMGetAPI2( "IecVarAccGetNodeFullPath4", (RTS_VOID_FCTPTR *)&pfIecVarAccGetNodeFullPath4, (fl), 0, 0)
	#define CAL_IecVarAccGetNodeFullPath4  pfIecVarAccGetNodeFullPath4
	#define CHK_IecVarAccGetNodeFullPath4  (pfIecVarAccGetNodeFullPath4 != NULL)
	#define EXP_IecVarAccGetNodeFullPath4  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNodeFullPath4", (RTS_UINTPTR)IecVarAccGetNodeFullPath4, 0, 0) 
#endif




/**
 * <description>Get name of the specified node (e.g. "A")</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to node name</result>
 */
char* CDECL IecVarAccGetNodeName(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
typedef char* (CDECL * PFIECVARACCGETNODENAME) (RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNODENAME_NOTIMPLEMENTED)
	#define USE_IecVarAccGetNodeName
	#define EXT_IecVarAccGetNodeName
	#define GET_IecVarAccGetNodeName(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetNodeName(p0,p1,p2)  (char*)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetNodeName  FALSE
	#define EXP_IecVarAccGetNodeName  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetNodeName
	#define EXT_IecVarAccGetNodeName
	#define GET_IecVarAccGetNodeName(fl)  CAL_CMGETAPI( "IecVarAccGetNodeName" ) 
	#define CAL_IecVarAccGetNodeName  IecVarAccGetNodeName
	#define CHK_IecVarAccGetNodeName  TRUE
	#define EXP_IecVarAccGetNodeName  CAL_CMEXPAPI( "IecVarAccGetNodeName" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetNodeName
	#define EXT_IecVarAccGetNodeName
	#define GET_IecVarAccGetNodeName(fl)  CAL_CMGETAPI( "IecVarAccGetNodeName" ) 
	#define CAL_IecVarAccGetNodeName  IecVarAccGetNodeName
	#define CHK_IecVarAccGetNodeName  TRUE
	#define EXP_IecVarAccGetNodeName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNodeName", (RTS_UINTPTR)IecVarAccGetNodeName, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetNodeName
	#define EXT_CmpIecVarAccessIecVarAccGetNodeName
	#define GET_CmpIecVarAccessIecVarAccGetNodeName  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetNodeName pICmpIecVarAccess->IIecVarAccGetNodeName
	#define CHK_CmpIecVarAccessIecVarAccGetNodeName (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetNodeName  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetNodeName
	#define EXT_IecVarAccGetNodeName
	#define GET_IecVarAccGetNodeName(fl)  CAL_CMGETAPI( "IecVarAccGetNodeName" ) 
	#define CAL_IecVarAccGetNodeName pICmpIecVarAccess->IIecVarAccGetNodeName
	#define CHK_IecVarAccGetNodeName (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetNodeName  CAL_CMEXPAPI( "IecVarAccGetNodeName" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetNodeName  PFIECVARACCGETNODENAME pfIecVarAccGetNodeName;
	#define EXT_IecVarAccGetNodeName  extern PFIECVARACCGETNODENAME pfIecVarAccGetNodeName;
	#define GET_IecVarAccGetNodeName(fl)  s_pfCMGetAPI2( "IecVarAccGetNodeName", (RTS_VOID_FCTPTR *)&pfIecVarAccGetNodeName, (fl), 0, 0)
	#define CAL_IecVarAccGetNodeName  pfIecVarAccGetNodeName
	#define CHK_IecVarAccGetNodeName  (pfIecVarAccGetNodeName != NULL)
	#define EXP_IecVarAccGetNodeName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNodeName", (RTS_UINTPTR)IecVarAccGetNodeName, 0, 0) 
#endif




/**
 * <description>Get name of the specified node (e.g. "A")</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by IecVarAccGetNode3</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to node name</result>
 */
char* CDECL IecVarAccGetNodeName3(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult);
typedef char* (CDECL * PFIECVARACCGETNODENAME3) (RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNODENAME3_NOTIMPLEMENTED)
	#define USE_IecVarAccGetNodeName3
	#define EXT_IecVarAccGetNodeName3
	#define GET_IecVarAccGetNodeName3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetNodeName3(p0,p1,p2,p3)  (char*)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetNodeName3  FALSE
	#define EXP_IecVarAccGetNodeName3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetNodeName3
	#define EXT_IecVarAccGetNodeName3
	#define GET_IecVarAccGetNodeName3(fl)  CAL_CMGETAPI( "IecVarAccGetNodeName3" ) 
	#define CAL_IecVarAccGetNodeName3  IecVarAccGetNodeName3
	#define CHK_IecVarAccGetNodeName3  TRUE
	#define EXP_IecVarAccGetNodeName3  CAL_CMEXPAPI( "IecVarAccGetNodeName3" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetNodeName3
	#define EXT_IecVarAccGetNodeName3
	#define GET_IecVarAccGetNodeName3(fl)  CAL_CMGETAPI( "IecVarAccGetNodeName3" ) 
	#define CAL_IecVarAccGetNodeName3  IecVarAccGetNodeName3
	#define CHK_IecVarAccGetNodeName3  TRUE
	#define EXP_IecVarAccGetNodeName3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNodeName3", (RTS_UINTPTR)IecVarAccGetNodeName3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetNodeName3
	#define EXT_CmpIecVarAccessIecVarAccGetNodeName3
	#define GET_CmpIecVarAccessIecVarAccGetNodeName3  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetNodeName3 pICmpIecVarAccess->IIecVarAccGetNodeName3
	#define CHK_CmpIecVarAccessIecVarAccGetNodeName3 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetNodeName3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetNodeName3
	#define EXT_IecVarAccGetNodeName3
	#define GET_IecVarAccGetNodeName3(fl)  CAL_CMGETAPI( "IecVarAccGetNodeName3" ) 
	#define CAL_IecVarAccGetNodeName3 pICmpIecVarAccess->IIecVarAccGetNodeName3
	#define CHK_IecVarAccGetNodeName3 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetNodeName3  CAL_CMEXPAPI( "IecVarAccGetNodeName3" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetNodeName3  PFIECVARACCGETNODENAME3 pfIecVarAccGetNodeName3;
	#define EXT_IecVarAccGetNodeName3  extern PFIECVARACCGETNODENAME3 pfIecVarAccGetNodeName3;
	#define GET_IecVarAccGetNodeName3(fl)  s_pfCMGetAPI2( "IecVarAccGetNodeName3", (RTS_VOID_FCTPTR *)&pfIecVarAccGetNodeName3, (fl), 0, 0)
	#define CAL_IecVarAccGetNodeName3  pfIecVarAccGetNodeName3
	#define CHK_IecVarAccGetNodeName3  (pfIecVarAccGetNodeName3 != NULL)
	#define EXP_IecVarAccGetNodeName3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNodeName3", (RTS_UINTPTR)IecVarAccGetNodeName3, 0, 0) 
#endif




/**
 * <description>Get name of the specified node (e.g. "A")</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information3 that is retrieved by all functions with VariableInformationStruct3 as a parameter!</param>
 * <param name="pszNodeName" type="IN">Pointer to get nodename</param>
 * <param name="nNodeNameLen" type="IN">Max nodename length</param>
 * <result>Error code</result>
 */
RTS_RESULT CDECL IecVarAccGetNodeName4(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, char *pszNodeName, RTS_UI32 nNodeNameLen);
typedef RTS_RESULT (CDECL * PFIECVARACCGETNODENAME4) (RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, char *pszNodeName, RTS_UI32 nNodeNameLen);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNODENAME4_NOTIMPLEMENTED)
	#define USE_IecVarAccGetNodeName4
	#define EXT_IecVarAccGetNodeName4
	#define GET_IecVarAccGetNodeName4(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetNodeName4(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetNodeName4  FALSE
	#define EXP_IecVarAccGetNodeName4  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetNodeName4
	#define EXT_IecVarAccGetNodeName4
	#define GET_IecVarAccGetNodeName4(fl)  CAL_CMGETAPI( "IecVarAccGetNodeName4" ) 
	#define CAL_IecVarAccGetNodeName4  IecVarAccGetNodeName4
	#define CHK_IecVarAccGetNodeName4  TRUE
	#define EXP_IecVarAccGetNodeName4  CAL_CMEXPAPI( "IecVarAccGetNodeName4" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetNodeName4
	#define EXT_IecVarAccGetNodeName4
	#define GET_IecVarAccGetNodeName4(fl)  CAL_CMGETAPI( "IecVarAccGetNodeName4" ) 
	#define CAL_IecVarAccGetNodeName4  IecVarAccGetNodeName4
	#define CHK_IecVarAccGetNodeName4  TRUE
	#define EXP_IecVarAccGetNodeName4  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNodeName4", (RTS_UINTPTR)IecVarAccGetNodeName4, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetNodeName4
	#define EXT_CmpIecVarAccessIecVarAccGetNodeName4
	#define GET_CmpIecVarAccessIecVarAccGetNodeName4  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetNodeName4 pICmpIecVarAccess->IIecVarAccGetNodeName4
	#define CHK_CmpIecVarAccessIecVarAccGetNodeName4 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetNodeName4  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetNodeName4
	#define EXT_IecVarAccGetNodeName4
	#define GET_IecVarAccGetNodeName4(fl)  CAL_CMGETAPI( "IecVarAccGetNodeName4" ) 
	#define CAL_IecVarAccGetNodeName4 pICmpIecVarAccess->IIecVarAccGetNodeName4
	#define CHK_IecVarAccGetNodeName4 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetNodeName4  CAL_CMEXPAPI( "IecVarAccGetNodeName4" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetNodeName4  PFIECVARACCGETNODENAME4 pfIecVarAccGetNodeName4;
	#define EXT_IecVarAccGetNodeName4  extern PFIECVARACCGETNODENAME4 pfIecVarAccGetNodeName4;
	#define GET_IecVarAccGetNodeName4(fl)  s_pfCMGetAPI2( "IecVarAccGetNodeName4", (RTS_VOID_FCTPTR *)&pfIecVarAccGetNodeName4, (fl), 0, 0)
	#define CAL_IecVarAccGetNodeName4  pfIecVarAccGetNodeName4
	#define CHK_IecVarAccGetNodeName4  (pfIecVarAccGetNodeName4 != NULL)
	#define EXP_IecVarAccGetNodeName4  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNodeName4", (RTS_UINTPTR)IecVarAccGetNodeName4, 0, 0) 
#endif




/**
 * <description>Get access rights of the specified symbolic node</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Access rights</result>
 */
AccessRights CDECL IecVarAccGetAccessRights(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
typedef AccessRights (CDECL * PFIECVARACCGETACCESSRIGHTS) (RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETACCESSRIGHTS_NOTIMPLEMENTED)
	#define USE_IecVarAccGetAccessRights
	#define EXT_IecVarAccGetAccessRights
	#define GET_IecVarAccGetAccessRights(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetAccessRights(p0,p1,p2)  (AccessRights)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetAccessRights  FALSE
	#define EXP_IecVarAccGetAccessRights  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetAccessRights
	#define EXT_IecVarAccGetAccessRights
	#define GET_IecVarAccGetAccessRights(fl)  CAL_CMGETAPI( "IecVarAccGetAccessRights" ) 
	#define CAL_IecVarAccGetAccessRights  IecVarAccGetAccessRights
	#define CHK_IecVarAccGetAccessRights  TRUE
	#define EXP_IecVarAccGetAccessRights  CAL_CMEXPAPI( "IecVarAccGetAccessRights" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetAccessRights
	#define EXT_IecVarAccGetAccessRights
	#define GET_IecVarAccGetAccessRights(fl)  CAL_CMGETAPI( "IecVarAccGetAccessRights" ) 
	#define CAL_IecVarAccGetAccessRights  IecVarAccGetAccessRights
	#define CHK_IecVarAccGetAccessRights  TRUE
	#define EXP_IecVarAccGetAccessRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetAccessRights", (RTS_UINTPTR)IecVarAccGetAccessRights, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetAccessRights
	#define EXT_CmpIecVarAccessIecVarAccGetAccessRights
	#define GET_CmpIecVarAccessIecVarAccGetAccessRights  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetAccessRights pICmpIecVarAccess->IIecVarAccGetAccessRights
	#define CHK_CmpIecVarAccessIecVarAccGetAccessRights (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetAccessRights  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetAccessRights
	#define EXT_IecVarAccGetAccessRights
	#define GET_IecVarAccGetAccessRights(fl)  CAL_CMGETAPI( "IecVarAccGetAccessRights" ) 
	#define CAL_IecVarAccGetAccessRights pICmpIecVarAccess->IIecVarAccGetAccessRights
	#define CHK_IecVarAccGetAccessRights (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetAccessRights  CAL_CMEXPAPI( "IecVarAccGetAccessRights" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetAccessRights  PFIECVARACCGETACCESSRIGHTS pfIecVarAccGetAccessRights;
	#define EXT_IecVarAccGetAccessRights  extern PFIECVARACCGETACCESSRIGHTS pfIecVarAccGetAccessRights;
	#define GET_IecVarAccGetAccessRights(fl)  s_pfCMGetAPI2( "IecVarAccGetAccessRights", (RTS_VOID_FCTPTR *)&pfIecVarAccGetAccessRights, (fl), 0, 0)
	#define CAL_IecVarAccGetAccessRights  pfIecVarAccGetAccessRights
	#define CHK_IecVarAccGetAccessRights  (pfIecVarAccGetAccessRights != NULL)
	#define EXP_IecVarAccGetAccessRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetAccessRights", (RTS_UINTPTR)IecVarAccGetAccessRights, 0, 0) 
#endif




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
void* CDECL IecVarAccGetAddress(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
typedef void* (CDECL * PFIECVARACCGETADDRESS) (RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETADDRESS_NOTIMPLEMENTED)
	#define USE_IecVarAccGetAddress
	#define EXT_IecVarAccGetAddress
	#define GET_IecVarAccGetAddress(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetAddress(p0,p1,p2)  (void*)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetAddress  FALSE
	#define EXP_IecVarAccGetAddress  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetAddress
	#define EXT_IecVarAccGetAddress
	#define GET_IecVarAccGetAddress(fl)  CAL_CMGETAPI( "IecVarAccGetAddress" ) 
	#define CAL_IecVarAccGetAddress  IecVarAccGetAddress
	#define CHK_IecVarAccGetAddress  TRUE
	#define EXP_IecVarAccGetAddress  CAL_CMEXPAPI( "IecVarAccGetAddress" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetAddress
	#define EXT_IecVarAccGetAddress
	#define GET_IecVarAccGetAddress(fl)  CAL_CMGETAPI( "IecVarAccGetAddress" ) 
	#define CAL_IecVarAccGetAddress  IecVarAccGetAddress
	#define CHK_IecVarAccGetAddress  TRUE
	#define EXP_IecVarAccGetAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetAddress", (RTS_UINTPTR)IecVarAccGetAddress, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetAddress
	#define EXT_CmpIecVarAccessIecVarAccGetAddress
	#define GET_CmpIecVarAccessIecVarAccGetAddress  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetAddress pICmpIecVarAccess->IIecVarAccGetAddress
	#define CHK_CmpIecVarAccessIecVarAccGetAddress (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetAddress  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetAddress
	#define EXT_IecVarAccGetAddress
	#define GET_IecVarAccGetAddress(fl)  CAL_CMGETAPI( "IecVarAccGetAddress" ) 
	#define CAL_IecVarAccGetAddress pICmpIecVarAccess->IIecVarAccGetAddress
	#define CHK_IecVarAccGetAddress (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetAddress  CAL_CMEXPAPI( "IecVarAccGetAddress" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetAddress  PFIECVARACCGETADDRESS pfIecVarAccGetAddress;
	#define EXT_IecVarAccGetAddress  extern PFIECVARACCGETADDRESS pfIecVarAccGetAddress;
	#define GET_IecVarAccGetAddress(fl)  s_pfCMGetAPI2( "IecVarAccGetAddress", (RTS_VOID_FCTPTR *)&pfIecVarAccGetAddress, (fl), 0, 0)
	#define CAL_IecVarAccGetAddress  pfIecVarAccGetAddress
	#define CHK_IecVarAccGetAddress  (pfIecVarAccGetAddress != NULL)
	#define EXP_IecVarAccGetAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetAddress", (RTS_UINTPTR)IecVarAccGetAddress, 0, 0) 
#endif




/**
 * <description>Get address of the variable value (including the offset, e.g. for array elements)</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="ulOffset" type="IN">Offset of the node, that is retrieved by IecVarAccGetNode</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to address of the variable value</result>
 */
void* CDECL IecVarAccGetAddress2(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_SIZE ulOffset, RTS_RESULT *pResult);
typedef void* (CDECL * PFIECVARACCGETADDRESS2) (RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_SIZE ulOffset, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETADDRESS2_NOTIMPLEMENTED)
	#define USE_IecVarAccGetAddress2
	#define EXT_IecVarAccGetAddress2
	#define GET_IecVarAccGetAddress2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetAddress2(p0,p1,p2,p3)  (void*)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetAddress2  FALSE
	#define EXP_IecVarAccGetAddress2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetAddress2
	#define EXT_IecVarAccGetAddress2
	#define GET_IecVarAccGetAddress2(fl)  CAL_CMGETAPI( "IecVarAccGetAddress2" ) 
	#define CAL_IecVarAccGetAddress2  IecVarAccGetAddress2
	#define CHK_IecVarAccGetAddress2  TRUE
	#define EXP_IecVarAccGetAddress2  CAL_CMEXPAPI( "IecVarAccGetAddress2" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetAddress2
	#define EXT_IecVarAccGetAddress2
	#define GET_IecVarAccGetAddress2(fl)  CAL_CMGETAPI( "IecVarAccGetAddress2" ) 
	#define CAL_IecVarAccGetAddress2  IecVarAccGetAddress2
	#define CHK_IecVarAccGetAddress2  TRUE
	#define EXP_IecVarAccGetAddress2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetAddress2", (RTS_UINTPTR)IecVarAccGetAddress2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetAddress2
	#define EXT_CmpIecVarAccessIecVarAccGetAddress2
	#define GET_CmpIecVarAccessIecVarAccGetAddress2  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetAddress2 pICmpIecVarAccess->IIecVarAccGetAddress2
	#define CHK_CmpIecVarAccessIecVarAccGetAddress2 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetAddress2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetAddress2
	#define EXT_IecVarAccGetAddress2
	#define GET_IecVarAccGetAddress2(fl)  CAL_CMGETAPI( "IecVarAccGetAddress2" ) 
	#define CAL_IecVarAccGetAddress2 pICmpIecVarAccess->IIecVarAccGetAddress2
	#define CHK_IecVarAccGetAddress2 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetAddress2  CAL_CMEXPAPI( "IecVarAccGetAddress2" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetAddress2  PFIECVARACCGETADDRESS2 pfIecVarAccGetAddress2;
	#define EXT_IecVarAccGetAddress2  extern PFIECVARACCGETADDRESS2 pfIecVarAccGetAddress2;
	#define GET_IecVarAccGetAddress2(fl)  s_pfCMGetAPI2( "IecVarAccGetAddress2", (RTS_VOID_FCTPTR *)&pfIecVarAccGetAddress2, (fl), 0, 0)
	#define CAL_IecVarAccGetAddress2  pfIecVarAccGetAddress2
	#define CHK_IecVarAccGetAddress2  (pfIecVarAccGetAddress2 != NULL)
	#define EXP_IecVarAccGetAddress2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetAddress2", (RTS_UINTPTR)IecVarAccGetAddress2, 0, 0) 
#endif




/**
 * <description>Get address of the variable value (including the offset, e.g. for array elements)</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by IecVarAccGetNode3</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to address of the variable value</result>
 */
void* CDECL IecVarAccGetAddress3(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult);
typedef void* (CDECL * PFIECVARACCGETADDRESS3) (RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETADDRESS3_NOTIMPLEMENTED)
	#define USE_IecVarAccGetAddress3
	#define EXT_IecVarAccGetAddress3
	#define GET_IecVarAccGetAddress3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetAddress3(p0,p1,p2,p3)  (void*)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetAddress3  FALSE
	#define EXP_IecVarAccGetAddress3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetAddress3
	#define EXT_IecVarAccGetAddress3
	#define GET_IecVarAccGetAddress3(fl)  CAL_CMGETAPI( "IecVarAccGetAddress3" ) 
	#define CAL_IecVarAccGetAddress3  IecVarAccGetAddress3
	#define CHK_IecVarAccGetAddress3  TRUE
	#define EXP_IecVarAccGetAddress3  CAL_CMEXPAPI( "IecVarAccGetAddress3" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetAddress3
	#define EXT_IecVarAccGetAddress3
	#define GET_IecVarAccGetAddress3(fl)  CAL_CMGETAPI( "IecVarAccGetAddress3" ) 
	#define CAL_IecVarAccGetAddress3  IecVarAccGetAddress3
	#define CHK_IecVarAccGetAddress3  TRUE
	#define EXP_IecVarAccGetAddress3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetAddress3", (RTS_UINTPTR)IecVarAccGetAddress3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetAddress3
	#define EXT_CmpIecVarAccessIecVarAccGetAddress3
	#define GET_CmpIecVarAccessIecVarAccGetAddress3  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetAddress3 pICmpIecVarAccess->IIecVarAccGetAddress3
	#define CHK_CmpIecVarAccessIecVarAccGetAddress3 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetAddress3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetAddress3
	#define EXT_IecVarAccGetAddress3
	#define GET_IecVarAccGetAddress3(fl)  CAL_CMGETAPI( "IecVarAccGetAddress3" ) 
	#define CAL_IecVarAccGetAddress3 pICmpIecVarAccess->IIecVarAccGetAddress3
	#define CHK_IecVarAccGetAddress3 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetAddress3  CAL_CMEXPAPI( "IecVarAccGetAddress3" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetAddress3  PFIECVARACCGETADDRESS3 pfIecVarAccGetAddress3;
	#define EXT_IecVarAccGetAddress3  extern PFIECVARACCGETADDRESS3 pfIecVarAccGetAddress3;
	#define GET_IecVarAccGetAddress3(fl)  s_pfCMGetAPI2( "IecVarAccGetAddress3", (RTS_VOID_FCTPTR *)&pfIecVarAccGetAddress3, (fl), 0, 0)
	#define CAL_IecVarAccGetAddress3  pfIecVarAccGetAddress3
	#define CHK_IecVarAccGetAddress3  (pfIecVarAccGetAddress3 != NULL)
	#define EXP_IecVarAccGetAddress3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetAddress3", (RTS_UINTPTR)IecVarAccGetAddress3, 0, 0) 
#endif




/**
 * <description>Get node type of the specified node (leaf or branch node)</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Node type</result>
 */
TreeNodeType CDECL IecVarAccGetNodeType(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
typedef TreeNodeType (CDECL * PFIECVARACCGETNODETYPE) (RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNODETYPE_NOTIMPLEMENTED)
	#define USE_IecVarAccGetNodeType
	#define EXT_IecVarAccGetNodeType
	#define GET_IecVarAccGetNodeType(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetNodeType(p0,p1,p2)  (TreeNodeType)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetNodeType  FALSE
	#define EXP_IecVarAccGetNodeType  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetNodeType
	#define EXT_IecVarAccGetNodeType
	#define GET_IecVarAccGetNodeType(fl)  CAL_CMGETAPI( "IecVarAccGetNodeType" ) 
	#define CAL_IecVarAccGetNodeType  IecVarAccGetNodeType
	#define CHK_IecVarAccGetNodeType  TRUE
	#define EXP_IecVarAccGetNodeType  CAL_CMEXPAPI( "IecVarAccGetNodeType" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetNodeType
	#define EXT_IecVarAccGetNodeType
	#define GET_IecVarAccGetNodeType(fl)  CAL_CMGETAPI( "IecVarAccGetNodeType" ) 
	#define CAL_IecVarAccGetNodeType  IecVarAccGetNodeType
	#define CHK_IecVarAccGetNodeType  TRUE
	#define EXP_IecVarAccGetNodeType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNodeType", (RTS_UINTPTR)IecVarAccGetNodeType, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetNodeType
	#define EXT_CmpIecVarAccessIecVarAccGetNodeType
	#define GET_CmpIecVarAccessIecVarAccGetNodeType  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetNodeType pICmpIecVarAccess->IIecVarAccGetNodeType
	#define CHK_CmpIecVarAccessIecVarAccGetNodeType (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetNodeType  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetNodeType
	#define EXT_IecVarAccGetNodeType
	#define GET_IecVarAccGetNodeType(fl)  CAL_CMGETAPI( "IecVarAccGetNodeType" ) 
	#define CAL_IecVarAccGetNodeType pICmpIecVarAccess->IIecVarAccGetNodeType
	#define CHK_IecVarAccGetNodeType (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetNodeType  CAL_CMEXPAPI( "IecVarAccGetNodeType" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetNodeType  PFIECVARACCGETNODETYPE pfIecVarAccGetNodeType;
	#define EXT_IecVarAccGetNodeType  extern PFIECVARACCGETNODETYPE pfIecVarAccGetNodeType;
	#define GET_IecVarAccGetNodeType(fl)  s_pfCMGetAPI2( "IecVarAccGetNodeType", (RTS_VOID_FCTPTR *)&pfIecVarAccGetNodeType, (fl), 0, 0)
	#define CAL_IecVarAccGetNodeType  pfIecVarAccGetNodeType
	#define CHK_IecVarAccGetNodeType  (pfIecVarAccGetNodeType != NULL)
	#define EXP_IecVarAccGetNodeType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNodeType", (RTS_UINTPTR)IecVarAccGetNodeType, 0, 0) 
#endif




/**
 * <description>Get the value size in bytes of the specified node. If it is an array, it returns the complete size
 *	of the array (e.g. "C[5]": Returns 15 if it is a byte array with 15 elements)</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Size in bytes of the value</result>
 */
RTS_SIZE CDECL IecVarAccGetSize(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFIECVARACCGETSIZE) (RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETSIZE_NOTIMPLEMENTED)
	#define USE_IecVarAccGetSize
	#define EXT_IecVarAccGetSize
	#define GET_IecVarAccGetSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetSize(p0,p1,p2)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetSize  FALSE
	#define EXP_IecVarAccGetSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetSize
	#define EXT_IecVarAccGetSize
	#define GET_IecVarAccGetSize(fl)  CAL_CMGETAPI( "IecVarAccGetSize" ) 
	#define CAL_IecVarAccGetSize  IecVarAccGetSize
	#define CHK_IecVarAccGetSize  TRUE
	#define EXP_IecVarAccGetSize  CAL_CMEXPAPI( "IecVarAccGetSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetSize
	#define EXT_IecVarAccGetSize
	#define GET_IecVarAccGetSize(fl)  CAL_CMGETAPI( "IecVarAccGetSize" ) 
	#define CAL_IecVarAccGetSize  IecVarAccGetSize
	#define CHK_IecVarAccGetSize  TRUE
	#define EXP_IecVarAccGetSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetSize", (RTS_UINTPTR)IecVarAccGetSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetSize
	#define EXT_CmpIecVarAccessIecVarAccGetSize
	#define GET_CmpIecVarAccessIecVarAccGetSize  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetSize pICmpIecVarAccess->IIecVarAccGetSize
	#define CHK_CmpIecVarAccessIecVarAccGetSize (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetSize
	#define EXT_IecVarAccGetSize
	#define GET_IecVarAccGetSize(fl)  CAL_CMGETAPI( "IecVarAccGetSize" ) 
	#define CAL_IecVarAccGetSize pICmpIecVarAccess->IIecVarAccGetSize
	#define CHK_IecVarAccGetSize (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetSize  CAL_CMEXPAPI( "IecVarAccGetSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetSize  PFIECVARACCGETSIZE pfIecVarAccGetSize;
	#define EXT_IecVarAccGetSize  extern PFIECVARACCGETSIZE pfIecVarAccGetSize;
	#define GET_IecVarAccGetSize(fl)  s_pfCMGetAPI2( "IecVarAccGetSize", (RTS_VOID_FCTPTR *)&pfIecVarAccGetSize, (fl), 0, 0)
	#define CAL_IecVarAccGetSize  pfIecVarAccGetSize
	#define CHK_IecVarAccGetSize  (pfIecVarAccGetSize != NULL)
	#define EXP_IecVarAccGetSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetSize", (RTS_UINTPTR)IecVarAccGetSize, 0, 0) 
#endif




/**
 * <description>Get the value size in bytes of the specified node. It returns always the real size of the node value
 *	(e.g. "C[5]": Returns 1 if it is a byte array)</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="ulOffset" type="IN">Offset of the node (is retrieved by IecVarAccGetNode)</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Size in bytes of the value</result>
 */
RTS_SIZE CDECL IecVarAccGetSize2(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_SIZE ulOffset, RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFIECVARACCGETSIZE2) (RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_SIZE ulOffset, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETSIZE2_NOTIMPLEMENTED)
	#define USE_IecVarAccGetSize2
	#define EXT_IecVarAccGetSize2
	#define GET_IecVarAccGetSize2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetSize2(p0,p1,p2,p3)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetSize2  FALSE
	#define EXP_IecVarAccGetSize2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetSize2
	#define EXT_IecVarAccGetSize2
	#define GET_IecVarAccGetSize2(fl)  CAL_CMGETAPI( "IecVarAccGetSize2" ) 
	#define CAL_IecVarAccGetSize2  IecVarAccGetSize2
	#define CHK_IecVarAccGetSize2  TRUE
	#define EXP_IecVarAccGetSize2  CAL_CMEXPAPI( "IecVarAccGetSize2" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetSize2
	#define EXT_IecVarAccGetSize2
	#define GET_IecVarAccGetSize2(fl)  CAL_CMGETAPI( "IecVarAccGetSize2" ) 
	#define CAL_IecVarAccGetSize2  IecVarAccGetSize2
	#define CHK_IecVarAccGetSize2  TRUE
	#define EXP_IecVarAccGetSize2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetSize2", (RTS_UINTPTR)IecVarAccGetSize2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetSize2
	#define EXT_CmpIecVarAccessIecVarAccGetSize2
	#define GET_CmpIecVarAccessIecVarAccGetSize2  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetSize2 pICmpIecVarAccess->IIecVarAccGetSize2
	#define CHK_CmpIecVarAccessIecVarAccGetSize2 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetSize2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetSize2
	#define EXT_IecVarAccGetSize2
	#define GET_IecVarAccGetSize2(fl)  CAL_CMGETAPI( "IecVarAccGetSize2" ) 
	#define CAL_IecVarAccGetSize2 pICmpIecVarAccess->IIecVarAccGetSize2
	#define CHK_IecVarAccGetSize2 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetSize2  CAL_CMEXPAPI( "IecVarAccGetSize2" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetSize2  PFIECVARACCGETSIZE2 pfIecVarAccGetSize2;
	#define EXT_IecVarAccGetSize2  extern PFIECVARACCGETSIZE2 pfIecVarAccGetSize2;
	#define GET_IecVarAccGetSize2(fl)  s_pfCMGetAPI2( "IecVarAccGetSize2", (RTS_VOID_FCTPTR *)&pfIecVarAccGetSize2, (fl), 0, 0)
	#define CAL_IecVarAccGetSize2  pfIecVarAccGetSize2
	#define CHK_IecVarAccGetSize2  (pfIecVarAccGetSize2 != NULL)
	#define EXP_IecVarAccGetSize2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetSize2", (RTS_UINTPTR)IecVarAccGetSize2, 0, 0) 
#endif




/**
 * <description>Get the value size in bytes of the specified node. It returns always the real size of the node value
 *	(e.g. "C[5]": Returns 1 if it is a byte array)</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by IecVarAccGetNode3</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Size in bytes of the value of the specified node</result>
 */
RTS_SIZE CDECL IecVarAccGetSize3(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFIECVARACCGETSIZE3) (RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETSIZE3_NOTIMPLEMENTED)
	#define USE_IecVarAccGetSize3
	#define EXT_IecVarAccGetSize3
	#define GET_IecVarAccGetSize3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetSize3(p0,p1,p2,p3)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetSize3  FALSE
	#define EXP_IecVarAccGetSize3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetSize3
	#define EXT_IecVarAccGetSize3
	#define GET_IecVarAccGetSize3(fl)  CAL_CMGETAPI( "IecVarAccGetSize3" ) 
	#define CAL_IecVarAccGetSize3  IecVarAccGetSize3
	#define CHK_IecVarAccGetSize3  TRUE
	#define EXP_IecVarAccGetSize3  CAL_CMEXPAPI( "IecVarAccGetSize3" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetSize3
	#define EXT_IecVarAccGetSize3
	#define GET_IecVarAccGetSize3(fl)  CAL_CMGETAPI( "IecVarAccGetSize3" ) 
	#define CAL_IecVarAccGetSize3  IecVarAccGetSize3
	#define CHK_IecVarAccGetSize3  TRUE
	#define EXP_IecVarAccGetSize3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetSize3", (RTS_UINTPTR)IecVarAccGetSize3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetSize3
	#define EXT_CmpIecVarAccessIecVarAccGetSize3
	#define GET_CmpIecVarAccessIecVarAccGetSize3  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetSize3 pICmpIecVarAccess->IIecVarAccGetSize3
	#define CHK_CmpIecVarAccessIecVarAccGetSize3 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetSize3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetSize3
	#define EXT_IecVarAccGetSize3
	#define GET_IecVarAccGetSize3(fl)  CAL_CMGETAPI( "IecVarAccGetSize3" ) 
	#define CAL_IecVarAccGetSize3 pICmpIecVarAccess->IIecVarAccGetSize3
	#define CHK_IecVarAccGetSize3 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetSize3  CAL_CMEXPAPI( "IecVarAccGetSize3" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetSize3  PFIECVARACCGETSIZE3 pfIecVarAccGetSize3;
	#define EXT_IecVarAccGetSize3  extern PFIECVARACCGETSIZE3 pfIecVarAccGetSize3;
	#define GET_IecVarAccGetSize3(fl)  s_pfCMGetAPI2( "IecVarAccGetSize3", (RTS_VOID_FCTPTR *)&pfIecVarAccGetSize3, (fl), 0, 0)
	#define CAL_IecVarAccGetSize3  pfIecVarAccGetSize3
	#define CHK_IecVarAccGetSize3  (pfIecVarAccGetSize3 != NULL)
	#define EXP_IecVarAccGetSize3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetSize3", (RTS_UINTPTR)IecVarAccGetSize3, 0, 0) 
#endif




/**
 * <description>Get the swap size of the specified node (can be used to change the byte order)</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Swap size:	8/4/2/1</result>
 */
RTS_SIZE CDECL IecVarAccGetSwapSize(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFIECVARACCGETSWAPSIZE) (RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETSWAPSIZE_NOTIMPLEMENTED)
	#define USE_IecVarAccGetSwapSize
	#define EXT_IecVarAccGetSwapSize
	#define GET_IecVarAccGetSwapSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetSwapSize(p0,p1,p2)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetSwapSize  FALSE
	#define EXP_IecVarAccGetSwapSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetSwapSize
	#define EXT_IecVarAccGetSwapSize
	#define GET_IecVarAccGetSwapSize(fl)  CAL_CMGETAPI( "IecVarAccGetSwapSize" ) 
	#define CAL_IecVarAccGetSwapSize  IecVarAccGetSwapSize
	#define CHK_IecVarAccGetSwapSize  TRUE
	#define EXP_IecVarAccGetSwapSize  CAL_CMEXPAPI( "IecVarAccGetSwapSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetSwapSize
	#define EXT_IecVarAccGetSwapSize
	#define GET_IecVarAccGetSwapSize(fl)  CAL_CMGETAPI( "IecVarAccGetSwapSize" ) 
	#define CAL_IecVarAccGetSwapSize  IecVarAccGetSwapSize
	#define CHK_IecVarAccGetSwapSize  TRUE
	#define EXP_IecVarAccGetSwapSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetSwapSize", (RTS_UINTPTR)IecVarAccGetSwapSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetSwapSize
	#define EXT_CmpIecVarAccessIecVarAccGetSwapSize
	#define GET_CmpIecVarAccessIecVarAccGetSwapSize  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetSwapSize pICmpIecVarAccess->IIecVarAccGetSwapSize
	#define CHK_CmpIecVarAccessIecVarAccGetSwapSize (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetSwapSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetSwapSize
	#define EXT_IecVarAccGetSwapSize
	#define GET_IecVarAccGetSwapSize(fl)  CAL_CMGETAPI( "IecVarAccGetSwapSize" ) 
	#define CAL_IecVarAccGetSwapSize pICmpIecVarAccess->IIecVarAccGetSwapSize
	#define CHK_IecVarAccGetSwapSize (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetSwapSize  CAL_CMEXPAPI( "IecVarAccGetSwapSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetSwapSize  PFIECVARACCGETSWAPSIZE pfIecVarAccGetSwapSize;
	#define EXT_IecVarAccGetSwapSize  extern PFIECVARACCGETSWAPSIZE pfIecVarAccGetSwapSize;
	#define GET_IecVarAccGetSwapSize(fl)  s_pfCMGetAPI2( "IecVarAccGetSwapSize", (RTS_VOID_FCTPTR *)&pfIecVarAccGetSwapSize, (fl), 0, 0)
	#define CAL_IecVarAccGetSwapSize  pfIecVarAccGetSwapSize
	#define CHK_IecVarAccGetSwapSize  (pfIecVarAccGetSwapSize != NULL)
	#define EXP_IecVarAccGetSwapSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetSwapSize", (RTS_UINTPTR)IecVarAccGetSwapSize, 0, 0) 
#endif




/**
 * <description>Get the type class of the specified node</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Type class</result>
 */
TypeClass3 CDECL IecVarAccGetTypeClass(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
typedef TypeClass3 (CDECL * PFIECVARACCGETTYPECLASS) (RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETTYPECLASS_NOTIMPLEMENTED)
	#define USE_IecVarAccGetTypeClass
	#define EXT_IecVarAccGetTypeClass
	#define GET_IecVarAccGetTypeClass(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetTypeClass(p0,p1,p2)  (TypeClass3)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetTypeClass  FALSE
	#define EXP_IecVarAccGetTypeClass  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetTypeClass
	#define EXT_IecVarAccGetTypeClass
	#define GET_IecVarAccGetTypeClass(fl)  CAL_CMGETAPI( "IecVarAccGetTypeClass" ) 
	#define CAL_IecVarAccGetTypeClass  IecVarAccGetTypeClass
	#define CHK_IecVarAccGetTypeClass  TRUE
	#define EXP_IecVarAccGetTypeClass  CAL_CMEXPAPI( "IecVarAccGetTypeClass" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetTypeClass
	#define EXT_IecVarAccGetTypeClass
	#define GET_IecVarAccGetTypeClass(fl)  CAL_CMGETAPI( "IecVarAccGetTypeClass" ) 
	#define CAL_IecVarAccGetTypeClass  IecVarAccGetTypeClass
	#define CHK_IecVarAccGetTypeClass  TRUE
	#define EXP_IecVarAccGetTypeClass  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetTypeClass", (RTS_UINTPTR)IecVarAccGetTypeClass, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetTypeClass
	#define EXT_CmpIecVarAccessIecVarAccGetTypeClass
	#define GET_CmpIecVarAccessIecVarAccGetTypeClass  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetTypeClass pICmpIecVarAccess->IIecVarAccGetTypeClass
	#define CHK_CmpIecVarAccessIecVarAccGetTypeClass (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetTypeClass  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetTypeClass
	#define EXT_IecVarAccGetTypeClass
	#define GET_IecVarAccGetTypeClass(fl)  CAL_CMGETAPI( "IecVarAccGetTypeClass" ) 
	#define CAL_IecVarAccGetTypeClass pICmpIecVarAccess->IIecVarAccGetTypeClass
	#define CHK_IecVarAccGetTypeClass (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetTypeClass  CAL_CMEXPAPI( "IecVarAccGetTypeClass" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetTypeClass  PFIECVARACCGETTYPECLASS pfIecVarAccGetTypeClass;
	#define EXT_IecVarAccGetTypeClass  extern PFIECVARACCGETTYPECLASS pfIecVarAccGetTypeClass;
	#define GET_IecVarAccGetTypeClass(fl)  s_pfCMGetAPI2( "IecVarAccGetTypeClass", (RTS_VOID_FCTPTR *)&pfIecVarAccGetTypeClass, (fl), 0, 0)
	#define CAL_IecVarAccGetTypeClass  pfIecVarAccGetTypeClass
	#define CHK_IecVarAccGetTypeClass  (pfIecVarAccGetTypeClass != NULL)
	#define EXP_IecVarAccGetTypeClass  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetTypeClass", (RTS_UINTPTR)IecVarAccGetTypeClass, 0, 0) 
#endif




/**
 * <description>Get the type class of the specified node</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by IecVarAccGetNode3</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Type class</result>
 */
TypeClass3 CDECL IecVarAccGetTypeClass3(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult);
typedef TypeClass3 (CDECL * PFIECVARACCGETTYPECLASS3) (RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETTYPECLASS3_NOTIMPLEMENTED)
	#define USE_IecVarAccGetTypeClass3
	#define EXT_IecVarAccGetTypeClass3
	#define GET_IecVarAccGetTypeClass3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetTypeClass3(p0,p1,p2,p3)  (TypeClass3)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetTypeClass3  FALSE
	#define EXP_IecVarAccGetTypeClass3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetTypeClass3
	#define EXT_IecVarAccGetTypeClass3
	#define GET_IecVarAccGetTypeClass3(fl)  CAL_CMGETAPI( "IecVarAccGetTypeClass3" ) 
	#define CAL_IecVarAccGetTypeClass3  IecVarAccGetTypeClass3
	#define CHK_IecVarAccGetTypeClass3  TRUE
	#define EXP_IecVarAccGetTypeClass3  CAL_CMEXPAPI( "IecVarAccGetTypeClass3" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetTypeClass3
	#define EXT_IecVarAccGetTypeClass3
	#define GET_IecVarAccGetTypeClass3(fl)  CAL_CMGETAPI( "IecVarAccGetTypeClass3" ) 
	#define CAL_IecVarAccGetTypeClass3  IecVarAccGetTypeClass3
	#define CHK_IecVarAccGetTypeClass3  TRUE
	#define EXP_IecVarAccGetTypeClass3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetTypeClass3", (RTS_UINTPTR)IecVarAccGetTypeClass3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetTypeClass3
	#define EXT_CmpIecVarAccessIecVarAccGetTypeClass3
	#define GET_CmpIecVarAccessIecVarAccGetTypeClass3  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetTypeClass3 pICmpIecVarAccess->IIecVarAccGetTypeClass3
	#define CHK_CmpIecVarAccessIecVarAccGetTypeClass3 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetTypeClass3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetTypeClass3
	#define EXT_IecVarAccGetTypeClass3
	#define GET_IecVarAccGetTypeClass3(fl)  CAL_CMGETAPI( "IecVarAccGetTypeClass3" ) 
	#define CAL_IecVarAccGetTypeClass3 pICmpIecVarAccess->IIecVarAccGetTypeClass3
	#define CHK_IecVarAccGetTypeClass3 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetTypeClass3  CAL_CMEXPAPI( "IecVarAccGetTypeClass3" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetTypeClass3  PFIECVARACCGETTYPECLASS3 pfIecVarAccGetTypeClass3;
	#define EXT_IecVarAccGetTypeClass3  extern PFIECVARACCGETTYPECLASS3 pfIecVarAccGetTypeClass3;
	#define GET_IecVarAccGetTypeClass3(fl)  s_pfCMGetAPI2( "IecVarAccGetTypeClass3", (RTS_VOID_FCTPTR *)&pfIecVarAccGetTypeClass3, (fl), 0, 0)
	#define CAL_IecVarAccGetTypeClass3  pfIecVarAccGetTypeClass3
	#define CHK_IecVarAccGetTypeClass3  (pfIecVarAccGetTypeClass3 != NULL)
	#define EXP_IecVarAccGetTypeClass3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetTypeClass3", (RTS_UINTPTR)IecVarAccGetTypeClass3, 0, 0) 
#endif




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
RTS_SIZE CDECL IecVarAccGetValue(RTS_HANDLE hInterface, RTS_HANDLE hNode, void *pDest, RTS_SIZE ulOffset, RTS_SIZE ulSize, RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFIECVARACCGETVALUE) (RTS_HANDLE hInterface, RTS_HANDLE hNode, void *pDest, RTS_SIZE ulOffset, RTS_SIZE ulSize, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETVALUE_NOTIMPLEMENTED)
	#define USE_IecVarAccGetValue
	#define EXT_IecVarAccGetValue
	#define GET_IecVarAccGetValue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetValue(p0,p1,p2,p3,p4,p5)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetValue  FALSE
	#define EXP_IecVarAccGetValue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetValue
	#define EXT_IecVarAccGetValue
	#define GET_IecVarAccGetValue(fl)  CAL_CMGETAPI( "IecVarAccGetValue" ) 
	#define CAL_IecVarAccGetValue  IecVarAccGetValue
	#define CHK_IecVarAccGetValue  TRUE
	#define EXP_IecVarAccGetValue  CAL_CMEXPAPI( "IecVarAccGetValue" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetValue
	#define EXT_IecVarAccGetValue
	#define GET_IecVarAccGetValue(fl)  CAL_CMGETAPI( "IecVarAccGetValue" ) 
	#define CAL_IecVarAccGetValue  IecVarAccGetValue
	#define CHK_IecVarAccGetValue  TRUE
	#define EXP_IecVarAccGetValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetValue", (RTS_UINTPTR)IecVarAccGetValue, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetValue
	#define EXT_CmpIecVarAccessIecVarAccGetValue
	#define GET_CmpIecVarAccessIecVarAccGetValue  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetValue pICmpIecVarAccess->IIecVarAccGetValue
	#define CHK_CmpIecVarAccessIecVarAccGetValue (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetValue  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetValue
	#define EXT_IecVarAccGetValue
	#define GET_IecVarAccGetValue(fl)  CAL_CMGETAPI( "IecVarAccGetValue" ) 
	#define CAL_IecVarAccGetValue pICmpIecVarAccess->IIecVarAccGetValue
	#define CHK_IecVarAccGetValue (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetValue  CAL_CMEXPAPI( "IecVarAccGetValue" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetValue  PFIECVARACCGETVALUE pfIecVarAccGetValue;
	#define EXT_IecVarAccGetValue  extern PFIECVARACCGETVALUE pfIecVarAccGetValue;
	#define GET_IecVarAccGetValue(fl)  s_pfCMGetAPI2( "IecVarAccGetValue", (RTS_VOID_FCTPTR *)&pfIecVarAccGetValue, (fl), 0, 0)
	#define CAL_IecVarAccGetValue  pfIecVarAccGetValue
	#define CHK_IecVarAccGetValue  (pfIecVarAccGetValue != NULL)
	#define EXP_IecVarAccGetValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetValue", (RTS_UINTPTR)IecVarAccGetValue, 0, 0) 
#endif




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
RTS_SIZE CDECL IecVarAccGetValue3(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, void *pDest, RTS_SIZE ulSize, RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFIECVARACCGETVALUE3) (RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, void *pDest, RTS_SIZE ulSize, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETVALUE3_NOTIMPLEMENTED)
	#define USE_IecVarAccGetValue3
	#define EXT_IecVarAccGetValue3
	#define GET_IecVarAccGetValue3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetValue3(p0,p1,p2,p3,p4,p5)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetValue3  FALSE
	#define EXP_IecVarAccGetValue3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetValue3
	#define EXT_IecVarAccGetValue3
	#define GET_IecVarAccGetValue3(fl)  CAL_CMGETAPI( "IecVarAccGetValue3" ) 
	#define CAL_IecVarAccGetValue3  IecVarAccGetValue3
	#define CHK_IecVarAccGetValue3  TRUE
	#define EXP_IecVarAccGetValue3  CAL_CMEXPAPI( "IecVarAccGetValue3" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetValue3
	#define EXT_IecVarAccGetValue3
	#define GET_IecVarAccGetValue3(fl)  CAL_CMGETAPI( "IecVarAccGetValue3" ) 
	#define CAL_IecVarAccGetValue3  IecVarAccGetValue3
	#define CHK_IecVarAccGetValue3  TRUE
	#define EXP_IecVarAccGetValue3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetValue3", (RTS_UINTPTR)IecVarAccGetValue3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetValue3
	#define EXT_CmpIecVarAccessIecVarAccGetValue3
	#define GET_CmpIecVarAccessIecVarAccGetValue3  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetValue3 pICmpIecVarAccess->IIecVarAccGetValue3
	#define CHK_CmpIecVarAccessIecVarAccGetValue3 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetValue3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetValue3
	#define EXT_IecVarAccGetValue3
	#define GET_IecVarAccGetValue3(fl)  CAL_CMGETAPI( "IecVarAccGetValue3" ) 
	#define CAL_IecVarAccGetValue3 pICmpIecVarAccess->IIecVarAccGetValue3
	#define CHK_IecVarAccGetValue3 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetValue3  CAL_CMEXPAPI( "IecVarAccGetValue3" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetValue3  PFIECVARACCGETVALUE3 pfIecVarAccGetValue3;
	#define EXT_IecVarAccGetValue3  extern PFIECVARACCGETVALUE3 pfIecVarAccGetValue3;
	#define GET_IecVarAccGetValue3(fl)  s_pfCMGetAPI2( "IecVarAccGetValue3", (RTS_VOID_FCTPTR *)&pfIecVarAccGetValue3, (fl), 0, 0)
	#define CAL_IecVarAccGetValue3  pfIecVarAccGetValue3
	#define CHK_IecVarAccGetValue3  (pfIecVarAccGetValue3 != NULL)
	#define EXP_IecVarAccGetValue3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetValue3", (RTS_UINTPTR)IecVarAccGetValue3, 0, 0) 
#endif




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
RTS_SIZE CDECL IecVarAccSetValue(RTS_HANDLE hInterface, RTS_HANDLE hNode, void *pSrc, RTS_SIZE ulOffset, RTS_SIZE ulSize, RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFIECVARACCSETVALUE) (RTS_HANDLE hInterface, RTS_HANDLE hNode, void *pSrc, RTS_SIZE ulOffset, RTS_SIZE ulSize, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCSETVALUE_NOTIMPLEMENTED)
	#define USE_IecVarAccSetValue
	#define EXT_IecVarAccSetValue
	#define GET_IecVarAccSetValue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccSetValue(p0,p1,p2,p3,p4,p5)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccSetValue  FALSE
	#define EXP_IecVarAccSetValue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccSetValue
	#define EXT_IecVarAccSetValue
	#define GET_IecVarAccSetValue(fl)  CAL_CMGETAPI( "IecVarAccSetValue" ) 
	#define CAL_IecVarAccSetValue  IecVarAccSetValue
	#define CHK_IecVarAccSetValue  TRUE
	#define EXP_IecVarAccSetValue  CAL_CMEXPAPI( "IecVarAccSetValue" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccSetValue
	#define EXT_IecVarAccSetValue
	#define GET_IecVarAccSetValue(fl)  CAL_CMGETAPI( "IecVarAccSetValue" ) 
	#define CAL_IecVarAccSetValue  IecVarAccSetValue
	#define CHK_IecVarAccSetValue  TRUE
	#define EXP_IecVarAccSetValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccSetValue", (RTS_UINTPTR)IecVarAccSetValue, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccSetValue
	#define EXT_CmpIecVarAccessIecVarAccSetValue
	#define GET_CmpIecVarAccessIecVarAccSetValue  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccSetValue pICmpIecVarAccess->IIecVarAccSetValue
	#define CHK_CmpIecVarAccessIecVarAccSetValue (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccSetValue  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccSetValue
	#define EXT_IecVarAccSetValue
	#define GET_IecVarAccSetValue(fl)  CAL_CMGETAPI( "IecVarAccSetValue" ) 
	#define CAL_IecVarAccSetValue pICmpIecVarAccess->IIecVarAccSetValue
	#define CHK_IecVarAccSetValue (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccSetValue  CAL_CMEXPAPI( "IecVarAccSetValue" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccSetValue  PFIECVARACCSETVALUE pfIecVarAccSetValue;
	#define EXT_IecVarAccSetValue  extern PFIECVARACCSETVALUE pfIecVarAccSetValue;
	#define GET_IecVarAccSetValue(fl)  s_pfCMGetAPI2( "IecVarAccSetValue", (RTS_VOID_FCTPTR *)&pfIecVarAccSetValue, (fl), 0, 0)
	#define CAL_IecVarAccSetValue  pfIecVarAccSetValue
	#define CHK_IecVarAccSetValue  (pfIecVarAccSetValue != NULL)
	#define EXP_IecVarAccSetValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccSetValue", (RTS_UINTPTR)IecVarAccSetValue, 0, 0) 
#endif




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
RTS_SIZE CDECL IecVarAccSetValue3(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, void *pSrc, RTS_SIZE ulSize, RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFIECVARACCSETVALUE3) (RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, void *pSrc, RTS_SIZE ulSize, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCSETVALUE3_NOTIMPLEMENTED)
	#define USE_IecVarAccSetValue3
	#define EXT_IecVarAccSetValue3
	#define GET_IecVarAccSetValue3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccSetValue3(p0,p1,p2,p3,p4,p5)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccSetValue3  FALSE
	#define EXP_IecVarAccSetValue3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccSetValue3
	#define EXT_IecVarAccSetValue3
	#define GET_IecVarAccSetValue3(fl)  CAL_CMGETAPI( "IecVarAccSetValue3" ) 
	#define CAL_IecVarAccSetValue3  IecVarAccSetValue3
	#define CHK_IecVarAccSetValue3  TRUE
	#define EXP_IecVarAccSetValue3  CAL_CMEXPAPI( "IecVarAccSetValue3" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccSetValue3
	#define EXT_IecVarAccSetValue3
	#define GET_IecVarAccSetValue3(fl)  CAL_CMGETAPI( "IecVarAccSetValue3" ) 
	#define CAL_IecVarAccSetValue3  IecVarAccSetValue3
	#define CHK_IecVarAccSetValue3  TRUE
	#define EXP_IecVarAccSetValue3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccSetValue3", (RTS_UINTPTR)IecVarAccSetValue3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccSetValue3
	#define EXT_CmpIecVarAccessIecVarAccSetValue3
	#define GET_CmpIecVarAccessIecVarAccSetValue3  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccSetValue3 pICmpIecVarAccess->IIecVarAccSetValue3
	#define CHK_CmpIecVarAccessIecVarAccSetValue3 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccSetValue3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccSetValue3
	#define EXT_IecVarAccSetValue3
	#define GET_IecVarAccSetValue3(fl)  CAL_CMGETAPI( "IecVarAccSetValue3" ) 
	#define CAL_IecVarAccSetValue3 pICmpIecVarAccess->IIecVarAccSetValue3
	#define CHK_IecVarAccSetValue3 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccSetValue3  CAL_CMEXPAPI( "IecVarAccSetValue3" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccSetValue3  PFIECVARACCSETVALUE3 pfIecVarAccSetValue3;
	#define EXT_IecVarAccSetValue3  extern PFIECVARACCSETVALUE3 pfIecVarAccSetValue3;
	#define GET_IecVarAccSetValue3(fl)  s_pfCMGetAPI2( "IecVarAccSetValue3", (RTS_VOID_FCTPTR *)&pfIecVarAccSetValue3, (fl), 0, 0)
	#define CAL_IecVarAccSetValue3  pfIecVarAccSetValue3
	#define CHK_IecVarAccSetValue3  (pfIecVarAccSetValue3 != NULL)
	#define EXP_IecVarAccSetValue3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccSetValue3", (RTS_UINTPTR)IecVarAccSetValue3, 0, 0) 
#endif




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
RTS_SIZE CDECL IecVarAccSwap(RTS_HANDLE hInterface, RTS_HANDLE hNode, void *pData, RTS_SIZE ulSize, int bMotorola, RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFIECVARACCSWAP) (RTS_HANDLE hInterface, RTS_HANDLE hNode, void *pData, RTS_SIZE ulSize, int bMotorola, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCSWAP_NOTIMPLEMENTED)
	#define USE_IecVarAccSwap
	#define EXT_IecVarAccSwap
	#define GET_IecVarAccSwap(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccSwap(p0,p1,p2,p3,p4,p5)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccSwap  FALSE
	#define EXP_IecVarAccSwap  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccSwap
	#define EXT_IecVarAccSwap
	#define GET_IecVarAccSwap(fl)  CAL_CMGETAPI( "IecVarAccSwap" ) 
	#define CAL_IecVarAccSwap  IecVarAccSwap
	#define CHK_IecVarAccSwap  TRUE
	#define EXP_IecVarAccSwap  CAL_CMEXPAPI( "IecVarAccSwap" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccSwap
	#define EXT_IecVarAccSwap
	#define GET_IecVarAccSwap(fl)  CAL_CMGETAPI( "IecVarAccSwap" ) 
	#define CAL_IecVarAccSwap  IecVarAccSwap
	#define CHK_IecVarAccSwap  TRUE
	#define EXP_IecVarAccSwap  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccSwap", (RTS_UINTPTR)IecVarAccSwap, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccSwap
	#define EXT_CmpIecVarAccessIecVarAccSwap
	#define GET_CmpIecVarAccessIecVarAccSwap  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccSwap pICmpIecVarAccess->IIecVarAccSwap
	#define CHK_CmpIecVarAccessIecVarAccSwap (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccSwap  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccSwap
	#define EXT_IecVarAccSwap
	#define GET_IecVarAccSwap(fl)  CAL_CMGETAPI( "IecVarAccSwap" ) 
	#define CAL_IecVarAccSwap pICmpIecVarAccess->IIecVarAccSwap
	#define CHK_IecVarAccSwap (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccSwap  CAL_CMEXPAPI( "IecVarAccSwap" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccSwap  PFIECVARACCSWAP pfIecVarAccSwap;
	#define EXT_IecVarAccSwap  extern PFIECVARACCSWAP pfIecVarAccSwap;
	#define GET_IecVarAccSwap(fl)  s_pfCMGetAPI2( "IecVarAccSwap", (RTS_VOID_FCTPTR *)&pfIecVarAccSwap, (fl), 0, 0)
	#define CAL_IecVarAccSwap  pfIecVarAccSwap
	#define CHK_IecVarAccSwap  (pfIecVarAccSwap != NULL)
	#define EXP_IecVarAccSwap  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccSwap", (RTS_UINTPTR)IecVarAccSwap, 0, 0) 
#endif




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
RTS_SIZE CDECL IecVarAccSwap2(RTS_HANDLE hInterface, RTS_HANDLE hNode, void *pData, RTS_SIZE ulSize, int bMotorola, RTS_SIZE ulOffset, RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFIECVARACCSWAP2) (RTS_HANDLE hInterface, RTS_HANDLE hNode, void *pData, RTS_SIZE ulSize, int bMotorola, RTS_SIZE ulOffset, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCSWAP2_NOTIMPLEMENTED)
	#define USE_IecVarAccSwap2
	#define EXT_IecVarAccSwap2
	#define GET_IecVarAccSwap2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccSwap2(p0,p1,p2,p3,p4,p5,p6)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccSwap2  FALSE
	#define EXP_IecVarAccSwap2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccSwap2
	#define EXT_IecVarAccSwap2
	#define GET_IecVarAccSwap2(fl)  CAL_CMGETAPI( "IecVarAccSwap2" ) 
	#define CAL_IecVarAccSwap2  IecVarAccSwap2
	#define CHK_IecVarAccSwap2  TRUE
	#define EXP_IecVarAccSwap2  CAL_CMEXPAPI( "IecVarAccSwap2" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccSwap2
	#define EXT_IecVarAccSwap2
	#define GET_IecVarAccSwap2(fl)  CAL_CMGETAPI( "IecVarAccSwap2" ) 
	#define CAL_IecVarAccSwap2  IecVarAccSwap2
	#define CHK_IecVarAccSwap2  TRUE
	#define EXP_IecVarAccSwap2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccSwap2", (RTS_UINTPTR)IecVarAccSwap2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccSwap2
	#define EXT_CmpIecVarAccessIecVarAccSwap2
	#define GET_CmpIecVarAccessIecVarAccSwap2  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccSwap2 pICmpIecVarAccess->IIecVarAccSwap2
	#define CHK_CmpIecVarAccessIecVarAccSwap2 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccSwap2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccSwap2
	#define EXT_IecVarAccSwap2
	#define GET_IecVarAccSwap2(fl)  CAL_CMGETAPI( "IecVarAccSwap2" ) 
	#define CAL_IecVarAccSwap2 pICmpIecVarAccess->IIecVarAccSwap2
	#define CHK_IecVarAccSwap2 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccSwap2  CAL_CMEXPAPI( "IecVarAccSwap2" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccSwap2  PFIECVARACCSWAP2 pfIecVarAccSwap2;
	#define EXT_IecVarAccSwap2  extern PFIECVARACCSWAP2 pfIecVarAccSwap2;
	#define GET_IecVarAccSwap2(fl)  s_pfCMGetAPI2( "IecVarAccSwap2", (RTS_VOID_FCTPTR *)&pfIecVarAccSwap2, (fl), 0, 0)
	#define CAL_IecVarAccSwap2  pfIecVarAccSwap2
	#define CHK_IecVarAccSwap2  (pfIecVarAccSwap2 != NULL)
	#define EXP_IecVarAccSwap2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccSwap2", (RTS_UINTPTR)IecVarAccSwap2, 0, 0) 
#endif




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
RTS_SIZE CDECL IecVarAccSwap3(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, void *pData, RTS_SIZE ulSize, int bMotorola, RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFIECVARACCSWAP3) (RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, void *pData, RTS_SIZE ulSize, int bMotorola, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCSWAP3_NOTIMPLEMENTED)
	#define USE_IecVarAccSwap3
	#define EXT_IecVarAccSwap3
	#define GET_IecVarAccSwap3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccSwap3(p0,p1,p2,p3,p4,p5,p6)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccSwap3  FALSE
	#define EXP_IecVarAccSwap3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccSwap3
	#define EXT_IecVarAccSwap3
	#define GET_IecVarAccSwap3(fl)  CAL_CMGETAPI( "IecVarAccSwap3" ) 
	#define CAL_IecVarAccSwap3  IecVarAccSwap3
	#define CHK_IecVarAccSwap3  TRUE
	#define EXP_IecVarAccSwap3  CAL_CMEXPAPI( "IecVarAccSwap3" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccSwap3
	#define EXT_IecVarAccSwap3
	#define GET_IecVarAccSwap3(fl)  CAL_CMGETAPI( "IecVarAccSwap3" ) 
	#define CAL_IecVarAccSwap3  IecVarAccSwap3
	#define CHK_IecVarAccSwap3  TRUE
	#define EXP_IecVarAccSwap3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccSwap3", (RTS_UINTPTR)IecVarAccSwap3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccSwap3
	#define EXT_CmpIecVarAccessIecVarAccSwap3
	#define GET_CmpIecVarAccessIecVarAccSwap3  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccSwap3 pICmpIecVarAccess->IIecVarAccSwap3
	#define CHK_CmpIecVarAccessIecVarAccSwap3 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccSwap3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccSwap3
	#define EXT_IecVarAccSwap3
	#define GET_IecVarAccSwap3(fl)  CAL_CMGETAPI( "IecVarAccSwap3" ) 
	#define CAL_IecVarAccSwap3 pICmpIecVarAccess->IIecVarAccSwap3
	#define CHK_IecVarAccSwap3 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccSwap3  CAL_CMEXPAPI( "IecVarAccSwap3" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccSwap3  PFIECVARACCSWAP3 pfIecVarAccSwap3;
	#define EXT_IecVarAccSwap3  extern PFIECVARACCSWAP3 pfIecVarAccSwap3;
	#define GET_IecVarAccSwap3(fl)  s_pfCMGetAPI2( "IecVarAccSwap3", (RTS_VOID_FCTPTR *)&pfIecVarAccSwap3, (fl), 0, 0)
	#define CAL_IecVarAccSwap3  pfIecVarAccSwap3
	#define CHK_IecVarAccSwap3  (pfIecVarAccSwap3 != NULL)
	#define EXP_IecVarAccSwap3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccSwap3", (RTS_UINTPTR)IecVarAccSwap3, 0, 0) 
#endif




/**
 * <description>Get the type node of the specified symbolic node. For arays, only the array type is retrieved!</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the type node (called hTypeNode)</result>
 */
RTS_HANDLE CDECL IecVarAccGetTypeNode(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECVARACCGETTYPENODE) (RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETTYPENODE_NOTIMPLEMENTED)
	#define USE_IecVarAccGetTypeNode
	#define EXT_IecVarAccGetTypeNode
	#define GET_IecVarAccGetTypeNode(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetTypeNode(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecVarAccGetTypeNode  FALSE
	#define EXP_IecVarAccGetTypeNode  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetTypeNode
	#define EXT_IecVarAccGetTypeNode
	#define GET_IecVarAccGetTypeNode(fl)  CAL_CMGETAPI( "IecVarAccGetTypeNode" ) 
	#define CAL_IecVarAccGetTypeNode  IecVarAccGetTypeNode
	#define CHK_IecVarAccGetTypeNode  TRUE
	#define EXP_IecVarAccGetTypeNode  CAL_CMEXPAPI( "IecVarAccGetTypeNode" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetTypeNode
	#define EXT_IecVarAccGetTypeNode
	#define GET_IecVarAccGetTypeNode(fl)  CAL_CMGETAPI( "IecVarAccGetTypeNode" ) 
	#define CAL_IecVarAccGetTypeNode  IecVarAccGetTypeNode
	#define CHK_IecVarAccGetTypeNode  TRUE
	#define EXP_IecVarAccGetTypeNode  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetTypeNode", (RTS_UINTPTR)IecVarAccGetTypeNode, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetTypeNode
	#define EXT_CmpIecVarAccessIecVarAccGetTypeNode
	#define GET_CmpIecVarAccessIecVarAccGetTypeNode  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetTypeNode pICmpIecVarAccess->IIecVarAccGetTypeNode
	#define CHK_CmpIecVarAccessIecVarAccGetTypeNode (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetTypeNode  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetTypeNode
	#define EXT_IecVarAccGetTypeNode
	#define GET_IecVarAccGetTypeNode(fl)  CAL_CMGETAPI( "IecVarAccGetTypeNode" ) 
	#define CAL_IecVarAccGetTypeNode pICmpIecVarAccess->IIecVarAccGetTypeNode
	#define CHK_IecVarAccGetTypeNode (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetTypeNode  CAL_CMEXPAPI( "IecVarAccGetTypeNode" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetTypeNode  PFIECVARACCGETTYPENODE pfIecVarAccGetTypeNode;
	#define EXT_IecVarAccGetTypeNode  extern PFIECVARACCGETTYPENODE pfIecVarAccGetTypeNode;
	#define GET_IecVarAccGetTypeNode(fl)  s_pfCMGetAPI2( "IecVarAccGetTypeNode", (RTS_VOID_FCTPTR *)&pfIecVarAccGetTypeNode, (fl), 0, 0)
	#define CAL_IecVarAccGetTypeNode  pfIecVarAccGetTypeNode
	#define CHK_IecVarAccGetTypeNode  (pfIecVarAccGetTypeNode != NULL)
	#define EXP_IecVarAccGetTypeNode  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetTypeNode", (RTS_UINTPTR)IecVarAccGetTypeNode, 0, 0) 
#endif




/**
 * <description>Get the type node of the specified symbolic node (worked for all types of node!)</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="ulOffset" type="IN">Offset of the node (is retrieved by IecVarAccGetNode)</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the type node (called hTypeNode)</result>
 */
RTS_HANDLE CDECL IecVarAccGetTypeNode2(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_SIZE ulOffset, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECVARACCGETTYPENODE2) (RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_SIZE ulOffset, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETTYPENODE2_NOTIMPLEMENTED)
	#define USE_IecVarAccGetTypeNode2
	#define EXT_IecVarAccGetTypeNode2
	#define GET_IecVarAccGetTypeNode2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetTypeNode2(p0,p1,p2,p3)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecVarAccGetTypeNode2  FALSE
	#define EXP_IecVarAccGetTypeNode2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetTypeNode2
	#define EXT_IecVarAccGetTypeNode2
	#define GET_IecVarAccGetTypeNode2(fl)  CAL_CMGETAPI( "IecVarAccGetTypeNode2" ) 
	#define CAL_IecVarAccGetTypeNode2  IecVarAccGetTypeNode2
	#define CHK_IecVarAccGetTypeNode2  TRUE
	#define EXP_IecVarAccGetTypeNode2  CAL_CMEXPAPI( "IecVarAccGetTypeNode2" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetTypeNode2
	#define EXT_IecVarAccGetTypeNode2
	#define GET_IecVarAccGetTypeNode2(fl)  CAL_CMGETAPI( "IecVarAccGetTypeNode2" ) 
	#define CAL_IecVarAccGetTypeNode2  IecVarAccGetTypeNode2
	#define CHK_IecVarAccGetTypeNode2  TRUE
	#define EXP_IecVarAccGetTypeNode2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetTypeNode2", (RTS_UINTPTR)IecVarAccGetTypeNode2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetTypeNode2
	#define EXT_CmpIecVarAccessIecVarAccGetTypeNode2
	#define GET_CmpIecVarAccessIecVarAccGetTypeNode2  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetTypeNode2 pICmpIecVarAccess->IIecVarAccGetTypeNode2
	#define CHK_CmpIecVarAccessIecVarAccGetTypeNode2 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetTypeNode2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetTypeNode2
	#define EXT_IecVarAccGetTypeNode2
	#define GET_IecVarAccGetTypeNode2(fl)  CAL_CMGETAPI( "IecVarAccGetTypeNode2" ) 
	#define CAL_IecVarAccGetTypeNode2 pICmpIecVarAccess->IIecVarAccGetTypeNode2
	#define CHK_IecVarAccGetTypeNode2 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetTypeNode2  CAL_CMEXPAPI( "IecVarAccGetTypeNode2" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetTypeNode2  PFIECVARACCGETTYPENODE2 pfIecVarAccGetTypeNode2;
	#define EXT_IecVarAccGetTypeNode2  extern PFIECVARACCGETTYPENODE2 pfIecVarAccGetTypeNode2;
	#define GET_IecVarAccGetTypeNode2(fl)  s_pfCMGetAPI2( "IecVarAccGetTypeNode2", (RTS_VOID_FCTPTR *)&pfIecVarAccGetTypeNode2, (fl), 0, 0)
	#define CAL_IecVarAccGetTypeNode2  pfIecVarAccGetTypeNode2
	#define CHK_IecVarAccGetTypeNode2  (pfIecVarAccGetTypeNode2 != NULL)
	#define EXP_IecVarAccGetTypeNode2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetTypeNode2", (RTS_UINTPTR)IecVarAccGetTypeNode2, 0, 0) 
#endif




/**
 * <description>Get the type node of the specified symbolic node (worked for all types of node!)</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pVariableInformation" type="IN">Pointer to the variable information that is retrieved by IecVarAccGetNode3</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the type node (called hTypeNode)</result>
 */
RTS_HANDLE CDECL IecVarAccGetTypeNode3(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECVARACCGETTYPENODE3) (RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETTYPENODE3_NOTIMPLEMENTED)
	#define USE_IecVarAccGetTypeNode3
	#define EXT_IecVarAccGetTypeNode3
	#define GET_IecVarAccGetTypeNode3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetTypeNode3(p0,p1,p2,p3)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecVarAccGetTypeNode3  FALSE
	#define EXP_IecVarAccGetTypeNode3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetTypeNode3
	#define EXT_IecVarAccGetTypeNode3
	#define GET_IecVarAccGetTypeNode3(fl)  CAL_CMGETAPI( "IecVarAccGetTypeNode3" ) 
	#define CAL_IecVarAccGetTypeNode3  IecVarAccGetTypeNode3
	#define CHK_IecVarAccGetTypeNode3  TRUE
	#define EXP_IecVarAccGetTypeNode3  CAL_CMEXPAPI( "IecVarAccGetTypeNode3" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetTypeNode3
	#define EXT_IecVarAccGetTypeNode3
	#define GET_IecVarAccGetTypeNode3(fl)  CAL_CMGETAPI( "IecVarAccGetTypeNode3" ) 
	#define CAL_IecVarAccGetTypeNode3  IecVarAccGetTypeNode3
	#define CHK_IecVarAccGetTypeNode3  TRUE
	#define EXP_IecVarAccGetTypeNode3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetTypeNode3", (RTS_UINTPTR)IecVarAccGetTypeNode3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetTypeNode3
	#define EXT_CmpIecVarAccessIecVarAccGetTypeNode3
	#define GET_CmpIecVarAccessIecVarAccGetTypeNode3  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetTypeNode3 pICmpIecVarAccess->IIecVarAccGetTypeNode3
	#define CHK_CmpIecVarAccessIecVarAccGetTypeNode3 (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetTypeNode3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetTypeNode3
	#define EXT_IecVarAccGetTypeNode3
	#define GET_IecVarAccGetTypeNode3(fl)  CAL_CMGETAPI( "IecVarAccGetTypeNode3" ) 
	#define CAL_IecVarAccGetTypeNode3 pICmpIecVarAccess->IIecVarAccGetTypeNode3
	#define CHK_IecVarAccGetTypeNode3 (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetTypeNode3  CAL_CMEXPAPI( "IecVarAccGetTypeNode3" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetTypeNode3  PFIECVARACCGETTYPENODE3 pfIecVarAccGetTypeNode3;
	#define EXT_IecVarAccGetTypeNode3  extern PFIECVARACCGETTYPENODE3 pfIecVarAccGetTypeNode3;
	#define GET_IecVarAccGetTypeNode3(fl)  s_pfCMGetAPI2( "IecVarAccGetTypeNode3", (RTS_VOID_FCTPTR *)&pfIecVarAccGetTypeNode3, (fl), 0, 0)
	#define CAL_IecVarAccGetTypeNode3  pfIecVarAccGetTypeNode3
	#define CHK_IecVarAccGetTypeNode3  (pfIecVarAccGetTypeNode3 != NULL)
	#define EXP_IecVarAccGetTypeNode3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetTypeNode3", (RTS_UINTPTR)IecVarAccGetTypeNode3, 0, 0) 
#endif




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
RTS_RESULT CDECL IecVarAccGetTypeDesc(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, TypeDescAsUnion *pTypeDesc);
typedef RTS_RESULT (CDECL * PFIECVARACCGETTYPEDESC) (RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, TypeDescAsUnion *pTypeDesc);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETTYPEDESC_NOTIMPLEMENTED)
	#define USE_IecVarAccGetTypeDesc
	#define EXT_IecVarAccGetTypeDesc
	#define GET_IecVarAccGetTypeDesc(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetTypeDesc(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetTypeDesc  FALSE
	#define EXP_IecVarAccGetTypeDesc  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetTypeDesc
	#define EXT_IecVarAccGetTypeDesc
	#define GET_IecVarAccGetTypeDesc(fl)  CAL_CMGETAPI( "IecVarAccGetTypeDesc" ) 
	#define CAL_IecVarAccGetTypeDesc  IecVarAccGetTypeDesc
	#define CHK_IecVarAccGetTypeDesc  TRUE
	#define EXP_IecVarAccGetTypeDesc  CAL_CMEXPAPI( "IecVarAccGetTypeDesc" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetTypeDesc
	#define EXT_IecVarAccGetTypeDesc
	#define GET_IecVarAccGetTypeDesc(fl)  CAL_CMGETAPI( "IecVarAccGetTypeDesc" ) 
	#define CAL_IecVarAccGetTypeDesc  IecVarAccGetTypeDesc
	#define CHK_IecVarAccGetTypeDesc  TRUE
	#define EXP_IecVarAccGetTypeDesc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetTypeDesc", (RTS_UINTPTR)IecVarAccGetTypeDesc, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetTypeDesc
	#define EXT_CmpIecVarAccessIecVarAccGetTypeDesc
	#define GET_CmpIecVarAccessIecVarAccGetTypeDesc  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetTypeDesc pICmpIecVarAccess->IIecVarAccGetTypeDesc
	#define CHK_CmpIecVarAccessIecVarAccGetTypeDesc (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetTypeDesc  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetTypeDesc
	#define EXT_IecVarAccGetTypeDesc
	#define GET_IecVarAccGetTypeDesc(fl)  CAL_CMGETAPI( "IecVarAccGetTypeDesc" ) 
	#define CAL_IecVarAccGetTypeDesc pICmpIecVarAccess->IIecVarAccGetTypeDesc
	#define CHK_IecVarAccGetTypeDesc (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetTypeDesc  CAL_CMEXPAPI( "IecVarAccGetTypeDesc" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetTypeDesc  PFIECVARACCGETTYPEDESC pfIecVarAccGetTypeDesc;
	#define EXT_IecVarAccGetTypeDesc  extern PFIECVARACCGETTYPEDESC pfIecVarAccGetTypeDesc;
	#define GET_IecVarAccGetTypeDesc(fl)  s_pfCMGetAPI2( "IecVarAccGetTypeDesc", (RTS_VOID_FCTPTR *)&pfIecVarAccGetTypeDesc, (fl), 0, 0)
	#define CAL_IecVarAccGetTypeDesc  pfIecVarAccGetTypeDesc
	#define CHK_IecVarAccGetTypeDesc  (pfIecVarAccGetTypeDesc != NULL)
	#define EXP_IecVarAccGetTypeDesc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetTypeDesc", (RTS_UINTPTR)IecVarAccGetTypeDesc, 0, 0) 
#endif




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
RTS_RESULT CDECL IecVarAccGetAddressInfo(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, char *pszAdressInfo, int *pnAddressInfoLen);
typedef RTS_RESULT (CDECL * PFIECVARACCGETADDRESSINFO) (RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, char *pszAdressInfo, int *pnAddressInfoLen);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETADDRESSINFO_NOTIMPLEMENTED)
	#define USE_IecVarAccGetAddressInfo
	#define EXT_IecVarAccGetAddressInfo
	#define GET_IecVarAccGetAddressInfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetAddressInfo(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetAddressInfo  FALSE
	#define EXP_IecVarAccGetAddressInfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetAddressInfo
	#define EXT_IecVarAccGetAddressInfo
	#define GET_IecVarAccGetAddressInfo(fl)  CAL_CMGETAPI( "IecVarAccGetAddressInfo" ) 
	#define CAL_IecVarAccGetAddressInfo  IecVarAccGetAddressInfo
	#define CHK_IecVarAccGetAddressInfo  TRUE
	#define EXP_IecVarAccGetAddressInfo  CAL_CMEXPAPI( "IecVarAccGetAddressInfo" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetAddressInfo
	#define EXT_IecVarAccGetAddressInfo
	#define GET_IecVarAccGetAddressInfo(fl)  CAL_CMGETAPI( "IecVarAccGetAddressInfo" ) 
	#define CAL_IecVarAccGetAddressInfo  IecVarAccGetAddressInfo
	#define CHK_IecVarAccGetAddressInfo  TRUE
	#define EXP_IecVarAccGetAddressInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetAddressInfo", (RTS_UINTPTR)IecVarAccGetAddressInfo, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetAddressInfo
	#define EXT_CmpIecVarAccessIecVarAccGetAddressInfo
	#define GET_CmpIecVarAccessIecVarAccGetAddressInfo  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetAddressInfo pICmpIecVarAccess->IIecVarAccGetAddressInfo
	#define CHK_CmpIecVarAccessIecVarAccGetAddressInfo (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetAddressInfo  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetAddressInfo
	#define EXT_IecVarAccGetAddressInfo
	#define GET_IecVarAccGetAddressInfo(fl)  CAL_CMGETAPI( "IecVarAccGetAddressInfo" ) 
	#define CAL_IecVarAccGetAddressInfo pICmpIecVarAccess->IIecVarAccGetAddressInfo
	#define CHK_IecVarAccGetAddressInfo (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetAddressInfo  CAL_CMEXPAPI( "IecVarAccGetAddressInfo" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetAddressInfo  PFIECVARACCGETADDRESSINFO pfIecVarAccGetAddressInfo;
	#define EXT_IecVarAccGetAddressInfo  extern PFIECVARACCGETADDRESSINFO pfIecVarAccGetAddressInfo;
	#define GET_IecVarAccGetAddressInfo(fl)  s_pfCMGetAPI2( "IecVarAccGetAddressInfo", (RTS_VOID_FCTPTR *)&pfIecVarAccGetAddressInfo, (fl), 0, 0)
	#define CAL_IecVarAccGetAddressInfo  pfIecVarAccGetAddressInfo
	#define CHK_IecVarAccGetAddressInfo  (pfIecVarAccGetAddressInfo != NULL)
	#define EXP_IecVarAccGetAddressInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetAddressInfo", (RTS_UINTPTR)IecVarAccGetAddressInfo, 0, 0) 
#endif





/*#### OPC UA interfaces ####*/

/**
 * <description>Get the number of defined data types.
 *	NOTE:
 *	Only supported if OPC UA support is activated in the symbolconfiguration in CODESYS!</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of defined data types</result>
 */
RTS_I32 CDECL IecVarAccGetNumOfTypes(RTS_HANDLE hInterface, RTS_RESULT *pResult);
typedef RTS_I32 (CDECL * PFIECVARACCGETNUMOFTYPES) (RTS_HANDLE hInterface, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNUMOFTYPES_NOTIMPLEMENTED)
	#define USE_IecVarAccGetNumOfTypes
	#define EXT_IecVarAccGetNumOfTypes
	#define GET_IecVarAccGetNumOfTypes(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetNumOfTypes(p0,p1)  (RTS_I32)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetNumOfTypes  FALSE
	#define EXP_IecVarAccGetNumOfTypes  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetNumOfTypes
	#define EXT_IecVarAccGetNumOfTypes
	#define GET_IecVarAccGetNumOfTypes(fl)  CAL_CMGETAPI( "IecVarAccGetNumOfTypes" ) 
	#define CAL_IecVarAccGetNumOfTypes  IecVarAccGetNumOfTypes
	#define CHK_IecVarAccGetNumOfTypes  TRUE
	#define EXP_IecVarAccGetNumOfTypes  CAL_CMEXPAPI( "IecVarAccGetNumOfTypes" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetNumOfTypes
	#define EXT_IecVarAccGetNumOfTypes
	#define GET_IecVarAccGetNumOfTypes(fl)  CAL_CMGETAPI( "IecVarAccGetNumOfTypes" ) 
	#define CAL_IecVarAccGetNumOfTypes  IecVarAccGetNumOfTypes
	#define CHK_IecVarAccGetNumOfTypes  TRUE
	#define EXP_IecVarAccGetNumOfTypes  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNumOfTypes", (RTS_UINTPTR)IecVarAccGetNumOfTypes, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetNumOfTypes
	#define EXT_CmpIecVarAccessIecVarAccGetNumOfTypes
	#define GET_CmpIecVarAccessIecVarAccGetNumOfTypes  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetNumOfTypes pICmpIecVarAccess->IIecVarAccGetNumOfTypes
	#define CHK_CmpIecVarAccessIecVarAccGetNumOfTypes (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetNumOfTypes  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetNumOfTypes
	#define EXT_IecVarAccGetNumOfTypes
	#define GET_IecVarAccGetNumOfTypes(fl)  CAL_CMGETAPI( "IecVarAccGetNumOfTypes" ) 
	#define CAL_IecVarAccGetNumOfTypes pICmpIecVarAccess->IIecVarAccGetNumOfTypes
	#define CHK_IecVarAccGetNumOfTypes (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetNumOfTypes  CAL_CMEXPAPI( "IecVarAccGetNumOfTypes" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetNumOfTypes  PFIECVARACCGETNUMOFTYPES pfIecVarAccGetNumOfTypes;
	#define EXT_IecVarAccGetNumOfTypes  extern PFIECVARACCGETNUMOFTYPES pfIecVarAccGetNumOfTypes;
	#define GET_IecVarAccGetNumOfTypes(fl)  s_pfCMGetAPI2( "IecVarAccGetNumOfTypes", (RTS_VOID_FCTPTR *)&pfIecVarAccGetNumOfTypes, (fl), 0, 0)
	#define CAL_IecVarAccGetNumOfTypes  pfIecVarAccGetNumOfTypes
	#define CHK_IecVarAccGetNumOfTypes  (pfIecVarAccGetNumOfTypes != NULL)
	#define EXP_IecVarAccGetNumOfTypes  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNumOfTypes", (RTS_UINTPTR)IecVarAccGetNumOfTypes, 0, 0) 
#endif




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
RTS_HANDLE CDECL IecVarAccGetTypeNodeByIndex(RTS_HANDLE hInterface, RTS_I32 nIndex, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECVARACCGETTYPENODEBYINDEX) (RTS_HANDLE hInterface, RTS_I32 nIndex, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETTYPENODEBYINDEX_NOTIMPLEMENTED)
	#define USE_IecVarAccGetTypeNodeByIndex
	#define EXT_IecVarAccGetTypeNodeByIndex
	#define GET_IecVarAccGetTypeNodeByIndex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetTypeNodeByIndex(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecVarAccGetTypeNodeByIndex  FALSE
	#define EXP_IecVarAccGetTypeNodeByIndex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetTypeNodeByIndex
	#define EXT_IecVarAccGetTypeNodeByIndex
	#define GET_IecVarAccGetTypeNodeByIndex(fl)  CAL_CMGETAPI( "IecVarAccGetTypeNodeByIndex" ) 
	#define CAL_IecVarAccGetTypeNodeByIndex  IecVarAccGetTypeNodeByIndex
	#define CHK_IecVarAccGetTypeNodeByIndex  TRUE
	#define EXP_IecVarAccGetTypeNodeByIndex  CAL_CMEXPAPI( "IecVarAccGetTypeNodeByIndex" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetTypeNodeByIndex
	#define EXT_IecVarAccGetTypeNodeByIndex
	#define GET_IecVarAccGetTypeNodeByIndex(fl)  CAL_CMGETAPI( "IecVarAccGetTypeNodeByIndex" ) 
	#define CAL_IecVarAccGetTypeNodeByIndex  IecVarAccGetTypeNodeByIndex
	#define CHK_IecVarAccGetTypeNodeByIndex  TRUE
	#define EXP_IecVarAccGetTypeNodeByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetTypeNodeByIndex", (RTS_UINTPTR)IecVarAccGetTypeNodeByIndex, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetTypeNodeByIndex
	#define EXT_CmpIecVarAccessIecVarAccGetTypeNodeByIndex
	#define GET_CmpIecVarAccessIecVarAccGetTypeNodeByIndex  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetTypeNodeByIndex pICmpIecVarAccess->IIecVarAccGetTypeNodeByIndex
	#define CHK_CmpIecVarAccessIecVarAccGetTypeNodeByIndex (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetTypeNodeByIndex  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetTypeNodeByIndex
	#define EXT_IecVarAccGetTypeNodeByIndex
	#define GET_IecVarAccGetTypeNodeByIndex(fl)  CAL_CMGETAPI( "IecVarAccGetTypeNodeByIndex" ) 
	#define CAL_IecVarAccGetTypeNodeByIndex pICmpIecVarAccess->IIecVarAccGetTypeNodeByIndex
	#define CHK_IecVarAccGetTypeNodeByIndex (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetTypeNodeByIndex  CAL_CMEXPAPI( "IecVarAccGetTypeNodeByIndex" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetTypeNodeByIndex  PFIECVARACCGETTYPENODEBYINDEX pfIecVarAccGetTypeNodeByIndex;
	#define EXT_IecVarAccGetTypeNodeByIndex  extern PFIECVARACCGETTYPENODEBYINDEX pfIecVarAccGetTypeNodeByIndex;
	#define GET_IecVarAccGetTypeNodeByIndex(fl)  s_pfCMGetAPI2( "IecVarAccGetTypeNodeByIndex", (RTS_VOID_FCTPTR *)&pfIecVarAccGetTypeNodeByIndex, (fl), 0, 0)
	#define CAL_IecVarAccGetTypeNodeByIndex  pfIecVarAccGetTypeNodeByIndex
	#define CHK_IecVarAccGetTypeNodeByIndex  (pfIecVarAccGetTypeNodeByIndex != NULL)
	#define EXP_IecVarAccGetTypeNodeByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetTypeNodeByIndex", (RTS_UINTPTR)IecVarAccGetTypeNodeByIndex, 0, 0) 
#endif




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
char* CDECL IecVarAccGetTypeName(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_RESULT *pResult);
typedef char* (CDECL * PFIECVARACCGETTYPENAME) (RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETTYPENAME_NOTIMPLEMENTED)
	#define USE_IecVarAccGetTypeName
	#define EXT_IecVarAccGetTypeName
	#define GET_IecVarAccGetTypeName(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetTypeName(p0,p1,p2)  (char*)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetTypeName  FALSE
	#define EXP_IecVarAccGetTypeName  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetTypeName
	#define EXT_IecVarAccGetTypeName
	#define GET_IecVarAccGetTypeName(fl)  CAL_CMGETAPI( "IecVarAccGetTypeName" ) 
	#define CAL_IecVarAccGetTypeName  IecVarAccGetTypeName
	#define CHK_IecVarAccGetTypeName  TRUE
	#define EXP_IecVarAccGetTypeName  CAL_CMEXPAPI( "IecVarAccGetTypeName" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetTypeName
	#define EXT_IecVarAccGetTypeName
	#define GET_IecVarAccGetTypeName(fl)  CAL_CMGETAPI( "IecVarAccGetTypeName" ) 
	#define CAL_IecVarAccGetTypeName  IecVarAccGetTypeName
	#define CHK_IecVarAccGetTypeName  TRUE
	#define EXP_IecVarAccGetTypeName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetTypeName", (RTS_UINTPTR)IecVarAccGetTypeName, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetTypeName
	#define EXT_CmpIecVarAccessIecVarAccGetTypeName
	#define GET_CmpIecVarAccessIecVarAccGetTypeName  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetTypeName pICmpIecVarAccess->IIecVarAccGetTypeName
	#define CHK_CmpIecVarAccessIecVarAccGetTypeName (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetTypeName  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetTypeName
	#define EXT_IecVarAccGetTypeName
	#define GET_IecVarAccGetTypeName(fl)  CAL_CMGETAPI( "IecVarAccGetTypeName" ) 
	#define CAL_IecVarAccGetTypeName pICmpIecVarAccess->IIecVarAccGetTypeName
	#define CHK_IecVarAccGetTypeName (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetTypeName  CAL_CMEXPAPI( "IecVarAccGetTypeName" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetTypeName  PFIECVARACCGETTYPENAME pfIecVarAccGetTypeName;
	#define EXT_IecVarAccGetTypeName  extern PFIECVARACCGETTYPENAME pfIecVarAccGetTypeName;
	#define GET_IecVarAccGetTypeName(fl)  s_pfCMGetAPI2( "IecVarAccGetTypeName", (RTS_VOID_FCTPTR *)&pfIecVarAccGetTypeName, (fl), 0, 0)
	#define CAL_IecVarAccGetTypeName  pfIecVarAccGetTypeName
	#define CHK_IecVarAccGetTypeName  (pfIecVarAccGetTypeName != NULL)
	#define EXP_IecVarAccGetTypeName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetTypeName", (RTS_UINTPTR)IecVarAccGetTypeName, 0, 0) 
#endif




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
TypeClass3 CDECL IecVarAccGetTypeClassFromType(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_IEC_DWORD dwFlags, RTS_RESULT *pResult);
typedef TypeClass3 (CDECL * PFIECVARACCGETTYPECLASSFROMTYPE) (RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_IEC_DWORD dwFlags, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETTYPECLASSFROMTYPE_NOTIMPLEMENTED)
	#define USE_IecVarAccGetTypeClassFromType
	#define EXT_IecVarAccGetTypeClassFromType
	#define GET_IecVarAccGetTypeClassFromType(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetTypeClassFromType(p0,p1,p2,p3)  (TypeClass3)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetTypeClassFromType  FALSE
	#define EXP_IecVarAccGetTypeClassFromType  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetTypeClassFromType
	#define EXT_IecVarAccGetTypeClassFromType
	#define GET_IecVarAccGetTypeClassFromType(fl)  CAL_CMGETAPI( "IecVarAccGetTypeClassFromType" ) 
	#define CAL_IecVarAccGetTypeClassFromType  IecVarAccGetTypeClassFromType
	#define CHK_IecVarAccGetTypeClassFromType  TRUE
	#define EXP_IecVarAccGetTypeClassFromType  CAL_CMEXPAPI( "IecVarAccGetTypeClassFromType" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetTypeClassFromType
	#define EXT_IecVarAccGetTypeClassFromType
	#define GET_IecVarAccGetTypeClassFromType(fl)  CAL_CMGETAPI( "IecVarAccGetTypeClassFromType" ) 
	#define CAL_IecVarAccGetTypeClassFromType  IecVarAccGetTypeClassFromType
	#define CHK_IecVarAccGetTypeClassFromType  TRUE
	#define EXP_IecVarAccGetTypeClassFromType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetTypeClassFromType", (RTS_UINTPTR)IecVarAccGetTypeClassFromType, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetTypeClassFromType
	#define EXT_CmpIecVarAccessIecVarAccGetTypeClassFromType
	#define GET_CmpIecVarAccessIecVarAccGetTypeClassFromType  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetTypeClassFromType pICmpIecVarAccess->IIecVarAccGetTypeClassFromType
	#define CHK_CmpIecVarAccessIecVarAccGetTypeClassFromType (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetTypeClassFromType  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetTypeClassFromType
	#define EXT_IecVarAccGetTypeClassFromType
	#define GET_IecVarAccGetTypeClassFromType(fl)  CAL_CMGETAPI( "IecVarAccGetTypeClassFromType" ) 
	#define CAL_IecVarAccGetTypeClassFromType pICmpIecVarAccess->IIecVarAccGetTypeClassFromType
	#define CHK_IecVarAccGetTypeClassFromType (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetTypeClassFromType  CAL_CMEXPAPI( "IecVarAccGetTypeClassFromType" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetTypeClassFromType  PFIECVARACCGETTYPECLASSFROMTYPE pfIecVarAccGetTypeClassFromType;
	#define EXT_IecVarAccGetTypeClassFromType  extern PFIECVARACCGETTYPECLASSFROMTYPE pfIecVarAccGetTypeClassFromType;
	#define GET_IecVarAccGetTypeClassFromType(fl)  s_pfCMGetAPI2( "IecVarAccGetTypeClassFromType", (RTS_VOID_FCTPTR *)&pfIecVarAccGetTypeClassFromType, (fl), 0, 0)
	#define CAL_IecVarAccGetTypeClassFromType  pfIecVarAccGetTypeClassFromType
	#define CHK_IecVarAccGetTypeClassFromType  (pfIecVarAccGetTypeClassFromType != NULL)
	#define EXP_IecVarAccGetTypeClassFromType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetTypeClassFromType", (RTS_UINTPTR)IecVarAccGetTypeClassFromType, 0, 0) 
#endif




/**
 * <description>Get the POU class of the specified type</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hTypeNode" type="IN">Handle to the type node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>POUClass</result>
 */
POUClass CDECL IecVarAccGetPOUClass(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_RESULT *pResult);
typedef POUClass (CDECL * PFIECVARACCGETPOUCLASS) (RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETPOUCLASS_NOTIMPLEMENTED)
	#define USE_IecVarAccGetPOUClass
	#define EXT_IecVarAccGetPOUClass
	#define GET_IecVarAccGetPOUClass(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetPOUClass(p0,p1,p2)  (POUClass)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetPOUClass  FALSE
	#define EXP_IecVarAccGetPOUClass  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetPOUClass
	#define EXT_IecVarAccGetPOUClass
	#define GET_IecVarAccGetPOUClass(fl)  CAL_CMGETAPI( "IecVarAccGetPOUClass" ) 
	#define CAL_IecVarAccGetPOUClass  IecVarAccGetPOUClass
	#define CHK_IecVarAccGetPOUClass  TRUE
	#define EXP_IecVarAccGetPOUClass  CAL_CMEXPAPI( "IecVarAccGetPOUClass" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetPOUClass
	#define EXT_IecVarAccGetPOUClass
	#define GET_IecVarAccGetPOUClass(fl)  CAL_CMGETAPI( "IecVarAccGetPOUClass" ) 
	#define CAL_IecVarAccGetPOUClass  IecVarAccGetPOUClass
	#define CHK_IecVarAccGetPOUClass  TRUE
	#define EXP_IecVarAccGetPOUClass  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetPOUClass", (RTS_UINTPTR)IecVarAccGetPOUClass, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetPOUClass
	#define EXT_CmpIecVarAccessIecVarAccGetPOUClass
	#define GET_CmpIecVarAccessIecVarAccGetPOUClass  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetPOUClass pICmpIecVarAccess->IIecVarAccGetPOUClass
	#define CHK_CmpIecVarAccessIecVarAccGetPOUClass (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetPOUClass  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetPOUClass
	#define EXT_IecVarAccGetPOUClass
	#define GET_IecVarAccGetPOUClass(fl)  CAL_CMGETAPI( "IecVarAccGetPOUClass" ) 
	#define CAL_IecVarAccGetPOUClass pICmpIecVarAccess->IIecVarAccGetPOUClass
	#define CHK_IecVarAccGetPOUClass (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetPOUClass  CAL_CMEXPAPI( "IecVarAccGetPOUClass" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetPOUClass  PFIECVARACCGETPOUCLASS pfIecVarAccGetPOUClass;
	#define EXT_IecVarAccGetPOUClass  extern PFIECVARACCGETPOUCLASS pfIecVarAccGetPOUClass;
	#define GET_IecVarAccGetPOUClass(fl)  s_pfCMGetAPI2( "IecVarAccGetPOUClass", (RTS_VOID_FCTPTR *)&pfIecVarAccGetPOUClass, (fl), 0, 0)
	#define CAL_IecVarAccGetPOUClass  pfIecVarAccGetPOUClass
	#define CHK_IecVarAccGetPOUClass  (pfIecVarAccGetPOUClass != NULL)
	#define EXP_IecVarAccGetPOUClass  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetPOUClass", (RTS_UINTPTR)IecVarAccGetPOUClass, 0, 0) 
#endif




/**
 * <description>Get the node flags of a specified node. Is typically used in memmer node of a struct/functionblock etc. to get the storage class info (VAR_INPUT, VAR_OUTPUT, etc.)</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hNode" type="IN">Handle to the node</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>NodeFlags. See NodeFlags for details</result>
 */
RTS_UI32 CDECL IecVarAccGetNodeFlags(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
typedef RTS_UI32 (CDECL * PFIECVARACCGETNODEFLAGS) (RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNODEFLAGS_NOTIMPLEMENTED)
	#define USE_IecVarAccGetNodeFlags
	#define EXT_IecVarAccGetNodeFlags
	#define GET_IecVarAccGetNodeFlags(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetNodeFlags(p0,p1,p2)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetNodeFlags  FALSE
	#define EXP_IecVarAccGetNodeFlags  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetNodeFlags
	#define EXT_IecVarAccGetNodeFlags
	#define GET_IecVarAccGetNodeFlags(fl)  CAL_CMGETAPI( "IecVarAccGetNodeFlags" ) 
	#define CAL_IecVarAccGetNodeFlags  IecVarAccGetNodeFlags
	#define CHK_IecVarAccGetNodeFlags  TRUE
	#define EXP_IecVarAccGetNodeFlags  CAL_CMEXPAPI( "IecVarAccGetNodeFlags" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetNodeFlags
	#define EXT_IecVarAccGetNodeFlags
	#define GET_IecVarAccGetNodeFlags(fl)  CAL_CMGETAPI( "IecVarAccGetNodeFlags" ) 
	#define CAL_IecVarAccGetNodeFlags  IecVarAccGetNodeFlags
	#define CHK_IecVarAccGetNodeFlags  TRUE
	#define EXP_IecVarAccGetNodeFlags  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNodeFlags", (RTS_UINTPTR)IecVarAccGetNodeFlags, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetNodeFlags
	#define EXT_CmpIecVarAccessIecVarAccGetNodeFlags
	#define GET_CmpIecVarAccessIecVarAccGetNodeFlags  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetNodeFlags pICmpIecVarAccess->IIecVarAccGetNodeFlags
	#define CHK_CmpIecVarAccessIecVarAccGetNodeFlags (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetNodeFlags  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetNodeFlags
	#define EXT_IecVarAccGetNodeFlags
	#define GET_IecVarAccGetNodeFlags(fl)  CAL_CMGETAPI( "IecVarAccGetNodeFlags" ) 
	#define CAL_IecVarAccGetNodeFlags pICmpIecVarAccess->IIecVarAccGetNodeFlags
	#define CHK_IecVarAccGetNodeFlags (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetNodeFlags  CAL_CMEXPAPI( "IecVarAccGetNodeFlags" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetNodeFlags  PFIECVARACCGETNODEFLAGS pfIecVarAccGetNodeFlags;
	#define EXT_IecVarAccGetNodeFlags  extern PFIECVARACCGETNODEFLAGS pfIecVarAccGetNodeFlags;
	#define GET_IecVarAccGetNodeFlags(fl)  s_pfCMGetAPI2( "IecVarAccGetNodeFlags", (RTS_VOID_FCTPTR *)&pfIecVarAccGetNodeFlags, (fl), 0, 0)
	#define CAL_IecVarAccGetNodeFlags  pfIecVarAccGetNodeFlags
	#define CHK_IecVarAccGetNodeFlags  (pfIecVarAccGetNodeFlags != NULL)
	#define EXP_IecVarAccGetNodeFlags  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNodeFlags", (RTS_UINTPTR)IecVarAccGetNodeFlags, 0, 0) 
#endif




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
RTS_UI16 CDECL IecVarAccGetNumOfAttributes(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
typedef RTS_UI16 (CDECL * PFIECVARACCGETNUMOFATTRIBUTES) (RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNUMOFATTRIBUTES_NOTIMPLEMENTED)
	#define USE_IecVarAccGetNumOfAttributes
	#define EXT_IecVarAccGetNumOfAttributes
	#define GET_IecVarAccGetNumOfAttributes(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetNumOfAttributes(p0,p1,p2)  (RTS_UI16)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetNumOfAttributes  FALSE
	#define EXP_IecVarAccGetNumOfAttributes  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetNumOfAttributes
	#define EXT_IecVarAccGetNumOfAttributes
	#define GET_IecVarAccGetNumOfAttributes(fl)  CAL_CMGETAPI( "IecVarAccGetNumOfAttributes" ) 
	#define CAL_IecVarAccGetNumOfAttributes  IecVarAccGetNumOfAttributes
	#define CHK_IecVarAccGetNumOfAttributes  TRUE
	#define EXP_IecVarAccGetNumOfAttributes  CAL_CMEXPAPI( "IecVarAccGetNumOfAttributes" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetNumOfAttributes
	#define EXT_IecVarAccGetNumOfAttributes
	#define GET_IecVarAccGetNumOfAttributes(fl)  CAL_CMGETAPI( "IecVarAccGetNumOfAttributes" ) 
	#define CAL_IecVarAccGetNumOfAttributes  IecVarAccGetNumOfAttributes
	#define CHK_IecVarAccGetNumOfAttributes  TRUE
	#define EXP_IecVarAccGetNumOfAttributes  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNumOfAttributes", (RTS_UINTPTR)IecVarAccGetNumOfAttributes, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetNumOfAttributes
	#define EXT_CmpIecVarAccessIecVarAccGetNumOfAttributes
	#define GET_CmpIecVarAccessIecVarAccGetNumOfAttributes  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetNumOfAttributes pICmpIecVarAccess->IIecVarAccGetNumOfAttributes
	#define CHK_CmpIecVarAccessIecVarAccGetNumOfAttributes (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetNumOfAttributes  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetNumOfAttributes
	#define EXT_IecVarAccGetNumOfAttributes
	#define GET_IecVarAccGetNumOfAttributes(fl)  CAL_CMGETAPI( "IecVarAccGetNumOfAttributes" ) 
	#define CAL_IecVarAccGetNumOfAttributes pICmpIecVarAccess->IIecVarAccGetNumOfAttributes
	#define CHK_IecVarAccGetNumOfAttributes (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetNumOfAttributes  CAL_CMEXPAPI( "IecVarAccGetNumOfAttributes" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetNumOfAttributes  PFIECVARACCGETNUMOFATTRIBUTES pfIecVarAccGetNumOfAttributes;
	#define EXT_IecVarAccGetNumOfAttributes  extern PFIECVARACCGETNUMOFATTRIBUTES pfIecVarAccGetNumOfAttributes;
	#define GET_IecVarAccGetNumOfAttributes(fl)  s_pfCMGetAPI2( "IecVarAccGetNumOfAttributes", (RTS_VOID_FCTPTR *)&pfIecVarAccGetNumOfAttributes, (fl), 0, 0)
	#define CAL_IecVarAccGetNumOfAttributes  pfIecVarAccGetNumOfAttributes
	#define CHK_IecVarAccGetNumOfAttributes  (pfIecVarAccGetNumOfAttributes != NULL)
	#define EXP_IecVarAccGetNumOfAttributes  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNumOfAttributes", (RTS_UINTPTR)IecVarAccGetNumOfAttributes, 0, 0) 
#endif




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
char* CDECL IecVarAccGetAttributeByIndex(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_UI16 ui16Index, RTS_RESULT *pResult);
typedef char* (CDECL * PFIECVARACCGETATTRIBUTEBYINDEX) (RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_UI16 ui16Index, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETATTRIBUTEBYINDEX_NOTIMPLEMENTED)
	#define USE_IecVarAccGetAttributeByIndex
	#define EXT_IecVarAccGetAttributeByIndex
	#define GET_IecVarAccGetAttributeByIndex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetAttributeByIndex(p0,p1,p2,p3)  (char*)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetAttributeByIndex  FALSE
	#define EXP_IecVarAccGetAttributeByIndex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetAttributeByIndex
	#define EXT_IecVarAccGetAttributeByIndex
	#define GET_IecVarAccGetAttributeByIndex(fl)  CAL_CMGETAPI( "IecVarAccGetAttributeByIndex" ) 
	#define CAL_IecVarAccGetAttributeByIndex  IecVarAccGetAttributeByIndex
	#define CHK_IecVarAccGetAttributeByIndex  TRUE
	#define EXP_IecVarAccGetAttributeByIndex  CAL_CMEXPAPI( "IecVarAccGetAttributeByIndex" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetAttributeByIndex
	#define EXT_IecVarAccGetAttributeByIndex
	#define GET_IecVarAccGetAttributeByIndex(fl)  CAL_CMGETAPI( "IecVarAccGetAttributeByIndex" ) 
	#define CAL_IecVarAccGetAttributeByIndex  IecVarAccGetAttributeByIndex
	#define CHK_IecVarAccGetAttributeByIndex  TRUE
	#define EXP_IecVarAccGetAttributeByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetAttributeByIndex", (RTS_UINTPTR)IecVarAccGetAttributeByIndex, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetAttributeByIndex
	#define EXT_CmpIecVarAccessIecVarAccGetAttributeByIndex
	#define GET_CmpIecVarAccessIecVarAccGetAttributeByIndex  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetAttributeByIndex pICmpIecVarAccess->IIecVarAccGetAttributeByIndex
	#define CHK_CmpIecVarAccessIecVarAccGetAttributeByIndex (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetAttributeByIndex  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetAttributeByIndex
	#define EXT_IecVarAccGetAttributeByIndex
	#define GET_IecVarAccGetAttributeByIndex(fl)  CAL_CMGETAPI( "IecVarAccGetAttributeByIndex" ) 
	#define CAL_IecVarAccGetAttributeByIndex pICmpIecVarAccess->IIecVarAccGetAttributeByIndex
	#define CHK_IecVarAccGetAttributeByIndex (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetAttributeByIndex  CAL_CMEXPAPI( "IecVarAccGetAttributeByIndex" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetAttributeByIndex  PFIECVARACCGETATTRIBUTEBYINDEX pfIecVarAccGetAttributeByIndex;
	#define EXT_IecVarAccGetAttributeByIndex  extern PFIECVARACCGETATTRIBUTEBYINDEX pfIecVarAccGetAttributeByIndex;
	#define GET_IecVarAccGetAttributeByIndex(fl)  s_pfCMGetAPI2( "IecVarAccGetAttributeByIndex", (RTS_VOID_FCTPTR *)&pfIecVarAccGetAttributeByIndex, (fl), 0, 0)
	#define CAL_IecVarAccGetAttributeByIndex  pfIecVarAccGetAttributeByIndex
	#define CHK_IecVarAccGetAttributeByIndex  (pfIecVarAccGetAttributeByIndex != NULL)
	#define EXP_IecVarAccGetAttributeByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetAttributeByIndex", (RTS_UINTPTR)IecVarAccGetAttributeByIndex, 0, 0) 
#endif




/**
 * <description>Get the enum values of an IEC Enum type</description>
 * <param name="hInterface" type="IN">Handle to the symbolic interface</param>
 * <param name="hTypeNode" type="IN">Handle to the type node (is retrieved by IecVarAccGetTypeNode or IecVarAccGetTypeNode2)</param>
 * <param name="pui16NumOfEnums" type="OUT">Pointer to the number of enum values in the returned array</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the array of enum values or NULL if it is not supported or this is no enum type</result>
 */
EnumValues* CDECL IecVarAccGetEnumValues(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_I16 *pi16NumOfEnums, RTS_RESULT *pResult);
typedef EnumValues* (CDECL * PFIECVARACCGETENUMVALUES) (RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_I16 *pi16NumOfEnums, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETENUMVALUES_NOTIMPLEMENTED)
	#define USE_IecVarAccGetEnumValues
	#define EXT_IecVarAccGetEnumValues
	#define GET_IecVarAccGetEnumValues(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetEnumValues(p0,p1,p2,p3)  (EnumValues*)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetEnumValues  FALSE
	#define EXP_IecVarAccGetEnumValues  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetEnumValues
	#define EXT_IecVarAccGetEnumValues
	#define GET_IecVarAccGetEnumValues(fl)  CAL_CMGETAPI( "IecVarAccGetEnumValues" ) 
	#define CAL_IecVarAccGetEnumValues  IecVarAccGetEnumValues
	#define CHK_IecVarAccGetEnumValues  TRUE
	#define EXP_IecVarAccGetEnumValues  CAL_CMEXPAPI( "IecVarAccGetEnumValues" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetEnumValues
	#define EXT_IecVarAccGetEnumValues
	#define GET_IecVarAccGetEnumValues(fl)  CAL_CMGETAPI( "IecVarAccGetEnumValues" ) 
	#define CAL_IecVarAccGetEnumValues  IecVarAccGetEnumValues
	#define CHK_IecVarAccGetEnumValues  TRUE
	#define EXP_IecVarAccGetEnumValues  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetEnumValues", (RTS_UINTPTR)IecVarAccGetEnumValues, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetEnumValues
	#define EXT_CmpIecVarAccessIecVarAccGetEnumValues
	#define GET_CmpIecVarAccessIecVarAccGetEnumValues  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetEnumValues pICmpIecVarAccess->IIecVarAccGetEnumValues
	#define CHK_CmpIecVarAccessIecVarAccGetEnumValues (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetEnumValues  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetEnumValues
	#define EXT_IecVarAccGetEnumValues
	#define GET_IecVarAccGetEnumValues(fl)  CAL_CMGETAPI( "IecVarAccGetEnumValues" ) 
	#define CAL_IecVarAccGetEnumValues pICmpIecVarAccess->IIecVarAccGetEnumValues
	#define CHK_IecVarAccGetEnumValues (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetEnumValues  CAL_CMEXPAPI( "IecVarAccGetEnumValues" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetEnumValues  PFIECVARACCGETENUMVALUES pfIecVarAccGetEnumValues;
	#define EXT_IecVarAccGetEnumValues  extern PFIECVARACCGETENUMVALUES pfIecVarAccGetEnumValues;
	#define GET_IecVarAccGetEnumValues(fl)  s_pfCMGetAPI2( "IecVarAccGetEnumValues", (RTS_VOID_FCTPTR *)&pfIecVarAccGetEnumValues, (fl), 0, 0)
	#define CAL_IecVarAccGetEnumValues  pfIecVarAccGetEnumValues
	#define CHK_IecVarAccGetEnumValues  (pfIecVarAccGetEnumValues != NULL)
	#define EXP_IecVarAccGetEnumValues  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetEnumValues", (RTS_UINTPTR)IecVarAccGetEnumValues, 0, 0) 
#endif




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
RTS_HANDLE CDECL IecVarAccGetDerivedBaseType(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIECVARACCGETDERIVEDBASETYPE) (RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETDERIVEDBASETYPE_NOTIMPLEMENTED)
	#define USE_IecVarAccGetDerivedBaseType
	#define EXT_IecVarAccGetDerivedBaseType
	#define GET_IecVarAccGetDerivedBaseType(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetDerivedBaseType(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IecVarAccGetDerivedBaseType  FALSE
	#define EXP_IecVarAccGetDerivedBaseType  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetDerivedBaseType
	#define EXT_IecVarAccGetDerivedBaseType
	#define GET_IecVarAccGetDerivedBaseType(fl)  CAL_CMGETAPI( "IecVarAccGetDerivedBaseType" ) 
	#define CAL_IecVarAccGetDerivedBaseType  IecVarAccGetDerivedBaseType
	#define CHK_IecVarAccGetDerivedBaseType  TRUE
	#define EXP_IecVarAccGetDerivedBaseType  CAL_CMEXPAPI( "IecVarAccGetDerivedBaseType" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetDerivedBaseType
	#define EXT_IecVarAccGetDerivedBaseType
	#define GET_IecVarAccGetDerivedBaseType(fl)  CAL_CMGETAPI( "IecVarAccGetDerivedBaseType" ) 
	#define CAL_IecVarAccGetDerivedBaseType  IecVarAccGetDerivedBaseType
	#define CHK_IecVarAccGetDerivedBaseType  TRUE
	#define EXP_IecVarAccGetDerivedBaseType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetDerivedBaseType", (RTS_UINTPTR)IecVarAccGetDerivedBaseType, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetDerivedBaseType
	#define EXT_CmpIecVarAccessIecVarAccGetDerivedBaseType
	#define GET_CmpIecVarAccessIecVarAccGetDerivedBaseType  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetDerivedBaseType pICmpIecVarAccess->IIecVarAccGetDerivedBaseType
	#define CHK_CmpIecVarAccessIecVarAccGetDerivedBaseType (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetDerivedBaseType  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetDerivedBaseType
	#define EXT_IecVarAccGetDerivedBaseType
	#define GET_IecVarAccGetDerivedBaseType(fl)  CAL_CMGETAPI( "IecVarAccGetDerivedBaseType" ) 
	#define CAL_IecVarAccGetDerivedBaseType pICmpIecVarAccess->IIecVarAccGetDerivedBaseType
	#define CHK_IecVarAccGetDerivedBaseType (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetDerivedBaseType  CAL_CMEXPAPI( "IecVarAccGetDerivedBaseType" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetDerivedBaseType  PFIECVARACCGETDERIVEDBASETYPE pfIecVarAccGetDerivedBaseType;
	#define EXT_IecVarAccGetDerivedBaseType  extern PFIECVARACCGETDERIVEDBASETYPE pfIecVarAccGetDerivedBaseType;
	#define GET_IecVarAccGetDerivedBaseType(fl)  s_pfCMGetAPI2( "IecVarAccGetDerivedBaseType", (RTS_VOID_FCTPTR *)&pfIecVarAccGetDerivedBaseType, (fl), 0, 0)
	#define CAL_IecVarAccGetDerivedBaseType  pfIecVarAccGetDerivedBaseType
	#define CHK_IecVarAccGetDerivedBaseType  (pfIecVarAccGetDerivedBaseType != NULL)
	#define EXP_IecVarAccGetDerivedBaseType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetDerivedBaseType", (RTS_UINTPTR)IecVarAccGetDerivedBaseType, 0, 0) 
#endif




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
RTS_BOOL CDECL IecVarAccIsDerivedType(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_RESULT *pResult);
typedef RTS_BOOL (CDECL * PFIECVARACCISDERIVEDTYPE) (RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCISDERIVEDTYPE_NOTIMPLEMENTED)
	#define USE_IecVarAccIsDerivedType
	#define EXT_IecVarAccIsDerivedType
	#define GET_IecVarAccIsDerivedType(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccIsDerivedType(p0,p1,p2)  (RTS_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccIsDerivedType  FALSE
	#define EXP_IecVarAccIsDerivedType  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccIsDerivedType
	#define EXT_IecVarAccIsDerivedType
	#define GET_IecVarAccIsDerivedType(fl)  CAL_CMGETAPI( "IecVarAccIsDerivedType" ) 
	#define CAL_IecVarAccIsDerivedType  IecVarAccIsDerivedType
	#define CHK_IecVarAccIsDerivedType  TRUE
	#define EXP_IecVarAccIsDerivedType  CAL_CMEXPAPI( "IecVarAccIsDerivedType" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccIsDerivedType
	#define EXT_IecVarAccIsDerivedType
	#define GET_IecVarAccIsDerivedType(fl)  CAL_CMGETAPI( "IecVarAccIsDerivedType" ) 
	#define CAL_IecVarAccIsDerivedType  IecVarAccIsDerivedType
	#define CHK_IecVarAccIsDerivedType  TRUE
	#define EXP_IecVarAccIsDerivedType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccIsDerivedType", (RTS_UINTPTR)IecVarAccIsDerivedType, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccIsDerivedType
	#define EXT_CmpIecVarAccessIecVarAccIsDerivedType
	#define GET_CmpIecVarAccessIecVarAccIsDerivedType  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccIsDerivedType pICmpIecVarAccess->IIecVarAccIsDerivedType
	#define CHK_CmpIecVarAccessIecVarAccIsDerivedType (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccIsDerivedType  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccIsDerivedType
	#define EXT_IecVarAccIsDerivedType
	#define GET_IecVarAccIsDerivedType(fl)  CAL_CMGETAPI( "IecVarAccIsDerivedType" ) 
	#define CAL_IecVarAccIsDerivedType pICmpIecVarAccess->IIecVarAccIsDerivedType
	#define CHK_IecVarAccIsDerivedType (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccIsDerivedType  CAL_CMEXPAPI( "IecVarAccIsDerivedType" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccIsDerivedType  PFIECVARACCISDERIVEDTYPE pfIecVarAccIsDerivedType;
	#define EXT_IecVarAccIsDerivedType  extern PFIECVARACCISDERIVEDTYPE pfIecVarAccIsDerivedType;
	#define GET_IecVarAccIsDerivedType(fl)  s_pfCMGetAPI2( "IecVarAccIsDerivedType", (RTS_VOID_FCTPTR *)&pfIecVarAccIsDerivedType, (fl), 0, 0)
	#define CAL_IecVarAccIsDerivedType  pfIecVarAccIsDerivedType
	#define CHK_IecVarAccIsDerivedType  (pfIecVarAccIsDerivedType != NULL)
	#define EXP_IecVarAccIsDerivedType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccIsDerivedType", (RTS_UINTPTR)IecVarAccIsDerivedType, 0, 0) 
#endif




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
RTS_SIZE CDECL IecVarAccGetClientOffset(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFIECVARACCGETCLIENTOFFSET) (RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETCLIENTOFFSET_NOTIMPLEMENTED)
	#define USE_IecVarAccGetClientOffset
	#define EXT_IecVarAccGetClientOffset
	#define GET_IecVarAccGetClientOffset(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetClientOffset(p0,p1,p2)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetClientOffset  FALSE
	#define EXP_IecVarAccGetClientOffset  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetClientOffset
	#define EXT_IecVarAccGetClientOffset
	#define GET_IecVarAccGetClientOffset(fl)  CAL_CMGETAPI( "IecVarAccGetClientOffset" ) 
	#define CAL_IecVarAccGetClientOffset  IecVarAccGetClientOffset
	#define CHK_IecVarAccGetClientOffset  TRUE
	#define EXP_IecVarAccGetClientOffset  CAL_CMEXPAPI( "IecVarAccGetClientOffset" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetClientOffset
	#define EXT_IecVarAccGetClientOffset
	#define GET_IecVarAccGetClientOffset(fl)  CAL_CMGETAPI( "IecVarAccGetClientOffset" ) 
	#define CAL_IecVarAccGetClientOffset  IecVarAccGetClientOffset
	#define CHK_IecVarAccGetClientOffset  TRUE
	#define EXP_IecVarAccGetClientOffset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetClientOffset", (RTS_UINTPTR)IecVarAccGetClientOffset, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetClientOffset
	#define EXT_CmpIecVarAccessIecVarAccGetClientOffset
	#define GET_CmpIecVarAccessIecVarAccGetClientOffset  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetClientOffset pICmpIecVarAccess->IIecVarAccGetClientOffset
	#define CHK_CmpIecVarAccessIecVarAccGetClientOffset (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetClientOffset  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetClientOffset
	#define EXT_IecVarAccGetClientOffset
	#define GET_IecVarAccGetClientOffset(fl)  CAL_CMGETAPI( "IecVarAccGetClientOffset" ) 
	#define CAL_IecVarAccGetClientOffset pICmpIecVarAccess->IIecVarAccGetClientOffset
	#define CHK_IecVarAccGetClientOffset (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetClientOffset  CAL_CMEXPAPI( "IecVarAccGetClientOffset" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetClientOffset  PFIECVARACCGETCLIENTOFFSET pfIecVarAccGetClientOffset;
	#define EXT_IecVarAccGetClientOffset  extern PFIECVARACCGETCLIENTOFFSET pfIecVarAccGetClientOffset;
	#define GET_IecVarAccGetClientOffset(fl)  s_pfCMGetAPI2( "IecVarAccGetClientOffset", (RTS_VOID_FCTPTR *)&pfIecVarAccGetClientOffset, (fl), 0, 0)
	#define CAL_IecVarAccGetClientOffset  pfIecVarAccGetClientOffset
	#define CHK_IecVarAccGetClientOffset  (pfIecVarAccGetClientOffset != NULL)
	#define EXP_IecVarAccGetClientOffset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetClientOffset", (RTS_UINTPTR)IecVarAccGetClientOffset, 0, 0) 
#endif




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
NAMESPACENODEFLAGS CDECL IecVarAccGetNamespaceNodeFlags(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
typedef NAMESPACENODEFLAGS (CDECL * PFIECVARACCGETNAMESPACENODEFLAGS) (RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNAMESPACENODEFLAGS_NOTIMPLEMENTED)
	#define USE_IecVarAccGetNamespaceNodeFlags
	#define EXT_IecVarAccGetNamespaceNodeFlags
	#define GET_IecVarAccGetNamespaceNodeFlags(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetNamespaceNodeFlags(p0,p1,p2)  (NAMESPACENODEFLAGS)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetNamespaceNodeFlags  FALSE
	#define EXP_IecVarAccGetNamespaceNodeFlags  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetNamespaceNodeFlags
	#define EXT_IecVarAccGetNamespaceNodeFlags
	#define GET_IecVarAccGetNamespaceNodeFlags(fl)  CAL_CMGETAPI( "IecVarAccGetNamespaceNodeFlags" ) 
	#define CAL_IecVarAccGetNamespaceNodeFlags  IecVarAccGetNamespaceNodeFlags
	#define CHK_IecVarAccGetNamespaceNodeFlags  TRUE
	#define EXP_IecVarAccGetNamespaceNodeFlags  CAL_CMEXPAPI( "IecVarAccGetNamespaceNodeFlags" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetNamespaceNodeFlags
	#define EXT_IecVarAccGetNamespaceNodeFlags
	#define GET_IecVarAccGetNamespaceNodeFlags(fl)  CAL_CMGETAPI( "IecVarAccGetNamespaceNodeFlags" ) 
	#define CAL_IecVarAccGetNamespaceNodeFlags  IecVarAccGetNamespaceNodeFlags
	#define CHK_IecVarAccGetNamespaceNodeFlags  TRUE
	#define EXP_IecVarAccGetNamespaceNodeFlags  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNamespaceNodeFlags", (RTS_UINTPTR)IecVarAccGetNamespaceNodeFlags, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetNamespaceNodeFlags
	#define EXT_CmpIecVarAccessIecVarAccGetNamespaceNodeFlags
	#define GET_CmpIecVarAccessIecVarAccGetNamespaceNodeFlags  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetNamespaceNodeFlags pICmpIecVarAccess->IIecVarAccGetNamespaceNodeFlags
	#define CHK_CmpIecVarAccessIecVarAccGetNamespaceNodeFlags (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetNamespaceNodeFlags  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetNamespaceNodeFlags
	#define EXT_IecVarAccGetNamespaceNodeFlags
	#define GET_IecVarAccGetNamespaceNodeFlags(fl)  CAL_CMGETAPI( "IecVarAccGetNamespaceNodeFlags" ) 
	#define CAL_IecVarAccGetNamespaceNodeFlags pICmpIecVarAccess->IIecVarAccGetNamespaceNodeFlags
	#define CHK_IecVarAccGetNamespaceNodeFlags (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetNamespaceNodeFlags  CAL_CMEXPAPI( "IecVarAccGetNamespaceNodeFlags" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetNamespaceNodeFlags  PFIECVARACCGETNAMESPACENODEFLAGS pfIecVarAccGetNamespaceNodeFlags;
	#define EXT_IecVarAccGetNamespaceNodeFlags  extern PFIECVARACCGETNAMESPACENODEFLAGS pfIecVarAccGetNamespaceNodeFlags;
	#define GET_IecVarAccGetNamespaceNodeFlags(fl)  s_pfCMGetAPI2( "IecVarAccGetNamespaceNodeFlags", (RTS_VOID_FCTPTR *)&pfIecVarAccGetNamespaceNodeFlags, (fl), 0, 0)
	#define CAL_IecVarAccGetNamespaceNodeFlags  pfIecVarAccGetNamespaceNodeFlags
	#define CHK_IecVarAccGetNamespaceNodeFlags  (pfIecVarAccGetNamespaceNodeFlags != NULL)
	#define EXP_IecVarAccGetNamespaceNodeFlags  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNamespaceNodeFlags", (RTS_UINTPTR)IecVarAccGetNamespaceNodeFlags, 0, 0) 
#endif




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
RTS_SIZE CDECL IecVarAccGetNativeSize(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFIECVARACCGETNATIVESIZE) (RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNATIVESIZE_NOTIMPLEMENTED)
	#define USE_IecVarAccGetNativeSize
	#define EXT_IecVarAccGetNativeSize
	#define GET_IecVarAccGetNativeSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetNativeSize(p0,p1,p2,p3)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetNativeSize  FALSE
	#define EXP_IecVarAccGetNativeSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetNativeSize
	#define EXT_IecVarAccGetNativeSize
	#define GET_IecVarAccGetNativeSize(fl)  CAL_CMGETAPI( "IecVarAccGetNativeSize" ) 
	#define CAL_IecVarAccGetNativeSize  IecVarAccGetNativeSize
	#define CHK_IecVarAccGetNativeSize  TRUE
	#define EXP_IecVarAccGetNativeSize  CAL_CMEXPAPI( "IecVarAccGetNativeSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetNativeSize
	#define EXT_IecVarAccGetNativeSize
	#define GET_IecVarAccGetNativeSize(fl)  CAL_CMGETAPI( "IecVarAccGetNativeSize" ) 
	#define CAL_IecVarAccGetNativeSize  IecVarAccGetNativeSize
	#define CHK_IecVarAccGetNativeSize  TRUE
	#define EXP_IecVarAccGetNativeSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNativeSize", (RTS_UINTPTR)IecVarAccGetNativeSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetNativeSize
	#define EXT_CmpIecVarAccessIecVarAccGetNativeSize
	#define GET_CmpIecVarAccessIecVarAccGetNativeSize  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetNativeSize pICmpIecVarAccess->IIecVarAccGetNativeSize
	#define CHK_CmpIecVarAccessIecVarAccGetNativeSize (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetNativeSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetNativeSize
	#define EXT_IecVarAccGetNativeSize
	#define GET_IecVarAccGetNativeSize(fl)  CAL_CMGETAPI( "IecVarAccGetNativeSize" ) 
	#define CAL_IecVarAccGetNativeSize pICmpIecVarAccess->IIecVarAccGetNativeSize
	#define CHK_IecVarAccGetNativeSize (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetNativeSize  CAL_CMEXPAPI( "IecVarAccGetNativeSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetNativeSize  PFIECVARACCGETNATIVESIZE pfIecVarAccGetNativeSize;
	#define EXT_IecVarAccGetNativeSize  extern PFIECVARACCGETNATIVESIZE pfIecVarAccGetNativeSize;
	#define GET_IecVarAccGetNativeSize(fl)  s_pfCMGetAPI2( "IecVarAccGetNativeSize", (RTS_VOID_FCTPTR *)&pfIecVarAccGetNativeSize, (fl), 0, 0)
	#define CAL_IecVarAccGetNativeSize  pfIecVarAccGetNativeSize
	#define CHK_IecVarAccGetNativeSize  (pfIecVarAccGetNativeSize != NULL)
	#define EXP_IecVarAccGetNativeSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNativeSize", (RTS_UINTPTR)IecVarAccGetNativeSize, 0, 0) 
#endif




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
EnumAttributes* CDECL IecVarAccGetEnumMemberAttributeList(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_I16* pnNumOfEnumValues, RTS_RESULT* pResult);
typedef EnumAttributes* (CDECL * PFIECVARACCGETENUMMEMBERATTRIBUTELIST) (RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_I16* pnNumOfEnumValues, RTS_RESULT* pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETENUMMEMBERATTRIBUTELIST_NOTIMPLEMENTED)
	#define USE_IecVarAccGetEnumMemberAttributeList
	#define EXT_IecVarAccGetEnumMemberAttributeList
	#define GET_IecVarAccGetEnumMemberAttributeList(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetEnumMemberAttributeList(p0,p1,p2,p3)  (EnumAttributes*)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetEnumMemberAttributeList  FALSE
	#define EXP_IecVarAccGetEnumMemberAttributeList  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetEnumMemberAttributeList
	#define EXT_IecVarAccGetEnumMemberAttributeList
	#define GET_IecVarAccGetEnumMemberAttributeList(fl)  CAL_CMGETAPI( "IecVarAccGetEnumMemberAttributeList" ) 
	#define CAL_IecVarAccGetEnumMemberAttributeList  IecVarAccGetEnumMemberAttributeList
	#define CHK_IecVarAccGetEnumMemberAttributeList  TRUE
	#define EXP_IecVarAccGetEnumMemberAttributeList  CAL_CMEXPAPI( "IecVarAccGetEnumMemberAttributeList" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetEnumMemberAttributeList
	#define EXT_IecVarAccGetEnumMemberAttributeList
	#define GET_IecVarAccGetEnumMemberAttributeList(fl)  CAL_CMGETAPI( "IecVarAccGetEnumMemberAttributeList" ) 
	#define CAL_IecVarAccGetEnumMemberAttributeList  IecVarAccGetEnumMemberAttributeList
	#define CHK_IecVarAccGetEnumMemberAttributeList  TRUE
	#define EXP_IecVarAccGetEnumMemberAttributeList  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetEnumMemberAttributeList", (RTS_UINTPTR)IecVarAccGetEnumMemberAttributeList, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetEnumMemberAttributeList
	#define EXT_CmpIecVarAccessIecVarAccGetEnumMemberAttributeList
	#define GET_CmpIecVarAccessIecVarAccGetEnumMemberAttributeList  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetEnumMemberAttributeList pICmpIecVarAccess->IIecVarAccGetEnumMemberAttributeList
	#define CHK_CmpIecVarAccessIecVarAccGetEnumMemberAttributeList (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetEnumMemberAttributeList  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetEnumMemberAttributeList
	#define EXT_IecVarAccGetEnumMemberAttributeList
	#define GET_IecVarAccGetEnumMemberAttributeList(fl)  CAL_CMGETAPI( "IecVarAccGetEnumMemberAttributeList" ) 
	#define CAL_IecVarAccGetEnumMemberAttributeList pICmpIecVarAccess->IIecVarAccGetEnumMemberAttributeList
	#define CHK_IecVarAccGetEnumMemberAttributeList (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetEnumMemberAttributeList  CAL_CMEXPAPI( "IecVarAccGetEnumMemberAttributeList" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetEnumMemberAttributeList  PFIECVARACCGETENUMMEMBERATTRIBUTELIST pfIecVarAccGetEnumMemberAttributeList;
	#define EXT_IecVarAccGetEnumMemberAttributeList  extern PFIECVARACCGETENUMMEMBERATTRIBUTELIST pfIecVarAccGetEnumMemberAttributeList;
	#define GET_IecVarAccGetEnumMemberAttributeList(fl)  s_pfCMGetAPI2( "IecVarAccGetEnumMemberAttributeList", (RTS_VOID_FCTPTR *)&pfIecVarAccGetEnumMemberAttributeList, (fl), 0, 0)
	#define CAL_IecVarAccGetEnumMemberAttributeList  pfIecVarAccGetEnumMemberAttributeList
	#define CHK_IecVarAccGetEnumMemberAttributeList  (pfIecVarAccGetEnumMemberAttributeList != NULL)
	#define EXP_IecVarAccGetEnumMemberAttributeList  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetEnumMemberAttributeList", (RTS_UINTPTR)IecVarAccGetEnumMemberAttributeList, 0, 0) 
#endif




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
RTS_UI16 CDECL IecVarAccGetNumOfTypeAttributes(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_RESULT* pResult);
typedef RTS_UI16 (CDECL * PFIECVARACCGETNUMOFTYPEATTRIBUTES) (RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_RESULT* pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETNUMOFTYPEATTRIBUTES_NOTIMPLEMENTED)
	#define USE_IecVarAccGetNumOfTypeAttributes
	#define EXT_IecVarAccGetNumOfTypeAttributes
	#define GET_IecVarAccGetNumOfTypeAttributes(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetNumOfTypeAttributes(p0,p1,p2)  (RTS_UI16)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetNumOfTypeAttributes  FALSE
	#define EXP_IecVarAccGetNumOfTypeAttributes  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetNumOfTypeAttributes
	#define EXT_IecVarAccGetNumOfTypeAttributes
	#define GET_IecVarAccGetNumOfTypeAttributes(fl)  CAL_CMGETAPI( "IecVarAccGetNumOfTypeAttributes" ) 
	#define CAL_IecVarAccGetNumOfTypeAttributes  IecVarAccGetNumOfTypeAttributes
	#define CHK_IecVarAccGetNumOfTypeAttributes  TRUE
	#define EXP_IecVarAccGetNumOfTypeAttributes  CAL_CMEXPAPI( "IecVarAccGetNumOfTypeAttributes" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetNumOfTypeAttributes
	#define EXT_IecVarAccGetNumOfTypeAttributes
	#define GET_IecVarAccGetNumOfTypeAttributes(fl)  CAL_CMGETAPI( "IecVarAccGetNumOfTypeAttributes" ) 
	#define CAL_IecVarAccGetNumOfTypeAttributes  IecVarAccGetNumOfTypeAttributes
	#define CHK_IecVarAccGetNumOfTypeAttributes  TRUE
	#define EXP_IecVarAccGetNumOfTypeAttributes  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNumOfTypeAttributes", (RTS_UINTPTR)IecVarAccGetNumOfTypeAttributes, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetNumOfTypeAttributes
	#define EXT_CmpIecVarAccessIecVarAccGetNumOfTypeAttributes
	#define GET_CmpIecVarAccessIecVarAccGetNumOfTypeAttributes  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetNumOfTypeAttributes pICmpIecVarAccess->IIecVarAccGetNumOfTypeAttributes
	#define CHK_CmpIecVarAccessIecVarAccGetNumOfTypeAttributes (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetNumOfTypeAttributes  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetNumOfTypeAttributes
	#define EXT_IecVarAccGetNumOfTypeAttributes
	#define GET_IecVarAccGetNumOfTypeAttributes(fl)  CAL_CMGETAPI( "IecVarAccGetNumOfTypeAttributes" ) 
	#define CAL_IecVarAccGetNumOfTypeAttributes pICmpIecVarAccess->IIecVarAccGetNumOfTypeAttributes
	#define CHK_IecVarAccGetNumOfTypeAttributes (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetNumOfTypeAttributes  CAL_CMEXPAPI( "IecVarAccGetNumOfTypeAttributes" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetNumOfTypeAttributes  PFIECVARACCGETNUMOFTYPEATTRIBUTES pfIecVarAccGetNumOfTypeAttributes;
	#define EXT_IecVarAccGetNumOfTypeAttributes  extern PFIECVARACCGETNUMOFTYPEATTRIBUTES pfIecVarAccGetNumOfTypeAttributes;
	#define GET_IecVarAccGetNumOfTypeAttributes(fl)  s_pfCMGetAPI2( "IecVarAccGetNumOfTypeAttributes", (RTS_VOID_FCTPTR *)&pfIecVarAccGetNumOfTypeAttributes, (fl), 0, 0)
	#define CAL_IecVarAccGetNumOfTypeAttributes  pfIecVarAccGetNumOfTypeAttributes
	#define CHK_IecVarAccGetNumOfTypeAttributes  (pfIecVarAccGetNumOfTypeAttributes != NULL)
	#define EXP_IecVarAccGetNumOfTypeAttributes  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetNumOfTypeAttributes", (RTS_UINTPTR)IecVarAccGetNumOfTypeAttributes, 0, 0) 
#endif




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
char* CDECL IecVarAccGetTypeAttributeByIndex(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_UI16 wIndex, RTS_RESULT* pResult);
typedef char* (CDECL * PFIECVARACCGETTYPEATTRIBUTEBYINDEX) (RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_UI16 wIndex, RTS_RESULT* pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETTYPEATTRIBUTEBYINDEX_NOTIMPLEMENTED)
	#define USE_IecVarAccGetTypeAttributeByIndex
	#define EXT_IecVarAccGetTypeAttributeByIndex
	#define GET_IecVarAccGetTypeAttributeByIndex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetTypeAttributeByIndex(p0,p1,p2,p3)  (char*)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetTypeAttributeByIndex  FALSE
	#define EXP_IecVarAccGetTypeAttributeByIndex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetTypeAttributeByIndex
	#define EXT_IecVarAccGetTypeAttributeByIndex
	#define GET_IecVarAccGetTypeAttributeByIndex(fl)  CAL_CMGETAPI( "IecVarAccGetTypeAttributeByIndex" ) 
	#define CAL_IecVarAccGetTypeAttributeByIndex  IecVarAccGetTypeAttributeByIndex
	#define CHK_IecVarAccGetTypeAttributeByIndex  TRUE
	#define EXP_IecVarAccGetTypeAttributeByIndex  CAL_CMEXPAPI( "IecVarAccGetTypeAttributeByIndex" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetTypeAttributeByIndex
	#define EXT_IecVarAccGetTypeAttributeByIndex
	#define GET_IecVarAccGetTypeAttributeByIndex(fl)  CAL_CMGETAPI( "IecVarAccGetTypeAttributeByIndex" ) 
	#define CAL_IecVarAccGetTypeAttributeByIndex  IecVarAccGetTypeAttributeByIndex
	#define CHK_IecVarAccGetTypeAttributeByIndex  TRUE
	#define EXP_IecVarAccGetTypeAttributeByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetTypeAttributeByIndex", (RTS_UINTPTR)IecVarAccGetTypeAttributeByIndex, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetTypeAttributeByIndex
	#define EXT_CmpIecVarAccessIecVarAccGetTypeAttributeByIndex
	#define GET_CmpIecVarAccessIecVarAccGetTypeAttributeByIndex  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetTypeAttributeByIndex pICmpIecVarAccess->IIecVarAccGetTypeAttributeByIndex
	#define CHK_CmpIecVarAccessIecVarAccGetTypeAttributeByIndex (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetTypeAttributeByIndex  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetTypeAttributeByIndex
	#define EXT_IecVarAccGetTypeAttributeByIndex
	#define GET_IecVarAccGetTypeAttributeByIndex(fl)  CAL_CMGETAPI( "IecVarAccGetTypeAttributeByIndex" ) 
	#define CAL_IecVarAccGetTypeAttributeByIndex pICmpIecVarAccess->IIecVarAccGetTypeAttributeByIndex
	#define CHK_IecVarAccGetTypeAttributeByIndex (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetTypeAttributeByIndex  CAL_CMEXPAPI( "IecVarAccGetTypeAttributeByIndex" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetTypeAttributeByIndex  PFIECVARACCGETTYPEATTRIBUTEBYINDEX pfIecVarAccGetTypeAttributeByIndex;
	#define EXT_IecVarAccGetTypeAttributeByIndex  extern PFIECVARACCGETTYPEATTRIBUTEBYINDEX pfIecVarAccGetTypeAttributeByIndex;
	#define GET_IecVarAccGetTypeAttributeByIndex(fl)  s_pfCMGetAPI2( "IecVarAccGetTypeAttributeByIndex", (RTS_VOID_FCTPTR *)&pfIecVarAccGetTypeAttributeByIndex, (fl), 0, 0)
	#define CAL_IecVarAccGetTypeAttributeByIndex  pfIecVarAccGetTypeAttributeByIndex
	#define CHK_IecVarAccGetTypeAttributeByIndex  (pfIecVarAccGetTypeAttributeByIndex != NULL)
	#define EXP_IecVarAccGetTypeAttributeByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetTypeAttributeByIndex", (RTS_UINTPTR)IecVarAccGetTypeAttributeByIndex, 0, 0) 
#endif




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
RTS_BOOL CDECL IecVarAccGetRange(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_UI64* pLower, RTS_UI64* pUpper, RTS_RESULT* pResult);
typedef RTS_BOOL (CDECL * PFIECVARACCGETRANGE) (RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_UI64* pLower, RTS_UI64* pUpper, RTS_RESULT* pResult);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETRANGE_NOTIMPLEMENTED)
	#define USE_IecVarAccGetRange
	#define EXT_IecVarAccGetRange
	#define GET_IecVarAccGetRange(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetRange(p0,p1,p2,p3,p4)  (RTS_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetRange  FALSE
	#define EXP_IecVarAccGetRange  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetRange
	#define EXT_IecVarAccGetRange
	#define GET_IecVarAccGetRange(fl)  CAL_CMGETAPI( "IecVarAccGetRange" ) 
	#define CAL_IecVarAccGetRange  IecVarAccGetRange
	#define CHK_IecVarAccGetRange  TRUE
	#define EXP_IecVarAccGetRange  CAL_CMEXPAPI( "IecVarAccGetRange" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetRange
	#define EXT_IecVarAccGetRange
	#define GET_IecVarAccGetRange(fl)  CAL_CMGETAPI( "IecVarAccGetRange" ) 
	#define CAL_IecVarAccGetRange  IecVarAccGetRange
	#define CHK_IecVarAccGetRange  TRUE
	#define EXP_IecVarAccGetRange  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetRange", (RTS_UINTPTR)IecVarAccGetRange, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetRange
	#define EXT_CmpIecVarAccessIecVarAccGetRange
	#define GET_CmpIecVarAccessIecVarAccGetRange  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetRange pICmpIecVarAccess->IIecVarAccGetRange
	#define CHK_CmpIecVarAccessIecVarAccGetRange (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetRange  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetRange
	#define EXT_IecVarAccGetRange
	#define GET_IecVarAccGetRange(fl)  CAL_CMGETAPI( "IecVarAccGetRange" ) 
	#define CAL_IecVarAccGetRange pICmpIecVarAccess->IIecVarAccGetRange
	#define CHK_IecVarAccGetRange (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetRange  CAL_CMEXPAPI( "IecVarAccGetRange" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetRange  PFIECVARACCGETRANGE pfIecVarAccGetRange;
	#define EXT_IecVarAccGetRange  extern PFIECVARACCGETRANGE pfIecVarAccGetRange;
	#define GET_IecVarAccGetRange(fl)  s_pfCMGetAPI2( "IecVarAccGetRange", (RTS_VOID_FCTPTR *)&pfIecVarAccGetRange, (fl), 0, 0)
	#define CAL_IecVarAccGetRange  pfIecVarAccGetRange
	#define CHK_IecVarAccGetRange  (pfIecVarAccGetRange != NULL)
	#define EXP_IecVarAccGetRange  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetRange", (RTS_UINTPTR)IecVarAccGetRange, 0, 0) 
#endif




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
RTS_RESULT CDECL IecVarAccGetContentFeatureFlags(RTS_HANDLE hInterface, CONTENTFEATUREFLAGS* pContentFeatureFlags);
typedef RTS_RESULT (CDECL * PFIECVARACCGETCONTENTFEATUREFLAGS) (RTS_HANDLE hInterface, CONTENTFEATUREFLAGS* pContentFeatureFlags);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCGETCONTENTFEATUREFLAGS_NOTIMPLEMENTED)
	#define USE_IecVarAccGetContentFeatureFlags
	#define EXT_IecVarAccGetContentFeatureFlags
	#define GET_IecVarAccGetContentFeatureFlags(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccGetContentFeatureFlags(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccGetContentFeatureFlags  FALSE
	#define EXP_IecVarAccGetContentFeatureFlags  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccGetContentFeatureFlags
	#define EXT_IecVarAccGetContentFeatureFlags
	#define GET_IecVarAccGetContentFeatureFlags(fl)  CAL_CMGETAPI( "IecVarAccGetContentFeatureFlags" ) 
	#define CAL_IecVarAccGetContentFeatureFlags  IecVarAccGetContentFeatureFlags
	#define CHK_IecVarAccGetContentFeatureFlags  TRUE
	#define EXP_IecVarAccGetContentFeatureFlags  CAL_CMEXPAPI( "IecVarAccGetContentFeatureFlags" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccGetContentFeatureFlags
	#define EXT_IecVarAccGetContentFeatureFlags
	#define GET_IecVarAccGetContentFeatureFlags(fl)  CAL_CMGETAPI( "IecVarAccGetContentFeatureFlags" ) 
	#define CAL_IecVarAccGetContentFeatureFlags  IecVarAccGetContentFeatureFlags
	#define CHK_IecVarAccGetContentFeatureFlags  TRUE
	#define EXP_IecVarAccGetContentFeatureFlags  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetContentFeatureFlags", (RTS_UINTPTR)IecVarAccGetContentFeatureFlags, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccGetContentFeatureFlags
	#define EXT_CmpIecVarAccessIecVarAccGetContentFeatureFlags
	#define GET_CmpIecVarAccessIecVarAccGetContentFeatureFlags  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccGetContentFeatureFlags pICmpIecVarAccess->IIecVarAccGetContentFeatureFlags
	#define CHK_CmpIecVarAccessIecVarAccGetContentFeatureFlags (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccGetContentFeatureFlags  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccGetContentFeatureFlags
	#define EXT_IecVarAccGetContentFeatureFlags
	#define GET_IecVarAccGetContentFeatureFlags(fl)  CAL_CMGETAPI( "IecVarAccGetContentFeatureFlags" ) 
	#define CAL_IecVarAccGetContentFeatureFlags pICmpIecVarAccess->IIecVarAccGetContentFeatureFlags
	#define CHK_IecVarAccGetContentFeatureFlags (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccGetContentFeatureFlags  CAL_CMEXPAPI( "IecVarAccGetContentFeatureFlags" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccGetContentFeatureFlags  PFIECVARACCGETCONTENTFEATUREFLAGS pfIecVarAccGetContentFeatureFlags;
	#define EXT_IecVarAccGetContentFeatureFlags  extern PFIECVARACCGETCONTENTFEATUREFLAGS pfIecVarAccGetContentFeatureFlags;
	#define GET_IecVarAccGetContentFeatureFlags(fl)  s_pfCMGetAPI2( "IecVarAccGetContentFeatureFlags", (RTS_VOID_FCTPTR *)&pfIecVarAccGetContentFeatureFlags, (fl), 0, 0)
	#define CAL_IecVarAccGetContentFeatureFlags  pfIecVarAccGetContentFeatureFlags
	#define CHK_IecVarAccGetContentFeatureFlags  (pfIecVarAccGetContentFeatureFlags != NULL)
	#define EXP_IecVarAccGetContentFeatureFlags  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccGetContentFeatureFlags", (RTS_UINTPTR)IecVarAccGetContentFeatureFlags, 0, 0) 
#endif




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
RTS_RESULT CDECL IecVarAccExecuteCall(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_UI8 *pArgumentBuffer, RTS_SIZE nArgumentBufferSize);
typedef RTS_RESULT (CDECL * PFIECVARACCEXECUTECALL) (RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_UI8 *pArgumentBuffer, RTS_SIZE nArgumentBufferSize);
#if defined(CMPIECVARACCESS_NOTIMPLEMENTED) || defined(IECVARACCEXECUTECALL_NOTIMPLEMENTED)
	#define USE_IecVarAccExecuteCall
	#define EXT_IecVarAccExecuteCall
	#define GET_IecVarAccExecuteCall(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IecVarAccExecuteCall(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IecVarAccExecuteCall  FALSE
	#define EXP_IecVarAccExecuteCall  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IecVarAccExecuteCall
	#define EXT_IecVarAccExecuteCall
	#define GET_IecVarAccExecuteCall(fl)  CAL_CMGETAPI( "IecVarAccExecuteCall" ) 
	#define CAL_IecVarAccExecuteCall  IecVarAccExecuteCall
	#define CHK_IecVarAccExecuteCall  TRUE
	#define EXP_IecVarAccExecuteCall  CAL_CMEXPAPI( "IecVarAccExecuteCall" ) 
#elif defined(MIXED_LINK) && !defined(CMPIECVARACCESS_EXTERNAL)
	#define USE_IecVarAccExecuteCall
	#define EXT_IecVarAccExecuteCall
	#define GET_IecVarAccExecuteCall(fl)  CAL_CMGETAPI( "IecVarAccExecuteCall" ) 
	#define CAL_IecVarAccExecuteCall  IecVarAccExecuteCall
	#define CHK_IecVarAccExecuteCall  TRUE
	#define EXP_IecVarAccExecuteCall  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccExecuteCall", (RTS_UINTPTR)IecVarAccExecuteCall, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIecVarAccessIecVarAccExecuteCall
	#define EXT_CmpIecVarAccessIecVarAccExecuteCall
	#define GET_CmpIecVarAccessIecVarAccExecuteCall  ERR_OK
	#define CAL_CmpIecVarAccessIecVarAccExecuteCall pICmpIecVarAccess->IIecVarAccExecuteCall
	#define CHK_CmpIecVarAccessIecVarAccExecuteCall (pICmpIecVarAccess != NULL)
	#define EXP_CmpIecVarAccessIecVarAccExecuteCall  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IecVarAccExecuteCall
	#define EXT_IecVarAccExecuteCall
	#define GET_IecVarAccExecuteCall(fl)  CAL_CMGETAPI( "IecVarAccExecuteCall" ) 
	#define CAL_IecVarAccExecuteCall pICmpIecVarAccess->IIecVarAccExecuteCall
	#define CHK_IecVarAccExecuteCall (pICmpIecVarAccess != NULL)
	#define EXP_IecVarAccExecuteCall  CAL_CMEXPAPI( "IecVarAccExecuteCall" ) 
#else /* DYNAMIC_LINK */
	#define USE_IecVarAccExecuteCall  PFIECVARACCEXECUTECALL pfIecVarAccExecuteCall;
	#define EXT_IecVarAccExecuteCall  extern PFIECVARACCEXECUTECALL pfIecVarAccExecuteCall;
	#define GET_IecVarAccExecuteCall(fl)  s_pfCMGetAPI2( "IecVarAccExecuteCall", (RTS_VOID_FCTPTR *)&pfIecVarAccExecuteCall, (fl), 0, 0)
	#define CAL_IecVarAccExecuteCall  pfIecVarAccExecuteCall
	#define CHK_IecVarAccExecuteCall  (pfIecVarAccExecuteCall != NULL)
	#define EXP_IecVarAccExecuteCall  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IecVarAccExecuteCall", (RTS_UINTPTR)IecVarAccExecuteCall, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFIECVARACCINITVARINFO IIecVarAccInitVarInfo;
 	PFIECVARACCEXITVARINFO IIecVarAccExitVarInfo;
 	PFIECVARACCCOPYVARINFO IIecVarAccCopyVarInfo;
 	PFIECVARACCGETFIRSTINTERFACE IIecVarAccGetFirstInterface;
 	PFIECVARACCGETNEXTINTERFACE IIecVarAccGetNextInterface;
 	PFIECVARACCGETAPPLICATIONNAME IIecVarAccGetApplicationName;
 	PFIECVARACCCREATEVARLIST IIecVarAccCreateVarList;
 	PFIECVARACCDELETEVARLIST IIecVarAccDeleteVarList;
 	PFIECVARACCDELETEVARLISTS IIecVarAccDeleteVarLists;
 	PFIECVARACCDELETEALLLISTS IIecVarAccDeleteAllLists;
 	PFIECVARACCVARLISTGETFLAGS IIecVarAccVarListGetFlags;
 	PFIECVARACCAPPENDVAR IIecVarAccAppendVar;
 	PFIECVARACCREMOVEVAR IIecVarAccRemoveVar;
 	PFIECVARACCGETFIRSTVAR IIecVarAccGetFirstVar;
 	PFIECVARACCGETNEXTVAR IIecVarAccGetNextVar;
 	PFIECVARACCINVALIDATEVAR IIecVarAccInvalidateVar;
 	PFIECVARACCREADVAR IIecVarAccReadVar;
 	PFIECVARACCWRITEVAR IIecVarAccWriteVar;
 	PFIECVARACCWRITEVAR2 IIecVarAccWriteVar2;
 	PFIECVARACCBEGINVARIABLECONFIGURATION IIecVarAccBeginVariableConfiguration;
 	PFIECVARACCAPPENDVARIABLE IIecVarAccAppendVariable;
 	PFIECVARACCAPPENDVARIABLE3 IIecVarAccAppendVariable3;
 	PFIECVARACCREMOVEVARIABLE IIecVarAccRemoveVariable;
 	PFIECVARACCREMOVEVARIABLE3 IIecVarAccRemoveVariable3;
 	PFIECVARACCENDVARIABLECONFIGURATION IIecVarAccEndVariableConfiguration;
 	PFIECVARACCBROWSERECURSIVE IIecVarAccBrowseRecursive;
 	PFIECVARACCBROWSEGETROOT IIecVarAccBrowseGetRoot;
 	PFIECVARACCBROWSEDOWN IIecVarAccBrowseDown;
 	PFIECVARACCBROWSEDOWN2 IIecVarAccBrowseDown2;
 	PFIECVARACCBROWSEUP IIecVarAccBrowseUp;
 	PFIECVARACCBROWSEUP2 IIecVarAccBrowseUp2;
 	PFIECVARACCBROWSEGETNEXT IIecVarAccBrowseGetNext;
 	PFIECVARACCBROWSEGETNEXT2 IIecVarAccBrowseGetNext2;
 	PFIECVARACCBROWSEGETCHILDBYINDEX IIecVarAccBrowseGetChildByIndex;
 	PFIECVARACCGETNODE IIecVarAccGetNode;
 	PFIECVARACCGETNODE3 IIecVarAccGetNode3;
 	PFIECVARACCGETNODE4 IIecVarAccGetNode4;
 	PFIECVARACCGETNODEFULLPATH IIecVarAccGetNodeFullPath;
 	PFIECVARACCGETNODEFULLPATH3 IIecVarAccGetNodeFullPath3;
 	PFIECVARACCGETNODEFULLPATH4 IIecVarAccGetNodeFullPath4;
 	PFIECVARACCGETNODENAME IIecVarAccGetNodeName;
 	PFIECVARACCGETNODENAME3 IIecVarAccGetNodeName3;
 	PFIECVARACCGETNODENAME4 IIecVarAccGetNodeName4;
 	PFIECVARACCGETACCESSRIGHTS IIecVarAccGetAccessRights;
 	PFIECVARACCGETADDRESS IIecVarAccGetAddress;
 	PFIECVARACCGETADDRESS2 IIecVarAccGetAddress2;
 	PFIECVARACCGETADDRESS3 IIecVarAccGetAddress3;
 	PFIECVARACCGETNODETYPE IIecVarAccGetNodeType;
 	PFIECVARACCGETSIZE IIecVarAccGetSize;
 	PFIECVARACCGETSIZE2 IIecVarAccGetSize2;
 	PFIECVARACCGETSIZE3 IIecVarAccGetSize3;
 	PFIECVARACCGETSWAPSIZE IIecVarAccGetSwapSize;
 	PFIECVARACCGETTYPECLASS IIecVarAccGetTypeClass;
 	PFIECVARACCGETTYPECLASS3 IIecVarAccGetTypeClass3;
 	PFIECVARACCGETVALUE IIecVarAccGetValue;
 	PFIECVARACCGETVALUE3 IIecVarAccGetValue3;
 	PFIECVARACCSETVALUE IIecVarAccSetValue;
 	PFIECVARACCSETVALUE3 IIecVarAccSetValue3;
 	PFIECVARACCSWAP IIecVarAccSwap;
 	PFIECVARACCSWAP2 IIecVarAccSwap2;
 	PFIECVARACCSWAP3 IIecVarAccSwap3;
 	PFIECVARACCGETTYPENODE IIecVarAccGetTypeNode;
 	PFIECVARACCGETTYPENODE2 IIecVarAccGetTypeNode2;
 	PFIECVARACCGETTYPENODE3 IIecVarAccGetTypeNode3;
 	PFIECVARACCGETTYPEDESC IIecVarAccGetTypeDesc;
 	PFIECVARACCGETADDRESSINFO IIecVarAccGetAddressInfo;
 	PFIECVARACCGETNUMOFTYPES IIecVarAccGetNumOfTypes;
 	PFIECVARACCGETTYPENODEBYINDEX IIecVarAccGetTypeNodeByIndex;
 	PFIECVARACCGETTYPENAME IIecVarAccGetTypeName;
 	PFIECVARACCGETTYPECLASSFROMTYPE IIecVarAccGetTypeClassFromType;
 	PFIECVARACCGETPOUCLASS IIecVarAccGetPOUClass;
 	PFIECVARACCGETNODEFLAGS IIecVarAccGetNodeFlags;
 	PFIECVARACCGETNUMOFATTRIBUTES IIecVarAccGetNumOfAttributes;
 	PFIECVARACCGETATTRIBUTEBYINDEX IIecVarAccGetAttributeByIndex;
 	PFIECVARACCGETENUMVALUES IIecVarAccGetEnumValues;
 	PFIECVARACCGETDERIVEDBASETYPE IIecVarAccGetDerivedBaseType;
 	PFIECVARACCISDERIVEDTYPE IIecVarAccIsDerivedType;
 	PFIECVARACCGETCLIENTOFFSET IIecVarAccGetClientOffset;
 	PFIECVARACCGETNAMESPACENODEFLAGS IIecVarAccGetNamespaceNodeFlags;
 	PFIECVARACCGETNATIVESIZE IIecVarAccGetNativeSize;
 	PFIECVARACCGETENUMMEMBERATTRIBUTELIST IIecVarAccGetEnumMemberAttributeList;
 	PFIECVARACCGETNUMOFTYPEATTRIBUTES IIecVarAccGetNumOfTypeAttributes;
 	PFIECVARACCGETTYPEATTRIBUTEBYINDEX IIecVarAccGetTypeAttributeByIndex;
 	PFIECVARACCGETRANGE IIecVarAccGetRange;
 	PFIECVARACCGETCONTENTFEATUREFLAGS IIecVarAccGetContentFeatureFlags;
 	PFIECVARACCEXECUTECALL IIecVarAccExecuteCall;
 } ICmpIecVarAccess_C;

#ifdef CPLUSPLUS
class ICmpIecVarAccess : public IBase
{
	public:
		virtual RTS_RESULT CDECL IIecVarAccInitVarInfo(VariableInformationStruct2 *pVarInfo, RTS_UI16 nSizeOfVarInfo) =0;
		virtual RTS_RESULT CDECL IIecVarAccExitVarInfo(VariableInformationStruct2 *pVarInfo) =0;
		virtual RTS_RESULT CDECL IIecVarAccCopyVarInfo(VariableInformationStruct2 *pVariableInformationDest, VariableInformationStruct2 *pVariableInformationSrc) =0;
		virtual RTS_HANDLE CDECL IIecVarAccGetFirstInterface(RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecVarAccGetNextInterface(RTS_HANDLE hPrevInterface, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IIecVarAccGetApplicationName(RTS_HANDLE hInterface, char *pszApplicationName, int nMaxLen) =0;
		virtual RTS_HANDLE CDECL IIecVarAccCreateVarList(RTS_UI32 ulChannelId, RTS_UI32 ulFlags, RTS_UI32 ulUpdateRateMs, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IIecVarAccDeleteVarList(RTS_HANDLE hVarList) =0;
		virtual RTS_RESULT CDECL IIecVarAccDeleteVarLists(RTS_UI32 ulChannelId) =0;
		virtual RTS_RESULT CDECL IIecVarAccDeleteAllLists(void) =0;
		virtual RTS_RESULT CDECL IIecVarAccVarListGetFlags(RTS_HANDLE hVarList, RTS_UI32 *pulFlags) =0;
		virtual RTS_HANDLE CDECL IIecVarAccAppendVar(RTS_HANDLE hVarList, char *pszVar, RTS_SIZE ulSize, RTS_UI32 hClientHandle, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IIecVarAccRemoveVar(RTS_HANDLE hVarList, RTS_HANDLE hVar) =0;
		virtual RTS_HANDLE CDECL IIecVarAccGetFirstVar(RTS_HANDLE hVarList, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecVarAccGetNextVar(RTS_HANDLE hVarList, RTS_HANDLE hPrevVar, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IIecVarAccInvalidateVar(RTS_HANDLE hVarList, RTS_HANDLE hVar) =0;
		virtual RTS_SIZE CDECL IIecVarAccReadVar(RTS_HANDLE hVar, void *pData, RTS_SIZE ulLen, RTS_UI32 *pulQuality, int varFlags, RTS_RESULT *pResult) =0;
		virtual RTS_SIZE CDECL IIecVarAccWriteVar(RTS_HANDLE hVar, void *pData, RTS_SIZE ulLen, int varFlags, RTS_RESULT *pResult) =0;
		virtual RTS_SIZE CDECL IIecVarAccWriteVar2(RTS_HANDLE hVar, void *pData, RTS_SIZE ulLen, int varFlags, RTS_UI32 ulSessionId, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IIecVarAccBeginVariableConfiguration(RTS_HANDLE hInterface, int bBlocking) =0;
		virtual RTS_RESULT CDECL IIecVarAccAppendVariable(RTS_HANDLE hInterface, RTS_HANDLE hNode) =0;
		virtual RTS_RESULT CDECL IIecVarAccAppendVariable3(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation) =0;
		virtual RTS_RESULT CDECL IIecVarAccRemoveVariable(RTS_HANDLE hInterface, RTS_HANDLE hNode) =0;
		virtual RTS_RESULT CDECL IIecVarAccRemoveVariable3(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation) =0;
		virtual RTS_RESULT CDECL IIecVarAccEndVariableConfiguration(RTS_HANDLE hInterface) =0;
		virtual RTS_RESULT CDECL IIecVarAccBrowseRecursive(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, PF_IECVARACC_BROWSECALLBACK pfBrowseCallback, RTS_BOOL bIecCallback, void *pUserParameter) =0;
		virtual RTS_HANDLE CDECL IIecVarAccBrowseGetRoot(RTS_HANDLE hInterface, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecVarAccBrowseDown(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecVarAccBrowseDown2(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecVarAccBrowseUp(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecVarAccBrowseUp2(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecVarAccBrowseGetNext(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecVarAccBrowseGetNext2(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecVarAccBrowseGetChildByIndex(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_UI32 ulIndex, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecVarAccGetNode(char *pszPath, RTS_SIZE *pulOffset, RTS_HANDLE *phInterface, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecVarAccGetNode3(char *pszPath, RTS_HANDLE *phInterface, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecVarAccGetNode4(char *pszPath, RTS_HANDLE *phInterface, VariableInformationStruct3 *pVariableInformation, RTS_RESULT *pResult) =0;
		virtual int CDECL IIecVarAccGetNodeFullPath(RTS_HANDLE hInterface, RTS_HANDLE hNode, char *pszPath, int iMaxPath, RTS_RESULT *pResult) =0;
		virtual int CDECL IIecVarAccGetNodeFullPath3(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, char *pszPath, int iMaxPath, RTS_RESULT *pResult) =0;
		virtual int CDECL IIecVarAccGetNodeFullPath4(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, char *pszPath, int iMaxPath, RTS_RESULT *pResult) =0;
		virtual char* CDECL IIecVarAccGetNodeName(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult) =0;
		virtual char* CDECL IIecVarAccGetNodeName3(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IIecVarAccGetNodeName4(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct3 *pVariableInformation, char *pszNodeName, RTS_UI32 nNodeNameLen) =0;
		virtual AccessRights CDECL IIecVarAccGetAccessRights(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult) =0;
		virtual void* CDECL IIecVarAccGetAddress(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult) =0;
		virtual void* CDECL IIecVarAccGetAddress2(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_SIZE ulOffset, RTS_RESULT *pResult) =0;
		virtual void* CDECL IIecVarAccGetAddress3(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult) =0;
		virtual TreeNodeType CDECL IIecVarAccGetNodeType(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult) =0;
		virtual RTS_SIZE CDECL IIecVarAccGetSize(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult) =0;
		virtual RTS_SIZE CDECL IIecVarAccGetSize2(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_SIZE ulOffset, RTS_RESULT *pResult) =0;
		virtual RTS_SIZE CDECL IIecVarAccGetSize3(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult) =0;
		virtual RTS_SIZE CDECL IIecVarAccGetSwapSize(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult) =0;
		virtual TypeClass3 CDECL IIecVarAccGetTypeClass(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult) =0;
		virtual TypeClass3 CDECL IIecVarAccGetTypeClass3(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult) =0;
		virtual RTS_SIZE CDECL IIecVarAccGetValue(RTS_HANDLE hInterface, RTS_HANDLE hNode, void *pDest, RTS_SIZE ulOffset, RTS_SIZE ulSize, RTS_RESULT *pResult) =0;
		virtual RTS_SIZE CDECL IIecVarAccGetValue3(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, void *pDest, RTS_SIZE ulSize, RTS_RESULT *pResult) =0;
		virtual RTS_SIZE CDECL IIecVarAccSetValue(RTS_HANDLE hInterface, RTS_HANDLE hNode, void *pSrc, RTS_SIZE ulOffset, RTS_SIZE ulSize, RTS_RESULT *pResult) =0;
		virtual RTS_SIZE CDECL IIecVarAccSetValue3(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, void *pSrc, RTS_SIZE ulSize, RTS_RESULT *pResult) =0;
		virtual RTS_SIZE CDECL IIecVarAccSwap(RTS_HANDLE hInterface, RTS_HANDLE hNode, void *pData, RTS_SIZE ulSize, int bMotorola, RTS_RESULT *pResult) =0;
		virtual RTS_SIZE CDECL IIecVarAccSwap2(RTS_HANDLE hInterface, RTS_HANDLE hNode, void *pData, RTS_SIZE ulSize, int bMotorola, RTS_SIZE ulOffset, RTS_RESULT *pResult) =0;
		virtual RTS_SIZE CDECL IIecVarAccSwap3(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, void *pData, RTS_SIZE ulSize, int bMotorola, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecVarAccGetTypeNode(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecVarAccGetTypeNode2(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_SIZE ulOffset, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecVarAccGetTypeNode3(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IIecVarAccGetTypeDesc(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, TypeDescAsUnion *pTypeDesc) =0;
		virtual RTS_RESULT CDECL IIecVarAccGetAddressInfo(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, char *pszAdressInfo, int *pnAddressInfoLen) =0;
		virtual RTS_I32 CDECL IIecVarAccGetNumOfTypes(RTS_HANDLE hInterface, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecVarAccGetTypeNodeByIndex(RTS_HANDLE hInterface, RTS_I32 nIndex, RTS_RESULT *pResult) =0;
		virtual char* CDECL IIecVarAccGetTypeName(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_RESULT *pResult) =0;
		virtual TypeClass3 CDECL IIecVarAccGetTypeClassFromType(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_IEC_DWORD dwFlags, RTS_RESULT *pResult) =0;
		virtual POUClass CDECL IIecVarAccGetPOUClass(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_RESULT *pResult) =0;
		virtual RTS_UI32 CDECL IIecVarAccGetNodeFlags(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult) =0;
		virtual RTS_UI16 CDECL IIecVarAccGetNumOfAttributes(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult) =0;
		virtual char* CDECL IIecVarAccGetAttributeByIndex(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_UI16 ui16Index, RTS_RESULT *pResult) =0;
		virtual EnumValues* CDECL IIecVarAccGetEnumValues(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_I16 *pi16NumOfEnums, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIecVarAccGetDerivedBaseType(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_RESULT *pResult) =0;
		virtual RTS_BOOL CDECL IIecVarAccIsDerivedType(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_RESULT *pResult) =0;
		virtual RTS_SIZE CDECL IIecVarAccGetClientOffset(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult) =0;
		virtual NAMESPACENODEFLAGS CDECL IIecVarAccGetNamespaceNodeFlags(RTS_HANDLE hInterface, RTS_HANDLE hNode, RTS_RESULT *pResult) =0;
		virtual RTS_SIZE CDECL IIecVarAccGetNativeSize(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_RESULT *pResult) =0;
		virtual EnumAttributes* CDECL IIecVarAccGetEnumMemberAttributeList(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_I16* pnNumOfEnumValues, RTS_RESULT* pResult) =0;
		virtual RTS_UI16 CDECL IIecVarAccGetNumOfTypeAttributes(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_RESULT* pResult) =0;
		virtual char* CDECL IIecVarAccGetTypeAttributeByIndex(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_UI16 wIndex, RTS_RESULT* pResult) =0;
		virtual RTS_BOOL CDECL IIecVarAccGetRange(RTS_HANDLE hInterface, RTS_HANDLE hTypeNode, RTS_UI64* pLower, RTS_UI64* pUpper, RTS_RESULT* pResult) =0;
		virtual RTS_RESULT CDECL IIecVarAccGetContentFeatureFlags(RTS_HANDLE hInterface, CONTENTFEATUREFLAGS* pContentFeatureFlags) =0;
		virtual RTS_RESULT CDECL IIecVarAccExecuteCall(RTS_HANDLE hInterface, RTS_HANDLE hNode, VariableInformationStruct2 *pVariableInformation, RTS_UI8 *pArgumentBuffer, RTS_SIZE nArgumentBufferSize) =0;
};
	#ifndef ITF_CmpIecVarAccess
		#define ITF_CmpIecVarAccess static ICmpIecVarAccess *pICmpIecVarAccess = NULL;
	#endif
	#define EXTITF_CmpIecVarAccess
#else	/*CPLUSPLUS*/
	typedef ICmpIecVarAccess_C		ICmpIecVarAccess;
	#ifndef ITF_CmpIecVarAccess
		#define ITF_CmpIecVarAccess
	#endif
	#define EXTITF_CmpIecVarAccess
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPIECVARACCESSITF_H_*/
