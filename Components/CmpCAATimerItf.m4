/**
 * <interfacename>CmpCAATimer</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`CmpCAATimer')

#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAATimer.h"

#ifdef __cplusplus
extern "C" {
#endif

DEF_ITF_API(`CAA_HANDLE',`CDECL',`TMR_CreateH',`(CAA_BOOL xCyclic, CAA_COUNT ctInterval, RTS_IEC_XWORD dwParam, CAA_BOOL xHardware, CAA_ENUM eTimer, CAA_ERROR *peError)')

DEF_ITF_API(`CAA_HANDLE',`CDECL',`TMR_CreateP',`(CAA_BOOL xCyclic, CAA_COUNT ctInterval, RTS_IEC_XWORD dwParam, CAA_BOOL xHardware, CAA_ENUM eTimer, CAA_SIZE szMemSize, CAA_PVOID pMemory, CAA_ERROR *peError)')

DEF_ITF_API(`CAA_SIZE',`CDECL',`TMR_GetSize',`(CAA_BOOL xCyclic, CAA_COUNT ctInterval,	RTS_IEC_XWORD dwParam, CAA_BOOL xHardware)')

DEF_ITF_API(`CAA_ERROR',`CDECL',`TMR_Start',`(CAA_HANDLE hTimer)')

DEF_ITF_API(`CAA_ERROR',`CDECL',`TMR_Stop',`(CAA_HANDLE hTimer)')

DEF_ITF_API(`CAA_ERROR',`CDECL',`TMR_Delete',`(CAA_HANDLE hTimer)')

DEF_ITF_API(`CAA_ERROR',`CDECL',`TMR_GetQuality',`(CAA_HANDLE hTimer, TMR_QUALITY *pqTimer)')

DEF_ITF_API(`RTS_IEC_XWORD',`CDECL',`TMR_GetProperty',`(CAA_WORD wProperty)')

DEF_ITF_API(`CAA_WORD',`CDECL',`TMR_GetSupplierVersion',`(CAA_BOOL xDummy)')

#ifdef __cplusplus
}
#endif


/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>tmr_createh</description>
 */
typedef struct tagtmr_createh_struct
{
	CAA_BOOL xCyclic;					/* VAR_INPUT */	/* FALSE: non cyclic send an event, TRUE: cyclic send an event */
	CAA_COUNT ctInterval;				/* VAR_INPUT */	/* timer interval in nanoseconds */
	RTS_IEC_XWORD dwParam;				/* VAR_INPUT */	/* parameter to transfer to callback function */
	CAA_BOOL xHardware;					/* VAR_INPUT */	/* TRUE: Hardwaretimer; FALSE: Softwaretimer */
	CAA_ENUM eTimer;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE TMR_CreateH;				/* VAR_OUTPUT */	/* hTimer */
} tmr_createh_struct;

DEF_API(`void',`CDECL',`tmr_createh',`(tmr_createh_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCD6CF9CC),0x03050500)

/**
 * <description>tmr_createp</description>
 */
typedef struct tagtmr_createp_struct
{
	CAA_BOOL xCyclic;					/* VAR_INPUT */	/* FALSE: non cyclic send an event, TRUE: cyclic send an event */
	CAA_COUNT ctInterval;				/* VAR_INPUT */	/* timer interval in nanoseconds */
	RTS_IEC_XWORD dwParam;				/* VAR_INPUT */	/* parameter to transfer to callback function */
	CAA_BOOL xHardware;					/* VAR_INPUT */	/* TRUE: Hardwaretimer; FALSE: Softwaretimer */
	CAA_ENUM eTimer;					/* VAR_INPUT */	
	CAA_SIZE szMemSize;					/* VAR_INPUT */	
	CAA_PVOID pMemory;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE TMR_CreateP;				/* VAR_OUTPUT */	/* hTimer */
} tmr_createp_struct;

DEF_API(`void',`CDECL',`tmr_createp',`(tmr_createp_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x82CE337D),0x03050500)

/**
 * <description>tmr_delete</description>
 */
typedef struct tagtmr_delete_struct
{
	CAA_HANDLE hTimer;					/* VAR_INPUT */	/* timer handle */
	CAA_ERROR TMR_Delete;				/* VAR_OUTPUT */	
} tmr_delete_struct;

DEF_API(`void',`CDECL',`tmr_delete',`(tmr_delete_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xE6D63FAA),0x03050500)

/**
 * <description>tmr_getproperty</description>
 */
typedef struct tagtmr_getproperty_struct
{
	RTS_IEC_WORD wProperty;				/* VAR_INPUT */	/* property number */
	RTS_IEC_XWORD TMR_GetProperty;		/* VAR_OUTPUT */	
} tmr_getproperty_struct;

DEF_API(`void',`CDECL',`tmr_getproperty',`(tmr_getproperty_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x57855015),0x03050500)

/**
 * <description>tmr_getquality</description>
 */
typedef struct tagtmr_getquality_struct
{
	CAA_HANDLE hTimer;					/* VAR_INPUT */	/* timer handle */
	TMR_QUALITY *pqTimer;				/* VAR_INPUT */	/* pointer to qualtiy structure, return the actual values in this structure */
	CAA_ERROR TMR_GetQuality;			/* VAR_OUTPUT */	
} tmr_getquality_struct;

DEF_API(`void',`CDECL',`tmr_getquality',`(tmr_getquality_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x5BB85F5E),0x03050500)

/**
 * <description>tmr_getsize</description>
 */
typedef struct tagtmr_getsize_struct
{
	CAA_BOOL xCyclic;					/* VAR_INPUT */	/* FALSE: non cyclic send an event, TRUE: cyclic send an event */
	CAA_COUNT ctInterval;				/* VAR_INPUT */	/* timer interval in nanoseconds */
	RTS_IEC_XWORD dwParam;				/* VAR_INPUT */	/* parameter to transfer to callback function */
	CAA_BOOL xHardware;					/* VAR_INPUT */	/* TRUE: Hardwaretimer; FALSE: Softwaretimer */
	CAA_SIZE TMR_GetSize;				/* VAR_OUTPUT */	
} tmr_getsize_struct;

DEF_API(`void',`CDECL',`tmr_getsize',`(tmr_getsize_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4819FDFC),0x03050500)

/**
 * <description>tmr_getsupplierversion</description>
 */
typedef struct tagtmr_getsupplierversion_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	RTS_IEC_WORD TMR_GetSupplierVersion;	/* VAR_OUTPUT */	
} tmr_getsupplierversion_struct;

DEF_API(`void',`CDECL',`tmr_getsupplierversion',`(tmr_getsupplierversion_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x353E7392),0x03050500)

/**
 * <description>tmr_start</description>
 */
typedef struct tagtmr_start_struct
{
	CAA_HANDLE hTimer;					/* VAR_INPUT */	/* timer handle */
	CAA_ERROR TMR_Start;				/* VAR_OUTPUT */	
} tmr_start_struct;

DEF_API(`void',`CDECL',`tmr_start',`(tmr_start_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x31717A79),0x03050500)

/**
 * <description>tmr_stop</description>
 */
typedef struct tagtmr_stop_struct
{
	CAA_HANDLE hTimer;					/* VAR_INPUT */	/* timer handle */
	CAA_ERROR TMR_Stop;					/* VAR_OUTPUT */	
} tmr_stop_struct;

DEF_API(`void',`CDECL',`tmr_stop',`(tmr_stop_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x816F6062),0x03050500)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

