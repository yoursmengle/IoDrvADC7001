/**
 * <interfacename>CmpXMLParser</interfacename>
 * <description> 
 *	Interface of the XML-Parser.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpXMLParser')

#include "CmpStd.h"

/* Hook definitions (0..10000 reserved for core components) */

typedef RTS_CWCHAR XML_Char;
typedef RTS_CWCHAR XML_LChar;

/**
 * <category>XML flags</category>
 * <description>
 *	Flags for the XML events
 * </description>
 *	<element name="RTS_XML_EVENTFLAG_ASCII" type="IN">ASCII strings</element>
 *	<element name="RTS_XML_EVENTFLAG_UNICODE" type="IN">Unicode strings</element>
 */
#define RTS_XML_EVENTFLAG_ASCII			0x00000001
#define RTS_XML_EVENTFLAG_UNICODE		0x00000002


/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <category>Event parameter</category>
 * <element name="hXML" type="IN">Handle to XML parser</element>
 * <element name="ulFlags" type="IN">Flags. See corresponding category</element>
 * <element name="pUserData" type="IN">Pointer to user data</element>
 * <element name="pcwName" type="IN">Pointer to tag name</element>
 */
typedef struct tagEVTPARAM_CmpXMLEnd
{
	RTS_IEC_HANDLE hXMLParser;		
	RTS_IEC_UDINT ulFlags;		
	RTS_IEC_BYTE *pUserData;		
	RTS_IEC_CWCHAR *pcwName;		
} EVTPARAM_CmpXMLEnd;

/**
 * <category>Event parameter</category>
 * <element name="hXML" type="IN">Handle to XML parser</element>
 * <element name="ulFlags" type="IN">Flags. See corresponding category</element>
 * <element name="pUserData" type="IN">Pointer to user data</element>
 * <element name="pcwName" type="IN">Pointer to tag name</element>
 * <element name="ppcwAttributes" type="IN">Pointer to list of attributes (NULL terminated list)</element>
 */
typedef struct tagEVTPARAM_CmpXMLData
{
	RTS_IEC_HANDLE hXMLParser;		
	RTS_IEC_UDINT ulFlags;		
	RTS_IEC_BYTE *pUserData;		
	RTS_IEC_CWCHAR *pcwValue;		
	RTS_IEC_DINT nValueLen;		
} EVTPARAM_CmpXMLData;

/**
 * <category>Event parameter</category>
 * <element name="hXML" type="IN">Handle to XML parser</element>
 * <element name="ulFlags" type="IN">Flags. See corresponding category</element>
 * <element name="pUserData" type="IN">Pointer to user data</element>
 * <element name="pcwName" type="IN">Pointer to tag name</element>
 */
typedef struct tagEVTPARAM_CmpXMLStart
{
	RTS_IEC_HANDLE hXMLParser;		
	RTS_IEC_UDINT ulFlags;		
	RTS_IEC_BYTE *pUserData;		
	RTS_IEC_CWCHAR *pcwName;		
	RTS_IEC_CWCHAR **ppcwAttributes;		
} EVTPARAM_CmpXMLStart;

/**
 * <description>createxmlparser2</description>
 */
typedef struct tagcreatexmlparser2_struct
{
	RTS_IEC_STRING szXMLFileName[81];	/* VAR_INPUT */	
	RTS_IEC_STRING szEncoding[81];		/* VAR_INPUT */	
	RTS_IEC_RESULT *Result;				/* VAR_IN_OUT */	
	RTS_IEC_HANDLE CreateXMLParser2;	/* VAR_OUTPUT */	
} createxmlparser2_struct;

DEF_API(`void',`CDECL',`createxmlparser2',`(createxmlparser2_struct *p)',1,0xAC05CC34,0x03050500)

/**
 * <description>freexmlparser</description>
 */
typedef struct tagfreexmlparser_struct
{
	RTS_IEC_HANDLE hParser;				/* VAR_INPUT */	
	RTS_IEC_RESULT FreeXMLParser;		/* VAR_OUTPUT */	
} freexmlparser_struct;

DEF_API(`void',`CDECL',`freexmlparser',`(freexmlparser_struct *p)',1,0xF9BB08C3,0x03050500)

/**
 * <description>parsexml2</description>
 */
typedef struct tagparsexml2_struct
{
	RTS_IEC_HANDLE hParser;				/* VAR_INPUT */	
	RTS_IEC_BOOL bIsFinal;				/* VAR_INPUT */	
	RTS_IEC_RESULT ParseXML2;			/* VAR_OUTPUT */	
} parsexml2_struct;

DEF_API(`void',`CDECL',`parsexml2',`(parsexml2_struct *p)',1,0xC0F3799A,0x03050500)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#define EVTPARAMID_CmpXMLStart			0x0001
#define EVTVERSION_CmpXMLStart			0x0001

#define EVTPARAMID_CmpXMLData			0x0002
#define EVTVERSION_CmpXMLData			0x0001

#define EVTPARAMID_CmpXMLEnd			0x0003
#define EVTVERSION_CmpXMLEnd			0x0001


/**
 * <category>Events</category>
 * <description>Event is sent, if a new XML tag is detected</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpXMLStart</param>
 */
#define EVT_XMLStart					MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Events</category>
 * <description>Event is sent, if the content value of a XML tag is detected</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpXMLData</param>
 */
#define EVT_XMLData						MAKE_EVENTID(EVTCLASS_INFO, 2)

/**
 * <category>Events</category>
 * <description>Event is sent, if the end of a XML tag is detected</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpXMLEnd</param>
 */
#define EVT_XMLEnd						MAKE_EVENTID(EVTCLASS_INFO, 3)


/**
 * <category>Encoding</category>
 * <description>Encoding to parse XML file</description>
 */
#define RTS_XML_ENCODING_UTF8			"UTF-8"
#define RTS_XML_ENCODING_UTF16			"UTF-16"


#ifdef __cplusplus
extern "C" {
#endif

/* atts is array of name/value pairs, terminated by 0;
   names and values are 0 terminated. */
typedef void (*PF_XML_StartElementHandler)(void *userData, XML_Char *name, XML_Char **atts);

typedef void (*PF_XML_EndElementHandler)(void *userData, XML_Char *name);

/* s is not 0 terminated. */
typedef void (*PF_XML_CharacterDataHandler)(void *userData, XML_Char *s, int len);

/**
 * <description> Creates a XML parser </description>
 * <param name="pcwEncoding" type="IN">Optional encoding. See category "Encoding".</param>
 * <result>Handle to XML parser instance</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `CreateXMLParser', `(const XML_Char *pcwEncoding)')

/**
 * <description> Creates a XML parser </description>
 * <param name="pszXMLFileName" type="IN">Name of the XML file</param>
 * <param name="pcwEncoding" type="IN">Optional encoding. See category "Encoding".</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to XML parser instance</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `CreateXMLParser2', `(char *pszXMLFileName, const XML_Char *pcwEncoding, RTS_RESULT *pResult)')

/**
 * <description> Frees the XML parser </description>
 * <param name="hParser" type="IN">Handle of the XML parser instance</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `FreeXMLParser', `(RTS_HANDLE hParser)')

/**
 * <description> Sets the XML element handler </description>
 * <param name="hParser" type="IN">Handle of the XML parser instance</param>
 * <param name="start" type="IN">Callback function for the StartElementHandler. If this is not set, the events above are sent instead!</param>
 * <param name="end" type="IN">Callback function for the EndElementHandler. If this is not set, the events above are sent instead!</param>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SetXMLElementHandler', `(RTS_HANDLE hParser, PF_XML_StartElementHandler start, PF_XML_EndElementHandler end)')

/**
 * <description> Sets the XML data handler </description>
 * <param name="hParser" type="IN">Handle of the XML parser instance</param>
 * <param name="handler" type="IN">Callback function for the CharacterDataHandler. If this is not set, the events above are sent instead!</param>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SetXMLCharacterDataHandler', `(RTS_HANDLE hParser, PF_XML_CharacterDataHandler handler)')

/**
 * <description> Starts the parsing process </description>
 * <param name="hParser" type="IN">Handle of the XML parser instance</param>
 * <param name="s" type="IN">Pointer to buffer that contains the XML file</param>
 * <param name="len" type="IN">Length of the XML file</param>
 * <param name="isFinal" type="IN"></param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `ParseXML', `(RTS_HANDLE hParser, const char *s, RTS_SIZE len, RTS_BOOL isFinal)')

/**
 * <description> Starts the parsing process </description>
 * <param name="hParser" type="IN">Handle of the XML parser instance</param>
 * <param name="isFinal" type="IN"></param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `ParseXML2', `(RTS_HANDLE hParser, RTS_BOOL isFinal)')

#ifdef __cplusplus
}
#endif
