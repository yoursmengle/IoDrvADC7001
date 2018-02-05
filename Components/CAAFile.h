/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		CAACallback.h
*	Version:		2.4
*	Purpose:		Interface to the CAA callback handler.
*
******************************************************************************/
#ifndef __CAA_FILE_H__
#define __CAA_FILE_H__

#ifdef CAALib

#include "CAADefines.h"

#ifdef CAA_FILE

/**
 * <description>MODE</description>
 */
typedef enum
{
	FILE_MWRITE = 0,
	FILE_MREAD = 1,
	FILE_MRDWR = 2,
	FILE_MAPPD = 3
} FILE_MODE;

/**
 * <description>ERROR</description>
 */
#define	FILE_NO_ERROR			((CAA_ERROR)0)
#define	FILE_FIRST_ERROR		((CAA_ERROR)5100)
#define	FILE_TIME_OUT			((CAA_ERROR)5101)
#define	FILE_ABORT				((CAA_ERROR)5102)
#define	FILE_HANDLE_INVALID		((CAA_ERROR)5103)
#define	FILE_NOT_EXIST			((CAA_ERROR)5104)
#define	FILE_EXIST				((CAA_ERROR)5105)
#define	FILE_NO_MORE_ENTRIES	((CAA_ERROR)5106)
#define	FILE_NOT_EMPTY			((CAA_ERROR)5107)
#define	FILE_READ_ONLY_CAA		((CAA_ERROR)5108)
#define	FILE_WRONG_PARAMETER	((CAA_ERROR)5109)
#define	FILE_ERROR_UNKNOWN		((CAA_ERROR)5110)
#define	FILE_WRITE_INCOMPLETE	((CAA_ERROR)5111)
#define	FILE_NOT_IMPLEMENTED	((CAA_ERROR)5112)
#define ASM_CREATEJOB_FAILED	((CAA_ERROR)5113)
#define FILE_OPERATION_DENIED	((CAA_ERROR)5114)
#define	FILE_FIRST_MF			((CAA_ERROR)5150)
#define	FILE_LAST_ERROR			((CAA_ERROR)5199)

/**
 * <description>ATTRIB</description>
 */
typedef enum
{
	FILE_ARCHIVE = 0,
	FILE_HIDDEN = 1,
	FILE_NORMAL = 2,
	FILE_READONLY = 3
} FILE_ATTRIB;

/**
 * <description>DIR_ENTRY</description>
 */
typedef struct tagDIR_ENTRY
{
	CAA_FILENAME sEntry;
	CAA_SIZE szSize;
	CAA_BOOL xDirectory;
	CAA_BOOL xExclusive;
	CAA_DT dtLastModification;
} FILE_DIR_ENTRY;

typedef struct
{
	CAA_FILENAME sFileName;				/* VAR_INPUT */
	CAA_ENUM eFileMode;					/* VAR_INPUT */
	CAA_BOOL xExclusive;				/* VAR_INPUT */
	unsigned char dummy;
	CAA_HANDLE hFile;
} FILE_WOpenParams;

typedef struct
{
	CAA_HANDLE hFile;
} FILE_WCloseParams;

typedef struct
{
	CAA_FILENAME sFileNameDest;	
	CAA_FILENAME sFileNameSource;
	CAA_BOOL xOverWrite;
	unsigned char abyDummy[3];
	CAA_SIZE szSize;
}FILE_WCopyParams;

typedef struct
{
	CAA_FILENAME sFileName;
}FILE_WDeleteParams;

typedef struct
{
	CAA_HANDLE hDir;
}FILE_WDirCloseParams;

typedef struct
{
	CAA_FILENAME sDirName;
	CAA_BOOL xParent;
}FILE_WDirCreateParams;

typedef struct
{
	CAA_HANDLE hDir;
	FILE_DIR_ENTRY deDirEntry;
}FILE_WDirListParams;

typedef struct
{
	CAA_FILENAME sDirName;
	CAA_HANDLE hDir;
}FILE_WDirOpenParams;

typedef struct
{
	CAA_FILENAME sDirName;
	CAA_BOOL xRecursive;
}FILE_WDirRemoveParams;

typedef struct
{
	CAA_FILENAME sDirNameOld;
	CAA_FILENAME sDirNameNew;
}FILE_WDirRenameParams;

typedef struct
{
	CAA_HANDLE hFile;
	CAA_BOOL xEOF;
}FILE_WEOFParams;

typedef struct
{
	CAA_HANDLE hFile;
	RTS_IEC_UXINT udiPos;
}FILE_WGetPosParams;

typedef struct
{
	CAA_FILENAME sFileName;
}FILE_WGetRootParams;

typedef struct
{
	CAA_FILENAME sFileName;
	CAA_SIZE szSize;
}FILE_WGetSizeParams;

typedef struct
{
	CAA_FILENAME sFileName;
	CAA_DT dtLastModification;
}FILE_WGetTimeParams;

typedef struct
{
	CAA_HANDLE hFile;
	CAA_PVOID pBuffer;
	CAA_SIZE szBuffer;
	CAA_SIZE szSize; /*Return value*/
}FILE_WReadParams;

typedef struct
{
	CAA_FILENAME sFileNameOld;
	CAA_FILENAME sFileNameNew;
}FILE_WRenameParams;

typedef struct
{
	CAA_HANDLE hFile;
	CAA_ENUM eFileAttrib;
}FILE_WSetAtParams;

typedef struct
{
	CAA_HANDLE hFile;
	CAA_ENUM eFileAttrib;
}FILE_WGetAtParams;

typedef struct
{
	CAA_HANDLE hFile;
	RTS_IEC_UXINT udiPos;
}FILE_WSetPosParams;

typedef struct
{
	CAA_FILENAME sFileName;
}FILE_WSetRootParams;

typedef struct
{
	CAA_HANDLE hFile;
	CAA_PVOID pBuffer;
	CAA_SIZE szSize;
}FILE_WWriteParams;

typedef struct
{
	CAA_HANDLE hFile;
}FILE_WFlushParams;

typedef struct
{
	CAA_FILENAME sDirNameDest;
	CAA_FILENAME sDirNameSource;
	CAA_BOOL xRecursive;
	CAA_BOOL xOverWrite;
}FILE_WDirCopyParams;

#endif /*__CAA_FILE_H__*/
#endif /* CAA_FILE */
#endif /* CAALib */
