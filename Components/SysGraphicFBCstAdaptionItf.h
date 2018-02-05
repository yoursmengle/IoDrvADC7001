 
	
	
#ifndef _SYSGRAPHICFBCSTADAPTIONITF_H_
#define _SYSGRAPHICFBCSTADAPTIONITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"

/* Hook definitions (0..10000 reserved for core components) */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	int iWindow_size_x;
	int iWindow_size_y;
	int iBits_per_pixel;
	int iBytes_per_pixel;
}SysGraphicGlobalParameters;

/**
 * <description> 
 * 
 * </description>
 * <result>ERR_OK</result>
 */
RTS_RESULT CDECL SysGraphicFBCstAdaptionGetGlobalParameters(SysGraphicGlobalParameters* pParameters);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICFBCSTADAPTIONGETGLOBALPARAMETERS) (SysGraphicGlobalParameters* pParameters);
#if defined(SYSGRAPHICFBCSTADAPTION_NOTIMPLEMENTED) || defined(SYSGRAPHICFBCSTADAPTIONGETGLOBALPARAMETERS_NOTIMPLEMENTED)
	#define USE_SysGraphicFBCstAdaptionGetGlobalParameters
	#define EXT_SysGraphicFBCstAdaptionGetGlobalParameters
	#define GET_SysGraphicFBCstAdaptionGetGlobalParameters(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicFBCstAdaptionGetGlobalParameters(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicFBCstAdaptionGetGlobalParameters  FALSE
	#define EXP_SysGraphicFBCstAdaptionGetGlobalParameters  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicFBCstAdaptionGetGlobalParameters
	#define EXT_SysGraphicFBCstAdaptionGetGlobalParameters
	#define GET_SysGraphicFBCstAdaptionGetGlobalParameters(fl)  CAL_CMGETAPI( "SysGraphicFBCstAdaptionGetGlobalParameters" ) 
	#define CAL_SysGraphicFBCstAdaptionGetGlobalParameters  SysGraphicFBCstAdaptionGetGlobalParameters
	#define CHK_SysGraphicFBCstAdaptionGetGlobalParameters  TRUE
	#define EXP_SysGraphicFBCstAdaptionGetGlobalParameters  CAL_CMEXPAPI( "SysGraphicFBCstAdaptionGetGlobalParameters" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICFBCSTADAPTION_EXTERNAL)
	#define USE_SysGraphicFBCstAdaptionGetGlobalParameters
	#define EXT_SysGraphicFBCstAdaptionGetGlobalParameters
	#define GET_SysGraphicFBCstAdaptionGetGlobalParameters(fl)  CAL_CMGETAPI( "SysGraphicFBCstAdaptionGetGlobalParameters" ) 
	#define CAL_SysGraphicFBCstAdaptionGetGlobalParameters  SysGraphicFBCstAdaptionGetGlobalParameters
	#define CHK_SysGraphicFBCstAdaptionGetGlobalParameters  TRUE
	#define EXP_SysGraphicFBCstAdaptionGetGlobalParameters  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicFBCstAdaptionGetGlobalParameters", (RTS_UINTPTR)SysGraphicFBCstAdaptionGetGlobalParameters, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionGetGlobalParameters
	#define EXT_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionGetGlobalParameters
	#define GET_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionGetGlobalParameters  ERR_OK
	#define CAL_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionGetGlobalParameters pISysGraphicFBCstAdaption->ISysGraphicFBCstAdaptionGetGlobalParameters
	#define CHK_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionGetGlobalParameters (pISysGraphicFBCstAdaption != NULL)
	#define EXP_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionGetGlobalParameters  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicFBCstAdaptionGetGlobalParameters
	#define EXT_SysGraphicFBCstAdaptionGetGlobalParameters
	#define GET_SysGraphicFBCstAdaptionGetGlobalParameters(fl)  CAL_CMGETAPI( "SysGraphicFBCstAdaptionGetGlobalParameters" ) 
	#define CAL_SysGraphicFBCstAdaptionGetGlobalParameters pISysGraphicFBCstAdaption->ISysGraphicFBCstAdaptionGetGlobalParameters
	#define CHK_SysGraphicFBCstAdaptionGetGlobalParameters (pISysGraphicFBCstAdaption != NULL)
	#define EXP_SysGraphicFBCstAdaptionGetGlobalParameters  CAL_CMEXPAPI( "SysGraphicFBCstAdaptionGetGlobalParameters" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicFBCstAdaptionGetGlobalParameters  PFSYSGRAPHICFBCSTADAPTIONGETGLOBALPARAMETERS pfSysGraphicFBCstAdaptionGetGlobalParameters;
	#define EXT_SysGraphicFBCstAdaptionGetGlobalParameters  extern PFSYSGRAPHICFBCSTADAPTIONGETGLOBALPARAMETERS pfSysGraphicFBCstAdaptionGetGlobalParameters;
	#define GET_SysGraphicFBCstAdaptionGetGlobalParameters(fl)  s_pfCMGetAPI2( "SysGraphicFBCstAdaptionGetGlobalParameters", (RTS_VOID_FCTPTR *)&pfSysGraphicFBCstAdaptionGetGlobalParameters, (fl), 0, 0)
	#define CAL_SysGraphicFBCstAdaptionGetGlobalParameters  pfSysGraphicFBCstAdaptionGetGlobalParameters
	#define CHK_SysGraphicFBCstAdaptionGetGlobalParameters  (pfSysGraphicFBCstAdaptionGetGlobalParameters != NULL)
	#define EXP_SysGraphicFBCstAdaptionGetGlobalParameters  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicFBCstAdaptionGetGlobalParameters", (RTS_UINTPTR)SysGraphicFBCstAdaptionGetGlobalParameters, 0, 0) 
#endif




/**
 * <description> 
 * 
 * </description>
 * <result>ERR_OK</result>
 */
RTS_RESULT CDECL SysGraphicFBCstAdaptionBufferWasUpdated(char* pcFBAddress);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICFBCSTADAPTIONBUFFERWASUPDATED) (char* pcFBAddress);
#if defined(SYSGRAPHICFBCSTADAPTION_NOTIMPLEMENTED) || defined(SYSGRAPHICFBCSTADAPTIONBUFFERWASUPDATED_NOTIMPLEMENTED)
	#define USE_SysGraphicFBCstAdaptionBufferWasUpdated
	#define EXT_SysGraphicFBCstAdaptionBufferWasUpdated
	#define GET_SysGraphicFBCstAdaptionBufferWasUpdated(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicFBCstAdaptionBufferWasUpdated(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicFBCstAdaptionBufferWasUpdated  FALSE
	#define EXP_SysGraphicFBCstAdaptionBufferWasUpdated  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicFBCstAdaptionBufferWasUpdated
	#define EXT_SysGraphicFBCstAdaptionBufferWasUpdated
	#define GET_SysGraphicFBCstAdaptionBufferWasUpdated(fl)  CAL_CMGETAPI( "SysGraphicFBCstAdaptionBufferWasUpdated" ) 
	#define CAL_SysGraphicFBCstAdaptionBufferWasUpdated  SysGraphicFBCstAdaptionBufferWasUpdated
	#define CHK_SysGraphicFBCstAdaptionBufferWasUpdated  TRUE
	#define EXP_SysGraphicFBCstAdaptionBufferWasUpdated  CAL_CMEXPAPI( "SysGraphicFBCstAdaptionBufferWasUpdated" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICFBCSTADAPTION_EXTERNAL)
	#define USE_SysGraphicFBCstAdaptionBufferWasUpdated
	#define EXT_SysGraphicFBCstAdaptionBufferWasUpdated
	#define GET_SysGraphicFBCstAdaptionBufferWasUpdated(fl)  CAL_CMGETAPI( "SysGraphicFBCstAdaptionBufferWasUpdated" ) 
	#define CAL_SysGraphicFBCstAdaptionBufferWasUpdated  SysGraphicFBCstAdaptionBufferWasUpdated
	#define CHK_SysGraphicFBCstAdaptionBufferWasUpdated  TRUE
	#define EXP_SysGraphicFBCstAdaptionBufferWasUpdated  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicFBCstAdaptionBufferWasUpdated", (RTS_UINTPTR)SysGraphicFBCstAdaptionBufferWasUpdated, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionBufferWasUpdated
	#define EXT_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionBufferWasUpdated
	#define GET_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionBufferWasUpdated  ERR_OK
	#define CAL_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionBufferWasUpdated pISysGraphicFBCstAdaption->ISysGraphicFBCstAdaptionBufferWasUpdated
	#define CHK_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionBufferWasUpdated (pISysGraphicFBCstAdaption != NULL)
	#define EXP_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionBufferWasUpdated  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicFBCstAdaptionBufferWasUpdated
	#define EXT_SysGraphicFBCstAdaptionBufferWasUpdated
	#define GET_SysGraphicFBCstAdaptionBufferWasUpdated(fl)  CAL_CMGETAPI( "SysGraphicFBCstAdaptionBufferWasUpdated" ) 
	#define CAL_SysGraphicFBCstAdaptionBufferWasUpdated pISysGraphicFBCstAdaption->ISysGraphicFBCstAdaptionBufferWasUpdated
	#define CHK_SysGraphicFBCstAdaptionBufferWasUpdated (pISysGraphicFBCstAdaption != NULL)
	#define EXP_SysGraphicFBCstAdaptionBufferWasUpdated  CAL_CMEXPAPI( "SysGraphicFBCstAdaptionBufferWasUpdated" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicFBCstAdaptionBufferWasUpdated  PFSYSGRAPHICFBCSTADAPTIONBUFFERWASUPDATED pfSysGraphicFBCstAdaptionBufferWasUpdated;
	#define EXT_SysGraphicFBCstAdaptionBufferWasUpdated  extern PFSYSGRAPHICFBCSTADAPTIONBUFFERWASUPDATED pfSysGraphicFBCstAdaptionBufferWasUpdated;
	#define GET_SysGraphicFBCstAdaptionBufferWasUpdated(fl)  s_pfCMGetAPI2( "SysGraphicFBCstAdaptionBufferWasUpdated", (RTS_VOID_FCTPTR *)&pfSysGraphicFBCstAdaptionBufferWasUpdated, (fl), 0, 0)
	#define CAL_SysGraphicFBCstAdaptionBufferWasUpdated  pfSysGraphicFBCstAdaptionBufferWasUpdated
	#define CHK_SysGraphicFBCstAdaptionBufferWasUpdated  (pfSysGraphicFBCstAdaptionBufferWasUpdated != NULL)
	#define EXP_SysGraphicFBCstAdaptionBufferWasUpdated  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicFBCstAdaptionBufferWasUpdated", (RTS_UINTPTR)SysGraphicFBCstAdaptionBufferWasUpdated, 0, 0) 
#endif




/**
 * <description> 
 * 
 * </description>
 * <result>ERR_OK</result>
 */
char* CDECL SysGraphicFBCstAdaptionGetFBAddress(char* pcFBAddress);
typedef char* (CDECL * PFSYSGRAPHICFBCSTADAPTIONGETFBADDRESS) (char* pcFBAddress);
#if defined(SYSGRAPHICFBCSTADAPTION_NOTIMPLEMENTED) || defined(SYSGRAPHICFBCSTADAPTIONGETFBADDRESS_NOTIMPLEMENTED)
	#define USE_SysGraphicFBCstAdaptionGetFBAddress
	#define EXT_SysGraphicFBCstAdaptionGetFBAddress
	#define GET_SysGraphicFBCstAdaptionGetFBAddress(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicFBCstAdaptionGetFBAddress(p0)  (char*)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicFBCstAdaptionGetFBAddress  FALSE
	#define EXP_SysGraphicFBCstAdaptionGetFBAddress  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicFBCstAdaptionGetFBAddress
	#define EXT_SysGraphicFBCstAdaptionGetFBAddress
	#define GET_SysGraphicFBCstAdaptionGetFBAddress(fl)  CAL_CMGETAPI( "SysGraphicFBCstAdaptionGetFBAddress" ) 
	#define CAL_SysGraphicFBCstAdaptionGetFBAddress  SysGraphicFBCstAdaptionGetFBAddress
	#define CHK_SysGraphicFBCstAdaptionGetFBAddress  TRUE
	#define EXP_SysGraphicFBCstAdaptionGetFBAddress  CAL_CMEXPAPI( "SysGraphicFBCstAdaptionGetFBAddress" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICFBCSTADAPTION_EXTERNAL)
	#define USE_SysGraphicFBCstAdaptionGetFBAddress
	#define EXT_SysGraphicFBCstAdaptionGetFBAddress
	#define GET_SysGraphicFBCstAdaptionGetFBAddress(fl)  CAL_CMGETAPI( "SysGraphicFBCstAdaptionGetFBAddress" ) 
	#define CAL_SysGraphicFBCstAdaptionGetFBAddress  SysGraphicFBCstAdaptionGetFBAddress
	#define CHK_SysGraphicFBCstAdaptionGetFBAddress  TRUE
	#define EXP_SysGraphicFBCstAdaptionGetFBAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicFBCstAdaptionGetFBAddress", (RTS_UINTPTR)SysGraphicFBCstAdaptionGetFBAddress, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionGetFBAddress
	#define EXT_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionGetFBAddress
	#define GET_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionGetFBAddress  ERR_OK
	#define CAL_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionGetFBAddress pISysGraphicFBCstAdaption->ISysGraphicFBCstAdaptionGetFBAddress
	#define CHK_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionGetFBAddress (pISysGraphicFBCstAdaption != NULL)
	#define EXP_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionGetFBAddress  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicFBCstAdaptionGetFBAddress
	#define EXT_SysGraphicFBCstAdaptionGetFBAddress
	#define GET_SysGraphicFBCstAdaptionGetFBAddress(fl)  CAL_CMGETAPI( "SysGraphicFBCstAdaptionGetFBAddress" ) 
	#define CAL_SysGraphicFBCstAdaptionGetFBAddress pISysGraphicFBCstAdaption->ISysGraphicFBCstAdaptionGetFBAddress
	#define CHK_SysGraphicFBCstAdaptionGetFBAddress (pISysGraphicFBCstAdaption != NULL)
	#define EXP_SysGraphicFBCstAdaptionGetFBAddress  CAL_CMEXPAPI( "SysGraphicFBCstAdaptionGetFBAddress" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicFBCstAdaptionGetFBAddress  PFSYSGRAPHICFBCSTADAPTIONGETFBADDRESS pfSysGraphicFBCstAdaptionGetFBAddress;
	#define EXT_SysGraphicFBCstAdaptionGetFBAddress  extern PFSYSGRAPHICFBCSTADAPTIONGETFBADDRESS pfSysGraphicFBCstAdaptionGetFBAddress;
	#define GET_SysGraphicFBCstAdaptionGetFBAddress(fl)  s_pfCMGetAPI2( "SysGraphicFBCstAdaptionGetFBAddress", (RTS_VOID_FCTPTR *)&pfSysGraphicFBCstAdaptionGetFBAddress, (fl), 0, 0)
	#define CAL_SysGraphicFBCstAdaptionGetFBAddress  pfSysGraphicFBCstAdaptionGetFBAddress
	#define CHK_SysGraphicFBCstAdaptionGetFBAddress  (pfSysGraphicFBCstAdaptionGetFBAddress != NULL)
	#define EXP_SysGraphicFBCstAdaptionGetFBAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicFBCstAdaptionGetFBAddress", (RTS_UINTPTR)SysGraphicFBCstAdaptionGetFBAddress, 0, 0) 
#endif




/**
 * <description> 
 * 
 * </description>
 * <result>ERR_OK</result>
 */
RTS_RESULT CDECL SysGraphicFBCstAdaptionGetTouchPosition(int* iX, int* iY, int* bPressed);
typedef RTS_RESULT (CDECL * PFSYSGRAPHICFBCSTADAPTIONGETTOUCHPOSITION) (int* iX, int* iY, int* bPressed);
#if defined(SYSGRAPHICFBCSTADAPTION_NOTIMPLEMENTED) || defined(SYSGRAPHICFBCSTADAPTIONGETTOUCHPOSITION_NOTIMPLEMENTED)
	#define USE_SysGraphicFBCstAdaptionGetTouchPosition
	#define EXT_SysGraphicFBCstAdaptionGetTouchPosition
	#define GET_SysGraphicFBCstAdaptionGetTouchPosition(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGraphicFBCstAdaptionGetTouchPosition(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysGraphicFBCstAdaptionGetTouchPosition  FALSE
	#define EXP_SysGraphicFBCstAdaptionGetTouchPosition  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGraphicFBCstAdaptionGetTouchPosition
	#define EXT_SysGraphicFBCstAdaptionGetTouchPosition
	#define GET_SysGraphicFBCstAdaptionGetTouchPosition(fl)  CAL_CMGETAPI( "SysGraphicFBCstAdaptionGetTouchPosition" ) 
	#define CAL_SysGraphicFBCstAdaptionGetTouchPosition  SysGraphicFBCstAdaptionGetTouchPosition
	#define CHK_SysGraphicFBCstAdaptionGetTouchPosition  TRUE
	#define EXP_SysGraphicFBCstAdaptionGetTouchPosition  CAL_CMEXPAPI( "SysGraphicFBCstAdaptionGetTouchPosition" ) 
#elif defined(MIXED_LINK) && !defined(SYSGRAPHICFBCSTADAPTION_EXTERNAL)
	#define USE_SysGraphicFBCstAdaptionGetTouchPosition
	#define EXT_SysGraphicFBCstAdaptionGetTouchPosition
	#define GET_SysGraphicFBCstAdaptionGetTouchPosition(fl)  CAL_CMGETAPI( "SysGraphicFBCstAdaptionGetTouchPosition" ) 
	#define CAL_SysGraphicFBCstAdaptionGetTouchPosition  SysGraphicFBCstAdaptionGetTouchPosition
	#define CHK_SysGraphicFBCstAdaptionGetTouchPosition  TRUE
	#define EXP_SysGraphicFBCstAdaptionGetTouchPosition  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicFBCstAdaptionGetTouchPosition", (RTS_UINTPTR)SysGraphicFBCstAdaptionGetTouchPosition, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionGetTouchPosition
	#define EXT_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionGetTouchPosition
	#define GET_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionGetTouchPosition  ERR_OK
	#define CAL_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionGetTouchPosition pISysGraphicFBCstAdaption->ISysGraphicFBCstAdaptionGetTouchPosition
	#define CHK_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionGetTouchPosition (pISysGraphicFBCstAdaption != NULL)
	#define EXP_SysGraphicFBCstAdaptionSysGraphicFBCstAdaptionGetTouchPosition  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGraphicFBCstAdaptionGetTouchPosition
	#define EXT_SysGraphicFBCstAdaptionGetTouchPosition
	#define GET_SysGraphicFBCstAdaptionGetTouchPosition(fl)  CAL_CMGETAPI( "SysGraphicFBCstAdaptionGetTouchPosition" ) 
	#define CAL_SysGraphicFBCstAdaptionGetTouchPosition pISysGraphicFBCstAdaption->ISysGraphicFBCstAdaptionGetTouchPosition
	#define CHK_SysGraphicFBCstAdaptionGetTouchPosition (pISysGraphicFBCstAdaption != NULL)
	#define EXP_SysGraphicFBCstAdaptionGetTouchPosition  CAL_CMEXPAPI( "SysGraphicFBCstAdaptionGetTouchPosition" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGraphicFBCstAdaptionGetTouchPosition  PFSYSGRAPHICFBCSTADAPTIONGETTOUCHPOSITION pfSysGraphicFBCstAdaptionGetTouchPosition;
	#define EXT_SysGraphicFBCstAdaptionGetTouchPosition  extern PFSYSGRAPHICFBCSTADAPTIONGETTOUCHPOSITION pfSysGraphicFBCstAdaptionGetTouchPosition;
	#define GET_SysGraphicFBCstAdaptionGetTouchPosition(fl)  s_pfCMGetAPI2( "SysGraphicFBCstAdaptionGetTouchPosition", (RTS_VOID_FCTPTR *)&pfSysGraphicFBCstAdaptionGetTouchPosition, (fl), 0, 0)
	#define CAL_SysGraphicFBCstAdaptionGetTouchPosition  pfSysGraphicFBCstAdaptionGetTouchPosition
	#define CHK_SysGraphicFBCstAdaptionGetTouchPosition  (pfSysGraphicFBCstAdaptionGetTouchPosition != NULL)
	#define EXP_SysGraphicFBCstAdaptionGetTouchPosition  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGraphicFBCstAdaptionGetTouchPosition", (RTS_UINTPTR)SysGraphicFBCstAdaptionGetTouchPosition, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSGRAPHICFBCSTADAPTIONGETGLOBALPARAMETERS ISysGraphicFBCstAdaptionGetGlobalParameters;
 	PFSYSGRAPHICFBCSTADAPTIONBUFFERWASUPDATED ISysGraphicFBCstAdaptionBufferWasUpdated;
 	PFSYSGRAPHICFBCSTADAPTIONGETFBADDRESS ISysGraphicFBCstAdaptionGetFBAddress;
 	PFSYSGRAPHICFBCSTADAPTIONGETTOUCHPOSITION ISysGraphicFBCstAdaptionGetTouchPosition;
 } ISysGraphicFBCstAdaption_C;

#ifdef CPLUSPLUS
class ISysGraphicFBCstAdaption : public IBase
{
	public:
		virtual RTS_RESULT CDECL ISysGraphicFBCstAdaptionGetGlobalParameters(SysGraphicGlobalParameters* pParameters) =0;
		virtual RTS_RESULT CDECL ISysGraphicFBCstAdaptionBufferWasUpdated(char* pcFBAddress) =0;
		virtual char* CDECL ISysGraphicFBCstAdaptionGetFBAddress(char* pcFBAddress) =0;
		virtual RTS_RESULT CDECL ISysGraphicFBCstAdaptionGetTouchPosition(int* iX, int* iY, int* bPressed) =0;
};
	#ifndef ITF_SysGraphicFBCstAdaption
		#define ITF_SysGraphicFBCstAdaption static ISysGraphicFBCstAdaption *pISysGraphicFBCstAdaption = NULL;
	#endif
	#define EXTITF_SysGraphicFBCstAdaption
#else	/*CPLUSPLUS*/
	typedef ISysGraphicFBCstAdaption_C		ISysGraphicFBCstAdaption;
	#ifndef ITF_SysGraphicFBCstAdaption
		#define ITF_SysGraphicFBCstAdaption
	#endif
	#define EXTITF_SysGraphicFBCstAdaption
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSGRAPHICFBCSTADAPTIONITF_H_*/
