SET_INTERFACE_NAME(`CmpCAASdoClient')

#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "ClientSdo.h"

#ifdef __cplusplus
extern "C" {
#endif

DEF_ITF_API(`CAA_ERROR',`CDECL',`SDO_Read',`(SDO_READ* pParam)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`SDO_ReadEx',`(SDO_READ* pParam, CAA_ENUM eEvent)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`SDO_Write',`(SDO_WRITE* pParam)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`SDO_WriteEx',`(SDO_WRITE* pParam, CAA_ENUM eEvent)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`SDO_Write2',`(SDO_WRITE2* pParam, CAA_ENUM eEvent)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`SDO_Read2',`(SDO_READ2* pParam, CAA_ENUM eEvent)')

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>sdo_read</description>
 * SDO Read for CANopenStack before 3.5.7.0 (only for compatibility)
 */
typedef struct tagsdo_read_struct
{
	SDO_READ* pParam;	/* VAR_INPUT */
	CAA_ERROR SDO_Read;	/* VAR_OUTPUT */
} sdo_read_struct;

DEF_API(`void',`CDECL',`sdo_read',`(sdo_read_struct *p)',1,0x0,0x0)

/**
 * <description>
 * SDO Write for CANopenStack before 3.5.7.0 (only for compatibility)
 * </description>
 */
typedef struct tagsdo_write_struct
{
	SDO_WRITE* pParam;		/* VAR_INPUT */
	CAA_ERROR SDO_Write;	/* VAR_OUTPUT */
} sdo_write_struct;

DEF_API(`void',`CDECL',`sdo_write',`(sdo_write_struct *p)',1,0x0,0x0)

 /**
 * <description>
 * SDO Read for CANopenStack 3.5.7.0 or newer.
 * Changes: uiSize => udiSize
 * </description>
 */
typedef struct tagsdo_read2_struct
{
	SDO_READ2 *pParam;					/* VAR_INPUT */	
	RTS_IEC_INT SDO_Read2;				/* VAR_OUTPUT, Enum: ERROR */
} sdo_read2_struct;

DEF_API(`void',`CDECL',`sdo_read2',`(sdo_read2_struct *p)',1,0x0,0x0)

/**
 * <description>
 * SDO Write for CANopenStack 3.5.7.0 or newer.
 * Changes: uiSize => udiSize
 * </description>
 */
typedef struct tagsdo_write2_struct
{
	SDO_WRITE2 *pParam;					/* VAR_INPUT */	
	RTS_IEC_INT SDO_Write2;				/* VAR_OUTPUT, Enum: ERROR */
} sdo_write2_struct;

DEF_API(`void',`CDECL',`sdo_write2',`(sdo_write2_struct *p)',1,0x0,0x0)

/**
 * <description>nodeset__main</description>
 */
typedef struct tagnodeset_struct
{
	void* __VFTABLEPOINTER;			/* Pointer to virtual function table */

	CAA_UINT auiNodes[8];			/* Local variable */
	CAA_BOOL xThreadSafe;			/* Local variable */
	CAA_CRITSEC
	CAA_USINT usiMaxActive;			/* Local variable */
	CAA_USINT usiCurrentActive;		/* Local variable */
	CAA_UINT uiNoLimitationNodeID;	/* Local variable */
} nodeset_struct;

typedef struct
{
	nodeset_struct *pInstance;	/* VAR_INPUT */
} nodeset_main_struct;

DEF_API(`void',`CDECL',`nodeset__main',`(nodeset_main_struct *p)',1,0x0,0x0)

/**
 * <description>nodeset_fb_reinit</description>
 */
typedef struct tagnodeset_fb_reinit_struct
{
	nodeset_struct *pInstance;			/* VAR_INPUT */
	CAA_BOOL FB_ReInit;					/* VAR_OUTPUT */
} nodeset_fb_reinit_struct;

DEF_API(`void',`CDECL',`nodeset__fb_reinit',`(nodeset_fb_reinit_struct *p)',1,0x0,0x0)

/**
 * <description>nodeset_isactive</description>
 */
typedef struct tagnodeset_isactive_struct
{
	nodeset_struct *pInstance;			/* VAR_INPUT */
	CAA_USINT usiNodeId;				/* VAR_INPUT */
	CAA_BOOL IsActive;					/* VAR_OUTPUT */
} nodeset_isactive_struct;

DEF_API(`void',`CDECL',`nodeset__isactive',`(nodeset_isactive_struct *p)',1,0x0,0x0)

/**
 * <description>nodeset_fb_init</description>
 */
typedef struct tagnodeset_fb_init_struct
{
	nodeset_struct *pInstance;		/* VAR_INPUT */
	CAA_BOOL bInitRetains;			/* VAR_INPUT */
	CAA_BOOL bInCopyCode;			/* VAR_INPUT */
	CAA_BOOL xThreadSafe;			/* VAR_INPUT */
	CAA_BOOL Fb_Init;				/* VAR_OUTPUT */
} nodeset_fb_init_struct;

DEF_API(`void',`CDECL',`nodeset__fb_init',`(nodeset_fb_init_struct *p)',1,0x0,0x0)

/**
 * <description>nodeset_activate</description>
 */
typedef struct tagnodeset_activate_struct
{
	nodeset_struct *pInstance;		/* VAR_INPUT */
	CAA_USINT usiNodeId;			/* VAR_INPUT */
	CAA_BOOL Activate;				/* VAR_OUTPUT */
} nodeset_activate_struct;

DEF_API(`void',`CDECL',`nodeset__activate',`(nodeset_activate_struct *p)',1,0x0,0x0)

/**
 * <description>nodeset_deactivate</description>
 */
typedef struct tagnodeset_deactivate_struct
{
	nodeset_struct *pInstance;		/* VAR_INPUT */
	CAA_USINT usiNodeId;			/* VAR_INPUT */
	CAA_BOOL Deactivate;			/* VAR_OUTPUT */
} nodeset_deactivate_struct;

DEF_API(`void',`CDECL',`nodeset__deactivate',`(nodeset_deactivate_struct *p)',1,0x0,0x0)

/**
 * <description>nodeset_fb_exit</description>
 */
typedef struct tagnodeset_fb_exit_struct
{
	nodeset_struct *pInstance;		/* VAR_INPUT */
	CAA_BOOL bInCopyCode;			/* VAR_INPUT */
	CAA_BOOL Fb_Exit;				/* VAR_OUTPUT */
} nodeset_fb_exit_struct;

DEF_API(`void',`CDECL',`nodeset__fb_exit',`(nodeset_fb_exit_struct *p)',1,0x0,0x0)


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/
