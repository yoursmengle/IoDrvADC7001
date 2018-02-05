/**
 * <interfacename>CmpIoDrvDPV1C2Master</interfacename>
 * <description> 
 *	Interface of a profibus IO-driver for the DPV1 Class 2 Master interface.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpIoDrvDPV1C2Master')

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>DPV1_C2_Abort</description>
 */
typedef struct tagDPV1_C2_Abort
{
	RTS_IEC_BOOL bEnable;
	RTS_IEC_BYTE byStationAddress;
	RTS_IEC_BYTE byDummy[2];
	RTS_IEC_UDINT udiConnectID;
	RTS_IEC_UDINT C_Ref;
	RTS_IEC_BYTE abyError[4];
	RTS_IEC_WORD wOpState;
	RTS_IEC_BOOL bOldEnable;
	RTS_IEC_UDINT udiId;
} DPV1_C2_Abort;

/**
 * <description>DPV1_C2_Read</description>
 */
typedef struct tagDPV1_C2_Read
{
	RTS_IEC_BOOL bEnable;
	RTS_IEC_BYTE byStationAddress;
	RTS_IEC_BYTE bySlotNr;
	RTS_IEC_BYTE byIndex;
	RTS_IEC_UDINT udiConnectID;
	RTS_IEC_UDINT C_Ref;
	RTS_IEC_WORD wLen;
	RTS_IEC_BYTE byDummy[2];
	RTS_IEC_BYTE *pBuffer;
	RTS_IEC_BYTE abyError[4];
	RTS_IEC_WORD wOpState;
	RTS_IEC_BOOL bOldEnable;
	RTS_IEC_UDINT udiId;
} DPV1_C2_Read;

/**
 * <description>DPV1_C2_Initiate</description>
 */
typedef struct tagDPV1_C2_Initiate
{
	RTS_IEC_BOOL bEnable;
	RTS_IEC_BYTE byStationAddress;
	RTS_IEC_BYTE byDummy[2];
	RTS_IEC_DWORD dwSendTimeoutMs;
	RTS_IEC_UDINT C_Ref;
	RTS_IEC_BYTE Res_SAP;
	RTS_IEC_WORD wOpState;
	RTS_IEC_BYTE abyError[4];
	RTS_IEC_UDINT udiConnectID;
	RTS_IEC_BOOL bOldEnable;
	RTS_IEC_UDINT udiId;
} DPV1_C2_Initiate;

/**
 * <description>DPV1_C2_Write</description>
 */
typedef struct tagDPV1_C2_Write
{
	RTS_IEC_BOOL bEnable;
	RTS_IEC_BYTE byStationAddress;
	RTS_IEC_BYTE bySlotNr;
	RTS_IEC_BYTE byIndex;
	RTS_IEC_UDINT udiConnectID;
	RTS_IEC_UDINT C_Ref;
	RTS_IEC_WORD wLen;
	RTS_IEC_BYTE byDummy[2];
	RTS_IEC_BYTE *pBuffer;
	RTS_IEC_BYTE abyError[4];
	RTS_IEC_WORD wOpState;
	RTS_IEC_BOOL bOldEnable;
	RTS_IEC_UDINT udiId;
} DPV1_C2_Write;

typedef struct
{
	ieciodrvinstance_struct *pInstance;
	DPV1_C2_Initiate *pInit;
	RTS_IEC_UDINT Result;
} iodrvdpv1_c2_m_initiate_struct;

typedef struct
{
	ieciodrvinstance_struct *pInstance;
	DPV1_C2_Abort *pInit;
	RTS_IEC_UDINT Result;
} iodrvdpv1_c2_m_abort_struct;

typedef struct
{
	ieciodrvinstance_struct *pInstance;
	DPV1_C2_Read *pInit;
	RTS_IEC_UDINT Result;
} iodrvdpv1_c2_m_read_struct;

typedef struct
{
	ieciodrvinstance_struct *pInstance;
	DPV1_C2_Write *pInit;
	RTS_IEC_UDINT Result;
} iodrvdpv1_c2_m_write_struct;

#ifdef __cplusplus
}
#endif

/**
 * <description></description>
 * <result>ERR_OK</result>
 */
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvDPV1_C2_M_Initiate', `(RTS_HANDLE hIoDrv, DPV1_C2_Initiate *pInit)')
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvDPV1_C2_M_Abort', `(RTS_HANDLE hIoDrv, DPV1_C2_Abort *pAbort)')
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvDPV1_C2_M_Read', `(RTS_HANDLE hIoDrv, DPV1_C2_Read *pRead)')
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvDPV1_C2_M_Write', `(RTS_HANDLE hIoDrv, DPV1_C2_Write *pWrite)')

