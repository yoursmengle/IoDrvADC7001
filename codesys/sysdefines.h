#ifndef __SYSDEFINES__H__
#define __SYSDEFINES__H__

/*
 *
 * This file is included at the beginning of CmpStd.h.
 * It's intention is to contain system specific "#define"'s.
 *
 */

/* Set customer-specific defines to overload the defaults, below */
#include "targetdefines.h"
#include "profile.h"

#define CDECL
#define __cdecl CDECL /*necessary for sqlite in CmpCAAStorage*/
#define STDCALL 
#define HUGEPTR

/****** OS *****/

#undef WIN32
#if defined QNX
	#define SYSTARGET_OS_QNX
#else
	#define SYSTARGET_OS_LINUX
#endif

#define FILE_END_OF_LINE_DELIMITER 		"\n"
#define  SOCK_BIND_TWO_SOCKETS
#ifndef NO_SETVBUF
	#define UNBUFFERED_FILE_IO
#endif
#ifndef NO_C99
	#define C99_FLOAT_FUNCTIONS
#endif

#define RTS_STRUCTURED_EXCEPTION_HANDLING
#include <setjmp.h>
#define RTS_JMP_BUF 	sigjmp_buf
#define RTS_SETJMP(x)	sigsetjmp(x,1)
#define RTS_LONGJMP		siglongjmp
#ifndef NO_FENV
	#include <fenv.h>
	#define RTS_FP_BUF			fenv_t
	#define RTS_GET_FPENV(buf)	fegetenv(buf);
	#define RTS_SET_FPENV(buf)	fesetenv(buf);
#endif
/*** types ***/

#ifndef STDINT_H_UINTPTR_T_DEFINED
	#define STDINT_H_UINTPTR_T_DEFINED
#endif
typedef unsigned short RTS_WCHAR;
#define RTS_WCHAR_DEFINED
#ifndef PLC_HANDLER
	#define RTS_UNICODE
#endif
#ifndef MEMPOOL_8BYTE_ALIGNED
	#define MEMPOOL_8BYTE_ALIGNED
#endif

/*** some useful default sizes ***/

/*
 * Defines the available communication buffers in the
 * communication server.
 * 
 * BUFFERSIZE is the overall amount of memory to be used by
 *  all channels
 * MAXCHANNELS defines the number of channels that may be handled 
 *  concurrently. 
 *
 * Since each channel needs separate send and receive channels
 * the available communication buffer is BUFFERSIZE / (2*MAXCHANNELS)
 */
#ifndef NETSERVER_BUFFERSIZE
	#define NETSERVER_BUFFERSIZE 800000
#endif
#ifndef NETSERVER_MAXCHANNELS
	#define NETSERVER_MAXCHANNELS 4
#endif

/*** some useful default settings ***/

#ifdef LINUX
	#define SYSTASKVALUE_INT_TASK_STACKSIZE_DEFAULT		0x20000
	#define SCHEDULEVALUE_STRING_SCHEDULING_MODE_DEFAULT SCHEDULEVALUE_STRING_SCHEDULING_MODE_OS_SCHEDULE
	#define SCHEDULEVALUE_STRING_SCHEDULING_SUPERVISOR_DEFAULT	SCHEDULEVALUE_STRING_SCHEDULING_SUPERVISOR_SCHEDULETICK_TASK
#endif
#ifdef QNX
	#define SCHEDULEVALUE_STRING_SCHEDULING_MODE_DEFAULT SCHEDULEVALUE_STRING_SCHEDULING_MODE_OS_SCHEDULE
	#define SCHEDULEVALUE_STRING_SCHEDULING_SUPERVISOR_DEFAULT	SCHEDULEVALUE_STRING_SCHEDULING_SUPERVISOR_SCHEDULETICK_TASK
#endif

#define NUM_OF_STATIC_IEC_EVENTS		10


#define FILE_END_OF_LINE_DELIMITER "\n"
			
/*** NOTIMPLEMENTED ***/

#define CMPVISUCLIENTCONTROLLERHOST_NOTIMPLEMENTED
#define CMPSIL2_NOTIMPLEMENTED
#define SYSFILESTREAMFGETPOS_NOTIMPLEMENTED
#define SYSFILESTREAMFSETPOS_NOTIMPLEMENTED
#ifdef QNX
	#define SYSFLASH_NOTIMPLEMENTED
	#define CMPCODEMETER_NOTIMPLEMENTED
#endif
#if !defined (SYSTARGET_INTERNAL) && !defined (SYSTARGET_EXTERNAL)
	#define SYSTARGET_EXTERNAL
#endif


/*** targetvisu ***/

#if !defined (QT_TARGET_VISU) && !defined (QT_TARGET_VISU_PLUGIN) && !defined (EMBEDDED_TARGET_VISU)
	#define CMPTARGETVISU_NOTIMPLEMENTED 
#endif
#if !defined (EMBEDDED_TARGET_VISU)
	#define SYSGRAPHICNATIVE_NOTIMPLEMENTED
	#define SYSWINDOWNATIVE_NOTIMPLEMENTED
#endif

/*** plchandler ***/

#ifdef PLC_HANDLER
	#define SYSCPUDEBUGHANDLER_NOTIMPLEMENTED
	#define SYSCPUCALLIECFUNCWITHPARAMS_NOTIMPLEMENTED
	#undef RTS_UNICODE
#endif

/*** cpu specific ***/

#ifndef INTEL_BYTE_ORDER
#ifndef  MOTOROLA_BYTE_ORDER
	#define INTEL_BYTE_ORDER
#endif
#endif
#if defined  (MOTOROLA_BYTE_ORDER) && defined (INTEL_BYTE_ORDER)
	#error "choose only ONE byteorder, that's enough"
#endif

# if defined(__ARM_ARCH_6__)  || defined(__ARM_ARCH_6J__)  || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__) || defined(__ARM_ARCH_6T2__) || defined(__ARM_ARCH_6M__) 
	#define RTS_ARM_ARCH_VERSION 6
#elif defined(__ARM_ARCH_7__)  || defined(__ARM_ARCH_7A__)  || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7M__) 
	#define RTS_ARM_ARCH_VERSION 7
#else
	#define RTS_ARM_ARCH_VERSION 5
#endif

/*** compact ***/

#define SETTG_ENTRIES_INT \
       {"CmpAppEmbedded", "Bootproject.RunInFlash", 1}, \
       {"CmpAppEmbedded", "Bootproject.CreateOnDownload", 1}, \
       {"SysMem", "Linux.Memlock", 0}, \
       {"SysExcept", "Linux.DisableFpuOverflowException", 1}, \
       {"SysExcept", "Linux.DisableFpuUnderflowException", 1}, \
       {"SysExcept", "Linux.DisableFpuInvaliOperationException", 1}, \
       {0, 0, 0}

#define FLASH_SIZE    0x40000
#define FLASH_START_ADDRESS   0x40000

#define FILE1_SIZE    FLASH_SIZE
/* Filemap */
#define FILE_MAP FILE_DESC m_FileSystem[] = \
{ \
	/*Name					Offset				MaxSize				read index	write index */\
	{"Application.app",		0x0,				FILE1_SIZE,			0xFFFFFFFF, 0xFFFFFFFF},\
};

#endif /* __SYSDEFINES__H__ */

