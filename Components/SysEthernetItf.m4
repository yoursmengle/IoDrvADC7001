/**
 * <interfacename>SysEthernet</interfacename>
 * <description> 
 *	<p>The SysEthernet interface contains low level routines for a direct access to an ethernet controller.
 *	This interface is typically used by an EtherCAT driver.</p>
 *	<p>All other ethernet communciation components use higher level routines (see SysSocket interface).</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`SysEthernet')

/**
 * <category>Static defines</category>
 * <description>Maximum number of supported adapters</description>
 */
#define MAX_NUM_ADAPTERS 5

/**
 * <category>Static defines</category>
 * <description>Maximum mac address length</description>
 */
#define MAX_MAC_ADDR_LENGTH 8

/**
 * <category>Static defines</category>
 * <description>Maximum packet size</description>
 */
#define MAX_PACKET_SIZE 1514

/**
 * <category>Static defines</category>
 * <description>Maximum queue size</description>
 */
#define MAX_QUEUE_SIZE 15000

/**
 * <category>Static defines</category>
 * <description></description>
 */
#define DEFAULT_ADAPTER_NAMELIST 1000

/**
 * <category>Static defines</category>
 * <description>Ethercat protocol type</description>
 */
#define PROTO_ECAT 0x88A4

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>filter for incoming packets by protocol type. Default is Ethercat</description>
 */
#define SYSETHERNETKEY_INT_LINUX_PROTOCOLFILTER			"Linux.ProtocolFilter"
#define SYSETHERNETKEY_INT_LINUX_PROTOCOLFILTER_DEFAULT	PROTO_ECAT

/**
 * <category>Event parameter</category>
 * <element name="pFrame" type="IN">Pointer to one ethernet frame</element>
 */
typedef struct
{
	unsigned char* pFrame;
} EVTPARAM_SysEthernet;
#define EVTPARAMID_SysEthernet		0x0001
#define EVTVERSION_SysEthernet		0x0001

/**
 * <category>Events</category>
 * <description>Event is sent when ethernet packet has arrived</description>
 * <param name="pEventParam" type="IN">EVTPARAM_SysEthernet</param>
 */
#define EVT_EthPacketArrived					MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Events</category>
 * <description>Event is sent when ethernet packet was sent</description>
 * <param name="pEventParam" type="IN">EVTPARAM_SysEthernet</param>
 */
#define EVT_EthPacketSent						MAKE_EVENTID(EVTCLASS_INFO, 2)

/**
 * <category>Events</category>
 * <description>Event is created by the platformspecific adaptation of SysEthernet, in case there are parameters, that are designed to be changed by the application.
 * This way it is possible for the application to check if there are such possibilities and to get some paramters by calling "EventPost"</description>
 * <param name="pEventParam" type="IN">EVTPARAM_SysEthernet</param>
 */
#define EVT_EthGetParameterValue						MAKE_EVENTID(EVTCLASS_INFO, 3)

/**
 * <category>Events</category>
 * <description>Event is created by the platformspecific adaptation of SysEthernet, in case there are parameters, that are designed to be changed by the application.
 * This way it is possible for the application to check if there are such possibilities and to set some paramters by calling "EventPost"</description>
 * <param name="pEventParam" type="IN">EVTPARAM_SysEthernet</param>
 */
#define EVT_EthSetParameterValue						MAKE_EVENTID(EVTCLASS_INFO, 4)

/**
 * <category>Event parameter</category>
 * <element name="ulLength" type="IN">Length of the parameter data.</element>
 * <element name="ulID" type="IN">A 32 bit value that identifies the parameter.</element>
 * <element name="pData" type="IN">A pointer to the value data of the parameter.</element>
 */
typedef struct
{
	unsigned long ulID;
	int iMasterNum;
	unsigned long ulLength;
	void* pData;
} EVTPARAM_SysEthernetSetGetParameter;
#define EVTPARAM_SysEthernetSetGetParameterID_NoPollingInGetEthframe	0x0001
#define EVTPARAM_SysEthernetSetGetParameterID_PollingOnlyNoInterrupts	0x0002
#define EVTPARAMID_SysEthernetParameter		0x0002


/**
 * <category>Online services</category>
 */

#define SRV_ETC_GETSOCKADAPTERINFO			0x76
#define SRV_ETC_GETADAPTERINFO				0x77

/**
 * <category>Online service tags</category>
 */
#define TAG_ETC_MASTERLIST					0x81
#define TAG_ETC_MASTERNAME					0x02
#define TAG_ETC_MASTERDESC					0x03
#define TAG_ETC_MASTERMAC					0x04

#define TAG_ETC_SOCKADAPTER					0x11
#define TAG_ETC_SOCKADAPTER_NEXT_INDEX		0x12

/**
 * <category>Online services</category>
 * <Description>
 *  Service to retrieve the adapter info on SysSocket level. Should be polled until the content of TAG_SERVICE_RESULT is 
 *  different from ERR_ENTRIES_REMAINING to get all adapters. 
 * </Description>
 * <service name="SRV_ETC_GETSOCKADAPTERINFO">
 *	<Request>
 *		<tag name="TAG_ETC_SOCKADAPTER_NEXT_INDEX" required="optional">[RTS_UI32]: Index of first adapter, which should be read. Default is 0, if tag is omitted.</tag>
 *	</Request>
 *	<Response>
 *		<tag name="TAG_ETC_SOCKADAPTER" required="optional">[SOCK_ADAPTER_INFORMATION]: Adapter information for one network adapter. 
 *			For each adapter one tag of this type is added. Layout of IEC structure SOCK_ADAPTER_INFORMATION is used.
 *			Is not returned, if no adapter is available.</tag>
 *		<tag name="TAG_ETC_SOCKADAPTER_NEXT_INDEX" required="optional">[RTS_UI32]: Index of next adapter, which should be requested by next service
 *			Only returned, if not all adapter informations fits into the communication buffer.</tag>
 *		<tag name="TAG_SERVICE_RESULT" required="mandatory">[RTS_UI16]: Result code of online service: 
 *				ERR_OK (all adapters have been read), 
 *				ERR_NOTIMPLEMENTED (SysSocket does not provide the functionality to read the adapter information),
 *				ERR_NOT_SUPPORTED (SysSockGetFirstAdapterInfo or SysSockGetFirstAdapterInfo are not available),
 *				ERR_FAILED (no adapter information available, e. g. no adapter present), 
 *				ERR_ENTRIES_REMAINING (not all adapter informations fits into the communication buffer).</tag>
 *	</Response>
 * </service>
 */
 

typedef struct
{
	RTS_UI32 MacAddressLen;					/* Length of the link layer address */
	unsigned char MacAddress[MAX_MAC_ADDR_LENGTH];	/* Link layer address */
}MacAdr;

typedef struct
{
	unsigned char dest_mac[6];
	unsigned char source_mac[6];
	unsigned short eth_type;
	unsigned char head_length;
	unsigned char service;
	unsigned char firsttel[1500];
}Ethernetframe;


typedef struct
{
	RTS_I32 iMasterNum;
	MacAdr MacAddress;
	RTS_I32 nReturnVal;
}OpenEthernetInterface;

typedef struct
{
	RTS_I32 iMasterNum;
	RTS_I32 nReturnVal;
}CloseEthernetInterface;


typedef struct
{
	RTS_I32 iMasterNum;
	Ethernetframe *pFrame;
	RTS_I32 nSize;
	RTS_I32 nReturnVal;
}SendEthernetInterface;

typedef struct
{
	RTS_I32 iMasterNum;
	unsigned char **ppFrame;
	RTS_I32* pnSize;
	RTS_I32 nReturnVal;
}GetEthernetInterface;

typedef struct
{
	unsigned char **ppFrame;
	RTS_I32* pnSize;
	RTS_I32 nReturnVal;
}GetIPEthernetInterface;

typedef struct
{
	Ethernetframe *pFrame;
	RTS_I32 nSize;
	RTS_I32 nReturnVal;
}SendIPEthernetInterface;

typedef struct
{
	RTS_I32* piAdapterCnt;
	RTS_I32 nReturnVal;
}GetNumberOfEthernetInterface;

typedef struct
{
	int iAdapterNum;
	char *pszName;
	char *pszDescription;
	int iBuffersize;
	int iMacLength;
	char* MacAddress;
	RTS_I32 nReturnVal;
}GetAdapterInfoEthernetInterface;

#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysEthernetOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysEthernetOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>Open a network adapter</description>
 * <param name="poei" type="IN">pointer to parameters</param>
 * <result>error code</result>
 */
DEF_ITF_API(`void',`CDECL',`openethernet',`(OpenEthernetInterface* poei)',1)

/**
 * <description>Send etherpacket</description>
 * <param name="psfi" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
DEF_ITF_API(`void',`CDECL',`sendethframe',`(SendEthernetInterface* psfi)',1)

/**
 * <description>Get ethernet packet</description>
 * <param name="pgei" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
DEF_ITF_API(`void',`CDECL',`getethframe',`(GetEthernetInterface* pgei)',1)

/**
 * <description>Close network adapter</description>
 * <param name="pcei" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
DEF_ITF_API(`void',`CDECL',`closeethernet',`(CloseEthernetInterface* pcei)',1)

/**
 * <description>Get number of network adapters</description>
 * <param name="pnoei" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
DEF_API(`void',`CDECL',`getnumberofadapters',`(GetNumberOfEthernetInterface* pnoei)',1)

/**
 *  <description>Get info about specified network adapters</description>
 * <param name="paiei" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
DEF_API(`void',`CDECL',`getadapterinfo',`(GetAdapterInfoEthernetInterface* paiei)',1)


/**
 * <description>Send IP etherpacket (EoE)</description>
 * <param name="psfi" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
DEF_ITF_API(`void',`CDECL',`sendIPethframe',`(SendIPEthernetInterface* psfi)',1)

/**
 * <description>Get IP ethernet packet</description>
 * <param name="pgei" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
DEF_ITF_API(`void',`CDECL',`getIPethframe',`(GetIPEthernetInterface* pgei)',1)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>AutoNegCaps</description>
 */
#define SYSETH_AUTONEGCAP_OTHERORUNKNOWN		RTS_IEC_ULINT_C(0x1)	/* other or unknown */
#define SYSETH_AUTONEGCAP_10BASET		RTS_IEC_ULINT_C(0x2)	/* 10BASE-T  half duplex mode */
#define SYSETH_AUTONEGCAP_10BASETFD		RTS_IEC_ULINT_C(0x4)	/* 10BASE-T  full duplex mode */
#define SYSETH_AUTONEGCAP_100BASET4		RTS_IEC_ULINT_C(0x8)	/* 100BASE-T4 */
#define SYSETH_AUTONEGCAP_100BASETX		RTS_IEC_ULINT_C(0x10)	/* 100BASE-TX half duplex mode */
#define SYSETH_AUTONEGCAP_100BASETXFD		RTS_IEC_ULINT_C(0x20)	/* 100BASE-TX full duplex mode */
#define SYSETH_AUTONEGCAP_100BASET2		RTS_IEC_ULINT_C(0x40)	/* 100BASE-T2 half duplex mode */
#define SYSETH_AUTONEGCAP_100BASET2FD		RTS_IEC_ULINT_C(0x80)	/* 100BASE-T2 full duplex mode */
#define SYSETH_AUTONEGCAP_FDXPAUSE		RTS_IEC_ULINT_C(0x100)	/* PAUSE for full-duplex links */
#define SYSETH_AUTONEGCAP_FDXAPAUSE		RTS_IEC_ULINT_C(0x200)	/* Asymmetric PAUSE for full-duplex links */
#define SYSETH_AUTONEGCAP_FDXSPAUSE		RTS_IEC_ULINT_C(0x400)	/* Symmetric PAUSE for full-duplex links */
#define SYSETH_AUTONEGCAP_FDXBPAUSE		RTS_IEC_ULINT_C(0x800)	/* Asymmetric and Symmetric PAUSE for full-duplex links */
#define SYSETH_AUTONEGCAP_1000BASEX		RTS_IEC_ULINT_C(0x1000)	/* 1000BASE-X, -LX, -SX, -CX half duplex mode */
#define SYSETH_AUTONEGCAP_1000BASEXFD		RTS_IEC_ULINT_C(0x2000)	/* 1000BASE-X, -LX, -SX, -CX full duplex mode */
#define SYSETH_AUTONEGCAP_1000BASET		RTS_IEC_ULINT_C(0x4000)	/* 1000BASE-T half duplex mode */
#define SYSETH_AUTONEGCAP_1000BASETFD		RTS_IEC_ULINT_C(0x8000)	/* 1000BASE-T full duplex mode */
#define SYSETH_AUTONEGCAP_10GBASET		RTS_IEC_ULINT_C(0x10000)	/* 10GBASE-T */
#define SYSETH_AUTONEGCAP_1000BASEKX		RTS_IEC_ULINT_C(0x20000)	/* 1000BASE-KX */
#define SYSETH_AUTONEGCAP_10GBASEKX4		RTS_IEC_ULINT_C(0x40000)	/* 10GBASE-KX4 */
#define SYSETH_AUTONEGCAP_10GBASEKR		RTS_IEC_ULINT_C(0x80000)	/* 10GBASE-KR */
#define SYSETH_AUTONEGCAP_40GBASEKR4		RTS_IEC_ULINT_C(0x100000)	/* 40GBASE-KR4 */
#define SYSETH_AUTONEGCAP_40GBASECR4		RTS_IEC_ULINT_C(0x200000)	/* 40GBASE-CR4 */
#define SYSETH_AUTONEGCAP_100GBASECR10		RTS_IEC_ULINT_C(0x400000)	/* 100GBASE-CR10 */
#define SYSETH_AUTONEGCAP_1000BASET1		RTS_IEC_ULINT_C(0x800000)	/* 1000BASE-T1 */
#define SYSETH_AUTONEGCAP_25GBASERS		RTS_IEC_ULINT_C(0x1000000)	/* 25GBASE-CR-S or 25GBASE-KR-S */
#define SYSETH_AUTONEGCAP_25GBASER		RTS_IEC_ULINT_C(0x2000000)	/* 25GBASE-CR or 25GBASE-KR */
#define SYSETH_AUTONEGCAP_RSFEC25GREQ		RTS_IEC_ULINT_C(0x4000000)	/* 25Gb/s RS-FEC */
#define SYSETH_AUTONEGCAP_BASEFEC25GREQ		RTS_IEC_ULINT_C(0x8000000)	/* 25Gb/s BASE-R FEC */
#define SYSETH_AUTONEGCAP_25GBASET		RTS_IEC_ULINT_C(0x10000000)	/* 25GBASE-T */
#define SYSETH_AUTONEGCAP_40GBASET		RTS_IEC_ULINT_C(0x20000000)	/* 40GBASE-T */
#define SYSETH_AUTONEGCAP_100GBASECR4		RTS_IEC_ULINT_C(0x40000000)	/* 100GBASE-CR4 */
#define SYSETH_AUTONEGCAP_100GBASEKR4		RTS_IEC_ULINT_C(0x80000000)	/* 100GBASE-KR4 */
#define SYSETH_AUTONEGCAP_100GBASEKP4		RTS_IEC_ULINT_C(0x100000000)	/* 100GBASE-KP4 */
#define SYSETH_AUTONEGCAP_FORCEMS		RTS_IEC_ULINT_C(0x200000000)	/* 1000BASE-T1 Force MS */

/**
 * <description>AutoNegMode</description>
 */
#define SYSETH_AUTONEGMODE_DISABLED		RTS_IEC_USINT_C(0x0)	
#define SYSETH_AUTONEGMODE_ENABLED		RTS_IEC_USINT_C(0x1)	
#define SYSETH_AUTONEGMODE_UNKNOWN		RTS_IEC_USINT_C(0xFF)	

/**
 * <description>AutoNegSupport</description>
 */
#define SYSETH_AUTONEGSUP_NOTSUPPORTED		RTS_IEC_USINT_C(0x0)	
#define SYSETH_AUTONEGSUP_SUPPORTED		RTS_IEC_USINT_C(0x1)	
#define SYSETH_AUTONEGSUP_UNKNOWN		RTS_IEC_USINT_C(0xFF)	

/**
 * <description>MauType</description>
 */
#define SYSETH_MAUTYPE_OTHERORUNKNOWN		RTS_IEC_UDINT_C(0x0)	/* other or unknown */
#define SYSETH_MAUTYPE_AUI		RTS_IEC_UDINT_C(0x1)	/* AUI */
#define SYSETH_MAUTYPE_10BASE5		RTS_IEC_UDINT_C(0x2)	/* 10BASE-5 */
#define SYSETH_MAUTYPE_FOIRL		RTS_IEC_UDINT_C(0x3)	/* FOIRL */
#define SYSETH_MAUTYPE_10BASE2		RTS_IEC_UDINT_C(0x4)	/* 10BASE-2 */
#define SYSETH_MAUTYPE_10BASET		RTS_IEC_UDINT_C(0x5)	/* 10BASE-T duplex mode unknown */
#define SYSETH_MAUTYPE_10BASEFP		RTS_IEC_UDINT_C(0x6)	/* 10BASE-FP */
#define SYSETH_MAUTYPE_10BASEFB		RTS_IEC_UDINT_C(0x7)	/* 10BASE-FB */
#define SYSETH_MAUTYPE_10BASEFL		RTS_IEC_UDINT_C(0x8)	/* 10BASE-FL duplex mode unknown */
#define SYSETH_MAUTYPE_10BROAD36		RTS_IEC_UDINT_C(0x9)	/* 10BROAD36 */
#define SYSETH_MAUTYPE_10BASETHD		RTS_IEC_UDINT_C(0xA)	/* 10BASE-T  half duplex mode */
#define SYSETH_MAUTYPE_10BASETFD		RTS_IEC_UDINT_C(0xB)	/* 10BASE-T  full duplex mode */
#define SYSETH_MAUTYPE_10BASEFLHD		RTS_IEC_UDINT_C(0xC)	/* 10BASE-FL half duplex mode */
#define SYSETH_MAUTYPE_10BASEFLFD		RTS_IEC_UDINT_C(0xD)	/* 10BASE-FL full duplex mode */
#define SYSETH_MAUTYPE_100BASET4		RTS_IEC_UDINT_C(0xE)	/* 100BASE-T4 */
#define SYSETH_MAUTYPE_100BASETXHD		RTS_IEC_UDINT_C(0xF)	/* 100BASE-TX half duplex mode */
#define SYSETH_MAUTYPE_100BASETXFD		RTS_IEC_UDINT_C(0x10)	/* 100BASE-TX full duplex mode */
#define SYSETH_MAUTYPE_100BASEFXHD		RTS_IEC_UDINT_C(0x11)	/* 100BASE-FX half duplex mode */
#define SYSETH_MAUTYPE_100BASEFXFD		RTS_IEC_UDINT_C(0x12)	/* 100BASE-FX full duplex mode */
#define SYSETH_MAUTYPE_100BASET2HD		RTS_IEC_UDINT_C(0x13)	/* 100BASE-T2 half duplex mode */
#define SYSETH_MAUTYPE_100BASET2FD		RTS_IEC_UDINT_C(0x14)	/* 100BASE-T2 full duplex mode */
#define SYSETH_MAUTYPE_1000BASEXHD		RTS_IEC_UDINT_C(0x15)	/* 1000BASE-X half duplex mode */
#define SYSETH_MAUTYPE_1000BASEXFD		RTS_IEC_UDINT_C(0x16)	/* 1000BASE-X full duplex mode */
#define SYSETH_MAUTYPE_1000BASELXHD		RTS_IEC_UDINT_C(0x17)	/* 1000BASE-LX half duplex mode */
#define SYSETH_MAUTYPE_1000BASELXFD		RTS_IEC_UDINT_C(0x18)	/* 1000BASE-LX full duplex mode */
#define SYSETH_MAUTYPE_1000BASESXHD		RTS_IEC_UDINT_C(0x19)	/* 1000BASE-SX half duplex mode */
#define SYSETH_MAUTYPE_1000BASESXFD		RTS_IEC_UDINT_C(0x1A)	/* 1000BASE-SX full duplex mode */
#define SYSETH_MAUTYPE_1000BASECXHD		RTS_IEC_UDINT_C(0x1B)	/* 1000BASE-CX half duplex mode */
#define SYSETH_MAUTYPE_1000BASECXFD		RTS_IEC_UDINT_C(0x1C)	/* 1000BASE-CX full duplex mode */
#define SYSETH_MAUTYPE_1000BASETHD		RTS_IEC_UDINT_C(0x1D)	/* 1000BASE-T half duplex mode */
#define SYSETH_MAUTYPE_1000BASETFD		RTS_IEC_UDINT_C(0x1E)	/* 1000BASE-T full duplex mode */
#define SYSETH_MAUTYPE_10GBASEX		RTS_IEC_UDINT_C(0x1F)	/* 10GBASE-X */
#define SYSETH_MAUTYPE_10GBASELX4		RTS_IEC_UDINT_C(0x20)	/* 10GBASE-LX4 */
#define SYSETH_MAUTYPE_10GBASER		RTS_IEC_UDINT_C(0x21)	/* 10GBASE-R */
#define SYSETH_MAUTYPE_10GBASEER		RTS_IEC_UDINT_C(0x22)	/* 10GBASE-ER */
#define SYSETH_MAUTYPE_10GBASELR		RTS_IEC_UDINT_C(0x23)	/* 10GBASE-LR */
#define SYSETH_MAUTYPE_10GBASESR		RTS_IEC_UDINT_C(0x24)	/* 10GBASE-SR */
#define SYSETH_MAUTYPE_10GBASEW		RTS_IEC_UDINT_C(0x25)	/* 10GBASE-W */
#define SYSETH_MAUTYPE_10GBASEEW		RTS_IEC_UDINT_C(0x26)	/* 10GBASE-EW */
#define SYSETH_MAUTYPE_10GBASELW		RTS_IEC_UDINT_C(0x27)	/* 10GBASE-LW */
#define SYSETH_MAUTYPE_10GBASESW		RTS_IEC_UDINT_C(0x28)	/* 10GBASE-SW */
#define SYSETH_MAUTYPE_10GBASECX4		RTS_IEC_UDINT_C(0x29)	/* 10GBASE-CX4 */
#define SYSETH_MAUTYPE_2BASETL		RTS_IEC_UDINT_C(0x2A)	/* 2BASE-TL */
#define SYSETH_MAUTYPE_10PASSTS		RTS_IEC_UDINT_C(0x2B)	/* 10PASS-TS */
#define SYSETH_MAUTYPE_100BASEBX10D		RTS_IEC_UDINT_C(0x2C)	/* 100BASE-BX10D */
#define SYSETH_MAUTYPE_100BASEBX10U		RTS_IEC_UDINT_C(0x2D)	/* 100BASE-BX10U */
#define SYSETH_MAUTYPE_100BASELX10		RTS_IEC_UDINT_C(0x2E)	/* 100BASE-LX10 */
#define SYSETH_MAUTYPE_1000BASEBX10D		RTS_IEC_UDINT_C(0x2F)	/* 1000BASE-BX10D */
#define SYSETH_MAUTYPE_1000BASEBX10U		RTS_IEC_UDINT_C(0x30)	/* 1000BASE-BX10U */
#define SYSETH_MAUTYPE_1000BASELX10		RTS_IEC_UDINT_C(0x31)	/* 1000BASE-LX10 */
#define SYSETH_MAUTYPE_1000BASEPX10D		RTS_IEC_UDINT_C(0x32)	/* 1000BASE-PX10D */
#define SYSETH_MAUTYPE_1000BASEPX10U		RTS_IEC_UDINT_C(0x33)	/* 1000BASE-PX10U */
#define SYSETH_MAUTYPE_1000BASEPX20D		RTS_IEC_UDINT_C(0x34)	/* 1000BASE-PX20D */
#define SYSETH_MAUTYPE_1000BASEPX20U		RTS_IEC_UDINT_C(0x35)	/* 1000BASE-PX20U */
#define SYSETH_MAUTYPE_10GBASET		RTS_IEC_UDINT_C(0x36)	/* 10GBASE-T */
#define SYSETH_MAUTYPE_10GBASELRM		RTS_IEC_UDINT_C(0x37)	/* 10GBASE-LRM */
#define SYSETH_MAUTYPE_1000BASEKX		RTS_IEC_UDINT_C(0x38)	/* 1000BASE-KX */
#define SYSETH_MAUTYPE_10GBASEKX4		RTS_IEC_UDINT_C(0x39)	/* 10GBASE-KX4 */
#define SYSETH_MAUTYPE_10GBASEKR		RTS_IEC_UDINT_C(0x3A)	/* 10GBASE-KR */
#define SYSETH_MAUTYPE_10G1GBASEPRXD1		RTS_IEC_UDINT_C(0x3B)	/* 10/1GBASE-PRX-D1 */
#define SYSETH_MAUTYPE_10G1GBASEPRXD2		RTS_IEC_UDINT_C(0x3C)	/* 10/1GBASE-PRX-D2 */
#define SYSETH_MAUTYPE_10G1GBASEPRXD3		RTS_IEC_UDINT_C(0x3D)	/* 10/1GBASE-PRX-D3 */
#define SYSETH_MAUTYPE_10G1GBASEPRXU1		RTS_IEC_UDINT_C(0x3E)	/* 10/1GBASE-PRX-U1 */
#define SYSETH_MAUTYPE_10G1GBASEPRXU2		RTS_IEC_UDINT_C(0x3F)	/* 10/1GBASE-PRX-U2 */
#define SYSETH_MAUTYPE_10G1GBASEPRXU3		RTS_IEC_UDINT_C(0x40)	/* 10/1GBASE-PRX-U3 */
#define SYSETH_MAUTYPE_10GBASEPRD1		RTS_IEC_UDINT_C(0x41)	/* 10GBASE-PR-D1 */
#define SYSETH_MAUTYPE_10GBASEPRD2		RTS_IEC_UDINT_C(0x42)	/* 10GBASE-PR-D2 */
#define SYSETH_MAUTYPE_10GBASEPRD3		RTS_IEC_UDINT_C(0x43)	/* 10GBASE-PR-D3 */
#define SYSETH_MAUTYPE_10GBASEPRU1		RTS_IEC_UDINT_C(0x44)	/* 10GBASE-PR-U1 */
#define SYSETH_MAUTYPE_10GBASEPRU3		RTS_IEC_UDINT_C(0x45)	/* 10GBASE-PR-U3 */
#define SYSETH_MAUTYPE_40GBASEKR4		RTS_IEC_UDINT_C(0x46)	/* 40GBASE-KR4 */
#define SYSETH_MAUTYPE_40GBASECR4		RTS_IEC_UDINT_C(0x47)	/* 40GBASE-CR4 */
#define SYSETH_MAUTYPE_40GBASESR4		RTS_IEC_UDINT_C(0x48)	/* 40GBASE-SR4 */
#define SYSETH_MAUTYPE_40GBASEFR		RTS_IEC_UDINT_C(0x49)	/* 40GBASE-FR */
#define SYSETH_MAUTYPE_40GBASELR4		RTS_IEC_UDINT_C(0x4A)	/* 40GBASE-LR4 */
#define SYSETH_MAUTYPE_100GBASECR10		RTS_IEC_UDINT_C(0x4B)	/* 100GBASE-CR10 */
#define SYSETH_MAUTYPE_100GBASESR10		RTS_IEC_UDINT_C(0x4C)	/* 100GBASE-SR10 */
#define SYSETH_MAUTYPE_100GBASELR4		RTS_IEC_UDINT_C(0x4D)	/* 100GBASE-LR4 */
#define SYSETH_MAUTYPE_100GBASEER4		RTS_IEC_UDINT_C(0x4E)	/* 100GBASE-ER4 */
#define SYSETH_MAUTYPE_1000BASET1		RTS_IEC_UDINT_C(0x4F)	/* 1000BASE-T1 */
#define SYSETH_MAUTYPE_1000BASEPX30D		RTS_IEC_UDINT_C(0x50)	/* 1000BASE-PX30D */
#define SYSETH_MAUTYPE_1000BASEPX30U		RTS_IEC_UDINT_C(0x51)	/* 1000BASE-PX30U */
#define SYSETH_MAUTYPE_1000BASEPX40D		RTS_IEC_UDINT_C(0x52)	/* 1000BASE-PX40D */
#define SYSETH_MAUTYPE_1000BASEPX40U		RTS_IEC_UDINT_C(0x53)	/* 1000BASE-PX40U */
#define SYSETH_MAUTYPE_10G1GBASEPRXD4		RTS_IEC_UDINT_C(0x54)	/* 10/1GBASE-PRX-D4 */
#define SYSETH_MAUTYPE_10G1GBASEPRXU4		RTS_IEC_UDINT_C(0x55)	/* 10/1GBASE-PRX-U4 */
#define SYSETH_MAUTYPE_10GBASEPRD4		RTS_IEC_UDINT_C(0x56)	/* 10GBASE-PRD4 */
#define SYSETH_MAUTYPE_10GBASEPRU4		RTS_IEC_UDINT_C(0x57)	/* 10GBASE-PRU4 */
#define SYSETH_MAUTYPE_25GBASECR		RTS_IEC_UDINT_C(0x58)	/* 25GBASE-CR */
#define SYSETH_MAUTYPE_25GBASECRS		RTS_IEC_UDINT_C(0x59)	/* 25GBASE-CR-S */
#define SYSETH_MAUTYPE_25GBASEKR		RTS_IEC_UDINT_C(0x5A)	/* 25GBASE-KR */
#define SYSETH_MAUTYPE_25GBASEKRS		RTS_IEC_UDINT_C(0x5B)	/* 25GBASE-KR-S */
#define SYSETH_MAUTYPE_25GBASER		RTS_IEC_UDINT_C(0x5C)	/* 25GBASE-R */
#define SYSETH_MAUTYPE_25GBASESR		RTS_IEC_UDINT_C(0x5D)	/* 25GBASE-SR */
#define SYSETH_MAUTYPE_25GBASET		RTS_IEC_UDINT_C(0x5E)	/* 25GBASE-T */
#define SYSETH_MAUTYPE_40GBASEER4		RTS_IEC_UDINT_C(0x5F)	/* 40GBASE-ER4 */
#define SYSETH_MAUTYPE_40GBASER		RTS_IEC_UDINT_C(0x60)	/* 40GBASE-R */
#define SYSETH_MAUTYPE_40GBASET		RTS_IEC_UDINT_C(0x61)	/* 40GBASE-T */
#define SYSETH_MAUTYPE_100GBASECR4		RTS_IEC_UDINT_C(0x62)	/* 100GBASE-CR4 */
#define SYSETH_MAUTYPE_100GBASEKR4		RTS_IEC_UDINT_C(0x63)	/* 100GBASE-KR4 */
#define SYSETH_MAUTYPE_100GBASEKP4		RTS_IEC_UDINT_C(0x64)	/* 100GBASE-KP4 */
#define SYSETH_MAUTYPE_100GBASER		RTS_IEC_UDINT_C(0x65)	/* 100GBASE-R */
#define SYSETH_MAUTYPE_100GBASESR4		RTS_IEC_UDINT_C(0x66)	/* 100GBASE-SR4 */

/**
 * <description>OperStatus</description>
 */
#define SYSETH_OPERSTAT_UP		RTS_IEC_UINT_C(0x1)	/* ready to pass packets */
#define SYSETH_OPERSTAT_DOWN		RTS_IEC_UINT_C(0x2)	/* down and not in a condition to pass packets */
#define SYSETH_OPERSTAT_TESTING		RTS_IEC_UINT_C(0x3)	/* in some test mode */
#define SYSETH_OPERSTAT_UNKNOWN		RTS_IEC_UINT_C(0x4)	/* status can not be determined for some reason */
#define SYSETH_OPERSTAT_DORMANT		RTS_IEC_UINT_C(0x5)	/* not up, pending state */
#define SYSETH_OPERSTAT_NOTPRESENT		RTS_IEC_UINT_C(0x6)	/* some component e. g. a hardware device is missing */
#define SYSETH_OPERSTAT_LOWERLAYERDOWN		RTS_IEC_UINT_C(0x7)	/* down due to state of lower-layer interface(s) */

/**
 * <description>ETCStructCommand</description>
 */
typedef struct tagETCStructCommand
{
	RTS_IEC_BYTE byCmd;		
	RTS_IEC_BYTE byIdx;		
	RTS_IEC_WORD wAddress1;		
	RTS_IEC_WORD wAddress2;		/* is offset, when not part of logical address */
	RTS_IEC_WORD wLength;		/* top 11 bit are length, bit 15 is follow indication */
	RTS_IEC_WORD wIrq;		/* reserved */
	RTS_IEC_BYTE abyData[1488];		
	RTS_IEC_WORD wWctr;		/* working counter may be found earlier in packet - valid only  for maximum size */
} ETCStructCommand;

/**
 * <description>StructEthernetframe</description>
 */
typedef struct tagStructEthernetframe
{
	RTS_IEC_BYTE dest_mac[6];		
	RTS_IEC_BYTE source_mac[6];		
	RTS_IEC_WORD ethtype;		
	RTS_IEC_BYTE ethlength;		
	RTS_IEC_BYTE ethservice;		
	ETCStructCommand first;		
} StructEthernetframe;

/**
 * <description>SysEthernetFrame</description>
 */
typedef struct tagSysEthernetFrame
{
	RTS_IEC_UDINT udFrameLen;		
	RTS_IEC_BYTE ethData[1522];		
} SysEthernetFrame;

/**
 * Structure containing the ethernet port configuration and status
 */
typedef struct tagSysEthernetPortConfigAndStatus
{
	RTS_IEC_UDINT udiStructSize;		/* Size of the structure SysEthernetPortConfigAndStatus returned from external implementation */
	RTS_IEC_UDINT udiVersion;		/* Version number of the structure */
	RTS_IEC_UDINT udiMauType;		/* Media Access Unit (MAU) type, see MauType constants SYSETH_MAUTYPE_... */
	RTS_IEC_UINT uiOperStatus;		/* Link state of ethernet port, see OperStatus constants SYSETH_OPERSTAT_... */
	RTS_IEC_USINT usiAutoNegSupport;		/* Autonegotiation support of MAU, see AutoNegSupport constants SYSETH_AUTONEGSUP_... */
	RTS_IEC_USINT usiAutoNegMode;		/* Autonegotiation mode of MAU, see AutoNegMode constants SYSETH_AUTONEGMODE_... */
	RTS_IEC_ULINT uliAutoNegSupportedCap;		/* Supported autonegotiation capabilities of MAU, see AutoNegCaps constants SYSETH_AUTONEGCAP_... */
	RTS_IEC_ULINT uliAutoNegAdvertisedCap;		/* Advertised autonegotiation capabilities of MAU, see AutoNegCaps constants SYSETH_AUTONEGCAP_... */
} SysEthernetPortConfigAndStatus;

/**
 * Close a ethernet adapter.
 */
typedef struct tagsysethernetadapterclose_struct
{
	RTS_IEC_HANDLE hAdapter;			/* VAR_INPUT */	/* Handle to the opened ethernet adapter. Retrieved using SysEthernetAdapterOpen() */
	RTS_IEC_RESULT SysEthernetAdapterClose;	/* VAR_OUTPUT */	
} sysethernetadapterclose_struct;

DEF_API(`void',`CDECL',`sysethernetadapterclose',`(sysethernetadapterclose_struct *p)',1,0x3AF33BA1,0x03050C00)

/**
 * Open an ethernet adapter by its MAC address.
 * .. note::
 *    Each adapter can only be opened once.
 * :return: Returns a handle to the opened adapter. SysTypes.RTS_INVALID_HANDLE is returned if the operation failed.
 */
typedef struct tagsysethernetadapteropen_struct
{
	RTS_IEC_BYTE macAddress[6];			/* VAR_INPUT */	/* MAC address of the adapter to be opened. */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Result of the operation */
	RTS_IEC_HANDLE SysEthernetAdapterOpen;	/* VAR_OUTPUT */	
} sysethernetadapteropen_struct;

DEF_API(`void',`CDECL',`sysethernetadapteropen',`(sysethernetadapteropen_struct *p)',1,0x7E26ED8D,0x03050C00)

/**
 * This function receives the next ethernet frame from the ethernet adapter. A pointer to this frame
 * is returned.
 * ..note::
 *   The frame returned has to be released using the SysEthernetEthFrameRelease() function.
 *   The frame will only be overwritten if the frame is released. As frames are reused when
 *   released pay attention to call this function if processing of the frame has finished.
 * :return: Pointer to the ethernet frame
 */
typedef struct tagsysethernetethframereceive_struct
{
	RTS_IEC_HANDLE hAdapter;			/* VAR_INPUT */	/* Ethernetadapter where to receive the frame. */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Result of the operation. */
	SysEthernetFrame *SysEthernetEthFrameReceive;	/* VAR_OUTPUT */	
} sysethernetethframereceive_struct;

DEF_API(`void',`CDECL',`sysethernetethframereceive',`(sysethernetethframereceive_struct *p)',1,0xAA2055F3,0x03050C00)

/**
 * This function sends an ethernetframe to the given adapter.
 * The data of the frame is copied to the adapter. When this function
 * returns the frame can be overwritten without any problems.
 */
typedef struct tagsysethernetethframesend_struct
{
	RTS_IEC_HANDLE hAdapter;			/* VAR_INPUT */	/* Ethernetadapter where to send the frame. */
	SysEthernetFrame *pFrame;			/* VAR_INPUT */	/* Pointer to the frame to send. */
	RTS_IEC_RESULT SysEthernetEthFrameSend;	/* VAR_OUTPUT */	
} sysethernetethframesend_struct;

DEF_API(`void',`CDECL',`sysethernetethframesend',`(sysethernetethframesend_struct *p)',1,0x9145ED7E,0x03050C00)

/**
 * Release a received frame to indicate that the frame can be reused.
 */
typedef struct tagsysethernetframerelease_struct
{
	SysEthernetFrame *pFrame;			/* VAR_INPUT */	/* Pointer to the frame to release */
	RTS_IEC_RESULT SysEthernetFrameRelease;	/* VAR_OUTPUT */	
} sysethernetframerelease_struct;

DEF_API(`void',`CDECL',`sysethernetframerelease',`(sysethernetframerelease_struct *p)',1,0xDF7EE900,0x03050C00)

/**
 * Get ethernet port configuration and status of an adapter identified by its MAC address.
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsysethernetgetportconfigandstatus_struct
{
	RTS_IEC_BYTE macAddress[6];			/* VAR_INPUT */	/* MAC address of the adapter to get information from */
	SysEthernetPortConfigAndStatus *pPortConfigAndStatus;	/* VAR_INPUT */	/* Port configuration and status structure */
	RTS_IEC_UXINT *puxiPortConfigAndDataSize;	/* VAR_INPUT */	/* Size in bytes of |SysEthernetPortConfigAndStatus|; returns structure size from external implementation */
	RTS_IEC_RESULT SysEthernetGetPortConfigAndStatus;	/* VAR_OUTPUT */	
} sysethernetgetportconfigandstatus_struct;

DEF_API(`void',`CDECL',`sysethernetgetportconfigandstatus',`(sysethernetgetportconfigandstatus_struct *p)',1,RTSITF_GET_SIGNATURE(0xE8D0BEEB, 0x21B15FAE),0x03050C00)

/**
 * This function receives an IP frame from the systems IP Stack.
 * This frame has to be packed into an Ethercat frame and sent to
 * this adapter.
 * ..note::
 *   Special function for Ethernet over Ethercat (EoE) 
 */
typedef struct tagsysethernetipframereceive_struct
{
	RTS_IEC_HANDLE hAdapter;			/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	SysEthernetFrame *SysEthernetIpFrameReceive;	/* VAR_OUTPUT */	
} sysethernetipframereceive_struct;

DEF_API(`void',`CDECL',`sysethernetipframereceive',`(sysethernetipframereceive_struct *p)',1,0x3794F2CE,0x03050C00)

/**
 * This functions sends an ethernet frame to the local IP Stack for processing.
 * The frame can be safely reused when this function has returned.
 * ..note::
 *   Special function for Ethernet over Ethercat (EoE) 
 */
typedef struct tagsysethernetipframesend_struct
{
	RTS_IEC_HANDLE hAdapter;			/* VAR_INPUT */	
	SysEthernetFrame *pFrame;			/* VAR_INPUT */	
	RTS_IEC_RESULT SysEthernetIpFrameSend;	/* VAR_OUTPUT */	
} sysethernetipframesend_struct;

DEF_API(`void',`CDECL',`sysethernetipframesend',`(sysethernetipframesend_struct *p)',1,0x02F5C5D2,0x03050C00)

/**
 * Set advertised autonegotiation capabilities for an adapter identified by its MAC address.
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsysethernetsetautonegadvertisedcap_struct
{
	RTS_IEC_BYTE macAddress[6];			/* VAR_INPUT */	/* MAC address of the adapter */
	RTS_IEC_ULINT uliAutoNegAdvertisedCap;	/* VAR_INPUT */	/* Advertised autonegotiation capabilities of MAU, see AutoNegCaps constants SYSETH_AUTONEGCAP_... */
	RTS_IEC_RESULT SysEthernetSetAutoNegAdvertisedCap;	/* VAR_OUTPUT */	
} sysethernetsetautonegadvertisedcap_struct;

DEF_API(`void',`CDECL',`sysethernetsetautonegadvertisedcap',`(sysethernetsetautonegadvertisedcap_struct *p)',1,0xBC4E06DB,0x03050C00)

/**
 * Set autonegotiation mode for an adapter identified by its MAC address.
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsysethernetsetautonegmode_struct
{
	RTS_IEC_BYTE macAddress[6];			/* VAR_INPUT */	/* MAC address of the adapter */
	RTS_IEC_USINT usiAutoNegMode;		/* VAR_INPUT */	/* Autonegotiation mode of MAU, see AutoNegMode constants SYSETH_AUTONEGMODE_... */
	RTS_IEC_RESULT SysEthernetSetAutoNegMode;	/* VAR_OUTPUT */	
} sysethernetsetautonegmode_struct;

DEF_API(`void',`CDECL',`sysethernetsetautonegmode',`(sysethernetsetautonegmode_struct *p)',1,0xCDFED6BF,0x03050C00)

/**
 * Set Media Access Unit (MAU) type for an adapter identified by its MAC address.
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsysethernetsetmautype_struct
{
	RTS_IEC_BYTE macAddress[6];			/* VAR_INPUT */	/* MAC address of the adapter */
	RTS_IEC_UDINT udiMauType;			/* VAR_INPUT */	/* Media Access Unit (MAU) type, see MauType constants SYSETH_MAUTYPE_... */
	RTS_IEC_RESULT SysEthernetSetMauType;	/* VAR_OUTPUT */	
} sysethernetsetmautype_struct;

DEF_API(`void',`CDECL',`sysethernetsetmautype',`(sysethernetsetmautype_struct *p)',1,0x06B2A7F6,0x03050C00)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Open and Close Ethernet adapters 
 */
/**
 * <description>Open an ethernet adapter by its MAC address.
 *  Note: Each adapter can only be opened once.
 * </description>
 * <return>Returns a handle to the opened adapter. SysTypes.RTS_INVALID_HANDLE is returned if the operation failed.</return>
 * <param name="pMacAddress" type="IN">Pointer to the MAC address of the adapter to be opened.</param>
 * <param name="macSize" type="IN">Size of the MAC address. This is usually 6 bytes.</param>
 * <param name="pResult" type="OUT">Result of the operation. On of ERR_FAILED or ERR_OK</param>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`SysEthernetAdapterOpen',`(RTS_UI8* pMacAddress, RTS_SIZE macSize, RTS_RESULT* pResult)')

/**
 * <description>Close an ethernet adapter.</description>
 * <return>Result of the operation. ERR_INVALID_HANDLE if the handle was invalid. ERR_OK if operation was successful.</return>
 * <param name="hAdapter" type="IN">Adapter to close.</param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysEthernetAdapterClose',`(RTS_HANDLE hAdapter)')

/*
 * Send and receive data
 */
/**
 * <description>Send an ethernet frame to the adapter. The data of the frame is copied to the adapter. When this function
 * returns the frame can be overwritten without any problems.
 * <return>Result of the operation. ERR_OK if successful. ERR_INVALID_HANDLE if the handle was invalid.</return>
 * <param name="hAdapter" type="IN">Adapter where to send the frame.</param>
 * <param name="pFrame" type="IN">Pointer to frame to send.</param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysEthernetEthFrameSend',`(RTS_HANDLE hAdapter, SysEthernetFrame* pFrame)')

/**
 * <description>Receive an ethernet frame for the ethernet adapter.
 * Note: 
 *   The frame returned has to be released using the SysEthernetEthFrameRelease() function.
 *   The frame will only be overwritten if the frame is released. As frames are reused when
 *   released pay attention to call this function if processing of the frame has finished.</description>
 * <return>Pointer to the received frame. NULL if failed.</return>
 * <param name="hAdapter" type="IN">Adapter where to receive.</param>
 * <param name="pResult" type="OUT">Result of the operation.</param>
 */
DEF_ITF_API(`SysEthernetFrame*',`CDECL',`SysEthernetEthFrameReceive',`(RTS_HANDLE hAdapter, RTS_RESULT* pResult)')

/*
 * Functions for Ethernet over Ethercat (EoE)
 */
/**
 * <description>This functions sends an ethernet frame to the local IP Stack for processing.
 * The frame can be safely reused when this function has returned.
 * Note: Special function for Ethernet over Ethercat (EoE)</description>
 * <return>Pointer to the received frame. NULL if failed.</return>
 * <param name="hAdapter" type="IN">Adapter where to send the IP Frame.</param>
 * <param name="pResult" type="OUT">Result of the operation.</param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysEthernetIpFrameSend',`(RTS_HANDLE hAdapter, SysEthernetFrame* pFrame)')

/**
 * <description>This function receives an IP frame from the systems IP Stack.
 * This frame has to be packed into an Ethercat frame and sent to
 * this adapter.
 * Note: Special function for Ethernet over Ethercat (EoE) </description>
 * <return>Pointer to the received frame. NULL if failed.</return>
 * <param name="hAdapter" type="IN">Adapter where to receive the IP Frame.</param>
 * <param name="pResult" type="OUT">Result of the operation.</param>
 */
DEF_ITF_API(`SysEthernetFrame*',`CDECL',`SysEthernetIpFrameReceive',`(RTS_HANDLE hAdapter, RTS_RESULT* pResult)')

/*
 * Helper functions
 */
 /**
 * <description>Release a received frame to indicate that the frame can be reused.</description>
 * <param name="pFrame" type="IN">Pointer to the frame to release</param>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysEthernetFrameRelease',`(SysEthernetFrame* pFrame)')


/*
* Functions for accessing the MAU type etc.
*/

#define SYSETH_CONFIG_AND_STATUS_STRUCT_VERSION		1	/* version number of structure, to be increased on changes */

/**
* <description>Get ethernet port configuration and status of an adapter identified by its MAC address.</description>
* <param name="pMacAddress" type="IN">Pointer to the MAC address of the adapter to get information from.</param>
* <param name="macSize" type="IN">Size of the MAC address. This is usually 6 bytes.</param>
* <param name="pPortConfigAndStatus" type="IN">Structure to be filled with the configuration and status data. The struct element udiStructSize must contain a valid size for the struct.</param>
* <result>Runtime system error code</result>
* <errorcode name="RTS_RESULT" type="ERR_OK">Information is available</errorcode>
* <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Paramter error</errorcode>
* <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No adapter with the provided MAC address could be found</errorcode>
* <errorcode name="RTS_RESULT" type="ERR_FAILED">Generic error, typically occured in lower layer</errorcode>
* <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Function is not implemented/errorcode>
*/
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysEthernetGetPortConfigAndStatus',`(RTS_UI8* pMacAddress, RTS_SIZE macSize, SysEthernetPortConfigAndStatus* pPortConfigAndStatus)')

/**
* <description>Set advertised autonegotiation capabilities for an adapter identified by its MAC address.</description>
* <param name="pMacAddress" type="IN">Pointer to the MAC address of the adapter.</param>
* <param name="macSize" type="IN">Size of the MAC address. This is usually 6 bytes.</param>
* <param name="ui64AutoNegAdvertisedCap" type="IN">Advertised autonegotiation capabilities of MAU, see AutoNegCaps constants SYSETH_AUTONEGCAP_...</param>
* <result>Runtime system error code</result>
*/
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysEthernetSetAutoNegAdvertisedCap',`(RTS_UI8* pMacAddress, RTS_SIZE macSize, RTS_UI64 ui64AutoNegAdvertisedCap)')

/**
* <description>Set autonegotiation mode for an adapter identified by its MAC address.</description>
* <param name="pMacAddress" type="IN">Pointer to the MAC address of the adapter.</param>
* <param name="macSize" type="IN">Size of the MAC address. This is usually 6 bytes.</param>
* <param name="ui8AutoNegMode" type="IN">Autonegotiation mode of MAU, see AutoNegMode constants SYSETH_AUTONEGMODE_...</param>
* <result>Runtime system error code</result>
*/
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysEthernetSetAutoNegMode',`(RTS_UI8* pMacAddress, RTS_SIZE macSize, RTS_UI8 ui8AutoNegMode)')

/**
* <description>Set Media Access Unit (MAU) type for an adapter identified by its MAC address.</description>
* <param name="pMacAddress" type="IN">Pointer to the MAC address of the adapter.</param>
* <param name="macSize" type="IN">Size of the MAC address. This is usually 6 bytes.</param>
* <param name="ui32MauType" type="IN">Media Access Unit (MAU) type, see MauType constants SYSETH_MAUTYPE_...</param>
* <result>Runtime system error code</result>
*/
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysEthernetSetMauType',`(RTS_UI8* pMacAddress, RTS_SIZE macSize, RTS_UI32 ui32MauType)')


#ifdef __cplusplus
}
#endif


