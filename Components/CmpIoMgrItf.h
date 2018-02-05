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
 * .             _,.--''''     ''--..__
 * .          ,,          ___            --.._
 * .       _,i__       ,-ii_  `'--.._         `-..
 * .     ,;'   -._,;''   -._      `-.._       `-._
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
 * .       .     |
 * .   ,-./       \,-.
 * .  ( C )       ( D )
 * .   -         -
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


	
	
#ifndef _CMPIOMGRITF_H_
#define _CMPIOMGRITF_H_

#include "CmpStd.h"

 

 




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
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

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

void CDECL CDECL_EXT iomgrconfiggetconnector(iomgrconfiggetconnector_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRCONFIGGETCONNECTOR_IEC) (iomgrconfiggetconnector_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETCONNECTOR_NOTIMPLEMENTED)
	#define USE_iomgrconfiggetconnector
	#define EXT_iomgrconfiggetconnector
	#define GET_iomgrconfiggetconnector(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrconfiggetconnector(p0) 
	#define CHK_iomgrconfiggetconnector  FALSE
	#define EXP_iomgrconfiggetconnector  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrconfiggetconnector
	#define EXT_iomgrconfiggetconnector
	#define GET_iomgrconfiggetconnector(fl)  CAL_CMGETAPI( "iomgrconfiggetconnector" ) 
	#define CAL_iomgrconfiggetconnector  iomgrconfiggetconnector
	#define CHK_iomgrconfiggetconnector  TRUE
	#define EXP_iomgrconfiggetconnector  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetconnector", (RTS_UINTPTR)iomgrconfiggetconnector, 1, RTSITF_GET_SIGNATURE(0, 0xB093BAED), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrconfiggetconnector
	#define EXT_iomgrconfiggetconnector
	#define GET_iomgrconfiggetconnector(fl)  CAL_CMGETAPI( "iomgrconfiggetconnector" ) 
	#define CAL_iomgrconfiggetconnector  iomgrconfiggetconnector
	#define CHK_iomgrconfiggetconnector  TRUE
	#define EXP_iomgrconfiggetconnector  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetconnector", (RTS_UINTPTR)iomgrconfiggetconnector, 1, RTSITF_GET_SIGNATURE(0, 0xB093BAED), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrconfiggetconnector
	#define EXT_CmpIoMgriomgrconfiggetconnector
	#define GET_CmpIoMgriomgrconfiggetconnector  ERR_OK
	#define CAL_CmpIoMgriomgrconfiggetconnector  iomgrconfiggetconnector
	#define CHK_CmpIoMgriomgrconfiggetconnector  TRUE
	#define EXP_CmpIoMgriomgrconfiggetconnector  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetconnector", (RTS_UINTPTR)iomgrconfiggetconnector, 1, RTSITF_GET_SIGNATURE(0, 0xB093BAED), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrconfiggetconnector
	#define EXT_iomgrconfiggetconnector
	#define GET_iomgrconfiggetconnector(fl)  CAL_CMGETAPI( "iomgrconfiggetconnector" ) 
	#define CAL_iomgrconfiggetconnector  iomgrconfiggetconnector
	#define CHK_iomgrconfiggetconnector  TRUE
	#define EXP_iomgrconfiggetconnector  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetconnector", (RTS_UINTPTR)iomgrconfiggetconnector, 1, RTSITF_GET_SIGNATURE(0, 0xB093BAED), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrconfiggetconnector  PFIOMGRCONFIGGETCONNECTOR_IEC pfiomgrconfiggetconnector;
	#define EXT_iomgrconfiggetconnector  extern PFIOMGRCONFIGGETCONNECTOR_IEC pfiomgrconfiggetconnector;
	#define GET_iomgrconfiggetconnector(fl)  s_pfCMGetAPI2( "iomgrconfiggetconnector", (RTS_VOID_FCTPTR *)&pfiomgrconfiggetconnector, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xB093BAED), 0x03050800)
	#define CAL_iomgrconfiggetconnector  pfiomgrconfiggetconnector
	#define CHK_iomgrconfiggetconnector  (pfiomgrconfiggetconnector != NULL)
	#define EXP_iomgrconfiggetconnector   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetconnector", (RTS_UINTPTR)iomgrconfiggetconnector, 1, RTSITF_GET_SIGNATURE(0, 0xB093BAED), 0x03050800) 
#endif


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

void CDECL CDECL_EXT iomgrconfiggetconnectorbydriver(iomgrconfiggetconnectorbydriver_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRCONFIGGETCONNECTORBYDRIVER_IEC) (iomgrconfiggetconnectorbydriver_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETCONNECTORBYDRIVER_NOTIMPLEMENTED)
	#define USE_iomgrconfiggetconnectorbydriver
	#define EXT_iomgrconfiggetconnectorbydriver
	#define GET_iomgrconfiggetconnectorbydriver(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrconfiggetconnectorbydriver(p0) 
	#define CHK_iomgrconfiggetconnectorbydriver  FALSE
	#define EXP_iomgrconfiggetconnectorbydriver  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrconfiggetconnectorbydriver
	#define EXT_iomgrconfiggetconnectorbydriver
	#define GET_iomgrconfiggetconnectorbydriver(fl)  CAL_CMGETAPI( "iomgrconfiggetconnectorbydriver" ) 
	#define CAL_iomgrconfiggetconnectorbydriver  iomgrconfiggetconnectorbydriver
	#define CHK_iomgrconfiggetconnectorbydriver  TRUE
	#define EXP_iomgrconfiggetconnectorbydriver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetconnectorbydriver", (RTS_UINTPTR)iomgrconfiggetconnectorbydriver, 1, RTSITF_GET_SIGNATURE(0, 0x076B9D1E), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrconfiggetconnectorbydriver
	#define EXT_iomgrconfiggetconnectorbydriver
	#define GET_iomgrconfiggetconnectorbydriver(fl)  CAL_CMGETAPI( "iomgrconfiggetconnectorbydriver" ) 
	#define CAL_iomgrconfiggetconnectorbydriver  iomgrconfiggetconnectorbydriver
	#define CHK_iomgrconfiggetconnectorbydriver  TRUE
	#define EXP_iomgrconfiggetconnectorbydriver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetconnectorbydriver", (RTS_UINTPTR)iomgrconfiggetconnectorbydriver, 1, RTSITF_GET_SIGNATURE(0, 0x076B9D1E), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrconfiggetconnectorbydriver
	#define EXT_CmpIoMgriomgrconfiggetconnectorbydriver
	#define GET_CmpIoMgriomgrconfiggetconnectorbydriver  ERR_OK
	#define CAL_CmpIoMgriomgrconfiggetconnectorbydriver  iomgrconfiggetconnectorbydriver
	#define CHK_CmpIoMgriomgrconfiggetconnectorbydriver  TRUE
	#define EXP_CmpIoMgriomgrconfiggetconnectorbydriver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetconnectorbydriver", (RTS_UINTPTR)iomgrconfiggetconnectorbydriver, 1, RTSITF_GET_SIGNATURE(0, 0x076B9D1E), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrconfiggetconnectorbydriver
	#define EXT_iomgrconfiggetconnectorbydriver
	#define GET_iomgrconfiggetconnectorbydriver(fl)  CAL_CMGETAPI( "iomgrconfiggetconnectorbydriver" ) 
	#define CAL_iomgrconfiggetconnectorbydriver  iomgrconfiggetconnectorbydriver
	#define CHK_iomgrconfiggetconnectorbydriver  TRUE
	#define EXP_iomgrconfiggetconnectorbydriver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetconnectorbydriver", (RTS_UINTPTR)iomgrconfiggetconnectorbydriver, 1, RTSITF_GET_SIGNATURE(0, 0x076B9D1E), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrconfiggetconnectorbydriver  PFIOMGRCONFIGGETCONNECTORBYDRIVER_IEC pfiomgrconfiggetconnectorbydriver;
	#define EXT_iomgrconfiggetconnectorbydriver  extern PFIOMGRCONFIGGETCONNECTORBYDRIVER_IEC pfiomgrconfiggetconnectorbydriver;
	#define GET_iomgrconfiggetconnectorbydriver(fl)  s_pfCMGetAPI2( "iomgrconfiggetconnectorbydriver", (RTS_VOID_FCTPTR *)&pfiomgrconfiggetconnectorbydriver, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x076B9D1E), 0x03050800)
	#define CAL_iomgrconfiggetconnectorbydriver  pfiomgrconfiggetconnectorbydriver
	#define CHK_iomgrconfiggetconnectorbydriver  (pfiomgrconfiggetconnectorbydriver != NULL)
	#define EXP_iomgrconfiggetconnectorbydriver   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetconnectorbydriver", (RTS_UINTPTR)iomgrconfiggetconnectorbydriver, 1, RTSITF_GET_SIGNATURE(0, 0x076B9D1E), 0x03050800) 
#endif


/**
 * <description>iomgrconfiggetconnectorlist</description>
 */
typedef struct tagiomgrconfiggetconnectorlist_struct
{
	IoConfigConnector **ppConnectorList;	/* VAR_INPUT */	
	RTS_IEC_DINT *pnCount;				/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrConfigGetConnectorList;	/* VAR_OUTPUT */	
} iomgrconfiggetconnectorlist_struct;

void CDECL CDECL_EXT iomgrconfiggetconnectorlist(iomgrconfiggetconnectorlist_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRCONFIGGETCONNECTORLIST_IEC) (iomgrconfiggetconnectorlist_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETCONNECTORLIST_NOTIMPLEMENTED)
	#define USE_iomgrconfiggetconnectorlist
	#define EXT_iomgrconfiggetconnectorlist
	#define GET_iomgrconfiggetconnectorlist(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrconfiggetconnectorlist(p0) 
	#define CHK_iomgrconfiggetconnectorlist  FALSE
	#define EXP_iomgrconfiggetconnectorlist  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrconfiggetconnectorlist
	#define EXT_iomgrconfiggetconnectorlist
	#define GET_iomgrconfiggetconnectorlist(fl)  CAL_CMGETAPI( "iomgrconfiggetconnectorlist" ) 
	#define CAL_iomgrconfiggetconnectorlist  iomgrconfiggetconnectorlist
	#define CHK_iomgrconfiggetconnectorlist  TRUE
	#define EXP_iomgrconfiggetconnectorlist  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetconnectorlist", (RTS_UINTPTR)iomgrconfiggetconnectorlist, 1, RTSITF_GET_SIGNATURE(0, 0x6E3F45DC), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrconfiggetconnectorlist
	#define EXT_iomgrconfiggetconnectorlist
	#define GET_iomgrconfiggetconnectorlist(fl)  CAL_CMGETAPI( "iomgrconfiggetconnectorlist" ) 
	#define CAL_iomgrconfiggetconnectorlist  iomgrconfiggetconnectorlist
	#define CHK_iomgrconfiggetconnectorlist  TRUE
	#define EXP_iomgrconfiggetconnectorlist  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetconnectorlist", (RTS_UINTPTR)iomgrconfiggetconnectorlist, 1, RTSITF_GET_SIGNATURE(0, 0x6E3F45DC), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrconfiggetconnectorlist
	#define EXT_CmpIoMgriomgrconfiggetconnectorlist
	#define GET_CmpIoMgriomgrconfiggetconnectorlist  ERR_OK
	#define CAL_CmpIoMgriomgrconfiggetconnectorlist  iomgrconfiggetconnectorlist
	#define CHK_CmpIoMgriomgrconfiggetconnectorlist  TRUE
	#define EXP_CmpIoMgriomgrconfiggetconnectorlist  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetconnectorlist", (RTS_UINTPTR)iomgrconfiggetconnectorlist, 1, RTSITF_GET_SIGNATURE(0, 0x6E3F45DC), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrconfiggetconnectorlist
	#define EXT_iomgrconfiggetconnectorlist
	#define GET_iomgrconfiggetconnectorlist(fl)  CAL_CMGETAPI( "iomgrconfiggetconnectorlist" ) 
	#define CAL_iomgrconfiggetconnectorlist  iomgrconfiggetconnectorlist
	#define CHK_iomgrconfiggetconnectorlist  TRUE
	#define EXP_iomgrconfiggetconnectorlist  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetconnectorlist", (RTS_UINTPTR)iomgrconfiggetconnectorlist, 1, RTSITF_GET_SIGNATURE(0, 0x6E3F45DC), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrconfiggetconnectorlist  PFIOMGRCONFIGGETCONNECTORLIST_IEC pfiomgrconfiggetconnectorlist;
	#define EXT_iomgrconfiggetconnectorlist  extern PFIOMGRCONFIGGETCONNECTORLIST_IEC pfiomgrconfiggetconnectorlist;
	#define GET_iomgrconfiggetconnectorlist(fl)  s_pfCMGetAPI2( "iomgrconfiggetconnectorlist", (RTS_VOID_FCTPTR *)&pfiomgrconfiggetconnectorlist, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x6E3F45DC), 0x03050800)
	#define CAL_iomgrconfiggetconnectorlist  pfiomgrconfiggetconnectorlist
	#define CHK_iomgrconfiggetconnectorlist  (pfiomgrconfiggetconnectorlist != NULL)
	#define EXP_iomgrconfiggetconnectorlist   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetconnectorlist", (RTS_UINTPTR)iomgrconfiggetconnectorlist, 1, RTSITF_GET_SIGNATURE(0, 0x6E3F45DC), 0x03050800) 
#endif


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

void CDECL CDECL_EXT iomgrconfiggetdriver(iomgrconfiggetdriver_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRCONFIGGETDRIVER_IEC) (iomgrconfiggetdriver_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETDRIVER_NOTIMPLEMENTED)
	#define USE_iomgrconfiggetdriver
	#define EXT_iomgrconfiggetdriver
	#define GET_iomgrconfiggetdriver(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrconfiggetdriver(p0) 
	#define CHK_iomgrconfiggetdriver  FALSE
	#define EXP_iomgrconfiggetdriver  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrconfiggetdriver
	#define EXT_iomgrconfiggetdriver
	#define GET_iomgrconfiggetdriver(fl)  CAL_CMGETAPI( "iomgrconfiggetdriver" ) 
	#define CAL_iomgrconfiggetdriver  iomgrconfiggetdriver
	#define CHK_iomgrconfiggetdriver  TRUE
	#define EXP_iomgrconfiggetdriver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetdriver", (RTS_UINTPTR)iomgrconfiggetdriver, 1, RTSITF_GET_SIGNATURE(0, 0xA6C591A7), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrconfiggetdriver
	#define EXT_iomgrconfiggetdriver
	#define GET_iomgrconfiggetdriver(fl)  CAL_CMGETAPI( "iomgrconfiggetdriver" ) 
	#define CAL_iomgrconfiggetdriver  iomgrconfiggetdriver
	#define CHK_iomgrconfiggetdriver  TRUE
	#define EXP_iomgrconfiggetdriver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetdriver", (RTS_UINTPTR)iomgrconfiggetdriver, 1, RTSITF_GET_SIGNATURE(0, 0xA6C591A7), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrconfiggetdriver
	#define EXT_CmpIoMgriomgrconfiggetdriver
	#define GET_CmpIoMgriomgrconfiggetdriver  ERR_OK
	#define CAL_CmpIoMgriomgrconfiggetdriver  iomgrconfiggetdriver
	#define CHK_CmpIoMgriomgrconfiggetdriver  TRUE
	#define EXP_CmpIoMgriomgrconfiggetdriver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetdriver", (RTS_UINTPTR)iomgrconfiggetdriver, 1, RTSITF_GET_SIGNATURE(0, 0xA6C591A7), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrconfiggetdriver
	#define EXT_iomgrconfiggetdriver
	#define GET_iomgrconfiggetdriver(fl)  CAL_CMGETAPI( "iomgrconfiggetdriver" ) 
	#define CAL_iomgrconfiggetdriver  iomgrconfiggetdriver
	#define CHK_iomgrconfiggetdriver  TRUE
	#define EXP_iomgrconfiggetdriver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetdriver", (RTS_UINTPTR)iomgrconfiggetdriver, 1, RTSITF_GET_SIGNATURE(0, 0xA6C591A7), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrconfiggetdriver  PFIOMGRCONFIGGETDRIVER_IEC pfiomgrconfiggetdriver;
	#define EXT_iomgrconfiggetdriver  extern PFIOMGRCONFIGGETDRIVER_IEC pfiomgrconfiggetdriver;
	#define GET_iomgrconfiggetdriver(fl)  s_pfCMGetAPI2( "iomgrconfiggetdriver", (RTS_VOID_FCTPTR *)&pfiomgrconfiggetdriver, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA6C591A7), 0x03050800)
	#define CAL_iomgrconfiggetdriver  pfiomgrconfiggetdriver
	#define CHK_iomgrconfiggetdriver  (pfiomgrconfiggetdriver != NULL)
	#define EXP_iomgrconfiggetdriver   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetdriver", (RTS_UINTPTR)iomgrconfiggetdriver, 1, RTSITF_GET_SIGNATURE(0, 0xA6C591A7), 0x03050800) 
#endif


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

void CDECL CDECL_EXT iomgrconfiggetfirstchild(iomgrconfiggetfirstchild_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRCONFIGGETFIRSTCHILD_IEC) (iomgrconfiggetfirstchild_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETFIRSTCHILD_NOTIMPLEMENTED)
	#define USE_iomgrconfiggetfirstchild
	#define EXT_iomgrconfiggetfirstchild
	#define GET_iomgrconfiggetfirstchild(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrconfiggetfirstchild(p0) 
	#define CHK_iomgrconfiggetfirstchild  FALSE
	#define EXP_iomgrconfiggetfirstchild  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrconfiggetfirstchild
	#define EXT_iomgrconfiggetfirstchild
	#define GET_iomgrconfiggetfirstchild(fl)  CAL_CMGETAPI( "iomgrconfiggetfirstchild" ) 
	#define CAL_iomgrconfiggetfirstchild  iomgrconfiggetfirstchild
	#define CHK_iomgrconfiggetfirstchild  TRUE
	#define EXP_iomgrconfiggetfirstchild  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetfirstchild", (RTS_UINTPTR)iomgrconfiggetfirstchild, 1, RTSITF_GET_SIGNATURE(0, 0xB89B6273), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrconfiggetfirstchild
	#define EXT_iomgrconfiggetfirstchild
	#define GET_iomgrconfiggetfirstchild(fl)  CAL_CMGETAPI( "iomgrconfiggetfirstchild" ) 
	#define CAL_iomgrconfiggetfirstchild  iomgrconfiggetfirstchild
	#define CHK_iomgrconfiggetfirstchild  TRUE
	#define EXP_iomgrconfiggetfirstchild  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetfirstchild", (RTS_UINTPTR)iomgrconfiggetfirstchild, 1, RTSITF_GET_SIGNATURE(0, 0xB89B6273), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrconfiggetfirstchild
	#define EXT_CmpIoMgriomgrconfiggetfirstchild
	#define GET_CmpIoMgriomgrconfiggetfirstchild  ERR_OK
	#define CAL_CmpIoMgriomgrconfiggetfirstchild  iomgrconfiggetfirstchild
	#define CHK_CmpIoMgriomgrconfiggetfirstchild  TRUE
	#define EXP_CmpIoMgriomgrconfiggetfirstchild  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetfirstchild", (RTS_UINTPTR)iomgrconfiggetfirstchild, 1, RTSITF_GET_SIGNATURE(0, 0xB89B6273), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrconfiggetfirstchild
	#define EXT_iomgrconfiggetfirstchild
	#define GET_iomgrconfiggetfirstchild(fl)  CAL_CMGETAPI( "iomgrconfiggetfirstchild" ) 
	#define CAL_iomgrconfiggetfirstchild  iomgrconfiggetfirstchild
	#define CHK_iomgrconfiggetfirstchild  TRUE
	#define EXP_iomgrconfiggetfirstchild  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetfirstchild", (RTS_UINTPTR)iomgrconfiggetfirstchild, 1, RTSITF_GET_SIGNATURE(0, 0xB89B6273), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrconfiggetfirstchild  PFIOMGRCONFIGGETFIRSTCHILD_IEC pfiomgrconfiggetfirstchild;
	#define EXT_iomgrconfiggetfirstchild  extern PFIOMGRCONFIGGETFIRSTCHILD_IEC pfiomgrconfiggetfirstchild;
	#define GET_iomgrconfiggetfirstchild(fl)  s_pfCMGetAPI2( "iomgrconfiggetfirstchild", (RTS_VOID_FCTPTR *)&pfiomgrconfiggetfirstchild, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xB89B6273), 0x03050800)
	#define CAL_iomgrconfiggetfirstchild  pfiomgrconfiggetfirstchild
	#define CHK_iomgrconfiggetfirstchild  (pfiomgrconfiggetfirstchild != NULL)
	#define EXP_iomgrconfiggetfirstchild   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetfirstchild", (RTS_UINTPTR)iomgrconfiggetfirstchild, 1, RTSITF_GET_SIGNATURE(0, 0xB89B6273), 0x03050800) 
#endif


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

void CDECL CDECL_EXT iomgrconfiggetfirstconnector(iomgrconfiggetfirstconnector_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRCONFIGGETFIRSTCONNECTOR_IEC) (iomgrconfiggetfirstconnector_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETFIRSTCONNECTOR_NOTIMPLEMENTED)
	#define USE_iomgrconfiggetfirstconnector
	#define EXT_iomgrconfiggetfirstconnector
	#define GET_iomgrconfiggetfirstconnector(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrconfiggetfirstconnector(p0) 
	#define CHK_iomgrconfiggetfirstconnector  FALSE
	#define EXP_iomgrconfiggetfirstconnector  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrconfiggetfirstconnector
	#define EXT_iomgrconfiggetfirstconnector
	#define GET_iomgrconfiggetfirstconnector(fl)  CAL_CMGETAPI( "iomgrconfiggetfirstconnector" ) 
	#define CAL_iomgrconfiggetfirstconnector  iomgrconfiggetfirstconnector
	#define CHK_iomgrconfiggetfirstconnector  TRUE
	#define EXP_iomgrconfiggetfirstconnector  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetfirstconnector", (RTS_UINTPTR)iomgrconfiggetfirstconnector, 1, RTSITF_GET_SIGNATURE(0, 0x1AEDD2CA), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrconfiggetfirstconnector
	#define EXT_iomgrconfiggetfirstconnector
	#define GET_iomgrconfiggetfirstconnector(fl)  CAL_CMGETAPI( "iomgrconfiggetfirstconnector" ) 
	#define CAL_iomgrconfiggetfirstconnector  iomgrconfiggetfirstconnector
	#define CHK_iomgrconfiggetfirstconnector  TRUE
	#define EXP_iomgrconfiggetfirstconnector  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetfirstconnector", (RTS_UINTPTR)iomgrconfiggetfirstconnector, 1, RTSITF_GET_SIGNATURE(0, 0x1AEDD2CA), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrconfiggetfirstconnector
	#define EXT_CmpIoMgriomgrconfiggetfirstconnector
	#define GET_CmpIoMgriomgrconfiggetfirstconnector  ERR_OK
	#define CAL_CmpIoMgriomgrconfiggetfirstconnector  iomgrconfiggetfirstconnector
	#define CHK_CmpIoMgriomgrconfiggetfirstconnector  TRUE
	#define EXP_CmpIoMgriomgrconfiggetfirstconnector  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetfirstconnector", (RTS_UINTPTR)iomgrconfiggetfirstconnector, 1, RTSITF_GET_SIGNATURE(0, 0x1AEDD2CA), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrconfiggetfirstconnector
	#define EXT_iomgrconfiggetfirstconnector
	#define GET_iomgrconfiggetfirstconnector(fl)  CAL_CMGETAPI( "iomgrconfiggetfirstconnector" ) 
	#define CAL_iomgrconfiggetfirstconnector  iomgrconfiggetfirstconnector
	#define CHK_iomgrconfiggetfirstconnector  TRUE
	#define EXP_iomgrconfiggetfirstconnector  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetfirstconnector", (RTS_UINTPTR)iomgrconfiggetfirstconnector, 1, RTSITF_GET_SIGNATURE(0, 0x1AEDD2CA), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrconfiggetfirstconnector  PFIOMGRCONFIGGETFIRSTCONNECTOR_IEC pfiomgrconfiggetfirstconnector;
	#define EXT_iomgrconfiggetfirstconnector  extern PFIOMGRCONFIGGETFIRSTCONNECTOR_IEC pfiomgrconfiggetfirstconnector;
	#define GET_iomgrconfiggetfirstconnector(fl)  s_pfCMGetAPI2( "iomgrconfiggetfirstconnector", (RTS_VOID_FCTPTR *)&pfiomgrconfiggetfirstconnector, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x1AEDD2CA), 0x03050800)
	#define CAL_iomgrconfiggetfirstconnector  pfiomgrconfiggetfirstconnector
	#define CHK_iomgrconfiggetfirstconnector  (pfiomgrconfiggetfirstconnector != NULL)
	#define EXP_iomgrconfiggetfirstconnector   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetfirstconnector", (RTS_UINTPTR)iomgrconfiggetfirstconnector, 1, RTSITF_GET_SIGNATURE(0, 0x1AEDD2CA), 0x03050800) 
#endif


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

void CDECL CDECL_EXT iomgrconfiggetnextchild(iomgrconfiggetnextchild_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRCONFIGGETNEXTCHILD_IEC) (iomgrconfiggetnextchild_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETNEXTCHILD_NOTIMPLEMENTED)
	#define USE_iomgrconfiggetnextchild
	#define EXT_iomgrconfiggetnextchild
	#define GET_iomgrconfiggetnextchild(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrconfiggetnextchild(p0) 
	#define CHK_iomgrconfiggetnextchild  FALSE
	#define EXP_iomgrconfiggetnextchild  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrconfiggetnextchild
	#define EXT_iomgrconfiggetnextchild
	#define GET_iomgrconfiggetnextchild(fl)  CAL_CMGETAPI( "iomgrconfiggetnextchild" ) 
	#define CAL_iomgrconfiggetnextchild  iomgrconfiggetnextchild
	#define CHK_iomgrconfiggetnextchild  TRUE
	#define EXP_iomgrconfiggetnextchild  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetnextchild", (RTS_UINTPTR)iomgrconfiggetnextchild, 1, RTSITF_GET_SIGNATURE(0, 0x2F87EBF8), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrconfiggetnextchild
	#define EXT_iomgrconfiggetnextchild
	#define GET_iomgrconfiggetnextchild(fl)  CAL_CMGETAPI( "iomgrconfiggetnextchild" ) 
	#define CAL_iomgrconfiggetnextchild  iomgrconfiggetnextchild
	#define CHK_iomgrconfiggetnextchild  TRUE
	#define EXP_iomgrconfiggetnextchild  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetnextchild", (RTS_UINTPTR)iomgrconfiggetnextchild, 1, RTSITF_GET_SIGNATURE(0, 0x2F87EBF8), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrconfiggetnextchild
	#define EXT_CmpIoMgriomgrconfiggetnextchild
	#define GET_CmpIoMgriomgrconfiggetnextchild  ERR_OK
	#define CAL_CmpIoMgriomgrconfiggetnextchild  iomgrconfiggetnextchild
	#define CHK_CmpIoMgriomgrconfiggetnextchild  TRUE
	#define EXP_CmpIoMgriomgrconfiggetnextchild  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetnextchild", (RTS_UINTPTR)iomgrconfiggetnextchild, 1, RTSITF_GET_SIGNATURE(0, 0x2F87EBF8), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrconfiggetnextchild
	#define EXT_iomgrconfiggetnextchild
	#define GET_iomgrconfiggetnextchild(fl)  CAL_CMGETAPI( "iomgrconfiggetnextchild" ) 
	#define CAL_iomgrconfiggetnextchild  iomgrconfiggetnextchild
	#define CHK_iomgrconfiggetnextchild  TRUE
	#define EXP_iomgrconfiggetnextchild  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetnextchild", (RTS_UINTPTR)iomgrconfiggetnextchild, 1, RTSITF_GET_SIGNATURE(0, 0x2F87EBF8), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrconfiggetnextchild  PFIOMGRCONFIGGETNEXTCHILD_IEC pfiomgrconfiggetnextchild;
	#define EXT_iomgrconfiggetnextchild  extern PFIOMGRCONFIGGETNEXTCHILD_IEC pfiomgrconfiggetnextchild;
	#define GET_iomgrconfiggetnextchild(fl)  s_pfCMGetAPI2( "iomgrconfiggetnextchild", (RTS_VOID_FCTPTR *)&pfiomgrconfiggetnextchild, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x2F87EBF8), 0x03050800)
	#define CAL_iomgrconfiggetnextchild  pfiomgrconfiggetnextchild
	#define CHK_iomgrconfiggetnextchild  (pfiomgrconfiggetnextchild != NULL)
	#define EXP_iomgrconfiggetnextchild   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetnextchild", (RTS_UINTPTR)iomgrconfiggetnextchild, 1, RTSITF_GET_SIGNATURE(0, 0x2F87EBF8), 0x03050800) 
#endif


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

void CDECL CDECL_EXT iomgrconfiggetnextconnector(iomgrconfiggetnextconnector_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRCONFIGGETNEXTCONNECTOR_IEC) (iomgrconfiggetnextconnector_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETNEXTCONNECTOR_NOTIMPLEMENTED)
	#define USE_iomgrconfiggetnextconnector
	#define EXT_iomgrconfiggetnextconnector
	#define GET_iomgrconfiggetnextconnector(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrconfiggetnextconnector(p0) 
	#define CHK_iomgrconfiggetnextconnector  FALSE
	#define EXP_iomgrconfiggetnextconnector  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrconfiggetnextconnector
	#define EXT_iomgrconfiggetnextconnector
	#define GET_iomgrconfiggetnextconnector(fl)  CAL_CMGETAPI( "iomgrconfiggetnextconnector" ) 
	#define CAL_iomgrconfiggetnextconnector  iomgrconfiggetnextconnector
	#define CHK_iomgrconfiggetnextconnector  TRUE
	#define EXP_iomgrconfiggetnextconnector  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetnextconnector", (RTS_UINTPTR)iomgrconfiggetnextconnector, 1, RTSITF_GET_SIGNATURE(0, 0xA5BCF071), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrconfiggetnextconnector
	#define EXT_iomgrconfiggetnextconnector
	#define GET_iomgrconfiggetnextconnector(fl)  CAL_CMGETAPI( "iomgrconfiggetnextconnector" ) 
	#define CAL_iomgrconfiggetnextconnector  iomgrconfiggetnextconnector
	#define CHK_iomgrconfiggetnextconnector  TRUE
	#define EXP_iomgrconfiggetnextconnector  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetnextconnector", (RTS_UINTPTR)iomgrconfiggetnextconnector, 1, RTSITF_GET_SIGNATURE(0, 0xA5BCF071), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrconfiggetnextconnector
	#define EXT_CmpIoMgriomgrconfiggetnextconnector
	#define GET_CmpIoMgriomgrconfiggetnextconnector  ERR_OK
	#define CAL_CmpIoMgriomgrconfiggetnextconnector  iomgrconfiggetnextconnector
	#define CHK_CmpIoMgriomgrconfiggetnextconnector  TRUE
	#define EXP_CmpIoMgriomgrconfiggetnextconnector  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetnextconnector", (RTS_UINTPTR)iomgrconfiggetnextconnector, 1, RTSITF_GET_SIGNATURE(0, 0xA5BCF071), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrconfiggetnextconnector
	#define EXT_iomgrconfiggetnextconnector
	#define GET_iomgrconfiggetnextconnector(fl)  CAL_CMGETAPI( "iomgrconfiggetnextconnector" ) 
	#define CAL_iomgrconfiggetnextconnector  iomgrconfiggetnextconnector
	#define CHK_iomgrconfiggetnextconnector  TRUE
	#define EXP_iomgrconfiggetnextconnector  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetnextconnector", (RTS_UINTPTR)iomgrconfiggetnextconnector, 1, RTSITF_GET_SIGNATURE(0, 0xA5BCF071), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrconfiggetnextconnector  PFIOMGRCONFIGGETNEXTCONNECTOR_IEC pfiomgrconfiggetnextconnector;
	#define EXT_iomgrconfiggetnextconnector  extern PFIOMGRCONFIGGETNEXTCONNECTOR_IEC pfiomgrconfiggetnextconnector;
	#define GET_iomgrconfiggetnextconnector(fl)  s_pfCMGetAPI2( "iomgrconfiggetnextconnector", (RTS_VOID_FCTPTR *)&pfiomgrconfiggetnextconnector, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA5BCF071), 0x03050800)
	#define CAL_iomgrconfiggetnextconnector  pfiomgrconfiggetnextconnector
	#define CHK_iomgrconfiggetnextconnector  (pfiomgrconfiggetnextconnector != NULL)
	#define EXP_iomgrconfiggetnextconnector   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetnextconnector", (RTS_UINTPTR)iomgrconfiggetnextconnector, 1, RTSITF_GET_SIGNATURE(0, 0xA5BCF071), 0x03050800) 
#endif


/**
 * <description>iomgrconfiggetparameter</description>
 */
typedef struct tagiomgrconfiggetparameter_struct
{
	IoConfigConnector *pConnector;		/* VAR_INPUT */	
	RTS_IEC_DWORD dwParameterId;		/* VAR_INPUT */	
	IoConfigParameter *IoMgrConfigGetParameter;	/* VAR_OUTPUT */	
} iomgrconfiggetparameter_struct;

void CDECL CDECL_EXT iomgrconfiggetparameter(iomgrconfiggetparameter_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRCONFIGGETPARAMETER_IEC) (iomgrconfiggetparameter_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETPARAMETER_NOTIMPLEMENTED)
	#define USE_iomgrconfiggetparameter
	#define EXT_iomgrconfiggetparameter
	#define GET_iomgrconfiggetparameter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrconfiggetparameter(p0) 
	#define CHK_iomgrconfiggetparameter  FALSE
	#define EXP_iomgrconfiggetparameter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrconfiggetparameter
	#define EXT_iomgrconfiggetparameter
	#define GET_iomgrconfiggetparameter(fl)  CAL_CMGETAPI( "iomgrconfiggetparameter" ) 
	#define CAL_iomgrconfiggetparameter  iomgrconfiggetparameter
	#define CHK_iomgrconfiggetparameter  TRUE
	#define EXP_iomgrconfiggetparameter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparameter", (RTS_UINTPTR)iomgrconfiggetparameter, 1, RTSITF_GET_SIGNATURE(0, 0xC7A23B05), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrconfiggetparameter
	#define EXT_iomgrconfiggetparameter
	#define GET_iomgrconfiggetparameter(fl)  CAL_CMGETAPI( "iomgrconfiggetparameter" ) 
	#define CAL_iomgrconfiggetparameter  iomgrconfiggetparameter
	#define CHK_iomgrconfiggetparameter  TRUE
	#define EXP_iomgrconfiggetparameter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparameter", (RTS_UINTPTR)iomgrconfiggetparameter, 1, RTSITF_GET_SIGNATURE(0, 0xC7A23B05), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrconfiggetparameter
	#define EXT_CmpIoMgriomgrconfiggetparameter
	#define GET_CmpIoMgriomgrconfiggetparameter  ERR_OK
	#define CAL_CmpIoMgriomgrconfiggetparameter  iomgrconfiggetparameter
	#define CHK_CmpIoMgriomgrconfiggetparameter  TRUE
	#define EXP_CmpIoMgriomgrconfiggetparameter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparameter", (RTS_UINTPTR)iomgrconfiggetparameter, 1, RTSITF_GET_SIGNATURE(0, 0xC7A23B05), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrconfiggetparameter
	#define EXT_iomgrconfiggetparameter
	#define GET_iomgrconfiggetparameter(fl)  CAL_CMGETAPI( "iomgrconfiggetparameter" ) 
	#define CAL_iomgrconfiggetparameter  iomgrconfiggetparameter
	#define CHK_iomgrconfiggetparameter  TRUE
	#define EXP_iomgrconfiggetparameter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparameter", (RTS_UINTPTR)iomgrconfiggetparameter, 1, RTSITF_GET_SIGNATURE(0, 0xC7A23B05), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrconfiggetparameter  PFIOMGRCONFIGGETPARAMETER_IEC pfiomgrconfiggetparameter;
	#define EXT_iomgrconfiggetparameter  extern PFIOMGRCONFIGGETPARAMETER_IEC pfiomgrconfiggetparameter;
	#define GET_iomgrconfiggetparameter(fl)  s_pfCMGetAPI2( "iomgrconfiggetparameter", (RTS_VOID_FCTPTR *)&pfiomgrconfiggetparameter, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xC7A23B05), 0x03050800)
	#define CAL_iomgrconfiggetparameter  pfiomgrconfiggetparameter
	#define CHK_iomgrconfiggetparameter  (pfiomgrconfiggetparameter != NULL)
	#define EXP_iomgrconfiggetparameter   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparameter", (RTS_UINTPTR)iomgrconfiggetparameter, 1, RTSITF_GET_SIGNATURE(0, 0xC7A23B05), 0x03050800) 
#endif


/**
 * <description>iomgrconfiggetparametervaluebyte</description>
 */
typedef struct tagiomgrconfiggetparametervaluebyte_struct
{
	IoConfigParameter *pParameter;		/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_BYTE IoMgrConfigGetParameterValueByte;	/* VAR_OUTPUT */	
} iomgrconfiggetparametervaluebyte_struct;

void CDECL CDECL_EXT iomgrconfiggetparametervaluebyte(iomgrconfiggetparametervaluebyte_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRCONFIGGETPARAMETERVALUEBYTE_IEC) (iomgrconfiggetparametervaluebyte_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETPARAMETERVALUEBYTE_NOTIMPLEMENTED)
	#define USE_iomgrconfiggetparametervaluebyte
	#define EXT_iomgrconfiggetparametervaluebyte
	#define GET_iomgrconfiggetparametervaluebyte(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrconfiggetparametervaluebyte(p0) 
	#define CHK_iomgrconfiggetparametervaluebyte  FALSE
	#define EXP_iomgrconfiggetparametervaluebyte  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrconfiggetparametervaluebyte
	#define EXT_iomgrconfiggetparametervaluebyte
	#define GET_iomgrconfiggetparametervaluebyte(fl)  CAL_CMGETAPI( "iomgrconfiggetparametervaluebyte" ) 
	#define CAL_iomgrconfiggetparametervaluebyte  iomgrconfiggetparametervaluebyte
	#define CHK_iomgrconfiggetparametervaluebyte  TRUE
	#define EXP_iomgrconfiggetparametervaluebyte  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparametervaluebyte", (RTS_UINTPTR)iomgrconfiggetparametervaluebyte, 1, RTSITF_GET_SIGNATURE(0, 0xDE4EF488), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrconfiggetparametervaluebyte
	#define EXT_iomgrconfiggetparametervaluebyte
	#define GET_iomgrconfiggetparametervaluebyte(fl)  CAL_CMGETAPI( "iomgrconfiggetparametervaluebyte" ) 
	#define CAL_iomgrconfiggetparametervaluebyte  iomgrconfiggetparametervaluebyte
	#define CHK_iomgrconfiggetparametervaluebyte  TRUE
	#define EXP_iomgrconfiggetparametervaluebyte  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparametervaluebyte", (RTS_UINTPTR)iomgrconfiggetparametervaluebyte, 1, RTSITF_GET_SIGNATURE(0, 0xDE4EF488), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrconfiggetparametervaluebyte
	#define EXT_CmpIoMgriomgrconfiggetparametervaluebyte
	#define GET_CmpIoMgriomgrconfiggetparametervaluebyte  ERR_OK
	#define CAL_CmpIoMgriomgrconfiggetparametervaluebyte  iomgrconfiggetparametervaluebyte
	#define CHK_CmpIoMgriomgrconfiggetparametervaluebyte  TRUE
	#define EXP_CmpIoMgriomgrconfiggetparametervaluebyte  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparametervaluebyte", (RTS_UINTPTR)iomgrconfiggetparametervaluebyte, 1, RTSITF_GET_SIGNATURE(0, 0xDE4EF488), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrconfiggetparametervaluebyte
	#define EXT_iomgrconfiggetparametervaluebyte
	#define GET_iomgrconfiggetparametervaluebyte(fl)  CAL_CMGETAPI( "iomgrconfiggetparametervaluebyte" ) 
	#define CAL_iomgrconfiggetparametervaluebyte  iomgrconfiggetparametervaluebyte
	#define CHK_iomgrconfiggetparametervaluebyte  TRUE
	#define EXP_iomgrconfiggetparametervaluebyte  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparametervaluebyte", (RTS_UINTPTR)iomgrconfiggetparametervaluebyte, 1, RTSITF_GET_SIGNATURE(0, 0xDE4EF488), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrconfiggetparametervaluebyte  PFIOMGRCONFIGGETPARAMETERVALUEBYTE_IEC pfiomgrconfiggetparametervaluebyte;
	#define EXT_iomgrconfiggetparametervaluebyte  extern PFIOMGRCONFIGGETPARAMETERVALUEBYTE_IEC pfiomgrconfiggetparametervaluebyte;
	#define GET_iomgrconfiggetparametervaluebyte(fl)  s_pfCMGetAPI2( "iomgrconfiggetparametervaluebyte", (RTS_VOID_FCTPTR *)&pfiomgrconfiggetparametervaluebyte, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xDE4EF488), 0x03050800)
	#define CAL_iomgrconfiggetparametervaluebyte  pfiomgrconfiggetparametervaluebyte
	#define CHK_iomgrconfiggetparametervaluebyte  (pfiomgrconfiggetparametervaluebyte != NULL)
	#define EXP_iomgrconfiggetparametervaluebyte   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparametervaluebyte", (RTS_UINTPTR)iomgrconfiggetparametervaluebyte, 1, RTSITF_GET_SIGNATURE(0, 0xDE4EF488), 0x03050800) 
#endif


/**
 * <description>iomgrconfiggetparametervaluedword</description>
 */
typedef struct tagiomgrconfiggetparametervaluedword_struct
{
	IoConfigParameter *pParameter;		/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_DWORD IoMgrConfigGetParameterValueDword;	/* VAR_OUTPUT */	
} iomgrconfiggetparametervaluedword_struct;

void CDECL CDECL_EXT iomgrconfiggetparametervaluedword(iomgrconfiggetparametervaluedword_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRCONFIGGETPARAMETERVALUEDWORD_IEC) (iomgrconfiggetparametervaluedword_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETPARAMETERVALUEDWORD_NOTIMPLEMENTED)
	#define USE_iomgrconfiggetparametervaluedword
	#define EXT_iomgrconfiggetparametervaluedword
	#define GET_iomgrconfiggetparametervaluedword(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrconfiggetparametervaluedword(p0) 
	#define CHK_iomgrconfiggetparametervaluedword  FALSE
	#define EXP_iomgrconfiggetparametervaluedword  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrconfiggetparametervaluedword
	#define EXT_iomgrconfiggetparametervaluedword
	#define GET_iomgrconfiggetparametervaluedword(fl)  CAL_CMGETAPI( "iomgrconfiggetparametervaluedword" ) 
	#define CAL_iomgrconfiggetparametervaluedword  iomgrconfiggetparametervaluedword
	#define CHK_iomgrconfiggetparametervaluedword  TRUE
	#define EXP_iomgrconfiggetparametervaluedword  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparametervaluedword", (RTS_UINTPTR)iomgrconfiggetparametervaluedword, 1, RTSITF_GET_SIGNATURE(0, 0x6F885F72), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrconfiggetparametervaluedword
	#define EXT_iomgrconfiggetparametervaluedword
	#define GET_iomgrconfiggetparametervaluedword(fl)  CAL_CMGETAPI( "iomgrconfiggetparametervaluedword" ) 
	#define CAL_iomgrconfiggetparametervaluedword  iomgrconfiggetparametervaluedword
	#define CHK_iomgrconfiggetparametervaluedword  TRUE
	#define EXP_iomgrconfiggetparametervaluedword  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparametervaluedword", (RTS_UINTPTR)iomgrconfiggetparametervaluedword, 1, RTSITF_GET_SIGNATURE(0, 0x6F885F72), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrconfiggetparametervaluedword
	#define EXT_CmpIoMgriomgrconfiggetparametervaluedword
	#define GET_CmpIoMgriomgrconfiggetparametervaluedword  ERR_OK
	#define CAL_CmpIoMgriomgrconfiggetparametervaluedword  iomgrconfiggetparametervaluedword
	#define CHK_CmpIoMgriomgrconfiggetparametervaluedword  TRUE
	#define EXP_CmpIoMgriomgrconfiggetparametervaluedword  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparametervaluedword", (RTS_UINTPTR)iomgrconfiggetparametervaluedword, 1, RTSITF_GET_SIGNATURE(0, 0x6F885F72), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrconfiggetparametervaluedword
	#define EXT_iomgrconfiggetparametervaluedword
	#define GET_iomgrconfiggetparametervaluedword(fl)  CAL_CMGETAPI( "iomgrconfiggetparametervaluedword" ) 
	#define CAL_iomgrconfiggetparametervaluedword  iomgrconfiggetparametervaluedword
	#define CHK_iomgrconfiggetparametervaluedword  TRUE
	#define EXP_iomgrconfiggetparametervaluedword  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparametervaluedword", (RTS_UINTPTR)iomgrconfiggetparametervaluedword, 1, RTSITF_GET_SIGNATURE(0, 0x6F885F72), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrconfiggetparametervaluedword  PFIOMGRCONFIGGETPARAMETERVALUEDWORD_IEC pfiomgrconfiggetparametervaluedword;
	#define EXT_iomgrconfiggetparametervaluedword  extern PFIOMGRCONFIGGETPARAMETERVALUEDWORD_IEC pfiomgrconfiggetparametervaluedword;
	#define GET_iomgrconfiggetparametervaluedword(fl)  s_pfCMGetAPI2( "iomgrconfiggetparametervaluedword", (RTS_VOID_FCTPTR *)&pfiomgrconfiggetparametervaluedword, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x6F885F72), 0x03050800)
	#define CAL_iomgrconfiggetparametervaluedword  pfiomgrconfiggetparametervaluedword
	#define CHK_iomgrconfiggetparametervaluedword  (pfiomgrconfiggetparametervaluedword != NULL)
	#define EXP_iomgrconfiggetparametervaluedword   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparametervaluedword", (RTS_UINTPTR)iomgrconfiggetparametervaluedword, 1, RTSITF_GET_SIGNATURE(0, 0x6F885F72), 0x03050800) 
#endif


/**
 * <description>iomgrconfiggetparametervaluepointer</description>
 */
typedef struct tagiomgrconfiggetparametervaluepointer_struct
{
	IoConfigParameter *pParameter;		/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_BYTE *IoMgrConfigGetParameterValuePointer;	/* VAR_OUTPUT */	
} iomgrconfiggetparametervaluepointer_struct;

void CDECL CDECL_EXT iomgrconfiggetparametervaluepointer(iomgrconfiggetparametervaluepointer_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRCONFIGGETPARAMETERVALUEPOINTER_IEC) (iomgrconfiggetparametervaluepointer_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETPARAMETERVALUEPOINTER_NOTIMPLEMENTED)
	#define USE_iomgrconfiggetparametervaluepointer
	#define EXT_iomgrconfiggetparametervaluepointer
	#define GET_iomgrconfiggetparametervaluepointer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrconfiggetparametervaluepointer(p0) 
	#define CHK_iomgrconfiggetparametervaluepointer  FALSE
	#define EXP_iomgrconfiggetparametervaluepointer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrconfiggetparametervaluepointer
	#define EXT_iomgrconfiggetparametervaluepointer
	#define GET_iomgrconfiggetparametervaluepointer(fl)  CAL_CMGETAPI( "iomgrconfiggetparametervaluepointer" ) 
	#define CAL_iomgrconfiggetparametervaluepointer  iomgrconfiggetparametervaluepointer
	#define CHK_iomgrconfiggetparametervaluepointer  TRUE
	#define EXP_iomgrconfiggetparametervaluepointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparametervaluepointer", (RTS_UINTPTR)iomgrconfiggetparametervaluepointer, 1, RTSITF_GET_SIGNATURE(0, 0x633BC6E3), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrconfiggetparametervaluepointer
	#define EXT_iomgrconfiggetparametervaluepointer
	#define GET_iomgrconfiggetparametervaluepointer(fl)  CAL_CMGETAPI( "iomgrconfiggetparametervaluepointer" ) 
	#define CAL_iomgrconfiggetparametervaluepointer  iomgrconfiggetparametervaluepointer
	#define CHK_iomgrconfiggetparametervaluepointer  TRUE
	#define EXP_iomgrconfiggetparametervaluepointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparametervaluepointer", (RTS_UINTPTR)iomgrconfiggetparametervaluepointer, 1, RTSITF_GET_SIGNATURE(0, 0x633BC6E3), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrconfiggetparametervaluepointer
	#define EXT_CmpIoMgriomgrconfiggetparametervaluepointer
	#define GET_CmpIoMgriomgrconfiggetparametervaluepointer  ERR_OK
	#define CAL_CmpIoMgriomgrconfiggetparametervaluepointer  iomgrconfiggetparametervaluepointer
	#define CHK_CmpIoMgriomgrconfiggetparametervaluepointer  TRUE
	#define EXP_CmpIoMgriomgrconfiggetparametervaluepointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparametervaluepointer", (RTS_UINTPTR)iomgrconfiggetparametervaluepointer, 1, RTSITF_GET_SIGNATURE(0, 0x633BC6E3), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrconfiggetparametervaluepointer
	#define EXT_iomgrconfiggetparametervaluepointer
	#define GET_iomgrconfiggetparametervaluepointer(fl)  CAL_CMGETAPI( "iomgrconfiggetparametervaluepointer" ) 
	#define CAL_iomgrconfiggetparametervaluepointer  iomgrconfiggetparametervaluepointer
	#define CHK_iomgrconfiggetparametervaluepointer  TRUE
	#define EXP_iomgrconfiggetparametervaluepointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparametervaluepointer", (RTS_UINTPTR)iomgrconfiggetparametervaluepointer, 1, RTSITF_GET_SIGNATURE(0, 0x633BC6E3), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrconfiggetparametervaluepointer  PFIOMGRCONFIGGETPARAMETERVALUEPOINTER_IEC pfiomgrconfiggetparametervaluepointer;
	#define EXT_iomgrconfiggetparametervaluepointer  extern PFIOMGRCONFIGGETPARAMETERVALUEPOINTER_IEC pfiomgrconfiggetparametervaluepointer;
	#define GET_iomgrconfiggetparametervaluepointer(fl)  s_pfCMGetAPI2( "iomgrconfiggetparametervaluepointer", (RTS_VOID_FCTPTR *)&pfiomgrconfiggetparametervaluepointer, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x633BC6E3), 0x03050800)
	#define CAL_iomgrconfiggetparametervaluepointer  pfiomgrconfiggetparametervaluepointer
	#define CHK_iomgrconfiggetparametervaluepointer  (pfiomgrconfiggetparametervaluepointer != NULL)
	#define EXP_iomgrconfiggetparametervaluepointer   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparametervaluepointer", (RTS_UINTPTR)iomgrconfiggetparametervaluepointer, 1, RTSITF_GET_SIGNATURE(0, 0x633BC6E3), 0x03050800) 
#endif


/**
 * <description>iomgrconfiggetparametervalueword</description>
 */
typedef struct tagiomgrconfiggetparametervalueword_struct
{
	IoConfigParameter *pParameter;		/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_WORD IoMgrConfigGetParameterValueWord;	/* VAR_OUTPUT */	
} iomgrconfiggetparametervalueword_struct;

void CDECL CDECL_EXT iomgrconfiggetparametervalueword(iomgrconfiggetparametervalueword_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRCONFIGGETPARAMETERVALUEWORD_IEC) (iomgrconfiggetparametervalueword_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETPARAMETERVALUEWORD_NOTIMPLEMENTED)
	#define USE_iomgrconfiggetparametervalueword
	#define EXT_iomgrconfiggetparametervalueword
	#define GET_iomgrconfiggetparametervalueword(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrconfiggetparametervalueword(p0) 
	#define CHK_iomgrconfiggetparametervalueword  FALSE
	#define EXP_iomgrconfiggetparametervalueword  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrconfiggetparametervalueword
	#define EXT_iomgrconfiggetparametervalueword
	#define GET_iomgrconfiggetparametervalueword(fl)  CAL_CMGETAPI( "iomgrconfiggetparametervalueword" ) 
	#define CAL_iomgrconfiggetparametervalueword  iomgrconfiggetparametervalueword
	#define CHK_iomgrconfiggetparametervalueword  TRUE
	#define EXP_iomgrconfiggetparametervalueword  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparametervalueword", (RTS_UINTPTR)iomgrconfiggetparametervalueword, 1, RTSITF_GET_SIGNATURE(0, 0x522D5073), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrconfiggetparametervalueword
	#define EXT_iomgrconfiggetparametervalueword
	#define GET_iomgrconfiggetparametervalueword(fl)  CAL_CMGETAPI( "iomgrconfiggetparametervalueword" ) 
	#define CAL_iomgrconfiggetparametervalueword  iomgrconfiggetparametervalueword
	#define CHK_iomgrconfiggetparametervalueword  TRUE
	#define EXP_iomgrconfiggetparametervalueword  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparametervalueword", (RTS_UINTPTR)iomgrconfiggetparametervalueword, 1, RTSITF_GET_SIGNATURE(0, 0x522D5073), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrconfiggetparametervalueword
	#define EXT_CmpIoMgriomgrconfiggetparametervalueword
	#define GET_CmpIoMgriomgrconfiggetparametervalueword  ERR_OK
	#define CAL_CmpIoMgriomgrconfiggetparametervalueword  iomgrconfiggetparametervalueword
	#define CHK_CmpIoMgriomgrconfiggetparametervalueword  TRUE
	#define EXP_CmpIoMgriomgrconfiggetparametervalueword  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparametervalueword", (RTS_UINTPTR)iomgrconfiggetparametervalueword, 1, RTSITF_GET_SIGNATURE(0, 0x522D5073), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrconfiggetparametervalueword
	#define EXT_iomgrconfiggetparametervalueword
	#define GET_iomgrconfiggetparametervalueword(fl)  CAL_CMGETAPI( "iomgrconfiggetparametervalueword" ) 
	#define CAL_iomgrconfiggetparametervalueword  iomgrconfiggetparametervalueword
	#define CHK_iomgrconfiggetparametervalueword  TRUE
	#define EXP_iomgrconfiggetparametervalueword  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparametervalueword", (RTS_UINTPTR)iomgrconfiggetparametervalueword, 1, RTSITF_GET_SIGNATURE(0, 0x522D5073), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrconfiggetparametervalueword  PFIOMGRCONFIGGETPARAMETERVALUEWORD_IEC pfiomgrconfiggetparametervalueword;
	#define EXT_iomgrconfiggetparametervalueword  extern PFIOMGRCONFIGGETPARAMETERVALUEWORD_IEC pfiomgrconfiggetparametervalueword;
	#define GET_iomgrconfiggetparametervalueword(fl)  s_pfCMGetAPI2( "iomgrconfiggetparametervalueword", (RTS_VOID_FCTPTR *)&pfiomgrconfiggetparametervalueword, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x522D5073), 0x03050800)
	#define CAL_iomgrconfiggetparametervalueword  pfiomgrconfiggetparametervalueword
	#define CHK_iomgrconfiggetparametervalueword  (pfiomgrconfiggetparametervalueword != NULL)
	#define EXP_iomgrconfiggetparametervalueword   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetparametervalueword", (RTS_UINTPTR)iomgrconfiggetparametervalueword, 1, RTSITF_GET_SIGNATURE(0, 0x522D5073), 0x03050800) 
#endif


/**
 * <description>iomgrconfigresetdiagnosis</description>
 */
typedef struct tagiomgrconfigresetdiagnosis_struct
{
	IoConfigConnector *pConnector;		/* VAR_INPUT */	
	RTS_IEC_DWORD dwFlags;				/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrConfigResetDiagnosis;	/* VAR_OUTPUT */	
} iomgrconfigresetdiagnosis_struct;

void CDECL CDECL_EXT iomgrconfigresetdiagnosis(iomgrconfigresetdiagnosis_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRCONFIGRESETDIAGNOSIS_IEC) (iomgrconfigresetdiagnosis_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGRESETDIAGNOSIS_NOTIMPLEMENTED)
	#define USE_iomgrconfigresetdiagnosis
	#define EXT_iomgrconfigresetdiagnosis
	#define GET_iomgrconfigresetdiagnosis(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrconfigresetdiagnosis(p0) 
	#define CHK_iomgrconfigresetdiagnosis  FALSE
	#define EXP_iomgrconfigresetdiagnosis  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrconfigresetdiagnosis
	#define EXT_iomgrconfigresetdiagnosis
	#define GET_iomgrconfigresetdiagnosis(fl)  CAL_CMGETAPI( "iomgrconfigresetdiagnosis" ) 
	#define CAL_iomgrconfigresetdiagnosis  iomgrconfigresetdiagnosis
	#define CHK_iomgrconfigresetdiagnosis  TRUE
	#define EXP_iomgrconfigresetdiagnosis  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfigresetdiagnosis", (RTS_UINTPTR)iomgrconfigresetdiagnosis, 1, RTSITF_GET_SIGNATURE(0, 0x6B60C0F6), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrconfigresetdiagnosis
	#define EXT_iomgrconfigresetdiagnosis
	#define GET_iomgrconfigresetdiagnosis(fl)  CAL_CMGETAPI( "iomgrconfigresetdiagnosis" ) 
	#define CAL_iomgrconfigresetdiagnosis  iomgrconfigresetdiagnosis
	#define CHK_iomgrconfigresetdiagnosis  TRUE
	#define EXP_iomgrconfigresetdiagnosis  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfigresetdiagnosis", (RTS_UINTPTR)iomgrconfigresetdiagnosis, 1, RTSITF_GET_SIGNATURE(0, 0x6B60C0F6), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrconfigresetdiagnosis
	#define EXT_CmpIoMgriomgrconfigresetdiagnosis
	#define GET_CmpIoMgriomgrconfigresetdiagnosis  ERR_OK
	#define CAL_CmpIoMgriomgrconfigresetdiagnosis  iomgrconfigresetdiagnosis
	#define CHK_CmpIoMgriomgrconfigresetdiagnosis  TRUE
	#define EXP_CmpIoMgriomgrconfigresetdiagnosis  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfigresetdiagnosis", (RTS_UINTPTR)iomgrconfigresetdiagnosis, 1, RTSITF_GET_SIGNATURE(0, 0x6B60C0F6), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrconfigresetdiagnosis
	#define EXT_iomgrconfigresetdiagnosis
	#define GET_iomgrconfigresetdiagnosis(fl)  CAL_CMGETAPI( "iomgrconfigresetdiagnosis" ) 
	#define CAL_iomgrconfigresetdiagnosis  iomgrconfigresetdiagnosis
	#define CHK_iomgrconfigresetdiagnosis  TRUE
	#define EXP_iomgrconfigresetdiagnosis  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfigresetdiagnosis", (RTS_UINTPTR)iomgrconfigresetdiagnosis, 1, RTSITF_GET_SIGNATURE(0, 0x6B60C0F6), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrconfigresetdiagnosis  PFIOMGRCONFIGRESETDIAGNOSIS_IEC pfiomgrconfigresetdiagnosis;
	#define EXT_iomgrconfigresetdiagnosis  extern PFIOMGRCONFIGRESETDIAGNOSIS_IEC pfiomgrconfigresetdiagnosis;
	#define GET_iomgrconfigresetdiagnosis(fl)  s_pfCMGetAPI2( "iomgrconfigresetdiagnosis", (RTS_VOID_FCTPTR *)&pfiomgrconfigresetdiagnosis, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x6B60C0F6), 0x03050800)
	#define CAL_iomgrconfigresetdiagnosis  pfiomgrconfigresetdiagnosis
	#define CHK_iomgrconfigresetdiagnosis  (pfiomgrconfigresetdiagnosis != NULL)
	#define EXP_iomgrconfigresetdiagnosis   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfigresetdiagnosis", (RTS_UINTPTR)iomgrconfigresetdiagnosis, 1, RTSITF_GET_SIGNATURE(0, 0x6B60C0F6), 0x03050800) 
#endif


/**
 * <description>iomgrconfigsetdiagnosis</description>
 */
typedef struct tagiomgrconfigsetdiagnosis_struct
{
	IoConfigConnector *pConnector;		/* VAR_INPUT */	
	RTS_IEC_DWORD dwFlags;				/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrConfigSetDiagnosis;	/* VAR_OUTPUT */	
} iomgrconfigsetdiagnosis_struct;

void CDECL CDECL_EXT iomgrconfigsetdiagnosis(iomgrconfigsetdiagnosis_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRCONFIGSETDIAGNOSIS_IEC) (iomgrconfigsetdiagnosis_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGSETDIAGNOSIS_NOTIMPLEMENTED)
	#define USE_iomgrconfigsetdiagnosis
	#define EXT_iomgrconfigsetdiagnosis
	#define GET_iomgrconfigsetdiagnosis(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrconfigsetdiagnosis(p0) 
	#define CHK_iomgrconfigsetdiagnosis  FALSE
	#define EXP_iomgrconfigsetdiagnosis  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrconfigsetdiagnosis
	#define EXT_iomgrconfigsetdiagnosis
	#define GET_iomgrconfigsetdiagnosis(fl)  CAL_CMGETAPI( "iomgrconfigsetdiagnosis" ) 
	#define CAL_iomgrconfigsetdiagnosis  iomgrconfigsetdiagnosis
	#define CHK_iomgrconfigsetdiagnosis  TRUE
	#define EXP_iomgrconfigsetdiagnosis  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfigsetdiagnosis", (RTS_UINTPTR)iomgrconfigsetdiagnosis, 1, RTSITF_GET_SIGNATURE(0, 0xE0CCC2C9), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrconfigsetdiagnosis
	#define EXT_iomgrconfigsetdiagnosis
	#define GET_iomgrconfigsetdiagnosis(fl)  CAL_CMGETAPI( "iomgrconfigsetdiagnosis" ) 
	#define CAL_iomgrconfigsetdiagnosis  iomgrconfigsetdiagnosis
	#define CHK_iomgrconfigsetdiagnosis  TRUE
	#define EXP_iomgrconfigsetdiagnosis  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfigsetdiagnosis", (RTS_UINTPTR)iomgrconfigsetdiagnosis, 1, RTSITF_GET_SIGNATURE(0, 0xE0CCC2C9), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrconfigsetdiagnosis
	#define EXT_CmpIoMgriomgrconfigsetdiagnosis
	#define GET_CmpIoMgriomgrconfigsetdiagnosis  ERR_OK
	#define CAL_CmpIoMgriomgrconfigsetdiagnosis  iomgrconfigsetdiagnosis
	#define CHK_CmpIoMgriomgrconfigsetdiagnosis  TRUE
	#define EXP_CmpIoMgriomgrconfigsetdiagnosis  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfigsetdiagnosis", (RTS_UINTPTR)iomgrconfigsetdiagnosis, 1, RTSITF_GET_SIGNATURE(0, 0xE0CCC2C9), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrconfigsetdiagnosis
	#define EXT_iomgrconfigsetdiagnosis
	#define GET_iomgrconfigsetdiagnosis(fl)  CAL_CMGETAPI( "iomgrconfigsetdiagnosis" ) 
	#define CAL_iomgrconfigsetdiagnosis  iomgrconfigsetdiagnosis
	#define CHK_iomgrconfigsetdiagnosis  TRUE
	#define EXP_iomgrconfigsetdiagnosis  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfigsetdiagnosis", (RTS_UINTPTR)iomgrconfigsetdiagnosis, 1, RTSITF_GET_SIGNATURE(0, 0xE0CCC2C9), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrconfigsetdiagnosis  PFIOMGRCONFIGSETDIAGNOSIS_IEC pfiomgrconfigsetdiagnosis;
	#define EXT_iomgrconfigsetdiagnosis  extern PFIOMGRCONFIGSETDIAGNOSIS_IEC pfiomgrconfigsetdiagnosis;
	#define GET_iomgrconfigsetdiagnosis(fl)  s_pfCMGetAPI2( "iomgrconfigsetdiagnosis", (RTS_VOID_FCTPTR *)&pfiomgrconfigsetdiagnosis, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xE0CCC2C9), 0x03050800)
	#define CAL_iomgrconfigsetdiagnosis  pfiomgrconfigsetdiagnosis
	#define CHK_iomgrconfigsetdiagnosis  (pfiomgrconfigsetdiagnosis != NULL)
	#define EXP_iomgrconfigsetdiagnosis   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfigsetdiagnosis", (RTS_UINTPTR)iomgrconfigsetdiagnosis, 1, RTSITF_GET_SIGNATURE(0, 0xE0CCC2C9), 0x03050800) 
#endif


/**
 * <description>iomgrcopyinputbe</description>
 */
typedef struct tagiomgrcopyinputbe_struct
{
	IoConfigChannelMap *pChannel;		/* VAR_INPUT */	
	RTS_IEC_BYTE *pAddress;				/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrCopyInputBE;	/* VAR_OUTPUT */	
} iomgrcopyinputbe_struct;

void CDECL CDECL_EXT iomgrcopyinputbe(iomgrcopyinputbe_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRCOPYINPUTBE_IEC) (iomgrcopyinputbe_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCOPYINPUTBE_NOTIMPLEMENTED)
	#define USE_iomgrcopyinputbe
	#define EXT_iomgrcopyinputbe
	#define GET_iomgrcopyinputbe(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrcopyinputbe(p0) 
	#define CHK_iomgrcopyinputbe  FALSE
	#define EXP_iomgrcopyinputbe  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrcopyinputbe
	#define EXT_iomgrcopyinputbe
	#define GET_iomgrcopyinputbe(fl)  CAL_CMGETAPI( "iomgrcopyinputbe" ) 
	#define CAL_iomgrcopyinputbe  iomgrcopyinputbe
	#define CHK_iomgrcopyinputbe  TRUE
	#define EXP_iomgrcopyinputbe  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrcopyinputbe", (RTS_UINTPTR)iomgrcopyinputbe, 1, RTSITF_GET_SIGNATURE(0, 0x072C6C71), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrcopyinputbe
	#define EXT_iomgrcopyinputbe
	#define GET_iomgrcopyinputbe(fl)  CAL_CMGETAPI( "iomgrcopyinputbe" ) 
	#define CAL_iomgrcopyinputbe  iomgrcopyinputbe
	#define CHK_iomgrcopyinputbe  TRUE
	#define EXP_iomgrcopyinputbe  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrcopyinputbe", (RTS_UINTPTR)iomgrcopyinputbe, 1, RTSITF_GET_SIGNATURE(0, 0x072C6C71), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrcopyinputbe
	#define EXT_CmpIoMgriomgrcopyinputbe
	#define GET_CmpIoMgriomgrcopyinputbe  ERR_OK
	#define CAL_CmpIoMgriomgrcopyinputbe  iomgrcopyinputbe
	#define CHK_CmpIoMgriomgrcopyinputbe  TRUE
	#define EXP_CmpIoMgriomgrcopyinputbe  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrcopyinputbe", (RTS_UINTPTR)iomgrcopyinputbe, 1, RTSITF_GET_SIGNATURE(0, 0x072C6C71), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrcopyinputbe
	#define EXT_iomgrcopyinputbe
	#define GET_iomgrcopyinputbe(fl)  CAL_CMGETAPI( "iomgrcopyinputbe" ) 
	#define CAL_iomgrcopyinputbe  iomgrcopyinputbe
	#define CHK_iomgrcopyinputbe  TRUE
	#define EXP_iomgrcopyinputbe  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrcopyinputbe", (RTS_UINTPTR)iomgrcopyinputbe, 1, RTSITF_GET_SIGNATURE(0, 0x072C6C71), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrcopyinputbe  PFIOMGRCOPYINPUTBE_IEC pfiomgrcopyinputbe;
	#define EXT_iomgrcopyinputbe  extern PFIOMGRCOPYINPUTBE_IEC pfiomgrcopyinputbe;
	#define GET_iomgrcopyinputbe(fl)  s_pfCMGetAPI2( "iomgrcopyinputbe", (RTS_VOID_FCTPTR *)&pfiomgrcopyinputbe, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x072C6C71), 0x03050800)
	#define CAL_iomgrcopyinputbe  pfiomgrcopyinputbe
	#define CHK_iomgrcopyinputbe  (pfiomgrcopyinputbe != NULL)
	#define EXP_iomgrcopyinputbe   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrcopyinputbe", (RTS_UINTPTR)iomgrcopyinputbe, 1, RTSITF_GET_SIGNATURE(0, 0x072C6C71), 0x03050800) 
#endif


/**
 * <description>iomgrcopyinputle</description>
 */
typedef struct tagiomgrcopyinputle_struct
{
	IoConfigChannelMap *pChannel;		/* VAR_INPUT */	
	RTS_IEC_BYTE *pAddress;				/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrCopyInputLE;	/* VAR_OUTPUT */	
} iomgrcopyinputle_struct;

void CDECL CDECL_EXT iomgrcopyinputle(iomgrcopyinputle_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRCOPYINPUTLE_IEC) (iomgrcopyinputle_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCOPYINPUTLE_NOTIMPLEMENTED)
	#define USE_iomgrcopyinputle
	#define EXT_iomgrcopyinputle
	#define GET_iomgrcopyinputle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrcopyinputle(p0) 
	#define CHK_iomgrcopyinputle  FALSE
	#define EXP_iomgrcopyinputle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrcopyinputle
	#define EXT_iomgrcopyinputle
	#define GET_iomgrcopyinputle(fl)  CAL_CMGETAPI( "iomgrcopyinputle" ) 
	#define CAL_iomgrcopyinputle  iomgrcopyinputle
	#define CHK_iomgrcopyinputle  TRUE
	#define EXP_iomgrcopyinputle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrcopyinputle", (RTS_UINTPTR)iomgrcopyinputle, 1, RTSITF_GET_SIGNATURE(0, 0xD4FB4CB6), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrcopyinputle
	#define EXT_iomgrcopyinputle
	#define GET_iomgrcopyinputle(fl)  CAL_CMGETAPI( "iomgrcopyinputle" ) 
	#define CAL_iomgrcopyinputle  iomgrcopyinputle
	#define CHK_iomgrcopyinputle  TRUE
	#define EXP_iomgrcopyinputle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrcopyinputle", (RTS_UINTPTR)iomgrcopyinputle, 1, RTSITF_GET_SIGNATURE(0, 0xD4FB4CB6), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrcopyinputle
	#define EXT_CmpIoMgriomgrcopyinputle
	#define GET_CmpIoMgriomgrcopyinputle  ERR_OK
	#define CAL_CmpIoMgriomgrcopyinputle  iomgrcopyinputle
	#define CHK_CmpIoMgriomgrcopyinputle  TRUE
	#define EXP_CmpIoMgriomgrcopyinputle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrcopyinputle", (RTS_UINTPTR)iomgrcopyinputle, 1, RTSITF_GET_SIGNATURE(0, 0xD4FB4CB6), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrcopyinputle
	#define EXT_iomgrcopyinputle
	#define GET_iomgrcopyinputle(fl)  CAL_CMGETAPI( "iomgrcopyinputle" ) 
	#define CAL_iomgrcopyinputle  iomgrcopyinputle
	#define CHK_iomgrcopyinputle  TRUE
	#define EXP_iomgrcopyinputle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrcopyinputle", (RTS_UINTPTR)iomgrcopyinputle, 1, RTSITF_GET_SIGNATURE(0, 0xD4FB4CB6), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrcopyinputle  PFIOMGRCOPYINPUTLE_IEC pfiomgrcopyinputle;
	#define EXT_iomgrcopyinputle  extern PFIOMGRCOPYINPUTLE_IEC pfiomgrcopyinputle;
	#define GET_iomgrcopyinputle(fl)  s_pfCMGetAPI2( "iomgrcopyinputle", (RTS_VOID_FCTPTR *)&pfiomgrcopyinputle, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xD4FB4CB6), 0x03050800)
	#define CAL_iomgrcopyinputle  pfiomgrcopyinputle
	#define CHK_iomgrcopyinputle  (pfiomgrcopyinputle != NULL)
	#define EXP_iomgrcopyinputle   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrcopyinputle", (RTS_UINTPTR)iomgrcopyinputle, 1, RTSITF_GET_SIGNATURE(0, 0xD4FB4CB6), 0x03050800) 
#endif


/**
 * <description>iomgrcopyoutputbe</description>
 */
typedef struct tagiomgrcopyoutputbe_struct
{
	IoConfigChannelMap *pChannel;		/* VAR_INPUT */	
	RTS_IEC_BYTE *pAddress;				/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrCopyOutputBE;	/* VAR_OUTPUT */	
} iomgrcopyoutputbe_struct;

void CDECL CDECL_EXT iomgrcopyoutputbe(iomgrcopyoutputbe_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRCOPYOUTPUTBE_IEC) (iomgrcopyoutputbe_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCOPYOUTPUTBE_NOTIMPLEMENTED)
	#define USE_iomgrcopyoutputbe
	#define EXT_iomgrcopyoutputbe
	#define GET_iomgrcopyoutputbe(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrcopyoutputbe(p0) 
	#define CHK_iomgrcopyoutputbe  FALSE
	#define EXP_iomgrcopyoutputbe  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrcopyoutputbe
	#define EXT_iomgrcopyoutputbe
	#define GET_iomgrcopyoutputbe(fl)  CAL_CMGETAPI( "iomgrcopyoutputbe" ) 
	#define CAL_iomgrcopyoutputbe  iomgrcopyoutputbe
	#define CHK_iomgrcopyoutputbe  TRUE
	#define EXP_iomgrcopyoutputbe  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrcopyoutputbe", (RTS_UINTPTR)iomgrcopyoutputbe, 1, RTSITF_GET_SIGNATURE(0, 0xCDB7B2BE), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrcopyoutputbe
	#define EXT_iomgrcopyoutputbe
	#define GET_iomgrcopyoutputbe(fl)  CAL_CMGETAPI( "iomgrcopyoutputbe" ) 
	#define CAL_iomgrcopyoutputbe  iomgrcopyoutputbe
	#define CHK_iomgrcopyoutputbe  TRUE
	#define EXP_iomgrcopyoutputbe  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrcopyoutputbe", (RTS_UINTPTR)iomgrcopyoutputbe, 1, RTSITF_GET_SIGNATURE(0, 0xCDB7B2BE), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrcopyoutputbe
	#define EXT_CmpIoMgriomgrcopyoutputbe
	#define GET_CmpIoMgriomgrcopyoutputbe  ERR_OK
	#define CAL_CmpIoMgriomgrcopyoutputbe  iomgrcopyoutputbe
	#define CHK_CmpIoMgriomgrcopyoutputbe  TRUE
	#define EXP_CmpIoMgriomgrcopyoutputbe  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrcopyoutputbe", (RTS_UINTPTR)iomgrcopyoutputbe, 1, RTSITF_GET_SIGNATURE(0, 0xCDB7B2BE), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrcopyoutputbe
	#define EXT_iomgrcopyoutputbe
	#define GET_iomgrcopyoutputbe(fl)  CAL_CMGETAPI( "iomgrcopyoutputbe" ) 
	#define CAL_iomgrcopyoutputbe  iomgrcopyoutputbe
	#define CHK_iomgrcopyoutputbe  TRUE
	#define EXP_iomgrcopyoutputbe  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrcopyoutputbe", (RTS_UINTPTR)iomgrcopyoutputbe, 1, RTSITF_GET_SIGNATURE(0, 0xCDB7B2BE), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrcopyoutputbe  PFIOMGRCOPYOUTPUTBE_IEC pfiomgrcopyoutputbe;
	#define EXT_iomgrcopyoutputbe  extern PFIOMGRCOPYOUTPUTBE_IEC pfiomgrcopyoutputbe;
	#define GET_iomgrcopyoutputbe(fl)  s_pfCMGetAPI2( "iomgrcopyoutputbe", (RTS_VOID_FCTPTR *)&pfiomgrcopyoutputbe, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xCDB7B2BE), 0x03050800)
	#define CAL_iomgrcopyoutputbe  pfiomgrcopyoutputbe
	#define CHK_iomgrcopyoutputbe  (pfiomgrcopyoutputbe != NULL)
	#define EXP_iomgrcopyoutputbe   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrcopyoutputbe", (RTS_UINTPTR)iomgrcopyoutputbe, 1, RTSITF_GET_SIGNATURE(0, 0xCDB7B2BE), 0x03050800) 
#endif


/**
 * <description>iomgrcopyoutputle</description>
 */
typedef struct tagiomgrcopyoutputle_struct
{
	IoConfigChannelMap *pChannel;		/* VAR_INPUT */	
	RTS_IEC_BYTE *pAddress;				/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrCopyOutputLE;	/* VAR_OUTPUT */	
} iomgrcopyoutputle_struct;

void CDECL CDECL_EXT iomgrcopyoutputle(iomgrcopyoutputle_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRCOPYOUTPUTLE_IEC) (iomgrcopyoutputle_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCOPYOUTPUTLE_NOTIMPLEMENTED)
	#define USE_iomgrcopyoutputle
	#define EXT_iomgrcopyoutputle
	#define GET_iomgrcopyoutputle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrcopyoutputle(p0) 
	#define CHK_iomgrcopyoutputle  FALSE
	#define EXP_iomgrcopyoutputle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrcopyoutputle
	#define EXT_iomgrcopyoutputle
	#define GET_iomgrcopyoutputle(fl)  CAL_CMGETAPI( "iomgrcopyoutputle" ) 
	#define CAL_iomgrcopyoutputle  iomgrcopyoutputle
	#define CHK_iomgrcopyoutputle  TRUE
	#define EXP_iomgrcopyoutputle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrcopyoutputle", (RTS_UINTPTR)iomgrcopyoutputle, 1, RTSITF_GET_SIGNATURE(0, 0x5FC818BC), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrcopyoutputle
	#define EXT_iomgrcopyoutputle
	#define GET_iomgrcopyoutputle(fl)  CAL_CMGETAPI( "iomgrcopyoutputle" ) 
	#define CAL_iomgrcopyoutputle  iomgrcopyoutputle
	#define CHK_iomgrcopyoutputle  TRUE
	#define EXP_iomgrcopyoutputle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrcopyoutputle", (RTS_UINTPTR)iomgrcopyoutputle, 1, RTSITF_GET_SIGNATURE(0, 0x5FC818BC), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrcopyoutputle
	#define EXT_CmpIoMgriomgrcopyoutputle
	#define GET_CmpIoMgriomgrcopyoutputle  ERR_OK
	#define CAL_CmpIoMgriomgrcopyoutputle  iomgrcopyoutputle
	#define CHK_CmpIoMgriomgrcopyoutputle  TRUE
	#define EXP_CmpIoMgriomgrcopyoutputle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrcopyoutputle", (RTS_UINTPTR)iomgrcopyoutputle, 1, RTSITF_GET_SIGNATURE(0, 0x5FC818BC), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrcopyoutputle
	#define EXT_iomgrcopyoutputle
	#define GET_iomgrcopyoutputle(fl)  CAL_CMGETAPI( "iomgrcopyoutputle" ) 
	#define CAL_iomgrcopyoutputle  iomgrcopyoutputle
	#define CHK_iomgrcopyoutputle  TRUE
	#define EXP_iomgrcopyoutputle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrcopyoutputle", (RTS_UINTPTR)iomgrcopyoutputle, 1, RTSITF_GET_SIGNATURE(0, 0x5FC818BC), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrcopyoutputle  PFIOMGRCOPYOUTPUTLE_IEC pfiomgrcopyoutputle;
	#define EXT_iomgrcopyoutputle  extern PFIOMGRCOPYOUTPUTLE_IEC pfiomgrcopyoutputle;
	#define GET_iomgrcopyoutputle(fl)  s_pfCMGetAPI2( "iomgrcopyoutputle", (RTS_VOID_FCTPTR *)&pfiomgrcopyoutputle, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x5FC818BC), 0x03050800)
	#define CAL_iomgrcopyoutputle  pfiomgrcopyoutputle
	#define CHK_iomgrcopyoutputle  (pfiomgrcopyoutputle != NULL)
	#define EXP_iomgrcopyoutputle   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrcopyoutputle", (RTS_UINTPTR)iomgrcopyoutputle, 1, RTSITF_GET_SIGNATURE(0, 0x5FC818BC), 0x03050800) 
#endif


/**
 * <description>iomgrgetbuscycletype</description>
 */
typedef struct tagiomgrgetbuscycletype_struct
{
	IoConfigConnector *pConnector;		/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrGetBusCycleType;	/* VAR_OUTPUT */	
} iomgrgetbuscycletype_struct;

void CDECL CDECL_EXT iomgrgetbuscycletype(iomgrgetbuscycletype_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRGETBUSCYCLETYPE_IEC) (iomgrgetbuscycletype_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRGETBUSCYCLETYPE_NOTIMPLEMENTED)
	#define USE_iomgrgetbuscycletype
	#define EXT_iomgrgetbuscycletype
	#define GET_iomgrgetbuscycletype(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrgetbuscycletype(p0) 
	#define CHK_iomgrgetbuscycletype  FALSE
	#define EXP_iomgrgetbuscycletype  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrgetbuscycletype
	#define EXT_iomgrgetbuscycletype
	#define GET_iomgrgetbuscycletype(fl)  CAL_CMGETAPI( "iomgrgetbuscycletype" ) 
	#define CAL_iomgrgetbuscycletype  iomgrgetbuscycletype
	#define CHK_iomgrgetbuscycletype  TRUE
	#define EXP_iomgrgetbuscycletype  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetbuscycletype", (RTS_UINTPTR)iomgrgetbuscycletype, 1, RTSITF_GET_SIGNATURE(0, 0x8334DD20), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrgetbuscycletype
	#define EXT_iomgrgetbuscycletype
	#define GET_iomgrgetbuscycletype(fl)  CAL_CMGETAPI( "iomgrgetbuscycletype" ) 
	#define CAL_iomgrgetbuscycletype  iomgrgetbuscycletype
	#define CHK_iomgrgetbuscycletype  TRUE
	#define EXP_iomgrgetbuscycletype  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetbuscycletype", (RTS_UINTPTR)iomgrgetbuscycletype, 1, RTSITF_GET_SIGNATURE(0, 0x8334DD20), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrgetbuscycletype
	#define EXT_CmpIoMgriomgrgetbuscycletype
	#define GET_CmpIoMgriomgrgetbuscycletype  ERR_OK
	#define CAL_CmpIoMgriomgrgetbuscycletype  iomgrgetbuscycletype
	#define CHK_CmpIoMgriomgrgetbuscycletype  TRUE
	#define EXP_CmpIoMgriomgrgetbuscycletype  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetbuscycletype", (RTS_UINTPTR)iomgrgetbuscycletype, 1, RTSITF_GET_SIGNATURE(0, 0x8334DD20), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrgetbuscycletype
	#define EXT_iomgrgetbuscycletype
	#define GET_iomgrgetbuscycletype(fl)  CAL_CMGETAPI( "iomgrgetbuscycletype" ) 
	#define CAL_iomgrgetbuscycletype  iomgrgetbuscycletype
	#define CHK_iomgrgetbuscycletype  TRUE
	#define EXP_iomgrgetbuscycletype  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetbuscycletype", (RTS_UINTPTR)iomgrgetbuscycletype, 1, RTSITF_GET_SIGNATURE(0, 0x8334DD20), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrgetbuscycletype  PFIOMGRGETBUSCYCLETYPE_IEC pfiomgrgetbuscycletype;
	#define EXT_iomgrgetbuscycletype  extern PFIOMGRGETBUSCYCLETYPE_IEC pfiomgrgetbuscycletype;
	#define GET_iomgrgetbuscycletype(fl)  s_pfCMGetAPI2( "iomgrgetbuscycletype", (RTS_VOID_FCTPTR *)&pfiomgrgetbuscycletype, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x8334DD20), 0x03050800)
	#define CAL_iomgrgetbuscycletype  pfiomgrgetbuscycletype
	#define CHK_iomgrgetbuscycletype  (pfiomgrgetbuscycletype != NULL)
	#define EXP_iomgrgetbuscycletype   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetbuscycletype", (RTS_UINTPTR)iomgrgetbuscycletype, 1, RTSITF_GET_SIGNATURE(0, 0x8334DD20), 0x03050800) 
#endif


/**
 * <description>iomgrgetconfigapplication</description>
 */
typedef struct tagiomgrgetconfigapplication_struct
{
	RTS_IEC_STRING *pszConfigApplication;	/* VAR_INPUT */	
	RTS_IEC_DINT *pnMaxLen;				/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrGetConfigApplication;	/* VAR_OUTPUT */	
} iomgrgetconfigapplication_struct;

void CDECL CDECL_EXT iomgrgetconfigapplication(iomgrgetconfigapplication_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRGETCONFIGAPPLICATION_IEC) (iomgrgetconfigapplication_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRGETCONFIGAPPLICATION_NOTIMPLEMENTED)
	#define USE_iomgrgetconfigapplication
	#define EXT_iomgrgetconfigapplication
	#define GET_iomgrgetconfigapplication(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrgetconfigapplication(p0) 
	#define CHK_iomgrgetconfigapplication  FALSE
	#define EXP_iomgrgetconfigapplication  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrgetconfigapplication
	#define EXT_iomgrgetconfigapplication
	#define GET_iomgrgetconfigapplication(fl)  CAL_CMGETAPI( "iomgrgetconfigapplication" ) 
	#define CAL_iomgrgetconfigapplication  iomgrgetconfigapplication
	#define CHK_iomgrgetconfigapplication  TRUE
	#define EXP_iomgrgetconfigapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetconfigapplication", (RTS_UINTPTR)iomgrgetconfigapplication, 1, RTSITF_GET_SIGNATURE(0, 0xF82C99F4), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrgetconfigapplication
	#define EXT_iomgrgetconfigapplication
	#define GET_iomgrgetconfigapplication(fl)  CAL_CMGETAPI( "iomgrgetconfigapplication" ) 
	#define CAL_iomgrgetconfigapplication  iomgrgetconfigapplication
	#define CHK_iomgrgetconfigapplication  TRUE
	#define EXP_iomgrgetconfigapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetconfigapplication", (RTS_UINTPTR)iomgrgetconfigapplication, 1, RTSITF_GET_SIGNATURE(0, 0xF82C99F4), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrgetconfigapplication
	#define EXT_CmpIoMgriomgrgetconfigapplication
	#define GET_CmpIoMgriomgrgetconfigapplication  ERR_OK
	#define CAL_CmpIoMgriomgrgetconfigapplication  iomgrgetconfigapplication
	#define CHK_CmpIoMgriomgrgetconfigapplication  TRUE
	#define EXP_CmpIoMgriomgrgetconfigapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetconfigapplication", (RTS_UINTPTR)iomgrgetconfigapplication, 1, RTSITF_GET_SIGNATURE(0, 0xF82C99F4), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrgetconfigapplication
	#define EXT_iomgrgetconfigapplication
	#define GET_iomgrgetconfigapplication(fl)  CAL_CMGETAPI( "iomgrgetconfigapplication" ) 
	#define CAL_iomgrgetconfigapplication  iomgrgetconfigapplication
	#define CHK_iomgrgetconfigapplication  TRUE
	#define EXP_iomgrgetconfigapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetconfigapplication", (RTS_UINTPTR)iomgrgetconfigapplication, 1, RTSITF_GET_SIGNATURE(0, 0xF82C99F4), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrgetconfigapplication  PFIOMGRGETCONFIGAPPLICATION_IEC pfiomgrgetconfigapplication;
	#define EXT_iomgrgetconfigapplication  extern PFIOMGRGETCONFIGAPPLICATION_IEC pfiomgrgetconfigapplication;
	#define GET_iomgrgetconfigapplication(fl)  s_pfCMGetAPI2( "iomgrgetconfigapplication", (RTS_VOID_FCTPTR *)&pfiomgrgetconfigapplication, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xF82C99F4), 0x03050800)
	#define CAL_iomgrgetconfigapplication  pfiomgrgetconfigapplication
	#define CHK_iomgrgetconfigapplication  (pfiomgrgetconfigapplication != NULL)
	#define EXP_iomgrgetconfigapplication   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetconfigapplication", (RTS_UINTPTR)iomgrgetconfigapplication, 1, RTSITF_GET_SIGNATURE(0, 0xF82C99F4), 0x03050800) 
#endif


/**
 * <description>iomgrgetdriverproperties</description>
 */
typedef struct tagiomgrgetdriverproperties_struct
{
	RTS_IEC_HANDLE hIoDrv;				/* VAR_INPUT */	
	RTS_IEC_DWORD **ppProperties;		/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrGetDriverProperties;	/* VAR_OUTPUT */	
} iomgrgetdriverproperties_struct;

void CDECL CDECL_EXT iomgrgetdriverproperties(iomgrgetdriverproperties_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRGETDRIVERPROPERTIES_IEC) (iomgrgetdriverproperties_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRGETDRIVERPROPERTIES_NOTIMPLEMENTED)
	#define USE_iomgrgetdriverproperties
	#define EXT_iomgrgetdriverproperties
	#define GET_iomgrgetdriverproperties(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrgetdriverproperties(p0) 
	#define CHK_iomgrgetdriverproperties  FALSE
	#define EXP_iomgrgetdriverproperties  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrgetdriverproperties
	#define EXT_iomgrgetdriverproperties
	#define GET_iomgrgetdriverproperties(fl)  CAL_CMGETAPI( "iomgrgetdriverproperties" ) 
	#define CAL_iomgrgetdriverproperties  iomgrgetdriverproperties
	#define CHK_iomgrgetdriverproperties  TRUE
	#define EXP_iomgrgetdriverproperties  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetdriverproperties", (RTS_UINTPTR)iomgrgetdriverproperties, 1, RTSITF_GET_SIGNATURE(0, 0xEC0D662D), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrgetdriverproperties
	#define EXT_iomgrgetdriverproperties
	#define GET_iomgrgetdriverproperties(fl)  CAL_CMGETAPI( "iomgrgetdriverproperties" ) 
	#define CAL_iomgrgetdriverproperties  iomgrgetdriverproperties
	#define CHK_iomgrgetdriverproperties  TRUE
	#define EXP_iomgrgetdriverproperties  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetdriverproperties", (RTS_UINTPTR)iomgrgetdriverproperties, 1, RTSITF_GET_SIGNATURE(0, 0xEC0D662D), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrgetdriverproperties
	#define EXT_CmpIoMgriomgrgetdriverproperties
	#define GET_CmpIoMgriomgrgetdriverproperties  ERR_OK
	#define CAL_CmpIoMgriomgrgetdriverproperties  iomgrgetdriverproperties
	#define CHK_CmpIoMgriomgrgetdriverproperties  TRUE
	#define EXP_CmpIoMgriomgrgetdriverproperties  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetdriverproperties", (RTS_UINTPTR)iomgrgetdriverproperties, 1, RTSITF_GET_SIGNATURE(0, 0xEC0D662D), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrgetdriverproperties
	#define EXT_iomgrgetdriverproperties
	#define GET_iomgrgetdriverproperties(fl)  CAL_CMGETAPI( "iomgrgetdriverproperties" ) 
	#define CAL_iomgrgetdriverproperties  iomgrgetdriverproperties
	#define CHK_iomgrgetdriverproperties  TRUE
	#define EXP_iomgrgetdriverproperties  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetdriverproperties", (RTS_UINTPTR)iomgrgetdriverproperties, 1, RTSITF_GET_SIGNATURE(0, 0xEC0D662D), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrgetdriverproperties  PFIOMGRGETDRIVERPROPERTIES_IEC pfiomgrgetdriverproperties;
	#define EXT_iomgrgetdriverproperties  extern PFIOMGRGETDRIVERPROPERTIES_IEC pfiomgrgetdriverproperties;
	#define GET_iomgrgetdriverproperties(fl)  s_pfCMGetAPI2( "iomgrgetdriverproperties", (RTS_VOID_FCTPTR *)&pfiomgrgetdriverproperties, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xEC0D662D), 0x03050800)
	#define CAL_iomgrgetdriverproperties  pfiomgrgetdriverproperties
	#define CHK_iomgrgetdriverproperties  (pfiomgrgetdriverproperties != NULL)
	#define EXP_iomgrgetdriverproperties   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetdriverproperties", (RTS_UINTPTR)iomgrgetdriverproperties, 1, RTSITF_GET_SIGNATURE(0, 0xEC0D662D), 0x03050800) 
#endif


/**
 * <description>iomgrgetfirstdriverinstance</description>
 */
typedef struct tagiomgrgetfirstdriverinstance_struct
{
	RTS_IEC_DINT *pbIecDriver;			/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	IBase *IoMgrGetFirstDriverInstance;	/* VAR_OUTPUT */	
} iomgrgetfirstdriverinstance_struct;

void CDECL CDECL_EXT iomgrgetfirstdriverinstance(iomgrgetfirstdriverinstance_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRGETFIRSTDRIVERINSTANCE_IEC) (iomgrgetfirstdriverinstance_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRGETFIRSTDRIVERINSTANCE_NOTIMPLEMENTED)
	#define USE_iomgrgetfirstdriverinstance
	#define EXT_iomgrgetfirstdriverinstance
	#define GET_iomgrgetfirstdriverinstance(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrgetfirstdriverinstance(p0) 
	#define CHK_iomgrgetfirstdriverinstance  FALSE
	#define EXP_iomgrgetfirstdriverinstance  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrgetfirstdriverinstance
	#define EXT_iomgrgetfirstdriverinstance
	#define GET_iomgrgetfirstdriverinstance(fl)  CAL_CMGETAPI( "iomgrgetfirstdriverinstance" ) 
	#define CAL_iomgrgetfirstdriverinstance  iomgrgetfirstdriverinstance
	#define CHK_iomgrgetfirstdriverinstance  TRUE
	#define EXP_iomgrgetfirstdriverinstance  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetfirstdriverinstance", (RTS_UINTPTR)iomgrgetfirstdriverinstance, 1, RTSITF_GET_SIGNATURE(0, 0x7823BC76), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrgetfirstdriverinstance
	#define EXT_iomgrgetfirstdriverinstance
	#define GET_iomgrgetfirstdriverinstance(fl)  CAL_CMGETAPI( "iomgrgetfirstdriverinstance" ) 
	#define CAL_iomgrgetfirstdriverinstance  iomgrgetfirstdriverinstance
	#define CHK_iomgrgetfirstdriverinstance  TRUE
	#define EXP_iomgrgetfirstdriverinstance  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetfirstdriverinstance", (RTS_UINTPTR)iomgrgetfirstdriverinstance, 1, RTSITF_GET_SIGNATURE(0, 0x7823BC76), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrgetfirstdriverinstance
	#define EXT_CmpIoMgriomgrgetfirstdriverinstance
	#define GET_CmpIoMgriomgrgetfirstdriverinstance  ERR_OK
	#define CAL_CmpIoMgriomgrgetfirstdriverinstance  iomgrgetfirstdriverinstance
	#define CHK_CmpIoMgriomgrgetfirstdriverinstance  TRUE
	#define EXP_CmpIoMgriomgrgetfirstdriverinstance  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetfirstdriverinstance", (RTS_UINTPTR)iomgrgetfirstdriverinstance, 1, RTSITF_GET_SIGNATURE(0, 0x7823BC76), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrgetfirstdriverinstance
	#define EXT_iomgrgetfirstdriverinstance
	#define GET_iomgrgetfirstdriverinstance(fl)  CAL_CMGETAPI( "iomgrgetfirstdriverinstance" ) 
	#define CAL_iomgrgetfirstdriverinstance  iomgrgetfirstdriverinstance
	#define CHK_iomgrgetfirstdriverinstance  TRUE
	#define EXP_iomgrgetfirstdriverinstance  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetfirstdriverinstance", (RTS_UINTPTR)iomgrgetfirstdriverinstance, 1, RTSITF_GET_SIGNATURE(0, 0x7823BC76), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrgetfirstdriverinstance  PFIOMGRGETFIRSTDRIVERINSTANCE_IEC pfiomgrgetfirstdriverinstance;
	#define EXT_iomgrgetfirstdriverinstance  extern PFIOMGRGETFIRSTDRIVERINSTANCE_IEC pfiomgrgetfirstdriverinstance;
	#define GET_iomgrgetfirstdriverinstance(fl)  s_pfCMGetAPI2( "iomgrgetfirstdriverinstance", (RTS_VOID_FCTPTR *)&pfiomgrgetfirstdriverinstance, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x7823BC76), 0x03050800)
	#define CAL_iomgrgetfirstdriverinstance  pfiomgrgetfirstdriverinstance
	#define CHK_iomgrgetfirstdriverinstance  (pfiomgrgetfirstdriverinstance != NULL)
	#define EXP_iomgrgetfirstdriverinstance   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetfirstdriverinstance", (RTS_UINTPTR)iomgrgetfirstdriverinstance, 1, RTSITF_GET_SIGNATURE(0, 0x7823BC76), 0x03050800) 
#endif


/**
 * <description>iomgrgetmodulediagnosis</description>
 */
typedef struct tagiomgrgetmodulediagnosis_struct
{
	IoConfigConnector *pConnector;		/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrGetModuleDiagnosis;	/* VAR_OUTPUT */	
} iomgrgetmodulediagnosis_struct;

void CDECL CDECL_EXT iomgrgetmodulediagnosis(iomgrgetmodulediagnosis_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRGETMODULEDIAGNOSIS_IEC) (iomgrgetmodulediagnosis_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRGETMODULEDIAGNOSIS_NOTIMPLEMENTED)
	#define USE_iomgrgetmodulediagnosis
	#define EXT_iomgrgetmodulediagnosis
	#define GET_iomgrgetmodulediagnosis(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrgetmodulediagnosis(p0) 
	#define CHK_iomgrgetmodulediagnosis  FALSE
	#define EXP_iomgrgetmodulediagnosis  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrgetmodulediagnosis
	#define EXT_iomgrgetmodulediagnosis
	#define GET_iomgrgetmodulediagnosis(fl)  CAL_CMGETAPI( "iomgrgetmodulediagnosis" ) 
	#define CAL_iomgrgetmodulediagnosis  iomgrgetmodulediagnosis
	#define CHK_iomgrgetmodulediagnosis  TRUE
	#define EXP_iomgrgetmodulediagnosis  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetmodulediagnosis", (RTS_UINTPTR)iomgrgetmodulediagnosis, 1, RTSITF_GET_SIGNATURE(0, 0x5DA78ABA), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrgetmodulediagnosis
	#define EXT_iomgrgetmodulediagnosis
	#define GET_iomgrgetmodulediagnosis(fl)  CAL_CMGETAPI( "iomgrgetmodulediagnosis" ) 
	#define CAL_iomgrgetmodulediagnosis  iomgrgetmodulediagnosis
	#define CHK_iomgrgetmodulediagnosis  TRUE
	#define EXP_iomgrgetmodulediagnosis  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetmodulediagnosis", (RTS_UINTPTR)iomgrgetmodulediagnosis, 1, RTSITF_GET_SIGNATURE(0, 0x5DA78ABA), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrgetmodulediagnosis
	#define EXT_CmpIoMgriomgrgetmodulediagnosis
	#define GET_CmpIoMgriomgrgetmodulediagnosis  ERR_OK
	#define CAL_CmpIoMgriomgrgetmodulediagnosis  iomgrgetmodulediagnosis
	#define CHK_CmpIoMgriomgrgetmodulediagnosis  TRUE
	#define EXP_CmpIoMgriomgrgetmodulediagnosis  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetmodulediagnosis", (RTS_UINTPTR)iomgrgetmodulediagnosis, 1, RTSITF_GET_SIGNATURE(0, 0x5DA78ABA), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrgetmodulediagnosis
	#define EXT_iomgrgetmodulediagnosis
	#define GET_iomgrgetmodulediagnosis(fl)  CAL_CMGETAPI( "iomgrgetmodulediagnosis" ) 
	#define CAL_iomgrgetmodulediagnosis  iomgrgetmodulediagnosis
	#define CHK_iomgrgetmodulediagnosis  TRUE
	#define EXP_iomgrgetmodulediagnosis  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetmodulediagnosis", (RTS_UINTPTR)iomgrgetmodulediagnosis, 1, RTSITF_GET_SIGNATURE(0, 0x5DA78ABA), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrgetmodulediagnosis  PFIOMGRGETMODULEDIAGNOSIS_IEC pfiomgrgetmodulediagnosis;
	#define EXT_iomgrgetmodulediagnosis  extern PFIOMGRGETMODULEDIAGNOSIS_IEC pfiomgrgetmodulediagnosis;
	#define GET_iomgrgetmodulediagnosis(fl)  s_pfCMGetAPI2( "iomgrgetmodulediagnosis", (RTS_VOID_FCTPTR *)&pfiomgrgetmodulediagnosis, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x5DA78ABA), 0x03050800)
	#define CAL_iomgrgetmodulediagnosis  pfiomgrgetmodulediagnosis
	#define CHK_iomgrgetmodulediagnosis  (pfiomgrgetmodulediagnosis != NULL)
	#define EXP_iomgrgetmodulediagnosis   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetmodulediagnosis", (RTS_UINTPTR)iomgrgetmodulediagnosis, 1, RTSITF_GET_SIGNATURE(0, 0x5DA78ABA), 0x03050800) 
#endif


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

void CDECL CDECL_EXT iomgrgetnextdriverinstance(iomgrgetnextdriverinstance_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRGETNEXTDRIVERINSTANCE_IEC) (iomgrgetnextdriverinstance_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRGETNEXTDRIVERINSTANCE_NOTIMPLEMENTED)
	#define USE_iomgrgetnextdriverinstance
	#define EXT_iomgrgetnextdriverinstance
	#define GET_iomgrgetnextdriverinstance(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrgetnextdriverinstance(p0) 
	#define CHK_iomgrgetnextdriverinstance  FALSE
	#define EXP_iomgrgetnextdriverinstance  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrgetnextdriverinstance
	#define EXT_iomgrgetnextdriverinstance
	#define GET_iomgrgetnextdriverinstance(fl)  CAL_CMGETAPI( "iomgrgetnextdriverinstance" ) 
	#define CAL_iomgrgetnextdriverinstance  iomgrgetnextdriverinstance
	#define CHK_iomgrgetnextdriverinstance  TRUE
	#define EXP_iomgrgetnextdriverinstance  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetnextdriverinstance", (RTS_UINTPTR)iomgrgetnextdriverinstance, 1, RTSITF_GET_SIGNATURE(0, 0x0B47742F), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrgetnextdriverinstance
	#define EXT_iomgrgetnextdriverinstance
	#define GET_iomgrgetnextdriverinstance(fl)  CAL_CMGETAPI( "iomgrgetnextdriverinstance" ) 
	#define CAL_iomgrgetnextdriverinstance  iomgrgetnextdriverinstance
	#define CHK_iomgrgetnextdriverinstance  TRUE
	#define EXP_iomgrgetnextdriverinstance  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetnextdriverinstance", (RTS_UINTPTR)iomgrgetnextdriverinstance, 1, RTSITF_GET_SIGNATURE(0, 0x0B47742F), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrgetnextdriverinstance
	#define EXT_CmpIoMgriomgrgetnextdriverinstance
	#define GET_CmpIoMgriomgrgetnextdriverinstance  ERR_OK
	#define CAL_CmpIoMgriomgrgetnextdriverinstance  iomgrgetnextdriverinstance
	#define CHK_CmpIoMgriomgrgetnextdriverinstance  TRUE
	#define EXP_CmpIoMgriomgrgetnextdriverinstance  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetnextdriverinstance", (RTS_UINTPTR)iomgrgetnextdriverinstance, 1, RTSITF_GET_SIGNATURE(0, 0x0B47742F), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrgetnextdriverinstance
	#define EXT_iomgrgetnextdriverinstance
	#define GET_iomgrgetnextdriverinstance(fl)  CAL_CMGETAPI( "iomgrgetnextdriverinstance" ) 
	#define CAL_iomgrgetnextdriverinstance  iomgrgetnextdriverinstance
	#define CHK_iomgrgetnextdriverinstance  TRUE
	#define EXP_iomgrgetnextdriverinstance  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetnextdriverinstance", (RTS_UINTPTR)iomgrgetnextdriverinstance, 1, RTSITF_GET_SIGNATURE(0, 0x0B47742F), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrgetnextdriverinstance  PFIOMGRGETNEXTDRIVERINSTANCE_IEC pfiomgrgetnextdriverinstance;
	#define EXT_iomgrgetnextdriverinstance  extern PFIOMGRGETNEXTDRIVERINSTANCE_IEC pfiomgrgetnextdriverinstance;
	#define GET_iomgrgetnextdriverinstance(fl)  s_pfCMGetAPI2( "iomgrgetnextdriverinstance", (RTS_VOID_FCTPTR *)&pfiomgrgetnextdriverinstance, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x0B47742F), 0x03050800)
	#define CAL_iomgrgetnextdriverinstance  pfiomgrgetnextdriverinstance
	#define CHK_iomgrgetnextdriverinstance  (pfiomgrgetnextdriverinstance != NULL)
	#define EXP_iomgrgetnextdriverinstance   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrgetnextdriverinstance", (RTS_UINTPTR)iomgrgetnextdriverinstance, 1, RTSITF_GET_SIGNATURE(0, 0x0B47742F), 0x03050800) 
#endif


/**
 * <description>iomgridentify</description>
 */
typedef struct tagiomgridentify_struct
{
	IoConfigConnector *pConnector;		/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrIdentify;		/* VAR_OUTPUT */	
} iomgridentify_struct;

void CDECL CDECL_EXT iomgridentify(iomgridentify_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRIDENTIFY_IEC) (iomgridentify_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRIDENTIFY_NOTIMPLEMENTED)
	#define USE_iomgridentify
	#define EXT_iomgridentify
	#define GET_iomgridentify(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgridentify(p0) 
	#define CHK_iomgridentify  FALSE
	#define EXP_iomgridentify  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgridentify
	#define EXT_iomgridentify
	#define GET_iomgridentify(fl)  CAL_CMGETAPI( "iomgridentify" ) 
	#define CAL_iomgridentify  iomgridentify
	#define CHK_iomgridentify  TRUE
	#define EXP_iomgridentify  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgridentify", (RTS_UINTPTR)iomgridentify, 1, RTSITF_GET_SIGNATURE(0, 0xC48724F5), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgridentify
	#define EXT_iomgridentify
	#define GET_iomgridentify(fl)  CAL_CMGETAPI( "iomgridentify" ) 
	#define CAL_iomgridentify  iomgridentify
	#define CHK_iomgridentify  TRUE
	#define EXP_iomgridentify  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgridentify", (RTS_UINTPTR)iomgridentify, 1, RTSITF_GET_SIGNATURE(0, 0xC48724F5), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgridentify
	#define EXT_CmpIoMgriomgridentify
	#define GET_CmpIoMgriomgridentify  ERR_OK
	#define CAL_CmpIoMgriomgridentify  iomgridentify
	#define CHK_CmpIoMgriomgridentify  TRUE
	#define EXP_CmpIoMgriomgridentify  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgridentify", (RTS_UINTPTR)iomgridentify, 1, RTSITF_GET_SIGNATURE(0, 0xC48724F5), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgridentify
	#define EXT_iomgridentify
	#define GET_iomgridentify(fl)  CAL_CMGETAPI( "iomgridentify" ) 
	#define CAL_iomgridentify  iomgridentify
	#define CHK_iomgridentify  TRUE
	#define EXP_iomgridentify  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgridentify", (RTS_UINTPTR)iomgridentify, 1, RTSITF_GET_SIGNATURE(0, 0xC48724F5), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgridentify  PFIOMGRIDENTIFY_IEC pfiomgridentify;
	#define EXT_iomgridentify  extern PFIOMGRIDENTIFY_IEC pfiomgridentify;
	#define GET_iomgridentify(fl)  s_pfCMGetAPI2( "iomgridentify", (RTS_VOID_FCTPTR *)&pfiomgridentify, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xC48724F5), 0x03050800)
	#define CAL_iomgridentify  pfiomgridentify
	#define CHK_iomgridentify  (pfiomgridentify != NULL)
	#define EXP_iomgridentify   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgridentify", (RTS_UINTPTR)iomgridentify, 1, RTSITF_GET_SIGNATURE(0, 0xC48724F5), 0x03050800) 
#endif


/**
 * <description>iomgrreadinputs</description>
 */
typedef struct tagiomgrreadinputs_struct
{
	IoConfigTaskMap *pTaskMap;			/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrReadInputs;		/* VAR_OUTPUT */	
} iomgrreadinputs_struct;

void CDECL CDECL_EXT iomgrreadinputs(iomgrreadinputs_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRREADINPUTS_IEC) (iomgrreadinputs_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRREADINPUTS_NOTIMPLEMENTED)
	#define USE_iomgrreadinputs
	#define EXT_iomgrreadinputs
	#define GET_iomgrreadinputs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrreadinputs(p0) 
	#define CHK_iomgrreadinputs  FALSE
	#define EXP_iomgrreadinputs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrreadinputs
	#define EXT_iomgrreadinputs
	#define GET_iomgrreadinputs(fl)  CAL_CMGETAPI( "iomgrreadinputs" ) 
	#define CAL_iomgrreadinputs  iomgrreadinputs
	#define CHK_iomgrreadinputs  TRUE
	#define EXP_iomgrreadinputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrreadinputs", (RTS_UINTPTR)iomgrreadinputs, 1, RTSITF_GET_SIGNATURE(0, 0x3BCE0A42), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrreadinputs
	#define EXT_iomgrreadinputs
	#define GET_iomgrreadinputs(fl)  CAL_CMGETAPI( "iomgrreadinputs" ) 
	#define CAL_iomgrreadinputs  iomgrreadinputs
	#define CHK_iomgrreadinputs  TRUE
	#define EXP_iomgrreadinputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrreadinputs", (RTS_UINTPTR)iomgrreadinputs, 1, RTSITF_GET_SIGNATURE(0, 0x3BCE0A42), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrreadinputs
	#define EXT_CmpIoMgriomgrreadinputs
	#define GET_CmpIoMgriomgrreadinputs  ERR_OK
	#define CAL_CmpIoMgriomgrreadinputs  iomgrreadinputs
	#define CHK_CmpIoMgriomgrreadinputs  TRUE
	#define EXP_CmpIoMgriomgrreadinputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrreadinputs", (RTS_UINTPTR)iomgrreadinputs, 1, RTSITF_GET_SIGNATURE(0, 0x3BCE0A42), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrreadinputs
	#define EXT_iomgrreadinputs
	#define GET_iomgrreadinputs(fl)  CAL_CMGETAPI( "iomgrreadinputs" ) 
	#define CAL_iomgrreadinputs  iomgrreadinputs
	#define CHK_iomgrreadinputs  TRUE
	#define EXP_iomgrreadinputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrreadinputs", (RTS_UINTPTR)iomgrreadinputs, 1, RTSITF_GET_SIGNATURE(0, 0x3BCE0A42), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrreadinputs  PFIOMGRREADINPUTS_IEC pfiomgrreadinputs;
	#define EXT_iomgrreadinputs  extern PFIOMGRREADINPUTS_IEC pfiomgrreadinputs;
	#define GET_iomgrreadinputs(fl)  s_pfCMGetAPI2( "iomgrreadinputs", (RTS_VOID_FCTPTR *)&pfiomgrreadinputs, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x3BCE0A42), 0x03050800)
	#define CAL_iomgrreadinputs  pfiomgrreadinputs
	#define CHK_iomgrreadinputs  (pfiomgrreadinputs != NULL)
	#define EXP_iomgrreadinputs   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrreadinputs", (RTS_UINTPTR)iomgrreadinputs, 1, RTSITF_GET_SIGNATURE(0, 0x3BCE0A42), 0x03050800) 
#endif


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

void CDECL CDECL_EXT iomgrreadparameter(iomgrreadparameter_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRREADPARAMETER_IEC) (iomgrreadparameter_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRREADPARAMETER_NOTIMPLEMENTED)
	#define USE_iomgrreadparameter
	#define EXT_iomgrreadparameter
	#define GET_iomgrreadparameter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrreadparameter(p0) 
	#define CHK_iomgrreadparameter  FALSE
	#define EXP_iomgrreadparameter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrreadparameter
	#define EXT_iomgrreadparameter
	#define GET_iomgrreadparameter(fl)  CAL_CMGETAPI( "iomgrreadparameter" ) 
	#define CAL_iomgrreadparameter  iomgrreadparameter
	#define CHK_iomgrreadparameter  TRUE
	#define EXP_iomgrreadparameter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrreadparameter", (RTS_UINTPTR)iomgrreadparameter, 1, RTSITF_GET_SIGNATURE(0, 0xD37BF5DF), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrreadparameter
	#define EXT_iomgrreadparameter
	#define GET_iomgrreadparameter(fl)  CAL_CMGETAPI( "iomgrreadparameter" ) 
	#define CAL_iomgrreadparameter  iomgrreadparameter
	#define CHK_iomgrreadparameter  TRUE
	#define EXP_iomgrreadparameter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrreadparameter", (RTS_UINTPTR)iomgrreadparameter, 1, RTSITF_GET_SIGNATURE(0, 0xD37BF5DF), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrreadparameter
	#define EXT_CmpIoMgriomgrreadparameter
	#define GET_CmpIoMgriomgrreadparameter  ERR_OK
	#define CAL_CmpIoMgriomgrreadparameter  iomgrreadparameter
	#define CHK_CmpIoMgriomgrreadparameter  TRUE
	#define EXP_CmpIoMgriomgrreadparameter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrreadparameter", (RTS_UINTPTR)iomgrreadparameter, 1, RTSITF_GET_SIGNATURE(0, 0xD37BF5DF), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrreadparameter
	#define EXT_iomgrreadparameter
	#define GET_iomgrreadparameter(fl)  CAL_CMGETAPI( "iomgrreadparameter" ) 
	#define CAL_iomgrreadparameter  iomgrreadparameter
	#define CHK_iomgrreadparameter  TRUE
	#define EXP_iomgrreadparameter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrreadparameter", (RTS_UINTPTR)iomgrreadparameter, 1, RTSITF_GET_SIGNATURE(0, 0xD37BF5DF), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrreadparameter  PFIOMGRREADPARAMETER_IEC pfiomgrreadparameter;
	#define EXT_iomgrreadparameter  extern PFIOMGRREADPARAMETER_IEC pfiomgrreadparameter;
	#define GET_iomgrreadparameter(fl)  s_pfCMGetAPI2( "iomgrreadparameter", (RTS_VOID_FCTPTR *)&pfiomgrreadparameter, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xD37BF5DF), 0x03050800)
	#define CAL_iomgrreadparameter  pfiomgrreadparameter
	#define CHK_iomgrreadparameter  (pfiomgrreadparameter != NULL)
	#define EXP_iomgrreadparameter   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrreadparameter", (RTS_UINTPTR)iomgrreadparameter, 1, RTSITF_GET_SIGNATURE(0, 0xD37BF5DF), 0x03050800) 
#endif


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

void CDECL CDECL_EXT iomgrreconfigure(iomgrreconfigure_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRRECONFIGURE_IEC) (iomgrreconfigure_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRRECONFIGURE_NOTIMPLEMENTED)
	#define USE_iomgrreconfigure
	#define EXT_iomgrreconfigure
	#define GET_iomgrreconfigure(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrreconfigure(p0) 
	#define CHK_iomgrreconfigure  FALSE
	#define EXP_iomgrreconfigure  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrreconfigure
	#define EXT_iomgrreconfigure
	#define GET_iomgrreconfigure(fl)  CAL_CMGETAPI( "iomgrreconfigure" ) 
	#define CAL_iomgrreconfigure  iomgrreconfigure
	#define CHK_iomgrreconfigure  TRUE
	#define EXP_iomgrreconfigure  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrreconfigure", (RTS_UINTPTR)iomgrreconfigure, 1, RTSITF_GET_SIGNATURE(0x7DDF91C4, 0x731E5390), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrreconfigure
	#define EXT_iomgrreconfigure
	#define GET_iomgrreconfigure(fl)  CAL_CMGETAPI( "iomgrreconfigure" ) 
	#define CAL_iomgrreconfigure  iomgrreconfigure
	#define CHK_iomgrreconfigure  TRUE
	#define EXP_iomgrreconfigure  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrreconfigure", (RTS_UINTPTR)iomgrreconfigure, 1, RTSITF_GET_SIGNATURE(0x7DDF91C4, 0x731E5390), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrreconfigure
	#define EXT_CmpIoMgriomgrreconfigure
	#define GET_CmpIoMgriomgrreconfigure  ERR_OK
	#define CAL_CmpIoMgriomgrreconfigure  iomgrreconfigure
	#define CHK_CmpIoMgriomgrreconfigure  TRUE
	#define EXP_CmpIoMgriomgrreconfigure  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrreconfigure", (RTS_UINTPTR)iomgrreconfigure, 1, RTSITF_GET_SIGNATURE(0x7DDF91C4, 0x731E5390), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrreconfigure
	#define EXT_iomgrreconfigure
	#define GET_iomgrreconfigure(fl)  CAL_CMGETAPI( "iomgrreconfigure" ) 
	#define CAL_iomgrreconfigure  iomgrreconfigure
	#define CHK_iomgrreconfigure  TRUE
	#define EXP_iomgrreconfigure  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrreconfigure", (RTS_UINTPTR)iomgrreconfigure, 1, RTSITF_GET_SIGNATURE(0x7DDF91C4, 0x731E5390), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrreconfigure  PFIOMGRRECONFIGURE_IEC pfiomgrreconfigure;
	#define EXT_iomgrreconfigure  extern PFIOMGRRECONFIGURE_IEC pfiomgrreconfigure;
	#define GET_iomgrreconfigure(fl)  s_pfCMGetAPI2( "iomgrreconfigure", (RTS_VOID_FCTPTR *)&pfiomgrreconfigure, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0x7DDF91C4, 0x731E5390), 0x03050800)
	#define CAL_iomgrreconfigure  pfiomgrreconfigure
	#define CHK_iomgrreconfigure  (pfiomgrreconfigure != NULL)
	#define EXP_iomgrreconfigure   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrreconfigure", (RTS_UINTPTR)iomgrreconfigure, 1, RTSITF_GET_SIGNATURE(0x7DDF91C4, 0x731E5390), 0x03050800) 
#endif


/**
 * <description>iomgrregisterconfigapplication</description>
 */
typedef struct tagiomgrregisterconfigapplication_struct
{
	RTS_IEC_STRING *pszConfigApplication;	/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrRegisterConfigApplication;	/* VAR_OUTPUT */	
} iomgrregisterconfigapplication_struct;

void CDECL CDECL_EXT iomgrregisterconfigapplication(iomgrregisterconfigapplication_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRREGISTERCONFIGAPPLICATION_IEC) (iomgrregisterconfigapplication_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRREGISTERCONFIGAPPLICATION_NOTIMPLEMENTED)
	#define USE_iomgrregisterconfigapplication
	#define EXT_iomgrregisterconfigapplication
	#define GET_iomgrregisterconfigapplication(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrregisterconfigapplication(p0) 
	#define CHK_iomgrregisterconfigapplication  FALSE
	#define EXP_iomgrregisterconfigapplication  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrregisterconfigapplication
	#define EXT_iomgrregisterconfigapplication
	#define GET_iomgrregisterconfigapplication(fl)  CAL_CMGETAPI( "iomgrregisterconfigapplication" ) 
	#define CAL_iomgrregisterconfigapplication  iomgrregisterconfigapplication
	#define CHK_iomgrregisterconfigapplication  TRUE
	#define EXP_iomgrregisterconfigapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrregisterconfigapplication", (RTS_UINTPTR)iomgrregisterconfigapplication, 1, RTSITF_GET_SIGNATURE(0, 0xBEF7EAA8), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrregisterconfigapplication
	#define EXT_iomgrregisterconfigapplication
	#define GET_iomgrregisterconfigapplication(fl)  CAL_CMGETAPI( "iomgrregisterconfigapplication" ) 
	#define CAL_iomgrregisterconfigapplication  iomgrregisterconfigapplication
	#define CHK_iomgrregisterconfigapplication  TRUE
	#define EXP_iomgrregisterconfigapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrregisterconfigapplication", (RTS_UINTPTR)iomgrregisterconfigapplication, 1, RTSITF_GET_SIGNATURE(0, 0xBEF7EAA8), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrregisterconfigapplication
	#define EXT_CmpIoMgriomgrregisterconfigapplication
	#define GET_CmpIoMgriomgrregisterconfigapplication  ERR_OK
	#define CAL_CmpIoMgriomgrregisterconfigapplication  iomgrregisterconfigapplication
	#define CHK_CmpIoMgriomgrregisterconfigapplication  TRUE
	#define EXP_CmpIoMgriomgrregisterconfigapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrregisterconfigapplication", (RTS_UINTPTR)iomgrregisterconfigapplication, 1, RTSITF_GET_SIGNATURE(0, 0xBEF7EAA8), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrregisterconfigapplication
	#define EXT_iomgrregisterconfigapplication
	#define GET_iomgrregisterconfigapplication(fl)  CAL_CMGETAPI( "iomgrregisterconfigapplication" ) 
	#define CAL_iomgrregisterconfigapplication  iomgrregisterconfigapplication
	#define CHK_iomgrregisterconfigapplication  TRUE
	#define EXP_iomgrregisterconfigapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrregisterconfigapplication", (RTS_UINTPTR)iomgrregisterconfigapplication, 1, RTSITF_GET_SIGNATURE(0, 0xBEF7EAA8), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrregisterconfigapplication  PFIOMGRREGISTERCONFIGAPPLICATION_IEC pfiomgrregisterconfigapplication;
	#define EXT_iomgrregisterconfigapplication  extern PFIOMGRREGISTERCONFIGAPPLICATION_IEC pfiomgrregisterconfigapplication;
	#define GET_iomgrregisterconfigapplication(fl)  s_pfCMGetAPI2( "iomgrregisterconfigapplication", (RTS_VOID_FCTPTR *)&pfiomgrregisterconfigapplication, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xBEF7EAA8), 0x03050800)
	#define CAL_iomgrregisterconfigapplication  pfiomgrregisterconfigapplication
	#define CHK_iomgrregisterconfigapplication  (pfiomgrregisterconfigapplication != NULL)
	#define EXP_iomgrregisterconfigapplication   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrregisterconfigapplication", (RTS_UINTPTR)iomgrregisterconfigapplication, 1, RTSITF_GET_SIGNATURE(0, 0xBEF7EAA8), 0x03050800) 
#endif


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

void CDECL CDECL_EXT iomgrregisterinstance2(iomgrregisterinstance2_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRREGISTERINSTANCE2_IEC) (iomgrregisterinstance2_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRREGISTERINSTANCE2_NOTIMPLEMENTED)
	#define USE_iomgrregisterinstance2
	#define EXT_iomgrregisterinstance2
	#define GET_iomgrregisterinstance2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrregisterinstance2(p0) 
	#define CHK_iomgrregisterinstance2  FALSE
	#define EXP_iomgrregisterinstance2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrregisterinstance2
	#define EXT_iomgrregisterinstance2
	#define GET_iomgrregisterinstance2(fl)  CAL_CMGETAPI( "iomgrregisterinstance2" ) 
	#define CAL_iomgrregisterinstance2  iomgrregisterinstance2
	#define CHK_iomgrregisterinstance2  TRUE
	#define EXP_iomgrregisterinstance2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrregisterinstance2", (RTS_UINTPTR)iomgrregisterinstance2, 1, RTSITF_GET_SIGNATURE(0, 0x4219F9A3), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrregisterinstance2
	#define EXT_iomgrregisterinstance2
	#define GET_iomgrregisterinstance2(fl)  CAL_CMGETAPI( "iomgrregisterinstance2" ) 
	#define CAL_iomgrregisterinstance2  iomgrregisterinstance2
	#define CHK_iomgrregisterinstance2  TRUE
	#define EXP_iomgrregisterinstance2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrregisterinstance2", (RTS_UINTPTR)iomgrregisterinstance2, 1, RTSITF_GET_SIGNATURE(0, 0x4219F9A3), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrregisterinstance2
	#define EXT_CmpIoMgriomgrregisterinstance2
	#define GET_CmpIoMgriomgrregisterinstance2  ERR_OK
	#define CAL_CmpIoMgriomgrregisterinstance2  iomgrregisterinstance2
	#define CHK_CmpIoMgriomgrregisterinstance2  TRUE
	#define EXP_CmpIoMgriomgrregisterinstance2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrregisterinstance2", (RTS_UINTPTR)iomgrregisterinstance2, 1, RTSITF_GET_SIGNATURE(0, 0x4219F9A3), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrregisterinstance2
	#define EXT_iomgrregisterinstance2
	#define GET_iomgrregisterinstance2(fl)  CAL_CMGETAPI( "iomgrregisterinstance2" ) 
	#define CAL_iomgrregisterinstance2  iomgrregisterinstance2
	#define CHK_iomgrregisterinstance2  TRUE
	#define EXP_iomgrregisterinstance2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrregisterinstance2", (RTS_UINTPTR)iomgrregisterinstance2, 1, RTSITF_GET_SIGNATURE(0, 0x4219F9A3), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrregisterinstance2  PFIOMGRREGISTERINSTANCE2_IEC pfiomgrregisterinstance2;
	#define EXT_iomgrregisterinstance2  extern PFIOMGRREGISTERINSTANCE2_IEC pfiomgrregisterinstance2;
	#define GET_iomgrregisterinstance2(fl)  s_pfCMGetAPI2( "iomgrregisterinstance2", (RTS_VOID_FCTPTR *)&pfiomgrregisterinstance2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x4219F9A3), 0x03050800)
	#define CAL_iomgrregisterinstance2  pfiomgrregisterinstance2
	#define CHK_iomgrregisterinstance2  (pfiomgrregisterinstance2 != NULL)
	#define EXP_iomgrregisterinstance2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrregisterinstance2", (RTS_UINTPTR)iomgrregisterinstance2, 1, RTSITF_GET_SIGNATURE(0, 0x4219F9A3), 0x03050800) 
#endif


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

void CDECL CDECL_EXT iomgrscanmodules(iomgrscanmodules_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRSCANMODULES_IEC) (iomgrscanmodules_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRSCANMODULES_NOTIMPLEMENTED)
	#define USE_iomgrscanmodules
	#define EXT_iomgrscanmodules
	#define GET_iomgrscanmodules(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrscanmodules(p0) 
	#define CHK_iomgrscanmodules  FALSE
	#define EXP_iomgrscanmodules  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrscanmodules
	#define EXT_iomgrscanmodules
	#define GET_iomgrscanmodules(fl)  CAL_CMGETAPI( "iomgrscanmodules" ) 
	#define CAL_iomgrscanmodules  iomgrscanmodules
	#define CHK_iomgrscanmodules  TRUE
	#define EXP_iomgrscanmodules  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrscanmodules", (RTS_UINTPTR)iomgrscanmodules, 1, RTSITF_GET_SIGNATURE(0, 0xF31DBCAE), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrscanmodules
	#define EXT_iomgrscanmodules
	#define GET_iomgrscanmodules(fl)  CAL_CMGETAPI( "iomgrscanmodules" ) 
	#define CAL_iomgrscanmodules  iomgrscanmodules
	#define CHK_iomgrscanmodules  TRUE
	#define EXP_iomgrscanmodules  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrscanmodules", (RTS_UINTPTR)iomgrscanmodules, 1, RTSITF_GET_SIGNATURE(0, 0xF31DBCAE), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrscanmodules
	#define EXT_CmpIoMgriomgrscanmodules
	#define GET_CmpIoMgriomgrscanmodules  ERR_OK
	#define CAL_CmpIoMgriomgrscanmodules  iomgrscanmodules
	#define CHK_CmpIoMgriomgrscanmodules  TRUE
	#define EXP_CmpIoMgriomgrscanmodules  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrscanmodules", (RTS_UINTPTR)iomgrscanmodules, 1, RTSITF_GET_SIGNATURE(0, 0xF31DBCAE), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrscanmodules
	#define EXT_iomgrscanmodules
	#define GET_iomgrscanmodules(fl)  CAL_CMGETAPI( "iomgrscanmodules" ) 
	#define CAL_iomgrscanmodules  iomgrscanmodules
	#define CHK_iomgrscanmodules  TRUE
	#define EXP_iomgrscanmodules  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrscanmodules", (RTS_UINTPTR)iomgrscanmodules, 1, RTSITF_GET_SIGNATURE(0, 0xF31DBCAE), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrscanmodules  PFIOMGRSCANMODULES_IEC pfiomgrscanmodules;
	#define EXT_iomgrscanmodules  extern PFIOMGRSCANMODULES_IEC pfiomgrscanmodules;
	#define GET_iomgrscanmodules(fl)  s_pfCMGetAPI2( "iomgrscanmodules", (RTS_VOID_FCTPTR *)&pfiomgrscanmodules, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xF31DBCAE), 0x03050800)
	#define CAL_iomgrscanmodules  pfiomgrscanmodules
	#define CHK_iomgrscanmodules  (pfiomgrscanmodules != NULL)
	#define EXP_iomgrscanmodules   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrscanmodules", (RTS_UINTPTR)iomgrscanmodules, 1, RTSITF_GET_SIGNATURE(0, 0xF31DBCAE), 0x03050800) 
#endif


/**
 * <description>iomgrsetdriverproperties</description>
 */
typedef struct tagiomgrsetdriverproperties_struct
{
	RTS_IEC_HANDLE hIoDrv;				/* VAR_INPUT */	
	RTS_IEC_DWORD ulProperties;			/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrSetDriverProperties;	/* VAR_OUTPUT */	
} iomgrsetdriverproperties_struct;

void CDECL CDECL_EXT iomgrsetdriverproperties(iomgrsetdriverproperties_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRSETDRIVERPROPERTIES_IEC) (iomgrsetdriverproperties_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRSETDRIVERPROPERTIES_NOTIMPLEMENTED)
	#define USE_iomgrsetdriverproperties
	#define EXT_iomgrsetdriverproperties
	#define GET_iomgrsetdriverproperties(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrsetdriverproperties(p0) 
	#define CHK_iomgrsetdriverproperties  FALSE
	#define EXP_iomgrsetdriverproperties  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrsetdriverproperties
	#define EXT_iomgrsetdriverproperties
	#define GET_iomgrsetdriverproperties(fl)  CAL_CMGETAPI( "iomgrsetdriverproperties" ) 
	#define CAL_iomgrsetdriverproperties  iomgrsetdriverproperties
	#define CHK_iomgrsetdriverproperties  TRUE
	#define EXP_iomgrsetdriverproperties  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrsetdriverproperties", (RTS_UINTPTR)iomgrsetdriverproperties, 1, RTSITF_GET_SIGNATURE(0, 0x607A5D95), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrsetdriverproperties
	#define EXT_iomgrsetdriverproperties
	#define GET_iomgrsetdriverproperties(fl)  CAL_CMGETAPI( "iomgrsetdriverproperties" ) 
	#define CAL_iomgrsetdriverproperties  iomgrsetdriverproperties
	#define CHK_iomgrsetdriverproperties  TRUE
	#define EXP_iomgrsetdriverproperties  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrsetdriverproperties", (RTS_UINTPTR)iomgrsetdriverproperties, 1, RTSITF_GET_SIGNATURE(0, 0x607A5D95), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrsetdriverproperties
	#define EXT_CmpIoMgriomgrsetdriverproperties
	#define GET_CmpIoMgriomgrsetdriverproperties  ERR_OK
	#define CAL_CmpIoMgriomgrsetdriverproperties  iomgrsetdriverproperties
	#define CHK_CmpIoMgriomgrsetdriverproperties  TRUE
	#define EXP_CmpIoMgriomgrsetdriverproperties  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrsetdriverproperties", (RTS_UINTPTR)iomgrsetdriverproperties, 1, RTSITF_GET_SIGNATURE(0, 0x607A5D95), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrsetdriverproperties
	#define EXT_iomgrsetdriverproperties
	#define GET_iomgrsetdriverproperties(fl)  CAL_CMGETAPI( "iomgrsetdriverproperties" ) 
	#define CAL_iomgrsetdriverproperties  iomgrsetdriverproperties
	#define CHK_iomgrsetdriverproperties  TRUE
	#define EXP_iomgrsetdriverproperties  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrsetdriverproperties", (RTS_UINTPTR)iomgrsetdriverproperties, 1, RTSITF_GET_SIGNATURE(0, 0x607A5D95), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrsetdriverproperties  PFIOMGRSETDRIVERPROPERTIES_IEC pfiomgrsetdriverproperties;
	#define EXT_iomgrsetdriverproperties  extern PFIOMGRSETDRIVERPROPERTIES_IEC pfiomgrsetdriverproperties;
	#define GET_iomgrsetdriverproperties(fl)  s_pfCMGetAPI2( "iomgrsetdriverproperties", (RTS_VOID_FCTPTR *)&pfiomgrsetdriverproperties, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x607A5D95), 0x03050800)
	#define CAL_iomgrsetdriverproperties  pfiomgrsetdriverproperties
	#define CHK_iomgrsetdriverproperties  (pfiomgrsetdriverproperties != NULL)
	#define EXP_iomgrsetdriverproperties   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrsetdriverproperties", (RTS_UINTPTR)iomgrsetdriverproperties, 1, RTSITF_GET_SIGNATURE(0, 0x607A5D95), 0x03050800) 
#endif


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

void CDECL CDECL_EXT iomgrsetdriverproperty(iomgrsetdriverproperty_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRSETDRIVERPROPERTY_IEC) (iomgrsetdriverproperty_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRSETDRIVERPROPERTY_NOTIMPLEMENTED)
	#define USE_iomgrsetdriverproperty
	#define EXT_iomgrsetdriverproperty
	#define GET_iomgrsetdriverproperty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrsetdriverproperty(p0) 
	#define CHK_iomgrsetdriverproperty  FALSE
	#define EXP_iomgrsetdriverproperty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrsetdriverproperty
	#define EXT_iomgrsetdriverproperty
	#define GET_iomgrsetdriverproperty(fl)  CAL_CMGETAPI( "iomgrsetdriverproperty" ) 
	#define CAL_iomgrsetdriverproperty  iomgrsetdriverproperty
	#define CHK_iomgrsetdriverproperty  TRUE
	#define EXP_iomgrsetdriverproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrsetdriverproperty", (RTS_UINTPTR)iomgrsetdriverproperty, 1, RTSITF_GET_SIGNATURE(0, 0x936FC5C4), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrsetdriverproperty
	#define EXT_iomgrsetdriverproperty
	#define GET_iomgrsetdriverproperty(fl)  CAL_CMGETAPI( "iomgrsetdriverproperty" ) 
	#define CAL_iomgrsetdriverproperty  iomgrsetdriverproperty
	#define CHK_iomgrsetdriverproperty  TRUE
	#define EXP_iomgrsetdriverproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrsetdriverproperty", (RTS_UINTPTR)iomgrsetdriverproperty, 1, RTSITF_GET_SIGNATURE(0, 0x936FC5C4), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrsetdriverproperty
	#define EXT_CmpIoMgriomgrsetdriverproperty
	#define GET_CmpIoMgriomgrsetdriverproperty  ERR_OK
	#define CAL_CmpIoMgriomgrsetdriverproperty  iomgrsetdriverproperty
	#define CHK_CmpIoMgriomgrsetdriverproperty  TRUE
	#define EXP_CmpIoMgriomgrsetdriverproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrsetdriverproperty", (RTS_UINTPTR)iomgrsetdriverproperty, 1, RTSITF_GET_SIGNATURE(0, 0x936FC5C4), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrsetdriverproperty
	#define EXT_iomgrsetdriverproperty
	#define GET_iomgrsetdriverproperty(fl)  CAL_CMGETAPI( "iomgrsetdriverproperty" ) 
	#define CAL_iomgrsetdriverproperty  iomgrsetdriverproperty
	#define CHK_iomgrsetdriverproperty  TRUE
	#define EXP_iomgrsetdriverproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrsetdriverproperty", (RTS_UINTPTR)iomgrsetdriverproperty, 1, RTSITF_GET_SIGNATURE(0, 0x936FC5C4), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrsetdriverproperty  PFIOMGRSETDRIVERPROPERTY_IEC pfiomgrsetdriverproperty;
	#define EXT_iomgrsetdriverproperty  extern PFIOMGRSETDRIVERPROPERTY_IEC pfiomgrsetdriverproperty;
	#define GET_iomgrsetdriverproperty(fl)  s_pfCMGetAPI2( "iomgrsetdriverproperty", (RTS_VOID_FCTPTR *)&pfiomgrsetdriverproperty, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x936FC5C4), 0x03050800)
	#define CAL_iomgrsetdriverproperty  pfiomgrsetdriverproperty
	#define CHK_iomgrsetdriverproperty  (pfiomgrsetdriverproperty != NULL)
	#define EXP_iomgrsetdriverproperty   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrsetdriverproperty", (RTS_UINTPTR)iomgrsetdriverproperty, 1, RTSITF_GET_SIGNATURE(0, 0x936FC5C4), 0x03050800) 
#endif


/**
 * <description>iomgrstartbuscycle</description>
 */
typedef struct tagiomgrstartbuscycle_struct
{
	IoConfigConnector *pConnector;		/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrStartBusCycle;	/* VAR_OUTPUT */	
} iomgrstartbuscycle_struct;

void CDECL CDECL_EXT iomgrstartbuscycle(iomgrstartbuscycle_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRSTARTBUSCYCLE_IEC) (iomgrstartbuscycle_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRSTARTBUSCYCLE_NOTIMPLEMENTED)
	#define USE_iomgrstartbuscycle
	#define EXT_iomgrstartbuscycle
	#define GET_iomgrstartbuscycle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrstartbuscycle(p0) 
	#define CHK_iomgrstartbuscycle  FALSE
	#define EXP_iomgrstartbuscycle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrstartbuscycle
	#define EXT_iomgrstartbuscycle
	#define GET_iomgrstartbuscycle(fl)  CAL_CMGETAPI( "iomgrstartbuscycle" ) 
	#define CAL_iomgrstartbuscycle  iomgrstartbuscycle
	#define CHK_iomgrstartbuscycle  TRUE
	#define EXP_iomgrstartbuscycle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrstartbuscycle", (RTS_UINTPTR)iomgrstartbuscycle, 1, RTSITF_GET_SIGNATURE(0, 0x09EEEC27), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrstartbuscycle
	#define EXT_iomgrstartbuscycle
	#define GET_iomgrstartbuscycle(fl)  CAL_CMGETAPI( "iomgrstartbuscycle" ) 
	#define CAL_iomgrstartbuscycle  iomgrstartbuscycle
	#define CHK_iomgrstartbuscycle  TRUE
	#define EXP_iomgrstartbuscycle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrstartbuscycle", (RTS_UINTPTR)iomgrstartbuscycle, 1, RTSITF_GET_SIGNATURE(0, 0x09EEEC27), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrstartbuscycle
	#define EXT_CmpIoMgriomgrstartbuscycle
	#define GET_CmpIoMgriomgrstartbuscycle  ERR_OK
	#define CAL_CmpIoMgriomgrstartbuscycle  iomgrstartbuscycle
	#define CHK_CmpIoMgriomgrstartbuscycle  TRUE
	#define EXP_CmpIoMgriomgrstartbuscycle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrstartbuscycle", (RTS_UINTPTR)iomgrstartbuscycle, 1, RTSITF_GET_SIGNATURE(0, 0x09EEEC27), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrstartbuscycle
	#define EXT_iomgrstartbuscycle
	#define GET_iomgrstartbuscycle(fl)  CAL_CMGETAPI( "iomgrstartbuscycle" ) 
	#define CAL_iomgrstartbuscycle  iomgrstartbuscycle
	#define CHK_iomgrstartbuscycle  TRUE
	#define EXP_iomgrstartbuscycle  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrstartbuscycle", (RTS_UINTPTR)iomgrstartbuscycle, 1, RTSITF_GET_SIGNATURE(0, 0x09EEEC27), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrstartbuscycle  PFIOMGRSTARTBUSCYCLE_IEC pfiomgrstartbuscycle;
	#define EXT_iomgrstartbuscycle  extern PFIOMGRSTARTBUSCYCLE_IEC pfiomgrstartbuscycle;
	#define GET_iomgrstartbuscycle(fl)  s_pfCMGetAPI2( "iomgrstartbuscycle", (RTS_VOID_FCTPTR *)&pfiomgrstartbuscycle, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x09EEEC27), 0x03050800)
	#define CAL_iomgrstartbuscycle  pfiomgrstartbuscycle
	#define CHK_iomgrstartbuscycle  (pfiomgrstartbuscycle != NULL)
	#define EXP_iomgrstartbuscycle   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrstartbuscycle", (RTS_UINTPTR)iomgrstartbuscycle, 1, RTSITF_GET_SIGNATURE(0, 0x09EEEC27), 0x03050800) 
#endif


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

void CDECL CDECL_EXT iomgrstartbuscycle2(iomgrstartbuscycle2_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRSTARTBUSCYCLE2_IEC) (iomgrstartbuscycle2_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRSTARTBUSCYCLE2_NOTIMPLEMENTED)
	#define USE_iomgrstartbuscycle2
	#define EXT_iomgrstartbuscycle2
	#define GET_iomgrstartbuscycle2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrstartbuscycle2(p0) 
	#define CHK_iomgrstartbuscycle2  FALSE
	#define EXP_iomgrstartbuscycle2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrstartbuscycle2
	#define EXT_iomgrstartbuscycle2
	#define GET_iomgrstartbuscycle2(fl)  CAL_CMGETAPI( "iomgrstartbuscycle2" ) 
	#define CAL_iomgrstartbuscycle2  iomgrstartbuscycle2
	#define CHK_iomgrstartbuscycle2  TRUE
	#define EXP_iomgrstartbuscycle2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrstartbuscycle2", (RTS_UINTPTR)iomgrstartbuscycle2, 1, RTSITF_GET_SIGNATURE(0, 0x8AB99A18), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrstartbuscycle2
	#define EXT_iomgrstartbuscycle2
	#define GET_iomgrstartbuscycle2(fl)  CAL_CMGETAPI( "iomgrstartbuscycle2" ) 
	#define CAL_iomgrstartbuscycle2  iomgrstartbuscycle2
	#define CHK_iomgrstartbuscycle2  TRUE
	#define EXP_iomgrstartbuscycle2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrstartbuscycle2", (RTS_UINTPTR)iomgrstartbuscycle2, 1, RTSITF_GET_SIGNATURE(0, 0x8AB99A18), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrstartbuscycle2
	#define EXT_CmpIoMgriomgrstartbuscycle2
	#define GET_CmpIoMgriomgrstartbuscycle2  ERR_OK
	#define CAL_CmpIoMgriomgrstartbuscycle2  iomgrstartbuscycle2
	#define CHK_CmpIoMgriomgrstartbuscycle2  TRUE
	#define EXP_CmpIoMgriomgrstartbuscycle2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrstartbuscycle2", (RTS_UINTPTR)iomgrstartbuscycle2, 1, RTSITF_GET_SIGNATURE(0, 0x8AB99A18), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrstartbuscycle2
	#define EXT_iomgrstartbuscycle2
	#define GET_iomgrstartbuscycle2(fl)  CAL_CMGETAPI( "iomgrstartbuscycle2" ) 
	#define CAL_iomgrstartbuscycle2  iomgrstartbuscycle2
	#define CHK_iomgrstartbuscycle2  TRUE
	#define EXP_iomgrstartbuscycle2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrstartbuscycle2", (RTS_UINTPTR)iomgrstartbuscycle2, 1, RTSITF_GET_SIGNATURE(0, 0x8AB99A18), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrstartbuscycle2  PFIOMGRSTARTBUSCYCLE2_IEC pfiomgrstartbuscycle2;
	#define EXT_iomgrstartbuscycle2  extern PFIOMGRSTARTBUSCYCLE2_IEC pfiomgrstartbuscycle2;
	#define GET_iomgrstartbuscycle2(fl)  s_pfCMGetAPI2( "iomgrstartbuscycle2", (RTS_VOID_FCTPTR *)&pfiomgrstartbuscycle2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x8AB99A18), 0x03050800)
	#define CAL_iomgrstartbuscycle2  pfiomgrstartbuscycle2
	#define CHK_iomgrstartbuscycle2  (pfiomgrstartbuscycle2 != NULL)
	#define EXP_iomgrstartbuscycle2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrstartbuscycle2", (RTS_UINTPTR)iomgrstartbuscycle2, 1, RTSITF_GET_SIGNATURE(0, 0x8AB99A18), 0x03050800) 
#endif


/**
 * <description>iomgrunregisterconfigapplication</description>
 */
typedef struct tagiomgrunregisterconfigapplication_struct
{
	RTS_IEC_STRING *pszConfigApplication;	/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrUnregisterConfigApplication;	/* VAR_OUTPUT */	
} iomgrunregisterconfigapplication_struct;

void CDECL CDECL_EXT iomgrunregisterconfigapplication(iomgrunregisterconfigapplication_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRUNREGISTERCONFIGAPPLICATION_IEC) (iomgrunregisterconfigapplication_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRUNREGISTERCONFIGAPPLICATION_NOTIMPLEMENTED)
	#define USE_iomgrunregisterconfigapplication
	#define EXT_iomgrunregisterconfigapplication
	#define GET_iomgrunregisterconfigapplication(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrunregisterconfigapplication(p0) 
	#define CHK_iomgrunregisterconfigapplication  FALSE
	#define EXP_iomgrunregisterconfigapplication  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrunregisterconfigapplication
	#define EXT_iomgrunregisterconfigapplication
	#define GET_iomgrunregisterconfigapplication(fl)  CAL_CMGETAPI( "iomgrunregisterconfigapplication" ) 
	#define CAL_iomgrunregisterconfigapplication  iomgrunregisterconfigapplication
	#define CHK_iomgrunregisterconfigapplication  TRUE
	#define EXP_iomgrunregisterconfigapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrunregisterconfigapplication", (RTS_UINTPTR)iomgrunregisterconfigapplication, 1, RTSITF_GET_SIGNATURE(0, 0xECB18F2E), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrunregisterconfigapplication
	#define EXT_iomgrunregisterconfigapplication
	#define GET_iomgrunregisterconfigapplication(fl)  CAL_CMGETAPI( "iomgrunregisterconfigapplication" ) 
	#define CAL_iomgrunregisterconfigapplication  iomgrunregisterconfigapplication
	#define CHK_iomgrunregisterconfigapplication  TRUE
	#define EXP_iomgrunregisterconfigapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrunregisterconfigapplication", (RTS_UINTPTR)iomgrunregisterconfigapplication, 1, RTSITF_GET_SIGNATURE(0, 0xECB18F2E), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrunregisterconfigapplication
	#define EXT_CmpIoMgriomgrunregisterconfigapplication
	#define GET_CmpIoMgriomgrunregisterconfigapplication  ERR_OK
	#define CAL_CmpIoMgriomgrunregisterconfigapplication  iomgrunregisterconfigapplication
	#define CHK_CmpIoMgriomgrunregisterconfigapplication  TRUE
	#define EXP_CmpIoMgriomgrunregisterconfigapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrunregisterconfigapplication", (RTS_UINTPTR)iomgrunregisterconfigapplication, 1, RTSITF_GET_SIGNATURE(0, 0xECB18F2E), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrunregisterconfigapplication
	#define EXT_iomgrunregisterconfigapplication
	#define GET_iomgrunregisterconfigapplication(fl)  CAL_CMGETAPI( "iomgrunregisterconfigapplication" ) 
	#define CAL_iomgrunregisterconfigapplication  iomgrunregisterconfigapplication
	#define CHK_iomgrunregisterconfigapplication  TRUE
	#define EXP_iomgrunregisterconfigapplication  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrunregisterconfigapplication", (RTS_UINTPTR)iomgrunregisterconfigapplication, 1, RTSITF_GET_SIGNATURE(0, 0xECB18F2E), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrunregisterconfigapplication  PFIOMGRUNREGISTERCONFIGAPPLICATION_IEC pfiomgrunregisterconfigapplication;
	#define EXT_iomgrunregisterconfigapplication  extern PFIOMGRUNREGISTERCONFIGAPPLICATION_IEC pfiomgrunregisterconfigapplication;
	#define GET_iomgrunregisterconfigapplication(fl)  s_pfCMGetAPI2( "iomgrunregisterconfigapplication", (RTS_VOID_FCTPTR *)&pfiomgrunregisterconfigapplication, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xECB18F2E), 0x03050800)
	#define CAL_iomgrunregisterconfigapplication  pfiomgrunregisterconfigapplication
	#define CHK_iomgrunregisterconfigapplication  (pfiomgrunregisterconfigapplication != NULL)
	#define EXP_iomgrunregisterconfigapplication   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrunregisterconfigapplication", (RTS_UINTPTR)iomgrunregisterconfigapplication, 1, RTSITF_GET_SIGNATURE(0, 0xECB18F2E), 0x03050800) 
#endif


/**
 * <description>iomgrunregisterinstance</description>
 */
typedef struct tagiomgrunregisterinstance_struct
{
	RTS_IEC_HANDLE hInterface;			/* VAR_INPUT */	
	RTS_IEC_RESULT IoMgrUnregisterInstance;	/* VAR_OUTPUT */	
} iomgrunregisterinstance_struct;

void CDECL CDECL_EXT iomgrunregisterinstance(iomgrunregisterinstance_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRUNREGISTERINSTANCE_IEC) (iomgrunregisterinstance_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRUNREGISTERINSTANCE_NOTIMPLEMENTED)
	#define USE_iomgrunregisterinstance
	#define EXT_iomgrunregisterinstance
	#define GET_iomgrunregisterinstance(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrunregisterinstance(p0) 
	#define CHK_iomgrunregisterinstance  FALSE
	#define EXP_iomgrunregisterinstance  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrunregisterinstance
	#define EXT_iomgrunregisterinstance
	#define GET_iomgrunregisterinstance(fl)  CAL_CMGETAPI( "iomgrunregisterinstance" ) 
	#define CAL_iomgrunregisterinstance  iomgrunregisterinstance
	#define CHK_iomgrunregisterinstance  TRUE
	#define EXP_iomgrunregisterinstance  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrunregisterinstance", (RTS_UINTPTR)iomgrunregisterinstance, 1, RTSITF_GET_SIGNATURE(0, 0x830B7CC7), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrunregisterinstance
	#define EXT_iomgrunregisterinstance
	#define GET_iomgrunregisterinstance(fl)  CAL_CMGETAPI( "iomgrunregisterinstance" ) 
	#define CAL_iomgrunregisterinstance  iomgrunregisterinstance
	#define CHK_iomgrunregisterinstance  TRUE
	#define EXP_iomgrunregisterinstance  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrunregisterinstance", (RTS_UINTPTR)iomgrunregisterinstance, 1, RTSITF_GET_SIGNATURE(0, 0x830B7CC7), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrunregisterinstance
	#define EXT_CmpIoMgriomgrunregisterinstance
	#define GET_CmpIoMgriomgrunregisterinstance  ERR_OK
	#define CAL_CmpIoMgriomgrunregisterinstance  iomgrunregisterinstance
	#define CHK_CmpIoMgriomgrunregisterinstance  TRUE
	#define EXP_CmpIoMgriomgrunregisterinstance  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrunregisterinstance", (RTS_UINTPTR)iomgrunregisterinstance, 1, RTSITF_GET_SIGNATURE(0, 0x830B7CC7), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrunregisterinstance
	#define EXT_iomgrunregisterinstance
	#define GET_iomgrunregisterinstance(fl)  CAL_CMGETAPI( "iomgrunregisterinstance" ) 
	#define CAL_iomgrunregisterinstance  iomgrunregisterinstance
	#define CHK_iomgrunregisterinstance  TRUE
	#define EXP_iomgrunregisterinstance  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrunregisterinstance", (RTS_UINTPTR)iomgrunregisterinstance, 1, RTSITF_GET_SIGNATURE(0, 0x830B7CC7), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrunregisterinstance  PFIOMGRUNREGISTERINSTANCE_IEC pfiomgrunregisterinstance;
	#define EXT_iomgrunregisterinstance  extern PFIOMGRUNREGISTERINSTANCE_IEC pfiomgrunregisterinstance;
	#define GET_iomgrunregisterinstance(fl)  s_pfCMGetAPI2( "iomgrunregisterinstance", (RTS_VOID_FCTPTR *)&pfiomgrunregisterinstance, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x830B7CC7), 0x03050800)
	#define CAL_iomgrunregisterinstance  pfiomgrunregisterinstance
	#define CHK_iomgrunregisterinstance  (pfiomgrunregisterinstance != NULL)
	#define EXP_iomgrunregisterinstance   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrunregisterinstance", (RTS_UINTPTR)iomgrunregisterinstance, 1, RTSITF_GET_SIGNATURE(0, 0x830B7CC7), 0x03050800) 
#endif


/**
 * <description>iomgrupdateconfiguration</description>
 */
typedef struct tagiomgrupdateconfiguration_struct
{
	IoConfigConnector *pConnectorList;	/* VAR_INPUT */	
	RTS_IEC_DINT nCount;				/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrUpdateConfiguration;	/* VAR_OUTPUT */	
} iomgrupdateconfiguration_struct;

void CDECL CDECL_EXT iomgrupdateconfiguration(iomgrupdateconfiguration_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRUPDATECONFIGURATION_IEC) (iomgrupdateconfiguration_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRUPDATECONFIGURATION_NOTIMPLEMENTED)
	#define USE_iomgrupdateconfiguration
	#define EXT_iomgrupdateconfiguration
	#define GET_iomgrupdateconfiguration(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrupdateconfiguration(p0) 
	#define CHK_iomgrupdateconfiguration  FALSE
	#define EXP_iomgrupdateconfiguration  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrupdateconfiguration
	#define EXT_iomgrupdateconfiguration
	#define GET_iomgrupdateconfiguration(fl)  CAL_CMGETAPI( "iomgrupdateconfiguration" ) 
	#define CAL_iomgrupdateconfiguration  iomgrupdateconfiguration
	#define CHK_iomgrupdateconfiguration  TRUE
	#define EXP_iomgrupdateconfiguration  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrupdateconfiguration", (RTS_UINTPTR)iomgrupdateconfiguration, 1, RTSITF_GET_SIGNATURE(0, 0xB1381773), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrupdateconfiguration
	#define EXT_iomgrupdateconfiguration
	#define GET_iomgrupdateconfiguration(fl)  CAL_CMGETAPI( "iomgrupdateconfiguration" ) 
	#define CAL_iomgrupdateconfiguration  iomgrupdateconfiguration
	#define CHK_iomgrupdateconfiguration  TRUE
	#define EXP_iomgrupdateconfiguration  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrupdateconfiguration", (RTS_UINTPTR)iomgrupdateconfiguration, 1, RTSITF_GET_SIGNATURE(0, 0xB1381773), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrupdateconfiguration
	#define EXT_CmpIoMgriomgrupdateconfiguration
	#define GET_CmpIoMgriomgrupdateconfiguration  ERR_OK
	#define CAL_CmpIoMgriomgrupdateconfiguration  iomgrupdateconfiguration
	#define CHK_CmpIoMgriomgrupdateconfiguration  TRUE
	#define EXP_CmpIoMgriomgrupdateconfiguration  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrupdateconfiguration", (RTS_UINTPTR)iomgrupdateconfiguration, 1, RTSITF_GET_SIGNATURE(0, 0xB1381773), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrupdateconfiguration
	#define EXT_iomgrupdateconfiguration
	#define GET_iomgrupdateconfiguration(fl)  CAL_CMGETAPI( "iomgrupdateconfiguration" ) 
	#define CAL_iomgrupdateconfiguration  iomgrupdateconfiguration
	#define CHK_iomgrupdateconfiguration  TRUE
	#define EXP_iomgrupdateconfiguration  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrupdateconfiguration", (RTS_UINTPTR)iomgrupdateconfiguration, 1, RTSITF_GET_SIGNATURE(0, 0xB1381773), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrupdateconfiguration  PFIOMGRUPDATECONFIGURATION_IEC pfiomgrupdateconfiguration;
	#define EXT_iomgrupdateconfiguration  extern PFIOMGRUPDATECONFIGURATION_IEC pfiomgrupdateconfiguration;
	#define GET_iomgrupdateconfiguration(fl)  s_pfCMGetAPI2( "iomgrupdateconfiguration", (RTS_VOID_FCTPTR *)&pfiomgrupdateconfiguration, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xB1381773), 0x03050800)
	#define CAL_iomgrupdateconfiguration  pfiomgrupdateconfiguration
	#define CHK_iomgrupdateconfiguration  (pfiomgrupdateconfiguration != NULL)
	#define EXP_iomgrupdateconfiguration   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrupdateconfiguration", (RTS_UINTPTR)iomgrupdateconfiguration, 1, RTSITF_GET_SIGNATURE(0, 0xB1381773), 0x03050800) 
#endif


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

void CDECL CDECL_EXT iomgrupdateconfiguration2(iomgrupdateconfiguration2_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRUPDATECONFIGURATION2_IEC) (iomgrupdateconfiguration2_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRUPDATECONFIGURATION2_NOTIMPLEMENTED)
	#define USE_iomgrupdateconfiguration2
	#define EXT_iomgrupdateconfiguration2
	#define GET_iomgrupdateconfiguration2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrupdateconfiguration2(p0) 
	#define CHK_iomgrupdateconfiguration2  FALSE
	#define EXP_iomgrupdateconfiguration2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrupdateconfiguration2
	#define EXT_iomgrupdateconfiguration2
	#define GET_iomgrupdateconfiguration2(fl)  CAL_CMGETAPI( "iomgrupdateconfiguration2" ) 
	#define CAL_iomgrupdateconfiguration2  iomgrupdateconfiguration2
	#define CHK_iomgrupdateconfiguration2  TRUE
	#define EXP_iomgrupdateconfiguration2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrupdateconfiguration2", (RTS_UINTPTR)iomgrupdateconfiguration2, 1, RTSITF_GET_SIGNATURE(0, 0x44CD4528), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrupdateconfiguration2
	#define EXT_iomgrupdateconfiguration2
	#define GET_iomgrupdateconfiguration2(fl)  CAL_CMGETAPI( "iomgrupdateconfiguration2" ) 
	#define CAL_iomgrupdateconfiguration2  iomgrupdateconfiguration2
	#define CHK_iomgrupdateconfiguration2  TRUE
	#define EXP_iomgrupdateconfiguration2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrupdateconfiguration2", (RTS_UINTPTR)iomgrupdateconfiguration2, 1, RTSITF_GET_SIGNATURE(0, 0x44CD4528), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrupdateconfiguration2
	#define EXT_CmpIoMgriomgrupdateconfiguration2
	#define GET_CmpIoMgriomgrupdateconfiguration2  ERR_OK
	#define CAL_CmpIoMgriomgrupdateconfiguration2  iomgrupdateconfiguration2
	#define CHK_CmpIoMgriomgrupdateconfiguration2  TRUE
	#define EXP_CmpIoMgriomgrupdateconfiguration2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrupdateconfiguration2", (RTS_UINTPTR)iomgrupdateconfiguration2, 1, RTSITF_GET_SIGNATURE(0, 0x44CD4528), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrupdateconfiguration2
	#define EXT_iomgrupdateconfiguration2
	#define GET_iomgrupdateconfiguration2(fl)  CAL_CMGETAPI( "iomgrupdateconfiguration2" ) 
	#define CAL_iomgrupdateconfiguration2  iomgrupdateconfiguration2
	#define CHK_iomgrupdateconfiguration2  TRUE
	#define EXP_iomgrupdateconfiguration2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrupdateconfiguration2", (RTS_UINTPTR)iomgrupdateconfiguration2, 1, RTSITF_GET_SIGNATURE(0, 0x44CD4528), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrupdateconfiguration2  PFIOMGRUPDATECONFIGURATION2_IEC pfiomgrupdateconfiguration2;
	#define EXT_iomgrupdateconfiguration2  extern PFIOMGRUPDATECONFIGURATION2_IEC pfiomgrupdateconfiguration2;
	#define GET_iomgrupdateconfiguration2(fl)  s_pfCMGetAPI2( "iomgrupdateconfiguration2", (RTS_VOID_FCTPTR *)&pfiomgrupdateconfiguration2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x44CD4528), 0x03050800)
	#define CAL_iomgrupdateconfiguration2  pfiomgrupdateconfiguration2
	#define CHK_iomgrupdateconfiguration2  (pfiomgrupdateconfiguration2 != NULL)
	#define EXP_iomgrupdateconfiguration2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrupdateconfiguration2", (RTS_UINTPTR)iomgrupdateconfiguration2, 1, RTSITF_GET_SIGNATURE(0, 0x44CD4528), 0x03050800) 
#endif


/**
 * <description>iomgrupdatemapping</description>
 */
typedef struct tagiomgrupdatemapping_struct
{
	IoConfigTaskMap *pTaskMapList;		/* VAR_INPUT */	
	RTS_IEC_DINT nCount;				/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrUpdateMapping;	/* VAR_OUTPUT */	
} iomgrupdatemapping_struct;

void CDECL CDECL_EXT iomgrupdatemapping(iomgrupdatemapping_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRUPDATEMAPPING_IEC) (iomgrupdatemapping_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRUPDATEMAPPING_NOTIMPLEMENTED)
	#define USE_iomgrupdatemapping
	#define EXT_iomgrupdatemapping
	#define GET_iomgrupdatemapping(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrupdatemapping(p0) 
	#define CHK_iomgrupdatemapping  FALSE
	#define EXP_iomgrupdatemapping  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrupdatemapping
	#define EXT_iomgrupdatemapping
	#define GET_iomgrupdatemapping(fl)  CAL_CMGETAPI( "iomgrupdatemapping" ) 
	#define CAL_iomgrupdatemapping  iomgrupdatemapping
	#define CHK_iomgrupdatemapping  TRUE
	#define EXP_iomgrupdatemapping  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrupdatemapping", (RTS_UINTPTR)iomgrupdatemapping, 1, RTSITF_GET_SIGNATURE(0, 0x0A15126C), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrupdatemapping
	#define EXT_iomgrupdatemapping
	#define GET_iomgrupdatemapping(fl)  CAL_CMGETAPI( "iomgrupdatemapping" ) 
	#define CAL_iomgrupdatemapping  iomgrupdatemapping
	#define CHK_iomgrupdatemapping  TRUE
	#define EXP_iomgrupdatemapping  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrupdatemapping", (RTS_UINTPTR)iomgrupdatemapping, 1, RTSITF_GET_SIGNATURE(0, 0x0A15126C), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrupdatemapping
	#define EXT_CmpIoMgriomgrupdatemapping
	#define GET_CmpIoMgriomgrupdatemapping  ERR_OK
	#define CAL_CmpIoMgriomgrupdatemapping  iomgrupdatemapping
	#define CHK_CmpIoMgriomgrupdatemapping  TRUE
	#define EXP_CmpIoMgriomgrupdatemapping  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrupdatemapping", (RTS_UINTPTR)iomgrupdatemapping, 1, RTSITF_GET_SIGNATURE(0, 0x0A15126C), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrupdatemapping
	#define EXT_iomgrupdatemapping
	#define GET_iomgrupdatemapping(fl)  CAL_CMGETAPI( "iomgrupdatemapping" ) 
	#define CAL_iomgrupdatemapping  iomgrupdatemapping
	#define CHK_iomgrupdatemapping  TRUE
	#define EXP_iomgrupdatemapping  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrupdatemapping", (RTS_UINTPTR)iomgrupdatemapping, 1, RTSITF_GET_SIGNATURE(0, 0x0A15126C), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrupdatemapping  PFIOMGRUPDATEMAPPING_IEC pfiomgrupdatemapping;
	#define EXT_iomgrupdatemapping  extern PFIOMGRUPDATEMAPPING_IEC pfiomgrupdatemapping;
	#define GET_iomgrupdatemapping(fl)  s_pfCMGetAPI2( "iomgrupdatemapping", (RTS_VOID_FCTPTR *)&pfiomgrupdatemapping, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x0A15126C), 0x03050800)
	#define CAL_iomgrupdatemapping  pfiomgrupdatemapping
	#define CHK_iomgrupdatemapping  (pfiomgrupdatemapping != NULL)
	#define EXP_iomgrupdatemapping   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrupdatemapping", (RTS_UINTPTR)iomgrupdatemapping, 1, RTSITF_GET_SIGNATURE(0, 0x0A15126C), 0x03050800) 
#endif


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

void CDECL CDECL_EXT iomgrupdatemapping2(iomgrupdatemapping2_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRUPDATEMAPPING2_IEC) (iomgrupdatemapping2_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRUPDATEMAPPING2_NOTIMPLEMENTED)
	#define USE_iomgrupdatemapping2
	#define EXT_iomgrupdatemapping2
	#define GET_iomgrupdatemapping2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrupdatemapping2(p0) 
	#define CHK_iomgrupdatemapping2  FALSE
	#define EXP_iomgrupdatemapping2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrupdatemapping2
	#define EXT_iomgrupdatemapping2
	#define GET_iomgrupdatemapping2(fl)  CAL_CMGETAPI( "iomgrupdatemapping2" ) 
	#define CAL_iomgrupdatemapping2  iomgrupdatemapping2
	#define CHK_iomgrupdatemapping2  TRUE
	#define EXP_iomgrupdatemapping2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrupdatemapping2", (RTS_UINTPTR)iomgrupdatemapping2, 1, RTSITF_GET_SIGNATURE(0, 0x775F7CAD), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrupdatemapping2
	#define EXT_iomgrupdatemapping2
	#define GET_iomgrupdatemapping2(fl)  CAL_CMGETAPI( "iomgrupdatemapping2" ) 
	#define CAL_iomgrupdatemapping2  iomgrupdatemapping2
	#define CHK_iomgrupdatemapping2  TRUE
	#define EXP_iomgrupdatemapping2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrupdatemapping2", (RTS_UINTPTR)iomgrupdatemapping2, 1, RTSITF_GET_SIGNATURE(0, 0x775F7CAD), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrupdatemapping2
	#define EXT_CmpIoMgriomgrupdatemapping2
	#define GET_CmpIoMgriomgrupdatemapping2  ERR_OK
	#define CAL_CmpIoMgriomgrupdatemapping2  iomgrupdatemapping2
	#define CHK_CmpIoMgriomgrupdatemapping2  TRUE
	#define EXP_CmpIoMgriomgrupdatemapping2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrupdatemapping2", (RTS_UINTPTR)iomgrupdatemapping2, 1, RTSITF_GET_SIGNATURE(0, 0x775F7CAD), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrupdatemapping2
	#define EXT_iomgrupdatemapping2
	#define GET_iomgrupdatemapping2(fl)  CAL_CMGETAPI( "iomgrupdatemapping2" ) 
	#define CAL_iomgrupdatemapping2  iomgrupdatemapping2
	#define CHK_iomgrupdatemapping2  TRUE
	#define EXP_iomgrupdatemapping2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrupdatemapping2", (RTS_UINTPTR)iomgrupdatemapping2, 1, RTSITF_GET_SIGNATURE(0, 0x775F7CAD), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrupdatemapping2  PFIOMGRUPDATEMAPPING2_IEC pfiomgrupdatemapping2;
	#define EXT_iomgrupdatemapping2  extern PFIOMGRUPDATEMAPPING2_IEC pfiomgrupdatemapping2;
	#define GET_iomgrupdatemapping2(fl)  s_pfCMGetAPI2( "iomgrupdatemapping2", (RTS_VOID_FCTPTR *)&pfiomgrupdatemapping2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x775F7CAD), 0x03050800)
	#define CAL_iomgrupdatemapping2  pfiomgrupdatemapping2
	#define CHK_iomgrupdatemapping2  (pfiomgrupdatemapping2 != NULL)
	#define EXP_iomgrupdatemapping2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrupdatemapping2", (RTS_UINTPTR)iomgrupdatemapping2, 1, RTSITF_GET_SIGNATURE(0, 0x775F7CAD), 0x03050800) 
#endif


/**
 * <description>iomgrwatchdogtrigger</description>
 */
typedef struct tagiomgrwatchdogtrigger_struct
{
	IoConfigConnector *pConnector;		/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrWatchdogTrigger;	/* VAR_OUTPUT */	
} iomgrwatchdogtrigger_struct;

void CDECL CDECL_EXT iomgrwatchdogtrigger(iomgrwatchdogtrigger_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRWATCHDOGTRIGGER_IEC) (iomgrwatchdogtrigger_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRWATCHDOGTRIGGER_NOTIMPLEMENTED)
	#define USE_iomgrwatchdogtrigger
	#define EXT_iomgrwatchdogtrigger
	#define GET_iomgrwatchdogtrigger(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrwatchdogtrigger(p0) 
	#define CHK_iomgrwatchdogtrigger  FALSE
	#define EXP_iomgrwatchdogtrigger  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrwatchdogtrigger
	#define EXT_iomgrwatchdogtrigger
	#define GET_iomgrwatchdogtrigger(fl)  CAL_CMGETAPI( "iomgrwatchdogtrigger" ) 
	#define CAL_iomgrwatchdogtrigger  iomgrwatchdogtrigger
	#define CHK_iomgrwatchdogtrigger  TRUE
	#define EXP_iomgrwatchdogtrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrwatchdogtrigger", (RTS_UINTPTR)iomgrwatchdogtrigger, 1, RTSITF_GET_SIGNATURE(0, 0x986DFD93), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrwatchdogtrigger
	#define EXT_iomgrwatchdogtrigger
	#define GET_iomgrwatchdogtrigger(fl)  CAL_CMGETAPI( "iomgrwatchdogtrigger" ) 
	#define CAL_iomgrwatchdogtrigger  iomgrwatchdogtrigger
	#define CHK_iomgrwatchdogtrigger  TRUE
	#define EXP_iomgrwatchdogtrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrwatchdogtrigger", (RTS_UINTPTR)iomgrwatchdogtrigger, 1, RTSITF_GET_SIGNATURE(0, 0x986DFD93), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrwatchdogtrigger
	#define EXT_CmpIoMgriomgrwatchdogtrigger
	#define GET_CmpIoMgriomgrwatchdogtrigger  ERR_OK
	#define CAL_CmpIoMgriomgrwatchdogtrigger  iomgrwatchdogtrigger
	#define CHK_CmpIoMgriomgrwatchdogtrigger  TRUE
	#define EXP_CmpIoMgriomgrwatchdogtrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrwatchdogtrigger", (RTS_UINTPTR)iomgrwatchdogtrigger, 1, RTSITF_GET_SIGNATURE(0, 0x986DFD93), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrwatchdogtrigger
	#define EXT_iomgrwatchdogtrigger
	#define GET_iomgrwatchdogtrigger(fl)  CAL_CMGETAPI( "iomgrwatchdogtrigger" ) 
	#define CAL_iomgrwatchdogtrigger  iomgrwatchdogtrigger
	#define CHK_iomgrwatchdogtrigger  TRUE
	#define EXP_iomgrwatchdogtrigger  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrwatchdogtrigger", (RTS_UINTPTR)iomgrwatchdogtrigger, 1, RTSITF_GET_SIGNATURE(0, 0x986DFD93), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrwatchdogtrigger  PFIOMGRWATCHDOGTRIGGER_IEC pfiomgrwatchdogtrigger;
	#define EXT_iomgrwatchdogtrigger  extern PFIOMGRWATCHDOGTRIGGER_IEC pfiomgrwatchdogtrigger;
	#define GET_iomgrwatchdogtrigger(fl)  s_pfCMGetAPI2( "iomgrwatchdogtrigger", (RTS_VOID_FCTPTR *)&pfiomgrwatchdogtrigger, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x986DFD93), 0x03050800)
	#define CAL_iomgrwatchdogtrigger  pfiomgrwatchdogtrigger
	#define CHK_iomgrwatchdogtrigger  (pfiomgrwatchdogtrigger != NULL)
	#define EXP_iomgrwatchdogtrigger   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrwatchdogtrigger", (RTS_UINTPTR)iomgrwatchdogtrigger, 1, RTSITF_GET_SIGNATURE(0, 0x986DFD93), 0x03050800) 
#endif


/**
 * <description>iomgrwriteoutputs</description>
 */
typedef struct tagiomgrwriteoutputs_struct
{
	IoConfigTaskMap *pTaskMap;			/* VAR_INPUT */	
	RTS_IEC_UDINT IoMgrWriteOutputs;	/* VAR_OUTPUT */	
} iomgrwriteoutputs_struct;

void CDECL CDECL_EXT iomgrwriteoutputs(iomgrwriteoutputs_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRWRITEOUTPUTS_IEC) (iomgrwriteoutputs_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRWRITEOUTPUTS_NOTIMPLEMENTED)
	#define USE_iomgrwriteoutputs
	#define EXT_iomgrwriteoutputs
	#define GET_iomgrwriteoutputs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrwriteoutputs(p0) 
	#define CHK_iomgrwriteoutputs  FALSE
	#define EXP_iomgrwriteoutputs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrwriteoutputs
	#define EXT_iomgrwriteoutputs
	#define GET_iomgrwriteoutputs(fl)  CAL_CMGETAPI( "iomgrwriteoutputs" ) 
	#define CAL_iomgrwriteoutputs  iomgrwriteoutputs
	#define CHK_iomgrwriteoutputs  TRUE
	#define EXP_iomgrwriteoutputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrwriteoutputs", (RTS_UINTPTR)iomgrwriteoutputs, 1, RTSITF_GET_SIGNATURE(0, 0xDA3433B3), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrwriteoutputs
	#define EXT_iomgrwriteoutputs
	#define GET_iomgrwriteoutputs(fl)  CAL_CMGETAPI( "iomgrwriteoutputs" ) 
	#define CAL_iomgrwriteoutputs  iomgrwriteoutputs
	#define CHK_iomgrwriteoutputs  TRUE
	#define EXP_iomgrwriteoutputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrwriteoutputs", (RTS_UINTPTR)iomgrwriteoutputs, 1, RTSITF_GET_SIGNATURE(0, 0xDA3433B3), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrwriteoutputs
	#define EXT_CmpIoMgriomgrwriteoutputs
	#define GET_CmpIoMgriomgrwriteoutputs  ERR_OK
	#define CAL_CmpIoMgriomgrwriteoutputs  iomgrwriteoutputs
	#define CHK_CmpIoMgriomgrwriteoutputs  TRUE
	#define EXP_CmpIoMgriomgrwriteoutputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrwriteoutputs", (RTS_UINTPTR)iomgrwriteoutputs, 1, RTSITF_GET_SIGNATURE(0, 0xDA3433B3), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrwriteoutputs
	#define EXT_iomgrwriteoutputs
	#define GET_iomgrwriteoutputs(fl)  CAL_CMGETAPI( "iomgrwriteoutputs" ) 
	#define CAL_iomgrwriteoutputs  iomgrwriteoutputs
	#define CHK_iomgrwriteoutputs  TRUE
	#define EXP_iomgrwriteoutputs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrwriteoutputs", (RTS_UINTPTR)iomgrwriteoutputs, 1, RTSITF_GET_SIGNATURE(0, 0xDA3433B3), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrwriteoutputs  PFIOMGRWRITEOUTPUTS_IEC pfiomgrwriteoutputs;
	#define EXT_iomgrwriteoutputs  extern PFIOMGRWRITEOUTPUTS_IEC pfiomgrwriteoutputs;
	#define GET_iomgrwriteoutputs(fl)  s_pfCMGetAPI2( "iomgrwriteoutputs", (RTS_VOID_FCTPTR *)&pfiomgrwriteoutputs, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xDA3433B3), 0x03050800)
	#define CAL_iomgrwriteoutputs  pfiomgrwriteoutputs
	#define CHK_iomgrwriteoutputs  (pfiomgrwriteoutputs != NULL)
	#define EXP_iomgrwriteoutputs   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrwriteoutputs", (RTS_UINTPTR)iomgrwriteoutputs, 1, RTSITF_GET_SIGNATURE(0, 0xDA3433B3), 0x03050800) 
#endif


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

void CDECL CDECL_EXT iomgrwriteparameter(iomgrwriteparameter_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRWRITEPARAMETER_IEC) (iomgrwriteparameter_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRWRITEPARAMETER_NOTIMPLEMENTED)
	#define USE_iomgrwriteparameter
	#define EXT_iomgrwriteparameter
	#define GET_iomgrwriteparameter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrwriteparameter(p0) 
	#define CHK_iomgrwriteparameter  FALSE
	#define EXP_iomgrwriteparameter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrwriteparameter
	#define EXT_iomgrwriteparameter
	#define GET_iomgrwriteparameter(fl)  CAL_CMGETAPI( "iomgrwriteparameter" ) 
	#define CAL_iomgrwriteparameter  iomgrwriteparameter
	#define CHK_iomgrwriteparameter  TRUE
	#define EXP_iomgrwriteparameter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrwriteparameter", (RTS_UINTPTR)iomgrwriteparameter, 1, RTSITF_GET_SIGNATURE(0, 0xAD04F7E8), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrwriteparameter
	#define EXT_iomgrwriteparameter
	#define GET_iomgrwriteparameter(fl)  CAL_CMGETAPI( "iomgrwriteparameter" ) 
	#define CAL_iomgrwriteparameter  iomgrwriteparameter
	#define CHK_iomgrwriteparameter  TRUE
	#define EXP_iomgrwriteparameter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrwriteparameter", (RTS_UINTPTR)iomgrwriteparameter, 1, RTSITF_GET_SIGNATURE(0, 0xAD04F7E8), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrwriteparameter
	#define EXT_CmpIoMgriomgrwriteparameter
	#define GET_CmpIoMgriomgrwriteparameter  ERR_OK
	#define CAL_CmpIoMgriomgrwriteparameter  iomgrwriteparameter
	#define CHK_CmpIoMgriomgrwriteparameter  TRUE
	#define EXP_CmpIoMgriomgrwriteparameter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrwriteparameter", (RTS_UINTPTR)iomgrwriteparameter, 1, RTSITF_GET_SIGNATURE(0, 0xAD04F7E8), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrwriteparameter
	#define EXT_iomgrwriteparameter
	#define GET_iomgrwriteparameter(fl)  CAL_CMGETAPI( "iomgrwriteparameter" ) 
	#define CAL_iomgrwriteparameter  iomgrwriteparameter
	#define CHK_iomgrwriteparameter  TRUE
	#define EXP_iomgrwriteparameter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrwriteparameter", (RTS_UINTPTR)iomgrwriteparameter, 1, RTSITF_GET_SIGNATURE(0, 0xAD04F7E8), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrwriteparameter  PFIOMGRWRITEPARAMETER_IEC pfiomgrwriteparameter;
	#define EXT_iomgrwriteparameter  extern PFIOMGRWRITEPARAMETER_IEC pfiomgrwriteparameter;
	#define GET_iomgrwriteparameter(fl)  s_pfCMGetAPI2( "iomgrwriteparameter", (RTS_VOID_FCTPTR *)&pfiomgrwriteparameter, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xAD04F7E8), 0x03050800)
	#define CAL_iomgrwriteparameter  pfiomgrwriteparameter
	#define CHK_iomgrwriteparameter  (pfiomgrwriteparameter != NULL)
	#define EXP_iomgrwriteparameter   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrwriteparameter", (RTS_UINTPTR)iomgrwriteparameter, 1, RTSITF_GET_SIGNATURE(0, 0xAD04F7E8), 0x03050800) 
#endif


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
void CDECL CDECL_EXT iomgrconfiggetiodriver(iomgrconfiggetiodriver_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRCONFIGGETIODRIVER_IEC) (iomgrconfiggetiodriver_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETIODRIVER_NOTIMPLEMENTED)
	#define USE_iomgrconfiggetiodriver
	#define EXT_iomgrconfiggetiodriver
	#define GET_iomgrconfiggetiodriver(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrconfiggetiodriver(p0) 
	#define CHK_iomgrconfiggetiodriver  FALSE
	#define EXP_iomgrconfiggetiodriver  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrconfiggetiodriver
	#define EXT_iomgrconfiggetiodriver
	#define GET_iomgrconfiggetiodriver(fl)  CAL_CMGETAPI( "iomgrconfiggetiodriver" ) 
	#define CAL_iomgrconfiggetiodriver  iomgrconfiggetiodriver
	#define CHK_iomgrconfiggetiodriver  TRUE
	#define EXP_iomgrconfiggetiodriver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetiodriver", (RTS_UINTPTR)iomgrconfiggetiodriver, 1, 0, 0x3010200) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrconfiggetiodriver
	#define EXT_iomgrconfiggetiodriver
	#define GET_iomgrconfiggetiodriver(fl)  CAL_CMGETAPI( "iomgrconfiggetiodriver" ) 
	#define CAL_iomgrconfiggetiodriver  iomgrconfiggetiodriver
	#define CHK_iomgrconfiggetiodriver  TRUE
	#define EXP_iomgrconfiggetiodriver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetiodriver", (RTS_UINTPTR)iomgrconfiggetiodriver, 1, 0, 0x3010200) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrconfiggetiodriver
	#define EXT_CmpIoMgriomgrconfiggetiodriver
	#define GET_CmpIoMgriomgrconfiggetiodriver  ERR_OK
	#define CAL_CmpIoMgriomgrconfiggetiodriver  iomgrconfiggetiodriver
	#define CHK_CmpIoMgriomgrconfiggetiodriver  TRUE
	#define EXP_CmpIoMgriomgrconfiggetiodriver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetiodriver", (RTS_UINTPTR)iomgrconfiggetiodriver, 1, 0, 0x3010200) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrconfiggetiodriver
	#define EXT_iomgrconfiggetiodriver
	#define GET_iomgrconfiggetiodriver(fl)  CAL_CMGETAPI( "iomgrconfiggetiodriver" ) 
	#define CAL_iomgrconfiggetiodriver  iomgrconfiggetiodriver
	#define CHK_iomgrconfiggetiodriver  TRUE
	#define EXP_iomgrconfiggetiodriver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetiodriver", (RTS_UINTPTR)iomgrconfiggetiodriver, 1, 0, 0x3010200) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrconfiggetiodriver  PFIOMGRCONFIGGETIODRIVER_IEC pfiomgrconfiggetiodriver;
	#define EXT_iomgrconfiggetiodriver  extern PFIOMGRCONFIGGETIODRIVER_IEC pfiomgrconfiggetiodriver;
	#define GET_iomgrconfiggetiodriver(fl)  s_pfCMGetAPI2( "iomgrconfiggetiodriver", (RTS_VOID_FCTPTR *)&pfiomgrconfiggetiodriver, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0x3010200)
	#define CAL_iomgrconfiggetiodriver  pfiomgrconfiggetiodriver
	#define CHK_iomgrconfiggetiodriver  (pfiomgrconfiggetiodriver != NULL)
	#define EXP_iomgrconfiggetiodriver   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"iomgrconfiggetiodriver", (RTS_UINTPTR)iomgrconfiggetiodriver, 1, 0, 0x3010200) 
#endif


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
RTS_RESULT CDECL IoMgrExceptionHandler(char *pszApplication, RTS_UI32 ulException);
typedef RTS_RESULT (CDECL * PFIOMGREXCEPTIONHANDLER) (char *pszApplication, RTS_UI32 ulException);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGREXCEPTIONHANDLER_NOTIMPLEMENTED)
	#define USE_IoMgrExceptionHandler
	#define EXT_IoMgrExceptionHandler
	#define GET_IoMgrExceptionHandler(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrExceptionHandler(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrExceptionHandler  FALSE
	#define EXP_IoMgrExceptionHandler  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrExceptionHandler
	#define EXT_IoMgrExceptionHandler
	#define GET_IoMgrExceptionHandler(fl)  CAL_CMGETAPI( "IoMgrExceptionHandler" ) 
	#define CAL_IoMgrExceptionHandler  IoMgrExceptionHandler
	#define CHK_IoMgrExceptionHandler  TRUE
	#define EXP_IoMgrExceptionHandler  CAL_CMEXPAPI( "IoMgrExceptionHandler" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrExceptionHandler
	#define EXT_IoMgrExceptionHandler
	#define GET_IoMgrExceptionHandler(fl)  CAL_CMGETAPI( "IoMgrExceptionHandler" ) 
	#define CAL_IoMgrExceptionHandler  IoMgrExceptionHandler
	#define CHK_IoMgrExceptionHandler  TRUE
	#define EXP_IoMgrExceptionHandler  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrExceptionHandler", (RTS_UINTPTR)IoMgrExceptionHandler, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrExceptionHandler
	#define EXT_CmpIoMgrIoMgrExceptionHandler
	#define GET_CmpIoMgrIoMgrExceptionHandler  ERR_OK
	#define CAL_CmpIoMgrIoMgrExceptionHandler pICmpIoMgr->IIoMgrExceptionHandler
	#define CHK_CmpIoMgrIoMgrExceptionHandler (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrExceptionHandler  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrExceptionHandler
	#define EXT_IoMgrExceptionHandler
	#define GET_IoMgrExceptionHandler(fl)  CAL_CMGETAPI( "IoMgrExceptionHandler" ) 
	#define CAL_IoMgrExceptionHandler pICmpIoMgr->IIoMgrExceptionHandler
	#define CHK_IoMgrExceptionHandler (pICmpIoMgr != NULL)
	#define EXP_IoMgrExceptionHandler  CAL_CMEXPAPI( "IoMgrExceptionHandler" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrExceptionHandler  PFIOMGREXCEPTIONHANDLER pfIoMgrExceptionHandler;
	#define EXT_IoMgrExceptionHandler  extern PFIOMGREXCEPTIONHANDLER pfIoMgrExceptionHandler;
	#define GET_IoMgrExceptionHandler(fl)  s_pfCMGetAPI2( "IoMgrExceptionHandler", (RTS_VOID_FCTPTR *)&pfIoMgrExceptionHandler, (fl), 0, 0)
	#define CAL_IoMgrExceptionHandler  pfIoMgrExceptionHandler
	#define CHK_IoMgrExceptionHandler  (pfIoMgrExceptionHandler != NULL)
	#define EXP_IoMgrExceptionHandler  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrExceptionHandler", (RTS_UINTPTR)IoMgrExceptionHandler, 0, 0) 
#endif




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
RTS_HANDLE CDECL IoMgrRegisterInstance(IBase *pIBase, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIOMGRREGISTERINSTANCE) (IBase *pIBase, RTS_RESULT *pResult);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRREGISTERINSTANCE_NOTIMPLEMENTED)
	#define USE_IoMgrRegisterInstance
	#define EXT_IoMgrRegisterInstance
	#define GET_IoMgrRegisterInstance(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrRegisterInstance(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IoMgrRegisterInstance  FALSE
	#define EXP_IoMgrRegisterInstance  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrRegisterInstance
	#define EXT_IoMgrRegisterInstance
	#define GET_IoMgrRegisterInstance(fl)  CAL_CMGETAPI( "IoMgrRegisterInstance" ) 
	#define CAL_IoMgrRegisterInstance  IoMgrRegisterInstance
	#define CHK_IoMgrRegisterInstance  TRUE
	#define EXP_IoMgrRegisterInstance  CAL_CMEXPAPI( "IoMgrRegisterInstance" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrRegisterInstance
	#define EXT_IoMgrRegisterInstance
	#define GET_IoMgrRegisterInstance(fl)  CAL_CMGETAPI( "IoMgrRegisterInstance" ) 
	#define CAL_IoMgrRegisterInstance  IoMgrRegisterInstance
	#define CHK_IoMgrRegisterInstance  TRUE
	#define EXP_IoMgrRegisterInstance  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrRegisterInstance", (RTS_UINTPTR)IoMgrRegisterInstance, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrRegisterInstance
	#define EXT_CmpIoMgrIoMgrRegisterInstance
	#define GET_CmpIoMgrIoMgrRegisterInstance  ERR_OK
	#define CAL_CmpIoMgrIoMgrRegisterInstance pICmpIoMgr->IIoMgrRegisterInstance
	#define CHK_CmpIoMgrIoMgrRegisterInstance (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrRegisterInstance  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrRegisterInstance
	#define EXT_IoMgrRegisterInstance
	#define GET_IoMgrRegisterInstance(fl)  CAL_CMGETAPI( "IoMgrRegisterInstance" ) 
	#define CAL_IoMgrRegisterInstance pICmpIoMgr->IIoMgrRegisterInstance
	#define CHK_IoMgrRegisterInstance (pICmpIoMgr != NULL)
	#define EXP_IoMgrRegisterInstance  CAL_CMEXPAPI( "IoMgrRegisterInstance" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrRegisterInstance  PFIOMGRREGISTERINSTANCE pfIoMgrRegisterInstance;
	#define EXT_IoMgrRegisterInstance  extern PFIOMGRREGISTERINSTANCE pfIoMgrRegisterInstance;
	#define GET_IoMgrRegisterInstance(fl)  s_pfCMGetAPI2( "IoMgrRegisterInstance", (RTS_VOID_FCTPTR *)&pfIoMgrRegisterInstance, (fl), 0, 0)
	#define CAL_IoMgrRegisterInstance  pfIoMgrRegisterInstance
	#define CHK_IoMgrRegisterInstance  (pfIoMgrRegisterInstance != NULL)
	#define EXP_IoMgrRegisterInstance  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrRegisterInstance", (RTS_UINTPTR)IoMgrRegisterInstance, 0, 0) 
#endif



void CDECL CDECL_EXT iomgrregisterinstance(iomgrregisterinstance_struct *p);
typedef void (CDECL CDECL_EXT* PFIOMGRREGISTERINSTANCE_IEC) (iomgrregisterinstance_struct *p);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRREGISTERINSTANCE_NOTIMPLEMENTED)
	#define USE_iomgrregisterinstance
	#define EXT_iomgrregisterinstance
	#define GET_iomgrregisterinstance(fl)  ERR_NOTIMPLEMENTED
	#define CAL_iomgrregisterinstance(p0) 
	#define CHK_iomgrregisterinstance  FALSE
	#define EXP_iomgrregisterinstance  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_iomgrregisterinstance
	#define EXT_iomgrregisterinstance
	#define GET_iomgrregisterinstance(fl)  CAL_CMGETAPI( "iomgrregisterinstance" ) 
	#define CAL_iomgrregisterinstance  iomgrregisterinstance
	#define CHK_iomgrregisterinstance  TRUE
	#define EXP_iomgrregisterinstance  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"iomgrregisterinstance", (RTS_UINTPTR)iomgrregisterinstance, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_iomgrregisterinstance
	#define EXT_iomgrregisterinstance
	#define GET_iomgrregisterinstance(fl)  CAL_CMGETAPI( "iomgrregisterinstance" ) 
	#define CAL_iomgrregisterinstance  iomgrregisterinstance
	#define CHK_iomgrregisterinstance  TRUE
	#define EXP_iomgrregisterinstance  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"iomgrregisterinstance", (RTS_UINTPTR)iomgrregisterinstance, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgriomgrregisterinstance
	#define EXT_CmpIoMgriomgrregisterinstance
	#define GET_CmpIoMgriomgrregisterinstance  ERR_OK
	#define CAL_CmpIoMgriomgrregisterinstance  iomgrregisterinstance
	#define CHK_CmpIoMgriomgrregisterinstance  TRUE
	#define EXP_CmpIoMgriomgrregisterinstance  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"iomgrregisterinstance", (RTS_UINTPTR)iomgrregisterinstance, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_iomgrregisterinstance
	#define EXT_iomgrregisterinstance
	#define GET_iomgrregisterinstance(fl)  CAL_CMGETAPI( "iomgrregisterinstance" ) 
	#define CAL_iomgrregisterinstance  iomgrregisterinstance
	#define CHK_iomgrregisterinstance  TRUE
	#define EXP_iomgrregisterinstance  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"iomgrregisterinstance", (RTS_UINTPTR)iomgrregisterinstance, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_iomgrregisterinstance  PFIOMGRREGISTERINSTANCE_IEC pfiomgrregisterinstance;
	#define EXT_iomgrregisterinstance  extern PFIOMGRREGISTERINSTANCE_IEC pfiomgrregisterinstance;
	#define GET_iomgrregisterinstance(fl)  s_pfCMGetAPI2( "iomgrregisterinstance", (RTS_VOID_FCTPTR *)&pfiomgrregisterinstance, (fl), 0, 0)
	#define CAL_iomgrregisterinstance  pfiomgrregisterinstance
	#define CHK_iomgrregisterinstance  (pfiomgrregisterinstance != NULL)
	#define EXP_iomgrregisterinstance   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"iomgrregisterinstance", (RTS_UINTPTR)iomgrregisterinstance, 1, 0) 
#endif


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
RTS_HANDLE CDECL IoMgrRegisterInstance2(IBase *pIBase, int bIecDriver, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFIOMGRREGISTERINSTANCE2) (IBase *pIBase, int bIecDriver, RTS_RESULT *pResult);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRREGISTERINSTANCE2_NOTIMPLEMENTED)
	#define USE_IoMgrRegisterInstance2
	#define EXT_IoMgrRegisterInstance2
	#define GET_IoMgrRegisterInstance2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrRegisterInstance2(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_IoMgrRegisterInstance2  FALSE
	#define EXP_IoMgrRegisterInstance2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrRegisterInstance2
	#define EXT_IoMgrRegisterInstance2
	#define GET_IoMgrRegisterInstance2(fl)  CAL_CMGETAPI( "IoMgrRegisterInstance2" ) 
	#define CAL_IoMgrRegisterInstance2  IoMgrRegisterInstance2
	#define CHK_IoMgrRegisterInstance2  TRUE
	#define EXP_IoMgrRegisterInstance2  CAL_CMEXPAPI( "IoMgrRegisterInstance2" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrRegisterInstance2
	#define EXT_IoMgrRegisterInstance2
	#define GET_IoMgrRegisterInstance2(fl)  CAL_CMGETAPI( "IoMgrRegisterInstance2" ) 
	#define CAL_IoMgrRegisterInstance2  IoMgrRegisterInstance2
	#define CHK_IoMgrRegisterInstance2  TRUE
	#define EXP_IoMgrRegisterInstance2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrRegisterInstance2", (RTS_UINTPTR)IoMgrRegisterInstance2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrRegisterInstance2
	#define EXT_CmpIoMgrIoMgrRegisterInstance2
	#define GET_CmpIoMgrIoMgrRegisterInstance2  ERR_OK
	#define CAL_CmpIoMgrIoMgrRegisterInstance2 pICmpIoMgr->IIoMgrRegisterInstance2
	#define CHK_CmpIoMgrIoMgrRegisterInstance2 (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrRegisterInstance2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrRegisterInstance2
	#define EXT_IoMgrRegisterInstance2
	#define GET_IoMgrRegisterInstance2(fl)  CAL_CMGETAPI( "IoMgrRegisterInstance2" ) 
	#define CAL_IoMgrRegisterInstance2 pICmpIoMgr->IIoMgrRegisterInstance2
	#define CHK_IoMgrRegisterInstance2 (pICmpIoMgr != NULL)
	#define EXP_IoMgrRegisterInstance2  CAL_CMEXPAPI( "IoMgrRegisterInstance2" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrRegisterInstance2  PFIOMGRREGISTERINSTANCE2 pfIoMgrRegisterInstance2;
	#define EXT_IoMgrRegisterInstance2  extern PFIOMGRREGISTERINSTANCE2 pfIoMgrRegisterInstance2;
	#define GET_IoMgrRegisterInstance2(fl)  s_pfCMGetAPI2( "IoMgrRegisterInstance2", (RTS_VOID_FCTPTR *)&pfIoMgrRegisterInstance2, (fl), 0, 0)
	#define CAL_IoMgrRegisterInstance2  pfIoMgrRegisterInstance2
	#define CHK_IoMgrRegisterInstance2  (pfIoMgrRegisterInstance2 != NULL)
	#define EXP_IoMgrRegisterInstance2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrRegisterInstance2", (RTS_UINTPTR)IoMgrRegisterInstance2, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrUnregisterInstance(IBase *pIBase);
typedef RTS_RESULT (CDECL * PFIOMGRUNREGISTERINSTANCE) (IBase *pIBase);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRUNREGISTERINSTANCE_NOTIMPLEMENTED)
	#define USE_IoMgrUnregisterInstance
	#define EXT_IoMgrUnregisterInstance
	#define GET_IoMgrUnregisterInstance(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrUnregisterInstance(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrUnregisterInstance  FALSE
	#define EXP_IoMgrUnregisterInstance  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrUnregisterInstance
	#define EXT_IoMgrUnregisterInstance
	#define GET_IoMgrUnregisterInstance(fl)  CAL_CMGETAPI( "IoMgrUnregisterInstance" ) 
	#define CAL_IoMgrUnregisterInstance  IoMgrUnregisterInstance
	#define CHK_IoMgrUnregisterInstance  TRUE
	#define EXP_IoMgrUnregisterInstance  CAL_CMEXPAPI( "IoMgrUnregisterInstance" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrUnregisterInstance
	#define EXT_IoMgrUnregisterInstance
	#define GET_IoMgrUnregisterInstance(fl)  CAL_CMGETAPI( "IoMgrUnregisterInstance" ) 
	#define CAL_IoMgrUnregisterInstance  IoMgrUnregisterInstance
	#define CHK_IoMgrUnregisterInstance  TRUE
	#define EXP_IoMgrUnregisterInstance  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrUnregisterInstance", (RTS_UINTPTR)IoMgrUnregisterInstance, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrUnregisterInstance
	#define EXT_CmpIoMgrIoMgrUnregisterInstance
	#define GET_CmpIoMgrIoMgrUnregisterInstance  ERR_OK
	#define CAL_CmpIoMgrIoMgrUnregisterInstance pICmpIoMgr->IIoMgrUnregisterInstance
	#define CHK_CmpIoMgrIoMgrUnregisterInstance (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrUnregisterInstance  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrUnregisterInstance
	#define EXT_IoMgrUnregisterInstance
	#define GET_IoMgrUnregisterInstance(fl)  CAL_CMGETAPI( "IoMgrUnregisterInstance" ) 
	#define CAL_IoMgrUnregisterInstance pICmpIoMgr->IIoMgrUnregisterInstance
	#define CHK_IoMgrUnregisterInstance (pICmpIoMgr != NULL)
	#define EXP_IoMgrUnregisterInstance  CAL_CMEXPAPI( "IoMgrUnregisterInstance" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrUnregisterInstance  PFIOMGRUNREGISTERINSTANCE pfIoMgrUnregisterInstance;
	#define EXT_IoMgrUnregisterInstance  extern PFIOMGRUNREGISTERINSTANCE pfIoMgrUnregisterInstance;
	#define GET_IoMgrUnregisterInstance(fl)  s_pfCMGetAPI2( "IoMgrUnregisterInstance", (RTS_VOID_FCTPTR *)&pfIoMgrUnregisterInstance, (fl), 0, 0)
	#define CAL_IoMgrUnregisterInstance  pfIoMgrUnregisterInstance
	#define CHK_IoMgrUnregisterInstance  (pfIoMgrUnregisterInstance != NULL)
	#define EXP_IoMgrUnregisterInstance  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrUnregisterInstance", (RTS_UINTPTR)IoMgrUnregisterInstance, 0, 0) 
#endif




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
IBase* CDECL IoMgrGetFirstDriverInstance(int *pbIecDriver, RTS_RESULT *pResult);
typedef IBase* (CDECL * PFIOMGRGETFIRSTDRIVERINSTANCE) (int *pbIecDriver, RTS_RESULT *pResult);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRGETFIRSTDRIVERINSTANCE_NOTIMPLEMENTED)
	#define USE_IoMgrGetFirstDriverInstance
	#define EXT_IoMgrGetFirstDriverInstance
	#define GET_IoMgrGetFirstDriverInstance(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrGetFirstDriverInstance(p0,p1)  (IBase*)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrGetFirstDriverInstance  FALSE
	#define EXP_IoMgrGetFirstDriverInstance  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrGetFirstDriverInstance
	#define EXT_IoMgrGetFirstDriverInstance
	#define GET_IoMgrGetFirstDriverInstance(fl)  CAL_CMGETAPI( "IoMgrGetFirstDriverInstance" ) 
	#define CAL_IoMgrGetFirstDriverInstance  IoMgrGetFirstDriverInstance
	#define CHK_IoMgrGetFirstDriverInstance  TRUE
	#define EXP_IoMgrGetFirstDriverInstance  CAL_CMEXPAPI( "IoMgrGetFirstDriverInstance" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrGetFirstDriverInstance
	#define EXT_IoMgrGetFirstDriverInstance
	#define GET_IoMgrGetFirstDriverInstance(fl)  CAL_CMGETAPI( "IoMgrGetFirstDriverInstance" ) 
	#define CAL_IoMgrGetFirstDriverInstance  IoMgrGetFirstDriverInstance
	#define CHK_IoMgrGetFirstDriverInstance  TRUE
	#define EXP_IoMgrGetFirstDriverInstance  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrGetFirstDriverInstance", (RTS_UINTPTR)IoMgrGetFirstDriverInstance, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrGetFirstDriverInstance
	#define EXT_CmpIoMgrIoMgrGetFirstDriverInstance
	#define GET_CmpIoMgrIoMgrGetFirstDriverInstance  ERR_OK
	#define CAL_CmpIoMgrIoMgrGetFirstDriverInstance pICmpIoMgr->IIoMgrGetFirstDriverInstance
	#define CHK_CmpIoMgrIoMgrGetFirstDriverInstance (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrGetFirstDriverInstance  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrGetFirstDriverInstance
	#define EXT_IoMgrGetFirstDriverInstance
	#define GET_IoMgrGetFirstDriverInstance(fl)  CAL_CMGETAPI( "IoMgrGetFirstDriverInstance" ) 
	#define CAL_IoMgrGetFirstDriverInstance pICmpIoMgr->IIoMgrGetFirstDriverInstance
	#define CHK_IoMgrGetFirstDriverInstance (pICmpIoMgr != NULL)
	#define EXP_IoMgrGetFirstDriverInstance  CAL_CMEXPAPI( "IoMgrGetFirstDriverInstance" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrGetFirstDriverInstance  PFIOMGRGETFIRSTDRIVERINSTANCE pfIoMgrGetFirstDriverInstance;
	#define EXT_IoMgrGetFirstDriverInstance  extern PFIOMGRGETFIRSTDRIVERINSTANCE pfIoMgrGetFirstDriverInstance;
	#define GET_IoMgrGetFirstDriverInstance(fl)  s_pfCMGetAPI2( "IoMgrGetFirstDriverInstance", (RTS_VOID_FCTPTR *)&pfIoMgrGetFirstDriverInstance, (fl), 0, 0)
	#define CAL_IoMgrGetFirstDriverInstance  pfIoMgrGetFirstDriverInstance
	#define CHK_IoMgrGetFirstDriverInstance  (pfIoMgrGetFirstDriverInstance != NULL)
	#define EXP_IoMgrGetFirstDriverInstance  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrGetFirstDriverInstance", (RTS_UINTPTR)IoMgrGetFirstDriverInstance, 0, 0) 
#endif




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
IBase* CDECL IoMgrGetNextDriverInstance(IBase *pIBasePrev, int *pbIecDriver, RTS_RESULT *pResult);
typedef IBase* (CDECL * PFIOMGRGETNEXTDRIVERINSTANCE) (IBase *pIBasePrev, int *pbIecDriver, RTS_RESULT *pResult);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRGETNEXTDRIVERINSTANCE_NOTIMPLEMENTED)
	#define USE_IoMgrGetNextDriverInstance
	#define EXT_IoMgrGetNextDriverInstance
	#define GET_IoMgrGetNextDriverInstance(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrGetNextDriverInstance(p0,p1,p2)  (IBase*)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrGetNextDriverInstance  FALSE
	#define EXP_IoMgrGetNextDriverInstance  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrGetNextDriverInstance
	#define EXT_IoMgrGetNextDriverInstance
	#define GET_IoMgrGetNextDriverInstance(fl)  CAL_CMGETAPI( "IoMgrGetNextDriverInstance" ) 
	#define CAL_IoMgrGetNextDriverInstance  IoMgrGetNextDriverInstance
	#define CHK_IoMgrGetNextDriverInstance  TRUE
	#define EXP_IoMgrGetNextDriverInstance  CAL_CMEXPAPI( "IoMgrGetNextDriverInstance" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrGetNextDriverInstance
	#define EXT_IoMgrGetNextDriverInstance
	#define GET_IoMgrGetNextDriverInstance(fl)  CAL_CMGETAPI( "IoMgrGetNextDriverInstance" ) 
	#define CAL_IoMgrGetNextDriverInstance  IoMgrGetNextDriverInstance
	#define CHK_IoMgrGetNextDriverInstance  TRUE
	#define EXP_IoMgrGetNextDriverInstance  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrGetNextDriverInstance", (RTS_UINTPTR)IoMgrGetNextDriverInstance, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrGetNextDriverInstance
	#define EXT_CmpIoMgrIoMgrGetNextDriverInstance
	#define GET_CmpIoMgrIoMgrGetNextDriverInstance  ERR_OK
	#define CAL_CmpIoMgrIoMgrGetNextDriverInstance pICmpIoMgr->IIoMgrGetNextDriverInstance
	#define CHK_CmpIoMgrIoMgrGetNextDriverInstance (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrGetNextDriverInstance  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrGetNextDriverInstance
	#define EXT_IoMgrGetNextDriverInstance
	#define GET_IoMgrGetNextDriverInstance(fl)  CAL_CMGETAPI( "IoMgrGetNextDriverInstance" ) 
	#define CAL_IoMgrGetNextDriverInstance pICmpIoMgr->IIoMgrGetNextDriverInstance
	#define CHK_IoMgrGetNextDriverInstance (pICmpIoMgr != NULL)
	#define EXP_IoMgrGetNextDriverInstance  CAL_CMEXPAPI( "IoMgrGetNextDriverInstance" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrGetNextDriverInstance  PFIOMGRGETNEXTDRIVERINSTANCE pfIoMgrGetNextDriverInstance;
	#define EXT_IoMgrGetNextDriverInstance  extern PFIOMGRGETNEXTDRIVERINSTANCE pfIoMgrGetNextDriverInstance;
	#define GET_IoMgrGetNextDriverInstance(fl)  s_pfCMGetAPI2( "IoMgrGetNextDriverInstance", (RTS_VOID_FCTPTR *)&pfIoMgrGetNextDriverInstance, (fl), 0, 0)
	#define CAL_IoMgrGetNextDriverInstance  pfIoMgrGetNextDriverInstance
	#define CHK_IoMgrGetNextDriverInstance  (pfIoMgrGetNextDriverInstance != NULL)
	#define EXP_IoMgrGetNextDriverInstance  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrGetNextDriverInstance", (RTS_UINTPTR)IoMgrGetNextDriverInstance, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrSetDriverProperties(IBase *pIBase, RTS_UI32 ulProperties);
typedef RTS_RESULT (CDECL * PFIOMGRSETDRIVERPROPERTIES) (IBase *pIBase, RTS_UI32 ulProperties);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRSETDRIVERPROPERTIES_NOTIMPLEMENTED)
	#define USE_IoMgrSetDriverProperties
	#define EXT_IoMgrSetDriverProperties
	#define GET_IoMgrSetDriverProperties(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrSetDriverProperties(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrSetDriverProperties  FALSE
	#define EXP_IoMgrSetDriverProperties  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrSetDriverProperties
	#define EXT_IoMgrSetDriverProperties
	#define GET_IoMgrSetDriverProperties(fl)  CAL_CMGETAPI( "IoMgrSetDriverProperties" ) 
	#define CAL_IoMgrSetDriverProperties  IoMgrSetDriverProperties
	#define CHK_IoMgrSetDriverProperties  TRUE
	#define EXP_IoMgrSetDriverProperties  CAL_CMEXPAPI( "IoMgrSetDriverProperties" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrSetDriverProperties
	#define EXT_IoMgrSetDriverProperties
	#define GET_IoMgrSetDriverProperties(fl)  CAL_CMGETAPI( "IoMgrSetDriverProperties" ) 
	#define CAL_IoMgrSetDriverProperties  IoMgrSetDriverProperties
	#define CHK_IoMgrSetDriverProperties  TRUE
	#define EXP_IoMgrSetDriverProperties  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrSetDriverProperties", (RTS_UINTPTR)IoMgrSetDriverProperties, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrSetDriverProperties
	#define EXT_CmpIoMgrIoMgrSetDriverProperties
	#define GET_CmpIoMgrIoMgrSetDriverProperties  ERR_OK
	#define CAL_CmpIoMgrIoMgrSetDriverProperties pICmpIoMgr->IIoMgrSetDriverProperties
	#define CHK_CmpIoMgrIoMgrSetDriverProperties (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrSetDriverProperties  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrSetDriverProperties
	#define EXT_IoMgrSetDriverProperties
	#define GET_IoMgrSetDriverProperties(fl)  CAL_CMGETAPI( "IoMgrSetDriverProperties" ) 
	#define CAL_IoMgrSetDriverProperties pICmpIoMgr->IIoMgrSetDriverProperties
	#define CHK_IoMgrSetDriverProperties (pICmpIoMgr != NULL)
	#define EXP_IoMgrSetDriverProperties  CAL_CMEXPAPI( "IoMgrSetDriverProperties" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrSetDriverProperties  PFIOMGRSETDRIVERPROPERTIES pfIoMgrSetDriverProperties;
	#define EXT_IoMgrSetDriverProperties  extern PFIOMGRSETDRIVERPROPERTIES pfIoMgrSetDriverProperties;
	#define GET_IoMgrSetDriverProperties(fl)  s_pfCMGetAPI2( "IoMgrSetDriverProperties", (RTS_VOID_FCTPTR *)&pfIoMgrSetDriverProperties, (fl), 0, 0)
	#define CAL_IoMgrSetDriverProperties  pfIoMgrSetDriverProperties
	#define CHK_IoMgrSetDriverProperties  (pfIoMgrSetDriverProperties != NULL)
	#define EXP_IoMgrSetDriverProperties  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrSetDriverProperties", (RTS_UINTPTR)IoMgrSetDriverProperties, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrGetDriverProperties(IBase *pIBase, RTS_UI32 **ppulProperty);
typedef RTS_RESULT (CDECL * PFIOMGRGETDRIVERPROPERTIES) (IBase *pIBase, RTS_UI32 **ppulProperty);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRGETDRIVERPROPERTIES_NOTIMPLEMENTED)
	#define USE_IoMgrGetDriverProperties
	#define EXT_IoMgrGetDriverProperties
	#define GET_IoMgrGetDriverProperties(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrGetDriverProperties(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrGetDriverProperties  FALSE
	#define EXP_IoMgrGetDriverProperties  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrGetDriverProperties
	#define EXT_IoMgrGetDriverProperties
	#define GET_IoMgrGetDriverProperties(fl)  CAL_CMGETAPI( "IoMgrGetDriverProperties" ) 
	#define CAL_IoMgrGetDriverProperties  IoMgrGetDriverProperties
	#define CHK_IoMgrGetDriverProperties  TRUE
	#define EXP_IoMgrGetDriverProperties  CAL_CMEXPAPI( "IoMgrGetDriverProperties" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrGetDriverProperties
	#define EXT_IoMgrGetDriverProperties
	#define GET_IoMgrGetDriverProperties(fl)  CAL_CMGETAPI( "IoMgrGetDriverProperties" ) 
	#define CAL_IoMgrGetDriverProperties  IoMgrGetDriverProperties
	#define CHK_IoMgrGetDriverProperties  TRUE
	#define EXP_IoMgrGetDriverProperties  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrGetDriverProperties", (RTS_UINTPTR)IoMgrGetDriverProperties, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrGetDriverProperties
	#define EXT_CmpIoMgrIoMgrGetDriverProperties
	#define GET_CmpIoMgrIoMgrGetDriverProperties  ERR_OK
	#define CAL_CmpIoMgrIoMgrGetDriverProperties pICmpIoMgr->IIoMgrGetDriverProperties
	#define CHK_CmpIoMgrIoMgrGetDriverProperties (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrGetDriverProperties  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrGetDriverProperties
	#define EXT_IoMgrGetDriverProperties
	#define GET_IoMgrGetDriverProperties(fl)  CAL_CMGETAPI( "IoMgrGetDriverProperties" ) 
	#define CAL_IoMgrGetDriverProperties pICmpIoMgr->IIoMgrGetDriverProperties
	#define CHK_IoMgrGetDriverProperties (pICmpIoMgr != NULL)
	#define EXP_IoMgrGetDriverProperties  CAL_CMEXPAPI( "IoMgrGetDriverProperties" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrGetDriverProperties  PFIOMGRGETDRIVERPROPERTIES pfIoMgrGetDriverProperties;
	#define EXT_IoMgrGetDriverProperties  extern PFIOMGRGETDRIVERPROPERTIES pfIoMgrGetDriverProperties;
	#define GET_IoMgrGetDriverProperties(fl)  s_pfCMGetAPI2( "IoMgrGetDriverProperties", (RTS_VOID_FCTPTR *)&pfIoMgrGetDriverProperties, (fl), 0, 0)
	#define CAL_IoMgrGetDriverProperties  pfIoMgrGetDriverProperties
	#define CHK_IoMgrGetDriverProperties  (pfIoMgrGetDriverProperties != NULL)
	#define EXP_IoMgrGetDriverProperties  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrGetDriverProperties", (RTS_UINTPTR)IoMgrGetDriverProperties, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrSetDriverProperty(IBase *pIBase, RTS_UI32 ulProperty, int bValue);
typedef RTS_RESULT (CDECL * PFIOMGRSETDRIVERPROPERTY) (IBase *pIBase, RTS_UI32 ulProperty, int bValue);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRSETDRIVERPROPERTY_NOTIMPLEMENTED)
	#define USE_IoMgrSetDriverProperty
	#define EXT_IoMgrSetDriverProperty
	#define GET_IoMgrSetDriverProperty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrSetDriverProperty(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrSetDriverProperty  FALSE
	#define EXP_IoMgrSetDriverProperty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrSetDriverProperty
	#define EXT_IoMgrSetDriverProperty
	#define GET_IoMgrSetDriverProperty(fl)  CAL_CMGETAPI( "IoMgrSetDriverProperty" ) 
	#define CAL_IoMgrSetDriverProperty  IoMgrSetDriverProperty
	#define CHK_IoMgrSetDriverProperty  TRUE
	#define EXP_IoMgrSetDriverProperty  CAL_CMEXPAPI( "IoMgrSetDriverProperty" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrSetDriverProperty
	#define EXT_IoMgrSetDriverProperty
	#define GET_IoMgrSetDriverProperty(fl)  CAL_CMGETAPI( "IoMgrSetDriverProperty" ) 
	#define CAL_IoMgrSetDriverProperty  IoMgrSetDriverProperty
	#define CHK_IoMgrSetDriverProperty  TRUE
	#define EXP_IoMgrSetDriverProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrSetDriverProperty", (RTS_UINTPTR)IoMgrSetDriverProperty, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrSetDriverProperty
	#define EXT_CmpIoMgrIoMgrSetDriverProperty
	#define GET_CmpIoMgrIoMgrSetDriverProperty  ERR_OK
	#define CAL_CmpIoMgrIoMgrSetDriverProperty pICmpIoMgr->IIoMgrSetDriverProperty
	#define CHK_CmpIoMgrIoMgrSetDriverProperty (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrSetDriverProperty  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrSetDriverProperty
	#define EXT_IoMgrSetDriverProperty
	#define GET_IoMgrSetDriverProperty(fl)  CAL_CMGETAPI( "IoMgrSetDriverProperty" ) 
	#define CAL_IoMgrSetDriverProperty pICmpIoMgr->IIoMgrSetDriverProperty
	#define CHK_IoMgrSetDriverProperty (pICmpIoMgr != NULL)
	#define EXP_IoMgrSetDriverProperty  CAL_CMEXPAPI( "IoMgrSetDriverProperty" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrSetDriverProperty  PFIOMGRSETDRIVERPROPERTY pfIoMgrSetDriverProperty;
	#define EXT_IoMgrSetDriverProperty  extern PFIOMGRSETDRIVERPROPERTY pfIoMgrSetDriverProperty;
	#define GET_IoMgrSetDriverProperty(fl)  s_pfCMGetAPI2( "IoMgrSetDriverProperty", (RTS_VOID_FCTPTR *)&pfIoMgrSetDriverProperty, (fl), 0, 0)
	#define CAL_IoMgrSetDriverProperty  pfIoMgrSetDriverProperty
	#define CHK_IoMgrSetDriverProperty  (pfIoMgrSetDriverProperty != NULL)
	#define EXP_IoMgrSetDriverProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrSetDriverProperty", (RTS_UINTPTR)IoMgrSetDriverProperty, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrRegisterConfigApplication(char *pszConfigApplication);
typedef RTS_RESULT (CDECL * PFIOMGRREGISTERCONFIGAPPLICATION) (char *pszConfigApplication);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRREGISTERCONFIGAPPLICATION_NOTIMPLEMENTED)
	#define USE_IoMgrRegisterConfigApplication
	#define EXT_IoMgrRegisterConfigApplication
	#define GET_IoMgrRegisterConfigApplication(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrRegisterConfigApplication(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrRegisterConfigApplication  FALSE
	#define EXP_IoMgrRegisterConfigApplication  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrRegisterConfigApplication
	#define EXT_IoMgrRegisterConfigApplication
	#define GET_IoMgrRegisterConfigApplication(fl)  CAL_CMGETAPI( "IoMgrRegisterConfigApplication" ) 
	#define CAL_IoMgrRegisterConfigApplication  IoMgrRegisterConfigApplication
	#define CHK_IoMgrRegisterConfigApplication  TRUE
	#define EXP_IoMgrRegisterConfigApplication  CAL_CMEXPAPI( "IoMgrRegisterConfigApplication" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrRegisterConfigApplication
	#define EXT_IoMgrRegisterConfigApplication
	#define GET_IoMgrRegisterConfigApplication(fl)  CAL_CMGETAPI( "IoMgrRegisterConfigApplication" ) 
	#define CAL_IoMgrRegisterConfigApplication  IoMgrRegisterConfigApplication
	#define CHK_IoMgrRegisterConfigApplication  TRUE
	#define EXP_IoMgrRegisterConfigApplication  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrRegisterConfigApplication", (RTS_UINTPTR)IoMgrRegisterConfigApplication, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrRegisterConfigApplication
	#define EXT_CmpIoMgrIoMgrRegisterConfigApplication
	#define GET_CmpIoMgrIoMgrRegisterConfigApplication  ERR_OK
	#define CAL_CmpIoMgrIoMgrRegisterConfigApplication pICmpIoMgr->IIoMgrRegisterConfigApplication
	#define CHK_CmpIoMgrIoMgrRegisterConfigApplication (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrRegisterConfigApplication  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrRegisterConfigApplication
	#define EXT_IoMgrRegisterConfigApplication
	#define GET_IoMgrRegisterConfigApplication(fl)  CAL_CMGETAPI( "IoMgrRegisterConfigApplication" ) 
	#define CAL_IoMgrRegisterConfigApplication pICmpIoMgr->IIoMgrRegisterConfigApplication
	#define CHK_IoMgrRegisterConfigApplication (pICmpIoMgr != NULL)
	#define EXP_IoMgrRegisterConfigApplication  CAL_CMEXPAPI( "IoMgrRegisterConfigApplication" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrRegisterConfigApplication  PFIOMGRREGISTERCONFIGAPPLICATION pfIoMgrRegisterConfigApplication;
	#define EXT_IoMgrRegisterConfigApplication  extern PFIOMGRREGISTERCONFIGAPPLICATION pfIoMgrRegisterConfigApplication;
	#define GET_IoMgrRegisterConfigApplication(fl)  s_pfCMGetAPI2( "IoMgrRegisterConfigApplication", (RTS_VOID_FCTPTR *)&pfIoMgrRegisterConfigApplication, (fl), 0, 0)
	#define CAL_IoMgrRegisterConfigApplication  pfIoMgrRegisterConfigApplication
	#define CHK_IoMgrRegisterConfigApplication  (pfIoMgrRegisterConfigApplication != NULL)
	#define EXP_IoMgrRegisterConfigApplication  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrRegisterConfigApplication", (RTS_UINTPTR)IoMgrRegisterConfigApplication, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrUnregisterConfigApplication(char *pszConfigApplication);
typedef RTS_RESULT (CDECL * PFIOMGRUNREGISTERCONFIGAPPLICATION) (char *pszConfigApplication);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRUNREGISTERCONFIGAPPLICATION_NOTIMPLEMENTED)
	#define USE_IoMgrUnregisterConfigApplication
	#define EXT_IoMgrUnregisterConfigApplication
	#define GET_IoMgrUnregisterConfigApplication(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrUnregisterConfigApplication(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrUnregisterConfigApplication  FALSE
	#define EXP_IoMgrUnregisterConfigApplication  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrUnregisterConfigApplication
	#define EXT_IoMgrUnregisterConfigApplication
	#define GET_IoMgrUnregisterConfigApplication(fl)  CAL_CMGETAPI( "IoMgrUnregisterConfigApplication" ) 
	#define CAL_IoMgrUnregisterConfigApplication  IoMgrUnregisterConfigApplication
	#define CHK_IoMgrUnregisterConfigApplication  TRUE
	#define EXP_IoMgrUnregisterConfigApplication  CAL_CMEXPAPI( "IoMgrUnregisterConfigApplication" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrUnregisterConfigApplication
	#define EXT_IoMgrUnregisterConfigApplication
	#define GET_IoMgrUnregisterConfigApplication(fl)  CAL_CMGETAPI( "IoMgrUnregisterConfigApplication" ) 
	#define CAL_IoMgrUnregisterConfigApplication  IoMgrUnregisterConfigApplication
	#define CHK_IoMgrUnregisterConfigApplication  TRUE
	#define EXP_IoMgrUnregisterConfigApplication  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrUnregisterConfigApplication", (RTS_UINTPTR)IoMgrUnregisterConfigApplication, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrUnregisterConfigApplication
	#define EXT_CmpIoMgrIoMgrUnregisterConfigApplication
	#define GET_CmpIoMgrIoMgrUnregisterConfigApplication  ERR_OK
	#define CAL_CmpIoMgrIoMgrUnregisterConfigApplication pICmpIoMgr->IIoMgrUnregisterConfigApplication
	#define CHK_CmpIoMgrIoMgrUnregisterConfigApplication (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrUnregisterConfigApplication  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrUnregisterConfigApplication
	#define EXT_IoMgrUnregisterConfigApplication
	#define GET_IoMgrUnregisterConfigApplication(fl)  CAL_CMGETAPI( "IoMgrUnregisterConfigApplication" ) 
	#define CAL_IoMgrUnregisterConfigApplication pICmpIoMgr->IIoMgrUnregisterConfigApplication
	#define CHK_IoMgrUnregisterConfigApplication (pICmpIoMgr != NULL)
	#define EXP_IoMgrUnregisterConfigApplication  CAL_CMEXPAPI( "IoMgrUnregisterConfigApplication" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrUnregisterConfigApplication  PFIOMGRUNREGISTERCONFIGAPPLICATION pfIoMgrUnregisterConfigApplication;
	#define EXT_IoMgrUnregisterConfigApplication  extern PFIOMGRUNREGISTERCONFIGAPPLICATION pfIoMgrUnregisterConfigApplication;
	#define GET_IoMgrUnregisterConfigApplication(fl)  s_pfCMGetAPI2( "IoMgrUnregisterConfigApplication", (RTS_VOID_FCTPTR *)&pfIoMgrUnregisterConfigApplication, (fl), 0, 0)
	#define CAL_IoMgrUnregisterConfigApplication  pfIoMgrUnregisterConfigApplication
	#define CHK_IoMgrUnregisterConfigApplication  (pfIoMgrUnregisterConfigApplication != NULL)
	#define EXP_IoMgrUnregisterConfigApplication  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrUnregisterConfigApplication", (RTS_UINTPTR)IoMgrUnregisterConfigApplication, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrGetConfigApplication(char *pszConfigApplication, int *pnMaxLen);
typedef RTS_RESULT (CDECL * PFIOMGRGETCONFIGAPPLICATION) (char *pszConfigApplication, int *pnMaxLen);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRGETCONFIGAPPLICATION_NOTIMPLEMENTED)
	#define USE_IoMgrGetConfigApplication
	#define EXT_IoMgrGetConfigApplication
	#define GET_IoMgrGetConfigApplication(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrGetConfigApplication(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrGetConfigApplication  FALSE
	#define EXP_IoMgrGetConfigApplication  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrGetConfigApplication
	#define EXT_IoMgrGetConfigApplication
	#define GET_IoMgrGetConfigApplication(fl)  CAL_CMGETAPI( "IoMgrGetConfigApplication" ) 
	#define CAL_IoMgrGetConfigApplication  IoMgrGetConfigApplication
	#define CHK_IoMgrGetConfigApplication  TRUE
	#define EXP_IoMgrGetConfigApplication  CAL_CMEXPAPI( "IoMgrGetConfigApplication" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrGetConfigApplication
	#define EXT_IoMgrGetConfigApplication
	#define GET_IoMgrGetConfigApplication(fl)  CAL_CMGETAPI( "IoMgrGetConfigApplication" ) 
	#define CAL_IoMgrGetConfigApplication  IoMgrGetConfigApplication
	#define CHK_IoMgrGetConfigApplication  TRUE
	#define EXP_IoMgrGetConfigApplication  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrGetConfigApplication", (RTS_UINTPTR)IoMgrGetConfigApplication, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrGetConfigApplication
	#define EXT_CmpIoMgrIoMgrGetConfigApplication
	#define GET_CmpIoMgrIoMgrGetConfigApplication  ERR_OK
	#define CAL_CmpIoMgrIoMgrGetConfigApplication pICmpIoMgr->IIoMgrGetConfigApplication
	#define CHK_CmpIoMgrIoMgrGetConfigApplication (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrGetConfigApplication  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrGetConfigApplication
	#define EXT_IoMgrGetConfigApplication
	#define GET_IoMgrGetConfigApplication(fl)  CAL_CMGETAPI( "IoMgrGetConfigApplication" ) 
	#define CAL_IoMgrGetConfigApplication pICmpIoMgr->IIoMgrGetConfigApplication
	#define CHK_IoMgrGetConfigApplication (pICmpIoMgr != NULL)
	#define EXP_IoMgrGetConfigApplication  CAL_CMEXPAPI( "IoMgrGetConfigApplication" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrGetConfigApplication  PFIOMGRGETCONFIGAPPLICATION pfIoMgrGetConfigApplication;
	#define EXT_IoMgrGetConfigApplication  extern PFIOMGRGETCONFIGAPPLICATION pfIoMgrGetConfigApplication;
	#define GET_IoMgrGetConfigApplication(fl)  s_pfCMGetAPI2( "IoMgrGetConfigApplication", (RTS_VOID_FCTPTR *)&pfIoMgrGetConfigApplication, (fl), 0, 0)
	#define CAL_IoMgrGetConfigApplication  pfIoMgrGetConfigApplication
	#define CHK_IoMgrGetConfigApplication  (pfIoMgrGetConfigApplication != NULL)
	#define EXP_IoMgrGetConfigApplication  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrGetConfigApplication", (RTS_UINTPTR)IoMgrGetConfigApplication, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrUpdateConfiguration(IoConfigConnector *pConnectorList, int nCount);
typedef RTS_RESULT (CDECL * PFIOMGRUPDATECONFIGURATION) (IoConfigConnector *pConnectorList, int nCount);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRUPDATECONFIGURATION_NOTIMPLEMENTED)
	#define USE_IoMgrUpdateConfiguration
	#define EXT_IoMgrUpdateConfiguration
	#define GET_IoMgrUpdateConfiguration(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrUpdateConfiguration(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrUpdateConfiguration  FALSE
	#define EXP_IoMgrUpdateConfiguration  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrUpdateConfiguration
	#define EXT_IoMgrUpdateConfiguration
	#define GET_IoMgrUpdateConfiguration(fl)  CAL_CMGETAPI( "IoMgrUpdateConfiguration" ) 
	#define CAL_IoMgrUpdateConfiguration  IoMgrUpdateConfiguration
	#define CHK_IoMgrUpdateConfiguration  TRUE
	#define EXP_IoMgrUpdateConfiguration  CAL_CMEXPAPI( "IoMgrUpdateConfiguration" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrUpdateConfiguration
	#define EXT_IoMgrUpdateConfiguration
	#define GET_IoMgrUpdateConfiguration(fl)  CAL_CMGETAPI( "IoMgrUpdateConfiguration" ) 
	#define CAL_IoMgrUpdateConfiguration  IoMgrUpdateConfiguration
	#define CHK_IoMgrUpdateConfiguration  TRUE
	#define EXP_IoMgrUpdateConfiguration  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrUpdateConfiguration", (RTS_UINTPTR)IoMgrUpdateConfiguration, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrUpdateConfiguration
	#define EXT_CmpIoMgrIoMgrUpdateConfiguration
	#define GET_CmpIoMgrIoMgrUpdateConfiguration  ERR_OK
	#define CAL_CmpIoMgrIoMgrUpdateConfiguration pICmpIoMgr->IIoMgrUpdateConfiguration
	#define CHK_CmpIoMgrIoMgrUpdateConfiguration (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrUpdateConfiguration  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrUpdateConfiguration
	#define EXT_IoMgrUpdateConfiguration
	#define GET_IoMgrUpdateConfiguration(fl)  CAL_CMGETAPI( "IoMgrUpdateConfiguration" ) 
	#define CAL_IoMgrUpdateConfiguration pICmpIoMgr->IIoMgrUpdateConfiguration
	#define CHK_IoMgrUpdateConfiguration (pICmpIoMgr != NULL)
	#define EXP_IoMgrUpdateConfiguration  CAL_CMEXPAPI( "IoMgrUpdateConfiguration" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrUpdateConfiguration  PFIOMGRUPDATECONFIGURATION pfIoMgrUpdateConfiguration;
	#define EXT_IoMgrUpdateConfiguration  extern PFIOMGRUPDATECONFIGURATION pfIoMgrUpdateConfiguration;
	#define GET_IoMgrUpdateConfiguration(fl)  s_pfCMGetAPI2( "IoMgrUpdateConfiguration", (RTS_VOID_FCTPTR *)&pfIoMgrUpdateConfiguration, (fl), 0, 0)
	#define CAL_IoMgrUpdateConfiguration  pfIoMgrUpdateConfiguration
	#define CHK_IoMgrUpdateConfiguration  (pfIoMgrUpdateConfiguration != NULL)
	#define EXP_IoMgrUpdateConfiguration  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrUpdateConfiguration", (RTS_UINTPTR)IoMgrUpdateConfiguration, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrUpdateConfiguration2(IoConfigConnector *pConnectorList, int nCount, char *pszConfigApplication);
typedef RTS_RESULT (CDECL * PFIOMGRUPDATECONFIGURATION2) (IoConfigConnector *pConnectorList, int nCount, char *pszConfigApplication);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRUPDATECONFIGURATION2_NOTIMPLEMENTED)
	#define USE_IoMgrUpdateConfiguration2
	#define EXT_IoMgrUpdateConfiguration2
	#define GET_IoMgrUpdateConfiguration2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrUpdateConfiguration2(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrUpdateConfiguration2  FALSE
	#define EXP_IoMgrUpdateConfiguration2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrUpdateConfiguration2
	#define EXT_IoMgrUpdateConfiguration2
	#define GET_IoMgrUpdateConfiguration2(fl)  CAL_CMGETAPI( "IoMgrUpdateConfiguration2" ) 
	#define CAL_IoMgrUpdateConfiguration2  IoMgrUpdateConfiguration2
	#define CHK_IoMgrUpdateConfiguration2  TRUE
	#define EXP_IoMgrUpdateConfiguration2  CAL_CMEXPAPI( "IoMgrUpdateConfiguration2" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrUpdateConfiguration2
	#define EXT_IoMgrUpdateConfiguration2
	#define GET_IoMgrUpdateConfiguration2(fl)  CAL_CMGETAPI( "IoMgrUpdateConfiguration2" ) 
	#define CAL_IoMgrUpdateConfiguration2  IoMgrUpdateConfiguration2
	#define CHK_IoMgrUpdateConfiguration2  TRUE
	#define EXP_IoMgrUpdateConfiguration2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrUpdateConfiguration2", (RTS_UINTPTR)IoMgrUpdateConfiguration2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrUpdateConfiguration2
	#define EXT_CmpIoMgrIoMgrUpdateConfiguration2
	#define GET_CmpIoMgrIoMgrUpdateConfiguration2  ERR_OK
	#define CAL_CmpIoMgrIoMgrUpdateConfiguration2 pICmpIoMgr->IIoMgrUpdateConfiguration2
	#define CHK_CmpIoMgrIoMgrUpdateConfiguration2 (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrUpdateConfiguration2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrUpdateConfiguration2
	#define EXT_IoMgrUpdateConfiguration2
	#define GET_IoMgrUpdateConfiguration2(fl)  CAL_CMGETAPI( "IoMgrUpdateConfiguration2" ) 
	#define CAL_IoMgrUpdateConfiguration2 pICmpIoMgr->IIoMgrUpdateConfiguration2
	#define CHK_IoMgrUpdateConfiguration2 (pICmpIoMgr != NULL)
	#define EXP_IoMgrUpdateConfiguration2  CAL_CMEXPAPI( "IoMgrUpdateConfiguration2" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrUpdateConfiguration2  PFIOMGRUPDATECONFIGURATION2 pfIoMgrUpdateConfiguration2;
	#define EXT_IoMgrUpdateConfiguration2  extern PFIOMGRUPDATECONFIGURATION2 pfIoMgrUpdateConfiguration2;
	#define GET_IoMgrUpdateConfiguration2(fl)  s_pfCMGetAPI2( "IoMgrUpdateConfiguration2", (RTS_VOID_FCTPTR *)&pfIoMgrUpdateConfiguration2, (fl), 0, 0)
	#define CAL_IoMgrUpdateConfiguration2  pfIoMgrUpdateConfiguration2
	#define CHK_IoMgrUpdateConfiguration2  (pfIoMgrUpdateConfiguration2 != NULL)
	#define EXP_IoMgrUpdateConfiguration2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrUpdateConfiguration2", (RTS_UINTPTR)IoMgrUpdateConfiguration2, 0, 0) 
#endif




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
RTS_BOOL CDECL IoMgrHasTaskIOs(RTS_UI32 dwTaskId, RTS_UI16 taskMapType, RTS_RESULT *pResult);
typedef RTS_BOOL (CDECL * PFIOMGRHASTASKIOS) (RTS_UI32 dwTaskId, RTS_UI16 taskMapType, RTS_RESULT *pResult);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRHASTASKIOS_NOTIMPLEMENTED)
	#define USE_IoMgrHasTaskIOs
	#define EXT_IoMgrHasTaskIOs
	#define GET_IoMgrHasTaskIOs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrHasTaskIOs(p0,p1,p2)  (RTS_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrHasTaskIOs  FALSE
	#define EXP_IoMgrHasTaskIOs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrHasTaskIOs
	#define EXT_IoMgrHasTaskIOs
	#define GET_IoMgrHasTaskIOs(fl)  CAL_CMGETAPI( "IoMgrHasTaskIOs" ) 
	#define CAL_IoMgrHasTaskIOs  IoMgrHasTaskIOs
	#define CHK_IoMgrHasTaskIOs  TRUE
	#define EXP_IoMgrHasTaskIOs  CAL_CMEXPAPI( "IoMgrHasTaskIOs" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrHasTaskIOs
	#define EXT_IoMgrHasTaskIOs
	#define GET_IoMgrHasTaskIOs(fl)  CAL_CMGETAPI( "IoMgrHasTaskIOs" ) 
	#define CAL_IoMgrHasTaskIOs  IoMgrHasTaskIOs
	#define CHK_IoMgrHasTaskIOs  TRUE
	#define EXP_IoMgrHasTaskIOs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrHasTaskIOs", (RTS_UINTPTR)IoMgrHasTaskIOs, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrHasTaskIOs
	#define EXT_CmpIoMgrIoMgrHasTaskIOs
	#define GET_CmpIoMgrIoMgrHasTaskIOs  ERR_OK
	#define CAL_CmpIoMgrIoMgrHasTaskIOs pICmpIoMgr->IIoMgrHasTaskIOs
	#define CHK_CmpIoMgrIoMgrHasTaskIOs (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrHasTaskIOs  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrHasTaskIOs
	#define EXT_IoMgrHasTaskIOs
	#define GET_IoMgrHasTaskIOs(fl)  CAL_CMGETAPI( "IoMgrHasTaskIOs" ) 
	#define CAL_IoMgrHasTaskIOs pICmpIoMgr->IIoMgrHasTaskIOs
	#define CHK_IoMgrHasTaskIOs (pICmpIoMgr != NULL)
	#define EXP_IoMgrHasTaskIOs  CAL_CMEXPAPI( "IoMgrHasTaskIOs" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrHasTaskIOs  PFIOMGRHASTASKIOS pfIoMgrHasTaskIOs;
	#define EXT_IoMgrHasTaskIOs  extern PFIOMGRHASTASKIOS pfIoMgrHasTaskIOs;
	#define GET_IoMgrHasTaskIOs(fl)  s_pfCMGetAPI2( "IoMgrHasTaskIOs", (RTS_VOID_FCTPTR *)&pfIoMgrHasTaskIOs, (fl), 0, 0)
	#define CAL_IoMgrHasTaskIOs  pfIoMgrHasTaskIOs
	#define CHK_IoMgrHasTaskIOs  (pfIoMgrHasTaskIOs != NULL)
	#define EXP_IoMgrHasTaskIOs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrHasTaskIOs", (RTS_UINTPTR)IoMgrHasTaskIOs, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrUpdateMapping(IoConfigTaskMap *pTaskMapList, int nCount);
typedef RTS_RESULT (CDECL * PFIOMGRUPDATEMAPPING) (IoConfigTaskMap *pTaskMapList, int nCount);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRUPDATEMAPPING_NOTIMPLEMENTED)
	#define USE_IoMgrUpdateMapping
	#define EXT_IoMgrUpdateMapping
	#define GET_IoMgrUpdateMapping(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrUpdateMapping(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrUpdateMapping  FALSE
	#define EXP_IoMgrUpdateMapping  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrUpdateMapping
	#define EXT_IoMgrUpdateMapping
	#define GET_IoMgrUpdateMapping(fl)  CAL_CMGETAPI( "IoMgrUpdateMapping" ) 
	#define CAL_IoMgrUpdateMapping  IoMgrUpdateMapping
	#define CHK_IoMgrUpdateMapping  TRUE
	#define EXP_IoMgrUpdateMapping  CAL_CMEXPAPI( "IoMgrUpdateMapping" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrUpdateMapping
	#define EXT_IoMgrUpdateMapping
	#define GET_IoMgrUpdateMapping(fl)  CAL_CMGETAPI( "IoMgrUpdateMapping" ) 
	#define CAL_IoMgrUpdateMapping  IoMgrUpdateMapping
	#define CHK_IoMgrUpdateMapping  TRUE
	#define EXP_IoMgrUpdateMapping  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrUpdateMapping", (RTS_UINTPTR)IoMgrUpdateMapping, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrUpdateMapping
	#define EXT_CmpIoMgrIoMgrUpdateMapping
	#define GET_CmpIoMgrIoMgrUpdateMapping  ERR_OK
	#define CAL_CmpIoMgrIoMgrUpdateMapping pICmpIoMgr->IIoMgrUpdateMapping
	#define CHK_CmpIoMgrIoMgrUpdateMapping (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrUpdateMapping  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrUpdateMapping
	#define EXT_IoMgrUpdateMapping
	#define GET_IoMgrUpdateMapping(fl)  CAL_CMGETAPI( "IoMgrUpdateMapping" ) 
	#define CAL_IoMgrUpdateMapping pICmpIoMgr->IIoMgrUpdateMapping
	#define CHK_IoMgrUpdateMapping (pICmpIoMgr != NULL)
	#define EXP_IoMgrUpdateMapping  CAL_CMEXPAPI( "IoMgrUpdateMapping" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrUpdateMapping  PFIOMGRUPDATEMAPPING pfIoMgrUpdateMapping;
	#define EXT_IoMgrUpdateMapping  extern PFIOMGRUPDATEMAPPING pfIoMgrUpdateMapping;
	#define GET_IoMgrUpdateMapping(fl)  s_pfCMGetAPI2( "IoMgrUpdateMapping", (RTS_VOID_FCTPTR *)&pfIoMgrUpdateMapping, (fl), 0, 0)
	#define CAL_IoMgrUpdateMapping  pfIoMgrUpdateMapping
	#define CHK_IoMgrUpdateMapping  (pfIoMgrUpdateMapping != NULL)
	#define EXP_IoMgrUpdateMapping  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrUpdateMapping", (RTS_UINTPTR)IoMgrUpdateMapping, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrUpdateMapping2(IoConfigTaskMap *pTaskMapList, int nCount, char *pszConfigApplication);
typedef RTS_RESULT (CDECL * PFIOMGRUPDATEMAPPING2) (IoConfigTaskMap *pTaskMapList, int nCount, char *pszConfigApplication);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRUPDATEMAPPING2_NOTIMPLEMENTED)
	#define USE_IoMgrUpdateMapping2
	#define EXT_IoMgrUpdateMapping2
	#define GET_IoMgrUpdateMapping2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrUpdateMapping2(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrUpdateMapping2  FALSE
	#define EXP_IoMgrUpdateMapping2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrUpdateMapping2
	#define EXT_IoMgrUpdateMapping2
	#define GET_IoMgrUpdateMapping2(fl)  CAL_CMGETAPI( "IoMgrUpdateMapping2" ) 
	#define CAL_IoMgrUpdateMapping2  IoMgrUpdateMapping2
	#define CHK_IoMgrUpdateMapping2  TRUE
	#define EXP_IoMgrUpdateMapping2  CAL_CMEXPAPI( "IoMgrUpdateMapping2" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrUpdateMapping2
	#define EXT_IoMgrUpdateMapping2
	#define GET_IoMgrUpdateMapping2(fl)  CAL_CMGETAPI( "IoMgrUpdateMapping2" ) 
	#define CAL_IoMgrUpdateMapping2  IoMgrUpdateMapping2
	#define CHK_IoMgrUpdateMapping2  TRUE
	#define EXP_IoMgrUpdateMapping2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrUpdateMapping2", (RTS_UINTPTR)IoMgrUpdateMapping2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrUpdateMapping2
	#define EXT_CmpIoMgrIoMgrUpdateMapping2
	#define GET_CmpIoMgrIoMgrUpdateMapping2  ERR_OK
	#define CAL_CmpIoMgrIoMgrUpdateMapping2 pICmpIoMgr->IIoMgrUpdateMapping2
	#define CHK_CmpIoMgrIoMgrUpdateMapping2 (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrUpdateMapping2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrUpdateMapping2
	#define EXT_IoMgrUpdateMapping2
	#define GET_IoMgrUpdateMapping2(fl)  CAL_CMGETAPI( "IoMgrUpdateMapping2" ) 
	#define CAL_IoMgrUpdateMapping2 pICmpIoMgr->IIoMgrUpdateMapping2
	#define CHK_IoMgrUpdateMapping2 (pICmpIoMgr != NULL)
	#define EXP_IoMgrUpdateMapping2  CAL_CMEXPAPI( "IoMgrUpdateMapping2" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrUpdateMapping2  PFIOMGRUPDATEMAPPING2 pfIoMgrUpdateMapping2;
	#define EXT_IoMgrUpdateMapping2  extern PFIOMGRUPDATEMAPPING2 pfIoMgrUpdateMapping2;
	#define GET_IoMgrUpdateMapping2(fl)  s_pfCMGetAPI2( "IoMgrUpdateMapping2", (RTS_VOID_FCTPTR *)&pfIoMgrUpdateMapping2, (fl), 0, 0)
	#define CAL_IoMgrUpdateMapping2  pfIoMgrUpdateMapping2
	#define CHK_IoMgrUpdateMapping2  (pfIoMgrUpdateMapping2 != NULL)
	#define EXP_IoMgrUpdateMapping2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrUpdateMapping2", (RTS_UINTPTR)IoMgrUpdateMapping2, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrReconfigure(IoConfigConnector *pConnector, RTS_UI32 *pui32State);
typedef RTS_RESULT (CDECL * PFIOMGRRECONFIGURE) (IoConfigConnector *pConnector, RTS_UI32 *pui32State);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRRECONFIGURE_NOTIMPLEMENTED)
	#define USE_IoMgrReconfigure
	#define EXT_IoMgrReconfigure
	#define GET_IoMgrReconfigure(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrReconfigure(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrReconfigure  FALSE
	#define EXP_IoMgrReconfigure  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrReconfigure
	#define EXT_IoMgrReconfigure
	#define GET_IoMgrReconfigure(fl)  CAL_CMGETAPI( "IoMgrReconfigure" ) 
	#define CAL_IoMgrReconfigure  IoMgrReconfigure
	#define CHK_IoMgrReconfigure  TRUE
	#define EXP_IoMgrReconfigure  CAL_CMEXPAPI( "IoMgrReconfigure" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrReconfigure
	#define EXT_IoMgrReconfigure
	#define GET_IoMgrReconfigure(fl)  CAL_CMGETAPI( "IoMgrReconfigure" ) 
	#define CAL_IoMgrReconfigure  IoMgrReconfigure
	#define CHK_IoMgrReconfigure  TRUE
	#define EXP_IoMgrReconfigure  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrReconfigure", (RTS_UINTPTR)IoMgrReconfigure, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrReconfigure
	#define EXT_CmpIoMgrIoMgrReconfigure
	#define GET_CmpIoMgrIoMgrReconfigure  ERR_OK
	#define CAL_CmpIoMgrIoMgrReconfigure pICmpIoMgr->IIoMgrReconfigure
	#define CHK_CmpIoMgrIoMgrReconfigure (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrReconfigure  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrReconfigure
	#define EXT_IoMgrReconfigure
	#define GET_IoMgrReconfigure(fl)  CAL_CMGETAPI( "IoMgrReconfigure" ) 
	#define CAL_IoMgrReconfigure pICmpIoMgr->IIoMgrReconfigure
	#define CHK_IoMgrReconfigure (pICmpIoMgr != NULL)
	#define EXP_IoMgrReconfigure  CAL_CMEXPAPI( "IoMgrReconfigure" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrReconfigure  PFIOMGRRECONFIGURE pfIoMgrReconfigure;
	#define EXT_IoMgrReconfigure  extern PFIOMGRRECONFIGURE pfIoMgrReconfigure;
	#define GET_IoMgrReconfigure(fl)  s_pfCMGetAPI2( "IoMgrReconfigure", (RTS_VOID_FCTPTR *)&pfIoMgrReconfigure, (fl), 0, 0)
	#define CAL_IoMgrReconfigure  pfIoMgrReconfigure
	#define CHK_IoMgrReconfigure  (pfIoMgrReconfigure != NULL)
	#define EXP_IoMgrReconfigure  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrReconfigure", (RTS_UINTPTR)IoMgrReconfigure, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrReadInputs(IoConfigTaskMap *pTaskMap);
typedef RTS_RESULT (CDECL * PFIOMGRREADINPUTS) (IoConfigTaskMap *pTaskMap);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRREADINPUTS_NOTIMPLEMENTED)
	#define USE_IoMgrReadInputs
	#define EXT_IoMgrReadInputs
	#define GET_IoMgrReadInputs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrReadInputs(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrReadInputs  FALSE
	#define EXP_IoMgrReadInputs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrReadInputs
	#define EXT_IoMgrReadInputs
	#define GET_IoMgrReadInputs(fl)  CAL_CMGETAPI( "IoMgrReadInputs" ) 
	#define CAL_IoMgrReadInputs  IoMgrReadInputs
	#define CHK_IoMgrReadInputs  TRUE
	#define EXP_IoMgrReadInputs  CAL_CMEXPAPI( "IoMgrReadInputs" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrReadInputs
	#define EXT_IoMgrReadInputs
	#define GET_IoMgrReadInputs(fl)  CAL_CMGETAPI( "IoMgrReadInputs" ) 
	#define CAL_IoMgrReadInputs  IoMgrReadInputs
	#define CHK_IoMgrReadInputs  TRUE
	#define EXP_IoMgrReadInputs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrReadInputs", (RTS_UINTPTR)IoMgrReadInputs, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrReadInputs
	#define EXT_CmpIoMgrIoMgrReadInputs
	#define GET_CmpIoMgrIoMgrReadInputs  ERR_OK
	#define CAL_CmpIoMgrIoMgrReadInputs pICmpIoMgr->IIoMgrReadInputs
	#define CHK_CmpIoMgrIoMgrReadInputs (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrReadInputs  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrReadInputs
	#define EXT_IoMgrReadInputs
	#define GET_IoMgrReadInputs(fl)  CAL_CMGETAPI( "IoMgrReadInputs" ) 
	#define CAL_IoMgrReadInputs pICmpIoMgr->IIoMgrReadInputs
	#define CHK_IoMgrReadInputs (pICmpIoMgr != NULL)
	#define EXP_IoMgrReadInputs  CAL_CMEXPAPI( "IoMgrReadInputs" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrReadInputs  PFIOMGRREADINPUTS pfIoMgrReadInputs;
	#define EXT_IoMgrReadInputs  extern PFIOMGRREADINPUTS pfIoMgrReadInputs;
	#define GET_IoMgrReadInputs(fl)  s_pfCMGetAPI2( "IoMgrReadInputs", (RTS_VOID_FCTPTR *)&pfIoMgrReadInputs, (fl), 0, 0)
	#define CAL_IoMgrReadInputs  pfIoMgrReadInputs
	#define CHK_IoMgrReadInputs  (pfIoMgrReadInputs != NULL)
	#define EXP_IoMgrReadInputs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrReadInputs", (RTS_UINTPTR)IoMgrReadInputs, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrWriteOutputs(IoConfigTaskMap *pTaskMap);
typedef RTS_RESULT (CDECL * PFIOMGRWRITEOUTPUTS) (IoConfigTaskMap *pTaskMap);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRWRITEOUTPUTS_NOTIMPLEMENTED)
	#define USE_IoMgrWriteOutputs
	#define EXT_IoMgrWriteOutputs
	#define GET_IoMgrWriteOutputs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrWriteOutputs(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrWriteOutputs  FALSE
	#define EXP_IoMgrWriteOutputs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrWriteOutputs
	#define EXT_IoMgrWriteOutputs
	#define GET_IoMgrWriteOutputs(fl)  CAL_CMGETAPI( "IoMgrWriteOutputs" ) 
	#define CAL_IoMgrWriteOutputs  IoMgrWriteOutputs
	#define CHK_IoMgrWriteOutputs  TRUE
	#define EXP_IoMgrWriteOutputs  CAL_CMEXPAPI( "IoMgrWriteOutputs" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrWriteOutputs
	#define EXT_IoMgrWriteOutputs
	#define GET_IoMgrWriteOutputs(fl)  CAL_CMGETAPI( "IoMgrWriteOutputs" ) 
	#define CAL_IoMgrWriteOutputs  IoMgrWriteOutputs
	#define CHK_IoMgrWriteOutputs  TRUE
	#define EXP_IoMgrWriteOutputs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrWriteOutputs", (RTS_UINTPTR)IoMgrWriteOutputs, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrWriteOutputs
	#define EXT_CmpIoMgrIoMgrWriteOutputs
	#define GET_CmpIoMgrIoMgrWriteOutputs  ERR_OK
	#define CAL_CmpIoMgrIoMgrWriteOutputs pICmpIoMgr->IIoMgrWriteOutputs
	#define CHK_CmpIoMgrIoMgrWriteOutputs (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrWriteOutputs  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrWriteOutputs
	#define EXT_IoMgrWriteOutputs
	#define GET_IoMgrWriteOutputs(fl)  CAL_CMGETAPI( "IoMgrWriteOutputs" ) 
	#define CAL_IoMgrWriteOutputs pICmpIoMgr->IIoMgrWriteOutputs
	#define CHK_IoMgrWriteOutputs (pICmpIoMgr != NULL)
	#define EXP_IoMgrWriteOutputs  CAL_CMEXPAPI( "IoMgrWriteOutputs" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrWriteOutputs  PFIOMGRWRITEOUTPUTS pfIoMgrWriteOutputs;
	#define EXT_IoMgrWriteOutputs  extern PFIOMGRWRITEOUTPUTS pfIoMgrWriteOutputs;
	#define GET_IoMgrWriteOutputs(fl)  s_pfCMGetAPI2( "IoMgrWriteOutputs", (RTS_VOID_FCTPTR *)&pfIoMgrWriteOutputs, (fl), 0, 0)
	#define CAL_IoMgrWriteOutputs  pfIoMgrWriteOutputs
	#define CHK_IoMgrWriteOutputs  (pfIoMgrWriteOutputs != NULL)
	#define EXP_IoMgrWriteOutputs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrWriteOutputs", (RTS_UINTPTR)IoMgrWriteOutputs, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrStartBusCycle(IoConfigConnector *pConnector);
typedef RTS_RESULT (CDECL * PFIOMGRSTARTBUSCYCLE) (IoConfigConnector *pConnector);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRSTARTBUSCYCLE_NOTIMPLEMENTED)
	#define USE_IoMgrStartBusCycle
	#define EXT_IoMgrStartBusCycle
	#define GET_IoMgrStartBusCycle(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrStartBusCycle(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrStartBusCycle  FALSE
	#define EXP_IoMgrStartBusCycle  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrStartBusCycle
	#define EXT_IoMgrStartBusCycle
	#define GET_IoMgrStartBusCycle(fl)  CAL_CMGETAPI( "IoMgrStartBusCycle" ) 
	#define CAL_IoMgrStartBusCycle  IoMgrStartBusCycle
	#define CHK_IoMgrStartBusCycle  TRUE
	#define EXP_IoMgrStartBusCycle  CAL_CMEXPAPI( "IoMgrStartBusCycle" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrStartBusCycle
	#define EXT_IoMgrStartBusCycle
	#define GET_IoMgrStartBusCycle(fl)  CAL_CMGETAPI( "IoMgrStartBusCycle" ) 
	#define CAL_IoMgrStartBusCycle  IoMgrStartBusCycle
	#define CHK_IoMgrStartBusCycle  TRUE
	#define EXP_IoMgrStartBusCycle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrStartBusCycle", (RTS_UINTPTR)IoMgrStartBusCycle, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrStartBusCycle
	#define EXT_CmpIoMgrIoMgrStartBusCycle
	#define GET_CmpIoMgrIoMgrStartBusCycle  ERR_OK
	#define CAL_CmpIoMgrIoMgrStartBusCycle pICmpIoMgr->IIoMgrStartBusCycle
	#define CHK_CmpIoMgrIoMgrStartBusCycle (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrStartBusCycle  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrStartBusCycle
	#define EXT_IoMgrStartBusCycle
	#define GET_IoMgrStartBusCycle(fl)  CAL_CMGETAPI( "IoMgrStartBusCycle" ) 
	#define CAL_IoMgrStartBusCycle pICmpIoMgr->IIoMgrStartBusCycle
	#define CHK_IoMgrStartBusCycle (pICmpIoMgr != NULL)
	#define EXP_IoMgrStartBusCycle  CAL_CMEXPAPI( "IoMgrStartBusCycle" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrStartBusCycle  PFIOMGRSTARTBUSCYCLE pfIoMgrStartBusCycle;
	#define EXT_IoMgrStartBusCycle  extern PFIOMGRSTARTBUSCYCLE pfIoMgrStartBusCycle;
	#define GET_IoMgrStartBusCycle(fl)  s_pfCMGetAPI2( "IoMgrStartBusCycle", (RTS_VOID_FCTPTR *)&pfIoMgrStartBusCycle, (fl), 0, 0)
	#define CAL_IoMgrStartBusCycle  pfIoMgrStartBusCycle
	#define CHK_IoMgrStartBusCycle  (pfIoMgrStartBusCycle != NULL)
	#define EXP_IoMgrStartBusCycle  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrStartBusCycle", (RTS_UINTPTR)IoMgrStartBusCycle, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrStartBusCycle2(IoConfigConnector *pConnector, RTS_UI32 dwType);
typedef RTS_RESULT (CDECL * PFIOMGRSTARTBUSCYCLE2) (IoConfigConnector *pConnector, RTS_UI32 dwType);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRSTARTBUSCYCLE2_NOTIMPLEMENTED)
	#define USE_IoMgrStartBusCycle2
	#define EXT_IoMgrStartBusCycle2
	#define GET_IoMgrStartBusCycle2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrStartBusCycle2(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrStartBusCycle2  FALSE
	#define EXP_IoMgrStartBusCycle2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrStartBusCycle2
	#define EXT_IoMgrStartBusCycle2
	#define GET_IoMgrStartBusCycle2(fl)  CAL_CMGETAPI( "IoMgrStartBusCycle2" ) 
	#define CAL_IoMgrStartBusCycle2  IoMgrStartBusCycle2
	#define CHK_IoMgrStartBusCycle2  TRUE
	#define EXP_IoMgrStartBusCycle2  CAL_CMEXPAPI( "IoMgrStartBusCycle2" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrStartBusCycle2
	#define EXT_IoMgrStartBusCycle2
	#define GET_IoMgrStartBusCycle2(fl)  CAL_CMGETAPI( "IoMgrStartBusCycle2" ) 
	#define CAL_IoMgrStartBusCycle2  IoMgrStartBusCycle2
	#define CHK_IoMgrStartBusCycle2  TRUE
	#define EXP_IoMgrStartBusCycle2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrStartBusCycle2", (RTS_UINTPTR)IoMgrStartBusCycle2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrStartBusCycle2
	#define EXT_CmpIoMgrIoMgrStartBusCycle2
	#define GET_CmpIoMgrIoMgrStartBusCycle2  ERR_OK
	#define CAL_CmpIoMgrIoMgrStartBusCycle2 pICmpIoMgr->IIoMgrStartBusCycle2
	#define CHK_CmpIoMgrIoMgrStartBusCycle2 (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrStartBusCycle2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrStartBusCycle2
	#define EXT_IoMgrStartBusCycle2
	#define GET_IoMgrStartBusCycle2(fl)  CAL_CMGETAPI( "IoMgrStartBusCycle2" ) 
	#define CAL_IoMgrStartBusCycle2 pICmpIoMgr->IIoMgrStartBusCycle2
	#define CHK_IoMgrStartBusCycle2 (pICmpIoMgr != NULL)
	#define EXP_IoMgrStartBusCycle2  CAL_CMEXPAPI( "IoMgrStartBusCycle2" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrStartBusCycle2  PFIOMGRSTARTBUSCYCLE2 pfIoMgrStartBusCycle2;
	#define EXT_IoMgrStartBusCycle2  extern PFIOMGRSTARTBUSCYCLE2 pfIoMgrStartBusCycle2;
	#define GET_IoMgrStartBusCycle2(fl)  s_pfCMGetAPI2( "IoMgrStartBusCycle2", (RTS_VOID_FCTPTR *)&pfIoMgrStartBusCycle2, (fl), 0, 0)
	#define CAL_IoMgrStartBusCycle2  pfIoMgrStartBusCycle2
	#define CHK_IoMgrStartBusCycle2  (pfIoMgrStartBusCycle2 != NULL)
	#define EXP_IoMgrStartBusCycle2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrStartBusCycle2", (RTS_UINTPTR)IoMgrStartBusCycle2, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrGetBusCycleType(IoConfigConnector *pConnector, RTS_RESULT *pResult);
typedef RTS_RESULT (CDECL * PFIOMGRGETBUSCYCLETYPE) (IoConfigConnector *pConnector, RTS_RESULT *pResult);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRGETBUSCYCLETYPE_NOTIMPLEMENTED)
	#define USE_IoMgrGetBusCycleType
	#define EXT_IoMgrGetBusCycleType
	#define GET_IoMgrGetBusCycleType(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrGetBusCycleType(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrGetBusCycleType  FALSE
	#define EXP_IoMgrGetBusCycleType  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrGetBusCycleType
	#define EXT_IoMgrGetBusCycleType
	#define GET_IoMgrGetBusCycleType(fl)  CAL_CMGETAPI( "IoMgrGetBusCycleType" ) 
	#define CAL_IoMgrGetBusCycleType  IoMgrGetBusCycleType
	#define CHK_IoMgrGetBusCycleType  TRUE
	#define EXP_IoMgrGetBusCycleType  CAL_CMEXPAPI( "IoMgrGetBusCycleType" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrGetBusCycleType
	#define EXT_IoMgrGetBusCycleType
	#define GET_IoMgrGetBusCycleType(fl)  CAL_CMGETAPI( "IoMgrGetBusCycleType" ) 
	#define CAL_IoMgrGetBusCycleType  IoMgrGetBusCycleType
	#define CHK_IoMgrGetBusCycleType  TRUE
	#define EXP_IoMgrGetBusCycleType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrGetBusCycleType", (RTS_UINTPTR)IoMgrGetBusCycleType, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrGetBusCycleType
	#define EXT_CmpIoMgrIoMgrGetBusCycleType
	#define GET_CmpIoMgrIoMgrGetBusCycleType  ERR_OK
	#define CAL_CmpIoMgrIoMgrGetBusCycleType pICmpIoMgr->IIoMgrGetBusCycleType
	#define CHK_CmpIoMgrIoMgrGetBusCycleType (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrGetBusCycleType  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrGetBusCycleType
	#define EXT_IoMgrGetBusCycleType
	#define GET_IoMgrGetBusCycleType(fl)  CAL_CMGETAPI( "IoMgrGetBusCycleType" ) 
	#define CAL_IoMgrGetBusCycleType pICmpIoMgr->IIoMgrGetBusCycleType
	#define CHK_IoMgrGetBusCycleType (pICmpIoMgr != NULL)
	#define EXP_IoMgrGetBusCycleType  CAL_CMEXPAPI( "IoMgrGetBusCycleType" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrGetBusCycleType  PFIOMGRGETBUSCYCLETYPE pfIoMgrGetBusCycleType;
	#define EXT_IoMgrGetBusCycleType  extern PFIOMGRGETBUSCYCLETYPE pfIoMgrGetBusCycleType;
	#define GET_IoMgrGetBusCycleType(fl)  s_pfCMGetAPI2( "IoMgrGetBusCycleType", (RTS_VOID_FCTPTR *)&pfIoMgrGetBusCycleType, (fl), 0, 0)
	#define CAL_IoMgrGetBusCycleType  pfIoMgrGetBusCycleType
	#define CHK_IoMgrGetBusCycleType  (pfIoMgrGetBusCycleType != NULL)
	#define EXP_IoMgrGetBusCycleType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrGetBusCycleType", (RTS_UINTPTR)IoMgrGetBusCycleType, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrScanModules(IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount);
typedef RTS_RESULT (CDECL * PFIOMGRSCANMODULES) (IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRSCANMODULES_NOTIMPLEMENTED)
	#define USE_IoMgrScanModules
	#define EXT_IoMgrScanModules
	#define GET_IoMgrScanModules(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrScanModules(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrScanModules  FALSE
	#define EXP_IoMgrScanModules  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrScanModules
	#define EXT_IoMgrScanModules
	#define GET_IoMgrScanModules(fl)  CAL_CMGETAPI( "IoMgrScanModules" ) 
	#define CAL_IoMgrScanModules  IoMgrScanModules
	#define CHK_IoMgrScanModules  TRUE
	#define EXP_IoMgrScanModules  CAL_CMEXPAPI( "IoMgrScanModules" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrScanModules
	#define EXT_IoMgrScanModules
	#define GET_IoMgrScanModules(fl)  CAL_CMGETAPI( "IoMgrScanModules" ) 
	#define CAL_IoMgrScanModules  IoMgrScanModules
	#define CHK_IoMgrScanModules  TRUE
	#define EXP_IoMgrScanModules  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrScanModules", (RTS_UINTPTR)IoMgrScanModules, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrScanModules
	#define EXT_CmpIoMgrIoMgrScanModules
	#define GET_CmpIoMgrIoMgrScanModules  ERR_OK
	#define CAL_CmpIoMgrIoMgrScanModules pICmpIoMgr->IIoMgrScanModules
	#define CHK_CmpIoMgrIoMgrScanModules (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrScanModules  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrScanModules
	#define EXT_IoMgrScanModules
	#define GET_IoMgrScanModules(fl)  CAL_CMGETAPI( "IoMgrScanModules" ) 
	#define CAL_IoMgrScanModules pICmpIoMgr->IIoMgrScanModules
	#define CHK_IoMgrScanModules (pICmpIoMgr != NULL)
	#define EXP_IoMgrScanModules  CAL_CMEXPAPI( "IoMgrScanModules" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrScanModules  PFIOMGRSCANMODULES pfIoMgrScanModules;
	#define EXT_IoMgrScanModules  extern PFIOMGRSCANMODULES pfIoMgrScanModules;
	#define GET_IoMgrScanModules(fl)  s_pfCMGetAPI2( "IoMgrScanModules", (RTS_VOID_FCTPTR *)&pfIoMgrScanModules, (fl), 0, 0)
	#define CAL_IoMgrScanModules  pfIoMgrScanModules
	#define CHK_IoMgrScanModules  (pfIoMgrScanModules != NULL)
	#define EXP_IoMgrScanModules  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrScanModules", (RTS_UINTPTR)IoMgrScanModules, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrGetModuleDiagnosis(IoConfigConnector *pConnector);
typedef RTS_RESULT (CDECL * PFIOMGRGETMODULEDIAGNOSIS) (IoConfigConnector *pConnector);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRGETMODULEDIAGNOSIS_NOTIMPLEMENTED)
	#define USE_IoMgrGetModuleDiagnosis
	#define EXT_IoMgrGetModuleDiagnosis
	#define GET_IoMgrGetModuleDiagnosis(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrGetModuleDiagnosis(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrGetModuleDiagnosis  FALSE
	#define EXP_IoMgrGetModuleDiagnosis  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrGetModuleDiagnosis
	#define EXT_IoMgrGetModuleDiagnosis
	#define GET_IoMgrGetModuleDiagnosis(fl)  CAL_CMGETAPI( "IoMgrGetModuleDiagnosis" ) 
	#define CAL_IoMgrGetModuleDiagnosis  IoMgrGetModuleDiagnosis
	#define CHK_IoMgrGetModuleDiagnosis  TRUE
	#define EXP_IoMgrGetModuleDiagnosis  CAL_CMEXPAPI( "IoMgrGetModuleDiagnosis" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrGetModuleDiagnosis
	#define EXT_IoMgrGetModuleDiagnosis
	#define GET_IoMgrGetModuleDiagnosis(fl)  CAL_CMGETAPI( "IoMgrGetModuleDiagnosis" ) 
	#define CAL_IoMgrGetModuleDiagnosis  IoMgrGetModuleDiagnosis
	#define CHK_IoMgrGetModuleDiagnosis  TRUE
	#define EXP_IoMgrGetModuleDiagnosis  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrGetModuleDiagnosis", (RTS_UINTPTR)IoMgrGetModuleDiagnosis, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrGetModuleDiagnosis
	#define EXT_CmpIoMgrIoMgrGetModuleDiagnosis
	#define GET_CmpIoMgrIoMgrGetModuleDiagnosis  ERR_OK
	#define CAL_CmpIoMgrIoMgrGetModuleDiagnosis pICmpIoMgr->IIoMgrGetModuleDiagnosis
	#define CHK_CmpIoMgrIoMgrGetModuleDiagnosis (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrGetModuleDiagnosis  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrGetModuleDiagnosis
	#define EXT_IoMgrGetModuleDiagnosis
	#define GET_IoMgrGetModuleDiagnosis(fl)  CAL_CMGETAPI( "IoMgrGetModuleDiagnosis" ) 
	#define CAL_IoMgrGetModuleDiagnosis pICmpIoMgr->IIoMgrGetModuleDiagnosis
	#define CHK_IoMgrGetModuleDiagnosis (pICmpIoMgr != NULL)
	#define EXP_IoMgrGetModuleDiagnosis  CAL_CMEXPAPI( "IoMgrGetModuleDiagnosis" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrGetModuleDiagnosis  PFIOMGRGETMODULEDIAGNOSIS pfIoMgrGetModuleDiagnosis;
	#define EXT_IoMgrGetModuleDiagnosis  extern PFIOMGRGETMODULEDIAGNOSIS pfIoMgrGetModuleDiagnosis;
	#define GET_IoMgrGetModuleDiagnosis(fl)  s_pfCMGetAPI2( "IoMgrGetModuleDiagnosis", (RTS_VOID_FCTPTR *)&pfIoMgrGetModuleDiagnosis, (fl), 0, 0)
	#define CAL_IoMgrGetModuleDiagnosis  pfIoMgrGetModuleDiagnosis
	#define CHK_IoMgrGetModuleDiagnosis  (pfIoMgrGetModuleDiagnosis != NULL)
	#define EXP_IoMgrGetModuleDiagnosis  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrGetModuleDiagnosis", (RTS_UINTPTR)IoMgrGetModuleDiagnosis, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrIdentify(IoConfigConnector *pConnector);
typedef RTS_RESULT (CDECL * PFIOMGRIDENTIFY) (IoConfigConnector *pConnector);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRIDENTIFY_NOTIMPLEMENTED)
	#define USE_IoMgrIdentify
	#define EXT_IoMgrIdentify
	#define GET_IoMgrIdentify(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrIdentify(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrIdentify  FALSE
	#define EXP_IoMgrIdentify  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrIdentify
	#define EXT_IoMgrIdentify
	#define GET_IoMgrIdentify(fl)  CAL_CMGETAPI( "IoMgrIdentify" ) 
	#define CAL_IoMgrIdentify  IoMgrIdentify
	#define CHK_IoMgrIdentify  TRUE
	#define EXP_IoMgrIdentify  CAL_CMEXPAPI( "IoMgrIdentify" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrIdentify
	#define EXT_IoMgrIdentify
	#define GET_IoMgrIdentify(fl)  CAL_CMGETAPI( "IoMgrIdentify" ) 
	#define CAL_IoMgrIdentify  IoMgrIdentify
	#define CHK_IoMgrIdentify  TRUE
	#define EXP_IoMgrIdentify  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrIdentify", (RTS_UINTPTR)IoMgrIdentify, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrIdentify
	#define EXT_CmpIoMgrIoMgrIdentify
	#define GET_CmpIoMgrIoMgrIdentify  ERR_OK
	#define CAL_CmpIoMgrIoMgrIdentify pICmpIoMgr->IIoMgrIdentify
	#define CHK_CmpIoMgrIoMgrIdentify (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrIdentify  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrIdentify
	#define EXT_IoMgrIdentify
	#define GET_IoMgrIdentify(fl)  CAL_CMGETAPI( "IoMgrIdentify" ) 
	#define CAL_IoMgrIdentify pICmpIoMgr->IIoMgrIdentify
	#define CHK_IoMgrIdentify (pICmpIoMgr != NULL)
	#define EXP_IoMgrIdentify  CAL_CMEXPAPI( "IoMgrIdentify" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrIdentify  PFIOMGRIDENTIFY pfIoMgrIdentify;
	#define EXT_IoMgrIdentify  extern PFIOMGRIDENTIFY pfIoMgrIdentify;
	#define GET_IoMgrIdentify(fl)  s_pfCMGetAPI2( "IoMgrIdentify", (RTS_VOID_FCTPTR *)&pfIoMgrIdentify, (fl), 0, 0)
	#define CAL_IoMgrIdentify  pfIoMgrIdentify
	#define CHK_IoMgrIdentify  (pfIoMgrIdentify != NULL)
	#define EXP_IoMgrIdentify  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrIdentify", (RTS_UINTPTR)IoMgrIdentify, 0, 0) 
#endif




/**
 * <description>Interface to nominate a device specified by connector. Nomination can be used for example
 *	for ProfiNET devices to configure their IP-addresses.</description>
 * <param name="pConnector" type="IN">Pointer to connector</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL IoMgrNominate(IoConfigConnector *pConnector);
typedef RTS_RESULT (CDECL * PFIOMGRNOMINATE) (IoConfigConnector *pConnector);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRNOMINATE_NOTIMPLEMENTED)
	#define USE_IoMgrNominate
	#define EXT_IoMgrNominate
	#define GET_IoMgrNominate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrNominate(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrNominate  FALSE
	#define EXP_IoMgrNominate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrNominate
	#define EXT_IoMgrNominate
	#define GET_IoMgrNominate(fl)  CAL_CMGETAPI( "IoMgrNominate" ) 
	#define CAL_IoMgrNominate  IoMgrNominate
	#define CHK_IoMgrNominate  TRUE
	#define EXP_IoMgrNominate  CAL_CMEXPAPI( "IoMgrNominate" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrNominate
	#define EXT_IoMgrNominate
	#define GET_IoMgrNominate(fl)  CAL_CMGETAPI( "IoMgrNominate" ) 
	#define CAL_IoMgrNominate  IoMgrNominate
	#define CHK_IoMgrNominate  TRUE
	#define EXP_IoMgrNominate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrNominate", (RTS_UINTPTR)IoMgrNominate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrNominate
	#define EXT_CmpIoMgrIoMgrNominate
	#define GET_CmpIoMgrIoMgrNominate  ERR_OK
	#define CAL_CmpIoMgrIoMgrNominate pICmpIoMgr->IIoMgrNominate
	#define CHK_CmpIoMgrIoMgrNominate (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrNominate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrNominate
	#define EXT_IoMgrNominate
	#define GET_IoMgrNominate(fl)  CAL_CMGETAPI( "IoMgrNominate" ) 
	#define CAL_IoMgrNominate pICmpIoMgr->IIoMgrNominate
	#define CHK_IoMgrNominate (pICmpIoMgr != NULL)
	#define EXP_IoMgrNominate  CAL_CMEXPAPI( "IoMgrNominate" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrNominate  PFIOMGRNOMINATE pfIoMgrNominate;
	#define EXT_IoMgrNominate  extern PFIOMGRNOMINATE pfIoMgrNominate;
	#define GET_IoMgrNominate(fl)  s_pfCMGetAPI2( "IoMgrNominate", (RTS_VOID_FCTPTR *)&pfIoMgrNominate, (fl), 0, 0)
	#define CAL_IoMgrNominate  pfIoMgrNominate
	#define CHK_IoMgrNominate  (pfIoMgrNominate != NULL)
	#define EXP_IoMgrNominate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrNominate", (RTS_UINTPTR)IoMgrNominate, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrWatchdogTrigger(IoConfigConnector *pConnector);
typedef RTS_RESULT (CDECL * PFIOMGRWATCHDOGTRIGGER) (IoConfigConnector *pConnector);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRWATCHDOGTRIGGER_NOTIMPLEMENTED)
	#define USE_IoMgrWatchdogTrigger
	#define EXT_IoMgrWatchdogTrigger
	#define GET_IoMgrWatchdogTrigger(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrWatchdogTrigger(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrWatchdogTrigger  FALSE
	#define EXP_IoMgrWatchdogTrigger  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrWatchdogTrigger
	#define EXT_IoMgrWatchdogTrigger
	#define GET_IoMgrWatchdogTrigger(fl)  CAL_CMGETAPI( "IoMgrWatchdogTrigger" ) 
	#define CAL_IoMgrWatchdogTrigger  IoMgrWatchdogTrigger
	#define CHK_IoMgrWatchdogTrigger  TRUE
	#define EXP_IoMgrWatchdogTrigger  CAL_CMEXPAPI( "IoMgrWatchdogTrigger" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrWatchdogTrigger
	#define EXT_IoMgrWatchdogTrigger
	#define GET_IoMgrWatchdogTrigger(fl)  CAL_CMGETAPI( "IoMgrWatchdogTrigger" ) 
	#define CAL_IoMgrWatchdogTrigger  IoMgrWatchdogTrigger
	#define CHK_IoMgrWatchdogTrigger  TRUE
	#define EXP_IoMgrWatchdogTrigger  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrWatchdogTrigger", (RTS_UINTPTR)IoMgrWatchdogTrigger, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrWatchdogTrigger
	#define EXT_CmpIoMgrIoMgrWatchdogTrigger
	#define GET_CmpIoMgrIoMgrWatchdogTrigger  ERR_OK
	#define CAL_CmpIoMgrIoMgrWatchdogTrigger pICmpIoMgr->IIoMgrWatchdogTrigger
	#define CHK_CmpIoMgrIoMgrWatchdogTrigger (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrWatchdogTrigger  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrWatchdogTrigger
	#define EXT_IoMgrWatchdogTrigger
	#define GET_IoMgrWatchdogTrigger(fl)  CAL_CMGETAPI( "IoMgrWatchdogTrigger" ) 
	#define CAL_IoMgrWatchdogTrigger pICmpIoMgr->IIoMgrWatchdogTrigger
	#define CHK_IoMgrWatchdogTrigger (pICmpIoMgr != NULL)
	#define EXP_IoMgrWatchdogTrigger  CAL_CMEXPAPI( "IoMgrWatchdogTrigger" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrWatchdogTrigger  PFIOMGRWATCHDOGTRIGGER pfIoMgrWatchdogTrigger;
	#define EXT_IoMgrWatchdogTrigger  extern PFIOMGRWATCHDOGTRIGGER pfIoMgrWatchdogTrigger;
	#define GET_IoMgrWatchdogTrigger(fl)  s_pfCMGetAPI2( "IoMgrWatchdogTrigger", (RTS_VOID_FCTPTR *)&pfIoMgrWatchdogTrigger, (fl), 0, 0)
	#define CAL_IoMgrWatchdogTrigger  pfIoMgrWatchdogTrigger
	#define CHK_IoMgrWatchdogTrigger  (pfIoMgrWatchdogTrigger != NULL)
	#define EXP_IoMgrWatchdogTrigger  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrWatchdogTrigger", (RTS_UINTPTR)IoMgrWatchdogTrigger, 0, 0) 
#endif




/**
 * <description>
 * <p>Interface to get a parameter on a specified connector specified by ID</p>
 * </description>
 * <param name="pConnector" type="IN" range="[NULL,VALID_CONNECTOR,INVALID_CONNECTOR]">Pointer to connector</param>
 * <param name="dwParameterId" type="IN" range="[VALID_PARAMETERID,INVALID_PARAMETERID]">ID of the parameter. Is defined in the device description.</param>
 * <parampseudo name="bException" type="OUT">Exception occured for Invalid Connector</parampseudo>
 * <result>Parameter or NULL if failed</result>
 */
IoConfigParameter* CDECL IoMgrConfigGetParameter(IoConfigConnector *pConnector, RTS_UI32 dwParameterId);
typedef IoConfigParameter* (CDECL * PFIOMGRCONFIGGETPARAMETER) (IoConfigConnector *pConnector, RTS_UI32 dwParameterId);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETPARAMETER_NOTIMPLEMENTED)
	#define USE_IoMgrConfigGetParameter
	#define EXT_IoMgrConfigGetParameter
	#define GET_IoMgrConfigGetParameter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrConfigGetParameter(p0,p1)  (IoConfigParameter*)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrConfigGetParameter  FALSE
	#define EXP_IoMgrConfigGetParameter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrConfigGetParameter
	#define EXT_IoMgrConfigGetParameter
	#define GET_IoMgrConfigGetParameter(fl)  CAL_CMGETAPI( "IoMgrConfigGetParameter" ) 
	#define CAL_IoMgrConfigGetParameter  IoMgrConfigGetParameter
	#define CHK_IoMgrConfigGetParameter  TRUE
	#define EXP_IoMgrConfigGetParameter  CAL_CMEXPAPI( "IoMgrConfigGetParameter" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrConfigGetParameter
	#define EXT_IoMgrConfigGetParameter
	#define GET_IoMgrConfigGetParameter(fl)  CAL_CMGETAPI( "IoMgrConfigGetParameter" ) 
	#define CAL_IoMgrConfigGetParameter  IoMgrConfigGetParameter
	#define CHK_IoMgrConfigGetParameter  TRUE
	#define EXP_IoMgrConfigGetParameter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetParameter", (RTS_UINTPTR)IoMgrConfigGetParameter, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrConfigGetParameter
	#define EXT_CmpIoMgrIoMgrConfigGetParameter
	#define GET_CmpIoMgrIoMgrConfigGetParameter  ERR_OK
	#define CAL_CmpIoMgrIoMgrConfigGetParameter pICmpIoMgr->IIoMgrConfigGetParameter
	#define CHK_CmpIoMgrIoMgrConfigGetParameter (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrConfigGetParameter  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrConfigGetParameter
	#define EXT_IoMgrConfigGetParameter
	#define GET_IoMgrConfigGetParameter(fl)  CAL_CMGETAPI( "IoMgrConfigGetParameter" ) 
	#define CAL_IoMgrConfigGetParameter pICmpIoMgr->IIoMgrConfigGetParameter
	#define CHK_IoMgrConfigGetParameter (pICmpIoMgr != NULL)
	#define EXP_IoMgrConfigGetParameter  CAL_CMEXPAPI( "IoMgrConfigGetParameter" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrConfigGetParameter  PFIOMGRCONFIGGETPARAMETER pfIoMgrConfigGetParameter;
	#define EXT_IoMgrConfigGetParameter  extern PFIOMGRCONFIGGETPARAMETER pfIoMgrConfigGetParameter;
	#define GET_IoMgrConfigGetParameter(fl)  s_pfCMGetAPI2( "IoMgrConfigGetParameter", (RTS_VOID_FCTPTR *)&pfIoMgrConfigGetParameter, (fl), 0, 0)
	#define CAL_IoMgrConfigGetParameter  pfIoMgrConfigGetParameter
	#define CHK_IoMgrConfigGetParameter  (pfIoMgrConfigGetParameter != NULL)
	#define EXP_IoMgrConfigGetParameter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetParameter", (RTS_UINTPTR)IoMgrConfigGetParameter, 0, 0) 
#endif




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
RTS_UI32 CDECL IoMgrConfigGetParameterValueDword(IoConfigParameter *pParameter, RTS_RESULT *pResult);
typedef RTS_UI32 (CDECL * PFIOMGRCONFIGGETPARAMETERVALUEDWORD) (IoConfigParameter *pParameter, RTS_RESULT *pResult);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETPARAMETERVALUEDWORD_NOTIMPLEMENTED)
	#define USE_IoMgrConfigGetParameterValueDword
	#define EXT_IoMgrConfigGetParameterValueDword
	#define GET_IoMgrConfigGetParameterValueDword(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrConfigGetParameterValueDword(p0,p1)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrConfigGetParameterValueDword  FALSE
	#define EXP_IoMgrConfigGetParameterValueDword  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrConfigGetParameterValueDword
	#define EXT_IoMgrConfigGetParameterValueDword
	#define GET_IoMgrConfigGetParameterValueDword(fl)  CAL_CMGETAPI( "IoMgrConfigGetParameterValueDword" ) 
	#define CAL_IoMgrConfigGetParameterValueDword  IoMgrConfigGetParameterValueDword
	#define CHK_IoMgrConfigGetParameterValueDword  TRUE
	#define EXP_IoMgrConfigGetParameterValueDword  CAL_CMEXPAPI( "IoMgrConfigGetParameterValueDword" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrConfigGetParameterValueDword
	#define EXT_IoMgrConfigGetParameterValueDword
	#define GET_IoMgrConfigGetParameterValueDword(fl)  CAL_CMGETAPI( "IoMgrConfigGetParameterValueDword" ) 
	#define CAL_IoMgrConfigGetParameterValueDword  IoMgrConfigGetParameterValueDword
	#define CHK_IoMgrConfigGetParameterValueDword  TRUE
	#define EXP_IoMgrConfigGetParameterValueDword  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetParameterValueDword", (RTS_UINTPTR)IoMgrConfigGetParameterValueDword, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrConfigGetParameterValueDword
	#define EXT_CmpIoMgrIoMgrConfigGetParameterValueDword
	#define GET_CmpIoMgrIoMgrConfigGetParameterValueDword  ERR_OK
	#define CAL_CmpIoMgrIoMgrConfigGetParameterValueDword pICmpIoMgr->IIoMgrConfigGetParameterValueDword
	#define CHK_CmpIoMgrIoMgrConfigGetParameterValueDword (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrConfigGetParameterValueDword  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrConfigGetParameterValueDword
	#define EXT_IoMgrConfigGetParameterValueDword
	#define GET_IoMgrConfigGetParameterValueDword(fl)  CAL_CMGETAPI( "IoMgrConfigGetParameterValueDword" ) 
	#define CAL_IoMgrConfigGetParameterValueDword pICmpIoMgr->IIoMgrConfigGetParameterValueDword
	#define CHK_IoMgrConfigGetParameterValueDword (pICmpIoMgr != NULL)
	#define EXP_IoMgrConfigGetParameterValueDword  CAL_CMEXPAPI( "IoMgrConfigGetParameterValueDword" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrConfigGetParameterValueDword  PFIOMGRCONFIGGETPARAMETERVALUEDWORD pfIoMgrConfigGetParameterValueDword;
	#define EXT_IoMgrConfigGetParameterValueDword  extern PFIOMGRCONFIGGETPARAMETERVALUEDWORD pfIoMgrConfigGetParameterValueDword;
	#define GET_IoMgrConfigGetParameterValueDword(fl)  s_pfCMGetAPI2( "IoMgrConfigGetParameterValueDword", (RTS_VOID_FCTPTR *)&pfIoMgrConfigGetParameterValueDword, (fl), 0, 0)
	#define CAL_IoMgrConfigGetParameterValueDword  pfIoMgrConfigGetParameterValueDword
	#define CHK_IoMgrConfigGetParameterValueDword  (pfIoMgrConfigGetParameterValueDword != NULL)
	#define EXP_IoMgrConfigGetParameterValueDword  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetParameterValueDword", (RTS_UINTPTR)IoMgrConfigGetParameterValueDword, 0, 0) 
#endif




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
unsigned short CDECL IoMgrConfigGetParameterValueWord(IoConfigParameter *pParameter, RTS_RESULT *pResult);
typedef unsigned short (CDECL * PFIOMGRCONFIGGETPARAMETERVALUEWORD) (IoConfigParameter *pParameter, RTS_RESULT *pResult);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETPARAMETERVALUEWORD_NOTIMPLEMENTED)
	#define USE_IoMgrConfigGetParameterValueWord
	#define EXT_IoMgrConfigGetParameterValueWord
	#define GET_IoMgrConfigGetParameterValueWord(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrConfigGetParameterValueWord(p0,p1)  (unsigned short)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrConfigGetParameterValueWord  FALSE
	#define EXP_IoMgrConfigGetParameterValueWord  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrConfigGetParameterValueWord
	#define EXT_IoMgrConfigGetParameterValueWord
	#define GET_IoMgrConfigGetParameterValueWord(fl)  CAL_CMGETAPI( "IoMgrConfigGetParameterValueWord" ) 
	#define CAL_IoMgrConfigGetParameterValueWord  IoMgrConfigGetParameterValueWord
	#define CHK_IoMgrConfigGetParameterValueWord  TRUE
	#define EXP_IoMgrConfigGetParameterValueWord  CAL_CMEXPAPI( "IoMgrConfigGetParameterValueWord" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrConfigGetParameterValueWord
	#define EXT_IoMgrConfigGetParameterValueWord
	#define GET_IoMgrConfigGetParameterValueWord(fl)  CAL_CMGETAPI( "IoMgrConfigGetParameterValueWord" ) 
	#define CAL_IoMgrConfigGetParameterValueWord  IoMgrConfigGetParameterValueWord
	#define CHK_IoMgrConfigGetParameterValueWord  TRUE
	#define EXP_IoMgrConfigGetParameterValueWord  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetParameterValueWord", (RTS_UINTPTR)IoMgrConfigGetParameterValueWord, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrConfigGetParameterValueWord
	#define EXT_CmpIoMgrIoMgrConfigGetParameterValueWord
	#define GET_CmpIoMgrIoMgrConfigGetParameterValueWord  ERR_OK
	#define CAL_CmpIoMgrIoMgrConfigGetParameterValueWord pICmpIoMgr->IIoMgrConfigGetParameterValueWord
	#define CHK_CmpIoMgrIoMgrConfigGetParameterValueWord (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrConfigGetParameterValueWord  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrConfigGetParameterValueWord
	#define EXT_IoMgrConfigGetParameterValueWord
	#define GET_IoMgrConfigGetParameterValueWord(fl)  CAL_CMGETAPI( "IoMgrConfigGetParameterValueWord" ) 
	#define CAL_IoMgrConfigGetParameterValueWord pICmpIoMgr->IIoMgrConfigGetParameterValueWord
	#define CHK_IoMgrConfigGetParameterValueWord (pICmpIoMgr != NULL)
	#define EXP_IoMgrConfigGetParameterValueWord  CAL_CMEXPAPI( "IoMgrConfigGetParameterValueWord" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrConfigGetParameterValueWord  PFIOMGRCONFIGGETPARAMETERVALUEWORD pfIoMgrConfigGetParameterValueWord;
	#define EXT_IoMgrConfigGetParameterValueWord  extern PFIOMGRCONFIGGETPARAMETERVALUEWORD pfIoMgrConfigGetParameterValueWord;
	#define GET_IoMgrConfigGetParameterValueWord(fl)  s_pfCMGetAPI2( "IoMgrConfigGetParameterValueWord", (RTS_VOID_FCTPTR *)&pfIoMgrConfigGetParameterValueWord, (fl), 0, 0)
	#define CAL_IoMgrConfigGetParameterValueWord  pfIoMgrConfigGetParameterValueWord
	#define CHK_IoMgrConfigGetParameterValueWord  (pfIoMgrConfigGetParameterValueWord != NULL)
	#define EXP_IoMgrConfigGetParameterValueWord  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetParameterValueWord", (RTS_UINTPTR)IoMgrConfigGetParameterValueWord, 0, 0) 
#endif




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
unsigned char CDECL IoMgrConfigGetParameterValueByte(IoConfigParameter *pParameter, RTS_RESULT *pResult);
typedef unsigned char (CDECL * PFIOMGRCONFIGGETPARAMETERVALUEBYTE) (IoConfigParameter *pParameter, RTS_RESULT *pResult);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETPARAMETERVALUEBYTE_NOTIMPLEMENTED)
	#define USE_IoMgrConfigGetParameterValueByte
	#define EXT_IoMgrConfigGetParameterValueByte
	#define GET_IoMgrConfigGetParameterValueByte(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrConfigGetParameterValueByte(p0,p1)  (unsigned char)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrConfigGetParameterValueByte  FALSE
	#define EXP_IoMgrConfigGetParameterValueByte  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrConfigGetParameterValueByte
	#define EXT_IoMgrConfigGetParameterValueByte
	#define GET_IoMgrConfigGetParameterValueByte(fl)  CAL_CMGETAPI( "IoMgrConfigGetParameterValueByte" ) 
	#define CAL_IoMgrConfigGetParameterValueByte  IoMgrConfigGetParameterValueByte
	#define CHK_IoMgrConfigGetParameterValueByte  TRUE
	#define EXP_IoMgrConfigGetParameterValueByte  CAL_CMEXPAPI( "IoMgrConfigGetParameterValueByte" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrConfigGetParameterValueByte
	#define EXT_IoMgrConfigGetParameterValueByte
	#define GET_IoMgrConfigGetParameterValueByte(fl)  CAL_CMGETAPI( "IoMgrConfigGetParameterValueByte" ) 
	#define CAL_IoMgrConfigGetParameterValueByte  IoMgrConfigGetParameterValueByte
	#define CHK_IoMgrConfigGetParameterValueByte  TRUE
	#define EXP_IoMgrConfigGetParameterValueByte  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetParameterValueByte", (RTS_UINTPTR)IoMgrConfigGetParameterValueByte, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrConfigGetParameterValueByte
	#define EXT_CmpIoMgrIoMgrConfigGetParameterValueByte
	#define GET_CmpIoMgrIoMgrConfigGetParameterValueByte  ERR_OK
	#define CAL_CmpIoMgrIoMgrConfigGetParameterValueByte pICmpIoMgr->IIoMgrConfigGetParameterValueByte
	#define CHK_CmpIoMgrIoMgrConfigGetParameterValueByte (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrConfigGetParameterValueByte  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrConfigGetParameterValueByte
	#define EXT_IoMgrConfigGetParameterValueByte
	#define GET_IoMgrConfigGetParameterValueByte(fl)  CAL_CMGETAPI( "IoMgrConfigGetParameterValueByte" ) 
	#define CAL_IoMgrConfigGetParameterValueByte pICmpIoMgr->IIoMgrConfigGetParameterValueByte
	#define CHK_IoMgrConfigGetParameterValueByte (pICmpIoMgr != NULL)
	#define EXP_IoMgrConfigGetParameterValueByte  CAL_CMEXPAPI( "IoMgrConfigGetParameterValueByte" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrConfigGetParameterValueByte  PFIOMGRCONFIGGETPARAMETERVALUEBYTE pfIoMgrConfigGetParameterValueByte;
	#define EXT_IoMgrConfigGetParameterValueByte  extern PFIOMGRCONFIGGETPARAMETERVALUEBYTE pfIoMgrConfigGetParameterValueByte;
	#define GET_IoMgrConfigGetParameterValueByte(fl)  s_pfCMGetAPI2( "IoMgrConfigGetParameterValueByte", (RTS_VOID_FCTPTR *)&pfIoMgrConfigGetParameterValueByte, (fl), 0, 0)
	#define CAL_IoMgrConfigGetParameterValueByte  pfIoMgrConfigGetParameterValueByte
	#define CHK_IoMgrConfigGetParameterValueByte  (pfIoMgrConfigGetParameterValueByte != NULL)
	#define EXP_IoMgrConfigGetParameterValueByte  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetParameterValueByte", (RTS_UINTPTR)IoMgrConfigGetParameterValueByte, 0, 0) 
#endif




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
void * CDECL IoMgrConfigGetParameterValuePointer(IoConfigParameter *pParameter, RTS_RESULT *pResult);
typedef void * (CDECL * PFIOMGRCONFIGGETPARAMETERVALUEPOINTER) (IoConfigParameter *pParameter, RTS_RESULT *pResult);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETPARAMETERVALUEPOINTER_NOTIMPLEMENTED)
	#define USE_IoMgrConfigGetParameterValuePointer
	#define EXT_IoMgrConfigGetParameterValuePointer
	#define GET_IoMgrConfigGetParameterValuePointer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrConfigGetParameterValuePointer(p0,p1)  (void *)(RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrConfigGetParameterValuePointer  FALSE
	#define EXP_IoMgrConfigGetParameterValuePointer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrConfigGetParameterValuePointer
	#define EXT_IoMgrConfigGetParameterValuePointer
	#define GET_IoMgrConfigGetParameterValuePointer(fl)  CAL_CMGETAPI( "IoMgrConfigGetParameterValuePointer" ) 
	#define CAL_IoMgrConfigGetParameterValuePointer  IoMgrConfigGetParameterValuePointer
	#define CHK_IoMgrConfigGetParameterValuePointer  TRUE
	#define EXP_IoMgrConfigGetParameterValuePointer  CAL_CMEXPAPI( "IoMgrConfigGetParameterValuePointer" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrConfigGetParameterValuePointer
	#define EXT_IoMgrConfigGetParameterValuePointer
	#define GET_IoMgrConfigGetParameterValuePointer(fl)  CAL_CMGETAPI( "IoMgrConfigGetParameterValuePointer" ) 
	#define CAL_IoMgrConfigGetParameterValuePointer  IoMgrConfigGetParameterValuePointer
	#define CHK_IoMgrConfigGetParameterValuePointer  TRUE
	#define EXP_IoMgrConfigGetParameterValuePointer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetParameterValuePointer", (RTS_UINTPTR)IoMgrConfigGetParameterValuePointer, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrConfigGetParameterValuePointer
	#define EXT_CmpIoMgrIoMgrConfigGetParameterValuePointer
	#define GET_CmpIoMgrIoMgrConfigGetParameterValuePointer  ERR_OK
	#define CAL_CmpIoMgrIoMgrConfigGetParameterValuePointer pICmpIoMgr->IIoMgrConfigGetParameterValuePointer
	#define CHK_CmpIoMgrIoMgrConfigGetParameterValuePointer (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrConfigGetParameterValuePointer  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrConfigGetParameterValuePointer
	#define EXT_IoMgrConfigGetParameterValuePointer
	#define GET_IoMgrConfigGetParameterValuePointer(fl)  CAL_CMGETAPI( "IoMgrConfigGetParameterValuePointer" ) 
	#define CAL_IoMgrConfigGetParameterValuePointer pICmpIoMgr->IIoMgrConfigGetParameterValuePointer
	#define CHK_IoMgrConfigGetParameterValuePointer (pICmpIoMgr != NULL)
	#define EXP_IoMgrConfigGetParameterValuePointer  CAL_CMEXPAPI( "IoMgrConfigGetParameterValuePointer" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrConfigGetParameterValuePointer  PFIOMGRCONFIGGETPARAMETERVALUEPOINTER pfIoMgrConfigGetParameterValuePointer;
	#define EXT_IoMgrConfigGetParameterValuePointer  extern PFIOMGRCONFIGGETPARAMETERVALUEPOINTER pfIoMgrConfigGetParameterValuePointer;
	#define GET_IoMgrConfigGetParameterValuePointer(fl)  s_pfCMGetAPI2( "IoMgrConfigGetParameterValuePointer", (RTS_VOID_FCTPTR *)&pfIoMgrConfigGetParameterValuePointer, (fl), 0, 0)
	#define CAL_IoMgrConfigGetParameterValuePointer  pfIoMgrConfigGetParameterValuePointer
	#define CHK_IoMgrConfigGetParameterValuePointer  (pfIoMgrConfigGetParameterValuePointer != NULL)
	#define EXP_IoMgrConfigGetParameterValuePointer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetParameterValuePointer", (RTS_UINTPTR)IoMgrConfigGetParameterValuePointer, 0, 0) 
#endif




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
IoConfigConnector* CDECL IoMgrConfigGetFirstConnector(IoConfigConnector *pConnectorList, int *pnCount, unsigned short wType);
typedef IoConfigConnector* (CDECL * PFIOMGRCONFIGGETFIRSTCONNECTOR) (IoConfigConnector *pConnectorList, int *pnCount, unsigned short wType);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETFIRSTCONNECTOR_NOTIMPLEMENTED)
	#define USE_IoMgrConfigGetFirstConnector
	#define EXT_IoMgrConfigGetFirstConnector
	#define GET_IoMgrConfigGetFirstConnector(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrConfigGetFirstConnector(p0,p1,p2)  (IoConfigConnector*)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrConfigGetFirstConnector  FALSE
	#define EXP_IoMgrConfigGetFirstConnector  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrConfigGetFirstConnector
	#define EXT_IoMgrConfigGetFirstConnector
	#define GET_IoMgrConfigGetFirstConnector(fl)  CAL_CMGETAPI( "IoMgrConfigGetFirstConnector" ) 
	#define CAL_IoMgrConfigGetFirstConnector  IoMgrConfigGetFirstConnector
	#define CHK_IoMgrConfigGetFirstConnector  TRUE
	#define EXP_IoMgrConfigGetFirstConnector  CAL_CMEXPAPI( "IoMgrConfigGetFirstConnector" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrConfigGetFirstConnector
	#define EXT_IoMgrConfigGetFirstConnector
	#define GET_IoMgrConfigGetFirstConnector(fl)  CAL_CMGETAPI( "IoMgrConfigGetFirstConnector" ) 
	#define CAL_IoMgrConfigGetFirstConnector  IoMgrConfigGetFirstConnector
	#define CHK_IoMgrConfigGetFirstConnector  TRUE
	#define EXP_IoMgrConfigGetFirstConnector  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetFirstConnector", (RTS_UINTPTR)IoMgrConfigGetFirstConnector, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrConfigGetFirstConnector
	#define EXT_CmpIoMgrIoMgrConfigGetFirstConnector
	#define GET_CmpIoMgrIoMgrConfigGetFirstConnector  ERR_OK
	#define CAL_CmpIoMgrIoMgrConfigGetFirstConnector pICmpIoMgr->IIoMgrConfigGetFirstConnector
	#define CHK_CmpIoMgrIoMgrConfigGetFirstConnector (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrConfigGetFirstConnector  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrConfigGetFirstConnector
	#define EXT_IoMgrConfigGetFirstConnector
	#define GET_IoMgrConfigGetFirstConnector(fl)  CAL_CMGETAPI( "IoMgrConfigGetFirstConnector" ) 
	#define CAL_IoMgrConfigGetFirstConnector pICmpIoMgr->IIoMgrConfigGetFirstConnector
	#define CHK_IoMgrConfigGetFirstConnector (pICmpIoMgr != NULL)
	#define EXP_IoMgrConfigGetFirstConnector  CAL_CMEXPAPI( "IoMgrConfigGetFirstConnector" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrConfigGetFirstConnector  PFIOMGRCONFIGGETFIRSTCONNECTOR pfIoMgrConfigGetFirstConnector;
	#define EXT_IoMgrConfigGetFirstConnector  extern PFIOMGRCONFIGGETFIRSTCONNECTOR pfIoMgrConfigGetFirstConnector;
	#define GET_IoMgrConfigGetFirstConnector(fl)  s_pfCMGetAPI2( "IoMgrConfigGetFirstConnector", (RTS_VOID_FCTPTR *)&pfIoMgrConfigGetFirstConnector, (fl), 0, 0)
	#define CAL_IoMgrConfigGetFirstConnector  pfIoMgrConfigGetFirstConnector
	#define CHK_IoMgrConfigGetFirstConnector  (pfIoMgrConfigGetFirstConnector != NULL)
	#define EXP_IoMgrConfigGetFirstConnector  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetFirstConnector", (RTS_UINTPTR)IoMgrConfigGetFirstConnector, 0, 0) 
#endif




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
IoConfigConnector* CDECL IoMgrConfigGetNextConnector(IoConfigConnector *pConnectorList, int *pnCount, unsigned short wType);
typedef IoConfigConnector* (CDECL * PFIOMGRCONFIGGETNEXTCONNECTOR) (IoConfigConnector *pConnectorList, int *pnCount, unsigned short wType);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETNEXTCONNECTOR_NOTIMPLEMENTED)
	#define USE_IoMgrConfigGetNextConnector
	#define EXT_IoMgrConfigGetNextConnector
	#define GET_IoMgrConfigGetNextConnector(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrConfigGetNextConnector(p0,p1,p2)  (IoConfigConnector*)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrConfigGetNextConnector  FALSE
	#define EXP_IoMgrConfigGetNextConnector  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrConfigGetNextConnector
	#define EXT_IoMgrConfigGetNextConnector
	#define GET_IoMgrConfigGetNextConnector(fl)  CAL_CMGETAPI( "IoMgrConfigGetNextConnector" ) 
	#define CAL_IoMgrConfigGetNextConnector  IoMgrConfigGetNextConnector
	#define CHK_IoMgrConfigGetNextConnector  TRUE
	#define EXP_IoMgrConfigGetNextConnector  CAL_CMEXPAPI( "IoMgrConfigGetNextConnector" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrConfigGetNextConnector
	#define EXT_IoMgrConfigGetNextConnector
	#define GET_IoMgrConfigGetNextConnector(fl)  CAL_CMGETAPI( "IoMgrConfigGetNextConnector" ) 
	#define CAL_IoMgrConfigGetNextConnector  IoMgrConfigGetNextConnector
	#define CHK_IoMgrConfigGetNextConnector  TRUE
	#define EXP_IoMgrConfigGetNextConnector  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetNextConnector", (RTS_UINTPTR)IoMgrConfigGetNextConnector, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrConfigGetNextConnector
	#define EXT_CmpIoMgrIoMgrConfigGetNextConnector
	#define GET_CmpIoMgrIoMgrConfigGetNextConnector  ERR_OK
	#define CAL_CmpIoMgrIoMgrConfigGetNextConnector pICmpIoMgr->IIoMgrConfigGetNextConnector
	#define CHK_CmpIoMgrIoMgrConfigGetNextConnector (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrConfigGetNextConnector  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrConfigGetNextConnector
	#define EXT_IoMgrConfigGetNextConnector
	#define GET_IoMgrConfigGetNextConnector(fl)  CAL_CMGETAPI( "IoMgrConfigGetNextConnector" ) 
	#define CAL_IoMgrConfigGetNextConnector pICmpIoMgr->IIoMgrConfigGetNextConnector
	#define CHK_IoMgrConfigGetNextConnector (pICmpIoMgr != NULL)
	#define EXP_IoMgrConfigGetNextConnector  CAL_CMEXPAPI( "IoMgrConfigGetNextConnector" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrConfigGetNextConnector  PFIOMGRCONFIGGETNEXTCONNECTOR pfIoMgrConfigGetNextConnector;
	#define EXT_IoMgrConfigGetNextConnector  extern PFIOMGRCONFIGGETNEXTCONNECTOR pfIoMgrConfigGetNextConnector;
	#define GET_IoMgrConfigGetNextConnector(fl)  s_pfCMGetAPI2( "IoMgrConfigGetNextConnector", (RTS_VOID_FCTPTR *)&pfIoMgrConfigGetNextConnector, (fl), 0, 0)
	#define CAL_IoMgrConfigGetNextConnector  pfIoMgrConfigGetNextConnector
	#define CHK_IoMgrConfigGetNextConnector  (pfIoMgrConfigGetNextConnector != NULL)
	#define EXP_IoMgrConfigGetNextConnector  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetNextConnector", (RTS_UINTPTR)IoMgrConfigGetNextConnector, 0, 0) 
#endif




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
IoConfigConnector* CDECL IoMgrConfigGetFirstChild(IoConfigConnector *pConnectorList, int *pnCount, IoConfigConnector *pFather);
typedef IoConfigConnector* (CDECL * PFIOMGRCONFIGGETFIRSTCHILD) (IoConfigConnector *pConnectorList, int *pnCount, IoConfigConnector *pFather);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETFIRSTCHILD_NOTIMPLEMENTED)
	#define USE_IoMgrConfigGetFirstChild
	#define EXT_IoMgrConfigGetFirstChild
	#define GET_IoMgrConfigGetFirstChild(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrConfigGetFirstChild(p0,p1,p2)  (IoConfigConnector*)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrConfigGetFirstChild  FALSE
	#define EXP_IoMgrConfigGetFirstChild  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrConfigGetFirstChild
	#define EXT_IoMgrConfigGetFirstChild
	#define GET_IoMgrConfigGetFirstChild(fl)  CAL_CMGETAPI( "IoMgrConfigGetFirstChild" ) 
	#define CAL_IoMgrConfigGetFirstChild  IoMgrConfigGetFirstChild
	#define CHK_IoMgrConfigGetFirstChild  TRUE
	#define EXP_IoMgrConfigGetFirstChild  CAL_CMEXPAPI( "IoMgrConfigGetFirstChild" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrConfigGetFirstChild
	#define EXT_IoMgrConfigGetFirstChild
	#define GET_IoMgrConfigGetFirstChild(fl)  CAL_CMGETAPI( "IoMgrConfigGetFirstChild" ) 
	#define CAL_IoMgrConfigGetFirstChild  IoMgrConfigGetFirstChild
	#define CHK_IoMgrConfigGetFirstChild  TRUE
	#define EXP_IoMgrConfigGetFirstChild  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetFirstChild", (RTS_UINTPTR)IoMgrConfigGetFirstChild, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrConfigGetFirstChild
	#define EXT_CmpIoMgrIoMgrConfigGetFirstChild
	#define GET_CmpIoMgrIoMgrConfigGetFirstChild  ERR_OK
	#define CAL_CmpIoMgrIoMgrConfigGetFirstChild pICmpIoMgr->IIoMgrConfigGetFirstChild
	#define CHK_CmpIoMgrIoMgrConfigGetFirstChild (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrConfigGetFirstChild  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrConfigGetFirstChild
	#define EXT_IoMgrConfigGetFirstChild
	#define GET_IoMgrConfigGetFirstChild(fl)  CAL_CMGETAPI( "IoMgrConfigGetFirstChild" ) 
	#define CAL_IoMgrConfigGetFirstChild pICmpIoMgr->IIoMgrConfigGetFirstChild
	#define CHK_IoMgrConfigGetFirstChild (pICmpIoMgr != NULL)
	#define EXP_IoMgrConfigGetFirstChild  CAL_CMEXPAPI( "IoMgrConfigGetFirstChild" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrConfigGetFirstChild  PFIOMGRCONFIGGETFIRSTCHILD pfIoMgrConfigGetFirstChild;
	#define EXT_IoMgrConfigGetFirstChild  extern PFIOMGRCONFIGGETFIRSTCHILD pfIoMgrConfigGetFirstChild;
	#define GET_IoMgrConfigGetFirstChild(fl)  s_pfCMGetAPI2( "IoMgrConfigGetFirstChild", (RTS_VOID_FCTPTR *)&pfIoMgrConfigGetFirstChild, (fl), 0, 0)
	#define CAL_IoMgrConfigGetFirstChild  pfIoMgrConfigGetFirstChild
	#define CHK_IoMgrConfigGetFirstChild  (pfIoMgrConfigGetFirstChild != NULL)
	#define EXP_IoMgrConfigGetFirstChild  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetFirstChild", (RTS_UINTPTR)IoMgrConfigGetFirstChild, 0, 0) 
#endif




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
IoConfigConnector* CDECL IoMgrConfigGetNextChild(IoConfigConnector *pConnectorList, int *pnCount, IoConfigConnector *pFather);
typedef IoConfigConnector* (CDECL * PFIOMGRCONFIGGETNEXTCHILD) (IoConfigConnector *pConnectorList, int *pnCount, IoConfigConnector *pFather);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETNEXTCHILD_NOTIMPLEMENTED)
	#define USE_IoMgrConfigGetNextChild
	#define EXT_IoMgrConfigGetNextChild
	#define GET_IoMgrConfigGetNextChild(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrConfigGetNextChild(p0,p1,p2)  (IoConfigConnector*)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrConfigGetNextChild  FALSE
	#define EXP_IoMgrConfigGetNextChild  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrConfigGetNextChild
	#define EXT_IoMgrConfigGetNextChild
	#define GET_IoMgrConfigGetNextChild(fl)  CAL_CMGETAPI( "IoMgrConfigGetNextChild" ) 
	#define CAL_IoMgrConfigGetNextChild  IoMgrConfigGetNextChild
	#define CHK_IoMgrConfigGetNextChild  TRUE
	#define EXP_IoMgrConfigGetNextChild  CAL_CMEXPAPI( "IoMgrConfigGetNextChild" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrConfigGetNextChild
	#define EXT_IoMgrConfigGetNextChild
	#define GET_IoMgrConfigGetNextChild(fl)  CAL_CMGETAPI( "IoMgrConfigGetNextChild" ) 
	#define CAL_IoMgrConfigGetNextChild  IoMgrConfigGetNextChild
	#define CHK_IoMgrConfigGetNextChild  TRUE
	#define EXP_IoMgrConfigGetNextChild  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetNextChild", (RTS_UINTPTR)IoMgrConfigGetNextChild, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrConfigGetNextChild
	#define EXT_CmpIoMgrIoMgrConfigGetNextChild
	#define GET_CmpIoMgrIoMgrConfigGetNextChild  ERR_OK
	#define CAL_CmpIoMgrIoMgrConfigGetNextChild pICmpIoMgr->IIoMgrConfigGetNextChild
	#define CHK_CmpIoMgrIoMgrConfigGetNextChild (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrConfigGetNextChild  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrConfigGetNextChild
	#define EXT_IoMgrConfigGetNextChild
	#define GET_IoMgrConfigGetNextChild(fl)  CAL_CMGETAPI( "IoMgrConfigGetNextChild" ) 
	#define CAL_IoMgrConfigGetNextChild pICmpIoMgr->IIoMgrConfigGetNextChild
	#define CHK_IoMgrConfigGetNextChild (pICmpIoMgr != NULL)
	#define EXP_IoMgrConfigGetNextChild  CAL_CMEXPAPI( "IoMgrConfigGetNextChild" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrConfigGetNextChild  PFIOMGRCONFIGGETNEXTCHILD pfIoMgrConfigGetNextChild;
	#define EXT_IoMgrConfigGetNextChild  extern PFIOMGRCONFIGGETNEXTCHILD pfIoMgrConfigGetNextChild;
	#define GET_IoMgrConfigGetNextChild(fl)  s_pfCMGetAPI2( "IoMgrConfigGetNextChild", (RTS_VOID_FCTPTR *)&pfIoMgrConfigGetNextChild, (fl), 0, 0)
	#define CAL_IoMgrConfigGetNextChild  pfIoMgrConfigGetNextChild
	#define CHK_IoMgrConfigGetNextChild  (pfIoMgrConfigGetNextChild != NULL)
	#define EXP_IoMgrConfigGetNextChild  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetNextChild", (RTS_UINTPTR)IoMgrConfigGetNextChild, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrConfigGetConnectorList(IoConfigConnector **ppConnectorList, int *pnCount);
typedef RTS_RESULT (CDECL * PFIOMGRCONFIGGETCONNECTORLIST) (IoConfigConnector **ppConnectorList, int *pnCount);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETCONNECTORLIST_NOTIMPLEMENTED)
	#define USE_IoMgrConfigGetConnectorList
	#define EXT_IoMgrConfigGetConnectorList
	#define GET_IoMgrConfigGetConnectorList(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrConfigGetConnectorList(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrConfigGetConnectorList  FALSE
	#define EXP_IoMgrConfigGetConnectorList  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrConfigGetConnectorList
	#define EXT_IoMgrConfigGetConnectorList
	#define GET_IoMgrConfigGetConnectorList(fl)  CAL_CMGETAPI( "IoMgrConfigGetConnectorList" ) 
	#define CAL_IoMgrConfigGetConnectorList  IoMgrConfigGetConnectorList
	#define CHK_IoMgrConfigGetConnectorList  TRUE
	#define EXP_IoMgrConfigGetConnectorList  CAL_CMEXPAPI( "IoMgrConfigGetConnectorList" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrConfigGetConnectorList
	#define EXT_IoMgrConfigGetConnectorList
	#define GET_IoMgrConfigGetConnectorList(fl)  CAL_CMGETAPI( "IoMgrConfigGetConnectorList" ) 
	#define CAL_IoMgrConfigGetConnectorList  IoMgrConfigGetConnectorList
	#define CHK_IoMgrConfigGetConnectorList  TRUE
	#define EXP_IoMgrConfigGetConnectorList  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetConnectorList", (RTS_UINTPTR)IoMgrConfigGetConnectorList, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrConfigGetConnectorList
	#define EXT_CmpIoMgrIoMgrConfigGetConnectorList
	#define GET_CmpIoMgrIoMgrConfigGetConnectorList  ERR_OK
	#define CAL_CmpIoMgrIoMgrConfigGetConnectorList pICmpIoMgr->IIoMgrConfigGetConnectorList
	#define CHK_CmpIoMgrIoMgrConfigGetConnectorList (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrConfigGetConnectorList  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrConfigGetConnectorList
	#define EXT_IoMgrConfigGetConnectorList
	#define GET_IoMgrConfigGetConnectorList(fl)  CAL_CMGETAPI( "IoMgrConfigGetConnectorList" ) 
	#define CAL_IoMgrConfigGetConnectorList pICmpIoMgr->IIoMgrConfigGetConnectorList
	#define CHK_IoMgrConfigGetConnectorList (pICmpIoMgr != NULL)
	#define EXP_IoMgrConfigGetConnectorList  CAL_CMEXPAPI( "IoMgrConfigGetConnectorList" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrConfigGetConnectorList  PFIOMGRCONFIGGETCONNECTORLIST pfIoMgrConfigGetConnectorList;
	#define EXT_IoMgrConfigGetConnectorList  extern PFIOMGRCONFIGGETCONNECTORLIST pfIoMgrConfigGetConnectorList;
	#define GET_IoMgrConfigGetConnectorList(fl)  s_pfCMGetAPI2( "IoMgrConfigGetConnectorList", (RTS_VOID_FCTPTR *)&pfIoMgrConfigGetConnectorList, (fl), 0, 0)
	#define CAL_IoMgrConfigGetConnectorList  pfIoMgrConfigGetConnectorList
	#define CHK_IoMgrConfigGetConnectorList  (pfIoMgrConfigGetConnectorList != NULL)
	#define EXP_IoMgrConfigGetConnectorList  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetConnectorList", (RTS_UINTPTR)IoMgrConfigGetConnectorList, 0, 0) 
#endif




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
IoConfigConnector* CDECL IoMgrConfigGetConnector(IoConfigConnector *pConnectorList, int *pnCount, RTS_UI32 ulModuleType, RTS_UI32 ulInstance);
typedef IoConfigConnector* (CDECL * PFIOMGRCONFIGGETCONNECTOR) (IoConfigConnector *pConnectorList, int *pnCount, RTS_UI32 ulModuleType, RTS_UI32 ulInstance);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETCONNECTOR_NOTIMPLEMENTED)
	#define USE_IoMgrConfigGetConnector
	#define EXT_IoMgrConfigGetConnector
	#define GET_IoMgrConfigGetConnector(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrConfigGetConnector(p0,p1,p2,p3)  (IoConfigConnector*)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrConfigGetConnector  FALSE
	#define EXP_IoMgrConfigGetConnector  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrConfigGetConnector
	#define EXT_IoMgrConfigGetConnector
	#define GET_IoMgrConfigGetConnector(fl)  CAL_CMGETAPI( "IoMgrConfigGetConnector" ) 
	#define CAL_IoMgrConfigGetConnector  IoMgrConfigGetConnector
	#define CHK_IoMgrConfigGetConnector  TRUE
	#define EXP_IoMgrConfigGetConnector  CAL_CMEXPAPI( "IoMgrConfigGetConnector" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrConfigGetConnector
	#define EXT_IoMgrConfigGetConnector
	#define GET_IoMgrConfigGetConnector(fl)  CAL_CMGETAPI( "IoMgrConfigGetConnector" ) 
	#define CAL_IoMgrConfigGetConnector  IoMgrConfigGetConnector
	#define CHK_IoMgrConfigGetConnector  TRUE
	#define EXP_IoMgrConfigGetConnector  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetConnector", (RTS_UINTPTR)IoMgrConfigGetConnector, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrConfigGetConnector
	#define EXT_CmpIoMgrIoMgrConfigGetConnector
	#define GET_CmpIoMgrIoMgrConfigGetConnector  ERR_OK
	#define CAL_CmpIoMgrIoMgrConfigGetConnector pICmpIoMgr->IIoMgrConfigGetConnector
	#define CHK_CmpIoMgrIoMgrConfigGetConnector (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrConfigGetConnector  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrConfigGetConnector
	#define EXT_IoMgrConfigGetConnector
	#define GET_IoMgrConfigGetConnector(fl)  CAL_CMGETAPI( "IoMgrConfigGetConnector" ) 
	#define CAL_IoMgrConfigGetConnector pICmpIoMgr->IIoMgrConfigGetConnector
	#define CHK_IoMgrConfigGetConnector (pICmpIoMgr != NULL)
	#define EXP_IoMgrConfigGetConnector  CAL_CMEXPAPI( "IoMgrConfigGetConnector" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrConfigGetConnector  PFIOMGRCONFIGGETCONNECTOR pfIoMgrConfigGetConnector;
	#define EXT_IoMgrConfigGetConnector  extern PFIOMGRCONFIGGETCONNECTOR pfIoMgrConfigGetConnector;
	#define GET_IoMgrConfigGetConnector(fl)  s_pfCMGetAPI2( "IoMgrConfigGetConnector", (RTS_VOID_FCTPTR *)&pfIoMgrConfigGetConnector, (fl), 0, 0)
	#define CAL_IoMgrConfigGetConnector  pfIoMgrConfigGetConnector
	#define CHK_IoMgrConfigGetConnector  (pfIoMgrConfigGetConnector != NULL)
	#define EXP_IoMgrConfigGetConnector  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetConnector", (RTS_UINTPTR)IoMgrConfigGetConnector, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrConfigSetDiagnosis(IoConfigConnector *pConnector, RTS_UI32 ulFlags);
typedef RTS_RESULT (CDECL * PFIOMGRCONFIGSETDIAGNOSIS) (IoConfigConnector *pConnector, RTS_UI32 ulFlags);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGSETDIAGNOSIS_NOTIMPLEMENTED)
	#define USE_IoMgrConfigSetDiagnosis
	#define EXT_IoMgrConfigSetDiagnosis
	#define GET_IoMgrConfigSetDiagnosis(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrConfigSetDiagnosis(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrConfigSetDiagnosis  FALSE
	#define EXP_IoMgrConfigSetDiagnosis  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrConfigSetDiagnosis
	#define EXT_IoMgrConfigSetDiagnosis
	#define GET_IoMgrConfigSetDiagnosis(fl)  CAL_CMGETAPI( "IoMgrConfigSetDiagnosis" ) 
	#define CAL_IoMgrConfigSetDiagnosis  IoMgrConfigSetDiagnosis
	#define CHK_IoMgrConfigSetDiagnosis  TRUE
	#define EXP_IoMgrConfigSetDiagnosis  CAL_CMEXPAPI( "IoMgrConfigSetDiagnosis" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrConfigSetDiagnosis
	#define EXT_IoMgrConfigSetDiagnosis
	#define GET_IoMgrConfigSetDiagnosis(fl)  CAL_CMGETAPI( "IoMgrConfigSetDiagnosis" ) 
	#define CAL_IoMgrConfigSetDiagnosis  IoMgrConfigSetDiagnosis
	#define CHK_IoMgrConfigSetDiagnosis  TRUE
	#define EXP_IoMgrConfigSetDiagnosis  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigSetDiagnosis", (RTS_UINTPTR)IoMgrConfigSetDiagnosis, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrConfigSetDiagnosis
	#define EXT_CmpIoMgrIoMgrConfigSetDiagnosis
	#define GET_CmpIoMgrIoMgrConfigSetDiagnosis  ERR_OK
	#define CAL_CmpIoMgrIoMgrConfigSetDiagnosis pICmpIoMgr->IIoMgrConfigSetDiagnosis
	#define CHK_CmpIoMgrIoMgrConfigSetDiagnosis (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrConfigSetDiagnosis  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrConfigSetDiagnosis
	#define EXT_IoMgrConfigSetDiagnosis
	#define GET_IoMgrConfigSetDiagnosis(fl)  CAL_CMGETAPI( "IoMgrConfigSetDiagnosis" ) 
	#define CAL_IoMgrConfigSetDiagnosis pICmpIoMgr->IIoMgrConfigSetDiagnosis
	#define CHK_IoMgrConfigSetDiagnosis (pICmpIoMgr != NULL)
	#define EXP_IoMgrConfigSetDiagnosis  CAL_CMEXPAPI( "IoMgrConfigSetDiagnosis" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrConfigSetDiagnosis  PFIOMGRCONFIGSETDIAGNOSIS pfIoMgrConfigSetDiagnosis;
	#define EXT_IoMgrConfigSetDiagnosis  extern PFIOMGRCONFIGSETDIAGNOSIS pfIoMgrConfigSetDiagnosis;
	#define GET_IoMgrConfigSetDiagnosis(fl)  s_pfCMGetAPI2( "IoMgrConfigSetDiagnosis", (RTS_VOID_FCTPTR *)&pfIoMgrConfigSetDiagnosis, (fl), 0, 0)
	#define CAL_IoMgrConfigSetDiagnosis  pfIoMgrConfigSetDiagnosis
	#define CHK_IoMgrConfigSetDiagnosis  (pfIoMgrConfigSetDiagnosis != NULL)
	#define EXP_IoMgrConfigSetDiagnosis  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigSetDiagnosis", (RTS_UINTPTR)IoMgrConfigSetDiagnosis, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrConfigResetDiagnosis(IoConfigConnector *pConnector, RTS_UI32 ulFlags);
typedef RTS_RESULT (CDECL * PFIOMGRCONFIGRESETDIAGNOSIS) (IoConfigConnector *pConnector, RTS_UI32 ulFlags);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGRESETDIAGNOSIS_NOTIMPLEMENTED)
	#define USE_IoMgrConfigResetDiagnosis
	#define EXT_IoMgrConfigResetDiagnosis
	#define GET_IoMgrConfigResetDiagnosis(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrConfigResetDiagnosis(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrConfigResetDiagnosis  FALSE
	#define EXP_IoMgrConfigResetDiagnosis  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrConfigResetDiagnosis
	#define EXT_IoMgrConfigResetDiagnosis
	#define GET_IoMgrConfigResetDiagnosis(fl)  CAL_CMGETAPI( "IoMgrConfigResetDiagnosis" ) 
	#define CAL_IoMgrConfigResetDiagnosis  IoMgrConfigResetDiagnosis
	#define CHK_IoMgrConfigResetDiagnosis  TRUE
	#define EXP_IoMgrConfigResetDiagnosis  CAL_CMEXPAPI( "IoMgrConfigResetDiagnosis" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrConfigResetDiagnosis
	#define EXT_IoMgrConfigResetDiagnosis
	#define GET_IoMgrConfigResetDiagnosis(fl)  CAL_CMGETAPI( "IoMgrConfigResetDiagnosis" ) 
	#define CAL_IoMgrConfigResetDiagnosis  IoMgrConfigResetDiagnosis
	#define CHK_IoMgrConfigResetDiagnosis  TRUE
	#define EXP_IoMgrConfigResetDiagnosis  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigResetDiagnosis", (RTS_UINTPTR)IoMgrConfigResetDiagnosis, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrConfigResetDiagnosis
	#define EXT_CmpIoMgrIoMgrConfigResetDiagnosis
	#define GET_CmpIoMgrIoMgrConfigResetDiagnosis  ERR_OK
	#define CAL_CmpIoMgrIoMgrConfigResetDiagnosis pICmpIoMgr->IIoMgrConfigResetDiagnosis
	#define CHK_CmpIoMgrIoMgrConfigResetDiagnosis (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrConfigResetDiagnosis  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrConfigResetDiagnosis
	#define EXT_IoMgrConfigResetDiagnosis
	#define GET_IoMgrConfigResetDiagnosis(fl)  CAL_CMGETAPI( "IoMgrConfigResetDiagnosis" ) 
	#define CAL_IoMgrConfigResetDiagnosis pICmpIoMgr->IIoMgrConfigResetDiagnosis
	#define CHK_IoMgrConfigResetDiagnosis (pICmpIoMgr != NULL)
	#define EXP_IoMgrConfigResetDiagnosis  CAL_CMEXPAPI( "IoMgrConfigResetDiagnosis" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrConfigResetDiagnosis  PFIOMGRCONFIGRESETDIAGNOSIS pfIoMgrConfigResetDiagnosis;
	#define EXT_IoMgrConfigResetDiagnosis  extern PFIOMGRCONFIGRESETDIAGNOSIS pfIoMgrConfigResetDiagnosis;
	#define GET_IoMgrConfigResetDiagnosis(fl)  s_pfCMGetAPI2( "IoMgrConfigResetDiagnosis", (RTS_VOID_FCTPTR *)&pfIoMgrConfigResetDiagnosis, (fl), 0, 0)
	#define CAL_IoMgrConfigResetDiagnosis  pfIoMgrConfigResetDiagnosis
	#define CHK_IoMgrConfigResetDiagnosis  (pfIoMgrConfigResetDiagnosis != NULL)
	#define EXP_IoMgrConfigResetDiagnosis  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigResetDiagnosis", (RTS_UINTPTR)IoMgrConfigResetDiagnosis, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrReadParameter(RTS_UI32 ulModuleType, RTS_UI32 ulInstance, RTS_UI32 ulParameterId, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset);
typedef RTS_RESULT (CDECL * PFIOMGRREADPARAMETER) (RTS_UI32 ulModuleType, RTS_UI32 ulInstance, RTS_UI32 ulParameterId, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRREADPARAMETER_NOTIMPLEMENTED)
	#define USE_IoMgrReadParameter
	#define EXT_IoMgrReadParameter
	#define GET_IoMgrReadParameter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrReadParameter(p0,p1,p2,p3,p4,p5)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrReadParameter  FALSE
	#define EXP_IoMgrReadParameter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrReadParameter
	#define EXT_IoMgrReadParameter
	#define GET_IoMgrReadParameter(fl)  CAL_CMGETAPI( "IoMgrReadParameter" ) 
	#define CAL_IoMgrReadParameter  IoMgrReadParameter
	#define CHK_IoMgrReadParameter  TRUE
	#define EXP_IoMgrReadParameter  CAL_CMEXPAPI( "IoMgrReadParameter" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrReadParameter
	#define EXT_IoMgrReadParameter
	#define GET_IoMgrReadParameter(fl)  CAL_CMGETAPI( "IoMgrReadParameter" ) 
	#define CAL_IoMgrReadParameter  IoMgrReadParameter
	#define CHK_IoMgrReadParameter  TRUE
	#define EXP_IoMgrReadParameter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrReadParameter", (RTS_UINTPTR)IoMgrReadParameter, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrReadParameter
	#define EXT_CmpIoMgrIoMgrReadParameter
	#define GET_CmpIoMgrIoMgrReadParameter  ERR_OK
	#define CAL_CmpIoMgrIoMgrReadParameter pICmpIoMgr->IIoMgrReadParameter
	#define CHK_CmpIoMgrIoMgrReadParameter (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrReadParameter  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrReadParameter
	#define EXT_IoMgrReadParameter
	#define GET_IoMgrReadParameter(fl)  CAL_CMGETAPI( "IoMgrReadParameter" ) 
	#define CAL_IoMgrReadParameter pICmpIoMgr->IIoMgrReadParameter
	#define CHK_IoMgrReadParameter (pICmpIoMgr != NULL)
	#define EXP_IoMgrReadParameter  CAL_CMEXPAPI( "IoMgrReadParameter" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrReadParameter  PFIOMGRREADPARAMETER pfIoMgrReadParameter;
	#define EXT_IoMgrReadParameter  extern PFIOMGRREADPARAMETER pfIoMgrReadParameter;
	#define GET_IoMgrReadParameter(fl)  s_pfCMGetAPI2( "IoMgrReadParameter", (RTS_VOID_FCTPTR *)&pfIoMgrReadParameter, (fl), 0, 0)
	#define CAL_IoMgrReadParameter  pfIoMgrReadParameter
	#define CHK_IoMgrReadParameter  (pfIoMgrReadParameter != NULL)
	#define EXP_IoMgrReadParameter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrReadParameter", (RTS_UINTPTR)IoMgrReadParameter, 0, 0) 
#endif




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
RTS_RESULT CDECL IoMgrWriteParameter(RTS_UI32 ulModuleType, RTS_UI32 ulInstance, RTS_UI32 ulParameterId, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset);
typedef RTS_RESULT (CDECL * PFIOMGRWRITEPARAMETER) (RTS_UI32 ulModuleType, RTS_UI32 ulInstance, RTS_UI32 ulParameterId, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRWRITEPARAMETER_NOTIMPLEMENTED)
	#define USE_IoMgrWriteParameter
	#define EXT_IoMgrWriteParameter
	#define GET_IoMgrWriteParameter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrWriteParameter(p0,p1,p2,p3,p4,p5)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrWriteParameter  FALSE
	#define EXP_IoMgrWriteParameter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrWriteParameter
	#define EXT_IoMgrWriteParameter
	#define GET_IoMgrWriteParameter(fl)  CAL_CMGETAPI( "IoMgrWriteParameter" ) 
	#define CAL_IoMgrWriteParameter  IoMgrWriteParameter
	#define CHK_IoMgrWriteParameter  TRUE
	#define EXP_IoMgrWriteParameter  CAL_CMEXPAPI( "IoMgrWriteParameter" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrWriteParameter
	#define EXT_IoMgrWriteParameter
	#define GET_IoMgrWriteParameter(fl)  CAL_CMGETAPI( "IoMgrWriteParameter" ) 
	#define CAL_IoMgrWriteParameter  IoMgrWriteParameter
	#define CHK_IoMgrWriteParameter  TRUE
	#define EXP_IoMgrWriteParameter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrWriteParameter", (RTS_UINTPTR)IoMgrWriteParameter, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrWriteParameter
	#define EXT_CmpIoMgrIoMgrWriteParameter
	#define GET_CmpIoMgrIoMgrWriteParameter  ERR_OK
	#define CAL_CmpIoMgrIoMgrWriteParameter pICmpIoMgr->IIoMgrWriteParameter
	#define CHK_CmpIoMgrIoMgrWriteParameter (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrWriteParameter  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrWriteParameter
	#define EXT_IoMgrWriteParameter
	#define GET_IoMgrWriteParameter(fl)  CAL_CMGETAPI( "IoMgrWriteParameter" ) 
	#define CAL_IoMgrWriteParameter pICmpIoMgr->IIoMgrWriteParameter
	#define CHK_IoMgrWriteParameter (pICmpIoMgr != NULL)
	#define EXP_IoMgrWriteParameter  CAL_CMEXPAPI( "IoMgrWriteParameter" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrWriteParameter  PFIOMGRWRITEPARAMETER pfIoMgrWriteParameter;
	#define EXT_IoMgrWriteParameter  extern PFIOMGRWRITEPARAMETER pfIoMgrWriteParameter;
	#define GET_IoMgrWriteParameter(fl)  s_pfCMGetAPI2( "IoMgrWriteParameter", (RTS_VOID_FCTPTR *)&pfIoMgrWriteParameter, (fl), 0, 0)
	#define CAL_IoMgrWriteParameter  pfIoMgrWriteParameter
	#define CHK_IoMgrWriteParameter  (pfIoMgrWriteParameter != NULL)
	#define EXP_IoMgrWriteParameter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrWriteParameter", (RTS_UINTPTR)IoMgrWriteParameter, 0, 0) 
#endif




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
IBase * CDECL IoMgrConfigGetDriver(IoConfigConnector *pConnector, RTS_RESULT *pResult);
typedef IBase * (CDECL * PFIOMGRCONFIGGETDRIVER) (IoConfigConnector *pConnector, RTS_RESULT *pResult);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETDRIVER_NOTIMPLEMENTED)
	#define USE_IoMgrConfigGetDriver
	#define EXT_IoMgrConfigGetDriver
	#define GET_IoMgrConfigGetDriver(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrConfigGetDriver(p0,p1)  (IBase *)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrConfigGetDriver  FALSE
	#define EXP_IoMgrConfigGetDriver  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrConfigGetDriver
	#define EXT_IoMgrConfigGetDriver
	#define GET_IoMgrConfigGetDriver(fl)  CAL_CMGETAPI( "IoMgrConfigGetDriver" ) 
	#define CAL_IoMgrConfigGetDriver  IoMgrConfigGetDriver
	#define CHK_IoMgrConfigGetDriver  TRUE
	#define EXP_IoMgrConfigGetDriver  CAL_CMEXPAPI( "IoMgrConfigGetDriver" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrConfigGetDriver
	#define EXT_IoMgrConfigGetDriver
	#define GET_IoMgrConfigGetDriver(fl)  CAL_CMGETAPI( "IoMgrConfigGetDriver" ) 
	#define CAL_IoMgrConfigGetDriver  IoMgrConfigGetDriver
	#define CHK_IoMgrConfigGetDriver  TRUE
	#define EXP_IoMgrConfigGetDriver  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetDriver", (RTS_UINTPTR)IoMgrConfigGetDriver, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrConfigGetDriver
	#define EXT_CmpIoMgrIoMgrConfigGetDriver
	#define GET_CmpIoMgrIoMgrConfigGetDriver  ERR_OK
	#define CAL_CmpIoMgrIoMgrConfigGetDriver pICmpIoMgr->IIoMgrConfigGetDriver
	#define CHK_CmpIoMgrIoMgrConfigGetDriver (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrConfigGetDriver  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrConfigGetDriver
	#define EXT_IoMgrConfigGetDriver
	#define GET_IoMgrConfigGetDriver(fl)  CAL_CMGETAPI( "IoMgrConfigGetDriver" ) 
	#define CAL_IoMgrConfigGetDriver pICmpIoMgr->IIoMgrConfigGetDriver
	#define CHK_IoMgrConfigGetDriver (pICmpIoMgr != NULL)
	#define EXP_IoMgrConfigGetDriver  CAL_CMEXPAPI( "IoMgrConfigGetDriver" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrConfigGetDriver  PFIOMGRCONFIGGETDRIVER pfIoMgrConfigGetDriver;
	#define EXT_IoMgrConfigGetDriver  extern PFIOMGRCONFIGGETDRIVER pfIoMgrConfigGetDriver;
	#define GET_IoMgrConfigGetDriver(fl)  s_pfCMGetAPI2( "IoMgrConfigGetDriver", (RTS_VOID_FCTPTR *)&pfIoMgrConfigGetDriver, (fl), 0, 0)
	#define CAL_IoMgrConfigGetDriver  pfIoMgrConfigGetDriver
	#define CHK_IoMgrConfigGetDriver  (pfIoMgrConfigGetDriver != NULL)
	#define EXP_IoMgrConfigGetDriver  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetDriver", (RTS_UINTPTR)IoMgrConfigGetDriver, 0, 0) 
#endif




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
IoConfigConnector * CDECL IoMgrConfigGetConnectorByDriver(IBase *pIBase, int nIndex, RTS_RESULT *pResult);
typedef IoConfigConnector * (CDECL * PFIOMGRCONFIGGETCONNECTORBYDRIVER) (IBase *pIBase, int nIndex, RTS_RESULT *pResult);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCONFIGGETCONNECTORBYDRIVER_NOTIMPLEMENTED)
	#define USE_IoMgrConfigGetConnectorByDriver
	#define EXT_IoMgrConfigGetConnectorByDriver
	#define GET_IoMgrConfigGetConnectorByDriver(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrConfigGetConnectorByDriver(p0,p1,p2)  (IoConfigConnector *)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrConfigGetConnectorByDriver  FALSE
	#define EXP_IoMgrConfigGetConnectorByDriver  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrConfigGetConnectorByDriver
	#define EXT_IoMgrConfigGetConnectorByDriver
	#define GET_IoMgrConfigGetConnectorByDriver(fl)  CAL_CMGETAPI( "IoMgrConfigGetConnectorByDriver" ) 
	#define CAL_IoMgrConfigGetConnectorByDriver  IoMgrConfigGetConnectorByDriver
	#define CHK_IoMgrConfigGetConnectorByDriver  TRUE
	#define EXP_IoMgrConfigGetConnectorByDriver  CAL_CMEXPAPI( "IoMgrConfigGetConnectorByDriver" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrConfigGetConnectorByDriver
	#define EXT_IoMgrConfigGetConnectorByDriver
	#define GET_IoMgrConfigGetConnectorByDriver(fl)  CAL_CMGETAPI( "IoMgrConfigGetConnectorByDriver" ) 
	#define CAL_IoMgrConfigGetConnectorByDriver  IoMgrConfigGetConnectorByDriver
	#define CHK_IoMgrConfigGetConnectorByDriver  TRUE
	#define EXP_IoMgrConfigGetConnectorByDriver  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetConnectorByDriver", (RTS_UINTPTR)IoMgrConfigGetConnectorByDriver, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrConfigGetConnectorByDriver
	#define EXT_CmpIoMgrIoMgrConfigGetConnectorByDriver
	#define GET_CmpIoMgrIoMgrConfigGetConnectorByDriver  ERR_OK
	#define CAL_CmpIoMgrIoMgrConfigGetConnectorByDriver pICmpIoMgr->IIoMgrConfigGetConnectorByDriver
	#define CHK_CmpIoMgrIoMgrConfigGetConnectorByDriver (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrConfigGetConnectorByDriver  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrConfigGetConnectorByDriver
	#define EXT_IoMgrConfigGetConnectorByDriver
	#define GET_IoMgrConfigGetConnectorByDriver(fl)  CAL_CMGETAPI( "IoMgrConfigGetConnectorByDriver" ) 
	#define CAL_IoMgrConfigGetConnectorByDriver pICmpIoMgr->IIoMgrConfigGetConnectorByDriver
	#define CHK_IoMgrConfigGetConnectorByDriver (pICmpIoMgr != NULL)
	#define EXP_IoMgrConfigGetConnectorByDriver  CAL_CMEXPAPI( "IoMgrConfigGetConnectorByDriver" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrConfigGetConnectorByDriver  PFIOMGRCONFIGGETCONNECTORBYDRIVER pfIoMgrConfigGetConnectorByDriver;
	#define EXT_IoMgrConfigGetConnectorByDriver  extern PFIOMGRCONFIGGETCONNECTORBYDRIVER pfIoMgrConfigGetConnectorByDriver;
	#define GET_IoMgrConfigGetConnectorByDriver(fl)  s_pfCMGetAPI2( "IoMgrConfigGetConnectorByDriver", (RTS_VOID_FCTPTR *)&pfIoMgrConfigGetConnectorByDriver, (fl), 0, 0)
	#define CAL_IoMgrConfigGetConnectorByDriver  pfIoMgrConfigGetConnectorByDriver
	#define CHK_IoMgrConfigGetConnectorByDriver  (pfIoMgrConfigGetConnectorByDriver != NULL)
	#define EXP_IoMgrConfigGetConnectorByDriver  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrConfigGetConnectorByDriver", (RTS_UINTPTR)IoMgrConfigGetConnectorByDriver, 0, 0) 
#endif




/**
 * <description>
 * <p>Copy an Input from the Device to some local memory and swap to little endian if necessary.</p>
 * </description>
 * <param name="pChannel" type="IN" range="[NULL,VALID_COPINPUT_CHANNELMAP_1,VALID_COPINPUT_CHANNELMAP_2]">Pointer to one Channel Mapping</param>
 * <param name="pAddress" type="IN" range="[NULL,VALID_COPYINPUT_SRC]">Pointer to the Source Address</param>
 */
RTS_RESULT CDECL IoMgrCopyInputLE(IoConfigChannelMap *pChannel, char *pAddress);
typedef RTS_RESULT (CDECL * PFIOMGRCOPYINPUTLE) (IoConfigChannelMap *pChannel, char *pAddress);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCOPYINPUTLE_NOTIMPLEMENTED)
	#define USE_IoMgrCopyInputLE
	#define EXT_IoMgrCopyInputLE
	#define GET_IoMgrCopyInputLE(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrCopyInputLE(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrCopyInputLE  FALSE
	#define EXP_IoMgrCopyInputLE  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrCopyInputLE
	#define EXT_IoMgrCopyInputLE
	#define GET_IoMgrCopyInputLE(fl)  CAL_CMGETAPI( "IoMgrCopyInputLE" ) 
	#define CAL_IoMgrCopyInputLE  IoMgrCopyInputLE
	#define CHK_IoMgrCopyInputLE  TRUE
	#define EXP_IoMgrCopyInputLE  CAL_CMEXPAPI( "IoMgrCopyInputLE" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrCopyInputLE
	#define EXT_IoMgrCopyInputLE
	#define GET_IoMgrCopyInputLE(fl)  CAL_CMGETAPI( "IoMgrCopyInputLE" ) 
	#define CAL_IoMgrCopyInputLE  IoMgrCopyInputLE
	#define CHK_IoMgrCopyInputLE  TRUE
	#define EXP_IoMgrCopyInputLE  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrCopyInputLE", (RTS_UINTPTR)IoMgrCopyInputLE, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrCopyInputLE
	#define EXT_CmpIoMgrIoMgrCopyInputLE
	#define GET_CmpIoMgrIoMgrCopyInputLE  ERR_OK
	#define CAL_CmpIoMgrIoMgrCopyInputLE pICmpIoMgr->IIoMgrCopyInputLE
	#define CHK_CmpIoMgrIoMgrCopyInputLE (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrCopyInputLE  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrCopyInputLE
	#define EXT_IoMgrCopyInputLE
	#define GET_IoMgrCopyInputLE(fl)  CAL_CMGETAPI( "IoMgrCopyInputLE" ) 
	#define CAL_IoMgrCopyInputLE pICmpIoMgr->IIoMgrCopyInputLE
	#define CHK_IoMgrCopyInputLE (pICmpIoMgr != NULL)
	#define EXP_IoMgrCopyInputLE  CAL_CMEXPAPI( "IoMgrCopyInputLE" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrCopyInputLE  PFIOMGRCOPYINPUTLE pfIoMgrCopyInputLE;
	#define EXT_IoMgrCopyInputLE  extern PFIOMGRCOPYINPUTLE pfIoMgrCopyInputLE;
	#define GET_IoMgrCopyInputLE(fl)  s_pfCMGetAPI2( "IoMgrCopyInputLE", (RTS_VOID_FCTPTR *)&pfIoMgrCopyInputLE, (fl), 0, 0)
	#define CAL_IoMgrCopyInputLE  pfIoMgrCopyInputLE
	#define CHK_IoMgrCopyInputLE  (pfIoMgrCopyInputLE != NULL)
	#define EXP_IoMgrCopyInputLE  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrCopyInputLE", (RTS_UINTPTR)IoMgrCopyInputLE, 0, 0) 
#endif




/**
 * <description>
 * <p>Copy an Input from the Device to some local memory and swap to big endian if necessary</p>
 * </description>
 * <param name="pChannel" type="IN" range="[NULL,VALID_COPINPUT_CHANNELMAP_1,VALID_COPINPUT_CHANNELMAP_2]">Pointer to one Channel Mapping</param>
 * <param name="pAddress" type="IN" range="[NULL,VALID_COPYINPUT_SRC]">Pointer to the Source Address</param>
 */
RTS_RESULT CDECL IoMgrCopyInputBE(IoConfigChannelMap *pChannel, char *pAddress);
typedef RTS_RESULT (CDECL * PFIOMGRCOPYINPUTBE) (IoConfigChannelMap *pChannel, char *pAddress);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCOPYINPUTBE_NOTIMPLEMENTED)
	#define USE_IoMgrCopyInputBE
	#define EXT_IoMgrCopyInputBE
	#define GET_IoMgrCopyInputBE(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrCopyInputBE(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrCopyInputBE  FALSE
	#define EXP_IoMgrCopyInputBE  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrCopyInputBE
	#define EXT_IoMgrCopyInputBE
	#define GET_IoMgrCopyInputBE(fl)  CAL_CMGETAPI( "IoMgrCopyInputBE" ) 
	#define CAL_IoMgrCopyInputBE  IoMgrCopyInputBE
	#define CHK_IoMgrCopyInputBE  TRUE
	#define EXP_IoMgrCopyInputBE  CAL_CMEXPAPI( "IoMgrCopyInputBE" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrCopyInputBE
	#define EXT_IoMgrCopyInputBE
	#define GET_IoMgrCopyInputBE(fl)  CAL_CMGETAPI( "IoMgrCopyInputBE" ) 
	#define CAL_IoMgrCopyInputBE  IoMgrCopyInputBE
	#define CHK_IoMgrCopyInputBE  TRUE
	#define EXP_IoMgrCopyInputBE  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrCopyInputBE", (RTS_UINTPTR)IoMgrCopyInputBE, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrCopyInputBE
	#define EXT_CmpIoMgrIoMgrCopyInputBE
	#define GET_CmpIoMgrIoMgrCopyInputBE  ERR_OK
	#define CAL_CmpIoMgrIoMgrCopyInputBE pICmpIoMgr->IIoMgrCopyInputBE
	#define CHK_CmpIoMgrIoMgrCopyInputBE (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrCopyInputBE  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrCopyInputBE
	#define EXT_IoMgrCopyInputBE
	#define GET_IoMgrCopyInputBE(fl)  CAL_CMGETAPI( "IoMgrCopyInputBE" ) 
	#define CAL_IoMgrCopyInputBE pICmpIoMgr->IIoMgrCopyInputBE
	#define CHK_IoMgrCopyInputBE (pICmpIoMgr != NULL)
	#define EXP_IoMgrCopyInputBE  CAL_CMEXPAPI( "IoMgrCopyInputBE" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrCopyInputBE  PFIOMGRCOPYINPUTBE pfIoMgrCopyInputBE;
	#define EXT_IoMgrCopyInputBE  extern PFIOMGRCOPYINPUTBE pfIoMgrCopyInputBE;
	#define GET_IoMgrCopyInputBE(fl)  s_pfCMGetAPI2( "IoMgrCopyInputBE", (RTS_VOID_FCTPTR *)&pfIoMgrCopyInputBE, (fl), 0, 0)
	#define CAL_IoMgrCopyInputBE  pfIoMgrCopyInputBE
	#define CHK_IoMgrCopyInputBE  (pfIoMgrCopyInputBE != NULL)
	#define EXP_IoMgrCopyInputBE  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrCopyInputBE", (RTS_UINTPTR)IoMgrCopyInputBE, 0, 0) 
#endif




/**
 * <description>
 * <p>Copy an Output from local memory to the Device and swap to little endian if necessary</p>
 * </description>
 * <param name="pChannel" type="IN" range="[NULL,VALID_COPINPUT_CHANNELMAP_1,VALID_COPINPUT_CHANNELMAP_2]">Pointer to one Channel Mapping</param>
 * <param name="pAddress" type="IN" range="[NULL,VALID_COPYOUTPUT_DST]">Pointer to the Destination Address</param>
 */
RTS_RESULT CDECL IoMgrCopyOutputLE(IoConfigChannelMap *pChannel, char *pAddress);
typedef RTS_RESULT (CDECL * PFIOMGRCOPYOUTPUTLE) (IoConfigChannelMap *pChannel, char *pAddress);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCOPYOUTPUTLE_NOTIMPLEMENTED)
	#define USE_IoMgrCopyOutputLE
	#define EXT_IoMgrCopyOutputLE
	#define GET_IoMgrCopyOutputLE(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrCopyOutputLE(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrCopyOutputLE  FALSE
	#define EXP_IoMgrCopyOutputLE  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrCopyOutputLE
	#define EXT_IoMgrCopyOutputLE
	#define GET_IoMgrCopyOutputLE(fl)  CAL_CMGETAPI( "IoMgrCopyOutputLE" ) 
	#define CAL_IoMgrCopyOutputLE  IoMgrCopyOutputLE
	#define CHK_IoMgrCopyOutputLE  TRUE
	#define EXP_IoMgrCopyOutputLE  CAL_CMEXPAPI( "IoMgrCopyOutputLE" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrCopyOutputLE
	#define EXT_IoMgrCopyOutputLE
	#define GET_IoMgrCopyOutputLE(fl)  CAL_CMGETAPI( "IoMgrCopyOutputLE" ) 
	#define CAL_IoMgrCopyOutputLE  IoMgrCopyOutputLE
	#define CHK_IoMgrCopyOutputLE  TRUE
	#define EXP_IoMgrCopyOutputLE  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrCopyOutputLE", (RTS_UINTPTR)IoMgrCopyOutputLE, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrCopyOutputLE
	#define EXT_CmpIoMgrIoMgrCopyOutputLE
	#define GET_CmpIoMgrIoMgrCopyOutputLE  ERR_OK
	#define CAL_CmpIoMgrIoMgrCopyOutputLE pICmpIoMgr->IIoMgrCopyOutputLE
	#define CHK_CmpIoMgrIoMgrCopyOutputLE (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrCopyOutputLE  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrCopyOutputLE
	#define EXT_IoMgrCopyOutputLE
	#define GET_IoMgrCopyOutputLE(fl)  CAL_CMGETAPI( "IoMgrCopyOutputLE" ) 
	#define CAL_IoMgrCopyOutputLE pICmpIoMgr->IIoMgrCopyOutputLE
	#define CHK_IoMgrCopyOutputLE (pICmpIoMgr != NULL)
	#define EXP_IoMgrCopyOutputLE  CAL_CMEXPAPI( "IoMgrCopyOutputLE" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrCopyOutputLE  PFIOMGRCOPYOUTPUTLE pfIoMgrCopyOutputLE;
	#define EXT_IoMgrCopyOutputLE  extern PFIOMGRCOPYOUTPUTLE pfIoMgrCopyOutputLE;
	#define GET_IoMgrCopyOutputLE(fl)  s_pfCMGetAPI2( "IoMgrCopyOutputLE", (RTS_VOID_FCTPTR *)&pfIoMgrCopyOutputLE, (fl), 0, 0)
	#define CAL_IoMgrCopyOutputLE  pfIoMgrCopyOutputLE
	#define CHK_IoMgrCopyOutputLE  (pfIoMgrCopyOutputLE != NULL)
	#define EXP_IoMgrCopyOutputLE  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrCopyOutputLE", (RTS_UINTPTR)IoMgrCopyOutputLE, 0, 0) 
#endif




/**
 * <description>
 * <p>Copy an Output from local memory to the Device and swap to big endian if necessary</p>
 * </description>
 * <param name="pChannel" type="IN" range="[NULL,VALID_COPINPUT_CHANNELMAP_1,VALID_COPINPUT_CHANNELMAP_2]">Pointer to one Channel Mapping</param>
 * <param name="pAddress" type="IN" range="[NULL,VALID_COPYOUTPUT_DST]">Pointer to the DestinationAddress</param>
 */
RTS_RESULT CDECL IoMgrCopyOutputBE(IoConfigChannelMap *pChannel, char *pAddress);
typedef RTS_RESULT (CDECL * PFIOMGRCOPYOUTPUTBE) (IoConfigChannelMap *pChannel, char *pAddress);
#if defined(CMPIOMGR_NOTIMPLEMENTED) || defined(IOMGRCOPYOUTPUTBE_NOTIMPLEMENTED)
	#define USE_IoMgrCopyOutputBE
	#define EXT_IoMgrCopyOutputBE
	#define GET_IoMgrCopyOutputBE(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoMgrCopyOutputBE(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoMgrCopyOutputBE  FALSE
	#define EXP_IoMgrCopyOutputBE  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoMgrCopyOutputBE
	#define EXT_IoMgrCopyOutputBE
	#define GET_IoMgrCopyOutputBE(fl)  CAL_CMGETAPI( "IoMgrCopyOutputBE" ) 
	#define CAL_IoMgrCopyOutputBE  IoMgrCopyOutputBE
	#define CHK_IoMgrCopyOutputBE  TRUE
	#define EXP_IoMgrCopyOutputBE  CAL_CMEXPAPI( "IoMgrCopyOutputBE" ) 
#elif defined(MIXED_LINK) && !defined(CMPIOMGR_EXTERNAL)
	#define USE_IoMgrCopyOutputBE
	#define EXT_IoMgrCopyOutputBE
	#define GET_IoMgrCopyOutputBE(fl)  CAL_CMGETAPI( "IoMgrCopyOutputBE" ) 
	#define CAL_IoMgrCopyOutputBE  IoMgrCopyOutputBE
	#define CHK_IoMgrCopyOutputBE  TRUE
	#define EXP_IoMgrCopyOutputBE  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrCopyOutputBE", (RTS_UINTPTR)IoMgrCopyOutputBE, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoMgrIoMgrCopyOutputBE
	#define EXT_CmpIoMgrIoMgrCopyOutputBE
	#define GET_CmpIoMgrIoMgrCopyOutputBE  ERR_OK
	#define CAL_CmpIoMgrIoMgrCopyOutputBE pICmpIoMgr->IIoMgrCopyOutputBE
	#define CHK_CmpIoMgrIoMgrCopyOutputBE (pICmpIoMgr != NULL)
	#define EXP_CmpIoMgrIoMgrCopyOutputBE  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoMgrCopyOutputBE
	#define EXT_IoMgrCopyOutputBE
	#define GET_IoMgrCopyOutputBE(fl)  CAL_CMGETAPI( "IoMgrCopyOutputBE" ) 
	#define CAL_IoMgrCopyOutputBE pICmpIoMgr->IIoMgrCopyOutputBE
	#define CHK_IoMgrCopyOutputBE (pICmpIoMgr != NULL)
	#define EXP_IoMgrCopyOutputBE  CAL_CMEXPAPI( "IoMgrCopyOutputBE" ) 
#else /* DYNAMIC_LINK */
	#define USE_IoMgrCopyOutputBE  PFIOMGRCOPYOUTPUTBE pfIoMgrCopyOutputBE;
	#define EXT_IoMgrCopyOutputBE  extern PFIOMGRCOPYOUTPUTBE pfIoMgrCopyOutputBE;
	#define GET_IoMgrCopyOutputBE(fl)  s_pfCMGetAPI2( "IoMgrCopyOutputBE", (RTS_VOID_FCTPTR *)&pfIoMgrCopyOutputBE, (fl), 0, 0)
	#define CAL_IoMgrCopyOutputBE  pfIoMgrCopyOutputBE
	#define CHK_IoMgrCopyOutputBE  (pfIoMgrCopyOutputBE != NULL)
	#define EXP_IoMgrCopyOutputBE  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"IoMgrCopyOutputBE", (RTS_UINTPTR)IoMgrCopyOutputBE, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFIOMGREXCEPTIONHANDLER IIoMgrExceptionHandler;
 	PFIOMGRREGISTERINSTANCE IIoMgrRegisterInstance;
 	PFIOMGRREGISTERINSTANCE2 IIoMgrRegisterInstance2;
 	PFIOMGRUNREGISTERINSTANCE IIoMgrUnregisterInstance;
 	PFIOMGRGETFIRSTDRIVERINSTANCE IIoMgrGetFirstDriverInstance;
 	PFIOMGRGETNEXTDRIVERINSTANCE IIoMgrGetNextDriverInstance;
 	PFIOMGRSETDRIVERPROPERTIES IIoMgrSetDriverProperties;
 	PFIOMGRGETDRIVERPROPERTIES IIoMgrGetDriverProperties;
 	PFIOMGRSETDRIVERPROPERTY IIoMgrSetDriverProperty;
 	PFIOMGRREGISTERCONFIGAPPLICATION IIoMgrRegisterConfigApplication;
 	PFIOMGRUNREGISTERCONFIGAPPLICATION IIoMgrUnregisterConfigApplication;
 	PFIOMGRGETCONFIGAPPLICATION IIoMgrGetConfigApplication;
 	PFIOMGRUPDATECONFIGURATION IIoMgrUpdateConfiguration;
 	PFIOMGRUPDATECONFIGURATION2 IIoMgrUpdateConfiguration2;
 	PFIOMGRHASTASKIOS IIoMgrHasTaskIOs;
 	PFIOMGRUPDATEMAPPING IIoMgrUpdateMapping;
 	PFIOMGRUPDATEMAPPING2 IIoMgrUpdateMapping2;
 	PFIOMGRRECONFIGURE IIoMgrReconfigure;
 	PFIOMGRREADINPUTS IIoMgrReadInputs;
 	PFIOMGRWRITEOUTPUTS IIoMgrWriteOutputs;
 	PFIOMGRSTARTBUSCYCLE IIoMgrStartBusCycle;
 	PFIOMGRSTARTBUSCYCLE2 IIoMgrStartBusCycle2;
 	PFIOMGRGETBUSCYCLETYPE IIoMgrGetBusCycleType;
 	PFIOMGRSCANMODULES IIoMgrScanModules;
 	PFIOMGRGETMODULEDIAGNOSIS IIoMgrGetModuleDiagnosis;
 	PFIOMGRIDENTIFY IIoMgrIdentify;
 	PFIOMGRNOMINATE IIoMgrNominate;
 	PFIOMGRWATCHDOGTRIGGER IIoMgrWatchdogTrigger;
 	PFIOMGRCONFIGGETPARAMETER IIoMgrConfigGetParameter;
 	PFIOMGRCONFIGGETPARAMETERVALUEDWORD IIoMgrConfigGetParameterValueDword;
 	PFIOMGRCONFIGGETPARAMETERVALUEWORD IIoMgrConfigGetParameterValueWord;
 	PFIOMGRCONFIGGETPARAMETERVALUEBYTE IIoMgrConfigGetParameterValueByte;
 	PFIOMGRCONFIGGETPARAMETERVALUEPOINTER IIoMgrConfigGetParameterValuePointer;
 	PFIOMGRCONFIGGETFIRSTCONNECTOR IIoMgrConfigGetFirstConnector;
 	PFIOMGRCONFIGGETNEXTCONNECTOR IIoMgrConfigGetNextConnector;
 	PFIOMGRCONFIGGETFIRSTCHILD IIoMgrConfigGetFirstChild;
 	PFIOMGRCONFIGGETNEXTCHILD IIoMgrConfigGetNextChild;
 	PFIOMGRCONFIGGETCONNECTORLIST IIoMgrConfigGetConnectorList;
 	PFIOMGRCONFIGGETCONNECTOR IIoMgrConfigGetConnector;
 	PFIOMGRCONFIGSETDIAGNOSIS IIoMgrConfigSetDiagnosis;
 	PFIOMGRCONFIGRESETDIAGNOSIS IIoMgrConfigResetDiagnosis;
 	PFIOMGRREADPARAMETER IIoMgrReadParameter;
 	PFIOMGRWRITEPARAMETER IIoMgrWriteParameter;
 	PFIOMGRCONFIGGETDRIVER IIoMgrConfigGetDriver;
 	PFIOMGRCONFIGGETCONNECTORBYDRIVER IIoMgrConfigGetConnectorByDriver;
 	PFIOMGRCOPYINPUTLE IIoMgrCopyInputLE;
 	PFIOMGRCOPYINPUTBE IIoMgrCopyInputBE;
 	PFIOMGRCOPYOUTPUTLE IIoMgrCopyOutputLE;
 	PFIOMGRCOPYOUTPUTBE IIoMgrCopyOutputBE;
 } ICmpIoMgr_C;

#ifdef CPLUSPLUS
class ICmpIoMgr : public IBase
{
	public:
		virtual RTS_RESULT CDECL IIoMgrExceptionHandler(char *pszApplication, RTS_UI32 ulException) =0;
		virtual RTS_HANDLE CDECL IIoMgrRegisterInstance(IBase *pIBase, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IIoMgrRegisterInstance2(IBase *pIBase, int bIecDriver, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IIoMgrUnregisterInstance(IBase *pIBase) =0;
		virtual IBase* CDECL IIoMgrGetFirstDriverInstance(int *pbIecDriver, RTS_RESULT *pResult) =0;
		virtual IBase* CDECL IIoMgrGetNextDriverInstance(IBase *pIBasePrev, int *pbIecDriver, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IIoMgrSetDriverProperties(IBase *pIBase, RTS_UI32 ulProperties) =0;
		virtual RTS_RESULT CDECL IIoMgrGetDriverProperties(IBase *pIBase, RTS_UI32 **ppulProperty) =0;
		virtual RTS_RESULT CDECL IIoMgrSetDriverProperty(IBase *pIBase, RTS_UI32 ulProperty, int bValue) =0;
		virtual RTS_RESULT CDECL IIoMgrRegisterConfigApplication(char *pszConfigApplication) =0;
		virtual RTS_RESULT CDECL IIoMgrUnregisterConfigApplication(char *pszConfigApplication) =0;
		virtual RTS_RESULT CDECL IIoMgrGetConfigApplication(char *pszConfigApplication, int *pnMaxLen) =0;
		virtual RTS_RESULT CDECL IIoMgrUpdateConfiguration(IoConfigConnector *pConnectorList, int nCount) =0;
		virtual RTS_RESULT CDECL IIoMgrUpdateConfiguration2(IoConfigConnector *pConnectorList, int nCount, char *pszConfigApplication) =0;
		virtual RTS_BOOL CDECL IIoMgrHasTaskIOs(RTS_UI32 dwTaskId, RTS_UI16 taskMapType, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IIoMgrUpdateMapping(IoConfigTaskMap *pTaskMapList, int nCount) =0;
		virtual RTS_RESULT CDECL IIoMgrUpdateMapping2(IoConfigTaskMap *pTaskMapList, int nCount, char *pszConfigApplication) =0;
		virtual RTS_RESULT CDECL IIoMgrReconfigure(IoConfigConnector *pConnector, RTS_UI32 *pui32State) =0;
		virtual RTS_RESULT CDECL IIoMgrReadInputs(IoConfigTaskMap *pTaskMap) =0;
		virtual RTS_RESULT CDECL IIoMgrWriteOutputs(IoConfigTaskMap *pTaskMap) =0;
		virtual RTS_RESULT CDECL IIoMgrStartBusCycle(IoConfigConnector *pConnector) =0;
		virtual RTS_RESULT CDECL IIoMgrStartBusCycle2(IoConfigConnector *pConnector, RTS_UI32 dwType) =0;
		virtual RTS_RESULT CDECL IIoMgrGetBusCycleType(IoConfigConnector *pConnector, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IIoMgrScanModules(IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount) =0;
		virtual RTS_RESULT CDECL IIoMgrGetModuleDiagnosis(IoConfigConnector *pConnector) =0;
		virtual RTS_RESULT CDECL IIoMgrIdentify(IoConfigConnector *pConnector) =0;
		virtual RTS_RESULT CDECL IIoMgrNominate(IoConfigConnector *pConnector) =0;
		virtual RTS_RESULT CDECL IIoMgrWatchdogTrigger(IoConfigConnector *pConnector) =0;
		virtual IoConfigParameter* CDECL IIoMgrConfigGetParameter(IoConfigConnector *pConnector, RTS_UI32 dwParameterId) =0;
		virtual RTS_UI32 CDECL IIoMgrConfigGetParameterValueDword(IoConfigParameter *pParameter, RTS_RESULT *pResult) =0;
		virtual unsigned short CDECL IIoMgrConfigGetParameterValueWord(IoConfigParameter *pParameter, RTS_RESULT *pResult) =0;
		virtual unsigned char CDECL IIoMgrConfigGetParameterValueByte(IoConfigParameter *pParameter, RTS_RESULT *pResult) =0;
		virtual void * CDECL IIoMgrConfigGetParameterValuePointer(IoConfigParameter *pParameter, RTS_RESULT *pResult) =0;
		virtual IoConfigConnector* CDECL IIoMgrConfigGetFirstConnector(IoConfigConnector *pConnectorList, int *pnCount, unsigned short wType) =0;
		virtual IoConfigConnector* CDECL IIoMgrConfigGetNextConnector(IoConfigConnector *pConnectorList, int *pnCount, unsigned short wType) =0;
		virtual IoConfigConnector* CDECL IIoMgrConfigGetFirstChild(IoConfigConnector *pConnectorList, int *pnCount, IoConfigConnector *pFather) =0;
		virtual IoConfigConnector* CDECL IIoMgrConfigGetNextChild(IoConfigConnector *pConnectorList, int *pnCount, IoConfigConnector *pFather) =0;
		virtual RTS_RESULT CDECL IIoMgrConfigGetConnectorList(IoConfigConnector **ppConnectorList, int *pnCount) =0;
		virtual IoConfigConnector* CDECL IIoMgrConfigGetConnector(IoConfigConnector *pConnectorList, int *pnCount, RTS_UI32 ulModuleType, RTS_UI32 ulInstance) =0;
		virtual RTS_RESULT CDECL IIoMgrConfigSetDiagnosis(IoConfigConnector *pConnector, RTS_UI32 ulFlags) =0;
		virtual RTS_RESULT CDECL IIoMgrConfigResetDiagnosis(IoConfigConnector *pConnector, RTS_UI32 ulFlags) =0;
		virtual RTS_RESULT CDECL IIoMgrReadParameter(RTS_UI32 ulModuleType, RTS_UI32 ulInstance, RTS_UI32 ulParameterId, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset) =0;
		virtual RTS_RESULT CDECL IIoMgrWriteParameter(RTS_UI32 ulModuleType, RTS_UI32 ulInstance, RTS_UI32 ulParameterId, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset) =0;
		virtual IBase * CDECL IIoMgrConfigGetDriver(IoConfigConnector *pConnector, RTS_RESULT *pResult) =0;
		virtual IoConfigConnector * CDECL IIoMgrConfigGetConnectorByDriver(IBase *pIBase, int nIndex, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IIoMgrCopyInputLE(IoConfigChannelMap *pChannel, char *pAddress) =0;
		virtual RTS_RESULT CDECL IIoMgrCopyInputBE(IoConfigChannelMap *pChannel, char *pAddress) =0;
		virtual RTS_RESULT CDECL IIoMgrCopyOutputLE(IoConfigChannelMap *pChannel, char *pAddress) =0;
		virtual RTS_RESULT CDECL IIoMgrCopyOutputBE(IoConfigChannelMap *pChannel, char *pAddress) =0;
};
	#ifndef ITF_CmpIoMgr
		#define ITF_CmpIoMgr static ICmpIoMgr *pICmpIoMgr = NULL;
	#endif
	#define EXTITF_CmpIoMgr
#else	/*CPLUSPLUS*/
	typedef ICmpIoMgr_C		ICmpIoMgr;
	#ifndef ITF_CmpIoMgr
		#define ITF_CmpIoMgr
	#endif
	#define EXTITF_CmpIoMgr
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPIOMGRITF_H_*/
