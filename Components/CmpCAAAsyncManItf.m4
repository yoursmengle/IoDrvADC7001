/**
 * <interfacename>CmpCAAAsyncMan</interfacename>
 * <description> 
 *	<p>CAA Technik Work Group: Asnyc Manager.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpCAAAsyncMan')

/**
 * <description>
 *   The CAA Asycn Manager provides an asynchronous job handling.
 *   Please see the CAA documentation CAA_AsyncManager.pdf for any further
 *   information.
 * </description>
 */    

#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAAAsyncMan.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Interface functions of CAA Async Man*/
DEF_ITF_API(`CAA_HANDLE',`CDECL',`ASM_JobOpenEx',`(CAA_UDINT udiId, CAA_PVOID pParams, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`ASM_JobOpen',`(RTS_IEC_UDINT udiId, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`ASM_JobClose',`(CAA_HANDLE hJob)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`ASM_JobExecute',`(CAA_HANDLE hJob)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`ASM_JobReset',`(CAA_HANDLE hJob)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`ASM_JobAbort',`(CAA_HANDLE hJob)')
DEF_ITF_API(`CAA_PVOID',`CDECL',`ASM_JobGetParams',`(CAA_HANDLE hJob, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`ASM_JobGetState',`(CAA_HANDLE hJob, ASM_STATE* pstateJob)')
DEF_ITF_API(`RTS_IEC_UDINT',`CDECL',`ASM_JobGetId',`(CAA_HANDLE hJob, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`ASM_WorkerRegister',`(RTS_IEC_UDINT udiId, ASM_IWORKER* pwiItf)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`ASM_WorkerRegister2',`(RTS_IEC_UDINT udiId, ASM_IWORKER2* pwiItf2)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`ASM_WorkerUnregister',`(RTS_IEC_UDINT udiId)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`ASM_JobSetState',`(CAA_HANDLE hJob, ASM_STATE stateJob)')
DEF_ITF_API(`unsigned short',`CDECL',`ASM_GetSupplierVersion',`(CAA_BOOL xDummy)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`ASM_JobExecQueue',`(void)')

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>asm_jobabort</description>
 */
typedef struct tagasm_jobabort_struct
{
	CAA_HANDLE hJob;					/* VAR_INPUT */	/* Handle of a Job */
	CAA_ERROR ASM_JobAbort;				/* VAR_OUTPUT */	
} asm_jobabort_struct;

DEF_API(`void',`CDECL',`asm_jobabort',`(asm_jobabort_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x5050C65B),0x03050528)

/**
 * <description>asm_jobclose</description>
 */
typedef struct tagasm_jobclose_struct
{
	CAA_HANDLE hJob;					/* VAR_INPUT */	/* Handle of a Job */
	CAA_ERROR ASM_JobClose;				/* VAR_OUTPUT */	
} asm_jobclose_struct;

DEF_API(`void',`CDECL',`asm_jobclose',`(asm_jobclose_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xE8BCA52A),0x03050528)

/**
 * <description>asm_jobexecute</description>
 */
typedef struct tagasm_jobexecute_struct
{
	CAA_HANDLE hJob;					/* VAR_INPUT */	/* Handle of a Job */
	CAA_ERROR ASM_JobExecute;			/* VAR_OUTPUT */	
} asm_jobexecute_struct;

DEF_API(`void',`CDECL',`asm_jobexecute',`(asm_jobexecute_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x35D667D5),0x03050528)

/**
 * <description>asm_jobgetid</description>
 */
typedef struct tagasm_jobgetid_struct
{
	CAA_HANDLE hJob;					/* VAR_INPUT */	/* Handle of a Job */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	RTS_IEC_UDINT ASM_JobGetId;			/* VAR_OUTPUT */	
} asm_jobgetid_struct;

DEF_API(`void',`CDECL',`asm_jobgetid',`(asm_jobgetid_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4C69332D),0x03050528)

/**
 * <description>asm_jobgetparams</description>
 */
typedef struct tagasm_jobgetparams_struct
{
	CAA_HANDLE hJob;					/* VAR_INPUT */	/* Handle of a Job */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_PVOID ASM_JobGetParams;			/* VAR_OUTPUT */	
} asm_jobgetparams_struct;

DEF_API(`void',`CDECL',`asm_jobgetparams',`(asm_jobgetparams_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x77004163),0x03050528)

/**
 * <description>asm_jobgetstate</description>
 */
typedef struct tagasm_jobgetstate_struct
{
	CAA_HANDLE hJob;					/* VAR_INPUT */	/* Handle of a Job */
	ASM_STATE *pStateJob;				/* VAR_INPUT */	
	CAA_ERROR ASM_JobGetState;			/* VAR_OUTPUT */	
} asm_jobgetstate_struct;

DEF_API(`void',`CDECL',`asm_jobgetstate',`(asm_jobgetstate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xBA2A911E),0x03050528)

/**
 * <description>asm_jobopen</description>
 */
typedef struct tagasm_jobopen_struct
{
	RTS_IEC_UDINT udiId;				/* VAR_INPUT */	/* Unique Identifier, see Praefix.pdf */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE ASM_JobOpen;				/* VAR_OUTPUT */	
} asm_jobopen_struct;

DEF_API(`void',`CDECL',`asm_jobopen',`(asm_jobopen_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0D083D90),0x03050528)

/**
 * <description>asm_jobopenex</description>
 */
typedef struct tagasm_jobopenex_struct
{
	RTS_IEC_UDINT udiId;				/* VAR_INPUT */	/* Unique Identifier, see Praefix.pdf */
	CAA_PVOID pParams;					/* VAR_INPUT */	/* Pointer to Parameters */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE ASM_JobOpenEx;			/* VAR_OUTPUT */	
} asm_jobopenex_struct;

DEF_API(`void',`CDECL',`asm_jobopenex',`(asm_jobopenex_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1B44DB2C),0x03050528)

/**
 * <description>asm_jobreset</description>
 */
typedef struct tagasm_jobreset_struct
{
	CAA_HANDLE hJob;					/* VAR_INPUT */	/* Handle of a Job */
	CAA_ERROR ASM_JobReset;				/* VAR_OUTPUT */	
} asm_jobreset_struct;

DEF_API(`void',`CDECL',`asm_jobreset',`(asm_jobreset_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xE9F7DD31),0x03050528)

/**
 * Implementation Note: This function should be called only from a Worker
 */
typedef struct tagasm_jobsetstate_struct
{
	CAA_HANDLE hJob;					/* VAR_INPUT */	/* Handle of a Job */
	ASM_STATE StateJob;					/* VAR_INPUT */	
	CAA_ERROR ASM_JobSetState;			/* VAR_OUTPUT */	
} asm_jobsetstate_struct;

DEF_API(`void',`CDECL',`asm_jobsetstate',`(asm_jobsetstate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x5F95B914),0x03050528)

/**
 * Implementation Note: A Worker must be implemented in C or in C++, IEC is not supported
 */
typedef struct tagasm_workerregister_struct
{
	RTS_IEC_UDINT udiId;				/* VAR_INPUT */	/* Unique Identifier, see Praefix.pdf */
	ASM_IWORKER *pwItf;					/* VAR_INPUT */	/* Pointer to Worker Interface */
	CAA_ERROR ASM_WorkerRegister;		/* VAR_OUTPUT */	
} asm_workerregister_struct;

DEF_API(`void',`CDECL',`asm_workerregister',`(asm_workerregister_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x75B6C708),0x03050528)

/**
 * Implementation Note: A Worker must be implemented in C or in C++, IEC is not supported
 */
typedef struct tagasm_workerunregister_struct
{
	RTS_IEC_UDINT udiId;				/* VAR_INPUT */	/* Unique Identifier, see Praefix.pdf */
	CAA_ERROR ASM_WorkerUnregister;		/* VAR_OUTPUT */	
} asm_workerunregister_struct;

DEF_API(`void',`CDECL',`asm_workerunregister',`(asm_workerunregister_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4ECC5BAB),0x03050528)

/**
 * <description>asm_getsupplierversion</description>
 */
typedef struct tagasm_getsupplierversion_struct
{
	RTS_IEC_WORD ASM_GetSupplierVersion;	/* VAR_OUTPUT */	
} asm_getsupplierversion_struct;

DEF_API(`void',`CDECL',`asm_getsupplierversion',`(asm_getsupplierversion_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xAC164AE9),0x03050528)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/
