/**
 * <interfacename>SysCpuBreakpoints</interfacename>
 * <description> 
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysCpuBreakpoints')

/* Since CpuBreakpoints are only available on Windows this interface has to be deactivated by default. */
#if !defined(SYSCPUBREAKPOINTS_IMPLEMENTED) && !defined(SYSCPUBREAKPOINTS_EXTERNAL)
	#define SYSCPUBREAKPOINTS_NOTIMPLEMENTED
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysCpuBreakpointsOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysCpuBreakpointsOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>
 * <p>Function to set a hardware breakpoint (data breakpoint).</p>
 * </description>
 * <param name="hApp" type="IN" range="[RTS_INVALID_HANDLE]">Handle to the application (see CmpAppItf.h)</param>
 * <param name="ulBPType" type="IN" range="[RTS_RANGE_OF_RTS_UI32]">The type of the breakpoint to set (BP_DATA)</param>
 * <param name="pAddress" type="IN">The address in the global data are to be observed</param>
 * <param name="ulSize" type="IN">The size of data to be observed</param>
 * <result>Returns ERR_OK or ERR_FAILED</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysCpuBreakpointSet',`(RTS_HANDLE hApp, RTS_UI32 ulBPType, void *pAddress, RTS_UI32 ulSize)')

 /**
 * <description>
 * <p>Function to delete a hardware breakpoint (data breakpoint).</p>
 * </description>
 * <param name="hApp" type="IN" range="[RTS_INVALID_HANDLE]">Handle to the application (see CmpAppItf.h)</param>
 * <param name="ulBPType" type="IN" range="[RTS_RANGE_OF_RTS_I32]">The type of the breakpoint to set (BP_DATA)</param>
 * <param name="pAddress" type="IN">The address in the global data area of the breakpoint to be deleted</param>
 * <param name="ulSize" type="IN">The size of data of the breakpoint to be deleted</param>
 * <result>Returns ERR_OK or ERR_FAILED</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysCpuBreakpointDelete',`(RTS_HANDLE hApp, RTS_UI32 ulBPType, void *pAddress, RTS_UI32 ulSize)')

 /**
 * <description>
 * <p>Function to retrieve a breakpoint address by the context as produced in the breakpoint exception. This function is system specific and may only be called by other system components.</p>
 * </description>
 * <param name="pContext" type="IN" range="NULL">pointer to the context. This parameter is system specific and is interpreted as a system specific type. (e.g: in Windows CONTEXT). It contains all information necessary to retrieve the active hardware breakpoint.</param>
 * <param name="ppAddress" type="OUT">The address in the global data area of the currently active breakpoint as retrieved according to the pContext.</param>
 * <param name="pulSize" type="OUT">The size of data of the currently active breakpoint as retrieved according to the pContext</param>
 * <result>Returns ERR_OK or ERR_FAILED</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysCpuBreakpointGetAddressByContext',`(void* pContext, RTS_UINTPTR *pAddress, RTS_UI32 *pulSize)')

#ifdef __cplusplus
}
#endif

