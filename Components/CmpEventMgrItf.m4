/**
 * <interfacename>CmpEventMgr</interfacename>
 * <description> 
 *	<p>This is the interface of the event manager. The manager is responsible to handle all events in the
 *	runtime system and to call special registered functions (callbacks) if an event occurred. An event can be 
 *	sent in any situation, when a state will be changed in the runtime system. An event can be e.g. stop of 
 *	an Iec application, download of an Iec application, exception occurred in a component, etc.</p>
 *
 *	<p>Typically an event will be sent before a state changed (xxxPrepare) and if the state has changed (xxxDone)</p>
 *
 *	<p>The component that provides and sends an event is called the provider. The component that receives the event
 *	is called the consumer of an event.</p>
 *
 *	<p>Each component can define its own event ID. Such an event ID consists of two numbers:
 *	<ul>
 *		<li>Event class:	16 bit number that specifies the class of the event</li>
 *		<li>Event:			16 bit number that specifies the event</li>
 *	</ul>
 *	The event class and the event is matched to one 32 bit number that is called the event ID. The event, 
 *	event class and the component ID of the provider makes an event unique. So every provider has
 *	to specify at least these three things to sent an event.</p>
 *
 *	<p>Each provider can specify additional parameters for each event that is transferred to the consumer. This is
 *	event specific and can be specified by the consumer. Such an optional event parameter must be specified by a
 *	component specific parameter ID and with a parameter version number. With this information, a consumer can 
 *	check, which parameter in which version the provider is sending.</p>
 *	
 *	<p>To use an event, first of all the provider has to register the event. After that, the consumer can open this 
 *	event and can attach its callback routine to this event. Such a callback routine can be:</p>
 *	<ul>
 *		<li>C-Function</li>
 *		<li>Iec-Function</li>
 *		<li>Iec-Method of a function block</li>
 *		<li>C++-Method of a C++ class</li>
 *	</ul>
 *
 *	<p>IMPLEMENTATION NOTE: A provider typically registers its event in the CH_INIT2 hook. The consumer typically
 *	registers its callback to special events in the CH_INIT3 hook.</p>
 *	<p>If a provider only wants to register an event if it is really needed by a consumer, the CmpEventMgr sents
 *	a special event, if a consumer tries to open an event (see EVT_EventOpen). In this event, the provider
 *	can register the event and the consumer can open a valid event.</p>
 *	<p>In opposite, if a consumer wants to register a callback on an event, an event is sent if a provider 
 *	registers its event (see EVT_EventCreate).</p>
 *	<p>If an event is unregistred by a provider, the event EVT_EventDelete is sent. If an event is closed by
 *	a consumer, the event EVT_EventClose is sent.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpEventMgr')

#include "CmpItf.h"
REF_ITF(`CmpEventCallbackItf.m4')


/**
 * <category>Static defines</category>
 * <description>Maximum number of static allocated events</description>
 */
#ifndef EVENTMGR_NUM_OF_STATIC_EVENTS
	#define EVENTMGR_NUM_OF_STATIC_EVENTS		50
#endif

/**
 * <category>Static defines</category>
 * <description>Maximum number of static allocated callback routines to be registered</description>
 */
#ifndef EVENTMGR_NUM_OF_STATIC_CALLBACKS
	#define EVENTMGR_NUM_OF_STATIC_CALLBACKS	10
#endif

/**
 * <category>Static defines</category>
 * <description>Maximum number of static allocated iec callback routines to be registered</description>
 */
#ifndef EVENTMGR_NUM_OF_STATIC_IECCALLBACKS
	#define EVENTMGR_NUM_OF_STATIC_IECCALLBACKS	5
#endif

/**
 * <category>Convert macro</category>
 * <description>Macro to create an event ID with the event class and the event</description>
 */
#define MAKE_EVENTID(Class, Event)				(Class | Event)

/**
 * <category>Provider component ids</category>
 * <description>Special priovider ids</description>
 */
#define EVTPROVIDER_NONE					0
#define EVTPROVIDER_ALL						UINT32_MAX

/**
 * <category>Event classes</category>
 * <description><p>All possible event classes:</p>
 *	<ul>
 *		<li>EVTCLASS_NONE: No class or invalid</li>
 *		<li>EVTCLASS_ALL: All classes</li>
 *		<li>EVTCLASS_INFO: Information</li>
 *		<li>EVTCLASS_WARNING: Warning</li>
 *		<li>EVTCLASS_ERROR: Error</li>
 *		<li>EVTCLASS_EXCEPTION: Exception</li>
 *		<li>EVTCLASS_VENDOR_SPEC: Vendor specific. Can be used for own event classes</li>
 *	</ul>
 * </description>
 */
#define EVTCLASS_NONE						0	
#define EVTCLASS_ALL						UINT32_C(0xFFFF0000)
#define EVTCLASS_INFO						UINT32_C(0x00010000)
#define EVTCLASS_WARNING					UINT32_C(0x00020000)
#define EVTCLASS_ERROR						UINT32_C(0x00040000)
#define EVTCLASS_EXCEPTION					UINT32_C(0x00080000)
#define EVTCLASS_VENDOR_SPEC				UINT32_C(0x10000000)


/**
 * <category>Special Events</category>
 * <description>
 *	<ul>
 *		<li>EVT_NONE: No event or invalid</li>
 *		<li>EVT_ALL: All events</li>
 *	</ul>
 * </description>
 */
#define EVT_NONE							0
#define EVT_ALL								0xFFFF


/**
 * <category>Callback limit</category>
 * <description>No limit of callbacks possible per event</description>
 */
#define EVENT_CALLBACKS_NO_LIMIT			UINT32_MAX

/**
 * <category>Event manager flags</category>
 * <description>
 *	Flags used by the event manager.
 * </description>
 *	<element name="EMF_NO_IEC_CALLBACKS" type="IN">No callbacks in IEC possible</element>
 */
#define EMF_NO_IEC_CALLBACKS	UINT32_C(0x00000001)

/**
 * <category>Event options</category>
 * <element name="nCallbacksPossible" type="IN">Maximum number of callbacks possible on this event or EVENT_CALLBACKS_NO_LIMIT for no limit</element>
 * <element name="flags" type="IN">Event manager flags</element>
 */
typedef struct tagEventOptions
{
       RTS_UI32 nCallbacksPossible;
       RTS_UI32 flags;
} EventOptions;

/**
 * <category>Event parameter</category>
 * <element name="EventId" type="IN">EventID of the event. Contains the class and the event</element>
 * <element name="CmpIdProvider" type="IN">Component ID of the provider</element>
 */
typedef struct
{
	EVENTID EventId;
	CMPID CmpIdProvider;
} EVTPARAM_CmpEventMgr;
#define EVTPARAMID_CmpEventMgr		0x0001
#define EVTVERSION_CmpEventMgr		0x0001

/**
 * <category>Events</category>
 * <description>Event is sent after a provider creates a new event</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpEventMgr</param>
 */
#define EVT_EventCreate						MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Events</category>
 * <description>Event is sent before a provider deletes an event</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpEventMgr</param>
 */
#define EVT_EventDelete						MAKE_EVENTID(EVTCLASS_INFO, 2)

/**
 * <category>Events</category>
 * <description>Event is sent before a consumer tries to open an event</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpEventMgr</param>
 */
#define EVT_EventOpen						MAKE_EVENTID(EVTCLASS_INFO, 3)

/**
 * <category>Events</category>
 * <description>Event is sent before a consumer closes an event</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpEventMgr</param>
 */
#define EVT_EventClose						MAKE_EVENTID(EVTCLASS_INFO, 4)

/**
 * <category>Events</category>
 * <description>Event is sent in every call of the CH_COMM_CYCLE. Can be used for IEC background jobs.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_CmpEventMgr</param>
 */
#define EVT_EventCommCycle					MAKE_EVENTID(EVTCLASS_INFO, 5)

#define EventParam2		EventParam

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	void* __VFTABLEPOINTER;	/* Pointer to virtual function table */
} icmpeventcallback_struct;

/**
 * The interface ICmpEventCallback must be registered for an event. If this event is posted, this callback method is called.
 */
typedef struct tagicmpeventcallback_eventcallback_struct
{
	icmpeventcallback_struct *pInstance;	/* VAR_INPUT */	
	EventParam *pEventParam;			/* VAR_INPUT */	/* Pointer to the event parameters, see Struct EventParam */
	RTS_IEC_RESULT EventCallback;		/* VAR_OUTPUT */	
} icmpeventcallback_eventcallback_struct;

/**
 * Close an event specified by handle 
 */
typedef struct tageventclose_struct
{
	RTS_IEC_HANDLE hEvent;				/* VAR_INPUT */	/* Event handle */
	RTS_IEC_RESULT EventClose;			/* VAR_OUTPUT */	/* Error code */
} eventclose_struct;

DEF_API(`void',`CDECL',`eventclose',`(eventclose_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4668EEC1),0x03050C00)

/**
 * Creates a new event object. If event still exists, a handle to this object will be returned.
 *   An IEC event is typically created by the provider in FB_Init of a function block 
 */
typedef struct tageventcreate_struct
{
	RTS_IEC_UDINT EventId;				/* VAR_INPUT */	/* Event ID of the event. Contains the class and the event */
	RTS_IEC_UDINT CmpIdProvider;		/* VAR_INPUT */	/* Component ID of the provider */
	RTS_IEC_RESULT *Result;				/* VAR_IN_OUT */	/* Error code */
	RTS_IEC_HANDLE EventCreate;			/* VAR_OUTPUT */	/* Handle to created event */
} eventcreate_struct;

DEF_API(`void',`CDECL',`eventcreate',`(eventcreate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xAC9E014A),0x03050C00)

/**
 * Creates a new event object. If event still exists, a handle to this object will be returned.
 *   An IEC event is typically created by the provider in FB_Init of a function block 
 */
typedef struct tageventcreate2_struct
{
	RTS_IEC_UDINT EventId;				/* VAR_INPUT */	/* Event ID of the event. Contains the class and the event */
	RTS_IEC_UDINT CmpIdProvider;		/* VAR_INPUT */	/* Component ID of the provider */
	RTS_IEC_UDINT nCallbacksPossible;	/* VAR_INPUT */	/* Maximum number of callbacks possible on this event or EVENT_CALLBACKS_NO_LIMIT for no limit */
	RTS_IEC_RESULT *Result;				/* VAR_IN_OUT */	/* Error code */
	RTS_IEC_HANDLE EventCreate2;		/* VAR_OUTPUT */	/* Handle to created event */
} eventcreate2_struct;

DEF_API(`void',`CDECL',`eventcreate2',`(eventcreate2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD6BF4CE8),0x03050C00)

/**
 * Deletes an event specified by handle. 
 */
typedef struct tageventdelete_struct
{
	RTS_IEC_HANDLE hEvent;				/* VAR_INPUT */	/* Event handle */
	RTS_IEC_RESULT EventDelete;			/* VAR_OUTPUT */	/* Error code */
} eventdelete_struct;

DEF_API(`void',`CDECL',`eventdelete',`(eventdelete_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0794C5F5),0x03050C00)

/**
 * Extract the event class from eventid. Return value is the event class 
 */
typedef struct tageventgetclass_struct
{
	RTS_IEC_UDINT EventId;				/* VAR_INPUT */	/* Event id */
	RTS_IEC_UINT EventGetClass;			/* VAR_OUTPUT */	
} eventgetclass_struct;

DEF_API(`void',`CDECL',`eventgetclass',`(eventgetclass_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB0745754),0x03050C00)

/**
 * Extract the event from eventid. Return value ist the event 
 */
typedef struct tageventgetevent_struct
{
	RTS_IEC_UDINT EventId;				/* VAR_INPUT */	/* Event ID */
	RTS_IEC_UINT EventGetEvent;			/* VAR_OUTPUT */	
} eventgetevent_struct;

DEF_API(`void',`CDECL',`eventgetevent',`(eventgetevent_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0E7E3D61),0x03050C00)

/**
 * Opens an existing event object. Can be used to check, if the event was created by the provider.
 *   If the event does not exist, an error code is returned. 
 */
typedef struct tageventopen_struct
{
	RTS_IEC_UDINT EventId;				/* VAR_INPUT */	/* EventID of the event. Contains the class and the event */
	RTS_IEC_UDINT CmpIdProvider;		/* VAR_INPUT */	/* Component ID of the provider */
	RTS_IEC_RESULT *Result;				/* VAR_IN_OUT */	/* Error code */
	RTS_IEC_HANDLE EventOpen;			/* VAR_OUTPUT */	/* Handle to opened event */
} eventopen_struct;

DEF_API(`void',`CDECL',`eventopen',`(eventopen_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xBC5AE4E1),0x03050C00)

/**
 * Post or sent an event 
 */
typedef struct tageventpost_struct
{
	RTS_IEC_HANDLE hEvent;				/* VAR_INPUT */	/* Event handle */
	EventParam *pEventParam;			/* VAR_INPUT */	/* Pointer to the event parameters */
	RTS_IEC_RESULT EventPost;			/* VAR_OUTPUT */	/* Error code */
} eventpost_struct;

DEF_API(`void',`CDECL',`eventpost',`(eventpost_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x9FDEA762),0x03050C00)

/**
 * Post or sent an event 
 */
typedef struct tageventpost2_struct
{
	RTS_IEC_HANDLE hEvent;				/* VAR_INPUT */	/* Event handle */
	EventParam2 *pEventParam;			/* VAR_INPUT */	/* Pointer to the event parameters */
	RTS_IEC_RESULT EventPost2;			/* VAR_OUTPUT */	/* Error code */
} eventpost2_struct;

DEF_API(`void',`CDECL',`eventpost2',`(eventpost2_struct *p)',1,0xCE90F5F0,0x03050C00)

/**
 * Post an event direct without the event handle 
 */
typedef struct tageventpostbyevent_struct
{
	RTS_IEC_UDINT EventId;				/* VAR_INPUT */	/* Event ID of the event. Contains the class and the event */
	RTS_IEC_UDINT CmpIdProvider;		/* VAR_INPUT */	/* Component ID of the provider */
	EventParam *pEventParam;			/* VAR_INPUT */	/* Pointer to the event parameters */
	RTS_IEC_RESULT EventPostByEvent;	/* VAR_OUTPUT */	/* Error code */
} eventpostbyevent_struct;

DEF_API(`void',`CDECL',`eventpostbyevent',`(eventpostbyevent_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA33BD23D),0x03050C00)

/**
 * Post an event direct without the event handle 
 */
typedef struct tageventpostbyevent2_struct
{
	RTS_IEC_UDINT EventId;				/* VAR_INPUT */	/* Event ID of the event. Contains the class and the event */
	RTS_IEC_UDINT CmpIdProvider;		/* VAR_INPUT */	/* Component ID of the provider */
	EventParam2 *pEventParam;			/* VAR_INPUT */	/* Pointer to the event parameters */
	RTS_IEC_RESULT EventPostByEvent2;	/* VAR_OUTPUT */	/* Error code */
} eventpostbyevent2_struct;

DEF_API(`void',`CDECL',`eventpostbyevent2',`(eventpostbyevent2_struct *p)',1,0x61F1EA28,0x03050C00)

/**
 * Register an callback method to an event. The callback must be an interface from an Iec function block! 
 */
typedef struct tageventregistercallback_struct
{
	RTS_IEC_HANDLE hEvent;				/* VAR_INPUT */	/* Handle to event */
	ICmpEventCallback *pICallback;		/* VAR_INPUT */	/* Interface ICmpEventCallback */
	RTS_IEC_RESULT *Result;				/* VAR_IN_OUT */	/* Error code */
	RTS_IEC_HANDLE EventRegisterCallback;	/* VAR_OUTPUT */	/* Handle to the callback that must be used to unregister with EventUnregisterCallback! */
} eventregistercallback_struct;

DEF_API(`void',`CDECL',`eventregistercallback',`(eventregistercallback_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x5EF9AC91),0x03050C00)

/**
 * Register an callback method to an event. The callback must be an interface from an Iec function block! 
 */
typedef struct tageventregistercallback2_struct
{
	RTS_IEC_HANDLE hEvent;				/* VAR_INPUT */	/* Handle to event */
	ICmpEventCallback *pICallback;		/* VAR_INPUT */	/* Interface ICmpEventCallback */
	RTS_IEC_BYTE *pUserParameter;		/* VAR_INPUT */	/* Pointer to user parameter, that is transmitted to the callback (see EventParam) */
	RTS_IEC_RESULT *Result;				/* VAR_IN_OUT */	/* Error code */
	RTS_IEC_HANDLE EventRegisterCallback2;	/* VAR_OUTPUT */	/* Handle to the callback that must be used to unregister with EventUnregisterCallback! */
} eventregistercallback2_struct;

DEF_API(`void',`CDECL',`eventregistercallback2',`(eventregistercallback2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x95D8F44C),0x03050C00)

/**
 * Register a callback function to an event. Callback is the address of an Iec function: ADR(function) 
 */
typedef struct tageventregistercallbackfunction_struct
{
	RTS_IEC_HANDLE hEvent;				/* VAR_INPUT */	/* Handle to event */
	RTS_IEC_BYTE *pfCallbackFunction;	/* VAR_INPUT */	/* Address of callback function. Prototype: same as ICmpEventCallback::EventCallback method
															  Function pointer is retrieved by the ADR operator: ADR(function) */
	RTS_IEC_RESULT EventRegisterCallbackFunction;	/* VAR_OUTPUT */	/* Error code */
} eventregistercallbackfunction_struct;

DEF_API(`void',`CDECL',`eventregistercallbackfunction',`(eventregistercallbackfunction_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x989C8BB3),0x03050C00)

/**
 * Register a callback function to an event. Callback is the address of an Iec function: ADR(function) 
 */
typedef struct tageventregistercallbackfunction2_struct
{
	RTS_IEC_HANDLE hEvent;				/* VAR_INPUT */	/* Handle to event */
	RTS_IEC_BYTE *pfCallbackFunction;	/* VAR_INPUT */	/* Address of callback function. Prototype: same as ICmpEventCallback::EventCallback method
															  Function pointer is retrieved by the ADR operator: ADR(function) */
	RTS_IEC_BYTE *pUserParameter;		/* VAR_INPUT */	/* Pointer to user parameter, that is transmitted optional to the callback (see EventParam) */
	RTS_IEC_RESULT EventRegisterCallbackFunction2;	/* VAR_OUTPUT */	/* Error code */
} eventregistercallbackfunction2_struct;

DEF_API(`void',`CDECL',`eventregistercallbackfunction2',`(eventregistercallbackfunction2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xBD946DD7),0x03050C00)

/**
 * Returns the number of registered callbacks on the event 
 */
typedef struct tageventregisteredcallbacks_struct
{
	RTS_IEC_HANDLE hEvent;				/* VAR_INPUT */	/* Event handle */
	RTS_IEC_RESULT *Result;				/* VAR_IN_OUT */	/* Error code */
	RTS_IEC_UDINT EventRegisteredCallbacks;	/* VAR_OUTPUT */	
} eventregisteredcallbacks_struct;

DEF_API(`void',`CDECL',`eventregisteredcallbacks',`(eventregisteredcallbacks_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC4EA0B3B),0x03050C00)

/**
 * Unregister a callback interface from an event specified by handle and callback interface 
 */
typedef struct tageventunregistercallback_struct
{
	RTS_IEC_HANDLE hEvent;				/* VAR_INPUT */	/* Event handle */
	RTS_IEC_HANDLE hInterface;			/* VAR_INPUT */	/* Callback handle is returned by EventRegisterCallback() or EventRegisterCallback2()!!! */
	RTS_IEC_RESULT EventUnregisterCallback;	/* VAR_OUTPUT */	/* Error code */
} eventunregistercallback_struct;

DEF_API(`void',`CDECL',`eventunregistercallback',`(eventunregistercallback_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x80238B4F),0x03050C00)

/**
 * Unregister a callback function from an event specified by handle and callback 
 */
typedef struct tageventunregistercallbackfunction_struct
{
	RTS_IEC_HANDLE hEvent;				/* VAR_INPUT */	/* Handle to event */
	RTS_IEC_BYTE *pfCallbackFunction;	/* VAR_INPUT */	/* Address of callback function. Function pointer is retrieved by the ADR operator: ADR(function) */
	RTS_IEC_RESULT EventUnregisterCallbackFunction;	/* VAR_OUTPUT */	/* Error code */
} eventunregistercallbackfunction_struct;

DEF_API(`void',`CDECL',`eventunregistercallbackfunction',`(eventunregistercallbackfunction_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x5E0DD5BD),0x03050C00)

/**
 * Unregister a callback function with a specific user parameter from an event specified by handle and callback and parameter 
 */
typedef struct tageventunregistercallbackfunction2_struct
{
	RTS_IEC_HANDLE hEvent;				/* VAR_INPUT */	/* Handle to event */
	RTS_IEC_BYTE *pfCallbackFunction;	/* VAR_INPUT */	/* Address of callback function. Function pointer is retrieved by the ADR operator: ADR(function) */
	RTS_IEC_BYTE *pUserParameter;		/* VAR_INPUT */	/* Pointer to user parameter, that is transmitted optional to the callback (see EventParam) */
	RTS_IEC_RESULT EventUnregisterCallbackFunction2;	/* VAR_OUTPUT */	/* Error code */
} eventunregistercallbackfunction2_struct;

DEF_API(`void',`CDECL',`eventunregistercallbackfunction2',`(eventunregistercallbackfunction2_struct *p)',1,0x779853A9,0x03050C00)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Creates a new event object. If event still exists, a handle to this object will be returned.
 * An event is typically created by the provider of an event in the CH_INIT_DONE hook.</description>
 * <param name="EventId" type="IN">Event ID of the event. Contains the class and the event</param>
 * <param name="CmpIdProvider" type="IN">Component ID of the provider</param>
 * <param name="pResult" type="OUT">Pointer to the error code</param>
 * <result>Handle to the event object</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `EventCreate', `(EVENTID EventId, CMPID CmpIdProvider, RTS_RESULT *pResult)')

/**
 * <description>Creates a new event object. If event still exists, a handle to this object will be returned.
 * An event is typically created by the provider of an event in the CH_INIT_DONE hook.</description>
 * <param name="EventId" type="IN">Event ID of the event. Contains the class and the event</param>
 * <param name="CmpIdProvider" type="IN">Component ID of the provider</param>
 * <param name="nCallbacksPossible" type="IN">Maximum number of callbacks possible on this event or EVENT_CALLBACKS_NO_LIMIT for no limit</param>
 * <param name="pResult" type="OUT">Pointer to the error code</param>
 * <result>Handle to the event object</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `EventCreate2', `(EVENTID EventId, CMPID CmpIdProvider, RTS_UI32 nCallbacksPossible, RTS_RESULT *pResult)')

/**
 * <description>Creates a new event object. If event still exists, a handle to this object will be returned.
 * An event is typically created by the provider of an event in the CH_INIT_DONE hook.</description>
 * <param name="EventId" type="IN">Event ID of the event. Contains the class and the event</param>
 * <param name="CmpIdProvider" type="IN">Component ID of the provider</param>
 * <param name="pEventOptions" type="IN">Pointer to the EventOptions. May be NULL, then EventCreate() will be called without EventOptions.</param>
 * <param name="pResult" type="OUT">Pointer to the error code</param>
 * <result>Handle to the event object</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `EventCreate3', `(EVENTID EventId, CMPID CmpIdProvider, EventOptions *pEventOptions, RTS_RESULT *pResult)')

/**
 * <description>Deletes an event specified by handle </description>
 * <param name="hEvent" type="IN">Handle to event</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `EventDelete', `(RTS_HANDLE hEvent)')

/**
 * <description>Delete all registered events and the registered callbacks</description>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `EventDeleteAll', `(void)')

/**
 * <description><p>Opens an existing event object. Can be used to check, if the event was created by the provider.
 * If the event does not exist, an error code is returned.</p>
 * Typically an event is opened by the consumer of an event in the CH_INIT_DONE2 hook.</description>
 * <param name="EventId" type="IN">Event ID of the event. Contains the class and the event</param>
 * <param name="CmpIdProvider" type="IN">Component ID of the provider</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Handle to the event object</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `EventOpen', `(EVENTID EventId, CMPID CmpIdProvider, RTS_RESULT *pResult)')

/**
 * <description>Close an event specified by handle</description>
 * <param name="hEvent" type="IN">Handle to the event</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `EventClose', `(RTS_HANDLE hEvent)')

/**
 * <description>Extract the event from eventid</description>
 * <param name="EventId" type="IN">Event ID</param>
 * <result>Event. Is specified in the interface of each component</result>
 */
DEF_ITF_API(`unsigned short', `CDECL', `EventGetEvent', `(EVENTID EventId)')

/**
 * <description>Extract the event class from eventid</description>
 * <param name="EventId" type="IN">Event ID</param>
 * <result>Event class</result>
 */
DEF_ITF_API(`unsigned short', `CDECL', `EventGetClass', `(EVENTID EventId)')

/**
 * <description>Register an interface callback function to an event. The interface can be from a C object,
 *	a C++ class or a wrapper class for an Iec function block</description>
 * <param name="hEvent" type="IN">Handle to event</param>
 * <param name="pICallback" type="IN">Pointer to callback interface</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `EventRegisterCallback', `(RTS_HANDLE hEvent, ICmpEventCallback *pICallback)')

/**
 * <description>Register an interface callback function to an event. The interface can be from a C object,
 *	a C++ class or a wrapper class for an Iec function block</description>
 * <param name="hEvent" type="IN">Handle to event</param>
 * <param name="pICallback" type="IN">Pointer to callback interface</param>
 * <param name="pUserParameter" type="IN">Pointer to user parameter, that is transmitted to the callback (see EventParam)</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `EventRegisterCallback2', `(RTS_HANDLE hEvent, ICmpEventCallback *pICallback, void *pUserParameter)')

/**
 * <description>Register an interface callback function to an event. The interface can be from a C object,
 *	a C++ class or a wrapper class for an Iec function block</description>
 * <param name="hEvent" type="IN">Handle to event</param>
 * <param name="pICallback" type="IN">Pointer to callback interface</param>
 * <param name="bIec" type="IN">1=Iec interface behind the C interface, 0=C interface</param>
 * <param name="pUserParameter" type="IN">Pointer to user parameter, that is transmitted to the callback (see EventParam)</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `EventRegisterCallback3', `(RTS_HANDLE hEvent, ICmpEventCallback *pICallback, int bIec, void *pUserParameter)')

/**
 * <description>Unregister a callback interface from an event specified by handle and callback interface</description>
 * <param name="hEvent" type="IN">Handle to event</param>
 * <param name="pICallback" type="IN">Pointer to callback interface</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `EventUnregisterCallback', `(RTS_HANDLE hEvent, ICmpEventCallback *pICallback)')

/**
 * <description>Register a callback function to an event. Callback function can be a C or Iec function</description>
 * <param name="hEvent" type="IN">Handle to event</param>
 * <param name="pfCallbackFunction" type="IN">Pointer to callback function</param>
 * <param name="bIec" type="IN">1=Iec function, 0=C function</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `EventRegisterCallbackFunction', `(RTS_HANDLE hEvent, PFEVENTCALLBACKFUNCTION pfCallbackFunction, int bIec)')

/**
 * <description>Register a callback function to an event. Callback function can be a C or Iec function</description>
 * <param name="hEvent" type="IN">Handle to event</param>
 * <param name="pfCallbackFunction" type="IN">Pointer to callback function</param>
 * <param name="bIec" type="IN">1=Iec function, 0=C function</param>
 * <param name="pUserParameter" type="IN">Pointer to user parameter, that is transmitted to the callback (see EventParam)</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `EventRegisterCallbackFunction2', `(RTS_HANDLE hEvent, PFEVENTCALLBACKFUNCTION pfCallbackFunction, int bIec, void *pUserParameter)')

/**
 * <description>Unregister a callback function from an event specified by handle and callback </description>
 * <param name="hEvent" type="IN">Handle to event</param>
 * <param name="pfCallbackFunction" type="IN">Pointer to callback function</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `EventUnregisterCallbackFunction', `(RTS_HANDLE hEvent, PFEVENTCALLBACKFUNCTION pfCallbackFunction)')

/**
 * <description>Unregister a callback function with a specific user parameter from an event specified by handle and callback and parameter</description>
 * <param name="hEvent" type="IN">Handle to event</param>
 * <param name="pfCallbackFunction" type="IN">Pointer to callback function</param>
 * <param name="bIec" type="IN">1=Iec function, 0=C function</param>
 * <param name="pUserParameter" type="IN">Pointer to user parameter, that was specified as a parameter at EventRegisterCallback2()</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `EventUnregisterCallbackFunction2', `(RTS_HANDLE hEvent, PFEVENTCALLBACKFUNCTION pfCallbackFunction, void *pUserParameter)')
 
/**
 * <description>Function to evaluate the number of registered callback handlers on a single event</description>
 * <param name="hEvent" type="IN">Handle to event</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Number of registered callback handlers on this event</result>
 */
DEF_ITF_API(`unsigned long', `CDECL', `EventRegisteredCallbacks', `(RTS_HANDLE hEvent, RTS_RESULT *pResult)')

/**
 * <description>Post or sent an event</description>
 * <param name="hEvent" type="IN">Handle to event</param>
 * <param name="pEventParam" type="IN">Pointer to the event parameters</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `EventPost', `(RTS_HANDLE hEvent, EventParam *pEventParam)')

/**
 * <description>Sent an event and call synchronously all registered callback handler</description>
 * <param name="hEvent" type="IN">Handle to event</param>
 * <param name="usParamId" type="IN">Id of the parameter</param>
 * <param name="usVersion" type="IN">Version of the parameter</param>
 * <param name="pParameter" type="IN">Pointer to the event specific parameter, that is specified by Id</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `EventPost2', `(RTS_HANDLE hEvent, unsigned short usParamId, unsigned short usVersion, void* pParameter)')

/**
 * <description>Post an event direct without opening the event</description>
 * <param name="EventId" type="IN">Event ID of the event. Contains the class and the event</param>
 * <param name="CmpIdProvider" type="IN">Component ID of the provider</param>
 * <param name="pEventParam" type="IN">Pointer to the event parameters</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `EventPostByEvent', `(EVENTID EventId, CMPID CmpIdProvider, EventParam *pEventParam)')

#ifdef __cplusplus
}
#endif

