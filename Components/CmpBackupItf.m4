/**
 * <interfacename>CmpBackup</interfacename>
 * <description> 
 *	Interface for the backup component. This component is optional, and intended to serve a backup and restore feature.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpBackup')

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to enable/diable backup & restore for application related data:
 *	1: enable
 *	0: disable
 * </description>
 */
#define BACKUPKEY_INT_CAPABILITIES_APPLICATION					"Capabilities.Application"
#ifndef BACKUPVALUE_INT_CAPABILITIES_APPLICATION_DEFAULT
	#define BACKUPVALUE_INT_CAPABILITIES_APPLICATION_DEFAULT	1
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to enable/diable backup & restore for system related data:
 *	1: enable
 *	0: disable
 * </description>
 */
#define BACKUPKEY_INT_CAPABILITIES_SYSTEM						"Capabilities.System"
#ifndef BACKUPVALUE_INT_CAPABILITIES_SYSTEM_DEFAULT
	#define BACKUPVALUE_INT_CAPABILITIES_SYSTEM_DEFAULT			0
#endif

/**
 * <category>Online services</category>
 * <Description>
 * Online Service Backup. A service sequence to initiate a backup
 * </Description>
 *
 * <service name="SRV_BACKUP_CAPABILITIES">
 *	<Request>
 *		<tag name="TAGBACKUP_COMMAND" required="mandatory">[RTS_UI32]: CMDBACKUP_NORMAL</tag>
 *	</Request>
 *	<Response>
 *		<tag name="TAGBACKUP_STATUS" required="mandatory">[RTS_UI32]: Bitvector: SRVBACKUP_BIT_APPLICATION, SRVBACKUP_BIT_SYSTEM, all other bits are reserved, see category "Online service bits" for details.</tag>
 *	</Response>
 * </service>
 *
 * <service name="SRV_BACKUP_INFO">
 *	<Request>
 *		<tag name="TAGBACKUP_COMMAND" required="mandatory">[RTS_UI32]: CMDBACKUP_START, CMDBACKUP_CONTINUE</tag>
 *		<tag name="TAGBACKUP_HANDLE" required="optional">[RTS_HANDLE] with CMDBACKUP_CONTINUE</tag>
 *	</Request>
 *	<Response>
 *		<tag name="TAGBACKUP_GLOBAL_BLOCK" required="mandatory">Top level tag</tag>
 *			<tag name="TAGBACKUP_STATUS" required="mandatory">[RTS_UI32]</tag>
 *		<tag name="TAGBACKUP_DEVICE_INFO_BLOCK" required="mandatory">Top level tag</tag>
 *			<tag name="TAGBACKUP_STATUS" required="mandatory">[RTS_UI32]</tag>
 *			<tag name="TAGBACKUP_TARGET_IDENT" required="mandatory">[RTS_UI32, RTS_UI32, RTS_UI32] see TargetIdent in CmpDeviceItf for details.</tag>
 *			<tag name="TAGBACKUP_FILE_ENTRY" required="optional">[SrvBackupFileEntry] may appear multiple times</tag>
 *			<tag name="TAGBACKUP_FILE_ENTRY" required="optional">[SrvBackupFileEntry] may appear multiple times</tag>
 *		<tag name="TAGBACKUP_APPLICATION_INFO_BLOCK required="optional">Top level tag, may appear multiple times</tag>
 *			<tag name="TAGBACKUP_STATUS" required="mandatory">[RTS_UI32]</tag>
 *			<tag name="TAGBACKUP_NAME" required="mandatory">[char[]]</tag>
 *			<tag name="TAGBACKUP_FILE_ENTRY" required="optional">[SrvBackupFileEntry] may appear multiple times</tag>
 *			<tag name="TAGBACKUP_FILE_ENTRY" required="optional">[SrvBackupFileEntry] may appear multiple times</tag>
 *		<tag name="TAG_CMPBACKUP_INFO_BLOCK" required="optional">Top level tag, may appear multiple times</tag>
 *			<tag name="TAGBACKUP_STATUS" required="mandatory">[RTS_UI32]</tag>
 *			<tag name="TAGBACKUP_NAME" required="mandatory">[char[]]</tag>
 *			<tag name="TAGBACKUP_FILE_ENTRY" required="optional">[SrvBackupFileEntry] may appear multiple times</tag>
 *			<tag name="TAGBACKUP_FILE_ENTRY" required="optional">[SrvBackupFileEntry] may appear multiple times</tag>
 *		<tag name="TAGBACKUP_CMP_INFO_BLOCK" required="optional">Top level tag, may appear multiple times</tag>
 *			...
 *		<tag name="TAGBACKUP_APPLICATION_INFO_BLOCK required="optional">Top level tag, may appear multiple times</tag>
 *			...
 *		<tag name="TAGBACKUP_HANDLE" required="optional">[RTS_HANDLE] for next CMDBACKUP_CONTINUE</tag>
 *	</Response>
 * </service>
 *
 * <service name="SRV_BACKUP_START">
 *	<Request>
 *		<tag name="TAGBACKUP_COMMAND" required="mandatory">[RTS_UI32]</tag>
 *	</Request>
 *	<Response>
 *		<tag name="TAGBACKUP_STATUS" required="mandatory">[RTS_UI32]</tag>
 *	</Response>
 * </service>
 *
 * SRVFT_UPLOAD (file transfer services are described in CmpFileTransferItf.m4)
 * ...
 *
 * <service name="SRV_BACKUP_END">
 *	<Request>
 *		<tag name="TAGBACKUP_COMMAND" required="mandatory">[RTS_UI32]: CMDBACKUP_NORMAL, CMDBACKUP_ABORT</tag>
 *	</Request>
 *	<Response>
 *		<tag name="TAGBACKUP_STATUS" required="mandatory">[RTS_UI32]</tag>
 *	</Response>
 * </service>
 */

/**
 * <category>Online services</category>
 * <Description>
 * Online Service Restore. A service sequence to initiate a restore.
 * </Description>
 *
 * <service name="SRV_RESTORE_REQ">
 *	<Request>
 *		<tag name="TAGBACKUP_GLOBAL_BLOCK" required="mandatory">Top level tag</tag>
 *			<tag name="TAGBACKUP_COMMAND" required="mandatory">[RTS_UI32]: CMDBACKUP_START, CMDBACKUP_CONTINUE</tag>
 *		<tag name="TAGBACKUP_DEVICE_INFO_BLOCK" required="mandatory">Top level tag</tag>
 *			<tag name="TAGBACKUP_STATUS" required="mandatory">[RTS_UI32]</tag>
 *			<tag name="TAGBACKUP_TARGET_IDENT" required="mandatory">[RTS_UI32, RTS_UI32, RTS_UI32] see TargetIdent in CmpDeviceItf for details.</tag>
 *			<tag name="TAGBACKUP_FILE_ENTRY" required="optional">[SrvBackupFileEntry] may appear multiple times</tag>
 *			<tag name="TAGBACKUP_FILE_ENTRY" required="optional">[SrvBackupFileEntry] may appear multiple times</tag>
 *		<tag name="TAGBACKUP_APPLICATION_INFO_BLOCK required="optional">Top level tag, may appear multiple times</tag>
 *			<tag name="TAGBACKUP_STATUS" required="mandatory">[RTS_UI32]</tag>
 *			<tag name="TAGBACKUP_NAME" required="mandatory">[char[]]</tag>
 *			<tag name="TAGBACKUP_FILE_ENTRY" required="optional">[SrvBackupFileEntry] may appear multiple times</tag>
 *			<tag name="TAGBACKUP_FILE_ENTRY" required="optional">[SrvBackupFileEntry] may appear multiple times</tag>
 *		<tag name="TAGBACKUP_CMP_INFO_BLOCK" required="optional">Top level tag, may appear multiple times</tag>
 *			<tag name="TAGBACKUP_STATUS" required="mandatory">[RTS_UI32]</tag>
 *			<tag name="TAGBACKUP_NAME" required="mandatory">[char[]]</tag>
 *			<tag name="TAGBACKUP_FILE_ENTRY" required="optional">[SrvBackupFileEntry] may appear multiple times</tag>
 *			<tag name="TAGBACKUP_FILE_ENTRY" required="optional">[SrvBackupFileEntry] may appear multiple times</tag>
 *		<tag name="TAGBACKUP_CMP_INFO_BLOCK" required="optional">Top level tag, may appear multiple times</tag>
 *			...
 *		<tag name="TAGBACKUP_APPLICATION_INFO_BLOCK required="optional">Top level tag, may appear multiple times</tag>
 *			...
 *	</Request>
 *	<Response>
 *		<tag name="TAGBACKUP_STATUS" required="mandatory">[RTS_UI32]</tag>
 *	</Response>
 * </service>
 * 
 * <service name="SRV_RESTORE_START">
 *	<Request>
 *			<tag name="TAGBACKUP_COMMAND" required="mandatory">[RTS_UI32]: CMDBACKUP_NORMAL, CMDBACKUP_FORCE</tag>
 *	<Response>
 *		<tag name="TAGBACKUP_STATUS" required="mandatory">[RTS_UI32]</tag>
 *	</Response>
 * </service>
 *
 * SRVFT_DOWNLOAD (file transfer services are described in CmpFileTransferItf.m4)
 * ...
 *
 * <service name="SRV_RESTORE _END">
 *	<Request>
 *		<tag name="TAGBACKUP_COMMAND" required="mandatory">[RTS_UI32]: CMDBACKUP_NORMAL, CMDBACKUP_ABORT</tag>
 *	</Request>
 *	<Response>
 *		<tag name="TAGBACKUP_STATUS" required="mandatory">[RTS_UI32]</tag>
 *	</Response>
 * </service>
 */

/**
 * <category>Online services</category>
 * <description>
 * </description>
 */
#define SRV_BACKUP_CAPABILITIES				 1
#define SRV_BACKUP_INFO						 2
#define SRV_BACKUP_START					 3
#define SRV_BACKUP_END						 4

#define SRV_RESTORE_REQ						 5
#define SRV_RESTORE_START					 6
#define SRV_RESTORE_END						 7

/**
 * <category>Online service tags</category>
 * <description>
 * </description>
 */
#define TAGBACKUP_GLOBAL_BLOCK				14+128

#define TAGBACKUP_COMMAND					15
#define TAGBACKUP_STATUS					16

#define TAGBACKUP_DEVICE_INFO_BLOCK			17+128
#define TAGBACKUP_APPLICATION_INFO_BLOCK	18+128
#define TAGBACKUP_CMP_INFO_BLOCK			19+128

#define TAGBACKUP_TARGET_IDENT				20
#define TAGBACKUP_FILE_ENTRY				21
#define TAGBACKUP_NAME						22
#define TAGBACKUP_HANDLE					23

/**
 * <category>Online service structs</category>
 * <description>
 * </description>
 */
typedef struct
{
	RTS_UI32 size; /* size of file */
	RTS_UI32 flags; /* Bitvector: See category "Register file flags" */
	RTS_UI32 pathlen; /* length of path */
	/*char path[]; complete file path */
} SrvBackupFileEntry;

/**
 * <category>Online service commands</category>
 * <description>
 * </description>
 */
typedef enum {
	CMDBACKUP_NORMAL,
	CMDBACKUP_START,
	CMDBACKUP_CONTINUE,
	CMDBACKUP_ABORT,
	CMDBACKUP_FORCE
} BackupServiceCommands;

/**
 * <category>Online service bits</category>
 * <description>
 * </description>
 */
#define SRVBACKUP_BIT_NONE 				0x00
#define SRVBACKUP_BIT_APPLICATION 		0x01
#define SRVBACKUP_BIT_SYSTEM			0x02

#define IsApplication(flags)			((flags & SRVBACKUP_BIT_APPLICATION) != 0)
#define IsSystem(flags)  				((flags & SRVBACKUP_BIT_SYSTEM) != 0)

/**
 * <category>Register file flags</category>
 * Only files that can be omitted are optional. Files that require the runtime to be in STOP shall set this flag.
 * <description>
 *	
 * </description>
 */
#define BAK_BIT_OPTIONAL				0x00
#define BAK_BIT_MANDATORY				0x01
#define BAK_BIT_REQUIRES_STOP			0x02

#define IsMandatory(flags)				((flags & BAK_BIT_MANDATORY) != 0)
#define IsOptional(flags)				((flags & BAK_BIT_MANDATORY) == 0)
#define RequiresStop(flags)				((flags & BAK_BIT_REQUIRES_STOP) != 0)

/**
 * <category>Backup mode flags</category>
 * <description>
 *	These flags determine what kind of backup or restore is desired (application, system or both), how optional files should be handled, and if the function will wait to finish.
 * </description>
 */
#define BAK_MODE_BIT_APPLICATION 		SRVBACKUP_BIT_APPLICATION
#define BAK_MODE_BIT_SYSTEM 			SRVBACKUP_BIT_SYSTEM
#define BAK_MODE_BIT_OMIT_OPTIONALS		0x00000010
#define BAK_MODE_BIT_SYNC				0x00001000

#define OmitOptionals(flags)			((flags & BAK_MODE_BIT_OMIT_OPTIONALS) != 0)
#define IsSynchronCall(flags)			((flags & BAK_MODE_BIT_SYNC) != 0)


/**
 * <category>Event parameter</category>
 * <description>
 *	Passes the online service requests to all registered consumers
 * </description>
 * <element name="usService" type="IN">See category "Online services" for details.</element>
 * <element name="ulCommand" type="IN">See category "Online service commands" for details.</element>
 */
typedef struct
{
	RTS_UI16 usService;
	RTS_UI32 ulCommand;
} EVTPARAM_CmpBackup;
#define EVTPARAMID_CmpBackup		0x0001
#define EVTVERSION_CmpBackup		0x0001

/**
 * <category>Events</category>
 * <description>Event is sent at start and completion of backup or restore process</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpBackup</param>
 */
#define EVT_Backup					MAKE_EVENTID(EVTCLASS_INFO, 1)


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Set the status for the backup request</description>
 * <param name="cmpId" type="IN">Id of component</param>
 * <param name="ulStatus" type="IN">Status</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK"></errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER"></errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED"></errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BakSetStatus',`(CMPID cmpId, RTS_UI32 ulStatus)')

/**
 * <description>Registers a file from a component to be in the backup file list</description>
 * <param name="cmpId" type="IN">Id of component</param>
 * <param name="pszFilePath" type="IN">Given file path</param>
 * <param name="ulFlags" type="IN">Flags. See category "Register file flags" for details.</param>
 * <param name="ulFileSize" type="IN">File size. May be set to 0, in that case CmpBackup checks the file size. If unsuccessfull the entry will be discarded, i.e. not registered (ERR_NO_OBJECT).</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">File was successfully registered</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER"></errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED"></errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOBUFFER"></errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">File size check failed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_DUPLICATE">The file is already registered</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BakRegisterFile',`(CMPID cmpId, char *pszFilePath, RTS_UI32 ulFlags, RTS_SIZE ulFileSize)')

/**
 * <description>Unregisters a file from a component to be removed from the backup file list</description>
 * <param name="cmpId" type="IN">Id of component</param>
 * <param name="pszFilePath" type="IN">Given file path</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">File was successfully unregistered</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER"></errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED"></errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">File was not registered</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BakUnregisterFile',`(CMPID cmpId, char *pszFilePath)')


/**
 * <description>Returns the backup capabilities</description>
 * <result>Capability flags (see category "Online service bits")</result>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`BakGetCapabilities',`(void)')

/**
 * <description>
 *	Triggers the complete backup process. Function returns immediately (asynchronous).
 *	Start and completion can be optionally monitored via events.
 *	With the sync bit set, the function will wait to finish the operation and returns success or failure (synchronous).
 * </description>
 * <param name="pszFilePath" type="IN">File path of backup file</param>
 * <param name="ulMode" type="IN">Mode flags (see category "Backup mode flags")</param>
 * <param name="pfCallbackFunction" type="IN">Callback function to monitor Backup events (optional)</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Backup was successfully triggered</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER"></errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_ACCESS_RIGHTS"></errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_OPERATION_DENIED"></errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BakBackup',`(char *pszFilePath, RTS_UI32 ulMode, PFEVENTCALLBACKFUNCTION pfCallbackFunction)')

/**
 * <description>
 *	Triggers the complete restore process. Function returns immediately (asynchronous).
 *	Start and completion can be optionally monitored via events.
 *	With the sync bit set, the function will wait to finish the operation and returns success or failure (synchronous).
 * </description>
 * <param name="pszFilePath" type="IN">File path of backup file</param>
 * <param name="ulMode" type="IN">Mode flags (see category "Backup mode flags")</param>
 * <param name="pfCallbackFunction" type="IN">Callback function to monitor Backup events (optional)</param>
 * <result>error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Restore was successfully triggered</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER"></errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_ACCESS_RIGHTS"></errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_OPERATION_DENIED"></errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`BakRestore',`(char *pszFilePath, RTS_UI32 ulMode, PFEVENTCALLBACKFUNCTION pfCallbackFunction)')

#ifdef __cplusplus
}
#endif
