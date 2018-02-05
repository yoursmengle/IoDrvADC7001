/**
 * <interfacename>CmpUserDB</interfacename>
 * <description> 
 *	Interface for the user management database. Two different kinds of user management items must be stored:
 *	
 *	1. Users + Groups:
 *	   Here you have to store all users with their credentials and their property flags, additionally all user groups with all assigned users and the usergroup property flags.
 *
 *	   Example:
 *			- User: Name = "MyUser"; Password = [password in a safe hash]; Property = 0x....
 *			- UserGroup: Name = "Administrator"; UserMembers = "MyUser", "..."; Property = 0x....
 *
 *	2. User Rights:
 *	   Here you have to store the tree of all objects of the runtime system with their assigned usergroups and the configured rights on it.
 *
 *	   Example:
 *			- Object: Name = "Device"; UserGroup = "Administator" | Rights = USERDB_RIGHT_ALL | DeniedRights = USERDB_RIGHT_NONE; 
 *									   UserGroup = "..." | Rights = ... | DeniedRights = ...;
 *									   ...
 *			- Object: Name = "Device.MyObject"; UserGroup = "Administator" | Rights = USERDB_RIGHT_ALL | DeniedRights = USERDB_RIGHT_NONE; 
 *												UserGroup = "..." | Rights = ... | DeniedRights = ...;
 *												...
 *
 *	For details see CmpUserMgrItf.h.
 *
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions GmbH</copyright>
 */

SET_INTERFACE_NAME(`CmpUserDB')

#include "CmpItf.h"
#include "CmpCryptMD5Itf.h"

/**
 * <category>Static defines</category>
 * <description>Number of users at startup</description>
 */
#ifndef USERDB_NUM_OF_STATIC_USERS
	#define USERDB_NUM_OF_STATIC_USERS		8
#endif

/**
 * <category>Static defines</category>
 * <description>Number of usergroups at startup</description>
 */
#ifndef USERDB_NUM_OF_STATIC_GROUPS
	#define USERDB_NUM_OF_STATIC_GROUPS		4
#endif

/**
 * <category>Static defines</category>
 * <description>Number of user and group handles at startup</description>
 */
#ifndef USERDB_NUM_OF_STATIC_HANDLES
	#define USERDB_NUM_OF_STATIC_HANDLES	12
#endif

/**
 * <category>UserDB properties</category>
 * <description>Properties for a user or usergroup</description>
 */
#define USERDB_PROP_NONE					UINT32_C(0x00000000)
#define USERDB_PROP_EDITABLE				UINT32_C(0x00000001)
#define USERDB_PROP_ADD_MEMBER				UINT32_C(0x00000002)
#define USERDB_PROP_REMOVE_MEMBER			UINT32_C(0x00000004)
#define USERDB_PROP_CREATE					UINT32_C(0x00000008)
#define USERDB_PROP_DELETE					UINT32_C(0x00000010)
#define USERDB_PROP_REMOVE_ALL_MEMBERS		UINT32_C(0x00000020)
#define USERDB_PROP_EDIT_RIGHTS				UINT32_C(0x00000040)
#define USERDB_PROP_OWNER					UINT32_C(0x00000080)
#define USERDB_PROP_NAME_EDITABLE			UINT32_C(0x00000100)
#define USERDB_PROP_PASSWORD_UPTODATE		UINT32_C(0x00001000)
#define USERDB_PROP_ENABLE_CHANGE_PASSWORD	UINT32_C(0x00002000)
#define USERDB_PROP_ALL					(UINT32_C(0x0FFFFFFF) & ~USERDB_PROP_OWNER)

#define USERDB_PROP_GROUP_ADMINISTRATOR_DEFAULT	(USERDB_PROP_EDITABLE | USERDB_PROP_ADD_MEMBER | USERDB_PROP_REMOVE_MEMBER | USERDB_PROP_CREATE | USERDB_PROP_OWNER)
#define USERDB_PROP_USER_ADMINISTRATOR_DEFAULT	(UINT32_C(0x0FFFFFFF) & ~USERDB_PROP_NAME_EDITABLE & ~USERDB_PROP_DELETE)
#define USERDB_PROP_GROUP_EVERYONE_DEFAULT		(USERDB_PROP_ADD_MEMBER | USERDB_PROP_REMOVE_MEMBER | USERDB_PROP_CREATE | USERDB_PROP_EDIT_RIGHTS )

/**
 * <category>Static defines</category>
 * <description>Passwort types</description>
 */
#define USERDB_PASSWORD_TYPE_STRING		UINT32_C(0x00000001)
#define USERDB_PASSWORD_TYPE_MD5		UINT32_C(0x00000002)

/**
 * <category>Union to store the cleartext password or a password hash optional</category>
 * <description>
 *	Password entry.
 * </description>
 *	<element name="psz" type="IN">Cleartext password</element>
 *	<element name="abyMD5" type="IN">Buffer to store the MD5 hash</element>
 */
typedef union
{
	char *psz;			
	unsigned char abyMD5[CRYPTMD5_KEY_LENGTH];
} UserDBPassword;

/**
 * <category>User database entry</category>
 * <description>
 *	User database entry to hold all informations of a user.
 * </description>
 *	<element name="pszUser" type="IN">User name</element>
 *	<element name="ulPasswordType" type="IN">Password type</element>
 *	<element name="Password" type="IN">Stored password credential</element>
 *	<element name="ulProperty" type="IN">User properties. See category "UserDB properties"</element>
 */
typedef struct
{
	char *pszUser;
	RTS_UI32 ulPasswordType;
	UserDBPassword Password;
	RTS_UI32 ulProperty;
} UserDBEntry;

/**
 * <category>User group database entry</category>
 * <description>
 *	User group database entry to hold all informations of a usergroup.
 * </description>
 *	<element name="pszGroup" type="IN">Group name</element>
 *	<element name="hUserList" type="IN">Handle to the mempool user list assigned to the group</element>
 *	<element name="hGroupList" type="IN">Handle to the mempool group list from which this group is derived</element>
 *	<element name="ulProperty" type="IN">User group properties. See category "UserDB properties"</element>
 */
typedef struct
{
	char *pszGroup;
	RTS_HANDLE hUserList;
	RTS_HANDLE hGroupList;
	RTS_UI32 ulProperty;
} GroupDBEntry;


/**
 * <category>Predefined user groups</category>
 * <description>Predefined user groups</description>
 * <element name="USERDB_GROUP_ADMINISTRATOR" type="IN">Administrator group. A member of this groups has all access rights on all objects!</element>
 * <element name="USERDB_GROUP_DEVELOPER" type="IN">Developer group. A member of this groups has all access to the IEC applications an all related stuff.</element>
 * <element name="USERDB_GROUP_SERVICE" type="IN">Service group. A member of this groups has all access to object for maintenance and service operations.</element>
 * <element name="USERDB_GROUP_WATCH" type="IN">Watch group. A member of this groups has read-only access to the objects.</element>
 * <element name="USERDB_GROUP_EVERYONE" type="IN">Everyone group. Every user is automatically member of this group!
 *					NOTE:
 *					By default, this group has read-only access to the objects. But this can be deactivated, so every user must be a member of one of the groups above and have
 *					no access right by default!
 * </element>
 */
#define USERDB_GROUP_ADMINISTRATOR		"Administrator"
#define USERDB_GROUP_DEVELOPER			"Developer"
#define USERDB_GROUP_SERVICE			"Service"
#define USERDB_GROUP_WATCH				"Watch"
#define USERDB_GROUP_EVERYONE			"Everyone"

/**
 * <category>Predefined users</category>
 * <description>Predefined users that are created for the default user management</description>
 */
#define USERDB_USER_ADMINISTRATOR		"Administrator"
#define USERDB_USER_ANONYMOUS			"Anonymous"


/**
 * <category>User rights</category>
 * <description>Defined rights that can fully control the access to an object</description>
 * <element name="USERDB_RIGHT_NONE" type="IN">Access denied</element>
 * <element name="USERDB_RIGHT_VIEW" type="IN">Only view rights on the object. Object cannot be modified in any way!</element>
 * <element name="USERDB_RIGHT_MODIFY" type="IN">Object can be viewed and modified</element>
 * <element name="USERDB_RIGHT_EXECUTE" type="IN">Object can be executed</element>
 * <element name="USERDB_RIGHT_ADD_REMOVE" type="IN">It is allowed to add and remove subobjects</element>
 * <element name="USERDB_RIGHT_OEM" type="IN">The upper 8 bits of the access rights are reserved for OEM specific access rights</element>
 * <element name="USERDB_RIGHT_ALL" type="IN">All rights allowed on the object</element>
 */
#define USERDB_RIGHT_NONE					UINT32_C(0x00000000)
#define USERDB_RIGHT_VIEW					UINT32_C(0x00000001)
#define USERDB_RIGHT_MODIFY					UINT32_C(0x00000002)
#define USERDB_RIGHT_EXECUTE				UINT32_C(0x00000004)
#define USERDB_RIGHT_ADD_REMOVE				UINT32_C(0x00000008)
#define USERDB_RIGHT_OEM					UINT32_C(0xFF000000)
#define USERDB_RIGHT_ALL					UINT32_C(0xFFFFFFFF)

/**
 * <category>Event parameter</category>
 * <element name="bUserManagementChanged" type="IN">TRUE: Usermanagement database changed; FALSE: Not changed</element>
 * <element name="bRightsManagementChanged" type="IN">TRUE: Rightsmanagement database changed; FALSE: Not changed</element>
 */
typedef struct
{
	RTS_HANDLE hGroup;
} EVTPARAM_UserDbRemoveGroupFromRightsDB;

#define EVTPARAMID_UserDbRemoveGroupFromRightsDB	0x0001
#define EVTVERSION_UserDbRemoveGroupFromRightsDB	0x0001

/**
 * <category>Events</category>
 * <description>Event is sent every time the usermanagement database or the userrights database was changed</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpUserMgrDatabaseChanged</param>
 */
#define EVT_UserDbRemoveGroupFromRightsDB		MAKE_EVENTID(EVTCLASS_INFO, 1)


#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*                    Users and UserGroups management																														*/
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

/* --------- User management configuration ---------------------------------- */ 
/* This section of functions is OPTIONAL and must only be implemented, if the */
/* Users + Groups configuration in CODESYS is used!							  */

/**
 * <description>Function to check if users and usergroups database is configurable (not fix compiled)</description>
 * <param name="pulPropertyUsers" type="OUT">Pointer to get the users property: USERDB_PROP_ALL = Users are configurable, USERDB_PROP_NONE = Users are not configurable</param>
 * <param name="pulPropertyGroups" type="OUT">Pointer to get the user groups property: USERDB_PROP_ALL = Groups are configurable, USERDB_PROP_NONE = Groups are not configurable</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Succeeded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Could not be retrieved</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBIsConfigurable', `(RTS_UI32 *pulPropertyUsers, RTS_UI32 *pulPropertyGroups)')

/**
 * <description>Load the user database into memory</description>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Succeeded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Error loading user database</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Is not implemented perhaps the UserDB is fix</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBLoad', `(void)')

/**
 * <description>Storing the current user management into permanent database file</description>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Succeeded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Error storing user database</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Is not implemented perhaps the UserDB is fix</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBStore', `(void)')

/**
 * <description>Release user management in memory. NOTE: The database file is not removed!</description>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Succeeded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Failed releasing user management</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Is not implemented perhaps the UserDB is fix</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBRelease', `(void)')

/* Single user configuration */

/**
 * <description>Add a new user to the user database</description>
 * <param name="pszUser" type="IN">User name</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User could be added</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_DUPLICATE">User already exists</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter. pszUser = NULL or empty</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">No memory available to store new user</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <result>Handle to the added user or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBAdd', `(char *pszUser, RTS_RESULT *pResult)')

/**
 * <description>Remove user from the user database</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User could be removed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user handle</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBRemove', `(RTS_HANDLE hUser)')

/**
 * <description>Set or overwrite the password credential of the user</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="pszPassword" type="IN">Pointer to password in cleartext</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Password could be set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user handle or password = NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_DUPLICATE">The new and the old password are the same</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBSetPassword', `(RTS_HANDLE hUser, char *pszPassword)')

/**
 * <description>Get the password credential of the user</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="pbyPasswordMD5" type="IN">Pointer to MD5 hash of the password</param>
 * <param name="piMaxLen" type="INOUT">Pointer to password MD5 hash length. If it is too short, needed length is returned if error code is ERR_BUFFERSIZE</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Password could be set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user handle or piMaxLen = NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_BUFFERSIZE">If password buffer is too short. Needed length is returned in *piMaxLen </errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBGetPasswordMD5', `(RTS_HANDLE hUser, unsigned char *pbyPasswordMD5, int *piMaxLen)')

/**
 * <description>Set or overwrite the password credential of the user</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="pbyPasswordMD5" type="IN">Pointer to MD5 hash of the password</param>
 * <param name="piMaxLen" type="INOUT">Pointer to password MD5 hash length. If it is too short, needed length is returned if error code is ERR_BUFFERSIZE</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Password could be set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user handle or piMaxLen = NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_BUFFERSIZE">If password is too short. Needed length is returned in *piMaxLen </errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_DUPLICATE">The new and the old password are the same</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBSetPasswordMD5', `(RTS_HANDLE hUser, unsigned char *pbyPasswordMD5, int *piMaxLen)')

/**
 * <description>Set properties of a user</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="pulProperty" type="IN">Pointer to set the properties. For details see category "UserDB properties"</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Properties could be set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user handle or property pointer = NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Invalid combination of property flags (password change not allowed but password not up to date)</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBSetProperty', `(RTS_HANDLE hUser, RTS_UI32 ulProperty)')


/* --------- User management ------------------------------------------------- */
/* This section of functions is MANDATORY for the user management!             */

/* User iteration */

/**
 * <description>Iteration interface to get the first configured user</description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">First user available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No user configured</errorcode>
 * <result>Handle to the first user or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBGetFirst', `(RTS_RESULT *pResult)')

/**
 * <description>Iteration interface to get next configured user. Must be started with UserDBGetFirst()</description>
 * <param name="hPrevUser" type="IN">Handle to the previous user retrieved via UserDBGetFirst() or subsequent calls of UserDBGetNext()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Next user available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No next user available</errorcode>
 * <result>Handle to the next user or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBGetNext', `(RTS_HANDLE hPrevUser, RTS_RESULT *pResult)')

/* Single user access */

/**
 * <description>Open user specified by its name</description>
 * <param name="pszUser" type="IN">User name</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User could be opened</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter. pszUser = NULL or empty</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <result>Handle to the user or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBOpen', `(char *pszUser, RTS_RESULT *pResult)')

/**
 * <description>Close a user</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User could be closed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user handle</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBClose', `(RTS_HANDLE hUser)')

/**
 * <description>Get user name</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="pszUser" type="OUT">Pointer to get user name</param>
 * <param name="piMaxLen" type="INOUT">Pointer to length of buffer in pszUser. If pszUser = NULL, only the length of the user name is returned in *piMaxLen</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User name is returned</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user handle or pszUser = NULL and piMaxLen = NULL</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBGetName', `(RTS_HANDLE hUser, char *pszUser, int *piMaxLen)')

/**
 * <description>Get properties of a user</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="pulProperty" type="OUT">Pointer to return the properties. For details see category "UserDB properties"</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Properties could be retrieved</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user handle or property pointer = NULL</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBGetProperty', `(RTS_HANDLE hUser, RTS_UI32 *pulProperty)')

/**
 * <description>Check user credentials (authentication)</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="pszPassword" type="IN">Pointer to password in cleartext</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Password credential matched!</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user handle or password = NULL so password credential does not match!</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Password credential does not match!</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBCheckPassword', `(RTS_HANDLE hUser, char *pszPassword)')

/* Iteration over all groups to which the user is assigned */

/**
 * <description>Iteration interface to get the first group to which the user is assigned</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">First user group available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user handle</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No user group configured</errorcode>
 * <result>Handle to the first user group or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBGetFirstGroup', `(RTS_HANDLE hUser, RTS_RESULT *pResult)')

/**
 * <description>Iteration interface to get next configured user group to which the user is assigned. Must be started with UserDBGetFirstGroup()</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="hPrevGroup" type="IN">Handle to the previous user group retrieved via UserDBGetFirstGroup() or subsequent calls of UserDBGetNextGroup()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Next user group available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No next user group available</errorcode>
 * <result>Handle to the next user group or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBGetNextGroup', `(RTS_HANDLE hUser, RTS_HANDLE hPrevGroup, RTS_RESULT *pResult)')


/* --------- Group management configuration --------------------------------- */
/* This section of functions is OPTIONAL and must only be implemented, if the */
/* Users + Groups configuration in CODESYS is used!							  */

/**
 * <description>Add a new user group to the user database</description>
 * <param name="pszGroup" type="IN">Group name</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Group could be added</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_DUPLICATE">Group already exists</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter. pszGroup = NULL or empty</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">No memory available to store new group</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <result>Handle to the added group or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBGroupAdd', `(char *pszGroup, RTS_RESULT *pResult)')

/**
 * <description>Remove user group from the user database</description>
 * <param name="hGroup" type="IN">Handle to the group</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Group could be removed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid group handle</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBGroupRemove', `(RTS_HANDLE hGroup)')

/**
 * <description>Add a new user to a group</description>
 * <param name="hGroup" type="IN">Handle to the group</param>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User could be added or is already added</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter. hGroup or hUser invalid</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">No memory available to add user to group</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBGroupAddUser', `(RTS_HANDLE hGroup, RTS_HANDLE hUser)')

/**
 * <description>Remove a user from a group</description>
 * <param name="hGroup" type="IN">Handle to the group</param>
 * <param name="hUser" type="IN">Handle to the user</param>
  * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User could be removed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter. hGroup or hUser invalid</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBGroupRemoveUser', `(RTS_HANDLE hGroup, RTS_HANDLE hUser)')

/**
 * <description>Set properties of a group</description>
 * <param name="hGroup" type="IN">Handle to the group</param>
 * <param name="pulProperty" type="IN">Pointer to set the properties. For details see category "UserDB properties"</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Properties could be set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user group or property pointer = NULL</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBGroupSetProperty', `(RTS_HANDLE hGroup, RTS_UI32 ulProperty)')

/**
 * <description>Add a group as a member to another group. So that group is derived from the first one</description>
 * <param name="hGroup" type="IN">First group to derive from</param>
 * <param name="hGroupMember" type="IN">New member group which is derived from the first group (hGroup) after this operation</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Group could be added</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_DUPLICATE">Group is already added</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter. hGroup or hGroupMember invalid</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">No memory available to add group to another group</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBGroupAddMember', `(RTS_HANDLE hGroup, RTS_HANDLE hGroupMember)')

/**
 * <description>Remove a group as a member from another group. So the group is no longer derived from the first one</description>
 * <param name="hGroup" type="IN">First group to remove the derived group from</param>
 * <param name="hGroupMember" type="IN">Member group which is no longer derived from the first group (hGroup) after this operation</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Group could be removed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter. hGroup or hGroupMember invalid</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 */
 DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBGroupRemoveMember', `(RTS_HANDLE hGroup, RTS_HANDLE hGroupMember)')

/**
 * <description>Explicitly enforce the usage of user authentication: no anonymous login is possible, login with user and password is required
 * NOTE: The UserDB is enforced implicitly when a DB file is loaded or configured via CODESYS.
 * </description>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User and password login is required</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Anonymous login is possible</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 */
 DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBEnforce', `(void)')

/* --------- Group management ------------------------------------------------ */
/* This section of functions is MANDATORY for the user management!             */

/* Group iteration */

/**
 * <description>Iteration interface to get the first configured user group</description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">First user group available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No user group configured</errorcode>
 * <result>Handle to the first user group or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBGroupGetFirst', `(RTS_RESULT *pResult)')

/**
 * <description>Iteration interface to get next configured user group. Must be started with UserDBGroupGetFirst()</description>
 * <param name="hPrevGroup" type="IN">Handle to the previous user group retrieved via UserDBGroupGetFirst() or subsequent calls of UserDBGroupGetNext()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Next user group available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No next user group available</errorcode>
 * <result>Handle to the next user group or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBGroupGetNext', `(RTS_HANDLE hPrevGroup, RTS_RESULT *pResult)')

/* Single group access */

/**
 * <description>Open user group specified by its name</description>
 * <param name="pszGroup" type="IN">User group name</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User group could be opened</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter. pszGroup = NULL or empty</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <result>Handle to the user group or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBGroupOpen', `(char *pszGroup, RTS_RESULT *pResult)')

/**
 * <description>Close a user group</description>
 * <param name="hGroup" type="IN">Handle to the user group</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User group could be closed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user group handle</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBGroupClose', `(RTS_HANDLE hGroup)')

/**
 * <description>Get user group name</description>
 * <param name="hGroup" type="IN">Handle to the user group</param>
 * <param name="pszGroup" type="OUT">Pointer to get user group name</param>
 * <param name="piMaxLen" type="INOUT">Pointer to length of buffer in pszGroup. If pszGroup = NULL, only the length of the user group name is returned in *piMaxLen</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User group name is returned</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user group handle or pszGroup = NULL and piMaxLen = NULL</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBGroupGetName', `(RTS_HANDLE hGroup, char *pszGroup, int *piMaxLen)')

/**
 * <description>Get properties of a group</description>
 * <param name="hGroup" type="IN">Handle to the group</param>
 * <param name="pulProperty" type="OUT">Pointer to return the properties. For details see category "UserDB properties"</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Properties could be retrieved</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user group or property pointer = NULL</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBGroupGetProperty', `(RTS_HANDLE hGroup, RTS_UI32 *pulProperty)')

/**
 * <description>Check if the user is a member of the group</description>
 * <param name="hGroup" type="IN">Handle to the user group</param>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User is a member of the group</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user or user group handle</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">User is no member of the specified user group</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBGroupHasUser', `(RTS_HANDLE hGroup, RTS_HANDLE hUser)')

/**
 * <description>Iteration interface to get the first user of the user group</description>
 * <param name="hGroup" type="IN">Handle to the user group</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">First user in the group available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No user configured in the user group</errorcode>
 * <result>Handle to the first user in the user group or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBGroupGetFirstUser', `(RTS_HANDLE hGroup, RTS_RESULT *pResult)')

/**
 * <description>Iteration interface to get next configured user of the user group. Must be started with UserDBGroupGetFirstUser()</description>
 * <param name="hGroup" type="IN">Handle to the user group</param>
 * <param name="hPrevUser" type="IN">Handle to the previous user retrieved via UserDBGroupGetFirstUser() or subsequent calls of UserDBGroupGetNextUser()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Next user available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handles</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No next user available</errorcode>
 * <result>Handle to the next user or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBGroupGetNextUser', `(RTS_HANDLE hGroup, RTS_HANDLE hPrevUser, RTS_RESULT *pResult)')

/**
 * <description>Check if a user group is a member of the first specified group</description>
 * <param name="hGroup" type="IN">Handle to the first user group</param>
 * <param name="hGroupMember" type="IN">Handle to the user group to check if it is a member of hGroup</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User group is a member of the first group</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user group handles</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">User group is no member of the specified user group</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBGroupHasMember', `(RTS_HANDLE hGroup, RTS_HANDLE hGroupMember)')

/**
 * <description>Iteration interface to get the first user group as member of the specified group</description>
 * <param name="hGroup" type="IN">Handle to the user group</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">First user group member available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user group handle</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No user group configured</errorcode>
 * <result>Handle to the first user group member or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBGroupGetFirstMember', `(RTS_HANDLE hGroup, RTS_RESULT *pResult)')

/**
 * <description>Iteration interface to get next configured user group as member of the specified group. Must be started with UserDBGroupGetFirstMember()</description>
 * <param name="hGroup" type="IN">Handle to the user group</param>
 * <param name="hPrevGroupMember" type="IN">Handle to the previous user group retrieved via UserDBGroupGetFirstMember() or subsequent calls of UserDBGroupGetNextMember()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Next user group member available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No next user group member available</errorcode>
 * <result>Handle to the next user group member or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBGroupGetNextMember', `(RTS_HANDLE hGroup, RTS_HANDLE hPrevGroupMember, RTS_RESULT *pResult)')


#ifdef __cplusplus
}
#endif
