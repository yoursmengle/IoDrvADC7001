 
	
	
#ifndef _CMPALARMMANAGERITF_H_
#define _CMPALARMMANAGERITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"

/**
 * <category>Online services</category>
 * <description>
 * </description>
 */
#define SRV_GET_ALARM_COUNT					0x81
#define SRV_GET_ALARMS						0x82

/**
 * <category>Online tags</category>
 * <description>
 * </description>
 */
#define TAG_APPL_NAME						0x01
#define TAG_ALARMGROUP_IDS					0x02
#define TAG_ALARMCLASS_IDS					0x03
#define TAG_PRIORITY						0x04
#define TAG_ROW_SPECIFICATION				0x05
#define TAG_ROW_ID							0x06

#define TAG_GET_ALARM_COUNT_REPLY			0x01
#define TAG_GET_ALARMS_REPLY				0x82

#define SUBT_GET_ALARMS_REPLY_ERROR			0x01
#define SUBT_GET_ALARMS_REPLY_ROWS			0x02
#define SUBT_GET_ALARMS_REPLY_ROW_ID		0x03

/* Return Values */
#define RETURN_OK							0x00
/* Was unable to create the event and therefore no event can be raised. */
#define RETURN_NO_EVENT						0x01
/* Communication buffer is not large enough to store all the requested alarms. */
#define RETURN_BUFFER_OVERFLOW				0x02
/* No callback handled the event, probably application name was invalid. */
#define RETURN_NOT_HANDLED					0x03


/**
 * <category>Event parameter</category>
 * <element name="pszApplName" type="IN">The name of the application, which has to process the request.</element>
 * <element name="udiCountAlarmGroups" type="IN">
 * The number of alarm group IDs the parameter <c>puiAlarmGroupIDs</c> points to. If no alarm group IDs are
 * specified, this parameter is 0.</element>
 * <element name="pudiAlarmGroupIDs" type="IN">Points to an array of UDINT values with the IDs of the alarm
 * groups to use as filter. If no such filter has been specified this parameter is NULL.</element>
 * <element name="udiCountAlarmClasses" type="IN">
 * The number of alarm class IDs the parameter <c>puiAlarmClassIDs</c> points to. If no alarm class IDs are
 * specified, this parameter is 0.</element>
 * <element name="pudiAlarmClassIDs" type="IN">Points to an array of UDINT values with the IDs of the alarm
 * classes to use as filter. If no such filter has been specified this parameter is NULL.</element>
 * <element name="usiPriorityFrom" type="IN">A byte value with minimum priority the alarm must have.</element>
 * <element name="usiPriorityTo" type="IN">A byte value with maximum priority the alarm must have.</element>
 * <element name="udiCount" type="OUT">The total number of relevant alarms</element>
 * <element name="bRequestHandled" type="OUT">Returns <c>TRUE</c> if the request has been handled, otherwise <c>FALSE</c></element>
 */
typedef struct
{
	RTS_IEC_STRING* pszApplName;
	RTS_IEC_UDINT udiCountAlarmGroups;
	RTS_IEC_UDINT* pudiAlarmGroupIDs;
	RTS_IEC_UDINT udiCountAlarmClasses;
	RTS_IEC_UDINT* pudiAlarmClassIDs;
	RTS_IEC_USINT usiPriorityFrom;
	RTS_IEC_USINT usiPriorityTo;
	RTS_IEC_UDINT udiCount;
	RTS_IEC_BOOL bRequestHandled;	
} EVTPARAM_AlarmManagerGetCount;
#define EVTPARAMID_AlarmManagerGetCount					0x0001
#define EVTVERSION_AlarmManagerGetCount					0x0001

/**
 * <category>Events</category>
 * <description>Event is sent to determine the total number of relevant alarms in the alarm storage 
 * for an alarm table. </description>
 * <param name="pEventParam" type="IN">EVTPARAMID_AlarmManagerGetCount</param>
 */
#define EVT_AlarmManagerGetCount					MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Event parameter</category>
 * <element name="pszApplName" type="IN">The name of the application, which has to process the request.</element>
 * <element name="iSkipRows" type="IN">An int value with the number of rows, that have to skipped.</element>
 * <element name="iMaxRows" type="IN">An int value with the maximum number of rows, that have to be returned.</element>
 * <element name="udiCountAlarmGroups" type="IN">
 * The number of alarm group IDs the parameter <c>puiAlarmGroupIDs</c> points to. If no alarm group IDs are
 * specified, this parameter is 0.</element>
 * <element name="pudiAlarmGroupIDs" type="IN">Points to an array of UDINT values with the IDs of the alarm
 * groups to use as filter. If no such filter has been specified this parameter is NULL.</element>
 * <element name="udiCountAlarmClasses" type="IN">
 * The number of alarm class IDs the parameter <c>puiAlarmClassIDs</c> points to. If no alarm class IDs are
 * specified, this parameter is 0.</element>
 * <element name="pudiAlarmClassIDs" type="IN">Points to an array of UDINT values with the IDs of the alarm
 * classes to use as filter. If no such filter has been specified this parameter is NULL.</element>
 * <element name="usiPriorityFrom" type="IN">A byte value with minimum priority the alarm must have.</element>
 * <element name="usiPriorityTo" type="IN">A byte value with maximum priority the alarm must have.</element>
 * <element name="bRowIDValid" type="IN_OUT">A flag indicating, whether the row ID parameter contains a valid row ID.</element>
 * <element name="diRowID" type="IN_OUT">The row ID of the row, where the search has to start.</element>
 * <element name="pbResult" type="IN">A pointer to the communication buffer, where the data of the rows will 
 * be stored in a serialized way.</element>
 * <element name="udiBufferSize" type="IN">The size of the communication buffer in byte</element>
 * <element name="udiCountRows" type="OUT">The number of rows stored in <c>pbResult</c></element>
 * <element name="uiError" type="OUT">Returns an error code indicating, whether the processing was successful or not</element>
 * <element name="bRequestHandled" type="OUT">Returns <c>TRUE</c> if the request has been handled, otherwise <c>FALSE</c></element>
 */
typedef struct
{
	RTS_IEC_STRING* pszApplName;
	RTS_IEC_INT iSkipRows;	
	RTS_IEC_INT iMaxRows;
	RTS_IEC_UDINT udiCountAlarmGroups;
	RTS_IEC_UDINT* pudiAlarmGroupIDs;
	RTS_IEC_UDINT udiCountAlarmClasses;
	RTS_IEC_UDINT* pudiAlarmClassIDs;
	RTS_IEC_USINT usiPriorityFrom;
	RTS_IEC_USINT usiPriorityTo;
	RTS_IEC_BOOL bRowIDValid;	
	RTS_IEC_DINT diRowID;
	RTS_IEC_BYTE* pbResult;
	RTS_IEC_UDINT udiBufferSize;
	RTS_IEC_UDINT udiCountRows;
	RTS_IEC_UINT uiError;
	RTS_IEC_BOOL bRequestHandled;	
} EVTPARAM_AlarmManagerGetAlarms;
#define EVTPARAMID_AlarmManagerGetAlarms				0x0002
#define EVTVERSION_AlarmManagerGetAlarms				0x0001

/**
 * <category>Events</category>
 * <description>Event is sent to a number of alarms from the alarm storage 
 * for an alarm table. </description>
 * <param name="pEventParam" type="IN">EVTPARAMID_AlarmManagerGetAlarms</param>
 */
#define EVT_AlarmManagerGetAlarms					MAKE_EVENTID(EVTCLASS_INFO, 2)


#define EVTPARAMID_AlarmManagerHandleService			0x0003
#define EVTVERSION_AlarmManagerHandleService			0x0001

/**
 * <category>Events</category>
 * <description>Event is sent to delegate the processing of a service request to
 * the library, where the service will be handled.</description>
 * <param name="pEventParam" type="IN">EVTPARAMID_AlarmManagerHandleService</param>
 */
#define EVT_AlarmManagerHandleService				MAKE_EVENTID(EVTCLASS_INFO, 3)



typedef struct
{
	IBase_C *pBase;
} ICmpAlarmManager_C;

#ifdef CPLUSPLUS
class ICmpAlarmManager : public IBase
{
	public:
};
	#ifndef ITF_CmpAlarmManager
		#define ITF_CmpAlarmManager static ICmpAlarmManager *pICmpAlarmManager = NULL;
	#endif
	#define EXTITF_CmpAlarmManager
#else	/*CPLUSPLUS*/
	typedef ICmpAlarmManager_C		ICmpAlarmManager;
	#ifndef ITF_CmpAlarmManager
		#define ITF_CmpAlarmManager
	#endif
	#define EXTITF_CmpAlarmManager
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPALARMMANAGERITF_H_*/
