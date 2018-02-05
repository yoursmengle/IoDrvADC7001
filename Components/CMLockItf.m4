/**
 * <interfacename>CMLock</interfacename>
 * <description>
 *	<p>Interface for a generic locking mechanism</p>
 *	<p>If both SysSem and SysInt components are implemented in the runtime system,
 *	a global int-lock implementation can be choosen with CMLOCK_PREFER_SYSINT macro.
 *	Otherwise, a mutex-based implementation is automatically selected.</p>
 *	<p>If either SysSem or SysInt component is implemented only, then
 *	the CMLock implementation is based on an existing component.</p>
 *  <pre>
 *	USAGE in a module:
 *
 *		RTS_HANDLE s_hLock = RTS_INVALID_HANDLE;
 *		CH_INIT:
 *			RTS_RESULT result;
 *			s_hLock = CAL_CMLockCreate(&amp;result);
 *		CH_EXIT:
 *			CAL_CMLockDelete(s_hLock);
 *	
 *		Function()
 *		{
 *			RTS_HANDLE hLock;
 *			CM_GET_LOCK(s_hLock, hLock);
 *		
 *			CAL_CMLockEnter(hLock);
 *			...
 *			CAL_CMLockLeave(hLock);
 *		}
 * </pre>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CMLock')

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(SYSSEM_NOTIMPLEMENTED) && !defined(SYSINT_NOTIMPLEMENTED)
/* If SysSem and SysInt are both implemented, check if there is */
/* a preference to use SysInt */
#	ifndef CMLOCK_PREFER_SYSINT
/* SysInt is not explicitly defined, than we choose CMLOCK_PREFER_SYSSEM */
#		ifndef CMLOCK_PREFER_SYSSEM
#			define CMLOCK_PREFER_SYSSEM
#		endif
#	else
/* SysInt is explicitly defined, than we undef CMLOCK_PREFER_SYSSEM */
#		ifdef CMLOCK_PREFER_SYSSEM
#			undef CMLOCK_PREFER_SYSSEM
#		endif
#	endif
#elif defined(SYSINT_NOTIMPLEMENTED) 
/* SysInt is not implemented, than SysSem has to be used */
#	ifdef CMLOCK_PREFER_SYSINT
#		undef		CMLOCK_PREFER_SYSINT /* SysInt should NOT be used */
#	endif
#ifndef CMLOCK_PREFER_SYSSEM
#		define	CMLOCK_PREFER_SYSSEM	/* SysSem SHOULD be used */
#	endif
#else
/* SysSem is not implemented, than SysInt has to be used */
#	ifdef CMLOCK_PREFER_SYSSEM
#		undef		CMLOCK_PREFER_SYSSEM /* SysSem should NOT be used */
#	endif
#	ifndef CMLOCK_PREFER_SYSINT
#		define	CMLOCK_PREFER_SYSINT /* SysInt should be used */
#	endif
#endif

/**
 * <description> 
 *  Macro to get the correct parameter for the lock functions:
 *		CM_GET_LOCK(hLock, hLocalLock)
 * </description>
 * <param name="hLockObject" type="IN">is retrieved by CMLockCreate()</param>
 * <param name="hLock" type="IN">local variable of type RTS_HANDLE (declared in the local function!)</param>
 * <result>Error code</result>
 */
#if defined(CMLOCK_PREFER_SYSINT)
	#define CM_GET_LOCK(lockobject, lock)	 	RTS_UI32 cmlock;\
												lock = &cmlock;
#elif defined(CMLOCK_PREFER_SYSSEM)
	#define CM_GET_LOCK(lockobject, lock)	 	lock = lockobject;
#else
	#define CM_GET_LOCK(lockobject, lock)
#endif


/**
 * <description> 
 *  Function to create a lock object to synchronize data against concurrent task or interrupt access.
 * </description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the lock object</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `CMLockCreate', `(RTS_RESULT *pResult)')

/**
 * <description> 
 *  Function to delete a lock object.
 * </description>
 * <param name="hLock" type="IN">Handle to the lock object retrieved by CMLockCreate()</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMLockDelete', `(RTS_HANDLE hLock)')

/**
 * <description> 
 *  Function to enter a lock object. After entering, the accessed data is _safe_ against concurrent
 *	access.
 * </description>
 * <param name="hLock" type="IN">Handle to the lock object retrieved by macro: CM_GET_LOCK(hLockObject, hLock)
 *					- hLockObject is retrieved by CMLockCreate()
 *					- hLock is a local variable of type RTS_HANDLE (declared in the local function!)</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMLockEnter', `(RTS_HANDLE hLock)')

/**
 * <description> 
 *  Function to leave a lock object. After leaving, the accessed data is _unsafe_ against concurrent
 *	access.
 * </description>
 * <param name="hLock" type="IN">Handle to the lock object retrieved by CMLockCreate()</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMLockLeave', `(RTS_HANDLE hLock)')

#ifdef __cplusplus
}
#endif
