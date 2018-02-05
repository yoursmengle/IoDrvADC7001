/**
 * <interfacename>SysTimeRtc</interfacename>
 * <description> 
 *	The SysTimeRtc interface is projected to get access to an optional realtime clock
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysTimeRtc')

#include "CmpStd.h"

#ifndef CDECL
	#define CDECL
#endif

REF_ITF(`SysTimeItf.m4')


/**
 * <category>Control status HourMode</category>
 * <description></description>
 * <element name="RTC_12HOURS" type="IN">12 hours mode</element>
 * <element name="RTC_24HOURS" type="IN">24 hoursmode</element>
 */
#define RTC_12HOURS		0
#define RTC_24HOURS		1

/**
 * <category>Control status CheckBattery</category>
 * <description></description>
 * <element name="RTC_BATTERY_FAILED" type="IN">Battery empty or failed</element>
 * <element name="RTC_BATTERY_OK" type="IN">Battery Ok</element>
 */
#define RTC_BATTERY_FAILED		0
#define RTC_BATTERY_OK			1

/**
 * <category>Control tags</category>
 * <description></description>
 * <element name="RTC_CTRL_CHECKBATTERY" type="IN">Check the battery of the RTC</element>
 * <element name="RTC_CTRL_HOURMODE" type="IN">Check the hour mode of the RTC</element>
 */
#define RTC_CTRL_CHECKBATTERY	0
#define RTC_CTRL_HOURMODE		1


/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Time and date in structured</description>
 */
typedef struct tagRTS_SYSTIMEDATE
{
	RTS_IEC_UINT wYear;		/* <element="wYear" type="IN">Year (e.g. 2006)</element> */
	RTS_IEC_UINT wMonth;		/* <element="wMonth" type="IN">Month (1..12: January = 1, December = 12)</element> */
	RTS_IEC_UINT wDay;		/* <element="wDay" type="IN">Day of month (1..31)</element> */
	RTS_IEC_UINT wHour;		/* <element="wHour" type="IN">Hours after midnight (0..23)</element> */
	RTS_IEC_UINT wMinute;		/* <element="wMinute" type="IN">Minutes after hour (0..59)</element> */
	RTS_IEC_UINT wSecond;		/* <element="wSecond" type="IN">Seconds after minute (0..59)</element> */
	RTS_IEC_UINT wMilliseconds;		/* <element="wMilliseconds" type="IN">Milliseconds after second (0..999). Optional!</element> */
	RTS_IEC_UINT wDayOfWeek;		/* <element="wDayOfWeek" type="IN">Day of week (1..7: Monday = 1, Sunday = 7</element> */
	RTS_IEC_UINT wYday;		/* <element="wYday" type="IN">Day of year (1..365): January 1 = 1, December 31 = 364/365</element> */
} RTS_SYSTIMEDATE;

/**
 * <category>Timezone information</category>
 * <description>
 *     This infomation describes a local timezone with standard- and daylight-saving-time
 *     (also known as summer- and wintertime).
 * </description>
 */
typedef struct tagTimezoneInformation
{
	RTS_IEC_UDINT ulStandardDate;		/* <element name="ulStandardDate" type="IN">Date to switch to standard time (from summer- to wintertime) [local time in seconds since 1.1.1970 00:00:00]</element> */
	RTS_IEC_UDINT ulDaylightDate;		/* <element name="ulDaylightDate" type="IN">Date to switch to daylight savings time (from winter- to summertime) [local time in seconds since 1.1.1970 00:00:00]</element> */
	RTS_IEC_STRING szStandardName[33];		/* <element name="szStandardName" type="IN">Standard name of the timezone (wintertime) [string with max. 32bytes]</element> */
	RTS_IEC_STRING szDaylightName[33];		/* <element name="szDaylightName" type="IN">Daylight savings time name (summertime) [string with max. 32bytes]</element> */
	RTS_IEC_INT iBias;		/* <element name="iBias" type="IN">UTC = local time + bias [minutes]</element> */
	RTS_IEC_INT iStandardBias;		/* <element name="iStandardBias" type="IN">Additional offset at standard time (wintertime) [minutes]</element> */
	RTS_IEC_INT iDaylightBias;		/* <element name="iDaylightBias" type="IN">Additional offset at daylight savings time (summertime) [minutes]</element> */
} TimezoneInformation;

/**
 * <description>Control the Rtc and read out hardware status information</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystimertccontrol_struct
{
	RTS_IEC_DINT iControlTag;			/* VAR_INPUT */	/* <param name="iControl" type="IN">Control key. See corresponding category for detailed information</param> */
	RTS_IEC_DINT *pdiControlResult;		/* VAR_IN_OUT */	/* <param name="pdiControlResult" type="OUT">Control state. See category Control status for detailed information</param> */
	RTS_IEC_RESULT SysTimeRtcControl;	/* VAR_OUTPUT */	
} systimertccontrol_struct;

DEF_API(`void',`CDECL',`systimertccontrol',`(systimertccontrol_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x6C6D5178),0x03050500)

/**
 * <description>
 * This function converts the time given by time structure into a High Resolution Time of format SysTime.
 *	Time values are always UTC!</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystimertcconvertdatetohighres_struct
{
	RTS_SYSTIMEDATE *pDate;				/* VAR_IN_OUT */	/* <param name="pDate" type="IN">Structure format</param> */
	RTS_IEC_ULINT *pTimestamp;			/* VAR_IN_OUT */	/* <param name="pTimestamp" type="OUT">Milliseconds since 1.1.1970 00:00:000 UTC</param> */
	RTS_IEC_RESULT SysTimeRtcConvertDateToHighRes;	/* VAR_OUTPUT */	
} systimertcconvertdatetohighres_struct;

DEF_API(`void',`CDECL',`systimertcconvertdatetohighres',`(systimertcconvertdatetohighres_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x615A4496),0x03050500)

/**
 * <description>Convert UTC in a structured format to timestamp in seconds</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystimertcconvertdatetoutc_struct
{
	RTS_SYSTIMEDATE *pDate;				/* VAR_IN_OUT */	/* <param name="pDate" type="IN">Pointer to structure format. See category for detailed information</param> */
	RTS_IEC_DWORD *pdwTimestampUtc;		/* VAR_IN_OUT */	/* <param name="pdwTimestampUtc" type="OUT">Pointer to UTC time in seconds since 1.1.1970 00:00:00</param> */
	RTS_IEC_RESULT SysTimeRtcConvertDateToUtc;	/* VAR_OUTPUT */	
} systimertcconvertdatetoutc_struct;

DEF_API(`void',`CDECL',`systimertcconvertdatetoutc',`(systimertcconvertdatetoutc_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x808E752B),0x03050500)

/**
 * <description>Convert a high resolution timestamp to a structure format.
 *	Time values are always UTC!</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystimertcconverthighrestodate_struct
{
	RTS_IEC_ULINT *pTimestamp;			/* VAR_IN_OUT */	/* <param name="pTimestamp" type="IN">Milliseconds since 1.1.1970 00:00:000 UTC</param> */
	RTS_SYSTIMEDATE *pDate;				/* VAR_IN_OUT */	/* <param name="pDate" type="OUT">Structure format</param> */
	RTS_IEC_RESULT SysTimeRtcConvertHighResToDate;	/* VAR_OUTPUT */	
} systimertcconverthighrestodate_struct;

DEF_API(`void',`CDECL',`systimertcconverthighrestodate',`(systimertcconverthighrestodate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x7343C11D),0x03050500)

/**
 * <description>
 * Convert a high resolution timestamp [UTC] to a structure format [Localtime]
 * </description>
 * <errorcode name="RTS_RESULT Result" TYPE="ERR_OK">Timestamp can be converted</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Timestamp failed to convert</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">Conversion is not available on the target</errorcode>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystimertcconverthighrestolocal_struct
{
	RTS_IEC_ULINT *pTimestamp;			/* VAR_IN_OUT */	/* <param name="pTimestamp" type="IN">Milliseconds since 1.1.1970 00:00:000 [UTC]</param> */
	RTS_SYSTIMEDATE *pDate;				/* VAR_IN_OUT */	/* <param name="pDate" type="OUT">Structure format [Localtime]</param> */
	RTS_IEC_RESULT SysTimeRtcConvertHighResToLocal;	/* VAR_OUTPUT */	
} systimertcconverthighrestolocal_struct;

DEF_API(`void',`CDECL',`systimertcconverthighrestolocal',`(systimertcconverthighrestolocal_struct *p)',1,0x326AB8DF,0x03050500)

/**
 * <description>
 * This function converts the time given by time structure [Localtime] into a High Resolution Time of format SysTime [UTC].
 *	</description>
 * <errorcode name="RTS_RESULT Result" TYPE="ERR_OK">DATE can be converted</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Date failed to convert</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">Conversion is not available on the target</errorcode>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystimertcconvertlocaltohighres_struct
{
	RTS_SYSTIMEDATE *pDate;				/* VAR_IN_OUT */	/* <param name="pDate" type="IN">Structure format [Localtime]</param> */
	RTS_IEC_ULINT *pTimestamp;			/* VAR_IN_OUT */	/* <param name="pTimestamp" type="OUT">Milliseconds since 1.1.1970 00:00:000 [UTC]</param> */
	RTS_IEC_RESULT SysTimeRtcConvertLocalToHighRes;	/* VAR_OUTPUT */	
} systimertcconvertlocaltohighres_struct;

DEF_API(`void',`CDECL',`systimertcconvertlocaltohighres',`(systimertcconvertlocaltohighres_struct *p)',1,0x82603563,0x03050500)

/**
 * <description>*OBSOLETE*: Only for backward compatibility.</description>
 */
typedef struct tagsystimertcconvertlocaltoutc_struct
{
	RTS_IEC_DWORD dwTimestampLocal;		/* VAR_INPUT */	
	RTS_IEC_DWORD *pdwTimestampUtc;		/* VAR_IN_OUT */	
	RTS_IEC_RESULT SysTimeRtcConvertLocalToUtc;	/* VAR_OUTPUT */	
} systimertcconvertlocaltoutc_struct;

DEF_API(`void',`CDECL',`systimertcconvertlocaltoutc',`(systimertcconvertlocaltoutc_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x7D11A77B),0x03050500)

/**
 * <description>Convert UTC timestamp in seconds to a structured format</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystimertcconvertutctodate_struct
{
	RTS_IEC_DWORD dwTimestampUtc;		/* VAR_INPUT */	/* <param name="dwTimestampUtc" type="IN">UTC time in seconds since 1.1.1970 00:00:00</param> */
	RTS_SYSTIMEDATE *pDate;				/* VAR_IN_OUT */	/* <param name="pDate" type="OUT">Pointer to structure format. See category for detailed information</param> */
	RTS_IEC_RESULT SysTimeRtcConvertUtcToDate;	/* VAR_OUTPUT */	
} systimertcconvertutctodate_struct;

DEF_API(`void',`CDECL',`systimertcconvertutctodate',`(systimertcconvertutctodate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x6F250D17),0x03050500)

/**
 * <description>*OBSOLETE*: Only for backward compatibility.</description>
 */
typedef struct tagsystimertcconvertutctolocal_struct
{
	RTS_IEC_DWORD dwTimestampUtc;		/* VAR_INPUT */	
	RTS_IEC_DWORD *pdwTimestampLocal;	/* VAR_IN_OUT */	
	RTS_IEC_RESULT SysTimeRtcConvertUtcToLocal;	/* VAR_OUTPUT */	
} systimertcconvertutctolocal_struct;

DEF_API(`void',`CDECL',`systimertcconvertutctolocal',`(systimertcconvertutctolocal_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xFE9BA7D8),0x03050500)

/**
 * <description>Returns the curent Rtc (realtime clock) value in UTC.
 *	<p>UTC time: current coordinated universal time; has replaced the Greenwich Mean Time.
 * The time zones are given as positive or negative deviation from UTC.:
 *	e.g. „UTC+1“ corresponds to the Central European Time (CET) and 
 * ”UTC+2” corresponds to the Central European Summer Time (CEST)</p>
 * </description>
 * <result><p>RESULT: Seconds since 1.1.1970 00:00:00 UTC</p></result>
 */
typedef struct tagsystimertcget_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_IN_OUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param> */
	RTS_IEC_DWORD SysTimeRtcGet;		/* VAR_OUTPUT */	
} systimertcget_struct;

DEF_API(`void',`CDECL',`systimertcget',`(systimertcget_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC885177F),0x03050500)

/**
 * <description>Returns the timezone information</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystimertcgettimezone_struct
{
	TimezoneInformation *pTimezone;		/* VAR_IN_OUT */	/* <param name="pTimezone" type="OUT">Pointer to timezone information. See corresponding category.</param> */
	RTS_IEC_RESULT SysTimeRtcGetTimezone;	/* VAR_OUTPUT */	
} systimertcgettimezone_struct;

DEF_API(`void',`CDECL',`systimertcgettimezone',`(systimertcgettimezone_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCC6D982F),0x03050500)

/**
 * <description>Returns the Rtc (realtime clock) value with a high resolution in UTC.
 *	<p>UTC time: current coordinated universal time; has replaced the Greenwich Mean Time.
 * The time zones are given as positive or negative deviation from UTC.:
 *	e.g. „UTC+1“ corresponds to the Central European Time (CET) and 
 * ”UTC+2” corresponds to the Central European Summer Time (CEST)</p>
 * </description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystimertchighresget_struct
{
	RTS_IEC_ULINT *pTimestamp;			/* VAR_IN_OUT */	/* <param name="pTimestamp" type="OUT">Milliseconds since 1.1.1970 00:00:000 UTC</param> */
	RTS_IEC_RESULT SysTimeRtcHighResGet;	/* VAR_OUTPUT */	
} systimertchighresget_struct;

DEF_API(`void',`CDECL',`systimertchighresget',`(systimertchighresget_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xDA82D1F0),0x03050500)

/**
 * <description>Set the Rtc (realtime clock) value with a high resolution.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsystimertchighresset_struct
{
	RTS_IEC_ULINT *pTimestamp;			/* VAR_IN_OUT */	/* <param name="pTimestamp" type="OUT">Milliseconds since 1.1.1970 00:00:000 UTC</param> */
	RTS_IEC_RESULT SysTimeRtcHighResSet;	/* VAR_OUTPUT */	
} systimertchighresset_struct;

DEF_API(`void',`CDECL',`systimertchighresset',`(systimertchighresset_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x6902D901),0x03050500)

/**
 * <description>Set the Rtc (realtime clock) value in UTC.
 *	<p>UTC time: current coordinated universal time; has replaced the Greenwich Mean Time.
 * The time zones are given as positive or negative deviation from UTC.:
 *	e.g. „UTC+1“ corresponds to the Central European Time (CET) and 
 * ”UTC+2” corresponds to the Central European Summer Time (CEST)</p>
 * </description>
 */
typedef struct tagsystimertcset_struct
{
	RTS_IEC_DWORD ulTimestamp;			/* VAR_INPUT */	/* <param name="ulTimestamp" type="IN">Seconds since 1.1.1970 00:00:00 UTC</param> */
	RTS_IEC_RESULT SysTimeRtcSet;		/* VAR_OUTPUT */	
} systimertcset_struct;

DEF_API(`void',`CDECL',`systimertcset',`(systimertcset_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x288F7E63),0x03050500)

/**
 * <description>Set the specified timezone information</description>
 */
typedef struct tagsystimertcsettimezone_struct
{
	TimezoneInformation *pTimezone;		/* VAR_IN_OUT */	/* <param name="pTimezone" type="IN">Pointer to timezone information. See corresponding category.</param> */
	RTS_IEC_RESULT SysTimeRtcSetTimezone;	/* VAR_OUTPUT */	
} systimertcsettimezone_struct;

DEF_API(`void',`CDECL',`systimertcsettimezone',`(systimertcsettimezone_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x018F4E27),0x03050500)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysTimeRtcOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysTimeRtcOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>Returns the Rtc value (realtime clock). The value is the elapsed number of seconds since
 *	1.1.1970 00:00:00 UTC time.</description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Seconds since 1.1.1970 00:00:00 UTC</result>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`SysTimeRtcGet',`(RTS_RESULT *pResult)')

/**
 * <description>
 * OPTIONAL INTERFACE FUNCTION
 * Set the Rtc value (realtime clock). The value is the elapsed number of seconds since
 *	1.1.1970 00:00:00 UTC time.
 * </description>
 * <param name="ulTimestamp" type="IN">Seconds since 1.1.1970 00:00:00 [UTC]</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Timestamp can be set</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Timestamp failed to set</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">Set is not available on the target</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NO_ACCESS_RIGHTS">No access rights to set the system time</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTimeRtcSet',`(RTS_UI32 ulTimestampUtc)')

/**
 * <description>
 * OPTIONAL INTERFACE FUNCTION
 * Returns the timezone information
 * </description>
 * <param name="pTimezone" type="OUT">Pointer to timezone information. See corresponding category.</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Timezone available</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Get Timezone failed</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">Timezone not available on the target</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTimeRtcGetTimezone',`(TimezoneInformation *pTimezone)')

/**
 * <description>
 * OPTIONAL INTERFACE FUNCTION
 * Set the specified timezone information
 * </description>
 * <param name="pTimezone" type="IN">Pointer to timezone information. See corresponding category.</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Timezone available</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Set Timezone failed</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">Timezone not available on the target</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTimeRtcSetTimezone',`(TimezoneInformation *pTimezone)')

/**
 * <description>Convert UTC time to local time</description>
 * <param name="ulTimestampUtc" type="IN">UTC time in seconds since 1.1.1970 00:00:00</param>
 * <param name="pulTimestampLocal" type="OUT">Local time in seconds since 1.1.1970 00:00:00</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTimeRtcConvertUtcToLocal',`(RTS_UI32 ulTimestampUtc, RTS_UI32 *pulTimestampLocal)')

/**
 * <description>Convert local time to UTC</description>
 * <param name="ulTimestampLocal" type="IN">Local time in seconds since 1.1.1970 00:00:00</param>
 * <param name="pulTimestampUtc" type="OUT">UTC time in seconds since 1.1.1970 00:00:00</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTimeRtcConvertLocalToUtc',`(RTS_UI32 ulTimestampLocal, RTS_UI32 *pulTimestampUtc)')

/**
 * <description>Convert UTC time in seconds to a structure format</description>
 * <param name="ulTimestampUtc" type="IN">UTC time in seconds since 1.1.1970 00:00:00</param>
 * <param name="pDate" type="OUT">Pointer to structure format. See category for detailed information</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTimeRtcConvertUtcToDate',`(RTS_UI32 ulTimestampUtc, RTS_SYSTIMEDATE *pDate)')

/**
 * <description>Convert UTC in a structure format to time in seconds</description>
 * <param name="pDate" type="IN">Pointer to structure format. See category for detailed information</param>
 * <param name="pulTimestampUtc" type="OUT">Pointer to UTC time in seconds since 1.1.1970 00:00:00</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTimeRtcConvertDateToUtc',`(RTS_SYSTIMEDATE *pDate, RTS_UI32 *pulTimestampUtc)')

/**
 * <description>
 * OPTIONAL INTERFACE FUNCTION
 * Control the Rtc and read out hardware status information
 * </description>
 * <param name="rtcControl" type="IN">Control key. See corresponding category for detailed information</param>
 * <param name="piControlResult" type="OUT">Pointer to result. See category Control status for detailed information</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">RTC control available</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">RTC control failed</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">RTC control not available on the target</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTimeRtcControl',`(int iControlTag, int *piControlResult)')



/**
 * <description>Returns the Rtc value (realtime clock). The value is the elapsed number of milliseconds since
 *	1.1.1970 00:00:00:000 UTC time.</description>
 * <param name="pTimestamp" type="OUT">Milliseconds since 1.1.1970 00:00:000 UTC</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTimeRtcHighResGet',`(RTS_SYSTIME* pTimestampUtcHighRes)')

/**
 * <description>
 * OPTIONAL INTERFACE FUNCTION
 * Set the Rtc value (realtime clock). The value is the elapsed number of milliseconds since
 *	1.1.1970 00:00:00:000 UTC time.
 * </description>
 * <param name="pTimestamp" type="OUT">Milliseconds since 1.1.1970 00:00:000 UTC</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Timestamp can be set</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Timestamp failed to set</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">Set is not available on the target</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTimeRtcHighResSet',`(RTS_SYSTIME* pTimestampUtcHighRes)')

/**
 * <description>Convert a high resolution timestamp [UTC] to a structure format [UTC]</description>
 * <param name="pTimestamp" type="IN">Milliseconds since 1.1.1970 00:00:000 [UTC]</param>
 * <param name="pDate" type="OUT">Structure format [UTC]</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTimeRtcConvertHighResToDate',`(RTS_SYSTIME *pTimestampUtcHighRes, RTS_SYSTIMEDATE *pDate)')

/**
 * <description>Convert structure format [UTC] to a high resolution timestamp [UTC]</description>
 * <param name="pDate" type="IN">Structure format [UTC]</param>
 * <param name="pTimestampUtcHighRes" type="OUT">Milliseconds since 1.1.1970 00:00:000 [UTC]</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTimeRtcConvertDateToHighRes',`(RTS_SYSTIMEDATE *pDate, RTS_SYSTIME *pTimestampUtcHighRes)')

/**
 * <description>
 * OPTIONAL INTERFACE FUNCTION
 * Convert a high resolution timestamp [UTC ] to a structure format [Localtime].
 * </description>
 * <param name="pTimestampUtcHighRes" type="IN">Milliseconds since 1.1.1970 00:00:000 [UTC]</param>
 * <param name="pDate" type="OUT">Structure format [Localtime]</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Timestamp can be converted</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Timestamp failed to convert</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">Conversion is not available on the target</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTimeRtcConvertHighResToLocal',`(RTS_SYSTIME *pTimestampUtcHighRes, RTS_SYSTIMEDATE *pDate)')

/**
 * <description>
 * OPTIONAL INTERFACE FUNCTION
 * Convert a structure format [Localtime] to a high resolution timestamp [UTC ].
 * </description>
 * <param name="pDate" type="IN">Structure format [Localtime]</param>
 * <param name="pTimestampUtcHighRes" type="OUT">Milliseconds since 1.1.1970 00:00:000 [UTC]</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Date can be converted</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Date failed to convert</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">Conversion is not available on the target</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysTimeRtcConvertLocalToHighRes',`(RTS_SYSTIMEDATE *pDate, RTS_SYSTIME *pTimestampUtcHighRes)')

#ifdef __cplusplus
}
#endif
