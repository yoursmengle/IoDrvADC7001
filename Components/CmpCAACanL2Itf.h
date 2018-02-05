 
	
	
#ifndef _CMPCAACANL2ITF_H_
#define _CMPCAACANL2ITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAACanL2.h"
#include "CAACanL2I.h"
#include "CAACanMiniDriver.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Global setting for all CAN Networks. If 1 Baudrate used in DriverOpen will be saved to Net.X.DefaultBaudrate.
 * </description>
 */
#define CANL2KEY_INT_PERSISTENTBAUDRATE			"PersistentBaudrate"
#ifndef CANL2KEY_INT_PERSISTENTBAUDRATE_DEFAULT
	#define CANL2KEY_INT_PERSISTENTBAUDRATE_DEFAULT		0
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting prefix for CANL2 Networks.</description>
 */
#define CANL2_STRING_NET						"Net"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Default Baudrate in kbit/s which should be used if CAN interface will be opened with baudrate 0.
 * Example: Net.0.Baudrate = 1000
 * </description>
 */
#define CANL2KEY_INT_BAUDRATE					"DefaultBaudrate"
#ifndef CANL2KEY_INT_BAUDRATE_DEFAULT
	#define CANL2KEY_INT_BAUDRATE_DEFAULT		0
#endif


/* Basic Functions */
CAA_HANDLE CDECL CL2_DriverOpenH(unsigned char ucNetId, unsigned short usBaudrate, CAA_BOOL xSupport29Bit, CAA_COUNT ctMessages, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFCL2_DRIVEROPENH) (unsigned char ucNetId, unsigned short usBaudrate, CAA_BOOL xSupport29Bit, CAA_COUNT ctMessages, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_DRIVEROPENH_NOTIMPLEMENTED)
	#define USE_CL2_DriverOpenH
	#define EXT_CL2_DriverOpenH
	#define GET_CL2_DriverOpenH(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_DriverOpenH(p0,p1,p2,p3,p4)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_CL2_DriverOpenH  FALSE
	#define EXP_CL2_DriverOpenH  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_DriverOpenH
	#define EXT_CL2_DriverOpenH
	#define GET_CL2_DriverOpenH(fl)  CAL_CMGETAPI( "CL2_DriverOpenH" ) 
	#define CAL_CL2_DriverOpenH  CL2_DriverOpenH
	#define CHK_CL2_DriverOpenH  TRUE
	#define EXP_CL2_DriverOpenH  CAL_CMEXPAPI( "CL2_DriverOpenH" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_DriverOpenH
	#define EXT_CL2_DriverOpenH
	#define GET_CL2_DriverOpenH(fl)  CAL_CMGETAPI( "CL2_DriverOpenH" ) 
	#define CAL_CL2_DriverOpenH  CL2_DriverOpenH
	#define CHK_CL2_DriverOpenH  TRUE
	#define EXP_CL2_DriverOpenH  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_DriverOpenH", (RTS_UINTPTR)CL2_DriverOpenH, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_DriverOpenH
	#define EXT_CmpCAACanL2CL2_DriverOpenH
	#define GET_CmpCAACanL2CL2_DriverOpenH  ERR_OK
	#define CAL_CmpCAACanL2CL2_DriverOpenH pICmpCAACanL2->ICL2_DriverOpenH
	#define CHK_CmpCAACanL2CL2_DriverOpenH (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_DriverOpenH  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_DriverOpenH
	#define EXT_CL2_DriverOpenH
	#define GET_CL2_DriverOpenH(fl)  CAL_CMGETAPI( "CL2_DriverOpenH" ) 
	#define CAL_CL2_DriverOpenH pICmpCAACanL2->ICL2_DriverOpenH
	#define CHK_CL2_DriverOpenH (pICmpCAACanL2 != NULL)
	#define EXP_CL2_DriverOpenH  CAL_CMEXPAPI( "CL2_DriverOpenH" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_DriverOpenH  PFCL2_DRIVEROPENH pfCL2_DriverOpenH;
	#define EXT_CL2_DriverOpenH  extern PFCL2_DRIVEROPENH pfCL2_DriverOpenH;
	#define GET_CL2_DriverOpenH(fl)  s_pfCMGetAPI2( "CL2_DriverOpenH", (RTS_VOID_FCTPTR *)&pfCL2_DriverOpenH, (fl), 0, 0)
	#define CAL_CL2_DriverOpenH  pfCL2_DriverOpenH
	#define CHK_CL2_DriverOpenH  (pfCL2_DriverOpenH != NULL)
	#define EXP_CL2_DriverOpenH  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_DriverOpenH", (RTS_UINTPTR)CL2_DriverOpenH, 0, 0) 
#endif



CAA_SIZE CDECL CL2_DriverGetSize(unsigned char ucNetId, CAA_BOOL xSupport29Bit, CAA_COUNT ctMessages, CAA_ERROR* peError);
typedef CAA_SIZE (CDECL * PFCL2_DRIVERGETSIZE) (unsigned char ucNetId, CAA_BOOL xSupport29Bit, CAA_COUNT ctMessages, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_DRIVERGETSIZE_NOTIMPLEMENTED)
	#define USE_CL2_DriverGetSize
	#define EXT_CL2_DriverGetSize
	#define GET_CL2_DriverGetSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_DriverGetSize(p0,p1,p2,p3)  (CAA_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_CL2_DriverGetSize  FALSE
	#define EXP_CL2_DriverGetSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_DriverGetSize
	#define EXT_CL2_DriverGetSize
	#define GET_CL2_DriverGetSize(fl)  CAL_CMGETAPI( "CL2_DriverGetSize" ) 
	#define CAL_CL2_DriverGetSize  CL2_DriverGetSize
	#define CHK_CL2_DriverGetSize  TRUE
	#define EXP_CL2_DriverGetSize  CAL_CMEXPAPI( "CL2_DriverGetSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_DriverGetSize
	#define EXT_CL2_DriverGetSize
	#define GET_CL2_DriverGetSize(fl)  CAL_CMGETAPI( "CL2_DriverGetSize" ) 
	#define CAL_CL2_DriverGetSize  CL2_DriverGetSize
	#define CHK_CL2_DriverGetSize  TRUE
	#define EXP_CL2_DriverGetSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_DriverGetSize", (RTS_UINTPTR)CL2_DriverGetSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_DriverGetSize
	#define EXT_CmpCAACanL2CL2_DriverGetSize
	#define GET_CmpCAACanL2CL2_DriverGetSize  ERR_OK
	#define CAL_CmpCAACanL2CL2_DriverGetSize pICmpCAACanL2->ICL2_DriverGetSize
	#define CHK_CmpCAACanL2CL2_DriverGetSize (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_DriverGetSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_DriverGetSize
	#define EXT_CL2_DriverGetSize
	#define GET_CL2_DriverGetSize(fl)  CAL_CMGETAPI( "CL2_DriverGetSize" ) 
	#define CAL_CL2_DriverGetSize pICmpCAACanL2->ICL2_DriverGetSize
	#define CHK_CL2_DriverGetSize (pICmpCAACanL2 != NULL)
	#define EXP_CL2_DriverGetSize  CAL_CMEXPAPI( "CL2_DriverGetSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_DriverGetSize  PFCL2_DRIVERGETSIZE pfCL2_DriverGetSize;
	#define EXT_CL2_DriverGetSize  extern PFCL2_DRIVERGETSIZE pfCL2_DriverGetSize;
	#define GET_CL2_DriverGetSize(fl)  s_pfCMGetAPI2( "CL2_DriverGetSize", (RTS_VOID_FCTPTR *)&pfCL2_DriverGetSize, (fl), 0, 0)
	#define CAL_CL2_DriverGetSize  pfCL2_DriverGetSize
	#define CHK_CL2_DriverGetSize  (pfCL2_DriverGetSize != NULL)
	#define EXP_CL2_DriverGetSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_DriverGetSize", (RTS_UINTPTR)CL2_DriverGetSize, 0, 0) 
#endif



CAA_HANDLE CDECL CL2_DriverOpenP(unsigned char ucNetId, unsigned short usBaudrate, CAA_BOOL xSupport29Bit, CAA_SIZE szMemSize, CAA_PVOID pMemory, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFCL2_DRIVEROPENP) (unsigned char ucNetId, unsigned short usBaudrate, CAA_BOOL xSupport29Bit, CAA_SIZE szMemSize, CAA_PVOID pMemory, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_DRIVEROPENP_NOTIMPLEMENTED)
	#define USE_CL2_DriverOpenP
	#define EXT_CL2_DriverOpenP
	#define GET_CL2_DriverOpenP(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_DriverOpenP(p0,p1,p2,p3,p4,p5)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_CL2_DriverOpenP  FALSE
	#define EXP_CL2_DriverOpenP  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_DriverOpenP
	#define EXT_CL2_DriverOpenP
	#define GET_CL2_DriverOpenP(fl)  CAL_CMGETAPI( "CL2_DriverOpenP" ) 
	#define CAL_CL2_DriverOpenP  CL2_DriverOpenP
	#define CHK_CL2_DriverOpenP  TRUE
	#define EXP_CL2_DriverOpenP  CAL_CMEXPAPI( "CL2_DriverOpenP" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_DriverOpenP
	#define EXT_CL2_DriverOpenP
	#define GET_CL2_DriverOpenP(fl)  CAL_CMGETAPI( "CL2_DriverOpenP" ) 
	#define CAL_CL2_DriverOpenP  CL2_DriverOpenP
	#define CHK_CL2_DriverOpenP  TRUE
	#define EXP_CL2_DriverOpenP  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_DriverOpenP", (RTS_UINTPTR)CL2_DriverOpenP, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_DriverOpenP
	#define EXT_CmpCAACanL2CL2_DriverOpenP
	#define GET_CmpCAACanL2CL2_DriverOpenP  ERR_OK
	#define CAL_CmpCAACanL2CL2_DriverOpenP pICmpCAACanL2->ICL2_DriverOpenP
	#define CHK_CmpCAACanL2CL2_DriverOpenP (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_DriverOpenP  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_DriverOpenP
	#define EXT_CL2_DriverOpenP
	#define GET_CL2_DriverOpenP(fl)  CAL_CMGETAPI( "CL2_DriverOpenP" ) 
	#define CAL_CL2_DriverOpenP pICmpCAACanL2->ICL2_DriverOpenP
	#define CHK_CL2_DriverOpenP (pICmpCAACanL2 != NULL)
	#define EXP_CL2_DriverOpenP  CAL_CMEXPAPI( "CL2_DriverOpenP" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_DriverOpenP  PFCL2_DRIVEROPENP pfCL2_DriverOpenP;
	#define EXT_CL2_DriverOpenP  extern PFCL2_DRIVEROPENP pfCL2_DriverOpenP;
	#define GET_CL2_DriverOpenP(fl)  s_pfCMGetAPI2( "CL2_DriverOpenP", (RTS_VOID_FCTPTR *)&pfCL2_DriverOpenP, (fl), 0, 0)
	#define CAL_CL2_DriverOpenP  pfCL2_DriverOpenP
	#define CHK_CL2_DriverOpenP  (pfCL2_DriverOpenP != NULL)
	#define EXP_CL2_DriverOpenP  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_DriverOpenP", (RTS_UINTPTR)CL2_DriverOpenP, 0, 0) 
#endif



CAA_ERROR CDECL CL2_DriverClose(CAA_HANDLE hDriver);
typedef CAA_ERROR (CDECL * PFCL2_DRIVERCLOSE) (CAA_HANDLE hDriver);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_DRIVERCLOSE_NOTIMPLEMENTED)
	#define USE_CL2_DriverClose
	#define EXT_CL2_DriverClose
	#define GET_CL2_DriverClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_DriverClose(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CL2_DriverClose  FALSE
	#define EXP_CL2_DriverClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_DriverClose
	#define EXT_CL2_DriverClose
	#define GET_CL2_DriverClose(fl)  CAL_CMGETAPI( "CL2_DriverClose" ) 
	#define CAL_CL2_DriverClose  CL2_DriverClose
	#define CHK_CL2_DriverClose  TRUE
	#define EXP_CL2_DriverClose  CAL_CMEXPAPI( "CL2_DriverClose" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_DriverClose
	#define EXT_CL2_DriverClose
	#define GET_CL2_DriverClose(fl)  CAL_CMGETAPI( "CL2_DriverClose" ) 
	#define CAL_CL2_DriverClose  CL2_DriverClose
	#define CHK_CL2_DriverClose  TRUE
	#define EXP_CL2_DriverClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_DriverClose", (RTS_UINTPTR)CL2_DriverClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_DriverClose
	#define EXT_CmpCAACanL2CL2_DriverClose
	#define GET_CmpCAACanL2CL2_DriverClose  ERR_OK
	#define CAL_CmpCAACanL2CL2_DriverClose pICmpCAACanL2->ICL2_DriverClose
	#define CHK_CmpCAACanL2CL2_DriverClose (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_DriverClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_DriverClose
	#define EXT_CL2_DriverClose
	#define GET_CL2_DriverClose(fl)  CAL_CMGETAPI( "CL2_DriverClose" ) 
	#define CAL_CL2_DriverClose pICmpCAACanL2->ICL2_DriverClose
	#define CHK_CL2_DriverClose (pICmpCAACanL2 != NULL)
	#define EXP_CL2_DriverClose  CAL_CMEXPAPI( "CL2_DriverClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_DriverClose  PFCL2_DRIVERCLOSE pfCL2_DriverClose;
	#define EXT_CL2_DriverClose  extern PFCL2_DRIVERCLOSE pfCL2_DriverClose;
	#define GET_CL2_DriverClose(fl)  s_pfCMGetAPI2( "CL2_DriverClose", (RTS_VOID_FCTPTR *)&pfCL2_DriverClose, (fl), 0, 0)
	#define CAL_CL2_DriverClose  pfCL2_DriverClose
	#define CHK_CL2_DriverClose  (pfCL2_DriverClose != NULL)
	#define EXP_CL2_DriverClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_DriverClose", (RTS_UINTPTR)CL2_DriverClose, 0, 0) 
#endif



CAA_HANDLE CDECL CL2_CreateMessage(CAA_HANDLE hDriver, CL2I_COBID cobId, unsigned char ucLength, CAA_BOOL xRTR, CAA_BOOL x29BitId, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFCL2_CREATEMESSAGE) (CAA_HANDLE hDriver, CL2I_COBID cobId, unsigned char ucLength, CAA_BOOL xRTR, CAA_BOOL x29BitId, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CREATEMESSAGE_NOTIMPLEMENTED)
	#define USE_CL2_CreateMessage
	#define EXT_CL2_CreateMessage
	#define GET_CL2_CreateMessage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_CreateMessage(p0,p1,p2,p3,p4,p5)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_CL2_CreateMessage  FALSE
	#define EXP_CL2_CreateMessage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_CreateMessage
	#define EXT_CL2_CreateMessage
	#define GET_CL2_CreateMessage(fl)  CAL_CMGETAPI( "CL2_CreateMessage" ) 
	#define CAL_CL2_CreateMessage  CL2_CreateMessage
	#define CHK_CL2_CreateMessage  TRUE
	#define EXP_CL2_CreateMessage  CAL_CMEXPAPI( "CL2_CreateMessage" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_CreateMessage
	#define EXT_CL2_CreateMessage
	#define GET_CL2_CreateMessage(fl)  CAL_CMGETAPI( "CL2_CreateMessage" ) 
	#define CAL_CL2_CreateMessage  CL2_CreateMessage
	#define CHK_CL2_CreateMessage  TRUE
	#define EXP_CL2_CreateMessage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CreateMessage", (RTS_UINTPTR)CL2_CreateMessage, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_CreateMessage
	#define EXT_CmpCAACanL2CL2_CreateMessage
	#define GET_CmpCAACanL2CL2_CreateMessage  ERR_OK
	#define CAL_CmpCAACanL2CL2_CreateMessage pICmpCAACanL2->ICL2_CreateMessage
	#define CHK_CmpCAACanL2CL2_CreateMessage (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_CreateMessage  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_CreateMessage
	#define EXT_CL2_CreateMessage
	#define GET_CL2_CreateMessage(fl)  CAL_CMGETAPI( "CL2_CreateMessage" ) 
	#define CAL_CL2_CreateMessage pICmpCAACanL2->ICL2_CreateMessage
	#define CHK_CL2_CreateMessage (pICmpCAACanL2 != NULL)
	#define EXP_CL2_CreateMessage  CAL_CMEXPAPI( "CL2_CreateMessage" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_CreateMessage  PFCL2_CREATEMESSAGE pfCL2_CreateMessage;
	#define EXT_CL2_CreateMessage  extern PFCL2_CREATEMESSAGE pfCL2_CreateMessage;
	#define GET_CL2_CreateMessage(fl)  s_pfCMGetAPI2( "CL2_CreateMessage", (RTS_VOID_FCTPTR *)&pfCL2_CreateMessage, (fl), 0, 0)
	#define CAL_CL2_CreateMessage  pfCL2_CreateMessage
	#define CHK_CL2_CreateMessage  (pfCL2_CreateMessage != NULL)
	#define EXP_CL2_CreateMessage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CreateMessage", (RTS_UINTPTR)CL2_CreateMessage, 0, 0) 
#endif



CAA_ERROR CDECL CL2_FreeMessage(CAA_HANDLE hMessage);
typedef CAA_ERROR (CDECL * PFCL2_FREEMESSAGE) (CAA_HANDLE hMessage);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_FREEMESSAGE_NOTIMPLEMENTED)
	#define USE_CL2_FreeMessage
	#define EXT_CL2_FreeMessage
	#define GET_CL2_FreeMessage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_FreeMessage(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CL2_FreeMessage  FALSE
	#define EXP_CL2_FreeMessage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_FreeMessage
	#define EXT_CL2_FreeMessage
	#define GET_CL2_FreeMessage(fl)  CAL_CMGETAPI( "CL2_FreeMessage" ) 
	#define CAL_CL2_FreeMessage  CL2_FreeMessage
	#define CHK_CL2_FreeMessage  TRUE
	#define EXP_CL2_FreeMessage  CAL_CMEXPAPI( "CL2_FreeMessage" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_FreeMessage
	#define EXT_CL2_FreeMessage
	#define GET_CL2_FreeMessage(fl)  CAL_CMGETAPI( "CL2_FreeMessage" ) 
	#define CAL_CL2_FreeMessage  CL2_FreeMessage
	#define CHK_CL2_FreeMessage  TRUE
	#define EXP_CL2_FreeMessage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_FreeMessage", (RTS_UINTPTR)CL2_FreeMessage, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_FreeMessage
	#define EXT_CmpCAACanL2CL2_FreeMessage
	#define GET_CmpCAACanL2CL2_FreeMessage  ERR_OK
	#define CAL_CmpCAACanL2CL2_FreeMessage pICmpCAACanL2->ICL2_FreeMessage
	#define CHK_CmpCAACanL2CL2_FreeMessage (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_FreeMessage  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_FreeMessage
	#define EXT_CL2_FreeMessage
	#define GET_CL2_FreeMessage(fl)  CAL_CMGETAPI( "CL2_FreeMessage" ) 
	#define CAL_CL2_FreeMessage pICmpCAACanL2->ICL2_FreeMessage
	#define CHK_CL2_FreeMessage (pICmpCAACanL2 != NULL)
	#define EXP_CL2_FreeMessage  CAL_CMEXPAPI( "CL2_FreeMessage" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_FreeMessage  PFCL2_FREEMESSAGE pfCL2_FreeMessage;
	#define EXT_CL2_FreeMessage  extern PFCL2_FREEMESSAGE pfCL2_FreeMessage;
	#define GET_CL2_FreeMessage(fl)  s_pfCMGetAPI2( "CL2_FreeMessage", (RTS_VOID_FCTPTR *)&pfCL2_FreeMessage, (fl), 0, 0)
	#define CAL_CL2_FreeMessage  pfCL2_FreeMessage
	#define CHK_CL2_FreeMessage  (pfCL2_FreeMessage != NULL)
	#define EXP_CL2_FreeMessage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_FreeMessage", (RTS_UINTPTR)CL2_FreeMessage, 0, 0) 
#endif



CAA_HANDLE CDECL CL2_CloneMessage(CAA_HANDLE hMessage, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFCL2_CLONEMESSAGE) (CAA_HANDLE hMessage, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CLONEMESSAGE_NOTIMPLEMENTED)
	#define USE_CL2_CloneMessage
	#define EXT_CL2_CloneMessage
	#define GET_CL2_CloneMessage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_CloneMessage(p0,p1)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_CL2_CloneMessage  FALSE
	#define EXP_CL2_CloneMessage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_CloneMessage
	#define EXT_CL2_CloneMessage
	#define GET_CL2_CloneMessage(fl)  CAL_CMGETAPI( "CL2_CloneMessage" ) 
	#define CAL_CL2_CloneMessage  CL2_CloneMessage
	#define CHK_CL2_CloneMessage  TRUE
	#define EXP_CL2_CloneMessage  CAL_CMEXPAPI( "CL2_CloneMessage" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_CloneMessage
	#define EXT_CL2_CloneMessage
	#define GET_CL2_CloneMessage(fl)  CAL_CMGETAPI( "CL2_CloneMessage" ) 
	#define CAL_CL2_CloneMessage  CL2_CloneMessage
	#define CHK_CL2_CloneMessage  TRUE
	#define EXP_CL2_CloneMessage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CloneMessage", (RTS_UINTPTR)CL2_CloneMessage, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_CloneMessage
	#define EXT_CmpCAACanL2CL2_CloneMessage
	#define GET_CmpCAACanL2CL2_CloneMessage  ERR_OK
	#define CAL_CmpCAACanL2CL2_CloneMessage pICmpCAACanL2->ICL2_CloneMessage
	#define CHK_CmpCAACanL2CL2_CloneMessage (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_CloneMessage  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_CloneMessage
	#define EXT_CL2_CloneMessage
	#define GET_CL2_CloneMessage(fl)  CAL_CMGETAPI( "CL2_CloneMessage" ) 
	#define CAL_CL2_CloneMessage pICmpCAACanL2->ICL2_CloneMessage
	#define CHK_CL2_CloneMessage (pICmpCAACanL2 != NULL)
	#define EXP_CL2_CloneMessage  CAL_CMEXPAPI( "CL2_CloneMessage" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_CloneMessage  PFCL2_CLONEMESSAGE pfCL2_CloneMessage;
	#define EXT_CL2_CloneMessage  extern PFCL2_CLONEMESSAGE pfCL2_CloneMessage;
	#define GET_CL2_CloneMessage(fl)  s_pfCMGetAPI2( "CL2_CloneMessage", (RTS_VOID_FCTPTR *)&pfCL2_CloneMessage, (fl), 0, 0)
	#define CAL_CL2_CloneMessage  pfCL2_CloneMessage
	#define CHK_CL2_CloneMessage  (pfCL2_CloneMessage != NULL)
	#define EXP_CL2_CloneMessage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CloneMessage", (RTS_UINTPTR)CL2_CloneMessage, 0, 0) 
#endif



CAA_HANDLE CDECL CL2_CreateSingleIdReceiver(CAA_HANDLE hDriver, CL2I_COBID cobId, CAA_BOOL xRTR, CAA_BOOL x29BitId, CAA_BOOL xTransmit, CAA_BOOL xAlwaysNewest, CAA_ENUM eEvent, CAA_BOOL xEnableSyncWindow, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFCL2_CREATESINGLEIDRECEIVER) (CAA_HANDLE hDriver, CL2I_COBID cobId, CAA_BOOL xRTR, CAA_BOOL x29BitId, CAA_BOOL xTransmit, CAA_BOOL xAlwaysNewest, CAA_ENUM eEvent, CAA_BOOL xEnableSyncWindow, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CREATESINGLEIDRECEIVER_NOTIMPLEMENTED)
	#define USE_CL2_CreateSingleIdReceiver
	#define EXT_CL2_CreateSingleIdReceiver
	#define GET_CL2_CreateSingleIdReceiver(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_CreateSingleIdReceiver(p0,p1,p2,p3,p4,p5,p6,p7,p8)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_CL2_CreateSingleIdReceiver  FALSE
	#define EXP_CL2_CreateSingleIdReceiver  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_CreateSingleIdReceiver
	#define EXT_CL2_CreateSingleIdReceiver
	#define GET_CL2_CreateSingleIdReceiver(fl)  CAL_CMGETAPI( "CL2_CreateSingleIdReceiver" ) 
	#define CAL_CL2_CreateSingleIdReceiver  CL2_CreateSingleIdReceiver
	#define CHK_CL2_CreateSingleIdReceiver  TRUE
	#define EXP_CL2_CreateSingleIdReceiver  CAL_CMEXPAPI( "CL2_CreateSingleIdReceiver" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_CreateSingleIdReceiver
	#define EXT_CL2_CreateSingleIdReceiver
	#define GET_CL2_CreateSingleIdReceiver(fl)  CAL_CMGETAPI( "CL2_CreateSingleIdReceiver" ) 
	#define CAL_CL2_CreateSingleIdReceiver  CL2_CreateSingleIdReceiver
	#define CHK_CL2_CreateSingleIdReceiver  TRUE
	#define EXP_CL2_CreateSingleIdReceiver  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CreateSingleIdReceiver", (RTS_UINTPTR)CL2_CreateSingleIdReceiver, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_CreateSingleIdReceiver
	#define EXT_CmpCAACanL2CL2_CreateSingleIdReceiver
	#define GET_CmpCAACanL2CL2_CreateSingleIdReceiver  ERR_OK
	#define CAL_CmpCAACanL2CL2_CreateSingleIdReceiver pICmpCAACanL2->ICL2_CreateSingleIdReceiver
	#define CHK_CmpCAACanL2CL2_CreateSingleIdReceiver (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_CreateSingleIdReceiver  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_CreateSingleIdReceiver
	#define EXT_CL2_CreateSingleIdReceiver
	#define GET_CL2_CreateSingleIdReceiver(fl)  CAL_CMGETAPI( "CL2_CreateSingleIdReceiver" ) 
	#define CAL_CL2_CreateSingleIdReceiver pICmpCAACanL2->ICL2_CreateSingleIdReceiver
	#define CHK_CL2_CreateSingleIdReceiver (pICmpCAACanL2 != NULL)
	#define EXP_CL2_CreateSingleIdReceiver  CAL_CMEXPAPI( "CL2_CreateSingleIdReceiver" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_CreateSingleIdReceiver  PFCL2_CREATESINGLEIDRECEIVER pfCL2_CreateSingleIdReceiver;
	#define EXT_CL2_CreateSingleIdReceiver  extern PFCL2_CREATESINGLEIDRECEIVER pfCL2_CreateSingleIdReceiver;
	#define GET_CL2_CreateSingleIdReceiver(fl)  s_pfCMGetAPI2( "CL2_CreateSingleIdReceiver", (RTS_VOID_FCTPTR *)&pfCL2_CreateSingleIdReceiver, (fl), 0, 0)
	#define CAL_CL2_CreateSingleIdReceiver  pfCL2_CreateSingleIdReceiver
	#define CHK_CL2_CreateSingleIdReceiver  (pfCL2_CreateSingleIdReceiver != NULL)
	#define EXP_CL2_CreateSingleIdReceiver  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CreateSingleIdReceiver", (RTS_UINTPTR)CL2_CreateSingleIdReceiver, 0, 0) 
#endif



CAA_HANDLE CDECL CL2_CreateIdAreaReceiver(CAA_HANDLE hDriver, CAA_BOOL xAlwaysNewest, CAA_ENUM eEvent, CAA_BOOL xEnableSyncWindow, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFCL2_CREATEIDAREARECEIVER) (CAA_HANDLE hDriver, CAA_BOOL xAlwaysNewest, CAA_ENUM eEvent, CAA_BOOL xEnableSyncWindow, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CREATEIDAREARECEIVER_NOTIMPLEMENTED)
	#define USE_CL2_CreateIdAreaReceiver
	#define EXT_CL2_CreateIdAreaReceiver
	#define GET_CL2_CreateIdAreaReceiver(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_CreateIdAreaReceiver(p0,p1,p2,p3,p4)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_CL2_CreateIdAreaReceiver  FALSE
	#define EXP_CL2_CreateIdAreaReceiver  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_CreateIdAreaReceiver
	#define EXT_CL2_CreateIdAreaReceiver
	#define GET_CL2_CreateIdAreaReceiver(fl)  CAL_CMGETAPI( "CL2_CreateIdAreaReceiver" ) 
	#define CAL_CL2_CreateIdAreaReceiver  CL2_CreateIdAreaReceiver
	#define CHK_CL2_CreateIdAreaReceiver  TRUE
	#define EXP_CL2_CreateIdAreaReceiver  CAL_CMEXPAPI( "CL2_CreateIdAreaReceiver" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_CreateIdAreaReceiver
	#define EXT_CL2_CreateIdAreaReceiver
	#define GET_CL2_CreateIdAreaReceiver(fl)  CAL_CMGETAPI( "CL2_CreateIdAreaReceiver" ) 
	#define CAL_CL2_CreateIdAreaReceiver  CL2_CreateIdAreaReceiver
	#define CHK_CL2_CreateIdAreaReceiver  TRUE
	#define EXP_CL2_CreateIdAreaReceiver  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CreateIdAreaReceiver", (RTS_UINTPTR)CL2_CreateIdAreaReceiver, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_CreateIdAreaReceiver
	#define EXT_CmpCAACanL2CL2_CreateIdAreaReceiver
	#define GET_CmpCAACanL2CL2_CreateIdAreaReceiver  ERR_OK
	#define CAL_CmpCAACanL2CL2_CreateIdAreaReceiver pICmpCAACanL2->ICL2_CreateIdAreaReceiver
	#define CHK_CmpCAACanL2CL2_CreateIdAreaReceiver (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_CreateIdAreaReceiver  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_CreateIdAreaReceiver
	#define EXT_CL2_CreateIdAreaReceiver
	#define GET_CL2_CreateIdAreaReceiver(fl)  CAL_CMGETAPI( "CL2_CreateIdAreaReceiver" ) 
	#define CAL_CL2_CreateIdAreaReceiver pICmpCAACanL2->ICL2_CreateIdAreaReceiver
	#define CHK_CL2_CreateIdAreaReceiver (pICmpCAACanL2 != NULL)
	#define EXP_CL2_CreateIdAreaReceiver  CAL_CMEXPAPI( "CL2_CreateIdAreaReceiver" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_CreateIdAreaReceiver  PFCL2_CREATEIDAREARECEIVER pfCL2_CreateIdAreaReceiver;
	#define EXT_CL2_CreateIdAreaReceiver  extern PFCL2_CREATEIDAREARECEIVER pfCL2_CreateIdAreaReceiver;
	#define GET_CL2_CreateIdAreaReceiver(fl)  s_pfCMGetAPI2( "CL2_CreateIdAreaReceiver", (RTS_VOID_FCTPTR *)&pfCL2_CreateIdAreaReceiver, (fl), 0, 0)
	#define CAL_CL2_CreateIdAreaReceiver  pfCL2_CreateIdAreaReceiver
	#define CHK_CL2_CreateIdAreaReceiver  (pfCL2_CreateIdAreaReceiver != NULL)
	#define EXP_CL2_CreateIdAreaReceiver  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CreateIdAreaReceiver", (RTS_UINTPTR)CL2_CreateIdAreaReceiver, 0, 0) 
#endif



CAA_HANDLE CDECL CL2_CreateIdAreaReceiverEx(CAA_HANDLE hDriver, CAA_BOOL xAlwaysNewest, CAA_BOOL xReverse, CAA_ENUM eEvent, CAA_BOOL xEnableSyncWindow, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFCL2_CREATEIDAREARECEIVEREX) (CAA_HANDLE hDriver, CAA_BOOL xAlwaysNewest, CAA_BOOL xReverse, CAA_ENUM eEvent, CAA_BOOL xEnableSyncWindow, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CREATEIDAREARECEIVEREX_NOTIMPLEMENTED)
	#define USE_CL2_CreateIdAreaReceiverEx
	#define EXT_CL2_CreateIdAreaReceiverEx
	#define GET_CL2_CreateIdAreaReceiverEx(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_CreateIdAreaReceiverEx(p0,p1,p2,p3,p4,p5)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_CL2_CreateIdAreaReceiverEx  FALSE
	#define EXP_CL2_CreateIdAreaReceiverEx  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_CreateIdAreaReceiverEx
	#define EXT_CL2_CreateIdAreaReceiverEx
	#define GET_CL2_CreateIdAreaReceiverEx(fl)  CAL_CMGETAPI( "CL2_CreateIdAreaReceiverEx" ) 
	#define CAL_CL2_CreateIdAreaReceiverEx  CL2_CreateIdAreaReceiverEx
	#define CHK_CL2_CreateIdAreaReceiverEx  TRUE
	#define EXP_CL2_CreateIdAreaReceiverEx  CAL_CMEXPAPI( "CL2_CreateIdAreaReceiverEx" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_CreateIdAreaReceiverEx
	#define EXT_CL2_CreateIdAreaReceiverEx
	#define GET_CL2_CreateIdAreaReceiverEx(fl)  CAL_CMGETAPI( "CL2_CreateIdAreaReceiverEx" ) 
	#define CAL_CL2_CreateIdAreaReceiverEx  CL2_CreateIdAreaReceiverEx
	#define CHK_CL2_CreateIdAreaReceiverEx  TRUE
	#define EXP_CL2_CreateIdAreaReceiverEx  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CreateIdAreaReceiverEx", (RTS_UINTPTR)CL2_CreateIdAreaReceiverEx, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_CreateIdAreaReceiverEx
	#define EXT_CmpCAACanL2CL2_CreateIdAreaReceiverEx
	#define GET_CmpCAACanL2CL2_CreateIdAreaReceiverEx  ERR_OK
	#define CAL_CmpCAACanL2CL2_CreateIdAreaReceiverEx pICmpCAACanL2->ICL2_CreateIdAreaReceiverEx
	#define CHK_CmpCAACanL2CL2_CreateIdAreaReceiverEx (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_CreateIdAreaReceiverEx  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_CreateIdAreaReceiverEx
	#define EXT_CL2_CreateIdAreaReceiverEx
	#define GET_CL2_CreateIdAreaReceiverEx(fl)  CAL_CMGETAPI( "CL2_CreateIdAreaReceiverEx" ) 
	#define CAL_CL2_CreateIdAreaReceiverEx pICmpCAACanL2->ICL2_CreateIdAreaReceiverEx
	#define CHK_CL2_CreateIdAreaReceiverEx (pICmpCAACanL2 != NULL)
	#define EXP_CL2_CreateIdAreaReceiverEx  CAL_CMEXPAPI( "CL2_CreateIdAreaReceiverEx" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_CreateIdAreaReceiverEx  PFCL2_CREATEIDAREARECEIVEREX pfCL2_CreateIdAreaReceiverEx;
	#define EXT_CL2_CreateIdAreaReceiverEx  extern PFCL2_CREATEIDAREARECEIVEREX pfCL2_CreateIdAreaReceiverEx;
	#define GET_CL2_CreateIdAreaReceiverEx(fl)  s_pfCMGetAPI2( "CL2_CreateIdAreaReceiverEx", (RTS_VOID_FCTPTR *)&pfCL2_CreateIdAreaReceiverEx, (fl), 0, 0)
	#define CAL_CL2_CreateIdAreaReceiverEx  pfCL2_CreateIdAreaReceiverEx
	#define CHK_CL2_CreateIdAreaReceiverEx  (pfCL2_CreateIdAreaReceiverEx != NULL)
	#define EXP_CL2_CreateIdAreaReceiverEx  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CreateIdAreaReceiverEx", (RTS_UINTPTR)CL2_CreateIdAreaReceiverEx, 0, 0) 
#endif



CAA_ERROR CDECL CL2_RegisterIdArea(CAA_HANDLE hReceiverId, CL2I_COBID cobIdStart, CL2I_COBID cobIdEnd, CAA_BOOL xRTRValue, CAA_BOOL xRTRMask, CAA_BOOL x29BitIdValue, CAA_BOOL x29BitIdMask, CAA_BOOL xTransmitValue, CAA_BOOL xTransmitMask);
typedef CAA_ERROR (CDECL * PFCL2_REGISTERIDAREA) (CAA_HANDLE hReceiverId, CL2I_COBID cobIdStart, CL2I_COBID cobIdEnd, CAA_BOOL xRTRValue, CAA_BOOL xRTRMask, CAA_BOOL x29BitIdValue, CAA_BOOL x29BitIdMask, CAA_BOOL xTransmitValue, CAA_BOOL xTransmitMask);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_REGISTERIDAREA_NOTIMPLEMENTED)
	#define USE_CL2_RegisterIdArea
	#define EXT_CL2_RegisterIdArea
	#define GET_CL2_RegisterIdArea(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_RegisterIdArea(p0,p1,p2,p3,p4,p5,p6,p7,p8)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CL2_RegisterIdArea  FALSE
	#define EXP_CL2_RegisterIdArea  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_RegisterIdArea
	#define EXT_CL2_RegisterIdArea
	#define GET_CL2_RegisterIdArea(fl)  CAL_CMGETAPI( "CL2_RegisterIdArea" ) 
	#define CAL_CL2_RegisterIdArea  CL2_RegisterIdArea
	#define CHK_CL2_RegisterIdArea  TRUE
	#define EXP_CL2_RegisterIdArea  CAL_CMEXPAPI( "CL2_RegisterIdArea" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_RegisterIdArea
	#define EXT_CL2_RegisterIdArea
	#define GET_CL2_RegisterIdArea(fl)  CAL_CMGETAPI( "CL2_RegisterIdArea" ) 
	#define CAL_CL2_RegisterIdArea  CL2_RegisterIdArea
	#define CHK_CL2_RegisterIdArea  TRUE
	#define EXP_CL2_RegisterIdArea  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_RegisterIdArea", (RTS_UINTPTR)CL2_RegisterIdArea, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_RegisterIdArea
	#define EXT_CmpCAACanL2CL2_RegisterIdArea
	#define GET_CmpCAACanL2CL2_RegisterIdArea  ERR_OK
	#define CAL_CmpCAACanL2CL2_RegisterIdArea pICmpCAACanL2->ICL2_RegisterIdArea
	#define CHK_CmpCAACanL2CL2_RegisterIdArea (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_RegisterIdArea  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_RegisterIdArea
	#define EXT_CL2_RegisterIdArea
	#define GET_CL2_RegisterIdArea(fl)  CAL_CMGETAPI( "CL2_RegisterIdArea" ) 
	#define CAL_CL2_RegisterIdArea pICmpCAACanL2->ICL2_RegisterIdArea
	#define CHK_CL2_RegisterIdArea (pICmpCAACanL2 != NULL)
	#define EXP_CL2_RegisterIdArea  CAL_CMEXPAPI( "CL2_RegisterIdArea" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_RegisterIdArea  PFCL2_REGISTERIDAREA pfCL2_RegisterIdArea;
	#define EXT_CL2_RegisterIdArea  extern PFCL2_REGISTERIDAREA pfCL2_RegisterIdArea;
	#define GET_CL2_RegisterIdArea(fl)  s_pfCMGetAPI2( "CL2_RegisterIdArea", (RTS_VOID_FCTPTR *)&pfCL2_RegisterIdArea, (fl), 0, 0)
	#define CAL_CL2_RegisterIdArea  pfCL2_RegisterIdArea
	#define CHK_CL2_RegisterIdArea  (pfCL2_RegisterIdArea != NULL)
	#define EXP_CL2_RegisterIdArea  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_RegisterIdArea", (RTS_UINTPTR)CL2_RegisterIdArea, 0, 0) 
#endif



CAA_ERROR CDECL CL2_UnregisterIdArea(CAA_HANDLE hReceiverId, CL2I_COBID cobIdStart, CL2I_COBID cobIdEnd,  CAA_BOOL xRTRValue, CAA_BOOL xRTRMask, CAA_BOOL x29BitIdValue, CAA_BOOL x29BitIdMask, CAA_BOOL xTransmitValue, CAA_BOOL xTransmitMask);
typedef CAA_ERROR (CDECL * PFCL2_UNREGISTERIDAREA) (CAA_HANDLE hReceiverId, CL2I_COBID cobIdStart, CL2I_COBID cobIdEnd,  CAA_BOOL xRTRValue, CAA_BOOL xRTRMask, CAA_BOOL x29BitIdValue, CAA_BOOL x29BitIdMask, CAA_BOOL xTransmitValue, CAA_BOOL xTransmitMask);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_UNREGISTERIDAREA_NOTIMPLEMENTED)
	#define USE_CL2_UnregisterIdArea
	#define EXT_CL2_UnregisterIdArea
	#define GET_CL2_UnregisterIdArea(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_UnregisterIdArea(p0,p1,p2,p3,p4,p5,p6,p7,p8)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CL2_UnregisterIdArea  FALSE
	#define EXP_CL2_UnregisterIdArea  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_UnregisterIdArea
	#define EXT_CL2_UnregisterIdArea
	#define GET_CL2_UnregisterIdArea(fl)  CAL_CMGETAPI( "CL2_UnregisterIdArea" ) 
	#define CAL_CL2_UnregisterIdArea  CL2_UnregisterIdArea
	#define CHK_CL2_UnregisterIdArea  TRUE
	#define EXP_CL2_UnregisterIdArea  CAL_CMEXPAPI( "CL2_UnregisterIdArea" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_UnregisterIdArea
	#define EXT_CL2_UnregisterIdArea
	#define GET_CL2_UnregisterIdArea(fl)  CAL_CMGETAPI( "CL2_UnregisterIdArea" ) 
	#define CAL_CL2_UnregisterIdArea  CL2_UnregisterIdArea
	#define CHK_CL2_UnregisterIdArea  TRUE
	#define EXP_CL2_UnregisterIdArea  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_UnregisterIdArea", (RTS_UINTPTR)CL2_UnregisterIdArea, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_UnregisterIdArea
	#define EXT_CmpCAACanL2CL2_UnregisterIdArea
	#define GET_CmpCAACanL2CL2_UnregisterIdArea  ERR_OK
	#define CAL_CmpCAACanL2CL2_UnregisterIdArea pICmpCAACanL2->ICL2_UnregisterIdArea
	#define CHK_CmpCAACanL2CL2_UnregisterIdArea (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_UnregisterIdArea  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_UnregisterIdArea
	#define EXT_CL2_UnregisterIdArea
	#define GET_CL2_UnregisterIdArea(fl)  CAL_CMGETAPI( "CL2_UnregisterIdArea" ) 
	#define CAL_CL2_UnregisterIdArea pICmpCAACanL2->ICL2_UnregisterIdArea
	#define CHK_CL2_UnregisterIdArea (pICmpCAACanL2 != NULL)
	#define EXP_CL2_UnregisterIdArea  CAL_CMEXPAPI( "CL2_UnregisterIdArea" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_UnregisterIdArea  PFCL2_UNREGISTERIDAREA pfCL2_UnregisterIdArea;
	#define EXT_CL2_UnregisterIdArea  extern PFCL2_UNREGISTERIDAREA pfCL2_UnregisterIdArea;
	#define GET_CL2_UnregisterIdArea(fl)  s_pfCMGetAPI2( "CL2_UnregisterIdArea", (RTS_VOID_FCTPTR *)&pfCL2_UnregisterIdArea, (fl), 0, 0)
	#define CAL_CL2_UnregisterIdArea  pfCL2_UnregisterIdArea
	#define CHK_CL2_UnregisterIdArea  (pfCL2_UnregisterIdArea != NULL)
	#define EXP_CL2_UnregisterIdArea  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_UnregisterIdArea", (RTS_UINTPTR)CL2_UnregisterIdArea, 0, 0) 
#endif



CAA_HANDLE CDECL CL2_CreateMaskReceiver(CAA_HANDLE hDriver, CL2I_COBID cobIdValue, CL2I_COBID cobIdMask, CAA_BOOL xRTRValue, CAA_BOOL xRTRMask, CAA_BOOL x29BitIdValue, CAA_BOOL x29BitIdMask, CAA_BOOL xTransmitValue, CAA_BOOL xTransmitMask, CAA_BOOL xAlwaysNewest, CAA_ENUM eEvent, CAA_BOOL xEnableSyncWindow, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFCL2_CREATEMASKRECEIVER) (CAA_HANDLE hDriver, CL2I_COBID cobIdValue, CL2I_COBID cobIdMask, CAA_BOOL xRTRValue, CAA_BOOL xRTRMask, CAA_BOOL x29BitIdValue, CAA_BOOL x29BitIdMask, CAA_BOOL xTransmitValue, CAA_BOOL xTransmitMask, CAA_BOOL xAlwaysNewest, CAA_ENUM eEvent, CAA_BOOL xEnableSyncWindow, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CREATEMASKRECEIVER_NOTIMPLEMENTED)
	#define USE_CL2_CreateMaskReceiver
	#define EXT_CL2_CreateMaskReceiver
	#define GET_CL2_CreateMaskReceiver(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_CreateMaskReceiver(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_CL2_CreateMaskReceiver  FALSE
	#define EXP_CL2_CreateMaskReceiver  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_CreateMaskReceiver
	#define EXT_CL2_CreateMaskReceiver
	#define GET_CL2_CreateMaskReceiver(fl)  CAL_CMGETAPI( "CL2_CreateMaskReceiver" ) 
	#define CAL_CL2_CreateMaskReceiver  CL2_CreateMaskReceiver
	#define CHK_CL2_CreateMaskReceiver  TRUE
	#define EXP_CL2_CreateMaskReceiver  CAL_CMEXPAPI( "CL2_CreateMaskReceiver" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_CreateMaskReceiver
	#define EXT_CL2_CreateMaskReceiver
	#define GET_CL2_CreateMaskReceiver(fl)  CAL_CMGETAPI( "CL2_CreateMaskReceiver" ) 
	#define CAL_CL2_CreateMaskReceiver  CL2_CreateMaskReceiver
	#define CHK_CL2_CreateMaskReceiver  TRUE
	#define EXP_CL2_CreateMaskReceiver  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CreateMaskReceiver", (RTS_UINTPTR)CL2_CreateMaskReceiver, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_CreateMaskReceiver
	#define EXT_CmpCAACanL2CL2_CreateMaskReceiver
	#define GET_CmpCAACanL2CL2_CreateMaskReceiver  ERR_OK
	#define CAL_CmpCAACanL2CL2_CreateMaskReceiver pICmpCAACanL2->ICL2_CreateMaskReceiver
	#define CHK_CmpCAACanL2CL2_CreateMaskReceiver (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_CreateMaskReceiver  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_CreateMaskReceiver
	#define EXT_CL2_CreateMaskReceiver
	#define GET_CL2_CreateMaskReceiver(fl)  CAL_CMGETAPI( "CL2_CreateMaskReceiver" ) 
	#define CAL_CL2_CreateMaskReceiver pICmpCAACanL2->ICL2_CreateMaskReceiver
	#define CHK_CL2_CreateMaskReceiver (pICmpCAACanL2 != NULL)
	#define EXP_CL2_CreateMaskReceiver  CAL_CMEXPAPI( "CL2_CreateMaskReceiver" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_CreateMaskReceiver  PFCL2_CREATEMASKRECEIVER pfCL2_CreateMaskReceiver;
	#define EXT_CL2_CreateMaskReceiver  extern PFCL2_CREATEMASKRECEIVER pfCL2_CreateMaskReceiver;
	#define GET_CL2_CreateMaskReceiver(fl)  s_pfCMGetAPI2( "CL2_CreateMaskReceiver", (RTS_VOID_FCTPTR *)&pfCL2_CreateMaskReceiver, (fl), 0, 0)
	#define CAL_CL2_CreateMaskReceiver  pfCL2_CreateMaskReceiver
	#define CHK_CL2_CreateMaskReceiver  (pfCL2_CreateMaskReceiver != NULL)
	#define EXP_CL2_CreateMaskReceiver  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CreateMaskReceiver", (RTS_UINTPTR)CL2_CreateMaskReceiver, 0, 0) 
#endif



CAA_HANDLE CDECL CL2_CreateArrayReceiver(CAA_HANDLE hDriver, CL2I_ARRAYRECV_ENTRY* paSortedCOBIDs, CAA_COUNT ctCOBIDs, CAA_ENUM eEvent, CAA_BOOL xEnableSyncWindow, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFCL2_CREATEARRAYRECEIVER) (CAA_HANDLE hDriver, CL2I_ARRAYRECV_ENTRY* paSortedCOBIDs, CAA_COUNT ctCOBIDs, CAA_ENUM eEvent, CAA_BOOL xEnableSyncWindow, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CREATEARRAYRECEIVER_NOTIMPLEMENTED)
	#define USE_CL2_CreateArrayReceiver
	#define EXT_CL2_CreateArrayReceiver
	#define GET_CL2_CreateArrayReceiver(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_CreateArrayReceiver(p0,p1,p2,p3,p4,p5)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_CL2_CreateArrayReceiver  FALSE
	#define EXP_CL2_CreateArrayReceiver  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_CreateArrayReceiver
	#define EXT_CL2_CreateArrayReceiver
	#define GET_CL2_CreateArrayReceiver(fl)  CAL_CMGETAPI( "CL2_CreateArrayReceiver" ) 
	#define CAL_CL2_CreateArrayReceiver  CL2_CreateArrayReceiver
	#define CHK_CL2_CreateArrayReceiver  TRUE
	#define EXP_CL2_CreateArrayReceiver  CAL_CMEXPAPI( "CL2_CreateArrayReceiver" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_CreateArrayReceiver
	#define EXT_CL2_CreateArrayReceiver
	#define GET_CL2_CreateArrayReceiver(fl)  CAL_CMGETAPI( "CL2_CreateArrayReceiver" ) 
	#define CAL_CL2_CreateArrayReceiver  CL2_CreateArrayReceiver
	#define CHK_CL2_CreateArrayReceiver  TRUE
	#define EXP_CL2_CreateArrayReceiver  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CreateArrayReceiver", (RTS_UINTPTR)CL2_CreateArrayReceiver, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_CreateArrayReceiver
	#define EXT_CmpCAACanL2CL2_CreateArrayReceiver
	#define GET_CmpCAACanL2CL2_CreateArrayReceiver  ERR_OK
	#define CAL_CmpCAACanL2CL2_CreateArrayReceiver pICmpCAACanL2->ICL2_CreateArrayReceiver
	#define CHK_CmpCAACanL2CL2_CreateArrayReceiver (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_CreateArrayReceiver  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_CreateArrayReceiver
	#define EXT_CL2_CreateArrayReceiver
	#define GET_CL2_CreateArrayReceiver(fl)  CAL_CMGETAPI( "CL2_CreateArrayReceiver" ) 
	#define CAL_CL2_CreateArrayReceiver pICmpCAACanL2->ICL2_CreateArrayReceiver
	#define CHK_CL2_CreateArrayReceiver (pICmpCAACanL2 != NULL)
	#define EXP_CL2_CreateArrayReceiver  CAL_CMEXPAPI( "CL2_CreateArrayReceiver" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_CreateArrayReceiver  PFCL2_CREATEARRAYRECEIVER pfCL2_CreateArrayReceiver;
	#define EXT_CL2_CreateArrayReceiver  extern PFCL2_CREATEARRAYRECEIVER pfCL2_CreateArrayReceiver;
	#define GET_CL2_CreateArrayReceiver(fl)  s_pfCMGetAPI2( "CL2_CreateArrayReceiver", (RTS_VOID_FCTPTR *)&pfCL2_CreateArrayReceiver, (fl), 0, 0)
	#define CAL_CL2_CreateArrayReceiver  pfCL2_CreateArrayReceiver
	#define CHK_CL2_CreateArrayReceiver  (pfCL2_CreateArrayReceiver != NULL)
	#define EXP_CL2_CreateArrayReceiver  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CreateArrayReceiver", (RTS_UINTPTR)CL2_CreateArrayReceiver, 0, 0) 
#endif



CAA_ERROR CDECL CL2_DeleteReceiver(CAA_HANDLE hReceiverId);
typedef CAA_ERROR (CDECL * PFCL2_DELETERECEIVER) (CAA_HANDLE hReceiverId);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_DELETERECEIVER_NOTIMPLEMENTED)
	#define USE_CL2_DeleteReceiver
	#define EXT_CL2_DeleteReceiver
	#define GET_CL2_DeleteReceiver(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_DeleteReceiver(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CL2_DeleteReceiver  FALSE
	#define EXP_CL2_DeleteReceiver  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_DeleteReceiver
	#define EXT_CL2_DeleteReceiver
	#define GET_CL2_DeleteReceiver(fl)  CAL_CMGETAPI( "CL2_DeleteReceiver" ) 
	#define CAL_CL2_DeleteReceiver  CL2_DeleteReceiver
	#define CHK_CL2_DeleteReceiver  TRUE
	#define EXP_CL2_DeleteReceiver  CAL_CMEXPAPI( "CL2_DeleteReceiver" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_DeleteReceiver
	#define EXT_CL2_DeleteReceiver
	#define GET_CL2_DeleteReceiver(fl)  CAL_CMGETAPI( "CL2_DeleteReceiver" ) 
	#define CAL_CL2_DeleteReceiver  CL2_DeleteReceiver
	#define CHK_CL2_DeleteReceiver  TRUE
	#define EXP_CL2_DeleteReceiver  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_DeleteReceiver", (RTS_UINTPTR)CL2_DeleteReceiver, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_DeleteReceiver
	#define EXT_CmpCAACanL2CL2_DeleteReceiver
	#define GET_CmpCAACanL2CL2_DeleteReceiver  ERR_OK
	#define CAL_CmpCAACanL2CL2_DeleteReceiver pICmpCAACanL2->ICL2_DeleteReceiver
	#define CHK_CmpCAACanL2CL2_DeleteReceiver (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_DeleteReceiver  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_DeleteReceiver
	#define EXT_CL2_DeleteReceiver
	#define GET_CL2_DeleteReceiver(fl)  CAL_CMGETAPI( "CL2_DeleteReceiver" ) 
	#define CAL_CL2_DeleteReceiver pICmpCAACanL2->ICL2_DeleteReceiver
	#define CHK_CL2_DeleteReceiver (pICmpCAACanL2 != NULL)
	#define EXP_CL2_DeleteReceiver  CAL_CMEXPAPI( "CL2_DeleteReceiver" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_DeleteReceiver  PFCL2_DELETERECEIVER pfCL2_DeleteReceiver;
	#define EXT_CL2_DeleteReceiver  extern PFCL2_DELETERECEIVER pfCL2_DeleteReceiver;
	#define GET_CL2_DeleteReceiver(fl)  s_pfCMGetAPI2( "CL2_DeleteReceiver", (RTS_VOID_FCTPTR *)&pfCL2_DeleteReceiver, (fl), 0, 0)
	#define CAL_CL2_DeleteReceiver  pfCL2_DeleteReceiver
	#define CHK_CL2_DeleteReceiver  (pfCL2_DeleteReceiver != NULL)
	#define EXP_CL2_DeleteReceiver  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_DeleteReceiver", (RTS_UINTPTR)CL2_DeleteReceiver, 0, 0) 
#endif



CAA_HANDLE CDECL CL2_Read(CAA_HANDLE hReceiverId, CAA_COUNT* pctMsgLeft, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFCL2_READ) (CAA_HANDLE hReceiverId, CAA_COUNT* pctMsgLeft, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_READ_NOTIMPLEMENTED)
	#define USE_CL2_Read
	#define EXT_CL2_Read
	#define GET_CL2_Read(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_Read(p0,p1,p2)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_CL2_Read  FALSE
	#define EXP_CL2_Read  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_Read
	#define EXT_CL2_Read
	#define GET_CL2_Read(fl)  CAL_CMGETAPI( "CL2_Read" ) 
	#define CAL_CL2_Read  CL2_Read
	#define CHK_CL2_Read  TRUE
	#define EXP_CL2_Read  CAL_CMEXPAPI( "CL2_Read" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_Read
	#define EXT_CL2_Read
	#define GET_CL2_Read(fl)  CAL_CMGETAPI( "CL2_Read" ) 
	#define CAL_CL2_Read  CL2_Read
	#define CHK_CL2_Read  TRUE
	#define EXP_CL2_Read  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_Read", (RTS_UINTPTR)CL2_Read, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_Read
	#define EXT_CmpCAACanL2CL2_Read
	#define GET_CmpCAACanL2CL2_Read  ERR_OK
	#define CAL_CmpCAACanL2CL2_Read pICmpCAACanL2->ICL2_Read
	#define CHK_CmpCAACanL2CL2_Read (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_Read  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_Read
	#define EXT_CL2_Read
	#define GET_CL2_Read(fl)  CAL_CMGETAPI( "CL2_Read" ) 
	#define CAL_CL2_Read pICmpCAACanL2->ICL2_Read
	#define CHK_CL2_Read (pICmpCAACanL2 != NULL)
	#define EXP_CL2_Read  CAL_CMEXPAPI( "CL2_Read" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_Read  PFCL2_READ pfCL2_Read;
	#define EXT_CL2_Read  extern PFCL2_READ pfCL2_Read;
	#define GET_CL2_Read(fl)  s_pfCMGetAPI2( "CL2_Read", (RTS_VOID_FCTPTR *)&pfCL2_Read, (fl), 0, 0)
	#define CAL_CL2_Read  pfCL2_Read
	#define CHK_CL2_Read  (pfCL2_Read != NULL)
	#define EXP_CL2_Read  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_Read", (RTS_UINTPTR)CL2_Read, 0, 0) 
#endif



CAA_HANDLE CDECL CL2_ReadArrayReceiver(CAA_HANDLE hArrayReceiver, CAA_COUNT ctIndex, CAA_COUNT* pctMsgLeft, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFCL2_READARRAYRECEIVER) (CAA_HANDLE hArrayReceiver, CAA_COUNT ctIndex, CAA_COUNT* pctMsgLeft, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_READARRAYRECEIVER_NOTIMPLEMENTED)
	#define USE_CL2_ReadArrayReceiver
	#define EXT_CL2_ReadArrayReceiver
	#define GET_CL2_ReadArrayReceiver(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_ReadArrayReceiver(p0,p1,p2,p3)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_CL2_ReadArrayReceiver  FALSE
	#define EXP_CL2_ReadArrayReceiver  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_ReadArrayReceiver
	#define EXT_CL2_ReadArrayReceiver
	#define GET_CL2_ReadArrayReceiver(fl)  CAL_CMGETAPI( "CL2_ReadArrayReceiver" ) 
	#define CAL_CL2_ReadArrayReceiver  CL2_ReadArrayReceiver
	#define CHK_CL2_ReadArrayReceiver  TRUE
	#define EXP_CL2_ReadArrayReceiver  CAL_CMEXPAPI( "CL2_ReadArrayReceiver" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_ReadArrayReceiver
	#define EXT_CL2_ReadArrayReceiver
	#define GET_CL2_ReadArrayReceiver(fl)  CAL_CMGETAPI( "CL2_ReadArrayReceiver" ) 
	#define CAL_CL2_ReadArrayReceiver  CL2_ReadArrayReceiver
	#define CHK_CL2_ReadArrayReceiver  TRUE
	#define EXP_CL2_ReadArrayReceiver  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_ReadArrayReceiver", (RTS_UINTPTR)CL2_ReadArrayReceiver, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_ReadArrayReceiver
	#define EXT_CmpCAACanL2CL2_ReadArrayReceiver
	#define GET_CmpCAACanL2CL2_ReadArrayReceiver  ERR_OK
	#define CAL_CmpCAACanL2CL2_ReadArrayReceiver pICmpCAACanL2->ICL2_ReadArrayReceiver
	#define CHK_CmpCAACanL2CL2_ReadArrayReceiver (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_ReadArrayReceiver  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_ReadArrayReceiver
	#define EXT_CL2_ReadArrayReceiver
	#define GET_CL2_ReadArrayReceiver(fl)  CAL_CMGETAPI( "CL2_ReadArrayReceiver" ) 
	#define CAL_CL2_ReadArrayReceiver pICmpCAACanL2->ICL2_ReadArrayReceiver
	#define CHK_CL2_ReadArrayReceiver (pICmpCAACanL2 != NULL)
	#define EXP_CL2_ReadArrayReceiver  CAL_CMEXPAPI( "CL2_ReadArrayReceiver" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_ReadArrayReceiver  PFCL2_READARRAYRECEIVER pfCL2_ReadArrayReceiver;
	#define EXT_CL2_ReadArrayReceiver  extern PFCL2_READARRAYRECEIVER pfCL2_ReadArrayReceiver;
	#define GET_CL2_ReadArrayReceiver(fl)  s_pfCMGetAPI2( "CL2_ReadArrayReceiver", (RTS_VOID_FCTPTR *)&pfCL2_ReadArrayReceiver, (fl), 0, 0)
	#define CAL_CL2_ReadArrayReceiver  pfCL2_ReadArrayReceiver
	#define CHK_CL2_ReadArrayReceiver  (pfCL2_ReadArrayReceiver != NULL)
	#define EXP_CL2_ReadArrayReceiver  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_ReadArrayReceiver", (RTS_UINTPTR)CL2_ReadArrayReceiver, 0, 0) 
#endif



CAA_ERROR CDECL CL2_Write(CAA_HANDLE hDriver, CAA_HANDLE hMessage, unsigned char ucPrio, CAA_BOOL xEnableSyncWindow);
typedef CAA_ERROR (CDECL * PFCL2_WRITE) (CAA_HANDLE hDriver, CAA_HANDLE hMessage, unsigned char ucPrio, CAA_BOOL xEnableSyncWindow);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_WRITE_NOTIMPLEMENTED)
	#define USE_CL2_Write
	#define EXT_CL2_Write
	#define GET_CL2_Write(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_Write(p0,p1,p2,p3)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CL2_Write  FALSE
	#define EXP_CL2_Write  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_Write
	#define EXT_CL2_Write
	#define GET_CL2_Write(fl)  CAL_CMGETAPI( "CL2_Write" ) 
	#define CAL_CL2_Write  CL2_Write
	#define CHK_CL2_Write  TRUE
	#define EXP_CL2_Write  CAL_CMEXPAPI( "CL2_Write" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_Write
	#define EXT_CL2_Write
	#define GET_CL2_Write(fl)  CAL_CMGETAPI( "CL2_Write" ) 
	#define CAL_CL2_Write  CL2_Write
	#define CHK_CL2_Write  TRUE
	#define EXP_CL2_Write  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_Write", (RTS_UINTPTR)CL2_Write, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_Write
	#define EXT_CmpCAACanL2CL2_Write
	#define GET_CmpCAACanL2CL2_Write  ERR_OK
	#define CAL_CmpCAACanL2CL2_Write pICmpCAACanL2->ICL2_Write
	#define CHK_CmpCAACanL2CL2_Write (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_Write  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_Write
	#define EXT_CL2_Write
	#define GET_CL2_Write(fl)  CAL_CMGETAPI( "CL2_Write" ) 
	#define CAL_CL2_Write pICmpCAACanL2->ICL2_Write
	#define CHK_CL2_Write (pICmpCAACanL2 != NULL)
	#define EXP_CL2_Write  CAL_CMEXPAPI( "CL2_Write" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_Write  PFCL2_WRITE pfCL2_Write;
	#define EXT_CL2_Write  extern PFCL2_WRITE pfCL2_Write;
	#define GET_CL2_Write(fl)  s_pfCMGetAPI2( "CL2_Write", (RTS_VOID_FCTPTR *)&pfCL2_Write, (fl), 0, 0)
	#define CAL_CL2_Write  pfCL2_Write
	#define CHK_CL2_Write  (pfCL2_Write != NULL)
	#define EXP_CL2_Write  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_Write", (RTS_UINTPTR)CL2_Write, 0, 0) 
#endif




/* Cyclic Custom Services */
CAA_HANDLE CDECL CL2_CstCycleOpen(CAA_HANDLE hDriver, CAA_ENUM eCstEvent, unsigned short usPrio, CAA_BOOL xEnableSyncWindow, CAA_UDINT ulCstCycle, CAA_UDINT ulCstForewarnTime, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFCL2_CSTCYCLEOPEN) (CAA_HANDLE hDriver, CAA_ENUM eCstEvent, unsigned short usPrio, CAA_BOOL xEnableSyncWindow, CAA_UDINT ulCstCycle, CAA_UDINT ulCstForewarnTime, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CSTCYCLEOPEN_NOTIMPLEMENTED)
	#define USE_CL2_CstCycleOpen
	#define EXT_CL2_CstCycleOpen
	#define GET_CL2_CstCycleOpen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_CstCycleOpen(p0,p1,p2,p3,p4,p5,p6)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_CL2_CstCycleOpen  FALSE
	#define EXP_CL2_CstCycleOpen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_CstCycleOpen
	#define EXT_CL2_CstCycleOpen
	#define GET_CL2_CstCycleOpen(fl)  CAL_CMGETAPI( "CL2_CstCycleOpen" ) 
	#define CAL_CL2_CstCycleOpen  CL2_CstCycleOpen
	#define CHK_CL2_CstCycleOpen  TRUE
	#define EXP_CL2_CstCycleOpen  CAL_CMEXPAPI( "CL2_CstCycleOpen" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_CstCycleOpen
	#define EXT_CL2_CstCycleOpen
	#define GET_CL2_CstCycleOpen(fl)  CAL_CMGETAPI( "CL2_CstCycleOpen" ) 
	#define CAL_CL2_CstCycleOpen  CL2_CstCycleOpen
	#define CHK_CL2_CstCycleOpen  TRUE
	#define EXP_CL2_CstCycleOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CstCycleOpen", (RTS_UINTPTR)CL2_CstCycleOpen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_CstCycleOpen
	#define EXT_CmpCAACanL2CL2_CstCycleOpen
	#define GET_CmpCAACanL2CL2_CstCycleOpen  ERR_OK
	#define CAL_CmpCAACanL2CL2_CstCycleOpen pICmpCAACanL2->ICL2_CstCycleOpen
	#define CHK_CmpCAACanL2CL2_CstCycleOpen (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_CstCycleOpen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_CstCycleOpen
	#define EXT_CL2_CstCycleOpen
	#define GET_CL2_CstCycleOpen(fl)  CAL_CMGETAPI( "CL2_CstCycleOpen" ) 
	#define CAL_CL2_CstCycleOpen pICmpCAACanL2->ICL2_CstCycleOpen
	#define CHK_CL2_CstCycleOpen (pICmpCAACanL2 != NULL)
	#define EXP_CL2_CstCycleOpen  CAL_CMEXPAPI( "CL2_CstCycleOpen" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_CstCycleOpen  PFCL2_CSTCYCLEOPEN pfCL2_CstCycleOpen;
	#define EXT_CL2_CstCycleOpen  extern PFCL2_CSTCYCLEOPEN pfCL2_CstCycleOpen;
	#define GET_CL2_CstCycleOpen(fl)  s_pfCMGetAPI2( "CL2_CstCycleOpen", (RTS_VOID_FCTPTR *)&pfCL2_CstCycleOpen, (fl), 0, 0)
	#define CAL_CL2_CstCycleOpen  pfCL2_CstCycleOpen
	#define CHK_CL2_CstCycleOpen  (pfCL2_CstCycleOpen != NULL)
	#define EXP_CL2_CstCycleOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CstCycleOpen", (RTS_UINTPTR)CL2_CstCycleOpen, 0, 0) 
#endif



CAA_HANDLE CDECL CL2_CstCycleUpdate(CAA_HANDLE hCstCycle, CAA_HANDLE hMessage, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFCL2_CSTCYCLEUPDATE) (CAA_HANDLE hCstCycle, CAA_HANDLE hMessage, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CSTCYCLEUPDATE_NOTIMPLEMENTED)
	#define USE_CL2_CstCycleUpdate
	#define EXT_CL2_CstCycleUpdate
	#define GET_CL2_CstCycleUpdate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_CstCycleUpdate(p0,p1,p2)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_CL2_CstCycleUpdate  FALSE
	#define EXP_CL2_CstCycleUpdate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_CstCycleUpdate
	#define EXT_CL2_CstCycleUpdate
	#define GET_CL2_CstCycleUpdate(fl)  CAL_CMGETAPI( "CL2_CstCycleUpdate" ) 
	#define CAL_CL2_CstCycleUpdate  CL2_CstCycleUpdate
	#define CHK_CL2_CstCycleUpdate  TRUE
	#define EXP_CL2_CstCycleUpdate  CAL_CMEXPAPI( "CL2_CstCycleUpdate" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_CstCycleUpdate
	#define EXT_CL2_CstCycleUpdate
	#define GET_CL2_CstCycleUpdate(fl)  CAL_CMGETAPI( "CL2_CstCycleUpdate" ) 
	#define CAL_CL2_CstCycleUpdate  CL2_CstCycleUpdate
	#define CHK_CL2_CstCycleUpdate  TRUE
	#define EXP_CL2_CstCycleUpdate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CstCycleUpdate", (RTS_UINTPTR)CL2_CstCycleUpdate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_CstCycleUpdate
	#define EXT_CmpCAACanL2CL2_CstCycleUpdate
	#define GET_CmpCAACanL2CL2_CstCycleUpdate  ERR_OK
	#define CAL_CmpCAACanL2CL2_CstCycleUpdate pICmpCAACanL2->ICL2_CstCycleUpdate
	#define CHK_CmpCAACanL2CL2_CstCycleUpdate (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_CstCycleUpdate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_CstCycleUpdate
	#define EXT_CL2_CstCycleUpdate
	#define GET_CL2_CstCycleUpdate(fl)  CAL_CMGETAPI( "CL2_CstCycleUpdate" ) 
	#define CAL_CL2_CstCycleUpdate pICmpCAACanL2->ICL2_CstCycleUpdate
	#define CHK_CL2_CstCycleUpdate (pICmpCAACanL2 != NULL)
	#define EXP_CL2_CstCycleUpdate  CAL_CMEXPAPI( "CL2_CstCycleUpdate" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_CstCycleUpdate  PFCL2_CSTCYCLEUPDATE pfCL2_CstCycleUpdate;
	#define EXT_CL2_CstCycleUpdate  extern PFCL2_CSTCYCLEUPDATE pfCL2_CstCycleUpdate;
	#define GET_CL2_CstCycleUpdate(fl)  s_pfCMGetAPI2( "CL2_CstCycleUpdate", (RTS_VOID_FCTPTR *)&pfCL2_CstCycleUpdate, (fl), 0, 0)
	#define CAL_CL2_CstCycleUpdate  pfCL2_CstCycleUpdate
	#define CHK_CL2_CstCycleUpdate  (pfCL2_CstCycleUpdate != NULL)
	#define EXP_CL2_CstCycleUpdate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CstCycleUpdate", (RTS_UINTPTR)CL2_CstCycleUpdate, 0, 0) 
#endif



CAA_ERROR CDECL CL2_CstCycleStart(CAA_HANDLE hCstCycle);
typedef CAA_ERROR (CDECL * PFCL2_CSTCYCLESTART) (CAA_HANDLE hCstCycle);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CSTCYCLESTART_NOTIMPLEMENTED)
	#define USE_CL2_CstCycleStart
	#define EXT_CL2_CstCycleStart
	#define GET_CL2_CstCycleStart(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_CstCycleStart(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CL2_CstCycleStart  FALSE
	#define EXP_CL2_CstCycleStart  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_CstCycleStart
	#define EXT_CL2_CstCycleStart
	#define GET_CL2_CstCycleStart(fl)  CAL_CMGETAPI( "CL2_CstCycleStart" ) 
	#define CAL_CL2_CstCycleStart  CL2_CstCycleStart
	#define CHK_CL2_CstCycleStart  TRUE
	#define EXP_CL2_CstCycleStart  CAL_CMEXPAPI( "CL2_CstCycleStart" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_CstCycleStart
	#define EXT_CL2_CstCycleStart
	#define GET_CL2_CstCycleStart(fl)  CAL_CMGETAPI( "CL2_CstCycleStart" ) 
	#define CAL_CL2_CstCycleStart  CL2_CstCycleStart
	#define CHK_CL2_CstCycleStart  TRUE
	#define EXP_CL2_CstCycleStart  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CstCycleStart", (RTS_UINTPTR)CL2_CstCycleStart, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_CstCycleStart
	#define EXT_CmpCAACanL2CL2_CstCycleStart
	#define GET_CmpCAACanL2CL2_CstCycleStart  ERR_OK
	#define CAL_CmpCAACanL2CL2_CstCycleStart pICmpCAACanL2->ICL2_CstCycleStart
	#define CHK_CmpCAACanL2CL2_CstCycleStart (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_CstCycleStart  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_CstCycleStart
	#define EXT_CL2_CstCycleStart
	#define GET_CL2_CstCycleStart(fl)  CAL_CMGETAPI( "CL2_CstCycleStart" ) 
	#define CAL_CL2_CstCycleStart pICmpCAACanL2->ICL2_CstCycleStart
	#define CHK_CL2_CstCycleStart (pICmpCAACanL2 != NULL)
	#define EXP_CL2_CstCycleStart  CAL_CMEXPAPI( "CL2_CstCycleStart" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_CstCycleStart  PFCL2_CSTCYCLESTART pfCL2_CstCycleStart;
	#define EXT_CL2_CstCycleStart  extern PFCL2_CSTCYCLESTART pfCL2_CstCycleStart;
	#define GET_CL2_CstCycleStart(fl)  s_pfCMGetAPI2( "CL2_CstCycleStart", (RTS_VOID_FCTPTR *)&pfCL2_CstCycleStart, (fl), 0, 0)
	#define CAL_CL2_CstCycleStart  pfCL2_CstCycleStart
	#define CHK_CL2_CstCycleStart  (pfCL2_CstCycleStart != NULL)
	#define EXP_CL2_CstCycleStart  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CstCycleStart", (RTS_UINTPTR)CL2_CstCycleStart, 0, 0) 
#endif



CAA_ERROR CDECL CL2_CstCycleStop(CAA_HANDLE hCstCycle);
typedef CAA_ERROR (CDECL * PFCL2_CSTCYCLESTOP) (CAA_HANDLE hCstCycle);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CSTCYCLESTOP_NOTIMPLEMENTED)
	#define USE_CL2_CstCycleStop
	#define EXT_CL2_CstCycleStop
	#define GET_CL2_CstCycleStop(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_CstCycleStop(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CL2_CstCycleStop  FALSE
	#define EXP_CL2_CstCycleStop  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_CstCycleStop
	#define EXT_CL2_CstCycleStop
	#define GET_CL2_CstCycleStop(fl)  CAL_CMGETAPI( "CL2_CstCycleStop" ) 
	#define CAL_CL2_CstCycleStop  CL2_CstCycleStop
	#define CHK_CL2_CstCycleStop  TRUE
	#define EXP_CL2_CstCycleStop  CAL_CMEXPAPI( "CL2_CstCycleStop" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_CstCycleStop
	#define EXT_CL2_CstCycleStop
	#define GET_CL2_CstCycleStop(fl)  CAL_CMGETAPI( "CL2_CstCycleStop" ) 
	#define CAL_CL2_CstCycleStop  CL2_CstCycleStop
	#define CHK_CL2_CstCycleStop  TRUE
	#define EXP_CL2_CstCycleStop  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CstCycleStop", (RTS_UINTPTR)CL2_CstCycleStop, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_CstCycleStop
	#define EXT_CmpCAACanL2CL2_CstCycleStop
	#define GET_CmpCAACanL2CL2_CstCycleStop  ERR_OK
	#define CAL_CmpCAACanL2CL2_CstCycleStop pICmpCAACanL2->ICL2_CstCycleStop
	#define CHK_CmpCAACanL2CL2_CstCycleStop (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_CstCycleStop  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_CstCycleStop
	#define EXT_CL2_CstCycleStop
	#define GET_CL2_CstCycleStop(fl)  CAL_CMGETAPI( "CL2_CstCycleStop" ) 
	#define CAL_CL2_CstCycleStop pICmpCAACanL2->ICL2_CstCycleStop
	#define CHK_CL2_CstCycleStop (pICmpCAACanL2 != NULL)
	#define EXP_CL2_CstCycleStop  CAL_CMEXPAPI( "CL2_CstCycleStop" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_CstCycleStop  PFCL2_CSTCYCLESTOP pfCL2_CstCycleStop;
	#define EXT_CL2_CstCycleStop  extern PFCL2_CSTCYCLESTOP pfCL2_CstCycleStop;
	#define GET_CL2_CstCycleStop(fl)  s_pfCMGetAPI2( "CL2_CstCycleStop", (RTS_VOID_FCTPTR *)&pfCL2_CstCycleStop, (fl), 0, 0)
	#define CAL_CL2_CstCycleStop  pfCL2_CstCycleStop
	#define CHK_CL2_CstCycleStop  (pfCL2_CstCycleStop != NULL)
	#define EXP_CL2_CstCycleStop  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CstCycleStop", (RTS_UINTPTR)CL2_CstCycleStop, 0, 0) 
#endif



CAA_HANDLE CDECL CL2_CstCycleClose(CAA_HANDLE hCstCycle, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFCL2_CSTCYCLECLOSE) (CAA_HANDLE hCstCycle, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CSTCYCLECLOSE_NOTIMPLEMENTED)
	#define USE_CL2_CstCycleClose
	#define EXT_CL2_CstCycleClose
	#define GET_CL2_CstCycleClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_CstCycleClose(p0,p1)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_CL2_CstCycleClose  FALSE
	#define EXP_CL2_CstCycleClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_CstCycleClose
	#define EXT_CL2_CstCycleClose
	#define GET_CL2_CstCycleClose(fl)  CAL_CMGETAPI( "CL2_CstCycleClose" ) 
	#define CAL_CL2_CstCycleClose  CL2_CstCycleClose
	#define CHK_CL2_CstCycleClose  TRUE
	#define EXP_CL2_CstCycleClose  CAL_CMEXPAPI( "CL2_CstCycleClose" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_CstCycleClose
	#define EXT_CL2_CstCycleClose
	#define GET_CL2_CstCycleClose(fl)  CAL_CMGETAPI( "CL2_CstCycleClose" ) 
	#define CAL_CL2_CstCycleClose  CL2_CstCycleClose
	#define CHK_CL2_CstCycleClose  TRUE
	#define EXP_CL2_CstCycleClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CstCycleClose", (RTS_UINTPTR)CL2_CstCycleClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_CstCycleClose
	#define EXT_CmpCAACanL2CL2_CstCycleClose
	#define GET_CmpCAACanL2CL2_CstCycleClose  ERR_OK
	#define CAL_CmpCAACanL2CL2_CstCycleClose pICmpCAACanL2->ICL2_CstCycleClose
	#define CHK_CmpCAACanL2CL2_CstCycleClose (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_CstCycleClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_CstCycleClose
	#define EXT_CL2_CstCycleClose
	#define GET_CL2_CstCycleClose(fl)  CAL_CMGETAPI( "CL2_CstCycleClose" ) 
	#define CAL_CL2_CstCycleClose pICmpCAACanL2->ICL2_CstCycleClose
	#define CHK_CL2_CstCycleClose (pICmpCAACanL2 != NULL)
	#define EXP_CL2_CstCycleClose  CAL_CMEXPAPI( "CL2_CstCycleClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_CstCycleClose  PFCL2_CSTCYCLECLOSE pfCL2_CstCycleClose;
	#define EXT_CL2_CstCycleClose  extern PFCL2_CSTCYCLECLOSE pfCL2_CstCycleClose;
	#define GET_CL2_CstCycleClose(fl)  s_pfCMGetAPI2( "CL2_CstCycleClose", (RTS_VOID_FCTPTR *)&pfCL2_CstCycleClose, (fl), 0, 0)
	#define CAL_CL2_CstCycleClose  pfCL2_CstCycleClose
	#define CHK_CL2_CstCycleClose  (pfCL2_CstCycleClose != NULL)
	#define EXP_CL2_CstCycleClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CstCycleClose", (RTS_UINTPTR)CL2_CstCycleClose, 0, 0) 
#endif




/* Diagnostic Information */
unsigned short CDECL CL2_GetBaudrate(CAA_HANDLE hDriver, CAA_ERROR* peError);
typedef unsigned short (CDECL * PFCL2_GETBAUDRATE) (CAA_HANDLE hDriver, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETBAUDRATE_NOTIMPLEMENTED)
	#define USE_CL2_GetBaudrate
	#define EXT_CL2_GetBaudrate
	#define GET_CL2_GetBaudrate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetBaudrate(p0,p1)  (unsigned short)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetBaudrate  FALSE
	#define EXP_CL2_GetBaudrate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetBaudrate
	#define EXT_CL2_GetBaudrate
	#define GET_CL2_GetBaudrate(fl)  CAL_CMGETAPI( "CL2_GetBaudrate" ) 
	#define CAL_CL2_GetBaudrate  CL2_GetBaudrate
	#define CHK_CL2_GetBaudrate  TRUE
	#define EXP_CL2_GetBaudrate  CAL_CMEXPAPI( "CL2_GetBaudrate" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetBaudrate
	#define EXT_CL2_GetBaudrate
	#define GET_CL2_GetBaudrate(fl)  CAL_CMGETAPI( "CL2_GetBaudrate" ) 
	#define CAL_CL2_GetBaudrate  CL2_GetBaudrate
	#define CHK_CL2_GetBaudrate  TRUE
	#define EXP_CL2_GetBaudrate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetBaudrate", (RTS_UINTPTR)CL2_GetBaudrate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetBaudrate
	#define EXT_CmpCAACanL2CL2_GetBaudrate
	#define GET_CmpCAACanL2CL2_GetBaudrate  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetBaudrate pICmpCAACanL2->ICL2_GetBaudrate
	#define CHK_CmpCAACanL2CL2_GetBaudrate (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetBaudrate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetBaudrate
	#define EXT_CL2_GetBaudrate
	#define GET_CL2_GetBaudrate(fl)  CAL_CMGETAPI( "CL2_GetBaudrate" ) 
	#define CAL_CL2_GetBaudrate pICmpCAACanL2->ICL2_GetBaudrate
	#define CHK_CL2_GetBaudrate (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetBaudrate  CAL_CMEXPAPI( "CL2_GetBaudrate" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetBaudrate  PFCL2_GETBAUDRATE pfCL2_GetBaudrate;
	#define EXT_CL2_GetBaudrate  extern PFCL2_GETBAUDRATE pfCL2_GetBaudrate;
	#define GET_CL2_GetBaudrate(fl)  s_pfCMGetAPI2( "CL2_GetBaudrate", (RTS_VOID_FCTPTR *)&pfCL2_GetBaudrate, (fl), 0, 0)
	#define CAL_CL2_GetBaudrate  pfCL2_GetBaudrate
	#define CHK_CL2_GetBaudrate  (pfCL2_GetBaudrate != NULL)
	#define EXP_CL2_GetBaudrate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetBaudrate", (RTS_UINTPTR)CL2_GetBaudrate, 0, 0) 
#endif



unsigned short CDECL CL2_GetBusload(CAA_HANDLE hDriver, CAA_ERROR* peError);
typedef unsigned short (CDECL * PFCL2_GETBUSLOAD) (CAA_HANDLE hDriver, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETBUSLOAD_NOTIMPLEMENTED)
	#define USE_CL2_GetBusload
	#define EXT_CL2_GetBusload
	#define GET_CL2_GetBusload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetBusload(p0,p1)  (unsigned short)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetBusload  FALSE
	#define EXP_CL2_GetBusload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetBusload
	#define EXT_CL2_GetBusload
	#define GET_CL2_GetBusload(fl)  CAL_CMGETAPI( "CL2_GetBusload" ) 
	#define CAL_CL2_GetBusload  CL2_GetBusload
	#define CHK_CL2_GetBusload  TRUE
	#define EXP_CL2_GetBusload  CAL_CMEXPAPI( "CL2_GetBusload" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetBusload
	#define EXT_CL2_GetBusload
	#define GET_CL2_GetBusload(fl)  CAL_CMGETAPI( "CL2_GetBusload" ) 
	#define CAL_CL2_GetBusload  CL2_GetBusload
	#define CHK_CL2_GetBusload  TRUE
	#define EXP_CL2_GetBusload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetBusload", (RTS_UINTPTR)CL2_GetBusload, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetBusload
	#define EXT_CmpCAACanL2CL2_GetBusload
	#define GET_CmpCAACanL2CL2_GetBusload  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetBusload pICmpCAACanL2->ICL2_GetBusload
	#define CHK_CmpCAACanL2CL2_GetBusload (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetBusload  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetBusload
	#define EXT_CL2_GetBusload
	#define GET_CL2_GetBusload(fl)  CAL_CMGETAPI( "CL2_GetBusload" ) 
	#define CAL_CL2_GetBusload pICmpCAACanL2->ICL2_GetBusload
	#define CHK_CL2_GetBusload (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetBusload  CAL_CMEXPAPI( "CL2_GetBusload" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetBusload  PFCL2_GETBUSLOAD pfCL2_GetBusload;
	#define EXT_CL2_GetBusload  extern PFCL2_GETBUSLOAD pfCL2_GetBusload;
	#define GET_CL2_GetBusload(fl)  s_pfCMGetAPI2( "CL2_GetBusload", (RTS_VOID_FCTPTR *)&pfCL2_GetBusload, (fl), 0, 0)
	#define CAL_CL2_GetBusload  pfCL2_GetBusload
	#define CHK_CL2_GetBusload  (pfCL2_GetBusload != NULL)
	#define EXP_CL2_GetBusload  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetBusload", (RTS_UINTPTR)CL2_GetBusload, 0, 0) 
#endif



CAA_ENUM CDECL CL2_GetBusState(CAA_HANDLE hDriver, CAA_ERROR* peError);
typedef CAA_ENUM (CDECL * PFCL2_GETBUSSTATE) (CAA_HANDLE hDriver, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETBUSSTATE_NOTIMPLEMENTED)
	#define USE_CL2_GetBusState
	#define EXT_CL2_GetBusState
	#define GET_CL2_GetBusState(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetBusState(p0,p1)  (CAA_ENUM)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetBusState  FALSE
	#define EXP_CL2_GetBusState  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetBusState
	#define EXT_CL2_GetBusState
	#define GET_CL2_GetBusState(fl)  CAL_CMGETAPI( "CL2_GetBusState" ) 
	#define CAL_CL2_GetBusState  CL2_GetBusState
	#define CHK_CL2_GetBusState  TRUE
	#define EXP_CL2_GetBusState  CAL_CMEXPAPI( "CL2_GetBusState" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetBusState
	#define EXT_CL2_GetBusState
	#define GET_CL2_GetBusState(fl)  CAL_CMGETAPI( "CL2_GetBusState" ) 
	#define CAL_CL2_GetBusState  CL2_GetBusState
	#define CHK_CL2_GetBusState  TRUE
	#define EXP_CL2_GetBusState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetBusState", (RTS_UINTPTR)CL2_GetBusState, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetBusState
	#define EXT_CmpCAACanL2CL2_GetBusState
	#define GET_CmpCAACanL2CL2_GetBusState  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetBusState pICmpCAACanL2->ICL2_GetBusState
	#define CHK_CmpCAACanL2CL2_GetBusState (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetBusState  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetBusState
	#define EXT_CL2_GetBusState
	#define GET_CL2_GetBusState(fl)  CAL_CMGETAPI( "CL2_GetBusState" ) 
	#define CAL_CL2_GetBusState pICmpCAACanL2->ICL2_GetBusState
	#define CHK_CL2_GetBusState (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetBusState  CAL_CMEXPAPI( "CL2_GetBusState" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetBusState  PFCL2_GETBUSSTATE pfCL2_GetBusState;
	#define EXT_CL2_GetBusState  extern PFCL2_GETBUSSTATE pfCL2_GetBusState;
	#define GET_CL2_GetBusState(fl)  s_pfCMGetAPI2( "CL2_GetBusState", (RTS_VOID_FCTPTR *)&pfCL2_GetBusState, (fl), 0, 0)
	#define CAL_CL2_GetBusState  pfCL2_GetBusState
	#define CHK_CL2_GetBusState  (pfCL2_GetBusState != NULL)
	#define EXP_CL2_GetBusState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetBusState", (RTS_UINTPTR)CL2_GetBusState, 0, 0) 
#endif



CAA_COUNT CDECL CL2_GetReceiveCounter(CAA_HANDLE hDriver, CAA_ERROR* peError);
typedef CAA_COUNT (CDECL * PFCL2_GETRECEIVECOUNTER) (CAA_HANDLE hDriver, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETRECEIVECOUNTER_NOTIMPLEMENTED)
	#define USE_CL2_GetReceiveCounter
	#define EXT_CL2_GetReceiveCounter
	#define GET_CL2_GetReceiveCounter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetReceiveCounter(p0,p1)  (CAA_COUNT)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetReceiveCounter  FALSE
	#define EXP_CL2_GetReceiveCounter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetReceiveCounter
	#define EXT_CL2_GetReceiveCounter
	#define GET_CL2_GetReceiveCounter(fl)  CAL_CMGETAPI( "CL2_GetReceiveCounter" ) 
	#define CAL_CL2_GetReceiveCounter  CL2_GetReceiveCounter
	#define CHK_CL2_GetReceiveCounter  TRUE
	#define EXP_CL2_GetReceiveCounter  CAL_CMEXPAPI( "CL2_GetReceiveCounter" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetReceiveCounter
	#define EXT_CL2_GetReceiveCounter
	#define GET_CL2_GetReceiveCounter(fl)  CAL_CMGETAPI( "CL2_GetReceiveCounter" ) 
	#define CAL_CL2_GetReceiveCounter  CL2_GetReceiveCounter
	#define CHK_CL2_GetReceiveCounter  TRUE
	#define EXP_CL2_GetReceiveCounter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetReceiveCounter", (RTS_UINTPTR)CL2_GetReceiveCounter, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetReceiveCounter
	#define EXT_CmpCAACanL2CL2_GetReceiveCounter
	#define GET_CmpCAACanL2CL2_GetReceiveCounter  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetReceiveCounter pICmpCAACanL2->ICL2_GetReceiveCounter
	#define CHK_CmpCAACanL2CL2_GetReceiveCounter (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetReceiveCounter  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetReceiveCounter
	#define EXT_CL2_GetReceiveCounter
	#define GET_CL2_GetReceiveCounter(fl)  CAL_CMGETAPI( "CL2_GetReceiveCounter" ) 
	#define CAL_CL2_GetReceiveCounter pICmpCAACanL2->ICL2_GetReceiveCounter
	#define CHK_CL2_GetReceiveCounter (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetReceiveCounter  CAL_CMEXPAPI( "CL2_GetReceiveCounter" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetReceiveCounter  PFCL2_GETRECEIVECOUNTER pfCL2_GetReceiveCounter;
	#define EXT_CL2_GetReceiveCounter  extern PFCL2_GETRECEIVECOUNTER pfCL2_GetReceiveCounter;
	#define GET_CL2_GetReceiveCounter(fl)  s_pfCMGetAPI2( "CL2_GetReceiveCounter", (RTS_VOID_FCTPTR *)&pfCL2_GetReceiveCounter, (fl), 0, 0)
	#define CAL_CL2_GetReceiveCounter  pfCL2_GetReceiveCounter
	#define CHK_CL2_GetReceiveCounter  (pfCL2_GetReceiveCounter != NULL)
	#define EXP_CL2_GetReceiveCounter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetReceiveCounter", (RTS_UINTPTR)CL2_GetReceiveCounter, 0, 0) 
#endif



CAA_COUNT CDECL CL2_GetLostCounter(CAA_HANDLE hDriver, CAA_ERROR* peError);
typedef CAA_COUNT (CDECL * PFCL2_GETLOSTCOUNTER) (CAA_HANDLE hDriver, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETLOSTCOUNTER_NOTIMPLEMENTED)
	#define USE_CL2_GetLostCounter
	#define EXT_CL2_GetLostCounter
	#define GET_CL2_GetLostCounter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetLostCounter(p0,p1)  (CAA_COUNT)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetLostCounter  FALSE
	#define EXP_CL2_GetLostCounter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetLostCounter
	#define EXT_CL2_GetLostCounter
	#define GET_CL2_GetLostCounter(fl)  CAL_CMGETAPI( "CL2_GetLostCounter" ) 
	#define CAL_CL2_GetLostCounter  CL2_GetLostCounter
	#define CHK_CL2_GetLostCounter  TRUE
	#define EXP_CL2_GetLostCounter  CAL_CMEXPAPI( "CL2_GetLostCounter" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetLostCounter
	#define EXT_CL2_GetLostCounter
	#define GET_CL2_GetLostCounter(fl)  CAL_CMGETAPI( "CL2_GetLostCounter" ) 
	#define CAL_CL2_GetLostCounter  CL2_GetLostCounter
	#define CHK_CL2_GetLostCounter  TRUE
	#define EXP_CL2_GetLostCounter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetLostCounter", (RTS_UINTPTR)CL2_GetLostCounter, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetLostCounter
	#define EXT_CmpCAACanL2CL2_GetLostCounter
	#define GET_CmpCAACanL2CL2_GetLostCounter  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetLostCounter pICmpCAACanL2->ICL2_GetLostCounter
	#define CHK_CmpCAACanL2CL2_GetLostCounter (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetLostCounter  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetLostCounter
	#define EXT_CL2_GetLostCounter
	#define GET_CL2_GetLostCounter(fl)  CAL_CMGETAPI( "CL2_GetLostCounter" ) 
	#define CAL_CL2_GetLostCounter pICmpCAACanL2->ICL2_GetLostCounter
	#define CHK_CL2_GetLostCounter (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetLostCounter  CAL_CMEXPAPI( "CL2_GetLostCounter" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetLostCounter  PFCL2_GETLOSTCOUNTER pfCL2_GetLostCounter;
	#define EXT_CL2_GetLostCounter  extern PFCL2_GETLOSTCOUNTER pfCL2_GetLostCounter;
	#define GET_CL2_GetLostCounter(fl)  s_pfCMGetAPI2( "CL2_GetLostCounter", (RTS_VOID_FCTPTR *)&pfCL2_GetLostCounter, (fl), 0, 0)
	#define CAL_CL2_GetLostCounter  pfCL2_GetLostCounter
	#define CHK_CL2_GetLostCounter  (pfCL2_GetLostCounter != NULL)
	#define EXP_CL2_GetLostCounter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetLostCounter", (RTS_UINTPTR)CL2_GetLostCounter, 0, 0) 
#endif



CAA_COUNT CDECL CL2_GetTransmitCounter(CAA_HANDLE hDriver, CAA_ERROR* peError);
typedef CAA_COUNT (CDECL * PFCL2_GETTRANSMITCOUNTER) (CAA_HANDLE hDriver, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETTRANSMITCOUNTER_NOTIMPLEMENTED)
	#define USE_CL2_GetTransmitCounter
	#define EXT_CL2_GetTransmitCounter
	#define GET_CL2_GetTransmitCounter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetTransmitCounter(p0,p1)  (CAA_COUNT)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetTransmitCounter  FALSE
	#define EXP_CL2_GetTransmitCounter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetTransmitCounter
	#define EXT_CL2_GetTransmitCounter
	#define GET_CL2_GetTransmitCounter(fl)  CAL_CMGETAPI( "CL2_GetTransmitCounter" ) 
	#define CAL_CL2_GetTransmitCounter  CL2_GetTransmitCounter
	#define CHK_CL2_GetTransmitCounter  TRUE
	#define EXP_CL2_GetTransmitCounter  CAL_CMEXPAPI( "CL2_GetTransmitCounter" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetTransmitCounter
	#define EXT_CL2_GetTransmitCounter
	#define GET_CL2_GetTransmitCounter(fl)  CAL_CMGETAPI( "CL2_GetTransmitCounter" ) 
	#define CAL_CL2_GetTransmitCounter  CL2_GetTransmitCounter
	#define CHK_CL2_GetTransmitCounter  TRUE
	#define EXP_CL2_GetTransmitCounter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetTransmitCounter", (RTS_UINTPTR)CL2_GetTransmitCounter, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetTransmitCounter
	#define EXT_CmpCAACanL2CL2_GetTransmitCounter
	#define GET_CmpCAACanL2CL2_GetTransmitCounter  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetTransmitCounter pICmpCAACanL2->ICL2_GetTransmitCounter
	#define CHK_CmpCAACanL2CL2_GetTransmitCounter (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetTransmitCounter  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetTransmitCounter
	#define EXT_CL2_GetTransmitCounter
	#define GET_CL2_GetTransmitCounter(fl)  CAL_CMGETAPI( "CL2_GetTransmitCounter" ) 
	#define CAL_CL2_GetTransmitCounter pICmpCAACanL2->ICL2_GetTransmitCounter
	#define CHK_CL2_GetTransmitCounter (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetTransmitCounter  CAL_CMEXPAPI( "CL2_GetTransmitCounter" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetTransmitCounter  PFCL2_GETTRANSMITCOUNTER pfCL2_GetTransmitCounter;
	#define EXT_CL2_GetTransmitCounter  extern PFCL2_GETTRANSMITCOUNTER pfCL2_GetTransmitCounter;
	#define GET_CL2_GetTransmitCounter(fl)  s_pfCMGetAPI2( "CL2_GetTransmitCounter", (RTS_VOID_FCTPTR *)&pfCL2_GetTransmitCounter, (fl), 0, 0)
	#define CAL_CL2_GetTransmitCounter  pfCL2_GetTransmitCounter
	#define CHK_CL2_GetTransmitCounter  (pfCL2_GetTransmitCounter != NULL)
	#define EXP_CL2_GetTransmitCounter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetTransmitCounter", (RTS_UINTPTR)CL2_GetTransmitCounter, 0, 0) 
#endif



CAA_COUNT CDECL CL2_GetTransmitErrorCounter(CAA_HANDLE hDriver, CAA_ERROR* peError);
typedef CAA_COUNT (CDECL * PFCL2_GETTRANSMITERRORCOUNTER) (CAA_HANDLE hDriver, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETTRANSMITERRORCOUNTER_NOTIMPLEMENTED)
	#define USE_CL2_GetTransmitErrorCounter
	#define EXT_CL2_GetTransmitErrorCounter
	#define GET_CL2_GetTransmitErrorCounter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetTransmitErrorCounter(p0,p1)  (CAA_COUNT)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetTransmitErrorCounter  FALSE
	#define EXP_CL2_GetTransmitErrorCounter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetTransmitErrorCounter
	#define EXT_CL2_GetTransmitErrorCounter
	#define GET_CL2_GetTransmitErrorCounter(fl)  CAL_CMGETAPI( "CL2_GetTransmitErrorCounter" ) 
	#define CAL_CL2_GetTransmitErrorCounter  CL2_GetTransmitErrorCounter
	#define CHK_CL2_GetTransmitErrorCounter  TRUE
	#define EXP_CL2_GetTransmitErrorCounter  CAL_CMEXPAPI( "CL2_GetTransmitErrorCounter" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetTransmitErrorCounter
	#define EXT_CL2_GetTransmitErrorCounter
	#define GET_CL2_GetTransmitErrorCounter(fl)  CAL_CMGETAPI( "CL2_GetTransmitErrorCounter" ) 
	#define CAL_CL2_GetTransmitErrorCounter  CL2_GetTransmitErrorCounter
	#define CHK_CL2_GetTransmitErrorCounter  TRUE
	#define EXP_CL2_GetTransmitErrorCounter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetTransmitErrorCounter", (RTS_UINTPTR)CL2_GetTransmitErrorCounter, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetTransmitErrorCounter
	#define EXT_CmpCAACanL2CL2_GetTransmitErrorCounter
	#define GET_CmpCAACanL2CL2_GetTransmitErrorCounter  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetTransmitErrorCounter pICmpCAACanL2->ICL2_GetTransmitErrorCounter
	#define CHK_CmpCAACanL2CL2_GetTransmitErrorCounter (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetTransmitErrorCounter  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetTransmitErrorCounter
	#define EXT_CL2_GetTransmitErrorCounter
	#define GET_CL2_GetTransmitErrorCounter(fl)  CAL_CMGETAPI( "CL2_GetTransmitErrorCounter" ) 
	#define CAL_CL2_GetTransmitErrorCounter pICmpCAACanL2->ICL2_GetTransmitErrorCounter
	#define CHK_CL2_GetTransmitErrorCounter (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetTransmitErrorCounter  CAL_CMEXPAPI( "CL2_GetTransmitErrorCounter" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetTransmitErrorCounter  PFCL2_GETTRANSMITERRORCOUNTER pfCL2_GetTransmitErrorCounter;
	#define EXT_CL2_GetTransmitErrorCounter  extern PFCL2_GETTRANSMITERRORCOUNTER pfCL2_GetTransmitErrorCounter;
	#define GET_CL2_GetTransmitErrorCounter(fl)  s_pfCMGetAPI2( "CL2_GetTransmitErrorCounter", (RTS_VOID_FCTPTR *)&pfCL2_GetTransmitErrorCounter, (fl), 0, 0)
	#define CAL_CL2_GetTransmitErrorCounter  pfCL2_GetTransmitErrorCounter
	#define CHK_CL2_GetTransmitErrorCounter  (pfCL2_GetTransmitErrorCounter != NULL)
	#define EXP_CL2_GetTransmitErrorCounter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetTransmitErrorCounter", (RTS_UINTPTR)CL2_GetTransmitErrorCounter, 0, 0) 
#endif



CAA_COUNT CDECL CL2_GetReceiveErrorCounter(CAA_HANDLE hDriver, CAA_ERROR* peError);
typedef CAA_COUNT (CDECL * PFCL2_GETRECEIVEERRORCOUNTER) (CAA_HANDLE hDriver, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETRECEIVEERRORCOUNTER_NOTIMPLEMENTED)
	#define USE_CL2_GetReceiveErrorCounter
	#define EXT_CL2_GetReceiveErrorCounter
	#define GET_CL2_GetReceiveErrorCounter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetReceiveErrorCounter(p0,p1)  (CAA_COUNT)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetReceiveErrorCounter  FALSE
	#define EXP_CL2_GetReceiveErrorCounter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetReceiveErrorCounter
	#define EXT_CL2_GetReceiveErrorCounter
	#define GET_CL2_GetReceiveErrorCounter(fl)  CAL_CMGETAPI( "CL2_GetReceiveErrorCounter" ) 
	#define CAL_CL2_GetReceiveErrorCounter  CL2_GetReceiveErrorCounter
	#define CHK_CL2_GetReceiveErrorCounter  TRUE
	#define EXP_CL2_GetReceiveErrorCounter  CAL_CMEXPAPI( "CL2_GetReceiveErrorCounter" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetReceiveErrorCounter
	#define EXT_CL2_GetReceiveErrorCounter
	#define GET_CL2_GetReceiveErrorCounter(fl)  CAL_CMGETAPI( "CL2_GetReceiveErrorCounter" ) 
	#define CAL_CL2_GetReceiveErrorCounter  CL2_GetReceiveErrorCounter
	#define CHK_CL2_GetReceiveErrorCounter  TRUE
	#define EXP_CL2_GetReceiveErrorCounter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetReceiveErrorCounter", (RTS_UINTPTR)CL2_GetReceiveErrorCounter, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetReceiveErrorCounter
	#define EXT_CmpCAACanL2CL2_GetReceiveErrorCounter
	#define GET_CmpCAACanL2CL2_GetReceiveErrorCounter  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetReceiveErrorCounter pICmpCAACanL2->ICL2_GetReceiveErrorCounter
	#define CHK_CmpCAACanL2CL2_GetReceiveErrorCounter (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetReceiveErrorCounter  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetReceiveErrorCounter
	#define EXT_CL2_GetReceiveErrorCounter
	#define GET_CL2_GetReceiveErrorCounter(fl)  CAL_CMGETAPI( "CL2_GetReceiveErrorCounter" ) 
	#define CAL_CL2_GetReceiveErrorCounter pICmpCAACanL2->ICL2_GetReceiveErrorCounter
	#define CHK_CL2_GetReceiveErrorCounter (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetReceiveErrorCounter  CAL_CMEXPAPI( "CL2_GetReceiveErrorCounter" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetReceiveErrorCounter  PFCL2_GETRECEIVEERRORCOUNTER pfCL2_GetReceiveErrorCounter;
	#define EXT_CL2_GetReceiveErrorCounter  extern PFCL2_GETRECEIVEERRORCOUNTER pfCL2_GetReceiveErrorCounter;
	#define GET_CL2_GetReceiveErrorCounter(fl)  s_pfCMGetAPI2( "CL2_GetReceiveErrorCounter", (RTS_VOID_FCTPTR *)&pfCL2_GetReceiveErrorCounter, (fl), 0, 0)
	#define CAL_CL2_GetReceiveErrorCounter  pfCL2_GetReceiveErrorCounter
	#define CHK_CL2_GetReceiveErrorCounter  (pfCL2_GetReceiveErrorCounter != NULL)
	#define EXP_CL2_GetReceiveErrorCounter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetReceiveErrorCounter", (RTS_UINTPTR)CL2_GetReceiveErrorCounter, 0, 0) 
#endif



CAA_BOOL CDECL CL2_IsSendingActive(CAA_HANDLE hDriver, CAA_ERROR* peError);
typedef CAA_BOOL (CDECL * PFCL2_ISSENDINGACTIVE) (CAA_HANDLE hDriver, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_ISSENDINGACTIVE_NOTIMPLEMENTED)
	#define USE_CL2_IsSendingActive
	#define EXT_CL2_IsSendingActive
	#define GET_CL2_IsSendingActive(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_IsSendingActive(p0,p1)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_CL2_IsSendingActive  FALSE
	#define EXP_CL2_IsSendingActive  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_IsSendingActive
	#define EXT_CL2_IsSendingActive
	#define GET_CL2_IsSendingActive(fl)  CAL_CMGETAPI( "CL2_IsSendingActive" ) 
	#define CAL_CL2_IsSendingActive  CL2_IsSendingActive
	#define CHK_CL2_IsSendingActive  TRUE
	#define EXP_CL2_IsSendingActive  CAL_CMEXPAPI( "CL2_IsSendingActive" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_IsSendingActive
	#define EXT_CL2_IsSendingActive
	#define GET_CL2_IsSendingActive(fl)  CAL_CMGETAPI( "CL2_IsSendingActive" ) 
	#define CAL_CL2_IsSendingActive  CL2_IsSendingActive
	#define CHK_CL2_IsSendingActive  TRUE
	#define EXP_CL2_IsSendingActive  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_IsSendingActive", (RTS_UINTPTR)CL2_IsSendingActive, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_IsSendingActive
	#define EXT_CmpCAACanL2CL2_IsSendingActive
	#define GET_CmpCAACanL2CL2_IsSendingActive  ERR_OK
	#define CAL_CmpCAACanL2CL2_IsSendingActive pICmpCAACanL2->ICL2_IsSendingActive
	#define CHK_CmpCAACanL2CL2_IsSendingActive (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_IsSendingActive  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_IsSendingActive
	#define EXT_CL2_IsSendingActive
	#define GET_CL2_IsSendingActive(fl)  CAL_CMGETAPI( "CL2_IsSendingActive" ) 
	#define CAL_CL2_IsSendingActive pICmpCAACanL2->ICL2_IsSendingActive
	#define CHK_CL2_IsSendingActive (pICmpCAACanL2 != NULL)
	#define EXP_CL2_IsSendingActive  CAL_CMEXPAPI( "CL2_IsSendingActive" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_IsSendingActive  PFCL2_ISSENDINGACTIVE pfCL2_IsSendingActive;
	#define EXT_CL2_IsSendingActive  extern PFCL2_ISSENDINGACTIVE pfCL2_IsSendingActive;
	#define GET_CL2_IsSendingActive(fl)  s_pfCMGetAPI2( "CL2_IsSendingActive", (RTS_VOID_FCTPTR *)&pfCL2_IsSendingActive, (fl), 0, 0)
	#define CAL_CL2_IsSendingActive  pfCL2_IsSendingActive
	#define CHK_CL2_IsSendingActive  (pfCL2_IsSendingActive != NULL)
	#define EXP_CL2_IsSendingActive  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_IsSendingActive", (RTS_UINTPTR)CL2_IsSendingActive, 0, 0) 
#endif



CAA_BOOL CDECL CL2_GetBusAlarm(CAA_HANDLE hDriver, CAA_ERROR* peError);
typedef CAA_BOOL (CDECL * PFCL2_GETBUSALARM) (CAA_HANDLE hDriver, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETBUSALARM_NOTIMPLEMENTED)
	#define USE_CL2_GetBusAlarm
	#define EXT_CL2_GetBusAlarm
	#define GET_CL2_GetBusAlarm(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetBusAlarm(p0,p1)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetBusAlarm  FALSE
	#define EXP_CL2_GetBusAlarm  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetBusAlarm
	#define EXT_CL2_GetBusAlarm
	#define GET_CL2_GetBusAlarm(fl)  CAL_CMGETAPI( "CL2_GetBusAlarm" ) 
	#define CAL_CL2_GetBusAlarm  CL2_GetBusAlarm
	#define CHK_CL2_GetBusAlarm  TRUE
	#define EXP_CL2_GetBusAlarm  CAL_CMEXPAPI( "CL2_GetBusAlarm" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetBusAlarm
	#define EXT_CL2_GetBusAlarm
	#define GET_CL2_GetBusAlarm(fl)  CAL_CMGETAPI( "CL2_GetBusAlarm" ) 
	#define CAL_CL2_GetBusAlarm  CL2_GetBusAlarm
	#define CHK_CL2_GetBusAlarm  TRUE
	#define EXP_CL2_GetBusAlarm  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetBusAlarm", (RTS_UINTPTR)CL2_GetBusAlarm, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetBusAlarm
	#define EXT_CmpCAACanL2CL2_GetBusAlarm
	#define GET_CmpCAACanL2CL2_GetBusAlarm  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetBusAlarm pICmpCAACanL2->ICL2_GetBusAlarm
	#define CHK_CmpCAACanL2CL2_GetBusAlarm (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetBusAlarm  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetBusAlarm
	#define EXT_CL2_GetBusAlarm
	#define GET_CL2_GetBusAlarm(fl)  CAL_CMGETAPI( "CL2_GetBusAlarm" ) 
	#define CAL_CL2_GetBusAlarm pICmpCAACanL2->ICL2_GetBusAlarm
	#define CHK_CL2_GetBusAlarm (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetBusAlarm  CAL_CMEXPAPI( "CL2_GetBusAlarm" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetBusAlarm  PFCL2_GETBUSALARM pfCL2_GetBusAlarm;
	#define EXT_CL2_GetBusAlarm  extern PFCL2_GETBUSALARM pfCL2_GetBusAlarm;
	#define GET_CL2_GetBusAlarm(fl)  s_pfCMGetAPI2( "CL2_GetBusAlarm", (RTS_VOID_FCTPTR *)&pfCL2_GetBusAlarm, (fl), 0, 0)
	#define CAL_CL2_GetBusAlarm  pfCL2_GetBusAlarm
	#define CHK_CL2_GetBusAlarm  (pfCL2_GetBusAlarm != NULL)
	#define EXP_CL2_GetBusAlarm  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetBusAlarm", (RTS_UINTPTR)CL2_GetBusAlarm, 0, 0) 
#endif



CAA_ERROR CDECL CL2_ResetBusAlarm(CAA_HANDLE hDriver);
typedef CAA_ERROR (CDECL * PFCL2_RESETBUSALARM) (CAA_HANDLE hDriver);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_RESETBUSALARM_NOTIMPLEMENTED)
	#define USE_CL2_ResetBusAlarm
	#define EXT_CL2_ResetBusAlarm
	#define GET_CL2_ResetBusAlarm(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_ResetBusAlarm(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CL2_ResetBusAlarm  FALSE
	#define EXP_CL2_ResetBusAlarm  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_ResetBusAlarm
	#define EXT_CL2_ResetBusAlarm
	#define GET_CL2_ResetBusAlarm(fl)  CAL_CMGETAPI( "CL2_ResetBusAlarm" ) 
	#define CAL_CL2_ResetBusAlarm  CL2_ResetBusAlarm
	#define CHK_CL2_ResetBusAlarm  TRUE
	#define EXP_CL2_ResetBusAlarm  CAL_CMEXPAPI( "CL2_ResetBusAlarm" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_ResetBusAlarm
	#define EXT_CL2_ResetBusAlarm
	#define GET_CL2_ResetBusAlarm(fl)  CAL_CMGETAPI( "CL2_ResetBusAlarm" ) 
	#define CAL_CL2_ResetBusAlarm  CL2_ResetBusAlarm
	#define CHK_CL2_ResetBusAlarm  TRUE
	#define EXP_CL2_ResetBusAlarm  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_ResetBusAlarm", (RTS_UINTPTR)CL2_ResetBusAlarm, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_ResetBusAlarm
	#define EXT_CmpCAACanL2CL2_ResetBusAlarm
	#define GET_CmpCAACanL2CL2_ResetBusAlarm  ERR_OK
	#define CAL_CmpCAACanL2CL2_ResetBusAlarm pICmpCAACanL2->ICL2_ResetBusAlarm
	#define CHK_CmpCAACanL2CL2_ResetBusAlarm (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_ResetBusAlarm  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_ResetBusAlarm
	#define EXT_CL2_ResetBusAlarm
	#define GET_CL2_ResetBusAlarm(fl)  CAL_CMGETAPI( "CL2_ResetBusAlarm" ) 
	#define CAL_CL2_ResetBusAlarm pICmpCAACanL2->ICL2_ResetBusAlarm
	#define CHK_CL2_ResetBusAlarm (pICmpCAACanL2 != NULL)
	#define EXP_CL2_ResetBusAlarm  CAL_CMEXPAPI( "CL2_ResetBusAlarm" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_ResetBusAlarm  PFCL2_RESETBUSALARM pfCL2_ResetBusAlarm;
	#define EXT_CL2_ResetBusAlarm  extern PFCL2_RESETBUSALARM pfCL2_ResetBusAlarm;
	#define GET_CL2_ResetBusAlarm(fl)  s_pfCMGetAPI2( "CL2_ResetBusAlarm", (RTS_VOID_FCTPTR *)&pfCL2_ResetBusAlarm, (fl), 0, 0)
	#define CAL_CL2_ResetBusAlarm  pfCL2_ResetBusAlarm
	#define CHK_CL2_ResetBusAlarm  (pfCL2_ResetBusAlarm != NULL)
	#define EXP_CL2_ResetBusAlarm  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_ResetBusAlarm", (RTS_UINTPTR)CL2_ResetBusAlarm, 0, 0) 
#endif



CAA_COUNT CDECL CL2_GetTransmitQueueLength(CAA_HANDLE hDriver, CAA_ERROR* peError);
typedef CAA_COUNT (CDECL * PFCL2_GETTRANSMITQUEUELENGTH) (CAA_HANDLE hDriver, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETTRANSMITQUEUELENGTH_NOTIMPLEMENTED)
	#define USE_CL2_GetTransmitQueueLength
	#define EXT_CL2_GetTransmitQueueLength
	#define GET_CL2_GetTransmitQueueLength(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetTransmitQueueLength(p0,p1)  (CAA_COUNT)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetTransmitQueueLength  FALSE
	#define EXP_CL2_GetTransmitQueueLength  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetTransmitQueueLength
	#define EXT_CL2_GetTransmitQueueLength
	#define GET_CL2_GetTransmitQueueLength(fl)  CAL_CMGETAPI( "CL2_GetTransmitQueueLength" ) 
	#define CAL_CL2_GetTransmitQueueLength  CL2_GetTransmitQueueLength
	#define CHK_CL2_GetTransmitQueueLength  TRUE
	#define EXP_CL2_GetTransmitQueueLength  CAL_CMEXPAPI( "CL2_GetTransmitQueueLength" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetTransmitQueueLength
	#define EXT_CL2_GetTransmitQueueLength
	#define GET_CL2_GetTransmitQueueLength(fl)  CAL_CMGETAPI( "CL2_GetTransmitQueueLength" ) 
	#define CAL_CL2_GetTransmitQueueLength  CL2_GetTransmitQueueLength
	#define CHK_CL2_GetTransmitQueueLength  TRUE
	#define EXP_CL2_GetTransmitQueueLength  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetTransmitQueueLength", (RTS_UINTPTR)CL2_GetTransmitQueueLength, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetTransmitQueueLength
	#define EXT_CmpCAACanL2CL2_GetTransmitQueueLength
	#define GET_CmpCAACanL2CL2_GetTransmitQueueLength  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetTransmitQueueLength pICmpCAACanL2->ICL2_GetTransmitQueueLength
	#define CHK_CmpCAACanL2CL2_GetTransmitQueueLength (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetTransmitQueueLength  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetTransmitQueueLength
	#define EXT_CL2_GetTransmitQueueLength
	#define GET_CL2_GetTransmitQueueLength(fl)  CAL_CMGETAPI( "CL2_GetTransmitQueueLength" ) 
	#define CAL_CL2_GetTransmitQueueLength pICmpCAACanL2->ICL2_GetTransmitQueueLength
	#define CHK_CL2_GetTransmitQueueLength (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetTransmitQueueLength  CAL_CMEXPAPI( "CL2_GetTransmitQueueLength" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetTransmitQueueLength  PFCL2_GETTRANSMITQUEUELENGTH pfCL2_GetTransmitQueueLength;
	#define EXT_CL2_GetTransmitQueueLength  extern PFCL2_GETTRANSMITQUEUELENGTH pfCL2_GetTransmitQueueLength;
	#define GET_CL2_GetTransmitQueueLength(fl)  s_pfCMGetAPI2( "CL2_GetTransmitQueueLength", (RTS_VOID_FCTPTR *)&pfCL2_GetTransmitQueueLength, (fl), 0, 0)
	#define CAL_CL2_GetTransmitQueueLength  pfCL2_GetTransmitQueueLength
	#define CHK_CL2_GetTransmitQueueLength  (pfCL2_GetTransmitQueueLength != NULL)
	#define EXP_CL2_GetTransmitQueueLength  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetTransmitQueueLength", (RTS_UINTPTR)CL2_GetTransmitQueueLength, 0, 0) 
#endif



CAA_COUNT CDECL CL2_GetReceiveQueueLength(CAA_HANDLE hDriver, CAA_ERROR* peError);
typedef CAA_COUNT (CDECL * PFCL2_GETRECEIVEQUEUELENGTH) (CAA_HANDLE hDriver, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETRECEIVEQUEUELENGTH_NOTIMPLEMENTED)
	#define USE_CL2_GetReceiveQueueLength
	#define EXT_CL2_GetReceiveQueueLength
	#define GET_CL2_GetReceiveQueueLength(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetReceiveQueueLength(p0,p1)  (CAA_COUNT)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetReceiveQueueLength  FALSE
	#define EXP_CL2_GetReceiveQueueLength  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetReceiveQueueLength
	#define EXT_CL2_GetReceiveQueueLength
	#define GET_CL2_GetReceiveQueueLength(fl)  CAL_CMGETAPI( "CL2_GetReceiveQueueLength" ) 
	#define CAL_CL2_GetReceiveQueueLength  CL2_GetReceiveQueueLength
	#define CHK_CL2_GetReceiveQueueLength  TRUE
	#define EXP_CL2_GetReceiveQueueLength  CAL_CMEXPAPI( "CL2_GetReceiveQueueLength" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetReceiveQueueLength
	#define EXT_CL2_GetReceiveQueueLength
	#define GET_CL2_GetReceiveQueueLength(fl)  CAL_CMGETAPI( "CL2_GetReceiveQueueLength" ) 
	#define CAL_CL2_GetReceiveQueueLength  CL2_GetReceiveQueueLength
	#define CHK_CL2_GetReceiveQueueLength  TRUE
	#define EXP_CL2_GetReceiveQueueLength  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetReceiveQueueLength", (RTS_UINTPTR)CL2_GetReceiveQueueLength, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetReceiveQueueLength
	#define EXT_CmpCAACanL2CL2_GetReceiveQueueLength
	#define GET_CmpCAACanL2CL2_GetReceiveQueueLength  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetReceiveQueueLength pICmpCAACanL2->ICL2_GetReceiveQueueLength
	#define CHK_CmpCAACanL2CL2_GetReceiveQueueLength (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetReceiveQueueLength  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetReceiveQueueLength
	#define EXT_CL2_GetReceiveQueueLength
	#define GET_CL2_GetReceiveQueueLength(fl)  CAL_CMGETAPI( "CL2_GetReceiveQueueLength" ) 
	#define CAL_CL2_GetReceiveQueueLength pICmpCAACanL2->ICL2_GetReceiveQueueLength
	#define CHK_CL2_GetReceiveQueueLength (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetReceiveQueueLength  CAL_CMEXPAPI( "CL2_GetReceiveQueueLength" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetReceiveQueueLength  PFCL2_GETRECEIVEQUEUELENGTH pfCL2_GetReceiveQueueLength;
	#define EXT_CL2_GetReceiveQueueLength  extern PFCL2_GETRECEIVEQUEUELENGTH pfCL2_GetReceiveQueueLength;
	#define GET_CL2_GetReceiveQueueLength(fl)  s_pfCMGetAPI2( "CL2_GetReceiveQueueLength", (RTS_VOID_FCTPTR *)&pfCL2_GetReceiveQueueLength, (fl), 0, 0)
	#define CAL_CL2_GetReceiveQueueLength  pfCL2_GetReceiveQueueLength
	#define CHK_CL2_GetReceiveQueueLength  (pfCL2_GetReceiveQueueLength != NULL)
	#define EXP_CL2_GetReceiveQueueLength  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetReceiveQueueLength", (RTS_UINTPTR)CL2_GetReceiveQueueLength, 0, 0) 
#endif



CAA_COUNT CDECL CL2_GetTransmitPoolSize(CAA_HANDLE hDriver, CAA_ERROR* peError);
typedef CAA_COUNT (CDECL * PFCL2_GETTRANSMITPOOLSIZE) (CAA_HANDLE hDriver, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETTRANSMITPOOLSIZE_NOTIMPLEMENTED)
	#define USE_CL2_GetTransmitPoolSize
	#define EXT_CL2_GetTransmitPoolSize
	#define GET_CL2_GetTransmitPoolSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetTransmitPoolSize(p0,p1)  (CAA_COUNT)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetTransmitPoolSize  FALSE
	#define EXP_CL2_GetTransmitPoolSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetTransmitPoolSize
	#define EXT_CL2_GetTransmitPoolSize
	#define GET_CL2_GetTransmitPoolSize(fl)  CAL_CMGETAPI( "CL2_GetTransmitPoolSize" ) 
	#define CAL_CL2_GetTransmitPoolSize  CL2_GetTransmitPoolSize
	#define CHK_CL2_GetTransmitPoolSize  TRUE
	#define EXP_CL2_GetTransmitPoolSize  CAL_CMEXPAPI( "CL2_GetTransmitPoolSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetTransmitPoolSize
	#define EXT_CL2_GetTransmitPoolSize
	#define GET_CL2_GetTransmitPoolSize(fl)  CAL_CMGETAPI( "CL2_GetTransmitPoolSize" ) 
	#define CAL_CL2_GetTransmitPoolSize  CL2_GetTransmitPoolSize
	#define CHK_CL2_GetTransmitPoolSize  TRUE
	#define EXP_CL2_GetTransmitPoolSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetTransmitPoolSize", (RTS_UINTPTR)CL2_GetTransmitPoolSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetTransmitPoolSize
	#define EXT_CmpCAACanL2CL2_GetTransmitPoolSize
	#define GET_CmpCAACanL2CL2_GetTransmitPoolSize  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetTransmitPoolSize pICmpCAACanL2->ICL2_GetTransmitPoolSize
	#define CHK_CmpCAACanL2CL2_GetTransmitPoolSize (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetTransmitPoolSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetTransmitPoolSize
	#define EXT_CL2_GetTransmitPoolSize
	#define GET_CL2_GetTransmitPoolSize(fl)  CAL_CMGETAPI( "CL2_GetTransmitPoolSize" ) 
	#define CAL_CL2_GetTransmitPoolSize pICmpCAACanL2->ICL2_GetTransmitPoolSize
	#define CHK_CL2_GetTransmitPoolSize (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetTransmitPoolSize  CAL_CMEXPAPI( "CL2_GetTransmitPoolSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetTransmitPoolSize  PFCL2_GETTRANSMITPOOLSIZE pfCL2_GetTransmitPoolSize;
	#define EXT_CL2_GetTransmitPoolSize  extern PFCL2_GETTRANSMITPOOLSIZE pfCL2_GetTransmitPoolSize;
	#define GET_CL2_GetTransmitPoolSize(fl)  s_pfCMGetAPI2( "CL2_GetTransmitPoolSize", (RTS_VOID_FCTPTR *)&pfCL2_GetTransmitPoolSize, (fl), 0, 0)
	#define CAL_CL2_GetTransmitPoolSize  pfCL2_GetTransmitPoolSize
	#define CHK_CL2_GetTransmitPoolSize  (pfCL2_GetTransmitPoolSize != NULL)
	#define EXP_CL2_GetTransmitPoolSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetTransmitPoolSize", (RTS_UINTPTR)CL2_GetTransmitPoolSize, 0, 0) 
#endif



CAA_COUNT CDECL CL2_GetReceivePoolSize(CAA_HANDLE hDriver, CAA_ERROR* peError);
typedef CAA_COUNT (CDECL * PFCL2_GETRECEIVEPOOLSIZE) (CAA_HANDLE hDriver, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETRECEIVEPOOLSIZE_NOTIMPLEMENTED)
	#define USE_CL2_GetReceivePoolSize
	#define EXT_CL2_GetReceivePoolSize
	#define GET_CL2_GetReceivePoolSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetReceivePoolSize(p0,p1)  (CAA_COUNT)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetReceivePoolSize  FALSE
	#define EXP_CL2_GetReceivePoolSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetReceivePoolSize
	#define EXT_CL2_GetReceivePoolSize
	#define GET_CL2_GetReceivePoolSize(fl)  CAL_CMGETAPI( "CL2_GetReceivePoolSize" ) 
	#define CAL_CL2_GetReceivePoolSize  CL2_GetReceivePoolSize
	#define CHK_CL2_GetReceivePoolSize  TRUE
	#define EXP_CL2_GetReceivePoolSize  CAL_CMEXPAPI( "CL2_GetReceivePoolSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetReceivePoolSize
	#define EXT_CL2_GetReceivePoolSize
	#define GET_CL2_GetReceivePoolSize(fl)  CAL_CMGETAPI( "CL2_GetReceivePoolSize" ) 
	#define CAL_CL2_GetReceivePoolSize  CL2_GetReceivePoolSize
	#define CHK_CL2_GetReceivePoolSize  TRUE
	#define EXP_CL2_GetReceivePoolSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetReceivePoolSize", (RTS_UINTPTR)CL2_GetReceivePoolSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetReceivePoolSize
	#define EXT_CmpCAACanL2CL2_GetReceivePoolSize
	#define GET_CmpCAACanL2CL2_GetReceivePoolSize  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetReceivePoolSize pICmpCAACanL2->ICL2_GetReceivePoolSize
	#define CHK_CmpCAACanL2CL2_GetReceivePoolSize (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetReceivePoolSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetReceivePoolSize
	#define EXT_CL2_GetReceivePoolSize
	#define GET_CL2_GetReceivePoolSize(fl)  CAL_CMGETAPI( "CL2_GetReceivePoolSize" ) 
	#define CAL_CL2_GetReceivePoolSize pICmpCAACanL2->ICL2_GetReceivePoolSize
	#define CHK_CL2_GetReceivePoolSize (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetReceivePoolSize  CAL_CMEXPAPI( "CL2_GetReceivePoolSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetReceivePoolSize  PFCL2_GETRECEIVEPOOLSIZE pfCL2_GetReceivePoolSize;
	#define EXT_CL2_GetReceivePoolSize  extern PFCL2_GETRECEIVEPOOLSIZE pfCL2_GetReceivePoolSize;
	#define GET_CL2_GetReceivePoolSize(fl)  s_pfCMGetAPI2( "CL2_GetReceivePoolSize", (RTS_VOID_FCTPTR *)&pfCL2_GetReceivePoolSize, (fl), 0, 0)
	#define CAL_CL2_GetReceivePoolSize  pfCL2_GetReceivePoolSize
	#define CHK_CL2_GetReceivePoolSize  (pfCL2_GetReceivePoolSize != NULL)
	#define EXP_CL2_GetReceivePoolSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetReceivePoolSize", (RTS_UINTPTR)CL2_GetReceivePoolSize, 0, 0) 
#endif




/* Extended Functionality */
CAA_ERROR CDECL CL2_DisableSyncService(CAA_HANDLE hDriver);
typedef CAA_ERROR (CDECL * PFCL2_DISABLESYNCSERVICE) (CAA_HANDLE hDriver);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_DISABLESYNCSERVICE_NOTIMPLEMENTED)
	#define USE_CL2_DisableSyncService
	#define EXT_CL2_DisableSyncService
	#define GET_CL2_DisableSyncService(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_DisableSyncService(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CL2_DisableSyncService  FALSE
	#define EXP_CL2_DisableSyncService  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_DisableSyncService
	#define EXT_CL2_DisableSyncService
	#define GET_CL2_DisableSyncService(fl)  CAL_CMGETAPI( "CL2_DisableSyncService" ) 
	#define CAL_CL2_DisableSyncService  CL2_DisableSyncService
	#define CHK_CL2_DisableSyncService  TRUE
	#define EXP_CL2_DisableSyncService  CAL_CMEXPAPI( "CL2_DisableSyncService" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_DisableSyncService
	#define EXT_CL2_DisableSyncService
	#define GET_CL2_DisableSyncService(fl)  CAL_CMGETAPI( "CL2_DisableSyncService" ) 
	#define CAL_CL2_DisableSyncService  CL2_DisableSyncService
	#define CHK_CL2_DisableSyncService  TRUE
	#define EXP_CL2_DisableSyncService  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_DisableSyncService", (RTS_UINTPTR)CL2_DisableSyncService, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_DisableSyncService
	#define EXT_CmpCAACanL2CL2_DisableSyncService
	#define GET_CmpCAACanL2CL2_DisableSyncService  ERR_OK
	#define CAL_CmpCAACanL2CL2_DisableSyncService pICmpCAACanL2->ICL2_DisableSyncService
	#define CHK_CmpCAACanL2CL2_DisableSyncService (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_DisableSyncService  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_DisableSyncService
	#define EXT_CL2_DisableSyncService
	#define GET_CL2_DisableSyncService(fl)  CAL_CMGETAPI( "CL2_DisableSyncService" ) 
	#define CAL_CL2_DisableSyncService pICmpCAACanL2->ICL2_DisableSyncService
	#define CHK_CL2_DisableSyncService (pICmpCAACanL2 != NULL)
	#define EXP_CL2_DisableSyncService  CAL_CMEXPAPI( "CL2_DisableSyncService" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_DisableSyncService  PFCL2_DISABLESYNCSERVICE pfCL2_DisableSyncService;
	#define EXT_CL2_DisableSyncService  extern PFCL2_DISABLESYNCSERVICE pfCL2_DisableSyncService;
	#define GET_CL2_DisableSyncService(fl)  s_pfCMGetAPI2( "CL2_DisableSyncService", (RTS_VOID_FCTPTR *)&pfCL2_DisableSyncService, (fl), 0, 0)
	#define CAL_CL2_DisableSyncService  pfCL2_DisableSyncService
	#define CHK_CL2_DisableSyncService  (pfCL2_DisableSyncService != NULL)
	#define EXP_CL2_DisableSyncService  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_DisableSyncService", (RTS_UINTPTR)CL2_DisableSyncService, 0, 0) 
#endif



CAA_ERROR CDECL CL2_DisableTimeService(CAA_HANDLE hDriver);
typedef CAA_ERROR (CDECL * PFCL2_DISABLETIMESERVICE) (CAA_HANDLE hDriver);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_DISABLETIMESERVICE_NOTIMPLEMENTED)
	#define USE_CL2_DisableTimeService
	#define EXT_CL2_DisableTimeService
	#define GET_CL2_DisableTimeService(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_DisableTimeService(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CL2_DisableTimeService  FALSE
	#define EXP_CL2_DisableTimeService  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_DisableTimeService
	#define EXT_CL2_DisableTimeService
	#define GET_CL2_DisableTimeService(fl)  CAL_CMGETAPI( "CL2_DisableTimeService" ) 
	#define CAL_CL2_DisableTimeService  CL2_DisableTimeService
	#define CHK_CL2_DisableTimeService  TRUE
	#define EXP_CL2_DisableTimeService  CAL_CMEXPAPI( "CL2_DisableTimeService" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_DisableTimeService
	#define EXT_CL2_DisableTimeService
	#define GET_CL2_DisableTimeService(fl)  CAL_CMGETAPI( "CL2_DisableTimeService" ) 
	#define CAL_CL2_DisableTimeService  CL2_DisableTimeService
	#define CHK_CL2_DisableTimeService  TRUE
	#define EXP_CL2_DisableTimeService  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_DisableTimeService", (RTS_UINTPTR)CL2_DisableTimeService, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_DisableTimeService
	#define EXT_CmpCAACanL2CL2_DisableTimeService
	#define GET_CmpCAACanL2CL2_DisableTimeService  ERR_OK
	#define CAL_CmpCAACanL2CL2_DisableTimeService pICmpCAACanL2->ICL2_DisableTimeService
	#define CHK_CmpCAACanL2CL2_DisableTimeService (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_DisableTimeService  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_DisableTimeService
	#define EXT_CL2_DisableTimeService
	#define GET_CL2_DisableTimeService(fl)  CAL_CMGETAPI( "CL2_DisableTimeService" ) 
	#define CAL_CL2_DisableTimeService pICmpCAACanL2->ICL2_DisableTimeService
	#define CHK_CL2_DisableTimeService (pICmpCAACanL2 != NULL)
	#define EXP_CL2_DisableTimeService  CAL_CMEXPAPI( "CL2_DisableTimeService" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_DisableTimeService  PFCL2_DISABLETIMESERVICE pfCL2_DisableTimeService;
	#define EXT_CL2_DisableTimeService  extern PFCL2_DISABLETIMESERVICE pfCL2_DisableTimeService;
	#define GET_CL2_DisableTimeService(fl)  s_pfCMGetAPI2( "CL2_DisableTimeService", (RTS_VOID_FCTPTR *)&pfCL2_DisableTimeService, (fl), 0, 0)
	#define CAL_CL2_DisableTimeService  pfCL2_DisableTimeService
	#define CHK_CL2_DisableTimeService  (pfCL2_DisableTimeService != NULL)
	#define EXP_CL2_DisableTimeService  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_DisableTimeService", (RTS_UINTPTR)CL2_DisableTimeService, 0, 0) 
#endif



CAA_ERROR CDECL CL2_EnableSyncService(CAA_HANDLE hDriver, CL2I_COBID cobId, CAA_BOOL xSyncProducer, CAA_BOOL xEnableSyncEvent, CAA_UDINT ulSyncCycle, CAA_UDINT ulSyncWindowLength, CAA_UDINT ulSyncForewarnTime);
typedef CAA_ERROR (CDECL * PFCL2_ENABLESYNCSERVICE) (CAA_HANDLE hDriver, CL2I_COBID cobId, CAA_BOOL xSyncProducer, CAA_BOOL xEnableSyncEvent, CAA_UDINT ulSyncCycle, CAA_UDINT ulSyncWindowLength, CAA_UDINT ulSyncForewarnTime);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_ENABLESYNCSERVICE_NOTIMPLEMENTED)
	#define USE_CL2_EnableSyncService
	#define EXT_CL2_EnableSyncService
	#define GET_CL2_EnableSyncService(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_EnableSyncService(p0,p1,p2,p3,p4,p5,p6)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CL2_EnableSyncService  FALSE
	#define EXP_CL2_EnableSyncService  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_EnableSyncService
	#define EXT_CL2_EnableSyncService
	#define GET_CL2_EnableSyncService(fl)  CAL_CMGETAPI( "CL2_EnableSyncService" ) 
	#define CAL_CL2_EnableSyncService  CL2_EnableSyncService
	#define CHK_CL2_EnableSyncService  TRUE
	#define EXP_CL2_EnableSyncService  CAL_CMEXPAPI( "CL2_EnableSyncService" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_EnableSyncService
	#define EXT_CL2_EnableSyncService
	#define GET_CL2_EnableSyncService(fl)  CAL_CMGETAPI( "CL2_EnableSyncService" ) 
	#define CAL_CL2_EnableSyncService  CL2_EnableSyncService
	#define CHK_CL2_EnableSyncService  TRUE
	#define EXP_CL2_EnableSyncService  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_EnableSyncService", (RTS_UINTPTR)CL2_EnableSyncService, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_EnableSyncService
	#define EXT_CmpCAACanL2CL2_EnableSyncService
	#define GET_CmpCAACanL2CL2_EnableSyncService  ERR_OK
	#define CAL_CmpCAACanL2CL2_EnableSyncService pICmpCAACanL2->ICL2_EnableSyncService
	#define CHK_CmpCAACanL2CL2_EnableSyncService (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_EnableSyncService  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_EnableSyncService
	#define EXT_CL2_EnableSyncService
	#define GET_CL2_EnableSyncService(fl)  CAL_CMGETAPI( "CL2_EnableSyncService" ) 
	#define CAL_CL2_EnableSyncService pICmpCAACanL2->ICL2_EnableSyncService
	#define CHK_CL2_EnableSyncService (pICmpCAACanL2 != NULL)
	#define EXP_CL2_EnableSyncService  CAL_CMEXPAPI( "CL2_EnableSyncService" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_EnableSyncService  PFCL2_ENABLESYNCSERVICE pfCL2_EnableSyncService;
	#define EXT_CL2_EnableSyncService  extern PFCL2_ENABLESYNCSERVICE pfCL2_EnableSyncService;
	#define GET_CL2_EnableSyncService(fl)  s_pfCMGetAPI2( "CL2_EnableSyncService", (RTS_VOID_FCTPTR *)&pfCL2_EnableSyncService, (fl), 0, 0)
	#define CAL_CL2_EnableSyncService  pfCL2_EnableSyncService
	#define CHK_CL2_EnableSyncService  (pfCL2_EnableSyncService != NULL)
	#define EXP_CL2_EnableSyncService  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_EnableSyncService", (RTS_UINTPTR)CL2_EnableSyncService, 0, 0) 
#endif



CAA_ERROR CDECL CL2_EnableTimeService(CAA_HANDLE hDriver, CL2I_COBID cobId, CAA_BOOL xTimeProducer, CAA_BOOL xEnableTimeEvent, CAA_UDINT ulTimeCycle, CAA_UDINT ulTimeForewarnTime);
typedef CAA_ERROR (CDECL * PFCL2_ENABLETIMESERVICE) (CAA_HANDLE hDriver, CL2I_COBID cobId, CAA_BOOL xTimeProducer, CAA_BOOL xEnableTimeEvent, CAA_UDINT ulTimeCycle, CAA_UDINT ulTimeForewarnTime);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_ENABLETIMESERVICE_NOTIMPLEMENTED)
	#define USE_CL2_EnableTimeService
	#define EXT_CL2_EnableTimeService
	#define GET_CL2_EnableTimeService(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_EnableTimeService(p0,p1,p2,p3,p4,p5)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CL2_EnableTimeService  FALSE
	#define EXP_CL2_EnableTimeService  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_EnableTimeService
	#define EXT_CL2_EnableTimeService
	#define GET_CL2_EnableTimeService(fl)  CAL_CMGETAPI( "CL2_EnableTimeService" ) 
	#define CAL_CL2_EnableTimeService  CL2_EnableTimeService
	#define CHK_CL2_EnableTimeService  TRUE
	#define EXP_CL2_EnableTimeService  CAL_CMEXPAPI( "CL2_EnableTimeService" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_EnableTimeService
	#define EXT_CL2_EnableTimeService
	#define GET_CL2_EnableTimeService(fl)  CAL_CMGETAPI( "CL2_EnableTimeService" ) 
	#define CAL_CL2_EnableTimeService  CL2_EnableTimeService
	#define CHK_CL2_EnableTimeService  TRUE
	#define EXP_CL2_EnableTimeService  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_EnableTimeService", (RTS_UINTPTR)CL2_EnableTimeService, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_EnableTimeService
	#define EXT_CmpCAACanL2CL2_EnableTimeService
	#define GET_CmpCAACanL2CL2_EnableTimeService  ERR_OK
	#define CAL_CmpCAACanL2CL2_EnableTimeService pICmpCAACanL2->ICL2_EnableTimeService
	#define CHK_CmpCAACanL2CL2_EnableTimeService (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_EnableTimeService  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_EnableTimeService
	#define EXT_CL2_EnableTimeService
	#define GET_CL2_EnableTimeService(fl)  CAL_CMGETAPI( "CL2_EnableTimeService" ) 
	#define CAL_CL2_EnableTimeService pICmpCAACanL2->ICL2_EnableTimeService
	#define CHK_CL2_EnableTimeService (pICmpCAACanL2 != NULL)
	#define EXP_CL2_EnableTimeService  CAL_CMEXPAPI( "CL2_EnableTimeService" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_EnableTimeService  PFCL2_ENABLETIMESERVICE pfCL2_EnableTimeService;
	#define EXT_CL2_EnableTimeService  extern PFCL2_ENABLETIMESERVICE pfCL2_EnableTimeService;
	#define GET_CL2_EnableTimeService(fl)  s_pfCMGetAPI2( "CL2_EnableTimeService", (RTS_VOID_FCTPTR *)&pfCL2_EnableTimeService, (fl), 0, 0)
	#define CAL_CL2_EnableTimeService  pfCL2_EnableTimeService
	#define CHK_CL2_EnableTimeService  (pfCL2_EnableTimeService != NULL)
	#define EXP_CL2_EnableTimeService  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_EnableTimeService", (RTS_UINTPTR)CL2_EnableTimeService, 0, 0) 
#endif



CAA_ERROR CDECL CL2_UpdateTimeService(CAA_HANDLE hDriver, CAA_UDINT ulTime, CAA_UDINT ulDate);
typedef CAA_ERROR (CDECL * PFCL2_UPDATETIMESERVICE) (CAA_HANDLE hDriver, CAA_UDINT ulTime, CAA_UDINT ulDate);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_UPDATETIMESERVICE_NOTIMPLEMENTED)
	#define USE_CL2_UpdateTimeService
	#define EXT_CL2_UpdateTimeService
	#define GET_CL2_UpdateTimeService(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_UpdateTimeService(p0,p1,p2)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CL2_UpdateTimeService  FALSE
	#define EXP_CL2_UpdateTimeService  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_UpdateTimeService
	#define EXT_CL2_UpdateTimeService
	#define GET_CL2_UpdateTimeService(fl)  CAL_CMGETAPI( "CL2_UpdateTimeService" ) 
	#define CAL_CL2_UpdateTimeService  CL2_UpdateTimeService
	#define CHK_CL2_UpdateTimeService  TRUE
	#define EXP_CL2_UpdateTimeService  CAL_CMEXPAPI( "CL2_UpdateTimeService" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_UpdateTimeService
	#define EXT_CL2_UpdateTimeService
	#define GET_CL2_UpdateTimeService(fl)  CAL_CMGETAPI( "CL2_UpdateTimeService" ) 
	#define CAL_CL2_UpdateTimeService  CL2_UpdateTimeService
	#define CHK_CL2_UpdateTimeService  TRUE
	#define EXP_CL2_UpdateTimeService  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_UpdateTimeService", (RTS_UINTPTR)CL2_UpdateTimeService, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_UpdateTimeService
	#define EXT_CmpCAACanL2CL2_UpdateTimeService
	#define GET_CmpCAACanL2CL2_UpdateTimeService  ERR_OK
	#define CAL_CmpCAACanL2CL2_UpdateTimeService pICmpCAACanL2->ICL2_UpdateTimeService
	#define CHK_CmpCAACanL2CL2_UpdateTimeService (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_UpdateTimeService  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_UpdateTimeService
	#define EXT_CL2_UpdateTimeService
	#define GET_CL2_UpdateTimeService(fl)  CAL_CMGETAPI( "CL2_UpdateTimeService" ) 
	#define CAL_CL2_UpdateTimeService pICmpCAACanL2->ICL2_UpdateTimeService
	#define CHK_CL2_UpdateTimeService (pICmpCAACanL2 != NULL)
	#define EXP_CL2_UpdateTimeService  CAL_CMEXPAPI( "CL2_UpdateTimeService" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_UpdateTimeService  PFCL2_UPDATETIMESERVICE pfCL2_UpdateTimeService;
	#define EXT_CL2_UpdateTimeService  extern PFCL2_UPDATETIMESERVICE pfCL2_UpdateTimeService;
	#define GET_CL2_UpdateTimeService(fl)  s_pfCMGetAPI2( "CL2_UpdateTimeService", (RTS_VOID_FCTPTR *)&pfCL2_UpdateTimeService, (fl), 0, 0)
	#define CAL_CL2_UpdateTimeService  pfCL2_UpdateTimeService
	#define CHK_CL2_UpdateTimeService  (pfCL2_UpdateTimeService != NULL)
	#define EXP_CL2_UpdateTimeService  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_UpdateTimeService", (RTS_UINTPTR)CL2_UpdateTimeService, 0, 0) 
#endif




/* Message Information */
CL2I_DATA* CDECL CL2_GetMessageDataPointer(CAA_HANDLE hMessage, CAA_ERROR* peError);
typedef CL2I_DATA* (CDECL * PFCL2_GETMESSAGEDATAPOINTER) (CAA_HANDLE hMessage, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETMESSAGEDATAPOINTER_NOTIMPLEMENTED)
	#define USE_CL2_GetMessageDataPointer
	#define EXT_CL2_GetMessageDataPointer
	#define GET_CL2_GetMessageDataPointer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetMessageDataPointer(p0,p1)  (CL2I_DATA*)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetMessageDataPointer  FALSE
	#define EXP_CL2_GetMessageDataPointer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetMessageDataPointer
	#define EXT_CL2_GetMessageDataPointer
	#define GET_CL2_GetMessageDataPointer(fl)  CAL_CMGETAPI( "CL2_GetMessageDataPointer" ) 
	#define CAL_CL2_GetMessageDataPointer  CL2_GetMessageDataPointer
	#define CHK_CL2_GetMessageDataPointer  TRUE
	#define EXP_CL2_GetMessageDataPointer  CAL_CMEXPAPI( "CL2_GetMessageDataPointer" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetMessageDataPointer
	#define EXT_CL2_GetMessageDataPointer
	#define GET_CL2_GetMessageDataPointer(fl)  CAL_CMGETAPI( "CL2_GetMessageDataPointer" ) 
	#define CAL_CL2_GetMessageDataPointer  CL2_GetMessageDataPointer
	#define CHK_CL2_GetMessageDataPointer  TRUE
	#define EXP_CL2_GetMessageDataPointer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetMessageDataPointer", (RTS_UINTPTR)CL2_GetMessageDataPointer, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetMessageDataPointer
	#define EXT_CmpCAACanL2CL2_GetMessageDataPointer
	#define GET_CmpCAACanL2CL2_GetMessageDataPointer  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetMessageDataPointer pICmpCAACanL2->ICL2_GetMessageDataPointer
	#define CHK_CmpCAACanL2CL2_GetMessageDataPointer (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetMessageDataPointer  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetMessageDataPointer
	#define EXT_CL2_GetMessageDataPointer
	#define GET_CL2_GetMessageDataPointer(fl)  CAL_CMGETAPI( "CL2_GetMessageDataPointer" ) 
	#define CAL_CL2_GetMessageDataPointer pICmpCAACanL2->ICL2_GetMessageDataPointer
	#define CHK_CL2_GetMessageDataPointer (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetMessageDataPointer  CAL_CMEXPAPI( "CL2_GetMessageDataPointer" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetMessageDataPointer  PFCL2_GETMESSAGEDATAPOINTER pfCL2_GetMessageDataPointer;
	#define EXT_CL2_GetMessageDataPointer  extern PFCL2_GETMESSAGEDATAPOINTER pfCL2_GetMessageDataPointer;
	#define GET_CL2_GetMessageDataPointer(fl)  s_pfCMGetAPI2( "CL2_GetMessageDataPointer", (RTS_VOID_FCTPTR *)&pfCL2_GetMessageDataPointer, (fl), 0, 0)
	#define CAL_CL2_GetMessageDataPointer  pfCL2_GetMessageDataPointer
	#define CHK_CL2_GetMessageDataPointer  (pfCL2_GetMessageDataPointer != NULL)
	#define EXP_CL2_GetMessageDataPointer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetMessageDataPointer", (RTS_UINTPTR)CL2_GetMessageDataPointer, 0, 0) 
#endif



CL2I_COBID CDECL CL2_GetMessageId(CAA_HANDLE hMessage, CAA_ERROR* peError);
typedef CL2I_COBID (CDECL * PFCL2_GETMESSAGEID) (CAA_HANDLE hMessage, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETMESSAGEID_NOTIMPLEMENTED)
	#define USE_CL2_GetMessageId
	#define EXT_CL2_GetMessageId
	#define GET_CL2_GetMessageId(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetMessageId(p0,p1)  (CL2I_COBID)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetMessageId  FALSE
	#define EXP_CL2_GetMessageId  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetMessageId
	#define EXT_CL2_GetMessageId
	#define GET_CL2_GetMessageId(fl)  CAL_CMGETAPI( "CL2_GetMessageId" ) 
	#define CAL_CL2_GetMessageId  CL2_GetMessageId
	#define CHK_CL2_GetMessageId  TRUE
	#define EXP_CL2_GetMessageId  CAL_CMEXPAPI( "CL2_GetMessageId" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetMessageId
	#define EXT_CL2_GetMessageId
	#define GET_CL2_GetMessageId(fl)  CAL_CMGETAPI( "CL2_GetMessageId" ) 
	#define CAL_CL2_GetMessageId  CL2_GetMessageId
	#define CHK_CL2_GetMessageId  TRUE
	#define EXP_CL2_GetMessageId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetMessageId", (RTS_UINTPTR)CL2_GetMessageId, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetMessageId
	#define EXT_CmpCAACanL2CL2_GetMessageId
	#define GET_CmpCAACanL2CL2_GetMessageId  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetMessageId pICmpCAACanL2->ICL2_GetMessageId
	#define CHK_CmpCAACanL2CL2_GetMessageId (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetMessageId  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetMessageId
	#define EXT_CL2_GetMessageId
	#define GET_CL2_GetMessageId(fl)  CAL_CMGETAPI( "CL2_GetMessageId" ) 
	#define CAL_CL2_GetMessageId pICmpCAACanL2->ICL2_GetMessageId
	#define CHK_CL2_GetMessageId (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetMessageId  CAL_CMEXPAPI( "CL2_GetMessageId" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetMessageId  PFCL2_GETMESSAGEID pfCL2_GetMessageId;
	#define EXT_CL2_GetMessageId  extern PFCL2_GETMESSAGEID pfCL2_GetMessageId;
	#define GET_CL2_GetMessageId(fl)  s_pfCMGetAPI2( "CL2_GetMessageId", (RTS_VOID_FCTPTR *)&pfCL2_GetMessageId, (fl), 0, 0)
	#define CAL_CL2_GetMessageId  pfCL2_GetMessageId
	#define CHK_CL2_GetMessageId  (pfCL2_GetMessageId != NULL)
	#define EXP_CL2_GetMessageId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetMessageId", (RTS_UINTPTR)CL2_GetMessageId, 0, 0) 
#endif



unsigned char CDECL CL2_GetMessageLength(CAA_HANDLE hMessage, CAA_ERROR* peError);
typedef unsigned char (CDECL * PFCL2_GETMESSAGELENGTH) (CAA_HANDLE hMessage, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETMESSAGELENGTH_NOTIMPLEMENTED)
	#define USE_CL2_GetMessageLength
	#define EXT_CL2_GetMessageLength
	#define GET_CL2_GetMessageLength(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetMessageLength(p0,p1)  (unsigned char)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetMessageLength  FALSE
	#define EXP_CL2_GetMessageLength  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetMessageLength
	#define EXT_CL2_GetMessageLength
	#define GET_CL2_GetMessageLength(fl)  CAL_CMGETAPI( "CL2_GetMessageLength" ) 
	#define CAL_CL2_GetMessageLength  CL2_GetMessageLength
	#define CHK_CL2_GetMessageLength  TRUE
	#define EXP_CL2_GetMessageLength  CAL_CMEXPAPI( "CL2_GetMessageLength" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetMessageLength
	#define EXT_CL2_GetMessageLength
	#define GET_CL2_GetMessageLength(fl)  CAL_CMGETAPI( "CL2_GetMessageLength" ) 
	#define CAL_CL2_GetMessageLength  CL2_GetMessageLength
	#define CHK_CL2_GetMessageLength  TRUE
	#define EXP_CL2_GetMessageLength  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetMessageLength", (RTS_UINTPTR)CL2_GetMessageLength, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetMessageLength
	#define EXT_CmpCAACanL2CL2_GetMessageLength
	#define GET_CmpCAACanL2CL2_GetMessageLength  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetMessageLength pICmpCAACanL2->ICL2_GetMessageLength
	#define CHK_CmpCAACanL2CL2_GetMessageLength (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetMessageLength  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetMessageLength
	#define EXT_CL2_GetMessageLength
	#define GET_CL2_GetMessageLength(fl)  CAL_CMGETAPI( "CL2_GetMessageLength" ) 
	#define CAL_CL2_GetMessageLength pICmpCAACanL2->ICL2_GetMessageLength
	#define CHK_CL2_GetMessageLength (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetMessageLength  CAL_CMEXPAPI( "CL2_GetMessageLength" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetMessageLength  PFCL2_GETMESSAGELENGTH pfCL2_GetMessageLength;
	#define EXT_CL2_GetMessageLength  extern PFCL2_GETMESSAGELENGTH pfCL2_GetMessageLength;
	#define GET_CL2_GetMessageLength(fl)  s_pfCMGetAPI2( "CL2_GetMessageLength", (RTS_VOID_FCTPTR *)&pfCL2_GetMessageLength, (fl), 0, 0)
	#define CAL_CL2_GetMessageLength  pfCL2_GetMessageLength
	#define CHK_CL2_GetMessageLength  (pfCL2_GetMessageLength != NULL)
	#define EXP_CL2_GetMessageLength  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetMessageLength", (RTS_UINTPTR)CL2_GetMessageLength, 0, 0) 
#endif



CAA_UDINT CDECL CL2_GetTimeStamp(CAA_HANDLE hMessage, CAA_ERROR* peError);
typedef CAA_UDINT (CDECL * PFCL2_GETTIMESTAMP) (CAA_HANDLE hMessage, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETTIMESTAMP_NOTIMPLEMENTED)
	#define USE_CL2_GetTimeStamp
	#define EXT_CL2_GetTimeStamp
	#define GET_CL2_GetTimeStamp(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetTimeStamp(p0,p1)  (CAA_UDINT)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetTimeStamp  FALSE
	#define EXP_CL2_GetTimeStamp  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetTimeStamp
	#define EXT_CL2_GetTimeStamp
	#define GET_CL2_GetTimeStamp(fl)  CAL_CMGETAPI( "CL2_GetTimeStamp" ) 
	#define CAL_CL2_GetTimeStamp  CL2_GetTimeStamp
	#define CHK_CL2_GetTimeStamp  TRUE
	#define EXP_CL2_GetTimeStamp  CAL_CMEXPAPI( "CL2_GetTimeStamp" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetTimeStamp
	#define EXT_CL2_GetTimeStamp
	#define GET_CL2_GetTimeStamp(fl)  CAL_CMGETAPI( "CL2_GetTimeStamp" ) 
	#define CAL_CL2_GetTimeStamp  CL2_GetTimeStamp
	#define CHK_CL2_GetTimeStamp  TRUE
	#define EXP_CL2_GetTimeStamp  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetTimeStamp", (RTS_UINTPTR)CL2_GetTimeStamp, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetTimeStamp
	#define EXT_CmpCAACanL2CL2_GetTimeStamp
	#define GET_CmpCAACanL2CL2_GetTimeStamp  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetTimeStamp pICmpCAACanL2->ICL2_GetTimeStamp
	#define CHK_CmpCAACanL2CL2_GetTimeStamp (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetTimeStamp  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetTimeStamp
	#define EXT_CL2_GetTimeStamp
	#define GET_CL2_GetTimeStamp(fl)  CAL_CMGETAPI( "CL2_GetTimeStamp" ) 
	#define CAL_CL2_GetTimeStamp pICmpCAACanL2->ICL2_GetTimeStamp
	#define CHK_CL2_GetTimeStamp (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetTimeStamp  CAL_CMEXPAPI( "CL2_GetTimeStamp" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetTimeStamp  PFCL2_GETTIMESTAMP pfCL2_GetTimeStamp;
	#define EXT_CL2_GetTimeStamp  extern PFCL2_GETTIMESTAMP pfCL2_GetTimeStamp;
	#define GET_CL2_GetTimeStamp(fl)  s_pfCMGetAPI2( "CL2_GetTimeStamp", (RTS_VOID_FCTPTR *)&pfCL2_GetTimeStamp, (fl), 0, 0)
	#define CAL_CL2_GetTimeStamp  pfCL2_GetTimeStamp
	#define CHK_CL2_GetTimeStamp  (pfCL2_GetTimeStamp != NULL)
	#define EXP_CL2_GetTimeStamp  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetTimeStamp", (RTS_UINTPTR)CL2_GetTimeStamp, 0, 0) 
#endif



CAA_BOOL CDECL CL2_Is29BitIdMessage(CAA_HANDLE hMessage, CAA_ERROR* peError);
typedef CAA_BOOL (CDECL * PFCL2_IS29BITIDMESSAGE) (CAA_HANDLE hMessage, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_IS29BITIDMESSAGE_NOTIMPLEMENTED)
	#define USE_CL2_Is29BitIdMessage
	#define EXT_CL2_Is29BitIdMessage
	#define GET_CL2_Is29BitIdMessage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_Is29BitIdMessage(p0,p1)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_CL2_Is29BitIdMessage  FALSE
	#define EXP_CL2_Is29BitIdMessage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_Is29BitIdMessage
	#define EXT_CL2_Is29BitIdMessage
	#define GET_CL2_Is29BitIdMessage(fl)  CAL_CMGETAPI( "CL2_Is29BitIdMessage" ) 
	#define CAL_CL2_Is29BitIdMessage  CL2_Is29BitIdMessage
	#define CHK_CL2_Is29BitIdMessage  TRUE
	#define EXP_CL2_Is29BitIdMessage  CAL_CMEXPAPI( "CL2_Is29BitIdMessage" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_Is29BitIdMessage
	#define EXT_CL2_Is29BitIdMessage
	#define GET_CL2_Is29BitIdMessage(fl)  CAL_CMGETAPI( "CL2_Is29BitIdMessage" ) 
	#define CAL_CL2_Is29BitIdMessage  CL2_Is29BitIdMessage
	#define CHK_CL2_Is29BitIdMessage  TRUE
	#define EXP_CL2_Is29BitIdMessage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_Is29BitIdMessage", (RTS_UINTPTR)CL2_Is29BitIdMessage, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_Is29BitIdMessage
	#define EXT_CmpCAACanL2CL2_Is29BitIdMessage
	#define GET_CmpCAACanL2CL2_Is29BitIdMessage  ERR_OK
	#define CAL_CmpCAACanL2CL2_Is29BitIdMessage pICmpCAACanL2->ICL2_Is29BitIdMessage
	#define CHK_CmpCAACanL2CL2_Is29BitIdMessage (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_Is29BitIdMessage  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_Is29BitIdMessage
	#define EXT_CL2_Is29BitIdMessage
	#define GET_CL2_Is29BitIdMessage(fl)  CAL_CMGETAPI( "CL2_Is29BitIdMessage" ) 
	#define CAL_CL2_Is29BitIdMessage pICmpCAACanL2->ICL2_Is29BitIdMessage
	#define CHK_CL2_Is29BitIdMessage (pICmpCAACanL2 != NULL)
	#define EXP_CL2_Is29BitIdMessage  CAL_CMEXPAPI( "CL2_Is29BitIdMessage" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_Is29BitIdMessage  PFCL2_IS29BITIDMESSAGE pfCL2_Is29BitIdMessage;
	#define EXT_CL2_Is29BitIdMessage  extern PFCL2_IS29BITIDMESSAGE pfCL2_Is29BitIdMessage;
	#define GET_CL2_Is29BitIdMessage(fl)  s_pfCMGetAPI2( "CL2_Is29BitIdMessage", (RTS_VOID_FCTPTR *)&pfCL2_Is29BitIdMessage, (fl), 0, 0)
	#define CAL_CL2_Is29BitIdMessage  pfCL2_Is29BitIdMessage
	#define CHK_CL2_Is29BitIdMessage  (pfCL2_Is29BitIdMessage != NULL)
	#define EXP_CL2_Is29BitIdMessage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_Is29BitIdMessage", (RTS_UINTPTR)CL2_Is29BitIdMessage, 0, 0) 
#endif



CAA_BOOL CDECL CL2_IsRTRMessage(CAA_HANDLE hMessage, CAA_ERROR* peError);
typedef CAA_BOOL (CDECL * PFCL2_ISRTRMESSAGE) (CAA_HANDLE hMessage, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_ISRTRMESSAGE_NOTIMPLEMENTED)
	#define USE_CL2_IsRTRMessage
	#define EXT_CL2_IsRTRMessage
	#define GET_CL2_IsRTRMessage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_IsRTRMessage(p0,p1)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_CL2_IsRTRMessage  FALSE
	#define EXP_CL2_IsRTRMessage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_IsRTRMessage
	#define EXT_CL2_IsRTRMessage
	#define GET_CL2_IsRTRMessage(fl)  CAL_CMGETAPI( "CL2_IsRTRMessage" ) 
	#define CAL_CL2_IsRTRMessage  CL2_IsRTRMessage
	#define CHK_CL2_IsRTRMessage  TRUE
	#define EXP_CL2_IsRTRMessage  CAL_CMEXPAPI( "CL2_IsRTRMessage" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_IsRTRMessage
	#define EXT_CL2_IsRTRMessage
	#define GET_CL2_IsRTRMessage(fl)  CAL_CMGETAPI( "CL2_IsRTRMessage" ) 
	#define CAL_CL2_IsRTRMessage  CL2_IsRTRMessage
	#define CHK_CL2_IsRTRMessage  TRUE
	#define EXP_CL2_IsRTRMessage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_IsRTRMessage", (RTS_UINTPTR)CL2_IsRTRMessage, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_IsRTRMessage
	#define EXT_CmpCAACanL2CL2_IsRTRMessage
	#define GET_CmpCAACanL2CL2_IsRTRMessage  ERR_OK
	#define CAL_CmpCAACanL2CL2_IsRTRMessage pICmpCAACanL2->ICL2_IsRTRMessage
	#define CHK_CmpCAACanL2CL2_IsRTRMessage (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_IsRTRMessage  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_IsRTRMessage
	#define EXT_CL2_IsRTRMessage
	#define GET_CL2_IsRTRMessage(fl)  CAL_CMGETAPI( "CL2_IsRTRMessage" ) 
	#define CAL_CL2_IsRTRMessage pICmpCAACanL2->ICL2_IsRTRMessage
	#define CHK_CL2_IsRTRMessage (pICmpCAACanL2 != NULL)
	#define EXP_CL2_IsRTRMessage  CAL_CMEXPAPI( "CL2_IsRTRMessage" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_IsRTRMessage  PFCL2_ISRTRMESSAGE pfCL2_IsRTRMessage;
	#define EXT_CL2_IsRTRMessage  extern PFCL2_ISRTRMESSAGE pfCL2_IsRTRMessage;
	#define GET_CL2_IsRTRMessage(fl)  s_pfCMGetAPI2( "CL2_IsRTRMessage", (RTS_VOID_FCTPTR *)&pfCL2_IsRTRMessage, (fl), 0, 0)
	#define CAL_CL2_IsRTRMessage  pfCL2_IsRTRMessage
	#define CHK_CL2_IsRTRMessage  (pfCL2_IsRTRMessage != NULL)
	#define EXP_CL2_IsRTRMessage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_IsRTRMessage", (RTS_UINTPTR)CL2_IsRTRMessage, 0, 0) 
#endif



CAA_BOOL CDECL CL2_IsTransmitMessage(CAA_HANDLE hMessage, CAA_ERROR* peError);
typedef CAA_BOOL (CDECL * PFCL2_ISTRANSMITMESSAGE) (CAA_HANDLE hMessage, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_ISTRANSMITMESSAGE_NOTIMPLEMENTED)
	#define USE_CL2_IsTransmitMessage
	#define EXT_CL2_IsTransmitMessage
	#define GET_CL2_IsTransmitMessage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_IsTransmitMessage(p0,p1)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_CL2_IsTransmitMessage  FALSE
	#define EXP_CL2_IsTransmitMessage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_IsTransmitMessage
	#define EXT_CL2_IsTransmitMessage
	#define GET_CL2_IsTransmitMessage(fl)  CAL_CMGETAPI( "CL2_IsTransmitMessage" ) 
	#define CAL_CL2_IsTransmitMessage  CL2_IsTransmitMessage
	#define CHK_CL2_IsTransmitMessage  TRUE
	#define EXP_CL2_IsTransmitMessage  CAL_CMEXPAPI( "CL2_IsTransmitMessage" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_IsTransmitMessage
	#define EXT_CL2_IsTransmitMessage
	#define GET_CL2_IsTransmitMessage(fl)  CAL_CMGETAPI( "CL2_IsTransmitMessage" ) 
	#define CAL_CL2_IsTransmitMessage  CL2_IsTransmitMessage
	#define CHK_CL2_IsTransmitMessage  TRUE
	#define EXP_CL2_IsTransmitMessage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_IsTransmitMessage", (RTS_UINTPTR)CL2_IsTransmitMessage, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_IsTransmitMessage
	#define EXT_CmpCAACanL2CL2_IsTransmitMessage
	#define GET_CmpCAACanL2CL2_IsTransmitMessage  ERR_OK
	#define CAL_CmpCAACanL2CL2_IsTransmitMessage pICmpCAACanL2->ICL2_IsTransmitMessage
	#define CHK_CmpCAACanL2CL2_IsTransmitMessage (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_IsTransmitMessage  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_IsTransmitMessage
	#define EXT_CL2_IsTransmitMessage
	#define GET_CL2_IsTransmitMessage(fl)  CAL_CMGETAPI( "CL2_IsTransmitMessage" ) 
	#define CAL_CL2_IsTransmitMessage pICmpCAACanL2->ICL2_IsTransmitMessage
	#define CHK_CL2_IsTransmitMessage (pICmpCAACanL2 != NULL)
	#define EXP_CL2_IsTransmitMessage  CAL_CMEXPAPI( "CL2_IsTransmitMessage" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_IsTransmitMessage  PFCL2_ISTRANSMITMESSAGE pfCL2_IsTransmitMessage;
	#define EXT_CL2_IsTransmitMessage  extern PFCL2_ISTRANSMITMESSAGE pfCL2_IsTransmitMessage;
	#define GET_CL2_IsTransmitMessage(fl)  s_pfCMGetAPI2( "CL2_IsTransmitMessage", (RTS_VOID_FCTPTR *)&pfCL2_IsTransmitMessage, (fl), 0, 0)
	#define CAL_CL2_IsTransmitMessage  pfCL2_IsTransmitMessage
	#define CHK_CL2_IsTransmitMessage  (pfCL2_IsTransmitMessage != NULL)
	#define EXP_CL2_IsTransmitMessage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_IsTransmitMessage", (RTS_UINTPTR)CL2_IsTransmitMessage, 0, 0) 
#endif



unsigned char CDECL CL2_GetNetId(CAA_HANDLE hMessage, CAA_ERROR* peError);
typedef unsigned char (CDECL * PFCL2_GETNETID) (CAA_HANDLE hMessage, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETNETID_NOTIMPLEMENTED)
	#define USE_CL2_GetNetId
	#define EXT_CL2_GetNetId
	#define GET_CL2_GetNetId(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetNetId(p0,p1)  (unsigned char)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetNetId  FALSE
	#define EXP_CL2_GetNetId  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetNetId
	#define EXT_CL2_GetNetId
	#define GET_CL2_GetNetId(fl)  CAL_CMGETAPI( "CL2_GetNetId" ) 
	#define CAL_CL2_GetNetId  CL2_GetNetId
	#define CHK_CL2_GetNetId  TRUE
	#define EXP_CL2_GetNetId  CAL_CMEXPAPI( "CL2_GetNetId" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetNetId
	#define EXT_CL2_GetNetId
	#define GET_CL2_GetNetId(fl)  CAL_CMGETAPI( "CL2_GetNetId" ) 
	#define CAL_CL2_GetNetId  CL2_GetNetId
	#define CHK_CL2_GetNetId  TRUE
	#define EXP_CL2_GetNetId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetNetId", (RTS_UINTPTR)CL2_GetNetId, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetNetId
	#define EXT_CmpCAACanL2CL2_GetNetId
	#define GET_CmpCAACanL2CL2_GetNetId  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetNetId pICmpCAACanL2->ICL2_GetNetId
	#define CHK_CmpCAACanL2CL2_GetNetId (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetNetId  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetNetId
	#define EXT_CL2_GetNetId
	#define GET_CL2_GetNetId(fl)  CAL_CMGETAPI( "CL2_GetNetId" ) 
	#define CAL_CL2_GetNetId pICmpCAACanL2->ICL2_GetNetId
	#define CHK_CL2_GetNetId (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetNetId  CAL_CMEXPAPI( "CL2_GetNetId" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetNetId  PFCL2_GETNETID pfCL2_GetNetId;
	#define EXT_CL2_GetNetId  extern PFCL2_GETNETID pfCL2_GetNetId;
	#define GET_CL2_GetNetId(fl)  s_pfCMGetAPI2( "CL2_GetNetId", (RTS_VOID_FCTPTR *)&pfCL2_GetNetId, (fl), 0, 0)
	#define CAL_CL2_GetNetId  pfCL2_GetNetId
	#define CHK_CL2_GetNetId  (pfCL2_GetNetId != NULL)
	#define EXP_CL2_GetNetId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetNetId", (RTS_UINTPTR)CL2_GetNetId, 0, 0) 
#endif



CAA_COUNT CDECL CL2_LostMessages(CAA_HANDLE hReceiverId, CAA_ERROR* peError);
typedef CAA_COUNT (CDECL * PFCL2_LOSTMESSAGES) (CAA_HANDLE hReceiverId, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_LOSTMESSAGES_NOTIMPLEMENTED)
	#define USE_CL2_LostMessages
	#define EXT_CL2_LostMessages
	#define GET_CL2_LostMessages(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_LostMessages(p0,p1)  (CAA_COUNT)ERR_NOTIMPLEMENTED
	#define CHK_CL2_LostMessages  FALSE
	#define EXP_CL2_LostMessages  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_LostMessages
	#define EXT_CL2_LostMessages
	#define GET_CL2_LostMessages(fl)  CAL_CMGETAPI( "CL2_LostMessages" ) 
	#define CAL_CL2_LostMessages  CL2_LostMessages
	#define CHK_CL2_LostMessages  TRUE
	#define EXP_CL2_LostMessages  CAL_CMEXPAPI( "CL2_LostMessages" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_LostMessages
	#define EXT_CL2_LostMessages
	#define GET_CL2_LostMessages(fl)  CAL_CMGETAPI( "CL2_LostMessages" ) 
	#define CAL_CL2_LostMessages  CL2_LostMessages
	#define CHK_CL2_LostMessages  TRUE
	#define EXP_CL2_LostMessages  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_LostMessages", (RTS_UINTPTR)CL2_LostMessages, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_LostMessages
	#define EXT_CmpCAACanL2CL2_LostMessages
	#define GET_CmpCAACanL2CL2_LostMessages  ERR_OK
	#define CAL_CmpCAACanL2CL2_LostMessages pICmpCAACanL2->ICL2_LostMessages
	#define CHK_CmpCAACanL2CL2_LostMessages (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_LostMessages  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_LostMessages
	#define EXT_CL2_LostMessages
	#define GET_CL2_LostMessages(fl)  CAL_CMGETAPI( "CL2_LostMessages" ) 
	#define CAL_CL2_LostMessages pICmpCAACanL2->ICL2_LostMessages
	#define CHK_CL2_LostMessages (pICmpCAACanL2 != NULL)
	#define EXP_CL2_LostMessages  CAL_CMEXPAPI( "CL2_LostMessages" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_LostMessages  PFCL2_LOSTMESSAGES pfCL2_LostMessages;
	#define EXT_CL2_LostMessages  extern PFCL2_LOSTMESSAGES pfCL2_LostMessages;
	#define GET_CL2_LostMessages(fl)  s_pfCMGetAPI2( "CL2_LostMessages", (RTS_VOID_FCTPTR *)&pfCL2_LostMessages, (fl), 0, 0)
	#define CAL_CL2_LostMessages  pfCL2_LostMessages
	#define CHK_CL2_LostMessages  (pfCL2_LostMessages != NULL)
	#define EXP_CL2_LostMessages  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_LostMessages", (RTS_UINTPTR)CL2_LostMessages, 0, 0) 
#endif



CAA_COUNT CDECL CL2_GetMsgCount(CAA_HANDLE hReceiverId, CAA_ERROR* peError);
typedef CAA_COUNT (CDECL * PFCL2_GETMSGCOUNT) (CAA_HANDLE hReceiverId, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETMSGCOUNT_NOTIMPLEMENTED)
	#define USE_CL2_GetMsgCount
	#define EXT_CL2_GetMsgCount
	#define GET_CL2_GetMsgCount(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetMsgCount(p0,p1)  (CAA_COUNT)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetMsgCount  FALSE
	#define EXP_CL2_GetMsgCount  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetMsgCount
	#define EXT_CL2_GetMsgCount
	#define GET_CL2_GetMsgCount(fl)  CAL_CMGETAPI( "CL2_GetMsgCount" ) 
	#define CAL_CL2_GetMsgCount  CL2_GetMsgCount
	#define CHK_CL2_GetMsgCount  TRUE
	#define EXP_CL2_GetMsgCount  CAL_CMEXPAPI( "CL2_GetMsgCount" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetMsgCount
	#define EXT_CL2_GetMsgCount
	#define GET_CL2_GetMsgCount(fl)  CAL_CMGETAPI( "CL2_GetMsgCount" ) 
	#define CAL_CL2_GetMsgCount  CL2_GetMsgCount
	#define CHK_CL2_GetMsgCount  TRUE
	#define EXP_CL2_GetMsgCount  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetMsgCount", (RTS_UINTPTR)CL2_GetMsgCount, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetMsgCount
	#define EXT_CmpCAACanL2CL2_GetMsgCount
	#define GET_CmpCAACanL2CL2_GetMsgCount  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetMsgCount pICmpCAACanL2->ICL2_GetMsgCount
	#define CHK_CmpCAACanL2CL2_GetMsgCount (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetMsgCount  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetMsgCount
	#define EXT_CL2_GetMsgCount
	#define GET_CL2_GetMsgCount(fl)  CAL_CMGETAPI( "CL2_GetMsgCount" ) 
	#define CAL_CL2_GetMsgCount pICmpCAACanL2->ICL2_GetMsgCount
	#define CHK_CL2_GetMsgCount (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetMsgCount  CAL_CMEXPAPI( "CL2_GetMsgCount" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetMsgCount  PFCL2_GETMSGCOUNT pfCL2_GetMsgCount;
	#define EXT_CL2_GetMsgCount  extern PFCL2_GETMSGCOUNT pfCL2_GetMsgCount;
	#define GET_CL2_GetMsgCount(fl)  s_pfCMGetAPI2( "CL2_GetMsgCount", (RTS_VOID_FCTPTR *)&pfCL2_GetMsgCount, (fl), 0, 0)
	#define CAL_CL2_GetMsgCount  pfCL2_GetMsgCount
	#define CHK_CL2_GetMsgCount  (pfCL2_GetMsgCount != NULL)
	#define EXP_CL2_GetMsgCount  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetMsgCount", (RTS_UINTPTR)CL2_GetMsgCount, 0, 0) 
#endif




/* CiA 303 Indicator services */
unsigned char CDECL CL2_GetCiAState(CAA_HANDLE hDriver, CAA_ERROR* peError);
typedef unsigned char (CDECL * PFCL2_GETCIASTATE) (CAA_HANDLE hDriver, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETCIASTATE_NOTIMPLEMENTED)
	#define USE_CL2_GetCiAState
	#define EXT_CL2_GetCiAState
	#define GET_CL2_GetCiAState(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetCiAState(p0,p1)  (unsigned char)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetCiAState  FALSE
	#define EXP_CL2_GetCiAState  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetCiAState
	#define EXT_CL2_GetCiAState
	#define GET_CL2_GetCiAState(fl)  CAL_CMGETAPI( "CL2_GetCiAState" ) 
	#define CAL_CL2_GetCiAState  CL2_GetCiAState
	#define CHK_CL2_GetCiAState  TRUE
	#define EXP_CL2_GetCiAState  CAL_CMEXPAPI( "CL2_GetCiAState" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetCiAState
	#define EXT_CL2_GetCiAState
	#define GET_CL2_GetCiAState(fl)  CAL_CMGETAPI( "CL2_GetCiAState" ) 
	#define CAL_CL2_GetCiAState  CL2_GetCiAState
	#define CHK_CL2_GetCiAState  TRUE
	#define EXP_CL2_GetCiAState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetCiAState", (RTS_UINTPTR)CL2_GetCiAState, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetCiAState
	#define EXT_CmpCAACanL2CL2_GetCiAState
	#define GET_CmpCAACanL2CL2_GetCiAState  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetCiAState pICmpCAACanL2->ICL2_GetCiAState
	#define CHK_CmpCAACanL2CL2_GetCiAState (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetCiAState  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetCiAState
	#define EXT_CL2_GetCiAState
	#define GET_CL2_GetCiAState(fl)  CAL_CMGETAPI( "CL2_GetCiAState" ) 
	#define CAL_CL2_GetCiAState pICmpCAACanL2->ICL2_GetCiAState
	#define CHK_CL2_GetCiAState (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetCiAState  CAL_CMEXPAPI( "CL2_GetCiAState" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetCiAState  PFCL2_GETCIASTATE pfCL2_GetCiAState;
	#define EXT_CL2_GetCiAState  extern PFCL2_GETCIASTATE pfCL2_GetCiAState;
	#define GET_CL2_GetCiAState(fl)  s_pfCMGetAPI2( "CL2_GetCiAState", (RTS_VOID_FCTPTR *)&pfCL2_GetCiAState, (fl), 0, 0)
	#define CAL_CL2_GetCiAState  pfCL2_GetCiAState
	#define CHK_CL2_GetCiAState  (pfCL2_GetCiAState != NULL)
	#define EXP_CL2_GetCiAState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetCiAState", (RTS_UINTPTR)CL2_GetCiAState, 0, 0) 
#endif



CAA_ERROR CDECL CL2_SetCiAState(CAA_HANDLE hDriver, unsigned char byState);
typedef CAA_ERROR (CDECL * PFCL2_SETCIASTATE) (CAA_HANDLE hDriver, unsigned char byState);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_SETCIASTATE_NOTIMPLEMENTED)
	#define USE_CL2_SetCiAState
	#define EXT_CL2_SetCiAState
	#define GET_CL2_SetCiAState(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_SetCiAState(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CL2_SetCiAState  FALSE
	#define EXP_CL2_SetCiAState  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_SetCiAState
	#define EXT_CL2_SetCiAState
	#define GET_CL2_SetCiAState(fl)  CAL_CMGETAPI( "CL2_SetCiAState" ) 
	#define CAL_CL2_SetCiAState  CL2_SetCiAState
	#define CHK_CL2_SetCiAState  TRUE
	#define EXP_CL2_SetCiAState  CAL_CMEXPAPI( "CL2_SetCiAState" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_SetCiAState
	#define EXT_CL2_SetCiAState
	#define GET_CL2_SetCiAState(fl)  CAL_CMGETAPI( "CL2_SetCiAState" ) 
	#define CAL_CL2_SetCiAState  CL2_SetCiAState
	#define CHK_CL2_SetCiAState  TRUE
	#define EXP_CL2_SetCiAState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_SetCiAState", (RTS_UINTPTR)CL2_SetCiAState, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_SetCiAState
	#define EXT_CmpCAACanL2CL2_SetCiAState
	#define GET_CmpCAACanL2CL2_SetCiAState  ERR_OK
	#define CAL_CmpCAACanL2CL2_SetCiAState pICmpCAACanL2->ICL2_SetCiAState
	#define CHK_CmpCAACanL2CL2_SetCiAState (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_SetCiAState  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_SetCiAState
	#define EXT_CL2_SetCiAState
	#define GET_CL2_SetCiAState(fl)  CAL_CMGETAPI( "CL2_SetCiAState" ) 
	#define CAL_CL2_SetCiAState pICmpCAACanL2->ICL2_SetCiAState
	#define CHK_CL2_SetCiAState (pICmpCAACanL2 != NULL)
	#define EXP_CL2_SetCiAState  CAL_CMEXPAPI( "CL2_SetCiAState" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_SetCiAState  PFCL2_SETCIASTATE pfCL2_SetCiAState;
	#define EXT_CL2_SetCiAState  extern PFCL2_SETCIASTATE pfCL2_SetCiAState;
	#define GET_CL2_SetCiAState(fl)  s_pfCMGetAPI2( "CL2_SetCiAState", (RTS_VOID_FCTPTR *)&pfCL2_SetCiAState, (fl), 0, 0)
	#define CAL_CL2_SetCiAState  pfCL2_SetCiAState
	#define CHK_CL2_SetCiAState  (pfCL2_SetCiAState != NULL)
	#define EXP_CL2_SetCiAState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_SetCiAState", (RTS_UINTPTR)CL2_SetCiAState, 0, 0) 
#endif




/* Properties */
CAA_UDINT CDECL CL2_GetProperty(unsigned short usPropery);
typedef CAA_UDINT (CDECL * PFCL2_GETPROPERTY) (unsigned short usPropery);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETPROPERTY_NOTIMPLEMENTED)
	#define USE_CL2_GetProperty
	#define EXT_CL2_GetProperty
	#define GET_CL2_GetProperty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetProperty(p0)  (CAA_UDINT)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetProperty  FALSE
	#define EXP_CL2_GetProperty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetProperty
	#define EXT_CL2_GetProperty
	#define GET_CL2_GetProperty(fl)  CAL_CMGETAPI( "CL2_GetProperty" ) 
	#define CAL_CL2_GetProperty  CL2_GetProperty
	#define CHK_CL2_GetProperty  TRUE
	#define EXP_CL2_GetProperty  CAL_CMEXPAPI( "CL2_GetProperty" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetProperty
	#define EXT_CL2_GetProperty
	#define GET_CL2_GetProperty(fl)  CAL_CMGETAPI( "CL2_GetProperty" ) 
	#define CAL_CL2_GetProperty  CL2_GetProperty
	#define CHK_CL2_GetProperty  TRUE
	#define EXP_CL2_GetProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetProperty", (RTS_UINTPTR)CL2_GetProperty, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetProperty
	#define EXT_CmpCAACanL2CL2_GetProperty
	#define GET_CmpCAACanL2CL2_GetProperty  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetProperty pICmpCAACanL2->ICL2_GetProperty
	#define CHK_CmpCAACanL2CL2_GetProperty (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetProperty  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetProperty
	#define EXT_CL2_GetProperty
	#define GET_CL2_GetProperty(fl)  CAL_CMGETAPI( "CL2_GetProperty" ) 
	#define CAL_CL2_GetProperty pICmpCAACanL2->ICL2_GetProperty
	#define CHK_CL2_GetProperty (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetProperty  CAL_CMEXPAPI( "CL2_GetProperty" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetProperty  PFCL2_GETPROPERTY pfCL2_GetProperty;
	#define EXT_CL2_GetProperty  extern PFCL2_GETPROPERTY pfCL2_GetProperty;
	#define GET_CL2_GetProperty(fl)  s_pfCMGetAPI2( "CL2_GetProperty", (RTS_VOID_FCTPTR *)&pfCL2_GetProperty, (fl), 0, 0)
	#define CAL_CL2_GetProperty  pfCL2_GetProperty
	#define CHK_CL2_GetProperty  (pfCL2_GetProperty != NULL)
	#define EXP_CL2_GetProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetProperty", (RTS_UINTPTR)CL2_GetProperty, 0, 0) 
#endif




/* Services for Can Mini Driver */
CAA_ERROR CDECL CL2_CmdRegister(unsigned char ucNetId, CMD_CMDRV* pCMDRV, CAA_COUNT ctMessages, CL2I_INFO** ppInfo);
typedef CAA_ERROR (CDECL * PFCL2_CMDREGISTER) (unsigned char ucNetId, CMD_CMDRV* pCMDRV, CAA_COUNT ctMessages, CL2I_INFO** ppInfo);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CMDREGISTER_NOTIMPLEMENTED)
	#define USE_CL2_CmdRegister
	#define EXT_CL2_CmdRegister
	#define GET_CL2_CmdRegister(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_CmdRegister(p0,p1,p2,p3)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CL2_CmdRegister  FALSE
	#define EXP_CL2_CmdRegister  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_CmdRegister
	#define EXT_CL2_CmdRegister
	#define GET_CL2_CmdRegister(fl)  CAL_CMGETAPI( "CL2_CmdRegister" ) 
	#define CAL_CL2_CmdRegister  CL2_CmdRegister
	#define CHK_CL2_CmdRegister  TRUE
	#define EXP_CL2_CmdRegister  CAL_CMEXPAPI( "CL2_CmdRegister" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_CmdRegister
	#define EXT_CL2_CmdRegister
	#define GET_CL2_CmdRegister(fl)  CAL_CMGETAPI( "CL2_CmdRegister" ) 
	#define CAL_CL2_CmdRegister  CL2_CmdRegister
	#define CHK_CL2_CmdRegister  TRUE
	#define EXP_CL2_CmdRegister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CmdRegister", (RTS_UINTPTR)CL2_CmdRegister, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_CmdRegister
	#define EXT_CmpCAACanL2CL2_CmdRegister
	#define GET_CmpCAACanL2CL2_CmdRegister  ERR_OK
	#define CAL_CmpCAACanL2CL2_CmdRegister pICmpCAACanL2->ICL2_CmdRegister
	#define CHK_CmpCAACanL2CL2_CmdRegister (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_CmdRegister  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_CmdRegister
	#define EXT_CL2_CmdRegister
	#define GET_CL2_CmdRegister(fl)  CAL_CMGETAPI( "CL2_CmdRegister" ) 
	#define CAL_CL2_CmdRegister pICmpCAACanL2->ICL2_CmdRegister
	#define CHK_CL2_CmdRegister (pICmpCAACanL2 != NULL)
	#define EXP_CL2_CmdRegister  CAL_CMEXPAPI( "CL2_CmdRegister" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_CmdRegister  PFCL2_CMDREGISTER pfCL2_CmdRegister;
	#define EXT_CL2_CmdRegister  extern PFCL2_CMDREGISTER pfCL2_CmdRegister;
	#define GET_CL2_CmdRegister(fl)  s_pfCMGetAPI2( "CL2_CmdRegister", (RTS_VOID_FCTPTR *)&pfCL2_CmdRegister, (fl), 0, 0)
	#define CAL_CL2_CmdRegister  pfCL2_CmdRegister
	#define CHK_CL2_CmdRegister  (pfCL2_CmdRegister != NULL)
	#define EXP_CL2_CmdRegister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CmdRegister", (RTS_UINTPTR)CL2_CmdRegister, 0, 0) 
#endif



CAA_ERROR CDECL CL2_CmdUnRegister(unsigned char ucNetId);
typedef CAA_ERROR (CDECL * PFCL2_CMDUNREGISTER) (unsigned char ucNetId);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CMDUNREGISTER_NOTIMPLEMENTED)
	#define USE_CL2_CmdUnRegister
	#define EXT_CL2_CmdUnRegister
	#define GET_CL2_CmdUnRegister(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_CmdUnRegister(p0)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CL2_CmdUnRegister  FALSE
	#define EXP_CL2_CmdUnRegister  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_CmdUnRegister
	#define EXT_CL2_CmdUnRegister
	#define GET_CL2_CmdUnRegister(fl)  CAL_CMGETAPI( "CL2_CmdUnRegister" ) 
	#define CAL_CL2_CmdUnRegister  CL2_CmdUnRegister
	#define CHK_CL2_CmdUnRegister  TRUE
	#define EXP_CL2_CmdUnRegister  CAL_CMEXPAPI( "CL2_CmdUnRegister" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_CmdUnRegister
	#define EXT_CL2_CmdUnRegister
	#define GET_CL2_CmdUnRegister(fl)  CAL_CMGETAPI( "CL2_CmdUnRegister" ) 
	#define CAL_CL2_CmdUnRegister  CL2_CmdUnRegister
	#define CHK_CL2_CmdUnRegister  TRUE
	#define EXP_CL2_CmdUnRegister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CmdUnRegister", (RTS_UINTPTR)CL2_CmdUnRegister, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_CmdUnRegister
	#define EXT_CmpCAACanL2CL2_CmdUnRegister
	#define GET_CmpCAACanL2CL2_CmdUnRegister  ERR_OK
	#define CAL_CmpCAACanL2CL2_CmdUnRegister pICmpCAACanL2->ICL2_CmdUnRegister
	#define CHK_CmpCAACanL2CL2_CmdUnRegister (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_CmdUnRegister  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_CmdUnRegister
	#define EXT_CL2_CmdUnRegister
	#define GET_CL2_CmdUnRegister(fl)  CAL_CMGETAPI( "CL2_CmdUnRegister" ) 
	#define CAL_CL2_CmdUnRegister pICmpCAACanL2->ICL2_CmdUnRegister
	#define CHK_CL2_CmdUnRegister (pICmpCAACanL2 != NULL)
	#define EXP_CL2_CmdUnRegister  CAL_CMEXPAPI( "CL2_CmdUnRegister" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_CmdUnRegister  PFCL2_CMDUNREGISTER pfCL2_CmdUnRegister;
	#define EXT_CL2_CmdUnRegister  extern PFCL2_CMDUNREGISTER pfCL2_CmdUnRegister;
	#define GET_CL2_CmdUnRegister(fl)  s_pfCMGetAPI2( "CL2_CmdUnRegister", (RTS_VOID_FCTPTR *)&pfCL2_CmdUnRegister, (fl), 0, 0)
	#define CAL_CL2_CmdUnRegister  pfCL2_CmdUnRegister
	#define CHK_CL2_CmdUnRegister  (pfCL2_CmdUnRegister != NULL)
	#define EXP_CL2_CmdUnRegister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_CmdUnRegister", (RTS_UINTPTR)CL2_CmdUnRegister, 0, 0) 
#endif




/**
 * <description> 
 *	This function can be used to determine the current number of messages in Tx Queue of a specific CAN network.
 *	It is also the number of following CMD_Send calls (if driver returns no error). So it can be used for Tx message bundling in CMD_Send.
 * </description>
 * <param name="ucNetId" type="IN">CAN Network ID</param>
 * <param name="peError" type="IN">Pointer to error</param>
 * <result>Number of messages in Tx queue</result>
 */
CAA_COUNT CDECL CL2_GetTxQueueLength(unsigned char ucNetId, CAA_ERROR* peError);
typedef CAA_COUNT (CDECL * PFCL2_GETTXQUEUELENGTH) (unsigned char ucNetId, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETTXQUEUELENGTH_NOTIMPLEMENTED)
	#define USE_CL2_GetTxQueueLength
	#define EXT_CL2_GetTxQueueLength
	#define GET_CL2_GetTxQueueLength(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetTxQueueLength(p0,p1)  (CAA_COUNT)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetTxQueueLength  FALSE
	#define EXP_CL2_GetTxQueueLength  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetTxQueueLength
	#define EXT_CL2_GetTxQueueLength
	#define GET_CL2_GetTxQueueLength(fl)  CAL_CMGETAPI( "CL2_GetTxQueueLength" ) 
	#define CAL_CL2_GetTxQueueLength  CL2_GetTxQueueLength
	#define CHK_CL2_GetTxQueueLength  TRUE
	#define EXP_CL2_GetTxQueueLength  CAL_CMEXPAPI( "CL2_GetTxQueueLength" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetTxQueueLength
	#define EXT_CL2_GetTxQueueLength
	#define GET_CL2_GetTxQueueLength(fl)  CAL_CMGETAPI( "CL2_GetTxQueueLength" ) 
	#define CAL_CL2_GetTxQueueLength  CL2_GetTxQueueLength
	#define CHK_CL2_GetTxQueueLength  TRUE
	#define EXP_CL2_GetTxQueueLength  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetTxQueueLength", (RTS_UINTPTR)CL2_GetTxQueueLength, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetTxQueueLength
	#define EXT_CmpCAACanL2CL2_GetTxQueueLength
	#define GET_CmpCAACanL2CL2_GetTxQueueLength  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetTxQueueLength pICmpCAACanL2->ICL2_GetTxQueueLength
	#define CHK_CmpCAACanL2CL2_GetTxQueueLength (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetTxQueueLength  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetTxQueueLength
	#define EXT_CL2_GetTxQueueLength
	#define GET_CL2_GetTxQueueLength(fl)  CAL_CMGETAPI( "CL2_GetTxQueueLength" ) 
	#define CAL_CL2_GetTxQueueLength pICmpCAACanL2->ICL2_GetTxQueueLength
	#define CHK_CL2_GetTxQueueLength (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetTxQueueLength  CAL_CMEXPAPI( "CL2_GetTxQueueLength" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetTxQueueLength  PFCL2_GETTXQUEUELENGTH pfCL2_GetTxQueueLength;
	#define EXT_CL2_GetTxQueueLength  extern PFCL2_GETTXQUEUELENGTH pfCL2_GetTxQueueLength;
	#define GET_CL2_GetTxQueueLength(fl)  s_pfCMGetAPI2( "CL2_GetTxQueueLength", (RTS_VOID_FCTPTR *)&pfCL2_GetTxQueueLength, (fl), 0, 0)
	#define CAL_CL2_GetTxQueueLength  pfCL2_GetTxQueueLength
	#define CHK_CL2_GetTxQueueLength  (pfCL2_GetTxQueueLength != NULL)
	#define EXP_CL2_GetTxQueueLength  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetTxQueueLength", (RTS_UINTPTR)CL2_GetTxQueueLength, 0, 0) 
#endif



CAA_HANDLE CDECL CL2_MsgAlloc(unsigned char ucNetId, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFCL2_MSGALLOC) (unsigned char ucNetId, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_MSGALLOC_NOTIMPLEMENTED)
	#define USE_CL2_MsgAlloc
	#define EXT_CL2_MsgAlloc
	#define GET_CL2_MsgAlloc(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_MsgAlloc(p0,p1)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_CL2_MsgAlloc  FALSE
	#define EXP_CL2_MsgAlloc  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_MsgAlloc
	#define EXT_CL2_MsgAlloc
	#define GET_CL2_MsgAlloc(fl)  CAL_CMGETAPI( "CL2_MsgAlloc" ) 
	#define CAL_CL2_MsgAlloc  CL2_MsgAlloc
	#define CHK_CL2_MsgAlloc  TRUE
	#define EXP_CL2_MsgAlloc  CAL_CMEXPAPI( "CL2_MsgAlloc" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_MsgAlloc
	#define EXT_CL2_MsgAlloc
	#define GET_CL2_MsgAlloc(fl)  CAL_CMGETAPI( "CL2_MsgAlloc" ) 
	#define CAL_CL2_MsgAlloc  CL2_MsgAlloc
	#define CHK_CL2_MsgAlloc  TRUE
	#define EXP_CL2_MsgAlloc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_MsgAlloc", (RTS_UINTPTR)CL2_MsgAlloc, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_MsgAlloc
	#define EXT_CmpCAACanL2CL2_MsgAlloc
	#define GET_CmpCAACanL2CL2_MsgAlloc  ERR_OK
	#define CAL_CmpCAACanL2CL2_MsgAlloc pICmpCAACanL2->ICL2_MsgAlloc
	#define CHK_CmpCAACanL2CL2_MsgAlloc (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_MsgAlloc  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_MsgAlloc
	#define EXT_CL2_MsgAlloc
	#define GET_CL2_MsgAlloc(fl)  CAL_CMGETAPI( "CL2_MsgAlloc" ) 
	#define CAL_CL2_MsgAlloc pICmpCAACanL2->ICL2_MsgAlloc
	#define CHK_CL2_MsgAlloc (pICmpCAACanL2 != NULL)
	#define EXP_CL2_MsgAlloc  CAL_CMEXPAPI( "CL2_MsgAlloc" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_MsgAlloc  PFCL2_MSGALLOC pfCL2_MsgAlloc;
	#define EXT_CL2_MsgAlloc  extern PFCL2_MSGALLOC pfCL2_MsgAlloc;
	#define GET_CL2_MsgAlloc(fl)  s_pfCMGetAPI2( "CL2_MsgAlloc", (RTS_VOID_FCTPTR *)&pfCL2_MsgAlloc, (fl), 0, 0)
	#define CAL_CL2_MsgAlloc  pfCL2_MsgAlloc
	#define CHK_CL2_MsgAlloc  (pfCL2_MsgAlloc != NULL)
	#define EXP_CL2_MsgAlloc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_MsgAlloc", (RTS_UINTPTR)CL2_MsgAlloc, 0, 0) 
#endif



CL2I_BLOCK* CDECL CL2_MsgGetData(CAA_HANDLE hBlock);
typedef CL2I_BLOCK* (CDECL * PFCL2_MSGGETDATA) (CAA_HANDLE hBlock);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_MSGGETDATA_NOTIMPLEMENTED)
	#define USE_CL2_MsgGetData
	#define EXT_CL2_MsgGetData
	#define GET_CL2_MsgGetData(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_MsgGetData(p0)  (CL2I_BLOCK*)ERR_NOTIMPLEMENTED
	#define CHK_CL2_MsgGetData  FALSE
	#define EXP_CL2_MsgGetData  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_MsgGetData
	#define EXT_CL2_MsgGetData
	#define GET_CL2_MsgGetData(fl)  CAL_CMGETAPI( "CL2_MsgGetData" ) 
	#define CAL_CL2_MsgGetData  CL2_MsgGetData
	#define CHK_CL2_MsgGetData  TRUE
	#define EXP_CL2_MsgGetData  CAL_CMEXPAPI( "CL2_MsgGetData" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_MsgGetData
	#define EXT_CL2_MsgGetData
	#define GET_CL2_MsgGetData(fl)  CAL_CMGETAPI( "CL2_MsgGetData" ) 
	#define CAL_CL2_MsgGetData  CL2_MsgGetData
	#define CHK_CL2_MsgGetData  TRUE
	#define EXP_CL2_MsgGetData  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_MsgGetData", (RTS_UINTPTR)CL2_MsgGetData, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_MsgGetData
	#define EXT_CmpCAACanL2CL2_MsgGetData
	#define GET_CmpCAACanL2CL2_MsgGetData  ERR_OK
	#define CAL_CmpCAACanL2CL2_MsgGetData pICmpCAACanL2->ICL2_MsgGetData
	#define CHK_CmpCAACanL2CL2_MsgGetData (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_MsgGetData  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_MsgGetData
	#define EXT_CL2_MsgGetData
	#define GET_CL2_MsgGetData(fl)  CAL_CMGETAPI( "CL2_MsgGetData" ) 
	#define CAL_CL2_MsgGetData pICmpCAACanL2->ICL2_MsgGetData
	#define CHK_CL2_MsgGetData (pICmpCAACanL2 != NULL)
	#define EXP_CL2_MsgGetData  CAL_CMEXPAPI( "CL2_MsgGetData" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_MsgGetData  PFCL2_MSGGETDATA pfCL2_MsgGetData;
	#define EXT_CL2_MsgGetData  extern PFCL2_MSGGETDATA pfCL2_MsgGetData;
	#define GET_CL2_MsgGetData(fl)  s_pfCMGetAPI2( "CL2_MsgGetData", (RTS_VOID_FCTPTR *)&pfCL2_MsgGetData, (fl), 0, 0)
	#define CAL_CL2_MsgGetData  pfCL2_MsgGetData
	#define CHK_CL2_MsgGetData  (pfCL2_MsgGetData != NULL)
	#define EXP_CL2_MsgGetData  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_MsgGetData", (RTS_UINTPTR)CL2_MsgGetData, 0, 0) 
#endif



CAA_ERROR CDECL CL2_MsgFree(unsigned char ucNetId, CAA_HANDLE hBlock);
typedef CAA_ERROR (CDECL * PFCL2_MSGFREE) (unsigned char ucNetId, CAA_HANDLE hBlock);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_MSGFREE_NOTIMPLEMENTED)
	#define USE_CL2_MsgFree
	#define EXT_CL2_MsgFree
	#define GET_CL2_MsgFree(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_MsgFree(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CL2_MsgFree  FALSE
	#define EXP_CL2_MsgFree  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_MsgFree
	#define EXT_CL2_MsgFree
	#define GET_CL2_MsgFree(fl)  CAL_CMGETAPI( "CL2_MsgFree" ) 
	#define CAL_CL2_MsgFree  CL2_MsgFree
	#define CHK_CL2_MsgFree  TRUE
	#define EXP_CL2_MsgFree  CAL_CMEXPAPI( "CL2_MsgFree" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_MsgFree
	#define EXT_CL2_MsgFree
	#define GET_CL2_MsgFree(fl)  CAL_CMGETAPI( "CL2_MsgFree" ) 
	#define CAL_CL2_MsgFree  CL2_MsgFree
	#define CHK_CL2_MsgFree  TRUE
	#define EXP_CL2_MsgFree  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_MsgFree", (RTS_UINTPTR)CL2_MsgFree, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_MsgFree
	#define EXT_CmpCAACanL2CL2_MsgFree
	#define GET_CmpCAACanL2CL2_MsgFree  ERR_OK
	#define CAL_CmpCAACanL2CL2_MsgFree pICmpCAACanL2->ICL2_MsgFree
	#define CHK_CmpCAACanL2CL2_MsgFree (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_MsgFree  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_MsgFree
	#define EXT_CL2_MsgFree
	#define GET_CL2_MsgFree(fl)  CAL_CMGETAPI( "CL2_MsgFree" ) 
	#define CAL_CL2_MsgFree pICmpCAACanL2->ICL2_MsgFree
	#define CHK_CL2_MsgFree (pICmpCAACanL2 != NULL)
	#define EXP_CL2_MsgFree  CAL_CMEXPAPI( "CL2_MsgFree" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_MsgFree  PFCL2_MSGFREE pfCL2_MsgFree;
	#define EXT_CL2_MsgFree  extern PFCL2_MSGFREE pfCL2_MsgFree;
	#define GET_CL2_MsgFree(fl)  s_pfCMGetAPI2( "CL2_MsgFree", (RTS_VOID_FCTPTR *)&pfCL2_MsgFree, (fl), 0, 0)
	#define CAL_CL2_MsgFree  pfCL2_MsgFree
	#define CHK_CL2_MsgFree  (pfCL2_MsgFree != NULL)
	#define EXP_CL2_MsgFree  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_MsgFree", (RTS_UINTPTR)CL2_MsgFree, 0, 0) 
#endif




/**
 * <description> 
 *	After a message has been sent successfully, the block transmitted to the CAN Mini Driver has to be returned to the CL2 layer. 
 *	This is done using the function CL2_MsgSendAcknIRQ or CL2_MsgSendAcknNoIRQ. 
 *	CL2_MsgSendAcknIRQ is designed to be used in interrupt context (e.g. Tx IRQ). The implementation is optimized for optimal chip utilization.
 *  If there are still messages in Tx Queue, CMD_Send is triggered as long as the driver signals an error (e.g. chip not ready) or Tx queue is empty. 
 *	Afterwards hBlock is processed if unequal CAA_hINVALID. After calling the function hBlock should not be used anymore by driver.
 *  
 *	Note:
 *	With 3.5 SP7 CL2_MsgSendAckn was renamed to CL2_MsgSendAcknIRQ. 
 *  CL2_MsgSendAcknNoIRQ provides a new implementation optimized for using outside interrupt context.
 * </description>
 * <param name="ucNetId" type="IN">CAN Network ID</param>
 * <param name="hBlock" type="IN">Handle of successfully sent message</param>
 * <result>error code</result>
 */
CAA_ERROR CDECL CL2_MsgSendAcknIRQ(unsigned char ucNetId, CAA_HANDLE hBlock);
typedef CAA_ERROR (CDECL * PFCL2_MSGSENDACKNIRQ) (unsigned char ucNetId, CAA_HANDLE hBlock);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_MSGSENDACKNIRQ_NOTIMPLEMENTED)
	#define USE_CL2_MsgSendAcknIRQ
	#define EXT_CL2_MsgSendAcknIRQ
	#define GET_CL2_MsgSendAcknIRQ(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_MsgSendAcknIRQ(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CL2_MsgSendAcknIRQ  FALSE
	#define EXP_CL2_MsgSendAcknIRQ  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_MsgSendAcknIRQ
	#define EXT_CL2_MsgSendAcknIRQ
	#define GET_CL2_MsgSendAcknIRQ(fl)  CAL_CMGETAPI( "CL2_MsgSendAcknIRQ" ) 
	#define CAL_CL2_MsgSendAcknIRQ  CL2_MsgSendAcknIRQ
	#define CHK_CL2_MsgSendAcknIRQ  TRUE
	#define EXP_CL2_MsgSendAcknIRQ  CAL_CMEXPAPI( "CL2_MsgSendAcknIRQ" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_MsgSendAcknIRQ
	#define EXT_CL2_MsgSendAcknIRQ
	#define GET_CL2_MsgSendAcknIRQ(fl)  CAL_CMGETAPI( "CL2_MsgSendAcknIRQ" ) 
	#define CAL_CL2_MsgSendAcknIRQ  CL2_MsgSendAcknIRQ
	#define CHK_CL2_MsgSendAcknIRQ  TRUE
	#define EXP_CL2_MsgSendAcknIRQ  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_MsgSendAcknIRQ", (RTS_UINTPTR)CL2_MsgSendAcknIRQ, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_MsgSendAcknIRQ
	#define EXT_CmpCAACanL2CL2_MsgSendAcknIRQ
	#define GET_CmpCAACanL2CL2_MsgSendAcknIRQ  ERR_OK
	#define CAL_CmpCAACanL2CL2_MsgSendAcknIRQ pICmpCAACanL2->ICL2_MsgSendAcknIRQ
	#define CHK_CmpCAACanL2CL2_MsgSendAcknIRQ (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_MsgSendAcknIRQ  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_MsgSendAcknIRQ
	#define EXT_CL2_MsgSendAcknIRQ
	#define GET_CL2_MsgSendAcknIRQ(fl)  CAL_CMGETAPI( "CL2_MsgSendAcknIRQ" ) 
	#define CAL_CL2_MsgSendAcknIRQ pICmpCAACanL2->ICL2_MsgSendAcknIRQ
	#define CHK_CL2_MsgSendAcknIRQ (pICmpCAACanL2 != NULL)
	#define EXP_CL2_MsgSendAcknIRQ  CAL_CMEXPAPI( "CL2_MsgSendAcknIRQ" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_MsgSendAcknIRQ  PFCL2_MSGSENDACKNIRQ pfCL2_MsgSendAcknIRQ;
	#define EXT_CL2_MsgSendAcknIRQ  extern PFCL2_MSGSENDACKNIRQ pfCL2_MsgSendAcknIRQ;
	#define GET_CL2_MsgSendAcknIRQ(fl)  s_pfCMGetAPI2( "CL2_MsgSendAcknIRQ", (RTS_VOID_FCTPTR *)&pfCL2_MsgSendAcknIRQ, (fl), 0, 0)
	#define CAL_CL2_MsgSendAcknIRQ  pfCL2_MsgSendAcknIRQ
	#define CHK_CL2_MsgSendAcknIRQ  (pfCL2_MsgSendAcknIRQ != NULL)
	#define EXP_CL2_MsgSendAcknIRQ  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_MsgSendAcknIRQ", (RTS_UINTPTR)CL2_MsgSendAcknIRQ, 0, 0) 
#endif




/**
 * <description> 
 *	After a message has been sent successfully, the block transmitted to the CAN Mini Driver has to be returned to the CL2 layer. 
 *	This is done using the function CL2_MsgSendAcknIRQ or CL2_MsgSendAcknNoIRQ. 
 *	CL2_MsgSendAcknNoIRQ is designed to be used outside interrupt context (e.g. CMD_Send). Function behaviour depends on hBlock:
 *	If hBlock is unequal CAA_hINVALID: hBlock is processed by CL2. After calling the function hBlock should not be used anymore.
 *	No further CMD_Send is triggered (difference to CL2_MsgSendAcknNoIRQ)!
 *	If hBlock is CAA_hINVALID: The function checks for messages in Tx Queue and tries sending them by calling CMD_Send. A call with
 *	CAA_hINVALID is only needed afterwards CMD_Send returning an error.
 *  
 *	Note:
 *	With 3.5 SP7 CL2_MsgSendAckn was renamed to CL2_MsgSendAcknIRQ. 
 *  CL2_MsgSendAcknNoIRQ provides a new implementation optimized for using outside interrupt context.
 * </description>
 * <param name="ucNetId" type="IN">CAN Network ID</param>
 * <param name="hBlock" type="IN">Handle of successfully sent message</param>
 * <result>error code</result>
 */
CAA_ERROR CDECL CL2_MsgSendAcknNoIRQ(unsigned char ucNetId, CAA_HANDLE hBlock);
typedef CAA_ERROR (CDECL * PFCL2_MSGSENDACKNNOIRQ) (unsigned char ucNetId, CAA_HANDLE hBlock);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_MSGSENDACKNNOIRQ_NOTIMPLEMENTED)
	#define USE_CL2_MsgSendAcknNoIRQ
	#define EXT_CL2_MsgSendAcknNoIRQ
	#define GET_CL2_MsgSendAcknNoIRQ(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_MsgSendAcknNoIRQ(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CL2_MsgSendAcknNoIRQ  FALSE
	#define EXP_CL2_MsgSendAcknNoIRQ  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_MsgSendAcknNoIRQ
	#define EXT_CL2_MsgSendAcknNoIRQ
	#define GET_CL2_MsgSendAcknNoIRQ(fl)  CAL_CMGETAPI( "CL2_MsgSendAcknNoIRQ" ) 
	#define CAL_CL2_MsgSendAcknNoIRQ  CL2_MsgSendAcknNoIRQ
	#define CHK_CL2_MsgSendAcknNoIRQ  TRUE
	#define EXP_CL2_MsgSendAcknNoIRQ  CAL_CMEXPAPI( "CL2_MsgSendAcknNoIRQ" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_MsgSendAcknNoIRQ
	#define EXT_CL2_MsgSendAcknNoIRQ
	#define GET_CL2_MsgSendAcknNoIRQ(fl)  CAL_CMGETAPI( "CL2_MsgSendAcknNoIRQ" ) 
	#define CAL_CL2_MsgSendAcknNoIRQ  CL2_MsgSendAcknNoIRQ
	#define CHK_CL2_MsgSendAcknNoIRQ  TRUE
	#define EXP_CL2_MsgSendAcknNoIRQ  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_MsgSendAcknNoIRQ", (RTS_UINTPTR)CL2_MsgSendAcknNoIRQ, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_MsgSendAcknNoIRQ
	#define EXT_CmpCAACanL2CL2_MsgSendAcknNoIRQ
	#define GET_CmpCAACanL2CL2_MsgSendAcknNoIRQ  ERR_OK
	#define CAL_CmpCAACanL2CL2_MsgSendAcknNoIRQ pICmpCAACanL2->ICL2_MsgSendAcknNoIRQ
	#define CHK_CmpCAACanL2CL2_MsgSendAcknNoIRQ (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_MsgSendAcknNoIRQ  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_MsgSendAcknNoIRQ
	#define EXT_CL2_MsgSendAcknNoIRQ
	#define GET_CL2_MsgSendAcknNoIRQ(fl)  CAL_CMGETAPI( "CL2_MsgSendAcknNoIRQ" ) 
	#define CAL_CL2_MsgSendAcknNoIRQ pICmpCAACanL2->ICL2_MsgSendAcknNoIRQ
	#define CHK_CL2_MsgSendAcknNoIRQ (pICmpCAACanL2 != NULL)
	#define EXP_CL2_MsgSendAcknNoIRQ  CAL_CMEXPAPI( "CL2_MsgSendAcknNoIRQ" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_MsgSendAcknNoIRQ  PFCL2_MSGSENDACKNNOIRQ pfCL2_MsgSendAcknNoIRQ;
	#define EXT_CL2_MsgSendAcknNoIRQ  extern PFCL2_MSGSENDACKNNOIRQ pfCL2_MsgSendAcknNoIRQ;
	#define GET_CL2_MsgSendAcknNoIRQ(fl)  s_pfCMGetAPI2( "CL2_MsgSendAcknNoIRQ", (RTS_VOID_FCTPTR *)&pfCL2_MsgSendAcknNoIRQ, (fl), 0, 0)
	#define CAL_CL2_MsgSendAcknNoIRQ  pfCL2_MsgSendAcknNoIRQ
	#define CHK_CL2_MsgSendAcknNoIRQ  (pfCL2_MsgSendAcknNoIRQ != NULL)
	#define EXP_CL2_MsgSendAcknNoIRQ  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_MsgSendAcknNoIRQ", (RTS_UINTPTR)CL2_MsgSendAcknNoIRQ, 0, 0) 
#endif



CAA_ERROR CDECL CL2_MsgPutRQueue(unsigned char ucNetId, CAA_HANDLE hBlock);
typedef CAA_ERROR (CDECL * PFCL2_MSGPUTRQUEUE) (unsigned char ucNetId, CAA_HANDLE hBlock);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_MSGPUTRQUEUE_NOTIMPLEMENTED)
	#define USE_CL2_MsgPutRQueue
	#define EXT_CL2_MsgPutRQueue
	#define GET_CL2_MsgPutRQueue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_MsgPutRQueue(p0,p1)  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_CL2_MsgPutRQueue  FALSE
	#define EXP_CL2_MsgPutRQueue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_MsgPutRQueue
	#define EXT_CL2_MsgPutRQueue
	#define GET_CL2_MsgPutRQueue(fl)  CAL_CMGETAPI( "CL2_MsgPutRQueue" ) 
	#define CAL_CL2_MsgPutRQueue  CL2_MsgPutRQueue
	#define CHK_CL2_MsgPutRQueue  TRUE
	#define EXP_CL2_MsgPutRQueue  CAL_CMEXPAPI( "CL2_MsgPutRQueue" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_MsgPutRQueue
	#define EXT_CL2_MsgPutRQueue
	#define GET_CL2_MsgPutRQueue(fl)  CAL_CMGETAPI( "CL2_MsgPutRQueue" ) 
	#define CAL_CL2_MsgPutRQueue  CL2_MsgPutRQueue
	#define CHK_CL2_MsgPutRQueue  TRUE
	#define EXP_CL2_MsgPutRQueue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_MsgPutRQueue", (RTS_UINTPTR)CL2_MsgPutRQueue, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_MsgPutRQueue
	#define EXT_CmpCAACanL2CL2_MsgPutRQueue
	#define GET_CmpCAACanL2CL2_MsgPutRQueue  ERR_OK
	#define CAL_CmpCAACanL2CL2_MsgPutRQueue pICmpCAACanL2->ICL2_MsgPutRQueue
	#define CHK_CmpCAACanL2CL2_MsgPutRQueue (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_MsgPutRQueue  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_MsgPutRQueue
	#define EXT_CL2_MsgPutRQueue
	#define GET_CL2_MsgPutRQueue(fl)  CAL_CMGETAPI( "CL2_MsgPutRQueue" ) 
	#define CAL_CL2_MsgPutRQueue pICmpCAACanL2->ICL2_MsgPutRQueue
	#define CHK_CL2_MsgPutRQueue (pICmpCAACanL2 != NULL)
	#define EXP_CL2_MsgPutRQueue  CAL_CMEXPAPI( "CL2_MsgPutRQueue" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_MsgPutRQueue  PFCL2_MSGPUTRQUEUE pfCL2_MsgPutRQueue;
	#define EXT_CL2_MsgPutRQueue  extern PFCL2_MSGPUTRQUEUE pfCL2_MsgPutRQueue;
	#define GET_CL2_MsgPutRQueue(fl)  s_pfCMGetAPI2( "CL2_MsgPutRQueue", (RTS_VOID_FCTPTR *)&pfCL2_MsgPutRQueue, (fl), 0, 0)
	#define CAL_CL2_MsgPutRQueue  pfCL2_MsgPutRQueue
	#define CHK_CL2_MsgPutRQueue  (pfCL2_MsgPutRQueue != NULL)
	#define EXP_CL2_MsgPutRQueue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_MsgPutRQueue", (RTS_UINTPTR)CL2_MsgPutRQueue, 0, 0) 
#endif



CAA_HANDLE CDECL CL2_MsgClone(unsigned char ucNetId, CAA_HANDLE hBlock, CAA_ERROR* peError);
typedef CAA_HANDLE (CDECL * PFCL2_MSGCLONE) (unsigned char ucNetId, CAA_HANDLE hBlock, CAA_ERROR* peError);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_MSGCLONE_NOTIMPLEMENTED)
	#define USE_CL2_MsgClone
	#define EXT_CL2_MsgClone
	#define GET_CL2_MsgClone(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_MsgClone(p0,p1,p2)  (CAA_HANDLE)ERR_NOTIMPLEMENTED
	#define CHK_CL2_MsgClone  FALSE
	#define EXP_CL2_MsgClone  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_MsgClone
	#define EXT_CL2_MsgClone
	#define GET_CL2_MsgClone(fl)  CAL_CMGETAPI( "CL2_MsgClone" ) 
	#define CAL_CL2_MsgClone  CL2_MsgClone
	#define CHK_CL2_MsgClone  TRUE
	#define EXP_CL2_MsgClone  CAL_CMEXPAPI( "CL2_MsgClone" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_MsgClone
	#define EXT_CL2_MsgClone
	#define GET_CL2_MsgClone(fl)  CAL_CMGETAPI( "CL2_MsgClone" ) 
	#define CAL_CL2_MsgClone  CL2_MsgClone
	#define CHK_CL2_MsgClone  TRUE
	#define EXP_CL2_MsgClone  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_MsgClone", (RTS_UINTPTR)CL2_MsgClone, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_MsgClone
	#define EXT_CmpCAACanL2CL2_MsgClone
	#define GET_CmpCAACanL2CL2_MsgClone  ERR_OK
	#define CAL_CmpCAACanL2CL2_MsgClone pICmpCAACanL2->ICL2_MsgClone
	#define CHK_CmpCAACanL2CL2_MsgClone (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_MsgClone  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_MsgClone
	#define EXT_CL2_MsgClone
	#define GET_CL2_MsgClone(fl)  CAL_CMGETAPI( "CL2_MsgClone" ) 
	#define CAL_CL2_MsgClone pICmpCAACanL2->ICL2_MsgClone
	#define CHK_CL2_MsgClone (pICmpCAACanL2 != NULL)
	#define EXP_CL2_MsgClone  CAL_CMEXPAPI( "CL2_MsgClone" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_MsgClone  PFCL2_MSGCLONE pfCL2_MsgClone;
	#define EXT_CL2_MsgClone  extern PFCL2_MSGCLONE pfCL2_MsgClone;
	#define GET_CL2_MsgClone(fl)  s_pfCMGetAPI2( "CL2_MsgClone", (RTS_VOID_FCTPTR *)&pfCL2_MsgClone, (fl), 0, 0)
	#define CAL_CL2_MsgClone  pfCL2_MsgClone
	#define CHK_CL2_MsgClone  (pfCL2_MsgClone != NULL)
	#define EXP_CL2_MsgClone  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_MsgClone", (RTS_UINTPTR)CL2_MsgClone, 0, 0) 
#endif




unsigned short CDECL CL2_GetSupplierVersion(CAA_BOOL xDummy);
typedef unsigned short (CDECL * PFCL2_GETSUPPLIERVERSION) (CAA_BOOL xDummy);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_CL2_GetSupplierVersion
	#define EXT_CL2_GetSupplierVersion
	#define GET_CL2_GetSupplierVersion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CL2_GetSupplierVersion(p0)  (unsigned short)ERR_NOTIMPLEMENTED
	#define CHK_CL2_GetSupplierVersion  FALSE
	#define EXP_CL2_GetSupplierVersion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CL2_GetSupplierVersion
	#define EXT_CL2_GetSupplierVersion
	#define GET_CL2_GetSupplierVersion(fl)  CAL_CMGETAPI( "CL2_GetSupplierVersion" ) 
	#define CAL_CL2_GetSupplierVersion  CL2_GetSupplierVersion
	#define CHK_CL2_GetSupplierVersion  TRUE
	#define EXP_CL2_GetSupplierVersion  CAL_CMEXPAPI( "CL2_GetSupplierVersion" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_CL2_GetSupplierVersion
	#define EXT_CL2_GetSupplierVersion
	#define GET_CL2_GetSupplierVersion(fl)  CAL_CMGETAPI( "CL2_GetSupplierVersion" ) 
	#define CAL_CL2_GetSupplierVersion  CL2_GetSupplierVersion
	#define CHK_CL2_GetSupplierVersion  TRUE
	#define EXP_CL2_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetSupplierVersion", (RTS_UINTPTR)CL2_GetSupplierVersion, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2CL2_GetSupplierVersion
	#define EXT_CmpCAACanL2CL2_GetSupplierVersion
	#define GET_CmpCAACanL2CL2_GetSupplierVersion  ERR_OK
	#define CAL_CmpCAACanL2CL2_GetSupplierVersion pICmpCAACanL2->ICL2_GetSupplierVersion
	#define CHK_CmpCAACanL2CL2_GetSupplierVersion (pICmpCAACanL2 != NULL)
	#define EXP_CmpCAACanL2CL2_GetSupplierVersion  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CL2_GetSupplierVersion
	#define EXT_CL2_GetSupplierVersion
	#define GET_CL2_GetSupplierVersion(fl)  CAL_CMGETAPI( "CL2_GetSupplierVersion" ) 
	#define CAL_CL2_GetSupplierVersion pICmpCAACanL2->ICL2_GetSupplierVersion
	#define CHK_CL2_GetSupplierVersion (pICmpCAACanL2 != NULL)
	#define EXP_CL2_GetSupplierVersion  CAL_CMEXPAPI( "CL2_GetSupplierVersion" ) 
#else /* DYNAMIC_LINK */
	#define USE_CL2_GetSupplierVersion  PFCL2_GETSUPPLIERVERSION pfCL2_GetSupplierVersion;
	#define EXT_CL2_GetSupplierVersion  extern PFCL2_GETSUPPLIERVERSION pfCL2_GetSupplierVersion;
	#define GET_CL2_GetSupplierVersion(fl)  s_pfCMGetAPI2( "CL2_GetSupplierVersion", (RTS_VOID_FCTPTR *)&pfCL2_GetSupplierVersion, (fl), 0, 0)
	#define CAL_CL2_GetSupplierVersion  pfCL2_GetSupplierVersion
	#define CHK_CL2_GetSupplierVersion  (pfCL2_GetSupplierVersion != NULL)
	#define EXP_CL2_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CL2_GetSupplierVersion", (RTS_UINTPTR)CL2_GetSupplierVersion, 0, 0) 
#endif




/**
 * <description>cl2_driveropenp</description>
 */
typedef struct tagcl2_driveropenp_struct
{
	RTS_IEC_USINT usiNetId;				/* VAR_INPUT */
	RTS_IEC_UINT uiBaudrate;			/* VAR_INPUT */
	CAA_BOOL xSupport29Bits;			/* VAR_INPUT */
	CAA_SIZE szMemSize;					/* VAR_INPUT */
	CAA_PVOID* pMemory;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE DriverOpenP;				/* VAR_OUTPUT */
} cl2_driveropenp_struct;

void CDECL CDECL_EXT cl2_driveropenp(cl2_driveropenp_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_DRIVEROPENP_IEC) (cl2_driveropenp_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_DRIVEROPENP_NOTIMPLEMENTED)
	#define USE_cl2_driveropenp
	#define EXT_cl2_driveropenp
	#define GET_cl2_driveropenp(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_driveropenp(p0) 
	#define CHK_cl2_driveropenp  FALSE
	#define EXP_cl2_driveropenp  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_driveropenp
	#define EXT_cl2_driveropenp
	#define GET_cl2_driveropenp(fl)  CAL_CMGETAPI( "cl2_driveropenp" ) 
	#define CAL_cl2_driveropenp  cl2_driveropenp
	#define CHK_cl2_driveropenp  TRUE
	#define EXP_cl2_driveropenp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_driveropenp", (RTS_UINTPTR)cl2_driveropenp, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_driveropenp
	#define EXT_cl2_driveropenp
	#define GET_cl2_driveropenp(fl)  CAL_CMGETAPI( "cl2_driveropenp" ) 
	#define CAL_cl2_driveropenp  cl2_driveropenp
	#define CHK_cl2_driveropenp  TRUE
	#define EXP_cl2_driveropenp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_driveropenp", (RTS_UINTPTR)cl2_driveropenp, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_driveropenp
	#define EXT_CmpCAACanL2cl2_driveropenp
	#define GET_CmpCAACanL2cl2_driveropenp  ERR_OK
	#define CAL_CmpCAACanL2cl2_driveropenp  cl2_driveropenp
	#define CHK_CmpCAACanL2cl2_driveropenp  TRUE
	#define EXP_CmpCAACanL2cl2_driveropenp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_driveropenp", (RTS_UINTPTR)cl2_driveropenp, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_driveropenp
	#define EXT_cl2_driveropenp
	#define GET_cl2_driveropenp(fl)  CAL_CMGETAPI( "cl2_driveropenp" ) 
	#define CAL_cl2_driveropenp  cl2_driveropenp
	#define CHK_cl2_driveropenp  TRUE
	#define EXP_cl2_driveropenp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_driveropenp", (RTS_UINTPTR)cl2_driveropenp, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_driveropenp  PFCL2_DRIVEROPENP_IEC pfcl2_driveropenp;
	#define EXT_cl2_driveropenp  extern PFCL2_DRIVEROPENP_IEC pfcl2_driveropenp;
	#define GET_cl2_driveropenp(fl)  s_pfCMGetAPI2( "cl2_driveropenp", (RTS_VOID_FCTPTR *)&pfcl2_driveropenp, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_driveropenp  pfcl2_driveropenp
	#define CHK_cl2_driveropenp  (pfcl2_driveropenp != NULL)
	#define EXP_cl2_driveropenp   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_driveropenp", (RTS_UINTPTR)cl2_driveropenp, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_cstcyclestart</description>
 */
typedef struct tagcl2_cstcyclestart_struct
{
	CAA_HANDLE hCstCycle;				/* VAR_INPUT */
	CAA_ERROR CstCycleStart;			/* VAR_OUTPUT */
} cl2_cstcyclestart_struct;

void CDECL CDECL_EXT cl2_cstcyclestart(cl2_cstcyclestart_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_CSTCYCLESTART_IEC) (cl2_cstcyclestart_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CSTCYCLESTART_NOTIMPLEMENTED)
	#define USE_cl2_cstcyclestart
	#define EXT_cl2_cstcyclestart
	#define GET_cl2_cstcyclestart(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_cstcyclestart(p0) 
	#define CHK_cl2_cstcyclestart  FALSE
	#define EXP_cl2_cstcyclestart  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_cstcyclestart
	#define EXT_cl2_cstcyclestart
	#define GET_cl2_cstcyclestart(fl)  CAL_CMGETAPI( "cl2_cstcyclestart" ) 
	#define CAL_cl2_cstcyclestart  cl2_cstcyclestart
	#define CHK_cl2_cstcyclestart  TRUE
	#define EXP_cl2_cstcyclestart  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcyclestart", (RTS_UINTPTR)cl2_cstcyclestart, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_cstcyclestart
	#define EXT_cl2_cstcyclestart
	#define GET_cl2_cstcyclestart(fl)  CAL_CMGETAPI( "cl2_cstcyclestart" ) 
	#define CAL_cl2_cstcyclestart  cl2_cstcyclestart
	#define CHK_cl2_cstcyclestart  TRUE
	#define EXP_cl2_cstcyclestart  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcyclestart", (RTS_UINTPTR)cl2_cstcyclestart, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_cstcyclestart
	#define EXT_CmpCAACanL2cl2_cstcyclestart
	#define GET_CmpCAACanL2cl2_cstcyclestart  ERR_OK
	#define CAL_CmpCAACanL2cl2_cstcyclestart  cl2_cstcyclestart
	#define CHK_CmpCAACanL2cl2_cstcyclestart  TRUE
	#define EXP_CmpCAACanL2cl2_cstcyclestart  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcyclestart", (RTS_UINTPTR)cl2_cstcyclestart, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_cstcyclestart
	#define EXT_cl2_cstcyclestart
	#define GET_cl2_cstcyclestart(fl)  CAL_CMGETAPI( "cl2_cstcyclestart" ) 
	#define CAL_cl2_cstcyclestart  cl2_cstcyclestart
	#define CHK_cl2_cstcyclestart  TRUE
	#define EXP_cl2_cstcyclestart  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcyclestart", (RTS_UINTPTR)cl2_cstcyclestart, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_cstcyclestart  PFCL2_CSTCYCLESTART_IEC pfcl2_cstcyclestart;
	#define EXT_cl2_cstcyclestart  extern PFCL2_CSTCYCLESTART_IEC pfcl2_cstcyclestart;
	#define GET_cl2_cstcyclestart(fl)  s_pfCMGetAPI2( "cl2_cstcyclestart", (RTS_VOID_FCTPTR *)&pfcl2_cstcyclestart, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_cstcyclestart  pfcl2_cstcyclestart
	#define CHK_cl2_cstcyclestart  (pfcl2_cstcyclestart != NULL)
	#define EXP_cl2_cstcyclestart   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcyclestart", (RTS_UINTPTR)cl2_cstcyclestart, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_updatetimeservice</description>
 */
typedef struct tagcl2_updatetimeservice_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	RTS_IEC_TIME_OF_DAY todTime;		/* VAR_INPUT */
	RTS_IEC_DATE datDate;				/* VAR_INPUT */
	CAA_ERROR UpdateTimeService;		/* VAR_OUTPUT */
} cl2_updatetimeservice_struct;

void CDECL CDECL_EXT cl2_updatetimeservice(cl2_updatetimeservice_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_UPDATETIMESERVICE_IEC) (cl2_updatetimeservice_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_UPDATETIMESERVICE_NOTIMPLEMENTED)
	#define USE_cl2_updatetimeservice
	#define EXT_cl2_updatetimeservice
	#define GET_cl2_updatetimeservice(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_updatetimeservice(p0) 
	#define CHK_cl2_updatetimeservice  FALSE
	#define EXP_cl2_updatetimeservice  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_updatetimeservice
	#define EXT_cl2_updatetimeservice
	#define GET_cl2_updatetimeservice(fl)  CAL_CMGETAPI( "cl2_updatetimeservice" ) 
	#define CAL_cl2_updatetimeservice  cl2_updatetimeservice
	#define CHK_cl2_updatetimeservice  TRUE
	#define EXP_cl2_updatetimeservice  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_updatetimeservice", (RTS_UINTPTR)cl2_updatetimeservice, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_updatetimeservice
	#define EXT_cl2_updatetimeservice
	#define GET_cl2_updatetimeservice(fl)  CAL_CMGETAPI( "cl2_updatetimeservice" ) 
	#define CAL_cl2_updatetimeservice  cl2_updatetimeservice
	#define CHK_cl2_updatetimeservice  TRUE
	#define EXP_cl2_updatetimeservice  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_updatetimeservice", (RTS_UINTPTR)cl2_updatetimeservice, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_updatetimeservice
	#define EXT_CmpCAACanL2cl2_updatetimeservice
	#define GET_CmpCAACanL2cl2_updatetimeservice  ERR_OK
	#define CAL_CmpCAACanL2cl2_updatetimeservice  cl2_updatetimeservice
	#define CHK_CmpCAACanL2cl2_updatetimeservice  TRUE
	#define EXP_CmpCAACanL2cl2_updatetimeservice  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_updatetimeservice", (RTS_UINTPTR)cl2_updatetimeservice, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_updatetimeservice
	#define EXT_cl2_updatetimeservice
	#define GET_cl2_updatetimeservice(fl)  CAL_CMGETAPI( "cl2_updatetimeservice" ) 
	#define CAL_cl2_updatetimeservice  cl2_updatetimeservice
	#define CHK_cl2_updatetimeservice  TRUE
	#define EXP_cl2_updatetimeservice  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_updatetimeservice", (RTS_UINTPTR)cl2_updatetimeservice, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_updatetimeservice  PFCL2_UPDATETIMESERVICE_IEC pfcl2_updatetimeservice;
	#define EXT_cl2_updatetimeservice  extern PFCL2_UPDATETIMESERVICE_IEC pfcl2_updatetimeservice;
	#define GET_cl2_updatetimeservice(fl)  s_pfCMGetAPI2( "cl2_updatetimeservice", (RTS_VOID_FCTPTR *)&pfcl2_updatetimeservice, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_updatetimeservice  pfcl2_updatetimeservice
	#define CHK_cl2_updatetimeservice  (pfcl2_updatetimeservice != NULL)
	#define EXP_cl2_updatetimeservice   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_updatetimeservice", (RTS_UINTPTR)cl2_updatetimeservice, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_getmsgcount</description>
 */
typedef struct tagcl2_getmsgcount_struct
{
	CAA_HANDLE hReceiverId;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_COUNT GetMsgCount;				/* VAR_OUTPUT */
} cl2_getmsgcount_struct;

void CDECL CDECL_EXT cl2_getmsgcount(cl2_getmsgcount_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_GETMSGCOUNT_IEC) (cl2_getmsgcount_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETMSGCOUNT_NOTIMPLEMENTED)
	#define USE_cl2_getmsgcount
	#define EXT_cl2_getmsgcount
	#define GET_cl2_getmsgcount(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_getmsgcount(p0) 
	#define CHK_cl2_getmsgcount  FALSE
	#define EXP_cl2_getmsgcount  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_getmsgcount
	#define EXT_cl2_getmsgcount
	#define GET_cl2_getmsgcount(fl)  CAL_CMGETAPI( "cl2_getmsgcount" ) 
	#define CAL_cl2_getmsgcount  cl2_getmsgcount
	#define CHK_cl2_getmsgcount  TRUE
	#define EXP_cl2_getmsgcount  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getmsgcount", (RTS_UINTPTR)cl2_getmsgcount, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_getmsgcount
	#define EXT_cl2_getmsgcount
	#define GET_cl2_getmsgcount(fl)  CAL_CMGETAPI( "cl2_getmsgcount" ) 
	#define CAL_cl2_getmsgcount  cl2_getmsgcount
	#define CHK_cl2_getmsgcount  TRUE
	#define EXP_cl2_getmsgcount  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getmsgcount", (RTS_UINTPTR)cl2_getmsgcount, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_getmsgcount
	#define EXT_CmpCAACanL2cl2_getmsgcount
	#define GET_CmpCAACanL2cl2_getmsgcount  ERR_OK
	#define CAL_CmpCAACanL2cl2_getmsgcount  cl2_getmsgcount
	#define CHK_CmpCAACanL2cl2_getmsgcount  TRUE
	#define EXP_CmpCAACanL2cl2_getmsgcount  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getmsgcount", (RTS_UINTPTR)cl2_getmsgcount, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_getmsgcount
	#define EXT_cl2_getmsgcount
	#define GET_cl2_getmsgcount(fl)  CAL_CMGETAPI( "cl2_getmsgcount" ) 
	#define CAL_cl2_getmsgcount  cl2_getmsgcount
	#define CHK_cl2_getmsgcount  TRUE
	#define EXP_cl2_getmsgcount  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getmsgcount", (RTS_UINTPTR)cl2_getmsgcount, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_getmsgcount  PFCL2_GETMSGCOUNT_IEC pfcl2_getmsgcount;
	#define EXT_cl2_getmsgcount  extern PFCL2_GETMSGCOUNT_IEC pfcl2_getmsgcount;
	#define GET_cl2_getmsgcount(fl)  s_pfCMGetAPI2( "cl2_getmsgcount", (RTS_VOID_FCTPTR *)&pfcl2_getmsgcount, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_getmsgcount  pfcl2_getmsgcount
	#define CHK_cl2_getmsgcount  (pfcl2_getmsgcount != NULL)
	#define EXP_cl2_getmsgcount   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getmsgcount", (RTS_UINTPTR)cl2_getmsgcount, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_enablesyncservice</description>
 */
typedef struct tagenablesyncservice_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CL2I_COBID cobID;						/* VAR_INPUT */
	CAA_BOOL xSyncProducer;				/* VAR_INPUT */
	CAA_BOOL xEnableSyncEvent;			/* VAR_INPUT */
	RTS_IEC_UDINT udiSyncCycle;			/* VAR_INPUT */
	RTS_IEC_UDINT udiSyncWindowLength;	/* VAR_INPUT */
	RTS_IEC_UDINT udiSyncForewarnTime;	/* VAR_INPUT */
	CAA_ERROR EnableSyncService;		/* VAR_OUTPUT */
} cl2_enablesyncservice_struct;

void CDECL CDECL_EXT cl2_enablesyncservice(cl2_enablesyncservice_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_ENABLESYNCSERVICE_IEC) (cl2_enablesyncservice_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_ENABLESYNCSERVICE_NOTIMPLEMENTED)
	#define USE_cl2_enablesyncservice
	#define EXT_cl2_enablesyncservice
	#define GET_cl2_enablesyncservice(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_enablesyncservice(p0) 
	#define CHK_cl2_enablesyncservice  FALSE
	#define EXP_cl2_enablesyncservice  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_enablesyncservice
	#define EXT_cl2_enablesyncservice
	#define GET_cl2_enablesyncservice(fl)  CAL_CMGETAPI( "cl2_enablesyncservice" ) 
	#define CAL_cl2_enablesyncservice  cl2_enablesyncservice
	#define CHK_cl2_enablesyncservice  TRUE
	#define EXP_cl2_enablesyncservice  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_enablesyncservice", (RTS_UINTPTR)cl2_enablesyncservice, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_enablesyncservice
	#define EXT_cl2_enablesyncservice
	#define GET_cl2_enablesyncservice(fl)  CAL_CMGETAPI( "cl2_enablesyncservice" ) 
	#define CAL_cl2_enablesyncservice  cl2_enablesyncservice
	#define CHK_cl2_enablesyncservice  TRUE
	#define EXP_cl2_enablesyncservice  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_enablesyncservice", (RTS_UINTPTR)cl2_enablesyncservice, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_enablesyncservice
	#define EXT_CmpCAACanL2cl2_enablesyncservice
	#define GET_CmpCAACanL2cl2_enablesyncservice  ERR_OK
	#define CAL_CmpCAACanL2cl2_enablesyncservice  cl2_enablesyncservice
	#define CHK_CmpCAACanL2cl2_enablesyncservice  TRUE
	#define EXP_CmpCAACanL2cl2_enablesyncservice  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_enablesyncservice", (RTS_UINTPTR)cl2_enablesyncservice, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_enablesyncservice
	#define EXT_cl2_enablesyncservice
	#define GET_cl2_enablesyncservice(fl)  CAL_CMGETAPI( "cl2_enablesyncservice" ) 
	#define CAL_cl2_enablesyncservice  cl2_enablesyncservice
	#define CHK_cl2_enablesyncservice  TRUE
	#define EXP_cl2_enablesyncservice  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_enablesyncservice", (RTS_UINTPTR)cl2_enablesyncservice, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_enablesyncservice  PFCL2_ENABLESYNCSERVICE_IEC pfcl2_enablesyncservice;
	#define EXT_cl2_enablesyncservice  extern PFCL2_ENABLESYNCSERVICE_IEC pfcl2_enablesyncservice;
	#define GET_cl2_enablesyncservice(fl)  s_pfCMGetAPI2( "cl2_enablesyncservice", (RTS_VOID_FCTPTR *)&pfcl2_enablesyncservice, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_enablesyncservice  pfcl2_enablesyncservice
	#define CHK_cl2_enablesyncservice  (pfcl2_enablesyncservice != NULL)
	#define EXP_cl2_enablesyncservice   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_enablesyncservice", (RTS_UINTPTR)cl2_enablesyncservice, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_disabletimeservice</description>
 */
typedef struct tagcl2_disabletimeservice_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR DisableTimeService;		/* VAR_OUTPUT */
} cl2_disabletimeservice_struct;

void CDECL CDECL_EXT cl2_disabletimeservice(cl2_disabletimeservice_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_DISABLETIMESERVICE_IEC) (cl2_disabletimeservice_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_DISABLETIMESERVICE_NOTIMPLEMENTED)
	#define USE_cl2_disabletimeservice
	#define EXT_cl2_disabletimeservice
	#define GET_cl2_disabletimeservice(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_disabletimeservice(p0) 
	#define CHK_cl2_disabletimeservice  FALSE
	#define EXP_cl2_disabletimeservice  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_disabletimeservice
	#define EXT_cl2_disabletimeservice
	#define GET_cl2_disabletimeservice(fl)  CAL_CMGETAPI( "cl2_disabletimeservice" ) 
	#define CAL_cl2_disabletimeservice  cl2_disabletimeservice
	#define CHK_cl2_disabletimeservice  TRUE
	#define EXP_cl2_disabletimeservice  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_disabletimeservice", (RTS_UINTPTR)cl2_disabletimeservice, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_disabletimeservice
	#define EXT_cl2_disabletimeservice
	#define GET_cl2_disabletimeservice(fl)  CAL_CMGETAPI( "cl2_disabletimeservice" ) 
	#define CAL_cl2_disabletimeservice  cl2_disabletimeservice
	#define CHK_cl2_disabletimeservice  TRUE
	#define EXP_cl2_disabletimeservice  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_disabletimeservice", (RTS_UINTPTR)cl2_disabletimeservice, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_disabletimeservice
	#define EXT_CmpCAACanL2cl2_disabletimeservice
	#define GET_CmpCAACanL2cl2_disabletimeservice  ERR_OK
	#define CAL_CmpCAACanL2cl2_disabletimeservice  cl2_disabletimeservice
	#define CHK_CmpCAACanL2cl2_disabletimeservice  TRUE
	#define EXP_CmpCAACanL2cl2_disabletimeservice  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_disabletimeservice", (RTS_UINTPTR)cl2_disabletimeservice, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_disabletimeservice
	#define EXT_cl2_disabletimeservice
	#define GET_cl2_disabletimeservice(fl)  CAL_CMGETAPI( "cl2_disabletimeservice" ) 
	#define CAL_cl2_disabletimeservice  cl2_disabletimeservice
	#define CHK_cl2_disabletimeservice  TRUE
	#define EXP_cl2_disabletimeservice  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_disabletimeservice", (RTS_UINTPTR)cl2_disabletimeservice, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_disabletimeservice  PFCL2_DISABLETIMESERVICE_IEC pfcl2_disabletimeservice;
	#define EXT_cl2_disabletimeservice  extern PFCL2_DISABLETIMESERVICE_IEC pfcl2_disabletimeservice;
	#define GET_cl2_disabletimeservice(fl)  s_pfCMGetAPI2( "cl2_disabletimeservice", (RTS_VOID_FCTPTR *)&pfcl2_disabletimeservice, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_disabletimeservice  pfcl2_disabletimeservice
	#define CHK_cl2_disabletimeservice  (pfcl2_disabletimeservice != NULL)
	#define EXP_cl2_disabletimeservice   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_disabletimeservice", (RTS_UINTPTR)cl2_disabletimeservice, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_enabletimeservice</description>
 */
typedef struct tagcl2_enabletimeservice_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CL2I_COBID cobID;						/* VAR_INPUT */
	CAA_BOOL xTimeProducer;				/* VAR_INPUT */
	CAA_BOOL xEnableTimeEvent;			/* VAR_INPUT */
	RTS_IEC_UDINT udiTimeCycle;			/* VAR_INPUT */
	RTS_IEC_UDINT udiTimeForewarnTime;	/* VAR_INPUT */
	CAA_ERROR EnableTimeService;		/* VAR_OUTPUT */
} cl2_enabletimeservice_struct;

void CDECL CDECL_EXT cl2_enabletimeservice(cl2_enabletimeservice_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_ENABLETIMESERVICE_IEC) (cl2_enabletimeservice_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_ENABLETIMESERVICE_NOTIMPLEMENTED)
	#define USE_cl2_enabletimeservice
	#define EXT_cl2_enabletimeservice
	#define GET_cl2_enabletimeservice(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_enabletimeservice(p0) 
	#define CHK_cl2_enabletimeservice  FALSE
	#define EXP_cl2_enabletimeservice  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_enabletimeservice
	#define EXT_cl2_enabletimeservice
	#define GET_cl2_enabletimeservice(fl)  CAL_CMGETAPI( "cl2_enabletimeservice" ) 
	#define CAL_cl2_enabletimeservice  cl2_enabletimeservice
	#define CHK_cl2_enabletimeservice  TRUE
	#define EXP_cl2_enabletimeservice  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_enabletimeservice", (RTS_UINTPTR)cl2_enabletimeservice, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_enabletimeservice
	#define EXT_cl2_enabletimeservice
	#define GET_cl2_enabletimeservice(fl)  CAL_CMGETAPI( "cl2_enabletimeservice" ) 
	#define CAL_cl2_enabletimeservice  cl2_enabletimeservice
	#define CHK_cl2_enabletimeservice  TRUE
	#define EXP_cl2_enabletimeservice  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_enabletimeservice", (RTS_UINTPTR)cl2_enabletimeservice, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_enabletimeservice
	#define EXT_CmpCAACanL2cl2_enabletimeservice
	#define GET_CmpCAACanL2cl2_enabletimeservice  ERR_OK
	#define CAL_CmpCAACanL2cl2_enabletimeservice  cl2_enabletimeservice
	#define CHK_CmpCAACanL2cl2_enabletimeservice  TRUE
	#define EXP_CmpCAACanL2cl2_enabletimeservice  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_enabletimeservice", (RTS_UINTPTR)cl2_enabletimeservice, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_enabletimeservice
	#define EXT_cl2_enabletimeservice
	#define GET_cl2_enabletimeservice(fl)  CAL_CMGETAPI( "cl2_enabletimeservice" ) 
	#define CAL_cl2_enabletimeservice  cl2_enabletimeservice
	#define CHK_cl2_enabletimeservice  TRUE
	#define EXP_cl2_enabletimeservice  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_enabletimeservice", (RTS_UINTPTR)cl2_enabletimeservice, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_enabletimeservice  PFCL2_ENABLETIMESERVICE_IEC pfcl2_enabletimeservice;
	#define EXT_cl2_enabletimeservice  extern PFCL2_ENABLETIMESERVICE_IEC pfcl2_enabletimeservice;
	#define GET_cl2_enabletimeservice(fl)  s_pfCMGetAPI2( "cl2_enabletimeservice", (RTS_VOID_FCTPTR *)&pfcl2_enabletimeservice, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_enabletimeservice  pfcl2_enabletimeservice
	#define CHK_cl2_enabletimeservice  (pfcl2_enabletimeservice != NULL)
	#define EXP_cl2_enabletimeservice   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_enabletimeservice", (RTS_UINTPTR)cl2_enabletimeservice, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_isrtrmessage</description>
 */
typedef struct tagcl2_isrtrmessage_struct
{
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_BOOL IsRTRMessage;				/* VAR_OUTPUT */
} cl2_isrtrmessage_struct;

void CDECL CDECL_EXT cl2_isrtrmessage(cl2_isrtrmessage_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_ISRTRMESSAGE_IEC) (cl2_isrtrmessage_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_ISRTRMESSAGE_NOTIMPLEMENTED)
	#define USE_cl2_isrtrmessage
	#define EXT_cl2_isrtrmessage
	#define GET_cl2_isrtrmessage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_isrtrmessage(p0) 
	#define CHK_cl2_isrtrmessage  FALSE
	#define EXP_cl2_isrtrmessage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_isrtrmessage
	#define EXT_cl2_isrtrmessage
	#define GET_cl2_isrtrmessage(fl)  CAL_CMGETAPI( "cl2_isrtrmessage" ) 
	#define CAL_cl2_isrtrmessage  cl2_isrtrmessage
	#define CHK_cl2_isrtrmessage  TRUE
	#define EXP_cl2_isrtrmessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_isrtrmessage", (RTS_UINTPTR)cl2_isrtrmessage, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_isrtrmessage
	#define EXT_cl2_isrtrmessage
	#define GET_cl2_isrtrmessage(fl)  CAL_CMGETAPI( "cl2_isrtrmessage" ) 
	#define CAL_cl2_isrtrmessage  cl2_isrtrmessage
	#define CHK_cl2_isrtrmessage  TRUE
	#define EXP_cl2_isrtrmessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_isrtrmessage", (RTS_UINTPTR)cl2_isrtrmessage, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_isrtrmessage
	#define EXT_CmpCAACanL2cl2_isrtrmessage
	#define GET_CmpCAACanL2cl2_isrtrmessage  ERR_OK
	#define CAL_CmpCAACanL2cl2_isrtrmessage  cl2_isrtrmessage
	#define CHK_CmpCAACanL2cl2_isrtrmessage  TRUE
	#define EXP_CmpCAACanL2cl2_isrtrmessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_isrtrmessage", (RTS_UINTPTR)cl2_isrtrmessage, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_isrtrmessage
	#define EXT_cl2_isrtrmessage
	#define GET_cl2_isrtrmessage(fl)  CAL_CMGETAPI( "cl2_isrtrmessage" ) 
	#define CAL_cl2_isrtrmessage  cl2_isrtrmessage
	#define CHK_cl2_isrtrmessage  TRUE
	#define EXP_cl2_isrtrmessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_isrtrmessage", (RTS_UINTPTR)cl2_isrtrmessage, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_isrtrmessage  PFCL2_ISRTRMESSAGE_IEC pfcl2_isrtrmessage;
	#define EXT_cl2_isrtrmessage  extern PFCL2_ISRTRMESSAGE_IEC pfcl2_isrtrmessage;
	#define GET_cl2_isrtrmessage(fl)  s_pfCMGetAPI2( "cl2_isrtrmessage", (RTS_VOID_FCTPTR *)&pfcl2_isrtrmessage, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_isrtrmessage  pfcl2_isrtrmessage
	#define CHK_cl2_isrtrmessage  (pfcl2_isrtrmessage != NULL)
	#define EXP_cl2_isrtrmessage   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_isrtrmessage", (RTS_UINTPTR)cl2_isrtrmessage, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_cstcycleupdate</description>
 */
typedef struct tagcl2_cstcycleupdate_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE CstCycleUpdate;			/* VAR_OUTPUT */
} cl2_cstcycleupdate_struct;

void CDECL CDECL_EXT cl2_cstcycleupdate(cl2_cstcycleupdate_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_CSTCYCLEUPDATE_IEC) (cl2_cstcycleupdate_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CSTCYCLEUPDATE_NOTIMPLEMENTED)
	#define USE_cl2_cstcycleupdate
	#define EXT_cl2_cstcycleupdate
	#define GET_cl2_cstcycleupdate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_cstcycleupdate(p0) 
	#define CHK_cl2_cstcycleupdate  FALSE
	#define EXP_cl2_cstcycleupdate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_cstcycleupdate
	#define EXT_cl2_cstcycleupdate
	#define GET_cl2_cstcycleupdate(fl)  CAL_CMGETAPI( "cl2_cstcycleupdate" ) 
	#define CAL_cl2_cstcycleupdate  cl2_cstcycleupdate
	#define CHK_cl2_cstcycleupdate  TRUE
	#define EXP_cl2_cstcycleupdate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcycleupdate", (RTS_UINTPTR)cl2_cstcycleupdate, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_cstcycleupdate
	#define EXT_cl2_cstcycleupdate
	#define GET_cl2_cstcycleupdate(fl)  CAL_CMGETAPI( "cl2_cstcycleupdate" ) 
	#define CAL_cl2_cstcycleupdate  cl2_cstcycleupdate
	#define CHK_cl2_cstcycleupdate  TRUE
	#define EXP_cl2_cstcycleupdate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcycleupdate", (RTS_UINTPTR)cl2_cstcycleupdate, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_cstcycleupdate
	#define EXT_CmpCAACanL2cl2_cstcycleupdate
	#define GET_CmpCAACanL2cl2_cstcycleupdate  ERR_OK
	#define CAL_CmpCAACanL2cl2_cstcycleupdate  cl2_cstcycleupdate
	#define CHK_CmpCAACanL2cl2_cstcycleupdate  TRUE
	#define EXP_CmpCAACanL2cl2_cstcycleupdate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcycleupdate", (RTS_UINTPTR)cl2_cstcycleupdate, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_cstcycleupdate
	#define EXT_cl2_cstcycleupdate
	#define GET_cl2_cstcycleupdate(fl)  CAL_CMGETAPI( "cl2_cstcycleupdate" ) 
	#define CAL_cl2_cstcycleupdate  cl2_cstcycleupdate
	#define CHK_cl2_cstcycleupdate  TRUE
	#define EXP_cl2_cstcycleupdate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcycleupdate", (RTS_UINTPTR)cl2_cstcycleupdate, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_cstcycleupdate  PFCL2_CSTCYCLEUPDATE_IEC pfcl2_cstcycleupdate;
	#define EXT_cl2_cstcycleupdate  extern PFCL2_CSTCYCLEUPDATE_IEC pfcl2_cstcycleupdate;
	#define GET_cl2_cstcycleupdate(fl)  s_pfCMGetAPI2( "cl2_cstcycleupdate", (RTS_VOID_FCTPTR *)&pfcl2_cstcycleupdate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_cstcycleupdate  pfcl2_cstcycleupdate
	#define CHK_cl2_cstcycleupdate  (pfcl2_cstcycleupdate != NULL)
	#define EXP_cl2_cstcycleupdate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcycleupdate", (RTS_UINTPTR)cl2_cstcycleupdate, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_createsingleidreceiver</description>
 */
typedef struct tagcl2_createsingleidreceiver_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CL2I_COBID cobId;						/* VAR_INPUT */
	CAA_BOOL xRTR;							/* VAR_INPUT */
	CAA_BOOL x29BitId;					/* VAR_INPUT */
	CAA_BOOL xTransmit;					/* VAR_INPUT */
	CAA_BOOL xAlwaysNewest;				/* VAR_INPUT */
	CAA_ENUM eEvent;						/* VAR_INPUT */
	CAA_BOOL xEnableSyncWindow;		/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE CreateSingleIdReceiver;	/* VAR_OUTPUT */
} cl2_createsingleidreceiver_struct;

void CDECL CDECL_EXT cl2_createsingleidreceiver(cl2_createsingleidreceiver_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_CREATESINGLEIDRECEIVER_IEC) (cl2_createsingleidreceiver_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CREATESINGLEIDRECEIVER_NOTIMPLEMENTED)
	#define USE_cl2_createsingleidreceiver
	#define EXT_cl2_createsingleidreceiver
	#define GET_cl2_createsingleidreceiver(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_createsingleidreceiver(p0) 
	#define CHK_cl2_createsingleidreceiver  FALSE
	#define EXP_cl2_createsingleidreceiver  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_createsingleidreceiver
	#define EXT_cl2_createsingleidreceiver
	#define GET_cl2_createsingleidreceiver(fl)  CAL_CMGETAPI( "cl2_createsingleidreceiver" ) 
	#define CAL_cl2_createsingleidreceiver  cl2_createsingleidreceiver
	#define CHK_cl2_createsingleidreceiver  TRUE
	#define EXP_cl2_createsingleidreceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createsingleidreceiver", (RTS_UINTPTR)cl2_createsingleidreceiver, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_createsingleidreceiver
	#define EXT_cl2_createsingleidreceiver
	#define GET_cl2_createsingleidreceiver(fl)  CAL_CMGETAPI( "cl2_createsingleidreceiver" ) 
	#define CAL_cl2_createsingleidreceiver  cl2_createsingleidreceiver
	#define CHK_cl2_createsingleidreceiver  TRUE
	#define EXP_cl2_createsingleidreceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createsingleidreceiver", (RTS_UINTPTR)cl2_createsingleidreceiver, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_createsingleidreceiver
	#define EXT_CmpCAACanL2cl2_createsingleidreceiver
	#define GET_CmpCAACanL2cl2_createsingleidreceiver  ERR_OK
	#define CAL_CmpCAACanL2cl2_createsingleidreceiver  cl2_createsingleidreceiver
	#define CHK_CmpCAACanL2cl2_createsingleidreceiver  TRUE
	#define EXP_CmpCAACanL2cl2_createsingleidreceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createsingleidreceiver", (RTS_UINTPTR)cl2_createsingleidreceiver, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_createsingleidreceiver
	#define EXT_cl2_createsingleidreceiver
	#define GET_cl2_createsingleidreceiver(fl)  CAL_CMGETAPI( "cl2_createsingleidreceiver" ) 
	#define CAL_cl2_createsingleidreceiver  cl2_createsingleidreceiver
	#define CHK_cl2_createsingleidreceiver  TRUE
	#define EXP_cl2_createsingleidreceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createsingleidreceiver", (RTS_UINTPTR)cl2_createsingleidreceiver, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_createsingleidreceiver  PFCL2_CREATESINGLEIDRECEIVER_IEC pfcl2_createsingleidreceiver;
	#define EXT_cl2_createsingleidreceiver  extern PFCL2_CREATESINGLEIDRECEIVER_IEC pfcl2_createsingleidreceiver;
	#define GET_cl2_createsingleidreceiver(fl)  s_pfCMGetAPI2( "cl2_createsingleidreceiver", (RTS_VOID_FCTPTR *)&pfcl2_createsingleidreceiver, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_createsingleidreceiver  pfcl2_createsingleidreceiver
	#define CHK_cl2_createsingleidreceiver  (pfcl2_createsingleidreceiver != NULL)
	#define EXP_cl2_createsingleidreceiver   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createsingleidreceiver", (RTS_UINTPTR)cl2_createsingleidreceiver, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_gettimestamp</description>
 */
typedef struct tagcl2_gettimestamp_struct
{
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	RTS_IEC_UDINT GetTimeStamp;			/* VAR_OUTPUT */
} cl2_gettimestamp_struct;

void CDECL CDECL_EXT cl2_gettimestamp(cl2_gettimestamp_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_GETTIMESTAMP_IEC) (cl2_gettimestamp_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETTIMESTAMP_NOTIMPLEMENTED)
	#define USE_cl2_gettimestamp
	#define EXT_cl2_gettimestamp
	#define GET_cl2_gettimestamp(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_gettimestamp(p0) 
	#define CHK_cl2_gettimestamp  FALSE
	#define EXP_cl2_gettimestamp  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_gettimestamp
	#define EXT_cl2_gettimestamp
	#define GET_cl2_gettimestamp(fl)  CAL_CMGETAPI( "cl2_gettimestamp" ) 
	#define CAL_cl2_gettimestamp  cl2_gettimestamp
	#define CHK_cl2_gettimestamp  TRUE
	#define EXP_cl2_gettimestamp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettimestamp", (RTS_UINTPTR)cl2_gettimestamp, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_gettimestamp
	#define EXT_cl2_gettimestamp
	#define GET_cl2_gettimestamp(fl)  CAL_CMGETAPI( "cl2_gettimestamp" ) 
	#define CAL_cl2_gettimestamp  cl2_gettimestamp
	#define CHK_cl2_gettimestamp  TRUE
	#define EXP_cl2_gettimestamp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettimestamp", (RTS_UINTPTR)cl2_gettimestamp, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_gettimestamp
	#define EXT_CmpCAACanL2cl2_gettimestamp
	#define GET_CmpCAACanL2cl2_gettimestamp  ERR_OK
	#define CAL_CmpCAACanL2cl2_gettimestamp  cl2_gettimestamp
	#define CHK_CmpCAACanL2cl2_gettimestamp  TRUE
	#define EXP_CmpCAACanL2cl2_gettimestamp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettimestamp", (RTS_UINTPTR)cl2_gettimestamp, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_gettimestamp
	#define EXT_cl2_gettimestamp
	#define GET_cl2_gettimestamp(fl)  CAL_CMGETAPI( "cl2_gettimestamp" ) 
	#define CAL_cl2_gettimestamp  cl2_gettimestamp
	#define CHK_cl2_gettimestamp  TRUE
	#define EXP_cl2_gettimestamp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettimestamp", (RTS_UINTPTR)cl2_gettimestamp, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_gettimestamp  PFCL2_GETTIMESTAMP_IEC pfcl2_gettimestamp;
	#define EXT_cl2_gettimestamp  extern PFCL2_GETTIMESTAMP_IEC pfcl2_gettimestamp;
	#define GET_cl2_gettimestamp(fl)  s_pfCMGetAPI2( "cl2_gettimestamp", (RTS_VOID_FCTPTR *)&pfcl2_gettimestamp, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_gettimestamp  pfcl2_gettimestamp
	#define CHK_cl2_gettimestamp  (pfcl2_gettimestamp != NULL)
	#define EXP_cl2_gettimestamp   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettimestamp", (RTS_UINTPTR)cl2_gettimestamp, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_cstcyclestop</description>
 */
typedef struct tagcl2_cstcyclestop_struct
{
	CAA_HANDLE hCstCycle;				/* VAR_INPUT */
	CAA_ERROR CstCycleStop;				/* VAR_OUTPUT */
} cl2_cstcyclestop_struct;

void CDECL CDECL_EXT cl2_cstcyclestop(cl2_cstcyclestop_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_CSTCYCLESTOP_IEC) (cl2_cstcyclestop_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CSTCYCLESTOP_NOTIMPLEMENTED)
	#define USE_cl2_cstcyclestop
	#define EXT_cl2_cstcyclestop
	#define GET_cl2_cstcyclestop(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_cstcyclestop(p0) 
	#define CHK_cl2_cstcyclestop  FALSE
	#define EXP_cl2_cstcyclestop  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_cstcyclestop
	#define EXT_cl2_cstcyclestop
	#define GET_cl2_cstcyclestop(fl)  CAL_CMGETAPI( "cl2_cstcyclestop" ) 
	#define CAL_cl2_cstcyclestop  cl2_cstcyclestop
	#define CHK_cl2_cstcyclestop  TRUE
	#define EXP_cl2_cstcyclestop  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcyclestop", (RTS_UINTPTR)cl2_cstcyclestop, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_cstcyclestop
	#define EXT_cl2_cstcyclestop
	#define GET_cl2_cstcyclestop(fl)  CAL_CMGETAPI( "cl2_cstcyclestop" ) 
	#define CAL_cl2_cstcyclestop  cl2_cstcyclestop
	#define CHK_cl2_cstcyclestop  TRUE
	#define EXP_cl2_cstcyclestop  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcyclestop", (RTS_UINTPTR)cl2_cstcyclestop, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_cstcyclestop
	#define EXT_CmpCAACanL2cl2_cstcyclestop
	#define GET_CmpCAACanL2cl2_cstcyclestop  ERR_OK
	#define CAL_CmpCAACanL2cl2_cstcyclestop  cl2_cstcyclestop
	#define CHK_CmpCAACanL2cl2_cstcyclestop  TRUE
	#define EXP_CmpCAACanL2cl2_cstcyclestop  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcyclestop", (RTS_UINTPTR)cl2_cstcyclestop, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_cstcyclestop
	#define EXT_cl2_cstcyclestop
	#define GET_cl2_cstcyclestop(fl)  CAL_CMGETAPI( "cl2_cstcyclestop" ) 
	#define CAL_cl2_cstcyclestop  cl2_cstcyclestop
	#define CHK_cl2_cstcyclestop  TRUE
	#define EXP_cl2_cstcyclestop  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcyclestop", (RTS_UINTPTR)cl2_cstcyclestop, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_cstcyclestop  PFCL2_CSTCYCLESTOP_IEC pfcl2_cstcyclestop;
	#define EXT_cl2_cstcyclestop  extern PFCL2_CSTCYCLESTOP_IEC pfcl2_cstcyclestop;
	#define GET_cl2_cstcyclestop(fl)  s_pfCMGetAPI2( "cl2_cstcyclestop", (RTS_VOID_FCTPTR *)&pfcl2_cstcyclestop, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_cstcyclestop  pfcl2_cstcyclestop
	#define CHK_cl2_cstcyclestop  (pfcl2_cstcyclestop != NULL)
	#define EXP_cl2_cstcyclestop   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcyclestop", (RTS_UINTPTR)cl2_cstcyclestop, 1, 0x0, 0x0) 
#endif


/**
 * <description>disablesyncservice</description>
 */
typedef struct tagcl2_disablesyncservice_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR DisableSyncService;		/* VAR_OUTPUT */
} cl2_disablesyncservice_struct;

void CDECL CDECL_EXT cl2_disablesyncservice(cl2_disablesyncservice_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_DISABLESYNCSERVICE_IEC) (cl2_disablesyncservice_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_DISABLESYNCSERVICE_NOTIMPLEMENTED)
	#define USE_cl2_disablesyncservice
	#define EXT_cl2_disablesyncservice
	#define GET_cl2_disablesyncservice(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_disablesyncservice(p0) 
	#define CHK_cl2_disablesyncservice  FALSE
	#define EXP_cl2_disablesyncservice  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_disablesyncservice
	#define EXT_cl2_disablesyncservice
	#define GET_cl2_disablesyncservice(fl)  CAL_CMGETAPI( "cl2_disablesyncservice" ) 
	#define CAL_cl2_disablesyncservice  cl2_disablesyncservice
	#define CHK_cl2_disablesyncservice  TRUE
	#define EXP_cl2_disablesyncservice  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_disablesyncservice", (RTS_UINTPTR)cl2_disablesyncservice, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_disablesyncservice
	#define EXT_cl2_disablesyncservice
	#define GET_cl2_disablesyncservice(fl)  CAL_CMGETAPI( "cl2_disablesyncservice" ) 
	#define CAL_cl2_disablesyncservice  cl2_disablesyncservice
	#define CHK_cl2_disablesyncservice  TRUE
	#define EXP_cl2_disablesyncservice  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_disablesyncservice", (RTS_UINTPTR)cl2_disablesyncservice, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_disablesyncservice
	#define EXT_CmpCAACanL2cl2_disablesyncservice
	#define GET_CmpCAACanL2cl2_disablesyncservice  ERR_OK
	#define CAL_CmpCAACanL2cl2_disablesyncservice  cl2_disablesyncservice
	#define CHK_CmpCAACanL2cl2_disablesyncservice  TRUE
	#define EXP_CmpCAACanL2cl2_disablesyncservice  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_disablesyncservice", (RTS_UINTPTR)cl2_disablesyncservice, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_disablesyncservice
	#define EXT_cl2_disablesyncservice
	#define GET_cl2_disablesyncservice(fl)  CAL_CMGETAPI( "cl2_disablesyncservice" ) 
	#define CAL_cl2_disablesyncservice  cl2_disablesyncservice
	#define CHK_cl2_disablesyncservice  TRUE
	#define EXP_cl2_disablesyncservice  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_disablesyncservice", (RTS_UINTPTR)cl2_disablesyncservice, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_disablesyncservice  PFCL2_DISABLESYNCSERVICE_IEC pfcl2_disablesyncservice;
	#define EXT_cl2_disablesyncservice  extern PFCL2_DISABLESYNCSERVICE_IEC pfcl2_disablesyncservice;
	#define GET_cl2_disablesyncservice(fl)  s_pfCMGetAPI2( "cl2_disablesyncservice", (RTS_VOID_FCTPTR *)&pfcl2_disablesyncservice, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_disablesyncservice  pfcl2_disablesyncservice
	#define CHK_cl2_disablesyncservice  (pfcl2_disablesyncservice != NULL)
	#define EXP_cl2_disablesyncservice   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_disablesyncservice", (RTS_UINTPTR)cl2_disablesyncservice, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_write</description>
 */
typedef struct tagcl2_write_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	RTS_IEC_USINT usiPriority;			/* VAR_INPUT */
	CAA_BOOL xEnableSyncWindow;			/* VAR_INPUT */
	CAA_ERROR Write;					/* VAR_OUTPUT */
} cl2_write_struct;

void CDECL CDECL_EXT cl2_write(cl2_write_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_WRITE_IEC) (cl2_write_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_WRITE_NOTIMPLEMENTED)
	#define USE_cl2_write
	#define EXT_cl2_write
	#define GET_cl2_write(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_write(p0) 
	#define CHK_cl2_write  FALSE
	#define EXP_cl2_write  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_write
	#define EXT_cl2_write
	#define GET_cl2_write(fl)  CAL_CMGETAPI( "cl2_write" ) 
	#define CAL_cl2_write  cl2_write
	#define CHK_cl2_write  TRUE
	#define EXP_cl2_write  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_write", (RTS_UINTPTR)cl2_write, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_write
	#define EXT_cl2_write
	#define GET_cl2_write(fl)  CAL_CMGETAPI( "cl2_write" ) 
	#define CAL_cl2_write  cl2_write
	#define CHK_cl2_write  TRUE
	#define EXP_cl2_write  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_write", (RTS_UINTPTR)cl2_write, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_write
	#define EXT_CmpCAACanL2cl2_write
	#define GET_CmpCAACanL2cl2_write  ERR_OK
	#define CAL_CmpCAACanL2cl2_write  cl2_write
	#define CHK_CmpCAACanL2cl2_write  TRUE
	#define EXP_CmpCAACanL2cl2_write  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_write", (RTS_UINTPTR)cl2_write, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_write
	#define EXT_cl2_write
	#define GET_cl2_write(fl)  CAL_CMGETAPI( "cl2_write" ) 
	#define CAL_cl2_write  cl2_write
	#define CHK_cl2_write  TRUE
	#define EXP_cl2_write  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_write", (RTS_UINTPTR)cl2_write, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_write  PFCL2_WRITE_IEC pfcl2_write;
	#define EXT_cl2_write  extern PFCL2_WRITE_IEC pfcl2_write;
	#define GET_cl2_write(fl)  s_pfCMGetAPI2( "cl2_write", (RTS_VOID_FCTPTR *)&pfcl2_write, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_write  pfcl2_write
	#define CHK_cl2_write  (pfcl2_write != NULL)
	#define EXP_cl2_write   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_write", (RTS_UINTPTR)cl2_write, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_getnetid</description>
 */
typedef struct tagcl2_getnetid_struct
{
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	RTS_IEC_USINT GetNetId;				/* VAR_OUTPUT */
} cl2_getnetid_struct;

void CDECL CDECL_EXT cl2_getnetid(cl2_getnetid_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_GETNETID_IEC) (cl2_getnetid_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETNETID_NOTIMPLEMENTED)
	#define USE_cl2_getnetid
	#define EXT_cl2_getnetid
	#define GET_cl2_getnetid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_getnetid(p0) 
	#define CHK_cl2_getnetid  FALSE
	#define EXP_cl2_getnetid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_getnetid
	#define EXT_cl2_getnetid
	#define GET_cl2_getnetid(fl)  CAL_CMGETAPI( "cl2_getnetid" ) 
	#define CAL_cl2_getnetid  cl2_getnetid
	#define CHK_cl2_getnetid  TRUE
	#define EXP_cl2_getnetid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getnetid", (RTS_UINTPTR)cl2_getnetid, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_getnetid
	#define EXT_cl2_getnetid
	#define GET_cl2_getnetid(fl)  CAL_CMGETAPI( "cl2_getnetid" ) 
	#define CAL_cl2_getnetid  cl2_getnetid
	#define CHK_cl2_getnetid  TRUE
	#define EXP_cl2_getnetid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getnetid", (RTS_UINTPTR)cl2_getnetid, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_getnetid
	#define EXT_CmpCAACanL2cl2_getnetid
	#define GET_CmpCAACanL2cl2_getnetid  ERR_OK
	#define CAL_CmpCAACanL2cl2_getnetid  cl2_getnetid
	#define CHK_CmpCAACanL2cl2_getnetid  TRUE
	#define EXP_CmpCAACanL2cl2_getnetid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getnetid", (RTS_UINTPTR)cl2_getnetid, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_getnetid
	#define EXT_cl2_getnetid
	#define GET_cl2_getnetid(fl)  CAL_CMGETAPI( "cl2_getnetid" ) 
	#define CAL_cl2_getnetid  cl2_getnetid
	#define CHK_cl2_getnetid  TRUE
	#define EXP_cl2_getnetid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getnetid", (RTS_UINTPTR)cl2_getnetid, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_getnetid  PFCL2_GETNETID_IEC pfcl2_getnetid;
	#define EXT_cl2_getnetid  extern PFCL2_GETNETID_IEC pfcl2_getnetid;
	#define GET_cl2_getnetid(fl)  s_pfCMGetAPI2( "cl2_getnetid", (RTS_VOID_FCTPTR *)&pfcl2_getnetid, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_getnetid  pfcl2_getnetid
	#define CHK_cl2_getnetid  (pfcl2_getnetid != NULL)
	#define EXP_cl2_getnetid   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getnetid", (RTS_UINTPTR)cl2_getnetid, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_getsupplierversion</description>
 */
typedef struct tagcl2_getsupplierversion_struct
{
	CAA_BOOL xDummy; /* VAR_INPUT */
	RTS_IEC_WORD GetSupplierVersion;	/* VAR_OUTPUT */
} cl2_getsupplierversion_struct;

void CDECL CDECL_EXT cl2_getsupplierversion(cl2_getsupplierversion_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_GETSUPPLIERVERSION_IEC) (cl2_getsupplierversion_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_cl2_getsupplierversion
	#define EXT_cl2_getsupplierversion
	#define GET_cl2_getsupplierversion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_getsupplierversion(p0) 
	#define CHK_cl2_getsupplierversion  FALSE
	#define EXP_cl2_getsupplierversion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_getsupplierversion
	#define EXT_cl2_getsupplierversion
	#define GET_cl2_getsupplierversion(fl)  CAL_CMGETAPI( "cl2_getsupplierversion" ) 
	#define CAL_cl2_getsupplierversion  cl2_getsupplierversion
	#define CHK_cl2_getsupplierversion  TRUE
	#define EXP_cl2_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getsupplierversion", (RTS_UINTPTR)cl2_getsupplierversion, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_getsupplierversion
	#define EXT_cl2_getsupplierversion
	#define GET_cl2_getsupplierversion(fl)  CAL_CMGETAPI( "cl2_getsupplierversion" ) 
	#define CAL_cl2_getsupplierversion  cl2_getsupplierversion
	#define CHK_cl2_getsupplierversion  TRUE
	#define EXP_cl2_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getsupplierversion", (RTS_UINTPTR)cl2_getsupplierversion, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_getsupplierversion
	#define EXT_CmpCAACanL2cl2_getsupplierversion
	#define GET_CmpCAACanL2cl2_getsupplierversion  ERR_OK
	#define CAL_CmpCAACanL2cl2_getsupplierversion  cl2_getsupplierversion
	#define CHK_CmpCAACanL2cl2_getsupplierversion  TRUE
	#define EXP_CmpCAACanL2cl2_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getsupplierversion", (RTS_UINTPTR)cl2_getsupplierversion, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_getsupplierversion
	#define EXT_cl2_getsupplierversion
	#define GET_cl2_getsupplierversion(fl)  CAL_CMGETAPI( "cl2_getsupplierversion" ) 
	#define CAL_cl2_getsupplierversion  cl2_getsupplierversion
	#define CHK_cl2_getsupplierversion  TRUE
	#define EXP_cl2_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getsupplierversion", (RTS_UINTPTR)cl2_getsupplierversion, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_getsupplierversion  PFCL2_GETSUPPLIERVERSION_IEC pfcl2_getsupplierversion;
	#define EXT_cl2_getsupplierversion  extern PFCL2_GETSUPPLIERVERSION_IEC pfcl2_getsupplierversion;
	#define GET_cl2_getsupplierversion(fl)  s_pfCMGetAPI2( "cl2_getsupplierversion", (RTS_VOID_FCTPTR *)&pfcl2_getsupplierversion, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_getsupplierversion  pfcl2_getsupplierversion
	#define CHK_cl2_getsupplierversion  (pfcl2_getsupplierversion != NULL)
	#define EXP_cl2_getsupplierversion   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getsupplierversion", (RTS_UINTPTR)cl2_getsupplierversion, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_cstcycleclose</description>
 */
typedef struct tagcl2_cstcycleclose_struct
{
	CAA_HANDLE hCstCycle;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE CstCycleClose;			/* VAR_OUTPUT */
} cl2_cstcycleclose_struct;

void CDECL CDECL_EXT cl2_cstcycleclose(cl2_cstcycleclose_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_CSTCYCLECLOSE_IEC) (cl2_cstcycleclose_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CSTCYCLECLOSE_NOTIMPLEMENTED)
	#define USE_cl2_cstcycleclose
	#define EXT_cl2_cstcycleclose
	#define GET_cl2_cstcycleclose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_cstcycleclose(p0) 
	#define CHK_cl2_cstcycleclose  FALSE
	#define EXP_cl2_cstcycleclose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_cstcycleclose
	#define EXT_cl2_cstcycleclose
	#define GET_cl2_cstcycleclose(fl)  CAL_CMGETAPI( "cl2_cstcycleclose" ) 
	#define CAL_cl2_cstcycleclose  cl2_cstcycleclose
	#define CHK_cl2_cstcycleclose  TRUE
	#define EXP_cl2_cstcycleclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcycleclose", (RTS_UINTPTR)cl2_cstcycleclose, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_cstcycleclose
	#define EXT_cl2_cstcycleclose
	#define GET_cl2_cstcycleclose(fl)  CAL_CMGETAPI( "cl2_cstcycleclose" ) 
	#define CAL_cl2_cstcycleclose  cl2_cstcycleclose
	#define CHK_cl2_cstcycleclose  TRUE
	#define EXP_cl2_cstcycleclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcycleclose", (RTS_UINTPTR)cl2_cstcycleclose, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_cstcycleclose
	#define EXT_CmpCAACanL2cl2_cstcycleclose
	#define GET_CmpCAACanL2cl2_cstcycleclose  ERR_OK
	#define CAL_CmpCAACanL2cl2_cstcycleclose  cl2_cstcycleclose
	#define CHK_CmpCAACanL2cl2_cstcycleclose  TRUE
	#define EXP_CmpCAACanL2cl2_cstcycleclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcycleclose", (RTS_UINTPTR)cl2_cstcycleclose, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_cstcycleclose
	#define EXT_cl2_cstcycleclose
	#define GET_cl2_cstcycleclose(fl)  CAL_CMGETAPI( "cl2_cstcycleclose" ) 
	#define CAL_cl2_cstcycleclose  cl2_cstcycleclose
	#define CHK_cl2_cstcycleclose  TRUE
	#define EXP_cl2_cstcycleclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcycleclose", (RTS_UINTPTR)cl2_cstcycleclose, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_cstcycleclose  PFCL2_CSTCYCLECLOSE_IEC pfcl2_cstcycleclose;
	#define EXT_cl2_cstcycleclose  extern PFCL2_CSTCYCLECLOSE_IEC pfcl2_cstcycleclose;
	#define GET_cl2_cstcycleclose(fl)  s_pfCMGetAPI2( "cl2_cstcycleclose", (RTS_VOID_FCTPTR *)&pfcl2_cstcycleclose, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_cstcycleclose  pfcl2_cstcycleclose
	#define CHK_cl2_cstcycleclose  (pfcl2_cstcycleclose != NULL)
	#define EXP_cl2_cstcycleclose   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcycleclose", (RTS_UINTPTR)cl2_cstcycleclose, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_createmaskreceiver</description>
 */
typedef struct tagcl2_createmaskreceiver_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CL2I_COBID cobIdValue;				/* VAR_INPUT */
	CL2I_COBID cobIdMask;				/* VAR_INPUT */
	CAA_BOOL xRTRValue;					/* VAR_INPUT */
	CAA_BOOL xRTRMask;					/* VAR_INPUT */
	CAA_BOOL x29BitIdValue;				/* VAR_INPUT */
	CAA_BOOL x29BitIdMask;				/* VAR_INPUT */
	CAA_BOOL xTransmitValue;			/* VAR_INPUT */
	CAA_BOOL xTransmitMask;				/* VAR_INPUT */
	CAA_BOOL xAlwaysNewest;				/* VAR_INPUT */
	CAA_ENUM eEvent;						/* VAR_INPUT */
	CAA_BOOL xEnableSyncWindow;		/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE CreateMaskReceiver;	/* VAR_OUTPUT */
} cl2_createmaskreceiver_struct;

void CDECL CDECL_EXT cl2_createmaskreceiver(cl2_createmaskreceiver_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_CREATEMASKRECEIVER_IEC) (cl2_createmaskreceiver_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CREATEMASKRECEIVER_NOTIMPLEMENTED)
	#define USE_cl2_createmaskreceiver
	#define EXT_cl2_createmaskreceiver
	#define GET_cl2_createmaskreceiver(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_createmaskreceiver(p0) 
	#define CHK_cl2_createmaskreceiver  FALSE
	#define EXP_cl2_createmaskreceiver  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_createmaskreceiver
	#define EXT_cl2_createmaskreceiver
	#define GET_cl2_createmaskreceiver(fl)  CAL_CMGETAPI( "cl2_createmaskreceiver" ) 
	#define CAL_cl2_createmaskreceiver  cl2_createmaskreceiver
	#define CHK_cl2_createmaskreceiver  TRUE
	#define EXP_cl2_createmaskreceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createmaskreceiver", (RTS_UINTPTR)cl2_createmaskreceiver, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_createmaskreceiver
	#define EXT_cl2_createmaskreceiver
	#define GET_cl2_createmaskreceiver(fl)  CAL_CMGETAPI( "cl2_createmaskreceiver" ) 
	#define CAL_cl2_createmaskreceiver  cl2_createmaskreceiver
	#define CHK_cl2_createmaskreceiver  TRUE
	#define EXP_cl2_createmaskreceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createmaskreceiver", (RTS_UINTPTR)cl2_createmaskreceiver, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_createmaskreceiver
	#define EXT_CmpCAACanL2cl2_createmaskreceiver
	#define GET_CmpCAACanL2cl2_createmaskreceiver  ERR_OK
	#define CAL_CmpCAACanL2cl2_createmaskreceiver  cl2_createmaskreceiver
	#define CHK_CmpCAACanL2cl2_createmaskreceiver  TRUE
	#define EXP_CmpCAACanL2cl2_createmaskreceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createmaskreceiver", (RTS_UINTPTR)cl2_createmaskreceiver, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_createmaskreceiver
	#define EXT_cl2_createmaskreceiver
	#define GET_cl2_createmaskreceiver(fl)  CAL_CMGETAPI( "cl2_createmaskreceiver" ) 
	#define CAL_cl2_createmaskreceiver  cl2_createmaskreceiver
	#define CHK_cl2_createmaskreceiver  TRUE
	#define EXP_cl2_createmaskreceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createmaskreceiver", (RTS_UINTPTR)cl2_createmaskreceiver, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_createmaskreceiver  PFCL2_CREATEMASKRECEIVER_IEC pfcl2_createmaskreceiver;
	#define EXT_cl2_createmaskreceiver  extern PFCL2_CREATEMASKRECEIVER_IEC pfcl2_createmaskreceiver;
	#define GET_cl2_createmaskreceiver(fl)  s_pfCMGetAPI2( "cl2_createmaskreceiver", (RTS_VOID_FCTPTR *)&pfcl2_createmaskreceiver, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_createmaskreceiver  pfcl2_createmaskreceiver
	#define CHK_cl2_createmaskreceiver  (pfcl2_createmaskreceiver != NULL)
	#define EXP_cl2_createmaskreceiver   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createmaskreceiver", (RTS_UINTPTR)cl2_createmaskreceiver, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_createarrayreceiver</description>
 */
typedef struct tagcl2_createarrayreceiver_struct
{
	CAA_HANDLE hDriver;						/* VAR_INPUT */
	CL2I_ARRAYRECV_ENTRY* paSortedCOBIDs;	/* VAR_INPUT */
	CAA_COUNT ctCOBIDs;						/* VAR_INPUT */
	CAA_ENUM eEvent;						/* VAR_INPUT */
	CAA_BOOL xEnableSyncWindow;				/* VAR_INPUT */
	CAA_ERROR* peError;						/* VAR_INPUT */
	CAA_HANDLE CreateArrayReceiver;			/* VAR_OUTPUT */
} cl2_createarrayreceiver_struct;

void CDECL CDECL_EXT cl2_createarrayreceiver(cl2_createarrayreceiver_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_CREATEARRAYRECEIVER_IEC) (cl2_createarrayreceiver_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CREATEARRAYRECEIVER_NOTIMPLEMENTED)
	#define USE_cl2_createarrayreceiver
	#define EXT_cl2_createarrayreceiver
	#define GET_cl2_createarrayreceiver(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_createarrayreceiver(p0) 
	#define CHK_cl2_createarrayreceiver  FALSE
	#define EXP_cl2_createarrayreceiver  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_createarrayreceiver
	#define EXT_cl2_createarrayreceiver
	#define GET_cl2_createarrayreceiver(fl)  CAL_CMGETAPI( "cl2_createarrayreceiver" ) 
	#define CAL_cl2_createarrayreceiver  cl2_createarrayreceiver
	#define CHK_cl2_createarrayreceiver  TRUE
	#define EXP_cl2_createarrayreceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createarrayreceiver", (RTS_UINTPTR)cl2_createarrayreceiver, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_createarrayreceiver
	#define EXT_cl2_createarrayreceiver
	#define GET_cl2_createarrayreceiver(fl)  CAL_CMGETAPI( "cl2_createarrayreceiver" ) 
	#define CAL_cl2_createarrayreceiver  cl2_createarrayreceiver
	#define CHK_cl2_createarrayreceiver  TRUE
	#define EXP_cl2_createarrayreceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createarrayreceiver", (RTS_UINTPTR)cl2_createarrayreceiver, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_createarrayreceiver
	#define EXT_CmpCAACanL2cl2_createarrayreceiver
	#define GET_CmpCAACanL2cl2_createarrayreceiver  ERR_OK
	#define CAL_CmpCAACanL2cl2_createarrayreceiver  cl2_createarrayreceiver
	#define CHK_CmpCAACanL2cl2_createarrayreceiver  TRUE
	#define EXP_CmpCAACanL2cl2_createarrayreceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createarrayreceiver", (RTS_UINTPTR)cl2_createarrayreceiver, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_createarrayreceiver
	#define EXT_cl2_createarrayreceiver
	#define GET_cl2_createarrayreceiver(fl)  CAL_CMGETAPI( "cl2_createarrayreceiver" ) 
	#define CAL_cl2_createarrayreceiver  cl2_createarrayreceiver
	#define CHK_cl2_createarrayreceiver  TRUE
	#define EXP_cl2_createarrayreceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createarrayreceiver", (RTS_UINTPTR)cl2_createarrayreceiver, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_createarrayreceiver  PFCL2_CREATEARRAYRECEIVER_IEC pfcl2_createarrayreceiver;
	#define EXT_cl2_createarrayreceiver  extern PFCL2_CREATEARRAYRECEIVER_IEC pfcl2_createarrayreceiver;
	#define GET_cl2_createarrayreceiver(fl)  s_pfCMGetAPI2( "cl2_createarrayreceiver", (RTS_VOID_FCTPTR *)&pfcl2_createarrayreceiver, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_createarrayreceiver  pfcl2_createarrayreceiver
	#define CHK_cl2_createarrayreceiver  (pfcl2_createarrayreceiver != NULL)
	#define EXP_cl2_createarrayreceiver   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createarrayreceiver", (RTS_UINTPTR)cl2_createarrayreceiver, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_freemessage</description>
 */
typedef struct tagcl2_freemessage_struct
{
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	CAA_ERROR FreeMessage;				/* VAR_OUTPUT */
} cl2_freemessage_struct;

void CDECL CDECL_EXT cl2_freemessage(cl2_freemessage_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_FREEMESSAGE_IEC) (cl2_freemessage_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_FREEMESSAGE_NOTIMPLEMENTED)
	#define USE_cl2_freemessage
	#define EXT_cl2_freemessage
	#define GET_cl2_freemessage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_freemessage(p0) 
	#define CHK_cl2_freemessage  FALSE
	#define EXP_cl2_freemessage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_freemessage
	#define EXT_cl2_freemessage
	#define GET_cl2_freemessage(fl)  CAL_CMGETAPI( "cl2_freemessage" ) 
	#define CAL_cl2_freemessage  cl2_freemessage
	#define CHK_cl2_freemessage  TRUE
	#define EXP_cl2_freemessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_freemessage", (RTS_UINTPTR)cl2_freemessage, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_freemessage
	#define EXT_cl2_freemessage
	#define GET_cl2_freemessage(fl)  CAL_CMGETAPI( "cl2_freemessage" ) 
	#define CAL_cl2_freemessage  cl2_freemessage
	#define CHK_cl2_freemessage  TRUE
	#define EXP_cl2_freemessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_freemessage", (RTS_UINTPTR)cl2_freemessage, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_freemessage
	#define EXT_CmpCAACanL2cl2_freemessage
	#define GET_CmpCAACanL2cl2_freemessage  ERR_OK
	#define CAL_CmpCAACanL2cl2_freemessage  cl2_freemessage
	#define CHK_CmpCAACanL2cl2_freemessage  TRUE
	#define EXP_CmpCAACanL2cl2_freemessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_freemessage", (RTS_UINTPTR)cl2_freemessage, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_freemessage
	#define EXT_cl2_freemessage
	#define GET_cl2_freemessage(fl)  CAL_CMGETAPI( "cl2_freemessage" ) 
	#define CAL_cl2_freemessage  cl2_freemessage
	#define CHK_cl2_freemessage  TRUE
	#define EXP_cl2_freemessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_freemessage", (RTS_UINTPTR)cl2_freemessage, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_freemessage  PFCL2_FREEMESSAGE_IEC pfcl2_freemessage;
	#define EXT_cl2_freemessage  extern PFCL2_FREEMESSAGE_IEC pfcl2_freemessage;
	#define GET_cl2_freemessage(fl)  s_pfCMGetAPI2( "cl2_freemessage", (RTS_VOID_FCTPTR *)&pfcl2_freemessage, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_freemessage  pfcl2_freemessage
	#define CHK_cl2_freemessage  (pfcl2_freemessage != NULL)
	#define EXP_cl2_freemessage   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_freemessage", (RTS_UINTPTR)cl2_freemessage, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_getmessageid</description>
 */
typedef struct tagcl2_getmessageid_struct
{
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	CAA_ERROR* peError;				/* VAR_INPUT */
	CL2I_COBID GetMessageId;		/* VAR_OUTPUT */
} cl2_getmessageid_struct;

void CDECL CDECL_EXT cl2_getmessageid(cl2_getmessageid_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_GETMESSAGEID_IEC) (cl2_getmessageid_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETMESSAGEID_NOTIMPLEMENTED)
	#define USE_cl2_getmessageid
	#define EXT_cl2_getmessageid
	#define GET_cl2_getmessageid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_getmessageid(p0) 
	#define CHK_cl2_getmessageid  FALSE
	#define EXP_cl2_getmessageid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_getmessageid
	#define EXT_cl2_getmessageid
	#define GET_cl2_getmessageid(fl)  CAL_CMGETAPI( "cl2_getmessageid" ) 
	#define CAL_cl2_getmessageid  cl2_getmessageid
	#define CHK_cl2_getmessageid  TRUE
	#define EXP_cl2_getmessageid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getmessageid", (RTS_UINTPTR)cl2_getmessageid, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_getmessageid
	#define EXT_cl2_getmessageid
	#define GET_cl2_getmessageid(fl)  CAL_CMGETAPI( "cl2_getmessageid" ) 
	#define CAL_cl2_getmessageid  cl2_getmessageid
	#define CHK_cl2_getmessageid  TRUE
	#define EXP_cl2_getmessageid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getmessageid", (RTS_UINTPTR)cl2_getmessageid, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_getmessageid
	#define EXT_CmpCAACanL2cl2_getmessageid
	#define GET_CmpCAACanL2cl2_getmessageid  ERR_OK
	#define CAL_CmpCAACanL2cl2_getmessageid  cl2_getmessageid
	#define CHK_CmpCAACanL2cl2_getmessageid  TRUE
	#define EXP_CmpCAACanL2cl2_getmessageid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getmessageid", (RTS_UINTPTR)cl2_getmessageid, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_getmessageid
	#define EXT_cl2_getmessageid
	#define GET_cl2_getmessageid(fl)  CAL_CMGETAPI( "cl2_getmessageid" ) 
	#define CAL_cl2_getmessageid  cl2_getmessageid
	#define CHK_cl2_getmessageid  TRUE
	#define EXP_cl2_getmessageid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getmessageid", (RTS_UINTPTR)cl2_getmessageid, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_getmessageid  PFCL2_GETMESSAGEID_IEC pfcl2_getmessageid;
	#define EXT_cl2_getmessageid  extern PFCL2_GETMESSAGEID_IEC pfcl2_getmessageid;
	#define GET_cl2_getmessageid(fl)  s_pfCMGetAPI2( "cl2_getmessageid", (RTS_VOID_FCTPTR *)&pfcl2_getmessageid, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_getmessageid  pfcl2_getmessageid
	#define CHK_cl2_getmessageid  (pfcl2_getmessageid != NULL)
	#define EXP_cl2_getmessageid   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getmessageid", (RTS_UINTPTR)cl2_getmessageid, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_lostmessages</description>
 */
typedef struct tagcl2_lostmessages_struct
{
	CAA_HANDLE hReceiverId;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_COUNT LostMessages;			/* VAR_OUTPUT */
} cl2_lostmessages_struct;

void CDECL CDECL_EXT cl2_lostmessages(cl2_lostmessages_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_LOSTMESSAGES_IEC) (cl2_lostmessages_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_LOSTMESSAGES_NOTIMPLEMENTED)
	#define USE_cl2_lostmessages
	#define EXT_cl2_lostmessages
	#define GET_cl2_lostmessages(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_lostmessages(p0) 
	#define CHK_cl2_lostmessages  FALSE
	#define EXP_cl2_lostmessages  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_lostmessages
	#define EXT_cl2_lostmessages
	#define GET_cl2_lostmessages(fl)  CAL_CMGETAPI( "cl2_lostmessages" ) 
	#define CAL_cl2_lostmessages  cl2_lostmessages
	#define CHK_cl2_lostmessages  TRUE
	#define EXP_cl2_lostmessages  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_lostmessages", (RTS_UINTPTR)cl2_lostmessages, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_lostmessages
	#define EXT_cl2_lostmessages
	#define GET_cl2_lostmessages(fl)  CAL_CMGETAPI( "cl2_lostmessages" ) 
	#define CAL_cl2_lostmessages  cl2_lostmessages
	#define CHK_cl2_lostmessages  TRUE
	#define EXP_cl2_lostmessages  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_lostmessages", (RTS_UINTPTR)cl2_lostmessages, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_lostmessages
	#define EXT_CmpCAACanL2cl2_lostmessages
	#define GET_CmpCAACanL2cl2_lostmessages  ERR_OK
	#define CAL_CmpCAACanL2cl2_lostmessages  cl2_lostmessages
	#define CHK_CmpCAACanL2cl2_lostmessages  TRUE
	#define EXP_CmpCAACanL2cl2_lostmessages  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_lostmessages", (RTS_UINTPTR)cl2_lostmessages, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_lostmessages
	#define EXT_cl2_lostmessages
	#define GET_cl2_lostmessages(fl)  CAL_CMGETAPI( "cl2_lostmessages" ) 
	#define CAL_cl2_lostmessages  cl2_lostmessages
	#define CHK_cl2_lostmessages  TRUE
	#define EXP_cl2_lostmessages  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_lostmessages", (RTS_UINTPTR)cl2_lostmessages, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_lostmessages  PFCL2_LOSTMESSAGES_IEC pfcl2_lostmessages;
	#define EXT_cl2_lostmessages  extern PFCL2_LOSTMESSAGES_IEC pfcl2_lostmessages;
	#define GET_cl2_lostmessages(fl)  s_pfCMGetAPI2( "cl2_lostmessages", (RTS_VOID_FCTPTR *)&pfcl2_lostmessages, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_lostmessages  pfcl2_lostmessages
	#define CHK_cl2_lostmessages  (pfcl2_lostmessages != NULL)
	#define EXP_cl2_lostmessages   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_lostmessages", (RTS_UINTPTR)cl2_lostmessages, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_getbusload</description>
 */
typedef struct tagcl2_getbusload_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	unsigned short GetBusload;			/* VAR_OUTPUT */
} cl2_getbusload_struct;

void CDECL CDECL_EXT cl2_getbusload(cl2_getbusload_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_GETBUSLOAD_IEC) (cl2_getbusload_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETBUSLOAD_NOTIMPLEMENTED)
	#define USE_cl2_getbusload
	#define EXT_cl2_getbusload
	#define GET_cl2_getbusload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_getbusload(p0) 
	#define CHK_cl2_getbusload  FALSE
	#define EXP_cl2_getbusload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_getbusload
	#define EXT_cl2_getbusload
	#define GET_cl2_getbusload(fl)  CAL_CMGETAPI( "cl2_getbusload" ) 
	#define CAL_cl2_getbusload  cl2_getbusload
	#define CHK_cl2_getbusload  TRUE
	#define EXP_cl2_getbusload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getbusload", (RTS_UINTPTR)cl2_getbusload, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_getbusload
	#define EXT_cl2_getbusload
	#define GET_cl2_getbusload(fl)  CAL_CMGETAPI( "cl2_getbusload" ) 
	#define CAL_cl2_getbusload  cl2_getbusload
	#define CHK_cl2_getbusload  TRUE
	#define EXP_cl2_getbusload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getbusload", (RTS_UINTPTR)cl2_getbusload, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_getbusload
	#define EXT_CmpCAACanL2cl2_getbusload
	#define GET_CmpCAACanL2cl2_getbusload  ERR_OK
	#define CAL_CmpCAACanL2cl2_getbusload  cl2_getbusload
	#define CHK_CmpCAACanL2cl2_getbusload  TRUE
	#define EXP_CmpCAACanL2cl2_getbusload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getbusload", (RTS_UINTPTR)cl2_getbusload, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_getbusload
	#define EXT_cl2_getbusload
	#define GET_cl2_getbusload(fl)  CAL_CMGETAPI( "cl2_getbusload" ) 
	#define CAL_cl2_getbusload  cl2_getbusload
	#define CHK_cl2_getbusload  TRUE
	#define EXP_cl2_getbusload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getbusload", (RTS_UINTPTR)cl2_getbusload, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_getbusload  PFCL2_GETBUSLOAD_IEC pfcl2_getbusload;
	#define EXT_cl2_getbusload  extern PFCL2_GETBUSLOAD_IEC pfcl2_getbusload;
	#define GET_cl2_getbusload(fl)  s_pfCMGetAPI2( "cl2_getbusload", (RTS_VOID_FCTPTR *)&pfcl2_getbusload, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_getbusload  pfcl2_getbusload
	#define CHK_cl2_getbusload  (pfcl2_getbusload != NULL)
	#define EXP_cl2_getbusload   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getbusload", (RTS_UINTPTR)cl2_getbusload, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_getmessagedatapointer</description>
 */
typedef struct tagcl2_getmessagedatapointer_struct
{
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CL2I_DATA* GetMessageDataPointer;		/* VAR_OUTPUT */
} cl2_getmessagedatapointer_struct;

void CDECL CDECL_EXT cl2_getmessagedatapointer(cl2_getmessagedatapointer_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_GETMESSAGEDATAPOINTER_IEC) (cl2_getmessagedatapointer_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETMESSAGEDATAPOINTER_NOTIMPLEMENTED)
	#define USE_cl2_getmessagedatapointer
	#define EXT_cl2_getmessagedatapointer
	#define GET_cl2_getmessagedatapointer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_getmessagedatapointer(p0) 
	#define CHK_cl2_getmessagedatapointer  FALSE
	#define EXP_cl2_getmessagedatapointer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_getmessagedatapointer
	#define EXT_cl2_getmessagedatapointer
	#define GET_cl2_getmessagedatapointer(fl)  CAL_CMGETAPI( "cl2_getmessagedatapointer" ) 
	#define CAL_cl2_getmessagedatapointer  cl2_getmessagedatapointer
	#define CHK_cl2_getmessagedatapointer  TRUE
	#define EXP_cl2_getmessagedatapointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getmessagedatapointer", (RTS_UINTPTR)cl2_getmessagedatapointer, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_getmessagedatapointer
	#define EXT_cl2_getmessagedatapointer
	#define GET_cl2_getmessagedatapointer(fl)  CAL_CMGETAPI( "cl2_getmessagedatapointer" ) 
	#define CAL_cl2_getmessagedatapointer  cl2_getmessagedatapointer
	#define CHK_cl2_getmessagedatapointer  TRUE
	#define EXP_cl2_getmessagedatapointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getmessagedatapointer", (RTS_UINTPTR)cl2_getmessagedatapointer, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_getmessagedatapointer
	#define EXT_CmpCAACanL2cl2_getmessagedatapointer
	#define GET_CmpCAACanL2cl2_getmessagedatapointer  ERR_OK
	#define CAL_CmpCAACanL2cl2_getmessagedatapointer  cl2_getmessagedatapointer
	#define CHK_CmpCAACanL2cl2_getmessagedatapointer  TRUE
	#define EXP_CmpCAACanL2cl2_getmessagedatapointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getmessagedatapointer", (RTS_UINTPTR)cl2_getmessagedatapointer, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_getmessagedatapointer
	#define EXT_cl2_getmessagedatapointer
	#define GET_cl2_getmessagedatapointer(fl)  CAL_CMGETAPI( "cl2_getmessagedatapointer" ) 
	#define CAL_cl2_getmessagedatapointer  cl2_getmessagedatapointer
	#define CHK_cl2_getmessagedatapointer  TRUE
	#define EXP_cl2_getmessagedatapointer  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getmessagedatapointer", (RTS_UINTPTR)cl2_getmessagedatapointer, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_getmessagedatapointer  PFCL2_GETMESSAGEDATAPOINTER_IEC pfcl2_getmessagedatapointer;
	#define EXT_cl2_getmessagedatapointer  extern PFCL2_GETMESSAGEDATAPOINTER_IEC pfcl2_getmessagedatapointer;
	#define GET_cl2_getmessagedatapointer(fl)  s_pfCMGetAPI2( "cl2_getmessagedatapointer", (RTS_VOID_FCTPTR *)&pfcl2_getmessagedatapointer, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_getmessagedatapointer  pfcl2_getmessagedatapointer
	#define CHK_cl2_getmessagedatapointer  (pfcl2_getmessagedatapointer != NULL)
	#define EXP_cl2_getmessagedatapointer   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getmessagedatapointer", (RTS_UINTPTR)cl2_getmessagedatapointer, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_unregisteridarea</description>
 */
typedef struct tagcl2_unregisteridarea_struct
{
	CAA_HANDLE hReceiverId;				/* VAR_INPUT */
	CL2I_COBID cobIdStart;				/* VAR_INPUT */
	CL2I_COBID cobIdEnd;					/* VAR_INPUT */
	CAA_BOOL xRTRValue;					/* VAR_INPUT */
	CAA_BOOL xRTRMask;					/* VAR_INPUT */
	CAA_BOOL x29BitIdValue;				/* VAR_INPUT */
	CAA_BOOL x29BitIdMask;				/* VAR_INPUT */
	CAA_BOOL xTransmitValue;			/* VAR_INPUT */
	CAA_BOOL xTransmitMask;				/* VAR_INPUT */
	CAA_ERROR UnregisterIdArea;		/* VAR_OUTPUT */
} cl2_unregisteridarea_struct;

void CDECL CDECL_EXT cl2_unregisteridarea(cl2_unregisteridarea_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_UNREGISTERIDAREA_IEC) (cl2_unregisteridarea_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_UNREGISTERIDAREA_NOTIMPLEMENTED)
	#define USE_cl2_unregisteridarea
	#define EXT_cl2_unregisteridarea
	#define GET_cl2_unregisteridarea(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_unregisteridarea(p0) 
	#define CHK_cl2_unregisteridarea  FALSE
	#define EXP_cl2_unregisteridarea  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_unregisteridarea
	#define EXT_cl2_unregisteridarea
	#define GET_cl2_unregisteridarea(fl)  CAL_CMGETAPI( "cl2_unregisteridarea" ) 
	#define CAL_cl2_unregisteridarea  cl2_unregisteridarea
	#define CHK_cl2_unregisteridarea  TRUE
	#define EXP_cl2_unregisteridarea  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_unregisteridarea", (RTS_UINTPTR)cl2_unregisteridarea, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_unregisteridarea
	#define EXT_cl2_unregisteridarea
	#define GET_cl2_unregisteridarea(fl)  CAL_CMGETAPI( "cl2_unregisteridarea" ) 
	#define CAL_cl2_unregisteridarea  cl2_unregisteridarea
	#define CHK_cl2_unregisteridarea  TRUE
	#define EXP_cl2_unregisteridarea  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_unregisteridarea", (RTS_UINTPTR)cl2_unregisteridarea, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_unregisteridarea
	#define EXT_CmpCAACanL2cl2_unregisteridarea
	#define GET_CmpCAACanL2cl2_unregisteridarea  ERR_OK
	#define CAL_CmpCAACanL2cl2_unregisteridarea  cl2_unregisteridarea
	#define CHK_CmpCAACanL2cl2_unregisteridarea  TRUE
	#define EXP_CmpCAACanL2cl2_unregisteridarea  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_unregisteridarea", (RTS_UINTPTR)cl2_unregisteridarea, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_unregisteridarea
	#define EXT_cl2_unregisteridarea
	#define GET_cl2_unregisteridarea(fl)  CAL_CMGETAPI( "cl2_unregisteridarea" ) 
	#define CAL_cl2_unregisteridarea  cl2_unregisteridarea
	#define CHK_cl2_unregisteridarea  TRUE
	#define EXP_cl2_unregisteridarea  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_unregisteridarea", (RTS_UINTPTR)cl2_unregisteridarea, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_unregisteridarea  PFCL2_UNREGISTERIDAREA_IEC pfcl2_unregisteridarea;
	#define EXT_cl2_unregisteridarea  extern PFCL2_UNREGISTERIDAREA_IEC pfcl2_unregisteridarea;
	#define GET_cl2_unregisteridarea(fl)  s_pfCMGetAPI2( "cl2_unregisteridarea", (RTS_VOID_FCTPTR *)&pfcl2_unregisteridarea, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_unregisteridarea  pfcl2_unregisteridarea
	#define CHK_cl2_unregisteridarea  (pfcl2_unregisteridarea != NULL)
	#define EXP_cl2_unregisteridarea   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_unregisteridarea", (RTS_UINTPTR)cl2_unregisteridarea, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_gettransmitcounter</description>
 */
typedef struct tagcl2_gettransmitcounter_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_COUNT GetTransmitCounter;			/* VAR_OUTPUT */
} cl2_gettransmitcounter_struct;

void CDECL CDECL_EXT cl2_gettransmitcounter(cl2_gettransmitcounter_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_GETTRANSMITCOUNTER_IEC) (cl2_gettransmitcounter_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETTRANSMITCOUNTER_NOTIMPLEMENTED)
	#define USE_cl2_gettransmitcounter
	#define EXT_cl2_gettransmitcounter
	#define GET_cl2_gettransmitcounter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_gettransmitcounter(p0) 
	#define CHK_cl2_gettransmitcounter  FALSE
	#define EXP_cl2_gettransmitcounter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_gettransmitcounter
	#define EXT_cl2_gettransmitcounter
	#define GET_cl2_gettransmitcounter(fl)  CAL_CMGETAPI( "cl2_gettransmitcounter" ) 
	#define CAL_cl2_gettransmitcounter  cl2_gettransmitcounter
	#define CHK_cl2_gettransmitcounter  TRUE
	#define EXP_cl2_gettransmitcounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettransmitcounter", (RTS_UINTPTR)cl2_gettransmitcounter, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_gettransmitcounter
	#define EXT_cl2_gettransmitcounter
	#define GET_cl2_gettransmitcounter(fl)  CAL_CMGETAPI( "cl2_gettransmitcounter" ) 
	#define CAL_cl2_gettransmitcounter  cl2_gettransmitcounter
	#define CHK_cl2_gettransmitcounter  TRUE
	#define EXP_cl2_gettransmitcounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettransmitcounter", (RTS_UINTPTR)cl2_gettransmitcounter, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_gettransmitcounter
	#define EXT_CmpCAACanL2cl2_gettransmitcounter
	#define GET_CmpCAACanL2cl2_gettransmitcounter  ERR_OK
	#define CAL_CmpCAACanL2cl2_gettransmitcounter  cl2_gettransmitcounter
	#define CHK_CmpCAACanL2cl2_gettransmitcounter  TRUE
	#define EXP_CmpCAACanL2cl2_gettransmitcounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettransmitcounter", (RTS_UINTPTR)cl2_gettransmitcounter, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_gettransmitcounter
	#define EXT_cl2_gettransmitcounter
	#define GET_cl2_gettransmitcounter(fl)  CAL_CMGETAPI( "cl2_gettransmitcounter" ) 
	#define CAL_cl2_gettransmitcounter  cl2_gettransmitcounter
	#define CHK_cl2_gettransmitcounter  TRUE
	#define EXP_cl2_gettransmitcounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettransmitcounter", (RTS_UINTPTR)cl2_gettransmitcounter, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_gettransmitcounter  PFCL2_GETTRANSMITCOUNTER_IEC pfcl2_gettransmitcounter;
	#define EXT_cl2_gettransmitcounter  extern PFCL2_GETTRANSMITCOUNTER_IEC pfcl2_gettransmitcounter;
	#define GET_cl2_gettransmitcounter(fl)  s_pfCMGetAPI2( "cl2_gettransmitcounter", (RTS_VOID_FCTPTR *)&pfcl2_gettransmitcounter, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_gettransmitcounter  pfcl2_gettransmitcounter
	#define CHK_cl2_gettransmitcounter  (pfcl2_gettransmitcounter != NULL)
	#define EXP_cl2_gettransmitcounter   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettransmitcounter", (RTS_UINTPTR)cl2_gettransmitcounter, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_createidareareceiver</description>
 */
typedef struct tagcl2_createidareareceiver_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_BOOL xAlwaysNewest;				/* VAR_INPUT */
	CAA_ENUM eEvent;					/* VAR_INPUT */
	CAA_BOOL xEnableSyncWindow;			/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE CreateIdAreaReceiver;	/* VAR_OUTPUT */
} cl2_createidareareceiver_struct;

void CDECL CDECL_EXT cl2_createidareareceiver(cl2_createidareareceiver_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_CREATEIDAREARECEIVER_IEC) (cl2_createidareareceiver_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CREATEIDAREARECEIVER_NOTIMPLEMENTED)
	#define USE_cl2_createidareareceiver
	#define EXT_cl2_createidareareceiver
	#define GET_cl2_createidareareceiver(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_createidareareceiver(p0) 
	#define CHK_cl2_createidareareceiver  FALSE
	#define EXP_cl2_createidareareceiver  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_createidareareceiver
	#define EXT_cl2_createidareareceiver
	#define GET_cl2_createidareareceiver(fl)  CAL_CMGETAPI( "cl2_createidareareceiver" ) 
	#define CAL_cl2_createidareareceiver  cl2_createidareareceiver
	#define CHK_cl2_createidareareceiver  TRUE
	#define EXP_cl2_createidareareceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createidareareceiver", (RTS_UINTPTR)cl2_createidareareceiver, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_createidareareceiver
	#define EXT_cl2_createidareareceiver
	#define GET_cl2_createidareareceiver(fl)  CAL_CMGETAPI( "cl2_createidareareceiver" ) 
	#define CAL_cl2_createidareareceiver  cl2_createidareareceiver
	#define CHK_cl2_createidareareceiver  TRUE
	#define EXP_cl2_createidareareceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createidareareceiver", (RTS_UINTPTR)cl2_createidareareceiver, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_createidareareceiver
	#define EXT_CmpCAACanL2cl2_createidareareceiver
	#define GET_CmpCAACanL2cl2_createidareareceiver  ERR_OK
	#define CAL_CmpCAACanL2cl2_createidareareceiver  cl2_createidareareceiver
	#define CHK_CmpCAACanL2cl2_createidareareceiver  TRUE
	#define EXP_CmpCAACanL2cl2_createidareareceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createidareareceiver", (RTS_UINTPTR)cl2_createidareareceiver, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_createidareareceiver
	#define EXT_cl2_createidareareceiver
	#define GET_cl2_createidareareceiver(fl)  CAL_CMGETAPI( "cl2_createidareareceiver" ) 
	#define CAL_cl2_createidareareceiver  cl2_createidareareceiver
	#define CHK_cl2_createidareareceiver  TRUE
	#define EXP_cl2_createidareareceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createidareareceiver", (RTS_UINTPTR)cl2_createidareareceiver, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_createidareareceiver  PFCL2_CREATEIDAREARECEIVER_IEC pfcl2_createidareareceiver;
	#define EXT_cl2_createidareareceiver  extern PFCL2_CREATEIDAREARECEIVER_IEC pfcl2_createidareareceiver;
	#define GET_cl2_createidareareceiver(fl)  s_pfCMGetAPI2( "cl2_createidareareceiver", (RTS_VOID_FCTPTR *)&pfcl2_createidareareceiver, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_createidareareceiver  pfcl2_createidareareceiver
	#define CHK_cl2_createidareareceiver  (pfcl2_createidareareceiver != NULL)
	#define EXP_cl2_createidareareceiver   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createidareareceiver", (RTS_UINTPTR)cl2_createidareareceiver, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_createidareareceiverex</description>
 */
typedef struct tagcl2_createidareareceiverex_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_BOOL xAlwaysNewest;				/* VAR_INPUT */
	CAA_BOOL xReverse;					/* VAR_INPUT */
	CAA_ENUM eEvent;					/* VAR_INPUT */
	CAA_BOOL xEnableSyncWindow;			/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE CreateIdAreaReceiverEx;	/* VAR_OUTPUT */
} cl2_createidareareceiverex_struct;

void CDECL CDECL_EXT cl2_createidareareceiverex(cl2_createidareareceiverex_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_CREATEIDAREARECEIVEREX_IEC) (cl2_createidareareceiverex_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CREATEIDAREARECEIVEREX_NOTIMPLEMENTED)
	#define USE_cl2_createidareareceiverex
	#define EXT_cl2_createidareareceiverex
	#define GET_cl2_createidareareceiverex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_createidareareceiverex(p0) 
	#define CHK_cl2_createidareareceiverex  FALSE
	#define EXP_cl2_createidareareceiverex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_createidareareceiverex
	#define EXT_cl2_createidareareceiverex
	#define GET_cl2_createidareareceiverex(fl)  CAL_CMGETAPI( "cl2_createidareareceiverex" ) 
	#define CAL_cl2_createidareareceiverex  cl2_createidareareceiverex
	#define CHK_cl2_createidareareceiverex  TRUE
	#define EXP_cl2_createidareareceiverex  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createidareareceiverex", (RTS_UINTPTR)cl2_createidareareceiverex, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_createidareareceiverex
	#define EXT_cl2_createidareareceiverex
	#define GET_cl2_createidareareceiverex(fl)  CAL_CMGETAPI( "cl2_createidareareceiverex" ) 
	#define CAL_cl2_createidareareceiverex  cl2_createidareareceiverex
	#define CHK_cl2_createidareareceiverex  TRUE
	#define EXP_cl2_createidareareceiverex  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createidareareceiverex", (RTS_UINTPTR)cl2_createidareareceiverex, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_createidareareceiverex
	#define EXT_CmpCAACanL2cl2_createidareareceiverex
	#define GET_CmpCAACanL2cl2_createidareareceiverex  ERR_OK
	#define CAL_CmpCAACanL2cl2_createidareareceiverex  cl2_createidareareceiverex
	#define CHK_CmpCAACanL2cl2_createidareareceiverex  TRUE
	#define EXP_CmpCAACanL2cl2_createidareareceiverex  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createidareareceiverex", (RTS_UINTPTR)cl2_createidareareceiverex, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_createidareareceiverex
	#define EXT_cl2_createidareareceiverex
	#define GET_cl2_createidareareceiverex(fl)  CAL_CMGETAPI( "cl2_createidareareceiverex" ) 
	#define CAL_cl2_createidareareceiverex  cl2_createidareareceiverex
	#define CHK_cl2_createidareareceiverex  TRUE
	#define EXP_cl2_createidareareceiverex  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createidareareceiverex", (RTS_UINTPTR)cl2_createidareareceiverex, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_createidareareceiverex  PFCL2_CREATEIDAREARECEIVEREX_IEC pfcl2_createidareareceiverex;
	#define EXT_cl2_createidareareceiverex  extern PFCL2_CREATEIDAREARECEIVEREX_IEC pfcl2_createidareareceiverex;
	#define GET_cl2_createidareareceiverex(fl)  s_pfCMGetAPI2( "cl2_createidareareceiverex", (RTS_VOID_FCTPTR *)&pfcl2_createidareareceiverex, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_createidareareceiverex  pfcl2_createidareareceiverex
	#define CHK_cl2_createidareareceiverex  (pfcl2_createidareareceiverex != NULL)
	#define EXP_cl2_createidareareceiverex   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createidareareceiverex", (RTS_UINTPTR)cl2_createidareareceiverex, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_createmessage</description>
 */
typedef struct tagcl2_createmessage_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CL2I_COBID cobID;						/* VAR_INPUT */
	RTS_IEC_USINT usiLength;			/* VAR_INPUT */
	CAA_BOOL xRTR;							/* VAR_INPUT */
	CAA_BOOL x29BitID;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE CreateMessage;			/* VAR_OUTPUT */
} cl2_createmessage_struct;

void CDECL CDECL_EXT cl2_createmessage(cl2_createmessage_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_CREATEMESSAGE_IEC) (cl2_createmessage_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CREATEMESSAGE_NOTIMPLEMENTED)
	#define USE_cl2_createmessage
	#define EXT_cl2_createmessage
	#define GET_cl2_createmessage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_createmessage(p0) 
	#define CHK_cl2_createmessage  FALSE
	#define EXP_cl2_createmessage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_createmessage
	#define EXT_cl2_createmessage
	#define GET_cl2_createmessage(fl)  CAL_CMGETAPI( "cl2_createmessage" ) 
	#define CAL_cl2_createmessage  cl2_createmessage
	#define CHK_cl2_createmessage  TRUE
	#define EXP_cl2_createmessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createmessage", (RTS_UINTPTR)cl2_createmessage, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_createmessage
	#define EXT_cl2_createmessage
	#define GET_cl2_createmessage(fl)  CAL_CMGETAPI( "cl2_createmessage" ) 
	#define CAL_cl2_createmessage  cl2_createmessage
	#define CHK_cl2_createmessage  TRUE
	#define EXP_cl2_createmessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createmessage", (RTS_UINTPTR)cl2_createmessage, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_createmessage
	#define EXT_CmpCAACanL2cl2_createmessage
	#define GET_CmpCAACanL2cl2_createmessage  ERR_OK
	#define CAL_CmpCAACanL2cl2_createmessage  cl2_createmessage
	#define CHK_CmpCAACanL2cl2_createmessage  TRUE
	#define EXP_CmpCAACanL2cl2_createmessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createmessage", (RTS_UINTPTR)cl2_createmessage, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_createmessage
	#define EXT_cl2_createmessage
	#define GET_cl2_createmessage(fl)  CAL_CMGETAPI( "cl2_createmessage" ) 
	#define CAL_cl2_createmessage  cl2_createmessage
	#define CHK_cl2_createmessage  TRUE
	#define EXP_cl2_createmessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createmessage", (RTS_UINTPTR)cl2_createmessage, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_createmessage  PFCL2_CREATEMESSAGE_IEC pfcl2_createmessage;
	#define EXT_cl2_createmessage  extern PFCL2_CREATEMESSAGE_IEC pfcl2_createmessage;
	#define GET_cl2_createmessage(fl)  s_pfCMGetAPI2( "cl2_createmessage", (RTS_VOID_FCTPTR *)&pfcl2_createmessage, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_createmessage  pfcl2_createmessage
	#define CHK_cl2_createmessage  (pfcl2_createmessage != NULL)
	#define EXP_cl2_createmessage   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_createmessage", (RTS_UINTPTR)cl2_createmessage, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_registeridarea</description>
 */
typedef struct tagcl2_registeridarea_struct
{
	CAA_HANDLE hReceiverId;				/* VAR_INPUT */
	CL2I_COBID cobIdStart;				/* VAR_INPUT */
	CL2I_COBID cobIdEnd;					/* VAR_INPUT */
	CAA_BOOL xRTRValue;					/* VAR_INPUT */
	CAA_BOOL xRTRMask;					/* VAR_INPUT */
	CAA_BOOL x29BitIdValue;				/* VAR_INPUT */
	CAA_BOOL x29BitIdMask;				/* VAR_INPUT */
	CAA_BOOL xTransmitValue;			/* VAR_INPUT */
	CAA_BOOL xTransmitMask;				/* VAR_INPUT */
	CAA_ERROR RegisterIdArea;			/* VAR_OUTPUT */
} cl2_registeridarea_struct;

void CDECL CDECL_EXT cl2_registeridarea(cl2_registeridarea_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_REGISTERIDAREA_IEC) (cl2_registeridarea_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_REGISTERIDAREA_NOTIMPLEMENTED)
	#define USE_cl2_registeridarea
	#define EXT_cl2_registeridarea
	#define GET_cl2_registeridarea(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_registeridarea(p0) 
	#define CHK_cl2_registeridarea  FALSE
	#define EXP_cl2_registeridarea  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_registeridarea
	#define EXT_cl2_registeridarea
	#define GET_cl2_registeridarea(fl)  CAL_CMGETAPI( "cl2_registeridarea" ) 
	#define CAL_cl2_registeridarea  cl2_registeridarea
	#define CHK_cl2_registeridarea  TRUE
	#define EXP_cl2_registeridarea  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_registeridarea", (RTS_UINTPTR)cl2_registeridarea, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_registeridarea
	#define EXT_cl2_registeridarea
	#define GET_cl2_registeridarea(fl)  CAL_CMGETAPI( "cl2_registeridarea" ) 
	#define CAL_cl2_registeridarea  cl2_registeridarea
	#define CHK_cl2_registeridarea  TRUE
	#define EXP_cl2_registeridarea  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_registeridarea", (RTS_UINTPTR)cl2_registeridarea, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_registeridarea
	#define EXT_CmpCAACanL2cl2_registeridarea
	#define GET_CmpCAACanL2cl2_registeridarea  ERR_OK
	#define CAL_CmpCAACanL2cl2_registeridarea  cl2_registeridarea
	#define CHK_CmpCAACanL2cl2_registeridarea  TRUE
	#define EXP_CmpCAACanL2cl2_registeridarea  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_registeridarea", (RTS_UINTPTR)cl2_registeridarea, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_registeridarea
	#define EXT_cl2_registeridarea
	#define GET_cl2_registeridarea(fl)  CAL_CMGETAPI( "cl2_registeridarea" ) 
	#define CAL_cl2_registeridarea  cl2_registeridarea
	#define CHK_cl2_registeridarea  TRUE
	#define EXP_cl2_registeridarea  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_registeridarea", (RTS_UINTPTR)cl2_registeridarea, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_registeridarea  PFCL2_REGISTERIDAREA_IEC pfcl2_registeridarea;
	#define EXT_cl2_registeridarea  extern PFCL2_REGISTERIDAREA_IEC pfcl2_registeridarea;
	#define GET_cl2_registeridarea(fl)  s_pfCMGetAPI2( "cl2_registeridarea", (RTS_VOID_FCTPTR *)&pfcl2_registeridarea, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_registeridarea  pfcl2_registeridarea
	#define CHK_cl2_registeridarea  (pfcl2_registeridarea != NULL)
	#define EXP_cl2_registeridarea   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_registeridarea", (RTS_UINTPTR)cl2_registeridarea, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_driverclose</description>
 */
typedef struct tagcl2_driverclose_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR DriverClose;				/* VAR_OUTPUT */
} cl2_driverclose_struct;

void CDECL CDECL_EXT cl2_driverclose(cl2_driverclose_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_DRIVERCLOSE_IEC) (cl2_driverclose_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_DRIVERCLOSE_NOTIMPLEMENTED)
	#define USE_cl2_driverclose
	#define EXT_cl2_driverclose
	#define GET_cl2_driverclose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_driverclose(p0) 
	#define CHK_cl2_driverclose  FALSE
	#define EXP_cl2_driverclose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_driverclose
	#define EXT_cl2_driverclose
	#define GET_cl2_driverclose(fl)  CAL_CMGETAPI( "cl2_driverclose" ) 
	#define CAL_cl2_driverclose  cl2_driverclose
	#define CHK_cl2_driverclose  TRUE
	#define EXP_cl2_driverclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_driverclose", (RTS_UINTPTR)cl2_driverclose, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_driverclose
	#define EXT_cl2_driverclose
	#define GET_cl2_driverclose(fl)  CAL_CMGETAPI( "cl2_driverclose" ) 
	#define CAL_cl2_driverclose  cl2_driverclose
	#define CHK_cl2_driverclose  TRUE
	#define EXP_cl2_driverclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_driverclose", (RTS_UINTPTR)cl2_driverclose, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_driverclose
	#define EXT_CmpCAACanL2cl2_driverclose
	#define GET_CmpCAACanL2cl2_driverclose  ERR_OK
	#define CAL_CmpCAACanL2cl2_driverclose  cl2_driverclose
	#define CHK_CmpCAACanL2cl2_driverclose  TRUE
	#define EXP_CmpCAACanL2cl2_driverclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_driverclose", (RTS_UINTPTR)cl2_driverclose, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_driverclose
	#define EXT_cl2_driverclose
	#define GET_cl2_driverclose(fl)  CAL_CMGETAPI( "cl2_driverclose" ) 
	#define CAL_cl2_driverclose  cl2_driverclose
	#define CHK_cl2_driverclose  TRUE
	#define EXP_cl2_driverclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_driverclose", (RTS_UINTPTR)cl2_driverclose, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_driverclose  PFCL2_DRIVERCLOSE_IEC pfcl2_driverclose;
	#define EXT_cl2_driverclose  extern PFCL2_DRIVERCLOSE_IEC pfcl2_driverclose;
	#define GET_cl2_driverclose(fl)  s_pfCMGetAPI2( "cl2_driverclose", (RTS_VOID_FCTPTR *)&pfcl2_driverclose, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_driverclose  pfcl2_driverclose
	#define CHK_cl2_driverclose  (pfcl2_driverclose != NULL)
	#define EXP_cl2_driverclose   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_driverclose", (RTS_UINTPTR)cl2_driverclose, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_clonemessage</description>
 */
typedef struct tagcl2_clonemessage_struct
{
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE CloneMessage;			/* VAR_OUTPUT */
} cl2_clonemessage_struct;

void CDECL CDECL_EXT cl2_clonemessage(cl2_clonemessage_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_CLONEMESSAGE_IEC) (cl2_clonemessage_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CLONEMESSAGE_NOTIMPLEMENTED)
	#define USE_cl2_clonemessage
	#define EXT_cl2_clonemessage
	#define GET_cl2_clonemessage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_clonemessage(p0) 
	#define CHK_cl2_clonemessage  FALSE
	#define EXP_cl2_clonemessage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_clonemessage
	#define EXT_cl2_clonemessage
	#define GET_cl2_clonemessage(fl)  CAL_CMGETAPI( "cl2_clonemessage" ) 
	#define CAL_cl2_clonemessage  cl2_clonemessage
	#define CHK_cl2_clonemessage  TRUE
	#define EXP_cl2_clonemessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_clonemessage", (RTS_UINTPTR)cl2_clonemessage, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_clonemessage
	#define EXT_cl2_clonemessage
	#define GET_cl2_clonemessage(fl)  CAL_CMGETAPI( "cl2_clonemessage" ) 
	#define CAL_cl2_clonemessage  cl2_clonemessage
	#define CHK_cl2_clonemessage  TRUE
	#define EXP_cl2_clonemessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_clonemessage", (RTS_UINTPTR)cl2_clonemessage, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_clonemessage
	#define EXT_CmpCAACanL2cl2_clonemessage
	#define GET_CmpCAACanL2cl2_clonemessage  ERR_OK
	#define CAL_CmpCAACanL2cl2_clonemessage  cl2_clonemessage
	#define CHK_CmpCAACanL2cl2_clonemessage  TRUE
	#define EXP_CmpCAACanL2cl2_clonemessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_clonemessage", (RTS_UINTPTR)cl2_clonemessage, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_clonemessage
	#define EXT_cl2_clonemessage
	#define GET_cl2_clonemessage(fl)  CAL_CMGETAPI( "cl2_clonemessage" ) 
	#define CAL_cl2_clonemessage  cl2_clonemessage
	#define CHK_cl2_clonemessage  TRUE
	#define EXP_cl2_clonemessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_clonemessage", (RTS_UINTPTR)cl2_clonemessage, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_clonemessage  PFCL2_CLONEMESSAGE_IEC pfcl2_clonemessage;
	#define EXT_cl2_clonemessage  extern PFCL2_CLONEMESSAGE_IEC pfcl2_clonemessage;
	#define GET_cl2_clonemessage(fl)  s_pfCMGetAPI2( "cl2_clonemessage", (RTS_VOID_FCTPTR *)&pfcl2_clonemessage, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_clonemessage  pfcl2_clonemessage
	#define CHK_cl2_clonemessage  (pfcl2_clonemessage != NULL)
	#define EXP_cl2_clonemessage   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_clonemessage", (RTS_UINTPTR)cl2_clonemessage, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_getbusstate</description>
 */
typedef struct tagcl2_getbusstate_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_ENUM GetBusState;				/* VAR_OUTPUT */
} cl2_getbusstate_struct;

void CDECL CDECL_EXT cl2_getbusstate(cl2_getbusstate_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_GETBUSSTATE_IEC) (cl2_getbusstate_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETBUSSTATE_NOTIMPLEMENTED)
	#define USE_cl2_getbusstate
	#define EXT_cl2_getbusstate
	#define GET_cl2_getbusstate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_getbusstate(p0) 
	#define CHK_cl2_getbusstate  FALSE
	#define EXP_cl2_getbusstate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_getbusstate
	#define EXT_cl2_getbusstate
	#define GET_cl2_getbusstate(fl)  CAL_CMGETAPI( "cl2_getbusstate" ) 
	#define CAL_cl2_getbusstate  cl2_getbusstate
	#define CHK_cl2_getbusstate  TRUE
	#define EXP_cl2_getbusstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getbusstate", (RTS_UINTPTR)cl2_getbusstate, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_getbusstate
	#define EXT_cl2_getbusstate
	#define GET_cl2_getbusstate(fl)  CAL_CMGETAPI( "cl2_getbusstate" ) 
	#define CAL_cl2_getbusstate  cl2_getbusstate
	#define CHK_cl2_getbusstate  TRUE
	#define EXP_cl2_getbusstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getbusstate", (RTS_UINTPTR)cl2_getbusstate, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_getbusstate
	#define EXT_CmpCAACanL2cl2_getbusstate
	#define GET_CmpCAACanL2cl2_getbusstate  ERR_OK
	#define CAL_CmpCAACanL2cl2_getbusstate  cl2_getbusstate
	#define CHK_CmpCAACanL2cl2_getbusstate  TRUE
	#define EXP_CmpCAACanL2cl2_getbusstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getbusstate", (RTS_UINTPTR)cl2_getbusstate, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_getbusstate
	#define EXT_cl2_getbusstate
	#define GET_cl2_getbusstate(fl)  CAL_CMGETAPI( "cl2_getbusstate" ) 
	#define CAL_cl2_getbusstate  cl2_getbusstate
	#define CHK_cl2_getbusstate  TRUE
	#define EXP_cl2_getbusstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getbusstate", (RTS_UINTPTR)cl2_getbusstate, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_getbusstate  PFCL2_GETBUSSTATE_IEC pfcl2_getbusstate;
	#define EXT_cl2_getbusstate  extern PFCL2_GETBUSSTATE_IEC pfcl2_getbusstate;
	#define GET_cl2_getbusstate(fl)  s_pfCMGetAPI2( "cl2_getbusstate", (RTS_VOID_FCTPTR *)&pfcl2_getbusstate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_getbusstate  pfcl2_getbusstate
	#define CHK_cl2_getbusstate  (pfcl2_getbusstate != NULL)
	#define EXP_cl2_getbusstate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getbusstate", (RTS_UINTPTR)cl2_getbusstate, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_issendingactive</description>
 */
typedef struct tagcl2_issendingactive_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_BOOL IsSendingActive;			/* VAR_OUTPUT */
} cl2_issendingactive_struct;

void CDECL CDECL_EXT cl2_issendingactive(cl2_issendingactive_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_ISSENDINGACTIVE_IEC) (cl2_issendingactive_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_ISSENDINGACTIVE_NOTIMPLEMENTED)
	#define USE_cl2_issendingactive
	#define EXT_cl2_issendingactive
	#define GET_cl2_issendingactive(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_issendingactive(p0) 
	#define CHK_cl2_issendingactive  FALSE
	#define EXP_cl2_issendingactive  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_issendingactive
	#define EXT_cl2_issendingactive
	#define GET_cl2_issendingactive(fl)  CAL_CMGETAPI( "cl2_issendingactive" ) 
	#define CAL_cl2_issendingactive  cl2_issendingactive
	#define CHK_cl2_issendingactive  TRUE
	#define EXP_cl2_issendingactive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_issendingactive", (RTS_UINTPTR)cl2_issendingactive, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_issendingactive
	#define EXT_cl2_issendingactive
	#define GET_cl2_issendingactive(fl)  CAL_CMGETAPI( "cl2_issendingactive" ) 
	#define CAL_cl2_issendingactive  cl2_issendingactive
	#define CHK_cl2_issendingactive  TRUE
	#define EXP_cl2_issendingactive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_issendingactive", (RTS_UINTPTR)cl2_issendingactive, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_issendingactive
	#define EXT_CmpCAACanL2cl2_issendingactive
	#define GET_CmpCAACanL2cl2_issendingactive  ERR_OK
	#define CAL_CmpCAACanL2cl2_issendingactive  cl2_issendingactive
	#define CHK_CmpCAACanL2cl2_issendingactive  TRUE
	#define EXP_CmpCAACanL2cl2_issendingactive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_issendingactive", (RTS_UINTPTR)cl2_issendingactive, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_issendingactive
	#define EXT_cl2_issendingactive
	#define GET_cl2_issendingactive(fl)  CAL_CMGETAPI( "cl2_issendingactive" ) 
	#define CAL_cl2_issendingactive  cl2_issendingactive
	#define CHK_cl2_issendingactive  TRUE
	#define EXP_cl2_issendingactive  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_issendingactive", (RTS_UINTPTR)cl2_issendingactive, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_issendingactive  PFCL2_ISSENDINGACTIVE_IEC pfcl2_issendingactive;
	#define EXT_cl2_issendingactive  extern PFCL2_ISSENDINGACTIVE_IEC pfcl2_issendingactive;
	#define GET_cl2_issendingactive(fl)  s_pfCMGetAPI2( "cl2_issendingactive", (RTS_VOID_FCTPTR *)&pfcl2_issendingactive, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_issendingactive  pfcl2_issendingactive
	#define CHK_cl2_issendingactive  (pfcl2_issendingactive != NULL)
	#define EXP_cl2_issendingactive   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_issendingactive", (RTS_UINTPTR)cl2_issendingactive, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_read</description>
 */
typedef struct tagcl2_read_struct
{
	CAA_HANDLE hReceiverId;				/* VAR_INPUT */
	CAA_COUNT* pctMsgLeft;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE Read;					/* VAR_OUTPUT */
} cl2_read_struct;

void CDECL CDECL_EXT cl2_read(cl2_read_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_READ_IEC) (cl2_read_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_READ_NOTIMPLEMENTED)
	#define USE_cl2_read
	#define EXT_cl2_read
	#define GET_cl2_read(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_read(p0) 
	#define CHK_cl2_read  FALSE
	#define EXP_cl2_read  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_read
	#define EXT_cl2_read
	#define GET_cl2_read(fl)  CAL_CMGETAPI( "cl2_read" ) 
	#define CAL_cl2_read  cl2_read
	#define CHK_cl2_read  TRUE
	#define EXP_cl2_read  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_read", (RTS_UINTPTR)cl2_read, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_read
	#define EXT_cl2_read
	#define GET_cl2_read(fl)  CAL_CMGETAPI( "cl2_read" ) 
	#define CAL_cl2_read  cl2_read
	#define CHK_cl2_read  TRUE
	#define EXP_cl2_read  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_read", (RTS_UINTPTR)cl2_read, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_read
	#define EXT_CmpCAACanL2cl2_read
	#define GET_CmpCAACanL2cl2_read  ERR_OK
	#define CAL_CmpCAACanL2cl2_read  cl2_read
	#define CHK_CmpCAACanL2cl2_read  TRUE
	#define EXP_CmpCAACanL2cl2_read  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_read", (RTS_UINTPTR)cl2_read, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_read
	#define EXT_cl2_read
	#define GET_cl2_read(fl)  CAL_CMGETAPI( "cl2_read" ) 
	#define CAL_cl2_read  cl2_read
	#define CHK_cl2_read  TRUE
	#define EXP_cl2_read  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_read", (RTS_UINTPTR)cl2_read, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_read  PFCL2_READ_IEC pfcl2_read;
	#define EXT_cl2_read  extern PFCL2_READ_IEC pfcl2_read;
	#define GET_cl2_read(fl)  s_pfCMGetAPI2( "cl2_read", (RTS_VOID_FCTPTR *)&pfcl2_read, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_read  pfcl2_read
	#define CHK_cl2_read  (pfcl2_read != NULL)
	#define EXP_cl2_read   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_read", (RTS_UINTPTR)cl2_read, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_readarrayreceiver</description>
 */
typedef struct tagcl2_readarrayreceiver_struct
{
	CAA_HANDLE hArrayReceiver;			/* VAR_INPUT */
	CAA_COUNT  ctIndex;					/* VAR_INPUT */
	CAA_COUNT* pctMsgLeft;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE ReadArrayReceiver;		/* VAR_OUTPUT */
} cl2_readarrayreceiver_struct;

void CDECL CDECL_EXT cl2_readarrayreceiver(cl2_readarrayreceiver_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_READARRAYRECEIVER_IEC) (cl2_readarrayreceiver_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_READARRAYRECEIVER_NOTIMPLEMENTED)
	#define USE_cl2_readarrayreceiver
	#define EXT_cl2_readarrayreceiver
	#define GET_cl2_readarrayreceiver(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_readarrayreceiver(p0) 
	#define CHK_cl2_readarrayreceiver  FALSE
	#define EXP_cl2_readarrayreceiver  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_readarrayreceiver
	#define EXT_cl2_readarrayreceiver
	#define GET_cl2_readarrayreceiver(fl)  CAL_CMGETAPI( "cl2_readarrayreceiver" ) 
	#define CAL_cl2_readarrayreceiver  cl2_readarrayreceiver
	#define CHK_cl2_readarrayreceiver  TRUE
	#define EXP_cl2_readarrayreceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_readarrayreceiver", (RTS_UINTPTR)cl2_readarrayreceiver, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_readarrayreceiver
	#define EXT_cl2_readarrayreceiver
	#define GET_cl2_readarrayreceiver(fl)  CAL_CMGETAPI( "cl2_readarrayreceiver" ) 
	#define CAL_cl2_readarrayreceiver  cl2_readarrayreceiver
	#define CHK_cl2_readarrayreceiver  TRUE
	#define EXP_cl2_readarrayreceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_readarrayreceiver", (RTS_UINTPTR)cl2_readarrayreceiver, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_readarrayreceiver
	#define EXT_CmpCAACanL2cl2_readarrayreceiver
	#define GET_CmpCAACanL2cl2_readarrayreceiver  ERR_OK
	#define CAL_CmpCAACanL2cl2_readarrayreceiver  cl2_readarrayreceiver
	#define CHK_CmpCAACanL2cl2_readarrayreceiver  TRUE
	#define EXP_CmpCAACanL2cl2_readarrayreceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_readarrayreceiver", (RTS_UINTPTR)cl2_readarrayreceiver, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_readarrayreceiver
	#define EXT_cl2_readarrayreceiver
	#define GET_cl2_readarrayreceiver(fl)  CAL_CMGETAPI( "cl2_readarrayreceiver" ) 
	#define CAL_cl2_readarrayreceiver  cl2_readarrayreceiver
	#define CHK_cl2_readarrayreceiver  TRUE
	#define EXP_cl2_readarrayreceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_readarrayreceiver", (RTS_UINTPTR)cl2_readarrayreceiver, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_readarrayreceiver  PFCL2_READARRAYRECEIVER_IEC pfcl2_readarrayreceiver;
	#define EXT_cl2_readarrayreceiver  extern PFCL2_READARRAYRECEIVER_IEC pfcl2_readarrayreceiver;
	#define GET_cl2_readarrayreceiver(fl)  s_pfCMGetAPI2( "cl2_readarrayreceiver", (RTS_VOID_FCTPTR *)&pfcl2_readarrayreceiver, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_readarrayreceiver  pfcl2_readarrayreceiver
	#define CHK_cl2_readarrayreceiver  (pfcl2_readarrayreceiver != NULL)
	#define EXP_cl2_readarrayreceiver   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_readarrayreceiver", (RTS_UINTPTR)cl2_readarrayreceiver, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_getbaudrate</description>
 */
typedef struct tagcl2_getbaudrate_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	RTS_IEC_UINT GetBaudrate;			/* VAR_OUTPUT */
} cl2_getbaudrate_struct;

void CDECL CDECL_EXT cl2_getbaudrate(cl2_getbaudrate_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_GETBAUDRATE_IEC) (cl2_getbaudrate_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETBAUDRATE_NOTIMPLEMENTED)
	#define USE_cl2_getbaudrate
	#define EXT_cl2_getbaudrate
	#define GET_cl2_getbaudrate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_getbaudrate(p0) 
	#define CHK_cl2_getbaudrate  FALSE
	#define EXP_cl2_getbaudrate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_getbaudrate
	#define EXT_cl2_getbaudrate
	#define GET_cl2_getbaudrate(fl)  CAL_CMGETAPI( "cl2_getbaudrate" ) 
	#define CAL_cl2_getbaudrate  cl2_getbaudrate
	#define CHK_cl2_getbaudrate  TRUE
	#define EXP_cl2_getbaudrate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getbaudrate", (RTS_UINTPTR)cl2_getbaudrate, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_getbaudrate
	#define EXT_cl2_getbaudrate
	#define GET_cl2_getbaudrate(fl)  CAL_CMGETAPI( "cl2_getbaudrate" ) 
	#define CAL_cl2_getbaudrate  cl2_getbaudrate
	#define CHK_cl2_getbaudrate  TRUE
	#define EXP_cl2_getbaudrate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getbaudrate", (RTS_UINTPTR)cl2_getbaudrate, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_getbaudrate
	#define EXT_CmpCAACanL2cl2_getbaudrate
	#define GET_CmpCAACanL2cl2_getbaudrate  ERR_OK
	#define CAL_CmpCAACanL2cl2_getbaudrate  cl2_getbaudrate
	#define CHK_CmpCAACanL2cl2_getbaudrate  TRUE
	#define EXP_CmpCAACanL2cl2_getbaudrate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getbaudrate", (RTS_UINTPTR)cl2_getbaudrate, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_getbaudrate
	#define EXT_cl2_getbaudrate
	#define GET_cl2_getbaudrate(fl)  CAL_CMGETAPI( "cl2_getbaudrate" ) 
	#define CAL_cl2_getbaudrate  cl2_getbaudrate
	#define CHK_cl2_getbaudrate  TRUE
	#define EXP_cl2_getbaudrate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getbaudrate", (RTS_UINTPTR)cl2_getbaudrate, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_getbaudrate  PFCL2_GETBAUDRATE_IEC pfcl2_getbaudrate;
	#define EXT_cl2_getbaudrate  extern PFCL2_GETBAUDRATE_IEC pfcl2_getbaudrate;
	#define GET_cl2_getbaudrate(fl)  s_pfCMGetAPI2( "cl2_getbaudrate", (RTS_VOID_FCTPTR *)&pfcl2_getbaudrate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_getbaudrate  pfcl2_getbaudrate
	#define CHK_cl2_getbaudrate  (pfcl2_getbaudrate != NULL)
	#define EXP_cl2_getbaudrate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getbaudrate", (RTS_UINTPTR)cl2_getbaudrate, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_getproperty</description>
 */
typedef struct tagcl2_getproperty_struct
{
	RTS_IEC_UINT uiProperty;			/* VAR_INPUT */
	RTS_IEC_UDINT GetProperty;			/* VAR_OUTPUT */
} cl2_getproperty_struct;

void CDECL CDECL_EXT cl2_getproperty(cl2_getproperty_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_GETPROPERTY_IEC) (cl2_getproperty_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETPROPERTY_NOTIMPLEMENTED)
	#define USE_cl2_getproperty
	#define EXT_cl2_getproperty
	#define GET_cl2_getproperty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_getproperty(p0) 
	#define CHK_cl2_getproperty  FALSE
	#define EXP_cl2_getproperty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_getproperty
	#define EXT_cl2_getproperty
	#define GET_cl2_getproperty(fl)  CAL_CMGETAPI( "cl2_getproperty" ) 
	#define CAL_cl2_getproperty  cl2_getproperty
	#define CHK_cl2_getproperty  TRUE
	#define EXP_cl2_getproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getproperty", (RTS_UINTPTR)cl2_getproperty, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_getproperty
	#define EXT_cl2_getproperty
	#define GET_cl2_getproperty(fl)  CAL_CMGETAPI( "cl2_getproperty" ) 
	#define CAL_cl2_getproperty  cl2_getproperty
	#define CHK_cl2_getproperty  TRUE
	#define EXP_cl2_getproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getproperty", (RTS_UINTPTR)cl2_getproperty, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_getproperty
	#define EXT_CmpCAACanL2cl2_getproperty
	#define GET_CmpCAACanL2cl2_getproperty  ERR_OK
	#define CAL_CmpCAACanL2cl2_getproperty  cl2_getproperty
	#define CHK_CmpCAACanL2cl2_getproperty  TRUE
	#define EXP_CmpCAACanL2cl2_getproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getproperty", (RTS_UINTPTR)cl2_getproperty, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_getproperty
	#define EXT_cl2_getproperty
	#define GET_cl2_getproperty(fl)  CAL_CMGETAPI( "cl2_getproperty" ) 
	#define CAL_cl2_getproperty  cl2_getproperty
	#define CHK_cl2_getproperty  TRUE
	#define EXP_cl2_getproperty  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getproperty", (RTS_UINTPTR)cl2_getproperty, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_getproperty  PFCL2_GETPROPERTY_IEC pfcl2_getproperty;
	#define EXT_cl2_getproperty  extern PFCL2_GETPROPERTY_IEC pfcl2_getproperty;
	#define GET_cl2_getproperty(fl)  s_pfCMGetAPI2( "cl2_getproperty", (RTS_VOID_FCTPTR *)&pfcl2_getproperty, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_getproperty  pfcl2_getproperty
	#define CHK_cl2_getproperty  (pfcl2_getproperty != NULL)
	#define EXP_cl2_getproperty   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getproperty", (RTS_UINTPTR)cl2_getproperty, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_istransmitmessage</description>
 */
typedef struct tagcl2_istransmitmessage_struct
{
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_BOOL IsTransmitMessage;			/* VAR_OUTPUT */
} cl2_istransmitmessage_struct;

void CDECL CDECL_EXT cl2_istransmitmessage(cl2_istransmitmessage_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_ISTRANSMITMESSAGE_IEC) (cl2_istransmitmessage_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_ISTRANSMITMESSAGE_NOTIMPLEMENTED)
	#define USE_cl2_istransmitmessage
	#define EXT_cl2_istransmitmessage
	#define GET_cl2_istransmitmessage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_istransmitmessage(p0) 
	#define CHK_cl2_istransmitmessage  FALSE
	#define EXP_cl2_istransmitmessage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_istransmitmessage
	#define EXT_cl2_istransmitmessage
	#define GET_cl2_istransmitmessage(fl)  CAL_CMGETAPI( "cl2_istransmitmessage" ) 
	#define CAL_cl2_istransmitmessage  cl2_istransmitmessage
	#define CHK_cl2_istransmitmessage  TRUE
	#define EXP_cl2_istransmitmessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_istransmitmessage", (RTS_UINTPTR)cl2_istransmitmessage, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_istransmitmessage
	#define EXT_cl2_istransmitmessage
	#define GET_cl2_istransmitmessage(fl)  CAL_CMGETAPI( "cl2_istransmitmessage" ) 
	#define CAL_cl2_istransmitmessage  cl2_istransmitmessage
	#define CHK_cl2_istransmitmessage  TRUE
	#define EXP_cl2_istransmitmessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_istransmitmessage", (RTS_UINTPTR)cl2_istransmitmessage, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_istransmitmessage
	#define EXT_CmpCAACanL2cl2_istransmitmessage
	#define GET_CmpCAACanL2cl2_istransmitmessage  ERR_OK
	#define CAL_CmpCAACanL2cl2_istransmitmessage  cl2_istransmitmessage
	#define CHK_CmpCAACanL2cl2_istransmitmessage  TRUE
	#define EXP_CmpCAACanL2cl2_istransmitmessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_istransmitmessage", (RTS_UINTPTR)cl2_istransmitmessage, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_istransmitmessage
	#define EXT_cl2_istransmitmessage
	#define GET_cl2_istransmitmessage(fl)  CAL_CMGETAPI( "cl2_istransmitmessage" ) 
	#define CAL_cl2_istransmitmessage  cl2_istransmitmessage
	#define CHK_cl2_istransmitmessage  TRUE
	#define EXP_cl2_istransmitmessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_istransmitmessage", (RTS_UINTPTR)cl2_istransmitmessage, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_istransmitmessage  PFCL2_ISTRANSMITMESSAGE_IEC pfcl2_istransmitmessage;
	#define EXT_cl2_istransmitmessage  extern PFCL2_ISTRANSMITMESSAGE_IEC pfcl2_istransmitmessage;
	#define GET_cl2_istransmitmessage(fl)  s_pfCMGetAPI2( "cl2_istransmitmessage", (RTS_VOID_FCTPTR *)&pfcl2_istransmitmessage, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_istransmitmessage  pfcl2_istransmitmessage
	#define CHK_cl2_istransmitmessage  (pfcl2_istransmitmessage != NULL)
	#define EXP_cl2_istransmitmessage   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_istransmitmessage", (RTS_UINTPTR)cl2_istransmitmessage, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_is29bitidmessage</description>
 */
typedef struct tagcl2_is29bitidmessage_struct
{
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_BOOL Is29BitIdMessage;			/* VAR_OUTPUT */
} cl2_is29bitidmessage_struct;

void CDECL CDECL_EXT cl2_is29bitidmessage(cl2_is29bitidmessage_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_IS29BITIDMESSAGE_IEC) (cl2_is29bitidmessage_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_IS29BITIDMESSAGE_NOTIMPLEMENTED)
	#define USE_cl2_is29bitidmessage
	#define EXT_cl2_is29bitidmessage
	#define GET_cl2_is29bitidmessage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_is29bitidmessage(p0) 
	#define CHK_cl2_is29bitidmessage  FALSE
	#define EXP_cl2_is29bitidmessage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_is29bitidmessage
	#define EXT_cl2_is29bitidmessage
	#define GET_cl2_is29bitidmessage(fl)  CAL_CMGETAPI( "cl2_is29bitidmessage" ) 
	#define CAL_cl2_is29bitidmessage  cl2_is29bitidmessage
	#define CHK_cl2_is29bitidmessage  TRUE
	#define EXP_cl2_is29bitidmessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_is29bitidmessage", (RTS_UINTPTR)cl2_is29bitidmessage, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_is29bitidmessage
	#define EXT_cl2_is29bitidmessage
	#define GET_cl2_is29bitidmessage(fl)  CAL_CMGETAPI( "cl2_is29bitidmessage" ) 
	#define CAL_cl2_is29bitidmessage  cl2_is29bitidmessage
	#define CHK_cl2_is29bitidmessage  TRUE
	#define EXP_cl2_is29bitidmessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_is29bitidmessage", (RTS_UINTPTR)cl2_is29bitidmessage, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_is29bitidmessage
	#define EXT_CmpCAACanL2cl2_is29bitidmessage
	#define GET_CmpCAACanL2cl2_is29bitidmessage  ERR_OK
	#define CAL_CmpCAACanL2cl2_is29bitidmessage  cl2_is29bitidmessage
	#define CHK_CmpCAACanL2cl2_is29bitidmessage  TRUE
	#define EXP_CmpCAACanL2cl2_is29bitidmessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_is29bitidmessage", (RTS_UINTPTR)cl2_is29bitidmessage, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_is29bitidmessage
	#define EXT_cl2_is29bitidmessage
	#define GET_cl2_is29bitidmessage(fl)  CAL_CMGETAPI( "cl2_is29bitidmessage" ) 
	#define CAL_cl2_is29bitidmessage  cl2_is29bitidmessage
	#define CHK_cl2_is29bitidmessage  TRUE
	#define EXP_cl2_is29bitidmessage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_is29bitidmessage", (RTS_UINTPTR)cl2_is29bitidmessage, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_is29bitidmessage  PFCL2_IS29BITIDMESSAGE_IEC pfcl2_is29bitidmessage;
	#define EXT_cl2_is29bitidmessage  extern PFCL2_IS29BITIDMESSAGE_IEC pfcl2_is29bitidmessage;
	#define GET_cl2_is29bitidmessage(fl)  s_pfCMGetAPI2( "cl2_is29bitidmessage", (RTS_VOID_FCTPTR *)&pfcl2_is29bitidmessage, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_is29bitidmessage  pfcl2_is29bitidmessage
	#define CHK_cl2_is29bitidmessage  (pfcl2_is29bitidmessage != NULL)
	#define EXP_cl2_is29bitidmessage   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_is29bitidmessage", (RTS_UINTPTR)cl2_is29bitidmessage, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_getmessagelength</description>
 */
typedef struct tagcl2_getmessagelength_struct
{
	CAA_HANDLE hMessage;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	RTS_IEC_USINT GetMessageLength;		/* VAR_OUTPUT */
} cl2_getmessagelength_struct;

void CDECL CDECL_EXT cl2_getmessagelength(cl2_getmessagelength_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_GETMESSAGELENGTH_IEC) (cl2_getmessagelength_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETMESSAGELENGTH_NOTIMPLEMENTED)
	#define USE_cl2_getmessagelength
	#define EXT_cl2_getmessagelength
	#define GET_cl2_getmessagelength(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_getmessagelength(p0) 
	#define CHK_cl2_getmessagelength  FALSE
	#define EXP_cl2_getmessagelength  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_getmessagelength
	#define EXT_cl2_getmessagelength
	#define GET_cl2_getmessagelength(fl)  CAL_CMGETAPI( "cl2_getmessagelength" ) 
	#define CAL_cl2_getmessagelength  cl2_getmessagelength
	#define CHK_cl2_getmessagelength  TRUE
	#define EXP_cl2_getmessagelength  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getmessagelength", (RTS_UINTPTR)cl2_getmessagelength, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_getmessagelength
	#define EXT_cl2_getmessagelength
	#define GET_cl2_getmessagelength(fl)  CAL_CMGETAPI( "cl2_getmessagelength" ) 
	#define CAL_cl2_getmessagelength  cl2_getmessagelength
	#define CHK_cl2_getmessagelength  TRUE
	#define EXP_cl2_getmessagelength  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getmessagelength", (RTS_UINTPTR)cl2_getmessagelength, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_getmessagelength
	#define EXT_CmpCAACanL2cl2_getmessagelength
	#define GET_CmpCAACanL2cl2_getmessagelength  ERR_OK
	#define CAL_CmpCAACanL2cl2_getmessagelength  cl2_getmessagelength
	#define CHK_CmpCAACanL2cl2_getmessagelength  TRUE
	#define EXP_CmpCAACanL2cl2_getmessagelength  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getmessagelength", (RTS_UINTPTR)cl2_getmessagelength, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_getmessagelength
	#define EXT_cl2_getmessagelength
	#define GET_cl2_getmessagelength(fl)  CAL_CMGETAPI( "cl2_getmessagelength" ) 
	#define CAL_cl2_getmessagelength  cl2_getmessagelength
	#define CHK_cl2_getmessagelength  TRUE
	#define EXP_cl2_getmessagelength  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getmessagelength", (RTS_UINTPTR)cl2_getmessagelength, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_getmessagelength  PFCL2_GETMESSAGELENGTH_IEC pfcl2_getmessagelength;
	#define EXT_cl2_getmessagelength  extern PFCL2_GETMESSAGELENGTH_IEC pfcl2_getmessagelength;
	#define GET_cl2_getmessagelength(fl)  s_pfCMGetAPI2( "cl2_getmessagelength", (RTS_VOID_FCTPTR *)&pfcl2_getmessagelength, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_getmessagelength  pfcl2_getmessagelength
	#define CHK_cl2_getmessagelength  (pfcl2_getmessagelength != NULL)
	#define EXP_cl2_getmessagelength   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getmessagelength", (RTS_UINTPTR)cl2_getmessagelength, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_deletereceiver</description>
 */
typedef struct tagcl2_deletereceiver_struct
{
	CAA_HANDLE hReceiverId;				/* VAR_INPUT */
	CAA_ERROR DeleteReceiver;			/* VAR_OUTPUT */
} cl2_deletereceiver_struct;

void CDECL CDECL_EXT cl2_deletereceiver(cl2_deletereceiver_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_DELETERECEIVER_IEC) (cl2_deletereceiver_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_DELETERECEIVER_NOTIMPLEMENTED)
	#define USE_cl2_deletereceiver
	#define EXT_cl2_deletereceiver
	#define GET_cl2_deletereceiver(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_deletereceiver(p0) 
	#define CHK_cl2_deletereceiver  FALSE
	#define EXP_cl2_deletereceiver  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_deletereceiver
	#define EXT_cl2_deletereceiver
	#define GET_cl2_deletereceiver(fl)  CAL_CMGETAPI( "cl2_deletereceiver" ) 
	#define CAL_cl2_deletereceiver  cl2_deletereceiver
	#define CHK_cl2_deletereceiver  TRUE
	#define EXP_cl2_deletereceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_deletereceiver", (RTS_UINTPTR)cl2_deletereceiver, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_deletereceiver
	#define EXT_cl2_deletereceiver
	#define GET_cl2_deletereceiver(fl)  CAL_CMGETAPI( "cl2_deletereceiver" ) 
	#define CAL_cl2_deletereceiver  cl2_deletereceiver
	#define CHK_cl2_deletereceiver  TRUE
	#define EXP_cl2_deletereceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_deletereceiver", (RTS_UINTPTR)cl2_deletereceiver, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_deletereceiver
	#define EXT_CmpCAACanL2cl2_deletereceiver
	#define GET_CmpCAACanL2cl2_deletereceiver  ERR_OK
	#define CAL_CmpCAACanL2cl2_deletereceiver  cl2_deletereceiver
	#define CHK_CmpCAACanL2cl2_deletereceiver  TRUE
	#define EXP_CmpCAACanL2cl2_deletereceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_deletereceiver", (RTS_UINTPTR)cl2_deletereceiver, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_deletereceiver
	#define EXT_cl2_deletereceiver
	#define GET_cl2_deletereceiver(fl)  CAL_CMGETAPI( "cl2_deletereceiver" ) 
	#define CAL_cl2_deletereceiver  cl2_deletereceiver
	#define CHK_cl2_deletereceiver  TRUE
	#define EXP_cl2_deletereceiver  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_deletereceiver", (RTS_UINTPTR)cl2_deletereceiver, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_deletereceiver  PFCL2_DELETERECEIVER_IEC pfcl2_deletereceiver;
	#define EXT_cl2_deletereceiver  extern PFCL2_DELETERECEIVER_IEC pfcl2_deletereceiver;
	#define GET_cl2_deletereceiver(fl)  s_pfCMGetAPI2( "cl2_deletereceiver", (RTS_VOID_FCTPTR *)&pfcl2_deletereceiver, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_deletereceiver  pfcl2_deletereceiver
	#define CHK_cl2_deletereceiver  (pfcl2_deletereceiver != NULL)
	#define EXP_cl2_deletereceiver   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_deletereceiver", (RTS_UINTPTR)cl2_deletereceiver, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_cstcycleopen</description>
 */
typedef struct tagcl2_cstcycleopen_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ENUM eCstEvent;					/* VAR_INPUT */
	RTS_IEC_USINT usiPriority;			/* VAR_INPUT */
	CAA_BOOL xEnableSyncWindow;			/* VAR_INPUT */
	RTS_IEC_UDINT udiCstCycle;			/* VAR_INPUT */
	RTS_IEC_UDINT udiCstForewarnTime;	/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE CstCycleOpen;			/* VAR_OUTPUT */
} cl2_cstcycleopen_struct;

void CDECL CDECL_EXT cl2_cstcycleopen(cl2_cstcycleopen_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_CSTCYCLEOPEN_IEC) (cl2_cstcycleopen_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_CSTCYCLEOPEN_NOTIMPLEMENTED)
	#define USE_cl2_cstcycleopen
	#define EXT_cl2_cstcycleopen
	#define GET_cl2_cstcycleopen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_cstcycleopen(p0) 
	#define CHK_cl2_cstcycleopen  FALSE
	#define EXP_cl2_cstcycleopen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_cstcycleopen
	#define EXT_cl2_cstcycleopen
	#define GET_cl2_cstcycleopen(fl)  CAL_CMGETAPI( "cl2_cstcycleopen" ) 
	#define CAL_cl2_cstcycleopen  cl2_cstcycleopen
	#define CHK_cl2_cstcycleopen  TRUE
	#define EXP_cl2_cstcycleopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcycleopen", (RTS_UINTPTR)cl2_cstcycleopen, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_cstcycleopen
	#define EXT_cl2_cstcycleopen
	#define GET_cl2_cstcycleopen(fl)  CAL_CMGETAPI( "cl2_cstcycleopen" ) 
	#define CAL_cl2_cstcycleopen  cl2_cstcycleopen
	#define CHK_cl2_cstcycleopen  TRUE
	#define EXP_cl2_cstcycleopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcycleopen", (RTS_UINTPTR)cl2_cstcycleopen, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_cstcycleopen
	#define EXT_CmpCAACanL2cl2_cstcycleopen
	#define GET_CmpCAACanL2cl2_cstcycleopen  ERR_OK
	#define CAL_CmpCAACanL2cl2_cstcycleopen  cl2_cstcycleopen
	#define CHK_CmpCAACanL2cl2_cstcycleopen  TRUE
	#define EXP_CmpCAACanL2cl2_cstcycleopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcycleopen", (RTS_UINTPTR)cl2_cstcycleopen, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_cstcycleopen
	#define EXT_cl2_cstcycleopen
	#define GET_cl2_cstcycleopen(fl)  CAL_CMGETAPI( "cl2_cstcycleopen" ) 
	#define CAL_cl2_cstcycleopen  cl2_cstcycleopen
	#define CHK_cl2_cstcycleopen  TRUE
	#define EXP_cl2_cstcycleopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcycleopen", (RTS_UINTPTR)cl2_cstcycleopen, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_cstcycleopen  PFCL2_CSTCYCLEOPEN_IEC pfcl2_cstcycleopen;
	#define EXT_cl2_cstcycleopen  extern PFCL2_CSTCYCLEOPEN_IEC pfcl2_cstcycleopen;
	#define GET_cl2_cstcycleopen(fl)  s_pfCMGetAPI2( "cl2_cstcycleopen", (RTS_VOID_FCTPTR *)&pfcl2_cstcycleopen, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_cstcycleopen  pfcl2_cstcycleopen
	#define CHK_cl2_cstcycleopen  (pfcl2_cstcycleopen != NULL)
	#define EXP_cl2_cstcycleopen   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_cstcycleopen", (RTS_UINTPTR)cl2_cstcycleopen, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_getreceivecounter</description>
 */
typedef struct tagcl2_getreceivecounter_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_COUNT GetReceiveCounter;		/* VAR_OUTPUT */
} cl2_getreceivecounter_struct;

void CDECL CDECL_EXT cl2_getreceivecounter(cl2_getreceivecounter_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_GETRECEIVECOUNTER_IEC) (cl2_getreceivecounter_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETRECEIVECOUNTER_NOTIMPLEMENTED)
	#define USE_cl2_getreceivecounter
	#define EXT_cl2_getreceivecounter
	#define GET_cl2_getreceivecounter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_getreceivecounter(p0) 
	#define CHK_cl2_getreceivecounter  FALSE
	#define EXP_cl2_getreceivecounter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_getreceivecounter
	#define EXT_cl2_getreceivecounter
	#define GET_cl2_getreceivecounter(fl)  CAL_CMGETAPI( "cl2_getreceivecounter" ) 
	#define CAL_cl2_getreceivecounter  cl2_getreceivecounter
	#define CHK_cl2_getreceivecounter  TRUE
	#define EXP_cl2_getreceivecounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getreceivecounter", (RTS_UINTPTR)cl2_getreceivecounter, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_getreceivecounter
	#define EXT_cl2_getreceivecounter
	#define GET_cl2_getreceivecounter(fl)  CAL_CMGETAPI( "cl2_getreceivecounter" ) 
	#define CAL_cl2_getreceivecounter  cl2_getreceivecounter
	#define CHK_cl2_getreceivecounter  TRUE
	#define EXP_cl2_getreceivecounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getreceivecounter", (RTS_UINTPTR)cl2_getreceivecounter, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_getreceivecounter
	#define EXT_CmpCAACanL2cl2_getreceivecounter
	#define GET_CmpCAACanL2cl2_getreceivecounter  ERR_OK
	#define CAL_CmpCAACanL2cl2_getreceivecounter  cl2_getreceivecounter
	#define CHK_CmpCAACanL2cl2_getreceivecounter  TRUE
	#define EXP_CmpCAACanL2cl2_getreceivecounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getreceivecounter", (RTS_UINTPTR)cl2_getreceivecounter, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_getreceivecounter
	#define EXT_cl2_getreceivecounter
	#define GET_cl2_getreceivecounter(fl)  CAL_CMGETAPI( "cl2_getreceivecounter" ) 
	#define CAL_cl2_getreceivecounter  cl2_getreceivecounter
	#define CHK_cl2_getreceivecounter  TRUE
	#define EXP_cl2_getreceivecounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getreceivecounter", (RTS_UINTPTR)cl2_getreceivecounter, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_getreceivecounter  PFCL2_GETRECEIVECOUNTER_IEC pfcl2_getreceivecounter;
	#define EXT_cl2_getreceivecounter  extern PFCL2_GETRECEIVECOUNTER_IEC pfcl2_getreceivecounter;
	#define GET_cl2_getreceivecounter(fl)  s_pfCMGetAPI2( "cl2_getreceivecounter", (RTS_VOID_FCTPTR *)&pfcl2_getreceivecounter, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_getreceivecounter  pfcl2_getreceivecounter
	#define CHK_cl2_getreceivecounter  (pfcl2_getreceivecounter != NULL)
	#define EXP_cl2_getreceivecounter   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getreceivecounter", (RTS_UINTPTR)cl2_getreceivecounter, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_driveropenh</description>
 */
typedef struct tagcl2_driveropenh_struct
{
	RTS_IEC_USINT usiNetId;				/* VAR_INPUT */
	RTS_IEC_UINT uiBaudrate;			/* VAR_INPUT */
	CAA_BOOL xSupport29Bits;			/* VAR_INPUT */
	CAA_COUNT ctMessages;				/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_HANDLE DriverOpenH;				/* VAR_OUTPUT */
} cl2_driveropenh_struct;

void CDECL CDECL_EXT cl2_driveropenh(cl2_driveropenh_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_DRIVEROPENH_IEC) (cl2_driveropenh_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_DRIVEROPENH_NOTIMPLEMENTED)
	#define USE_cl2_driveropenh
	#define EXT_cl2_driveropenh
	#define GET_cl2_driveropenh(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_driveropenh(p0) 
	#define CHK_cl2_driveropenh  FALSE
	#define EXP_cl2_driveropenh  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_driveropenh
	#define EXT_cl2_driveropenh
	#define GET_cl2_driveropenh(fl)  CAL_CMGETAPI( "cl2_driveropenh" ) 
	#define CAL_cl2_driveropenh  cl2_driveropenh
	#define CHK_cl2_driveropenh  TRUE
	#define EXP_cl2_driveropenh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_driveropenh", (RTS_UINTPTR)cl2_driveropenh, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_driveropenh
	#define EXT_cl2_driveropenh
	#define GET_cl2_driveropenh(fl)  CAL_CMGETAPI( "cl2_driveropenh" ) 
	#define CAL_cl2_driveropenh  cl2_driveropenh
	#define CHK_cl2_driveropenh  TRUE
	#define EXP_cl2_driveropenh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_driveropenh", (RTS_UINTPTR)cl2_driveropenh, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_driveropenh
	#define EXT_CmpCAACanL2cl2_driveropenh
	#define GET_CmpCAACanL2cl2_driveropenh  ERR_OK
	#define CAL_CmpCAACanL2cl2_driveropenh  cl2_driveropenh
	#define CHK_CmpCAACanL2cl2_driveropenh  TRUE
	#define EXP_CmpCAACanL2cl2_driveropenh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_driveropenh", (RTS_UINTPTR)cl2_driveropenh, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_driveropenh
	#define EXT_cl2_driveropenh
	#define GET_cl2_driveropenh(fl)  CAL_CMGETAPI( "cl2_driveropenh" ) 
	#define CAL_cl2_driveropenh  cl2_driveropenh
	#define CHK_cl2_driveropenh  TRUE
	#define EXP_cl2_driveropenh  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_driveropenh", (RTS_UINTPTR)cl2_driveropenh, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_driveropenh  PFCL2_DRIVEROPENH_IEC pfcl2_driveropenh;
	#define EXT_cl2_driveropenh  extern PFCL2_DRIVEROPENH_IEC pfcl2_driveropenh;
	#define GET_cl2_driveropenh(fl)  s_pfCMGetAPI2( "cl2_driveropenh", (RTS_VOID_FCTPTR *)&pfcl2_driveropenh, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_driveropenh  pfcl2_driveropenh
	#define CHK_cl2_driveropenh  (pfcl2_driveropenh != NULL)
	#define EXP_cl2_driveropenh   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_driveropenh", (RTS_UINTPTR)cl2_driveropenh, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_getlostcounter</description>
 */
typedef struct tagcl2_getlostcounter_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_COUNT GetLostCounter;			/* VAR_OUTPUT */
} cl2_getlostcounter_struct;

void CDECL CDECL_EXT cl2_getlostcounter(cl2_getlostcounter_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_GETLOSTCOUNTER_IEC) (cl2_getlostcounter_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETLOSTCOUNTER_NOTIMPLEMENTED)
	#define USE_cl2_getlostcounter
	#define EXT_cl2_getlostcounter
	#define GET_cl2_getlostcounter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_getlostcounter(p0) 
	#define CHK_cl2_getlostcounter  FALSE
	#define EXP_cl2_getlostcounter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_getlostcounter
	#define EXT_cl2_getlostcounter
	#define GET_cl2_getlostcounter(fl)  CAL_CMGETAPI( "cl2_getlostcounter" ) 
	#define CAL_cl2_getlostcounter  cl2_getlostcounter
	#define CHK_cl2_getlostcounter  TRUE
	#define EXP_cl2_getlostcounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getlostcounter", (RTS_UINTPTR)cl2_getlostcounter, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_getlostcounter
	#define EXT_cl2_getlostcounter
	#define GET_cl2_getlostcounter(fl)  CAL_CMGETAPI( "cl2_getlostcounter" ) 
	#define CAL_cl2_getlostcounter  cl2_getlostcounter
	#define CHK_cl2_getlostcounter  TRUE
	#define EXP_cl2_getlostcounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getlostcounter", (RTS_UINTPTR)cl2_getlostcounter, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_getlostcounter
	#define EXT_CmpCAACanL2cl2_getlostcounter
	#define GET_CmpCAACanL2cl2_getlostcounter  ERR_OK
	#define CAL_CmpCAACanL2cl2_getlostcounter  cl2_getlostcounter
	#define CHK_CmpCAACanL2cl2_getlostcounter  TRUE
	#define EXP_CmpCAACanL2cl2_getlostcounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getlostcounter", (RTS_UINTPTR)cl2_getlostcounter, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_getlostcounter
	#define EXT_cl2_getlostcounter
	#define GET_cl2_getlostcounter(fl)  CAL_CMGETAPI( "cl2_getlostcounter" ) 
	#define CAL_cl2_getlostcounter  cl2_getlostcounter
	#define CHK_cl2_getlostcounter  TRUE
	#define EXP_cl2_getlostcounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getlostcounter", (RTS_UINTPTR)cl2_getlostcounter, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_getlostcounter  PFCL2_GETLOSTCOUNTER_IEC pfcl2_getlostcounter;
	#define EXT_cl2_getlostcounter  extern PFCL2_GETLOSTCOUNTER_IEC pfcl2_getlostcounter;
	#define GET_cl2_getlostcounter(fl)  s_pfCMGetAPI2( "cl2_getlostcounter", (RTS_VOID_FCTPTR *)&pfcl2_getlostcounter, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_getlostcounter  pfcl2_getlostcounter
	#define CHK_cl2_getlostcounter  (pfcl2_getlostcounter != NULL)
	#define EXP_cl2_getlostcounter   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getlostcounter", (RTS_UINTPTR)cl2_getlostcounter, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_getbusalarm</description>
 */
typedef struct tagcl2_getbusalarm_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_BOOL GetBusAlarm;				/* VAR_OUTPUT */
} cl2_getbusalarm_struct;

void CDECL CDECL_EXT cl2_getbusalarm(cl2_getbusalarm_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_GETBUSALARM_IEC) (cl2_getbusalarm_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETBUSALARM_NOTIMPLEMENTED)
	#define USE_cl2_getbusalarm
	#define EXT_cl2_getbusalarm
	#define GET_cl2_getbusalarm(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_getbusalarm(p0) 
	#define CHK_cl2_getbusalarm  FALSE
	#define EXP_cl2_getbusalarm  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_getbusalarm
	#define EXT_cl2_getbusalarm
	#define GET_cl2_getbusalarm(fl)  CAL_CMGETAPI( "cl2_getbusalarm" ) 
	#define CAL_cl2_getbusalarm  cl2_getbusalarm
	#define CHK_cl2_getbusalarm  TRUE
	#define EXP_cl2_getbusalarm  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getbusalarm", (RTS_UINTPTR)cl2_getbusalarm, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_getbusalarm
	#define EXT_cl2_getbusalarm
	#define GET_cl2_getbusalarm(fl)  CAL_CMGETAPI( "cl2_getbusalarm" ) 
	#define CAL_cl2_getbusalarm  cl2_getbusalarm
	#define CHK_cl2_getbusalarm  TRUE
	#define EXP_cl2_getbusalarm  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getbusalarm", (RTS_UINTPTR)cl2_getbusalarm, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_getbusalarm
	#define EXT_CmpCAACanL2cl2_getbusalarm
	#define GET_CmpCAACanL2cl2_getbusalarm  ERR_OK
	#define CAL_CmpCAACanL2cl2_getbusalarm  cl2_getbusalarm
	#define CHK_CmpCAACanL2cl2_getbusalarm  TRUE
	#define EXP_CmpCAACanL2cl2_getbusalarm  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getbusalarm", (RTS_UINTPTR)cl2_getbusalarm, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_getbusalarm
	#define EXT_cl2_getbusalarm
	#define GET_cl2_getbusalarm(fl)  CAL_CMGETAPI( "cl2_getbusalarm" ) 
	#define CAL_cl2_getbusalarm  cl2_getbusalarm
	#define CHK_cl2_getbusalarm  TRUE
	#define EXP_cl2_getbusalarm  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getbusalarm", (RTS_UINTPTR)cl2_getbusalarm, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_getbusalarm  PFCL2_GETBUSALARM_IEC pfcl2_getbusalarm;
	#define EXT_cl2_getbusalarm  extern PFCL2_GETBUSALARM_IEC pfcl2_getbusalarm;
	#define GET_cl2_getbusalarm(fl)  s_pfCMGetAPI2( "cl2_getbusalarm", (RTS_VOID_FCTPTR *)&pfcl2_getbusalarm, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_getbusalarm  pfcl2_getbusalarm
	#define CHK_cl2_getbusalarm  (pfcl2_getbusalarm != NULL)
	#define EXP_cl2_getbusalarm   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getbusalarm", (RTS_UINTPTR)cl2_getbusalarm, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_getreceiveerrorcounter</description>
 */
typedef struct tagcl2_getreceiveerrorcounter_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR *peError;					/* VAR_INPUT */
	CAA_COUNT GetReceiveErrorCounter;	/* VAR_OUTPUT */
} cl2_getreceiveerrorcounter_struct;

void CDECL CDECL_EXT cl2_getreceiveerrorcounter(cl2_getreceiveerrorcounter_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_GETRECEIVEERRORCOUNTER_IEC) (cl2_getreceiveerrorcounter_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETRECEIVEERRORCOUNTER_NOTIMPLEMENTED)
	#define USE_cl2_getreceiveerrorcounter
	#define EXT_cl2_getreceiveerrorcounter
	#define GET_cl2_getreceiveerrorcounter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_getreceiveerrorcounter(p0) 
	#define CHK_cl2_getreceiveerrorcounter  FALSE
	#define EXP_cl2_getreceiveerrorcounter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_getreceiveerrorcounter
	#define EXT_cl2_getreceiveerrorcounter
	#define GET_cl2_getreceiveerrorcounter(fl)  CAL_CMGETAPI( "cl2_getreceiveerrorcounter" ) 
	#define CAL_cl2_getreceiveerrorcounter  cl2_getreceiveerrorcounter
	#define CHK_cl2_getreceiveerrorcounter  TRUE
	#define EXP_cl2_getreceiveerrorcounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getreceiveerrorcounter", (RTS_UINTPTR)cl2_getreceiveerrorcounter, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_getreceiveerrorcounter
	#define EXT_cl2_getreceiveerrorcounter
	#define GET_cl2_getreceiveerrorcounter(fl)  CAL_CMGETAPI( "cl2_getreceiveerrorcounter" ) 
	#define CAL_cl2_getreceiveerrorcounter  cl2_getreceiveerrorcounter
	#define CHK_cl2_getreceiveerrorcounter  TRUE
	#define EXP_cl2_getreceiveerrorcounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getreceiveerrorcounter", (RTS_UINTPTR)cl2_getreceiveerrorcounter, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_getreceiveerrorcounter
	#define EXT_CmpCAACanL2cl2_getreceiveerrorcounter
	#define GET_CmpCAACanL2cl2_getreceiveerrorcounter  ERR_OK
	#define CAL_CmpCAACanL2cl2_getreceiveerrorcounter  cl2_getreceiveerrorcounter
	#define CHK_CmpCAACanL2cl2_getreceiveerrorcounter  TRUE
	#define EXP_CmpCAACanL2cl2_getreceiveerrorcounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getreceiveerrorcounter", (RTS_UINTPTR)cl2_getreceiveerrorcounter, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_getreceiveerrorcounter
	#define EXT_cl2_getreceiveerrorcounter
	#define GET_cl2_getreceiveerrorcounter(fl)  CAL_CMGETAPI( "cl2_getreceiveerrorcounter" ) 
	#define CAL_cl2_getreceiveerrorcounter  cl2_getreceiveerrorcounter
	#define CHK_cl2_getreceiveerrorcounter  TRUE
	#define EXP_cl2_getreceiveerrorcounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getreceiveerrorcounter", (RTS_UINTPTR)cl2_getreceiveerrorcounter, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_getreceiveerrorcounter  PFCL2_GETRECEIVEERRORCOUNTER_IEC pfcl2_getreceiveerrorcounter;
	#define EXT_cl2_getreceiveerrorcounter  extern PFCL2_GETRECEIVEERRORCOUNTER_IEC pfcl2_getreceiveerrorcounter;
	#define GET_cl2_getreceiveerrorcounter(fl)  s_pfCMGetAPI2( "cl2_getreceiveerrorcounter", (RTS_VOID_FCTPTR *)&pfcl2_getreceiveerrorcounter, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_getreceiveerrorcounter  pfcl2_getreceiveerrorcounter
	#define CHK_cl2_getreceiveerrorcounter  (pfcl2_getreceiveerrorcounter != NULL)
	#define EXP_cl2_getreceiveerrorcounter   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getreceiveerrorcounter", (RTS_UINTPTR)cl2_getreceiveerrorcounter, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_gettransmiterrorcounter</description>
 */
typedef struct tagcl2_gettransmiterrorcounter_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	CAA_COUNT GetTransmitErrorCounter;	/* VAR_OUTPUT */
} cl2_gettransmiterrorcounter_struct;

void CDECL CDECL_EXT cl2_gettransmiterrorcounter(cl2_gettransmiterrorcounter_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_GETTRANSMITERRORCOUNTER_IEC) (cl2_gettransmiterrorcounter_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETTRANSMITERRORCOUNTER_NOTIMPLEMENTED)
	#define USE_cl2_gettransmiterrorcounter
	#define EXT_cl2_gettransmiterrorcounter
	#define GET_cl2_gettransmiterrorcounter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_gettransmiterrorcounter(p0) 
	#define CHK_cl2_gettransmiterrorcounter  FALSE
	#define EXP_cl2_gettransmiterrorcounter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_gettransmiterrorcounter
	#define EXT_cl2_gettransmiterrorcounter
	#define GET_cl2_gettransmiterrorcounter(fl)  CAL_CMGETAPI( "cl2_gettransmiterrorcounter" ) 
	#define CAL_cl2_gettransmiterrorcounter  cl2_gettransmiterrorcounter
	#define CHK_cl2_gettransmiterrorcounter  TRUE
	#define EXP_cl2_gettransmiterrorcounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettransmiterrorcounter", (RTS_UINTPTR)cl2_gettransmiterrorcounter, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_gettransmiterrorcounter
	#define EXT_cl2_gettransmiterrorcounter
	#define GET_cl2_gettransmiterrorcounter(fl)  CAL_CMGETAPI( "cl2_gettransmiterrorcounter" ) 
	#define CAL_cl2_gettransmiterrorcounter  cl2_gettransmiterrorcounter
	#define CHK_cl2_gettransmiterrorcounter  TRUE
	#define EXP_cl2_gettransmiterrorcounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettransmiterrorcounter", (RTS_UINTPTR)cl2_gettransmiterrorcounter, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_gettransmiterrorcounter
	#define EXT_CmpCAACanL2cl2_gettransmiterrorcounter
	#define GET_CmpCAACanL2cl2_gettransmiterrorcounter  ERR_OK
	#define CAL_CmpCAACanL2cl2_gettransmiterrorcounter  cl2_gettransmiterrorcounter
	#define CHK_CmpCAACanL2cl2_gettransmiterrorcounter  TRUE
	#define EXP_CmpCAACanL2cl2_gettransmiterrorcounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettransmiterrorcounter", (RTS_UINTPTR)cl2_gettransmiterrorcounter, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_gettransmiterrorcounter
	#define EXT_cl2_gettransmiterrorcounter
	#define GET_cl2_gettransmiterrorcounter(fl)  CAL_CMGETAPI( "cl2_gettransmiterrorcounter" ) 
	#define CAL_cl2_gettransmiterrorcounter  cl2_gettransmiterrorcounter
	#define CHK_cl2_gettransmiterrorcounter  TRUE
	#define EXP_cl2_gettransmiterrorcounter  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettransmiterrorcounter", (RTS_UINTPTR)cl2_gettransmiterrorcounter, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_gettransmiterrorcounter  PFCL2_GETTRANSMITERRORCOUNTER_IEC pfcl2_gettransmiterrorcounter;
	#define EXT_cl2_gettransmiterrorcounter  extern PFCL2_GETTRANSMITERRORCOUNTER_IEC pfcl2_gettransmiterrorcounter;
	#define GET_cl2_gettransmiterrorcounter(fl)  s_pfCMGetAPI2( "cl2_gettransmiterrorcounter", (RTS_VOID_FCTPTR *)&pfcl2_gettransmiterrorcounter, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_gettransmiterrorcounter  pfcl2_gettransmiterrorcounter
	#define CHK_cl2_gettransmiterrorcounter  (pfcl2_gettransmiterrorcounter != NULL)
	#define EXP_cl2_gettransmiterrorcounter   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettransmiterrorcounter", (RTS_UINTPTR)cl2_gettransmiterrorcounter, 1, 0x0, 0x0) 
#endif


/**
 * <description>cl2_resetbusalarm</description>
 */
typedef struct tagcl2_resetbusalarm_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR ResetBusAlarm;			/* VAR_OUTPUT */
} cl2_resetbusalarm_struct;

void CDECL CDECL_EXT cl2_resetbusalarm(cl2_resetbusalarm_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_RESETBUSALARM_IEC) (cl2_resetbusalarm_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_RESETBUSALARM_NOTIMPLEMENTED)
	#define USE_cl2_resetbusalarm
	#define EXT_cl2_resetbusalarm
	#define GET_cl2_resetbusalarm(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_resetbusalarm(p0) 
	#define CHK_cl2_resetbusalarm  FALSE
	#define EXP_cl2_resetbusalarm  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_resetbusalarm
	#define EXT_cl2_resetbusalarm
	#define GET_cl2_resetbusalarm(fl)  CAL_CMGETAPI( "cl2_resetbusalarm" ) 
	#define CAL_cl2_resetbusalarm  cl2_resetbusalarm
	#define CHK_cl2_resetbusalarm  TRUE
	#define EXP_cl2_resetbusalarm  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_resetbusalarm", (RTS_UINTPTR)cl2_resetbusalarm, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_resetbusalarm
	#define EXT_cl2_resetbusalarm
	#define GET_cl2_resetbusalarm(fl)  CAL_CMGETAPI( "cl2_resetbusalarm" ) 
	#define CAL_cl2_resetbusalarm  cl2_resetbusalarm
	#define CHK_cl2_resetbusalarm  TRUE
	#define EXP_cl2_resetbusalarm  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_resetbusalarm", (RTS_UINTPTR)cl2_resetbusalarm, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_resetbusalarm
	#define EXT_CmpCAACanL2cl2_resetbusalarm
	#define GET_CmpCAACanL2cl2_resetbusalarm  ERR_OK
	#define CAL_CmpCAACanL2cl2_resetbusalarm  cl2_resetbusalarm
	#define CHK_CmpCAACanL2cl2_resetbusalarm  TRUE
	#define EXP_CmpCAACanL2cl2_resetbusalarm  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_resetbusalarm", (RTS_UINTPTR)cl2_resetbusalarm, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_resetbusalarm
	#define EXT_cl2_resetbusalarm
	#define GET_cl2_resetbusalarm(fl)  CAL_CMGETAPI( "cl2_resetbusalarm" ) 
	#define CAL_cl2_resetbusalarm  cl2_resetbusalarm
	#define CHK_cl2_resetbusalarm  TRUE
	#define EXP_cl2_resetbusalarm  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_resetbusalarm", (RTS_UINTPTR)cl2_resetbusalarm, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_resetbusalarm  PFCL2_RESETBUSALARM_IEC pfcl2_resetbusalarm;
	#define EXT_cl2_resetbusalarm  extern PFCL2_RESETBUSALARM_IEC pfcl2_resetbusalarm;
	#define GET_cl2_resetbusalarm(fl)  s_pfCMGetAPI2( "cl2_resetbusalarm", (RTS_VOID_FCTPTR *)&pfcl2_resetbusalarm, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_resetbusalarm  pfcl2_resetbusalarm
	#define CHK_cl2_resetbusalarm  (pfcl2_resetbusalarm != NULL)
	#define EXP_cl2_resetbusalarm   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_resetbusalarm", (RTS_UINTPTR)cl2_resetbusalarm, 1, 0x0, 0x0) 
#endif


typedef struct tagcl2_getciastate_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
	unsigned char GetCiAState;			/* VAR_OUTPUT */
} cl2_getciastate_struct;

void CDECL CDECL_EXT cl2_getciastate(cl2_getciastate_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_GETCIASTATE_IEC) (cl2_getciastate_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETCIASTATE_NOTIMPLEMENTED)
	#define USE_cl2_getciastate
	#define EXT_cl2_getciastate
	#define GET_cl2_getciastate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_getciastate(p0) 
	#define CHK_cl2_getciastate  FALSE
	#define EXP_cl2_getciastate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_getciastate
	#define EXT_cl2_getciastate
	#define GET_cl2_getciastate(fl)  CAL_CMGETAPI( "cl2_getciastate" ) 
	#define CAL_cl2_getciastate  cl2_getciastate
	#define CHK_cl2_getciastate  TRUE
	#define EXP_cl2_getciastate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getciastate", (RTS_UINTPTR)cl2_getciastate, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_getciastate
	#define EXT_cl2_getciastate
	#define GET_cl2_getciastate(fl)  CAL_CMGETAPI( "cl2_getciastate" ) 
	#define CAL_cl2_getciastate  cl2_getciastate
	#define CHK_cl2_getciastate  TRUE
	#define EXP_cl2_getciastate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getciastate", (RTS_UINTPTR)cl2_getciastate, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_getciastate
	#define EXT_CmpCAACanL2cl2_getciastate
	#define GET_CmpCAACanL2cl2_getciastate  ERR_OK
	#define CAL_CmpCAACanL2cl2_getciastate  cl2_getciastate
	#define CHK_CmpCAACanL2cl2_getciastate  TRUE
	#define EXP_CmpCAACanL2cl2_getciastate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getciastate", (RTS_UINTPTR)cl2_getciastate, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_getciastate
	#define EXT_cl2_getciastate
	#define GET_cl2_getciastate(fl)  CAL_CMGETAPI( "cl2_getciastate" ) 
	#define CAL_cl2_getciastate  cl2_getciastate
	#define CHK_cl2_getciastate  TRUE
	#define EXP_cl2_getciastate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getciastate", (RTS_UINTPTR)cl2_getciastate, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_getciastate  PFCL2_GETCIASTATE_IEC pfcl2_getciastate;
	#define EXT_cl2_getciastate  extern PFCL2_GETCIASTATE_IEC pfcl2_getciastate;
	#define GET_cl2_getciastate(fl)  s_pfCMGetAPI2( "cl2_getciastate", (RTS_VOID_FCTPTR *)&pfcl2_getciastate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_getciastate  pfcl2_getciastate
	#define CHK_cl2_getciastate  (pfcl2_getciastate != NULL)
	#define EXP_cl2_getciastate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getciastate", (RTS_UINTPTR)cl2_getciastate, 1, 0x0, 0x0) 
#endif


typedef struct tagcl2_setciastate_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	unsigned char byState;				/* VAR_INPUT */
    CAA_ERROR SetCiAState;			    /* VAR_OUTPUT */
} cl2_setciastate_struct;

void CDECL CDECL_EXT cl2_setciastate(cl2_setciastate_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_SETCIASTATE_IEC) (cl2_setciastate_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_SETCIASTATE_NOTIMPLEMENTED)
	#define USE_cl2_setciastate
	#define EXT_cl2_setciastate
	#define GET_cl2_setciastate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_setciastate(p0) 
	#define CHK_cl2_setciastate  FALSE
	#define EXP_cl2_setciastate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_setciastate
	#define EXT_cl2_setciastate
	#define GET_cl2_setciastate(fl)  CAL_CMGETAPI( "cl2_setciastate" ) 
	#define CAL_cl2_setciastate  cl2_setciastate
	#define CHK_cl2_setciastate  TRUE
	#define EXP_cl2_setciastate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_setciastate", (RTS_UINTPTR)cl2_setciastate, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_setciastate
	#define EXT_cl2_setciastate
	#define GET_cl2_setciastate(fl)  CAL_CMGETAPI( "cl2_setciastate" ) 
	#define CAL_cl2_setciastate  cl2_setciastate
	#define CHK_cl2_setciastate  TRUE
	#define EXP_cl2_setciastate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_setciastate", (RTS_UINTPTR)cl2_setciastate, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_setciastate
	#define EXT_CmpCAACanL2cl2_setciastate
	#define GET_CmpCAACanL2cl2_setciastate  ERR_OK
	#define CAL_CmpCAACanL2cl2_setciastate  cl2_setciastate
	#define CHK_CmpCAACanL2cl2_setciastate  TRUE
	#define EXP_CmpCAACanL2cl2_setciastate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_setciastate", (RTS_UINTPTR)cl2_setciastate, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_setciastate
	#define EXT_cl2_setciastate
	#define GET_cl2_setciastate(fl)  CAL_CMGETAPI( "cl2_setciastate" ) 
	#define CAL_cl2_setciastate  cl2_setciastate
	#define CHK_cl2_setciastate  TRUE
	#define EXP_cl2_setciastate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_setciastate", (RTS_UINTPTR)cl2_setciastate, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_setciastate  PFCL2_SETCIASTATE_IEC pfcl2_setciastate;
	#define EXT_cl2_setciastate  extern PFCL2_SETCIASTATE_IEC pfcl2_setciastate;
	#define GET_cl2_setciastate(fl)  s_pfCMGetAPI2( "cl2_setciastate", (RTS_VOID_FCTPTR *)&pfcl2_setciastate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_setciastate  pfcl2_setciastate
	#define CHK_cl2_setciastate  (pfcl2_setciastate != NULL)
	#define EXP_cl2_setciastate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_setciastate", (RTS_UINTPTR)cl2_setciastate, 1, 0x0, 0x0) 
#endif


typedef struct tagcl2_gettransmitqueuelength_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
    CAA_COUNT GetTransmitQueueLength;   /* VAR_OUTPUT */
} cl2_gettransmitqueuelength_struct;

void CDECL CDECL_EXT cl2_gettransmitqueuelength(cl2_gettransmitqueuelength_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_GETTRANSMITQUEUELENGTH_IEC) (cl2_gettransmitqueuelength_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETTRANSMITQUEUELENGTH_NOTIMPLEMENTED)
	#define USE_cl2_gettransmitqueuelength
	#define EXT_cl2_gettransmitqueuelength
	#define GET_cl2_gettransmitqueuelength(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_gettransmitqueuelength(p0) 
	#define CHK_cl2_gettransmitqueuelength  FALSE
	#define EXP_cl2_gettransmitqueuelength  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_gettransmitqueuelength
	#define EXT_cl2_gettransmitqueuelength
	#define GET_cl2_gettransmitqueuelength(fl)  CAL_CMGETAPI( "cl2_gettransmitqueuelength" ) 
	#define CAL_cl2_gettransmitqueuelength  cl2_gettransmitqueuelength
	#define CHK_cl2_gettransmitqueuelength  TRUE
	#define EXP_cl2_gettransmitqueuelength  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettransmitqueuelength", (RTS_UINTPTR)cl2_gettransmitqueuelength, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_gettransmitqueuelength
	#define EXT_cl2_gettransmitqueuelength
	#define GET_cl2_gettransmitqueuelength(fl)  CAL_CMGETAPI( "cl2_gettransmitqueuelength" ) 
	#define CAL_cl2_gettransmitqueuelength  cl2_gettransmitqueuelength
	#define CHK_cl2_gettransmitqueuelength  TRUE
	#define EXP_cl2_gettransmitqueuelength  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettransmitqueuelength", (RTS_UINTPTR)cl2_gettransmitqueuelength, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_gettransmitqueuelength
	#define EXT_CmpCAACanL2cl2_gettransmitqueuelength
	#define GET_CmpCAACanL2cl2_gettransmitqueuelength  ERR_OK
	#define CAL_CmpCAACanL2cl2_gettransmitqueuelength  cl2_gettransmitqueuelength
	#define CHK_CmpCAACanL2cl2_gettransmitqueuelength  TRUE
	#define EXP_CmpCAACanL2cl2_gettransmitqueuelength  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettransmitqueuelength", (RTS_UINTPTR)cl2_gettransmitqueuelength, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_gettransmitqueuelength
	#define EXT_cl2_gettransmitqueuelength
	#define GET_cl2_gettransmitqueuelength(fl)  CAL_CMGETAPI( "cl2_gettransmitqueuelength" ) 
	#define CAL_cl2_gettransmitqueuelength  cl2_gettransmitqueuelength
	#define CHK_cl2_gettransmitqueuelength  TRUE
	#define EXP_cl2_gettransmitqueuelength  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettransmitqueuelength", (RTS_UINTPTR)cl2_gettransmitqueuelength, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_gettransmitqueuelength  PFCL2_GETTRANSMITQUEUELENGTH_IEC pfcl2_gettransmitqueuelength;
	#define EXT_cl2_gettransmitqueuelength  extern PFCL2_GETTRANSMITQUEUELENGTH_IEC pfcl2_gettransmitqueuelength;
	#define GET_cl2_gettransmitqueuelength(fl)  s_pfCMGetAPI2( "cl2_gettransmitqueuelength", (RTS_VOID_FCTPTR *)&pfcl2_gettransmitqueuelength, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_gettransmitqueuelength  pfcl2_gettransmitqueuelength
	#define CHK_cl2_gettransmitqueuelength  (pfcl2_gettransmitqueuelength != NULL)
	#define EXP_cl2_gettransmitqueuelength   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettransmitqueuelength", (RTS_UINTPTR)cl2_gettransmitqueuelength, 1, 0x0, 0x0) 
#endif


typedef struct tagcl2_getreceivequeuelength_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
    CAA_COUNT GetReceiveQueueLength;    /* VAR_OUTPUT */
} cl2_getreceivequeuelength_struct;

void CDECL CDECL_EXT cl2_getreceivequeuelength(cl2_getreceivequeuelength_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_GETRECEIVEQUEUELENGTH_IEC) (cl2_getreceivequeuelength_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETRECEIVEQUEUELENGTH_NOTIMPLEMENTED)
	#define USE_cl2_getreceivequeuelength
	#define EXT_cl2_getreceivequeuelength
	#define GET_cl2_getreceivequeuelength(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_getreceivequeuelength(p0) 
	#define CHK_cl2_getreceivequeuelength  FALSE
	#define EXP_cl2_getreceivequeuelength  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_getreceivequeuelength
	#define EXT_cl2_getreceivequeuelength
	#define GET_cl2_getreceivequeuelength(fl)  CAL_CMGETAPI( "cl2_getreceivequeuelength" ) 
	#define CAL_cl2_getreceivequeuelength  cl2_getreceivequeuelength
	#define CHK_cl2_getreceivequeuelength  TRUE
	#define EXP_cl2_getreceivequeuelength  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getreceivequeuelength", (RTS_UINTPTR)cl2_getreceivequeuelength, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_getreceivequeuelength
	#define EXT_cl2_getreceivequeuelength
	#define GET_cl2_getreceivequeuelength(fl)  CAL_CMGETAPI( "cl2_getreceivequeuelength" ) 
	#define CAL_cl2_getreceivequeuelength  cl2_getreceivequeuelength
	#define CHK_cl2_getreceivequeuelength  TRUE
	#define EXP_cl2_getreceivequeuelength  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getreceivequeuelength", (RTS_UINTPTR)cl2_getreceivequeuelength, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_getreceivequeuelength
	#define EXT_CmpCAACanL2cl2_getreceivequeuelength
	#define GET_CmpCAACanL2cl2_getreceivequeuelength  ERR_OK
	#define CAL_CmpCAACanL2cl2_getreceivequeuelength  cl2_getreceivequeuelength
	#define CHK_CmpCAACanL2cl2_getreceivequeuelength  TRUE
	#define EXP_CmpCAACanL2cl2_getreceivequeuelength  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getreceivequeuelength", (RTS_UINTPTR)cl2_getreceivequeuelength, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_getreceivequeuelength
	#define EXT_cl2_getreceivequeuelength
	#define GET_cl2_getreceivequeuelength(fl)  CAL_CMGETAPI( "cl2_getreceivequeuelength" ) 
	#define CAL_cl2_getreceivequeuelength  cl2_getreceivequeuelength
	#define CHK_cl2_getreceivequeuelength  TRUE
	#define EXP_cl2_getreceivequeuelength  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getreceivequeuelength", (RTS_UINTPTR)cl2_getreceivequeuelength, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_getreceivequeuelength  PFCL2_GETRECEIVEQUEUELENGTH_IEC pfcl2_getreceivequeuelength;
	#define EXT_cl2_getreceivequeuelength  extern PFCL2_GETRECEIVEQUEUELENGTH_IEC pfcl2_getreceivequeuelength;
	#define GET_cl2_getreceivequeuelength(fl)  s_pfCMGetAPI2( "cl2_getreceivequeuelength", (RTS_VOID_FCTPTR *)&pfcl2_getreceivequeuelength, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_getreceivequeuelength  pfcl2_getreceivequeuelength
	#define CHK_cl2_getreceivequeuelength  (pfcl2_getreceivequeuelength != NULL)
	#define EXP_cl2_getreceivequeuelength   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getreceivequeuelength", (RTS_UINTPTR)cl2_getreceivequeuelength, 1, 0x0, 0x0) 
#endif


typedef struct tagcl2_gettransmitpoolsize_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
    CAA_COUNT GetTransmitPoolSize;      /* VAR_OUTPUT */
} cl2_gettransmitpoolsize_struct;

void CDECL CDECL_EXT cl2_gettransmitpoolsize(cl2_gettransmitpoolsize_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_GETTRANSMITPOOLSIZE_IEC) (cl2_gettransmitpoolsize_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETTRANSMITPOOLSIZE_NOTIMPLEMENTED)
	#define USE_cl2_gettransmitpoolsize
	#define EXT_cl2_gettransmitpoolsize
	#define GET_cl2_gettransmitpoolsize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_gettransmitpoolsize(p0) 
	#define CHK_cl2_gettransmitpoolsize  FALSE
	#define EXP_cl2_gettransmitpoolsize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_gettransmitpoolsize
	#define EXT_cl2_gettransmitpoolsize
	#define GET_cl2_gettransmitpoolsize(fl)  CAL_CMGETAPI( "cl2_gettransmitpoolsize" ) 
	#define CAL_cl2_gettransmitpoolsize  cl2_gettransmitpoolsize
	#define CHK_cl2_gettransmitpoolsize  TRUE
	#define EXP_cl2_gettransmitpoolsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettransmitpoolsize", (RTS_UINTPTR)cl2_gettransmitpoolsize, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_gettransmitpoolsize
	#define EXT_cl2_gettransmitpoolsize
	#define GET_cl2_gettransmitpoolsize(fl)  CAL_CMGETAPI( "cl2_gettransmitpoolsize" ) 
	#define CAL_cl2_gettransmitpoolsize  cl2_gettransmitpoolsize
	#define CHK_cl2_gettransmitpoolsize  TRUE
	#define EXP_cl2_gettransmitpoolsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettransmitpoolsize", (RTS_UINTPTR)cl2_gettransmitpoolsize, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_gettransmitpoolsize
	#define EXT_CmpCAACanL2cl2_gettransmitpoolsize
	#define GET_CmpCAACanL2cl2_gettransmitpoolsize  ERR_OK
	#define CAL_CmpCAACanL2cl2_gettransmitpoolsize  cl2_gettransmitpoolsize
	#define CHK_CmpCAACanL2cl2_gettransmitpoolsize  TRUE
	#define EXP_CmpCAACanL2cl2_gettransmitpoolsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettransmitpoolsize", (RTS_UINTPTR)cl2_gettransmitpoolsize, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_gettransmitpoolsize
	#define EXT_cl2_gettransmitpoolsize
	#define GET_cl2_gettransmitpoolsize(fl)  CAL_CMGETAPI( "cl2_gettransmitpoolsize" ) 
	#define CAL_cl2_gettransmitpoolsize  cl2_gettransmitpoolsize
	#define CHK_cl2_gettransmitpoolsize  TRUE
	#define EXP_cl2_gettransmitpoolsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettransmitpoolsize", (RTS_UINTPTR)cl2_gettransmitpoolsize, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_gettransmitpoolsize  PFCL2_GETTRANSMITPOOLSIZE_IEC pfcl2_gettransmitpoolsize;
	#define EXT_cl2_gettransmitpoolsize  extern PFCL2_GETTRANSMITPOOLSIZE_IEC pfcl2_gettransmitpoolsize;
	#define GET_cl2_gettransmitpoolsize(fl)  s_pfCMGetAPI2( "cl2_gettransmitpoolsize", (RTS_VOID_FCTPTR *)&pfcl2_gettransmitpoolsize, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_gettransmitpoolsize  pfcl2_gettransmitpoolsize
	#define CHK_cl2_gettransmitpoolsize  (pfcl2_gettransmitpoolsize != NULL)
	#define EXP_cl2_gettransmitpoolsize   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_gettransmitpoolsize", (RTS_UINTPTR)cl2_gettransmitpoolsize, 1, 0x0, 0x0) 
#endif


typedef struct tagcl2_getreceivepoolsize_struct
{
	CAA_HANDLE hDriver;					/* VAR_INPUT */
	CAA_ERROR* peError;					/* VAR_INPUT */
    CAA_COUNT GetReceivePoolSize;       /* VAR_OUTPUT */
} cl2_getreceivepoolsize_struct;

void CDECL CDECL_EXT cl2_getreceivepoolsize(cl2_getreceivepoolsize_struct *p);
typedef void (CDECL CDECL_EXT* PFCL2_GETRECEIVEPOOLSIZE_IEC) (cl2_getreceivepoolsize_struct *p);
#if defined(CMPCAACANL2_NOTIMPLEMENTED) || defined(CL2_GETRECEIVEPOOLSIZE_NOTIMPLEMENTED)
	#define USE_cl2_getreceivepoolsize
	#define EXT_cl2_getreceivepoolsize
	#define GET_cl2_getreceivepoolsize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_cl2_getreceivepoolsize(p0) 
	#define CHK_cl2_getreceivepoolsize  FALSE
	#define EXP_cl2_getreceivepoolsize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_cl2_getreceivepoolsize
	#define EXT_cl2_getreceivepoolsize
	#define GET_cl2_getreceivepoolsize(fl)  CAL_CMGETAPI( "cl2_getreceivepoolsize" ) 
	#define CAL_cl2_getreceivepoolsize  cl2_getreceivepoolsize
	#define CHK_cl2_getreceivepoolsize  TRUE
	#define EXP_cl2_getreceivepoolsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getreceivepoolsize", (RTS_UINTPTR)cl2_getreceivepoolsize, 1, 0x0, 0x0) 
#elif defined(MIXED_LINK) && !defined(CMPCAACANL2_EXTERNAL)
	#define USE_cl2_getreceivepoolsize
	#define EXT_cl2_getreceivepoolsize
	#define GET_cl2_getreceivepoolsize(fl)  CAL_CMGETAPI( "cl2_getreceivepoolsize" ) 
	#define CAL_cl2_getreceivepoolsize  cl2_getreceivepoolsize
	#define CHK_cl2_getreceivepoolsize  TRUE
	#define EXP_cl2_getreceivepoolsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getreceivepoolsize", (RTS_UINTPTR)cl2_getreceivepoolsize, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAACanL2cl2_getreceivepoolsize
	#define EXT_CmpCAACanL2cl2_getreceivepoolsize
	#define GET_CmpCAACanL2cl2_getreceivepoolsize  ERR_OK
	#define CAL_CmpCAACanL2cl2_getreceivepoolsize  cl2_getreceivepoolsize
	#define CHK_CmpCAACanL2cl2_getreceivepoolsize  TRUE
	#define EXP_CmpCAACanL2cl2_getreceivepoolsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getreceivepoolsize", (RTS_UINTPTR)cl2_getreceivepoolsize, 1, 0x0, 0x0) 
#elif defined(CPLUSPLUS)
	#define USE_cl2_getreceivepoolsize
	#define EXT_cl2_getreceivepoolsize
	#define GET_cl2_getreceivepoolsize(fl)  CAL_CMGETAPI( "cl2_getreceivepoolsize" ) 
	#define CAL_cl2_getreceivepoolsize  cl2_getreceivepoolsize
	#define CHK_cl2_getreceivepoolsize  TRUE
	#define EXP_cl2_getreceivepoolsize  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getreceivepoolsize", (RTS_UINTPTR)cl2_getreceivepoolsize, 1, 0x0, 0x0) 
#else /* DYNAMIC_LINK */
	#define USE_cl2_getreceivepoolsize  PFCL2_GETRECEIVEPOOLSIZE_IEC pfcl2_getreceivepoolsize;
	#define EXT_cl2_getreceivepoolsize  extern PFCL2_GETRECEIVEPOOLSIZE_IEC pfcl2_getreceivepoolsize;
	#define GET_cl2_getreceivepoolsize(fl)  s_pfCMGetAPI2( "cl2_getreceivepoolsize", (RTS_VOID_FCTPTR *)&pfcl2_getreceivepoolsize, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0, 0x0)
	#define CAL_cl2_getreceivepoolsize  pfcl2_getreceivepoolsize
	#define CHK_cl2_getreceivepoolsize  (pfcl2_getreceivepoolsize != NULL)
	#define EXP_cl2_getreceivepoolsize   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"cl2_getreceivepoolsize", (RTS_UINTPTR)cl2_getreceivepoolsize, 1, 0x0, 0x0) 
#endif


#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFCL2_DRIVEROPENH ICL2_DriverOpenH;
 	PFCL2_DRIVERGETSIZE ICL2_DriverGetSize;
 	PFCL2_DRIVEROPENP ICL2_DriverOpenP;
 	PFCL2_DRIVERCLOSE ICL2_DriverClose;
 	PFCL2_CREATEMESSAGE ICL2_CreateMessage;
 	PFCL2_FREEMESSAGE ICL2_FreeMessage;
 	PFCL2_CLONEMESSAGE ICL2_CloneMessage;
 	PFCL2_CREATESINGLEIDRECEIVER ICL2_CreateSingleIdReceiver;
 	PFCL2_CREATEIDAREARECEIVER ICL2_CreateIdAreaReceiver;
 	PFCL2_CREATEIDAREARECEIVEREX ICL2_CreateIdAreaReceiverEx;
 	PFCL2_REGISTERIDAREA ICL2_RegisterIdArea;
 	PFCL2_UNREGISTERIDAREA ICL2_UnregisterIdArea;
 	PFCL2_CREATEMASKRECEIVER ICL2_CreateMaskReceiver;
 	PFCL2_CREATEARRAYRECEIVER ICL2_CreateArrayReceiver;
 	PFCL2_DELETERECEIVER ICL2_DeleteReceiver;
 	PFCL2_READ ICL2_Read;
 	PFCL2_READARRAYRECEIVER ICL2_ReadArrayReceiver;
 	PFCL2_WRITE ICL2_Write;
 	PFCL2_CSTCYCLEOPEN ICL2_CstCycleOpen;
 	PFCL2_CSTCYCLEUPDATE ICL2_CstCycleUpdate;
 	PFCL2_CSTCYCLESTART ICL2_CstCycleStart;
 	PFCL2_CSTCYCLESTOP ICL2_CstCycleStop;
 	PFCL2_CSTCYCLECLOSE ICL2_CstCycleClose;
 	PFCL2_GETBAUDRATE ICL2_GetBaudrate;
 	PFCL2_GETBUSLOAD ICL2_GetBusload;
 	PFCL2_GETBUSSTATE ICL2_GetBusState;
 	PFCL2_GETRECEIVECOUNTER ICL2_GetReceiveCounter;
 	PFCL2_GETLOSTCOUNTER ICL2_GetLostCounter;
 	PFCL2_GETTRANSMITCOUNTER ICL2_GetTransmitCounter;
 	PFCL2_GETTRANSMITERRORCOUNTER ICL2_GetTransmitErrorCounter;
 	PFCL2_GETRECEIVEERRORCOUNTER ICL2_GetReceiveErrorCounter;
 	PFCL2_ISSENDINGACTIVE ICL2_IsSendingActive;
 	PFCL2_GETBUSALARM ICL2_GetBusAlarm;
 	PFCL2_RESETBUSALARM ICL2_ResetBusAlarm;
 	PFCL2_GETTRANSMITQUEUELENGTH ICL2_GetTransmitQueueLength;
 	PFCL2_GETRECEIVEQUEUELENGTH ICL2_GetReceiveQueueLength;
 	PFCL2_GETTRANSMITPOOLSIZE ICL2_GetTransmitPoolSize;
 	PFCL2_GETRECEIVEPOOLSIZE ICL2_GetReceivePoolSize;
 	PFCL2_DISABLESYNCSERVICE ICL2_DisableSyncService;
 	PFCL2_DISABLETIMESERVICE ICL2_DisableTimeService;
 	PFCL2_ENABLESYNCSERVICE ICL2_EnableSyncService;
 	PFCL2_ENABLETIMESERVICE ICL2_EnableTimeService;
 	PFCL2_UPDATETIMESERVICE ICL2_UpdateTimeService;
 	PFCL2_GETMESSAGEDATAPOINTER ICL2_GetMessageDataPointer;
 	PFCL2_GETMESSAGEID ICL2_GetMessageId;
 	PFCL2_GETMESSAGELENGTH ICL2_GetMessageLength;
 	PFCL2_GETTIMESTAMP ICL2_GetTimeStamp;
 	PFCL2_IS29BITIDMESSAGE ICL2_Is29BitIdMessage;
 	PFCL2_ISRTRMESSAGE ICL2_IsRTRMessage;
 	PFCL2_ISTRANSMITMESSAGE ICL2_IsTransmitMessage;
 	PFCL2_GETNETID ICL2_GetNetId;
 	PFCL2_LOSTMESSAGES ICL2_LostMessages;
 	PFCL2_GETMSGCOUNT ICL2_GetMsgCount;
 	PFCL2_GETCIASTATE ICL2_GetCiAState;
 	PFCL2_SETCIASTATE ICL2_SetCiAState;
 	PFCL2_GETPROPERTY ICL2_GetProperty;
 	PFCL2_CMDREGISTER ICL2_CmdRegister;
 	PFCL2_CMDUNREGISTER ICL2_CmdUnRegister;
 	PFCL2_GETTXQUEUELENGTH ICL2_GetTxQueueLength;
 	PFCL2_MSGALLOC ICL2_MsgAlloc;
 	PFCL2_MSGGETDATA ICL2_MsgGetData;
 	PFCL2_MSGFREE ICL2_MsgFree;
 	PFCL2_MSGSENDACKNIRQ ICL2_MsgSendAcknIRQ;
 	PFCL2_MSGSENDACKNNOIRQ ICL2_MsgSendAcknNoIRQ;
 	PFCL2_MSGPUTRQUEUE ICL2_MsgPutRQueue;
 	PFCL2_MSGCLONE ICL2_MsgClone;
 	PFCL2_GETSUPPLIERVERSION ICL2_GetSupplierVersion;
 } ICmpCAACanL2_C;

#ifdef CPLUSPLUS
class ICmpCAACanL2 : public IBase
{
	public:
		virtual CAA_HANDLE CDECL ICL2_DriverOpenH(unsigned char ucNetId, unsigned short usBaudrate, CAA_BOOL xSupport29Bit, CAA_COUNT ctMessages, CAA_ERROR* peError) =0;
		virtual CAA_SIZE CDECL ICL2_DriverGetSize(unsigned char ucNetId, CAA_BOOL xSupport29Bit, CAA_COUNT ctMessages, CAA_ERROR* peError) =0;
		virtual CAA_HANDLE CDECL ICL2_DriverOpenP(unsigned char ucNetId, unsigned short usBaudrate, CAA_BOOL xSupport29Bit, CAA_SIZE szMemSize, CAA_PVOID pMemory, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL ICL2_DriverClose(CAA_HANDLE hDriver) =0;
		virtual CAA_HANDLE CDECL ICL2_CreateMessage(CAA_HANDLE hDriver, CL2I_COBID cobId, unsigned char ucLength, CAA_BOOL xRTR, CAA_BOOL x29BitId, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL ICL2_FreeMessage(CAA_HANDLE hMessage) =0;
		virtual CAA_HANDLE CDECL ICL2_CloneMessage(CAA_HANDLE hMessage, CAA_ERROR* peError) =0;
		virtual CAA_HANDLE CDECL ICL2_CreateSingleIdReceiver(CAA_HANDLE hDriver, CL2I_COBID cobId, CAA_BOOL xRTR, CAA_BOOL x29BitId, CAA_BOOL xTransmit, CAA_BOOL xAlwaysNewest, CAA_ENUM eEvent, CAA_BOOL xEnableSyncWindow, CAA_ERROR* peError) =0;
		virtual CAA_HANDLE CDECL ICL2_CreateIdAreaReceiver(CAA_HANDLE hDriver, CAA_BOOL xAlwaysNewest, CAA_ENUM eEvent, CAA_BOOL xEnableSyncWindow, CAA_ERROR* peError) =0;
		virtual CAA_HANDLE CDECL ICL2_CreateIdAreaReceiverEx(CAA_HANDLE hDriver, CAA_BOOL xAlwaysNewest, CAA_BOOL xReverse, CAA_ENUM eEvent, CAA_BOOL xEnableSyncWindow, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL ICL2_RegisterIdArea(CAA_HANDLE hReceiverId, CL2I_COBID cobIdStart, CL2I_COBID cobIdEnd, CAA_BOOL xRTRValue, CAA_BOOL xRTRMask, CAA_BOOL x29BitIdValue, CAA_BOOL x29BitIdMask, CAA_BOOL xTransmitValue, CAA_BOOL xTransmitMask) =0;
		virtual CAA_ERROR CDECL ICL2_UnregisterIdArea(CAA_HANDLE hReceiverId, CL2I_COBID cobIdStart, CL2I_COBID cobIdEnd, CAA_BOOL xRTRValue, CAA_BOOL xRTRMask, CAA_BOOL x29BitIdValue, CAA_BOOL x29BitIdMask, CAA_BOOL xTransmitValue, CAA_BOOL xTransmitMask) =0;
		virtual CAA_HANDLE CDECL ICL2_CreateMaskReceiver(CAA_HANDLE hDriver, CL2I_COBID cobIdValue, CL2I_COBID cobIdMask, CAA_BOOL xRTRValue, CAA_BOOL xRTRMask, CAA_BOOL x29BitIdValue, CAA_BOOL x29BitIdMask, CAA_BOOL xTransmitValue, CAA_BOOL xTransmitMask, CAA_BOOL xAlwaysNewest, CAA_ENUM eEvent, CAA_BOOL xEnableSyncWindow, CAA_ERROR* peError) =0;
		virtual CAA_HANDLE CDECL ICL2_CreateArrayReceiver(CAA_HANDLE hDriver, CL2I_ARRAYRECV_ENTRY* paSortedCOBIDs, CAA_COUNT ctCOBIDs, CAA_ENUM eEvent, CAA_BOOL xEnableSyncWindow, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL ICL2_DeleteReceiver(CAA_HANDLE hReceiverId) =0;
		virtual CAA_HANDLE CDECL ICL2_Read(CAA_HANDLE hReceiverId, CAA_COUNT* pctMsgLeft, CAA_ERROR* peError) =0;
		virtual CAA_HANDLE CDECL ICL2_ReadArrayReceiver(CAA_HANDLE hArrayReceiver, CAA_COUNT ctIndex, CAA_COUNT* pctMsgLeft, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL ICL2_Write(CAA_HANDLE hDriver, CAA_HANDLE hMessage, unsigned char ucPrio, CAA_BOOL xEnableSyncWindow) =0;
		virtual CAA_HANDLE CDECL ICL2_CstCycleOpen(CAA_HANDLE hDriver, CAA_ENUM eCstEvent, unsigned short usPrio, CAA_BOOL xEnableSyncWindow, CAA_UDINT ulCstCycle, CAA_UDINT ulCstForewarnTime, CAA_ERROR* peError) =0;
		virtual CAA_HANDLE CDECL ICL2_CstCycleUpdate(CAA_HANDLE hCstCycle, CAA_HANDLE hMessage, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL ICL2_CstCycleStart(CAA_HANDLE hCstCycle) =0;
		virtual CAA_ERROR CDECL ICL2_CstCycleStop(CAA_HANDLE hCstCycle) =0;
		virtual CAA_HANDLE CDECL ICL2_CstCycleClose(CAA_HANDLE hCstCycle, CAA_ERROR* peError) =0;
		virtual unsigned short CDECL ICL2_GetBaudrate(CAA_HANDLE hDriver, CAA_ERROR* peError) =0;
		virtual unsigned short CDECL ICL2_GetBusload(CAA_HANDLE hDriver, CAA_ERROR* peError) =0;
		virtual CAA_ENUM CDECL ICL2_GetBusState(CAA_HANDLE hDriver, CAA_ERROR* peError) =0;
		virtual CAA_COUNT CDECL ICL2_GetReceiveCounter(CAA_HANDLE hDriver, CAA_ERROR* peError) =0;
		virtual CAA_COUNT CDECL ICL2_GetLostCounter(CAA_HANDLE hDriver, CAA_ERROR* peError) =0;
		virtual CAA_COUNT CDECL ICL2_GetTransmitCounter(CAA_HANDLE hDriver, CAA_ERROR* peError) =0;
		virtual CAA_COUNT CDECL ICL2_GetTransmitErrorCounter(CAA_HANDLE hDriver, CAA_ERROR* peError) =0;
		virtual CAA_COUNT CDECL ICL2_GetReceiveErrorCounter(CAA_HANDLE hDriver, CAA_ERROR* peError) =0;
		virtual CAA_BOOL CDECL ICL2_IsSendingActive(CAA_HANDLE hDriver, CAA_ERROR* peError) =0;
		virtual CAA_BOOL CDECL ICL2_GetBusAlarm(CAA_HANDLE hDriver, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL ICL2_ResetBusAlarm(CAA_HANDLE hDriver) =0;
		virtual CAA_COUNT CDECL ICL2_GetTransmitQueueLength(CAA_HANDLE hDriver, CAA_ERROR* peError) =0;
		virtual CAA_COUNT CDECL ICL2_GetReceiveQueueLength(CAA_HANDLE hDriver, CAA_ERROR* peError) =0;
		virtual CAA_COUNT CDECL ICL2_GetTransmitPoolSize(CAA_HANDLE hDriver, CAA_ERROR* peError) =0;
		virtual CAA_COUNT CDECL ICL2_GetReceivePoolSize(CAA_HANDLE hDriver, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL ICL2_DisableSyncService(CAA_HANDLE hDriver) =0;
		virtual CAA_ERROR CDECL ICL2_DisableTimeService(CAA_HANDLE hDriver) =0;
		virtual CAA_ERROR CDECL ICL2_EnableSyncService(CAA_HANDLE hDriver, CL2I_COBID cobId, CAA_BOOL xSyncProducer, CAA_BOOL xEnableSyncEvent, CAA_UDINT ulSyncCycle, CAA_UDINT ulSyncWindowLength, CAA_UDINT ulSyncForewarnTime) =0;
		virtual CAA_ERROR CDECL ICL2_EnableTimeService(CAA_HANDLE hDriver, CL2I_COBID cobId, CAA_BOOL xTimeProducer, CAA_BOOL xEnableTimeEvent, CAA_UDINT ulTimeCycle, CAA_UDINT ulTimeForewarnTime) =0;
		virtual CAA_ERROR CDECL ICL2_UpdateTimeService(CAA_HANDLE hDriver, CAA_UDINT ulTime, CAA_UDINT ulDate) =0;
		virtual CL2I_DATA* CDECL ICL2_GetMessageDataPointer(CAA_HANDLE hMessage, CAA_ERROR* peError) =0;
		virtual CL2I_COBID CDECL ICL2_GetMessageId(CAA_HANDLE hMessage, CAA_ERROR* peError) =0;
		virtual unsigned char CDECL ICL2_GetMessageLength(CAA_HANDLE hMessage, CAA_ERROR* peError) =0;
		virtual CAA_UDINT CDECL ICL2_GetTimeStamp(CAA_HANDLE hMessage, CAA_ERROR* peError) =0;
		virtual CAA_BOOL CDECL ICL2_Is29BitIdMessage(CAA_HANDLE hMessage, CAA_ERROR* peError) =0;
		virtual CAA_BOOL CDECL ICL2_IsRTRMessage(CAA_HANDLE hMessage, CAA_ERROR* peError) =0;
		virtual CAA_BOOL CDECL ICL2_IsTransmitMessage(CAA_HANDLE hMessage, CAA_ERROR* peError) =0;
		virtual unsigned char CDECL ICL2_GetNetId(CAA_HANDLE hMessage, CAA_ERROR* peError) =0;
		virtual CAA_COUNT CDECL ICL2_LostMessages(CAA_HANDLE hReceiverId, CAA_ERROR* peError) =0;
		virtual CAA_COUNT CDECL ICL2_GetMsgCount(CAA_HANDLE hReceiverId, CAA_ERROR* peError) =0;
		virtual unsigned char CDECL ICL2_GetCiAState(CAA_HANDLE hDriver, CAA_ERROR* peError) =0;
		virtual CAA_ERROR CDECL ICL2_SetCiAState(CAA_HANDLE hDriver, unsigned char byState) =0;
		virtual CAA_UDINT CDECL ICL2_GetProperty(unsigned short usPropery) =0;
		virtual CAA_ERROR CDECL ICL2_CmdRegister(unsigned char ucNetId, CMD_CMDRV* pCMDRV, CAA_COUNT ctMessages, CL2I_INFO** ppInfo) =0;
		virtual CAA_ERROR CDECL ICL2_CmdUnRegister(unsigned char ucNetId) =0;
		virtual CAA_COUNT CDECL ICL2_GetTxQueueLength(unsigned char ucNetId, CAA_ERROR* peError) =0;
		virtual CAA_HANDLE CDECL ICL2_MsgAlloc(unsigned char ucNetId, CAA_ERROR* peError) =0;
		virtual CL2I_BLOCK* CDECL ICL2_MsgGetData(CAA_HANDLE hBlock) =0;
		virtual CAA_ERROR CDECL ICL2_MsgFree(unsigned char ucNetId, CAA_HANDLE hBlock) =0;
		virtual CAA_ERROR CDECL ICL2_MsgSendAcknIRQ(unsigned char ucNetId, CAA_HANDLE hBlock) =0;
		virtual CAA_ERROR CDECL ICL2_MsgSendAcknNoIRQ(unsigned char ucNetId, CAA_HANDLE hBlock) =0;
		virtual CAA_ERROR CDECL ICL2_MsgPutRQueue(unsigned char ucNetId, CAA_HANDLE hBlock) =0;
		virtual CAA_HANDLE CDECL ICL2_MsgClone(unsigned char ucNetId, CAA_HANDLE hBlock, CAA_ERROR* peError) =0;
		virtual unsigned short CDECL ICL2_GetSupplierVersion(CAA_BOOL xDummy) =0;
};
	#ifndef ITF_CmpCAACanL2
		#define ITF_CmpCAACanL2 static ICmpCAACanL2 *pICmpCAACanL2 = NULL;
	#endif
	#define EXTITF_CmpCAACanL2
#else	/*CPLUSPLUS*/
	typedef ICmpCAACanL2_C		ICmpCAACanL2;
	#ifndef ITF_CmpCAACanL2
		#define ITF_CmpCAACanL2
	#endif
	#define EXTITF_CmpCAACanL2
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCAACANL2ITF_H_*/
