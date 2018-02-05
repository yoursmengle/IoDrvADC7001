/**
 * <interfacename>CmpVisuHandler</interfacename>
 * <description> 
 *	Interface for the visu handler component.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpVisuHandler')

REF_ITF(`CmpFileTransferItf.m4')

#include "CmpItf.h"
#include "SysGraphicBase.h"

#define ERR_INVALIDTYPE		11001		/* the same as in VisuElemBase.library, will be returned to clients! */

typedef RTS_IEC_DWORD	ExternID;
typedef RTS_IEC_WORD	IecID;


#define VISU_EVENT_ADDITIONALDATASIZE_SIZE_MASK				0x00ffffff
#define VISU_EVENT_ADDITIONALDATASIZE_DOSYSMEMFREE_MASK		0x01000000

/** constants for eventtags
*
*/
#define VISU_ET_NOTHING 							0x00000000
#define	VISU_ET_MONITORING							0x00000001
#define	VISU_ET_MOUSEDOWN							0x00000002
#define	VISU_ET_MOUSEUP								0x00000004
#define	VISU_ET_MOUSEDBLCLK							0x00000008
#define VISU_ET_MOUSEMOVE							0x00000010
#define VISU_ET_MOUSEOUT							0x00001000
#define VISU_ET_TOUCHSTART							0x00001001
#define VISU_ET_TOUCHSTOP							0x00001002
#define	VISU_ET_KEYDOWN								0x00000080
#define	VISU_ET_KEYUP								0x00000100
#define VISU_ET_CHAR								0x00000101
#define	VISU_ET_INPUTRESULT							0x00000200
#define VISU_ET_INVALIDATETOOLTIP					0x00000201
#define VISU_ET_FILEDLGRESULT						0x00000202
#define VISU_ET_CALLNATIVECONTROLMETHODRESULT		0x00000203
#define VISU_ET_SETCLIENTSIZE						0x00000204
#define VISU_ET_CLIENTREQUEST						0x00000205
#define VISU_ET_MEASURESTRINGRESULT					0x00000206
#define VISU_ET_MEASURESTRING2RESULT				0x00000207
#define VISU_ET_FILETRANSFERSTARTED					0x00000209
#define VISU_ET_FILETRANSFERRESULT					0x00000210
#define VISU_ET_FILESTREAMINGDLGRESULT				0x00000211
#define VISU_ET_FILESTREAMINGDATA					0x00000212
#define VISU_ET_FILESTREAMINGRESULT					0x00000213		/* Sent only in case of failure when streaming data from the plc to the visualization */
#define VISU_ET_PRINT								0x00000400
#define	VISU_ET_GESTURE_SPREADPINCH					0x00000801		/* all gesture events have the 0x800 bit set; this bit should not be set in other event tags */
#define	VISU_ET_GESTURE_PAN							0x00000802
#define	VISU_ET_GESTURE_FLICK						0x00000803
#define	VISU_ET_GESTURE_IECTOUCH					0x00000804
#define VISU_ET_GESTURE_IECTOUCH_ONLYMOVES			0x00000805		/* must be the value of the  previous one + 1*/
#define VISU_ET_GESTURE_TOUCHTOMOUSE				0x00000806
#define VISU_ET_GESTURE_TOUCHTOMOUSE_ONLYMOVES		0x00000807		/* must be the value of the  previous one + 1*/
#define VISU_ET_INVALIDATE							0x00100000
#define VISU_ET_SPECIAL								0x00200000

/* Support of custom events */

/* This bit is used to identify an event as a custom event.
** In this case 16 bits (see VISU_ET_CUSTOM_EVENT_BITMASK) can be used to define the custom event
*/
#define VISU_ET_CUSTOM_EVENT_FLAG					0x00010000
#define VISU_ET_CUSTOM_EVENT_BITMASK				0x0000FFFF

#define VISU_CLIENTS_NOTHINGTODO	0x0000
#define VISU_CLIENTS_TOREMOVE		0x0001
#define VISU_CLIENTS_TOADD			0x0002
#define VISU_CLIENTS_INVALIDAPPLICATION		0x0100

#define VISU_CLIENTS_CREATESHAREDMEMORY				0x00000001
#define VISU_CLIENTS_CREATEIECMEMORY				0x00000002
/* this type will be used when the client does not specify the type (probably old clients registering using CmpVisuServer) */
#define VISU_CLIENTS_PROGRAMMINGSYSTEM_OBSOLETE		0x00010000
/* a remote visualization client (probably CmpVisuHandlerRemote) */
#define VISU_CLIENTS_HMI_TARGET						0x00020000
#define VISU_CLIENTS_TARGETVISU						0x00040000
#define VISU_CLIENTS_WEBVISUALIZATION				0x00080000
#define VISU_CLIENTS_NOEXTERNIDTIMEOUT				0x00100000
/* a CoDeSys that passes the correct client type */
#define VISU_CLIENTS_PROGRAMMINGSYSTEM				0x00200000		

/**
 * <description>Enum: VisuEnumClientTag</description>
 */
#define VISUENUMCLIENTTAG_UNDEFINED	    0	
#define VISUENUMCLIENTTAG_NAME			1	
#define VISUENUMCLIENTTAG_ADDRESSIPV4   2	
/* Typed enum definition */
#define VISUENUMCLIENTTAG    RTS_IEC_INT

/* This flag will start the targetvisu, either as an own process or within the runtimesystem process.
	dwParam1 will be a pointer to a <Vish_Starttargetvisu_Params>
*/
#define VISU_STARTVISU_TARGETVISU				0x00000001	
/* This flag will start a webserver, allowing webclients to connect to the running visu
	As starting/stopping the webserver is implemented using a reference counting mechanism,
	a call with this tag must be followed by a call with VISU_STARTVISU_WEBSERVER_RELEASE.
 */
#define VISU_STARTVISU_WEBSERVER				0x00000002
/* This type will start the targetvisu, similar to VISU_STARTVISU_TARGETVISU, with the difference that
	the handle to the targetvisuinstance will be returned. dwParam1 will be a pointer to a  <Vish_Starttargetvisu_Params>
	dwParam2 a pointer to a RTS_HANDLE, that will receive the result! If dwParam points to a valid handle than this
	targetvisuinstance will be released before creating a new one. */
#define VISU_STARTVISU_TARGETVISU_WITHHANDLE	0x00000003
/* This type will stop an existing targetvisu. dwParam1 will be the handle to the targetvisuinstance. */
#define VISU_STARTVISU_TARGETVISU_CLOSE			0x00000004
/* This type will start the targetvisu, similar to VISU_STARTVISU_TARGETVISU_WITHHANDLE; The difference is that calling this
	tag allows to pass further information to the targetvisualization; This information is passed in the structure behind dwParam1
	dwParam1 will be a pointer to a  <Vish_Starttargetvisu_Params> or an extension of this structure
	dwParam2 a pointer to a RTS_HANDLE, that will receive the result! If dwParam points to a valid handle than this
	targetvisuinstance will be released before creating a new one. 
	Older runtimes might not support this tag; in this case, ERR_NOTIMPLEMENTED will be returned so that a compatibility call with
	VISU_STARTVISU_TARGETVISU_WITHHANDLE can be done.
*/
#define VISU_STARTVISU_TARGETVISU_WITHHANDLE2	0x00000005
/* This type will release a webserver. As starting/stopping the webserver is implemented using a reference counting mechanism,
	a call with this tag must be prepended by a call with VISU_STARTVISU_WEBSERVER. */
#define VISU_STARTVISU_WEBSERVER_RELEASE		0x00000006

/* This flag can be passed to <see>VishPostClientRequest</see>. The intention is to restart the targetvisualization. */
#define VISU_CLIENTREQUEST_RESTARTTARGETVISUIFNOTRUNNING			1

/* This flag can be passed to <see>VishPostClientRequest</see>. The intention is to close all open targetvisualization windows. */
#define VISU_CLIENTREQUEST_REMOVEALLTARGETVISUCLIENTS				2	

/* This flag can be passed to <see>VishPostClientRequest</see>. The intention is to force a repaint in all open visualization clients. */
#define VISU_CLIENTREQUEST_INVALIDATEALLCIENTS						3


/********************************************************************************
* Interface to IEC part of Visualisation
********************************************************************************/

/*
	Within the runtime system, this structure was called EventStruct for all the time. As the same is
	true for the name VisuStructEvent in IEC, we do not want to change either name because that effects
	several components in each situations (both could have been used by customers too).
	To be able to use the m4 generation nevertheless, we have this typedef mapping the existing type
	to the one expected by the m4 export.
*/
typedef EventStruct VisuStructEvent;


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Enum: Visu_Types</description>
 */
#define VISU_TYPES_TYPE_BOOL    0	/* x */
#define VISU_TYPES_TYPE_INT    1	/* x */
#define VISU_TYPES_TYPE_BYTE    2	
#define VISU_TYPES_TYPE_WORD    3	
#define VISU_TYPES_TYPE_DINT    4	/* x */
#define VISU_TYPES_TYPE_DWORD    5	
#define VISU_TYPES_TYPE_REAL    6	/* x */
#define VISU_TYPES_TYPE_TIME    7	
#define VISU_TYPES_TYPE_STRING    8	/* x */
#define VISU_TYPES_TYPE_ARRAY    9	
#define VISU_TYPES_TYPE_ENUM    10	
#define VISU_TYPES_TYPE_USERDEF    11	
#define VISU_TYPES_TYPE_BITORBYTE    12	
#define VISU_TYPES_TYPE_POINTER    13	
#define VISU_TYPES_TYPE_SINT    14	/* x */
#define VISU_TYPES_TYPE_USINT    15	/* x */
#define VISU_TYPES_TYPE_UINT    16	/* x */
#define VISU_TYPES_TYPE_UDINT    17	/* x */
#define VISU_TYPES_TYPE_DATE    18	
#define VISU_TYPES_TYPE_TOD    19	
#define VISU_TYPES_TYPE_DT    20	
#define VISU_TYPES_TYPE_VOID    21	
#define VISU_TYPES_TYPE_LREAL    22	/* x */
#define VISU_TYPES_TYPE_REF    23	
#define VISU_TYPES_TYPE_SUBRANGE    24	/* this class is only used for load and save
						  in all other cases a subrange type behaves like the basetype! */
#define VISU_TYPES_TYPE_LBITORBYTE    25	
#define VISU_TYPES_TYPE_LINT    26	/* x */
#define VISU_TYPES_TYPE_ULINT    27	/* x */
#define VISU_TYPES_TYPE_LWORD    28	
#define VISU_TYPES_TYPE_NONE    29	
#define VISU_TYPES_TYPE_BIT    30	
#define VISU_TYPES_TYPE_WSTRING    31	
#define VISU_TYPES_TYPE_LTIME    32	
#define VISU_TYPES_MAXTYPES    33	
/* Typed enum definition */
#define VISU_TYPES    RTS_IEC_INT

/**
 * <description>Enum: VisuEnumClientTag</description>
 */
#define VISUENUMCLIENTTAG_UNDEFINED    0	
#define VISUENUMCLIENTTAG_NAME    1	
#define VISUENUMCLIENTTAG_ADDRESSIPV4    2	
#define VISUENUMCLIENTTAG_RTVID		3		/* format is encoded in a string, 8 hex digits for the targetid, a space, 8 hex digits for the version */
/* Typed enum definition */
#define VISUENUMCLIENTTAG    RTS_IEC_INT

/**
 * This structure is an extension of Vish_Starttargetvisu_Params; can be passed to VishStartVisu using the starttype VISU_STARTVISU_TARGETVISU_WITHRESULT2 
 */
typedef struct tagVish_Starttargetvisu_Params2
{
	RTS_IEC_INT iSize;		/* Not needed by the converted code
CHECKED_OMIT */
	RTS_IEC_INT iXPos;		
	RTS_IEC_INT iYPos;		
	RTS_IEC_INT iWidth;		
	RTS_IEC_INT iHeight;		
	RTS_IEC_STRING *stApp;		
	RTS_IEC_UINT uiAntiAliasing;		/* Information about the antialiasing settings chosen by the configuration. */
	RTS_IEC_UINT uiWindowType;		/* Information about the frame type of the targetvisu window (fullscreen, with window frame, without window frame,...); Reserved for future use; not yet implemented */
	RTS_IEC_UINT uiUpdateRateMs;		/* The cyclic update rate in milliseconds of the targetvisualization window; Reserved for future use; not yet implemented */
	RTS_IEC_UINT uiFlags;		/* Some flags regarding the targetvisualizations; Reserved for future use; not yet implemented */
} Vish_Starttargetvisu_Params2;

/**
 * <description>Visu_InputChecks</description>
 */
typedef struct tagVisu_InputChecks
{
	RTS_IEC_INT iVersion;		/* for extensibility */
	RTS_IEC_BYTE *pMin;		/* will point to the typespecific min value. For the converted code
 this component contains the name of variable holding the minimum
 value resp. a string with the constant value */
	RTS_IEC_BYTE *pMax;		/* will point to the typespecific max value. For the converted code
 this component contains the name of variable holding the maximum
 value resp. a string with the constant value */
} Visu_InputChecks;

/**
 * the structure is the same than Visu_InputChecks, only extended
 */
typedef struct tagVisu_InputChecks2
{
	RTS_IEC_INT iVersion;		/* for extensibility */
	RTS_IEC_BYTE *pMin;		/* will point to the typespecific min value. For the converted code
 this component contains the name of variable holding the minimum
 value resp. a string with the constant value */
	RTS_IEC_BYTE *pMax;		/* will point to the typespecific max value. For the converted code
 this component contains the name of variable holding the maximum
 value resp. a string with the constant value */
	RTS_IEC_DINT diMaxLen;		
} Visu_InputChecks2;

/**
 * <description>Vish_HavetomanageClient_Data</description>
 */
typedef struct tagVish_HavetomanageClient_Data
{
	RTS_IEC_INT iSize;		/* Not needed by the converted code
CHECKED_OMIT */
	RTS_IEC_DWORD dwExternID;		
	RTS_IEC_DWORD dwFlags;		
} Vish_HavetomanageClient_Data;

/**
 * <description>Vish_Starttargetvisu_Params</description>
 */
typedef struct tagVish_Starttargetvisu_Params
{
	RTS_IEC_INT iSize;		/* TOCHECK: looks like a hack */
	RTS_IEC_INT iXPos;		
	RTS_IEC_INT iYPos;		
	RTS_IEC_INT iWidth;		
	RTS_IEC_INT iHeight;		
	RTS_IEC_STRING *stApp;		
} Vish_Starttargetvisu_Params;

/**
 * <description>WebserverInitParameter</description>
 */
typedef struct tagWebserverInitParameter
{
	RTS_IEC_STRING stStartHTMName[81];		/* This string defines a start htm filename, which will be opened,
 when only ip-address and port is entered in the webbrowser. */
} WebserverInitParameter;

/**
 * <description>Visu_ClientTagData</description>
 */
typedef struct tagVisu_ClientTagData
{
	RTS_IEC_INT tag;		
	RTS_IEC_STRING strValue[41];		/* 40 chars is enough space for holding names and ipv6 addresses in the future */
} Visu_ClientTagData;

/**
 * <description>Vish_HavetomanageClient_Data2</description>
 */
typedef struct tagVish_HavetomanageClient_Data2
{
	RTS_IEC_INT iSize;		/* Not needed by the converted code
CHECKED_OMIT */
	RTS_IEC_DWORD dwExternID;		
	RTS_IEC_DWORD dwFlags;		
	RTS_IEC_DWORD dwTagsCapacity;		/* Contains the number of entries pTags points to. */
	RTS_IEC_DWORD dwNumTags;		/* Contains the number of tags effectively returned. */
	Visu_ClientTagData *pTags;		
} Vish_HavetomanageClient_Data2;

/**
 * | This function writes a value of a string with a specific type to
 * | the given buffer if the input has the correct type, otherwise an error is returned.
 * :return: The runtime system error code (see CmpErrors.library)
 * link even in simulation mode
 */
typedef struct tagvishbufferprintf_struct
{
	RTS_IEC_STRING *pstFormat;			/* VAR_INPUT */	/* the formatstring */
	RTS_IEC_DWORD *pVarAdr;				/* VAR_INPUT */	/* the address of the variable that shall be printed */
	RTS_IEC_DWORD dwVarType;			/* VAR_INPUT */	/* the type of the variable as defined in visu_types */
	RTS_IEC_BYTE *pBuffer;				/* VAR_INPUT */	/* the buffer where the text is to be printed */
	RTS_IEC_UDINT dwBufferSize;			/* VAR_INPUT */	/* the size of the buffer in bytes */
	RTS_IEC_INT VishBufferPrintf;		/* VAR_OUTPUT */	
} vishbufferprintf_struct;

DEF_API(`void',`CDECL',`vishbufferprintf',`(vishbufferprintf_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC539705B),0x03050600)

/**
 * Does a printf for the given format string and the given variable. Will not return NULL!
 */
typedef struct tagvishbufferprintfw_struct
{
	RTS_IEC_WSTRING *wstFormat;			/* VAR_INPUT */	/* the formatstring */
	RTS_IEC_DWORD *pVarAdr;				/* VAR_INPUT */	/* the address of the variable that shall be printed */
	RTS_IEC_DWORD dwVarType;			/* VAR_INPUT */	/* the type of the variable as defined in visu_types */
	RTS_IEC_BYTE *pBuffer;				/* VAR_INPUT */	/* the buffer where the text is to be printed */
	RTS_IEC_UDINT dwBufferSize;			/* VAR_INPUT */	/* the size of the buffer in bytes, not in wstring characters! */
	RTS_IEC_INT VishBufferPrintfW;		/* VAR_OUTPUT */	
} vishbufferprintfw_struct;

DEF_API(`void',`CDECL',`vishbufferprintfw',`(vishbufferprintfw_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x3E99BEF7),0x03050600)

/**
 * | Returns the currently active event for the given application.
 * | Fills the given structure, when there is no current event, it will be filled with a monitoring event.
 * :return: The runtime system error code (see CmpErrors.library)
 * link even in simulation mode
 */
typedef struct tagvishfillcurrentevent_struct
{
	RTS_IEC_STRING stAppName[81];		/* VAR_INPUT */	/* The name of the application where to get the event from the queue */
	VisuStructEvent *pEvent;			/* VAR_INPUT */	/* Pointer to the event that should be filled */
	RTS_IEC_INT VishFillCurrentEvent;	/* VAR_OUTPUT */	
} vishfillcurrentevent_struct;

DEF_API(`void',`CDECL',`vishfillcurrentevent',`(vishfillcurrentevent_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x73CA5FD9),0x03050600)

/**
 * | Returns the iec id the client was registered with. Executes the mapping from
 * | externID -> IEC-ID
 * :return: a valid IEC-ID or INVALID_IEC_ID(-1)
 * link even in simulation mode
 */
typedef struct tagvishgetclientid_struct
{
	RTS_IEC_DWORD dwExternID;			/* VAR_INPUT */	
	RTS_IEC_INT VishGetClientId;		/* VAR_OUTPUT */	
} vishgetclientid_struct;

DEF_API(`void',`CDECL',`vishgetclientid',`(vishgetclientid_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x96B89426),0x03050600)

/**
 * | Returns the currently active event for the given application.
 * :return: The active input event or a monitoring event if there is none. 
 * link even in simulation mode
 */
typedef struct tagvishgetcurrentevent_struct
{
	RTS_IEC_STRING stAppName[81];		/* VAR_INPUT */	/* The name of the application where to get the event from the queue */
	VisuStructEvent VishGetCurrentEvent;	/* VAR_OUTPUT */	
} vishgetcurrentevent_struct;

DEF_API(`void',`CDECL',`vishgetcurrentevent',`(vishgetcurrentevent_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x786413F1),0x03050600)

/**
 * | Checks if a new Client has to be created or an existing Client has to
 * | be removed
 * :return: 
 *
 * - VISU_CLIENTS_TOREMOVE(0x0001) if a client has to be removed.
 * - VISU_CLIENTS_TOADD(0x0002) if a new Client has to be created. 
 * link even in simulation mode
 */
typedef struct tagvishhavetomanageclients_struct
{
	Vish_HavetomanageClient_Data *pData;	/* VAR_INPUT */	/* returns information about the client to handle */
	RTS_IEC_STRING stAppName[81];		/* VAR_INPUT */	/* the application to check */
	RTS_IEC_INT VishHaveToManageClients;	/* VAR_OUTPUT */	
} vishhavetomanageclients_struct;

DEF_API(`void',`CDECL',`vishhavetomanageclients',`(vishhavetomanageclients_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x2541155E),0x03050600)

/**
 * | Checks if a new Client has to be created or an existing Client has to
 * | be removed
 * :return: 
 *
 * - VISU_CLIENTS_TOREMOVE(0x0001) if a client has to be removed.
 * - VISU_CLIENTS_TOADD(0x0002) if a new Client has to be created. 
 * link even in simulation mode
 */
typedef struct tagvishhavetomanageclients2_struct
{
	Vish_HavetomanageClient_Data2 *pData;	/* VAR_INPUT */	/* returns information about the client to handle */
	RTS_IEC_STRING stAppName[81];		/* VAR_INPUT */	/* the application to check */
	RTS_IEC_INT VishHaveToManageClients2;	/* VAR_OUTPUT */	
} vishhavetomanageclients2_struct;

DEF_API(`void',`CDECL',`vishhavetomanageclients2',`(vishhavetomanageclients2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x68E999B9),0x03050600)

/**
 * | Does a printf for the given format string and the given variable. Will not return NULL!
 * | Obsolete, use VishBufferPrintf instead
 * :return: the formatted string
 */
typedef struct tagvishprintf_struct
{
	RTS_IEC_STRING *pstFormat;			/* VAR_INPUT */	/* The format string */
	RTS_IEC_DWORD *pVarAdr;				/* VAR_INPUT */	/* Pointer to variable */
	RTS_IEC_DWORD dwVarType;			/* VAR_INPUT */	/* The variable type */
	RTS_IEC_STRING *VishPrintf;			/* VAR_OUTPUT */	
} vishprintf_struct;

DEF_API(`void',`CDECL',`vishprintf',`(vishprintf_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x5514EA1B),0x03050600)

/**
 * | Does a printf for the given format wstring and the given variable. Will not return NULL!
 * | Obsolete, use VishBufferPrintfW instead
 * :return: the formatted string
 */
typedef struct tagvishprintfw_struct
{
	RTS_IEC_WSTRING *pwstFormat;		/* VAR_INPUT */	/* The format string */
	RTS_IEC_DWORD *pVarAdr;				/* VAR_INPUT */	/* Pointer to variable */
	RTS_IEC_DWORD dwVarType;			/* VAR_INPUT */	/* The variable type */
	RTS_IEC_WSTRING *VishPrintfW;		/* VAR_OUTPUT */	
} vishprintfw_struct;

DEF_API(`void',`CDECL',`vishprintfw',`(vishprintfw_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xE3A4DA48),0x03050600)

/**
 * | Removes the currently active event from the applications event queue
 * :return: The runtime system error code (see CmpErrors.library)
 * link even in simulation mode
 */
typedef struct tagvishremovecurrentevent_struct
{
	RTS_IEC_STRING stAppName[81];		/* VAR_INPUT */	/* The name of the application where to remove the event from the queue */
	RTS_IEC_INT VishRemoveCurrentEvent;	/* VAR_OUTPUT */	
} vishremovecurrentevent_struct;

DEF_API(`void',`CDECL',`vishremovecurrentevent',`(vishremovecurrentevent_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x033E84DC),0x03050600)

/**
 * | Registers the IEC-ID of the client and the paintbuffer of this client
 * | in the runtime system. 
 * | A id of -1 means that the client was not registered!
 * | A dwExternID of 0xFFFFFFFE, i.e. REMOVE_CLIENT means that the client with IEC_ID id
 * | has to be removed from the maps in the runtime. The data in the IEC-Task has already be
 * | freed!   
 * link even in simulation mode
 */
typedef struct tagvishsetclientdata_struct
{
	RTS_IEC_DWORD dwExternID;			/* VAR_INPUT */	
	RTS_IEC_INT iClientID;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pPaintBuffer;			/* VAR_INPUT */	
	RTS_IEC_STRING stAppName[81];		/* VAR_INPUT */	
	RTS_IEC_INT VishSetClientData;		/* VAR_OUTPUT */	
} vishsetclientdata_struct;

DEF_API(`void',`CDECL',`vishsetclientdata',`(vishsetclientdata_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x474A3B55),0x03050600)

/**
 * | Provides functionality to start a visu in the runtime system. Can be used for starting
 * | a targetvisu or a webserver for example.
 */
typedef struct tagvishstartvisu_struct
{
	RTS_IEC_DWORD dwType;				/* VAR_INPUT */	/* What to start, see the definition of the valid parameters VISU_STARTVISU_... */
	RTS_IEC_XWORD dwParam1;				/* VAR_INPUT */	/* A parameter specific to the requested dwType */
	RTS_IEC_XWORD dwParam2;				/* VAR_INPUT */	/* A parameter specific to the requested dwType */
	RTS_IEC_INT VishStartVisu;			/* VAR_OUTPUT */	
} vishstartvisu_struct;

DEF_API(`void',`CDECL',`vishstartvisu',`(vishstartvisu_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x8E8D0ABE),0x03050600)

/**
 * | This function writes a value of a string with a specific type to
 * | a pointer if the input has the correct type, else a error is returned
 * :return: The runtime system error code (see CmpErrors.library)
 * link even in simulation mode
 */
typedef struct tagvishwritevalueifvalid_struct
{
	RTS_IEC_STRING *pstToWrite;			/* VAR_INPUT */	
	RTS_IEC_BYTE *pDataToWriteTo;		/* VAR_INPUT */	
	RTS_IEC_INT dataType;				/* VAR_INPUT, Enum: VISU_TYPES */
	Visu_InputChecks *pInputChecks;		/* VAR_INPUT */	
	RTS_IEC_INT VishWriteValueIfValid;	/* VAR_OUTPUT */	
} vishwritevalueifvalid_struct;

DEF_API(`void',`CDECL',`vishwritevalueifvalid',`(vishwritevalueifvalid_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x390D7585),0x03050600)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


/********************************************************************************
* END Interface to IEC part of Visualisation
********************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
* Interface to Visualisationclients
********************************************************************************/
#define SUCCESSFULLY_REGISTERED	0
#define NOT_REGISTERED			0xFFFFFFFF
#define NOT_YET_REGISTERED		0xFFFFFFFE
#define UNKNOWN_EXTERN_ID		0xFFFFFFFD

#define INVALID_EXTERN_ID			0xFFFFFFFF
#define REMOVE_CLIENT				0xFFFFFFFE
#define INVALID_APPLICATION			0xFFFFFFFD
#define NO_MORE_MEMORY				0xFFFFFFFC
#define TOO_MANY_CLIENTTAGS			0xFFFFFFFB
#define MAXIMAL_VALID_EXTERN_ID		0xAFFFFFFF		/* all values above will be treated as errors */

#define INVALID_IEC_ID			0xFFFF
#define UNSET_IEC_ID			0xFFFE

/**
 * <description> Function to register a new client in the runtimesystem. A 
 * ID will be returned that can be used to poll if the ID has been registered in the IEC-Task. </description>
 * <param name="pszAppName">The application to whose visualization the client wants to connect</param>
 * <param name="dwFlags">Some flags can be given here to set how the client will be created,
 *	those flags are the VISU_CLIENTS_CREATE... flags or 0 for a standard client living within the process of the runtime. </param>
 * <result>An ID that allows the client to get access to his session</result>
 */
DEF_API(`ExternID', `CDECL', `VishRegisterClient', `(char* pszAppName, RTS_IEC_DWORD dwFlags)')

/**
 * <description> Function to register a new client in the runtimesystem. A 
 * ID will be returned that can be used to poll if the ID has been registered in the IEC-Task. </description>
 * <param name="pszAppName">The application to whose visualization the client wants to connect</param>
 * <param name="dwFlags">Some flags can be given here to set how the client will be created,
 *	those flags are the VISU_CLIENTS_CREATE... flags or 0 for a standard client living within the process of the runtime. </param>
 * <param name="numClientTags">The number of client data tags associated with this newly created client.</param>
 * <param name="pTags">A pointer to an array of <see>numClientTags</see> entries of tags associated with this newly created client.
 *	This pointer might be NULL when the number of tags equals 0. The pointer does not need to be valid longer than the call to 
 *  to this function.</param>
 * <result>An ID that allows the client to get access to his session</result>
 */
DEF_API(`ExternID', `CDECL', `VishRegisterClient2', `(char* pszAppName, RTS_IEC_DWORD dwFlags, RTS_UI32 numClientTags, Visu_ClientTagData* pTags)')

/**
 * <description> Function to obtain the real ID from the IEC-Task. </description>
 * <result>If the ID is not equal to INVALID_IEC_ID it can be used, otherwise this 
 * function has to be called some times more until a valid ID is returned</result>
 */
DEF_API(`RTS_UI32', `CDECL', `VishIsRegistered', `(ExternID extID)')

/**
 * <description> Function to remove a Visuclient with a specific ID.</description>
 * <result></result>
 */
DEF_API(`void', `CDECL', `VishRemoveClient', `(ExternID extID)')

/**
 * <description> Function to deliver the current event, inkl. monitoring</description>
 * <param name="pEvent">The Event to handle</param>
 * <param name="pCmdsResult">Will get the paintbuffer that contains the current data for painting. If there
 * is nothing to paint NULL will be returned. pCmdsResult may not be NULL!</param>
 * <result>An errorcode signaling whether the call was successfull. ERR_OK, if everything is ok, ERR_NOBUFFER if
 *	the event could not be added to the underlying eventbuffer. A returnvalue of INVALID_IEC_ID
 * signals that the request concerned a not registered Client. This could also be the result of a download between
 * the calls to GetPaintData.</result>
 */
DEF_API(`int', `CDECL', `VishGetPaintData', `(EventStruct* pEvent, CommandBuffer** pCmdsResult)')

/**
 * <description> Function to deliver the current event, inkl. monitoring. This call will only post an event to the queue
 *	it will not retrieve the currently available paint data! </description>
 * <param name="pEvent">The Event to handle</param>
 * <result>An errorcode signaling whether the call was successfull. ERR_OK, if everything is ok, ERR_NOBUFFER if
 *	the event could not be added to the underlying eventbuffer. A returnvalue of INVALID_IEC_ID
 * signals that the request concerned a not registered Client. This could also be the result of a download between
 * the calls to GetPaintData.</result>
 */
DEF_API(`int', `CDECL', `VishPostEvent', `(EventStruct* pEvent)')

/**
 * <description> Function that releases the paintbuffer, ie. allows an update of the visualization. 
 *	Call this function after the client has finished using the paintbuffer, ie. the client has interpreted the 
 *	commands or copied the buffer. </description>
 * <param name="extID">The externid whose paintbuffer should be released.</param>
 * <result>ERR_OK, ERR_PARAMETER or ERR_FAILED if the buffer is already released.</result>
 */
DEF_API(`RTS_RESULT', `CDECL', `VishReleasePaintBuffer', `(ExternID extID)')

/**
 * <description> Function to return if Combination of IecID and ExternID is registered within the 
 * runtime system </description>
 * <result>0 if the combination of ids is not registered, nonzero if it is registered </result>
 */
DEF_API(`long', `CDECL', `VishIsValidClientID', `(ExternID extId, IecID id)')

/**
 * <description> Function initializes a Event </description>
 * <result>The paintbuffer that contains the current data for painting</result>
 */
DEF_API(`void', `CDECL', `VishInitEventStruct', `(EventStruct* pEvent)')

/**
 * <description> Function to deliver a visual client request. This call will only post an event to the queue
 *	</description>
 * <param name="pszAppName">The application name</param>
 * <param name="dwFlags">The flags</param>
 * <result>A Errorvalue if the call was successful. ERR_OK, if everything is ok. </result>
 */
DEF_API(`int', `CDECL', `VishPostClientRequest', `(char* pszAppName, RTS_IEC_DWORD dwFlags)')

/**
 * <description> Function to set up a new paint buffer based on shared memory. Is only used in case
 * of the 2-process target visualization.</description>
 * <param name="extID">The externid whose paintbuffer should be set up.</param>
 * <param name="pszShmName">The name of the shared memory, that is used for the paint buffer</param>
 * <result>ERR_OK in case of success, ERR_NOT_SUPPORTED in case of the 1-process target visualization.
 * Other error codes in case of failure</result>
 */
DEF_API(`RTS_RESULT', `CDECL', `VishSetupPaintBuffer', `(ExternID extID, char* pszShmName)')

/**
 * <description>Function to obtain the maximum size of data, that can be read from a file,
 * when transferring data from the visualization to the plc by streaming.</description>
 * <result>The maximum size</result>
 */
DEF_API(`RTS_UI32', `CDECL', `VishGetFileStreamingChunkSize', `()')

typedef enum
{
	VishFileTransferDirection_PlcToVisu,
	VishFileTransferDirection_VisuToPlc
} VishFileTransferDirection;

typedef enum
{
	VishFileTransferType_File,
	VishFileTransferType_Streaming
} VishFileTransferType;

/**
 * <description>Enum: VisuEnumFileTransferControlFlags</description>
 */
#define VISUENUMFILETRANSFERCONTROLFLAGS_USEORIGINALFILENAME    0x00000004	
#define VISUENUMFILETRANSFERCONTROLFLAGS_CONFIRMFILEOVERWRITEINPLC    0x00000008	


typedef struct
{
	RTS_IEC_DWORD dwClientID;
	RTS_IEC_WORD wRequestID;
	VishFileTransferDirection direction;
	const char* pszPlcFilename;
	const char* pszVisuFilename;
	RTS_IEC_DWORD dwControlFlags;
	char* pszPlcFilenameCopy;
} VishFileTransferConfiguration;


/**
 * <description> Function to initiate a file transfer between a visu client and the plc.</description>
 * <param name="configuration">The configuration parameters for the file transfer.</param>
 * <result>Error code.</result>
 */
DEF_API(`RTS_RESULT', `CDECL', `VishInitiateFileTransfer', `(const VishFileTransferConfiguration* configuration)')

/**
 * <description> Function which is used by a file transfer between a visu client and the plc to ask for the file info.</description>
 * <param name="pszFileName">The file name for which the file info is needed.</param>
 * <param name="pfi">The file info which is the result.</param>
 * <result>Error code.</result>
 */
DEF_API(`RTS_RESULT', `CDECL', `VishFileTransferGetFileInfo', `(const char* pszFileName, FileInfo* pfi)')

/********************************************************************************
* END Interface to Visualisationclients
********************************************************************************/

/*********************************************************************************
* Function definitions that could be called via IPC
*********************************************************************************/

#define VISH_IPC_REGISTERCLIENT		"VishRegisterClient"
#define VISH_IPC_ISREGISTERED		"VishIsRegistered"
#define VISH_IPC_GETPAINTDATA		"VishGetPaintdata"
#define VISH_IPC_RELEASEPAINTBUFFER	"VishReleasePaintBuffer"
#define VISH_IPC_REMOVEINSTANCE		"VishRemoveInstance"
#define VISH_IPC_REGISTERBITMAPPOOL	"VishRegisterBitmapPool"
#define VISH_IPC_POSTEVENT			"VishPostEvent"
#define VISH_IPC_GETTARGETVISUSETTINGS	"VishGetTargetvisuSettings"	/* special function only for the two process targetvisu */
#define VISH_IPC_SENDCLIENTREQUEST	"VishSendClientRequest"	/* special function to control visu clients */

/*********************************************************************************
* END: Function definitions that could be called via IPC
*********************************************************************************/


#ifdef __cplusplus
}
#endif