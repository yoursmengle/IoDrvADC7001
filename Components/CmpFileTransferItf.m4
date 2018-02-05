/**
 * <interfacename>CmpFileTransfer</interfacename>
 * <description> 
 *	This interface is specified for the file transfer component, to enable the transmission of files
 *	from and to the runtime system, to browse the directories online on the target and to handle 
 *	directories (create, delete, rename).
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpFileTransfer')

#include "CmpItf.h"

/**
 * <category>Alloc types</category>
 * <description>Alloc types for the file name</description>
 */
#define FILENAME_STATIC		0
#define FILENAME_DYNAMIC	1

/**
 * <category>Transfer types</category>
 * <description>Type of file transfer</description>
 */
#define FT_UPLOAD			0
#define FT_DOWNLOAD			1

/**
 * <category>Transfer types</category>
 * <description>Type of file transfer notification</description>
 */
#define FT_SYNC_FILE_BEGIN_APP			0x01
#define FT_SYNC_FILE_END_APP			0x02
#define FT_SYNC_FILE_BEING_DEVICE		0x03
#define FT_SYNC_FILE_END_DEVICE			0x04
#define FT_FILE_BEGIN_LOGIN_APP			0x05
#define FT_FILE_END_LOGIN_APP			0x06
#define FT_FILE_BEGIN_OEM				0x07
#define FT_FILE_END_OEM					0x08

/**
 * <category>Static defines</category>
 * <description>Number of static transfers possible</description>
 */
#ifndef FT_NUM_OF_STATIC_TANSFERS
	#define FT_NUM_OF_STATIC_TANSFERS	4
#endif

/**
 * <category>Static defines</category>
 * <description>Extension for files during download sequence. This extension is removed at the end of the successful transfer or renamed into
 *	FT_BACKUP_FILE_EXTENSION, if origin file is occupied with a parallel running file transfer.
 *	NOTE:
 *	If this extension is defined empty "", no rename of the transferred file is done. FT_BACKUP_FILE_EXTENSION must be defined empty too!
 * </description>
 */
#ifndef FT_TEMP_FILE_EXTENSION
	#define FT_TEMP_FILE_EXTENSION		".tmp"
#endif

/**
 * <category>Static defines</category>
 * <description>Extension for files after successful file download. The extension is removed, if the still running file transfer on the source file ends.
 *	NOTE:
 *	If this extension is defined empty "", no rename of the transferred file is done. FT_TEMP_FILE_EXTENSION must be defined empty too!
 * </description>
 */
#ifndef FT_BACKUP_FILE_EXTENSION
	#define FT_BACKUP_FILE_EXTENSION	".bak"
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Handle all file transfer services asynchronously.
 * </description>
 */
#define FTKEY_INT_ASYNC_SERVICES					"AsyncServices"
#ifndef FTVALUE_INT_ASYNC_SERVICES_DEFAULT
	#define FTVALUE_INT_ASYNC_SERVICES_DEFAULT		0
#endif


typedef struct
{
	RTS_UI32 ulCRC32;
	RTS_UI32 ulSize;
} FileInfo;

typedef struct
{
	int iAllocType;
	RTS_SIZE iMaxLen;
	char *pszName;
	char sz[64];
} FileName;

typedef struct
{
	RTS_HANDLE hFile;
	RTS_SIZE ulTransferred;
	RTS_UI32 ulSessionId;
	RTS_UI32 ulOnlineCRC32;
	FileInfo fi;
	FileName fn;
	int iTransferType;
} FileTransfer;

/**
 * <category>Operations</category>
 * <description>Operations of the file transfer component. Can be disabled with the event CMPID_CmpMgr::EVT_CmpMgr_DisableOperation!</description>
 */
#define OP_FILE_TRANSFER_DOWNLOAD				1
#define OP_FILE_TRANSFER_UPLOAD					2
#define OP_FILE_TRANSFER_DELETE_FILE			3
#define OP_FILE_TRANSFER_RENAME_FILE			4
#define OP_FILE_TRANSFER_CREATE_DIRECTORY		5
#define OP_FILE_TRANSFER_DELETE_DIRECTORY		6
#define OP_FILE_TRANSFER_RENAME_DIRECTORY		7

/**
 * <category>Event parameter</category>
 * <element name="pszFileName" type="IN">File name that is transferred</element>
 * <element name="pInfo" type="IN">Pointer to actual file info</element>
 * <element name="usType" type="IN">File transfer type. See category "Transfer types" for details.</element>
 * <element name="bBegin" type="IN">bBegin=1: Begin of the file transfer, bBegin=0: End of the file transfer</element>
 * <element name="pszPlaceHolderFileName" type="IN">File name including any place holder path. Optional, may be NULL.</element>
 */
typedef struct
{
	char *pszFileName;
	FileInfo *pInfo;
	unsigned short usType;
	char bBegin;
	char *pszPlaceHolderFileName;
} EVTPARAM_CmpFileTransfer;
#define EVTPARAMID_CmpFileTransfer		0x0001
#define EVTVERSION_CmpFileTransfer		0x0002


/**
 * <category>Events</category>
 * <description>Event is sent at each begin and end of a filetransfer</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpFileTransfer</param>
 */
#define EVT_FileTransfer				MAKE_EVENTID(EVTCLASS_INFO, 1)



/**
 * <category>Event parameter</category>
 * <element name="pszApplicationName" type="IN">Application name for which the files are being transferred.</element>
 * <element name="usType" type="IN">Synchronized file transfer type. See category "Transfer types" for details.</element>
 */
typedef struct
{
	char *pszApplicationName;
	RTS_UI16 usType;
} EVTPARAM_CmpSyncFileTransfer;
#define EVTPARAMID_CmpSyncFileTransfer		0x0002
#define EVTVERSION_CmpSyncFileTransfer		0x0001

/**
 * <category>Events</category>
 * <description>
 * This event is sent before and after synchronized files are downloaded. 
 * Typically this occurs after an application download or online change.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpSyncFileTransfer</param>
 */
#define EVT_SyncFileTransfer				MAKE_EVENTID(EVTCLASS_INFO, 2)



/**
 * <category>Online services</category>
 * <description>
 *	Online services for the file transfer
 * </description>
 */
#define SRVFT_GET_FILEINFO			0x01	
#define SRVFT_START_DOWNLOAD		0x02
#define SRVFT_RESTART_DOWNLOAD		0x03
#define SRVFT_DOWNLOAD				0x04
#define SRVFT_START_UPLOAD			0x05
#define SRVFT_RESTART_UPLOAD		0x06
#define SRVFT_UPLOAD				0x07
#define SRVFT_END					0x08
#define SRVFT_CANCEL				0x09
#define SRVFT_SAFE_SIGNATURE		0x0A
#define SRVFT_GET_SAFED_SIGNATURE	0x0B
#define SRVFT_GET_DIRECTORYINFO		0x0C
#define SRVFT_GET_DIRECTORYINFO_CANCEL	0x0D
#define SRVFT_DELETE_FILE			0x0E
#define SRVFT_RENAME_FILE			0x0F
#define SRVFT_CREATE_DIRECTORY		0x10
#define SRVFT_DELETE_DIRECTORY		0x11
#define SRVFT_RENAME_DIRECTORY		0x12
#define SRVFT_GET_FREE_DISK_SPACE	0x13	/* Not implemented, only sent by CDS >= V3.5.1.0 and < V3.5.1.30 */
#define SRVFT_SYNC_FILE_TRANSFER	0x14

#define FTT_DOWNLOAD				1
#define FTT_UPLOAD					2

/**
 * <category>Online reply tags</category>
 * <description>
 * </description>
 */
#define TAG_REPLY_FILEINFO			0x81
#define TAG_FILENAME				0x01
#define TAG_FILEINFO				0x02
#define TAG_SESSIONID				0x03

#define TAG_STARTINFO				0x04
#define TAG_REPLY_STARTINFO			0x84
#define TAG_DATA					0x05
#define TAG_REPLY_DATAACK			0x05
#define TAG_DATASIZE				0x06
#define TAG_REPLY_DATASIZE			0x06
#define TAG_END						0x07
#define TAG_REPLY_ENDACK			0x07
#define TAG_REPLY_ERROR				0x08
#define TAG_REPLY_GET_SAFED_SIGNATURE	0x09
#define TAG_REPLY_GET_FILENAME		0x0A

#define TAG_DIRECTORY_NAME			0x0B
#define TAG_DIRECTORY_HANDLE		0x0C
#define TAG_REPLY_DIRECTORY_INFO	0x8D
#define TAG_ENTRY_NAME				0x0E
#define TAG_DIRECTORY_INFO			0x0F
#define TAG_FILETRANSFER_TYPE		0x10
#define TAG_DIRECTORY_EXTRAINFO		0x11
#define TAG_REPLY_DIRECTORY_HANDLE	0x1F
#define TAG_DIR_ENTRY               0x90

/**
 * <category>Directory extra info flags</category>
 * <description>
 * Bits for the bitvector submitted via TAG_DIRECTORY_EXTRAINFO.
 * All other bits are reserved and may be used for future extensions.
 * </description>
 * <element name="TDEI_PLACEHOLDER" type="IN">Entry is a placeholder</element>
 * <element name="TDEI_REDUNDANT" type="IN">Entry is redundant, i.e. links to a subdirectory in the default path</element>
 */
#define TDEI_PLACEHOLDER			0x00000001
#define TDEI_REDUNDANT				0x00000002

/**
 * <category>Static defines</category>
 * <description>Predefined objects in the runtime</description>
 */
#define USERDB_OBJECT_ROOTDIRECTORY	"/"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Creates a file transfer download object to transfer a file from client to target</description>
 * <param name="pszFileName" type="IN">File name (can have a file path)</param>
 * <param name="pInfo" type="IN">File info of the file to be transmitted from the client</param>
 * <param name="ulSessionId" type="IN">SessionId (can be the channelid) of the transfer</param>
 * <param name="bRestart" type="IN">1: the file transfer will be continued, 0: start of the file transfer from the beginning</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the file transfer object</result>
 */
DEF_STATICITF_API(`RTS_HANDLE', `CDECL', `FileTransferStartDownload', `(char *pszFileName, FileInfo *pInfo, RTS_UI32 ulSessionId, int bRestart, RTS_RESULT *pResult)')

/**
 * <description>Transfer file data to the target</description>
 * <param name="hFiletransfer" type="IN">Handle to the file transfer object</param>
 * <param name="pbyData" type="IN">Data to transfer into the file</param>
 * <param name="ulLen" type="IN">Number of bytes to transfer</param>
 * <result>error code</result>
 */
DEF_STATICITF_API(`RTS_RESULT', `CDECL', `FileTransferDownload', `(RTS_HANDLE hFiletransfer, unsigned char *pbyData, RTS_SIZE ulLen)')

/**
 * <description>Finish file transfer download</description>
 * <param name="hFiletransfer" type="IN">Handle to the file transfer object</param>
 * <result>error code</result>
 */
DEF_STATICITF_API(`RTS_RESULT', `CDECL', `FileTransferEndDownload', `(RTS_HANDLE hFiletransfer)')

/**
 * <description>Creates a file transfer upload object to transfer a file from target to client</description>
 * <param name="pszFileName" type="IN">File name (can have a file path)</param>
 * <param name="pInfo" type="IN">File info of the file to be transmitted to the client</param>
 * <param name="ulSessionId" type="IN">SessionId (can be the channelid) of the transfer</param>
 * <param name="bRestart" type="IN">1: the file transfer will be continued, 0: start of the file transfer from the beginning</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the file transfer object</result>
 */
DEF_STATICITF_API(`RTS_HANDLE', `CDECL', `FileTransferStartUpload', `(char *pszFileName, FileInfo *pInfo, RTS_UI32 ulSessionId, int bRestart, RTS_RESULT *pResult)')

/**
 * <description>Transfer file data to the client</description>
 * <param name="hFiletransfer" type="IN">Handle to the file transfer object</param>
 * <param name="pbyData" type="IN">Data to transfer from the file</param>
 * <param name="pulMaxLen" type="INOUT">Number of bytes to transfer, returns the real number of transferred bytes</param>
 * <result>error code</result>
 */
DEF_STATICITF_API(`RTS_RESULT', `CDECL', `FileTransferUpload', `(RTS_HANDLE hFiletransfer, unsigned char *pbyData, RTS_SIZE *pulMaxLen)')

/**
 * <description>Finish file transfer upload</description>
 * <param name="hFiletransfer" type="IN">Handle to the file transfer object</param>
 * <param name="pFileInfo" type="OUT">Returns the file info of the uploaded file. Can be used to check the consistence on the upload side.</param>
 * <result>error code</result>
 */
DEF_STATICITF_API(`RTS_RESULT', `CDECL', `FileTransferEndUpload', `(RTS_HANDLE hFiletransfer, FileInfo *pFileInfo)')

/**
 * <description>Close a file transfer</description>
 * <param name="hFiletransfer" type="IN">Handle to the file transfer object</param>
 * <result>error code</result>
 */
DEF_STATICITF_API(`RTS_RESULT', `CDECL', `FileTransferClose', `(RTS_HANDLE hFiletransfer)')

/**
 * <description>Cancel and abort a file transfer</description>
 * <param name="hFiletransfer" type="IN">Handle to the file transfer object</param>
 * <result>error code</result>
 */
DEF_STATICITF_API(`RTS_RESULT', `CDECL', `FileTransferCancel', `(RTS_HANDLE hFiletransfer)')

/**
 * <description>Cancel and abort all file transfers on the specified sessionid (channelid)</description>
 * <param name="hFiletransfer" type="IN">Handle to the file transfer object</param>
 * <result>error code</result>
 */
DEF_STATICITF_API(`RTS_RESULT', `CDECL', `FileTransferCancelAll', `(RTS_UI32 ulSessionId)')

/**
 * <description>Get file infos from target and client</description>
 * <param name="pszFileName" type="IN">File name (can have a file path)</param>
 * <param name="pInfo" type="OUT">File info of the file in the target</param>
 * <param name="pInfoClient" type="IN">File info of the file at the client</param>
 * <result>error code</result>
 */
DEF_STATICITF_API(`RTS_RESULT', `CDECL', `FileTransferGetInfo', `(char *pszFileName, FileInfo *pInfo, FileInfo *pInfoClient)')

/**
 * <description>Get number of bytes to transmit</description>
 * <param name="hFiletransfer" type="IN">Handle to the file transfer object</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of bytes to transmit</result>
 */
DEF_STATICITF_API(`RTS_SIZE', `CDECL', `FileTransferToTransmit', `(RTS_HANDLE hFiletransfer, RTS_RESULT *pResult)')

/**
 * <description>Safe signature of a specified file to check consistency</description>
 * <param name="pszFileName" type="IN">File name (can have a file path)</param>
 * <param name="ulCRC32" type="IN">CRC32 of the file</param>
 * <result>error code</result>
 */
DEF_STATICITF_API(`RTS_RESULT', `CDECL', `FileTransferSafeSignature', `(char *pszFileName, RTS_UI32 ulCRC32)')

/**
 * <description>Get safed signature of a specified file to check consistency</description>
 * <param name="pszFileName" type="IN">File name (can have a file path)</param>
 * <param name="pulCRC32" type="OUT">Pointer to get CRC32 of the file</param>
 * <result>error code</result>
 */
DEF_STATICITF_API(`RTS_RESULT', `CDECL', `FileTransferGetSafedSignature', `(char *pszFileName, RTS_UI32 *pulCRC32)')

#ifdef __cplusplus
}
#endif
