 /**
 * <interfacename>CmpCodeMeter</interfacename>
 * <description></description>
 *
 * <copyright>
 *  (c) 2003-2017 3S-Smart Software Solutions
 * </copyright>
 */


	
	
#ifndef _CMPCODEMETERITF_H_
#define _CMPCODEMETERITF_H_

#include "CmpStd.h"

 

 




#define RTS_CM_PUBLIC_KEY_LEN					64

/**
 * <category>Compiler switch</category>
 * <description>
 *	Compiler switches to enable/disable single features in the component.
 * </description>
 * <element name="RTS_CODEMETER_EMBEDDED">Switch to enable CmCompact on an embedded device.
 *	- WIBU USB Dongles are supported, if they are implemented in the platform specific part (actually VxWorks, Linux and WIndows CE
 *	
 *		NOTE:
 *		This switch must be set on targets on which no WIBU CodeMeter Runtime is available!</element>
 * <element name="RTS_CODEMETER_SOFTLICENSING">Switch to enable CmActLicense / SoftLicense based on the binding value from SysTargetGetSerialNumber_Secure().
 *		NOTE:
 *		This switch must only be set if the target supports a secure serial number that is appropriate for single target licensing!!!
 * </element>
 * <element name="RTS_CODEMETER_DISABLE_USB">Switch to disable WIBU USB dongle support</element>
 * <element name="RTS_CODEMETER_DISABLE_CMCARD">Switch to disable WIBU CF/SD card support</element>
 */


/**
 * <description>3S Firmcodes</description>
 * <element name="RTS_CODEMETER_SOFTLICENSES_FIRMCODE" type="IN">Firmcode for softkey licenses (CmActLicenses)</element>
 * <element name="RTS_CODEMETER_LICENSES_FIRMCODE" type="IN">Firmcode for hardkey licenses (CmDongle)</element>
 * <element name="RTS_CODEMETER_ENCRYPTION_FIRMCODE" type="IN">Firmcode for encryption of the bootproject</element>
 */
#ifndef RTS_CODEMETER_SOFTLICENSES_FIRMCODE
	#define RTS_CODEMETER_SOFTLICENSES_FIRMCODE		5000304
#endif
#ifndef RTS_CODEMETER_LICENSES_FIRMCODE
	#define RTS_CODEMETER_LICENSES_FIRMCODE			101597
#endif
#ifndef RTS_CODEMETER_ENCRYPTION_FIRMCODE
	#define RTS_CODEMETER_ENCRYPTION_FIRMCODE		101599
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>List of wbb files to create empty CmActLicense containers. List of files must be indexed starting with 1.
 *	NOTE:
 *  - Every license vendor must create its own wbb file with the contaning firmcode! And so for every license vendor an empty CmAct license container is created
 *	  as a file on the target!
 *
 * Example:
 *	[CmpCodeMeter]
 *	InitLicenseFile.1=[vendor].wbb
 *	...
 * </description>
 */
#define CODEMKEY_STRING_INIT_LICENSE_FILE					"InitLicenseFile."

/**
 * <description>
 *	This is the name of the 3S-wbb file to create an empty softcontainer!
 * </description>
 */
#ifndef CODEM_3S_INIT_LICENSE_FILE
	#define CODEM_3S_INIT_LICENSE_FILE						"3SLicense.wbb"
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting to specify the directory for all act license files.
 * </description>
 */
#define CODEMKEY_STRING_ACTLICENSE_DIRECTORY				"ActLicenseDirectory"
#ifndef CODEMVALUE_STRING_ACTLICENSE_DIRECTORY_DEFAULT
	#define CODEMVALUE_STRING_ACTLICENSE_DIRECTORY_DEFAULT	"./cmact_licenses"
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to activate installing license container. The wbb files(s) must be registered for that (see setting "InitLicenseFile").
 *	NOTE:
 *	The key is deleted after installing the container!
 * </description>
 */
#define CODEMKEY_INT_INSTALL_CMACT_CONTAINER				"InstallCmActContainer"
#ifndef CODEMVALUE_INT_CMACT_CONTAINER
	#define CODEMVALUE_INT_CMACT_CONTAINER					0
#endif


/**
 * <category>Online services</category>
 * <Description>
 *	Generate list of connected Wibu-Boxes
 * </Description>
 * <service name="SRV_CODEMETER_READ_DONGLE_LIST">
 *	<Request>
 *	</Request>
 *	<Response>
 *		<tag name="TAG_CM_NUM_OF_DONGLES" required="mandatory">[RTS_UI16]: Number of dongles in the reply</tag>
 *		<tag name="TAG_CM_CMPLX_DONGLE" required="mandatory">Complex tag for dongle entry</tag>
 *			<tag name="TAG_CM_DONGLE_HANDLE" required="mandatory">[char*]: Dongle handle. Here we use the serial number as string</tag>
 *			<tag name="TAG_CM_DONGLE_INFOSTRING" required="mandatory">[char*]: Infos string of the dongle </tag>
 *	</Response>
 * </service>
 */
#define SRV_CODEMETER_READ_DONGLE_LIST 0x0001
#define TAG_CM_NUM_OF_DONGLES 0x0001
#define TAG_CM_CMPLX_DONGLE 0x0081
#define TAG_CM_DONGLE_HANDLE 0x0001
#define TAG_CM_DONGLE_INFOSTRING 0x0002

/**
 * <category>Online services</category>
 * <Description>
 *	Generate license information of a Wibu-Box
 * </Description>
 * <service name="SRV_CODEMETER_READ_LIC_PER_DONGLE">
 *	<Request>
 *	</Request>
 *	<Response>
 *		<tag name="TAG_CMREQ_DONGLE_HANDLE" required="mandatory">[char*]: Dongle handle. Here we use the serial number as string</tag>
 *		<tag name="TAG_CM_NUM_OF_LICS" required="mandatory">[RTS_UI16]: Number of licenses</tag>
 *		<tag name="TAG_CM_CMPLX_LICDESC" required="mandatory">Complex tag for license entry</tag>
 *			<tag name="TAG_CM_LIC_NAME" required="mandatory">[char*]: License name</tag>
 *			<tag name="TAG_CM_LIC_COMPANY" required="mandatory">[char*]: Company name</tag>
 *			<tag name="TAG_CM_LIC_FIRMCODE" required="mandatory">[RTS_UI32]: Firm code</tag>
 *			<tag name="TAG_CM_LIC_PRODUCTCODE" required="mandatory">[RTS_UI32]: Product code</tag>
 *			<tag name="TAG_CM_LIC_FEATUREMAP" required="mandatory">[RTS_UI32]: Feature map</tag>
 *			<tag name="TAG_CM_LIC_LICSTATE" required="mandatory">[RTS_UI32]: License state (active/inactive)</tag>
 *			<tag name="TAG_CM_LIC_ACTIVATIONURL" required="mandatory">[char*]: Activation URL</tag>
 *			<tag name="TAG_CM_LIC_DESCRIPTION" required="mandatory">[char*]: Description</tag>
 *	</Response>
 * </service>
 */
#define SRV_CODEMETER_READ_LIC_PER_DONGLE 0x0002
#define TAG_CMREQ_DONGLE_HANDLE 0x0001
#define TAG_CM_NUM_OF_LICS 0x0001
#define TAG_CM_CMPLX_LICDESC 0x0081
#define TAG_CM_LIC_NAME 0x0001
#define TAG_CM_LIC_COMPANY 0x0002
#define TAG_CM_LIC_FIRMCODE 0x0003
#define TAG_CM_LIC_PRODUCTCODE 0x0004
#define TAG_CM_LIC_FEATUREMAP 0x0005
#define TAG_CM_LIC_LICSTATE 0x0006
#define TAG_CM_LIC_ACTIVATIONURL 0x0007
#define TAG_CM_LIC_DESCRIPTION 0x0008

/**
 * <category>Online services</category>
 * <Description>
 *	Generate license information of a Wibu-Box
 * </Description>
 * <service name="SRV_CODEMETER_CREATE_CONTEXT_FILE">
 *	<Request>
 *		<tag name="TAG_CMREQ_DONGLE_HANDLE" required="mandatory">see above</tag>
 *		<tag name="TAG_CMREQ_NUM_FIRMCODE" required="mandatory">[RTS_UI32]: Number of firmcodes</tag>
 *		<tag name="TAG_CMREQ_FIRMCODE" required="optional">[RTS_UI32]: Requested firmcode</tag>
 *	</Request>
 *	<Response>
 *		<tag name="TAG_CM_CONTEXT_FILE_NAME" required="mandatory">[char*]: Name of the generated context file</tag>
 *	</Response>
 * </service>
 */
#define SRV_CODEMETER_CREATE_CONTEXT_FILE 0x0003
#define TAG_CMREQ_NUM_FIRMCODE 0x0002
#define TAG_CMREQ_FIRMCODE 0x0003
#define TAG_CM_CONTEXT_FILE_NAME 0x0001

/**
 * <category>Online services</category>
 * <Description>
 *	Activate an updated context file
 * </Description>
 * <service name="SRV_CODEMETER_ACTIVATE_UPD_CTXT_FILE">
 *	<Request>
 *		<tag name="TAG_CMREQ_CTXT_FILENAME" required="mandatory">see above</tag>
 *		<tag name="TAG_CMREQ_CTXT_DONGLEHANDLE" required="mandatory">[char*]: Dongle handle. Here we use the serial number as string</tag>
 *	</Request>
 *	<Response>
 *	</Response>
 * </service>
 */
#define SRV_CODEMETER_ACTIVATE_UPD_CTXT_FILE 0x0004
#define TAG_CMREQ_CTXT_FILENAME 0x0001
#define TAG_CMREQ_CTXT_DONGLEHANDLE 0x0002
#define TAG_CM_ERROR_RTS_ERROR 0x0001
#define TAG_CM_ERROR_CM_ERROR 0x0002
#define TAG_CM_ERROR_CM_ERROR_TEXT 0x0003


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>RTS_CODEMETER_INFO</description>
 */
typedef struct tagRTS_CODEMETER_INFO
{
	RTS_IEC_BYTE byMajorVersion;		
	RTS_IEC_BYTE byMinorVersion;		
	RTS_IEC_WORD wBoxMask;		
	RTS_IEC_DWORD dwSerialNumber;		
	RTS_IEC_WORD wChipType;		
	RTS_IEC_WORD wSiliconRevision;		
} RTS_CODEMETER_INFO;

/**
 * <description>RTS_CMBOXENTRY</description>
 */
typedef struct tagRTS_CMBOXENTRY
{
	RTS_IEC_WORD musBoxMask;		
	RTS_IEC_UDINT mulBoxSerial;		
	RTS_IEC_UDINT mflFiCtrl;		
	RTS_IEC_UDINT mulFirmCode;		
	RTS_IEC_WORD musFirmAccessCounter;		
	RTS_IEC_WORD musFirmItemRef;		
	RTS_IEC_UDINT mulFirmUpdateCounter;		
	RTS_IEC_UDINT mulFirmPreciseTime;		
	RTS_IEC_WSTRING mausFirmItemText[256];		
	RTS_IEC_UDINT mulProductCode;		
	RTS_IEC_UDINT mulFeatureMap;		
	RTS_IEC_UDINT mulUnitCounter;		
	RTS_IEC_UDINT mulLicenseQuantity;		
	RTS_IEC_WORD musProductItemRef;		
} RTS_CMBOXENTRY;

/**
 * <description>codemclose</description>
 */
typedef struct tagcodemclose_struct
{
	RTS_IEC_HANDLE hCodeMeter;			/* VAR_INPUT */	
	RTS_IEC_RESULT CodeMClose;			/* VAR_OUTPUT */	
} codemclose_struct;

void CDECL CDECL_EXT codemclose(codemclose_struct *p);
typedef void (CDECL CDECL_EXT* PFCODEMCLOSE_IEC) (codemclose_struct *p);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMCLOSE_NOTIMPLEMENTED)
	#define USE_codemclose
	#define EXT_codemclose
	#define GET_codemclose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_codemclose(p0) 
	#define CHK_codemclose  FALSE
	#define EXP_codemclose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_codemclose
	#define EXT_codemclose
	#define GET_codemclose(fl)  CAL_CMGETAPI( "codemclose" ) 
	#define CAL_codemclose  codemclose
	#define CHK_codemclose  TRUE
	#define EXP_codemclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemclose", (RTS_UINTPTR)codemclose, 1, 0x3CEA9D8D, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_codemclose
	#define EXT_codemclose
	#define GET_codemclose(fl)  CAL_CMGETAPI( "codemclose" ) 
	#define CAL_codemclose  codemclose
	#define CHK_codemclose  TRUE
	#define EXP_codemclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemclose", (RTS_UINTPTR)codemclose, 1, 0x3CEA9D8D, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMetercodemclose
	#define EXT_CmpCodeMetercodemclose
	#define GET_CmpCodeMetercodemclose  ERR_OK
	#define CAL_CmpCodeMetercodemclose  codemclose
	#define CHK_CmpCodeMetercodemclose  TRUE
	#define EXP_CmpCodeMetercodemclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemclose", (RTS_UINTPTR)codemclose, 1, 0x3CEA9D8D, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_codemclose
	#define EXT_codemclose
	#define GET_codemclose(fl)  CAL_CMGETAPI( "codemclose" ) 
	#define CAL_codemclose  codemclose
	#define CHK_codemclose  TRUE
	#define EXP_codemclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemclose", (RTS_UINTPTR)codemclose, 1, 0x3CEA9D8D, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_codemclose  PFCODEMCLOSE_IEC pfcodemclose;
	#define EXT_codemclose  extern PFCODEMCLOSE_IEC pfcodemclose;
	#define GET_codemclose(fl)  s_pfCMGetAPI2( "codemclose", (RTS_VOID_FCTPTR *)&pfcodemclose, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x3CEA9D8D, 0x03050500)
	#define CAL_codemclose  pfcodemclose
	#define CHK_codemclose  (pfcodemclose != NULL)
	#define EXP_codemclose   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemclose", (RTS_UINTPTR)codemclose, 1, 0x3CEA9D8D, 0x03050500) 
#endif


/**
 * <description>codemdecrypt</description>
 */
typedef struct tagcodemdecrypt_struct
{
	RTS_IEC_HANDLE hCodeMeter;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiEncryptionCode;	/* VAR_INPUT */	
	RTS_IEC_UDINT ulCRC;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pbyData;				/* VAR_INPUT */	
	RTS_IEC_XWORD nDataLen;				/* VAR_INPUT */	
	RTS_IEC_RESULT CodeMDecrypt;		/* VAR_OUTPUT */	
} codemdecrypt_struct;

void CDECL CDECL_EXT codemdecrypt(codemdecrypt_struct *p);
typedef void (CDECL CDECL_EXT* PFCODEMDECRYPT_IEC) (codemdecrypt_struct *p);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMDECRYPT_NOTIMPLEMENTED)
	#define USE_codemdecrypt
	#define EXT_codemdecrypt
	#define GET_codemdecrypt(fl)  ERR_NOTIMPLEMENTED
	#define CAL_codemdecrypt(p0) 
	#define CHK_codemdecrypt  FALSE
	#define EXP_codemdecrypt  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_codemdecrypt
	#define EXT_codemdecrypt
	#define GET_codemdecrypt(fl)  CAL_CMGETAPI( "codemdecrypt" ) 
	#define CAL_codemdecrypt  codemdecrypt
	#define CHK_codemdecrypt  TRUE
	#define EXP_codemdecrypt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemdecrypt", (RTS_UINTPTR)codemdecrypt, 1, RTSITF_GET_SIGNATURE(0, 0xBB35024D), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_codemdecrypt
	#define EXT_codemdecrypt
	#define GET_codemdecrypt(fl)  CAL_CMGETAPI( "codemdecrypt" ) 
	#define CAL_codemdecrypt  codemdecrypt
	#define CHK_codemdecrypt  TRUE
	#define EXP_codemdecrypt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemdecrypt", (RTS_UINTPTR)codemdecrypt, 1, RTSITF_GET_SIGNATURE(0, 0xBB35024D), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMetercodemdecrypt
	#define EXT_CmpCodeMetercodemdecrypt
	#define GET_CmpCodeMetercodemdecrypt  ERR_OK
	#define CAL_CmpCodeMetercodemdecrypt  codemdecrypt
	#define CHK_CmpCodeMetercodemdecrypt  TRUE
	#define EXP_CmpCodeMetercodemdecrypt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemdecrypt", (RTS_UINTPTR)codemdecrypt, 1, RTSITF_GET_SIGNATURE(0, 0xBB35024D), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_codemdecrypt
	#define EXT_codemdecrypt
	#define GET_codemdecrypt(fl)  CAL_CMGETAPI( "codemdecrypt" ) 
	#define CAL_codemdecrypt  codemdecrypt
	#define CHK_codemdecrypt  TRUE
	#define EXP_codemdecrypt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemdecrypt", (RTS_UINTPTR)codemdecrypt, 1, RTSITF_GET_SIGNATURE(0, 0xBB35024D), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_codemdecrypt  PFCODEMDECRYPT_IEC pfcodemdecrypt;
	#define EXT_codemdecrypt  extern PFCODEMDECRYPT_IEC pfcodemdecrypt;
	#define GET_codemdecrypt(fl)  s_pfCMGetAPI2( "codemdecrypt", (RTS_VOID_FCTPTR *)&pfcodemdecrypt, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xBB35024D), 0x03050500)
	#define CAL_codemdecrypt  pfcodemdecrypt
	#define CHK_codemdecrypt  (pfcodemdecrypt != NULL)
	#define EXP_codemdecrypt   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemdecrypt", (RTS_UINTPTR)codemdecrypt, 1, RTSITF_GET_SIGNATURE(0, 0xBB35024D), 0x03050500) 
#endif


/**
 * <description>codemencrypt</description>
 */
typedef struct tagcodemencrypt_struct
{
	RTS_IEC_HANDLE hCodeMeter;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiEncryptionCode;	/* VAR_INPUT */	
	RTS_IEC_BYTE *pbyData;				/* VAR_INPUT */	
	RTS_IEC_XWORD nDataLen;				/* VAR_INPUT */	
	RTS_IEC_UDINT *ulCRC;				/* VAR_IN_OUT */	
	RTS_IEC_RESULT CodeMEncrypt;		/* VAR_OUTPUT */	
} codemencrypt_struct;

void CDECL CDECL_EXT codemencrypt(codemencrypt_struct *p);
typedef void (CDECL CDECL_EXT* PFCODEMENCRYPT_IEC) (codemencrypt_struct *p);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMENCRYPT_NOTIMPLEMENTED)
	#define USE_codemencrypt
	#define EXT_codemencrypt
	#define GET_codemencrypt(fl)  ERR_NOTIMPLEMENTED
	#define CAL_codemencrypt(p0) 
	#define CHK_codemencrypt  FALSE
	#define EXP_codemencrypt  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_codemencrypt
	#define EXT_codemencrypt
	#define GET_codemencrypt(fl)  CAL_CMGETAPI( "codemencrypt" ) 
	#define CAL_codemencrypt  codemencrypt
	#define CHK_codemencrypt  TRUE
	#define EXP_codemencrypt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemencrypt", (RTS_UINTPTR)codemencrypt, 1, RTSITF_GET_SIGNATURE(0, 0x33A9B633), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_codemencrypt
	#define EXT_codemencrypt
	#define GET_codemencrypt(fl)  CAL_CMGETAPI( "codemencrypt" ) 
	#define CAL_codemencrypt  codemencrypt
	#define CHK_codemencrypt  TRUE
	#define EXP_codemencrypt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemencrypt", (RTS_UINTPTR)codemencrypt, 1, RTSITF_GET_SIGNATURE(0, 0x33A9B633), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMetercodemencrypt
	#define EXT_CmpCodeMetercodemencrypt
	#define GET_CmpCodeMetercodemencrypt  ERR_OK
	#define CAL_CmpCodeMetercodemencrypt  codemencrypt
	#define CHK_CmpCodeMetercodemencrypt  TRUE
	#define EXP_CmpCodeMetercodemencrypt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemencrypt", (RTS_UINTPTR)codemencrypt, 1, RTSITF_GET_SIGNATURE(0, 0x33A9B633), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_codemencrypt
	#define EXT_codemencrypt
	#define GET_codemencrypt(fl)  CAL_CMGETAPI( "codemencrypt" ) 
	#define CAL_codemencrypt  codemencrypt
	#define CHK_codemencrypt  TRUE
	#define EXP_codemencrypt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemencrypt", (RTS_UINTPTR)codemencrypt, 1, RTSITF_GET_SIGNATURE(0, 0x33A9B633), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_codemencrypt  PFCODEMENCRYPT_IEC pfcodemencrypt;
	#define EXT_codemencrypt  extern PFCODEMENCRYPT_IEC pfcodemencrypt;
	#define GET_codemencrypt(fl)  s_pfCMGetAPI2( "codemencrypt", (RTS_VOID_FCTPTR *)&pfcodemencrypt, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x33A9B633), 0x03050500)
	#define CAL_codemencrypt  pfcodemencrypt
	#define CHK_codemencrypt  (pfcodemencrypt != NULL)
	#define EXP_codemencrypt   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemencrypt", (RTS_UINTPTR)codemencrypt, 1, RTSITF_GET_SIGNATURE(0, 0x33A9B633), 0x03050500) 
#endif


/**
 * <description>codemgetcontentbyfirmcode2</description>
 */
typedef struct tagcodemgetcontentbyfirmcode2_struct
{
	RTS_IEC_UDINT duiFirmcode;			/* VAR_INPUT */	
	RTS_IEC_UDINT duiProductcode;		/* VAR_INPUT */	
	RTS_CMBOXENTRY *licenseEntry;		/* VAR_IN_OUT */	
	RTS_IEC_RESULT CodeMGetContentByFirmcode2;	/* VAR_OUTPUT */	
} codemgetcontentbyfirmcode2_struct;

void CDECL CDECL_EXT codemgetcontentbyfirmcode2(codemgetcontentbyfirmcode2_struct *p);
typedef void (CDECL CDECL_EXT* PFCODEMGETCONTENTBYFIRMCODE2_IEC) (codemgetcontentbyfirmcode2_struct *p);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMGETCONTENTBYFIRMCODE2_NOTIMPLEMENTED)
	#define USE_codemgetcontentbyfirmcode2
	#define EXT_codemgetcontentbyfirmcode2
	#define GET_codemgetcontentbyfirmcode2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_codemgetcontentbyfirmcode2(p0) 
	#define CHK_codemgetcontentbyfirmcode2  FALSE
	#define EXP_codemgetcontentbyfirmcode2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_codemgetcontentbyfirmcode2
	#define EXT_codemgetcontentbyfirmcode2
	#define GET_codemgetcontentbyfirmcode2(fl)  CAL_CMGETAPI( "codemgetcontentbyfirmcode2" ) 
	#define CAL_codemgetcontentbyfirmcode2  codemgetcontentbyfirmcode2
	#define CHK_codemgetcontentbyfirmcode2  TRUE
	#define EXP_codemgetcontentbyfirmcode2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetcontentbyfirmcode2", (RTS_UINTPTR)codemgetcontentbyfirmcode2, 1, 0xDCB38C4D, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_codemgetcontentbyfirmcode2
	#define EXT_codemgetcontentbyfirmcode2
	#define GET_codemgetcontentbyfirmcode2(fl)  CAL_CMGETAPI( "codemgetcontentbyfirmcode2" ) 
	#define CAL_codemgetcontentbyfirmcode2  codemgetcontentbyfirmcode2
	#define CHK_codemgetcontentbyfirmcode2  TRUE
	#define EXP_codemgetcontentbyfirmcode2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetcontentbyfirmcode2", (RTS_UINTPTR)codemgetcontentbyfirmcode2, 1, 0xDCB38C4D, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMetercodemgetcontentbyfirmcode2
	#define EXT_CmpCodeMetercodemgetcontentbyfirmcode2
	#define GET_CmpCodeMetercodemgetcontentbyfirmcode2  ERR_OK
	#define CAL_CmpCodeMetercodemgetcontentbyfirmcode2  codemgetcontentbyfirmcode2
	#define CHK_CmpCodeMetercodemgetcontentbyfirmcode2  TRUE
	#define EXP_CmpCodeMetercodemgetcontentbyfirmcode2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetcontentbyfirmcode2", (RTS_UINTPTR)codemgetcontentbyfirmcode2, 1, 0xDCB38C4D, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_codemgetcontentbyfirmcode2
	#define EXT_codemgetcontentbyfirmcode2
	#define GET_codemgetcontentbyfirmcode2(fl)  CAL_CMGETAPI( "codemgetcontentbyfirmcode2" ) 
	#define CAL_codemgetcontentbyfirmcode2  codemgetcontentbyfirmcode2
	#define CHK_codemgetcontentbyfirmcode2  TRUE
	#define EXP_codemgetcontentbyfirmcode2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetcontentbyfirmcode2", (RTS_UINTPTR)codemgetcontentbyfirmcode2, 1, 0xDCB38C4D, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_codemgetcontentbyfirmcode2  PFCODEMGETCONTENTBYFIRMCODE2_IEC pfcodemgetcontentbyfirmcode2;
	#define EXT_codemgetcontentbyfirmcode2  extern PFCODEMGETCONTENTBYFIRMCODE2_IEC pfcodemgetcontentbyfirmcode2;
	#define GET_codemgetcontentbyfirmcode2(fl)  s_pfCMGetAPI2( "codemgetcontentbyfirmcode2", (RTS_VOID_FCTPTR *)&pfcodemgetcontentbyfirmcode2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xDCB38C4D, 0x03050500)
	#define CAL_codemgetcontentbyfirmcode2  pfcodemgetcontentbyfirmcode2
	#define CHK_codemgetcontentbyfirmcode2  (pfcodemgetcontentbyfirmcode2 != NULL)
	#define EXP_codemgetcontentbyfirmcode2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetcontentbyfirmcode2", (RTS_UINTPTR)codemgetcontentbyfirmcode2, 1, 0xDCB38C4D, 0x03050500) 
#endif


/**
 * <description>codemgetexpirationtime</description>
 */
typedef struct tagcodemgetexpirationtime_struct
{
	RTS_IEC_HANDLE hCodeMeter;			/* VAR_INPUT */	
	RTS_IEC_DATE_AND_TIME *dtExpiration;	/* VAR_IN_OUT */	
	RTS_IEC_RESULT CodeMGetExpirationTime;	/* VAR_OUTPUT */	
} codemgetexpirationtime_struct;

void CDECL CDECL_EXT codemgetexpirationtime(codemgetexpirationtime_struct *p);
typedef void (CDECL CDECL_EXT* PFCODEMGETEXPIRATIONTIME_IEC) (codemgetexpirationtime_struct *p);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMGETEXPIRATIONTIME_NOTIMPLEMENTED)
	#define USE_codemgetexpirationtime
	#define EXT_codemgetexpirationtime
	#define GET_codemgetexpirationtime(fl)  ERR_NOTIMPLEMENTED
	#define CAL_codemgetexpirationtime(p0) 
	#define CHK_codemgetexpirationtime  FALSE
	#define EXP_codemgetexpirationtime  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_codemgetexpirationtime
	#define EXT_codemgetexpirationtime
	#define GET_codemgetexpirationtime(fl)  CAL_CMGETAPI( "codemgetexpirationtime" ) 
	#define CAL_codemgetexpirationtime  codemgetexpirationtime
	#define CHK_codemgetexpirationtime  TRUE
	#define EXP_codemgetexpirationtime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetexpirationtime", (RTS_UINTPTR)codemgetexpirationtime, 1, 0x9CC99260, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_codemgetexpirationtime
	#define EXT_codemgetexpirationtime
	#define GET_codemgetexpirationtime(fl)  CAL_CMGETAPI( "codemgetexpirationtime" ) 
	#define CAL_codemgetexpirationtime  codemgetexpirationtime
	#define CHK_codemgetexpirationtime  TRUE
	#define EXP_codemgetexpirationtime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetexpirationtime", (RTS_UINTPTR)codemgetexpirationtime, 1, 0x9CC99260, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMetercodemgetexpirationtime
	#define EXT_CmpCodeMetercodemgetexpirationtime
	#define GET_CmpCodeMetercodemgetexpirationtime  ERR_OK
	#define CAL_CmpCodeMetercodemgetexpirationtime  codemgetexpirationtime
	#define CHK_CmpCodeMetercodemgetexpirationtime  TRUE
	#define EXP_CmpCodeMetercodemgetexpirationtime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetexpirationtime", (RTS_UINTPTR)codemgetexpirationtime, 1, 0x9CC99260, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_codemgetexpirationtime
	#define EXT_codemgetexpirationtime
	#define GET_codemgetexpirationtime(fl)  CAL_CMGETAPI( "codemgetexpirationtime" ) 
	#define CAL_codemgetexpirationtime  codemgetexpirationtime
	#define CHK_codemgetexpirationtime  TRUE
	#define EXP_codemgetexpirationtime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetexpirationtime", (RTS_UINTPTR)codemgetexpirationtime, 1, 0x9CC99260, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_codemgetexpirationtime  PFCODEMGETEXPIRATIONTIME_IEC pfcodemgetexpirationtime;
	#define EXT_codemgetexpirationtime  extern PFCODEMGETEXPIRATIONTIME_IEC pfcodemgetexpirationtime;
	#define GET_codemgetexpirationtime(fl)  s_pfCMGetAPI2( "codemgetexpirationtime", (RTS_VOID_FCTPTR *)&pfcodemgetexpirationtime, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x9CC99260, 0x03050500)
	#define CAL_codemgetexpirationtime  pfcodemgetexpirationtime
	#define CHK_codemgetexpirationtime  (pfcodemgetexpirationtime != NULL)
	#define EXP_codemgetexpirationtime   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetexpirationtime", (RTS_UINTPTR)codemgetexpirationtime, 1, 0x9CC99260, 0x03050500) 
#endif


/**
 * <description>codemgetfirst</description>
 */
typedef struct tagcodemgetfirst_struct
{
	RTS_IEC_RESULT *Result;				/* VAR_IN_OUT */	
	RTS_IEC_HANDLE CodeMGetFirst;		/* VAR_OUTPUT */	
} codemgetfirst_struct;

void CDECL CDECL_EXT codemgetfirst(codemgetfirst_struct *p);
typedef void (CDECL CDECL_EXT* PFCODEMGETFIRST_IEC) (codemgetfirst_struct *p);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMGETFIRST_NOTIMPLEMENTED)
	#define USE_codemgetfirst
	#define EXT_codemgetfirst
	#define GET_codemgetfirst(fl)  ERR_NOTIMPLEMENTED
	#define CAL_codemgetfirst(p0) 
	#define CHK_codemgetfirst  FALSE
	#define EXP_codemgetfirst  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_codemgetfirst
	#define EXT_codemgetfirst
	#define GET_codemgetfirst(fl)  CAL_CMGETAPI( "codemgetfirst" ) 
	#define CAL_codemgetfirst  codemgetfirst
	#define CHK_codemgetfirst  TRUE
	#define EXP_codemgetfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetfirst", (RTS_UINTPTR)codemgetfirst, 1, 0x0276119A, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_codemgetfirst
	#define EXT_codemgetfirst
	#define GET_codemgetfirst(fl)  CAL_CMGETAPI( "codemgetfirst" ) 
	#define CAL_codemgetfirst  codemgetfirst
	#define CHK_codemgetfirst  TRUE
	#define EXP_codemgetfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetfirst", (RTS_UINTPTR)codemgetfirst, 1, 0x0276119A, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMetercodemgetfirst
	#define EXT_CmpCodeMetercodemgetfirst
	#define GET_CmpCodeMetercodemgetfirst  ERR_OK
	#define CAL_CmpCodeMetercodemgetfirst  codemgetfirst
	#define CHK_CmpCodeMetercodemgetfirst  TRUE
	#define EXP_CmpCodeMetercodemgetfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetfirst", (RTS_UINTPTR)codemgetfirst, 1, 0x0276119A, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_codemgetfirst
	#define EXT_codemgetfirst
	#define GET_codemgetfirst(fl)  CAL_CMGETAPI( "codemgetfirst" ) 
	#define CAL_codemgetfirst  codemgetfirst
	#define CHK_codemgetfirst  TRUE
	#define EXP_codemgetfirst  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetfirst", (RTS_UINTPTR)codemgetfirst, 1, 0x0276119A, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_codemgetfirst  PFCODEMGETFIRST_IEC pfcodemgetfirst;
	#define EXT_codemgetfirst  extern PFCODEMGETFIRST_IEC pfcodemgetfirst;
	#define GET_codemgetfirst(fl)  s_pfCMGetAPI2( "codemgetfirst", (RTS_VOID_FCTPTR *)&pfcodemgetfirst, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0276119A, 0x03050500)
	#define CAL_codemgetfirst  pfcodemgetfirst
	#define CHK_codemgetfirst  (pfcodemgetfirst != NULL)
	#define EXP_codemgetfirst   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetfirst", (RTS_UINTPTR)codemgetfirst, 1, 0x0276119A, 0x03050500) 
#endif


/**
 * <description>codemgetinfo</description>
 */
typedef struct tagcodemgetinfo_struct
{
	RTS_IEC_HANDLE hCodeMeter;			/* VAR_INPUT */	
	RTS_CODEMETER_INFO *info;			/* VAR_IN_OUT */	
	RTS_IEC_RESULT CodeMGetInfo;		/* VAR_OUTPUT */	
} codemgetinfo_struct;

void CDECL CDECL_EXT codemgetinfo(codemgetinfo_struct *p);
typedef void (CDECL CDECL_EXT* PFCODEMGETINFO_IEC) (codemgetinfo_struct *p);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMGETINFO_NOTIMPLEMENTED)
	#define USE_codemgetinfo
	#define EXT_codemgetinfo
	#define GET_codemgetinfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_codemgetinfo(p0) 
	#define CHK_codemgetinfo  FALSE
	#define EXP_codemgetinfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_codemgetinfo
	#define EXT_codemgetinfo
	#define GET_codemgetinfo(fl)  CAL_CMGETAPI( "codemgetinfo" ) 
	#define CAL_codemgetinfo  codemgetinfo
	#define CHK_codemgetinfo  TRUE
	#define EXP_codemgetinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetinfo", (RTS_UINTPTR)codemgetinfo, 1, 0x1CD05996, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_codemgetinfo
	#define EXT_codemgetinfo
	#define GET_codemgetinfo(fl)  CAL_CMGETAPI( "codemgetinfo" ) 
	#define CAL_codemgetinfo  codemgetinfo
	#define CHK_codemgetinfo  TRUE
	#define EXP_codemgetinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetinfo", (RTS_UINTPTR)codemgetinfo, 1, 0x1CD05996, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMetercodemgetinfo
	#define EXT_CmpCodeMetercodemgetinfo
	#define GET_CmpCodeMetercodemgetinfo  ERR_OK
	#define CAL_CmpCodeMetercodemgetinfo  codemgetinfo
	#define CHK_CmpCodeMetercodemgetinfo  TRUE
	#define EXP_CmpCodeMetercodemgetinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetinfo", (RTS_UINTPTR)codemgetinfo, 1, 0x1CD05996, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_codemgetinfo
	#define EXT_codemgetinfo
	#define GET_codemgetinfo(fl)  CAL_CMGETAPI( "codemgetinfo" ) 
	#define CAL_codemgetinfo  codemgetinfo
	#define CHK_codemgetinfo  TRUE
	#define EXP_codemgetinfo  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetinfo", (RTS_UINTPTR)codemgetinfo, 1, 0x1CD05996, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_codemgetinfo  PFCODEMGETINFO_IEC pfcodemgetinfo;
	#define EXT_codemgetinfo  extern PFCODEMGETINFO_IEC pfcodemgetinfo;
	#define GET_codemgetinfo(fl)  s_pfCMGetAPI2( "codemgetinfo", (RTS_VOID_FCTPTR *)&pfcodemgetinfo, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x1CD05996, 0x03050500)
	#define CAL_codemgetinfo  pfcodemgetinfo
	#define CHK_codemgetinfo  (pfcodemgetinfo != NULL)
	#define EXP_codemgetinfo   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetinfo", (RTS_UINTPTR)codemgetinfo, 1, 0x1CD05996, 0x03050500) 
#endif


/**
 * <description>codemgetname</description>
 */
typedef struct tagcodemgetname_struct
{
	RTS_IEC_HANDLE hCodeMeter;			/* VAR_INPUT */	
	RTS_IEC_WSTRING *wstName;			/* VAR_IN_OUT */	
	RTS_IEC_UDINT nLenBytes;			/* VAR_INPUT */	
	RTS_IEC_RESULT CodeMGetName;		/* VAR_OUTPUT */	
} codemgetname_struct;

void CDECL CDECL_EXT codemgetname(codemgetname_struct *p);
typedef void (CDECL CDECL_EXT* PFCODEMGETNAME_IEC) (codemgetname_struct *p);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMGETNAME_NOTIMPLEMENTED)
	#define USE_codemgetname
	#define EXT_codemgetname
	#define GET_codemgetname(fl)  ERR_NOTIMPLEMENTED
	#define CAL_codemgetname(p0) 
	#define CHK_codemgetname  FALSE
	#define EXP_codemgetname  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_codemgetname
	#define EXT_codemgetname
	#define GET_codemgetname(fl)  CAL_CMGETAPI( "codemgetname" ) 
	#define CAL_codemgetname  codemgetname
	#define CHK_codemgetname  TRUE
	#define EXP_codemgetname  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetname", (RTS_UINTPTR)codemgetname, 1, 0xC0E6AE1E, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_codemgetname
	#define EXT_codemgetname
	#define GET_codemgetname(fl)  CAL_CMGETAPI( "codemgetname" ) 
	#define CAL_codemgetname  codemgetname
	#define CHK_codemgetname  TRUE
	#define EXP_codemgetname  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetname", (RTS_UINTPTR)codemgetname, 1, 0xC0E6AE1E, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMetercodemgetname
	#define EXT_CmpCodeMetercodemgetname
	#define GET_CmpCodeMetercodemgetname  ERR_OK
	#define CAL_CmpCodeMetercodemgetname  codemgetname
	#define CHK_CmpCodeMetercodemgetname  TRUE
	#define EXP_CmpCodeMetercodemgetname  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetname", (RTS_UINTPTR)codemgetname, 1, 0xC0E6AE1E, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_codemgetname
	#define EXT_codemgetname
	#define GET_codemgetname(fl)  CAL_CMGETAPI( "codemgetname" ) 
	#define CAL_codemgetname  codemgetname
	#define CHK_codemgetname  TRUE
	#define EXP_codemgetname  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetname", (RTS_UINTPTR)codemgetname, 1, 0xC0E6AE1E, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_codemgetname  PFCODEMGETNAME_IEC pfcodemgetname;
	#define EXT_codemgetname  extern PFCODEMGETNAME_IEC pfcodemgetname;
	#define GET_codemgetname(fl)  s_pfCMGetAPI2( "codemgetname", (RTS_VOID_FCTPTR *)&pfcodemgetname, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xC0E6AE1E, 0x03050500)
	#define CAL_codemgetname  pfcodemgetname
	#define CHK_codemgetname  (pfcodemgetname != NULL)
	#define EXP_codemgetname   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetname", (RTS_UINTPTR)codemgetname, 1, 0xC0E6AE1E, 0x03050500) 
#endif


/**
 * <description>codemgetnext</description>
 */
typedef struct tagcodemgetnext_struct
{
	RTS_IEC_HANDLE hPrevCodeMeter;		/* VAR_INPUT */	
	RTS_IEC_RESULT *Result;				/* VAR_IN_OUT */	
	RTS_IEC_HANDLE CodeMGetNext;		/* VAR_OUTPUT */	
} codemgetnext_struct;

void CDECL CDECL_EXT codemgetnext(codemgetnext_struct *p);
typedef void (CDECL CDECL_EXT* PFCODEMGETNEXT_IEC) (codemgetnext_struct *p);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMGETNEXT_NOTIMPLEMENTED)
	#define USE_codemgetnext
	#define EXT_codemgetnext
	#define GET_codemgetnext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_codemgetnext(p0) 
	#define CHK_codemgetnext  FALSE
	#define EXP_codemgetnext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_codemgetnext
	#define EXT_codemgetnext
	#define GET_codemgetnext(fl)  CAL_CMGETAPI( "codemgetnext" ) 
	#define CAL_codemgetnext  codemgetnext
	#define CHK_codemgetnext  TRUE
	#define EXP_codemgetnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetnext", (RTS_UINTPTR)codemgetnext, 1, 0x1E179338, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_codemgetnext
	#define EXT_codemgetnext
	#define GET_codemgetnext(fl)  CAL_CMGETAPI( "codemgetnext" ) 
	#define CAL_codemgetnext  codemgetnext
	#define CHK_codemgetnext  TRUE
	#define EXP_codemgetnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetnext", (RTS_UINTPTR)codemgetnext, 1, 0x1E179338, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMetercodemgetnext
	#define EXT_CmpCodeMetercodemgetnext
	#define GET_CmpCodeMetercodemgetnext  ERR_OK
	#define CAL_CmpCodeMetercodemgetnext  codemgetnext
	#define CHK_CmpCodeMetercodemgetnext  TRUE
	#define EXP_CmpCodeMetercodemgetnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetnext", (RTS_UINTPTR)codemgetnext, 1, 0x1E179338, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_codemgetnext
	#define EXT_codemgetnext
	#define GET_codemgetnext(fl)  CAL_CMGETAPI( "codemgetnext" ) 
	#define CAL_codemgetnext  codemgetnext
	#define CHK_codemgetnext  TRUE
	#define EXP_codemgetnext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetnext", (RTS_UINTPTR)codemgetnext, 1, 0x1E179338, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_codemgetnext  PFCODEMGETNEXT_IEC pfcodemgetnext;
	#define EXT_codemgetnext  extern PFCODEMGETNEXT_IEC pfcodemgetnext;
	#define GET_codemgetnext(fl)  s_pfCMGetAPI2( "codemgetnext", (RTS_VOID_FCTPTR *)&pfcodemgetnext, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x1E179338, 0x03050500)
	#define CAL_codemgetnext  pfcodemgetnext
	#define CHK_codemgetnext  (pfcodemgetnext != NULL)
	#define EXP_codemgetnext   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetnext", (RTS_UINTPTR)codemgetnext, 1, 0x1E179338, 0x03050500) 
#endif


/**
 * <description>codemgetquantity</description>
 */
typedef struct tagcodemgetquantity_struct
{
	RTS_IEC_HANDLE hCodeMeter;			/* VAR_INPUT */	
	RTS_IEC_UDINT *udiQuantity;			/* VAR_IN_OUT */	
	RTS_IEC_RESULT CodeMGetQuantity;	/* VAR_OUTPUT */	
} codemgetquantity_struct;

void CDECL CDECL_EXT codemgetquantity(codemgetquantity_struct *p);
typedef void (CDECL CDECL_EXT* PFCODEMGETQUANTITY_IEC) (codemgetquantity_struct *p);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMGETQUANTITY_NOTIMPLEMENTED)
	#define USE_codemgetquantity
	#define EXT_codemgetquantity
	#define GET_codemgetquantity(fl)  ERR_NOTIMPLEMENTED
	#define CAL_codemgetquantity(p0) 
	#define CHK_codemgetquantity  FALSE
	#define EXP_codemgetquantity  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_codemgetquantity
	#define EXT_codemgetquantity
	#define GET_codemgetquantity(fl)  CAL_CMGETAPI( "codemgetquantity" ) 
	#define CAL_codemgetquantity  codemgetquantity
	#define CHK_codemgetquantity  TRUE
	#define EXP_codemgetquantity  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetquantity", (RTS_UINTPTR)codemgetquantity, 1, 0x82616ACF, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_codemgetquantity
	#define EXT_codemgetquantity
	#define GET_codemgetquantity(fl)  CAL_CMGETAPI( "codemgetquantity" ) 
	#define CAL_codemgetquantity  codemgetquantity
	#define CHK_codemgetquantity  TRUE
	#define EXP_codemgetquantity  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetquantity", (RTS_UINTPTR)codemgetquantity, 1, 0x82616ACF, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMetercodemgetquantity
	#define EXT_CmpCodeMetercodemgetquantity
	#define GET_CmpCodeMetercodemgetquantity  ERR_OK
	#define CAL_CmpCodeMetercodemgetquantity  codemgetquantity
	#define CHK_CmpCodeMetercodemgetquantity  TRUE
	#define EXP_CmpCodeMetercodemgetquantity  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetquantity", (RTS_UINTPTR)codemgetquantity, 1, 0x82616ACF, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_codemgetquantity
	#define EXT_codemgetquantity
	#define GET_codemgetquantity(fl)  CAL_CMGETAPI( "codemgetquantity" ) 
	#define CAL_codemgetquantity  codemgetquantity
	#define CHK_codemgetquantity  TRUE
	#define EXP_codemgetquantity  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetquantity", (RTS_UINTPTR)codemgetquantity, 1, 0x82616ACF, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_codemgetquantity  PFCODEMGETQUANTITY_IEC pfcodemgetquantity;
	#define EXT_codemgetquantity  extern PFCODEMGETQUANTITY_IEC pfcodemgetquantity;
	#define GET_codemgetquantity(fl)  s_pfCMGetAPI2( "codemgetquantity", (RTS_VOID_FCTPTR *)&pfcodemgetquantity, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x82616ACF, 0x03050500)
	#define CAL_codemgetquantity  pfcodemgetquantity
	#define CHK_codemgetquantity  (pfcodemgetquantity != NULL)
	#define EXP_codemgetquantity   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetquantity", (RTS_UINTPTR)codemgetquantity, 1, 0x82616ACF, 0x03050500) 
#endif


/**
 * <description>codemgetunitcounter</description>
 */
typedef struct tagcodemgetunitcounter_struct
{
	RTS_IEC_HANDLE hCodeMeter;			/* VAR_INPUT */	
	RTS_IEC_UDINT *udiUnitCount;		/* VAR_IN_OUT */	
	RTS_IEC_RESULT CodeMGetUnitCounter;	/* VAR_OUTPUT */	
} codemgetunitcounter_struct;

void CDECL CDECL_EXT codemgetunitcounter(codemgetunitcounter_struct *p);
typedef void (CDECL CDECL_EXT* PFCODEMGETUNITCOUNTER_IEC) (codemgetunitcounter_struct *p);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMGETUNITCOUNTER_NOTIMPLEMENTED)
	#define USE_codemgetunitcounter
	#define EXT_codemgetunitcounter
	#define GET_codemgetunitcounter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_codemgetunitcounter(p0) 
	#define CHK_codemgetunitcounter  FALSE
	#define EXP_codemgetunitcounter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_codemgetunitcounter
	#define EXT_codemgetunitcounter
	#define GET_codemgetunitcounter(fl)  CAL_CMGETAPI( "codemgetunitcounter" ) 
	#define CAL_codemgetunitcounter  codemgetunitcounter
	#define CHK_codemgetunitcounter  TRUE
	#define EXP_codemgetunitcounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetunitcounter", (RTS_UINTPTR)codemgetunitcounter, 1, 0xEDA602B2, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_codemgetunitcounter
	#define EXT_codemgetunitcounter
	#define GET_codemgetunitcounter(fl)  CAL_CMGETAPI( "codemgetunitcounter" ) 
	#define CAL_codemgetunitcounter  codemgetunitcounter
	#define CHK_codemgetunitcounter  TRUE
	#define EXP_codemgetunitcounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetunitcounter", (RTS_UINTPTR)codemgetunitcounter, 1, 0xEDA602B2, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMetercodemgetunitcounter
	#define EXT_CmpCodeMetercodemgetunitcounter
	#define GET_CmpCodeMetercodemgetunitcounter  ERR_OK
	#define CAL_CmpCodeMetercodemgetunitcounter  codemgetunitcounter
	#define CHK_CmpCodeMetercodemgetunitcounter  TRUE
	#define EXP_CmpCodeMetercodemgetunitcounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetunitcounter", (RTS_UINTPTR)codemgetunitcounter, 1, 0xEDA602B2, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_codemgetunitcounter
	#define EXT_codemgetunitcounter
	#define GET_codemgetunitcounter(fl)  CAL_CMGETAPI( "codemgetunitcounter" ) 
	#define CAL_codemgetunitcounter  codemgetunitcounter
	#define CHK_codemgetunitcounter  TRUE
	#define EXP_codemgetunitcounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetunitcounter", (RTS_UINTPTR)codemgetunitcounter, 1, 0xEDA602B2, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_codemgetunitcounter  PFCODEMGETUNITCOUNTER_IEC pfcodemgetunitcounter;
	#define EXT_codemgetunitcounter  extern PFCODEMGETUNITCOUNTER_IEC pfcodemgetunitcounter;
	#define GET_codemgetunitcounter(fl)  s_pfCMGetAPI2( "codemgetunitcounter", (RTS_VOID_FCTPTR *)&pfcodemgetunitcounter, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xEDA602B2, 0x03050500)
	#define CAL_codemgetunitcounter  pfcodemgetunitcounter
	#define CHK_codemgetunitcounter  (pfcodemgetunitcounter != NULL)
	#define EXP_codemgetunitcounter   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemgetunitcounter", (RTS_UINTPTR)codemgetunitcounter, 1, 0xEDA602B2, 0x03050500) 
#endif


/**
 * <description>codemopen</description>
 */
typedef struct tagcodemopen_struct
{
	RTS_IEC_UDINT udiFirmCode;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiProductCode;		/* VAR_INPUT */	
	RTS_IEC_UDINT udiFeatureCode;		/* VAR_INPUT */	
	RTS_IEC_RESULT *Result;				/* VAR_IN_OUT */	
	RTS_IEC_HANDLE CodeMOpen;			/* VAR_OUTPUT */	
} codemopen_struct;

void CDECL CDECL_EXT codemopen(codemopen_struct *p);
typedef void (CDECL CDECL_EXT* PFCODEMOPEN_IEC) (codemopen_struct *p);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMOPEN_NOTIMPLEMENTED)
	#define USE_codemopen
	#define EXT_codemopen
	#define GET_codemopen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_codemopen(p0) 
	#define CHK_codemopen  FALSE
	#define EXP_codemopen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_codemopen
	#define EXT_codemopen
	#define GET_codemopen(fl)  CAL_CMGETAPI( "codemopen" ) 
	#define CAL_codemopen  codemopen
	#define CHK_codemopen  TRUE
	#define EXP_codemopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemopen", (RTS_UINTPTR)codemopen, 1, 0x290D791C, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_codemopen
	#define EXT_codemopen
	#define GET_codemopen(fl)  CAL_CMGETAPI( "codemopen" ) 
	#define CAL_codemopen  codemopen
	#define CHK_codemopen  TRUE
	#define EXP_codemopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemopen", (RTS_UINTPTR)codemopen, 1, 0x290D791C, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMetercodemopen
	#define EXT_CmpCodeMetercodemopen
	#define GET_CmpCodeMetercodemopen  ERR_OK
	#define CAL_CmpCodeMetercodemopen  codemopen
	#define CHK_CmpCodeMetercodemopen  TRUE
	#define EXP_CmpCodeMetercodemopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemopen", (RTS_UINTPTR)codemopen, 1, 0x290D791C, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_codemopen
	#define EXT_codemopen
	#define GET_codemopen(fl)  CAL_CMGETAPI( "codemopen" ) 
	#define CAL_codemopen  codemopen
	#define CHK_codemopen  TRUE
	#define EXP_codemopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemopen", (RTS_UINTPTR)codemopen, 1, 0x290D791C, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_codemopen  PFCODEMOPEN_IEC pfcodemopen;
	#define EXT_codemopen  extern PFCODEMOPEN_IEC pfcodemopen;
	#define GET_codemopen(fl)  s_pfCMGetAPI2( "codemopen", (RTS_VOID_FCTPTR *)&pfcodemopen, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x290D791C, 0x03050500)
	#define CAL_codemopen  pfcodemopen
	#define CHK_codemopen  (pfcodemopen != NULL)
	#define EXP_codemopen   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"codemopen", (RTS_UINTPTR)codemopen, 1, 0x290D791C, 0x03050500) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 *	Open the first attached CodeMeter device
 * </description>
 * <param name="pResult" type="OUT">Pointer to error code:
 *   <ul>
 *     <li>ERR_OK: Device found</li>
 *     <li>ERR_NO_OBJECT: No device found</li>
 *   </ul>
 * </param>
 * <result>Returns a handle to the first CodeMeter device or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL CodeMGetFirst(RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFCODEMGETFIRST) (RTS_RESULT *pResult);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMGETFIRST_NOTIMPLEMENTED)
	#define USE_CodeMGetFirst
	#define EXT_CodeMGetFirst
	#define GET_CodeMGetFirst(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CodeMGetFirst(p0)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_CodeMGetFirst  FALSE
	#define EXP_CodeMGetFirst  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CodeMGetFirst
	#define EXT_CodeMGetFirst
	#define GET_CodeMGetFirst(fl)  CAL_CMGETAPI( "CodeMGetFirst" ) 
	#define CAL_CodeMGetFirst  CodeMGetFirst
	#define CHK_CodeMGetFirst  TRUE
	#define EXP_CodeMGetFirst  CAL_CMEXPAPI( "CodeMGetFirst" ) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_CodeMGetFirst
	#define EXT_CodeMGetFirst
	#define GET_CodeMGetFirst(fl)  CAL_CMGETAPI( "CodeMGetFirst" ) 
	#define CAL_CodeMGetFirst  CodeMGetFirst
	#define CHK_CodeMGetFirst  TRUE
	#define EXP_CodeMGetFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMGetFirst", (RTS_UINTPTR)CodeMGetFirst, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMeterCodeMGetFirst
	#define EXT_CmpCodeMeterCodeMGetFirst
	#define GET_CmpCodeMeterCodeMGetFirst  ERR_OK
	#define CAL_CmpCodeMeterCodeMGetFirst pICmpCodeMeter->ICodeMGetFirst
	#define CHK_CmpCodeMeterCodeMGetFirst (pICmpCodeMeter != NULL)
	#define EXP_CmpCodeMeterCodeMGetFirst  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CodeMGetFirst
	#define EXT_CodeMGetFirst
	#define GET_CodeMGetFirst(fl)  CAL_CMGETAPI( "CodeMGetFirst" ) 
	#define CAL_CodeMGetFirst pICmpCodeMeter->ICodeMGetFirst
	#define CHK_CodeMGetFirst (pICmpCodeMeter != NULL)
	#define EXP_CodeMGetFirst  CAL_CMEXPAPI( "CodeMGetFirst" ) 
#else /* DYNAMIC_LINK */
	#define USE_CodeMGetFirst  PFCODEMGETFIRST pfCodeMGetFirst;
	#define EXT_CodeMGetFirst  extern PFCODEMGETFIRST pfCodeMGetFirst;
	#define GET_CodeMGetFirst(fl)  s_pfCMGetAPI2( "CodeMGetFirst", (RTS_VOID_FCTPTR *)&pfCodeMGetFirst, (fl), 0, 0)
	#define CAL_CodeMGetFirst  pfCodeMGetFirst
	#define CHK_CodeMGetFirst  (pfCodeMGetFirst != NULL)
	#define EXP_CodeMGetFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMGetFirst", (RTS_UINTPTR)CodeMGetFirst, 0, 0) 
#endif




/**
 * <description>
 *	Open the next attached CodeMeter device
 * </description>
 * <param name="hPrevCodeMeter" type="IN">Handle of the previous device</param>
 * <param name="pResult" type="OUT">Pointer to error code:
 *   <ul>
 *     <li>ERR_OK: Device found</li>
 *     <li>ERR_NO_OBJECT: No device found</li>
 *     <li>ERR_PARAMETER: If handle is invalid</li>
 *   </ul>
 * </param>
 * <result>Returns a handle to the next CodeMeter device or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL CodeMGetNext(RTS_HANDLE hPrevCodeMeter, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFCODEMGETNEXT) (RTS_HANDLE hPrevCodeMeter, RTS_RESULT *pResult);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMGETNEXT_NOTIMPLEMENTED)
	#define USE_CodeMGetNext
	#define EXT_CodeMGetNext
	#define GET_CodeMGetNext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CodeMGetNext(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_CodeMGetNext  FALSE
	#define EXP_CodeMGetNext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CodeMGetNext
	#define EXT_CodeMGetNext
	#define GET_CodeMGetNext(fl)  CAL_CMGETAPI( "CodeMGetNext" ) 
	#define CAL_CodeMGetNext  CodeMGetNext
	#define CHK_CodeMGetNext  TRUE
	#define EXP_CodeMGetNext  CAL_CMEXPAPI( "CodeMGetNext" ) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_CodeMGetNext
	#define EXT_CodeMGetNext
	#define GET_CodeMGetNext(fl)  CAL_CMGETAPI( "CodeMGetNext" ) 
	#define CAL_CodeMGetNext  CodeMGetNext
	#define CHK_CodeMGetNext  TRUE
	#define EXP_CodeMGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMGetNext", (RTS_UINTPTR)CodeMGetNext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMeterCodeMGetNext
	#define EXT_CmpCodeMeterCodeMGetNext
	#define GET_CmpCodeMeterCodeMGetNext  ERR_OK
	#define CAL_CmpCodeMeterCodeMGetNext pICmpCodeMeter->ICodeMGetNext
	#define CHK_CmpCodeMeterCodeMGetNext (pICmpCodeMeter != NULL)
	#define EXP_CmpCodeMeterCodeMGetNext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CodeMGetNext
	#define EXT_CodeMGetNext
	#define GET_CodeMGetNext(fl)  CAL_CMGETAPI( "CodeMGetNext" ) 
	#define CAL_CodeMGetNext pICmpCodeMeter->ICodeMGetNext
	#define CHK_CodeMGetNext (pICmpCodeMeter != NULL)
	#define EXP_CodeMGetNext  CAL_CMEXPAPI( "CodeMGetNext" ) 
#else /* DYNAMIC_LINK */
	#define USE_CodeMGetNext  PFCODEMGETNEXT pfCodeMGetNext;
	#define EXT_CodeMGetNext  extern PFCODEMGETNEXT pfCodeMGetNext;
	#define GET_CodeMGetNext(fl)  s_pfCMGetAPI2( "CodeMGetNext", (RTS_VOID_FCTPTR *)&pfCodeMGetNext, (fl), 0, 0)
	#define CAL_CodeMGetNext  pfCodeMGetNext
	#define CHK_CodeMGetNext  (pfCodeMGetNext != NULL)
	#define EXP_CodeMGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMGetNext", (RTS_UINTPTR)CodeMGetNext, 0, 0) 
#endif




/**
 * <description>
 *	Open the communication to a the CodeMeter device
 * </description>
 * <param name="ulFirmCode" type="IN">Firmcode of the vendor</param>
 * <param name="ulProductCode" type="IN">Product code</param>
 * <param name="ulFeatureCode" type="IN">Feature code</param>
 * <param name="pResult" type="OUT">Pointer to error code:
 *   <ul>
 *     <li>ERR_OK: Device found</li>
 *     <li>ERR_NO_OBJECT: No device found</li>
 *     <li>ERR_PARAMETER: If one of the parameter is invalid</li>
 *   </ul>
 * </param>
 * <result>Handle to the CodeMeter device</result>
 */
RTS_HANDLE CDECL CodeMOpen(RTS_UI32 ulFirmCode, RTS_UI32 ulProductCode, RTS_UI32 ulFeatureCode, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFCODEMOPEN) (RTS_UI32 ulFirmCode, RTS_UI32 ulProductCode, RTS_UI32 ulFeatureCode, RTS_RESULT *pResult);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMOPEN_NOTIMPLEMENTED)
	#define USE_CodeMOpen
	#define EXT_CodeMOpen
	#define GET_CodeMOpen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CodeMOpen(p0,p1,p2,p3)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_CodeMOpen  FALSE
	#define EXP_CodeMOpen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CodeMOpen
	#define EXT_CodeMOpen
	#define GET_CodeMOpen(fl)  CAL_CMGETAPI( "CodeMOpen" ) 
	#define CAL_CodeMOpen  CodeMOpen
	#define CHK_CodeMOpen  TRUE
	#define EXP_CodeMOpen  CAL_CMEXPAPI( "CodeMOpen" ) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_CodeMOpen
	#define EXT_CodeMOpen
	#define GET_CodeMOpen(fl)  CAL_CMGETAPI( "CodeMOpen" ) 
	#define CAL_CodeMOpen  CodeMOpen
	#define CHK_CodeMOpen  TRUE
	#define EXP_CodeMOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMOpen", (RTS_UINTPTR)CodeMOpen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMeterCodeMOpen
	#define EXT_CmpCodeMeterCodeMOpen
	#define GET_CmpCodeMeterCodeMOpen  ERR_OK
	#define CAL_CmpCodeMeterCodeMOpen pICmpCodeMeter->ICodeMOpen
	#define CHK_CmpCodeMeterCodeMOpen (pICmpCodeMeter != NULL)
	#define EXP_CmpCodeMeterCodeMOpen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CodeMOpen
	#define EXT_CodeMOpen
	#define GET_CodeMOpen(fl)  CAL_CMGETAPI( "CodeMOpen" ) 
	#define CAL_CodeMOpen pICmpCodeMeter->ICodeMOpen
	#define CHK_CodeMOpen (pICmpCodeMeter != NULL)
	#define EXP_CodeMOpen  CAL_CMEXPAPI( "CodeMOpen" ) 
#else /* DYNAMIC_LINK */
	#define USE_CodeMOpen  PFCODEMOPEN pfCodeMOpen;
	#define EXT_CodeMOpen  extern PFCODEMOPEN pfCodeMOpen;
	#define GET_CodeMOpen(fl)  s_pfCMGetAPI2( "CodeMOpen", (RTS_VOID_FCTPTR *)&pfCodeMOpen, (fl), 0, 0)
	#define CAL_CodeMOpen  pfCodeMOpen
	#define CHK_CodeMOpen  (pfCodeMOpen != NULL)
	#define EXP_CodeMOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMOpen", (RTS_UINTPTR)CodeMOpen, 0, 0) 
#endif




/**
 * <description>
 *	Close the communication to a the CodeMeter device
 * </description>
 * <param name="hCodeMeter" type="IN">Handle to the CodeMeter device</param>
 * <result>Error code:
 *   <ul>
 *     <li>ERR_OK: Successful</li>
 *     <li>ERR_PARAMETER: If handle is invalid</li>
 *   </ul>
 * </result>
 */
RTS_RESULT CDECL CodeMClose(RTS_HANDLE hCodeMeter);
typedef RTS_RESULT (CDECL * PFCODEMCLOSE) (RTS_HANDLE hCodeMeter);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMCLOSE_NOTIMPLEMENTED)
	#define USE_CodeMClose
	#define EXT_CodeMClose
	#define GET_CodeMClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CodeMClose(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_CodeMClose  FALSE
	#define EXP_CodeMClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CodeMClose
	#define EXT_CodeMClose
	#define GET_CodeMClose(fl)  CAL_CMGETAPI( "CodeMClose" ) 
	#define CAL_CodeMClose  CodeMClose
	#define CHK_CodeMClose  TRUE
	#define EXP_CodeMClose  CAL_CMEXPAPI( "CodeMClose" ) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_CodeMClose
	#define EXT_CodeMClose
	#define GET_CodeMClose(fl)  CAL_CMGETAPI( "CodeMClose" ) 
	#define CAL_CodeMClose  CodeMClose
	#define CHK_CodeMClose  TRUE
	#define EXP_CodeMClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMClose", (RTS_UINTPTR)CodeMClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMeterCodeMClose
	#define EXT_CmpCodeMeterCodeMClose
	#define GET_CmpCodeMeterCodeMClose  ERR_OK
	#define CAL_CmpCodeMeterCodeMClose pICmpCodeMeter->ICodeMClose
	#define CHK_CmpCodeMeterCodeMClose (pICmpCodeMeter != NULL)
	#define EXP_CmpCodeMeterCodeMClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CodeMClose
	#define EXT_CodeMClose
	#define GET_CodeMClose(fl)  CAL_CMGETAPI( "CodeMClose" ) 
	#define CAL_CodeMClose pICmpCodeMeter->ICodeMClose
	#define CHK_CodeMClose (pICmpCodeMeter != NULL)
	#define EXP_CodeMClose  CAL_CMEXPAPI( "CodeMClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_CodeMClose  PFCODEMCLOSE pfCodeMClose;
	#define EXT_CodeMClose  extern PFCODEMCLOSE pfCodeMClose;
	#define GET_CodeMClose(fl)  s_pfCMGetAPI2( "CodeMClose", (RTS_VOID_FCTPTR *)&pfCodeMClose, (fl), 0, 0)
	#define CAL_CodeMClose  pfCodeMClose
	#define CHK_CodeMClose  (pfCodeMClose != NULL)
	#define EXP_CodeMClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMClose", (RTS_UINTPTR)CodeMClose, 0, 0) 
#endif




/**
 * <description>
 *	Get information of the opened CodeMeter device
 * </description>
 * <param name="hCodeMeter" type="IN">Handle to the CodeMeter device</param>
 * <param name="pInfo" type="OUT">Pointer to get the information of a device</param>
 * <result>Error code:
 *   <ul>
 *     <li>ERR_OK: Successful</li>
 *     <li>ERR_PARAMETER: If handle is invalid</li>
 *   </ul>
 * </result>
 */
RTS_RESULT CDECL CodeMGetInfo(RTS_HANDLE hCodeMeter, RTS_CODEMETER_INFO *pInfo);
typedef RTS_RESULT (CDECL * PFCODEMGETINFO) (RTS_HANDLE hCodeMeter, RTS_CODEMETER_INFO *pInfo);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMGETINFO_NOTIMPLEMENTED)
	#define USE_CodeMGetInfo
	#define EXT_CodeMGetInfo
	#define GET_CodeMGetInfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CodeMGetInfo(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_CodeMGetInfo  FALSE
	#define EXP_CodeMGetInfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CodeMGetInfo
	#define EXT_CodeMGetInfo
	#define GET_CodeMGetInfo(fl)  CAL_CMGETAPI( "CodeMGetInfo" ) 
	#define CAL_CodeMGetInfo  CodeMGetInfo
	#define CHK_CodeMGetInfo  TRUE
	#define EXP_CodeMGetInfo  CAL_CMEXPAPI( "CodeMGetInfo" ) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_CodeMGetInfo
	#define EXT_CodeMGetInfo
	#define GET_CodeMGetInfo(fl)  CAL_CMGETAPI( "CodeMGetInfo" ) 
	#define CAL_CodeMGetInfo  CodeMGetInfo
	#define CHK_CodeMGetInfo  TRUE
	#define EXP_CodeMGetInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMGetInfo", (RTS_UINTPTR)CodeMGetInfo, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMeterCodeMGetInfo
	#define EXT_CmpCodeMeterCodeMGetInfo
	#define GET_CmpCodeMeterCodeMGetInfo  ERR_OK
	#define CAL_CmpCodeMeterCodeMGetInfo pICmpCodeMeter->ICodeMGetInfo
	#define CHK_CmpCodeMeterCodeMGetInfo (pICmpCodeMeter != NULL)
	#define EXP_CmpCodeMeterCodeMGetInfo  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CodeMGetInfo
	#define EXT_CodeMGetInfo
	#define GET_CodeMGetInfo(fl)  CAL_CMGETAPI( "CodeMGetInfo" ) 
	#define CAL_CodeMGetInfo pICmpCodeMeter->ICodeMGetInfo
	#define CHK_CodeMGetInfo (pICmpCodeMeter != NULL)
	#define EXP_CodeMGetInfo  CAL_CMEXPAPI( "CodeMGetInfo" ) 
#else /* DYNAMIC_LINK */
	#define USE_CodeMGetInfo  PFCODEMGETINFO pfCodeMGetInfo;
	#define EXT_CodeMGetInfo  extern PFCODEMGETINFO pfCodeMGetInfo;
	#define GET_CodeMGetInfo(fl)  s_pfCMGetAPI2( "CodeMGetInfo", (RTS_VOID_FCTPTR *)&pfCodeMGetInfo, (fl), 0, 0)
	#define CAL_CodeMGetInfo  pfCodeMGetInfo
	#define CHK_CodeMGetInfo  (pfCodeMGetInfo != NULL)
	#define EXP_CodeMGetInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMGetInfo", (RTS_UINTPTR)CodeMGetInfo, 0, 0) 
#endif




/**
 * <description>
 *	Get the expiration date
 * </description>
 * <param name="hCodeMeter" type="IN">Handle to the CodeMeter device</param>
 * <param name="ptExpirationTime" type="OUT">Pointer to get the expiration date</param>
 * <result>Error code:
 *   <ul>
 *     <li>ERR_OK: Successful</li>
 *     <li>ERR_PARAMETER: If one of the parameter is invalid</li>
 *   </ul>
 * </result>
 */
RTS_RESULT CDECL CodeMGetExpirationTime(RTS_HANDLE hCodeMeter, RTS_UI32 *ptExpirationTime);
typedef RTS_RESULT (CDECL * PFCODEMGETEXPIRATIONTIME) (RTS_HANDLE hCodeMeter, RTS_UI32 *ptExpirationTime);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMGETEXPIRATIONTIME_NOTIMPLEMENTED)
	#define USE_CodeMGetExpirationTime
	#define EXT_CodeMGetExpirationTime
	#define GET_CodeMGetExpirationTime(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CodeMGetExpirationTime(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_CodeMGetExpirationTime  FALSE
	#define EXP_CodeMGetExpirationTime  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CodeMGetExpirationTime
	#define EXT_CodeMGetExpirationTime
	#define GET_CodeMGetExpirationTime(fl)  CAL_CMGETAPI( "CodeMGetExpirationTime" ) 
	#define CAL_CodeMGetExpirationTime  CodeMGetExpirationTime
	#define CHK_CodeMGetExpirationTime  TRUE
	#define EXP_CodeMGetExpirationTime  CAL_CMEXPAPI( "CodeMGetExpirationTime" ) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_CodeMGetExpirationTime
	#define EXT_CodeMGetExpirationTime
	#define GET_CodeMGetExpirationTime(fl)  CAL_CMGETAPI( "CodeMGetExpirationTime" ) 
	#define CAL_CodeMGetExpirationTime  CodeMGetExpirationTime
	#define CHK_CodeMGetExpirationTime  TRUE
	#define EXP_CodeMGetExpirationTime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMGetExpirationTime", (RTS_UINTPTR)CodeMGetExpirationTime, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMeterCodeMGetExpirationTime
	#define EXT_CmpCodeMeterCodeMGetExpirationTime
	#define GET_CmpCodeMeterCodeMGetExpirationTime  ERR_OK
	#define CAL_CmpCodeMeterCodeMGetExpirationTime pICmpCodeMeter->ICodeMGetExpirationTime
	#define CHK_CmpCodeMeterCodeMGetExpirationTime (pICmpCodeMeter != NULL)
	#define EXP_CmpCodeMeterCodeMGetExpirationTime  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CodeMGetExpirationTime
	#define EXT_CodeMGetExpirationTime
	#define GET_CodeMGetExpirationTime(fl)  CAL_CMGETAPI( "CodeMGetExpirationTime" ) 
	#define CAL_CodeMGetExpirationTime pICmpCodeMeter->ICodeMGetExpirationTime
	#define CHK_CodeMGetExpirationTime (pICmpCodeMeter != NULL)
	#define EXP_CodeMGetExpirationTime  CAL_CMEXPAPI( "CodeMGetExpirationTime" ) 
#else /* DYNAMIC_LINK */
	#define USE_CodeMGetExpirationTime  PFCODEMGETEXPIRATIONTIME pfCodeMGetExpirationTime;
	#define EXT_CodeMGetExpirationTime  extern PFCODEMGETEXPIRATIONTIME pfCodeMGetExpirationTime;
	#define GET_CodeMGetExpirationTime(fl)  s_pfCMGetAPI2( "CodeMGetExpirationTime", (RTS_VOID_FCTPTR *)&pfCodeMGetExpirationTime, (fl), 0, 0)
	#define CAL_CodeMGetExpirationTime  pfCodeMGetExpirationTime
	#define CHK_CodeMGetExpirationTime  (pfCodeMGetExpirationTime != NULL)
	#define EXP_CodeMGetExpirationTime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMGetExpirationTime", (RTS_UINTPTR)CodeMGetExpirationTime, 0, 0) 
#endif




/**
 * <description>
 *	Get the device name
 * </description>
 * <param name="hCodeMeter" type="IN">Handle to the CodeMeter device</param>
 * <param name="pwszName" type="OUT">Pointer to get the name of the device</param>
 * <param name="nLenBytes" type="IN">Maximum name length in bytes</param>
 * <result>Error code:
 *   <ul>
 *     <li>ERR_OK: Successful</li>
 *     <li>ERR_PARAMETER: If one of the parameter is invalid</li>
 *   </ul>
 * </result>
 */
RTS_RESULT CDECL CodeMGetName(RTS_HANDLE hCodeMeter, RTS_WCHAR *pwszName, RTS_UI32 nLenBytes);
typedef RTS_RESULT (CDECL * PFCODEMGETNAME) (RTS_HANDLE hCodeMeter, RTS_WCHAR *pwszName, RTS_UI32 nLenBytes);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMGETNAME_NOTIMPLEMENTED)
	#define USE_CodeMGetName
	#define EXT_CodeMGetName
	#define GET_CodeMGetName(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CodeMGetName(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_CodeMGetName  FALSE
	#define EXP_CodeMGetName  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CodeMGetName
	#define EXT_CodeMGetName
	#define GET_CodeMGetName(fl)  CAL_CMGETAPI( "CodeMGetName" ) 
	#define CAL_CodeMGetName  CodeMGetName
	#define CHK_CodeMGetName  TRUE
	#define EXP_CodeMGetName  CAL_CMEXPAPI( "CodeMGetName" ) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_CodeMGetName
	#define EXT_CodeMGetName
	#define GET_CodeMGetName(fl)  CAL_CMGETAPI( "CodeMGetName" ) 
	#define CAL_CodeMGetName  CodeMGetName
	#define CHK_CodeMGetName  TRUE
	#define EXP_CodeMGetName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMGetName", (RTS_UINTPTR)CodeMGetName, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMeterCodeMGetName
	#define EXT_CmpCodeMeterCodeMGetName
	#define GET_CmpCodeMeterCodeMGetName  ERR_OK
	#define CAL_CmpCodeMeterCodeMGetName pICmpCodeMeter->ICodeMGetName
	#define CHK_CmpCodeMeterCodeMGetName (pICmpCodeMeter != NULL)
	#define EXP_CmpCodeMeterCodeMGetName  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CodeMGetName
	#define EXT_CodeMGetName
	#define GET_CodeMGetName(fl)  CAL_CMGETAPI( "CodeMGetName" ) 
	#define CAL_CodeMGetName pICmpCodeMeter->ICodeMGetName
	#define CHK_CodeMGetName (pICmpCodeMeter != NULL)
	#define EXP_CodeMGetName  CAL_CMEXPAPI( "CodeMGetName" ) 
#else /* DYNAMIC_LINK */
	#define USE_CodeMGetName  PFCODEMGETNAME pfCodeMGetName;
	#define EXT_CodeMGetName  extern PFCODEMGETNAME pfCodeMGetName;
	#define GET_CodeMGetName(fl)  s_pfCMGetAPI2( "CodeMGetName", (RTS_VOID_FCTPTR *)&pfCodeMGetName, (fl), 0, 0)
	#define CAL_CodeMGetName  pfCodeMGetName
	#define CHK_CodeMGetName  (pfCodeMGetName != NULL)
	#define EXP_CodeMGetName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMGetName", (RTS_UINTPTR)CodeMGetName, 0, 0) 
#endif




/**
 * <description>
 *	Get the unit count
 * </description>
 * <param name="hCodeMeter" type="IN">Handle to the CodeMeter device</param>
 * <param name="pulUnitCount" type="OUT">Pointer to get the unit count</param>
 * <result>Error code:
 *   <ul>
 *     <li>ERR_OK: Successful</li>
 *     <li>ERR_PARAMETER: If one of the parameter is invalid</li>
 *   </ul>
 * </result>
 */
RTS_RESULT CDECL CodeMGetUnitCounter(RTS_HANDLE hCodeMeter, RTS_UI32 *pulUnitCount);
typedef RTS_RESULT (CDECL * PFCODEMGETUNITCOUNTER) (RTS_HANDLE hCodeMeter, RTS_UI32 *pulUnitCount);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMGETUNITCOUNTER_NOTIMPLEMENTED)
	#define USE_CodeMGetUnitCounter
	#define EXT_CodeMGetUnitCounter
	#define GET_CodeMGetUnitCounter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CodeMGetUnitCounter(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_CodeMGetUnitCounter  FALSE
	#define EXP_CodeMGetUnitCounter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CodeMGetUnitCounter
	#define EXT_CodeMGetUnitCounter
	#define GET_CodeMGetUnitCounter(fl)  CAL_CMGETAPI( "CodeMGetUnitCounter" ) 
	#define CAL_CodeMGetUnitCounter  CodeMGetUnitCounter
	#define CHK_CodeMGetUnitCounter  TRUE
	#define EXP_CodeMGetUnitCounter  CAL_CMEXPAPI( "CodeMGetUnitCounter" ) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_CodeMGetUnitCounter
	#define EXT_CodeMGetUnitCounter
	#define GET_CodeMGetUnitCounter(fl)  CAL_CMGETAPI( "CodeMGetUnitCounter" ) 
	#define CAL_CodeMGetUnitCounter  CodeMGetUnitCounter
	#define CHK_CodeMGetUnitCounter  TRUE
	#define EXP_CodeMGetUnitCounter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMGetUnitCounter", (RTS_UINTPTR)CodeMGetUnitCounter, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMeterCodeMGetUnitCounter
	#define EXT_CmpCodeMeterCodeMGetUnitCounter
	#define GET_CmpCodeMeterCodeMGetUnitCounter  ERR_OK
	#define CAL_CmpCodeMeterCodeMGetUnitCounter pICmpCodeMeter->ICodeMGetUnitCounter
	#define CHK_CmpCodeMeterCodeMGetUnitCounter (pICmpCodeMeter != NULL)
	#define EXP_CmpCodeMeterCodeMGetUnitCounter  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CodeMGetUnitCounter
	#define EXT_CodeMGetUnitCounter
	#define GET_CodeMGetUnitCounter(fl)  CAL_CMGETAPI( "CodeMGetUnitCounter" ) 
	#define CAL_CodeMGetUnitCounter pICmpCodeMeter->ICodeMGetUnitCounter
	#define CHK_CodeMGetUnitCounter (pICmpCodeMeter != NULL)
	#define EXP_CodeMGetUnitCounter  CAL_CMEXPAPI( "CodeMGetUnitCounter" ) 
#else /* DYNAMIC_LINK */
	#define USE_CodeMGetUnitCounter  PFCODEMGETUNITCOUNTER pfCodeMGetUnitCounter;
	#define EXT_CodeMGetUnitCounter  extern PFCODEMGETUNITCOUNTER pfCodeMGetUnitCounter;
	#define GET_CodeMGetUnitCounter(fl)  s_pfCMGetAPI2( "CodeMGetUnitCounter", (RTS_VOID_FCTPTR *)&pfCodeMGetUnitCounter, (fl), 0, 0)
	#define CAL_CodeMGetUnitCounter  pfCodeMGetUnitCounter
	#define CHK_CodeMGetUnitCounter  (pfCodeMGetUnitCounter != NULL)
	#define EXP_CodeMGetUnitCounter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMGetUnitCounter", (RTS_UINTPTR)CodeMGetUnitCounter, 0, 0) 
#endif




/**
 * <description>
 *	Function to encrypt data with the support of the CodeMeter device
 * </description>
 * <param name="hCodeMeter" type="IN">Handle to the CodeMeter device</param>
 * <param name="ulEncryptionCode" type="IN">Encryption code</param>
 * <param name="pulCRC" type="OUT">Return the CRC of the encrypted data</param>
 * <param name="pbyData" type="IN">Pointer to data to encrypt</param>
 * <param name="ulDataLen" type="IN">Length of data to encrypt</param>
 * <result>Error code:
 *   <ul>
 *     <li>ERR_OK: Successful</li>
 *     <li>ERR_PARAMETER: If one of the parameter is invalid</li>
 *   </ul>
 * </result>
 */
RTS_RESULT CDECL CodeMEncrypt(RTS_HANDLE hCodeMeter, RTS_UI32 ulEncryptionCode, RTS_UI32 *pulCRC, RTS_UI8 *pbyData, RTS_SIZE ulDataLen);
typedef RTS_RESULT (CDECL * PFCODEMENCRYPT) (RTS_HANDLE hCodeMeter, RTS_UI32 ulEncryptionCode, RTS_UI32 *pulCRC, RTS_UI8 *pbyData, RTS_SIZE ulDataLen);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMENCRYPT_NOTIMPLEMENTED)
	#define USE_CodeMEncrypt
	#define EXT_CodeMEncrypt
	#define GET_CodeMEncrypt(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CodeMEncrypt(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_CodeMEncrypt  FALSE
	#define EXP_CodeMEncrypt  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CodeMEncrypt
	#define EXT_CodeMEncrypt
	#define GET_CodeMEncrypt(fl)  CAL_CMGETAPI( "CodeMEncrypt" ) 
	#define CAL_CodeMEncrypt  CodeMEncrypt
	#define CHK_CodeMEncrypt  TRUE
	#define EXP_CodeMEncrypt  CAL_CMEXPAPI( "CodeMEncrypt" ) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_CodeMEncrypt
	#define EXT_CodeMEncrypt
	#define GET_CodeMEncrypt(fl)  CAL_CMGETAPI( "CodeMEncrypt" ) 
	#define CAL_CodeMEncrypt  CodeMEncrypt
	#define CHK_CodeMEncrypt  TRUE
	#define EXP_CodeMEncrypt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMEncrypt", (RTS_UINTPTR)CodeMEncrypt, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMeterCodeMEncrypt
	#define EXT_CmpCodeMeterCodeMEncrypt
	#define GET_CmpCodeMeterCodeMEncrypt  ERR_OK
	#define CAL_CmpCodeMeterCodeMEncrypt pICmpCodeMeter->ICodeMEncrypt
	#define CHK_CmpCodeMeterCodeMEncrypt (pICmpCodeMeter != NULL)
	#define EXP_CmpCodeMeterCodeMEncrypt  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CodeMEncrypt
	#define EXT_CodeMEncrypt
	#define GET_CodeMEncrypt(fl)  CAL_CMGETAPI( "CodeMEncrypt" ) 
	#define CAL_CodeMEncrypt pICmpCodeMeter->ICodeMEncrypt
	#define CHK_CodeMEncrypt (pICmpCodeMeter != NULL)
	#define EXP_CodeMEncrypt  CAL_CMEXPAPI( "CodeMEncrypt" ) 
#else /* DYNAMIC_LINK */
	#define USE_CodeMEncrypt  PFCODEMENCRYPT pfCodeMEncrypt;
	#define EXT_CodeMEncrypt  extern PFCODEMENCRYPT pfCodeMEncrypt;
	#define GET_CodeMEncrypt(fl)  s_pfCMGetAPI2( "CodeMEncrypt", (RTS_VOID_FCTPTR *)&pfCodeMEncrypt, (fl), 0, 0)
	#define CAL_CodeMEncrypt  pfCodeMEncrypt
	#define CHK_CodeMEncrypt  (pfCodeMEncrypt != NULL)
	#define EXP_CodeMEncrypt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMEncrypt", (RTS_UINTPTR)CodeMEncrypt, 0, 0) 
#endif




/**
 * <description>
 *	Function to decrypt data with the support of the CodeMeter device
 * </description>
 * <param name="hCodeMeter" type="IN">Handle to the CodeMeter device</param>
 * <param name="ulEncryptionCode" type="IN">Encryption code</param>
 * <param name="ulCRC" type="IN">CRC of the encrypted data</param>
 * <param name="pbyData" type="IN">Pointer to data to decrypt</param>
 * <param name="ulDataLen" type="IN">Length of data to decrypt</param>
 * <result>Error code:
 *   <ul>
 *     <li>ERR_OK: Successful</li>
 *     <li>ERR_PARAMETER: If one of the parameter is invalid</li>
 *   </ul>
 * </result>
 */
RTS_RESULT CDECL CodeMDecrypt(RTS_HANDLE hCodeMeter, RTS_UI32 ulEncryptionCode, RTS_UI32 ulCRC, RTS_UI8 *pbyData, RTS_SIZE ulDataLen);
typedef RTS_RESULT (CDECL * PFCODEMDECRYPT) (RTS_HANDLE hCodeMeter, RTS_UI32 ulEncryptionCode, RTS_UI32 ulCRC, RTS_UI8 *pbyData, RTS_SIZE ulDataLen);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMDECRYPT_NOTIMPLEMENTED)
	#define USE_CodeMDecrypt
	#define EXT_CodeMDecrypt
	#define GET_CodeMDecrypt(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CodeMDecrypt(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_CodeMDecrypt  FALSE
	#define EXP_CodeMDecrypt  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CodeMDecrypt
	#define EXT_CodeMDecrypt
	#define GET_CodeMDecrypt(fl)  CAL_CMGETAPI( "CodeMDecrypt" ) 
	#define CAL_CodeMDecrypt  CodeMDecrypt
	#define CHK_CodeMDecrypt  TRUE
	#define EXP_CodeMDecrypt  CAL_CMEXPAPI( "CodeMDecrypt" ) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_CodeMDecrypt
	#define EXT_CodeMDecrypt
	#define GET_CodeMDecrypt(fl)  CAL_CMGETAPI( "CodeMDecrypt" ) 
	#define CAL_CodeMDecrypt  CodeMDecrypt
	#define CHK_CodeMDecrypt  TRUE
	#define EXP_CodeMDecrypt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMDecrypt", (RTS_UINTPTR)CodeMDecrypt, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMeterCodeMDecrypt
	#define EXT_CmpCodeMeterCodeMDecrypt
	#define GET_CmpCodeMeterCodeMDecrypt  ERR_OK
	#define CAL_CmpCodeMeterCodeMDecrypt pICmpCodeMeter->ICodeMDecrypt
	#define CHK_CmpCodeMeterCodeMDecrypt (pICmpCodeMeter != NULL)
	#define EXP_CmpCodeMeterCodeMDecrypt  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CodeMDecrypt
	#define EXT_CodeMDecrypt
	#define GET_CodeMDecrypt(fl)  CAL_CMGETAPI( "CodeMDecrypt" ) 
	#define CAL_CodeMDecrypt pICmpCodeMeter->ICodeMDecrypt
	#define CHK_CodeMDecrypt (pICmpCodeMeter != NULL)
	#define EXP_CodeMDecrypt  CAL_CMEXPAPI( "CodeMDecrypt" ) 
#else /* DYNAMIC_LINK */
	#define USE_CodeMDecrypt  PFCODEMDECRYPT pfCodeMDecrypt;
	#define EXT_CodeMDecrypt  extern PFCODEMDECRYPT pfCodeMDecrypt;
	#define GET_CodeMDecrypt(fl)  s_pfCMGetAPI2( "CodeMDecrypt", (RTS_VOID_FCTPTR *)&pfCodeMDecrypt, (fl), 0, 0)
	#define CAL_CodeMDecrypt  pfCodeMDecrypt
	#define CHK_CodeMDecrypt  (pfCodeMDecrypt != NULL)
	#define EXP_CodeMDecrypt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMDecrypt", (RTS_UINTPTR)CodeMDecrypt, 0, 0) 
#endif




/**
 * <description>
 *	Function to encrypt data without the support of the CodeMeter device
 * </description>
 * <param name="pKey" type="IN">Pointer to the key</param>
 * <param name="ulLeyLen" type="IN">Length of the key</param>
 * <param name="pbyData" type="IN">Pointer to data to encrypt</param>
 * <param name="ulDataLen" type="IN">Length of data to encrypt</param>
 * <result>Error code:
 *   <ul>
 *     <li>ERR_OK: Successful</li>
 *     <li>ERR_PARAMETER: If one of the parameter is invalid</li>
 *   </ul>
 * </result>
 */
RTS_RESULT CDECL CodeMEncryptDirect(RTS_UI8 *pKey, RTS_UI32 ulLeyLen, RTS_UI8 *pbyData, RTS_UI32 ulDataLen);
typedef RTS_RESULT (CDECL * PFCODEMENCRYPTDIRECT) (RTS_UI8 *pKey, RTS_UI32 ulLeyLen, RTS_UI8 *pbyData, RTS_UI32 ulDataLen);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMENCRYPTDIRECT_NOTIMPLEMENTED)
	#define USE_CodeMEncryptDirect
	#define EXT_CodeMEncryptDirect
	#define GET_CodeMEncryptDirect(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CodeMEncryptDirect(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_CodeMEncryptDirect  FALSE
	#define EXP_CodeMEncryptDirect  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CodeMEncryptDirect
	#define EXT_CodeMEncryptDirect
	#define GET_CodeMEncryptDirect(fl)  CAL_CMGETAPI( "CodeMEncryptDirect" ) 
	#define CAL_CodeMEncryptDirect  CodeMEncryptDirect
	#define CHK_CodeMEncryptDirect  TRUE
	#define EXP_CodeMEncryptDirect  CAL_CMEXPAPI( "CodeMEncryptDirect" ) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_CodeMEncryptDirect
	#define EXT_CodeMEncryptDirect
	#define GET_CodeMEncryptDirect(fl)  CAL_CMGETAPI( "CodeMEncryptDirect" ) 
	#define CAL_CodeMEncryptDirect  CodeMEncryptDirect
	#define CHK_CodeMEncryptDirect  TRUE
	#define EXP_CodeMEncryptDirect  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMEncryptDirect", (RTS_UINTPTR)CodeMEncryptDirect, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMeterCodeMEncryptDirect
	#define EXT_CmpCodeMeterCodeMEncryptDirect
	#define GET_CmpCodeMeterCodeMEncryptDirect  ERR_OK
	#define CAL_CmpCodeMeterCodeMEncryptDirect pICmpCodeMeter->ICodeMEncryptDirect
	#define CHK_CmpCodeMeterCodeMEncryptDirect (pICmpCodeMeter != NULL)
	#define EXP_CmpCodeMeterCodeMEncryptDirect  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CodeMEncryptDirect
	#define EXT_CodeMEncryptDirect
	#define GET_CodeMEncryptDirect(fl)  CAL_CMGETAPI( "CodeMEncryptDirect" ) 
	#define CAL_CodeMEncryptDirect pICmpCodeMeter->ICodeMEncryptDirect
	#define CHK_CodeMEncryptDirect (pICmpCodeMeter != NULL)
	#define EXP_CodeMEncryptDirect  CAL_CMEXPAPI( "CodeMEncryptDirect" ) 
#else /* DYNAMIC_LINK */
	#define USE_CodeMEncryptDirect  PFCODEMENCRYPTDIRECT pfCodeMEncryptDirect;
	#define EXT_CodeMEncryptDirect  extern PFCODEMENCRYPTDIRECT pfCodeMEncryptDirect;
	#define GET_CodeMEncryptDirect(fl)  s_pfCMGetAPI2( "CodeMEncryptDirect", (RTS_VOID_FCTPTR *)&pfCodeMEncryptDirect, (fl), 0, 0)
	#define CAL_CodeMEncryptDirect  pfCodeMEncryptDirect
	#define CHK_CodeMEncryptDirect  (pfCodeMEncryptDirect != NULL)
	#define EXP_CodeMEncryptDirect  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMEncryptDirect", (RTS_UINTPTR)CodeMEncryptDirect, 0, 0) 
#endif




/**
 * <description>
 *	Function to decrypt data without the support of the CodeMeter device
 * </description>
 * <param name="pKey" type="IN">Pointer to the key</param>
 * <param name="ulLeyLen" type="IN">Length of the key</param>
 * <param name="pbyData" type="IN">Pointer to data to decrypt</param>
 * <param name="ulDataLen" type="IN">Length of data to decrypt</param>
 * <result>Error code:
 *   <ul>
 *     <li>ERR_OK: Successful</li>
 *     <li>ERR_PARAMETER: If one of the parameter is invalid</li>
 *   </ul>
 * </result>
 */
RTS_RESULT CDECL CodeMDecryptDirect(RTS_UI8 *pKey, RTS_UI32 ulLeyLen, RTS_UI8 *pbyData, RTS_UI32 ulDataLen);
typedef RTS_RESULT (CDECL * PFCODEMDECRYPTDIRECT) (RTS_UI8 *pKey, RTS_UI32 ulLeyLen, RTS_UI8 *pbyData, RTS_UI32 ulDataLen);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMDECRYPTDIRECT_NOTIMPLEMENTED)
	#define USE_CodeMDecryptDirect
	#define EXT_CodeMDecryptDirect
	#define GET_CodeMDecryptDirect(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CodeMDecryptDirect(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_CodeMDecryptDirect  FALSE
	#define EXP_CodeMDecryptDirect  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CodeMDecryptDirect
	#define EXT_CodeMDecryptDirect
	#define GET_CodeMDecryptDirect(fl)  CAL_CMGETAPI( "CodeMDecryptDirect" ) 
	#define CAL_CodeMDecryptDirect  CodeMDecryptDirect
	#define CHK_CodeMDecryptDirect  TRUE
	#define EXP_CodeMDecryptDirect  CAL_CMEXPAPI( "CodeMDecryptDirect" ) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_CodeMDecryptDirect
	#define EXT_CodeMDecryptDirect
	#define GET_CodeMDecryptDirect(fl)  CAL_CMGETAPI( "CodeMDecryptDirect" ) 
	#define CAL_CodeMDecryptDirect  CodeMDecryptDirect
	#define CHK_CodeMDecryptDirect  TRUE
	#define EXP_CodeMDecryptDirect  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMDecryptDirect", (RTS_UINTPTR)CodeMDecryptDirect, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMeterCodeMDecryptDirect
	#define EXT_CmpCodeMeterCodeMDecryptDirect
	#define GET_CmpCodeMeterCodeMDecryptDirect  ERR_OK
	#define CAL_CmpCodeMeterCodeMDecryptDirect pICmpCodeMeter->ICodeMDecryptDirect
	#define CHK_CmpCodeMeterCodeMDecryptDirect (pICmpCodeMeter != NULL)
	#define EXP_CmpCodeMeterCodeMDecryptDirect  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CodeMDecryptDirect
	#define EXT_CodeMDecryptDirect
	#define GET_CodeMDecryptDirect(fl)  CAL_CMGETAPI( "CodeMDecryptDirect" ) 
	#define CAL_CodeMDecryptDirect pICmpCodeMeter->ICodeMDecryptDirect
	#define CHK_CodeMDecryptDirect (pICmpCodeMeter != NULL)
	#define EXP_CodeMDecryptDirect  CAL_CMEXPAPI( "CodeMDecryptDirect" ) 
#else /* DYNAMIC_LINK */
	#define USE_CodeMDecryptDirect  PFCODEMDECRYPTDIRECT pfCodeMDecryptDirect;
	#define EXT_CodeMDecryptDirect  extern PFCODEMDECRYPTDIRECT pfCodeMDecryptDirect;
	#define GET_CodeMDecryptDirect(fl)  s_pfCMGetAPI2( "CodeMDecryptDirect", (RTS_VOID_FCTPTR *)&pfCodeMDecryptDirect, (fl), 0, 0)
	#define CAL_CodeMDecryptDirect  pfCodeMDecryptDirect
	#define CHK_CodeMDecryptDirect  (pfCodeMDecryptDirect != NULL)
	#define EXP_CodeMDecryptDirect  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMDecryptDirect", (RTS_UINTPTR)CodeMDecryptDirect, 0, 0) 
#endif




/**
 * <description>
 *	Function to generate the export license file for the specified firmcodes
 * </description>
 * <param name="paulFirmCodes" type="IN">Pointer to array of firmcodes</param>
 * <param name="ulFirmCodes" type="IN">Number of firmcodes in the array</param>
 * <param name="pszLicenseFile" type="IN">License file to store license information</param>
 * <result>Error code:
 *   <ul>
 *     <li>ERR_OK: Successful</li>
 *     <li>ERR_PARAMETER: If one of the parameter is invalid</li>
 *     <li>ERR_FAILED: License file could not be generated</li>
 *   </ul>
 * </result>
 */
RTS_RESULT CDECL CodeMGenerateLicenseFile(RTS_UI32 *paulFirmCodes, RTS_UI32 ulFirmCodes, const char *pszLicenseFile);
typedef RTS_RESULT (CDECL * PFCODEMGENERATELICENSEFILE) (RTS_UI32 *paulFirmCodes, RTS_UI32 ulFirmCodes, const char *pszLicenseFile);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMGENERATELICENSEFILE_NOTIMPLEMENTED)
	#define USE_CodeMGenerateLicenseFile
	#define EXT_CodeMGenerateLicenseFile
	#define GET_CodeMGenerateLicenseFile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CodeMGenerateLicenseFile(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_CodeMGenerateLicenseFile  FALSE
	#define EXP_CodeMGenerateLicenseFile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CodeMGenerateLicenseFile
	#define EXT_CodeMGenerateLicenseFile
	#define GET_CodeMGenerateLicenseFile(fl)  CAL_CMGETAPI( "CodeMGenerateLicenseFile" ) 
	#define CAL_CodeMGenerateLicenseFile  CodeMGenerateLicenseFile
	#define CHK_CodeMGenerateLicenseFile  TRUE
	#define EXP_CodeMGenerateLicenseFile  CAL_CMEXPAPI( "CodeMGenerateLicenseFile" ) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_CodeMGenerateLicenseFile
	#define EXT_CodeMGenerateLicenseFile
	#define GET_CodeMGenerateLicenseFile(fl)  CAL_CMGETAPI( "CodeMGenerateLicenseFile" ) 
	#define CAL_CodeMGenerateLicenseFile  CodeMGenerateLicenseFile
	#define CHK_CodeMGenerateLicenseFile  TRUE
	#define EXP_CodeMGenerateLicenseFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMGenerateLicenseFile", (RTS_UINTPTR)CodeMGenerateLicenseFile, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMeterCodeMGenerateLicenseFile
	#define EXT_CmpCodeMeterCodeMGenerateLicenseFile
	#define GET_CmpCodeMeterCodeMGenerateLicenseFile  ERR_OK
	#define CAL_CmpCodeMeterCodeMGenerateLicenseFile pICmpCodeMeter->ICodeMGenerateLicenseFile
	#define CHK_CmpCodeMeterCodeMGenerateLicenseFile (pICmpCodeMeter != NULL)
	#define EXP_CmpCodeMeterCodeMGenerateLicenseFile  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CodeMGenerateLicenseFile
	#define EXT_CodeMGenerateLicenseFile
	#define GET_CodeMGenerateLicenseFile(fl)  CAL_CMGETAPI( "CodeMGenerateLicenseFile" ) 
	#define CAL_CodeMGenerateLicenseFile pICmpCodeMeter->ICodeMGenerateLicenseFile
	#define CHK_CodeMGenerateLicenseFile (pICmpCodeMeter != NULL)
	#define EXP_CodeMGenerateLicenseFile  CAL_CMEXPAPI( "CodeMGenerateLicenseFile" ) 
#else /* DYNAMIC_LINK */
	#define USE_CodeMGenerateLicenseFile  PFCODEMGENERATELICENSEFILE pfCodeMGenerateLicenseFile;
	#define EXT_CodeMGenerateLicenseFile  extern PFCODEMGENERATELICENSEFILE pfCodeMGenerateLicenseFile;
	#define GET_CodeMGenerateLicenseFile(fl)  s_pfCMGetAPI2( "CodeMGenerateLicenseFile", (RTS_VOID_FCTPTR *)&pfCodeMGenerateLicenseFile, (fl), 0, 0)
	#define CAL_CodeMGenerateLicenseFile  pfCodeMGenerateLicenseFile
	#define CHK_CodeMGenerateLicenseFile  (pfCodeMGenerateLicenseFile != NULL)
	#define EXP_CodeMGenerateLicenseFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMGenerateLicenseFile", (RTS_UINTPTR)CodeMGenerateLicenseFile, 0, 0) 
#endif




/**
 * <description>
 *	Function to write new licenses on the CodeMeter device
 * </description>
 * <param name="ui32SerialNumber" type="IN">Serial number of the adapter to write license file. 0 to write to any matching adapter.</param>
 * <param name="pszLicenseFile" type="IN">License file with new licenses</param>
 * <result>Error code:
 *   <ul>
 *     <li>ERR_OK: Successful</li>
 *     <li>ERR_PARAMETER: If one of the parameter is invalid</li>
 *     <li>ERR_FAILED: License file could not be written</li>
 *   </ul>
 * </result>
 */
RTS_RESULT CDECL CodeMWriteLicenseFile(RTS_UI32 ui32SerialNumber, const char *pszLicenseFile);
typedef RTS_RESULT (CDECL * PFCODEMWRITELICENSEFILE) (RTS_UI32 ui32SerialNumber, const char *pszLicenseFile);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMWRITELICENSEFILE_NOTIMPLEMENTED)
	#define USE_CodeMWriteLicenseFile
	#define EXT_CodeMWriteLicenseFile
	#define GET_CodeMWriteLicenseFile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CodeMWriteLicenseFile(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_CodeMWriteLicenseFile  FALSE
	#define EXP_CodeMWriteLicenseFile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CodeMWriteLicenseFile
	#define EXT_CodeMWriteLicenseFile
	#define GET_CodeMWriteLicenseFile(fl)  CAL_CMGETAPI( "CodeMWriteLicenseFile" ) 
	#define CAL_CodeMWriteLicenseFile  CodeMWriteLicenseFile
	#define CHK_CodeMWriteLicenseFile  TRUE
	#define EXP_CodeMWriteLicenseFile  CAL_CMEXPAPI( "CodeMWriteLicenseFile" ) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_CodeMWriteLicenseFile
	#define EXT_CodeMWriteLicenseFile
	#define GET_CodeMWriteLicenseFile(fl)  CAL_CMGETAPI( "CodeMWriteLicenseFile" ) 
	#define CAL_CodeMWriteLicenseFile  CodeMWriteLicenseFile
	#define CHK_CodeMWriteLicenseFile  TRUE
	#define EXP_CodeMWriteLicenseFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMWriteLicenseFile", (RTS_UINTPTR)CodeMWriteLicenseFile, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMeterCodeMWriteLicenseFile
	#define EXT_CmpCodeMeterCodeMWriteLicenseFile
	#define GET_CmpCodeMeterCodeMWriteLicenseFile  ERR_OK
	#define CAL_CmpCodeMeterCodeMWriteLicenseFile pICmpCodeMeter->ICodeMWriteLicenseFile
	#define CHK_CmpCodeMeterCodeMWriteLicenseFile (pICmpCodeMeter != NULL)
	#define EXP_CmpCodeMeterCodeMWriteLicenseFile  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CodeMWriteLicenseFile
	#define EXT_CodeMWriteLicenseFile
	#define GET_CodeMWriteLicenseFile(fl)  CAL_CMGETAPI( "CodeMWriteLicenseFile" ) 
	#define CAL_CodeMWriteLicenseFile pICmpCodeMeter->ICodeMWriteLicenseFile
	#define CHK_CodeMWriteLicenseFile (pICmpCodeMeter != NULL)
	#define EXP_CodeMWriteLicenseFile  CAL_CMEXPAPI( "CodeMWriteLicenseFile" ) 
#else /* DYNAMIC_LINK */
	#define USE_CodeMWriteLicenseFile  PFCODEMWRITELICENSEFILE pfCodeMWriteLicenseFile;
	#define EXT_CodeMWriteLicenseFile  extern PFCODEMWRITELICENSEFILE pfCodeMWriteLicenseFile;
	#define GET_CodeMWriteLicenseFile(fl)  s_pfCMGetAPI2( "CodeMWriteLicenseFile", (RTS_VOID_FCTPTR *)&pfCodeMWriteLicenseFile, (fl), 0, 0)
	#define CAL_CodeMWriteLicenseFile  pfCodeMWriteLicenseFile
	#define CHK_CodeMWriteLicenseFile  (pfCodeMWriteLicenseFile != NULL)
	#define EXP_CodeMWriteLicenseFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMWriteLicenseFile", (RTS_UINTPTR)CodeMWriteLicenseFile, 0, 0) 
#endif




/**
 * <description>
 *	Function to read all licenses for a specific firmcode. 
 * </description>
 * <param name="ulFirmcode" type="IN">Firmcode to enumerate.</param>
 * <param name="paEntry" type="OUT">Array of RTS_CMBOXENTRY-structures to receive the boxentries.</param>
 * <param name="pnEntries" type="IN OUT">Pointer to an initialized variable. Initvalue is number of structs in paEntry.</param>
 * <result>Error code:
 *   <ul>
 *     <li>ERR_OK: Successful</li>
 *     <li>ERR_PARAMETER: License entry pointer is NULL</li>
 *     <li>ERR_NOT_SUPPORTED: License entry not found</li> 
 *     <li>ERR_NOBUFFER: Buffer is too small, check output of pnEntries for required number of structs in paEntry.</li> 
 *   </ul>
 * </result>
 */
RTS_RESULT CDECL CodeMGetContentByFirmcode(RTS_UI32 ulFirmcode, RTS_CMBOXENTRY *paEntry, RTS_UI32 *pnEntries);
typedef RTS_RESULT (CDECL * PFCODEMGETCONTENTBYFIRMCODE) (RTS_UI32 ulFirmcode, RTS_CMBOXENTRY *paEntry, RTS_UI32 *pnEntries);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMGETCONTENTBYFIRMCODE_NOTIMPLEMENTED)
	#define USE_CodeMGetContentByFirmcode
	#define EXT_CodeMGetContentByFirmcode
	#define GET_CodeMGetContentByFirmcode(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CodeMGetContentByFirmcode(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_CodeMGetContentByFirmcode  FALSE
	#define EXP_CodeMGetContentByFirmcode  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CodeMGetContentByFirmcode
	#define EXT_CodeMGetContentByFirmcode
	#define GET_CodeMGetContentByFirmcode(fl)  CAL_CMGETAPI( "CodeMGetContentByFirmcode" ) 
	#define CAL_CodeMGetContentByFirmcode  CodeMGetContentByFirmcode
	#define CHK_CodeMGetContentByFirmcode  TRUE
	#define EXP_CodeMGetContentByFirmcode  CAL_CMEXPAPI( "CodeMGetContentByFirmcode" ) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_CodeMGetContentByFirmcode
	#define EXT_CodeMGetContentByFirmcode
	#define GET_CodeMGetContentByFirmcode(fl)  CAL_CMGETAPI( "CodeMGetContentByFirmcode" ) 
	#define CAL_CodeMGetContentByFirmcode  CodeMGetContentByFirmcode
	#define CHK_CodeMGetContentByFirmcode  TRUE
	#define EXP_CodeMGetContentByFirmcode  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMGetContentByFirmcode", (RTS_UINTPTR)CodeMGetContentByFirmcode, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMeterCodeMGetContentByFirmcode
	#define EXT_CmpCodeMeterCodeMGetContentByFirmcode
	#define GET_CmpCodeMeterCodeMGetContentByFirmcode  ERR_OK
	#define CAL_CmpCodeMeterCodeMGetContentByFirmcode pICmpCodeMeter->ICodeMGetContentByFirmcode
	#define CHK_CmpCodeMeterCodeMGetContentByFirmcode (pICmpCodeMeter != NULL)
	#define EXP_CmpCodeMeterCodeMGetContentByFirmcode  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CodeMGetContentByFirmcode
	#define EXT_CodeMGetContentByFirmcode
	#define GET_CodeMGetContentByFirmcode(fl)  CAL_CMGETAPI( "CodeMGetContentByFirmcode" ) 
	#define CAL_CodeMGetContentByFirmcode pICmpCodeMeter->ICodeMGetContentByFirmcode
	#define CHK_CodeMGetContentByFirmcode (pICmpCodeMeter != NULL)
	#define EXP_CodeMGetContentByFirmcode  CAL_CMEXPAPI( "CodeMGetContentByFirmcode" ) 
#else /* DYNAMIC_LINK */
	#define USE_CodeMGetContentByFirmcode  PFCODEMGETCONTENTBYFIRMCODE pfCodeMGetContentByFirmcode;
	#define EXT_CodeMGetContentByFirmcode  extern PFCODEMGETCONTENTBYFIRMCODE pfCodeMGetContentByFirmcode;
	#define GET_CodeMGetContentByFirmcode(fl)  s_pfCMGetAPI2( "CodeMGetContentByFirmcode", (RTS_VOID_FCTPTR *)&pfCodeMGetContentByFirmcode, (fl), 0, 0)
	#define CAL_CodeMGetContentByFirmcode  pfCodeMGetContentByFirmcode
	#define CHK_CodeMGetContentByFirmcode  (pfCodeMGetContentByFirmcode != NULL)
	#define EXP_CodeMGetContentByFirmcode  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMGetContentByFirmcode", (RTS_UINTPTR)CodeMGetContentByFirmcode, 0, 0) 
#endif




/**
 * <description>
 *	Function to read a license entry specified by frimcode and productcode. 
 * </description>
 * <param name="ulFirmcode" type="IN">Firmcode of the license entry</param>
 * <param name="ulProductcode" type="IN">Productcode of the license entry</param>
 * <param name="paEntry" type="OUT">Pointer to RTS_CMBOXENTRY to get the license entry</param>
 * <result>Error code:
 *   <ul>
 *     <li>ERR_OK: Successful</li>
 *     <li>ERR_PARAMETER: License entry pointer is NULL</li>
 *     <li>ERR_NOT_SUPPORTED: License entry not found</li> 
 *   </ul>
 * </result>
 */
RTS_RESULT CDECL CodeMGetContentByFirmcode2(RTS_UI32 ulFirmcode, RTS_UI32 ulProductcode, RTS_CMBOXENTRY *paEntry);
typedef RTS_RESULT (CDECL * PFCODEMGETCONTENTBYFIRMCODE2) (RTS_UI32 ulFirmcode, RTS_UI32 ulProductcode, RTS_CMBOXENTRY *paEntry);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMGETCONTENTBYFIRMCODE2_NOTIMPLEMENTED)
	#define USE_CodeMGetContentByFirmcode2
	#define EXT_CodeMGetContentByFirmcode2
	#define GET_CodeMGetContentByFirmcode2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CodeMGetContentByFirmcode2(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_CodeMGetContentByFirmcode2  FALSE
	#define EXP_CodeMGetContentByFirmcode2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CodeMGetContentByFirmcode2
	#define EXT_CodeMGetContentByFirmcode2
	#define GET_CodeMGetContentByFirmcode2(fl)  CAL_CMGETAPI( "CodeMGetContentByFirmcode2" ) 
	#define CAL_CodeMGetContentByFirmcode2  CodeMGetContentByFirmcode2
	#define CHK_CodeMGetContentByFirmcode2  TRUE
	#define EXP_CodeMGetContentByFirmcode2  CAL_CMEXPAPI( "CodeMGetContentByFirmcode2" ) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_CodeMGetContentByFirmcode2
	#define EXT_CodeMGetContentByFirmcode2
	#define GET_CodeMGetContentByFirmcode2(fl)  CAL_CMGETAPI( "CodeMGetContentByFirmcode2" ) 
	#define CAL_CodeMGetContentByFirmcode2  CodeMGetContentByFirmcode2
	#define CHK_CodeMGetContentByFirmcode2  TRUE
	#define EXP_CodeMGetContentByFirmcode2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMGetContentByFirmcode2", (RTS_UINTPTR)CodeMGetContentByFirmcode2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMeterCodeMGetContentByFirmcode2
	#define EXT_CmpCodeMeterCodeMGetContentByFirmcode2
	#define GET_CmpCodeMeterCodeMGetContentByFirmcode2  ERR_OK
	#define CAL_CmpCodeMeterCodeMGetContentByFirmcode2 pICmpCodeMeter->ICodeMGetContentByFirmcode2
	#define CHK_CmpCodeMeterCodeMGetContentByFirmcode2 (pICmpCodeMeter != NULL)
	#define EXP_CmpCodeMeterCodeMGetContentByFirmcode2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CodeMGetContentByFirmcode2
	#define EXT_CodeMGetContentByFirmcode2
	#define GET_CodeMGetContentByFirmcode2(fl)  CAL_CMGETAPI( "CodeMGetContentByFirmcode2" ) 
	#define CAL_CodeMGetContentByFirmcode2 pICmpCodeMeter->ICodeMGetContentByFirmcode2
	#define CHK_CodeMGetContentByFirmcode2 (pICmpCodeMeter != NULL)
	#define EXP_CodeMGetContentByFirmcode2  CAL_CMEXPAPI( "CodeMGetContentByFirmcode2" ) 
#else /* DYNAMIC_LINK */
	#define USE_CodeMGetContentByFirmcode2  PFCODEMGETCONTENTBYFIRMCODE2 pfCodeMGetContentByFirmcode2;
	#define EXT_CodeMGetContentByFirmcode2  extern PFCODEMGETCONTENTBYFIRMCODE2 pfCodeMGetContentByFirmcode2;
	#define GET_CodeMGetContentByFirmcode2(fl)  s_pfCMGetAPI2( "CodeMGetContentByFirmcode2", (RTS_VOID_FCTPTR *)&pfCodeMGetContentByFirmcode2, (fl), 0, 0)
	#define CAL_CodeMGetContentByFirmcode2  pfCodeMGetContentByFirmcode2
	#define CHK_CodeMGetContentByFirmcode2  (pfCodeMGetContentByFirmcode2 != NULL)
	#define EXP_CodeMGetContentByFirmcode2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMGetContentByFirmcode2", (RTS_UINTPTR)CodeMGetContentByFirmcode2, 0, 0) 
#endif




/**
 * <description>
 *	Function to read a license entry specified by frimcode and productcode from a network server. 
 * </description>
 * <param name="ulFirmcode" type="IN">Firmcode of the license entry</param>
 * <param name="ulProductcode" type="IN">Productcode of the license entry</param>
 * <param name="pszServer" type="IN">Servername or IP-Address (dotted string format)</param>
 * <param name="paEntry" type="OUT">Pointer to RTS_CMBOXENTRY to get the license entry</param>
 * <param name="bNoRelease" type="IN">Determines if the function calls CmRelease. 1= CmRelease not called.</param>
 * <param name="phEntry" type="IN">In case CmRelease is not called, the resulting entry handle is returned to the caller here.</param>
 * <result>Error code:
 *   <ul>
 *     <li>ERR_OK: Successful</li>
 *     <li>ERR_PARAMETER: License entry pointer is NULL</li>
 *     <li>ERR_NOT_SUPPORTED: License entry not found</li> 
 *   </ul>
 * </result>
 */
RTS_RESULT CDECL CodeMGetContentByFirmcodeNet(RTS_UI32 ulFirmcode,RTS_UI32 ulProductcode, RTS_CMBOXENTRY *paEntry, char* pszServer, int bNoRelease, RTS_HANDLE* phEntry);
typedef RTS_RESULT (CDECL * PFCODEMGETCONTENTBYFIRMCODENET) (RTS_UI32 ulFirmcode,RTS_UI32 ulProductcode, RTS_CMBOXENTRY *paEntry, char* pszServer, int bNoRelease, RTS_HANDLE* phEntry);
#if defined(CMPCODEMETER_NOTIMPLEMENTED) || defined(CODEMGETCONTENTBYFIRMCODENET_NOTIMPLEMENTED)
	#define USE_CodeMGetContentByFirmcodeNet
	#define EXT_CodeMGetContentByFirmcodeNet
	#define GET_CodeMGetContentByFirmcodeNet(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CodeMGetContentByFirmcodeNet(p0,p1,p2,p3,p4,p5)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_CodeMGetContentByFirmcodeNet  FALSE
	#define EXP_CodeMGetContentByFirmcodeNet  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CodeMGetContentByFirmcodeNet
	#define EXT_CodeMGetContentByFirmcodeNet
	#define GET_CodeMGetContentByFirmcodeNet(fl)  CAL_CMGETAPI( "CodeMGetContentByFirmcodeNet" ) 
	#define CAL_CodeMGetContentByFirmcodeNet  CodeMGetContentByFirmcodeNet
	#define CHK_CodeMGetContentByFirmcodeNet  TRUE
	#define EXP_CodeMGetContentByFirmcodeNet  CAL_CMEXPAPI( "CodeMGetContentByFirmcodeNet" ) 
#elif defined(MIXED_LINK) && !defined(CMPCODEMETER_EXTERNAL)
	#define USE_CodeMGetContentByFirmcodeNet
	#define EXT_CodeMGetContentByFirmcodeNet
	#define GET_CodeMGetContentByFirmcodeNet(fl)  CAL_CMGETAPI( "CodeMGetContentByFirmcodeNet" ) 
	#define CAL_CodeMGetContentByFirmcodeNet  CodeMGetContentByFirmcodeNet
	#define CHK_CodeMGetContentByFirmcodeNet  TRUE
	#define EXP_CodeMGetContentByFirmcodeNet  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMGetContentByFirmcodeNet", (RTS_UINTPTR)CodeMGetContentByFirmcodeNet, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCodeMeterCodeMGetContentByFirmcodeNet
	#define EXT_CmpCodeMeterCodeMGetContentByFirmcodeNet
	#define GET_CmpCodeMeterCodeMGetContentByFirmcodeNet  ERR_OK
	#define CAL_CmpCodeMeterCodeMGetContentByFirmcodeNet pICmpCodeMeter->ICodeMGetContentByFirmcodeNet
	#define CHK_CmpCodeMeterCodeMGetContentByFirmcodeNet (pICmpCodeMeter != NULL)
	#define EXP_CmpCodeMeterCodeMGetContentByFirmcodeNet  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CodeMGetContentByFirmcodeNet
	#define EXT_CodeMGetContentByFirmcodeNet
	#define GET_CodeMGetContentByFirmcodeNet(fl)  CAL_CMGETAPI( "CodeMGetContentByFirmcodeNet" ) 
	#define CAL_CodeMGetContentByFirmcodeNet pICmpCodeMeter->ICodeMGetContentByFirmcodeNet
	#define CHK_CodeMGetContentByFirmcodeNet (pICmpCodeMeter != NULL)
	#define EXP_CodeMGetContentByFirmcodeNet  CAL_CMEXPAPI( "CodeMGetContentByFirmcodeNet" ) 
#else /* DYNAMIC_LINK */
	#define USE_CodeMGetContentByFirmcodeNet  PFCODEMGETCONTENTBYFIRMCODENET pfCodeMGetContentByFirmcodeNet;
	#define EXT_CodeMGetContentByFirmcodeNet  extern PFCODEMGETCONTENTBYFIRMCODENET pfCodeMGetContentByFirmcodeNet;
	#define GET_CodeMGetContentByFirmcodeNet(fl)  s_pfCMGetAPI2( "CodeMGetContentByFirmcodeNet", (RTS_VOID_FCTPTR *)&pfCodeMGetContentByFirmcodeNet, (fl), 0, 0)
	#define CAL_CodeMGetContentByFirmcodeNet  pfCodeMGetContentByFirmcodeNet
	#define CHK_CodeMGetContentByFirmcodeNet  (pfCodeMGetContentByFirmcodeNet != NULL)
	#define EXP_CodeMGetContentByFirmcodeNet  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CodeMGetContentByFirmcodeNet", (RTS_UINTPTR)CodeMGetContentByFirmcodeNet, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFCODEMGETFIRST ICodeMGetFirst;
 	PFCODEMGETNEXT ICodeMGetNext;
 	PFCODEMOPEN ICodeMOpen;
 	PFCODEMCLOSE ICodeMClose;
 	PFCODEMGETINFO ICodeMGetInfo;
 	PFCODEMGETEXPIRATIONTIME ICodeMGetExpirationTime;
 	PFCODEMGETNAME ICodeMGetName;
 	PFCODEMGETUNITCOUNTER ICodeMGetUnitCounter;
 	PFCODEMENCRYPT ICodeMEncrypt;
 	PFCODEMDECRYPT ICodeMDecrypt;
 	PFCODEMENCRYPTDIRECT ICodeMEncryptDirect;
 	PFCODEMDECRYPTDIRECT ICodeMDecryptDirect;
 	PFCODEMGENERATELICENSEFILE ICodeMGenerateLicenseFile;
 	PFCODEMWRITELICENSEFILE ICodeMWriteLicenseFile;
 	PFCODEMGETCONTENTBYFIRMCODE ICodeMGetContentByFirmcode;
 	PFCODEMGETCONTENTBYFIRMCODE2 ICodeMGetContentByFirmcode2;
 	PFCODEMGETCONTENTBYFIRMCODENET ICodeMGetContentByFirmcodeNet;
 } ICmpCodeMeter_C;

#ifdef CPLUSPLUS
class ICmpCodeMeter : public IBase
{
	public:
		virtual RTS_HANDLE CDECL ICodeMGetFirst(RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL ICodeMGetNext(RTS_HANDLE hPrevCodeMeter, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL ICodeMOpen(RTS_UI32 ulFirmCode, RTS_UI32 ulProductCode, RTS_UI32 ulFeatureCode, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ICodeMClose(RTS_HANDLE hCodeMeter) =0;
		virtual RTS_RESULT CDECL ICodeMGetInfo(RTS_HANDLE hCodeMeter, RTS_CODEMETER_INFO *pInfo) =0;
		virtual RTS_RESULT CDECL ICodeMGetExpirationTime(RTS_HANDLE hCodeMeter, RTS_UI32 *ptExpirationTime) =0;
		virtual RTS_RESULT CDECL ICodeMGetName(RTS_HANDLE hCodeMeter, RTS_WCHAR *pwszName, RTS_UI32 nLenBytes) =0;
		virtual RTS_RESULT CDECL ICodeMGetUnitCounter(RTS_HANDLE hCodeMeter, RTS_UI32 *pulUnitCount) =0;
		virtual RTS_RESULT CDECL ICodeMEncrypt(RTS_HANDLE hCodeMeter, RTS_UI32 ulEncryptionCode, RTS_UI32 *pulCRC, RTS_UI8 *pbyData, RTS_SIZE ulDataLen) =0;
		virtual RTS_RESULT CDECL ICodeMDecrypt(RTS_HANDLE hCodeMeter, RTS_UI32 ulEncryptionCode, RTS_UI32 ulCRC, RTS_UI8 *pbyData, RTS_SIZE ulDataLen) =0;
		virtual RTS_RESULT CDECL ICodeMEncryptDirect(RTS_UI8 *pKey, RTS_UI32 ulLeyLen, RTS_UI8 *pbyData, RTS_UI32 ulDataLen) =0;
		virtual RTS_RESULT CDECL ICodeMDecryptDirect(RTS_UI8 *pKey, RTS_UI32 ulLeyLen, RTS_UI8 *pbyData, RTS_UI32 ulDataLen) =0;
		virtual RTS_RESULT CDECL ICodeMGenerateLicenseFile(RTS_UI32 *paulFirmCodes, RTS_UI32 ulFirmCodes, const char *pszLicenseFile) =0;
		virtual RTS_RESULT CDECL ICodeMWriteLicenseFile(RTS_UI32 ui32SerialNumber, const char *pszLicenseFile) =0;
		virtual RTS_RESULT CDECL ICodeMGetContentByFirmcode(RTS_UI32 ulFirmcode, RTS_CMBOXENTRY *paEntry, RTS_UI32 *pnEntries) =0;
		virtual RTS_RESULT CDECL ICodeMGetContentByFirmcode2(RTS_UI32 ulFirmcode, RTS_UI32 ulProductcode, RTS_CMBOXENTRY *paEntry) =0;
		virtual RTS_RESULT CDECL ICodeMGetContentByFirmcodeNet(RTS_UI32 ulFirmcode, RTS_UI32 ulProductcode, RTS_CMBOXENTRY *paEntry, char* pszServer, int bNoRelease, RTS_HANDLE* phEntry) =0;
};
	#ifndef ITF_CmpCodeMeter
		#define ITF_CmpCodeMeter static ICmpCodeMeter *pICmpCodeMeter = NULL;
	#endif
	#define EXTITF_CmpCodeMeter
#else	/*CPLUSPLUS*/
	typedef ICmpCodeMeter_C		ICmpCodeMeter;
	#ifndef ITF_CmpCodeMeter
		#define ITF_CmpCodeMeter
	#endif
	#define EXTITF_CmpCodeMeter
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCODEMETERITF_H_*/
