/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/

/**
 * <name>SysTarget</name>
 * <description> 
 *	Target specific functions
 * </description>
 *
 * <copyright>(c) 2003-2018 3S-Smart Software Solutions</copyright>
 */
#ifndef _SYSTARGETDEP_H_
#define _SYSTARGETDEP_H_

#define COMPONENT_NAME "SysTarget"COMPONENT_NAME_POSTFIX
#define COMPONENT_ID    ADDVENDORID(CMP_VENDORID, CMPID_SysTarget)
#define COMPONENT_NAME_UNQUOTED SysTarget






#define CMP_VERSION         UINT32_C(0x03050C01)
#define CMP_VERSION_STRING "3.5.12.1"
#define CMP_VERSION_RC      3,5,12,1
#define CMP_VENDORID       RTS_VENDORID_3S

#ifndef WIN32_RESOURCES

#include "CmpLogItf.h"
#include "CMUtilsItf.h"


#include "CMItf.h"


/*Obsolete include: CMUtilsItf.m4*/


#include "CmpSettingsItf.h"


#include "SysMemItf.h"


#include "SysTargetItf.h"


#include "SysCpuHandlingItf.h"


#include "CmpSIL2Itf.h"


#include "CmpChecksumItf.h"


#include "CmpEventMgrItf.h"







#include "SysTargetItf.h"







    






      






     

    

















     




















#ifdef CPLUSPLUS
    #define INIT_STMT \
    {\
        IBase *pIBase;\
        RTS_RESULT initResult;\
        if (pICmpLog == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpLog, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpLog = (ICmpLog *)pIBase->QueryInterface(pIBase, ITFID_ICmpLog, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
        if (pICMUtils == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCMUtils, &initResult); \
            if (pIBase != NULL) \
            { \
                pICMUtils = (ICMUtils *)pIBase->QueryInterface(pIBase, ITFID_ICMUtils, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
        if (pICmpEventMgr == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpEventMgr, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpEventMgr = (ICmpEventMgr *)pIBase->QueryInterface(pIBase, ITFID_ICmpEventMgr, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpChecksum == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpChecksum, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpChecksum = (ICmpChecksum *)pIBase->QueryInterface(pIBase, ITFID_ICmpChecksum, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpSIL2 == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpSIL2, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpSIL2 = (ICmpSIL2 *)pIBase->QueryInterface(pIBase, ITFID_ICmpSIL2, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pISysCpuHandling == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysCpuHandling, &initResult); \
            if (pIBase != NULL) \
            { \
                pISysCpuHandling = (ISysCpuHandling *)pIBase->QueryInterface(pIBase, ITFID_ISysCpuHandling, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pISysTarget == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysTarget, &initResult); \
            if (pIBase != NULL) \
            { \
                pISysTarget = (ISysTarget *)pIBase->QueryInterface(pIBase, ITFID_ISysTarget, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pISysMem == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysMem, &initResult); \
            if (pIBase != NULL) \
            { \
                pISysMem = (ISysMem *)pIBase->QueryInterface(pIBase, ITFID_ISysMem, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpSettings == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpSettings, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpSettings = (ICmpSettings *)pIBase->QueryInterface(pIBase, ITFID_ICmpSettings, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          /*Obsolete include CMUtils*/ \
		  if (pICM == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCM, &initResult); \
            if (pIBase != NULL) \
            { \
                pICM = (ICM *)pIBase->QueryInterface(pIBase, ITFID_ICM, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
           \
    }
    #define INIT_LOCALS_STMT \
    {\
        pICmpLog = NULL; \
        pICMUtils = NULL; \
        pICmpEventMgr = NULL; \
          pICmpChecksum = NULL; \
          pICmpSIL2 = NULL; \
          pISysCpuHandling = NULL; \
          pISysTarget = NULL; \
          pISysMem = NULL; \
          pICmpSettings = NULL; \
          /*Obsolete include CMUtils*/ \
		  pICM = NULL; \
           \
    }
    #define EXIT_STMT \
    {\
        IBase *pIBase;\
        RTS_RESULT exitResult;\
        if (pICmpLog != NULL) \
        { \
            pIBase = (IBase *)pICmpLog->QueryInterface(pICmpLog, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpLog = NULL; \
            } \
        } \
        if (pICMUtils != NULL) \
        { \
            pIBase = (IBase *)pICMUtils->QueryInterface(pICMUtils, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICMUtils = NULL; \
            } \
        } \
        if (pICmpEventMgr != NULL) \
        { \
            pIBase = (IBase *)pICmpEventMgr->QueryInterface(pICmpEventMgr, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpEventMgr = NULL; \
            } \
        } \
          if (pICmpChecksum != NULL) \
        { \
            pIBase = (IBase *)pICmpChecksum->QueryInterface(pICmpChecksum, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpChecksum = NULL; \
            } \
        } \
          if (pICmpSIL2 != NULL) \
        { \
            pIBase = (IBase *)pICmpSIL2->QueryInterface(pICmpSIL2, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpSIL2 = NULL; \
            } \
        } \
          if (pISysCpuHandling != NULL) \
        { \
            pIBase = (IBase *)pISysCpuHandling->QueryInterface(pISysCpuHandling, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pISysCpuHandling = NULL; \
            } \
        } \
          if (pISysTarget != NULL) \
        { \
            pIBase = (IBase *)pISysTarget->QueryInterface(pISysTarget, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pISysTarget = NULL; \
            } \
        } \
          if (pISysMem != NULL) \
        { \
            pIBase = (IBase *)pISysMem->QueryInterface(pISysMem, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pISysMem = NULL; \
            } \
        } \
          if (pICmpSettings != NULL) \
        { \
            pIBase = (IBase *)pICmpSettings->QueryInterface(pICmpSettings, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpSettings = NULL; \
            } \
        } \
          /*Obsolete include CMUtils*/ \
		  if (pICM != NULL) \
        { \
            pIBase = (IBase *)pICM->QueryInterface(pICM, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICM = NULL; \
            } \
        } \
           \
    }
#else
    #define INIT_STMT
    #define INIT_LOCALS_STMT
    #define EXIT_STMT
#endif



#if defined(STATIC_LINK)
    #define IMPORT_STMT
#else
    #define IMPORT_STMT \
    {\
        RTS_RESULT importResult = ERR_OK;\
        RTS_RESULT TempResult = ERR_OK;\
        INIT_STMT   \
        TempResult = GET_LogAdd(CM_IMPORT_OPTIONAL_FUNCTION); \
        TempResult = GET_CMUtlMemCpy(CM_IMPORT_OPTIONAL_FUNCTION); \
        if (ERR_OK == importResult ) importResult = GET_SysTargetGetVersion(0);\
          if (ERR_OK == importResult ) importResult = GET_SysTargetGetId(0);\
          if (ERR_OK == importResult ) importResult = GET_SysTargetGetType(0);\
          if (ERR_OK == importResult ) importResult = GET_SysTargetGetConfiguredNodeName(0);\
          if (ERR_OK == importResult ) importResult = GET_SysMemSwap(0);\
          if (ERR_OK == importResult ) importResult = GET_SettgRemoveKey(0);\
          if (ERR_OK == importResult ) importResult = GET_SettgSetWStringValue(0);\
          if (ERR_OK == importResult ) importResult = GET_SettgGetIntValue(0);\
          if (ERR_OK == importResult ) importResult = GET_SettgGetStringValue(0);\
          if (ERR_OK == importResult ) importResult = GET_SettgGetWStringValue(0);\
          if (ERR_OK == importResult ) importResult = GET_CMCheckSysTargetSignature(0);\
          if (ERR_OK == importResult ) importResult = GET_CMUtlStrToW(0);\
          if (ERR_OK == importResult ) importResult = GET_CMUtlwstrlen(0);\
          if (ERR_OK == importResult ) importResult = GET_CMUtlwstrcat(0);\
          if (ERR_OK == importResult ) importResult = GET_CMUtlwstrcpy(0);\
          if (ERR_OK == importResult ) importResult = GET_CMUtlSafeStrCat(0);\
          if (ERR_OK == importResult ) importResult = GET_CMUtlsnprintf(0);\
          if (ERR_OK == importResult ) importResult = GET_CMUtlSafeStrCpy(0);\
          if (ERR_OK == importResult ) TempResult = GET_EventPost2(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_EventDelete(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_EventCreate3(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_CRC32Finish(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_CRC32Update(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_CRC32Init(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SIL2CheckCallerContext(CM_IMPORT_OPTIONAL_FUNCTION);\
           \
        /* To make LINT happy */\
        TempResult = TempResult;\
        if (ERR_OK != importResult) return importResult;\
    }
#endif



#ifndef SYSTARGET_DISABLE_EXTREF
#define EXPORT_EXTREF_STMT \
                                        { (RTS_VOID_FCTPTR)systargetgetversion2, "systargetgetversion2", 0x183560B4, 0x03050500 },\
          { (RTS_VOID_FCTPTR)systargetgetversion, "systargetgetversion", 0x03C80949, 0x03050500 },\
          { (RTS_VOID_FCTPTR)systargetgetvendorname2, "systargetgetvendorname2", 0xECA5949D, 0x03050500 },\
          { (RTS_VOID_FCTPTR)systargetgetvendorname, "systargetgetvendorname", 0xC7C8EF60, 0x03050500 },\
          { (RTS_VOID_FCTPTR)systargetgettype2, "systargetgettype2", 0x5F20D079, 0x03050500 },\
          { (RTS_VOID_FCTPTR)systargetgettype, "systargetgettype", 0x4AD38850, 0x03050500 },\
          { (RTS_VOID_FCTPTR)systargetgetserialnumber, "systargetgetserialnumber", 0x0DB18CE9, 0x03050500 },\
          { (RTS_VOID_FCTPTR)systargetgetprocessorid, "systargetgetprocessorid", 0x1C22A79F, 0x03050500 },\
          { (RTS_VOID_FCTPTR)systargetgetoperatingsystemid, "systargetgetoperatingsystemid", 0xC12147F5, 0x03050500 },\
          { (RTS_VOID_FCTPTR)systargetgetnodename2, "systargetgetnodename2", 0x72B60F75, 0x03050500 },\
          { (RTS_VOID_FCTPTR)systargetgetnodename, "systargetgetnodename", 0xA0044621, 0x03050500 },\
          { (RTS_VOID_FCTPTR)systargetgetid2, "systargetgetid2", 0xEA1E39C4, 0x03050500 },\
          { (RTS_VOID_FCTPTR)systargetgetid, "systargetgetid", 0x02ED027A, 0x03050500 },\
          { (RTS_VOID_FCTPTR)systargetgetdevicename2, "systargetgetdevicename2", 0x332F9AF1, 0x03050500 },\
          { (RTS_VOID_FCTPTR)systargetgetdevicename, "systargetgetdevicename", 0x2DEFEA3D, 0x03050500 },\
          
#else
#define EXPORT_EXTREF_STMT
#endif
#ifndef SYSTARGET_DISABLE_EXTREF2
#define EXPORT_EXTREF2_STMT \
                                                                      
#else
#define EXPORT_EXTREF2_STMT
#endif
#if !defined(STATIC_LINK) && !defined(CPLUSPLUS) && !defined(CPLUSPLUS_ONLY)
#define EXPORT_CMPITF_STMT \
    {\
        { (RTS_VOID_FCTPTR)SysTargetSetNodeName, "SysTargetSetNodeName", 0, 0 },\
          { (RTS_VOID_FCTPTR)SysTargetGetAPI, "SysTargetGetAPI", 0, 0 },\
          { (RTS_VOID_FCTPTR)SysTargetCheckIdent, "SysTargetCheckIdent", 0, 0 },\
          { (RTS_VOID_FCTPTR)SysTargetGetDeviceMask, "SysTargetGetDeviceMask", 0, 0 },\
          { (RTS_VOID_FCTPTR)SysTargetGetSignature, "SysTargetGetSignature", 0, 0 },\
          { (RTS_VOID_FCTPTR)SysTargetGetSerialNumber_Secure, "SysTargetGetSerialNumber_Secure", 0, 0 },\
          { (RTS_VOID_FCTPTR)SysTargetGetSerialNumber, "SysTargetGetSerialNumber", 0, 0 },\
          { (RTS_VOID_FCTPTR)SysTargetGetProcessorId, "SysTargetGetProcessorId", 0, 0 },\
          { (RTS_VOID_FCTPTR)SysTargetGetOperatingSystemId, "SysTargetGetOperatingSystemId", 0, 0 },\
          { (RTS_VOID_FCTPTR)SysTargetGetVendorName, "SysTargetGetVendorName", 0, 0 },\
          { (RTS_VOID_FCTPTR)SysTargetGetDeviceName, "SysTargetGetDeviceName", 0, 0 },\
          { (RTS_VOID_FCTPTR)SysTargetGetVersion, "SysTargetGetVersion", 0, 0 },\
          { (RTS_VOID_FCTPTR)SysTargetGetId, "SysTargetGetId", 0, 0 },\
          { (RTS_VOID_FCTPTR)SysTargetGetType, "SysTargetGetType", 0, 0 },\
          { (RTS_VOID_FCTPTR)SysTargetGetConfiguredNodeName, "SysTargetGetConfiguredNodeName", 0, 0 },\
          { (RTS_VOID_FCTPTR)SysTargetGetNodeName, "SysTargetGetNodeName", 0, 0 },\
                                        \
        { ((RTS_VOID_FCTPTR)(void *)0), "", 0, 0 }\
    }
#else
#define EXPORT_CMPITF_STMT \
    {\
        { ((RTS_VOID_FCTPTR)(void *)0), "", 0, 0 }\
    }
#endif
#define EXPORT_CPP_STMT


#if defined(STATIC_LINK)
    #define EXPORT_STMT\
    {\
        RTS_RESULT ExpResult;\
        if (NULL == s_pfCMRegisterAPI)\
            return ERR_NOTINITIALIZED;\
        ExpResult = s_pfCMRegisterAPI(s_ExternalsTable, 0, 1, COMPONENT_ID);\
        if (ERR_OK != ExpResult)\
            return ExpResult;\
    }
#else
    #define EXPORT_STMT\
    {\
        RTS_RESULT ExpResult;\
        if (NULL == s_pfCMRegisterAPI)\
            return ERR_NOTINITIALIZED;\
        ExpResult = s_pfCMRegisterAPI(s_ExternalsTable, 0, 1, COMPONENT_ID);\
        if (ERR_OK != ExpResult)\
            return ExpResult;\
        ExpResult = s_pfCMRegisterAPI(s_ItfTable, 0, 0, COMPONENT_ID);\
        if (ERR_OK != ExpResult)\
            return ExpResult;\
    }
#endif

#define USE_STMT \
    /*lint -save --e{528} --e{551} */ \
    static volatile PF_REGISTER_API s_pfCMRegisterAPI; \
    static volatile PF_REGISTER_API2 s_pfCMRegisterAPI2; \
    static volatile PF_GET_API s_pfCMGetAPI; \
    static volatile PF_GET_API2 s_pfCMGetAPI2; \
    static volatile PF_REGISTER_CLASS s_pfCMRegisterClass; \
    static volatile PF_CREATEINSTANCE s_pfCMCreateInstance; \
    static volatile PF_CALL_HOOK s_pfCMCallHook; \
    static const CMP_EXT_FUNCTION_REF s_ExternalsTable[] =\
    {\
        EXPORT_EXTREF_STMT\
        EXPORT_EXTREF2_STMT\
        { ((RTS_VOID_FCTPTR)(void *)0), "", 0, 0 }\
    };\
    static const CMP_EXT_FUNCTION_REF s_ItfTable[] = EXPORT_CMPITF_STMT; \
    /*lint -restore */  \
    static int CDECL ExportFunctions(void); \
    static int CDECL ImportFunctions(void); \
    static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult); \
    static RTS_RESULT CDECL DeleteInstance(IBase *pIBase); \
    static RTS_UI32 CDECL CmpGetVersion(void); \
    static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2); \
    ITF_CmpLog   \
    ITF_CMUtils  \
    USE_CMUtlMemCpy  \
    USE_LogAdd \
	ITF_CM     \
	/*obsolete entry ITF_CMUtils*/      \
	ITF_CmpSettings     \
	ITF_SysMem     \
	ITF_SysTarget     \
	ITF_SysCpuHandling     \
	ITF_CmpSIL2     \
	ITF_CmpChecksum     \
	ITF_CmpEventMgr      \
    USE_SIL2CheckCallerContext      \
    USE_CRC32Init      \
    USE_CRC32Update      \
    USE_CRC32Finish      \
    USE_EventCreate3      \
    USE_EventDelete      \
    USE_EventPost2      \
    USE_CMUtlSafeStrCpy      \
    USE_CMUtlsnprintf      \
    USE_CMUtlSafeStrCat      \
    USE_CMUtlwstrcpy      \
    USE_CMUtlwstrcat      \
    USE_CMUtlwstrlen      \
    USE_CMUtlStrToW      \
    USE_CMCheckSysTargetSignature      \
    USE_SettgGetWStringValue      \
    USE_SettgGetStringValue      \
    USE_SettgGetIntValue      \
    USE_SettgSetWStringValue      \
    USE_SettgRemoveKey      \
    USE_SysMemSwap      \
    USE_SysTargetGetConfiguredNodeName      \
    USE_SysTargetGetType      \
    USE_SysTargetGetId      \
    USE_SysTargetGetVersion     
#define USEIMPORT_STMT \
    /*lint -save --e{551} */ \
    static volatile PF_REGISTER_API s_pfCMRegisterAPI; \
    static volatile PF_REGISTER_API2 s_pfCMRegisterAPI2; \
    static volatile PF_GET_API s_pfCMGetAPI; \
    static volatile PF_GET_API2 s_pfCMGetAPI2; \
    static volatile PF_REGISTER_CLASS s_pfCMRegisterClass; \
    static volatile PF_CREATEINSTANCE s_pfCMCreateInstance; \
    static volatile PF_CALL_HOOK s_pfCMCallHook; \
    /*lint -restore */  \
    ITF_CmpLog   \
    ITF_CMUtils  \
    USE_CMUtlMemCpy  \
    USE_LogAdd \
	ITF_CM    \
	/*obsolete entry ITF_CMUtils*/     \
	ITF_CmpSettings    \
	ITF_SysMem    \
	ITF_SysTarget    \
	ITF_SysCpuHandling    \
	ITF_CmpSIL2    \
	ITF_CmpChecksum    \
	ITF_CmpEventMgr     \
    USE_SIL2CheckCallerContext      \
    USE_CRC32Init      \
    USE_CRC32Update      \
    USE_CRC32Finish      \
    USE_EventCreate3      \
    USE_EventDelete      \
    USE_EventPost2      \
    USE_CMUtlSafeStrCpy      \
    USE_CMUtlsnprintf      \
    USE_CMUtlSafeStrCat      \
    USE_CMUtlwstrcpy      \
    USE_CMUtlwstrcat      \
    USE_CMUtlwstrlen      \
    USE_CMUtlStrToW      \
    USE_CMCheckSysTargetSignature      \
    USE_SettgGetWStringValue      \
    USE_SettgGetStringValue      \
    USE_SettgGetIntValue      \
    USE_SettgSetWStringValue      \
    USE_SettgRemoveKey      \
    USE_SysMemSwap      \
    USE_SysTargetGetConfiguredNodeName      \
    USE_SysTargetGetType      \
    USE_SysTargetGetId      \
    USE_SysTargetGetVersion     
#define USEEXTERN_STMT \
    EXT_CMUtlMemCpy  \
    EXT_LogAdd \
	EXTITF_CM    \
	/*obsolete entry EXTITF_CMUtils*/     \
	EXTITF_CmpSettings    \
	EXTITF_SysMem    \
	EXTITF_SysTarget    \
	EXTITF_SysCpuHandling    \
	EXTITF_CmpSIL2    \
	EXTITF_CmpChecksum    \
	EXTITF_CmpEventMgr     \
    EXT_SIL2CheckCallerContext  \
    EXT_CRC32Init  \
    EXT_CRC32Update  \
    EXT_CRC32Finish  \
    EXT_EventCreate3  \
    EXT_EventDelete  \
    EXT_EventPost2  \
    EXT_CMUtlSafeStrCpy  \
    EXT_CMUtlsnprintf  \
    EXT_CMUtlSafeStrCat  \
    EXT_CMUtlwstrcpy  \
    EXT_CMUtlwstrcat  \
    EXT_CMUtlwstrlen  \
    EXT_CMUtlStrToW  \
    EXT_CMCheckSysTargetSignature  \
    EXT_SettgGetWStringValue  \
    EXT_SettgGetStringValue  \
    EXT_SettgGetIntValue  \
    EXT_SettgSetWStringValue  \
    EXT_SettgRemoveKey  \
    EXT_SysMemSwap  \
    EXT_SysTargetGetConfiguredNodeName  \
    EXT_SysTargetGetType  \
    EXT_SysTargetGetId  \
    EXT_SysTargetGetVersion 
#ifndef COMPONENT_NAME
    #error COMPONENT_NAME is not defined. This prevents the component from being linked statically. Use SET_COMPONENT_NAME(<name_of_your_component>) to set the name of the component in your .m4 component description.
#endif




#if defined(STATIC_LINK) || defined(MIXED_LINK) || defined(DYNAMIC_LINK) || defined(CPLUSPLUS_STATIC_LINK)
    #define ComponentEntry SysTarget__Entry
#endif


#ifdef CPLUSPLUS

class CSysTarget : public ISysTarget 
{
    public:
        CSysTarget() : hSysTarget(RTS_INVALID_HANDLE), iRefCount(0)
        {
        }
        virtual ~CSysTarget()
        {
        }
        virtual unsigned long AddRef(IBase *pIBase = NULL)
        {
            iRefCount++;
            return iRefCount;
        }
        virtual unsigned long Release(IBase *pIBase = NULL)
        {
            iRefCount--;
            if (iRefCount == 0)
            {
                delete this;
                return 0;
            }
            return iRefCount;
        }

        
        virtual void* QueryInterface(IBase *pIBase, ITFID iid, RTS_RESULT *pResult)
        {
            void *pItf;
            if (iid == ITFID_IBase)
                pItf = dynamic_cast<IBase *>((ISysTarget *)this);            
            else if (iid == ITFID_ISysTarget)
                pItf = dynamic_cast<ISysTarget *>(this); 
            else
            {
                if (pResult != NULL)
                    *pResult = ERR_NOTIMPLEMENTED;
                return NULL;
            }
            if (pResult != (RTS_RESULT *)1)
                (reinterpret_cast<IBase *>(pItf))->AddRef();
            if (pResult != NULL && pResult != (RTS_RESULT *)1)
                *pResult = ERR_OK;
            return pItf;
        }
        virtual RTS_RESULT CDECL ISysTargetGetNodeName(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength);
        virtual RTS_RESULT CDECL ISysTargetGetConfiguredNodeName(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength);
        virtual RTS_RESULT CDECL ISysTargetGetType(RTS_UI32 *pulType);
        virtual RTS_RESULT CDECL ISysTargetGetId(RTS_UI32 *pulTargetId);
        virtual RTS_RESULT CDECL ISysTargetGetVersion(RTS_UI32 *pulVersion);
        virtual RTS_RESULT CDECL ISysTargetGetDeviceName(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength);
        virtual RTS_RESULT CDECL ISysTargetGetVendorName(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength);
        virtual RTS_RESULT CDECL ISysTargetGetOperatingSystemId(RTS_UI32 *pulOperatingSystemId);
        virtual RTS_RESULT CDECL ISysTargetGetProcessorId(RTS_UI32 *pulProcessorId);
        virtual RTS_RESULT CDECL ISysTargetGetSerialNumber(char **ppszSerialNumber, RTS_I32 *pnMaxLen);
        virtual RTS_RESULT CDECL ISysTargetGetSerialNumber_Secure(char **ppszSerialNumber, RTS_I32 *pnMaxLen);
        virtual RTS_RESULT CDECL ISysTargetGetSignature(RTS_UI32 ulChallenge, RTS_UI32 *pulSignature);
        virtual RTS_RESULT CDECL ISysTargetGetDeviceMask(RTS_UI16 *pusDeviceMask);
        virtual RTS_RESULT CDECL ISysTargetCheckIdent(SysTargetIdent *pTargetIdentReq, SysTargetIdent *pTargetIdent);
        virtual RTS_RESULT CDECL ISysTargetGetAPI(API_RESOLVE_INFO apiInfo, RTS_VOID_FCTPTR *ppfAPIFunction);
        virtual RTS_RESULT CDECL ISysTargetSetNodeName(RTS_WCHAR *pwszName);

    public:
        RTS_HANDLE hSysTarget;
        int iRefCount;
};

#endif /*CPLUSPLUS*/
#ifdef RTS_COMPACT_MICRO
/* SysTarget Declarations for uRTS */
/* This header is included only to have the CMP_EXT_FUNCTION_REF type definition. */
/* In final version this type could be moved to CmpItf.h, if we will use */
/* the same structure for representing an export entry. */
#include <_OptionalIncludes/Profiles/uRTS/CMMicro.h>

/* Undefine these macros if they were previously defined */

#ifdef USE_HOOK_FUNCTION
#undef USE_HOOK_FUNCTION
#endif

#ifdef USE_CMEXPORTFUNCTIONS
#undef USE_CMEXPORTFUNCTIONS
#endif

#ifdef USE_EXPORT_EXTREF
#undef USE_EXPORT_EXTREF
#endif

#ifdef USE_EXPORT_CMPITF
#undef USE_EXPORT_CMPITF
#endif

#ifdef USE_ENTRY_LINKAGE
#undef USE_ENTRY_LINKAGE
#endif

#ifdef IMPLEMENT_EXPORT_FUNCTIONS
#undef IMPLEMENT_EXPORT_FUNCTIONS
#endif

#ifdef IMPLEMENT_IMPORT_FUNCTIONS
#undef IMPLEMENT_IMPORT_FUNCTIONS
#endif

#ifdef IMPLEMENT_GETVERSION_FUNCTIONS
#undef IMPLEMENT_GETVERSION_FUNCTIONS
#endif

#ifdef EXPORT_STMT
#undef EXPORT_STMT
#endif

#ifdef USEEXTERN_STMT
#undef USEEXTERN_STMT
#endif

#ifdef USE_STMT
#undef USE_STMT
#endif

#ifdef USEIMPORT_STMT
#undef USEIMPORT_STMT
#endif

/* This wrapper is only required in uRTS */
#define USE_HOOK_FUNCTION	RTS_RESULT SysTarget_HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)\
{\
	return HookFunction(ulHook, ulParam1, ulParam2);\
}

/******************************************************************************/
/* No s_pfCMExportFunctions in uRTS */
#define USE_CMEXPORTFUNCTIONS

/* Exports table to IEC */
#define USE_EXPORT_EXTREF const CMP_EXT_FUNCTION_REF SysTarget_ExternalsTable[] = \
	{\
		EXPORT_EXTREF_STMT\
		EXPORT_EXTREF2_STMT\
		{ ((RTS_VOID_FCTPTR)(void *)0), "", 0 }\
	};

/* No component interface exports in uRTS */
#define USE_EXPORT_CMPITF

/* No dynamic linkage in uRTS */
#define USE_ENTRY_LINKAGE

/* No ExportFunctions() routine in uRTS */
#define IMPLEMENT_EXPORT_FUNCTIONS

/* No ImportFunctions() routine in uRTS */
#define IMPLEMENT_IMPORT_FUNCTIONS

/* No CmpGetVersion() routine in uRTS */
#define IMPLEMENT_GETVERSION_FUNCTIONS

/* No usage of externals from the component secondary C-modules in uRTS */
#define USEEXTERN_STMT

/* No need for export calling to the Component Manager in uRTS */
#define EXPORT_STMT

/* No need for importing from secondary C-modules */
#define USEIMPORT_STMT

/* Instantiation macro for a root component C-module */
#define USE_STMT\
	static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);\
		USE_EXPORT_EXTREF;\
		USE_EXPORT_CMPITF;\
		USE_HOOK_FUNCTION;\
		USE_CMEXPORTFUNCTIONS;\


/******************************************************************************/
#endif

#endif /*WIN32_RESOURCES*/
#endif /*_DEP_H_*/
