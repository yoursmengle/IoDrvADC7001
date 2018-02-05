 
	
	
#ifndef _SYSDEPICTORITF_H_
#define _SYSDEPICTORITF_H_

#include "CmpStd.h"

 

 




#ifndef NUM_OF_STATIC_DEPICTOR_CONTROLS
	#define NUM_OF_STATIC_DEPICTOR_CONTROLS	8
#endif


typedef struct
{
	IBase_C *pBase;
} ISysDepictor_C;

#ifdef CPLUSPLUS
class ISysDepictor : public IBase
{
	public:
};
	#ifndef ITF_SysDepictor
		#define ITF_SysDepictor static ISysDepictor *pISysDepictor = NULL;
	#endif
	#define EXTITF_SysDepictor
#else	/*CPLUSPLUS*/
	typedef ISysDepictor_C		ISysDepictor;
	#ifndef ITF_SysDepictor
		#define ITF_SysDepictor
	#endif
	#define EXTITF_SysDepictor
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSDEPICTORITF_H_*/
