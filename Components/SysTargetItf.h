 /**
 * <interfacename>SysTarget</interfacename>
 * <description> 
 *	<p>The SysTarget interface is projected to get access to target specific informations. With this informations
 *	a target can be recognized unique in the complete network.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSTARGETITF_H_
#define _SYSTARGETITF_H_

#include "CmpStd.h"

 

 




#include "CMItf.h"
#include "CmpIoDrvItf.h"

/**
 * <category>Max node name length</category>
 * <description>
 * Specifies the max. number of 16-bit code units allowed for the UTF-16 node name including NULL termination.
 * A single character may consist of 1 or more 16-bit code units.
 * </description>
 */
#define SYSTARGET_MAX_NODE_NAME_LEN 		50

/**
 * <category>Max device name length</category>
 * <description>
 * Specifies the max. number of 16-bit code units allowed for the UTF-16 device name including NULL termination.
 * A single character may consist of 1 or more 16-bit code units.
 * </description>
 */
#define SYSTARGET_MAX_DEVICE_NAME_LEN 		100

 /**
 * <category>Max vendor name length</category>
 * <description>
 * Specifies the max. number of 16-bit code units allowed for the UTF-16 vendor name including NULL termination.
 * A single character may consist of 1 or more 16-bit code units.
 * </description>
 */
#define SYSTARGET_MAX_VENDOR_NAME_LEN 		100

 /**
 * <category>Max serial number length</category>
 * <description>Specifies the max. number of (char) characters allowed for the serial number including NULL termination.</description>
 */
#define SYSTARGET_MAX_SERIAL_NUMBER_LEN 	65

/**
 * <category>Operating System ID</category>
 * <description>Specifies which operating system is used. With these defines, operating system specific code can be managed.</description>
 *	<element name="SYSTARGET_OS_NONE" type="IN">No operating system or proprietary used</element>
 *	<element name="SYSTARGET_OS_WINDOWS" type="IN">Windows operating system (user mode)</element>
 *	<element name="SYSTARGET_OS_WINDOWS_RTE" type="IN">Windows operating system (RTE)</element>
 *	<element name="SYSTARGET_OS_WINDOWS_CE" type="IN">Windows CE operating system</element>
 *	<element name="SYSTARGET_OS_LINUX" type="IN">Linux operating system</element>
 *	<element name="SYSTARGET_OS_VXWORKS" type="IN">VxWorks operating system</element>
 *	<element name="SYSTARGET_OS_QNX" type="IN">QNX operating system</element>
 *	<element name="SYSTARGET_OS_UCOS" type="IN">UCOS operating system</element>
 */
#ifdef SYSTARGET_OS_NONE
	#define SYSTARGET_OS_ID					1
#endif
#ifdef SYSTARGET_OS_WINDOWS
	#define SYSTARGET_OS_ID					2
#endif
#ifdef SYSTARGET_OS_WINDOWS_RTE
	#define SYSTARGET_OS_ID					3
#endif
#ifdef SYSTARGET_OS_WINDOWS_CE
	#define SYSTARGET_OS_ID					4
#endif
#ifdef SYSTARGET_OS_LINUX
	#define SYSTARGET_OS_ID					5
#endif
#ifdef SYSTARGET_OS_VXWORKS
	#define SYSTARGET_OS_ID					6
#endif
#ifdef SYSTARGET_OS_QNX
	#define SYSTARGET_OS_ID					7
#endif
#ifdef SYSTARGET_OS_UCOS
	#define SYSTARGET_OS_ID					8
#endif

/**
 * <category>Compiler switch</category>
 * <description>
 *	Compiler switches to select the processor width.
 * </description>
 * <element name="TRG_16BIT">16 Bit platform</element>
 * <element name="TRG_32BIT">32 Bit platform</element>
 * <element name="TRG_64BIT">64 Bit platform</element>
 */


/**
 * <category>Processor ID</category>
 * <description>Specifies which processor is used. With these defines, processor specific code can be managed.</description>
 *	<element name="TRG_X86" type="IN">80x86 processor used</element>
 *	<element name="TRG_ARM" type="IN">ARM processor used</element>
 *	<element name="TRG_PPC" type="IN">PowerPC processor used</element>
 *	<element name="TRG_MIPS" type="IN">MIPS processor used</element>
 *	<element name="TRG_SH" type="IN">Hitachi SH processor used</element>
 *	<element name="TRG_BLACKFIN" type="IN">BlackFin processor used</element>
 *	<element name="TRG_TRICORE" type="IN">Infineon TriCore processor used</element>
 *	<element name="TRG_NIOS" type="IN">Altera NIOS processor used</element>
 *	<element name="TRG_C16X" type="IN">Infineon C16x processor used</element>
 *	<element name="TRG_CORTEX" type="IN">Cortex processor used</element>
 *	<element name="TRG_DSP" type="IN">DSP used</element>
 *	<element name="TRG_V850" type="IN">Renesas V850 processor used</element>
 *	<element name="TRG_RX6" type="IN">Renesas RX6 processor used</element>
 *	<element name="TRG_COLDFIRE" type="IN">Freescale Coldfire processor used</element>
 */
#ifdef TRG_X86
	#define SYSTARGET_CPU_ID				1
#endif
#ifdef TRG_ARM
	#define SYSTARGET_CPU_ID				2
#endif
#ifdef TRG_PPC
	#define SYSTARGET_CPU_ID				3
#endif
#ifdef TRG_MIPS
	#define SYSTARGET_CPU_ID				4
#endif
#ifdef TRG_SH
	#define SYSTARGET_CPU_ID				5
#endif
#ifdef TRG_BLACKFIN
	#define SYSTARGET_CPU_ID				6
#endif
#ifdef TRG_TRICORE
	#define SYSTARGET_CPU_ID				7
#endif
#ifdef TRG_NIOS
	#define SYSTARGET_CPU_ID				8
#endif
#ifdef TRG_C16X
	#define SYSTARGET_CPU_ID				9
#endif
#ifdef TRG_CORTEX
	#define SYSTARGET_CPU_ID				10
#endif
#ifdef TRG_DSP
	#define SYSTARGET_CPU_ID				11
#endif
#ifdef TRG_V850
	#define SYSTARGET_CPU_ID				12
#endif
#ifdef TRG_RX6
	#define SYSTARGET_CPU_ID				13
#endif
#ifdef TRG_COLDFIRE
	#define SYSTARGET_CPU_ID				14
#endif



/**
 * <category>Device ID</category>
 * <description>Specifies the DeviceID for the runtime system. The DeviceID in combination with the VendorID gets a unique device identification ID.</description>
 */
#ifndef SYSTARGET_DEVICE_ID
	#error SYSTARGET_DEVICE_ID must be defined. Can be requested at 3S.
#endif

/**
 * <category>DeviceID mask</category>
 * <description>Specifices, which parts of the DeviceID are checked in the signature. So a range of devices can use the same signature.</description>
 */
#ifndef SYSTARGET_DEVICE_MASK
	#define SYSTARGET_DEVICE_MASK			0x0000
#endif

/**
 * <category>Vendor ID</category>
 * <description>Specifies the VendorID for the runtime system. The DeviceID in combination with the VendorID gets a unique device identification ID.</description>
 */
#ifndef SYSTARGET_VENDOR_ID
	#error SYSTARGET_VENDOR_ID must be defined. Can be requested at 3S.
#endif

/**
 * <category>Device Type</category>
 * <description>Specifies the device type of the runtime system.</description>
 */
#ifndef SYSTARGET_DEVICE_TYPE
	#error SYSTARGET_DEVICE_TYPE must be defined. See category "Device Types".
#endif

/**
 * <category>Target signature</category>
 * <description>With DeviceID, VendorID, Type, OperatingSystemID and ProcessorID a unique signature is generated to be safe against modifications.</description>
 */
#ifndef SYSTARGET_SIGNATUREID
	#error SYSTARGET_SIGNATUREID must be defined. Can be requested at 3S.
#endif


/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting to get the target name.
 *	Router name could be used as prefix to specify router specific target informations, e.g.:
 *	Router2.NodeName="CoDeSysControl Win"
 * </description>
 */
#define SYSTARGETKEY_STRING_GET_NODENAME			"NodeName"

/**
 * <category>Settings</category>
 * <type>WString</type>
 * <description>Setting to get the target name in UTF-16.
 *	Router name could be used as prefix to specify router specific target informations, e.g.:
 *	Router2.NodeNameUnicode="C\00o\00D\00e\00S\00y\00s\00S\00P\00 \00W\00i\00n\00"
 * </description>
 */
#define SYSTARGETKEY_WSTRING_GET_NODENAME_UNICODE	"NodeNameUnicode"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to get the target version. Router name optional as prefix separated by a '.'</description>
 */
#define SYSTARGETKEY_INT_GET_VERSION				"TargetVersion"

/**
 * <category>Settings</category>
 * <type>WString</type>
 * <description>Setting to get the device name in UTF-16.
 *	Router name could be used as prefix to specify router specific target informations.
 * </description>
 */
#define SYSTARGETKEY_WSTRING_GET_DEVICENAME_UNICODE	"DeviceNameUnicode"

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting to get the device name.
 *	Router name could be used as prefix to specify router specific target informations.
 * </description>
 */
#define SYSTARGETKEY_STRING_GET_DEVICENAME	"DeviceName"

/**
 * <category>Settings</category>
 * <type>WString</type>
 * <description>Setting to get the vendor name in UTF-16.
 *	Router name could be used as prefix to specify router specific target informations.
 * </description>
 */
#define SYSTARGETKEY_WSTRING_GET_VENDORNAME_UNICODE	"VendorNameUnicode"

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting to get the vendor name.
 *	Router name could be used as prefix to specify router specific target informations.
 * </description>
 */
#define SYSTARGETKEY_STRING_GET_VENDORNAME		"VendorName"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to specify a mask to check the target version for compatibility with the device description.
 *	In the mask only the significant digits are checked.
 *
 *	Example:
 *	TargetVersionMask = 0xFFFF0000
 *
 *	1.	devdesc = 3.5.1.0 (0x03050100)
 *		target  = 3.5.2.0 (0x03050200)
 *		-> Identifications compatible
 *
 *	2.	devdesc = 3.4.3.0 (0x03040300)
 *		target  = 3.5.2.0 (0x03050200)
 *		-> Identifications _not_ compatible
 *
 * </description>
 */
#define SYSTARGETKEY_INT_TARGET_VERSION_MASK						"TargetVersionMask"
#ifndef SYSTARGETVALUE_INT_TARGET_VERSION_MASK_DEFAULT
	#ifdef DEVVALUE_INT_TARGET_VERSION_MASK_DEFAULT
		#define SYSTARGETVALUE_INT_TARGET_VERSION_MASK_DEFAULT		DEVVALUE_INT_TARGET_VERSION_MASK_DEFAULT
	#else
		#define SYSTARGETVALUE_INT_TARGET_VERSION_MASK_DEFAULT		INT32_C(0xFFFF0000) 
	#endif
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to specify a compatibility mask to check the target version for compatibility with the device description.
 *  A device description that is lower or equal the target version is accepted. A higher device description version
 *	is denied.
 *
 *	Example:
 *	TargetVersionMask			   = 0xFFFF0000
 *	TargetVersionCompatibilityMask = 0xFFFFFF00
 *
 *	1.	devdesc = 3.5.1.0 (0x03050100)
 *		target  = 3.5.2.0 (0x03050200)
 *		-> Identifications compatible
 *
 *	2.	devdesc = 3.5.3.0 (0x03050300)
 *		target  = 3.5.2.0 (0x03050200)
 *		-> Identifications _not_ compatible
 *
 *	3.	devdesc = 3.4.3.0 (0x03040300)
 *		target  = 3.5.2.0 (0x03050200)
 *		-> Identifications _not_ compatible
 *
 * </description>
 */
#define SYSTARGETKEY_INT_TARGET_VERSION_COMPATIBILITY_MASK						"TargetVersionCompatibilityMask"
#ifndef SYSTARGETVALUE_INT_TARGET_VERSION_COMPATIBILITY_MASK_DEFAULT
	#ifdef DEVKEY_INT_TARGET_VERSION_COMPATIBILITY_MASK
		#define SYSTARGETVALUE_INT_TARGET_VERSION_COMPATIBILITY_MASK_DEFAULT	DEVKEY_INT_TARGET_VERSION_COMPATIBILITY_MASK
	#else
		#define SYSTARGETVALUE_INT_TARGET_VERSION_COMPATIBILITY_MASK_DEFAULT	INT32_C(0xFFFFFF00)
	#endif
#endif


/**
 * <category>Device Types</category>
 * <description>Special device with unregistered slots</description>
 */
#define SYSTARGET_TYPE_SPECIAL_UNREGISTERED_SLOT	0x0000

/**
 * <category>Device Types</category>
 * <description>Programmable device</description>
 */
 #define SYSTARGET_TYPE_PROGRAMMABLE				0x1000
 
/**
 * <category>Device Types</category>
 * <description>3S special device (e.g. OfflineVisuClient)</description>
 */
#define SYSTARGET_TYPE_3S_SPECIAL_DEVICE			0x1001
 
/**
 * <category>Device Types</category>
 * <description>Safety device</description>
 */
#define SYSTARGET_TYPE_SAFETY_DEVICE				0x1002

 /**
 * <category>Device Types</category>
 * <description>Drive device</description>
 */
#define SYSTARGET_TYPE_DRIVE						0x1003
 
/**
 * <category>Device Types</category>
 * <description>Parametrizable device</description>
 */
#define SYSTARGET_TYPE_PARAMETRIZABLE				0x1004

/**
 * <category>Device Types</category>
 * <description>Pure HMI device</description>
 */
#define SYSTARGET_TYPE_HMI							0x1005
 
/**
 * <category>Device Types</category>
 * <description>3S SoftMotion device</description>
 */
#define SYSTARGET_TYPE_3S_SOFTMOTION				0x1006 
 
/**
 * <category>Device Types</category>
 * <description>Communication device (e.g. CODESYS Gateway")</description>
 *
 */
#define SYSTARGET_TYPE_COMMUNICATION				0x1007
 
/**
 * <category>Device Types</category>
 * <description>Remote targetvisu device</description>
 *
 */
#define SYSTARGET_TYPE_REMOTETARGETVISU				0x1008

 /**
 * <category>Event parameter</category>
 * <element name="pwszName" type="IN">New node name to be set</element>
 * <element name="rResult" type="OUT">Result, see description of event EVTPARAM_SysEvent_SetNodeName for more details.</element>
 *	<ul>
 *		<li>ERR_OK: Event is not handled. SysTargetSetNodeName() will store the name in the settings</li>
 *		<li>ERR_NOTHING_TO_DO: The event handler has already stored the new node name somewhere.</li>
 *		<li>ERR_OPERATION_DENIED: The event handler denies to set the new node name.</li>
 *		<li>ERR_NOT_SUPPORTED: Device does not support to store the node name.</li>
 *	</ul>
 */
typedef struct
{
	RTS_WCHAR* pwszName;
	RTS_RESULT rResult;
} EVTPARAM_SysEvent_SetNodeName;
#define EVTPARAMID_SysTarget_SetNodeName	0x0001
#define EVTVERSION_SysTarget_SetNodeName	0x0001

/**
* <category>Events</category>
* <description>Event is sent in function SysTargetSetNodeName() before the new node 
* name is stored in the settings. The following results can be returned by the event:
* - ERR_OK: Event is not handled. SysTargetSetNodeName() will store the name in the
*   settings.
* - ERR_NOTHING_TO_DO: The event handler has already stored the new node name somewhere, 
*   thus SysTargetSetNodeName() shall not store the name. A later call to the OEM-specific
*   implementation of SysTargetGetNodeName() will return the new node name.
* - ERR_OPERATION_DENIED: The event handler denies to set the new node name. 
*   SysTargetSetNodeName() shall not store the name.
* - ERR_NOT_SUPPORTED: Device does not support to store the node name. 
*   SysTargetSetNodeName() shall not store the name.
* </description>
* <param name="pEventParam" type="IN">EVTPARAM_SysEvent_SetNodeName</param>
*/
#define EVT_SysTarget_SetNodeName			MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>SysTarget identification</category>
 * <description>
 *	These values identifies a target completely unique!
 * </description>
 *	<element name="ulTargetType" type="IN">Target type. See category "Device Types"</element>
 *	<element name="ulTargetId" type="IN">ID: HiWord = VendorID, LowWord = ID</element>
 *	<element name="ulTargetVersion" type="IN">Version of the target</element>
 */
typedef struct SysTargetIdent_
{
	RTS_UI32 ulTargetType;
	RTS_UI32 ulTargetId;
	RTS_UI32 ulTargetVersion;
} SysTargetIdent;


/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Returns the device name of the target.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystargetgetdevicename_struct
{
	RTS_IEC_WSTRING *pwszName;			/* VAR_INPUT */	/* <param name="pwszName" type="OUT">Pointer to the device name</param> */
	RTS_IEC_UDINT *pnMaxLength;			/* VAR_INPUT */	/* <param name="nMaxLength" type="IN">Max length of the name</param> */
	RTS_IEC_RESULT SysTargetGetDeviceName;	/* VAR_OUTPUT */	
} systargetgetdevicename_struct;

void CDECL CDECL_EXT systargetgetdevicename(systargetgetdevicename_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTARGETGETDEVICENAME_IEC) (systargetgetdevicename_struct *p);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETDEVICENAME_NOTIMPLEMENTED)
	#define USE_systargetgetdevicename
	#define EXT_systargetgetdevicename
	#define GET_systargetgetdevicename(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systargetgetdevicename(p0) 
	#define CHK_systargetgetdevicename  FALSE
	#define EXP_systargetgetdevicename  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systargetgetdevicename
	#define EXT_systargetgetdevicename
	#define GET_systargetgetdevicename(fl)  CAL_CMGETAPI( "systargetgetdevicename" ) 
	#define CAL_systargetgetdevicename  systargetgetdevicename
	#define CHK_systargetgetdevicename  TRUE
	#define EXP_systargetgetdevicename  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetdevicename", (RTS_UINTPTR)systargetgetdevicename, 1, 0x2DEFEA3D, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_systargetgetdevicename
	#define EXT_systargetgetdevicename
	#define GET_systargetgetdevicename(fl)  CAL_CMGETAPI( "systargetgetdevicename" ) 
	#define CAL_systargetgetdevicename  systargetgetdevicename
	#define CHK_systargetgetdevicename  TRUE
	#define EXP_systargetgetdevicename  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetdevicename", (RTS_UINTPTR)systargetgetdevicename, 1, 0x2DEFEA3D, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetsystargetgetdevicename
	#define EXT_SysTargetsystargetgetdevicename
	#define GET_SysTargetsystargetgetdevicename  ERR_OK
	#define CAL_SysTargetsystargetgetdevicename  systargetgetdevicename
	#define CHK_SysTargetsystargetgetdevicename  TRUE
	#define EXP_SysTargetsystargetgetdevicename  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetdevicename", (RTS_UINTPTR)systargetgetdevicename, 1, 0x2DEFEA3D, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systargetgetdevicename
	#define EXT_systargetgetdevicename
	#define GET_systargetgetdevicename(fl)  CAL_CMGETAPI( "systargetgetdevicename" ) 
	#define CAL_systargetgetdevicename  systargetgetdevicename
	#define CHK_systargetgetdevicename  TRUE
	#define EXP_systargetgetdevicename  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetdevicename", (RTS_UINTPTR)systargetgetdevicename, 1, 0x2DEFEA3D, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systargetgetdevicename  PFSYSTARGETGETDEVICENAME_IEC pfsystargetgetdevicename;
	#define EXT_systargetgetdevicename  extern PFSYSTARGETGETDEVICENAME_IEC pfsystargetgetdevicename;
	#define GET_systargetgetdevicename(fl)  s_pfCMGetAPI2( "systargetgetdevicename", (RTS_VOID_FCTPTR *)&pfsystargetgetdevicename, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x2DEFEA3D, 0x03050500)
	#define CAL_systargetgetdevicename  pfsystargetgetdevicename
	#define CHK_systargetgetdevicename  (pfsystargetgetdevicename != NULL)
	#define EXP_systargetgetdevicename   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetdevicename", (RTS_UINTPTR)systargetgetdevicename, 1, 0x2DEFEA3D, 0x03050500) 
#endif


/**
 * *OBSOLETE*: Only for backward compatibility! Should not be used. 
 */
typedef struct tagsystargetgetdevicename2_struct
{
	RTS_IEC_STRING *pszRouterName;		/* VAR_INPUT */	
	RTS_IEC_WSTRING *pwszName;			/* VAR_INPUT */	
	RTS_IEC_UDINT *pnMaxLength;			/* VAR_INPUT */	
	RTS_IEC_RESULT SysTargetGetDeviceName2;	/* VAR_OUTPUT */	
} systargetgetdevicename2_struct;

void CDECL CDECL_EXT systargetgetdevicename2(systargetgetdevicename2_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTARGETGETDEVICENAME2_IEC) (systargetgetdevicename2_struct *p);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETDEVICENAME2_NOTIMPLEMENTED)
	#define USE_systargetgetdevicename2
	#define EXT_systargetgetdevicename2
	#define GET_systargetgetdevicename2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systargetgetdevicename2(p0) 
	#define CHK_systargetgetdevicename2  FALSE
	#define EXP_systargetgetdevicename2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systargetgetdevicename2
	#define EXT_systargetgetdevicename2
	#define GET_systargetgetdevicename2(fl)  CAL_CMGETAPI( "systargetgetdevicename2" ) 
	#define CAL_systargetgetdevicename2  systargetgetdevicename2
	#define CHK_systargetgetdevicename2  TRUE
	#define EXP_systargetgetdevicename2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetdevicename2", (RTS_UINTPTR)systargetgetdevicename2, 1, 0x332F9AF1, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_systargetgetdevicename2
	#define EXT_systargetgetdevicename2
	#define GET_systargetgetdevicename2(fl)  CAL_CMGETAPI( "systargetgetdevicename2" ) 
	#define CAL_systargetgetdevicename2  systargetgetdevicename2
	#define CHK_systargetgetdevicename2  TRUE
	#define EXP_systargetgetdevicename2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetdevicename2", (RTS_UINTPTR)systargetgetdevicename2, 1, 0x332F9AF1, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetsystargetgetdevicename2
	#define EXT_SysTargetsystargetgetdevicename2
	#define GET_SysTargetsystargetgetdevicename2  ERR_OK
	#define CAL_SysTargetsystargetgetdevicename2  systargetgetdevicename2
	#define CHK_SysTargetsystargetgetdevicename2  TRUE
	#define EXP_SysTargetsystargetgetdevicename2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetdevicename2", (RTS_UINTPTR)systargetgetdevicename2, 1, 0x332F9AF1, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systargetgetdevicename2
	#define EXT_systargetgetdevicename2
	#define GET_systargetgetdevicename2(fl)  CAL_CMGETAPI( "systargetgetdevicename2" ) 
	#define CAL_systargetgetdevicename2  systargetgetdevicename2
	#define CHK_systargetgetdevicename2  TRUE
	#define EXP_systargetgetdevicename2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetdevicename2", (RTS_UINTPTR)systargetgetdevicename2, 1, 0x332F9AF1, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systargetgetdevicename2  PFSYSTARGETGETDEVICENAME2_IEC pfsystargetgetdevicename2;
	#define EXT_systargetgetdevicename2  extern PFSYSTARGETGETDEVICENAME2_IEC pfsystargetgetdevicename2;
	#define GET_systargetgetdevicename2(fl)  s_pfCMGetAPI2( "systargetgetdevicename2", (RTS_VOID_FCTPTR *)&pfsystargetgetdevicename2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x332F9AF1, 0x03050500)
	#define CAL_systargetgetdevicename2  pfsystargetgetdevicename2
	#define CHK_systargetgetdevicename2  (pfsystargetgetdevicename2 != NULL)
	#define EXP_systargetgetdevicename2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetdevicename2", (RTS_UINTPTR)systargetgetdevicename2, 1, 0x332F9AF1, 0x03050500) 
#endif


/**
 * <description>Returns the TargetId.
 *	NOTE: Highword of the TargetId is the VendorId! The VendorId is managed by 3S.
 * </description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystargetgetid_struct
{
	RTS_IEC_DWORD *pulTargetId;			/* VAR_INPUT */	/* <param name="pulTargetId" type="OUT">Pointer to the TargetId</param> */
	RTS_IEC_RESULT SysTargetGetId;		/* VAR_OUTPUT */	
} systargetgetid_struct;

void CDECL CDECL_EXT systargetgetid(systargetgetid_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTARGETGETID_IEC) (systargetgetid_struct *p);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETID_NOTIMPLEMENTED)
	#define USE_systargetgetid
	#define EXT_systargetgetid
	#define GET_systargetgetid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systargetgetid(p0) 
	#define CHK_systargetgetid  FALSE
	#define EXP_systargetgetid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systargetgetid
	#define EXT_systargetgetid
	#define GET_systargetgetid(fl)  CAL_CMGETAPI( "systargetgetid" ) 
	#define CAL_systargetgetid  systargetgetid
	#define CHK_systargetgetid  TRUE
	#define EXP_systargetgetid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetid", (RTS_UINTPTR)systargetgetid, 1, 0x02ED027A, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_systargetgetid
	#define EXT_systargetgetid
	#define GET_systargetgetid(fl)  CAL_CMGETAPI( "systargetgetid" ) 
	#define CAL_systargetgetid  systargetgetid
	#define CHK_systargetgetid  TRUE
	#define EXP_systargetgetid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetid", (RTS_UINTPTR)systargetgetid, 1, 0x02ED027A, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetsystargetgetid
	#define EXT_SysTargetsystargetgetid
	#define GET_SysTargetsystargetgetid  ERR_OK
	#define CAL_SysTargetsystargetgetid  systargetgetid
	#define CHK_SysTargetsystargetgetid  TRUE
	#define EXP_SysTargetsystargetgetid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetid", (RTS_UINTPTR)systargetgetid, 1, 0x02ED027A, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systargetgetid
	#define EXT_systargetgetid
	#define GET_systargetgetid(fl)  CAL_CMGETAPI( "systargetgetid" ) 
	#define CAL_systargetgetid  systargetgetid
	#define CHK_systargetgetid  TRUE
	#define EXP_systargetgetid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetid", (RTS_UINTPTR)systargetgetid, 1, 0x02ED027A, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systargetgetid  PFSYSTARGETGETID_IEC pfsystargetgetid;
	#define EXT_systargetgetid  extern PFSYSTARGETGETID_IEC pfsystargetgetid;
	#define GET_systargetgetid(fl)  s_pfCMGetAPI2( "systargetgetid", (RTS_VOID_FCTPTR *)&pfsystargetgetid, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x02ED027A, 0x03050500)
	#define CAL_systargetgetid  pfsystargetgetid
	#define CHK_systargetgetid  (pfsystargetgetid != NULL)
	#define EXP_systargetgetid   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetid", (RTS_UINTPTR)systargetgetid, 1, 0x02ED027A, 0x03050500) 
#endif


/**
 * *OBSOLETE*: Only for backward compatibility! Should not be used.
 */
typedef struct tagsystargetgetid2_struct
{
	RTS_IEC_STRING *pszRouterName;		/* VAR_INPUT */	
	RTS_IEC_DWORD *pulTargetId;			/* VAR_INPUT */	
	RTS_IEC_RESULT SysTargetGetId2;		/* VAR_OUTPUT */	
} systargetgetid2_struct;

void CDECL CDECL_EXT systargetgetid2(systargetgetid2_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTARGETGETID2_IEC) (systargetgetid2_struct *p);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETID2_NOTIMPLEMENTED)
	#define USE_systargetgetid2
	#define EXT_systargetgetid2
	#define GET_systargetgetid2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systargetgetid2(p0) 
	#define CHK_systargetgetid2  FALSE
	#define EXP_systargetgetid2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systargetgetid2
	#define EXT_systargetgetid2
	#define GET_systargetgetid2(fl)  CAL_CMGETAPI( "systargetgetid2" ) 
	#define CAL_systargetgetid2  systargetgetid2
	#define CHK_systargetgetid2  TRUE
	#define EXP_systargetgetid2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetid2", (RTS_UINTPTR)systargetgetid2, 1, 0xEA1E39C4, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_systargetgetid2
	#define EXT_systargetgetid2
	#define GET_systargetgetid2(fl)  CAL_CMGETAPI( "systargetgetid2" ) 
	#define CAL_systargetgetid2  systargetgetid2
	#define CHK_systargetgetid2  TRUE
	#define EXP_systargetgetid2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetid2", (RTS_UINTPTR)systargetgetid2, 1, 0xEA1E39C4, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetsystargetgetid2
	#define EXT_SysTargetsystargetgetid2
	#define GET_SysTargetsystargetgetid2  ERR_OK
	#define CAL_SysTargetsystargetgetid2  systargetgetid2
	#define CHK_SysTargetsystargetgetid2  TRUE
	#define EXP_SysTargetsystargetgetid2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetid2", (RTS_UINTPTR)systargetgetid2, 1, 0xEA1E39C4, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systargetgetid2
	#define EXT_systargetgetid2
	#define GET_systargetgetid2(fl)  CAL_CMGETAPI( "systargetgetid2" ) 
	#define CAL_systargetgetid2  systargetgetid2
	#define CHK_systargetgetid2  TRUE
	#define EXP_systargetgetid2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetid2", (RTS_UINTPTR)systargetgetid2, 1, 0xEA1E39C4, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systargetgetid2  PFSYSTARGETGETID2_IEC pfsystargetgetid2;
	#define EXT_systargetgetid2  extern PFSYSTARGETGETID2_IEC pfsystargetgetid2;
	#define GET_systargetgetid2(fl)  s_pfCMGetAPI2( "systargetgetid2", (RTS_VOID_FCTPTR *)&pfsystargetgetid2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xEA1E39C4, 0x03050500)
	#define CAL_systargetgetid2  pfsystargetgetid2
	#define CHK_systargetgetid2  (pfsystargetgetid2 != NULL)
	#define EXP_systargetgetid2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetid2", (RTS_UINTPTR)systargetgetid2, 1, 0xEA1E39C4, 0x03050500) 
#endif


/**
 * <description>
 *  Get a human readable name that identifies this node in the network.
 *	NOTE: This could be the registered host name of the target in the network.
 * </description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystargetgetnodename_struct
{
	RTS_IEC_WSTRING *pwszName;			/* VAR_INPUT */	/* <param name="pwszName" type="IN">Buffer that is filled with the name of the node. Type is UTF-16.</param> */
	RTS_IEC_UDINT *pnMaxLength;			/* VAR_INPUT */	/* <param name="nMaxLength" type="IN">Maximum length of the node name including the trailing zero</param> */
	RTS_IEC_RESULT SysTargetGetNodeName;	/* VAR_OUTPUT */	
} systargetgetnodename_struct;

void CDECL CDECL_EXT systargetgetnodename(systargetgetnodename_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTARGETGETNODENAME_IEC) (systargetgetnodename_struct *p);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETNODENAME_NOTIMPLEMENTED)
	#define USE_systargetgetnodename
	#define EXT_systargetgetnodename
	#define GET_systargetgetnodename(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systargetgetnodename(p0) 
	#define CHK_systargetgetnodename  FALSE
	#define EXP_systargetgetnodename  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systargetgetnodename
	#define EXT_systargetgetnodename
	#define GET_systargetgetnodename(fl)  CAL_CMGETAPI( "systargetgetnodename" ) 
	#define CAL_systargetgetnodename  systargetgetnodename
	#define CHK_systargetgetnodename  TRUE
	#define EXP_systargetgetnodename  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetnodename", (RTS_UINTPTR)systargetgetnodename, 1, 0xA0044621, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_systargetgetnodename
	#define EXT_systargetgetnodename
	#define GET_systargetgetnodename(fl)  CAL_CMGETAPI( "systargetgetnodename" ) 
	#define CAL_systargetgetnodename  systargetgetnodename
	#define CHK_systargetgetnodename  TRUE
	#define EXP_systargetgetnodename  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetnodename", (RTS_UINTPTR)systargetgetnodename, 1, 0xA0044621, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetsystargetgetnodename
	#define EXT_SysTargetsystargetgetnodename
	#define GET_SysTargetsystargetgetnodename  ERR_OK
	#define CAL_SysTargetsystargetgetnodename  systargetgetnodename
	#define CHK_SysTargetsystargetgetnodename  TRUE
	#define EXP_SysTargetsystargetgetnodename  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetnodename", (RTS_UINTPTR)systargetgetnodename, 1, 0xA0044621, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systargetgetnodename
	#define EXT_systargetgetnodename
	#define GET_systargetgetnodename(fl)  CAL_CMGETAPI( "systargetgetnodename" ) 
	#define CAL_systargetgetnodename  systargetgetnodename
	#define CHK_systargetgetnodename  TRUE
	#define EXP_systargetgetnodename  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetnodename", (RTS_UINTPTR)systargetgetnodename, 1, 0xA0044621, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systargetgetnodename  PFSYSTARGETGETNODENAME_IEC pfsystargetgetnodename;
	#define EXT_systargetgetnodename  extern PFSYSTARGETGETNODENAME_IEC pfsystargetgetnodename;
	#define GET_systargetgetnodename(fl)  s_pfCMGetAPI2( "systargetgetnodename", (RTS_VOID_FCTPTR *)&pfsystargetgetnodename, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xA0044621, 0x03050500)
	#define CAL_systargetgetnodename  pfsystargetgetnodename
	#define CHK_systargetgetnodename  (pfsystargetgetnodename != NULL)
	#define EXP_systargetgetnodename   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetnodename", (RTS_UINTPTR)systargetgetnodename, 1, 0xA0044621, 0x03050500) 
#endif


/**
 * *OBSOLETE*: Only for backward compatibility! Should not be used
 */
typedef struct tagsystargetgetnodename2_struct
{
	RTS_IEC_STRING *pszRouterName;		/* VAR_INPUT */	
	RTS_IEC_WSTRING *pwszName;			/* VAR_INPUT */	
	RTS_IEC_UDINT *pnMaxLength;			/* VAR_INPUT */	
	RTS_IEC_RESULT SysTargetGetNodeName2;	/* VAR_OUTPUT */	
} systargetgetnodename2_struct;

void CDECL CDECL_EXT systargetgetnodename2(systargetgetnodename2_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTARGETGETNODENAME2_IEC) (systargetgetnodename2_struct *p);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETNODENAME2_NOTIMPLEMENTED)
	#define USE_systargetgetnodename2
	#define EXT_systargetgetnodename2
	#define GET_systargetgetnodename2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systargetgetnodename2(p0) 
	#define CHK_systargetgetnodename2  FALSE
	#define EXP_systargetgetnodename2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systargetgetnodename2
	#define EXT_systargetgetnodename2
	#define GET_systargetgetnodename2(fl)  CAL_CMGETAPI( "systargetgetnodename2" ) 
	#define CAL_systargetgetnodename2  systargetgetnodename2
	#define CHK_systargetgetnodename2  TRUE
	#define EXP_systargetgetnodename2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetnodename2", (RTS_UINTPTR)systargetgetnodename2, 1, 0x72B60F75, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_systargetgetnodename2
	#define EXT_systargetgetnodename2
	#define GET_systargetgetnodename2(fl)  CAL_CMGETAPI( "systargetgetnodename2" ) 
	#define CAL_systargetgetnodename2  systargetgetnodename2
	#define CHK_systargetgetnodename2  TRUE
	#define EXP_systargetgetnodename2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetnodename2", (RTS_UINTPTR)systargetgetnodename2, 1, 0x72B60F75, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetsystargetgetnodename2
	#define EXT_SysTargetsystargetgetnodename2
	#define GET_SysTargetsystargetgetnodename2  ERR_OK
	#define CAL_SysTargetsystargetgetnodename2  systargetgetnodename2
	#define CHK_SysTargetsystargetgetnodename2  TRUE
	#define EXP_SysTargetsystargetgetnodename2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetnodename2", (RTS_UINTPTR)systargetgetnodename2, 1, 0x72B60F75, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systargetgetnodename2
	#define EXT_systargetgetnodename2
	#define GET_systargetgetnodename2(fl)  CAL_CMGETAPI( "systargetgetnodename2" ) 
	#define CAL_systargetgetnodename2  systargetgetnodename2
	#define CHK_systargetgetnodename2  TRUE
	#define EXP_systargetgetnodename2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetnodename2", (RTS_UINTPTR)systargetgetnodename2, 1, 0x72B60F75, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systargetgetnodename2  PFSYSTARGETGETNODENAME2_IEC pfsystargetgetnodename2;
	#define EXT_systargetgetnodename2  extern PFSYSTARGETGETNODENAME2_IEC pfsystargetgetnodename2;
	#define GET_systargetgetnodename2(fl)  s_pfCMGetAPI2( "systargetgetnodename2", (RTS_VOID_FCTPTR *)&pfsystargetgetnodename2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x72B60F75, 0x03050500)
	#define CAL_systargetgetnodename2  pfsystargetgetnodename2
	#define CHK_systargetgetnodename2  (pfsystargetgetnodename2 != NULL)
	#define EXP_systargetgetnodename2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetnodename2", (RTS_UINTPTR)systargetgetnodename2, 1, 0x72B60F75, 0x03050500) 
#endif


/**
 * <description>Returns the ID of the operating system.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystargetgetoperatingsystemid_struct
{
	RTS_IEC_UDINT *pudiOperatingSystemId;	/* VAR_INPUT */	/* <param name="pudiOperatingSystemID" type="OUT">Pointer to operating system Id. See category "OperatingSystemID"</param> */
	RTS_IEC_RESULT SysTargetGetOperatingSystemId;	/* VAR_OUTPUT */	
} systargetgetoperatingsystemid_struct;

void CDECL CDECL_EXT systargetgetoperatingsystemid(systargetgetoperatingsystemid_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTARGETGETOPERATINGSYSTEMID_IEC) (systargetgetoperatingsystemid_struct *p);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETOPERATINGSYSTEMID_NOTIMPLEMENTED)
	#define USE_systargetgetoperatingsystemid
	#define EXT_systargetgetoperatingsystemid
	#define GET_systargetgetoperatingsystemid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systargetgetoperatingsystemid(p0) 
	#define CHK_systargetgetoperatingsystemid  FALSE
	#define EXP_systargetgetoperatingsystemid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systargetgetoperatingsystemid
	#define EXT_systargetgetoperatingsystemid
	#define GET_systargetgetoperatingsystemid(fl)  CAL_CMGETAPI( "systargetgetoperatingsystemid" ) 
	#define CAL_systargetgetoperatingsystemid  systargetgetoperatingsystemid
	#define CHK_systargetgetoperatingsystemid  TRUE
	#define EXP_systargetgetoperatingsystemid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetoperatingsystemid", (RTS_UINTPTR)systargetgetoperatingsystemid, 1, 0xC12147F5, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_systargetgetoperatingsystemid
	#define EXT_systargetgetoperatingsystemid
	#define GET_systargetgetoperatingsystemid(fl)  CAL_CMGETAPI( "systargetgetoperatingsystemid" ) 
	#define CAL_systargetgetoperatingsystemid  systargetgetoperatingsystemid
	#define CHK_systargetgetoperatingsystemid  TRUE
	#define EXP_systargetgetoperatingsystemid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetoperatingsystemid", (RTS_UINTPTR)systargetgetoperatingsystemid, 1, 0xC12147F5, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetsystargetgetoperatingsystemid
	#define EXT_SysTargetsystargetgetoperatingsystemid
	#define GET_SysTargetsystargetgetoperatingsystemid  ERR_OK
	#define CAL_SysTargetsystargetgetoperatingsystemid  systargetgetoperatingsystemid
	#define CHK_SysTargetsystargetgetoperatingsystemid  TRUE
	#define EXP_SysTargetsystargetgetoperatingsystemid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetoperatingsystemid", (RTS_UINTPTR)systargetgetoperatingsystemid, 1, 0xC12147F5, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systargetgetoperatingsystemid
	#define EXT_systargetgetoperatingsystemid
	#define GET_systargetgetoperatingsystemid(fl)  CAL_CMGETAPI( "systargetgetoperatingsystemid" ) 
	#define CAL_systargetgetoperatingsystemid  systargetgetoperatingsystemid
	#define CHK_systargetgetoperatingsystemid  TRUE
	#define EXP_systargetgetoperatingsystemid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetoperatingsystemid", (RTS_UINTPTR)systargetgetoperatingsystemid, 1, 0xC12147F5, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systargetgetoperatingsystemid  PFSYSTARGETGETOPERATINGSYSTEMID_IEC pfsystargetgetoperatingsystemid;
	#define EXT_systargetgetoperatingsystemid  extern PFSYSTARGETGETOPERATINGSYSTEMID_IEC pfsystargetgetoperatingsystemid;
	#define GET_systargetgetoperatingsystemid(fl)  s_pfCMGetAPI2( "systargetgetoperatingsystemid", (RTS_VOID_FCTPTR *)&pfsystargetgetoperatingsystemid, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xC12147F5, 0x03050500)
	#define CAL_systargetgetoperatingsystemid  pfsystargetgetoperatingsystemid
	#define CHK_systargetgetoperatingsystemid  (pfsystargetgetoperatingsystemid != NULL)
	#define EXP_systargetgetoperatingsystemid   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetoperatingsystemid", (RTS_UINTPTR)systargetgetoperatingsystemid, 1, 0xC12147F5, 0x03050500) 
#endif


/**
 * <description>Returns the ID of the processor</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystargetgetprocessorid_struct
{
	RTS_IEC_UDINT *pudiProcessorId;		/* VAR_INPUT */	/* <param name="pudiProcessorId" type="OUT">Pointer to processor ID. See category "ProcessorID" above</param> */
	RTS_IEC_RESULT SysTargetGetProcessorId;	/* VAR_OUTPUT */	
} systargetgetprocessorid_struct;

void CDECL CDECL_EXT systargetgetprocessorid(systargetgetprocessorid_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTARGETGETPROCESSORID_IEC) (systargetgetprocessorid_struct *p);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETPROCESSORID_NOTIMPLEMENTED)
	#define USE_systargetgetprocessorid
	#define EXT_systargetgetprocessorid
	#define GET_systargetgetprocessorid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systargetgetprocessorid(p0) 
	#define CHK_systargetgetprocessorid  FALSE
	#define EXP_systargetgetprocessorid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systargetgetprocessorid
	#define EXT_systargetgetprocessorid
	#define GET_systargetgetprocessorid(fl)  CAL_CMGETAPI( "systargetgetprocessorid" ) 
	#define CAL_systargetgetprocessorid  systargetgetprocessorid
	#define CHK_systargetgetprocessorid  TRUE
	#define EXP_systargetgetprocessorid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetprocessorid", (RTS_UINTPTR)systargetgetprocessorid, 1, 0x1C22A79F, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_systargetgetprocessorid
	#define EXT_systargetgetprocessorid
	#define GET_systargetgetprocessorid(fl)  CAL_CMGETAPI( "systargetgetprocessorid" ) 
	#define CAL_systargetgetprocessorid  systargetgetprocessorid
	#define CHK_systargetgetprocessorid  TRUE
	#define EXP_systargetgetprocessorid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetprocessorid", (RTS_UINTPTR)systargetgetprocessorid, 1, 0x1C22A79F, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetsystargetgetprocessorid
	#define EXT_SysTargetsystargetgetprocessorid
	#define GET_SysTargetsystargetgetprocessorid  ERR_OK
	#define CAL_SysTargetsystargetgetprocessorid  systargetgetprocessorid
	#define CHK_SysTargetsystargetgetprocessorid  TRUE
	#define EXP_SysTargetsystargetgetprocessorid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetprocessorid", (RTS_UINTPTR)systargetgetprocessorid, 1, 0x1C22A79F, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systargetgetprocessorid
	#define EXT_systargetgetprocessorid
	#define GET_systargetgetprocessorid(fl)  CAL_CMGETAPI( "systargetgetprocessorid" ) 
	#define CAL_systargetgetprocessorid  systargetgetprocessorid
	#define CHK_systargetgetprocessorid  TRUE
	#define EXP_systargetgetprocessorid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetprocessorid", (RTS_UINTPTR)systargetgetprocessorid, 1, 0x1C22A79F, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systargetgetprocessorid  PFSYSTARGETGETPROCESSORID_IEC pfsystargetgetprocessorid;
	#define EXT_systargetgetprocessorid  extern PFSYSTARGETGETPROCESSORID_IEC pfsystargetgetprocessorid;
	#define GET_systargetgetprocessorid(fl)  s_pfCMGetAPI2( "systargetgetprocessorid", (RTS_VOID_FCTPTR *)&pfsystargetgetprocessorid, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x1C22A79F, 0x03050500)
	#define CAL_systargetgetprocessorid  pfsystargetgetprocessorid
	#define CHK_systargetgetprocessorid  (pfsystargetgetprocessorid != NULL)
	#define EXP_systargetgetprocessorid   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetprocessorid", (RTS_UINTPTR)systargetgetprocessorid, 1, 0x1C22A79F, 0x03050500) 
#endif


/**
 * <description>Returns the serial number of the target. This can be a list of hardware specific signs (processor number, board number, mac-address, etc.).</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystargetgetserialnumber_struct
{
	RTS_IEC_STRING **ppsSerialNumber;	/* VAR_INPUT */	/* <param name="ppsSerialNumber" type="INOUT">Pointer to pointer to serial number.
	If ppsSerialNumber==NULL, the length of the serial number can be retrieved in *pnMaxLen.
	If *ppsSerialNumber==NULL, the pointer will be set to the serial nubmer. *pnMaxLen contains the real length of the serial number.
	If *ppsSerialNumber!=NULL, the serial number will be written into the buffer. *pnMaxLen must specify the max length of the buffer!</param> */
	RTS_IEC_DINT *pnMaxLen;				/* VAR_INPUT */	/* <param name="pnMaxLen" type="INOUT">Pointer to maxlength of ppsSerialNumber, returns the real length of content of ppsSerialNumber.</param> */
	RTS_IEC_RESULT SysTargetGetSerialNumber;	/* VAR_OUTPUT */	
} systargetgetserialnumber_struct;

void CDECL CDECL_EXT systargetgetserialnumber(systargetgetserialnumber_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTARGETGETSERIALNUMBER_IEC) (systargetgetserialnumber_struct *p);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETSERIALNUMBER_NOTIMPLEMENTED)
	#define USE_systargetgetserialnumber
	#define EXT_systargetgetserialnumber
	#define GET_systargetgetserialnumber(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systargetgetserialnumber(p0) 
	#define CHK_systargetgetserialnumber  FALSE
	#define EXP_systargetgetserialnumber  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systargetgetserialnumber
	#define EXT_systargetgetserialnumber
	#define GET_systargetgetserialnumber(fl)  CAL_CMGETAPI( "systargetgetserialnumber" ) 
	#define CAL_systargetgetserialnumber  systargetgetserialnumber
	#define CHK_systargetgetserialnumber  TRUE
	#define EXP_systargetgetserialnumber  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetserialnumber", (RTS_UINTPTR)systargetgetserialnumber, 1, 0x0DB18CE9, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_systargetgetserialnumber
	#define EXT_systargetgetserialnumber
	#define GET_systargetgetserialnumber(fl)  CAL_CMGETAPI( "systargetgetserialnumber" ) 
	#define CAL_systargetgetserialnumber  systargetgetserialnumber
	#define CHK_systargetgetserialnumber  TRUE
	#define EXP_systargetgetserialnumber  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetserialnumber", (RTS_UINTPTR)systargetgetserialnumber, 1, 0x0DB18CE9, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetsystargetgetserialnumber
	#define EXT_SysTargetsystargetgetserialnumber
	#define GET_SysTargetsystargetgetserialnumber  ERR_OK
	#define CAL_SysTargetsystargetgetserialnumber  systargetgetserialnumber
	#define CHK_SysTargetsystargetgetserialnumber  TRUE
	#define EXP_SysTargetsystargetgetserialnumber  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetserialnumber", (RTS_UINTPTR)systargetgetserialnumber, 1, 0x0DB18CE9, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systargetgetserialnumber
	#define EXT_systargetgetserialnumber
	#define GET_systargetgetserialnumber(fl)  CAL_CMGETAPI( "systargetgetserialnumber" ) 
	#define CAL_systargetgetserialnumber  systargetgetserialnumber
	#define CHK_systargetgetserialnumber  TRUE
	#define EXP_systargetgetserialnumber  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetserialnumber", (RTS_UINTPTR)systargetgetserialnumber, 1, 0x0DB18CE9, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systargetgetserialnumber  PFSYSTARGETGETSERIALNUMBER_IEC pfsystargetgetserialnumber;
	#define EXT_systargetgetserialnumber  extern PFSYSTARGETGETSERIALNUMBER_IEC pfsystargetgetserialnumber;
	#define GET_systargetgetserialnumber(fl)  s_pfCMGetAPI2( "systargetgetserialnumber", (RTS_VOID_FCTPTR *)&pfsystargetgetserialnumber, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0DB18CE9, 0x03050500)
	#define CAL_systargetgetserialnumber  pfsystargetgetserialnumber
	#define CHK_systargetgetserialnumber  (pfsystargetgetserialnumber != NULL)
	#define EXP_systargetgetserialnumber   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetserialnumber", (RTS_UINTPTR)systargetgetserialnumber, 1, 0x0DB18CE9, 0x03050500) 
#endif


/**
 * <description>Returns the target type. See "Device Types" for details.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystargetgettype_struct
{
	RTS_IEC_DWORD *pulType;				/* VAR_INPUT */	/* <param name="pulType" type="OUT">Pointer to target type. See corresponding category "Device Types"</param> */
	RTS_IEC_RESULT SysTargetGetType;	/* VAR_OUTPUT */	
} systargetgettype_struct;

void CDECL CDECL_EXT systargetgettype(systargetgettype_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTARGETGETTYPE_IEC) (systargetgettype_struct *p);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETTYPE_NOTIMPLEMENTED)
	#define USE_systargetgettype
	#define EXT_systargetgettype
	#define GET_systargetgettype(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systargetgettype(p0) 
	#define CHK_systargetgettype  FALSE
	#define EXP_systargetgettype  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systargetgettype
	#define EXT_systargetgettype
	#define GET_systargetgettype(fl)  CAL_CMGETAPI( "systargetgettype" ) 
	#define CAL_systargetgettype  systargetgettype
	#define CHK_systargetgettype  TRUE
	#define EXP_systargetgettype  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgettype", (RTS_UINTPTR)systargetgettype, 1, 0x4AD38850, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_systargetgettype
	#define EXT_systargetgettype
	#define GET_systargetgettype(fl)  CAL_CMGETAPI( "systargetgettype" ) 
	#define CAL_systargetgettype  systargetgettype
	#define CHK_systargetgettype  TRUE
	#define EXP_systargetgettype  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgettype", (RTS_UINTPTR)systargetgettype, 1, 0x4AD38850, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetsystargetgettype
	#define EXT_SysTargetsystargetgettype
	#define GET_SysTargetsystargetgettype  ERR_OK
	#define CAL_SysTargetsystargetgettype  systargetgettype
	#define CHK_SysTargetsystargetgettype  TRUE
	#define EXP_SysTargetsystargetgettype  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgettype", (RTS_UINTPTR)systargetgettype, 1, 0x4AD38850, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systargetgettype
	#define EXT_systargetgettype
	#define GET_systargetgettype(fl)  CAL_CMGETAPI( "systargetgettype" ) 
	#define CAL_systargetgettype  systargetgettype
	#define CHK_systargetgettype  TRUE
	#define EXP_systargetgettype  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgettype", (RTS_UINTPTR)systargetgettype, 1, 0x4AD38850, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systargetgettype  PFSYSTARGETGETTYPE_IEC pfsystargetgettype;
	#define EXT_systargetgettype  extern PFSYSTARGETGETTYPE_IEC pfsystargetgettype;
	#define GET_systargetgettype(fl)  s_pfCMGetAPI2( "systargetgettype", (RTS_VOID_FCTPTR *)&pfsystargetgettype, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x4AD38850, 0x03050500)
	#define CAL_systargetgettype  pfsystargetgettype
	#define CHK_systargetgettype  (pfsystargetgettype != NULL)
	#define EXP_systargetgettype   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgettype", (RTS_UINTPTR)systargetgettype, 1, 0x4AD38850, 0x03050500) 
#endif


/**
 * *OBSOLETE*: Only for backward compatibility! Should not be used
 */
typedef struct tagsystargetgettype2_struct
{
	RTS_IEC_STRING *pszRouterName;		/* VAR_INPUT */	
	RTS_IEC_DWORD *pulType;				/* VAR_INPUT */	
	RTS_IEC_RESULT SysTargetGetType2;	/* VAR_OUTPUT */	
} systargetgettype2_struct;

void CDECL CDECL_EXT systargetgettype2(systargetgettype2_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTARGETGETTYPE2_IEC) (systargetgettype2_struct *p);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETTYPE2_NOTIMPLEMENTED)
	#define USE_systargetgettype2
	#define EXT_systargetgettype2
	#define GET_systargetgettype2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systargetgettype2(p0) 
	#define CHK_systargetgettype2  FALSE
	#define EXP_systargetgettype2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systargetgettype2
	#define EXT_systargetgettype2
	#define GET_systargetgettype2(fl)  CAL_CMGETAPI( "systargetgettype2" ) 
	#define CAL_systargetgettype2  systargetgettype2
	#define CHK_systargetgettype2  TRUE
	#define EXP_systargetgettype2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgettype2", (RTS_UINTPTR)systargetgettype2, 1, 0x5F20D079, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_systargetgettype2
	#define EXT_systargetgettype2
	#define GET_systargetgettype2(fl)  CAL_CMGETAPI( "systargetgettype2" ) 
	#define CAL_systargetgettype2  systargetgettype2
	#define CHK_systargetgettype2  TRUE
	#define EXP_systargetgettype2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgettype2", (RTS_UINTPTR)systargetgettype2, 1, 0x5F20D079, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetsystargetgettype2
	#define EXT_SysTargetsystargetgettype2
	#define GET_SysTargetsystargetgettype2  ERR_OK
	#define CAL_SysTargetsystargetgettype2  systargetgettype2
	#define CHK_SysTargetsystargetgettype2  TRUE
	#define EXP_SysTargetsystargetgettype2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgettype2", (RTS_UINTPTR)systargetgettype2, 1, 0x5F20D079, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systargetgettype2
	#define EXT_systargetgettype2
	#define GET_systargetgettype2(fl)  CAL_CMGETAPI( "systargetgettype2" ) 
	#define CAL_systargetgettype2  systargetgettype2
	#define CHK_systargetgettype2  TRUE
	#define EXP_systargetgettype2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgettype2", (RTS_UINTPTR)systargetgettype2, 1, 0x5F20D079, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systargetgettype2  PFSYSTARGETGETTYPE2_IEC pfsystargetgettype2;
	#define EXT_systargetgettype2  extern PFSYSTARGETGETTYPE2_IEC pfsystargetgettype2;
	#define GET_systargetgettype2(fl)  s_pfCMGetAPI2( "systargetgettype2", (RTS_VOID_FCTPTR *)&pfsystargetgettype2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x5F20D079, 0x03050500)
	#define CAL_systargetgettype2  pfsystargetgettype2
	#define CHK_systargetgettype2  (pfsystargetgettype2 != NULL)
	#define EXP_systargetgettype2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgettype2", (RTS_UINTPTR)systargetgettype2, 1, 0x5F20D079, 0x03050500) 
#endif


/**
 * <description>Returns the vendor name of the target.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystargetgetvendorname_struct
{
	RTS_IEC_WSTRING *pwszName;			/* VAR_INPUT */	/* <param name="pwszName" type="OUT">Pointer to the device name</param> */
	RTS_IEC_UDINT *pnMaxLength;			/* VAR_INPUT */	/* <param name="nMaxLength" type="IN">Max length of the name</param> */
	RTS_IEC_RESULT SysTargetGetVendorName;	/* VAR_OUTPUT */	
} systargetgetvendorname_struct;

void CDECL CDECL_EXT systargetgetvendorname(systargetgetvendorname_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTARGETGETVENDORNAME_IEC) (systargetgetvendorname_struct *p);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETVENDORNAME_NOTIMPLEMENTED)
	#define USE_systargetgetvendorname
	#define EXT_systargetgetvendorname
	#define GET_systargetgetvendorname(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systargetgetvendorname(p0) 
	#define CHK_systargetgetvendorname  FALSE
	#define EXP_systargetgetvendorname  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systargetgetvendorname
	#define EXT_systargetgetvendorname
	#define GET_systargetgetvendorname(fl)  CAL_CMGETAPI( "systargetgetvendorname" ) 
	#define CAL_systargetgetvendorname  systargetgetvendorname
	#define CHK_systargetgetvendorname  TRUE
	#define EXP_systargetgetvendorname  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetvendorname", (RTS_UINTPTR)systargetgetvendorname, 1, 0xC7C8EF60, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_systargetgetvendorname
	#define EXT_systargetgetvendorname
	#define GET_systargetgetvendorname(fl)  CAL_CMGETAPI( "systargetgetvendorname" ) 
	#define CAL_systargetgetvendorname  systargetgetvendorname
	#define CHK_systargetgetvendorname  TRUE
	#define EXP_systargetgetvendorname  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetvendorname", (RTS_UINTPTR)systargetgetvendorname, 1, 0xC7C8EF60, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetsystargetgetvendorname
	#define EXT_SysTargetsystargetgetvendorname
	#define GET_SysTargetsystargetgetvendorname  ERR_OK
	#define CAL_SysTargetsystargetgetvendorname  systargetgetvendorname
	#define CHK_SysTargetsystargetgetvendorname  TRUE
	#define EXP_SysTargetsystargetgetvendorname  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetvendorname", (RTS_UINTPTR)systargetgetvendorname, 1, 0xC7C8EF60, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systargetgetvendorname
	#define EXT_systargetgetvendorname
	#define GET_systargetgetvendorname(fl)  CAL_CMGETAPI( "systargetgetvendorname" ) 
	#define CAL_systargetgetvendorname  systargetgetvendorname
	#define CHK_systargetgetvendorname  TRUE
	#define EXP_systargetgetvendorname  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetvendorname", (RTS_UINTPTR)systargetgetvendorname, 1, 0xC7C8EF60, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systargetgetvendorname  PFSYSTARGETGETVENDORNAME_IEC pfsystargetgetvendorname;
	#define EXT_systargetgetvendorname  extern PFSYSTARGETGETVENDORNAME_IEC pfsystargetgetvendorname;
	#define GET_systargetgetvendorname(fl)  s_pfCMGetAPI2( "systargetgetvendorname", (RTS_VOID_FCTPTR *)&pfsystargetgetvendorname, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xC7C8EF60, 0x03050500)
	#define CAL_systargetgetvendorname  pfsystargetgetvendorname
	#define CHK_systargetgetvendorname  (pfsystargetgetvendorname != NULL)
	#define EXP_systargetgetvendorname   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetvendorname", (RTS_UINTPTR)systargetgetvendorname, 1, 0xC7C8EF60, 0x03050500) 
#endif


/**
 * *OBSOLETE*: Only for backward compatibility! Should not be used
 */
typedef struct tagsystargetgetvendorname2_struct
{
	RTS_IEC_STRING *pszRouterName;		/* VAR_INPUT */	
	RTS_IEC_WSTRING *pwszName;			/* VAR_INPUT */	
	RTS_IEC_UDINT *pnMaxLength;			/* VAR_INPUT */	
	RTS_IEC_RESULT SysTargetGetVendorName2;	/* VAR_OUTPUT */	
} systargetgetvendorname2_struct;

void CDECL CDECL_EXT systargetgetvendorname2(systargetgetvendorname2_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTARGETGETVENDORNAME2_IEC) (systargetgetvendorname2_struct *p);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETVENDORNAME2_NOTIMPLEMENTED)
	#define USE_systargetgetvendorname2
	#define EXT_systargetgetvendorname2
	#define GET_systargetgetvendorname2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systargetgetvendorname2(p0) 
	#define CHK_systargetgetvendorname2  FALSE
	#define EXP_systargetgetvendorname2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systargetgetvendorname2
	#define EXT_systargetgetvendorname2
	#define GET_systargetgetvendorname2(fl)  CAL_CMGETAPI( "systargetgetvendorname2" ) 
	#define CAL_systargetgetvendorname2  systargetgetvendorname2
	#define CHK_systargetgetvendorname2  TRUE
	#define EXP_systargetgetvendorname2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetvendorname2", (RTS_UINTPTR)systargetgetvendorname2, 1, 0xECA5949D, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_systargetgetvendorname2
	#define EXT_systargetgetvendorname2
	#define GET_systargetgetvendorname2(fl)  CAL_CMGETAPI( "systargetgetvendorname2" ) 
	#define CAL_systargetgetvendorname2  systargetgetvendorname2
	#define CHK_systargetgetvendorname2  TRUE
	#define EXP_systargetgetvendorname2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetvendorname2", (RTS_UINTPTR)systargetgetvendorname2, 1, 0xECA5949D, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetsystargetgetvendorname2
	#define EXT_SysTargetsystargetgetvendorname2
	#define GET_SysTargetsystargetgetvendorname2  ERR_OK
	#define CAL_SysTargetsystargetgetvendorname2  systargetgetvendorname2
	#define CHK_SysTargetsystargetgetvendorname2  TRUE
	#define EXP_SysTargetsystargetgetvendorname2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetvendorname2", (RTS_UINTPTR)systargetgetvendorname2, 1, 0xECA5949D, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systargetgetvendorname2
	#define EXT_systargetgetvendorname2
	#define GET_systargetgetvendorname2(fl)  CAL_CMGETAPI( "systargetgetvendorname2" ) 
	#define CAL_systargetgetvendorname2  systargetgetvendorname2
	#define CHK_systargetgetvendorname2  TRUE
	#define EXP_systargetgetvendorname2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetvendorname2", (RTS_UINTPTR)systargetgetvendorname2, 1, 0xECA5949D, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systargetgetvendorname2  PFSYSTARGETGETVENDORNAME2_IEC pfsystargetgetvendorname2;
	#define EXT_systargetgetvendorname2  extern PFSYSTARGETGETVENDORNAME2_IEC pfsystargetgetvendorname2;
	#define GET_systargetgetvendorname2(fl)  s_pfCMGetAPI2( "systargetgetvendorname2", (RTS_VOID_FCTPTR *)&pfsystargetgetvendorname2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xECA5949D, 0x03050500)
	#define CAL_systargetgetvendorname2  pfsystargetgetvendorname2
	#define CHK_systargetgetvendorname2  (pfsystargetgetvendorname2 != NULL)
	#define EXP_systargetgetvendorname2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetvendorname2", (RTS_UINTPTR)systargetgetvendorname2, 1, 0xECA5949D, 0x03050500) 
#endif


/**
 * <description>Returns the target version.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystargetgetversion_struct
{
	RTS_IEC_DWORD *pulVersion;			/* VAR_INPUT */	/* <param name="pulVersion" type="OUT">Pointer to version of the target</param> */
	RTS_IEC_RESULT SysTargetGetVersion;	/* VAR_OUTPUT */	
} systargetgetversion_struct;

void CDECL CDECL_EXT systargetgetversion(systargetgetversion_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTARGETGETVERSION_IEC) (systargetgetversion_struct *p);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETVERSION_NOTIMPLEMENTED)
	#define USE_systargetgetversion
	#define EXT_systargetgetversion
	#define GET_systargetgetversion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systargetgetversion(p0) 
	#define CHK_systargetgetversion  FALSE
	#define EXP_systargetgetversion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systargetgetversion
	#define EXT_systargetgetversion
	#define GET_systargetgetversion(fl)  CAL_CMGETAPI( "systargetgetversion" ) 
	#define CAL_systargetgetversion  systargetgetversion
	#define CHK_systargetgetversion  TRUE
	#define EXP_systargetgetversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetversion", (RTS_UINTPTR)systargetgetversion, 1, 0x03C80949, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_systargetgetversion
	#define EXT_systargetgetversion
	#define GET_systargetgetversion(fl)  CAL_CMGETAPI( "systargetgetversion" ) 
	#define CAL_systargetgetversion  systargetgetversion
	#define CHK_systargetgetversion  TRUE
	#define EXP_systargetgetversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetversion", (RTS_UINTPTR)systargetgetversion, 1, 0x03C80949, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetsystargetgetversion
	#define EXT_SysTargetsystargetgetversion
	#define GET_SysTargetsystargetgetversion  ERR_OK
	#define CAL_SysTargetsystargetgetversion  systargetgetversion
	#define CHK_SysTargetsystargetgetversion  TRUE
	#define EXP_SysTargetsystargetgetversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetversion", (RTS_UINTPTR)systargetgetversion, 1, 0x03C80949, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systargetgetversion
	#define EXT_systargetgetversion
	#define GET_systargetgetversion(fl)  CAL_CMGETAPI( "systargetgetversion" ) 
	#define CAL_systargetgetversion  systargetgetversion
	#define CHK_systargetgetversion  TRUE
	#define EXP_systargetgetversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetversion", (RTS_UINTPTR)systargetgetversion, 1, 0x03C80949, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systargetgetversion  PFSYSTARGETGETVERSION_IEC pfsystargetgetversion;
	#define EXT_systargetgetversion  extern PFSYSTARGETGETVERSION_IEC pfsystargetgetversion;
	#define GET_systargetgetversion(fl)  s_pfCMGetAPI2( "systargetgetversion", (RTS_VOID_FCTPTR *)&pfsystargetgetversion, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x03C80949, 0x03050500)
	#define CAL_systargetgetversion  pfsystargetgetversion
	#define CHK_systargetgetversion  (pfsystargetgetversion != NULL)
	#define EXP_systargetgetversion   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetversion", (RTS_UINTPTR)systargetgetversion, 1, 0x03C80949, 0x03050500) 
#endif


/**
 * <description>Returns the target version</description>
 * <param name="pszRouterName" type="IN">Name of the corresponding router. This feature is used to set different identifications,
 *	if several routers are used on the same target.</param>
 * <param name="pulVersion" type="OUT">Pointer to version of the target</param>
 * <result>error code</result>
 */
typedef struct tagsystargetgetversion2_struct
{
	RTS_IEC_STRING *pszRouterName;		/* VAR_INPUT */	
	RTS_IEC_DWORD *pulVersion;			/* VAR_INPUT */	
	RTS_IEC_RESULT SysTargetGetVersion2;	/* VAR_OUTPUT */	
} systargetgetversion2_struct;

void CDECL CDECL_EXT systargetgetversion2(systargetgetversion2_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTARGETGETVERSION2_IEC) (systargetgetversion2_struct *p);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETVERSION2_NOTIMPLEMENTED)
	#define USE_systargetgetversion2
	#define EXT_systargetgetversion2
	#define GET_systargetgetversion2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systargetgetversion2(p0) 
	#define CHK_systargetgetversion2  FALSE
	#define EXP_systargetgetversion2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systargetgetversion2
	#define EXT_systargetgetversion2
	#define GET_systargetgetversion2(fl)  CAL_CMGETAPI( "systargetgetversion2" ) 
	#define CAL_systargetgetversion2  systargetgetversion2
	#define CHK_systargetgetversion2  TRUE
	#define EXP_systargetgetversion2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetversion2", (RTS_UINTPTR)systargetgetversion2, 1, 0x183560B4, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_systargetgetversion2
	#define EXT_systargetgetversion2
	#define GET_systargetgetversion2(fl)  CAL_CMGETAPI( "systargetgetversion2" ) 
	#define CAL_systargetgetversion2  systargetgetversion2
	#define CHK_systargetgetversion2  TRUE
	#define EXP_systargetgetversion2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetversion2", (RTS_UINTPTR)systargetgetversion2, 1, 0x183560B4, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetsystargetgetversion2
	#define EXT_SysTargetsystargetgetversion2
	#define GET_SysTargetsystargetgetversion2  ERR_OK
	#define CAL_SysTargetsystargetgetversion2  systargetgetversion2
	#define CHK_SysTargetsystargetgetversion2  TRUE
	#define EXP_SysTargetsystargetgetversion2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetversion2", (RTS_UINTPTR)systargetgetversion2, 1, 0x183560B4, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systargetgetversion2
	#define EXT_systargetgetversion2
	#define GET_systargetgetversion2(fl)  CAL_CMGETAPI( "systargetgetversion2" ) 
	#define CAL_systargetgetversion2  systargetgetversion2
	#define CHK_systargetgetversion2  TRUE
	#define EXP_systargetgetversion2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetversion2", (RTS_UINTPTR)systargetgetversion2, 1, 0x183560B4, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systargetgetversion2  PFSYSTARGETGETVERSION2_IEC pfsystargetgetversion2;
	#define EXT_systargetgetversion2  extern PFSYSTARGETGETVERSION2_IEC pfsystargetgetversion2;
	#define GET_systargetgetversion2(fl)  s_pfCMGetAPI2( "systargetgetversion2", (RTS_VOID_FCTPTR *)&pfsystargetgetversion2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x183560B4, 0x03050500)
	#define CAL_systargetgetversion2  pfsystargetgetversion2
	#define CHK_systargetgetversion2  (pfsystargetgetversion2 != NULL)
	#define EXP_systargetgetversion2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systargetgetversion2", (RTS_UINTPTR)systargetgetversion2, 1, 0x183560B4, 0x03050500) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysTargetOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysTargetOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>
 *  Get a human readable name that identifies this node in the network.
 *  <p>IMPLEMENTATION NOTES:</p>
 *  This node name, which is for example displayed in the CODESYS communication dialog scanning all targets, should be 
 *  unique by default. In first instance this could be the registered host name of the target in the network. Another
 *  approach ist to add the official serial number (e.g. "MyController_1234-5678") or the IP-Address of the controller, 
 *  which is most of the time unique (e.g. "MyController_192.168.123.234") as part of the node name. This requirement focused 
 *  on the use case where an end user takes several identical controllers of one vendor and plugs at once into his plant or machine.
 *  And so every controller should show up in the commuication dialog at a scan with a unique node name. Furthermore this is important
 *  to allow a client to connect by using the node name.
 *  The length is limited to SYSTARGET_MAX_NODE_NAME_LEN.
 * </description>
 * <param name="pwszName" type="IN" range="[0,VALID_NAME,INVALID_NAME]">Buffer that is filled with the name of the node. Type is UTF-16.</param>
 * <param name="pnMaxLength" type="INOUT" range="[0,VALID_LENGTH,INVALID_LENGTH]">Pointer to maximum length in 16-bit code units (not bytes!).
 *	Returns the number of 16-bit code units copied into the buffer including the trailing zero.</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Name was retrieved sucessfull</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Pointer to MaxLength or Name may not be null</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Name could not be retrieved</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysTargetGetNodeName(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength);
typedef RTS_RESULT (CDECL * PFSYSTARGETGETNODENAME) (RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETNODENAME_NOTIMPLEMENTED)
	#define USE_SysTargetGetNodeName
	#define EXT_SysTargetGetNodeName
	#define GET_SysTargetGetNodeName(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTargetGetNodeName(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTargetGetNodeName  FALSE
	#define EXP_SysTargetGetNodeName  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTargetGetNodeName
	#define EXT_SysTargetGetNodeName
	#define GET_SysTargetGetNodeName(fl)  CAL_CMGETAPI( "SysTargetGetNodeName" ) 
	#define CAL_SysTargetGetNodeName  SysTargetGetNodeName
	#define CHK_SysTargetGetNodeName  TRUE
	#define EXP_SysTargetGetNodeName  CAL_CMEXPAPI( "SysTargetGetNodeName" ) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_SysTargetGetNodeName
	#define EXT_SysTargetGetNodeName
	#define GET_SysTargetGetNodeName(fl)  CAL_CMGETAPI( "SysTargetGetNodeName" ) 
	#define CAL_SysTargetGetNodeName  SysTargetGetNodeName
	#define CHK_SysTargetGetNodeName  TRUE
	#define EXP_SysTargetGetNodeName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetNodeName", (RTS_UINTPTR)SysTargetGetNodeName, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetSysTargetGetNodeName
	#define EXT_SysTargetSysTargetGetNodeName
	#define GET_SysTargetSysTargetGetNodeName  ERR_OK
	#define CAL_SysTargetSysTargetGetNodeName pISysTarget->ISysTargetGetNodeName
	#define CHK_SysTargetSysTargetGetNodeName (pISysTarget != NULL)
	#define EXP_SysTargetSysTargetGetNodeName  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTargetGetNodeName
	#define EXT_SysTargetGetNodeName
	#define GET_SysTargetGetNodeName(fl)  CAL_CMGETAPI( "SysTargetGetNodeName" ) 
	#define CAL_SysTargetGetNodeName pISysTarget->ISysTargetGetNodeName
	#define CHK_SysTargetGetNodeName (pISysTarget != NULL)
	#define EXP_SysTargetGetNodeName  CAL_CMEXPAPI( "SysTargetGetNodeName" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTargetGetNodeName  PFSYSTARGETGETNODENAME pfSysTargetGetNodeName;
	#define EXT_SysTargetGetNodeName  extern PFSYSTARGETGETNODENAME pfSysTargetGetNodeName;
	#define GET_SysTargetGetNodeName(fl)  s_pfCMGetAPI2( "SysTargetGetNodeName", (RTS_VOID_FCTPTR *)&pfSysTargetGetNodeName, (fl), 0, 0)
	#define CAL_SysTargetGetNodeName  pfSysTargetGetNodeName
	#define CHK_SysTargetGetNodeName  (pfSysTargetGetNodeName != NULL)
	#define EXP_SysTargetGetNodeName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetNodeName", (RTS_UINTPTR)SysTargetGetNodeName, 0, 0) 
#endif




/**
 * <description>
 *  Get a human readable name for the target. This can be configured by the name setting (see category above).
 * </description>
 * <param name="pwszName" type="IN" range="[0,VALID_NAME,INVALID_NAME]">Buffer that is filled with the name of the node. Type is UTF-16. Can be NULL to get the necessary length.</param>
 * <param name="pnMaxLength" type="INOUT" range="[0,VALID_LENGTH,INVALID_LENGTH]">Pointer to maximum length in 16-bit code units (not bytes!).
 *	Returns the number of 16-bit code units copied into the buffer including the trailing zero.</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Name was retrieved sucessfull</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Pointer to MaxLength or Name may not be null</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Name could not be retrieved</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysTargetGetConfiguredNodeName(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength);
typedef RTS_RESULT (CDECL * PFSYSTARGETGETCONFIGUREDNODENAME) (RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETCONFIGUREDNODENAME_NOTIMPLEMENTED)
	#define USE_SysTargetGetConfiguredNodeName
	#define EXT_SysTargetGetConfiguredNodeName
	#define GET_SysTargetGetConfiguredNodeName(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTargetGetConfiguredNodeName(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTargetGetConfiguredNodeName  FALSE
	#define EXP_SysTargetGetConfiguredNodeName  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTargetGetConfiguredNodeName
	#define EXT_SysTargetGetConfiguredNodeName
	#define GET_SysTargetGetConfiguredNodeName(fl)  CAL_CMGETAPI( "SysTargetGetConfiguredNodeName" ) 
	#define CAL_SysTargetGetConfiguredNodeName  SysTargetGetConfiguredNodeName
	#define CHK_SysTargetGetConfiguredNodeName  TRUE
	#define EXP_SysTargetGetConfiguredNodeName  CAL_CMEXPAPI( "SysTargetGetConfiguredNodeName" ) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_SysTargetGetConfiguredNodeName
	#define EXT_SysTargetGetConfiguredNodeName
	#define GET_SysTargetGetConfiguredNodeName(fl)  CAL_CMGETAPI( "SysTargetGetConfiguredNodeName" ) 
	#define CAL_SysTargetGetConfiguredNodeName  SysTargetGetConfiguredNodeName
	#define CHK_SysTargetGetConfiguredNodeName  TRUE
	#define EXP_SysTargetGetConfiguredNodeName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetConfiguredNodeName", (RTS_UINTPTR)SysTargetGetConfiguredNodeName, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetSysTargetGetConfiguredNodeName
	#define EXT_SysTargetSysTargetGetConfiguredNodeName
	#define GET_SysTargetSysTargetGetConfiguredNodeName  ERR_OK
	#define CAL_SysTargetSysTargetGetConfiguredNodeName pISysTarget->ISysTargetGetConfiguredNodeName
	#define CHK_SysTargetSysTargetGetConfiguredNodeName (pISysTarget != NULL)
	#define EXP_SysTargetSysTargetGetConfiguredNodeName  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTargetGetConfiguredNodeName
	#define EXT_SysTargetGetConfiguredNodeName
	#define GET_SysTargetGetConfiguredNodeName(fl)  CAL_CMGETAPI( "SysTargetGetConfiguredNodeName" ) 
	#define CAL_SysTargetGetConfiguredNodeName pISysTarget->ISysTargetGetConfiguredNodeName
	#define CHK_SysTargetGetConfiguredNodeName (pISysTarget != NULL)
	#define EXP_SysTargetGetConfiguredNodeName  CAL_CMEXPAPI( "SysTargetGetConfiguredNodeName" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTargetGetConfiguredNodeName  PFSYSTARGETGETCONFIGUREDNODENAME pfSysTargetGetConfiguredNodeName;
	#define EXT_SysTargetGetConfiguredNodeName  extern PFSYSTARGETGETCONFIGUREDNODENAME pfSysTargetGetConfiguredNodeName;
	#define GET_SysTargetGetConfiguredNodeName(fl)  s_pfCMGetAPI2( "SysTargetGetConfiguredNodeName", (RTS_VOID_FCTPTR *)&pfSysTargetGetConfiguredNodeName, (fl), 0, 0)
	#define CAL_SysTargetGetConfiguredNodeName  pfSysTargetGetConfiguredNodeName
	#define CHK_SysTargetGetConfiguredNodeName  (pfSysTargetGetConfiguredNodeName != NULL)
	#define EXP_SysTargetGetConfiguredNodeName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetConfiguredNodeName", (RTS_UINTPTR)SysTargetGetConfiguredNodeName, 0, 0) 
#endif




/**
 * <description>
 * <p>Returns the target type</p>
 * <p>The possible target types are specified in the section "Device Types" (e.g. SYSTARGET_TYPE_PROGRAMMABLE).</p>
 * <p>Note: On SIL2 runtimes, this should return the value of the define SYSTARGET_DEVICE_TYPE.</p>
 * </description>
 * <param name="pulType" type="INOUT" range="[0,VALID_TYPE_POINTER]">Pointer to target type. See corresponding category "Device Types"</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">TargetType was retrieved sucessfull</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Pointer to Type may not be null</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">TargetType could not be retrieved</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysTargetGetType(RTS_UI32 *pulType);
typedef RTS_RESULT (CDECL * PFSYSTARGETGETTYPE) (RTS_UI32 *pulType);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETTYPE_NOTIMPLEMENTED)
	#define USE_SysTargetGetType
	#define EXT_SysTargetGetType
	#define GET_SysTargetGetType(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTargetGetType(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTargetGetType  FALSE
	#define EXP_SysTargetGetType  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTargetGetType
	#define EXT_SysTargetGetType
	#define GET_SysTargetGetType(fl)  CAL_CMGETAPI( "SysTargetGetType" ) 
	#define CAL_SysTargetGetType  SysTargetGetType
	#define CHK_SysTargetGetType  TRUE
	#define EXP_SysTargetGetType  CAL_CMEXPAPI( "SysTargetGetType" ) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_SysTargetGetType
	#define EXT_SysTargetGetType
	#define GET_SysTargetGetType(fl)  CAL_CMGETAPI( "SysTargetGetType" ) 
	#define CAL_SysTargetGetType  SysTargetGetType
	#define CHK_SysTargetGetType  TRUE
	#define EXP_SysTargetGetType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetType", (RTS_UINTPTR)SysTargetGetType, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetSysTargetGetType
	#define EXT_SysTargetSysTargetGetType
	#define GET_SysTargetSysTargetGetType  ERR_OK
	#define CAL_SysTargetSysTargetGetType pISysTarget->ISysTargetGetType
	#define CHK_SysTargetSysTargetGetType (pISysTarget != NULL)
	#define EXP_SysTargetSysTargetGetType  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTargetGetType
	#define EXT_SysTargetGetType
	#define GET_SysTargetGetType(fl)  CAL_CMGETAPI( "SysTargetGetType" ) 
	#define CAL_SysTargetGetType pISysTarget->ISysTargetGetType
	#define CHK_SysTargetGetType (pISysTarget != NULL)
	#define EXP_SysTargetGetType  CAL_CMEXPAPI( "SysTargetGetType" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTargetGetType  PFSYSTARGETGETTYPE pfSysTargetGetType;
	#define EXT_SysTargetGetType  extern PFSYSTARGETGETTYPE pfSysTargetGetType;
	#define GET_SysTargetGetType(fl)  s_pfCMGetAPI2( "SysTargetGetType", (RTS_VOID_FCTPTR *)&pfSysTargetGetType, (fl), 0, 0)
	#define CAL_SysTargetGetType  pfSysTargetGetType
	#define CHK_SysTargetGetType  (pfSysTargetGetType != NULL)
	#define EXP_SysTargetGetType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetType", (RTS_UINTPTR)SysTargetGetType, 0, 0) 
#endif




/**
 * <description>
 * <p>Returns the TargetId of the PLC.</p>
 * <p>Note: Highword of the TargetId must be the VendorId! The VendorId is managed by 3S.</p>
 * <p>Note2: On SIL2 runtimes, this should return the combination of the defines SYSTARGET_VENDOR_ID and SYSTARGET_DEVICE_ID.</p>
 * </description>
 * <param name="pulTargetId" type="INOUT" range="[0,VALID_ID_POINTER]">Pointer to the TargetId</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">TargetId was retrieved sucessfull</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Pointer to TargetId may not be null</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">TargetId could not be retrieved</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysTargetGetId(RTS_UI32 *pulTargetId);
typedef RTS_RESULT (CDECL * PFSYSTARGETGETID) (RTS_UI32 *pulTargetId);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETID_NOTIMPLEMENTED)
	#define USE_SysTargetGetId
	#define EXT_SysTargetGetId
	#define GET_SysTargetGetId(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTargetGetId(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTargetGetId  FALSE
	#define EXP_SysTargetGetId  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTargetGetId
	#define EXT_SysTargetGetId
	#define GET_SysTargetGetId(fl)  CAL_CMGETAPI( "SysTargetGetId" ) 
	#define CAL_SysTargetGetId  SysTargetGetId
	#define CHK_SysTargetGetId  TRUE
	#define EXP_SysTargetGetId  CAL_CMEXPAPI( "SysTargetGetId" ) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_SysTargetGetId
	#define EXT_SysTargetGetId
	#define GET_SysTargetGetId(fl)  CAL_CMGETAPI( "SysTargetGetId" ) 
	#define CAL_SysTargetGetId  SysTargetGetId
	#define CHK_SysTargetGetId  TRUE
	#define EXP_SysTargetGetId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetId", (RTS_UINTPTR)SysTargetGetId, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetSysTargetGetId
	#define EXT_SysTargetSysTargetGetId
	#define GET_SysTargetSysTargetGetId  ERR_OK
	#define CAL_SysTargetSysTargetGetId pISysTarget->ISysTargetGetId
	#define CHK_SysTargetSysTargetGetId (pISysTarget != NULL)
	#define EXP_SysTargetSysTargetGetId  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTargetGetId
	#define EXT_SysTargetGetId
	#define GET_SysTargetGetId(fl)  CAL_CMGETAPI( "SysTargetGetId" ) 
	#define CAL_SysTargetGetId pISysTarget->ISysTargetGetId
	#define CHK_SysTargetGetId (pISysTarget != NULL)
	#define EXP_SysTargetGetId  CAL_CMEXPAPI( "SysTargetGetId" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTargetGetId  PFSYSTARGETGETID pfSysTargetGetId;
	#define EXT_SysTargetGetId  extern PFSYSTARGETGETID pfSysTargetGetId;
	#define GET_SysTargetGetId(fl)  s_pfCMGetAPI2( "SysTargetGetId", (RTS_VOID_FCTPTR *)&pfSysTargetGetId, (fl), 0, 0)
	#define CAL_SysTargetGetId  pfSysTargetGetId
	#define CHK_SysTargetGetId  (pfSysTargetGetId != NULL)
	#define EXP_SysTargetGetId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetId", (RTS_UINTPTR)SysTargetGetId, 0, 0) 
#endif




/**
 * <description>
 * <p>Returns the target version</p>
 * <p>Note: On SIL2 runtimes, this should return the value of the define SYSTARGET_DEVICE_VERSION.</p>
 * </description>
 * <param name="pulVersion" type="INOUT" range="[0,VALID_VERSION_POINTER]">Pointer to version of the target</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">version was retrieved sucessfull</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Pointer to version may not be null</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">version could not be retrieved</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysTargetGetVersion(RTS_UI32 *pulVersion);
typedef RTS_RESULT (CDECL * PFSYSTARGETGETVERSION) (RTS_UI32 *pulVersion);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETVERSION_NOTIMPLEMENTED)
	#define USE_SysTargetGetVersion
	#define EXT_SysTargetGetVersion
	#define GET_SysTargetGetVersion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTargetGetVersion(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTargetGetVersion  FALSE
	#define EXP_SysTargetGetVersion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTargetGetVersion
	#define EXT_SysTargetGetVersion
	#define GET_SysTargetGetVersion(fl)  CAL_CMGETAPI( "SysTargetGetVersion" ) 
	#define CAL_SysTargetGetVersion  SysTargetGetVersion
	#define CHK_SysTargetGetVersion  TRUE
	#define EXP_SysTargetGetVersion  CAL_CMEXPAPI( "SysTargetGetVersion" ) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_SysTargetGetVersion
	#define EXT_SysTargetGetVersion
	#define GET_SysTargetGetVersion(fl)  CAL_CMGETAPI( "SysTargetGetVersion" ) 
	#define CAL_SysTargetGetVersion  SysTargetGetVersion
	#define CHK_SysTargetGetVersion  TRUE
	#define EXP_SysTargetGetVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetVersion", (RTS_UINTPTR)SysTargetGetVersion, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetSysTargetGetVersion
	#define EXT_SysTargetSysTargetGetVersion
	#define GET_SysTargetSysTargetGetVersion  ERR_OK
	#define CAL_SysTargetSysTargetGetVersion pISysTarget->ISysTargetGetVersion
	#define CHK_SysTargetSysTargetGetVersion (pISysTarget != NULL)
	#define EXP_SysTargetSysTargetGetVersion  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTargetGetVersion
	#define EXT_SysTargetGetVersion
	#define GET_SysTargetGetVersion(fl)  CAL_CMGETAPI( "SysTargetGetVersion" ) 
	#define CAL_SysTargetGetVersion pISysTarget->ISysTargetGetVersion
	#define CHK_SysTargetGetVersion (pISysTarget != NULL)
	#define EXP_SysTargetGetVersion  CAL_CMEXPAPI( "SysTargetGetVersion" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTargetGetVersion  PFSYSTARGETGETVERSION pfSysTargetGetVersion;
	#define EXT_SysTargetGetVersion  extern PFSYSTARGETGETVERSION pfSysTargetGetVersion;
	#define GET_SysTargetGetVersion(fl)  s_pfCMGetAPI2( "SysTargetGetVersion", (RTS_VOID_FCTPTR *)&pfSysTargetGetVersion, (fl), 0, 0)
	#define CAL_SysTargetGetVersion  pfSysTargetGetVersion
	#define CHK_SysTargetGetVersion  (pfSysTargetGetVersion != NULL)
	#define EXP_SysTargetGetVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetVersion", (RTS_UINTPTR)SysTargetGetVersion, 0, 0) 
#endif




/**
 * <description>Returns the device name</description>
 *  The device name is for example displayed in the CODESYS communication dialog scanning all targets.
 * <p>IMPLEMENTATION NOTES:</p>
 *  The length is limited to SYSTARGET_MAX_DEVICE_NAME_LEN. But it is strongly recommended to avoid device names with more than
 *  50 16-bit code units including NULL termination, because there exist use cases which can handle only this shorter length.
 * <param name="pwszName" type="INOUT" range="[0,INVALID_NAME,VALID_NAME]">Pointer to the device name. Type is UTF-16. Can be NULL to get the necessary length.</param>
 * <param name="pnMaxLength" type="INOUT" range="[0,INVALID_LENGTH,VALID_LENGTH]">Pointer to maximum length of the name in 16-bit code units (not bytes!).
 *	Returns the number of 16-bit code units copied into the buffer including the trailing zero.</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">device name was retrieved sucessfull</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Pointer to length may not be null</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">device name could not be retrieved</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysTargetGetDeviceName(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength);
typedef RTS_RESULT (CDECL * PFSYSTARGETGETDEVICENAME) (RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETDEVICENAME_NOTIMPLEMENTED)
	#define USE_SysTargetGetDeviceName
	#define EXT_SysTargetGetDeviceName
	#define GET_SysTargetGetDeviceName(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTargetGetDeviceName(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTargetGetDeviceName  FALSE
	#define EXP_SysTargetGetDeviceName  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTargetGetDeviceName
	#define EXT_SysTargetGetDeviceName
	#define GET_SysTargetGetDeviceName(fl)  CAL_CMGETAPI( "SysTargetGetDeviceName" ) 
	#define CAL_SysTargetGetDeviceName  SysTargetGetDeviceName
	#define CHK_SysTargetGetDeviceName  TRUE
	#define EXP_SysTargetGetDeviceName  CAL_CMEXPAPI( "SysTargetGetDeviceName" ) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_SysTargetGetDeviceName
	#define EXT_SysTargetGetDeviceName
	#define GET_SysTargetGetDeviceName(fl)  CAL_CMGETAPI( "SysTargetGetDeviceName" ) 
	#define CAL_SysTargetGetDeviceName  SysTargetGetDeviceName
	#define CHK_SysTargetGetDeviceName  TRUE
	#define EXP_SysTargetGetDeviceName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetDeviceName", (RTS_UINTPTR)SysTargetGetDeviceName, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetSysTargetGetDeviceName
	#define EXT_SysTargetSysTargetGetDeviceName
	#define GET_SysTargetSysTargetGetDeviceName  ERR_OK
	#define CAL_SysTargetSysTargetGetDeviceName pISysTarget->ISysTargetGetDeviceName
	#define CHK_SysTargetSysTargetGetDeviceName (pISysTarget != NULL)
	#define EXP_SysTargetSysTargetGetDeviceName  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTargetGetDeviceName
	#define EXT_SysTargetGetDeviceName
	#define GET_SysTargetGetDeviceName(fl)  CAL_CMGETAPI( "SysTargetGetDeviceName" ) 
	#define CAL_SysTargetGetDeviceName pISysTarget->ISysTargetGetDeviceName
	#define CHK_SysTargetGetDeviceName (pISysTarget != NULL)
	#define EXP_SysTargetGetDeviceName  CAL_CMEXPAPI( "SysTargetGetDeviceName" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTargetGetDeviceName  PFSYSTARGETGETDEVICENAME pfSysTargetGetDeviceName;
	#define EXT_SysTargetGetDeviceName  extern PFSYSTARGETGETDEVICENAME pfSysTargetGetDeviceName;
	#define GET_SysTargetGetDeviceName(fl)  s_pfCMGetAPI2( "SysTargetGetDeviceName", (RTS_VOID_FCTPTR *)&pfSysTargetGetDeviceName, (fl), 0, 0)
	#define CAL_SysTargetGetDeviceName  pfSysTargetGetDeviceName
	#define CHK_SysTargetGetDeviceName  (pfSysTargetGetDeviceName != NULL)
	#define EXP_SysTargetGetDeviceName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetDeviceName", (RTS_UINTPTR)SysTargetGetDeviceName, 0, 0) 
#endif




/**
 * <description>Returns the vendor name</description>
 *  The vendor name is for example displayed in the CODESYS communication dialog scanning all targets.
 * <p>IMPLEMENTATION NOTES:</p>
 *  The length is limited to SYSTARGET_MAX_VENDOR_NAME_LEN. But it is strongly recommended to avoid device names with more than
 *  50 16-bit code units including NULL termination, because there exist use cases which can handle only this shorter length.
 * <param name="pwszName" type="INOUT" range="[0,INVALID_NAME,VALID_NAME]">Pointer to the device name. Type is UTF-16. Can be NULL to get the necessary length.</param>
 * <param name="pnMaxLength" type="INOUT" range="[0,INVALID_LENGTH,VALID_LENGTH]">Pointer to maximum length of the name in 16-bit code units (not bytes!).
 *	Returns the number of 16-bit code units copied into the buffer including the trailing zero.</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">vendor name was retrieved sucessfull</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Pointer to length may not be null</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">vendor name could not be retrieved</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysTargetGetVendorName(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength);
typedef RTS_RESULT (CDECL * PFSYSTARGETGETVENDORNAME) (RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETVENDORNAME_NOTIMPLEMENTED)
	#define USE_SysTargetGetVendorName
	#define EXT_SysTargetGetVendorName
	#define GET_SysTargetGetVendorName(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTargetGetVendorName(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTargetGetVendorName  FALSE
	#define EXP_SysTargetGetVendorName  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTargetGetVendorName
	#define EXT_SysTargetGetVendorName
	#define GET_SysTargetGetVendorName(fl)  CAL_CMGETAPI( "SysTargetGetVendorName" ) 
	#define CAL_SysTargetGetVendorName  SysTargetGetVendorName
	#define CHK_SysTargetGetVendorName  TRUE
	#define EXP_SysTargetGetVendorName  CAL_CMEXPAPI( "SysTargetGetVendorName" ) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_SysTargetGetVendorName
	#define EXT_SysTargetGetVendorName
	#define GET_SysTargetGetVendorName(fl)  CAL_CMGETAPI( "SysTargetGetVendorName" ) 
	#define CAL_SysTargetGetVendorName  SysTargetGetVendorName
	#define CHK_SysTargetGetVendorName  TRUE
	#define EXP_SysTargetGetVendorName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetVendorName", (RTS_UINTPTR)SysTargetGetVendorName, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetSysTargetGetVendorName
	#define EXT_SysTargetSysTargetGetVendorName
	#define GET_SysTargetSysTargetGetVendorName  ERR_OK
	#define CAL_SysTargetSysTargetGetVendorName pISysTarget->ISysTargetGetVendorName
	#define CHK_SysTargetSysTargetGetVendorName (pISysTarget != NULL)
	#define EXP_SysTargetSysTargetGetVendorName  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTargetGetVendorName
	#define EXT_SysTargetGetVendorName
	#define GET_SysTargetGetVendorName(fl)  CAL_CMGETAPI( "SysTargetGetVendorName" ) 
	#define CAL_SysTargetGetVendorName pISysTarget->ISysTargetGetVendorName
	#define CHK_SysTargetGetVendorName (pISysTarget != NULL)
	#define EXP_SysTargetGetVendorName  CAL_CMEXPAPI( "SysTargetGetVendorName" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTargetGetVendorName  PFSYSTARGETGETVENDORNAME pfSysTargetGetVendorName;
	#define EXT_SysTargetGetVendorName  extern PFSYSTARGETGETVENDORNAME pfSysTargetGetVendorName;
	#define GET_SysTargetGetVendorName(fl)  s_pfCMGetAPI2( "SysTargetGetVendorName", (RTS_VOID_FCTPTR *)&pfSysTargetGetVendorName, (fl), 0, 0)
	#define CAL_SysTargetGetVendorName  pfSysTargetGetVendorName
	#define CHK_SysTargetGetVendorName  (pfSysTargetGetVendorName != NULL)
	#define EXP_SysTargetGetVendorName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetVendorName", (RTS_UINTPTR)SysTargetGetVendorName, 0, 0) 
#endif




/**
 * <description>Returns the ID of the operating system.</description>
 * <param name="pulOperatingSystemID" type="INOUT" range="[0,VALID_OS_ID_POINTER]">Pointer to operating system Id. See category "Operating System" above</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">OS ID was retrieved sucessfull</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Pointer to OS ID may not be null</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">OS ID could not be retrieved</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysTargetGetOperatingSystemId(RTS_UI32 *pulOperatingSystemId);
typedef RTS_RESULT (CDECL * PFSYSTARGETGETOPERATINGSYSTEMID) (RTS_UI32 *pulOperatingSystemId);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETOPERATINGSYSTEMID_NOTIMPLEMENTED)
	#define USE_SysTargetGetOperatingSystemId
	#define EXT_SysTargetGetOperatingSystemId
	#define GET_SysTargetGetOperatingSystemId(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTargetGetOperatingSystemId(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTargetGetOperatingSystemId  FALSE
	#define EXP_SysTargetGetOperatingSystemId  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTargetGetOperatingSystemId
	#define EXT_SysTargetGetOperatingSystemId
	#define GET_SysTargetGetOperatingSystemId(fl)  CAL_CMGETAPI( "SysTargetGetOperatingSystemId" ) 
	#define CAL_SysTargetGetOperatingSystemId  SysTargetGetOperatingSystemId
	#define CHK_SysTargetGetOperatingSystemId  TRUE
	#define EXP_SysTargetGetOperatingSystemId  CAL_CMEXPAPI( "SysTargetGetOperatingSystemId" ) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_SysTargetGetOperatingSystemId
	#define EXT_SysTargetGetOperatingSystemId
	#define GET_SysTargetGetOperatingSystemId(fl)  CAL_CMGETAPI( "SysTargetGetOperatingSystemId" ) 
	#define CAL_SysTargetGetOperatingSystemId  SysTargetGetOperatingSystemId
	#define CHK_SysTargetGetOperatingSystemId  TRUE
	#define EXP_SysTargetGetOperatingSystemId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetOperatingSystemId", (RTS_UINTPTR)SysTargetGetOperatingSystemId, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetSysTargetGetOperatingSystemId
	#define EXT_SysTargetSysTargetGetOperatingSystemId
	#define GET_SysTargetSysTargetGetOperatingSystemId  ERR_OK
	#define CAL_SysTargetSysTargetGetOperatingSystemId pISysTarget->ISysTargetGetOperatingSystemId
	#define CHK_SysTargetSysTargetGetOperatingSystemId (pISysTarget != NULL)
	#define EXP_SysTargetSysTargetGetOperatingSystemId  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTargetGetOperatingSystemId
	#define EXT_SysTargetGetOperatingSystemId
	#define GET_SysTargetGetOperatingSystemId(fl)  CAL_CMGETAPI( "SysTargetGetOperatingSystemId" ) 
	#define CAL_SysTargetGetOperatingSystemId pISysTarget->ISysTargetGetOperatingSystemId
	#define CHK_SysTargetGetOperatingSystemId (pISysTarget != NULL)
	#define EXP_SysTargetGetOperatingSystemId  CAL_CMEXPAPI( "SysTargetGetOperatingSystemId" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTargetGetOperatingSystemId  PFSYSTARGETGETOPERATINGSYSTEMID pfSysTargetGetOperatingSystemId;
	#define EXT_SysTargetGetOperatingSystemId  extern PFSYSTARGETGETOPERATINGSYSTEMID pfSysTargetGetOperatingSystemId;
	#define GET_SysTargetGetOperatingSystemId(fl)  s_pfCMGetAPI2( "SysTargetGetOperatingSystemId", (RTS_VOID_FCTPTR *)&pfSysTargetGetOperatingSystemId, (fl), 0, 0)
	#define CAL_SysTargetGetOperatingSystemId  pfSysTargetGetOperatingSystemId
	#define CHK_SysTargetGetOperatingSystemId  (pfSysTargetGetOperatingSystemId != NULL)
	#define EXP_SysTargetGetOperatingSystemId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetOperatingSystemId", (RTS_UINTPTR)SysTargetGetOperatingSystemId, 0, 0) 
#endif




/**
 * <description>Returns the ID of the processor</description>
 * <param name="pulProcessorID" type="INOUT" range="[0,VALID_CPU_ID_POINTER]">Pointer to processor ID. See category "Processor ID" above</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">CPU ID was retrieved sucessfull</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Pointer to CPU ID may not be null</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">CPU ID could not be retrieved</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysTargetGetProcessorId(RTS_UI32 *pulProcessorId);
typedef RTS_RESULT (CDECL * PFSYSTARGETGETPROCESSORID) (RTS_UI32 *pulProcessorId);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETPROCESSORID_NOTIMPLEMENTED)
	#define USE_SysTargetGetProcessorId
	#define EXT_SysTargetGetProcessorId
	#define GET_SysTargetGetProcessorId(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTargetGetProcessorId(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTargetGetProcessorId  FALSE
	#define EXP_SysTargetGetProcessorId  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTargetGetProcessorId
	#define EXT_SysTargetGetProcessorId
	#define GET_SysTargetGetProcessorId(fl)  CAL_CMGETAPI( "SysTargetGetProcessorId" ) 
	#define CAL_SysTargetGetProcessorId  SysTargetGetProcessorId
	#define CHK_SysTargetGetProcessorId  TRUE
	#define EXP_SysTargetGetProcessorId  CAL_CMEXPAPI( "SysTargetGetProcessorId" ) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_SysTargetGetProcessorId
	#define EXT_SysTargetGetProcessorId
	#define GET_SysTargetGetProcessorId(fl)  CAL_CMGETAPI( "SysTargetGetProcessorId" ) 
	#define CAL_SysTargetGetProcessorId  SysTargetGetProcessorId
	#define CHK_SysTargetGetProcessorId  TRUE
	#define EXP_SysTargetGetProcessorId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetProcessorId", (RTS_UINTPTR)SysTargetGetProcessorId, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetSysTargetGetProcessorId
	#define EXT_SysTargetSysTargetGetProcessorId
	#define GET_SysTargetSysTargetGetProcessorId  ERR_OK
	#define CAL_SysTargetSysTargetGetProcessorId pISysTarget->ISysTargetGetProcessorId
	#define CHK_SysTargetSysTargetGetProcessorId (pISysTarget != NULL)
	#define EXP_SysTargetSysTargetGetProcessorId  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTargetGetProcessorId
	#define EXT_SysTargetGetProcessorId
	#define GET_SysTargetGetProcessorId(fl)  CAL_CMGETAPI( "SysTargetGetProcessorId" ) 
	#define CAL_SysTargetGetProcessorId pISysTarget->ISysTargetGetProcessorId
	#define CHK_SysTargetGetProcessorId (pISysTarget != NULL)
	#define EXP_SysTargetGetProcessorId  CAL_CMEXPAPI( "SysTargetGetProcessorId" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTargetGetProcessorId  PFSYSTARGETGETPROCESSORID pfSysTargetGetProcessorId;
	#define EXT_SysTargetGetProcessorId  extern PFSYSTARGETGETPROCESSORID pfSysTargetGetProcessorId;
	#define GET_SysTargetGetProcessorId(fl)  s_pfCMGetAPI2( "SysTargetGetProcessorId", (RTS_VOID_FCTPTR *)&pfSysTargetGetProcessorId, (fl), 0, 0)
	#define CAL_SysTargetGetProcessorId  pfSysTargetGetProcessorId
	#define CHK_SysTargetGetProcessorId  (pfSysTargetGetProcessorId != NULL)
	#define EXP_SysTargetGetProcessorId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetProcessorId", (RTS_UINTPTR)SysTargetGetProcessorId, 0, 0) 
#endif




/**
 * <description>Returns a unique serial number of the target. Unique serial number can be used e.g. for detection or communication needs (e. g. as part of node name).
 * <p>IMPLEMENTATION NOTES:</p>
 * The length of the serial number string must be limited to SYSTARGET_MAX_SERIAL_NUMBER_LEN characters including NULL termination! 
 *
 *	Example:	"C4D7F967-00020655-00100800-029AF2C4"
 *
 *	If ppszSerialNumber==NULL, the length of the serial number including NULL can be retrieved in *pnMaxLen.
 *	If *ppszSerialNumber==NULL, the pointer will be set to the static serial number. *pnMaxLen returns the real length of the serial number including NULL.
 *	If *ppszSerialNumber!=NULL, the serial number will be written into the buffer. *pnMaxLen must specify the max length of the buffer! On return it contains the
 *  number of characters copied into the buffer including the trailing zero.
 * </description>
 * <param name="ppszSerialNumber" type="INOUT" range="[0,VALID_SN_P_NULL,VALID_SN_P_VALID]">Pointer to pointer to serial number.
 *	<ul>
 *		<li>If ppszSerialNumber==NULL, the length of the serial number can be retrieved in *pnMaxLen.</li>
 *		<li>If *ppszSerialNumber==NULL, the pointer will be set to the static serial nubmer. *pnMaxLen contains the real length of the serial number.</li>
 *		<li>If *ppszSerialNumber!=NULL, the serial number will be written into the buffer. *pnMaxLen must specify the max length of the buffer!</li>
 *	</ul>	
 * </param>
 * <param name="pnMaxLen" type="INOUT" range="[0,VALID_MAX_LEN]">Pointer to the max length of the string (if *ppszSerialNumber!=NULL). On return it contains returned length including NULL.</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">SN was retrieved successful</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Pointer to MaxLen may not be null</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">SN could not be retrieved</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">SN not implemented</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOT_SUPPORTED">Kind of SN not supported</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysTargetGetSerialNumber(char **ppszSerialNumber, RTS_I32 *pnMaxLen);
typedef RTS_RESULT (CDECL * PFSYSTARGETGETSERIALNUMBER) (char **ppszSerialNumber, RTS_I32 *pnMaxLen);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETSERIALNUMBER_NOTIMPLEMENTED)
	#define USE_SysTargetGetSerialNumber
	#define EXT_SysTargetGetSerialNumber
	#define GET_SysTargetGetSerialNumber(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTargetGetSerialNumber(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTargetGetSerialNumber  FALSE
	#define EXP_SysTargetGetSerialNumber  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTargetGetSerialNumber
	#define EXT_SysTargetGetSerialNumber
	#define GET_SysTargetGetSerialNumber(fl)  CAL_CMGETAPI( "SysTargetGetSerialNumber" ) 
	#define CAL_SysTargetGetSerialNumber  SysTargetGetSerialNumber
	#define CHK_SysTargetGetSerialNumber  TRUE
	#define EXP_SysTargetGetSerialNumber  CAL_CMEXPAPI( "SysTargetGetSerialNumber" ) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_SysTargetGetSerialNumber
	#define EXT_SysTargetGetSerialNumber
	#define GET_SysTargetGetSerialNumber(fl)  CAL_CMGETAPI( "SysTargetGetSerialNumber" ) 
	#define CAL_SysTargetGetSerialNumber  SysTargetGetSerialNumber
	#define CHK_SysTargetGetSerialNumber  TRUE
	#define EXP_SysTargetGetSerialNumber  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetSerialNumber", (RTS_UINTPTR)SysTargetGetSerialNumber, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetSysTargetGetSerialNumber
	#define EXT_SysTargetSysTargetGetSerialNumber
	#define GET_SysTargetSysTargetGetSerialNumber  ERR_OK
	#define CAL_SysTargetSysTargetGetSerialNumber pISysTarget->ISysTargetGetSerialNumber
	#define CHK_SysTargetSysTargetGetSerialNumber (pISysTarget != NULL)
	#define EXP_SysTargetSysTargetGetSerialNumber  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTargetGetSerialNumber
	#define EXT_SysTargetGetSerialNumber
	#define GET_SysTargetGetSerialNumber(fl)  CAL_CMGETAPI( "SysTargetGetSerialNumber" ) 
	#define CAL_SysTargetGetSerialNumber pISysTarget->ISysTargetGetSerialNumber
	#define CHK_SysTargetGetSerialNumber (pISysTarget != NULL)
	#define EXP_SysTargetGetSerialNumber  CAL_CMEXPAPI( "SysTargetGetSerialNumber" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTargetGetSerialNumber  PFSYSTARGETGETSERIALNUMBER pfSysTargetGetSerialNumber;
	#define EXT_SysTargetGetSerialNumber  extern PFSYSTARGETGETSERIALNUMBER pfSysTargetGetSerialNumber;
	#define GET_SysTargetGetSerialNumber(fl)  s_pfCMGetAPI2( "SysTargetGetSerialNumber", (RTS_VOID_FCTPTR *)&pfSysTargetGetSerialNumber, (fl), 0, 0)
	#define CAL_SysTargetGetSerialNumber  pfSysTargetGetSerialNumber
	#define CHK_SysTargetGetSerialNumber  (pfSysTargetGetSerialNumber != NULL)
	#define EXP_SysTargetGetSerialNumber  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetSerialNumber", (RTS_UINTPTR)SysTargetGetSerialNumber, 0, 0) 
#endif




/**
 * <description>Returns a _secure_ serial number of the target. Secure means here are unique serial number that can be used e.g. for licensing!
 * <p>IMPLEMENTATION NOTES:</p>
 * - The length of the serial number string must be limited to 512 characters! It is recommended to limit the length to 64 characters.
 * - The serial number must be robust against cracking!!! Typically it should be determined from a unique hardware serial number (device serial number, CPU serial number etc.).
 *	 If this is not available, it must be calculated out of hardware unique characteristics (harddisk serial number + operating system serial number + CPU type + BIOS type etc.)
 *
 *	Example:	"C4D7F967-00020655-00100800-029AF2C4"
 *
 *	If ppszSerialNumber==NULL, the length of the serial number can be retrieved in *pnMaxLen.
 *	If *ppszSerialNumber==NULL, the pointer will be set to the static serial nubmer. *pnMaxLen contains the real length of the serial number.
 *	If *ppszSerialNumber!=NULL, the serial number will be written into the buffer. *pnMaxLen must specify the max length of the buffer!
 * </description>
 * <param name="ppszSerialNumber" type="INOUT" range="[0,VALID_SN_P_NULL,VALID_SN_P_VALID]">Pointer to pointer to serial number.
 *	<ul>
 *		<li>If ppszSerialNumber==NULL, the length of the serial number can be retrieved in *pnMaxLen.</li>
 *		<li>If *ppszSerialNumber==NULL, the pointer will be set to the static serial nubmer. *pnMaxLen contains the real length of the serial number.</li>
 *		<li>If *ppszSerialNumber!=NULL, the serial number will be written into the buffer. *pnMaxLen must specify the max length of the buffer!</li>
 *	</ul>	
 * </param>
 * <param name="pnMaxLen" type="INOUT" range="[0,VALID_MAX_LEN]">Pointer to the max length of the string (if *ppszSerialNumber!=NULL) or the length that is returned by the function.</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">SN was retrieved successful</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Pointer to MaxLen may not be null</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Error retrieving SN</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">SN not implemented</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOT_SUPPORTED">Kind of SN not supported</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysTargetGetSerialNumber_Secure(char **ppszSerialNumber, RTS_I32 *pnMaxLen);
typedef RTS_RESULT (CDECL * PFSYSTARGETGETSERIALNUMBER_SECURE) (char **ppszSerialNumber, RTS_I32 *pnMaxLen);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETSERIALNUMBER_SECURE_NOTIMPLEMENTED)
	#define USE_SysTargetGetSerialNumber_Secure
	#define EXT_SysTargetGetSerialNumber_Secure
	#define GET_SysTargetGetSerialNumber_Secure(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTargetGetSerialNumber_Secure(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTargetGetSerialNumber_Secure  FALSE
	#define EXP_SysTargetGetSerialNumber_Secure  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTargetGetSerialNumber_Secure
	#define EXT_SysTargetGetSerialNumber_Secure
	#define GET_SysTargetGetSerialNumber_Secure(fl)  CAL_CMGETAPI( "SysTargetGetSerialNumber_Secure" ) 
	#define CAL_SysTargetGetSerialNumber_Secure  SysTargetGetSerialNumber_Secure
	#define CHK_SysTargetGetSerialNumber_Secure  TRUE
	#define EXP_SysTargetGetSerialNumber_Secure  CAL_CMEXPAPI( "SysTargetGetSerialNumber_Secure" ) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_SysTargetGetSerialNumber_Secure
	#define EXT_SysTargetGetSerialNumber_Secure
	#define GET_SysTargetGetSerialNumber_Secure(fl)  CAL_CMGETAPI( "SysTargetGetSerialNumber_Secure" ) 
	#define CAL_SysTargetGetSerialNumber_Secure  SysTargetGetSerialNumber_Secure
	#define CHK_SysTargetGetSerialNumber_Secure  TRUE
	#define EXP_SysTargetGetSerialNumber_Secure  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetSerialNumber_Secure", (RTS_UINTPTR)SysTargetGetSerialNumber_Secure, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetSysTargetGetSerialNumber_Secure
	#define EXT_SysTargetSysTargetGetSerialNumber_Secure
	#define GET_SysTargetSysTargetGetSerialNumber_Secure  ERR_OK
	#define CAL_SysTargetSysTargetGetSerialNumber_Secure pISysTarget->ISysTargetGetSerialNumber_Secure
	#define CHK_SysTargetSysTargetGetSerialNumber_Secure (pISysTarget != NULL)
	#define EXP_SysTargetSysTargetGetSerialNumber_Secure  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTargetGetSerialNumber_Secure
	#define EXT_SysTargetGetSerialNumber_Secure
	#define GET_SysTargetGetSerialNumber_Secure(fl)  CAL_CMGETAPI( "SysTargetGetSerialNumber_Secure" ) 
	#define CAL_SysTargetGetSerialNumber_Secure pISysTarget->ISysTargetGetSerialNumber_Secure
	#define CHK_SysTargetGetSerialNumber_Secure (pISysTarget != NULL)
	#define EXP_SysTargetGetSerialNumber_Secure  CAL_CMEXPAPI( "SysTargetGetSerialNumber_Secure" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTargetGetSerialNumber_Secure  PFSYSTARGETGETSERIALNUMBER_SECURE pfSysTargetGetSerialNumber_Secure;
	#define EXT_SysTargetGetSerialNumber_Secure  extern PFSYSTARGETGETSERIALNUMBER_SECURE pfSysTargetGetSerialNumber_Secure;
	#define GET_SysTargetGetSerialNumber_Secure(fl)  s_pfCMGetAPI2( "SysTargetGetSerialNumber_Secure", (RTS_VOID_FCTPTR *)&pfSysTargetGetSerialNumber_Secure, (fl), 0, 0)
	#define CAL_SysTargetGetSerialNumber_Secure  pfSysTargetGetSerialNumber_Secure
	#define CHK_SysTargetGetSerialNumber_Secure  (pfSysTargetGetSerialNumber_Secure != NULL)
	#define EXP_SysTargetGetSerialNumber_Secure  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetSerialNumber_Secure", (RTS_UINTPTR)SysTargetGetSerialNumber_Secure, 0, 0) 
#endif




/**
 * <description>Returns the signature of SysTarget</description>
 * <param name="ulChallenge" type="IN" range="[0,VALID_CHALLENGE]">Challenge to get the signature</param>
 * <param name="pulSignature" type="INOUT" range="[0,VALID_SIGNATURE,INVALID_SIGNATURE]">Signature of the SysTarget entries Type, Id, OperatingSystem, ProcessorType</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Signature was retrieved sucessfull</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Pointer to Signature and ulChallenge may not be null</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Signature could not be retrieved</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysTargetGetSignature(RTS_UI32 ulChallenge, RTS_UI32 *pulSignature);
typedef RTS_RESULT (CDECL * PFSYSTARGETGETSIGNATURE) (RTS_UI32 ulChallenge, RTS_UI32 *pulSignature);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETSIGNATURE_NOTIMPLEMENTED)
	#define USE_SysTargetGetSignature
	#define EXT_SysTargetGetSignature
	#define GET_SysTargetGetSignature(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTargetGetSignature(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTargetGetSignature  FALSE
	#define EXP_SysTargetGetSignature  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTargetGetSignature
	#define EXT_SysTargetGetSignature
	#define GET_SysTargetGetSignature(fl)  CAL_CMGETAPI( "SysTargetGetSignature" ) 
	#define CAL_SysTargetGetSignature  SysTargetGetSignature
	#define CHK_SysTargetGetSignature  TRUE
	#define EXP_SysTargetGetSignature  CAL_CMEXPAPI( "SysTargetGetSignature" ) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_SysTargetGetSignature
	#define EXT_SysTargetGetSignature
	#define GET_SysTargetGetSignature(fl)  CAL_CMGETAPI( "SysTargetGetSignature" ) 
	#define CAL_SysTargetGetSignature  SysTargetGetSignature
	#define CHK_SysTargetGetSignature  TRUE
	#define EXP_SysTargetGetSignature  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetSignature", (RTS_UINTPTR)SysTargetGetSignature, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetSysTargetGetSignature
	#define EXT_SysTargetSysTargetGetSignature
	#define GET_SysTargetSysTargetGetSignature  ERR_OK
	#define CAL_SysTargetSysTargetGetSignature pISysTarget->ISysTargetGetSignature
	#define CHK_SysTargetSysTargetGetSignature (pISysTarget != NULL)
	#define EXP_SysTargetSysTargetGetSignature  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTargetGetSignature
	#define EXT_SysTargetGetSignature
	#define GET_SysTargetGetSignature(fl)  CAL_CMGETAPI( "SysTargetGetSignature" ) 
	#define CAL_SysTargetGetSignature pISysTarget->ISysTargetGetSignature
	#define CHK_SysTargetGetSignature (pISysTarget != NULL)
	#define EXP_SysTargetGetSignature  CAL_CMEXPAPI( "SysTargetGetSignature" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTargetGetSignature  PFSYSTARGETGETSIGNATURE pfSysTargetGetSignature;
	#define EXT_SysTargetGetSignature  extern PFSYSTARGETGETSIGNATURE pfSysTargetGetSignature;
	#define GET_SysTargetGetSignature(fl)  s_pfCMGetAPI2( "SysTargetGetSignature", (RTS_VOID_FCTPTR *)&pfSysTargetGetSignature, (fl), 0, 0)
	#define CAL_SysTargetGetSignature  pfSysTargetGetSignature
	#define CHK_SysTargetGetSignature  (pfSysTargetGetSignature != NULL)
	#define EXP_SysTargetGetSignature  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetSignature", (RTS_UINTPTR)SysTargetGetSignature, 0, 0) 
#endif




/**
 * <description>Returns the device mask. It is used to use the same signature for a range of devices.
 *	Example:
 *		*pusDeviceMask = 0x0000: All parts of the DeviceID is used to generate the signature
 *		*pusDeviceMask = 0x00FF: Only the high BYTE of the DeviceID is used to generate the signature. So a range of 255 devices can be used with the same signature.
 * </description>
 * <param name="pusDeviceMask" type="INOUT" range="[0,P_VALID_DEVICE_MASK]">Pointer to return the device mask</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">device mask was retrieved sucessfull</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Pointer to device mask may not be null</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">device mask could not be retrieved</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysTargetGetDeviceMask(RTS_UI16 *pusDeviceMask);
typedef RTS_RESULT (CDECL * PFSYSTARGETGETDEVICEMASK) (RTS_UI16 *pusDeviceMask);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETDEVICEMASK_NOTIMPLEMENTED)
	#define USE_SysTargetGetDeviceMask
	#define EXT_SysTargetGetDeviceMask
	#define GET_SysTargetGetDeviceMask(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTargetGetDeviceMask(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTargetGetDeviceMask  FALSE
	#define EXP_SysTargetGetDeviceMask  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTargetGetDeviceMask
	#define EXT_SysTargetGetDeviceMask
	#define GET_SysTargetGetDeviceMask(fl)  CAL_CMGETAPI( "SysTargetGetDeviceMask" ) 
	#define CAL_SysTargetGetDeviceMask  SysTargetGetDeviceMask
	#define CHK_SysTargetGetDeviceMask  TRUE
	#define EXP_SysTargetGetDeviceMask  CAL_CMEXPAPI( "SysTargetGetDeviceMask" ) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_SysTargetGetDeviceMask
	#define EXT_SysTargetGetDeviceMask
	#define GET_SysTargetGetDeviceMask(fl)  CAL_CMGETAPI( "SysTargetGetDeviceMask" ) 
	#define CAL_SysTargetGetDeviceMask  SysTargetGetDeviceMask
	#define CHK_SysTargetGetDeviceMask  TRUE
	#define EXP_SysTargetGetDeviceMask  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetDeviceMask", (RTS_UINTPTR)SysTargetGetDeviceMask, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetSysTargetGetDeviceMask
	#define EXT_SysTargetSysTargetGetDeviceMask
	#define GET_SysTargetSysTargetGetDeviceMask  ERR_OK
	#define CAL_SysTargetSysTargetGetDeviceMask pISysTarget->ISysTargetGetDeviceMask
	#define CHK_SysTargetSysTargetGetDeviceMask (pISysTarget != NULL)
	#define EXP_SysTargetSysTargetGetDeviceMask  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTargetGetDeviceMask
	#define EXT_SysTargetGetDeviceMask
	#define GET_SysTargetGetDeviceMask(fl)  CAL_CMGETAPI( "SysTargetGetDeviceMask" ) 
	#define CAL_SysTargetGetDeviceMask pISysTarget->ISysTargetGetDeviceMask
	#define CHK_SysTargetGetDeviceMask (pISysTarget != NULL)
	#define EXP_SysTargetGetDeviceMask  CAL_CMEXPAPI( "SysTargetGetDeviceMask" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTargetGetDeviceMask  PFSYSTARGETGETDEVICEMASK pfSysTargetGetDeviceMask;
	#define EXT_SysTargetGetDeviceMask  extern PFSYSTARGETGETDEVICEMASK pfSysTargetGetDeviceMask;
	#define GET_SysTargetGetDeviceMask(fl)  s_pfCMGetAPI2( "SysTargetGetDeviceMask", (RTS_VOID_FCTPTR *)&pfSysTargetGetDeviceMask, (fl), 0, 0)
	#define CAL_SysTargetGetDeviceMask  pfSysTargetGetDeviceMask
	#define CHK_SysTargetGetDeviceMask  (pfSysTargetGetDeviceMask != NULL)
	#define EXP_SysTargetGetDeviceMask  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetDeviceMask", (RTS_UINTPTR)SysTargetGetDeviceMask, 0, 0) 
#endif




/**
 * <description>Checks the compatibility between a requested identification and the target identification</description>
 * <param name="pTargetIdentReq" type="IN">Requested target identification to check. Must not be NULL!</param>
 * <param name="pTargetIdent" type="IN">Own target identity. Can be NULL, then the built in target identification is used</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Target identifications matched</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pTargetIdentReq is NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_TYPE_MISMATCH">Type mismatch</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_ID_MISMATCH">ID mismatch</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_VERSION_MISMATCH">Version mismatch. Versions not compatible!</errorcode>
 */
RTS_RESULT CDECL SysTargetCheckIdent(SysTargetIdent *pTargetIdentReq, SysTargetIdent *pTargetIdent);
typedef RTS_RESULT (CDECL * PFSYSTARGETCHECKIDENT) (SysTargetIdent *pTargetIdentReq, SysTargetIdent *pTargetIdent);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETCHECKIDENT_NOTIMPLEMENTED)
	#define USE_SysTargetCheckIdent
	#define EXT_SysTargetCheckIdent
	#define GET_SysTargetCheckIdent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTargetCheckIdent(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTargetCheckIdent  FALSE
	#define EXP_SysTargetCheckIdent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTargetCheckIdent
	#define EXT_SysTargetCheckIdent
	#define GET_SysTargetCheckIdent(fl)  CAL_CMGETAPI( "SysTargetCheckIdent" ) 
	#define CAL_SysTargetCheckIdent  SysTargetCheckIdent
	#define CHK_SysTargetCheckIdent  TRUE
	#define EXP_SysTargetCheckIdent  CAL_CMEXPAPI( "SysTargetCheckIdent" ) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_SysTargetCheckIdent
	#define EXT_SysTargetCheckIdent
	#define GET_SysTargetCheckIdent(fl)  CAL_CMGETAPI( "SysTargetCheckIdent" ) 
	#define CAL_SysTargetCheckIdent  SysTargetCheckIdent
	#define CHK_SysTargetCheckIdent  TRUE
	#define EXP_SysTargetCheckIdent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetCheckIdent", (RTS_UINTPTR)SysTargetCheckIdent, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetSysTargetCheckIdent
	#define EXT_SysTargetSysTargetCheckIdent
	#define GET_SysTargetSysTargetCheckIdent  ERR_OK
	#define CAL_SysTargetSysTargetCheckIdent pISysTarget->ISysTargetCheckIdent
	#define CHK_SysTargetSysTargetCheckIdent (pISysTarget != NULL)
	#define EXP_SysTargetSysTargetCheckIdent  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTargetCheckIdent
	#define EXT_SysTargetCheckIdent
	#define GET_SysTargetCheckIdent(fl)  CAL_CMGETAPI( "SysTargetCheckIdent" ) 
	#define CAL_SysTargetCheckIdent pISysTarget->ISysTargetCheckIdent
	#define CHK_SysTargetCheckIdent (pISysTarget != NULL)
	#define EXP_SysTargetCheckIdent  CAL_CMEXPAPI( "SysTargetCheckIdent" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTargetCheckIdent  PFSYSTARGETCHECKIDENT pfSysTargetCheckIdent;
	#define EXT_SysTargetCheckIdent  extern PFSYSTARGETCHECKIDENT pfSysTargetCheckIdent;
	#define GET_SysTargetCheckIdent(fl)  s_pfCMGetAPI2( "SysTargetCheckIdent", (RTS_VOID_FCTPTR *)&pfSysTargetCheckIdent, (fl), 0, 0)
	#define CAL_SysTargetCheckIdent  pfSysTargetCheckIdent
	#define CHK_SysTargetCheckIdent  (pfSysTargetCheckIdent != NULL)
	#define EXP_SysTargetCheckIdent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetCheckIdent", (RTS_UINTPTR)SysTargetCheckIdent, 0, 0) 
#endif




/**
 * <description>This function is called for all external function calls and can be used to overload external functions.
 * <p>IMPLEMENTATION NOTES:</p> 
 * The OEM can use the implementation in SysTargetOEM to redirect or disable specific functions.
 * </description>
 * <param name="apiInfo" type="IN">API info of the current API function to resolve</param>
 * <param name="ppfAPIFunction" type="INOUT">Pointer to API functionpointer</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">API function successfully redirected to the function that *ppfAPIFunction is pointing to</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOT_SUPPORTED">API function is disabled for external calls. Unresolved reference will occur.</errorcode> 
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Pointer to API functionpointer is NULL</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">API function is not overloaded or redirected by SysTargetGetAPI</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">No implementation to resolve the API</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysTargetGetAPI(API_RESOLVE_INFO apiInfo, RTS_VOID_FCTPTR *ppfAPIFunction);
typedef RTS_RESULT (CDECL * PFSYSTARGETGETAPI) (API_RESOLVE_INFO apiInfo, RTS_VOID_FCTPTR *ppfAPIFunction);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETGETAPI_NOTIMPLEMENTED)
	#define USE_SysTargetGetAPI
	#define EXT_SysTargetGetAPI
	#define GET_SysTargetGetAPI(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTargetGetAPI(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTargetGetAPI  FALSE
	#define EXP_SysTargetGetAPI  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTargetGetAPI
	#define EXT_SysTargetGetAPI
	#define GET_SysTargetGetAPI(fl)  CAL_CMGETAPI( "SysTargetGetAPI" ) 
	#define CAL_SysTargetGetAPI  SysTargetGetAPI
	#define CHK_SysTargetGetAPI  TRUE
	#define EXP_SysTargetGetAPI  CAL_CMEXPAPI( "SysTargetGetAPI" ) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_SysTargetGetAPI
	#define EXT_SysTargetGetAPI
	#define GET_SysTargetGetAPI(fl)  CAL_CMGETAPI( "SysTargetGetAPI" ) 
	#define CAL_SysTargetGetAPI  SysTargetGetAPI
	#define CHK_SysTargetGetAPI  TRUE
	#define EXP_SysTargetGetAPI  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetAPI", (RTS_UINTPTR)SysTargetGetAPI, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetSysTargetGetAPI
	#define EXT_SysTargetSysTargetGetAPI
	#define GET_SysTargetSysTargetGetAPI  ERR_OK
	#define CAL_SysTargetSysTargetGetAPI pISysTarget->ISysTargetGetAPI
	#define CHK_SysTargetSysTargetGetAPI (pISysTarget != NULL)
	#define EXP_SysTargetSysTargetGetAPI  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTargetGetAPI
	#define EXT_SysTargetGetAPI
	#define GET_SysTargetGetAPI(fl)  CAL_CMGETAPI( "SysTargetGetAPI" ) 
	#define CAL_SysTargetGetAPI pISysTarget->ISysTargetGetAPI
	#define CHK_SysTargetGetAPI (pISysTarget != NULL)
	#define EXP_SysTargetGetAPI  CAL_CMEXPAPI( "SysTargetGetAPI" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTargetGetAPI  PFSYSTARGETGETAPI pfSysTargetGetAPI;
	#define EXT_SysTargetGetAPI  extern PFSYSTARGETGETAPI pfSysTargetGetAPI;
	#define GET_SysTargetGetAPI(fl)  s_pfCMGetAPI2( "SysTargetGetAPI", (RTS_VOID_FCTPTR *)&pfSysTargetGetAPI, (fl), 0, 0)
	#define CAL_SysTargetGetAPI  pfSysTargetGetAPI
	#define CHK_SysTargetGetAPI  (pfSysTargetGetAPI != NULL)
	#define EXP_SysTargetGetAPI  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetGetAPI", (RTS_UINTPTR)SysTargetGetAPI, 0, 0) 
#endif




/**
* <description>
*  Set a human readable name that identifies this device in the network.
*  The length is limited to SYSTARGET_MAX_NODE_NAME_LEN. By passing an empty string, the node name settings are
*  deleted and so the default node name is set again.
* </description>
* <param name="pwszName" type="IN">Buffer that is filled with the name of the node. Type is UTF-16.</param>
* <errorcode name="RTS_RESULT Result" type="ERR_OK">Node name was set sucessfully</errorcode>
* <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Pointer to name may not be null</errorcode>
* <errorcode name="RTS_RESULT Result" type="ERR_OUT_OF_LIMITS">Length of name exceeds SYSTARGET_MAX_NODE_NAME_LEN</errorcode>
* <errorcode name="RTS_RESULT Result" type="ERR_NO_ACCESS_RIGHTS">Configuration (file) is write protected</errorcode>
* <errorcode name="RTS_RESULT Result" type="ERR_NOT_SUPPORTED">Device does not support to store the node name</errorcode>
* <errorcode name="RTS_RESULT Result" type="ERR_OPERATION_DENIED">OEM implementation has denied to store the node name</errorcode>
* <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Name could not be set because of unknown reason</errorcode>
* <result>error code</result>
*/
RTS_RESULT CDECL SysTargetSetNodeName(RTS_WCHAR *pwszName);
typedef RTS_RESULT (CDECL * PFSYSTARGETSETNODENAME) (RTS_WCHAR *pwszName);
#if defined(SYSTARGET_NOTIMPLEMENTED) || defined(SYSTARGETSETNODENAME_NOTIMPLEMENTED)
	#define USE_SysTargetSetNodeName
	#define EXT_SysTargetSetNodeName
	#define GET_SysTargetSetNodeName(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTargetSetNodeName(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysTargetSetNodeName  FALSE
	#define EXP_SysTargetSetNodeName  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTargetSetNodeName
	#define EXT_SysTargetSetNodeName
	#define GET_SysTargetSetNodeName(fl)  CAL_CMGETAPI( "SysTargetSetNodeName" ) 
	#define CAL_SysTargetSetNodeName  SysTargetSetNodeName
	#define CHK_SysTargetSetNodeName  TRUE
	#define EXP_SysTargetSetNodeName  CAL_CMEXPAPI( "SysTargetSetNodeName" ) 
#elif defined(MIXED_LINK) && !defined(SYSTARGET_EXTERNAL)
	#define USE_SysTargetSetNodeName
	#define EXT_SysTargetSetNodeName
	#define GET_SysTargetSetNodeName(fl)  CAL_CMGETAPI( "SysTargetSetNodeName" ) 
	#define CAL_SysTargetSetNodeName  SysTargetSetNodeName
	#define CHK_SysTargetSetNodeName  TRUE
	#define EXP_SysTargetSetNodeName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetSetNodeName", (RTS_UINTPTR)SysTargetSetNodeName, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysTargetSysTargetSetNodeName
	#define EXT_SysTargetSysTargetSetNodeName
	#define GET_SysTargetSysTargetSetNodeName  ERR_OK
	#define CAL_SysTargetSysTargetSetNodeName pISysTarget->ISysTargetSetNodeName
	#define CHK_SysTargetSysTargetSetNodeName (pISysTarget != NULL)
	#define EXP_SysTargetSysTargetSetNodeName  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTargetSetNodeName
	#define EXT_SysTargetSetNodeName
	#define GET_SysTargetSetNodeName(fl)  CAL_CMGETAPI( "SysTargetSetNodeName" ) 
	#define CAL_SysTargetSetNodeName pISysTarget->ISysTargetSetNodeName
	#define CHK_SysTargetSetNodeName (pISysTarget != NULL)
	#define EXP_SysTargetSetNodeName  CAL_CMEXPAPI( "SysTargetSetNodeName" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTargetSetNodeName  PFSYSTARGETSETNODENAME pfSysTargetSetNodeName;
	#define EXT_SysTargetSetNodeName  extern PFSYSTARGETSETNODENAME pfSysTargetSetNodeName;
	#define GET_SysTargetSetNodeName(fl)  s_pfCMGetAPI2( "SysTargetSetNodeName", (RTS_VOID_FCTPTR *)&pfSysTargetSetNodeName, (fl), 0, 0)
	#define CAL_SysTargetSetNodeName  pfSysTargetSetNodeName
	#define CHK_SysTargetSetNodeName  (pfSysTargetSetNodeName != NULL)
	#define EXP_SysTargetSetNodeName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTargetSetNodeName", (RTS_UINTPTR)SysTargetSetNodeName, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSTARGETGETNODENAME ISysTargetGetNodeName;
 	PFSYSTARGETGETCONFIGUREDNODENAME ISysTargetGetConfiguredNodeName;
 	PFSYSTARGETGETTYPE ISysTargetGetType;
 	PFSYSTARGETGETID ISysTargetGetId;
 	PFSYSTARGETGETVERSION ISysTargetGetVersion;
 	PFSYSTARGETGETDEVICENAME ISysTargetGetDeviceName;
 	PFSYSTARGETGETVENDORNAME ISysTargetGetVendorName;
 	PFSYSTARGETGETOPERATINGSYSTEMID ISysTargetGetOperatingSystemId;
 	PFSYSTARGETGETPROCESSORID ISysTargetGetProcessorId;
 	PFSYSTARGETGETSERIALNUMBER ISysTargetGetSerialNumber;
 	PFSYSTARGETGETSERIALNUMBER_SECURE ISysTargetGetSerialNumber_Secure;
 	PFSYSTARGETGETSIGNATURE ISysTargetGetSignature;
 	PFSYSTARGETGETDEVICEMASK ISysTargetGetDeviceMask;
 	PFSYSTARGETCHECKIDENT ISysTargetCheckIdent;
 	PFSYSTARGETGETAPI ISysTargetGetAPI;
 	PFSYSTARGETSETNODENAME ISysTargetSetNodeName;
 } ISysTarget_C;

#ifdef CPLUSPLUS
class ISysTarget : public IBase
{
	public:
		virtual RTS_RESULT CDECL ISysTargetGetNodeName(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength) =0;
		virtual RTS_RESULT CDECL ISysTargetGetConfiguredNodeName(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength) =0;
		virtual RTS_RESULT CDECL ISysTargetGetType(RTS_UI32 *pulType) =0;
		virtual RTS_RESULT CDECL ISysTargetGetId(RTS_UI32 *pulTargetId) =0;
		virtual RTS_RESULT CDECL ISysTargetGetVersion(RTS_UI32 *pulVersion) =0;
		virtual RTS_RESULT CDECL ISysTargetGetDeviceName(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength) =0;
		virtual RTS_RESULT CDECL ISysTargetGetVendorName(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength) =0;
		virtual RTS_RESULT CDECL ISysTargetGetOperatingSystemId(RTS_UI32 *pulOperatingSystemId) =0;
		virtual RTS_RESULT CDECL ISysTargetGetProcessorId(RTS_UI32 *pulProcessorId) =0;
		virtual RTS_RESULT CDECL ISysTargetGetSerialNumber(char **ppszSerialNumber, RTS_I32 *pnMaxLen) =0;
		virtual RTS_RESULT CDECL ISysTargetGetSerialNumber_Secure(char **ppszSerialNumber, RTS_I32 *pnMaxLen) =0;
		virtual RTS_RESULT CDECL ISysTargetGetSignature(RTS_UI32 ulChallenge, RTS_UI32 *pulSignature) =0;
		virtual RTS_RESULT CDECL ISysTargetGetDeviceMask(RTS_UI16 *pusDeviceMask) =0;
		virtual RTS_RESULT CDECL ISysTargetCheckIdent(SysTargetIdent *pTargetIdentReq, SysTargetIdent *pTargetIdent) =0;
		virtual RTS_RESULT CDECL ISysTargetGetAPI(API_RESOLVE_INFO apiInfo, RTS_VOID_FCTPTR *ppfAPIFunction) =0;
		virtual RTS_RESULT CDECL ISysTargetSetNodeName(RTS_WCHAR *pwszName) =0;
};
	#ifndef ITF_SysTarget
		#define ITF_SysTarget static ISysTarget *pISysTarget = NULL;
	#endif
	#define EXTITF_SysTarget
#else	/*CPLUSPLUS*/
	typedef ISysTarget_C		ISysTarget;
	#ifndef ITF_SysTarget
		#define ITF_SysTarget
	#endif
	#define EXTITF_SysTarget
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSTARGETITF_H_*/
