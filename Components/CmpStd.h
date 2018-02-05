/**
 * <name>CmpStd.h</name>
 * <description> 
 *	<p>This is the standard header file of the runtime system, that must be included as the first file in every component!</p>
 *	<p>sysdefines.h ist included here as the first file. The platform specific defines must be set here.</p>
 *	<ul>
 *		<li>STATIC_LINK, MIXED_LINK, DYNAMIC_LINK(default) and CPLUSPLUS.</li>
 *		<li>RTS_LITTLEENDIAN_BYTEORDER or RTS_BIGENDIAN_BYTEORDER / RTS_BIGENDIAN_BITORDER
 *			Backward compatibility: INTEL_BYTE_ORDER or MOTOROLA_BYTE_ORDER  			
 *		</li>
 *		<li>RTS_SIXTEENBITBYTES for a DSP platform (e.g. Texas Instruments TI28x)</li>
 *		<li>BASETYPES_DEFINED to overload all standard types</li>
 *		<li>IECBASETYPES_DEFINED to overload all IEC standard types</li>
 *	</ul>
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */

#ifndef __RTSSTD_H__
#define __RTSSTD_H__

#include "sysdefines.h"

#ifndef RC_INVOKED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <ctype.h>
#include <math.h>

/**
 * <category>Compiler switch</category>
 * <description>
 *	Compiler switches to specify the byteorder of the runtime.
 * </description>
 * <element name="RTS_LITTLEENDIAN_BYTEORDER">Switch to specify the little endian byteorder</element>
 * <element name="RTS_BIGENDIAN_BYTEORDER">Switch to specify the big endian byteorder</element>
 */
#if defined(MOTOROLA_BYTE_ORDER) && !defined(RTS_BIGENDIAN_BYTEORDER)
	#define RTS_BIGENDIAN_BYTEORDER
#endif
#if defined(RTS_BIGENDIAN_BYTEORDER) && !defined(MOTOROLA_BYTE_ORDER)
	#define MOTOROLA_BYTE_ORDER	
#endif
#if !defined(RTS_BIGENDIAN_BYTEORDER)
	#if defined(INTEL_BYTE_ORDER) && !defined(RTS_LITTLEENDIAN_BYTEORDER)
		#define RTS_LITTLEENDIAN_BYTEORDER
	#endif
	#if defined(RTS_LITTLEENDIAN_BYTEORDER) && !defined(INTEL_BYTE_ORDER)
		#define INTEL_BYTE_ORDER
	#endif	
#endif

/*
 * Portable integer and memsize-types are included here.
 * Some operations with integers and pointers (LOWWORD, etc.) have also been
 * moved to cstdtypes.h																														
 */
#include "cstdtypes.h"
#include "CmpErrors.h"
#include "LogInfoIds.h"

#ifdef __cplusplus
	#define EXTERNC		extern "C"
	#define VIRTUAL		virtual
#else
	#define EXTERNC
#endif

typedef void*	OBJREF;

#endif /* RC_INVOKED */

/*
 * The RTS_VERSION below is to be changed only by 3S - Smart Software Solutions. 
 */
#define RTS_VERSION							UINT32_C(0x03050C01)
#define RTS_VERSION_STRING					"3.5.12.1"
#define RTS_VERSION_RC						3,5,12,1

#define RTS_GETVERSION_MAJOR(version)		(((version)>>24) & UINT32_C(0x000000FF))
#define RTS_GETVERSION_SUB(version)			(((version)>>16) & UINT32_C(0x000000FF))
#define RTS_GETVERSION_SERVICEPACK(version)	(((version)>>8) & UINT32_C(0x000000FF))
#define RTS_GETVERSION_PATCH(version)		((version) & UINT32_C(0x000000FF))

#define RTS_SETVERSION(major, minor, servicepack, patch)		(((major & UINT32_C(0x000000FF)) << 24) | \
																 ((minor & UINT32_C(0x000000FF)) << 16) | \
																 ((servicepack & UINT32_C(0x000000FF)) << 8) | \
																 (patch & UINT32_C(0x000000FF)))

#ifndef RTS_PRODUCT_FAMILY_NAME
	#define RTS_PRODUCT_FAMILY_NAME			"CODESYS"
#endif

#ifndef RTS_PRODUCT_NAME
	#define RTS_PRODUCT_NAME				RTS_PRODUCT_FAMILY_NAME" Control"
#endif

#ifndef RTS_CONFIGURATION_FILE
	#define RTS_CONFIGURATION_FILE			RTS_PRODUCT_FAMILY_NAME"Control.cfg"
#endif

#ifndef RC_INVOKED

#ifndef RTS_ASSERT
	#define RTS_ASSERT(a)
#endif

/*
 * Macros to export and check availability of functions in statically linked
 * runtimes. For performance reasons, those checks are disabled by default.
 * But for larger systems, they should be enabled, to avoid misconfigurations
 * of the system.
 * The macros can look, s.th. like this and should be defined in sysdefines.h:
 * #define CAL_CMGETAPI(name) s_pfCMGetAPI( name, (RTS_VOID_FCTPTR *)NULL, 0)
 * #define CAL_CMEXPAPI(name) s_pfCMRegisterAPI( name, (RTS_VOID_FCTPTR)-1, 0, 0)
 */
#ifndef CAL_CMGETAPI
	#define CAL_CMGETAPI(name) ERR_OK
#endif
#ifndef CAL_CMEXPAPI
	#define CAL_CMEXPAPI(name) ERR_OK
#endif


#if !defined(__cplusplus) /* no need for C++ */
   #if (__STDC_VERSION__ < 199901L) /* no need vor C99 or newer */
      #if defined(_MSC_VER) && !defined(inline)
        #define inline __inline
      #endif
  #endif
#endif


/**
 * This define specifies, that the bits inside of a bitfield are
 * organized in oposite order. Usually this is the case for
 * platforms with motorola byte order, but some compilers are
 * doing it differently.
 */
#ifndef RTS_BIGENDIAN_BITORDER
	#if defined(MOTOROLA_BYTE_ORDER) || defined(RTS_BIGENDIAN_BYTEORDER)
		#define RTS_BIGENDIAN_BITORDER
	#endif
#endif


#define RTS_MAXSTR				80

#ifndef _RTS_VOID_FCTPTR
	#define _RTS_VOID_FCTPTR
	typedef void HUGEPTR(CDECL *RTS_VOID_FCTPTR)(void);
#endif

/*
 * Runtime system basic typedefinitions.
 * Defines some types with special meaning. Systems not using standard type sizes 
 * must redefine this types in sysdefines.h and set BASETYPES_DEFINED
 */

#ifndef RTS_I64_CONST
	#define RTS_I64_CONST(a)	(a##LL)
#endif
#ifndef RTS_UI64_CONST
	#define RTS_UI64_CONST(a)	(a##ULL)
#endif

#ifndef BASETYPES_DEFINED
#	define BASETYPES_DEFINED

	typedef int8_t				RTS_I8;		/* Signed 8 bit value */
	typedef int16_t				RTS_I16;	/* Signed 16 bit value */
#ifndef RTS_I32_DEFINED
	#define RTS_I32_DEFINED
	typedef int32_t				RTS_I32; 	/* Signed 32 bit value */
#endif

	typedef uint8_t				RTS_UI8;	/* Unsigned 8 bit value */
#	define	RTS_UI8_MAX			(RTS_UI8)(~((RTS_UI8)0))

	typedef uint16_t			RTS_UI16;	/* Unsigned 16 bit value */
#	define	RTS_UI16_MAX		(RTS_UI16)(~((RTS_UI16)0))

#ifndef RTS_UI32_DEFINED
	#define RTS_UI32_DEFINED
	typedef uint32_t			RTS_UI32;	/* Unsigned 32 bit value */
#endif	
#	define	RTS_UI32_MAX		(RTS_UI32)(~((RTS_UI32)0))

#ifndef IEEE754TYPES_DEFINED
#	define IEEE754TYPES_DEFINED
	typedef float				RTS_REAL32;		/* 32 bit floating point value */
	typedef double				RTS_REAL64;		/* 64 bit floating point value */
	#define RTS_REAL32_MAX		3.4028234e+38
	#define RTS_REAL64_MAX		1.7976931348623157e+308
#endif

	typedef void*				RTS_HANDLE;		/* Handle for files, semaphores, ... Usually the native integer type of the platform*/
	#define RTS_INVALID_HANDLE	((RTS_HANDLE)(~((uintptr_t)0)))

	typedef RTS_UI32			RTS_RESULT;		/* Result type for most functions. At least 16 bit. Should be the natural integer of a platform. */

	typedef uintptr_t			RTS_UINTPTR;	/* Unsigned integral type that can hold a pointer */
	#define RTS_UINTPTR_MAX		(RTS_UINTPTR)(~((RTS_UINTPTR)0))

	typedef intptr_t			RTS_INTPTR;		/* Signed integral type that can hold a pointer */
	#define RTS_INTPTR_MAX		(RTS_INTPTR)(~((RTS_INTPTR)0))

#ifndef RTS_SIZE_DEFINED
#	define RTS_SIZE_DEFINED
	typedef size_t				RTS_SIZE;	/* Unsigned integral type that can hold a buffer offset */
#endif
	#define RTS_SIZE_MAX		(RTS_SIZE)(~((RTS_SIZE)0))

	typedef ptrdiff_t			RTS_PTRDIFF;	/* Signed integral type that can hold an array index */

#ifndef RTS_SSIZE_DEFINED
#	define RTS_SSIZE_DEFINED
	typedef RTS_PTRDIFF	RTS_SSIZE;			/* integral type that can hold a buffer offset */
#endif
	#define RTS_SSIZE_MAX		(RTS_SSIZE)(~((RTS_SSIZE)0))

	typedef RTS_UINTPTR	RTS_TIME;			/* Coordinated Universal Time (UTC) */

	typedef int					RTS_INT;	/* Data type has no constant size, so be careful in sharing shuch datatypes with IEC! */
	typedef int					RTS_BOOL;	/* Boolean value (TRUE or FALSE). For best performance use platform specific int.
											   Data type has no constant size, so be carful in sharing shuch datatypes with IEC! */

#if !defined(BASE64BITTYPES_DEFINED) && !defined(SYSINTERNAL_DISABLE_64BIT)
#	define	BASE64BITTYPES_DEFINED
	typedef uint64_t			RTS_UI64;
	typedef int64_t				RTS_I64;
	#define RTS_UI64_MAX		(RTS_UI64)(~((RTS_UI64)0))
	#define RTS_I64_MAX			(RTS_I64)(~((RTS_I64)0))
#endif

	typedef char				RTS_CSTRING;

#	ifndef RTS_WCHAR_DEFINED
#		define RTS_WCHAR_DEFINED
		typedef wchar_t			RTS_WCHAR;	/* wide character value. We expect 2 bytes unicode here! */
#	endif	/*RTS_WCHAR_DEFINED*/

#	ifndef RTS_CWCHAR_DEFINED
#		define RTS_CWCHAR_DEFINED
#		ifdef RTS_UNICODE
			typedef RTS_WCHAR	RTS_CWCHAR;
#		else
			typedef RTS_CSTRING	 RTS_CWCHAR;
#		endif
#	endif	/*RTS_CWCHAR_DEFINED*/
#endif /*BASETYPES_DEFINED*/


/*
 * IEC basic typedefinitions.
 * Defines all datatypes used in IEC programs. Datatypes must match to CoDeSys compiler.
 * Systems that overloads standard types must redefine this types in sysdefines.h and set IECBASETYPES_DEFINED
 */
#ifndef IECBASETYPES_DEFINED
#define IECBASETYPES_DEFINED

#	define RTS_IEC_VOID_FCTPTR		RTS_VOID_FCTPTR
	typedef void*			RTS_IEC_VOIDPTR;

	typedef RTS_I8			RTS_IEC_BOOL;
	typedef RTS_I8			RTS_IEC_SINT;
	typedef RTS_UI8			RTS_IEC_USINT;
	typedef RTS_UI8			RTS_IEC_BYTE;
	typedef RTS_I16			RTS_IEC_INT;
	typedef RTS_UI16		RTS_IEC_UINT;
	typedef RTS_UI16		RTS_IEC_WORD;
	typedef RTS_I32			RTS_IEC_DINT;
	typedef RTS_UI32		RTS_IEC_UDINT;
	typedef RTS_UI32		RTS_IEC_DWORD;

	typedef RTS_UI32		RTS_IEC_TIME;
	typedef RTS_UI32		RTS_IEC_TIME_OF_DAY;
	typedef RTS_UI32		RTS_IEC_TOD;
	typedef RTS_UI32		RTS_IEC_DATE_AND_TIME;
	typedef RTS_UI32		RTS_IEC_DT;
	typedef RTS_UI32		RTS_IEC_DATE;
	
	typedef RTS_I64			RTS_IEC_LINT;
	typedef RTS_UI64		RTS_IEC_ULINT;
	typedef RTS_UI64		RTS_IEC_LWORD;
	typedef RTS_UI64		RTS_IEC_LTIME;

	typedef RTS_SIZE		RTS_IEC_XWORD;
	typedef RTS_UINTPTR		RTS_IEC_UXINT;
	typedef RTS_PTRDIFF		RTS_IEC_XINT;

	typedef RTS_REAL32		RTS_IEC_REAL;
	typedef RTS_REAL64		RTS_IEC_LREAL;

	typedef RTS_CSTRING		RTS_IEC_STRING;
#	ifdef RTS_UNICODE
		typedef RTS_WCHAR	RTS_IEC_WSTRING;
#	else
		typedef RTS_UI16	RTS_IEC_WSTRING;
#	endif
	typedef RTS_CWCHAR		RTS_IEC_CWCHAR;

	typedef RTS_SIZE		RTS_IEC_SIZE;
	typedef RTS_HANDLE		RTS_IEC_HANDLE;
	typedef RTS_IEC_UDINT	RTS_IEC_RESULT;
#endif	/*IECBASETYPES_DEFINED*/

/* <SIL2/> */
typedef struct tagRTS_GUID
{
	RTS_UI32 data1;
	RTS_UI16 data2;
	RTS_UI16 data3;
#ifdef RTS_SIXTEENBITBYTES
	RTS_UI16 data4[4];
#else
	RTS_UI8 data4[8];
#endif
} RTS_GUID;

#ifndef RTS_MEM_REGION_DEFINED
#define RTS_MEM_REGION_DEFINED

/**
 *	<description>
 *	 Abstract Memory Region.
 *	</description>
 */  
typedef struct tagRTS_MEM_REGION
{
	/* base address of the region */
	RTS_UINTPTR base;

	/* region size */
	RTS_SIZE		size;

} RTS_MEM_REGION;
#endif

#ifndef EXT_FUNCT_REF_DEFINED
#define EXT_FUNCT_REF_DEFINED
/**
 *	Exported function descriptor
 */
typedef struct tagCMP_EXT_FUNCTION_REF
{
	/* pointer to an exported function */
	RTS_VOID_FCTPTR	pfExtCall;

	/* name of an exported function */
	const char*			pszExtCallName;

	/* signature */
	RTS_UI32				signature;

	/* version */
	RTS_UI32				version;

} CMP_EXT_FUNCTION_REF;
#endif

/* The CMGetAPI2/CMGetAPI3 importOptions parameter flag which specifies an import */
/* as a required function (error if it is unresolved) */
#define CM_IMPORT_REQUIRED_FUNCTION			0

/* The CMGetAPI2/CMGetAPI3 importOptions parameter flag which specifies an import */
/* as an external libray function */
#define CM_IMPORT_EXTERNAL_LIB_FUNCTION		1

/* The CMGetAPI2/CMGetAPI3 importOptions parameter flag which specifies an import */
/* as an optional function */
#define CM_IMPORT_OPTIONAL_FUNCTION			2

/* Imported function belongs to an external libray */
#define ImportIsExternalLibFunction(par) (0 != ((par) & CM_IMPORT_EXTERNAL_LIB_FUNCTION))

/* Imported function is optional */
#define ImportIsOptionalFunction(par) (0 != ((par) & CM_IMPORT_OPTIONAL_FUNCTION))


/**
 * <category>Handling of Infinity</category>
 * <description>
 *     Check Macros to check a REAL value for positive or negative infinity.
 * </description>
 */
#ifndef RTS_IS_INFINITY_DEFINED
	#define RTS_IS_REAL32_INFINITY_POS(dVal) (*((RTS_UI32*)&dVal) == (UINT32_C(0x7f800000)))
	#define RTS_IS_REAL32_INFINITY_NEG(dVal) (*((RTS_UI32*)&dVal) == (UINT32_C(0xff800000)))
	#define RTS_IS_REAL64_INFINITY_POS(dVal) (*((RTS_UI64*)&dVal) == (RTS_UI64_CONST(0x7ff0000000000000)))
	#define RTS_IS_REAL64_INFINITY_NEG(dVal) (*((RTS_UI64*)&dVal) == (RTS_UI64_CONST(0xfff0000000000000)))
#endif


/**
 * <category>DSP specific sizeof and offset definitions</category>
 * <description>
 *	sizeof() on a DSP platform returned 1 for byte and word datatypes, so sizeof() must be handled specific.
 *	Offset calculations must be done WORD wize!
 * </description>
 */
#ifdef RTS_SIXTEENBITBYTES
	#define sizeof_RTS_I8					1
	#define sizeof_RTS_UI8					1
	#define sizeof_RTS_I16					2
	#define sizeof_RTS_UI16					2
	#define sizeof_RTS_I32					4
	#define sizeof_RTS_UI32					4
	#define sizeof_RTS_UINTPTR				4
	#define sizeof_RTS_SIZE					sizeof_RTS_UINTPTR
	#define sizeof_RTS_IEC_DWORD			sizeof_RTS_UI32
	#define sizeof_RTS_RESULT				sizeof_RTS_UI32
	#define sizeof_RTS_HANDLE				sizeof_RTS_UI32
	#define sizeof_RTS_WCHAR				sizeof_RTS_UI16
	#define sizeof_RTS_GUID					16
	#define sizeof_RTS_IEC_DATE_AND_TIME	sizeof_RTS_UI32
	#define sizeof_AREA_INFO				(sizeof(AREA_INFO) * 2)
	#define sizeof_EXT_REF_INFO				(sizeof(EXT_REF_INFO) * 2)
	#define sizeof_ADDRESSCOMPONENT         sizeof(ADDRESSCOMPONENT)
	#define sizeof_CMPID					sizeof_RTS_UI32

	#define RTS_SIZEOF(type)				sizeof_##type
	#define RTS_GET_WORD_OFFSET(offset)		((offset) / 2)
	#define RTS_GET_WORD_SIZE				RTS_GET_WORD_OFFSET
	#define RTS_GET_BYTE_OFFSET(offset)		((offset) * 2)
	#define RTS_GET_BYTE_SIZE				RTS_GET_BYTE_OFFSET
	#define RTS_MEMSET(dest, c, count)		memset(dest, c, count / 2)
	#define RTS_ALIGN_4BYTES				2
	#define RTS_BITS_IN_BYTE				16
#else
	#define RTS_SIZEOF						sizeof
	#define RTS_GET_WORD_OFFSET(typesize)	(typesize)
	#define RTS_GET_WORD_SIZE				RTS_GET_WORD_OFFSET
	#define RTS_GET_BYTE_OFFSET(offset)		(offset)
	#define RTS_GET_BYTE_SIZE(size)			(size)
	#define RTS_MEMSET						memset
	#define RTS_ALIGN_4BYTES				4
	#define RTS_BITS_IN_BYTE				8
#endif


#define RTS_TIMEOUT_INFINITE	(~(RTS_UI32)0)
#define RTS_TIMEOUT_DEFAULT		(RTS_UI32)(-2)
#define RTS_TIMEOUT_NO_WAIT		(0)

#include "CmpItf.h"

#ifdef PLC_HANDLER
	#include "CmpPLCHandler.h"
#endif

/* 
 * This file must exist in a systemspecific include directory (eg. <rts_src>\Win32) 
 * and may include any additional includes/definitions needed for a special system/environment.
 */
#include "sysspecific.h"


#ifdef PREFER_PORTABLE_SNPRINTF

/* Portable snprintf routines are implemented in CMConvToStr.c */
#ifdef CPLUSPLUS
extern "C"
{
#endif
	int CDECL CMUtlPortableSnprintf(char* str, RTS_SIZE buf_len, const char* fmt, ...);
	int CDECL CMUtlPortableVsnprintf(char* str, RTS_SIZE buf_len, const char* fmt, va_list ap);
#ifdef CPLUSPLUS
}
#endif

#	ifdef RTS_VSNPRINTF
#	undef RTS_VSNPRINTF
#	define RTS_VSNPRINTF(s,len,format,arglist) CMUtlPortableVsnprintf((s), (len), (format), (arglist))
#	endif

#endif


#ifndef  COMPONENT_NAME_POSTFIX
	#define COMPONENT_NAME_POSTFIX
#endif

#ifdef RTS_COMPACT
	#ifdef RTS_STRUCTURED_EXCEPTION_HANDLING
		#define RTS_IECTASK_STRUCTURED_EXCEPTION_HANDLING
	#endif
#endif

#ifdef TRG_64BIT
#	ifndef CM_OBJECT_MANAGER_ENABLED
#		define CM_OBJECT_MANAGER_ENABLED
#	endif
#else
	#define CMPOBJECTMGR_NOTIMPLEMENTED
#endif

#endif /* RC_INVOKED */

#endif /*__RTSSTD_H__*/
