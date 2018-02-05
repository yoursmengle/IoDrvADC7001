SET_INTERFACE_NAME(`CmpCoreDump')

#include "CmpItf.h"

/**
 * <category>Application code location information</category>
 * <description>
 *	Describes all POUs contained in an application
 * </description>
 */
typedef struct _CODE_LOCATION_STRUCT
{
	RTS_IEC_UINT usiAreaCodeLocation;
	RTS_IEC_UDINT udiOffsetCodeLocation;
	RTS_IEC_UDINT udiCodeSize;
} CODE_LOCATION_STRUCT;

typedef struct _CODE_LOCATION_INFO
{
	RTS_IEC_UDINT udiInfoVersion;
	RTS_IEC_UDINT udiNumPOUs;
	CODE_LOCATION_STRUCT* pPOUs;
} CODE_LOCATION_INFO;

/**
 * <category>Online services</category>
 * <description>
 * </description>
 */
#define SRV_CD_READ_STACK					0x01
#define SRV_CD_GET_EXISTING_FILENAME		0x02

/**
 * <category>Online tags</category>
 * <description>
 * </description>
 */
#define TAG_CD_APP_SESSIONID				0x02
#define TAG_CD_STACK_FRAME					0x83
#define TAG_CD_STACK_FRAME_SIZE				0x04
#define TAG_CD_STACK_FRAME_DATA				0x05
#define TAG_CD_STACK_FRAME_PTR				0x06
#define TAG_CD_CORE_FILE_INFO				0x84
#define TAG_CD_CORE_FILENAME				0x02
#define TAG_CD_FILE_CREATION_DATE			0x03

/**
 * <category>Static defines</category>
 * <description>Core-Dump file extension. The prefix is the corresponding application name, e.g. "Application.core".</description>
 */
#ifndef CORE_DUMP_FILE_EXTENSION
	#define CORE_DUMP_FILE_EXTENSION			".core"
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to enable/disable the addition of a timestamp to the filename. 
 *  Activating this option also means that several Core Dump files might be stored on the PLC.
 *  This increases storage size requirements.
 *	1: Add timestamp
 *	0: Don't add timestamp (default)
 * </description>
 */
#define CDKEY_INT_ADD_TIMESTAMP_FILENAME					"AddTimestampToFilename"
#ifndef CDVALUE_INT_ADD_TIMESTAMP_FILENAME_DEFAULT		
	#define CDVALUE_INT_ADD_TIMESTAMP_FILENAME_DEFAULT		0
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 *	Setting for the storage location of Core Dumps. By default they are stored in the same location as the boot project.
 * </description>
 */
#define CDKEY_STRING_STORAGE_PATH					"StoragePath"
#ifndef CDVALUE_STRING_STORAGE_PATH_DEFAULT	
	#define CDVALUE_STRING_STORAGE_PATH_DEFAULT			""
#endif

/**
 * <category>Event parameter</category>
 * <element name="pApp" type="IN">Pointer to application object.</element>
 * <element name="bDeny" type="OUT">1: Operation is denied, 0: Operation can be executed</element>
 */
typedef struct
{
	struct tagAPPLICATION *pApp;
	int bDeny;
} EVTPARAM_CmpCoreDumpBeforeCreate;
#define EVTPARAMID_CmpCoreDumpBeforeCreate				0x0001
#define EVTVERSION_CmpCoreDumpBeforeCreate				0x0001

/**
 * <category>Event parameter</category>
 * <element name="pApp" type="IN">Pointer to application object.</element>
 * <element name="bDeny" type="OUT">1: Operation is denied, 0: Operation can be executed</element>
 */
typedef struct
{
	struct tagAPPLICATION *pApp;
} EVTPARAM_CmpCoreDumpAfterCreate;
#define EVTPARAMID_CmpCoreDumpAfterCreate				0x0001
#define EVTVERSION_CmpCoreDumpAfterCreate				0x0001

/**
 * <category>Events</category>
 * <description>Event is sent before creating a core dump. The creation can be denied.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpCoreDumpBeforeCreate</param>
 */
#define EVT_BeforeCreate						MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Events</category>
 * <description>Event is sent after creating a Core Dump for an application</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpCoreDumpAfterCreate</param>
 */
#define EVT_AfterCreate						MAKE_EVENTID(EVTCLASS_INFO, 2)

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif
