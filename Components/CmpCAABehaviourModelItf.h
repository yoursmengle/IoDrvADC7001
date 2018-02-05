 /**
 * <interfacename>CAA_BehaviourModel_Extern</interfacename>
 * <description>
 * </description>
 *
 * <copyright>
 * (c) 2003-2017 3S-Smart Software Solutions
 * </copyright>
 */


	
	
#ifndef _CMPCAABEHAVIOURMODELITF_H_
#define _CMPCAABEHAVIOURMODELITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAABehaviourModel.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Interface functions of CAA BehaviourModel*/
void CDECL CBM_ETrig(CBM_ETRIG_CLASS* pInstance);
typedef void (CDECL * PFCBM_ETRIG) (CBM_ETRIG_CLASS* pInstance);
#if defined(CMPCAABEHAVIOURMODEL_NOTIMPLEMENTED) || defined(CBM_ETRIG_NOTIMPLEMENTED)
	#define USE_CBM_ETrig
	#define EXT_CBM_ETrig
	#define GET_CBM_ETrig(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CBM_ETrig(p0)  
	#define CHK_CBM_ETrig  FALSE
	#define EXP_CBM_ETrig  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CBM_ETrig
	#define EXT_CBM_ETrig
	#define GET_CBM_ETrig(fl)  CAL_CMGETAPI( "CBM_ETrig" ) 
	#define CAL_CBM_ETrig  CBM_ETrig
	#define CHK_CBM_ETrig  TRUE
	#define EXP_CBM_ETrig  CAL_CMEXPAPI( "CBM_ETrig" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAABEHAVIOURMODEL_EXTERNAL)
	#define USE_CBM_ETrig
	#define EXT_CBM_ETrig
	#define GET_CBM_ETrig(fl)  CAL_CMGETAPI( "CBM_ETrig" ) 
	#define CAL_CBM_ETrig  CBM_ETrig
	#define CHK_CBM_ETrig  TRUE
	#define EXP_CBM_ETrig  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CBM_ETrig", (RTS_UINTPTR)CBM_ETrig, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAABehaviourModelCBM_ETrig
	#define EXT_CmpCAABehaviourModelCBM_ETrig
	#define GET_CmpCAABehaviourModelCBM_ETrig  ERR_OK
	#define CAL_CmpCAABehaviourModelCBM_ETrig pICmpCAABehaviourModel->ICBM_ETrig
	#define CHK_CmpCAABehaviourModelCBM_ETrig (pICmpCAABehaviourModel != NULL)
	#define EXP_CmpCAABehaviourModelCBM_ETrig  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CBM_ETrig
	#define EXT_CBM_ETrig
	#define GET_CBM_ETrig(fl)  CAL_CMGETAPI( "CBM_ETrig" ) 
	#define CAL_CBM_ETrig pICmpCAABehaviourModel->ICBM_ETrig
	#define CHK_CBM_ETrig (pICmpCAABehaviourModel != NULL)
	#define EXP_CBM_ETrig  CAL_CMEXPAPI( "CBM_ETrig" ) 
#else /* DYNAMIC_LINK */
	#define USE_CBM_ETrig  PFCBM_ETRIG pfCBM_ETrig;
	#define EXT_CBM_ETrig  extern PFCBM_ETRIG pfCBM_ETrig;
	#define GET_CBM_ETrig(fl)  s_pfCMGetAPI2( "CBM_ETrig", (RTS_VOID_FCTPTR *)&pfCBM_ETrig, (fl), 0, 0)
	#define CAL_CBM_ETrig  pfCBM_ETrig
	#define CHK_CBM_ETrig  (pfCBM_ETrig != NULL)
	#define EXP_CBM_ETrig  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CBM_ETrig", (RTS_UINTPTR)CBM_ETrig, 0, 0) 
#endif



void CDECL CBM_ETrig_prvStart(void);
typedef void (CDECL * PFCBM_ETRIG_PRVSTART) (void);
#if defined(CMPCAABEHAVIOURMODEL_NOTIMPLEMENTED) || defined(CBM_ETRIG_PRVSTART_NOTIMPLEMENTED)
	#define USE_CBM_ETrig_prvStart
	#define EXT_CBM_ETrig_prvStart
	#define GET_CBM_ETrig_prvStart(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CBM_ETrig_prvStart()  
	#define CHK_CBM_ETrig_prvStart  FALSE
	#define EXP_CBM_ETrig_prvStart  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CBM_ETrig_prvStart
	#define EXT_CBM_ETrig_prvStart
	#define GET_CBM_ETrig_prvStart(fl)  CAL_CMGETAPI( "CBM_ETrig_prvStart" ) 
	#define CAL_CBM_ETrig_prvStart  CBM_ETrig_prvStart
	#define CHK_CBM_ETrig_prvStart  TRUE
	#define EXP_CBM_ETrig_prvStart  CAL_CMEXPAPI( "CBM_ETrig_prvStart" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAABEHAVIOURMODEL_EXTERNAL)
	#define USE_CBM_ETrig_prvStart
	#define EXT_CBM_ETrig_prvStart
	#define GET_CBM_ETrig_prvStart(fl)  CAL_CMGETAPI( "CBM_ETrig_prvStart" ) 
	#define CAL_CBM_ETrig_prvStart  CBM_ETrig_prvStart
	#define CHK_CBM_ETrig_prvStart  TRUE
	#define EXP_CBM_ETrig_prvStart  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CBM_ETrig_prvStart", (RTS_UINTPTR)CBM_ETrig_prvStart, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAABehaviourModelCBM_ETrig_prvStart
	#define EXT_CmpCAABehaviourModelCBM_ETrig_prvStart
	#define GET_CmpCAABehaviourModelCBM_ETrig_prvStart  ERR_OK
	#define CAL_CmpCAABehaviourModelCBM_ETrig_prvStart pICmpCAABehaviourModel->ICBM_ETrig_prvStart
	#define CHK_CmpCAABehaviourModelCBM_ETrig_prvStart (pICmpCAABehaviourModel != NULL)
	#define EXP_CmpCAABehaviourModelCBM_ETrig_prvStart  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CBM_ETrig_prvStart
	#define EXT_CBM_ETrig_prvStart
	#define GET_CBM_ETrig_prvStart(fl)  CAL_CMGETAPI( "CBM_ETrig_prvStart" ) 
	#define CAL_CBM_ETrig_prvStart pICmpCAABehaviourModel->ICBM_ETrig_prvStart
	#define CHK_CBM_ETrig_prvStart (pICmpCAABehaviourModel != NULL)
	#define EXP_CBM_ETrig_prvStart  CAL_CMEXPAPI( "CBM_ETrig_prvStart" ) 
#else /* DYNAMIC_LINK */
	#define USE_CBM_ETrig_prvStart  PFCBM_ETRIG_PRVSTART pfCBM_ETrig_prvStart;
	#define EXT_CBM_ETrig_prvStart  extern PFCBM_ETRIG_PRVSTART pfCBM_ETrig_prvStart;
	#define GET_CBM_ETrig_prvStart(fl)  s_pfCMGetAPI2( "CBM_ETrig_prvStart", (RTS_VOID_FCTPTR *)&pfCBM_ETrig_prvStart, (fl), 0, 0)
	#define CAL_CBM_ETrig_prvStart  pfCBM_ETrig_prvStart
	#define CHK_CBM_ETrig_prvStart  (pfCBM_ETrig_prvStart != NULL)
	#define EXP_CBM_ETrig_prvStart  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CBM_ETrig_prvStart", (RTS_UINTPTR)CBM_ETrig_prvStart, 0, 0) 
#endif



void CDECL CBM_ETrig_prvCyclicAction(void);
typedef void (CDECL * PFCBM_ETRIG_PRVCYCLICACTION) (void);
#if defined(CMPCAABEHAVIOURMODEL_NOTIMPLEMENTED) || defined(CBM_ETRIG_PRVCYCLICACTION_NOTIMPLEMENTED)
	#define USE_CBM_ETrig_prvCyclicAction
	#define EXT_CBM_ETrig_prvCyclicAction
	#define GET_CBM_ETrig_prvCyclicAction(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CBM_ETrig_prvCyclicAction()  
	#define CHK_CBM_ETrig_prvCyclicAction  FALSE
	#define EXP_CBM_ETrig_prvCyclicAction  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CBM_ETrig_prvCyclicAction
	#define EXT_CBM_ETrig_prvCyclicAction
	#define GET_CBM_ETrig_prvCyclicAction(fl)  CAL_CMGETAPI( "CBM_ETrig_prvCyclicAction" ) 
	#define CAL_CBM_ETrig_prvCyclicAction  CBM_ETrig_prvCyclicAction
	#define CHK_CBM_ETrig_prvCyclicAction  TRUE
	#define EXP_CBM_ETrig_prvCyclicAction  CAL_CMEXPAPI( "CBM_ETrig_prvCyclicAction" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAABEHAVIOURMODEL_EXTERNAL)
	#define USE_CBM_ETrig_prvCyclicAction
	#define EXT_CBM_ETrig_prvCyclicAction
	#define GET_CBM_ETrig_prvCyclicAction(fl)  CAL_CMGETAPI( "CBM_ETrig_prvCyclicAction" ) 
	#define CAL_CBM_ETrig_prvCyclicAction  CBM_ETrig_prvCyclicAction
	#define CHK_CBM_ETrig_prvCyclicAction  TRUE
	#define EXP_CBM_ETrig_prvCyclicAction  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CBM_ETrig_prvCyclicAction", (RTS_UINTPTR)CBM_ETrig_prvCyclicAction, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAABehaviourModelCBM_ETrig_prvCyclicAction
	#define EXT_CmpCAABehaviourModelCBM_ETrig_prvCyclicAction
	#define GET_CmpCAABehaviourModelCBM_ETrig_prvCyclicAction  ERR_OK
	#define CAL_CmpCAABehaviourModelCBM_ETrig_prvCyclicAction pICmpCAABehaviourModel->ICBM_ETrig_prvCyclicAction
	#define CHK_CmpCAABehaviourModelCBM_ETrig_prvCyclicAction (pICmpCAABehaviourModel != NULL)
	#define EXP_CmpCAABehaviourModelCBM_ETrig_prvCyclicAction  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CBM_ETrig_prvCyclicAction
	#define EXT_CBM_ETrig_prvCyclicAction
	#define GET_CBM_ETrig_prvCyclicAction(fl)  CAL_CMGETAPI( "CBM_ETrig_prvCyclicAction" ) 
	#define CAL_CBM_ETrig_prvCyclicAction pICmpCAABehaviourModel->ICBM_ETrig_prvCyclicAction
	#define CHK_CBM_ETrig_prvCyclicAction (pICmpCAABehaviourModel != NULL)
	#define EXP_CBM_ETrig_prvCyclicAction  CAL_CMEXPAPI( "CBM_ETrig_prvCyclicAction" ) 
#else /* DYNAMIC_LINK */
	#define USE_CBM_ETrig_prvCyclicAction  PFCBM_ETRIG_PRVCYCLICACTION pfCBM_ETrig_prvCyclicAction;
	#define EXT_CBM_ETrig_prvCyclicAction  extern PFCBM_ETRIG_PRVCYCLICACTION pfCBM_ETrig_prvCyclicAction;
	#define GET_CBM_ETrig_prvCyclicAction(fl)  s_pfCMGetAPI2( "CBM_ETrig_prvCyclicAction", (RTS_VOID_FCTPTR *)&pfCBM_ETrig_prvCyclicAction, (fl), 0, 0)
	#define CAL_CBM_ETrig_prvCyclicAction  pfCBM_ETrig_prvCyclicAction
	#define CHK_CBM_ETrig_prvCyclicAction  (pfCBM_ETrig_prvCyclicAction != NULL)
	#define EXP_CBM_ETrig_prvCyclicAction  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CBM_ETrig_prvCyclicAction", (RTS_UINTPTR)CBM_ETrig_prvCyclicAction, 0, 0) 
#endif



void CDECL CBM_ETrig_prvAbort(void);
typedef void (CDECL * PFCBM_ETRIG_PRVABORT) (void);
#if defined(CMPCAABEHAVIOURMODEL_NOTIMPLEMENTED) || defined(CBM_ETRIG_PRVABORT_NOTIMPLEMENTED)
	#define USE_CBM_ETrig_prvAbort
	#define EXT_CBM_ETrig_prvAbort
	#define GET_CBM_ETrig_prvAbort(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CBM_ETrig_prvAbort()  
	#define CHK_CBM_ETrig_prvAbort  FALSE
	#define EXP_CBM_ETrig_prvAbort  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CBM_ETrig_prvAbort
	#define EXT_CBM_ETrig_prvAbort
	#define GET_CBM_ETrig_prvAbort(fl)  CAL_CMGETAPI( "CBM_ETrig_prvAbort" ) 
	#define CAL_CBM_ETrig_prvAbort  CBM_ETrig_prvAbort
	#define CHK_CBM_ETrig_prvAbort  TRUE
	#define EXP_CBM_ETrig_prvAbort  CAL_CMEXPAPI( "CBM_ETrig_prvAbort" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAABEHAVIOURMODEL_EXTERNAL)
	#define USE_CBM_ETrig_prvAbort
	#define EXT_CBM_ETrig_prvAbort
	#define GET_CBM_ETrig_prvAbort(fl)  CAL_CMGETAPI( "CBM_ETrig_prvAbort" ) 
	#define CAL_CBM_ETrig_prvAbort  CBM_ETrig_prvAbort
	#define CHK_CBM_ETrig_prvAbort  TRUE
	#define EXP_CBM_ETrig_prvAbort  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CBM_ETrig_prvAbort", (RTS_UINTPTR)CBM_ETrig_prvAbort, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAABehaviourModelCBM_ETrig_prvAbort
	#define EXT_CmpCAABehaviourModelCBM_ETrig_prvAbort
	#define GET_CmpCAABehaviourModelCBM_ETrig_prvAbort  ERR_OK
	#define CAL_CmpCAABehaviourModelCBM_ETrig_prvAbort pICmpCAABehaviourModel->ICBM_ETrig_prvAbort
	#define CHK_CmpCAABehaviourModelCBM_ETrig_prvAbort (pICmpCAABehaviourModel != NULL)
	#define EXP_CmpCAABehaviourModelCBM_ETrig_prvAbort  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CBM_ETrig_prvAbort
	#define EXT_CBM_ETrig_prvAbort
	#define GET_CBM_ETrig_prvAbort(fl)  CAL_CMGETAPI( "CBM_ETrig_prvAbort" ) 
	#define CAL_CBM_ETrig_prvAbort pICmpCAABehaviourModel->ICBM_ETrig_prvAbort
	#define CHK_CBM_ETrig_prvAbort (pICmpCAABehaviourModel != NULL)
	#define EXP_CBM_ETrig_prvAbort  CAL_CMEXPAPI( "CBM_ETrig_prvAbort" ) 
#else /* DYNAMIC_LINK */
	#define USE_CBM_ETrig_prvAbort  PFCBM_ETRIG_PRVABORT pfCBM_ETrig_prvAbort;
	#define EXT_CBM_ETrig_prvAbort  extern PFCBM_ETRIG_PRVABORT pfCBM_ETrig_prvAbort;
	#define GET_CBM_ETrig_prvAbort(fl)  s_pfCMGetAPI2( "CBM_ETrig_prvAbort", (RTS_VOID_FCTPTR *)&pfCBM_ETrig_prvAbort, (fl), 0, 0)
	#define CAL_CBM_ETrig_prvAbort  pfCBM_ETrig_prvAbort
	#define CHK_CBM_ETrig_prvAbort  (pfCBM_ETrig_prvAbort != NULL)
	#define EXP_CBM_ETrig_prvAbort  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CBM_ETrig_prvAbort", (RTS_UINTPTR)CBM_ETrig_prvAbort, 0, 0) 
#endif



void CDECL CBM_ETrig_prvResetOutputs(CBM_ETRIG_CLASS* pInstance);
typedef void (CDECL * PFCBM_ETRIG_PRVRESETOUTPUTS) (CBM_ETRIG_CLASS* pInstance);
#if defined(CMPCAABEHAVIOURMODEL_NOTIMPLEMENTED) || defined(CBM_ETRIG_PRVRESETOUTPUTS_NOTIMPLEMENTED)
	#define USE_CBM_ETrig_prvResetOutputs
	#define EXT_CBM_ETrig_prvResetOutputs
	#define GET_CBM_ETrig_prvResetOutputs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CBM_ETrig_prvResetOutputs(p0)  
	#define CHK_CBM_ETrig_prvResetOutputs  FALSE
	#define EXP_CBM_ETrig_prvResetOutputs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CBM_ETrig_prvResetOutputs
	#define EXT_CBM_ETrig_prvResetOutputs
	#define GET_CBM_ETrig_prvResetOutputs(fl)  CAL_CMGETAPI( "CBM_ETrig_prvResetOutputs" ) 
	#define CAL_CBM_ETrig_prvResetOutputs  CBM_ETrig_prvResetOutputs
	#define CHK_CBM_ETrig_prvResetOutputs  TRUE
	#define EXP_CBM_ETrig_prvResetOutputs  CAL_CMEXPAPI( "CBM_ETrig_prvResetOutputs" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAABEHAVIOURMODEL_EXTERNAL)
	#define USE_CBM_ETrig_prvResetOutputs
	#define EXT_CBM_ETrig_prvResetOutputs
	#define GET_CBM_ETrig_prvResetOutputs(fl)  CAL_CMGETAPI( "CBM_ETrig_prvResetOutputs" ) 
	#define CAL_CBM_ETrig_prvResetOutputs  CBM_ETrig_prvResetOutputs
	#define CHK_CBM_ETrig_prvResetOutputs  TRUE
	#define EXP_CBM_ETrig_prvResetOutputs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CBM_ETrig_prvResetOutputs", (RTS_UINTPTR)CBM_ETrig_prvResetOutputs, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAABehaviourModelCBM_ETrig_prvResetOutputs
	#define EXT_CmpCAABehaviourModelCBM_ETrig_prvResetOutputs
	#define GET_CmpCAABehaviourModelCBM_ETrig_prvResetOutputs  ERR_OK
	#define CAL_CmpCAABehaviourModelCBM_ETrig_prvResetOutputs pICmpCAABehaviourModel->ICBM_ETrig_prvResetOutputs
	#define CHK_CmpCAABehaviourModelCBM_ETrig_prvResetOutputs (pICmpCAABehaviourModel != NULL)
	#define EXP_CmpCAABehaviourModelCBM_ETrig_prvResetOutputs  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CBM_ETrig_prvResetOutputs
	#define EXT_CBM_ETrig_prvResetOutputs
	#define GET_CBM_ETrig_prvResetOutputs(fl)  CAL_CMGETAPI( "CBM_ETrig_prvResetOutputs" ) 
	#define CAL_CBM_ETrig_prvResetOutputs pICmpCAABehaviourModel->ICBM_ETrig_prvResetOutputs
	#define CHK_CBM_ETrig_prvResetOutputs (pICmpCAABehaviourModel != NULL)
	#define EXP_CBM_ETrig_prvResetOutputs  CAL_CMEXPAPI( "CBM_ETrig_prvResetOutputs" ) 
#else /* DYNAMIC_LINK */
	#define USE_CBM_ETrig_prvResetOutputs  PFCBM_ETRIG_PRVRESETOUTPUTS pfCBM_ETrig_prvResetOutputs;
	#define EXT_CBM_ETrig_prvResetOutputs  extern PFCBM_ETRIG_PRVRESETOUTPUTS pfCBM_ETrig_prvResetOutputs;
	#define GET_CBM_ETrig_prvResetOutputs(fl)  s_pfCMGetAPI2( "CBM_ETrig_prvResetOutputs", (RTS_VOID_FCTPTR *)&pfCBM_ETrig_prvResetOutputs, (fl), 0, 0)
	#define CAL_CBM_ETrig_prvResetOutputs  pfCBM_ETrig_prvResetOutputs
	#define CHK_CBM_ETrig_prvResetOutputs  (pfCBM_ETrig_prvResetOutputs != NULL)
	#define EXP_CBM_ETrig_prvResetOutputs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CBM_ETrig_prvResetOutputs", (RTS_UINTPTR)CBM_ETrig_prvResetOutputs, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif




typedef struct
{
	IBase_C *pBase;
	PFCBM_ETRIG ICBM_ETrig;
 	PFCBM_ETRIG_PRVSTART ICBM_ETrig_prvStart;
 	PFCBM_ETRIG_PRVCYCLICACTION ICBM_ETrig_prvCyclicAction;
 	PFCBM_ETRIG_PRVABORT ICBM_ETrig_prvAbort;
 	PFCBM_ETRIG_PRVRESETOUTPUTS ICBM_ETrig_prvResetOutputs;
 } ICmpCAABehaviourModel_C;

#ifdef CPLUSPLUS
class ICmpCAABehaviourModel : public IBase
{
	public:
		virtual void CDECL ICBM_ETrig(CBM_ETRIG_CLASS* pInstance) =0;
		virtual void CDECL ICBM_ETrig_prvStart(void) =0;
		virtual void CDECL ICBM_ETrig_prvCyclicAction(void) =0;
		virtual void CDECL ICBM_ETrig_prvAbort(void) =0;
		virtual void CDECL ICBM_ETrig_prvResetOutputs(CBM_ETRIG_CLASS* pInstance) =0;
};
	#ifndef ITF_CmpCAABehaviourModel
		#define ITF_CmpCAABehaviourModel static ICmpCAABehaviourModel *pICmpCAABehaviourModel = NULL;
	#endif
	#define EXTITF_CmpCAABehaviourModel
#else	/*CPLUSPLUS*/
	typedef ICmpCAABehaviourModel_C		ICmpCAABehaviourModel;
	#ifndef ITF_CmpCAABehaviourModel
		#define ITF_CmpCAABehaviourModel
	#endif
	#define EXTITF_CmpCAABehaviourModel
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCAABEHAVIOURMODELITF_H_*/
