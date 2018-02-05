 /**
 * <interfacename>CmpUserDBObjects</interfacename>
 * <description> 
 *	Interface for the user rights management database.
 *
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

SET_INTERFACE_NAME(`CmpUserDBObjects')

#include "CmpItf.h"

/**
 * <category>Static defines</category>
 * <description>Number of objects at startup</description>
 */
#ifndef USERDB_NUM_OF_STATIC_OBJECTS
	#define USERDB_NUM_OF_STATIC_OBJECTS		6
#endif

/**
 * <category>Static defines</category>
 * <description>Number of usergroup specific rights at startup</description>
 */
#ifndef USERDB_NUM_OF_STATIC_GROUPRIGHTS
	#define USERDB_NUM_OF_STATIC_GROUPRIGHTS	10
#endif

/**
 * <category>Group rights entry</category>
 * <description>
 *	Entry to store the rights in a specified group.
 * </description>
 * <element name="hGroup" type="IN">Handle to the group</element>
 * <element name="ulRights" type="IN">Rights of the group</element>
 * <element name="ulDeniedRights" type="IN">Denied rights of the group</element>
 */
typedef struct tagGroupRightsEntry
{
	RTS_HANDLE hGroup;
	RTS_UI32 ulRights;
	RTS_UI32 ulDeniedRights;
} GroupRightsEntry;

/**
 * <category>Object entry</category>
 * <description>
 *	Entry to store an object in the object tree.
 * </description>
 * <element name="pszObject" type="IN">Name of the object</element>
 * <element name="hFatherObject" type="IN">Handle of the father object</element>
 * <element name="hGroupRightsList" type="IN">Handle to a memory pool to store the list of all usergroups on which rights are explicitly assigned to the object</element>
 * <element name="ulID" type="IN">ID of the object</element>
 * <element name="ulUsedRights" type="IN">Rights that are in use</element>
 */
typedef struct tagObjectEntry
{
	char *pszObject;
	RTS_HANDLE hFatherObject;
	RTS_HANDLE hGroupRightsList;
	RTS_UI32 ulID;
	RTS_UI32 ulUsedRights;
} ObjectEntry;

#ifdef __cplusplus
extern "C" {
#endif

/* --------- Objects and Rights management configuration --------------------- */
/* This section of functions is MANDATORY and must be implemented			   */

/**
 * <description>Load the user rights database into memory</description>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Succeeded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Error loading user rights database</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Is not implemented perhaps the UserDBRights is fix</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBRightsLoad', `(void)')

/**
 * <description>Storing the current user rights management into permanent database file</description>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Succeeded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Error storing user rights database</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Is not implemented perhaps the UserDBRights is fix</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBRightsStore', `(void)')

/**
 * <description>Release user rights management in memory. NOTE: The database file is not removed!</description>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Succeeded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Failed releasing user rights management</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Is not implemented perhaps the UserDBRights is fix</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBRightsRelease', `(void)')

/* Objects management configuration */

/**
 * <description>
 *	Add a new object to the object management, so the access rights can be configured on that object.
 *	NOTE:
 *	The name of the object must include the full namespace with "Device" as the root node, e.g. "Device.MyObject" or if it's a filesystem object with "/" as the root node.
 * </description>
 * <param name="pszObject" type="IN">Full object name (see object tree)</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Object could be added</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Object invalid = NULL or empty</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">If memory could not be allocated to store this object</errorcode>
 * <result>Handle to the object or RTS_INVALID_HANDLE if it could not be added</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBObjectAdd', `(char *pszObject, RTS_RESULT *pResult)')

/**
 * <description>Remove an object from the object management and all its children</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Object could be removed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid object handle</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBObjectRemove', `(RTS_HANDLE hObject)')

/**
 * <description>
 *	Add a new object under a father object specified by its name to the object management, so the access rights can be configured on that object.
 * </description>
 * <param name="hFatherObject" type="IN">Handle to the father object, under which the object will be added</param>
 * <param name="pszObject" type="IN">Object name (see object tree)</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Object could be added</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Object invalid = NULL or empty</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">If memory could not be allocated to store this object</errorcode>
 * <result>Handle to the object or RTS_INVALID_HANDLE if it could not be added</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBObjectAddChild', `(RTS_HANDLE hFatherObject, char *pszObject, RTS_RESULT *pResult)')

/**
 * <description>
 *	Set the used access rights for the object specified by handle.
 *	The rights are additionally stored in an internal list. In case USERDB_RIGHT_NONE is passed for ulUsedRights the previously stored rights are retrieved for this object.
 * </description>
 * <param name="hObject" type="IN">Handle to the object</param>
 * <param name="ulUsedRights" type="IN">Used access rights or USERDB_RIGHT_NONE for retrieval</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Rights are successfully set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid object handle</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">Object was not found for rights retrieval</errorcode>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBObjectSetUsedRights', `(RTS_HANDLE hObject, RTS_UI32 ulUsedRights)')

/**
 * <description>
 *	Get the used access rights for the object specified by handle.
 *	NOTE: In case the used rights are not set the function returns USERDB_RIGHT_ALL.
 * </description>
 * <param name="hObject" type="IN">Handle to the object</param>
 * <param name="pulUsedRights" type="OUT">Pointer to used access rights</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Rights are successfully set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid object handle or invalid pointer</errorcode>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBObjectGetUsedRights', `(RTS_HANDLE hObject, RTS_UI32 *pulUsedRights)')

/**
 * <description>Get a unique identifier of an object</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <param name="pulID" type="OUT">Pointer to get the ObjectID</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">ObjectID could be retrieved</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid object handle</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBObjectGetID', `(RTS_HANDLE hObject, RTS_UI32 *pulID)')

/**
 * <description>Set a unique identifier of an object</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <param name="ulID" type="IN">ObjectID to set</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">ObjectID could be set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid object handle</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBObjectSetID', `(RTS_HANDLE hObject, RTS_UI32 ulID)')

/* Rights management configuration */

/**
 * <description>Add a group to the specified object to manage access rights</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <param name="hGroup" type="IN">Handle to the group that should be attached</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Group could be added or is already added</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handles</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">No memory to add group</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBObjectAddGroup', `(RTS_HANDLE hObject, RTS_HANDLE hGroup)')

/**
 * <description>Remove a group from the specified object</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <param name="hGroup" type="IN">Handle to the group that should be removed</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Group could be removed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handles</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBObjectRemoveGroup', `(RTS_HANDLE hObject, RTS_HANDLE hGroup)')

/**
 * <description>Set the access rights for the group at the specified object</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <param name="hGroup" type="IN">Handle to the group</param>
 * <element name="ulRights" type="IN">Rights of the group. See category "User rights" for details</element>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Access rights could be set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handles</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBObjectSetGroupRights', `(RTS_HANDLE hObject, RTS_HANDLE hGroup, RTS_UI32 ulRights)')

/**
 * <description>Set the denied access rights for the group at the specified object</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <param name="hGroup" type="IN">Handle to the group</param>
 * <element name="ulDeniedRights" type="IN">Denied rights of the group. See category "User rights" for details</element>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Access rights could be set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handles</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBObjectSetGroupDeniedRights', `(RTS_HANDLE hObject, RTS_HANDLE hGroup, RTS_UI32 ulDeniedRights)')


/* --------- Objects and Rights managament ---------------------------------- */
/* This section of functions is MANDATORY and must be implemented			  */

/* Object iteration */

/**
 * <description>Iteration interface to get the first object of the user rights management</description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">First object of the user rights management available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No object available</errorcode>
 * <result>Handle to the first object in the user rights management or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBObjectGetFirst', `(RTS_RESULT *pResult)')

/**
 * <description>Iteration interface to get next object of the user rights management. Must be started with UserDBObjectGetFirst()</description>
 * <param name="hPrevObject" type="IN">Handle to the previous object retrieved via UserDBObjectGetFirst() or subsequent calls of UserDBObjectGetNext()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Next object available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handles</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No next object available</errorcode>
 * <result>Handle to the next object in the user rights management or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBObjectGetNext', `(RTS_HANDLE hPrevObject, RTS_RESULT *pResult)')

/* Single object access */

/**
 * <description>Open object specified by its name</description>
 * <param name="pszObject" type="IN">Full object name (see object tree)</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Object could be opened</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter. pszObject = NULL or empty</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <result>Handle to the object or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBObjectOpen', `(char *pszObject, RTS_RESULT *pResult)')

/**
 * <description>Close an object</description>
 * <param name="hObject" type="IN">Handle to the object</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Object could be closed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid object handle</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBObjectClose', `(RTS_HANDLE hObject)')

/**
 * <description>Get object name</description>
 * <param name="hObject" type="IN">Handle to the object</param>
 * <param name="pszObject" type="OUT">Pointer to get object name</param>
 * <param name="piMaxLen" type="INOUT">Pointer to length of buffer in pszObject. If pszObject = NULL, only the length of the object name is returned in *piMaxLen</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Object name is returned</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid object handle or pszObject = NULL and piMaxLen = NULL</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBObjectGetName', `(RTS_HANDLE hObject, char *pszObject, int *piMaxLen)')

/**
 * <description>Get the complete object path name</description>
 * <param name="hObject" type="IN">Handle to the object</param>
 * <param name="pszObject" type="IN">Full object path name (see object tree)</param>
 * <param name="piMaxLen" type="INOUT">Pointer to length of buffer in pszObject. If pszObject = NULL, only the length of the object name is returned in *piMaxLen</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Object name is returned</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid object handle or pszObject = NULL and piMaxLen = NULL</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBObjectGetPath', `(RTS_HANDLE hObject, char *pszObject, int *piMaxLen)')

/**
 * <description>Get first child object in object tree of the specified father object</description>
 * <param name="hFatherObject" type="IN">Handle to the father object</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">First child object available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter hFatherObject</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <result>Handle to the child object or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBObjectGetFirstChild', `(RTS_HANDLE hFatherObject, RTS_RESULT *pResult)')

/**
 * <description>Get next child object in object tree of the specified father object. Must be started with UserDBObjectGetFirstChild()</description>
 * <param name="hFatherObject" type="IN">Handle to the father object</param>
 * <param name="hPrevChildObject" type="IN">Handle to the previous child object retrieved by UserDBObjectGetFirstChild() or subsequent calls of UserDBObjectGetNextChild()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Next child object available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter hFatherObject or hPrevChildObject</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <result>Handle to the next child object or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBObjectGetNextChild', `(RTS_HANDLE hFatherObject, RTS_HANDLE hPrevChildObject, RTS_RESULT *pResult)')

/**
 * <description>Get the father object in object tree of the specified child object</description>
 * <param name="hChildObject" type="IN">Handle to the child object</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Father object could be retrieved</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter hChildObject</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <result>Handle to the father/parent object or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBObjectGetFather', `(RTS_HANDLE hChildObject, RTS_RESULT *pResult)')

/* Iteration over all groups that are assigned to the object */

/**
 * <description>Iteration interface to get the first group in the user rights management of the specified object</description>
 * <param name="hObject" type="IN">Handle to the object</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">First group available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No group available</errorcode>
 * <result>Handle to the first group of the object in the user rights management or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBObjectGetFirstGroup', `(RTS_HANDLE hObject, RTS_RESULT *pResult)')

/**
 * <description>Iteration interface to get next group in the user rights management of the specified object. Must be started with UserDBObjectGetFirstGroup()</description>
 * <param name="hObject" type="IN">Handle to the object</param>
 * <param name="hPrevGroup" type="IN">Handle to the previous group retrieved via UserDBObjectGetFirstGroup() or subsequent calls of UserDBObjectGetNextGroup()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Next group available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handles</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No next group available</errorcode>
 * <result>Handle to the next group of the object in the user rights management or RTS_INVALID_HANDLE if failed</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserDBObjectGetNextGroup', `(RTS_HANDLE hObject, RTS_HANDLE hPrevGroup, RTS_RESULT *pResult)')

/* Get rights */

/**
 * <description>Get the rights and the denied rights of a group on a specified object</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <param name="hGroup" type="IN">Handle to the group which access rights are requested</param>
 * <element name="pulRights" type="IN">Pointer to get rights of the group. See category "User rights" for details</element>
 * <element name="pulDeniedRights" type="IN">Pointer to get denied rights of the group. See category "User rights" for details</element>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Access rights could be retrieved</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handles</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBObjectGetGroupRights', `(RTS_HANDLE hObject, RTS_HANDLE hGroup, RTS_UI32 *pulRights, RTS_UI32 *pulDeniedRights)')

/**
 * <description>Check access rights of a user on an object (authorization)</description>
 * <param name="pszObject" type="IN">Full object name (see object tree)</param>
 * <param name="hUser" type="IN">Handle to the user which access rights are checked</param>
 * <element name="ulRequestedRights" type="IN">Requested access rights. See category "User rights" for details</element>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Access permitted</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Access rights could not be retrieved, so no access rights!</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_ACCESS_RIGHTS">No access rights!</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBObjectHasRights', `(char *pszObject, RTS_HANDLE hUser, RTS_UI32 ulRequestedRights)')

/**
 * <description>Get the rights and the denied rights of a user on a specified object</description>
 * <param name="pszObject" type="IN">Full object name (see object tree)</param>
 * <param name="hUser" type="IN">Handle to the user which access rights are requested</param>
 * <element name="pulRights" type="IN">Pointer to get rights of the user. See category "User rights" for details</element>
 * <element name="pulDeniedRights" type="IN">Pointer to get denied rights of the user. See category "User rights" for details</element>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Access rights could be retrieved</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handles</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBObjectGetRights', `(char *pszObject, RTS_HANDLE hUser, RTS_UI32 *pulRights, RTS_UI32 *pulDeniedRights)')

/**
 * <description>Explicitly activate the usage of user authentication: no assuming of administrator rights
 * NOTE: The UserDBObjects is activated implicitly when a DB file is loaded or configured via CODESYS.
 * </description>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Activation was successful</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserDBObjectsActivate', `(void)')

#ifdef __cplusplus
}
#endif
