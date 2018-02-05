 /**
 * <interfacename>SysFlash</interfacename>
 * <description> 
 *	<p>The SysFlash interface is projected to get access to flash memory of a controller.
 *	It has to be adpated to your flash.</p>
 *	<p>There are functions to read and write to flash memory. It is used by some implementations
 *	of the file component (SysFileFlash) to store some files in flash, and by the 
 *	application component for execution of user code in flash. 
 *  The SysFlash Component divides two different kinds of flash areas:
 *  FA_CODE and FA_FILE. FA_FILE is only needed, if SysFileFlash is used.
 *  Please see further description for SysFileFlash and our Flash-Filesystem.
 *	Please note that the offsets of the files have to correspond with sector borders of the flash. One file should be
 *	stored in one sector.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSFLASHITF_H_
#define _SYSFLASHITF_H_

#include "CmpStd.h"

 

 




#include "CmpStd.h"

#ifndef CDECL
	#define CDECL
#endif


/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Max. size of a block, which is erased in one piece. If a block exceeds this size, the erase operation
 *  is splitted up into several calls of SysFlashErase_(), each limited to this value. 
 *  Should be set to a size, which is erased in below 1 second, because the CommCycleHook is called after
 *  each block to keep the rest of the RTS alive.  
 * </description>
 */
#define SYSFLASH_KEY_INT_ERASE_BLOCK_SIZE					"EraseBlockSize"
#ifndef SYSFLASH_VALUE_INT_ERASE_BLOCK_SIZE_DEFAULT
	#define SYSFLASH_VALUE_INT_ERASE_BLOCK_SIZE_DEFAULT		INT32_C(0x1000)
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Max. size of a block, which is read in one piece. If a block exceeds this size, the erase operation
 *  is splitted up into several calls of SysFlashRead_(), each limited to this value. 
 *  Should be set to a size, which is read in below 1 second, because the CommCycleHook is called after
 *  each block to keep the rest of the RTS alive.  
 * </description>
 */
#define SYSFLASH_KEY_INT_READ_BLOCK_SIZE					"ReadBlockSize"
#ifndef SYSFLASH_VALUE_INT_READ_BLOCK_SIZE_DEFAULT
	#define SYSFLASH_VALUE_INT_READ_BLOCK_SIZE_DEFAULT		INT32_C(0x10000)
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Max. size of a block, which is written in one piece. If a block exceeds this size, the write operation
 *  is splitted up into several calls of SysFlashWrite_(), each limited to this value. 
 *  Should be set to a size, which is written in below 1 second, because the CommCycleHook is called after
 *  each block to keep the rest of the RTS alive.  
 * </description>
 */
#define SYSFLASH_KEY_INT_WRITE_BLOCK_SIZE					"WriteBlockSize"
#ifndef SYSFLASH_VALUE_INT_WRITE_BLOCK_SIZE_DEFAULT
	#define SYSFLASH_VALUE_INT_WRITE_BLOCK_SIZE_DEFAULT		INT32_C(0x1000)
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Max. size of a block, which is flushed in one piece. If a block exceeds this size, the flush operation
 *  is splitted up into several calls of SysFlashFlush_(), each limited to this value. 
 *  Should be set to a size, which is flushed in below 1 second, because the CommCycleHook is called after
 *  each block to keep the rest of the RTS alive.  
 * </description>
 */
#define SYSFLASH_KEY_INT_FLUSH_BLOCK_SIZE					"FlushBlockSize"
#ifndef SYSFLASH_VALUE_INT_FLUSH_BLOCK_SIZE_DEFAULT
	#define SYSFLASH_VALUE_INT_FLUSH_BLOCK_SIZE_DEFAULT		INT32_C(0x10000000)
#endif


#ifdef __cplusplus
extern "C" {
#endif

typedef enum tagFlashArea
{
	FA_UNKNOWN,
	FA_FILE,
	FA_CODE
} FlashArea;

#define MAX_FILENAME 32
typedef struct FILE_DESCtag
{
	char szFileName[MAX_FILENAME+1];
	RTS_SIZE ulOffset;
	RTS_SIZE ulMaxSize;
	RTS_SIZE ulWritePos;
	RTS_SIZE ulReadPos;
} FILE_DESC;


/* Init routines for OS specific modules */
RTS_RESULT CDECL SysFlashOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysFlashOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>
 *	Init the flash system
 * </description>
 * <param name="fa" type="IN" range="[FA_UNKNOWN,FA_FILE,FA_CODE]">Flash area that shall be used for the operation. Now, FA_CODE and FA_FILE are defined.</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Flash init was successful</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOT_SUPPORTED">Type of Flasharea is not supported</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Flash could not be initialized </errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysFlashInit(FlashArea fa);
typedef RTS_RESULT (CDECL * PFSYSFLASHINIT) (FlashArea fa);
#if defined(SYSFLASH_NOTIMPLEMENTED) || defined(SYSFLASHINIT_NOTIMPLEMENTED)
	#define USE_SysFlashInit
	#define EXT_SysFlashInit
	#define GET_SysFlashInit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFlashInit(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysFlashInit  FALSE
	#define EXP_SysFlashInit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFlashInit
	#define EXT_SysFlashInit
	#define GET_SysFlashInit(fl)  CAL_CMGETAPI( "SysFlashInit" ) 
	#define CAL_SysFlashInit  SysFlashInit
	#define CHK_SysFlashInit  TRUE
	#define EXP_SysFlashInit  CAL_CMEXPAPI( "SysFlashInit" ) 
#elif defined(MIXED_LINK) && !defined(SYSFLASH_EXTERNAL)
	#define USE_SysFlashInit
	#define EXT_SysFlashInit
	#define GET_SysFlashInit(fl)  CAL_CMGETAPI( "SysFlashInit" ) 
	#define CAL_SysFlashInit  SysFlashInit
	#define CHK_SysFlashInit  TRUE
	#define EXP_SysFlashInit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFlashInit", (RTS_UINTPTR)SysFlashInit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFlashSysFlashInit
	#define EXT_SysFlashSysFlashInit
	#define GET_SysFlashSysFlashInit  ERR_OK
	#define CAL_SysFlashSysFlashInit pISysFlash->ISysFlashInit
	#define CHK_SysFlashSysFlashInit (pISysFlash != NULL)
	#define EXP_SysFlashSysFlashInit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFlashInit
	#define EXT_SysFlashInit
	#define GET_SysFlashInit(fl)  CAL_CMGETAPI( "SysFlashInit" ) 
	#define CAL_SysFlashInit pISysFlash->ISysFlashInit
	#define CHK_SysFlashInit (pISysFlash != NULL)
	#define EXP_SysFlashInit  CAL_CMEXPAPI( "SysFlashInit" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFlashInit  PFSYSFLASHINIT pfSysFlashInit;
	#define EXT_SysFlashInit  extern PFSYSFLASHINIT pfSysFlashInit;
	#define GET_SysFlashInit(fl)  s_pfCMGetAPI2( "SysFlashInit", (RTS_VOID_FCTPTR *)&pfSysFlashInit, (fl), 0, 0)
	#define CAL_SysFlashInit  pfSysFlashInit
	#define CHK_SysFlashInit  (pfSysFlashInit != NULL)
	#define EXP_SysFlashInit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFlashInit", (RTS_UINTPTR)SysFlashInit, 0, 0) 
#endif




/**
 * <description>
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
RTS_RESULT CDECL SysFlashErase(FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset);
typedef RTS_RESULT (CDECL * PFSYSFLASHERASE) (FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset);
#if defined(SYSFLASH_NOTIMPLEMENTED) || defined(SYSFLASHERASE_NOTIMPLEMENTED)
	#define USE_SysFlashErase
	#define EXT_SysFlashErase
	#define GET_SysFlashErase(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFlashErase(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysFlashErase  FALSE
	#define EXP_SysFlashErase  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFlashErase
	#define EXT_SysFlashErase
	#define GET_SysFlashErase(fl)  CAL_CMGETAPI( "SysFlashErase" ) 
	#define CAL_SysFlashErase  SysFlashErase
	#define CHK_SysFlashErase  TRUE
	#define EXP_SysFlashErase  CAL_CMEXPAPI( "SysFlashErase" ) 
#elif defined(MIXED_LINK) && !defined(SYSFLASH_EXTERNAL)
	#define USE_SysFlashErase
	#define EXT_SysFlashErase
	#define GET_SysFlashErase(fl)  CAL_CMGETAPI( "SysFlashErase" ) 
	#define CAL_SysFlashErase  SysFlashErase
	#define CHK_SysFlashErase  TRUE
	#define EXP_SysFlashErase  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFlashErase", (RTS_UINTPTR)SysFlashErase, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFlashSysFlashErase
	#define EXT_SysFlashSysFlashErase
	#define GET_SysFlashSysFlashErase  ERR_OK
	#define CAL_SysFlashSysFlashErase pISysFlash->ISysFlashErase
	#define CHK_SysFlashSysFlashErase (pISysFlash != NULL)
	#define EXP_SysFlashSysFlashErase  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFlashErase
	#define EXT_SysFlashErase
	#define GET_SysFlashErase(fl)  CAL_CMGETAPI( "SysFlashErase" ) 
	#define CAL_SysFlashErase pISysFlash->ISysFlashErase
	#define CHK_SysFlashErase (pISysFlash != NULL)
	#define EXP_SysFlashErase  CAL_CMEXPAPI( "SysFlashErase" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFlashErase  PFSYSFLASHERASE pfSysFlashErase;
	#define EXT_SysFlashErase  extern PFSYSFLASHERASE pfSysFlashErase;
	#define GET_SysFlashErase(fl)  s_pfCMGetAPI2( "SysFlashErase", (RTS_VOID_FCTPTR *)&pfSysFlashErase, (fl), 0, 0)
	#define CAL_SysFlashErase  pfSysFlashErase
	#define CHK_SysFlashErase  (pfSysFlashErase != NULL)
	#define EXP_SysFlashErase  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFlashErase", (RTS_UINTPTR)SysFlashErase, 0, 0) 
#endif




/**
 * <description>
 *	Reads a block of memory from the flash.
 *  This function is implemented in the generic part of SysFlash and splits up the block to read in several smaller pieces with the
 *  maximum size of ReadBlockSize. For each piece SysFlashRead_() and the CommCycleHook is called, to keep the rest of the RTS 
 *  also on single-tasking systems alive.
 * </description>
 * <param name="fa" type="IN" range="[FA_UNKNOWN,FA_FILE,FA_CODE]">Flash area that shall be used for the operation. Now, FA_CODE and FA_FILE are defined.</param>
 * <param name="pcDest" type="IN" range="[0,INVALID_DEST_BUFFER,VALID_DEST_BUFFER]">Pointer to buffer that receives the data</param>
 * <param name="ulSize" type="IN" range="[0,VALID_BUFFER_SIZE,INVALID_BUFFER_SIZE]">Size of the buffer</param>
 * <param name="ulOffset" type="IN" range="[0,VALID_FLASH_OFFSET,INVALID_FLASH_OFFSET]">Offset of flash area to read from. The function adds the start address of the flash to calculate the physical address of the area.</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Flash read was successful</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOT_SUPPORTED">Type of Flasharea is not supported</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">pcDest,size or offset wrong or null</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Flash could not be read </errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysFlashRead(FlashArea fa, char *pcDest, RTS_SIZE ulSize, RTS_SIZE ulOffset);
typedef RTS_RESULT (CDECL * PFSYSFLASHREAD) (FlashArea fa, char *pcDest, RTS_SIZE ulSize, RTS_SIZE ulOffset);
#if defined(SYSFLASH_NOTIMPLEMENTED) || defined(SYSFLASHREAD_NOTIMPLEMENTED)
	#define USE_SysFlashRead
	#define EXT_SysFlashRead
	#define GET_SysFlashRead(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFlashRead(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysFlashRead  FALSE
	#define EXP_SysFlashRead  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFlashRead
	#define EXT_SysFlashRead
	#define GET_SysFlashRead(fl)  CAL_CMGETAPI( "SysFlashRead" ) 
	#define CAL_SysFlashRead  SysFlashRead
	#define CHK_SysFlashRead  TRUE
	#define EXP_SysFlashRead  CAL_CMEXPAPI( "SysFlashRead" ) 
#elif defined(MIXED_LINK) && !defined(SYSFLASH_EXTERNAL)
	#define USE_SysFlashRead
	#define EXT_SysFlashRead
	#define GET_SysFlashRead(fl)  CAL_CMGETAPI( "SysFlashRead" ) 
	#define CAL_SysFlashRead  SysFlashRead
	#define CHK_SysFlashRead  TRUE
	#define EXP_SysFlashRead  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFlashRead", (RTS_UINTPTR)SysFlashRead, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFlashSysFlashRead
	#define EXT_SysFlashSysFlashRead
	#define GET_SysFlashSysFlashRead  ERR_OK
	#define CAL_SysFlashSysFlashRead pISysFlash->ISysFlashRead
	#define CHK_SysFlashSysFlashRead (pISysFlash != NULL)
	#define EXP_SysFlashSysFlashRead  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFlashRead
	#define EXT_SysFlashRead
	#define GET_SysFlashRead(fl)  CAL_CMGETAPI( "SysFlashRead" ) 
	#define CAL_SysFlashRead pISysFlash->ISysFlashRead
	#define CHK_SysFlashRead (pISysFlash != NULL)
	#define EXP_SysFlashRead  CAL_CMEXPAPI( "SysFlashRead" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFlashRead  PFSYSFLASHREAD pfSysFlashRead;
	#define EXT_SysFlashRead  extern PFSYSFLASHREAD pfSysFlashRead;
	#define GET_SysFlashRead(fl)  s_pfCMGetAPI2( "SysFlashRead", (RTS_VOID_FCTPTR *)&pfSysFlashRead, (fl), 0, 0)
	#define CAL_SysFlashRead  pfSysFlashRead
	#define CHK_SysFlashRead  (pfSysFlashRead != NULL)
	#define EXP_SysFlashRead  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFlashRead", (RTS_UINTPTR)SysFlashRead, 0, 0) 
#endif




/**
 * <description>
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
RTS_RESULT CDECL SysFlashWrite(FlashArea fa, char *pcSource, RTS_SIZE ulSize, RTS_SIZE ulOffset);
typedef RTS_RESULT (CDECL * PFSYSFLASHWRITE) (FlashArea fa, char *pcSource, RTS_SIZE ulSize, RTS_SIZE ulOffset);
#if defined(SYSFLASH_NOTIMPLEMENTED) || defined(SYSFLASHWRITE_NOTIMPLEMENTED)
	#define USE_SysFlashWrite
	#define EXT_SysFlashWrite
	#define GET_SysFlashWrite(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFlashWrite(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysFlashWrite  FALSE
	#define EXP_SysFlashWrite  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFlashWrite
	#define EXT_SysFlashWrite
	#define GET_SysFlashWrite(fl)  CAL_CMGETAPI( "SysFlashWrite" ) 
	#define CAL_SysFlashWrite  SysFlashWrite
	#define CHK_SysFlashWrite  TRUE
	#define EXP_SysFlashWrite  CAL_CMEXPAPI( "SysFlashWrite" ) 
#elif defined(MIXED_LINK) && !defined(SYSFLASH_EXTERNAL)
	#define USE_SysFlashWrite
	#define EXT_SysFlashWrite
	#define GET_SysFlashWrite(fl)  CAL_CMGETAPI( "SysFlashWrite" ) 
	#define CAL_SysFlashWrite  SysFlashWrite
	#define CHK_SysFlashWrite  TRUE
	#define EXP_SysFlashWrite  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFlashWrite", (RTS_UINTPTR)SysFlashWrite, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFlashSysFlashWrite
	#define EXT_SysFlashSysFlashWrite
	#define GET_SysFlashSysFlashWrite  ERR_OK
	#define CAL_SysFlashSysFlashWrite pISysFlash->ISysFlashWrite
	#define CHK_SysFlashSysFlashWrite (pISysFlash != NULL)
	#define EXP_SysFlashSysFlashWrite  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFlashWrite
	#define EXT_SysFlashWrite
	#define GET_SysFlashWrite(fl)  CAL_CMGETAPI( "SysFlashWrite" ) 
	#define CAL_SysFlashWrite pISysFlash->ISysFlashWrite
	#define CHK_SysFlashWrite (pISysFlash != NULL)
	#define EXP_SysFlashWrite  CAL_CMEXPAPI( "SysFlashWrite" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFlashWrite  PFSYSFLASHWRITE pfSysFlashWrite;
	#define EXT_SysFlashWrite  extern PFSYSFLASHWRITE pfSysFlashWrite;
	#define GET_SysFlashWrite(fl)  s_pfCMGetAPI2( "SysFlashWrite", (RTS_VOID_FCTPTR *)&pfSysFlashWrite, (fl), 0, 0)
	#define CAL_SysFlashWrite  pfSysFlashWrite
	#define CHK_SysFlashWrite  (pfSysFlashWrite != NULL)
	#define EXP_SysFlashWrite  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFlashWrite", (RTS_UINTPTR)SysFlashWrite, 0, 0) 
#endif




/**
 * <description>
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
RTS_RESULT CDECL SysFlashFlush(FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset);
typedef RTS_RESULT (CDECL * PFSYSFLASHFLUSH) (FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset);
#if defined(SYSFLASH_NOTIMPLEMENTED) || defined(SYSFLASHFLUSH_NOTIMPLEMENTED)
	#define USE_SysFlashFlush
	#define EXT_SysFlashFlush
	#define GET_SysFlashFlush(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFlashFlush(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysFlashFlush  FALSE
	#define EXP_SysFlashFlush  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFlashFlush
	#define EXT_SysFlashFlush
	#define GET_SysFlashFlush(fl)  CAL_CMGETAPI( "SysFlashFlush" ) 
	#define CAL_SysFlashFlush  SysFlashFlush
	#define CHK_SysFlashFlush  TRUE
	#define EXP_SysFlashFlush  CAL_CMEXPAPI( "SysFlashFlush" ) 
#elif defined(MIXED_LINK) && !defined(SYSFLASH_EXTERNAL)
	#define USE_SysFlashFlush
	#define EXT_SysFlashFlush
	#define GET_SysFlashFlush(fl)  CAL_CMGETAPI( "SysFlashFlush" ) 
	#define CAL_SysFlashFlush  SysFlashFlush
	#define CHK_SysFlashFlush  TRUE
	#define EXP_SysFlashFlush  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFlashFlush", (RTS_UINTPTR)SysFlashFlush, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFlashSysFlashFlush
	#define EXT_SysFlashSysFlashFlush
	#define GET_SysFlashSysFlashFlush  ERR_OK
	#define CAL_SysFlashSysFlashFlush pISysFlash->ISysFlashFlush
	#define CHK_SysFlashSysFlashFlush (pISysFlash != NULL)
	#define EXP_SysFlashSysFlashFlush  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFlashFlush
	#define EXT_SysFlashFlush
	#define GET_SysFlashFlush(fl)  CAL_CMGETAPI( "SysFlashFlush" ) 
	#define CAL_SysFlashFlush pISysFlash->ISysFlashFlush
	#define CHK_SysFlashFlush (pISysFlash != NULL)
	#define EXP_SysFlashFlush  CAL_CMEXPAPI( "SysFlashFlush" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFlashFlush  PFSYSFLASHFLUSH pfSysFlashFlush;
	#define EXT_SysFlashFlush  extern PFSYSFLASHFLUSH pfSysFlashFlush;
	#define GET_SysFlashFlush(fl)  s_pfCMGetAPI2( "SysFlashFlush", (RTS_VOID_FCTPTR *)&pfSysFlashFlush, (fl), 0, 0)
	#define CAL_SysFlashFlush  pfSysFlashFlush
	#define CHK_SysFlashFlush  (pfSysFlashFlush != NULL)
	#define EXP_SysFlashFlush  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFlashFlush", (RTS_UINTPTR)SysFlashFlush, 0, 0) 
#endif




/**
 * <description>
 *	Retrieve the physical address of a flash area
 * </description>
 * <param name="fa" type="IN" range="[FA_UNKNOWN,FA_FILE,FA_CODE]">Flash area that shall be used for the operation. Now, FA_CODE and FA_FILE are defined.</param>
 * <parampseudo name="bWriteFlashPattern" type="IN" range="[TRUE,FALSE]">A pattern was written to the flash, using SysFlashWrite(), before the call to SysFlashGetPhysicalAddress().</parampseudo>
 * <parampseudo name="bWriteMemoryPattern" type="IN" range="[TRUE,FALSE]">A pattern was written to the flash, using direct memory access, before the call to SysFlashGetPhysicalAddress().</parampseudo>
 * <parampseudo name="bFlashFlush" type="IN" range="[TRUE,FALSE]">SysFlashFlush() was called before the call to SysFlashGetPhysicalAddress().</parampseudo>
 * <parampseudo name="bExceptionGenerated" type="OUT" range="[TRUE,FALSE]">An exception was generated.</parampseudo>
 * <parampseudo name="bPatternExists" type="OUT" range="[TRUE,FALSE]">The pattern could be read, using standard memory access.</parampseudo>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Startaddress was successful retrieved</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOT_SUPPORTED">Type of Flasharea is not supported</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">Startaddress could not be retrieved</errorcode>
 * <result>Physical address of flash area</result>
 */
RTS_UINTPTR CDECL SysFlashGetPhysicalAddress(FlashArea fa, RTS_RESULT *pResult);
typedef RTS_UINTPTR (CDECL * PFSYSFLASHGETPHYSICALADDRESS) (FlashArea fa, RTS_RESULT *pResult);
#if defined(SYSFLASH_NOTIMPLEMENTED) || defined(SYSFLASHGETPHYSICALADDRESS_NOTIMPLEMENTED)
	#define USE_SysFlashGetPhysicalAddress
	#define EXT_SysFlashGetPhysicalAddress
	#define GET_SysFlashGetPhysicalAddress(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFlashGetPhysicalAddress(p0,p1)  (RTS_UINTPTR)ERR_NOTIMPLEMENTED
	#define CHK_SysFlashGetPhysicalAddress  FALSE
	#define EXP_SysFlashGetPhysicalAddress  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFlashGetPhysicalAddress
	#define EXT_SysFlashGetPhysicalAddress
	#define GET_SysFlashGetPhysicalAddress(fl)  CAL_CMGETAPI( "SysFlashGetPhysicalAddress" ) 
	#define CAL_SysFlashGetPhysicalAddress  SysFlashGetPhysicalAddress
	#define CHK_SysFlashGetPhysicalAddress  TRUE
	#define EXP_SysFlashGetPhysicalAddress  CAL_CMEXPAPI( "SysFlashGetPhysicalAddress" ) 
#elif defined(MIXED_LINK) && !defined(SYSFLASH_EXTERNAL)
	#define USE_SysFlashGetPhysicalAddress
	#define EXT_SysFlashGetPhysicalAddress
	#define GET_SysFlashGetPhysicalAddress(fl)  CAL_CMGETAPI( "SysFlashGetPhysicalAddress" ) 
	#define CAL_SysFlashGetPhysicalAddress  SysFlashGetPhysicalAddress
	#define CHK_SysFlashGetPhysicalAddress  TRUE
	#define EXP_SysFlashGetPhysicalAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFlashGetPhysicalAddress", (RTS_UINTPTR)SysFlashGetPhysicalAddress, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFlashSysFlashGetPhysicalAddress
	#define EXT_SysFlashSysFlashGetPhysicalAddress
	#define GET_SysFlashSysFlashGetPhysicalAddress  ERR_OK
	#define CAL_SysFlashSysFlashGetPhysicalAddress pISysFlash->ISysFlashGetPhysicalAddress
	#define CHK_SysFlashSysFlashGetPhysicalAddress (pISysFlash != NULL)
	#define EXP_SysFlashSysFlashGetPhysicalAddress  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFlashGetPhysicalAddress
	#define EXT_SysFlashGetPhysicalAddress
	#define GET_SysFlashGetPhysicalAddress(fl)  CAL_CMGETAPI( "SysFlashGetPhysicalAddress" ) 
	#define CAL_SysFlashGetPhysicalAddress pISysFlash->ISysFlashGetPhysicalAddress
	#define CHK_SysFlashGetPhysicalAddress (pISysFlash != NULL)
	#define EXP_SysFlashGetPhysicalAddress  CAL_CMEXPAPI( "SysFlashGetPhysicalAddress" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFlashGetPhysicalAddress  PFSYSFLASHGETPHYSICALADDRESS pfSysFlashGetPhysicalAddress;
	#define EXT_SysFlashGetPhysicalAddress  extern PFSYSFLASHGETPHYSICALADDRESS pfSysFlashGetPhysicalAddress;
	#define GET_SysFlashGetPhysicalAddress(fl)  s_pfCMGetAPI2( "SysFlashGetPhysicalAddress", (RTS_VOID_FCTPTR *)&pfSysFlashGetPhysicalAddress, (fl), 0, 0)
	#define CAL_SysFlashGetPhysicalAddress  pfSysFlashGetPhysicalAddress
	#define CHK_SysFlashGetPhysicalAddress  (pfSysFlashGetPhysicalAddress != NULL)
	#define EXP_SysFlashGetPhysicalAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFlashGetPhysicalAddress", (RTS_UINTPTR)SysFlashGetPhysicalAddress, 0, 0) 
#endif




/**
 * <description>
 *	Retrieve the size of a flash area
 * </description>
 * <param name="fa" type="IN" range="[FA_UNKNOWN,FA_FILE,FA_CODE]">Flash area that shall be used for the operation. Now, FA_CODE and FA_FILE are defined.</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Flashsize was successful retrieved</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOT_SUPPORTED">Type of Flasharea is not supported</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">Flashsize could not be retrieved</errorcode>
 * <result>Size of flash area</result>
 */
RTS_SIZE CDECL SysFlashGetSize(FlashArea fa, RTS_RESULT *pResult);
typedef RTS_SIZE (CDECL * PFSYSFLASHGETSIZE) (FlashArea fa, RTS_RESULT *pResult);
#if defined(SYSFLASH_NOTIMPLEMENTED) || defined(SYSFLASHGETSIZE_NOTIMPLEMENTED)
	#define USE_SysFlashGetSize
	#define EXT_SysFlashGetSize
	#define GET_SysFlashGetSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFlashGetSize(p0,p1)  (RTS_SIZE)ERR_NOTIMPLEMENTED
	#define CHK_SysFlashGetSize  FALSE
	#define EXP_SysFlashGetSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFlashGetSize
	#define EXT_SysFlashGetSize
	#define GET_SysFlashGetSize(fl)  CAL_CMGETAPI( "SysFlashGetSize" ) 
	#define CAL_SysFlashGetSize  SysFlashGetSize
	#define CHK_SysFlashGetSize  TRUE
	#define EXP_SysFlashGetSize  CAL_CMEXPAPI( "SysFlashGetSize" ) 
#elif defined(MIXED_LINK) && !defined(SYSFLASH_EXTERNAL)
	#define USE_SysFlashGetSize
	#define EXT_SysFlashGetSize
	#define GET_SysFlashGetSize(fl)  CAL_CMGETAPI( "SysFlashGetSize" ) 
	#define CAL_SysFlashGetSize  SysFlashGetSize
	#define CHK_SysFlashGetSize  TRUE
	#define EXP_SysFlashGetSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFlashGetSize", (RTS_UINTPTR)SysFlashGetSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFlashSysFlashGetSize
	#define EXT_SysFlashSysFlashGetSize
	#define GET_SysFlashSysFlashGetSize  ERR_OK
	#define CAL_SysFlashSysFlashGetSize pISysFlash->ISysFlashGetSize
	#define CHK_SysFlashSysFlashGetSize (pISysFlash != NULL)
	#define EXP_SysFlashSysFlashGetSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFlashGetSize
	#define EXT_SysFlashGetSize
	#define GET_SysFlashGetSize(fl)  CAL_CMGETAPI( "SysFlashGetSize" ) 
	#define CAL_SysFlashGetSize pISysFlash->ISysFlashGetSize
	#define CHK_SysFlashGetSize (pISysFlash != NULL)
	#define EXP_SysFlashGetSize  CAL_CMEXPAPI( "SysFlashGetSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFlashGetSize  PFSYSFLASHGETSIZE pfSysFlashGetSize;
	#define EXT_SysFlashGetSize  extern PFSYSFLASHGETSIZE pfSysFlashGetSize;
	#define GET_SysFlashGetSize(fl)  s_pfCMGetAPI2( "SysFlashGetSize", (RTS_VOID_FCTPTR *)&pfSysFlashGetSize, (fl), 0, 0)
	#define CAL_SysFlashGetSize  pfSysFlashGetSize
	#define CHK_SysFlashGetSize  (pfSysFlashGetSize != NULL)
	#define EXP_SysFlashGetSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFlashGetSize", (RTS_UINTPTR)SysFlashGetSize, 0, 0) 
#endif




/**
 * <description>
 *	Erases a block of flash memory. You must erase a flash area before writing to it. The content of the flash area should be erased with 0 or ff.
 *  Must be implemented in the OS-specific part of SysFlash. Should only be called by SysFlashErase().
 * </description>
 * <param name="fa" type="IN" range="[FA_UNKNOWN,FA_FILE,FA_CODE]">Flash area that shall be used for the operation. Now, FA_CODE and FA_FILE are defined.</param>
 * <param name="ulSize" type="IN" range="[0,VALID_BUFFER_SIZE,INVALID_BUFFER_SIZE]">Size of flash area to erase</param>
 * <param name="ulOffset" type="IN" range="[0,VALID_FLASH_OFFSET,INVALID_FLASH_OFFSET]">Offset of flash area to erase. The function adds the start address of the flash to calculate the physical address of the area.</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Flash was successfully erased</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOT_SUPPORTED">Type of Flasharea is not supported</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Size or Offset is not correct</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">Flash could not be erased</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysFlashErase_(FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset);
typedef RTS_RESULT (CDECL * PFSYSFLASHERASE_) (FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset);
#if defined(SYSFLASH_NOTIMPLEMENTED) || defined(SYSFLASHERASE__NOTIMPLEMENTED)
	#define USE_SysFlashErase_
	#define EXT_SysFlashErase_
	#define GET_SysFlashErase_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFlashErase_(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysFlashErase_  FALSE
	#define EXP_SysFlashErase_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFlashErase_
	#define EXT_SysFlashErase_
	#define GET_SysFlashErase_(fl)  CAL_CMGETAPI( "SysFlashErase_" ) 
	#define CAL_SysFlashErase_  SysFlashErase_
	#define CHK_SysFlashErase_  TRUE
	#define EXP_SysFlashErase_  CAL_CMEXPAPI( "SysFlashErase_" ) 
#elif defined(MIXED_LINK) && !defined(SYSFLASH_EXTERNAL)
	#define USE_SysFlashErase_
	#define EXT_SysFlashErase_
	#define GET_SysFlashErase_(fl)  CAL_CMGETAPI( "SysFlashErase_" ) 
	#define CAL_SysFlashErase_  SysFlashErase_
	#define CHK_SysFlashErase_  TRUE
	#define EXP_SysFlashErase_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFlashErase_", (RTS_UINTPTR)SysFlashErase_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFlashSysFlashErase_
	#define EXT_SysFlashSysFlashErase_
	#define GET_SysFlashSysFlashErase_  ERR_OK
	#define CAL_SysFlashSysFlashErase_ pISysFlash->ISysFlashErase_
	#define CHK_SysFlashSysFlashErase_ (pISysFlash != NULL)
	#define EXP_SysFlashSysFlashErase_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFlashErase_
	#define EXT_SysFlashErase_
	#define GET_SysFlashErase_(fl)  CAL_CMGETAPI( "SysFlashErase_" ) 
	#define CAL_SysFlashErase_ pISysFlash->ISysFlashErase_
	#define CHK_SysFlashErase_ (pISysFlash != NULL)
	#define EXP_SysFlashErase_  CAL_CMEXPAPI( "SysFlashErase_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFlashErase_  PFSYSFLASHERASE_ pfSysFlashErase_;
	#define EXT_SysFlashErase_  extern PFSYSFLASHERASE_ pfSysFlashErase_;
	#define GET_SysFlashErase_(fl)  s_pfCMGetAPI2( "SysFlashErase_", (RTS_VOID_FCTPTR *)&pfSysFlashErase_, (fl), 0, 0)
	#define CAL_SysFlashErase_  pfSysFlashErase_
	#define CHK_SysFlashErase_  (pfSysFlashErase_ != NULL)
	#define EXP_SysFlashErase_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFlashErase_", (RTS_UINTPTR)SysFlashErase_, 0, 0) 
#endif




/**
 * <description>
 *	Reads a block of memory from the flash.
 *  Must be implemented in the OS-specific part of SysFlash. Should only be called by SysFlashRead().
 * </description>
 * <param name="fa" type="IN" range="[FA_UNKNOWN,FA_FILE,FA_CODE]">Flash area that shall be used for the operation. Now, FA_CODE and FA_FILE are defined.</param>
 * <param name="pcDest" type="IN" range="[0,INVALID_DEST_BUFFER,VALID_DEST_BUFFER]">Pointer to buffer that receives the data</param>
 * <param name="ulSize" type="IN" range="[0,VALID_BUFFER_SIZE,INVALID_BUFFER_SIZE]">Size of the buffer</param>
 * <param name="ulOffset" type="IN" range="[0,VALID_FLASH_OFFSET,INVALID_FLASH_OFFSET]">Offset of flash area to read from. The function adds the start address of the flash to calculate the physical address of the area.</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Flash was successfully read</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOT_SUPPORTED">Type of Flasharea is not supported</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Size or Offset is not correct</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">Flash could not be read</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysFlashRead_(FlashArea fa, char *pcDest, RTS_SIZE ulSize, RTS_SIZE ulOffset);
typedef RTS_RESULT (CDECL * PFSYSFLASHREAD_) (FlashArea fa, char *pcDest, RTS_SIZE ulSize, RTS_SIZE ulOffset);
#if defined(SYSFLASH_NOTIMPLEMENTED) || defined(SYSFLASHREAD__NOTIMPLEMENTED)
	#define USE_SysFlashRead_
	#define EXT_SysFlashRead_
	#define GET_SysFlashRead_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFlashRead_(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysFlashRead_  FALSE
	#define EXP_SysFlashRead_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFlashRead_
	#define EXT_SysFlashRead_
	#define GET_SysFlashRead_(fl)  CAL_CMGETAPI( "SysFlashRead_" ) 
	#define CAL_SysFlashRead_  SysFlashRead_
	#define CHK_SysFlashRead_  TRUE
	#define EXP_SysFlashRead_  CAL_CMEXPAPI( "SysFlashRead_" ) 
#elif defined(MIXED_LINK) && !defined(SYSFLASH_EXTERNAL)
	#define USE_SysFlashRead_
	#define EXT_SysFlashRead_
	#define GET_SysFlashRead_(fl)  CAL_CMGETAPI( "SysFlashRead_" ) 
	#define CAL_SysFlashRead_  SysFlashRead_
	#define CHK_SysFlashRead_  TRUE
	#define EXP_SysFlashRead_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFlashRead_", (RTS_UINTPTR)SysFlashRead_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFlashSysFlashRead_
	#define EXT_SysFlashSysFlashRead_
	#define GET_SysFlashSysFlashRead_  ERR_OK
	#define CAL_SysFlashSysFlashRead_ pISysFlash->ISysFlashRead_
	#define CHK_SysFlashSysFlashRead_ (pISysFlash != NULL)
	#define EXP_SysFlashSysFlashRead_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFlashRead_
	#define EXT_SysFlashRead_
	#define GET_SysFlashRead_(fl)  CAL_CMGETAPI( "SysFlashRead_" ) 
	#define CAL_SysFlashRead_ pISysFlash->ISysFlashRead_
	#define CHK_SysFlashRead_ (pISysFlash != NULL)
	#define EXP_SysFlashRead_  CAL_CMEXPAPI( "SysFlashRead_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFlashRead_  PFSYSFLASHREAD_ pfSysFlashRead_;
	#define EXT_SysFlashRead_  extern PFSYSFLASHREAD_ pfSysFlashRead_;
	#define GET_SysFlashRead_(fl)  s_pfCMGetAPI2( "SysFlashRead_", (RTS_VOID_FCTPTR *)&pfSysFlashRead_, (fl), 0, 0)
	#define CAL_SysFlashRead_  pfSysFlashRead_
	#define CHK_SysFlashRead_  (pfSysFlashRead_ != NULL)
	#define EXP_SysFlashRead_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFlashRead_", (RTS_UINTPTR)SysFlashRead_, 0, 0) 
#endif




/**
 * <description>
 *	Writes a block of data to the flash. The flash area has to be erased first with SysFlashErase.
 *  Must be implemented in the OS-specific part of SysFlash. Should only be called by SysFlashWrite().
 * </description>
 * <param name="fa" type="IN" range="[FA_UNKNOWN,FA_FILE,FA_CODE]">Flash area that shall be used for the operation. Now, FA_CODE and FA_FILE are defined.</param>
 * <param name="pcSource" type="IN" range="[0,INVALID_SRC_BUFFER,VALID_SRC_BUFFER]">Pointer to buffer that contains the data</param>
 * <param name="ulSize" type="IN" range="[0,VALID_BUFFER_SIZE,INVALID_BUFFER_SIZE]">Size of the buffer</param>
 * <param name="ulOffset" type="IN" range="[0,VALID_FLASH_OFFSET,INVALID_FLASH_OFFSET]">Offset of flash area to write to. The function adds the start address of the flash to calculate the physical address of the area.</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Flash was successfully written</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOT_SUPPORTED">Type of Flasharea is not supported</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Size or Offset is not correct</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">Flash could not be written</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysFlashWrite_(FlashArea fa, char *pcSource, RTS_SIZE ulSize, RTS_SIZE ulOffset);
typedef RTS_RESULT (CDECL * PFSYSFLASHWRITE_) (FlashArea fa, char *pcSource, RTS_SIZE ulSize, RTS_SIZE ulOffset);
#if defined(SYSFLASH_NOTIMPLEMENTED) || defined(SYSFLASHWRITE__NOTIMPLEMENTED)
	#define USE_SysFlashWrite_
	#define EXT_SysFlashWrite_
	#define GET_SysFlashWrite_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFlashWrite_(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysFlashWrite_  FALSE
	#define EXP_SysFlashWrite_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFlashWrite_
	#define EXT_SysFlashWrite_
	#define GET_SysFlashWrite_(fl)  CAL_CMGETAPI( "SysFlashWrite_" ) 
	#define CAL_SysFlashWrite_  SysFlashWrite_
	#define CHK_SysFlashWrite_  TRUE
	#define EXP_SysFlashWrite_  CAL_CMEXPAPI( "SysFlashWrite_" ) 
#elif defined(MIXED_LINK) && !defined(SYSFLASH_EXTERNAL)
	#define USE_SysFlashWrite_
	#define EXT_SysFlashWrite_
	#define GET_SysFlashWrite_(fl)  CAL_CMGETAPI( "SysFlashWrite_" ) 
	#define CAL_SysFlashWrite_  SysFlashWrite_
	#define CHK_SysFlashWrite_  TRUE
	#define EXP_SysFlashWrite_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFlashWrite_", (RTS_UINTPTR)SysFlashWrite_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFlashSysFlashWrite_
	#define EXT_SysFlashSysFlashWrite_
	#define GET_SysFlashSysFlashWrite_  ERR_OK
	#define CAL_SysFlashSysFlashWrite_ pISysFlash->ISysFlashWrite_
	#define CHK_SysFlashSysFlashWrite_ (pISysFlash != NULL)
	#define EXP_SysFlashSysFlashWrite_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFlashWrite_
	#define EXT_SysFlashWrite_
	#define GET_SysFlashWrite_(fl)  CAL_CMGETAPI( "SysFlashWrite_" ) 
	#define CAL_SysFlashWrite_ pISysFlash->ISysFlashWrite_
	#define CHK_SysFlashWrite_ (pISysFlash != NULL)
	#define EXP_SysFlashWrite_  CAL_CMEXPAPI( "SysFlashWrite_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFlashWrite_  PFSYSFLASHWRITE_ pfSysFlashWrite_;
	#define EXT_SysFlashWrite_  extern PFSYSFLASHWRITE_ pfSysFlashWrite_;
	#define GET_SysFlashWrite_(fl)  s_pfCMGetAPI2( "SysFlashWrite_", (RTS_VOID_FCTPTR *)&pfSysFlashWrite_, (fl), 0, 0)
	#define CAL_SysFlashWrite_  pfSysFlashWrite_
	#define CHK_SysFlashWrite_  (pfSysFlashWrite_ != NULL)
	#define EXP_SysFlashWrite_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFlashWrite_", (RTS_UINTPTR)SysFlashWrite_, 0, 0) 
#endif




/**
 * <description>
 *	Called when a file that was opened for writing is closed. Normally, this function can be left empty.
 *	It can be useful, if the data is not written to flash directly, but buffered in RAM. The call of this function indicates
 *	that the file is closed and the data has to be written to flash.
 *  Must be implemented in the OS-specific part of SysFlash. Should only be called by SysFlashFlush().
 * </description>
 * <param name="fa" type="IN" range="[FA_UNKNOWN,FA_FILE,FA_CODE]">Flash area that shall be used for the operation. Now, FA_CODE and FA_FILE are defined.</param>
 * <param name="ulSize" type="IN" range="[0,VALID_BUFFER_SIZE,INVALID_BUFFER_SIZE]">Size of the buffer</param>
 * <param name="ulOffset" type="IN" range="[0,VALID_FLASH_OFFSET,INVALID_FLASH_OFFSET]">Offset of flash area to write to. The function adds the start address of the flash to calculate the physical address of the area.</param>
  * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Flash was successfully flushed</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOT_SUPPORTED">Type of Flasharea is not supported</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Size or Offset is not correct</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">Flash could not be flushed</errorcode>
 * <result>error code</result>
 */
RTS_RESULT CDECL SysFlashFlush_(FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset);
typedef RTS_RESULT (CDECL * PFSYSFLASHFLUSH_) (FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset);
#if defined(SYSFLASH_NOTIMPLEMENTED) || defined(SYSFLASHFLUSH__NOTIMPLEMENTED)
	#define USE_SysFlashFlush_
	#define EXT_SysFlashFlush_
	#define GET_SysFlashFlush_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFlashFlush_(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysFlashFlush_  FALSE
	#define EXP_SysFlashFlush_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFlashFlush_
	#define EXT_SysFlashFlush_
	#define GET_SysFlashFlush_(fl)  CAL_CMGETAPI( "SysFlashFlush_" ) 
	#define CAL_SysFlashFlush_  SysFlashFlush_
	#define CHK_SysFlashFlush_  TRUE
	#define EXP_SysFlashFlush_  CAL_CMEXPAPI( "SysFlashFlush_" ) 
#elif defined(MIXED_LINK) && !defined(SYSFLASH_EXTERNAL)
	#define USE_SysFlashFlush_
	#define EXT_SysFlashFlush_
	#define GET_SysFlashFlush_(fl)  CAL_CMGETAPI( "SysFlashFlush_" ) 
	#define CAL_SysFlashFlush_  SysFlashFlush_
	#define CHK_SysFlashFlush_  TRUE
	#define EXP_SysFlashFlush_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFlashFlush_", (RTS_UINTPTR)SysFlashFlush_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFlashSysFlashFlush_
	#define EXT_SysFlashSysFlashFlush_
	#define GET_SysFlashSysFlashFlush_  ERR_OK
	#define CAL_SysFlashSysFlashFlush_ pISysFlash->ISysFlashFlush_
	#define CHK_SysFlashSysFlashFlush_ (pISysFlash != NULL)
	#define EXP_SysFlashSysFlashFlush_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFlashFlush_
	#define EXT_SysFlashFlush_
	#define GET_SysFlashFlush_(fl)  CAL_CMGETAPI( "SysFlashFlush_" ) 
	#define CAL_SysFlashFlush_ pISysFlash->ISysFlashFlush_
	#define CHK_SysFlashFlush_ (pISysFlash != NULL)
	#define EXP_SysFlashFlush_  CAL_CMEXPAPI( "SysFlashFlush_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFlashFlush_  PFSYSFLASHFLUSH_ pfSysFlashFlush_;
	#define EXT_SysFlashFlush_  extern PFSYSFLASHFLUSH_ pfSysFlashFlush_;
	#define GET_SysFlashFlush_(fl)  s_pfCMGetAPI2( "SysFlashFlush_", (RTS_VOID_FCTPTR *)&pfSysFlashFlush_, (fl), 0, 0)
	#define CAL_SysFlashFlush_  pfSysFlashFlush_
	#define CHK_SysFlashFlush_  (pfSysFlashFlush_ != NULL)
	#define EXP_SysFlashFlush_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFlashFlush_", (RTS_UINTPTR)SysFlashFlush_, 0, 0) 
#endif





#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSFLASHINIT ISysFlashInit;
 	PFSYSFLASHERASE ISysFlashErase;
 	PFSYSFLASHREAD ISysFlashRead;
 	PFSYSFLASHWRITE ISysFlashWrite;
 	PFSYSFLASHFLUSH ISysFlashFlush;
 	PFSYSFLASHGETPHYSICALADDRESS ISysFlashGetPhysicalAddress;
 	PFSYSFLASHGETSIZE ISysFlashGetSize;
 	PFSYSFLASHERASE_ ISysFlashErase_;
 	PFSYSFLASHREAD_ ISysFlashRead_;
 	PFSYSFLASHWRITE_ ISysFlashWrite_;
 	PFSYSFLASHFLUSH_ ISysFlashFlush_;
 } ISysFlash_C;

#ifdef CPLUSPLUS
class ISysFlash : public IBase
{
	public:
		virtual RTS_RESULT CDECL ISysFlashInit(FlashArea fa) =0;
		virtual RTS_RESULT CDECL ISysFlashErase(FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset) =0;
		virtual RTS_RESULT CDECL ISysFlashRead(FlashArea fa, char *pcDest, RTS_SIZE ulSize, RTS_SIZE ulOffset) =0;
		virtual RTS_RESULT CDECL ISysFlashWrite(FlashArea fa, char *pcSource, RTS_SIZE ulSize, RTS_SIZE ulOffset) =0;
		virtual RTS_RESULT CDECL ISysFlashFlush(FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset) =0;
		virtual RTS_UINTPTR CDECL ISysFlashGetPhysicalAddress(FlashArea fa, RTS_RESULT *pResult) =0;
		virtual RTS_SIZE CDECL ISysFlashGetSize(FlashArea fa, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISysFlashErase_(FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset) =0;
		virtual RTS_RESULT CDECL ISysFlashRead_(FlashArea fa, char *pcDest, RTS_SIZE ulSize, RTS_SIZE ulOffset) =0;
		virtual RTS_RESULT CDECL ISysFlashWrite_(FlashArea fa, char *pcSource, RTS_SIZE ulSize, RTS_SIZE ulOffset) =0;
		virtual RTS_RESULT CDECL ISysFlashFlush_(FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset) =0;
};
	#ifndef ITF_SysFlash
		#define ITF_SysFlash static ISysFlash *pISysFlash = NULL;
	#endif
	#define EXTITF_SysFlash
#else	/*CPLUSPLUS*/
	typedef ISysFlash_C		ISysFlash;
	#ifndef ITF_SysFlash
		#define ITF_SysFlash
	#endif
	#define EXTITF_SysFlash
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSFLASHITF_H_*/
