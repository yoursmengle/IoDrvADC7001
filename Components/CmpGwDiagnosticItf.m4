/**
 * <interfacename>CmpGwDiagnostic</interfacename>
 * <description> 
 *   This interface provides diagnostic access to the gateway. It allows other
 *   components to register as a listener. After that they will be informed about
 *   activities in the gateway like addition of new channels, closing of channels,
 *   connected clients, etc. 
 *   It also allows the client to query the state of several objects. The state of
 *   a channel for example includes the number of open requests or the current quality
 *   (error rate, round-trip-time).
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpGwDiagnostic')

REF_ITF(`CmpCommunicationLibItf.m4')

#ifdef __cplusplus
extern "C" {
#endif

/* 
 * Object types
 */
enum
{
	GWDOT_COMMDRV,					/* A communication driver (client-gateway communication) */
	GWDOT_CLIENT,
	GWDOT_CHANNEL,
	GWDOT_VIRTUALCHANNEL,
	GWDOT_VIRTUALCHANNELREF
};

/* This struct is used to pass name/value pairs in different contexts */
typedef struct 
{
	RTS_WCHAR *wszName;
	RTS_WCHAR *wszValue;
}GWDPROPERTY;

typedef struct
{
	RTS_SIZE nSize;					/* Size of the structure */
	RTS_HANDLE hObjectId;			/* The object id is unique only within one object type (ie. different object types may use the same id)! */
}GWDOBJECTINFO;

typedef struct
{
	GWDOBJECTINFO objInfo;
	RTS_WCHAR *wszName;

	RTS_SIZE nNumSettings;			/* Number of valid entries in the driverSettings array */
	GWDPROPERTY *driverSettings;	/* An array of properties of the driver - eg. port(TCP) or BaudRate(RS232) etc.*/
}GWDCOMMDRVINFO;

typedef struct
{
	GWDOBJECTINFO objInfo;

	RTS_HANDLE hDriverId;			/* Id of the commdriver used */
	RTS_WCHAR *wszAddress;			/* Address of the client. The content depends highly on the commdriver */
	RTS_WCHAR *wszUserName;			/* Name of the authenticated user */

	/* TODO: Connected since (timestamp) */
}GWDCLIENTINFO;

typedef struct
{
	GWDOBJECTINFO objInfo;

	NODEADDRESSREF addrDevice;		/* Address of the remote device */
	RTS_UI32 ulCommBufferSize; 
}GWDCHANNELINFO;

/* Information about a virtual channel passed as pInfo in a call to the ObjectAdded function. */
typedef struct
{
	GWDOBJECTINFO objInfo;

	RTS_UI32 ulChannelId;			/* The channel used by this virtual channel */
	RTS_WCHAR *wszChannelName;
}GWDVIRTUALCHANNELINFO;

/* Information about a reference to a virtual channel.
   This struct is passed as pInfo in a call to the ObjectAdded function. 
*/
typedef struct
{
	GWDOBJECTINFO objInfo;
	
	RTS_HANDLE hVirtualChannelId;
	RTS_HANDLE hClientId;
}GWDVIRTUALCHANNELREFINFO;

/**
 * <description>
 *   This structure describes the current state of a channel. The information provided
 *   describes a snapshot of the channel state and is likely to change when retrieved next.
 *   This structure is intended for future extension; new members may be appended to the end.
 *   Any component using this structure or an extension of it must be prepared to also handle 
 *   this base structure.
 * </description>
 */
typedef struct
{
	RTS_SIZE nStructSize;			/* Size of this struct. Allows for future extension of this struct */

	RTS_INT nOpenRequests;			/* Number of requests currently waiting to be handled for this channel */

	RTS_UI32 ulBlocksSent;			/* Number of blocks sent to the remote node. Retransmitted blocks are counted twice. */
	RTS_UI32 ulBlocksFailed;		/* Number of blocks that had to be retransmitted */

	RTS_UI32 ulRoundTripTime;		/* Average time from the sending of a block until the answer is received (microseconds)*/
}GWDCHANNELSTATE;

/** 
 * <description>
 *   Is called every time an object is added in the gateway. 
 * </description>
 * <param name="hListenerId" type="IN">The id returned by the GWDRegisterListener</param>
 * <param name="nObjType" type="IN">
 *   The type of the object which is added. One of the GWDOT_xxx constants.
 *   Since new object types may be added in the future, implementations should
 *   handle unknown objects types gracefully.
 * </param>
 * <param name="pInfo" type="IN">
 *   Additional information about the added object. Depending on the object type
 *   an extension of the GWOBJECTINFO struct will be passed.
 * </param>
 */
typedef void (CDECL *PFOBJECTADDED)(RTS_HANDLE hListenerId, RTS_INT nObjType, GWDOBJECTINFO *pInfo);

/** 
 * <description>
 *   Called by the gateway when an object is removed. 
 * </description>
 * <param name="hListenerId" type="IN">The id returned by the GWDRegisterListener</param>
 * <param name="nObjType" type="IN">
 *   Same as in PFOBJECTADDED. hObjectId is not unique across different object types!
 * </param>
 * <param name="hObjectId" type="IN">
 *   Refers to the object id passed in the ObjectAdded routines pInfo parameter.
 * </param>
 */
typedef void (CDECL *PFOBJECTREMOVED)(RTS_HANDLE hListenerId, RTS_INT nObjType, RTS_HANDLE hObjectId);

typedef struct
{
	RTS_SIZE nStructSize; /* Allows for future extension of this structure */

	PFOBJECTADDED pfObjectAdded;
	PFOBJECTREMOVED pfObjectRemoved;
}GWDLISTENERCALLBACKS;
 
/**
 * <description>
 *   Register a listener for the gateway diagnostics interface. The listener will be informed about
 *   activities within the gateway using the provided callbacks.
 *   When calling this function, the listener is expected to be in an initial state. 
 *   Therefore the pfObjectAdded function will be called for each object that exists in the gateway
 *   in order to synchronize the listener with the gateway.
 * </description>
 * <param name="callbacks" type="IN">callback functions of the listener</param>
 * <param name="phListenerId" type="OUT">
 *   Will be set to a unique number that identifies the listener. Use this value in a call to 
 *   unsubscribe.
 * </param>
 */
DEF_API(`RTS_RESULT',`CDECL',`GWDRegisterListener',`(GWDLISTENERCALLBACKS callbacks, RTS_HANDLE *phListenerId)')

/**
 * <description>
 *   Stop informing the specified listener about activities in the gateway.
 * </description>
 * <param name="hListenerId" type="IN">The id returned by the GWDRegisterListener</param>
 */
DEF_API(`RTS_RESULT',`CDECL',`GWDUnregisterListener',`(RTS_HANDLE hListenerId)')

/**
 * <description>
 *   Fills the pState structure with the current state of a channel. 
 * </description>  
 * <param name="ulChannelId" type="IN">id of the channel as provided in the addObject callback</param>
 * <param name="pState" type="OUT">
 *   Will be filled with the current channel state. Must not be NULL and the nStructSize member of the
 *   struct must be set to thesize of the structure provided. 
 *   On success this member will be set to the size of the structure actually used, which is less or equal
 *   to the provided size. If a component passes in an extension of GWDCHANNELSTATE it must be prepared
 *   that the gateway only fills the basic structure.

 */
DEF_API(`RTS_RESULT',`CDECL',`GWDGetChannelState',`(RTS_UI32 ulChannelId, GWDCHANNELSTATE *pState)')

#ifdef __cplusplus
}
#endif
