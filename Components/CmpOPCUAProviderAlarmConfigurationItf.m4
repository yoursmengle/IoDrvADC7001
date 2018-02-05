/**
 * <interfacename>CmpOPCUAProviderAlarmConfiguration</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`CmpOPCUAProviderAlarmConfiguration')

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This function is used to send and event to the OPC UA Server.
 */
typedef struct tagcmpopcuaprovideralarmconfigurationfireevent_struct
{
	RTS_IEC_HANDLE hApplication;		/* VAR_INPUT */	/* Handle to the registered application returned by CmpOPCUAProviderAlarmConfigurationRegister */
	RTS_IEC_UDINT ui32EventId;			/* VAR_INPUT */	/* EventID of the alarm manager. */
	RTS_IEC_LINT eventTimestamp;		/* VAR_INPUT */	/* The timestamp of the event. The alarm Manager used 100ns interval since 1.1.1601. Same format as OPC UA. */
	RTS_IEC_UDINT ui32Priority;			/* VAR_INPUT */	/* Priority of the event. Has to be converted to OPC UA notation 1 (lowest) - 1000 (highest) priority */
	RTS_IEC_WSTRING *message;			/* VAR_INPUT */	/* WSTRING message of the event. Will be converted to UTF-8 by the OPC UA server. */
	RTS_IEC_RESULT CmpOPCUAProviderAlarmConfigurationFireEvent;	/* VAR_OUTPUT */	
} cmpopcuaprovideralarmconfigurationfireevent_struct;

DEF_API(`void',`CDECL',`cmpopcuaprovideralarmconfigurationfireevent',`(cmpopcuaprovideralarmconfigurationfireevent_struct *p)',1,0xEC235428,0x03050C00)

/**
 * This function is used to register the applicaiton at the OPC UA server as event source.
 */
typedef struct tagcmpopcuaprovideralarmconfigurationregister_struct
{
	APPLICATION *pApplication;			/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_HANDLE CmpOPCUAProviderAlarmConfigurationRegister;	/* VAR_OUTPUT */	
} cmpopcuaprovideralarmconfigurationregister_struct;

DEF_API(`void',`CDECL',`cmpopcuaprovideralarmconfigurationregister',`(cmpopcuaprovideralarmconfigurationregister_struct *p)',1,0xF4F696A7,0x03050C00)

/**
 * This function is used to unregsiter the applicaiton as an event source.
 */
typedef struct tagcmpopcuaprovideralarmconfigurationunregister_struct
{
	RTS_IEC_HANDLE hAlarmHandler;		/* VAR_INPUT */	
	RTS_IEC_RESULT CmpOPCUAProviderAlarmConfigurationUnregister;	/* VAR_OUTPUT */	
} cmpopcuaprovideralarmconfigurationunregister_struct;

DEF_API(`void',`CDECL',`cmpopcuaprovideralarmconfigurationunregister',`(cmpopcuaprovideralarmconfigurationunregister_struct *p)',1,0x06481C5A,0x03050C00)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

