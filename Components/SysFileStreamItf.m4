/**
 * <interfacename>SysFileStream23</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`SysFileStream')

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>sysfilestreamclearerr</description>
 */
typedef struct tagsysfilestreamclearerr_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamClearerr;	/* VAR_OUTPUT */
} sysfilestreamclearerr_struct;

DEF_API(`void',`CDECL',`sysfilestreamclearerr',`(sysfilestreamclearerr_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1B38E038),0x03050000)

/**
 * <description>sysfilestreamfclose</description>
 */
typedef struct tagsysfilestreamfclose_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFClose;	/* VAR_OUTPUT */
} sysfilestreamfclose_struct;

DEF_API(`void',`CDECL',`sysfilestreamfclose',`(sysfilestreamfclose_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x01C196F3),0x03050000)

/**
 * <description>sysfilestreamfeof</description>
 */
typedef struct tagsysfilestreamfeof_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFEOF;		/* VAR_OUTPUT */
} sysfilestreamfeof_struct;

DEF_API(`void',`CDECL',`sysfilestreamfeof',`(sysfilestreamfeof_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCCFD6E4A),0x03050000)

/**
 * <description>sysfilestreamferror</description>
 */
typedef struct tagsysfilestreamferror_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFError;	/* VAR_OUTPUT */
} sysfilestreamferror_struct;

DEF_API(`void',`CDECL',`sysfilestreamferror',`(sysfilestreamferror_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x7C8AC3DB),0x03050000)

/**
 * <description>sysfilestreamfflush</description>
 */
typedef struct tagsysfilestreamfflush_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFFlush;	/* VAR_OUTPUT */
} sysfilestreamfflush_struct;

DEF_API(`void',`CDECL',`sysfilestreamfflush',`(sysfilestreamfflush_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4FE8ECB6),0x03050000)

/**
 * <description>sysfilestreamfgetc</description>
 */
typedef struct tagsysfilestreamfgetc_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFGetC;	/* VAR_OUTPUT */
} sysfilestreamfgetc_struct;

DEF_API(`void',`CDECL',`sysfilestreamfgetc',`(sysfilestreamfgetc_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x73628B5F),0x03050000)

/**
 * <description>sysfilestreamfgetpos</description>
 */
typedef struct tagsysfilestreamfgetpos_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_BYTE *pFPos;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFGetPos;	/* VAR_OUTPUT */
} sysfilestreamfgetpos_struct;

DEF_API(`void',`CDECL',`sysfilestreamfgetpos',`(sysfilestreamfgetpos_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xBFEA66FC),0x03050000)

/**
 * <description>sysfilestreamfgets</description>
 */
typedef struct tagsysfilestreamfgets_struct
{
	RTS_IEC_STRING *str;				/* VAR_INPUT */
	RTS_IEC_DINT n;						/* VAR_INPUT */
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_STRING *SysFileStreamFGetS;	/* VAR_OUTPUT */
} sysfilestreamfgets_struct;

DEF_API(`void',`CDECL',`sysfilestreamfgets',`(sysfilestreamfgets_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x8E1D114C),0x03050000)

/**
 * <description>sysfilestreamfopen</description>
 */
typedef struct tagsysfilestreamfopen_struct
{
	RTS_IEC_STRING *FileName;			/* VAR_INPUT */
	RTS_IEC_STRING *Mode;				/* VAR_INPUT */
	RTS_IEC_HANDLE SysFileStreamFOpen;	/* VAR_OUTPUT */
} sysfilestreamfopen_struct;

DEF_API(`void',`CDECL',`sysfilestreamfopen',`(sysfilestreamfopen_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0AD9CD95),0x03050000)

/**
 * <description>sysfilestreamfprintf_int</description>
 */
typedef struct tagsysfilestreamfprintf_int_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_STRING *szFormat;			/* VAR_INPUT */
	RTS_IEC_DINT nArg;					/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFPrintf_Int;	/* VAR_OUTPUT */
} sysfilestreamfprintf_int_struct;

DEF_API(`void',`CDECL',`sysfilestreamfprintf_int',`(sysfilestreamfprintf_int_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x2BB939E3),0x03050000)

/**
 * <description>sysfilestreamfprintf_real</description>
 */
typedef struct tagsysfilestreamfprintf_real_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_STRING *szFormat;			/* VAR_INPUT */
	RTS_IEC_REAL rArg;					/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFPrintf_Real;	/* VAR_OUTPUT */
} sysfilestreamfprintf_real_struct;

DEF_API(`void',`CDECL',`sysfilestreamfprintf_real',`(sysfilestreamfprintf_real_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x6F4D6A7C),0x03050000)

/**
 * <description>sysfilestreamfprintf_string</description>
 */
typedef struct tagsysfilestreamfprintf_string_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_STRING *szFormat;			/* VAR_INPUT */
	RTS_IEC_STRING *sArg;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFPrintf_String;	/* VAR_OUTPUT */
} sysfilestreamfprintf_string_struct;

DEF_API(`void',`CDECL',`sysfilestreamfprintf_string',`(sysfilestreamfprintf_string_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x7E3FE324),0x03050000)

/**
 * <description>sysfilestreamfputc</description>
 */
typedef struct tagsysfilestreamfputc_struct
{
	RTS_IEC_DINT c;						/* VAR_INPUT */
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFPutC;	/* VAR_OUTPUT */
} sysfilestreamfputc_struct;

DEF_API(`void',`CDECL',`sysfilestreamfputc',`(sysfilestreamfputc_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0E6EACA5),0x03050000)

/**
 * <description>sysfilestreamfputs</description>
 */
typedef struct tagsysfilestreamfputs_struct
{
	RTS_IEC_STRING *str;				/* VAR_INPUT */
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFPutS;	/* VAR_OUTPUT */
} sysfilestreamfputs_struct;

DEF_API(`void',`CDECL',`sysfilestreamfputs',`(sysfilestreamfputs_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x386D65D8),0x03050000)

/**
 * <description>sysfilestreamfread</description>
 */
typedef struct tagsysfilestreamfread_struct
{
	RTS_IEC_BYTE *Buffer;				/* VAR_INPUT */
	RTS_IEC_DWORD Size;					/* VAR_INPUT */
	RTS_IEC_DWORD NObjs;				/* VAR_INPUT */
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DWORD SysFileStreamFRead;	/* VAR_OUTPUT */
} sysfilestreamfread_struct;

DEF_API(`void',`CDECL',`sysfilestreamfread',`(sysfilestreamfread_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x04A4CE64),0x03050000)

/**
 * <description>sysfilestreamfscanf_int</description>
 */
typedef struct tagsysfilestreamfscanf_int_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_STRING *szFormat;			/* VAR_INPUT */
	RTS_IEC_DINT *pnArg;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFScanf_Int;	/* VAR_OUTPUT */
} sysfilestreamfscanf_int_struct;

DEF_API(`void',`CDECL',`sysfilestreamfscanf_int',`(sysfilestreamfscanf_int_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x797A9171),0x03050000)

/**
 * <description>sysfilestreamfscanf_real</description>
 */
typedef struct tagsysfilestreamfscanf_real_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_STRING *szFormat;			/* VAR_INPUT */
	RTS_IEC_REAL *pfArg;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFScanf_Real;	/* VAR_OUTPUT */
} sysfilestreamfscanf_real_struct;

DEF_API(`void',`CDECL',`sysfilestreamfscanf_real',`(sysfilestreamfscanf_real_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x35DAE113),0x03050000)

/**
 * <description>sysfilestreamfscanf_string</description>
 */
typedef struct tagsysfilestreamfscanf_string_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_STRING *szFormat;			/* VAR_INPUT */
	RTS_IEC_STRING *psArg;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFScanf_String;	/* VAR_OUTPUT */
} sysfilestreamfscanf_string_struct;

DEF_API(`void',`CDECL',`sysfilestreamfscanf_string',`(sysfilestreamfscanf_string_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB5F64354),0x03050000)

/**
 * <description>sysfilestreamfseek</description>
 */
typedef struct tagsysfilestreamfseek_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DINT offset;				/* VAR_INPUT */
	RTS_IEC_DINT origin;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFSeek;	/* VAR_OUTPUT */
} sysfilestreamfseek_struct;

DEF_API(`void',`CDECL',`sysfilestreamfseek',`(sysfilestreamfseek_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xFC0CF4A9),0x03050000)

/**
 * <description>sysfilestreamfsetpos</description>
 */
typedef struct tagsysfilestreamfsetpos_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_BYTE *pFPos;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFSetPos;	/* VAR_OUTPUT */
} sysfilestreamfsetpos_struct;

DEF_API(`void',`CDECL',`sysfilestreamfsetpos',`(sysfilestreamfsetpos_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x2E8D7680),0x03050000)

/**
 * <description>sysfilestreamftell</description>
 */
typedef struct tagsysfilestreamftell_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamFTell;	/* VAR_OUTPUT */
} sysfilestreamftell_struct;

DEF_API(`void',`CDECL',`sysfilestreamftell',`(sysfilestreamftell_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xAC140163),0x03050000)

/**
 * <description>sysfilestreamfwrite</description>
 */
typedef struct tagsysfilestreamfwrite_struct
{
	RTS_IEC_BYTE *Buffer;				/* VAR_INPUT */
	RTS_IEC_DWORD Size;					/* VAR_INPUT */
	RTS_IEC_DWORD NObjs;				/* VAR_INPUT */
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DWORD SysFileStreamFWrite;	/* VAR_OUTPUT */
} sysfilestreamfwrite_struct;

DEF_API(`void',`CDECL',`sysfilestreamfwrite',`(sysfilestreamfwrite_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD0E8E5B8),0x03050000)

/**
 * <description>sysfilestreamremove</description>
 */
typedef struct tagsysfilestreamremove_struct
{
	RTS_IEC_STRING *FileName;			/* VAR_INPUT */
	RTS_IEC_BOOL SysFileStreamRemove;	/* VAR_OUTPUT */
} sysfilestreamremove_struct;

DEF_API(`void',`CDECL',`sysfilestreamremove',`(sysfilestreamremove_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD7CA98CE),0x03050000)

/**
 * <description>sysfilestreamrename</description>
 */
typedef struct tagsysfilestreamrename_struct
{
	RTS_IEC_STRING *FileOldName;		/* VAR_INPUT */
	RTS_IEC_STRING *FileNewName;		/* VAR_INPUT */
	RTS_IEC_BOOL SysFileStreamRename;	/* VAR_OUTPUT */
} sysfilestreamrename_struct;

DEF_API(`void',`CDECL',`sysfilestreamrename',`(sysfilestreamrename_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xBE0E9BBF),0x03050000)

/**
 * <description>sysfilestreamrewind</description>
 */
typedef struct tagsysfilestreamrewind_struct
{
	RTS_IEC_HANDLE File;				/* VAR_INPUT */
	RTS_IEC_DINT SysFileStreamRewind;	/* VAR_OUTPUT */
} sysfilestreamrewind_struct;

DEF_API(`void',`CDECL',`sysfilestreamrewind',`(sysfilestreamrewind_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x2C2552D5),0x03050000)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

DEF_CREATEITF_API(`void*',`CDECL',`SysFileStreamFOpen',`(char *szFileName, char *szMode)')
DEF_DELETEITF_API(`int',`CDECL',`SysFileStreamFClose',`(void *pFile)')
DEF_HANDLEITF_API(`int',`CDECL',`SysFileStreamFFlush',`(void *pFile)')
DEF_HANDLEITF_API(`int',`CDECL',`SysFileStreamFPrintf_Int',`(void *pFile, char *szFormat, int nArg)')
DEF_HANDLEITF_API(`int',`CDECL',`SysFileStreamFPrintf_Real',`(void *pFile, char *szFormat, float fArg)')
DEF_HANDLEITF_API(`int',`CDECL',`SysFileStreamFPrintf_String',`(void *pFile, char *szFormat, char *pcArg)')
DEF_HANDLEITF_API(`int',`CDECL',`SysFileStreamFScanf_Int',`(void *pFile, char *szFormat, int *pnArg)')
DEF_HANDLEITF_API(`int',`CDECL',`SysFileStreamFScanf_Real',`(void *pFile, char *szFormat, float *pfArg)')
DEF_HANDLEITF_API(`int',`CDECL',`SysFileStreamFScanf_String',`(void *pFile, char *szFormat, char *pcArg)')
DEF_HANDLEITF_API(`int',`CDECL',`SysFileStreamFGetC',`(void *pFile)')
DEF_ITF_API2(`int',`CDECL',`SysFileStreamFPutc',`(int c, void *pFile)')
DEF_HANDLEITF_API(`int',`CDECL',`SysFileStreamFPutc2',`(void *pFile, int c)')
DEF_ITF_API2(`char*',`CDECL',`SysFileStreamFGetS',`(char *pcDest, int n, void* pFile)')
DEF_HANDLEITF_API(`char*',`CDECL',`SysFileStreamFGetS2',`(void* pFile, char *pcDest, int n)')
DEF_ITF_API2(`int',`CDECL',`SysFileStreamFPutS',`(char* pcSource, void* pFile)')
DEF_HANDLEITF_API(`int',`CDECL',`SysFileStreamFPutS2',`(void* pFile, char* pcSource)')
DEF_ITF_API2(`unsigned int',`CDECL',`SysFileStreamFRead',`(void *pDest, unsigned int uiSize, unsigned int uiNObjs, void *pFile)')
DEF_HANDLEITF_API(`unsigned int',`CDECL',`SysFileStreamFRead2',`(void *pFile, void *pDest, unsigned int uiSize, unsigned int uiNObjs)')
DEF_ITF_API2(`unsigned int',`CDECL',`SysFileStreamFWrite',`(void* pSource, unsigned int uiSize, unsigned int uiNObjs, void *pFile)')
DEF_HANDLEITF_API(`unsigned int',`CDECL',`SysFileStreamFWrite2',`(void *pFile, void* pSource, unsigned int uiSize, unsigned int uiNObjs)')
DEF_HANDLEITF_API(`int',`CDECL',`SysFileStreamFSeek',`(void* pFile, long lOffset, int origin)')
DEF_HANDLEITF_API(`long',`CDECL',`SysFileStreamFTell',`(void *pFile)')
DEF_HANDLEITF_API(`int',`CDECL',`SysFileStreamRewind',`(void *pFile)')
DEF_HANDLEITF_API(`int',`CDECL',`SysFileStreamFGetPos',`(void *pFile, long *plOffset)')
DEF_HANDLEITF_API(`int',`CDECL',`SysFileStreamFSetPos',`(void *pFile, long *plOffset)')
DEF_HANDLEITF_API(`long',`CDECL',`SysFileStreamClearerr',`(void *pFile)')
DEF_HANDLEITF_API(`int',`CDECL',`SysFileStreamFEOF',`(void *pFile)')
DEF_HANDLEITF_API(`int',`CDECL',`SysFileStreamFError',`(void *pFile)')
DEF_STATICITF_API(`int',`CDECL',`SysFileStreamRemove',`(char *szFileName)')
DEF_STATICITF_API(`int',`CDECL',`SysFileStreamRename',`(char *szOldFileName, char *szNewFileName)')

#ifdef __cplusplus
}
#endif

