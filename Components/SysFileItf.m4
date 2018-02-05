/**
 * <interfacename>SysFile</interfacename>
 * <description> 
 *	<p>The SysFile interface is projected to get access to the files of a filesystem.
 *	The filesystem can be on harddisk, a flash/flash disk, a RAM disk or what ever. The only
 *	requirement is, that the filesystem is non volatile!</p>
 *  <p>Please read following notes if using the SysFileFlash with our SysFlash:
 *	This component needs a global
 *	define of the file table FILE_MAP. It has to be declared in sysdefines.h. Here is an example
 *	with the neccessay initializations:
 *	#define FILE1_SIZE	0x4000
 *	#define FILE2_SIZE	0x2000
 *	#define FILE3_SIZE	0x2000
 *	#define FILE4_SIZE	0x38000
 *	#define FILE5_SIZE	0x40000
 *	#define SYSFILEFLASH_MAX_SIZE			(FILE1_SIZE + FILE2_SIZE + FILE3_SIZE + FILE4_SIZE + FILE5_SIZE)
 *	#define FILE_MAP	static FILE_DESC m_FileSystem[] = \
 *				{ \
 *					*	Name		Offset											MaxSize				read index	write index * \
 *					{"file1.txt",	0x0,											FILE1_SIZE,			0xFFFFFFFF, 0xFFFFFFFF}, \
 *					{"app.crc",		FILE1_SIZE,										FILE2_SIZE,			0xFFFFFFFF, 0xFFFFFFFF}, \
 *					{"file2.txt",	FILE1_SIZE+FILE2_SIZE,							FILE3_SIZE,			0xFFFFFFFF, 0xFFFFFFFF}, \
 *					{"file4.txt",	FILE1_SIZE+FILE2_SIZE+FILE3_SIZE,				FILE4_SIZE,			0xFFFFFFFF, 0xFFFFFFFF}, \
 *					{"app.app",		FILE1_SIZE+FILE2_SIZE+FILE3_SIZE+FILE4_SIZE,	FILE5_SIZE,			0xFFFFFFFF, 0xFFFFFFFF}, \
 *				};
 *	Please note that the offsets of the files have to correspond with sector borders of the flash. One file should be
 *	stored in one sector.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysFile')

#include "CmpStd.h"

#ifndef CDECL
	#define CDECL
#endif

#if defined(WIN32) && defined(_WIN32_WCE)
	#define itoa		_itoa
#endif

/**
 * <category>Compiler switch</category>
 * <description>
 * Compiler switches to enable/disable single features in the component.
 * </description>
 * <element name="SYSFILE_DISABLE_FILE_CACHE">For each transmitted file, the CRC and size is stored in a central config file (cache). This can be disabled by this compiler switch.
 * <element name="SYSFILE_NOPLCLOGICMIGRATION">At startup SysFile.PlcLogicPrefix=0 checks for no bootprojects and than creates the new folder structure with SysFile.PlcLogicPrefix=1. This can be disabled by this compiler switch.
 * </element>
 */ 

/**
 * <category>Static defines</category>
 * <description>Maximum length of a file path</description>
 */
#ifndef MAX_PATH_LEN
	#define MAX_PATH_LEN							255
#endif
#define RTS_MAX_PATH_LEN							MAX_PATH_LEN

/**
 * <category>Static defines</category>
 * <description>Size for temporary buffer e.g. to calculate CRC. If size is larger than 256, buffer is allocated from heap!</description>
 */
#ifndef SYSFILE_TEMP_BUFFER_SIZE
     #define SYSFILE_TEMP_BUFFER_SIZE				256
#endif 

/**
 * <category>Static defines</category>
 * <description>File name prefix to make a file invisible e.g. for the filetransfer dialog. This prevents the corresponding file to be overwritten/read/compromized from outside.
 * </description>
 */
#ifndef SYSFILE_INVISIBLE_FILENAME_PREFIX
	#define SYSFILE_INVISIBLE_FILENAME_PREFIX		"."
#endif

/**
 * <category>Static defines</category>
 * <description>This is the name for a section which contains the name, CRC and size of a file. Is used as a cache for these values.
 *	Improves for example the performance of the file transfer. SYSFILE_DISABLE_FILE_CACHE disables this feature.
 *	NOTE:
 *	It is recommended to use a filereference in the configuration, to move these entries into a separate cfg-file. e.g.:
 *	[CmpSettings]
 *	FileReference.0=SysFileMap.cfg, SysFileMap
 * </description>
 */
#ifndef SYSFILE_MAP_SECTION_NAME
	#define SYSFILE_MAP_SECTION_NAME				"SysFileMap"
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description><p>Setting to get the standard file path for all filenames with no specified path.
 *	Several file paths could be entered, if they were indexed, e.g.:</p>
 *	<p>FilePath.1=./Boot, *.app, *.ap_, *.ret, *.frc</p>
 *	<p>In this case, files with special extensions could be separated into several directories. File
 *	extensions can be specified with the wildcards '*'.</p>
 *	<p>If a file extension is not configured, the standard path (FilePath= or FilePath.1=) is used.</p>
 * </description>
 */
#define SYSFILE_KEY_STRING_GET_FILEPATH						"FilePath"
#ifndef SYSFILE_VALUE_STRING_GET_FILEPATH_DEFAULT
	#define SYSFILE_VALUE_STRING_GET_FILEPATH_DEFAULT		""
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to force the configured file path to every file access.
 *	If an absolute file path is requested and error is returned at this operation (ERR_OPERATION_DENIED).
 * </description>
 */
#define SYSFILE_KEY_INT_FORCE_FILEPATH						"ForceFilePath"
#ifndef SYSFILE_VALUE_INT_FORCE_FILEPATH_DEFAULT
	#define SYSFILE_VALUE_INT_FORCE_FILEPATH_DEFAULT		0
#endif


/**
 * <category>Settings</category>
 * <type>String</type>
 * <description><p>Setting to get the standard file path for file access for all filenames with no specified path or for directory access.
 *	NOTE: THIS IS USED ONLY FOR ALL FILE ACCESS ROUTINES OUT OF THE IEC PROGRAM!
 *	Several file paths could be entered, if they were indexed, e.g.:</p>
 *	<p>IecFilePath.1=./Boot, *.app, *.ap_, *.ret, *.frc</p>
 *	<p>In this case, files with special extensions could be separated into several directories. File
 *	extensions can be specified with the wildcards '*'.</p>
 *	<p>If a file extension is not configured, the standard path (IecFilePath= or IecFilePath.1=) is used.</p>
 *	</description>
 */
#define SYSFILE_KEY_STRING_GET_IEC_FILEPATH					"IecFilePath"
#ifndef SYSFILE_VALUE_STRING_GET_IEC_FILEPATH_DEFAULT
	#define SYSFILE_VALUE_STRING_GET_IEC_FILEPATH_DEFAULT	""
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Setting to force the configured file path to every file access.
 *	If an absolute file path is requested and error is returned at this operation (ERR_OPERATION_DENIED).
 * </description>
 */
#define SYSFILE_KEY_INT_FORCE_IECFILEPATH					"ForceIecFilePath"
#ifndef SYSFILE_VALUE_INT_FORCE_IECFILEPATH_DEFAULT
	#define SYSFILE_VALUE_INT_FORCE_IECFILEPATH_DEFAULT		0
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description><p>Setting to get the placeholder file path for file access. A placeholder is defined like a relative path, but with special placeholder marks, e.g.:
 *		$visu$/mainwindows.bmp
 * The setting has the following structure:
 *		PlaceholderFilePath=[directory, relative or absolute], [placeholder]
 * Example:
 *		PlaceholderFilePath.1=visu/, $visu$
 *	Several file paths could be entered, if they were indexed, e.g.:</p>
 *	<p>PlaceholderFilePath.1=visu/, $visu$</p>
 *	</description>
 */
#define SYSFILE_KEY_STRING_GET_PLACEHOLDER_FILEPATH					"PlaceholderFilePath"
#ifndef SYSFILE_VALUE_STRING_GET_PLACEHOLDER_FILEPATH_DEFAULT
	#define SYSFILE_VALUE_STRING_GET_PLACEHOLDER_FILEPATH_DEFAULT	""
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description><p>Setting to make a placeholder visible in the file transfer window.
 * Example:
 *		PlaceholderFilePath.View=1</p>
 *	</description>
 */
#define SYSFILE_KEY_EXT_VIEW										".View"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description><p>Setting to make all placeholders visible in the file transfer window.
 * Example:
 *		PlaceholderFilePath.All.View=1</p>
 *	</description>
 */
#define SYSFILE_KEY_INT_PLACEHOLDER_FILEPATH_ALL_VIEW				"PlaceholderFilePath.All.View"
#ifndef SYSFILE_VALUE_INT_PLACEHOLDER_FILEPATH_ALL_VIEW_DEFAULT
	#define SYSFILE_VALUE_INT_PLACEHOLDER_FILEPATH_ALL_VIEW_DEFAULT	0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description><p>Setting to mark a placeholder as volatile, i.e. the specified folder is not created automatically at startup and the placeholder is visible in the filetransfer windows only when the folder exists.
 * This behavior is important for hot plug devices like usb sticks. 
 * Example:
 *		PlaceholderFilePath.2=/mnt/USBDevice, $USBDev$
 *		PlaceholderFilePath.2.Volatile=1</p>
 *	</description>
 */
#define SYSFILE_KEY_EXT_VOLATILE									".Volatile"

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description><p>Setting to connect a placeholder virtually with a parent placeholder, i.e. in the filetransfer window this placeholder is reachable via its virtual parent placeholder.
 * Example:
 *		PlaceholderFilePath.1=/temp/oem, $oem$
 *		PlaceholderFilePath.1.VParent=$PlcLogic$
 *	The oem placeholder is virtually placed under $PlcLogic$ but physically at /temp/oem.</p>
 *	</description>
 */
#define SYSFILE_KEY_EXT_VPARENT										".VParent"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description><p>Setting to mark a placeholder so that the specified folder is created when a file is to be written in that folder, the  folder is not created at startup, the placeholder is visible in the filetransfer windows only when the folder exists.
 * Example:
 *		PlaceholderFilePath.2=/Temp, $Temp$
 *		PlaceholderFilePath.2.CreateOnWrite=1</p>
 *	</description>
 */
#define SYSFILE_KEY_EXT_CREATEONWRITE								".CreateOnWrite"

/**
 * <category>Static defines</category>
 * <description>Defines to specify the visu folder that is requested by every filetransfer/fileaccess on visu files. And we specify the placeholder for there files, for which
 *	the destination folder can be specified with the setting "PlaceholderFilePath" (see details above).
 * </description>
 */
#ifndef SYSFILE_VISU_FOLDER
	#define SYSFILE_VISU_FOLDER					"visu/"
#endif
#ifndef SYSFILE_VISU_PLACEHOLDER
	#define SYSFILE_VISU_PLACEHOLDER			"$visu$"
#endif

/**
 * <category>Static defines</category>
 * <description>
 * Defines to specify the plc logic folder that is requested by application and device related file transfers. 
 * The destination folder can be specified with the setting "PlaceholderFilePath" (see details above).
 * </description>
 */
#ifndef SYSFILE_PLC_LOGIC_FOLDER
	#define SYSFILE_PLC_LOGIC_FOLDER			"PlcLogic/"
#endif
#ifndef SYSFILE_PLC_LOGIC_PLACEHOLDER
	#define SYSFILE_PLC_LOGIC_PLACEHOLDER		"$PlcLogic$"
#endif

/**
 * <category>Static defines</category>
 * <description>
 * Setting to configure the plc logic placeholder prefix that is used now by all application related files.
 * -1 - old behaviour: flat file structure (default)
 *  0 - old behaviour: flat file structure, but Reset Origin Device will change that to 1
 *  1 - new folder structure:
 *    $PlcLogic$
 *    + &lt;application&gt;
 *    + $trend$
 *    + $alarm$
 *    + $ac_persistence$
 *    + $visu$
 * </description>
 */
#define SYSFILE_KEY_INT_PLCLOGIC_PREFIX					"PlcLogicPrefix"
#ifndef SYSFILE_VALUE_INT_PLCLOGIC_PREFIX_DEFAULT
	#define SYSFILE_VALUE_INT_PLCLOGIC_PREFIX_DEFAULT	-1
#endif

/**
 * <category>Static defines</category>
 * <description>
 * Placeholder defines for grouping application related files:
 * The destination folders can be specified with the setting "PlaceholderFilePath" (see details above).
 * If not configured resolving depends on "PlcLogicPrefix" (see above).
 * </description>
 */
#ifndef SYSFILE_TREND_FOLDER
	#define SYSFILE_TREND_FOLDER				"trend/"
#endif
#ifndef SYSFILE_TREND_PLACEHOLDER
	#define SYSFILE_TREND_PLACEHOLDER			"$trend$"
#endif
#ifndef SYSFILE_ALARMS_FOLDER
	#define SYSFILE_ALARMS_FOLDER				"alarms/"
#endif
#ifndef SYSFILE_ALARMS_PLACEHOLDER
	#define SYSFILE_ALARMS_PLACEHOLDER			"$alarms$"
#endif
#ifndef SYSFILE_AC_PERSISTENCE_FOLDER
	#define SYSFILE_AC_PERSISTENCE_FOLDER		"ac_persistence/"
#endif
#ifndef SYSFILE_AC_PERSISTENCE_PLACEHOLDER
	#define SYSFILE_AC_PERSISTENCE_PLACEHOLDER	"$ac_persistence$"
#endif

/**
 * <category>Static defines</category>
 * <description>
 * Placeholder defines for backup operations:
 * The destination folders can be specified with the setting "PlaceholderFilePath" (see details above).
 * </description>
 */
#ifndef SYSFILE_BACKUP_FOLDER
	#define SYSFILE_BACKUP_FOLDER				"TBF/"
#endif
#ifndef SYSFILE_BACKUP_PLACEHOLDER
	#define SYSFILE_BACKUP_PLACEHOLDER			"$TBF$"
#endif

/**
 * <category>Static defines</category>
 * <description>
 * Placeholder defines for CNC files:
 * The destination folders can be specified with the setting "PlaceholderFilePath" (see details above).
 * </description>
 */
#ifndef SYSFILE_CNC_FOLDER
	#define SYSFILE_CNC_FOLDER				"_cnc/"
#endif
#ifndef SYSFILE_CNC_PLACEHOLDER
	#define SYSFILE_CNC_PLACEHOLDER			"$_cnc$"
#endif

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * | Access mode
 * | File modes to open a file.
 *
 * .. note::
 *    For all ``*_PLUS`` modes be aware, that after reading from a file, writing can only be done after a call
 *    to |SysFileGetPos| or |SysFileSetPos|! If you call |SysFileWrite| right after |SysFileRead|,
 *    the file pointer could be on an invalid position!
 *
 *    Correct example::
 *
 * 	     SysFileRead();
 * 	     SysFileGetPos();
 * 	     SysFileWrite();
 */
#define RTS_ACCESS_MODE_AM_READ    0	/* Open an existing file with Read access. If file does not exist, Open fails */
#define RTS_ACCESS_MODE_AM_WRITE    1	/* Create new file with Write access. If file does exist, content is discarded */
#define RTS_ACCESS_MODE_AM_APPEND    2	/* Open an existing file with Append (only write) access. If file does not exist, Open fails */
#define RTS_ACCESS_MODE_AM_READ_PLUS    3	/* Open an existing file with Read/Write access. If file does not exist, Open fails */
#define RTS_ACCESS_MODE_AM_WRITE_PLUS    4	/* Create new file with Read/Write access. If file does exist, content is discarded */
#define RTS_ACCESS_MODE_AM_APPEND_PLUS    5	/* Open an existing file with Append (read/write) access. If file does not exist, Open creates a new file */
/* Typed enum definition */
#define RTS_ACCESS_MODE    RTS_IEC_UDINT

/**
 * | File status
 * | Actual file status of the specified file.
 */
#define SYS_FILE_STATUS_FS_OK    0	/* File could be opened */
#define SYS_FILE_STATUS_FS_NO_FILE    1	/* No file available */
#define SYS_FILE_STATUS_FS_ILLEGAL_POS    2	/* Illegal position in the file */
#define SYS_FILE_STATUS_FS_FULL    3	/* No more space on the filesystem */
#define SYS_FILE_STATUS_FS_EOF    4	/* End of file reached */
/* Typed enum definition */
#define SYS_FILE_STATUS    RTS_IEC_INT

/**
 * | File TIME
 * | Timestamps of the specified file.
 */
typedef struct tagSYS_FILETIME
{
	RTS_IEC_UDINT tCreation;		/* Creation time of the file */
	RTS_IEC_UDINT tLastAccess;		/* Time of as access to the file */
	RTS_IEC_UDINT tLastModification;		/* Time of last modification */
} SYS_FILETIME;

/**
 * | Option for SysFileGetPath2, SysFileGetFullPath2, SysFileGetIecPath2
 * | Separation of directory or file
 */
#define SYSFILE_PATH_OPTION_UNKNOWN 0
#define SYSFILE_PATH_OPTION_FILE 1
#define SYSFILE_PATH_OPTION_DIRECTORY 2
#define SYSFILE_PATH_OPTION_FILE_KEEP_NAME 3

/**
 * <category>Event parameter</category>
 * <element name="hFile" type="IN">Handle of the file</element>
 * <element name="szPath" type="IN">Full path name of the file</element>
 * <element name="am " type="IN">Access mode for open, see RTS_ACCESS_MODE</element>
 */
typedef struct
{
	RTS_HANDLE hFile;
	char *pszPath;
	RTS_ACCESS_MODE am;
} EVTPARAM_SysFileOpen;
#define EVTPARAMID_SysFileOpen						0x0001
#define EVTVERSION_SysFileOpen						0x0001

/**
 * <category>Event parameter</category>
 * <element name="hFile" type="IN">Handle of the file</element>
 */
typedef struct
{
	RTS_HANDLE hFile;
} EVTPARAM_SysFileClose;
#define EVTPARAMID_SysFileClose						0x0002
#define EVTVERSION_SysFileClose						0x0001

/**
 * <category>Event parameter</category>
 * <element name="szFileName" type="OUT">name of founded file</element>
 * <element name="byIndex" type="IN/OUT">index of file in file mapping list</element>
 */
 #define MAX_FILENAME 32
typedef struct
{
	char * pbyExecute;
  int * pintIndex;
}EVTPARAM_SysFileFlashGetFileMapIndex;
#define EVTPARAMID_SysFileFlashGetFileMapIndex					0x0003
#define EVTVERSION_SysFileFlashGetFileMapIndex					0x0001


/**
 * <category>Events</category>
 * <description>Event is sent when a file is opened. It is sent directly after the file was opened.
 * Note: The event is set only with SysFile, it is not set with SysFileFlash.
 * Note: Event set after CH_INIT2. There is no notification of opening a file before this hook.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_SysFileOpen</param>
 */
#define EVT_SysFileOpen					MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Events</category>
 * <description>Event is sent when a file is closed. It is send directly before the file is closed (file handle still valid).
 * Note: The event is set only with SysFile, it is not set with SysFileFlash.
 * Note: Event set after CH_INIT2. There is no notification of opening a file before this hook.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_SysFileClose</param>
 */
#define EVT_SysFileClose					MAKE_EVENTID(EVTCLASS_INFO, 2)

/**
 * <category>Events</category>
 * <description>The event is sent if the function GetFileMapIndex is called
 *	NOTE:
 *	This event is fired for every call and every loop call of count of files
 * </description>
 * <param name="pEventParam" type="IN/OUT">EVTPARAM_SysFileFlashGetFileMapIndex</param>
 */
#define EVT_SysFileFlashGetFileMapIndex					MAKE_EVENTID(EVTCLASS_INFO, 3)

/**
 * Close a file specified by handle
 * :return: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysfileclose_struct
{
	RTS_IEC_HANDLE hFile;				/* VAR_INPUT */	/* Handle of the file */
	RTS_IEC_RESULT SysFileClose;		/* VAR_OUTPUT */	
} sysfileclose_struct;

DEF_API(`void',`CDECL',`sysfileclose',`(sysfileclose_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC19E28BA),0x03050500)

/**
 * | Copy one file to another.
 * | A standard path will be added to the filename, if no path is specified.
 * :return: The runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysfilecopy_struct
{
	RTS_IEC_STRING *szDestFileName;		/* VAR_INPUT */	/* Destination file name. File name can contain an absolute or relative path to the file.
 Path entries must be separated with a Slash (/)  and not with a Backslash (\\)! */
	RTS_IEC_STRING *szSourceFileName;	/* VAR_INPUT */	/* Source file name. File name can contain an absolute or relative path to the file.											
 Path entries must be separated with a Slash (/)  and not with a Backslash (\\)! */
	RTS_IEC_XWORD *pulCopied;			/* VAR_INPUT */	/* Number of bytes copied */
	RTS_IEC_RESULT SysFileCopy;			/* VAR_OUTPUT */	
} sysfilecopy_struct;

DEF_API(`void',`CDECL',`sysfilecopy',`(sysfilecopy_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xDB491610),0x03050500)

/**
 * | Delete the file specified by name.
 * | A standard path will be added in the runtime system to the filename, if no path is specified.
 * :return: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysfiledelete_struct
{
	RTS_IEC_STRING *szFileName;			/* VAR_INPUT */	/* File name. File name can contain an absolute or relative path to the file.
 Path entries must be separated with a Slash (/)  and not with a Backslash (\\)! */
	RTS_IEC_RESULT SysFileDelete;		/* VAR_OUTPUT */	
} sysfiledelete_struct;

DEF_API(`void',`CDECL',`sysfiledelete',`(sysfiledelete_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA977F762),0x03050500)

/**
 * Delete the file specified by handle
 * :return: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysfiledeletebyhandle_struct
{
	RTS_IEC_HANDLE hFile;				/* VAR_INPUT */	/* Handle of the file */
	RTS_IEC_RESULT SysFileDeleteByHandle;	/* VAR_OUTPUT */	
} sysfiledeletebyhandle_struct;

DEF_API(`void',`CDECL',`sysfiledeletebyhandle',`(sysfiledeletebyhandle_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC812562E),0x03050500)

/**
 * Check, if end of file is reached
 * :return: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysfileeof_struct
{
	RTS_IEC_HANDLE hFile;				/* VAR_INPUT */	/* Handle of the file */
	RTS_IEC_RESULT SysFileEOF;			/* VAR_OUTPUT */	
} sysfileeof_struct;

DEF_API(`void',`CDECL',`sysfileeof',`(sysfileeof_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x30A3EB85),0x03050500)

/**
 * Flush the file cache and write into the file
 * :return: Returns the runtime system error code (see CmpErrors_Itfs.library):
 *
 * - ERR_OK: Succeeded flushing the file
 * - ERR_FAILED: Error occurred during file flush
 * - ERR_NOTIMPLEMENTED: File flush is not implemented
 * - ERR_NOT_SUPPORTED: File flush not available on the target
 */
typedef struct tagsysfileflush_struct
{
	RTS_IEC_HANDLE hFile;				/* VAR_INPUT */	/* Handle of the file */
	RTS_IEC_RESULT SysFileFlush;		/* VAR_OUTPUT */	
} sysfileflush_struct;

DEF_API(`void',`CDECL',`sysfileflush',`(sysfileflush_struct *p)',1,0x32985005,0x03050500)

/**
 * Get the file name from file specified by handle
 * :return: File name of the specified file
 */
typedef struct tagsysfilegetname_struct
{
	RTS_IEC_HANDLE hFile;				/* VAR_INPUT */	/* Handle of the file */
	RTS_IEC_STRING *SysFileGetName;		/* VAR_OUTPUT */	
} sysfilegetname_struct;

DEF_API(`void',`CDECL',`sysfilegetname',`(sysfilegetname_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4AEE0669),0x03050500)

/**
 * Get the file name from file specified by handle
 * :return: File name of the specified file
 */
typedef struct tagsysfilegetname2_struct
{
	RTS_IEC_HANDLE hFile;				/* VAR_INPUT */	/* Handle of the file */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library) */
	RTS_IEC_STRING *SysFileGetName2;	/* VAR_OUTPUT */	
} sysfilegetname2_struct;

DEF_API(`void',`CDECL',`sysfilegetname2',`(sysfilegetname2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x2856F375),0x03050500)

/**
 * | Get the path of this file.
 * | If a path is specified in the filename, the path will be extracted from the filename.
 * | If no path is specified in the filename, the standard path for this file extension type will be returned.
 * :return: The runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysfilegetpath_struct
{
	RTS_IEC_STRING *szFileName;			/* VAR_INPUT */	/* File name. Can contain an absolute or relative path */
	RTS_IEC_STRING *szPath;				/* VAR_INPUT */	/* Path for this file */
	RTS_IEC_DINT diMaxLen;				/* VAR_INPUT */	/* Maximum size in bytes of path length */
	RTS_IEC_RESULT SysFileGetPath;		/* VAR_OUTPUT */	
} sysfilegetpath_struct;

DEF_API(`void',`CDECL',`sysfilegetpath',`(sysfilegetpath_struct *p)',1,0xE8836F87,0x03050500)

/**
 * Get actual file pointer position
 * :return: The runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysfilegetpos_struct
{
	RTS_IEC_HANDLE hFile;				/* VAR_INPUT */	/* Handle of the file */
	RTS_IEC_XWORD *pulPos;				/* VAR_INPUT */	/* Pointer to get actual position of the file pointer from the beginning of the file */
	RTS_IEC_RESULT SysFileGetPos;		/* VAR_OUTPUT */	
} sysfilegetpos_struct;

DEF_API(`void',`CDECL',`sysfilegetpos',`(sysfilegetpos_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4F0954A2),0x03050500)

/**
 * | Get file size of the file specified by name.
 * | A standard path will be added to the filename, if no path is specified.
 * :return: Size of the file in bytes
 */
typedef struct tagsysfilegetsize_struct
{
	RTS_IEC_STRING *szFileName;			/* VAR_INPUT */	/* File name. File name can contain an absolute or relative path to the file.
 Path entries must be separated with a Slash (/) and not with a Backslash (\\)! */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library):

 - ERR_OK: Successful
 - ERR_NO_OBJECT: File not available
 - ERR_FAILED: Failed to get file size */
	RTS_IEC_XWORD SysFileGetSize;		/* VAR_OUTPUT */	
} sysfilegetsize_struct;

DEF_API(`void',`CDECL',`sysfilegetsize',`(sysfilegetsize_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0A16C4DB),0x03050500)

/**
 * Get file size of the file specified by handle
 * :return: Size of the file in bytes
 */
typedef struct tagsysfilegetsizebyhandle_struct
{
	RTS_IEC_HANDLE hFile;				/* VAR_INPUT */	/* Handle of the file */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library) */
	RTS_IEC_XWORD SysFileGetSizeByHandle;	/* VAR_OUTPUT */	
} sysfilegetsizebyhandle_struct;

DEF_API(`void',`CDECL',`sysfilegetsizebyhandle',`(sysfilegetsizebyhandle_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x847C756B),0x03050500)

/**
 * Get the file status
 * :return: File status. See category file status
 */
typedef struct tagsysfilegetstatus_struct
{
	RTS_IEC_HANDLE hFile;				/* VAR_INPUT */	/* Handle of the file */
	RTS_IEC_INT SysFileGetStatus;		/* VAR_OUTPUT, Enum: SYS_FILE_STATUS */
} sysfilegetstatus_struct;

DEF_API(`void',`CDECL',`sysfilegetstatus',`(sysfilegetstatus_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x31FB098C),0x03050500)

/**
 * Get the file status
 * :return: File status. See category file status
 */
typedef struct tagsysfilegetstatus2_struct
{
	RTS_IEC_HANDLE hFile;				/* VAR_INPUT */	/* Handle of the file */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library) */
	RTS_IEC_INT SysFileGetStatus2;		/* VAR_OUTPUT, Enum: SYS_FILE_STATUS */
} sysfilegetstatus2_struct;

DEF_API(`void',`CDECL',`sysfilegetstatus2',`(sysfilegetstatus2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x59D8FC78),0x03050500)

/**
 * | Get file time of the specified file.
 * | A standard path will be added to the filename, if no path is specified.
 * :return: The runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysfilegettime_struct
{
	RTS_IEC_STRING *szFileName;			/* VAR_INPUT */	/* File name. File name can contain an absolute or relative path to the file.	
 Path entries must be separated with a Slash (/)  and not with a Backslash (\\)! */
	SYS_FILETIME *ptFileTime;			/* VAR_INPUT */	/* Pointer to get the file time results. */
	RTS_IEC_RESULT SysFileGetTime;		/* VAR_OUTPUT */	
} sysfilegettime_struct;

DEF_API(`void',`CDECL',`sysfilegettime',`(sysfilegettime_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB2AF6BDD),0x03050500)

/**
 * | Open or create file. A standard path will be added to the filename, if no path is specified in the file name.
 * | If a file extension is specified in the settings, this path will be used (see category settings).
 *
 * .. note:: File name can contain an absolute or relative path to the file. Path entries
 *           must be separated with a Slash (/)  and not with a Backslash (\\)!
 *
 * :return: Handle to the file or RTS_INVALID_HANDLE if failed
 */
typedef struct tagsysfileopen_struct
{
	RTS_IEC_STRING *szFile;				/* VAR_INPUT */	/* File name. File name can contain an absolute or relative path to the file.	
 Path entries must be separated with a Slash (/)  and not with a Backslash (\\)! */
	RTS_IEC_UDINT am;					/* VAR_INPUT, Enum: ACCESS_MODE */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library) */
	RTS_IEC_HANDLE SysFileOpen;			/* VAR_OUTPUT */	
} sysfileopen_struct;

DEF_API(`void',`CDECL',`sysfileopen',`(sysfileopen_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xFE31259F),0x03050500)

/**
 * Read number of bytes out of the file
 * :return: Number of bytes read from file. 0=if failed
 */
typedef struct tagsysfileread_struct
{
	RTS_IEC_HANDLE hFile;				/* VAR_INPUT */	/* Handle of the file */
	RTS_IEC_BYTE *pbyBuffer;			/* VAR_INPUT */	/* Pointer to buffer for read data */
	RTS_IEC_XWORD ulSize;				/* VAR_INPUT */	/* Number of bytes to read from file. Must be less or equal the buffer size! */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library) */
	RTS_IEC_XWORD SysFileRead;			/* VAR_OUTPUT */	
} sysfileread_struct;

DEF_API(`void',`CDECL',`sysfileread',`(sysfileread_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD962D4F9),0x03050500)

/**
 * | Rename the file.
 * | A standard path will be added to the filename, if no path is specified.
 * :return: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysfilerename_struct
{
	RTS_IEC_STRING *szOldFileName;		/* VAR_INPUT */	/* Old file name. File name can contain an absolute or relative path to the file.
 Path entries must be separated with a Slash (/)  and not with a Backslash (\\)! */
	RTS_IEC_STRING *szNewFileName;		/* VAR_INPUT */	/* New file name. File name can contain an absolute or relative path to the file.
 Path entries must be separated with a Slash (/)  and not with a Backslash (\\)! */
	RTS_IEC_RESULT SysFileRename;		/* VAR_OUTPUT */	
} sysfilerename_struct;

DEF_API(`void',`CDECL',`sysfilerename',`(sysfilerename_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF3B9A110),0x03050500)

/**
 * Set the file pointer to the specified position
 * :return: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysfilesetpos_struct
{
	RTS_IEC_HANDLE hFile;				/* VAR_INPUT */	/* Handle of the file */
	RTS_IEC_XWORD ulOffset;				/* VAR_INPUT */	/* Offset to set from the beginning of the file */
	RTS_IEC_RESULT SysFileSetPos;		/* VAR_OUTPUT */	
} sysfilesetpos_struct;

DEF_API(`void',`CDECL',`sysfilesetpos',`(sysfilesetpos_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xFC7A70CE),0x03050500)

/**
 * Set a new filesize. May be larger or smaller than current size.
 * :return: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysfiletruncate_struct
{
	RTS_IEC_HANDLE hFile;				/* VAR_INPUT */	/* Handle of the file */
	RTS_IEC_XWORD ulSizeNew;			/* VAR_INPUT */	/* Size to set. */
	RTS_IEC_RESULT SysFileTruncate;		/* VAR_OUTPUT */	
} sysfiletruncate_struct;

DEF_API(`void',`CDECL',`sysfiletruncate',`(sysfiletruncate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF2C7CF6C),0x03050600)

/**
 * Write number of bytes to the file. File must be opened with |AM_WRITE| or |AM_APPEND|.
 * :return: Number of bytes written to the file. 0=if failed
 */
typedef struct tagsysfilewrite_struct
{
	RTS_IEC_HANDLE hFile;				/* VAR_INPUT */	/* Handle of the file */
	RTS_IEC_BYTE *pbyBuffer;			/* VAR_INPUT */	/* Pointer to buffer with data to write to file */
	RTS_IEC_XWORD ulSize;				/* VAR_INPUT */	/* Number of bytes to write in the file. Must be less or equal the buffer size! */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library) */
	RTS_IEC_XWORD SysFileWrite;			/* VAR_OUTPUT */	
} sysfilewrite_struct;

DEF_API(`void',`CDECL',`sysfilewrite',`(sysfilewrite_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x6AE210A7),0x03050500)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


/**
 * <category>File info</category>
 * <description>
 *	<element name="pszName" type="IN">Name of the file</element>
 *	<element name="am" type="IN">Access mode. See corresponding category</element>
 *	<element name="status" type="IN">File status. See corresponding category</element>
 *	<element name="hOSFile" type="IN">Operating system file handle</element>
 * </description>
 */
typedef struct SYS_FILE_INFO_
{
	char szName[MAX_PATH_LEN];
	RTS_ACCESS_MODE am;
	SYS_FILE_STATUS status;
	RTS_HANDLE hOSFile;
} SYS_FILE_INFO;


/* Backward compatibility */
#define ACCESS_MODE_AM_READ				RTS_ACCESS_MODE_AM_READ
#define ACCESS_MODE_AM_WRITE			RTS_ACCESS_MODE_AM_WRITE
#define ACCESS_MODE_AM_APPEND			RTS_ACCESS_MODE_AM_APPEND
#define ACCESS_MODE_AM_READ_PLUS		RTS_ACCESS_MODE_AM_READ_PLUS
#define ACCESS_MODE_AM_WRITE_PLUS		RTS_ACCESS_MODE_AM_WRITE_PLUS
#define ACCESS_MODE_AM_APPEND_PLUS		RTS_ACCESS_MODE_AM_APPEND_PLUS
#define AM_READ							ACCESS_MODE_AM_READ
#define AM_WRITE						ACCESS_MODE_AM_WRITE
#define AM_APPEND						ACCESS_MODE_AM_APPEND
#define AM_READ_PLUS					ACCESS_MODE_AM_READ_PLUS
#define AM_WRITE_PLUS					ACCESS_MODE_AM_WRITE_PLUS
#define AM_APPEND_PLUS					ACCESS_MODE_AM_APPEND_PLUS

#define FS_OK							SYS_FILE_STATUS_FS_OK
#define FS_NO_FILE						SYS_FILE_STATUS_FS_NO_FILE
#define FS_ILLEGALPOS					SYS_FILE_STATUS_FS_ILLEGALPOS
#define FS_FULL							SYS_FILE_STATUS_FS_FULL

/**
 * <category>Options</category>
 * <description>
 * Flags for SysFileGetNextConfiguredPath2
 *	<element name="SYSFILE_BIT_VIEWALL" type="IN">Overrides the setting PlaceholderFilePath.x.View to view all placeholders.</element>
 *	<element name="SYSFILE_BIT_VIRTUAL" type="IN">In case the placeholder has a virtual parent return this instead of the resolved path.</element>
 * </description>
 */
#define SYSFILE_BIT_VIEWALL 0x01
#define SYSFILE_BIT_VIRTUAL 0x02

#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysFileOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysFileOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>
 *	<p>Open or create file. A standard path will be added to the filename, if no path is specified in the
 *	file name.</p>
 *	<p>If a file extension is specified in the settings, this path will be used (see category settings).</p>
 *	<p>IMPLEMENTATION NOTE: File name can contain an absolute or relative path to the file. Path entries
 *	must be separated with a '/' and not with a '\"!</p>
 * </description>
 * <param name="pszFile" type="IN">File name. File name can contain an absolute or relative path to the 
 *	file. Path entries must be separated with a '/' and not with a '\"!</param>
 * <param name="am" type="IN"><p>Requested access mode to the file:</p>
 *	<ul>
 *		<li>AM_READ: If file does not exist, an error is returned. If the file exists, the file 
 *					will be opened</li>
 *		<li>AM_WRITE: If file does not exist, a new file will be created. If the file exists,
 *					it will be overwritten!</li>
 *		<li>AM_APPEND: If the file does not exist, an error is returned. If the file exists, the file 
 *					will be opened</li>
 *	</ul>
 * </param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the file or RTS_INVALID_HANDLE if failed</result>
 */
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysFileOpen',`(char *pszFile, RTS_ACCESS_MODE am, RTS_RESULT *pResult)')

/**
 * <description>Open or create a file. File will be opened with no standard path. The file name
 *	will be used as it is.</description>
 * <param name="pszFile" type="IN">File name. File name can contain an absolute or relative path to the 
 *	file. Path entries must be separated with a '/' and not with a '\"!</param>
 * <param name="am" type="IN"><p>Requested access mode to the file:</p>
 *	<ul>
 *		<li>AM_READ: If file does not exist, an error is returned. If the file exists, the file 
 *					will be opened</li>
 *		<li>AM_WRITE: If file does not exist, a new file will be created. If the file exists,
 *					it will be overwritten!</li>
 *		<li>AM_APPEND: If the file does not exist, an error is returned. If the file exists, the file 
 *					will be opened</li>
 *	</ul>
 * </param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the file or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SysFileOpen_',`(char *pszFile, RTS_ACCESS_MODE am, RTS_RESULT *pResult)')

/**
 * <description>Close a file specified by handle</description>
 * <param name="hFile" type="IN">Handle to the file</param>
 * <result>error code</result>
 */
DEF_DELETEITF_API(`RTS_RESULT',`CDECL',`SysFileClose',`(RTS_HANDLE hFile)')

/**
 * <description>Close a file specified by handle. System specific version of the function</description>
 * <param name="hFile" type="IN">Handle to the file</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileClose_',`(RTS_HANDLE hFile)')

/**
 * <description>Get the file status</description>
 * <param name="hFile" type="IN">Handle to the file</param>
 * <param name="pResult" type="IN">Pointer to error code</param>
 * <result>File status. See category file status</result>
 */
DEF_HANDLEITF_API(`SYS_FILE_STATUS',`CDECL',`SysFileGetStatus',`(RTS_HANDLE hFile, RTS_RESULT *pResult)')

/**
 * <description>Get the file name from file specified by handle</description>
 * <param name="hFile" type="IN">Handle to the file</param>
 * <param name="pResult" type="IN">Pointer to error code</param>
 * <result>File name</result>
 */
DEF_HANDLEITF_API(`char*',`CDECL',`SysFileGetName',`(RTS_HANDLE hFile, RTS_RESULT *pResult)')

/**
 * <description>
 *	Read number of bytes out of the file
 * </description>
 * <param name="hFile" type="IN">Handle to the file</param>
 * <param name="pbyBuffer" type="OUT">Pointer to buffer for read data</param>
 * <param name="uiSize" type="IN">Number of bytes to read from file. Must be less or equal the buffer size!</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of bytes read from file. 0=if failed</result>
 */
DEF_HANDLEITF_API(`RTS_SIZE',`CDECL',`SysFileRead',`(RTS_HANDLE hFile, unsigned char *pbyBuffer, RTS_SIZE uiSize, RTS_RESULT *pResult)')

/**
 * <description>
 *	Write number of bytes to the file. File must be opened with AM_WRITE or AM_APPEND.
 * </description>
 * <param name="hFile" type="IN">Handle to the file</param>
 * <param name="pbyBuffer" type="IN">Pointer to buffer with data to write to file</param>
 * <param name="uiSize" type="IN">Number of bytes to write in the file. Must be less or equal the buffer size!</param>
 * <param name="pResult" type="OUT">Pointer to error code </param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">File could be written</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter (handle invalid, buffer pointer NULL or buffer size 0)</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Error occurred during writing</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_DISK_FULL">Disk is full so writing failed</errorcode>
 * <result>Number of bytes written to the file. 0=if failed</result>
 */
DEF_HANDLEITF_API(`RTS_SIZE',`CDECL',`SysFileWrite',`(RTS_HANDLE hFile, unsigned char *pbyBuffer, RTS_SIZE uiSize, RTS_RESULT *pResult)')

/**
 * <description>
 *	Delete the file specified by name.
 *	A standard path will be added to the filename, if no path is specified.
 * </description>
 * <param name="pszFile" type="IN">File name. File name can contain an absolute or relative path to the 
 *	file. Path entries must be separated with a '/' and not with a '\"!</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileDelete',`(char *pszFile)')

/**
 * <description>
 *	Delete the file specified by name. Filename will be used with no standard path.
 * </description>
 * <param name="pszFile" type="IN">File name. File name can contain an absolute or relative path to the 
 *	file. Path entries must be separated with a '/' and not with a '\"!</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileDelete_',`(char *pszFile)')

/**
 * <description>
 *	Delete the file specified by handle
 * </description>
 * <param name="hFile" type="IN">Handle to the file</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysFileDeleteByHandle',`(RTS_HANDLE hFile)')

/**
 * <description>
 *	Rename the file.
 *	A standard path will be added to the filename, if no path is specified.
 * </description>
 * <param name="pszOldFileName" type="IN">Old file name. File name can contain an absolute or relative path to the 
 *	file. Path entries must be separated with a '/' and not with a '\"!</param>
 * <param name="pszNewFileName" type="IN">New file name. File name can contain an absolute or relative path to the 
 *	file. Path entries must be separated with a '/' and not with a '\"!</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">File could be successfully renamed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter (pointer NULL or length 0)</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">Failed because old file does not exist</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_DUPLICATE">Failed because new file already exists</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileRename',`(char *pszOldFileName, char *pszNewFileName)')

/**
 * <description>
 *	Rename the file. File will be renamed with no standard path.
 * </description>
 * <param name="pszOldFileName" type="IN">Old file name. File name can contain an absolute or relative path to the 
 *	file. Path entries must be separated with a '/' and not with a '\"!</param>
 * <param name="pszNewFileName" type="IN">New file name. File name can contain an absolute or relative path to the 
 *	file. Path entries must be separated with a '/' and not with a '\"!</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileRename_',`(char *pszOldFileName, char *pszNewFileName)')

/**
 * <description>
 *	Set the file pointer to the specified position
 * </description>
 * <param name="hFile" type="IN">Handle to the file</param>
 * <param name="uiOffset" type="IN">Offset to set from the beginning of the file</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysFileSetPos',`(RTS_HANDLE hFile, RTS_SIZE uiOffset)')

/**
 * <description>
 *	Get actual file pointer position
 * </description>
 * <param name="hFile" type="IN">Handle to the file</param>
 * <param name="puiPos" type="OUT">Pointer to get actual position of the file pointer from
 *	the beginning of the file</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysFileGetPos',`(RTS_HANDLE hFile, RTS_SIZE *puiPos)')

/**
 * <description>
 *	Get file size of the file specified by name
 *	A standard path will be added to the filename, if no path is specified.
 * </description>
 * <param name="pszFile" type="IN">File name. File name can contain an absolute or relative path to the 
 *	file. Path entries must be separated with a '/' and not with a '\"!</param>
 * <param name="pResult" type="OUT">Pointer to error code:
 *	ERR_OK: Successful
 *	ERR_NO_OBJECT: File not available
 *	ERR_FAILED: Failed to get file size
 * </param>
 * <result>Size of the file in bytes</result>
 */
DEF_ITF_API(`RTS_SIZE',`CDECL',`SysFileGetSize',`(char *pszFile, RTS_RESULT *pResult)')

/**
 * <description>
 *	Get file size of the file specified by name, No standard path will be added to the file name.
 * </description>
 * <param name="pszFile" type="IN">File name. File name can contain an absolute or relative path to the 
 *	file. Path entries must be separated with a '/' and not with a '\"!</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Size of the file in bytes</result>
 */
DEF_ITF_API(`RTS_SIZE',`CDECL',`SysFileGetSize_',`(char *pszFile, RTS_RESULT *pResult)')

/**
 * <description>
 *	Get file size of the actual opened file
 * </description>
 * <param name="hFile" type="IN">Handle to the file</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Size of the file in bytes</result>
 */
DEF_HANDLEITF_API(`RTS_SIZE',`CDECL',`SysFileGetSizeByHandle',`(RTS_HANDLE hFile, RTS_RESULT *pResult)')

/**
 * <description>
 *	Get file time of the specified file.
 *	A standard path will be added to the filename, if no path is specified.
 * </description>
 * <param name="pszFile" type="IN">File name. File name can contain an absolute or relative path to the 
 *	file. Path entries must be separated with a '/' and not with a '\"!</param>
 * <param name="pftFileTime" type="OUT">Pointer to get the file time results.
 *	IMPLEMENTATION NOTE: All time values must be local time!</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileGetTime',`(char *pszFile, SYS_FILETIME *pftFileTime)')

/**
 * <description>
 *	Get file time of the file specified by name. No standard path will be added.
 * </description>
 * <param name="pszFile" type="IN">File name. File name can contain an absolute or relative path to the 
 *	file. Path entries must be separated with a '/' and not with a '\"!</param>
 * <param name="pftFileTime" type="OUT">Pointer to get the file time results.
 *	IMPLEMENTATION NOTE: All time values must be local time!</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileGetTime_',`(char *pszFile, SYS_FILETIME *pftFileTime)')

/**

 * <description>
 *	Check, if end of file is reached at reading from the file.
 *	IMPLEMENTATION NOTE:
 *	End of file is only checked after a read operation with SysFileRead! But after a SysFileWrite or SysFileSetPos call, the function
 *	returns ERR_FAILED (no end of file)!
 * </description>
 * <param name="hFile" type="IN">Handle to the file</param>
 * <result>Error code:
 *	<ul>
 *		<li>ERR_OK: End of file reached at reading beyond the end of the file</li>
 *		<li>ERR_FAILED: No end of file reached</li>
 *		<li>ERR_PARAMETER: hFile is invalid</li>
 *	</ul>
 * </result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysFileEOF',`(RTS_HANDLE hFile)')

/**
 * <description>
 *	Copy one file to another.
 *	A standard path will be added to the filename, if no path is specified.
 *  IMPLEMENTATION NOTE:
 *	If the destination file exists, the file will be overwritten and the function succeeded.
 * </description>
 * <param name="pszDestFileName" type="IN">Destination file name. File name can contain an absolute or relative path to the 
 *	file. Path entries must be separated with a '/' and not with a '\"!</param>
 * <param name="pszSourceFileName" type="IN">Source file name. File name can contain an absolute or relative path to the 
 *	file. Path entries must be separated with a '/' and not with a '\"!</param>
 * <param name="puiCopied" type="OUT">Number of bytes copied</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileCopy',`(char *pszDestFileName, char *pszSourceFileName, RTS_SIZE *puiCopied)')

/**
 * <description>
 *	Copy one file in another. No standard path will be added to filename.
 * </description>
 * <param name="pszFile" type="IN">File name. File name can contain an absolute or relative path to the 
 *	file. Path entries must be separated with a '/' and not with a '\"!</param>
 * <param name="pftFileTime" type="OUT">Pointer to get the file time results</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileCopy_',`(char *pszDestFileName, char *pszSourceFileName, RTS_SIZE *puiCopied)')

/**
 * <description>
 *	Get the path of this file. If a path is specified in the filename, the path will be extracted from the filename.
 *	If no path is specified in the filename, the standard path for this file extension type will be returned.
 * </description>
 * <param name="pszFileName" type="IN">File name. Can contain an absolute or relative path</param>
 * <param name="pszPath" type="OUT">Path for this file</param>
 * <param name="iMaxLen" type="IN">Maximum size in bytes of path length</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Resolved file path is correctly returned</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter (pointer NULL or length 0)</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_BUFFERSIZE">Path buffer too short</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_OPERATION_DENIED">Access to this file path not allowed! The following file or directory access must be denied!</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileGetPath',`(char *pszFileName, char *pszPath, RTS_SIZE iMaxLen)')

/**
 * <description>
 *	Get the path of this file. If a path is specified in the filename, the path will be extracted from the filename.
 *	If no path is specified in the filename, the standard path for this file extension type will be returned.
 * </description>
 * <param name="pszFileName" type="IN">File name. Can contain an absolute or relative path</param>
 * <param name="nOption" type="IN">Separation of directory or file</param>
 * <param name="pszPath" type="OUT">Path for this file</param>
 * <param name="iMaxLen" type="IN">Maximum size in bytes of path length</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Resolved file path is correctly returned</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter (pointer NULL or length 0)</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_BUFFERSIZE">Path buffer too short</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_OPERATION_DENIED">Access to this file path not allowed! The following file or directory access must be denied!</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileGetPath2',`(char *pszFileName, RTS_I32 nOption, char *pszPath, RTS_SIZE iMaxLen)')

/**
 * <description>
 *	Get the path of this file including the filename. If no path is specified in pszFileName, the filename is returned in pszPath.
 * </description>
 * <param name="pszFileName" type="IN">File name. Can contain an absolute or relative path</param>
 * <param name="pszPath" type="OUT">Path for this file including the filename</param>
 * <param name="iMaxLen" type="IN">Maximum size in bytes of path length</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Resolved file path including the filename is correctly returned</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter (pointer NULL or length 0)</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_BUFFERSIZE">Path buffer too short</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_OPERATION_DENIED">Access to this file path not allowed! The following file or directory access must be denied!</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileGetFullPath',`(char *pszFileName, char *pszPath, RTS_SIZE iMaxLen)')

/**
 * <description>
 *	Get the path of this file including the filename. If no path is specified in pszFileName, the filename is returned in pszPath.
 * </description>
 * <param name="pszFileName" type="IN">File name. Can contain an absolute or relative path</param>
 * <param name="nOption" type="IN">Separation of directory or file</param>
 * <param name="pszPath" type="OUT">Path for this file including the filename</param>
 * <param name="iMaxLen" type="IN">Maximum size in bytes of path length</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Resolved file path including the filename is correctly returned</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter (pointer NULL or length 0)</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_BUFFERSIZE">Path buffer too short</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_OPERATION_DENIED">Access to this file path not allowed! The following file or directory access must be denied!</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileGetFullPath2',`(char *pszFileName, RTS_I32 nOption, char *pszPath, RTS_SIZE iMaxLen)')

/**
 * <description>
 *	Get the path of this file for Iec applications. If a path is specified in the filename, the path will be extracted from the filename.
 *	If no path is specified in the filename, the standard path for this file extension type will be returned.
 * </description>
 * <param name="pszFileName" type="IN">File name. Can contain an absolute or relative path</param>
 * <param name="pszPath" type="OUT">Path for this file</param>
 * <param name="iMaxLen" type="IN">Maximum size in bytes of path length</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileGetIecPath',`(char *pszFileName, char *pszPath, RTS_SIZE iMaxLen)')

/**
 * <description>
 *	Get the path of this file for Iec applications. If a path is specified in the filename, the path will be extracted from the filename.
 *	If no path is specified in the filename, the standard path for this file extension type will be returned.
 * </description>
 * <param name="pszFileName" type="IN">File name. Can contain an absolute or relative path</param>
 * <param name="nOption" type="IN">Separation of directory or file</param>
 * <param name="pszPath" type="OUT">Path for this file</param>
 * <param name="iMaxLen" type="IN">Maximum size in bytes of path length</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileGetIecPath2',`(char *pszFileName, RTS_I32 nOption, char *pszPath, RTS_SIZE iMaxLen)')

/**
 * <description>
 *	Generate the CRC32 of a file. Can be used to check file integrity.
 *	ATTENTION: Only for backward compatibility! CRC is implemented not independant from buffer size!
 * </description>
 * <param name="pszFile" type="IN">File name. Can contain an absolute or relative path</param>
 * <param name="ulSize" type="IN">Size to calculate checksum. 0 if real size of file should be used [default]</param>
 * <param name="pulCRC" type="OUT">Pointer to get CRC32 result</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileGenerateCRC',`(char *pszFile, RTS_SIZE ulSize, RTS_UI32 *pulCRC)')

/**
 * <description>
 *	Generate the CRC32 of a file. Can be used to check file integrity.
 * </description>
 * <param name="pszFile" type="IN">File name. Can contain an absolute or relative path</param>
 * <param name="ulSize" type="IN">Size to calculate checksum. 0 if real size of file should be used [default]</param>
 * <param name="pulCRC" type="OUT">Pointer to get CRC32 result</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileGenerateCRC2',`(char *pszFile, RTS_SIZE ulSize, RTS_UI32 *pulCRC)')

/**
 * <description>
 *	Generate the CRC32 of a file. Can be used to check file integrity.
 * </description>
 * <param name="pszFile" type="IN">File name. Can contain an absolute or relative path</param>
 * <param name="ulSize" type="IN">Size to calculate checksum. 0 if real size of file should be used [default]</param>
 * <param name="pulCRC" type="OUT">Pointer to get CRC32 result</param>
 * <param name="bUseCache type="IN">Flag whether to use the SysFileMap cache. In case there is no cache this flag is ignored.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileGenerateCRC3',`(char *pszFile, RTS_SIZE ulSize, RTS_UI32 *pulCRC, RTS_BOOL bUseCache)')

/**
 * <description>
 *	Generate the CRC32 of a file. Can be used to check file integrity.
 *	IMPLEMENTATION NOTE:
 *	This interface function is implemented operating system dependant! Optimizations can be done here.
 * </description>
 * <param name="pszFile" type="IN">File name. Can contain an absolute or relative path</param>
 * <param name="ulSize" type="IN">Size to calculate checksum. 0 if real size of file should be used [default]</param>
 * <param name="pulCRC" type="OUT">Pointer to get CRC32 result</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileGenerateCRC2_',`(char *pszFile, RTS_SIZE ulSize, RTS_UI32 *pulCRC)')

/**
 * <description>
 *	Flush the file cache and write into the file.
 * </description>
 * <param name="hFile" type="IN">Handle to the file</param>
 * <result>Error code:
 *	<ul>
 *		<li>ERR_OK: Succeeded flushing the file</li>
 *		<li>ERR_FAILED: Error occurred during file flush</li>
 *		<li>ERR_NOTIMPLEMENTED: File flush is not implemented</li>
 *		<li>ERR_NOT_SUPPORTED: File flush not available on the target</li>
 *	</ul>
 * </result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysFileFlush',`(RTS_HANDLE hFile)')

/**
 * <description>
 *	Interface function to check, if the filename has a prefix that marked that this file must be invisible outside the runtime system (e.g. in CmpFileTransfer).
 * </description>
 * <param name="pszFileName" type="IN">HPointer to the filename to check</param>
 * <result>Error code:
 *	<ul>
 *		<li>ERR_OK: Invisible file! Must be invisible outside the runtime system (e.g. in CmpFileTransfer)</li>
 *		<li>ERR_FAILED: No invisible file</li>
 *		<li>ERR_PARAMETER: Invalid parameter pszFileName</li>
 *	</ul>
 * </result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileIsInvisible',`(char *pszFileName)')

/**
 * <description>
 *	Set the size of the actual opened file.
 *  Used for increasing/decreasing the size of a file.
 *  The current fileoffset (filepointer) is not changed. 
 * </description>
 * <param name="hFile" type="IN">Handle to the file</param>
 * <param name="sSizeNew" type="IN">New size of the file, type: RTS_SIZE </param>
 * <result>Error code.</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysFileTruncate',`(RTS_HANDLE hFile, RTS_SIZE sSizeNew)')

/**
 * <description>
 * Returns the first configured path and a handle for further processing.
 * </description>
 * <param name="pszFilePath" type="OUT">File path</param>
 * <param name="nMaxFilePathLen" type="IN">Max size of pszFilePath</param>
 * <param name="pszPlaceholder" type="OUT">Name of placeholder</param>
 * <param name="nMaxPlaceholderLen" type="IN">Max size of pszPlaceholder</param>
 * <param name="pResult" type="OUT">Error code</param>
 * <result>Handle</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">A placeholder and its path are successfully found and returned</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter (pointer NULL or length 0)</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_END_OF_OBJECT">No entries found. The referenced buffers of pszFilePath and pszPlaceholder are left untouched.</errorcode>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SysFileGetFirstConfiguredPath',`(char *pszFilePath, RTS_I32 nMaxFilePathLen, char *pszPlaceholder, RTS_I32 nMaxPlaceholderLen, RTS_RESULT *pResult)')

/**
 * <description>
 * Returns the next configured path and a handle for further processing.
 * </description>
 * <param name="hPrevPath" type="IN">Handle from previous call</param>
 * <param name="pszFilePath" type="OUT">File path</param>
 * <param name="nMaxFilePathLen" type="IN">Max size of pszFilePath</param>
 * <param name="pszPlaceholder" type="OUT">Name of placeholder</param>
 * <param name="nMaxPlaceholderLen" type="IN">Max size of pszPlaceholder</param>
 * <param name="pResult" type="OUT">Error code</param>
 * <result>Handle</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">A placeholder and its path are successfully found and returned.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter (pointer NULL or length 0)</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_END_OF_OBJECT">No more entries found. The referenced buffers of pszFilePath and pszPlaceholder are left untouched.</errorcode>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SysFileGetNextConfiguredPath',`(RTS_HANDLE hPrevPath, char *pszFilePath, RTS_I32 nMaxFilePathLen, char *pszPlaceholder, RTS_I32 nMaxPlaceholderLen, RTS_RESULT *pResult)')

/**
 * <description>
 * Returns the next configured path and a handle for further processing.
 * </description>
 * <param name="hPrevPath" type="IN">Handle from previous call</param>
 * <param name="pszFilePath" type="OUT">File path</param>
 * <param name="nMaxFilePathLen" type="IN">Max size of pszFilePath</param>
 * <param name="pszPlaceholder" type="OUT">Name of placeholder</param>
 * <param name="nMaxPlaceholderLen" type="IN">Max size of pszPlaceholder</param>
 * <param name="nFlags" type="IN">See Flags for SysFileGetNextConfiguredPath2</param>
 * <param name="pResult" type="OUT">Error code</param>
 * <result>Handle</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">A placeholder and its path are successfully found and returned.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter (pointer NULL or length 0)</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_END_OF_OBJECT">No more entries found. The referenced buffers of pszFilePath and pszPlaceholder are left untouched.</errorcode>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SysFileGetNextConfiguredPath2',`(RTS_HANDLE hPrevPath, char *pszFilePath, RTS_I32 nMaxFilePathLen, char *pszPlaceholder, RTS_I32 nMaxPlaceholderLen, RTS_UI32 nFlags, RTS_RESULT *pResult)')

/**
 * <description>
 * Sets the standard path for all IEC file operations (IEC working directory). Reset with empty path.
 * </description>
 * <param name="pszPath" type="IN">Standard IEC file path</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileSetIecPath',`(char *pszPath)')

/**
 * <description>
 * Returns the plc logic prefix.
 * </description>
 * <result>plc logic prefix</result>
 */
DEF_ITF_API(`char *',`CDECL',`SysFileGetPlcLogicPrefix',`(void)')

/**
 * <description>
 * Prepends the plc logic prefix to name and ext in the resulting pathOut, makes sure the extension is there at the cost of the filename.
 * </description>
 * <param name="pszPathOut" type="OUT">Resulting file path</param>
 * <param name="ulPathOutSize" type="IN">Size of resulting file path</param>
 * <param name="pszSubDir" type="IN">Name of subdir (optional, only used when plc logic prefix is set)</param>
 * <param name="pszName" type="IN">Name of file</param>
 * <param name="pszExt" type="IN">>Extension of file</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFilePlcLogicPrefix',`(char *pszPathOut, RTS_SIZE ulPathOutSize, char *pszSubDir, char *pszName, const char *pszExt)')

/**
 * <description>
 * Check whether a given file and/or path is blacklisted
 * On a blacklisted file or path it is intended to deny all operations
 * NOTE: SysFile uses this blacklist to deny file access from IEC.
 * NOTE: Other components may use this blacklist too (currently CmpFileTransfer).
 * </description>
 * <param name="pszPath" type="IN">File and/or path to check</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">The checked file/path is blacklisted</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">The checked file/path not blacklisted.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">The file/path to check is empty or the pointer is NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">List is not initialized</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileIsBlacklisted',`(char *pszPath)')

/**
 * <description>
 * Add a given file and/or path to the blacklist
 * NOTE: SysFile uses this blacklist to deny file access from IEC.
 * NOTE: Other components may use this blacklist too (currently CmpFileTransfer).
 * </description>
 * <param name="pszPath" type="IN">File and/or path to add</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">The file/path is successfully added to the list.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">Not enough memory to add the file/path</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOBUFFER">Copy failure, file/path is to long</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">The file/path to add is empty or the pointer is NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">List is not initialized</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysFileAddToBlacklist',`(char *pszPath)')


#ifdef __cplusplus
}
#endif
