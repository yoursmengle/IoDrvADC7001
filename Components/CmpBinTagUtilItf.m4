/**
 * <interfacename>CmpBinTagUtil</interfacename>
 * <description> 
 *	<p>Interface for the binary tag utility.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpBinTagUtil')

/**
 * <category>Static defines</category>
 * <description>Maximum tag length that can be expected. Can be used to check, if the response fits into the communication buffer.</description>
 */
#define BTU_MAX_TAG_LEN		12

/**
 * <description>
 *   This struct defines an alignment property. 
 *   The meaning of the members is
 *   "Align to an address for which the following equation holds:
 *   address % sModulus = sRemainder"
 *   Eg.: 
 *   (4,0) aligns to a 4 byte boundary
 *   (4,1) aligns to a 4 byte boundary + 1 (1,5,9,13,...)
 *   (2,0) aligns to an equal address
 *   (2,1) aligns to an odd address
 *   (1,0) aligns to any address
 * </description>
 */    
typedef struct
{
	unsigned short usModulus;
	unsigned short usRemainder;
} BTAG_ALIGNMENT;

static BTAG_ALIGNMENT const align_40 = {4,0};
static BTAG_ALIGNMENT const align_42 = {4,2};

#ifndef BTAG_MAX_NESTED_TAGS
	#define BTAG_MAX_NESTED_TAGS 10
#endif

#ifndef BTAG_MAX_STATIC_FILESTREAM_BUFFER
	#define BTAG_MAX_STATIC_FILESTREAM_BUFFER		(NETSERVER_BUFFERSIZE / (NETSERVER_MAXCHANNELS * 2))
#endif

typedef struct
{
	RTS_UI16 usHeaderTag;
	RTS_UI16 usHeaderLength;
	RTS_UI16 usServiceGroup;
	RTS_UI16 usService;
	RTS_UI32 ulSessionID;
	RTS_UI32 ulServiceLength;
} HEADER_TAG;

typedef struct
{
	RTS_UI16 usHeaderTag;
	RTS_UI16 usHeaderLength;
	RTS_UI16 usServiceGroup;
	RTS_UI16 usService;
	RTS_UI32 ulSessionID;
	RTS_UI32 ulServiceLength;
	RTS_UI16 usCustomerId;
	RTS_UI16 usReserved; /* Must be 0x0000 */
} HEADER_TAG_EXT;


#ifdef RTS_SIXTEENBITBYTES
	#define sizeof_HEADER_TAG_EXT	sizeof(HEADER_TAG_EXT) * 2
#endif


typedef struct _BTAG_WriterTagInfo
{
	RTS_UI32 ulTagId;
	RTS_UI32 ulSizePos; /* Index of the length field */
	RTS_UI32 ulSize; /* Current content size of the tag */
	RTS_UI8 ucSizeLength; /* Will contain values from 1 to 8 */
	RTS_I8 bIsDataTag;
}BTAG_WRITERTAGINFO;

typedef struct _BTAG_ReaderTagInfo
{
	RTS_UI32 ulTagId;
	RTS_UI32 ulSize;		/* Size of the tag */
	RTS_UI32 ulContentPos; /* Index of the tag content*/
}BTAG_READERTAGINFO;


#define BINTAGTYPE_STREAM		1
#define BINTAGTYPE_FILE			2
#define BINTAGTYPE_FILESTREAM	3

typedef void (CDECL *PFUPDATECRC)(RTS_UI8 *pbyData, RTS_UI32 ulDataLen, void *pParameter);

/**
 * <description>
 *   This struct holds the internal state of a writer and should be 
 *   treated as opaque by an application.
 *   Do not alter!
 * </description>
 */
typedef struct
{
	RTS_UI8 *pBuffer;
	RTS_HANDLE hFile;
	RTS_UI32 ulBufferSize;
	RTS_UI32 ulPos;

	BTAG_WRITERTAGINFO tagStack[BTAG_MAX_NESTED_TAGS];

	int nStackPos; /* Points to the index of the current tag. Initially set to -1 (toplevel, no current tag).
	                   Must not exceed BTAG_MAX_NESTED_TAGS-1 */
	
	int iType;
	RTS_UI32 ulEndServicePos;
	int bSwapHeader;
	int	bBufferOverflow;
	PFUPDATECRC pfUpdateCRC;
	void *pParameterUpdateCRC;
}BINTAGWRITER;

typedef struct
{
	RTS_UI32 ulPos;

	BTAG_WRITERTAGINFO tagStack[BTAG_MAX_NESTED_TAGS];
	int nStackPos; /* Points to the index of the current tag. Initially set to -1 (toplevel, no current tag).
	                   Must not exceed BTAG_MAX_NESTED_TAGS-1 */
	int	bBufferOverflow;
}BINTAGSAVEPOINT;

/**
 * <description>
 *   This struct holds the internal state of a reader and should be 
 *   treated as opaque by an application.
 *   Do not alter!
 * </description>
 */
typedef struct
{
	RTS_UI8 *pBuffer;
	RTS_UI32 ulBufferSize;
	RTS_HANDLE hFile;

	RTS_UI32 ulPos;

	BTAG_READERTAGINFO tagStack[BTAG_MAX_NESTED_TAGS];
	int nStackPos; /* Points to the index of the current tag. Initially set to -1 (toplevel, no current tag).
	                   Must not exceed BTAG_MAX_NESTED_TAGS-1 */
	int iType;
	RTS_UI32 ulStartServicePos;
}BINTAGREADER;

typedef struct 
{
	RTS_UI32 ulPos;

	BTAG_READERTAGINFO tagStack[BTAG_MAX_NESTED_TAGS];
	int nStackPos; /* Points to the index of the current tag. Initially set to -1 (toplevel, no current tag).
	                   Must not exceed BTAG_MAX_NESTED_TAGS-1 */
}BINTAGREADERSAVEPOINT;

/* Enumeration of element types */
enum
{
	BTAG_ET_STARTTAG = 0,
	BTAG_ET_ENDTAG = 1,
	BTAG_ET_EOF = 2
};


#ifdef __cplusplus
extern "C" {
#endif
 

/**
 * <description>
 *   Swap the header of a service. 
 * </description>
 * <param name="pHeader" type="INOUT">
 *   Pass in a HEADER_TAG_EXT struct that should be swapped.
 * </param>
 * <param name="bSwap" type="IN">
 *   Determines, if the header should be swapped (1) or not (0).
 * </param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagSwapHeader',`(HEADER_TAG_EXT* pHeader, RTS_I32 bSwap)')


/* --------- The writer interface ---------- */

/**
 * <description>
 *   Initialize a writer. 
 * </description>
 * <param name="pWriter" type="INOUT">
 *   Pass in a BINTAGWRITER struct that will be initialized to a empty writer.
 * </param>
 * <param name="pBuffer" type="IN">
 *   The buffer that the writer will write to. 
 *   The buffer should not be altered until the writer has finished.
 * </param>
 * <param name="ulBufferSize" type="IN">
 *   The size of the buffer. The writer will fail if a write operation would exceed the buffer.
 * </param>
 * <param name="bSwapHeader" type="IN">
 *    Clients have to set this flag, if the addressed server has a different byte order. 
 *    Must be always FALSE for server implementations or if the client has the same byte order as the server. 
 * </param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagWriterInit2',`(BINTAGWRITER *pWriter, RTS_UI8 *pBuffer, RTS_UI32 ulBufferSize, RTS_I32 bSwapHeader)')

/**
 * <description>
 *   Initialize a writer. Can be used by servers or if the client and the server have the same byte order.
 * </description>
 * <param name="pWriter" type="INOUT">
 *   Pass in a BINTAGWRITER struct that will be initialized to a empty writer.
 * </param>
 * <param name="pBuffer" type="IN">
 *   The buffer that the writer will write to. 
 *   The buffer should not be altered until the writer has finished.
 * </param>
 * <param name="ulBufferSize" type="IN">
 *   The size of the buffer. The writer will fail if a write operation would exceed the buffer.
 * </param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagWriterInit',`(BINTAGWRITER *pWriter, RTS_UI8 *pBuffer, RTS_UI32 ulBufferSize)')

/**
 * <description>
 *   Start a new service. Must be called after BTagWriterInit.
 * </description>
 * <param name="pWriter" type="INOUT">
 *   The writer.
 * </param>
 * <param name="ulSessionID" type="IN">
 *   SessionID of the current session
 * </param>
 * <param name="usHeaderTag" type="IN">
 *   HeaderTag to identify the protocol handler.
 * </param>
 * <param name="ulServiceGroup" type="IN">
 *   ulServiceGroup = HIGHWORD: usCustomerId, LOWWORD: usServiceGroup;
 * </param>
 * <param name="usService" type="IN">
 *   Service
 * </param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagWriterStartService',`(BINTAGWRITER *pWriter, RTS_UI32 ulSessionID, RTS_UI16 usHeaderTag, RTS_UI32 ulServiceGroup, RTS_UI16 usService)')

/**
 * <description>
 *   Finishes the service.
 *   It returns the buffer passed in to BTagWriterInit in ppBuffer and the number
 *   of bytes written to the buffer in pulSize;
 * </description>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagWriterFinishService',`(BINTAGWRITER *pWriter, RTS_UI8 **ppBuffer, RTS_UI32 *pulSize)')

/**
 * <description>
 *   Start a new tag. A tag cannot be started within a data tag. Data tags are determined
 *   by the id of the tag: If bit 7 (that is the highest bit of the least significant byte of the tagid)
 *   is set then the tag contains only subtags, otherwise it contains no subtags but only content.
 *   Every call to BTagWriterStartTag must be matched with a call to BTagWriterEndTag.
 *   All subtags of a tag must be closed before the tag itself may be closed.
 * </description>
 * <param name="pWriter" type="INOUT">
 *   The writer must have been initialized with a call to BTagWriterInit.
 * </param>
 * <param name="ulTagId" type="IN">
 *   The id of the tag.
 * </param>
 * <param name="contentAlignment" type="IN">
 *   How the content should be aligned within this tag. If the tag is not a data tag 
 *   then contentAlignment must always be (4,0).
 *   In any case in this version of the data format the nModulus member must always be 4
 *   since all alignment is done in respect to 4 byte boundaries.
 * </param>
 * <param name="ulMinLengthSize" type="IN">
 *   
 * </param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagWriterStartTag',`(BINTAGWRITER *pWriter, RTS_UI32 ulTagId, BTAG_ALIGNMENT contentAlignment, RTS_UI32 ulMinLengthSize)')

/**
 * <description>
 *   Append a C-string to the current tag. The string is written including
 *   the trailing end of string char (NUL). The current tag must be a data tag.
 * </description>
 * <param name="pWriter" type="IN">Pointer to bintag writer</param>
 * <param name="pszString" type="IN">Pointer to NUL terminated string to append</param>
 * <result>TRUE=succeeded, FALSE=failed</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagWriterAppendString',`(BINTAGWRITER *pWriter, const char *pszString)')

/**
 * <description>
 *   Append a UTF-16 (widechar) string to the current tag. The string is written including
 *   the trailing end of string char (0x0000). The current tag must be a data tag.
 * </description>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagWriterAppendWString',`(BINTAGWRITER *pWriter, const RTS_WCHAR *wszString)')

/**
 * <description>
 *   Append ulSize bytes from the buffer pBlob to the current tag. 
 *   The current tag must be a data tag.
 * </description>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagWriterAppendBlob',`(BINTAGWRITER *pWriter, const RTS_UI8 *pBlob, RTS_UI32 ulSize)')

/**
 * <description>
 *  Returns a pointer to the current content position and forwards the write position for ulSize bytes.
 *   This function provides a buffer of length ulSize within the content of the current tag, in effect giving
 *   the caller random access to this buffer.
 *   This function is especially usefull, if that buffer has to be passed to another function, that fills it.
 *   (see example).
 *   ATTENTION: The returned pointer is valid only until the next operation on the bintagwriter is executed.
 *   After that the pointer must not be used any more! Do not store that pointer permanently.
 *   The current tag must be a data tag.
 * </description>
 * <param name="ppBuffer" type="OUT">Is set to point to the buffer, if the function succeeds</param>
 * <pre>
 *   // Store a number as hexadecimal string in a bintag writer
 *   unsigned char *pBuffer;
 *   unsigned char **ppBuffer;
 *   int nNumber = 1234;
 *	 *ppBuffer = pBuffer;
 *   if (ERR_OK == CAL_BTagWriterAppendRaw(pWriter, ppBuffer, 5)) // 4 digits + an additional byte for a trailing zero
 *     sprintf(pBuffer, "%04x", nNumber);
 *   pBuffer = NULL; // Avoid accidentally writing on that buffer again
 * </pre>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagWriterAppendRaw',`(BINTAGWRITER *pWriter, RTS_UI8 **ppBuffer, RTS_UI32 ulSize)')

/**
 * <description>
 *   Add byFillByte to the content until the current content ends 
 *   on a position that satifies the desired alignment.
 *   Eg. a tag must always be closed on a (4,0)-alignment, so after adding a variable length
 *   string one should call:
 *   <pre>
 *     BTAG_ALIGNMENT align = {4,0};
 *     ...
 *     BTagWriterAppendFillBytes(pWriter, 0, align);
 *     BTagWriterEndTag(pWriter, TAG_ID);
 *   </pre>
 *   If the alignment property is already fullfilled nothing will be appended.
 * </description>
 * <param name="pWriter" type="IN"></param>
 * <param name="byFillByte" type="IN">
 *   The byte to be appended until alignment is achieved.
 * </param>
 * <param name="alignment" type="IN">
 *   The desired alignment of the next writer position.
 * </param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagWriterAppendFillBytes',`(BINTAGWRITER *pWriter, RTS_UI8 byFillByte, BTAG_ALIGNMENT alignment)')

/**
 * <description>
 *   Append byFillByte ulSize times.
 * </description>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagWriterAppendDummyBytes',`(BINTAGWRITER *pWriter, RTS_UI8 byFillByte, RTS_UI32 ulSize)')

/**
 * <description>
 *   Close the current tag. The current tag must have been started with the given tag id.
 *   ulTagId is used only as an additional check that all tags are closed in the right order.
 *   Since the only element that follows a tag must be a tag again and a tag must always start
 *   on a 4 byte boundary the complete size of a tag (header + content) must be dividable by 4.
 *   Taking a contentalignment of (4,x) then "contentsize == 4 - x (MOD 4) " must hold.
 *   (eg. for (4,1): contentsize % 4 == 3)
 *   If this condition does not hold, the function will fail.
 * </description>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagWriterEndTag',`(BINTAGWRITER *pWriter, RTS_UI32 ulTagId)')

/**
 * <description>
 *   Replaces the current writer buffer with a new one. All content in the current buffer
 *   is copied to the new buffer. This also means that the size of the new buffer has to be
 *   at least the current position of the writer. 
 *   The purpose of this function is to allow for extension of the buffer if an operation
 *   returned a buffer overflow. Then the caller may allocate a new buffer, call 
 *   BTagWriterSwitchBuffer and retry the failed operation.
 * </description>
 * <param name="pWriter" type="IN"></param>
 * <param name="pNewBuffer" type="IN">
 *   The buffer that is to replace the original buffer.
 * </param>
 * <param name="ulNewSize" type="IN">
 *   Size of the new buffer. Must be greater or at least equal to the current postion
 *   of the writer.
 * </param>
 * <param name="ppOldBuffer" type="OUT">
 *   Is set to the previous buffer.
 * </param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagWriterSwitchBuffer',`(BINTAGWRITER *pWriter, RTS_UI8 *pNewBuffer, RTS_UI32 ulNewSize, RTS_UI8 **ppOldBuffer)')

/**
 * <description>
 *   Save the current state of the writer. A later call to BTagWriterRestoreSavepoint will
 *   reset the writer and its buffer to that state. Any number of savepoints may be created.
 *   The caller must use multiple savepoints in a stack-like fashion: If savepoints are
 *   created in the order 1,2,3,4 then they must be restored in opposite order only. Not 
 *   every savepoint must be restored - but if one is restored all savepoints created after
 *   that one MUST NOT BE USED any more.
 *   Examples: ("sX"="create savepoint X", "rX"="Restore savepoint X", 
 *			    "(x,y,z)"="stack of valid savepoints")
 *   The following sequences are valid:
 *   () s1 (1) s2 (1,2) s3 (1,2,3) r2 (1) r1 ()
 *   () s1 (1) s2 (1,2) s3 (1,2,3) r2 (1) s4 (1,4) r4 (1)  
 *   whereas this one is invalid:
 *   () s1 (1) s2 (1,2) s3 (1,2,3) r2 (1) r3 [3 is not valid at this point]
 * 
 *   The writer does not track the stack of savepoints, therefore it cannot
 *   detect errors in the restore order. It's the responsibility of the application
 *   to ensure the correct restore order. Failure in doing so will lead to an 
 *   inconsistent state and may well corrupt the whole document.
 *   Besides the restore order savepoints are independent of each other. The application
 *   may delete/reuse a savepoint anytime it doesn't need it anymore.
 * 
 *   Savepoints cannot be used to transfer the state of a writer to a second writer.
 *   Any attempt in doing so will lead to undefined behaviour.
 * </description>
 * <param name="pWriter" type="IN"></param>
 * <param name="pSavePoint" type="OUT">
 *   Will receive all information needed to restore the current state of the writer.
 * </param>
 */ 
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagWriterCreateSavepoint',`(BINTAGWRITER *pWriter, BINTAGSAVEPOINT *pSavepoint)')

/**
 * <description>
 *   Restore the state of the writer to one previously saved using 
 *   BTagWriterCreateSavepoint. See there for a detailed description on how to use
 *   these functions.
 * </description>
 * <param name="pWriter" type="IN">
 *   Must be the same writer that the savepoint was created on.
 * </param>
 * <param name="pSavepoint" type="IN">
 *   A previously created savepoint.
 * </param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagWriterRestoreSavepoint',`(BINTAGWRITER *pWriter, BINTAGSAVEPOINT *pSavepoint)')

/**
 * <description>
 *   Reads the available bytes in writer buffer that can be used for data.
 * </description>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`BTagWriterGetAvailableBuffer',`(BINTAGWRITER *pWriter)')

/**
 * <description>
 *   Finishes the writer. If not all tags have been closed properly this function will fail.
 *   Otherwise it returns the buffer passed in to BTagWriterInit in ppBuffer and the number
 *   of bytes written to the buffer in pulSize;
 * </description>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagWriterFinish',`(BINTAGWRITER *pWriter, RTS_UI8 **ppBuffer, RTS_UI32 *pulSize)')

/**
 * <description>Write a single tag</description>
 * <param name="pWriter" type="IN">Pointer to the writer stream</param>
 * <param name="ulTag" type="IN">Tag to write</param>
 * <param name="align" type="IN">Alignment of the tag</param>
 * <param name="pContent" type="IN">Pointer to the tag data</param>
 * <param name="ulSize" type="IN">Size in bytes of the tag data</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagWriteSingleTag',`(BINTAGWRITER *pWriter, RTS_UI32 ulTag, BTAG_ALIGNMENT align, RTS_I32 bFillBytes, void *pContent, RTS_UI32 ulSize)')

/**
 * <description>Write a single tag with more than one content</description>
 * <param name="pWriter" type="IN">Pointer to the writer stream</param>
 * <param name="ulTag" type="IN">Tag to write</param>
 * <param name="align" type="IN">Alignment of the tag</param>
 * <param name="pContent" type="IN">Pointer to the tag data</param>
 * <param name="ulSize" type="IN">Size in bytes of the tag data</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagWriteSingleTag2',`(BINTAGWRITER *pWriter, RTS_UI32 ulTag, BTAG_ALIGNMENT align, void **ppContentList, RTS_UI32 *paulSize)')

/* --------- The reader interface ---------- */
/**
 * <description>
 *   Initialize a reader.
 * </description>
 * <param name="pReader" type="INOUT">
 *   Pass in a BINTAGREADER structure that will be initialized to an empty reader.
 * </param>
 * <param name="pBuffer" type="IN">
 *   The buffer that contains the bintag structure to be read. Do not alter the buffer
 *   until the reader isn't used any more.
 * </param>
 * <param name="ulBufferSize" type="IN">
 *   The size of pBuffer. It is expected that the whole buffer is in the bintag structure,
 *   possibly containing multiple toplevel tags. 
 * </param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagReaderInit',`(BINTAGREADER *pReader, RTS_UI8 *pBuffer, RTS_UI32 ulBufferSize)')

/**
 * <description>
 *   Peek at the type of the next element as it would be returned by a call to BTagReaderMoveNext,
 *   but do not actually move to it (ie. the readers state will not be changed).
 * </description>
 * <param name="pReader" type="IN">
 *   An active reader.
 * </param>
 * <param name="pnElementType" type="OUT">
 *   Will be set to the type of the current element:
 *   <ul>
 *     <li>BTAG_ET_STARTTAG: Reader entered a new tag.</li>
 *     <li>BTAG_ET_ENDTAG: End of the current tag reached. New active tag is the surrounding tag</li>
 *     <li>BTAG_ET_EOF: End of the buffer reached. No more content/tags can be read</li>
 *   </ul>
 * </param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagReaderPeekNext',`(BINTAGREADER *pReader)')

/**
 * <description>
 *   Let the reader move on to the next element.
 * </description>
 * <param name="pReader" type="IN">
 *   An active reader.
 * </param>
 * <param name="pnElementType" type="OUT">
 *   Will be set to the type of the current element:
 *   <ul>
 *     <li>BTAG_ET_STARTTAG: Reader entered a new tag.</li>
 *     <li>BTAG_ET_ENDTAG: End of the current tag reached. New active tag is the surrounding tag</li>
 *     <li>BTAG_ET_EOF: End of the buffer reached. No more content/tags can be read</li>
 *   </ul>
 * </param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagReaderMoveNext',`(BINTAGREADER *pReader, RTS_I32 *pnElementType)')

/** 
 * <description>
 *   Jump to the end of the current tag. The next element that will be read by BTagReaderMoveNext
 *   will be the ENDTAG of the current tag.
 * </description>
 * <param name="pReader">
 * </param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagReaderSkipContent',`(BINTAGREADER *pReader)')

/**
 * <description>
 *   Get the id of the current tag. Will fail if the reader is positioned at the toplevel.
 * </description>
 * <param name="pulTagId" type="OUT">
 *   Will be set to the id of the current tag.
 * </param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagReaderGetTagId',`(BINTAGREADER *pReader, RTS_UI32 *pulTagId)')

/**
 * <description>
 *   Get the tag length of the current tag. Will fail if the reader is positioned at the toplevel.
 * </description>
 * <param name="pulTagLen" type="OUT">
 *   Will be set to the length of the current tag.
 * </param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagReaderGetTagLen',`(BINTAGREADER *pReader, RTS_UI32 *pulTagLen)')

/**
 * <description>
 *   Check if the current tag is a data tag (ie. contains raw content) or does contain
 *   subtags. Will return an error if the reader is not positioned on a tag (ie. is at the 
 *   toplevel). However, in that case pbIsData will be set to FALSE.
 * </description>
 * <param name="pReader" type="IN">
 * </param>
 * <param name="pbIsDataTag" type="IN">
 *   Is set to TRUE, if the current tag is a data tag, FALSE otherwise.
 * </param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagReaderIsDataTag',`(BINTAGREADER *pReader, RTS_I32 *pbIsDataTag)')

/**
 * <description>
 *   Get a pointer on the content of the current tag. 
 * </description>
 * <param name="pReader" type="IN">
 * </param>
 * <param name="ppBuffer" type="OUT">
 *   Will be set to point at the content of the current tag.
 * </param>
 * <param name="pulSize" type="OUT">
 *   Will contain the size of the content.
 * </param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagReaderGetComplexContent',`(BINTAGREADER *pReader, RTS_UI8 **ppBuffer, RTS_UI32 *pulSize)')

/**
 * <description>
 *   Get a pointer on the content of the current tag. 
 *   Will fail if the reader is on the toplevel
 *   (no current tag) or the current tag is not a data tag.
 * </description>
 * <param name="pReader" type="IN">
 * </param>
 * <param name="ppBuffer" type="OUT">
 *   Will be set to point at the content of the current tag.
 * </param>
 * <param name="pulSize" type="OUT">
 *   Will contain the size of the content.
 * </param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagReaderGetContent',`(BINTAGREADER *pReader, RTS_UI8 **ppBuffer, RTS_UI32 *pulSize)')

/**
 * <description>
 *   Like BTagReaderGetContent but treats the content as a string. If a '\0' is found
 *   before the end of the tag, pulSize is set to the length up to (and including) the zero.
 *   If bAddEndOfString is set, then '\0' is written at the last byte, if '\0' is not found. 
 * </description>
 * <note>
 *   If the length of the tag is 0 then no '\0' can be written into the buffer without overwriting
 *   other content. In that case a reference to a static empty string is returned. 
 * </note>
 * <param name="pReader" type="IN">
 * </param>
 * <param name="ppString" type="OUT">
 *   Will be set to the start of the string. Will not necessarily point into the readers buffer.
 *   (see note).
 * </param>
 * <param name="pulSize" type="IN">
 *   The length of the string INCLUDING the trailing '\0',
 *   ie. "strlen(ppString)+1".
 * </param>
 * <param name="bAddEndOfString" type="IN">
 *   Force a trailing zero byte to be added, if it doesn't exist within the bounds of the tag.
 *   Will overwrite the last char of the string.
 *   Note: This option will alter the content of the buffer!
 * </param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagReaderGetString',`(BINTAGREADER *pReader, char **ppString, RTS_UI32 *pulSize, RTS_I32 bAddEndOfString)')

/**
 * <description>
 *   Save the current state of the reader. A later call to BTagReaderRestoreSavepoint will
 *   reset the reader and its buffer to that state. Any number of savepoints may be created.
 *   The caller must use multiple savepoints in a stack-like fashion: If savepoints are
 *   created in the order 1,2,3,4 then they must be restored in opposite order only. Not 
 *   every savepoint must be restored - but if one is restored all savepoints created after
 *   that one MUST NOT BE USED any more.
 *   Examples: ("sX"="create savepoint X", "rX"="Restore savepoint X", 
 *			    "(x,y,z)"="stack of valid savepoints")
 *   The following sequences are valid:
 *   () s1 (1) s2 (1,2) s3 (1,2,3) r2 (1) r1 ()
 *   () s1 (1) s2 (1,2) s3 (1,2,3) r2 (1) s4 (1,4) r4 (1)  
 *   whereas this one is invalid:
 *   () s1 (1) s2 (1,2) s3 (1,2,3) r2 (1) r3 [3 is not valid at this point]
 * 
 *   The reader does not track the stack of savepoints, therefore it cannot
 *   detect errors in the restore order. It's the responsibility of the application
 *   to ensure the correct restore order. Failure in doing so will lead to an 
 *   inconsistent state and may well corrupt the whole document.
 *   Besides the restore order savepoints are independent of each other. The application
 *   may delete/reuse a savepoint anytime it doesn't need it anymore.
 * 
 *   Savepoints cannot be used to transfer the state of a reader to a second reader.
 *   Any attempt in doing so will lead to undefined behaviour.
 * </description>
 * <param name="pReader" type="IN"></param>
 * <param name="pSavePoint" type="OUT">
 *   Will receive all information needed to restore the current state of the reader.
 * </param>
 */ 
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagReaderCreateSavepoint',`(BINTAGREADER *pReader, BINTAGREADERSAVEPOINT *pSavepoint)')

/**
 * <description>
 *   Restore the state of the reader to one previously saved using 
 *   BTagReaderCreateSavepoint. See there for a detailed description on how to use
 *   these functions.
 * </description>
 * <param name="pReader" type="IN">
 *   Must be the same reader that the savepoint was created on.
 * </param>
 * <param name="pSavepoint" type="IN">
 *   A previously created savepoint.
 * </param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagReaderRestoreSavepoint',`(BINTAGREADER *pReader, BINTAGREADERSAVEPOINT *pSavepoint)')

DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagWriterFileInit',`(BINTAGWRITER *pWriter, RTS_HANDLE hFile)')
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagWriterFileInit2',`(BINTAGWRITER *pWriter, char *pszFileName)')
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagWriterFileStreamInit',`(BINTAGWRITER *pWriter, RTS_HANDLE hFile)')
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagWriterFileStreamInit2',`(BINTAGWRITER *pWriter, RTS_HANDLE hFile, PFUPDATECRC pfUpdateCRC, void *pParameterUpdateCRC)')
DEF_ITF_API(`RTS_RESULT',`CDECL',`BTagReaderFileInit',`(BINTAGREADER *pReader, RTS_UI8 *pBuffer, RTS_UI32 ulBufferSize, RTS_HANDLE hFile)')

/**
 * <description>Get the first tag out of a stream</description>
 * <param name="pReader" type="IN">Pointer to the reader stream</param>
 * <param name="pulToplevelTag" type="OUT">Returns the toplevel tag. -1, if no complex tag</param>
 * <param name="pulTag" type="OUT">Returns the tag</param>
 * <param name="pulSize" type="OUT">Size of the tag</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the content</result>
 */
DEF_ITF_API(`void*',`CDECL',`BTagReaderGetFirstTag',`(BINTAGREADER *pReader, RTS_UI32 *pulToplevelTag, RTS_UI32 *pulTag, RTS_UI32 *pulSize, RTS_RESULT *pResult)')

/**
 * <description>Get the first tag out of a stream</description>
 * <param name="pReader" type="IN">Pointer to the reader stream</param>
 * <param name="pulToplevelTag" type="OUT">Returns the toplevel tag. -1, if no complex tag</param>
 * <param name="pulTag" type="OUT">Returns the tag</param>
 * <param name="pulSize" type="OUT">Size of the tag</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to the content</result>
 */
DEF_ITF_API(`void*',`CDECL',`BTagReaderGetNextTag',`(BINTAGREADER *pReader, RTS_UI32 *pulToplevelTag, RTS_UI32 *pulTag, RTS_UI32 *pulSize, RTS_RESULT *pResult)')

#ifdef __cplusplus
}
#endif

