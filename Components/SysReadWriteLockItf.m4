/**
 * <interfacename>SysReadWriteLock</interfacename>
 * <description>
 * <p>This interface provides a synchronization technique for multiple (shared) reading and single (exclusive) writing access control to a critical resource</p>
 * </description>
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysReadWriteLock')

/**
 * <category>Compiler switch</category>
 * <description>
 * Compiler switch to enable/disable generic implementation.
 * When SYSREADWRITELOCK_GENERIC is not defined, the implementation relies on the underlying operating system.
 * If the switch is defined, the generic implementation is activated, indepentend of the underlying operating system.
 * </description>
 * <element name="SYSREADWRITELOCK_GENERIC">This switch may be defined in sysdefines.h</element>
 */

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This function can be used to create a ReadWrite locking object (synchronization object)
 * RETURN: Handle to the semaphore or RTS_INVALID_HANDLE if failed
 */
typedef struct tagsysrwlcreate_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Pointer to runtime system error code (see CmpErrors.library) */
	RTS_IEC_HANDLE SysRWLCreate;		/* VAR_OUTPUT */	
} sysrwlcreate_struct;

DEF_API(`void',`CDECL',`sysrwlcreate',`(sysrwlcreate_struct *p)',1,0xC47B7841,0x03050B00)

/**
 * This function can be used to delete a ReadWrite locking object (synchronization object)
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysrwldelete_struct
{
	RTS_IEC_HANDLE hRWLock;				/* VAR_INPUT */	/* Handle to the ReadWrite lock object created by SysRWLCreate */
	RTS_IEC_RESULT SysRWLDelete;		/* VAR_OUTPUT */	
} sysrwldelete_struct;

DEF_API(`void',`CDECL',`sysrwldelete',`(sysrwldelete_struct *p)',1,0x27A4A555,0x03050B00)

/**
 * This function to enter a read lock(synchronization object). NOTE: Several readers can enter the lock simultaneously! But they are synchronized against an entered write lock!
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysrwlreadlock_struct
{
	RTS_IEC_HANDLE hRWLock;				/* VAR_INPUT */	/* Handle to the ReadWrite lock object created by SysRWLCreate */
	RTS_IEC_RESULT SysRWLReadLock;		/* VAR_OUTPUT */	
} sysrwlreadlock_struct;

DEF_API(`void',`CDECL',`sysrwlreadlock',`(sysrwlreadlock_struct *p)',1,0x9CD9B449,0x03050B00)

/**
 * This function tries enter a read lock(synchronization object). If a write lock is still active, the functions returns an error. The function succeeded as well, if another read lock
 * is still active.
 * NOTE: Several readers can enter the lock simultaneously! But they are synchronized against an entered write lock!
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysrwlreadlocktry_struct
{
	RTS_IEC_HANDLE hRWLock;				/* VAR_INPUT */	/* Handle to the ReadWrite lock object created by SysRWLCreate */
	RTS_IEC_RESULT SysRWLReadLockTry;	/* VAR_OUTPUT */	
} sysrwlreadlocktry_struct;

DEF_API(`void',`CDECL',`sysrwlreadlocktry',`(sysrwlreadlocktry_struct *p)',1,0x80D90810,0x03050B00)

/**
 * This function leaves a read lock, entered by SysRWLReadLock (synchronization object).
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysrwlreadunlock_struct
{
	RTS_IEC_HANDLE hRWLock;				/* VAR_INPUT */	/* Handle to the ReadWrite lock object created by SysRWLCreate */
	RTS_IEC_RESULT SysRWLReadUnlock;	/* VAR_OUTPUT */	
} sysrwlreadunlock_struct;

DEF_API(`void',`CDECL',`sysrwlreadunlock',`(sysrwlreadunlock_struct *p)',1,0x2F29EF04,0x03050B00)

/**
 * This function to enter a write lock(synchronization object). NOTE: Several readers can enter the lock simultaneously! But they are synchronized against an entered write lock!
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysrwlwritelock_struct
{
	RTS_IEC_HANDLE hRWLock;				/* VAR_INPUT */	/* Handle to the ReadWrite lock object created by SysRWLCreate */
	RTS_IEC_RESULT SysRWLWriteLock;		/* VAR_OUTPUT */	
} sysrwlwritelock_struct;

DEF_API(`void',`CDECL',`sysrwlwritelock',`(sysrwlwritelock_struct *p)',1,0xCA2B1D08,0x03050B00)

/**
 * This function tries enter a write lock(synchronization object). If a write lock is still active, the functions returns an error.
 * NOTE: Several readers can enter the lock simultaneously! But they are synchronized against an entered write lock!
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysrwlwritelocktry_struct
{
	RTS_IEC_HANDLE hRWLock;				/* VAR_INPUT */	/* Handle to the ReadWrite lock object created by SysRWLCreate */
	RTS_IEC_RESULT SysRWLWriteLockTry;	/* VAR_OUTPUT */	
} sysrwlwritelocktry_struct;

DEF_API(`void',`CDECL',`sysrwlwritelocktry',`(sysrwlwritelocktry_struct *p)',1,0x26069BED,0x03050B00)

/**
 * This function leaves a write lock, entered by SysRWLReadLock (synchronization object).
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagsysrwlwriteunlock_struct
{
	RTS_IEC_HANDLE hRWLock;				/* VAR_INPUT */	/* Handle to the ReadWrite lock object created by SysRWLCreate */
	RTS_IEC_RESULT SysRWLWriteUnlock;	/* VAR_OUTPUT */	
} sysrwlwriteunlock_struct;

DEF_API(`void',`CDECL',`sysrwlwriteunlock',`(sysrwlwriteunlock_struct *p)',1,0xDF9F26CB,0x03050B00)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysReadWriteLockOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysReadWriteLockOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>
 * This function creates a ReadWrite locking synchronization object.
 * </description>
 * <param name="pResult" type="IN">Pointer to a variable to return an errorcode (optional).</param>
 * <result>Returns a handle to the synchronization object or RTS_INVALID_HANDLE in case of failure.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">A valid handle is returned.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">Not enough memory available.</errorcode>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SysRWLCreate',`(RTS_RESULT *pResult)')

/**
 * <description>
 * This function deletes a prior created ReadWrite locking synchronization object.
 * </description>
 * <param name="hRWLock" type="IN">Handle to the synchronization object</param>
 * <result>Returns the runtime system error code.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Success</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysRWLDelete',`(RTS_HANDLE hRWLock)')

/**
 * <description>
 * <p>This function enters a read lock (synchronization object).</p>
 * NOTE: Several readers can enter the lock simultaneously! But they are synchronized against an entered write lock!
 * </description>
 * <param name="hRWLock" type="IN">Handle to the synchronization object</param>
 * <result>Returns the runtime system error code.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Success</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysRWLReadLock',`(RTS_HANDLE hRWLock)')

/**
 * <description>
 * <p>This function enters a write lock (synchronization object).</p>
 * NOTE: Several readers can enter the lock simultaneously! But they are synchronized against an entered write lock!
 * </description>
 * <param name="hRWLock" type="IN">Handle to the synchronization object</param>
 * <result>Returns the runtime system error code.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Success</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysRWLWriteLock',`(RTS_HANDLE hRWLock)')

/**
 * <description>
 * <p>This function tries to enter a read lock (synchronization object).</p>
 * If a write lock is still active, the functions returns ERR_FAILED. On the other hand the function succeeds, even though another read lock is still active.
 * NOTE: Several readers can enter the lock simultaneously! But they are synchronized against an entered write lock!
 * </description>
 * <param name="hRWLock" type="IN">Handle to the synchronization object</param>
 * <result>Returns the runtime system error code.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Success</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">The lock can't be entered.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysRWLReadLockTry',`(RTS_HANDLE hRWLock)')

/**
 * <description>
 * <p> This function tries to enter a write lock (synchronization object).</p>
 * If a write lock is still active, the functions returns ERR_FAILED.
 * NOTE: Several readers can enter the lock simultaneously! But they are synchronized against an entered write lock!
 * </description>
 * <param name="hRWLock" type="IN">Handle to the synchronization object</param>
 * <result>Returns the runtime system error code.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Success</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">The lock can't be entered.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysRWLWriteLockTry',`(RTS_HANDLE hRWLock)')

/**
 * <description>
 * This function leaves a read lock, entered by SysRWLReadLock (synchronization object).
 * </description>
 * <param name="hRWLock" type="IN">Handle to the synchronization object</param>
 * <result>Returns the runtime system error code.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Success</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysRWLReadUnlock',`(RTS_HANDLE hRWLock)')

/**
 * <description>
 * This function leaves a write lock, entered by SysRWLWriteLock (synchronization object).
 * </description>
 * <param name="hRWLock" type="IN">Handle to the synchronization object</param>
 * <result>Returns the runtime system error code.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Success</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">The given handle is invalid</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysRWLWriteUnlock',`(RTS_HANDLE hRWLock)')

#ifdef __cplusplus
}
#endif
