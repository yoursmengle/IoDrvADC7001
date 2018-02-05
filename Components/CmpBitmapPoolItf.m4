/**
 * <interfacename>CmpBitmapPool</interfacename>
 * <description> 
 *	<p>Interface for the bitmap pool manager.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpBitmapPool')

/**
 * <category>BimapPool Settings</category>
 * <description>Setting which decides about the file that contains the contents of the bitmappool</description>
 *
 */
#ifndef BMPPOOL_VALUE_CONTENTFILE_IPC_DEFAULT
	#define BMPPOOL_VALUE_CONTENTFILE_IPC_DEFAULT "IPCBitmapPool"
#endif /* BMPPOOL_VALUE_CONTENTFILE_IPC_DEFAULT */

#ifndef BMPPOOL_VALUE_CONTENTFILE_IPC_DEFAULT_EXTENSION
	/* tmb was chosen (instead of possibly tmp) to be able to distinguis between the temporary files used in the filetransfer and
		this temporary file */
	#define BMPPOOL_VALUE_CONTENTFILE_IPC_DEFAULT_EXTENSION ".tmb"			
#endif /* BMPPOOL_VALUE_CONTENTFILE_IPC_DEFAULT_EXTENSION */

/**
 * <description>Setting which decides about the path where the configuration file and all 
 * the bitmaps are saved. Default is the current working directory.</description>
 *
 */
#define BMPPOOL_KEY_BASEPATH "BitmapPath"
#define BMPPOOL_VALUE_BASEPATH_DEFAULT ""

typedef struct
{
	RTS_IEC_STRING* pszId;
	RTS_IEC_STRING* pszPath;
	RTS_I32	Result;
} bitmappoolregister_struct;

typedef struct
{
	RTS_IEC_STRING* pszId;
	RTS_I32	Result;
} bitmappoolunregister_struct;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description> Add a bitmap pool entry from plc program</description>
 * <param name="pEntry" type="IN">Pointer to entry structure</param>
 * <result></result>
 */
DEF_API(`void', `CDECL', `bmppoolregister', `(bitmappoolregister_struct *pEntry)', 1, 0)

/**
 * <description> Remove a bitmap pool entry from plc program</description>
 * <param name="pEntry" type="IN">Pointer to entry structure</param>
 * <result></result>
 */
DEF_API(`void', `CDECL', `bmppoolunregister', `(bitmappoolunregister_struct *pEntry)', 1, 0)

/**
 * <description>Registers a bitmap within the bitmappool.</description>
 * <param name="pszBmpId" type="IN">Id of the bitmap to register.</param>
 * <param name="pszPath" type="IN">The path of the registered bitmap.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `BmpPoolRegister', `(const char *pszBmpId, const char *pszPath)')

/**
 * <description>Removes a bitmap from the bitmappool.</description>
 * <param name="pszBmpId" type="IN">Id of the searched bitmap.</param>
 * <result>error code: ERR_OK in case of success, ERR_PARAMETER if the bitmap is not registered</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `BmpPoolUnregister', `(const char *pszBmpId)')

/**
 * OBSOLETE FUNCTION: This function should not be used anymore.
 * <description>Returns the path of a bitmap that is handled by the BitmapPool</description>
 * <param name="pszBmpId" type="IN">Id of the searched bitmap.</param>
 * <param name="pszBmpPath" type="OUT">A string containing the path of the requested bitmap or NULL if 
 * it hasn't been found. The returned pointer will point to a string within the bitmap pool, so do not free
 * the returned string.</param>
 * <result>error code: ERR_OK, ERR_PARAMETER or ERR_INVALIDID if the bitmap is not registered</result>
 */
DEF_API(`RTS_RESULT', `CDECL', `BmpPoolGetPath', `(const char *pszBmpId, const char **ppszBmpPath)')

/**
 * <description>Clears the content of the bitmappool</description>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT', `CDECL', `BmpPoolClear', `(void)')

/**
 * <description>Loads the contents of the bitmappool from the configured location.</description>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT', `CDECL', `BmpPoolReadContents', `(char *pszFilePath, RTS_BOOL bDelete)')

/**
 * <description>Saves the contents of the bitmappool in the configured location.</description>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT', `CDECL', `BmpPoolWriteContents', `(char **ppszFilePath)')

/**
 * <description>
 *	This callback function can be implemented by components iterating over the content of an imagepool using <see>BmpPoolForeachEntry</see>.
 * </description>
 * <param name="pData" type="IN">The pointer that was passed in the call to BmpPoolForeachEntry</param>
 * <param name="pszId" type="IN">The id of an entry</param>
 * <param name="pszPath" type="IN">The path of an entry</param>
 * <result>
 *	Should return ERR_OK to continue the iteration or an error code to cancel the iteration.
 * </result>
 */
typedef RTS_RESULT (CDECL *PFForeachBmpPoolEntry)(void* pData, char* pszId, char* pszPath);

/**
 * <description>Call this function to iterate over all entries of the imagepool.</description>
 * <param name="pData" type="IN">A pointer to arbitrary data that will be passed to each callback.</param>
 * <param name="pfCallback" type="IN">The callback function that will be called for each entry of the imagepool</param>
 * <result>error code</result>
 */
DEF_API(`RTS_RESULT', `CDECL', `BmpPoolForeachEntry', `(void* pData, PFForeachBmpPoolEntry pfCallback)')

#ifdef __cplusplus
}
#endif
