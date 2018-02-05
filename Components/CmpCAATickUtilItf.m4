/**
 * <interfacename>CmpCAATickUtil</interfacename>
 * <description></description> 
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`CmpCAATickUtil')

#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAATickUtil.h"

#ifdef __cplusplus
extern "C" {
#endif

DEF_ITF_API(`CAA_TICK',`CDECL',`TICKU_ConvertNSecToTick',`(RTS_UI32 ulNSeconds)')
DEF_ITF_API(`RTS_UI32',`CDECL',`TICKU_ConvertTickToNSec',`(CAA_TICK tkTick)')
DEF_ITF_API(`RTS_UI32',`CDECL',`TICKU_ConvertTickToUSec',`(CAA_TICK tkTick)')
DEF_ITF_API(`CAA_TICK',`CDECL',`TICKU_ConvertUSecToTick',`(RTS_UI32 ulUSeconds)')
DEF_ITF_API(`RTS_UI32',`CDECL',`TICKU_GetElapsedTimeInNSec',`(CAA_TICK tkStart)')
DEF_ITF_API(`RTS_UI32',`CDECL',`TICKU_GetElapsedTimeInUSec',`(CAA_TICK tkStart)')
DEF_ITF_API(`unsigned short',`CDECL',`TICKU_GetSupplierVersion',`(CAA_BOOL xDummy)')

#ifdef __cplusplus
}
#endif


/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>ticku_convertnsectotick</description>
 */
typedef struct tagticku_convertnsectotick_struct
{
	RTS_IEC_UDINT udiNSeconds;			/* VAR_INPUT */	
	CAA_TICK TICKU_ConvertNSecToTick;	/* VAR_OUTPUT */	
} ticku_convertnsectotick_struct;

DEF_API(`void',`CDECL',`ticku_convertnsectotick',`(ticku_convertnsectotick_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCE69B11B),0x03050500)

/**
 * <description>ticku_convertticktonsec</description>
 */
typedef struct tagticku_convertticktonsec_struct
{
	CAA_TICK tkTick;					/* VAR_INPUT */	
	RTS_IEC_UDINT TICKU_ConvertTickToNSec;	/* VAR_OUTPUT */	
} ticku_convertticktonsec_struct;

DEF_API(`void',`CDECL',`ticku_convertticktonsec',`(ticku_convertticktonsec_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1163A81F),0x03050500)

/**
 * <description>ticku_convertticktousec</description>
 */
typedef struct tagticku_convertticktousec_struct
{
	CAA_TICK tkTick;					/* VAR_INPUT */	
	RTS_IEC_UDINT TICKU_ConvertTickToUSec;	/* VAR_OUTPUT */	
} ticku_convertticktousec_struct;

DEF_API(`void',`CDECL',`ticku_convertticktousec',`(ticku_convertticktousec_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x89370F4E),0x03050500)

/**
 * <description>ticku_convertusectotick</description>
 */
typedef struct tagticku_convertusectotick_struct
{
	RTS_IEC_UDINT udiUSeconds;			/* VAR_INPUT */	
	CAA_TICK TICKU_ConvertUSecToTick;	/* VAR_OUTPUT */	
} ticku_convertusectotick_struct;

DEF_API(`void',`CDECL',`ticku_convertusectotick',`(ticku_convertusectotick_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xEF322DA4),0x03050500)

/**
 * <description>ticku_getelapsedtimeinnsec</description>
 */
typedef struct tagticku_getelapsedtimeinnsec_struct
{
	CAA_TICK tkStart;					/* VAR_INPUT */	
	RTS_IEC_UDINT TICKU_GetElapsedTimeInNSec;	/* VAR_OUTPUT */	
} ticku_getelapsedtimeinnsec_struct;

DEF_API(`void',`CDECL',`ticku_getelapsedtimeinnsec',`(ticku_getelapsedtimeinnsec_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF18913FC),0x03050500)

/**
 * <description>ticku_getelapsedtimeinusec</description>
 */
typedef struct tagticku_getelapsedtimeinusec_struct
{
	CAA_TICK tkStart;					/* VAR_INPUT */	
	RTS_IEC_UDINT TICKU_GetElapsedTimeInUSec;	/* VAR_OUTPUT */	
} ticku_getelapsedtimeinusec_struct;

DEF_API(`void',`CDECL',`ticku_getelapsedtimeinusec',`(ticku_getelapsedtimeinusec_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC903347A),0x03050500)

/**
 * <description>ticku_getsupplierversion</description>
 */
typedef struct tagticku_getsupplierversion_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	RTS_IEC_WORD TICKU_GetSupplierVersion;	/* VAR_OUTPUT */	
} ticku_getsupplierversion_struct;

DEF_API(`void',`CDECL',`ticku_getsupplierversion',`(ticku_getsupplierversion_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA4D2E65F),0x03050500)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/
