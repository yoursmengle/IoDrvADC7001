 /**
 * <interfacename>SysWindowNative</interfacename>
 * <description> 
 *	<p>SysWindowNative interface is projected for implementing a simple window management system that is not based on
 *	operating system functionality. This interface is an extension of the interface SysWindow.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSWINDOWNATIVEITF_H_
#define _SYSWINDOWNATIVEITF_H_

#include "CmpStd.h"

 

 




/* Init routines for OS specific modules */
RTS_RESULT CDECL SysWindowNativeOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysWindowNativeOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

typedef enum
{
	SYSWIN_INPUT_DUMMY,		/* just a dummy event, will not be handled; can be used for a cycle in the message loop*/
	SYSWIN_INPUT_TIMER,
	SYSWIN_INPUT_MOUSE,
	SYSWIN_INPUT_KEY,
	SYSWIN_INPUT_KEYCHAR,	/* this event will be raised when a character key is pressed, It might be raised additionally to KEY(Down, Up) */
	SYSWIN_INPUT_INVALIDATION,
	SYSWIN_INPUT_NOTIFICATION
} SysWindowNativeInputType;

typedef enum
{
	SYSWIN_MOUSE_DOWN,
	SYSWIN_MOUSE_UP,
	SYSWIN_MOUSE_MOVE
} SysWindowNativeMouseEventType;

typedef enum
{
	SYSWIN_KEY_DOWN,
	SYSWIN_KEY_UP
} SysWindowNativeKeyEventType;

typedef struct _tagSysWindowNativeTimer
{
	int iTimerNumber;
} SysWindowNativeInputTimer;

typedef struct _tagSysWindowNativeInputMouse
{
	SysWindowNativeMouseEventType	eventType;
	/* For raising events, the coordinates are in absolute (-> screen relative coordinates) */
	int								x;
	/* For raising events, the coordinates are in absolute (-> screen relative coordinates) */
	int								y;
} SysWindowNativeInputMouse;

typedef struct _tagSysWindowNativeInputKey
{
	SysWindowNativeKeyEventType		eventType;
	/* The keycodes have values that are defined in the header SysWindowKeyMapping.h */
	int								iKeyCode;
	/* The values of the modifiers are defined in the header SysWindowKeyMapping.h */
	unsigned int					uiModifiers;
} SysWindowNativeInputKey;

typedef struct _tagSysWindowNativeInputKeyChar
{
	/* The character that was pressed. Will only be raised when there are according characters to the pressed keys. */
	RTS_WCHAR						wcKey;
	/* not yet used and not yet defined */
	unsigned int					uiFlags;
} SysWindowNativeInputKeyChar;

typedef struct _tagSysWindowNativeInputNotification
{
	/* specifies the invalidation area in screen coordinates; evaluation of these coordinates is not yet implemented! */
	RTS_UI32 notificationCode;
	void* notificationParam;
} SysWindowNativeInputNotification;

typedef struct _tagSysWindowNativeInputInvalidation
{
	/* specifies the invalidation area in screen coordinates; evaluation of these coordinates is not yet implemented! */
	short x, y, width, height;
} SysWindowNativeInputInvalidation;

typedef struct _tagSysWindowNativeInput
{
	SysWindowNativeInputType	inputType;
	union
	{
		SysWindowNativeInputTimer	timerInput;
		SysWindowNativeInputMouse	mouseInput;
		SysWindowNativeInputKey		keyInput;
		SysWindowNativeInputKeyChar	keyCharInput;
		SysWindowNativeInputInvalidation	invalidation;
		SysWindowNativeInputNotification notification;
	} info;
} SysWindowNativeInput;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Returns a handle to the display context of the given window. The returned handle is still owned by
 *	the window so there is no need to release this handle after usage.</description>
 * <param name="hWindow" type="IN">The window to get the display context of.</param>
 * <param name="pResult" type="OUT">Optionally returns an error code</param>
 * <result>The handle to the native display context or <see>RTS_INVALID_HANDLE</see> in case of errors.</result>
 */
RTS_HANDLE CDECL SysWindowNativeGetDisplayDeviceContext(RTS_HANDLE hWindow, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFSYSWINDOWNATIVEGETDISPLAYDEVICECONTEXT) (RTS_HANDLE hWindow, RTS_RESULT *pResult);
#if defined(SYSWINDOWNATIVE_NOTIMPLEMENTED) || defined(SYSWINDOWNATIVEGETDISPLAYDEVICECONTEXT_NOTIMPLEMENTED)
	#define USE_SysWindowNativeGetDisplayDeviceContext
	#define EXT_SysWindowNativeGetDisplayDeviceContext
	#define GET_SysWindowNativeGetDisplayDeviceContext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowNativeGetDisplayDeviceContext(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysWindowNativeGetDisplayDeviceContext  FALSE
	#define EXP_SysWindowNativeGetDisplayDeviceContext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowNativeGetDisplayDeviceContext
	#define EXT_SysWindowNativeGetDisplayDeviceContext
	#define GET_SysWindowNativeGetDisplayDeviceContext(fl)  CAL_CMGETAPI( "SysWindowNativeGetDisplayDeviceContext" ) 
	#define CAL_SysWindowNativeGetDisplayDeviceContext  SysWindowNativeGetDisplayDeviceContext
	#define CHK_SysWindowNativeGetDisplayDeviceContext  TRUE
	#define EXP_SysWindowNativeGetDisplayDeviceContext  CAL_CMEXPAPI( "SysWindowNativeGetDisplayDeviceContext" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOWNATIVE_EXTERNAL)
	#define USE_SysWindowNativeGetDisplayDeviceContext
	#define EXT_SysWindowNativeGetDisplayDeviceContext
	#define GET_SysWindowNativeGetDisplayDeviceContext(fl)  CAL_CMGETAPI( "SysWindowNativeGetDisplayDeviceContext" ) 
	#define CAL_SysWindowNativeGetDisplayDeviceContext  SysWindowNativeGetDisplayDeviceContext
	#define CHK_SysWindowNativeGetDisplayDeviceContext  TRUE
	#define EXP_SysWindowNativeGetDisplayDeviceContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowNativeGetDisplayDeviceContext", (RTS_UINTPTR)SysWindowNativeGetDisplayDeviceContext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowNativeSysWindowNativeGetDisplayDeviceContext
	#define EXT_SysWindowNativeSysWindowNativeGetDisplayDeviceContext
	#define GET_SysWindowNativeSysWindowNativeGetDisplayDeviceContext  ERR_OK
	#define CAL_SysWindowNativeSysWindowNativeGetDisplayDeviceContext(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindowNative->ISysWindowNativeGetDisplayDeviceContext(p1) : ((ISysWindowNative*)(((IBase*)p0)->QueryInterface((IBase *)p0, ITFID_ISysWindowNative, (RTS_RESULT *)1)))->ISysWindowNativeGetDisplayDeviceContext(p1))
	#define CHK_SysWindowNativeSysWindowNativeGetDisplayDeviceContext  (pISysWindowNative != NULL)
	#define EXP_SysWindowNativeSysWindowNativeGetDisplayDeviceContext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowNativeGetDisplayDeviceContext
	#define EXT_SysWindowNativeGetDisplayDeviceContext
	#define GET_SysWindowNativeGetDisplayDeviceContext(fl)  CAL_CMGETAPI( "SysWindowNativeGetDisplayDeviceContext" ) 
	#define CAL_SysWindowNativeGetDisplayDeviceContext(p0,p1)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindowNative->ISysWindowNativeGetDisplayDeviceContext(p1) : ((ISysWindowNative*)(((IBase*)p0)->QueryInterface((IBase *)p0, ITFID_ISysWindowNative, (RTS_RESULT *)1)))->ISysWindowNativeGetDisplayDeviceContext(p1))
	#define CHK_SysWindowNativeGetDisplayDeviceContext  (pISysWindowNative != NULL)
	#define EXP_SysWindowNativeGetDisplayDeviceContext  CAL_CMEXPAPI( "SysWindowNativeGetDisplayDeviceContext" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowNativeGetDisplayDeviceContext  PFSYSWINDOWNATIVEGETDISPLAYDEVICECONTEXT pfSysWindowNativeGetDisplayDeviceContext;
	#define EXT_SysWindowNativeGetDisplayDeviceContext  extern PFSYSWINDOWNATIVEGETDISPLAYDEVICECONTEXT pfSysWindowNativeGetDisplayDeviceContext;
	#define GET_SysWindowNativeGetDisplayDeviceContext(fl)  s_pfCMGetAPI2( "SysWindowNativeGetDisplayDeviceContext", (RTS_VOID_FCTPTR *)&pfSysWindowNativeGetDisplayDeviceContext, (fl), 0, 0)
	#define CAL_SysWindowNativeGetDisplayDeviceContext  pfSysWindowNativeGetDisplayDeviceContext
	#define CHK_SysWindowNativeGetDisplayDeviceContext  (pfSysWindowNativeGetDisplayDeviceContext != NULL)
	#define EXP_SysWindowNativeGetDisplayDeviceContext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowNativeGetDisplayDeviceContext", (RTS_UINTPTR)SysWindowNativeGetDisplayDeviceContext, 0, 0) 
#endif




/**
 * <description>This method can be called to raise an input event that can be evaluated by the visualization for example. 
 *	The method may be called from arbitrary tasks.</description>
 * <param name="pInput" type="IN">A pointer to the structure describing the input event.</param>
 * <result>A result code.</result>
 */
RTS_RESULT CDECL SysWindowNativeRaiseInput(SysWindowNativeInput* pInput);
typedef RTS_RESULT (CDECL * PFSYSWINDOWNATIVERAISEINPUT) (SysWindowNativeInput* pInput);
#if defined(SYSWINDOWNATIVE_NOTIMPLEMENTED) || defined(SYSWINDOWNATIVERAISEINPUT_NOTIMPLEMENTED)
	#define USE_SysWindowNativeRaiseInput
	#define EXT_SysWindowNativeRaiseInput
	#define GET_SysWindowNativeRaiseInput(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowNativeRaiseInput(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowNativeRaiseInput  FALSE
	#define EXP_SysWindowNativeRaiseInput  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowNativeRaiseInput
	#define EXT_SysWindowNativeRaiseInput
	#define GET_SysWindowNativeRaiseInput(fl)  CAL_CMGETAPI( "SysWindowNativeRaiseInput" ) 
	#define CAL_SysWindowNativeRaiseInput  SysWindowNativeRaiseInput
	#define CHK_SysWindowNativeRaiseInput  TRUE
	#define EXP_SysWindowNativeRaiseInput  CAL_CMEXPAPI( "SysWindowNativeRaiseInput" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOWNATIVE_EXTERNAL)
	#define USE_SysWindowNativeRaiseInput
	#define EXT_SysWindowNativeRaiseInput
	#define GET_SysWindowNativeRaiseInput(fl)  CAL_CMGETAPI( "SysWindowNativeRaiseInput" ) 
	#define CAL_SysWindowNativeRaiseInput  SysWindowNativeRaiseInput
	#define CHK_SysWindowNativeRaiseInput  TRUE
	#define EXP_SysWindowNativeRaiseInput  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowNativeRaiseInput", (RTS_UINTPTR)SysWindowNativeRaiseInput, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowNativeSysWindowNativeRaiseInput
	#define EXT_SysWindowNativeSysWindowNativeRaiseInput
	#define GET_SysWindowNativeSysWindowNativeRaiseInput  ERR_OK
	#define CAL_SysWindowNativeSysWindowNativeRaiseInput pISysWindowNative->ISysWindowNativeRaiseInput
	#define CHK_SysWindowNativeSysWindowNativeRaiseInput (pISysWindowNative != NULL)
	#define EXP_SysWindowNativeSysWindowNativeRaiseInput  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowNativeRaiseInput
	#define EXT_SysWindowNativeRaiseInput
	#define GET_SysWindowNativeRaiseInput(fl)  CAL_CMGETAPI( "SysWindowNativeRaiseInput" ) 
	#define CAL_SysWindowNativeRaiseInput pISysWindowNative->ISysWindowNativeRaiseInput
	#define CHK_SysWindowNativeRaiseInput (pISysWindowNative != NULL)
	#define EXP_SysWindowNativeRaiseInput  CAL_CMEXPAPI( "SysWindowNativeRaiseInput" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowNativeRaiseInput  PFSYSWINDOWNATIVERAISEINPUT pfSysWindowNativeRaiseInput;
	#define EXT_SysWindowNativeRaiseInput  extern PFSYSWINDOWNATIVERAISEINPUT pfSysWindowNativeRaiseInput;
	#define GET_SysWindowNativeRaiseInput(fl)  s_pfCMGetAPI2( "SysWindowNativeRaiseInput", (RTS_VOID_FCTPTR *)&pfSysWindowNativeRaiseInput, (fl), 0, 0)
	#define CAL_SysWindowNativeRaiseInput  pfSysWindowNativeRaiseInput
	#define CHK_SysWindowNativeRaiseInput  (pfSysWindowNativeRaiseInput != NULL)
	#define EXP_SysWindowNativeRaiseInput  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowNativeRaiseInput", (RTS_UINTPTR)SysWindowNativeRaiseInput, 0, 0) 
#endif




/**
 * <description>This method will be called cyclically from the context of the IEC-Visualization-Task in environments using the embedded
 *	targetvisualization. The call is intended to do the processing of the pending input events as well as painting the content of the visualization.
 *	</description>
 * <param name="hWindow" type="IN">The handle of the window that should be processed.</param>
 * <result>A result code.</result>
 */
RTS_RESULT CDECL SysWindowNativeProcessCyclic(RTS_HANDLE hWindow);
typedef RTS_RESULT (CDECL * PFSYSWINDOWNATIVEPROCESSCYCLIC) (RTS_HANDLE hWindow);
#if defined(SYSWINDOWNATIVE_NOTIMPLEMENTED) || defined(SYSWINDOWNATIVEPROCESSCYCLIC_NOTIMPLEMENTED)
	#define USE_SysWindowNativeProcessCyclic
	#define EXT_SysWindowNativeProcessCyclic
	#define GET_SysWindowNativeProcessCyclic(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysWindowNativeProcessCyclic(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysWindowNativeProcessCyclic  FALSE
	#define EXP_SysWindowNativeProcessCyclic  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysWindowNativeProcessCyclic
	#define EXT_SysWindowNativeProcessCyclic
	#define GET_SysWindowNativeProcessCyclic(fl)  CAL_CMGETAPI( "SysWindowNativeProcessCyclic" ) 
	#define CAL_SysWindowNativeProcessCyclic  SysWindowNativeProcessCyclic
	#define CHK_SysWindowNativeProcessCyclic  TRUE
	#define EXP_SysWindowNativeProcessCyclic  CAL_CMEXPAPI( "SysWindowNativeProcessCyclic" ) 
#elif defined(MIXED_LINK) && !defined(SYSWINDOWNATIVE_EXTERNAL)
	#define USE_SysWindowNativeProcessCyclic
	#define EXT_SysWindowNativeProcessCyclic
	#define GET_SysWindowNativeProcessCyclic(fl)  CAL_CMGETAPI( "SysWindowNativeProcessCyclic" ) 
	#define CAL_SysWindowNativeProcessCyclic  SysWindowNativeProcessCyclic
	#define CHK_SysWindowNativeProcessCyclic  TRUE
	#define EXP_SysWindowNativeProcessCyclic  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowNativeProcessCyclic", (RTS_UINTPTR)SysWindowNativeProcessCyclic, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysWindowNativeSysWindowNativeProcessCyclic
	#define EXT_SysWindowNativeSysWindowNativeProcessCyclic
	#define GET_SysWindowNativeSysWindowNativeProcessCyclic  ERR_OK
	#define CAL_SysWindowNativeSysWindowNativeProcessCyclic(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindowNative->ISysWindowNativeProcessCyclic() : ((ISysWindowNative*)(((IBase*)p0)->QueryInterface((IBase *)p0, ITFID_ISysWindowNative, (RTS_RESULT *)1)))->ISysWindowNativeProcessCyclic())
	#define CHK_SysWindowNativeSysWindowNativeProcessCyclic  (pISysWindowNative != NULL)
	#define EXP_SysWindowNativeSysWindowNativeProcessCyclic  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysWindowNativeProcessCyclic
	#define EXT_SysWindowNativeProcessCyclic
	#define GET_SysWindowNativeProcessCyclic(fl)  CAL_CMGETAPI( "SysWindowNativeProcessCyclic" ) 
	#define CAL_SysWindowNativeProcessCyclic(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pISysWindowNative->ISysWindowNativeProcessCyclic() : ((ISysWindowNative*)(((IBase*)p0)->QueryInterface((IBase *)p0, ITFID_ISysWindowNative, (RTS_RESULT *)1)))->ISysWindowNativeProcessCyclic())
	#define CHK_SysWindowNativeProcessCyclic  (pISysWindowNative != NULL)
	#define EXP_SysWindowNativeProcessCyclic  CAL_CMEXPAPI( "SysWindowNativeProcessCyclic" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysWindowNativeProcessCyclic  PFSYSWINDOWNATIVEPROCESSCYCLIC pfSysWindowNativeProcessCyclic;
	#define EXT_SysWindowNativeProcessCyclic  extern PFSYSWINDOWNATIVEPROCESSCYCLIC pfSysWindowNativeProcessCyclic;
	#define GET_SysWindowNativeProcessCyclic(fl)  s_pfCMGetAPI2( "SysWindowNativeProcessCyclic", (RTS_VOID_FCTPTR *)&pfSysWindowNativeProcessCyclic, (fl), 0, 0)
	#define CAL_SysWindowNativeProcessCyclic  pfSysWindowNativeProcessCyclic
	#define CHK_SysWindowNativeProcessCyclic  (pfSysWindowNativeProcessCyclic != NULL)
	#define EXP_SysWindowNativeProcessCyclic  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysWindowNativeProcessCyclic", (RTS_UINTPTR)SysWindowNativeProcessCyclic, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif


typedef struct
{
	IBase_C *pBase;
	PFSYSWINDOWNATIVEGETDISPLAYDEVICECONTEXT ISysWindowNativeGetDisplayDeviceContext;
 	PFSYSWINDOWNATIVERAISEINPUT ISysWindowNativeRaiseInput;
 	PFSYSWINDOWNATIVEPROCESSCYCLIC ISysWindowNativeProcessCyclic;
 } ISysWindowNative_C;

#ifdef CPLUSPLUS
class ISysWindowNative : public IBase
{
	public:
		virtual RTS_HANDLE CDECL ISysWindowNativeGetDisplayDeviceContext(RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL ISysWindowNativeRaiseInput(SysWindowNativeInput* pInput) =0;
		virtual RTS_RESULT CDECL ISysWindowNativeProcessCyclic(void) =0;
};
	#ifndef ITF_SysWindowNative
		#define ITF_SysWindowNative static ISysWindowNative *pISysWindowNative = NULL;
	#endif
	#define EXTITF_SysWindowNative
#else	/*CPLUSPLUS*/
	typedef ISysWindowNative_C		ISysWindowNative;
	#ifndef ITF_SysWindowNative
		#define ITF_SysWindowNative
	#endif
	#define EXTITF_SysWindowNative
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSWINDOWNATIVEITF_H_*/
