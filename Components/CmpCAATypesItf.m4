SET_INTERFACE_NAME(`CmpCAATypes')

#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns the actual release and implementation version of the library 
 */
typedef struct tagcaa_getsupplierversion_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	/* Backward compatibility */
	RTS_IEC_WORD CAA_GetSupplierVersion;	/* VAR_OUTPUT */	
} caa_getsupplierversion_struct;

DEF_API(`void',`CDECL',`caa_getsupplierversion',`(caa_getsupplierversion_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0CB79C27),0x03050500)

/**
 * <description>caa_resmanincharge</description>
 */
typedef struct tagcaa_resmanincharge_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	CAA_BOOL CAA_ResManInCharge;		/* VAR_OUTPUT */	
} caa_resmanincharge_struct;

DEF_API(`void',`CDECL',`caa_resmanincharge',`(caa_resmanincharge_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x152491C7),0x03050500)

/**
 * <description>caa_tasklock</description>
 */
typedef struct tagcaa_tasklock_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	CAA_ERROR CAA_TaskLock;				/* VAR_OUTPUT */	
} caa_tasklock_struct;

DEF_API(`void',`CDECL',`caa_tasklock',`(caa_tasklock_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x7366A49D),0x03050500)

/**
 * <description>caa_taskunlock</description>
 */
typedef struct tagcaa_taskunlock_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	CAA_ERROR CAA_TaskUnlock;			/* VAR_OUTPUT */	
} caa_taskunlock_struct;

DEF_API(`void',`CDECL',`caa_taskunlock',`(caa_taskunlock_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x8ABBECC7),0x03050500)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

DEF_ITF_API(`unsigned short',`CDECL',`CAA_GetSupplierVersion',`(char xDummy)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`CAA_Dummy',`(CAA_HANDLE hHandle, CAA_ERROR* pError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`CAA_Dummy2',`(void)')

#ifdef __cplusplus
}
#endif
