/**
 * <interfacename>SysCom</interfacename>
 * <description> 
 *	<p>The SysCom interface is projected to connect to a serial COM port (RS232) and 
 *	to send and receive data via this port.</p>
 *	<p>IMPLEMENTATION NODE: All routines must be realized asynchronous! You have to use the FIFO of
 *	the serial device! Don't block the read and write routines, until the operations are finished.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysCom')

#include "CmpStd.h"

#ifndef CDECL
	#define CDECL
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Allows to specify a serial port by its Microsoft Windows friendly name instead of the COM port number.
 * The friendly name of the COM port is for example shown by the Microsoft Windows Device Manager. 
 * This feature is useful, if the port number is somehow dynamic, but if the adapter has a well defined 
 * friendly name. Typically it's used for USB devices, which provide a virtual COM port driver. If the 
 * (by SysComOpen) requested COM port number is found in the list of the configured "Windows.PortToCheck" 
 * settings, then the port is opened, which matches to the name specified by "Windows.CheckWithPortName",
 * instead of the requested port number. 
 * (Only for Windows).
 * Example:
 * Windows.PortToCheck.0=99
 * Windows.CheckWithPortName.0=My USB serial device
 * Windows.PortToCheck.1=98
 * Windows.CheckWithPortName.1=PLC USB interface
 * </description>
 */
#define SYSCOMKEY_INT_WINDOWS_PORT_TO_CHECK						"Windows.PortToCheck"
#define SYSTIMERVALUE_INT_WINDOWS_PORT_TO_CHECK_DEFAULT	        0

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 * Specifies a string, which is compared to the Microsoft Windows friendly name of the available COM ports.
 * The name matches, if it starts with the provided string.  
 * See also setting PortToCheck.
 * (Only for Windows).
 * </description>
 */
#define SYSCOMKEY_STRING_WINDOWS_PORTNAME_CHECK_WITH						"Windows.CheckWithPortname"
#define SYSTIMERVALUE_STRING_WINDOWS_PORTNAME_CHECK_WITH_DEFAULT	        ""

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 * Devicefile for serial interface (Only for Linux).
 * </description>
 */
#define SYSCOMKEY_STRING_LINUX_DEVICEFILE			"Linux.Devicefile"
#define SYSCOMKEY_STRING_LINUX_DEVICEFILE_DEFAULT	"/dev/ttyS"

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 *	Physical layer of the serial interface. Valid values are "rs232" and "rs485".
 * (Only for Linux).
 * </description>
 */
#define SYSCOMKEY_STRING_LINUX_PHYSICAL_LAYER						"Linux.PhysicalLayer"
#define SYSCOMKEY_STRING_LINUX_PHYSICAL_LAYER_DEFAULT	        	"rs232"

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 * on_send: RTS pin is high on send, and low all other times. 
 * after_send: RTS pin is low on send. 
 * (Only for Linux).
 * </description>
 */
#define SYSCOMKEY_STRING_LINUX_RS485_RTS_PIN						"Linux.rs485.RTSPin"
#define SYSCOMKEY_STRING_LINUX_RS485_RTS_PIN_DEFAULT	        	"on_send"

/**
 * <category>Event parameter</category>
 * <element name="device" type="IN">Name of serial device</element>
 */
typedef struct
{
	unsigned char* name;
} EVTPARAM_SysComOpen;
#define EVTPARAMID_SysComOpen 0x0001
#define EVTVERSION_SysComOpen 0x0001

/**
 * <category>Events</category>
 * <description>Platform dependent event. Sent before the physical driver open.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_SysComOpenBefore</param>
 */
#define EVT_SysComOpenBefore MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Events</category>
 * <description>Platform dependent event. Sent directly after the physical driver open.</description>
 * <param name="pEventParam" type="IN">EVTPARAM_SysComOpenAfter</param>
 */
#define EVT_SysComOpenAfter MAKE_EVENTID(EVTCLASS_INFO, 2)


/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <category>Baudrates</category>
 * <description>Supported baudrates</description>
 */
#define SYS_BR_4800    4800	
#define SYS_BR_9600    9600	
#define SYS_BR_19200    19200	
#define SYS_BR_38400    38400	
#define SYS_BR_57600    57600	
#define SYS_BR_115200    115200	
/* Typed enum definition */
#define COM_BAUDRATE    RTS_IEC_DWORD

/**
 * <category>Parity</category>
 * <description>Supported parity</description>
 */
#define SYS_NOPARITY    0	/* <element name="SYS_NOPARITY" TYPE="IN">No parity</element> */
#define SYS_ODDPARITY    1	/* <element name="SYS_ODDPARITY" TYPE="IN">Odd parity</element> */
#define SYS_EVENPARITY    2	/* <element name="SYS_EVENPARITY" TYPE="IN">Even parity</element> */
/* Typed enum definition */
#define COM_PARITY    RTS_IEC_BYTE

/**
 * <category>Com ports</category>
 * <description>Supported com port numbers</description>
 */
#define SYS_COMPORT_NONE    0	
#define SYS_COMPORT1    1	
#define SYS_COMPORT2    2	
#define SYS_COMPORT3    3	
#define SYS_COMPORT4    4	
/* Typed enum definition */
#define COM_PORTS    RTS_IEC_INT

/**
 * <category>Stop bits</category>
 * <description>Supported stop bits</description>
 */
#define SYS_ONESTOPBIT    1	
#define SYS_ONE5STOPBITS    2	
#define SYS_TWOSTOPBITS    3	
/* Typed enum definition */
#define COM_STOPBITS    RTS_IEC_BYTE

/**
 * <category>Timeouts</category>
 * <description>Specified standard timeouts</description>
 */
#define SYS_NOWAIT    0	
#define SYS_INFINITE    0xFFFFFFFF	
/* Typed enum definition */
#define COM_TIMEOUT    RTS_IEC_UDINT

/**
 * <category>Com port extended settings</category>
 * <description>
 *	</description>
 */
typedef struct tagCOM_SettingsEx
{
	RTS_IEC_BYTE byByteSize;		/* <element name="byByteSize" TYPE="IN">Number OF bits/BYTE, 4-8</element> */
	RTS_IEC_BOOL bBinary;		/* <element name="bBinary" TYPE="IN">binary mode, no EOF check</element> */
	RTS_IEC_BOOL bOutxCtsFlow;		/* <element name="bOutxCtsFlow" TYPE="IN">CTS handshaking on output</element> */
	RTS_IEC_BOOL bOutxDsrFlow;		/* <element name="bOutxDsrFlow" TYPE="IN">DSR handshaking on output</element> */
	RTS_IEC_BOOL bDtrControl;		/* <element name="bDtrControl" TYPE="IN">DTR Flow control</element> */
	RTS_IEC_BOOL bDsrSensitivity;		/* <element name="bDsrSensitivity" TYPE="IN">DSR Sensitivity</element> */
	RTS_IEC_BOOL bRtsControl;		/* <element name="bRtsControl" TYPE="IN">Rts Flow control</element> */
	RTS_IEC_BOOL bTXContinueOnXoff;		/* <element name="bTXContinueOnXoff" TYPE="IN">XOFF continues Tx</element> */
	RTS_IEC_BOOL bOutX;		/* <element name="bOutX" TYPE="IN">XON/XOFF out flow control</element> */
	RTS_IEC_BOOL bInX;		/* <element name="bInX" TYPE="IN">XON/XOFF in flow control</element> */
	RTS_IEC_BYTE byXonChar;		/* <element name="XonChar" TYPE="IN">Tx AND Rx XON character</element> */
	RTS_IEC_BYTE byXoffChar;		/* <element name="XoffChar" TYPE="IN">Tx AND Rx XOFF character</element> */
	RTS_IEC_WORD wXonLim;		/* <element name="XonLim" TYPE="IN">transmit XON threshold</element> */
	RTS_IEC_WORD wXoffLim;		/* <element name="XoffLim" TYPE="IN">transmit XOFF threshold</element> */
} COM_SettingsEx;

/**
 * <category>Com port settings</category>
 * <description>Settings to open and to configure a COM interface</description>
 */
typedef struct tagCOM_Settings
{
	RTS_IEC_INT sPort;		/* <element name="sPort" type="IN">Port number: 0=disabled, 1=COM1, 2=COM2, .... See category "Com ports"</element> */
	RTS_IEC_BYTE byStopBits;		/* <element name="byStopBits" type="IN">Stop bits. See category "Stop bits"</element> */
	RTS_IEC_BYTE byParity;		/* <element name="byParity" type="IN">Parity. See category "Parity"</element> */
	RTS_IEC_DWORD ulBaudrate;		/* <element name="ulBaudRate" type="IN">Baudrate. See "category "Baudrates"</element> */
	RTS_IEC_UDINT ulTimeout;		/* <element name="ulTimeout" TYPE="IN">Hardware timeout. The Timeout is the TIME between two received OR sent
	 	characters until the read or write operation will return.
		Typically this value should be 0 (returns immediately)</element> */
	RTS_IEC_UDINT ulBufferSize;		/* <element name="ulBufferSize" type="IN">Buffersize of FIFO buffer</element> */
} COM_Settings;

/**
 * <description>Close a serial communication device.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsyscomclose_struct
{
	RTS_IEC_HANDLE hCom;				/* VAR_INPUT */	/* <param name="hCom" type="IN">Handle to com port to close</param> */
	RTS_IEC_RESULT SysComClose;			/* VAR_OUTPUT */	
} syscomclose_struct;

DEF_API(`void',`CDECL',`syscomclose',`(syscomclose_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xACD27C01),0x03050500)

/**
 * <description>Get the parameter of the interface specified by handle.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsyscomgetsettings_struct
{
	RTS_IEC_HANDLE hCom;				/* VAR_INPUT */	/* <param name="hCom" type="IN">Handle to com port</param> */
	COM_Settings *pSettings;			/* VAR_INPUT */	/* <param name="pSettings" type="IN">Pointer to new settings</param> */
	COM_SettingsEx *pSettingsEx;		/* VAR_INPUT */	/* <param name="pSettingsEx" type="IN">Pointer to extended settings</param> */
	RTS_IEC_RESULT SysComGetSettings;	/* VAR_OUTPUT */	
} syscomgetsettings_struct;

DEF_API(`void',`CDECL',`syscomgetsettings',`(syscomgetsettings_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF56E4DFA),0x03050500)

/**
 * <description>Open a serial communication device.</description>
 * <result><p>RESULT: Handle to the opened com port or RTS_INVALID_HANDLE if failed</p></result>
 */
typedef struct tagsyscomopen_struct
{
	RTS_IEC_INT sPort;					/* VAR_INPUT, Enum: COM_PORTS */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param> */
	RTS_IEC_HANDLE SysComOpen;			/* VAR_OUTPUT */	
} syscomopen_struct;

DEF_API(`void',`CDECL',`syscomopen',`(syscomopen_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1CE3B492),0x03050500)

/**
 * <description>Opens a serial communication device specified by settings</description>
 * <result><p>RESULT: Handle to the opened com port or RTS_INVALID_HANDLE if failed</p></result>
 */
typedef struct tagsyscomopen2_struct
{
	COM_Settings *pSettings;			/* VAR_INPUT */	/* <param name="pSettings" type="IN">Settings for the communication device.
	See category "Com port settings" for detailed information</param> */
	COM_SettingsEx *pSettingsEx;		/* VAR_INPUT */	/* <param name="pSettingsEx" type="IN">Optional extended settings for the serial device. Can be 0.</param> */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to runtime system error code (see CmpErrors.library)</param> */
	RTS_IEC_HANDLE SysComOpen2;			/* VAR_OUTPUT */	
} syscomopen2_struct;

DEF_API(`void',`CDECL',`syscomopen2',`(syscomopen2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x62B114BA),0x03050500)

/**
 * <description>Clear the fifo buffer of the serial interface</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsyscompurge_struct
{
	RTS_IEC_HANDLE hCom;				/* VAR_INPUT */	/* <param name="hCom" type="IN">Handle to com port</param> */
	RTS_IEC_RESULT SysComPurge;			/* VAR_OUTPUT */	
} syscompurge_struct;

DEF_API(`void',`CDECL',`syscompurge',`(syscompurge_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC2A013BE),0x03050500)

/**
 * <description>Reads a number bytes from the specifed device to the receive buffer.
 * <p>IMPLEMENTATION NOTE: If the timeout elapsed until the requested number of bytes are received,
 *	the function returns with the bytes still received! This must be considered in the caller and
 *	the implementation!</p></description>
 * <result><p>RESULT: Number of actually read bytes</p></result>
 */
typedef struct tagsyscomread_struct
{
	RTS_IEC_HANDLE hCom;				/* VAR_INPUT */	/* <param name="hCom" type="IN">Handle to com port</param> */
	RTS_IEC_BYTE *pbyBuffer;			/* VAR_INPUT */	/* <param name="pbyBuffer" type="IN">Pointer to data buffer for received data</param> */
	RTS_IEC_UDINT ulSize;				/* VAR_INPUT */	/* <param name="uiSize" type="IN">Requested number of bytes to read. Must be less or equal the size
	of the receive buffer!</param> */
	RTS_IEC_UDINT ulTimeout;			/* VAR_INPUT, Enum: COM_TIMEOUT */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to return the runtime system error code (see CmpErrors.library).</param> */
	RTS_IEC_UDINT SysComRead;			/* VAR_OUTPUT */	
} syscomread_struct;

DEF_API(`void',`CDECL',`syscomread',`(syscomread_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xDEDB5081),0x03050500)

/**
 * <description>Set the parameter of the interface specified by handle.</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsyscomsetsettings_struct
{
	RTS_IEC_HANDLE hCom;				/* VAR_INPUT */	/* <param name="hCom" type="IN">Handle to com port</param> */
	COM_Settings *pSettings;			/* VAR_INPUT */	/* <param name="pSettings" type="IN">Pointer to new settings</param> */
	COM_SettingsEx *pSettingsEx;		/* VAR_INPUT */	/* <param name="pSettingsEx" type="IN">Pointer to extended settings</param> */
	RTS_IEC_RESULT SysComSetSettings;	/* VAR_OUTPUT */	
} syscomsetsettings_struct;

DEF_API(`void',`CDECL',`syscomsetsettings',`(syscomsetsettings_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x7064AF11),0x03050500)

/**
 * <description>Set the timeout of the specified serial interface (hardware timeout).
 *	The Timeout is the time between two received or sent characters until the read or write operation
 *	will return. Typically this value should be 0 (returns immediately)</description>
 * <result><p>RESULT: Returns the runtime system error code (see CmpErrors.library).</p></result>
 */
typedef struct tagsyscomsettimeout_struct
{
	RTS_IEC_HANDLE hCom;				/* VAR_INPUT */	/* <param name="hCom" type="IN">Handle to com port</param> */
	RTS_IEC_UDINT ulTimeout;			/* VAR_INPUT, Enum: COM_TIMEOUT */
	RTS_IEC_RESULT SysComSetTimeout;	/* VAR_OUTPUT */	
} syscomsettimeout_struct;

DEF_API(`void',`CDECL',`syscomsettimeout',`(syscomsettimeout_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x2E035E87),0x03050500)

/**
 * <description><p>Writes a number bytes to the specifed device from the sent buffer.</p>
 * <p>IMPLEMENTATION NOTE: If the timeout elapsed until the requested number of bytes are sent,
 *	the function returns with the bytes still sent! This must be considered in the caller and
 *	the implementation!</p></description>
 * <result><p>RESULT: Number of actually written bytes</p></result>
 */
typedef struct tagsyscomwrite_struct
{
	RTS_IEC_HANDLE hCom;				/* VAR_INPUT */	/* <param name="hCom" type="IN">Handle to com port</param> */
	RTS_IEC_BYTE *pbyBuffer;			/* VAR_INPUT */	/* <param name="pbyBuffer" type="IN">Pointer to data buffer for sent data</param> */
	RTS_IEC_UDINT ulSize;				/* VAR_INPUT */	/* <param name="uiSize" type="IN">Requested number of bytes to sent. Must be less or equal the size
	of the sent buffer!</param> */
	RTS_IEC_UDINT ulTimeout;			/* VAR_INPUT, Enum: COM_TIMEOUT */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* <param name="pResult" type="OUT">Pointer to return the runtime system error code (see CmpErrors.library).</param> */
	RTS_IEC_UDINT SysComWrite;			/* VAR_OUTPUT */	
} syscomwrite_struct;

DEF_API(`void',`CDECL',`syscomwrite',`(syscomwrite_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA00AEE60),0x03050500)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


typedef COM_Settings	COMSettings;
typedef COM_SettingsEx	COMSettingsEx;

#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysComOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysComOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>Open a serial communication device</description>
 * <param name="sPort" type="IN">Number of the Port to open: 1=COM1, 2=COM2, ...</param>
 * <param name="pResult" type="OUT">Pointer to error code </param>
 * <result>Handle to the interface or RTS_INVALID_HANDLE if failed</result>
 */
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysComOpen',`(short sPort, RTS_RESULT *pResult)')

/**
 * <description>Opens a serial communication device specified with settings</description>
 * <param name="pSettings" type="IN">Settings for the communication device. 
 *	See category "Com port settings" for detailed information</param>
 * <param name="pSettingsEx" type="IN">Optional extended settings for the serial device. Can be NULL.</param>
 * <param name="pResult" type="OUT">Pointer to error code </param>
 * <result>Handle to the interface or RTS_INVALID_HANDLE if failed</result>
 */
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`SysComOpen2',`(COM_Settings *pSettings, COM_SettingsEx *pSettingsEx, RTS_RESULT *pResult)')

/**
 * <description>Set the parameter of the interface specified by handle</description>
 * <param name="hCom" type="IN">Handle to Com Port</param>
 * <param name="pSettings" type="IN">Pointer to new settings</param>
 * <param name="pSettingsEx" type="IN">Pointer to extended settings</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysComSetSettings',`(RTS_HANDLE hCom, COM_Settings *pSettings, COM_SettingsEx *pSettingsEx)')

/**
 * <description>Get the parameter of the interface specified by handle</description>
 * <param name="hCom" type="IN">Handle to Com Port</param>
 * <param name="pSettings" type="IN">Pointer to new settings</param>
 * <param name="pSettingsEx" type="IN">Pointer to extended settings</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysComGetSettings',`(RTS_HANDLE hCom, COM_Settings *pSettings, COM_SettingsEx *pSettingsEx)')

/**
 * <description>Close a serial communication device</description>
 * <param name="hCom" type="IN">Handle to com port</param>
 * <result>error code</result>
 */
DEF_DELETEITF_API(`RTS_RESULT',`CDECL',`SysComClose',`(RTS_HANDLE hCom)')

/**
 * <description>Reads a number bytes from the specifed device to the receive buffer.
 *
 * <p>IMPLEMENTATION NOTE: If the timeout elapsed until the requested number of bytes are received,
 *	the function returns with the bytes still received! This must be considered in the caller and
 *	the implementation!</p></description>
 *
 * <param name="hCom" type="IN">Handle to com port</param>
 * <param name="pbyBuffer" type="IN">Pointer to data buffer for received data</param>
 * <param name="uiSize" type="IN">Requested number of bytes to read. Must be less or equal the size
 *	of the receive buffer!</param>
 * <param name="ulTimeout" type="IN">Timeout to read data from the device. 0=Immediate return.
 *	If the timeout elapsed, the function returns with the still received data (could be less then the 
 *	requested number of bytes!)</param>
 * <param name="pResult" type="IN">Pointer to error code, ERR_TIMEOUT if timeout elapsed</param>
 * <result>Number of actually read bytes</result>
 */
DEF_HANDLEITF_API(`RTS_UI32',`CDECL',`SysComRead',`(RTS_HANDLE hCom, unsigned char *pbyBuffer, RTS_UI32 uiSize, RTS_UI32 ulTimeout, RTS_RESULT *pResult)')

/**
 * <description>Writes a number bytes to the specifed device from the sent buffer.
 *
 * <p>IMPLEMENTATION NOTE: If the timeout elapsed until the requested number of bytes are sent,
 *	the function returns with the bytes still sent! This must be considered in the caller and
 *	the implementation!</p></description>
 *
 * <param name="hCom" type="IN">Handle to com port</param>
 * <param name="pbyBuffer" type="IN">Pointer to data buffer for sent data</param>
 * <param name="uiSize" type="IN">Requested number of bytes to sent. Must be less or equal the size
 *	of the sent buffer!</param>
 * <param name="ulTimeout" type="IN">Timeout to sent data to the device. 0=Immediate return.
 *	If the timeout elapsed, the function returns with the still sent data (could be less then the 
 *	requested number of bytes!)</param>
 * <param name="pResult" type="IN">Pointer to error code, ERR_TIMEOUT if timeout elapsed</param>
 * <result>Number of actually written bytes</result>
 */
DEF_HANDLEITF_API(`RTS_UI32',`CDECL',`SysComWrite',`(RTS_HANDLE hCom, unsigned char *pbyBuffer, RTS_UI32 uiSize, RTS_UI32 ulTimeout, RTS_RESULT *pResult)')

 /**
 * <description>Clear the fifo buffer of the serial interface</description>
 * <param name="hCom" type="IN">Handle to com port</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysComPurge',`(RTS_HANDLE hCom)')

/**
 * <description>Set the timeout of the specified serial interface (hardware timeout).
 *	The Timeout is the time between two received or sent characters until the read or write operation
 *	will return. Typically this value should be 0 (returns immediately)</description>
 * <param name="hCom" type="IN">Handle to com port</param>
 * <param name="ulTimeout" type="IN">Timeout to set</param>
 * <result>error code</result>
 */
DEF_HANDLEITF_API(`RTS_RESULT',`CDECL',`SysComSetTimeout',`(RTS_HANDLE hCom, RTS_UI32 ulTimeout)')


#ifdef __cplusplus
}
#endif
