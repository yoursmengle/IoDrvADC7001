 
	
	
#ifndef _CMPCAAFILEITF_H_
#define _CMPCAAFILEITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAAFile.h"
#include "CAAAsyncMan.h"
#include "CAAMemBlockMan.h"

#ifdef __cplusplus
extern "C" {
#endif

CAA_ERROR CDECL FILE_WorkerInit(void);
typedef CAA_ERROR (CDECL * PFFILE_WORKERINIT) (void);
#if defined(CMPCAAFILE_NOTIMPLEMENTED) || defined(FILE_WORKERINIT_NOTIMPLEMENTED)
	#define USE_FILE_WorkerInit
	#define EXT_FILE_WorkerInit
	#define GET_FILE_WorkerInit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_FILE_WorkerInit()  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_FILE_WorkerInit  FALSE
	#define EXP_FILE_WorkerInit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_FILE_WorkerInit
	#define EXT_FILE_WorkerInit
	#define GET_FILE_WorkerInit(fl)  CAL_CMGETAPI( "FILE_WorkerInit" ) 
	#define CAL_FILE_WorkerInit  FILE_WorkerInit
	#define CHK_FILE_WorkerInit  TRUE
	#define EXP_FILE_WorkerInit  CAL_CMEXPAPI( "FILE_WorkerInit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAFILE_EXTERNAL)
	#define USE_FILE_WorkerInit
	#define EXT_FILE_WorkerInit
	#define GET_FILE_WorkerInit(fl)  CAL_CMGETAPI( "FILE_WorkerInit" ) 
	#define CAL_FILE_WorkerInit  FILE_WorkerInit
	#define CHK_FILE_WorkerInit  TRUE
	#define EXP_FILE_WorkerInit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FILE_WorkerInit", (RTS_UINTPTR)FILE_WorkerInit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAFileFILE_WorkerInit
	#define EXT_CmpCAAFileFILE_WorkerInit
	#define GET_CmpCAAFileFILE_WorkerInit  ERR_OK
	#define CAL_CmpCAAFileFILE_WorkerInit pICmpCAAFile->IFILE_WorkerInit
	#define CHK_CmpCAAFileFILE_WorkerInit (pICmpCAAFile != NULL)
	#define EXP_CmpCAAFileFILE_WorkerInit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_FILE_WorkerInit
	#define EXT_FILE_WorkerInit
	#define GET_FILE_WorkerInit(fl)  CAL_CMGETAPI( "FILE_WorkerInit" ) 
	#define CAL_FILE_WorkerInit pICmpCAAFile->IFILE_WorkerInit
	#define CHK_FILE_WorkerInit (pICmpCAAFile != NULL)
	#define EXP_FILE_WorkerInit  CAL_CMEXPAPI( "FILE_WorkerInit" ) 
#else /* DYNAMIC_LINK */
	#define USE_FILE_WorkerInit  PFFILE_WORKERINIT pfFILE_WorkerInit;
	#define EXT_FILE_WorkerInit  extern PFFILE_WORKERINIT pfFILE_WorkerInit;
	#define GET_FILE_WorkerInit(fl)  s_pfCMGetAPI2( "FILE_WorkerInit", (RTS_VOID_FCTPTR *)&pfFILE_WorkerInit, (fl), 0, 0)
	#define CAL_FILE_WorkerInit  pfFILE_WorkerInit
	#define CHK_FILE_WorkerInit  (pfFILE_WorkerInit != NULL)
	#define EXP_FILE_WorkerInit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FILE_WorkerInit", (RTS_UINTPTR)FILE_WorkerInit, 0, 0) 
#endif



CAA_ERROR CDECL FILE_WorkerExit(void);
typedef CAA_ERROR (CDECL * PFFILE_WORKEREXIT) (void);
#if defined(CMPCAAFILE_NOTIMPLEMENTED) || defined(FILE_WORKEREXIT_NOTIMPLEMENTED)
	#define USE_FILE_WorkerExit
	#define EXT_FILE_WorkerExit
	#define GET_FILE_WorkerExit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_FILE_WorkerExit()  (CAA_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_FILE_WorkerExit  FALSE
	#define EXP_FILE_WorkerExit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_FILE_WorkerExit
	#define EXT_FILE_WorkerExit
	#define GET_FILE_WorkerExit(fl)  CAL_CMGETAPI( "FILE_WorkerExit" ) 
	#define CAL_FILE_WorkerExit  FILE_WorkerExit
	#define CHK_FILE_WorkerExit  TRUE
	#define EXP_FILE_WorkerExit  CAL_CMEXPAPI( "FILE_WorkerExit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAAFILE_EXTERNAL)
	#define USE_FILE_WorkerExit
	#define EXT_FILE_WorkerExit
	#define GET_FILE_WorkerExit(fl)  CAL_CMGETAPI( "FILE_WorkerExit" ) 
	#define CAL_FILE_WorkerExit  FILE_WorkerExit
	#define CHK_FILE_WorkerExit  TRUE
	#define EXP_FILE_WorkerExit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FILE_WorkerExit", (RTS_UINTPTR)FILE_WorkerExit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAFileFILE_WorkerExit
	#define EXT_CmpCAAFileFILE_WorkerExit
	#define GET_CmpCAAFileFILE_WorkerExit  ERR_OK
	#define CAL_CmpCAAFileFILE_WorkerExit pICmpCAAFile->IFILE_WorkerExit
	#define CHK_CmpCAAFileFILE_WorkerExit (pICmpCAAFile != NULL)
	#define EXP_CmpCAAFileFILE_WorkerExit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_FILE_WorkerExit
	#define EXT_FILE_WorkerExit
	#define GET_FILE_WorkerExit(fl)  CAL_CMGETAPI( "FILE_WorkerExit" ) 
	#define CAL_FILE_WorkerExit pICmpCAAFile->IFILE_WorkerExit
	#define CHK_FILE_WorkerExit (pICmpCAAFile != NULL)
	#define EXP_FILE_WorkerExit  CAL_CMEXPAPI( "FILE_WorkerExit" ) 
#else /* DYNAMIC_LINK */
	#define USE_FILE_WorkerExit  PFFILE_WORKEREXIT pfFILE_WorkerExit;
	#define EXT_FILE_WorkerExit  extern PFFILE_WORKEREXIT pfFILE_WorkerExit;
	#define GET_FILE_WorkerExit(fl)  s_pfCMGetAPI2( "FILE_WorkerExit", (RTS_VOID_FCTPTR *)&pfFILE_WorkerExit, (fl), 0, 0)
	#define CAL_FILE_WorkerExit  pfFILE_WorkerExit
	#define CHK_FILE_WorkerExit  (pfFILE_WorkerExit != NULL)
	#define EXP_FILE_WorkerExit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"FILE_WorkerExit", (RTS_UINTPTR)FILE_WorkerExit, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

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

void CDECL CDECL_EXT file_close(file_close_struct *p);
typedef void (CDECL CDECL_EXT* PFFILE_CLOSE_IEC) (file_close_struct *p);
#if defined(CMPCAAFILE_NOTIMPLEMENTED) || defined(FILE_CLOSE_NOTIMPLEMENTED)
	#define USE_file_close
	#define EXT_file_close
	#define GET_file_close(fl)  ERR_NOTIMPLEMENTED
	#define CAL_file_close(p0) 
	#define CHK_file_close  FALSE
	#define EXP_file_close  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_file_close
	#define EXT_file_close
	#define GET_file_close(fl)  CAL_CMGETAPI( "file_close" ) 
	#define CAL_file_close  file_close
	#define CHK_file_close  TRUE
	#define EXP_file_close  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"file_close", (RTS_UINTPTR)file_close, 1, RTSITF_GET_SIGNATURE(0xF6BFBE32, 0x2085E894), 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPCAAFILE_EXTERNAL)
	#define USE_file_close
	#define EXT_file_close
	#define GET_file_close(fl)  CAL_CMGETAPI( "file_close" ) 
	#define CAL_file_close  file_close
	#define CHK_file_close  TRUE
	#define EXP_file_close  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"file_close", (RTS_UINTPTR)file_close, 1, RTSITF_GET_SIGNATURE(0xF6BFBE32, 0x2085E894), 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAFilefile_close
	#define EXT_CmpCAAFilefile_close
	#define GET_CmpCAAFilefile_close  ERR_OK
	#define CAL_CmpCAAFilefile_close  file_close
	#define CHK_CmpCAAFilefile_close  TRUE
	#define EXP_CmpCAAFilefile_close  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"file_close", (RTS_UINTPTR)file_close, 1, RTSITF_GET_SIGNATURE(0xF6BFBE32, 0x2085E894), 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_file_close
	#define EXT_file_close
	#define GET_file_close(fl)  CAL_CMGETAPI( "file_close" ) 
	#define CAL_file_close  file_close
	#define CHK_file_close  TRUE
	#define EXP_file_close  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"file_close", (RTS_UINTPTR)file_close, 1, RTSITF_GET_SIGNATURE(0xF6BFBE32, 0x2085E894), 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_file_close  PFFILE_CLOSE_IEC pffile_close;
	#define EXT_file_close  extern PFFILE_CLOSE_IEC pffile_close;
	#define GET_file_close(fl)  s_pfCMGetAPI2( "file_close", (RTS_VOID_FCTPTR *)&pffile_close, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0xF6BFBE32, 0x2085E894), 0x03050600)
	#define CAL_file_close  pffile_close
	#define CHK_file_close  (pffile_close != NULL)
	#define EXP_file_close   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"file_close", (RTS_UINTPTR)file_close, 1, RTSITF_GET_SIGNATURE(0xF6BFBE32, 0x2085E894), 0x03050600) 
#endif


/**
 * Closes the directory synchonously. Only to be called by DirClass.Close in FB_Exit. 
 */
typedef struct tagfile_dirclose_struct
{
	CAA_HANDLE hDir;					/* VAR_INPUT */	
	CAA_ERROR FILE_DirClose;			/* VAR_OUTPUT */	
} file_dirclose_struct;

void CDECL CDECL_EXT file_dirclose(file_dirclose_struct *p);
typedef void (CDECL CDECL_EXT* PFFILE_DIRCLOSE_IEC) (file_dirclose_struct *p);
#if defined(CMPCAAFILE_NOTIMPLEMENTED) || defined(FILE_DIRCLOSE_NOTIMPLEMENTED)
	#define USE_file_dirclose
	#define EXT_file_dirclose
	#define GET_file_dirclose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_file_dirclose(p0) 
	#define CHK_file_dirclose  FALSE
	#define EXP_file_dirclose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_file_dirclose
	#define EXT_file_dirclose
	#define GET_file_dirclose(fl)  CAL_CMGETAPI( "file_dirclose" ) 
	#define CAL_file_dirclose  file_dirclose
	#define CHK_file_dirclose  TRUE
	#define EXP_file_dirclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"file_dirclose", (RTS_UINTPTR)file_dirclose, 1, RTSITF_GET_SIGNATURE(0x8C6E5952, 0xD80E92CA), 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPCAAFILE_EXTERNAL)
	#define USE_file_dirclose
	#define EXT_file_dirclose
	#define GET_file_dirclose(fl)  CAL_CMGETAPI( "file_dirclose" ) 
	#define CAL_file_dirclose  file_dirclose
	#define CHK_file_dirclose  TRUE
	#define EXP_file_dirclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"file_dirclose", (RTS_UINTPTR)file_dirclose, 1, RTSITF_GET_SIGNATURE(0x8C6E5952, 0xD80E92CA), 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAFilefile_dirclose
	#define EXT_CmpCAAFilefile_dirclose
	#define GET_CmpCAAFilefile_dirclose  ERR_OK
	#define CAL_CmpCAAFilefile_dirclose  file_dirclose
	#define CHK_CmpCAAFilefile_dirclose  TRUE
	#define EXP_CmpCAAFilefile_dirclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"file_dirclose", (RTS_UINTPTR)file_dirclose, 1, RTSITF_GET_SIGNATURE(0x8C6E5952, 0xD80E92CA), 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_file_dirclose
	#define EXT_file_dirclose
	#define GET_file_dirclose(fl)  CAL_CMGETAPI( "file_dirclose" ) 
	#define CAL_file_dirclose  file_dirclose
	#define CHK_file_dirclose  TRUE
	#define EXP_file_dirclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"file_dirclose", (RTS_UINTPTR)file_dirclose, 1, RTSITF_GET_SIGNATURE(0x8C6E5952, 0xD80E92CA), 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_file_dirclose  PFFILE_DIRCLOSE_IEC pffile_dirclose;
	#define EXT_file_dirclose  extern PFFILE_DIRCLOSE_IEC pffile_dirclose;
	#define GET_file_dirclose(fl)  s_pfCMGetAPI2( "file_dirclose", (RTS_VOID_FCTPTR *)&pffile_dirclose, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0x8C6E5952, 0xD80E92CA), 0x03050600)
	#define CAL_file_dirclose  pffile_dirclose
	#define CHK_file_dirclose  (pffile_dirclose != NULL)
	#define EXP_file_dirclose   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"file_dirclose", (RTS_UINTPTR)file_dirclose, 1, RTSITF_GET_SIGNATURE(0x8C6E5952, 0xD80E92CA), 0x03050600) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/



typedef struct
{
	IBase_C *pBase;
	PFFILE_WORKERINIT IFILE_WorkerInit;
 	PFFILE_WORKEREXIT IFILE_WorkerExit;
 } ICmpCAAFile_C;

#ifdef CPLUSPLUS
class ICmpCAAFile : public IBase
{
	public:
		virtual CAA_ERROR CDECL IFILE_WorkerInit(void) =0;
		virtual CAA_ERROR CDECL IFILE_WorkerExit(void) =0;
};
	#ifndef ITF_CmpCAAFile
		#define ITF_CmpCAAFile static ICmpCAAFile *pICmpCAAFile = NULL;
	#endif
	#define EXTITF_CmpCAAFile
#else	/*CPLUSPLUS*/
	typedef ICmpCAAFile_C		ICmpCAAFile;
	#ifndef ITF_CmpCAAFile
		#define ITF_CmpCAAFile
	#endif
	#define EXTITF_CmpCAAFile
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCAAFILEITF_H_*/
