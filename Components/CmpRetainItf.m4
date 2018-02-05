/**
 * <interfacename>CmpRetain</interfacename>
 * <description> 
 *	<p>This is the interface of the retain manager. Retains are data that are not lost after a reboot (non-volatile).</p>
 *	<p>To realize non-volatile data, following different techniques are used typically:</p>
 *	<p>
 *	<ul>
 *		<li>Store data at shutdown on a non-volatile medium (e.g. harddisk): This can be used only on systems with
 *		a defined shutdown and with an UPS (external power supply)!</li>
 *		<li>Store retain data directly on a non-voaltile RAM (SRAM, NVRAM, etc.): This can be used only on systems with
 *		this types of memory.</li>
 *	</ul>
 *	</p>
 *	<p>All retain data is checked for consistency with a data GUID. This GUID is written at the beginning of each
 *	retain area and can be checked after the next restore.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpRetain')


/**
 * <category>Static defines</category>
 * <description>Number of static retain memory entries to manage</description>
 */
#ifndef CMPRETAIN_NUM_OF_STATIC_RETAINS
	#define CMPRETAIN_NUM_OF_STATIC_RETAINS	8
#endif

/**
 * <category>Static defines</category>
 * <description>File extension for storing retains</description>
 */
#ifndef CMPRETAIN_RETAIN_FILE_EXTENSION
	#define CMPRETAIN_RETAIN_FILE_EXTENSION			".ret"
#endif


/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Address of the SRAM memory can be specified here. The physical address is 
 *	mapped afterwards in to the address space of the runtime process.
 *	Retain parameter for type RETAIN_SRAM (see corresponding category in CmpAppItf.h).</description>
 */
#define CMPRETAINKEY_INT_RETAIN_SRAM_ADDRESS		"Retain.SRAM.Address"

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Address of the SRAM memory can be specified here.
 *	The address _must_ still be mapped in the address space of the runtime process!
 *	Retain parameter for type RETAIN_SRAM (see corresponding category in CmpAppItf.h).</description>
 */
#define CMPRETAINKEY_INT_RETAIN_SRAM_ADDRESS_MAPPED	"Retain.SRAM.AddressMapped"

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Specifies the size of the SRAM.
 *	Retain parameter for type RETAIN_SRAM (see corresponding category in CmpAppItf.h).</description>
 */
#define CMPRETAINKEY_INT_RETAIN_SRAM_SIZE			"Retain.SRAM.Size"


/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Settings to simulate a SRAM with a heap memory</description>
 */
#define CMPRETAINKEY_INT_RETAIN_SIMULATE_SRAM	"SimulateSRAM"


/**
 * <category>Event parameter</category>
 * <element name="iRetainSize" type="IN">Size of the SRAM in bytes</element>
 * <element name="pPhysicalAddress" type="IN">Physical address of the SRAM. pMappedAddress must set to NULL.
 *											NOTE: Is mapped by the runtime system!</element>
 * <element name="pMappedAddress" type="IN">Mapped address of the SRAM. pPhysicalAddress must set to NULL.
 *											NOTE: Is a still mapped address and is used directly!</element>
 */
typedef struct
{
	void *pPhysicalAddress;
	void *pMappedAddress;
	unsigned long ulRetainSize;
} EVTPARAM_CmpRetainSRAM;
#define EVTPARAMID_CmpRetainSRAM	0x0001
#define EVTVERSION_CmpRetainSRAM	0x0001

/**
 * <category>Events</category>
 * <description>Event is sent to configure the SRAM</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpRetainSRAM</param>
 */
#define EVT_RetainGetSRAM					MAKE_EVENTID(EVTCLASS_INFO, 1)


/**
 * <category>Static defines</category>
 * <description>Tag types to detect the beginning of each retain area</description>
 *	<element name="TAG_RETAIN_USED" type="IN">Retain area is in use</element>
 *	<element name="TAG_RETAIN_FREE" type="IN">Retain area is free. Can be used for new areas</element>
 *	<element name="TAG_RETAIN_RESERVED" type="IN">Retain area is reserved, because it was in use before the last shutdown.
 *		After complete reboot, this area is marked as free, if it is no longer in use.</element>
 */
#define TAG_RETAIN_USED					UINT32_C(0xABACADAE)
#define TAG_RETAIN_PERSISTENT_USED		UINT32_C(0xABADAEAF)
#define TAG_RETAIN_FREE					UINT32_C(0xEBECEDEE)
#define TAG_RETAIN_RESERVED				UINT32_C(0xFBFCFDFE)
#define TAG_RETAIN_PERSISTENT_RESERVED	UINT32_C(0xFBFDFEFF)

#define TAG_RETAIN_SWAPPED				UINT32_C(0xAEADACAB)	/* Only used for backward compatibility */

/**
 * <category>Retain header</category>
 * <description>Header that is written at the beginning of each retain area</description>
 *	<element name="ulTag" type="IN">Start tag of a retain area.
 *	 TAG_RETAIN: Occupied retain area
 *	 TAG_RETAIN_FREE: Free retain area</element>
 *	<element name="ulSize" type="IN">Size of the retain area</element>
 *	<element name="DataGuid" type="IN">Data guid of the retain area</element>
 */
typedef struct
{
	RTS_UI32 ulTag;
	RTS_UI32 ulSize;
	RTS_GUID DataGuid;
} RetainHeader;

/**
 * <category>Retain type</category>
 * <description></description>
 *	<element name="RETAIN_NONE" type="IN">No retain handling specified. All retain data gets lost at the next reboot!</element>
 *	<element name="RETAIN_IN_SRAM" type="IN">Retains are saved in a non-volatile RAM (SRAM)</element>
 *	<element name="RETAIN_ON_POWERFAIL" type="IN">All retain data will be stored on a harddisk at the defined shutdown and 
 *		are restored from the harddisk at the next reboot</element>
 */
typedef enum
{
	RETAIN_NONE,
	RETAIN_IN_SRAM,
	RETAIN_ON_POWERFAIL
} RetainType;

/**
 * <category>Delete option</category>
 * <description></description>
 *	<element name="CMPRETAIN_DELETEOPTION_REMOVE" type="IN">Only remove retain memory from retain management</element>
 *	<element name="CMPRETAIN_DELETEOPTION_ALL" type="IN">Release retain memory, mark memory as free and call RetainUpdate() to mark reserved segment as free! Complete retain memory is deleted!</element>
 *	<element name="CMPRETAIN_DELETEOPTION_REMOVE_AND_FREE" type="IN">remove retain memory from retain management and mark as free. Don't delete retain file!</element>
 */
#define CMPRETAIN_DELETEOPTION_REMOVE				0
#define CMPRETAIN_DELETEOPTION_ALL					1
#define CMPRETAIN_DELETEOPTION_REMOVE_AND_FREE		2

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Routine to allocate retain memory</description>
 * <param name="pszName" type="IN">Name to assign to the retain memory</param>
 * <param name="pDataGUID" type="IN">Pointer to data GUID (GUID of the data content or another unique GUID)</param>
 * <param name="rtType" type="IN">Retain type</param>
 * <param name="usAreaType" type="IN">Area type. See category "Area Types" in SysMemItf.h for detailed information</param>
 * <param name="iSize" type="IN">Requested size of the retain area</param>
 * <param name="bRestore" type="IN">1=if retain should be restored, 0=no restore necessary</param>
 * <param name="ppbyRetain" type="OUT">Pointer pointer to return the retain memory</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `RetainAlloc', `(char *pszName, RTS_GUID *pDataGUID, RetainType rtType, RTS_UI16 usAreaType, RTS_SIZE iSize, int bRestore, RTS_UI8 **ppbyRetain)')

/**
 * <description>Release the retain memory</description>
 * <param name="pszName" type="IN">Name that was assigned to the retain memory</param>
 * <param name="pbyRetain" type="IN">Pointer of the retain memory to release</param>
 * <param name="nDeleteOption" type="IN">Option to delete retain memory. See "Delete option"</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `RetainFree', `(char *pszName, RTS_UI8 *pbyRetain, int nDeleteOption)')

/**
 * <description>Update data GUID in the specified retain area</description>
 * <param name="pszName" type="IN">Name that was assigned to the retain memory</param>
 * <param name="pbyRetain" type="IN">Pointer of the retain memory to release</param>
 * <param name="pDataGuidOld" type="IN">Pointer to old data GUID</param>
 * <param name="pDataGuidNew" type="IN">Pointer to new data GUID</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `RetainUpdateGuid', `(char *pszName, RTS_UI8 *pbyRetain, RTS_GUID *pDataGuidOld, RTS_GUID *pDataGuidNew)')

/**
 * <description>Check GUID that is stored in the retain memory</description>
 * <param name="pszName" type="IN">Name that was assigned to the retain memory</param>
 * <param name="pbyRetain" type="IN">Pointer of the retain memory to release</param>
 * <param name="pDataGUID" type="IN">Pointer to data GUID</param>
 * <param name="usAreaType" type="IN">Area type. See category "Area Types" in SysMemItf.h for detailed information</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `RetainCheckGuid', `(char *pszName, RTS_UI8 *pbyRetain, RTS_GUID *pDataGuid, RTS_UI16 usAreaType)')

/**
 * <description>Update retain management. Can be used to detect all free retain areas after loading all bootprojects</description>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `RetainUpdate', `(void)')

/**
 * <description>Function to store retain data. Is used for example to store retains on a harddisk.</description>
 * <param name="pszName" type="IN">Name that was assigned to the retain memory</param>
 * <param name="iSize" type="IN">Requested size of the retain area</param>
 * <param name="pDataGUID" type="IN">Data guid of the retain area</param>
 * <param name="pbyRetain" type="IN">Pointer of the retain memory</param>
 * <param name="bBackup" type="IN">If parameter is 1, then the retain data of the specified area is stored for backup needs</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `RetainStore', `(char *pszName, RTS_UI8 *pbyRetain, RTS_SIZE iSize, RTS_GUID *pDataGUID, int bBackup)')

/**
 * <description>Function to store retain data. Is used for example to store retains on a harddisk.</description>
 * <param name="pszFile" type="IN">Name of the file to store retains to</param>
 * <param name="pszName" type="IN">Name that was assigned to the retain memory</param>
 * <param name="iSize" type="IN">Requested size of the retain area</param>
 * <param name="pDataGUID" type="IN">Data guid of the retain area</param>
 * <param name="pbyRetain" type="IN">Pointer of the retain memory</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `RetainStoreInFile', `(char* pszFile, char *pszName, RTS_UI8 *pbyRetain, RTS_SIZE iSize, RTS_GUID *pDataGUID)')

/**
 * <description>Function to restore retain data after booting the plc.
 *	Is used for example to restore retains from a harddisk.</description>
 * <param name="pszName" type="IN">Name that was assigned to the retain memory</param>
 * <param name="iSize" type="IN">Requested size of the retain area</param>
 * <param name="pDataGUID" type="IN">Data guid of the retain area</param>
 * <param name="pbyRetain" type="IN">Pointer of the retain memory</param>
 * <param name="usAreaType" type="IN">Area type. See category "Area Types" in SysMemItf.h for detailed information</param>
 * <param name="bBackup" type="IN">If parameter is 1, then the retain data of the specified area is restored for backup needs</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `RetainRestore', `(char *pszName, RTS_UI8 *pbyRetain, RTS_SIZE iSize, RTS_GUID *pDataGUID, RTS_UI16 usAreaType, int bBackup)')

/**
 * <description>Function to restore retain data after booting the plc.
 *	Is used for example to restore retains from a harddisk.</description>
 * <param name="pszFile" type="IN">Name of the file to restore retains from</param>
 * <param name="pszName" type="IN">Name that was assigned to the retain memory</param>
 * <param name="iSize" type="IN">Requested size of the retain area</param>
 * <param name="pDataGUID" type="IN">Data guid of the retain area</param>
 * <param name="pbyRetain" type="IN">Pointer of the retain memory</param>
 * <param name="usAreaType" type="IN">Area type. See category "Area Types" in SysMemItf.h for detailed information</param>
 * <param name="bBackup" type="IN">If parameter is 1, then the retain data of the specified area is restored for backup needs</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `RetainRestoreFromFile', `(char* pszFile, char *pszName, RTS_UI8 *pbyRetain, RTS_SIZE iSize, RTS_GUID *pDataGUID, RTS_UI16 usAreaType)')

/**
 * <description>Function to prepare store retains</description>
 * <param name="pszFile" type="IN">Name of the file to prepare</param>
 * <param name="pszName" type="IN">Name that was assigned to the retain memory</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `RetainPrepareStore', `(char* pszFile, char *pszName)')

#ifdef __cplusplus
}
#endif
