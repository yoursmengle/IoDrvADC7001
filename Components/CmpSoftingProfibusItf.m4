/**
 * <interfacename>CmpSoftingProfibus</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`CmpSoftingProfibus')

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

DEF_API(`void',`CDECL',`softing_profi_get_last_errror',`(softing_profi_get_last_errror_struct *p)',1,0xD6F91F9D,0x03040414)

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

DEF_API(`void',`CDECL',`softing_profi_get_dps_input_data',`(softing_profi_get_dps_input_data_struct *p)',1,0xE8323117,0x03040414)

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

DEF_API(`void',`CDECL',`softing_profi_set_data',`(softing_profi_set_data_struct *p)',1,0xEACB0540,0x03040414)

/**
 * <description>softing_profi_get_versions</description>
 */
typedef struct tagsofting_profi_get_versions_struct
{
	RTS_IEC_SINT *pPapiVersion;			/* VAR_INPUT */
	RTS_IEC_SINT *pFirmwareVersion;		/* VAR_INPUT */
	RTS_IEC_INT softing_profi_get_versions;	/* VAR_OUTPUT */
} softing_profi_get_versions_struct;

DEF_API(`void',`CDECL',`softing_profi_get_versions',`(softing_profi_get_versions_struct *p)',1,0x8949CA9D,0x03040414)

/**
 * <description>softing_profi_end</description>
 */
typedef struct tagsofting_profi_end_struct
{
	RTS_IEC_INT softing_profi_end;		/* VAR_OUTPUT */
} softing_profi_end_struct;

DEF_API(`void',`CDECL',`softing_profi_end',`(softing_profi_end_struct *p)',1,0x80D7B753,0x03040414)

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

DEF_API(`void',`CDECL',`softing_profi_set_dps_input_data',`(softing_profi_set_dps_input_data_struct *p)',1,0xA21E693A,0x03040414)

/**
 * <description>softing_profi_get_serial_device_number</description>
 */
typedef struct tagsofting_profi_get_serial_device_number_struct
{
	RTS_IEC_UDINT *pSerialDeviceNumber;	/* VAR_INPUT */
	RTS_IEC_INT softing_profi_get_serial_device_number;	/* VAR_OUTPUT */
} softing_profi_get_serial_device_number_struct;

DEF_API(`void',`CDECL',`softing_profi_get_serial_device_number',`(softing_profi_get_serial_device_number_struct *p)',1,0x1FF9FA59,0x03040414)

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

DEF_API(`void',`CDECL',`softing_profi_rcv_con_ind',`(softing_profi_rcv_con_ind_struct *p)',1,0x2476D026,0x03040414)

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

DEF_API(`void',`CDECL',`softing_profi_snd_req_res',`(softing_profi_snd_req_res_struct *p)',1,0xCC3AEC38,0x03040414)

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

DEF_API(`void',`CDECL',`softing_profi_init',`(softing_profi_init_struct *p)',1,0xB4F2204C,0x03040414)

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

DEF_API(`void',`CDECL',`softing_profi_get_dps_output_data',`(softing_profi_get_dps_output_data_struct *p)',1,0xA0C40F04,0x03040414)

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

DEF_API(`void',`CDECL',`softing_profi_get_data',`(softing_profi_get_data_struct *p)',1,0x89219B6E,0x03040414)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

