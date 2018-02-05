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

SET_INTERFACE_NAME(`SysFlash')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFlashInit',`(FlashArea fa)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFlashErase',`(FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFlashRead',`(FlashArea fa, char *pcDest, RTS_SIZE ulSize, RTS_SIZE ulOffset)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFlashWrite',`(FlashArea fa, char *pcSource, RTS_SIZE ulSize, RTS_SIZE ulOffset)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFlashFlush',`(FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset)')

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
DEF_ITF_API(`RTS_UINTPTR',`CDECL',`SysFlashGetPhysicalAddress',`(FlashArea fa, RTS_RESULT *pResult)')

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
DEF_ITF_API(`RTS_SIZE',`CDECL',`SysFlashGetSize',`(FlashArea fa, RTS_RESULT *pResult)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFlashErase_',`(FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFlashRead_',`(FlashArea fa, char *pcDest, RTS_SIZE ulSize, RTS_SIZE ulOffset)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFlashWrite_',`(FlashArea fa, char *pcSource, RTS_SIZE ulSize, RTS_SIZE ulOffset)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFlashFlush_',`(FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset)')


#ifdef __cplusplus
}
#endif
