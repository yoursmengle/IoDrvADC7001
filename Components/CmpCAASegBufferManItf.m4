SET_INTERFACE_NAME(`CmpCAASegBufferMan')

#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAASegBufferMan.h"


#ifdef __cplusplus
extern "C" {
#endif

DEF_ITF_API(`CAA_ERROR',`CDECL',`SBM_Init',`(void)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`SBM_Exit',`(void)')

DEF_ITF_API(`SBM_PBUFFER',`CDECL',`SBM_ChainBuffer',`(SBM_PBUFFER pHead, SBM_PBUFFER pTail, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`SBM_CopyBufferData',`(SBM_PBUFFER pBuffer, CAA_SIZE szOffset, CAA_SIZE szLength, CAA_PVOID pData, CAA_SIZE szSize)')
DEF_ITF_API(`SBM_PBUFFER',`CDECL',`SBM_CreateBuffer',`(CAA_SIZE szSize, CAA_PVOID pData, CAA_BOOL xPermanent, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`SBM_DeleteBuffer',`(SBM_PBUFFER pBuffer)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`SBM_BufferAddRef',`(SBM_PBUFFER pBuffer)')
DEF_ITF_API(`CAA_SIZE',`CDECL',`SBM_GetBufferSize',`(SBM_PBUFFER pBuffer, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_PVOID',`CDECL',`SBM_GetSegmentDataPointer',`(SBM_PBUFFER pBuffer, CAA_SIZE* pszSize, CAA_BOOL* pxPermanent, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`SBM_MoveToBufferOffset',`(SBM_PBUFFER pBuffer, CAA_SIZE szOffset)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`SBM_MoveToNextSegment',`(SBM_PBUFFER pBuffer)')
DEF_ITF_API(`SBM_PBUFFER',`CDECL',`SBM_SliceBuffer',`(SBM_PBUFFER pBuffer, CAA_SIZE szOffset, CAA_SIZE szLength, CAA_ERROR* peError)')
DEF_ITF_API(`SBM_PQUEUE',`CDECL',`SBM_CreateQueue',`(CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`SBM_DeleteQueue',`(SBM_PQUEUE pQueue)')
DEF_ITF_API(`SBM_PBUFFER',`CDECL',`SBM_DequeueBuffer',`(SBM_PQUEUE pQueue, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`SBM_EnqueueBuffer',`(SBM_PQUEUE pQueue, SBM_PBUFFER hBuffer)')
DEF_ITF_API(`CAA_SIZE',`CDECL',`SBM_GetQueueLength',`(SBM_PQUEUE pQueue, CAA_ERROR* peError)')
DEF_ITF_API(`CAA_UINT',`CDECL',`SBM_GetSupplierVersion',`(CAA_BOOL xDummy)')

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>sbm_bufferaddref</description>
 */
typedef struct tagsbm_bufferaddref_struct
{
	CAA_HANDLE hBuffer;					/* VAR_INPUT */	
	CAA_ERROR SBM_BufferAddRef;			/* VAR_OUTPUT */	
} sbm_bufferaddref_struct;

DEF_API(`void',`CDECL',`sbm_bufferaddref',`(sbm_bufferaddref_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x17A0E79E),0x03050500)

/**
 * <description>sbm_chainbuffer</description>
 */
typedef struct tagsbm_chainbuffer_struct
{
	CAA_HANDLE hHead;					/* VAR_INPUT */	/* Head hBuffer */
	CAA_HANDLE hTail;					/* VAR_INPUT */	/* Tail hBuffer */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE SBM_ChainBuffer;			/* VAR_OUTPUT */	/* hBuffer */
} sbm_chainbuffer_struct;

DEF_API(`void',`CDECL',`sbm_chainbuffer',`(sbm_chainbuffer_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x3A6B344E),0x03050500)

/**
 * <description>sbm_copybufferdata</description>
 */
typedef struct tagsbm_copybufferdata_struct
{
	CAA_HANDLE hBuffer;					/* VAR_INPUT */	/* Source */
	CAA_SIZE szOffset;					/* VAR_INPUT */	/* Offset in Buffer */
	CAA_SIZE szLength;					/* VAR_INPUT */	/* Length of Data to Copy */
	CAA_PVOID pData;					/* VAR_INPUT */	/* Destination */
	CAA_SIZE szSize;					/* VAR_INPUT */	/* Size of Destination */
	CAA_ERROR SBM_CopyBufferData;		/* VAR_OUTPUT */	/* eError */
} sbm_copybufferdata_struct;

DEF_API(`void',`CDECL',`sbm_copybufferdata',`(sbm_copybufferdata_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xE0E8C059),0x03050500)

/**
 * <description>sbm_createbuffer</description>
 */
typedef struct tagsbm_createbuffer_struct
{
	CAA_SIZE szSize;					/* VAR_INPUT */	/* size of the new Buffer */
	CAA_PVOID pData;					/* VAR_INPUT */	/* Pointer to initial data. CAA.gc_pNULL => Init with zero */
	CAA_BOOL xPermanent;				/* VAR_INPUT */	/* TRUE => Buffer is imutable */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE SBM_CreateBuffer;		/* VAR_OUTPUT */	/* hBuffer */
} sbm_createbuffer_struct;

DEF_API(`void',`CDECL',`sbm_createbuffer',`(sbm_createbuffer_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xEE6CBB0F),0x03050500)

/**
 * <description>sbm_createqueue</description>
 */
typedef struct tagsbm_createqueue_struct
{
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE SBM_CreateQueue;			/* VAR_OUTPUT */	/* hQueue */
} sbm_createqueue_struct;

DEF_API(`void',`CDECL',`sbm_createqueue',`(sbm_createqueue_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xFEB5034F),0x03050500)

/**
 * <description>sbm_deletebuffer</description>
 */
typedef struct tagsbm_deletebuffer_struct
{
	CAA_HANDLE hBuffer;					/* VAR_INPUT */	
	CAA_ERROR SBM_DeleteBuffer;			/* VAR_OUTPUT */	/* eError */
} sbm_deletebuffer_struct;

DEF_API(`void',`CDECL',`sbm_deletebuffer',`(sbm_deletebuffer_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x42A2EADD),0x03050500)

/**
 * <description>sbm_deletequeue</description>
 */
typedef struct tagsbm_deletequeue_struct
{
	CAA_HANDLE hQueue;					/* VAR_INPUT */	
	CAA_ERROR SBM_DeleteQueue;			/* VAR_OUTPUT */	/* eError */
} sbm_deletequeue_struct;

DEF_API(`void',`CDECL',`sbm_deletequeue',`(sbm_deletequeue_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1637AFBF),0x03050500)

/**
 * <description>sbm_dequeuebuffer</description>
 */
typedef struct tagsbm_dequeuebuffer_struct
{
	CAA_HANDLE hQueue;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE SBM_DequeueBuffer;		/* VAR_OUTPUT */	/* hBuffer */
} sbm_dequeuebuffer_struct;

DEF_API(`void',`CDECL',`sbm_dequeuebuffer',`(sbm_dequeuebuffer_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x94D91D25),0x03050500)

/**
 * <description>sbm_enqueuebuffer</description>
 */
typedef struct tagsbm_enqueuebuffer_struct
{
	CAA_HANDLE hQueue;					/* VAR_INPUT */	
	CAA_HANDLE hBuffer;					/* VAR_INPUT */	
	CAA_ERROR SBM_EnqueueBuffer;		/* VAR_OUTPUT */	
} sbm_enqueuebuffer_struct;

DEF_API(`void',`CDECL',`sbm_enqueuebuffer',`(sbm_enqueuebuffer_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4216F02A),0x03050500)

/**
 * <description>sbm_getbuffersize</description>
 */
typedef struct tagsbm_getbuffersize_struct
{
	CAA_HANDLE hBuffer;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_SIZE SBM_GetBufferSize;			/* VAR_OUTPUT */	/* szBufferSize */
} sbm_getbuffersize_struct;

DEF_API(`void',`CDECL',`sbm_getbuffersize',`(sbm_getbuffersize_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x03A7FF21),0x03050500)

/**
 * <description>sbm_getqueuelength</description>
 */
typedef struct tagsbm_getqueuelength_struct
{
	CAA_HANDLE hQueue;					/* VAR_INPUT */	
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_SIZE SBM_GetQueueLength;		/* VAR_OUTPUT */	/* szQueueLength */
} sbm_getqueuelength_struct;

DEF_API(`void',`CDECL',`sbm_getqueuelength',`(sbm_getqueuelength_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xFE9B8C99),0x03050500)

/**
 * <description>sbm_getsegmentdatapointer</description>
 */
typedef struct tagsbm_getsegmentdatapointer_struct
{
	CAA_HANDLE hBuffer;					/* VAR_INPUT */	
	CAA_SIZE *pszSize;					/* VAR_INPUT */	/* Size of Data */
	CAA_BOOL *pxPermanent;				/* VAR_INPUT */	/* TRUE => Segment is imutable */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_PVOID SBM_GetSegmentDataPointer;	/* VAR_OUTPUT */	/* pData */
} sbm_getsegmentdatapointer_struct;

DEF_API(`void',`CDECL',`sbm_getsegmentdatapointer',`(sbm_getsegmentdatapointer_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x6E812FF2),0x03050500)

/**
 * <description>sbm_movetobufferoffset</description>
 */
typedef struct tagsbm_movetobufferoffset_struct
{
	CAA_HANDLE hBuffer;					/* VAR_INPUT */	
	CAA_SIZE szOffset;					/* VAR_INPUT */	
	CAA_ERROR SBM_MoveToBufferOffset;	/* VAR_OUTPUT */	/* eError */
} sbm_movetobufferoffset_struct;

DEF_API(`void',`CDECL',`sbm_movetobufferoffset',`(sbm_movetobufferoffset_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x2E7ADC1E),0x03050500)

/**
 * <description>sbm_movetonextsegment</description>
 */
typedef struct tagsbm_movetonextsegment_struct
{
	CAA_HANDLE hBuffer;					/* VAR_INPUT */	
	CAA_ERROR SBM_MoveToNextSegment;	/* VAR_OUTPUT */	/* eError */
} sbm_movetonextsegment_struct;

DEF_API(`void',`CDECL',`sbm_movetonextsegment',`(sbm_movetonextsegment_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC8C81F37),0x03050500)

/**
 * <description>sbm_slicebuffer</description>
 */
typedef struct tagsbm_slicebuffer_struct
{
	CAA_HANDLE hBuffer;					/* VAR_INPUT */	/* Buffer to split */
	CAA_SIZE szOffset;					/* VAR_INPUT */	/* Offset in Buffer */
	CAA_SIZE szLength;					/* VAR_INPUT */	/* Length of Data */
	CAA_ERROR *peError;					/* VAR_INPUT */	
	CAA_HANDLE SBM_SliceBuffer;			/* VAR_OUTPUT */	/* hNewBuffer */
} sbm_slicebuffer_struct;

DEF_API(`void',`CDECL',`sbm_slicebuffer',`(sbm_slicebuffer_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x8AB6BC00),0x03050500)

/**
 * <description>sbm_getsupplierversion</description>
 */
typedef struct tagsbm_getsupplierversion_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	RTS_IEC_WORD SBM_GetSupplierVersion;	/* VAR_OUTPUT */	
} sbm_getsupplierversion_struct;

DEF_API(`void',`CDECL',`sbm_getsupplierversion',`(sbm_getsupplierversion_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB2BCF041),0x03050500)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/
