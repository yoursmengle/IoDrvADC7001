/**
 * <interfacename>CmpVisuServer</interfacename>
 * <description> 
 *	Interface for the visu server.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpVisuServer')

#include "CmpItf.h"

/**
 * <category>Online tags</category>
 * <description>
 * </description>
 */
#define TAG_APPL_NAME						0x01
#define TAG_VISU_USER_MGMT_DB				0x02
#define TAG_VISU_USER_MGMT_REQ_VERSION		0x03
#define TAG_VISU_USER_MGMT_START_INDEX		0x04
#define TAG_VISU_USER_MGMT_END_INDEX		0x05
#define TAG_VISU_USER_MGMT_FLAGS			0x06
#define TAG_VISU_USER_MGMT_USERCHANGETYPE	0x07
#define TAG_VISU_USER_MGMT_INDEX			0x08
#define TAG_VISU_USER_MGMT_USER				0x09

#define TAG_GET_USER_COUNT_REPLY			0x01
#define TAG_GET_USERS_REPLY					0x02
#define TAG_CHECK_CHANGE_USER_REPLY			0x03
#define TAG_GET_SET_DB_REPLY				0x04

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
 * <element name="udiUserDB" type="IN">The database id of the visu user management</element>
 * <element name="udiReqVersion" type="IN">The request version is used to handle different visu user mgmt library versions.</element>
 * <element name="udiCount" type="OUT">The total number of users in the visualization user management</element>
 * <element name="udiError" type="OUT">Returns an error code indicating, whether the processing was successful or not</element>
 * <element name="bRequestHandled" type="OUT">Returns <c>TRUE</c> if the request has been handled, otherwise <c>FALSE</c></element>
 */
typedef struct
{
	RTS_IEC_STRING* pszApplName;
	RTS_IEC_UDINT udiUserDB;
	RTS_IEC_UDINT udiReqVersion;
	RTS_IEC_UDINT udiCount;
	RTS_IEC_UDINT udiError;
	RTS_IEC_BOOL bRequestHandled;	
} EVTPARAM_VisuUserMgmtGetUserCount;
#define EVTPARAMID_VisuUserMgmtGetUserCount					0x0001
#define EVTVERSION_VisuUserMgmtGetUserCount					0x0001

/**
 * <category>Events</category>
 * <description>Event is sent to determine the total number of users in the visualization user management. </description>
 * <param name="pEventParam" type="IN">EVTPARAMID_VisuUserMgmtGetUserCount</param>
 */
#define EVT_VisuUserMgmtGetUserCount					MAKE_EVENTID(EVTCLASS_INFO, 1)


/**
 * <category>Event parameter</category>
 * <element name="pszApplName" type="IN">The name of the application, which has to process the request.</element>
 * <element name="udiUserDB" type="IN">The user database from which the user info is collected.</element>
 * <element name="udiReqVersion" type="IN">The request version is used to handle different visu user mgmt library versions.</element>
 * <element name="udiStartIndex" type="IN">The start index, where the search has to start.</element>
 * <element name="udiEndIndex" type="IN">The end index, where the search has to start.</element>
 * <element name="udiBufferSize" type="IN">The size of the communication buffer in byte</element>
 * <element name="iArrSize" type="OUT">The number of users stored in <c>pbResult</c></element>
 * <element name="udiError" type="OUT">Returns an error code indicating, whether the processing was successful or not</element>
 * <element name="bRequestHandled" type="OUT">Returns <c>TRUE</c> if the request has been handled, otherwise <c>FALSE</c></element>
 */
typedef struct
{
	RTS_IEC_STRING* pszApplName;
	RTS_IEC_UDINT udiUserDB;
	RTS_IEC_UDINT udiReqVersion;
	RTS_IEC_UDINT udiStartIndex;
	RTS_IEC_UDINT udiEndIndex;
	RTS_IEC_BYTE* pArrUsers;
	RTS_IEC_UDINT udiArrSize;
	RTS_IEC_UDINT udiError;
	RTS_IEC_BOOL bRequestHandled;	
} EVTPARAM_VisuUserMgmtGetUsers;
#define EVTPARAMID_VisuUserMgmtGetUsers				0x0002
#define EVTVERSION_VisuUserMgmtGetUsers				0x0001

/**
 * <category>Events</category>
 * <description>Event is sent to the central visu user mgmt to get a list of users. </description>
 * <param name="pEventParam" type="IN">EVTPARAMID_VisuUserMgmtGetUsers</param>
 */
#define EVT_VisuUserMgmtGetUsers					MAKE_EVENTID(EVTCLASS_INFO, 2)

/**
 * <category>Event parameter</category>
 * <element name="pszApplName" type="IN">The name of the application, which has to process the request.</element>
 * <element name="udiUserDB" type="IN">The database id of the visu user management</element>
 * <element name="udiReqVersion" type="IN">The request version is used to handle different visu user mgmt library versions.</element>
 * <element name="udiCheckChangeUserFlags" type="IN">The flags of this event</element>
 * <element name="udiCheckChangeUserType" type="IN">The change type</element>
 * <element name="udiCheckChangeUserIndex" type="IN">The user index</element>
 * <element name="pvumUser" type="IN">The pointer to the VUM_User structure</element>
 * <element name="udiBufferSize" type="IN">The buffer size of the pvumUser</element>
 * <element name="udiError" type="OUT">Returns an error code indicating, whether the processing was successful or not</element>
 * <element name="udiResult" type="OUT">Returns the result of this request</element>
 * <element name="bRequestHandled" type="OUT">Returns <c>TRUE</c> if the request has been handled, otherwise <c>FALSE</c></element>
 */
typedef struct
{
	RTS_IEC_STRING* pszApplName;
	RTS_IEC_UDINT udiUserDB;
	RTS_IEC_UDINT udiReqVersion;
	RTS_IEC_UDINT udiCheckChangeUserFlags;
	RTS_IEC_UDINT udiCheckChangeUserType;
	RTS_IEC_UDINT udiCheckChangeUserIndex;
	RTS_IEC_BYTE* pvumUser;
	RTS_IEC_UDINT udiBufferSize;
	RTS_IEC_UDINT udiError;
	RTS_IEC_UDINT udiResult;
	RTS_IEC_BOOL bRequestHandled;	
} EVTPARAM_VisuUserMgmtCheckChangeUser;
#define EVTPARAMID_VisuUserMgmtCheckChangeUser					0x0003
#define EVTVERSION_VisuUserMgmtCheckChangeUser					0x0001

/**
 * <category>Events</category>
 * <description>Event is sent to get or set a temporary user mgmt database file in the visualization user management. </description>
 * <param name="pEventParam" type="IN">EVTPARAMID_VisuUserMgmtCheckChangeUser</param>
 */
#define EVT_VisuUserMgmtCheckChangeUser					MAKE_EVENTID(EVTCLASS_INFO, 3)

/**
 * <category>Event parameter</category>
 * <element name="pszApplName" type="IN">The name of the application, which has to process the request.</element>
 * <element name="udiUserDB" type="IN">The database id of the visu user management</element>
 * <element name="udiReqVersion" type="IN">The request version is used to handle different visu user mgmt library versions.</element>
 * <element name="udiGetSetDBFlags" type="IN">The flags of this event</element>
 * <element name="udiError" type="OUT">Returns an error code indicating, whether the processing was successful or not</element>
 * <element name="bRequestHandled" type="OUT">Returns <c>TRUE</c> if the request has been handled, otherwise <c>FALSE</c></element>
 */
typedef struct
{
	RTS_IEC_STRING* pszApplName;
	RTS_IEC_UDINT udiUserDB;
	RTS_IEC_UDINT udiReqVersion;
	RTS_IEC_UDINT udiGetSetDBFlags;
	RTS_IEC_UDINT udiError;
	RTS_IEC_BOOL bRequestHandled;	
} EVTPARAM_VisuUserMgmtGetSetDB;
#define EVTPARAMID_VisuUserMgmtGetSetDB					0x0004
#define EVTVERSION_VisuUserMgmtGetSetDB					0x0001

/**
 * <category>Events</category>
 * <description>Event is sent to get or set a temporary user mgmt database file in the visualization user management. </description>
 * <param name="pEventParam" type="IN">EVTPARAMID_VisuUserMgmtGetSetDB</param>
 */
#define EVT_VisuUserMgmtGetSetDB					MAKE_EVENTID(EVTCLASS_INFO, 4)


