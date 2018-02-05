 /**
 * <interfacename>CmpObjectMgr</interfacename>
 * <description>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPOBJECTMGRITF_H_
#define _CMPOBJECTMGRITF_H_

#include "CmpStd.h"

 

 





/* Object Key */
typedef RTS_UI32	IKKey;

/**
 * <category>Static defines</category>
 * <description>Invalid object value that can't be stored in a dictionary</description>
 */
#define IKHS_NO_VALUE ((RTS_UINTPTR)(~0))

/**
 * <category>Static defines</category>
 * <description>Invalid key value that can't be stored in a dictionary</description>
 */
#define IKHS_NO_KEY ((IKKey)(~0))



#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description> 
 *	Opens an object dictionary for the component with CmpId.
 *	<p>This routine should be called during one of the early phases of system initialization process.</p>
 *	<p>One component can open a single dictionary only.</p>
 * </description>
 * <param name="CmpId" type="IN">Specifies a component ID</param>
 * <param name="capacity" type="IN">Supplies the size for the dictionary. The more capacity, the better performance..</param>
 * <param name="bRequireSync" type="IN">if TRUE, sets a requirement to create a thread-safe dictionary for this component</param>
 * <result>Returns a handle to an object dictionary</result>
 */
RTS_HANDLE CDECL ObjManDictionaryOpen(CMPID CmpId, RTS_SIZE capacity, RTS_BOOL bRequireSync);
typedef RTS_HANDLE (CDECL * PFOBJMANDICTIONARYOPEN) (CMPID CmpId, RTS_SIZE capacity, RTS_BOOL bRequireSync);
#if defined(CMPOBJECTMGR_NOTIMPLEMENTED) || defined(OBJMANDICTIONARYOPEN_NOTIMPLEMENTED)
	#define USE_ObjManDictionaryOpen
	#define EXT_ObjManDictionaryOpen
	#define GET_ObjManDictionaryOpen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ObjManDictionaryOpen(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_ObjManDictionaryOpen  FALSE
	#define EXP_ObjManDictionaryOpen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ObjManDictionaryOpen
	#define EXT_ObjManDictionaryOpen
	#define GET_ObjManDictionaryOpen(fl)  CAL_CMGETAPI( "ObjManDictionaryOpen" ) 
	#define CAL_ObjManDictionaryOpen  ObjManDictionaryOpen
	#define CHK_ObjManDictionaryOpen  TRUE
	#define EXP_ObjManDictionaryOpen  CAL_CMEXPAPI( "ObjManDictionaryOpen" ) 
#elif defined(MIXED_LINK) && !defined(CMPOBJECTMGR_EXTERNAL)
	#define USE_ObjManDictionaryOpen
	#define EXT_ObjManDictionaryOpen
	#define GET_ObjManDictionaryOpen(fl)  CAL_CMGETAPI( "ObjManDictionaryOpen" ) 
	#define CAL_ObjManDictionaryOpen  ObjManDictionaryOpen
	#define CHK_ObjManDictionaryOpen  TRUE
	#define EXP_ObjManDictionaryOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ObjManDictionaryOpen", (RTS_UINTPTR)ObjManDictionaryOpen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpObjectMgrObjManDictionaryOpen
	#define EXT_CmpObjectMgrObjManDictionaryOpen
	#define GET_CmpObjectMgrObjManDictionaryOpen  ERR_OK
	#define CAL_CmpObjectMgrObjManDictionaryOpen pICmpObjectMgr->IObjManDictionaryOpen
	#define CHK_CmpObjectMgrObjManDictionaryOpen (pICmpObjectMgr != NULL)
	#define EXP_CmpObjectMgrObjManDictionaryOpen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ObjManDictionaryOpen
	#define EXT_ObjManDictionaryOpen
	#define GET_ObjManDictionaryOpen(fl)  CAL_CMGETAPI( "ObjManDictionaryOpen" ) 
	#define CAL_ObjManDictionaryOpen pICmpObjectMgr->IObjManDictionaryOpen
	#define CHK_ObjManDictionaryOpen (pICmpObjectMgr != NULL)
	#define EXP_ObjManDictionaryOpen  CAL_CMEXPAPI( "ObjManDictionaryOpen" ) 
#else /* DYNAMIC_LINK */
	#define USE_ObjManDictionaryOpen  PFOBJMANDICTIONARYOPEN pfObjManDictionaryOpen;
	#define EXT_ObjManDictionaryOpen  extern PFOBJMANDICTIONARYOPEN pfObjManDictionaryOpen;
	#define GET_ObjManDictionaryOpen(fl)  s_pfCMGetAPI2( "ObjManDictionaryOpen", (RTS_VOID_FCTPTR *)&pfObjManDictionaryOpen, (fl), 0, 0)
	#define CAL_ObjManDictionaryOpen  pfObjManDictionaryOpen
	#define CHK_ObjManDictionaryOpen  (pfObjManDictionaryOpen != NULL)
	#define EXP_ObjManDictionaryOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ObjManDictionaryOpen", (RTS_UINTPTR)ObjManDictionaryOpen, 0, 0) 
#endif




/**
 * <description> 
 *	Closes an object dictionary.
 *	<p>This routine should be called during one of the late phases of system shutdown process.</p>
 * </description>
 * <param name="hDictionary" type="IN">Supplies a handle to a dictionary that has to be closed</param>
 * <result>Error code:
 * <ul>
 *		<li>ERR_OK: Dictionary has been closed successfully</li>
 *		<li>ERR_PARAMETER: Invalid handle passed as the routine parameter</li>
 *		<li>ERR_FAILED: Failed to close a dictionary</li>
 * </ul>
 * </result>
 */
RTS_RESULT CDECL ObjManDictionaryClose(RTS_HANDLE hDictionary);
typedef RTS_RESULT (CDECL * PFOBJMANDICTIONARYCLOSE) (RTS_HANDLE hDictionary);
#if defined(CMPOBJECTMGR_NOTIMPLEMENTED) || defined(OBJMANDICTIONARYCLOSE_NOTIMPLEMENTED)
	#define USE_ObjManDictionaryClose
	#define EXT_ObjManDictionaryClose
	#define GET_ObjManDictionaryClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ObjManDictionaryClose(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_ObjManDictionaryClose  FALSE
	#define EXP_ObjManDictionaryClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ObjManDictionaryClose
	#define EXT_ObjManDictionaryClose
	#define GET_ObjManDictionaryClose(fl)  CAL_CMGETAPI( "ObjManDictionaryClose" ) 
	#define CAL_ObjManDictionaryClose  ObjManDictionaryClose
	#define CHK_ObjManDictionaryClose  TRUE
	#define EXP_ObjManDictionaryClose  CAL_CMEXPAPI( "ObjManDictionaryClose" ) 
#elif defined(MIXED_LINK) && !defined(CMPOBJECTMGR_EXTERNAL)
	#define USE_ObjManDictionaryClose
	#define EXT_ObjManDictionaryClose
	#define GET_ObjManDictionaryClose(fl)  CAL_CMGETAPI( "ObjManDictionaryClose" ) 
	#define CAL_ObjManDictionaryClose  ObjManDictionaryClose
	#define CHK_ObjManDictionaryClose  TRUE
	#define EXP_ObjManDictionaryClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ObjManDictionaryClose", (RTS_UINTPTR)ObjManDictionaryClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpObjectMgrObjManDictionaryClose
	#define EXT_CmpObjectMgrObjManDictionaryClose
	#define GET_CmpObjectMgrObjManDictionaryClose  ERR_OK
	#define CAL_CmpObjectMgrObjManDictionaryClose pICmpObjectMgr->IObjManDictionaryClose
	#define CHK_CmpObjectMgrObjManDictionaryClose (pICmpObjectMgr != NULL)
	#define EXP_CmpObjectMgrObjManDictionaryClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ObjManDictionaryClose
	#define EXT_ObjManDictionaryClose
	#define GET_ObjManDictionaryClose(fl)  CAL_CMGETAPI( "ObjManDictionaryClose" ) 
	#define CAL_ObjManDictionaryClose pICmpObjectMgr->IObjManDictionaryClose
	#define CHK_ObjManDictionaryClose (pICmpObjectMgr != NULL)
	#define EXP_ObjManDictionaryClose  CAL_CMEXPAPI( "ObjManDictionaryClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_ObjManDictionaryClose  PFOBJMANDICTIONARYCLOSE pfObjManDictionaryClose;
	#define EXT_ObjManDictionaryClose  extern PFOBJMANDICTIONARYCLOSE pfObjManDictionaryClose;
	#define GET_ObjManDictionaryClose(fl)  s_pfCMGetAPI2( "ObjManDictionaryClose", (RTS_VOID_FCTPTR *)&pfObjManDictionaryClose, (fl), 0, 0)
	#define CAL_ObjManDictionaryClose  pfObjManDictionaryClose
	#define CHK_ObjManDictionaryClose  (pfObjManDictionaryClose != NULL)
	#define EXP_ObjManDictionaryClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ObjManDictionaryClose", (RTS_UINTPTR)ObjManDictionaryClose, 0, 0) 
#endif




/**
 * <description> 
 *	Adds an object to a dictionary returning a 32-bit key.
 * </description>
 * <param name="hDictionary" type="IN">Supplies a handle to a dictionary</param>
 * <param name="hObject" type="IN">Supplies a handle to an object that has to be added to a dictionary</param>
 * <result>Returns a key to an object, or IKHS_NO_KEY in case of failure</result>
 */
IKKey CDECL ObjManDictionaryAddObject(RTS_HANDLE hDictionary, RTS_HANDLE hObject);
typedef IKKey (CDECL * PFOBJMANDICTIONARYADDOBJECT) (RTS_HANDLE hDictionary, RTS_HANDLE hObject);
#if defined(CMPOBJECTMGR_NOTIMPLEMENTED) || defined(OBJMANDICTIONARYADDOBJECT_NOTIMPLEMENTED)
	#define USE_ObjManDictionaryAddObject
	#define EXT_ObjManDictionaryAddObject
	#define GET_ObjManDictionaryAddObject(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ObjManDictionaryAddObject(p0,p1)  (IKKey)ERR_NOTIMPLEMENTED
	#define CHK_ObjManDictionaryAddObject  FALSE
	#define EXP_ObjManDictionaryAddObject  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ObjManDictionaryAddObject
	#define EXT_ObjManDictionaryAddObject
	#define GET_ObjManDictionaryAddObject(fl)  CAL_CMGETAPI( "ObjManDictionaryAddObject" ) 
	#define CAL_ObjManDictionaryAddObject  ObjManDictionaryAddObject
	#define CHK_ObjManDictionaryAddObject  TRUE
	#define EXP_ObjManDictionaryAddObject  CAL_CMEXPAPI( "ObjManDictionaryAddObject" ) 
#elif defined(MIXED_LINK) && !defined(CMPOBJECTMGR_EXTERNAL)
	#define USE_ObjManDictionaryAddObject
	#define EXT_ObjManDictionaryAddObject
	#define GET_ObjManDictionaryAddObject(fl)  CAL_CMGETAPI( "ObjManDictionaryAddObject" ) 
	#define CAL_ObjManDictionaryAddObject  ObjManDictionaryAddObject
	#define CHK_ObjManDictionaryAddObject  TRUE
	#define EXP_ObjManDictionaryAddObject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ObjManDictionaryAddObject", (RTS_UINTPTR)ObjManDictionaryAddObject, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpObjectMgrObjManDictionaryAddObject
	#define EXT_CmpObjectMgrObjManDictionaryAddObject
	#define GET_CmpObjectMgrObjManDictionaryAddObject  ERR_OK
	#define CAL_CmpObjectMgrObjManDictionaryAddObject pICmpObjectMgr->IObjManDictionaryAddObject
	#define CHK_CmpObjectMgrObjManDictionaryAddObject (pICmpObjectMgr != NULL)
	#define EXP_CmpObjectMgrObjManDictionaryAddObject  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ObjManDictionaryAddObject
	#define EXT_ObjManDictionaryAddObject
	#define GET_ObjManDictionaryAddObject(fl)  CAL_CMGETAPI( "ObjManDictionaryAddObject" ) 
	#define CAL_ObjManDictionaryAddObject pICmpObjectMgr->IObjManDictionaryAddObject
	#define CHK_ObjManDictionaryAddObject (pICmpObjectMgr != NULL)
	#define EXP_ObjManDictionaryAddObject  CAL_CMEXPAPI( "ObjManDictionaryAddObject" ) 
#else /* DYNAMIC_LINK */
	#define USE_ObjManDictionaryAddObject  PFOBJMANDICTIONARYADDOBJECT pfObjManDictionaryAddObject;
	#define EXT_ObjManDictionaryAddObject  extern PFOBJMANDICTIONARYADDOBJECT pfObjManDictionaryAddObject;
	#define GET_ObjManDictionaryAddObject(fl)  s_pfCMGetAPI2( "ObjManDictionaryAddObject", (RTS_VOID_FCTPTR *)&pfObjManDictionaryAddObject, (fl), 0, 0)
	#define CAL_ObjManDictionaryAddObject  pfObjManDictionaryAddObject
	#define CHK_ObjManDictionaryAddObject  (pfObjManDictionaryAddObject != NULL)
	#define EXP_ObjManDictionaryAddObject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ObjManDictionaryAddObject", (RTS_UINTPTR)ObjManDictionaryAddObject, 0, 0) 
#endif




/**
 * <description> 
 *	Removes an object from a dictionary.
 * </description>
 * <param name="hDictionary" type="IN">Supplies a handle to a dictionary</param>
 * <param name="hObject" type="IN">Supplies a handle to an object that has to be removed from a dictionary</param>
 * <result>Error code:
 * <ul>
 *		<li>ERR_OK: Object has been removed successfully</li>
 *		<li>ERR_PARAMETER: Invalid handle passed as the routine parameter</li>
 *		<li>ERR_FAILED: Object not found</li>
 * </ul>
 * </result>
 */
RTS_RESULT CDECL ObjManDictionaryRemoveObject(RTS_HANDLE hDictionary, RTS_HANDLE hObject);
typedef RTS_RESULT (CDECL * PFOBJMANDICTIONARYREMOVEOBJECT) (RTS_HANDLE hDictionary, RTS_HANDLE hObject);
#if defined(CMPOBJECTMGR_NOTIMPLEMENTED) || defined(OBJMANDICTIONARYREMOVEOBJECT_NOTIMPLEMENTED)
	#define USE_ObjManDictionaryRemoveObject
	#define EXT_ObjManDictionaryRemoveObject
	#define GET_ObjManDictionaryRemoveObject(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ObjManDictionaryRemoveObject(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_ObjManDictionaryRemoveObject  FALSE
	#define EXP_ObjManDictionaryRemoveObject  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ObjManDictionaryRemoveObject
	#define EXT_ObjManDictionaryRemoveObject
	#define GET_ObjManDictionaryRemoveObject(fl)  CAL_CMGETAPI( "ObjManDictionaryRemoveObject" ) 
	#define CAL_ObjManDictionaryRemoveObject  ObjManDictionaryRemoveObject
	#define CHK_ObjManDictionaryRemoveObject  TRUE
	#define EXP_ObjManDictionaryRemoveObject  CAL_CMEXPAPI( "ObjManDictionaryRemoveObject" ) 
#elif defined(MIXED_LINK) && !defined(CMPOBJECTMGR_EXTERNAL)
	#define USE_ObjManDictionaryRemoveObject
	#define EXT_ObjManDictionaryRemoveObject
	#define GET_ObjManDictionaryRemoveObject(fl)  CAL_CMGETAPI( "ObjManDictionaryRemoveObject" ) 
	#define CAL_ObjManDictionaryRemoveObject  ObjManDictionaryRemoveObject
	#define CHK_ObjManDictionaryRemoveObject  TRUE
	#define EXP_ObjManDictionaryRemoveObject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ObjManDictionaryRemoveObject", (RTS_UINTPTR)ObjManDictionaryRemoveObject, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpObjectMgrObjManDictionaryRemoveObject
	#define EXT_CmpObjectMgrObjManDictionaryRemoveObject
	#define GET_CmpObjectMgrObjManDictionaryRemoveObject  ERR_OK
	#define CAL_CmpObjectMgrObjManDictionaryRemoveObject pICmpObjectMgr->IObjManDictionaryRemoveObject
	#define CHK_CmpObjectMgrObjManDictionaryRemoveObject (pICmpObjectMgr != NULL)
	#define EXP_CmpObjectMgrObjManDictionaryRemoveObject  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ObjManDictionaryRemoveObject
	#define EXT_ObjManDictionaryRemoveObject
	#define GET_ObjManDictionaryRemoveObject(fl)  CAL_CMGETAPI( "ObjManDictionaryRemoveObject" ) 
	#define CAL_ObjManDictionaryRemoveObject pICmpObjectMgr->IObjManDictionaryRemoveObject
	#define CHK_ObjManDictionaryRemoveObject (pICmpObjectMgr != NULL)
	#define EXP_ObjManDictionaryRemoveObject  CAL_CMEXPAPI( "ObjManDictionaryRemoveObject" ) 
#else /* DYNAMIC_LINK */
	#define USE_ObjManDictionaryRemoveObject  PFOBJMANDICTIONARYREMOVEOBJECT pfObjManDictionaryRemoveObject;
	#define EXT_ObjManDictionaryRemoveObject  extern PFOBJMANDICTIONARYREMOVEOBJECT pfObjManDictionaryRemoveObject;
	#define GET_ObjManDictionaryRemoveObject(fl)  s_pfCMGetAPI2( "ObjManDictionaryRemoveObject", (RTS_VOID_FCTPTR *)&pfObjManDictionaryRemoveObject, (fl), 0, 0)
	#define CAL_ObjManDictionaryRemoveObject  pfObjManDictionaryRemoveObject
	#define CHK_ObjManDictionaryRemoveObject  (pfObjManDictionaryRemoveObject != NULL)
	#define EXP_ObjManDictionaryRemoveObject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ObjManDictionaryRemoveObject", (RTS_UINTPTR)ObjManDictionaryRemoveObject, 0, 0) 
#endif




/**
 * <description> 
 *	Removes an object from a dictionary by a key.
 * </description>
 * <param name="hDictionary" type="IN">Supplies a handle to a dictionary</param>
 * <param name="key" type="IN">Supplies a key to an object that has to be removed from a dictionary</param>
 * <result>Error code:
 * <ul>
 *		<li>ERR_OK: Object has been removed successfully</li>
 *		<li>ERR_PARAMETER: Invalid handle or key passed as the routine parameter</li>
 *		<li>ERR_FAILED: Object not found</li>
 * </ul>
 * </result>
 */
RTS_RESULT CDECL ObjManDictionaryRemoveKey(RTS_HANDLE hDictionary, IKKey key);
typedef RTS_RESULT (CDECL * PFOBJMANDICTIONARYREMOVEKEY) (RTS_HANDLE hDictionary, IKKey key);
#if defined(CMPOBJECTMGR_NOTIMPLEMENTED) || defined(OBJMANDICTIONARYREMOVEKEY_NOTIMPLEMENTED)
	#define USE_ObjManDictionaryRemoveKey
	#define EXT_ObjManDictionaryRemoveKey
	#define GET_ObjManDictionaryRemoveKey(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ObjManDictionaryRemoveKey(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_ObjManDictionaryRemoveKey  FALSE
	#define EXP_ObjManDictionaryRemoveKey  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ObjManDictionaryRemoveKey
	#define EXT_ObjManDictionaryRemoveKey
	#define GET_ObjManDictionaryRemoveKey(fl)  CAL_CMGETAPI( "ObjManDictionaryRemoveKey" ) 
	#define CAL_ObjManDictionaryRemoveKey  ObjManDictionaryRemoveKey
	#define CHK_ObjManDictionaryRemoveKey  TRUE
	#define EXP_ObjManDictionaryRemoveKey  CAL_CMEXPAPI( "ObjManDictionaryRemoveKey" ) 
#elif defined(MIXED_LINK) && !defined(CMPOBJECTMGR_EXTERNAL)
	#define USE_ObjManDictionaryRemoveKey
	#define EXT_ObjManDictionaryRemoveKey
	#define GET_ObjManDictionaryRemoveKey(fl)  CAL_CMGETAPI( "ObjManDictionaryRemoveKey" ) 
	#define CAL_ObjManDictionaryRemoveKey  ObjManDictionaryRemoveKey
	#define CHK_ObjManDictionaryRemoveKey  TRUE
	#define EXP_ObjManDictionaryRemoveKey  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ObjManDictionaryRemoveKey", (RTS_UINTPTR)ObjManDictionaryRemoveKey, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpObjectMgrObjManDictionaryRemoveKey
	#define EXT_CmpObjectMgrObjManDictionaryRemoveKey
	#define GET_CmpObjectMgrObjManDictionaryRemoveKey  ERR_OK
	#define CAL_CmpObjectMgrObjManDictionaryRemoveKey pICmpObjectMgr->IObjManDictionaryRemoveKey
	#define CHK_CmpObjectMgrObjManDictionaryRemoveKey (pICmpObjectMgr != NULL)
	#define EXP_CmpObjectMgrObjManDictionaryRemoveKey  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ObjManDictionaryRemoveKey
	#define EXT_ObjManDictionaryRemoveKey
	#define GET_ObjManDictionaryRemoveKey(fl)  CAL_CMGETAPI( "ObjManDictionaryRemoveKey" ) 
	#define CAL_ObjManDictionaryRemoveKey pICmpObjectMgr->IObjManDictionaryRemoveKey
	#define CHK_ObjManDictionaryRemoveKey (pICmpObjectMgr != NULL)
	#define EXP_ObjManDictionaryRemoveKey  CAL_CMEXPAPI( "ObjManDictionaryRemoveKey" ) 
#else /* DYNAMIC_LINK */
	#define USE_ObjManDictionaryRemoveKey  PFOBJMANDICTIONARYREMOVEKEY pfObjManDictionaryRemoveKey;
	#define EXT_ObjManDictionaryRemoveKey  extern PFOBJMANDICTIONARYREMOVEKEY pfObjManDictionaryRemoveKey;
	#define GET_ObjManDictionaryRemoveKey(fl)  s_pfCMGetAPI2( "ObjManDictionaryRemoveKey", (RTS_VOID_FCTPTR *)&pfObjManDictionaryRemoveKey, (fl), 0, 0)
	#define CAL_ObjManDictionaryRemoveKey  pfObjManDictionaryRemoveKey
	#define CHK_ObjManDictionaryRemoveKey  (pfObjManDictionaryRemoveKey != NULL)
	#define EXP_ObjManDictionaryRemoveKey  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ObjManDictionaryRemoveKey", (RTS_UINTPTR)ObjManDictionaryRemoveKey, 0, 0) 
#endif




/**
 * <description> 
 *	Clears a dictionary.
 * </description>
 * <param name="hDictionary" type="IN">Supplies a handle to a dictionary</param>
 * <result>Error code:
 * <ul>
 *		<li>ERR_OK: Dictionary has been cleared successfully</li>
 *		<li>ERR_PARAMETER: Invalid handle passed as the routine parameter</li>
 *		<li>ERR_FAILED: Dictionary not found</li>
 * </ul>
 * </result>
 */
RTS_RESULT CDECL ObjManDictionaryClear(RTS_HANDLE hDictionary);
typedef RTS_RESULT (CDECL * PFOBJMANDICTIONARYCLEAR) (RTS_HANDLE hDictionary);
#if defined(CMPOBJECTMGR_NOTIMPLEMENTED) || defined(OBJMANDICTIONARYCLEAR_NOTIMPLEMENTED)
	#define USE_ObjManDictionaryClear
	#define EXT_ObjManDictionaryClear
	#define GET_ObjManDictionaryClear(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ObjManDictionaryClear(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_ObjManDictionaryClear  FALSE
	#define EXP_ObjManDictionaryClear  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ObjManDictionaryClear
	#define EXT_ObjManDictionaryClear
	#define GET_ObjManDictionaryClear(fl)  CAL_CMGETAPI( "ObjManDictionaryClear" ) 
	#define CAL_ObjManDictionaryClear  ObjManDictionaryClear
	#define CHK_ObjManDictionaryClear  TRUE
	#define EXP_ObjManDictionaryClear  CAL_CMEXPAPI( "ObjManDictionaryClear" ) 
#elif defined(MIXED_LINK) && !defined(CMPOBJECTMGR_EXTERNAL)
	#define USE_ObjManDictionaryClear
	#define EXT_ObjManDictionaryClear
	#define GET_ObjManDictionaryClear(fl)  CAL_CMGETAPI( "ObjManDictionaryClear" ) 
	#define CAL_ObjManDictionaryClear  ObjManDictionaryClear
	#define CHK_ObjManDictionaryClear  TRUE
	#define EXP_ObjManDictionaryClear  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ObjManDictionaryClear", (RTS_UINTPTR)ObjManDictionaryClear, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpObjectMgrObjManDictionaryClear
	#define EXT_CmpObjectMgrObjManDictionaryClear
	#define GET_CmpObjectMgrObjManDictionaryClear  ERR_OK
	#define CAL_CmpObjectMgrObjManDictionaryClear pICmpObjectMgr->IObjManDictionaryClear
	#define CHK_CmpObjectMgrObjManDictionaryClear (pICmpObjectMgr != NULL)
	#define EXP_CmpObjectMgrObjManDictionaryClear  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ObjManDictionaryClear
	#define EXT_ObjManDictionaryClear
	#define GET_ObjManDictionaryClear(fl)  CAL_CMGETAPI( "ObjManDictionaryClear" ) 
	#define CAL_ObjManDictionaryClear pICmpObjectMgr->IObjManDictionaryClear
	#define CHK_ObjManDictionaryClear (pICmpObjectMgr != NULL)
	#define EXP_ObjManDictionaryClear  CAL_CMEXPAPI( "ObjManDictionaryClear" ) 
#else /* DYNAMIC_LINK */
	#define USE_ObjManDictionaryClear  PFOBJMANDICTIONARYCLEAR pfObjManDictionaryClear;
	#define EXT_ObjManDictionaryClear  extern PFOBJMANDICTIONARYCLEAR pfObjManDictionaryClear;
	#define GET_ObjManDictionaryClear(fl)  s_pfCMGetAPI2( "ObjManDictionaryClear", (RTS_VOID_FCTPTR *)&pfObjManDictionaryClear, (fl), 0, 0)
	#define CAL_ObjManDictionaryClear  pfObjManDictionaryClear
	#define CHK_ObjManDictionaryClear  (pfObjManDictionaryClear != NULL)
	#define EXP_ObjManDictionaryClear  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ObjManDictionaryClear", (RTS_UINTPTR)ObjManDictionaryClear, 0, 0) 
#endif




/**
 * <description> 
 *	Returns the number of elements in a dictionary.
 * </description>
 * <param name="hDictionary" type="IN">Supplies a handle to a dictionary</param>
 * <param name="pSize" type="OUT">Contains the number of elements in a dictionary</param>
 * <result>Error code:
 * <ul>
 *		<li>ERR_OK: pSize contains some valid value</li>
 *		<li>ERR_PARAMETER: Invalid handle or null pointer passed as the routine parameter</li>
 *		<li>ERR_FAILED: Dictionary not found</li>
 * </ul>
 * </result>
 */
RTS_RESULT CDECL ObjManDictionaryGetSize(RTS_HANDLE hDictionary, RTS_SIZE* pSize);
typedef RTS_RESULT (CDECL * PFOBJMANDICTIONARYGETSIZE) (RTS_HANDLE hDictionary, RTS_SIZE* pSize);
#if defined(CMPOBJECTMGR_NOTIMPLEMENTED) || defined(OBJMANDICTIONARYGETSIZE_NOTIMPLEMENTED)
	#define USE_ObjManDictionaryGetSize
	#define EXT_ObjManDictionaryGetSize
	#define GET_ObjManDictionaryGetSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ObjManDictionaryGetSize(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_ObjManDictionaryGetSize  FALSE
	#define EXP_ObjManDictionaryGetSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ObjManDictionaryGetSize
	#define EXT_ObjManDictionaryGetSize
	#define GET_ObjManDictionaryGetSize(fl)  CAL_CMGETAPI( "ObjManDictionaryGetSize" ) 
	#define CAL_ObjManDictionaryGetSize  ObjManDictionaryGetSize
	#define CHK_ObjManDictionaryGetSize  TRUE
	#define EXP_ObjManDictionaryGetSize  CAL_CMEXPAPI( "ObjManDictionaryGetSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPOBJECTMGR_EXTERNAL)
	#define USE_ObjManDictionaryGetSize
	#define EXT_ObjManDictionaryGetSize
	#define GET_ObjManDictionaryGetSize(fl)  CAL_CMGETAPI( "ObjManDictionaryGetSize" ) 
	#define CAL_ObjManDictionaryGetSize  ObjManDictionaryGetSize
	#define CHK_ObjManDictionaryGetSize  TRUE
	#define EXP_ObjManDictionaryGetSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ObjManDictionaryGetSize", (RTS_UINTPTR)ObjManDictionaryGetSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpObjectMgrObjManDictionaryGetSize
	#define EXT_CmpObjectMgrObjManDictionaryGetSize
	#define GET_CmpObjectMgrObjManDictionaryGetSize  ERR_OK
	#define CAL_CmpObjectMgrObjManDictionaryGetSize pICmpObjectMgr->IObjManDictionaryGetSize
	#define CHK_CmpObjectMgrObjManDictionaryGetSize (pICmpObjectMgr != NULL)
	#define EXP_CmpObjectMgrObjManDictionaryGetSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ObjManDictionaryGetSize
	#define EXT_ObjManDictionaryGetSize
	#define GET_ObjManDictionaryGetSize(fl)  CAL_CMGETAPI( "ObjManDictionaryGetSize" ) 
	#define CAL_ObjManDictionaryGetSize pICmpObjectMgr->IObjManDictionaryGetSize
	#define CHK_ObjManDictionaryGetSize (pICmpObjectMgr != NULL)
	#define EXP_ObjManDictionaryGetSize  CAL_CMEXPAPI( "ObjManDictionaryGetSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_ObjManDictionaryGetSize  PFOBJMANDICTIONARYGETSIZE pfObjManDictionaryGetSize;
	#define EXT_ObjManDictionaryGetSize  extern PFOBJMANDICTIONARYGETSIZE pfObjManDictionaryGetSize;
	#define GET_ObjManDictionaryGetSize(fl)  s_pfCMGetAPI2( "ObjManDictionaryGetSize", (RTS_VOID_FCTPTR *)&pfObjManDictionaryGetSize, (fl), 0, 0)
	#define CAL_ObjManDictionaryGetSize  pfObjManDictionaryGetSize
	#define CHK_ObjManDictionaryGetSize  (pfObjManDictionaryGetSize != NULL)
	#define EXP_ObjManDictionaryGetSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ObjManDictionaryGetSize", (RTS_UINTPTR)ObjManDictionaryGetSize, 0, 0) 
#endif





/**
 * <description> 
 *	Returns a 32-bit key for an object previously added to a dictionary.
 * </description>
 * <param name="hDictionary" type="IN">Supplies a handle to a dictionary</param>
 * <param name="hObject" type="IN">Supplies a handle to an object previously added to a dictionary</param>
 * <result>Returns a key to an object, or IKHS_NO_KEY in case of failure</result>
 */
IKKey CDECL ObjManDictionaryGetKey(RTS_HANDLE hDictionary, RTS_HANDLE hObject);
typedef IKKey (CDECL * PFOBJMANDICTIONARYGETKEY) (RTS_HANDLE hDictionary, RTS_HANDLE hObject);
#if defined(CMPOBJECTMGR_NOTIMPLEMENTED) || defined(OBJMANDICTIONARYGETKEY_NOTIMPLEMENTED)
	#define USE_ObjManDictionaryGetKey
	#define EXT_ObjManDictionaryGetKey
	#define GET_ObjManDictionaryGetKey(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ObjManDictionaryGetKey(p0,p1)  (IKKey)ERR_NOTIMPLEMENTED
	#define CHK_ObjManDictionaryGetKey  FALSE
	#define EXP_ObjManDictionaryGetKey  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ObjManDictionaryGetKey
	#define EXT_ObjManDictionaryGetKey
	#define GET_ObjManDictionaryGetKey(fl)  CAL_CMGETAPI( "ObjManDictionaryGetKey" ) 
	#define CAL_ObjManDictionaryGetKey  ObjManDictionaryGetKey
	#define CHK_ObjManDictionaryGetKey  TRUE
	#define EXP_ObjManDictionaryGetKey  CAL_CMEXPAPI( "ObjManDictionaryGetKey" ) 
#elif defined(MIXED_LINK) && !defined(CMPOBJECTMGR_EXTERNAL)
	#define USE_ObjManDictionaryGetKey
	#define EXT_ObjManDictionaryGetKey
	#define GET_ObjManDictionaryGetKey(fl)  CAL_CMGETAPI( "ObjManDictionaryGetKey" ) 
	#define CAL_ObjManDictionaryGetKey  ObjManDictionaryGetKey
	#define CHK_ObjManDictionaryGetKey  TRUE
	#define EXP_ObjManDictionaryGetKey  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ObjManDictionaryGetKey", (RTS_UINTPTR)ObjManDictionaryGetKey, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpObjectMgrObjManDictionaryGetKey
	#define EXT_CmpObjectMgrObjManDictionaryGetKey
	#define GET_CmpObjectMgrObjManDictionaryGetKey  ERR_OK
	#define CAL_CmpObjectMgrObjManDictionaryGetKey pICmpObjectMgr->IObjManDictionaryGetKey
	#define CHK_CmpObjectMgrObjManDictionaryGetKey (pICmpObjectMgr != NULL)
	#define EXP_CmpObjectMgrObjManDictionaryGetKey  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ObjManDictionaryGetKey
	#define EXT_ObjManDictionaryGetKey
	#define GET_ObjManDictionaryGetKey(fl)  CAL_CMGETAPI( "ObjManDictionaryGetKey" ) 
	#define CAL_ObjManDictionaryGetKey pICmpObjectMgr->IObjManDictionaryGetKey
	#define CHK_ObjManDictionaryGetKey (pICmpObjectMgr != NULL)
	#define EXP_ObjManDictionaryGetKey  CAL_CMEXPAPI( "ObjManDictionaryGetKey" ) 
#else /* DYNAMIC_LINK */
	#define USE_ObjManDictionaryGetKey  PFOBJMANDICTIONARYGETKEY pfObjManDictionaryGetKey;
	#define EXT_ObjManDictionaryGetKey  extern PFOBJMANDICTIONARYGETKEY pfObjManDictionaryGetKey;
	#define GET_ObjManDictionaryGetKey(fl)  s_pfCMGetAPI2( "ObjManDictionaryGetKey", (RTS_VOID_FCTPTR *)&pfObjManDictionaryGetKey, (fl), 0, 0)
	#define CAL_ObjManDictionaryGetKey  pfObjManDictionaryGetKey
	#define CHK_ObjManDictionaryGetKey  (pfObjManDictionaryGetKey != NULL)
	#define EXP_ObjManDictionaryGetKey  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ObjManDictionaryGetKey", (RTS_UINTPTR)ObjManDictionaryGetKey, 0, 0) 
#endif




/**
 * <description> 
 *	Returns a handle to an object by a key.
 * </description>
 * <param name="hDictionary" type="IN">Supplies a handle to a dictionary</param>
 * <param name="key" type="IN">Supplies a key to an object previously added to a dictionary</param>
 * <result>Returns a handle to an object, or RTS_INVALID_HANDLE in case of failure</result>
 */
RTS_HANDLE CDECL ObjManDictionaryGetObject(RTS_HANDLE hDictionary, IKKey key);
typedef RTS_HANDLE (CDECL * PFOBJMANDICTIONARYGETOBJECT) (RTS_HANDLE hDictionary, IKKey key);
#if defined(CMPOBJECTMGR_NOTIMPLEMENTED) || defined(OBJMANDICTIONARYGETOBJECT_NOTIMPLEMENTED)
	#define USE_ObjManDictionaryGetObject
	#define EXT_ObjManDictionaryGetObject
	#define GET_ObjManDictionaryGetObject(fl)  ERR_NOTIMPLEMENTED
	#define CAL_ObjManDictionaryGetObject(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_ObjManDictionaryGetObject  FALSE
	#define EXP_ObjManDictionaryGetObject  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_ObjManDictionaryGetObject
	#define EXT_ObjManDictionaryGetObject
	#define GET_ObjManDictionaryGetObject(fl)  CAL_CMGETAPI( "ObjManDictionaryGetObject" ) 
	#define CAL_ObjManDictionaryGetObject  ObjManDictionaryGetObject
	#define CHK_ObjManDictionaryGetObject  TRUE
	#define EXP_ObjManDictionaryGetObject  CAL_CMEXPAPI( "ObjManDictionaryGetObject" ) 
#elif defined(MIXED_LINK) && !defined(CMPOBJECTMGR_EXTERNAL)
	#define USE_ObjManDictionaryGetObject
	#define EXT_ObjManDictionaryGetObject
	#define GET_ObjManDictionaryGetObject(fl)  CAL_CMGETAPI( "ObjManDictionaryGetObject" ) 
	#define CAL_ObjManDictionaryGetObject  ObjManDictionaryGetObject
	#define CHK_ObjManDictionaryGetObject  TRUE
	#define EXP_ObjManDictionaryGetObject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ObjManDictionaryGetObject", (RTS_UINTPTR)ObjManDictionaryGetObject, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpObjectMgrObjManDictionaryGetObject
	#define EXT_CmpObjectMgrObjManDictionaryGetObject
	#define GET_CmpObjectMgrObjManDictionaryGetObject  ERR_OK
	#define CAL_CmpObjectMgrObjManDictionaryGetObject pICmpObjectMgr->IObjManDictionaryGetObject
	#define CHK_CmpObjectMgrObjManDictionaryGetObject (pICmpObjectMgr != NULL)
	#define EXP_CmpObjectMgrObjManDictionaryGetObject  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_ObjManDictionaryGetObject
	#define EXT_ObjManDictionaryGetObject
	#define GET_ObjManDictionaryGetObject(fl)  CAL_CMGETAPI( "ObjManDictionaryGetObject" ) 
	#define CAL_ObjManDictionaryGetObject pICmpObjectMgr->IObjManDictionaryGetObject
	#define CHK_ObjManDictionaryGetObject (pICmpObjectMgr != NULL)
	#define EXP_ObjManDictionaryGetObject  CAL_CMEXPAPI( "ObjManDictionaryGetObject" ) 
#else /* DYNAMIC_LINK */
	#define USE_ObjManDictionaryGetObject  PFOBJMANDICTIONARYGETOBJECT pfObjManDictionaryGetObject;
	#define EXT_ObjManDictionaryGetObject  extern PFOBJMANDICTIONARYGETOBJECT pfObjManDictionaryGetObject;
	#define GET_ObjManDictionaryGetObject(fl)  s_pfCMGetAPI2( "ObjManDictionaryGetObject", (RTS_VOID_FCTPTR *)&pfObjManDictionaryGetObject, (fl), 0, 0)
	#define CAL_ObjManDictionaryGetObject  pfObjManDictionaryGetObject
	#define CHK_ObjManDictionaryGetObject  (pfObjManDictionaryGetObject != NULL)
	#define EXP_ObjManDictionaryGetObject  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"ObjManDictionaryGetObject", (RTS_UINTPTR)ObjManDictionaryGetObject, 0, 0) 
#endif





#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFOBJMANDICTIONARYOPEN IObjManDictionaryOpen;
 	PFOBJMANDICTIONARYCLOSE IObjManDictionaryClose;
 	PFOBJMANDICTIONARYADDOBJECT IObjManDictionaryAddObject;
 	PFOBJMANDICTIONARYREMOVEOBJECT IObjManDictionaryRemoveObject;
 	PFOBJMANDICTIONARYREMOVEKEY IObjManDictionaryRemoveKey;
 	PFOBJMANDICTIONARYCLEAR IObjManDictionaryClear;
 	PFOBJMANDICTIONARYGETSIZE IObjManDictionaryGetSize;
 	PFOBJMANDICTIONARYGETKEY IObjManDictionaryGetKey;
 	PFOBJMANDICTIONARYGETOBJECT IObjManDictionaryGetObject;
 } ICmpObjectMgr_C;

#ifdef CPLUSPLUS
class ICmpObjectMgr : public IBase
{
	public:
		virtual RTS_HANDLE CDECL IObjManDictionaryOpen(CMPID CmpId, RTS_SIZE capacity, RTS_BOOL bRequireSync) =0;
		virtual RTS_RESULT CDECL IObjManDictionaryClose(RTS_HANDLE hDictionary) =0;
		virtual IKKey CDECL IObjManDictionaryAddObject(RTS_HANDLE hDictionary, RTS_HANDLE hObject) =0;
		virtual RTS_RESULT CDECL IObjManDictionaryRemoveObject(RTS_HANDLE hDictionary, RTS_HANDLE hObject) =0;
		virtual RTS_RESULT CDECL IObjManDictionaryRemoveKey(RTS_HANDLE hDictionary, IKKey key) =0;
		virtual RTS_RESULT CDECL IObjManDictionaryClear(RTS_HANDLE hDictionary) =0;
		virtual RTS_RESULT CDECL IObjManDictionaryGetSize(RTS_HANDLE hDictionary, RTS_SIZE* pSize) =0;
		virtual IKKey CDECL IObjManDictionaryGetKey(RTS_HANDLE hDictionary, RTS_HANDLE hObject) =0;
		virtual RTS_HANDLE CDECL IObjManDictionaryGetObject(RTS_HANDLE hDictionary, IKKey key) =0;
};
	#ifndef ITF_CmpObjectMgr
		#define ITF_CmpObjectMgr static ICmpObjectMgr *pICmpObjectMgr = NULL;
	#endif
	#define EXTITF_CmpObjectMgr
#else	/*CPLUSPLUS*/
	typedef ICmpObjectMgr_C		ICmpObjectMgr;
	#ifndef ITF_CmpObjectMgr
		#define ITF_CmpObjectMgr
	#endif
	#define EXTITF_CmpObjectMgr
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPOBJECTMGRITF_H_*/
