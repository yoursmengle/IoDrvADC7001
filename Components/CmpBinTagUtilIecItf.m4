/**
 * <interfacename>CmpBinTagUtilIec</interfacename>
 * <description> 
 *	<p>Interface of the IEC binary tag utility</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpBinTagUtilIec')

/* --------- The writer interface ---------- */

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>BTagAlignment</description>
 */
typedef struct tagBTagAlignment
{
	RTS_IEC_UINT uiModulus;		
	RTS_IEC_UINT uiRemainder;		
} BTagAlignment;

/**
 * <description>btagreadercreate</description>
 */
typedef struct tagbtagreadercreate_struct
{
	RTS_IEC_BYTE *pBuffer;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwSize;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* optionally for an errorcode */
	RTS_IEC_HANDLE BTagReaderCreate;	/* VAR_OUTPUT */	
} btagreadercreate_struct;

DEF_API(`void',`CDECL',`btagreadercreate',`(btagreadercreate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1A997D85),0x03050500)

/**
 * <description>btagreadercreatedynamic</description>
 */
typedef struct tagbtagreadercreatedynamic_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* optionally for an errorcode */
	RTS_IEC_HANDLE BTagReaderCreateDynamic;	/* VAR_OUTPUT */	
} btagreadercreatedynamic_struct;

DEF_API(`void',`CDECL',`btagreadercreatedynamic',`(btagreadercreatedynamic_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xE334F937),0x03050500)

/**
 * <description>btagreaderdestroy</description>
 */
typedef struct tagbtagreaderdestroy_struct
{
	RTS_IEC_HANDLE hReader;				/* VAR_INPUT */	
	RTS_IEC_RESULT BTagReaderDestroy;	/* VAR_OUTPUT */	
} btagreaderdestroy_struct;

DEF_API(`void',`CDECL',`btagreaderdestroy',`(btagreaderdestroy_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x516D60C3),0x03050500)

/**
 * <description>btagreadergetcomplexcontent</description>
 */
typedef struct tagbtagreadergetcomplexcontent_struct
{
	RTS_IEC_HANDLE hReader;				/* VAR_INPUT */	
	RTS_IEC_BYTE **ppBuffer;			/* VAR_INPUT */	
	RTS_IEC_UDINT *pulSize;				/* VAR_INPUT */	
	RTS_IEC_RESULT BTagReaderGetComplexContent;	/* VAR_OUTPUT */	
} btagreadergetcomplexcontent_struct;

DEF_API(`void',`CDECL',`btagreadergetcomplexcontent',`(btagreadergetcomplexcontent_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x129CC395),0x03050500)

/**
 * <description>btagreadergetcontent</description>
 */
typedef struct tagbtagreadergetcontent_struct
{
	RTS_IEC_HANDLE hReader;				/* VAR_INPUT */	
	RTS_IEC_BYTE **ppBuffer;			/* VAR_INPUT */	
	RTS_IEC_UDINT *pulSize;				/* VAR_INPUT */	
	RTS_IEC_RESULT BTagReaderGetContent;	/* VAR_OUTPUT */	
} btagreadergetcontent_struct;

DEF_API(`void',`CDECL',`btagreadergetcontent',`(btagreadergetcontent_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x61AF7447),0x03050500)

/**
 * <description>btagreadergetstring</description>
 */
typedef struct tagbtagreadergetstring_struct
{
	RTS_IEC_HANDLE hReader;				/* VAR_INPUT */	
	RTS_IEC_BYTE **ppBuffer;			/* VAR_INPUT */	
	RTS_IEC_UDINT *pulSize;				/* VAR_INPUT */	
	RTS_IEC_BOOL bAddEndOfString;		/* VAR_INPUT */	
	RTS_IEC_RESULT BTagReaderGetString;	/* VAR_OUTPUT */	
} btagreadergetstring_struct;

DEF_API(`void',`CDECL',`btagreadergetstring',`(btagreadergetstring_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x752DCAA9),0x03050500)

/**
 * <description>btagreadergettagid</description>
 */
typedef struct tagbtagreadergettagid_struct
{
	RTS_IEC_HANDLE hReader;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pulTagId;			/* VAR_INPUT */	
	RTS_IEC_RESULT BTagReaderGetTagId;	/* VAR_OUTPUT */	
} btagreadergettagid_struct;

DEF_API(`void',`CDECL',`btagreadergettagid',`(btagreadergettagid_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x597C68FC),0x03050500)

/**
 * <description>btagreadergettaglen</description>
 */
typedef struct tagbtagreadergettaglen_struct
{
	RTS_IEC_HANDLE hReader;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pulTagLen;			/* VAR_INPUT */	
	RTS_IEC_RESULT BTagReaderGetTagLen;	/* VAR_OUTPUT */	
} btagreadergettaglen_struct;

DEF_API(`void',`CDECL',`btagreadergettaglen',`(btagreadergettaglen_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCE73E40F),0x03050500)

/**
 * <description>btagreaderinit</description>
 */
typedef struct tagbtagreaderinit_struct
{
	RTS_IEC_HANDLE hReader;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pBuffer;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwBufferSize;			/* VAR_INPUT */	
	RTS_IEC_RESULT BTagReaderInit;		/* VAR_OUTPUT */	
} btagreaderinit_struct;

DEF_API(`void',`CDECL',`btagreaderinit',`(btagreaderinit_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x02485C09),0x03050500)

/**
 * <description>btagreaderisdatatag</description>
 */
typedef struct tagbtagreaderisdatatag_struct
{
	RTS_IEC_HANDLE hReader;				/* VAR_INPUT */	
	RTS_IEC_BOOL *pbDataTag;			/* VAR_INPUT */	
	RTS_IEC_RESULT BTagReaderIsDataTag;	/* VAR_OUTPUT */	
} btagreaderisdatatag_struct;

DEF_API(`void',`CDECL',`btagreaderisdatatag',`(btagreaderisdatatag_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0BABA36F),0x03050500)

/**
 * <description>btagreadermovenext</description>
 */
typedef struct tagbtagreadermovenext_struct
{
	RTS_IEC_HANDLE hReader;				/* VAR_INPUT */	
	RTS_IEC_DINT *pnElementType;		/* VAR_INPUT */	
	RTS_IEC_RESULT BTagReaderMoveNext;	/* VAR_OUTPUT */	
} btagreadermovenext_struct;

DEF_API(`void',`CDECL',`btagreadermovenext',`(btagreadermovenext_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4B1EFC23),0x03050500)

/**
 * <description>btagreaderpeeknext</description>
 */
typedef struct tagbtagreaderpeeknext_struct
{
	RTS_IEC_HANDLE hReader;				/* VAR_INPUT */	
	RTS_IEC_DINT BTagReaderPeekNext;	/* VAR_OUTPUT, Enum: BTAGELEMENTTYPE */
} btagreaderpeeknext_struct;

DEF_API(`void',`CDECL',`btagreaderpeeknext',`(btagreaderpeeknext_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x9310CF7A),0x03050500)

/**
 * <description>btagreaderskipcontent</description>
 */
typedef struct tagbtagreaderskipcontent_struct
{
	RTS_IEC_HANDLE hReader;				/* VAR_INPUT */	
	RTS_IEC_RESULT BTagReaderSkipContent;	/* VAR_OUTPUT */	
} btagreaderskipcontent_struct;

DEF_API(`void',`CDECL',`btagreaderskipcontent',`(btagreaderskipcontent_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4BB13EDE),0x03050500)

/**
 * <description>btagswapheader</description>
 */
typedef struct tagbtagswapheader_struct
{
	RTS_IEC_DWORD *pHeaderTag;			/* VAR_INPUT */	/* A pointer to the header tag that has to be swapped correctly */
	RTS_IEC_DINT bSwap;					/* VAR_INPUT */	/* Determines if the header should be swapped (1) or not (0) */
	RTS_IEC_DWORD BTagSwapHeader;		/* VAR_OUTPUT */	
} btagswapheader_struct;

DEF_API(`void',`CDECL',`btagswapheader',`(btagswapheader_struct *p)',1,0x5C8E76D6,0x03050500)

/**
 * <description>btagwriterappendblob</description>
 */
typedef struct tagbtagwriterappendblob_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwDataSize;			/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterAppendBlob;	/* VAR_OUTPUT */	
} btagwriterappendblob_struct;

DEF_API(`void',`CDECL',`btagwriterappendblob',`(btagwriterappendblob_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xDF96F47F),0x03050500)

/**
 * <description>btagwriterappenddummybytes</description>
 */
typedef struct tagbtagwriterappenddummybytes_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_BYTE btFill;				/* VAR_INPUT */	
	RTS_IEC_DWORD ulCount;				/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterAppendDummyBytes;	/* VAR_OUTPUT */	
} btagwriterappenddummybytes_struct;

DEF_API(`void',`CDECL',`btagwriterappenddummybytes',`(btagwriterappenddummybytes_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xDDDCB7E7),0x03050500)

/**
 * <description>btagwriterappendfillbytes</description>
 */
typedef struct tagbtagwriterappendfillbytes_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_BYTE btFill;				/* VAR_INPUT */	
	BTagAlignment alignment;			/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterAppendFillBytes;	/* VAR_OUTPUT */	
} btagwriterappendfillbytes_struct;

DEF_API(`void',`CDECL',`btagwriterappendfillbytes',`(btagwriterappendfillbytes_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4EFA2ED1),0x03050500)

/**
 * <description>btagwriterappendraw</description>
 */
typedef struct tagbtagwriterappendraw_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_BYTE **ppData;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwSize;				/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterAppendRaw;	/* VAR_OUTPUT */	
} btagwriterappendraw_struct;

DEF_API(`void',`CDECL',`btagwriterappendraw',`(btagwriterappendraw_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xBB6DE51A),0x03050500)

/**
 * <description>btagwriterappendwstring</description>
 */
typedef struct tagbtagwriterappendwstring_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_WSTRING *wszString;			/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterAppendWString;	/* VAR_OUTPUT */	
} btagwriterappendwstring_struct;

DEF_API(`void',`CDECL',`btagwriterappendwstring',`(btagwriterappendwstring_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF11A95EC),0x03050500)

/**
 * <description>btagwritercreate</description>
 */
typedef struct tagbtagwritercreate_struct
{
	RTS_IEC_BYTE *pBuffer;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwSize;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* optionally for an errorcode */
	RTS_IEC_HANDLE BTagWriterCreate;	/* VAR_OUTPUT */	
} btagwritercreate_struct;

DEF_API(`void',`CDECL',`btagwritercreate',`(btagwritercreate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB9D46425),0x03050500)

/**
 * <description>btagwritercreatedynamic</description>
 */
typedef struct tagbtagwritercreatedynamic_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* optionally for an errorcode */
	RTS_IEC_HANDLE BTagWriterCreateDynamic;	/* VAR_OUTPUT */	
} btagwritercreatedynamic_struct;

DEF_API(`void',`CDECL',`btagwritercreatedynamic',`(btagwritercreatedynamic_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x3E261347),0x03050500)

/**
 * <description>btagwritercreatesavepoint</description>
 */
typedef struct tagbtagwritercreatesavepoint_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwDataSize;			/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* optionally for an errorcode */
	RTS_IEC_HANDLE BTagWriterCreateSavePoint;	/* VAR_OUTPUT */	
} btagwritercreatesavepoint_struct;

DEF_API(`void',`CDECL',`btagwritercreatesavepoint',`(btagwritercreatesavepoint_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA762E901),0x03050500)

/**
 * <description>btagwritercreatesavepointdynamic</description>
 */
typedef struct tagbtagwritercreatesavepointdynamic_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* optionally for an errorcode */
	RTS_IEC_HANDLE BTagWriterCreateSavePointDynamic;	/* VAR_OUTPUT */	
} btagwritercreatesavepointdynamic_struct;

DEF_API(`void',`CDECL',`btagwritercreatesavepointdynamic',`(btagwritercreatesavepointdynamic_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA2C52642),0x03050500)

/**
 * <description>btagwriterdestroy</description>
 */
typedef struct tagbtagwriterdestroy_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterDestroy;	/* VAR_OUTPUT */	
} btagwriterdestroy_struct;

DEF_API(`void',`CDECL',`btagwriterdestroy',`(btagwriterdestroy_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xDF047A85),0x03050500)

/**
 * <description>btagwriterdestroysavepoint</description>
 */
typedef struct tagbtagwriterdestroysavepoint_struct
{
	RTS_IEC_HANDLE hSavePoint;			/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterDestroySavePoint;	/* VAR_OUTPUT */	
} btagwriterdestroysavepoint_struct;

DEF_API(`void',`CDECL',`btagwriterdestroysavepoint',`(btagwriterdestroysavepoint_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x445E5755),0x03050500)

/**
 * <description>btagwriterendtag</description>
 */
typedef struct tagbtagwriterendtag_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiTagId;				/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterEndTag;	/* VAR_OUTPUT */	
} btagwriterendtag_struct;

DEF_API(`void',`CDECL',`btagwriterendtag',`(btagwriterendtag_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x8152E9BA),0x03050500)

/**
 * <description>btagwriterfinish</description>
 */
typedef struct tagbtagwriterfinish_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_BYTE **ppBuffer;			/* VAR_INPUT */	
	RTS_IEC_UDINT *puiSize;				/* VAR_INPUT */	/* number of written bytes */
	RTS_IEC_RESULT BTagWriterFinish;	/* VAR_OUTPUT */	
} btagwriterfinish_struct;

DEF_API(`void',`CDECL',`btagwriterfinish',`(btagwriterfinish_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x8D01C919),0x03050500)

/**
 * <description>btagwriterinit</description>
 */
typedef struct tagbtagwriterinit_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pBuffer;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwBufferSize;			/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterInit;		/* VAR_OUTPUT */	
} btagwriterinit_struct;

DEF_API(`void',`CDECL',`btagwriterinit',`(btagwriterinit_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x3101147D),0x03050500)

/**
 * <description>btagwriterinit2</description>
 */
typedef struct tagbtagwriterinit2_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pBuffer;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwBufferSize;			/* VAR_INPUT */	
	RTS_IEC_DINT bSwap;					/* VAR_INPUT */	/* Clients have TO set THIS flag (1), IF the addressed server has a different BYTE order. 
 Must be always FALSE (0) for server implementations or if the client has the same byte order as the server. */
	RTS_IEC_RESULT BTagWriterInit2;		/* VAR_OUTPUT */	
} btagwriterinit2_struct;

DEF_API(`void',`CDECL',`btagwriterinit2',`(btagwriterinit2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x47EB6D2D),0x03050500)

/**
 * <description>btagwriterrestoresavepoint</description>
 */
typedef struct tagbtagwriterrestoresavepoint_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_HANDLE hSavePoint;			/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterRestoreSavePoint;	/* VAR_OUTPUT */	
} btagwriterrestoresavepoint_struct;

DEF_API(`void',`CDECL',`btagwriterrestoresavepoint',`(btagwriterrestoresavepoint_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCEE4117D),0x03050500)

/**
 * <description>btagwriterstarttag</description>
 */
typedef struct tagbtagwriterstarttag_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiTagId;				/* VAR_INPUT */	
	BTagAlignment alignment;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiMinLengthSize;		/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterStartTag;	/* VAR_OUTPUT */	
} btagwriterstarttag_struct;

DEF_API(`void',`CDECL',`btagwriterstarttag',`(btagwriterstarttag_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA356707B),0x03050500)

/**
 * <description>btagwriterswitchbuffer</description>
 */
typedef struct tagbtagwriterswitchbuffer_struct
{
	RTS_IEC_HANDLE hWriter;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pNewBuffer;			/* VAR_INPUT */	
	RTS_IEC_DWORD dwNewBufferSize;		/* VAR_INPUT */	
	RTS_IEC_BYTE **ppOldBuffer;			/* VAR_INPUT */	
	RTS_IEC_RESULT BTagWriterSwitchBuffer;	/* VAR_OUTPUT */	
} btagwriterswitchbuffer_struct;

DEF_API(`void',`CDECL',`btagwriterswitchbuffer',`(btagwriterswitchbuffer_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x7C1CA317),0x03050500)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

