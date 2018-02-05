/**
 * <interfacename>SysModRTSub</interfacename>
 * <description> 
 *
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */
 
SET_INTERFACE_NAME(`SysModRTSub')

REF_ITF(`SysModRTMainItf.m4')
REF_ITF(`SysFlashItf.m4')
REF_ITF(`SysTimeItf.m4')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`ModRTMainSysFlashErase',`(FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`ModRTMainSysFlashWrite',`(FlashArea fa, char *pcSource, RTS_SIZE ulSize, RTS_SIZE ulOffset)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`ModRTMainSysFlashFlush',`(FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset)')

/**
 * <description>
 * <p>Interface wrapper function to ModRTMain.</p>
 * <p>Return a monotonic, rising millisecond tick.</p>
 * </description> 
 * <result>Returns the millisecond tick</result>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`ModRTMainSysTimeGetMs',`(void)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`ModRTMainSysTimeGetUs',`(RTS_SYSTIME* pTime)')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`ModRTMainSysTimeGetNs',`(RTS_SYSTIME* pTime)')


/** EXTERN LIB SECTION END **/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
