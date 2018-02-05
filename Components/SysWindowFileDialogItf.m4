/**
 * <interfacename>SysWindowFileDialog</interfacename>
 * <description> 
 *	<p>The SysWindowFileDialog interface is designed to have access to a file dialog that is displayed when a screen is available.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysWindowFileDialog')

#include "CmpItf.h"
#include "CmpStd.h"
REF_ITF(`SysFileItf.m4')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysWindowFileDlgOpen',`(RTS_HANDLE hParentWindow, SysWinFileDlgOpenOptions* pOptions, SysWinFileDlgResult* pFileResult)')

#ifdef __cplusplus
}
#endif
