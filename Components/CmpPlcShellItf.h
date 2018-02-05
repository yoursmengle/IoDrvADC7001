 /**
 * <interfacename>CmpPlcShell</interfacename>
 * <description> 
 * This interface enables foreign components or an IEC Application, to register
 * a command handler and to send the output of the handler back to the PLC Shell.
 *
 * If the output of the command is big and has to be devided into several chunks
 * to be sent to the programming system, there are two possibilities to do that:
 *
 * 1) The command handler is dump and just sends the whole output, every time it
 *    is called, and doesn't care about the current "BlockID".
 *    In this case the PlcShell Component takes care about that. It calls the
 *    handler several times, but discards all output which doesn't belong to
 *    the current block.
 *
 * 2) The command handler is intelligent enough to prepare only the currently
 *    requested block.
 *    - First, the handler needs to call PlcShellSkip(...) to skip the number of
 *    blocks, which he doesn't need to send again.
 *    - Then, the handler will call PlcShellAppend(...) as much as necessary to
 *    prepare the currently sent block.
 *    - The handler has to call the function PlcShellSetEof(...) once with the
 *    number of bytes he want's to sent at all (not within the current request,
 *    but the total number of bytes, during all requests.)
 *
 * IMPLEMENTATION NOTES:
 * - The help description of a command is limited. So if you would like to provide
 *   a larger description:
 *   Provide a dedicated help command with "?" as a parameter and as result transport
 *   the extended help description!
 * 
 *	 Example:
 *		Command = "mycommand""
 *		Extended help = "mycommand ?"
 *   
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */



	
	
#ifndef _CMPPLCSHELLITF_H_
#define _CMPPLCSHELLITF_H_

#include "CmpStd.h"

 

 



#include "CmpEventCallbackItf.h"

/**
 * <category>Static defines</category>
 * <description>Predefined objects in the runtime</description>
 */
#define USERDB_OBJECT_PLCSHELL				"Device.PlcShell"

/**
 * <category>Static defines</category>
 * <description>Command name limit</description>
 */
#define PLCSHELL_MAX_CMD_LEN		32

/**
 * <category>Static defines</category>
 * <description>Help text limit</description>
 */
#define PLCSHELL_MAX_HELP_LEN		128

/**
 * <category>PlcShellCommandEntry</category>
 * <element name="szName" type="IN">Name of the command</element>
 * <element name="szHelp" type="IN">Help description of the command</element>
 * <element name="pfCallback" type="IN">Pointer to callback function for handling the command</element>
 * <element name="bIec" type="IN">0=C-Callback, 1=IEC-callback</element>
 */
typedef struct _PlcShellCommandEntry
{
	char szName[PLCSHELL_MAX_CMD_LEN];
	char szHelp[PLCSHELL_MAX_HELP_LEN];
	PFEVENTCALLBACKFUNCTION pfCallback;
	int bIec;
} PlcShellCommandEntry;


#define PLC_COMMAND			0x01
#define PLC_COMMAND_CANCEL		0x02
#define TAG_COMMAND			0x10
#define TAG_SESSION_ID			0x11
#define TAG_ARGS			0x12
#define TAG_BLOCKS			0x13

#define PLC_ACK				0x81
#define PLC_END				0x82
#define TAG_REPLY			0x20

/**
 * <category>Event parameter</category>
 * <element name="pszCommand" type="IN">Name of the Command to execute</element>
 * <element name="pszArguments" type="IN">Argument String, passed to command</element>
 * <element name="iBlockID" type="IN">Number of the current Block (or also number of already sent blocks)</element>
 * <element name="uiBlockSize" type="IN">Size of the communication buffer blocks</element>
 */
typedef struct
{
	char* pszCommand;
	char* pszArguments;
	int iBlockID;
	unsigned int uiBlockSize;
} EVTPARAM_PlcShellCommand;
#define EVTPARAMID_PlcShellCommand 0x0001
#define EVTVERSION_PlcShellCommand 0x0001

/**
 * <category>Event parameter</category>
 * <element name="pszCommand" type="IN">Name of the Command to execute</element>
 * <element name="bDisable" type="IN">Flag to disable the command</element>
 */
typedef struct
{
	char* pszCommand;
	RTS_BOOL bDisable;
} EVTPARAM_PlcShellCommandRegister;
#define EVTPARAMID_PlcShellCommandRegister 0x0001
#define EVTVERSION_PlcShellCommandRegister 0x0001

/**
 * <category>Events</category>
 * <description>This event is sent to all command handlers. It has to be handled only if the command name matches.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_PlcShellCommand</param>
 */
#define EVT_PlcShellCommand MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Events</category>
 * <description>
 *  This event is sent in CH_INIT_TASKS for each registered PlcShell command. It can be used to disable the command by setting
 *  the bDisable flag (see EVTPARAM_PlcShellCommandRegister).
 * </description>
 * <param name="pEventParam" type="IN">EVTPARAM_PlcShellCommandRegister</param>
 */
#define EVT_PlcShellCommandRegister MAKE_EVENTID(EVTCLASS_INFO, 2)


/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Append a line to the command output
 *
 * The passed parameter iBlockID, has TO be the BlockID, which
 * was passed to the command handler!
 * The communication layer automatically manages the split of
 * blocks. If you want to avoid this and write only the current
 * block that is sent to CoDeSys, use the function PlcShellSkip().
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagplcshellappend_struct
{
	RTS_IEC_STRING *pszString;			/* VAR_INPUT */	
	RTS_IEC_DINT iBlockID;				/* VAR_INPUT */	
	RTS_IEC_RESULT PlcShellAppend;		/* VAR_OUTPUT */	
} plcshellappend_struct;

void CDECL CDECL_EXT plcshellappend(plcshellappend_struct *p);
typedef void (CDECL CDECL_EXT* PFPLCSHELLAPPEND_IEC) (plcshellappend_struct *p);
#if defined(CMPPLCSHELL_NOTIMPLEMENTED) || defined(PLCSHELLAPPEND_NOTIMPLEMENTED)
	#define USE_plcshellappend
	#define EXT_plcshellappend
	#define GET_plcshellappend(fl)  ERR_NOTIMPLEMENTED
	#define CAL_plcshellappend(p0) 
	#define CHK_plcshellappend  FALSE
	#define EXP_plcshellappend  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_plcshellappend
	#define EXT_plcshellappend
	#define GET_plcshellappend(fl)  CAL_CMGETAPI( "plcshellappend" ) 
	#define CAL_plcshellappend  plcshellappend
	#define CHK_plcshellappend  TRUE
	#define EXP_plcshellappend  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellappend", (RTS_UINTPTR)plcshellappend, 1, 0x5F41CE4A, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPPLCSHELL_EXTERNAL)
	#define USE_plcshellappend
	#define EXT_plcshellappend
	#define GET_plcshellappend(fl)  CAL_CMGETAPI( "plcshellappend" ) 
	#define CAL_plcshellappend  plcshellappend
	#define CHK_plcshellappend  TRUE
	#define EXP_plcshellappend  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellappend", (RTS_UINTPTR)plcshellappend, 1, 0x5F41CE4A, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpPlcShellplcshellappend
	#define EXT_CmpPlcShellplcshellappend
	#define GET_CmpPlcShellplcshellappend  ERR_OK
	#define CAL_CmpPlcShellplcshellappend  plcshellappend
	#define CHK_CmpPlcShellplcshellappend  TRUE
	#define EXP_CmpPlcShellplcshellappend  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellappend", (RTS_UINTPTR)plcshellappend, 1, 0x5F41CE4A, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_plcshellappend
	#define EXT_plcshellappend
	#define GET_plcshellappend(fl)  CAL_CMGETAPI( "plcshellappend" ) 
	#define CAL_plcshellappend  plcshellappend
	#define CHK_plcshellappend  TRUE
	#define EXP_plcshellappend  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellappend", (RTS_UINTPTR)plcshellappend, 1, 0x5F41CE4A, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_plcshellappend  PFPLCSHELLAPPEND_IEC pfplcshellappend;
	#define EXT_plcshellappend  extern PFPLCSHELLAPPEND_IEC pfplcshellappend;
	#define GET_plcshellappend(fl)  s_pfCMGetAPI2( "plcshellappend", (RTS_VOID_FCTPTR *)&pfplcshellappend, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x5F41CE4A, 0x03050500)
	#define CAL_plcshellappend  pfplcshellappend
	#define CHK_plcshellappend  (pfplcshellappend != NULL)
	#define EXP_plcshellappend   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellappend", (RTS_UINTPTR)plcshellappend, 1, 0x5F41CE4A, 0x03050500) 
#endif


/**
 * Register a new Command Handler
 *
 * The command is sent TO the handler as an event OF the
 * EventMgr. So the CommandHandler needs to implement the
 * Interface ICmpEventCallback.
 * 
 * Note: For the ease of use, you can also derive your Command
 * Handler from the FB "CommandHandler" in this library. This
 * helps you in the registration and deregistration of the
 * handler.
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagplcshellregister_struct
{
	RTS_IEC_STRING *pszName;			/* VAR_INPUT */	
	RTS_IEC_STRING *pszHelp;			/* VAR_INPUT */	
	ICmpEventCallback *pICallback;		/* VAR_INPUT */	
	RTS_IEC_RESULT PlcShellRegister;	/* VAR_OUTPUT */	
} plcshellregister_struct;

void CDECL CDECL_EXT plcshellregister(plcshellregister_struct *p);
typedef void (CDECL CDECL_EXT* PFPLCSHELLREGISTER_IEC) (plcshellregister_struct *p);
#if defined(CMPPLCSHELL_NOTIMPLEMENTED) || defined(PLCSHELLREGISTER_NOTIMPLEMENTED)
	#define USE_plcshellregister
	#define EXT_plcshellregister
	#define GET_plcshellregister(fl)  ERR_NOTIMPLEMENTED
	#define CAL_plcshellregister(p0) 
	#define CHK_plcshellregister  FALSE
	#define EXP_plcshellregister  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_plcshellregister
	#define EXT_plcshellregister
	#define GET_plcshellregister(fl)  CAL_CMGETAPI( "plcshellregister" ) 
	#define CAL_plcshellregister  plcshellregister
	#define CHK_plcshellregister  TRUE
	#define EXP_plcshellregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellregister", (RTS_UINTPTR)plcshellregister, 1, 0x4A20A9BA, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPPLCSHELL_EXTERNAL)
	#define USE_plcshellregister
	#define EXT_plcshellregister
	#define GET_plcshellregister(fl)  CAL_CMGETAPI( "plcshellregister" ) 
	#define CAL_plcshellregister  plcshellregister
	#define CHK_plcshellregister  TRUE
	#define EXP_plcshellregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellregister", (RTS_UINTPTR)plcshellregister, 1, 0x4A20A9BA, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpPlcShellplcshellregister
	#define EXT_CmpPlcShellplcshellregister
	#define GET_CmpPlcShellplcshellregister  ERR_OK
	#define CAL_CmpPlcShellplcshellregister  plcshellregister
	#define CHK_CmpPlcShellplcshellregister  TRUE
	#define EXP_CmpPlcShellplcshellregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellregister", (RTS_UINTPTR)plcshellregister, 1, 0x4A20A9BA, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_plcshellregister
	#define EXT_plcshellregister
	#define GET_plcshellregister(fl)  CAL_CMGETAPI( "plcshellregister" ) 
	#define CAL_plcshellregister  plcshellregister
	#define CHK_plcshellregister  TRUE
	#define EXP_plcshellregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellregister", (RTS_UINTPTR)plcshellregister, 1, 0x4A20A9BA, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_plcshellregister  PFPLCSHELLREGISTER_IEC pfplcshellregister;
	#define EXT_plcshellregister  extern PFPLCSHELLREGISTER_IEC pfplcshellregister;
	#define GET_plcshellregister(fl)  s_pfCMGetAPI2( "plcshellregister", (RTS_VOID_FCTPTR *)&pfplcshellregister, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x4A20A9BA, 0x03050500)
	#define CAL_plcshellregister  pfplcshellregister
	#define CHK_plcshellregister  (pfplcshellregister != NULL)
	#define EXP_plcshellregister   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellregister", (RTS_UINTPTR)plcshellregister, 1, 0x4A20A9BA, 0x03050500) 
#endif


/**
 * Set EOF
 * 
 * This function should be called when the Command Handler
 * is finished with it's output.
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagplcshellseteof_struct
{
	RTS_IEC_RESULT PlcShellSetEof;		/* VAR_OUTPUT */	
} plcshellseteof_struct;

void CDECL CDECL_EXT plcshellseteof(plcshellseteof_struct *p);
typedef void (CDECL CDECL_EXT* PFPLCSHELLSETEOF_IEC) (plcshellseteof_struct *p);
#if defined(CMPPLCSHELL_NOTIMPLEMENTED) || defined(PLCSHELLSETEOF_NOTIMPLEMENTED)
	#define USE_plcshellseteof
	#define EXT_plcshellseteof
	#define GET_plcshellseteof(fl)  ERR_NOTIMPLEMENTED
	#define CAL_plcshellseteof(p0) 
	#define CHK_plcshellseteof  FALSE
	#define EXP_plcshellseteof  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_plcshellseteof
	#define EXT_plcshellseteof
	#define GET_plcshellseteof(fl)  CAL_CMGETAPI( "plcshellseteof" ) 
	#define CAL_plcshellseteof  plcshellseteof
	#define CHK_plcshellseteof  TRUE
	#define EXP_plcshellseteof  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellseteof", (RTS_UINTPTR)plcshellseteof, 1, 0x1C411A51, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPPLCSHELL_EXTERNAL)
	#define USE_plcshellseteof
	#define EXT_plcshellseteof
	#define GET_plcshellseteof(fl)  CAL_CMGETAPI( "plcshellseteof" ) 
	#define CAL_plcshellseteof  plcshellseteof
	#define CHK_plcshellseteof  TRUE
	#define EXP_plcshellseteof  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellseteof", (RTS_UINTPTR)plcshellseteof, 1, 0x1C411A51, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpPlcShellplcshellseteof
	#define EXT_CmpPlcShellplcshellseteof
	#define GET_CmpPlcShellplcshellseteof  ERR_OK
	#define CAL_CmpPlcShellplcshellseteof  plcshellseteof
	#define CHK_CmpPlcShellplcshellseteof  TRUE
	#define EXP_CmpPlcShellplcshellseteof  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellseteof", (RTS_UINTPTR)plcshellseteof, 1, 0x1C411A51, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_plcshellseteof
	#define EXT_plcshellseteof
	#define GET_plcshellseteof(fl)  CAL_CMGETAPI( "plcshellseteof" ) 
	#define CAL_plcshellseteof  plcshellseteof
	#define CHK_plcshellseteof  TRUE
	#define EXP_plcshellseteof  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellseteof", (RTS_UINTPTR)plcshellseteof, 1, 0x1C411A51, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_plcshellseteof  PFPLCSHELLSETEOF_IEC pfplcshellseteof;
	#define EXT_plcshellseteof  extern PFPLCSHELLSETEOF_IEC pfplcshellseteof;
	#define GET_plcshellseteof(fl)  s_pfCMGetAPI2( "plcshellseteof", (RTS_VOID_FCTPTR *)&pfplcshellseteof, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x1C411A51, 0x03050500)
	#define CAL_plcshellseteof  pfplcshellseteof
	#define CHK_plcshellseteof  (pfplcshellseteof != NULL)
	#define EXP_plcshellseteof   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellseteof", (RTS_UINTPTR)plcshellseteof, 1, 0x1C411A51, 0x03050500) 
#endif


/**
 * Skip a number of blocks in the output.
 * 
 * If a Command Handler sends a huge amount of output, it
 * might be necessary, that this output is splitted into
 * several blocks by the communication layer. When this
 * happens, the communication layer will discard everything,
 * but the current block from the output and recall the
 * Command Handler several times.
 * 
 * To avoid this, an intelligent Command Handler can generate
 * only the currently necessary block of output. For this,
 * it needs to "skip" all blocks, which are already sent, by
 * calling this function. Then it should write only that much
 * data, that they fit into one block and call PlcShellSetEof()
 * when it is finished.
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagplcshellskip_struct
{
	RTS_IEC_DINT iBlockID;				/* VAR_INPUT */	
	RTS_IEC_RESULT PlcShellSkip;		/* VAR_OUTPUT */	
} plcshellskip_struct;

void CDECL CDECL_EXT plcshellskip(plcshellskip_struct *p);
typedef void (CDECL CDECL_EXT* PFPLCSHELLSKIP_IEC) (plcshellskip_struct *p);
#if defined(CMPPLCSHELL_NOTIMPLEMENTED) || defined(PLCSHELLSKIP_NOTIMPLEMENTED)
	#define USE_plcshellskip
	#define EXT_plcshellskip
	#define GET_plcshellskip(fl)  ERR_NOTIMPLEMENTED
	#define CAL_plcshellskip(p0) 
	#define CHK_plcshellskip  FALSE
	#define EXP_plcshellskip  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_plcshellskip
	#define EXT_plcshellskip
	#define GET_plcshellskip(fl)  CAL_CMGETAPI( "plcshellskip" ) 
	#define CAL_plcshellskip  plcshellskip
	#define CHK_plcshellskip  TRUE
	#define EXP_plcshellskip  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellskip", (RTS_UINTPTR)plcshellskip, 1, 0xD5ADBD5C, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPPLCSHELL_EXTERNAL)
	#define USE_plcshellskip
	#define EXT_plcshellskip
	#define GET_plcshellskip(fl)  CAL_CMGETAPI( "plcshellskip" ) 
	#define CAL_plcshellskip  plcshellskip
	#define CHK_plcshellskip  TRUE
	#define EXP_plcshellskip  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellskip", (RTS_UINTPTR)plcshellskip, 1, 0xD5ADBD5C, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpPlcShellplcshellskip
	#define EXT_CmpPlcShellplcshellskip
	#define GET_CmpPlcShellplcshellskip  ERR_OK
	#define CAL_CmpPlcShellplcshellskip  plcshellskip
	#define CHK_CmpPlcShellplcshellskip  TRUE
	#define EXP_CmpPlcShellplcshellskip  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellskip", (RTS_UINTPTR)plcshellskip, 1, 0xD5ADBD5C, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_plcshellskip
	#define EXT_plcshellskip
	#define GET_plcshellskip(fl)  CAL_CMGETAPI( "plcshellskip" ) 
	#define CAL_plcshellskip  plcshellskip
	#define CHK_plcshellskip  TRUE
	#define EXP_plcshellskip  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellskip", (RTS_UINTPTR)plcshellskip, 1, 0xD5ADBD5C, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_plcshellskip  PFPLCSHELLSKIP_IEC pfplcshellskip;
	#define EXT_plcshellskip  extern PFPLCSHELLSKIP_IEC pfplcshellskip;
	#define GET_plcshellskip(fl)  s_pfCMGetAPI2( "plcshellskip", (RTS_VOID_FCTPTR *)&pfplcshellskip, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xD5ADBD5C, 0x03050500)
	#define CAL_plcshellskip  pfplcshellskip
	#define CHK_plcshellskip  (pfplcshellskip != NULL)
	#define EXP_plcshellskip   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellskip", (RTS_UINTPTR)plcshellskip, 1, 0xD5ADBD5C, 0x03050500) 
#endif


/**
 * Unregister a new Command Handler
 * 
 * Unregister the command handler, which is passed
 * to this function. Most likely this function will
 * be used in FB_exit, because every Command Handler
 * in IEC has to unregister when the application
 * is deleted.
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagplcshellunregister_struct
{
	ICmpEventCallback *pICallback;		/* VAR_INPUT */	
	RTS_IEC_RESULT PlcShellUnregister;	/* VAR_OUTPUT */	
} plcshellunregister_struct;

void CDECL CDECL_EXT plcshellunregister(plcshellunregister_struct *p);
typedef void (CDECL CDECL_EXT* PFPLCSHELLUNREGISTER_IEC) (plcshellunregister_struct *p);
#if defined(CMPPLCSHELL_NOTIMPLEMENTED) || defined(PLCSHELLUNREGISTER_NOTIMPLEMENTED)
	#define USE_plcshellunregister
	#define EXT_plcshellunregister
	#define GET_plcshellunregister(fl)  ERR_NOTIMPLEMENTED
	#define CAL_plcshellunregister(p0) 
	#define CHK_plcshellunregister  FALSE
	#define EXP_plcshellunregister  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_plcshellunregister
	#define EXT_plcshellunregister
	#define GET_plcshellunregister(fl)  CAL_CMGETAPI( "plcshellunregister" ) 
	#define CAL_plcshellunregister  plcshellunregister
	#define CHK_plcshellunregister  TRUE
	#define EXP_plcshellunregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellunregister", (RTS_UINTPTR)plcshellunregister, 1, 0x68D86B06, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPPLCSHELL_EXTERNAL)
	#define USE_plcshellunregister
	#define EXT_plcshellunregister
	#define GET_plcshellunregister(fl)  CAL_CMGETAPI( "plcshellunregister" ) 
	#define CAL_plcshellunregister  plcshellunregister
	#define CHK_plcshellunregister  TRUE
	#define EXP_plcshellunregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellunregister", (RTS_UINTPTR)plcshellunregister, 1, 0x68D86B06, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpPlcShellplcshellunregister
	#define EXT_CmpPlcShellplcshellunregister
	#define GET_CmpPlcShellplcshellunregister  ERR_OK
	#define CAL_CmpPlcShellplcshellunregister  plcshellunregister
	#define CHK_CmpPlcShellplcshellunregister  TRUE
	#define EXP_CmpPlcShellplcshellunregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellunregister", (RTS_UINTPTR)plcshellunregister, 1, 0x68D86B06, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_plcshellunregister
	#define EXT_plcshellunregister
	#define GET_plcshellunregister(fl)  CAL_CMGETAPI( "plcshellunregister" ) 
	#define CAL_plcshellunregister  plcshellunregister
	#define CHK_plcshellunregister  TRUE
	#define EXP_plcshellunregister  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellunregister", (RTS_UINTPTR)plcshellunregister, 1, 0x68D86B06, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_plcshellunregister  PFPLCSHELLUNREGISTER_IEC pfplcshellunregister;
	#define EXT_plcshellunregister  extern PFPLCSHELLUNREGISTER_IEC pfplcshellunregister;
	#define GET_plcshellunregister(fl)  s_pfCMGetAPI2( "plcshellunregister", (RTS_VOID_FCTPTR *)&pfplcshellunregister, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x68D86B06, 0x03050500)
	#define CAL_plcshellunregister  pfplcshellunregister
	#define CHK_plcshellunregister  (pfplcshellunregister != NULL)
	#define EXP_plcshellunregister   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"plcshellunregister", (RTS_UINTPTR)plcshellunregister, 1, 0x68D86B06, 0x03050500) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Register a new command handler</description>
 * <param name="pszName" type="IN">Name of the command.</param>
 * <param name="pszHelp" type="IN">Help Text of the command.</param>
 * <param name="pfCallbackFunction" type="IN">Event Callback, which is called, whenever a command occurs.</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL PlcShellRegister(char *pszName, char *pszHelp, PFEVENTCALLBACKFUNCTION pfCallbackFunction, int bIec);
typedef RTS_RESULT (CDECL * PFPLCSHELLREGISTER) (char *pszName, char *pszHelp, PFEVENTCALLBACKFUNCTION pfCallbackFunction, int bIec);
#if defined(CMPPLCSHELL_NOTIMPLEMENTED) || defined(PLCSHELLREGISTER_NOTIMPLEMENTED)
	#define USE_PlcShellRegister
	#define EXT_PlcShellRegister
	#define GET_PlcShellRegister(fl)  ERR_NOTIMPLEMENTED
	#define CAL_PlcShellRegister(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_PlcShellRegister  FALSE
	#define EXP_PlcShellRegister  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_PlcShellRegister
	#define EXT_PlcShellRegister
	#define GET_PlcShellRegister(fl)  CAL_CMGETAPI( "PlcShellRegister" ) 
	#define CAL_PlcShellRegister  PlcShellRegister
	#define CHK_PlcShellRegister  TRUE
	#define EXP_PlcShellRegister  CAL_CMEXPAPI( "PlcShellRegister" ) 
#elif defined(MIXED_LINK) && !defined(CMPPLCSHELL_EXTERNAL)
	#define USE_PlcShellRegister
	#define EXT_PlcShellRegister
	#define GET_PlcShellRegister(fl)  CAL_CMGETAPI( "PlcShellRegister" ) 
	#define CAL_PlcShellRegister  PlcShellRegister
	#define CHK_PlcShellRegister  TRUE
	#define EXP_PlcShellRegister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"PlcShellRegister", (RTS_UINTPTR)PlcShellRegister, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpPlcShellPlcShellRegister
	#define EXT_CmpPlcShellPlcShellRegister
	#define GET_CmpPlcShellPlcShellRegister  ERR_OK
	#define CAL_CmpPlcShellPlcShellRegister pICmpPlcShell->IPlcShellRegister
	#define CHK_CmpPlcShellPlcShellRegister (pICmpPlcShell != NULL)
	#define EXP_CmpPlcShellPlcShellRegister  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_PlcShellRegister
	#define EXT_PlcShellRegister
	#define GET_PlcShellRegister(fl)  CAL_CMGETAPI( "PlcShellRegister" ) 
	#define CAL_PlcShellRegister pICmpPlcShell->IPlcShellRegister
	#define CHK_PlcShellRegister (pICmpPlcShell != NULL)
	#define EXP_PlcShellRegister  CAL_CMEXPAPI( "PlcShellRegister" ) 
#else /* DYNAMIC_LINK */
	#define USE_PlcShellRegister  PFPLCSHELLREGISTER pfPlcShellRegister;
	#define EXT_PlcShellRegister  extern PFPLCSHELLREGISTER pfPlcShellRegister;
	#define GET_PlcShellRegister(fl)  s_pfCMGetAPI2( "PlcShellRegister", (RTS_VOID_FCTPTR *)&pfPlcShellRegister, (fl), 0, 0)
	#define CAL_PlcShellRegister  pfPlcShellRegister
	#define CHK_PlcShellRegister  (pfPlcShellRegister != NULL)
	#define EXP_PlcShellRegister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"PlcShellRegister", (RTS_UINTPTR)PlcShellRegister, 0, 0) 
#endif




/**
 * <description>Unregister a new command handler</description>
 * <param name="pfCallbackFunction" type="IN">Event Callback, which was registered with PlcShellRegister() before.</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL PlcShellUnregister(PFEVENTCALLBACKFUNCTION pfCallbackFunction);
typedef RTS_RESULT (CDECL * PFPLCSHELLUNREGISTER) (PFEVENTCALLBACKFUNCTION pfCallbackFunction);
#if defined(CMPPLCSHELL_NOTIMPLEMENTED) || defined(PLCSHELLUNREGISTER_NOTIMPLEMENTED)
	#define USE_PlcShellUnregister
	#define EXT_PlcShellUnregister
	#define GET_PlcShellUnregister(fl)  ERR_NOTIMPLEMENTED
	#define CAL_PlcShellUnregister(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_PlcShellUnregister  FALSE
	#define EXP_PlcShellUnregister  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_PlcShellUnregister
	#define EXT_PlcShellUnregister
	#define GET_PlcShellUnregister(fl)  CAL_CMGETAPI( "PlcShellUnregister" ) 
	#define CAL_PlcShellUnregister  PlcShellUnregister
	#define CHK_PlcShellUnregister  TRUE
	#define EXP_PlcShellUnregister  CAL_CMEXPAPI( "PlcShellUnregister" ) 
#elif defined(MIXED_LINK) && !defined(CMPPLCSHELL_EXTERNAL)
	#define USE_PlcShellUnregister
	#define EXT_PlcShellUnregister
	#define GET_PlcShellUnregister(fl)  CAL_CMGETAPI( "PlcShellUnregister" ) 
	#define CAL_PlcShellUnregister  PlcShellUnregister
	#define CHK_PlcShellUnregister  TRUE
	#define EXP_PlcShellUnregister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"PlcShellUnregister", (RTS_UINTPTR)PlcShellUnregister, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpPlcShellPlcShellUnregister
	#define EXT_CmpPlcShellPlcShellUnregister
	#define GET_CmpPlcShellPlcShellUnregister  ERR_OK
	#define CAL_CmpPlcShellPlcShellUnregister pICmpPlcShell->IPlcShellUnregister
	#define CHK_CmpPlcShellPlcShellUnregister (pICmpPlcShell != NULL)
	#define EXP_CmpPlcShellPlcShellUnregister  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_PlcShellUnregister
	#define EXT_PlcShellUnregister
	#define GET_PlcShellUnregister(fl)  CAL_CMGETAPI( "PlcShellUnregister" ) 
	#define CAL_PlcShellUnregister pICmpPlcShell->IPlcShellUnregister
	#define CHK_PlcShellUnregister (pICmpPlcShell != NULL)
	#define EXP_PlcShellUnregister  CAL_CMEXPAPI( "PlcShellUnregister" ) 
#else /* DYNAMIC_LINK */
	#define USE_PlcShellUnregister  PFPLCSHELLUNREGISTER pfPlcShellUnregister;
	#define EXT_PlcShellUnregister  extern PFPLCSHELLUNREGISTER pfPlcShellUnregister;
	#define GET_PlcShellUnregister(fl)  s_pfCMGetAPI2( "PlcShellUnregister", (RTS_VOID_FCTPTR *)&pfPlcShellUnregister, (fl), 0, 0)
	#define CAL_PlcShellUnregister  pfPlcShellUnregister
	#define CHK_PlcShellUnregister  (pfPlcShellUnregister != NULL)
	#define EXP_PlcShellUnregister  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"PlcShellUnregister", (RTS_UINTPTR)PlcShellUnregister, 0, 0) 
#endif




/**
 * <description>Set End Of File to current position.
 * This function should be called from a command handler, to signal that he is finished with his output.
 * If this function is not called upon the end of the command handler, the system implies that the end
 * was reached at the end of the handler.
 * </description>
 * <result>error code</result>
 */
RTS_RESULT CDECL PlcShellSetEof(unsigned int uiEofPos);
typedef RTS_RESULT (CDECL * PFPLCSHELLSETEOF) (unsigned int uiEofPos);
#if defined(CMPPLCSHELL_NOTIMPLEMENTED) || defined(PLCSHELLSETEOF_NOTIMPLEMENTED)
	#define USE_PlcShellSetEof
	#define EXT_PlcShellSetEof
	#define GET_PlcShellSetEof(fl)  ERR_NOTIMPLEMENTED
	#define CAL_PlcShellSetEof(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_PlcShellSetEof  FALSE
	#define EXP_PlcShellSetEof  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_PlcShellSetEof
	#define EXT_PlcShellSetEof
	#define GET_PlcShellSetEof(fl)  CAL_CMGETAPI( "PlcShellSetEof" ) 
	#define CAL_PlcShellSetEof  PlcShellSetEof
	#define CHK_PlcShellSetEof  TRUE
	#define EXP_PlcShellSetEof  CAL_CMEXPAPI( "PlcShellSetEof" ) 
#elif defined(MIXED_LINK) && !defined(CMPPLCSHELL_EXTERNAL)
	#define USE_PlcShellSetEof
	#define EXT_PlcShellSetEof
	#define GET_PlcShellSetEof(fl)  CAL_CMGETAPI( "PlcShellSetEof" ) 
	#define CAL_PlcShellSetEof  PlcShellSetEof
	#define CHK_PlcShellSetEof  TRUE
	#define EXP_PlcShellSetEof  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"PlcShellSetEof", (RTS_UINTPTR)PlcShellSetEof, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpPlcShellPlcShellSetEof
	#define EXT_CmpPlcShellPlcShellSetEof
	#define GET_CmpPlcShellPlcShellSetEof  ERR_OK
	#define CAL_CmpPlcShellPlcShellSetEof pICmpPlcShell->IPlcShellSetEof
	#define CHK_CmpPlcShellPlcShellSetEof (pICmpPlcShell != NULL)
	#define EXP_CmpPlcShellPlcShellSetEof  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_PlcShellSetEof
	#define EXT_PlcShellSetEof
	#define GET_PlcShellSetEof(fl)  CAL_CMGETAPI( "PlcShellSetEof" ) 
	#define CAL_PlcShellSetEof pICmpPlcShell->IPlcShellSetEof
	#define CHK_PlcShellSetEof (pICmpPlcShell != NULL)
	#define EXP_PlcShellSetEof  CAL_CMEXPAPI( "PlcShellSetEof" ) 
#else /* DYNAMIC_LINK */
	#define USE_PlcShellSetEof  PFPLCSHELLSETEOF pfPlcShellSetEof;
	#define EXT_PlcShellSetEof  extern PFPLCSHELLSETEOF pfPlcShellSetEof;
	#define GET_PlcShellSetEof(fl)  s_pfCMGetAPI2( "PlcShellSetEof", (RTS_VOID_FCTPTR *)&pfPlcShellSetEof, (fl), 0, 0)
	#define CAL_PlcShellSetEof  pfPlcShellSetEof
	#define CHK_PlcShellSetEof  (pfPlcShellSetEof != NULL)
	#define EXP_PlcShellSetEof  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"PlcShellSetEof", (RTS_UINTPTR)PlcShellSetEof, 0, 0) 
#endif




/**
 * <description>Check if end of shell command reached</description>
 * <param name="iBlockID" type="IN">ID of the next block (which is equal to the number of blocks to skip).</param>
 * <result>error code:
 *		ERR_OK:	End of shell command reached
 *		ERR_FAILED: Shell command in progress
 * </result>
 */
RTS_RESULT CDECL PlcShellEof(int iBlockID);
typedef RTS_RESULT (CDECL * PFPLCSHELLEOF) (int iBlockID);
#if defined(CMPPLCSHELL_NOTIMPLEMENTED) || defined(PLCSHELLEOF_NOTIMPLEMENTED)
	#define USE_PlcShellEof
	#define EXT_PlcShellEof
	#define GET_PlcShellEof(fl)  ERR_NOTIMPLEMENTED
	#define CAL_PlcShellEof(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_PlcShellEof  FALSE
	#define EXP_PlcShellEof  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_PlcShellEof
	#define EXT_PlcShellEof
	#define GET_PlcShellEof(fl)  CAL_CMGETAPI( "PlcShellEof" ) 
	#define CAL_PlcShellEof  PlcShellEof
	#define CHK_PlcShellEof  TRUE
	#define EXP_PlcShellEof  CAL_CMEXPAPI( "PlcShellEof" ) 
#elif defined(MIXED_LINK) && !defined(CMPPLCSHELL_EXTERNAL)
	#define USE_PlcShellEof
	#define EXT_PlcShellEof
	#define GET_PlcShellEof(fl)  CAL_CMGETAPI( "PlcShellEof" ) 
	#define CAL_PlcShellEof  PlcShellEof
	#define CHK_PlcShellEof  TRUE
	#define EXP_PlcShellEof  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"PlcShellEof", (RTS_UINTPTR)PlcShellEof, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpPlcShellPlcShellEof
	#define EXT_CmpPlcShellPlcShellEof
	#define GET_CmpPlcShellPlcShellEof  ERR_OK
	#define CAL_CmpPlcShellPlcShellEof pICmpPlcShell->IPlcShellEof
	#define CHK_CmpPlcShellPlcShellEof (pICmpPlcShell != NULL)
	#define EXP_CmpPlcShellPlcShellEof  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_PlcShellEof
	#define EXT_PlcShellEof
	#define GET_PlcShellEof(fl)  CAL_CMGETAPI( "PlcShellEof" ) 
	#define CAL_PlcShellEof pICmpPlcShell->IPlcShellEof
	#define CHK_PlcShellEof (pICmpPlcShell != NULL)
	#define EXP_PlcShellEof  CAL_CMEXPAPI( "PlcShellEof" ) 
#else /* DYNAMIC_LINK */
	#define USE_PlcShellEof  PFPLCSHELLEOF pfPlcShellEof;
	#define EXT_PlcShellEof  extern PFPLCSHELLEOF pfPlcShellEof;
	#define GET_PlcShellEof(fl)  s_pfCMGetAPI2( "PlcShellEof", (RTS_VOID_FCTPTR *)&pfPlcShellEof, (fl), 0, 0)
	#define CAL_PlcShellEof  pfPlcShellEof
	#define CHK_PlcShellEof  (pfPlcShellEof != NULL)
	#define EXP_PlcShellEof  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"PlcShellEof", (RTS_UINTPTR)PlcShellEof, 0, 0) 
#endif




/**
 * <description>Skip a number of blocks in the output buffer.
 * Skip the specified number of blocks in the output and imply, that we are starting now with the next
 * block, when we call PlcShellAppend() afterwards.
 * </description>
 * <param name="iBlockID" type="IN">ID of the next block (which is equal to the number of blocks to skip).</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL PlcShellSkip(int iBlockID);
typedef RTS_RESULT (CDECL * PFPLCSHELLSKIP) (int iBlockID);
#if defined(CMPPLCSHELL_NOTIMPLEMENTED) || defined(PLCSHELLSKIP_NOTIMPLEMENTED)
	#define USE_PlcShellSkip
	#define EXT_PlcShellSkip
	#define GET_PlcShellSkip(fl)  ERR_NOTIMPLEMENTED
	#define CAL_PlcShellSkip(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_PlcShellSkip  FALSE
	#define EXP_PlcShellSkip  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_PlcShellSkip
	#define EXT_PlcShellSkip
	#define GET_PlcShellSkip(fl)  CAL_CMGETAPI( "PlcShellSkip" ) 
	#define CAL_PlcShellSkip  PlcShellSkip
	#define CHK_PlcShellSkip  TRUE
	#define EXP_PlcShellSkip  CAL_CMEXPAPI( "PlcShellSkip" ) 
#elif defined(MIXED_LINK) && !defined(CMPPLCSHELL_EXTERNAL)
	#define USE_PlcShellSkip
	#define EXT_PlcShellSkip
	#define GET_PlcShellSkip(fl)  CAL_CMGETAPI( "PlcShellSkip" ) 
	#define CAL_PlcShellSkip  PlcShellSkip
	#define CHK_PlcShellSkip  TRUE
	#define EXP_PlcShellSkip  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"PlcShellSkip", (RTS_UINTPTR)PlcShellSkip, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpPlcShellPlcShellSkip
	#define EXT_CmpPlcShellPlcShellSkip
	#define GET_CmpPlcShellPlcShellSkip  ERR_OK
	#define CAL_CmpPlcShellPlcShellSkip pICmpPlcShell->IPlcShellSkip
	#define CHK_CmpPlcShellPlcShellSkip (pICmpPlcShell != NULL)
	#define EXP_CmpPlcShellPlcShellSkip  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_PlcShellSkip
	#define EXT_PlcShellSkip
	#define GET_PlcShellSkip(fl)  CAL_CMGETAPI( "PlcShellSkip" ) 
	#define CAL_PlcShellSkip pICmpPlcShell->IPlcShellSkip
	#define CHK_PlcShellSkip (pICmpPlcShell != NULL)
	#define EXP_PlcShellSkip  CAL_CMEXPAPI( "PlcShellSkip" ) 
#else /* DYNAMIC_LINK */
	#define USE_PlcShellSkip  PFPLCSHELLSKIP pfPlcShellSkip;
	#define EXT_PlcShellSkip  extern PFPLCSHELLSKIP pfPlcShellSkip;
	#define GET_PlcShellSkip(fl)  s_pfCMGetAPI2( "PlcShellSkip", (RTS_VOID_FCTPTR *)&pfPlcShellSkip, (fl), 0, 0)
	#define CAL_PlcShellSkip  pfPlcShellSkip
	#define CHK_PlcShellSkip  (pfPlcShellSkip != NULL)
	#define EXP_PlcShellSkip  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"PlcShellSkip", (RTS_UINTPTR)PlcShellSkip, 0, 0) 
#endif




/**
 * <description>Append a string to the output of the command.
 * In case, that our output buffer is not yet or not anymore within the specified Block, the output
 * is simply discarded. 
 * </description>
 * <param name="iBlockID" type="IN">ID of the next block (which is equal to the number of blocks to skip).</param>
 * <param name="iBlockID" type="IN">ID of the current block.</param>
 * <result>error code</result>
 */
RTS_RESULT CDECL PlcShellAppend(const char *pszString, int iBlockID);
typedef RTS_RESULT (CDECL * PFPLCSHELLAPPEND) (const char *pszString, int iBlockID);
#if defined(CMPPLCSHELL_NOTIMPLEMENTED) || defined(PLCSHELLAPPEND_NOTIMPLEMENTED)
	#define USE_PlcShellAppend
	#define EXT_PlcShellAppend
	#define GET_PlcShellAppend(fl)  ERR_NOTIMPLEMENTED
	#define CAL_PlcShellAppend(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_PlcShellAppend  FALSE
	#define EXP_PlcShellAppend  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_PlcShellAppend
	#define EXT_PlcShellAppend
	#define GET_PlcShellAppend(fl)  CAL_CMGETAPI( "PlcShellAppend" ) 
	#define CAL_PlcShellAppend  PlcShellAppend
	#define CHK_PlcShellAppend  TRUE
	#define EXP_PlcShellAppend  CAL_CMEXPAPI( "PlcShellAppend" ) 
#elif defined(MIXED_LINK) && !defined(CMPPLCSHELL_EXTERNAL)
	#define USE_PlcShellAppend
	#define EXT_PlcShellAppend
	#define GET_PlcShellAppend(fl)  CAL_CMGETAPI( "PlcShellAppend" ) 
	#define CAL_PlcShellAppend  PlcShellAppend
	#define CHK_PlcShellAppend  TRUE
	#define EXP_PlcShellAppend  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"PlcShellAppend", (RTS_UINTPTR)PlcShellAppend, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpPlcShellPlcShellAppend
	#define EXT_CmpPlcShellPlcShellAppend
	#define GET_CmpPlcShellPlcShellAppend  ERR_OK
	#define CAL_CmpPlcShellPlcShellAppend pICmpPlcShell->IPlcShellAppend
	#define CHK_CmpPlcShellPlcShellAppend (pICmpPlcShell != NULL)
	#define EXP_CmpPlcShellPlcShellAppend  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_PlcShellAppend
	#define EXT_PlcShellAppend
	#define GET_PlcShellAppend(fl)  CAL_CMGETAPI( "PlcShellAppend" ) 
	#define CAL_PlcShellAppend pICmpPlcShell->IPlcShellAppend
	#define CHK_PlcShellAppend (pICmpPlcShell != NULL)
	#define EXP_PlcShellAppend  CAL_CMEXPAPI( "PlcShellAppend" ) 
#else /* DYNAMIC_LINK */
	#define USE_PlcShellAppend  PFPLCSHELLAPPEND pfPlcShellAppend;
	#define EXT_PlcShellAppend  extern PFPLCSHELLAPPEND pfPlcShellAppend;
	#define GET_PlcShellAppend(fl)  s_pfCMGetAPI2( "PlcShellAppend", (RTS_VOID_FCTPTR *)&pfPlcShellAppend, (fl), 0, 0)
	#define CAL_PlcShellAppend  pfPlcShellAppend
	#define CHK_PlcShellAppend  (pfPlcShellAppend != NULL)
	#define EXP_PlcShellAppend  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"PlcShellAppend", (RTS_UINTPTR)PlcShellAppend, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFPLCSHELLREGISTER IPlcShellRegister;
 	PFPLCSHELLUNREGISTER IPlcShellUnregister;
 	PFPLCSHELLSETEOF IPlcShellSetEof;
 	PFPLCSHELLEOF IPlcShellEof;
 	PFPLCSHELLSKIP IPlcShellSkip;
 	PFPLCSHELLAPPEND IPlcShellAppend;
 } ICmpPlcShell_C;

#ifdef CPLUSPLUS
class ICmpPlcShell : public IBase
{
	public:
		virtual RTS_RESULT CDECL IPlcShellRegister(char *pszName, char *pszHelp, PFEVENTCALLBACKFUNCTION pfCallbackFunction, int bIec) =0;
		virtual RTS_RESULT CDECL IPlcShellUnregister(PFEVENTCALLBACKFUNCTION pfCallbackFunction) =0;
		virtual RTS_RESULT CDECL IPlcShellSetEof(unsigned int uiEofPos) =0;
		virtual RTS_RESULT CDECL IPlcShellEof(int iBlockID) =0;
		virtual RTS_RESULT CDECL IPlcShellSkip(int iBlockID) =0;
		virtual RTS_RESULT CDECL IPlcShellAppend(const char *pszString, int iBlockID) =0;
};
	#ifndef ITF_CmpPlcShell
		#define ITF_CmpPlcShell static ICmpPlcShell *pICmpPlcShell = NULL;
	#endif
	#define EXTITF_CmpPlcShell
#else	/*CPLUSPLUS*/
	typedef ICmpPlcShell_C		ICmpPlcShell;
	#ifndef ITF_CmpPlcShell
		#define ITF_CmpPlcShell
	#endif
	#define EXTITF_CmpPlcShell
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPPLCSHELLITF_H_*/
