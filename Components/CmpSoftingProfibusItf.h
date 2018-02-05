 /**
 * <interfacename>CmpSoftingProfibus</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _CMPSOFTINGPROFIBUSITF_H_
#define _CMPSOFTINGPROFIBUSITF_H_

#include "CmpStd.h"

 

 




/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>SOFTING_T_DP_INIT_MASTER_CON</description>
 */
typedef struct tagSOFTING_T_DP_INIT_MASTER_CON
{
	RTS_IEC_UINT status;
} SOFTING_T_DP_INIT_MASTER_CON;

/**
 * <description>SOFTING_T_DP_EXIT_MASTER_CON</description>
 */
typedef struct tagSOFTING_T_DP_EXIT_MASTER_CON
{
	RTS_IEC_UINT status;
} SOFTING_T_DP_EXIT_MASTER_CON;

/**
 * <description>SOFTING_T_DP_SLAVE_USER_DATA</description>
 */
typedef struct tagSOFTING_T_DP_SLAVE_USER_DATA
{
	RTS_IEC_UINT slave_user_data_len;
	RTS_IEC_BYTE slave_user_data[100];
} SOFTING_T_DP_SLAVE_USER_DATA;

/**
 * <description>SOFTING_T_DP_UPLOAD_RES_CON</description>
 */
typedef struct tagSOFTING_T_DP_UPLOAD_RES_CON
{
	RTS_IEC_UINT status;
	RTS_IEC_UINT data_len;
} SOFTING_T_DP_UPLOAD_RES_CON;

/**
 * <description>SOFTING_T_DP_SET_BUSPARAMETER_CON</description>
 */
typedef struct tagSOFTING_T_DP_SET_BUSPARAMETER_CON
{
	RTS_IEC_UINT status;
} SOFTING_T_DP_SET_BUSPARAMETER_CON;

/**
 * <description>SOFTING_T_FMB_CONFIG_CRL</description>
 */
typedef struct tagSOFTING_T_FMB_CONFIG_CRL
{
	RTS_IEC_UINT max_no_fal_sdbs;
	RTS_IEC_UINT max_no_fdl_sdbs;
	RTS_IEC_UINT max_no_data_buffer;
	RTS_IEC_UINT max_no_api_buffer;
	RTS_IEC_UINT max_no_poll_entries;
	RTS_IEC_UINT max_no_subscr_entries;
	RTS_IEC_USINT resrc_check;
	RTS_IEC_USINT max_no_parallel_req;
	RTS_IEC_USINT max_no_parallel_ind;
	RTS_IEC_USINT dummy;
} SOFTING_T_FMB_CONFIG_CRL;

/**
 * <description>SOFTING_T_DP_SET_PRM_CON</description>
 */
typedef struct tagSOFTING_T_DP_SET_PRM_CON
{
	RTS_IEC_UINT status;
} SOFTING_T_DP_SET_PRM_CON;

/**
 * <description>SOFTING_T_DP_SET_BUSPARAMETER_REQ</description>
 */
typedef struct tagSOFTING_T_DP_SET_BUSPARAMETER_REQ
{
	RTS_IEC_USINT bf_flag;
	RTS_IEC_USINT dummy;
	RTS_IEC_UINT min_slave_interval;
	RTS_IEC_UINT poll_timeout;
	RTS_IEC_UINT data_control_time;
	RTS_IEC_UINT master_user_data_len;
	RTS_IEC_STRING master_class2_name[32];
} SOFTING_T_DP_SET_BUSPARAMETER_REQ;

/**
 * <description>SOFTING_T_DP_GET_MASTER_DIAG_REQ</description>
 */
typedef struct tagSOFTING_T_DP_GET_MASTER_DIAG_REQ
{
	RTS_IEC_USINT rem_add;
	RTS_IEC_USINT identifier;
} SOFTING_T_DP_GET_MASTER_DIAG_REQ;

/**
 * <description>SOFTING_T_DP_ACT_PARAM_REQ</description>
 */
typedef struct tagSOFTING_T_DP_ACT_PARAM_REQ
{
	RTS_IEC_USINT rem_add;
	RTS_IEC_USINT area_code;
	RTS_IEC_USINT activate;
	RTS_IEC_USINT dummy;
} SOFTING_T_DP_ACT_PARAM_REQ;

/**
 * <description>SOFTING_T_DP_DATA_TRANSFER_CON</description>
 */
typedef struct tagSOFTING_T_DP_DATA_TRANSFER_CON
{
	RTS_IEC_UINT status;
	RTS_IEC_INT diag_entries;
} SOFTING_T_DP_DATA_TRANSFER_CON;

/**
 * <description>SOFTING_T_DP_DIAG_DATA</description>
 */
typedef struct tagSOFTING_T_DP_DIAG_DATA
{
	RTS_IEC_USINT station_status_1;
	RTS_IEC_USINT station_status_2;
	RTS_IEC_USINT station_status_3;
	RTS_IEC_USINT master_add;
	RTS_IEC_UINT ident_number;
} SOFTING_T_DP_DIAG_DATA;

/**
 * <description>SOFTING_T_DP_GET_SLAVE_DIAG_IND</description>
 */
typedef struct tagSOFTING_T_DP_GET_SLAVE_DIAG_IND
{
	RTS_IEC_UINT status;
	RTS_IEC_USINT rem_add;
	RTS_IEC_USINT dummy;
	RTS_IEC_INT diag_entries;
	RTS_IEC_UINT diag_data_len;
	SOFTING_T_DP_DIAG_DATA diag_data;
} SOFTING_T_DP_GET_SLAVE_DIAG_IND;

/**
 * <description>SOFTING_T_DP_DOWNLOAD_RES_CON</description>
 */
typedef struct tagSOFTING_T_DP_DOWNLOAD_RES_CON
{
	RTS_IEC_UINT status;
} SOFTING_T_DP_DOWNLOAD_RES_CON;

/**
 * <description>SOFTING_T_FMB_CONFIG_VFD</description>
 */
typedef struct tagSOFTING_T_FMB_CONFIG_VFD
{
	RTS_IEC_UINT max_no_vfds;
	RTS_IEC_UINT max_no_obj_descr;
	RTS_IEC_USINT max_obj_name_length;
	RTS_IEC_USINT max_obj_ext_length;
} SOFTING_T_FMB_CONFIG_VFD;

/**
 * <description>SOFTING_T_FMB_CONFIG_DP</description>
 */
typedef struct tagSOFTING_T_FMB_CONFIG_DP
{
	RTS_IEC_USINT max_number_slaves;
	RTS_IEC_USINT max_slave_output_len;
	RTS_IEC_USINT max_slave_input_len;
	RTS_IEC_USINT max_slave_diag_len;
	RTS_IEC_UINT max_slave_diag_entries;
	RTS_IEC_UINT max_bus_para_len;
	RTS_IEC_UINT max_slave_para_len;
} SOFTING_T_FMB_CONFIG_DP;

/**
 * <description>SOFTING_T_DP_START_SEQ_IND</description>
 */
typedef struct tagSOFTING_T_DP_START_SEQ_IND
{
	RTS_IEC_USINT rem_add;
	RTS_IEC_USINT area_code;
	RTS_IEC_UINT timeout;
} SOFTING_T_DP_START_SEQ_IND;

/**
 * <description>SOFTING_T_DP_END_SEQ_REQ</description>
 */
typedef struct tagSOFTING_T_DP_END_SEQ_REQ
{
	RTS_IEC_USINT rem_add;
	RTS_IEC_USINT dummy;
} SOFTING_T_DP_END_SEQ_REQ;

/**
 * <description>SOFTING_T_DP_GET_MASTER_DIAG_RES_CON</description>
 */
typedef struct tagSOFTING_T_DP_GET_MASTER_DIAG_RES_CON
{
	RTS_IEC_UINT status;
	RTS_IEC_UINT data_len;
} SOFTING_T_DP_GET_MASTER_DIAG_RES_CON;

/**
 * <description>SOFTING_T_DP_CFG_DATA</description>
 */
typedef struct tagSOFTING_T_DP_CFG_DATA
{
	RTS_IEC_UINT cfg_data_len;
	RTS_IEC_BYTE cfg_data[255];
} SOFTING_T_DP_CFG_DATA;

/**
 * <description>SOFTING_T_FMB_CONFIG_FDLIF</description>
 */
typedef struct tagSOFTING_T_FMB_CONFIG_FDLIF
{
	RTS_IEC_USINT send_req_credits;
	RTS_IEC_USINT srd_req_credits;
	RTS_IEC_USINT receive_credits;
	RTS_IEC_USINT max_no_resp_saps;
} SOFTING_T_FMB_CONFIG_FDLIF;

/**
 * <description>SOFTING_T_DP_ACT_PARAM_RES_CON</description>
 */
typedef struct tagSOFTING_T_DP_ACT_PARAM_RES_CON
{
	RTS_IEC_UINT status;
} SOFTING_T_DP_ACT_PARAM_RES_CON;

/**
 * <description>SOFTING_T_DP_GET_SLAVE_DIAG_CON</description>
 */
typedef struct tagSOFTING_T_DP_GET_SLAVE_DIAG_CON
{
	RTS_IEC_UINT status;
	RTS_IEC_USINT rem_add;
	RTS_IEC_USINT dummy;
	RTS_IEC_INT diag_entries;
	RTS_IEC_UINT diag_data_len;
	SOFTING_T_DP_DIAG_DATA diag_data;
} SOFTING_T_DP_GET_SLAVE_DIAG_CON;

/**
 * <description>SOFTING_T_DP_SLAVE_PARAM_SLAVE_INFO</description>
 */
typedef struct tagSOFTING_T_DP_SLAVE_PARAM_SLAVE_INFO
{
	RTS_IEC_UINT diag_entries;
	RTS_IEC_UINT offset_inputs;
	RTS_IEC_UINT offset_outputs;
	RTS_IEC_USINT number_inputs;
	RTS_IEC_USINT number_outputs;
	RTS_IEC_USINT sl_flag;
	RTS_IEC_USINT slave_type;
} SOFTING_T_DP_SLAVE_PARAM_SLAVE_INFO;

/**
 * <description>SOFTING_T_DP_UPLOAD_REQ</description>
 */
typedef struct tagSOFTING_T_DP_UPLOAD_REQ
{
	RTS_IEC_USINT rem_add;
	RTS_IEC_USINT area_code;
	RTS_IEC_UINT add_offset;
	RTS_IEC_USINT data_len;
	RTS_IEC_USINT dummy;
} SOFTING_T_DP_UPLOAD_REQ;

/**
 * <description>SOFTING_T_DP_INIT_MASTER_REQ</description>
 */
typedef struct tagSOFTING_T_DP_INIT_MASTER_REQ
{
	RTS_IEC_USINT master_default_address;
	RTS_IEC_USINT master_class2;
	RTS_IEC_STRING master_class2_name[32];
	RTS_IEC_USINT lowest_slave_address;
	RTS_IEC_USINT slave_io_address_mode;
	RTS_IEC_USINT clear_outputs;
	RTS_IEC_USINT auto_remote_services;
	RTS_IEC_USINT cyclic_data_transfer;
} SOFTING_T_DP_INIT_MASTER_REQ;

/**
 * <description>SOFTING_T_DP_SLAVE_PARA_SET</description>
 */
typedef struct tagSOFTING_T_DP_SLAVE_PARA_SET
{
	RTS_IEC_UINT slave_para_len;
	RTS_IEC_USINT sl_flag;
	RTS_IEC_USINT slave_type;
	RTS_IEC_USINT reserved[12];
} SOFTING_T_DP_SLAVE_PARA_SET;

/**
 * <description>SOFTING_T_DP_START_SEQ_RES_CON</description>
 */
typedef struct tagSOFTING_T_DP_START_SEQ_RES_CON
{
	RTS_IEC_UINT status;
	RTS_IEC_USINT maxlen_data_unit;
	RTS_IEC_USINT dummy;
} SOFTING_T_DP_START_SEQ_RES_CON;

/**
 * <description>SOFTING_T_DP_SLAVE_PARAM_SYS_INFO</description>
 */
typedef struct tagSOFTING_T_DP_SLAVE_PARAM_SYS_INFO
{
	RTS_IEC_USINT loaded_slaves;
	RTS_IEC_USINT active_slaves;
	RTS_IEC_INT diag_entries;
	RTS_IEC_UINT slave_io_image_len;
} SOFTING_T_DP_SLAVE_PARAM_SYS_INFO;

/**
 * <description>SOFTING_T_FMB_FM2_EVENT_IND</description>
 */
typedef struct tagSOFTING_T_FMB_FM2_EVENT_IND
{
	RTS_IEC_UINT reason;
} SOFTING_T_FMB_FM2_EVENT_IND;

/**
 * <description>SOFTING_T_FMB_CONFIG_SM7</description>
 */
typedef struct tagSOFTING_T_FMB_CONFIG_SM7
{
	RTS_IEC_UINT reserved;
} SOFTING_T_FMB_CONFIG_SM7;

/**
 * <description>SOFTING_T_FMB_SET_CONFIGURATION_REQ</description>
 */
typedef struct tagSOFTING_T_FMB_SET_CONFIGURATION_REQ
{
	RTS_IEC_USINT fms_active;
	RTS_IEC_USINT dp_active;
	RTS_IEC_USINT fdlif_active;
	RTS_IEC_USINT sm7_active;
	RTS_IEC_UINT fdl_evt_receiver;
	RTS_IEC_UINT data_buffer_length;
	SOFTING_T_FMB_CONFIG_VFD vfd;
	SOFTING_T_FMB_CONFIG_CRL crl;
	SOFTING_T_FMB_CONFIG_DP dp;
	SOFTING_T_FMB_CONFIG_FDLIF fdlif;
	SOFTING_T_FMB_CONFIG_SM7 sm7;
} SOFTING_T_FMB_SET_CONFIGURATION_REQ;

/**
 * <description>SOFTING_T_PROFI_SERVICE_DESCR</description>
 */
typedef struct tagSOFTING_T_PROFI_SERVICE_DESCR
{
	RTS_IEC_UINT comm_ref;
	RTS_IEC_USINT layer;
	RTS_IEC_USINT service;
	RTS_IEC_USINT primitive;
	RTS_IEC_SINT invoke_id;
	RTS_IEC_INT result;
} SOFTING_T_PROFI_SERVICE_DESCR;

/**
 * <description>SOFTING_T_DP_PRM_DATA</description>
 */
typedef struct tagSOFTING_T_DP_PRM_DATA
{
	RTS_IEC_UINT prm_data_len;
	RTS_IEC_USINT station_status;
	RTS_IEC_USINT wd_fact_1;
	RTS_IEC_USINT wd_fact_2;
	RTS_IEC_USINT min_tsdr;
	RTS_IEC_UINT ident_number;
	RTS_IEC_USINT group_ident;
	RTS_IEC_BYTE user_prm_data[242];
} SOFTING_T_DP_PRM_DATA;

/**
 * <description>SOFTING_T_DP_SET_PRM_REQ</description>
 */
typedef struct tagSOFTING_T_DP_SET_PRM_REQ
{
	RTS_IEC_USINT rem_add;
	RTS_IEC_USINT dummy;
	SOFTING_T_DP_PRM_DATA prm_data;
} SOFTING_T_DP_SET_PRM_REQ;

/**
 * <description>SOFTING_T_DP_DOWNLOAD_REQ</description>
 */
typedef struct tagSOFTING_T_DP_DOWNLOAD_REQ
{
	RTS_IEC_UINT data_len;
	RTS_IEC_USINT rem_add;
	RTS_IEC_USINT area_code;
	RTS_IEC_UINT add_offset;
} SOFTING_T_DP_DOWNLOAD_REQ;

/**
 * <description>SOFTING_T_DP_BUS_PARA_SET</description>
 */
typedef struct tagSOFTING_T_DP_BUS_PARA_SET
{
	RTS_IEC_UINT bus_para_len;
	RTS_IEC_USINT fdl_add;
	RTS_IEC_USINT baud_rate;
	RTS_IEC_UINT tsl;
	RTS_IEC_UINT min_tsdr;
	RTS_IEC_UINT max_tsdr;
	RTS_IEC_USINT tqui;
	RTS_IEC_USINT tset;
	RTS_IEC_UINT ttr;
	RTS_IEC_USINT g;
	RTS_IEC_USINT hsa;
	RTS_IEC_USINT max_retry_limit;
	RTS_IEC_USINT bp_flag;
	RTS_IEC_UINT min_slave_interval;
	RTS_IEC_UINT poll_timeout;
	RTS_IEC_UINT data_control_time;
	RTS_IEC_USINT reserved[6];
	RTS_IEC_UINT master_user_data_len;
	RTS_IEC_STRING master_class2_name[32];
} SOFTING_T_DP_BUS_PARA_SET;

/**
 * <description>SOFTING_T_DP_START_SEQ_REQ</description>
 */
typedef struct tagSOFTING_T_DP_START_SEQ_REQ
{
	RTS_IEC_USINT rem_add;
	RTS_IEC_USINT area_code;
	RTS_IEC_UINT timeout;
} SOFTING_T_DP_START_SEQ_REQ;

/**
 * <description>SOFTING_T_DP_END_SEQ_IND</description>
 */
typedef struct tagSOFTING_T_DP_END_SEQ_IND
{
	RTS_IEC_USINT rem_add;
	RTS_IEC_USINT dummy;
} SOFTING_T_DP_END_SEQ_IND;

/**
 * <description>SOFTING_T_DP_END_SEQ_RES_CON</description>
 */
typedef struct tagSOFTING_T_DP_END_SEQ_RES_CON
{
	RTS_IEC_UINT status;
} SOFTING_T_DP_END_SEQ_RES_CON;

/**
 * <description>SOFTING_T_DP_AAT_DATA</description>
 */
typedef struct tagSOFTING_T_DP_AAT_DATA
{
	RTS_IEC_UINT aat_data_len;
	RTS_IEC_USINT number_inputs;
	RTS_IEC_USINT number_outputs;
	RTS_IEC_WORD offset_input_output[244];
} SOFTING_T_DP_AAT_DATA;

/**
 * <description>SOFTING_T_DP_GET_SLAVE_PARAM_CON</description>
 */
typedef struct tagSOFTING_T_DP_GET_SLAVE_PARAM_CON
{
	RTS_IEC_UINT status;
	RTS_IEC_UINT data_len;
} SOFTING_T_DP_GET_SLAVE_PARAM_CON;

/**
 * <description>SOFTING_T_DP_GET_SLAVE_PARAM_REQ</description>
 */
typedef struct tagSOFTING_T_DP_GET_SLAVE_PARAM_REQ
{
	RTS_IEC_USINT identifier;
	RTS_IEC_USINT rem_add;
} SOFTING_T_DP_GET_SLAVE_PARAM_REQ;

/**
 * <description>SOFTING_T_DP_ACT_PARAM_IND</description>
 */
typedef struct tagSOFTING_T_DP_ACT_PARAM_IND
{
	RTS_IEC_USINT rem_add;
	RTS_IEC_USINT area_code;
	RTS_IEC_USINT activate;
	RTS_IEC_USINT dummy;
} SOFTING_T_DP_ACT_PARAM_IND;

/**
 * <description>SOFTING_T_DP_GET_PRM_REQ</description>
 */
typedef struct tagSOFTING_T_DP_GET_PRM_REQ
{
	RTS_IEC_USINT rem_add;
	RTS_IEC_USINT dummy;
	SOFTING_T_DP_PRM_DATA prm_data;
} SOFTING_T_DP_GET_PRM_REQ;

/**
 * <description>SOFTING_T_DP_DOWNLOAD_IND</description>
 */
typedef struct tagSOFTING_T_DP_DOWNLOAD_IND
{
	RTS_IEC_UINT data_len;
	RTS_IEC_USINT rem_add;
	RTS_IEC_USINT area_code;
	RTS_IEC_UINT add_offset;
} SOFTING_T_DP_DOWNLOAD_IND;

/**
 * <description>softing_profi_get_last_errror</description>
 */
typedef struct tagsofting_profi_get_last_errror_struct
{
	RTS_IEC_INT softing_profi_get_last_errror;	/* VAR_OUTPUT */
} softing_profi_get_last_errror_struct;

void CDECL CDECL_EXT softing_profi_get_last_errror(softing_profi_get_last_errror_struct *p);
typedef void (CDECL CDECL_EXT* PFSOFTING_PROFI_GET_LAST_ERRROR_IEC) (softing_profi_get_last_errror_struct *p);
#if defined(CMPSOFTINGPROFIBUS_NOTIMPLEMENTED) || defined(SOFTING_PROFI_GET_LAST_ERRROR_NOTIMPLEMENTED)
	#define USE_softing_profi_get_last_errror
	#define EXT_softing_profi_get_last_errror
	#define GET_softing_profi_get_last_errror(fl)  ERR_NOTIMPLEMENTED
	#define CAL_softing_profi_get_last_errror(p0) 
	#define CHK_softing_profi_get_last_errror  FALSE
	#define EXP_softing_profi_get_last_errror  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_softing_profi_get_last_errror
	#define EXT_softing_profi_get_last_errror
	#define GET_softing_profi_get_last_errror(fl)  CAL_CMGETAPI( "softing_profi_get_last_errror" ) 
	#define CAL_softing_profi_get_last_errror  softing_profi_get_last_errror
	#define CHK_softing_profi_get_last_errror  TRUE
	#define EXP_softing_profi_get_last_errror  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_last_errror", (RTS_UINTPTR)softing_profi_get_last_errror, 1, 0xD6F91F9D, 0x03040414) 
#elif defined(MIXED_LINK) && !defined(CMPSOFTINGPROFIBUS_EXTERNAL)
	#define USE_softing_profi_get_last_errror
	#define EXT_softing_profi_get_last_errror
	#define GET_softing_profi_get_last_errror(fl)  CAL_CMGETAPI( "softing_profi_get_last_errror" ) 
	#define CAL_softing_profi_get_last_errror  softing_profi_get_last_errror
	#define CHK_softing_profi_get_last_errror  TRUE
	#define EXP_softing_profi_get_last_errror  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_last_errror", (RTS_UINTPTR)softing_profi_get_last_errror, 1, 0xD6F91F9D, 0x03040414) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSoftingProfibussofting_profi_get_last_errror
	#define EXT_CmpSoftingProfibussofting_profi_get_last_errror
	#define GET_CmpSoftingProfibussofting_profi_get_last_errror  ERR_OK
	#define CAL_CmpSoftingProfibussofting_profi_get_last_errror  softing_profi_get_last_errror
	#define CHK_CmpSoftingProfibussofting_profi_get_last_errror  TRUE
	#define EXP_CmpSoftingProfibussofting_profi_get_last_errror  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_last_errror", (RTS_UINTPTR)softing_profi_get_last_errror, 1, 0xD6F91F9D, 0x03040414) 
#elif defined(CPLUSPLUS)
	#define USE_softing_profi_get_last_errror
	#define EXT_softing_profi_get_last_errror
	#define GET_softing_profi_get_last_errror(fl)  CAL_CMGETAPI( "softing_profi_get_last_errror" ) 
	#define CAL_softing_profi_get_last_errror  softing_profi_get_last_errror
	#define CHK_softing_profi_get_last_errror  TRUE
	#define EXP_softing_profi_get_last_errror  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_last_errror", (RTS_UINTPTR)softing_profi_get_last_errror, 1, 0xD6F91F9D, 0x03040414) 
#else /* DYNAMIC_LINK */
	#define USE_softing_profi_get_last_errror  PFSOFTING_PROFI_GET_LAST_ERRROR_IEC pfsofting_profi_get_last_errror;
	#define EXT_softing_profi_get_last_errror  extern PFSOFTING_PROFI_GET_LAST_ERRROR_IEC pfsofting_profi_get_last_errror;
	#define GET_softing_profi_get_last_errror(fl)  s_pfCMGetAPI2( "softing_profi_get_last_errror", (RTS_VOID_FCTPTR *)&pfsofting_profi_get_last_errror, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xD6F91F9D, 0x03040414)
	#define CAL_softing_profi_get_last_errror  pfsofting_profi_get_last_errror
	#define CHK_softing_profi_get_last_errror  (pfsofting_profi_get_last_errror != NULL)
	#define EXP_softing_profi_get_last_errror   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_last_errror", (RTS_UINTPTR)softing_profi_get_last_errror, 1, 0xD6F91F9D, 0x03040414) 
#endif


/**
 * <description>softing_profi_get_dps_input_data</description>
 */
typedef struct tagsofting_profi_get_dps_input_data_struct
{
	RTS_IEC_USINT *pData;				/* VAR_INPUT */
	RTS_IEC_USINT *pDataLength;			/* VAR_INPUT */
	RTS_IEC_USINT *pState;				/* VAR_INPUT */
	RTS_IEC_INT softing_profi_get_dps_input_data;	/* VAR_OUTPUT */
} softing_profi_get_dps_input_data_struct;

void CDECL CDECL_EXT softing_profi_get_dps_input_data(softing_profi_get_dps_input_data_struct *p);
typedef void (CDECL CDECL_EXT* PFSOFTING_PROFI_GET_DPS_INPUT_DATA_IEC) (softing_profi_get_dps_input_data_struct *p);
#if defined(CMPSOFTINGPROFIBUS_NOTIMPLEMENTED) || defined(SOFTING_PROFI_GET_DPS_INPUT_DATA_NOTIMPLEMENTED)
	#define USE_softing_profi_get_dps_input_data
	#define EXT_softing_profi_get_dps_input_data
	#define GET_softing_profi_get_dps_input_data(fl)  ERR_NOTIMPLEMENTED
	#define CAL_softing_profi_get_dps_input_data(p0) 
	#define CHK_softing_profi_get_dps_input_data  FALSE
	#define EXP_softing_profi_get_dps_input_data  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_softing_profi_get_dps_input_data
	#define EXT_softing_profi_get_dps_input_data
	#define GET_softing_profi_get_dps_input_data(fl)  CAL_CMGETAPI( "softing_profi_get_dps_input_data" ) 
	#define CAL_softing_profi_get_dps_input_data  softing_profi_get_dps_input_data
	#define CHK_softing_profi_get_dps_input_data  TRUE
	#define EXP_softing_profi_get_dps_input_data  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_dps_input_data", (RTS_UINTPTR)softing_profi_get_dps_input_data, 1, 0xE8323117, 0x03040414) 
#elif defined(MIXED_LINK) && !defined(CMPSOFTINGPROFIBUS_EXTERNAL)
	#define USE_softing_profi_get_dps_input_data
	#define EXT_softing_profi_get_dps_input_data
	#define GET_softing_profi_get_dps_input_data(fl)  CAL_CMGETAPI( "softing_profi_get_dps_input_data" ) 
	#define CAL_softing_profi_get_dps_input_data  softing_profi_get_dps_input_data
	#define CHK_softing_profi_get_dps_input_data  TRUE
	#define EXP_softing_profi_get_dps_input_data  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_dps_input_data", (RTS_UINTPTR)softing_profi_get_dps_input_data, 1, 0xE8323117, 0x03040414) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSoftingProfibussofting_profi_get_dps_input_data
	#define EXT_CmpSoftingProfibussofting_profi_get_dps_input_data
	#define GET_CmpSoftingProfibussofting_profi_get_dps_input_data  ERR_OK
	#define CAL_CmpSoftingProfibussofting_profi_get_dps_input_data  softing_profi_get_dps_input_data
	#define CHK_CmpSoftingProfibussofting_profi_get_dps_input_data  TRUE
	#define EXP_CmpSoftingProfibussofting_profi_get_dps_input_data  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_dps_input_data", (RTS_UINTPTR)softing_profi_get_dps_input_data, 1, 0xE8323117, 0x03040414) 
#elif defined(CPLUSPLUS)
	#define USE_softing_profi_get_dps_input_data
	#define EXT_softing_profi_get_dps_input_data
	#define GET_softing_profi_get_dps_input_data(fl)  CAL_CMGETAPI( "softing_profi_get_dps_input_data" ) 
	#define CAL_softing_profi_get_dps_input_data  softing_profi_get_dps_input_data
	#define CHK_softing_profi_get_dps_input_data  TRUE
	#define EXP_softing_profi_get_dps_input_data  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_dps_input_data", (RTS_UINTPTR)softing_profi_get_dps_input_data, 1, 0xE8323117, 0x03040414) 
#else /* DYNAMIC_LINK */
	#define USE_softing_profi_get_dps_input_data  PFSOFTING_PROFI_GET_DPS_INPUT_DATA_IEC pfsofting_profi_get_dps_input_data;
	#define EXT_softing_profi_get_dps_input_data  extern PFSOFTING_PROFI_GET_DPS_INPUT_DATA_IEC pfsofting_profi_get_dps_input_data;
	#define GET_softing_profi_get_dps_input_data(fl)  s_pfCMGetAPI2( "softing_profi_get_dps_input_data", (RTS_VOID_FCTPTR *)&pfsofting_profi_get_dps_input_data, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xE8323117, 0x03040414)
	#define CAL_softing_profi_get_dps_input_data  pfsofting_profi_get_dps_input_data
	#define CHK_softing_profi_get_dps_input_data  (pfsofting_profi_get_dps_input_data != NULL)
	#define EXP_softing_profi_get_dps_input_data   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_dps_input_data", (RTS_UINTPTR)softing_profi_get_dps_input_data, 1, 0xE8323117, 0x03040414) 
#endif


/**
 * <description>softing_profi_set_data</description>
 */
typedef struct tagsofting_profi_set_data_struct
{
	RTS_IEC_USINT DataId;				/* VAR_INPUT */
	RTS_IEC_UINT Offset;				/* VAR_INPUT */
	RTS_IEC_UINT DataSize;				/* VAR_INPUT */
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */
	RTS_IEC_INT softing_profi_set_data;	/* VAR_OUTPUT */
} softing_profi_set_data_struct;

void CDECL CDECL_EXT softing_profi_set_data(softing_profi_set_data_struct *p);
typedef void (CDECL CDECL_EXT* PFSOFTING_PROFI_SET_DATA_IEC) (softing_profi_set_data_struct *p);
#if defined(CMPSOFTINGPROFIBUS_NOTIMPLEMENTED) || defined(SOFTING_PROFI_SET_DATA_NOTIMPLEMENTED)
	#define USE_softing_profi_set_data
	#define EXT_softing_profi_set_data
	#define GET_softing_profi_set_data(fl)  ERR_NOTIMPLEMENTED
	#define CAL_softing_profi_set_data(p0) 
	#define CHK_softing_profi_set_data  FALSE
	#define EXP_softing_profi_set_data  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_softing_profi_set_data
	#define EXT_softing_profi_set_data
	#define GET_softing_profi_set_data(fl)  CAL_CMGETAPI( "softing_profi_set_data" ) 
	#define CAL_softing_profi_set_data  softing_profi_set_data
	#define CHK_softing_profi_set_data  TRUE
	#define EXP_softing_profi_set_data  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_set_data", (RTS_UINTPTR)softing_profi_set_data, 1, 0xEACB0540, 0x03040414) 
#elif defined(MIXED_LINK) && !defined(CMPSOFTINGPROFIBUS_EXTERNAL)
	#define USE_softing_profi_set_data
	#define EXT_softing_profi_set_data
	#define GET_softing_profi_set_data(fl)  CAL_CMGETAPI( "softing_profi_set_data" ) 
	#define CAL_softing_profi_set_data  softing_profi_set_data
	#define CHK_softing_profi_set_data  TRUE
	#define EXP_softing_profi_set_data  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_set_data", (RTS_UINTPTR)softing_profi_set_data, 1, 0xEACB0540, 0x03040414) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSoftingProfibussofting_profi_set_data
	#define EXT_CmpSoftingProfibussofting_profi_set_data
	#define GET_CmpSoftingProfibussofting_profi_set_data  ERR_OK
	#define CAL_CmpSoftingProfibussofting_profi_set_data  softing_profi_set_data
	#define CHK_CmpSoftingProfibussofting_profi_set_data  TRUE
	#define EXP_CmpSoftingProfibussofting_profi_set_data  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_set_data", (RTS_UINTPTR)softing_profi_set_data, 1, 0xEACB0540, 0x03040414) 
#elif defined(CPLUSPLUS)
	#define USE_softing_profi_set_data
	#define EXT_softing_profi_set_data
	#define GET_softing_profi_set_data(fl)  CAL_CMGETAPI( "softing_profi_set_data" ) 
	#define CAL_softing_profi_set_data  softing_profi_set_data
	#define CHK_softing_profi_set_data  TRUE
	#define EXP_softing_profi_set_data  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_set_data", (RTS_UINTPTR)softing_profi_set_data, 1, 0xEACB0540, 0x03040414) 
#else /* DYNAMIC_LINK */
	#define USE_softing_profi_set_data  PFSOFTING_PROFI_SET_DATA_IEC pfsofting_profi_set_data;
	#define EXT_softing_profi_set_data  extern PFSOFTING_PROFI_SET_DATA_IEC pfsofting_profi_set_data;
	#define GET_softing_profi_set_data(fl)  s_pfCMGetAPI2( "softing_profi_set_data", (RTS_VOID_FCTPTR *)&pfsofting_profi_set_data, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xEACB0540, 0x03040414)
	#define CAL_softing_profi_set_data  pfsofting_profi_set_data
	#define CHK_softing_profi_set_data  (pfsofting_profi_set_data != NULL)
	#define EXP_softing_profi_set_data   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_set_data", (RTS_UINTPTR)softing_profi_set_data, 1, 0xEACB0540, 0x03040414) 
#endif


/**
 * <description>softing_profi_get_versions</description>
 */
typedef struct tagsofting_profi_get_versions_struct
{
	RTS_IEC_SINT *pPapiVersion;			/* VAR_INPUT */
	RTS_IEC_SINT *pFirmwareVersion;		/* VAR_INPUT */
	RTS_IEC_INT softing_profi_get_versions;	/* VAR_OUTPUT */
} softing_profi_get_versions_struct;

void CDECL CDECL_EXT softing_profi_get_versions(softing_profi_get_versions_struct *p);
typedef void (CDECL CDECL_EXT* PFSOFTING_PROFI_GET_VERSIONS_IEC) (softing_profi_get_versions_struct *p);
#if defined(CMPSOFTINGPROFIBUS_NOTIMPLEMENTED) || defined(SOFTING_PROFI_GET_VERSIONS_NOTIMPLEMENTED)
	#define USE_softing_profi_get_versions
	#define EXT_softing_profi_get_versions
	#define GET_softing_profi_get_versions(fl)  ERR_NOTIMPLEMENTED
	#define CAL_softing_profi_get_versions(p0) 
	#define CHK_softing_profi_get_versions  FALSE
	#define EXP_softing_profi_get_versions  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_softing_profi_get_versions
	#define EXT_softing_profi_get_versions
	#define GET_softing_profi_get_versions(fl)  CAL_CMGETAPI( "softing_profi_get_versions" ) 
	#define CAL_softing_profi_get_versions  softing_profi_get_versions
	#define CHK_softing_profi_get_versions  TRUE
	#define EXP_softing_profi_get_versions  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_versions", (RTS_UINTPTR)softing_profi_get_versions, 1, 0x8949CA9D, 0x03040414) 
#elif defined(MIXED_LINK) && !defined(CMPSOFTINGPROFIBUS_EXTERNAL)
	#define USE_softing_profi_get_versions
	#define EXT_softing_profi_get_versions
	#define GET_softing_profi_get_versions(fl)  CAL_CMGETAPI( "softing_profi_get_versions" ) 
	#define CAL_softing_profi_get_versions  softing_profi_get_versions
	#define CHK_softing_profi_get_versions  TRUE
	#define EXP_softing_profi_get_versions  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_versions", (RTS_UINTPTR)softing_profi_get_versions, 1, 0x8949CA9D, 0x03040414) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSoftingProfibussofting_profi_get_versions
	#define EXT_CmpSoftingProfibussofting_profi_get_versions
	#define GET_CmpSoftingProfibussofting_profi_get_versions  ERR_OK
	#define CAL_CmpSoftingProfibussofting_profi_get_versions  softing_profi_get_versions
	#define CHK_CmpSoftingProfibussofting_profi_get_versions  TRUE
	#define EXP_CmpSoftingProfibussofting_profi_get_versions  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_versions", (RTS_UINTPTR)softing_profi_get_versions, 1, 0x8949CA9D, 0x03040414) 
#elif defined(CPLUSPLUS)
	#define USE_softing_profi_get_versions
	#define EXT_softing_profi_get_versions
	#define GET_softing_profi_get_versions(fl)  CAL_CMGETAPI( "softing_profi_get_versions" ) 
	#define CAL_softing_profi_get_versions  softing_profi_get_versions
	#define CHK_softing_profi_get_versions  TRUE
	#define EXP_softing_profi_get_versions  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_versions", (RTS_UINTPTR)softing_profi_get_versions, 1, 0x8949CA9D, 0x03040414) 
#else /* DYNAMIC_LINK */
	#define USE_softing_profi_get_versions  PFSOFTING_PROFI_GET_VERSIONS_IEC pfsofting_profi_get_versions;
	#define EXT_softing_profi_get_versions  extern PFSOFTING_PROFI_GET_VERSIONS_IEC pfsofting_profi_get_versions;
	#define GET_softing_profi_get_versions(fl)  s_pfCMGetAPI2( "softing_profi_get_versions", (RTS_VOID_FCTPTR *)&pfsofting_profi_get_versions, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x8949CA9D, 0x03040414)
	#define CAL_softing_profi_get_versions  pfsofting_profi_get_versions
	#define CHK_softing_profi_get_versions  (pfsofting_profi_get_versions != NULL)
	#define EXP_softing_profi_get_versions   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_versions", (RTS_UINTPTR)softing_profi_get_versions, 1, 0x8949CA9D, 0x03040414) 
#endif


/**
 * <description>softing_profi_end</description>
 */
typedef struct tagsofting_profi_end_struct
{
	RTS_IEC_INT softing_profi_end;		/* VAR_OUTPUT */
} softing_profi_end_struct;

void CDECL CDECL_EXT softing_profi_end(softing_profi_end_struct *p);
typedef void (CDECL CDECL_EXT* PFSOFTING_PROFI_END_IEC) (softing_profi_end_struct *p);
#if defined(CMPSOFTINGPROFIBUS_NOTIMPLEMENTED) || defined(SOFTING_PROFI_END_NOTIMPLEMENTED)
	#define USE_softing_profi_end
	#define EXT_softing_profi_end
	#define GET_softing_profi_end(fl)  ERR_NOTIMPLEMENTED
	#define CAL_softing_profi_end(p0) 
	#define CHK_softing_profi_end  FALSE
	#define EXP_softing_profi_end  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_softing_profi_end
	#define EXT_softing_profi_end
	#define GET_softing_profi_end(fl)  CAL_CMGETAPI( "softing_profi_end" ) 
	#define CAL_softing_profi_end  softing_profi_end
	#define CHK_softing_profi_end  TRUE
	#define EXP_softing_profi_end  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_end", (RTS_UINTPTR)softing_profi_end, 1, 0x80D7B753, 0x03040414) 
#elif defined(MIXED_LINK) && !defined(CMPSOFTINGPROFIBUS_EXTERNAL)
	#define USE_softing_profi_end
	#define EXT_softing_profi_end
	#define GET_softing_profi_end(fl)  CAL_CMGETAPI( "softing_profi_end" ) 
	#define CAL_softing_profi_end  softing_profi_end
	#define CHK_softing_profi_end  TRUE
	#define EXP_softing_profi_end  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_end", (RTS_UINTPTR)softing_profi_end, 1, 0x80D7B753, 0x03040414) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSoftingProfibussofting_profi_end
	#define EXT_CmpSoftingProfibussofting_profi_end
	#define GET_CmpSoftingProfibussofting_profi_end  ERR_OK
	#define CAL_CmpSoftingProfibussofting_profi_end  softing_profi_end
	#define CHK_CmpSoftingProfibussofting_profi_end  TRUE
	#define EXP_CmpSoftingProfibussofting_profi_end  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_end", (RTS_UINTPTR)softing_profi_end, 1, 0x80D7B753, 0x03040414) 
#elif defined(CPLUSPLUS)
	#define USE_softing_profi_end
	#define EXT_softing_profi_end
	#define GET_softing_profi_end(fl)  CAL_CMGETAPI( "softing_profi_end" ) 
	#define CAL_softing_profi_end  softing_profi_end
	#define CHK_softing_profi_end  TRUE
	#define EXP_softing_profi_end  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_end", (RTS_UINTPTR)softing_profi_end, 1, 0x80D7B753, 0x03040414) 
#else /* DYNAMIC_LINK */
	#define USE_softing_profi_end  PFSOFTING_PROFI_END_IEC pfsofting_profi_end;
	#define EXT_softing_profi_end  extern PFSOFTING_PROFI_END_IEC pfsofting_profi_end;
	#define GET_softing_profi_end(fl)  s_pfCMGetAPI2( "softing_profi_end", (RTS_VOID_FCTPTR *)&pfsofting_profi_end, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x80D7B753, 0x03040414)
	#define CAL_softing_profi_end  pfsofting_profi_end
	#define CHK_softing_profi_end  (pfsofting_profi_end != NULL)
	#define EXP_softing_profi_end   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_end", (RTS_UINTPTR)softing_profi_end, 1, 0x80D7B753, 0x03040414) 
#endif


/**
 * <description>softing_profi_set_dps_input_data</description>
 */
typedef struct tagsofting_profi_set_dps_input_data_struct
{
	RTS_IEC_USINT *pData;				/* VAR_INPUT */
	RTS_IEC_USINT DataLength;			/* VAR_INPUT */
	RTS_IEC_USINT *pState;				/* VAR_INPUT */
	RTS_IEC_INT softing_profi_set_dps_input_data;	/* VAR_OUTPUT */
} softing_profi_set_dps_input_data_struct;

void CDECL CDECL_EXT softing_profi_set_dps_input_data(softing_profi_set_dps_input_data_struct *p);
typedef void (CDECL CDECL_EXT* PFSOFTING_PROFI_SET_DPS_INPUT_DATA_IEC) (softing_profi_set_dps_input_data_struct *p);
#if defined(CMPSOFTINGPROFIBUS_NOTIMPLEMENTED) || defined(SOFTING_PROFI_SET_DPS_INPUT_DATA_NOTIMPLEMENTED)
	#define USE_softing_profi_set_dps_input_data
	#define EXT_softing_profi_set_dps_input_data
	#define GET_softing_profi_set_dps_input_data(fl)  ERR_NOTIMPLEMENTED
	#define CAL_softing_profi_set_dps_input_data(p0) 
	#define CHK_softing_profi_set_dps_input_data  FALSE
	#define EXP_softing_profi_set_dps_input_data  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_softing_profi_set_dps_input_data
	#define EXT_softing_profi_set_dps_input_data
	#define GET_softing_profi_set_dps_input_data(fl)  CAL_CMGETAPI( "softing_profi_set_dps_input_data" ) 
	#define CAL_softing_profi_set_dps_input_data  softing_profi_set_dps_input_data
	#define CHK_softing_profi_set_dps_input_data  TRUE
	#define EXP_softing_profi_set_dps_input_data  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_set_dps_input_data", (RTS_UINTPTR)softing_profi_set_dps_input_data, 1, 0xA21E693A, 0x03040414) 
#elif defined(MIXED_LINK) && !defined(CMPSOFTINGPROFIBUS_EXTERNAL)
	#define USE_softing_profi_set_dps_input_data
	#define EXT_softing_profi_set_dps_input_data
	#define GET_softing_profi_set_dps_input_data(fl)  CAL_CMGETAPI( "softing_profi_set_dps_input_data" ) 
	#define CAL_softing_profi_set_dps_input_data  softing_profi_set_dps_input_data
	#define CHK_softing_profi_set_dps_input_data  TRUE
	#define EXP_softing_profi_set_dps_input_data  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_set_dps_input_data", (RTS_UINTPTR)softing_profi_set_dps_input_data, 1, 0xA21E693A, 0x03040414) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSoftingProfibussofting_profi_set_dps_input_data
	#define EXT_CmpSoftingProfibussofting_profi_set_dps_input_data
	#define GET_CmpSoftingProfibussofting_profi_set_dps_input_data  ERR_OK
	#define CAL_CmpSoftingProfibussofting_profi_set_dps_input_data  softing_profi_set_dps_input_data
	#define CHK_CmpSoftingProfibussofting_profi_set_dps_input_data  TRUE
	#define EXP_CmpSoftingProfibussofting_profi_set_dps_input_data  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_set_dps_input_data", (RTS_UINTPTR)softing_profi_set_dps_input_data, 1, 0xA21E693A, 0x03040414) 
#elif defined(CPLUSPLUS)
	#define USE_softing_profi_set_dps_input_data
	#define EXT_softing_profi_set_dps_input_data
	#define GET_softing_profi_set_dps_input_data(fl)  CAL_CMGETAPI( "softing_profi_set_dps_input_data" ) 
	#define CAL_softing_profi_set_dps_input_data  softing_profi_set_dps_input_data
	#define CHK_softing_profi_set_dps_input_data  TRUE
	#define EXP_softing_profi_set_dps_input_data  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_set_dps_input_data", (RTS_UINTPTR)softing_profi_set_dps_input_data, 1, 0xA21E693A, 0x03040414) 
#else /* DYNAMIC_LINK */
	#define USE_softing_profi_set_dps_input_data  PFSOFTING_PROFI_SET_DPS_INPUT_DATA_IEC pfsofting_profi_set_dps_input_data;
	#define EXT_softing_profi_set_dps_input_data  extern PFSOFTING_PROFI_SET_DPS_INPUT_DATA_IEC pfsofting_profi_set_dps_input_data;
	#define GET_softing_profi_set_dps_input_data(fl)  s_pfCMGetAPI2( "softing_profi_set_dps_input_data", (RTS_VOID_FCTPTR *)&pfsofting_profi_set_dps_input_data, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xA21E693A, 0x03040414)
	#define CAL_softing_profi_set_dps_input_data  pfsofting_profi_set_dps_input_data
	#define CHK_softing_profi_set_dps_input_data  (pfsofting_profi_set_dps_input_data != NULL)
	#define EXP_softing_profi_set_dps_input_data   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_set_dps_input_data", (RTS_UINTPTR)softing_profi_set_dps_input_data, 1, 0xA21E693A, 0x03040414) 
#endif


/**
 * <description>softing_profi_get_serial_device_number</description>
 */
typedef struct tagsofting_profi_get_serial_device_number_struct
{
	RTS_IEC_UDINT *pSerialDeviceNumber;	/* VAR_INPUT */
	RTS_IEC_INT softing_profi_get_serial_device_number;	/* VAR_OUTPUT */
} softing_profi_get_serial_device_number_struct;

void CDECL CDECL_EXT softing_profi_get_serial_device_number(softing_profi_get_serial_device_number_struct *p);
typedef void (CDECL CDECL_EXT* PFSOFTING_PROFI_GET_SERIAL_DEVICE_NUMBER_IEC) (softing_profi_get_serial_device_number_struct *p);
#if defined(CMPSOFTINGPROFIBUS_NOTIMPLEMENTED) || defined(SOFTING_PROFI_GET_SERIAL_DEVICE_NUMBER_NOTIMPLEMENTED)
	#define USE_softing_profi_get_serial_device_number
	#define EXT_softing_profi_get_serial_device_number
	#define GET_softing_profi_get_serial_device_number(fl)  ERR_NOTIMPLEMENTED
	#define CAL_softing_profi_get_serial_device_number(p0) 
	#define CHK_softing_profi_get_serial_device_number  FALSE
	#define EXP_softing_profi_get_serial_device_number  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_softing_profi_get_serial_device_number
	#define EXT_softing_profi_get_serial_device_number
	#define GET_softing_profi_get_serial_device_number(fl)  CAL_CMGETAPI( "softing_profi_get_serial_device_number" ) 
	#define CAL_softing_profi_get_serial_device_number  softing_profi_get_serial_device_number
	#define CHK_softing_profi_get_serial_device_number  TRUE
	#define EXP_softing_profi_get_serial_device_number  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_serial_device_number", (RTS_UINTPTR)softing_profi_get_serial_device_number, 1, 0x1FF9FA59, 0x03040414) 
#elif defined(MIXED_LINK) && !defined(CMPSOFTINGPROFIBUS_EXTERNAL)
	#define USE_softing_profi_get_serial_device_number
	#define EXT_softing_profi_get_serial_device_number
	#define GET_softing_profi_get_serial_device_number(fl)  CAL_CMGETAPI( "softing_profi_get_serial_device_number" ) 
	#define CAL_softing_profi_get_serial_device_number  softing_profi_get_serial_device_number
	#define CHK_softing_profi_get_serial_device_number  TRUE
	#define EXP_softing_profi_get_serial_device_number  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_serial_device_number", (RTS_UINTPTR)softing_profi_get_serial_device_number, 1, 0x1FF9FA59, 0x03040414) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSoftingProfibussofting_profi_get_serial_device_number
	#define EXT_CmpSoftingProfibussofting_profi_get_serial_device_number
	#define GET_CmpSoftingProfibussofting_profi_get_serial_device_number  ERR_OK
	#define CAL_CmpSoftingProfibussofting_profi_get_serial_device_number  softing_profi_get_serial_device_number
	#define CHK_CmpSoftingProfibussofting_profi_get_serial_device_number  TRUE
	#define EXP_CmpSoftingProfibussofting_profi_get_serial_device_number  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_serial_device_number", (RTS_UINTPTR)softing_profi_get_serial_device_number, 1, 0x1FF9FA59, 0x03040414) 
#elif defined(CPLUSPLUS)
	#define USE_softing_profi_get_serial_device_number
	#define EXT_softing_profi_get_serial_device_number
	#define GET_softing_profi_get_serial_device_number(fl)  CAL_CMGETAPI( "softing_profi_get_serial_device_number" ) 
	#define CAL_softing_profi_get_serial_device_number  softing_profi_get_serial_device_number
	#define CHK_softing_profi_get_serial_device_number  TRUE
	#define EXP_softing_profi_get_serial_device_number  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_serial_device_number", (RTS_UINTPTR)softing_profi_get_serial_device_number, 1, 0x1FF9FA59, 0x03040414) 
#else /* DYNAMIC_LINK */
	#define USE_softing_profi_get_serial_device_number  PFSOFTING_PROFI_GET_SERIAL_DEVICE_NUMBER_IEC pfsofting_profi_get_serial_device_number;
	#define EXT_softing_profi_get_serial_device_number  extern PFSOFTING_PROFI_GET_SERIAL_DEVICE_NUMBER_IEC pfsofting_profi_get_serial_device_number;
	#define GET_softing_profi_get_serial_device_number(fl)  s_pfCMGetAPI2( "softing_profi_get_serial_device_number", (RTS_VOID_FCTPTR *)&pfsofting_profi_get_serial_device_number, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x1FF9FA59, 0x03040414)
	#define CAL_softing_profi_get_serial_device_number  pfsofting_profi_get_serial_device_number
	#define CHK_softing_profi_get_serial_device_number  (pfsofting_profi_get_serial_device_number != NULL)
	#define EXP_softing_profi_get_serial_device_number   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_serial_device_number", (RTS_UINTPTR)softing_profi_get_serial_device_number, 1, 0x1FF9FA59, 0x03040414) 
#endif


/**
 * <description>softing_profi_rcv_con_ind</description>
 */
typedef struct tagsofting_profi_rcv_con_ind_struct
{
	SOFTING_T_PROFI_SERVICE_DESCR *pSdb;	/* VAR_INPUT */
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */
	RTS_IEC_UINT *pDataLength;			/* VAR_INPUT */
	RTS_IEC_INT softing_profi_rcv_con_ind;	/* VAR_OUTPUT */
} softing_profi_rcv_con_ind_struct;

void CDECL CDECL_EXT softing_profi_rcv_con_ind(softing_profi_rcv_con_ind_struct *p);
typedef void (CDECL CDECL_EXT* PFSOFTING_PROFI_RCV_CON_IND_IEC) (softing_profi_rcv_con_ind_struct *p);
#if defined(CMPSOFTINGPROFIBUS_NOTIMPLEMENTED) || defined(SOFTING_PROFI_RCV_CON_IND_NOTIMPLEMENTED)
	#define USE_softing_profi_rcv_con_ind
	#define EXT_softing_profi_rcv_con_ind
	#define GET_softing_profi_rcv_con_ind(fl)  ERR_NOTIMPLEMENTED
	#define CAL_softing_profi_rcv_con_ind(p0) 
	#define CHK_softing_profi_rcv_con_ind  FALSE
	#define EXP_softing_profi_rcv_con_ind  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_softing_profi_rcv_con_ind
	#define EXT_softing_profi_rcv_con_ind
	#define GET_softing_profi_rcv_con_ind(fl)  CAL_CMGETAPI( "softing_profi_rcv_con_ind" ) 
	#define CAL_softing_profi_rcv_con_ind  softing_profi_rcv_con_ind
	#define CHK_softing_profi_rcv_con_ind  TRUE
	#define EXP_softing_profi_rcv_con_ind  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_rcv_con_ind", (RTS_UINTPTR)softing_profi_rcv_con_ind, 1, 0x2476D026, 0x03040414) 
#elif defined(MIXED_LINK) && !defined(CMPSOFTINGPROFIBUS_EXTERNAL)
	#define USE_softing_profi_rcv_con_ind
	#define EXT_softing_profi_rcv_con_ind
	#define GET_softing_profi_rcv_con_ind(fl)  CAL_CMGETAPI( "softing_profi_rcv_con_ind" ) 
	#define CAL_softing_profi_rcv_con_ind  softing_profi_rcv_con_ind
	#define CHK_softing_profi_rcv_con_ind  TRUE
	#define EXP_softing_profi_rcv_con_ind  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_rcv_con_ind", (RTS_UINTPTR)softing_profi_rcv_con_ind, 1, 0x2476D026, 0x03040414) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSoftingProfibussofting_profi_rcv_con_ind
	#define EXT_CmpSoftingProfibussofting_profi_rcv_con_ind
	#define GET_CmpSoftingProfibussofting_profi_rcv_con_ind  ERR_OK
	#define CAL_CmpSoftingProfibussofting_profi_rcv_con_ind  softing_profi_rcv_con_ind
	#define CHK_CmpSoftingProfibussofting_profi_rcv_con_ind  TRUE
	#define EXP_CmpSoftingProfibussofting_profi_rcv_con_ind  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_rcv_con_ind", (RTS_UINTPTR)softing_profi_rcv_con_ind, 1, 0x2476D026, 0x03040414) 
#elif defined(CPLUSPLUS)
	#define USE_softing_profi_rcv_con_ind
	#define EXT_softing_profi_rcv_con_ind
	#define GET_softing_profi_rcv_con_ind(fl)  CAL_CMGETAPI( "softing_profi_rcv_con_ind" ) 
	#define CAL_softing_profi_rcv_con_ind  softing_profi_rcv_con_ind
	#define CHK_softing_profi_rcv_con_ind  TRUE
	#define EXP_softing_profi_rcv_con_ind  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_rcv_con_ind", (RTS_UINTPTR)softing_profi_rcv_con_ind, 1, 0x2476D026, 0x03040414) 
#else /* DYNAMIC_LINK */
	#define USE_softing_profi_rcv_con_ind  PFSOFTING_PROFI_RCV_CON_IND_IEC pfsofting_profi_rcv_con_ind;
	#define EXT_softing_profi_rcv_con_ind  extern PFSOFTING_PROFI_RCV_CON_IND_IEC pfsofting_profi_rcv_con_ind;
	#define GET_softing_profi_rcv_con_ind(fl)  s_pfCMGetAPI2( "softing_profi_rcv_con_ind", (RTS_VOID_FCTPTR *)&pfsofting_profi_rcv_con_ind, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x2476D026, 0x03040414)
	#define CAL_softing_profi_rcv_con_ind  pfsofting_profi_rcv_con_ind
	#define CHK_softing_profi_rcv_con_ind  (pfsofting_profi_rcv_con_ind != NULL)
	#define EXP_softing_profi_rcv_con_ind   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_rcv_con_ind", (RTS_UINTPTR)softing_profi_rcv_con_ind, 1, 0x2476D026, 0x03040414) 
#endif


/**
 * <description>softing_profi_snd_req_res</description>
 */
typedef struct tagsofting_profi_snd_req_res_struct
{
	SOFTING_T_PROFI_SERVICE_DESCR *pSdb;	/* VAR_INPUT */
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */
	RTS_IEC_USINT Dummy;				/* VAR_INPUT */
	RTS_IEC_INT softing_profi_snd_req_res;	/* VAR_OUTPUT */
} softing_profi_snd_req_res_struct;

void CDECL CDECL_EXT softing_profi_snd_req_res(softing_profi_snd_req_res_struct *p);
typedef void (CDECL CDECL_EXT* PFSOFTING_PROFI_SND_REQ_RES_IEC) (softing_profi_snd_req_res_struct *p);
#if defined(CMPSOFTINGPROFIBUS_NOTIMPLEMENTED) || defined(SOFTING_PROFI_SND_REQ_RES_NOTIMPLEMENTED)
	#define USE_softing_profi_snd_req_res
	#define EXT_softing_profi_snd_req_res
	#define GET_softing_profi_snd_req_res(fl)  ERR_NOTIMPLEMENTED
	#define CAL_softing_profi_snd_req_res(p0) 
	#define CHK_softing_profi_snd_req_res  FALSE
	#define EXP_softing_profi_snd_req_res  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_softing_profi_snd_req_res
	#define EXT_softing_profi_snd_req_res
	#define GET_softing_profi_snd_req_res(fl)  CAL_CMGETAPI( "softing_profi_snd_req_res" ) 
	#define CAL_softing_profi_snd_req_res  softing_profi_snd_req_res
	#define CHK_softing_profi_snd_req_res  TRUE
	#define EXP_softing_profi_snd_req_res  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_snd_req_res", (RTS_UINTPTR)softing_profi_snd_req_res, 1, 0xCC3AEC38, 0x03040414) 
#elif defined(MIXED_LINK) && !defined(CMPSOFTINGPROFIBUS_EXTERNAL)
	#define USE_softing_profi_snd_req_res
	#define EXT_softing_profi_snd_req_res
	#define GET_softing_profi_snd_req_res(fl)  CAL_CMGETAPI( "softing_profi_snd_req_res" ) 
	#define CAL_softing_profi_snd_req_res  softing_profi_snd_req_res
	#define CHK_softing_profi_snd_req_res  TRUE
	#define EXP_softing_profi_snd_req_res  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_snd_req_res", (RTS_UINTPTR)softing_profi_snd_req_res, 1, 0xCC3AEC38, 0x03040414) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSoftingProfibussofting_profi_snd_req_res
	#define EXT_CmpSoftingProfibussofting_profi_snd_req_res
	#define GET_CmpSoftingProfibussofting_profi_snd_req_res  ERR_OK
	#define CAL_CmpSoftingProfibussofting_profi_snd_req_res  softing_profi_snd_req_res
	#define CHK_CmpSoftingProfibussofting_profi_snd_req_res  TRUE
	#define EXP_CmpSoftingProfibussofting_profi_snd_req_res  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_snd_req_res", (RTS_UINTPTR)softing_profi_snd_req_res, 1, 0xCC3AEC38, 0x03040414) 
#elif defined(CPLUSPLUS)
	#define USE_softing_profi_snd_req_res
	#define EXT_softing_profi_snd_req_res
	#define GET_softing_profi_snd_req_res(fl)  CAL_CMGETAPI( "softing_profi_snd_req_res" ) 
	#define CAL_softing_profi_snd_req_res  softing_profi_snd_req_res
	#define CHK_softing_profi_snd_req_res  TRUE
	#define EXP_softing_profi_snd_req_res  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_snd_req_res", (RTS_UINTPTR)softing_profi_snd_req_res, 1, 0xCC3AEC38, 0x03040414) 
#else /* DYNAMIC_LINK */
	#define USE_softing_profi_snd_req_res  PFSOFTING_PROFI_SND_REQ_RES_IEC pfsofting_profi_snd_req_res;
	#define EXT_softing_profi_snd_req_res  extern PFSOFTING_PROFI_SND_REQ_RES_IEC pfsofting_profi_snd_req_res;
	#define GET_softing_profi_snd_req_res(fl)  s_pfCMGetAPI2( "softing_profi_snd_req_res", (RTS_VOID_FCTPTR *)&pfsofting_profi_snd_req_res, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xCC3AEC38, 0x03040414)
	#define CAL_softing_profi_snd_req_res  pfsofting_profi_snd_req_res
	#define CHK_softing_profi_snd_req_res  (pfsofting_profi_snd_req_res != NULL)
	#define EXP_softing_profi_snd_req_res   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_snd_req_res", (RTS_UINTPTR)softing_profi_snd_req_res, 1, 0xCC3AEC38, 0x03040414) 
#endif


/**
 * <description>softing_profi_init</description>
 */
typedef struct tagsofting_profi_init_struct
{
	RTS_IEC_USINT Board;				/* VAR_INPUT */
	RTS_IEC_UDINT ReadTimeout;			/* VAR_INPUT */
	RTS_IEC_UDINT WriteTimeout;			/* VAR_INPUT */
	RTS_IEC_INT softing_profi_init;		/* VAR_OUTPUT */
} softing_profi_init_struct;

void CDECL CDECL_EXT softing_profi_init(softing_profi_init_struct *p);
typedef void (CDECL CDECL_EXT* PFSOFTING_PROFI_INIT_IEC) (softing_profi_init_struct *p);
#if defined(CMPSOFTINGPROFIBUS_NOTIMPLEMENTED) || defined(SOFTING_PROFI_INIT_NOTIMPLEMENTED)
	#define USE_softing_profi_init
	#define EXT_softing_profi_init
	#define GET_softing_profi_init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_softing_profi_init(p0) 
	#define CHK_softing_profi_init  FALSE
	#define EXP_softing_profi_init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_softing_profi_init
	#define EXT_softing_profi_init
	#define GET_softing_profi_init(fl)  CAL_CMGETAPI( "softing_profi_init" ) 
	#define CAL_softing_profi_init  softing_profi_init
	#define CHK_softing_profi_init  TRUE
	#define EXP_softing_profi_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_init", (RTS_UINTPTR)softing_profi_init, 1, 0xB4F2204C, 0x03040414) 
#elif defined(MIXED_LINK) && !defined(CMPSOFTINGPROFIBUS_EXTERNAL)
	#define USE_softing_profi_init
	#define EXT_softing_profi_init
	#define GET_softing_profi_init(fl)  CAL_CMGETAPI( "softing_profi_init" ) 
	#define CAL_softing_profi_init  softing_profi_init
	#define CHK_softing_profi_init  TRUE
	#define EXP_softing_profi_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_init", (RTS_UINTPTR)softing_profi_init, 1, 0xB4F2204C, 0x03040414) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSoftingProfibussofting_profi_init
	#define EXT_CmpSoftingProfibussofting_profi_init
	#define GET_CmpSoftingProfibussofting_profi_init  ERR_OK
	#define CAL_CmpSoftingProfibussofting_profi_init  softing_profi_init
	#define CHK_CmpSoftingProfibussofting_profi_init  TRUE
	#define EXP_CmpSoftingProfibussofting_profi_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_init", (RTS_UINTPTR)softing_profi_init, 1, 0xB4F2204C, 0x03040414) 
#elif defined(CPLUSPLUS)
	#define USE_softing_profi_init
	#define EXT_softing_profi_init
	#define GET_softing_profi_init(fl)  CAL_CMGETAPI( "softing_profi_init" ) 
	#define CAL_softing_profi_init  softing_profi_init
	#define CHK_softing_profi_init  TRUE
	#define EXP_softing_profi_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_init", (RTS_UINTPTR)softing_profi_init, 1, 0xB4F2204C, 0x03040414) 
#else /* DYNAMIC_LINK */
	#define USE_softing_profi_init  PFSOFTING_PROFI_INIT_IEC pfsofting_profi_init;
	#define EXT_softing_profi_init  extern PFSOFTING_PROFI_INIT_IEC pfsofting_profi_init;
	#define GET_softing_profi_init(fl)  s_pfCMGetAPI2( "softing_profi_init", (RTS_VOID_FCTPTR *)&pfsofting_profi_init, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xB4F2204C, 0x03040414)
	#define CAL_softing_profi_init  pfsofting_profi_init
	#define CHK_softing_profi_init  (pfsofting_profi_init != NULL)
	#define EXP_softing_profi_init   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_init", (RTS_UINTPTR)softing_profi_init, 1, 0xB4F2204C, 0x03040414) 
#endif


/**
 * <description>softing_profi_get_dps_output_data</description>
 */
typedef struct tagsofting_profi_get_dps_output_data_struct
{
	RTS_IEC_USINT *pData;				/* VAR_INPUT */
	RTS_IEC_USINT *pDataLength;			/* VAR_INPUT */
	RTS_IEC_USINT *pState;				/* VAR_INPUT */
	RTS_IEC_INT softing_profi_get_dps_output_data;	/* VAR_OUTPUT */
} softing_profi_get_dps_output_data_struct;

void CDECL CDECL_EXT softing_profi_get_dps_output_data(softing_profi_get_dps_output_data_struct *p);
typedef void (CDECL CDECL_EXT* PFSOFTING_PROFI_GET_DPS_OUTPUT_DATA_IEC) (softing_profi_get_dps_output_data_struct *p);
#if defined(CMPSOFTINGPROFIBUS_NOTIMPLEMENTED) || defined(SOFTING_PROFI_GET_DPS_OUTPUT_DATA_NOTIMPLEMENTED)
	#define USE_softing_profi_get_dps_output_data
	#define EXT_softing_profi_get_dps_output_data
	#define GET_softing_profi_get_dps_output_data(fl)  ERR_NOTIMPLEMENTED
	#define CAL_softing_profi_get_dps_output_data(p0) 
	#define CHK_softing_profi_get_dps_output_data  FALSE
	#define EXP_softing_profi_get_dps_output_data  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_softing_profi_get_dps_output_data
	#define EXT_softing_profi_get_dps_output_data
	#define GET_softing_profi_get_dps_output_data(fl)  CAL_CMGETAPI( "softing_profi_get_dps_output_data" ) 
	#define CAL_softing_profi_get_dps_output_data  softing_profi_get_dps_output_data
	#define CHK_softing_profi_get_dps_output_data  TRUE
	#define EXP_softing_profi_get_dps_output_data  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_dps_output_data", (RTS_UINTPTR)softing_profi_get_dps_output_data, 1, 0xA0C40F04, 0x03040414) 
#elif defined(MIXED_LINK) && !defined(CMPSOFTINGPROFIBUS_EXTERNAL)
	#define USE_softing_profi_get_dps_output_data
	#define EXT_softing_profi_get_dps_output_data
	#define GET_softing_profi_get_dps_output_data(fl)  CAL_CMGETAPI( "softing_profi_get_dps_output_data" ) 
	#define CAL_softing_profi_get_dps_output_data  softing_profi_get_dps_output_data
	#define CHK_softing_profi_get_dps_output_data  TRUE
	#define EXP_softing_profi_get_dps_output_data  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_dps_output_data", (RTS_UINTPTR)softing_profi_get_dps_output_data, 1, 0xA0C40F04, 0x03040414) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSoftingProfibussofting_profi_get_dps_output_data
	#define EXT_CmpSoftingProfibussofting_profi_get_dps_output_data
	#define GET_CmpSoftingProfibussofting_profi_get_dps_output_data  ERR_OK
	#define CAL_CmpSoftingProfibussofting_profi_get_dps_output_data  softing_profi_get_dps_output_data
	#define CHK_CmpSoftingProfibussofting_profi_get_dps_output_data  TRUE
	#define EXP_CmpSoftingProfibussofting_profi_get_dps_output_data  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_dps_output_data", (RTS_UINTPTR)softing_profi_get_dps_output_data, 1, 0xA0C40F04, 0x03040414) 
#elif defined(CPLUSPLUS)
	#define USE_softing_profi_get_dps_output_data
	#define EXT_softing_profi_get_dps_output_data
	#define GET_softing_profi_get_dps_output_data(fl)  CAL_CMGETAPI( "softing_profi_get_dps_output_data" ) 
	#define CAL_softing_profi_get_dps_output_data  softing_profi_get_dps_output_data
	#define CHK_softing_profi_get_dps_output_data  TRUE
	#define EXP_softing_profi_get_dps_output_data  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_dps_output_data", (RTS_UINTPTR)softing_profi_get_dps_output_data, 1, 0xA0C40F04, 0x03040414) 
#else /* DYNAMIC_LINK */
	#define USE_softing_profi_get_dps_output_data  PFSOFTING_PROFI_GET_DPS_OUTPUT_DATA_IEC pfsofting_profi_get_dps_output_data;
	#define EXT_softing_profi_get_dps_output_data  extern PFSOFTING_PROFI_GET_DPS_OUTPUT_DATA_IEC pfsofting_profi_get_dps_output_data;
	#define GET_softing_profi_get_dps_output_data(fl)  s_pfCMGetAPI2( "softing_profi_get_dps_output_data", (RTS_VOID_FCTPTR *)&pfsofting_profi_get_dps_output_data, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xA0C40F04, 0x03040414)
	#define CAL_softing_profi_get_dps_output_data  pfsofting_profi_get_dps_output_data
	#define CHK_softing_profi_get_dps_output_data  (pfsofting_profi_get_dps_output_data != NULL)
	#define EXP_softing_profi_get_dps_output_data   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_dps_output_data", (RTS_UINTPTR)softing_profi_get_dps_output_data, 1, 0xA0C40F04, 0x03040414) 
#endif


/**
 * <description>softing_profi_get_data</description>
 */
typedef struct tagsofting_profi_get_data_struct
{
	RTS_IEC_USINT DataId;				/* VAR_INPUT */
	RTS_IEC_UINT Offset;				/* VAR_INPUT */
	RTS_IEC_UINT *pDataSize;			/* VAR_INPUT */
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */
	RTS_IEC_INT softing_profi_get_data;	/* VAR_OUTPUT */
} softing_profi_get_data_struct;

void CDECL CDECL_EXT softing_profi_get_data(softing_profi_get_data_struct *p);
typedef void (CDECL CDECL_EXT* PFSOFTING_PROFI_GET_DATA_IEC) (softing_profi_get_data_struct *p);
#if defined(CMPSOFTINGPROFIBUS_NOTIMPLEMENTED) || defined(SOFTING_PROFI_GET_DATA_NOTIMPLEMENTED)
	#define USE_softing_profi_get_data
	#define EXT_softing_profi_get_data
	#define GET_softing_profi_get_data(fl)  ERR_NOTIMPLEMENTED
	#define CAL_softing_profi_get_data(p0) 
	#define CHK_softing_profi_get_data  FALSE
	#define EXP_softing_profi_get_data  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_softing_profi_get_data
	#define EXT_softing_profi_get_data
	#define GET_softing_profi_get_data(fl)  CAL_CMGETAPI( "softing_profi_get_data" ) 
	#define CAL_softing_profi_get_data  softing_profi_get_data
	#define CHK_softing_profi_get_data  TRUE
	#define EXP_softing_profi_get_data  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_data", (RTS_UINTPTR)softing_profi_get_data, 1, 0x89219B6E, 0x03040414) 
#elif defined(MIXED_LINK) && !defined(CMPSOFTINGPROFIBUS_EXTERNAL)
	#define USE_softing_profi_get_data
	#define EXT_softing_profi_get_data
	#define GET_softing_profi_get_data(fl)  CAL_CMGETAPI( "softing_profi_get_data" ) 
	#define CAL_softing_profi_get_data  softing_profi_get_data
	#define CHK_softing_profi_get_data  TRUE
	#define EXP_softing_profi_get_data  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_data", (RTS_UINTPTR)softing_profi_get_data, 1, 0x89219B6E, 0x03040414) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpSoftingProfibussofting_profi_get_data
	#define EXT_CmpSoftingProfibussofting_profi_get_data
	#define GET_CmpSoftingProfibussofting_profi_get_data  ERR_OK
	#define CAL_CmpSoftingProfibussofting_profi_get_data  softing_profi_get_data
	#define CHK_CmpSoftingProfibussofting_profi_get_data  TRUE
	#define EXP_CmpSoftingProfibussofting_profi_get_data  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_data", (RTS_UINTPTR)softing_profi_get_data, 1, 0x89219B6E, 0x03040414) 
#elif defined(CPLUSPLUS)
	#define USE_softing_profi_get_data
	#define EXT_softing_profi_get_data
	#define GET_softing_profi_get_data(fl)  CAL_CMGETAPI( "softing_profi_get_data" ) 
	#define CAL_softing_profi_get_data  softing_profi_get_data
	#define CHK_softing_profi_get_data  TRUE
	#define EXP_softing_profi_get_data  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_data", (RTS_UINTPTR)softing_profi_get_data, 1, 0x89219B6E, 0x03040414) 
#else /* DYNAMIC_LINK */
	#define USE_softing_profi_get_data  PFSOFTING_PROFI_GET_DATA_IEC pfsofting_profi_get_data;
	#define EXT_softing_profi_get_data  extern PFSOFTING_PROFI_GET_DATA_IEC pfsofting_profi_get_data;
	#define GET_softing_profi_get_data(fl)  s_pfCMGetAPI2( "softing_profi_get_data", (RTS_VOID_FCTPTR *)&pfsofting_profi_get_data, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x89219B6E, 0x03040414)
	#define CAL_softing_profi_get_data  pfsofting_profi_get_data
	#define CHK_softing_profi_get_data  (pfsofting_profi_get_data != NULL)
	#define EXP_softing_profi_get_data   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"softing_profi_get_data", (RTS_UINTPTR)softing_profi_get_data, 1, 0x89219B6E, 0x03040414) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
} ICmpSoftingProfibus_C;

#ifdef CPLUSPLUS
class ICmpSoftingProfibus : public IBase
{
	public:
};
	#ifndef ITF_CmpSoftingProfibus
		#define ITF_CmpSoftingProfibus static ICmpSoftingProfibus *pICmpSoftingProfibus = NULL;
	#endif
	#define EXTITF_CmpSoftingProfibus
#else	/*CPLUSPLUS*/
	typedef ICmpSoftingProfibus_C		ICmpSoftingProfibus;
	#ifndef ITF_CmpSoftingProfibus
		#define ITF_CmpSoftingProfibus
	#endif
	#define EXTITF_CmpSoftingProfibus
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPSOFTINGPROFIBUSITF_H_*/
