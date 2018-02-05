 /**
 * <interfacename>SysPort</interfacename>
 * <description> 
 *	<p>The SysPort interface is projected to get direct access to hardware devices by port access</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSPORTITF_H_
#define _SYSPORTITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"


/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>This function reads the current BYTE-value at the given port address.</description>
 * <result><p>RESULT: Input port value that was read.</p></result>
 */
typedef struct tagsysportin_struct
{
	RTS_IEC_UDINT ulAddress;			/* VAR_INPUT */	/* <param name="ulAddress" type="IN">Port address</param> */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param> */
	RTS_IEC_BYTE SysPortIn;				/* VAR_OUTPUT */	
} sysportin_struct;

void CDECL CDECL_EXT sysportin(sysportin_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSPORTIN_IEC) (sysportin_struct *p);
#if defined(SYSPORT_NOTIMPLEMENTED) || defined(SYSPORTIN_NOTIMPLEMENTED)
	#define USE_sysportin
	#define EXT_sysportin
	#define GET_sysportin(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysportin(p0) 
	#define CHK_sysportin  FALSE
	#define EXP_sysportin  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysportin
	#define EXT_sysportin
	#define GET_sysportin(fl)  CAL_CMGETAPI( "sysportin" ) 
	#define CAL_sysportin  sysportin
	#define CHK_sysportin  TRUE
	#define EXP_sysportin  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportin", (RTS_UINTPTR)sysportin, 1, RTSITF_GET_SIGNATURE(0, 0xD23F618E), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSPORT_EXTERNAL)
	#define USE_sysportin
	#define EXT_sysportin
	#define GET_sysportin(fl)  CAL_CMGETAPI( "sysportin" ) 
	#define CAL_sysportin  sysportin
	#define CHK_sysportin  TRUE
	#define EXP_sysportin  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportin", (RTS_UINTPTR)sysportin, 1, RTSITF_GET_SIGNATURE(0, 0xD23F618E), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysPortsysportin
	#define EXT_SysPortsysportin
	#define GET_SysPortsysportin  ERR_OK
	#define CAL_SysPortsysportin  sysportin
	#define CHK_SysPortsysportin  TRUE
	#define EXP_SysPortsysportin  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportin", (RTS_UINTPTR)sysportin, 1, RTSITF_GET_SIGNATURE(0, 0xD23F618E), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sysportin
	#define EXT_sysportin
	#define GET_sysportin(fl)  CAL_CMGETAPI( "sysportin" ) 
	#define CAL_sysportin  sysportin
	#define CHK_sysportin  TRUE
	#define EXP_sysportin  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportin", (RTS_UINTPTR)sysportin, 1, RTSITF_GET_SIGNATURE(0, 0xD23F618E), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sysportin  PFSYSPORTIN_IEC pfsysportin;
	#define EXT_sysportin  extern PFSYSPORTIN_IEC pfsysportin;
	#define GET_sysportin(fl)  s_pfCMGetAPI2( "sysportin", (RTS_VOID_FCTPTR *)&pfsysportin, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xD23F618E), 0x03050500)
	#define CAL_sysportin  pfsysportin
	#define CHK_sysportin  (pfsysportin != NULL)
	#define EXP_sysportin   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportin", (RTS_UINTPTR)sysportin, 1, RTSITF_GET_SIGNATURE(0, 0xD23F618E), 0x03050500) 
#endif


/**
 * <description>This function reads the current UDINT-value at the given port address.</description>
 * <result><p>RESULT: Input port value that was read.</p></result>
 */
typedef struct tagsysportind_struct
{
	RTS_IEC_UDINT ulAddress;			/* VAR_INPUT */	/* <param name="ulAddress" type="IN">Port address</param> */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param> */
	RTS_IEC_UDINT SysPortInD;			/* VAR_OUTPUT */	
} sysportind_struct;

void CDECL CDECL_EXT sysportind(sysportind_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSPORTIND_IEC) (sysportind_struct *p);
#if defined(SYSPORT_NOTIMPLEMENTED) || defined(SYSPORTIND_NOTIMPLEMENTED)
	#define USE_sysportind
	#define EXT_sysportind
	#define GET_sysportind(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysportind(p0) 
	#define CHK_sysportind  FALSE
	#define EXP_sysportind  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysportind
	#define EXT_sysportind
	#define GET_sysportind(fl)  CAL_CMGETAPI( "sysportind" ) 
	#define CAL_sysportind  sysportind
	#define CHK_sysportind  TRUE
	#define EXP_sysportind  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportind", (RTS_UINTPTR)sysportind, 1, RTSITF_GET_SIGNATURE(0, 0x40C580DD), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSPORT_EXTERNAL)
	#define USE_sysportind
	#define EXT_sysportind
	#define GET_sysportind(fl)  CAL_CMGETAPI( "sysportind" ) 
	#define CAL_sysportind  sysportind
	#define CHK_sysportind  TRUE
	#define EXP_sysportind  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportind", (RTS_UINTPTR)sysportind, 1, RTSITF_GET_SIGNATURE(0, 0x40C580DD), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysPortsysportind
	#define EXT_SysPortsysportind
	#define GET_SysPortsysportind  ERR_OK
	#define CAL_SysPortsysportind  sysportind
	#define CHK_SysPortsysportind  TRUE
	#define EXP_SysPortsysportind  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportind", (RTS_UINTPTR)sysportind, 1, RTSITF_GET_SIGNATURE(0, 0x40C580DD), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sysportind
	#define EXT_sysportind
	#define GET_sysportind(fl)  CAL_CMGETAPI( "sysportind" ) 
	#define CAL_sysportind  sysportind
	#define CHK_sysportind  TRUE
	#define EXP_sysportind  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportind", (RTS_UINTPTR)sysportind, 1, RTSITF_GET_SIGNATURE(0, 0x40C580DD), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sysportind  PFSYSPORTIND_IEC pfsysportind;
	#define EXT_sysportind  extern PFSYSPORTIND_IEC pfsysportind;
	#define GET_sysportind(fl)  s_pfCMGetAPI2( "sysportind", (RTS_VOID_FCTPTR *)&pfsysportind, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x40C580DD), 0x03050500)
	#define CAL_sysportind  pfsysportind
	#define CHK_sysportind  (pfsysportind != NULL)
	#define EXP_sysportind   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportind", (RTS_UINTPTR)sysportind, 1, RTSITF_GET_SIGNATURE(0, 0x40C580DD), 0x03050500) 
#endif


/**
 * <description>This function reads the current WORD-value at the given port address.</description>
 * <result><p>RESULT: Input port value that was read.</p></result>
 */
typedef struct tagsysportinw_struct
{
	RTS_IEC_UDINT ulAddress;			/* VAR_INPUT */	/* <param name="ulAddress" type="IN">Port address</param> */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param> */
	RTS_IEC_WORD SysPortInW;			/* VAR_OUTPUT */	
} sysportinw_struct;

void CDECL CDECL_EXT sysportinw(sysportinw_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSPORTINW_IEC) (sysportinw_struct *p);
#if defined(SYSPORT_NOTIMPLEMENTED) || defined(SYSPORTINW_NOTIMPLEMENTED)
	#define USE_sysportinw
	#define EXT_sysportinw
	#define GET_sysportinw(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysportinw(p0) 
	#define CHK_sysportinw  FALSE
	#define EXP_sysportinw  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysportinw
	#define EXT_sysportinw
	#define GET_sysportinw(fl)  CAL_CMGETAPI( "sysportinw" ) 
	#define CAL_sysportinw  sysportinw
	#define CHK_sysportinw  TRUE
	#define EXP_sysportinw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportinw", (RTS_UINTPTR)sysportinw, 1, RTSITF_GET_SIGNATURE(0, 0x8D4FCB60), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSPORT_EXTERNAL)
	#define USE_sysportinw
	#define EXT_sysportinw
	#define GET_sysportinw(fl)  CAL_CMGETAPI( "sysportinw" ) 
	#define CAL_sysportinw  sysportinw
	#define CHK_sysportinw  TRUE
	#define EXP_sysportinw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportinw", (RTS_UINTPTR)sysportinw, 1, RTSITF_GET_SIGNATURE(0, 0x8D4FCB60), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysPortsysportinw
	#define EXT_SysPortsysportinw
	#define GET_SysPortsysportinw  ERR_OK
	#define CAL_SysPortsysportinw  sysportinw
	#define CHK_SysPortsysportinw  TRUE
	#define EXP_SysPortsysportinw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportinw", (RTS_UINTPTR)sysportinw, 1, RTSITF_GET_SIGNATURE(0, 0x8D4FCB60), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sysportinw
	#define EXT_sysportinw
	#define GET_sysportinw(fl)  CAL_CMGETAPI( "sysportinw" ) 
	#define CAL_sysportinw  sysportinw
	#define CHK_sysportinw  TRUE
	#define EXP_sysportinw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportinw", (RTS_UINTPTR)sysportinw, 1, RTSITF_GET_SIGNATURE(0, 0x8D4FCB60), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sysportinw  PFSYSPORTINW_IEC pfsysportinw;
	#define EXT_sysportinw  extern PFSYSPORTINW_IEC pfsysportinw;
	#define GET_sysportinw(fl)  s_pfCMGetAPI2( "sysportinw", (RTS_VOID_FCTPTR *)&pfsysportinw, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x8D4FCB60), 0x03050500)
	#define CAL_sysportinw  pfsysportinw
	#define CHK_sysportinw  (pfsysportinw != NULL)
	#define EXP_sysportinw   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportinw", (RTS_UINTPTR)sysportinw, 1, RTSITF_GET_SIGNATURE(0, 0x8D4FCB60), 0x03050500) 
#endif


/**
 * <description>This function writes the specified BYTE-value on the certain port address.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysportout_struct
{
	RTS_IEC_UDINT ulAddress;			/* VAR_INPUT */	/* <param name="ulAddress" type="IN">Port address</param> */
	RTS_IEC_BYTE byVal;					/* VAR_INPUT */	/* <param name="byVal" type="IN">Value to be written to the port.</param> */
	RTS_IEC_RESULT SysPortOut;			/* VAR_OUTPUT */	
} sysportout_struct;

void CDECL CDECL_EXT sysportout(sysportout_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSPORTOUT_IEC) (sysportout_struct *p);
#if defined(SYSPORT_NOTIMPLEMENTED) || defined(SYSPORTOUT_NOTIMPLEMENTED)
	#define USE_sysportout
	#define EXT_sysportout
	#define GET_sysportout(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysportout(p0) 
	#define CHK_sysportout  FALSE
	#define EXP_sysportout  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysportout
	#define EXT_sysportout
	#define GET_sysportout(fl)  CAL_CMGETAPI( "sysportout" ) 
	#define CAL_sysportout  sysportout
	#define CHK_sysportout  TRUE
	#define EXP_sysportout  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportout", (RTS_UINTPTR)sysportout, 1, RTSITF_GET_SIGNATURE(0, 0x8A8205C9), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSPORT_EXTERNAL)
	#define USE_sysportout
	#define EXT_sysportout
	#define GET_sysportout(fl)  CAL_CMGETAPI( "sysportout" ) 
	#define CAL_sysportout  sysportout
	#define CHK_sysportout  TRUE
	#define EXP_sysportout  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportout", (RTS_UINTPTR)sysportout, 1, RTSITF_GET_SIGNATURE(0, 0x8A8205C9), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysPortsysportout
	#define EXT_SysPortsysportout
	#define GET_SysPortsysportout  ERR_OK
	#define CAL_SysPortsysportout  sysportout
	#define CHK_SysPortsysportout  TRUE
	#define EXP_SysPortsysportout  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportout", (RTS_UINTPTR)sysportout, 1, RTSITF_GET_SIGNATURE(0, 0x8A8205C9), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sysportout
	#define EXT_sysportout
	#define GET_sysportout(fl)  CAL_CMGETAPI( "sysportout" ) 
	#define CAL_sysportout  sysportout
	#define CHK_sysportout  TRUE
	#define EXP_sysportout  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportout", (RTS_UINTPTR)sysportout, 1, RTSITF_GET_SIGNATURE(0, 0x8A8205C9), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sysportout  PFSYSPORTOUT_IEC pfsysportout;
	#define EXT_sysportout  extern PFSYSPORTOUT_IEC pfsysportout;
	#define GET_sysportout(fl)  s_pfCMGetAPI2( "sysportout", (RTS_VOID_FCTPTR *)&pfsysportout, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x8A8205C9), 0x03050500)
	#define CAL_sysportout  pfsysportout
	#define CHK_sysportout  (pfsysportout != NULL)
	#define EXP_sysportout   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportout", (RTS_UINTPTR)sysportout, 1, RTSITF_GET_SIGNATURE(0, 0x8A8205C9), 0x03050500) 
#endif


/**
 * <description>This function writes the specified UDINT-value on the certain port address.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysportoutd_struct
{
	RTS_IEC_UDINT ulAddress;			/* VAR_INPUT */	/* <param name="ulAddress" type="IN">Port address</param> */
	RTS_IEC_UDINT udVal;				/* VAR_INPUT */	/* <param name="udVal" type="IN">Value to be written to the port.</param> */
	RTS_IEC_RESULT SysPortOutD;			/* VAR_OUTPUT */	
} sysportoutd_struct;

void CDECL CDECL_EXT sysportoutd(sysportoutd_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSPORTOUTD_IEC) (sysportoutd_struct *p);
#if defined(SYSPORT_NOTIMPLEMENTED) || defined(SYSPORTOUTD_NOTIMPLEMENTED)
	#define USE_sysportoutd
	#define EXT_sysportoutd
	#define GET_sysportoutd(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysportoutd(p0) 
	#define CHK_sysportoutd  FALSE
	#define EXP_sysportoutd  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysportoutd
	#define EXT_sysportoutd
	#define GET_sysportoutd(fl)  CAL_CMGETAPI( "sysportoutd" ) 
	#define CAL_sysportoutd  sysportoutd
	#define CHK_sysportoutd  TRUE
	#define EXP_sysportoutd  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportoutd", (RTS_UINTPTR)sysportoutd, 1, RTSITF_GET_SIGNATURE(0, 0xB129E67D), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSPORT_EXTERNAL)
	#define USE_sysportoutd
	#define EXT_sysportoutd
	#define GET_sysportoutd(fl)  CAL_CMGETAPI( "sysportoutd" ) 
	#define CAL_sysportoutd  sysportoutd
	#define CHK_sysportoutd  TRUE
	#define EXP_sysportoutd  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportoutd", (RTS_UINTPTR)sysportoutd, 1, RTSITF_GET_SIGNATURE(0, 0xB129E67D), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysPortsysportoutd
	#define EXT_SysPortsysportoutd
	#define GET_SysPortsysportoutd  ERR_OK
	#define CAL_SysPortsysportoutd  sysportoutd
	#define CHK_SysPortsysportoutd  TRUE
	#define EXP_SysPortsysportoutd  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportoutd", (RTS_UINTPTR)sysportoutd, 1, RTSITF_GET_SIGNATURE(0, 0xB129E67D), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sysportoutd
	#define EXT_sysportoutd
	#define GET_sysportoutd(fl)  CAL_CMGETAPI( "sysportoutd" ) 
	#define CAL_sysportoutd  sysportoutd
	#define CHK_sysportoutd  TRUE
	#define EXP_sysportoutd  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportoutd", (RTS_UINTPTR)sysportoutd, 1, RTSITF_GET_SIGNATURE(0, 0xB129E67D), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sysportoutd  PFSYSPORTOUTD_IEC pfsysportoutd;
	#define EXT_sysportoutd  extern PFSYSPORTOUTD_IEC pfsysportoutd;
	#define GET_sysportoutd(fl)  s_pfCMGetAPI2( "sysportoutd", (RTS_VOID_FCTPTR *)&pfsysportoutd, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xB129E67D), 0x03050500)
	#define CAL_sysportoutd  pfsysportoutd
	#define CHK_sysportoutd  (pfsysportoutd != NULL)
	#define EXP_sysportoutd   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportoutd", (RTS_UINTPTR)sysportoutd, 1, RTSITF_GET_SIGNATURE(0, 0xB129E67D), 0x03050500) 
#endif


/**
 * <description>This function writes the specified WORD-value on the certain port address.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysportoutw_struct
{
	RTS_IEC_UDINT ulAddress;			/* VAR_INPUT */	/* <param name="ulAddress" type="IN">Port address</param> */
	RTS_IEC_WORD usVal;					/* VAR_INPUT */	/* <param name="usVal" type="IN">Value to be written to the port.</param> */
	RTS_IEC_RESULT SysPortOutW;			/* VAR_OUTPUT */	
} sysportoutw_struct;

void CDECL CDECL_EXT sysportoutw(sysportoutw_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSPORTOUTW_IEC) (sysportoutw_struct *p);
#if defined(SYSPORT_NOTIMPLEMENTED) || defined(SYSPORTOUTW_NOTIMPLEMENTED)
	#define USE_sysportoutw
	#define EXT_sysportoutw
	#define GET_sysportoutw(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysportoutw(p0) 
	#define CHK_sysportoutw  FALSE
	#define EXP_sysportoutw  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysportoutw
	#define EXT_sysportoutw
	#define GET_sysportoutw(fl)  CAL_CMGETAPI( "sysportoutw" ) 
	#define CAL_sysportoutw  sysportoutw
	#define CHK_sysportoutw  TRUE
	#define EXP_sysportoutw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportoutw", (RTS_UINTPTR)sysportoutw, 1, RTSITF_GET_SIGNATURE(0, 0x19126DF2), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSPORT_EXTERNAL)
	#define USE_sysportoutw
	#define EXT_sysportoutw
	#define GET_sysportoutw(fl)  CAL_CMGETAPI( "sysportoutw" ) 
	#define CAL_sysportoutw  sysportoutw
	#define CHK_sysportoutw  TRUE
	#define EXP_sysportoutw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportoutw", (RTS_UINTPTR)sysportoutw, 1, RTSITF_GET_SIGNATURE(0, 0x19126DF2), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysPortsysportoutw
	#define EXT_SysPortsysportoutw
	#define GET_SysPortsysportoutw  ERR_OK
	#define CAL_SysPortsysportoutw  sysportoutw
	#define CHK_SysPortsysportoutw  TRUE
	#define EXP_SysPortsysportoutw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportoutw", (RTS_UINTPTR)sysportoutw, 1, RTSITF_GET_SIGNATURE(0, 0x19126DF2), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sysportoutw
	#define EXT_sysportoutw
	#define GET_sysportoutw(fl)  CAL_CMGETAPI( "sysportoutw" ) 
	#define CAL_sysportoutw  sysportoutw
	#define CHK_sysportoutw  TRUE
	#define EXP_sysportoutw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportoutw", (RTS_UINTPTR)sysportoutw, 1, RTSITF_GET_SIGNATURE(0, 0x19126DF2), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sysportoutw  PFSYSPORTOUTW_IEC pfsysportoutw;
	#define EXT_sysportoutw  extern PFSYSPORTOUTW_IEC pfsysportoutw;
	#define GET_sysportoutw(fl)  s_pfCMGetAPI2( "sysportoutw", (RTS_VOID_FCTPTR *)&pfsysportoutw, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x19126DF2), 0x03050500)
	#define CAL_sysportoutw  pfsysportoutw
	#define CHK_sysportoutw  (pfsysportoutw != NULL)
	#define EXP_sysportoutw   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysportoutw", (RTS_UINTPTR)sysportoutw, 1, RTSITF_GET_SIGNATURE(0, 0x19126DF2), 0x03050500) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysPortOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysPortOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description> Function to read in a device port </description>
 * <param name="ulAddress" type="IN">Port address</param>
 * <param name="pResult" type="OUT">Result</param>
 * <result>input port value</result>
 */
RTS_UI8 CDECL SysPortIn(RTS_UI32 ulAddress, RTS_RESULT *pResult);
typedef RTS_UI8 (CDECL * PFSYSPORTIN) (RTS_UI32 ulAddress, RTS_RESULT *pResult);
#if defined(SYSPORT_NOTIMPLEMENTED) || defined(SYSPORTIN_NOTIMPLEMENTED)
	#define USE_SysPortIn
	#define EXT_SysPortIn
	#define GET_SysPortIn(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysPortIn(p0,p1)  (RTS_UI8)ERR_NOTIMPLEMENTED
	#define CHK_SysPortIn  FALSE
	#define EXP_SysPortIn  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysPortIn
	#define EXT_SysPortIn
	#define GET_SysPortIn(fl)  CAL_CMGETAPI( "SysPortIn" ) 
	#define CAL_SysPortIn  SysPortIn
	#define CHK_SysPortIn  TRUE
	#define EXP_SysPortIn  CAL_CMEXPAPI( "SysPortIn" ) 
#elif defined(MIXED_LINK) && !defined(SYSPORT_EXTERNAL)
	#define USE_SysPortIn
	#define EXT_SysPortIn
	#define GET_SysPortIn(fl)  CAL_CMGETAPI( "SysPortIn" ) 
	#define CAL_SysPortIn  SysPortIn
	#define CHK_SysPortIn  TRUE
	#define EXP_SysPortIn  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysPortIn", (RTS_UINTPTR)SysPortIn, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysPortSysPortIn
	#define EXT_SysPortSysPortIn
	#define GET_SysPortSysPortIn  ERR_OK
	#define CAL_SysPortSysPortIn pISysPort->ISysPortIn
	#define CHK_SysPortSysPortIn (pISysPort != NULL)
	#define EXP_SysPortSysPortIn  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysPortIn
	#define EXT_SysPortIn
	#define GET_SysPortIn(fl)  CAL_CMGETAPI( "SysPortIn" ) 
	#define CAL_SysPortIn pISysPort->ISysPortIn
	#define CHK_SysPortIn (pISysPort != NULL)
	#define EXP_SysPortIn  CAL_CMEXPAPI( "SysPortIn" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysPortIn  PFSYSPORTIN pfSysPortIn;
	#define EXT_SysPortIn  extern PFSYSPORTIN pfSysPortIn;
	#define GET_SysPortIn(fl)  s_pfCMGetAPI2( "SysPortIn", (RTS_VOID_FCTPTR *)&pfSysPortIn, (fl), 0, 0)
	#define CAL_SysPortIn  pfSysPortIn
	#define CHK_SysPortIn  (pfSysPortIn != NULL)
	#define EXP_SysPortIn  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysPortIn", (RTS_UINTPTR)SysPortIn, 0, 0) 
#endif




/**
 * <description> Function to read in a device port </description>
 * <param name="ulAddress" type="IN">Port address</param>
 * <param name="pResult" type="OUT">Result</param>
 * <result>input port value</result>
 */
RTS_UI16 CDECL SysPortInW(RTS_UI32 ulAddress, RTS_RESULT *pResult);
typedef RTS_UI16 (CDECL * PFSYSPORTINW) (RTS_UI32 ulAddress, RTS_RESULT *pResult);
#if defined(SYSPORT_NOTIMPLEMENTED) || defined(SYSPORTINW_NOTIMPLEMENTED)
	#define USE_SysPortInW
	#define EXT_SysPortInW
	#define GET_SysPortInW(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysPortInW(p0,p1)  (RTS_UI16)ERR_NOTIMPLEMENTED
	#define CHK_SysPortInW  FALSE
	#define EXP_SysPortInW  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysPortInW
	#define EXT_SysPortInW
	#define GET_SysPortInW(fl)  CAL_CMGETAPI( "SysPortInW" ) 
	#define CAL_SysPortInW  SysPortInW
	#define CHK_SysPortInW  TRUE
	#define EXP_SysPortInW  CAL_CMEXPAPI( "SysPortInW" ) 
#elif defined(MIXED_LINK) && !defined(SYSPORT_EXTERNAL)
	#define USE_SysPortInW
	#define EXT_SysPortInW
	#define GET_SysPortInW(fl)  CAL_CMGETAPI( "SysPortInW" ) 
	#define CAL_SysPortInW  SysPortInW
	#define CHK_SysPortInW  TRUE
	#define EXP_SysPortInW  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysPortInW", (RTS_UINTPTR)SysPortInW, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysPortSysPortInW
	#define EXT_SysPortSysPortInW
	#define GET_SysPortSysPortInW  ERR_OK
	#define CAL_SysPortSysPortInW pISysPort->ISysPortInW
	#define CHK_SysPortSysPortInW (pISysPort != NULL)
	#define EXP_SysPortSysPortInW  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysPortInW
	#define EXT_SysPortInW
	#define GET_SysPortInW(fl)  CAL_CMGETAPI( "SysPortInW" ) 
	#define CAL_SysPortInW pISysPort->ISysPortInW
	#define CHK_SysPortInW (pISysPort != NULL)
	#define EXP_SysPortInW  CAL_CMEXPAPI( "SysPortInW" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysPortInW  PFSYSPORTINW pfSysPortInW;
	#define EXT_SysPortInW  extern PFSYSPORTINW pfSysPortInW;
	#define GET_SysPortInW(fl)  s_pfCMGetAPI2( "SysPortInW", (RTS_VOID_FCTPTR *)&pfSysPortInW, (fl), 0, 0)
	#define CAL_SysPortInW  pfSysPortInW
	#define CHK_SysPortInW  (pfSysPortInW != NULL)
	#define EXP_SysPortInW  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysPortInW", (RTS_UINTPTR)SysPortInW, 0, 0) 
#endif




/**
 * <description> Function to read in a device port </description>
 * <param name="ulAddress" type="IN">Port address</param>
 * <param name="pResult" type="OUT">Result</param>
 * <result>input port value</result>
 */
RTS_UI32 CDECL SysPortInD(RTS_UI32 ulAddress, RTS_RESULT *pResult);
typedef RTS_UI32 (CDECL * PFSYSPORTIND) (RTS_UI32 ulAddress, RTS_RESULT *pResult);
#if defined(SYSPORT_NOTIMPLEMENTED) || defined(SYSPORTIND_NOTIMPLEMENTED)
	#define USE_SysPortInD
	#define EXT_SysPortInD
	#define GET_SysPortInD(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysPortInD(p0,p1)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_SysPortInD  FALSE
	#define EXP_SysPortInD  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysPortInD
	#define EXT_SysPortInD
	#define GET_SysPortInD(fl)  CAL_CMGETAPI( "SysPortInD" ) 
	#define CAL_SysPortInD  SysPortInD
	#define CHK_SysPortInD  TRUE
	#define EXP_SysPortInD  CAL_CMEXPAPI( "SysPortInD" ) 
#elif defined(MIXED_LINK) && !defined(SYSPORT_EXTERNAL)
	#define USE_SysPortInD
	#define EXT_SysPortInD
	#define GET_SysPortInD(fl)  CAL_CMGETAPI( "SysPortInD" ) 
	#define CAL_SysPortInD  SysPortInD
	#define CHK_SysPortInD  TRUE
	#define EXP_SysPortInD  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysPortInD", (RTS_UINTPTR)SysPortInD, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysPortSysPortInD
	#define EXT_SysPortSysPortInD
	#define GET_SysPortSysPortInD  ERR_OK
	#define CAL_SysPortSysPortInD pISysPort->ISysPortInD
	#define CHK_SysPortSysPortInD (pISysPort != NULL)
	#define EXP_SysPortSysPortInD  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysPortInD
	#define EXT_SysPortInD
	#define GET_SysPortInD(fl)  CAL_CMGETAPI( "SysPortInD" ) 
	#define CAL_SysPortInD pISysPort->ISysPortInD
	#define CHK_SysPortInD (pISysPort != NULL)
	#define EXP_SysPortInD  CAL_CMEXPAPI( "SysPortInD" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysPortInD  PFSYSPORTIND pfSysPortInD;
	#define EXT_SysPortInD  extern PFSYSPORTIND pfSysPortInD;
	#define GET_SysPortInD(fl)  s_pfCMGetAPI2( "SysPortInD", (RTS_VOID_FCTPTR *)&pfSysPortInD, (fl), 0, 0)
	#define CAL_SysPortInD  pfSysPortInD
	#define CHK_SysPortInD  (pfSysPortInD != NULL)
	#define EXP_SysPortInD  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysPortInD", (RTS_UINTPTR)SysPortInD, 0, 0) 
#endif




/**
 * <description> Function to write a value to a device port </description>
 * <param name="ulAddress" type="IN">Port address</param>
 * <param name="byValue" type="IN">Value</param>
 * <result>ERR_OK</result>
 */
RTS_RESULT CDECL SysPortOut(RTS_UI32 ulAddress, RTS_UI8 byValue);
typedef RTS_RESULT (CDECL * PFSYSPORTOUT) (RTS_UI32 ulAddress, RTS_UI8 byValue);
#if defined(SYSPORT_NOTIMPLEMENTED) || defined(SYSPORTOUT_NOTIMPLEMENTED)
	#define USE_SysPortOut
	#define EXT_SysPortOut
	#define GET_SysPortOut(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysPortOut(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysPortOut  FALSE
	#define EXP_SysPortOut  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysPortOut
	#define EXT_SysPortOut
	#define GET_SysPortOut(fl)  CAL_CMGETAPI( "SysPortOut" ) 
	#define CAL_SysPortOut  SysPortOut
	#define CHK_SysPortOut  TRUE
	#define EXP_SysPortOut  CAL_CMEXPAPI( "SysPortOut" ) 
#elif defined(MIXED_LINK) && !defined(SYSPORT_EXTERNAL)
	#define USE_SysPortOut
	#define EXT_SysPortOut
	#define GET_SysPortOut(fl)  CAL_CMGETAPI( "SysPortOut" ) 
	#define CAL_SysPortOut  SysPortOut
	#define CHK_SysPortOut  TRUE
	#define EXP_SysPortOut  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysPortOut", (RTS_UINTPTR)SysPortOut, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysPortSysPortOut
	#define EXT_SysPortSysPortOut
	#define GET_SysPortSysPortOut  ERR_OK
	#define CAL_SysPortSysPortOut pISysPort->ISysPortOut
	#define CHK_SysPortSysPortOut (pISysPort != NULL)
	#define EXP_SysPortSysPortOut  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysPortOut
	#define EXT_SysPortOut
	#define GET_SysPortOut(fl)  CAL_CMGETAPI( "SysPortOut" ) 
	#define CAL_SysPortOut pISysPort->ISysPortOut
	#define CHK_SysPortOut (pISysPort != NULL)
	#define EXP_SysPortOut  CAL_CMEXPAPI( "SysPortOut" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysPortOut  PFSYSPORTOUT pfSysPortOut;
	#define EXT_SysPortOut  extern PFSYSPORTOUT pfSysPortOut;
	#define GET_SysPortOut(fl)  s_pfCMGetAPI2( "SysPortOut", (RTS_VOID_FCTPTR *)&pfSysPortOut, (fl), 0, 0)
	#define CAL_SysPortOut  pfSysPortOut
	#define CHK_SysPortOut  (pfSysPortOut != NULL)
	#define EXP_SysPortOut  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysPortOut", (RTS_UINTPTR)SysPortOut, 0, 0) 
#endif




/**
 * <description> Function to write a value to a device port </description>
 * <param name="ulAddress" type="IN">Port address</param>
 * <param name="wValue" type="IN">Value</param>
 * <result>ERR_OK</result>
 */
RTS_RESULT CDECL SysPortOutW(RTS_UI32 ulAddress, RTS_UI16 usValue);
typedef RTS_RESULT (CDECL * PFSYSPORTOUTW) (RTS_UI32 ulAddress, RTS_UI16 usValue);
#if defined(SYSPORT_NOTIMPLEMENTED) || defined(SYSPORTOUTW_NOTIMPLEMENTED)
	#define USE_SysPortOutW
	#define EXT_SysPortOutW
	#define GET_SysPortOutW(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysPortOutW(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysPortOutW  FALSE
	#define EXP_SysPortOutW  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysPortOutW
	#define EXT_SysPortOutW
	#define GET_SysPortOutW(fl)  CAL_CMGETAPI( "SysPortOutW" ) 
	#define CAL_SysPortOutW  SysPortOutW
	#define CHK_SysPortOutW  TRUE
	#define EXP_SysPortOutW  CAL_CMEXPAPI( "SysPortOutW" ) 
#elif defined(MIXED_LINK) && !defined(SYSPORT_EXTERNAL)
	#define USE_SysPortOutW
	#define EXT_SysPortOutW
	#define GET_SysPortOutW(fl)  CAL_CMGETAPI( "SysPortOutW" ) 
	#define CAL_SysPortOutW  SysPortOutW
	#define CHK_SysPortOutW  TRUE
	#define EXP_SysPortOutW  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysPortOutW", (RTS_UINTPTR)SysPortOutW, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysPortSysPortOutW
	#define EXT_SysPortSysPortOutW
	#define GET_SysPortSysPortOutW  ERR_OK
	#define CAL_SysPortSysPortOutW pISysPort->ISysPortOutW
	#define CHK_SysPortSysPortOutW (pISysPort != NULL)
	#define EXP_SysPortSysPortOutW  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysPortOutW
	#define EXT_SysPortOutW
	#define GET_SysPortOutW(fl)  CAL_CMGETAPI( "SysPortOutW" ) 
	#define CAL_SysPortOutW pISysPort->ISysPortOutW
	#define CHK_SysPortOutW (pISysPort != NULL)
	#define EXP_SysPortOutW  CAL_CMEXPAPI( "SysPortOutW" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysPortOutW  PFSYSPORTOUTW pfSysPortOutW;
	#define EXT_SysPortOutW  extern PFSYSPORTOUTW pfSysPortOutW;
	#define GET_SysPortOutW(fl)  s_pfCMGetAPI2( "SysPortOutW", (RTS_VOID_FCTPTR *)&pfSysPortOutW, (fl), 0, 0)
	#define CAL_SysPortOutW  pfSysPortOutW
	#define CHK_SysPortOutW  (pfSysPortOutW != NULL)
	#define EXP_SysPortOutW  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysPortOutW", (RTS_UINTPTR)SysPortOutW, 0, 0) 
#endif




/**
 * <description> Function to write a value to a device port </description>
 * <param name="ulAddress" type="IN">Port address</param>
 * <param name="dwValue" type="IN">Value</param>
 * <result>ERR_OK</result>
 */
RTS_RESULT CDECL SysPortOutD(RTS_UI32 ulAddress, RTS_UI32 ulValue);
typedef RTS_RESULT (CDECL * PFSYSPORTOUTD) (RTS_UI32 ulAddress, RTS_UI32 ulValue);
#if defined(SYSPORT_NOTIMPLEMENTED) || defined(SYSPORTOUTD_NOTIMPLEMENTED)
	#define USE_SysPortOutD
	#define EXT_SysPortOutD
	#define GET_SysPortOutD(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysPortOutD(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysPortOutD  FALSE
	#define EXP_SysPortOutD  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysPortOutD
	#define EXT_SysPortOutD
	#define GET_SysPortOutD(fl)  CAL_CMGETAPI( "SysPortOutD" ) 
	#define CAL_SysPortOutD  SysPortOutD
	#define CHK_SysPortOutD  TRUE
	#define EXP_SysPortOutD  CAL_CMEXPAPI( "SysPortOutD" ) 
#elif defined(MIXED_LINK) && !defined(SYSPORT_EXTERNAL)
	#define USE_SysPortOutD
	#define EXT_SysPortOutD
	#define GET_SysPortOutD(fl)  CAL_CMGETAPI( "SysPortOutD" ) 
	#define CAL_SysPortOutD  SysPortOutD
	#define CHK_SysPortOutD  TRUE
	#define EXP_SysPortOutD  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysPortOutD", (RTS_UINTPTR)SysPortOutD, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysPortSysPortOutD
	#define EXT_SysPortSysPortOutD
	#define GET_SysPortSysPortOutD  ERR_OK
	#define CAL_SysPortSysPortOutD pISysPort->ISysPortOutD
	#define CHK_SysPortSysPortOutD (pISysPort != NULL)
	#define EXP_SysPortSysPortOutD  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysPortOutD
	#define EXT_SysPortOutD
	#define GET_SysPortOutD(fl)  CAL_CMGETAPI( "SysPortOutD" ) 
	#define CAL_SysPortOutD pISysPort->ISysPortOutD
	#define CHK_SysPortOutD (pISysPort != NULL)
	#define EXP_SysPortOutD  CAL_CMEXPAPI( "SysPortOutD" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysPortOutD  PFSYSPORTOUTD pfSysPortOutD;
	#define EXT_SysPortOutD  extern PFSYSPORTOUTD pfSysPortOutD;
	#define GET_SysPortOutD(fl)  s_pfCMGetAPI2( "SysPortOutD", (RTS_VOID_FCTPTR *)&pfSysPortOutD, (fl), 0, 0)
	#define CAL_SysPortOutD  pfSysPortOutD
	#define CHK_SysPortOutD  (pfSysPortOutD != NULL)
	#define EXP_SysPortOutD  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysPortOutD", (RTS_UINTPTR)SysPortOutD, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSPORTIN ISysPortIn;
 	PFSYSPORTINW ISysPortInW;
 	PFSYSPORTIND ISysPortInD;
 	PFSYSPORTOUT ISysPortOut;
 	PFSYSPORTOUTW ISysPortOutW;
 	PFSYSPORTOUTD ISysPortOutD;
 } ISysPort_C;

#ifdef CPLUSPLUS
class ISysPort : public IBase
{
	public:
		virtual RTS_UI8 CDECL ISysPortIn(RTS_UI32 ulAddress, RTS_RESULT *pResult) =0;
		virtual RTS_UI16 CDECL ISysPortInW(RTS_UI32 ulAddress, RTS_RESULT *pResult) =0;
		virtual RTS_UI32 CDECL ISysPortInD(RTS_UI32 ulAddress, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISysPortOut(RTS_UI32 ulAddress, RTS_UI8 byValue) =0;
		virtual RTS_RESULT CDECL ISysPortOutW(RTS_UI32 ulAddress, RTS_UI16 usValue) =0;
		virtual RTS_RESULT CDECL ISysPortOutD(RTS_UI32 ulAddress, RTS_UI32 ulValue) =0;
};
	#ifndef ITF_SysPort
		#define ITF_SysPort static ISysPort *pISysPort = NULL;
	#endif
	#define EXTITF_SysPort
#else	/*CPLUSPLUS*/
	typedef ISysPort_C		ISysPort;
	#ifndef ITF_SysPort
		#define ITF_SysPort
	#endif
	#define EXTITF_SysPort
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSPORTITF_H_*/
