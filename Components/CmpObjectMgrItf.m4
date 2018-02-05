/**
 * <interfacename>CmpObjectMgr</interfacename>
 * <description>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpObjectMgr')


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
DEF_ITF_API(`RTS_HANDLE', `CDECL', `ObjManDictionaryOpen', `(CMPID CmpId, RTS_SIZE capacity, RTS_BOOL bRequireSync)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `ObjManDictionaryClose', `(RTS_HANDLE hDictionary)')

/**
 * <description> 
 *	Adds an object to a dictionary returning a 32-bit key.
 * </description>
 * <param name="hDictionary" type="IN">Supplies a handle to a dictionary</param>
 * <param name="hObject" type="IN">Supplies a handle to an object that has to be added to a dictionary</param>
 * <result>Returns a key to an object, or IKHS_NO_KEY in case of failure</result>
 */
DEF_ITF_API(`IKKey', `CDECL', `ObjManDictionaryAddObject', `(RTS_HANDLE hDictionary, RTS_HANDLE hObject)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `ObjManDictionaryRemoveObject', `(RTS_HANDLE hDictionary, RTS_HANDLE hObject)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `ObjManDictionaryRemoveKey', `(RTS_HANDLE hDictionary, IKKey key)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `ObjManDictionaryClear', `(RTS_HANDLE hDictionary)')

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `ObjManDictionaryGetSize', `(RTS_HANDLE hDictionary, RTS_SIZE* pSize)')


/**
 * <description> 
 *	Returns a 32-bit key for an object previously added to a dictionary.
 * </description>
 * <param name="hDictionary" type="IN">Supplies a handle to a dictionary</param>
 * <param name="hObject" type="IN">Supplies a handle to an object previously added to a dictionary</param>
 * <result>Returns a key to an object, or IKHS_NO_KEY in case of failure</result>
 */
DEF_ITF_API(`IKKey', `CDECL', `ObjManDictionaryGetKey', `(RTS_HANDLE hDictionary, RTS_HANDLE hObject)')

/**
 * <description> 
 *	Returns a handle to an object by a key.
 * </description>
 * <param name="hDictionary" type="IN">Supplies a handle to a dictionary</param>
 * <param name="key" type="IN">Supplies a key to an object previously added to a dictionary</param>
 * <result>Returns a handle to an object, or RTS_INVALID_HANDLE in case of failure</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `ObjManDictionaryGetObject', `(RTS_HANDLE hDictionary, IKKey key)')


#ifdef __cplusplus
}
#endif
