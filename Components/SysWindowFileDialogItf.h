 /**
 * <interfacename>SysWindowFileDialog</interfacename>
 * <description> 
 *	<p>The SysWindowFileDialog interface is designed to have access to a file dialog that is displayed when a screen is available.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSWINDOWFILEDIALOGITF_H_
#define _SYSWINDOWFILEDIALOGITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "CmpStd.h"
#include "SysFileItf.h"

typedef struct
{
	/* the number of filters */
	int iFilterCount;
	/* an array of pointers to strings where each is a description of a filter. the form of such a filter is
	<description>|<filter>, eg. "Txt-Files|*.txt" */
	char** ppFilters;		
} SysWinFileDlgOpenFilters;

typedef struct
{
	SysWinFileDlgOpenFilters Filters;	/* the filters for the file dialog */
	RTS_IEC_BOOL	bSaveDlg;		/* if true a save dialog will be shown, otherwise an open dialog */
	RTS_IEC_STRING*	pszInitFile;	/* the initially selected file or NULL if there is no preselection */
	RTS_IEC_STRING* pszTitle;		/* the title of the dialog, may be NULL */
	RTS_IEC_DWORD	dwFlags;		/* some flags, TODO: define */
	RTS_IEC_DWORD	dwAdditional;	/* some additional data, depending on the flags, not yet implemented */
} SysWinFileDlgOpenOptions;

/* the states of a file dialog operation */
#define SYSWINFILEDLG_STATE_PENDING				1
#define SYSWINFILEDLG_STATE_OPEN				2
#define SYSWINFILEDLG_STATE_CLOSED_OK			3
#define SYSWINFILEDLG_STATE_CLOSED_CANCEL		4

typedef struct
{
	RTS_IEC_DWORD			resultType;						/* not yet used */
	RTS_IEC_STRING			selectedPath[MAX_PATH_LEN];		/* the selected path, valid if state == CLOSED_OK, else an empty string */
} SysWinFileDlgResult;

#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysWindowFileDialogOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysWindowFileDialogOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description></description>
 * <param name="iMaxMsgs" type="IN"></param>
 * <param name="iOptions" type="IN"></param>
 * <param name="pResult" type="OUT"></param>
 * <result>Handle to a structure describing the opened file dialog and its result or RTS_INVALID_HANDLE if failed</result>
 */
RTS_RESULT CDECL SysWindowFileDlgOpen(RTS_HANDLE hParentWindow, SysWinFileDlgOpenOptions* pOptions, SysWinFileDlgResult* pFileResult);
typedef RTS_RESULT (CDECL * PFSYSWINDOWFILEDLGOPEN) (RTS_HANDLE hParentWindow, SysWinFileDlgOpenOptions* pOptions, SysWinFileDlgResult* pFileResult);
#if defined(SYSWINDOWFILEDIALOG_NOTIMPLEMENTED) || defined(SYSWINDOWFILEDLGOPEN_NOTIMPLEMENTED)
	#define USE_SysWindowFileDlgOpen
	#define EXT_SysWindowFileDlgOpen
	#define GET_SysWindowFileDlgOpen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowFileDlgOpen(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowFileDlgOpen  FALSE
	#define EXP_SysWindowFileDlgOpen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowFileDlgOpen
	#define EXT_SysWindowFileDlgOpen
	#define GET_SysWindowFileDlgOpen(fl)  CAL_CMGETAPI( "SysWindowFileDlgOpen" ) 
	#define CAL_SysWindowFileDlgOpen  SysWindowFileDlgOpen
	#define CHK_SysWindowFileDlgOpen  TRUE
	#define EXP_SysWindowFileDlgOpen  CAL_CMEXPAPI( "SysWindowFileDlgOpen" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOWFILEDIALOG_EXTERNAL)
	#define USE_SysWindowFileDlgOpen
	#define EXT_SysWindowFileDlgOpen
	#define GET_SysWindowFileDlgOpen(fl)  CAL_CMGETAPI( "SysWindowFileDlgOpen" ) 
	#define CAL_SysWindowFileDlgOpen  SysWindowFileDlgOpen
	#define CHK_SysWindowFileDlgOpen  TRUE
	#define EXP_SysWindowFileDlgOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowFileDlgOpen", (RTS_UINTPTR)SysWindowFileDlgOpen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowFileDialogSysWindowFileDlgOpen
	#define EXT_SysWindowFileDialogSysWindowFileDlgOpen
	#define GET_SysWindowFileDialogSysWindowFileDlgOpen  ERR_OK
	#define CAL_SysWindowFileDialogSysWindowFileDlgOpen pISysWindowFileDialog->ISysWindowFileDlgOpen
	#define CHK_SysWindowFileDialogSysWindowFileDlgOpen (pISysWindowFileDialog != NULL)
	#define EXP_SysWindowFileDialogSysWindowFileDlgOpen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowFileDlgOpen
	#define EXT_SysWindowFileDlgOpen
	#define GET_SysWindowFileDlgOpen(fl)  CAL_CMGETAPI( "SysWindowFileDlgOpen" ) 
	#define CAL_SysWindowFileDlgOpen pISysWindowFileDialog->ISysWindowFileDlgOpen
	#define CHK_SysWindowFileDlgOpen (pISysWindowFileDialog != NULL)
	#define EXP_SysWindowFileDlgOpen  CAL_CMEXPAPI( "SysWindowFileDlgOpen" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowFileDlgOpen  PFSYSWINDOWFILEDLGOPEN pfSysWindowFileDlgOpen;
	#define EXT_SysWindowFileDlgOpen  extern PFSYSWINDOWFILEDLGOPEN pfSysWindowFileDlgOpen;
	#define GET_SysWindowFileDlgOpen(fl)  s_pfCMGetAPI2( "SysWindowFileDlgOpen", (RTS_VOID_FCTPTR *)&pfSysWindowFileDlgOpen, (fl), 0, 0)
	#define CAL_SysWindowFileDlgOpen  pfSysWindowFileDlgOpen
	#define CHK_SysWindowFileDlgOpen  (pfSysWindowFileDlgOpen != NULL)
	#define EXP_SysWindowFileDlgOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowFileDlgOpen", (RTS_UINTPTR)SysWindowFileDlgOpen, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSWINDOWFILEDLGOPEN ISysWindowFileDlgOpen;
 } ISysWindowFileDialog_C;

#ifdef CPLUSPLUS
class ISysWindowFileDialog : public IBase
{
	public:
		virtual RTS_RESULT CDECL ISysWindowFileDlgOpen(RTS_HANDLE hParentWindow, SysWinFileDlgOpenOptions* pOptions, SysWinFileDlgResult* pFileResult) =0;
};
	#ifndef ITF_SysWindowFileDialog
		#define ITF_SysWindowFileDialog static ISysWindowFileDialog *pISysWindowFileDialog = NULL;
	#endif
	#define EXTITF_SysWindowFileDialog
#else	/*CPLUSPLUS*/
	typedef ISysWindowFileDialog_C		ISysWindowFileDialog;
	#ifndef ITF_SysWindowFileDialog
		#define ITF_SysWindowFileDialog
	#endif
	#define EXTITF_SysWindowFileDialog
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSWINDOWFILEDIALOGITF_H_*/
