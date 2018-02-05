/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		CAADefinesGeneric.h
*	Version:		2.4
*	Purpose:		Generic CAA Parameters, do not change here, changes only in CAADefines.h.
*
******************************************************************************/
#ifndef __CAADEFINESGENERIC_H__                                   
#define __CAADEFINESGENERIC_H__                                   

#include <sysdefines.h>
#include "CmpStd.h"
#include "CmpItf.h"

#ifndef CAA_CB
	#ifdef CMPCAACALLBACK_NOTIMPLEMENTED
		#define CAA_CB	0 /* Activate CAA_Callback.lib */
	#else
		#define CAA_CB	1 /* Activate CAA_Callback.lib */
	#endif
#endif

#ifndef CAA_RSM
	#ifdef CMPCAARESMAN_NOTIMPLEMENTED
		#define CAA_RSM	0 /* Activate CAA_ResMan.lib */
	#else
		#define CAA_RSM	1 /* Activate CAA_ResMan.lib */
	#endif
#endif

#ifndef CAA_MBM
	#ifdef CMPCAAMEMBLOCKMAN_NOTIMPLEMENTED
		#define CAA_MBM	0 /* Activate CAA_MemBlockMan.lib */
	#else
		#define CAA_MBM	1 /* Activate CAA_MemBlockMan.lib */
	#endif
#endif

#ifndef CAA_CL2
	#ifdef CMPCAACANL2_NOTIMPLEMENTED
		#define CAA_CL2	0 /* Activate CAA_CanLevel2.lib */
	#else
		#define CAA_CL2	1 /* Activate CAA_CanLevel2.lib */
	#endif
#endif

#ifndef CAA_ASM
	#ifdef CMPCAAASYNCMAN_NOTIMPLEMENTED
		#define CAA_ASM	0 /* Activate CAA_AsyncMan.lib */
	#else
		#define CAA_ASM	1 /* Activate CAA_AsyncMan.lib */
	#endif
#endif

#ifndef CAA_FILE
	#ifdef CMPCAAFILE_NOTIMPLEMENTED
		#define CAA_FILE	0 /* Activate CAA_File.lib */
	#else
		#define CAA_FILE	1 /* Activate CAA_File.lib */
	#endif
#endif

#ifndef CAA_TICKS
	#ifdef CMPCAATICK_NOTIMPLEMENTED
		#define CAA_TICKS	0 /* Activate CAA_Ticks.lib */
	#else
		#define CAA_TICKS	1 /* Activate CAA_Ticks.lib */
	#endif
#endif

#ifndef CAA_TICKU
	#ifdef CMPCAATICKUTIL_NOTIMPLEMENTED
		#define CAA_TICKU	0 /* Activate CAA_TickUtil.lib */
	#else
		#define CAA_TICKU	1 /* Activate CAA_TickUtil.lib */
	#endif
#endif

#ifndef CAA_COM
	#ifdef CMPCAASERIALCOM_NOTIMPLEMENTED
		#define CAA_COM	0 /* Activate CAA_SerialCom.lib */
	#else
		#define CAA_COM	1 /* Activate CAA_SerialCom.lib */
	#endif
#endif

#ifndef CAA_DTU
	#ifdef CMPCAADTUTIL_NOTIMPLEMENTED
		#define CAA_DTU	0 /* Activate CAA_DTUtil.lib */
	#else
		#define CAA_DTU	1 /* Activate CAA_DTUtil.lib */
	#endif
#endif

#ifndef CAA_RTCLK
	#ifdef CMPCAAREALTIMECLOCK_NOTIMPLEMENTED
		#define CAA_RTCLK	0 /* Activate CAA_RealTimeClock.lib */
	#else
		#define CAA_RTCLK	1 /* Activate CAA_RealTimeClock.lib */
	#endif
#endif

#ifndef CAA_CBM
	#ifdef CMPCAABEHAVIOURMODEL_NOTIMPLEMENTED
		#define CAA_CBM	0 /* Activate CAA_BehaviourModel.lib */
	#else
		#define CAA_CBM	1 /* Activate CAA_BehaviourModel.lib */
	#endif
#endif

#ifndef CAA_TMR
	#ifdef CMPCAATIMER_NOTIMPLEMENTED
		#define CAA_TMR	0 /* Activate CAA_Timer.lib */
	#else
		#define CAA_TMR	1 /* Activate CAA_Timer.lib */
	#endif
#endif

#ifndef CAA_NBS
	#ifdef CMPCAANETBASESERVICES_NOTIMPLEMENTED
		#define CAA_NBS	0 /* Activate CAA_NetBaseServices.lib */
	#else
		#define CAA_NBS	1 /* Activate CAA_NetBaseServices.lib */
	#endif
#endif

#ifndef CAA_SBM
	#ifdef CMPCAASEGBUFFERMAN_NOTIMPLEMENTED
		#define CAA_SBM	0 /* Activate CAA_SegBufferMan.lib */
	#else
		#define CAA_SBM	1 /* Activate CAA_SegBufferMan.lib */
	#endif
#endif

#ifndef CAA_BIG_ENDIAN
	#ifdef RTS_BIGENDIAN_BITORDER
		#define CAA_BIG_ENDIAN 1
	#else
		#define CAA_BIG_ENDIAN 0
	#endif
#endif

#ifndef CAA_DEBUG
	#define CAA_DEBUG 0
#endif

/* Define CAA_IMP_TYPE */
#ifndef CAAFKT
	#define CAAFKT
#endif

#ifndef CAA_CRITSEC
	#define CAA_CRITSEC
#endif

#ifndef CAA_MSR_SAVE
	#define CAA_MSR_SAVE	RTS_UINTPTR ulParam;
#endif

/* Do not Define
#ifndef CAA_OPEN_CRITSEC
	#define CAA_OPEN_CRITSEC()
#endif
*/

#ifndef CAA_ENTER_CRITSEC
	#define CAA_ENTER_CRITSEC(h)	SysIntDisableAll(&ulParam)
#endif

#ifndef CAA_EXIT_CRITSEC
	#define CAA_EXIT_CRITSEC(h)		SysIntEnableAll(&ulParam)
#endif

/* Do not Define
#ifndef CAA_CLOSE_CRITSEC
	#define CAA_CLOSE_CRITSEC(h)
#endif
*/

#ifndef CAA_LOCK
	#define CAA_LOCK RTS_HANDLE _rts_lock;
#endif

#ifndef CAA_CREATE_LOCK
	#define CAA_CREATE_LOCK()	CAL_SysSemCreate((RTS_RESULT*)0)
#endif

#ifndef CAA_ENTER_LOCK
	#define CAA_ENTER_LOCK(h)	(void)CAL_SysSemEnter(h)
#endif

#ifndef CAA_LEAVE_LOCK
	#define CAA_LEAVE_LOCK(h)	(void)CAL_SysSemLeave(h)
#endif

#ifndef CAA_DELETE_LOCK
	#define CAA_DELETE_LOCK(h)	(void)CAL_SysSemDelete(h)
#endif

#undef CAA_MALLOC
#undef CAA_FREE
#undef CAA_MEMSET
#undef CAA_MEMCPY

#define CAA_MALLOC(szSize) CAL_SysMemAllocData(COMPONENT_NAME, ((RTS_SIZE)(szSize)),0)
#define CAA_FREE(pBlock, szSize) /*lint -e522 -e550 -e438*/ CAL_SysMemFreeData(COMPONENT_NAME, ((void*)(pBlock)))
#define CAA_MEMSET(pBlock, byData, szSize) memset(((void*)(pBlock)), ((unsigned char)(byData)), ((RTS_SIZE)(szSize)))
#define CAA_MEMCPY(pDst, pSrc, szSize) memcpy(((void*)(pDst)), ((void*)(pSrc)), ((RTS_SIZE)(szSize)))


#undef CAA_LIBS_IMP

#if CAA_CL2

	#ifndef CL2I_INCLUDE
		#define CL2I_INCLUDE "CAACanL2I.h"
	#endif

	#ifndef CL2_NNET
		#define CL2_NNET 		2	/* Max. Number of physical CANbus Networks */
	#endif

	#ifndef CL2_NPRIO
		#define CL2_NPRIO		8	/* Max. Number of TX priorities for the TX-Queue */
	#endif

	#ifndef CL2_NRXMSG
		#define CL2_NRXMSG 100  /* Max. Number of RX-Messages in Rx-Pool */
	#endif

	#ifndef CL2_SZRIDP
		#define CL2_SZRIDP 4096 /* RegId Pool Size */
	#endif

	#ifndef CL2_QUEUE_ADAPTION
		#define CL2_QUEUE_ADAPTION 1 /*Enable RxQueue extensions if neccessary*/
	#endif
	
	#ifndef CL2_CALLBACK
		#if CAA_CB
			#define CL2_CALLBACK 1 /*Enable event mechanism*/
		#else
			#define CL2_CALLBACK 0
		#endif
	#endif
	
#endif

#if CAA_MBM
	#ifndef MBM_CALLBACK
		#if CAA_CB
			#define MBM_CALLBACK 1 /*Enable event mechanism*/ 
		#else
			#define MBM_CALLBACK 0
		#endif
	#endif
#endif

#if CAA_RSM
	#if CAA_RSM_IMP
	#endif

	#ifndef RSM_MAX_HANDLES
		#define RSM_MAX_HANDLES 20
	#endif

	#undef CAA_RSM_IMP
#else
	#define RSM_CLASSCREATEFKT_NOTIMPLEMENTED
	#define RSM_CLASSFREE_NOTIMPLEMENTED
	#define RSM_CLASSDELETE_NOTIMPLEMENTED
	#define RSM_GETCLASS_NOTIMPLEMENTED
	#define RSM_GETCLASSINFO_NOTIMPLEMENTED
	#define RSM_GETPARENT_NOTIMPLEMENTED
	#define RSM_GETINFO_NOTIMPLEMENTED
	#define RSM_GETSUPPLIERVERSION_NOTIMPLEMENTED
	#define RSM_REGISTER_NOTIMPLEMENTED
	#define RSM_REGISTERNOCHECK_NOTIMPLEMENTED
	#define RSM_UNREGISTER_NOTIMPLEMENTED
#endif

#if CAA_ASM

	#define _ASYNC_IDLE 0
	#define _ASYNC_TASK 1
	#ifndef CAA_ASM_ASYNC_TYPE
		#define CAA_ASM_ASYNC_TYPE _ASYNC_TASK
	#endif

	#ifndef CAA_ASM_ASYNC_NUM_JOB_TASKS
		#define CAA_ASM_ASYNC_NUM_JOB_TASKS		5 /*Defines the number of Async taks waiting for a job, this is the number of jobs, which can be executed at the same time*/
	#endif

	#ifndef CAA_ASM_ASNC_NUM_JOB_TASK_GROUP
		#define CAA_ASM_ASNC_NUM_JOB_TASK_GROUP   0
	#endif
	
	#ifndef CAA_ASM_ASYNC_TASK_PRIORITY
		#define CAA_ASM_ASYNC_TASK_PRIORITY		TASKPRIO_NORMAL_BASE  /*Defines the number of Async taks waiting for a job*/
	#endif

	#ifndef CAA_ASM_ASYNC_TASK_SLEEPTIME
		#define CAA_ASM_ASYNC_TASK_SLEEPTIME	1  /*Defines the sleep time of the async task in msec*/
	#endif

	#ifndef ASM_NUM_OF_JOBS
		#define ASM_NUM_OF_JOBS		20		/* Number of Jobs */
	#endif
	#ifndef ASM_NUM_OF_WORKERS
		#define ASM_NUM_OF_WORKERS	50		/* Number of Workers*/
	#endif
	#undef CAA_ASM_IMP
#endif

#if CAA_TICKS
	#ifndef TICKS_RESEXP
		#define TICKS_RESEXP 1
	#endif
	
	#ifndef TICKS_RESNUM
		#define TICKS_RESNUM 2
	#endif
	
	#ifndef TICKS_RESDENOM
		#define TICKS_RESDENOM 3
	#endif
	
	#ifndef TICKS_MAXINTERVAL
		#define TICKS_MAXINTERVAL 10
	#endif
#endif

#if CAA_FILE
	#if CAA_FILE_IMP
		#define CAA_FILE_OPEN					CAAFileOpen
		#define CAA_FILE_COPY					CAAFileCopy
		#define CAA_FILE_DELETE					CAAFileDelete
		#define CAA_FILE_EOF					CAAFileEOF
		#define CAA_FILE_GETPOS					CAAFileGetPos
		#define CAA_FILE_GETSIZE				CAAFileGetSize
		#define CAA_FILE_GETTIME				CAAFileGetTime
		#define CAA_FILE_READ					CAAFileRead
		#define CAA_FILE_RENAME					CAAFileRename
		#define CAA_FILE_GETATTRIBUTE(x, h, y)	FILE_NOT_IMPLEMENTED
		#define CAA_FILE_SETATTRIBUTE(x, h, y)	FILE_NOT_IMPLEMENTED
		#define CAA_FILE_SETPOS					CAAFileSetPos
		#define CAA_FILE_WRITE					CAAFileWrite
		#define CAA_FILE_GETROOT(x, y)			FILE_NOT_IMPLEMENTED
		#define CAA_DIR_CREATE					CAADirCreate
		#define CAA_DIR_READ					CAADirRead
		#define CAA_DIR_OPEN					CAADirOpen
		#define CAA_DIR_REMOVE					CAADirRemove
		#define CAA_DIR_RENAME					CAADirRename
		#define CAA_DIR_CLOSE					CAL_SysDirClose
		#define CAA_FILE_CLOSE					CAL_SysFileClose
		#define CAA_FILE_FLUSH					CAAFileFlush
		#define CAA_DIR_COPY					CAADirCopy


		#ifndef CAA_FILE_GETJOBGROUP
			#define CAA_FILE_GETJOBGROUP(x,y)	CAA_hINVALID
		#endif	

		#ifndef CAA_FILE_INIT_IMPL
			#define CAA_FILE_INIT_IMPL
		#endif
	
		#ifndef CAA_FILE_EXIT_IMPL
			#define CAA_FILE_EXIT_IMPL
		#endif	
	#endif
	#undef CAA_FILE_IMP
#endif

#if CAA_COM
	#if CAA_COM_IMP
		#define CAA_COM_OPEN				CAAComOpen
		#define CAA_COM_WRITE				CAAComWrite
		#define CAA_COM_READ(x, h, y, z)	CAL_SysComRead(h, (unsigned char*)y->pBuffer, (RTS_UI32)y->szBuffer, z, 0);
		#define CAA_COM_CLOSE				CAL_SysComClose
	#endif
	#undef CAA_COM_IMP
#endif

#if CAA_TMR
	#if CAA_TMR_IMP
		#ifndef TMR_MAX_TIMER_TICK
			#define TMR_MAX_TIMER_TICK			RTS_TIMEOUT_INFINITE/*0xffffffffUL*/
		#endif
		#ifndef TMR_HW_TIMER_RESOLUTION
			#define TMR_HW_TIMER_RESOLUTION		1000UL
		#endif
		#ifndef TMR_PRIORITY
			#define TMR_PRIORITY	20
		#endif
	#endif
	#define _SYSTIMERV3 0
	#define _HW_TIMER 1
	#ifndef CAA_TMR_TICK_TYPE
		#define CAA_TMR_TICK_TYPE _SYSTIMERV3
	#endif
	#undef CAA_TMR_IMP
#endif

#if CAA_NBS
	#if CAA_NBS_IMP
		#define CAA_NBS_TCP_OPEN_SERVER			CAANBSTcpOpenServer
		#define CAA_NBS_TCP_OPEN_CLIENT			CAANBSTcpOpenClient
		#define CAA_NBS_TCP_OPEN_CONNECTION		CAANBSTcpOpenConnection
		#define CAA_NBS_TCP_WRITE				CAANBSTcpWrite
		#define CAA_NBS_TCP_READ				CAANBSTcpRead
		#define CAA_NBS_TCP_CLOSE				CAANBSTcpClose
		#define CAA_NBS_UDP_OPEN				CAANBSUdpOpen
		#define CAA_NBS_UDP_SEND				CAANBSUdpSend
		#define CAA_NBS_UDP_RECEIVE				CAANBSUdpReceive
		#define CAA_NBS_UDP_CLOSE(h)			CAL_SysSockClose(h)
		#define CAA_NBS_GETDATASIZE				CAANBSGetDataSize
	#endif
	#undef CAA_NBS_IMP
#endif

#undef CAA_CB_IMP
#undef CAA_TICKU_IMP
#undef CAA_MBM_IMP
#undef CAA_CL2_IMP
#undef CAA_RTCLK_IMP
#undef CAA_DTU_IMP
#undef CAA_CBM_IMP

#if !CAA_CB
#undef CAA_CB
#endif

#if !CAA_RSM
#undef CAA_RSM
#endif

#if !CAA_MBM
#undef CAA_MBM
#endif

#if !CAA_CL2
#undef CAA_CL2
#endif

#if !CAA_ASM
#undef CAA_ASM
#endif

#if !CAA_FILE
#undef CAA_FILE
#endif

#if !CAA_TICKS
#undef CAA_TICKS
#endif

#if !CAA_TICKU
#undef CAA_TICKU
#endif

#if !CAA_RTCLK
#undef CAA_RTCLK
#endif

#if !CAA_DTU
#undef CAA_DTU
#endif

#if !CAA_COM
#undef CAA_COM
#endif

#if !CAA_CBM
#undef CAA_CBM
#endif

#endif /* __CAADEFINESGENERIC__ */
