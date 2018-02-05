#ifndef __CMPVISUSERVICES_H__
#define __CMPVISUSERVICES_H__

/* Visu services */
#define SRV_VISU_REGISTERCLIENT		0x01
#define SRV_VISU_REMOVECLIENT		0x02
#define SRV_VISU_ISREGISTERED		0x03
#define SRV_VISU_GETPAINTDATA		0x04
#define SRV_VISU_ISVALIDCLIENTID	0x05
#define SRV_VISU_POSTEVENT			0x06
#define SRV_VISU_WRITEIMAGEPOOL		0x07
#define SRV_VISU_POSTCLIENTREQUEST	0x10
/* User management services */
#define SRV_VISU_USER_MGMT_GETUSERCOUNT		0x08
#define SRV_VISU_USER_MGMT_GETUSERS			0x09
#define SRV_VISU_USER_MGMT_CHECKCHANGEUSER	0x0A
#define SRV_VISU_USER_MGMT_GETSETDB			0x0B
/* END User management services */
#define SRV_FILETRANSFER_GETFILEINFO	0x01
#define SRV_FILETRANSFER_STARTDOWNLOAD	0x02
#define SRV_FILETRANSFER_DOWNLOAD		0x04
#define SRV_FILETRANSFER_STARTUPLOAD	0x05
#define SRV_FILETRANSFER_UPLOAD			0x07
#define SRV_FILETRANSFER_END			0x08
#define SRV_FILETRANSFER_CANCEL			0x09
/* END Visu services */

/* Visu Tags */
#define TAG_VISU_REGISTERCLIENT		0x01
#define TAG_VISU_REMOVECLIENT		0x02
#define TAG_VISU_ISREGISTERED		0x03
#define TAG_VISU_GETPAINTDATA		0x84
#define TAG_VISU_ISVALIDCLIENTID	0x05
#define TAG_VISU_POSTEVENT			0x86
#define TAG_VISU_WRITEIMAGEPOOL		0x07
#define TAG_VISU_POSTCLIENTREQUEST	0x10


#define TAG_VISU_REGISTERCLIENT_REPLY	0x01
#define TAG_VISU_REMOVECLIENT_REPLY		0x02
#define TAG_VISU_ISREGISTERED_REPLY		0x03
#define TAG_VISU_GETPAINTDATA_REPLY		0x84
#define TAG_VISU_ISVALIDCLIENTID_REPLY	0x05
#define TAG_VISU_POSTEVENT_REPLY		0x06
#define TAG_VISU_WRITEIMAGEPOOL_REPLY	0x07
#define TAG_VISU_POSTCLIENTREQUEST_REPLY	0x10

#define SUBT_VISU_GETPAINTDATA_REPLY_ERROR		0x01
#define SUBT_VISU_GETPAINTDATA_REPLY_START		0x02
#define SUBT_VISU_GETPAINTDATA_REPLY_DATA		0x03
#define SUBT_VISU_GETPAINTDATA_REPLY_END		0x04

#define SUBT_VISU_GETPAINTDATA_EVENT			0x01
#define SUBT_VISU_GETPAINTDATA_EVENTDATA		0x02
#define SUBT_VISU_GETPAINTDATA_INV_RECT			0x03
#define SUBT_VISU_GETPAINTDATA_CONTINUATION		0x04

#define SUBT_VISU_POSTCLIENTREQUEST_APPNAME		0x01
#define SUBT_VISU_POSTCLIENTREQUEST_REQUEST		0x02		
/* END Visu Tags */

/* Return Values */
#define STATE_VALID_IECID			0x00
#define STATE_UNSET_IECID			0x01
#define STATE_INVALID_IECID			0x02
#define STATE_INVALID_EXTERNID		0x03
/* END Return Values */

#endif /* __CMPVISUSERVICES_H__ */
