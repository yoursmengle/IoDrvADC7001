 /*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		Naming service
*	Version:
*	Description:	External interface for the naming service client
******************************************************************************/


	
	
#ifndef _CMPBLKDRVUDPITF_H_
#define _CMPBLKDRVUDPITF_H_

#include "CmpStd.h"

 

 







typedef struct
{
	IBase_C *pBase;
} ICmpBlkDrvUdp_C;

#ifdef CPLUSPLUS
class ICmpBlkDrvUdp : public IBase
{
	public:
};
	#ifndef ITF_CmpBlkDrvUdp
		#define ITF_CmpBlkDrvUdp static ICmpBlkDrvUdp *pICmpBlkDrvUdp = NULL;
	#endif
	#define EXTITF_CmpBlkDrvUdp
#else	/*CPLUSPLUS*/
	typedef ICmpBlkDrvUdp_C		ICmpBlkDrvUdp;
	#ifndef ITF_CmpBlkDrvUdp
		#define ITF_CmpBlkDrvUdp
	#endif
	#define EXTITF_CmpBlkDrvUdp
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPBLKDRVUDPITF_H_*/
