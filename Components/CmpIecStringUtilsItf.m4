SET_INTERFACE_NAME(`CmpIecStringUtils')

#include "CmpItf.h"

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif
/**
 * Does a sprintf for the given format string and the given variable. Will not return NULL!
 */
typedef struct tagstusprintf_struct
{
	RTS_IEC_STRING *pstFormat;			/* VAR_INPUT */	/* the formatstring */
	RTS_IEC_DWORD *pVarAdr;				/* VAR_INPUT */	/* the address of the variable that shall be printed */
	RTS_IEC_DWORD udiVarType;			/* VAR_INPUT, Enum: TYPE_CLASS */
	RTS_IEC_BYTE *pBuffer;				/* VAR_INPUT */	/* the buffer where the text is to be printed */
	RTS_IEC_UDINT dwBufferSize;			/* VAR_INPUT */	/* the size of the buffer in bytes */
	RTS_IEC_INT StuSprintf;				/* VAR_OUTPUT */	
} stusprintf_struct;

DEF_API(`void',`CDECL',`stusprintf',`(stusprintf_struct *p)',1,0,0x03050500)

/**
 * Does a sprintf for the given format string and the given variable. Will not return NULL!
 */
typedef struct tagstusprintfw_struct
{
	RTS_IEC_WSTRING *wstFormat;			/* VAR_INPUT */	/* the formatstring */
	RTS_IEC_DWORD *pVarAdr;				/* VAR_INPUT */	/* the address of the variable that shall be printed */
	RTS_IEC_DWORD udiVarType;			/* VAR_INPUT, Enum: TYPE_CLASS */
	RTS_IEC_BYTE *pBuffer;				/* VAR_INPUT */	/* the buffer where the text is to be printed */
	RTS_IEC_UDINT dwBufferSize;			/* VAR_INPUT */	/* the size of the buffer in bytes, not in wstring characters! */
	RTS_IEC_INT StuSprintfW;			/* VAR_OUTPUT */	
} stusprintfw_struct;

DEF_API(`void',`CDECL',`stusprintfw',`(stusprintfw_struct *p)',1,0,0x03050500)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

