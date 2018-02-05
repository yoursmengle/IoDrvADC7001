#ifndef __SYSSPECIFIC__H__
#define __SYSSPECIFIC__H__
/*
 * ---Linux/QNX specific---
 * 
 * This file is included at the end of  CmpStd.h.
 * It may contain system specific include files etc. 
 * 
 */

#ifndef PTHREAD_STACK_MIN
	#define PTHREAD_STACK_MIN		0x4000
#endif

#define HANDLE2FD(h)	(int)(unsigned long)h
#define FD2HANDLE(fd)	(RTS_HANDLE)(unsigned long)(fd)

/* Debugging  ---------------------------------------------------------------------------------------- */
#ifdef RTS_DEBUG

#ifdef RTS_ASSERT
  #undef RTS_ASSERT
#endif
 #define RTS_ASSERT(expr) \
        if (!(expr)) DEBUGP("ASSERT: '%s'\n", #expr)

 #ifdef PLC_HANDLER
  #define DEBUGP(fmt, args...) \
        printf("%s[%d]: " fmt "\n", __FUNCTION__, __LINE__, ## args)
 #endif

#else
 #ifdef PLC_HANDLER
  #define DEBUGP(fmt, args...)
 #endif
#endif

#ifndef PLC_HANDLER

 extern int b_debug;

 #define DEBUGP(fmt, args...) \
        if(b_debug)printf("%s[%d]: " fmt "\n", __FUNCTION__, __LINE__, ## args)
 #define DEBUGP2(fmt, args...) \
        if(b_debug >= 2)printf("%s[%d]: " fmt "\n", __FUNCTION__, __LINE__, ## args)
#else
 #define DEBUGP2(fmt, args...)
#endif
/* --------------------------------------------------------------------------------------------------- */

#if defined(LINUX_SL_PRODUCT) && LINUX_SL_PRODUCT==RASPBERRYPI
	#define memcpy(a,b,c) CMUtlMemCpy(a,b,c)
#endif


extern int rts_system(const char *command);

#if defined (TRG_PPC) || defined (TRG_MIPS) || defined (QNX)
#define NO_CAS64_SUPPORT
#endif

#ifdef NO_CAS_SUPPORT
#define NO_CAS64_SUPPORT
#else
#define SYS_ATOMIC_COMPARE_AND_SWAP(piValue, iExchangeValue, iCompareValue, Result) \
	do { \
		if (__sync_bool_compare_and_swap((unsigned int *)piValue, (unsigned int)iCompareValue, (unsigned int)iExchangeValue)) \
			Result = ERR_OK; \
		else \
			Result = ERR_FAILED; \
	} while (0)
#endif

#ifndef NO_CAS64_SUPPORT
#define SYS_ATOMIC_COMPARE_AND_SWAP64(pi64Value, i64ExchangeValue, i64CompareValue, Result) \
			do { \
				if (__sync_bool_compare_and_swap((unsigned long long *)pi64Value, (unsigned long long)i64CompareValue, (unsigned long long)i64ExchangeValue)) \
					Result = ERR_OK; \
				else \
					Result = ERR_FAILED; \
			} while (0)
#endif

#endif	/*__SYSSPECIFIC__H__*/
