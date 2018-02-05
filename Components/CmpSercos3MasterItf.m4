/**
 * <interfacename>CmpSercos3Master</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`CmpSercos3Master')

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>csmd_calculatetiming_func</description>
 */
typedef struct tagcsmd_calculatetiming_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_WORD wTimingMethod;			/* VAR_INPUT */	
	RTS_IEC_WORD wIPChannelBandwidth;	/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_CalculateTiming_Func;	/* VAR_OUTPUT */	
} csmd_calculatetiming_func_struct;

DEF_API(`void',`CDECL',`csmd_calculatetiming_func',`(csmd_calculatetiming_func_struct *p)',1,0x66F3AB88,0x03050600)

/**
 * <description>csmd_checkint_func</description>
 */
typedef struct tagcsmd_checkint_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_DWORD *pulInt;				/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_CheckInt_Func;	/* VAR_OUTPUT */	
} csmd_checkint_func_struct;

DEF_API(`void',`CDECL',`csmd_checkint_func',`(csmd_checkint_func_struct *p)',1,0x37960093,0x03050600)

/**
 * <description>csmd_checksvchbusy_func</description>
 */
typedef struct tagcsmd_checksvchbusy_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchData;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_CheckSVCHBusy_Func;	/* VAR_OUTPUT */	
} csmd_checksvchbusy_func_struct;

DEF_API(`void',`CDECL',`csmd_checksvchbusy_func',`(csmd_checksvchbusy_func_struct *p)',1,0xB3E14239,0x03050600)

/**
 * <description>csmd_checkversion_func</description>
 */
typedef struct tagcsmd_checkversion_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prFuncState;			/* VAR_INPUT */	
	RTS_IEC_BYTE *parSvcMacro;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_CheckVersion_Func;	/* VAR_OUTPUT */	
} csmd_checkversion_func_struct;

DEF_API(`void',`CDECL',`csmd_checkversion_func',`(csmd_checkversion_func_struct *p)',1,0x761ECE64,0x03050600)

/**
 * <description>csmd_clearcommand_func</description>
 */
typedef struct tagcsmd_clearcommand_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchData;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_ClearCommand_Func;	/* VAR_OUTPUT */	
} csmd_clearcommand_func_struct;

DEF_API(`void',`CDECL',`csmd_clearcommand_func',`(csmd_clearcommand_func_struct *p)',1,0xCFB8C080,0x03050600)

/**
 * <description>csmd_clearint_func</description>
 */
typedef struct tagcsmd_clearint_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_DWORD ulIntClearMask;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_ClearInt_Func;	/* VAR_OUTPUT */	
} csmd_clearint_func_struct;

DEF_API(`void',`CDECL',`csmd_clearint_func',`(csmd_clearint_func_struct *p)',1,0xCBAF09F0,0x03050600)

/**
 * <description>csmd_enable_cycclk_input_func</description>
 */
typedef struct tagcsmd_enable_cycclk_input_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BOOL bEnable;				/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_Enable_CYCCLK_Input_Func;	/* VAR_OUTPUT */	
} csmd_enable_cycclk_input_func_struct;

DEF_API(`void',`CDECL',`csmd_enable_cycclk_input_func',`(csmd_enable_cycclk_input_func_struct *p)',1,0x845313A4,0x03050600)

/**
 * <description>csmd_eventcontrol_func</description>
 */
typedef struct tagcsmd_eventcontrol_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_WORD wEventID;				/* VAR_INPUT */	
	RTS_IEC_BOOL bActivate;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwEvent_TCNT_Value;	/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_EventControl_Func;	/* VAR_OUTPUT */	
} csmd_eventcontrol_func_struct;

DEF_API(`void',`CDECL',`csmd_eventcontrol_func',`(csmd_eventcontrol_func_struct *p)',1,0xA88254A8,0x03050600)

/**
 * <description>csmd_getattribute_func</description>
 */
typedef struct tagcsmd_getattribute_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchMngmtData;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_GetAttribute_Func;	/* VAR_OUTPUT */	
} csmd_getattribute_func_struct;

DEF_API(`void',`CDECL',`csmd_getattribute_func',`(csmd_getattribute_func_struct *p)',1,0x0D98F820,0x03050600)

/**
 * <description>csmd_getdata_func</description>
 */
typedef struct tagcsmd_getdata_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchMngmtData;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_GetData_Func;	/* VAR_OUTPUT */	
} csmd_getdata_func_struct;

DEF_API(`void',`CDECL',`csmd_getdata_func',`(csmd_getdata_func_struct *p)',1,0xAB0E8CF8,0x03050600)

/**
 * <description>csmd_getdatastatus_func</description>
 */
typedef struct tagcsmd_getdatastatus_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchMngmtData;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_GetDataStatus_Func;	/* VAR_OUTPUT */	
} csmd_getdatastatus_func_struct;

DEF_API(`void',`CDECL',`csmd_getdatastatus_func',`(csmd_getdatastatus_func_struct *p)',1,0x345C3E5B,0x03050600)

/**
 * <description>csmd_getlistlength_func</description>
 */
typedef struct tagcsmd_getlistlength_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchMngmtData;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_GetListLength_Func;	/* VAR_OUTPUT */	
} csmd_getlistlength_func_struct;

DEF_API(`void',`CDECL',`csmd_getlistlength_func',`(csmd_getlistlength_func_struct *p)',1,0xB561D934,0x03050600)

/**
 * <description>csmd_getmax_func</description>
 */
typedef struct tagcsmd_getmax_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchMngmtData;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_GetMax_Func;		/* VAR_OUTPUT */	
} csmd_getmax_func_struct;

DEF_API(`void',`CDECL',`csmd_getmax_func',`(csmd_getmax_func_struct *p)',1,0x19415CB4,0x03050600)

/**
 * <description>csmd_getmin_func</description>
 */
typedef struct tagcsmd_getmin_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchMngmtData;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_GetMin_Func;		/* VAR_OUTPUT */	
} csmd_getmin_func_struct;

DEF_API(`void',`CDECL',`csmd_getmin_func',`(csmd_getmin_func_struct *p)',1,0xFA45F9C2,0x03050600)

/**
 * <description>csmd_getname_func</description>
 */
typedef struct tagcsmd_getname_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchMngmtData;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_GetName_Func;	/* VAR_OUTPUT */	
} csmd_getname_func_struct;

DEF_API(`void',`CDECL',`csmd_getname_func',`(csmd_getname_func_struct *p)',1,0x76A643D5,0x03050600)

/**
 * <description>csmd_getphase_func</description>
 */
typedef struct tagcsmd_getphase_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_WORD *pwPhase;				/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_GetPhase_Func;	/* VAR_OUTPUT */	
} csmd_getphase_func_struct;

DEF_API(`void',`CDECL',`csmd_getphase_func',`(csmd_getphase_func_struct *p)',1,0x37A96B4E,0x03050600)

/**
 * <description>csmd_gettimingdata_func</description>
 */
typedef struct tagcsmd_gettimingdata_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prFuncState;			/* VAR_INPUT */	
	RTS_IEC_BYTE *parSvcMacro;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_GetTimingData_Func;	/* VAR_OUTPUT */	
} csmd_gettimingdata_func_struct;

DEF_API(`void',`CDECL',`csmd_gettimingdata_func',`(csmd_gettimingdata_func_struct *p)',1,0x9C4DBC7F,0x03050600)

/**
 * <description>csmd_gettopology_func</description>
 */
typedef struct tagcsmd_gettopology_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prFuncState;			/* VAR_INPUT */	
	RTS_IEC_WORD wTopology;				/* VAR_INPUT */	
	RTS_IEC_BYTE *parSvcMacro;			/* VAR_INPUT */	
	RTS_IEC_WORD *pwDev_P1;				/* VAR_INPUT */	
	RTS_IEC_WORD *pwDev_P2;				/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_GetTopology_Func;	/* VAR_OUTPUT */	
} csmd_gettopology_func_struct;

DEF_API(`void',`CDECL',`csmd_gettopology_func',`(csmd_gettopology_func_struct *p)',1,0xCC7ABCD2,0x03050600)

/**
 * <description>csmd_getunit_func</description>
 */
typedef struct tagcsmd_getunit_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchMngmtData;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_GetUnit_Func;	/* VAR_OUTPUT */	
} csmd_getunit_func_struct;

DEF_API(`void',`CDECL',`csmd_getunit_func',`(csmd_getunit_func_struct *p)',1,0x70BD674C,0x03050600)

/**
 * <description>csmd_identifyslave_func</description>
 */
typedef struct tagcsmd_identifyslave_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_WORD wDevIdx;				/* VAR_INPUT */	
	RTS_IEC_BYTE bActivated;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_IdentifySlave_Func;	/* VAR_OUTPUT */	
} csmd_identifyslave_func_struct;

DEF_API(`void',`CDECL',`csmd_identifyslave_func',`(csmd_identifyslave_func_struct *p)',1,0x97737054,0x03050600)

/**
 * <description>csmd_inithardware_func</description>
 */
typedef struct tagcsmd_inithardware_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prFuncState;			/* VAR_INPUT */	
	RTS_IEC_BYTE *prHW_Init_Struct;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_InitHardware_Func;	/* VAR_OUTPUT */	
} csmd_inithardware_func_struct;

DEF_API(`void',`CDECL',`csmd_inithardware_func',`(csmd_inithardware_func_struct *p)',1,0x52A33D5D,0x03050600)

/**
 * <description>csmd_initialize_func</description>
 */
typedef struct tagcsmd_initialize_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_DWORD *prSERCOS_Register;	/* VAR_INPUT */	
	RTS_IEC_DWORD *prSERCOS_SVC_Ram;	/* VAR_INPUT */	
	RTS_IEC_DWORD *prSERCOS_TX_Ram;		/* VAR_INPUT */	
	RTS_IEC_DWORD *prSERCOS_RX_Ram;		/* VAR_INPUT */	
	RTS_IEC_DWORD *prSERCOS_IP_TX_Ram;	/* VAR_INPUT */	
	RTS_IEC_DWORD *prSERCOS_IP_RX_Ram;	/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_Initialize_Func;	/* VAR_OUTPUT */	
} csmd_initialize_func_struct;

DEF_API(`void',`CDECL',`csmd_initialize_func',`(csmd_initialize_func_struct *p)',1,0xA5BC5EA3,0x03050600)

/**
 * <description>csmd_intcontrol_func</description>
 */
typedef struct tagcsmd_intcontrol_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_DWORD dwIntEnable;			/* VAR_INPUT */	
	RTS_IEC_DWORD dwIntOutputMask;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_IntControl_Func;	/* VAR_OUTPUT */	
} csmd_intcontrol_func_struct;

DEF_API(`void',`CDECL',`csmd_intcontrol_func',`(csmd_intcontrol_func_struct *p)',1,0x0B2DB2CF,0x03050600)

/**
 * <description>csmd_openidn_func</description>
 */
typedef struct tagcsmd_openidn_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchMngmtData;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_OpenIDN_Func;	/* VAR_OUTPUT */	
} csmd_openidn_func_struct;

DEF_API(`void',`CDECL',`csmd_openidn_func',`(csmd_openidn_func_struct *p)',1,0x71DDA747,0x03050600)

/**
 * <description>csmd_preparecycclk_func</description>
 */
typedef struct tagcsmd_preparecycclk_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BOOL bActivate;				/* VAR_INPUT */	
	RTS_IEC_BOOL bEnableInput;			/* VAR_INPUT */	
	RTS_IEC_BOOL bPolarity;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwStartDelay;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_PrepareCYCCLK_Func;	/* VAR_OUTPUT */	
} csmd_preparecycclk_func_struct;

DEF_API(`void',`CDECL',`csmd_preparecycclk_func',`(csmd_preparecycclk_func_struct *p)',1,0x4B021723,0x03050600)

/**
 * <description>csmd_putdata_func</description>
 */
typedef struct tagcsmd_putdata_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchMngmtData;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_PutData_Func;	/* VAR_OUTPUT */	
} csmd_putdata_func_struct;

DEF_API(`void',`CDECL',`csmd_putdata_func',`(csmd_putdata_func_struct *p)',1,0xB64BD3C0,0x03050600)

/**
 * <description>csmd_readat_func</description>
 */
typedef struct tagcsmd_readat_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prATDestination;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_ReadAT_Func;		/* VAR_OUTPUT */	
} csmd_readat_func_struct;

DEF_API(`void',`CDECL',`csmd_readat_func',`(csmd_readat_func_struct *p)',1,0x929B64F4,0x03050600)

/**
 * <description>csmd_readcmdstatus_func</description>
 */
typedef struct tagcsmd_readcmdstatus_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchData;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_ReadCmdStatus_Func;	/* VAR_OUTPUT */	
} csmd_readcmdstatus_func_struct;

DEF_API(`void',`CDECL',`csmd_readcmdstatus_func',`(csmd_readcmdstatus_func_struct *p)',1,0x3970DE22,0x03050600)

/**
 * <description>csmd_readsvch_func</description>
 */
typedef struct tagcsmd_readsvch_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchData;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_ReadSVCH_Func;	/* VAR_OUTPUT */	
} csmd_readsvch_func_struct;

DEF_API(`void',`CDECL',`csmd_readsvch_func',`(csmd_readsvch_func_struct *p)',1,0x7DD3BEAC,0x03050600)

/**
 * <description>csmd_recoverringtopology_func</description>
 */
typedef struct tagcsmd_recoverringtopology_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prFuncState;			/* VAR_INPUT */	
	RTS_IEC_BYTE *parSvcMacro;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_RecoverRingTopology_Func;	/* VAR_OUTPUT */	
} csmd_recoverringtopology_func_struct;

DEF_API(`void',`CDECL',`csmd_recoverringtopology_func',`(csmd_recoverringtopology_func_struct *p)',1,0xFBAAF5C6,0x03050600)

/**
 * <description>csmd_resethardware_func</description>
 */
typedef struct tagcsmd_resethardware_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_ResetHardware_Func;	/* VAR_OUTPUT */	
} csmd_resethardware_func_struct;

DEF_API(`void',`CDECL',`csmd_resethardware_func',`(csmd_resethardware_func_struct *p)',1,0xE447FB79,0x03050600)

/**
 * <description>csmd_resetsvch_func</description>
 */
typedef struct tagcsmd_resetsvch_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_WORD wDevIdx;				/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_ResetSVCH_Func;	/* VAR_OUTPUT */	
} csmd_resetsvch_func_struct;

DEF_API(`void',`CDECL',`csmd_resetsvch_func',`(csmd_resetsvch_func_struct *p)',1,0x75C61AB7,0x03050600)

/**
 * <description>csmd_set_nrt_mode_func</description>
 */
typedef struct tagcsmd_set_nrt_mode_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prHW_Init_Struct;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_Set_NRT_Mode_Func;	/* VAR_OUTPUT */	
} csmd_set_nrt_mode_func_struct;

DEF_API(`void',`CDECL',`csmd_set_nrt_mode_func',`(csmd_set_nrt_mode_func_struct *p)',1,0x31E74A3D,0x03050600)

/**
 * <description>csmd_setcommand_func</description>
 */
typedef struct tagcsmd_setcommand_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchData;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_SetCommand_Func;	/* VAR_OUTPUT */	
} csmd_setcommand_func_struct;

DEF_API(`void',`CDECL',`csmd_setcommand_func',`(csmd_setcommand_func_struct *p)',1,0xB09682A5,0x03050600)

/**
 * <description>csmd_setcommparam_func</description>
 */
typedef struct tagcsmd_setcommparam_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prHW_Init_Struct;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_SetCommParam_Func;	/* VAR_OUTPUT */	
} csmd_setcommparam_func_struct;

DEF_API(`void',`CDECL',`csmd_setcommparam_func',`(csmd_setcommparam_func_struct *p)',1,0x66EEDBA0,0x03050600)

/**
 * <description>csmd_setphase0_func</description>
 */
typedef struct tagcsmd_setphase0_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prFuncState;			/* VAR_INPUT */	
	RTS_IEC_WORD **pwRecognizedDeviceList;	/* VAR_INPUT */	
	RTS_IEC_WORD eComVersion;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_SetPhase0_Func;	/* VAR_OUTPUT */	
} csmd_setphase0_func_struct;

DEF_API(`void',`CDECL',`csmd_setphase0_func',`(csmd_setphase0_func_struct *p)',1,0x63660DD2,0x03050600)

/**
 * <description>csmd_setphase1_func</description>
 */
typedef struct tagcsmd_setphase1_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prFuncState;			/* VAR_INPUT */	
	RTS_IEC_WORD *pusOperableDeviceList;	/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_SetPhase1_Func;	/* VAR_OUTPUT */	
} csmd_setphase1_func_struct;

DEF_API(`void',`CDECL',`csmd_setphase1_func',`(csmd_setphase1_func_struct *p)',1,0xE87B4786,0x03050600)

/**
 * <description>csmd_setphase2_func</description>
 */
typedef struct tagcsmd_setphase2_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prFuncState;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_SetPhase2_Func;	/* VAR_OUTPUT */	
} csmd_setphase2_func_struct;

DEF_API(`void',`CDECL',`csmd_setphase2_func',`(csmd_setphase2_func_struct *p)',1,0xC968421B,0x03050600)

/**
 * <description>csmd_setphase3_func</description>
 */
typedef struct tagcsmd_setphase3_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prFuncState;			/* VAR_INPUT */	
	RTS_IEC_BYTE *parSvcMacro;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_SetPhase3_Func;	/* VAR_OUTPUT */	
} csmd_setphase3_func_struct;

DEF_API(`void',`CDECL',`csmd_setphase3_func',`(csmd_setphase3_func_struct *p)',1,0x17B4657A,0x03050600)

/**
 * <description>csmd_setphase4_func</description>
 */
typedef struct tagcsmd_setphase4_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prFuncState;			/* VAR_INPUT */	
	RTS_IEC_BYTE *parSvcMacro;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_SetPhase4_Func;	/* VAR_OUTPUT */	
} csmd_setphase4_func_struct;

DEF_API(`void',`CDECL',`csmd_setphase4_func',`(csmd_setphase4_func_struct *p)',1,0xAF666F4D,0x03050600)

/**
 * <description>csmd_transmittiming_func</description>
 */
typedef struct tagcsmd_transmittiming_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prFuncState;			/* VAR_INPUT */	
	RTS_IEC_BYTE *parSvcMacro;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_TransmitTiming_Func;	/* VAR_OUTPUT */	
} csmd_transmittiming_func_struct;

DEF_API(`void',`CDECL',`csmd_transmittiming_func',`(csmd_transmittiming_func_struct *p)',1,0x62B09AE5,0x03050600)

/**
 * <description>csmd_txrxsoftcont_func</description>
 */
typedef struct tagcsmd_txrxsoftcont_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_TxRxSoftCont_Func;	/* VAR_OUTPUT */	
} csmd_txrxsoftcont_func_struct;

DEF_API(`void',`CDECL',`csmd_txrxsoftcont_func',`(csmd_txrxsoftcont_func_struct *p)',1,0x25210353,0x03050600)

/**
 * <description>csmd_writemdt_func</description>
 */
typedef struct tagcsmd_writemdt_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prMDTSource;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_WriteMDT_Func;	/* VAR_OUTPUT */	
} csmd_writemdt_func_struct;

DEF_API(`void',`CDECL',`csmd_writemdt_func',`(csmd_writemdt_func_struct *p)',1,0x2127D1D8,0x03050600)

/**
 * <description>csmd_writesvch_func</description>
 */
typedef struct tagcsmd_writesvch_func_struct
{
	RTS_IEC_BYTE *prCSMD_Instance;		/* VAR_INPUT */	
	RTS_IEC_BYTE *prSvchData;			/* VAR_INPUT */	
	RTS_IEC_DWORD CSMD_WriteSVCH_Func;	/* VAR_OUTPUT */	
} csmd_writesvch_func_struct;

DEF_API(`void',`CDECL',`csmd_writesvch_func',`(csmd_writesvch_func_struct *p)',1,0xB775BE02,0x03050600)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

