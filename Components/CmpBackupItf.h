 /**
 * <interfacename>CmpBackup</interfacename>
 * <description> 
 *	Interface for the backup component. This component is optional, and intended to serve a backup and restore feature.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPBACKUPITF_H_
#define _CMPBACKUPITF_H_

#include "CmpStd.h"

 

 




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
RTS_RESULT CDECL BakSetStatus(CMPID cmpId, RTS_UI32 ulStatus);
typedef RTS_RESULT (CDECL * PFBAKSETSTATUS) (CMPID cmpId, RTS_UI32 ulStatus);
#if defined(CMPBACKUP_NOTIMPLEMENTED) || defined(BAKSETSTATUS_NOTIMPLEMENTED)
	#define USE_BakSetStatus
	#define EXT_BakSetStatus
	#define GET_BakSetStatus(fl)  ERR_NOTIMPLEMENTED
	#define CAL_BakSetStatus(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_BakSetStatus  FALSE
	#define EXP_BakSetStatus  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_BakSetStatus
	#define EXT_BakSetStatus
	#define GET_BakSetStatus(fl)  CAL_CMGETAPI( "BakSetStatus" ) 
	#define CAL_BakSetStatus  BakSetStatus
	#define CHK_BakSetStatus  TRUE
	#define EXP_BakSetStatus  CAL_CMEXPAPI( "BakSetStatus" ) 
#elif defined(MIXED_LINK) && !defined(CMPBACKUP_EXTERNAL)
	#define USE_BakSetStatus
	#define EXT_BakSetStatus
	#define GET_BakSetStatus(fl)  CAL_CMGETAPI( "BakSetStatus" ) 
	#define CAL_BakSetStatus  BakSetStatus
	#define CHK_BakSetStatus  TRUE
	#define EXP_BakSetStatus  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BakSetStatus", (RTS_UINTPTR)BakSetStatus, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBackupBakSetStatus
	#define EXT_CmpBackupBakSetStatus
	#define GET_CmpBackupBakSetStatus  ERR_OK
	#define CAL_CmpBackupBakSetStatus pICmpBackup->IBakSetStatus
	#define CHK_CmpBackupBakSetStatus (pICmpBackup != NULL)
	#define EXP_CmpBackupBakSetStatus  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_BakSetStatus
	#define EXT_BakSetStatus
	#define GET_BakSetStatus(fl)  CAL_CMGETAPI( "BakSetStatus" ) 
	#define CAL_BakSetStatus pICmpBackup->IBakSetStatus
	#define CHK_BakSetStatus (pICmpBackup != NULL)
	#define EXP_BakSetStatus  CAL_CMEXPAPI( "BakSetStatus" ) 
#else /* DYNAMIC_LINK */
	#define USE_BakSetStatus  PFBAKSETSTATUS pfBakSetStatus;
	#define EXT_BakSetStatus  extern PFBAKSETSTATUS pfBakSetStatus;
	#define GET_BakSetStatus(fl)  s_pfCMGetAPI2( "BakSetStatus", (RTS_VOID_FCTPTR *)&pfBakSetStatus, (fl), 0, 0)
	#define CAL_BakSetStatus  pfBakSetStatus
	#define CHK_BakSetStatus  (pfBakSetStatus != NULL)
	#define EXP_BakSetStatus  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BakSetStatus", (RTS_UINTPTR)BakSetStatus, 0, 0) 
#endif




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
RTS_RESULT CDECL BakRegisterFile(CMPID cmpId, char *pszFilePath, RTS_UI32 ulFlags, RTS_SIZE ulFileSize);
typedef RTS_RESULT (CDECL * PFBAKREGISTERFILE) (CMPID cmpId, char *pszFilePath, RTS_UI32 ulFlags, RTS_SIZE ulFileSize);
#if defined(CMPBACKUP_NOTIMPLEMENTED) || defined(BAKREGISTERFILE_NOTIMPLEMENTED)
	#define USE_BakRegisterFile
	#define EXT_BakRegisterFile
	#define GET_BakRegisterFile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_BakRegisterFile(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_BakRegisterFile  FALSE
	#define EXP_BakRegisterFile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_BakRegisterFile
	#define EXT_BakRegisterFile
	#define GET_BakRegisterFile(fl)  CAL_CMGETAPI( "BakRegisterFile" ) 
	#define CAL_BakRegisterFile  BakRegisterFile
	#define CHK_BakRegisterFile  TRUE
	#define EXP_BakRegisterFile  CAL_CMEXPAPI( "BakRegisterFile" ) 
#elif defined(MIXED_LINK) && !defined(CMPBACKUP_EXTERNAL)
	#define USE_BakRegisterFile
	#define EXT_BakRegisterFile
	#define GET_BakRegisterFile(fl)  CAL_CMGETAPI( "BakRegisterFile" ) 
	#define CAL_BakRegisterFile  BakRegisterFile
	#define CHK_BakRegisterFile  TRUE
	#define EXP_BakRegisterFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BakRegisterFile", (RTS_UINTPTR)BakRegisterFile, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBackupBakRegisterFile
	#define EXT_CmpBackupBakRegisterFile
	#define GET_CmpBackupBakRegisterFile  ERR_OK
	#define CAL_CmpBackupBakRegisterFile pICmpBackup->IBakRegisterFile
	#define CHK_CmpBackupBakRegisterFile (pICmpBackup != NULL)
	#define EXP_CmpBackupBakRegisterFile  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_BakRegisterFile
	#define EXT_BakRegisterFile
	#define GET_BakRegisterFile(fl)  CAL_CMGETAPI( "BakRegisterFile" ) 
	#define CAL_BakRegisterFile pICmpBackup->IBakRegisterFile
	#define CHK_BakRegisterFile (pICmpBackup != NULL)
	#define EXP_BakRegisterFile  CAL_CMEXPAPI( "BakRegisterFile" ) 
#else /* DYNAMIC_LINK */
	#define USE_BakRegisterFile  PFBAKREGISTERFILE pfBakRegisterFile;
	#define EXT_BakRegisterFile  extern PFBAKREGISTERFILE pfBakRegisterFile;
	#define GET_BakRegisterFile(fl)  s_pfCMGetAPI2( "BakRegisterFile", (RTS_VOID_FCTPTR *)&pfBakRegisterFile, (fl), 0, 0)
	#define CAL_BakRegisterFile  pfBakRegisterFile
	#define CHK_BakRegisterFile  (pfBakRegisterFile != NULL)
	#define EXP_BakRegisterFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BakRegisterFile", (RTS_UINTPTR)BakRegisterFile, 0, 0) 
#endif




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
RTS_RESULT CDECL BakUnregisterFile(CMPID cmpId, char *pszFilePath);
typedef RTS_RESULT (CDECL * PFBAKUNREGISTERFILE) (CMPID cmpId, char *pszFilePath);
#if defined(CMPBACKUP_NOTIMPLEMENTED) || defined(BAKUNREGISTERFILE_NOTIMPLEMENTED)
	#define USE_BakUnregisterFile
	#define EXT_BakUnregisterFile
	#define GET_BakUnregisterFile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_BakUnregisterFile(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_BakUnregisterFile  FALSE
	#define EXP_BakUnregisterFile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_BakUnregisterFile
	#define EXT_BakUnregisterFile
	#define GET_BakUnregisterFile(fl)  CAL_CMGETAPI( "BakUnregisterFile" ) 
	#define CAL_BakUnregisterFile  BakUnregisterFile
	#define CHK_BakUnregisterFile  TRUE
	#define EXP_BakUnregisterFile  CAL_CMEXPAPI( "BakUnregisterFile" ) 
#elif defined(MIXED_LINK) && !defined(CMPBACKUP_EXTERNAL)
	#define USE_BakUnregisterFile
	#define EXT_BakUnregisterFile
	#define GET_BakUnregisterFile(fl)  CAL_CMGETAPI( "BakUnregisterFile" ) 
	#define CAL_BakUnregisterFile  BakUnregisterFile
	#define CHK_BakUnregisterFile  TRUE
	#define EXP_BakUnregisterFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BakUnregisterFile", (RTS_UINTPTR)BakUnregisterFile, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBackupBakUnregisterFile
	#define EXT_CmpBackupBakUnregisterFile
	#define GET_CmpBackupBakUnregisterFile  ERR_OK
	#define CAL_CmpBackupBakUnregisterFile pICmpBackup->IBakUnregisterFile
	#define CHK_CmpBackupBakUnregisterFile (pICmpBackup != NULL)
	#define EXP_CmpBackupBakUnregisterFile  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_BakUnregisterFile
	#define EXT_BakUnregisterFile
	#define GET_BakUnregisterFile(fl)  CAL_CMGETAPI( "BakUnregisterFile" ) 
	#define CAL_BakUnregisterFile pICmpBackup->IBakUnregisterFile
	#define CHK_BakUnregisterFile (pICmpBackup != NULL)
	#define EXP_BakUnregisterFile  CAL_CMEXPAPI( "BakUnregisterFile" ) 
#else /* DYNAMIC_LINK */
	#define USE_BakUnregisterFile  PFBAKUNREGISTERFILE pfBakUnregisterFile;
	#define EXT_BakUnregisterFile  extern PFBAKUNREGISTERFILE pfBakUnregisterFile;
	#define GET_BakUnregisterFile(fl)  s_pfCMGetAPI2( "BakUnregisterFile", (RTS_VOID_FCTPTR *)&pfBakUnregisterFile, (fl), 0, 0)
	#define CAL_BakUnregisterFile  pfBakUnregisterFile
	#define CHK_BakUnregisterFile  (pfBakUnregisterFile != NULL)
	#define EXP_BakUnregisterFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BakUnregisterFile", (RTS_UINTPTR)BakUnregisterFile, 0, 0) 
#endif





/**
 * <description>Returns the backup capabilities</description>
 * <result>Capability flags (see category "Online service bits")</result>
 */
RTS_UI32 CDECL BakGetCapabilities(void);
typedef RTS_UI32 (CDECL * PFBAKGETCAPABILITIES) (void);
#if defined(CMPBACKUP_NOTIMPLEMENTED) || defined(BAKGETCAPABILITIES_NOTIMPLEMENTED)
	#define USE_BakGetCapabilities
	#define EXT_BakGetCapabilities
	#define GET_BakGetCapabilities(fl)  ERR_NOTIMPLEMENTED
	#define CAL_BakGetCapabilities()  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_BakGetCapabilities  FALSE
	#define EXP_BakGetCapabilities  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_BakGetCapabilities
	#define EXT_BakGetCapabilities
	#define GET_BakGetCapabilities(fl)  CAL_CMGETAPI( "BakGetCapabilities" ) 
	#define CAL_BakGetCapabilities  BakGetCapabilities
	#define CHK_BakGetCapabilities  TRUE
	#define EXP_BakGetCapabilities  CAL_CMEXPAPI( "BakGetCapabilities" ) 
#elif defined(MIXED_LINK) && !defined(CMPBACKUP_EXTERNAL)
	#define USE_BakGetCapabilities
	#define EXT_BakGetCapabilities
	#define GET_BakGetCapabilities(fl)  CAL_CMGETAPI( "BakGetCapabilities" ) 
	#define CAL_BakGetCapabilities  BakGetCapabilities
	#define CHK_BakGetCapabilities  TRUE
	#define EXP_BakGetCapabilities  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BakGetCapabilities", (RTS_UINTPTR)BakGetCapabilities, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBackupBakGetCapabilities
	#define EXT_CmpBackupBakGetCapabilities
	#define GET_CmpBackupBakGetCapabilities  ERR_OK
	#define CAL_CmpBackupBakGetCapabilities pICmpBackup->IBakGetCapabilities
	#define CHK_CmpBackupBakGetCapabilities (pICmpBackup != NULL)
	#define EXP_CmpBackupBakGetCapabilities  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_BakGetCapabilities
	#define EXT_BakGetCapabilities
	#define GET_BakGetCapabilities(fl)  CAL_CMGETAPI( "BakGetCapabilities" ) 
	#define CAL_BakGetCapabilities pICmpBackup->IBakGetCapabilities
	#define CHK_BakGetCapabilities (pICmpBackup != NULL)
	#define EXP_BakGetCapabilities  CAL_CMEXPAPI( "BakGetCapabilities" ) 
#else /* DYNAMIC_LINK */
	#define USE_BakGetCapabilities  PFBAKGETCAPABILITIES pfBakGetCapabilities;
	#define EXT_BakGetCapabilities  extern PFBAKGETCAPABILITIES pfBakGetCapabilities;
	#define GET_BakGetCapabilities(fl)  s_pfCMGetAPI2( "BakGetCapabilities", (RTS_VOID_FCTPTR *)&pfBakGetCapabilities, (fl), 0, 0)
	#define CAL_BakGetCapabilities  pfBakGetCapabilities
	#define CHK_BakGetCapabilities  (pfBakGetCapabilities != NULL)
	#define EXP_BakGetCapabilities  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BakGetCapabilities", (RTS_UINTPTR)BakGetCapabilities, 0, 0) 
#endif




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
RTS_RESULT CDECL BakBackup(char *pszFilePath, RTS_UI32 ulMode, PFEVENTCALLBACKFUNCTION pfCallbackFunction);
typedef RTS_RESULT (CDECL * PFBAKBACKUP) (char *pszFilePath, RTS_UI32 ulMode, PFEVENTCALLBACKFUNCTION pfCallbackFunction);
#if defined(CMPBACKUP_NOTIMPLEMENTED) || defined(BAKBACKUP_NOTIMPLEMENTED)
	#define USE_BakBackup
	#define EXT_BakBackup
	#define GET_BakBackup(fl)  ERR_NOTIMPLEMENTED
	#define CAL_BakBackup(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_BakBackup  FALSE
	#define EXP_BakBackup  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_BakBackup
	#define EXT_BakBackup
	#define GET_BakBackup(fl)  CAL_CMGETAPI( "BakBackup" ) 
	#define CAL_BakBackup  BakBackup
	#define CHK_BakBackup  TRUE
	#define EXP_BakBackup  CAL_CMEXPAPI( "BakBackup" ) 
#elif defined(MIXED_LINK) && !defined(CMPBACKUP_EXTERNAL)
	#define USE_BakBackup
	#define EXT_BakBackup
	#define GET_BakBackup(fl)  CAL_CMGETAPI( "BakBackup" ) 
	#define CAL_BakBackup  BakBackup
	#define CHK_BakBackup  TRUE
	#define EXP_BakBackup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BakBackup", (RTS_UINTPTR)BakBackup, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBackupBakBackup
	#define EXT_CmpBackupBakBackup
	#define GET_CmpBackupBakBackup  ERR_OK
	#define CAL_CmpBackupBakBackup pICmpBackup->IBakBackup
	#define CHK_CmpBackupBakBackup (pICmpBackup != NULL)
	#define EXP_CmpBackupBakBackup  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_BakBackup
	#define EXT_BakBackup
	#define GET_BakBackup(fl)  CAL_CMGETAPI( "BakBackup" ) 
	#define CAL_BakBackup pICmpBackup->IBakBackup
	#define CHK_BakBackup (pICmpBackup != NULL)
	#define EXP_BakBackup  CAL_CMEXPAPI( "BakBackup" ) 
#else /* DYNAMIC_LINK */
	#define USE_BakBackup  PFBAKBACKUP pfBakBackup;
	#define EXT_BakBackup  extern PFBAKBACKUP pfBakBackup;
	#define GET_BakBackup(fl)  s_pfCMGetAPI2( "BakBackup", (RTS_VOID_FCTPTR *)&pfBakBackup, (fl), 0, 0)
	#define CAL_BakBackup  pfBakBackup
	#define CHK_BakBackup  (pfBakBackup != NULL)
	#define EXP_BakBackup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BakBackup", (RTS_UINTPTR)BakBackup, 0, 0) 
#endif




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
RTS_RESULT CDECL BakRestore(char *pszFilePath, RTS_UI32 ulMode, PFEVENTCALLBACKFUNCTION pfCallbackFunction);
typedef RTS_RESULT (CDECL * PFBAKRESTORE) (char *pszFilePath, RTS_UI32 ulMode, PFEVENTCALLBACKFUNCTION pfCallbackFunction);
#if defined(CMPBACKUP_NOTIMPLEMENTED) || defined(BAKRESTORE_NOTIMPLEMENTED)
	#define USE_BakRestore
	#define EXT_BakRestore
	#define GET_BakRestore(fl)  ERR_NOTIMPLEMENTED
	#define CAL_BakRestore(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_BakRestore  FALSE
	#define EXP_BakRestore  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_BakRestore
	#define EXT_BakRestore
	#define GET_BakRestore(fl)  CAL_CMGETAPI( "BakRestore" ) 
	#define CAL_BakRestore  BakRestore
	#define CHK_BakRestore  TRUE
	#define EXP_BakRestore  CAL_CMEXPAPI( "BakRestore" ) 
#elif defined(MIXED_LINK) && !defined(CMPBACKUP_EXTERNAL)
	#define USE_BakRestore
	#define EXT_BakRestore
	#define GET_BakRestore(fl)  CAL_CMGETAPI( "BakRestore" ) 
	#define CAL_BakRestore  BakRestore
	#define CHK_BakRestore  TRUE
	#define EXP_BakRestore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BakRestore", (RTS_UINTPTR)BakRestore, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpBackupBakRestore
	#define EXT_CmpBackupBakRestore
	#define GET_CmpBackupBakRestore  ERR_OK
	#define CAL_CmpBackupBakRestore pICmpBackup->IBakRestore
	#define CHK_CmpBackupBakRestore (pICmpBackup != NULL)
	#define EXP_CmpBackupBakRestore  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_BakRestore
	#define EXT_BakRestore
	#define GET_BakRestore(fl)  CAL_CMGETAPI( "BakRestore" ) 
	#define CAL_BakRestore pICmpBackup->IBakRestore
	#define CHK_BakRestore (pICmpBackup != NULL)
	#define EXP_BakRestore  CAL_CMEXPAPI( "BakRestore" ) 
#else /* DYNAMIC_LINK */
	#define USE_BakRestore  PFBAKRESTORE pfBakRestore;
	#define EXT_BakRestore  extern PFBAKRESTORE pfBakRestore;
	#define GET_BakRestore(fl)  s_pfCMGetAPI2( "BakRestore", (RTS_VOID_FCTPTR *)&pfBakRestore, (fl), 0, 0)
	#define CAL_BakRestore  pfBakRestore
	#define CHK_BakRestore  (pfBakRestore != NULL)
	#define EXP_BakRestore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"BakRestore", (RTS_UINTPTR)BakRestore, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFBAKSETSTATUS IBakSetStatus;
 	PFBAKREGISTERFILE IBakRegisterFile;
 	PFBAKUNREGISTERFILE IBakUnregisterFile;
 	PFBAKGETCAPABILITIES IBakGetCapabilities;
 	PFBAKBACKUP IBakBackup;
 	PFBAKRESTORE IBakRestore;
 } ICmpBackup_C;

#ifdef CPLUSPLUS
class ICmpBackup : public IBase
{
	public:
		virtual RTS_RESULT CDECL IBakSetStatus(CMPID cmpId, RTS_UI32 ulStatus) =0;
		virtual RTS_RESULT CDECL IBakRegisterFile(CMPID cmpId, char *pszFilePath, RTS_UI32 ulFlags, RTS_SIZE ulFileSize) =0;
		virtual RTS_RESULT CDECL IBakUnregisterFile(CMPID cmpId, char *pszFilePath) =0;
		virtual RTS_UI32 CDECL IBakGetCapabilities(void) =0;
		virtual RTS_RESULT CDECL IBakBackup(char *pszFilePath, RTS_UI32 ulMode, PFEVENTCALLBACKFUNCTION pfCallbackFunction) =0;
		virtual RTS_RESULT CDECL IBakRestore(char *pszFilePath, RTS_UI32 ulMode, PFEVENTCALLBACKFUNCTION pfCallbackFunction) =0;
};
	#ifndef ITF_CmpBackup
		#define ITF_CmpBackup static ICmpBackup *pICmpBackup = NULL;
	#endif
	#define EXTITF_CmpBackup
#else	/*CPLUSPLUS*/
	typedef ICmpBackup_C		ICmpBackup;
	#ifndef ITF_CmpBackup
		#define ITF_CmpBackup
	#endif
	#define EXTITF_CmpBackup
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPBACKUPITF_H_*/
