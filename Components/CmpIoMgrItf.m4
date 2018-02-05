/**
 * <interfacename>CmpIoMgr</interfacename>
 * <description> 
 * <p>Interface of the IO-manager, which manages all IO-driver instances in the runtime system.</p>
 * <p>There are several data structures involved in the I/O update. All of them are registered
 * in or passed to the I/O Manager. The following is an overview over the most essential
 * structures and how they are passed to the I/O Manager:</p>
 * <pre>
 * .    +------------------+ UpdateConfiguration()
 * .  +------------------+ |
 * . +-----------------+ |-+
 * . | IoConfigTaskMap |-+
 * . +-------+---------+ ReadInputs() / WriteOutputs()
 * .         | 1                                  UpdateConfiguration()
 * .         |                       +--------------------+
 * .         | n                   +--------------------+ |
 * . +-------+--------------+     +-------------------+ |-+
 * . | IoConfigConnectorMap |     | IoConfigConnector |-+
 * . +-------+--------------+     +--------+----------+ StartBusCycle()
 * .         | 1                           | 1
 * .         |                             |
 * .         | n                           | n
 * . +-------+------------+ n   1 +--------+----------+
 * . | IoConfigChannelMap +-------+ IoConfigParameter |
 * . +--------------------+       +-------------------+
 * </pre>
 * <p>Most calls to the I/O Manager are just passed directly through to the drivers.
 * Depending on the kind of driver, this may passed through CmpIoDrvIEC or directly
 * to it.</p>
 * <p>The following drawing illustrates how a call to e.g. ReadInputs() is passed
 * to the drivers if there is a C and an IEC driver registered and used in one task:</p>
 * <pre>
 * . +--------+    +--------+    +--------+   +-----------+   +--------+
 * . |IEC Task|    |CmpIoMgr|    |IoDrvInC|   |CmpIoDrvIEC|   |IoDrvLib|
 * . +--------+    +---+----+    +---+----+   +----+------+   +---+----+
 * .     |             |             |             |              |
 * .    +++            |             |             |              |
 * .    | |-----------+++            |             |              |
 * .    | |           | |-----------+++            |              |
 * .    | |           | |           | |            |              |
 * .    | |           | |           | |            |              |
 * .    | |           | |           | |            |              |
 * .    | |           | |...........+++            |              |
 * .    | |           | |            |             |              |
 * .    | |           | |------------+------------+++             |
 * .    | |           | |            |            | |             |
 * .    | |           | |            |            | |             |
 * .    | |           | |            |            | |------------+++
 * .    | |           | |            |            | |            | |
 * .    | |           | |            |            | |            | |
 * .    | |           | |            |            | |............+++
 * .    | |           | |.........................+++             |
 * .    | |...........+++            |             |              |
 * .    | |            |             |             |              |
 * .    | |            |             |             |              |
 * .    +++            |             |             |              |
 * .     |             |             |             |              |
 * .     |             |             |             |              |
 * </pre>
 * <p>The devices, which are configured in the CoDeSys programming system
 * are downloaded in form of connector lists. All connectors, specified
 * for the devices are downloaded in form of a list.</p>
 * <p>Beside neighbours, this list has although a parent role, that means,
 * that every list member can point to it's parent.</p>
 * <p>For example:</p>
 * <pre>
 * .                      _____
 * .             _,.--''''     `'''`--..__
 * .          ,,'          ___            `--.._
 * .       _,i__       ,-ii_  `''`--.._         `-..
 * .     ,;''   `'-._,;''   `'-._      ``-.._       `-._
 * .  +----+      +----+      +----+      +----+      +-'--+
 * .  | A  |------+ B  |------| C  |------| D  |------+ E  |-----
 * .  +----+      +----+      +----+      +----+      +----+
 * </pre>
 * <p>This list represents the following tree:</p>
 * <pre>
 * .                 ,-.
 * .                ( A )
 * .                /`-'\
 * .              .'     |
 * .          ,-./       \,-.
 * .         ( B )       ( E )
 * .         /`-'\        `-'
 * .       .'     |
 * .   ,-./       \,-.
 * .  ( C )       ( D )
 * .   `-'         `-'
 * </pre>
 * <p>The API functions within this component await always a pointer
 * to one of these connectors, when the input is a "Connecto List".
 * The count doesn't essentially need to specify the absolut size
 * of the list, but the size, starting at the connector that we
 * passed to the function.</p>
 * <p>For example, if we want to iterate over the connector list above (in pseudo code):</p>
 * <pre>
 * GetFirst(A, 5) => A (count: 5)
 * GetNext(A,5) => B (count: 4)
 * GetNextChild(B, 4, B) => C (Count: 3)
 * GetNextChild(B, 4, C) => D (count: 2)
 * GetNextChild(B, 4, D) => NULL
 * GetNext(D, 2) => E (count: 1)
 * GetNext(E, 1) => NULL
 * </pre>
 * <p>Note: Because the parameter pnCount is an INOUT, you need to save
 * the size of the list in a different variable when you use for example
 * GetNextChild(). Because this value will be overwritten with the number
 * of remaining entries in the list, starting at the connector that was 
 * returned.</p>
 * <p>There are two different kinds of driver handles, that the I/O Manager
 * needs to differenciate:</p>
 * <ul>
 *   <li>C Drivers</li>
 *   <li>IEC Drivers</li>
 * </ul>
 * <p>The I/O Manager provides a common function interface for C Components
 * and for IEC Applications. But while the Connectors and Paramter structures
 * are completely the same for both sides, the driver handles are significantly
 * different. Internally the I/O manager works with C driver handles. The
 * abstraction to provide an IEC interface, which is based on Function Blocks,
 * is done by the two components CmpIoDrvC and CmpIoDrvIec.</p>
 * <p>The component CmpIoDrvC manages all C drivers and CmpIoDrvIec manages all
 * IEC drivers.</p>
 * </description>
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpIoMgr')

/**
 * <category>Compiler switch</category>
 * <description>
 *	Compiler switches to enable/disable single features in the component.
 * </description>
 * <element name="CMPIECTASK_DONT_REGISTER_WATCHDOG_AT_SUPERVISOR">Switch to disable registering all hardware supported fieldbus watchdogs (e.g. Hilscher CIFX masters) at the CmpSupervisor!
 *	If this defined is set, the hardware supported fieldbus watchdogs are always enabled and cannot selectively be disabled via the CmpSupervisor!
 * </element>
 */


/**
 * <category>Static defines</category>
 * <description>Number of static IO-driver instances to store</description>
 */
#ifndef NUM_OF_STATIC_DEVICES
	#define NUM_OF_STATIC_DEVICES				5
#endif

/**
 * <category>Static defines</category>
 * <description>Number of static parameter to store during writing operation. See setting </description>
 */
#ifndef NUM_OF_STATIC_PARAMETER_STORAGE
	#define	NUM_OF_STATIC_PARAMETER_STORAGE		10
#endif

/**
 * <category>Static defines</category>
 * <description>Number of static mapping entries to hold all mapping informations</description>
 */
#ifndef IOMGR_NUM_OF_STATIC_MAPPING_ENTRIES
	#define	IOMGR_NUM_OF_STATIC_MAPPING_ENTRIES		5
#endif

/**
 * <category>Static defines</category>
 * <description>Number of static scan entries to hold IO driver scan informarion to transmit all of the scanned connectors</description>
 */
#ifndef IOMGR_NUM_OF_STATIC_SCAN_ENTRIES
	#define	IOMGR_NUM_OF_STATIC_SCAN_ENTRIES		1
#endif


/**
 * <category>File name definitions</category>
 * <description>Name of the parameter storage to save the changed IO-config parameters</description>
 */
#ifndef IOMGR_PARAMETER_STORAGE_FILE
	#define IOMGR_PARAMETER_STORAGE_FILE		"IoConfig.par"
#endif


/**
 * <category>Watchdog definitions</category>
 * <description>This is the initial watchdogtask task delay. On the first download of a watchdog time, this time is recalculated</description>
 */
#ifndef IOMGR_WATCHTDOGTASK_TASK_DELAY
	#define IOMGR_WATCHTDOGTASK_TASK_DELAY		100
#endif

/**
 * <category>Bus Cycle Type</category>
 * <description>
 * <p>
 *	Type of the bus cycle to differenciate between:
 * </p>
 * <ul>
 *     <li>BCT_START: Bus Cycle is executed at the beginning of the task cycle</li>
 *     <li>BCT_END:   Bus Cycle is executed at the end of the task cycle</li>
 * </ul>
 * </description>
 */
#define BCT_START 0x00000001
#define BCT_END   0x00000002

/**
 * <category>Online services</category>
 * <description>
 * </description>
 */
#define SRV_IOMGRSCANMODULES		0x01
#define SRV_IOMGRIDENTIFY			0x02
#define SRV_IOMGRNOMINATE			0x03
#define SRV_IOMGRUPLOADDESCRIPTION	0x04

/**
 * <category>Online tags</category>
 * <description>
 * </description>
 */
#define TAG_DEVICESCAN_LIST			0x81
#define TAG_DEVICESCAN_CONNECTOR	0x02
#define TAG_DEVICESCAN_PARAMETER	0x03
#define TAG_DEVICESCAN_ROOTDEVICE	0x04

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to enable/disable the sorting of the IoConfigTaskMap list in the runtime system
 *	1: Disable the sorting of the IoConfigTaskMap list in the runtime system
 *	0: Enable the sorting of the IoConfigTaskMap list in the runtime system (default).
 * </description>
 */
#define IOMGRKEY_INT_DISABLE_TASK_MAP_LIST_SORTING				"DisableTaskMapListSorting"
#define IOMGRKEY_INT_DISABLE_TASK_MAP_LIST_SORTING_DEFAULT		0


/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to store all changed parameters and to restore after reboot.
 * </description>
 */
#define IOMGRKEY_INT_STORE_CHANGED_PARAMETERS					"StoreChangedParameters"
#ifndef IOMGRKEY_INT_STORE_CHANGED_PARAMETERS_DEFAULT
	#define IOMGRKEY_INT_STORE_CHANGED_PARAMETERS_DEFAULT		0
#endif

/**
* <category>Settings</category>
* <type>Int</type>
* <description>
*     Setting to enable full IO-update consistency resp. disable DRVPROP_CONSISTENCY for all IO-drivers! This setting must be used, if consistency cannot be
*     realized on this target by the IO-driver itself.
*  NOTE:
*     This settings must be enabled on targets with no strict priority scheduling for the IO-update tasks (for example for MultiCore systems).
* </description>
*/
#define IOMGRKEY_INT_ENABLE_FULL_CONSISTENCY					"EnableFullConsistency"
#ifndef IOMGRVALUE_INT_ENABLE_FULL_CONSISTENCY
       #define IOMGRVALUE_INT_ENABLE_FULL_CONSISTENCY			0
#endif

/**
 * <category>Task map types</category>
 * <description>
 * <p>Types of IO-channels in a task map</p>
 * </description>
 * <element name="TMT_INPUTS">Input connector maps</element>
 * <element name="TMT_OUTPUTS">Output connector maps</element>
 */
#define TMT_INPUTS				0x0001
#define TMT_OUTPUTS				0x0002

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 *		Parameter description. This entry describes completely a parameter of an connector.
 *	</description>
 * <param name="dwParameterId" type="IN">ID of the parameter. This ID is specified in the device description.</param>
 * <param name="dwValue" type="IN">Value (if is valud &lt; 4 bytes) or a pointer to the value of the parameter</param>
 * <param name="wType" type="IN">Type class of the parameter. See category "Type class" an here the enum TypeClass3 in SysInternalLibItf.h for detailed information.</param>
 * <param name="wLen" type="IN">Length of the parameter in bits</param>
 * <param name="dwFlags" type="IN">Parameter value flags.  See category "Parameter value flags" in CmpIoDrvItf.h for detailed information.</param>
 * <param name="dwDriverSpecific" type="IN">Driver specific entry. Reserved for the usage in the driver.</param>
 */
typedef struct tagIoConfigParameter
{
	RTS_IEC_DWORD dwParameterId;
	RTS_IEC_BYTE *dwValue;
	RTS_IEC_WORD wType;
	RTS_IEC_WORD wLen;
	RTS_IEC_DWORD dwFlags;
	RTS_IEC_BYTE *dwDriverSpecific;
} IoConfigParameter;

/**
 * <description>
 *		Connector information. Each device is described completely as a set of one input- and one or more
 *		output-conenctors. 
 *	</description>
 * <param name="wType" type="IN">Type of the connector. See category "Connector types" for detailed information.</param>
 * <param name="wOptions" type="IN">Connector options. See category "Connector options" for detailed information.</param>
 * <param name="dwFlags" type="IN">Connector flags. See category "Connector flags" for detailed information.</param>
 * <param name="hIoDrv" type="IN">Registered instance handle of the IO-driver, that operates this device respectively this connector</param>
 * <param name="dwNumOfParameters" type="IN">Number of parameters in the parameter list</param>
 * <param name="pParameterList" type="IN">Pointer to the parameter list, that contains all parameters of this connector</param>
 * <param name="pFather" type="IN">Pointer to the father connector to describe the device tree</param>
 * <SIL2/>
 */
typedef struct tagIoConfigConnector
{
	RTS_IEC_WORD wType;		
	RTS_IEC_WORD wOptions;		
	RTS_IEC_DWORD dwFlags;		
	RTS_IEC_HANDLE hIoDrv;		
	RTS_IEC_DWORD dwNumOfParameters;		
	IoConfigParameter *pParameterList;		
	struct tagIoConfigConnector *pFather;		
} IoConfigConnector;

/**
 * <description>
 *		Mapping information for a single channel. Every I/O-channel is described as a parameter, but with special meanings.
 *		The datatype of a channel can be simple (BOOL, BYTE, WORD, etc.) or array of simple types.
 *	</description>
 * <param name="pParameter" type="IN">Pointer to the parameter description</param>
 * <param name="pbyIecAddress" type="IN">Pointer to the parameter in the process image on the IEC side</param>
 * <param name="wParameterBitOffset" type="IN">Bitoffset of the device</param>
 * <param name="wIecAddressBitOffset" type="IN">Bitoffset of pbyIecAddress in the IEC process image</param>
 * <param name="wSize" type="IN">Size in bits of the channel</param>
 * <param name="wBaseTypeInformation" type="IN">If this field is unequal zero, it is used for the base type information. With this information, a correct swapping operation can be executed.</param>
 * <param name="dwDriverSpecific" type="IN">Driver specific entry. Reserved for the usage in the driver.</param>
 * <SIL2/>
 */
typedef struct tagIoConfigChannelMap
{
	IoConfigParameter *pParameter;
	RTS_IEC_BYTE *pbyIecAddress;
	RTS_IEC_WORD wParameterBitOffset;
	RTS_IEC_WORD wIecAddressBitOffset;
	RTS_IEC_WORD wSize;
	RTS_IEC_WORD wBaseTypeInformation;
	RTS_IEC_BYTE *dwDriverSpecific;
} IoConfigChannelMap;

/**
 * <description>
 *		Connector map to describe all IO-channels of one connector
 *	</description>
 * <param name="pConnector" type="IN">Pointer to the corresponding connector</param>
 * <param name="dwIoMgrSpecific" type="IN">IO-manager specific entry</param>
 * <param name="dwNumOfChannels" type="IN">Number of channels in the channel map list</param>
 * <param name="pChannelMapList" type="IN">Pointer to channel map list</param>
 * <SIL2/>
 */
typedef struct tagIoConfigConnectorMap
{
	IoConfigConnector *pConnector;
	RTS_IEC_BYTE *dwIoMgrSpecific;
	RTS_IEC_DWORD dwNumOfChannels;
	IoConfigChannelMap *pChannelMapList;
} IoConfigConnectorMap;

/**
 * <description>
 *		Mapping description for each task.
 *	</description>
 * <param name="dwTaskId" type="IN">Index of the IEC task</param>
 * <param name="wType" type="IN">Input or output type. See category "Task map types" for detailed information.</param>
 * <param name="wNumOfConnectorMap" type="IN">Number of connector maps int the connector map list</param>
 * <param name="pConnectorMapList" type="IN">Pointer to the connector map list</param>
 * <SIL2/>
 */
typedef struct tagIoConfigTaskMap
{
	RTS_IEC_DWORD dwTaskId;		
	RTS_IEC_WORD wType;		
	RTS_IEC_WORD wNumOfConnectorMap;		
	IoConfigConnectorMap *pConnectorMapList;		
} IoConfigTaskMap;

/**
 * <description>iomgrconfiggetconnector</description>
 */
typedef struct tagiomgrconfiggetconnector_struct
{
	IoConfigConnector *pConnectorList;	/* VAR_INPUT */	
	RTS_IEC_DINT *pnCount;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwModuleType;			/* VAR_INPUT */	
	RTS_IEC_DWORD dwInstance;			/* VAR_INPUT */	
	IoConfigConnector *IoMgrConfigGetConnector;	/* VAR_OUTPUT */	
} iomgrconfiggetconnector_struct;

DEF_API(`void',`CDECL',`iomgrconfiggetconnector',`(iomgrconfiggetconnector_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB093BAED),0x03050800)

/**
 * <description>iomgrconfiggetconnectorbydriver</description>
 */
typedef struct tagiomgrconfiggetconnectorbydriver_struct
{
	IBase *pIBase;						/* VAR_INPUT */	
	RTS_IEC_DINT bIecDriver;			/* VAR_INPUT */	
	RTS_IEC_DINT nIndex;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	IoConfigConnector *IoMgrConfigGetConnectorByDriver;	/* VAR_OUTPUT */	
} iomgrconfiggetconnectorbydriver_struct;

DEF_API(`void',`CDECL',`iomgrconfiggetconnectorbydriver',`(iomgrconfiggetconnectorbydriver_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x076B9D1E),0x03050800)

/**
 * <description>iomgrconfiggetconnectorlist</description>
 */
typedef struct tagiomgrconfiggetconnectorlist_struct
{
	IoConfigConnector **ppConnectorList;	/* VAR_INPUT */	
	RTS_IEC_DINT *pnCount;				/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrConfigGetConnectorList;	/* VAR_OUTPUT */	
} iomgrconfiggetconnectorlist_struct;

DEF_API(`void',`CDECL',`iomgrconfiggetconnectorlist',`(iomgrconfiggetconnectorlist_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x6E3F45DC),0x03050800)

/**
 * <description>iomgrconfiggetdriver</description>
 */
typedef struct tagiomgrconfiggetdriver_struct
{
	IoConfigConnector *pConnector;		/* VAR_INPUT */	
	RTS_IEC_DINT *pbIecDriver;			/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	IBase *IoMgrConfigGetDriver;		/* VAR_OUTPUT */	
} iomgrconfiggetdriver_struct;

DEF_API(`void',`CDECL',`iomgrconfiggetdriver',`(iomgrconfiggetdriver_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA6C591A7),0x03050800)

/**
 * <description>iomgrconfiggetfirstchild</description>
 */
typedef struct tagiomgrconfiggetfirstchild_struct
{
	IoConfigConnector *pConnectorList;	/* VAR_INPUT */	
	RTS_IEC_DINT *pnCount;				/* VAR_INPUT */	
	IoConfigConnector *pFather;			/* VAR_INPUT */	
	IoConfigConnector *IoMgrConfigGetFirstChild;	/* VAR_OUTPUT */	
} iomgrconfiggetfirstchild_struct;

DEF_API(`void',`CDECL',`iomgrconfiggetfirstchild',`(iomgrconfiggetfirstchild_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB89B6273),0x03050800)

/**
 * <description>iomgrconfiggetfirstconnector</description>
 */
typedef struct tagiomgrconfiggetfirstconnector_struct
{
	IoConfigConnector *pConnectorList;	/* VAR_INPUT */	
	RTS_IEC_DINT *pnCount;				/* VAR_INPUT */	
	RTS_IEC_WORD wType;					/* VAR_INPUT */	
	IoConfigConnector *IoMgrConfigGetFirstConnector;	/* VAR_OUTPUT */	
} iomgrconfiggetfirstconnector_struct;

DEF_API(`void',`CDECL',`iomgrconfiggetfirstconnector',`(iomgrconfiggetfirstconnector_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1AEDD2CA),0x03050800)

/**
 * <description>iomgrconfiggetnextchild</description>
 */
typedef struct tagiomgrconfiggetnextchild_struct
{
	IoConfigConnector *pConnectorList;	/* VAR_INPUT */	
	RTS_IEC_DINT *pnCount;				/* VAR_INPUT */	
	IoConfigConnector *pFather;			/* VAR_INPUT */	
	IoConfigConnector *IoMgrConfigGetNextChild;	/* VAR_OUTPUT */	
} iomgrconfiggetnextchild_struct;

DEF_API(`void',`CDECL',`iomgrconfiggetnextchild',`(iomgrconfiggetnextchild_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x2F87EBF8),0x03050800)

/**
 * <description>iomgrconfiggetnextconnector</description>
 */
typedef struct tagiomgrconfiggetnextconnector_struct
{
	IoConfigConnector *pConnectorList;	/* VAR_INPUT */	
	RTS_IEC_DINT *pnCount;				/* VAR_INPUT */	
	RTS_IEC_WORD wType;					/* VAR_INPUT */	
	IoConfigConnector *IoMgrConfigGetNextConnector;	/* VAR_OUTPUT */	
} iomgrconfiggetnextconnector_struct;

DEF_API(`void',`CDECL',`iomgrconfiggetnextconnector',`(iomgrconfiggetnextconnector_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA5BCF071),0x03050800)

/**
 * <description>iomgrconfiggetparameter</description>
 */
typedef struct tagiomgrconfiggetparameter_struct
{
	IoConfigConnector *pConnector;		/* VAR_INPUT */	
	RTS_IEC_DWORD dwParameterId;		/* VAR_INPUT */	
	IoConfigParameter *IoMgrConfigGetParameter;	/* VAR_OUTPUT */	
} iomgrconfiggetparameter_struct;

DEF_API(`void',`CDECL',`iomgrconfiggetparameter',`(iomgrconfiggetparameter_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC7A23B05),0x03050800)

/**
 * <description>iomgrconfiggetparametervaluebyte</description>
 */
typedef struct tagiomgrconfiggetparametervaluebyte_struct
{
	IoConfigParameter *pParameter;		/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_BYTE IoMgrConfigGetParameterValueByte;	/* VAR_OUTPUT */	
} iomgrconfiggetparametervaluebyte_struct;

DEF_API(`void',`CDECL',`iomgrconfiggetparametervaluebyte',`(iomgrconfiggetparametervaluebyte_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xDE4EF488),0x03050800)

/**
 * <description>iomgrconfiggetparametervaluedword</description>
 */
typedef struct tagiomgrconfiggetparametervaluedword_struct
{
	IoConfigParameter *pParameter;		/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_DWORD IoMgrConfigGetParameterValueDword;	/* VAR_OUTPUT */	
} iomgrconfiggetparametervaluedword_struct;

DEF_API(`void',`CDECL',`iomgrconfiggetparametervaluedword',`(iomgrconfiggetparametervaluedword_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x6F885F72),0x03050800)

/**
 * <description>iomgrconfiggetparametervaluepointer</description>
 */
typedef struct tagiomgrconfiggetparametervaluepointer_struct
{
	IoConfigParameter *pParameter;		/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_BYTE *IoMgrConfigGetParameterValuePointer;	/* VAR_OUTPUT */	
} iomgrconfiggetparametervaluepointer_struct;

DEF_API(`void',`CDECL',`iomgrconfiggetparametervaluepointer',`(iomgrconfiggetparametervaluepointer_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x633BC6E3),0x03050800)

/**
 * <description>iomgrconfiggetparametervalueword</description>
 */
typedef struct tagiomgrconfiggetparametervalueword_struct
{
	IoConfigParameter *pParameter;		/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_WORD IoMgrConfigGetParameterValueWord;	/* VAR_OUTPUT */	
} iomgrconfiggetparametervalueword_struct;

DEF_API(`void',`CDECL',`iomgrconfiggetparametervalueword',`(iomgrconfiggetparametervalueword_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x522D5073),0x03050800)

/**
 * <description>iomgrconfigresetdiagnosis</description>
 */
typedef struct tagiomgrconfigresetdiagnosis_struct
{
	IoConfigConnector *pConnector;		/* VAR_INPUT */	
	RTS_IEC_DWORD dwFlags;				/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrConfigResetDiagnosis;	/* VAR_OUTPUT */	
} iomgrconfigresetdiagnosis_struct;

DEF_API(`void',`CDECL',`iomgrconfigresetdiagnosis',`(iomgrconfigresetdiagnosis_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x6B60C0F6),0x03050800)

/**
 * <description>iomgrconfigsetdiagnosis</description>
 */
typedef struct tagiomgrconfigsetdiagnosis_struct
{
	IoConfigConnector *pConnector;		/* VAR_INPUT */	
	RTS_IEC_DWORD dwFlags;				/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrConfigSetDiagnosis;	/* VAR_OUTPUT */	
} iomgrconfigsetdiagnosis_struct;

DEF_API(`void',`CDECL',`iomgrconfigsetdiagnosis',`(iomgrconfigsetdiagnosis_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xE0CCC2C9),0x03050800)

/**
 * <description>iomgrcopyinputbe</description>
 */
typedef struct tagiomgrcopyinputbe_struct
{
	IoConfigChannelMap *pChannel;		/* VAR_INPUT */	
	RTS_IEC_BYTE *pAddress;				/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrCopyInputBE;	/* VAR_OUTPUT */	
} iomgrcopyinputbe_struct;

DEF_API(`void',`CDECL',`iomgrcopyinputbe',`(iomgrcopyinputbe_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x072C6C71),0x03050800)

/**
 * <description>iomgrcopyinputle</description>
 */
typedef struct tagiomgrcopyinputle_struct
{
	IoConfigChannelMap *pChannel;		/* VAR_INPUT */	
	RTS_IEC_BYTE *pAddress;				/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrCopyInputLE;	/* VAR_OUTPUT */	
} iomgrcopyinputle_struct;

DEF_API(`void',`CDECL',`iomgrcopyinputle',`(iomgrcopyinputle_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD4FB4CB6),0x03050800)

/**
 * <description>iomgrcopyoutputbe</description>
 */
typedef struct tagiomgrcopyoutputbe_struct
{
	IoConfigChannelMap *pChannel;		/* VAR_INPUT */	
	RTS_IEC_BYTE *pAddress;				/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrCopyOutputBE;	/* VAR_OUTPUT */	
} iomgrcopyoutputbe_struct;

DEF_API(`void',`CDECL',`iomgrcopyoutputbe',`(iomgrcopyoutputbe_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCDB7B2BE),0x03050800)

/**
 * <description>iomgrcopyoutputle</description>
 */
typedef struct tagiomgrcopyoutputle_struct
{
	IoConfigChannelMap *pChannel;		/* VAR_INPUT */	
	RTS_IEC_BYTE *pAddress;				/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrCopyOutputLE;	/* VAR_OUTPUT */	
} iomgrcopyoutputle_struct;

DEF_API(`void',`CDECL',`iomgrcopyoutputle',`(iomgrcopyoutputle_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x5FC818BC),0x03050800)

/**
 * <description>iomgrgetbuscycletype</description>
 */
typedef struct tagiomgrgetbuscycletype_struct
{
	IoConfigConnector *pConnector;		/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrGetBusCycleType;	/* VAR_OUTPUT */	
} iomgrgetbuscycletype_struct;

DEF_API(`void',`CDECL',`iomgrgetbuscycletype',`(iomgrgetbuscycletype_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x8334DD20),0x03050800)

/**
 * <description>iomgrgetconfigapplication</description>
 */
typedef struct tagiomgrgetconfigapplication_struct
{
	RTS_IEC_STRING *pszConfigApplication;	/* VAR_INPUT */	
	RTS_IEC_DINT *pnMaxLen;				/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrGetConfigApplication;	/* VAR_OUTPUT */	
} iomgrgetconfigapplication_struct;

DEF_API(`void',`CDECL',`iomgrgetconfigapplication',`(iomgrgetconfigapplication_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF82C99F4),0x03050800)

/**
 * <description>iomgrgetdriverproperties</description>
 */
typedef struct tagiomgrgetdriverproperties_struct
{
	RTS_IEC_HANDLE hIoDrv;				/* VAR_INPUT */	
	RTS_IEC_DWORD **ppProperties;		/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrGetDriverProperties;	/* VAR_OUTPUT */	
} iomgrgetdriverproperties_struct;

DEF_API(`void',`CDECL',`iomgrgetdriverproperties',`(iomgrgetdriverproperties_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xEC0D662D),0x03050800)

/**
 * <description>iomgrgetfirstdriverinstance</description>
 */
typedef struct tagiomgrgetfirstdriverinstance_struct
{
	RTS_IEC_DINT *pbIecDriver;			/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	IBase *IoMgrGetFirstDriverInstance;	/* VAR_OUTPUT */	
} iomgrgetfirstdriverinstance_struct;

DEF_API(`void',`CDECL',`iomgrgetfirstdriverinstance',`(iomgrgetfirstdriverinstance_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x7823BC76),0x03050800)

/**
 * <description>iomgrgetmodulediagnosis</description>
 */
typedef struct tagiomgrgetmodulediagnosis_struct
{
	IoConfigConnector *pConnector;		/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrGetModuleDiagnosis;	/* VAR_OUTPUT */	
} iomgrgetmodulediagnosis_struct;

DEF_API(`void',`CDECL',`iomgrgetmodulediagnosis',`(iomgrgetmodulediagnosis_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x5DA78ABA),0x03050800)

/**
 * <description>iomgrgetnextdriverinstance</description>
 */
typedef struct tagiomgrgetnextdriverinstance_struct
{
	IBase *pIBasePrev;					/* VAR_INPUT */	
	RTS_IEC_DINT *pbIecDriver;			/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	IBase *IoMgrGetNextDriverInstance;	/* VAR_OUTPUT */	
} iomgrgetnextdriverinstance_struct;

DEF_API(`void',`CDECL',`iomgrgetnextdriverinstance',`(iomgrgetnextdriverinstance_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0B47742F),0x03050800)

/**
 * <description>iomgridentify</description>
 */
typedef struct tagiomgridentify_struct
{
	IoConfigConnector *pConnector;		/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrIdentify;		/* VAR_OUTPUT */	
} iomgridentify_struct;

DEF_API(`void',`CDECL',`iomgridentify',`(iomgridentify_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC48724F5),0x03050800)

/**
 * <description>iomgrreadinputs</description>
 */
typedef struct tagiomgrreadinputs_struct
{
	IoConfigTaskMap *pTaskMap;			/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrReadInputs;		/* VAR_OUTPUT */	
} iomgrreadinputs_struct;

DEF_API(`void',`CDECL',`iomgrreadinputs',`(iomgrreadinputs_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x3BCE0A42),0x03050800)

/**
 * <description>iomgrreadparameter</description>
 */
typedef struct tagiomgrreadparameter_struct
{
	RTS_IEC_DWORD dwModuleType;			/* VAR_INPUT */	
	RTS_IEC_DWORD dwInstance;			/* VAR_INPUT */	
	RTS_IEC_DWORD dwParameterId;		/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwBitSize;			/* VAR_INPUT */	
	RTS_IEC_DWORD dwBitOffset;			/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrReadParameter;	/* VAR_OUTPUT */	
} iomgrreadparameter_struct;

DEF_API(`void',`CDECL',`iomgrreadparameter',`(iomgrreadparameter_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD37BF5DF),0x03050800)

/**
 * | Reconfigure a single connector respectively the corresponding master.
 * | In the reconfigure sequence we call the corresponding IO-driver at the connector the following way:
 * |    1. disable the IO-configuration
 * |    2. enable the IO-configuration
 * |    3. update the mapping
 * | This sequence is called asynchronously so the asynchronous state is transported in the parameter pudiState.
 * :return: The runtime system error code (see CmpErrors.library)
 */
typedef struct tagiomgrreconfigure_struct
{
	IoConfigConnector *pConnector;		/* VAR_INPUT */	/* Pointer to the corresponding connector to reconfigure */
	RTS_IEC_UDINT *pudiState;			/* VAR_INPUT */	/* Asynchronous state of the reconfigure operation. Can be one of the the following states (see CmpAsyncMgr.library for details:
 (ASYNCSTATE_INVALID | ASYNCSTATE_PENDING | ASYNCSTATE_ACTIVE | ASYNCSTATE_READY | ASYNCSTATE_ERROR | ASYNCSTATE_TIMEOUT) */
	RTS_IEC_RESULT IoMgrReconfigure;	/* VAR_OUTPUT */	
} iomgrreconfigure_struct;

DEF_API(`void',`CDECL',`iomgrreconfigure',`(iomgrreconfigure_struct *p)',1,RTSITF_GET_SIGNATURE(0x7DDF91C4, 0x731E5390),0x03050800)

/**
 * <description>iomgrregisterconfigapplication</description>
 */
typedef struct tagiomgrregisterconfigapplication_struct
{
	RTS_IEC_STRING *pszConfigApplication;	/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrRegisterConfigApplication;	/* VAR_OUTPUT */	
} iomgrregisterconfigapplication_struct;

DEF_API(`void',`CDECL',`iomgrregisterconfigapplication',`(iomgrregisterconfigapplication_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xBEF7EAA8),0x03050800)

/**
 * <description>iomgrregisterinstance2</description>
 */
typedef struct tagiomgrregisterinstance2_struct
{
	RTS_IEC_DWORD dwClassId;			/* VAR_INPUT */	
	IBase *pItf;						/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE IoMgrRegisterInstance2;	/* VAR_OUTPUT */	
} iomgrregisterinstance2_struct;

DEF_API(`void',`CDECL',`iomgrregisterinstance2',`(iomgrregisterinstance2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4219F9A3),0x03050800)

/**
 * <description>iomgrscanmodules</description>
 */
typedef struct tagiomgrscanmodules_struct
{
	IoConfigConnector *pConnector;		/* VAR_INPUT */	
	IoConfigConnector **ppConnectorList;	/* VAR_INPUT */	
	RTS_IEC_DINT *pnCount;				/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrScanModules;		/* VAR_OUTPUT */	
} iomgrscanmodules_struct;

DEF_API(`void',`CDECL',`iomgrscanmodules',`(iomgrscanmodules_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF31DBCAE),0x03050800)

/**
 * <description>iomgrsetdriverproperties</description>
 */
typedef struct tagiomgrsetdriverproperties_struct
{
	RTS_IEC_HANDLE hIoDrv;				/* VAR_INPUT */	
	RTS_IEC_DWORD ulProperties;			/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrSetDriverProperties;	/* VAR_OUTPUT */	
} iomgrsetdriverproperties_struct;

DEF_API(`void',`CDECL',`iomgrsetdriverproperties',`(iomgrsetdriverproperties_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x607A5D95),0x03050800)

/**
 * <description>iomgrsetdriverproperty</description>
 */
typedef struct tagiomgrsetdriverproperty_struct
{
	RTS_IEC_HANDLE hIoDrv;				/* VAR_INPUT */	
	RTS_IEC_DWORD ulProperty;			/* VAR_INPUT */	
	RTS_IEC_DINT bValue;				/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrSetDriverProperty;	/* VAR_OUTPUT */	
} iomgrsetdriverproperty_struct;

DEF_API(`void',`CDECL',`iomgrsetdriverproperty',`(iomgrsetdriverproperty_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x936FC5C4),0x03050800)

/**
 * <description>iomgrstartbuscycle</description>
 */
typedef struct tagiomgrstartbuscycle_struct
{
	IoConfigConnector *pConnector;		/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrStartBusCycle;	/* VAR_OUTPUT */	
} iomgrstartbuscycle_struct;

DEF_API(`void',`CDECL',`iomgrstartbuscycle',`(iomgrstartbuscycle_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x09EEEC27),0x03050800)

/**
 * start the bus cycle for a specific connector, and pass
 * * the type of this call as an additional option. This way,
 * * the driver knows in which conditions (see BusCycleType)
 * * was called, by calling IoMgrGetBusCycleType().
 * 
 */
typedef struct tagiomgrstartbuscycle2_struct
{
	IoConfigConnector *pConnector;		/* VAR_INPUT */	
	RTS_IEC_UDINT dwType;				/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrStartBusCycle2;	/* VAR_OUTPUT */	
} iomgrstartbuscycle2_struct;

DEF_API(`void',`CDECL',`iomgrstartbuscycle2',`(iomgrstartbuscycle2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x8AB99A18),0x03050800)

/**
 * <description>iomgrunregisterconfigapplication</description>
 */
typedef struct tagiomgrunregisterconfigapplication_struct
{
	RTS_IEC_STRING *pszConfigApplication;	/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrUnregisterConfigApplication;	/* VAR_OUTPUT */	
} iomgrunregisterconfigapplication_struct;

DEF_API(`void',`CDECL',`iomgrunregisterconfigapplication',`(iomgrunregisterconfigapplication_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xECB18F2E),0x03050800)

/**
 * <description>iomgrunregisterinstance</description>
 */
typedef struct tagiomgrunregisterinstance_struct
{
	RTS_IEC_HANDLE hInterface;			/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrUnregisterInstance;	/* VAR_OUTPUT */	
} iomgrunregisterinstance_struct;

DEF_API(`void',`CDECL',`iomgrunregisterinstance',`(iomgrunregisterinstance_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x830B7CC7),0x03050800)

/**
 * <description>iomgrupdateconfiguration</description>
 */
typedef struct tagiomgrupdateconfiguration_struct
{
	IoConfigConnector *pConnectorList;	/* VAR_INPUT */	
	RTS_IEC_DINT nCount;				/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrUpdateConfiguration;	/* VAR_OUTPUT */	
} iomgrupdateconfiguration_struct;

DEF_API(`void',`CDECL',`iomgrupdateconfiguration',`(iomgrupdateconfiguration_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB1381773),0x03050800)

/**
 * <description>iomgrupdateconfiguration2</description>
 */
typedef struct tagiomgrupdateconfiguration2_struct
{
	IoConfigConnector *pConnectorList;	/* VAR_INPUT */	
	RTS_IEC_DINT nCount;				/* VAR_INPUT */	
	RTS_IEC_STRING *pszConfigApplication;	/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrUpdateConfiguration2;	/* VAR_OUTPUT */	
} iomgrupdateconfiguration2_struct;

DEF_API(`void',`CDECL',`iomgrupdateconfiguration2',`(iomgrupdateconfiguration2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x44CD4528),0x03050800)

/**
 * <description>iomgrupdatemapping</description>
 */
typedef struct tagiomgrupdatemapping_struct
{
	IoConfigTaskMap *pTaskMapList;		/* VAR_INPUT */	
	RTS_IEC_DINT nCount;				/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrUpdateMapping;	/* VAR_OUTPUT */	
} iomgrupdatemapping_struct;

DEF_API(`void',`CDECL',`iomgrupdatemapping',`(iomgrupdatemapping_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0A15126C),0x03050800)

/**
 * <description>iomgrupdatemapping2</description>
 */
typedef struct tagiomgrupdatemapping2_struct
{
	IoConfigTaskMap *pTaskMapList;		/* VAR_INPUT */	
	RTS_IEC_DINT nCount;				/* VAR_INPUT */	
	RTS_IEC_STRING *pszConfigApplication;	/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrUpdateMapping2;	/* VAR_OUTPUT */	
} iomgrupdatemapping2_struct;

DEF_API(`void',`CDECL',`iomgrupdatemapping2',`(iomgrupdatemapping2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x775F7CAD),0x03050800)

/**
 * <description>iomgrwatchdogtrigger</description>
 */
typedef struct tagiomgrwatchdogtrigger_struct
{
	IoConfigConnector *pConnector;		/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrWatchdogTrigger;	/* VAR_OUTPUT */	
} iomgrwatchdogtrigger_struct;

DEF_API(`void',`CDECL',`iomgrwatchdogtrigger',`(iomgrwatchdogtrigger_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x986DFD93),0x03050800)

/**
 * <description>iomgrwriteoutputs</description>
 */
typedef struct tagiomgrwriteoutputs_struct
{
	IoConfigTaskMap *pTaskMap;			/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrWriteOutputs;	/* VAR_OUTPUT */	
} iomgrwriteoutputs_struct;

DEF_API(`void',`CDECL',`iomgrwriteoutputs',`(iomgrwriteoutputs_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xDA3433B3),0x03050800)

/**
 * <description>iomgrwriteparameter</description>
 */
typedef struct tagiomgrwriteparameter_struct
{
	RTS_IEC_DWORD dwModuleType;			/* VAR_INPUT */	
	RTS_IEC_DWORD dwInstance;			/* VAR_INPUT */	
	RTS_IEC_DWORD dwParameterId;		/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwBitSize;			/* VAR_INPUT */	
	RTS_IEC_DWORD dwBitOffset;			/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrWriteParameter;	/* VAR_OUTPUT */	
} iomgrwriteparameter_struct;

DEF_API(`void',`CDECL',`iomgrwriteparameter',`(iomgrwriteparameter_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xAD04F7E8),0x03050800)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


/* Only for backward compatibility! BEGIN */

/**
 * <description>iomgrconfiggetiodriver</description>
 */
typedef struct tagiomgrconfiggetiodriver_struct
{
	IoConfigConnector *pConnector;		/* VAR_INPUT */
	RTS_IEC_DINT *pbIecDriver;			/* VAR_INPUT */
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */
	IBase *IoMgrConfigGetIoDriver;		/* VAR_OUTPUT */
} iomgrconfiggetiodriver_struct;

/**
 * <description>IEC Interface for the function IoMgrConfigGetIoDriver()</description>
 */
DEF_API(`void',`CDECL',`iomgrconfiggetiodriver',`(iomgrconfiggetiodriver_struct *p)',1,0,0x3010200)

/* Only for backward compatibility! END */

/**
 * <category>Event parameter</category>
 * <element name="pConnectorList" type="IN">Pointer to connector list</element>
 * <element name="nCount" type="IN">Number of elements in connectors in list</element>
 */
typedef struct tagEVTPARAM_CmpIoMgr
{
	IoConfigConnector *pConnectorList;
	RTS_IEC_DINT nCount;
} EVTPARAM_CmpIoMgr;
#define EVTPARAMID_CmpIoMgr						0x0001
#define EVTVERSION_CmpIoMgr						0x0001

/**
 * <category>Event parameter</category>
 * <element name="pTaskMapList" type="IN">Pointer to task map list</element>
 * <element name="nCount" type="IN">Number of elements in map list</element>
 * <element name="pszConfigApplication" type="IN">Name of the mapping application</element>
 */
typedef struct
{
	IoConfigTaskMap *pTaskMapList;
	int nCount;
	char *pszConfigApplication;
} EVTPARAM_CmpIoMgrUpdateMapping;
#define EVTPARAMID_CmpIoMgrUpdateMapping		0x0002
#define EVTVERSION_CmpIoMgrUpdateMapping		0x0001

/**
 * <category>Event parameter</category>
 * <element name="hIoDrv" type="IN">Registered instance handle of the IO-driver</element>
 */
typedef struct
{
	RTS_HANDLE hIoDrv;
} EVTPARAM_CmpIoMgrUpdateDiag;
#define EVTPARAMID_CmpIoMgrUpdateDiag			0x0003
#define EVTVERSION_CmpIoMgrUpdateDiag			0x0001


/**
 * <category>Events</category>
 * <description>Event is sent before updating the IO-configuration</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpIoMgr</param>
 */
#define EVT_PrepareUpdateConfiguration							MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Events</category>
 * <description>Event is sent after updating the IO-configuration</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpIoMgr</param>
 */
#define EVT_DoneUpdateConfiguration								MAKE_EVENTID(EVTCLASS_INFO, 2)

/**
 * <category>Events</category>
 * <description>Event is sent after the config application is started</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpIoMgr</param>
 */
#define EVT_ConfigAppStartedDone								MAKE_EVENTID(EVTCLASS_INFO, 3)

/**
 * <category>Events</category>
 * <description>Event is sent before the config application is stopped</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpIoMgr</param>
 */
#define EVT_PrepareConfigAppStopped								MAKE_EVENTID(EVTCLASS_INFO, 4)

/**
 * <category>Events</category>
 * <description>Event is sent before updating the IO-mapping of an application</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpIoMgrUpdateMapping</param>
 */
#define EVT_PrepareUpdateMapping								MAKE_EVENTID(EVTCLASS_INFO, 5)

/**
 * <category>Events</category>
 * <description>Event is sent after updating the IO-mapping of an application</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpIoMgrUpdateMapping</param>
 */
#define EVT_DoneUpdateMapping									MAKE_EVENTID(EVTCLASS_INFO, 6)

/**
 * <category>Events</category>
 * <description>Event is sent after updating the module diagnosis of the specified driver, which supports the property DRVPROP_BACKGROUND_GETDIAG</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpIoMgrUpdateDiag</param>
 */
#define EVT_UpdateDiagDone										MAKE_EVENTID(EVTCLASS_INFO, 7)

/**
 * <category>Events</category>
 * <description>Event is sent after the config application is stopped</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpIoMgr</param>
 */
#define EVT_ConfigAppStoppedDone								MAKE_EVENTID(EVTCLASS_INFO, 8)


typedef struct
{
	RTS_IEC_DWORD dwClassId;
	RTS_IEC_DWORD dwItfId;
	void *pInterface;
	RTS_IEC_UDINT *pResult;
	RTS_IEC_HANDLE hInterface;
} iomgrregisterinstance_struct;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Exception handler of the IO-manager</description>
 * <param name="pszApplication" type="IN">Pointer to the specified application name, in which the exception was generated</param>
 * <param name="ulException" type="IN">Exception number of the exception. See SysExceptItf.h for details.</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">This function never fails</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IoMgrExceptionHandler',`(char *pszApplication, RTS_UI32 ulException)')

/**
 * <description>
 * <p>This function has the same behavior as IoMgrRegisterInstance2() but
 * is not able to handle IEC drivers</p>
 * </description>
 * <param name="pIBase" type="IN">IBase interface of the IO-driver</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Driver was successfully registered</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">No driver pool was found</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pIBase was NULL or bIecDriver was set but not supported</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">There was no space left in the device pool</errorcode>
 * <result>Handle to the registered instance</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IoMgrRegisterInstance',`(IBase *pIBase, RTS_RESULT *pResult)')
DEF_API(`void',`CDECL',`iomgrregisterinstance',`(iomgrregisterinstance_struct *p)',1,0)

/**
 * <description>
 * <p>Register an instance of an IO-driver.</p>
 * <p>This function registers C as well as IEC drivers in a common
 * device pool.</p>
 * </description>
 * <param name="pIBase" type="IN" range="[NULL,VALID_IBASE]">IBase interface of the IO-driver</param>
 * <param name="bIecDriver" type="IN" range="[0,1]">Specifies if IBase describes a C or an IEC driver</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <parampseudo name="bException" type="OUT">Exception occured, because MemPool is full</parampseudo>
 * <parampseudo name="DevicePool" type="IN" range="[VALID_MEMPOOL,FULL_MEMPOOL]">State of MemPool</parampseudo>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Driver was successfully registered</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">No driver pool was found</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pIBase was NULL or bIecDriver was set but not supported</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">There was no space left in the device pool</errorcode>
 * <result>Handle to the registered driver instance</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`IoMgrRegisterInstance2',`(IBase *pIBase, int bIecDriver, RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Unregister an instance of an IO-driver</p>
 * <p>Note: For SIL2, this function is only allowed in debug mode, or from a safe context in safety mode.</p>
 * </description>
 * <param name="pIBase" type="IN" range="[NULL,VALID_IBASE,INVALID_IBASE]">IBase interface of the IO-driver</param>
 * <parampseudo name="SIL2ModeDebug" type="IN" range="[0,1]">SIL2 safety mode</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception occured, not allowed in safety mode</parampseudo>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Driver unregistered successfully</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Parameter invalid or driver not found</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The I/O Manager component was not correctly initialized</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Internal error</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IoMgrUnregisterInstance',`(IBase *pIBase)')

/**
 * <description>Get first registered driver instance</description>
 * <param name="pbIecDriver" type="INOUT" range="[NULL,VALID_PBIECDRIVER]">Pointer to return, if the instance is an IEC- or C-driver:
 *	1= pIBase is an interface of an IEC-driver, 0= C-driver</param>
 * <parampseudo name="bIecDriver" type="IN" range="[0,1]">If the instance is an IEC- or C-driver</parampseudo>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Driver retrieved successfully</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Parameter invalid</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">Driver could not be found</errorcode>
 * <result>Handle to the first instance</result>
 */
DEF_ITF_API(`IBase*',`CDECL',`IoMgrGetFirstDriverInstance',`(int *pbIecDriver, RTS_RESULT *pResult)')

/**
 * <description>Get the next registered driver instance</description>
 * <param name="pIBasePrev" type="IN" range="[NULL,VALID_PIBASEPREV,INVALID_PIBASEPREV]">Pointer to IBase of the previous interface</param>
 * <param name="pbIecDriver" type="INOUT" range="[NULL,VALID_PBIECDRIVER]">Pointer to return, if the instance is an IEC- or C-driver:
 * <parampseudo name="bIecDriver" type="IN" range="[0,1]">If the instance is an IEC- or C-driver</parampseudo>
 *	1= pIBase is an interface of an IEC-driver, 0= C-driver</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Driver retrieved successfully</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Parameter invalid</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">Driver could not be found</errorcode>
 * <result>Handle to the first instance</result>
 */
DEF_ITF_API(`IBase*',`CDECL',`IoMgrGetNextDriverInstance',`(IBase *pIBasePrev, int *pbIecDriver, RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Set the properties of a driver.</p>
 * <p>This function overwrites all existing properties of the driver.</p>
 * </description>
 * <param name="pIBase" type="IN" range="[NULL,VALID_IBASE]">Pointer to IBase interface of the driver</param>
 * <param name="ulProperties" type="IN" range="[0,VALID_PROPERTIES]">Properties of the driver. See category "Driver property flags" for detailed information.</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Properties where successfully overwritten</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Driver could not be found</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IoMgrSetDriverProperties',`(IBase *pIBase, RTS_UI32 ulProperties)')

/**
 * <description>
 * <p>Get a pointer to the properties of a driver.</p>
 * </description>
 * <param name="pIBase" type="IN" range="[NULL,VALID_IBASE]">Pointer to IBase interface of the driver</param>
 * <param name="ppulProperty" type="INOUT" range="[NULL,VALID_PROPERTY_POINTER]">Pointer will point to the properties of the driver.</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Pointer to properties was returned successfully</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pIBase or ppulProperty was NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No driver found</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IoMgrGetDriverProperties',`(IBase *pIBase, RTS_UI32 **ppulProperty)')

/**
 * <description>
 * <p>Modify a Property Bitfield of a driver.</p>
 * <p>The bits in the mask ulProperty are set or reset, depending on the value of bValue.</p>
 * </description>
 * <param name="pIBase" type="IN" range="[NULL,VALID_IBASE]">Pointer to IBase interface of the driver</param>
 * <param name="bValue" type="IN" range="[0,1]">Value to set.</param>
 * <param name="ulProperty" type="IN" range="[0,VALID_PROPERTY]">Property of the driver. See category "Driver property flags" for detailed information.</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">The Property was successfully set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Driver could not be found</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`IoMgrSetDriverProperty',`(IBase *pIBase, RTS_UI32 ulProperty, int bValue)')

/**
 * <description>
 * <p>Register the name of the application that contains the IO-configuration.</p>
 * </description>
 * <param name="pszConfigApplication" type="IN" range="[NULL,VALID_CONFIGAPP_NAME]">Pointer to the name of the IO-config application</param>
 * <parampseudo name="pszRegisteredConfigApplication" type="IN" range="[NULL,VALID_CONFIGAPP_NAME,INVALID_CONFIGAPP_NAME]">Registered Config Application</parampseudo>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">The config application was registered</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_DUPLICATE">Another application is already registered</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pszConfigApplication was NULL</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrRegisterConfigApplication', `(char *pszConfigApplication)')

/**
 * <description>
 * <p>Unregister the name of the application that contains the IO-configuration.</p>
 * </description>
 * <param name="pszConfigApplication" type="IN" range="[NULL,VALID_CONFIGAPP]">Pointer to the name of the IO-config application</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">The config application was unregistered</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">The application is not the registered config application</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pszConfigApplication was NULL</errorcode>
 * <parampseudo name="pszRegisteredConfigApplication" type="IN" range="[NULL,VALID_REGISTERED_CONFIGAPP]">Registered Config Application</parampseudo>
 * <parampseudo name="bException" type="OUT">SIL2 Runtime: Exception if not in Debug Mode</parampseudo>
 * <parampseudo name="bSIL2SafeMode" type="IN" range="[0,1]">SIL2 Runtime: SIL2 OpMode</parampseudo>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrUnregisterConfigApplication', `(char *pszConfigApplication)')

/**
 * <description>
 * <p>Return the name of the application that contains the I/O configuration.</p>
 * <p>If the parameter pszConfigApplication is NULL, only the size of the string is returned.</p>
 * </description>
 * <param name="pszConfigApplication" type="IN" range="[NULL,VALID_CONFIGAPP]">Pointer to get the name of the IO-config application</param>
 * <param name="pnMaxLen" type="INOUT" range="[NULL,VALID_CONFIGAPP_LENGTH]">IN: size of pszConfigApplication, OUT: Size of config application if psz</param>
 * <parampseudo name="pszRegisteredConfigApplication" type="IN" range="[NULL,VALID_REGISTERED_CONFIGAPP]">Registered Config Application</parampseudo>
 * <errorcode name="RTS_RESULT" type="ERR_OK">The config application was retrieved successfully</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No config application registered</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pnMaxLen was NULL</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrGetConfigApplication', `(char *pszConfigApplication, int *pnMaxLen)')

/**
 * <description>
 * <p>Interface to inform all IO-drivers about a new IO-configuration.</p>
 * <p>On initialization, the parameter pConnectorList describes the
 * whole I/O configuration of the IEC application.</p>
 * <p>On Reset or deletion of the application, this function is called,
 * too, but then with the parameter pConnectorList set to NULL.</p>
 * <p>Note: When an I/O driver returns ERR_EXCEPTION, the I/O Manager puts 
 * the application into an exception state. All other errors are just, logged.</p>
 * <p>Note2: On SIL2 runtimes, any error code that is returned by the I/O
 * driver, leads to an exception.</p>
 * </description>
 * <param name="pConnectorList" type="IN" range="[NULL,VALID_CONNECTORLIST]">Pointer to the complete connector list of the IO-configuration</param>
 * <param name="nCount" type="INOUT" range="[0,VALID_CONNECTORCOUNT]">Number of connectors in the connector list</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Update Configuration of all drivers was successfull</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrUpdateConfiguration', `(IoConfigConnector *pConnectorList, int nCount)')

/**
 * <description>
 * <p>Interface to inform all IO-drivers about a new IO-configuration.</p>
 * <p>On initialization, the parameter pConnectorList describes the
 * whole I/O configuration of the IEC application.</p>
 * <p>On Reset or deletion of the application, this function is called,
 * too, but then with the parameter pConnectorList set to NULL.</p>
 * <p>Note: When an I/O driver returns ERR_EXCEPTION, the I/O Manager puts 
 * the application into an exception state. All other errors are just, logged.</p>
 * <p>Note2: On SIL2 runtimes, any error code that is returned by the I/O
 * driver, leads to an exception.</p>
 * </description>
 * <param name="pConnectorList" type="IN" range="[NULL,VALID_CONNECTORLIST]">Pointer to the complete connector list of the IO-configuration</param>
 * <param name="nCount" type="IN" range="[0,VALID_CONNECTORCOUNT]">Number of connectors in the connector list</param>
 * <param name="pszConfigApplication" type="IN" range="[NULL,VALID_CONFIGAPP]">Pointer to the application name in which context this function is called</param>
 * <parampseudo name="bUpdateConfigFailed" type="IN" range="[0,1]">Pointer to the application name in which context this function is called</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception is thrown as UpdateConfiguration failed</parampseudo>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Update Configuration of all drivers was successfull</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Update Configuration of at least one driver failed</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrUpdateConfiguration2', `(IoConfigConnector *pConnectorList, int nCount, char *pszConfigApplication)')

/**
 * <description>
 * Function to check, if specified IEC task has mapped inputs or outputs.
 * </description>
 * <param name="dwTaskId" type="IN">Index of the IEC task</param>
 * <param name="taskMapType" type="IN">Input or output type. See category "Task map types" for detailed information.</param>
 * <param name="pResult" type="OUT">Pointer to the error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">TaskID could be verified</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid taskid or maptype</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Interface function not implemented</errorcode>
 * <result>TRUE=Task has mapped requested IO types; FALSE=Task has _no_ mapped requested IO types</result>
 */
DEF_ITF_API(`RTS_BOOL', `CDECL', `IoMgrHasTaskIOs', `(RTS_UI32 dwTaskId, RTS_UI16 taskMapType, RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Interface to inform all IO-drivers about a new IO-mapping.</p>
 * </description>
 * <param name="pTaskMapList" type="IN" range="[NULL,VALID_TASKMAPLIST,INVALID_TASKMAPLIST]">Pointer to the complete task map list</param>
 * <param name="nCount" type="INOUT" range="[0,VALID_TASKMAPCOUNT,INVALID_TASKMAPCOUNT]">Number of task map entries in the list</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">All registered drivers where informed about the change</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pTaskMapList may not be NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Update Mapping of at least one driver failed</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrUpdateMapping', `(IoConfigTaskMap *pTaskMapList, int nCount)')

/**
 * <description>
 * <p>Interface to inform all IO-drivers about a new IO-mapping.</p>
 * <p>Note: When an I/O driver returns ERR_EXCEPTION, the I/O Manager puts 
 * the application into an exception state. All other errors are just, logged.</p>
 * <p>Note2: On SIL2 runtimes, any error code that is returned by the I/O
 * driver, leads to an exception.</p>
 * </description>
 * <param name="pTaskMapList" type="IN" range="[NULL,VALID_TASKMAPLIST,INVALID_TASKMAPLIST]">Pointer to the complete task map list</param>
 * <param name="nCount" type="IN" range="[0,VALID_TASKMAPCOUNT]">Number of task map entries in the list</param>
 * <param name="pszConfigApplication" type="IN" range="[NULL,VALID_CONFIGAPP]">Pointer to the application name in which context this function is called</param>
 * <parampseudo name="dwTaskId" type="IN" range="[0,1,NUM_OF_STATIC_IEC_TASKS]">Exception is thrown if Taskmap is corrupted, or TaskId invalid</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception is thrown if Taskmap is corrupted, or TaskId invalid</parampseudo>
 * <parampseudo name="bUpdateMappingFailed" type="IN" range="[0,1]">UpdateMapping Failed in IoDriver</parampseudo>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">All registered drivers where informed about the change</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pTaskMapList may not be NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Update Mapping of at least one driver failed</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrUpdateMapping2', `(IoConfigTaskMap *pTaskMapList, int nCount, char *pszConfigApplication)')

/**
 * <description>
 * <p>Interface to reconfigure a single connector respectively the corresponding master.</p>
 * <p>In the reconfigure sequence we call the corresponding IO-driver at the connector the following way:
 *    1. disable the IO-configuration
 *    2. enable the IO-configuration
 *    3. update the mapping
 *	This sequence is called asynchronously so the asynchronous state is transported in pudi</p>
 *
 *	NOTE:
 *	If the CmpAsyncMgr ist not available, the reconfiguration is done synchronously!
 *
 * </description>
 * <param name="pConnector" type="IN" range="[NULL,VALID_CONNECTOR_1,INVALID_CONNECTOR]">Pointer to the connector to reconfigure</param>
 * <param name="pui32State" type="OUT">Pointer to get the asynchronous status of the reconfigure operation. See States in CmpAsyncMgrItf.h for details.</param>
 * <parampseudo name="SIL2OpModeSafe" type="IN" range="[0,1]">Is not allowed in SIL2 Mode</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception if in Safe Mode</parampseudo> 
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Asynchronous reconfigure can be startet</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">One of the parameter is NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">CmpAsyncMgr is not available</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrReconfigure', `(IoConfigConnector *pConnector, RTS_UI32 *pui32State)')

/**
 * <description>
 * <p>Interface to perform an update of all inputs of one task.</p>
 * <p>This function is called once out of each IEC-task, in which inputs are referenced.
 * This call is passed to every I/O driver that is used by this task.</p>
 * <p>Throws Exception if dwDriverSpecific is 0.</p>
 * </description>
 * <param name="pTaskMap" type="IN" range="[NULL,VALID_TASKMAP,INVALID_TASKMAP]">Pointer to the task map, which references all input channels of the task</param>
 * <parampseudo name="hIoDrv" type="IN" range="[NULL,VALID_TASKMAP_IBASE]">hIoDrv May be NULL</parampseudo>
 * <parampseudo name="dwIoMgrSpecific" type="IN" range="[0,1]">dwIoMgrSpecific contains a valid cound or not</parampseudo>
 * <parampseudo name="IsCalled" type="OUT">Is Testdriver called or not</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception thrown</parampseudo>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">All registered drivers where called</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">TaskMap may not be null</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">dwDriverSpecific may not be 0</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrReadInputs', `(IoConfigTaskMap *pTaskMap)')

/**
 * <description>
 * <p>Interface to perform an update of all outputs of one task.</p>
 * <p>This function is called once out of each IEC-task, in which outputs are referenced.
 * This call is passed to every I/O driver that is used by this task.</p>
 * <p>Throws Exception if dwDriverSpecific is 0.</p>
 * </description>
 * <param name="pTaskMap" type="IN" range="[NULL,VALID_TASKMAP,INVALID_TASKMAP]">Pointer to the task map, which references all output channels of the task</param>
 * <parampseudo name="hIoDrv" type="IN" range="[NULL,VALID_TASKMAP_IBASE]">hIoDrv May be NULL</parampseudo>
 * <parampseudo name="dwIoMgrSpecific" type="IN" range="[0,1]">dwIoMgrSpecific contains a valid cound or not</parampseudo>
 * <parampseudo name="bFlowControlError" type="IN" range="[0,1]">Error in FlowControl</parampseudo>
 * <parampseudo name="IsCalled" type="OUT">Is Testdriver called or not</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception thrown</parampseudo> 
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">All registered drivers where called</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">TaskMap may not be null</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">dwDriverSpecific may not be 0</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrWriteOutputs', `(IoConfigTaskMap *pTaskMap)')

/**
 * <description>
 * <p>This function is deprecated. Newer versions of the iostandard library,
 * are using IoMgrStartBusCycle2.</p>
 * </description>
 * <param name="pConnector" type="IN" range="[NULL,VALID_CONNECTOR_1,INVALID_CONNECTOR]">Pointer to the connector that needs a bus cycle</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">All registered drivers where called</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pConnector may not be null</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">No Driver found</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrStartBusCycle', `(IoConfigConnector *pConnector)')

/**
 * <description>
 * <p>This function is called for every connector that has the setting "needs bus cycle"
 * in the device description. It is only called once and only from the context of the
 * so called "buscycle task". This task can be specified globally (= default for all
 * drivers), or specifically for every driver.</p>
 * <p>The parameter dwType defines if the function was calle at the beginning
 * or at the end of the IEC task cycle. This value, can actively be requested
 * by the driver, by calling IoMgrGetBusCycleType().</p>
 * </description>
 * <param name="pConnector" type="IN" range="[NULL,VALID_CONNECTOR_1,INVALID_CONNECTOR]">Pointer to the connector that needs a bus cycle</param>
 * <param name="dwType" type="IN" range="[BCT_START,BCT_END]">Type of the bus cycle</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">All registered drivers where called</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pConnector may not be null</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">No Driver found</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrStartBusCycle2', `(IoConfigConnector *pConnector, RTS_UI32 dwType)')

/**
 * <description>
 * <p>This function can be called by the I/O driver, within the function 
 * IoDrvStartBusCycle, to determine if this bus cycle was called at the
 * beginning or at the end of a task cycle.</p>
 * <p>Note: When this function is called when an application is loaded, that
 * uses an older version of the iostandard library, the function will return
 * ERR_FAILED, as the caller context can't be determined.</p>
 * </description>
 * <param name="pConnector" type="IN" range="[NULL,VALID_CONNECTOR_1,INVALID_CONNECTOR]">Pointer to the connector that got the bus cycle</param>
 * <param name="pResult" type="OUT">Pointer to the error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">The current type was returned successfully</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pConnector was null, or didn't contain a valid driver handle</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">The function was called outside of IoDrvStartBuscycle or the iostandard library was too old</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrGetBusCycleType', `(IoConfigConnector *pConnector, RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Interface to scan submodule on the specified connector.</p>
 * <p>This interface is optional and may not be implemented by the runtime system.</p>
 * </description>
 * <param name="pConnector" type="IN" range="[NULL,VALID_CONNECTOR]">Pointer to connector</param>
 * <param name="ppConnectorList" type="OUT" range="[NULL,VALID_SCAN_CONNECTORLIST]">List of submodule connectors</param>
 * <param name="pnCount" type="OUT" range="[NULL,VALID_CONNECTORCOUNT_P]">Pointer to elements in the connector list</param>
 * <parampseudo name="SIL2OpModeSafe" type="IN" range="[0,1]">Is not allowed in SIL2 Mode</parampseudo>
 * <parampseudo name="bScanSuccessful" type="IN" range="[0,1]">IoDrvStub return value for the scan</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception if in Safe Mode</parampseudo>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Scan was executed successfully.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">hIoDrv was invalid or one of the other parameters was NULL.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Internal error</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PENDING">Scan still in progress. Function will be called again. ppConnectorList and pnCount may contain a partial scan result.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrScanModules', `(IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount)')

/**
 * <description>
 * <p>Get diagnostic flags of specified connector.</p>
 * </description>
 * <param name="pConnector" type="IN" range="[NULL,VALID_CONNECTOR,INVALID_CONNECTOR]">Pointer to connector</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Diagnostic flags could be read</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Diagnostic info could not be read</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pConnector may not be null</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrGetModuleDiagnosis', `(IoConfigConnector *pConnector)')

/**
 * <description>
 * <p>Interface to identify a device specified by connector.</p>
 * <p>This can be used for example to blink a LED on the device to identify it physically.</p>
 * </description>
 * <param name="pConnector" type="IN" range="[NULL,VALID_CONNECTOR,INVALID_CONNECTOR]">Pointer to connector</param>
 * <parampseudo name="SIL2OpModeSafe" type="IN" range="[0,1]">Is not allowed in SIL2 Mode</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception if in Safe Mode</parampseudo> 
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">This error code is passed directly from the driver.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pConnector may not be null.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Driver returned ERR_FAILED or driver not found</errorcode> 
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrIdentify', `(IoConfigConnector *pConnector)')

/**
 * <description>Interface to nominate a device specified by connector. Nomination can be used for example
 *	for ProfiNET devices to configure their IP-addresses.</description>
 * <param name="pConnector" type="IN">Pointer to connector</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrNominate', `(IoConfigConnector *pConnector)')

/**
 * <description>
 * <p>If enabled in the device description, this function is called periodically to
 * trigger some kind of hardware watchdog.</p>
 * </description>
 * <param name="pConnector" type="IN" range="[NULL,VALID_CONNECTOR_1]">Pointer to the connector of the device</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Watchdog triggered successfully</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOT_SUPPORTED">Function is not implemented on this target</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrWatchdogTrigger', `(IoConfigConnector *pConnector)')

/**
 * <description>
 * <p>Interface to get a parameter on a specified connector specified by ID</p>
 * </description>
 * <param name="pConnector" type="IN" range="[NULL,VALID_CONNECTOR,INVALID_CONNECTOR]">Pointer to connector</param>
 * <param name="dwParameterId" type="IN" range="[VALID_PARAMETERID,INVALID_PARAMETERID]">ID of the parameter. Is defined in the device description.</param>
 * <parampseudo name="bException" type="OUT">Exception occured for Invalid Connector</parampseudo>
 * <result>Parameter or NULL if failed</result>
 */
DEF_ITF_API(`IoConfigParameter*', `CDECL', `IoMgrConfigGetParameter', `(IoConfigConnector *pConnector, RTS_UI32 dwParameterId)')

/**
 * <description>
 * <p>Interface to get the DWORD value out of the specified parameter</p>
 * </description>
 * <param name="pParameter" type="IN" range="[NULL,VALID_PARAMETER_BYTE,VALID_PARAMETER_WORD,VALID_PARAMETER_DWORD,INVALID_PARAMETER_DWORD_LEN,INVALID_PARAMETER_DWORD]">Pointer to the parameter</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <parampseudo name="bException" type="OUT">Exception occured for Invalid Parameter</parampseudo>
 * <result>Value of the parameter or 0 if failed. Please check always pResult additionally!</result>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Value was read successfully</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">pParameter was NULL or Parameter has not the value flag</errorcode>
 */
DEF_ITF_API(`RTS_UI32', `CDECL', `IoMgrConfigGetParameterValueDword', `(IoConfigParameter *pParameter, RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Interface to get the WORD value out of the specified parameter</p>
 * </description>
 * <param name="pParameter" type="IN" range="[NULL,VALID_PARAMETER_BYTE,VALID_PARAMETER_WORD,VALID_PARAMETER_DWORD,INVALID_PARAMETER_WORD_LEN,INVALID_PARAMETER_WORD]">Pointer to the parameter</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <parampseudo name="bException" type="OUT">Exception occured for Invalid Parameter</parampseudo>
 * <result>Value of the parameter or 0 if failed. Please check always pResult additionally!</result>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Value was read successfully</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">pParameter was NULL or Parameter has not the value flag</errorcode>
 */
DEF_ITF_API(`unsigned short', `CDECL', `IoMgrConfigGetParameterValueWord', `(IoConfigParameter *pParameter, RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Interface to get the BYTE value out of the specified parameter</p>
 * </description>
 * <param name="pParameter" type="IN" range="[NULL,VALID_PARAMETER_BYTE,VALID_PARAMETER_WORD,VALID_PARAMETER_DWORD,INVALID_PARAMETER_BYTE_LEN,INVALID_PARAMETER_BYTE]">Pointer to the parameter</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <parampseudo name="bException" type="OUT">Exception occured for Invalid Parameter</parampseudo>
 * <result>Value of the parameter or 0 if failed. Please check always pResult additionally!</result>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Value was read successfully</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">pParameter was NULL or Parameter has not the value flag</errorcode>
 */
DEF_ITF_API(`unsigned char', `CDECL', `IoMgrConfigGetParameterValueByte', `(IoConfigParameter *pParameter, RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Interface to get the POINTER to the value out of the specified parameter</p>
 * </description>
 * <param name="pParameter" type="IN" range="[NULL,VALID_PARAMETER_POINTER,INVALID_PARAMETER]">Pointer to the parameter</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <parampseudo name="bException" type="OUT">Exception occured for Invalid Parameter</parampseudo>
 * <result>Pointer to the value or NULL if failed. Please check always pResult additionally!</result>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Value was read successfully</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">pParameter was NULL or Parameter has not the value flag</errorcode>
 */
DEF_ITF_API(`void *', `CDECL', `IoMgrConfigGetParameterValuePointer', `(IoConfigParameter *pParameter, RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Get the first connector with the specified wType in the connector list.</p>
 * <p>pnCount is decreased and contains the rest of elements still remaining in list.</p>
 * </description>
 * <param name="pConnectorList" type="IN" range="[NULL,VALID_CONNECTORLIST,INVALID_CONNECTORLIST]">Pointer to connector list</param>
 * <param name="pnCount" type="INOUT" range="[NULL,VALID_CONNECTORCOUNT_P]">Pointer to number of elements in list</param>
 * <param name="wType" type="IN" range="[0,VALID_MODULE_TYPE]">Type of the connector</param>
 * <parampseudo name="bException" type="OUT">Exception if Connectorlist is invalid</parampseudo>
 * <result>Pointer to the connector or NULL if not found</result>
 */
DEF_ITF_API(`IoConfigConnector*', `CDECL', `IoMgrConfigGetFirstConnector', `(IoConfigConnector *pConnectorList, int *pnCount, unsigned short wType)')

/**
 * <description>
 * <p>Get the next connector with the specified wType in the connector list.</p>
 * <p>pnCount is decreased and contains the rest of elements still remaining in list.</p>
 * </description>
 * <param name="pConnectorList" type="IN" range="[NULL,VALID_CONNECTORLIST,INVALID_CONNECTORLIST]">Pointer to connector list</param>
 * <param name="pnCount" type="INOUT" range="[NULL,VALID_CONNECTORCOUNT_P]">Pointer to number of elements in list</param>
 * <param name="wType" type="IN" range="[0,VALID_MODULE_TYPE]">Type of the connector</param>
 * <parampseudo name="bException" type="OUT">Exception if Connectorlist is invalid</parampseudo>
 * <result>Pointer to the connector or NULL if not found</result>
 */
DEF_ITF_API(`IoConfigConnector*', `CDECL', `IoMgrConfigGetNextConnector', `(IoConfigConnector *pConnectorList, int *pnCount, unsigned short wType)')

/**
 * <description>
 * <p>Get the first child connector of the specified father connector.</p>
 * <p>pnCount is decreased and contains the rest of elements still remaining in list.</p>
 * </description>
 * <param name="pConnectorList" type="IN" range="[NULL,VALID_CONNECTORLIST,INVALID_CONNECTORLIST]">Pointer to connector list</param>
 * <param name="pnCount" type="INOUT" range="[NULL,VALID_CONNECTORCOUNT_P]">Pointer to number of elements in list</param>
 * <param name="pFather" type="IN" range="[NULL,VALID_PARENTCONNECTOR,INVALID_PARENTCONNECTOR]">Pointer to the father connector</param>
 * <parampseudo name="bException" type="OUT">Exception at Connectorlist check</parampseudo>
 * <result>Pointer to the child connector or NULL if not found</result>
 */
DEF_ITF_API(`IoConfigConnector*', `CDECL', `IoMgrConfigGetFirstChild', `(IoConfigConnector *pConnectorList, int *pnCount, IoConfigConnector *pFather)')

/**
 * <description>
 * <p>Get the next child connector of the specified father connector.</p>
 * <p>pnCount is decreased and contains the rest of elements still remaining in list.</p>
 * </description>
 * <param name="pConnectorList" type="IN" range="[NULL,VALID_CONNECTORLIST,INVALID_CONNECTORLIST]">Pointer to connector list</param>
 * <param name="pnCount" type="INOUT" range="[NULL,VALID_CONNECTORCOUNT_P]">Pointer to number of elements in list</param>
 * <param name="pFather" type="IN" range="[NULL,VALID_PARENTCONNECTOR,INVALID_PARENTCONNECTOR]">Pointer to the father connector</param>
 * <parampseudo name="bException" type="OUT">Exception at Connectorlist check</parampseudo>
 * <result>Pointer to the child connector or NULL if not found</result>
 */
DEF_ITF_API(`IoConfigConnector*', `CDECL', `IoMgrConfigGetNextChild', `(IoConfigConnector *pConnectorList, int *pnCount, IoConfigConnector *pFather)')

/**
 * <description>
 * <p>Get the actual IO-configuration in form of the connector list.</p>
 * <p>If the parameter ppConnectorList is NULL, only the size of the list will be returned.</p>
 * </description>
 * <parampseudo name="RegisteredConnectorList" type="IN"  range="[NULL,VALID_CONNECTORLIST,INVALID_CONNECTORLIST]">Registered Pointer to connector list</parampseudo>
 * <param name="ppConnectorList" type="OUT">Pointer to connector list</param>
 * <parampseudo name="bException" type="OUT">Exception if Connectorlist is invalid</parampseudo>
 * <param name="pnCount" type="INOUT"  range="[NULL,VALID_CONNECTORCOUNT_P]">Number of elements in the list</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">There was a list registered and at least the size could be returned</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Registered list was corrupted</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No list was registered, yet</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pnCount was NULL</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrConfigGetConnectorList', `(IoConfigConnector **ppConnectorList, int *pnCount)')

/**
 * <description>
 * <p>Get the connector specified by ModuleType and ModuleInstance number</p>
 * <p>pnCount is decreased and contains the rest of elements, still remaining in list! </p>
 * <p>Might be called with NULL as Connectorlist, then the Connectorlist and pnCount from the last call to UpdateConfiguration is used </p>
 * <p>Returns NULL if pnCount is NULL, if ulInstance is greater than nCount, no fitting Connector with given Instance and Type is found or (if pConnectorList is Null, the last stored ConnectorList is also NULL) </p>
 * </description>
 * <param name="pConnectorList" type="IN" range="[NULL,VALID_CONNECTORLIST,INVALID_CONNECTORLIST]">Pointer to connector list</param>
 * <param name="pnCount" type="INOUT" range="[NULL,VALID_CONNECTORCOUNT_P_P,INVALID_CONNECTORCOUNT_P_P]">Number of elements in the list</param>
 * <param name="ulModuleType" type="IN" range="[0,VALID_MODULE_TYPE]">Module type</param>
 * <param name="ulInstance" type="IN" range="[0,VALID_INSTANCE_COUNT,INVALID_INSTANCE_COUNT]">Instance number</param>
 * <parampseudo name="Exception" type="OUT">Exception may be thrown if problem occurs while checking Connectorlist</parampseudo>
 * <result>Pointer to found connector or NULL</result>
 */
DEF_ITF_API(`IoConfigConnector*', `CDECL', `IoMgrConfigGetConnector', `(IoConfigConnector *pConnectorList, int *pnCount, RTS_UI32 ulModuleType, RTS_UI32 ulInstance)')

/**
 * <description>
 * <p>Interface to set the diagnostic flags in the connector.</p>
 * <p>Only the bits that are specified with 1 in the passed ulFlags parameter
 * will be set.</p>
 * </description>
 * <param name="pConnector" type="IN" range="[NULL,VALID_CONNECTOR,INVALID_CONNECTOR]">Pointer to connector</param>
 * <param name="ulFlags" type="IN" range="[0x0001,0x0010,0x0020,0x0040,0x0080,0x0100,0x0200,0x0400,0x0800]">Flags to write</param>
 * <parampseudo name="bException" type="OUT">Exception caused by INVALID_CONNECTOR</parampseudo>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrConfigSetDiagnosis', `(IoConfigConnector *pConnector, RTS_UI32 ulFlags)')

/**
 * <description>
 * <p>Interface to reset the diagnostic flags in the connector.</p>
 * <p>Only the bits that are specified with 1 in the passed ulFlags parameter
 * will be resetted.</p>
 * </description>
 * <param name="pConnector" type="IN" range="[NULL,VALID_CONNECTOR,INVALID_CONNECTOR]">Pointer to connector</param>
 * <param name="ulFlags" type="IN" range="[0x0001,0x0010,0x0020,0x0040,0x0080,0x0100,0x0200,0x0400,0x0800]">Flags to write</param>
 * <parampseudo name="bException" type="OUT">Exception caused by INVALID_CONNECTOR</parampseudo>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Diagnostic flags set successfully</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pConnector was NULL or not consistent</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrConfigResetDiagnosis', `(IoConfigConnector *pConnector, RTS_UI32 ulFlags)')

/**
 * <description>
 * <p>Interface to read a specified parameter.</p>
 * <p>This interface is optional and may not be implemented by the runtime system.</p>
 * </description>
 * <param name="ulModuleType" type="IN" range="[0,VALID_MODULE_TYPE]">Module type</param>
 * <param name="ulInstance" type="IN" range="[0,VALID_INSTANCE_COUNT,INVALID_INSTANCE_COUNT]">Instance number</param>
 * <param name="ulParameterId" type="IN" range="[VALID_PARAMETERID_1,INVALID_PARAMETERID_1]">ID of the parameter. Is defined in the device description.</param>
 * <param name="pData" type="IN" range="[NULL,VALID_PDATA]">Pointer to read in the parameter value</param>
 * <param name="ulBitSize" type="IN" range="[0,VALID_BITSIZE]">Bits to read</param>
 * <param name="ulBitOffset" type="IN" range="[0,VALID_BITOFFSET]">Bitoffset of the parameter value</param>
 * <parampseudo name="bSafetyMode" type="IN" range="[0,1]">According to SIL2 operation mode this function may not be called</parampseudo>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrReadParameter', `(RTS_UI32 ulModuleType, RTS_UI32 ulInstance, RTS_UI32 ulParameterId, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)')

/**
 * <description>
 * <p>Interface to write a specified parameter.</p>
 * <p>This interface is optional and may not be implemented by the runtime system.</p>
 * </description>
 * <param name="ulModuleType" type="IN" range="[0,VALID_MODULE_TYPE]">Module type</param>
 * <param name="ulInstance" type="IN" range="[0,VALID_INSTANCE_COUNT,INVALID_INSTANCE_COUNT]">Instance number</param>
 * <param name="ulParameterId" type="IN" range="[VALID_PARAMETERID_1,INVALID_PARAMETERID_1]">ID of the parameter. Is defined in the device description.</param>
 * <param name="pData" type="IN" range="[NULL,VALID_PDATA]">Pointer to the parameter write value</param>
 * <param name="ulBitSize" type="IN" range="[0,VALID_BITSIZE]">Bits to write</param>
 * <param name="ulBitOffset" type="IN" range="[0,VALID_BITOFFSET]">Bitoffset of the parameter value</param>
 * <parampseudo name="bSafetyMode" type="IN" range="[0,1]">According to SIL2 operation mode this function may not be called</parampseudo>
 * <parampseudo name="bException" type="OUT">SIL2 Runtime: Exception is thrown if not in DebugMode</parampseudo>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrWriteParameter', `(RTS_UI32 ulModuleType, RTS_UI32 ulInstance, RTS_UI32 ulParameterId, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)')

/**
 * <description>
 * <p>Return the registered driver interface of a connector</p>
 * </description>
 * <param name="pConnector" type="IN" range="[NULL,VALID_CONNECTOR_CDRIVER, VALID_CONNECTOR_IECDRIVER]">Pointer to connector</param>
 * <parampseudo name="bIecDriver_out" type="OUT">For ext function: If the instance is an IEC or C driver</parampseudo>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to IBase interface</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">driver interface successfully retrieved</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">driver interface not retrieved</errorcode>
 */
DEF_ITF_API(`IBase *', `CDECL', `IoMgrConfigGetDriver', `(IoConfigConnector *pConnector, RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Interface to get the connector of the driver specified by IBase interface</p>
 * <p>Note: This function is optional and not supported by CmpIoMgrEmbedded!</p>
 * </description>
 * <param name="pIBase" type="IN" range="[NULL,VALID_IBASE]">Pointer to IBase interface of the driver</param>
 * <param name="nIndex" type="IN" range="[RTS_RANGE_OF_INT]">Index of the connector</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to connector</result>
 */
DEF_ITF_API(`IoConfigConnector *', `CDECL', `IoMgrConfigGetConnectorByDriver', `(IBase *pIBase, int nIndex, RTS_RESULT *pResult)')

/**
 * <description>
 * <p>Copy an Input from the Device to some local memory and swap to little endian if necessary.</p>
 * </description>
 * <param name="pChannel" type="IN" range="[NULL,VALID_COPINPUT_CHANNELMAP_1,VALID_COPINPUT_CHANNELMAP_2]">Pointer to one Channel Mapping</param>
 * <param name="pAddress" type="IN" range="[NULL,VALID_COPYINPUT_SRC]">Pointer to the Source Address</param>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrCopyInputLE', `(IoConfigChannelMap *pChannel, char *pAddress)')

/**
 * <description>
 * <p>Copy an Input from the Device to some local memory and swap to big endian if necessary</p>
 * </description>
 * <param name="pChannel" type="IN" range="[NULL,VALID_COPINPUT_CHANNELMAP_1,VALID_COPINPUT_CHANNELMAP_2]">Pointer to one Channel Mapping</param>
 * <param name="pAddress" type="IN" range="[NULL,VALID_COPYINPUT_SRC]">Pointer to the Source Address</param>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrCopyInputBE', `(IoConfigChannelMap *pChannel, char *pAddress)')

/**
 * <description>
 * <p>Copy an Output from local memory to the Device and swap to little endian if necessary</p>
 * </description>
 * <param name="pChannel" type="IN" range="[NULL,VALID_COPINPUT_CHANNELMAP_1,VALID_COPINPUT_CHANNELMAP_2]">Pointer to one Channel Mapping</param>
 * <param name="pAddress" type="IN" range="[NULL,VALID_COPYOUTPUT_DST]">Pointer to the Destination Address</param>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrCopyOutputLE', `(IoConfigChannelMap *pChannel, char *pAddress)')

/**
 * <description>
 * <p>Copy an Output from local memory to the Device and swap to big endian if necessary</p>
 * </description>
 * <param name="pChannel" type="IN" range="[NULL,VALID_COPINPUT_CHANNELMAP_1,VALID_COPINPUT_CHANNELMAP_2]">Pointer to one Channel Mapping</param>
 * <param name="pAddress" type="IN" range="[NULL,VALID_COPYOUTPUT_DST]">Pointer to the DestinationAddress</param>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `IoMgrCopyOutputBE', `(IoConfigChannelMap *pChannel, char *pAddress)')

#ifdef __cplusplus
}
#endif
