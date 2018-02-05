 /**
 * <interfacename>CmpIoDrvProfinet</interfacename>
 * <description> 
 *	Interface to get access to a ProfiNet IO-driver.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPIODRVPROFINETITF_H_
#define _CMPIODRVPROFINETITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"

#include "CmpIoMgrItf.h"
#include "CmpIoDrvItf.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	ieciodrvinstance_struct *pInstance;
	IoConfigConnector *pConnector;
	RTS_IEC_UDINT Result;
} iodrvprofinet_nominate_struct;

#ifdef __cplusplus
}
#endif

/**
 * <description>  </description>
 * <result>ERR_OK</result>
 */
STATICITF_DEF RTS_RESULT CDECL IoDrvProfinet_Nominate(RTS_HANDLE hDevice, IoConfigConnector *pConnector);
typedef RTS_RESULT (CDECL * PFIODRVPROFINET_NOMINATE) (RTS_HANDLE hDevice, IoConfigConnector *pConnector);
#if defined(CMPIODRVPROFINET_NOTIMPLEMENTED) || defined(IODRVPROFINET_NOMINATE_NOTIMPLEMENTED)
	#define USE_IoDrvProfinet_Nominate
	#define EXT_IoDrvProfinet_Nominate
	#define GET_IoDrvProfinet_Nominate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvProfinet_Nominate(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvProfinet_Nominate  FALSE
	#define EXP_IoDrvProfinet_Nominate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvProfinet_Nominate
	#define EXT_IoDrvProfinet_Nominate
	#define GET_IoDrvProfinet_Nominate(fl)  ERR_OK
	#define CAL_IoDrvProfinet_Nominate(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvProfinet*)p0)->IIoDrvProfinet_Nominate(((ICmpIoDrvProfinet*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvProfinet_Nominate  TRUE
	#define EXP_IoDrvProfinet_Nominate  ERR_OK
#elif defined(MIXED_LINK) && !defined(CMPIODRVPROFINET_EXTERNAL)
	#define USE_IoDrvProfinet_Nominate
	#define EXT_IoDrvProfinet_Nominate
	#define GET_IoDrvProfinet_Nominate(fl)  ERR_OK
	#define CAL_IoDrvProfinet_Nominate(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvProfinet*)p0)->IIoDrvProfinet_Nominate(((ICmpIoDrvProfinet*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvProfinet_Nominate  TRUE
	#define EXP_IoDrvProfinet_Nominate  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvProfinetIoDrvProfinet_Nominate
	#define EXT_CmpIoDrvProfinetIoDrvProfinet_Nominate
	#define GET_CmpIoDrvProfinetIoDrvProfinet_Nominate  ERR_OK
	#define CAL_CmpIoDrvProfinetIoDrvProfinet_Nominate(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvProfinet*)p0)->IIoDrvProfinet_Nominate(p1))
	#define CHK_CmpIoDrvProfinetIoDrvProfinet_Nominate  TRUE
	#define EXP_CmpIoDrvProfinetIoDrvProfinet_Nominate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvProfinet_Nominate
	#define EXT_IoDrvProfinet_Nominate
	#define GET_IoDrvProfinet_Nominate(fl)  ERR_OK
	#define CAL_IoDrvProfinet_Nominate(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvProfinet*)p0)->IIoDrvProfinet_Nominate(p1))
	#define CHK_IoDrvProfinet_Nominate  TRUE
	#define EXP_IoDrvProfinet_Nominate  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvProfinet_Nominate
	#define EXT_IoDrvProfinet_Nominate
	#define GET_IoDrvProfinet_Nominate(fl)  ERR_OK
	#define CAL_IoDrvProfinet_Nominate(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvProfinet*)p0)->IIoDrvProfinet_Nominate(((ICmpIoDrvProfinet*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvProfinet_Nominate  TRUE
	#define EXP_IoDrvProfinet_Nominate  ERR_OK
#endif







typedef struct
{
	IBase_C *pBase;
	PFIODRVPROFINET_NOMINATE IIoDrvProfinet_Nominate;
 } ICmpIoDrvProfinet_C;

#ifdef CPLUSPLUS
class ICmpIoDrvProfinet : public IBase
{
	public:
		virtual RTS_RESULT CDECL IIoDrvProfinet_Nominate(IoConfigConnector *pConnector) =0;
};
	#ifndef ITF_CmpIoDrvProfinet
		#define ITF_CmpIoDrvProfinet static ICmpIoDrvProfinet *pICmpIoDrvProfinet = NULL;
	#endif
	#define EXTITF_CmpIoDrvProfinet
#else	/*CPLUSPLUS*/
	typedef ICmpIoDrvProfinet_C		ICmpIoDrvProfinet;
	#ifndef ITF_CmpIoDrvProfinet
		#define ITF_CmpIoDrvProfinet
	#endif
	#define EXTITF_CmpIoDrvProfinet
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPIODRVPROFINETITF_H_*/
