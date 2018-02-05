/**
 * <interfacename>SysProcess</interfacename>
 * <description> 
 *	<p>The SysProcess interface is projected to handle operating system processes. This
 *	can be implemented only on targets with an operating system with processes.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysProcess')

#include "CmpItf.h"

/**
 * <category>Priority ranges</category>
 * <description>
 *	Process priorities can be set between 0..255.
 *	The priorities are mapped to real operating system piorirites at least with the spcified
 *	task segments
 * </description>
 */
#define PROCESSPRIO_RANGE				255
#define PROCESSPRIO_SEGMENT				32

#define PROCESSPRIO_MAX					0

/* PROCESS segment 1 */
#define PROCESSPRIO_SYSTEM_BASE			0
#define PROCESSPRIO_SYSTEM_END			31

/* PROCESS segment 2 */
#define PROCESSPRIO_REALTIME_BASE		32
#define PROCESSPRIO_REALTIME_END		63

/* PROCESS segment 3 */
#define PROCESSPRIO_HIGH_BASE			64
#define PROCESSPRIO_HIGH_END			95

/* PROCESS segment 4 */
#define PROCESSPRIO_ABOVENORMAL_BASE	96
#define PROCESSPRIO_ABOVENORMAL_END		127

/* PROCESS segment 5 */
#define PROCESSPRIO_NORMAL_BASE			128
#define PROCESSPRIO_NORMAL_END			159

/* PROCESS segment 6 */
#define PROCESSPRIO_BELOWNORMAL_BASE	160
#define PROCESSPRIO_BELOWNORMAL_END		191

/* PROCESS segment 7 */
#define PROCESSPRIO_LOW_BASE			192
#define PROCESSPRIO_LOW_END				223

/* PROCESS segment 8 */
#define PROCESSPRIO_LOWEST_BASE			224
#define PROCESSPRIO_LOWEST_END			255

#define PROCESSPRIO_IDLE				255
#define PROCESSPRIO_MIN					255

/**
 * <category>Process status</category>
 * <description>Actual status of a process</description>
 */
#define PROCESS_STATUS_RUNNING			1
#define PROCESS_STATUS_TERMINATED		2

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting to get process priority. STRING type</description>
 */
#define KEY_STRING_BASEPRIORITY							"BasePriority"
#define VALUE_STRING_BASEPRIORITY_REALTIME				"Realtime"
#define VALUE_STRING_BASEPRIORITY_HIGH					"High"
#define VALUE_STRING_BASEPRIORITY_NORMAL				"Normal"
#define VALUE_STRING_BASEPRIORITY_LOW					"Low"
#ifndef VALUE_STRING_BASEPRIORITY_DEFAULT
	#define VALUE_STRING_BASEPRIORITY_DEFAULT			""
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Setting to get process priority. STRING type</description>
 */
#define KEY_INT_PROCESSORID						"ProcessorId"
#define KEY_INT_PROCESSORID_DEFAULT				1

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description><p>Setting to define the allowed commands for SysExecuteCommand by a white list. 
 *	Several commands must be entered indexed, e.g.:</p>
 *	<p>Command.0=./dothis</p>
 *	<p>Command.1=./dothat</p>
 *	<p>If nothing is configured, SysExecuteCommand will always fail.</p>
 *	<p>In addition to that, it is also possible to ignore the above white list and allow all commands by:</p>
 *	<p>Command=AllowAll/p>
 *	<p>ATTENTION: If Command=AllowAll is set, there is no further verification done, before a command is executed. Please
 *	check your security requirements carefully before activating this. For the same reason you should also choose the 
 *	allowed commands in the list accurately. c</p>
 * </description>
 */
#define SYSPROCESS_KEY_STRING_COMMAND					"Command"
#ifndef SYSPROCESS_KEY_STRING_COMMAND_DEFAULT
	#define SYSPROCESS_KEY_STRING_COMMAND_DEFAULT		""
#endif
#define SYSPROCESS_KEY_STRING_COMMAND_ALLOW_ALL			"AllowAll"

/**
 * <category>Process creation flags</category>
 * <description>A combination of these flags can specify the startup of a process</description>
 * <element name="PROCESS_CREATEFLAG_HIDDEN" type="IN">Flag to create a hidden process</element>
 * <element name="PROCESS_CREATEFLAG_INTERACTIVE" type="IN">Flag to create an interactive process requiring input from the user</element>
 * <element name="PROCESS_CREATEFLAG_CREATESUSPENDED" type="IN">Flag to create a suspended process</element>
 * 
 */
#define PROCESS_CREATEFLAG_HIDDEN				1
#define PROCESS_CREATEFLAG_INTERACTIVE			2
#define PROCESS_CREATEFLAG_CREATESUSPENDED		4


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Function to create a process. NOTE: Is only available on systems with processes!
 * This function starts the specified application as new process, optionally either in the fore- or in the background.
 * </description>
 * <result><p>RESULT: Handle to the created process or RTS_INVALID_HANDLE if failed.</p></result>
 */
typedef struct tagsysprocesscreate_struct
{
	RTS_IEC_STRING *pszApplication;		/* VAR_INPUT */	/* <param name="pszApplication" type="IN">Name of application to start as a separate process</param> */
	RTS_IEC_STRING *pszCommandLine;		/* VAR_INPUT */	/* <param name="pszCommandLine" type="IN">String with the command line</param> */
	RTS_IEC_UDINT ulHide;				/* VAR_INPUT */	/* <param name="ulHide" type="IN">The application runs in the background for ulHide=1, else in the foreground.</param> */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param> */
	RTS_IEC_HANDLE SysProcessCreate;	/* VAR_OUTPUT */	
} sysprocesscreate_struct;

DEF_API(`void',`CDECL',`sysprocesscreate',`(sysprocesscreate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB8C769CB),0x03050700)

/**
 * <description>Function to create a process. NOTE: Is only available on systems with processes!
 * This functions creates and eventually starts a new process for the specified application. The properties of the
 * created process can be defined by appropriate flags.</description>
 * <result><p>RESULT: Handle to the created process or RTS_INVALID_HANDLE if failed.</p></result>
 */
typedef struct tagsysprocesscreate2_struct
{
	RTS_IEC_STRING *pszApplication;		/* VAR_INPUT */	/* <param name="pszApplication" type="IN">Name of application to start as a separate process</param> */
	RTS_IEC_STRING *pszCommandLine;		/* VAR_INPUT */	/* <param name="pszCommandLine" type="IN">String with the command line</param> */
	RTS_IEC_UDINT ulFlags;				/* VAR_INPUT */	/* <param name="ulFlags" type="IN">A combination of the process flags SYSPROCESS_CREATEFLAG_XXX.</param> */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param> */
	RTS_IEC_HANDLE SysProcessCreate2;	/* VAR_OUTPUT */	
} sysprocesscreate2_struct;

DEF_API(`void',`CDECL',`sysprocesscreate2',`(sysprocesscreate2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x053781FD),0x03050700)

/**
 * <description>Function to start a system command. The command is operating system dependant!</description>
 * <result><p>RESULT: Result of command after execution</p></result>
 */
typedef struct tagsysprocessexecutecommand_struct
{
	RTS_IEC_STRING *pszComand;			/* VAR_INPUT */	/* <param name="pszCommand" type="IN">Command line parameters to be trasnmitted to application at execution</param> */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param> */
	RTS_IEC_DINT SysProcessExecuteCommand;	/* VAR_OUTPUT */	
} sysprocessexecutecommand_struct;

DEF_API(`void',`CDECL',`sysprocessexecutecommand',`(sysprocessexecutecommand_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xE26B1ECD),0x03050700)

/**
 * <description>Function to start a system command. The command is operating system dependant! 
 *	Command will be executed, only if allowed (see settings for details). Output of the executed command will be filled into pszStdOut.
 * </description>
 * <result><p>RESULT: Number of bytes, read from the commands output.</p></result>
 */
typedef struct tagsysprocessexecutecommand2_struct
{
	RTS_IEC_STRING *pszCommand;			/* VAR_INPUT */	/* <param name="pszCommand" type="IN">Command line parameters to be transmitted to application at execution</param> */
	RTS_IEC_STRING *pszStdOut;			/* VAR_INPUT */	/* <param name="pszStdOut" type="IN">Buffer for StdOut string</param> */
	RTS_IEC_UDINT udiStdOutLen;			/* VAR_INPUT */	/* <param name="udiStdOutLen" type="IN">Buffersize for StdOut string buffer</param> */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code. ERR_PARAMETER: if pszCommand, pszStdOut or udiStdOutLen is null, ERR_NO_ACCESS_RIGHTS: if command is not allowed</param> */
	RTS_IEC_DINT SysProcessExecuteCommand2;	/* VAR_OUTPUT */	
} sysprocessexecutecommand2_struct;

DEF_API(`void',`CDECL',`sysprocessexecutecommand2',`(sysprocessexecutecommand2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x827A1263),0x03050700)

/**
 * <description>Function to release the process handle that is returned by SysProcessCreate or SysProcessGetCurrentHandle.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysprocessfreehandle_struct
{
	RTS_IEC_HANDLE hProcess;			/* VAR_INPUT */	/* <param name="hProcess" type="IN">Handle of the process</param> */
	RTS_IEC_RESULT SysProcessFreeHandle;	/* VAR_OUTPUT */	
} sysprocessfreehandle_struct;

DEF_API(`void',`CDECL',`sysprocessfreehandle',`(sysprocessfreehandle_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD81A18BC),0x03050700)

/**
 * <description>Function to get a handle to the current process</description>
 * <result><p>RESULT: Returns the handle of the process actually running by the processor or RTS_INVALID_HANDLE if failed.</p></result>
 */
typedef struct tagsysprocessgetcurrenthandle_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param> */
	RTS_IEC_HANDLE SysProcessGetCurrentHandle;	/* VAR_OUTPUT */	
} sysprocessgetcurrenthandle_struct;

DEF_API(`void',`CDECL',`sysprocessgetcurrenthandle',`(sysprocessgetcurrenthandle_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF293D47C),0x03050700)

/**
 * <description>Function to determine an operatingsystem dependant identification of a process. This 
 * identification must be unique in the system at a defined time! SysProcessGetOSId can only applied to 
 * the process actually executed or to processes having been generated by SysProcessCreate.</description>
 * <result><p>RESULT: Returns the operating system specific identification of the process</p></result>
 */
typedef struct tagsysprocessgetosid_struct
{
	RTS_IEC_HANDLE hProcess;			/* VAR_INPUT */	/* <param name="hProcess" type="IN">Handle of the process</param> */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param> */
	RTS_IEC_UDINT SysProcessGetOSId;	/* VAR_OUTPUT */	/* OSId */
} sysprocessgetosid_struct;

DEF_API(`void',`CDECL',`sysprocessgetosid',`(sysprocessgetosid_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x946F8470),0x03050700)

/**
 * <description>This function retrieves the priority of the process specified by its handle.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysprocessgetpriority_struct
{
	RTS_IEC_HANDLE hProcess;			/* VAR_INPUT */	/* <param name="hProcess" type="IN">Handle of the process</param> */
	RTS_IEC_UDINT *pulPriority;			/* VAR_INPUT */	/* <param name="pulPriority" type="OUT">Pointer to variable being assigned to priority of the process</param> */
	RTS_IEC_RESULT SysProcessGetPriority;	/* VAR_OUTPUT */	
} sysprocessgetpriority_struct;

DEF_API(`void',`CDECL',`sysprocessgetpriority',`(sysprocessgetpriority_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCEA416D5),0x03050700)

/**
 * <description>This function retrieves the status of the process specified by its handle.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysprocessgetstate_struct
{
	RTS_IEC_HANDLE hProcess;			/* VAR_INPUT */	/* <param name="hProcess" type="IN">Handle of the process</param> */
	RTS_IEC_UDINT *pulState;			/* VAR_INPUT */	/* <param name="pulState" type="OUT">Pointer to variable being assigned to value 1 for running processes and value 2 for terminated processes</param> */
	RTS_IEC_RESULT SysProcessGetState;	/* VAR_OUTPUT */	
} sysprocessgetstate_struct;

DEF_API(`void',`CDECL',`sysprocessgetstate',`(sysprocessgetstate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB65EA319),0x03050700)

/**
 * <description>This function starts the process specified by its handle. For example, the function can be used for
 * processes having been created in suspended mode by use of the flag SYSPROCESS_CREATEFLAG_CREATESUSPENDED.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysprocessresume_struct
{
	RTS_IEC_HANDLE hProcess;			/* VAR_INPUT */	/* <param name="hProcess" type="IN">Handle of the process</param> */
	RTS_IEC_RESULT SysProcessResume;	/* VAR_OUTPUT */	
} sysprocessresume_struct;

DEF_API(`void',`CDECL',`sysprocessresume',`(sysprocessresume_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1587F094),0x03050700)

/**
 * <description>This function sets the priority of the process specified by its handle.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysprocesssetpriority_struct
{
	RTS_IEC_HANDLE hProcess;			/* VAR_INPUT */	/* <param name="hProcess" type="IN">Handle of the process</param> */
	RTS_IEC_UDINT ulPriority;			/* VAR_INPUT */	/* <param name="ulPriority" type="IN">Process priority</param> */
	RTS_IEC_RESULT SysProcessSetPriority;	/* VAR_OUTPUT */	
} sysprocesssetpriority_struct;

DEF_API(`void',`CDECL',`sysprocesssetpriority',`(sysprocesssetpriority_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCB07213F),0x03050700)

/**
 * <description>This function terminates the process specified by its handle.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysprocessterminate_struct
{
	RTS_IEC_HANDLE hProcess;			/* VAR_INPUT */	/* <param name="hProcess" type="IN">Handle of the process</param> */
	RTS_IEC_RESULT SysProcessTerminate;	/* VAR_OUTPUT */	
} sysprocessterminate_struct;

DEF_API(`void',`CDECL',`sysprocessterminate',`(sysprocessterminate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x498BEF7C),0x03050700)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysProcessOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysProcessOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description> Function to start a system command. The command is operating system dependant! </description>
 * <param name="pszCommand" type="IN">String with the command line</param>
 * <result>Result after command execution</result>
 */
DEF_ITF_API(`RTS_I32',`CDECL',`SysProcessExecuteCommand',`(char *pszCommand, RTS_RESULT *pResult)')

/**
 * <description> Function to start a system command. The command is operating system dependant! 
 *	If Pointer to buffer is not null for StdOut or StdErr the buffer will be filled.</description>
 * <param name="pszCommand" type="IN">String with the command line</param> 
 * <param name="pszStdOut" type="IN">Buffer for StdOut string</param>
 * <param name="udiStdOutLen" type="IN">Buffersize for StdOut string buffer</param>
 * <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param>
 */
DEF_ITF_API(`RTS_I32',`CDECL',`SysProcessExecuteCommand2',`(char *pszCommand, char* pszStdOut, RTS_UI32 udiStdOutLen, RTS_RESULT *pResult)')


/**
 * <description> Function to create a process. Is only valid on systems with processes! </description>
 * <param name="pszApplication" type="IN">Name of application to start as a separate process</param>
 * <param name="pszCommandLine" type="IN">String with the command line</param>
 * <param name="ulFlags" type="IN">A combination of flags like PROCESS_CREATEFLAG_HIDDEN for example.</param>
 * <param name="pResult" type="OUT">Pointer to the result</param>
 * <result>Handle to the process</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SysProcessCreate',`(char *pszApplication, char *pszCommandLine, RTS_UI32 ulFlags, RTS_RESULT *pResult)')

/**
 * <description> Function to resume a process specified by handle. This can be used, if a process is created with PROCESS_CREATEFLAG_CREATESUSPENDED flag.</description>
 * <param name="hProcess" type="IN">Handle to the process</param>
 * <result>Error code: ERR_OK or ERR_FAILED</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysProcessResume',`(RTS_HANDLE hProcess)')

/**
 * <description> Function to terminate a process specified by handle </description>
 * <param name="hProcess" type="IN">Handle to the process</param>
 * <result>Error code: ERR_OK or ERR_FAILED</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysProcessTerminate',`(RTS_HANDLE hProcess)')

/**
 * <description> Function to get a handle to the current process </description>
 * <param name="pResult" type="OUT">Pointer to the result</param>
 * <result>The handle of the topical process</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SysProcessGetCurrentHandle',`(RTS_RESULT* pResult)')

/**
 * <description> Function to free the process handle that is returned by SysProcessCreate or SysProcessGetCurrentHandle </description>
 * <param name="hProcess" type="IN">Handle to the process</param>
 * <result>Error code: ERR_OK or ERR_PARAMETER if handle is invalid</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysProcessFreeHandle',`(RTS_HANDLE hProcess)')

/**
 * <description> Function to get the actual state of a process </description>
 * <param name="hProcess" type="IN">Handle to the process</param>
 * <param name="piState" type="OUT">Pointer to state of the process, see the definitions above</param>
 * <result>Error code: ERR_OK or ERR_PARAMETER if handle is invalid</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysProcessGetState',`(RTS_HANDLE hProcess, RTS_I32 *piState)')

/**
 * <description> Function to set the process priority </description>
 * <param name="hProcess" type="IN">Handle to the process</param>
 * <param name="ulPriority" type="IN">Process priority</param>
 * <result>Error code: ERR_OK or ERR_FAILED</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysProcessSetPriority',`(RTS_HANDLE hProcess, RTS_UI32 ulPriority)')

/**
 * <description> Function to get the process priority </description>
 * <param name="hProcess" type="IN">Handle to the process</param>
 * <param name="pulPriority" type="OUT">Pointer to priority</param>
 * <result>Error code: ERR_OK or ERR_FAILED</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysProcessGetPriority',`(RTS_HANDLE hProcess, RTS_UI32 *pulPriority)')

/**
 * <description> Function to determine an operatingsystem dependant identification of a process. This 
 * identification must be unique in the system at a defined time! This function will only work on processes created
 *	with SysProcessCreate or on the current process </description>
 * <param name="hProcess" type="IN">Handle to the process</param>
 * <param name="pResult" type="OUT">Pointer to the result</param>
 * <result>The OS dependant id as a DWORD</result>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`SysProcessGetOSId',`(RTS_HANDLE hProcess, RTS_RESULT* pResult)')

#ifdef __cplusplus
}
#endif
