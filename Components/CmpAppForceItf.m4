/**
 * <interfacename>CmpAppForce</interfacename>
 * <description> 
 *	This is the interface of the IEC application manager to handle forcing variables.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpAppForce')

REF_ITF(`CmpAppItf.m4')
REF_ITF(`CmpSrvItf.m4')

#ifdef CMPAPP_NOTIMPLEMENTED
	#ifndef CMPAPPFORCE_NOTIMPLEMENTED
		#define CMPAPPFORCE_NOTIMPLEMENTED
	#endif
#endif

/**
 * <category>Compiler switch</category>
 * <description>
 *	Compiler switches to enable/disable single features in the component.
 * </description>
 * <element name="APPFORCE_DISABLE_PERSISTENT_FORCE">Switch to disable persistent force</element>
 */


/**
 * <category>Static defines</category>
 * <description>Length of force list that is allocated static in the application object</description>
 */
#ifndef APPL_STATIC_FORCE_ENTRIES
	#define APPL_STATIC_FORCE_ENTRIES		10
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Settings to enable persistent force</description>
 */
#define APPKEY_INT_PERSISTENT_FORCE					"PersistentForce"
#ifndef APPVALUE_INT_PERSISTENT_FORCE_DEFAULT
	#define APPVALUE_INT_PERSISTENT_FORCE_DEFAULT	0
#endif
#ifdef APPFORCE_DISABLE_PERSISTENT_FORCE
	#undef APPVALUE_INT_PERSISTENT_FORCE_DEFAULT
	#define APPVALUE_INT_PERSISTENT_FORCE_DEFAULT	0
#endif

#define RTS_FORCEFLAGS_SAFEDOLDVALUE			1
#define RTS_FORCEFLAGS_RESTORE					2

typedef struct tagForceVarDesc
{
	RTS_I32 nRefCount;
	RTS_UI32 ulFlags;
	VarDataRef DataRef;
	VarValue Value;
	VarValue OldValue;
} ForceVarDesc;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Init force list on the specified application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppForceInit', `(APPLICATION *pApp)')

/**
 * <description>Exit force list on the specified application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <element name="bShutdown" type="IN">1=Runtime exits the application and so the force during shutdown, 0=else</element>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppForceExit', `(APPLICATION *pApp, int bShutdown)')

/**
 * <description>Add a new force value, that is forced in every task of the application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="pDataRef" type="IN">Pointer to decription of the force variable</param>
 * <param name="pValue" type="IN">Pointer to value of the force variable that will be hold</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppAddForceValue', `(APPLICATION* pApp, VarDataRef *pDataRef, VarValue *pValue)')

/**
 * <description>Remove a single force value</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="pDataRef" type="IN">Pointer to decription of the force variable</param>
 * <param name="bRestoreValue" type="IN">1=Restore old value before force. 0=Actual force value will not be modified</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppReleaseForceValue', `(APPLICATION* pApp, VarDataRef *pDataRef, int bRestoreValue)')

/**
 * <description>Get first force entry</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to force value</result>
 */
DEF_ITF_API(`ForceVarDesc *', `CDECL', `AppGetFirstForce', `(APPLICATION *pApp, RTS_RESULT *pResult)')

/**
 * <description>Get next force entry</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <param name="pPrevForce" type="IN">Pointer to previous force entry</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Pointer to force value</result>
 */
DEF_ITF_API(`ForceVarDesc *', `CDECL', `AppGetNextForce', `(APPLICATION *pApp, ForceVarDesc *pPrevForce, RTS_RESULT *pResult)')

/**
 * <description>Release all force values of the specified application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <element name="bShutdown" type="IN">1=Runtime exits the application and so the force during shutdown, 0=else</element>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppReleaseAllForceValues', `(APPLICATION* pApp, int bShutdown)')

/**
 * <description>Load persistent force list, if available</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppLoadPersistentForce', `(APPLICATION* pApp)')

/**
 * <description>Create persistent force list. This is used to force values right after a reboot
 *	of the controller</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppCreatePersistentForce', `(APPLICATION* pApp)')

/**
 * <description>Delete persistent force list of the specified application</description>
 * <param name="pApp" type="IN">Pointer to the specified application description</param>
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppDeletePersistentForce', `(APPLICATION* pApp)')

/**
 * <description>Handler for all force services</description>
 * <param name="ulChannelId" type="IN">ChannelID of the communication channel</param>
 * <param name="pHeaderTag" type="IN">Pointer to the service header</param>
 * <param name="pduData" type="IN">Data unit of the received service</param>
 * <param name="pduSendBuffer" type="IN">Data unit for the service reply</param>
 * <result>Error code:
 *		ERR_OK: Service could be executed successfully.
 *		ERR_NOT_SUPPORTED: Service is not supported
 *		ERR_FAILED: Error during executing service
 * </result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `AppForceServiceHandler2', `(RTS_UI32 ulChannelId, HEADER_TAG *pHeaderTag, PROTOCOL_DATA_UNIT pduData, PROTOCOL_DATA_UNIT *pduSendBuffer)')

#ifdef __cplusplus
}
#endif

