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


	
	
#ifndef _CMPUSERDBOBJECTSITF_H_
#define _CMPUSERDBOBJECTSITF_H_

#include "CmpStd.h"

 

 




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
RTS_RESULT CDECL UserDBRightsLoad(void);
typedef RTS_RESULT (CDECL * PFUSERDBRIGHTSLOAD) (void);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBRIGHTSLOAD_NOTIMPLEMENTED)
	#define USE_UserDBRightsLoad
	#define EXT_UserDBRightsLoad
	#define GET_UserDBRightsLoad(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBRightsLoad()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBRightsLoad  FALSE
	#define EXP_UserDBRightsLoad  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBRightsLoad
	#define EXT_UserDBRightsLoad
	#define GET_UserDBRightsLoad(fl)  CAL_CMGETAPI( "UserDBRightsLoad" ) 
	#define CAL_UserDBRightsLoad  UserDBRightsLoad
	#define CHK_UserDBRightsLoad  TRUE
	#define EXP_UserDBRightsLoad  CAL_CMEXPAPI( "UserDBRightsLoad" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBRightsLoad
	#define EXT_UserDBRightsLoad
	#define GET_UserDBRightsLoad(fl)  CAL_CMGETAPI( "UserDBRightsLoad" ) 
	#define CAL_UserDBRightsLoad  UserDBRightsLoad
	#define CHK_UserDBRightsLoad  TRUE
	#define EXP_UserDBRightsLoad  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBRightsLoad", (RTS_UINTPTR)UserDBRightsLoad, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBRightsLoad
	#define EXT_CmpUserDBObjectsUserDBRightsLoad
	#define GET_CmpUserDBObjectsUserDBRightsLoad  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBRightsLoad pICmpUserDBObjects->IUserDBRightsLoad
	#define CHK_CmpUserDBObjectsUserDBRightsLoad (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBRightsLoad  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBRightsLoad
	#define EXT_UserDBRightsLoad
	#define GET_UserDBRightsLoad(fl)  CAL_CMGETAPI( "UserDBRightsLoad" ) 
	#define CAL_UserDBRightsLoad pICmpUserDBObjects->IUserDBRightsLoad
	#define CHK_UserDBRightsLoad (pICmpUserDBObjects != NULL)
	#define EXP_UserDBRightsLoad  CAL_CMEXPAPI( "UserDBRightsLoad" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBRightsLoad  PFUSERDBRIGHTSLOAD pfUserDBRightsLoad;
	#define EXT_UserDBRightsLoad  extern PFUSERDBRIGHTSLOAD pfUserDBRightsLoad;
	#define GET_UserDBRightsLoad(fl)  s_pfCMGetAPI2( "UserDBRightsLoad", (RTS_VOID_FCTPTR *)&pfUserDBRightsLoad, (fl), 0, 0)
	#define CAL_UserDBRightsLoad  pfUserDBRightsLoad
	#define CHK_UserDBRightsLoad  (pfUserDBRightsLoad != NULL)
	#define EXP_UserDBRightsLoad  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBRightsLoad", (RTS_UINTPTR)UserDBRightsLoad, 0, 0) 
#endif




/**
 * <description>Storing the current user rights management into permanent database file</description>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Succeeded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Error storing user rights database</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Is not implemented perhaps the UserDBRights is fix</errorcode>
 */
RTS_RESULT CDECL UserDBRightsStore(void);
typedef RTS_RESULT (CDECL * PFUSERDBRIGHTSSTORE) (void);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBRIGHTSSTORE_NOTIMPLEMENTED)
	#define USE_UserDBRightsStore
	#define EXT_UserDBRightsStore
	#define GET_UserDBRightsStore(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBRightsStore()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBRightsStore  FALSE
	#define EXP_UserDBRightsStore  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBRightsStore
	#define EXT_UserDBRightsStore
	#define GET_UserDBRightsStore(fl)  CAL_CMGETAPI( "UserDBRightsStore" ) 
	#define CAL_UserDBRightsStore  UserDBRightsStore
	#define CHK_UserDBRightsStore  TRUE
	#define EXP_UserDBRightsStore  CAL_CMEXPAPI( "UserDBRightsStore" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBRightsStore
	#define EXT_UserDBRightsStore
	#define GET_UserDBRightsStore(fl)  CAL_CMGETAPI( "UserDBRightsStore" ) 
	#define CAL_UserDBRightsStore  UserDBRightsStore
	#define CHK_UserDBRightsStore  TRUE
	#define EXP_UserDBRightsStore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBRightsStore", (RTS_UINTPTR)UserDBRightsStore, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBRightsStore
	#define EXT_CmpUserDBObjectsUserDBRightsStore
	#define GET_CmpUserDBObjectsUserDBRightsStore  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBRightsStore pICmpUserDBObjects->IUserDBRightsStore
	#define CHK_CmpUserDBObjectsUserDBRightsStore (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBRightsStore  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBRightsStore
	#define EXT_UserDBRightsStore
	#define GET_UserDBRightsStore(fl)  CAL_CMGETAPI( "UserDBRightsStore" ) 
	#define CAL_UserDBRightsStore pICmpUserDBObjects->IUserDBRightsStore
	#define CHK_UserDBRightsStore (pICmpUserDBObjects != NULL)
	#define EXP_UserDBRightsStore  CAL_CMEXPAPI( "UserDBRightsStore" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBRightsStore  PFUSERDBRIGHTSSTORE pfUserDBRightsStore;
	#define EXT_UserDBRightsStore  extern PFUSERDBRIGHTSSTORE pfUserDBRightsStore;
	#define GET_UserDBRightsStore(fl)  s_pfCMGetAPI2( "UserDBRightsStore", (RTS_VOID_FCTPTR *)&pfUserDBRightsStore, (fl), 0, 0)
	#define CAL_UserDBRightsStore  pfUserDBRightsStore
	#define CHK_UserDBRightsStore  (pfUserDBRightsStore != NULL)
	#define EXP_UserDBRightsStore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBRightsStore", (RTS_UINTPTR)UserDBRightsStore, 0, 0) 
#endif




/**
 * <description>Release user rights management in memory. NOTE: The database file is not removed!</description>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Succeeded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Failed releasing user rights management</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Is not implemented perhaps the UserDBRights is fix</errorcode>
 */
RTS_RESULT CDECL UserDBRightsRelease(void);
typedef RTS_RESULT (CDECL * PFUSERDBRIGHTSRELEASE) (void);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBRIGHTSRELEASE_NOTIMPLEMENTED)
	#define USE_UserDBRightsRelease
	#define EXT_UserDBRightsRelease
	#define GET_UserDBRightsRelease(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBRightsRelease()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBRightsRelease  FALSE
	#define EXP_UserDBRightsRelease  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBRightsRelease
	#define EXT_UserDBRightsRelease
	#define GET_UserDBRightsRelease(fl)  CAL_CMGETAPI( "UserDBRightsRelease" ) 
	#define CAL_UserDBRightsRelease  UserDBRightsRelease
	#define CHK_UserDBRightsRelease  TRUE
	#define EXP_UserDBRightsRelease  CAL_CMEXPAPI( "UserDBRightsRelease" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBRightsRelease
	#define EXT_UserDBRightsRelease
	#define GET_UserDBRightsRelease(fl)  CAL_CMGETAPI( "UserDBRightsRelease" ) 
	#define CAL_UserDBRightsRelease  UserDBRightsRelease
	#define CHK_UserDBRightsRelease  TRUE
	#define EXP_UserDBRightsRelease  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBRightsRelease", (RTS_UINTPTR)UserDBRightsRelease, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBRightsRelease
	#define EXT_CmpUserDBObjectsUserDBRightsRelease
	#define GET_CmpUserDBObjectsUserDBRightsRelease  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBRightsRelease pICmpUserDBObjects->IUserDBRightsRelease
	#define CHK_CmpUserDBObjectsUserDBRightsRelease (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBRightsRelease  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBRightsRelease
	#define EXT_UserDBRightsRelease
	#define GET_UserDBRightsRelease(fl)  CAL_CMGETAPI( "UserDBRightsRelease" ) 
	#define CAL_UserDBRightsRelease pICmpUserDBObjects->IUserDBRightsRelease
	#define CHK_UserDBRightsRelease (pICmpUserDBObjects != NULL)
	#define EXP_UserDBRightsRelease  CAL_CMEXPAPI( "UserDBRightsRelease" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBRightsRelease  PFUSERDBRIGHTSRELEASE pfUserDBRightsRelease;
	#define EXT_UserDBRightsRelease  extern PFUSERDBRIGHTSRELEASE pfUserDBRightsRelease;
	#define GET_UserDBRightsRelease(fl)  s_pfCMGetAPI2( "UserDBRightsRelease", (RTS_VOID_FCTPTR *)&pfUserDBRightsRelease, (fl), 0, 0)
	#define CAL_UserDBRightsRelease  pfUserDBRightsRelease
	#define CHK_UserDBRightsRelease  (pfUserDBRightsRelease != NULL)
	#define EXP_UserDBRightsRelease  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBRightsRelease", (RTS_UINTPTR)UserDBRightsRelease, 0, 0) 
#endif




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
RTS_HANDLE CDECL UserDBObjectAdd(char *pszObject, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBOBJECTADD) (char *pszObject, RTS_RESULT *pResult);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTADD_NOTIMPLEMENTED)
	#define USE_UserDBObjectAdd
	#define EXT_UserDBObjectAdd
	#define GET_UserDBObjectAdd(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectAdd(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBObjectAdd  FALSE
	#define EXP_UserDBObjectAdd  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectAdd
	#define EXT_UserDBObjectAdd
	#define GET_UserDBObjectAdd(fl)  CAL_CMGETAPI( "UserDBObjectAdd" ) 
	#define CAL_UserDBObjectAdd  UserDBObjectAdd
	#define CHK_UserDBObjectAdd  TRUE
	#define EXP_UserDBObjectAdd  CAL_CMEXPAPI( "UserDBObjectAdd" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectAdd
	#define EXT_UserDBObjectAdd
	#define GET_UserDBObjectAdd(fl)  CAL_CMGETAPI( "UserDBObjectAdd" ) 
	#define CAL_UserDBObjectAdd  UserDBObjectAdd
	#define CHK_UserDBObjectAdd  TRUE
	#define EXP_UserDBObjectAdd  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectAdd", (RTS_UINTPTR)UserDBObjectAdd, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectAdd
	#define EXT_CmpUserDBObjectsUserDBObjectAdd
	#define GET_CmpUserDBObjectsUserDBObjectAdd  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectAdd pICmpUserDBObjects->IUserDBObjectAdd
	#define CHK_CmpUserDBObjectsUserDBObjectAdd (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectAdd  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectAdd
	#define EXT_UserDBObjectAdd
	#define GET_UserDBObjectAdd(fl)  CAL_CMGETAPI( "UserDBObjectAdd" ) 
	#define CAL_UserDBObjectAdd pICmpUserDBObjects->IUserDBObjectAdd
	#define CHK_UserDBObjectAdd (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectAdd  CAL_CMEXPAPI( "UserDBObjectAdd" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectAdd  PFUSERDBOBJECTADD pfUserDBObjectAdd;
	#define EXT_UserDBObjectAdd  extern PFUSERDBOBJECTADD pfUserDBObjectAdd;
	#define GET_UserDBObjectAdd(fl)  s_pfCMGetAPI2( "UserDBObjectAdd", (RTS_VOID_FCTPTR *)&pfUserDBObjectAdd, (fl), 0, 0)
	#define CAL_UserDBObjectAdd  pfUserDBObjectAdd
	#define CHK_UserDBObjectAdd  (pfUserDBObjectAdd != NULL)
	#define EXP_UserDBObjectAdd  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectAdd", (RTS_UINTPTR)UserDBObjectAdd, 0, 0) 
#endif




/**
 * <description>Remove an object from the object management and all its children</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Object could be removed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid object handle</errorcode>
 */
RTS_RESULT CDECL UserDBObjectRemove(RTS_HANDLE hObject);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTREMOVE) (RTS_HANDLE hObject);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTREMOVE_NOTIMPLEMENTED)
	#define USE_UserDBObjectRemove
	#define EXT_UserDBObjectRemove
	#define GET_UserDBObjectRemove(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectRemove(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectRemove  FALSE
	#define EXP_UserDBObjectRemove  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectRemove
	#define EXT_UserDBObjectRemove
	#define GET_UserDBObjectRemove(fl)  CAL_CMGETAPI( "UserDBObjectRemove" ) 
	#define CAL_UserDBObjectRemove  UserDBObjectRemove
	#define CHK_UserDBObjectRemove  TRUE
	#define EXP_UserDBObjectRemove  CAL_CMEXPAPI( "UserDBObjectRemove" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectRemove
	#define EXT_UserDBObjectRemove
	#define GET_UserDBObjectRemove(fl)  CAL_CMGETAPI( "UserDBObjectRemove" ) 
	#define CAL_UserDBObjectRemove  UserDBObjectRemove
	#define CHK_UserDBObjectRemove  TRUE
	#define EXP_UserDBObjectRemove  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectRemove", (RTS_UINTPTR)UserDBObjectRemove, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectRemove
	#define EXT_CmpUserDBObjectsUserDBObjectRemove
	#define GET_CmpUserDBObjectsUserDBObjectRemove  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectRemove pICmpUserDBObjects->IUserDBObjectRemove
	#define CHK_CmpUserDBObjectsUserDBObjectRemove (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectRemove  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectRemove
	#define EXT_UserDBObjectRemove
	#define GET_UserDBObjectRemove(fl)  CAL_CMGETAPI( "UserDBObjectRemove" ) 
	#define CAL_UserDBObjectRemove pICmpUserDBObjects->IUserDBObjectRemove
	#define CHK_UserDBObjectRemove (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectRemove  CAL_CMEXPAPI( "UserDBObjectRemove" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectRemove  PFUSERDBOBJECTREMOVE pfUserDBObjectRemove;
	#define EXT_UserDBObjectRemove  extern PFUSERDBOBJECTREMOVE pfUserDBObjectRemove;
	#define GET_UserDBObjectRemove(fl)  s_pfCMGetAPI2( "UserDBObjectRemove", (RTS_VOID_FCTPTR *)&pfUserDBObjectRemove, (fl), 0, 0)
	#define CAL_UserDBObjectRemove  pfUserDBObjectRemove
	#define CHK_UserDBObjectRemove  (pfUserDBObjectRemove != NULL)
	#define EXP_UserDBObjectRemove  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectRemove", (RTS_UINTPTR)UserDBObjectRemove, 0, 0) 
#endif




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
RTS_HANDLE CDECL UserDBObjectAddChild(RTS_HANDLE hFatherObject, char *pszObject, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBOBJECTADDCHILD) (RTS_HANDLE hFatherObject, char *pszObject, RTS_RESULT *pResult);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTADDCHILD_NOTIMPLEMENTED)
	#define USE_UserDBObjectAddChild
	#define EXT_UserDBObjectAddChild
	#define GET_UserDBObjectAddChild(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectAddChild(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBObjectAddChild  FALSE
	#define EXP_UserDBObjectAddChild  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectAddChild
	#define EXT_UserDBObjectAddChild
	#define GET_UserDBObjectAddChild(fl)  CAL_CMGETAPI( "UserDBObjectAddChild" ) 
	#define CAL_UserDBObjectAddChild  UserDBObjectAddChild
	#define CHK_UserDBObjectAddChild  TRUE
	#define EXP_UserDBObjectAddChild  CAL_CMEXPAPI( "UserDBObjectAddChild" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectAddChild
	#define EXT_UserDBObjectAddChild
	#define GET_UserDBObjectAddChild(fl)  CAL_CMGETAPI( "UserDBObjectAddChild" ) 
	#define CAL_UserDBObjectAddChild  UserDBObjectAddChild
	#define CHK_UserDBObjectAddChild  TRUE
	#define EXP_UserDBObjectAddChild  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectAddChild", (RTS_UINTPTR)UserDBObjectAddChild, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectAddChild
	#define EXT_CmpUserDBObjectsUserDBObjectAddChild
	#define GET_CmpUserDBObjectsUserDBObjectAddChild  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectAddChild pICmpUserDBObjects->IUserDBObjectAddChild
	#define CHK_CmpUserDBObjectsUserDBObjectAddChild (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectAddChild  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectAddChild
	#define EXT_UserDBObjectAddChild
	#define GET_UserDBObjectAddChild(fl)  CAL_CMGETAPI( "UserDBObjectAddChild" ) 
	#define CAL_UserDBObjectAddChild pICmpUserDBObjects->IUserDBObjectAddChild
	#define CHK_UserDBObjectAddChild (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectAddChild  CAL_CMEXPAPI( "UserDBObjectAddChild" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectAddChild  PFUSERDBOBJECTADDCHILD pfUserDBObjectAddChild;
	#define EXT_UserDBObjectAddChild  extern PFUSERDBOBJECTADDCHILD pfUserDBObjectAddChild;
	#define GET_UserDBObjectAddChild(fl)  s_pfCMGetAPI2( "UserDBObjectAddChild", (RTS_VOID_FCTPTR *)&pfUserDBObjectAddChild, (fl), 0, 0)
	#define CAL_UserDBObjectAddChild  pfUserDBObjectAddChild
	#define CHK_UserDBObjectAddChild  (pfUserDBObjectAddChild != NULL)
	#define EXP_UserDBObjectAddChild  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectAddChild", (RTS_UINTPTR)UserDBObjectAddChild, 0, 0) 
#endif




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
RTS_RESULT CDECL UserDBObjectSetUsedRights(RTS_HANDLE hObject, RTS_UI32 ulUsedRights);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTSETUSEDRIGHTS) (RTS_HANDLE hObject, RTS_UI32 ulUsedRights);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTSETUSEDRIGHTS_NOTIMPLEMENTED)
	#define USE_UserDBObjectSetUsedRights
	#define EXT_UserDBObjectSetUsedRights
	#define GET_UserDBObjectSetUsedRights(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectSetUsedRights(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectSetUsedRights  FALSE
	#define EXP_UserDBObjectSetUsedRights  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectSetUsedRights
	#define EXT_UserDBObjectSetUsedRights
	#define GET_UserDBObjectSetUsedRights(fl)  CAL_CMGETAPI( "UserDBObjectSetUsedRights" ) 
	#define CAL_UserDBObjectSetUsedRights  UserDBObjectSetUsedRights
	#define CHK_UserDBObjectSetUsedRights  TRUE
	#define EXP_UserDBObjectSetUsedRights  CAL_CMEXPAPI( "UserDBObjectSetUsedRights" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectSetUsedRights
	#define EXT_UserDBObjectSetUsedRights
	#define GET_UserDBObjectSetUsedRights(fl)  CAL_CMGETAPI( "UserDBObjectSetUsedRights" ) 
	#define CAL_UserDBObjectSetUsedRights  UserDBObjectSetUsedRights
	#define CHK_UserDBObjectSetUsedRights  TRUE
	#define EXP_UserDBObjectSetUsedRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectSetUsedRights", (RTS_UINTPTR)UserDBObjectSetUsedRights, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectSetUsedRights
	#define EXT_CmpUserDBObjectsUserDBObjectSetUsedRights
	#define GET_CmpUserDBObjectsUserDBObjectSetUsedRights  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectSetUsedRights pICmpUserDBObjects->IUserDBObjectSetUsedRights
	#define CHK_CmpUserDBObjectsUserDBObjectSetUsedRights (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectSetUsedRights  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectSetUsedRights
	#define EXT_UserDBObjectSetUsedRights
	#define GET_UserDBObjectSetUsedRights(fl)  CAL_CMGETAPI( "UserDBObjectSetUsedRights" ) 
	#define CAL_UserDBObjectSetUsedRights pICmpUserDBObjects->IUserDBObjectSetUsedRights
	#define CHK_UserDBObjectSetUsedRights (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectSetUsedRights  CAL_CMEXPAPI( "UserDBObjectSetUsedRights" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectSetUsedRights  PFUSERDBOBJECTSETUSEDRIGHTS pfUserDBObjectSetUsedRights;
	#define EXT_UserDBObjectSetUsedRights  extern PFUSERDBOBJECTSETUSEDRIGHTS pfUserDBObjectSetUsedRights;
	#define GET_UserDBObjectSetUsedRights(fl)  s_pfCMGetAPI2( "UserDBObjectSetUsedRights", (RTS_VOID_FCTPTR *)&pfUserDBObjectSetUsedRights, (fl), 0, 0)
	#define CAL_UserDBObjectSetUsedRights  pfUserDBObjectSetUsedRights
	#define CHK_UserDBObjectSetUsedRights  (pfUserDBObjectSetUsedRights != NULL)
	#define EXP_UserDBObjectSetUsedRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectSetUsedRights", (RTS_UINTPTR)UserDBObjectSetUsedRights, 0, 0) 
#endif




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
RTS_RESULT CDECL UserDBObjectGetUsedRights(RTS_HANDLE hObject, RTS_UI32 *pulUsedRights);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTGETUSEDRIGHTS) (RTS_HANDLE hObject, RTS_UI32 *pulUsedRights);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTGETUSEDRIGHTS_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetUsedRights
	#define EXT_UserDBObjectGetUsedRights
	#define GET_UserDBObjectGetUsedRights(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetUsedRights(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectGetUsedRights  FALSE
	#define EXP_UserDBObjectGetUsedRights  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetUsedRights
	#define EXT_UserDBObjectGetUsedRights
	#define GET_UserDBObjectGetUsedRights(fl)  CAL_CMGETAPI( "UserDBObjectGetUsedRights" ) 
	#define CAL_UserDBObjectGetUsedRights  UserDBObjectGetUsedRights
	#define CHK_UserDBObjectGetUsedRights  TRUE
	#define EXP_UserDBObjectGetUsedRights  CAL_CMEXPAPI( "UserDBObjectGetUsedRights" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectGetUsedRights
	#define EXT_UserDBObjectGetUsedRights
	#define GET_UserDBObjectGetUsedRights(fl)  CAL_CMGETAPI( "UserDBObjectGetUsedRights" ) 
	#define CAL_UserDBObjectGetUsedRights  UserDBObjectGetUsedRights
	#define CHK_UserDBObjectGetUsedRights  TRUE
	#define EXP_UserDBObjectGetUsedRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetUsedRights", (RTS_UINTPTR)UserDBObjectGetUsedRights, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectGetUsedRights
	#define EXT_CmpUserDBObjectsUserDBObjectGetUsedRights
	#define GET_CmpUserDBObjectsUserDBObjectGetUsedRights  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectGetUsedRights pICmpUserDBObjects->IUserDBObjectGetUsedRights
	#define CHK_CmpUserDBObjectsUserDBObjectGetUsedRights (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectGetUsedRights  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetUsedRights
	#define EXT_UserDBObjectGetUsedRights
	#define GET_UserDBObjectGetUsedRights(fl)  CAL_CMGETAPI( "UserDBObjectGetUsedRights" ) 
	#define CAL_UserDBObjectGetUsedRights pICmpUserDBObjects->IUserDBObjectGetUsedRights
	#define CHK_UserDBObjectGetUsedRights (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectGetUsedRights  CAL_CMEXPAPI( "UserDBObjectGetUsedRights" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetUsedRights  PFUSERDBOBJECTGETUSEDRIGHTS pfUserDBObjectGetUsedRights;
	#define EXT_UserDBObjectGetUsedRights  extern PFUSERDBOBJECTGETUSEDRIGHTS pfUserDBObjectGetUsedRights;
	#define GET_UserDBObjectGetUsedRights(fl)  s_pfCMGetAPI2( "UserDBObjectGetUsedRights", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetUsedRights, (fl), 0, 0)
	#define CAL_UserDBObjectGetUsedRights  pfUserDBObjectGetUsedRights
	#define CHK_UserDBObjectGetUsedRights  (pfUserDBObjectGetUsedRights != NULL)
	#define EXP_UserDBObjectGetUsedRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetUsedRights", (RTS_UINTPTR)UserDBObjectGetUsedRights, 0, 0) 
#endif




/**
 * <description>Get a unique identifier of an object</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <param name="pulID" type="OUT">Pointer to get the ObjectID</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">ObjectID could be retrieved</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid object handle</errorcode>
 */
RTS_RESULT CDECL UserDBObjectGetID(RTS_HANDLE hObject, RTS_UI32 *pulID);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTGETID) (RTS_HANDLE hObject, RTS_UI32 *pulID);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTGETID_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetID
	#define EXT_UserDBObjectGetID
	#define GET_UserDBObjectGetID(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetID(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectGetID  FALSE
	#define EXP_UserDBObjectGetID  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetID
	#define EXT_UserDBObjectGetID
	#define GET_UserDBObjectGetID(fl)  CAL_CMGETAPI( "UserDBObjectGetID" ) 
	#define CAL_UserDBObjectGetID  UserDBObjectGetID
	#define CHK_UserDBObjectGetID  TRUE
	#define EXP_UserDBObjectGetID  CAL_CMEXPAPI( "UserDBObjectGetID" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectGetID
	#define EXT_UserDBObjectGetID
	#define GET_UserDBObjectGetID(fl)  CAL_CMGETAPI( "UserDBObjectGetID" ) 
	#define CAL_UserDBObjectGetID  UserDBObjectGetID
	#define CHK_UserDBObjectGetID  TRUE
	#define EXP_UserDBObjectGetID  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetID", (RTS_UINTPTR)UserDBObjectGetID, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectGetID
	#define EXT_CmpUserDBObjectsUserDBObjectGetID
	#define GET_CmpUserDBObjectsUserDBObjectGetID  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectGetID pICmpUserDBObjects->IUserDBObjectGetID
	#define CHK_CmpUserDBObjectsUserDBObjectGetID (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectGetID  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetID
	#define EXT_UserDBObjectGetID
	#define GET_UserDBObjectGetID(fl)  CAL_CMGETAPI( "UserDBObjectGetID" ) 
	#define CAL_UserDBObjectGetID pICmpUserDBObjects->IUserDBObjectGetID
	#define CHK_UserDBObjectGetID (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectGetID  CAL_CMEXPAPI( "UserDBObjectGetID" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetID  PFUSERDBOBJECTGETID pfUserDBObjectGetID;
	#define EXT_UserDBObjectGetID  extern PFUSERDBOBJECTGETID pfUserDBObjectGetID;
	#define GET_UserDBObjectGetID(fl)  s_pfCMGetAPI2( "UserDBObjectGetID", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetID, (fl), 0, 0)
	#define CAL_UserDBObjectGetID  pfUserDBObjectGetID
	#define CHK_UserDBObjectGetID  (pfUserDBObjectGetID != NULL)
	#define EXP_UserDBObjectGetID  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetID", (RTS_UINTPTR)UserDBObjectGetID, 0, 0) 
#endif




/**
 * <description>Set a unique identifier of an object</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <param name="ulID" type="IN">ObjectID to set</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">ObjectID could be set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid object handle</errorcode>
 */
RTS_RESULT CDECL UserDBObjectSetID(RTS_HANDLE hObject, RTS_UI32 ulID);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTSETID) (RTS_HANDLE hObject, RTS_UI32 ulID);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTSETID_NOTIMPLEMENTED)
	#define USE_UserDBObjectSetID
	#define EXT_UserDBObjectSetID
	#define GET_UserDBObjectSetID(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectSetID(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectSetID  FALSE
	#define EXP_UserDBObjectSetID  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectSetID
	#define EXT_UserDBObjectSetID
	#define GET_UserDBObjectSetID(fl)  CAL_CMGETAPI( "UserDBObjectSetID" ) 
	#define CAL_UserDBObjectSetID  UserDBObjectSetID
	#define CHK_UserDBObjectSetID  TRUE
	#define EXP_UserDBObjectSetID  CAL_CMEXPAPI( "UserDBObjectSetID" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectSetID
	#define EXT_UserDBObjectSetID
	#define GET_UserDBObjectSetID(fl)  CAL_CMGETAPI( "UserDBObjectSetID" ) 
	#define CAL_UserDBObjectSetID  UserDBObjectSetID
	#define CHK_UserDBObjectSetID  TRUE
	#define EXP_UserDBObjectSetID  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectSetID", (RTS_UINTPTR)UserDBObjectSetID, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectSetID
	#define EXT_CmpUserDBObjectsUserDBObjectSetID
	#define GET_CmpUserDBObjectsUserDBObjectSetID  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectSetID pICmpUserDBObjects->IUserDBObjectSetID
	#define CHK_CmpUserDBObjectsUserDBObjectSetID (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectSetID  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectSetID
	#define EXT_UserDBObjectSetID
	#define GET_UserDBObjectSetID(fl)  CAL_CMGETAPI( "UserDBObjectSetID" ) 
	#define CAL_UserDBObjectSetID pICmpUserDBObjects->IUserDBObjectSetID
	#define CHK_UserDBObjectSetID (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectSetID  CAL_CMEXPAPI( "UserDBObjectSetID" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectSetID  PFUSERDBOBJECTSETID pfUserDBObjectSetID;
	#define EXT_UserDBObjectSetID  extern PFUSERDBOBJECTSETID pfUserDBObjectSetID;
	#define GET_UserDBObjectSetID(fl)  s_pfCMGetAPI2( "UserDBObjectSetID", (RTS_VOID_FCTPTR *)&pfUserDBObjectSetID, (fl), 0, 0)
	#define CAL_UserDBObjectSetID  pfUserDBObjectSetID
	#define CHK_UserDBObjectSetID  (pfUserDBObjectSetID != NULL)
	#define EXP_UserDBObjectSetID  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectSetID", (RTS_UINTPTR)UserDBObjectSetID, 0, 0) 
#endif




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
RTS_RESULT CDECL UserDBObjectAddGroup(RTS_HANDLE hObject, RTS_HANDLE hGroup);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTADDGROUP) (RTS_HANDLE hObject, RTS_HANDLE hGroup);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTADDGROUP_NOTIMPLEMENTED)
	#define USE_UserDBObjectAddGroup
	#define EXT_UserDBObjectAddGroup
	#define GET_UserDBObjectAddGroup(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectAddGroup(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectAddGroup  FALSE
	#define EXP_UserDBObjectAddGroup  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectAddGroup
	#define EXT_UserDBObjectAddGroup
	#define GET_UserDBObjectAddGroup(fl)  CAL_CMGETAPI( "UserDBObjectAddGroup" ) 
	#define CAL_UserDBObjectAddGroup  UserDBObjectAddGroup
	#define CHK_UserDBObjectAddGroup  TRUE
	#define EXP_UserDBObjectAddGroup  CAL_CMEXPAPI( "UserDBObjectAddGroup" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectAddGroup
	#define EXT_UserDBObjectAddGroup
	#define GET_UserDBObjectAddGroup(fl)  CAL_CMGETAPI( "UserDBObjectAddGroup" ) 
	#define CAL_UserDBObjectAddGroup  UserDBObjectAddGroup
	#define CHK_UserDBObjectAddGroup  TRUE
	#define EXP_UserDBObjectAddGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectAddGroup", (RTS_UINTPTR)UserDBObjectAddGroup, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectAddGroup
	#define EXT_CmpUserDBObjectsUserDBObjectAddGroup
	#define GET_CmpUserDBObjectsUserDBObjectAddGroup  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectAddGroup pICmpUserDBObjects->IUserDBObjectAddGroup
	#define CHK_CmpUserDBObjectsUserDBObjectAddGroup (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectAddGroup  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectAddGroup
	#define EXT_UserDBObjectAddGroup
	#define GET_UserDBObjectAddGroup(fl)  CAL_CMGETAPI( "UserDBObjectAddGroup" ) 
	#define CAL_UserDBObjectAddGroup pICmpUserDBObjects->IUserDBObjectAddGroup
	#define CHK_UserDBObjectAddGroup (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectAddGroup  CAL_CMEXPAPI( "UserDBObjectAddGroup" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectAddGroup  PFUSERDBOBJECTADDGROUP pfUserDBObjectAddGroup;
	#define EXT_UserDBObjectAddGroup  extern PFUSERDBOBJECTADDGROUP pfUserDBObjectAddGroup;
	#define GET_UserDBObjectAddGroup(fl)  s_pfCMGetAPI2( "UserDBObjectAddGroup", (RTS_VOID_FCTPTR *)&pfUserDBObjectAddGroup, (fl), 0, 0)
	#define CAL_UserDBObjectAddGroup  pfUserDBObjectAddGroup
	#define CHK_UserDBObjectAddGroup  (pfUserDBObjectAddGroup != NULL)
	#define EXP_UserDBObjectAddGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectAddGroup", (RTS_UINTPTR)UserDBObjectAddGroup, 0, 0) 
#endif




/**
 * <description>Remove a group from the specified object</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <param name="hGroup" type="IN">Handle to the group that should be removed</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Group could be removed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handles</errorcode>
 */
RTS_RESULT CDECL UserDBObjectRemoveGroup(RTS_HANDLE hObject, RTS_HANDLE hGroup);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTREMOVEGROUP) (RTS_HANDLE hObject, RTS_HANDLE hGroup);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTREMOVEGROUP_NOTIMPLEMENTED)
	#define USE_UserDBObjectRemoveGroup
	#define EXT_UserDBObjectRemoveGroup
	#define GET_UserDBObjectRemoveGroup(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectRemoveGroup(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectRemoveGroup  FALSE
	#define EXP_UserDBObjectRemoveGroup  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectRemoveGroup
	#define EXT_UserDBObjectRemoveGroup
	#define GET_UserDBObjectRemoveGroup(fl)  CAL_CMGETAPI( "UserDBObjectRemoveGroup" ) 
	#define CAL_UserDBObjectRemoveGroup  UserDBObjectRemoveGroup
	#define CHK_UserDBObjectRemoveGroup  TRUE
	#define EXP_UserDBObjectRemoveGroup  CAL_CMEXPAPI( "UserDBObjectRemoveGroup" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectRemoveGroup
	#define EXT_UserDBObjectRemoveGroup
	#define GET_UserDBObjectRemoveGroup(fl)  CAL_CMGETAPI( "UserDBObjectRemoveGroup" ) 
	#define CAL_UserDBObjectRemoveGroup  UserDBObjectRemoveGroup
	#define CHK_UserDBObjectRemoveGroup  TRUE
	#define EXP_UserDBObjectRemoveGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectRemoveGroup", (RTS_UINTPTR)UserDBObjectRemoveGroup, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectRemoveGroup
	#define EXT_CmpUserDBObjectsUserDBObjectRemoveGroup
	#define GET_CmpUserDBObjectsUserDBObjectRemoveGroup  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectRemoveGroup pICmpUserDBObjects->IUserDBObjectRemoveGroup
	#define CHK_CmpUserDBObjectsUserDBObjectRemoveGroup (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectRemoveGroup  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectRemoveGroup
	#define EXT_UserDBObjectRemoveGroup
	#define GET_UserDBObjectRemoveGroup(fl)  CAL_CMGETAPI( "UserDBObjectRemoveGroup" ) 
	#define CAL_UserDBObjectRemoveGroup pICmpUserDBObjects->IUserDBObjectRemoveGroup
	#define CHK_UserDBObjectRemoveGroup (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectRemoveGroup  CAL_CMEXPAPI( "UserDBObjectRemoveGroup" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectRemoveGroup  PFUSERDBOBJECTREMOVEGROUP pfUserDBObjectRemoveGroup;
	#define EXT_UserDBObjectRemoveGroup  extern PFUSERDBOBJECTREMOVEGROUP pfUserDBObjectRemoveGroup;
	#define GET_UserDBObjectRemoveGroup(fl)  s_pfCMGetAPI2( "UserDBObjectRemoveGroup", (RTS_VOID_FCTPTR *)&pfUserDBObjectRemoveGroup, (fl), 0, 0)
	#define CAL_UserDBObjectRemoveGroup  pfUserDBObjectRemoveGroup
	#define CHK_UserDBObjectRemoveGroup  (pfUserDBObjectRemoveGroup != NULL)
	#define EXP_UserDBObjectRemoveGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectRemoveGroup", (RTS_UINTPTR)UserDBObjectRemoveGroup, 0, 0) 
#endif




/**
 * <description>Set the access rights for the group at the specified object</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <param name="hGroup" type="IN">Handle to the group</param>
 * <element name="ulRights" type="IN">Rights of the group. See category "User rights" for details</element>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Access rights could be set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handles</errorcode>
 */
RTS_RESULT CDECL UserDBObjectSetGroupRights(RTS_HANDLE hObject, RTS_HANDLE hGroup, RTS_UI32 ulRights);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTSETGROUPRIGHTS) (RTS_HANDLE hObject, RTS_HANDLE hGroup, RTS_UI32 ulRights);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTSETGROUPRIGHTS_NOTIMPLEMENTED)
	#define USE_UserDBObjectSetGroupRights
	#define EXT_UserDBObjectSetGroupRights
	#define GET_UserDBObjectSetGroupRights(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectSetGroupRights(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectSetGroupRights  FALSE
	#define EXP_UserDBObjectSetGroupRights  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectSetGroupRights
	#define EXT_UserDBObjectSetGroupRights
	#define GET_UserDBObjectSetGroupRights(fl)  CAL_CMGETAPI( "UserDBObjectSetGroupRights" ) 
	#define CAL_UserDBObjectSetGroupRights  UserDBObjectSetGroupRights
	#define CHK_UserDBObjectSetGroupRights  TRUE
	#define EXP_UserDBObjectSetGroupRights  CAL_CMEXPAPI( "UserDBObjectSetGroupRights" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectSetGroupRights
	#define EXT_UserDBObjectSetGroupRights
	#define GET_UserDBObjectSetGroupRights(fl)  CAL_CMGETAPI( "UserDBObjectSetGroupRights" ) 
	#define CAL_UserDBObjectSetGroupRights  UserDBObjectSetGroupRights
	#define CHK_UserDBObjectSetGroupRights  TRUE
	#define EXP_UserDBObjectSetGroupRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectSetGroupRights", (RTS_UINTPTR)UserDBObjectSetGroupRights, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectSetGroupRights
	#define EXT_CmpUserDBObjectsUserDBObjectSetGroupRights
	#define GET_CmpUserDBObjectsUserDBObjectSetGroupRights  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectSetGroupRights pICmpUserDBObjects->IUserDBObjectSetGroupRights
	#define CHK_CmpUserDBObjectsUserDBObjectSetGroupRights (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectSetGroupRights  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectSetGroupRights
	#define EXT_UserDBObjectSetGroupRights
	#define GET_UserDBObjectSetGroupRights(fl)  CAL_CMGETAPI( "UserDBObjectSetGroupRights" ) 
	#define CAL_UserDBObjectSetGroupRights pICmpUserDBObjects->IUserDBObjectSetGroupRights
	#define CHK_UserDBObjectSetGroupRights (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectSetGroupRights  CAL_CMEXPAPI( "UserDBObjectSetGroupRights" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectSetGroupRights  PFUSERDBOBJECTSETGROUPRIGHTS pfUserDBObjectSetGroupRights;
	#define EXT_UserDBObjectSetGroupRights  extern PFUSERDBOBJECTSETGROUPRIGHTS pfUserDBObjectSetGroupRights;
	#define GET_UserDBObjectSetGroupRights(fl)  s_pfCMGetAPI2( "UserDBObjectSetGroupRights", (RTS_VOID_FCTPTR *)&pfUserDBObjectSetGroupRights, (fl), 0, 0)
	#define CAL_UserDBObjectSetGroupRights  pfUserDBObjectSetGroupRights
	#define CHK_UserDBObjectSetGroupRights  (pfUserDBObjectSetGroupRights != NULL)
	#define EXP_UserDBObjectSetGroupRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectSetGroupRights", (RTS_UINTPTR)UserDBObjectSetGroupRights, 0, 0) 
#endif




/**
 * <description>Set the denied access rights for the group at the specified object</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <param name="hGroup" type="IN">Handle to the group</param>
 * <element name="ulDeniedRights" type="IN">Denied rights of the group. See category "User rights" for details</element>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Access rights could be set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handles</errorcode>
 */
RTS_RESULT CDECL UserDBObjectSetGroupDeniedRights(RTS_HANDLE hObject, RTS_HANDLE hGroup, RTS_UI32 ulDeniedRights);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTSETGROUPDENIEDRIGHTS) (RTS_HANDLE hObject, RTS_HANDLE hGroup, RTS_UI32 ulDeniedRights);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTSETGROUPDENIEDRIGHTS_NOTIMPLEMENTED)
	#define USE_UserDBObjectSetGroupDeniedRights
	#define EXT_UserDBObjectSetGroupDeniedRights
	#define GET_UserDBObjectSetGroupDeniedRights(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectSetGroupDeniedRights(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectSetGroupDeniedRights  FALSE
	#define EXP_UserDBObjectSetGroupDeniedRights  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectSetGroupDeniedRights
	#define EXT_UserDBObjectSetGroupDeniedRights
	#define GET_UserDBObjectSetGroupDeniedRights(fl)  CAL_CMGETAPI( "UserDBObjectSetGroupDeniedRights" ) 
	#define CAL_UserDBObjectSetGroupDeniedRights  UserDBObjectSetGroupDeniedRights
	#define CHK_UserDBObjectSetGroupDeniedRights  TRUE
	#define EXP_UserDBObjectSetGroupDeniedRights  CAL_CMEXPAPI( "UserDBObjectSetGroupDeniedRights" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectSetGroupDeniedRights
	#define EXT_UserDBObjectSetGroupDeniedRights
	#define GET_UserDBObjectSetGroupDeniedRights(fl)  CAL_CMGETAPI( "UserDBObjectSetGroupDeniedRights" ) 
	#define CAL_UserDBObjectSetGroupDeniedRights  UserDBObjectSetGroupDeniedRights
	#define CHK_UserDBObjectSetGroupDeniedRights  TRUE
	#define EXP_UserDBObjectSetGroupDeniedRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectSetGroupDeniedRights", (RTS_UINTPTR)UserDBObjectSetGroupDeniedRights, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectSetGroupDeniedRights
	#define EXT_CmpUserDBObjectsUserDBObjectSetGroupDeniedRights
	#define GET_CmpUserDBObjectsUserDBObjectSetGroupDeniedRights  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectSetGroupDeniedRights pICmpUserDBObjects->IUserDBObjectSetGroupDeniedRights
	#define CHK_CmpUserDBObjectsUserDBObjectSetGroupDeniedRights (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectSetGroupDeniedRights  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectSetGroupDeniedRights
	#define EXT_UserDBObjectSetGroupDeniedRights
	#define GET_UserDBObjectSetGroupDeniedRights(fl)  CAL_CMGETAPI( "UserDBObjectSetGroupDeniedRights" ) 
	#define CAL_UserDBObjectSetGroupDeniedRights pICmpUserDBObjects->IUserDBObjectSetGroupDeniedRights
	#define CHK_UserDBObjectSetGroupDeniedRights (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectSetGroupDeniedRights  CAL_CMEXPAPI( "UserDBObjectSetGroupDeniedRights" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectSetGroupDeniedRights  PFUSERDBOBJECTSETGROUPDENIEDRIGHTS pfUserDBObjectSetGroupDeniedRights;
	#define EXT_UserDBObjectSetGroupDeniedRights  extern PFUSERDBOBJECTSETGROUPDENIEDRIGHTS pfUserDBObjectSetGroupDeniedRights;
	#define GET_UserDBObjectSetGroupDeniedRights(fl)  s_pfCMGetAPI2( "UserDBObjectSetGroupDeniedRights", (RTS_VOID_FCTPTR *)&pfUserDBObjectSetGroupDeniedRights, (fl), 0, 0)
	#define CAL_UserDBObjectSetGroupDeniedRights  pfUserDBObjectSetGroupDeniedRights
	#define CHK_UserDBObjectSetGroupDeniedRights  (pfUserDBObjectSetGroupDeniedRights != NULL)
	#define EXP_UserDBObjectSetGroupDeniedRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectSetGroupDeniedRights", (RTS_UINTPTR)UserDBObjectSetGroupDeniedRights, 0, 0) 
#endif





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
RTS_HANDLE CDECL UserDBObjectGetFirst(RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBOBJECTGETFIRST) (RTS_RESULT *pResult);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTGETFIRST_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetFirst
	#define EXT_UserDBObjectGetFirst
	#define GET_UserDBObjectGetFirst(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetFirst(p0)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBObjectGetFirst  FALSE
	#define EXP_UserDBObjectGetFirst  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetFirst
	#define EXT_UserDBObjectGetFirst
	#define GET_UserDBObjectGetFirst(fl)  CAL_CMGETAPI( "UserDBObjectGetFirst" ) 
	#define CAL_UserDBObjectGetFirst  UserDBObjectGetFirst
	#define CHK_UserDBObjectGetFirst  TRUE
	#define EXP_UserDBObjectGetFirst  CAL_CMEXPAPI( "UserDBObjectGetFirst" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectGetFirst
	#define EXT_UserDBObjectGetFirst
	#define GET_UserDBObjectGetFirst(fl)  CAL_CMGETAPI( "UserDBObjectGetFirst" ) 
	#define CAL_UserDBObjectGetFirst  UserDBObjectGetFirst
	#define CHK_UserDBObjectGetFirst  TRUE
	#define EXP_UserDBObjectGetFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetFirst", (RTS_UINTPTR)UserDBObjectGetFirst, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectGetFirst
	#define EXT_CmpUserDBObjectsUserDBObjectGetFirst
	#define GET_CmpUserDBObjectsUserDBObjectGetFirst  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectGetFirst pICmpUserDBObjects->IUserDBObjectGetFirst
	#define CHK_CmpUserDBObjectsUserDBObjectGetFirst (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectGetFirst  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetFirst
	#define EXT_UserDBObjectGetFirst
	#define GET_UserDBObjectGetFirst(fl)  CAL_CMGETAPI( "UserDBObjectGetFirst" ) 
	#define CAL_UserDBObjectGetFirst pICmpUserDBObjects->IUserDBObjectGetFirst
	#define CHK_UserDBObjectGetFirst (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectGetFirst  CAL_CMEXPAPI( "UserDBObjectGetFirst" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetFirst  PFUSERDBOBJECTGETFIRST pfUserDBObjectGetFirst;
	#define EXT_UserDBObjectGetFirst  extern PFUSERDBOBJECTGETFIRST pfUserDBObjectGetFirst;
	#define GET_UserDBObjectGetFirst(fl)  s_pfCMGetAPI2( "UserDBObjectGetFirst", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetFirst, (fl), 0, 0)
	#define CAL_UserDBObjectGetFirst  pfUserDBObjectGetFirst
	#define CHK_UserDBObjectGetFirst  (pfUserDBObjectGetFirst != NULL)
	#define EXP_UserDBObjectGetFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetFirst", (RTS_UINTPTR)UserDBObjectGetFirst, 0, 0) 
#endif




/**
 * <description>Iteration interface to get next object of the user rights management. Must be started with UserDBObjectGetFirst()</description>
 * <param name="hPrevObject" type="IN">Handle to the previous object retrieved via UserDBObjectGetFirst() or subsequent calls of UserDBObjectGetNext()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Next object available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handles</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No next object available</errorcode>
 * <result>Handle to the next object in the user rights management or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBObjectGetNext(RTS_HANDLE hPrevObject, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBOBJECTGETNEXT) (RTS_HANDLE hPrevObject, RTS_RESULT *pResult);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTGETNEXT_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetNext
	#define EXT_UserDBObjectGetNext
	#define GET_UserDBObjectGetNext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetNext(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBObjectGetNext  FALSE
	#define EXP_UserDBObjectGetNext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetNext
	#define EXT_UserDBObjectGetNext
	#define GET_UserDBObjectGetNext(fl)  CAL_CMGETAPI( "UserDBObjectGetNext" ) 
	#define CAL_UserDBObjectGetNext  UserDBObjectGetNext
	#define CHK_UserDBObjectGetNext  TRUE
	#define EXP_UserDBObjectGetNext  CAL_CMEXPAPI( "UserDBObjectGetNext" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectGetNext
	#define EXT_UserDBObjectGetNext
	#define GET_UserDBObjectGetNext(fl)  CAL_CMGETAPI( "UserDBObjectGetNext" ) 
	#define CAL_UserDBObjectGetNext  UserDBObjectGetNext
	#define CHK_UserDBObjectGetNext  TRUE
	#define EXP_UserDBObjectGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetNext", (RTS_UINTPTR)UserDBObjectGetNext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectGetNext
	#define EXT_CmpUserDBObjectsUserDBObjectGetNext
	#define GET_CmpUserDBObjectsUserDBObjectGetNext  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectGetNext pICmpUserDBObjects->IUserDBObjectGetNext
	#define CHK_CmpUserDBObjectsUserDBObjectGetNext (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectGetNext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetNext
	#define EXT_UserDBObjectGetNext
	#define GET_UserDBObjectGetNext(fl)  CAL_CMGETAPI( "UserDBObjectGetNext" ) 
	#define CAL_UserDBObjectGetNext pICmpUserDBObjects->IUserDBObjectGetNext
	#define CHK_UserDBObjectGetNext (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectGetNext  CAL_CMEXPAPI( "UserDBObjectGetNext" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetNext  PFUSERDBOBJECTGETNEXT pfUserDBObjectGetNext;
	#define EXT_UserDBObjectGetNext  extern PFUSERDBOBJECTGETNEXT pfUserDBObjectGetNext;
	#define GET_UserDBObjectGetNext(fl)  s_pfCMGetAPI2( "UserDBObjectGetNext", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetNext, (fl), 0, 0)
	#define CAL_UserDBObjectGetNext  pfUserDBObjectGetNext
	#define CHK_UserDBObjectGetNext  (pfUserDBObjectGetNext != NULL)
	#define EXP_UserDBObjectGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetNext", (RTS_UINTPTR)UserDBObjectGetNext, 0, 0) 
#endif




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
RTS_HANDLE CDECL UserDBObjectOpen(char *pszObject, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBOBJECTOPEN) (char *pszObject, RTS_RESULT *pResult);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTOPEN_NOTIMPLEMENTED)
	#define USE_UserDBObjectOpen
	#define EXT_UserDBObjectOpen
	#define GET_UserDBObjectOpen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectOpen(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBObjectOpen  FALSE
	#define EXP_UserDBObjectOpen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectOpen
	#define EXT_UserDBObjectOpen
	#define GET_UserDBObjectOpen(fl)  CAL_CMGETAPI( "UserDBObjectOpen" ) 
	#define CAL_UserDBObjectOpen  UserDBObjectOpen
	#define CHK_UserDBObjectOpen  TRUE
	#define EXP_UserDBObjectOpen  CAL_CMEXPAPI( "UserDBObjectOpen" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectOpen
	#define EXT_UserDBObjectOpen
	#define GET_UserDBObjectOpen(fl)  CAL_CMGETAPI( "UserDBObjectOpen" ) 
	#define CAL_UserDBObjectOpen  UserDBObjectOpen
	#define CHK_UserDBObjectOpen  TRUE
	#define EXP_UserDBObjectOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectOpen", (RTS_UINTPTR)UserDBObjectOpen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectOpen
	#define EXT_CmpUserDBObjectsUserDBObjectOpen
	#define GET_CmpUserDBObjectsUserDBObjectOpen  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectOpen pICmpUserDBObjects->IUserDBObjectOpen
	#define CHK_CmpUserDBObjectsUserDBObjectOpen (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectOpen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectOpen
	#define EXT_UserDBObjectOpen
	#define GET_UserDBObjectOpen(fl)  CAL_CMGETAPI( "UserDBObjectOpen" ) 
	#define CAL_UserDBObjectOpen pICmpUserDBObjects->IUserDBObjectOpen
	#define CHK_UserDBObjectOpen (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectOpen  CAL_CMEXPAPI( "UserDBObjectOpen" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectOpen  PFUSERDBOBJECTOPEN pfUserDBObjectOpen;
	#define EXT_UserDBObjectOpen  extern PFUSERDBOBJECTOPEN pfUserDBObjectOpen;
	#define GET_UserDBObjectOpen(fl)  s_pfCMGetAPI2( "UserDBObjectOpen", (RTS_VOID_FCTPTR *)&pfUserDBObjectOpen, (fl), 0, 0)
	#define CAL_UserDBObjectOpen  pfUserDBObjectOpen
	#define CHK_UserDBObjectOpen  (pfUserDBObjectOpen != NULL)
	#define EXP_UserDBObjectOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectOpen", (RTS_UINTPTR)UserDBObjectOpen, 0, 0) 
#endif




/**
 * <description>Close an object</description>
 * <param name="hObject" type="IN">Handle to the object</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Object could be closed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid object handle</errorcode>
 */
RTS_RESULT CDECL UserDBObjectClose(RTS_HANDLE hObject);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTCLOSE) (RTS_HANDLE hObject);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTCLOSE_NOTIMPLEMENTED)
	#define USE_UserDBObjectClose
	#define EXT_UserDBObjectClose
	#define GET_UserDBObjectClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectClose(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectClose  FALSE
	#define EXP_UserDBObjectClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectClose
	#define EXT_UserDBObjectClose
	#define GET_UserDBObjectClose(fl)  CAL_CMGETAPI( "UserDBObjectClose" ) 
	#define CAL_UserDBObjectClose  UserDBObjectClose
	#define CHK_UserDBObjectClose  TRUE
	#define EXP_UserDBObjectClose  CAL_CMEXPAPI( "UserDBObjectClose" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectClose
	#define EXT_UserDBObjectClose
	#define GET_UserDBObjectClose(fl)  CAL_CMGETAPI( "UserDBObjectClose" ) 
	#define CAL_UserDBObjectClose  UserDBObjectClose
	#define CHK_UserDBObjectClose  TRUE
	#define EXP_UserDBObjectClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectClose", (RTS_UINTPTR)UserDBObjectClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectClose
	#define EXT_CmpUserDBObjectsUserDBObjectClose
	#define GET_CmpUserDBObjectsUserDBObjectClose  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectClose pICmpUserDBObjects->IUserDBObjectClose
	#define CHK_CmpUserDBObjectsUserDBObjectClose (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectClose
	#define EXT_UserDBObjectClose
	#define GET_UserDBObjectClose(fl)  CAL_CMGETAPI( "UserDBObjectClose" ) 
	#define CAL_UserDBObjectClose pICmpUserDBObjects->IUserDBObjectClose
	#define CHK_UserDBObjectClose (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectClose  CAL_CMEXPAPI( "UserDBObjectClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectClose  PFUSERDBOBJECTCLOSE pfUserDBObjectClose;
	#define EXT_UserDBObjectClose  extern PFUSERDBOBJECTCLOSE pfUserDBObjectClose;
	#define GET_UserDBObjectClose(fl)  s_pfCMGetAPI2( "UserDBObjectClose", (RTS_VOID_FCTPTR *)&pfUserDBObjectClose, (fl), 0, 0)
	#define CAL_UserDBObjectClose  pfUserDBObjectClose
	#define CHK_UserDBObjectClose  (pfUserDBObjectClose != NULL)
	#define EXP_UserDBObjectClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectClose", (RTS_UINTPTR)UserDBObjectClose, 0, 0) 
#endif




/**
 * <description>Get object name</description>
 * <param name="hObject" type="IN">Handle to the object</param>
 * <param name="pszObject" type="OUT">Pointer to get object name</param>
 * <param name="piMaxLen" type="INOUT">Pointer to length of buffer in pszObject. If pszObject = NULL, only the length of the object name is returned in *piMaxLen</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Object name is returned</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid object handle or pszObject = NULL and piMaxLen = NULL</errorcode>
 */
RTS_RESULT CDECL UserDBObjectGetName(RTS_HANDLE hObject, char *pszObject, int *piMaxLen);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTGETNAME) (RTS_HANDLE hObject, char *pszObject, int *piMaxLen);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTGETNAME_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetName
	#define EXT_UserDBObjectGetName
	#define GET_UserDBObjectGetName(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetName(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectGetName  FALSE
	#define EXP_UserDBObjectGetName  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetName
	#define EXT_UserDBObjectGetName
	#define GET_UserDBObjectGetName(fl)  CAL_CMGETAPI( "UserDBObjectGetName" ) 
	#define CAL_UserDBObjectGetName  UserDBObjectGetName
	#define CHK_UserDBObjectGetName  TRUE
	#define EXP_UserDBObjectGetName  CAL_CMEXPAPI( "UserDBObjectGetName" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectGetName
	#define EXT_UserDBObjectGetName
	#define GET_UserDBObjectGetName(fl)  CAL_CMGETAPI( "UserDBObjectGetName" ) 
	#define CAL_UserDBObjectGetName  UserDBObjectGetName
	#define CHK_UserDBObjectGetName  TRUE
	#define EXP_UserDBObjectGetName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetName", (RTS_UINTPTR)UserDBObjectGetName, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectGetName
	#define EXT_CmpUserDBObjectsUserDBObjectGetName
	#define GET_CmpUserDBObjectsUserDBObjectGetName  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectGetName pICmpUserDBObjects->IUserDBObjectGetName
	#define CHK_CmpUserDBObjectsUserDBObjectGetName (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectGetName  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetName
	#define EXT_UserDBObjectGetName
	#define GET_UserDBObjectGetName(fl)  CAL_CMGETAPI( "UserDBObjectGetName" ) 
	#define CAL_UserDBObjectGetName pICmpUserDBObjects->IUserDBObjectGetName
	#define CHK_UserDBObjectGetName (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectGetName  CAL_CMEXPAPI( "UserDBObjectGetName" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetName  PFUSERDBOBJECTGETNAME pfUserDBObjectGetName;
	#define EXT_UserDBObjectGetName  extern PFUSERDBOBJECTGETNAME pfUserDBObjectGetName;
	#define GET_UserDBObjectGetName(fl)  s_pfCMGetAPI2( "UserDBObjectGetName", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetName, (fl), 0, 0)
	#define CAL_UserDBObjectGetName  pfUserDBObjectGetName
	#define CHK_UserDBObjectGetName  (pfUserDBObjectGetName != NULL)
	#define EXP_UserDBObjectGetName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetName", (RTS_UINTPTR)UserDBObjectGetName, 0, 0) 
#endif




/**
 * <description>Get the complete object path name</description>
 * <param name="hObject" type="IN">Handle to the object</param>
 * <param name="pszObject" type="IN">Full object path name (see object tree)</param>
 * <param name="piMaxLen" type="INOUT">Pointer to length of buffer in pszObject. If pszObject = NULL, only the length of the object name is returned in *piMaxLen</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Object name is returned</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid object handle or pszObject = NULL and piMaxLen = NULL</errorcode>
 */
RTS_RESULT CDECL UserDBObjectGetPath(RTS_HANDLE hObject, char *pszObject, int *piMaxLen);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTGETPATH) (RTS_HANDLE hObject, char *pszObject, int *piMaxLen);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTGETPATH_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetPath
	#define EXT_UserDBObjectGetPath
	#define GET_UserDBObjectGetPath(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetPath(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectGetPath  FALSE
	#define EXP_UserDBObjectGetPath  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetPath
	#define EXT_UserDBObjectGetPath
	#define GET_UserDBObjectGetPath(fl)  CAL_CMGETAPI( "UserDBObjectGetPath" ) 
	#define CAL_UserDBObjectGetPath  UserDBObjectGetPath
	#define CHK_UserDBObjectGetPath  TRUE
	#define EXP_UserDBObjectGetPath  CAL_CMEXPAPI( "UserDBObjectGetPath" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectGetPath
	#define EXT_UserDBObjectGetPath
	#define GET_UserDBObjectGetPath(fl)  CAL_CMGETAPI( "UserDBObjectGetPath" ) 
	#define CAL_UserDBObjectGetPath  UserDBObjectGetPath
	#define CHK_UserDBObjectGetPath  TRUE
	#define EXP_UserDBObjectGetPath  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetPath", (RTS_UINTPTR)UserDBObjectGetPath, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectGetPath
	#define EXT_CmpUserDBObjectsUserDBObjectGetPath
	#define GET_CmpUserDBObjectsUserDBObjectGetPath  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectGetPath pICmpUserDBObjects->IUserDBObjectGetPath
	#define CHK_CmpUserDBObjectsUserDBObjectGetPath (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectGetPath  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetPath
	#define EXT_UserDBObjectGetPath
	#define GET_UserDBObjectGetPath(fl)  CAL_CMGETAPI( "UserDBObjectGetPath" ) 
	#define CAL_UserDBObjectGetPath pICmpUserDBObjects->IUserDBObjectGetPath
	#define CHK_UserDBObjectGetPath (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectGetPath  CAL_CMEXPAPI( "UserDBObjectGetPath" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetPath  PFUSERDBOBJECTGETPATH pfUserDBObjectGetPath;
	#define EXT_UserDBObjectGetPath  extern PFUSERDBOBJECTGETPATH pfUserDBObjectGetPath;
	#define GET_UserDBObjectGetPath(fl)  s_pfCMGetAPI2( "UserDBObjectGetPath", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetPath, (fl), 0, 0)
	#define CAL_UserDBObjectGetPath  pfUserDBObjectGetPath
	#define CHK_UserDBObjectGetPath  (pfUserDBObjectGetPath != NULL)
	#define EXP_UserDBObjectGetPath  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetPath", (RTS_UINTPTR)UserDBObjectGetPath, 0, 0) 
#endif




/**
 * <description>Get first child object in object tree of the specified father object</description>
 * <param name="hFatherObject" type="IN">Handle to the father object</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">First child object available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter hFatherObject</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <result>Handle to the child object or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBObjectGetFirstChild(RTS_HANDLE hFatherObject, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBOBJECTGETFIRSTCHILD) (RTS_HANDLE hFatherObject, RTS_RESULT *pResult);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTGETFIRSTCHILD_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetFirstChild
	#define EXT_UserDBObjectGetFirstChild
	#define GET_UserDBObjectGetFirstChild(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetFirstChild(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBObjectGetFirstChild  FALSE
	#define EXP_UserDBObjectGetFirstChild  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetFirstChild
	#define EXT_UserDBObjectGetFirstChild
	#define GET_UserDBObjectGetFirstChild(fl)  CAL_CMGETAPI( "UserDBObjectGetFirstChild" ) 
	#define CAL_UserDBObjectGetFirstChild  UserDBObjectGetFirstChild
	#define CHK_UserDBObjectGetFirstChild  TRUE
	#define EXP_UserDBObjectGetFirstChild  CAL_CMEXPAPI( "UserDBObjectGetFirstChild" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectGetFirstChild
	#define EXT_UserDBObjectGetFirstChild
	#define GET_UserDBObjectGetFirstChild(fl)  CAL_CMGETAPI( "UserDBObjectGetFirstChild" ) 
	#define CAL_UserDBObjectGetFirstChild  UserDBObjectGetFirstChild
	#define CHK_UserDBObjectGetFirstChild  TRUE
	#define EXP_UserDBObjectGetFirstChild  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetFirstChild", (RTS_UINTPTR)UserDBObjectGetFirstChild, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectGetFirstChild
	#define EXT_CmpUserDBObjectsUserDBObjectGetFirstChild
	#define GET_CmpUserDBObjectsUserDBObjectGetFirstChild  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectGetFirstChild pICmpUserDBObjects->IUserDBObjectGetFirstChild
	#define CHK_CmpUserDBObjectsUserDBObjectGetFirstChild (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectGetFirstChild  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetFirstChild
	#define EXT_UserDBObjectGetFirstChild
	#define GET_UserDBObjectGetFirstChild(fl)  CAL_CMGETAPI( "UserDBObjectGetFirstChild" ) 
	#define CAL_UserDBObjectGetFirstChild pICmpUserDBObjects->IUserDBObjectGetFirstChild
	#define CHK_UserDBObjectGetFirstChild (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectGetFirstChild  CAL_CMEXPAPI( "UserDBObjectGetFirstChild" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetFirstChild  PFUSERDBOBJECTGETFIRSTCHILD pfUserDBObjectGetFirstChild;
	#define EXT_UserDBObjectGetFirstChild  extern PFUSERDBOBJECTGETFIRSTCHILD pfUserDBObjectGetFirstChild;
	#define GET_UserDBObjectGetFirstChild(fl)  s_pfCMGetAPI2( "UserDBObjectGetFirstChild", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetFirstChild, (fl), 0, 0)
	#define CAL_UserDBObjectGetFirstChild  pfUserDBObjectGetFirstChild
	#define CHK_UserDBObjectGetFirstChild  (pfUserDBObjectGetFirstChild != NULL)
	#define EXP_UserDBObjectGetFirstChild  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetFirstChild", (RTS_UINTPTR)UserDBObjectGetFirstChild, 0, 0) 
#endif




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
RTS_HANDLE CDECL UserDBObjectGetNextChild(RTS_HANDLE hFatherObject, RTS_HANDLE hPrevChildObject, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBOBJECTGETNEXTCHILD) (RTS_HANDLE hFatherObject, RTS_HANDLE hPrevChildObject, RTS_RESULT *pResult);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTGETNEXTCHILD_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetNextChild
	#define EXT_UserDBObjectGetNextChild
	#define GET_UserDBObjectGetNextChild(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetNextChild(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBObjectGetNextChild  FALSE
	#define EXP_UserDBObjectGetNextChild  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetNextChild
	#define EXT_UserDBObjectGetNextChild
	#define GET_UserDBObjectGetNextChild(fl)  CAL_CMGETAPI( "UserDBObjectGetNextChild" ) 
	#define CAL_UserDBObjectGetNextChild  UserDBObjectGetNextChild
	#define CHK_UserDBObjectGetNextChild  TRUE
	#define EXP_UserDBObjectGetNextChild  CAL_CMEXPAPI( "UserDBObjectGetNextChild" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectGetNextChild
	#define EXT_UserDBObjectGetNextChild
	#define GET_UserDBObjectGetNextChild(fl)  CAL_CMGETAPI( "UserDBObjectGetNextChild" ) 
	#define CAL_UserDBObjectGetNextChild  UserDBObjectGetNextChild
	#define CHK_UserDBObjectGetNextChild  TRUE
	#define EXP_UserDBObjectGetNextChild  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetNextChild", (RTS_UINTPTR)UserDBObjectGetNextChild, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectGetNextChild
	#define EXT_CmpUserDBObjectsUserDBObjectGetNextChild
	#define GET_CmpUserDBObjectsUserDBObjectGetNextChild  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectGetNextChild pICmpUserDBObjects->IUserDBObjectGetNextChild
	#define CHK_CmpUserDBObjectsUserDBObjectGetNextChild (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectGetNextChild  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetNextChild
	#define EXT_UserDBObjectGetNextChild
	#define GET_UserDBObjectGetNextChild(fl)  CAL_CMGETAPI( "UserDBObjectGetNextChild" ) 
	#define CAL_UserDBObjectGetNextChild pICmpUserDBObjects->IUserDBObjectGetNextChild
	#define CHK_UserDBObjectGetNextChild (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectGetNextChild  CAL_CMEXPAPI( "UserDBObjectGetNextChild" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetNextChild  PFUSERDBOBJECTGETNEXTCHILD pfUserDBObjectGetNextChild;
	#define EXT_UserDBObjectGetNextChild  extern PFUSERDBOBJECTGETNEXTCHILD pfUserDBObjectGetNextChild;
	#define GET_UserDBObjectGetNextChild(fl)  s_pfCMGetAPI2( "UserDBObjectGetNextChild", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetNextChild, (fl), 0, 0)
	#define CAL_UserDBObjectGetNextChild  pfUserDBObjectGetNextChild
	#define CHK_UserDBObjectGetNextChild  (pfUserDBObjectGetNextChild != NULL)
	#define EXP_UserDBObjectGetNextChild  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetNextChild", (RTS_UINTPTR)UserDBObjectGetNextChild, 0, 0) 
#endif




/**
 * <description>Get the father object in object tree of the specified child object</description>
 * <param name="hChildObject" type="IN">Handle to the child object</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Father object could be retrieved</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter hChildObject</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <result>Handle to the father/parent object or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBObjectGetFather(RTS_HANDLE hChildObject, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBOBJECTGETFATHER) (RTS_HANDLE hChildObject, RTS_RESULT *pResult);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTGETFATHER_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetFather
	#define EXT_UserDBObjectGetFather
	#define GET_UserDBObjectGetFather(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetFather(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBObjectGetFather  FALSE
	#define EXP_UserDBObjectGetFather  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetFather
	#define EXT_UserDBObjectGetFather
	#define GET_UserDBObjectGetFather(fl)  CAL_CMGETAPI( "UserDBObjectGetFather" ) 
	#define CAL_UserDBObjectGetFather  UserDBObjectGetFather
	#define CHK_UserDBObjectGetFather  TRUE
	#define EXP_UserDBObjectGetFather  CAL_CMEXPAPI( "UserDBObjectGetFather" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectGetFather
	#define EXT_UserDBObjectGetFather
	#define GET_UserDBObjectGetFather(fl)  CAL_CMGETAPI( "UserDBObjectGetFather" ) 
	#define CAL_UserDBObjectGetFather  UserDBObjectGetFather
	#define CHK_UserDBObjectGetFather  TRUE
	#define EXP_UserDBObjectGetFather  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetFather", (RTS_UINTPTR)UserDBObjectGetFather, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectGetFather
	#define EXT_CmpUserDBObjectsUserDBObjectGetFather
	#define GET_CmpUserDBObjectsUserDBObjectGetFather  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectGetFather pICmpUserDBObjects->IUserDBObjectGetFather
	#define CHK_CmpUserDBObjectsUserDBObjectGetFather (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectGetFather  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetFather
	#define EXT_UserDBObjectGetFather
	#define GET_UserDBObjectGetFather(fl)  CAL_CMGETAPI( "UserDBObjectGetFather" ) 
	#define CAL_UserDBObjectGetFather pICmpUserDBObjects->IUserDBObjectGetFather
	#define CHK_UserDBObjectGetFather (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectGetFather  CAL_CMEXPAPI( "UserDBObjectGetFather" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetFather  PFUSERDBOBJECTGETFATHER pfUserDBObjectGetFather;
	#define EXT_UserDBObjectGetFather  extern PFUSERDBOBJECTGETFATHER pfUserDBObjectGetFather;
	#define GET_UserDBObjectGetFather(fl)  s_pfCMGetAPI2( "UserDBObjectGetFather", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetFather, (fl), 0, 0)
	#define CAL_UserDBObjectGetFather  pfUserDBObjectGetFather
	#define CHK_UserDBObjectGetFather  (pfUserDBObjectGetFather != NULL)
	#define EXP_UserDBObjectGetFather  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetFather", (RTS_UINTPTR)UserDBObjectGetFather, 0, 0) 
#endif




/* Iteration over all groups that are assigned to the object */

/**
 * <description>Iteration interface to get the first group in the user rights management of the specified object</description>
 * <param name="hObject" type="IN">Handle to the object</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">First group available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No group available</errorcode>
 * <result>Handle to the first group of the object in the user rights management or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBObjectGetFirstGroup(RTS_HANDLE hObject, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBOBJECTGETFIRSTGROUP) (RTS_HANDLE hObject, RTS_RESULT *pResult);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTGETFIRSTGROUP_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetFirstGroup
	#define EXT_UserDBObjectGetFirstGroup
	#define GET_UserDBObjectGetFirstGroup(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetFirstGroup(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBObjectGetFirstGroup  FALSE
	#define EXP_UserDBObjectGetFirstGroup  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetFirstGroup
	#define EXT_UserDBObjectGetFirstGroup
	#define GET_UserDBObjectGetFirstGroup(fl)  CAL_CMGETAPI( "UserDBObjectGetFirstGroup" ) 
	#define CAL_UserDBObjectGetFirstGroup  UserDBObjectGetFirstGroup
	#define CHK_UserDBObjectGetFirstGroup  TRUE
	#define EXP_UserDBObjectGetFirstGroup  CAL_CMEXPAPI( "UserDBObjectGetFirstGroup" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectGetFirstGroup
	#define EXT_UserDBObjectGetFirstGroup
	#define GET_UserDBObjectGetFirstGroup(fl)  CAL_CMGETAPI( "UserDBObjectGetFirstGroup" ) 
	#define CAL_UserDBObjectGetFirstGroup  UserDBObjectGetFirstGroup
	#define CHK_UserDBObjectGetFirstGroup  TRUE
	#define EXP_UserDBObjectGetFirstGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetFirstGroup", (RTS_UINTPTR)UserDBObjectGetFirstGroup, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectGetFirstGroup
	#define EXT_CmpUserDBObjectsUserDBObjectGetFirstGroup
	#define GET_CmpUserDBObjectsUserDBObjectGetFirstGroup  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectGetFirstGroup pICmpUserDBObjects->IUserDBObjectGetFirstGroup
	#define CHK_CmpUserDBObjectsUserDBObjectGetFirstGroup (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectGetFirstGroup  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetFirstGroup
	#define EXT_UserDBObjectGetFirstGroup
	#define GET_UserDBObjectGetFirstGroup(fl)  CAL_CMGETAPI( "UserDBObjectGetFirstGroup" ) 
	#define CAL_UserDBObjectGetFirstGroup pICmpUserDBObjects->IUserDBObjectGetFirstGroup
	#define CHK_UserDBObjectGetFirstGroup (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectGetFirstGroup  CAL_CMEXPAPI( "UserDBObjectGetFirstGroup" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetFirstGroup  PFUSERDBOBJECTGETFIRSTGROUP pfUserDBObjectGetFirstGroup;
	#define EXT_UserDBObjectGetFirstGroup  extern PFUSERDBOBJECTGETFIRSTGROUP pfUserDBObjectGetFirstGroup;
	#define GET_UserDBObjectGetFirstGroup(fl)  s_pfCMGetAPI2( "UserDBObjectGetFirstGroup", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetFirstGroup, (fl), 0, 0)
	#define CAL_UserDBObjectGetFirstGroup  pfUserDBObjectGetFirstGroup
	#define CHK_UserDBObjectGetFirstGroup  (pfUserDBObjectGetFirstGroup != NULL)
	#define EXP_UserDBObjectGetFirstGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetFirstGroup", (RTS_UINTPTR)UserDBObjectGetFirstGroup, 0, 0) 
#endif




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
RTS_HANDLE CDECL UserDBObjectGetNextGroup(RTS_HANDLE hObject, RTS_HANDLE hPrevGroup, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBOBJECTGETNEXTGROUP) (RTS_HANDLE hObject, RTS_HANDLE hPrevGroup, RTS_RESULT *pResult);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTGETNEXTGROUP_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetNextGroup
	#define EXT_UserDBObjectGetNextGroup
	#define GET_UserDBObjectGetNextGroup(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetNextGroup(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBObjectGetNextGroup  FALSE
	#define EXP_UserDBObjectGetNextGroup  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetNextGroup
	#define EXT_UserDBObjectGetNextGroup
	#define GET_UserDBObjectGetNextGroup(fl)  CAL_CMGETAPI( "UserDBObjectGetNextGroup" ) 
	#define CAL_UserDBObjectGetNextGroup  UserDBObjectGetNextGroup
	#define CHK_UserDBObjectGetNextGroup  TRUE
	#define EXP_UserDBObjectGetNextGroup  CAL_CMEXPAPI( "UserDBObjectGetNextGroup" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectGetNextGroup
	#define EXT_UserDBObjectGetNextGroup
	#define GET_UserDBObjectGetNextGroup(fl)  CAL_CMGETAPI( "UserDBObjectGetNextGroup" ) 
	#define CAL_UserDBObjectGetNextGroup  UserDBObjectGetNextGroup
	#define CHK_UserDBObjectGetNextGroup  TRUE
	#define EXP_UserDBObjectGetNextGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetNextGroup", (RTS_UINTPTR)UserDBObjectGetNextGroup, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectGetNextGroup
	#define EXT_CmpUserDBObjectsUserDBObjectGetNextGroup
	#define GET_CmpUserDBObjectsUserDBObjectGetNextGroup  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectGetNextGroup pICmpUserDBObjects->IUserDBObjectGetNextGroup
	#define CHK_CmpUserDBObjectsUserDBObjectGetNextGroup (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectGetNextGroup  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetNextGroup
	#define EXT_UserDBObjectGetNextGroup
	#define GET_UserDBObjectGetNextGroup(fl)  CAL_CMGETAPI( "UserDBObjectGetNextGroup" ) 
	#define CAL_UserDBObjectGetNextGroup pICmpUserDBObjects->IUserDBObjectGetNextGroup
	#define CHK_UserDBObjectGetNextGroup (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectGetNextGroup  CAL_CMEXPAPI( "UserDBObjectGetNextGroup" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetNextGroup  PFUSERDBOBJECTGETNEXTGROUP pfUserDBObjectGetNextGroup;
	#define EXT_UserDBObjectGetNextGroup  extern PFUSERDBOBJECTGETNEXTGROUP pfUserDBObjectGetNextGroup;
	#define GET_UserDBObjectGetNextGroup(fl)  s_pfCMGetAPI2( "UserDBObjectGetNextGroup", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetNextGroup, (fl), 0, 0)
	#define CAL_UserDBObjectGetNextGroup  pfUserDBObjectGetNextGroup
	#define CHK_UserDBObjectGetNextGroup  (pfUserDBObjectGetNextGroup != NULL)
	#define EXP_UserDBObjectGetNextGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetNextGroup", (RTS_UINTPTR)UserDBObjectGetNextGroup, 0, 0) 
#endif




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
RTS_RESULT CDECL UserDBObjectGetGroupRights(RTS_HANDLE hObject, RTS_HANDLE hGroup, RTS_UI32 *pulRights, RTS_UI32 *pulDeniedRights);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTGETGROUPRIGHTS) (RTS_HANDLE hObject, RTS_HANDLE hGroup, RTS_UI32 *pulRights, RTS_UI32 *pulDeniedRights);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTGETGROUPRIGHTS_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetGroupRights
	#define EXT_UserDBObjectGetGroupRights
	#define GET_UserDBObjectGetGroupRights(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetGroupRights(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectGetGroupRights  FALSE
	#define EXP_UserDBObjectGetGroupRights  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetGroupRights
	#define EXT_UserDBObjectGetGroupRights
	#define GET_UserDBObjectGetGroupRights(fl)  CAL_CMGETAPI( "UserDBObjectGetGroupRights" ) 
	#define CAL_UserDBObjectGetGroupRights  UserDBObjectGetGroupRights
	#define CHK_UserDBObjectGetGroupRights  TRUE
	#define EXP_UserDBObjectGetGroupRights  CAL_CMEXPAPI( "UserDBObjectGetGroupRights" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectGetGroupRights
	#define EXT_UserDBObjectGetGroupRights
	#define GET_UserDBObjectGetGroupRights(fl)  CAL_CMGETAPI( "UserDBObjectGetGroupRights" ) 
	#define CAL_UserDBObjectGetGroupRights  UserDBObjectGetGroupRights
	#define CHK_UserDBObjectGetGroupRights  TRUE
	#define EXP_UserDBObjectGetGroupRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetGroupRights", (RTS_UINTPTR)UserDBObjectGetGroupRights, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectGetGroupRights
	#define EXT_CmpUserDBObjectsUserDBObjectGetGroupRights
	#define GET_CmpUserDBObjectsUserDBObjectGetGroupRights  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectGetGroupRights pICmpUserDBObjects->IUserDBObjectGetGroupRights
	#define CHK_CmpUserDBObjectsUserDBObjectGetGroupRights (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectGetGroupRights  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetGroupRights
	#define EXT_UserDBObjectGetGroupRights
	#define GET_UserDBObjectGetGroupRights(fl)  CAL_CMGETAPI( "UserDBObjectGetGroupRights" ) 
	#define CAL_UserDBObjectGetGroupRights pICmpUserDBObjects->IUserDBObjectGetGroupRights
	#define CHK_UserDBObjectGetGroupRights (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectGetGroupRights  CAL_CMEXPAPI( "UserDBObjectGetGroupRights" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetGroupRights  PFUSERDBOBJECTGETGROUPRIGHTS pfUserDBObjectGetGroupRights;
	#define EXT_UserDBObjectGetGroupRights  extern PFUSERDBOBJECTGETGROUPRIGHTS pfUserDBObjectGetGroupRights;
	#define GET_UserDBObjectGetGroupRights(fl)  s_pfCMGetAPI2( "UserDBObjectGetGroupRights", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetGroupRights, (fl), 0, 0)
	#define CAL_UserDBObjectGetGroupRights  pfUserDBObjectGetGroupRights
	#define CHK_UserDBObjectGetGroupRights  (pfUserDBObjectGetGroupRights != NULL)
	#define EXP_UserDBObjectGetGroupRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetGroupRights", (RTS_UINTPTR)UserDBObjectGetGroupRights, 0, 0) 
#endif




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
RTS_RESULT CDECL UserDBObjectHasRights(char *pszObject, RTS_HANDLE hUser, RTS_UI32 ulRequestedRights);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTHASRIGHTS) (char *pszObject, RTS_HANDLE hUser, RTS_UI32 ulRequestedRights);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTHASRIGHTS_NOTIMPLEMENTED)
	#define USE_UserDBObjectHasRights
	#define EXT_UserDBObjectHasRights
	#define GET_UserDBObjectHasRights(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectHasRights(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectHasRights  FALSE
	#define EXP_UserDBObjectHasRights  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectHasRights
	#define EXT_UserDBObjectHasRights
	#define GET_UserDBObjectHasRights(fl)  CAL_CMGETAPI( "UserDBObjectHasRights" ) 
	#define CAL_UserDBObjectHasRights  UserDBObjectHasRights
	#define CHK_UserDBObjectHasRights  TRUE
	#define EXP_UserDBObjectHasRights  CAL_CMEXPAPI( "UserDBObjectHasRights" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectHasRights
	#define EXT_UserDBObjectHasRights
	#define GET_UserDBObjectHasRights(fl)  CAL_CMGETAPI( "UserDBObjectHasRights" ) 
	#define CAL_UserDBObjectHasRights  UserDBObjectHasRights
	#define CHK_UserDBObjectHasRights  TRUE
	#define EXP_UserDBObjectHasRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectHasRights", (RTS_UINTPTR)UserDBObjectHasRights, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectHasRights
	#define EXT_CmpUserDBObjectsUserDBObjectHasRights
	#define GET_CmpUserDBObjectsUserDBObjectHasRights  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectHasRights pICmpUserDBObjects->IUserDBObjectHasRights
	#define CHK_CmpUserDBObjectsUserDBObjectHasRights (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectHasRights  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectHasRights
	#define EXT_UserDBObjectHasRights
	#define GET_UserDBObjectHasRights(fl)  CAL_CMGETAPI( "UserDBObjectHasRights" ) 
	#define CAL_UserDBObjectHasRights pICmpUserDBObjects->IUserDBObjectHasRights
	#define CHK_UserDBObjectHasRights (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectHasRights  CAL_CMEXPAPI( "UserDBObjectHasRights" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectHasRights  PFUSERDBOBJECTHASRIGHTS pfUserDBObjectHasRights;
	#define EXT_UserDBObjectHasRights  extern PFUSERDBOBJECTHASRIGHTS pfUserDBObjectHasRights;
	#define GET_UserDBObjectHasRights(fl)  s_pfCMGetAPI2( "UserDBObjectHasRights", (RTS_VOID_FCTPTR *)&pfUserDBObjectHasRights, (fl), 0, 0)
	#define CAL_UserDBObjectHasRights  pfUserDBObjectHasRights
	#define CHK_UserDBObjectHasRights  (pfUserDBObjectHasRights != NULL)
	#define EXP_UserDBObjectHasRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectHasRights", (RTS_UINTPTR)UserDBObjectHasRights, 0, 0) 
#endif




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
RTS_RESULT CDECL UserDBObjectGetRights(char *pszObject, RTS_HANDLE hUser, RTS_UI32 *pulRights, RTS_UI32 *pulDeniedRights);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTGETRIGHTS) (char *pszObject, RTS_HANDLE hUser, RTS_UI32 *pulRights, RTS_UI32 *pulDeniedRights);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTGETRIGHTS_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetRights
	#define EXT_UserDBObjectGetRights
	#define GET_UserDBObjectGetRights(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetRights(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectGetRights  FALSE
	#define EXP_UserDBObjectGetRights  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetRights
	#define EXT_UserDBObjectGetRights
	#define GET_UserDBObjectGetRights(fl)  CAL_CMGETAPI( "UserDBObjectGetRights" ) 
	#define CAL_UserDBObjectGetRights  UserDBObjectGetRights
	#define CHK_UserDBObjectGetRights  TRUE
	#define EXP_UserDBObjectGetRights  CAL_CMEXPAPI( "UserDBObjectGetRights" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectGetRights
	#define EXT_UserDBObjectGetRights
	#define GET_UserDBObjectGetRights(fl)  CAL_CMGETAPI( "UserDBObjectGetRights" ) 
	#define CAL_UserDBObjectGetRights  UserDBObjectGetRights
	#define CHK_UserDBObjectGetRights  TRUE
	#define EXP_UserDBObjectGetRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetRights", (RTS_UINTPTR)UserDBObjectGetRights, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectGetRights
	#define EXT_CmpUserDBObjectsUserDBObjectGetRights
	#define GET_CmpUserDBObjectsUserDBObjectGetRights  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectGetRights pICmpUserDBObjects->IUserDBObjectGetRights
	#define CHK_CmpUserDBObjectsUserDBObjectGetRights (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectGetRights  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetRights
	#define EXT_UserDBObjectGetRights
	#define GET_UserDBObjectGetRights(fl)  CAL_CMGETAPI( "UserDBObjectGetRights" ) 
	#define CAL_UserDBObjectGetRights pICmpUserDBObjects->IUserDBObjectGetRights
	#define CHK_UserDBObjectGetRights (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectGetRights  CAL_CMEXPAPI( "UserDBObjectGetRights" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetRights  PFUSERDBOBJECTGETRIGHTS pfUserDBObjectGetRights;
	#define EXT_UserDBObjectGetRights  extern PFUSERDBOBJECTGETRIGHTS pfUserDBObjectGetRights;
	#define GET_UserDBObjectGetRights(fl)  s_pfCMGetAPI2( "UserDBObjectGetRights", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetRights, (fl), 0, 0)
	#define CAL_UserDBObjectGetRights  pfUserDBObjectGetRights
	#define CHK_UserDBObjectGetRights  (pfUserDBObjectGetRights != NULL)
	#define EXP_UserDBObjectGetRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetRights", (RTS_UINTPTR)UserDBObjectGetRights, 0, 0) 
#endif




/**
 * <description>Explicitly activate the usage of user authentication: no assuming of administrator rights
 * NOTE: The UserDBObjects is activated implicitly when a DB file is loaded or configured via CODESYS.
 * </description>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Activation was successful</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 */
RTS_RESULT CDECL UserDBObjectsActivate(void);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTSACTIVATE) (void);
#if defined(CMPUSERDBOBJECTS_NOTIMPLEMENTED) || defined(USERDBOBJECTSACTIVATE_NOTIMPLEMENTED)
	#define USE_UserDBObjectsActivate
	#define EXT_UserDBObjectsActivate
	#define GET_UserDBObjectsActivate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectsActivate()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectsActivate  FALSE
	#define EXP_UserDBObjectsActivate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectsActivate
	#define EXT_UserDBObjectsActivate
	#define GET_UserDBObjectsActivate(fl)  CAL_CMGETAPI( "UserDBObjectsActivate" ) 
	#define CAL_UserDBObjectsActivate  UserDBObjectsActivate
	#define CHK_UserDBObjectsActivate  TRUE
	#define EXP_UserDBObjectsActivate  CAL_CMEXPAPI( "UserDBObjectsActivate" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDBOBJECTS_EXTERNAL)
	#define USE_UserDBObjectsActivate
	#define EXT_UserDBObjectsActivate
	#define GET_UserDBObjectsActivate(fl)  CAL_CMGETAPI( "UserDBObjectsActivate" ) 
	#define CAL_UserDBObjectsActivate  UserDBObjectsActivate
	#define CHK_UserDBObjectsActivate  TRUE
	#define EXP_UserDBObjectsActivate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectsActivate", (RTS_UINTPTR)UserDBObjectsActivate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBObjectsUserDBObjectsActivate
	#define EXT_CmpUserDBObjectsUserDBObjectsActivate
	#define GET_CmpUserDBObjectsUserDBObjectsActivate  ERR_OK
	#define CAL_CmpUserDBObjectsUserDBObjectsActivate pICmpUserDBObjects->IUserDBObjectsActivate
	#define CHK_CmpUserDBObjectsUserDBObjectsActivate (pICmpUserDBObjects != NULL)
	#define EXP_CmpUserDBObjectsUserDBObjectsActivate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectsActivate
	#define EXT_UserDBObjectsActivate
	#define GET_UserDBObjectsActivate(fl)  CAL_CMGETAPI( "UserDBObjectsActivate" ) 
	#define CAL_UserDBObjectsActivate pICmpUserDBObjects->IUserDBObjectsActivate
	#define CHK_UserDBObjectsActivate (pICmpUserDBObjects != NULL)
	#define EXP_UserDBObjectsActivate  CAL_CMEXPAPI( "UserDBObjectsActivate" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectsActivate  PFUSERDBOBJECTSACTIVATE pfUserDBObjectsActivate;
	#define EXT_UserDBObjectsActivate  extern PFUSERDBOBJECTSACTIVATE pfUserDBObjectsActivate;
	#define GET_UserDBObjectsActivate(fl)  s_pfCMGetAPI2( "UserDBObjectsActivate", (RTS_VOID_FCTPTR *)&pfUserDBObjectsActivate, (fl), 0, 0)
	#define CAL_UserDBObjectsActivate  pfUserDBObjectsActivate
	#define CHK_UserDBObjectsActivate  (pfUserDBObjectsActivate != NULL)
	#define EXP_UserDBObjectsActivate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectsActivate", (RTS_UINTPTR)UserDBObjectsActivate, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFUSERDBRIGHTSLOAD IUserDBRightsLoad;
 	PFUSERDBRIGHTSSTORE IUserDBRightsStore;
 	PFUSERDBRIGHTSRELEASE IUserDBRightsRelease;
 	PFUSERDBOBJECTADD IUserDBObjectAdd;
 	PFUSERDBOBJECTREMOVE IUserDBObjectRemove;
 	PFUSERDBOBJECTADDCHILD IUserDBObjectAddChild;
 	PFUSERDBOBJECTSETUSEDRIGHTS IUserDBObjectSetUsedRights;
 	PFUSERDBOBJECTGETUSEDRIGHTS IUserDBObjectGetUsedRights;
 	PFUSERDBOBJECTGETID IUserDBObjectGetID;
 	PFUSERDBOBJECTSETID IUserDBObjectSetID;
 	PFUSERDBOBJECTADDGROUP IUserDBObjectAddGroup;
 	PFUSERDBOBJECTREMOVEGROUP IUserDBObjectRemoveGroup;
 	PFUSERDBOBJECTSETGROUPRIGHTS IUserDBObjectSetGroupRights;
 	PFUSERDBOBJECTSETGROUPDENIEDRIGHTS IUserDBObjectSetGroupDeniedRights;
 	PFUSERDBOBJECTGETFIRST IUserDBObjectGetFirst;
 	PFUSERDBOBJECTGETNEXT IUserDBObjectGetNext;
 	PFUSERDBOBJECTOPEN IUserDBObjectOpen;
 	PFUSERDBOBJECTCLOSE IUserDBObjectClose;
 	PFUSERDBOBJECTGETNAME IUserDBObjectGetName;
 	PFUSERDBOBJECTGETPATH IUserDBObjectGetPath;
 	PFUSERDBOBJECTGETFIRSTCHILD IUserDBObjectGetFirstChild;
 	PFUSERDBOBJECTGETNEXTCHILD IUserDBObjectGetNextChild;
 	PFUSERDBOBJECTGETFATHER IUserDBObjectGetFather;
 	PFUSERDBOBJECTGETFIRSTGROUP IUserDBObjectGetFirstGroup;
 	PFUSERDBOBJECTGETNEXTGROUP IUserDBObjectGetNextGroup;
 	PFUSERDBOBJECTGETGROUPRIGHTS IUserDBObjectGetGroupRights;
 	PFUSERDBOBJECTHASRIGHTS IUserDBObjectHasRights;
 	PFUSERDBOBJECTGETRIGHTS IUserDBObjectGetRights;
 	PFUSERDBOBJECTSACTIVATE IUserDBObjectsActivate;
 } ICmpUserDBObjects_C;

#ifdef CPLUSPLUS
class ICmpUserDBObjects : public IBase
{
	public:
		virtual RTS_RESULT CDECL IUserDBRightsLoad(void) =0;
		virtual RTS_RESULT CDECL IUserDBRightsStore(void) =0;
		virtual RTS_RESULT CDECL IUserDBRightsRelease(void) =0;
		virtual RTS_HANDLE CDECL IUserDBObjectAdd(char *pszObject, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IUserDBObjectRemove(RTS_HANDLE hObject) =0;
		virtual RTS_HANDLE CDECL IUserDBObjectAddChild(RTS_HANDLE hFatherObject, char *pszObject, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IUserDBObjectSetUsedRights(RTS_HANDLE hObject, RTS_UI32 ulUsedRights) =0;
		virtual RTS_RESULT CDECL IUserDBObjectGetUsedRights(RTS_HANDLE hObject, RTS_UI32 *pulUsedRights) =0;
		virtual RTS_RESULT CDECL IUserDBObjectGetID(RTS_HANDLE hObject, RTS_UI32 *pulID) =0;
		virtual RTS_RESULT CDECL IUserDBObjectSetID(RTS_HANDLE hObject, RTS_UI32 ulID) =0;
		virtual RTS_RESULT CDECL IUserDBObjectAddGroup(RTS_HANDLE hObject, RTS_HANDLE hGroup) =0;
		virtual RTS_RESULT CDECL IUserDBObjectRemoveGroup(RTS_HANDLE hObject, RTS_HANDLE hGroup) =0;
		virtual RTS_RESULT CDECL IUserDBObjectSetGroupRights(RTS_HANDLE hObject, RTS_HANDLE hGroup, RTS_UI32 ulRights) =0;
		virtual RTS_RESULT CDECL IUserDBObjectSetGroupDeniedRights(RTS_HANDLE hObject, RTS_HANDLE hGroup, RTS_UI32 ulDeniedRights) =0;
		virtual RTS_HANDLE CDECL IUserDBObjectGetFirst(RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IUserDBObjectGetNext(RTS_HANDLE hPrevObject, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IUserDBObjectOpen(char *pszObject, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IUserDBObjectClose(RTS_HANDLE hObject) =0;
		virtual RTS_RESULT CDECL IUserDBObjectGetName(RTS_HANDLE hObject, char *pszObject, int *piMaxLen) =0;
		virtual RTS_RESULT CDECL IUserDBObjectGetPath(RTS_HANDLE hObject, char *pszObject, int *piMaxLen) =0;
		virtual RTS_HANDLE CDECL IUserDBObjectGetFirstChild(RTS_HANDLE hFatherObject, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IUserDBObjectGetNextChild(RTS_HANDLE hFatherObject, RTS_HANDLE hPrevChildObject, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IUserDBObjectGetFather(RTS_HANDLE hChildObject, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IUserDBObjectGetFirstGroup(RTS_HANDLE hObject, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IUserDBObjectGetNextGroup(RTS_HANDLE hObject, RTS_HANDLE hPrevGroup, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IUserDBObjectGetGroupRights(RTS_HANDLE hObject, RTS_HANDLE hGroup, RTS_UI32 *pulRights, RTS_UI32 *pulDeniedRights) =0;
		virtual RTS_RESULT CDECL IUserDBObjectHasRights(char *pszObject, RTS_HANDLE hUser, RTS_UI32 ulRequestedRights) =0;
		virtual RTS_RESULT CDECL IUserDBObjectGetRights(char *pszObject, RTS_HANDLE hUser, RTS_UI32 *pulRights, RTS_UI32 *pulDeniedRights) =0;
		virtual RTS_RESULT CDECL IUserDBObjectsActivate(void) =0;
};
	#ifndef ITF_CmpUserDBObjects
		#define ITF_CmpUserDBObjects static ICmpUserDBObjects *pICmpUserDBObjects = NULL;
	#endif
	#define EXTITF_CmpUserDBObjects
#else	/*CPLUSPLUS*/
	typedef ICmpUserDBObjects_C		ICmpUserDBObjects;
	#ifndef ITF_CmpUserDBObjects
		#define ITF_CmpUserDBObjects
	#endif
	#define EXTITF_CmpUserDBObjects
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPUSERDBOBJECTSITF_H_*/
