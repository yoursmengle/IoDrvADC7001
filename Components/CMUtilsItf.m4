/**
 * <interfacename>CmpMgrUtils</interfacename>
 * <description>
 *	<p>Interface for utility functions of the component manager</p>
 *	<p>The utility functions can be used by all components, because they are always included
 *	in the component manager.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CMUtils')

#ifndef RTS_WTEXT
	#define	RTS_WTEXT(s)				__RTS_WTEXT(s)
	#define	__RTS_WTEXT(s)				L ## s
#endif

#define RTS_WTEXT_EMPTY					RTS_WTEXT("\0")

#ifdef RTS_UNICODE
	#define	RTS_CWTEXT(s)				__RTS_CWTEXT(s)
	#define	__RTS_CWTEXT(s)				L ## s
#else
	#define	RTS_CWTEXT(s) 			s
#endif

/**
 * <category>Static defines</category>
 * <description>Static length of a string. Is ised for RTS_STRING_CLASS.</description>
 */
#define RTS_STATIC_STRING_LEN					32

/**
 * <category>Copy mode</category>
 * <type>Int</type>
 * <description>Modes to copy strings. Copy byte packed stream to a word stream. HI byte is filled with 0.</description>
 */ 
#define CMUTL_CPY_COMM2BUFFER		1

/**
 * <category>Copy mode</category>
 * <type>Int</type>
 * <description>Modes to copy strings. Copy word stream to a byte packed stream. HI byte is removed.</description>
 */
#define CMUTL_CPY_BUFFER2COMM		2

/**
 * <category>Copy mode</category>
 * <type>Int</type>
 * <description>Modes to copy strings. Copy stream unchanged.</description>
 */
#define CMUTL_CPY_DEFAULT			3

/**
 * <description> 
 * Definition of lock free ring buffer
 * </description>
 */
#define RTS_RINGBUFFER_STRUCT(size) \
struct { \
	RTS_UI32 uiReadPos; \
	RTS_UI32 uiWritePos; \
	RTS_UI8 ucBuf[size]; \
}
/**
 * <description> 
 * Ring buffer initialization
 * </description>
 */
#define RTS_RINGBUFFER_INIT(rbuf) (rbuf.uiReadPos = rbuf.uiWritePos = 0)

/**
 * <description> 
 * Get the length of written data in ring buffer, must be called before reading from buffer!
 * </description>
 */
#define RTS_RINGBUFFER_GET_FILL_SIZE(rbuf) ( (sizeof(rbuf.ucBuf) - rbuf.uiReadPos + rbuf.uiWritePos) % sizeof(rbuf.ucBuf) )

/**
 * <description> 
 * Get the length of available space in ring buffer, must be called before writing into buffer!
 * Always return one byte less than actual space size to avoid collision.
 * </description>
 */
#define RTS_RINGBUFFER_GET_FREE_SIZE(rbuf) ( (sizeof(rbuf.ucBuf) + rbuf.uiReadPos - rbuf.uiWritePos -1) % sizeof(rbuf.ucBuf) )

/**
 * <description> 
 * Read data from ring buffer. 
 * sizeToRead is the actual data length to be read from the buffer!
 * Comparison between filled data length in buffer and the length needs to be read must be done before calling this function!
 * Example:
 * sizeToRead = MIN(RTS_RINGBUFFER_GET_FILL_SIZE(rbuf), usSize);
 * RTS_RINGBUFFER_READ(dest, rbuf, sizeToRead);
 * </description>
 */
#define RTS_RINGBUFFER_READ(dest, rbuf, sizeToRead)\
	do{\
		RTS_UI32 sizeSectionA, sizeSectionB;\
		sizeSectionA = MIN(sizeof(rbuf.ucBuf) - rbuf.uiReadPos, sizeToRead);\
		sizeSectionB = sizeToRead - sizeSectionA;\
		memcpy(dest, &rbuf.ucBuf[rbuf.uiReadPos], sizeSectionA);\
		memcpy(dest + sizeSectionA, &rbuf.ucBuf[0], sizeSectionB);\
		rbuf.uiReadPos = (rbuf.uiReadPos + sizeToRead) % sizeof(rbuf.ucBuf);\
	}while(0)

/**
 * <description>
 * Read single byte of data from ring buffer.
 * </description>
 */
#define RTS_RINGBUFFER_READB(c, rbuf)\
	do{\
		c = rbuf.ucBuf[rbuf.uiReadPos];\
		rbuf.uiReadPos = (rbuf.uiReadPos + 1) % sizeof(rbuf.ucBuf);\
	}while(0)

/**
 * <description> 
 * Write data into ring buffer.
 * sizeToWrite is the actual data length to be written into the buffer!
 * Comparison between free buffer length and the length needs to be written must be done before calling this function!
 * Example:
 * sizeToWrite = MIN(RTS_RINGBUFFER_GET_FREE_SIZE(rbuf), usSize);
 * RTS_RINGBUFFER_WRITE(src, rbuf, sizeToWrite);
 * </description>
 */
#define RTS_RINGBUFFER_WRITE(src, rbuf, sizeToWrite)\
	do{\
		RTS_UI32 sizeSectionA, sizeSectionB;\
		sizeSectionA = MIN(sizeof(rbuf.ucBuf) - rbuf.uiWritePos, sizeToWrite);\
		sizeSectionB = sizeToWrite - sizeSectionA;\
		memcpy(&rbuf.ucBuf[rbuf.uiWritePos], src, sizeSectionA);\
		memcpy(&rbuf.ucBuf[0], src + sizeSectionA, sizeSectionB);\
		rbuf.uiWritePos = (rbuf.uiWritePos + sizeToWrite) % sizeof(rbuf.ucBuf);\
	}while(0)


/**
 * <description>
 * Write single byte of data into ring buffer.
 * </description>
 */
#define RTS_RINGBUFFER_WRITEB(c, rbuf)\
	do{\
		rbuf.ucBuf[rbuf.uiWritePos] = c;\
		rbuf.uiWritePos = (rbuf.uiWritePos + 1) % sizeof(rbuf.ucBuf);\
	}while(0)
		
#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description> 
 *	Called to skip withspaces out of a string.
 * </description>
 * <param name="psz" type="IN">Pointer to the string</param>
 * <result>returns the pointer to the next position in the string with no whitespace</result>
 */
DEF_ITF_API(`char*', `CDECL', `CMUtlSkipWhiteSpace', `(char* psz)')

/**
 * <description> 
 * Maximum length of the long binary string 
 * </description>
 */
#define MAX_LONG_BIN_STRING_LEN		(sizeof(RTS_I32) * 8 + 1)

/**
 * <description> 
 * Maximum length of the long decimal string 
 * </description>
 */
#define MAX_LONG_DEC_STRING_LEN		11

/**
 * <description> 
 * Maximum length of the long hexadecimal string
 * </description>
 */
#define MAX_LONG_HEX_STRING_LEN		11

/**
 * <description> 
 * <p>Converts a long value to a string. The representation can be specified by the iBase value:</p>
 * <p>2: binary (e.g. "10101010101110111100110011011101"). String length must be at least MAX_LONG_BIN_STRING_LEN bytes!</p>
 * <p>10: decimal (e.g. "2864434397"). String length must be at least MAX_LONG_DEC_STRING_LEN bytes!</p>
 * <p>16: hexadecimal (e.g. "0xAABBCCDD"). String length must be at least MAX_LONG_HEX_STRING_LEN bytes!</p>
 * </description>
 * <param name="lValue" type="IN">Long value to convert</param>
 * <param name="szString" type="OUT">Pointer to the string to get integer value as string</param>
 * <param name="iBase" type="IN">Base for the conversion: See description</param>
 * <result>returns the pointer to the next position in the string with no whitespace</result>
 */
DEF_ITF_API(`char*', `CDECL', `CMUtlLtoa', `(RTS_I32 lValue, char *pszString, int nMaxLen, int iBase, RTS_RESULT *pResult)')

/**
 * <description> 
 * Maximum length of the unsigned long binary string   
 * </description>
 */
#define MAX_ULONG_BIN_STRING_LEN	(sizeof(RTS_UI32) * 8 + 1)

/**
 * <description> 
 * Maximum length of the unsigned long decimal string  
 * </description>
 */
#define MAX_ULONG_DEC_STRING_LEN	11

/**
 * <description> 
 * Maximum length of the long unsigned hexadecimal string  
 * </description>
 */
#define MAX_ULONG_HEX_STRING_LEN	11

/**
 * <description> 
 *	Convert  a version as string in an integer. The string must have the format "x.x.x.x".
 * </description>
 * <param name="pszVersion" type="IN">Pointer to version as string</param>
 * <param name="pui32Version" type="OUT">Pointer to get the version as integer</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlStringToVersion', `(char *pszVersion, RTS_UI32 *pui32Version)')

/**
 * <description> 
 *	Convert  a version into a string. The string has the format "x.x.x.x".
 * </description>
 * <param name="ui32Version" type="IN">Version as integer</param>
 * <param name="pszVersion" type="OUT">Pointer to version as string</param>
 * <param name="nMaxLen" type="IN">Max lenght of pszVersion</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlVersionToString', `(RTS_UI32 ui32Version, char *pszVersion, RTS_SIZE nMaxLen)')

/**
 * <description> 
 * <p>Converts an unsigned long value to a string. The representation can be specified by the iBase value:</p>
 * <p>2: binary (e.g. "10101010101110111100110011011101"). String length must be at least MAX_ULONG_BIN_STRING_LEN bytes!</p>
 * <p>10: decimal (e.g. "2864434397"). String length must be at least MAX_ULONG_DEC_STRING_LEN bytes!</p>
 * <p>16: hexadecimal (e.g. "0xAABBCCDD"). String length must be at least MAX_ULONG_HEX_STRING_LEN bytes!</p>	
 * </description>
 * <param name="ulValue" type="IN">Unsigned long value to convert</param>
 * <param name="szString" type="OUT">Pointer to the string to get integer value as string</param>
 * <param name="iBase" type="IN">Base for the conversion: See description</param>
 * <result>returns the pointer to the next position in the string with no whitespace</result>
 */
DEF_ITF_API(`char*', `CDECL', `CMUtlUltoa', `(RTS_UI32 ulValue, char *pszString, int nMaxLen, int iBase, RTS_RESULT *pResult)')

/**
 * <description> 
 * <p>Reverses content of a string in place</p>
 * </description>
 * <param name="psz" type="INOUT">Pointer to a null-terminated string</param>
 * <result>returns the pointer to the next the same string</result>
 */
DEF_ITF_API(`char*', `CDECL', `CMUtlStrrev', `(char *psz)')


/**
 * <description> 
 *  Scan a string for the last occurrence of a character
 * </description>
 * <param name="pszString" type="IN">Pointer to scan</param>
 * <param name="pszBegin" type="IN">Pointer of a position into pszString to start the scan</param>
 * <result>Pointer to the first occurrence in string, or NULL if not found</result>
 */
DEF_ITF_API(`char*', `CDECL', `CMUtlStrRChr', `(char *pszString, char *pszBegin, char cFind)')

/**
 * <description> 
 * <p>Case insensitive string compare.</p>
 * </description>
 * <param name="pszString1" type="IN" range="[NULL,VALID_POINTER_TO_STRING1,VALID_POINTER_TO_STRING2]">Pointer to first string to compare</param>
 * <param name="pszString2" type="IN" range="[NULL,VALID_POINTER_TO_STRING1]">Pointer to second string to compare</param>
 * <result>0 if strings are equal, -1 or 1 if there is a difference between them</result>
 */
DEF_ITF_API(`int', `CDECL', `CMUtlStrICmp', `(char *pszString1, char *pszString2)')

/**
 * <description> 
 *  Lower case comparison of two strings specified by length.
 * </description>
 * <param name="pszString1" type="IN">Pointer to first string to compare</param>
 * <param name="pszString2" type="IN">Pointer to second string to compare</param>
 * <param name="n" type="IN">Number of characters to compare</param>
 * <result>0= strings are equal, !0=strings unequal</result>
 */
DEF_ITF_API(`int', `CDECL', `CMUtlStrNICmp', `(char *pszString1, char *pszString2, RTS_SIZE n)')

/**
 * <description> 
 *  Find a substring in another string.
 * </description>
 * <param name="pszString" type="IN">String to search substring in</param>
 * <param name="pszStringToFind" type="IN">Substring to find</param>
  * <result>NULL= substring not found in string, !NULL= pointer to string, where substring was found</result>
 */
DEF_ITF_API(`char *', `CDECL', `CMUtlStrIStr', `(const char *pszString, const char *pszStringToFind)')

/**
 * <description> 
 *  Lower case conversion of a string.
 * </description>
 * <param name="pszString" type="IN">Pointer to conversion string</param>
 * <result>Returns a pointer to the converted string, NULL if conversion failed</result>
 */
DEF_ITF_API(`char*', `CDECL', `CMUtlStrlwr', `(char *pszString)')

/**
 * <description> 
 *  Upper case conversion of a string.
 * </description>
 * <param name="pszString" type="IN">Pointer to conversion string</param>
 * <result>Returns a pointer to the converted string, NULL if conversion failed</result>
 */
DEF_ITF_API(`char*', `CDECL', `CMUtlStrupr', `(char *pszString)')

/**
 * <description> 
 *  Safe string copy of a string. The length of the destination buffer is checked to avoid memory overwrites.
 * </description>
 * <param name="pszDest" type="IN">Pointer to destination buffer</param>
 * <param name="nDestSize" type="IN">Length of destination buffer</param>
 * <param name="pszSrc" type="IN">Pointer to source buffer. String must be NUL terminated!</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlSafeStrCpy', `(char *pszDest, RTS_SIZE nDestSize, const char *pszSrc)')

/**
 * <description> 
 * <p>Copy a string from one buffer to another, but limit the size of the
 * destination buffer to nDestSize.</p>
 * </description>
 * <param name="pszDest" type="IN" range="[0,VALID_POINTER_TO_STRINGDEST]">Pointer to destination buffer</param>
 * <param name="nDestSize" type="IN" range="[0,INVALID_DST_SIZE,VALID_DST_SIZE]">Length of destination buffer</param>
 * <param name="pszSrc" type="IN" range="[0,VALID_POINTER_TO_STRINGSRC]">Pointer to source buffer. String must be NUL terminated!</param>
 * <param name="nCopyMode" type="IN" range="[0,CMUTL_CPY_COMM2BUFFER,CMUTL_CPY_BUFFER2COMM,CMUTL_CPY_DEFAULT]">Copy mode. See corresponding category "Copy mode"</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Copied successful!</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_BUFFERSIZE">Size of SrcString is greater than nDestSize!</errorcode> 
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlSafeStrCpy2', `(char *pszDest, RTS_SIZE nDestSize, const char *pszSrc, int nCopyMode)')

/**
 * <description> 
 * <p>Copy a string from one buffer to another specified by the number of characters to copy, but limit the size of the
 * destination buffer to nDestSize.</p>
 * </description>
 * <param name="pszDest" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_POINTER_TO_STRINGDEST]">Pointer to destination buffer</param>
 * <param name="nDestSize" type="IN" range="[0,1,RTS_SIZE_MAX]">Length of destination buffer</param>
 * <param name="pszSrc" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_POINTER_TO_STRINGSRC]">Pointer to source buffer. String must be NUL terminated!</param>
 * <param name="nBytesCopy" type="IN" range="[0,1,RTS_SIZE_MAX]">Number of bytes to copy</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Copy successful</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_BUFFERSIZE">Destination buffer too short. Only the possible number of charachters copied</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlSafeStrNCpy', `(char *pszDest, RTS_SIZE nDestSize, const char *pszSrc, RTS_SIZE nBytesCopy)')

/**
 * <description> 
 * <p>Concatenate two strings, but limit the size of the destination buffer to nDestSize.</p>
 * </description>
 * <param name="pszDest" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_POINTER_TO_STRINGDEST]">Pointer to destination buffer</param>
 * <param name="nDestSize" type="IN" range="[0,1,RTS_SIZE_MAX]">Length of destination buffer</param>
 * <param name="pszSrc" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_POINTER_TO_STRINGSRC]">Pointer to source buffer. String must be NUL terminated!</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Concatenate successful</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_BUFFERSIZE">Destination buffer too short. Only the possible number of charachters copied</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlSafeStrCat', `(char *pszDest, RTS_SIZE nDestSize, const char *pszSrc)')

/**
 * <description>
 * <p>Calculate the string length</p>
 * <p>Is able to handle Null pointer</p>
 * <p>This function works for targets where char has a size of 8 bits as well
 * as for targets where char is 16 bits wide.</p>
 * </description>
 * <param name="str" type="IN" range="[NULL,VALID_POINTER_TO_STRING1]">pointer to string</param>
 * <result>Length of string without trailing \0, 0 if str is Null</result>
 */
DEF_ITF_API(`RTS_SIZE', `CDECL', `CMUtlStrLen', `(char *str)')

/**
 * <description>
 * <p>Calculate the string length. This function will stop if no NUL is found in the first nMaxSize bytes of the string.</p>
 * <p>Is able to handle Null pointer</p>
 * <p>This function works for targets where char has a size of 8 bits as well
 * as for targets where char is 16 bits wide.</p>
 * </description>
 * <result>Length of string without trailing \0, 0 if str is Null, nMaxSize if no NUL is found.</result>
 */
DEF_ITF_API(`RTS_SIZE', `CDECL', `CMUtlStrNLen', `(char *str, RTS_SIZE nMaxSize)')

/**
 * <description> 
 *  Convert a string in lower case. String must be NUL terminated!
 * </description>
 * <param name="psz" type="IN">Pointer to string to convert</param>
 * <result>Pointer to psz with the converted content</result>
 */
DEF_ITF_API(`char*', `CDECL', `CMUtlStrToLower', `(char* psz)')

/**
 * <description> 
 *  Convert a string in upper case. String must be NUL terminated!
 * </description>
 * <param name="psz" type="IN">Pointer to string to convert</param>
 * <result>Pointer to psz with the converted content</result>
 */
DEF_ITF_API(`char*', `CDECL', `CMUtlStrToUpper', `(char* psz)')

/**
 * <description> 
 *  Safe sprintf with argument list.
 *	NOTES:
 *	- If ANSI vsnprintf is not available on the target, vsprintf is used instead and the size of the string can be evaluated only after
 *		writing the complete string! So the memory could be overwritten in this case and so the error code is the only way to detect this situation!
 *	- RTS_ASSERT() is generated, if string buffer is too short!
 * </description>
 * <param name="pszStr" type="IN">Destination buffer</param>
 * <param name="ulStrSize" type="IN">Destination buffer size</param>
 * <param name="pszFormat" type="IN">Format string</param>
 * <param name="pargList" type="IN">Pointer to argument list</param>
 * <result>Error code:
 *	<ul>
 *     <li>ERR_OK: String could be written</li>
 *     <li>ERR_PARAMETER: NULL pointer used as parameter</li>
 *     <li>ERR_BUFFERSIZE: If pszStr is too short to get the string value</li>
 *  </ul>
 * </result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlvsnprintf', `(char *pszStr, RTS_SIZE ulStrSize, const char *pszFormat, va_list *pargList)')

/**
 * <description> 
 *  Safe sprintf with format string and variable argument list.
 *	NOTES:
 *	- If ANSI vsnprintf is not available on the target, vsprintf is used instead and the size of the string can be evaluated only after
 *		writing the complete string! So the memory could be overwritten in this case and so the error code is the only way to detect this situation!
 *	- RTS_ASSERT() is generated, if string buffer is too short!
 * </description>
 * <param name="pszStr" type="IN">Destination buffer</param>
 * <param name="ulStrSize" type="IN">Destination buffer size</param>
 * <param name="pszFormat" type="IN">Format string</param>
 * <param name="..." type="IN">Argument list</param>
 * <result>Error code:
 *	<ul>
 *     <li>ERR_OK: String could be written</li>
 *     <li>ERR_PARAMETER: NULL pointer used as parameter</li> 
 *     <li>ERR_BUFFERSIZE: If pszStr is too short to get the string value</li>
 *  </ul>
 * </result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlsnprintf', `(char *pszStr, RTS_SIZE ulStrSize, const char *pszFormat, ...)')

/**
 * <description> 
 *  Memory copy between two buffers. 
 *  NOTES:
 *  - Caller has to take care about parameter checks. E.g. function does not check for nullpointer or overlapping.
 *  - Function behaves exactly like memcpy from standard c-library
 *  - For some platforms (e.g. ARM), the native memcpy might be problematic when accessing external memory. In these cases this implementation can be used
 * </description>
 * <param name="pDest" type="IN">Pointer to destination buffer</param>
 * <param name="pSrc" type="IN">Pointer to source buffer</param>
 * <param name="ulToCopy" type="IN">Bytes to copy from source to destination buffer</param>
 * <result>Pointer to destination buffer</result>
 */
DEF_ITF_API(`void*', `CDECL', `CMUtlMemCpy', `(void *pDest, const void *pSrc, RTS_SIZE ulToCopy)')

/**
 * <description> 
 *  Safe memory copy between two buffers. The length of the destination buffer is checked to avoid memory overwrites.
 * </description>
 * <param name="pDest" type="IN">Pointer to destination buffer</param>
 * <param name="ulDestSize" type="IN">Length of destination buffer</param>
 * <param name="pSrc" type="IN">Pointer to source buffer</param>
 * <param name="ulToCopy" type="IN">Bytes to copy from source to destination buffer</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlSafeMemCpy', `(void *pDest, RTS_SIZE ulDestSize, const void *pSrc, RTS_SIZE ulToCopy)')

/**
 * <description> 
 *  Safe memory move between two buffers. The length of the destination buffer is checked to avoid memory overwrites.
 * </description>
 * <param name="pDest" type="IN">Pointer to destination buffer</param>
 * <param name="ulDestSize" type="IN">Length of destination buffer</param>
 * <param name="pSrc" type="IN">Pointer to source buffer</param>
 * <param name="ulToCopy" type="IN">Bytes to copy from source to destination buffer</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlSafeMemMove', `(void *pDest, RTS_SIZE ulDestSize, const void *pSrc, RTS_SIZE ulToCopy)')

/**
 * <description> 
 * Maximum legth of the GUID string
 * </description>
 */
#define MAX_GUID_STRING_LEN		38

/**
 * <description> 
 *  Conversion of a GUID into a string.
 * </description>
 * <param name="pguid" type="IN">Pointer to the GUID to convert</param>
 * <param name="pszGUID" type="OUT">Pointer to string buffer for the result</param>
 * <param name="nMaxLen" type="IN">maximum length of the string buffer. Should be at least MAX_GUID_STRING_LEN</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlGUIDToString', `(RTS_GUID *pguid, char *pszGUID, RTS_SIZE nMaxLen)')


/**
 ***************************************************************************
 * <description> 
 *  String class routines
 * </description>
 ***************************************************************************
 */
/**
 * <category>ComponentNameFlags</category>
 * <description>
 *	<ul>
 *		<li>RTS_STRING_STATIC: Name is stored in a static buffer</li>
 *		<li>RTS_STRING_DYNAMIC: Name is stored in a dynamic buffer</li>
 *		<li>RTS_STRING_ASCII: Ascii string content</li>
 *	</ul>
 * </description>
 */
#define RTS_STRING_STATIC		0x00000001
#define RTS_STRING_DYNAMIC		0x00000002
#define RTS_STRING_ASCII		0x00010000

/**
 * <category>RTS_STRING_CLASS</category>
 * <description>
 *	Can be used to manage strings.
 * </description>
 */
typedef union RTS_STRING_ENTRY_
{
	char *psz;
	char sz[RTS_STATIC_STRING_LEN];
} RTS_STRING_ENTRY;

typedef struct RTS_STRING_CLASS_
{
	RTS_STRING_ENTRY name;
	RTS_SIZE size;
	RTS_UI32 ulFlags;
} RTS_STRING_CLASS;

/**
 * <description> 
 *  Macro to get the string content out of a string class.
 * </description>
 * <param name="pString" type="IN">Pointer to string class</param>
 * <param name="default" type="IN">Default string, if string content could not be returned</param>
 * <result>Pointer to content</result>
 */
#define CM_STRING_GET_CONTENT(pString, default)		(pString == NULL ? default : ( (((RTS_STRING_CLASS *)pString)->ulFlags & RTS_STRING_DYNAMIC) ? ((RTS_STRING_CLASS *)pString)->name.psz : ((RTS_STRING_CLASS *)pString)->name.sz) )

/**
 * <description> 
 *  Macro to get the size in bytes of the content of a string class.
 * </description>
 * <param name="pString" type="IN">Pointer to string class</param>
 * <result>Size in bytes of the string content</result>
 */
#define CM_STRING_GET_SIZE(pString)			(pString == NULL ? 0 : ((RTS_STRING_CLASS *)pString)->size)

/**
 * <description> 
 *  Create a string and initialize it with a default string.
 * </description>
 * <param name="pString" type="IN">Pointer to string class</param>
 * <param name="pszComponentName" type="IN">Pointer to the component name, which creates this string</param>
 * <param name="pszInit" type="IN">Pointer to init string to copy into content. Can be NULL.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMStringCreate', `(RTS_STRING_CLASS *pString, char *pszComponentName, char *pszInit)')

/**
 * <description> 
 *  Create a string and initialize it with a default string.
 * </description>
 * <param name="pString" type="IN">Pointer to string class</param>
 * <param name="pszComponentName" type="IN">Pointer to the component name, which creates this string</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMStringDelete', `(RTS_STRING_CLASS *pString, char *pszComponentName)')

/**
 * <description> 
 *  Extend a string to a specified size.
 * </description>
 * <param name="pString" type="IN">Pointer to string class</param>
 * <param name="pszComponentName" type="IN">Pointer to the component name, which creates this string</param>
 * <param name="size" type="IN">Size to which the content must be extended</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMStringExtend', `(RTS_STRING_CLASS *pString, char *pszComponentName, RTS_SIZE size)')


/**
 ***************************************************************************
 * <description> 
 *  UNICODE string routines
 * </description>
 ***************************************************************************
 */

/**
 * <description> 
 *  Compare two unicode strings
 * </description>
 * <param name="pwsz1" type="IN">Pointer to string 1</param>
 * <param name="pwsz2" type="IN">Pointer to string 2</param>
 * <result>
 *		0: string1 identical to string2
 *		lower 0: string1 less than string2
 *		greater 0: string1 greater than string2
 * </result>
 */
DEF_ITF_API(`int', `CDECL', `CMUtlwstrcmp', `(const RTS_WCHAR *pwsz1, const RTS_WCHAR *pwsz2)')

/**
 * <description> 
 *  Compare two unicode strings with specified number of characters
 * </description>
 * <param name="pwsz1" type="IN">Pointer to string 1</param>
 * <param name="pwsz2" type="IN">Pointer to string 2</param>
 * <param name="nCount" type="IN">Number of characters to compare</param>
 * <result>
 *		0: string1 identical to string2
 *		lower 0: string1 less than string2
 *		greater 0: string1 greater than string2
 * </result>
 */
DEF_ITF_API(`int', `CDECL', `CMUtlwstrncmp', `(const RTS_WCHAR *pwsz1, const RTS_WCHAR *pwsz2, RTS_SIZE nCount)')

/**
 * <description> 
 *  Copy one unicode string to another in a safe way
 * </description>
 * <param name="pwszDest" type="IN">Destination string</param>
 * <param name="nDestSize" type="IN">Size of the destination buffer in unicode characters (not bytes)!</param>
 * <param name="pwszSrc" type="IN">Source string</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlwstrcpy', `(RTS_WCHAR *pwszDest, RTS_SIZE nDestSize, const RTS_WCHAR *pwszSrc)')

/**
 * <description> 
 *  Concatenate two unicode strings in a safe way
 * </description>
 * <param name="pwszDest" type="IN">Destination string</param>
 * <param name="nDestSize" type="IN">Size of the destination buffer in unicode characters (not bytes)!</param>
 * <param name="pwszSrc" type="IN">Source string</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlwstrcat', `(RTS_WCHAR *pwszDest, RTS_SIZE nDestSize, const RTS_WCHAR *pwszSrc)')

/**
 * <description> 
 *  Copy number of characters from one unicode string to another in a safe way
 * </description>
 * <param name="pwszDest" type="IN">Destination string</param>
 * <param name="nDestSize" type="IN">Size of the destination buffer in unicode characters (not bytes)!</param>
 * <param name="pwszSrc" type="IN">Source string</param>
 * <param name="n" type="IN">Number of characters to copy (not bytes)!</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlwstrncpy', `(RTS_WCHAR *pwszDest, RTS_SIZE nDestSize, const RTS_WCHAR *pwszSrc, RTS_SIZE n)')

/**
 * <description> 
 *  Get the number of characters (not bytes!) in the content of a string _without_ NUL terminating character.
 * </description>
 * <param name="pwsz" type="IN">Pointer to string</param>
 * <result>Number of characters (not bytes!) in the content of a string _without_ NUL terminating character</result>
 */
DEF_ITF_API(`RTS_SIZE', `CDECL', `CMUtlwstrlen', `(const RTS_WCHAR *pwsz)')

/**
 * <description> 
 *  Convert the characters in a unicode string to lower case.
 * </description>
 * <param name="pwsz" type="IN">Pointer to string</param>
 * <result>pwsz is returned</result>
 */
DEF_ITF_API(`RTS_WCHAR*', `CDECL', `CMUtlwtolower', `(RTS_WCHAR* pwsz)')

/**
 * <description> 
 *  Convert the characters in a unicode string to upper case.
 * </description>
 * <param name="pwsz" type="IN">Pointer to string</param>
 * <result>pwsz is returned</result>
 */
DEF_ITF_API(`RTS_WCHAR*', `CDECL', `CMUtlwtoupper', `(RTS_WCHAR* pwsz)')

/**
 * <description> 
 *  Convert a byte character string to a unicode character string.
 * </description>
 * <param name="pszSrc" type="IN">Pointer to byte character string</param>
 * <param name="pwszDest" type="IN">Pointer to unicode character string</param>
 * <param name="nDestSize" type="IN">Size of the destination buffer in unicode characters (not bytes)!</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlStrToW', `(const char* pszSrc, RTS_WCHAR* pwszDest, RTS_SIZE nDestSize)')

/**
 * <description> 
 *  Convert a unicode character string to a byte character string .
 * </description>
 * <param name="pwszSrc" type="IN">Pointer to unicode character string</param>
 * <param name="pszDest" type="IN">Pointer to byte character string</param>
 * <param name="nDestSize" type="IN">Size of the destination buffer in bytes</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlWToStr', `(const RTS_WCHAR* pwszSrc, char* pszDest, RTS_SIZE nDestSize)')

/**
 * <description> 
 *  Find a character in a unicode string.
 * </description>
 * <param name="pwsz" type="IN">Pointer to unicode string</param>
 * <param name="w" type="IN">Character to find</param>
 * <result>Returns the find position or NULL if not found</result>
 */
DEF_ITF_API(`RTS_WCHAR*', `CDECL', `CMUtlwstrchr', `(const RTS_WCHAR *pwsz, RTS_WCHAR w)')


/*
 *************************************************************************
 * <description> 
 *  Conversion between UTF-8 and RTS_WSTRING (UTF-16). The conversion
 *  can produce the REPLACEMENT CHARACTER (U+FFFD) for invalid sequences.
 * </description>
 *************************************************************************
 */
 
/**
 * <description>This function converts a UTF-16 encoded WSTRING to a sequenze of UTF-8 code points.
 * If a codepoint cannot be converted this codepoint will be replaced with the Unicode REPLACEMENT 
 * CHARACTER (U+FFFD).</description>
 * <param name="pwsz" type="IN">Pointer to WSTRING to be converted.</param>
 * <param name="wstrLen" type="IN">Size of readbuffer in WCHARs. Set to -1 if unknown.</param>
 * <param name="pUtf8Str" type="IN">Pointer to buffer where to store the UTF-8 sequence.</param>
 * <param name="bufferSize" type="IN">Buffersize of UTF-8 buffer.</param>
 * <result>On of these error codes: 
 *                                  - ERR_OK: Everything went fine. No errors occured.
 *                                  - ERR_PARAMETER: The parameterchecks failed.
 *                                  - ERR_CONVERSION_INCOMPLETE: The conversion failed because of some codepoints. These where replaced with U+FFFD.
 * </result>
 */
 
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlWToUtf8', `(RTS_WCHAR *pwsz, RTS_SIZE wstrLen, RTS_UI8* pUtf8Str, RTS_SIZE bufferSize)')

/**
 * <description>This function converts a UTF-8 string to a UTF-16 encoded WSTRING.
 * The conversion inserts the REPLACEMENT CHARACTER (U+FFFD) if a UTF-8 codepoint or invalid.</description>
 * <param name="pUtf8Str" type="IN">Pointer to UTF-8 string to be converted.</param>
 * <param name="pUtf8BufferSize" type="IN">Read buffer size. Set to -1 if unknown.</param>
 * <param name="pwsz" type="IN">Pointer to WSTRING buffer.</param>
 * <param name="wstrLen" type="IN">Number of WCHARs in pwsz.</param>
 * <result>On of these error codes: 
 *                                  - ERR_OK: Everything went fine. No errors occured.
 *                                  - ERR_PARAMETER: The parameterchecks failed.
 *                                  - ERR_CONVERSION_INCOMPLETE: The conversion failed because of some codepoints. These where replaced with U+FFFD.
 * </result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlUtf8ToW', `(RTS_UI8* pUtf8Str, RTS_SIZE utf8BufferSize, RTS_WCHAR* pwsz, RTS_SIZE wstrLen)')

/**
 *************************************************************************
 * <description> 
 *  Variable string type routines. Can be UNICODE or C-strings, dependant
 *	of the type definition of RTS_CWCHAR!
 * </description>
 *************************************************************************/

/**
 * <description> 
 *  Compare two RTS_CWCHAR strings
 * </description>
 * <param name="pwsz1" type="IN">Pointer to string 1</param>
 * <param name="pwsz2" type="IN">Pointer to string 2</param>
 * <result>
 *		0: string1 identical to string2
 *		lower 0: string1 less than string2
 *		greater 0: string1 greater than string2
 * </result>
 */
DEF_ITF_API(`int', `CDECL', `CMUtlcwstrcmp', `(const RTS_CWCHAR *pwsz1, const RTS_CWCHAR *pwsz2)')

/**
 * <description> 
 *  Copy one RTS_CWCHAR string to another in a safe way
 * </description>
 * <param name="pwszDest" type="IN">Destination string</param>
 * <param name="nDestSize" type="IN">Size of the destination buffer in RTS_CWCHAR characters!</param>
 * <param name="pwszSrc" type="IN">Source string</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlcwstrcpy', `(RTS_CWCHAR *pwszDest, RTS_SIZE nDestSize, const RTS_CWCHAR *pwszSrc)')

/**
 * <description> 
 *  Concatenate two RTS_CWCHAR strings in a safe way
 * </description>
 * <param name="pwszDest" type="IN">Destination string</param>
 * <param name="nDestSize" type="IN">Size of the destination buffer in RTS_CWCHAR characters!</param>
 * <param name="pwszSrc" type="IN">Source string</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlcwstrcat', `(RTS_CWCHAR *pwszDest, RTS_SIZE nDestSize, const RTS_CWCHAR *pwszSrc)')

/**
 * <description> 
 *  Copy number of characters from one RTS_CWCHAR string to another in a safe way
 * </description>
 * <param name="pwszDest" type="IN">Destination string</param>
 * <param name="nDestSize" type="IN">Size of the destination buffer in RTS_CWCHAR characters!</param>
 * <param name="pwszSrc" type="IN">Source string</param>
 * <param name="n" type="IN">Number of characters to copy (not bytes)!</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlcwstrncpy', `(RTS_CWCHAR *pwszDest, RTS_SIZE nDestSize, const RTS_CWCHAR *pwszSrc, RTS_SIZE n)')

/**
 * <description> 
 *  Get the number of RTS_CWCHAR characters in the content of a string _without_ NUL terminating character.
 * </description>
 * <param name="pwsz" type="IN">Pointer to string</param>
 * <result>Number of RTS_CWCHAR characters in the content of a string _without_ NUL terminating character</result>
 */
DEF_ITF_API(`RTS_SIZE', `CDECL', `CMUtlcwstrlen', `(const RTS_CWCHAR *pwsz)')

/**
 * <description> 
 *  Convert the characters in a RTS_CWCHAR string to lower case.
 * </description>
 * <param name="pwsz" type="IN">Pointer to string</param>
 * <result>pwsz is returned</result>
 */
DEF_ITF_API(`RTS_CWCHAR*', `CDECL', `CMUtlcwtolower', `(RTS_CWCHAR* pwsz)')

/**
 * <description> 
 *  Convert the characters in a RTS_CWCHAR string to upper case.
 * </description>
 * <param name="pwsz" type="IN">Pointer to string</param>
 * <result>pwsz is returned</result>
 */
DEF_ITF_API(`RTS_CWCHAR*', `CDECL', `CMUtlcwtoupper', `(RTS_CWCHAR* pwsz)')

/**
 * <description> 
 *  Convert a byte character string to a RTS_CWCHAR character string.
 * </description>
 * <param name="pszSrc" type="IN">Pointer to byte character string</param>
 * <param name="pwszDest" type="IN">Pointer to RTS_CWCHAR character string</param>
 * <param name="nDestSize" type="IN">Size of the destination buffer in RTS_CWCHAR characters!</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlStrToCW', `(const char* pszSrc, RTS_CWCHAR* pwszDest, RTS_SIZE nDestSize)')

/**
 * <description> 
 *  Convert a RTS_CWCHAR character string to a byte character string .
 * </description>
 * <param name="pwszSrc" type="IN">Pointer to RTS_CWCHAR character string</param>
 * <param name="pszDest" type="IN">Pointer to byte character string</param>
 * <param name="nDestSize" type="IN">Size of the destination buffer in bytes</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlCWToStr', `(const RTS_CWCHAR* pwszSrc, char* pszDest, RTS_SIZE nDestSize)')

/**
 * <description> 
 *  Find a character in a RTS_CWCHAR string.
 * </description>
 * <param name="pwsz" type="IN">Pointer to RTS_CWCHAR string</param>
 * <param name="w" type="IN">Character to find</param>
 * <result>Returns the find position or NULL if not found</result>
 */
DEF_ITF_API(`RTS_CWCHAR*', `CDECL', `CMUtlcwstrchr', `(const RTS_CWCHAR *pwsz, RTS_CWCHAR cw)')

/**
 * <description> 
 *  Binary search for a RTS_UI32 key in an array. Array can be an array of structure and the structure contains a member with the key.
 * </description>
 * <param name="pui8SearchArray" type="IN">Pointer to search array. Can be an array of a structure</param>
 * <param name="siSearchArraySize" type="IN">Size of the search array in bytes</param>
 * <param name="siSearchElementSize" type="IN">Size of one array element (if it is an array of a structure, this is the structure size)</param>
 * <param name="siSearchElementKeyOffset" type="IN">Offset within an array element to find the key value</param>
 * <param name="siMin" type="IN">Minimal index in the array to start the search</param>
 * <param name="ui32Key" type="IN">Key value to search for</param>
 * <param name="pResult" type="OUT">Pointer to error code:
 *	<ul>
 *     <li>ERR_OK: Key found</li>
 *     <li>ERR_NO_OBJECT: Key not found</li> 
 *  </ul>
 * </param>
 * <result>Returns the find position or RTS_SIZE_MAX if not found</result>
 */
DEF_ITF_API(`RTS_SIZE', `CDECL', `CMUtlBinarySearch_UI32', `(RTS_UI8 *pui8SearchArray, RTS_SIZE siSearchArraySize, RTS_SIZE siSearchElementSize, RTS_SIZE siSearchElementKeyOffset, RTS_SIZE siMin, RTS_UI32 ui32Key, RTS_RESULT *pResult)')

#ifdef __cplusplus
}
#endif
