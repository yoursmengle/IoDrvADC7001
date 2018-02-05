 /**
 * <interfacename>SysEthernet</interfacename>
 * <description> 
 *	<p>The SysEthernet interface contains low level routines for a direct access to an ethernet controller.
 *	This interface is typically used by an EtherCAT driver.</p>
 *	<p>All other ethernet communciation components use higher level routines (see SysSocket interface).</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSETHERNET2ITF_H_
#define _SYSETHERNET2ITF_H_

#include "CmpStd.h"

 

 




/*Possible values for the flags in the EthernetframeAddInfo struct are:*/
#define EAI_FLG_QUALITY_GOOD	0x00000001
#define EAI_FLG_CRC_ERROR		0x00000002
#define EAI_FLG_ALIGNMENT_ERROR	0x00000004
#define EAI_FLG_OTHER_ERROR		0x00000008

typedef struct
{
	unsigned long ulFlags;
	unsigned long ulDummy;
	unsigned __int64 liTimestamp;
	unsigned __int64 liTimestampHR;
}EthernetframeAddInfo;


typedef struct
{
	long iMasterNum;
	unsigned char **ppFrame;
	long* pnSize;
	EthernetframeAddInfo** ppAddInfo;  
	long nReturnVal;
}GetEthernetInterfaceEx;

typedef struct
{
	long iMasterNum;
	long nReturnVal;
}ResetAdapter;

typedef struct
{
	long iMasterNum;
	short PciVendorID;
	short PciDeviceID;
	void* pHWRegs;
}EthernetAdapterDesc;

typedef struct
{
	long iMasterNum;
	EthernetAdapterDesc** ppAdapterDesc;
	long nReturnVal;
}GetAdapterDescription;

typedef struct
{
	long iMasterNum;
	unsigned char **ppFrame;
	RTS_I32* pnSize;
	RTS_I32 nReturnVal;
}GetIPEthernetInterface2;

typedef struct
{
	long iMasterNum;
	Ethernetframe *pFrame;
	RTS_I32 nSize;
	RTS_I32 nReturnVal;
}SendIPEthernetInterface2;

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  <description>Get info about specified network adapters</description>
 * <param name="paiei" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
void CDECL CDECL_EXT resetadapter(ResetAdapter* pra);
typedef void (CDECL * PFRESETADAPTER) (ResetAdapter* pra);
#if defined(SYSETHERNET2_NOTIMPLEMENTED) || defined(RESETADAPTER_NOTIMPLEMENTED)
	#define USE_resetadapter
	#define EXT_resetadapter
	#define GET_resetadapter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_resetadapter(p0) 
	#define CHK_resetadapter  FALSE
	#define EXP_resetadapter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_resetadapter
	#define EXT_resetadapter
	#define GET_resetadapter(fl)  CAL_CMGETAPI( "resetadapter" ) 
	#define CAL_resetadapter  resetadapter
	#define CHK_resetadapter  TRUE
	#define EXP_resetadapter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"resetadapter", (RTS_UINTPTR)resetadapter, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSETHERNET2_EXTERNAL)
	#define USE_resetadapter
	#define EXT_resetadapter
	#define GET_resetadapter(fl)  CAL_CMGETAPI( "resetadapter" ) 
	#define CAL_resetadapter  resetadapter
	#define CHK_resetadapter  TRUE
	#define EXP_resetadapter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"resetadapter", (RTS_UINTPTR)resetadapter, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysEthernet2resetadapter
	#define EXT_SysEthernet2resetadapter
	#define GET_SysEthernet2resetadapter  ERR_OK
	#define CAL_SysEthernet2resetadapter  resetadapter
	#define CHK_SysEthernet2resetadapter  TRUE
	#define EXP_SysEthernet2resetadapter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"resetadapter", (RTS_UINTPTR)resetadapter, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_resetadapter
	#define EXT_resetadapter
	#define GET_resetadapter(fl)  CAL_CMGETAPI( "resetadapter" ) 
	#define CAL_resetadapter  resetadapter
	#define CHK_resetadapter  TRUE
	#define EXP_resetadapter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"resetadapter", (RTS_UINTPTR)resetadapter, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_resetadapter  PFRESETADAPTER pfresetadapter;
	#define EXT_resetadapter  extern PFRESETADAPTER pfresetadapter;
	#define GET_resetadapter(fl)  s_pfCMGetAPI2( "resetadapter", (RTS_VOID_FCTPTR *)&pfresetadapter, (fl), 0, 0)
	#define CAL_resetadapter  pfresetadapter
	#define CHK_resetadapter  (pfresetadapter != NULL)
	#define EXP_resetadapter   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"resetadapter", (RTS_UINTPTR)resetadapter, 1, 0) 
#endif


/**
 *  <description>same as getethernet, but with additional info.</description>
 * <param name="pgeiex" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
void CDECL CDECL_EXT getethframeex(GetEthernetInterfaceEx* pgeiex);
typedef void (CDECL * PFGETETHFRAMEEX) (GetEthernetInterfaceEx* pgeiex);
#if defined(SYSETHERNET2_NOTIMPLEMENTED) || defined(GETETHFRAMEEX_NOTIMPLEMENTED)
	#define USE_getethframeex
	#define EXT_getethframeex
	#define GET_getethframeex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_getethframeex(p0) 
	#define CHK_getethframeex  FALSE
	#define EXP_getethframeex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_getethframeex
	#define EXT_getethframeex
	#define GET_getethframeex(fl)  CAL_CMGETAPI( "getethframeex" ) 
	#define CAL_getethframeex  getethframeex
	#define CHK_getethframeex  TRUE
	#define EXP_getethframeex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getethframeex", (RTS_UINTPTR)getethframeex, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSETHERNET2_EXTERNAL)
	#define USE_getethframeex
	#define EXT_getethframeex
	#define GET_getethframeex(fl)  CAL_CMGETAPI( "getethframeex" ) 
	#define CAL_getethframeex  getethframeex
	#define CHK_getethframeex  TRUE
	#define EXP_getethframeex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getethframeex", (RTS_UINTPTR)getethframeex, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysEthernet2getethframeex
	#define EXT_SysEthernet2getethframeex
	#define GET_SysEthernet2getethframeex  ERR_OK
	#define CAL_SysEthernet2getethframeex  getethframeex
	#define CHK_SysEthernet2getethframeex  TRUE
	#define EXP_SysEthernet2getethframeex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getethframeex", (RTS_UINTPTR)getethframeex, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_getethframeex
	#define EXT_getethframeex
	#define GET_getethframeex(fl)  CAL_CMGETAPI( "getethframeex" ) 
	#define CAL_getethframeex  getethframeex
	#define CHK_getethframeex  TRUE
	#define EXP_getethframeex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getethframeex", (RTS_UINTPTR)getethframeex, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_getethframeex  PFGETETHFRAMEEX pfgetethframeex;
	#define EXT_getethframeex  extern PFGETETHFRAMEEX pfgetethframeex;
	#define GET_getethframeex(fl)  s_pfCMGetAPI2( "getethframeex", (RTS_VOID_FCTPTR *)&pfgetethframeex, (fl), 0, 0)
	#define CAL_getethframeex  pfgetethframeex
	#define CHK_getethframeex  (pfgetethframeex != NULL)
	#define EXP_getethframeex   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getethframeex", (RTS_UINTPTR)getethframeex, 1, 0) 
#endif


/**
 *  <description>An interface function to get some information about the NIC's hardware.</description>
 * <param name="pgad" type="IN">Pointer to a GetAdapterDescription structure.</param>
 * <result>error code</result>
 */
void CDECL CDECL_EXT getadapterdescription(GetAdapterDescription* pgad);
typedef void (CDECL * PFGETADAPTERDESCRIPTION) (GetAdapterDescription* pgad);
#if defined(SYSETHERNET2_NOTIMPLEMENTED) || defined(GETADAPTERDESCRIPTION_NOTIMPLEMENTED)
	#define USE_getadapterdescription
	#define EXT_getadapterdescription
	#define GET_getadapterdescription(fl)  ERR_NOTIMPLEMENTED
	#define CAL_getadapterdescription(p0) 
	#define CHK_getadapterdescription  FALSE
	#define EXP_getadapterdescription  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_getadapterdescription
	#define EXT_getadapterdescription
	#define GET_getadapterdescription(fl)  CAL_CMGETAPI( "getadapterdescription" ) 
	#define CAL_getadapterdescription  getadapterdescription
	#define CHK_getadapterdescription  TRUE
	#define EXP_getadapterdescription  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getadapterdescription", (RTS_UINTPTR)getadapterdescription, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSETHERNET2_EXTERNAL)
	#define USE_getadapterdescription
	#define EXT_getadapterdescription
	#define GET_getadapterdescription(fl)  CAL_CMGETAPI( "getadapterdescription" ) 
	#define CAL_getadapterdescription  getadapterdescription
	#define CHK_getadapterdescription  TRUE
	#define EXP_getadapterdescription  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getadapterdescription", (RTS_UINTPTR)getadapterdescription, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysEthernet2getadapterdescription
	#define EXT_SysEthernet2getadapterdescription
	#define GET_SysEthernet2getadapterdescription  ERR_OK
	#define CAL_SysEthernet2getadapterdescription  getadapterdescription
	#define CHK_SysEthernet2getadapterdescription  TRUE
	#define EXP_SysEthernet2getadapterdescription  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getadapterdescription", (RTS_UINTPTR)getadapterdescription, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_getadapterdescription
	#define EXT_getadapterdescription
	#define GET_getadapterdescription(fl)  CAL_CMGETAPI( "getadapterdescription" ) 
	#define CAL_getadapterdescription  getadapterdescription
	#define CHK_getadapterdescription  TRUE
	#define EXP_getadapterdescription  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getadapterdescription", (RTS_UINTPTR)getadapterdescription, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_getadapterdescription  PFGETADAPTERDESCRIPTION pfgetadapterdescription;
	#define EXT_getadapterdescription  extern PFGETADAPTERDESCRIPTION pfgetadapterdescription;
	#define GET_getadapterdescription(fl)  s_pfCMGetAPI2( "getadapterdescription", (RTS_VOID_FCTPTR *)&pfgetadapterdescription, (fl), 0, 0)
	#define CAL_getadapterdescription  pfgetadapterdescription
	#define CHK_getadapterdescription  (pfgetadapterdescription != NULL)
	#define EXP_getadapterdescription   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getadapterdescription", (RTS_UINTPTR)getadapterdescription, 1, 0) 
#endif



/**
 * <description>Send IP etherpacket (EoE)</description>
 * <param name="psfi" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
void CDECL CDECL_EXT sendIPethframe2(SendIPEthernetInterface2* psfi);
typedef void (CDECL * PFSENDIPETHFRAME2) (SendIPEthernetInterface2* psfi);
#if defined(SYSETHERNET2_NOTIMPLEMENTED) || defined(SENDIPETHFRAME2_NOTIMPLEMENTED)
	#define USE_sendIPethframe2
	#define EXT_sendIPethframe2
	#define GET_sendIPethframe2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sendIPethframe2(p0)  
	#define CHK_sendIPethframe2  FALSE
	#define EXP_sendIPethframe2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sendIPethframe2
	#define EXT_sendIPethframe2
	#define GET_sendIPethframe2(fl)  CAL_CMGETAPI( "sendIPethframe2" ) 
	#define CAL_sendIPethframe2  sendIPethframe2
	#define CHK_sendIPethframe2  TRUE
	#define EXP_sendIPethframe2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"sendIPethframe2", (RTS_UINTPTR)sendIPethframe2, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSETHERNET2_EXTERNAL)
	#define USE_sendIPethframe2
	#define EXT_sendIPethframe2
	#define GET_sendIPethframe2(fl)  CAL_CMGETAPI( "sendIPethframe2" ) 
	#define CAL_sendIPethframe2  sendIPethframe2
	#define CHK_sendIPethframe2  TRUE
	#define EXP_sendIPethframe2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"sendIPethframe2", (RTS_UINTPTR)sendIPethframe2, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysEthernet2sendIPethframe2
	#define EXT_SysEthernet2sendIPethframe2
	#define GET_SysEthernet2sendIPethframe2  ERR_OK
	#define CAL_SysEthernet2sendIPethframe2 pISysEthernet2->IsendIPethframe2
	#define CHK_SysEthernet2sendIPethframe2 (pISysEthernet2 != NULL)
	#define EXP_SysEthernet2sendIPethframe2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_sendIPethframe2
	#define EXT_sendIPethframe2
	#define GET_sendIPethframe2(fl)  CAL_CMGETAPI( "sendIPethframe2" ) 
	#define CAL_sendIPethframe2 pISysEthernet2->IsendIPethframe2
	#define CHK_sendIPethframe2 (pISysEthernet2 != NULL)
	#define EXP_sendIPethframe2  CAL_CMEXPAPI( "sendIPethframe2" ) 
#else /* DYNAMIC_LINK */
	#define USE_sendIPethframe2  PFSENDIPETHFRAME2 pfsendIPethframe2;
	#define EXT_sendIPethframe2  extern PFSENDIPETHFRAME2 pfsendIPethframe2;
	#define GET_sendIPethframe2(fl)  s_pfCMGetAPI2( "sendIPethframe2", (RTS_VOID_FCTPTR *)&pfsendIPethframe2, (fl), 0, 0)
	#define CAL_sendIPethframe2  pfsendIPethframe2
	#define CHK_sendIPethframe2  (pfsendIPethframe2 != NULL)
	#define EXP_sendIPethframe2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"sendIPethframe2", (RTS_UINTPTR)sendIPethframe2, 1, 0) 
#endif




/**
 * <description>Get IP ethernet packet</description>
 * <param name="pgei" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
void CDECL CDECL_EXT getIPethframe2(GetIPEthernetInterface2* pgei);
typedef void (CDECL * PFGETIPETHFRAME2) (GetIPEthernetInterface2* pgei);
#if defined(SYSETHERNET2_NOTIMPLEMENTED) || defined(GETIPETHFRAME2_NOTIMPLEMENTED)
	#define USE_getIPethframe2
	#define EXT_getIPethframe2
	#define GET_getIPethframe2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_getIPethframe2(p0)  
	#define CHK_getIPethframe2  FALSE
	#define EXP_getIPethframe2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_getIPethframe2
	#define EXT_getIPethframe2
	#define GET_getIPethframe2(fl)  CAL_CMGETAPI( "getIPethframe2" ) 
	#define CAL_getIPethframe2  getIPethframe2
	#define CHK_getIPethframe2  TRUE
	#define EXP_getIPethframe2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getIPethframe2", (RTS_UINTPTR)getIPethframe2, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSETHERNET2_EXTERNAL)
	#define USE_getIPethframe2
	#define EXT_getIPethframe2
	#define GET_getIPethframe2(fl)  CAL_CMGETAPI( "getIPethframe2" ) 
	#define CAL_getIPethframe2  getIPethframe2
	#define CHK_getIPethframe2  TRUE
	#define EXP_getIPethframe2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getIPethframe2", (RTS_UINTPTR)getIPethframe2, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysEthernet2getIPethframe2
	#define EXT_SysEthernet2getIPethframe2
	#define GET_SysEthernet2getIPethframe2  ERR_OK
	#define CAL_SysEthernet2getIPethframe2 pISysEthernet2->IgetIPethframe2
	#define CHK_SysEthernet2getIPethframe2 (pISysEthernet2 != NULL)
	#define EXP_SysEthernet2getIPethframe2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_getIPethframe2
	#define EXT_getIPethframe2
	#define GET_getIPethframe2(fl)  CAL_CMGETAPI( "getIPethframe2" ) 
	#define CAL_getIPethframe2 pISysEthernet2->IgetIPethframe2
	#define CHK_getIPethframe2 (pISysEthernet2 != NULL)
	#define EXP_getIPethframe2  CAL_CMEXPAPI( "getIPethframe2" ) 
#else /* DYNAMIC_LINK */
	#define USE_getIPethframe2  PFGETIPETHFRAME2 pfgetIPethframe2;
	#define EXT_getIPethframe2  extern PFGETIPETHFRAME2 pfgetIPethframe2;
	#define GET_getIPethframe2(fl)  s_pfCMGetAPI2( "getIPethframe2", (RTS_VOID_FCTPTR *)&pfgetIPethframe2, (fl), 0, 0)
	#define CAL_getIPethframe2  pfgetIPethframe2
	#define CHK_getIPethframe2  (pfgetIPethframe2 != NULL)
	#define EXP_getIPethframe2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getIPethframe2", (RTS_UINTPTR)getIPethframe2, 1, 0) 
#endif




typedef void (CDECL * PFETHFRAMERECEIVED)(void);

typedef struct _EthernetAdapterDescription
{
	unsigned char aucMacAddress[6];
	int iAdapterNum;
	int iMasterNum;
	int bAdapterOpen;
	PFGETIPETHFRAME pfgetIPethframe;
	PFSENDIPETHFRAME pfsendIPethframe;
	PFGETADAPTERINFO pfgetadapterinfo;
	PFGETNUMBEROFADAPTERS pfgetnumberofadapters;
	PFCLOSEETHERNET pfcloseethernet;
	PFGETETHFRAME pfgetethframe;
	PFSENDETHFRAME pfsendethframe;
	PFOPENETHERNET pfopenethernet;
	PFGETADAPTERDESCRIPTION pfgetadapterdescription;
	PFGETETHFRAMEEX pfgetethframeex;
	PFRESETADAPTER pfresetadapter;
	PFETHFRAMERECEIVED pfEthFrameReceived;
	char szDriverName[32];
	PFGETIPETHFRAME2 pfgetIPethframe2;
	PFSENDIPETHFRAME2 pfsendIPethframe2;
}EthernetAdapterDescription;
RTS_RESULT CDECL CDECL_EXT SysEthernetRegisterEthernetAdapter(EthernetAdapterDescription* pAdapterDesc, int bUnregister);
typedef RTS_RESULT (CDECL * PFSYSETHERNETREGISTERETHERNETADAPTER) (EthernetAdapterDescription* pAdapterDesc, int bUnregister);
#if defined(SYSETHERNET2_NOTIMPLEMENTED) || defined(SYSETHERNETREGISTERETHERNETADAPTER_NOTIMPLEMENTED)
	#define USE_SysEthernetRegisterEthernetAdapter
	#define EXT_SysEthernetRegisterEthernetAdapter
	#define GET_SysEthernetRegisterEthernetAdapter(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysEthernetRegisterEthernetAdapter(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysEthernetRegisterEthernetAdapter  FALSE
	#define EXP_SysEthernetRegisterEthernetAdapter  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysEthernetRegisterEthernetAdapter
	#define EXT_SysEthernetRegisterEthernetAdapter
	#define GET_SysEthernetRegisterEthernetAdapter(fl)  CAL_CMGETAPI( "SysEthernetRegisterEthernetAdapter" ) 
	#define CAL_SysEthernetRegisterEthernetAdapter  SysEthernetRegisterEthernetAdapter
	#define CHK_SysEthernetRegisterEthernetAdapter  TRUE
	#define EXP_SysEthernetRegisterEthernetAdapter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysEthernetRegisterEthernetAdapter", (RTS_UINTPTR)SysEthernetRegisterEthernetAdapter, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSETHERNET2_EXTERNAL)
	#define USE_SysEthernetRegisterEthernetAdapter
	#define EXT_SysEthernetRegisterEthernetAdapter
	#define GET_SysEthernetRegisterEthernetAdapter(fl)  CAL_CMGETAPI( "SysEthernetRegisterEthernetAdapter" ) 
	#define CAL_SysEthernetRegisterEthernetAdapter  SysEthernetRegisterEthernetAdapter
	#define CHK_SysEthernetRegisterEthernetAdapter  TRUE
	#define EXP_SysEthernetRegisterEthernetAdapter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysEthernetRegisterEthernetAdapter", (RTS_UINTPTR)SysEthernetRegisterEthernetAdapter, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysEthernet2SysEthernetRegisterEthernetAdapter
	#define EXT_SysEthernet2SysEthernetRegisterEthernetAdapter
	#define GET_SysEthernet2SysEthernetRegisterEthernetAdapter  ERR_OK
	#define CAL_SysEthernet2SysEthernetRegisterEthernetAdapter  SysEthernetRegisterEthernetAdapter
	#define CHK_SysEthernet2SysEthernetRegisterEthernetAdapter  TRUE
	#define EXP_SysEthernet2SysEthernetRegisterEthernetAdapter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysEthernetRegisterEthernetAdapter", (RTS_UINTPTR)SysEthernetRegisterEthernetAdapter, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_SysEthernetRegisterEthernetAdapter
	#define EXT_SysEthernetRegisterEthernetAdapter
	#define GET_SysEthernetRegisterEthernetAdapter(fl)  CAL_CMGETAPI( "SysEthernetRegisterEthernetAdapter" ) 
	#define CAL_SysEthernetRegisterEthernetAdapter  SysEthernetRegisterEthernetAdapter
	#define CHK_SysEthernetRegisterEthernetAdapter  TRUE
	#define EXP_SysEthernetRegisterEthernetAdapter  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysEthernetRegisterEthernetAdapter", (RTS_UINTPTR)SysEthernetRegisterEthernetAdapter, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_SysEthernetRegisterEthernetAdapter  PFSYSETHERNETREGISTERETHERNETADAPTER pfSysEthernetRegisterEthernetAdapter;
	#define EXT_SysEthernetRegisterEthernetAdapter  extern PFSYSETHERNETREGISTERETHERNETADAPTER pfSysEthernetRegisterEthernetAdapter;
	#define GET_SysEthernetRegisterEthernetAdapter(fl)  s_pfCMGetAPI2( "SysEthernetRegisterEthernetAdapter", (RTS_VOID_FCTPTR *)&pfSysEthernetRegisterEthernetAdapter, (fl), 0, 0)
	#define CAL_SysEthernetRegisterEthernetAdapter  pfSysEthernetRegisterEthernetAdapter
	#define CHK_SysEthernetRegisterEthernetAdapter  (pfSysEthernetRegisterEthernetAdapter != NULL)
	#define EXP_SysEthernetRegisterEthernetAdapter   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysEthernetRegisterEthernetAdapter", (RTS_UINTPTR)SysEthernetRegisterEthernetAdapter, 1, 0) 
#endif

#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSENDIPETHFRAME2 IsendIPethframe2;
 	PFGETIPETHFRAME2 IgetIPethframe2;
 } ISysEthernet2_C;

#ifdef CPLUSPLUS
class ISysEthernet2 : public IBase
{
	public:
		virtual void CDECL IsendIPethframe2(SendIPEthernetInterface2* psfi) =0;
		virtual void CDECL IgetIPethframe2(GetIPEthernetInterface2* pgei) =0;
};
	#ifndef ITF_SysEthernet2
		#define ITF_SysEthernet2 static ISysEthernet2 *pISysEthernet2 = NULL;
	#endif
	#define EXTITF_SysEthernet2
#else	/*CPLUSPLUS*/
	typedef ISysEthernet2_C		ISysEthernet2;
	#ifndef ITF_SysEthernet2
		#define ITF_SysEthernet2
	#endif
	#define EXTITF_SysEthernet2
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSETHERNET2ITF_H_*/
