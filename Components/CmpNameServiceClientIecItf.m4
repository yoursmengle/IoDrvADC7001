/**
 * <interfacename>CmpNameServiceClientIec</interfacename>
 * <description> 
 *	Iec interface to the naming service client.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpNameServiceClientIec')

#include "CmpNameService.h"

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Constants</description>
 */
#define MAXNODEADDRLENGTH		0xF	

/**
 * <description>NSC_AddrComponent</description>
 */
typedef struct tagNSC_AddrComponent
{
	RTS_IEC_BYTE Component[2];		
} NSC_AddrComponent;

/**
 * <description>NSC_NodeAddress</description>
 */
typedef struct tagNSC_NodeAddress
{
	RTS_IEC_UDINT nAddrComponentCount;		
	NSC_AddrComponent AddrComponents[MAXNODEADDRLENGTH - 1 + 1];		
} NSC_NodeAddress;

/**
 * This is the structure as it is passed from the callback function
 */
typedef struct tagNSC_NodeInfoExt
{
	RTS_IEC_UINT uiMaxChannels;		
	RTS_IEC_BOOL bIntelByteOrder;		
	RTS_IEC_USINT byDummy;		
	RTS_IEC_UINT uiParentAddrSize;		
	RTS_IEC_UINT uiNodeNameLength;		
	RTS_IEC_UINT uiDeviceNameLength;		
	RTS_IEC_UINT uiVendorNameLength;		
	RTS_IEC_UDINT udiTargetType;		
	RTS_IEC_UDINT udiTargetId;		
	RTS_IEC_UDINT udiTargetVersion;		
	RTS_IEC_BYTE *pDynamicLengthData;		/* The dynamic fields are (in this order):
   - addrParent (wParentAddrSize NSC_AddrComponent components) followed by
   - node name (zero terminated wide-char string) followed by
   - device name (zero terminated wide-char string) followed by
   - type description (zero terminated wide-char string)
   If wParentAddrSize is zero (i.e. node has no parent) then the node name
   starts immediatly at position offsetof(addrParent).
 */
} NSC_NodeInfoExt;

/**
 * Close an instance of the nameservice client. Callbacks that arrive after the client has been closed will no longer be forwarded.
 * Returns the result of the operation, ERR_OK if a valid instance has been given in.
 */
typedef struct tagnsclientclose_struct
{
	RTS_IEC_HANDLE hNSClient;			/* VAR_INPUT */	/* Handle of the nameservice client that is to be closed */
	RTS_IEC_RESULT NSClientClose;		/* VAR_OUTPUT */	
} nsclientclose_struct;

DEF_API(`void',`CDECL',`nsclientclose',`(nsclientclose_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x739FD2C5),0x03050500)

/**
 * Opens an instance of the nameservice client. Returns the handle to the created name service client.
 */
typedef struct tagnsclientopen_struct
{
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Will optionally receive an error code if the creation of a nameservice client has failed. Otherwise ERR_OK will be returned. */
	RTS_IEC_HANDLE NSClientOpen;		/* VAR_OUTPUT */	
} nsclientopen_struct;

DEF_API(`void',`CDECL',`nsclientopen',`(nsclientopen_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD17DF797),0x03050500)

/**
 * Initiates the resolving of all available runtimes. Returns the result of the operation.
 */
typedef struct tagnsclientresolveall_struct
{
	RTS_IEC_HANDLE hNSClient;			/* VAR_INPUT */	/* The instance of a nameservice client that shall to do the nameresolving */
	RTS_IEC_UXINT udiReqId;				/* VAR_INPUT */	/* Identifies the request. */
	RTS_IEC_BYTE *pfnResponseCallback;	/* VAR_INPUT */	/* Prototype see NSClientResponseCallback. This callback will be triggered for each available node */
	RTS_IEC_RESULT NSClientResolveAll;	/* VAR_OUTPUT */	
} nsclientresolveall_struct;

DEF_API(`void',`CDECL',`nsclientresolveall',`(nsclientresolveall_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF500D28F),0x03050500)

/**
 * This is only a prototype for the function that will be called when a node has been found.
 * Only used to export the callback interface for generating the m4 runtime system files.
 * There is no implementation behind that....
 * Must not be called!!!
 */
typedef struct tagnsclientresponsecallback_struct
{
	RTS_IEC_RESULT udiResult;			/* VAR_INPUT */	
	NSC_NodeAddress addrNode;			/* VAR_INPUT */	
	NSC_NodeInfoExt *pNodeInfo;			/* VAR_INPUT */	
	RTS_IEC_WORD wVersion;				/* VAR_INPUT */	
	RTS_IEC_UXINT udiReqId;				/* VAR_INPUT */	
	RTS_IEC_BOOL bComplete;				/* VAR_INPUT */	
	RTS_IEC_UDINT NSClientResponseCallback;	/* VAR_OUTPUT */	
} nsclientresponsecallback_struct;


/* DEF_API(`void',`CDECL',`nsclientresponsecallback',`(nsclientresponsecallback_struct *p)',1,0,0x03050500) */
/* Callback interfaces are not yet supported by the CODESYS m4 export, therefore the type is manually defined here. */ 
typedef void (CDECL *PFNSCLIENTRESPONSECALLBACK_IEC) (nsclientresponsecallback_struct *p);


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/
