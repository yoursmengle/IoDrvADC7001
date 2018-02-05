SET_INTERFACE_NAME(`CmpBelb')

#include "CmpItf.h"

/* Hook definitions (0..10000 reserved for core components) */

#define CH_USER_1						10000
/*	First user hook
	ulParam1: Not used
	ulParam2: Not used
*/

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>startwatchdog</description>
 */
typedef struct tagstartwatchdog_struct
{
	RTS_IEC_DWORD StartWatchdog;		/* VAR_OUTPUT */
} startwatchdog_struct;

DEF_API(`void',`CDECL',`startwatchdog',`(startwatchdog_struct *p)',1,0x50E033B9,0x0000)

/**
 * <description>stopwatchdog</description>
 */
typedef struct tagstopwatchdog_struct
{
	RTS_IEC_DWORD StopWatchdog;			/* VAR_OUTPUT */
} stopwatchdog_struct;

DEF_API(`void',`CDECL',`stopwatchdog',`(stopwatchdog_struct *p)',1,0x2B1E3F4A,0x0000)

/**
 * <description>kickwatchdog</description>
 */
typedef struct tagkickwatchdog_struct
{
	RTS_IEC_DWORD KickWatchdog;			/* VAR_OUTPUT */
} kickwatchdog_struct;

DEF_API(`void',`CDECL',`kickwatchdog',`(kickwatchdog_struct *p)',1,0x12D360F2,0x0000)

/*From here functions called by other components should be defined.*/
/**
 * <description> 
 * Comments...
 * </description>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`unsigned long',`CDECL',`CmpBelbGetInterruptMask',`(unsigned long ulPar)')

/**
 * <description> 
 * Comments...
 * </description>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`unsigned long',`CDECL',`CmpBelbSetInterruptMask',`(unsigned long ulPar)')


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

