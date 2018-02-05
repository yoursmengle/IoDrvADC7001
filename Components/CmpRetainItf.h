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


	
	
#ifndef _CMPRETAINITF_H_
#define _CMPRETAINITF_H_

#include "CmpStd.h"

 

 





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
RTS_RESULT CDECL RetainAlloc(char *pszName, RTS_GUID *pDataGUID, RetainType rtType, RTS_UI16 usAreaType, RTS_SIZE iSize, int bRestore, RTS_UI8 **ppbyRetain);
typedef RTS_RESULT (CDECL * PFRETAINALLOC) (char *pszName, RTS_GUID *pDataGUID, RetainType rtType, RTS_UI16 usAreaType, RTS_SIZE iSize, int bRestore, RTS_UI8 **ppbyRetain);
#if defined(CMPRETAIN_NOTIMPLEMENTED) || defined(RETAINALLOC_NOTIMPLEMENTED)
	#define USE_RetainAlloc
	#define EXT_RetainAlloc
	#define GET_RetainAlloc(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RetainAlloc(p0,p1,p2,p3,p4,p5,p6)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_RetainAlloc  FALSE
	#define EXP_RetainAlloc  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RetainAlloc
	#define EXT_RetainAlloc
	#define GET_RetainAlloc(fl)  CAL_CMGETAPI( "RetainAlloc" ) 
	#define CAL_RetainAlloc  RetainAlloc
	#define CHK_RetainAlloc  TRUE
	#define EXP_RetainAlloc  CAL_CMEXPAPI( "RetainAlloc" ) 
#elif defined(MIXED_LINK) && !defined(CMPRETAIN_EXTERNAL)
	#define USE_RetainAlloc
	#define EXT_RetainAlloc
	#define GET_RetainAlloc(fl)  CAL_CMGETAPI( "RetainAlloc" ) 
	#define CAL_RetainAlloc  RetainAlloc
	#define CHK_RetainAlloc  TRUE
	#define EXP_RetainAlloc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RetainAlloc", (RTS_UINTPTR)RetainAlloc, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRetainRetainAlloc
	#define EXT_CmpRetainRetainAlloc
	#define GET_CmpRetainRetainAlloc  ERR_OK
	#define CAL_CmpRetainRetainAlloc pICmpRetain->IRetainAlloc
	#define CHK_CmpRetainRetainAlloc (pICmpRetain != NULL)
	#define EXP_CmpRetainRetainAlloc  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RetainAlloc
	#define EXT_RetainAlloc
	#define GET_RetainAlloc(fl)  CAL_CMGETAPI( "RetainAlloc" ) 
	#define CAL_RetainAlloc pICmpRetain->IRetainAlloc
	#define CHK_RetainAlloc (pICmpRetain != NULL)
	#define EXP_RetainAlloc  CAL_CMEXPAPI( "RetainAlloc" ) 
#else /* DYNAMIC_LINK */
	#define USE_RetainAlloc  PFRETAINALLOC pfRetainAlloc;
	#define EXT_RetainAlloc  extern PFRETAINALLOC pfRetainAlloc;
	#define GET_RetainAlloc(fl)  s_pfCMGetAPI2( "RetainAlloc", (RTS_VOID_FCTPTR *)&pfRetainAlloc, (fl), 0, 0)
	#define CAL_RetainAlloc  pfRetainAlloc
	#define CHK_RetainAlloc  (pfRetainAlloc != NULL)
	#define EXP_RetainAlloc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RetainAlloc", (RTS_UINTPTR)RetainAlloc, 0, 0) 
#endif




/**
 * <description>Release the retain memory</description>
 * <param name="pszName" type="IN">Name that was assigned to the retain memory</param>
 * <param name="pbyRetain" type="IN">Pointer of the retain memory to release</param>
 * <param name="nDeleteOption" type="IN">Option to delete retain memory. See "Delete option"</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL RetainFree(char *pszName, RTS_UI8 *pbyRetain, int nDeleteOption);
typedef RTS_RESULT (CDECL * PFRETAINFREE) (char *pszName, RTS_UI8 *pbyRetain, int nDeleteOption);
#if defined(CMPRETAIN_NOTIMPLEMENTED) || defined(RETAINFREE_NOTIMPLEMENTED)
	#define USE_RetainFree
	#define EXT_RetainFree
	#define GET_RetainFree(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RetainFree(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_RetainFree  FALSE
	#define EXP_RetainFree  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RetainFree
	#define EXT_RetainFree
	#define GET_RetainFree(fl)  CAL_CMGETAPI( "RetainFree" ) 
	#define CAL_RetainFree  RetainFree
	#define CHK_RetainFree  TRUE
	#define EXP_RetainFree  CAL_CMEXPAPI( "RetainFree" ) 
#elif defined(MIXED_LINK) && !defined(CMPRETAIN_EXTERNAL)
	#define USE_RetainFree
	#define EXT_RetainFree
	#define GET_RetainFree(fl)  CAL_CMGETAPI( "RetainFree" ) 
	#define CAL_RetainFree  RetainFree
	#define CHK_RetainFree  TRUE
	#define EXP_RetainFree  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RetainFree", (RTS_UINTPTR)RetainFree, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRetainRetainFree
	#define EXT_CmpRetainRetainFree
	#define GET_CmpRetainRetainFree  ERR_OK
	#define CAL_CmpRetainRetainFree pICmpRetain->IRetainFree
	#define CHK_CmpRetainRetainFree (pICmpRetain != NULL)
	#define EXP_CmpRetainRetainFree  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RetainFree
	#define EXT_RetainFree
	#define GET_RetainFree(fl)  CAL_CMGETAPI( "RetainFree" ) 
	#define CAL_RetainFree pICmpRetain->IRetainFree
	#define CHK_RetainFree (pICmpRetain != NULL)
	#define EXP_RetainFree  CAL_CMEXPAPI( "RetainFree" ) 
#else /* DYNAMIC_LINK */
	#define USE_RetainFree  PFRETAINFREE pfRetainFree;
	#define EXT_RetainFree  extern PFRETAINFREE pfRetainFree;
	#define GET_RetainFree(fl)  s_pfCMGetAPI2( "RetainFree", (RTS_VOID_FCTPTR *)&pfRetainFree, (fl), 0, 0)
	#define CAL_RetainFree  pfRetainFree
	#define CHK_RetainFree  (pfRetainFree != NULL)
	#define EXP_RetainFree  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RetainFree", (RTS_UINTPTR)RetainFree, 0, 0) 
#endif




/**
 * <description>Update data GUID in the specified retain area</description>
 * <param name="pszName" type="IN">Name that was assigned to the retain memory</param>
 * <param name="pbyRetain" type="IN">Pointer of the retain memory to release</param>
 * <param name="pDataGuidOld" type="IN">Pointer to old data GUID</param>
 * <param name="pDataGuidNew" type="IN">Pointer to new data GUID</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL RetainUpdateGuid(char *pszName, RTS_UI8 *pbyRetain, RTS_GUID *pDataGuidOld, RTS_GUID *pDataGuidNew);
typedef RTS_RESULT (CDECL * PFRETAINUPDATEGUID) (char *pszName, RTS_UI8 *pbyRetain, RTS_GUID *pDataGuidOld, RTS_GUID *pDataGuidNew);
#if defined(CMPRETAIN_NOTIMPLEMENTED) || defined(RETAINUPDATEGUID_NOTIMPLEMENTED)
	#define USE_RetainUpdateGuid
	#define EXT_RetainUpdateGuid
	#define GET_RetainUpdateGuid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RetainUpdateGuid(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_RetainUpdateGuid  FALSE
	#define EXP_RetainUpdateGuid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RetainUpdateGuid
	#define EXT_RetainUpdateGuid
	#define GET_RetainUpdateGuid(fl)  CAL_CMGETAPI( "RetainUpdateGuid" ) 
	#define CAL_RetainUpdateGuid  RetainUpdateGuid
	#define CHK_RetainUpdateGuid  TRUE
	#define EXP_RetainUpdateGuid  CAL_CMEXPAPI( "RetainUpdateGuid" ) 
#elif defined(MIXED_LINK) && !defined(CMPRETAIN_EXTERNAL)
	#define USE_RetainUpdateGuid
	#define EXT_RetainUpdateGuid
	#define GET_RetainUpdateGuid(fl)  CAL_CMGETAPI( "RetainUpdateGuid" ) 
	#define CAL_RetainUpdateGuid  RetainUpdateGuid
	#define CHK_RetainUpdateGuid  TRUE
	#define EXP_RetainUpdateGuid  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RetainUpdateGuid", (RTS_UINTPTR)RetainUpdateGuid, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRetainRetainUpdateGuid
	#define EXT_CmpRetainRetainUpdateGuid
	#define GET_CmpRetainRetainUpdateGuid  ERR_OK
	#define CAL_CmpRetainRetainUpdateGuid pICmpRetain->IRetainUpdateGuid
	#define CHK_CmpRetainRetainUpdateGuid (pICmpRetain != NULL)
	#define EXP_CmpRetainRetainUpdateGuid  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RetainUpdateGuid
	#define EXT_RetainUpdateGuid
	#define GET_RetainUpdateGuid(fl)  CAL_CMGETAPI( "RetainUpdateGuid" ) 
	#define CAL_RetainUpdateGuid pICmpRetain->IRetainUpdateGuid
	#define CHK_RetainUpdateGuid (pICmpRetain != NULL)
	#define EXP_RetainUpdateGuid  CAL_CMEXPAPI( "RetainUpdateGuid" ) 
#else /* DYNAMIC_LINK */
	#define USE_RetainUpdateGuid  PFRETAINUPDATEGUID pfRetainUpdateGuid;
	#define EXT_RetainUpdateGuid  extern PFRETAINUPDATEGUID pfRetainUpdateGuid;
	#define GET_RetainUpdateGuid(fl)  s_pfCMGetAPI2( "RetainUpdateGuid", (RTS_VOID_FCTPTR *)&pfRetainUpdateGuid, (fl), 0, 0)
	#define CAL_RetainUpdateGuid  pfRetainUpdateGuid
	#define CHK_RetainUpdateGuid  (pfRetainUpdateGuid != NULL)
	#define EXP_RetainUpdateGuid  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RetainUpdateGuid", (RTS_UINTPTR)RetainUpdateGuid, 0, 0) 
#endif




/**
 * <description>Check GUID that is stored in the retain memory</description>
 * <param name="pszName" type="IN">Name that was assigned to the retain memory</param>
 * <param name="pbyRetain" type="IN">Pointer of the retain memory to release</param>
 * <param name="pDataGUID" type="IN">Pointer to data GUID</param>
 * <param name="usAreaType" type="IN">Area type. See category "Area Types" in SysMemItf.h for detailed information</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL RetainCheckGuid(char *pszName, RTS_UI8 *pbyRetain, RTS_GUID *pDataGuid, RTS_UI16 usAreaType);
typedef RTS_RESULT (CDECL * PFRETAINCHECKGUID) (char *pszName, RTS_UI8 *pbyRetain, RTS_GUID *pDataGuid, RTS_UI16 usAreaType);
#if defined(CMPRETAIN_NOTIMPLEMENTED) || defined(RETAINCHECKGUID_NOTIMPLEMENTED)
	#define USE_RetainCheckGuid
	#define EXT_RetainCheckGuid
	#define GET_RetainCheckGuid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RetainCheckGuid(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_RetainCheckGuid  FALSE
	#define EXP_RetainCheckGuid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RetainCheckGuid
	#define EXT_RetainCheckGuid
	#define GET_RetainCheckGuid(fl)  CAL_CMGETAPI( "RetainCheckGuid" ) 
	#define CAL_RetainCheckGuid  RetainCheckGuid
	#define CHK_RetainCheckGuid  TRUE
	#define EXP_RetainCheckGuid  CAL_CMEXPAPI( "RetainCheckGuid" ) 
#elif defined(MIXED_LINK) && !defined(CMPRETAIN_EXTERNAL)
	#define USE_RetainCheckGuid
	#define EXT_RetainCheckGuid
	#define GET_RetainCheckGuid(fl)  CAL_CMGETAPI( "RetainCheckGuid" ) 
	#define CAL_RetainCheckGuid  RetainCheckGuid
	#define CHK_RetainCheckGuid  TRUE
	#define EXP_RetainCheckGuid  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RetainCheckGuid", (RTS_UINTPTR)RetainCheckGuid, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRetainRetainCheckGuid
	#define EXT_CmpRetainRetainCheckGuid
	#define GET_CmpRetainRetainCheckGuid  ERR_OK
	#define CAL_CmpRetainRetainCheckGuid pICmpRetain->IRetainCheckGuid
	#define CHK_CmpRetainRetainCheckGuid (pICmpRetain != NULL)
	#define EXP_CmpRetainRetainCheckGuid  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RetainCheckGuid
	#define EXT_RetainCheckGuid
	#define GET_RetainCheckGuid(fl)  CAL_CMGETAPI( "RetainCheckGuid" ) 
	#define CAL_RetainCheckGuid pICmpRetain->IRetainCheckGuid
	#define CHK_RetainCheckGuid (pICmpRetain != NULL)
	#define EXP_RetainCheckGuid  CAL_CMEXPAPI( "RetainCheckGuid" ) 
#else /* DYNAMIC_LINK */
	#define USE_RetainCheckGuid  PFRETAINCHECKGUID pfRetainCheckGuid;
	#define EXT_RetainCheckGuid  extern PFRETAINCHECKGUID pfRetainCheckGuid;
	#define GET_RetainCheckGuid(fl)  s_pfCMGetAPI2( "RetainCheckGuid", (RTS_VOID_FCTPTR *)&pfRetainCheckGuid, (fl), 0, 0)
	#define CAL_RetainCheckGuid  pfRetainCheckGuid
	#define CHK_RetainCheckGuid  (pfRetainCheckGuid != NULL)
	#define EXP_RetainCheckGuid  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RetainCheckGuid", (RTS_UINTPTR)RetainCheckGuid, 0, 0) 
#endif




/**
 * <description>Update retain management. Can be used to detect all free retain areas after loading all bootprojects</description>
 * <result>error code</result>
 */
RTS_RESULT CDECL RetainUpdate(void);
typedef RTS_RESULT (CDECL * PFRETAINUPDATE) (void);
#if defined(CMPRETAIN_NOTIMPLEMENTED) || defined(RETAINUPDATE_NOTIMPLEMENTED)
	#define USE_RetainUpdate
	#define EXT_RetainUpdate
	#define GET_RetainUpdate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RetainUpdate()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_RetainUpdate  FALSE
	#define EXP_RetainUpdate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RetainUpdate
	#define EXT_RetainUpdate
	#define GET_RetainUpdate(fl)  CAL_CMGETAPI( "RetainUpdate" ) 
	#define CAL_RetainUpdate  RetainUpdate
	#define CHK_RetainUpdate  TRUE
	#define EXP_RetainUpdate  CAL_CMEXPAPI( "RetainUpdate" ) 
#elif defined(MIXED_LINK) && !defined(CMPRETAIN_EXTERNAL)
	#define USE_RetainUpdate
	#define EXT_RetainUpdate
	#define GET_RetainUpdate(fl)  CAL_CMGETAPI( "RetainUpdate" ) 
	#define CAL_RetainUpdate  RetainUpdate
	#define CHK_RetainUpdate  TRUE
	#define EXP_RetainUpdate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RetainUpdate", (RTS_UINTPTR)RetainUpdate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRetainRetainUpdate
	#define EXT_CmpRetainRetainUpdate
	#define GET_CmpRetainRetainUpdate  ERR_OK
	#define CAL_CmpRetainRetainUpdate pICmpRetain->IRetainUpdate
	#define CHK_CmpRetainRetainUpdate (pICmpRetain != NULL)
	#define EXP_CmpRetainRetainUpdate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RetainUpdate
	#define EXT_RetainUpdate
	#define GET_RetainUpdate(fl)  CAL_CMGETAPI( "RetainUpdate" ) 
	#define CAL_RetainUpdate pICmpRetain->IRetainUpdate
	#define CHK_RetainUpdate (pICmpRetain != NULL)
	#define EXP_RetainUpdate  CAL_CMEXPAPI( "RetainUpdate" ) 
#else /* DYNAMIC_LINK */
	#define USE_RetainUpdate  PFRETAINUPDATE pfRetainUpdate;
	#define EXT_RetainUpdate  extern PFRETAINUPDATE pfRetainUpdate;
	#define GET_RetainUpdate(fl)  s_pfCMGetAPI2( "RetainUpdate", (RTS_VOID_FCTPTR *)&pfRetainUpdate, (fl), 0, 0)
	#define CAL_RetainUpdate  pfRetainUpdate
	#define CHK_RetainUpdate  (pfRetainUpdate != NULL)
	#define EXP_RetainUpdate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RetainUpdate", (RTS_UINTPTR)RetainUpdate, 0, 0) 
#endif




/**
 * <description>Function to store retain data. Is used for example to store retains on a harddisk.</description>
 * <param name="pszName" type="IN">Name that was assigned to the retain memory</param>
 * <param name="iSize" type="IN">Requested size of the retain area</param>
 * <param name="pDataGUID" type="IN">Data guid of the retain area</param>
 * <param name="pbyRetain" type="IN">Pointer of the retain memory</param>
 * <param name="bBackup" type="IN">If parameter is 1, then the retain data of the specified area is stored for backup needs</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL RetainStore(char *pszName, RTS_UI8 *pbyRetain, RTS_SIZE iSize, RTS_GUID *pDataGUID, int bBackup);
typedef RTS_RESULT (CDECL * PFRETAINSTORE) (char *pszName, RTS_UI8 *pbyRetain, RTS_SIZE iSize, RTS_GUID *pDataGUID, int bBackup);
#if defined(CMPRETAIN_NOTIMPLEMENTED) || defined(RETAINSTORE_NOTIMPLEMENTED)
	#define USE_RetainStore
	#define EXT_RetainStore
	#define GET_RetainStore(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RetainStore(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_RetainStore  FALSE
	#define EXP_RetainStore  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RetainStore
	#define EXT_RetainStore
	#define GET_RetainStore(fl)  CAL_CMGETAPI( "RetainStore" ) 
	#define CAL_RetainStore  RetainStore
	#define CHK_RetainStore  TRUE
	#define EXP_RetainStore  CAL_CMEXPAPI( "RetainStore" ) 
#elif defined(MIXED_LINK) && !defined(CMPRETAIN_EXTERNAL)
	#define USE_RetainStore
	#define EXT_RetainStore
	#define GET_RetainStore(fl)  CAL_CMGETAPI( "RetainStore" ) 
	#define CAL_RetainStore  RetainStore
	#define CHK_RetainStore  TRUE
	#define EXP_RetainStore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RetainStore", (RTS_UINTPTR)RetainStore, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRetainRetainStore
	#define EXT_CmpRetainRetainStore
	#define GET_CmpRetainRetainStore  ERR_OK
	#define CAL_CmpRetainRetainStore pICmpRetain->IRetainStore
	#define CHK_CmpRetainRetainStore (pICmpRetain != NULL)
	#define EXP_CmpRetainRetainStore  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RetainStore
	#define EXT_RetainStore
	#define GET_RetainStore(fl)  CAL_CMGETAPI( "RetainStore" ) 
	#define CAL_RetainStore pICmpRetain->IRetainStore
	#define CHK_RetainStore (pICmpRetain != NULL)
	#define EXP_RetainStore  CAL_CMEXPAPI( "RetainStore" ) 
#else /* DYNAMIC_LINK */
	#define USE_RetainStore  PFRETAINSTORE pfRetainStore;
	#define EXT_RetainStore  extern PFRETAINSTORE pfRetainStore;
	#define GET_RetainStore(fl)  s_pfCMGetAPI2( "RetainStore", (RTS_VOID_FCTPTR *)&pfRetainStore, (fl), 0, 0)
	#define CAL_RetainStore  pfRetainStore
	#define CHK_RetainStore  (pfRetainStore != NULL)
	#define EXP_RetainStore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RetainStore", (RTS_UINTPTR)RetainStore, 0, 0) 
#endif




/**
 * <description>Function to store retain data. Is used for example to store retains on a harddisk.</description>
 * <param name="pszFile" type="IN">Name of the file to store retains to</param>
 * <param name="pszName" type="IN">Name that was assigned to the retain memory</param>
 * <param name="iSize" type="IN">Requested size of the retain area</param>
 * <param name="pDataGUID" type="IN">Data guid of the retain area</param>
 * <param name="pbyRetain" type="IN">Pointer of the retain memory</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL RetainStoreInFile(char* pszFile, char *pszName, RTS_UI8 *pbyRetain, RTS_SIZE iSize, RTS_GUID *pDataGUID);
typedef RTS_RESULT (CDECL * PFRETAINSTOREINFILE) (char* pszFile, char *pszName, RTS_UI8 *pbyRetain, RTS_SIZE iSize, RTS_GUID *pDataGUID);
#if defined(CMPRETAIN_NOTIMPLEMENTED) || defined(RETAINSTOREINFILE_NOTIMPLEMENTED)
	#define USE_RetainStoreInFile
	#define EXT_RetainStoreInFile
	#define GET_RetainStoreInFile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RetainStoreInFile(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_RetainStoreInFile  FALSE
	#define EXP_RetainStoreInFile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RetainStoreInFile
	#define EXT_RetainStoreInFile
	#define GET_RetainStoreInFile(fl)  CAL_CMGETAPI( "RetainStoreInFile" ) 
	#define CAL_RetainStoreInFile  RetainStoreInFile
	#define CHK_RetainStoreInFile  TRUE
	#define EXP_RetainStoreInFile  CAL_CMEXPAPI( "RetainStoreInFile" ) 
#elif defined(MIXED_LINK) && !defined(CMPRETAIN_EXTERNAL)
	#define USE_RetainStoreInFile
	#define EXT_RetainStoreInFile
	#define GET_RetainStoreInFile(fl)  CAL_CMGETAPI( "RetainStoreInFile" ) 
	#define CAL_RetainStoreInFile  RetainStoreInFile
	#define CHK_RetainStoreInFile  TRUE
	#define EXP_RetainStoreInFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RetainStoreInFile", (RTS_UINTPTR)RetainStoreInFile, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRetainRetainStoreInFile
	#define EXT_CmpRetainRetainStoreInFile
	#define GET_CmpRetainRetainStoreInFile  ERR_OK
	#define CAL_CmpRetainRetainStoreInFile pICmpRetain->IRetainStoreInFile
	#define CHK_CmpRetainRetainStoreInFile (pICmpRetain != NULL)
	#define EXP_CmpRetainRetainStoreInFile  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RetainStoreInFile
	#define EXT_RetainStoreInFile
	#define GET_RetainStoreInFile(fl)  CAL_CMGETAPI( "RetainStoreInFile" ) 
	#define CAL_RetainStoreInFile pICmpRetain->IRetainStoreInFile
	#define CHK_RetainStoreInFile (pICmpRetain != NULL)
	#define EXP_RetainStoreInFile  CAL_CMEXPAPI( "RetainStoreInFile" ) 
#else /* DYNAMIC_LINK */
	#define USE_RetainStoreInFile  PFRETAINSTOREINFILE pfRetainStoreInFile;
	#define EXT_RetainStoreInFile  extern PFRETAINSTOREINFILE pfRetainStoreInFile;
	#define GET_RetainStoreInFile(fl)  s_pfCMGetAPI2( "RetainStoreInFile", (RTS_VOID_FCTPTR *)&pfRetainStoreInFile, (fl), 0, 0)
	#define CAL_RetainStoreInFile  pfRetainStoreInFile
	#define CHK_RetainStoreInFile  (pfRetainStoreInFile != NULL)
	#define EXP_RetainStoreInFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RetainStoreInFile", (RTS_UINTPTR)RetainStoreInFile, 0, 0) 
#endif




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
RTS_RESULT CDECL RetainRestore(char *pszName, RTS_UI8 *pbyRetain, RTS_SIZE iSize, RTS_GUID *pDataGUID, RTS_UI16 usAreaType, int bBackup);
typedef RTS_RESULT (CDECL * PFRETAINRESTORE) (char *pszName, RTS_UI8 *pbyRetain, RTS_SIZE iSize, RTS_GUID *pDataGUID, RTS_UI16 usAreaType, int bBackup);
#if defined(CMPRETAIN_NOTIMPLEMENTED) || defined(RETAINRESTORE_NOTIMPLEMENTED)
	#define USE_RetainRestore
	#define EXT_RetainRestore
	#define GET_RetainRestore(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RetainRestore(p0,p1,p2,p3,p4,p5)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_RetainRestore  FALSE
	#define EXP_RetainRestore  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RetainRestore
	#define EXT_RetainRestore
	#define GET_RetainRestore(fl)  CAL_CMGETAPI( "RetainRestore" ) 
	#define CAL_RetainRestore  RetainRestore
	#define CHK_RetainRestore  TRUE
	#define EXP_RetainRestore  CAL_CMEXPAPI( "RetainRestore" ) 
#elif defined(MIXED_LINK) && !defined(CMPRETAIN_EXTERNAL)
	#define USE_RetainRestore
	#define EXT_RetainRestore
	#define GET_RetainRestore(fl)  CAL_CMGETAPI( "RetainRestore" ) 
	#define CAL_RetainRestore  RetainRestore
	#define CHK_RetainRestore  TRUE
	#define EXP_RetainRestore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RetainRestore", (RTS_UINTPTR)RetainRestore, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRetainRetainRestore
	#define EXT_CmpRetainRetainRestore
	#define GET_CmpRetainRetainRestore  ERR_OK
	#define CAL_CmpRetainRetainRestore pICmpRetain->IRetainRestore
	#define CHK_CmpRetainRetainRestore (pICmpRetain != NULL)
	#define EXP_CmpRetainRetainRestore  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RetainRestore
	#define EXT_RetainRestore
	#define GET_RetainRestore(fl)  CAL_CMGETAPI( "RetainRestore" ) 
	#define CAL_RetainRestore pICmpRetain->IRetainRestore
	#define CHK_RetainRestore (pICmpRetain != NULL)
	#define EXP_RetainRestore  CAL_CMEXPAPI( "RetainRestore" ) 
#else /* DYNAMIC_LINK */
	#define USE_RetainRestore  PFRETAINRESTORE pfRetainRestore;
	#define EXT_RetainRestore  extern PFRETAINRESTORE pfRetainRestore;
	#define GET_RetainRestore(fl)  s_pfCMGetAPI2( "RetainRestore", (RTS_VOID_FCTPTR *)&pfRetainRestore, (fl), 0, 0)
	#define CAL_RetainRestore  pfRetainRestore
	#define CHK_RetainRestore  (pfRetainRestore != NULL)
	#define EXP_RetainRestore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RetainRestore", (RTS_UINTPTR)RetainRestore, 0, 0) 
#endif




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
RTS_RESULT CDECL RetainRestoreFromFile(char* pszFile, char *pszName, RTS_UI8 *pbyRetain, RTS_SIZE iSize, RTS_GUID *pDataGUID, RTS_UI16 usAreaType);
typedef RTS_RESULT (CDECL * PFRETAINRESTOREFROMFILE) (char* pszFile, char *pszName, RTS_UI8 *pbyRetain, RTS_SIZE iSize, RTS_GUID *pDataGUID, RTS_UI16 usAreaType);
#if defined(CMPRETAIN_NOTIMPLEMENTED) || defined(RETAINRESTOREFROMFILE_NOTIMPLEMENTED)
	#define USE_RetainRestoreFromFile
	#define EXT_RetainRestoreFromFile
	#define GET_RetainRestoreFromFile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RetainRestoreFromFile(p0,p1,p2,p3,p4,p5)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_RetainRestoreFromFile  FALSE
	#define EXP_RetainRestoreFromFile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RetainRestoreFromFile
	#define EXT_RetainRestoreFromFile
	#define GET_RetainRestoreFromFile(fl)  CAL_CMGETAPI( "RetainRestoreFromFile" ) 
	#define CAL_RetainRestoreFromFile  RetainRestoreFromFile
	#define CHK_RetainRestoreFromFile  TRUE
	#define EXP_RetainRestoreFromFile  CAL_CMEXPAPI( "RetainRestoreFromFile" ) 
#elif defined(MIXED_LINK) && !defined(CMPRETAIN_EXTERNAL)
	#define USE_RetainRestoreFromFile
	#define EXT_RetainRestoreFromFile
	#define GET_RetainRestoreFromFile(fl)  CAL_CMGETAPI( "RetainRestoreFromFile" ) 
	#define CAL_RetainRestoreFromFile  RetainRestoreFromFile
	#define CHK_RetainRestoreFromFile  TRUE
	#define EXP_RetainRestoreFromFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RetainRestoreFromFile", (RTS_UINTPTR)RetainRestoreFromFile, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRetainRetainRestoreFromFile
	#define EXT_CmpRetainRetainRestoreFromFile
	#define GET_CmpRetainRetainRestoreFromFile  ERR_OK
	#define CAL_CmpRetainRetainRestoreFromFile pICmpRetain->IRetainRestoreFromFile
	#define CHK_CmpRetainRetainRestoreFromFile (pICmpRetain != NULL)
	#define EXP_CmpRetainRetainRestoreFromFile  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RetainRestoreFromFile
	#define EXT_RetainRestoreFromFile
	#define GET_RetainRestoreFromFile(fl)  CAL_CMGETAPI( "RetainRestoreFromFile" ) 
	#define CAL_RetainRestoreFromFile pICmpRetain->IRetainRestoreFromFile
	#define CHK_RetainRestoreFromFile (pICmpRetain != NULL)
	#define EXP_RetainRestoreFromFile  CAL_CMEXPAPI( "RetainRestoreFromFile" ) 
#else /* DYNAMIC_LINK */
	#define USE_RetainRestoreFromFile  PFRETAINRESTOREFROMFILE pfRetainRestoreFromFile;
	#define EXT_RetainRestoreFromFile  extern PFRETAINRESTOREFROMFILE pfRetainRestoreFromFile;
	#define GET_RetainRestoreFromFile(fl)  s_pfCMGetAPI2( "RetainRestoreFromFile", (RTS_VOID_FCTPTR *)&pfRetainRestoreFromFile, (fl), 0, 0)
	#define CAL_RetainRestoreFromFile  pfRetainRestoreFromFile
	#define CHK_RetainRestoreFromFile  (pfRetainRestoreFromFile != NULL)
	#define EXP_RetainRestoreFromFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RetainRestoreFromFile", (RTS_UINTPTR)RetainRestoreFromFile, 0, 0) 
#endif




/**
 * <description>Function to prepare store retains</description>
 * <param name="pszFile" type="IN">Name of the file to prepare</param>
 * <param name="pszName" type="IN">Name that was assigned to the retain memory</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL RetainPrepareStore(char* pszFile, char *pszName);
typedef RTS_RESULT (CDECL * PFRETAINPREPARESTORE) (char* pszFile, char *pszName);
#if defined(CMPRETAIN_NOTIMPLEMENTED) || defined(RETAINPREPARESTORE_NOTIMPLEMENTED)
	#define USE_RetainPrepareStore
	#define EXT_RetainPrepareStore
	#define GET_RetainPrepareStore(fl)  ERR_NOTIMPLEMENTED
	#define CAL_RetainPrepareStore(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_RetainPrepareStore  FALSE
	#define EXP_RetainPrepareStore  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_RetainPrepareStore
	#define EXT_RetainPrepareStore
	#define GET_RetainPrepareStore(fl)  CAL_CMGETAPI( "RetainPrepareStore" ) 
	#define CAL_RetainPrepareStore  RetainPrepareStore
	#define CHK_RetainPrepareStore  TRUE
	#define EXP_RetainPrepareStore  CAL_CMEXPAPI( "RetainPrepareStore" ) 
#elif defined(MIXED_LINK) && !defined(CMPRETAIN_EXTERNAL)
	#define USE_RetainPrepareStore
	#define EXT_RetainPrepareStore
	#define GET_RetainPrepareStore(fl)  CAL_CMGETAPI( "RetainPrepareStore" ) 
	#define CAL_RetainPrepareStore  RetainPrepareStore
	#define CHK_RetainPrepareStore  TRUE
	#define EXP_RetainPrepareStore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RetainPrepareStore", (RTS_UINTPTR)RetainPrepareStore, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpRetainRetainPrepareStore
	#define EXT_CmpRetainRetainPrepareStore
	#define GET_CmpRetainRetainPrepareStore  ERR_OK
	#define CAL_CmpRetainRetainPrepareStore pICmpRetain->IRetainPrepareStore
	#define CHK_CmpRetainRetainPrepareStore (pICmpRetain != NULL)
	#define EXP_CmpRetainRetainPrepareStore  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_RetainPrepareStore
	#define EXT_RetainPrepareStore
	#define GET_RetainPrepareStore(fl)  CAL_CMGETAPI( "RetainPrepareStore" ) 
	#define CAL_RetainPrepareStore pICmpRetain->IRetainPrepareStore
	#define CHK_RetainPrepareStore (pICmpRetain != NULL)
	#define EXP_RetainPrepareStore  CAL_CMEXPAPI( "RetainPrepareStore" ) 
#else /* DYNAMIC_LINK */
	#define USE_RetainPrepareStore  PFRETAINPREPARESTORE pfRetainPrepareStore;
	#define EXT_RetainPrepareStore  extern PFRETAINPREPARESTORE pfRetainPrepareStore;
	#define GET_RetainPrepareStore(fl)  s_pfCMGetAPI2( "RetainPrepareStore", (RTS_VOID_FCTPTR *)&pfRetainPrepareStore, (fl), 0, 0)
	#define CAL_RetainPrepareStore  pfRetainPrepareStore
	#define CHK_RetainPrepareStore  (pfRetainPrepareStore != NULL)
	#define EXP_RetainPrepareStore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"RetainPrepareStore", (RTS_UINTPTR)RetainPrepareStore, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFRETAINALLOC IRetainAlloc;
 	PFRETAINFREE IRetainFree;
 	PFRETAINUPDATEGUID IRetainUpdateGuid;
 	PFRETAINCHECKGUID IRetainCheckGuid;
 	PFRETAINUPDATE IRetainUpdate;
 	PFRETAINSTORE IRetainStore;
 	PFRETAINSTOREINFILE IRetainStoreInFile;
 	PFRETAINRESTORE IRetainRestore;
 	PFRETAINRESTOREFROMFILE IRetainRestoreFromFile;
 	PFRETAINPREPARESTORE IRetainPrepareStore;
 } ICmpRetain_C;

#ifdef CPLUSPLUS
class ICmpRetain : public IBase
{
	public:
		virtual RTS_RESULT CDECL IRetainAlloc(char *pszName, RTS_GUID *pDataGUID, RetainType rtType, RTS_UI16 usAreaType, RTS_SIZE iSize, int bRestore, RTS_UI8 **ppbyRetain) =0;
		virtual RTS_RESULT CDECL IRetainFree(char *pszName, RTS_UI8 *pbyRetain, int nDeleteOption) =0;
		virtual RTS_RESULT CDECL IRetainUpdateGuid(char *pszName, RTS_UI8 *pbyRetain, RTS_GUID *pDataGuidOld, RTS_GUID *pDataGuidNew) =0;
		virtual RTS_RESULT CDECL IRetainCheckGuid(char *pszName, RTS_UI8 *pbyRetain, RTS_GUID *pDataGuid, RTS_UI16 usAreaType) =0;
		virtual RTS_RESULT CDECL IRetainUpdate(void) =0;
		virtual RTS_RESULT CDECL IRetainStore(char *pszName, RTS_UI8 *pbyRetain, RTS_SIZE iSize, RTS_GUID *pDataGUID, int bBackup) =0;
		virtual RTS_RESULT CDECL IRetainStoreInFile(char* pszFile, char *pszName, RTS_UI8 *pbyRetain, RTS_SIZE iSize, RTS_GUID *pDataGUID) =0;
		virtual RTS_RESULT CDECL IRetainRestore(char *pszName, RTS_UI8 *pbyRetain, RTS_SIZE iSize, RTS_GUID *pDataGUID, RTS_UI16 usAreaType, int bBackup) =0;
		virtual RTS_RESULT CDECL IRetainRestoreFromFile(char* pszFile, char *pszName, RTS_UI8 *pbyRetain, RTS_SIZE iSize, RTS_GUID *pDataGUID, RTS_UI16 usAreaType) =0;
		virtual RTS_RESULT CDECL IRetainPrepareStore(char* pszFile, char *pszName) =0;
};
	#ifndef ITF_CmpRetain
		#define ITF_CmpRetain static ICmpRetain *pICmpRetain = NULL;
	#endif
	#define EXTITF_CmpRetain
#else	/*CPLUSPLUS*/
	typedef ICmpRetain_C		ICmpRetain;
	#ifndef ITF_CmpRetain
		#define ITF_CmpRetain
	#endif
	#define EXTITF_CmpRetain
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPRETAINITF_H_*/
