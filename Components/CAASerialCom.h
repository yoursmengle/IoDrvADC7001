/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		CAACallback.h
*	Version:		2.4
*	Purpose:		Interface to the CAA callback handler.
*
******************************************************************************/

#ifdef CAALib

#include "CAADefines.h"

#ifdef CAA_COM

#ifndef __CAA_COM_H__
#define __CAA_COM_H__

/**
 * <description>ERROR</description>
 */
#define	COM_NO_ERROR			((CAA_ERROR)0)
#define	COM_FIRST_ERROR			((CAA_ERROR)5000)
#define	COM_TIME_OUT			((CAA_ERROR)5001)
#define	COM_ABORT				((CAA_ERROR)5002)
#define	COM_HANDLE_INVALID		((CAA_ERROR)5003)
#define	COM_ERROR_UNKNOWN		((CAA_ERROR)5004)
#define	COM_WRONG_PARAMETER		((CAA_ERROR)5005)
#define	COM_WRITE_INCOMPLETE	((CAA_ERROR)5006)
#define	COM_FIRST_MF			((CAA_ERROR)5050)
#define	COM_LAST_ERROR			((CAA_ERROR)5099)

/**
 * <description>STOPBIT</description>
 */
typedef enum
{
	COM_ONESTOPBIT		= 0,
	COM_ONE5STOPBITS	= 1,
	COM_TWOSTOPBITS		= 2
} COM_STOPBIT;

/**
 * <description>PARITY</description>
 */
typedef enum
{
	COM_EVEN	= 0,
	COM_ODD		= 1,
	COM_NONE	= 2
} COM_PARITY;

typedef struct
{
	CAA_UDINT udiParameterId;
	CAA_UDINT udiValue;
} CAA_PARAMETER;

typedef struct
{
	CAA_USINT usiListLength;
	CAA_PVOID pParamList;
	CAA_HANDLE hCom;
} COM_WOpenParams;

typedef struct
{
	CAA_HANDLE hCom;
} COM_WCloseParams;

typedef struct
{
	CAA_HANDLE hCom;
	CAA_PVOID pBuffer;
	CAA_SIZE szSize;
} COM_WWriteParams;

typedef struct
{
	CAA_HANDLE hCom;
	CAA_PVOID pBuffer;
	CAA_SIZE szBuffer;
	CAA_SIZE szSize;
} COM_WReadParams;

#endif /*__CAA_COM_H__*/
#endif /* CAA_COM */
#endif /* CAALib */
