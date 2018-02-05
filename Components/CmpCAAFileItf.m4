SET_INTERFACE_NAME(`CmpCAAFile')

#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAAFile.h"
#include "CAAAsyncMan.h"
#include "CAAMemBlockMan.h"

#ifdef __cplusplus
extern "C" {
#endif

DEF_ITF_API(`CAA_ERROR',`CDECL',`FILE_WorkerInit',`(void)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`FILE_WorkerExit',`(void)')

#ifdef __cplusplus
}
#endif


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Closes the file synchonously. Only to be called by FileClass.Close in FB_Exit. 
 */
typedef struct tagfile_close_struct
{
	CAA_HANDLE hFile;					/* VAR_INPUT */	
	CAA_ERROR FILE_Close;				/* VAR_OUTPUT */	
} file_close_struct;

DEF_API(`void',`CDECL',`file_close',`(file_close_struct *p)',1,RTSITF_GET_SIGNATURE(0xF6BFBE32, 0x2085E894),0x03050600)

/**
 * Closes the directory synchonously. Only to be called by DirClass.Close in FB_Exit. 
 */
typedef struct tagfile_dirclose_struct
{
	CAA_HANDLE hDir;					/* VAR_INPUT */	
	CAA_ERROR FILE_DirClose;			/* VAR_OUTPUT */	
} file_dirclose_struct;

DEF_API(`void',`CDECL',`file_dirclose',`(file_dirclose_struct *p)',1,RTSITF_GET_SIGNATURE(0x8C6E5952, 0xD80E92CA),0x03050600)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/
