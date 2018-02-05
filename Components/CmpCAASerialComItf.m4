SET_INTERFACE_NAME(`CmpCAASerialCom')

#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAASerialCom.h"
#include "CAAAsyncMan.h"
#include "CAAMemBlockMan.h"

#ifdef __cplusplus
extern "C" {
#endif

DEF_ITF_API(`CAA_ERROR',`CDECL',`COM_WorkerInit',`(void)')
DEF_ITF_API(`CAA_ERROR',`CDECL',`COM_WorkerExit',`(void)')

#define	COM_SETTINGS_PORT				0x01
#define	COM_SETTINGS_STOPBIT			0x02
#define	COM_SETTINGS_PARITY				0x03
#define	COM_SETTINGS_BAUDRATE			0x04
#define	COM_SETTINGS_TIMEOUT			0x05
#define	COM_SETTINGS_BUFFERSIZE			0x06
#define	COM_SETTINGS_BYTESIZE			0x07
#define	COM_SETTINGS_BINARY				0x08
#define	COM_SETTINGS_OUTXCTSFLOW		0x09
#define	COM_SETTINGS_OUTXDSRFLOW		0x0A
#define	COM_SETTINGS_DTRCONTROL			0x0B
#define	COM_SETTINGS_DSRSENSITIVITY		0x0C
#define	COM_SETTINGS_RTSCONTROL			0x0D
#define	COM_SETTINGS_TXCONTINUEONXOFF	0x0E
#define	COM_SETTINGS_OUTX				0x0F
#define	COM_SETTINGS_INX				0x10
#define	COM_SETTINGS_XONCHAR			0x11
#define	COM_SETTINGS_XOFFCHAR			0x12
#define	COM_SETTINGS_XONLIM				0x13
#define	COM_SETTINGS_XOFFLIM			0x14

#ifdef __cplusplus
}
#endif


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Closes the serial port synchonously. Only to be called by SerialClass.Close in FB_Exit. 
 */
typedef struct tagcom_close_struct
{
	CAA_HANDLE hCom;					/* VAR_INPUT */	
	CAA_ERROR COM_Close;				/* VAR_OUTPUT */	
} com_close_struct;

DEF_API(`void',`CDECL',`com_close',`(com_close_struct *p)',1,RTSITF_GET_SIGNATURE(0x14BED712, 0xE3A6D576),0x03050600)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/
