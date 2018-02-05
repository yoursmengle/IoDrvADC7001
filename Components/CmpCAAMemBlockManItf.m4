SET_INTERFACE_NAME(`CmpCAAMemBlockMan')

#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAAMemBlockMan.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Pool Functions */
DEF_ITF_API(`CAA_HANDLE',`CDECL',`MBM_PoolCreateH',`(CAA_COUNT ctNumBlocks, CAA_SIZE szBlockSize, CAA_ENUM eEmpty, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`MBM_PoolCreateP',`(CAA_SIZE szBlockSize, CAA_SIZE szMemSize, CAA_PVOID pMemory, CAA_ENUM eEmpty, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`MBM_PoolExtendH',`(CAA_HANDLE hPool, CAA_COUNT ctNumBlocks)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`MBM_PoolDelete',`(CAA_HANDLE hPool)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`MBM_PoolGetBlock',`(CAA_HANDLE hPool, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_PVOID',`CDECL',`MBM_BlockGetData',`(CAA_HANDLE hBlock, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`MBM_PoolPutBlock',`(CAA_HANDLE hBlock)')
DEF_ITF_API(`CAA_SIZE',`CDECL',`MBM_PoolGetSize',`(CAA_COUNT ctNumBlocks, CAA_SIZE szBlockSize)')

/* Message Functions */
DEF_ITF_API(`CAA_HANDLE',`CDECL',`MBM_MsgReceive',`(CAA_HANDLE hXChg, CAA_COUNT* pctMsgLeft, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_PVOID',`CDECL',`MBM_MsgGetData',`(CAA_HANDLE hMsg, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`MBM_MsgSend',`(CAA_HANDLE hMsg, unsigned char ucPrio, CAA_HANDLE hXChg)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`MBM_MsgAddRef',`(CAA_HANDLE hMsg)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`MBM_MsgRelease',`(CAA_HANDLE hMsg)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`MBM_MsgReleaseEx',`(CAA_HANDLE hMsg, CAA_HANDLE hXChg)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`MBM_MsgClone',`(CAA_HANDLE hMsg, CAA_ERROR* peError)')

/* Exchange Functions */
DEF_ITF_API(`CAA_HANDLE',`CDECL',`MBM_XChgCreateH',`(CAA_COUNT ctNumMsg, CAA_SIZE szBlockSize, CAA_COUNT ctNumPrios, CAA_ENUM eSendMsg, CAA_ENUM eReceiveMsg, CAA_ENUM eXChgEmpty, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`MBM_XChgCreateP',`(CAA_SIZE szBlockSize, CAA_COUNT ctNumPrios, CAA_SIZE szMemSize, CAA_PVOID pMemory, CAA_ENUM eSendMsg, CAA_ENUM eReceiveMsg, CAA_ENUM eXChgEmpty, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`MBM_XChgExtendH',`(CAA_HANDLE hXChg, CAA_COUNT ctNumBlocks)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`MBM_XChgDelete',`(CAA_HANDLE hXChg)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`MBM_XChgDelete2',`(CAA_HANDLE hXChg, CAA_BOOL xForce)')
DEF_ITF_API(`CAA_SIZE',`CDECL',`MBM_XChgGetSize',`(CAA_COUNT ctNumMsg, CAA_SIZE szBlockSize, CAA_COUNT ctNumPrios)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`MBM_XChgIsEmpty',`(CAA_HANDLE hXChg, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_COUNT',`CDECL',`MBM_XChgMsgLeft',`(CAA_HANDLE hXChg, CAA_ERROR* peError)')

/* Flat Functions */
DEF_ITF_API(`CAA_HANDLE',`CDECL',`MBM_FlatCreateH',`(CAA_IDENT idMinKey, CAA_IDENT idMaxKey, CAA_COUNT ctNumKeys, CAA_ENUM eEnable, CAA_ENUM eDisable, CAA_ENUM eUpdate, CAA_ENUM eRead, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`MBM_FlatCreateP',`(CAA_IDENT idMinKey, CAA_IDENT idMaxKey, CAA_COUNT ctNumKeys, CAA_SIZE szMemory, CAA_PVOID pMemory, CAA_ENUM eEnable, CAA_ENUM eDisable, CAA_ENUM eUpdate, CAA_ENUM eRead, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`MBM_FlatEnable',`(CAA_HANDLE hFlat, CAA_IDENT idKey)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`MBM_FlatDisable',`(CAA_HANDLE hFlat, CAA_IDENT idKey, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`MBM_FlatTest',`(CAA_HANDLE hFlat, CAA_IDENT idKey, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`MBM_FlatUpdate',`(CAA_HANDLE hFlat, CAA_IDENT idKey, CAA_HANDLE hMsg, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`MBM_FlatRead',`(CAA_HANDLE hFlat, CAA_IDENT idKey, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`MBM_FlatDelete',`(CAA_HANDLE hFlat)')
DEF_ITF_API(`CAA_SIZE',`CDECL',`MBM_FlatGetSize',`(CAA_COUNT ctNumKeys)')

/* Ready List Functions */
DEF_ITF_API(`CAA_HANDLE',`CDECL',`MBM_RLstCreateH',`(CAA_ERROR* peError)')
DEF_ITF_API(`CAA_HANDLE',`CDECL',`MBM_RLstCreateP',`(CAA_SIZE szMemory, CAA_PVOID pMemory, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`MBM_RLstAddPrio',`(CAA_HANDLE hRLst, unsigned char ucPrio)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`MBM_RLstRemovePrio',`(CAA_HANDLE hRLst, unsigned char ucPrio)')
DEF_ITF_API(`unsigned char',`CDECL',`MBM_RLstGetHighestPrio',`(CAA_HANDLE hRLst, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`MBM_RLstCheckPrio',`(CAA_HANDLE hRLst, unsigned char ucPrio, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`MBM_RLstDelete',`(CAA_HANDLE hRLst)')
DEF_ITF_API(`CAA_SIZE',`CDECL',`MBM_RLstGetSize',`(CAA_BOOL xDummy)')

DEF_ITF_API(`unsigned short',`CDECL',`MBM_GetSupplierVersion',`(CAA_BOOL xDummy)')

#ifdef __cplusplus
}
#endif


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>mbm_blockgetdata</description>
 */
typedef struct tagmbm_blockgetdata_struct
{
	CAA_HANDLE hBlock;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_PVOID MBM_BlockGetData;			/* VAR_OUTPUT */	
} mbm_blockgetdata_struct;

DEF_API(`void',`CDECL',`mbm_blockgetdata',`(mbm_blockgetdata_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x32F2CF4F),0x03050500)

/**
 * <description>mbm_flatcreateh</description>
 */
typedef struct tagmbm_flatcreateh_struct
{
	CAA_IDENT idMinKey;					/* VAR_INPUT */	
	CAA_IDENT idMaxKey;					/* VAR_INPUT */	
	CAA_COUNT ctNumKeys;				/* VAR_INPUT */	
	CAA_ENUM eEnable;					/* VAR_INPUT */	
	CAA_ENUM eDisable;					/* VAR_INPUT */	
	CAA_ENUM eUpdate;					/* VAR_INPUT */	
	CAA_ENUM eRead;						/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_FlatCreateH;			/* VAR_OUTPUT */	/* hFlast */
} mbm_flatcreateh_struct;

DEF_API(`void',`CDECL',`mbm_flatcreateh',`(mbm_flatcreateh_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x101D308E),0x03050500)

/**
 * <description>mbm_flatcreatep</description>
 */
typedef struct tagmbm_flatcreatep_struct
{
	CAA_IDENT idMinKey;					/* VAR_INPUT */	
	CAA_IDENT idMaxKey;					/* VAR_INPUT */	
	CAA_COUNT ctNumKey;					/* VAR_INPUT */	
	CAA_SIZE szMemSize;					/* VAR_INPUT */	
	CAA_PVOID pMemory;					/* VAR_INPUT */	
	CAA_ENUM eEnable;					/* VAR_INPUT */	
	CAA_ENUM eDisable;					/* VAR_INPUT */	
	CAA_ENUM eUpdate;					/* VAR_INPUT */	
	CAA_ENUM eRead;						/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_FlatCreateP;			/* VAR_OUTPUT */	/* hFlat */
} mbm_flatcreatep_struct;

DEF_API(`void',`CDECL',`mbm_flatcreatep',`(mbm_flatcreatep_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xFC1B413D),0x03050500)

/**
 * <description>mbm_flatdelete</description>
 */
typedef struct tagmbm_flatdelete_struct
{
	CAA_HANDLE hFlat;					/* VAR_INPUT */	
	CAA_ERROR MBM_FlatDelete;			/* VAR_OUTPUT */	/* eError */
} mbm_flatdelete_struct;

DEF_API(`void',`CDECL',`mbm_flatdelete',`(mbm_flatdelete_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x51070F21),0x03050500)

/**
 * <description>mbm_flatdisable</description>
 */
typedef struct tagmbm_flatdisable_struct
{
	CAA_HANDLE hFlat;					/* VAR_INPUT */	
	CAA_IDENT idKey;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_FlatDisable;			/* VAR_OUTPUT */	/* hOldFlat */
} mbm_flatdisable_struct;

DEF_API(`void',`CDECL',`mbm_flatdisable',`(mbm_flatdisable_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x89676E45),0x03050500)

/**
 * <description>mbm_flatenable</description>
 */
typedef struct tagmbm_flatenable_struct
{
	CAA_HANDLE hFlat;					/* VAR_INPUT */	
	CAA_IDENT idKey;					/* VAR_INPUT */	
	CAA_ERROR MBM_FlatEnable;			/* VAR_OUTPUT */	/* eError */
} mbm_flatenable_struct;

DEF_API(`void',`CDECL',`mbm_flatenable',`(mbm_flatenable_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1923C169),0x03050500)

/**
 * <description>mbm_flatgetsize</description>
 */
typedef struct tagmbm_flatgetsize_struct
{
	CAA_COUNT ctNumKeys;				/* VAR_INPUT */	
	CAA_SIZE MBM_FlatGetSize;			/* VAR_OUTPUT */	
} mbm_flatgetsize_struct;

DEF_API(`void',`CDECL',`mbm_flatgetsize',`(mbm_flatgetsize_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x80F388B2),0x03050500)

/**
 * <description>mbm_flatread</description>
 */
typedef struct tagmbm_flatread_struct
{
	CAA_HANDLE hFlat;					/* VAR_INPUT */	
	CAA_IDENT idKey;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_FlatRead;			/* VAR_OUTPUT */	/* hMsg */
} mbm_flatread_struct;

DEF_API(`void',`CDECL',`mbm_flatread',`(mbm_flatread_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x6D388DC6),0x03050500)

/**
 * <description>mbm_flattest</description>
 */
typedef struct tagmbm_flattest_struct
{
	CAA_HANDLE hFlat;					/* VAR_INPUT */	
	CAA_IDENT idKey;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_BOOL MBM_FlatTest;				/* VAR_OUTPUT */	/* xEnabled */
} mbm_flattest_struct;

DEF_API(`void',`CDECL',`mbm_flattest',`(mbm_flattest_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xFD1FEB32),0x03050500)

/**
 * <description>mbm_flatupdate</description>
 */
typedef struct tagmbm_flatupdate_struct
{
	CAA_HANDLE hFlat;					/* VAR_INPUT */	
	CAA_IDENT idKey;					/* VAR_INPUT */	
	CAA_HANDLE hMsg;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_FlatUpdate;			/* VAR_OUTPUT */	/* hOldMsg */
} mbm_flatupdate_struct;

DEF_API(`void',`CDECL',`mbm_flatupdate',`(mbm_flatupdate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xFDEEDB01),0x03050500)

/**
 * Add a reference, to this message 
 */
typedef struct tagmbm_msgaddref_struct
{
	CAA_HANDLE hMsg;					/* VAR_INPUT */	
	CAA_ERROR MBM_MsgAddRef;			/* VAR_OUTPUT */	
} mbm_msgaddref_struct;

DEF_API(`void',`CDECL',`mbm_msgaddref',`(mbm_msgaddref_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x7BF62E5D),0x03050500)

/**
 * <description>mbm_msgclone</description>
 */
typedef struct tagmbm_msgclone_struct
{
	CAA_HANDLE hMsg;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_MsgClone;			/* VAR_OUTPUT */	
} mbm_msgclone_struct;

DEF_API(`void',`CDECL',`mbm_msgclone',`(mbm_msgclone_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x7F73045D),0x03050500)

/**
 * <description>mbm_msggetdata</description>
 */
typedef struct tagmbm_msggetdata_struct
{
	CAA_HANDLE hMsg;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_PVOID MBM_MsgGetData;			/* VAR_OUTPUT */	
} mbm_msggetdata_struct;

DEF_API(`void',`CDECL',`mbm_msggetdata',`(mbm_msggetdata_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x6B8C9A39),0x03050500)

/**
 * Gets a message from hXChg 
 */
typedef struct tagmbm_msgreceive_struct
{
	CAA_HANDLE hXChg;					/* VAR_INPUT */	
	CAA_COUNT *pctMsgLeft;				/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_MsgReceive;			/* VAR_OUTPUT */	
} mbm_msgreceive_struct;

DEF_API(`void',`CDECL',`mbm_msgreceive',`(mbm_msgreceive_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4387638B),0x03050500)

/**
 * If this message has the last reference, then Send it back to its ResourceExchange 
 */
typedef struct tagmbm_msgrelease_struct
{
	CAA_HANDLE hMsg;					/* VAR_INPUT */	
	CAA_ERROR MBM_MsgRelease;			/* VAR_OUTPUT */	
} mbm_msgrelease_struct;

DEF_API(`void',`CDECL',`mbm_msgrelease',`(mbm_msgrelease_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x6D55A0C0),0x03050500)

/**
 * If this message has the last reference, then Send it back to hXchg 
 */
typedef struct tagmbm_msgreleaseex_struct
{
	CAA_HANDLE hMsg;					/* VAR_INPUT */	
	CAA_HANDLE hXChg;					/* VAR_INPUT */	
	CAA_ERROR MBM_MsgReleaseEx;			/* VAR_OUTPUT */	
} mbm_msgreleaseex_struct;

DEF_API(`void',`CDECL',`mbm_msgreleaseex',`(mbm_msgreleaseex_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD41DCC1F),0x03050500)

/**
 * <description>mbm_msgsend</description>
 */
typedef struct tagmbm_msgsend_struct
{
	CAA_HANDLE hMsg;					/* VAR_INPUT */	
	RTS_IEC_USINT usiPrio;				/* VAR_INPUT */	
	CAA_HANDLE hXChg;					/* VAR_INPUT */	
	CAA_ERROR MBM_MsgSend;				/* VAR_OUTPUT */	
} mbm_msgsend_struct;

DEF_API(`void',`CDECL',`mbm_msgsend',`(mbm_msgsend_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA4201973),0x03050500)

/**
 * Take a pool of ctNumBlocks * szBlockSize bytes from the Heap(OS) and build a block pool 
 */
typedef struct tagmbm_poolcreateh_struct
{
	CAA_COUNT ctNumBlocks;				/* VAR_INPUT */	
	CAA_SIZE szBlockSize;				/* VAR_INPUT */	
	CAA_ENUM eEmpty;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_PoolCreateH;			/* VAR_OUTPUT */	/* hPool */
} mbm_poolcreateh_struct;

DEF_API(`void',`CDECL',`mbm_poolcreateh',`(mbm_poolcreateh_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x5DCA1021),0x03050500)

/**
 * Take as much as possible block of szBlockSize bytes from a PLC(IEC) provided memory and build a block pool 
 */
typedef struct tagmbm_poolcreatep_struct
{
	CAA_SIZE szBlockSize;				/* VAR_INPUT */	
	CAA_SIZE szMemSize;					/* VAR_INPUT */	
	CAA_PVOID pMemory;					/* VAR_INPUT */	
	CAA_ENUM eEmpty;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_PoolCreateP;			/* VAR_OUTPUT */	
} mbm_poolcreatep_struct;

DEF_API(`void',`CDECL',`mbm_poolcreatep',`(mbm_poolcreatep_struct *p)',1,0,0x03050500)

/**
 * Deletes a block pool created by PoolCreateX provided that all blocks are free 
 * If a block is in use, this call aborts 
 */
typedef struct tagmbm_pooldelete_struct
{
	CAA_HANDLE hPool;					/* VAR_INPUT */	
	CAA_ERROR MBM_PoolDelete;			/* VAR_OUTPUT */	
} mbm_pooldelete_struct;

DEF_API(`void',`CDECL',`mbm_pooldelete',`(mbm_pooldelete_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x98572907),0x03050500)

/**
 * <description>mbm_poolextendh</description>
 */
typedef struct tagmbm_poolextendh_struct
{
	CAA_HANDLE hPool;					/* VAR_INPUT */	
	CAA_COUNT ctNumBlocks;				/* VAR_INPUT */	
	CAA_ERROR MBM_PoolExtendH;			/* VAR_OUTPUT */	
} mbm_poolextendh_struct;

DEF_API(`void',`CDECL',`mbm_poolextendh',`(mbm_poolextendh_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x9C00A6F0),0x03050500)

/**
 * Gets the next available block from hPool and returns ist handle 
 */
typedef struct tagmbm_poolgetblock_struct
{
	CAA_HANDLE hPool;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_PoolGetBlock;		/* VAR_OUTPUT */	
} mbm_poolgetblock_struct;

DEF_API(`void',`CDECL',`mbm_poolgetblock',`(mbm_poolgetblock_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x2B3E34EB),0x03050500)

/**
 * <description>mbm_poolgetsize</description>
 */
typedef struct tagmbm_poolgetsize_struct
{
	CAA_COUNT ctNumBlock;				/* VAR_INPUT */	
	CAA_SIZE szBlockSize;				/* VAR_INPUT */	
	CAA_SIZE MBM_PoolGetSize;			/* VAR_OUTPUT */	
} mbm_poolgetsize_struct;

DEF_API(`void',`CDECL',`mbm_poolgetsize',`(mbm_poolgetsize_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x47282742),0x03050500)

/**
 * Clears the block owner and returns hBlock to its pool 
 */
typedef struct tagmbm_poolputblock_struct
{
	CAA_HANDLE hBlock;					/* VAR_INPUT */	
	CAA_ERROR MBM_PoolPutBlock;			/* VAR_OUTPUT */	
} mbm_poolputblock_struct;

DEF_API(`void',`CDECL',`mbm_poolputblock',`(mbm_poolputblock_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x80479C72),0x03050500)

/**
 * Add the priroity level usiPrio to the ready list 
 */
typedef struct tagmbm_rlstaddprio_struct
{
	CAA_HANDLE hRLst;					/* VAR_INPUT */	
	RTS_IEC_USINT usiPrio;				/* VAR_INPUT */	/* [0..63] Priotity Level */
	CAA_ERROR MBM_RLstAddPrio;			/* VAR_OUTPUT */	
} mbm_rlstaddprio_struct;

DEF_API(`void',`CDECL',`mbm_rlstaddprio',`(mbm_rlstaddprio_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x977D4860),0x03050500)

/**
 * return TRUE if the priority level usiPrio is part of the ready list 
 */
typedef struct tagmbm_rlstcheckprio_struct
{
	CAA_HANDLE hRLst;					/* VAR_INPUT */	
	RTS_IEC_USINT usiPrio;				/* VAR_INPUT */	/* [0..63] priority level. */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_BOOL MBM_RLstCheckPrio;			/* VAR_OUTPUT */	/* xReady */
} mbm_rlstcheckprio_struct;

DEF_API(`void',`CDECL',`mbm_rlstcheckprio',`(mbm_rlstcheckprio_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x9650B960),0x03050500)

/**
 * Take a SIZEOF(RLST) bytes from the Heap(OS) and build a Reday List 
 */
typedef struct tagmbm_rlstcreateh_struct
{
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_RLstCreateH;			/* VAR_OUTPUT */	
} mbm_rlstcreateh_struct;

DEF_API(`void',`CDECL',`mbm_rlstcreateh',`(mbm_rlstcreateh_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x2D79CB11),0x03050500)

/**
 * Take SIZEOF(RLST) bytes from a PLC(IEC) provided memory and build a Ready List 
 */
typedef struct tagmbm_rlstcreatep_struct
{
	CAA_SIZE szMemory;					/* VAR_INPUT */	
	CAA_PVOID pMemory;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_RLstCreateP;			/* VAR_OUTPUT */	
} mbm_rlstcreatep_struct;

DEF_API(`void',`CDECL',`mbm_rlstcreatep',`(mbm_rlstcreatep_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x24A5FF5A),0x03050500)

/**
 * free all allocated resources of a ready list 
 */
typedef struct tagmbm_rlstdelete_struct
{
	CAA_HANDLE hRLst;					/* VAR_INPUT */	
	CAA_ERROR MBM_RLstDelete;			/* VAR_OUTPUT */	
} mbm_rlstdelete_struct;

DEF_API(`void',`CDECL',`mbm_rlstdelete',`(mbm_rlstdelete_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA1F0D540),0x03050500)

/**
 * find the higest priority level in the ready list 
 */
typedef struct tagmbm_rlstgethighestprio_struct
{
	CAA_HANDLE hRLst;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	RTS_IEC_USINT MBM_RLstGetHighestPrio;	/* VAR_OUTPUT */	
} mbm_rlstgethighestprio_struct;

DEF_API(`void',`CDECL',`mbm_rlstgethighestprio',`(mbm_rlstgethighestprio_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x94D7A1CB),0x03050500)

/**
 * <description>mbm_rlstgetsize</description>
 */
typedef struct tagmbm_rlstgetsize_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	CAA_SIZE MBM_RLstGetSize;			/* VAR_OUTPUT */	
} mbm_rlstgetsize_struct;

DEF_API(`void',`CDECL',`mbm_rlstgetsize',`(mbm_rlstgetsize_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x3913C3B8),0x03050500)

/**
 * remove the priority level usiPrio from the ready list 
 */
typedef struct tagmbm_rlstremoveprio_struct
{
	CAA_HANDLE hRLst;					/* VAR_INPUT */	
	RTS_IEC_USINT usiPrio;				/* VAR_INPUT */	/* [0..63] priority level. 255 :=> remove all levels from the list */
	CAA_ERROR MBM_RLstRemovePrio;		/* VAR_OUTPUT */	
} mbm_rlstremoveprio_struct;

DEF_API(`void',`CDECL',`mbm_rlstremoveprio',`(mbm_rlstremoveprio_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x15C75530),0x03050500)

/**
 * Creates a message exchange of the specified type with Memory from Heap 
 * ctNumPrios = 0 AND ctNumMsg <> 0 => Resource Exchange 
 * ctNumPrios <> 0 AND ctNumMsg = 0 => NormalExchange    
 */
typedef struct tagmbm_xchgcreateh_struct
{
	CAA_COUNT ctNumMsg;					/* VAR_INPUT */	
	CAA_SIZE szBlockSize;				/* VAR_INPUT */	
	CAA_COUNT ctNumPrios;				/* VAR_INPUT */	
	CAA_ENUM eSendMsg;					/* VAR_INPUT */	
	CAA_ENUM eReceiveMsg;				/* VAR_INPUT */	
	CAA_ENUM eXchgEmpty;				/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_XChgCreateH;			/* VAR_OUTPUT */	/* hXChg */
} mbm_xchgcreateh_struct;

DEF_API(`void',`CDECL',`mbm_xchgcreateh',`(mbm_xchgcreateh_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x36E091AE),0x03050500)

/**
 * Creates a message exchange of the specified type with Memory from PLC 
 * ctNumPrios = 0 AND ctNumMsg <> 0 => Resource Exchange 
 * ctNumPrios <> 0 AND ctNumMsg = 0 => NormalExchange    
 */
typedef struct tagmbm_xchgcreatep_struct
{
	CAA_SIZE szBlockSize;				/* VAR_INPUT */	
	CAA_COUNT ctNumPrios;				/* VAR_INPUT */	
	CAA_SIZE szMemSize;					/* VAR_INPUT */	
	CAA_PVOID pMemory;					/* VAR_INPUT */	
	CAA_ENUM eSendMsg;					/* VAR_INPUT */	
	CAA_ENUM eReceiveMsg;				/* VAR_INPUT */	
	CAA_ENUM eXchgEmpty;				/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE MBM_XChgCreateP;			/* VAR_OUTPUT */	/* hXChg */
} mbm_xchgcreatep_struct;

DEF_API(`void',`CDECL',`mbm_xchgcreatep',`(mbm_xchgcreatep_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x578CD111),0x03050500)

/**
 * Deletes an exchange created by XChgCreate 
 */
typedef struct tagmbm_xchgdelete_struct
{
	CAA_HANDLE hXChg;					/* VAR_INPUT */	
	CAA_ERROR MBM_XChgDelete;			/* VAR_OUTPUT */	
} mbm_xchgdelete_struct;

DEF_API(`void',`CDECL',`mbm_xchgdelete',`(mbm_xchgdelete_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB954F1E6),0x03050500)

/**
 * <description>mbm_xchgextendh</description>
 */
typedef struct tagmbm_xchgextendh_struct
{
	CAA_HANDLE hXChg;					/* VAR_INPUT */	
	CAA_COUNT ctNumMsg;					/* VAR_INPUT */	
	CAA_ERROR MBM_XChgExtendH;			/* VAR_OUTPUT */	
} mbm_xchgextendh_struct;

DEF_API(`void',`CDECL',`mbm_xchgextendh',`(mbm_xchgextendh_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x9A53A368),0x03050500)

/**
 * <description>mbm_xchggetsize</description>
 */
typedef struct tagmbm_xchggetsize_struct
{
	CAA_COUNT ctNumMsg;					/* VAR_INPUT */	
	CAA_SIZE szBlockSize;				/* VAR_INPUT */	
	CAA_COUNT ctNumPrios;				/* VAR_INPUT */	
	CAA_SIZE MBM_XChgGetSize;			/* VAR_OUTPUT */	
} mbm_xchggetsize_struct;

DEF_API(`void',`CDECL',`mbm_xchggetsize',`(mbm_xchggetsize_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x58328040),0x03050500)

/**
 * <description>mbm_xchgisempty</description>
 */
typedef struct tagmbm_xchgisempty_struct
{
	CAA_HANDLE hXChg;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_BOOL MBM_XChgIsEmpty;			/* VAR_OUTPUT */	
} mbm_xchgisempty_struct;

DEF_API(`void',`CDECL',`mbm_xchgisempty',`(mbm_xchgisempty_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF693F781),0x03050500)

/**
 * <description>mbm_xchgmsgleft</description>
 */
typedef struct tagmbm_xchgmsgleft_struct
{
	CAA_HANDLE hXChg;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_COUNT MBM_XChgMsgLeft;			/* VAR_OUTPUT */	
} mbm_xchgmsgleft_struct;

DEF_API(`void',`CDECL',`mbm_xchgmsgleft',`(mbm_xchgmsgleft_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC98A455C),0x03050500)

/**
 * <description>mbm_getsupplierversion</description>
 */
typedef struct tagmbm_getsupplierversion_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	RTS_IEC_WORD MBM_GetSupplierVersion;	/* VAR_OUTPUT */	
} mbm_getsupplierversion_struct;

DEF_API(`void',`CDECL',`mbm_getsupplierversion',`(mbm_getsupplierversion_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x83993EFD),0x03050500)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

