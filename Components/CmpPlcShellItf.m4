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


SET_INTERFACE_NAME(`CmpPlcShell')
REF_ITF(`CmpEventCallbackItf.m4')

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

DEF_API(`void',`CDECL',`plcshellappend',`(plcshellappend_struct *p)',1,0x5F41CE4A,0x03050500)

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

DEF_API(`void',`CDECL',`plcshellregister',`(plcshellregister_struct *p)',1,0x4A20A9BA,0x03050500)

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

DEF_API(`void',`CDECL',`plcshellseteof',`(plcshellseteof_struct *p)',1,0x1C411A51,0x03050500)

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

DEF_API(`void',`CDECL',`plcshellskip',`(plcshellskip_struct *p)',1,0xD5ADBD5C,0x03050500)

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

DEF_API(`void',`CDECL',`plcshellunregister',`(plcshellunregister_struct *p)',1,0x68D86B06,0x03050500)

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
DEF_ITF_API(`RTS_RESULT', `CDECL', `PlcShellRegister', `(char *pszName, char *pszHelp, PFEVENTCALLBACKFUNCTION pfCallbackFunction, int bIec)')

/**
 * <description>Unregister a new command handler</description>
 * <param name="pfCallbackFunction" type="IN">Event Callback, which was registered with PlcShellRegister() before.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `PlcShellUnregister', `(PFEVENTCALLBACKFUNCTION pfCallbackFunction)')

/**
 * <description>Set End Of File to current position.
 * This function should be called from a command handler, to signal that he is finished with his output.
 * If this function is not called upon the end of the command handler, the system implies that the end
 * was reached at the end of the handler.
 * </description>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `PlcShellSetEof', `(unsigned int uiEofPos)')

/**
 * <description>Check if end of shell command reached</description>
 * <param name="iBlockID" type="IN">ID of the next block (which is equal to the number of blocks to skip).</param>
 * <result>error code:
 *		ERR_OK:	End of shell command reached
 *		ERR_FAILED: Shell command in progress
 * </result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `PlcShellEof', `(int iBlockID)')

/**
 * <description>Skip a number of blocks in the output buffer.
 * Skip the specified number of blocks in the output and imply, that we are starting now with the next
 * block, when we call PlcShellAppend() afterwards.
 * </description>
 * <param name="iBlockID" type="IN">ID of the next block (which is equal to the number of blocks to skip).</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `PlcShellSkip', `(int iBlockID)')

/**
 * <description>Append a string to the output of the command.
 * In case, that our output buffer is not yet or not anymore within the specified Block, the output
 * is simply discarded. 
 * </description>
 * <param name="iBlockID" type="IN">ID of the next block (which is equal to the number of blocks to skip).</param>
 * <param name="iBlockID" type="IN">ID of the current block.</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `PlcShellAppend', `(const char *pszString, int iBlockID)')

#ifdef __cplusplus
}
#endif
