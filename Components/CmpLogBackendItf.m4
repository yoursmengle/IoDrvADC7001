/**
 * <interfacename>CmpLogBackend</interfacename>
 * <description> 
 *	Interface of a logger backend, to store and dump log entries.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpLogBackend')

#include <stdarg.h>

struct tagLogOptions;
struct tagLogEntry;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description> Create a logger </description>
 * <param name="pOptions" type="IN">Options for logger</param>
 * <param name="pResult" type="OUT">Pointer to get the result</param>
 * <result>Handle to the logger, or RTS_INVALID_HANDLE if failed</result>
 */
DEF_CREATECLASSITF2_API(`RTS_HANDLE', `CDECL', `LogBackendCreate', `(RTS_HANDLE hICmpLogBackend, CLASSID ClassId, struct tagLogOptions *pOptions)')

/**
 * <description> Delete a logger </description>
 * <param name="hLog" type="IN">Handle to logger</param>
 * <result>ERR_OK</result>
 */
DEF_DELETECLASSITF2_API(`RTS_RESULT', `CDECL', `LogBackendDelete', `(RTS_HANDLE hBackend)')

/**
 * <description> Add a new log entry </description>
 * <param name="hLog" type="IN">Handle to logger</param>
 * <param name="pOptions" type="IN">Log options</param>
 * <param name="pLog" type="IN">Log entry</param>
 * <param name="pResult" type="OUT">Result</param>
 * <result>Handle to logger (logger could be split into a new logger)</result>
 */
DEF_RETURNHANDLECLASSITF_API(`RTS_HANDLE', `CDECL', `LogBackendAdd', `(RTS_HANDLE hBackend, struct tagLogOptions *pOptions, struct tagLogEntry *pLog, RTS_RESULT *pResult)')

#ifdef __cplusplus
}
#endif
