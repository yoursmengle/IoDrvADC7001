/**
 * <interfacename>CmpLog</interfacename>
 * <description><p>Interface of the runtime system logger component.</p>
 *
 * <p>The logger can log runtime system messages in form of strings, together
 * with some describing informations, like message categories and IDs.
 * The messages are saved in a local buffer in the RAM and uploaded to
 * the CoDeSys programming system or an external service tool on demand.</p>
 *
 * <p>The embedded variant of this component does not support backends and
 * is therefore not able to save the log messages into a file.</p>
 *
 * <p>Neither the log buffer in RAM, nor the communication medium are safe.
 * Therefore one can not essentially rely on the content of the log
 * messages. They can only be used for analytical purposes.</p>
 *
 * <p>For runtimes with the define RTS_SIL2 defined, the component may be a
 * bit more limited. For example, no events are supported.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpLog')

#include <stdarg.h>
#include "CmpStd.h"
REF_ITF(`CmpLogBackendItf.m4')
REF_ITF(`SysTimeRtcItf.m4')


#ifndef LOG_TEXT
	#define LOG_TEXT(s)					s
#endif

#ifndef LOG_DEFAULT_NUM_OF_LOGGER
	#define LOG_DEFAULT_NUM_OF_LOGGER	1		/* Default number of loggers */
#endif

#ifndef LOG_DEFAULT_NUM_OF_ITF
	#define LOG_DEFAULT_NUM_OF_ITF		3		/* Default number of logger interfaces per logger */
#endif


/**
 * <category>Settings</category>
 * <description>
 *	For all logger settings you have to specify the prefix and the logger ID: "Logger.<ID>.xxx".
 *	ID=0 is the standard logger of the runtime system!
 *	Example:
 *		Logger.0.Name=PlcLog
 *		Logger.1.Name=MyLogger
 * </description>
 */
#define LOGKEY_LOGGER_PREFIX			"Logger"

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 *	Setting to specify the logger name
 *	Example:
 *		Logger.0.Name=PlcLog
 * </description>
 */
#ifndef LOGKEY_STRING_NAME
	#define LOGKEY_STRING_NAME			"Name"
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to enable a logger. Enable=0 means disable, Enable=1 means enable
 *	Example:
 *		Logger.0.Name=PlcLog
 *		Logger.0.Enable=0
 * </description>
 */
#define LOGKEY_INT_ENABLE				"Enable"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to filter which type of log entries the logger will store. See "Log class/filter" for details.
 *	Example:
 *		Logger.0.Name=PlcLog
 *		Logger.0.Filter=0x0000000F	; Only logger entries of type (LOG_INFO | LOG_WARNING | LOG_ERROR | LOG_EXCEPTION) are logged
 * </description>
 */
#define LOGKEY_INT_FILTER				"Filter"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to specify the type of a logger. See "Log types" for details.
 *	Example:
 *		Logger.0.Name=PlcLog
 *		Logger.0.Type=0x00000514	; This is a standard logger (LT_NORMAL | LT_TIMESTAMP_RTC | LT_NO_DISABLE | LT_DUMP_ALWAYS)
 * </description>
 */
#define LOGKEY_INT_TYPE					"Type"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to specify the maximum number of entries that can be stored in the ringbuffer of the logger.
 *	Example:
 *		Logger.0.Name=PlcLog
 *		Logger.0.MaxEntries=500
 * </description>
 */
#define LOGKEY_INT_MAXENTRIES			"MaxEntries"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to specify the maximum file size, if logger is stored in SysFile backend.
 *	Example:
 *		Logger.0.Name=PlcLog
 *		Logger.0.MaxFileSize=100000
 * </description>
 */
#define LOGKEY_INT_MAXFILESIZE			"MaxFileSize"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to specify the maximum number of files, if logger is stored in SysFile backend.
 *	Example:
 *		Logger.0.Name=PlcLog
 *		Logger.0.MaxFiles=3
 * </description>
 */
#define LOGKEY_INT_MAXFILES				"MaxFiles"


/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to specify the logger backend
 *	It must be used the way:  "Logger.<ID>.Backend.<ID Backend>.xxx"
 *	Example:
 *		Logger.0.Backend.0.ClassId=0x00000104
 * </description>
 */
#define LOGKEY_BACKEND					"Backend"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to specify the type of backend. This is specified via the corresponding class id of the backend (classes see CmpItf.h).
 *	E.g.
 *		ClassId=0x00000104		; This the class id of the SysFile component. See CLASSID_CSysFile in CmpItf.h.
 *		ClassId=0x0000010B		; This the class id of the CLASSID_CSysOut component for the outputs on a console. See CLASSID_CSysOut in CmpItf.h.
 *
 *	Example:
 *		Logger.0.Backend.0.ClassId=0x00000104
 * </description>
 */
#define LOGKEY_INT_CLASSID				"ClassId"


/**
 * <category>Log types</category>
 * <description>Types of a logger instance</description>
 * <element name="LT_HIGHSPEED" type="">Not supported</element>
 * <element name="LT_SAFE" type="">Not supported. Dump log entries in ring buffer residing in retain memory.</element>
 * <element name="LT_NORMAL" type="">Dump log entries in ring buffer residing in volatile memory (RAM)</element>
 * <element name="LT_TIMESTAMP_RTC" type="">Use realtime clock for the timestamp</element>
 * <element name="LT_TIMESTAMP_RTC_HIGHRES" type="">Use realtime clock with high resolution for the timestamp</element>
 * <element name="LT_TIMESTAMP_MS" type="">Use millisecond ticks for the timestamp</element>
 * <element name="LT_TIMESTAMP_US" type="">Use microsecond ticks for the timestamp</element>
 * <element name="LT_TIMESTAMP_NS" type="">Use nanosecond ticks for the timestamp</element>
 * <element name="LT_NO_DISABLE" type="">If this option is set, the logger cannot be disabled</element>
 * <element name="LT_DUMP_ASYNC" type="">Dump asynchronously in the backends</element>
 * <element name="LT_DUMP_ALWAYS" type="">Dump into the backends at every log entry</element>
 * <element name="LT_DUMP_ON_CLOSE" type="">Dump only the backends at closing the logger</element>
 * <element name="LT_DUMP_ON_REQUEST" type="">Dump can be done by calling LogDumpEntries()</element>
 * <element name="LT_DUMP_FORMAT2" type="">Dump with optional format 2. Is only recognized in the backends.</element>
 * <element name="LT_STD" type=""></element>
 */
#define LT_HIGHSPEED				UINT32_C(0x00000001)
#define LT_SAFE 					UINT32_C(0x00000002)
#define LT_NORMAL					UINT32_C(0x00000004)
#define LT_TS_BACKEND_LOCALTIME		UINT32_C(0x00000008)
#define LT_TIMESTAMP_RTC			UINT32_C(0x00000010)
#define LT_TIMESTAMP_RTC_HIGHRES	UINT32_C(0x00002000)
#define LT_TIMESTAMP_MS 			UINT32_C(0x00000020)
#define LT_TIMESTAMP_US 			UINT32_C(0x00000040)
#define LT_TIMESTAMP_NS 			UINT32_C(0x00000080)
#define LT_NO_DISABLE				UINT32_C(0x00000100)
#define LT_DUMP_ASYNC				UINT32_C(0x00000200)
#define LT_DUMP_ALWAYS				UINT32_C(0x00000400)
#define LT_DUMP_ON_CLOSE			UINT32_C(0x00000800)
#define LT_DUMP_ON_REQUEST			UINT32_C(0x00001000)
#define LT_DUMP_FORMAT2 			UINT32_C(0x00004000)
#ifndef LT_STD
	#define LT_STD						(LT_NORMAL | LT_TIMESTAMP_RTC | LT_NO_DISABLE | LT_DUMP_ALWAYS)
#endif
#define LT_HAS_TYPE(pLogger, Type)	 (pLogger->lo.iType & Type)

/**
 * <category>Log class/filter</category>
 * <description>Log entry classes and filters</description>
 * <element name="LOG_NONE" type="No defined class"></element>
 * <element name="LOG_INFO" type="Information"></element>
 * <element name="LOG_WARNING" type="Warning"></element>
 * <element name="LOG_ERROR" type="Error"></element>
 * <element name="LOG_EXCEPTION" type="Exception"></element>
 * <element name="LOG_DEBUG" type="Debug log entries (reserved for development, diagnosis or test)"></element>
 * <element name="LOG_PRINTF" type="Debug log entries like printf. For this entry, no timestamp ist logged."></element>
 * <element name="LOG_COM" type="Communication"></element>
 * <element name="LOG_INFO_TIMESTAMP_RELATIVE" type="Information with timestamp relative to the previous entry"></element>
 * <element name="LOG_CRIT_SEC" type="Semaphore log entries"></element>
 * <element name="LOG_USER_NOTIFY" type="Log entries are displayed as a message box in CoDeSys"></element>
 */
#define LOG_NONE					UINT32_C(0x00000000)
#define LOG_INFO					UINT32_C(0x00000001)
#define LOG_WARNING					UINT32_C(0x00000002)
#define LOG_ERROR					UINT32_C(0x00000004)
#define LOG_EXCEPTION				UINT32_C(0x00000008)
#define LOG_DEBUG					UINT32_C(0x00000010)
#define LOG_PRINTF					UINT32_C(0x00000020)
#define LOG_COM						UINT32_C(0x00000040)
#define LOG_INFO_TIMESTAMP_RELATIVE	UINT32_C(0x00000080)
#define LOG_CRIT_SEC				UINT32_C(0x00000100)
#define LOG_USER_NOTIFY				UINT32_C(0x00010000)

/**
 * <category>Log filter</category>
 * <description>Log entry classes and filters</description>
 * <element name="LOG_NONE" type="LogFilter"></element>
 */
#define LOG_ALL						UINT32_MAX
#define LOG_STD						(LOG_INFO | LOG_WARNING | LOG_ERROR | LOG_EXCEPTION)
#define ToLog(Class, Filter)		(Class & Filter)


/**
 * <category>Static defines</category>
 * <description>Predefined objects in the runtime</description>
 */
#define USERDB_OBJECT_LOGGER		"Device.Logger"


/* Log info id */
#define LOG_INFOID_NONE				0x00000000

/* Predefined logger handles */
#define STD_LOGGER					0

/* Predefined logger used for the Component manager profiling. */
#if defined RTS_ENABLE_PROFILING
#define PROFILER_LOGGER				(RTS_HANDLE)1
#define PROFILER_LOGGER_NAME		"Profiler"
#define PROFILER_LOGGER_MAX_ENTRIES 1000
#endif

#ifndef STD_LOGGER_NAME
	#define STD_LOGGER_NAME				"PlcLog"
#endif
#ifndef COMM_LOGGER_NAME
	#define COMM_LOGGER_NAME			"CommLog"
#endif
#ifndef STD_LOGFILE_ENDING
	#define STD_LOGFILE_ENDING			".csv"
#endif

/**
 * <category>Static defines</category>
 * <description>Default maximimum number of log entries in a logger instance</description>
 */
#ifndef LOG_STD_MAX_NUM_OF_ENTRIES
	#define LOG_STD_MAX_NUM_OF_ENTRIES	500
#endif

/**
 * <category>Static defines</category>
 * <description>Default maximimum number of files for a logger with a file backend</description>
 */
#ifndef LOG_STD_MAX_NUM_OF_FILES
	#define LOG_STD_MAX_NUM_OF_FILES	3
#endif

/**
 * <category>Static defines</category>
 * <description>Default maximimum file size for a logger with a file backend</description>
 */
#ifndef LOG_STD_MAX_FILE_SIZE
	#define LOG_STD_MAX_FILE_SIZE		100000
#endif

/**
 * <category>Static defines</category>
 * <description>Maximimum lenght of the info string in a logger entry</description>
 */
#ifndef LOG_MAX_INFO_LEN
	#define LOG_MAX_INFO_LEN		128
#endif

/**
 * <category>Event parameter</category>
 * <element name="pApp" type="IN">Pointer to application description</element>
 */
typedef struct
{
	RTS_HANDLE hLog;
	CMPID CmpId;
	RTS_I32 iClassID;
	RTS_RESULT iErrorID;
	RTS_I32 iInfoID;
	char *pszInfo;
	va_list *pargList;
} EVTPARAM_CmpLogAdd;
#define EVTPARAMID_CmpLogAdd		0x0001
#define EVTVERSION_CmpLogAdd		0x0002
/**
 * <category>Events</category>
 * <description>Event is sent, after a new log entry added to the logger</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpLogAdd</param>
 */
#define EVT_LogAdd							MAKE_EVENTID(EVTCLASS_INFO, 1)



/**
 * <category>Online services</category>
 * <description>
 *	Get all log entries
 * </description>
 */
#define LOG_GET_ENTRIES				0x01

/**
 * <category>Online services</category>
 * <description>
 *	Get component name specified by component id
 * </description>
 */
#define LOG_GET_COMPONENT_NAMES		0x02

/**
 * <category>Online services</category>
 * <description>
 *	Get all registered logger names
 * </description>
 */
#define LOG_GET_LOGGER_LIST			0x03

/**
 * <category>Online service tags</category>
 * <description>
 * </description>
 */
#define TAG_LOGGER_NAME				0x01
#define TAG_START_HANDLE			0x02
#define TAG_START_TIMESTAMP			0x03
#define TAG_NUM_OF_ENTRIES			0x04
#define TAG_COMPONENT_ID			0x05

#define TAG_LOG_REPLY_ERROR			0x01

#define TAG_REPLY_LOGENTRY			0x82
#define TAG_ENTRY_HANDLE			0x01
#define TAG_TIMESTAMP_UTC			0x02
#define TAG_LOG_ENTRY				0x03
#define TAG_LOG_INFO				0x04
#define TAG_COMPONENT_NAME			0x05
#define TAG_TIMESTAMP_MS			0x06
#define TAG_TIMESTAMP_US			0x07
#define TAG_TIMESTAMP_NS			0x08
#define TAG_TIMESTAMP_UTC_HIGH_RES	0x09


/**
 * <SIL2/>
 * <category>Logger</category>
 * <description>Options of a logger (part of the configuration).</description>
 * <param name="szName" type="IN">Name of logger</param>
 * <param name="bEnable" type="IN">Logger active/inactive</param>
 * <param name="iType" type="IN">Logger type. See above log types.</param>
 * <param name="iFilter" type="IN">Filter for the logger entries to store. It is a combination of log classes</param>
 * <param name="iMaxEntries" type="IN">Max number of possible log entries</param>
 * <param name="iMaxFileSize" type="IN">Max file size, if logger content is stored in a file</param>
 * <param name="iMaxFiles" type="IN">Max number of files, if logger content is stored in a file</param>
 * <param name="pszPath" type="IN">Optional path for the logger file</param>
 */
typedef struct tagLogOptions
{
	char szName[32];
	RTS_I32 bEnable;
	RTS_I32 iType;
	RTS_I32 iFilter;
	RTS_I32 iMaxEntries;
	RTS_I32 iMaxFileSize;
	RTS_I32 iMaxFiles;
	char *pszPath;
} LogOptions;

typedef union
{
	RTS_UI32 ulTs;
	RTS_UI64 ullTs;
} LogTimestamp;


/**
 * <SIL2/>
 * <category>Logger</category>
 * <description>One logger Entry, including the message.</description>
 */
typedef struct tagLogEntry
{
	LogTimestamp tTimestamp;
	CMPID CmpId;
	RTS_UI32 iClassID;
	RTS_RESULT iErrorID;
	RTS_UI32 iInfoID;
	char szInfo[LOG_MAX_INFO_LEN];
} LogEntry;

/**
 * <SIL2/>
 * <category>Logger</category>
 * <description>Backend interface of one logger.</description>
 */
typedef struct
{
	CLASSID ClassId;
	RTS_HANDLE hLogBackend;
	RTS_I32 iLastDumpedIndex;
} LogItf;

/**
 * <SIL2/>
 * <category>Logger</category>
 * <description>Configuration of one logger.</description>
 */
typedef struct
{
	LogOptions lo;
	RTS_UI32 ulStartTimestamp;
	RTS_I32 iIndex;
	RTS_I32 iFirstIndex;
	RTS_I32 iRegInterfaces;
	RTS_I32 iDumpSync;
	LogEntry *pLog;
	LogItf tLogItf[LOG_DEFAULT_NUM_OF_ITF];
} Logger;

typedef RTS_RESULT (CDECL * PFLOGADD2) (RTS_HANDLE hLog, CMPID CmpId, RTS_I32 iClassID, RTS_RESULT iErrorID, RTS_I32 iInfoID, char *pszInfo, ...);


/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <SIL2/>
 */
typedef struct taglogadd_struct
{
	RTS_IEC_HANDLE hLogger;				/* VAR_INPUT */	
	RTS_IEC_STRING stCmpName[81];		/* VAR_INPUT */	
	RTS_IEC_DINT diClassID;				/* VAR_INPUT */	
	RTS_IEC_DINT diErrorID;				/* VAR_INPUT */	
	RTS_IEC_DINT diInfoID;				/* VAR_INPUT */	
	RTS_IEC_STRING stInfo[256];			/* VAR_INPUT */	
	RTS_IEC_RESULT LogAdd;				/* VAR_OUTPUT */	
} logadd_struct;

DEF_API(`void',`CDECL',`logadd',`(logadd_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x23C1D811),0x03050500)

/**
 * <SIL2/>
 */
typedef struct taglogadd2_struct
{
	RTS_IEC_HANDLE hLogger;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiCmpID;				/* VAR_INPUT */	
	RTS_IEC_UDINT udiClassID;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiErrorID;			/* VAR_INPUT */	
	RTS_IEC_UDINT udiInfoID;			/* VAR_INPUT */	
	RTS_IEC_STRING *pszInfo;			/* VAR_INPUT */	
	RTS_IEC_RESULT LogAdd2;				/* VAR_OUTPUT */	
} logadd2_struct;

DEF_API(`void',`CDECL',`logadd2',`(logadd2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x317F5220),0x03050500)

/**
 * <SIL2/>
 */
typedef struct taglogclose_struct
{
	RTS_IEC_HANDLE hLogger;				/* VAR_INPUT */	
	RTS_IEC_RESULT LogClose;			/* VAR_OUTPUT */	
} logclose_struct;

DEF_API(`void',`CDECL',`logclose',`(logclose_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD950850C),0x03050500)

/**
 * <SIL2/>
 */
typedef struct taglogcreate_struct
{
	LogOptions *pOptions;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE LogCreate;			/* VAR_OUTPUT */	
} logcreate_struct;

DEF_API(`void',`CDECL',`logcreate',`(logcreate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x428C258C),0x03050500)

/**
 * <SIL2/>
 */
typedef struct taglogdelete_struct
{
	RTS_IEC_HANDLE hLogger;				/* VAR_INPUT */	
	RTS_IEC_RESULT LogDelete;			/* VAR_OUTPUT */	
} logdelete_struct;

DEF_API(`void',`CDECL',`logdelete',`(logdelete_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x676DF4F9),0x03050500)

/**
 * <SIL2/>
 */
typedef struct taglogopen_struct
{
	RTS_IEC_STRING *pszName;			/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE LogOpen;				/* VAR_OUTPUT */	
} logopen_struct;

DEF_API(`void',`CDECL',`logopen',`(logopen_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xABBDCC4F),0x03050500)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description> Create a logger </description>
 * <param name="pOptions" type="IN">Options for logger</param>
 * <param name="pResult" type="OUT">Pointer to get the result</param>
 * <result>Handle to the logger, or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `LogCreate', `(LogOptions *pOptions,  RTS_RESULT *pResult)')

/**
 * <description> Open a logger with the specified name. Logger must exist! </description>
 * <param name="pszName" type="IN">Logger name</param>
 * <param name="pResult" type="OUT">Pointer to get the result</param>
 * <result>Handle to the logger, or RTS_INVALID_HANDLE if logger does not exist</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `LogOpen', `(char *pszName, RTS_RESULT *pResult)')

/**
 * <description> Close the handle to a logger </description>
 * <param name="hLog" type="IN">Handle to logger</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `LogClose', `(RTS_HANDLE hLog)')

/**
 * <description> Delete a logger </description>
 * <param name="hLog" type="IN">Handle to logger</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `LogDelete', `(RTS_HANDLE hLog)')

/**
 * <description> Get options of logger </description>
 * <param name="hLog" type="IN">Handle to logger</param>
 * <param name="ppOptions" type="OUT">Pointer to pointer to log options</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `LogGetOptions', `(RTS_HANDLE hLog, LogOptions **ppOptions)')

/**
 * <description> Enable logging </description>
 * <param name="hLog" type="IN">Handle to logger</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `LogEnable', `(RTS_HANDLE hLog)')

/**
 * <description> Disable logging </description>
 * <param name="hLog" type="IN">Handle to logger</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `LogDisable', `(RTS_HANDLE hLog)')

/**
 * <description> Set filter of logger </description>
 * <param name="hLog" type="IN">Handle to logger</param>
 * <param name="iFilter" type="IN">Logger filter</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `LogSetFilter', `(RTS_HANDLE hLog, RTS_I32 iFilter)')

/**
 * <description> Get filter of logger</description>
 * <param name="hLog" type="IN">Handle to logger</param>
 * <result> Filter </result>
 */
DEF_ITF_API(`RTS_I32', `CDECL', `LogGetFilter', `(RTS_HANDLE hLog)')

/**
 * <description>
 * <p>Add a new log entry to the log buffer.</p>
 *
 * <p>If the buffer is full when this function is called, the oldest
 * log entry in the buffer will be overwritten.</p>
 *
 * <p>If the Class ID contains LOG_INFO_TIMESTAMP_RELATIVE, there is an additional
 * tag, called "TimeRel" added to the text of the log entry. This will
 * limit the message size of the entry by the size of this tag.</p>
 *
 * <p>If the Class ID contains the flag LOG_USER_NOTIFY, the log message
 * will be shown in form of a message box at the next log in of 
 * CoDeSys or instantly if CoDeSys is still loged in.</p>
 *
 * <p>The interface supports a minimum of 8 variable arguments. Depending
 * on the C-Library, this might be more.</p>
 * <p>LT_TIMESTAMP_RTC, LT_TIMESTAMP_RTC_HIGHRES is not supported in SIL2 Runtime.</p>
 * </description>
 * <param name="hLog" type="IN" range="[RTS_INVALID_HANDLE,STD_LOGGER]">Handle to logger</param>
 * <param name="CmpId" type="IN" range="[VALID_CMPID]">Component id</param>
 * <param name="iClassID" type="IN" range="[LOG_ALL,LOG_NONE,LOG_ALL_NOT_LOG_USER_NOTIFY,LOG_ALL_NOT_LOG_INFO_TIMESTAMP_RELATIVE]">ClassID of entry (Info, Warning, Error, etc.)</param>
 * <param name="iErrorID" type="IN" range="[VALID_IERRORID]">Error code if available</param>
 * <param name="iInfoID" type="IN" range="[VALID_IINFOID]">ID of info text to enable multiple language error texts</param>
 * <param name="pszInfo" type="IN" range="[NULL,VALID_PSZINFO]">String to info text (in english or informations coded in XML)</param>  
 * <parampseudo name="_iFilterID" type="IN" range="[LOG_ALL,LOG_ALL_NOT_LOG_USER_NOTIFY,LOG_ALL_NOT_LOG_INFO_TIMESTAMP_RELATIVE]">Filter option</parampseudo>
 * <parampseudo name="_iType_Timestamp" type="IN" range="[LT_TIMESTAMP_MS,LT_TIMESTAMP_US,LT_TIMESTAMP_NS]">Logger Type Timestamp</parampseudo>
 * <parampseudo name="_bAddedEntry" type="OUT">Entry Added to Log</parampseudo> 
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid logger handle</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">iClassID was filtered for this logger or Logger is not enabled,</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">Configured memory for log buffer could not be allocated</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `LogAdd', `(RTS_HANDLE hLog, CMPID CmpId, RTS_I32 iClassID, RTS_RESULT iErrorID, RTS_I32 iInfoID, char *pszInfo, ...)')

/**
 * <description>
 * <p>Add a new log entry to the log buffer.</p>
 *
 * <p>The behavior is the same as the behavior of "LogAdd()", except that the 
 * parameter is a pointer to a variable argument list instead of a direct
 * variable argument list, passed to the function.</p>
 * </description>
 * <param name="hLog" type="IN" range="[RTS_INVALID_HANDLE,STD_LOGGER]">Handle to logger</param>
 * <param name="CmpId" type="IN" range="[VALID_CMPID]">Component id</param>
 * <param name="iClassID" type="IN" range="[LOG_ALL,LOG_NONE]">ClassID of entry (Info, Warning, Error, etc.)</param>
 * <param name="iErrorID" type="IN" range="[VALID_IERRORID]">Error code if available</param>
 * <param name="iInfoID" type="IN" range="[VALID_IINFOID]">ID of info text to enable multiple language error texts</param>
 * <param name="pszInfo" type="IN" range="[NULL,VALID_PSZINFO_1,VALID_PSZINFO_MAX]">String to info text (in english or informations coded in XML)</param>
 * <param name="pargList" type="IN" range="[NULL,VALID_PARGLIST]">Pointer to argument list, format is specified in pszInfo</param>
 * <parampseudo name="_bAddedEntry" type="OUT">Entry Added to Log</parampseudo>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid logger handle</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">iClassID was filtered for this logger or Logger is not enabled,</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">Configured memory for log buffer could not be allocated</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `LogAddArg', `(RTS_HANDLE hLog, CMPID CmpId, RTS_I32 iClassID, RTS_RESULT iErrorID, RTS_I32 iInfoID, char *pszInfo, va_list *pargList)')

/**
 * <description> Dump all entries from all log files </description>
 * <param name="iOptions" type="IN"><p>One or multiple of the following options:</p> 
 *	<ul>
 *		<li>LT_DUMP_ASYNC: If dump is done from an asychronous event</li>
 *		<li>LT_DUMP_ALWAYS: If dump should be forced (always)</li>
 *		<li>LT_DUMP_ON_CLOSE: If dump is called from closing the logger instance</li>
 *		<li>LT_DUMP_ON_REQUEST: If dump is forced from a request</li>
 *	</ul>
 * </param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `LogDumpAll', `(int iOptions)')

/**
 * <description> Dump all entries from the last still dumped entry </description>
 * <param name="hLog" type="IN">Handle to the logger</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `LogDumpEntries', `(RTS_HANDLE hLog)')

/**
 * OBSOLETE FUNCTION: Use LogRegisterBackend instead
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `LogRegisterInterface', `(RTS_HANDLE hLog, CLASSID ClassId, ICmpLogBackend *pIBackend)')

/**
 * OBSOLETE FUNCTION: Use LogUnregisterBackend instead
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `LogUnregisterInterface', `(RTS_HANDLE hLog, ICmpLogBackend *pIBackend)')

/**
 * <description>Register a backend at the specified logger</description>
 * <param name="hLog" type="IN">Handle to the logger. Can be RTS_INVALID_HANDLE an so the backend is unregistered from all logger instances!</param>
 * <param name="ClassId" type="IN">ClassId of the backend. ClassId must be registered previously in the backend component with CMRegisterClass!</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `LogRegisterBackend', `(RTS_HANDLE hLog, CLASSID ClassId)')

/**
 * <description>Unregister a backend at the specified logger</description>
 * <param name="hLog" type="IN">Handle to the logger. Can be RTS_INVALID_HANDLE an so the backend is unregistered from all logger instances!</param>
 * <param name="ClassId" type="IN">ClassId of the backend. ClassId must be registered previously in the backend component with CMRegisterClass!</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `LogUnregisterBackend', `(RTS_HANDLE hLog, CLASSID ClassId)')

/**
 * <description> Get the first logentry of a logger </description>
 * <param name="hLog" type="IN">Handle to logger</param>
 * <param name="iIndex" type="IN">Index of entry to get. 0 is the first entry.</param>
 * <param name="pLogEntry" type="IN">Pointer to log entry</param>
 * <param name="pResult" type="IN">Pointer to result</param>
 * <result>Handle to next log entry or RTS_INVALID_HANDLE, if end of logger is reached</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `LogGetEntryByIndex', `(RTS_HANDLE hLog, int iIndex, LogEntry *pLogEntry, RTS_RESULT *pResult)')

/**
 * <description> Get the first logentry of a logger </description>
 * <param name="hLog" type="IN">Handle to logger</param>
 * <param name="iQueueIndex" type="IN">Index of entry to get. -1 get the first entry.</param>
 * <param name="pLogEntry" type="IN">Pointer to log entry</param>
 * <param name="pResult" type="IN">Pointer to result</param>
 * <result>Handle to next log entry or RTS_INVALID_HANDLE, if end of logger is reached</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `LogGetEntryByQueueIndex', `(RTS_HANDLE hLog, int iQueueIndex, LogEntry *pLogEntry, RTS_RESULT *pResult)')

/**
 * <description> Get the first logentry of a logger </description>
 * <param name="hLog" type="IN">Handle to logger</param>
 * <param name="pLogEntry" type="IN">Pointer to log entry</param>
 * <param name="pResult" type="IN">Pointer to result</param>
 * <result>Handle to next log entry or RTS_INVALID_HANDLE, if end of logger is reached</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `LogGetFirstEntry', `(RTS_HANDLE hLog, LogEntry *pLogEntry, RTS_RESULT *pResult)')

/**
 * <description> Get the next logentry of a logger </description>
 * <param name="hLog" type="IN">Handle to logger</param>
 * <param name="hEntry" type="IN">Handle to log entry (is returned by LogGetFirstEntry or LogGetNextEntry)</param>
 * <param name="pLogEntry" type="IN">Pointer to log entry</param>
 * <param name="pResult" type="IN">Pointer to result</param>
 * <result>Handle to next log entry or RTS_INVALID_HANDLE, if end of logger is reached</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `LogGetNextEntry', `(RTS_HANDLE hLog, RTS_HANDLE hEntry, LogEntry *pLogEntry, RTS_RESULT *pResult)')

/**
 * <description> Get an entry specified by handle</description>
 * <param name="hLog" type="IN">Handle to logger</param>
 * <param name="hEntry" type="IN">Handle to log entry (is returned by LogGetFirstEntry or LogGetNextEntry)</param>
 * <param name="pLogEntry" type="IN">Pointer to log entry</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `LogGetEntry', `(RTS_HANDLE hLog, RTS_HANDLE hEntry, LogEntry *pLogEntry)')

/**
 * <description>Get the first registered logger</description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the first logger</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `LogGetFirstLogger', `(RTS_RESULT *pResult)')

/**
 * <description>Get the next registered logger</description>
 * <param name="hLogger" type="IN">Handle to previous logger</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the first logger</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `LogGetNextLogger', `(RTS_HANDLE hLogger, RTS_RESULT *pResult)')

/**
 * <description>Get the logger name of the logger specified by handle</description>
 * <param name="hLogger" type="IN">Handle to the logger</param>
 * <param name="pszLogger" type="INOUT">Pointer to logger name</param>
 * <param name="nMaxLen" type="IN">Max length of pszLogger</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `LogGetName', `(RTS_HANDLE hLog, char *pszLoggerName, int nMaxLen)')

/**
 * <description>Get the last log entry of class LOG_USER_NOTIFY</description>
 * <param name="ppLogEntryUserNotify" type="OUT">Returns the pointer to the user notify entry</param>
 * <result>Error code:
 *	<ul>
 *		<li>ERR_OK: There is still an unread log entry of the type LOG_USER_NOTIFY</li>
 *		<li>ERR_NO_OBJECT: No pending log entry of the type LOG_USER_NOTIFY</li>
 *	</ul>
 * </result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `LogGetUserNotify', `(LogEntry **ppLogEntryUserNotify)')

/**
 * <description>Convert the timestamp of a log entry into the corresponding structured RTS_SYSTIMEDATE format</description>
 * <param name="hLog" type="IN">Handle to the logger</param>
 * <param name="tTimestamp" type="IN">Timestamp of the log entry</param>
 * <param name="pDate" type="OUT">Return the converted timestamp</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Timestamp type of the logger. See "Log types" for details</result>
 */
DEF_ITF_API(`RTS_UI32', `CDECL', `LogConvertTimestamp', `(RTS_HANDLE hLog, LogTimestamp tTimestamp, RTS_SYSTIMEDATE *pDate, RTS_RESULT *pResult)')

#ifdef __cplusplus
}
#endif

