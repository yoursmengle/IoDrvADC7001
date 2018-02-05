 /**
 * <interfacename>CmpMonitor</interfacename>
 * <description> 
 *	Interface of the monitoring component, that provides monitoring of IEC variables.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */



	
	
#ifndef _CMPMONITORITF_H_
#define _CMPMONITORITF_H_

#include "CmpStd.h"

 

 




/**
 * <category>Online services</category>
 * <description></description>
 */
#define SRV_MONITORLISTONCE		1
#define SRV_WRITE_VARIABLES		2
#define SRV_FORCE_VARIABLES		3

#define TAG_MONITORING			0x81
#define TAG_MON_DEREF			0x82
#define TAG_MON_COMPO			0x83
#define TAG_MON_ARRAYACCESS		0x84
#define TAG_MON_INDEX_REF		0x85
#define TAG_MON_OPERATOR		0x86
#define TAG_MON_NEW_BIT  		0x87
#define TAG_MON_PROP_EXT  		0x88
#define TAG_MON_FUNC_CALL		0x89
#define TAG_MON_FUNC_PARAM_INFO 	0x8A

#define TAG_MON_APPLICATION		0x10
#define TAG_MON_SIMPLEDATA		0x11
#define TAG_MON_STACKRELATIVE	0x12
#define TAG_MON_COMPO_DATA		0x13
#define TAG_MON_VAR_ID			0x14
#define TAG_MON_PARAMETER_TYPE	0x16
#define TAG_MON_DEREF_DATA		0x17
#define TAG_MON_BIT_DATA		0x18
#define TAG_MON_CONNECTOR_DIAG	0x19
#define TAG_MON_PROPERTY_CALL	0x20
#define TAG_MON_ARRAY_DATA		0x21
#define TAG_MON_ARRAY_BOUNDS	0x22
#define TAG_MON_OPERATOR_DATA	0x23
#define TAG_MON_SIGNED_CONST	0x24
#define TAG_MON_NEW_BITDATA		0x25
#define TAG_MON_STACKRELATIVE_SP 0x26
#define TAG_MON_PROPEXT_DATA	0x27
#define TAG_MON_FUNC_CALL_DATA	0x28
#define TAG_MON_FUNC_PARAM_INFO_DATA 0x29
#define TAG_MON_PROPERTY_CALL_REFERENCE 0x2A
#define TAG_MON_PROPEXT_DATA_REF 0x2B


/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to enable/disable task consistent monitoring of all variables.
 *	1: All variables should be monitored task consistent
 *	0: No task consistency needed
 * </description>
 */
#define MON_INT_CONSISTENCY_MONITORING				"ConsistencyMonitoring.Enable"
#ifndef MON_INT_CONSISTENCY_MONITORING_DEFAULT
	#define MON_INT_CONSISTENCY_MONITORING_DEFAULT	0
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 *	Setting to set the timeout for consistent monitoring of all variables. Timeout is in [ms];
 * </description>
 */
#define MON_INT_CONSISTENCY_MONITORING_TIMEOUT				"ConsistencyMonitoring.Timeout"
#ifndef MON_INT_CONSISTENCY_MONITORING_TIMEOUT_DEFAULT
	#define MON_INT_CONSISTENCY_MONITORING_TIMEOUT_DEFAULT	200
#endif


/**
 * <category>Features</category>
 * <type>Int</type>
 * <description>
 *	Supported features of the monitoring component
 * </description>
 */
#define MONITORING_FEATURE_COMPLEX_MONITORING			0x00000001


/**
 * <category>Event parameter</category>
 * <element name="usSize" type="IN">Size of the variable</element>
 * <element name="dummy" type="IN">Alignment dummy</element>
 * <element name="pAddress" type="IN">Pointer to the variable value</element>
 * <element name="pValue" type="IN">Pointer to the write value</element>
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
}
EVTPARAM_CmpMonitorWriteVar;

#define EVTPARAMID_CmpMonitor	0x0001
#define EVTVERSION_CmpMonitor	0x0001

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
EVTPARAM_CmpMonitorWriteVar2;

#define EVTPARAMID_CmpMonitor2	0x0001
#define EVTVERSION_CmpMonitor2	0x0002

/**
 * <category>Events</category>
 * <description>Event is sent to prepare the write operation to a variable</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpMonitorWriteVar2</param>
 */
#define EVT_PrepareWriteVariable					MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Events</category>
 * <description>Event is sent after the write operation to a variable was done</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpMonitorWriteVar</param>
 */
#define EVT_WriteVariableDone						MAKE_EVENTID(EVTCLASS_INFO, 2)

/**
 * <category>Events</category>
 * <description>Event is sent to prepare the force of variable</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpMonitorForceVar2</param>
 */
#define EVT_PrepareForceVariable					MAKE_EVENTID(EVTCLASS_INFO, 3)

/**
 * <category>Events</category>
 * <description>Event is sent after the force operation of a variable was done</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpMonitorForceVar</param>
 */
#define EVT_ForceVariableDone						MAKE_EVENTID(EVTCLASS_INFO, 4)

/**
 * <category>Event parameter</category>
 * <element name="usForceFlag" type="IN">Force flags</element>
 * <element name="dummy" type="IN">Alignment dummy</element>
 * <element name="pDataRef" type="IN">Data description of the variable</element>
 * <element name="pAppl" type="IN">Pointer to the application description</element>
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
}
EVTPARAM_CmpMonitorForceVar;

#define EVTPARAMID_CmpMonitorForce	0x0002
#define EVTVERSION_CmpMonitorForce	0x0001

/**
 * <category>Event parameter</category>
 * <element name="usForceFlag" type="IN">Force flags</element>
 * <element name="dummy" type="IN">Alignment dummy</element>
 * <element name="pDataRef" type="IN">Data description of the variable</element>
 * <element name="pAppl" type="IN">Pointer to the application description</element>
 * <element name="pAddress" type="IN">Pointer to the variable value, if it is a simple data type (no property variable!)</element>
 * <element name="bDeny" type="IN">1=Writing variable is denied, 0=Variable can be written</element>
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
EVTPARAM_CmpMonitorForceVar2;

#define EVTPARAMID_CmpMonitorForce2	0x0002
#define EVTVERSION_CmpMonitorForce2	0x0002


typedef struct
{
	RTS_UI32 ulSessionId;
#ifdef RTS_SIXTEENBITBYTES
	RTS_UI16 aucDataId[8];
#else
	RTS_UI8 aucDataId[16];
#endif
} MONITOR_HEADER;

typedef union
{
	RTS_UI16 usId; /* valid for monitoring request (SRV_MONITORLISTONCE) only */
	RTS_I8 value[1];       /* valid for force or write request only */
} MON_VALUE_RESULT;

typedef struct
{
	RTS_UI32 ulModuleType;
	RTS_UI32 ulInstance;
	RTS_UI32 ulParameterId;
	RTS_UI32 ulOffset;
	RTS_UI16 usSize;
	MON_VALUE_RESULT specific;
} PARAMETER_TYPE;

typedef struct
{
	RTS_UI32 ulModuleType;
	RTS_UI32 ulInstance;
	MON_VALUE_RESULT specific;
} CONNECTOR_TYPE;

typedef struct
{
	union
	{
		RTS_UI16 usDummy;
		RTS_UI16 usForce;
	} flags;
	RTS_UI16 usAreaInstance;
	RTS_UI16 usAreaProperty;
	RTS_UI16 alignment;
	RTS_UI32 ulOffsetInstance;				
	RTS_UI32 ulOffsetGet;
	RTS_UI32 ulOffsetSet;
	RTS_UI16 usSize;
	MON_VALUE_RESULT specific;
} PROPERTYCALL_REF;


typedef struct
{
	union
	{
		RTS_UI16 usDummy;
		RTS_UI16 usForce;
	} flags;
	RTS_UI16 bInterface;
	RTS_UI16 usSize;
	RTS_UI16 alignment;
	RTS_UI32 ulOffsetGet;
	RTS_UI32 ulOffsetSet;
	MON_VALUE_RESULT specific;
} PROPERTYCALLDATA_REF;


typedef struct
{
	RTS_UI8* pbyAddressInstance;
	RTS_UI8* pbyAddressGet;
	RTS_UI8* pbyAddressSet;
	RTS_UI16 usSize;
	RTS_UI16 usAreaInstance;
	RTS_UI16 usAreaProperty;
	RTS_UI16 alignment;	
	RTS_UI32 ulOffsetInstance;				
	RTS_UI32 ulOffsetGet;
	RTS_UI32 ulOffsetSet;
	MON_VALUE_RESULT* pspecific;
} PROPERTYCALLINFO;

typedef struct
{
	RTS_UI32 uiAreaInstance;
	RTS_UI32 uiAreaOffset;
	RTS_UI16 usImplementationStyle;
	RTS_UI16 usParameterCount;
	RTS_UI32 uiResultOffset;
	RTS_UI16 usResultSize;
	RTS_UI16 usVarID;
	RTS_UI32 uiIecParameterSize;
	RTS_UI8* pbyIecParameter;
} FUNCTIONCALL_DATA;

typedef struct
{
	union
	{
		RTS_UI16 usDummy;
		RTS_UI16 usForce;
	} flags;
	RTS_UI16 usArea;
	RTS_UI32 ulOffset;
	RTS_UI16 usSize;
	MON_VALUE_RESULT specific;
} SIMPLEDATA_REF;

#ifdef RTS_SIXTEENBITBYTES
	#define sizeof_SIMPLEDATA_REF	sizeof(SIMPLEDATA_REF) * 2
#endif

typedef struct
{
	union
	{
		RTS_UI16 usDummy;
		RTS_UI16 usForce;
	} flags;
	RTS_UI16 usArea;
	RTS_UI32 ulOffset;
#ifdef RTS_SIXTEENBITBYTES
	RTS_UI16 usBitOffsetAndValue;
#else
	RTS_UI8 byBitOffset;
	RTS_UI8 byBitValue;
#endif
	RTS_UI16 usDummy;
} BITDATA_REF;

#ifdef RTS_SIXTEENBITBYTES
	#define sizeof_BITDATA_REF		sizeof(BITDATA_REF) * 2

	/*Get/Set values of BITDATA_REF*/
	#define GET_BITDATA_REF_OFFSET(pkg)	(unsigned char)(((BITDATA_REF*)pkg)->usBitOffsetAndValue & 0x00FF)
	#define GET_BITDATA_REF_VALUE(pkg)	(unsigned char)((((BITDATA_REF*)pkg)->usBitOffsetAndValue >> 8) & 0x00FF)
	#define SET_BITDATA_REF_OFFSET(pkg,nOffset)	((BITDATA_REF*)pkg)->usBitOffsetAndValue = ((unsigned short) nOffset & 0x00FF) | (((BITDATA_REF*)pkg)->usBitOffsetAndValue & 0xFF00)
	#define SET_BITDATA_REF_VALUE(pkg,nValue)	((BITDATA_REF*)pkg)->usBitOffsetAndValue = (((unsigned short) nValue << 8) & 0xFF00) | (((BITDATA_REF*)pkg)->usBitOffsetAndValue & 0x00FF)
#else
	#define GET_BITDATA_REF_OFFSET(pkg)	(unsigned char)(((BITDATA_REF*)pkg)->byBitOffset)
	#define GET_BITDATA_REF_VALUE(pkg)	(unsigned char)(((BITDATA_REF*)pkg)->byBitValue)
	#define SET_BITDATA_REF_OFFSET(pkg,nOffset)	((BITDATA_REF*)pkg)->byBitOffset = ((unsigned short) nOffset)
	#define SET_BITDATA_REF_VALUE(pkg,nValue)	((BITDATA_REF*)pkg)->byBitValue = ((unsigned short) nValue)
#endif


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 *	Routine to check, if a scheduler has the specified feature.
 * </description>
 * <param name="ulFeatures" type="IN">Feature flags, See corresponding category "Features".</param>
 * <result>ERR_OK if the flags are supported, an error code otherwise</result>
 */
RTS_RESULT CDECL MonitoringHasFeature(unsigned long ulFeatures);
typedef RTS_RESULT (CDECL * PFMONITORINGHASFEATURE) (unsigned long ulFeatures);
#if defined(CMPMONITOR_NOTIMPLEMENTED) || defined(MONITORINGHASFEATURE_NOTIMPLEMENTED)
	#define USE_MonitoringHasFeature
	#define EXT_MonitoringHasFeature
	#define GET_MonitoringHasFeature(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MonitoringHasFeature(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MonitoringHasFeature  FALSE
	#define EXP_MonitoringHasFeature  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MonitoringHasFeature
	#define EXT_MonitoringHasFeature
	#define GET_MonitoringHasFeature(fl)  CAL_CMGETAPI( "MonitoringHasFeature" ) 
	#define CAL_MonitoringHasFeature  MonitoringHasFeature
	#define CHK_MonitoringHasFeature  TRUE
	#define EXP_MonitoringHasFeature  CAL_CMEXPAPI( "MonitoringHasFeature" ) 
#elif defined(MIXED_LINK) && !defined(CMPMONITOR_EXTERNAL)
	#define USE_MonitoringHasFeature
	#define EXT_MonitoringHasFeature
	#define GET_MonitoringHasFeature(fl)  CAL_CMGETAPI( "MonitoringHasFeature" ) 
	#define CAL_MonitoringHasFeature  MonitoringHasFeature
	#define CHK_MonitoringHasFeature  TRUE
	#define EXP_MonitoringHasFeature  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MonitoringHasFeature", (RTS_UINTPTR)MonitoringHasFeature, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMonitorMonitoringHasFeature
	#define EXT_CmpMonitorMonitoringHasFeature
	#define GET_CmpMonitorMonitoringHasFeature  ERR_OK
	#define CAL_CmpMonitorMonitoringHasFeature pICmpMonitor->IMonitoringHasFeature
	#define CHK_CmpMonitorMonitoringHasFeature (pICmpMonitor != NULL)
	#define EXP_CmpMonitorMonitoringHasFeature  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MonitoringHasFeature
	#define EXT_MonitoringHasFeature
	#define GET_MonitoringHasFeature(fl)  CAL_CMGETAPI( "MonitoringHasFeature" ) 
	#define CAL_MonitoringHasFeature pICmpMonitor->IMonitoringHasFeature
	#define CHK_MonitoringHasFeature (pICmpMonitor != NULL)
	#define EXP_MonitoringHasFeature  CAL_CMEXPAPI( "MonitoringHasFeature" ) 
#else /* DYNAMIC_LINK */
	#define USE_MonitoringHasFeature  PFMONITORINGHASFEATURE pfMonitoringHasFeature;
	#define EXT_MonitoringHasFeature  extern PFMONITORINGHASFEATURE pfMonitoringHasFeature;
	#define GET_MonitoringHasFeature(fl)  s_pfCMGetAPI2( "MonitoringHasFeature", (RTS_VOID_FCTPTR *)&pfMonitoringHasFeature, (fl), 0, 0)
	#define CAL_MonitoringHasFeature  pfMonitoringHasFeature
	#define CHK_MonitoringHasFeature  (pfMonitoringHasFeature != NULL)
	#define EXP_MonitoringHasFeature  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MonitoringHasFeature", (RTS_UINTPTR)MonitoringHasFeature, 0, 0) 
#endif





/**
 * <description>
 *	Routine to read a value via a monitoring service.
 *  Note: this function is equivalent to calling MonitoringReadValue2 with bIec = 0.
 * </description>
 * <param name="pappl" type="IN">Pointer to application.</param>
 * <param name="preader" type="IN">the reader specifying the location of the value to monitor.</param>
 * <param name="pbyValue" type="IN">pointer to the destination address were the retrieved value is written.</param> 
 * <param name="usSize" type="IN">size of value to read.</param> 
 * <result>ERR_OK if the value could be retrieved successfully</result>
 */
RTS_RESULT CDECL MonitoringReadValue(APPLICATION* pappl, BINTAGREADER* preader, RTS_UI8* pbyValue, RTS_UI16 usSize);
typedef RTS_RESULT (CDECL * PFMONITORINGREADVALUE) (APPLICATION* pappl, BINTAGREADER* preader, RTS_UI8* pbyValue, RTS_UI16 usSize);
#if defined(CMPMONITOR_NOTIMPLEMENTED) || defined(MONITORINGREADVALUE_NOTIMPLEMENTED)
	#define USE_MonitoringReadValue
	#define EXT_MonitoringReadValue
	#define GET_MonitoringReadValue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MonitoringReadValue(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MonitoringReadValue  FALSE
	#define EXP_MonitoringReadValue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MonitoringReadValue
	#define EXT_MonitoringReadValue
	#define GET_MonitoringReadValue(fl)  CAL_CMGETAPI( "MonitoringReadValue" ) 
	#define CAL_MonitoringReadValue  MonitoringReadValue
	#define CHK_MonitoringReadValue  TRUE
	#define EXP_MonitoringReadValue  CAL_CMEXPAPI( "MonitoringReadValue" ) 
#elif defined(MIXED_LINK) && !defined(CMPMONITOR_EXTERNAL)
	#define USE_MonitoringReadValue
	#define EXT_MonitoringReadValue
	#define GET_MonitoringReadValue(fl)  CAL_CMGETAPI( "MonitoringReadValue" ) 
	#define CAL_MonitoringReadValue  MonitoringReadValue
	#define CHK_MonitoringReadValue  TRUE
	#define EXP_MonitoringReadValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MonitoringReadValue", (RTS_UINTPTR)MonitoringReadValue, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMonitorMonitoringReadValue
	#define EXT_CmpMonitorMonitoringReadValue
	#define GET_CmpMonitorMonitoringReadValue  ERR_OK
	#define CAL_CmpMonitorMonitoringReadValue pICmpMonitor->IMonitoringReadValue
	#define CHK_CmpMonitorMonitoringReadValue (pICmpMonitor != NULL)
	#define EXP_CmpMonitorMonitoringReadValue  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MonitoringReadValue
	#define EXT_MonitoringReadValue
	#define GET_MonitoringReadValue(fl)  CAL_CMGETAPI( "MonitoringReadValue" ) 
	#define CAL_MonitoringReadValue pICmpMonitor->IMonitoringReadValue
	#define CHK_MonitoringReadValue (pICmpMonitor != NULL)
	#define EXP_MonitoringReadValue  CAL_CMEXPAPI( "MonitoringReadValue" ) 
#else /* DYNAMIC_LINK */
	#define USE_MonitoringReadValue  PFMONITORINGREADVALUE pfMonitoringReadValue;
	#define EXT_MonitoringReadValue  extern PFMONITORINGREADVALUE pfMonitoringReadValue;
	#define GET_MonitoringReadValue(fl)  s_pfCMGetAPI2( "MonitoringReadValue", (RTS_VOID_FCTPTR *)&pfMonitoringReadValue, (fl), 0, 0)
	#define CAL_MonitoringReadValue  pfMonitoringReadValue
	#define CHK_MonitoringReadValue  (pfMonitoringReadValue != NULL)
	#define EXP_MonitoringReadValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MonitoringReadValue", (RTS_UINTPTR)MonitoringReadValue, 0, 0) 
#endif




/**
 * <description>
 *	Routine to read a value via a monitoring service.
 * </description>
 * <param name="pappl" type="IN">Pointer to application.</param>
 * <param name="preader" type="IN">the reader specifying the location of the value to monitor.</param>
 * <param name="pbyValue" type="IN">pointer to the destination address were the retrieved value is written.</param> 
 * <param name="usSize" type="IN">size of value to read.</param> 
 * <param name="bIec" type="IN">whether the call is done from an IEC task or not</param>
 * <result>ERR_OK if the value could be retrieved successfully</result>
 */
RTS_RESULT CDECL MonitoringReadValue2(APPLICATION* pappl, BINTAGREADER* preader, RTS_UI8* pbyValue, RTS_UI16 usSize, int bIec);
typedef RTS_RESULT (CDECL * PFMONITORINGREADVALUE2) (APPLICATION* pappl, BINTAGREADER* preader, RTS_UI8* pbyValue, RTS_UI16 usSize, int bIec);
#if defined(CMPMONITOR_NOTIMPLEMENTED) || defined(MONITORINGREADVALUE2_NOTIMPLEMENTED)
	#define USE_MonitoringReadValue2
	#define EXT_MonitoringReadValue2
	#define GET_MonitoringReadValue2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MonitoringReadValue2(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MonitoringReadValue2  FALSE
	#define EXP_MonitoringReadValue2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MonitoringReadValue2
	#define EXT_MonitoringReadValue2
	#define GET_MonitoringReadValue2(fl)  CAL_CMGETAPI( "MonitoringReadValue2" ) 
	#define CAL_MonitoringReadValue2  MonitoringReadValue2
	#define CHK_MonitoringReadValue2  TRUE
	#define EXP_MonitoringReadValue2  CAL_CMEXPAPI( "MonitoringReadValue2" ) 
#elif defined(MIXED_LINK) && !defined(CMPMONITOR_EXTERNAL)
	#define USE_MonitoringReadValue2
	#define EXT_MonitoringReadValue2
	#define GET_MonitoringReadValue2(fl)  CAL_CMGETAPI( "MonitoringReadValue2" ) 
	#define CAL_MonitoringReadValue2  MonitoringReadValue2
	#define CHK_MonitoringReadValue2  TRUE
	#define EXP_MonitoringReadValue2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MonitoringReadValue2", (RTS_UINTPTR)MonitoringReadValue2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMonitorMonitoringReadValue2
	#define EXT_CmpMonitorMonitoringReadValue2
	#define GET_CmpMonitorMonitoringReadValue2  ERR_OK
	#define CAL_CmpMonitorMonitoringReadValue2 pICmpMonitor->IMonitoringReadValue2
	#define CHK_CmpMonitorMonitoringReadValue2 (pICmpMonitor != NULL)
	#define EXP_CmpMonitorMonitoringReadValue2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MonitoringReadValue2
	#define EXT_MonitoringReadValue2
	#define GET_MonitoringReadValue2(fl)  CAL_CMGETAPI( "MonitoringReadValue2" ) 
	#define CAL_MonitoringReadValue2 pICmpMonitor->IMonitoringReadValue2
	#define CHK_MonitoringReadValue2 (pICmpMonitor != NULL)
	#define EXP_MonitoringReadValue2  CAL_CMEXPAPI( "MonitoringReadValue2" ) 
#else /* DYNAMIC_LINK */
	#define USE_MonitoringReadValue2  PFMONITORINGREADVALUE2 pfMonitoringReadValue2;
	#define EXT_MonitoringReadValue2  extern PFMONITORINGREADVALUE2 pfMonitoringReadValue2;
	#define GET_MonitoringReadValue2(fl)  s_pfCMGetAPI2( "MonitoringReadValue2", (RTS_VOID_FCTPTR *)&pfMonitoringReadValue2, (fl), 0, 0)
	#define CAL_MonitoringReadValue2  pfMonitoringReadValue2
	#define CHK_MonitoringReadValue2  (pfMonitoringReadValue2 != NULL)
	#define EXP_MonitoringReadValue2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MonitoringReadValue2", (RTS_UINTPTR)MonitoringReadValue2, 0, 0) 
#endif




/**
 * <description>
 *	Routine to writa a value via a monitoring service.
 *  Note: this function is equivalent to calling MonitoringWriteValue2 with bIec = 0.
 * </description>
 * <param name="pappl" type="IN">Pointer to application.</param>
 * <param name="preader" type="IN">the reader specifying the location of the value to write.</param>
 * <param name="pbyValue" type="IN">pointer to the source address of the value to write.</param> 
 * <param name="usSize" type="IN">size of value to read.</param>
 * <result>ERR_OK if the value could be written successfully</result>
 */
RTS_RESULT CDECL MonitoringWriteValue(APPLICATION* pappl, BINTAGREADER* preader, RTS_UI8* pbyValue, RTS_UI16 usSize);
typedef RTS_RESULT (CDECL * PFMONITORINGWRITEVALUE) (APPLICATION* pappl, BINTAGREADER* preader, RTS_UI8* pbyValue, RTS_UI16 usSize);
#if defined(CMPMONITOR_NOTIMPLEMENTED) || defined(MONITORINGWRITEVALUE_NOTIMPLEMENTED)
	#define USE_MonitoringWriteValue
	#define EXT_MonitoringWriteValue
	#define GET_MonitoringWriteValue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MonitoringWriteValue(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MonitoringWriteValue  FALSE
	#define EXP_MonitoringWriteValue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MonitoringWriteValue
	#define EXT_MonitoringWriteValue
	#define GET_MonitoringWriteValue(fl)  CAL_CMGETAPI( "MonitoringWriteValue" ) 
	#define CAL_MonitoringWriteValue  MonitoringWriteValue
	#define CHK_MonitoringWriteValue  TRUE
	#define EXP_MonitoringWriteValue  CAL_CMEXPAPI( "MonitoringWriteValue" ) 
#elif defined(MIXED_LINK) && !defined(CMPMONITOR_EXTERNAL)
	#define USE_MonitoringWriteValue
	#define EXT_MonitoringWriteValue
	#define GET_MonitoringWriteValue(fl)  CAL_CMGETAPI( "MonitoringWriteValue" ) 
	#define CAL_MonitoringWriteValue  MonitoringWriteValue
	#define CHK_MonitoringWriteValue  TRUE
	#define EXP_MonitoringWriteValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MonitoringWriteValue", (RTS_UINTPTR)MonitoringWriteValue, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMonitorMonitoringWriteValue
	#define EXT_CmpMonitorMonitoringWriteValue
	#define GET_CmpMonitorMonitoringWriteValue  ERR_OK
	#define CAL_CmpMonitorMonitoringWriteValue pICmpMonitor->IMonitoringWriteValue
	#define CHK_CmpMonitorMonitoringWriteValue (pICmpMonitor != NULL)
	#define EXP_CmpMonitorMonitoringWriteValue  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MonitoringWriteValue
	#define EXT_MonitoringWriteValue
	#define GET_MonitoringWriteValue(fl)  CAL_CMGETAPI( "MonitoringWriteValue" ) 
	#define CAL_MonitoringWriteValue pICmpMonitor->IMonitoringWriteValue
	#define CHK_MonitoringWriteValue (pICmpMonitor != NULL)
	#define EXP_MonitoringWriteValue  CAL_CMEXPAPI( "MonitoringWriteValue" ) 
#else /* DYNAMIC_LINK */
	#define USE_MonitoringWriteValue  PFMONITORINGWRITEVALUE pfMonitoringWriteValue;
	#define EXT_MonitoringWriteValue  extern PFMONITORINGWRITEVALUE pfMonitoringWriteValue;
	#define GET_MonitoringWriteValue(fl)  s_pfCMGetAPI2( "MonitoringWriteValue", (RTS_VOID_FCTPTR *)&pfMonitoringWriteValue, (fl), 0, 0)
	#define CAL_MonitoringWriteValue  pfMonitoringWriteValue
	#define CHK_MonitoringWriteValue  (pfMonitoringWriteValue != NULL)
	#define EXP_MonitoringWriteValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MonitoringWriteValue", (RTS_UINTPTR)MonitoringWriteValue, 0, 0) 
#endif




/**
 * <description>
 *	Routine to writa a value via a monitoring service.
 * </description>
 * <param name="pappl" type="IN">Pointer to application.</param>
 * <param name="preader" type="IN">the reader specifying the location of the value to write.</param>
 * <param name="pbyValue" type="IN">pointer to the source address of the value to write.</param> 
 * <param name="usSize" type="IN">size of value to read.</param>
 * <param name="bIec" type="IN">whether the call is done from an IEC task or not</param>
 * <result>ERR_OK if the value could be written successfully</result>
 */
RTS_RESULT CDECL MonitoringWriteValue2(APPLICATION* pappl, BINTAGREADER* preader, RTS_UI8* pbyValue, RTS_UI16 usSize, int bIec);
typedef RTS_RESULT (CDECL * PFMONITORINGWRITEVALUE2) (APPLICATION* pappl, BINTAGREADER* preader, RTS_UI8* pbyValue, RTS_UI16 usSize, int bIec);
#if defined(CMPMONITOR_NOTIMPLEMENTED) || defined(MONITORINGWRITEVALUE2_NOTIMPLEMENTED)
	#define USE_MonitoringWriteValue2
	#define EXT_MonitoringWriteValue2
	#define GET_MonitoringWriteValue2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_MonitoringWriteValue2(p0,p1,p2,p3,p4)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_MonitoringWriteValue2  FALSE
	#define EXP_MonitoringWriteValue2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_MonitoringWriteValue2
	#define EXT_MonitoringWriteValue2
	#define GET_MonitoringWriteValue2(fl)  CAL_CMGETAPI( "MonitoringWriteValue2" ) 
	#define CAL_MonitoringWriteValue2  MonitoringWriteValue2
	#define CHK_MonitoringWriteValue2  TRUE
	#define EXP_MonitoringWriteValue2  CAL_CMEXPAPI( "MonitoringWriteValue2" ) 
#elif defined(MIXED_LINK) && !defined(CMPMONITOR_EXTERNAL)
	#define USE_MonitoringWriteValue2
	#define EXT_MonitoringWriteValue2
	#define GET_MonitoringWriteValue2(fl)  CAL_CMGETAPI( "MonitoringWriteValue2" ) 
	#define CAL_MonitoringWriteValue2  MonitoringWriteValue2
	#define CHK_MonitoringWriteValue2  TRUE
	#define EXP_MonitoringWriteValue2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MonitoringWriteValue2", (RTS_UINTPTR)MonitoringWriteValue2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpMonitorMonitoringWriteValue2
	#define EXT_CmpMonitorMonitoringWriteValue2
	#define GET_CmpMonitorMonitoringWriteValue2  ERR_OK
	#define CAL_CmpMonitorMonitoringWriteValue2 pICmpMonitor->IMonitoringWriteValue2
	#define CHK_CmpMonitorMonitoringWriteValue2 (pICmpMonitor != NULL)
	#define EXP_CmpMonitorMonitoringWriteValue2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_MonitoringWriteValue2
	#define EXT_MonitoringWriteValue2
	#define GET_MonitoringWriteValue2(fl)  CAL_CMGETAPI( "MonitoringWriteValue2" ) 
	#define CAL_MonitoringWriteValue2 pICmpMonitor->IMonitoringWriteValue2
	#define CHK_MonitoringWriteValue2 (pICmpMonitor != NULL)
	#define EXP_MonitoringWriteValue2  CAL_CMEXPAPI( "MonitoringWriteValue2" ) 
#else /* DYNAMIC_LINK */
	#define USE_MonitoringWriteValue2  PFMONITORINGWRITEVALUE2 pfMonitoringWriteValue2;
	#define EXT_MonitoringWriteValue2  extern PFMONITORINGWRITEVALUE2 pfMonitoringWriteValue2;
	#define GET_MonitoringWriteValue2(fl)  s_pfCMGetAPI2( "MonitoringWriteValue2", (RTS_VOID_FCTPTR *)&pfMonitoringWriteValue2, (fl), 0, 0)
	#define CAL_MonitoringWriteValue2  pfMonitoringWriteValue2
	#define CHK_MonitoringWriteValue2  (pfMonitoringWriteValue2 != NULL)
	#define EXP_MonitoringWriteValue2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"MonitoringWriteValue2", (RTS_UINTPTR)MonitoringWriteValue2, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFMONITORINGHASFEATURE IMonitoringHasFeature;
 	PFMONITORINGREADVALUE IMonitoringReadValue;
 	PFMONITORINGREADVALUE2 IMonitoringReadValue2;
 	PFMONITORINGWRITEVALUE IMonitoringWriteValue;
 	PFMONITORINGWRITEVALUE2 IMonitoringWriteValue2;
 } ICmpMonitor_C;

#ifdef CPLUSPLUS
class ICmpMonitor : public IBase
{
	public:
		virtual RTS_RESULT CDECL IMonitoringHasFeature(unsigned long ulFeatures) =0;
		virtual RTS_RESULT CDECL IMonitoringReadValue(APPLICATION* pappl, BINTAGREADER* preader, RTS_UI8* pbyValue, RTS_UI16 usSize) =0;
		virtual RTS_RESULT CDECL IMonitoringReadValue2(APPLICATION* pappl, BINTAGREADER* preader, RTS_UI8* pbyValue, RTS_UI16 usSize, int bIec) =0;
		virtual RTS_RESULT CDECL IMonitoringWriteValue(APPLICATION* pappl, BINTAGREADER* preader, RTS_UI8* pbyValue, RTS_UI16 usSize) =0;
		virtual RTS_RESULT CDECL IMonitoringWriteValue2(APPLICATION* pappl, BINTAGREADER* preader, RTS_UI8* pbyValue, RTS_UI16 usSize, int bIec) =0;
};
	#ifndef ITF_CmpMonitor
		#define ITF_CmpMonitor static ICmpMonitor *pICmpMonitor = NULL;
	#endif
	#define EXTITF_CmpMonitor
#else	/*CPLUSPLUS*/
	typedef ICmpMonitor_C		ICmpMonitor;
	#ifndef ITF_CmpMonitor
		#define ITF_CmpMonitor
	#endif
	#define EXTITF_CmpMonitor
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPMONITORITF_H_*/
