 /**
 * <interfacename>SysModRTSub</interfacename>
 * <description> 
 *
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */
 

	
	
#ifndef _SYSMODRTSUBITF_H_
#define _SYSMODRTSUBITF_H_

#include "CmpStd.h"

 

 




#include "SysModRTMainItf.h"
#include "SysFlashItf.h"
#include "SysTimeItf.h"

#include "CmpItf.h"

/**
 * <category>Static defines</category>
 * <description>Memory address of SysModRTSubFunctionTable</description>
 */
#ifndef MODRTSUB_FUNCTION_TABLE_ADDRESS
	#error MODRTSUB_FUNCTION_TABLE_ADDRESS not defined!!
#endif

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

typedef void (CDECL *PFMODRTSUBINIT)(void);
void ModRTSubInit(void);

typedef void (CDECL *PFMODRTSUBCOMMCYCLE)(void);
void ModRTSubCommCycle(void);


typedef struct
{
	PFMODRTSUBINIT pfModRTSubInit;
	PFMODRTSUBCOMMCYCLE pfModRTSubCommCycle;
} SysModRTSubFunctionTable;

/**
 * <description>
 *  Interface wrapper function to ModRTMain.
 *	Erases a block of flash memory. You must erase a flash area before writing to it.
 *  This function is implemented in the generic part of SysFlash and splits up the block to erase in several smaller pieces with the
 *  maximum size of EraseBlockSize. For each piece SysFlashErase_() and the CommCycleHook is called, to keep the rest of the RTS 
 *  also on single-tasking systems alive. 
 * </description>
 * <param name="fa" type="IN" range="[FA_UNKNOWN,FA_FILE,FA_CODE]">Flash area that shall be used for the operation. Now, FA_CODE and FA_FILE are defined.</param>
 * <param name="ulSize" type="IN" range="[0,VALID_FLASH_SIZE,INVALID_FLASH_SIZE]">Size of flash area to erase</param>
 * <param name="ulOffset" type="IN" range="[0,VALID_FLASH_OFFSET,INVALID_FLASH_OFFSET]">Offset of flash area to erase. The function adds the start address of the flash to calculate the physical address of the area.</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Flash erase was successful</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOT_SUPPORTED">Type of Flasharea is not supported</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">size or offset wrong</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Flash could not be erased </errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL ModRTMainSysFlashErase(FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset);
typedef RTS_RESULT (CDECL * PFMODRTMAINSYSFLASHERASE) (FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset);
#if defined(SYSMODRTSUB_NOTIMPLEMENTED) || defined(MODRTMAINSYSFLASHERASE_NOTIMPLEMENTED)
	#define USE_ModRTMainSysFlashErase
	#define EXT_ModRTMainSysFlashErase
	#define GET_ModRTMainSysFlashErase(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ModRTMainSysFlashErase(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_ModRTMainSysFlashErase  FALSE
	#define EXP_ModRTMainSysFlashErase  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ModRTMainSysFlashErase
	#define EXT_ModRTMainSysFlashErase
	#define GET_ModRTMainSysFlashErase(fl)  CAL_CMGETAPI( "ModRTMainSysFlashErase" ) 
	#define CAL_ModRTMainSysFlashErase  ModRTMainSysFlashErase
	#define CHK_ModRTMainSysFlashErase  TRUE
	#define EXP_ModRTMainSysFlashErase  CAL_CMEXPAPI( "ModRTMainSysFlashErase" ) 
#elif defined(MIXED_LINK) && !defined(SYSMODRTSUB_EXTERNAL)
	#define USE_ModRTMainSysFlashErase
	#define EXT_ModRTMainSysFlashErase
	#define GET_ModRTMainSysFlashErase(fl)  CAL_CMGETAPI( "ModRTMainSysFlashErase" ) 
	#define CAL_ModRTMainSysFlashErase  ModRTMainSysFlashErase
	#define CHK_ModRTMainSysFlashErase  TRUE
	#define EXP_ModRTMainSysFlashErase  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ModRTMainSysFlashErase", (RTS_UINTPTR)ModRTMainSysFlashErase, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysModRTSubModRTMainSysFlashErase
	#define EXT_SysModRTSubModRTMainSysFlashErase
	#define GET_SysModRTSubModRTMainSysFlashErase  ERR_OK
	#define CAL_SysModRTSubModRTMainSysFlashErase pISysModRTSub->IModRTMainSysFlashErase
	#define CHK_SysModRTSubModRTMainSysFlashErase (pISysModRTSub != NULL)
	#define EXP_SysModRTSubModRTMainSysFlashErase  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ModRTMainSysFlashErase
	#define EXT_ModRTMainSysFlashErase
	#define GET_ModRTMainSysFlashErase(fl)  CAL_CMGETAPI( "ModRTMainSysFlashErase" ) 
	#define CAL_ModRTMainSysFlashErase pISysModRTSub->IModRTMainSysFlashErase
	#define CHK_ModRTMainSysFlashErase (pISysModRTSub != NULL)
	#define EXP_ModRTMainSysFlashErase  CAL_CMEXPAPI( "ModRTMainSysFlashErase" ) 
#else /* DYNAMIC_LINK */
	#define USE_ModRTMainSysFlashErase  PFMODRTMAINSYSFLASHERASE pfModRTMainSysFlashErase;
	#define EXT_ModRTMainSysFlashErase  extern PFMODRTMAINSYSFLASHERASE pfModRTMainSysFlashErase;
	#define GET_ModRTMainSysFlashErase(fl)  s_pfCMGetAPI2( "ModRTMainSysFlashErase", (RTS_VOID_FCTPTR *)&pfModRTMainSysFlashErase, (fl), 0, 0)
	#define CAL_ModRTMainSysFlashErase  pfModRTMainSysFlashErase
	#define CHK_ModRTMainSysFlashErase  (pfModRTMainSysFlashErase != NULL)
	#define EXP_ModRTMainSysFlashErase  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ModRTMainSysFlashErase", (RTS_UINTPTR)ModRTMainSysFlashErase, 0, 0) 
#endif




/**
 * <description>
 *  Interface wrapper function to ModRTMain. 
 *	Writes a block of data to the flash. The flash area has to be erased first with SysFlashErase.
 *  This function is implemented in the generic part of SysFlash and splits up the block to write in several smaller pieces with the
 *  maximum size of WriteBlockSize. For each piece SysFlashWrite() and the CommCycleHook is called, to keep the rest of the RTS 
 *  also on single-tasking systems alive.
 * </description>
 * <param name="fa" type="IN" range="[FA_UNKNOWN,FA_FILE,FA_CODE]">Flash area that shall be used for the operation. Now, FA_CODE and FA_FILE are defined.</param>
 * <param name="pcSource" type="IN" range="[0,INVALID_SRC_BUFFER,VALID_SRC_BUFFER]">Pointer to buffer that contains the data</param>
 * <param name="ulSize" type="IN" range="[0,VALID_BUFFER_SIZE,INVALID_BUFFER_SIZE]">Size of the buffer</param>
 * <param name="ulOffset" type="IN" range="[0,VALID_FLASH_OFFSET,INVALID_FLASH_OFFSET]">Offset of flash area to write to. The function adds the start address of the flash to calculate the physical address of the area.</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Flash read was successful</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOT_SUPPORTED">Type of Flasharea is not supported</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">pcSrc,size or offset wrong or null</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Flash could not be read </errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL ModRTMainSysFlashWrite(FlashArea fa, char *pcSource, RTS_SIZE ulSize, RTS_SIZE ulOffset);
typedef RTS_RESULT (CDECL * PFMODRTMAINSYSFLASHWRITE) (FlashArea fa, char *pcSource, RTS_SIZE ulSize, RTS_SIZE ulOffset);
#if defined(SYSMODRTSUB_NOTIMPLEMENTED) || defined(MODRTMAINSYSFLASHWRITE_NOTIMPLEMENTED)
	#define USE_ModRTMainSysFlashWrite
	#define EXT_ModRTMainSysFlashWrite
	#define GET_ModRTMainSysFlashWrite(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ModRTMainSysFlashWrite(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_ModRTMainSysFlashWrite  FALSE
	#define EXP_ModRTMainSysFlashWrite  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ModRTMainSysFlashWrite
	#define EXT_ModRTMainSysFlashWrite
	#define GET_ModRTMainSysFlashWrite(fl)  CAL_CMGETAPI( "ModRTMainSysFlashWrite" ) 
	#define CAL_ModRTMainSysFlashWrite  ModRTMainSysFlashWrite
	#define CHK_ModRTMainSysFlashWrite  TRUE
	#define EXP_ModRTMainSysFlashWrite  CAL_CMEXPAPI( "ModRTMainSysFlashWrite" ) 
#elif defined(MIXED_LINK) && !defined(SYSMODRTSUB_EXTERNAL)
	#define USE_ModRTMainSysFlashWrite
	#define EXT_ModRTMainSysFlashWrite
	#define GET_ModRTMainSysFlashWrite(fl)  CAL_CMGETAPI( "ModRTMainSysFlashWrite" ) 
	#define CAL_ModRTMainSysFlashWrite  ModRTMainSysFlashWrite
	#define CHK_ModRTMainSysFlashWrite  TRUE
	#define EXP_ModRTMainSysFlashWrite  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ModRTMainSysFlashWrite", (RTS_UINTPTR)ModRTMainSysFlashWrite, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysModRTSubModRTMainSysFlashWrite
	#define EXT_SysModRTSubModRTMainSysFlashWrite
	#define GET_SysModRTSubModRTMainSysFlashWrite  ERR_OK
	#define CAL_SysModRTSubModRTMainSysFlashWrite pISysModRTSub->IModRTMainSysFlashWrite
	#define CHK_SysModRTSubModRTMainSysFlashWrite (pISysModRTSub != NULL)
	#define EXP_SysModRTSubModRTMainSysFlashWrite  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ModRTMainSysFlashWrite
	#define EXT_ModRTMainSysFlashWrite
	#define GET_ModRTMainSysFlashWrite(fl)  CAL_CMGETAPI( "ModRTMainSysFlashWrite" ) 
	#define CAL_ModRTMainSysFlashWrite pISysModRTSub->IModRTMainSysFlashWrite
	#define CHK_ModRTMainSysFlashWrite (pISysModRTSub != NULL)
	#define EXP_ModRTMainSysFlashWrite  CAL_CMEXPAPI( "ModRTMainSysFlashWrite" ) 
#else /* DYNAMIC_LINK */
	#define USE_ModRTMainSysFlashWrite  PFMODRTMAINSYSFLASHWRITE pfModRTMainSysFlashWrite;
	#define EXT_ModRTMainSysFlashWrite  extern PFMODRTMAINSYSFLASHWRITE pfModRTMainSysFlashWrite;
	#define GET_ModRTMainSysFlashWrite(fl)  s_pfCMGetAPI2( "ModRTMainSysFlashWrite", (RTS_VOID_FCTPTR *)&pfModRTMainSysFlashWrite, (fl), 0, 0)
	#define CAL_ModRTMainSysFlashWrite  pfModRTMainSysFlashWrite
	#define CHK_ModRTMainSysFlashWrite  (pfModRTMainSysFlashWrite != NULL)
	#define EXP_ModRTMainSysFlashWrite  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ModRTMainSysFlashWrite", (RTS_UINTPTR)ModRTMainSysFlashWrite, 0, 0) 
#endif




/**
 * <description>
 *  Interface wrapper function to ModRTMain.
 *	Called when a file that was opened for writing is closed. 
 *  This function is implemented in the generic part of SysFlash and splits up the block to flush in several smaller pieces with the
 *  maximum size of FlushBlockSize. For each piece SysFlashFlush() and the CommCycleHook is called, to keep the rest of the RTS 
 *  also on single-tasking systems alive.
 * </description>
 * <param name="fa" type="IN" range="[FA_UNKNOWN,FA_FILE,FA_CODE]">Flash area that shall be used for the operation. Now, FA_CODE and FA_FILE are defined.</param>
 * <param name="ulSize" type="IN" range="[0,VALID_BUFFER_SIZE,INVALID_BUFFER_SIZE]">Size of the buffer</param>
 * <param name="ulOffset" type="IN" range="[0,VALID_FLASH_OFFSET,INVALID_FLASH_OFFSET]">Offset of flash area to write to. The function adds the start address of the flash to calculate the physical address of the area.</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Flash flush was successful</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOT_SUPPORTED">Type of Flasharea is not supported</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">size or offset wrong or null</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Flash could not be flushed </errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL ModRTMainSysFlashFlush(FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset);
typedef RTS_RESULT (CDECL * PFMODRTMAINSYSFLASHFLUSH) (FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset);
#if defined(SYSMODRTSUB_NOTIMPLEMENTED) || defined(MODRTMAINSYSFLASHFLUSH_NOTIMPLEMENTED)
	#define USE_ModRTMainSysFlashFlush
	#define EXT_ModRTMainSysFlashFlush
	#define GET_ModRTMainSysFlashFlush(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ModRTMainSysFlashFlush(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_ModRTMainSysFlashFlush  FALSE
	#define EXP_ModRTMainSysFlashFlush  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ModRTMainSysFlashFlush
	#define EXT_ModRTMainSysFlashFlush
	#define GET_ModRTMainSysFlashFlush(fl)  CAL_CMGETAPI( "ModRTMainSysFlashFlush" ) 
	#define CAL_ModRTMainSysFlashFlush  ModRTMainSysFlashFlush
	#define CHK_ModRTMainSysFlashFlush  TRUE
	#define EXP_ModRTMainSysFlashFlush  CAL_CMEXPAPI( "ModRTMainSysFlashFlush" ) 
#elif defined(MIXED_LINK) && !defined(SYSMODRTSUB_EXTERNAL)
	#define USE_ModRTMainSysFlashFlush
	#define EXT_ModRTMainSysFlashFlush
	#define GET_ModRTMainSysFlashFlush(fl)  CAL_CMGETAPI( "ModRTMainSysFlashFlush" ) 
	#define CAL_ModRTMainSysFlashFlush  ModRTMainSysFlashFlush
	#define CHK_ModRTMainSysFlashFlush  TRUE
	#define EXP_ModRTMainSysFlashFlush  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ModRTMainSysFlashFlush", (RTS_UINTPTR)ModRTMainSysFlashFlush, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysModRTSubModRTMainSysFlashFlush
	#define EXT_SysModRTSubModRTMainSysFlashFlush
	#define GET_SysModRTSubModRTMainSysFlashFlush  ERR_OK
	#define CAL_SysModRTSubModRTMainSysFlashFlush pISysModRTSub->IModRTMainSysFlashFlush
	#define CHK_SysModRTSubModRTMainSysFlashFlush (pISysModRTSub != NULL)
	#define EXP_SysModRTSubModRTMainSysFlashFlush  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ModRTMainSysFlashFlush
	#define EXT_ModRTMainSysFlashFlush
	#define GET_ModRTMainSysFlashFlush(fl)  CAL_CMGETAPI( "ModRTMainSysFlashFlush" ) 
	#define CAL_ModRTMainSysFlashFlush pISysModRTSub->IModRTMainSysFlashFlush
	#define CHK_ModRTMainSysFlashFlush (pISysModRTSub != NULL)
	#define EXP_ModRTMainSysFlashFlush  CAL_CMEXPAPI( "ModRTMainSysFlashFlush" ) 
#else /* DYNAMIC_LINK */
	#define USE_ModRTMainSysFlashFlush  PFMODRTMAINSYSFLASHFLUSH pfModRTMainSysFlashFlush;
	#define EXT_ModRTMainSysFlashFlush  extern PFMODRTMAINSYSFLASHFLUSH pfModRTMainSysFlashFlush;
	#define GET_ModRTMainSysFlashFlush(fl)  s_pfCMGetAPI2( "ModRTMainSysFlashFlush", (RTS_VOID_FCTPTR *)&pfModRTMainSysFlashFlush, (fl), 0, 0)
	#define CAL_ModRTMainSysFlashFlush  pfModRTMainSysFlashFlush
	#define CHK_ModRTMainSysFlashFlush  (pfModRTMainSysFlashFlush != NULL)
	#define EXP_ModRTMainSysFlashFlush  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ModRTMainSysFlashFlush", (RTS_UINTPTR)ModRTMainSysFlashFlush, 0, 0) 
#endif




/**
 * <description>
 * <p>Interface wrapper function to ModRTMain.</p>
 * <p>Return a monotonic, rising millisecond tick.</p>
 * </description> 
 * <result>Returns the millisecond tick</result>
 */
RTS_UI32 CDECL ModRTMainSysTimeGetMs(void);
typedef RTS_UI32 (CDECL * PFMODRTMAINSYSTIMEGETMS) (void);
#if defined(SYSMODRTSUB_NOTIMPLEMENTED) || defined(MODRTMAINSYSTIMEGETMS_NOTIMPLEMENTED)
	#define USE_ModRTMainSysTimeGetMs
	#define EXT_ModRTMainSysTimeGetMs
	#define GET_ModRTMainSysTimeGetMs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ModRTMainSysTimeGetMs()  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_ModRTMainSysTimeGetMs  FALSE
	#define EXP_ModRTMainSysTimeGetMs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ModRTMainSysTimeGetMs
	#define EXT_ModRTMainSysTimeGetMs
	#define GET_ModRTMainSysTimeGetMs(fl)  CAL_CMGETAPI( "ModRTMainSysTimeGetMs" ) 
	#define CAL_ModRTMainSysTimeGetMs  ModRTMainSysTimeGetMs
	#define CHK_ModRTMainSysTimeGetMs  TRUE
	#define EXP_ModRTMainSysTimeGetMs  CAL_CMEXPAPI( "ModRTMainSysTimeGetMs" ) 
#elif defined(MIXED_LINK) && !defined(SYSMODRTSUB_EXTERNAL)
	#define USE_ModRTMainSysTimeGetMs
	#define EXT_ModRTMainSysTimeGetMs
	#define GET_ModRTMainSysTimeGetMs(fl)  CAL_CMGETAPI( "ModRTMainSysTimeGetMs" ) 
	#define CAL_ModRTMainSysTimeGetMs  ModRTMainSysTimeGetMs
	#define CHK_ModRTMainSysTimeGetMs  TRUE
	#define EXP_ModRTMainSysTimeGetMs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ModRTMainSysTimeGetMs", (RTS_UINTPTR)ModRTMainSysTimeGetMs, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysModRTSubModRTMainSysTimeGetMs
	#define EXT_SysModRTSubModRTMainSysTimeGetMs
	#define GET_SysModRTSubModRTMainSysTimeGetMs  ERR_OK
	#define CAL_SysModRTSubModRTMainSysTimeGetMs pISysModRTSub->IModRTMainSysTimeGetMs
	#define CHK_SysModRTSubModRTMainSysTimeGetMs (pISysModRTSub != NULL)
	#define EXP_SysModRTSubModRTMainSysTimeGetMs  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ModRTMainSysTimeGetMs
	#define EXT_ModRTMainSysTimeGetMs
	#define GET_ModRTMainSysTimeGetMs(fl)  CAL_CMGETAPI( "ModRTMainSysTimeGetMs" ) 
	#define CAL_ModRTMainSysTimeGetMs pISysModRTSub->IModRTMainSysTimeGetMs
	#define CHK_ModRTMainSysTimeGetMs (pISysModRTSub != NULL)
	#define EXP_ModRTMainSysTimeGetMs  CAL_CMEXPAPI( "ModRTMainSysTimeGetMs" ) 
#else /* DYNAMIC_LINK */
	#define USE_ModRTMainSysTimeGetMs  PFMODRTMAINSYSTIMEGETMS pfModRTMainSysTimeGetMs;
	#define EXT_ModRTMainSysTimeGetMs  extern PFMODRTMAINSYSTIMEGETMS pfModRTMainSysTimeGetMs;
	#define GET_ModRTMainSysTimeGetMs(fl)  s_pfCMGetAPI2( "ModRTMainSysTimeGetMs", (RTS_VOID_FCTPTR *)&pfModRTMainSysTimeGetMs, (fl), 0, 0)
	#define CAL_ModRTMainSysTimeGetMs  pfModRTMainSysTimeGetMs
	#define CHK_ModRTMainSysTimeGetMs  (pfModRTMainSysTimeGetMs != NULL)
	#define EXP_ModRTMainSysTimeGetMs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ModRTMainSysTimeGetMs", (RTS_UINTPTR)ModRTMainSysTimeGetMs, 0, 0) 
#endif




/**
 * <description>
 * <p>Interface wrapper function to ModRTMain.</p>
 * <p>Return a monotonic, rising microsecond tick.</p>
 * </description>
 * <param name="pTime" type="INOUT" range="[NULL,VALID_PTIME]">Pointer to the time tick result</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Time was returned successfully</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pTime was NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Internal Error</errorcode>
 */
RTS_RESULT CDECL ModRTMainSysTimeGetUs(RTS_SYSTIME* pTime);
typedef RTS_RESULT (CDECL * PFMODRTMAINSYSTIMEGETUS) (RTS_SYSTIME* pTime);
#if defined(SYSMODRTSUB_NOTIMPLEMENTED) || defined(MODRTMAINSYSTIMEGETUS_NOTIMPLEMENTED)
	#define USE_ModRTMainSysTimeGetUs
	#define EXT_ModRTMainSysTimeGetUs
	#define GET_ModRTMainSysTimeGetUs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ModRTMainSysTimeGetUs(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_ModRTMainSysTimeGetUs  FALSE
	#define EXP_ModRTMainSysTimeGetUs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ModRTMainSysTimeGetUs
	#define EXT_ModRTMainSysTimeGetUs
	#define GET_ModRTMainSysTimeGetUs(fl)  CAL_CMGETAPI( "ModRTMainSysTimeGetUs" ) 
	#define CAL_ModRTMainSysTimeGetUs  ModRTMainSysTimeGetUs
	#define CHK_ModRTMainSysTimeGetUs  TRUE
	#define EXP_ModRTMainSysTimeGetUs  CAL_CMEXPAPI( "ModRTMainSysTimeGetUs" ) 
#elif defined(MIXED_LINK) && !defined(SYSMODRTSUB_EXTERNAL)
	#define USE_ModRTMainSysTimeGetUs
	#define EXT_ModRTMainSysTimeGetUs
	#define GET_ModRTMainSysTimeGetUs(fl)  CAL_CMGETAPI( "ModRTMainSysTimeGetUs" ) 
	#define CAL_ModRTMainSysTimeGetUs  ModRTMainSysTimeGetUs
	#define CHK_ModRTMainSysTimeGetUs  TRUE
	#define EXP_ModRTMainSysTimeGetUs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ModRTMainSysTimeGetUs", (RTS_UINTPTR)ModRTMainSysTimeGetUs, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysModRTSubModRTMainSysTimeGetUs
	#define EXT_SysModRTSubModRTMainSysTimeGetUs
	#define GET_SysModRTSubModRTMainSysTimeGetUs  ERR_OK
	#define CAL_SysModRTSubModRTMainSysTimeGetUs pISysModRTSub->IModRTMainSysTimeGetUs
	#define CHK_SysModRTSubModRTMainSysTimeGetUs (pISysModRTSub != NULL)
	#define EXP_SysModRTSubModRTMainSysTimeGetUs  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ModRTMainSysTimeGetUs
	#define EXT_ModRTMainSysTimeGetUs
	#define GET_ModRTMainSysTimeGetUs(fl)  CAL_CMGETAPI( "ModRTMainSysTimeGetUs" ) 
	#define CAL_ModRTMainSysTimeGetUs pISysModRTSub->IModRTMainSysTimeGetUs
	#define CHK_ModRTMainSysTimeGetUs (pISysModRTSub != NULL)
	#define EXP_ModRTMainSysTimeGetUs  CAL_CMEXPAPI( "ModRTMainSysTimeGetUs" ) 
#else /* DYNAMIC_LINK */
	#define USE_ModRTMainSysTimeGetUs  PFMODRTMAINSYSTIMEGETUS pfModRTMainSysTimeGetUs;
	#define EXT_ModRTMainSysTimeGetUs  extern PFMODRTMAINSYSTIMEGETUS pfModRTMainSysTimeGetUs;
	#define GET_ModRTMainSysTimeGetUs(fl)  s_pfCMGetAPI2( "ModRTMainSysTimeGetUs", (RTS_VOID_FCTPTR *)&pfModRTMainSysTimeGetUs, (fl), 0, 0)
	#define CAL_ModRTMainSysTimeGetUs  pfModRTMainSysTimeGetUs
	#define CHK_ModRTMainSysTimeGetUs  (pfModRTMainSysTimeGetUs != NULL)
	#define EXP_ModRTMainSysTimeGetUs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ModRTMainSysTimeGetUs", (RTS_UINTPTR)ModRTMainSysTimeGetUs, 0, 0) 
#endif




/**
 * <description>
 * <p>Interface wrapper function to ModRTMain.</p>
 * <p>Return a monotonic, rising nanosecond tick.</p>
 * </description>
 * <param name="pTime" type="INOUT" range="[NULL,VALID_PTIME]">Pointer to the time tick result</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Time was returned successfully</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">pTime was NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Internal Error</errorcode>
 */
RTS_RESULT CDECL ModRTMainSysTimeGetNs(RTS_SYSTIME* pTime);
typedef RTS_RESULT (CDECL * PFMODRTMAINSYSTIMEGETNS) (RTS_SYSTIME* pTime);
#if defined(SYSMODRTSUB_NOTIMPLEMENTED) || defined(MODRTMAINSYSTIMEGETNS_NOTIMPLEMENTED)
	#define USE_ModRTMainSysTimeGetNs
	#define EXT_ModRTMainSysTimeGetNs
	#define GET_ModRTMainSysTimeGetNs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ModRTMainSysTimeGetNs(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_ModRTMainSysTimeGetNs  FALSE
	#define EXP_ModRTMainSysTimeGetNs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ModRTMainSysTimeGetNs
	#define EXT_ModRTMainSysTimeGetNs
	#define GET_ModRTMainSysTimeGetNs(fl)  CAL_CMGETAPI( "ModRTMainSysTimeGetNs" ) 
	#define CAL_ModRTMainSysTimeGetNs  ModRTMainSysTimeGetNs
	#define CHK_ModRTMainSysTimeGetNs  TRUE
	#define EXP_ModRTMainSysTimeGetNs  CAL_CMEXPAPI( "ModRTMainSysTimeGetNs" ) 
#elif defined(MIXED_LINK) && !defined(SYSMODRTSUB_EXTERNAL)
	#define USE_ModRTMainSysTimeGetNs
	#define EXT_ModRTMainSysTimeGetNs
	#define GET_ModRTMainSysTimeGetNs(fl)  CAL_CMGETAPI( "ModRTMainSysTimeGetNs" ) 
	#define CAL_ModRTMainSysTimeGetNs  ModRTMainSysTimeGetNs
	#define CHK_ModRTMainSysTimeGetNs  TRUE
	#define EXP_ModRTMainSysTimeGetNs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ModRTMainSysTimeGetNs", (RTS_UINTPTR)ModRTMainSysTimeGetNs, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysModRTSubModRTMainSysTimeGetNs
	#define EXT_SysModRTSubModRTMainSysTimeGetNs
	#define GET_SysModRTSubModRTMainSysTimeGetNs  ERR_OK
	#define CAL_SysModRTSubModRTMainSysTimeGetNs pISysModRTSub->IModRTMainSysTimeGetNs
	#define CHK_SysModRTSubModRTMainSysTimeGetNs (pISysModRTSub != NULL)
	#define EXP_SysModRTSubModRTMainSysTimeGetNs  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ModRTMainSysTimeGetNs
	#define EXT_ModRTMainSysTimeGetNs
	#define GET_ModRTMainSysTimeGetNs(fl)  CAL_CMGETAPI( "ModRTMainSysTimeGetNs" ) 
	#define CAL_ModRTMainSysTimeGetNs pISysModRTSub->IModRTMainSysTimeGetNs
	#define CHK_ModRTMainSysTimeGetNs (pISysModRTSub != NULL)
	#define EXP_ModRTMainSysTimeGetNs  CAL_CMEXPAPI( "ModRTMainSysTimeGetNs" ) 
#else /* DYNAMIC_LINK */
	#define USE_ModRTMainSysTimeGetNs  PFMODRTMAINSYSTIMEGETNS pfModRTMainSysTimeGetNs;
	#define EXT_ModRTMainSysTimeGetNs  extern PFMODRTMAINSYSTIMEGETNS pfModRTMainSysTimeGetNs;
	#define GET_ModRTMainSysTimeGetNs(fl)  s_pfCMGetAPI2( "ModRTMainSysTimeGetNs", (RTS_VOID_FCTPTR *)&pfModRTMainSysTimeGetNs, (fl), 0, 0)
	#define CAL_ModRTMainSysTimeGetNs  pfModRTMainSysTimeGetNs
	#define CHK_ModRTMainSysTimeGetNs  (pfModRTMainSysTimeGetNs != NULL)
	#define EXP_ModRTMainSysTimeGetNs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ModRTMainSysTimeGetNs", (RTS_UINTPTR)ModRTMainSysTimeGetNs, 0, 0) 
#endif





/** EXTERN LIB SECTION END **/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFMODRTMAINSYSFLASHERASE IModRTMainSysFlashErase;
 	PFMODRTMAINSYSFLASHWRITE IModRTMainSysFlashWrite;
 	PFMODRTMAINSYSFLASHFLUSH IModRTMainSysFlashFlush;
 	PFMODRTMAINSYSTIMEGETMS IModRTMainSysTimeGetMs;
 	PFMODRTMAINSYSTIMEGETUS IModRTMainSysTimeGetUs;
 	PFMODRTMAINSYSTIMEGETNS IModRTMainSysTimeGetNs;
 } ISysModRTSub_C;

#ifdef CPLUSPLUS
class ISysModRTSub : public IBase
{
	public:
		virtual RTS_RESULT CDECL IModRTMainSysFlashErase(FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset) =0;
		virtual RTS_RESULT CDECL IModRTMainSysFlashWrite(FlashArea fa, char *pcSource, RTS_SIZE ulSize, RTS_SIZE ulOffset) =0;
		virtual RTS_RESULT CDECL IModRTMainSysFlashFlush(FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset) =0;
		virtual RTS_UI32 CDECL IModRTMainSysTimeGetMs(void) =0;
		virtual RTS_RESULT CDECL IModRTMainSysTimeGetUs(RTS_SYSTIME* pTime) =0;
		virtual RTS_RESULT CDECL IModRTMainSysTimeGetNs(RTS_SYSTIME* pTime) =0;
};
	#ifndef ITF_SysModRTSub
		#define ITF_SysModRTSub static ISysModRTSub *pISysModRTSub = NULL;
	#endif
	#define EXTITF_SysModRTSub
#else	/*CPLUSPLUS*/
	typedef ISysModRTSub_C		ISysModRTSub;
	#ifndef ITF_SysModRTSub
		#define ITF_SysModRTSub
	#endif
	#define EXTITF_SysModRTSub
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSMODRTSUBITF_H_*/
