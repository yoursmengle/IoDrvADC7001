/**
 * <interfacename>SysInt</interfacename>
 * <description> 
 *	<p>The SysInt interface is projected to get access to the hardware interrupts of 
 *	the system.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysInt')

#include "CmpItf.h"

/**
 * <category>Static defines</category>
 * <description>Maximum number of interrupts</description>
 */
#ifndef MAX_INT
	#define		MAX_INT		2
#endif

/**
 * <category>Static defines</category>
 * <description>Maximum number of callback function for each interrupt</description>
 */
#ifndef MAX_INT_CALLBACKS
	#define		MAX_INT_CALLBACKS	1
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Use SysInt mapping for interrupts. Only used for WinCE.
 * 0: Do not use
 * 1: Use it
 * </description>
 */
#define SYSINTKEY_INT_WINCE_USE_SYSINTMAPPING				"WinCE.UseIRQSysIntrMapping"
#define SYSINTVALUE_INT_WINCE_DEFAULT_USE_SYSINTMAPPING		0

/**
 * <category>Interrupt handler type</category>
 * <description>Specification, which type of routine the handler is</description>
 */
#define		SYS_INT_NONE	0
#define		SYS_INT_IEC		1
#define		SYS_INT_C		2
	
/**
 * <category>Interrupt handler</category>
 * <description>Interrupt handler prototype</description>
 * <param name="ulAdditionalInfo" type="IN">Additional info that can be specified at registering the handler</param>
 */
typedef void HUGEPTR(CDECL *SYS_INT_INTHANDLER)(RTS_UINTPTR ulAdditionalInfo);

RTS_RESULT CDECL SysIntOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysIntOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <category>Event parameter</category>
 * <element name="ulInterrupt" type="IN">Interrupt number</element>
 */
typedef struct
{
	unsigned long ulInterrupt;
} EVTPARAM_SysInt;
#define EVTPARAMID_SysInt			0x0001
#define EVTVERSION_SysInt			0x0001

/**
 * <category>Events</category>
 * <description>Hardware interrupt events</description>
 * <param name="pEventParam" type="IN">EVTPARAM_SysInt</param>
 */
#define EVT_INTERRUPT_0						MAKE_EVENTID(EVTCLASS_INTERRUPT, 0)
#define EVT_INTERRUPT_1						MAKE_EVENTID(EVTCLASS_INTERRUPT, 1)
#define EVT_INTERRUPT_2						MAKE_EVENTID(EVTCLASS_INTERRUPT, 2)
#define EVT_INTERRUPT_3						MAKE_EVENTID(EVTCLASS_INTERRUPT, 3)
#define EVT_INTERRUPT_4						MAKE_EVENTID(EVTCLASS_INTERRUPT, 4)
#define EVT_INTERRUPT_5						MAKE_EVENTID(EVTCLASS_INTERRUPT, 5)
#define EVT_INTERRUPT_6						MAKE_EVENTID(EVTCLASS_INTERRUPT, 6)
#define EVT_INTERRUPT_7						MAKE_EVENTID(EVTCLASS_INTERRUPT, 7)
#define EVT_INTERRUPT_8						MAKE_EVENTID(EVTCLASS_INTERRUPT, 8)
#define EVT_INTERRUPT_9						MAKE_EVENTID(EVTCLASS_INTERRUPT, 9)
#define EVT_INTERRUPT_10					MAKE_EVENTID(EVTCLASS_INTERRUPT, 10)
#define EVT_INTERRUPT_11					MAKE_EVENTID(EVTCLASS_INTERRUPT, 11)
#define EVT_INTERRUPT_12					MAKE_EVENTID(EVTCLASS_INTERRUPT, 12)
#define EVT_INTERRUPT_13					MAKE_EVENTID(EVTCLASS_INTERRUPT, 13)
#define EVT_INTERRUPT_14					MAKE_EVENTID(EVTCLASS_INTERRUPT, 14)
#define EVT_INTERRUPT_15					MAKE_EVENTID(EVTCLASS_INTERRUPT, 15)
#define EVT_INTERRUPT_255					MAKE_EVENTID(EVTCLASS_INTERRUPT, 255)

/**
 * <description>Sys Int Callback Info Struct</description>
 * <param name="pCallback">Pointer to Callback for Sys Int Callback Info</param>
 * <param name="ulType">Type of Sys Int Callback Info</param>
 * <param name="ulAdditionalInfo">Additional Info for Sys Int Callback Info</param>
 */
typedef struct
{
	SYS_INT_INTHANDLER 	pCallback;
	unsigned long		ulType;
	RTS_UINTPTR			ulAdditionalInfo;
}SYS_INT_CALLBACK_INFO;

/**
 * <description>Sys Int Info Struct</description>
 * <param name="pszName">Name for Sys Int Info</param>
 * <param name="pSysData">SysData Pointer for Sys Int Info</param>
 * <param name="hCallbackPool">Handle for CallbackPool for Sys Int Info</param>
 * <param name="ulInterrupt">InterruptNr for Sys Int Info</param>
 */
typedef struct
{
	char*					pszName;
	void*					pSysData;
	RTS_HANDLE				hCallbackPool;
	unsigned long			ulInterrupt;
}SYS_INT_INFO;

/**
 * <category>Bus types</category>
 * <description>Architecture specific bus types</description>
 */
#define BT_Internal		0
#define BT_ISA			1
#define BT_EISA			2
#define BT_PCI			3
#define BT_VME			4
#define BT_PCMCIA		5
#define BT_ProcessorInternal	6
#define BT_MaxType		7

/**
 * <category>Interrupt modes</category>
 * <description></description>
 */
#define IM_LevelSensitive	0
#define IM_Latched			1


#define ISysIntIEC			isysintiec_struct

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <category>Pci interrupt</category>
 * <description><p>
 *	PCI specific interrupt description
 * </p></description>
 */
typedef struct tagPciInterrupt
{
	RTS_IEC_UDINT ulBusNumber;		/* <element name="ulBusNumber" type="IN">Bus number on the PCI bus</element> */
	RTS_IEC_UDINT ulDevciceNumber;		/* <element name="ulDevciceNumber" type="IN">Device number on the PCI bus</element> */
	RTS_IEC_UDINT ulFunctionNumber;		/* <element name="ulFunctionNumber" type="IN">Function number on the PCI bus. Is used for different functions on the same device.</element> */
	RTS_IEC_UDINT ulIntLine;		/* <element name="ulIntLine" type="IN">Interrupt line on the PCI bus.</element> */
} PciInterrupt;

/**
 * <category>Isa interrupt</category>
 * <description><p>
 *	ISA specific interrupt description
 * </p></description>
 */
typedef struct tagIsaInterrupt
{
	RTS_IEC_UDINT ulBusNumber;		/* <element name="ulBusNumber" type="IN">Unused on the ISA bus</element> */
	RTS_IEC_UDINT ulDevciceNumber;		/* <element name="ulDevciceNumber" type="IN">Unused on the ISA bus</element> */
	RTS_IEC_UDINT ulFunctionNumber;		/* <element name="ulFunctionNumber" type="IN">Unused on the ISA bus</element> */
	RTS_IEC_UDINT ulIntLine;		/* <element name="ulIntLine" type="IN">Unused on the ISA bus</element> */
} IsaInterrupt;

/**
 * <category>Bus specific</category>
 * <description><p>
 *	Bus specific interrupt description
 * </p></description>
 */
typedef union
{
	PciInterrupt pciInterrupt;		/* <param name="pciInterrupt">PCI interrupt</param> */
	IsaInterrupt isaInterrupt;		/* <param name="isaInterrupt">ISA interrupt</param> */
} BusSpecific;

/**
 * <category>Interrupt description</category>
 * <description><p>Optional description for an interrupt</p></description>
 */
typedef struct tagSYS_INT_DESCRIPTION
{
	RTS_IEC_UDINT BusType;		/* <param name="BusType">Bus type (architecture specific). See "BusTypes" for details.</param> */
	RTS_IEC_UDINT InterruptMode;		/* <param name="InterruptMode">Interrupt mode</param> */
	BusSpecific busSpecific;		/* <param name="busSpecific">Pci bus specific definitions</param> */
} SYS_INT_DESCRIPTION;

typedef struct
{
	void* __VFTABLEPOINTER;	/* Pointer to virtual function table */
} isysintiec_struct;

/**
 * <description>Close an interrupt</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysintclose_struct
{
	RTS_IEC_HANDLE hInt;				/* VAR_INPUT */	/* <param name="hInt" type="IN">Handle to interrupt returned by SysIntOpen.</param> */
	RTS_IEC_RESULT SysIntClose;			/* VAR_OUTPUT */	
} sysintclose_struct;

DEF_API(`void',`CDECL',`sysintclose',`(sysintclose_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0E05F037),0x03050500)

/**
 * <description>Function to disable an interrupt. By use of this function the interrupt specified by its handle
 * gets deactivated (masked).</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysintdisable_struct
{
	RTS_IEC_HANDLE hInt;				/* VAR_INPUT */	/* <param name="hInt" type="IN">Handle to interrupt returned by SysIntOpen.</param> */
	RTS_IEC_RESULT SysIntDisable;		/* VAR_OUTPUT */	
} sysintdisable_struct;

DEF_API(`void',`CDECL',`sysintdisable',`(sysintdisable_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC9EC050C),0x03050500)

/**
 * <description>Function to disable all interrupts. By use of this functions all interrupts are deactivated (masked).
 * A call of SysIntDisableAll has to be succeeded by a call to SysIntEnableAll!</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysintdisableall_struct
{
	RTS_IEC_UXINT *pulParam;			/* VAR_INPUT */	/* <param name="pulParam" type="IN">Parameter for the target to return the actual masled interrupts to use after in SysIntEnableAll().</param> */
	RTS_IEC_RESULT SysIntDisableAll;	/* VAR_OUTPUT */	
} sysintdisableall_struct;

DEF_API(`void',`CDECL',`sysintdisableall',`(sysintdisableall_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xBE4C0839),0x03050500)

/**
 * <description>Function to enable an interrupt. By use of this function the interrupt specified by its handle
 * is activated.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysintenable_struct
{
	RTS_IEC_HANDLE hInt;				/* VAR_INPUT */	/* <param name="hInt" type="IN">Handle to interrupt returned by SysIntOpen.</param> */
	RTS_IEC_RESULT SysIntEnable;		/* VAR_OUTPUT */	
} sysintenable_struct;

DEF_API(`void',`CDECL',`sysintenable',`(sysintenable_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x30131B72),0x03050500)

/**
 * A call to this function will be done after a call of function SysIntDisableAll and  will restore the situation
 * preceding the execution of SysIntDisableAll. That means, all interrupts, having been activated before the call
 * to SysIntDisableAll are activated again.
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysintenableall_struct
{
	RTS_IEC_UXINT *pulParam;			/* VAR_INPUT */	/* <param name="pulParam" type="IN">Parameter for the target with the masked interrupts that must are deactivated by the
 previous call to SysIntDisableAll().</param> */
	RTS_IEC_RESULT SysIntEnableAll;		/* VAR_OUTPUT */	
} sysintenableall_struct;

DEF_API(`void',`CDECL',`sysintenableall',`(sysintenableall_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xDE565CD4),0x03050500)

/**
 * <description> 
 * This function checks if the processor is actually executing an ISR. This information is necessary, as some functions
 * of an operating system must not be called within the interrupt level.
 * </description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library):
 *	<ul>
 *		<li>ERR_OK: We are still in an interrupt handler</li>
 *		<li>ERR_FAILED: not in interrupt context</li>
 *	</ul>
 * </p></result>
 */
typedef struct tagsysintlevel_struct
{
	RTS_IEC_RESULT SysIntLevel;			/* VAR_OUTPUT */	
} sysintlevel_struct;

DEF_API(`void',`CDECL',`sysintlevel',`(sysintlevel_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCA219D99),0x03050500)

/**
 * <description>Open a valid interrupt</description>
 * <result><p>RESULT: Handle to the interrupt or RTS_INVALID_HANDLE if failed.</p></result>
 */
typedef struct tagsysintopen_struct
{
	RTS_IEC_UDINT ulInterrupt;			/* VAR_INPUT */	/* <param name="ulInterrupt" type="IN">Interrupt number</param> */
	SYS_INT_DESCRIPTION *pIntDescription;	/* VAR_INPUT */	/* <param name="pIntDescription" type="IN">Pointer to optional interrupt description</param> */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param> */
	RTS_IEC_HANDLE SysIntOpen;			/* VAR_OUTPUT */	
} sysintopen_struct;

DEF_API(`void',`CDECL',`sysintopen',`(sysintopen_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB3D594FF),0x03050500)

/**
 * <description>Open a valid interrupt specified by name</description>
 * <result><p>RESULT: Handle to the interrupt or RTS_INVALID_HANDLE if failed.</p></result>
 */
typedef struct tagsysintopenbyname_struct
{
	RTS_IEC_STRING *pszIntName;			/* VAR_INPUT */	/* <param name="pszIntName" type="IN">Interrupt name defined in the settings component</param> */
	RTS_IEC_RESULT *Result;				/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param> */
	RTS_IEC_HANDLE SysIntOpenByName;	/* VAR_OUTPUT */	
} sysintopenbyname_struct;

DEF_API(`void',`CDECL',`sysintopenbyname',`(sysintopenbyname_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x928117BD),0x03050500)

/**
 * <description>Function to register an interrupt handler.
 * By use of this function an interrupt handler (Interrupt Service Routine, ISR) for the interrupt specified by its handle 
 * gets registered. During registration, the start address of the function to be executed in case of the associated interrupt
 * request is filled into the vector table on the target.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysintregister_struct
{
	RTS_IEC_HANDLE hInt;				/* VAR_INPUT */	/* <param name="hInt" type="IN">Handle to interrupt returned by SysIntOpen.</param> */
	RTS_IEC_BYTE *pCallback;			/* VAR_INPUT */	/* <param name="pCallback" type="IN">Interrupt handler. Callback layout:<br />
	FUNCTION IntHandler : RTS_IEC_RESULT<br />
 VAR_INPUT<br />
		ulAdditionalInfo : UDINT;<br />
	END_VAR
 </param> */
	RTS_IEC_UXINT ulAdditionalInfo;		/* VAR_INPUT */	/* <param name="ulAdditionalInfo" type="IN">Info value that is transmitted to the interrupt handler</param> */
	RTS_IEC_RESULT SysIntRegister;		/* VAR_OUTPUT */	
} sysintregister_struct;

DEF_API(`void',`CDECL',`sysintregister',`(sysintregister_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x63A36B82),0x03050500)

/**
 * <description>Still unsupported function!</description>
 */
typedef struct tagsysintregisterinstance_struct
{
	RTS_IEC_HANDLE hInt;				/* VAR_INPUT */	
	RTS_IEC_UDINT ulClassId;			/* VAR_INPUT */	
	RTS_IEC_UDINT ulItfId;				/* VAR_INPUT */	
	ISysIntIEC *pInterface;				/* VAR_INPUT */	
	RTS_IEC_UXINT ulAdditionalInfo;		/* VAR_INPUT */	
	RTS_IEC_RESULT SysIntRegisterInstance;	/* VAR_OUTPUT */	
} sysintregisterinstance_struct;

DEF_API(`void',`CDECL',`sysintregisterinstance',`(sysintregisterinstance_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC0428DE2),0x03050500)

/**
 * <description>Function to unregister an interrupt handler</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsysintunregister_struct
{
	RTS_IEC_HANDLE hInt;				/* VAR_INPUT */	/* <param name="hInt" type="IN">Handle to interrupt returned by SysIntOpen.</param> */
	RTS_IEC_BYTE *pCallback;			/* VAR_INPUT */	/* <param name="pCallback" type="IN">Interrupt handler</param> */
	RTS_IEC_RESULT SysIntUnregister;	/* VAR_OUTPUT */	
} sysintunregister_struct;

DEF_API(`void',`CDECL',`sysintunregister',`(sysintunregister_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x9CA9B33A),0x03050500)

/**
 * <description>Still unsupported function!</description>
 */
typedef struct tagsysintunregisterinstance_struct
{
	RTS_IEC_HANDLE hInt;				/* VAR_INPUT */	
	ISysIntIEC *pInterface;				/* VAR_INPUT */	
	RTS_IEC_RESULT SysIntUnregisterInstance;	/* VAR_OUTPUT */	
} sysintunregisterinstance_struct;

DEF_API(`void',`CDECL',`sysintunregisterinstance',`(sysintunregisterinstance_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA2A67F42),0x03050500)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Open a valid interrupt</description>
 * <param name="ulInterrupt" type="IN" range="[0,VALID_INT_NR,INVALID_INT_NR]">Interrupt number</param>
 * <param name="pIntDescription" type="IN" range="[0,VALID_INT_DESCR,INVALID_INT_DESCR]">Pointer to optional interrupt description</param>
 * <param name="pResult" type="OUT">Pointer to result</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Interrupt could be opened, a valid Handle is returned</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">Interrupt could not be opened, an invalid Handle is returned</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Invalid ulInterrupt Parameter</errorcode>
 * <result>Handle to interrupt, is RTS_INVALID_HANDLE if error occured, see Errorcodes.</result>
 */
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysIntOpen',`(unsigned long ulInterrupt, SYS_INT_DESCRIPTION *pIntDescription, RTS_RESULT *pResult)')

/**
 * <description>Open a valid interrupt specified by name</description>
 * <param name="pszIntName" type="IN" range="[0,VALID_INT_NAMR,INVALID_INT_NAME]">Interrupt name defined in the settings component</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Interrupt could be opened, a valid Handle is returned</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">Interrupt could not be opened, an invalid Handle is returned</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_PARAMETER">Parameter wrong, an invalid Handle is returned</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_OBJECT">No Interrupt found for given Name</errorcode>
 * <param name="pResult" type="OUT">Pointer to result</param>
 * <result>Handle to interrupt</result>
 */
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysIntOpenByName',`(char* pszIntName, RTS_RESULT* pResult)')

/**
 * <description>Close an interrupt</description>
 * <param name="hInt" type="IN" range="[RTS_INVALID_HANDLE,0,VALID_INT_HANDLE]">Interrupt handle</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Interrupt could be closed</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Interrupt could not be closed</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NO_OBJECT">No Interrupt found for Parameter</errorcode>
 * <result>error code</result>
 */
DEF_DELETEITF_API(`RTS_RESULT',`CDECL',`SysIntClose',`(RTS_HANDLE hInt)')

/**
 * <description>Function to enable an interrupt</description>
 * <param name="hInt" type="IN" range="[RTS_INVALID_HANDLE,0,VALID_INT_HANDLE]">Handle to the interrupt</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Interrupt could be enabled</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Interrupt could not be enabled</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NO_OBJECT">No Interrupt found for Parameter</errorcode>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysIntEnable',`(RTS_HANDLE hInt)')

/**
 * <description>Function to disable an interrupt</description>
 * <param name="hInt" type="IN" range="[RTS_INVALID_HANDLE,0,VALID_INT_HANDLE]">Handle to the interrupt</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Interrupt could be disabled</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Interrupt could not be disabled</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NO_OBJECT">No Interrupt found for Parameter</errorcode>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysIntDisable',`(RTS_HANDLE hInt)')

/**
 * <description>Function to register an interrupt handler</description>
 * <param name="hInt" type="IN" range="[RTS_INVALID_HANDLE,0,VALID_INT_HANDLE]">Handle to the interrupt</param>
 * <param name="ulType" type="IN" range="[SYS_INT_NONE,SYS_INT_IEC,SYS_INT_C,INVALID_INT_TYPE]">Type of interrupt handler. See category Interrupt handler type</param>
 * <param name="pHandler" type="IN" range="[0,VALID_INT_HANDLER,INVALID_INT_HANDLER]">Interrupt handler</param>
 * <param name="ulAdditionalInfo" type="IN" range="[0,VALID_INT_ADDINFO,INVALID_INT_ADDINFO]">Info value that is transmitted to the interrupt handler</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Interrupt Handler could be registered</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Interrupt Handler could not be registered</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NO_OBJECT">No Interrupt found for Parameter, Wrong Type</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">pHandler may not be null</errorcode>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysIntRegister',`(RTS_HANDLE hInt, unsigned long ulType, SYS_INT_INTHANDLER pHandler, RTS_UINTPTR ulAdditionalInfo)')

/**
 * <description>Function to unregister an interrupt handler</description>
 * <param name="hInt" type="IN" range="[RTS_INVALID_HANDLE,0,VALID_INT_HANDLE]">Handle to the interrupt</param>
 * <param name="pHandler" type="IN" range="[0,VALID_INT_HANDLER,INVALID_INT_HANDLER]">Interrupt handler</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Interrupt Handler could be unregistered</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Interrupt Handler could not be unregistered</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NO_OBJECT">No Interrupt found for hInt</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">pHandler may not be null</errorcode>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysIntUnregister',`(RTS_HANDLE hInt, SYS_INT_INTHANDLER pHandler)')

/**
 * <description>Function to enable all interrupts</description>
 * <param name="pulParam" type="IN" range="[NULL,VALID_PARAM,INVALID_PARAM_NONE,INVALID_PARAM_FULL]">Parameter for enabling all interrupts</param>
 * <parampseudo name="bTimerOccured" type="OUT" range="[TRUE,FALSE]">Specifies, if a timer was able to run, during the lock, or not</parampseudo>
 * <parampseudo name="bWatchdogOccured" type="OUT" range="[TRUE,FALSE]">Specifies, if the watchdog handler was able to run, during the lock, or not</parampseudo>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Interrupts could be enabled</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">Function is not supported by the system</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysIntEnableAll',`(RTS_UINTPTR *pulParam)')

/**
 * <description>Function to disable all interrupts</description>
 * <param name="pulParam" type="INOUT" range="[NULL,VALID_PARAM]">Parameter for disabling all interrupts</param>
 * <parampseudo name="bTimerOccured" type="OUT" range="[TRUE,FALSE]">Specifies, if a timer was able to run, during the lock, or not</parampseudo>
 * <parampseudo name="bWatchdogOccured" type="OUT" range="[TRUE,FALSE]">Specifies, if the watchdog handler was able to run, during the lock, or not</parampseudo>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Interrupts could be disabled</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_NOTIMPLEMENTED">Function is not supported by the system</errorcode>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysIntDisableAll',`(RTS_UINTPTR *pulParam)')

/**
 * <description>Function to check, if we are running actual in an interrupt context</description>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">We are still in an interrupt handler</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">not in interrupt context</errorcode>
 * <result>Returns ERR_OK if running in an interrupt handler, ERR_FAILED if not</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysIntLevel',`(void)')


#ifdef __cplusplus
}
#endif
