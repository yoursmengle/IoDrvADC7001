/**
 * <interfacename>RTSSIL2PSP</interfacename>
 * <description> 
 * <p>This is the interface of SIL2 Platform Support Package (PLP).</p>
 * </description>
 *
 * <copyright>(c) 2003-2010 3S-Smart Software Solutions</copyright>
 */

#ifndef _RTSSIL2PSPITF_H_
#define _RTSSIL2PSPITF_H_
 
/**
 * <SIL2/>
 * <category>Typedef</category>
 * <description>
 * <p>pointer to component entry function</p>
 * </description>
 */
typedef int (*PF_SIL2PSP_COMPONENT_ENTRY)(void*);

/**
 * <SIL2/>
 * <category>Typedef</category>
 * <description>
 * <p>Element of StaticComponents list.
 * This structure is duplicated from the CMItf.h StaticComponent structure and has to stay in sync with it!
 * It is used to extend the components list of the PSP.</p>
 * </description>
 * <element name="pszCmpName" type="IN">Name of component</element>
 * <element name="pfCmpEntry" type="IN">Pointer to entry function of component</element>
 * <element name="bSystem" type="IN">Is system component</element>
 */
typedef struct tagSIL2PSPStaticComponent
{
	char *pszCmpName;
	PF_SIL2PSP_COMPONENT_ENTRY pfCmpEntry;
	int bSystem;
} SIL2PSPStaticComponent;

/**
 * <SIL2/>
 * <category>Typedef</category>
 * <description>
 * <p>void function pointer</p>
 * </description>
 */
typedef void (*SIL2PSP_VOID_FCTPTR)(void);

/** <SIL2/>
 * <category>Typedef</category>
 * <description>
 * <p>Element of SIL2PSPExternalFunction list.
 * This structure duplicates the original definition defined in CmpSIL2Itf.h to be able to overload it.
 * It has to stay in sync with the original definition!</p>
 * </description>
 * <element name="pszCmpName" type="IN">Name of component</element>
 * <element name="pfCmpEntry" type="IN">Pointer to entry function of component</element>
 * <element name="bSystem" type="IN">Is system component</element>
 */
typedef struct SIL2PSPExternalFunction_s {
	SIL2PSP_VOID_FCTPTR pfAPI;
	const char *pszAPIName;
} SIL2PSPExternalFunction_t;

/**
 * <SIL2/>
 * <category>Typedef</category>
 * <description>
 * <p>SIL2PSP context</p>
 * </description>
 * <element name="IP" type="IN">Instruction pointer or program counter</element>
 * <element name="BP" type="IN">Base pointer or frame pointer</element>
 * <element name="SP" type="IN">Stack pointer</element>
 * <element name="ui32ExceptionCode" type="IN">Exception code</element>
 */
typedef struct SIL2PSPRegContexttag
{
	void* pIP;
	void* pBP;
	void* pSP;
	unsigned int ui32ExceptionCode;
} SIL2PSPRegContext;

/**
 * <SIL2/>
 * <category>Typedef</category>
 * <description>
 * <p>SIL2PSP context</p>
 * </description>
 * <element name="IP" type="IN">Instruction pointer or program counter</element>
 * <element name="BP" type="IN">Base pointer or frame pointer</element>
 * <element name="SP" type="IN">Stack pointer</element>
 * <element name="RetIP" type="OUT">Instruction pointer to return to.</element>
 * <element name="ui32ExceptionCode" type="IN">Exception code</element>
 */
typedef struct SIL2PSPRegContexttag2
{
	void* pIP;
	void* pBP;
	void* pSP;
	void* pRetIP;
	unsigned int ui32ExceptionCode;
} SIL2PSPRegContext2;

/**
 * <category>Operation Mode.</category>
 * <description>Specifies the operation mode of the PSP.</description>
 */
typedef unsigned int SIL2PSP_OPMODE;
#define RTS_SIL2PSP_OPMODE_SAFE 		0xAABB
#define RTS_SIL2PSP_OPMODE_DEBUG 		0x7788
#define RTS_SIL2PSP_OPMODE_UNKNOWN 		0x99AA

/**
 * <category>Operation Mode.</category>
 * <description>Specifies the operation mode of the PSP.</description>
 */
typedef unsigned int SIL2PSP_RESULT;
#define SIL2PSP_ERR_OK		 		0xAA550000
#define SIL2PSP_ERR_FAILED	 		0xAA550001
#define SIL2PSP_ERR_PARAMETER		0xAA550002

/**
 * <category>Exception Codes</category>
 * <description></description>
 */

/**
 * <category>Exception code</category>
 * <description>Invalid</description>
 */
#define SIL2PSP_RTSEXCPT_UNKNOWN					0xFFFFFFFF

/**
 * <category>Exception code</category>
 * <description>No exception</description>
 */
#define SIL2PSP_RTSEXCPT_NOEXCEPTION				0x00000000

/**
 * <category>Exception code</category>
 * <description>Software watchdog of IEC-task expired</description>
 */
#define SIL2PSP_RTSEXCPT_WATCHDOG					0x00000010

/**
 * <category>Exception code</category>
 * <description>Hardware watchdog expired. Global software error</description>
 */
#define SIL2PSP_RTSEXCPT_HARDWAREWATCHDOG			0x00000011

/**
 * <category>Exception code</category>
 * <description>IO configuration error</description>
 */
#define SIL2PSP_RTSEXCPT_IO_CONFIG_ERROR			0x00000012

/**
 * <category>Exception code</category>
 * <description>Checksum error after program download</description>
 */
#define SIL2PSP_RTSEXCPT_PROGRAMCHECKSUM			0x00000013

/**
 * <category>Exception code</category>
 * <description>Fieldbus error</description>
 */
#define SIL2PSP_RTSEXCPT_FIELDBUS_ERROR				0x00000014

/**
 * <category>Exception code</category>
 * <description>IO-update error</description>
 */
#define SIL2PSP_RTSEXCPT_IOUPDATE_ERROR				0x00000015

/**
 * <category>Exception code</category>
 * <description>Cycle time exceed</description>
 */
#define SIL2PSP_RTSEXCPT_CYCLE_TIME_EXCEED			0x00000016

/**
 * <category>Exception code</category>
 * <description>Online change program too large</description>
 */
#define SIL2PSP_RTSEXCPT_ONLCHANGE_PROGRAM_EXCEEDED 0x00000017

/**
 * <category>Exception code</category>
 * <description>Unresolved external references</description>
 */
#define SIL2PSP_RTSEXCPT_UNRESOLVED_EXTREFS			0x00000018

/**
 * <category>Exception code</category>
 * <description>Download was rejected</description>
 */
#define SIL2PSP_RTSEXCPT_DOWNLOAD_REJECTED			0x00000019

/**
 * <category>Exception code</category>
 * <description>Boot project not loaded because retain variables could not be relocated</description>
 */
#define SIL2PSP_RTSEXCPT_BOOTPROJECT_REJECTED_DUE_RETAIN_ERROR	0x0000001A

/**
 * <category>Exception code</category>
 * <description>Boot project not loaded and deleted</description>
 */
#define SIL2PSP_RTSEXCPT_LOADBOOTPROJECT_FAILED		0x0000001B

/**
 * <category>Exception code</category>
 * <description>Out of heap memory</description>
 */
#define SIL2PSP_RTSEXCPT_OUT_OF_MEMORY				0x0000001C

/**
 * <category>Exception code</category>
 * <description>Retain memory corrupt or cannot be mapped</description>
 */
#define SIL2PSP_RTSEXCPT_RETAIN_MEMORY_ERROR		0x0000001D

/**
 * <category>Exception code</category>
 * <description>Boot project that could be loaded but caused a crash later</description>
 */
#define SIL2PSP_RTSEXCPT_BOOTPROJECT_CRASH			0x0000001E

/**
 * <category>Exception code</category>
 * <description>Target of the boot project doesn't match the current target</description>
 */
#define SIL2PSP_RTSEXCPT_BOOTPROJECTTARGETMISMATCH	0x00000021

/**
 * <category>Exception code</category>
 * <description>Error at scheduling tasks</description>
 */
#define SIL2PSP_RTSEXCPT_SCHEDULEERROR				0x00000022

/**
 * <category>Exception code</category>
 * <description>Checksum of downloaded file does not match</description>
 */
#define SIL2PSP_RTSEXCPT_FILE_CHECKSUM_ERR			0x00000023

/**
 * <category>Exception code</category>
 * <description>Retain identity does not match to current boot project program identity</description>
 */
#define SIL2PSP_RTSEXCPT_RETAIN_IDENTITY_MISMATCH	0x00000024

/**
 * <category>Exception code</category>
 * <description>Iec task configuration failed</description>
 */
#define SIL2PSP_RTSEXCPT_IEC_TASK_CONFIG_ERROR		0x00000025

/**
 * <category>Exception code</category>
 * <description>Application is running on wrong target. Can be used for library protection!</description>
 */
#define SIL2PSP_RTSEXCPT_APP_TARGET_MISMATCH		0x00000026


/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Illegal instruction</description>
 */
#define SIL2PSP_RTSEXCPT_ILLEGAL_INSTRUCTION		0x00000050

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Access violation</description>
 */
#define SIL2PSP_RTSEXCPT_ACCESS_VIOLATION			0x00000051

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Privileged instruction</description>
 */
#define SIL2PSP_RTSEXCPT_PRIV_INSTRUCTION			0x00000052

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Page fault</description>
 */
#define SIL2PSP_RTSEXCPT_IN_PAGE_ERROR				0x00000053

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Stack overflow</description>
 */
#define SIL2PSP_RTSEXCPT_STACK_OVERFLOW				0x00000054

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Invalid disposition</description>
 */
#define SIL2PSP_RTSEXCPT_INVALID_DISPOSITION		0x00000055

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Invalid handle</description>
 */
#define SIL2PSP_RTSEXCPT_INVALID_HANDLE				0x00000056

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Guard page</description>
 */
#define SIL2PSP_RTSEXCPT_GUARD_PAGE					0x00000057

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Double fault</description>
 */
#define SIL2PSP_RTSEXCPT_DOUBLE_FAULT				0x00000058

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Invalid OpCode</description>
 */
#define SIL2PSP_RTSEXCPT_INVALID_OPCODE				0x00000059

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Datatype misalignment</description>
 */
#define SIL2PSP_RTSEXCPT_MISALIGNMENT				0x00000100

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Array bounds exceeded</description>
 */
#define SIL2PSP_RTSEXCPT_ARRAYBOUNDS				0x00000101

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Division by zero</description>
 */
#define SIL2PSP_RTSEXCPT_DIVIDEBYZERO				0x00000102

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Overflow</description>
 */
#define SIL2PSP_RTSEXCPT_OVERFLOW					0x00000103

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Non continuable</description>
 */
#define SIL2PSP_RTSEXCPT_NONCONTINUABLE				0x00000104

/**
 * <category>Exception code</category>
 * <description>Processor load watchdog of all IEC-tasks detected</description>
 */
#define SIL2PSP_RTSEXCPT_PROCESSORLOAD_WATCHDOG		0x00000105


/**
 * <category>Exception code, hardware FPU exceptions</category>
 * <description>FPU: Unspecified error</description>
 */
#define SIL2PSP_RTSEXCPT_FPU_ERROR					0x00000150

/**
 * <category>Exception code, hardware FPU exceptions</category>
 * <description>FPU: Denormal operand</description>
 */
#define SIL2PSP_RTSEXCPT_FPU_DENORMAL_OPERAND		0x00000151

/**
 * <category>Exception code, hardware FPU exceptions</category>
 * <description>FPU: Division by zero</description>
 */
#define SIL2PSP_RTSEXCPT_FPU_DIVIDEBYZERO			0x00000152

/**
 * <category>Exception code, hardware FPU exceptions</category>
 * <description>FPU: Inexact result</description>
 */
#define SIL2PSP_RTSEXCPT_FPU_INEXACT_RESULT			0x00000153

/**
 * <category>Exception code, hardware FPU exceptions</category>
 * <description>FPU: Invalid operation</description>
 */
#define SIL2PSP_RTSEXCPT_FPU_INVALID_OPERATION		0x00000154

/**
 * <category>Exception code, hardware FPU exceptions</category>
 * <description>FPU: Overflow</description>
 */
#define SIL2PSP_RTSEXCPT_FPU_OVERFLOW				0x00000155

/**
 * <category>Exception code, hardware FPU exceptions</category>
 * <description>FPU: Stack check</description>
 */
#define SIL2PSP_RTSEXCPT_FPU_STACK_CHECK			0x00000156

/**
 * <category>Exception code, hardware FPU exceptions</category>
 * <description>FPU: Underflow</description>
 */
#define SIL2PSP_RTSEXCPT_FPU_UNDERFLOW				0x00000157

/**
 * <category>Exception code, hardware exceptions</category>
 * <description>Hardware breakpoint</description>
 */
#define SIL2PSP_RTSEXCPT_BREAKPOINT					0x00000200

/**
 * <category>Exception code, 3SLicense exceptions</category>
 * <description>3SLicense: License invalid</description>
 */
#define SIL2PSP_RTSEXCPT_LICENSE_INVALID			0x100D0001


/**
 * <description>
 * <p>
 * Function to initialize CODESYSContol runtime system and to load the boot project. On initialization errors of the
 * runtime system an exception is thrown. When an error occurs during loading the boot project an error is returned.
 * </p>
 * </description>
 * <param name="bLoadBootproject" type="IN">Try to load a boot project if there is one, or not</param>
 * <errorcode name="SIL2PSP_RESULT Result" type="SIL2PSP_ERR_OK">Runtime system initialized successfully.</errorcode>
 * <errorcode name="SIL2PSP_RESULT Result" type="SIL2PSP_ERR_FAILED">Loading boot project failed.</errorcode>
 * <result>Result of initialization.</result>
 */
SIL2PSP_RESULT SIL2PSP_RuntimeInit(unsigned int bLoadBootproject);

/**
 * <description> 
 * <p>Called cyclically to call CH_COMM_CYCLE hoof of all components </p>
 * </description>
 * <errorcode name="SIL2PSP_RESULT pResult" type="SIL2PSP_ERR_OK">CH_COMM_CYCLE of all components successfully called</errorcode>
 * <errorcode name="SIL2PSP_RESULT pResult" type="SIL2PSP_ERR_FAILED">Any Component responded with some error</errorcode>
 * <result>error code</result>
 */
SIL2PSP_RESULT SIL2PSP_CommCycle(void);

/**
 * <description> 
 * <p>Function to handle PSP specific interrupts</p>
 * </description>
 * <errorcode name="SIL2PSP_RESULT pResult" type="SIL2PSP_ERR_OK">Interrupt handled</errorcode>
 * <errorcode name="SIL2PSP_RESULT pResult" type="SIL2PSP_ERR_FAILED">Failed handling interrupt</errorcode>
 * <result>error code</result>
 */
SIL2PSP_RESULT SIL2PSP_InterruptHandler(void);


/**
 * <description> 
 * <p>Function to handle PSP specific interrupts</p>
 * </description>
 * <param name="uiVector" type="IN">Vector of the interrupt</param>
 * <errorcode name="SIL2PSP_RESULT pResult" type="SIL2PSP_ERR_OK">Interrupt handled</errorcode>
 * <errorcode name="SIL2PSP_RESULT pResult" type="SIL2PSP_ERR_FAILED">Failed handling interrupt</errorcode>
 * <result>error code</result>
 */
SIL2PSP_RESULT SIL2PSP_InterruptHandler2(unsigned int uiVector);

/**
 * <description> 
 * <p>Function to handle exceptions by the PSP</p>
 * <p>This function handles the exception and modifies pContext->pIP to the desired return address.</p>
 * </description>
 * <param name="pContext" type="IN">Context</param>
 * <errorcode name="SIL2PSP_RESULT pResult" type="SIL2PSP_ERR_OK">Exception handled</errorcode>
 * <errorcode name="SIL2PSP_RESULT pResult" type="SIL2PSP_ERR_FAILED">Failed handling exception</errorcode>
 * <result>error code</result>
 */
SIL2PSP_RESULT SIL2PSP_ExceptionHandler(SIL2PSPRegContext *pContext);

/**
 * <description> 
 * <p>Function to handle exceptions by the PSP</p>
 * <p>This function handles the exception and writes pContext->pRetIP if it is different to the default,
 * which may be the case for breakpoits to be able to execute the instruction of the breakpoint.</p>
 * </description>
 * <param name="pContext" type="IN">Context</param>
 * <errorcode name="SIL2PSP_RESULT pResult" type="SIL2PSP_ERR_OK">Exception handled</errorcode>
 * <errorcode name="SIL2PSP_RESULT pResult" type="SIL2PSP_ERR_FAILED">Failed handling exception</errorcode>
 * <result>error code</result>
 */
SIL2PSP_RESULT SIL2PSP_ExceptionHandler2(SIL2PSPRegContext2 *pContext);

/**
 * <description>
 * <p>Function is called to enter system context</p>
 * </description>
 * <param name="puiFlags" type="IN">Flags</param>
 * <errorcode name="SIL2PSP_RESULT pResult" type="SIL2PSP_ERR_OK">Successfully entered system context</errorcode>
 * <errorcode name="SIL2PSP_RESULT pResult" type="SIL2PSP_ERR_PARAMETER">pui32Flags is invalid</errorcode>
 * <errorcode name="SIL2PSP_RESULT pResult" type="SIL2PSP_ERR_FAILED">Failed entering system context</errorcode>
 * <result>error code</result>
 */
SIL2PSP_RESULT SIL2PSP_EnterSystemContext(unsigned int *pui32Flags);

/**
 * <description> 
 * <p>Function is called to enter safe context</p>
 * </description>
 * <param name="puiFlags" type="IN">Flags</param>
 * <errorcode name="SIL2PSP_RESULT pResult" type="SIL2PSP_ERR_OK">Successfully entered safe context</errorcode>
 * <errorcode name="SIL2PSP_RESULT pResult" type="SIL2PSP_ERR_PARAMETER">pui32Flags is invalid</errorcode>
 * <errorcode name="SIL2PSP_RESULT pResult" type="SIL2PSP_ERR_FAILED">Failed entering safe context</errorcode>
 * <result>error code</result>
 */
SIL2PSP_RESULT SIL2PSP_EnterSafeContext(unsigned int *pui32Flags);

/**
 * <description> 
 * <p>Function is called to enter unsafe context</p>
 * </description>
 * <param name="puiFlags" type="IN">Flags</param>
 * <errorcode name="SIL2PSP_RESULT pResult" type="SIL2PSP_ERR_OK">Successfully entered unsafe context</errorcode>
 * <errorcode name="SIL2PSP_RESULT pResult" type="SIL2PSP_ERR_PARAMETER">pui32Flags is invalid</errorcode>
 * <errorcode name="SIL2PSP_RESULT pResult" type="SIL2PSP_ERR_FAILED">Failed entering unsafe context</errorcode>
 * <result>error code</result>
 */
SIL2PSP_RESULT SIL2PSP_EnterUnsafeContext(unsigned int *pui32Flags);

/**
 * <description> 
 * <p>Function is called to leave current context and to return to last context</p>
 * </description>
 * <param name="puiFlags" type="IN">Flags</param>
 * <errorcode name="SIL2PSP_RESULT pResult" type="SIL2PSP_ERR_OK">Successfully left context and switched to last context</errorcode>
 * <errorcode name="SIL2PSP_RESULT pResult" type="SIL2PSP_ERR_PARAMETER">pui32Flags is invalid</errorcode>
 * <errorcode name="SIL2PSP_RESULT pResult" type="SIL2PSP_ERR_FAILED">Failed leaving context</errorcode>
 * <result>error code</result>
 */
SIL2PSP_RESULT SIL2PSP_LeaveContext(unsigned int *pui32Flags);

/**
 * <description>
 * <p>Function is called to get the current operation mode</p>
 * </description>
 * <result>OperationMode. See category Operation Mode.</result>
 */
SIL2PSP_OPMODE SIL2PSP_GetOperationMode(void);

#endif /* _RTSSIL2PSPITF_H_ */
