/**
 * <interfacename>SysTarget</interfacename>
 * <description> 
 *	<p>The SysTarget interface is projected to get access to target specific informations. With this informations
 *	a target can be recognized unique in the complete network.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysTarget')

REF_ITF(`CMItf.m4')
REF_ITF(`CmpIoDrvItf.m4')

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

DEF_API(`void',`CDECL',`systargetgetdevicename',`(systargetgetdevicename_struct *p)',1,0x2DEFEA3D,0x03050500)

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

DEF_API(`void',`CDECL',`systargetgetdevicename2',`(systargetgetdevicename2_struct *p)',1,0x332F9AF1,0x03050500)

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

DEF_API(`void',`CDECL',`systargetgetid',`(systargetgetid_struct *p)',1,0x02ED027A,0x03050500)

/**
 * *OBSOLETE*: Only for backward compatibility! Should not be used.
 */
typedef struct tagsystargetgetid2_struct
{
	RTS_IEC_STRING *pszRouterName;		/* VAR_INPUT */	
	RTS_IEC_DWORD *pulTargetId;			/* VAR_INPUT */	
	RTS_IEC_RESULT SysTargetGetId2;		/* VAR_OUTPUT */	
} systargetgetid2_struct;

DEF_API(`void',`CDECL',`systargetgetid2',`(systargetgetid2_struct *p)',1,0xEA1E39C4,0x03050500)

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

DEF_API(`void',`CDECL',`systargetgetnodename',`(systargetgetnodename_struct *p)',1,0xA0044621,0x03050500)

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

DEF_API(`void',`CDECL',`systargetgetnodename2',`(systargetgetnodename2_struct *p)',1,0x72B60F75,0x03050500)

/**
 * <description>Returns the ID of the operating system.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystargetgetoperatingsystemid_struct
{
	RTS_IEC_UDINT *pudiOperatingSystemId;	/* VAR_INPUT */	/* <param name="pudiOperatingSystemID" type="OUT">Pointer to operating system Id. See category "OperatingSystemID"</param> */
	RTS_IEC_RESULT SysTargetGetOperatingSystemId;	/* VAR_OUTPUT */	
} systargetgetoperatingsystemid_struct;

DEF_API(`void',`CDECL',`systargetgetoperatingsystemid',`(systargetgetoperatingsystemid_struct *p)',1,0xC12147F5,0x03050500)

/**
 * <description>Returns the ID of the processor</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystargetgetprocessorid_struct
{
	RTS_IEC_UDINT *pudiProcessorId;		/* VAR_INPUT */	/* <param name="pudiProcessorId" type="OUT">Pointer to processor ID. See category "ProcessorID" above</param> */
	RTS_IEC_RESULT SysTargetGetProcessorId;	/* VAR_OUTPUT */	
} systargetgetprocessorid_struct;

DEF_API(`void',`CDECL',`systargetgetprocessorid',`(systargetgetprocessorid_struct *p)',1,0x1C22A79F,0x03050500)

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

DEF_API(`void',`CDECL',`systargetgetserialnumber',`(systargetgetserialnumber_struct *p)',1,0x0DB18CE9,0x03050500)

/**
 * <description>Returns the target type. See "Device Types" for details.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystargetgettype_struct
{
	RTS_IEC_DWORD *pulType;				/* VAR_INPUT */	/* <param name="pulType" type="OUT">Pointer to target type. See corresponding category "Device Types"</param> */
	RTS_IEC_RESULT SysTargetGetType;	/* VAR_OUTPUT */	
} systargetgettype_struct;

DEF_API(`void',`CDECL',`systargetgettype',`(systargetgettype_struct *p)',1,0x4AD38850,0x03050500)

/**
 * *OBSOLETE*: Only for backward compatibility! Should not be used
 */
typedef struct tagsystargetgettype2_struct
{
	RTS_IEC_STRING *pszRouterName;		/* VAR_INPUT */	
	RTS_IEC_DWORD *pulType;				/* VAR_INPUT */	
	RTS_IEC_RESULT SysTargetGetType2;	/* VAR_OUTPUT */	
} systargetgettype2_struct;

DEF_API(`void',`CDECL',`systargetgettype2',`(systargetgettype2_struct *p)',1,0x5F20D079,0x03050500)

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

DEF_API(`void',`CDECL',`systargetgetvendorname',`(systargetgetvendorname_struct *p)',1,0xC7C8EF60,0x03050500)

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

DEF_API(`void',`CDECL',`systargetgetvendorname2',`(systargetgetvendorname2_struct *p)',1,0xECA5949D,0x03050500)

/**
 * <description>Returns the target version.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystargetgetversion_struct
{
	RTS_IEC_DWORD *pulVersion;			/* VAR_INPUT */	/* <param name="pulVersion" type="OUT">Pointer to version of the target</param> */
	RTS_IEC_RESULT SysTargetGetVersion;	/* VAR_OUTPUT */	
} systargetgetversion_struct;

DEF_API(`void',`CDECL',`systargetgetversion',`(systargetgetversion_struct *p)',1,0x03C80949,0x03050500)

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

DEF_API(`void',`CDECL',`systargetgetversion2',`(systargetgetversion2_struct *p)',1,0x183560B4,0x03050500)

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysTargetGetNodeName',`(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysTargetGetConfiguredNodeName',`(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysTargetGetType',`(RTS_UI32 *pulType)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysTargetGetId',`(RTS_UI32 *pulTargetId)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysTargetGetVersion',`(RTS_UI32 *pulVersion)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysTargetGetDeviceName',`(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysTargetGetVendorName',`(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength)')

/**
 * <description>Returns the ID of the operating system.</description>
 * <param name="pulOperatingSystemID" type="INOUT" range="[0,VALID_OS_ID_POINTER]">Pointer to operating system Id. See category "Operating System" above</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">OS ID was retrieved sucessfull</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Pointer to OS ID may not be null</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">OS ID could not be retrieved</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysTargetGetOperatingSystemId',`(RTS_UI32 *pulOperatingSystemId)')

/**
 * <description>Returns the ID of the processor</description>
 * <param name="pulProcessorID" type="INOUT" range="[0,VALID_CPU_ID_POINTER]">Pointer to processor ID. See category "Processor ID" above</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">CPU ID was retrieved sucessfull</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Pointer to CPU ID may not be null</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">CPU ID could not be retrieved</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysTargetGetProcessorId',`(RTS_UI32 *pulProcessorId)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysTargetGetSerialNumber',`(char **ppszSerialNumber, RTS_I32 *pnMaxLen)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysTargetGetSerialNumber_Secure',`(char **ppszSerialNumber, RTS_I32 *pnMaxLen)')

/**
 * <description>Returns the signature of SysTarget</description>
 * <param name="ulChallenge" type="IN" range="[0,VALID_CHALLENGE]">Challenge to get the signature</param>
 * <param name="pulSignature" type="INOUT" range="[0,VALID_SIGNATURE,INVALID_SIGNATURE]">Signature of the SysTarget entries Type, Id, OperatingSystem, ProcessorType</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Signature was retrieved sucessfull</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Pointer to Signature and ulChallenge may not be null</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Signature could not be retrieved</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysTargetGetSignature',`(RTS_UI32 ulChallenge, RTS_UI32 *pulSignature)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysTargetGetDeviceMask',`(RTS_UI16 *pusDeviceMask)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysTargetCheckIdent',`(SysTargetIdent *pTargetIdentReq, SysTargetIdent *pTargetIdent)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysTargetGetAPI',`(API_RESOLVE_INFO apiInfo, RTS_VOID_FCTPTR *ppfAPIFunction)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysTargetSetNodeName',`(RTS_WCHAR *pwszName)')

#ifdef __cplusplus
}
#endif
