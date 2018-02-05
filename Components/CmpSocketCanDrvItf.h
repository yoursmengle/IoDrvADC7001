 
	
	
#ifndef _CMPSOCKETCANDRVITF_H_
#define _CMPSOCKETCANDRVITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Settings to set the baudrate.
 *
 * Example:
 * InterfaceName=can
 * ScriptPath=./
 * ScriptName=rts_set_baud
 * </description>
 *
 */

#define SOCKETCAN_STRING_INTERFACENAME "InterfaceName"
#define SOCKETCAN_STRING_INTERFACENAME_DEFAULT "can" //could be e.g. vcan
#define SOCKETCAN_STRING_SCRIPTPATH "ScriptPath"
#define SOCKETCAN_STRING_SCRIPTPATH_DEFAULT "./" //e.g. /usr/bin/
#define SOCKETCAN_STRING_SCRIPTNAME "ScriptName"
#define SOCKETCAN_STRING_SCRIPTNAME_DEFAULT "rts_set_baud.sh"
#define SOCKETCAN_INT_TIMESTAMPS "Timestamps"
#define SOCKETCAN_INT_TIMESTAMPS_DEFAULT 0
#define SOCKETCAN_INT_LOOPBACK "Loopback"
#define SOCKETCAN_INT_LOOPBACK_DEFAULT 0
#define SOCKETCAN_INT_RECV_OWN_MSGS "RecvOwnMsgs"
#define SOCKETCAN_INT_RECV_OWN_MSGS_DEFAULT 1
#define SOCKETCAN_INT_ERRMASK "ErrorMask"
/* all known errors without "bus error" (may flood!) and "controller restarted" */
#define SOCKETCAN_INT_ERRMASK_DEFAULT 0x7F




typedef struct
{
	IBase_C *pBase;
} ICmpSocketCanDrv_C;

#ifdef CPLUSPLUS
class ICmpSocketCanDrv : public IBase
{
	public:
};
	#ifndef ITF_CmpSocketCanDrv
		#define ITF_CmpSocketCanDrv static ICmpSocketCanDrv *pICmpSocketCanDrv = NULL;
	#endif
	#define EXTITF_CmpSocketCanDrv
#else	/*CPLUSPLUS*/
	typedef ICmpSocketCanDrv_C		ICmpSocketCanDrv;
	#ifndef ITF_CmpSocketCanDrv
		#define ITF_CmpSocketCanDrv
	#endif
	#define EXTITF_CmpSocketCanDrv
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPSOCKETCANDRVITF_H_*/
