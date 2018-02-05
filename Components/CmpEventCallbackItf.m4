/**
 * <interfacename>CmpEventCallback</interfacename>
 * <description> 
 *	This interface specifies the callback interface for event callbacks.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpEventCallback')

#include "CmpItf.h"

typedef	RTS_UI32	EVENTID;
typedef	RTS_UI16	EVENTCLASSID;

/**
 * <category>Base event parameter</category>
 * <element name="EventId" type="IN">EventID of the event. Contains the class and the event</element>
 * <element name="usParamId" type="IN">Id of the parameter structure (see pParameter)</element>
 * <element name="usVersion" type="IN">Version of the parameter structure (see pParameter)</element>
 * <element name="pParameter" type="IN">Pointer to the event specific parameter, that is specified by Id (see usParamId)</element>
 * <element name="pUserParameter" type="IN">Pointer to the user specific parameter, that can be specified by registering the callback</element>
 */
typedef struct
{
	EVENTID EventId;
	CMPID CmpIdProvider;
	RTS_UI16 usParamId;
	RTS_UI16 usVersion;
	void* pParameter;
	void* pUserParameter;
} EventParam;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description> Callback function </description>
 * <param name="pEventParam" type="IN">Pointer to the event parameter.</param>
 * <result></result>
 */
typedef void (CDECL *PFEVENTCALLBACKFUNCTION)(EventParam *pEventParam);

/**
 * <description> Callback interface </description>
 * <param name="hInstance" type="IN">Handle to callback instance.</param>
 * <param name="pEventParam" type="IN">Pointer to the event parameter.</param>
 * <result></result>
 */
DEF_CLASSITF_API(`void', `CDECL', `EventCallback', `(RTS_HANDLE hInstance, EventParam *pEventParam)')

#ifdef __cplusplus
}
#endif

