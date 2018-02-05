/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	ModULe: 		CAATypes.c
*	Version:		2.4
*	Purpose:		Handles a special set of plattform specific data types
*
******************************************************************************/
#ifndef __CAA_TYPES_H__
#define __CAA_TYPES_H__

#ifdef CAALib

#include "CAADefines.h"

#include "CmpStd.h"

typedef RTS_IEC_UXINT		CAA_COUNT;
typedef RTS_IEC_TIME		CAA_DURATION;
typedef RTS_IEC_STRING		CAA_FILENAME[256];
typedef RTS_IEC_LREAL		CAA_FLOAT;
typedef RTS_IEC_HANDLE		CAA_HANDLE;
typedef RTS_IEC_DWORD		CAA_IDENT;
typedef void*				CAA_PVOID;
typedef RTS_IEC_INT			CAA_SIGNED;
typedef RTS_IEC_UXINT		CAA_SIZE;
typedef RTS_IEC_UXINT		CAA_TICK;
typedef RTS_IEC_UINT		CAA_UNSIGNED;

typedef RTS_IEC_TIME 		CAA_TIME;
typedef RTS_IEC_LTIME 		CAA_LTIME;
typedef RTS_IEC_TOD 		CAA_TOD; /* TIME_OF_DAY */
typedef RTS_IEC_DT	 		CAA_DT;  /* DATE_AND_TIME */
typedef RTS_IEC_DATE 		CAA_DATE;
typedef RTS_IEC_BYTE 		CAA_BYTE;
typedef RTS_IEC_WORD 		CAA_WORD;
typedef RTS_IEC_DWORD 		CAA_DWORD;
typedef RTS_IEC_SINT		CAA_SINT;
typedef RTS_IEC_USINT		CAA_USINT;
typedef RTS_IEC_INT			CAA_INT;
typedef RTS_IEC_UINT 		CAA_UINT;
typedef RTS_IEC_DINT		CAA_DINT;
typedef RTS_IEC_UDINT 		CAA_UDINT;
typedef RTS_IEC_LINT	 	CAA_LINT;
typedef RTS_IEC_ULINT		CAA_ULINT;
typedef RTS_IEC_REAL		CAA_REAL;
typedef RTS_IEC_LREAL		CAA_LREAL;
typedef RTS_IEC_WSTRING		CAA_WSTRING;
typedef RTS_IEC_STRING		CAA_STRING;

typedef CAA_INT				CAA_ENUM;
typedef CAA_INT				CAA_ERROR;
typedef CAA_USINT			CAA_BOOL;

#ifdef CPLUSPLUS
#define CAA_pNULL			0
#else
#define CAA_pNULL			(CAA_PVOID)0UL
#endif

#define CAA_hINVALID		(CAA_HANDLE)0UL
#define CAA_szZERO			(CAA_SIZE)0UL
#define CAA_ctMAX_COUNT		(CAA_COUNT)(~((CAA_COUNT)0))
#define CAA_idMAX_IDENT		(CAA_IDENT)(~((CAA_IDENT)0))

#define CAA_FALSE			(CAA_USINT)0
#define CAA_TRUE			(CAA_USINT)1

#define CAA_SET_RESULT(p,r) if(p) *(p)=(CAA_ERROR)(r)

#endif /* __CAA_TYPES_H__ */
#endif /* CAALib */
