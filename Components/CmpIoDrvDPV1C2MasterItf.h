 /**
 * <interfacename>CmpIoDrvDPV1C2Master</interfacename>
 * <description> 
 *	Interface of a profibus IO-driver for the DPV1 Class 2 Master interface.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPIODRVDPV1C2MASTERITF_H_
#define _CMPIODRVDPV1C2MASTERITF_H_

#include "CmpStd.h"

 

 




#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>DPV1_C2_Abort</description>
 */
typedef struct tagDPV1_C2_Abort
{
	RTS_IEC_BOOL bEnable;
	RTS_IEC_BYTE byStationAddress;
	RTS_IEC_BYTE byDummy[2];
	RTS_IEC_UDINT udiConnectID;
	RTS_IEC_UDINT C_Ref;
	RTS_IEC_BYTE abyError[4];
	RTS_IEC_WORD wOpState;
	RTS_IEC_BOOL bOldEnable;
	RTS_IEC_UDINT udiId;
} DPV1_C2_Abort;

/**
 * <description>DPV1_C2_Read</description>
 */
typedef struct tagDPV1_C2_Read
{
	RTS_IEC_BOOL bEnable;
	RTS_IEC_BYTE byStationAddress;
	RTS_IEC_BYTE bySlotNr;
	RTS_IEC_BYTE byIndex;
	RTS_IEC_UDINT udiConnectID;
	RTS_IEC_UDINT C_Ref;
	RTS_IEC_WORD wLen;
	RTS_IEC_BYTE byDummy[2];
	RTS_IEC_BYTE *pBuffer;
	RTS_IEC_BYTE abyError[4];
	RTS_IEC_WORD wOpState;
	RTS_IEC_BOOL bOldEnable;
	RTS_IEC_UDINT udiId;
} DPV1_C2_Read;

/**
 * <description>DPV1_C2_Initiate</description>
 */
typedef struct tagDPV1_C2_Initiate
{
	RTS_IEC_BOOL bEnable;
	RTS_IEC_BYTE byStationAddress;
	RTS_IEC_BYTE byDummy[2];
	RTS_IEC_DWORD dwSendTimeoutMs;
	RTS_IEC_UDINT C_Ref;
	RTS_IEC_BYTE Res_SAP;
	RTS_IEC_WORD wOpState;
	RTS_IEC_BYTE abyError[4];
	RTS_IEC_UDINT udiConnectID;
	RTS_IEC_BOOL bOldEnable;
	RTS_IEC_UDINT udiId;
} DPV1_C2_Initiate;

/**
 * <description>DPV1_C2_Write</description>
 */
typedef struct tagDPV1_C2_Write
{
	RTS_IEC_BOOL bEnable;
	RTS_IEC_BYTE byStationAddress;
	RTS_IEC_BYTE bySlotNr;
	RTS_IEC_BYTE byIndex;
	RTS_IEC_UDINT udiConnectID;
	RTS_IEC_UDINT C_Ref;
	RTS_IEC_WORD wLen;
	RTS_IEC_BYTE byDummy[2];
	RTS_IEC_BYTE *pBuffer;
	RTS_IEC_BYTE abyError[4];
	RTS_IEC_WORD wOpState;
	RTS_IEC_BOOL bOldEnable;
	RTS_IEC_UDINT udiId;
} DPV1_C2_Write;

typedef struct
{
	ieciodrvinstance_struct *pInstance;
	DPV1_C2_Initiate *pInit;
	RTS_IEC_UDINT Result;
} iodrvdpv1_c2_m_initiate_struct;

typedef struct
{
	ieciodrvinstance_struct *pInstance;
	DPV1_C2_Abort *pInit;
	RTS_IEC_UDINT Result;
} iodrvdpv1_c2_m_abort_struct;

typedef struct
{
	ieciodrvinstance_struct *pInstance;
	DPV1_C2_Read *pInit;
	RTS_IEC_UDINT Result;
} iodrvdpv1_c2_m_read_struct;

typedef struct
{
	ieciodrvinstance_struct *pInstance;
	DPV1_C2_Write *pInit;
	RTS_IEC_UDINT Result;
} iodrvdpv1_c2_m_write_struct;

#ifdef __cplusplus
}
#endif

/**
 * <description></description>
 * <result>ERR_OK</result>
 */
STATICITF_DEF RTS_RESULT CDECL IoDrvDPV1_C2_M_Initiate(RTS_HANDLE hIoDrv, DPV1_C2_Initiate *pInit);
typedef RTS_RESULT (CDECL * PFIODRVDPV1_C2_M_INITIATE) (RTS_HANDLE hIoDrv, DPV1_C2_Initiate *pInit);
#if defined(CMPIODRVDPV1C2MASTER_NOTIMPLEMENTED) || defined(IODRVDPV1_C2_M_INITIATE_NOTIMPLEMENTED)
	#define USE_IoDrvDPV1_C2_M_Initiate
	#define EXT_IoDrvDPV1_C2_M_Initiate
	#define GET_IoDrvDPV1_C2_M_Initiate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvDPV1_C2_M_Initiate(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvDPV1_C2_M_Initiate  FALSE
	#define EXP_IoDrvDPV1_C2_M_Initiate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvDPV1_C2_M_Initiate
	#define EXT_IoDrvDPV1_C2_M_Initiate
	#define GET_IoDrvDPV1_C2_M_Initiate(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C2_M_Initiate(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C2Master*)p0)->IIoDrvDPV1_C2_M_Initiate(((ICmpIoDrvDPV1C2Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C2_M_Initiate  TRUE
	#define EXP_IoDrvDPV1_C2_M_Initiate  ERR_OK
#elif defined(MIXED_LINK) && !defined(CMPIODRVDPV1C2MASTER_EXTERNAL)
	#define USE_IoDrvDPV1_C2_M_Initiate
	#define EXT_IoDrvDPV1_C2_M_Initiate
	#define GET_IoDrvDPV1_C2_M_Initiate(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C2_M_Initiate(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C2Master*)p0)->IIoDrvDPV1_C2_M_Initiate(((ICmpIoDrvDPV1C2Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C2_M_Initiate  TRUE
	#define EXP_IoDrvDPV1_C2_M_Initiate  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Initiate
	#define EXT_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Initiate
	#define GET_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Initiate  ERR_OK
	#define CAL_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Initiate(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C2Master*)p0)->IIoDrvDPV1_C2_M_Initiate(p1))
	#define CHK_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Initiate  TRUE
	#define EXP_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Initiate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvDPV1_C2_M_Initiate
	#define EXT_IoDrvDPV1_C2_M_Initiate
	#define GET_IoDrvDPV1_C2_M_Initiate(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C2_M_Initiate(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C2Master*)p0)->IIoDrvDPV1_C2_M_Initiate(p1))
	#define CHK_IoDrvDPV1_C2_M_Initiate  TRUE
	#define EXP_IoDrvDPV1_C2_M_Initiate  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvDPV1_C2_M_Initiate
	#define EXT_IoDrvDPV1_C2_M_Initiate
	#define GET_IoDrvDPV1_C2_M_Initiate(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C2_M_Initiate(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C2Master*)p0)->IIoDrvDPV1_C2_M_Initiate(((ICmpIoDrvDPV1C2Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C2_M_Initiate  TRUE
	#define EXP_IoDrvDPV1_C2_M_Initiate  ERR_OK
#endif



STATICITF_DEF RTS_RESULT CDECL IoDrvDPV1_C2_M_Abort(RTS_HANDLE hIoDrv, DPV1_C2_Abort *pAbort);
typedef RTS_RESULT (CDECL * PFIODRVDPV1_C2_M_ABORT) (RTS_HANDLE hIoDrv, DPV1_C2_Abort *pAbort);
#if defined(CMPIODRVDPV1C2MASTER_NOTIMPLEMENTED) || defined(IODRVDPV1_C2_M_ABORT_NOTIMPLEMENTED)
	#define USE_IoDrvDPV1_C2_M_Abort
	#define EXT_IoDrvDPV1_C2_M_Abort
	#define GET_IoDrvDPV1_C2_M_Abort(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvDPV1_C2_M_Abort(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvDPV1_C2_M_Abort  FALSE
	#define EXP_IoDrvDPV1_C2_M_Abort  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvDPV1_C2_M_Abort
	#define EXT_IoDrvDPV1_C2_M_Abort
	#define GET_IoDrvDPV1_C2_M_Abort(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C2_M_Abort(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C2Master*)p0)->IIoDrvDPV1_C2_M_Abort(((ICmpIoDrvDPV1C2Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C2_M_Abort  TRUE
	#define EXP_IoDrvDPV1_C2_M_Abort  ERR_OK
#elif defined(MIXED_LINK) && !defined(CMPIODRVDPV1C2MASTER_EXTERNAL)
	#define USE_IoDrvDPV1_C2_M_Abort
	#define EXT_IoDrvDPV1_C2_M_Abort
	#define GET_IoDrvDPV1_C2_M_Abort(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C2_M_Abort(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C2Master*)p0)->IIoDrvDPV1_C2_M_Abort(((ICmpIoDrvDPV1C2Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C2_M_Abort  TRUE
	#define EXP_IoDrvDPV1_C2_M_Abort  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Abort
	#define EXT_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Abort
	#define GET_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Abort  ERR_OK
	#define CAL_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Abort(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C2Master*)p0)->IIoDrvDPV1_C2_M_Abort(p1))
	#define CHK_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Abort  TRUE
	#define EXP_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Abort  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvDPV1_C2_M_Abort
	#define EXT_IoDrvDPV1_C2_M_Abort
	#define GET_IoDrvDPV1_C2_M_Abort(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C2_M_Abort(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C2Master*)p0)->IIoDrvDPV1_C2_M_Abort(p1))
	#define CHK_IoDrvDPV1_C2_M_Abort  TRUE
	#define EXP_IoDrvDPV1_C2_M_Abort  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvDPV1_C2_M_Abort
	#define EXT_IoDrvDPV1_C2_M_Abort
	#define GET_IoDrvDPV1_C2_M_Abort(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C2_M_Abort(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C2Master*)p0)->IIoDrvDPV1_C2_M_Abort(((ICmpIoDrvDPV1C2Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C2_M_Abort  TRUE
	#define EXP_IoDrvDPV1_C2_M_Abort  ERR_OK
#endif



STATICITF_DEF RTS_RESULT CDECL IoDrvDPV1_C2_M_Read(RTS_HANDLE hIoDrv, DPV1_C2_Read *pRead);
typedef RTS_RESULT (CDECL * PFIODRVDPV1_C2_M_READ) (RTS_HANDLE hIoDrv, DPV1_C2_Read *pRead);
#if defined(CMPIODRVDPV1C2MASTER_NOTIMPLEMENTED) || defined(IODRVDPV1_C2_M_READ_NOTIMPLEMENTED)
	#define USE_IoDrvDPV1_C2_M_Read
	#define EXT_IoDrvDPV1_C2_M_Read
	#define GET_IoDrvDPV1_C2_M_Read(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvDPV1_C2_M_Read(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvDPV1_C2_M_Read  FALSE
	#define EXP_IoDrvDPV1_C2_M_Read  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvDPV1_C2_M_Read
	#define EXT_IoDrvDPV1_C2_M_Read
	#define GET_IoDrvDPV1_C2_M_Read(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C2_M_Read(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C2Master*)p0)->IIoDrvDPV1_C2_M_Read(((ICmpIoDrvDPV1C2Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C2_M_Read  TRUE
	#define EXP_IoDrvDPV1_C2_M_Read  ERR_OK
#elif defined(MIXED_LINK) && !defined(CMPIODRVDPV1C2MASTER_EXTERNAL)
	#define USE_IoDrvDPV1_C2_M_Read
	#define EXT_IoDrvDPV1_C2_M_Read
	#define GET_IoDrvDPV1_C2_M_Read(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C2_M_Read(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C2Master*)p0)->IIoDrvDPV1_C2_M_Read(((ICmpIoDrvDPV1C2Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C2_M_Read  TRUE
	#define EXP_IoDrvDPV1_C2_M_Read  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Read
	#define EXT_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Read
	#define GET_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Read  ERR_OK
	#define CAL_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Read(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C2Master*)p0)->IIoDrvDPV1_C2_M_Read(p1))
	#define CHK_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Read  TRUE
	#define EXP_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Read  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvDPV1_C2_M_Read
	#define EXT_IoDrvDPV1_C2_M_Read
	#define GET_IoDrvDPV1_C2_M_Read(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C2_M_Read(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C2Master*)p0)->IIoDrvDPV1_C2_M_Read(p1))
	#define CHK_IoDrvDPV1_C2_M_Read  TRUE
	#define EXP_IoDrvDPV1_C2_M_Read  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvDPV1_C2_M_Read
	#define EXT_IoDrvDPV1_C2_M_Read
	#define GET_IoDrvDPV1_C2_M_Read(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C2_M_Read(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C2Master*)p0)->IIoDrvDPV1_C2_M_Read(((ICmpIoDrvDPV1C2Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C2_M_Read  TRUE
	#define EXP_IoDrvDPV1_C2_M_Read  ERR_OK
#endif



STATICITF_DEF RTS_RESULT CDECL IoDrvDPV1_C2_M_Write(RTS_HANDLE hIoDrv, DPV1_C2_Write *pWrite);
typedef RTS_RESULT (CDECL * PFIODRVDPV1_C2_M_WRITE) (RTS_HANDLE hIoDrv, DPV1_C2_Write *pWrite);
#if defined(CMPIODRVDPV1C2MASTER_NOTIMPLEMENTED) || defined(IODRVDPV1_C2_M_WRITE_NOTIMPLEMENTED)
	#define USE_IoDrvDPV1_C2_M_Write
	#define EXT_IoDrvDPV1_C2_M_Write
	#define GET_IoDrvDPV1_C2_M_Write(fl)  ERR_NOTIMPLEMENTED
	#define CAL_IoDrvDPV1_C2_M_Write(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_IoDrvDPV1_C2_M_Write  FALSE
	#define EXP_IoDrvDPV1_C2_M_Write  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_IoDrvDPV1_C2_M_Write
	#define EXT_IoDrvDPV1_C2_M_Write
	#define GET_IoDrvDPV1_C2_M_Write(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C2_M_Write(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C2Master*)p0)->IIoDrvDPV1_C2_M_Write(((ICmpIoDrvDPV1C2Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C2_M_Write  TRUE
	#define EXP_IoDrvDPV1_C2_M_Write  ERR_OK
#elif defined(MIXED_LINK) && !defined(CMPIODRVDPV1C2MASTER_EXTERNAL)
	#define USE_IoDrvDPV1_C2_M_Write
	#define EXT_IoDrvDPV1_C2_M_Write
	#define GET_IoDrvDPV1_C2_M_Write(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C2_M_Write(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C2Master*)p0)->IIoDrvDPV1_C2_M_Write(((ICmpIoDrvDPV1C2Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C2_M_Write  TRUE
	#define EXP_IoDrvDPV1_C2_M_Write  ERR_OK
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Write
	#define EXT_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Write
	#define GET_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Write  ERR_OK
	#define CAL_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Write(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C2Master*)p0)->IIoDrvDPV1_C2_M_Write(p1))
	#define CHK_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Write  TRUE
	#define EXP_CmpIoDrvDPV1C2MasterIoDrvDPV1_C2_M_Write  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_IoDrvDPV1_C2_M_Write
	#define EXT_IoDrvDPV1_C2_M_Write
	#define GET_IoDrvDPV1_C2_M_Write(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C2_M_Write(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C2Master*)p0)->IIoDrvDPV1_C2_M_Write(p1))
	#define CHK_IoDrvDPV1_C2_M_Write  TRUE
	#define EXP_IoDrvDPV1_C2_M_Write  ERR_OK
#else /* DYNAMIC_LINK */
	#define USE_IoDrvDPV1_C2_M_Write
	#define EXT_IoDrvDPV1_C2_M_Write
	#define GET_IoDrvDPV1_C2_M_Write(fl)  ERR_OK
	#define CAL_IoDrvDPV1_C2_M_Write(p0,p1) (p0 == RTS_INVALID_HANDLE || p0 == NULL ? (RTS_RESULT)ERR_PARAMETER : ((ICmpIoDrvDPV1C2Master*)p0)->IIoDrvDPV1_C2_M_Write(((ICmpIoDrvDPV1C2Master*)p0)->pBase->hInstance,p1))
	#define CHK_IoDrvDPV1_C2_M_Write  TRUE
	#define EXP_IoDrvDPV1_C2_M_Write  ERR_OK
#endif







typedef struct
{
	IBase_C *pBase;
	PFIODRVDPV1_C2_M_INITIATE IIoDrvDPV1_C2_M_Initiate;
 	PFIODRVDPV1_C2_M_ABORT IIoDrvDPV1_C2_M_Abort;
 	PFIODRVDPV1_C2_M_READ IIoDrvDPV1_C2_M_Read;
 	PFIODRVDPV1_C2_M_WRITE IIoDrvDPV1_C2_M_Write;
 } ICmpIoDrvDPV1C2Master_C;

#ifdef CPLUSPLUS
class ICmpIoDrvDPV1C2Master : public IBase
{
	public:
		virtual RTS_RESULT CDECL IIoDrvDPV1_C2_M_Initiate(DPV1_C2_Initiate *pInit) =0;
		virtual RTS_RESULT CDECL IIoDrvDPV1_C2_M_Abort(DPV1_C2_Abort *pAbort) =0;
		virtual RTS_RESULT CDECL IIoDrvDPV1_C2_M_Read(DPV1_C2_Read *pRead) =0;
		virtual RTS_RESULT CDECL IIoDrvDPV1_C2_M_Write(DPV1_C2_Write *pWrite) =0;
};
	#ifndef ITF_CmpIoDrvDPV1C2Master
		#define ITF_CmpIoDrvDPV1C2Master static ICmpIoDrvDPV1C2Master *pICmpIoDrvDPV1C2Master = NULL;
	#endif
	#define EXTITF_CmpIoDrvDPV1C2Master
#else	/*CPLUSPLUS*/
	typedef ICmpIoDrvDPV1C2Master_C		ICmpIoDrvDPV1C2Master;
	#ifndef ITF_CmpIoDrvDPV1C2Master
		#define ITF_CmpIoDrvDPV1C2Master
	#endif
	#define EXTITF_CmpIoDrvDPV1C2Master
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPIODRVDPV1C2MASTERITF_H_*/
