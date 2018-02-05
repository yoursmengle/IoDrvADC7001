/**
 * <interfacename>CmpMonitor2</interfacename>
 * <description> 
 *	Interface of the new monitoring component, that provides monitoring of IEC variables.
 *
 *  Main advantages of this component against CmpMonitor:
 *	- Minimal stack usage (no recursive function calls) so it is more useful for embedded devices
 *	- Less code and data usage
 *	- All variable access mechanisms are available by default
 *	- Address checking is done for each access layer
 *	- Structured exception handling is fully integrated
 *	So the new monitoring component is recommended for all newer runtime systems and especially for targets with low resources.
 *	CODESYS higher or equal v3.5.0.0 automatically adapts the monitoring, if this new component is integrated in the runtime.
 *
 *	Disadvantage:
 *	- Not compatible with older version of CODESYS (before v3.5.0.0). To support older versions the CmpMonitor must be integrated in parallel.
 *
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpMonitor2')

/**
 * <category>Online services</category>
 */
#define SRV_MONITORING2_READ    1
#define SRV_MONITORING2_WRITE	2
#define SRV_MONITORING2_FORCE	3

#define TAG_MONITORING2_APP_HEADER			0x01
#define TAG_MONITORING2_READ_EXP_LIST		0x02
#define TAG_MONITORING2_WF_EXP_LIST		    0x03
#define TAG_MONITORING2_READ_VALUE_LIST     0x40
#define TAG_MONITORING2_READ_ERROR			0x41

#define TAG_MONITORING2_READ_EXP_LIST2					0x81
#define TAG_MONITORING2_READ_EXP_INFO					0x82
#define TAG_MONITORING2_READ_EXP_LIST2_VARID			0x01
#define TAG_MONITORING2_READ_EXP_LIST2_DATASIZE			0x02
#define TAG_MONITORING2_READ_EXP_LIST2_TYPECLASS		0x03
#define TAG_MONITORING2_READ_EXP_LIST2_BYTECODESIZE		0x04
#define TAG_MONITORING2_READ_EXP_LIST2_BYTECODE			0x05


/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to enable/disable task consistent monitoring of all variables.
 *	1: All variables should be monitored task consistent
 *	0: No task consistency needed
 * </description>
 */
#define MON2KEY_INT_CONSISTENCY_MONITORING				"ConsistencyMonitoring.Enable"
#ifndef MON2VALUE_INT_CONSISTENCY_MONITORING_DEFAULT
	#define MON2VALUE_INT_CONSISTENCY_MONITORING_DEFAULT	0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to set the timeout for consistent monitoring of all variables. Timeout is in [ms];
 * </description>
 */
#define MON2KEY_INT_CONSISTENCY_MONITORING_TIMEOUT				"ConsistencyMonitoring.Timeout"
#ifndef MON2VALUE_INT_CONSISTENCY_MONITORING_TIMEOUT_DEFAULT
	#define MON2VALUE_INT_CONSISTENCY_MONITORING_TIMEOUT_DEFAULT	200
#endif

/**
 * <category>Features</category>
 * <type>Int</type>
 * <description>
 *	The new monitoring component with the byte-code interpreter is present.
 * </description>
 */
#define MONITORING2_FEATURE_INTERPRETER		0x00000001


/**
 * <category>Events</category>
 * <description>
 *    Event is sent to prepare the write operation to an expression.
 *    Note: this event is compatible with the event EVT_PrepareWriteVariable
 *    from the component CmpMonitor.
 * </description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpMonitor2Write</param>
 */
#define EVT_CmpMonitor2_PrepareWrite					MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Events</category>
 * <description>
 *   Event is sent after the write operation to an expression was done.
 *   Note: this event is compatible with the event EVT_WriteVariableDone
 *   from the component CmpMonitor</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpMonitor2Write</param>
 */
#define EVT_CmpMonitor2_WriteDone						MAKE_EVENTID(EVTCLASS_INFO, 2)

/**
 * <category>Events</category>
 * <description>
 *   Event is sent to prepare the force of an expression
 *    Note: this event is compatible with the event EVT_PrepareForceVariable
 *    from the component CmpMonitor
 * </description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpMonitor2Force</param>
 */
#define EVT_CmpMonitor2_PrepareForce					MAKE_EVENTID(EVTCLASS_INFO, 3)

/**
 * <category>Events</category>
 * <description>
 *    Event is sent after the force operation of an expression was done.
 *    Note: this event is compatible with the event EVT_ForceVariableDone
 *    from the component CmpMonitor
 * </description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpMonitor2Force</param>
 */
#define EVT_CmpMonitor2_ForceDone						MAKE_EVENTID(EVTCLASS_INFO, 4)

/**
 * <category>Event parameter</category>
 * <element name="usSize" type="IN">Size of the variable</element>
 * <element name="dummy" type="IN">Alignment dummy</element>
 * <element name="pAddress" type="IN">Pointer to the variable value</element>
 * <element name="pValue" type="IN">Pointer to the write value</element>
 * <element name="bDeny" type="IN">1=Writing variable is denied, 0=Variable can be written</element>
 * <element name="cmpId" type="IN">ComponentID which denies this write operation</element>
 */
typedef struct
{
	RTS_UI16 usSize;
	RTS_UI16 dummy;
#ifdef TRG_64BIT
	RTS_UI32 dummy2;
#endif
	RTS_UI8* pAddress;
	void* pValue;
	RTS_I32 bDeny;
	CMPID cmpId;
}
EVTPARAM_CmpMonitor2Write;

#define EVTPARAMID_CmpMonitor2Write	0x0001
#define EVTVERSION_CmpMonitor2Write	0x0002

/**
 * <category>Event parameter</category>
 * <element name="usForceFlag" type="IN">Force flags</element>
 * <element name="dummy" type="IN">Alignment dummy</element>
 * <element name="pDataRef" type="IN">Data description of the variable</element>
 * <element name="pAppl" type="IN">Pointer to the application description</element>
 * <element name="pAddress" type="IN">Pointer to the variable value, if it is a simple data type (no property variable!)</element>
 * <element name="bDeny" type="IN">1=Forcing variable is denied, 0=Variable can be forced</element>
 * <element name="cmpId" type="IN">ComponentID which denies this write operation</element>
 */
typedef struct
{
	RTS_UI16 usForceFlag;
	RTS_UI16 dummy;
#ifdef TRG_64BIT
	RTS_UI32 dummy2;
#endif
	VarDataRef* pDataRef;
	APPLICATION* pAppl;
	RTS_UI8* pAddress;
	RTS_I32 bDeny;
	CMPID cmpId;
}
EVTPARAM_CmpMonitor2Force;

#define EVTPARAMID_CmpMonitor2Force	0x0002
#define EVTVERSION_CmpMonitor2Force	0x0002


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 *	Routine to check whether the new monitoring component has the specified feature.
 * </description>
 * <param name="ulFeatures" type="IN">Feature flags, See corresponding category "Features".</param>
 * <result>ERR_OK if the flags are supported, an error code otherwise</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`Monitoring2HasFeature',`(RTS_UI32 ulFeatures)')

/**
 * <description>
 * <p>Obsolete: the use of this function is only safe when called from the 
 *    context of the communication task. Use Monitoring2ReadValue2 instead.</p>
 *
 *	Routine to read a monitoring expression given as a byte-code program to
 *  be executed in the byte-code interpreter of CmpMonitor2.
 *
 *  Note: this function may only be called if the user does have access right
 *  USERDB_RIGHT_VIEW.
 *
 *  The byte-code program expects no inputs and, after successful execution,
 *  must have the address of the data to read on the top of the interpreter stack.
 * </description>
 * <param name="pApp" type="IN">Pointer to the application.  May be null if an
 *    IO config paramters is read.</param>
 * <param name="usSizeCodeBytes" type="IN">The size of the byte code in bytes.</param>
 * <param name="pCode" type="IN">Pointer th the byte-code program.</param>
 * <param name="pbyValue" type="IN">pointer to the destination address were the retrieved value is written.</param> 
 * <param name="ulSizeValueBytes" type="IN">size of value to read, in bytes.</param> 
 * <param name="pMonError" type="OUT">The detailed error value if the return value is ERR_FAILED,
 *    see MONITORING_ERR_* in CmpErrors.h.</param>
 * <result>ERR_OK if the value could be written successfully</result>
 * <result>ERR_PARAMETER if pCode, pbyValue, or pMonError is NULL</result>
 * <result>ERR_FAILED if the value could not be written successfully, *pMonError will hold a
 *    detailed error.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`Monitoring2ReadValue',`(APPLICATION* pApp, RTS_UI16 usSizeCodeBytes, const RTS_UI8* pCode, RTS_UI8* pbyValue, RTS_UI32 ulSizeValueBytes, RTS_UI32* pMonError)')

/**
 * <description>
 *	Routine to read a monitoring expression given as a byte-code program to
 *  be executed in the byte-code interpreter of CmpMonitor2.
 *
 *  Note: this function may only be called if the user does have access right
 *  USERDB_RIGHT_VIEW.
 *
 *  The byte-code program expects no inputs and, after successful execution,
 *  must have the address of the data to read on the top of the interpreter stack.
 *
 *  The stack for the byte-code interpreter is passed in by the caller.  This is done
 *  to make the function thread-safe by not sharing any data between threads.
 *  The size of the stack depends on the kind of byte-code programs to be executed.
 *  For example, if strings are to be read, the entire string must fit onto the stack.
 *  Apart from that, it depends on the "nesting depth" of the program.  For most reasonable
 *  expressions of numeric type, a stack size of 32 elements should be enough.
 * </description>
 * <param name="pApp" type="IN">Pointer to the application.  May be null if an
 *    IO config paramters is read.</param>
 * <param name="szStackElems" type="IN">The size of the interpreter stack pStack in elements.</param>
 * <param name="pStack" type="IN">The pointer to the interpreter stack.</param>
 * <param name="usSizeCodeBytes" type="IN">The size of the byte code in bytes.</param>
 * <param name="pCode" type="IN">Pointer th the byte-code program.</param>
 * <param name="pbyValue" type="IN">pointer to the destination address were the retrieved value is written.</param> 
 * <param name="ulSizeValueBytes" type="IN">size of value to read, in bytes.</param> 
 * <param name="pMonError" type="OUT">The detailed error value if the return value is ERR_FAILED,
 *    see MONITORING_ERR_* in CmpErrors.h.</param>
 * <result>ERR_OK if the value could be written successfully</result>
 * <result>ERR_PARAMETER if pStack pCode, pbyValue, or pMonError is NULL, or if szStackElems is 0</result>
 * <result>ERR_FAILED if the value could not be written successfully, *pMonError will hold a
 *    detailed error.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`Monitoring2ReadValue2',`(APPLICATION* pApp, RTS_SIZE szStackElems, RTS_UINTPTR* pStack, RTS_UI16 usSizeCodeBytes, const RTS_UI8* pCode, RTS_UI8* pbyValue, RTS_UI32 ulSizeValueBytes, RTS_UI32* pMonError)')

/**
 * <description>
 *	Routine to execute IEC expressions given as a byte-code program to
 *  be executed in the byte-code interpreter of CmpMonitor2.
 *
 *  Note: this function may only be called if the user does have access right
 *  USERDB_RIGHT_VIEW.
 *
 *  The stack for the byte-code interpreter is passed in by the caller.  This is done
 *  to make the function thread-safe by not sharing any data between threads.
 *  The size of the stack depends on the kind of byte-code programs to be executed.
 *  For example, if strings are to be read, the entire string must fit onto the stack.
 *  Apart from that, it depends on the "nesting depth" of the program.
 * </description>
 * <param name="pApp" type="IN">Pointer to the application.  May be null if an
 *    IO config paramters is read.</param>
 * <param name="szStackElems" type="IN">The size of the interpreter stack pStack in elements.</param>
 * <param name="pStack" type="IN">The pointer to the interpreter stack.</param>
 * <param name="usSizeCodeBytes" type="IN">The size of the byte code in bytes.</param>
 * <param name="pCode" type="IN">Pointer th the byte-code program.</param>
 * <param name="pMonError" type="OUT">The detailed error value if the return value is ERR_FAILED,
 *    see MONITORING_ERR_* in CmpErrors.h.</param>
 * <result>ERR_OK if the value could be written successfully</result>
 * <result>ERR_PARAMETER if pStack pCode, pbyValue, or pMonError is NULL, or if szStackElems is 0</result>
 * <result>ERR_FAILED if the value could not be written successfully, *pMonError will hold a
 *    detailed error.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`Monitoring2ExecuteCode',`(APPLICATION* pApp, RTS_SIZE szStackElems, RTS_UINTPTR* pStack, RTS_UI16 usSizeCodeBytes, const RTS_UI8* pCode, RTS_UI32* pMonError)')

/**
 * <description>
 * <p>Obsolete: the use of this function is only safe when called from the 
 *    context of the communication task. Use Monitoring2WriteValue2 instead.</p>
 *
 *	Routine to write a monitoring expression given as a byte-code program to
 *  be executed in the byte-code interpreter of CmpMonitor2.
 *
 *  Before the value is written, the event EVT_CmpMonitor2_PrepareWrite is
 *  raised, which can lead to an abortion of the write.
 *  After a successful write, the event EVT_CmpMonitor2_WriteDone is raised.
 *
 *  If the operation OP_APP_WRITE_VARIABLES is disabled for the application,
 *  the function returns with an error.
 *
 *  Note: this function may only be called if the user does have access right
 *  USERDB_RIGHT_MODIFY.
 *
 *  The byte-code program expects three arguments on the F-Stack: the address of
 *  the data to write (type void*), the length of the data to write in chars
 *  (type RTS_UI32), and the mode of operation (type RTS_UI32) which is either
 *  MODE_ADDR (0) or MODE_WRITE (1).  For the detailed explanation of these
 *  inputs see FS_CmpMonitor2.doc, section 3.3.
 *  Note: the byte-code programs created by the OnlineManager in CODESYS behave
 *  as described above.
 * </description>
 * <param name="pApp" type="IN">Pointer to application.  May be null if an
 *    IO config paramters is written.</param>
 * <param name="usSizeCodeBytes" type="IN">The size of the byte code in bytes.</param>
 * <param name="pCode" type="IN">Pointer th the byte-code program.</param>
 * <param name="pbyValue" type="IN">pointer to the source address of the value to write.</param> 
 * <param name="ulSizeValueBytes" type="IN">size of the value to write.</param>
 * <param name="pMonError" type="OUT">The detailed error value if the return value is ERR_FAILED,
 *    see MONITORING_ERR_* in CmpErrors.h.</param>
 * <result>ERR_OK if the value could be written successfully</result>
 * <result>ERR_PARAMETER if pCode, pbyValue, or pMonError is NULL</result>
 * <result>ERR_FAILED if the value could not be written successfully, *pMonError will hold a
 *    detailed error.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`Monitoring2WriteValue',`(APPLICATION* pApp,  RTS_UI16 usSizeCodeBytes, const RTS_UI8* pCode, const RTS_UI8* pbyValue, RTS_UI32 ulSizeValueBytes, RTS_UI32* pMonError)')

/**
 * <description>
 *	Routine to write a monitoring expression given as a byte-code program to
 *  be executed in the byte-code interpreter of CmpMonitor2.
 *
 *  Before the value is written, the event EVT_CmpMonitor2_PrepareWrite is
 *  raised, which can lead to an abortion of the write.
 *  After a successful write, the event EVT_CmpMonitor2_WriteDone is raised.
 *
 *  If the operation OP_APP_WRITE_VARIABLES is disabled for the application,
 *  the function returns with an error.
 *
 *  Note: this function may only be called if the user does have access right
 *  USERDB_RIGHT_MODIFY.
 *
 *  The stack for the byte-code interpreter is passed in by the caller.  This is done
 *  to make the function thread-safe by not sharing any data between threads.
 *  The size of the stack depends on the kind of byte-code programs to be executed.
 *  For most reasonable expressions of numeric type, a stack size of 32 elements
 *  should be enough.
 *
 *  The byte-code program expects three arguments on the F-Stack: the address of
 *  the data to write (type void*), the length of the data to write in chars
 *  (type RTS_UI32), and the mode of operation (type RTS_UI32) which is either
 *  MODE_ADDR (0) or MODE_WRITE (1).  For the detailed explanation of these
 *  inputs see FS_CmpMonitor2.doc, section 3.3.
 *  Note: the byte-code programs created by the OnlineManager in CODESYS behave
 *  as described above.
 * </description>
 * <param name="pApp" type="IN">Pointer to application.  May be null if an
 *    IO config paramters is written.</param>
 * <param name="szStackElems" type="IN">The size of the interpreter stack pStack in elements.</param>
 * <param name="pStack" type="IN">The pointer to the interpreter stack.</param>
 * <param name="usSizeCodeBytes" type="IN">The size of the byte code in bytes.</param>
 * <param name="pCode" type="IN">Pointer th the byte-code program.</param>
 * <param name="pbyValue" type="IN">pointer to the source address of the value to write.</param> 
 * <param name="ulSizeValueBytes" type="IN">size of the value to write.</param>
 * <param name="pMonError" type="OUT">The detailed error value if the return value is ERR_FAILED,
 *    see MONITORING_ERR_* in CmpErrors.h.</param>
 * <result>ERR_OK if the value could be written successfully</result>
 * <result>ERR_PARAMETER if pStack, pCode, pbyValue, or pMonError is NULL or if szStackElems is 0</result>
 * <result>ERR_FAILED if the value could not be written successfully, *pMonError will hold a
 *    detailed error.</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`Monitoring2WriteValue2',`(APPLICATION* pApp, RTS_SIZE szStackElems, RTS_UINTPTR* pStack, RTS_UI16 usSizeCodeBytes, const RTS_UI8* pCode, const RTS_UI8* pbyValue, RTS_UI32 ulSizeValueBytes, RTS_UI32* pMonError)')

#ifdef __cplusplus
}
#endif
