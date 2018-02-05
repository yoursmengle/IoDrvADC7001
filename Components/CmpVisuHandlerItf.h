 /**
 * <interfacename>CmpVisuHandler</interfacename>
 * <description> 
 *	Interface for the visu handler component.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPVISUHANDLERITF_H_
#define _CMPVISUHANDLERITF_H_

#include "CmpStd.h"

 

 




#include "CmpFileTransferItf.h"

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
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

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

void CDECL CDECL_EXT vishbufferprintf(vishbufferprintf_struct *p);
typedef void (CDECL CDECL_EXT* PFVISHBUFFERPRINTF_IEC) (vishbufferprintf_struct *p);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHBUFFERPRINTF_NOTIMPLEMENTED)
	#define USE_vishbufferprintf
	#define EXT_vishbufferprintf
	#define GET_vishbufferprintf(fl)  ERR_NOTIMPLEMENTED
	#define CAL_vishbufferprintf(p0) 
	#define CHK_vishbufferprintf  FALSE
	#define EXP_vishbufferprintf  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_vishbufferprintf
	#define EXT_vishbufferprintf
	#define GET_vishbufferprintf(fl)  CAL_CMGETAPI( "vishbufferprintf" ) 
	#define CAL_vishbufferprintf  vishbufferprintf
	#define CHK_vishbufferprintf  TRUE
	#define EXP_vishbufferprintf  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishbufferprintf", (RTS_UINTPTR)vishbufferprintf, 1, RTSITF_GET_SIGNATURE(0, 0xC539705B), 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_vishbufferprintf
	#define EXT_vishbufferprintf
	#define GET_vishbufferprintf(fl)  CAL_CMGETAPI( "vishbufferprintf" ) 
	#define CAL_vishbufferprintf  vishbufferprintf
	#define CHK_vishbufferprintf  TRUE
	#define EXP_vishbufferprintf  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishbufferprintf", (RTS_UINTPTR)vishbufferprintf, 1, RTSITF_GET_SIGNATURE(0, 0xC539705B), 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlervishbufferprintf
	#define EXT_CmpVisuHandlervishbufferprintf
	#define GET_CmpVisuHandlervishbufferprintf  ERR_OK
	#define CAL_CmpVisuHandlervishbufferprintf  vishbufferprintf
	#define CHK_CmpVisuHandlervishbufferprintf  TRUE
	#define EXP_CmpVisuHandlervishbufferprintf  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishbufferprintf", (RTS_UINTPTR)vishbufferprintf, 1, RTSITF_GET_SIGNATURE(0, 0xC539705B), 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_vishbufferprintf
	#define EXT_vishbufferprintf
	#define GET_vishbufferprintf(fl)  CAL_CMGETAPI( "vishbufferprintf" ) 
	#define CAL_vishbufferprintf  vishbufferprintf
	#define CHK_vishbufferprintf  TRUE
	#define EXP_vishbufferprintf  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishbufferprintf", (RTS_UINTPTR)vishbufferprintf, 1, RTSITF_GET_SIGNATURE(0, 0xC539705B), 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_vishbufferprintf  PFVISHBUFFERPRINTF_IEC pfvishbufferprintf;
	#define EXT_vishbufferprintf  extern PFVISHBUFFERPRINTF_IEC pfvishbufferprintf;
	#define GET_vishbufferprintf(fl)  s_pfCMGetAPI2( "vishbufferprintf", (RTS_VOID_FCTPTR *)&pfvishbufferprintf, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xC539705B), 0x03050600)
	#define CAL_vishbufferprintf  pfvishbufferprintf
	#define CHK_vishbufferprintf  (pfvishbufferprintf != NULL)
	#define EXP_vishbufferprintf   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishbufferprintf", (RTS_UINTPTR)vishbufferprintf, 1, RTSITF_GET_SIGNATURE(0, 0xC539705B), 0x03050600) 
#endif


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

void CDECL CDECL_EXT vishbufferprintfw(vishbufferprintfw_struct *p);
typedef void (CDECL CDECL_EXT* PFVISHBUFFERPRINTFW_IEC) (vishbufferprintfw_struct *p);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHBUFFERPRINTFW_NOTIMPLEMENTED)
	#define USE_vishbufferprintfw
	#define EXT_vishbufferprintfw
	#define GET_vishbufferprintfw(fl)  ERR_NOTIMPLEMENTED
	#define CAL_vishbufferprintfw(p0) 
	#define CHK_vishbufferprintfw  FALSE
	#define EXP_vishbufferprintfw  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_vishbufferprintfw
	#define EXT_vishbufferprintfw
	#define GET_vishbufferprintfw(fl)  CAL_CMGETAPI( "vishbufferprintfw" ) 
	#define CAL_vishbufferprintfw  vishbufferprintfw
	#define CHK_vishbufferprintfw  TRUE
	#define EXP_vishbufferprintfw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishbufferprintfw", (RTS_UINTPTR)vishbufferprintfw, 1, RTSITF_GET_SIGNATURE(0, 0x3E99BEF7), 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_vishbufferprintfw
	#define EXT_vishbufferprintfw
	#define GET_vishbufferprintfw(fl)  CAL_CMGETAPI( "vishbufferprintfw" ) 
	#define CAL_vishbufferprintfw  vishbufferprintfw
	#define CHK_vishbufferprintfw  TRUE
	#define EXP_vishbufferprintfw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishbufferprintfw", (RTS_UINTPTR)vishbufferprintfw, 1, RTSITF_GET_SIGNATURE(0, 0x3E99BEF7), 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlervishbufferprintfw
	#define EXT_CmpVisuHandlervishbufferprintfw
	#define GET_CmpVisuHandlervishbufferprintfw  ERR_OK
	#define CAL_CmpVisuHandlervishbufferprintfw  vishbufferprintfw
	#define CHK_CmpVisuHandlervishbufferprintfw  TRUE
	#define EXP_CmpVisuHandlervishbufferprintfw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishbufferprintfw", (RTS_UINTPTR)vishbufferprintfw, 1, RTSITF_GET_SIGNATURE(0, 0x3E99BEF7), 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_vishbufferprintfw
	#define EXT_vishbufferprintfw
	#define GET_vishbufferprintfw(fl)  CAL_CMGETAPI( "vishbufferprintfw" ) 
	#define CAL_vishbufferprintfw  vishbufferprintfw
	#define CHK_vishbufferprintfw  TRUE
	#define EXP_vishbufferprintfw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishbufferprintfw", (RTS_UINTPTR)vishbufferprintfw, 1, RTSITF_GET_SIGNATURE(0, 0x3E99BEF7), 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_vishbufferprintfw  PFVISHBUFFERPRINTFW_IEC pfvishbufferprintfw;
	#define EXT_vishbufferprintfw  extern PFVISHBUFFERPRINTFW_IEC pfvishbufferprintfw;
	#define GET_vishbufferprintfw(fl)  s_pfCMGetAPI2( "vishbufferprintfw", (RTS_VOID_FCTPTR *)&pfvishbufferprintfw, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x3E99BEF7), 0x03050600)
	#define CAL_vishbufferprintfw  pfvishbufferprintfw
	#define CHK_vishbufferprintfw  (pfvishbufferprintfw != NULL)
	#define EXP_vishbufferprintfw   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishbufferprintfw", (RTS_UINTPTR)vishbufferprintfw, 1, RTSITF_GET_SIGNATURE(0, 0x3E99BEF7), 0x03050600) 
#endif


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

void CDECL CDECL_EXT vishfillcurrentevent(vishfillcurrentevent_struct *p);
typedef void (CDECL CDECL_EXT* PFVISHFILLCURRENTEVENT_IEC) (vishfillcurrentevent_struct *p);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHFILLCURRENTEVENT_NOTIMPLEMENTED)
	#define USE_vishfillcurrentevent
	#define EXT_vishfillcurrentevent
	#define GET_vishfillcurrentevent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_vishfillcurrentevent(p0) 
	#define CHK_vishfillcurrentevent  FALSE
	#define EXP_vishfillcurrentevent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_vishfillcurrentevent
	#define EXT_vishfillcurrentevent
	#define GET_vishfillcurrentevent(fl)  CAL_CMGETAPI( "vishfillcurrentevent" ) 
	#define CAL_vishfillcurrentevent  vishfillcurrentevent
	#define CHK_vishfillcurrentevent  TRUE
	#define EXP_vishfillcurrentevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishfillcurrentevent", (RTS_UINTPTR)vishfillcurrentevent, 1, RTSITF_GET_SIGNATURE(0, 0x73CA5FD9), 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_vishfillcurrentevent
	#define EXT_vishfillcurrentevent
	#define GET_vishfillcurrentevent(fl)  CAL_CMGETAPI( "vishfillcurrentevent" ) 
	#define CAL_vishfillcurrentevent  vishfillcurrentevent
	#define CHK_vishfillcurrentevent  TRUE
	#define EXP_vishfillcurrentevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishfillcurrentevent", (RTS_UINTPTR)vishfillcurrentevent, 1, RTSITF_GET_SIGNATURE(0, 0x73CA5FD9), 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlervishfillcurrentevent
	#define EXT_CmpVisuHandlervishfillcurrentevent
	#define GET_CmpVisuHandlervishfillcurrentevent  ERR_OK
	#define CAL_CmpVisuHandlervishfillcurrentevent  vishfillcurrentevent
	#define CHK_CmpVisuHandlervishfillcurrentevent  TRUE
	#define EXP_CmpVisuHandlervishfillcurrentevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishfillcurrentevent", (RTS_UINTPTR)vishfillcurrentevent, 1, RTSITF_GET_SIGNATURE(0, 0x73CA5FD9), 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_vishfillcurrentevent
	#define EXT_vishfillcurrentevent
	#define GET_vishfillcurrentevent(fl)  CAL_CMGETAPI( "vishfillcurrentevent" ) 
	#define CAL_vishfillcurrentevent  vishfillcurrentevent
	#define CHK_vishfillcurrentevent  TRUE
	#define EXP_vishfillcurrentevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishfillcurrentevent", (RTS_UINTPTR)vishfillcurrentevent, 1, RTSITF_GET_SIGNATURE(0, 0x73CA5FD9), 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_vishfillcurrentevent  PFVISHFILLCURRENTEVENT_IEC pfvishfillcurrentevent;
	#define EXT_vishfillcurrentevent  extern PFVISHFILLCURRENTEVENT_IEC pfvishfillcurrentevent;
	#define GET_vishfillcurrentevent(fl)  s_pfCMGetAPI2( "vishfillcurrentevent", (RTS_VOID_FCTPTR *)&pfvishfillcurrentevent, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x73CA5FD9), 0x03050600)
	#define CAL_vishfillcurrentevent  pfvishfillcurrentevent
	#define CHK_vishfillcurrentevent  (pfvishfillcurrentevent != NULL)
	#define EXP_vishfillcurrentevent   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishfillcurrentevent", (RTS_UINTPTR)vishfillcurrentevent, 1, RTSITF_GET_SIGNATURE(0, 0x73CA5FD9), 0x03050600) 
#endif


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

void CDECL CDECL_EXT vishgetclientid(vishgetclientid_struct *p);
typedef void (CDECL CDECL_EXT* PFVISHGETCLIENTID_IEC) (vishgetclientid_struct *p);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHGETCLIENTID_NOTIMPLEMENTED)
	#define USE_vishgetclientid
	#define EXT_vishgetclientid
	#define GET_vishgetclientid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_vishgetclientid(p0) 
	#define CHK_vishgetclientid  FALSE
	#define EXP_vishgetclientid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_vishgetclientid
	#define EXT_vishgetclientid
	#define GET_vishgetclientid(fl)  CAL_CMGETAPI( "vishgetclientid" ) 
	#define CAL_vishgetclientid  vishgetclientid
	#define CHK_vishgetclientid  TRUE
	#define EXP_vishgetclientid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishgetclientid", (RTS_UINTPTR)vishgetclientid, 1, RTSITF_GET_SIGNATURE(0, 0x96B89426), 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_vishgetclientid
	#define EXT_vishgetclientid
	#define GET_vishgetclientid(fl)  CAL_CMGETAPI( "vishgetclientid" ) 
	#define CAL_vishgetclientid  vishgetclientid
	#define CHK_vishgetclientid  TRUE
	#define EXP_vishgetclientid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishgetclientid", (RTS_UINTPTR)vishgetclientid, 1, RTSITF_GET_SIGNATURE(0, 0x96B89426), 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlervishgetclientid
	#define EXT_CmpVisuHandlervishgetclientid
	#define GET_CmpVisuHandlervishgetclientid  ERR_OK
	#define CAL_CmpVisuHandlervishgetclientid  vishgetclientid
	#define CHK_CmpVisuHandlervishgetclientid  TRUE
	#define EXP_CmpVisuHandlervishgetclientid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishgetclientid", (RTS_UINTPTR)vishgetclientid, 1, RTSITF_GET_SIGNATURE(0, 0x96B89426), 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_vishgetclientid
	#define EXT_vishgetclientid
	#define GET_vishgetclientid(fl)  CAL_CMGETAPI( "vishgetclientid" ) 
	#define CAL_vishgetclientid  vishgetclientid
	#define CHK_vishgetclientid  TRUE
	#define EXP_vishgetclientid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishgetclientid", (RTS_UINTPTR)vishgetclientid, 1, RTSITF_GET_SIGNATURE(0, 0x96B89426), 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_vishgetclientid  PFVISHGETCLIENTID_IEC pfvishgetclientid;
	#define EXT_vishgetclientid  extern PFVISHGETCLIENTID_IEC pfvishgetclientid;
	#define GET_vishgetclientid(fl)  s_pfCMGetAPI2( "vishgetclientid", (RTS_VOID_FCTPTR *)&pfvishgetclientid, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x96B89426), 0x03050600)
	#define CAL_vishgetclientid  pfvishgetclientid
	#define CHK_vishgetclientid  (pfvishgetclientid != NULL)
	#define EXP_vishgetclientid   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishgetclientid", (RTS_UINTPTR)vishgetclientid, 1, RTSITF_GET_SIGNATURE(0, 0x96B89426), 0x03050600) 
#endif


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

void CDECL CDECL_EXT vishgetcurrentevent(vishgetcurrentevent_struct *p);
typedef void (CDECL CDECL_EXT* PFVISHGETCURRENTEVENT_IEC) (vishgetcurrentevent_struct *p);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHGETCURRENTEVENT_NOTIMPLEMENTED)
	#define USE_vishgetcurrentevent
	#define EXT_vishgetcurrentevent
	#define GET_vishgetcurrentevent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_vishgetcurrentevent(p0) 
	#define CHK_vishgetcurrentevent  FALSE
	#define EXP_vishgetcurrentevent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_vishgetcurrentevent
	#define EXT_vishgetcurrentevent
	#define GET_vishgetcurrentevent(fl)  CAL_CMGETAPI( "vishgetcurrentevent" ) 
	#define CAL_vishgetcurrentevent  vishgetcurrentevent
	#define CHK_vishgetcurrentevent  TRUE
	#define EXP_vishgetcurrentevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishgetcurrentevent", (RTS_UINTPTR)vishgetcurrentevent, 1, RTSITF_GET_SIGNATURE(0, 0x786413F1), 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_vishgetcurrentevent
	#define EXT_vishgetcurrentevent
	#define GET_vishgetcurrentevent(fl)  CAL_CMGETAPI( "vishgetcurrentevent" ) 
	#define CAL_vishgetcurrentevent  vishgetcurrentevent
	#define CHK_vishgetcurrentevent  TRUE
	#define EXP_vishgetcurrentevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishgetcurrentevent", (RTS_UINTPTR)vishgetcurrentevent, 1, RTSITF_GET_SIGNATURE(0, 0x786413F1), 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlervishgetcurrentevent
	#define EXT_CmpVisuHandlervishgetcurrentevent
	#define GET_CmpVisuHandlervishgetcurrentevent  ERR_OK
	#define CAL_CmpVisuHandlervishgetcurrentevent  vishgetcurrentevent
	#define CHK_CmpVisuHandlervishgetcurrentevent  TRUE
	#define EXP_CmpVisuHandlervishgetcurrentevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishgetcurrentevent", (RTS_UINTPTR)vishgetcurrentevent, 1, RTSITF_GET_SIGNATURE(0, 0x786413F1), 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_vishgetcurrentevent
	#define EXT_vishgetcurrentevent
	#define GET_vishgetcurrentevent(fl)  CAL_CMGETAPI( "vishgetcurrentevent" ) 
	#define CAL_vishgetcurrentevent  vishgetcurrentevent
	#define CHK_vishgetcurrentevent  TRUE
	#define EXP_vishgetcurrentevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishgetcurrentevent", (RTS_UINTPTR)vishgetcurrentevent, 1, RTSITF_GET_SIGNATURE(0, 0x786413F1), 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_vishgetcurrentevent  PFVISHGETCURRENTEVENT_IEC pfvishgetcurrentevent;
	#define EXT_vishgetcurrentevent  extern PFVISHGETCURRENTEVENT_IEC pfvishgetcurrentevent;
	#define GET_vishgetcurrentevent(fl)  s_pfCMGetAPI2( "vishgetcurrentevent", (RTS_VOID_FCTPTR *)&pfvishgetcurrentevent, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x786413F1), 0x03050600)
	#define CAL_vishgetcurrentevent  pfvishgetcurrentevent
	#define CHK_vishgetcurrentevent  (pfvishgetcurrentevent != NULL)
	#define EXP_vishgetcurrentevent   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishgetcurrentevent", (RTS_UINTPTR)vishgetcurrentevent, 1, RTSITF_GET_SIGNATURE(0, 0x786413F1), 0x03050600) 
#endif


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

void CDECL CDECL_EXT vishhavetomanageclients(vishhavetomanageclients_struct *p);
typedef void (CDECL CDECL_EXT* PFVISHHAVETOMANAGECLIENTS_IEC) (vishhavetomanageclients_struct *p);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHHAVETOMANAGECLIENTS_NOTIMPLEMENTED)
	#define USE_vishhavetomanageclients
	#define EXT_vishhavetomanageclients
	#define GET_vishhavetomanageclients(fl)  ERR_NOTIMPLEMENTED
	#define CAL_vishhavetomanageclients(p0) 
	#define CHK_vishhavetomanageclients  FALSE
	#define EXP_vishhavetomanageclients  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_vishhavetomanageclients
	#define EXT_vishhavetomanageclients
	#define GET_vishhavetomanageclients(fl)  CAL_CMGETAPI( "vishhavetomanageclients" ) 
	#define CAL_vishhavetomanageclients  vishhavetomanageclients
	#define CHK_vishhavetomanageclients  TRUE
	#define EXP_vishhavetomanageclients  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishhavetomanageclients", (RTS_UINTPTR)vishhavetomanageclients, 1, RTSITF_GET_SIGNATURE(0, 0x2541155E), 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_vishhavetomanageclients
	#define EXT_vishhavetomanageclients
	#define GET_vishhavetomanageclients(fl)  CAL_CMGETAPI( "vishhavetomanageclients" ) 
	#define CAL_vishhavetomanageclients  vishhavetomanageclients
	#define CHK_vishhavetomanageclients  TRUE
	#define EXP_vishhavetomanageclients  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishhavetomanageclients", (RTS_UINTPTR)vishhavetomanageclients, 1, RTSITF_GET_SIGNATURE(0, 0x2541155E), 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlervishhavetomanageclients
	#define EXT_CmpVisuHandlervishhavetomanageclients
	#define GET_CmpVisuHandlervishhavetomanageclients  ERR_OK
	#define CAL_CmpVisuHandlervishhavetomanageclients  vishhavetomanageclients
	#define CHK_CmpVisuHandlervishhavetomanageclients  TRUE
	#define EXP_CmpVisuHandlervishhavetomanageclients  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishhavetomanageclients", (RTS_UINTPTR)vishhavetomanageclients, 1, RTSITF_GET_SIGNATURE(0, 0x2541155E), 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_vishhavetomanageclients
	#define EXT_vishhavetomanageclients
	#define GET_vishhavetomanageclients(fl)  CAL_CMGETAPI( "vishhavetomanageclients" ) 
	#define CAL_vishhavetomanageclients  vishhavetomanageclients
	#define CHK_vishhavetomanageclients  TRUE
	#define EXP_vishhavetomanageclients  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishhavetomanageclients", (RTS_UINTPTR)vishhavetomanageclients, 1, RTSITF_GET_SIGNATURE(0, 0x2541155E), 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_vishhavetomanageclients  PFVISHHAVETOMANAGECLIENTS_IEC pfvishhavetomanageclients;
	#define EXT_vishhavetomanageclients  extern PFVISHHAVETOMANAGECLIENTS_IEC pfvishhavetomanageclients;
	#define GET_vishhavetomanageclients(fl)  s_pfCMGetAPI2( "vishhavetomanageclients", (RTS_VOID_FCTPTR *)&pfvishhavetomanageclients, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x2541155E), 0x03050600)
	#define CAL_vishhavetomanageclients  pfvishhavetomanageclients
	#define CHK_vishhavetomanageclients  (pfvishhavetomanageclients != NULL)
	#define EXP_vishhavetomanageclients   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishhavetomanageclients", (RTS_UINTPTR)vishhavetomanageclients, 1, RTSITF_GET_SIGNATURE(0, 0x2541155E), 0x03050600) 
#endif


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

void CDECL CDECL_EXT vishhavetomanageclients2(vishhavetomanageclients2_struct *p);
typedef void (CDECL CDECL_EXT* PFVISHHAVETOMANAGECLIENTS2_IEC) (vishhavetomanageclients2_struct *p);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHHAVETOMANAGECLIENTS2_NOTIMPLEMENTED)
	#define USE_vishhavetomanageclients2
	#define EXT_vishhavetomanageclients2
	#define GET_vishhavetomanageclients2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_vishhavetomanageclients2(p0) 
	#define CHK_vishhavetomanageclients2  FALSE
	#define EXP_vishhavetomanageclients2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_vishhavetomanageclients2
	#define EXT_vishhavetomanageclients2
	#define GET_vishhavetomanageclients2(fl)  CAL_CMGETAPI( "vishhavetomanageclients2" ) 
	#define CAL_vishhavetomanageclients2  vishhavetomanageclients2
	#define CHK_vishhavetomanageclients2  TRUE
	#define EXP_vishhavetomanageclients2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishhavetomanageclients2", (RTS_UINTPTR)vishhavetomanageclients2, 1, RTSITF_GET_SIGNATURE(0, 0x68E999B9), 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_vishhavetomanageclients2
	#define EXT_vishhavetomanageclients2
	#define GET_vishhavetomanageclients2(fl)  CAL_CMGETAPI( "vishhavetomanageclients2" ) 
	#define CAL_vishhavetomanageclients2  vishhavetomanageclients2
	#define CHK_vishhavetomanageclients2  TRUE
	#define EXP_vishhavetomanageclients2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishhavetomanageclients2", (RTS_UINTPTR)vishhavetomanageclients2, 1, RTSITF_GET_SIGNATURE(0, 0x68E999B9), 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlervishhavetomanageclients2
	#define EXT_CmpVisuHandlervishhavetomanageclients2
	#define GET_CmpVisuHandlervishhavetomanageclients2  ERR_OK
	#define CAL_CmpVisuHandlervishhavetomanageclients2  vishhavetomanageclients2
	#define CHK_CmpVisuHandlervishhavetomanageclients2  TRUE
	#define EXP_CmpVisuHandlervishhavetomanageclients2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishhavetomanageclients2", (RTS_UINTPTR)vishhavetomanageclients2, 1, RTSITF_GET_SIGNATURE(0, 0x68E999B9), 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_vishhavetomanageclients2
	#define EXT_vishhavetomanageclients2
	#define GET_vishhavetomanageclients2(fl)  CAL_CMGETAPI( "vishhavetomanageclients2" ) 
	#define CAL_vishhavetomanageclients2  vishhavetomanageclients2
	#define CHK_vishhavetomanageclients2  TRUE
	#define EXP_vishhavetomanageclients2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishhavetomanageclients2", (RTS_UINTPTR)vishhavetomanageclients2, 1, RTSITF_GET_SIGNATURE(0, 0x68E999B9), 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_vishhavetomanageclients2  PFVISHHAVETOMANAGECLIENTS2_IEC pfvishhavetomanageclients2;
	#define EXT_vishhavetomanageclients2  extern PFVISHHAVETOMANAGECLIENTS2_IEC pfvishhavetomanageclients2;
	#define GET_vishhavetomanageclients2(fl)  s_pfCMGetAPI2( "vishhavetomanageclients2", (RTS_VOID_FCTPTR *)&pfvishhavetomanageclients2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x68E999B9), 0x03050600)
	#define CAL_vishhavetomanageclients2  pfvishhavetomanageclients2
	#define CHK_vishhavetomanageclients2  (pfvishhavetomanageclients2 != NULL)
	#define EXP_vishhavetomanageclients2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishhavetomanageclients2", (RTS_UINTPTR)vishhavetomanageclients2, 1, RTSITF_GET_SIGNATURE(0, 0x68E999B9), 0x03050600) 
#endif


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

void CDECL CDECL_EXT vishprintf(vishprintf_struct *p);
typedef void (CDECL CDECL_EXT* PFVISHPRINTF_IEC) (vishprintf_struct *p);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHPRINTF_NOTIMPLEMENTED)
	#define USE_vishprintf
	#define EXT_vishprintf
	#define GET_vishprintf(fl)  ERR_NOTIMPLEMENTED
	#define CAL_vishprintf(p0) 
	#define CHK_vishprintf  FALSE
	#define EXP_vishprintf  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_vishprintf
	#define EXT_vishprintf
	#define GET_vishprintf(fl)  CAL_CMGETAPI( "vishprintf" ) 
	#define CAL_vishprintf  vishprintf
	#define CHK_vishprintf  TRUE
	#define EXP_vishprintf  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishprintf", (RTS_UINTPTR)vishprintf, 1, RTSITF_GET_SIGNATURE(0, 0x5514EA1B), 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_vishprintf
	#define EXT_vishprintf
	#define GET_vishprintf(fl)  CAL_CMGETAPI( "vishprintf" ) 
	#define CAL_vishprintf  vishprintf
	#define CHK_vishprintf  TRUE
	#define EXP_vishprintf  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishprintf", (RTS_UINTPTR)vishprintf, 1, RTSITF_GET_SIGNATURE(0, 0x5514EA1B), 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlervishprintf
	#define EXT_CmpVisuHandlervishprintf
	#define GET_CmpVisuHandlervishprintf  ERR_OK
	#define CAL_CmpVisuHandlervishprintf  vishprintf
	#define CHK_CmpVisuHandlervishprintf  TRUE
	#define EXP_CmpVisuHandlervishprintf  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishprintf", (RTS_UINTPTR)vishprintf, 1, RTSITF_GET_SIGNATURE(0, 0x5514EA1B), 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_vishprintf
	#define EXT_vishprintf
	#define GET_vishprintf(fl)  CAL_CMGETAPI( "vishprintf" ) 
	#define CAL_vishprintf  vishprintf
	#define CHK_vishprintf  TRUE
	#define EXP_vishprintf  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishprintf", (RTS_UINTPTR)vishprintf, 1, RTSITF_GET_SIGNATURE(0, 0x5514EA1B), 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_vishprintf  PFVISHPRINTF_IEC pfvishprintf;
	#define EXT_vishprintf  extern PFVISHPRINTF_IEC pfvishprintf;
	#define GET_vishprintf(fl)  s_pfCMGetAPI2( "vishprintf", (RTS_VOID_FCTPTR *)&pfvishprintf, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x5514EA1B), 0x03050600)
	#define CAL_vishprintf  pfvishprintf
	#define CHK_vishprintf  (pfvishprintf != NULL)
	#define EXP_vishprintf   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishprintf", (RTS_UINTPTR)vishprintf, 1, RTSITF_GET_SIGNATURE(0, 0x5514EA1B), 0x03050600) 
#endif


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

void CDECL CDECL_EXT vishprintfw(vishprintfw_struct *p);
typedef void (CDECL CDECL_EXT* PFVISHPRINTFW_IEC) (vishprintfw_struct *p);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHPRINTFW_NOTIMPLEMENTED)
	#define USE_vishprintfw
	#define EXT_vishprintfw
	#define GET_vishprintfw(fl)  ERR_NOTIMPLEMENTED
	#define CAL_vishprintfw(p0) 
	#define CHK_vishprintfw  FALSE
	#define EXP_vishprintfw  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_vishprintfw
	#define EXT_vishprintfw
	#define GET_vishprintfw(fl)  CAL_CMGETAPI( "vishprintfw" ) 
	#define CAL_vishprintfw  vishprintfw
	#define CHK_vishprintfw  TRUE
	#define EXP_vishprintfw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishprintfw", (RTS_UINTPTR)vishprintfw, 1, RTSITF_GET_SIGNATURE(0, 0xE3A4DA48), 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_vishprintfw
	#define EXT_vishprintfw
	#define GET_vishprintfw(fl)  CAL_CMGETAPI( "vishprintfw" ) 
	#define CAL_vishprintfw  vishprintfw
	#define CHK_vishprintfw  TRUE
	#define EXP_vishprintfw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishprintfw", (RTS_UINTPTR)vishprintfw, 1, RTSITF_GET_SIGNATURE(0, 0xE3A4DA48), 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlervishprintfw
	#define EXT_CmpVisuHandlervishprintfw
	#define GET_CmpVisuHandlervishprintfw  ERR_OK
	#define CAL_CmpVisuHandlervishprintfw  vishprintfw
	#define CHK_CmpVisuHandlervishprintfw  TRUE
	#define EXP_CmpVisuHandlervishprintfw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishprintfw", (RTS_UINTPTR)vishprintfw, 1, RTSITF_GET_SIGNATURE(0, 0xE3A4DA48), 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_vishprintfw
	#define EXT_vishprintfw
	#define GET_vishprintfw(fl)  CAL_CMGETAPI( "vishprintfw" ) 
	#define CAL_vishprintfw  vishprintfw
	#define CHK_vishprintfw  TRUE
	#define EXP_vishprintfw  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishprintfw", (RTS_UINTPTR)vishprintfw, 1, RTSITF_GET_SIGNATURE(0, 0xE3A4DA48), 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_vishprintfw  PFVISHPRINTFW_IEC pfvishprintfw;
	#define EXT_vishprintfw  extern PFVISHPRINTFW_IEC pfvishprintfw;
	#define GET_vishprintfw(fl)  s_pfCMGetAPI2( "vishprintfw", (RTS_VOID_FCTPTR *)&pfvishprintfw, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xE3A4DA48), 0x03050600)
	#define CAL_vishprintfw  pfvishprintfw
	#define CHK_vishprintfw  (pfvishprintfw != NULL)
	#define EXP_vishprintfw   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishprintfw", (RTS_UINTPTR)vishprintfw, 1, RTSITF_GET_SIGNATURE(0, 0xE3A4DA48), 0x03050600) 
#endif


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

void CDECL CDECL_EXT vishremovecurrentevent(vishremovecurrentevent_struct *p);
typedef void (CDECL CDECL_EXT* PFVISHREMOVECURRENTEVENT_IEC) (vishremovecurrentevent_struct *p);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHREMOVECURRENTEVENT_NOTIMPLEMENTED)
	#define USE_vishremovecurrentevent
	#define EXT_vishremovecurrentevent
	#define GET_vishremovecurrentevent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_vishremovecurrentevent(p0) 
	#define CHK_vishremovecurrentevent  FALSE
	#define EXP_vishremovecurrentevent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_vishremovecurrentevent
	#define EXT_vishremovecurrentevent
	#define GET_vishremovecurrentevent(fl)  CAL_CMGETAPI( "vishremovecurrentevent" ) 
	#define CAL_vishremovecurrentevent  vishremovecurrentevent
	#define CHK_vishremovecurrentevent  TRUE
	#define EXP_vishremovecurrentevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishremovecurrentevent", (RTS_UINTPTR)vishremovecurrentevent, 1, RTSITF_GET_SIGNATURE(0, 0x033E84DC), 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_vishremovecurrentevent
	#define EXT_vishremovecurrentevent
	#define GET_vishremovecurrentevent(fl)  CAL_CMGETAPI( "vishremovecurrentevent" ) 
	#define CAL_vishremovecurrentevent  vishremovecurrentevent
	#define CHK_vishremovecurrentevent  TRUE
	#define EXP_vishremovecurrentevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishremovecurrentevent", (RTS_UINTPTR)vishremovecurrentevent, 1, RTSITF_GET_SIGNATURE(0, 0x033E84DC), 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlervishremovecurrentevent
	#define EXT_CmpVisuHandlervishremovecurrentevent
	#define GET_CmpVisuHandlervishremovecurrentevent  ERR_OK
	#define CAL_CmpVisuHandlervishremovecurrentevent  vishremovecurrentevent
	#define CHK_CmpVisuHandlervishremovecurrentevent  TRUE
	#define EXP_CmpVisuHandlervishremovecurrentevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishremovecurrentevent", (RTS_UINTPTR)vishremovecurrentevent, 1, RTSITF_GET_SIGNATURE(0, 0x033E84DC), 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_vishremovecurrentevent
	#define EXT_vishremovecurrentevent
	#define GET_vishremovecurrentevent(fl)  CAL_CMGETAPI( "vishremovecurrentevent" ) 
	#define CAL_vishremovecurrentevent  vishremovecurrentevent
	#define CHK_vishremovecurrentevent  TRUE
	#define EXP_vishremovecurrentevent  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishremovecurrentevent", (RTS_UINTPTR)vishremovecurrentevent, 1, RTSITF_GET_SIGNATURE(0, 0x033E84DC), 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_vishremovecurrentevent  PFVISHREMOVECURRENTEVENT_IEC pfvishremovecurrentevent;
	#define EXT_vishremovecurrentevent  extern PFVISHREMOVECURRENTEVENT_IEC pfvishremovecurrentevent;
	#define GET_vishremovecurrentevent(fl)  s_pfCMGetAPI2( "vishremovecurrentevent", (RTS_VOID_FCTPTR *)&pfvishremovecurrentevent, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x033E84DC), 0x03050600)
	#define CAL_vishremovecurrentevent  pfvishremovecurrentevent
	#define CHK_vishremovecurrentevent  (pfvishremovecurrentevent != NULL)
	#define EXP_vishremovecurrentevent   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishremovecurrentevent", (RTS_UINTPTR)vishremovecurrentevent, 1, RTSITF_GET_SIGNATURE(0, 0x033E84DC), 0x03050600) 
#endif


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

void CDECL CDECL_EXT vishsetclientdata(vishsetclientdata_struct *p);
typedef void (CDECL CDECL_EXT* PFVISHSETCLIENTDATA_IEC) (vishsetclientdata_struct *p);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHSETCLIENTDATA_NOTIMPLEMENTED)
	#define USE_vishsetclientdata
	#define EXT_vishsetclientdata
	#define GET_vishsetclientdata(fl)  ERR_NOTIMPLEMENTED
	#define CAL_vishsetclientdata(p0) 
	#define CHK_vishsetclientdata  FALSE
	#define EXP_vishsetclientdata  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_vishsetclientdata
	#define EXT_vishsetclientdata
	#define GET_vishsetclientdata(fl)  CAL_CMGETAPI( "vishsetclientdata" ) 
	#define CAL_vishsetclientdata  vishsetclientdata
	#define CHK_vishsetclientdata  TRUE
	#define EXP_vishsetclientdata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishsetclientdata", (RTS_UINTPTR)vishsetclientdata, 1, RTSITF_GET_SIGNATURE(0, 0x474A3B55), 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_vishsetclientdata
	#define EXT_vishsetclientdata
	#define GET_vishsetclientdata(fl)  CAL_CMGETAPI( "vishsetclientdata" ) 
	#define CAL_vishsetclientdata  vishsetclientdata
	#define CHK_vishsetclientdata  TRUE
	#define EXP_vishsetclientdata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishsetclientdata", (RTS_UINTPTR)vishsetclientdata, 1, RTSITF_GET_SIGNATURE(0, 0x474A3B55), 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlervishsetclientdata
	#define EXT_CmpVisuHandlervishsetclientdata
	#define GET_CmpVisuHandlervishsetclientdata  ERR_OK
	#define CAL_CmpVisuHandlervishsetclientdata  vishsetclientdata
	#define CHK_CmpVisuHandlervishsetclientdata  TRUE
	#define EXP_CmpVisuHandlervishsetclientdata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishsetclientdata", (RTS_UINTPTR)vishsetclientdata, 1, RTSITF_GET_SIGNATURE(0, 0x474A3B55), 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_vishsetclientdata
	#define EXT_vishsetclientdata
	#define GET_vishsetclientdata(fl)  CAL_CMGETAPI( "vishsetclientdata" ) 
	#define CAL_vishsetclientdata  vishsetclientdata
	#define CHK_vishsetclientdata  TRUE
	#define EXP_vishsetclientdata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishsetclientdata", (RTS_UINTPTR)vishsetclientdata, 1, RTSITF_GET_SIGNATURE(0, 0x474A3B55), 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_vishsetclientdata  PFVISHSETCLIENTDATA_IEC pfvishsetclientdata;
	#define EXT_vishsetclientdata  extern PFVISHSETCLIENTDATA_IEC pfvishsetclientdata;
	#define GET_vishsetclientdata(fl)  s_pfCMGetAPI2( "vishsetclientdata", (RTS_VOID_FCTPTR *)&pfvishsetclientdata, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x474A3B55), 0x03050600)
	#define CAL_vishsetclientdata  pfvishsetclientdata
	#define CHK_vishsetclientdata  (pfvishsetclientdata != NULL)
	#define EXP_vishsetclientdata   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishsetclientdata", (RTS_UINTPTR)vishsetclientdata, 1, RTSITF_GET_SIGNATURE(0, 0x474A3B55), 0x03050600) 
#endif


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

void CDECL CDECL_EXT vishstartvisu(vishstartvisu_struct *p);
typedef void (CDECL CDECL_EXT* PFVISHSTARTVISU_IEC) (vishstartvisu_struct *p);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHSTARTVISU_NOTIMPLEMENTED)
	#define USE_vishstartvisu
	#define EXT_vishstartvisu
	#define GET_vishstartvisu(fl)  ERR_NOTIMPLEMENTED
	#define CAL_vishstartvisu(p0) 
	#define CHK_vishstartvisu  FALSE
	#define EXP_vishstartvisu  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_vishstartvisu
	#define EXT_vishstartvisu
	#define GET_vishstartvisu(fl)  CAL_CMGETAPI( "vishstartvisu" ) 
	#define CAL_vishstartvisu  vishstartvisu
	#define CHK_vishstartvisu  TRUE
	#define EXP_vishstartvisu  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishstartvisu", (RTS_UINTPTR)vishstartvisu, 1, RTSITF_GET_SIGNATURE(0, 0x8E8D0ABE), 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_vishstartvisu
	#define EXT_vishstartvisu
	#define GET_vishstartvisu(fl)  CAL_CMGETAPI( "vishstartvisu" ) 
	#define CAL_vishstartvisu  vishstartvisu
	#define CHK_vishstartvisu  TRUE
	#define EXP_vishstartvisu  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishstartvisu", (RTS_UINTPTR)vishstartvisu, 1, RTSITF_GET_SIGNATURE(0, 0x8E8D0ABE), 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlervishstartvisu
	#define EXT_CmpVisuHandlervishstartvisu
	#define GET_CmpVisuHandlervishstartvisu  ERR_OK
	#define CAL_CmpVisuHandlervishstartvisu  vishstartvisu
	#define CHK_CmpVisuHandlervishstartvisu  TRUE
	#define EXP_CmpVisuHandlervishstartvisu  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishstartvisu", (RTS_UINTPTR)vishstartvisu, 1, RTSITF_GET_SIGNATURE(0, 0x8E8D0ABE), 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_vishstartvisu
	#define EXT_vishstartvisu
	#define GET_vishstartvisu(fl)  CAL_CMGETAPI( "vishstartvisu" ) 
	#define CAL_vishstartvisu  vishstartvisu
	#define CHK_vishstartvisu  TRUE
	#define EXP_vishstartvisu  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishstartvisu", (RTS_UINTPTR)vishstartvisu, 1, RTSITF_GET_SIGNATURE(0, 0x8E8D0ABE), 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_vishstartvisu  PFVISHSTARTVISU_IEC pfvishstartvisu;
	#define EXT_vishstartvisu  extern PFVISHSTARTVISU_IEC pfvishstartvisu;
	#define GET_vishstartvisu(fl)  s_pfCMGetAPI2( "vishstartvisu", (RTS_VOID_FCTPTR *)&pfvishstartvisu, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x8E8D0ABE), 0x03050600)
	#define CAL_vishstartvisu  pfvishstartvisu
	#define CHK_vishstartvisu  (pfvishstartvisu != NULL)
	#define EXP_vishstartvisu   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishstartvisu", (RTS_UINTPTR)vishstartvisu, 1, RTSITF_GET_SIGNATURE(0, 0x8E8D0ABE), 0x03050600) 
#endif


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

void CDECL CDECL_EXT vishwritevalueifvalid(vishwritevalueifvalid_struct *p);
typedef void (CDECL CDECL_EXT* PFVISHWRITEVALUEIFVALID_IEC) (vishwritevalueifvalid_struct *p);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHWRITEVALUEIFVALID_NOTIMPLEMENTED)
	#define USE_vishwritevalueifvalid
	#define EXT_vishwritevalueifvalid
	#define GET_vishwritevalueifvalid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_vishwritevalueifvalid(p0) 
	#define CHK_vishwritevalueifvalid  FALSE
	#define EXP_vishwritevalueifvalid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_vishwritevalueifvalid
	#define EXT_vishwritevalueifvalid
	#define GET_vishwritevalueifvalid(fl)  CAL_CMGETAPI( "vishwritevalueifvalid" ) 
	#define CAL_vishwritevalueifvalid  vishwritevalueifvalid
	#define CHK_vishwritevalueifvalid  TRUE
	#define EXP_vishwritevalueifvalid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishwritevalueifvalid", (RTS_UINTPTR)vishwritevalueifvalid, 1, RTSITF_GET_SIGNATURE(0, 0x390D7585), 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_vishwritevalueifvalid
	#define EXT_vishwritevalueifvalid
	#define GET_vishwritevalueifvalid(fl)  CAL_CMGETAPI( "vishwritevalueifvalid" ) 
	#define CAL_vishwritevalueifvalid  vishwritevalueifvalid
	#define CHK_vishwritevalueifvalid  TRUE
	#define EXP_vishwritevalueifvalid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishwritevalueifvalid", (RTS_UINTPTR)vishwritevalueifvalid, 1, RTSITF_GET_SIGNATURE(0, 0x390D7585), 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlervishwritevalueifvalid
	#define EXT_CmpVisuHandlervishwritevalueifvalid
	#define GET_CmpVisuHandlervishwritevalueifvalid  ERR_OK
	#define CAL_CmpVisuHandlervishwritevalueifvalid  vishwritevalueifvalid
	#define CHK_CmpVisuHandlervishwritevalueifvalid  TRUE
	#define EXP_CmpVisuHandlervishwritevalueifvalid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishwritevalueifvalid", (RTS_UINTPTR)vishwritevalueifvalid, 1, RTSITF_GET_SIGNATURE(0, 0x390D7585), 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_vishwritevalueifvalid
	#define EXT_vishwritevalueifvalid
	#define GET_vishwritevalueifvalid(fl)  CAL_CMGETAPI( "vishwritevalueifvalid" ) 
	#define CAL_vishwritevalueifvalid  vishwritevalueifvalid
	#define CHK_vishwritevalueifvalid  TRUE
	#define EXP_vishwritevalueifvalid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishwritevalueifvalid", (RTS_UINTPTR)vishwritevalueifvalid, 1, RTSITF_GET_SIGNATURE(0, 0x390D7585), 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_vishwritevalueifvalid  PFVISHWRITEVALUEIFVALID_IEC pfvishwritevalueifvalid;
	#define EXT_vishwritevalueifvalid  extern PFVISHWRITEVALUEIFVALID_IEC pfvishwritevalueifvalid;
	#define GET_vishwritevalueifvalid(fl)  s_pfCMGetAPI2( "vishwritevalueifvalid", (RTS_VOID_FCTPTR *)&pfvishwritevalueifvalid, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x390D7585), 0x03050600)
	#define CAL_vishwritevalueifvalid  pfvishwritevalueifvalid
	#define CHK_vishwritevalueifvalid  (pfvishwritevalueifvalid != NULL)
	#define EXP_vishwritevalueifvalid   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"vishwritevalueifvalid", (RTS_UINTPTR)vishwritevalueifvalid, 1, RTSITF_GET_SIGNATURE(0, 0x390D7585), 0x03050600) 
#endif


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
ExternID CDECL VishRegisterClient(char* pszAppName, RTS_IEC_DWORD dwFlags);
typedef ExternID (CDECL * PFVISHREGISTERCLIENT) (char* pszAppName, RTS_IEC_DWORD dwFlags);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHREGISTERCLIENT_NOTIMPLEMENTED)
	#define USE_VishRegisterClient
	#define EXT_VishRegisterClient
	#define GET_VishRegisterClient(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VishRegisterClient(p0,p1) (ExternID)ERR_NOTIMPLEMENTED
	#define CHK_VishRegisterClient  FALSE
	#define EXP_VishRegisterClient  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VishRegisterClient
	#define EXT_VishRegisterClient
	#define GET_VishRegisterClient(fl)  CAL_CMGETAPI( "VishRegisterClient" ) 
	#define CAL_VishRegisterClient  VishRegisterClient
	#define CHK_VishRegisterClient  TRUE
	#define EXP_VishRegisterClient  CAL_CMEXPAPI( "VishRegisterClient" ) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_VishRegisterClient
	#define EXT_VishRegisterClient
	#define GET_VishRegisterClient(fl)  CAL_CMGETAPI( "VishRegisterClient" ) 
	#define CAL_VishRegisterClient  VishRegisterClient
	#define CHK_VishRegisterClient  TRUE
	#define EXP_VishRegisterClient  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishRegisterClient", (RTS_UINTPTR)VishRegisterClient, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlerVishRegisterClient
	#define EXT_CmpVisuHandlerVishRegisterClient
	#define GET_CmpVisuHandlerVishRegisterClient  ERR_OK
	#define CAL_CmpVisuHandlerVishRegisterClient  VishRegisterClient
	#define CHK_CmpVisuHandlerVishRegisterClient  TRUE
	#define EXP_CmpVisuHandlerVishRegisterClient  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VishRegisterClient
	#define EXT_VishRegisterClient
	#define GET_VishRegisterClient(fl)  CAL_CMGETAPI( "VishRegisterClient" ) 
	#define CAL_VishRegisterClient  VishRegisterClient
	#define CHK_VishRegisterClient  TRUE
	#define EXP_VishRegisterClient  CAL_CMEXPAPI( "VishRegisterClient" ) 
#else /* DYNAMIC_LINK */
	#define USE_VishRegisterClient  PFVISHREGISTERCLIENT pfVishRegisterClient;
	#define EXT_VishRegisterClient  extern PFVISHREGISTERCLIENT pfVishRegisterClient;
	#define GET_VishRegisterClient(fl)  s_pfCMGetAPI2( "VishRegisterClient", (RTS_VOID_FCTPTR *)&pfVishRegisterClient, (fl), 0, 0)
	#define CAL_VishRegisterClient  pfVishRegisterClient
	#define CHK_VishRegisterClient  (pfVishRegisterClient != NULL)
	#define EXP_VishRegisterClient   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishRegisterClient", (RTS_UINTPTR)VishRegisterClient, 0, 0) 
#endif


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
ExternID CDECL VishRegisterClient2(char* pszAppName, RTS_IEC_DWORD dwFlags, RTS_UI32 numClientTags, Visu_ClientTagData* pTags);
typedef ExternID (CDECL * PFVISHREGISTERCLIENT2) (char* pszAppName, RTS_IEC_DWORD dwFlags, RTS_UI32 numClientTags, Visu_ClientTagData* pTags);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHREGISTERCLIENT2_NOTIMPLEMENTED)
	#define USE_VishRegisterClient2
	#define EXT_VishRegisterClient2
	#define GET_VishRegisterClient2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VishRegisterClient2(p0,p1,p2,p3) (ExternID)ERR_NOTIMPLEMENTED
	#define CHK_VishRegisterClient2  FALSE
	#define EXP_VishRegisterClient2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VishRegisterClient2
	#define EXT_VishRegisterClient2
	#define GET_VishRegisterClient2(fl)  CAL_CMGETAPI( "VishRegisterClient2" ) 
	#define CAL_VishRegisterClient2  VishRegisterClient2
	#define CHK_VishRegisterClient2  TRUE
	#define EXP_VishRegisterClient2  CAL_CMEXPAPI( "VishRegisterClient2" ) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_VishRegisterClient2
	#define EXT_VishRegisterClient2
	#define GET_VishRegisterClient2(fl)  CAL_CMGETAPI( "VishRegisterClient2" ) 
	#define CAL_VishRegisterClient2  VishRegisterClient2
	#define CHK_VishRegisterClient2  TRUE
	#define EXP_VishRegisterClient2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishRegisterClient2", (RTS_UINTPTR)VishRegisterClient2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlerVishRegisterClient2
	#define EXT_CmpVisuHandlerVishRegisterClient2
	#define GET_CmpVisuHandlerVishRegisterClient2  ERR_OK
	#define CAL_CmpVisuHandlerVishRegisterClient2  VishRegisterClient2
	#define CHK_CmpVisuHandlerVishRegisterClient2  TRUE
	#define EXP_CmpVisuHandlerVishRegisterClient2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VishRegisterClient2
	#define EXT_VishRegisterClient2
	#define GET_VishRegisterClient2(fl)  CAL_CMGETAPI( "VishRegisterClient2" ) 
	#define CAL_VishRegisterClient2  VishRegisterClient2
	#define CHK_VishRegisterClient2  TRUE
	#define EXP_VishRegisterClient2  CAL_CMEXPAPI( "VishRegisterClient2" ) 
#else /* DYNAMIC_LINK */
	#define USE_VishRegisterClient2  PFVISHREGISTERCLIENT2 pfVishRegisterClient2;
	#define EXT_VishRegisterClient2  extern PFVISHREGISTERCLIENT2 pfVishRegisterClient2;
	#define GET_VishRegisterClient2(fl)  s_pfCMGetAPI2( "VishRegisterClient2", (RTS_VOID_FCTPTR *)&pfVishRegisterClient2, (fl), 0, 0)
	#define CAL_VishRegisterClient2  pfVishRegisterClient2
	#define CHK_VishRegisterClient2  (pfVishRegisterClient2 != NULL)
	#define EXP_VishRegisterClient2   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishRegisterClient2", (RTS_UINTPTR)VishRegisterClient2, 0, 0) 
#endif


/**
 * <description> Function to obtain the real ID from the IEC-Task. </description>
 * <result>If the ID is not equal to INVALID_IEC_ID it can be used, otherwise this 
 * function has to be called some times more until a valid ID is returned</result>
 */
RTS_UI32 CDECL VishIsRegistered(ExternID extID);
typedef RTS_UI32 (CDECL * PFVISHISREGISTERED) (ExternID extID);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHISREGISTERED_NOTIMPLEMENTED)
	#define USE_VishIsRegistered
	#define EXT_VishIsRegistered
	#define GET_VishIsRegistered(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VishIsRegistered(p0) (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_VishIsRegistered  FALSE
	#define EXP_VishIsRegistered  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VishIsRegistered
	#define EXT_VishIsRegistered
	#define GET_VishIsRegistered(fl)  CAL_CMGETAPI( "VishIsRegistered" ) 
	#define CAL_VishIsRegistered  VishIsRegistered
	#define CHK_VishIsRegistered  TRUE
	#define EXP_VishIsRegistered  CAL_CMEXPAPI( "VishIsRegistered" ) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_VishIsRegistered
	#define EXT_VishIsRegistered
	#define GET_VishIsRegistered(fl)  CAL_CMGETAPI( "VishIsRegistered" ) 
	#define CAL_VishIsRegistered  VishIsRegistered
	#define CHK_VishIsRegistered  TRUE
	#define EXP_VishIsRegistered  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishIsRegistered", (RTS_UINTPTR)VishIsRegistered, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlerVishIsRegistered
	#define EXT_CmpVisuHandlerVishIsRegistered
	#define GET_CmpVisuHandlerVishIsRegistered  ERR_OK
	#define CAL_CmpVisuHandlerVishIsRegistered  VishIsRegistered
	#define CHK_CmpVisuHandlerVishIsRegistered  TRUE
	#define EXP_CmpVisuHandlerVishIsRegistered  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VishIsRegistered
	#define EXT_VishIsRegistered
	#define GET_VishIsRegistered(fl)  CAL_CMGETAPI( "VishIsRegistered" ) 
	#define CAL_VishIsRegistered  VishIsRegistered
	#define CHK_VishIsRegistered  TRUE
	#define EXP_VishIsRegistered  CAL_CMEXPAPI( "VishIsRegistered" ) 
#else /* DYNAMIC_LINK */
	#define USE_VishIsRegistered  PFVISHISREGISTERED pfVishIsRegistered;
	#define EXT_VishIsRegistered  extern PFVISHISREGISTERED pfVishIsRegistered;
	#define GET_VishIsRegistered(fl)  s_pfCMGetAPI2( "VishIsRegistered", (RTS_VOID_FCTPTR *)&pfVishIsRegistered, (fl), 0, 0)
	#define CAL_VishIsRegistered  pfVishIsRegistered
	#define CHK_VishIsRegistered  (pfVishIsRegistered != NULL)
	#define EXP_VishIsRegistered   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishIsRegistered", (RTS_UINTPTR)VishIsRegistered, 0, 0) 
#endif


/**
 * <description> Function to remove a Visuclient with a specific ID.</description>
 * <result></result>
 */
void CDECL VishRemoveClient(ExternID extID);
typedef void (CDECL * PFVISHREMOVECLIENT) (ExternID extID);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHREMOVECLIENT_NOTIMPLEMENTED)
	#define USE_VishRemoveClient
	#define EXT_VishRemoveClient
	#define GET_VishRemoveClient(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VishRemoveClient(p0) 
	#define CHK_VishRemoveClient  FALSE
	#define EXP_VishRemoveClient  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VishRemoveClient
	#define EXT_VishRemoveClient
	#define GET_VishRemoveClient(fl)  CAL_CMGETAPI( "VishRemoveClient" ) 
	#define CAL_VishRemoveClient  VishRemoveClient
	#define CHK_VishRemoveClient  TRUE
	#define EXP_VishRemoveClient  CAL_CMEXPAPI( "VishRemoveClient" ) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_VishRemoveClient
	#define EXT_VishRemoveClient
	#define GET_VishRemoveClient(fl)  CAL_CMGETAPI( "VishRemoveClient" ) 
	#define CAL_VishRemoveClient  VishRemoveClient
	#define CHK_VishRemoveClient  TRUE
	#define EXP_VishRemoveClient  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishRemoveClient", (RTS_UINTPTR)VishRemoveClient, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlerVishRemoveClient
	#define EXT_CmpVisuHandlerVishRemoveClient
	#define GET_CmpVisuHandlerVishRemoveClient  ERR_OK
	#define CAL_CmpVisuHandlerVishRemoveClient  VishRemoveClient
	#define CHK_CmpVisuHandlerVishRemoveClient  TRUE
	#define EXP_CmpVisuHandlerVishRemoveClient  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VishRemoveClient
	#define EXT_VishRemoveClient
	#define GET_VishRemoveClient(fl)  CAL_CMGETAPI( "VishRemoveClient" ) 
	#define CAL_VishRemoveClient  VishRemoveClient
	#define CHK_VishRemoveClient  TRUE
	#define EXP_VishRemoveClient  CAL_CMEXPAPI( "VishRemoveClient" ) 
#else /* DYNAMIC_LINK */
	#define USE_VishRemoveClient  PFVISHREMOVECLIENT pfVishRemoveClient;
	#define EXT_VishRemoveClient  extern PFVISHREMOVECLIENT pfVishRemoveClient;
	#define GET_VishRemoveClient(fl)  s_pfCMGetAPI2( "VishRemoveClient", (RTS_VOID_FCTPTR *)&pfVishRemoveClient, (fl), 0, 0)
	#define CAL_VishRemoveClient  pfVishRemoveClient
	#define CHK_VishRemoveClient  (pfVishRemoveClient != NULL)
	#define EXP_VishRemoveClient   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishRemoveClient", (RTS_UINTPTR)VishRemoveClient, 0, 0) 
#endif


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
int CDECL VishGetPaintData(EventStruct* pEvent, CommandBuffer** pCmdsResult);
typedef int (CDECL * PFVISHGETPAINTDATA) (EventStruct* pEvent, CommandBuffer** pCmdsResult);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHGETPAINTDATA_NOTIMPLEMENTED)
	#define USE_VishGetPaintData
	#define EXT_VishGetPaintData
	#define GET_VishGetPaintData(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VishGetPaintData(p0,p1) (int)ERR_NOTIMPLEMENTED
	#define CHK_VishGetPaintData  FALSE
	#define EXP_VishGetPaintData  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VishGetPaintData
	#define EXT_VishGetPaintData
	#define GET_VishGetPaintData(fl)  CAL_CMGETAPI( "VishGetPaintData" ) 
	#define CAL_VishGetPaintData  VishGetPaintData
	#define CHK_VishGetPaintData  TRUE
	#define EXP_VishGetPaintData  CAL_CMEXPAPI( "VishGetPaintData" ) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_VishGetPaintData
	#define EXT_VishGetPaintData
	#define GET_VishGetPaintData(fl)  CAL_CMGETAPI( "VishGetPaintData" ) 
	#define CAL_VishGetPaintData  VishGetPaintData
	#define CHK_VishGetPaintData  TRUE
	#define EXP_VishGetPaintData  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishGetPaintData", (RTS_UINTPTR)VishGetPaintData, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlerVishGetPaintData
	#define EXT_CmpVisuHandlerVishGetPaintData
	#define GET_CmpVisuHandlerVishGetPaintData  ERR_OK
	#define CAL_CmpVisuHandlerVishGetPaintData  VishGetPaintData
	#define CHK_CmpVisuHandlerVishGetPaintData  TRUE
	#define EXP_CmpVisuHandlerVishGetPaintData  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VishGetPaintData
	#define EXT_VishGetPaintData
	#define GET_VishGetPaintData(fl)  CAL_CMGETAPI( "VishGetPaintData" ) 
	#define CAL_VishGetPaintData  VishGetPaintData
	#define CHK_VishGetPaintData  TRUE
	#define EXP_VishGetPaintData  CAL_CMEXPAPI( "VishGetPaintData" ) 
#else /* DYNAMIC_LINK */
	#define USE_VishGetPaintData  PFVISHGETPAINTDATA pfVishGetPaintData;
	#define EXT_VishGetPaintData  extern PFVISHGETPAINTDATA pfVishGetPaintData;
	#define GET_VishGetPaintData(fl)  s_pfCMGetAPI2( "VishGetPaintData", (RTS_VOID_FCTPTR *)&pfVishGetPaintData, (fl), 0, 0)
	#define CAL_VishGetPaintData  pfVishGetPaintData
	#define CHK_VishGetPaintData  (pfVishGetPaintData != NULL)
	#define EXP_VishGetPaintData   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishGetPaintData", (RTS_UINTPTR)VishGetPaintData, 0, 0) 
#endif


/**
 * <description> Function to deliver the current event, inkl. monitoring. This call will only post an event to the queue
 *	it will not retrieve the currently available paint data! </description>
 * <param name="pEvent">The Event to handle</param>
 * <result>An errorcode signaling whether the call was successfull. ERR_OK, if everything is ok, ERR_NOBUFFER if
 *	the event could not be added to the underlying eventbuffer. A returnvalue of INVALID_IEC_ID
 * signals that the request concerned a not registered Client. This could also be the result of a download between
 * the calls to GetPaintData.</result>
 */
int CDECL VishPostEvent(EventStruct* pEvent);
typedef int (CDECL * PFVISHPOSTEVENT) (EventStruct* pEvent);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHPOSTEVENT_NOTIMPLEMENTED)
	#define USE_VishPostEvent
	#define EXT_VishPostEvent
	#define GET_VishPostEvent(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VishPostEvent(p0) (int)ERR_NOTIMPLEMENTED
	#define CHK_VishPostEvent  FALSE
	#define EXP_VishPostEvent  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VishPostEvent
	#define EXT_VishPostEvent
	#define GET_VishPostEvent(fl)  CAL_CMGETAPI( "VishPostEvent" ) 
	#define CAL_VishPostEvent  VishPostEvent
	#define CHK_VishPostEvent  TRUE
	#define EXP_VishPostEvent  CAL_CMEXPAPI( "VishPostEvent" ) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_VishPostEvent
	#define EXT_VishPostEvent
	#define GET_VishPostEvent(fl)  CAL_CMGETAPI( "VishPostEvent" ) 
	#define CAL_VishPostEvent  VishPostEvent
	#define CHK_VishPostEvent  TRUE
	#define EXP_VishPostEvent  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishPostEvent", (RTS_UINTPTR)VishPostEvent, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlerVishPostEvent
	#define EXT_CmpVisuHandlerVishPostEvent
	#define GET_CmpVisuHandlerVishPostEvent  ERR_OK
	#define CAL_CmpVisuHandlerVishPostEvent  VishPostEvent
	#define CHK_CmpVisuHandlerVishPostEvent  TRUE
	#define EXP_CmpVisuHandlerVishPostEvent  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VishPostEvent
	#define EXT_VishPostEvent
	#define GET_VishPostEvent(fl)  CAL_CMGETAPI( "VishPostEvent" ) 
	#define CAL_VishPostEvent  VishPostEvent
	#define CHK_VishPostEvent  TRUE
	#define EXP_VishPostEvent  CAL_CMEXPAPI( "VishPostEvent" ) 
#else /* DYNAMIC_LINK */
	#define USE_VishPostEvent  PFVISHPOSTEVENT pfVishPostEvent;
	#define EXT_VishPostEvent  extern PFVISHPOSTEVENT pfVishPostEvent;
	#define GET_VishPostEvent(fl)  s_pfCMGetAPI2( "VishPostEvent", (RTS_VOID_FCTPTR *)&pfVishPostEvent, (fl), 0, 0)
	#define CAL_VishPostEvent  pfVishPostEvent
	#define CHK_VishPostEvent  (pfVishPostEvent != NULL)
	#define EXP_VishPostEvent   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishPostEvent", (RTS_UINTPTR)VishPostEvent, 0, 0) 
#endif


/**
 * <description> Function that releases the paintbuffer, ie. allows an update of the visualization. 
 *	Call this function after the client has finished using the paintbuffer, ie. the client has interpreted the 
 *	commands or copied the buffer. </description>
 * <param name="extID">The externid whose paintbuffer should be released.</param>
 * <result>ERR_OK, ERR_PARAMETER or ERR_FAILED if the buffer is already released.</result>
 */
RTS_RESULT CDECL VishReleasePaintBuffer(ExternID extID);
typedef RTS_RESULT (CDECL * PFVISHRELEASEPAINTBUFFER) (ExternID extID);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHRELEASEPAINTBUFFER_NOTIMPLEMENTED)
	#define USE_VishReleasePaintBuffer
	#define EXT_VishReleasePaintBuffer
	#define GET_VishReleasePaintBuffer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VishReleasePaintBuffer(p0) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_VishReleasePaintBuffer  FALSE
	#define EXP_VishReleasePaintBuffer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VishReleasePaintBuffer
	#define EXT_VishReleasePaintBuffer
	#define GET_VishReleasePaintBuffer(fl)  CAL_CMGETAPI( "VishReleasePaintBuffer" ) 
	#define CAL_VishReleasePaintBuffer  VishReleasePaintBuffer
	#define CHK_VishReleasePaintBuffer  TRUE
	#define EXP_VishReleasePaintBuffer  CAL_CMEXPAPI( "VishReleasePaintBuffer" ) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_VishReleasePaintBuffer
	#define EXT_VishReleasePaintBuffer
	#define GET_VishReleasePaintBuffer(fl)  CAL_CMGETAPI( "VishReleasePaintBuffer" ) 
	#define CAL_VishReleasePaintBuffer  VishReleasePaintBuffer
	#define CHK_VishReleasePaintBuffer  TRUE
	#define EXP_VishReleasePaintBuffer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishReleasePaintBuffer", (RTS_UINTPTR)VishReleasePaintBuffer, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlerVishReleasePaintBuffer
	#define EXT_CmpVisuHandlerVishReleasePaintBuffer
	#define GET_CmpVisuHandlerVishReleasePaintBuffer  ERR_OK
	#define CAL_CmpVisuHandlerVishReleasePaintBuffer  VishReleasePaintBuffer
	#define CHK_CmpVisuHandlerVishReleasePaintBuffer  TRUE
	#define EXP_CmpVisuHandlerVishReleasePaintBuffer  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VishReleasePaintBuffer
	#define EXT_VishReleasePaintBuffer
	#define GET_VishReleasePaintBuffer(fl)  CAL_CMGETAPI( "VishReleasePaintBuffer" ) 
	#define CAL_VishReleasePaintBuffer  VishReleasePaintBuffer
	#define CHK_VishReleasePaintBuffer  TRUE
	#define EXP_VishReleasePaintBuffer  CAL_CMEXPAPI( "VishReleasePaintBuffer" ) 
#else /* DYNAMIC_LINK */
	#define USE_VishReleasePaintBuffer  PFVISHRELEASEPAINTBUFFER pfVishReleasePaintBuffer;
	#define EXT_VishReleasePaintBuffer  extern PFVISHRELEASEPAINTBUFFER pfVishReleasePaintBuffer;
	#define GET_VishReleasePaintBuffer(fl)  s_pfCMGetAPI2( "VishReleasePaintBuffer", (RTS_VOID_FCTPTR *)&pfVishReleasePaintBuffer, (fl), 0, 0)
	#define CAL_VishReleasePaintBuffer  pfVishReleasePaintBuffer
	#define CHK_VishReleasePaintBuffer  (pfVishReleasePaintBuffer != NULL)
	#define EXP_VishReleasePaintBuffer   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishReleasePaintBuffer", (RTS_UINTPTR)VishReleasePaintBuffer, 0, 0) 
#endif


/**
 * <description> Function to return if Combination of IecID and ExternID is registered within the 
 * runtime system </description>
 * <result>0 if the combination of ids is not registered, nonzero if it is registered </result>
 */
long CDECL VishIsValidClientID(ExternID extId, IecID id);
typedef long (CDECL * PFVISHISVALIDCLIENTID) (ExternID extId, IecID id);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHISVALIDCLIENTID_NOTIMPLEMENTED)
	#define USE_VishIsValidClientID
	#define EXT_VishIsValidClientID
	#define GET_VishIsValidClientID(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VishIsValidClientID(p0,p1) (long)ERR_NOTIMPLEMENTED
	#define CHK_VishIsValidClientID  FALSE
	#define EXP_VishIsValidClientID  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VishIsValidClientID
	#define EXT_VishIsValidClientID
	#define GET_VishIsValidClientID(fl)  CAL_CMGETAPI( "VishIsValidClientID" ) 
	#define CAL_VishIsValidClientID  VishIsValidClientID
	#define CHK_VishIsValidClientID  TRUE
	#define EXP_VishIsValidClientID  CAL_CMEXPAPI( "VishIsValidClientID" ) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_VishIsValidClientID
	#define EXT_VishIsValidClientID
	#define GET_VishIsValidClientID(fl)  CAL_CMGETAPI( "VishIsValidClientID" ) 
	#define CAL_VishIsValidClientID  VishIsValidClientID
	#define CHK_VishIsValidClientID  TRUE
	#define EXP_VishIsValidClientID  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishIsValidClientID", (RTS_UINTPTR)VishIsValidClientID, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlerVishIsValidClientID
	#define EXT_CmpVisuHandlerVishIsValidClientID
	#define GET_CmpVisuHandlerVishIsValidClientID  ERR_OK
	#define CAL_CmpVisuHandlerVishIsValidClientID  VishIsValidClientID
	#define CHK_CmpVisuHandlerVishIsValidClientID  TRUE
	#define EXP_CmpVisuHandlerVishIsValidClientID  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VishIsValidClientID
	#define EXT_VishIsValidClientID
	#define GET_VishIsValidClientID(fl)  CAL_CMGETAPI( "VishIsValidClientID" ) 
	#define CAL_VishIsValidClientID  VishIsValidClientID
	#define CHK_VishIsValidClientID  TRUE
	#define EXP_VishIsValidClientID  CAL_CMEXPAPI( "VishIsValidClientID" ) 
#else /* DYNAMIC_LINK */
	#define USE_VishIsValidClientID  PFVISHISVALIDCLIENTID pfVishIsValidClientID;
	#define EXT_VishIsValidClientID  extern PFVISHISVALIDCLIENTID pfVishIsValidClientID;
	#define GET_VishIsValidClientID(fl)  s_pfCMGetAPI2( "VishIsValidClientID", (RTS_VOID_FCTPTR *)&pfVishIsValidClientID, (fl), 0, 0)
	#define CAL_VishIsValidClientID  pfVishIsValidClientID
	#define CHK_VishIsValidClientID  (pfVishIsValidClientID != NULL)
	#define EXP_VishIsValidClientID   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishIsValidClientID", (RTS_UINTPTR)VishIsValidClientID, 0, 0) 
#endif


/**
 * <description> Function initializes a Event </description>
 * <result>The paintbuffer that contains the current data for painting</result>
 */
void CDECL VishInitEventStruct(EventStruct* pEvent);
typedef void (CDECL * PFVISHINITEVENTSTRUCT) (EventStruct* pEvent);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHINITEVENTSTRUCT_NOTIMPLEMENTED)
	#define USE_VishInitEventStruct
	#define EXT_VishInitEventStruct
	#define GET_VishInitEventStruct(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VishInitEventStruct(p0) 
	#define CHK_VishInitEventStruct  FALSE
	#define EXP_VishInitEventStruct  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VishInitEventStruct
	#define EXT_VishInitEventStruct
	#define GET_VishInitEventStruct(fl)  CAL_CMGETAPI( "VishInitEventStruct" ) 
	#define CAL_VishInitEventStruct  VishInitEventStruct
	#define CHK_VishInitEventStruct  TRUE
	#define EXP_VishInitEventStruct  CAL_CMEXPAPI( "VishInitEventStruct" ) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_VishInitEventStruct
	#define EXT_VishInitEventStruct
	#define GET_VishInitEventStruct(fl)  CAL_CMGETAPI( "VishInitEventStruct" ) 
	#define CAL_VishInitEventStruct  VishInitEventStruct
	#define CHK_VishInitEventStruct  TRUE
	#define EXP_VishInitEventStruct  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishInitEventStruct", (RTS_UINTPTR)VishInitEventStruct, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlerVishInitEventStruct
	#define EXT_CmpVisuHandlerVishInitEventStruct
	#define GET_CmpVisuHandlerVishInitEventStruct  ERR_OK
	#define CAL_CmpVisuHandlerVishInitEventStruct  VishInitEventStruct
	#define CHK_CmpVisuHandlerVishInitEventStruct  TRUE
	#define EXP_CmpVisuHandlerVishInitEventStruct  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VishInitEventStruct
	#define EXT_VishInitEventStruct
	#define GET_VishInitEventStruct(fl)  CAL_CMGETAPI( "VishInitEventStruct" ) 
	#define CAL_VishInitEventStruct  VishInitEventStruct
	#define CHK_VishInitEventStruct  TRUE
	#define EXP_VishInitEventStruct  CAL_CMEXPAPI( "VishInitEventStruct" ) 
#else /* DYNAMIC_LINK */
	#define USE_VishInitEventStruct  PFVISHINITEVENTSTRUCT pfVishInitEventStruct;
	#define EXT_VishInitEventStruct  extern PFVISHINITEVENTSTRUCT pfVishInitEventStruct;
	#define GET_VishInitEventStruct(fl)  s_pfCMGetAPI2( "VishInitEventStruct", (RTS_VOID_FCTPTR *)&pfVishInitEventStruct, (fl), 0, 0)
	#define CAL_VishInitEventStruct  pfVishInitEventStruct
	#define CHK_VishInitEventStruct  (pfVishInitEventStruct != NULL)
	#define EXP_VishInitEventStruct   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishInitEventStruct", (RTS_UINTPTR)VishInitEventStruct, 0, 0) 
#endif


/**
 * <description> Function to deliver a visual client request. This call will only post an event to the queue
 *	</description>
 * <param name="pszAppName">The application name</param>
 * <param name="dwFlags">The flags</param>
 * <result>A Errorvalue if the call was successful. ERR_OK, if everything is ok. </result>
 */
int CDECL VishPostClientRequest(char* pszAppName, RTS_IEC_DWORD dwFlags);
typedef int (CDECL * PFVISHPOSTCLIENTREQUEST) (char* pszAppName, RTS_IEC_DWORD dwFlags);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHPOSTCLIENTREQUEST_NOTIMPLEMENTED)
	#define USE_VishPostClientRequest
	#define EXT_VishPostClientRequest
	#define GET_VishPostClientRequest(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VishPostClientRequest(p0,p1) (int)ERR_NOTIMPLEMENTED
	#define CHK_VishPostClientRequest  FALSE
	#define EXP_VishPostClientRequest  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VishPostClientRequest
	#define EXT_VishPostClientRequest
	#define GET_VishPostClientRequest(fl)  CAL_CMGETAPI( "VishPostClientRequest" ) 
	#define CAL_VishPostClientRequest  VishPostClientRequest
	#define CHK_VishPostClientRequest  TRUE
	#define EXP_VishPostClientRequest  CAL_CMEXPAPI( "VishPostClientRequest" ) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_VishPostClientRequest
	#define EXT_VishPostClientRequest
	#define GET_VishPostClientRequest(fl)  CAL_CMGETAPI( "VishPostClientRequest" ) 
	#define CAL_VishPostClientRequest  VishPostClientRequest
	#define CHK_VishPostClientRequest  TRUE
	#define EXP_VishPostClientRequest  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishPostClientRequest", (RTS_UINTPTR)VishPostClientRequest, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlerVishPostClientRequest
	#define EXT_CmpVisuHandlerVishPostClientRequest
	#define GET_CmpVisuHandlerVishPostClientRequest  ERR_OK
	#define CAL_CmpVisuHandlerVishPostClientRequest  VishPostClientRequest
	#define CHK_CmpVisuHandlerVishPostClientRequest  TRUE
	#define EXP_CmpVisuHandlerVishPostClientRequest  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VishPostClientRequest
	#define EXT_VishPostClientRequest
	#define GET_VishPostClientRequest(fl)  CAL_CMGETAPI( "VishPostClientRequest" ) 
	#define CAL_VishPostClientRequest  VishPostClientRequest
	#define CHK_VishPostClientRequest  TRUE
	#define EXP_VishPostClientRequest  CAL_CMEXPAPI( "VishPostClientRequest" ) 
#else /* DYNAMIC_LINK */
	#define USE_VishPostClientRequest  PFVISHPOSTCLIENTREQUEST pfVishPostClientRequest;
	#define EXT_VishPostClientRequest  extern PFVISHPOSTCLIENTREQUEST pfVishPostClientRequest;
	#define GET_VishPostClientRequest(fl)  s_pfCMGetAPI2( "VishPostClientRequest", (RTS_VOID_FCTPTR *)&pfVishPostClientRequest, (fl), 0, 0)
	#define CAL_VishPostClientRequest  pfVishPostClientRequest
	#define CHK_VishPostClientRequest  (pfVishPostClientRequest != NULL)
	#define EXP_VishPostClientRequest   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishPostClientRequest", (RTS_UINTPTR)VishPostClientRequest, 0, 0) 
#endif


/**
 * <description> Function to set up a new paint buffer based on shared memory. Is only used in case
 * of the 2-process target visualization.</description>
 * <param name="extID">The externid whose paintbuffer should be set up.</param>
 * <param name="pszShmName">The name of the shared memory, that is used for the paint buffer</param>
 * <result>ERR_OK in case of success, ERR_NOT_SUPPORTED in case of the 1-process target visualization.
 * Other error codes in case of failure</result>
 */
RTS_RESULT CDECL VishSetupPaintBuffer(ExternID extID, char* pszShmName);
typedef RTS_RESULT (CDECL * PFVISHSETUPPAINTBUFFER) (ExternID extID, char* pszShmName);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHSETUPPAINTBUFFER_NOTIMPLEMENTED)
	#define USE_VishSetupPaintBuffer
	#define EXT_VishSetupPaintBuffer
	#define GET_VishSetupPaintBuffer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VishSetupPaintBuffer(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_VishSetupPaintBuffer  FALSE
	#define EXP_VishSetupPaintBuffer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VishSetupPaintBuffer
	#define EXT_VishSetupPaintBuffer
	#define GET_VishSetupPaintBuffer(fl)  CAL_CMGETAPI( "VishSetupPaintBuffer" ) 
	#define CAL_VishSetupPaintBuffer  VishSetupPaintBuffer
	#define CHK_VishSetupPaintBuffer  TRUE
	#define EXP_VishSetupPaintBuffer  CAL_CMEXPAPI( "VishSetupPaintBuffer" ) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_VishSetupPaintBuffer
	#define EXT_VishSetupPaintBuffer
	#define GET_VishSetupPaintBuffer(fl)  CAL_CMGETAPI( "VishSetupPaintBuffer" ) 
	#define CAL_VishSetupPaintBuffer  VishSetupPaintBuffer
	#define CHK_VishSetupPaintBuffer  TRUE
	#define EXP_VishSetupPaintBuffer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishSetupPaintBuffer", (RTS_UINTPTR)VishSetupPaintBuffer, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlerVishSetupPaintBuffer
	#define EXT_CmpVisuHandlerVishSetupPaintBuffer
	#define GET_CmpVisuHandlerVishSetupPaintBuffer  ERR_OK
	#define CAL_CmpVisuHandlerVishSetupPaintBuffer  VishSetupPaintBuffer
	#define CHK_CmpVisuHandlerVishSetupPaintBuffer  TRUE
	#define EXP_CmpVisuHandlerVishSetupPaintBuffer  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VishSetupPaintBuffer
	#define EXT_VishSetupPaintBuffer
	#define GET_VishSetupPaintBuffer(fl)  CAL_CMGETAPI( "VishSetupPaintBuffer" ) 
	#define CAL_VishSetupPaintBuffer  VishSetupPaintBuffer
	#define CHK_VishSetupPaintBuffer  TRUE
	#define EXP_VishSetupPaintBuffer  CAL_CMEXPAPI( "VishSetupPaintBuffer" ) 
#else /* DYNAMIC_LINK */
	#define USE_VishSetupPaintBuffer  PFVISHSETUPPAINTBUFFER pfVishSetupPaintBuffer;
	#define EXT_VishSetupPaintBuffer  extern PFVISHSETUPPAINTBUFFER pfVishSetupPaintBuffer;
	#define GET_VishSetupPaintBuffer(fl)  s_pfCMGetAPI2( "VishSetupPaintBuffer", (RTS_VOID_FCTPTR *)&pfVishSetupPaintBuffer, (fl), 0, 0)
	#define CAL_VishSetupPaintBuffer  pfVishSetupPaintBuffer
	#define CHK_VishSetupPaintBuffer  (pfVishSetupPaintBuffer != NULL)
	#define EXP_VishSetupPaintBuffer   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishSetupPaintBuffer", (RTS_UINTPTR)VishSetupPaintBuffer, 0, 0) 
#endif


/**
 * <description>Function to obtain the maximum size of data, that can be read from a file,
 * when transferring data from the visualization to the plc by streaming.</description>
 * <result>The maximum size</result>
 */
RTS_UI32 CDECL VishGetFileStreamingChunkSize();
typedef RTS_UI32 (CDECL * PFVISHGETFILESTREAMINGCHUNKSIZE) ();
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHGETFILESTREAMINGCHUNKSIZE_NOTIMPLEMENTED)
	#define USE_VishGetFileStreamingChunkSize
	#define EXT_VishGetFileStreamingChunkSize
	#define GET_VishGetFileStreamingChunkSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VishGetFileStreamingChunkSize() (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_VishGetFileStreamingChunkSize  FALSE
	#define EXP_VishGetFileStreamingChunkSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VishGetFileStreamingChunkSize
	#define EXT_VishGetFileStreamingChunkSize
	#define GET_VishGetFileStreamingChunkSize(fl)  CAL_CMGETAPI( "VishGetFileStreamingChunkSize" ) 
	#define CAL_VishGetFileStreamingChunkSize  VishGetFileStreamingChunkSize
	#define CHK_VishGetFileStreamingChunkSize  TRUE
	#define EXP_VishGetFileStreamingChunkSize  CAL_CMEXPAPI( "VishGetFileStreamingChunkSize" ) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_VishGetFileStreamingChunkSize
	#define EXT_VishGetFileStreamingChunkSize
	#define GET_VishGetFileStreamingChunkSize(fl)  CAL_CMGETAPI( "VishGetFileStreamingChunkSize" ) 
	#define CAL_VishGetFileStreamingChunkSize  VishGetFileStreamingChunkSize
	#define CHK_VishGetFileStreamingChunkSize  TRUE
	#define EXP_VishGetFileStreamingChunkSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishGetFileStreamingChunkSize", (RTS_UINTPTR)VishGetFileStreamingChunkSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlerVishGetFileStreamingChunkSize
	#define EXT_CmpVisuHandlerVishGetFileStreamingChunkSize
	#define GET_CmpVisuHandlerVishGetFileStreamingChunkSize  ERR_OK
	#define CAL_CmpVisuHandlerVishGetFileStreamingChunkSize  VishGetFileStreamingChunkSize
	#define CHK_CmpVisuHandlerVishGetFileStreamingChunkSize  TRUE
	#define EXP_CmpVisuHandlerVishGetFileStreamingChunkSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VishGetFileStreamingChunkSize
	#define EXT_VishGetFileStreamingChunkSize
	#define GET_VishGetFileStreamingChunkSize(fl)  CAL_CMGETAPI( "VishGetFileStreamingChunkSize" ) 
	#define CAL_VishGetFileStreamingChunkSize  VishGetFileStreamingChunkSize
	#define CHK_VishGetFileStreamingChunkSize  TRUE
	#define EXP_VishGetFileStreamingChunkSize  CAL_CMEXPAPI( "VishGetFileStreamingChunkSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_VishGetFileStreamingChunkSize  PFVISHGETFILESTREAMINGCHUNKSIZE pfVishGetFileStreamingChunkSize;
	#define EXT_VishGetFileStreamingChunkSize  extern PFVISHGETFILESTREAMINGCHUNKSIZE pfVishGetFileStreamingChunkSize;
	#define GET_VishGetFileStreamingChunkSize(fl)  s_pfCMGetAPI2( "VishGetFileStreamingChunkSize", (RTS_VOID_FCTPTR *)&pfVishGetFileStreamingChunkSize, (fl), 0, 0)
	#define CAL_VishGetFileStreamingChunkSize  pfVishGetFileStreamingChunkSize
	#define CHK_VishGetFileStreamingChunkSize  (pfVishGetFileStreamingChunkSize != NULL)
	#define EXP_VishGetFileStreamingChunkSize   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishGetFileStreamingChunkSize", (RTS_UINTPTR)VishGetFileStreamingChunkSize, 0, 0) 
#endif


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
RTS_RESULT CDECL VishInitiateFileTransfer(const VishFileTransferConfiguration* configuration);
typedef RTS_RESULT (CDECL * PFVISHINITIATEFILETRANSFER) (const VishFileTransferConfiguration* configuration);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHINITIATEFILETRANSFER_NOTIMPLEMENTED)
	#define USE_VishInitiateFileTransfer
	#define EXT_VishInitiateFileTransfer
	#define GET_VishInitiateFileTransfer(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VishInitiateFileTransfer(p0) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_VishInitiateFileTransfer  FALSE
	#define EXP_VishInitiateFileTransfer  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VishInitiateFileTransfer
	#define EXT_VishInitiateFileTransfer
	#define GET_VishInitiateFileTransfer(fl)  CAL_CMGETAPI( "VishInitiateFileTransfer" ) 
	#define CAL_VishInitiateFileTransfer  VishInitiateFileTransfer
	#define CHK_VishInitiateFileTransfer  TRUE
	#define EXP_VishInitiateFileTransfer  CAL_CMEXPAPI( "VishInitiateFileTransfer" ) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_VishInitiateFileTransfer
	#define EXT_VishInitiateFileTransfer
	#define GET_VishInitiateFileTransfer(fl)  CAL_CMGETAPI( "VishInitiateFileTransfer" ) 
	#define CAL_VishInitiateFileTransfer  VishInitiateFileTransfer
	#define CHK_VishInitiateFileTransfer  TRUE
	#define EXP_VishInitiateFileTransfer  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishInitiateFileTransfer", (RTS_UINTPTR)VishInitiateFileTransfer, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlerVishInitiateFileTransfer
	#define EXT_CmpVisuHandlerVishInitiateFileTransfer
	#define GET_CmpVisuHandlerVishInitiateFileTransfer  ERR_OK
	#define CAL_CmpVisuHandlerVishInitiateFileTransfer  VishInitiateFileTransfer
	#define CHK_CmpVisuHandlerVishInitiateFileTransfer  TRUE
	#define EXP_CmpVisuHandlerVishInitiateFileTransfer  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VishInitiateFileTransfer
	#define EXT_VishInitiateFileTransfer
	#define GET_VishInitiateFileTransfer(fl)  CAL_CMGETAPI( "VishInitiateFileTransfer" ) 
	#define CAL_VishInitiateFileTransfer  VishInitiateFileTransfer
	#define CHK_VishInitiateFileTransfer  TRUE
	#define EXP_VishInitiateFileTransfer  CAL_CMEXPAPI( "VishInitiateFileTransfer" ) 
#else /* DYNAMIC_LINK */
	#define USE_VishInitiateFileTransfer  PFVISHINITIATEFILETRANSFER pfVishInitiateFileTransfer;
	#define EXT_VishInitiateFileTransfer  extern PFVISHINITIATEFILETRANSFER pfVishInitiateFileTransfer;
	#define GET_VishInitiateFileTransfer(fl)  s_pfCMGetAPI2( "VishInitiateFileTransfer", (RTS_VOID_FCTPTR *)&pfVishInitiateFileTransfer, (fl), 0, 0)
	#define CAL_VishInitiateFileTransfer  pfVishInitiateFileTransfer
	#define CHK_VishInitiateFileTransfer  (pfVishInitiateFileTransfer != NULL)
	#define EXP_VishInitiateFileTransfer   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishInitiateFileTransfer", (RTS_UINTPTR)VishInitiateFileTransfer, 0, 0) 
#endif


/**
 * <description> Function which is used by a file transfer between a visu client and the plc to ask for the file info.</description>
 * <param name="pszFileName">The file name for which the file info is needed.</param>
 * <param name="pfi">The file info which is the result.</param>
 * <result>Error code.</result>
 */
RTS_RESULT CDECL VishFileTransferGetFileInfo(const char* pszFileName, FileInfo* pfi);
typedef RTS_RESULT (CDECL * PFVISHFILETRANSFERGETFILEINFO) (const char* pszFileName, FileInfo* pfi);
#if defined(CMPVISUHANDLER_NOTIMPLEMENTED) || defined(VISHFILETRANSFERGETFILEINFO_NOTIMPLEMENTED)
	#define USE_VishFileTransferGetFileInfo
	#define EXT_VishFileTransferGetFileInfo
	#define GET_VishFileTransferGetFileInfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VishFileTransferGetFileInfo(p0,p1) (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_VishFileTransferGetFileInfo  FALSE
	#define EXP_VishFileTransferGetFileInfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VishFileTransferGetFileInfo
	#define EXT_VishFileTransferGetFileInfo
	#define GET_VishFileTransferGetFileInfo(fl)  CAL_CMGETAPI( "VishFileTransferGetFileInfo" ) 
	#define CAL_VishFileTransferGetFileInfo  VishFileTransferGetFileInfo
	#define CHK_VishFileTransferGetFileInfo  TRUE
	#define EXP_VishFileTransferGetFileInfo  CAL_CMEXPAPI( "VishFileTransferGetFileInfo" ) 
#elif defined(MIXED_LINK) && !defined(CMPVISUHANDLER_EXTERNAL)
	#define USE_VishFileTransferGetFileInfo
	#define EXT_VishFileTransferGetFileInfo
	#define GET_VishFileTransferGetFileInfo(fl)  CAL_CMGETAPI( "VishFileTransferGetFileInfo" ) 
	#define CAL_VishFileTransferGetFileInfo  VishFileTransferGetFileInfo
	#define CHK_VishFileTransferGetFileInfo  TRUE
	#define EXP_VishFileTransferGetFileInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishFileTransferGetFileInfo", (RTS_UINTPTR)VishFileTransferGetFileInfo, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpVisuHandlerVishFileTransferGetFileInfo
	#define EXT_CmpVisuHandlerVishFileTransferGetFileInfo
	#define GET_CmpVisuHandlerVishFileTransferGetFileInfo  ERR_OK
	#define CAL_CmpVisuHandlerVishFileTransferGetFileInfo  VishFileTransferGetFileInfo
	#define CHK_CmpVisuHandlerVishFileTransferGetFileInfo  TRUE
	#define EXP_CmpVisuHandlerVishFileTransferGetFileInfo  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VishFileTransferGetFileInfo
	#define EXT_VishFileTransferGetFileInfo
	#define GET_VishFileTransferGetFileInfo(fl)  CAL_CMGETAPI( "VishFileTransferGetFileInfo" ) 
	#define CAL_VishFileTransferGetFileInfo  VishFileTransferGetFileInfo
	#define CHK_VishFileTransferGetFileInfo  TRUE
	#define EXP_VishFileTransferGetFileInfo  CAL_CMEXPAPI( "VishFileTransferGetFileInfo" ) 
#else /* DYNAMIC_LINK */
	#define USE_VishFileTransferGetFileInfo  PFVISHFILETRANSFERGETFILEINFO pfVishFileTransferGetFileInfo;
	#define EXT_VishFileTransferGetFileInfo  extern PFVISHFILETRANSFERGETFILEINFO pfVishFileTransferGetFileInfo;
	#define GET_VishFileTransferGetFileInfo(fl)  s_pfCMGetAPI2( "VishFileTransferGetFileInfo", (RTS_VOID_FCTPTR *)&pfVishFileTransferGetFileInfo, (fl), 0, 0)
	#define CAL_VishFileTransferGetFileInfo  pfVishFileTransferGetFileInfo
	#define CHK_VishFileTransferGetFileInfo  (pfVishFileTransferGetFileInfo != NULL)
	#define EXP_VishFileTransferGetFileInfo   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VishFileTransferGetFileInfo", (RTS_UINTPTR)VishFileTransferGetFileInfo, 0, 0) 
#endif


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


typedef struct
{
	IBase_C *pBase;
} ICmpVisuHandler_C;

#ifdef CPLUSPLUS
class ICmpVisuHandler : public IBase
{
	public:
};
	#ifndef ITF_CmpVisuHandler
		#define ITF_CmpVisuHandler static ICmpVisuHandler *pICmpVisuHandler = NULL;
	#endif
	#define EXTITF_CmpVisuHandler
#else	/*CPLUSPLUS*/
	typedef ICmpVisuHandler_C		ICmpVisuHandler;
	#ifndef ITF_CmpVisuHandler
		#define ITF_CmpVisuHandler
	#endif
	#define EXTITF_CmpVisuHandler
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPVISUHANDLERITF_H_*/
