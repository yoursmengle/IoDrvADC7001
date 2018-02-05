/**
 * <interfacename>CmpCAATick</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`CmpCAATick')

#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAATick.h"

#ifdef __cplusplus
extern "C" {
#endif

DEF_ITF_API(`CAA_TICK',`CDECL',`TICKS_GetTick',`(CAA_BOOL xDummy)')
DEF_ITF_API(`RTS_IEC_XWORD',`CDECL',`TICKS_GetProperty',`(unsigned short usProperty)')
DEF_ITF_API(`unsigned short',`CDECL',`TICKS_GetSupplierVersion',`(CAA_BOOL xDummy)')

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>ticks_getproperty</description>
 */
typedef struct tagticks_getproperty_struct
{
	RTS_IEC_WORD wProperty;				/* VAR_INPUT */	
	RTS_IEC_XWORD TICKS_GetProperty;	/* VAR_OUTPUT */	
} ticks_getproperty_struct;

DEF_API(`void',`CDECL',`ticks_getproperty',`(ticks_getproperty_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x2BC58761),0x03050500)

/**
 * <description>ticks_getsupplierversion</description>
 */
typedef struct tagticks_getsupplierversion_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	RTS_IEC_WORD TICKS_GetSupplierVersion;	/* VAR_OUTPUT */	
} ticks_getsupplierversion_struct;

DEF_API(`void',`CDECL',`ticks_getsupplierversion',`(ticks_getsupplierversion_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF305F08E),0x03050500)

/**
 * <description>ticks_gettick</description>
 */
typedef struct tagticks_gettick_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	CAA_TICK TICKS_GetTick;				/* VAR_OUTPUT */	
} ticks_gettick_struct;

DEF_API(`void',`CDECL',`ticks_gettick',`(ticks_gettick_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xE34E0CC2),0x03050500)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/
