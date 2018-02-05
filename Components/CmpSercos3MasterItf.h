 /**
 * <interfacename>CmpSercos3Master</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _CMPSERCOS3MASTERITF_H_
#define _CMPSERCOS3MASTERITF_H_

#include "CmpStd.h"

 

 




/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>csmd_calculatetiming_func</description>
 */
typedef struct tagcsmd_calculatetiming_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_WORD wTimingMethod;			/* VAR_INPUT */	
	RTS_IEC_WORD wIPChannelBandwidth;	/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_CalculateTiming_Func;	/* VAR_OUTPUT */	
} csmd_calculatetiming_func_struct;

void CDECL CDECL_EXT csmd_calculatetiming_func(csmd_calculatetiming_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_CALCULATETIMING_FUNC_IEC) (csmd_calculatetiming_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_CALCULATETIMING_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_calculatetiming_func
	#define EXT_csmd_calculatetiming_func
	#define GET_csmd_calculatetiming_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_calculatetiming_func(p0) 
	#define CHK_csmd_calculatetiming_func  FALSE
	#define EXP_csmd_calculatetiming_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_calculatetiming_func
	#define EXT_csmd_calculatetiming_func
	#define GET_csmd_calculatetiming_func(fl)  CAL_CMGETAPI( "csmd_calculatetiming_func" ) 
	#define CAL_csmd_calculatetiming_func  csmd_calculatetiming_func
	#define CHK_csmd_calculatetiming_func  TRUE
	#define EXP_csmd_calculatetiming_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_calculatetiming_func", (RTS_UINTPTR)csmd_calculatetiming_func, 1, 0x66F3AB88, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_calculatetiming_func
	#define EXT_csmd_calculatetiming_func
	#define GET_csmd_calculatetiming_func(fl)  CAL_CMGETAPI( "csmd_calculatetiming_func" ) 
	#define CAL_csmd_calculatetiming_func  csmd_calculatetiming_func
	#define CHK_csmd_calculatetiming_func  TRUE
	#define EXP_csmd_calculatetiming_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_calculatetiming_func", (RTS_UINTPTR)csmd_calculatetiming_func, 1, 0x66F3AB88, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_calculatetiming_func
	#define EXT_CmpSercos3Mastercsmd_calculatetiming_func
	#define GET_CmpSercos3Mastercsmd_calculatetiming_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_calculatetiming_func  csmd_calculatetiming_func
	#define CHK_CmpSercos3Mastercsmd_calculatetiming_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_calculatetiming_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_calculatetiming_func", (RTS_UINTPTR)csmd_calculatetiming_func, 1, 0x66F3AB88, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_calculatetiming_func
	#define EXT_csmd_calculatetiming_func
	#define GET_csmd_calculatetiming_func(fl)  CAL_CMGETAPI( "csmd_calculatetiming_func" ) 
	#define CAL_csmd_calculatetiming_func  csmd_calculatetiming_func
	#define CHK_csmd_calculatetiming_func  TRUE
	#define EXP_csmd_calculatetiming_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_calculatetiming_func", (RTS_UINTPTR)csmd_calculatetiming_func, 1, 0x66F3AB88, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_calculatetiming_func  PFCSMD_CALCULATETIMING_FUNC_IEC pfcsmd_calculatetiming_func;
	#define EXT_csmd_calculatetiming_func  extern PFCSMD_CALCULATETIMING_FUNC_IEC pfcsmd_calculatetiming_func;
	#define GET_csmd_calculatetiming_func(fl)  s_pfCMGetAPI2( "csmd_calculatetiming_func", (RTS_VOID_FCTPTR *)&pfcsmd_calculatetiming_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x66F3AB88, 0x03050600)
	#define CAL_csmd_calculatetiming_func  pfcsmd_calculatetiming_func
	#define CHK_csmd_calculatetiming_func  (pfcsmd_calculatetiming_func != NULL)
	#define EXP_csmd_calculatetiming_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_calculatetiming_func", (RTS_UINTPTR)csmd_calculatetiming_func, 1, 0x66F3AB88, 0x03050600) 
#endif


/**
 * <description>csmd_checkint_func</description>
 */
typedef struct tagcsmd_checkint_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_DWORD *pulInt;				/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_CheckInt_Func;	/* VAR_OUTPUT */	
} csmd_checkint_func_struct;

void CDECL CDECL_EXT csmd_checkint_func(csmd_checkint_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_CHECKINT_FUNC_IEC) (csmd_checkint_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_CHECKINT_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_checkint_func
	#define EXT_csmd_checkint_func
	#define GET_csmd_checkint_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_checkint_func(p0) 
	#define CHK_csmd_checkint_func  FALSE
	#define EXP_csmd_checkint_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_checkint_func
	#define EXT_csmd_checkint_func
	#define GET_csmd_checkint_func(fl)  CAL_CMGETAPI( "csmd_checkint_func" ) 
	#define CAL_csmd_checkint_func  csmd_checkint_func
	#define CHK_csmd_checkint_func  TRUE
	#define EXP_csmd_checkint_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_checkint_func", (RTS_UINTPTR)csmd_checkint_func, 1, 0x37960093, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_checkint_func
	#define EXT_csmd_checkint_func
	#define GET_csmd_checkint_func(fl)  CAL_CMGETAPI( "csmd_checkint_func" ) 
	#define CAL_csmd_checkint_func  csmd_checkint_func
	#define CHK_csmd_checkint_func  TRUE
	#define EXP_csmd_checkint_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_checkint_func", (RTS_UINTPTR)csmd_checkint_func, 1, 0x37960093, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_checkint_func
	#define EXT_CmpSercos3Mastercsmd_checkint_func
	#define GET_CmpSercos3Mastercsmd_checkint_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_checkint_func  csmd_checkint_func
	#define CHK_CmpSercos3Mastercsmd_checkint_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_checkint_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_checkint_func", (RTS_UINTPTR)csmd_checkint_func, 1, 0x37960093, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_checkint_func
	#define EXT_csmd_checkint_func
	#define GET_csmd_checkint_func(fl)  CAL_CMGETAPI( "csmd_checkint_func" ) 
	#define CAL_csmd_checkint_func  csmd_checkint_func
	#define CHK_csmd_checkint_func  TRUE
	#define EXP_csmd_checkint_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_checkint_func", (RTS_UINTPTR)csmd_checkint_func, 1, 0x37960093, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_checkint_func  PFCSMD_CHECKINT_FUNC_IEC pfcsmd_checkint_func;
	#define EXT_csmd_checkint_func  extern PFCSMD_CHECKINT_FUNC_IEC pfcsmd_checkint_func;
	#define GET_csmd_checkint_func(fl)  s_pfCMGetAPI2( "csmd_checkint_func", (RTS_VOID_FCTPTR *)&pfcsmd_checkint_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x37960093, 0x03050600)
	#define CAL_csmd_checkint_func  pfcsmd_checkint_func
	#define CHK_csmd_checkint_func  (pfcsmd_checkint_func != NULL)
	#define EXP_csmd_checkint_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_checkint_func", (RTS_UINTPTR)csmd_checkint_func, 1, 0x37960093, 0x03050600) 
#endif


/**
 * <description>csmd_checksvchbusy_func</description>
 */
typedef struct tagcsmd_checksvchbusy_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchData;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_CheckSVCHBusy_Func;	/* VAR_OUTPUT */	
} csmd_checksvchbusy_func_struct;

void CDECL CDECL_EXT csmd_checksvchbusy_func(csmd_checksvchbusy_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_CHECKSVCHBUSY_FUNC_IEC) (csmd_checksvchbusy_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_CHECKSVCHBUSY_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_checksvchbusy_func
	#define EXT_csmd_checksvchbusy_func
	#define GET_csmd_checksvchbusy_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_checksvchbusy_func(p0) 
	#define CHK_csmd_checksvchbusy_func  FALSE
	#define EXP_csmd_checksvchbusy_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_checksvchbusy_func
	#define EXT_csmd_checksvchbusy_func
	#define GET_csmd_checksvchbusy_func(fl)  CAL_CMGETAPI( "csmd_checksvchbusy_func" ) 
	#define CAL_csmd_checksvchbusy_func  csmd_checksvchbusy_func
	#define CHK_csmd_checksvchbusy_func  TRUE
	#define EXP_csmd_checksvchbusy_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_checksvchbusy_func", (RTS_UINTPTR)csmd_checksvchbusy_func, 1, 0xB3E14239, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_checksvchbusy_func
	#define EXT_csmd_checksvchbusy_func
	#define GET_csmd_checksvchbusy_func(fl)  CAL_CMGETAPI( "csmd_checksvchbusy_func" ) 
	#define CAL_csmd_checksvchbusy_func  csmd_checksvchbusy_func
	#define CHK_csmd_checksvchbusy_func  TRUE
	#define EXP_csmd_checksvchbusy_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_checksvchbusy_func", (RTS_UINTPTR)csmd_checksvchbusy_func, 1, 0xB3E14239, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_checksvchbusy_func
	#define EXT_CmpSercos3Mastercsmd_checksvchbusy_func
	#define GET_CmpSercos3Mastercsmd_checksvchbusy_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_checksvchbusy_func  csmd_checksvchbusy_func
	#define CHK_CmpSercos3Mastercsmd_checksvchbusy_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_checksvchbusy_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_checksvchbusy_func", (RTS_UINTPTR)csmd_checksvchbusy_func, 1, 0xB3E14239, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_checksvchbusy_func
	#define EXT_csmd_checksvchbusy_func
	#define GET_csmd_checksvchbusy_func(fl)  CAL_CMGETAPI( "csmd_checksvchbusy_func" ) 
	#define CAL_csmd_checksvchbusy_func  csmd_checksvchbusy_func
	#define CHK_csmd_checksvchbusy_func  TRUE
	#define EXP_csmd_checksvchbusy_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_checksvchbusy_func", (RTS_UINTPTR)csmd_checksvchbusy_func, 1, 0xB3E14239, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_checksvchbusy_func  PFCSMD_CHECKSVCHBUSY_FUNC_IEC pfcsmd_checksvchbusy_func;
	#define EXT_csmd_checksvchbusy_func  extern PFCSMD_CHECKSVCHBUSY_FUNC_IEC pfcsmd_checksvchbusy_func;
	#define GET_csmd_checksvchbusy_func(fl)  s_pfCMGetAPI2( "csmd_checksvchbusy_func", (RTS_VOID_FCTPTR *)&pfcsmd_checksvchbusy_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xB3E14239, 0x03050600)
	#define CAL_csmd_checksvchbusy_func  pfcsmd_checksvchbusy_func
	#define CHK_csmd_checksvchbusy_func  (pfcsmd_checksvchbusy_func != NULL)
	#define EXP_csmd_checksvchbusy_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_checksvchbusy_func", (RTS_UINTPTR)csmd_checksvchbusy_func, 1, 0xB3E14239, 0x03050600) 
#endif


/**
 * <description>csmd_checkversion_func</description>
 */
typedef struct tagcsmd_checkversion_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prFuncState;			/* VAR_INPUT */	
	RTS_IEC_BYTE *parSvcMacro;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_CheckVersion_Func;	/* VAR_OUTPUT */	
} csmd_checkversion_func_struct;

void CDECL CDECL_EXT csmd_checkversion_func(csmd_checkversion_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_CHECKVERSION_FUNC_IEC) (csmd_checkversion_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_CHECKVERSION_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_checkversion_func
	#define EXT_csmd_checkversion_func
	#define GET_csmd_checkversion_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_checkversion_func(p0) 
	#define CHK_csmd_checkversion_func  FALSE
	#define EXP_csmd_checkversion_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_checkversion_func
	#define EXT_csmd_checkversion_func
	#define GET_csmd_checkversion_func(fl)  CAL_CMGETAPI( "csmd_checkversion_func" ) 
	#define CAL_csmd_checkversion_func  csmd_checkversion_func
	#define CHK_csmd_checkversion_func  TRUE
	#define EXP_csmd_checkversion_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_checkversion_func", (RTS_UINTPTR)csmd_checkversion_func, 1, 0x761ECE64, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_checkversion_func
	#define EXT_csmd_checkversion_func
	#define GET_csmd_checkversion_func(fl)  CAL_CMGETAPI( "csmd_checkversion_func" ) 
	#define CAL_csmd_checkversion_func  csmd_checkversion_func
	#define CHK_csmd_checkversion_func  TRUE
	#define EXP_csmd_checkversion_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_checkversion_func", (RTS_UINTPTR)csmd_checkversion_func, 1, 0x761ECE64, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_checkversion_func
	#define EXT_CmpSercos3Mastercsmd_checkversion_func
	#define GET_CmpSercos3Mastercsmd_checkversion_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_checkversion_func  csmd_checkversion_func
	#define CHK_CmpSercos3Mastercsmd_checkversion_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_checkversion_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_checkversion_func", (RTS_UINTPTR)csmd_checkversion_func, 1, 0x761ECE64, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_checkversion_func
	#define EXT_csmd_checkversion_func
	#define GET_csmd_checkversion_func(fl)  CAL_CMGETAPI( "csmd_checkversion_func" ) 
	#define CAL_csmd_checkversion_func  csmd_checkversion_func
	#define CHK_csmd_checkversion_func  TRUE
	#define EXP_csmd_checkversion_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_checkversion_func", (RTS_UINTPTR)csmd_checkversion_func, 1, 0x761ECE64, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_checkversion_func  PFCSMD_CHECKVERSION_FUNC_IEC pfcsmd_checkversion_func;
	#define EXT_csmd_checkversion_func  extern PFCSMD_CHECKVERSION_FUNC_IEC pfcsmd_checkversion_func;
	#define GET_csmd_checkversion_func(fl)  s_pfCMGetAPI2( "csmd_checkversion_func", (RTS_VOID_FCTPTR *)&pfcsmd_checkversion_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x761ECE64, 0x03050600)
	#define CAL_csmd_checkversion_func  pfcsmd_checkversion_func
	#define CHK_csmd_checkversion_func  (pfcsmd_checkversion_func != NULL)
	#define EXP_csmd_checkversion_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_checkversion_func", (RTS_UINTPTR)csmd_checkversion_func, 1, 0x761ECE64, 0x03050600) 
#endif


/**
 * <description>csmd_clearcommand_func</description>
 */
typedef struct tagcsmd_clearcommand_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchData;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_ClearCommand_Func;	/* VAR_OUTPUT */	
} csmd_clearcommand_func_struct;

void CDECL CDECL_EXT csmd_clearcommand_func(csmd_clearcommand_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_CLEARCOMMAND_FUNC_IEC) (csmd_clearcommand_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_CLEARCOMMAND_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_clearcommand_func
	#define EXT_csmd_clearcommand_func
	#define GET_csmd_clearcommand_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_clearcommand_func(p0) 
	#define CHK_csmd_clearcommand_func  FALSE
	#define EXP_csmd_clearcommand_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_clearcommand_func
	#define EXT_csmd_clearcommand_func
	#define GET_csmd_clearcommand_func(fl)  CAL_CMGETAPI( "csmd_clearcommand_func" ) 
	#define CAL_csmd_clearcommand_func  csmd_clearcommand_func
	#define CHK_csmd_clearcommand_func  TRUE
	#define EXP_csmd_clearcommand_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_clearcommand_func", (RTS_UINTPTR)csmd_clearcommand_func, 1, 0xCFB8C080, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_clearcommand_func
	#define EXT_csmd_clearcommand_func
	#define GET_csmd_clearcommand_func(fl)  CAL_CMGETAPI( "csmd_clearcommand_func" ) 
	#define CAL_csmd_clearcommand_func  csmd_clearcommand_func
	#define CHK_csmd_clearcommand_func  TRUE
	#define EXP_csmd_clearcommand_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_clearcommand_func", (RTS_UINTPTR)csmd_clearcommand_func, 1, 0xCFB8C080, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_clearcommand_func
	#define EXT_CmpSercos3Mastercsmd_clearcommand_func
	#define GET_CmpSercos3Mastercsmd_clearcommand_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_clearcommand_func  csmd_clearcommand_func
	#define CHK_CmpSercos3Mastercsmd_clearcommand_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_clearcommand_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_clearcommand_func", (RTS_UINTPTR)csmd_clearcommand_func, 1, 0xCFB8C080, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_clearcommand_func
	#define EXT_csmd_clearcommand_func
	#define GET_csmd_clearcommand_func(fl)  CAL_CMGETAPI( "csmd_clearcommand_func" ) 
	#define CAL_csmd_clearcommand_func  csmd_clearcommand_func
	#define CHK_csmd_clearcommand_func  TRUE
	#define EXP_csmd_clearcommand_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_clearcommand_func", (RTS_UINTPTR)csmd_clearcommand_func, 1, 0xCFB8C080, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_clearcommand_func  PFCSMD_CLEARCOMMAND_FUNC_IEC pfcsmd_clearcommand_func;
	#define EXT_csmd_clearcommand_func  extern PFCSMD_CLEARCOMMAND_FUNC_IEC pfcsmd_clearcommand_func;
	#define GET_csmd_clearcommand_func(fl)  s_pfCMGetAPI2( "csmd_clearcommand_func", (RTS_VOID_FCTPTR *)&pfcsmd_clearcommand_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xCFB8C080, 0x03050600)
	#define CAL_csmd_clearcommand_func  pfcsmd_clearcommand_func
	#define CHK_csmd_clearcommand_func  (pfcsmd_clearcommand_func != NULL)
	#define EXP_csmd_clearcommand_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_clearcommand_func", (RTS_UINTPTR)csmd_clearcommand_func, 1, 0xCFB8C080, 0x03050600) 
#endif


/**
 * <description>csmd_clearint_func</description>
 */
typedef struct tagcsmd_clearint_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_DWORD ulIntClearMask;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_ClearInt_Func;	/* VAR_OUTPUT */	
} csmd_clearint_func_struct;

void CDECL CDECL_EXT csmd_clearint_func(csmd_clearint_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_CLEARINT_FUNC_IEC) (csmd_clearint_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_CLEARINT_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_clearint_func
	#define EXT_csmd_clearint_func
	#define GET_csmd_clearint_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_clearint_func(p0) 
	#define CHK_csmd_clearint_func  FALSE
	#define EXP_csmd_clearint_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_clearint_func
	#define EXT_csmd_clearint_func
	#define GET_csmd_clearint_func(fl)  CAL_CMGETAPI( "csmd_clearint_func" ) 
	#define CAL_csmd_clearint_func  csmd_clearint_func
	#define CHK_csmd_clearint_func  TRUE
	#define EXP_csmd_clearint_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_clearint_func", (RTS_UINTPTR)csmd_clearint_func, 1, 0xCBAF09F0, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_clearint_func
	#define EXT_csmd_clearint_func
	#define GET_csmd_clearint_func(fl)  CAL_CMGETAPI( "csmd_clearint_func" ) 
	#define CAL_csmd_clearint_func  csmd_clearint_func
	#define CHK_csmd_clearint_func  TRUE
	#define EXP_csmd_clearint_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_clearint_func", (RTS_UINTPTR)csmd_clearint_func, 1, 0xCBAF09F0, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_clearint_func
	#define EXT_CmpSercos3Mastercsmd_clearint_func
	#define GET_CmpSercos3Mastercsmd_clearint_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_clearint_func  csmd_clearint_func
	#define CHK_CmpSercos3Mastercsmd_clearint_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_clearint_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_clearint_func", (RTS_UINTPTR)csmd_clearint_func, 1, 0xCBAF09F0, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_clearint_func
	#define EXT_csmd_clearint_func
	#define GET_csmd_clearint_func(fl)  CAL_CMGETAPI( "csmd_clearint_func" ) 
	#define CAL_csmd_clearint_func  csmd_clearint_func
	#define CHK_csmd_clearint_func  TRUE
	#define EXP_csmd_clearint_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_clearint_func", (RTS_UINTPTR)csmd_clearint_func, 1, 0xCBAF09F0, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_clearint_func  PFCSMD_CLEARINT_FUNC_IEC pfcsmd_clearint_func;
	#define EXT_csmd_clearint_func  extern PFCSMD_CLEARINT_FUNC_IEC pfcsmd_clearint_func;
	#define GET_csmd_clearint_func(fl)  s_pfCMGetAPI2( "csmd_clearint_func", (RTS_VOID_FCTPTR *)&pfcsmd_clearint_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xCBAF09F0, 0x03050600)
	#define CAL_csmd_clearint_func  pfcsmd_clearint_func
	#define CHK_csmd_clearint_func  (pfcsmd_clearint_func != NULL)
	#define EXP_csmd_clearint_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_clearint_func", (RTS_UINTPTR)csmd_clearint_func, 1, 0xCBAF09F0, 0x03050600) 
#endif


/**
 * <description>csmd_enable_cycclk_input_func</description>
 */
typedef struct tagcsmd_enable_cycclk_input_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BOOL bEnable;				/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_Enable_CYCCLK_Input_Func;	/* VAR_OUTPUT */	
} csmd_enable_cycclk_input_func_struct;

void CDECL CDECL_EXT csmd_enable_cycclk_input_func(csmd_enable_cycclk_input_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_ENABLE_CYCCLK_INPUT_FUNC_IEC) (csmd_enable_cycclk_input_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_ENABLE_CYCCLK_INPUT_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_enable_cycclk_input_func
	#define EXT_csmd_enable_cycclk_input_func
	#define GET_csmd_enable_cycclk_input_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_enable_cycclk_input_func(p0) 
	#define CHK_csmd_enable_cycclk_input_func  FALSE
	#define EXP_csmd_enable_cycclk_input_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_enable_cycclk_input_func
	#define EXT_csmd_enable_cycclk_input_func
	#define GET_csmd_enable_cycclk_input_func(fl)  CAL_CMGETAPI( "csmd_enable_cycclk_input_func" ) 
	#define CAL_csmd_enable_cycclk_input_func  csmd_enable_cycclk_input_func
	#define CHK_csmd_enable_cycclk_input_func  TRUE
	#define EXP_csmd_enable_cycclk_input_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_enable_cycclk_input_func", (RTS_UINTPTR)csmd_enable_cycclk_input_func, 1, 0x845313A4, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_enable_cycclk_input_func
	#define EXT_csmd_enable_cycclk_input_func
	#define GET_csmd_enable_cycclk_input_func(fl)  CAL_CMGETAPI( "csmd_enable_cycclk_input_func" ) 
	#define CAL_csmd_enable_cycclk_input_func  csmd_enable_cycclk_input_func
	#define CHK_csmd_enable_cycclk_input_func  TRUE
	#define EXP_csmd_enable_cycclk_input_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_enable_cycclk_input_func", (RTS_UINTPTR)csmd_enable_cycclk_input_func, 1, 0x845313A4, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_enable_cycclk_input_func
	#define EXT_CmpSercos3Mastercsmd_enable_cycclk_input_func
	#define GET_CmpSercos3Mastercsmd_enable_cycclk_input_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_enable_cycclk_input_func  csmd_enable_cycclk_input_func
	#define CHK_CmpSercos3Mastercsmd_enable_cycclk_input_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_enable_cycclk_input_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_enable_cycclk_input_func", (RTS_UINTPTR)csmd_enable_cycclk_input_func, 1, 0x845313A4, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_enable_cycclk_input_func
	#define EXT_csmd_enable_cycclk_input_func
	#define GET_csmd_enable_cycclk_input_func(fl)  CAL_CMGETAPI( "csmd_enable_cycclk_input_func" ) 
	#define CAL_csmd_enable_cycclk_input_func  csmd_enable_cycclk_input_func
	#define CHK_csmd_enable_cycclk_input_func  TRUE
	#define EXP_csmd_enable_cycclk_input_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_enable_cycclk_input_func", (RTS_UINTPTR)csmd_enable_cycclk_input_func, 1, 0x845313A4, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_enable_cycclk_input_func  PFCSMD_ENABLE_CYCCLK_INPUT_FUNC_IEC pfcsmd_enable_cycclk_input_func;
	#define EXT_csmd_enable_cycclk_input_func  extern PFCSMD_ENABLE_CYCCLK_INPUT_FUNC_IEC pfcsmd_enable_cycclk_input_func;
	#define GET_csmd_enable_cycclk_input_func(fl)  s_pfCMGetAPI2( "csmd_enable_cycclk_input_func", (RTS_VOID_FCTPTR *)&pfcsmd_enable_cycclk_input_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x845313A4, 0x03050600)
	#define CAL_csmd_enable_cycclk_input_func  pfcsmd_enable_cycclk_input_func
	#define CHK_csmd_enable_cycclk_input_func  (pfcsmd_enable_cycclk_input_func != NULL)
	#define EXP_csmd_enable_cycclk_input_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_enable_cycclk_input_func", (RTS_UINTPTR)csmd_enable_cycclk_input_func, 1, 0x845313A4, 0x03050600) 
#endif


/**
 * <description>csmd_eventcontrol_func</description>
 */
typedef struct tagcsmd_eventcontrol_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_WORD wEventID;				/* VAR_INPUT */	
	RTS_IEC_BOOL bActivate;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwEvent_TCNT_Value;	/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_EventControl_Func;	/* VAR_OUTPUT */	
} csmd_eventcontrol_func_struct;

void CDECL CDECL_EXT csmd_eventcontrol_func(csmd_eventcontrol_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_EVENTCONTROL_FUNC_IEC) (csmd_eventcontrol_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_EVENTCONTROL_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_eventcontrol_func
	#define EXT_csmd_eventcontrol_func
	#define GET_csmd_eventcontrol_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_eventcontrol_func(p0) 
	#define CHK_csmd_eventcontrol_func  FALSE
	#define EXP_csmd_eventcontrol_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_eventcontrol_func
	#define EXT_csmd_eventcontrol_func
	#define GET_csmd_eventcontrol_func(fl)  CAL_CMGETAPI( "csmd_eventcontrol_func" ) 
	#define CAL_csmd_eventcontrol_func  csmd_eventcontrol_func
	#define CHK_csmd_eventcontrol_func  TRUE
	#define EXP_csmd_eventcontrol_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_eventcontrol_func", (RTS_UINTPTR)csmd_eventcontrol_func, 1, 0xA88254A8, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_eventcontrol_func
	#define EXT_csmd_eventcontrol_func
	#define GET_csmd_eventcontrol_func(fl)  CAL_CMGETAPI( "csmd_eventcontrol_func" ) 
	#define CAL_csmd_eventcontrol_func  csmd_eventcontrol_func
	#define CHK_csmd_eventcontrol_func  TRUE
	#define EXP_csmd_eventcontrol_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_eventcontrol_func", (RTS_UINTPTR)csmd_eventcontrol_func, 1, 0xA88254A8, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_eventcontrol_func
	#define EXT_CmpSercos3Mastercsmd_eventcontrol_func
	#define GET_CmpSercos3Mastercsmd_eventcontrol_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_eventcontrol_func  csmd_eventcontrol_func
	#define CHK_CmpSercos3Mastercsmd_eventcontrol_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_eventcontrol_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_eventcontrol_func", (RTS_UINTPTR)csmd_eventcontrol_func, 1, 0xA88254A8, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_eventcontrol_func
	#define EXT_csmd_eventcontrol_func
	#define GET_csmd_eventcontrol_func(fl)  CAL_CMGETAPI( "csmd_eventcontrol_func" ) 
	#define CAL_csmd_eventcontrol_func  csmd_eventcontrol_func
	#define CHK_csmd_eventcontrol_func  TRUE
	#define EXP_csmd_eventcontrol_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_eventcontrol_func", (RTS_UINTPTR)csmd_eventcontrol_func, 1, 0xA88254A8, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_eventcontrol_func  PFCSMD_EVENTCONTROL_FUNC_IEC pfcsmd_eventcontrol_func;
	#define EXT_csmd_eventcontrol_func  extern PFCSMD_EVENTCONTROL_FUNC_IEC pfcsmd_eventcontrol_func;
	#define GET_csmd_eventcontrol_func(fl)  s_pfCMGetAPI2( "csmd_eventcontrol_func", (RTS_VOID_FCTPTR *)&pfcsmd_eventcontrol_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xA88254A8, 0x03050600)
	#define CAL_csmd_eventcontrol_func  pfcsmd_eventcontrol_func
	#define CHK_csmd_eventcontrol_func  (pfcsmd_eventcontrol_func != NULL)
	#define EXP_csmd_eventcontrol_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_eventcontrol_func", (RTS_UINTPTR)csmd_eventcontrol_func, 1, 0xA88254A8, 0x03050600) 
#endif


/**
 * <description>csmd_getattribute_func</description>
 */
typedef struct tagcsmd_getattribute_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchMngmtData;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_GetAttribute_Func;	/* VAR_OUTPUT */	
} csmd_getattribute_func_struct;

void CDECL CDECL_EXT csmd_getattribute_func(csmd_getattribute_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_GETATTRIBUTE_FUNC_IEC) (csmd_getattribute_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_GETATTRIBUTE_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_getattribute_func
	#define EXT_csmd_getattribute_func
	#define GET_csmd_getattribute_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_getattribute_func(p0) 
	#define CHK_csmd_getattribute_func  FALSE
	#define EXP_csmd_getattribute_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_getattribute_func
	#define EXT_csmd_getattribute_func
	#define GET_csmd_getattribute_func(fl)  CAL_CMGETAPI( "csmd_getattribute_func" ) 
	#define CAL_csmd_getattribute_func  csmd_getattribute_func
	#define CHK_csmd_getattribute_func  TRUE
	#define EXP_csmd_getattribute_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getattribute_func", (RTS_UINTPTR)csmd_getattribute_func, 1, 0x0D98F820, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_getattribute_func
	#define EXT_csmd_getattribute_func
	#define GET_csmd_getattribute_func(fl)  CAL_CMGETAPI( "csmd_getattribute_func" ) 
	#define CAL_csmd_getattribute_func  csmd_getattribute_func
	#define CHK_csmd_getattribute_func  TRUE
	#define EXP_csmd_getattribute_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getattribute_func", (RTS_UINTPTR)csmd_getattribute_func, 1, 0x0D98F820, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_getattribute_func
	#define EXT_CmpSercos3Mastercsmd_getattribute_func
	#define GET_CmpSercos3Mastercsmd_getattribute_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_getattribute_func  csmd_getattribute_func
	#define CHK_CmpSercos3Mastercsmd_getattribute_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_getattribute_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getattribute_func", (RTS_UINTPTR)csmd_getattribute_func, 1, 0x0D98F820, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_getattribute_func
	#define EXT_csmd_getattribute_func
	#define GET_csmd_getattribute_func(fl)  CAL_CMGETAPI( "csmd_getattribute_func" ) 
	#define CAL_csmd_getattribute_func  csmd_getattribute_func
	#define CHK_csmd_getattribute_func  TRUE
	#define EXP_csmd_getattribute_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getattribute_func", (RTS_UINTPTR)csmd_getattribute_func, 1, 0x0D98F820, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_getattribute_func  PFCSMD_GETATTRIBUTE_FUNC_IEC pfcsmd_getattribute_func;
	#define EXT_csmd_getattribute_func  extern PFCSMD_GETATTRIBUTE_FUNC_IEC pfcsmd_getattribute_func;
	#define GET_csmd_getattribute_func(fl)  s_pfCMGetAPI2( "csmd_getattribute_func", (RTS_VOID_FCTPTR *)&pfcsmd_getattribute_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0D98F820, 0x03050600)
	#define CAL_csmd_getattribute_func  pfcsmd_getattribute_func
	#define CHK_csmd_getattribute_func  (pfcsmd_getattribute_func != NULL)
	#define EXP_csmd_getattribute_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getattribute_func", (RTS_UINTPTR)csmd_getattribute_func, 1, 0x0D98F820, 0x03050600) 
#endif


/**
 * <description>csmd_getdata_func</description>
 */
typedef struct tagcsmd_getdata_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchMngmtData;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_GetData_Func;	/* VAR_OUTPUT */	
} csmd_getdata_func_struct;

void CDECL CDECL_EXT csmd_getdata_func(csmd_getdata_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_GETDATA_FUNC_IEC) (csmd_getdata_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_GETDATA_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_getdata_func
	#define EXT_csmd_getdata_func
	#define GET_csmd_getdata_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_getdata_func(p0) 
	#define CHK_csmd_getdata_func  FALSE
	#define EXP_csmd_getdata_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_getdata_func
	#define EXT_csmd_getdata_func
	#define GET_csmd_getdata_func(fl)  CAL_CMGETAPI( "csmd_getdata_func" ) 
	#define CAL_csmd_getdata_func  csmd_getdata_func
	#define CHK_csmd_getdata_func  TRUE
	#define EXP_csmd_getdata_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getdata_func", (RTS_UINTPTR)csmd_getdata_func, 1, 0xAB0E8CF8, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_getdata_func
	#define EXT_csmd_getdata_func
	#define GET_csmd_getdata_func(fl)  CAL_CMGETAPI( "csmd_getdata_func" ) 
	#define CAL_csmd_getdata_func  csmd_getdata_func
	#define CHK_csmd_getdata_func  TRUE
	#define EXP_csmd_getdata_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getdata_func", (RTS_UINTPTR)csmd_getdata_func, 1, 0xAB0E8CF8, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_getdata_func
	#define EXT_CmpSercos3Mastercsmd_getdata_func
	#define GET_CmpSercos3Mastercsmd_getdata_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_getdata_func  csmd_getdata_func
	#define CHK_CmpSercos3Mastercsmd_getdata_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_getdata_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getdata_func", (RTS_UINTPTR)csmd_getdata_func, 1, 0xAB0E8CF8, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_getdata_func
	#define EXT_csmd_getdata_func
	#define GET_csmd_getdata_func(fl)  CAL_CMGETAPI( "csmd_getdata_func" ) 
	#define CAL_csmd_getdata_func  csmd_getdata_func
	#define CHK_csmd_getdata_func  TRUE
	#define EXP_csmd_getdata_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getdata_func", (RTS_UINTPTR)csmd_getdata_func, 1, 0xAB0E8CF8, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_getdata_func  PFCSMD_GETDATA_FUNC_IEC pfcsmd_getdata_func;
	#define EXT_csmd_getdata_func  extern PFCSMD_GETDATA_FUNC_IEC pfcsmd_getdata_func;
	#define GET_csmd_getdata_func(fl)  s_pfCMGetAPI2( "csmd_getdata_func", (RTS_VOID_FCTPTR *)&pfcsmd_getdata_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xAB0E8CF8, 0x03050600)
	#define CAL_csmd_getdata_func  pfcsmd_getdata_func
	#define CHK_csmd_getdata_func  (pfcsmd_getdata_func != NULL)
	#define EXP_csmd_getdata_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getdata_func", (RTS_UINTPTR)csmd_getdata_func, 1, 0xAB0E8CF8, 0x03050600) 
#endif


/**
 * <description>csmd_getdatastatus_func</description>
 */
typedef struct tagcsmd_getdatastatus_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchMngmtData;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_GetDataStatus_Func;	/* VAR_OUTPUT */	
} csmd_getdatastatus_func_struct;

void CDECL CDECL_EXT csmd_getdatastatus_func(csmd_getdatastatus_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_GETDATASTATUS_FUNC_IEC) (csmd_getdatastatus_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_GETDATASTATUS_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_getdatastatus_func
	#define EXT_csmd_getdatastatus_func
	#define GET_csmd_getdatastatus_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_getdatastatus_func(p0) 
	#define CHK_csmd_getdatastatus_func  FALSE
	#define EXP_csmd_getdatastatus_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_getdatastatus_func
	#define EXT_csmd_getdatastatus_func
	#define GET_csmd_getdatastatus_func(fl)  CAL_CMGETAPI( "csmd_getdatastatus_func" ) 
	#define CAL_csmd_getdatastatus_func  csmd_getdatastatus_func
	#define CHK_csmd_getdatastatus_func  TRUE
	#define EXP_csmd_getdatastatus_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getdatastatus_func", (RTS_UINTPTR)csmd_getdatastatus_func, 1, 0x345C3E5B, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_getdatastatus_func
	#define EXT_csmd_getdatastatus_func
	#define GET_csmd_getdatastatus_func(fl)  CAL_CMGETAPI( "csmd_getdatastatus_func" ) 
	#define CAL_csmd_getdatastatus_func  csmd_getdatastatus_func
	#define CHK_csmd_getdatastatus_func  TRUE
	#define EXP_csmd_getdatastatus_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getdatastatus_func", (RTS_UINTPTR)csmd_getdatastatus_func, 1, 0x345C3E5B, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_getdatastatus_func
	#define EXT_CmpSercos3Mastercsmd_getdatastatus_func
	#define GET_CmpSercos3Mastercsmd_getdatastatus_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_getdatastatus_func  csmd_getdatastatus_func
	#define CHK_CmpSercos3Mastercsmd_getdatastatus_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_getdatastatus_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getdatastatus_func", (RTS_UINTPTR)csmd_getdatastatus_func, 1, 0x345C3E5B, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_getdatastatus_func
	#define EXT_csmd_getdatastatus_func
	#define GET_csmd_getdatastatus_func(fl)  CAL_CMGETAPI( "csmd_getdatastatus_func" ) 
	#define CAL_csmd_getdatastatus_func  csmd_getdatastatus_func
	#define CHK_csmd_getdatastatus_func  TRUE
	#define EXP_csmd_getdatastatus_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getdatastatus_func", (RTS_UINTPTR)csmd_getdatastatus_func, 1, 0x345C3E5B, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_getdatastatus_func  PFCSMD_GETDATASTATUS_FUNC_IEC pfcsmd_getdatastatus_func;
	#define EXT_csmd_getdatastatus_func  extern PFCSMD_GETDATASTATUS_FUNC_IEC pfcsmd_getdatastatus_func;
	#define GET_csmd_getdatastatus_func(fl)  s_pfCMGetAPI2( "csmd_getdatastatus_func", (RTS_VOID_FCTPTR *)&pfcsmd_getdatastatus_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x345C3E5B, 0x03050600)
	#define CAL_csmd_getdatastatus_func  pfcsmd_getdatastatus_func
	#define CHK_csmd_getdatastatus_func  (pfcsmd_getdatastatus_func != NULL)
	#define EXP_csmd_getdatastatus_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getdatastatus_func", (RTS_UINTPTR)csmd_getdatastatus_func, 1, 0x345C3E5B, 0x03050600) 
#endif


/**
 * <description>csmd_getlistlength_func</description>
 */
typedef struct tagcsmd_getlistlength_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchMngmtData;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_GetListLength_Func;	/* VAR_OUTPUT */	
} csmd_getlistlength_func_struct;

void CDECL CDECL_EXT csmd_getlistlength_func(csmd_getlistlength_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_GETLISTLENGTH_FUNC_IEC) (csmd_getlistlength_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_GETLISTLENGTH_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_getlistlength_func
	#define EXT_csmd_getlistlength_func
	#define GET_csmd_getlistlength_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_getlistlength_func(p0) 
	#define CHK_csmd_getlistlength_func  FALSE
	#define EXP_csmd_getlistlength_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_getlistlength_func
	#define EXT_csmd_getlistlength_func
	#define GET_csmd_getlistlength_func(fl)  CAL_CMGETAPI( "csmd_getlistlength_func" ) 
	#define CAL_csmd_getlistlength_func  csmd_getlistlength_func
	#define CHK_csmd_getlistlength_func  TRUE
	#define EXP_csmd_getlistlength_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getlistlength_func", (RTS_UINTPTR)csmd_getlistlength_func, 1, 0xB561D934, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_getlistlength_func
	#define EXT_csmd_getlistlength_func
	#define GET_csmd_getlistlength_func(fl)  CAL_CMGETAPI( "csmd_getlistlength_func" ) 
	#define CAL_csmd_getlistlength_func  csmd_getlistlength_func
	#define CHK_csmd_getlistlength_func  TRUE
	#define EXP_csmd_getlistlength_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getlistlength_func", (RTS_UINTPTR)csmd_getlistlength_func, 1, 0xB561D934, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_getlistlength_func
	#define EXT_CmpSercos3Mastercsmd_getlistlength_func
	#define GET_CmpSercos3Mastercsmd_getlistlength_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_getlistlength_func  csmd_getlistlength_func
	#define CHK_CmpSercos3Mastercsmd_getlistlength_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_getlistlength_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getlistlength_func", (RTS_UINTPTR)csmd_getlistlength_func, 1, 0xB561D934, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_getlistlength_func
	#define EXT_csmd_getlistlength_func
	#define GET_csmd_getlistlength_func(fl)  CAL_CMGETAPI( "csmd_getlistlength_func" ) 
	#define CAL_csmd_getlistlength_func  csmd_getlistlength_func
	#define CHK_csmd_getlistlength_func  TRUE
	#define EXP_csmd_getlistlength_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getlistlength_func", (RTS_UINTPTR)csmd_getlistlength_func, 1, 0xB561D934, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_getlistlength_func  PFCSMD_GETLISTLENGTH_FUNC_IEC pfcsmd_getlistlength_func;
	#define EXT_csmd_getlistlength_func  extern PFCSMD_GETLISTLENGTH_FUNC_IEC pfcsmd_getlistlength_func;
	#define GET_csmd_getlistlength_func(fl)  s_pfCMGetAPI2( "csmd_getlistlength_func", (RTS_VOID_FCTPTR *)&pfcsmd_getlistlength_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xB561D934, 0x03050600)
	#define CAL_csmd_getlistlength_func  pfcsmd_getlistlength_func
	#define CHK_csmd_getlistlength_func  (pfcsmd_getlistlength_func != NULL)
	#define EXP_csmd_getlistlength_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getlistlength_func", (RTS_UINTPTR)csmd_getlistlength_func, 1, 0xB561D934, 0x03050600) 
#endif


/**
 * <description>csmd_getmax_func</description>
 */
typedef struct tagcsmd_getmax_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchMngmtData;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_GetMax_Func;		/* VAR_OUTPUT */	
} csmd_getmax_func_struct;

void CDECL CDECL_EXT csmd_getmax_func(csmd_getmax_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_GETMAX_FUNC_IEC) (csmd_getmax_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_GETMAX_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_getmax_func
	#define EXT_csmd_getmax_func
	#define GET_csmd_getmax_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_getmax_func(p0) 
	#define CHK_csmd_getmax_func  FALSE
	#define EXP_csmd_getmax_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_getmax_func
	#define EXT_csmd_getmax_func
	#define GET_csmd_getmax_func(fl)  CAL_CMGETAPI( "csmd_getmax_func" ) 
	#define CAL_csmd_getmax_func  csmd_getmax_func
	#define CHK_csmd_getmax_func  TRUE
	#define EXP_csmd_getmax_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getmax_func", (RTS_UINTPTR)csmd_getmax_func, 1, 0x19415CB4, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_getmax_func
	#define EXT_csmd_getmax_func
	#define GET_csmd_getmax_func(fl)  CAL_CMGETAPI( "csmd_getmax_func" ) 
	#define CAL_csmd_getmax_func  csmd_getmax_func
	#define CHK_csmd_getmax_func  TRUE
	#define EXP_csmd_getmax_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getmax_func", (RTS_UINTPTR)csmd_getmax_func, 1, 0x19415CB4, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_getmax_func
	#define EXT_CmpSercos3Mastercsmd_getmax_func
	#define GET_CmpSercos3Mastercsmd_getmax_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_getmax_func  csmd_getmax_func
	#define CHK_CmpSercos3Mastercsmd_getmax_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_getmax_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getmax_func", (RTS_UINTPTR)csmd_getmax_func, 1, 0x19415CB4, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_getmax_func
	#define EXT_csmd_getmax_func
	#define GET_csmd_getmax_func(fl)  CAL_CMGETAPI( "csmd_getmax_func" ) 
	#define CAL_csmd_getmax_func  csmd_getmax_func
	#define CHK_csmd_getmax_func  TRUE
	#define EXP_csmd_getmax_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getmax_func", (RTS_UINTPTR)csmd_getmax_func, 1, 0x19415CB4, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_getmax_func  PFCSMD_GETMAX_FUNC_IEC pfcsmd_getmax_func;
	#define EXT_csmd_getmax_func  extern PFCSMD_GETMAX_FUNC_IEC pfcsmd_getmax_func;
	#define GET_csmd_getmax_func(fl)  s_pfCMGetAPI2( "csmd_getmax_func", (RTS_VOID_FCTPTR *)&pfcsmd_getmax_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x19415CB4, 0x03050600)
	#define CAL_csmd_getmax_func  pfcsmd_getmax_func
	#define CHK_csmd_getmax_func  (pfcsmd_getmax_func != NULL)
	#define EXP_csmd_getmax_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getmax_func", (RTS_UINTPTR)csmd_getmax_func, 1, 0x19415CB4, 0x03050600) 
#endif


/**
 * <description>csmd_getmin_func</description>
 */
typedef struct tagcsmd_getmin_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchMngmtData;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_GetMin_Func;		/* VAR_OUTPUT */	
} csmd_getmin_func_struct;

void CDECL CDECL_EXT csmd_getmin_func(csmd_getmin_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_GETMIN_FUNC_IEC) (csmd_getmin_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_GETMIN_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_getmin_func
	#define EXT_csmd_getmin_func
	#define GET_csmd_getmin_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_getmin_func(p0) 
	#define CHK_csmd_getmin_func  FALSE
	#define EXP_csmd_getmin_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_getmin_func
	#define EXT_csmd_getmin_func
	#define GET_csmd_getmin_func(fl)  CAL_CMGETAPI( "csmd_getmin_func" ) 
	#define CAL_csmd_getmin_func  csmd_getmin_func
	#define CHK_csmd_getmin_func  TRUE
	#define EXP_csmd_getmin_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getmin_func", (RTS_UINTPTR)csmd_getmin_func, 1, 0xFA45F9C2, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_getmin_func
	#define EXT_csmd_getmin_func
	#define GET_csmd_getmin_func(fl)  CAL_CMGETAPI( "csmd_getmin_func" ) 
	#define CAL_csmd_getmin_func  csmd_getmin_func
	#define CHK_csmd_getmin_func  TRUE
	#define EXP_csmd_getmin_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getmin_func", (RTS_UINTPTR)csmd_getmin_func, 1, 0xFA45F9C2, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_getmin_func
	#define EXT_CmpSercos3Mastercsmd_getmin_func
	#define GET_CmpSercos3Mastercsmd_getmin_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_getmin_func  csmd_getmin_func
	#define CHK_CmpSercos3Mastercsmd_getmin_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_getmin_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getmin_func", (RTS_UINTPTR)csmd_getmin_func, 1, 0xFA45F9C2, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_getmin_func
	#define EXT_csmd_getmin_func
	#define GET_csmd_getmin_func(fl)  CAL_CMGETAPI( "csmd_getmin_func" ) 
	#define CAL_csmd_getmin_func  csmd_getmin_func
	#define CHK_csmd_getmin_func  TRUE
	#define EXP_csmd_getmin_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getmin_func", (RTS_UINTPTR)csmd_getmin_func, 1, 0xFA45F9C2, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_getmin_func  PFCSMD_GETMIN_FUNC_IEC pfcsmd_getmin_func;
	#define EXT_csmd_getmin_func  extern PFCSMD_GETMIN_FUNC_IEC pfcsmd_getmin_func;
	#define GET_csmd_getmin_func(fl)  s_pfCMGetAPI2( "csmd_getmin_func", (RTS_VOID_FCTPTR *)&pfcsmd_getmin_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xFA45F9C2, 0x03050600)
	#define CAL_csmd_getmin_func  pfcsmd_getmin_func
	#define CHK_csmd_getmin_func  (pfcsmd_getmin_func != NULL)
	#define EXP_csmd_getmin_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getmin_func", (RTS_UINTPTR)csmd_getmin_func, 1, 0xFA45F9C2, 0x03050600) 
#endif


/**
 * <description>csmd_getname_func</description>
 */
typedef struct tagcsmd_getname_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchMngmtData;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_GetName_Func;	/* VAR_OUTPUT */	
} csmd_getname_func_struct;

void CDECL CDECL_EXT csmd_getname_func(csmd_getname_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_GETNAME_FUNC_IEC) (csmd_getname_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_GETNAME_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_getname_func
	#define EXT_csmd_getname_func
	#define GET_csmd_getname_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_getname_func(p0) 
	#define CHK_csmd_getname_func  FALSE
	#define EXP_csmd_getname_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_getname_func
	#define EXT_csmd_getname_func
	#define GET_csmd_getname_func(fl)  CAL_CMGETAPI( "csmd_getname_func" ) 
	#define CAL_csmd_getname_func  csmd_getname_func
	#define CHK_csmd_getname_func  TRUE
	#define EXP_csmd_getname_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getname_func", (RTS_UINTPTR)csmd_getname_func, 1, 0x76A643D5, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_getname_func
	#define EXT_csmd_getname_func
	#define GET_csmd_getname_func(fl)  CAL_CMGETAPI( "csmd_getname_func" ) 
	#define CAL_csmd_getname_func  csmd_getname_func
	#define CHK_csmd_getname_func  TRUE
	#define EXP_csmd_getname_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getname_func", (RTS_UINTPTR)csmd_getname_func, 1, 0x76A643D5, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_getname_func
	#define EXT_CmpSercos3Mastercsmd_getname_func
	#define GET_CmpSercos3Mastercsmd_getname_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_getname_func  csmd_getname_func
	#define CHK_CmpSercos3Mastercsmd_getname_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_getname_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getname_func", (RTS_UINTPTR)csmd_getname_func, 1, 0x76A643D5, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_getname_func
	#define EXT_csmd_getname_func
	#define GET_csmd_getname_func(fl)  CAL_CMGETAPI( "csmd_getname_func" ) 
	#define CAL_csmd_getname_func  csmd_getname_func
	#define CHK_csmd_getname_func  TRUE
	#define EXP_csmd_getname_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getname_func", (RTS_UINTPTR)csmd_getname_func, 1, 0x76A643D5, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_getname_func  PFCSMD_GETNAME_FUNC_IEC pfcsmd_getname_func;
	#define EXT_csmd_getname_func  extern PFCSMD_GETNAME_FUNC_IEC pfcsmd_getname_func;
	#define GET_csmd_getname_func(fl)  s_pfCMGetAPI2( "csmd_getname_func", (RTS_VOID_FCTPTR *)&pfcsmd_getname_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x76A643D5, 0x03050600)
	#define CAL_csmd_getname_func  pfcsmd_getname_func
	#define CHK_csmd_getname_func  (pfcsmd_getname_func != NULL)
	#define EXP_csmd_getname_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getname_func", (RTS_UINTPTR)csmd_getname_func, 1, 0x76A643D5, 0x03050600) 
#endif


/**
 * <description>csmd_getphase_func</description>
 */
typedef struct tagcsmd_getphase_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_WORD *pwPhase;				/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_GetPhase_Func;	/* VAR_OUTPUT */	
} csmd_getphase_func_struct;

void CDECL CDECL_EXT csmd_getphase_func(csmd_getphase_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_GETPHASE_FUNC_IEC) (csmd_getphase_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_GETPHASE_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_getphase_func
	#define EXT_csmd_getphase_func
	#define GET_csmd_getphase_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_getphase_func(p0) 
	#define CHK_csmd_getphase_func  FALSE
	#define EXP_csmd_getphase_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_getphase_func
	#define EXT_csmd_getphase_func
	#define GET_csmd_getphase_func(fl)  CAL_CMGETAPI( "csmd_getphase_func" ) 
	#define CAL_csmd_getphase_func  csmd_getphase_func
	#define CHK_csmd_getphase_func  TRUE
	#define EXP_csmd_getphase_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getphase_func", (RTS_UINTPTR)csmd_getphase_func, 1, 0x37A96B4E, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_getphase_func
	#define EXT_csmd_getphase_func
	#define GET_csmd_getphase_func(fl)  CAL_CMGETAPI( "csmd_getphase_func" ) 
	#define CAL_csmd_getphase_func  csmd_getphase_func
	#define CHK_csmd_getphase_func  TRUE
	#define EXP_csmd_getphase_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getphase_func", (RTS_UINTPTR)csmd_getphase_func, 1, 0x37A96B4E, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_getphase_func
	#define EXT_CmpSercos3Mastercsmd_getphase_func
	#define GET_CmpSercos3Mastercsmd_getphase_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_getphase_func  csmd_getphase_func
	#define CHK_CmpSercos3Mastercsmd_getphase_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_getphase_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getphase_func", (RTS_UINTPTR)csmd_getphase_func, 1, 0x37A96B4E, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_getphase_func
	#define EXT_csmd_getphase_func
	#define GET_csmd_getphase_func(fl)  CAL_CMGETAPI( "csmd_getphase_func" ) 
	#define CAL_csmd_getphase_func  csmd_getphase_func
	#define CHK_csmd_getphase_func  TRUE
	#define EXP_csmd_getphase_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getphase_func", (RTS_UINTPTR)csmd_getphase_func, 1, 0x37A96B4E, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_getphase_func  PFCSMD_GETPHASE_FUNC_IEC pfcsmd_getphase_func;
	#define EXT_csmd_getphase_func  extern PFCSMD_GETPHASE_FUNC_IEC pfcsmd_getphase_func;
	#define GET_csmd_getphase_func(fl)  s_pfCMGetAPI2( "csmd_getphase_func", (RTS_VOID_FCTPTR *)&pfcsmd_getphase_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x37A96B4E, 0x03050600)
	#define CAL_csmd_getphase_func  pfcsmd_getphase_func
	#define CHK_csmd_getphase_func  (pfcsmd_getphase_func != NULL)
	#define EXP_csmd_getphase_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getphase_func", (RTS_UINTPTR)csmd_getphase_func, 1, 0x37A96B4E, 0x03050600) 
#endif


/**
 * <description>csmd_gettimingdata_func</description>
 */
typedef struct tagcsmd_gettimingdata_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prFuncState;			/* VAR_INPUT */	
	RTS_IEC_BYTE *parSvcMacro;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_GetTimingData_Func;	/* VAR_OUTPUT */	
} csmd_gettimingdata_func_struct;

void CDECL CDECL_EXT csmd_gettimingdata_func(csmd_gettimingdata_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_GETTIMINGDATA_FUNC_IEC) (csmd_gettimingdata_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_GETTIMINGDATA_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_gettimingdata_func
	#define EXT_csmd_gettimingdata_func
	#define GET_csmd_gettimingdata_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_gettimingdata_func(p0) 
	#define CHK_csmd_gettimingdata_func  FALSE
	#define EXP_csmd_gettimingdata_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_gettimingdata_func
	#define EXT_csmd_gettimingdata_func
	#define GET_csmd_gettimingdata_func(fl)  CAL_CMGETAPI( "csmd_gettimingdata_func" ) 
	#define CAL_csmd_gettimingdata_func  csmd_gettimingdata_func
	#define CHK_csmd_gettimingdata_func  TRUE
	#define EXP_csmd_gettimingdata_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_gettimingdata_func", (RTS_UINTPTR)csmd_gettimingdata_func, 1, 0x9C4DBC7F, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_gettimingdata_func
	#define EXT_csmd_gettimingdata_func
	#define GET_csmd_gettimingdata_func(fl)  CAL_CMGETAPI( "csmd_gettimingdata_func" ) 
	#define CAL_csmd_gettimingdata_func  csmd_gettimingdata_func
	#define CHK_csmd_gettimingdata_func  TRUE
	#define EXP_csmd_gettimingdata_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_gettimingdata_func", (RTS_UINTPTR)csmd_gettimingdata_func, 1, 0x9C4DBC7F, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_gettimingdata_func
	#define EXT_CmpSercos3Mastercsmd_gettimingdata_func
	#define GET_CmpSercos3Mastercsmd_gettimingdata_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_gettimingdata_func  csmd_gettimingdata_func
	#define CHK_CmpSercos3Mastercsmd_gettimingdata_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_gettimingdata_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_gettimingdata_func", (RTS_UINTPTR)csmd_gettimingdata_func, 1, 0x9C4DBC7F, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_gettimingdata_func
	#define EXT_csmd_gettimingdata_func
	#define GET_csmd_gettimingdata_func(fl)  CAL_CMGETAPI( "csmd_gettimingdata_func" ) 
	#define CAL_csmd_gettimingdata_func  csmd_gettimingdata_func
	#define CHK_csmd_gettimingdata_func  TRUE
	#define EXP_csmd_gettimingdata_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_gettimingdata_func", (RTS_UINTPTR)csmd_gettimingdata_func, 1, 0x9C4DBC7F, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_gettimingdata_func  PFCSMD_GETTIMINGDATA_FUNC_IEC pfcsmd_gettimingdata_func;
	#define EXT_csmd_gettimingdata_func  extern PFCSMD_GETTIMINGDATA_FUNC_IEC pfcsmd_gettimingdata_func;
	#define GET_csmd_gettimingdata_func(fl)  s_pfCMGetAPI2( "csmd_gettimingdata_func", (RTS_VOID_FCTPTR *)&pfcsmd_gettimingdata_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x9C4DBC7F, 0x03050600)
	#define CAL_csmd_gettimingdata_func  pfcsmd_gettimingdata_func
	#define CHK_csmd_gettimingdata_func  (pfcsmd_gettimingdata_func != NULL)
	#define EXP_csmd_gettimingdata_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_gettimingdata_func", (RTS_UINTPTR)csmd_gettimingdata_func, 1, 0x9C4DBC7F, 0x03050600) 
#endif


/**
 * <description>csmd_gettopology_func</description>
 */
typedef struct tagcsmd_gettopology_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prFuncState;			/* VAR_INPUT */	
	RTS_IEC_WORD wTopology;				/* VAR_INPUT */	
	RTS_IEC_BYTE *parSvcMacro;			/* VAR_INPUT */	
	RTS_IEC_WORD *pwDev_P1;				/* VAR_INPUT */	
	RTS_IEC_WORD *pwDev_P2;				/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_GetTopology_Func;	/* VAR_OUTPUT */	
} csmd_gettopology_func_struct;

void CDECL CDECL_EXT csmd_gettopology_func(csmd_gettopology_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_GETTOPOLOGY_FUNC_IEC) (csmd_gettopology_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_GETTOPOLOGY_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_gettopology_func
	#define EXT_csmd_gettopology_func
	#define GET_csmd_gettopology_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_gettopology_func(p0) 
	#define CHK_csmd_gettopology_func  FALSE
	#define EXP_csmd_gettopology_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_gettopology_func
	#define EXT_csmd_gettopology_func
	#define GET_csmd_gettopology_func(fl)  CAL_CMGETAPI( "csmd_gettopology_func" ) 
	#define CAL_csmd_gettopology_func  csmd_gettopology_func
	#define CHK_csmd_gettopology_func  TRUE
	#define EXP_csmd_gettopology_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_gettopology_func", (RTS_UINTPTR)csmd_gettopology_func, 1, 0xCC7ABCD2, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_gettopology_func
	#define EXT_csmd_gettopology_func
	#define GET_csmd_gettopology_func(fl)  CAL_CMGETAPI( "csmd_gettopology_func" ) 
	#define CAL_csmd_gettopology_func  csmd_gettopology_func
	#define CHK_csmd_gettopology_func  TRUE
	#define EXP_csmd_gettopology_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_gettopology_func", (RTS_UINTPTR)csmd_gettopology_func, 1, 0xCC7ABCD2, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_gettopology_func
	#define EXT_CmpSercos3Mastercsmd_gettopology_func
	#define GET_CmpSercos3Mastercsmd_gettopology_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_gettopology_func  csmd_gettopology_func
	#define CHK_CmpSercos3Mastercsmd_gettopology_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_gettopology_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_gettopology_func", (RTS_UINTPTR)csmd_gettopology_func, 1, 0xCC7ABCD2, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_gettopology_func
	#define EXT_csmd_gettopology_func
	#define GET_csmd_gettopology_func(fl)  CAL_CMGETAPI( "csmd_gettopology_func" ) 
	#define CAL_csmd_gettopology_func  csmd_gettopology_func
	#define CHK_csmd_gettopology_func  TRUE
	#define EXP_csmd_gettopology_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_gettopology_func", (RTS_UINTPTR)csmd_gettopology_func, 1, 0xCC7ABCD2, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_gettopology_func  PFCSMD_GETTOPOLOGY_FUNC_IEC pfcsmd_gettopology_func;
	#define EXT_csmd_gettopology_func  extern PFCSMD_GETTOPOLOGY_FUNC_IEC pfcsmd_gettopology_func;
	#define GET_csmd_gettopology_func(fl)  s_pfCMGetAPI2( "csmd_gettopology_func", (RTS_VOID_FCTPTR *)&pfcsmd_gettopology_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xCC7ABCD2, 0x03050600)
	#define CAL_csmd_gettopology_func  pfcsmd_gettopology_func
	#define CHK_csmd_gettopology_func  (pfcsmd_gettopology_func != NULL)
	#define EXP_csmd_gettopology_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_gettopology_func", (RTS_UINTPTR)csmd_gettopology_func, 1, 0xCC7ABCD2, 0x03050600) 
#endif


/**
 * <description>csmd_getunit_func</description>
 */
typedef struct tagcsmd_getunit_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchMngmtData;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_GetUnit_Func;	/* VAR_OUTPUT */	
} csmd_getunit_func_struct;

void CDECL CDECL_EXT csmd_getunit_func(csmd_getunit_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_GETUNIT_FUNC_IEC) (csmd_getunit_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_GETUNIT_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_getunit_func
	#define EXT_csmd_getunit_func
	#define GET_csmd_getunit_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_getunit_func(p0) 
	#define CHK_csmd_getunit_func  FALSE
	#define EXP_csmd_getunit_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_getunit_func
	#define EXT_csmd_getunit_func
	#define GET_csmd_getunit_func(fl)  CAL_CMGETAPI( "csmd_getunit_func" ) 
	#define CAL_csmd_getunit_func  csmd_getunit_func
	#define CHK_csmd_getunit_func  TRUE
	#define EXP_csmd_getunit_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getunit_func", (RTS_UINTPTR)csmd_getunit_func, 1, 0x70BD674C, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_getunit_func
	#define EXT_csmd_getunit_func
	#define GET_csmd_getunit_func(fl)  CAL_CMGETAPI( "csmd_getunit_func" ) 
	#define CAL_csmd_getunit_func  csmd_getunit_func
	#define CHK_csmd_getunit_func  TRUE
	#define EXP_csmd_getunit_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getunit_func", (RTS_UINTPTR)csmd_getunit_func, 1, 0x70BD674C, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_getunit_func
	#define EXT_CmpSercos3Mastercsmd_getunit_func
	#define GET_CmpSercos3Mastercsmd_getunit_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_getunit_func  csmd_getunit_func
	#define CHK_CmpSercos3Mastercsmd_getunit_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_getunit_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getunit_func", (RTS_UINTPTR)csmd_getunit_func, 1, 0x70BD674C, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_getunit_func
	#define EXT_csmd_getunit_func
	#define GET_csmd_getunit_func(fl)  CAL_CMGETAPI( "csmd_getunit_func" ) 
	#define CAL_csmd_getunit_func  csmd_getunit_func
	#define CHK_csmd_getunit_func  TRUE
	#define EXP_csmd_getunit_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getunit_func", (RTS_UINTPTR)csmd_getunit_func, 1, 0x70BD674C, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_getunit_func  PFCSMD_GETUNIT_FUNC_IEC pfcsmd_getunit_func;
	#define EXT_csmd_getunit_func  extern PFCSMD_GETUNIT_FUNC_IEC pfcsmd_getunit_func;
	#define GET_csmd_getunit_func(fl)  s_pfCMGetAPI2( "csmd_getunit_func", (RTS_VOID_FCTPTR *)&pfcsmd_getunit_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x70BD674C, 0x03050600)
	#define CAL_csmd_getunit_func  pfcsmd_getunit_func
	#define CHK_csmd_getunit_func  (pfcsmd_getunit_func != NULL)
	#define EXP_csmd_getunit_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_getunit_func", (RTS_UINTPTR)csmd_getunit_func, 1, 0x70BD674C, 0x03050600) 
#endif


/**
 * <description>csmd_identifyslave_func</description>
 */
typedef struct tagcsmd_identifyslave_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_WORD wDevIdx;				/* VAR_INPUT */	
	RTS_IEC_BYTE bActivated;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_IdentifySlave_Func;	/* VAR_OUTPUT */	
} csmd_identifyslave_func_struct;

void CDECL CDECL_EXT csmd_identifyslave_func(csmd_identifyslave_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_IDENTIFYSLAVE_FUNC_IEC) (csmd_identifyslave_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_IDENTIFYSLAVE_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_identifyslave_func
	#define EXT_csmd_identifyslave_func
	#define GET_csmd_identifyslave_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_identifyslave_func(p0) 
	#define CHK_csmd_identifyslave_func  FALSE
	#define EXP_csmd_identifyslave_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_identifyslave_func
	#define EXT_csmd_identifyslave_func
	#define GET_csmd_identifyslave_func(fl)  CAL_CMGETAPI( "csmd_identifyslave_func" ) 
	#define CAL_csmd_identifyslave_func  csmd_identifyslave_func
	#define CHK_csmd_identifyslave_func  TRUE
	#define EXP_csmd_identifyslave_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_identifyslave_func", (RTS_UINTPTR)csmd_identifyslave_func, 1, 0x97737054, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_identifyslave_func
	#define EXT_csmd_identifyslave_func
	#define GET_csmd_identifyslave_func(fl)  CAL_CMGETAPI( "csmd_identifyslave_func" ) 
	#define CAL_csmd_identifyslave_func  csmd_identifyslave_func
	#define CHK_csmd_identifyslave_func  TRUE
	#define EXP_csmd_identifyslave_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_identifyslave_func", (RTS_UINTPTR)csmd_identifyslave_func, 1, 0x97737054, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_identifyslave_func
	#define EXT_CmpSercos3Mastercsmd_identifyslave_func
	#define GET_CmpSercos3Mastercsmd_identifyslave_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_identifyslave_func  csmd_identifyslave_func
	#define CHK_CmpSercos3Mastercsmd_identifyslave_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_identifyslave_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_identifyslave_func", (RTS_UINTPTR)csmd_identifyslave_func, 1, 0x97737054, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_identifyslave_func
	#define EXT_csmd_identifyslave_func
	#define GET_csmd_identifyslave_func(fl)  CAL_CMGETAPI( "csmd_identifyslave_func" ) 
	#define CAL_csmd_identifyslave_func  csmd_identifyslave_func
	#define CHK_csmd_identifyslave_func  TRUE
	#define EXP_csmd_identifyslave_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_identifyslave_func", (RTS_UINTPTR)csmd_identifyslave_func, 1, 0x97737054, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_identifyslave_func  PFCSMD_IDENTIFYSLAVE_FUNC_IEC pfcsmd_identifyslave_func;
	#define EXT_csmd_identifyslave_func  extern PFCSMD_IDENTIFYSLAVE_FUNC_IEC pfcsmd_identifyslave_func;
	#define GET_csmd_identifyslave_func(fl)  s_pfCMGetAPI2( "csmd_identifyslave_func", (RTS_VOID_FCTPTR *)&pfcsmd_identifyslave_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x97737054, 0x03050600)
	#define CAL_csmd_identifyslave_func  pfcsmd_identifyslave_func
	#define CHK_csmd_identifyslave_func  (pfcsmd_identifyslave_func != NULL)
	#define EXP_csmd_identifyslave_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_identifyslave_func", (RTS_UINTPTR)csmd_identifyslave_func, 1, 0x97737054, 0x03050600) 
#endif


/**
 * <description>csmd_inithardware_func</description>
 */
typedef struct tagcsmd_inithardware_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prFuncState;			/* VAR_INPUT */	
	RTS_IEC_BYTE *prHW_Init_Struct;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_InitHardware_Func;	/* VAR_OUTPUT */	
} csmd_inithardware_func_struct;

void CDECL CDECL_EXT csmd_inithardware_func(csmd_inithardware_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_INITHARDWARE_FUNC_IEC) (csmd_inithardware_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_INITHARDWARE_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_inithardware_func
	#define EXT_csmd_inithardware_func
	#define GET_csmd_inithardware_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_inithardware_func(p0) 
	#define CHK_csmd_inithardware_func  FALSE
	#define EXP_csmd_inithardware_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_inithardware_func
	#define EXT_csmd_inithardware_func
	#define GET_csmd_inithardware_func(fl)  CAL_CMGETAPI( "csmd_inithardware_func" ) 
	#define CAL_csmd_inithardware_func  csmd_inithardware_func
	#define CHK_csmd_inithardware_func  TRUE
	#define EXP_csmd_inithardware_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_inithardware_func", (RTS_UINTPTR)csmd_inithardware_func, 1, 0x52A33D5D, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_inithardware_func
	#define EXT_csmd_inithardware_func
	#define GET_csmd_inithardware_func(fl)  CAL_CMGETAPI( "csmd_inithardware_func" ) 
	#define CAL_csmd_inithardware_func  csmd_inithardware_func
	#define CHK_csmd_inithardware_func  TRUE
	#define EXP_csmd_inithardware_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_inithardware_func", (RTS_UINTPTR)csmd_inithardware_func, 1, 0x52A33D5D, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_inithardware_func
	#define EXT_CmpSercos3Mastercsmd_inithardware_func
	#define GET_CmpSercos3Mastercsmd_inithardware_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_inithardware_func  csmd_inithardware_func
	#define CHK_CmpSercos3Mastercsmd_inithardware_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_inithardware_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_inithardware_func", (RTS_UINTPTR)csmd_inithardware_func, 1, 0x52A33D5D, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_inithardware_func
	#define EXT_csmd_inithardware_func
	#define GET_csmd_inithardware_func(fl)  CAL_CMGETAPI( "csmd_inithardware_func" ) 
	#define CAL_csmd_inithardware_func  csmd_inithardware_func
	#define CHK_csmd_inithardware_func  TRUE
	#define EXP_csmd_inithardware_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_inithardware_func", (RTS_UINTPTR)csmd_inithardware_func, 1, 0x52A33D5D, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_inithardware_func  PFCSMD_INITHARDWARE_FUNC_IEC pfcsmd_inithardware_func;
	#define EXT_csmd_inithardware_func  extern PFCSMD_INITHARDWARE_FUNC_IEC pfcsmd_inithardware_func;
	#define GET_csmd_inithardware_func(fl)  s_pfCMGetAPI2( "csmd_inithardware_func", (RTS_VOID_FCTPTR *)&pfcsmd_inithardware_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x52A33D5D, 0x03050600)
	#define CAL_csmd_inithardware_func  pfcsmd_inithardware_func
	#define CHK_csmd_inithardware_func  (pfcsmd_inithardware_func != NULL)
	#define EXP_csmd_inithardware_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_inithardware_func", (RTS_UINTPTR)csmd_inithardware_func, 1, 0x52A33D5D, 0x03050600) 
#endif


/**
 * <description>csmd_initialize_func</description>
 */
typedef struct tagcsmd_initialize_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_DWORD *prSERCOS_Register;	/* VAR_INPUT */	
	RTS_IEC_DWORD *prSERCOS_SVC_Ram;	/* VAR_INPUT */	
	RTS_IEC_DWORD *prSERCOS_TX_Ram;		/* VAR_INPUT */	
	RTS_IEC_DWORD *prSERCOS_RX_Ram;		/* VAR_INPUT */	
	RTS_IEC_DWORD *prSERCOS_IP_TX_Ram;	/* VAR_INPUT */	
	RTS_IEC_DWORD *prSERCOS_IP_RX_Ram;	/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_Initialize_Func;	/* VAR_OUTPUT */	
} csmd_initialize_func_struct;

void CDECL CDECL_EXT csmd_initialize_func(csmd_initialize_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_INITIALIZE_FUNC_IEC) (csmd_initialize_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_INITIALIZE_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_initialize_func
	#define EXT_csmd_initialize_func
	#define GET_csmd_initialize_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_initialize_func(p0) 
	#define CHK_csmd_initialize_func  FALSE
	#define EXP_csmd_initialize_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_initialize_func
	#define EXT_csmd_initialize_func
	#define GET_csmd_initialize_func(fl)  CAL_CMGETAPI( "csmd_initialize_func" ) 
	#define CAL_csmd_initialize_func  csmd_initialize_func
	#define CHK_csmd_initialize_func  TRUE
	#define EXP_csmd_initialize_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_initialize_func", (RTS_UINTPTR)csmd_initialize_func, 1, 0xA5BC5EA3, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_initialize_func
	#define EXT_csmd_initialize_func
	#define GET_csmd_initialize_func(fl)  CAL_CMGETAPI( "csmd_initialize_func" ) 
	#define CAL_csmd_initialize_func  csmd_initialize_func
	#define CHK_csmd_initialize_func  TRUE
	#define EXP_csmd_initialize_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_initialize_func", (RTS_UINTPTR)csmd_initialize_func, 1, 0xA5BC5EA3, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_initialize_func
	#define EXT_CmpSercos3Mastercsmd_initialize_func
	#define GET_CmpSercos3Mastercsmd_initialize_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_initialize_func  csmd_initialize_func
	#define CHK_CmpSercos3Mastercsmd_initialize_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_initialize_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_initialize_func", (RTS_UINTPTR)csmd_initialize_func, 1, 0xA5BC5EA3, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_initialize_func
	#define EXT_csmd_initialize_func
	#define GET_csmd_initialize_func(fl)  CAL_CMGETAPI( "csmd_initialize_func" ) 
	#define CAL_csmd_initialize_func  csmd_initialize_func
	#define CHK_csmd_initialize_func  TRUE
	#define EXP_csmd_initialize_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_initialize_func", (RTS_UINTPTR)csmd_initialize_func, 1, 0xA5BC5EA3, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_initialize_func  PFCSMD_INITIALIZE_FUNC_IEC pfcsmd_initialize_func;
	#define EXT_csmd_initialize_func  extern PFCSMD_INITIALIZE_FUNC_IEC pfcsmd_initialize_func;
	#define GET_csmd_initialize_func(fl)  s_pfCMGetAPI2( "csmd_initialize_func", (RTS_VOID_FCTPTR *)&pfcsmd_initialize_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xA5BC5EA3, 0x03050600)
	#define CAL_csmd_initialize_func  pfcsmd_initialize_func
	#define CHK_csmd_initialize_func  (pfcsmd_initialize_func != NULL)
	#define EXP_csmd_initialize_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_initialize_func", (RTS_UINTPTR)csmd_initialize_func, 1, 0xA5BC5EA3, 0x03050600) 
#endif


/**
 * <description>csmd_intcontrol_func</description>
 */
typedef struct tagcsmd_intcontrol_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_DWORD dwIntEnable;			/* VAR_INPUT */	
	RTS_IEC_DWORD dwIntOutputMask;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_IntControl_Func;	/* VAR_OUTPUT */	
} csmd_intcontrol_func_struct;

void CDECL CDECL_EXT csmd_intcontrol_func(csmd_intcontrol_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_INTCONTROL_FUNC_IEC) (csmd_intcontrol_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_INTCONTROL_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_intcontrol_func
	#define EXT_csmd_intcontrol_func
	#define GET_csmd_intcontrol_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_intcontrol_func(p0) 
	#define CHK_csmd_intcontrol_func  FALSE
	#define EXP_csmd_intcontrol_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_intcontrol_func
	#define EXT_csmd_intcontrol_func
	#define GET_csmd_intcontrol_func(fl)  CAL_CMGETAPI( "csmd_intcontrol_func" ) 
	#define CAL_csmd_intcontrol_func  csmd_intcontrol_func
	#define CHK_csmd_intcontrol_func  TRUE
	#define EXP_csmd_intcontrol_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_intcontrol_func", (RTS_UINTPTR)csmd_intcontrol_func, 1, 0x0B2DB2CF, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_intcontrol_func
	#define EXT_csmd_intcontrol_func
	#define GET_csmd_intcontrol_func(fl)  CAL_CMGETAPI( "csmd_intcontrol_func" ) 
	#define CAL_csmd_intcontrol_func  csmd_intcontrol_func
	#define CHK_csmd_intcontrol_func  TRUE
	#define EXP_csmd_intcontrol_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_intcontrol_func", (RTS_UINTPTR)csmd_intcontrol_func, 1, 0x0B2DB2CF, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_intcontrol_func
	#define EXT_CmpSercos3Mastercsmd_intcontrol_func
	#define GET_CmpSercos3Mastercsmd_intcontrol_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_intcontrol_func  csmd_intcontrol_func
	#define CHK_CmpSercos3Mastercsmd_intcontrol_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_intcontrol_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_intcontrol_func", (RTS_UINTPTR)csmd_intcontrol_func, 1, 0x0B2DB2CF, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_intcontrol_func
	#define EXT_csmd_intcontrol_func
	#define GET_csmd_intcontrol_func(fl)  CAL_CMGETAPI( "csmd_intcontrol_func" ) 
	#define CAL_csmd_intcontrol_func  csmd_intcontrol_func
	#define CHK_csmd_intcontrol_func  TRUE
	#define EXP_csmd_intcontrol_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_intcontrol_func", (RTS_UINTPTR)csmd_intcontrol_func, 1, 0x0B2DB2CF, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_intcontrol_func  PFCSMD_INTCONTROL_FUNC_IEC pfcsmd_intcontrol_func;
	#define EXT_csmd_intcontrol_func  extern PFCSMD_INTCONTROL_FUNC_IEC pfcsmd_intcontrol_func;
	#define GET_csmd_intcontrol_func(fl)  s_pfCMGetAPI2( "csmd_intcontrol_func", (RTS_VOID_FCTPTR *)&pfcsmd_intcontrol_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0B2DB2CF, 0x03050600)
	#define CAL_csmd_intcontrol_func  pfcsmd_intcontrol_func
	#define CHK_csmd_intcontrol_func  (pfcsmd_intcontrol_func != NULL)
	#define EXP_csmd_intcontrol_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_intcontrol_func", (RTS_UINTPTR)csmd_intcontrol_func, 1, 0x0B2DB2CF, 0x03050600) 
#endif


/**
 * <description>csmd_openidn_func</description>
 */
typedef struct tagcsmd_openidn_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchMngmtData;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_OpenIDN_Func;	/* VAR_OUTPUT */	
} csmd_openidn_func_struct;

void CDECL CDECL_EXT csmd_openidn_func(csmd_openidn_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_OPENIDN_FUNC_IEC) (csmd_openidn_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_OPENIDN_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_openidn_func
	#define EXT_csmd_openidn_func
	#define GET_csmd_openidn_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_openidn_func(p0) 
	#define CHK_csmd_openidn_func  FALSE
	#define EXP_csmd_openidn_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_openidn_func
	#define EXT_csmd_openidn_func
	#define GET_csmd_openidn_func(fl)  CAL_CMGETAPI( "csmd_openidn_func" ) 
	#define CAL_csmd_openidn_func  csmd_openidn_func
	#define CHK_csmd_openidn_func  TRUE
	#define EXP_csmd_openidn_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_openidn_func", (RTS_UINTPTR)csmd_openidn_func, 1, 0x71DDA747, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_openidn_func
	#define EXT_csmd_openidn_func
	#define GET_csmd_openidn_func(fl)  CAL_CMGETAPI( "csmd_openidn_func" ) 
	#define CAL_csmd_openidn_func  csmd_openidn_func
	#define CHK_csmd_openidn_func  TRUE
	#define EXP_csmd_openidn_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_openidn_func", (RTS_UINTPTR)csmd_openidn_func, 1, 0x71DDA747, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_openidn_func
	#define EXT_CmpSercos3Mastercsmd_openidn_func
	#define GET_CmpSercos3Mastercsmd_openidn_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_openidn_func  csmd_openidn_func
	#define CHK_CmpSercos3Mastercsmd_openidn_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_openidn_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_openidn_func", (RTS_UINTPTR)csmd_openidn_func, 1, 0x71DDA747, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_openidn_func
	#define EXT_csmd_openidn_func
	#define GET_csmd_openidn_func(fl)  CAL_CMGETAPI( "csmd_openidn_func" ) 
	#define CAL_csmd_openidn_func  csmd_openidn_func
	#define CHK_csmd_openidn_func  TRUE
	#define EXP_csmd_openidn_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_openidn_func", (RTS_UINTPTR)csmd_openidn_func, 1, 0x71DDA747, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_openidn_func  PFCSMD_OPENIDN_FUNC_IEC pfcsmd_openidn_func;
	#define EXT_csmd_openidn_func  extern PFCSMD_OPENIDN_FUNC_IEC pfcsmd_openidn_func;
	#define GET_csmd_openidn_func(fl)  s_pfCMGetAPI2( "csmd_openidn_func", (RTS_VOID_FCTPTR *)&pfcsmd_openidn_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x71DDA747, 0x03050600)
	#define CAL_csmd_openidn_func  pfcsmd_openidn_func
	#define CHK_csmd_openidn_func  (pfcsmd_openidn_func != NULL)
	#define EXP_csmd_openidn_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_openidn_func", (RTS_UINTPTR)csmd_openidn_func, 1, 0x71DDA747, 0x03050600) 
#endif


/**
 * <description>csmd_preparecycclk_func</description>
 */
typedef struct tagcsmd_preparecycclk_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BOOL bActivate;				/* VAR_INPUT */	
	RTS_IEC_BOOL bEnableInput;			/* VAR_INPUT */	
	RTS_IEC_BOOL bPolarity;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwStartDelay;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_PrepareCYCCLK_Func;	/* VAR_OUTPUT */	
} csmd_preparecycclk_func_struct;

void CDECL CDECL_EXT csmd_preparecycclk_func(csmd_preparecycclk_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_PREPARECYCCLK_FUNC_IEC) (csmd_preparecycclk_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_PREPARECYCCLK_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_preparecycclk_func
	#define EXT_csmd_preparecycclk_func
	#define GET_csmd_preparecycclk_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_preparecycclk_func(p0) 
	#define CHK_csmd_preparecycclk_func  FALSE
	#define EXP_csmd_preparecycclk_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_preparecycclk_func
	#define EXT_csmd_preparecycclk_func
	#define GET_csmd_preparecycclk_func(fl)  CAL_CMGETAPI( "csmd_preparecycclk_func" ) 
	#define CAL_csmd_preparecycclk_func  csmd_preparecycclk_func
	#define CHK_csmd_preparecycclk_func  TRUE
	#define EXP_csmd_preparecycclk_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_preparecycclk_func", (RTS_UINTPTR)csmd_preparecycclk_func, 1, 0x4B021723, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_preparecycclk_func
	#define EXT_csmd_preparecycclk_func
	#define GET_csmd_preparecycclk_func(fl)  CAL_CMGETAPI( "csmd_preparecycclk_func" ) 
	#define CAL_csmd_preparecycclk_func  csmd_preparecycclk_func
	#define CHK_csmd_preparecycclk_func  TRUE
	#define EXP_csmd_preparecycclk_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_preparecycclk_func", (RTS_UINTPTR)csmd_preparecycclk_func, 1, 0x4B021723, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_preparecycclk_func
	#define EXT_CmpSercos3Mastercsmd_preparecycclk_func
	#define GET_CmpSercos3Mastercsmd_preparecycclk_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_preparecycclk_func  csmd_preparecycclk_func
	#define CHK_CmpSercos3Mastercsmd_preparecycclk_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_preparecycclk_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_preparecycclk_func", (RTS_UINTPTR)csmd_preparecycclk_func, 1, 0x4B021723, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_preparecycclk_func
	#define EXT_csmd_preparecycclk_func
	#define GET_csmd_preparecycclk_func(fl)  CAL_CMGETAPI( "csmd_preparecycclk_func" ) 
	#define CAL_csmd_preparecycclk_func  csmd_preparecycclk_func
	#define CHK_csmd_preparecycclk_func  TRUE
	#define EXP_csmd_preparecycclk_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_preparecycclk_func", (RTS_UINTPTR)csmd_preparecycclk_func, 1, 0x4B021723, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_preparecycclk_func  PFCSMD_PREPARECYCCLK_FUNC_IEC pfcsmd_preparecycclk_func;
	#define EXT_csmd_preparecycclk_func  extern PFCSMD_PREPARECYCCLK_FUNC_IEC pfcsmd_preparecycclk_func;
	#define GET_csmd_preparecycclk_func(fl)  s_pfCMGetAPI2( "csmd_preparecycclk_func", (RTS_VOID_FCTPTR *)&pfcsmd_preparecycclk_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x4B021723, 0x03050600)
	#define CAL_csmd_preparecycclk_func  pfcsmd_preparecycclk_func
	#define CHK_csmd_preparecycclk_func  (pfcsmd_preparecycclk_func != NULL)
	#define EXP_csmd_preparecycclk_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_preparecycclk_func", (RTS_UINTPTR)csmd_preparecycclk_func, 1, 0x4B021723, 0x03050600) 
#endif


/**
 * <description>csmd_putdata_func</description>
 */
typedef struct tagcsmd_putdata_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchMngmtData;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_PutData_Func;	/* VAR_OUTPUT */	
} csmd_putdata_func_struct;

void CDECL CDECL_EXT csmd_putdata_func(csmd_putdata_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_PUTDATA_FUNC_IEC) (csmd_putdata_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_PUTDATA_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_putdata_func
	#define EXT_csmd_putdata_func
	#define GET_csmd_putdata_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_putdata_func(p0) 
	#define CHK_csmd_putdata_func  FALSE
	#define EXP_csmd_putdata_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_putdata_func
	#define EXT_csmd_putdata_func
	#define GET_csmd_putdata_func(fl)  CAL_CMGETAPI( "csmd_putdata_func" ) 
	#define CAL_csmd_putdata_func  csmd_putdata_func
	#define CHK_csmd_putdata_func  TRUE
	#define EXP_csmd_putdata_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_putdata_func", (RTS_UINTPTR)csmd_putdata_func, 1, 0xB64BD3C0, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_putdata_func
	#define EXT_csmd_putdata_func
	#define GET_csmd_putdata_func(fl)  CAL_CMGETAPI( "csmd_putdata_func" ) 
	#define CAL_csmd_putdata_func  csmd_putdata_func
	#define CHK_csmd_putdata_func  TRUE
	#define EXP_csmd_putdata_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_putdata_func", (RTS_UINTPTR)csmd_putdata_func, 1, 0xB64BD3C0, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_putdata_func
	#define EXT_CmpSercos3Mastercsmd_putdata_func
	#define GET_CmpSercos3Mastercsmd_putdata_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_putdata_func  csmd_putdata_func
	#define CHK_CmpSercos3Mastercsmd_putdata_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_putdata_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_putdata_func", (RTS_UINTPTR)csmd_putdata_func, 1, 0xB64BD3C0, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_putdata_func
	#define EXT_csmd_putdata_func
	#define GET_csmd_putdata_func(fl)  CAL_CMGETAPI( "csmd_putdata_func" ) 
	#define CAL_csmd_putdata_func  csmd_putdata_func
	#define CHK_csmd_putdata_func  TRUE
	#define EXP_csmd_putdata_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_putdata_func", (RTS_UINTPTR)csmd_putdata_func, 1, 0xB64BD3C0, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_putdata_func  PFCSMD_PUTDATA_FUNC_IEC pfcsmd_putdata_func;
	#define EXT_csmd_putdata_func  extern PFCSMD_PUTDATA_FUNC_IEC pfcsmd_putdata_func;
	#define GET_csmd_putdata_func(fl)  s_pfCMGetAPI2( "csmd_putdata_func", (RTS_VOID_FCTPTR *)&pfcsmd_putdata_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xB64BD3C0, 0x03050600)
	#define CAL_csmd_putdata_func  pfcsmd_putdata_func
	#define CHK_csmd_putdata_func  (pfcsmd_putdata_func != NULL)
	#define EXP_csmd_putdata_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_putdata_func", (RTS_UINTPTR)csmd_putdata_func, 1, 0xB64BD3C0, 0x03050600) 
#endif


/**
 * <description>csmd_readat_func</description>
 */
typedef struct tagcsmd_readat_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prATDestination;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_ReadAT_Func;		/* VAR_OUTPUT */	
} csmd_readat_func_struct;

void CDECL CDECL_EXT csmd_readat_func(csmd_readat_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_READAT_FUNC_IEC) (csmd_readat_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_READAT_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_readat_func
	#define EXT_csmd_readat_func
	#define GET_csmd_readat_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_readat_func(p0) 
	#define CHK_csmd_readat_func  FALSE
	#define EXP_csmd_readat_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_readat_func
	#define EXT_csmd_readat_func
	#define GET_csmd_readat_func(fl)  CAL_CMGETAPI( "csmd_readat_func" ) 
	#define CAL_csmd_readat_func  csmd_readat_func
	#define CHK_csmd_readat_func  TRUE
	#define EXP_csmd_readat_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_readat_func", (RTS_UINTPTR)csmd_readat_func, 1, 0x929B64F4, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_readat_func
	#define EXT_csmd_readat_func
	#define GET_csmd_readat_func(fl)  CAL_CMGETAPI( "csmd_readat_func" ) 
	#define CAL_csmd_readat_func  csmd_readat_func
	#define CHK_csmd_readat_func  TRUE
	#define EXP_csmd_readat_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_readat_func", (RTS_UINTPTR)csmd_readat_func, 1, 0x929B64F4, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_readat_func
	#define EXT_CmpSercos3Mastercsmd_readat_func
	#define GET_CmpSercos3Mastercsmd_readat_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_readat_func  csmd_readat_func
	#define CHK_CmpSercos3Mastercsmd_readat_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_readat_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_readat_func", (RTS_UINTPTR)csmd_readat_func, 1, 0x929B64F4, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_readat_func
	#define EXT_csmd_readat_func
	#define GET_csmd_readat_func(fl)  CAL_CMGETAPI( "csmd_readat_func" ) 
	#define CAL_csmd_readat_func  csmd_readat_func
	#define CHK_csmd_readat_func  TRUE
	#define EXP_csmd_readat_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_readat_func", (RTS_UINTPTR)csmd_readat_func, 1, 0x929B64F4, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_readat_func  PFCSMD_READAT_FUNC_IEC pfcsmd_readat_func;
	#define EXT_csmd_readat_func  extern PFCSMD_READAT_FUNC_IEC pfcsmd_readat_func;
	#define GET_csmd_readat_func(fl)  s_pfCMGetAPI2( "csmd_readat_func", (RTS_VOID_FCTPTR *)&pfcsmd_readat_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x929B64F4, 0x03050600)
	#define CAL_csmd_readat_func  pfcsmd_readat_func
	#define CHK_csmd_readat_func  (pfcsmd_readat_func != NULL)
	#define EXP_csmd_readat_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_readat_func", (RTS_UINTPTR)csmd_readat_func, 1, 0x929B64F4, 0x03050600) 
#endif


/**
 * <description>csmd_readcmdstatus_func</description>
 */
typedef struct tagcsmd_readcmdstatus_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchData;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_ReadCmdStatus_Func;	/* VAR_OUTPUT */	
} csmd_readcmdstatus_func_struct;

void CDECL CDECL_EXT csmd_readcmdstatus_func(csmd_readcmdstatus_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_READCMDSTATUS_FUNC_IEC) (csmd_readcmdstatus_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_READCMDSTATUS_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_readcmdstatus_func
	#define EXT_csmd_readcmdstatus_func
	#define GET_csmd_readcmdstatus_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_readcmdstatus_func(p0) 
	#define CHK_csmd_readcmdstatus_func  FALSE
	#define EXP_csmd_readcmdstatus_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_readcmdstatus_func
	#define EXT_csmd_readcmdstatus_func
	#define GET_csmd_readcmdstatus_func(fl)  CAL_CMGETAPI( "csmd_readcmdstatus_func" ) 
	#define CAL_csmd_readcmdstatus_func  csmd_readcmdstatus_func
	#define CHK_csmd_readcmdstatus_func  TRUE
	#define EXP_csmd_readcmdstatus_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_readcmdstatus_func", (RTS_UINTPTR)csmd_readcmdstatus_func, 1, 0x3970DE22, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_readcmdstatus_func
	#define EXT_csmd_readcmdstatus_func
	#define GET_csmd_readcmdstatus_func(fl)  CAL_CMGETAPI( "csmd_readcmdstatus_func" ) 
	#define CAL_csmd_readcmdstatus_func  csmd_readcmdstatus_func
	#define CHK_csmd_readcmdstatus_func  TRUE
	#define EXP_csmd_readcmdstatus_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_readcmdstatus_func", (RTS_UINTPTR)csmd_readcmdstatus_func, 1, 0x3970DE22, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_readcmdstatus_func
	#define EXT_CmpSercos3Mastercsmd_readcmdstatus_func
	#define GET_CmpSercos3Mastercsmd_readcmdstatus_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_readcmdstatus_func  csmd_readcmdstatus_func
	#define CHK_CmpSercos3Mastercsmd_readcmdstatus_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_readcmdstatus_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_readcmdstatus_func", (RTS_UINTPTR)csmd_readcmdstatus_func, 1, 0x3970DE22, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_readcmdstatus_func
	#define EXT_csmd_readcmdstatus_func
	#define GET_csmd_readcmdstatus_func(fl)  CAL_CMGETAPI( "csmd_readcmdstatus_func" ) 
	#define CAL_csmd_readcmdstatus_func  csmd_readcmdstatus_func
	#define CHK_csmd_readcmdstatus_func  TRUE
	#define EXP_csmd_readcmdstatus_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_readcmdstatus_func", (RTS_UINTPTR)csmd_readcmdstatus_func, 1, 0x3970DE22, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_readcmdstatus_func  PFCSMD_READCMDSTATUS_FUNC_IEC pfcsmd_readcmdstatus_func;
	#define EXT_csmd_readcmdstatus_func  extern PFCSMD_READCMDSTATUS_FUNC_IEC pfcsmd_readcmdstatus_func;
	#define GET_csmd_readcmdstatus_func(fl)  s_pfCMGetAPI2( "csmd_readcmdstatus_func", (RTS_VOID_FCTPTR *)&pfcsmd_readcmdstatus_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x3970DE22, 0x03050600)
	#define CAL_csmd_readcmdstatus_func  pfcsmd_readcmdstatus_func
	#define CHK_csmd_readcmdstatus_func  (pfcsmd_readcmdstatus_func != NULL)
	#define EXP_csmd_readcmdstatus_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_readcmdstatus_func", (RTS_UINTPTR)csmd_readcmdstatus_func, 1, 0x3970DE22, 0x03050600) 
#endif


/**
 * <description>csmd_readsvch_func</description>
 */
typedef struct tagcsmd_readsvch_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchData;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_ReadSVCH_Func;	/* VAR_OUTPUT */	
} csmd_readsvch_func_struct;

void CDECL CDECL_EXT csmd_readsvch_func(csmd_readsvch_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_READSVCH_FUNC_IEC) (csmd_readsvch_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_READSVCH_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_readsvch_func
	#define EXT_csmd_readsvch_func
	#define GET_csmd_readsvch_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_readsvch_func(p0) 
	#define CHK_csmd_readsvch_func  FALSE
	#define EXP_csmd_readsvch_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_readsvch_func
	#define EXT_csmd_readsvch_func
	#define GET_csmd_readsvch_func(fl)  CAL_CMGETAPI( "csmd_readsvch_func" ) 
	#define CAL_csmd_readsvch_func  csmd_readsvch_func
	#define CHK_csmd_readsvch_func  TRUE
	#define EXP_csmd_readsvch_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_readsvch_func", (RTS_UINTPTR)csmd_readsvch_func, 1, 0x7DD3BEAC, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_readsvch_func
	#define EXT_csmd_readsvch_func
	#define GET_csmd_readsvch_func(fl)  CAL_CMGETAPI( "csmd_readsvch_func" ) 
	#define CAL_csmd_readsvch_func  csmd_readsvch_func
	#define CHK_csmd_readsvch_func  TRUE
	#define EXP_csmd_readsvch_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_readsvch_func", (RTS_UINTPTR)csmd_readsvch_func, 1, 0x7DD3BEAC, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_readsvch_func
	#define EXT_CmpSercos3Mastercsmd_readsvch_func
	#define GET_CmpSercos3Mastercsmd_readsvch_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_readsvch_func  csmd_readsvch_func
	#define CHK_CmpSercos3Mastercsmd_readsvch_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_readsvch_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_readsvch_func", (RTS_UINTPTR)csmd_readsvch_func, 1, 0x7DD3BEAC, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_readsvch_func
	#define EXT_csmd_readsvch_func
	#define GET_csmd_readsvch_func(fl)  CAL_CMGETAPI( "csmd_readsvch_func" ) 
	#define CAL_csmd_readsvch_func  csmd_readsvch_func
	#define CHK_csmd_readsvch_func  TRUE
	#define EXP_csmd_readsvch_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_readsvch_func", (RTS_UINTPTR)csmd_readsvch_func, 1, 0x7DD3BEAC, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_readsvch_func  PFCSMD_READSVCH_FUNC_IEC pfcsmd_readsvch_func;
	#define EXT_csmd_readsvch_func  extern PFCSMD_READSVCH_FUNC_IEC pfcsmd_readsvch_func;
	#define GET_csmd_readsvch_func(fl)  s_pfCMGetAPI2( "csmd_readsvch_func", (RTS_VOID_FCTPTR *)&pfcsmd_readsvch_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x7DD3BEAC, 0x03050600)
	#define CAL_csmd_readsvch_func  pfcsmd_readsvch_func
	#define CHK_csmd_readsvch_func  (pfcsmd_readsvch_func != NULL)
	#define EXP_csmd_readsvch_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_readsvch_func", (RTS_UINTPTR)csmd_readsvch_func, 1, 0x7DD3BEAC, 0x03050600) 
#endif


/**
 * <description>csmd_recoverringtopology_func</description>
 */
typedef struct tagcsmd_recoverringtopology_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prFuncState;			/* VAR_INPUT */	
	RTS_IEC_BYTE *parSvcMacro;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_RecoverRingTopology_Func;	/* VAR_OUTPUT */	
} csmd_recoverringtopology_func_struct;

void CDECL CDECL_EXT csmd_recoverringtopology_func(csmd_recoverringtopology_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_RECOVERRINGTOPOLOGY_FUNC_IEC) (csmd_recoverringtopology_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_RECOVERRINGTOPOLOGY_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_recoverringtopology_func
	#define EXT_csmd_recoverringtopology_func
	#define GET_csmd_recoverringtopology_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_recoverringtopology_func(p0) 
	#define CHK_csmd_recoverringtopology_func  FALSE
	#define EXP_csmd_recoverringtopology_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_recoverringtopology_func
	#define EXT_csmd_recoverringtopology_func
	#define GET_csmd_recoverringtopology_func(fl)  CAL_CMGETAPI( "csmd_recoverringtopology_func" ) 
	#define CAL_csmd_recoverringtopology_func  csmd_recoverringtopology_func
	#define CHK_csmd_recoverringtopology_func  TRUE
	#define EXP_csmd_recoverringtopology_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_recoverringtopology_func", (RTS_UINTPTR)csmd_recoverringtopology_func, 1, 0xFBAAF5C6, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_recoverringtopology_func
	#define EXT_csmd_recoverringtopology_func
	#define GET_csmd_recoverringtopology_func(fl)  CAL_CMGETAPI( "csmd_recoverringtopology_func" ) 
	#define CAL_csmd_recoverringtopology_func  csmd_recoverringtopology_func
	#define CHK_csmd_recoverringtopology_func  TRUE
	#define EXP_csmd_recoverringtopology_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_recoverringtopology_func", (RTS_UINTPTR)csmd_recoverringtopology_func, 1, 0xFBAAF5C6, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_recoverringtopology_func
	#define EXT_CmpSercos3Mastercsmd_recoverringtopology_func
	#define GET_CmpSercos3Mastercsmd_recoverringtopology_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_recoverringtopology_func  csmd_recoverringtopology_func
	#define CHK_CmpSercos3Mastercsmd_recoverringtopology_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_recoverringtopology_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_recoverringtopology_func", (RTS_UINTPTR)csmd_recoverringtopology_func, 1, 0xFBAAF5C6, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_recoverringtopology_func
	#define EXT_csmd_recoverringtopology_func
	#define GET_csmd_recoverringtopology_func(fl)  CAL_CMGETAPI( "csmd_recoverringtopology_func" ) 
	#define CAL_csmd_recoverringtopology_func  csmd_recoverringtopology_func
	#define CHK_csmd_recoverringtopology_func  TRUE
	#define EXP_csmd_recoverringtopology_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_recoverringtopology_func", (RTS_UINTPTR)csmd_recoverringtopology_func, 1, 0xFBAAF5C6, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_recoverringtopology_func  PFCSMD_RECOVERRINGTOPOLOGY_FUNC_IEC pfcsmd_recoverringtopology_func;
	#define EXT_csmd_recoverringtopology_func  extern PFCSMD_RECOVERRINGTOPOLOGY_FUNC_IEC pfcsmd_recoverringtopology_func;
	#define GET_csmd_recoverringtopology_func(fl)  s_pfCMGetAPI2( "csmd_recoverringtopology_func", (RTS_VOID_FCTPTR *)&pfcsmd_recoverringtopology_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xFBAAF5C6, 0x03050600)
	#define CAL_csmd_recoverringtopology_func  pfcsmd_recoverringtopology_func
	#define CHK_csmd_recoverringtopology_func  (pfcsmd_recoverringtopology_func != NULL)
	#define EXP_csmd_recoverringtopology_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_recoverringtopology_func", (RTS_UINTPTR)csmd_recoverringtopology_func, 1, 0xFBAAF5C6, 0x03050600) 
#endif


/**
 * <description>csmd_resethardware_func</description>
 */
typedef struct tagcsmd_resethardware_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_ResetHardware_Func;	/* VAR_OUTPUT */	
} csmd_resethardware_func_struct;

void CDECL CDECL_EXT csmd_resethardware_func(csmd_resethardware_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_RESETHARDWARE_FUNC_IEC) (csmd_resethardware_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_RESETHARDWARE_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_resethardware_func
	#define EXT_csmd_resethardware_func
	#define GET_csmd_resethardware_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_resethardware_func(p0) 
	#define CHK_csmd_resethardware_func  FALSE
	#define EXP_csmd_resethardware_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_resethardware_func
	#define EXT_csmd_resethardware_func
	#define GET_csmd_resethardware_func(fl)  CAL_CMGETAPI( "csmd_resethardware_func" ) 
	#define CAL_csmd_resethardware_func  csmd_resethardware_func
	#define CHK_csmd_resethardware_func  TRUE
	#define EXP_csmd_resethardware_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_resethardware_func", (RTS_UINTPTR)csmd_resethardware_func, 1, 0xE447FB79, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_resethardware_func
	#define EXT_csmd_resethardware_func
	#define GET_csmd_resethardware_func(fl)  CAL_CMGETAPI( "csmd_resethardware_func" ) 
	#define CAL_csmd_resethardware_func  csmd_resethardware_func
	#define CHK_csmd_resethardware_func  TRUE
	#define EXP_csmd_resethardware_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_resethardware_func", (RTS_UINTPTR)csmd_resethardware_func, 1, 0xE447FB79, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_resethardware_func
	#define EXT_CmpSercos3Mastercsmd_resethardware_func
	#define GET_CmpSercos3Mastercsmd_resethardware_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_resethardware_func  csmd_resethardware_func
	#define CHK_CmpSercos3Mastercsmd_resethardware_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_resethardware_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_resethardware_func", (RTS_UINTPTR)csmd_resethardware_func, 1, 0xE447FB79, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_resethardware_func
	#define EXT_csmd_resethardware_func
	#define GET_csmd_resethardware_func(fl)  CAL_CMGETAPI( "csmd_resethardware_func" ) 
	#define CAL_csmd_resethardware_func  csmd_resethardware_func
	#define CHK_csmd_resethardware_func  TRUE
	#define EXP_csmd_resethardware_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_resethardware_func", (RTS_UINTPTR)csmd_resethardware_func, 1, 0xE447FB79, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_resethardware_func  PFCSMD_RESETHARDWARE_FUNC_IEC pfcsmd_resethardware_func;
	#define EXT_csmd_resethardware_func  extern PFCSMD_RESETHARDWARE_FUNC_IEC pfcsmd_resethardware_func;
	#define GET_csmd_resethardware_func(fl)  s_pfCMGetAPI2( "csmd_resethardware_func", (RTS_VOID_FCTPTR *)&pfcsmd_resethardware_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xE447FB79, 0x03050600)
	#define CAL_csmd_resethardware_func  pfcsmd_resethardware_func
	#define CHK_csmd_resethardware_func  (pfcsmd_resethardware_func != NULL)
	#define EXP_csmd_resethardware_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_resethardware_func", (RTS_UINTPTR)csmd_resethardware_func, 1, 0xE447FB79, 0x03050600) 
#endif


/**
 * <description>csmd_resetsvch_func</description>
 */
typedef struct tagcsmd_resetsvch_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_WORD wDevIdx;				/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_ResetSVCH_Func;	/* VAR_OUTPUT */	
} csmd_resetsvch_func_struct;

void CDECL CDECL_EXT csmd_resetsvch_func(csmd_resetsvch_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_RESETSVCH_FUNC_IEC) (csmd_resetsvch_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_RESETSVCH_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_resetsvch_func
	#define EXT_csmd_resetsvch_func
	#define GET_csmd_resetsvch_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_resetsvch_func(p0) 
	#define CHK_csmd_resetsvch_func  FALSE
	#define EXP_csmd_resetsvch_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_resetsvch_func
	#define EXT_csmd_resetsvch_func
	#define GET_csmd_resetsvch_func(fl)  CAL_CMGETAPI( "csmd_resetsvch_func" ) 
	#define CAL_csmd_resetsvch_func  csmd_resetsvch_func
	#define CHK_csmd_resetsvch_func  TRUE
	#define EXP_csmd_resetsvch_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_resetsvch_func", (RTS_UINTPTR)csmd_resetsvch_func, 1, 0x75C61AB7, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_resetsvch_func
	#define EXT_csmd_resetsvch_func
	#define GET_csmd_resetsvch_func(fl)  CAL_CMGETAPI( "csmd_resetsvch_func" ) 
	#define CAL_csmd_resetsvch_func  csmd_resetsvch_func
	#define CHK_csmd_resetsvch_func  TRUE
	#define EXP_csmd_resetsvch_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_resetsvch_func", (RTS_UINTPTR)csmd_resetsvch_func, 1, 0x75C61AB7, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_resetsvch_func
	#define EXT_CmpSercos3Mastercsmd_resetsvch_func
	#define GET_CmpSercos3Mastercsmd_resetsvch_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_resetsvch_func  csmd_resetsvch_func
	#define CHK_CmpSercos3Mastercsmd_resetsvch_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_resetsvch_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_resetsvch_func", (RTS_UINTPTR)csmd_resetsvch_func, 1, 0x75C61AB7, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_resetsvch_func
	#define EXT_csmd_resetsvch_func
	#define GET_csmd_resetsvch_func(fl)  CAL_CMGETAPI( "csmd_resetsvch_func" ) 
	#define CAL_csmd_resetsvch_func  csmd_resetsvch_func
	#define CHK_csmd_resetsvch_func  TRUE
	#define EXP_csmd_resetsvch_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_resetsvch_func", (RTS_UINTPTR)csmd_resetsvch_func, 1, 0x75C61AB7, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_resetsvch_func  PFCSMD_RESETSVCH_FUNC_IEC pfcsmd_resetsvch_func;
	#define EXT_csmd_resetsvch_func  extern PFCSMD_RESETSVCH_FUNC_IEC pfcsmd_resetsvch_func;
	#define GET_csmd_resetsvch_func(fl)  s_pfCMGetAPI2( "csmd_resetsvch_func", (RTS_VOID_FCTPTR *)&pfcsmd_resetsvch_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x75C61AB7, 0x03050600)
	#define CAL_csmd_resetsvch_func  pfcsmd_resetsvch_func
	#define CHK_csmd_resetsvch_func  (pfcsmd_resetsvch_func != NULL)
	#define EXP_csmd_resetsvch_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_resetsvch_func", (RTS_UINTPTR)csmd_resetsvch_func, 1, 0x75C61AB7, 0x03050600) 
#endif


/**
 * <description>csmd_set_nrt_mode_func</description>
 */
typedef struct tagcsmd_set_nrt_mode_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prHW_Init_Struct;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_Set_NRT_Mode_Func;	/* VAR_OUTPUT */	
} csmd_set_nrt_mode_func_struct;

void CDECL CDECL_EXT csmd_set_nrt_mode_func(csmd_set_nrt_mode_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_SET_NRT_MODE_FUNC_IEC) (csmd_set_nrt_mode_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_SET_NRT_MODE_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_set_nrt_mode_func
	#define EXT_csmd_set_nrt_mode_func
	#define GET_csmd_set_nrt_mode_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_set_nrt_mode_func(p0) 
	#define CHK_csmd_set_nrt_mode_func  FALSE
	#define EXP_csmd_set_nrt_mode_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_set_nrt_mode_func
	#define EXT_csmd_set_nrt_mode_func
	#define GET_csmd_set_nrt_mode_func(fl)  CAL_CMGETAPI( "csmd_set_nrt_mode_func" ) 
	#define CAL_csmd_set_nrt_mode_func  csmd_set_nrt_mode_func
	#define CHK_csmd_set_nrt_mode_func  TRUE
	#define EXP_csmd_set_nrt_mode_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_set_nrt_mode_func", (RTS_UINTPTR)csmd_set_nrt_mode_func, 1, 0x31E74A3D, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_set_nrt_mode_func
	#define EXT_csmd_set_nrt_mode_func
	#define GET_csmd_set_nrt_mode_func(fl)  CAL_CMGETAPI( "csmd_set_nrt_mode_func" ) 
	#define CAL_csmd_set_nrt_mode_func  csmd_set_nrt_mode_func
	#define CHK_csmd_set_nrt_mode_func  TRUE
	#define EXP_csmd_set_nrt_mode_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_set_nrt_mode_func", (RTS_UINTPTR)csmd_set_nrt_mode_func, 1, 0x31E74A3D, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_set_nrt_mode_func
	#define EXT_CmpSercos3Mastercsmd_set_nrt_mode_func
	#define GET_CmpSercos3Mastercsmd_set_nrt_mode_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_set_nrt_mode_func  csmd_set_nrt_mode_func
	#define CHK_CmpSercos3Mastercsmd_set_nrt_mode_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_set_nrt_mode_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_set_nrt_mode_func", (RTS_UINTPTR)csmd_set_nrt_mode_func, 1, 0x31E74A3D, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_set_nrt_mode_func
	#define EXT_csmd_set_nrt_mode_func
	#define GET_csmd_set_nrt_mode_func(fl)  CAL_CMGETAPI( "csmd_set_nrt_mode_func" ) 
	#define CAL_csmd_set_nrt_mode_func  csmd_set_nrt_mode_func
	#define CHK_csmd_set_nrt_mode_func  TRUE
	#define EXP_csmd_set_nrt_mode_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_set_nrt_mode_func", (RTS_UINTPTR)csmd_set_nrt_mode_func, 1, 0x31E74A3D, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_set_nrt_mode_func  PFCSMD_SET_NRT_MODE_FUNC_IEC pfcsmd_set_nrt_mode_func;
	#define EXT_csmd_set_nrt_mode_func  extern PFCSMD_SET_NRT_MODE_FUNC_IEC pfcsmd_set_nrt_mode_func;
	#define GET_csmd_set_nrt_mode_func(fl)  s_pfCMGetAPI2( "csmd_set_nrt_mode_func", (RTS_VOID_FCTPTR *)&pfcsmd_set_nrt_mode_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x31E74A3D, 0x03050600)
	#define CAL_csmd_set_nrt_mode_func  pfcsmd_set_nrt_mode_func
	#define CHK_csmd_set_nrt_mode_func  (pfcsmd_set_nrt_mode_func != NULL)
	#define EXP_csmd_set_nrt_mode_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_set_nrt_mode_func", (RTS_UINTPTR)csmd_set_nrt_mode_func, 1, 0x31E74A3D, 0x03050600) 
#endif


/**
 * <description>csmd_setcommand_func</description>
 */
typedef struct tagcsmd_setcommand_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchData;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_SetCommand_Func;	/* VAR_OUTPUT */	
} csmd_setcommand_func_struct;

void CDECL CDECL_EXT csmd_setcommand_func(csmd_setcommand_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_SETCOMMAND_FUNC_IEC) (csmd_setcommand_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_SETCOMMAND_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_setcommand_func
	#define EXT_csmd_setcommand_func
	#define GET_csmd_setcommand_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_setcommand_func(p0) 
	#define CHK_csmd_setcommand_func  FALSE
	#define EXP_csmd_setcommand_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_setcommand_func
	#define EXT_csmd_setcommand_func
	#define GET_csmd_setcommand_func(fl)  CAL_CMGETAPI( "csmd_setcommand_func" ) 
	#define CAL_csmd_setcommand_func  csmd_setcommand_func
	#define CHK_csmd_setcommand_func  TRUE
	#define EXP_csmd_setcommand_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setcommand_func", (RTS_UINTPTR)csmd_setcommand_func, 1, 0xB09682A5, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_setcommand_func
	#define EXT_csmd_setcommand_func
	#define GET_csmd_setcommand_func(fl)  CAL_CMGETAPI( "csmd_setcommand_func" ) 
	#define CAL_csmd_setcommand_func  csmd_setcommand_func
	#define CHK_csmd_setcommand_func  TRUE
	#define EXP_csmd_setcommand_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setcommand_func", (RTS_UINTPTR)csmd_setcommand_func, 1, 0xB09682A5, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_setcommand_func
	#define EXT_CmpSercos3Mastercsmd_setcommand_func
	#define GET_CmpSercos3Mastercsmd_setcommand_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_setcommand_func  csmd_setcommand_func
	#define CHK_CmpSercos3Mastercsmd_setcommand_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_setcommand_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setcommand_func", (RTS_UINTPTR)csmd_setcommand_func, 1, 0xB09682A5, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_setcommand_func
	#define EXT_csmd_setcommand_func
	#define GET_csmd_setcommand_func(fl)  CAL_CMGETAPI( "csmd_setcommand_func" ) 
	#define CAL_csmd_setcommand_func  csmd_setcommand_func
	#define CHK_csmd_setcommand_func  TRUE
	#define EXP_csmd_setcommand_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setcommand_func", (RTS_UINTPTR)csmd_setcommand_func, 1, 0xB09682A5, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_setcommand_func  PFCSMD_SETCOMMAND_FUNC_IEC pfcsmd_setcommand_func;
	#define EXT_csmd_setcommand_func  extern PFCSMD_SETCOMMAND_FUNC_IEC pfcsmd_setcommand_func;
	#define GET_csmd_setcommand_func(fl)  s_pfCMGetAPI2( "csmd_setcommand_func", (RTS_VOID_FCTPTR *)&pfcsmd_setcommand_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xB09682A5, 0x03050600)
	#define CAL_csmd_setcommand_func  pfcsmd_setcommand_func
	#define CHK_csmd_setcommand_func  (pfcsmd_setcommand_func != NULL)
	#define EXP_csmd_setcommand_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setcommand_func", (RTS_UINTPTR)csmd_setcommand_func, 1, 0xB09682A5, 0x03050600) 
#endif


/**
 * <description>csmd_setcommparam_func</description>
 */
typedef struct tagcsmd_setcommparam_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prHW_Init_Struct;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_SetCommParam_Func;	/* VAR_OUTPUT */	
} csmd_setcommparam_func_struct;

void CDECL CDECL_EXT csmd_setcommparam_func(csmd_setcommparam_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_SETCOMMPARAM_FUNC_IEC) (csmd_setcommparam_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_SETCOMMPARAM_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_setcommparam_func
	#define EXT_csmd_setcommparam_func
	#define GET_csmd_setcommparam_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_setcommparam_func(p0) 
	#define CHK_csmd_setcommparam_func  FALSE
	#define EXP_csmd_setcommparam_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_setcommparam_func
	#define EXT_csmd_setcommparam_func
	#define GET_csmd_setcommparam_func(fl)  CAL_CMGETAPI( "csmd_setcommparam_func" ) 
	#define CAL_csmd_setcommparam_func  csmd_setcommparam_func
	#define CHK_csmd_setcommparam_func  TRUE
	#define EXP_csmd_setcommparam_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setcommparam_func", (RTS_UINTPTR)csmd_setcommparam_func, 1, 0x66EEDBA0, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_setcommparam_func
	#define EXT_csmd_setcommparam_func
	#define GET_csmd_setcommparam_func(fl)  CAL_CMGETAPI( "csmd_setcommparam_func" ) 
	#define CAL_csmd_setcommparam_func  csmd_setcommparam_func
	#define CHK_csmd_setcommparam_func  TRUE
	#define EXP_csmd_setcommparam_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setcommparam_func", (RTS_UINTPTR)csmd_setcommparam_func, 1, 0x66EEDBA0, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_setcommparam_func
	#define EXT_CmpSercos3Mastercsmd_setcommparam_func
	#define GET_CmpSercos3Mastercsmd_setcommparam_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_setcommparam_func  csmd_setcommparam_func
	#define CHK_CmpSercos3Mastercsmd_setcommparam_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_setcommparam_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setcommparam_func", (RTS_UINTPTR)csmd_setcommparam_func, 1, 0x66EEDBA0, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_setcommparam_func
	#define EXT_csmd_setcommparam_func
	#define GET_csmd_setcommparam_func(fl)  CAL_CMGETAPI( "csmd_setcommparam_func" ) 
	#define CAL_csmd_setcommparam_func  csmd_setcommparam_func
	#define CHK_csmd_setcommparam_func  TRUE
	#define EXP_csmd_setcommparam_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setcommparam_func", (RTS_UINTPTR)csmd_setcommparam_func, 1, 0x66EEDBA0, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_setcommparam_func  PFCSMD_SETCOMMPARAM_FUNC_IEC pfcsmd_setcommparam_func;
	#define EXT_csmd_setcommparam_func  extern PFCSMD_SETCOMMPARAM_FUNC_IEC pfcsmd_setcommparam_func;
	#define GET_csmd_setcommparam_func(fl)  s_pfCMGetAPI2( "csmd_setcommparam_func", (RTS_VOID_FCTPTR *)&pfcsmd_setcommparam_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x66EEDBA0, 0x03050600)
	#define CAL_csmd_setcommparam_func  pfcsmd_setcommparam_func
	#define CHK_csmd_setcommparam_func  (pfcsmd_setcommparam_func != NULL)
	#define EXP_csmd_setcommparam_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setcommparam_func", (RTS_UINTPTR)csmd_setcommparam_func, 1, 0x66EEDBA0, 0x03050600) 
#endif


/**
 * <description>csmd_setphase0_func</description>
 */
typedef struct tagcsmd_setphase0_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prFuncState;			/* VAR_INPUT */	
	RTS_IEC_WORD **pwRecognizedDeviceList;	/* VAR_INPUT */	
	RTS_IEC_WORD eComVersion;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_SetPhase0_Func;	/* VAR_OUTPUT */	
} csmd_setphase0_func_struct;

void CDECL CDECL_EXT csmd_setphase0_func(csmd_setphase0_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_SETPHASE0_FUNC_IEC) (csmd_setphase0_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_SETPHASE0_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_setphase0_func
	#define EXT_csmd_setphase0_func
	#define GET_csmd_setphase0_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_setphase0_func(p0) 
	#define CHK_csmd_setphase0_func  FALSE
	#define EXP_csmd_setphase0_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_setphase0_func
	#define EXT_csmd_setphase0_func
	#define GET_csmd_setphase0_func(fl)  CAL_CMGETAPI( "csmd_setphase0_func" ) 
	#define CAL_csmd_setphase0_func  csmd_setphase0_func
	#define CHK_csmd_setphase0_func  TRUE
	#define EXP_csmd_setphase0_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase0_func", (RTS_UINTPTR)csmd_setphase0_func, 1, 0x63660DD2, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_setphase0_func
	#define EXT_csmd_setphase0_func
	#define GET_csmd_setphase0_func(fl)  CAL_CMGETAPI( "csmd_setphase0_func" ) 
	#define CAL_csmd_setphase0_func  csmd_setphase0_func
	#define CHK_csmd_setphase0_func  TRUE
	#define EXP_csmd_setphase0_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase0_func", (RTS_UINTPTR)csmd_setphase0_func, 1, 0x63660DD2, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_setphase0_func
	#define EXT_CmpSercos3Mastercsmd_setphase0_func
	#define GET_CmpSercos3Mastercsmd_setphase0_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_setphase0_func  csmd_setphase0_func
	#define CHK_CmpSercos3Mastercsmd_setphase0_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_setphase0_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase0_func", (RTS_UINTPTR)csmd_setphase0_func, 1, 0x63660DD2, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_setphase0_func
	#define EXT_csmd_setphase0_func
	#define GET_csmd_setphase0_func(fl)  CAL_CMGETAPI( "csmd_setphase0_func" ) 
	#define CAL_csmd_setphase0_func  csmd_setphase0_func
	#define CHK_csmd_setphase0_func  TRUE
	#define EXP_csmd_setphase0_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase0_func", (RTS_UINTPTR)csmd_setphase0_func, 1, 0x63660DD2, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_setphase0_func  PFCSMD_SETPHASE0_FUNC_IEC pfcsmd_setphase0_func;
	#define EXT_csmd_setphase0_func  extern PFCSMD_SETPHASE0_FUNC_IEC pfcsmd_setphase0_func;
	#define GET_csmd_setphase0_func(fl)  s_pfCMGetAPI2( "csmd_setphase0_func", (RTS_VOID_FCTPTR *)&pfcsmd_setphase0_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x63660DD2, 0x03050600)
	#define CAL_csmd_setphase0_func  pfcsmd_setphase0_func
	#define CHK_csmd_setphase0_func  (pfcsmd_setphase0_func != NULL)
	#define EXP_csmd_setphase0_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase0_func", (RTS_UINTPTR)csmd_setphase0_func, 1, 0x63660DD2, 0x03050600) 
#endif


/**
 * <description>csmd_setphase1_func</description>
 */
typedef struct tagcsmd_setphase1_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prFuncState;			/* VAR_INPUT */	
	RTS_IEC_WORD *pusOperableDeviceList;	/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_SetPhase1_Func;	/* VAR_OUTPUT */	
} csmd_setphase1_func_struct;

void CDECL CDECL_EXT csmd_setphase1_func(csmd_setphase1_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_SETPHASE1_FUNC_IEC) (csmd_setphase1_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_SETPHASE1_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_setphase1_func
	#define EXT_csmd_setphase1_func
	#define GET_csmd_setphase1_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_setphase1_func(p0) 
	#define CHK_csmd_setphase1_func  FALSE
	#define EXP_csmd_setphase1_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_setphase1_func
	#define EXT_csmd_setphase1_func
	#define GET_csmd_setphase1_func(fl)  CAL_CMGETAPI( "csmd_setphase1_func" ) 
	#define CAL_csmd_setphase1_func  csmd_setphase1_func
	#define CHK_csmd_setphase1_func  TRUE
	#define EXP_csmd_setphase1_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase1_func", (RTS_UINTPTR)csmd_setphase1_func, 1, 0xE87B4786, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_setphase1_func
	#define EXT_csmd_setphase1_func
	#define GET_csmd_setphase1_func(fl)  CAL_CMGETAPI( "csmd_setphase1_func" ) 
	#define CAL_csmd_setphase1_func  csmd_setphase1_func
	#define CHK_csmd_setphase1_func  TRUE
	#define EXP_csmd_setphase1_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase1_func", (RTS_UINTPTR)csmd_setphase1_func, 1, 0xE87B4786, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_setphase1_func
	#define EXT_CmpSercos3Mastercsmd_setphase1_func
	#define GET_CmpSercos3Mastercsmd_setphase1_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_setphase1_func  csmd_setphase1_func
	#define CHK_CmpSercos3Mastercsmd_setphase1_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_setphase1_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase1_func", (RTS_UINTPTR)csmd_setphase1_func, 1, 0xE87B4786, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_setphase1_func
	#define EXT_csmd_setphase1_func
	#define GET_csmd_setphase1_func(fl)  CAL_CMGETAPI( "csmd_setphase1_func" ) 
	#define CAL_csmd_setphase1_func  csmd_setphase1_func
	#define CHK_csmd_setphase1_func  TRUE
	#define EXP_csmd_setphase1_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase1_func", (RTS_UINTPTR)csmd_setphase1_func, 1, 0xE87B4786, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_setphase1_func  PFCSMD_SETPHASE1_FUNC_IEC pfcsmd_setphase1_func;
	#define EXT_csmd_setphase1_func  extern PFCSMD_SETPHASE1_FUNC_IEC pfcsmd_setphase1_func;
	#define GET_csmd_setphase1_func(fl)  s_pfCMGetAPI2( "csmd_setphase1_func", (RTS_VOID_FCTPTR *)&pfcsmd_setphase1_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xE87B4786, 0x03050600)
	#define CAL_csmd_setphase1_func  pfcsmd_setphase1_func
	#define CHK_csmd_setphase1_func  (pfcsmd_setphase1_func != NULL)
	#define EXP_csmd_setphase1_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase1_func", (RTS_UINTPTR)csmd_setphase1_func, 1, 0xE87B4786, 0x03050600) 
#endif


/**
 * <description>csmd_setphase2_func</description>
 */
typedef struct tagcsmd_setphase2_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prFuncState;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_SetPhase2_Func;	/* VAR_OUTPUT */	
} csmd_setphase2_func_struct;

void CDECL CDECL_EXT csmd_setphase2_func(csmd_setphase2_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_SETPHASE2_FUNC_IEC) (csmd_setphase2_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_SETPHASE2_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_setphase2_func
	#define EXT_csmd_setphase2_func
	#define GET_csmd_setphase2_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_setphase2_func(p0) 
	#define CHK_csmd_setphase2_func  FALSE
	#define EXP_csmd_setphase2_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_setphase2_func
	#define EXT_csmd_setphase2_func
	#define GET_csmd_setphase2_func(fl)  CAL_CMGETAPI( "csmd_setphase2_func" ) 
	#define CAL_csmd_setphase2_func  csmd_setphase2_func
	#define CHK_csmd_setphase2_func  TRUE
	#define EXP_csmd_setphase2_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase2_func", (RTS_UINTPTR)csmd_setphase2_func, 1, 0xC968421B, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_setphase2_func
	#define EXT_csmd_setphase2_func
	#define GET_csmd_setphase2_func(fl)  CAL_CMGETAPI( "csmd_setphase2_func" ) 
	#define CAL_csmd_setphase2_func  csmd_setphase2_func
	#define CHK_csmd_setphase2_func  TRUE
	#define EXP_csmd_setphase2_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase2_func", (RTS_UINTPTR)csmd_setphase2_func, 1, 0xC968421B, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_setphase2_func
	#define EXT_CmpSercos3Mastercsmd_setphase2_func
	#define GET_CmpSercos3Mastercsmd_setphase2_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_setphase2_func  csmd_setphase2_func
	#define CHK_CmpSercos3Mastercsmd_setphase2_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_setphase2_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase2_func", (RTS_UINTPTR)csmd_setphase2_func, 1, 0xC968421B, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_setphase2_func
	#define EXT_csmd_setphase2_func
	#define GET_csmd_setphase2_func(fl)  CAL_CMGETAPI( "csmd_setphase2_func" ) 
	#define CAL_csmd_setphase2_func  csmd_setphase2_func
	#define CHK_csmd_setphase2_func  TRUE
	#define EXP_csmd_setphase2_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase2_func", (RTS_UINTPTR)csmd_setphase2_func, 1, 0xC968421B, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_setphase2_func  PFCSMD_SETPHASE2_FUNC_IEC pfcsmd_setphase2_func;
	#define EXT_csmd_setphase2_func  extern PFCSMD_SETPHASE2_FUNC_IEC pfcsmd_setphase2_func;
	#define GET_csmd_setphase2_func(fl)  s_pfCMGetAPI2( "csmd_setphase2_func", (RTS_VOID_FCTPTR *)&pfcsmd_setphase2_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xC968421B, 0x03050600)
	#define CAL_csmd_setphase2_func  pfcsmd_setphase2_func
	#define CHK_csmd_setphase2_func  (pfcsmd_setphase2_func != NULL)
	#define EXP_csmd_setphase2_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase2_func", (RTS_UINTPTR)csmd_setphase2_func, 1, 0xC968421B, 0x03050600) 
#endif


/**
 * <description>csmd_setphase3_func</description>
 */
typedef struct tagcsmd_setphase3_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prFuncState;			/* VAR_INPUT */	
	RTS_IEC_BYTE *parSvcMacro;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_SetPhase3_Func;	/* VAR_OUTPUT */	
} csmd_setphase3_func_struct;

void CDECL CDECL_EXT csmd_setphase3_func(csmd_setphase3_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_SETPHASE3_FUNC_IEC) (csmd_setphase3_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_SETPHASE3_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_setphase3_func
	#define EXT_csmd_setphase3_func
	#define GET_csmd_setphase3_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_setphase3_func(p0) 
	#define CHK_csmd_setphase3_func  FALSE
	#define EXP_csmd_setphase3_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_setphase3_func
	#define EXT_csmd_setphase3_func
	#define GET_csmd_setphase3_func(fl)  CAL_CMGETAPI( "csmd_setphase3_func" ) 
	#define CAL_csmd_setphase3_func  csmd_setphase3_func
	#define CHK_csmd_setphase3_func  TRUE
	#define EXP_csmd_setphase3_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase3_func", (RTS_UINTPTR)csmd_setphase3_func, 1, 0x17B4657A, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_setphase3_func
	#define EXT_csmd_setphase3_func
	#define GET_csmd_setphase3_func(fl)  CAL_CMGETAPI( "csmd_setphase3_func" ) 
	#define CAL_csmd_setphase3_func  csmd_setphase3_func
	#define CHK_csmd_setphase3_func  TRUE
	#define EXP_csmd_setphase3_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase3_func", (RTS_UINTPTR)csmd_setphase3_func, 1, 0x17B4657A, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_setphase3_func
	#define EXT_CmpSercos3Mastercsmd_setphase3_func
	#define GET_CmpSercos3Mastercsmd_setphase3_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_setphase3_func  csmd_setphase3_func
	#define CHK_CmpSercos3Mastercsmd_setphase3_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_setphase3_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase3_func", (RTS_UINTPTR)csmd_setphase3_func, 1, 0x17B4657A, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_setphase3_func
	#define EXT_csmd_setphase3_func
	#define GET_csmd_setphase3_func(fl)  CAL_CMGETAPI( "csmd_setphase3_func" ) 
	#define CAL_csmd_setphase3_func  csmd_setphase3_func
	#define CHK_csmd_setphase3_func  TRUE
	#define EXP_csmd_setphase3_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase3_func", (RTS_UINTPTR)csmd_setphase3_func, 1, 0x17B4657A, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_setphase3_func  PFCSMD_SETPHASE3_FUNC_IEC pfcsmd_setphase3_func;
	#define EXT_csmd_setphase3_func  extern PFCSMD_SETPHASE3_FUNC_IEC pfcsmd_setphase3_func;
	#define GET_csmd_setphase3_func(fl)  s_pfCMGetAPI2( "csmd_setphase3_func", (RTS_VOID_FCTPTR *)&pfcsmd_setphase3_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x17B4657A, 0x03050600)
	#define CAL_csmd_setphase3_func  pfcsmd_setphase3_func
	#define CHK_csmd_setphase3_func  (pfcsmd_setphase3_func != NULL)
	#define EXP_csmd_setphase3_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase3_func", (RTS_UINTPTR)csmd_setphase3_func, 1, 0x17B4657A, 0x03050600) 
#endif


/**
 * <description>csmd_setphase4_func</description>
 */
typedef struct tagcsmd_setphase4_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prFuncState;			/* VAR_INPUT */	
	RTS_IEC_BYTE *parSvcMacro;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_SetPhase4_Func;	/* VAR_OUTPUT */	
} csmd_setphase4_func_struct;

void CDECL CDECL_EXT csmd_setphase4_func(csmd_setphase4_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_SETPHASE4_FUNC_IEC) (csmd_setphase4_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_SETPHASE4_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_setphase4_func
	#define EXT_csmd_setphase4_func
	#define GET_csmd_setphase4_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_setphase4_func(p0) 
	#define CHK_csmd_setphase4_func  FALSE
	#define EXP_csmd_setphase4_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_setphase4_func
	#define EXT_csmd_setphase4_func
	#define GET_csmd_setphase4_func(fl)  CAL_CMGETAPI( "csmd_setphase4_func" ) 
	#define CAL_csmd_setphase4_func  csmd_setphase4_func
	#define CHK_csmd_setphase4_func  TRUE
	#define EXP_csmd_setphase4_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase4_func", (RTS_UINTPTR)csmd_setphase4_func, 1, 0xAF666F4D, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_setphase4_func
	#define EXT_csmd_setphase4_func
	#define GET_csmd_setphase4_func(fl)  CAL_CMGETAPI( "csmd_setphase4_func" ) 
	#define CAL_csmd_setphase4_func  csmd_setphase4_func
	#define CHK_csmd_setphase4_func  TRUE
	#define EXP_csmd_setphase4_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase4_func", (RTS_UINTPTR)csmd_setphase4_func, 1, 0xAF666F4D, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_setphase4_func
	#define EXT_CmpSercos3Mastercsmd_setphase4_func
	#define GET_CmpSercos3Mastercsmd_setphase4_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_setphase4_func  csmd_setphase4_func
	#define CHK_CmpSercos3Mastercsmd_setphase4_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_setphase4_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase4_func", (RTS_UINTPTR)csmd_setphase4_func, 1, 0xAF666F4D, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_setphase4_func
	#define EXT_csmd_setphase4_func
	#define GET_csmd_setphase4_func(fl)  CAL_CMGETAPI( "csmd_setphase4_func" ) 
	#define CAL_csmd_setphase4_func  csmd_setphase4_func
	#define CHK_csmd_setphase4_func  TRUE
	#define EXP_csmd_setphase4_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase4_func", (RTS_UINTPTR)csmd_setphase4_func, 1, 0xAF666F4D, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_setphase4_func  PFCSMD_SETPHASE4_FUNC_IEC pfcsmd_setphase4_func;
	#define EXT_csmd_setphase4_func  extern PFCSMD_SETPHASE4_FUNC_IEC pfcsmd_setphase4_func;
	#define GET_csmd_setphase4_func(fl)  s_pfCMGetAPI2( "csmd_setphase4_func", (RTS_VOID_FCTPTR *)&pfcsmd_setphase4_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xAF666F4D, 0x03050600)
	#define CAL_csmd_setphase4_func  pfcsmd_setphase4_func
	#define CHK_csmd_setphase4_func  (pfcsmd_setphase4_func != NULL)
	#define EXP_csmd_setphase4_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_setphase4_func", (RTS_UINTPTR)csmd_setphase4_func, 1, 0xAF666F4D, 0x03050600) 
#endif


/**
 * <description>csmd_transmittiming_func</description>
 */
typedef struct tagcsmd_transmittiming_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prFuncState;			/* VAR_INPUT */	
	RTS_IEC_BYTE *parSvcMacro;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_TransmitTiming_Func;	/* VAR_OUTPUT */	
} csmd_transmittiming_func_struct;

void CDECL CDECL_EXT csmd_transmittiming_func(csmd_transmittiming_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_TRANSMITTIMING_FUNC_IEC) (csmd_transmittiming_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_TRANSMITTIMING_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_transmittiming_func
	#define EXT_csmd_transmittiming_func
	#define GET_csmd_transmittiming_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_transmittiming_func(p0) 
	#define CHK_csmd_transmittiming_func  FALSE
	#define EXP_csmd_transmittiming_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_transmittiming_func
	#define EXT_csmd_transmittiming_func
	#define GET_csmd_transmittiming_func(fl)  CAL_CMGETAPI( "csmd_transmittiming_func" ) 
	#define CAL_csmd_transmittiming_func  csmd_transmittiming_func
	#define CHK_csmd_transmittiming_func  TRUE
	#define EXP_csmd_transmittiming_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_transmittiming_func", (RTS_UINTPTR)csmd_transmittiming_func, 1, 0x62B09AE5, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_transmittiming_func
	#define EXT_csmd_transmittiming_func
	#define GET_csmd_transmittiming_func(fl)  CAL_CMGETAPI( "csmd_transmittiming_func" ) 
	#define CAL_csmd_transmittiming_func  csmd_transmittiming_func
	#define CHK_csmd_transmittiming_func  TRUE
	#define EXP_csmd_transmittiming_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_transmittiming_func", (RTS_UINTPTR)csmd_transmittiming_func, 1, 0x62B09AE5, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_transmittiming_func
	#define EXT_CmpSercos3Mastercsmd_transmittiming_func
	#define GET_CmpSercos3Mastercsmd_transmittiming_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_transmittiming_func  csmd_transmittiming_func
	#define CHK_CmpSercos3Mastercsmd_transmittiming_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_transmittiming_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_transmittiming_func", (RTS_UINTPTR)csmd_transmittiming_func, 1, 0x62B09AE5, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_transmittiming_func
	#define EXT_csmd_transmittiming_func
	#define GET_csmd_transmittiming_func(fl)  CAL_CMGETAPI( "csmd_transmittiming_func" ) 
	#define CAL_csmd_transmittiming_func  csmd_transmittiming_func
	#define CHK_csmd_transmittiming_func  TRUE
	#define EXP_csmd_transmittiming_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_transmittiming_func", (RTS_UINTPTR)csmd_transmittiming_func, 1, 0x62B09AE5, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_transmittiming_func  PFCSMD_TRANSMITTIMING_FUNC_IEC pfcsmd_transmittiming_func;
	#define EXT_csmd_transmittiming_func  extern PFCSMD_TRANSMITTIMING_FUNC_IEC pfcsmd_transmittiming_func;
	#define GET_csmd_transmittiming_func(fl)  s_pfCMGetAPI2( "csmd_transmittiming_func", (RTS_VOID_FCTPTR *)&pfcsmd_transmittiming_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x62B09AE5, 0x03050600)
	#define CAL_csmd_transmittiming_func  pfcsmd_transmittiming_func
	#define CHK_csmd_transmittiming_func  (pfcsmd_transmittiming_func != NULL)
	#define EXP_csmd_transmittiming_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_transmittiming_func", (RTS_UINTPTR)csmd_transmittiming_func, 1, 0x62B09AE5, 0x03050600) 
#endif


/**
 * <description>csmd_txrxsoftcont_func</description>
 */
typedef struct tagcsmd_txrxsoftcont_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_TxRxSoftCont_Func;	/* VAR_OUTPUT */	
} csmd_txrxsoftcont_func_struct;

void CDECL CDECL_EXT csmd_txrxsoftcont_func(csmd_txrxsoftcont_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_TXRXSOFTCONT_FUNC_IEC) (csmd_txrxsoftcont_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_TXRXSOFTCONT_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_txrxsoftcont_func
	#define EXT_csmd_txrxsoftcont_func
	#define GET_csmd_txrxsoftcont_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_txrxsoftcont_func(p0) 
	#define CHK_csmd_txrxsoftcont_func  FALSE
	#define EXP_csmd_txrxsoftcont_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_txrxsoftcont_func
	#define EXT_csmd_txrxsoftcont_func
	#define GET_csmd_txrxsoftcont_func(fl)  CAL_CMGETAPI( "csmd_txrxsoftcont_func" ) 
	#define CAL_csmd_txrxsoftcont_func  csmd_txrxsoftcont_func
	#define CHK_csmd_txrxsoftcont_func  TRUE
	#define EXP_csmd_txrxsoftcont_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_txrxsoftcont_func", (RTS_UINTPTR)csmd_txrxsoftcont_func, 1, 0x25210353, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_txrxsoftcont_func
	#define EXT_csmd_txrxsoftcont_func
	#define GET_csmd_txrxsoftcont_func(fl)  CAL_CMGETAPI( "csmd_txrxsoftcont_func" ) 
	#define CAL_csmd_txrxsoftcont_func  csmd_txrxsoftcont_func
	#define CHK_csmd_txrxsoftcont_func  TRUE
	#define EXP_csmd_txrxsoftcont_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_txrxsoftcont_func", (RTS_UINTPTR)csmd_txrxsoftcont_func, 1, 0x25210353, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_txrxsoftcont_func
	#define EXT_CmpSercos3Mastercsmd_txrxsoftcont_func
	#define GET_CmpSercos3Mastercsmd_txrxsoftcont_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_txrxsoftcont_func  csmd_txrxsoftcont_func
	#define CHK_CmpSercos3Mastercsmd_txrxsoftcont_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_txrxsoftcont_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_txrxsoftcont_func", (RTS_UINTPTR)csmd_txrxsoftcont_func, 1, 0x25210353, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_txrxsoftcont_func
	#define EXT_csmd_txrxsoftcont_func
	#define GET_csmd_txrxsoftcont_func(fl)  CAL_CMGETAPI( "csmd_txrxsoftcont_func" ) 
	#define CAL_csmd_txrxsoftcont_func  csmd_txrxsoftcont_func
	#define CHK_csmd_txrxsoftcont_func  TRUE
	#define EXP_csmd_txrxsoftcont_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_txrxsoftcont_func", (RTS_UINTPTR)csmd_txrxsoftcont_func, 1, 0x25210353, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_txrxsoftcont_func  PFCSMD_TXRXSOFTCONT_FUNC_IEC pfcsmd_txrxsoftcont_func;
	#define EXT_csmd_txrxsoftcont_func  extern PFCSMD_TXRXSOFTCONT_FUNC_IEC pfcsmd_txrxsoftcont_func;
	#define GET_csmd_txrxsoftcont_func(fl)  s_pfCMGetAPI2( "csmd_txrxsoftcont_func", (RTS_VOID_FCTPTR *)&pfcsmd_txrxsoftcont_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x25210353, 0x03050600)
	#define CAL_csmd_txrxsoftcont_func  pfcsmd_txrxsoftcont_func
	#define CHK_csmd_txrxsoftcont_func  (pfcsmd_txrxsoftcont_func != NULL)
	#define EXP_csmd_txrxsoftcont_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_txrxsoftcont_func", (RTS_UINTPTR)csmd_txrxsoftcont_func, 1, 0x25210353, 0x03050600) 
#endif


/**
 * <description>csmd_writemdt_func</description>
 */
typedef struct tagcsmd_writemdt_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prMDTSource;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_WriteMDT_Func;	/* VAR_OUTPUT */	
} csmd_writemdt_func_struct;

void CDECL CDECL_EXT csmd_writemdt_func(csmd_writemdt_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_WRITEMDT_FUNC_IEC) (csmd_writemdt_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_WRITEMDT_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_writemdt_func
	#define EXT_csmd_writemdt_func
	#define GET_csmd_writemdt_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_writemdt_func(p0) 
	#define CHK_csmd_writemdt_func  FALSE
	#define EXP_csmd_writemdt_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_writemdt_func
	#define EXT_csmd_writemdt_func
	#define GET_csmd_writemdt_func(fl)  CAL_CMGETAPI( "csmd_writemdt_func" ) 
	#define CAL_csmd_writemdt_func  csmd_writemdt_func
	#define CHK_csmd_writemdt_func  TRUE
	#define EXP_csmd_writemdt_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_writemdt_func", (RTS_UINTPTR)csmd_writemdt_func, 1, 0x2127D1D8, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_writemdt_func
	#define EXT_csmd_writemdt_func
	#define GET_csmd_writemdt_func(fl)  CAL_CMGETAPI( "csmd_writemdt_func" ) 
	#define CAL_csmd_writemdt_func  csmd_writemdt_func
	#define CHK_csmd_writemdt_func  TRUE
	#define EXP_csmd_writemdt_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_writemdt_func", (RTS_UINTPTR)csmd_writemdt_func, 1, 0x2127D1D8, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_writemdt_func
	#define EXT_CmpSercos3Mastercsmd_writemdt_func
	#define GET_CmpSercos3Mastercsmd_writemdt_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_writemdt_func  csmd_writemdt_func
	#define CHK_CmpSercos3Mastercsmd_writemdt_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_writemdt_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_writemdt_func", (RTS_UINTPTR)csmd_writemdt_func, 1, 0x2127D1D8, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_writemdt_func
	#define EXT_csmd_writemdt_func
	#define GET_csmd_writemdt_func(fl)  CAL_CMGETAPI( "csmd_writemdt_func" ) 
	#define CAL_csmd_writemdt_func  csmd_writemdt_func
	#define CHK_csmd_writemdt_func  TRUE
	#define EXP_csmd_writemdt_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_writemdt_func", (RTS_UINTPTR)csmd_writemdt_func, 1, 0x2127D1D8, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_writemdt_func  PFCSMD_WRITEMDT_FUNC_IEC pfcsmd_writemdt_func;
	#define EXT_csmd_writemdt_func  extern PFCSMD_WRITEMDT_FUNC_IEC pfcsmd_writemdt_func;
	#define GET_csmd_writemdt_func(fl)  s_pfCMGetAPI2( "csmd_writemdt_func", (RTS_VOID_FCTPTR *)&pfcsmd_writemdt_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x2127D1D8, 0x03050600)
	#define CAL_csmd_writemdt_func  pfcsmd_writemdt_func
	#define CHK_csmd_writemdt_func  (pfcsmd_writemdt_func != NULL)
	#define EXP_csmd_writemdt_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_writemdt_func", (RTS_UINTPTR)csmd_writemdt_func, 1, 0x2127D1D8, 0x03050600) 
#endif


/**
 * <description>csmd_writesvch_func</description>
 */
typedef struct tagcsmd_writesvch_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchData;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_WriteSVCH_Func;	/* VAR_OUTPUT */	
} csmd_writesvch_func_struct;

void CDECL CDECL_EXT csmd_writesvch_func(csmd_writesvch_func_struct *p);
typedef void (CDECL CDECL_EXT* PFCSMD_WRITESVCH_FUNC_IEC) (csmd_writesvch_func_struct *p);
#if defined(CMPSERCOS3MASTER_NOTIMPLEMENTED) || defined(CSMD_WRITESVCH_FUNC_NOTIMPLEMENTED)
	#define USE_csmd_writesvch_func
	#define EXT_csmd_writesvch_func
	#define GET_csmd_writesvch_func(fl)  ERR_NOTIMPLEMENTED
	#define CAL_csmd_writesvch_func(p0) 
	#define CHK_csmd_writesvch_func  FALSE
	#define EXP_csmd_writesvch_func  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_csmd_writesvch_func
	#define EXT_csmd_writesvch_func
	#define GET_csmd_writesvch_func(fl)  CAL_CMGETAPI( "csmd_writesvch_func" ) 
	#define CAL_csmd_writesvch_func  csmd_writesvch_func
	#define CHK_csmd_writesvch_func  TRUE
	#define EXP_csmd_writesvch_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_writesvch_func", (RTS_UINTPTR)csmd_writesvch_func, 1, 0xB775BE02, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPSERCOS3MASTER_EXTERNAL)
	#define USE_csmd_writesvch_func
	#define EXT_csmd_writesvch_func
	#define GET_csmd_writesvch_func(fl)  CAL_CMGETAPI( "csmd_writesvch_func" ) 
	#define CAL_csmd_writesvch_func  csmd_writesvch_func
	#define CHK_csmd_writesvch_func  TRUE
	#define EXP_csmd_writesvch_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_writesvch_func", (RTS_UINTPTR)csmd_writesvch_func, 1, 0xB775BE02, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSercos3Mastercsmd_writesvch_func
	#define EXT_CmpSercos3Mastercsmd_writesvch_func
	#define GET_CmpSercos3Mastercsmd_writesvch_func  ERR_OK
	#define CAL_CmpSercos3Mastercsmd_writesvch_func  csmd_writesvch_func
	#define CHK_CmpSercos3Mastercsmd_writesvch_func  TRUE
	#define EXP_CmpSercos3Mastercsmd_writesvch_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_writesvch_func", (RTS_UINTPTR)csmd_writesvch_func, 1, 0xB775BE02, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_csmd_writesvch_func
	#define EXT_csmd_writesvch_func
	#define GET_csmd_writesvch_func(fl)  CAL_CMGETAPI( "csmd_writesvch_func" ) 
	#define CAL_csmd_writesvch_func  csmd_writesvch_func
	#define CHK_csmd_writesvch_func  TRUE
	#define EXP_csmd_writesvch_func  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_writesvch_func", (RTS_UINTPTR)csmd_writesvch_func, 1, 0xB775BE02, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_csmd_writesvch_func  PFCSMD_WRITESVCH_FUNC_IEC pfcsmd_writesvch_func;
	#define EXT_csmd_writesvch_func  extern PFCSMD_WRITESVCH_FUNC_IEC pfcsmd_writesvch_func;
	#define GET_csmd_writesvch_func(fl)  s_pfCMGetAPI2( "csmd_writesvch_func", (RTS_VOID_FCTPTR *)&pfcsmd_writesvch_func, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xB775BE02, 0x03050600)
	#define CAL_csmd_writesvch_func  pfcsmd_writesvch_func
	#define CHK_csmd_writesvch_func  (pfcsmd_writesvch_func != NULL)
	#define EXP_csmd_writesvch_func   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"csmd_writesvch_func", (RTS_UINTPTR)csmd_writesvch_func, 1, 0xB775BE02, 0x03050600) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
} ICmpSercos3Master_C;

#ifdef CPLUSPLUS
class ICmpSercos3Master : public IBase
{
	public:
};
	#ifndef ITF_CmpSercos3Master
		#define ITF_CmpSercos3Master static ICmpSercos3Master *pICmpSercos3Master = NULL;
	#endif
	#define EXTITF_CmpSercos3Master
#else	/*CPLUSPLUS*/
	typedef ICmpSercos3Master_C		ICmpSercos3Master;
	#ifndef ITF_CmpSercos3Master
		#define ITF_CmpSercos3Master
	#endif
	#define EXTITF_CmpSercos3Master
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPSERCOS3MASTERITF_H_*/
