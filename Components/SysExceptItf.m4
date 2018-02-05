/**
 * <interfacename>SysExcept</interfacename>
 * <description> 
 *	<p>The SysExcept interface is projected to handle all exceptions in the runtime system. All
 *	available exceptions on the target should be handled. Exception handling is typically cpu
 *	and operating system dependant.</p>
 *	<p>All active code parts in the runtime system (tasks, timer, interrupt handler) must be protected
 *	against software errors, because this could lead to an unpredictable behaviour or crash of the
 *	complete runtime system.</p>
 *	<p>All exceptions are handled in this component as first level.
 *	If the first level handling is done in another component, the component has to call the 
 *	SysExceptGenerateException() routine to	enable second level handling. In this case, the first
 *	level handling must be disabled with a config setting (see below).</p>
 *	<p>The SysExcept component forwards every exception to the component, that manages the active
 *	code, mostly the SysTask, SysTimer or SysInt component. These components must register exception
 *	handlers to the SysExcept component.</p>
 *	<p>As the last station of exception handling, the exception handler of the component, that creates
 *	the active object, was called from the SysTask, SysTimer or SysInt component. Below you can see
 *	the structure and the layers of exception handling:</p>
 *
 * <pre>
 * . +----------------------------------------------------------+
 * . | XXX component:                       Code that generates |
 * . | Registered exceptionhandler          exception (1)       |
 * . | of component, is called. (4)                             |
 * . +----------------------------------------------------------+
 * .      ^                                                 | 
 * .      |                                                 | 
 * .      |                                                 | 
 * . +-----------------------------------------------+      | 
 * . | SysTask or SysTimer component:                |      | 
 * . | Registered exception handler is called (3)    |      | 
 * . +-----------------------------------------------+      | 
 * .      ^                                                 | 
 * .      |                                                 | 
 * .      |                                                 | 
 * . +-----------------------------------------------+      | 
 * . | SysExcept component:                          |      | 
 * . | ::SysExceptGenerateException() is called (2)  |      | 
 * . +-----------------------------------------------+      | 
 * .      ^                                                 | 
 * .      |                                                 | 
 * .      |                    Exception occurred (1a)      | 
 * .      |&lt;------------------------------------------------| 
 * .      |                                                 | 
 * . +-----------------------------------------------+      | 
 * . | OEM component:                                |      | (1b)
 * . | First level exception handling. If the        |      | 
 * . | exception is not in the OEM context, it is    |      | 
 * . | forwarded to the SysExcept component          |      | 
 * . +-----------------------------------------------+      | 
 * .      ^                                                 |
 * .      '-------------------------------------------------'
 * </pre>
 * <p>If RTS_STRUCTURED_EXCEPTION_HANDLING is set as a define, the structured exception handling is activated.
 * To use this exception handling, the following functions must be imported:</p>
 * <ul>
 *    <li>SysExceptTry</li>
 *    <li>SysExceptCatch</li>
 *    <li>SysExceptCatchException</li>
 * </ul>
 * 
 * <p>Here is an example of the usage:</p>
 * <pre>
 * .    Variant 1:
 *.     ----------
 * .    rts_try
 * .    {
 * .        ...
 * .    }
 * .    rts_catch_exception(RTSEXCPT_DIVIDEBYZERO)
 * .    {
 * .        RTS_UI32 exceptionCode = EXCPT_GET_CODE();
 * .        RegContext *pExceptionContext = EXCPT_GET_CONTEXT();
 * .        ...
 * .    }
 * .    rts_catch_exception(RTSEXCPT_DIVIDEBYZERO)
 * .    {
 * .        ...
 * .    }
 * .    rts_catch
 * .    {
 * .        ...
 * .    }
 * .    rts_try_end
 * .   
 * .   
 * .    Variant 2:
 *.     ----------
 * .   
 * .    rts_try
 * .    {
 * .        ...
 * .    }
 * .    rts_catch
 * .    {
 * .        RTS_UI32 exceptionCode = EXCPT_GET_CODE();
 * .        RegContext *pExceptionContext = EXCPT_GET_CONTEXT();
 * .        ...
 * .    }
 * .    rts_try_end
 * </pre>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysExcept')

/**
 * <category>Compiler switch</category>
 * <description>
 *	Compiler switches to enable/disable single features in the component.
 * </description>
 * <element name="RTS_STRUCTURED_EXCEPTION_HANDLING">Switch to enabled structured exception handling. See rts_try/rts_catch for details.</element>
 */

/**
 * <category>Static defines</category>
 * <description>Default number of static interfaces that can be registered on exceptions</description>
 */
#ifndef EXCPT_DEFAULT_NUM_OF_INTERFACES
	#define EXCPT_DEFAULT_NUM_OF_INTERFACES		5
#endif

/**
 * <category>Static defines</category>
 * <description>Maximum number of nested structured exception handler on the same task</description>
 */
#ifndef EXCPT_MAX_NUM_OF_SEH_HANDLER
	#define EXCPT_MAX_NUM_OF_SEH_HANDLER		5
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to enable/disable first level exception handling:
 *	1: enable first level handling
 *	0: disable first level handling. Is done by an OEM component.
 * </description>
 */
#define SYSEXCEPT_KEY_INT_ENABLE_FIRST_LEVEL_HANDLING				"EnableFirstLevelHandling"
#define SYSEXCEPT_VALUE_INT_ENABLE_FIRST_LEVEL_HANDLING_DEFAULT		1

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Disable the FPU Invalid Operation exception</description>
 */
#define SYSEXCEPTKEY_INT_LINUX_DISABLE_FPU_INVALID_EXCEPTION			"Linux.DisableFpuInvalidOperationException"
#define SYSEXCEPTKEY_INT_LINUX_DISABLE_FPU_INVALID_EXCEPTION_DEFAULT	0

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Disable the FPU Overflow exception</description>
 */
#define SYSEXCEPTKEY_INT_LINUX_DISABLE_FPU_OVERFLOW_EXCEPTION			"Linux.DisableFpuOverflowException"
#define SYSEXCEPTKEY_INT_LINUX_DISABLE_FPU_OVERFLOW_EXCEPTION_DEFAULT	0

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Disable the FPU Underflow exception</description>
 */
#define SYSEXCEPTKEY_INT_LINUX_DISABLE_FPU_UNDERFLOW_EXCEPTION			"Linux.DisableFpuUnderflowException"
#define SYSEXCEPTKEY_INT_LINUX_DISABLE_FPU_UNDERFLOW_EXCEPTION_DEFAULT	0

#ifdef RTS_STRUCTURED_EXCEPTION_HANDLING
	#ifndef RTS_JMP_BUF
		#include <setjmp.h>
		#define RTS_JMP_BUF		jmp_buf
	#endif
	#ifndef RTS_SETJMP
		#define RTS_SETJMP		setjmp
	#endif
	#ifndef RTS_LONGJMP
		#define RTS_LONGJMP		longjmp
	#endif
#else
	#define RTS_JMP_BUF			void*
	#define RTS_SETJMP(buf)
	#define RTS_LONGJMP(buf, val)
#endif

#ifndef RTS_FP_BUF
	#define RTS_FP_BUF			void*
#endif
#ifndef RTS_GET_FPENV
	#define RTS_GET_FPENV(buf)
#endif
#ifndef RTS_SET_FPENV
	#define RTS_SET_FPENV(buf)
#endif

/**
 * <category>Exception code</category>
 * <description></description>
 * <element name="ulCode" type="IN">Exception code. Can be an operating system specific exception code
 *		or a runtime specific exception code (see exception code category)</element>
 * <element name="bOSException" type="IN">Exception code flag:
 *		<p>1=exception code is an operating system specific exception code</p>
 *		<p>0=exception code is a runtime code. See exception code category</p></element>
 */
typedef struct tagExceptionCode
{
	RTS_UI32 ulCode;
	int bOSException;
} ExceptionCode;

/**
 * <SIL2/>
 * <category>Exception context</category>
 * <description></description>
 *	<element name="IP" type="IN">Instruction pointer or program counter</element>
 *	<element name="BP" type="IN">Base pointer or frame pointer</element>
 *	<element name="SP" type="IN">Stack pointer</element>
 */
typedef struct RegContexttag
{
	RTS_UINTPTR IP;
	RTS_UINTPTR BP;
	RTS_UINTPTR SP;	
} RegContext;

/**
 * <category>SEH Context</category>
 * <description>Linked list of contexts for the structured exception handling.</description>
 * <element name="ui32Pattern" type="IN">Pattern to check if the stack was overwritten</element>
 * <element name="ui32ExceptionCode" type="IN">Current exception code for this exception frame (might be none)</element>
 * <element name="jmpbuf" type="IN">Context saving buffer for RTS_SETJMP / RTS_LONGJMP</element>
 * <element name="bHandled" type="IN">True, when the exception in this exception frame was already handled</element>
 */
typedef struct tagSEHCOntext
{
	struct tagSEHCOntext *pNext;
	RTS_UI32    ui32Pattern;
	RTS_UI32    ui32ExceptionCode;
	RTS_JMP_BUF jmpbuf;
	RegContext  context;
	RTS_BOOL    bHandled;
	RTS_BOOL    bRegistered;
	RTS_FP_BUF	fpenvbuf;
} SEHContext;

#define SEH_CONTEXT_PATTERN 0xA5A5ACDC

typedef struct
{
	RTS_IEC_HANDLE hSysTask;
	RTS_IEC_UDINT ulException;
	RegContext Context;
	RTS_IEC_RESULT excpthandler;
} excpthandler_struct;

/**
 * <category>Exception handler</category>
 * <description>Function prototype for the exception handler</description>
 * <param name="uiTaskOSHandle" type="IN">Operating system specific task handle</param>
 * <param name="ulException" type="IN">Exception code structure</param>
 * <param name="Context" type="IN">Context of actual exception position</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL ExceptionHandler(RTS_HANDLE uiTaskOSHandle, RTS_UI32 ulException, RegContext Context);
typedef RTS_RESULT (CDECL *PFEXCEPTIONHANDLER)(RTS_HANDLE uiTaskOSHandle, RTS_UI32 ulException, RegContext Context);
typedef void (CDECL*PFEXCEPTIONHANDLERIEC)(excpthandler_struct *p);


/**
 * <category>Exception pseudo code</category>
 * <description>Exception pseudo code to prepare exception handling. Can be used e.g. to release locking objects in the context of the task!</description>
 */
#define RTSEXCPT_FIRST_LEVEL				0x80000000

/**
 * <category>Exception code</category>
 * <description>Invalid</description>
 */
#define RTSEXCPT_UNKNOWN					(UINT32_MAX & ~RTSEXCPT_FIRST_LEVEL) 

/**
 * <category>Exception code</category>
 * <description>No exception</description>
 */
#define RTSEXCPT_NOEXCEPTION				0x00000000

/**
 * <category>Exception code</category>
 * <description>Software watchdog of IEC-task expired</description>
 */
#define RTSEXCPT_WATCHDOG					0x00000010

/**
 * <category>Exception code</category>
 * <description>Hardware watchdog expired. Global software error</description>
 */
#define RTSEXCPT_HARDWAREWATCHDOG			0x00000011

/**
 * <category>Exception code</category>
 * <description>IO config error</description>
 */
#define RTSEXCPT_IO_CONFIG_ERROR			0x00000012

/**
 * <category>Exception code</category>
 * <description>Checksum error after program download</description>
 */
#define RTSEXCPT_PROGRAMCHECKSUM			0x00000013

/**
 * <category>Exception code</category>
 * <description>Fieldbus error</description>
 */
#define RTSEXCPT_FIELDBUS_ERROR				0x00000014

/**
 * <category>Exception code</category>
 * <description>IO-update error</description>
 */
#define RTSEXCPT_IOUPDATE_ERROR				0x00000015

/**
 * <category>Exception code</category>
 * <description>Cycle time exceed</description>
 */
#define RTSEXCPT_CYCLE_TIME_EXCEED			0x00000016

/**
 * <category>Exception code</category>
 * <description>Online change program too large</description>
 */
#define RTSEXCPT_ONLCHANGE_PROGRAM_EXCEEDED 0x00000017

/**
 * <category>Exception code</category>
 * <description>Unresolved external references</description>
 */
#define RTSEXCPT_UNRESOLVED_EXTREFS			0x00000018

/**
 * <category>Exception code</category>
 * <description>Download was rejected</description>
 */
#define RTSEXCPT_DOWNLOAD_REJECTED			0x00000019

/**
 * <category>Exception code</category>
 * <description>Boot project not loaded because retain variables could not be relocated</description>
 */
#define RTSEXCPT_BOOTPROJECT_REJECTED_DUE_RETAIN_ERROR	0x0000001A

/**
 * <category>Exception code</category>
 * <description>Boot project not loaded and deleted</description>
 */
#define RTSEXCPT_LOADBOOTPROJECT_FAILED		0x0000001B

/**
 * <category>Exception code</category>
 * <description>Out of heap memory</description>
 */
#define RTSEXCPT_OUT_OF_MEMORY				0x0000001C

/**
 * <category>Exception code</category>
 * <description>Retain memory corrupt or cannot be mapped</description>
 */
#define RTSEXCPT_RETAIN_MEMORY_ERROR		0x0000001D

/**
 * <category>Exception code</category>
 * <description>Boot project that could be loaded but caused a crash later</description>
 */
#define RTSEXCPT_BOOTPROJECT_CRASH			0x0000001E

/**
 * <category>Exception code</category>
 * <description>Target of the bootproject doesn't match the current target</description>
 */
#define RTSEXCPT_BOOTPROJECTTARGETMISMATCH	0x00000021

/**
 * <category>Exception code</category>
 * <description>Error at scheduling tasks</description>
 */
#define RTSEXCPT_SCHEDULEERROR				0x00000022

/**
 * <category>Exception code</category>
 * <description>Checksum of downloaded file does not match</description>
 */
#define RTSEXCPT_FILE_CHECKSUM_ERR			0x00000023

/**
 * <category>Exception code</category>
 * <description>Retain identity does not match to current bootproject program identity</description>
 */
#define RTSEXCPT_RETAIN_IDENTITY_MISMATCH	0x00000024

/**
 * <category>Exception code</category>
 * <description>Iec task configuration failed</description>
 */
#define RTSEXCPT_IEC_TASK_CONFIG_ERROR		0x00000025

/**
 * <category>Exception code</category>
 * <description>Application is running on wrong target. Can be used for library protection!</description>
 */
#define RTSEXCPT_APP_TARGET_MISMATCH		0x00000026


/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Illegal instruction</description>
 */
#define RTSEXCPT_ILLEGAL_INSTRUCTION		0x00000050

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Access violation</description>
 */
#define RTSEXCPT_ACCESS_VIOLATION			0x00000051

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Privileged instruction</description>
 */
#define RTSEXCPT_PRIV_INSTRUCTION			0x00000052

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Page fault</description>
 */
#define RTSEXCPT_IN_PAGE_ERROR				0x00000053

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Stack overflow</description>
 */
#define RTSEXCPT_STACK_OVERFLOW				0x00000054

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Invalid disposition</description>
 */
#define RTSEXCPT_INVALID_DISPOSITION		0x00000055

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Invalid handle</description>
 */
#define RTSEXCPT_INVALID_HANDLE				0x00000056

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Guard page</description>
 */
#define RTSEXCPT_GUARD_PAGE					0x00000057

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Double fault</description>
 */
#define RTSEXCPT_DOUBLE_FAULT				0x00000058

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Invalid OpCode</description>
 */
#define RTSEXCPT_INVALID_OPCODE				0x00000059

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Datatype misalignment</description>
 */
#define RTSEXCPT_MISALIGNMENT				0x00000100

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Array bounds exceeded</description>
 */
#define RTSEXCPT_ARRAYBOUNDS				0x00000101

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Division by zero</description>
 */
#define RTSEXCPT_DIVIDEBYZERO				0x00000102

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Overflow</description>
 */
#define RTSEXCPT_OVERFLOW					0x00000103

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Non continuable</description>
 */
#define RTSEXCPT_NONCONTINUABLE				0x00000104

/**
 * <category>Exception code</category>
 * <description>Processor load watchdog of all IEC-tasks detected</description>
 */
#define RTSEXCPT_PROCESSORLOAD_WATCHDOG		0x00000105


/**
 * <category>Exception code, hardware FPU exceptions</category>
 * <description>FPU: Unspecified error</description>
 */
#define RTSEXCPT_FPU_ERROR					0x00000150

/**
 * <category>Exception code, hardware FPU exceptions</category>
 * <description>FPU: Denormal operand</description>
 */
#define RTSEXCPT_FPU_DENORMAL_OPERAND		0x00000151

/**
 * <category>Exception code, hardware FPU exceptions</category>
 * <description>FPU: Division by zero</description>
 */
#define RTSEXCPT_FPU_DIVIDEBYZERO			0x00000152

/**
 * <category>Exception code, hardware FPU exceptions</category>
 * <description>FPU: Inexact result</description>
 */
#define RTSEXCPT_FPU_INEXACT_RESULT			0x00000153

/**
 * <category>Exception code, hardware FPU exceptions</category>
 * <description>FPU: Invalid operation</description>
 */
#define RTSEXCPT_FPU_INVALID_OPERATION		0x00000154

/**
 * <category>Exception code, hardware FPU exceptions</category>
 * <description>FPU: Overflow</description>
 */
#define RTSEXCPT_FPU_OVERFLOW				0x00000155

/**
 * <category>Exception code, hardware FPU exceptions</category>
 * <description>FPU: Stack check</description>
 */
#define RTSEXCPT_FPU_STACK_CHECK			0x00000156

/**
 * <category>Exception code, hardware FPU exceptions</category>
 * <description>FPU: Underflow</description>
 */
#define RTSEXCPT_FPU_UNDERFLOW				0x00000157

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Hardware breakpoint</description>
 */
#define RTSEXCPT_BREAKPOINT					0x00000200

/**
 * <category>Exception code</category>
 * <description>Masks all exeption codes so far</description>
 */
#define RTSEXCPT_MASK						0x00000fff

/**
 * <category>Exception code, 3SLicense exceptions</category>
 * <description>3SLicense: License invalid</description>
 */
#define RTSEXCPT_LICENSE_INVALID			0x100D0001

/**
 * <category>Exception code</category>
 * <description>In addition to RTSEXCPT_WATCHDOG
 * in order to separate OmittedCycle watchdog from "normal" CycleExceed watchdog</description>
 */
#define RTSEXCPT_WATCHDOG_OMITTED_CYCLE		0x00001000

/**
 * <category>Exception code, vendor specific</category>
 * <description>Base number for vendor specific exception codes. VendorID must be specified as prefix
 *	inside the exception code:
 *	RTS_UI32 ulException = ADDVENDORID([VendorId], RTSEXCPT_VENDOR_EXCEPTION_BASE + [Exception]);
 * </description>
 */
#define RTSEXCPT_VENDOR_EXCEPTION_BASE		0x00002000

/**
 * <category>Exception code</category>
 * <description>Makro to test masked exeption codes</description>
 */
#define SysExcptIsException(e, exception)	((e & RTSEXCPT_MASK) == exception)


/**
 * <category>Event parameter</category>
 * <description></description>
 *	<element name="uiTaskOSHandle" type="IN">Operating system specific task handle</element>
 *	<element name="ulException" type="IN">Exception number. See category "Exception code"</element>
 *	<element name="Context" type="IN">Register context, where the exception occurred</element>
 */
typedef struct
{
	RTS_HANDLE uiTaskOSHandle;
	RTS_IEC_DWORD ulException;
	RegContext Context;
	RTS_RESULT Result;
} EVTPARAM_SysExcept;
#define EVTPARAMID_SysExcept		0x0001
#define EVTVERSION_SysExcept		0x0002

/**
 * <category>Events</category>
 * <description>The event is sent if an exception occurred (see category exception code for 
 *	detailed information).
 *	NOTE:
 *	This event is fired for every exception! That means also for handled exceptions via SEH (Structured Exception Handling)
 *	with rts_try/rts_catch! 
 * </description>
 * <param name="pEventParam" type="IN">EVTPARAM_SysExcept</param>
 */
#define EVT_EXCPT_GenerateException					MAKE_EVENTID(EVTCLASS_EXCEPTION, 1)

/**
 * <category>Events</category>
 * <description>The event is sent if an exception occurred (see category exception code for 
 *	detailed information).
 *	NOTE:
 *	This event is fired only for exceptions that are not handled via SEH (Structured Exception Handling)
 *	with rts_try/rts_catch! 
 * </description>
 * <param name="pEventParam" type="IN">EVTPARAM_SysExcept</param>
 */
#define EVT_EXCPT_GenerateException2				MAKE_EVENTID(EVTCLASS_EXCEPTION, 2)


#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysExceptOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysExceptOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>Map the operating system specific exception into the standard runtime exception code</description>
 * <param name="ulOSException" type="IN">Operating system specific exception code</param>
 * <result>Standard exception code (see category exception code above)</result>
 */
DEF_ITF_API(`RTS_UI32', `CDECL', `SysExceptMapException', `(RTS_UI32 ulOSException)')

/**
 * <description>
 * <p>Structured Exception Handling</p>
 * <p>This function is called from Exception handlers of the hardware,
 * operating systems or, in case of softerrors, within the task code.
 * </p>
 * <p>The structured exception handling calls every registered exception
 * handler, stops the IEC Tasks and prepares the task context of the
 * task that generated the exception, so that it can be read by the
 * CoDeSys programming system for analysation purposes.
 * </p>
 * <p>OEM customers can use this function also from their own exception
 * handlers to propagate generic as well as customer specific exceptions
 * to the application. This way, they can profit from the debugging
 * infrastructure of CoDeSys to find the fault adress within the IEC
 * application.</p>
 * <p><b>Note:</b> On SIL2 Platforms, this function will act only as
 * described above, when the PLC is currently in Debug-Mode. If it is
 * actually in the Safety-Mode, this call puts the PLC directly into
 * the safe mode, by calling the function SIL2OEMException().</p>
 * </description>
 * <param name="ulTaskOSHandle" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TASKHANDLE]">System specific task or timer handle or RTS_INVALID_HANDLE if unknown</param>
 * <param name="Exception" type="IN" range="[RTSEXCPT_UNKNOWN]">Exception code (OS or runtime specific)</param>
 * <param name="Context" type="IN" range="[NULL,VALID_CONTEXT]">Context to detect the code location where the exception was generated. If ulTaskOSHandle is RTS_INVALID_HANDLE, values can be 0.</param>
 * <parampseudo name="Mode" type="IN" range="[SAFETY,DEBUG]">Defines the current mode of the PLC.</parampseudo>
 * <parampseudo name="StructuredHandling" type="OUT">TRUE if structured Exception Handling was used.</parampseudo>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysExceptGenerateException', `(RTS_HANDLE ulTaskOSHandle, ExceptionCode Exception, RegContext Context)')

/**
 * <description>
 * <p>Structured Exception Handling</p>
 * <p>This function acts the same way as SysExceptGenerateException(),
 * except for the case, that it will try to suspend the task in the
 * following condition:
 * </p>
 * <ul>
 *   <li>bSuspendExceptionTask is set to TRUE</li>
 *   <li>None of the registered exception handlers returned ERR_DONT_SUSPEND_TASK</li>
 * </ul>
 * </description>
 * <param name="ulTaskOSHandle" type="IN" range="[RTS_INVALID_HANDLE,NULL,VALID_TASKHANDLE]">System specific task or timer handle or RTS_INVALID_HANDLE if unknown</param>
 * <param name="Exception" type="IN" range="[EXCEPTION_1]">Exception code (OS or runtime specific)</param>
 * <param name="Context" type="IN" range="[NULL,VALID_CONTEXT]">Context to detect the code location where the exception was generated. If ulTaskOSHandle is RTS_INVALID_HANDLE, values can be 0.</param>
 * <param name="bSuspendExceptionTask" type="IN" range="[0,1]">Flag to specify, if the exception task is forced to suspended</param>
 * <parampseudo name="bSafetyMode" type="IN" range="[0,1]">Defines the current mode of the PLC.</parampseudo>
 * <parampseudo name="bStructuredHandling" type="OUT">TRUE if structured Exception Handling was used.</parampseudo>
 * <errorcode name="RTS_RESULT" type="ERR_OK">None of the registered exception handlers returned ERR_DONT_SUSPEND_TASK</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_DONT_SUSPEND_TASK">An exception handler suspends the task itself</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysExceptGenerateException2', `(RTS_HANDLE ulTaskOSHandle, ExceptionCode Exception, RegContext Context, int bSuspendExceptionTask)')

/**
 * <description>Function to register an exception handler</description>
 * <param name="pExceptionHandler" type="IN">Pointer to exception handler</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysExceptRegisterInterface', `(PFEXCEPTIONHANDLER pExceptionHandler)')

/**
 * <description>This function registers or cleans up an exception context.
 * If this is the entry, it returns ERR_OK, otherwise ERR_FAILED</description>
 * <param name="context" type="IN">Context, describing one structured exception frame</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysExceptTry', `(SEHContext *context)')

/**
 * <description>This function returns ERR_OK when the passed exception matches
 * the exception code that really occured.</description>
 * <param name="context" type="IN">Context, describing one structured exception frame</param>
 * <param name="ui32ExceptionCode" type="IN">Exception code to match on</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysExceptCatchException', `(SEHContext *context, RTS_UI32 ui32ExceptionCode)')

/**
 * <description>This function returns ERR_OK if the exception was not yet handled.</description>
 * <param name="context" type="IN">Context, describing one structured exception frame</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysExceptCatch', `(SEHContext *context)')

/**
 * <description>Function to unregister exception handler</description>
 * <param name="pExceptionHandler" type="IN">Pointer to exception handler</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysExceptUnregisterInterface', `(PFEXCEPTIONHANDLER pExceptionHandler)')

/**
 * <description>Convert an exception to string</description>
 * <param name="ulExceptionCode" type="IN">Exception code</param>
 * <param name="pszException" type="OUT">Pointer to exception string</param>
 * <param name="iMaxExceptionLen" type="IN">Maximum length of exception string pointer</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SysExceptConvertToString', `(RTS_UI32 ulExceptionCode, char*pszException, int iMaxExceptionLen)')

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Interrupt the execution of the currently running
 * task, and set the application into an exception state. If the
 * runtime system supports it, CODESYS may even highlight the source
 * position where this function was called.</description>
 * <result><p>RESULT: If succeeded this function doesn't return at all, otherwise it returns ERR_FAILED.</p></result>
 */
typedef struct tagsysexceptgenerateexception_struct
{
	RTS_IEC_UDINT udiException;			/* VAR_INPUT */	
	RTS_IEC_RESULT SysExceptGenerateException;	/* VAR_OUTPUT */	
} sysexceptgenerateexception_struct;

DEF_API(`void',`CDECL',`sysexceptgenerateexception',`(sysexceptgenerateexception_struct *p)',1,0xE91614FA,0x03050500)

/**
 * <description>Obsolete function</description>
 */
typedef struct tagsysexceptdisableseh_struct
{
	RTS_IEC_RESULT SysExceptDisableSEH;	/* VAR_OUTPUT */	
} sysexceptdisableseh_struct;

DEF_API(`void',`CDECL',`sysexceptdisableseh',`(sysexceptdisableseh_struct *p)',1,0x8C7B1A37,0x03050500)

/**
 * <description>Obsolete function</description>
 */
typedef struct tagsysexceptdisableseh2_struct
{
	RTS_IEC_BYTE *pfExceptionHandler;	/* VAR_INPUT */	/* <param name="pfExceptionHandler" type="IN">Function pointer to the exception handler</param> */
	RTS_IEC_RESULT SysExceptDisableSEH2;	/* VAR_OUTPUT */	
} sysexceptdisableseh2_struct;

DEF_API(`void',`CDECL',`sysexceptdisableseh2',`(sysexceptdisableseh2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB55730A3),0x03050500)

/**
 * <description>Obsolete function</description>
 */
typedef struct tagsysexceptenableseh_struct
{
	RTS_IEC_RESULT SysExceptEnableSEH;	/* VAR_OUTPUT */	
} sysexceptenableseh_struct;

DEF_API(`void',`CDECL',`sysexceptenableseh',`(sysexceptenableseh_struct *p)',1,0x41742724,0x03050500)

/**
 * <description>Obsolete function</description>
 */
typedef struct tagsysexceptenableseh2_struct
{
	RTS_IEC_BYTE *pfExceptionHandler;	/* VAR_INPUT */	/* <param name="pfExceptionHandler" type="IN">Function pointer to the exception handler</param> */
	RTS_IEC_RESULT SysExceptEnableSEH2;	/* VAR_OUTPUT */	
} sysexceptenableseh2_struct;

DEF_API(`void',`CDECL',`sysexceptenableseh2',`(sysexceptenableseh2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x5FF166F1),0x03050500)


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef RTS_STRUCTURED_EXCEPTION_HANDLING
	/**
	 * <description>Structured exception handling:
	 * rts_try:             macro to enter an exception frame
	 * rts_catch_exception: macro to catch a specific exception
	 * rts_catch:           macro to catch all exception codes
	 * rts_try_end:         macro to close the block of the exception frame
	 * </description>
	 */

	#ifndef EXCPT_GET_CODE
		#define EXCPT_GET_CODE() 	__SEHContext.ui32ExceptionCode
	#endif

	#ifndef EXCPT_GET_CONTEXT
		#define EXCPT_GET_CONTEXT() &__SEHContext.context
	#endif

	#ifndef rts_try
		#define rts_try \
		{ \
			SEHContext __SEHContext; \
			__SEHContext.bRegistered = 0; \
			RTS_GET_FPENV(&__SEHContext.fpenvbuf) \
			__SEHContext.ui32ExceptionCode = RTS_SETJMP(__SEHContext.jmpbuf); \
			if(__SEHContext.ui32ExceptionCode != 0) \
				{RTS_SET_FPENV(&__SEHContext.fpenvbuf)} \
			while (CAL_SysExceptTry(&__SEHContext) == ERR_OK)

	#endif


	#ifndef rts_catch_exception
		#define rts_catch_exception(ui32ExceptionCode) \
			if (CAL_SysExceptCatchException(&__SEHContext, ui32ExceptionCode) == ERR_OK)
	#endif

	#ifndef rts_catch
		#define rts_catch \
			if (CAL_SysExceptCatch(&__SEHContext) == ERR_OK)
	#endif

	#ifndef rts_try_end
		#define rts_try_end \
		}
	#endif
#else	/*RTS_STRUCTURED_EXCEPTION_HANDLING*/

	#define EXCPT_GET_CODE()                       RTSEXCPT_NOEXCEPTION
	#define EXCPT_GET_CONTEXT()                    NULL
	#define rts_try                                {
	#define rts_catch_exception(ui32ExceptionCode) if (0)
	#define rts_catch                              if (0)
	#define rts_try_end                            }
#endif

#ifdef __cplusplus
}
#endif

