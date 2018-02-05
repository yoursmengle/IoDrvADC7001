/**
 * <interfacename>SysDir</interfacename>
 * <description> 
 *	<p>The SysDir interface is projected to handle all system dependant directory operations.
 *	If there is no filesystem on the target, the interface functions ERR_NOTIMPLEMENTED.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysDir')

#include "CmpItf.h"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Windows CE: Create a "Dummy.txt" file in directories.
 *	Default value is 0 (no "Dummy.txt" file in directories).
 * </description>
 */	
#define SYSDIR_WINCE_DUMMYTXT_IN_DIRS					"WinCE.DummyTxtInDirs" 
#ifndef SYSDIR_WINCE_DUMMYTXT_IN_DIRS_DEFAULT
	#define SYSDIR_WINCE_DUMMYTXT_IN_DIRS_DEFAULT				0
#endif

/**
 * <category>Directory file time</category>
 * <element name="ulCreation" type="IN">Creation date of the file</element>
 * <element name="ulLastAccess" type="IN">Date of last access to the file</element>
 * <element name="ulLastModification" type="IN">Date of last modification to the file</element>
 */
typedef struct
{
	RTS_UI32 ulCreation;
	RTS_UI32 ulLastAccess;
	RTS_UI32 ulLastModification;
} DirFileTime;

/**
 * <category>Directory info entry</category>
 * <description>
 *	This structure contains the description of one directory entry
 * </description>
 * <element name="dft" type="IN">Directory dates</element>
 * <element name="ulSize" type="IN">Size of the directory</element>
 * <element name="ulFlags" type="IN">Flag of a directory</element>
 */
typedef struct
{
	DirFileTime dft;
	RTS_SIZE ulSize;
	RTS_UI32 ulFlags;
} DirInfo;

/**
 * <category>Directory info flags</category>
 * <element name="DF_FILE" type="IN">Entry is a file</element>
 * <element name="DF_DIRECTORY" type="IN">Entry is a directory</element>
 */
#define DF_FILE			0x00000000
#define DF_DIRECTORY	0x00000002


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Close an open directory
 * :return: Returns the runtime system error code (see CmpErrors_Itf.library)
 */
typedef struct tagsysdirclose_struct
{
	RTS_IEC_HANDLE hDir;				/* VAR_INPUT */	/* Handle to directory opened with SysDirOpen */
	RTS_IEC_RESULT SysDirClose;			/* VAR_OUTPUT */	
} sysdirclose_struct;

DEF_API(`void',`CDECL',`sysdirclose',`(sysdirclose_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x7985F4ED),0x03050C00)

/**
 * Copies the contents of szSourceDir to szDestDir.
 * Nonexisting destination path will be created.
 * Depending of the parameters, all subdirectories and its content will be copied too, and existing files will be overwritten.
 * NOTE: Empty direcories will be copied if xRecursive is TRUE.
 * :return: Returns the runtime system error code (see CmpErrors_Itf.library)
 */
typedef struct tagsysdircopy_struct
{
	RTS_IEC_STRING *szDestDir;			/* VAR_INPUT */	/* Name of destination directory */
	RTS_IEC_STRING *szSourceDir;		/* VAR_INPUT */	/* Name of source directory */
	RTS_IEC_BOOL xRecursive;			/* VAR_INPUT */	/* TRUE: all subdirectories and their contents are copied, FALSE: subdirectories are omitted */
	RTS_IEC_BOOL xOverwrite;			/* VAR_INPUT */	/* TRUE: existing files are overwritten, FALSE: existing files are left untouched */
	RTS_IEC_RESULT SysDirCopy;			/* VAR_OUTPUT */	
} sysdircopy_struct;

DEF_API(`void',`CDECL',`sysdircopy',`(sysdircopy_struct *p)',1,0xDCC4B146,0x03050C00)

/**
 * Creates a new directory with the specified name
 * :return: Returns the runtime system error code (see CmpErrors_Itf.library)
 */
typedef struct tagsysdircreate_struct
{
	RTS_IEC_STRING *szDir;				/* VAR_INPUT */	/* Name of the directory */
	RTS_IEC_RESULT SysDirCreate;		/* VAR_OUTPUT */	
} sysdircreate_struct;

DEF_API(`void',`CDECL',`sysdircreate',`(sysdircreate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC775A9FA),0x03050C00)

/**
 * Creates a new directory with the specified name.
 * If xRecursive is set, a full path is created, i.e. all missing parent directories are created too.
 * :return: Returns the runtime system error code (see CmpErrors_Itf.library)
 */
typedef struct tagsysdircreate2_struct
{
	RTS_IEC_STRING *szDir;				/* VAR_INPUT */	/* Name of the directory */
	RTS_IEC_BOOL xRecursive;			/* VAR_INPUT */	/* Create a full path */
	RTS_IEC_RESULT SysDirCreate2;		/* VAR_OUTPUT */	
} sysdircreate2_struct;

DEF_API(`void',`CDECL',`sysdircreate2',`(sysdircreate2_struct *p)',1,0x03802B43,0x03050C00)

/**
 * Deletes a directory with the specified name
 * :return: Returns the runtime system error code (see CmpErrors_Itf.library)
 */
typedef struct tagsysdirdelete_struct
{
	RTS_IEC_STRING *szDir;				/* VAR_INPUT */	/* Name of directory */
	RTS_IEC_RESULT SysDirDelete;		/* VAR_OUTPUT */	
} sysdirdelete_struct;

DEF_API(`void',`CDECL',`sysdirdelete',`(sysdirdelete_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x3E032B8B),0x03050C00)

/**
 * Deletes a directory with the specified name
 *
 * If xRecursive is set, a whole folder tree can be deleted, i.e. all subfolders and files are deleted.
 * If xRecursive and xKeepDir are set, the folder is kept but its contents is deleted.
 * :return: Returns the runtime system error code (see CmpErrors_Itf.library)
 */
typedef struct tagsysdirdelete2_struct
{
	RTS_IEC_STRING *szDir;				/* VAR_INPUT */	/* Name of directory */
	RTS_IEC_BOOL xRecursive;			/* VAR_INPUT */	/* Delete a whole folder tree */
	RTS_IEC_BOOL xKeepDir;				/* VAR_INPUT */	/* Keep the starting folder */
	RTS_IEC_RESULT SysDirDelete2;		/* VAR_OUTPUT */	
} sysdirdelete2_struct;

DEF_API(`void',`CDECL',`sysdirdelete2',`(sysdirdelete2_struct *p)',1,0xB8EF3C3D,0x03050C00)

/**
 * Get current working directory for IEC file access
 * :return: Returns the runtime system error code (see CmpErrors_Itf.library)
 */
typedef struct tagsysdirgetcurrent_struct
{
	RTS_IEC_STRING *szDir;				/* VAR_INPUT */	/* OUT_PARAMETER: Name of current directory */
	RTS_IEC_DINT diMaxDirLen;			/* VAR_INPUT */	/* Max lenght of directory buffer */
	RTS_IEC_RESULT SysDirGetCurrent;	/* VAR_OUTPUT */	
} sysdirgetcurrent_struct;

DEF_API(`void',`CDECL',`sysdirgetcurrent',`(sysdirgetcurrent_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0376B53C),0x03050C00)

/**
 * Opens a specified directory and returns a handle and the first directory entry
 * :return: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysdiropen_struct
{
	RTS_IEC_STRING *szDir;				/* VAR_INPUT */	/* Directory entry as string

 .. note:: Empty string ('') is the request for the current working directory. */
	RTS_IEC_STRING *szDirEntry;			/* VAR_INPUT */	/* OUT_PARAMETER: Directory entry as string */
	RTS_IEC_DINT diMaxDirEntry;			/* VAR_INPUT */	/* OUT_PARAMETER: Max number of bytes to write in pszDirEntry */
	DirInfo *pDirInfo;					/* VAR_INPUT */	/* OUT_PARAMETER: Directory information */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* OUT_PARAMETER: Pointer to runtime system error code (see CmpErrors.library) */
	RTS_IEC_HANDLE SysDirOpen;			/* VAR_OUTPUT */	
} sysdiropen_struct;

DEF_API(`void',`CDECL',`sysdiropen',`(sysdiropen_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x05CA15A4),0x03050C00)

/**
 * Read next directory entry. Writes the entry in pszDirEntry.
 * :return: Returns the runtime system error code (see CmpErrors.library)
 *
 *		+ ERR_OK: Entry could be read
 *		+ ERR_END_OF_OBJECT: If end of directory list was reached
 *		+ ERR_PARAMETER: If one of the parameters is invalid
 *		+ ERR_BUFFERSIZE: If iMaxDirEntry is too short to get the complete directory entry string
 *
 * .. note:: Typically after error ``ERR_BUFFERSIZE``, the dir-handle is set to the next entry, so this entry will be missed!
 */
typedef struct tagsysdirread_struct
{
	RTS_IEC_HANDLE hDir;				/* VAR_INPUT */	/* Handle to directory opened with SysDirOpen */
	RTS_IEC_STRING *szDirEntry;			/* VAR_INPUT */	/* OUT_PARAMETER: Directory entry as string */
	RTS_IEC_DINT diMaxDirEntry;			/* VAR_INPUT */	/* OUT_PARAMETER: Max number of bytes to write in pszDirEntry */
	DirInfo *pDirInfo;					/* VAR_INPUT */	/* OUT_PARAMETER: Directory information
 NOTE: Can be 0 (so only directory name is provided in pszDirEntry) */
	RTS_IEC_RESULT SysDirRead;			/* VAR_OUTPUT */	
} sysdirread_struct;

DEF_API(`void',`CDECL',`sysdirread',`(sysdirread_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCF257171),0x03050C00)

/**
 * Rename directory
 * :return: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysdirrename_struct
{
	RTS_IEC_STRING *szOldDirName;		/* VAR_INPUT */	/* Name of existing directory */
	RTS_IEC_STRING *szNewDirName;		/* VAR_INPUT */	/* Name of new directory */
	RTS_IEC_RESULT SysDirRename;		/* VAR_OUTPUT */	
} sysdirrename_struct;

DEF_API(`void',`CDECL',`sysdirrename',`(sysdirrename_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA2EF5E53),0x03050C00)

/**
 * Set current working directory on the target. In this directory all following file function are operated.
 * This setting applies to file access from IEC only. An empty string resets the working directory to its default.
 * This function should not be used in parallel to any other file operation from IEC. 
 * :return: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysdirsetcurrent_struct
{
	RTS_IEC_STRING *szDir;				/* VAR_INPUT */	/* Name of current directory */
	RTS_IEC_RESULT SysDirSetCurrent;	/* VAR_OUTPUT */	
} sysdirsetcurrent_struct;

DEF_API(`void',`CDECL',`sysdirsetcurrent',`(sysdirsetcurrent_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x92FA36CD),0x03050C00)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysDirOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysDirOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>Opens a specified directory and returns a handle and the first directory entry</description>
 * <param name="pszDir" type="IN">Name of directory.
 * IMPLEMENTATION NOTE: Empty string ("") is the request for the current working directory.</param>
 * <param name="pszDirEntry" type="OUT">Optional: Directory entry as string. Can be NULL.</param>
 * <param name="iMaxDirEntry" type="IN">Optional: Max number of bytes to write in pszDirEntry</param>
 * <param name="pDirInfo" type="OUT">Directory information</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Directory can be opened and a directory info can be retrieved</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">Directory cannot be opened. An invalid handle is returned.</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_END_OF_OBJECT">Directory can be opened, but _no_ pszDirEntry can be retrieved (direcory is empty or end reached)!
 *		NOTE:
 *		A valid handle is returned with this error and so the directory must be closed after usage!
 * </errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OPERATION_DENIED">Directory cannot be opened because access was denied. An invalid handle is returned.</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">One of the parameters is invalid. An invalid handle is returned.</errorcode>
 * <result>RTS_HANDLE on directory</result>
 */
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysDirOpen',`(char *pszDir, char *pszDirEntry, int iMaxDirEntry, DirInfo *pDirInfo, RTS_RESULT *pResult)')

/**
 * <description>Opens a specified directory and returns a handle and the first directory entry. No standard path will be added.
 *	IMPLEMENTATION NOTE:
 *	This interface function is implemented operating system dependant! Optimizations can be done here.</description>
 * <param name="pszDir" type="IN">Name of directory.
 * IMPLEMENTATION NOTE: Empty string ("") is the request for the current working directory.</param>
 * <param name="pszDirEntry" type="OUT">Optional: Directory entry as string. Can be NULL.</param>
 * <param name="iMaxDirEntry" type="IN">Optional: Max number of bytes to write in pszDirEntry</param>
 * <param name="pDirInfo" type="OUT">Directory information</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Directory can be opened and a directory info can be retrieved</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">Directory cannot be opened. An invalid handle is returned.</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_END_OF_OBJECT">Directory can be opened, but _no_ pszDirEntry can be retrieved (direcory is empty or end reached)!
 *		NOTE:
 *		A valid handle is returned with this error and so the directory must be closed after usage!
 * </errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">One of the parameters is invalid. An invalid handle is returned.</errorcode>
 * <result>RTS_HANDLE on directory</result>
 */
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysDirOpen_',`(char *pszDir, char *pszDirEntry, int iMaxDirEntry, DirInfo *pDirInfo, RTS_RESULT *pResult)')

/**
 * <description>Close an open directory</description>
 * <param name="hDir" type="IN">Handle to directory opened with SysDirOpen or with SysDirOpen_</param>
 * <result>error code</result>
 */
DEF_DELETEITF_API(`RTS_RESULT',`CDECL',`SysDirClose',`(RTS_HANDLE hDir)')

/**
 * <description>Close an open directory.
 *	IMPLEMENTATION NOTE:
 *	This interface function is implemented operating system dependant! Optimizations can be done here.</description>
 * <param name="hDir" type="IN">Handle to directory opened with SysDirOpen</param>
 * <result>error code</result>
 */
DEF_DELETEITF_API(`RTS_RESULT',`CDECL',`SysDirClose_',`(RTS_HANDLE hDir)')

/**
 * <description>Read next directory entry. Writes the entry in pszDirEntry.</description>
 * <param name="hDir" type="IN">Handle to directory opened with SysDirOpen</param>
 * <param name="pszDirEntry" type="OUT">Directory entry as string</param>
 * <param name="iMaxDirEntry" type="OUT">Max number of bytes to write in pszDirEntry</param>
 * <param name="pDirInfo" type="OUT">Pointer to directory information.
 *		IMPLEMENTATION NOTE:
 *		Can be NULL (so only directory name is provided in pszDirEntry) </param>
 * <result>
 *   <ul>
 *     <li>ERR_OK: The directory string contains the next directory entry and is referenced by "pszDirEntry", "pDirInfo" references the related directory information string.</li>
 *     <li>ERR_END_OF_OBJECT: If end of directory list was reached, the "pszDirEntry" referenced buffer stays empty.</li>
 *     <li>ERR_PARAMETER: If one of the parameters is invalid, the function returns without updating the directory iterator.</li>
 *     <li>ERR_BUFFERSIZE: If iMaxDirEntry is too short to get the complete directory entry string but not null.
 *			ATTENTION: Typically if this error occurs, the "pszDirEntry" contains the string to the incomplete next entry, the iterator is updated!</li>
 *   </ul>
 * </result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysDirRead',`(RTS_HANDLE hDir, char *pszDirEntry, int iMaxDirEntry, DirInfo *pDirInfo)')

/**
 * <description>Read next directory entry. Writes the entry in pszDirEntry.
 *	IMPLEMENTATION NOTE:
 *	This interface function is implemented operating system dependant! Optimizations can be done here.</description>
 * <param name="hDir" type="IN">Handle to directory opened with SysDirOpen</param>
 * <param name="pszDirEntry" type="OUT">Directory entry as string</param>
 * <param name="iMaxDirEntry" type="OUT">Max number of bytes to write in pszDirEntry</param>
 * <param name="pDirInfo" type="OUT">Pointer to directory information.
 *		IMPLEMENTATION NOTE:
 *		Can be NULL (so only directory name is provided in pszDirEntry) </param>
 * <result>
 *   <ul>
 *     <li>ERR_OK: The directory string contains the next directory entry and is referenced by "pszDirEntry", "pDirInfo" references the related directory information string.</li>
 *     <li>ERR_END_OF_OBJECT: If end of directory list was reached, the "pszDirEntry" referenced buffer stays empty.</li>
 *     <li>ERR_PARAMETER: If one of the parameters is invalid, the function returns without updating the directory iterator.</li>
 *     <li>ERR_BUFFERSIZE: If iMaxDirEntry is too short to get the complete directory entry string but not null.
 *			ATTENTION: Typically if this error occurs, the "pszDirEntry" contains the string to the incomplete next entry, the iterator is updated!</li>
 *   </ul>
 * </result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysDirRead_',`(RTS_HANDLE hDir, char *pszDirEntry, int iMaxDirEntry, DirInfo *pDirInfo)')

/**
 * <description>Creates a new directory with the specified name</description>
 * <param name="pszDir" type="IN">Name of directory</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysDirCreate',`(char *pszDir)')

/**
 * <description>Creates a new directory with the specified name.
 * If bRecursive is set, a full path is created, i.e. all missing parent directories are created too.</description>
 * <param name="pszDir" type="IN">Name of directory</param>
 * <param name="bRecursive" type="IN">Create a full path</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysDirCreate2',`(char *pszDir, RTS_BOOL bRecursive)')

/**
 * <description>Creates a new directory with the specified name. No standard path will be added.
 *	IMPLEMENTATION NOTE:
 *	This interface function is implemented operating system dependant! Optimizations can be done here.</description>
 * <param name="pszDir" type="IN">Name of directory</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Directory was created successfully</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">Directory couldn't be created for various reasons other than the following two</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_OBJECT">The path to the directory to be created does not exist</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_DUPLICATE">The directory already exists</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysDirCreate_',`(char *pszDir)')

/**
 * <description>Deletes a directory with the specified name</description>
 * <param name="pszDir" type="IN">Name of directory</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysDirDelete',`(char *pszDir)')

/**
 * <description>Deletes a directory with the specified name
 * If bRecursive is set, a whole folder tree can be deleted, i.e. all subfolders and files are deleted.
 * If bRecursive and bKeepDir are set, the folder is kept but its contents is deleted.</description>
 * <param name="pszDir" type="IN">Name of directory</param>
 * <param name="bRecursive" type="IN">Delete a whole folder tree</param>
 * <param name="bKeepDir" type="IN">Keep the starting folder</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysDirDelete2',`(char *pszDir, RTS_BOOL bRecursive, RTS_BOOL bKeepDir)')

/**
 * <description>Deletes a directory with the specified name. No standard path will be added.
 *	IMPLEMENTATION NOTE:
 *	This interface function is implemented operating system dependant! Optimizations can be done here.</description>
 * <param name="pszDir" type="IN">Name of directory</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysDirDelete_',`(char *pszDir)')

/**
 * <description>Rename directory</description>
 * <param name="pszOldDir" type="IN">Name of existing directory</param>
 * <param name="pszNewDir" type="IN">New name</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysDirRename',`(char *pszOldDir, char *pszNewDir)')

/**
 * <description>Rename directory. No standard path will be added.
 *	IMPLEMENTATION NOTE:
 *	This interface function is implemented operating system dependant! Optimizations can be done here.</description>
 * <param name="pszOldDir" type="IN">Name of existing directory</param>
 * <param name="pszNewDir" type="IN">New name</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysDirRename_',`(char *pszOldDir, char *pszNewDir)')

/**
 * <description>Get current working directory. If no FilePath is specified pzDir is empty (default).
 * To obtain the working directory of the underlying file system use SysDirGetCurrent_.
 * </description>
 * <param name="pszDir" type="OUT">Name of current directory</param>
 * <param name="iMaxDirLen" type="IN">Max lenght of directory buffer</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysDirGetCurrent',`(char *pszDir, int iMaxDirLen)')

/**
 * <description>Get current working directory of the underlying file system. No standard path will be added.
 *	IMPLEMENTATION NOTE:
 *	This interface function is implemented operating system dependant!</description>
 * <param name="pszDir" type="OUT">Name of current directory</param>
 * <param name="iMaxDirLen" type="IN">Max lenght of directory buffer</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysDirGetCurrent_',`(char *pszDir, int iMaxDirLen)')

/**
 * <description> Former set current working directory.
 * This function has been deprecated. It returns just ERR_NOTIMPLEMENTED.
 * To really change the working directory of the whole runtime system use SysDirSetCurrent_.
 * </description>
 * <param name="pszDir" type="IN">not used</param>
 * <result>ERR_NOTIMPLEMENTED</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysDirSetCurrent',`(char *pszDir)')

/**
 * <description> Set current working directory of the underlying file system of the whole runtime system.
 * No standard path will be added. It is not recommended to use this function!
 * ATTENTION: Just in case it is strongly recommended to save the path with SysDirGetCurrent_ prior to this
 * call and restore the path as soon as possible. Otherwise the whole runtime system may not work any more!
 * ATTENTION: Reset Origin does not affect this setting. The runtime system has to be restarted!
 *	IMPLEMENTATION NOTE:
 *	This interface function is implemented operating system dependant!</description>
 * <param name="pszDir" type="IN">Name of current directory</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysDirSetCurrent_',`(char *pszDir)')

/**
 * <description> Copies the contents of pszSourceDir to pszDestDir.
 * Depending of the parameters, all subdirectories and its content will be copied too, and existing files will be overwritten.
 * NOTE: Empty direcories will be copied if bRecursive is TRUE.
 * </description>
 * <param name="pszDestDir" type="IN">Name of destination directory</param>
 * <param name="pszSourceDir" type="IN">Name of source directory</param>
 * <param name="bRecursive" type="IN">TRUE: all subdirectories and their contents are copied, FALSE: subdirectories are omitted</param>
 * <param name="bOverwrite" type="IN">TRUE: existing files are overwritten, FALSE: existing files are left untouched</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">The contents of the source direcory was successfully copied to the destination direcory</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_OBJECT">There were no files to copy, the destination directory is nevertheless created if need be</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OPERATION_DENIED">Source or destination direcory is not accessible</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">System error</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysDirCopy',`(char *pszDestDir, char *pszSourceDir, RTS_BOOL bRecursive, RTS_BOOL bOverwrite)')


#ifdef __cplusplus
}
#endif
