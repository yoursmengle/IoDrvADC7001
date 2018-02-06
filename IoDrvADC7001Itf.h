 /**
 * <interfacename>test</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _IODRVADC7001ITF_H_
#define _IODRVADC7001ITF_H_

#include "CmpStd.h"

 

 




/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>myexternalfunction</description>
 */
typedef struct tagmyexternalfunction_struct
{
	RTS_IEC_INT MyExternalFunction;		/* VAR_OUTPUT */
} myexternalfunction_struct;

void CDECL CDECL_EXT myexternalfunction(myexternalfunction_struct *p);
typedef void (CDECL CDECL_EXT* PFMYEXTERNALFUNCTION_IEC) (myexternalfunction_struct *p);
#if defined(IODRVADC7001_NOTIMPLEMENTED) || defined(MYEXTERNALFUNCTION_NOTIMPLEMENTED)
	#define USE_myexternalfunction
	#define EXT_myexternalfunction
	#define GET_myexternalfunction(fl)  ERR_NOTIMPLEMENTED
	#define CAL_myexternalfunction(p0) 
	#define CHK_myexternalfunction  FALSE
	#define EXP_myexternalfunction  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_myexternalfunction
	#define EXT_myexternalfunction
	#define GET_myexternalfunction(fl)  CAL_CMGETAPI( "myexternalfunction" ) 
	#define CAL_myexternalfunction  myexternalfunction
	#define CHK_myexternalfunction  TRUE
	#define EXP_myexternalfunction  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunction", (RTS_UINTPTR)myexternalfunction, 1, 0xE1C6D757, 0x3040000) 
#elif defined(MIXED_LINK) && !defined(IODRVADC7001_EXTERNAL)
	#define USE_myexternalfunction
	#define EXT_myexternalfunction
	#define GET_myexternalfunction(fl)  CAL_CMGETAPI( "myexternalfunction" ) 
	#define CAL_myexternalfunction  myexternalfunction
	#define CHK_myexternalfunction  TRUE
	#define EXP_myexternalfunction  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunction", (RTS_UINTPTR)myexternalfunction, 1, 0xE1C6D757, 0x3040000) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IoDrvADC7001myexternalfunction
	#define EXT_IoDrvADC7001myexternalfunction
	#define GET_IoDrvADC7001myexternalfunction  ERR_OK
	#define CAL_IoDrvADC7001myexternalfunction  myexternalfunction
	#define CHK_IoDrvADC7001myexternalfunction  TRUE
	#define EXP_IoDrvADC7001myexternalfunction  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunction", (RTS_UINTPTR)myexternalfunction, 1, 0xE1C6D757, 0x3040000) 
#elif defined(CPLUSPLUS)
	#define USE_myexternalfunction
	#define EXT_myexternalfunction
	#define GET_myexternalfunction(fl)  CAL_CMGETAPI( "myexternalfunction" ) 
	#define CAL_myexternalfunction  myexternalfunction
	#define CHK_myexternalfunction  TRUE
	#define EXP_myexternalfunction  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunction", (RTS_UINTPTR)myexternalfunction, 1, 0xE1C6D757, 0x3040000) 
#else /* DYNAMIC_LINK */
	#define USE_myexternalfunction  PFMYEXTERNALFUNCTION_IEC pfmyexternalfunction;
	#define EXT_myexternalfunction  extern PFMYEXTERNALFUNCTION_IEC pfmyexternalfunction;
	#define GET_myexternalfunction(fl)  s_pfCMGetAPI2( "myexternalfunction", (RTS_VOID_FCTPTR *)&pfmyexternalfunction, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xE1C6D757, 0x3040000)
	#define CAL_myexternalfunction  pfmyexternalfunction
	#define CHK_myexternalfunction  (pfmyexternalfunction != NULL)
	#define EXP_myexternalfunction   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunction", (RTS_UINTPTR)myexternalfunction, 1, 0xE1C6D757, 0x3040000) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
} IIoDrvADC7001_C;

#ifdef CPLUSPLUS
class IIoDrvADC7001 : public IBase
{
	public:
};
	#ifndef ITF_IoDrvADC7001
		#define ITF_IoDrvADC7001 static IIoDrvADC7001 *pIIoDrvADC7001 = NULL;
	#endif
	#define EXTITF_IoDrvADC7001
#else	/*CPLUSPLUS*/
	typedef IIoDrvADC7001_C		IIoDrvADC7001;
	#ifndef ITF_IoDrvADC7001
		#define ITF_IoDrvADC7001
	#endif
	#define EXTITF_IoDrvADC7001
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_IODRVADC7001ITF_H_*/
