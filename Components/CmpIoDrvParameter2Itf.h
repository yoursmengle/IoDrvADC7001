 /**
 * <interfacename>CmpIoDrvParameter2</interfacename>
 * <description> 
 *	Interface to access parameters of an IO-driver by their parameter id
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPIODRVPARAMETER2ITF_H_
#define _CMPIODRVPARAMETER2ITF_H_

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
	RTS_IEC_DWORD ulParamId;
	RTS_IEC_BYTE *pData;
	RTS_IEC_DWORD ulBitSize;
	RTS_IEC_DWORD ulBitOffset;
	RTS_IEC_UDINT Result;
} iodrvreadparameterbyid_struct;

typedef struct
{
	ieciodrvinstance_struct *pInstance;
	IoConfigConnector *pConnector;
	RTS_IEC_DWORD ulParamId;
	RTS_IEC_BYTE *pData;
	RTS_IEC_DWORD ulBitSize;
	RTS_IEC_DWORD ulBitOffset;
	RTS_IEC_UDINT Result;
} iodrvwriteparameterbyid_struct;

#ifdef __cplusplus
}
#endif

/**
 * <description>  </description>
 * <result>ERR_OK</result>
 */
STATICITF_DEF RTS_RESULT CDECL IoDrvReadParameterById(RTS_HANDLE hDevice, IoConfigConnector *pConnector, RTS_UI32 dwParamId, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset);
typedef RTS_RESULT (CDECL * PFIODRVREADPARAMETERBYID) (RTS_HANDLE hDevice, IoConfigConnector *pConnector, RTS_UI32 dwParamId, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset);
#if defined(CMPIODRVPARAMETER2_NOTIMPLEMENTED) || defined(IODRVREADPARAMETERBYID_NOTIMPLEMENTED)
	#define USE_IoDrvReadParameterById
	#define EXT_IoDrvReadParameterById
	#define GET_IoDrvReadParameterById(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvReadParameterById(p0,p1,p2,p3,p4,p5)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvReadParameterById  FALSE
	#define EXP_IoDrvReadParameterById  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvReadParameterById
	#define EXT_IoDrvReadParameterById
	#define GET_IoDrvReadParameterById(fl)  ERR_OK
	#define CAL_IoDrvReadParameterById(p0,p1,p2,p3,p4,p5) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvParameter2*)p0)->IIoDrvReadParameterById(((ICmpIoDrvParameter2*)p0)->pBase->hInstance,p1,p2,p3,p4,p5))
	#define CHK_IoDrvReadParameterById  TRUE
	#define EXP_IoDrvReadParameterById  ERR_OK
#elif defined(MIXED_LINK) && !defined(CMPIODRVPARAMETER2_EXTERNAL)
	#define USE_IoDrvReadParameterById
	#define EXT_IoDrvReadParameterById
	#define GET_IoDrvReadParameterById(fl)  ERR_OK
	#define CAL_IoDrvReadParameterById(p0,p1,p2,p3,p4,p5) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvParameter2*)p0)->IIoDrvReadParameterById(((ICmpIoDrvParameter2*)p0)->pBase->hInstance,p1,p2,p3,p4,p5))
	#define CHK_IoDrvReadParameterById  TRUE
	#define EXP_IoDrvReadParameterById  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvParameter2IoDrvReadParameterById
	#define EXT_CmpIoDrvParameter2IoDrvReadParameterById
	#define GET_CmpIoDrvParameter2IoDrvReadParameterById  ERR_OK
	#define CAL_CmpIoDrvParameter2IoDrvReadParameterById(p0,p1,p2,p3,p4,p5)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvParameter2*)p0)->IIoDrvReadParameterById(p1,p2,p3,p4,p5))
	#define CHK_CmpIoDrvParameter2IoDrvReadParameterById  TRUE
	#define EXP_CmpIoDrvParameter2IoDrvReadParameterById  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvReadParameterById
	#define EXT_IoDrvReadParameterById
	#define GET_IoDrvReadParameterById(fl)  ERR_OK
	#define CAL_IoDrvReadParameterById(p0,p1,p2,p3,p4,p5)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvParameter2*)p0)->IIoDrvReadParameterById(p1,p2,p3,p4,p5))
	#define CHK_IoDrvReadParameterById  TRUE
	#define EXP_IoDrvReadParameterById  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvReadParameterById
	#define EXT_IoDrvReadParameterById
	#define GET_IoDrvReadParameterById(fl)  ERR_OK
	#define CAL_IoDrvReadParameterById(p0,p1,p2,p3,p4,p5) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvParameter2*)p0)->IIoDrvReadParameterById(((ICmpIoDrvParameter2*)p0)->pBase->hInstance,p1,p2,p3,p4,p5))
	#define CHK_IoDrvReadParameterById  TRUE
	#define EXP_IoDrvReadParameterById  ERR_OK
#endif



STATICITF_DEF RTS_RESULT CDECL IoDrvWriteParameterById(RTS_HANDLE hDevice, IoConfigConnector *pConnector, RTS_UI32 dwParamId, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset);
typedef RTS_RESULT (CDECL * PFIODRVWRITEPARAMETERBYID) (RTS_HANDLE hDevice, IoConfigConnector *pConnector, RTS_UI32 dwParamId, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset);
#if defined(CMPIODRVPARAMETER2_NOTIMPLEMENTED) || defined(IODRVWRITEPARAMETERBYID_NOTIMPLEMENTED)
	#define USE_IoDrvWriteParameterById
	#define EXT_IoDrvWriteParameterById
	#define GET_IoDrvWriteParameterById(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvWriteParameterById(p0,p1,p2,p3,p4,p5)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvWriteParameterById  FALSE
	#define EXP_IoDrvWriteParameterById  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvWriteParameterById
	#define EXT_IoDrvWriteParameterById
	#define GET_IoDrvWriteParameterById(fl)  ERR_OK
	#define CAL_IoDrvWriteParameterById(p0,p1,p2,p3,p4,p5) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvParameter2*)p0)->IIoDrvWriteParameterById(((ICmpIoDrvParameter2*)p0)->pBase->hInstance,p1,p2,p3,p4,p5))
	#define CHK_IoDrvWriteParameterById  TRUE
	#define EXP_IoDrvWriteParameterById  ERR_OK
#elif defined(MIXED_LINK) && !defined(CMPIODRVPARAMETER2_EXTERNAL)
	#define USE_IoDrvWriteParameterById
	#define EXT_IoDrvWriteParameterById
	#define GET_IoDrvWriteParameterById(fl)  ERR_OK
	#define CAL_IoDrvWriteParameterById(p0,p1,p2,p3,p4,p5) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvParameter2*)p0)->IIoDrvWriteParameterById(((ICmpIoDrvParameter2*)p0)->pBase->hInstance,p1,p2,p3,p4,p5))
	#define CHK_IoDrvWriteParameterById  TRUE
	#define EXP_IoDrvWriteParameterById  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvParameter2IoDrvWriteParameterById
	#define EXT_CmpIoDrvParameter2IoDrvWriteParameterById
	#define GET_CmpIoDrvParameter2IoDrvWriteParameterById  ERR_OK
	#define CAL_CmpIoDrvParameter2IoDrvWriteParameterById(p0,p1,p2,p3,p4,p5)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvParameter2*)p0)->IIoDrvWriteParameterById(p1,p2,p3,p4,p5))
	#define CHK_CmpIoDrvParameter2IoDrvWriteParameterById  TRUE
	#define EXP_CmpIoDrvParameter2IoDrvWriteParameterById  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvWriteParameterById
	#define EXT_IoDrvWriteParameterById
	#define GET_IoDrvWriteParameterById(fl)  ERR_OK
	#define CAL_IoDrvWriteParameterById(p0,p1,p2,p3,p4,p5)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvParameter2*)p0)->IIoDrvWriteParameterById(p1,p2,p3,p4,p5))
	#define CHK_IoDrvWriteParameterById  TRUE
	#define EXP_IoDrvWriteParameterById  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvWriteParameterById
	#define EXT_IoDrvWriteParameterById
	#define GET_IoDrvWriteParameterById(fl)  ERR_OK
	#define CAL_IoDrvWriteParameterById(p0,p1,p2,p3,p4,p5) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvParameter2*)p0)->IIoDrvWriteParameterById(((ICmpIoDrvParameter2*)p0)->pBase->hInstance,p1,p2,p3,p4,p5))
	#define CHK_IoDrvWriteParameterById  TRUE
	#define EXP_IoDrvWriteParameterById  ERR_OK
#endif








typedef struct
{
	IBase_C *pBase;
	PFIODRVREADPARAMETERBYID IIoDrvReadParameterById;
 	PFIODRVWRITEPARAMETERBYID IIoDrvWriteParameterById;
 } ICmpIoDrvParameter2_C;

#ifdef CPLUSPLUS
class ICmpIoDrvParameter2 : public IBase
{
	public:
		virtual RTS_RESULT CDECL IIoDrvReadParameterById(IoConfigConnector *pConnector, RTS_UI32 dwParamId, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset) =0;
		virtual RTS_RESULT CDECL IIoDrvWriteParameterById(IoConfigConnector *pConnector, RTS_UI32 dwParamId, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset) =0;
};
	#ifndef ITF_CmpIoDrvParameter2
		#define ITF_CmpIoDrvParameter2 static ICmpIoDrvParameter2 *pICmpIoDrvParameter2 = NULL;
	#endif
	#define EXTITF_CmpIoDrvParameter2
#else	/*CPLUSPLUS*/
	typedef ICmpIoDrvParameter2_C		ICmpIoDrvParameter2;
	#ifndef ITF_CmpIoDrvParameter2
		#define ITF_CmpIoDrvParameter2
	#endif
	#define EXTITF_CmpIoDrvParameter2
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPIODRVPARAMETER2ITF_H_*/
