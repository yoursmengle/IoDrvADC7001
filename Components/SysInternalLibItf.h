 /**
 * <interfacename>SysInternalLib</interfacename>
 * <description> 
 *	<p>The SysInternalLib interface is projected to implement all platform dependant routines for:
 *	<ul>
 *		<li>Standard library routines</li>
 *		<li>Datatype conversion</li>
 *	</ul>
 *	This routines are used by CoDeSys for the Iec standard library implementation.</p>
 *
 *	<p>If the define SYSINTERNALLIB_DISABLE_INT_DIVBYZERO_CHECK is set, you can disable checking all int divisions on a zero divisor.</p>
 *	<p>If the define SYSINTERNALLIB_DISABLE_REAL_DIVBYZERO_CHECK is set, you can disable checking all real divisions on a zero divisor.</p>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSINTERNALLIBITF_H_
#define _SYSINTERNALLIBITF_H_

#include "CmpStd.h"

 

 




#if defined(SYSINTERNAL_DISABLE_64BIT) && !defined(SYSINTERNALLIB_DISABLE_EXTREF2)
#	define SYSINTERNALLIB_DISABLE_EXTREF2
#endif

#ifndef CDECL
	#define CDECL
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <SIL2/>
 * <category>Type class</category>
 * <description>
 *  Describes the type class correspoding to an <see>IIECType</see> instance.
 * </description>
 */
typedef enum 
{
	TYPE3_BOOL,
	TYPE3_BIT,
	TYPE3_BYTE,
	TYPE3_WORD,
	TYPE3_DWORD,
	TYPE3_LWORD,
	TYPE3_SINT,
	TYPE3_INT,
	TYPE3_DINT,
	TYPE3_LINT,
	TYPE3_USINT,
	TYPE3_UINT,
	TYPE3_UDINT,
	TYPE3_ULINT,
	TYPE3_REAL,
	TYPE3_LREAL,
	TYPE3_STRING,
	TYPE3_WSTRING,
	TYPE3_TIME,
	TYPE3_DATE,
	TYPE3_DATEANDTIME,
	TYPE3_TIMEOFDAY,
	TYPE3_POINTER,
	TYPE3_REFERENCE,
	TYPE3_SUBRANGE,
	TYPE3_ENUM,
	TYPE3_ARRAY,
	TYPE3_PARAMS,
	TYPE3_USERDEF,
	TYPE3_NONE,
	TYPE3_ANY,		/* all types */
	TYPE3_ANYBIT,	/* all "bit"-types: bit, byte, word, dword, lword */
	TYPE3_ANYDATE,	/* time, dat, tod, date*/
	TYPE3_ANYINT, 
	TYPE3_ANYNUM, 
	TYPE3_ANYREAL,
	TYPE3_LAZY,
	TYPE3_LTIME,
	TYPE3_BITCONST,
	TYPE3_MAX_TYPE 
} TypeClass3;

#define TYPECLASS3_SIZE(varname) \
static const unsigned int varname[] = { \
	1 /* TYPE3_BOOL */, \
	1 /* TYPE3_BIT */, \
	1 /* TYPE3_BYTE */, \
	2 /* TYPE3_WORD */, \
	4 /* TYPE3_DWORD */, \
	8 /* TYPE3_LWORD */, \
	1 /* TYPE3_SINT */, \
	2 /* TYPE3_INT */, \
	4 /* TYPE3_DINT */, \
	8 /* TYPE3_LINT */, \
	1 /* TYPE3_USINT */, \
	2 /* TYPE3_UINT */, \
	4 /* TYPE3_UDINT */, \
	8 /* TYPE3_ULINT */, \
	4 /* TYPE3_REAL */, \
	8 /* TYPE3_LREAL */, \
	1 /* TYPE3_STRING */, \
	2 /* TYPE3_WSTRING */, \
	4 /* TYPE3_TIME */, \
	4 /* TYPE3_DATE */, \
	4 /* TYPE3_DATEANDTIME */, \
	4 /* TYPE3_TIMEOFDAY */, \
	0 /* TYPE3_POINTER */, \
	0 /* TYPE3_REFERENCE */, \
	0 /* TYPE3_SUBRANGE */, \
	0 /* TYPE3_ENUM */, \
	0 /* TYPE3_ARRAY */, \
	0 /* TYPE3_PARAMS */, \
	0 /* TYPE3_USERDEF */, \
	0 /* TYPE3_NONE */, \
	0 /* TYPE3_ANY */, \
	0 /* TYPE3_ANYBIT */, \
	0 /* TYPE3_ANYDATE */, \
	0 /* TYPE3_ANYINT */, \
	0 /* TYPE3_ANYNUM */, \
	0 /* TYPE3_ANYREAL */, \
	0 /* TYPE3_LAZY */, \
	8 /* TYPE3_LTIME */, \
	0 /* TYPE3_BITCONST */ \
}

/********** Structures **********/

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for a memcopy wrapper.</description>
 */
typedef struct
{
	RTS_IEC_VOIDPTR pDest;
	RTS_IEC_VOIDPTR pSrc;
	RTS_IEC_DWORD dwSize;
	RTS_IEC_VOIDPTR pRet;
}__memcopy_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for a strcmp wrapper.</description>
 */
typedef struct
{
	RTS_IEC_STRING* pString1;
	RTS_IEC_STRING* pString2;
	RTS_IEC_DINT diRet;
}__stringcompare_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for a wstrcmp wrapper.</description>
 */
typedef struct
{
	RTS_IEC_WSTRING* pWString1;
	RTS_IEC_WSTRING* pWString2;
	RTS_IEC_DINT diRet;
}__wstringcompare_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for a time output as 32-bit value.</description>
 */
typedef struct
{
	RTS_IEC_DWORD out;
}get_time_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for a time output as 64-bit value.</description>
 */
typedef struct
{
	RTS_IEC_LTIME out;
}get_ltime_struct;

/**
 * <category>External IEC interface</category>
 * <description>Struct for setting memory.</description>
 */
typedef struct
{
	RTS_IEC_BYTE *pDest;
	RTS_IEC_DINT iValue;
	RTS_IEC_DINT iCount;
	RTS_IEC_BYTE *__MemSet;
} __memset_struct;

/**
 * <category>Type class</category>
 * <description>
 *  This flag describes additional properties of the try-block
 * </description>
 * <element name="EX_STOP"></element>
 */
#define TRYEXC_FLAG_STOP		0x1

/**
 * <category>External IEC interface</category>
 * <description>Struct for registering an exception handler within IEC.</description>
 */
typedef struct
{
	RTS_IEC_VOIDPTR **pFun;				/*in : pointer to Function pointer of IEC_Function to call*/
	RTS_IEC_VOIDPTR *pParam;			/*in : Pointer to parameters*/
	RTS_IEC_DWORD dwFlags;				/*in : flags for exception handling: at the moment only disable exception handling*/
	RTS_IEC_DINT* pExceptionCode;		/*out : kind of exception, 0 == no exception*/
	RTS_IEC_DINT result;				/*out : kind of exception, 0 == no exception*/
}trycatch_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct to compare two 32-bit real values.</description>
 */
typedef struct
{
	RTS_IEC_REAL in1;
	RTS_IEC_REAL in2;
	RTS_IEC_SINT out;
}real_cmp_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for operation with three 32-bit real values.</description>
 */
typedef struct 
{
	RTS_IEC_REAL in1;
	RTS_IEC_REAL in2;
	RTS_IEC_REAL in3;
	RTS_IEC_REAL out;
}real_3op_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for operation with two 32-bit real values.</description>
 */
typedef struct 
{
	RTS_IEC_REAL in1;
	RTS_IEC_REAL in2;
	RTS_IEC_REAL out;
}real_2op_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for operation with one 32-bit real value.</description>
 */
typedef struct 
{
	RTS_IEC_REAL in;
	RTS_IEC_REAL out;
}real_1op_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct to compare two 64-bit real values.</description>
 */
typedef struct 
{
	RTS_IEC_LREAL in1;
	RTS_IEC_LREAL in2;
	RTS_IEC_SINT  out;
}lreal_cmp_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for operation with three 64-bit real values.</description>
 */
typedef struct 
{
	RTS_IEC_LREAL in1;
	RTS_IEC_LREAL in2;
	RTS_IEC_LREAL in3;
	RTS_IEC_LREAL out;
}lreal_3op_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for conversion of a 32-bit real value to a 32-bit integer value.</description>
 */
typedef struct
{
	RTS_IEC_REAL in;
	RTS_IEC_DINT out;
}real_trunc_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for conversion of a 64-bit real value to a 32-bit integer value.</description>
 */
typedef struct
{
	RTS_IEC_LREAL in;
	RTS_IEC_DINT  out;
}lreal_trunc_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for operation with two 64-bit real values.</description>
 */
typedef struct 
{
	RTS_IEC_LREAL in1;
	RTS_IEC_LREAL in2;
	RTS_IEC_LREAL out;
}lreal_2op_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for operation with one 64-bit real value.</description>
 */
typedef struct 
{
	RTS_IEC_LREAL in;
	RTS_IEC_LREAL out;
}lreal_1op_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct to compare two 64-bit integer values.</description>
 */
typedef struct 
{
	RTS_IEC_LINT in1;
	RTS_IEC_LINT in2;
	RTS_IEC_SINT out;
}lint_cmp_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for operation with three 64-bit integer values.</description>
 */
typedef struct 
{
	RTS_IEC_LINT in1;
	RTS_IEC_LINT in2;
	RTS_IEC_LINT in3;
	RTS_IEC_LINT out;
}lint_3op_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for operation with two 64-bit integer values.</description>
 */
typedef struct 
{
	RTS_IEC_LINT in1;
	RTS_IEC_LINT in2;
	RTS_IEC_LINT out;
}lint_2op_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for operation with one 64-bit integer value.</description>
 */
typedef struct 
{
	RTS_IEC_LINT in;
	RTS_IEC_LINT out;
}lint_1op_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct to compare two 64-bit unsigned integer values.</description>
 */
typedef struct 
{
	RTS_IEC_ULINT in1;
	RTS_IEC_ULINT in2;
	RTS_IEC_SINT  out;
}ulint_cmp_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for operation with three 64-bit unsigned integer values.</description>
 */
typedef struct 
{
	RTS_IEC_ULINT in1;
	RTS_IEC_ULINT in2;
	RTS_IEC_ULINT in3;
	RTS_IEC_ULINT out;
}ulint_3op_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for operation with two 64-bit unsigned integer values.</description>
 */
typedef struct 
{
	RTS_IEC_ULINT in1;
	RTS_IEC_ULINT in2;
	RTS_IEC_ULINT out;
}ulint_2op_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for shift operations on a 64-bit unsigned integer value.</description>
 */
typedef struct 
{
	RTS_IEC_ULINT in1;
	RTS_IEC_UINT  in2;
#ifdef RTS_SIXTEENBITBYTES
	RTS_IEC_USINT dummy[3];
#else
	RTS_IEC_USINT dummy[6];
#endif
	RTS_IEC_ULINT out;
}ulint_shift_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for shift operations on a 64-bit integer value.</description>
 */
typedef struct 
{
	RTS_IEC_LINT  in1;
	RTS_IEC_UINT  in2;
#ifdef RTS_SIXTEENBITBYTES
	RTS_IEC_USINT dummy[3];
#else
	RTS_IEC_USINT dummy[6];
#endif
	RTS_IEC_LINT  out;
}lint_shift_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for operation with one 64-bit unsigned integer value.</description>
 */
typedef struct 
{
	RTS_IEC_ULINT in;
	RTS_IEC_ULINT out;
}ulint_1op_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for operation with one 32-bit integer value.</description>
 */
typedef struct 
{
	RTS_IEC_DINT in;
	RTS_IEC_DINT out;
}dint_1op_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for operation with two 32-bit integer values.</description>
 */
typedef struct 
{	RTS_IEC_DINT in1;
	RTS_IEC_DINT in2;
	RTS_IEC_DINT out;
}dint_2op_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for operation with three 32-bit integer values.</description>
 */
typedef struct 
{
	RTS_IEC_DINT in1;
	RTS_IEC_DINT in2;
	RTS_IEC_DINT in3;
	RTS_IEC_DINT out;
}dint_3op_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for shift operations on a 32-bit integer value.</description>
 */
typedef struct 
{
	RTS_IEC_DINT in1;
	RTS_IEC_INT	 in2;
#ifndef TRG_C16X
	RTS_IEC_INT	 dummy;
#endif
	RTS_IEC_DINT out;
}dint_shift_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for operation with two 32-bit unsigned integer values.</description>
 */
typedef struct 
{
	RTS_IEC_UDINT in1;
	RTS_IEC_UDINT in2;
	RTS_IEC_UDINT out;
}udint_2op_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for operation with three 32-bit unsigned integer values.</description>
 */
typedef struct 
{
	RTS_IEC_UDINT in1;
	RTS_IEC_UDINT in2;
	RTS_IEC_UDINT in3;
	RTS_IEC_UDINT out;
}udint_3op_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for shift operations on a 32-bit unsigned integer value.</description>
 */
typedef struct 
{
	RTS_IEC_UDINT in1;
	RTS_IEC_INT	  in2;
#ifndef TRG_C16X
	RTS_IEC_INT	  dummy;
#endif
	RTS_IEC_UDINT out;
}udint_shift_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for conversion of a 64-bit integer value to any 32-bit value.</description>
 */
typedef struct
{
	RTS_IEC_ULINT in;
	RTS_IEC_UDINT uiType;
	RTS_IEC_UDINT out;	
}int64_to_any32_struct;

/**
 * <category>External IEC interface</category>
 * <description>Struct to read a 64-bit integer value atomic.</description>
 */
typedef struct
{
	RTS_IEC_ULINT *pSrc;
	RTS_IEC_ULINT out;	
}int64_atomicread_struct;

/**
 * <category>External IEC interface</category>
 * <description>Struct to read a 64-bit integer value atomic.</description>
 */
typedef struct
{
	RTS_IEC_ULINT *pDest;
	RTS_IEC_ULINT write;
	RTS_IEC_RESULT out;	
}int64_atomicwrite_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for conversion of any 32-bit value to a 64-bit integer value.</description>
 */
typedef struct
{
	RTS_IEC_UDINT in;
	RTS_IEC_UDINT uiType;
	RTS_IEC_ULINT out;
}any32_to_int64_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for conversion of a 32-bit real value to any 32-bit value.</description>
 */
typedef struct
{
	RTS_IEC_REAL  in;
	RTS_IEC_UDINT uiType;
	RTS_IEC_UDINT out;
}real32_to_any32_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for conversion of any 32-bit value to a 32-bit real value.</description>
 */
typedef struct
{
	RTS_IEC_UDINT in;
	RTS_IEC_UDINT uiType;
	RTS_IEC_REAL  out;
}any32_to_real32_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for conversion of a 32-bit real value to any 64-bit value.</description>
 */
typedef struct
{
	RTS_IEC_REAL  in;
	RTS_IEC_UDINT uiType;
	RTS_IEC_ULINT out;
}real32_to_any64_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for conversion of any 64-bit value to a 32-bit real value.</description>
 */
typedef struct
{
	RTS_IEC_ULINT in;
	RTS_IEC_UDINT uiType;
	RTS_IEC_REAL  out;
}any64_to_real32_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for conversion of a 64-bit real value to any 32-bit value.</description>
 */
typedef struct
{
	RTS_IEC_LREAL in;
	RTS_IEC_UDINT uiType;
	RTS_IEC_UDINT out;
}real64_to_any32_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for conversion of any 32-bit value to a 64-bit real value.</description>
 */
typedef struct
{
	RTS_IEC_UDINT in;
	RTS_IEC_UDINT uiType;
	RTS_IEC_LREAL out;
}any32_to_real64_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for conversion of a 64-bit real value to any 64-bit value.</description>
 */
typedef struct
{
	RTS_IEC_LREAL in;
	RTS_IEC_UDINT uiType;
	RTS_IEC_UDINT dummy;
	RTS_IEC_ULINT out;	
}real64_to_any64_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for conversion of any 64-bit value to a 64-bit real value.</description>
 */
typedef struct
{
	RTS_IEC_ULINT in;	
	RTS_IEC_UDINT uiType;
	RTS_IEC_UDINT dummy;
	RTS_IEC_LREAL out;
}any64_to_real64_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for conversion of a 64-bit real value to a 32-bit real value.</description>
 */
typedef struct 
{
	RTS_IEC_LREAL in;
	RTS_IEC_REAL  out;
}real64_to_real32_struct;

/**
 * <SIL2/>
 * <category>External IEC interface</category>
 * <description>Struct for conversion of a 32-bit real value to a 64-bit real value.</description>
 */
typedef struct 
{
	RTS_IEC_REAL  in;
	RTS_IEC_UDINT dummy;
	RTS_IEC_LREAL out;
}real32_to_real64_struct;

/**
 * <category>External IEC interface</category>
 * <description>Struct to read a 64-bit integer value atomic.</description>
 */
typedef struct
{
	RTS_IEC_LREAL *pSrc;
	RTS_IEC_LREAL out;	
}real64_atomicread_struct;

/**
 * <category>External IEC interface</category>
 * <description>Struct to read a 64-bit integer value atomic.</description>
 */
typedef struct
{
	RTS_IEC_LREAL *pDest;
	RTS_IEC_LREAL write;
	RTS_IEC_RESULT out;	
}real64_atomicwrite_struct;


/********** Functions **********/
/**
 * <description>This function is a wrapper for a C style "memcpy" and behaves in the exact same way.</description>
 * <param name="p" type="IN" range="[VALID_MEMCOPY_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="iDestAlignmentOffset" type="IN" range="[0..7,8..15,15..31,31..63]">
 *   The parameter "pDest" is the destination pointer for the memcopy. 
 *   It has to be always valid, as there is no input parameter check.
 *   The has to support all possible alignments. "iDestAlignmentOffset"
 *   specifies the number of bytes, deviating from a 16Bit alignment.
 * </parampseudo>
 * <parampseudo name="iSrcAlignmentOffset" type="IN" range="[0..7,8..15,15..31,31..63]">
 *   The parameter "pSrc" is the source pointer for the memcopy. 
 *   It has to be always valid, as there is no input parameter check.
 *   The has to support all possible alignments. "iSrcAlignmentOffset"
 *   specifies the number of bytes, deviating from a 16Bit alignment.
 * </parampseudo>
 * <parampseudo name="dwSize" type="IN" range="[0..MEMCOPY_BUFFERSIZE]">Number of bytes to be copied</parampseudo>
 * <parampseudo name="dwPattern" type="IN" range="[0xAA55AA55,0x55AA55AA,0x00000000,0xFFFFFFFF]">fill pattern, which is copied in the test</parampseudo>
 * <parampseudo name="pRet" type="OUT">Pointer to the destination buffer.</parampseudo>
 */
void CDECL CDECL_EXT __memcopy(__memcopy_struct* p);
typedef void (CDECL * PF__MEMCOPY) (__memcopy_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(__MEMCOPY_NOTIMPLEMENTED)
	#define USE___memcopy
	#define EXT___memcopy
	#define GET___memcopy(fl)  ERR_NOTIMPLEMENTED
	#define CAL___memcopy(p0) 
	#define CHK___memcopy  FALSE
	#define EXP___memcopy  ERR_OK
#elif defined(STATIC_LINK)
	#define USE___memcopy
	#define EXT___memcopy
	#define GET___memcopy(fl)  CAL_CMGETAPI( "__memcopy" ) 
	#define CAL___memcopy  __memcopy
	#define CHK___memcopy  TRUE
	#define EXP___memcopy  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__memcopy", (RTS_UINTPTR)__memcopy, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE___memcopy
	#define EXT___memcopy
	#define GET___memcopy(fl)  CAL_CMGETAPI( "__memcopy" ) 
	#define CAL___memcopy  __memcopy
	#define CHK___memcopy  TRUE
	#define EXP___memcopy  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__memcopy", (RTS_UINTPTR)__memcopy, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLib__memcopy
	#define EXT_SysInternalLib__memcopy
	#define GET_SysInternalLib__memcopy  ERR_OK
	#define CAL_SysInternalLib__memcopy  __memcopy
	#define CHK_SysInternalLib__memcopy  TRUE
	#define EXP_SysInternalLib__memcopy  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__memcopy", (RTS_UINTPTR)__memcopy, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE___memcopy
	#define EXT___memcopy
	#define GET___memcopy(fl)  CAL_CMGETAPI( "__memcopy" ) 
	#define CAL___memcopy  __memcopy
	#define CHK___memcopy  TRUE
	#define EXP___memcopy  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__memcopy", (RTS_UINTPTR)__memcopy, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE___memcopy  PF__MEMCOPY pf__memcopy;
	#define EXT___memcopy  extern PF__MEMCOPY pf__memcopy;
	#define GET___memcopy(fl)  s_pfCMGetAPI2( "__memcopy", (RTS_VOID_FCTPTR *)&pf__memcopy, (fl), 0, 0)
	#define CAL___memcopy  pf__memcopy
	#define CHK___memcopy  (pf__memcopy != NULL)
	#define EXP___memcopy   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__memcopy", (RTS_UINTPTR)__memcopy, 1, 0) 
#endif


/**
 * <description>This function is a wrapper for a C style "strcmp" and behaves in the exact same way.</description>
 * <param name="p" type="IN" range="[VALID_STRINGCOMPARE_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="iCmp1AlignmentOffset" type="IN" range="[0..7,8..15,15..31,31..63]">
 *   The parameter "pString1" is one of the compared buffers. 
 *   It has to be always valid, as there is no input parameter check.
 *   The buffer has to be terminated with a terminating zero.
 *   The has to support all possible alignments. "iCmp1AlignmentOffset"
 *   specifies the number of bytes, deviating from a 16Bit alignment.
 * </parampseudo>
 * <parampseudo name="iCmp2AlignmentOffset" type="IN" range="[0..7,8..15,15..31,31..63]">
 *   The parameter "pString2" is one of the compared buffers.
 *   It has to be always valid, as there is no input parameter check.
 *   The buffer has to be terminated with a terminating zero.
 *   The has to support all possible alignments. "iCmp2AlignmentOffset"
 *   specifies the number of bytes, deviating from a 16Bit alignment.
 * </parampseudo>
 * <parampseudo name="pString1" type="IN" range="[LOWSTRING_SHORT,LOWSTRING_LONG,HIGHSTRING_SHORT,HIGHSTRING_LONG]">String type to be copied in the test</parampseudo>
 * <parampseudo name="pString2" type="IN" range="[LOWSTRING_SHORT,LOWSTRING_LONG,HIGHSTRING_SHORT,HIGHSTRING_LONG]">String type to be copied in the test</parampseudo>
 * <parampseudo name="diRet" type="OUT">Lexicographical result of "pString1" compared to "pString2". 0 if both are equal.</parampseudo>
 */
void CDECL CDECL_EXT __stringcompare(__stringcompare_struct* p);
typedef void (CDECL * PF__STRINGCOMPARE) (__stringcompare_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(__STRINGCOMPARE_NOTIMPLEMENTED)
	#define USE___stringcompare
	#define EXT___stringcompare
	#define GET___stringcompare(fl)  ERR_NOTIMPLEMENTED
	#define CAL___stringcompare(p0) 
	#define CHK___stringcompare  FALSE
	#define EXP___stringcompare  ERR_OK
#elif defined(STATIC_LINK)
	#define USE___stringcompare
	#define EXT___stringcompare
	#define GET___stringcompare(fl)  CAL_CMGETAPI( "__stringcompare" ) 
	#define CAL___stringcompare  __stringcompare
	#define CHK___stringcompare  TRUE
	#define EXP___stringcompare  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__stringcompare", (RTS_UINTPTR)__stringcompare, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE___stringcompare
	#define EXT___stringcompare
	#define GET___stringcompare(fl)  CAL_CMGETAPI( "__stringcompare" ) 
	#define CAL___stringcompare  __stringcompare
	#define CHK___stringcompare  TRUE
	#define EXP___stringcompare  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__stringcompare", (RTS_UINTPTR)__stringcompare, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLib__stringcompare
	#define EXT_SysInternalLib__stringcompare
	#define GET_SysInternalLib__stringcompare  ERR_OK
	#define CAL_SysInternalLib__stringcompare  __stringcompare
	#define CHK_SysInternalLib__stringcompare  TRUE
	#define EXP_SysInternalLib__stringcompare  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__stringcompare", (RTS_UINTPTR)__stringcompare, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE___stringcompare
	#define EXT___stringcompare
	#define GET___stringcompare(fl)  CAL_CMGETAPI( "__stringcompare" ) 
	#define CAL___stringcompare  __stringcompare
	#define CHK___stringcompare  TRUE
	#define EXP___stringcompare  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__stringcompare", (RTS_UINTPTR)__stringcompare, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE___stringcompare  PF__STRINGCOMPARE pf__stringcompare;
	#define EXT___stringcompare  extern PF__STRINGCOMPARE pf__stringcompare;
	#define GET___stringcompare(fl)  s_pfCMGetAPI2( "__stringcompare", (RTS_VOID_FCTPTR *)&pf__stringcompare, (fl), 0, 0)
	#define CAL___stringcompare  pf__stringcompare
	#define CHK___stringcompare  (pf__stringcompare != NULL)
	#define EXP___stringcompare   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__stringcompare", (RTS_UINTPTR)__stringcompare, 1, 0) 
#endif


/**
 * <description>This function is a wrapper for a C style "wstrcmp" and behaves in the exact same way.</description>
 * <param name="p" type="IN" range="[VALID_WSTRINGCOMPARE_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="iCmp1AlignmentOffset" type="IN" range="[0,2,6,8,14,16,30,32,62,64]">
 *   The parameter "pString1" is one of the compared buffers. 
 *   It has to be always valid, as there is no input parameter check.
 *   The buffer has to be terminated with a terminating zero.
 *   The has to support all possible alignments. "iCmp1AlignmentOffset"
 *   specifies the number of bytes, deviating from a 16Bit alignment.
 * </parampseudo>
 * <parampseudo name="iCmp2AlignmentOffset" type="IN" range="[0,2,6,8,14,16,30,32,62,64]">
 *   The parameter "pString2" is one of the compared buffers.
 *   It has to be always valid, as there is no input parameter check.
 *   The buffer has to be terminated with a terminating zero.
 *   The has to support all possible alignments. "iCmp2AlignmentOffset"
 *   specifies the number of bytes, deviating from a 16Bit alignment.
 * </parampseudo>
 * <parampseudo name="pString1" type="IN" range="[LOWWSTRING_SHORT,LOWWSTRING_LONG,HIGHWSTRING_SHORT,HIGHWSTRING_LONG]">String type to be copied in the test</parampseudo>
 * <parampseudo name="pString2" type="IN" range="[LOWWSTRING_SHORT,LOWWSTRING_LONG,HIGHWSTRING_SHORT,HIGHWSTRING_LONG]">String type to be copied in the test</parampseudo>
 * <parampseudo name="diRet" type="OUT">Lexicographical result of "pString1" compared to "pString2". 0 if both are equal.</parampseudo>
 */
void CDECL CDECL_EXT __wstringcompare(__wstringcompare_struct* p);
typedef void (CDECL * PF__WSTRINGCOMPARE) (__wstringcompare_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(__WSTRINGCOMPARE_NOTIMPLEMENTED)
	#define USE___wstringcompare
	#define EXT___wstringcompare
	#define GET___wstringcompare(fl)  ERR_NOTIMPLEMENTED
	#define CAL___wstringcompare(p0) 
	#define CHK___wstringcompare  FALSE
	#define EXP___wstringcompare  ERR_OK
#elif defined(STATIC_LINK)
	#define USE___wstringcompare
	#define EXT___wstringcompare
	#define GET___wstringcompare(fl)  CAL_CMGETAPI( "__wstringcompare" ) 
	#define CAL___wstringcompare  __wstringcompare
	#define CHK___wstringcompare  TRUE
	#define EXP___wstringcompare  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__wstringcompare", (RTS_UINTPTR)__wstringcompare, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE___wstringcompare
	#define EXT___wstringcompare
	#define GET___wstringcompare(fl)  CAL_CMGETAPI( "__wstringcompare" ) 
	#define CAL___wstringcompare  __wstringcompare
	#define CHK___wstringcompare  TRUE
	#define EXP___wstringcompare  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__wstringcompare", (RTS_UINTPTR)__wstringcompare, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLib__wstringcompare
	#define EXT_SysInternalLib__wstringcompare
	#define GET_SysInternalLib__wstringcompare  ERR_OK
	#define CAL_SysInternalLib__wstringcompare  __wstringcompare
	#define CHK_SysInternalLib__wstringcompare  TRUE
	#define EXP_SysInternalLib__wstringcompare  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__wstringcompare", (RTS_UINTPTR)__wstringcompare, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE___wstringcompare
	#define EXT___wstringcompare
	#define GET___wstringcompare(fl)  CAL_CMGETAPI( "__wstringcompare" ) 
	#define CAL___wstringcompare  __wstringcompare
	#define CHK___wstringcompare  TRUE
	#define EXP___wstringcompare  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__wstringcompare", (RTS_UINTPTR)__wstringcompare, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE___wstringcompare  PF__WSTRINGCOMPARE pf__wstringcompare;
	#define EXT___wstringcompare  extern PF__WSTRINGCOMPARE pf__wstringcompare;
	#define GET___wstringcompare(fl)  s_pfCMGetAPI2( "__wstringcompare", (RTS_VOID_FCTPTR *)&pf__wstringcompare, (fl), 0, 0)
	#define CAL___wstringcompare  pf__wstringcompare
	#define CHK___wstringcompare  (pf__wstringcompare != NULL)
	#define EXP___wstringcompare   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__wstringcompare", (RTS_UINTPTR)__wstringcompare, 1, 0) 
#endif


/**
 * <description>This function determines if two operands equal. The inputs are 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if the input values are equal, 0 if they are not equal. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT real32__eq(real_cmp_struct* p);
typedef void (CDECL * PFREAL32__EQ) (real_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__EQ_NOTIMPLEMENTED)
	#define USE_real32__eq
	#define EXT_real32__eq
	#define GET_real32__eq(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__eq(p0) 
	#define CHK_real32__eq  FALSE
	#define EXP_real32__eq  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__eq
	#define EXT_real32__eq
	#define GET_real32__eq(fl)  CAL_CMGETAPI( "real32__eq" ) 
	#define CAL_real32__eq  real32__eq
	#define CHK_real32__eq  TRUE
	#define EXP_real32__eq  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__eq", (RTS_UINTPTR)real32__eq, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__eq
	#define EXT_real32__eq
	#define GET_real32__eq(fl)  CAL_CMGETAPI( "real32__eq" ) 
	#define CAL_real32__eq  real32__eq
	#define CHK_real32__eq  TRUE
	#define EXP_real32__eq  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__eq", (RTS_UINTPTR)real32__eq, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__eq
	#define EXT_SysInternalLibreal32__eq
	#define GET_SysInternalLibreal32__eq  ERR_OK
	#define CAL_SysInternalLibreal32__eq  real32__eq
	#define CHK_SysInternalLibreal32__eq  TRUE
	#define EXP_SysInternalLibreal32__eq  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__eq", (RTS_UINTPTR)real32__eq, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__eq
	#define EXT_real32__eq
	#define GET_real32__eq(fl)  CAL_CMGETAPI( "real32__eq" ) 
	#define CAL_real32__eq  real32__eq
	#define CHK_real32__eq  TRUE
	#define EXP_real32__eq  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__eq", (RTS_UINTPTR)real32__eq, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__eq  PFREAL32__EQ pfreal32__eq;
	#define EXT_real32__eq  extern PFREAL32__EQ pfreal32__eq;
	#define GET_real32__eq(fl)  s_pfCMGetAPI2( "real32__eq", (RTS_VOID_FCTPTR *)&pfreal32__eq, (fl), 0, 0)
	#define CAL_real32__eq  pfreal32__eq
	#define CHK_real32__eq  (pfreal32__eq != NULL)
	#define EXP_real32__eq   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__eq", (RTS_UINTPTR)real32__eq, 1, 0) 
#endif


/**
 * <description>This function determines if two operands are not equal. The inputs are 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if the input values are not equal, 0 if they are equal. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT real32__ne(real_cmp_struct* p);
typedef void (CDECL * PFREAL32__NE) (real_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__NE_NOTIMPLEMENTED)
	#define USE_real32__ne
	#define EXT_real32__ne
	#define GET_real32__ne(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__ne(p0) 
	#define CHK_real32__ne  FALSE
	#define EXP_real32__ne  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__ne
	#define EXT_real32__ne
	#define GET_real32__ne(fl)  CAL_CMGETAPI( "real32__ne" ) 
	#define CAL_real32__ne  real32__ne
	#define CHK_real32__ne  TRUE
	#define EXP_real32__ne  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__ne", (RTS_UINTPTR)real32__ne, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__ne
	#define EXT_real32__ne
	#define GET_real32__ne(fl)  CAL_CMGETAPI( "real32__ne" ) 
	#define CAL_real32__ne  real32__ne
	#define CHK_real32__ne  TRUE
	#define EXP_real32__ne  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__ne", (RTS_UINTPTR)real32__ne, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__ne
	#define EXT_SysInternalLibreal32__ne
	#define GET_SysInternalLibreal32__ne  ERR_OK
	#define CAL_SysInternalLibreal32__ne  real32__ne
	#define CHK_SysInternalLibreal32__ne  TRUE
	#define EXP_SysInternalLibreal32__ne  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__ne", (RTS_UINTPTR)real32__ne, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__ne
	#define EXT_real32__ne
	#define GET_real32__ne(fl)  CAL_CMGETAPI( "real32__ne" ) 
	#define CAL_real32__ne  real32__ne
	#define CHK_real32__ne  TRUE
	#define EXP_real32__ne  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__ne", (RTS_UINTPTR)real32__ne, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__ne  PFREAL32__NE pfreal32__ne;
	#define EXT_real32__ne  extern PFREAL32__NE pfreal32__ne;
	#define GET_real32__ne(fl)  s_pfCMGetAPI2( "real32__ne", (RTS_VOID_FCTPTR *)&pfreal32__ne, (fl), 0, 0)
	#define CAL_real32__ne  pfreal32__ne
	#define CHK_real32__ne  (pfreal32__ne != NULL)
	#define EXP_real32__ne   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__ne", (RTS_UINTPTR)real32__ne, 1, 0) 
#endif


/**
 * <description>This function determines if an operand is lower than another. The inputs are 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is lower than in2, 0 if in1 is not lower than in2. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT real32__lt(real_cmp_struct* p);
typedef void (CDECL * PFREAL32__LT) (real_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__LT_NOTIMPLEMENTED)
	#define USE_real32__lt
	#define EXT_real32__lt
	#define GET_real32__lt(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__lt(p0) 
	#define CHK_real32__lt  FALSE
	#define EXP_real32__lt  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__lt
	#define EXT_real32__lt
	#define GET_real32__lt(fl)  CAL_CMGETAPI( "real32__lt" ) 
	#define CAL_real32__lt  real32__lt
	#define CHK_real32__lt  TRUE
	#define EXP_real32__lt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__lt", (RTS_UINTPTR)real32__lt, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__lt
	#define EXT_real32__lt
	#define GET_real32__lt(fl)  CAL_CMGETAPI( "real32__lt" ) 
	#define CAL_real32__lt  real32__lt
	#define CHK_real32__lt  TRUE
	#define EXP_real32__lt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__lt", (RTS_UINTPTR)real32__lt, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__lt
	#define EXT_SysInternalLibreal32__lt
	#define GET_SysInternalLibreal32__lt  ERR_OK
	#define CAL_SysInternalLibreal32__lt  real32__lt
	#define CHK_SysInternalLibreal32__lt  TRUE
	#define EXP_SysInternalLibreal32__lt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__lt", (RTS_UINTPTR)real32__lt, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__lt
	#define EXT_real32__lt
	#define GET_real32__lt(fl)  CAL_CMGETAPI( "real32__lt" ) 
	#define CAL_real32__lt  real32__lt
	#define CHK_real32__lt  TRUE
	#define EXP_real32__lt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__lt", (RTS_UINTPTR)real32__lt, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__lt  PFREAL32__LT pfreal32__lt;
	#define EXT_real32__lt  extern PFREAL32__LT pfreal32__lt;
	#define GET_real32__lt(fl)  s_pfCMGetAPI2( "real32__lt", (RTS_VOID_FCTPTR *)&pfreal32__lt, (fl), 0, 0)
	#define CAL_real32__lt  pfreal32__lt
	#define CHK_real32__lt  (pfreal32__lt != NULL)
	#define EXP_real32__lt   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__lt", (RTS_UINTPTR)real32__lt, 1, 0) 
#endif


/**
 * <description>This function determines if an operand is lower or equal than another. The inputs are 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is lower or equal than in2, 0 if in1 is not lower or equal than in2. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT real32__le(real_cmp_struct* p);
typedef void (CDECL * PFREAL32__LE) (real_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__LE_NOTIMPLEMENTED)
	#define USE_real32__le
	#define EXT_real32__le
	#define GET_real32__le(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__le(p0) 
	#define CHK_real32__le  FALSE
	#define EXP_real32__le  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__le
	#define EXT_real32__le
	#define GET_real32__le(fl)  CAL_CMGETAPI( "real32__le" ) 
	#define CAL_real32__le  real32__le
	#define CHK_real32__le  TRUE
	#define EXP_real32__le  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__le", (RTS_UINTPTR)real32__le, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__le
	#define EXT_real32__le
	#define GET_real32__le(fl)  CAL_CMGETAPI( "real32__le" ) 
	#define CAL_real32__le  real32__le
	#define CHK_real32__le  TRUE
	#define EXP_real32__le  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__le", (RTS_UINTPTR)real32__le, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__le
	#define EXT_SysInternalLibreal32__le
	#define GET_SysInternalLibreal32__le  ERR_OK
	#define CAL_SysInternalLibreal32__le  real32__le
	#define CHK_SysInternalLibreal32__le  TRUE
	#define EXP_SysInternalLibreal32__le  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__le", (RTS_UINTPTR)real32__le, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__le
	#define EXT_real32__le
	#define GET_real32__le(fl)  CAL_CMGETAPI( "real32__le" ) 
	#define CAL_real32__le  real32__le
	#define CHK_real32__le  TRUE
	#define EXP_real32__le  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__le", (RTS_UINTPTR)real32__le, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__le  PFREAL32__LE pfreal32__le;
	#define EXT_real32__le  extern PFREAL32__LE pfreal32__le;
	#define GET_real32__le(fl)  s_pfCMGetAPI2( "real32__le", (RTS_VOID_FCTPTR *)&pfreal32__le, (fl), 0, 0)
	#define CAL_real32__le  pfreal32__le
	#define CHK_real32__le  (pfreal32__le != NULL)
	#define EXP_real32__le   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__le", (RTS_UINTPTR)real32__le, 1, 0) 
#endif


/**
 * <description>This function determines if an operand is greater than another. The inputs are 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is greater than in2, 0 if in1 is not greater than in2. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT real32__gt(real_cmp_struct* p);
typedef void (CDECL * PFREAL32__GT) (real_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__GT_NOTIMPLEMENTED)
	#define USE_real32__gt
	#define EXT_real32__gt
	#define GET_real32__gt(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__gt(p0) 
	#define CHK_real32__gt  FALSE
	#define EXP_real32__gt  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__gt
	#define EXT_real32__gt
	#define GET_real32__gt(fl)  CAL_CMGETAPI( "real32__gt" ) 
	#define CAL_real32__gt  real32__gt
	#define CHK_real32__gt  TRUE
	#define EXP_real32__gt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__gt", (RTS_UINTPTR)real32__gt, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__gt
	#define EXT_real32__gt
	#define GET_real32__gt(fl)  CAL_CMGETAPI( "real32__gt" ) 
	#define CAL_real32__gt  real32__gt
	#define CHK_real32__gt  TRUE
	#define EXP_real32__gt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__gt", (RTS_UINTPTR)real32__gt, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__gt
	#define EXT_SysInternalLibreal32__gt
	#define GET_SysInternalLibreal32__gt  ERR_OK
	#define CAL_SysInternalLibreal32__gt  real32__gt
	#define CHK_SysInternalLibreal32__gt  TRUE
	#define EXP_SysInternalLibreal32__gt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__gt", (RTS_UINTPTR)real32__gt, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__gt
	#define EXT_real32__gt
	#define GET_real32__gt(fl)  CAL_CMGETAPI( "real32__gt" ) 
	#define CAL_real32__gt  real32__gt
	#define CHK_real32__gt  TRUE
	#define EXP_real32__gt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__gt", (RTS_UINTPTR)real32__gt, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__gt  PFREAL32__GT pfreal32__gt;
	#define EXT_real32__gt  extern PFREAL32__GT pfreal32__gt;
	#define GET_real32__gt(fl)  s_pfCMGetAPI2( "real32__gt", (RTS_VOID_FCTPTR *)&pfreal32__gt, (fl), 0, 0)
	#define CAL_real32__gt  pfreal32__gt
	#define CHK_real32__gt  (pfreal32__gt != NULL)
	#define EXP_real32__gt   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__gt", (RTS_UINTPTR)real32__gt, 1, 0) 
#endif


/**
 * <description>This function determines if an operand is greater or equal than another. The inputs are 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is greater or equal than in2, 0 if in1 is not greater or equal than in2. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT real32__ge(real_cmp_struct* p);
typedef void (CDECL * PFREAL32__GE) (real_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__GE_NOTIMPLEMENTED)
	#define USE_real32__ge
	#define EXT_real32__ge
	#define GET_real32__ge(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__ge(p0) 
	#define CHK_real32__ge  FALSE
	#define EXP_real32__ge  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__ge
	#define EXT_real32__ge
	#define GET_real32__ge(fl)  CAL_CMGETAPI( "real32__ge" ) 
	#define CAL_real32__ge  real32__ge
	#define CHK_real32__ge  TRUE
	#define EXP_real32__ge  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__ge", (RTS_UINTPTR)real32__ge, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__ge
	#define EXT_real32__ge
	#define GET_real32__ge(fl)  CAL_CMGETAPI( "real32__ge" ) 
	#define CAL_real32__ge  real32__ge
	#define CHK_real32__ge  TRUE
	#define EXP_real32__ge  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__ge", (RTS_UINTPTR)real32__ge, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__ge
	#define EXT_SysInternalLibreal32__ge
	#define GET_SysInternalLibreal32__ge  ERR_OK
	#define CAL_SysInternalLibreal32__ge  real32__ge
	#define CHK_SysInternalLibreal32__ge  TRUE
	#define EXP_SysInternalLibreal32__ge  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__ge", (RTS_UINTPTR)real32__ge, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__ge
	#define EXT_real32__ge
	#define GET_real32__ge(fl)  CAL_CMGETAPI( "real32__ge" ) 
	#define CAL_real32__ge  real32__ge
	#define CHK_real32__ge  TRUE
	#define EXP_real32__ge  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__ge", (RTS_UINTPTR)real32__ge, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__ge  PFREAL32__GE pfreal32__ge;
	#define EXT_real32__ge  extern PFREAL32__GE pfreal32__ge;
	#define GET_real32__ge(fl)  s_pfCMGetAPI2( "real32__ge", (RTS_VOID_FCTPTR *)&pfreal32__ge, (fl), 0, 0)
	#define CAL_real32__ge  pfreal32__ge
	#define CHK_real32__ge  (pfreal32__ge != NULL)
	#define EXP_real32__ge   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__ge", (RTS_UINTPTR)real32__ge, 1, 0) 
#endif


/**
 * <description>This function makes an addition of two 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">First summand</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Second summand</parampseudo>
 * <parampseudo name="bNegInfinity" type="OUT">The return value is -infinity</parampseudo>
 * <parampseudo name="bInfinity" type="OUT">The return value is infinity</parampseudo>
 * <parampseudo name="out" type="OUT">Sum of the two input values as 32-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real32__add(real_2op_struct* p);
typedef void (CDECL * PFREAL32__ADD) (real_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__ADD_NOTIMPLEMENTED)
	#define USE_real32__add
	#define EXT_real32__add
	#define GET_real32__add(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__add(p0) 
	#define CHK_real32__add  FALSE
	#define EXP_real32__add  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__add
	#define EXT_real32__add
	#define GET_real32__add(fl)  CAL_CMGETAPI( "real32__add" ) 
	#define CAL_real32__add  real32__add
	#define CHK_real32__add  TRUE
	#define EXP_real32__add  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__add", (RTS_UINTPTR)real32__add, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__add
	#define EXT_real32__add
	#define GET_real32__add(fl)  CAL_CMGETAPI( "real32__add" ) 
	#define CAL_real32__add  real32__add
	#define CHK_real32__add  TRUE
	#define EXP_real32__add  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__add", (RTS_UINTPTR)real32__add, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__add
	#define EXT_SysInternalLibreal32__add
	#define GET_SysInternalLibreal32__add  ERR_OK
	#define CAL_SysInternalLibreal32__add  real32__add
	#define CHK_SysInternalLibreal32__add  TRUE
	#define EXP_SysInternalLibreal32__add  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__add", (RTS_UINTPTR)real32__add, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__add
	#define EXT_real32__add
	#define GET_real32__add(fl)  CAL_CMGETAPI( "real32__add" ) 
	#define CAL_real32__add  real32__add
	#define CHK_real32__add  TRUE
	#define EXP_real32__add  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__add", (RTS_UINTPTR)real32__add, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__add  PFREAL32__ADD pfreal32__add;
	#define EXT_real32__add  extern PFREAL32__ADD pfreal32__add;
	#define GET_real32__add(fl)  s_pfCMGetAPI2( "real32__add", (RTS_VOID_FCTPTR *)&pfreal32__add, (fl), 0, 0)
	#define CAL_real32__add  pfreal32__add
	#define CHK_real32__add  (pfreal32__add != NULL)
	#define EXP_real32__add   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__add", (RTS_UINTPTR)real32__add, 1, 0) 
#endif


/**
 * <description>This function makes a subtraction of one variable from another one. The inputs are 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Minuend</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Subtrahend</parampseudo>
 * <parampseudo name="bNegInfinity" type="OUT">The return value is -infinity</parampseudo>
 * <parampseudo name="bInfinity" type="OUT">The return value is infinity</parampseudo>
 * <parampseudo name="out" type="OUT">Difference of the two input values as 32-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real32__sub(real_2op_struct* p);
typedef void (CDECL * PFREAL32__SUB) (real_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__SUB_NOTIMPLEMENTED)
	#define USE_real32__sub
	#define EXT_real32__sub
	#define GET_real32__sub(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__sub(p0) 
	#define CHK_real32__sub  FALSE
	#define EXP_real32__sub  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__sub
	#define EXT_real32__sub
	#define GET_real32__sub(fl)  CAL_CMGETAPI( "real32__sub" ) 
	#define CAL_real32__sub  real32__sub
	#define CHK_real32__sub  TRUE
	#define EXP_real32__sub  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__sub", (RTS_UINTPTR)real32__sub, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__sub
	#define EXT_real32__sub
	#define GET_real32__sub(fl)  CAL_CMGETAPI( "real32__sub" ) 
	#define CAL_real32__sub  real32__sub
	#define CHK_real32__sub  TRUE
	#define EXP_real32__sub  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__sub", (RTS_UINTPTR)real32__sub, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__sub
	#define EXT_SysInternalLibreal32__sub
	#define GET_SysInternalLibreal32__sub  ERR_OK
	#define CAL_SysInternalLibreal32__sub  real32__sub
	#define CHK_SysInternalLibreal32__sub  TRUE
	#define EXP_SysInternalLibreal32__sub  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__sub", (RTS_UINTPTR)real32__sub, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__sub
	#define EXT_real32__sub
	#define GET_real32__sub(fl)  CAL_CMGETAPI( "real32__sub" ) 
	#define CAL_real32__sub  real32__sub
	#define CHK_real32__sub  TRUE
	#define EXP_real32__sub  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__sub", (RTS_UINTPTR)real32__sub, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__sub  PFREAL32__SUB pfreal32__sub;
	#define EXT_real32__sub  extern PFREAL32__SUB pfreal32__sub;
	#define GET_real32__sub(fl)  s_pfCMGetAPI2( "real32__sub", (RTS_VOID_FCTPTR *)&pfreal32__sub, (fl), 0, 0)
	#define CAL_real32__sub  pfreal32__sub
	#define CHK_real32__sub  (pfreal32__sub != NULL)
	#define EXP_real32__sub   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__sub", (RTS_UINTPTR)real32__sub, 1, 0) 
#endif


/**
 * <description>This function makes a multiplication of two variables. The inputs are 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">First factor</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Second factor</parampseudo>
 * <parampseudo name="bNegInfinity" type="OUT">The return value is -infinity</parampseudo>
 * <parampseudo name="bInfinity" type="OUT">The return value is infinity</parampseudo>
 * <parampseudo name="out" type="OUT">Product of the two input values as 32-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real32__mul(real_2op_struct* p);
typedef void (CDECL * PFREAL32__MUL) (real_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__MUL_NOTIMPLEMENTED)
	#define USE_real32__mul
	#define EXT_real32__mul
	#define GET_real32__mul(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__mul(p0) 
	#define CHK_real32__mul  FALSE
	#define EXP_real32__mul  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__mul
	#define EXT_real32__mul
	#define GET_real32__mul(fl)  CAL_CMGETAPI( "real32__mul" ) 
	#define CAL_real32__mul  real32__mul
	#define CHK_real32__mul  TRUE
	#define EXP_real32__mul  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__mul", (RTS_UINTPTR)real32__mul, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__mul
	#define EXT_real32__mul
	#define GET_real32__mul(fl)  CAL_CMGETAPI( "real32__mul" ) 
	#define CAL_real32__mul  real32__mul
	#define CHK_real32__mul  TRUE
	#define EXP_real32__mul  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__mul", (RTS_UINTPTR)real32__mul, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__mul
	#define EXT_SysInternalLibreal32__mul
	#define GET_SysInternalLibreal32__mul  ERR_OK
	#define CAL_SysInternalLibreal32__mul  real32__mul
	#define CHK_SysInternalLibreal32__mul  TRUE
	#define EXP_SysInternalLibreal32__mul  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__mul", (RTS_UINTPTR)real32__mul, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__mul
	#define EXT_real32__mul
	#define GET_real32__mul(fl)  CAL_CMGETAPI( "real32__mul" ) 
	#define CAL_real32__mul  real32__mul
	#define CHK_real32__mul  TRUE
	#define EXP_real32__mul  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__mul", (RTS_UINTPTR)real32__mul, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__mul  PFREAL32__MUL pfreal32__mul;
	#define EXT_real32__mul  extern PFREAL32__MUL pfreal32__mul;
	#define GET_real32__mul(fl)  s_pfCMGetAPI2( "real32__mul", (RTS_VOID_FCTPTR *)&pfreal32__mul, (fl), 0, 0)
	#define CAL_real32__mul  pfreal32__mul
	#define CHK_real32__mul  (pfreal32__mul != NULL)
	#define EXP_real32__mul   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__mul", (RTS_UINTPTR)real32__mul, 1, 0) 
#endif


/**
 * <description>
 * <p>This function makes a division of two variables. The inputs are 32-bit real values.</p>
 * <p>The behaviour for divisor = 0.0 might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_REAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Dividend</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Divisor</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception thrown</parampseudo>
 * <parampseudo name="out" type="OUT">Quotient of the two input values as 32-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real32__div(real_2op_struct* p);
typedef void (CDECL * PFREAL32__DIV) (real_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__DIV_NOTIMPLEMENTED)
	#define USE_real32__div
	#define EXT_real32__div
	#define GET_real32__div(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__div(p0) 
	#define CHK_real32__div  FALSE
	#define EXP_real32__div  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__div
	#define EXT_real32__div
	#define GET_real32__div(fl)  CAL_CMGETAPI( "real32__div" ) 
	#define CAL_real32__div  real32__div
	#define CHK_real32__div  TRUE
	#define EXP_real32__div  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__div", (RTS_UINTPTR)real32__div, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__div
	#define EXT_real32__div
	#define GET_real32__div(fl)  CAL_CMGETAPI( "real32__div" ) 
	#define CAL_real32__div  real32__div
	#define CHK_real32__div  TRUE
	#define EXP_real32__div  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__div", (RTS_UINTPTR)real32__div, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__div
	#define EXT_SysInternalLibreal32__div
	#define GET_SysInternalLibreal32__div  ERR_OK
	#define CAL_SysInternalLibreal32__div  real32__div
	#define CHK_SysInternalLibreal32__div  TRUE
	#define EXP_SysInternalLibreal32__div  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__div", (RTS_UINTPTR)real32__div, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__div
	#define EXT_real32__div
	#define GET_real32__div(fl)  CAL_CMGETAPI( "real32__div" ) 
	#define CAL_real32__div  real32__div
	#define CHK_real32__div  TRUE
	#define EXP_real32__div  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__div", (RTS_UINTPTR)real32__div, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__div  PFREAL32__DIV pfreal32__div;
	#define EXT_real32__div  extern PFREAL32__DIV pfreal32__div;
	#define GET_real32__div(fl)  s_pfCMGetAPI2( "real32__div", (RTS_VOID_FCTPTR *)&pfreal32__div, (fl), 0, 0)
	#define CAL_real32__div  pfreal32__div
	#define CHK_real32__div  (pfreal32__div != NULL)
	#define EXP_real32__div   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__div", (RTS_UINTPTR)real32__div, 1, 0) 
#endif


/**
 * <description>This function builds the minimum of two variables. The inputs are 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">The lesser of the two values as 32-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real32__min(real_2op_struct* p);
typedef void (CDECL * PFREAL32__MIN) (real_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__MIN_NOTIMPLEMENTED)
	#define USE_real32__min
	#define EXT_real32__min
	#define GET_real32__min(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__min(p0) 
	#define CHK_real32__min  FALSE
	#define EXP_real32__min  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__min
	#define EXT_real32__min
	#define GET_real32__min(fl)  CAL_CMGETAPI( "real32__min" ) 
	#define CAL_real32__min  real32__min
	#define CHK_real32__min  TRUE
	#define EXP_real32__min  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__min", (RTS_UINTPTR)real32__min, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__min
	#define EXT_real32__min
	#define GET_real32__min(fl)  CAL_CMGETAPI( "real32__min" ) 
	#define CAL_real32__min  real32__min
	#define CHK_real32__min  TRUE
	#define EXP_real32__min  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__min", (RTS_UINTPTR)real32__min, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__min
	#define EXT_SysInternalLibreal32__min
	#define GET_SysInternalLibreal32__min  ERR_OK
	#define CAL_SysInternalLibreal32__min  real32__min
	#define CHK_SysInternalLibreal32__min  TRUE
	#define EXP_SysInternalLibreal32__min  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__min", (RTS_UINTPTR)real32__min, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__min
	#define EXT_real32__min
	#define GET_real32__min(fl)  CAL_CMGETAPI( "real32__min" ) 
	#define CAL_real32__min  real32__min
	#define CHK_real32__min  TRUE
	#define EXP_real32__min  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__min", (RTS_UINTPTR)real32__min, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__min  PFREAL32__MIN pfreal32__min;
	#define EXT_real32__min  extern PFREAL32__MIN pfreal32__min;
	#define GET_real32__min(fl)  s_pfCMGetAPI2( "real32__min", (RTS_VOID_FCTPTR *)&pfreal32__min, (fl), 0, 0)
	#define CAL_real32__min  pfreal32__min
	#define CHK_real32__min  (pfreal32__min != NULL)
	#define EXP_real32__min   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__min", (RTS_UINTPTR)real32__min, 1, 0) 
#endif


/**
 * <description>This function builds the maximum of two variables. The inputs are 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">The greater of the two values as 32-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real32__max(real_2op_struct* p);
typedef void (CDECL * PFREAL32__MAX) (real_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__MAX_NOTIMPLEMENTED)
	#define USE_real32__max
	#define EXT_real32__max
	#define GET_real32__max(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__max(p0) 
	#define CHK_real32__max  FALSE
	#define EXP_real32__max  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__max
	#define EXT_real32__max
	#define GET_real32__max(fl)  CAL_CMGETAPI( "real32__max" ) 
	#define CAL_real32__max  real32__max
	#define CHK_real32__max  TRUE
	#define EXP_real32__max  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__max", (RTS_UINTPTR)real32__max, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__max
	#define EXT_real32__max
	#define GET_real32__max(fl)  CAL_CMGETAPI( "real32__max" ) 
	#define CAL_real32__max  real32__max
	#define CHK_real32__max  TRUE
	#define EXP_real32__max  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__max", (RTS_UINTPTR)real32__max, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__max
	#define EXT_SysInternalLibreal32__max
	#define GET_SysInternalLibreal32__max  ERR_OK
	#define CAL_SysInternalLibreal32__max  real32__max
	#define CHK_SysInternalLibreal32__max  TRUE
	#define EXP_SysInternalLibreal32__max  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__max", (RTS_UINTPTR)real32__max, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__max
	#define EXT_real32__max
	#define GET_real32__max(fl)  CAL_CMGETAPI( "real32__max" ) 
	#define CAL_real32__max  real32__max
	#define CHK_real32__max  TRUE
	#define EXP_real32__max  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__max", (RTS_UINTPTR)real32__max, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__max  PFREAL32__MAX pfreal32__max;
	#define EXT_real32__max  extern PFREAL32__MAX pfreal32__max;
	#define GET_real32__max(fl)  s_pfCMGetAPI2( "real32__max", (RTS_VOID_FCTPTR *)&pfreal32__max, (fl), 0, 0)
	#define CAL_real32__max  pfreal32__max
	#define CHK_real32__max  (pfreal32__max != NULL)
	#define EXP_real32__max   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__max", (RTS_UINTPTR)real32__max, 1, 0) 
#endif


/**
 * <description>This function limits an input value to a lower and an upper bound. The inputs are 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_3OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Lower bound</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input value</parampseudo>
 * <parampseudo name="in3" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Upper bound</parampseudo>
 * <parampseudo name="out" type="OUT">in2 if in2 is in the range between in1 and in3, in1 if in2 is lower than in1, in3 if in2 is greater than in3. The result is a 32-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real32__limit(real_3op_struct* p);
typedef void (CDECL * PFREAL32__LIMIT) (real_3op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__LIMIT_NOTIMPLEMENTED)
	#define USE_real32__limit
	#define EXT_real32__limit
	#define GET_real32__limit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__limit(p0) 
	#define CHK_real32__limit  FALSE
	#define EXP_real32__limit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__limit
	#define EXT_real32__limit
	#define GET_real32__limit(fl)  CAL_CMGETAPI( "real32__limit" ) 
	#define CAL_real32__limit  real32__limit
	#define CHK_real32__limit  TRUE
	#define EXP_real32__limit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__limit", (RTS_UINTPTR)real32__limit, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__limit
	#define EXT_real32__limit
	#define GET_real32__limit(fl)  CAL_CMGETAPI( "real32__limit" ) 
	#define CAL_real32__limit  real32__limit
	#define CHK_real32__limit  TRUE
	#define EXP_real32__limit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__limit", (RTS_UINTPTR)real32__limit, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__limit
	#define EXT_SysInternalLibreal32__limit
	#define GET_SysInternalLibreal32__limit  ERR_OK
	#define CAL_SysInternalLibreal32__limit  real32__limit
	#define CHK_SysInternalLibreal32__limit  TRUE
	#define EXP_SysInternalLibreal32__limit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__limit", (RTS_UINTPTR)real32__limit, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__limit
	#define EXT_real32__limit
	#define GET_real32__limit(fl)  CAL_CMGETAPI( "real32__limit" ) 
	#define CAL_real32__limit  real32__limit
	#define CHK_real32__limit  TRUE
	#define EXP_real32__limit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__limit", (RTS_UINTPTR)real32__limit, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__limit  PFREAL32__LIMIT pfreal32__limit;
	#define EXT_real32__limit  extern PFREAL32__LIMIT pfreal32__limit;
	#define GET_real32__limit(fl)  s_pfCMGetAPI2( "real32__limit", (RTS_VOID_FCTPTR *)&pfreal32__limit, (fl), 0, 0)
	#define CAL_real32__limit  pfreal32__limit
	#define CHK_real32__limit  (pfreal32__limit != NULL)
	#define EXP_real32__limit   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__limit", (RTS_UINTPTR)real32__limit, 1, 0) 
#endif


/**
 * <description>This function converts a 32-bit real value to a 32-bit integer value.</description>
 * <param name="p" type="IN" range="[VALID_REAL_TRUNC_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[ANY_MIN, ANY_MID, ANY_MAX]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The whole number portion of the input as 32-bit integer value.</parampseudo>
 */
void CDECL CDECL_EXT real32__trunc(real_trunc_struct* p);
typedef void (CDECL * PFREAL32__TRUNC) (real_trunc_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__TRUNC_NOTIMPLEMENTED)
	#define USE_real32__trunc
	#define EXT_real32__trunc
	#define GET_real32__trunc(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__trunc(p0) 
	#define CHK_real32__trunc  FALSE
	#define EXP_real32__trunc  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__trunc
	#define EXT_real32__trunc
	#define GET_real32__trunc(fl)  CAL_CMGETAPI( "real32__trunc" ) 
	#define CAL_real32__trunc  real32__trunc
	#define CHK_real32__trunc  TRUE
	#define EXP_real32__trunc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__trunc", (RTS_UINTPTR)real32__trunc, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__trunc
	#define EXT_real32__trunc
	#define GET_real32__trunc(fl)  CAL_CMGETAPI( "real32__trunc" ) 
	#define CAL_real32__trunc  real32__trunc
	#define CHK_real32__trunc  TRUE
	#define EXP_real32__trunc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__trunc", (RTS_UINTPTR)real32__trunc, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__trunc
	#define EXT_SysInternalLibreal32__trunc
	#define GET_SysInternalLibreal32__trunc  ERR_OK
	#define CAL_SysInternalLibreal32__trunc  real32__trunc
	#define CHK_SysInternalLibreal32__trunc  TRUE
	#define EXP_SysInternalLibreal32__trunc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__trunc", (RTS_UINTPTR)real32__trunc, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__trunc
	#define EXT_real32__trunc
	#define GET_real32__trunc(fl)  CAL_CMGETAPI( "real32__trunc" ) 
	#define CAL_real32__trunc  real32__trunc
	#define CHK_real32__trunc  TRUE
	#define EXP_real32__trunc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__trunc", (RTS_UINTPTR)real32__trunc, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__trunc  PFREAL32__TRUNC pfreal32__trunc;
	#define EXT_real32__trunc  extern PFREAL32__TRUNC pfreal32__trunc;
	#define GET_real32__trunc(fl)  s_pfCMGetAPI2( "real32__trunc", (RTS_VOID_FCTPTR *)&pfreal32__trunc, (fl), 0, 0)
	#define CAL_real32__trunc  pfreal32__trunc
	#define CHK_real32__trunc  (pfreal32__trunc != NULL)
	#define EXP_real32__trunc   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__trunc", (RTS_UINTPTR)real32__trunc, 1, 0) 
#endif


/**
 * <description>
 * <p>This function calculates the tangent of a 32-bit real value.</p>
 * <p>The behaviour for input values that are multiples of PI_HALF might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_REAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_REAL)-PI_HALF,(RTS_IEC_REAL)-PI_HALF+MIN_DELTA..(RTS_IEC_REAL)0,(RTS_IEC_REAL)0..(RTS_IEC_REAL)PI_HALF-MIN_DELTA,(RTS_IEC_REAL)PI_HALF]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The tangent of the input as 32-bit real value or NaN.</parampseudo>
 */
void CDECL CDECL_EXT real32__tan(real_1op_struct* p);
typedef void (CDECL * PFREAL32__TAN) (real_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__TAN_NOTIMPLEMENTED)
	#define USE_real32__tan
	#define EXT_real32__tan
	#define GET_real32__tan(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__tan(p0) 
	#define CHK_real32__tan  FALSE
	#define EXP_real32__tan  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__tan
	#define EXT_real32__tan
	#define GET_real32__tan(fl)  CAL_CMGETAPI( "real32__tan" ) 
	#define CAL_real32__tan  real32__tan
	#define CHK_real32__tan  TRUE
	#define EXP_real32__tan  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__tan", (RTS_UINTPTR)real32__tan, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__tan
	#define EXT_real32__tan
	#define GET_real32__tan(fl)  CAL_CMGETAPI( "real32__tan" ) 
	#define CAL_real32__tan  real32__tan
	#define CHK_real32__tan  TRUE
	#define EXP_real32__tan  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__tan", (RTS_UINTPTR)real32__tan, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__tan
	#define EXT_SysInternalLibreal32__tan
	#define GET_SysInternalLibreal32__tan  ERR_OK
	#define CAL_SysInternalLibreal32__tan  real32__tan
	#define CHK_SysInternalLibreal32__tan  TRUE
	#define EXP_SysInternalLibreal32__tan  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__tan", (RTS_UINTPTR)real32__tan, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__tan
	#define EXT_real32__tan
	#define GET_real32__tan(fl)  CAL_CMGETAPI( "real32__tan" ) 
	#define CAL_real32__tan  real32__tan
	#define CHK_real32__tan  TRUE
	#define EXP_real32__tan  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__tan", (RTS_UINTPTR)real32__tan, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__tan  PFREAL32__TAN pfreal32__tan;
	#define EXT_real32__tan  extern PFREAL32__TAN pfreal32__tan;
	#define GET_real32__tan(fl)  s_pfCMGetAPI2( "real32__tan", (RTS_VOID_FCTPTR *)&pfreal32__tan, (fl), 0, 0)
	#define CAL_real32__tan  pfreal32__tan
	#define CHK_real32__tan  (pfreal32__tan != NULL)
	#define EXP_real32__tan   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__tan", (RTS_UINTPTR)real32__tan, 1, 0) 
#endif


/**
 * <description>This function calculates the sine of a 32-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_REAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_REAL)-PI,(RTS_IEC_REAL)-PI_HALF,0,(RTS_IEC_REAL)PI_HALF,(RTS_IEC_REAL)PI]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The sine of the input as 32-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real32__sin(real_1op_struct* p);
typedef void (CDECL * PFREAL32__SIN) (real_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__SIN_NOTIMPLEMENTED)
	#define USE_real32__sin
	#define EXT_real32__sin
	#define GET_real32__sin(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__sin(p0) 
	#define CHK_real32__sin  FALSE
	#define EXP_real32__sin  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__sin
	#define EXT_real32__sin
	#define GET_real32__sin(fl)  CAL_CMGETAPI( "real32__sin" ) 
	#define CAL_real32__sin  real32__sin
	#define CHK_real32__sin  TRUE
	#define EXP_real32__sin  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__sin", (RTS_UINTPTR)real32__sin, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__sin
	#define EXT_real32__sin
	#define GET_real32__sin(fl)  CAL_CMGETAPI( "real32__sin" ) 
	#define CAL_real32__sin  real32__sin
	#define CHK_real32__sin  TRUE
	#define EXP_real32__sin  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__sin", (RTS_UINTPTR)real32__sin, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__sin
	#define EXT_SysInternalLibreal32__sin
	#define GET_SysInternalLibreal32__sin  ERR_OK
	#define CAL_SysInternalLibreal32__sin  real32__sin
	#define CHK_SysInternalLibreal32__sin  TRUE
	#define EXP_SysInternalLibreal32__sin  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__sin", (RTS_UINTPTR)real32__sin, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__sin
	#define EXT_real32__sin
	#define GET_real32__sin(fl)  CAL_CMGETAPI( "real32__sin" ) 
	#define CAL_real32__sin  real32__sin
	#define CHK_real32__sin  TRUE
	#define EXP_real32__sin  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__sin", (RTS_UINTPTR)real32__sin, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__sin  PFREAL32__SIN pfreal32__sin;
	#define EXT_real32__sin  extern PFREAL32__SIN pfreal32__sin;
	#define GET_real32__sin(fl)  s_pfCMGetAPI2( "real32__sin", (RTS_VOID_FCTPTR *)&pfreal32__sin, (fl), 0, 0)
	#define CAL_real32__sin  pfreal32__sin
	#define CHK_real32__sin  (pfreal32__sin != NULL)
	#define EXP_real32__sin   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__sin", (RTS_UINTPTR)real32__sin, 1, 0) 
#endif


/**
 * <description>This function calculates the cosine of a 32-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_REAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_REAL)-PI,(RTS_IEC_REAL)-PI_HALF,0,(RTS_IEC_REAL)PI_HALF,(RTS_IEC_REAL)PI]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The cosine of the input as 32-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real32__cos(real_1op_struct* p);
typedef void (CDECL * PFREAL32__COS) (real_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__COS_NOTIMPLEMENTED)
	#define USE_real32__cos
	#define EXT_real32__cos
	#define GET_real32__cos(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__cos(p0) 
	#define CHK_real32__cos  FALSE
	#define EXP_real32__cos  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__cos
	#define EXT_real32__cos
	#define GET_real32__cos(fl)  CAL_CMGETAPI( "real32__cos" ) 
	#define CAL_real32__cos  real32__cos
	#define CHK_real32__cos  TRUE
	#define EXP_real32__cos  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__cos", (RTS_UINTPTR)real32__cos, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__cos
	#define EXT_real32__cos
	#define GET_real32__cos(fl)  CAL_CMGETAPI( "real32__cos" ) 
	#define CAL_real32__cos  real32__cos
	#define CHK_real32__cos  TRUE
	#define EXP_real32__cos  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__cos", (RTS_UINTPTR)real32__cos, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__cos
	#define EXT_SysInternalLibreal32__cos
	#define GET_SysInternalLibreal32__cos  ERR_OK
	#define CAL_SysInternalLibreal32__cos  real32__cos
	#define CHK_SysInternalLibreal32__cos  TRUE
	#define EXP_SysInternalLibreal32__cos  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__cos", (RTS_UINTPTR)real32__cos, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__cos
	#define EXT_real32__cos
	#define GET_real32__cos(fl)  CAL_CMGETAPI( "real32__cos" ) 
	#define CAL_real32__cos  real32__cos
	#define CHK_real32__cos  TRUE
	#define EXP_real32__cos  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__cos", (RTS_UINTPTR)real32__cos, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__cos  PFREAL32__COS pfreal32__cos;
	#define EXT_real32__cos  extern PFREAL32__COS pfreal32__cos;
	#define GET_real32__cos(fl)  s_pfCMGetAPI2( "real32__cos", (RTS_VOID_FCTPTR *)&pfreal32__cos, (fl), 0, 0)
	#define CAL_real32__cos  pfreal32__cos
	#define CHK_real32__cos  (pfreal32__cos != NULL)
	#define EXP_real32__cos   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__cos", (RTS_UINTPTR)real32__cos, 1, 0) 
#endif


/**
 * <description>This function calculates the arc tangent (inverse function of tangent) of a 32-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_REAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The arc tangent of the input as 32-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real32__atan(real_1op_struct* p);
typedef void (CDECL * PFREAL32__ATAN) (real_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__ATAN_NOTIMPLEMENTED)
	#define USE_real32__atan
	#define EXT_real32__atan
	#define GET_real32__atan(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__atan(p0) 
	#define CHK_real32__atan  FALSE
	#define EXP_real32__atan  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__atan
	#define EXT_real32__atan
	#define GET_real32__atan(fl)  CAL_CMGETAPI( "real32__atan" ) 
	#define CAL_real32__atan  real32__atan
	#define CHK_real32__atan  TRUE
	#define EXP_real32__atan  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__atan", (RTS_UINTPTR)real32__atan, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__atan
	#define EXT_real32__atan
	#define GET_real32__atan(fl)  CAL_CMGETAPI( "real32__atan" ) 
	#define CAL_real32__atan  real32__atan
	#define CHK_real32__atan  TRUE
	#define EXP_real32__atan  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__atan", (RTS_UINTPTR)real32__atan, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__atan
	#define EXT_SysInternalLibreal32__atan
	#define GET_SysInternalLibreal32__atan  ERR_OK
	#define CAL_SysInternalLibreal32__atan  real32__atan
	#define CHK_SysInternalLibreal32__atan  TRUE
	#define EXP_SysInternalLibreal32__atan  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__atan", (RTS_UINTPTR)real32__atan, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__atan
	#define EXT_real32__atan
	#define GET_real32__atan(fl)  CAL_CMGETAPI( "real32__atan" ) 
	#define CAL_real32__atan  real32__atan
	#define CHK_real32__atan  TRUE
	#define EXP_real32__atan  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__atan", (RTS_UINTPTR)real32__atan, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__atan  PFREAL32__ATAN pfreal32__atan;
	#define EXT_real32__atan  extern PFREAL32__ATAN pfreal32__atan;
	#define GET_real32__atan(fl)  s_pfCMGetAPI2( "real32__atan", (RTS_VOID_FCTPTR *)&pfreal32__atan, (fl), 0, 0)
	#define CAL_real32__atan  pfreal32__atan
	#define CHK_real32__atan  (pfreal32__atan != NULL)
	#define EXP_real32__atan   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__atan", (RTS_UINTPTR)real32__atan, 1, 0) 
#endif


/**
 * <description>
 * <p>This function calculates the arc sine (inverse function of sine) of a 32-bit real value.</p>
 * <p>The behaviour for input values &lt; -1.0 and &gt; 1.0 might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_REAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_REAL)-1.01,(RTS_IEC_REAL)-1.0..(RTS_IEC_REAL)1.0,(RTS_IEC_REAL)1.01]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The arc sine of the input as 32-bit real value or NaN.</parampseudo>
 */
void CDECL CDECL_EXT real32__asin(real_1op_struct* p);
typedef void (CDECL * PFREAL32__ASIN) (real_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__ASIN_NOTIMPLEMENTED)
	#define USE_real32__asin
	#define EXT_real32__asin
	#define GET_real32__asin(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__asin(p0) 
	#define CHK_real32__asin  FALSE
	#define EXP_real32__asin  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__asin
	#define EXT_real32__asin
	#define GET_real32__asin(fl)  CAL_CMGETAPI( "real32__asin" ) 
	#define CAL_real32__asin  real32__asin
	#define CHK_real32__asin  TRUE
	#define EXP_real32__asin  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__asin", (RTS_UINTPTR)real32__asin, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__asin
	#define EXT_real32__asin
	#define GET_real32__asin(fl)  CAL_CMGETAPI( "real32__asin" ) 
	#define CAL_real32__asin  real32__asin
	#define CHK_real32__asin  TRUE
	#define EXP_real32__asin  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__asin", (RTS_UINTPTR)real32__asin, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__asin
	#define EXT_SysInternalLibreal32__asin
	#define GET_SysInternalLibreal32__asin  ERR_OK
	#define CAL_SysInternalLibreal32__asin  real32__asin
	#define CHK_SysInternalLibreal32__asin  TRUE
	#define EXP_SysInternalLibreal32__asin  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__asin", (RTS_UINTPTR)real32__asin, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__asin
	#define EXT_real32__asin
	#define GET_real32__asin(fl)  CAL_CMGETAPI( "real32__asin" ) 
	#define CAL_real32__asin  real32__asin
	#define CHK_real32__asin  TRUE
	#define EXP_real32__asin  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__asin", (RTS_UINTPTR)real32__asin, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__asin  PFREAL32__ASIN pfreal32__asin;
	#define EXT_real32__asin  extern PFREAL32__ASIN pfreal32__asin;
	#define GET_real32__asin(fl)  s_pfCMGetAPI2( "real32__asin", (RTS_VOID_FCTPTR *)&pfreal32__asin, (fl), 0, 0)
	#define CAL_real32__asin  pfreal32__asin
	#define CHK_real32__asin  (pfreal32__asin != NULL)
	#define EXP_real32__asin   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__asin", (RTS_UINTPTR)real32__asin, 1, 0) 
#endif


/**
 * <description>
 * <p>This function calculates the arc cosine (inverse function of cosine) of a 32-bit real value.</p>
 * <p>The behaviour for input values &lt; -1.0 and &gt; 1.0 might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_REAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_REAL)-1.01,(RTS_IEC_REAL)-1.0..(RTS_IEC_REAL)1.0,(RTS_IEC_REAL)1.01]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The arc cosine of the input as 32-bit real value or NaN.</parampseudo>
 */
void CDECL CDECL_EXT real32__acos(real_1op_struct* p);
typedef void (CDECL * PFREAL32__ACOS) (real_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__ACOS_NOTIMPLEMENTED)
	#define USE_real32__acos
	#define EXT_real32__acos
	#define GET_real32__acos(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__acos(p0) 
	#define CHK_real32__acos  FALSE
	#define EXP_real32__acos  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__acos
	#define EXT_real32__acos
	#define GET_real32__acos(fl)  CAL_CMGETAPI( "real32__acos" ) 
	#define CAL_real32__acos  real32__acos
	#define CHK_real32__acos  TRUE
	#define EXP_real32__acos  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__acos", (RTS_UINTPTR)real32__acos, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__acos
	#define EXT_real32__acos
	#define GET_real32__acos(fl)  CAL_CMGETAPI( "real32__acos" ) 
	#define CAL_real32__acos  real32__acos
	#define CHK_real32__acos  TRUE
	#define EXP_real32__acos  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__acos", (RTS_UINTPTR)real32__acos, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__acos
	#define EXT_SysInternalLibreal32__acos
	#define GET_SysInternalLibreal32__acos  ERR_OK
	#define CAL_SysInternalLibreal32__acos  real32__acos
	#define CHK_SysInternalLibreal32__acos  TRUE
	#define EXP_SysInternalLibreal32__acos  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__acos", (RTS_UINTPTR)real32__acos, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__acos
	#define EXT_real32__acos
	#define GET_real32__acos(fl)  CAL_CMGETAPI( "real32__acos" ) 
	#define CAL_real32__acos  real32__acos
	#define CHK_real32__acos  TRUE
	#define EXP_real32__acos  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__acos", (RTS_UINTPTR)real32__acos, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__acos  PFREAL32__ACOS pfreal32__acos;
	#define EXT_real32__acos  extern PFREAL32__ACOS pfreal32__acos;
	#define GET_real32__acos(fl)  s_pfCMGetAPI2( "real32__acos", (RTS_VOID_FCTPTR *)&pfreal32__acos, (fl), 0, 0)
	#define CAL_real32__acos  pfreal32__acos
	#define CHK_real32__acos  (pfreal32__acos != NULL)
	#define EXP_real32__acos   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__acos", (RTS_UINTPTR)real32__acos, 1, 0) 
#endif


/**
 * <description>
 * <p>This function calculates the natural logarithm of a 32-bit real value.</p>
 * <p>The behaviour for input values &lt;= 0.0 might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_REAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_REAL)0.0,(RTS_IEC_REAL)0.01..RTS_IEC_REAL_MAX]">Input</parampseudo>
 * <parampseudo name="bNegInfinity" type="OUT">The return value is -infinity</parampseudo>
 * <parampseudo name="out" type="OUT">The natural logarithm of the input as 32-bit real value or NaN.</parampseudo>
 */
void CDECL CDECL_EXT real32__ln(real_1op_struct* p);
typedef void (CDECL * PFREAL32__LN) (real_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__LN_NOTIMPLEMENTED)
	#define USE_real32__ln
	#define EXT_real32__ln
	#define GET_real32__ln(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__ln(p0) 
	#define CHK_real32__ln  FALSE
	#define EXP_real32__ln  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__ln
	#define EXT_real32__ln
	#define GET_real32__ln(fl)  CAL_CMGETAPI( "real32__ln" ) 
	#define CAL_real32__ln  real32__ln
	#define CHK_real32__ln  TRUE
	#define EXP_real32__ln  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__ln", (RTS_UINTPTR)real32__ln, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__ln
	#define EXT_real32__ln
	#define GET_real32__ln(fl)  CAL_CMGETAPI( "real32__ln" ) 
	#define CAL_real32__ln  real32__ln
	#define CHK_real32__ln  TRUE
	#define EXP_real32__ln  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__ln", (RTS_UINTPTR)real32__ln, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__ln
	#define EXT_SysInternalLibreal32__ln
	#define GET_SysInternalLibreal32__ln  ERR_OK
	#define CAL_SysInternalLibreal32__ln  real32__ln
	#define CHK_SysInternalLibreal32__ln  TRUE
	#define EXP_SysInternalLibreal32__ln  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__ln", (RTS_UINTPTR)real32__ln, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__ln
	#define EXT_real32__ln
	#define GET_real32__ln(fl)  CAL_CMGETAPI( "real32__ln" ) 
	#define CAL_real32__ln  real32__ln
	#define CHK_real32__ln  TRUE
	#define EXP_real32__ln  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__ln", (RTS_UINTPTR)real32__ln, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__ln  PFREAL32__LN pfreal32__ln;
	#define EXT_real32__ln  extern PFREAL32__LN pfreal32__ln;
	#define GET_real32__ln(fl)  s_pfCMGetAPI2( "real32__ln", (RTS_VOID_FCTPTR *)&pfreal32__ln, (fl), 0, 0)
	#define CAL_real32__ln  pfreal32__ln
	#define CHK_real32__ln  (pfreal32__ln != NULL)
	#define EXP_real32__ln   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__ln", (RTS_UINTPTR)real32__ln, 1, 0) 
#endif


/**
 * <description>
 * <p>This function calculates the logarithm in Base 10 of a 32-bit real value.</p>
 * <p>The behaviour for input values &lt;= 0.0 might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_REAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_REAL)0.0,(RTS_IEC_REAL)0.01..RTS_IEC_REAL_MAX]">Input</parampseudo>
 * <parampseudo name="bNegInfinity" type="OUT">The return value is -infinity</parampseudo>
 * <parampseudo name="out" type="OUT">The logarithm in Base 10 of the input as 32-bit real value or NaN.</parampseudo>
 */
void CDECL CDECL_EXT real32__log(real_1op_struct* p);
typedef void (CDECL * PFREAL32__LOG) (real_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__LOG_NOTIMPLEMENTED)
	#define USE_real32__log
	#define EXT_real32__log
	#define GET_real32__log(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__log(p0) 
	#define CHK_real32__log  FALSE
	#define EXP_real32__log  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__log
	#define EXT_real32__log
	#define GET_real32__log(fl)  CAL_CMGETAPI( "real32__log" ) 
	#define CAL_real32__log  real32__log
	#define CHK_real32__log  TRUE
	#define EXP_real32__log  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__log", (RTS_UINTPTR)real32__log, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__log
	#define EXT_real32__log
	#define GET_real32__log(fl)  CAL_CMGETAPI( "real32__log" ) 
	#define CAL_real32__log  real32__log
	#define CHK_real32__log  TRUE
	#define EXP_real32__log  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__log", (RTS_UINTPTR)real32__log, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__log
	#define EXT_SysInternalLibreal32__log
	#define GET_SysInternalLibreal32__log  ERR_OK
	#define CAL_SysInternalLibreal32__log  real32__log
	#define CHK_SysInternalLibreal32__log  TRUE
	#define EXP_SysInternalLibreal32__log  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__log", (RTS_UINTPTR)real32__log, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__log
	#define EXT_real32__log
	#define GET_real32__log(fl)  CAL_CMGETAPI( "real32__log" ) 
	#define CAL_real32__log  real32__log
	#define CHK_real32__log  TRUE
	#define EXP_real32__log  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__log", (RTS_UINTPTR)real32__log, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__log  PFREAL32__LOG pfreal32__log;
	#define EXT_real32__log  extern PFREAL32__LOG pfreal32__log;
	#define GET_real32__log(fl)  s_pfCMGetAPI2( "real32__log", (RTS_VOID_FCTPTR *)&pfreal32__log, (fl), 0, 0)
	#define CAL_real32__log  pfreal32__log
	#define CHK_real32__log  (pfreal32__log != NULL)
	#define EXP_real32__log   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__log", (RTS_UINTPTR)real32__log, 1, 0) 
#endif


/**
 * <description>This function calculates the exponential function of a 32-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_REAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input</parampseudo>
 * <parampseudo name="bInfinity" type="OUT">The return value is infinity</parampseudo>
 * <parampseudo name="out" type="OUT">The exponential function of the input as 32-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real32__exp(real_1op_struct* p);
typedef void (CDECL * PFREAL32__EXP) (real_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__EXP_NOTIMPLEMENTED)
	#define USE_real32__exp
	#define EXT_real32__exp
	#define GET_real32__exp(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__exp(p0) 
	#define CHK_real32__exp  FALSE
	#define EXP_real32__exp  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__exp
	#define EXT_real32__exp
	#define GET_real32__exp(fl)  CAL_CMGETAPI( "real32__exp" ) 
	#define CAL_real32__exp  real32__exp
	#define CHK_real32__exp  TRUE
	#define EXP_real32__exp  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__exp", (RTS_UINTPTR)real32__exp, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__exp
	#define EXT_real32__exp
	#define GET_real32__exp(fl)  CAL_CMGETAPI( "real32__exp" ) 
	#define CAL_real32__exp  real32__exp
	#define CHK_real32__exp  TRUE
	#define EXP_real32__exp  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__exp", (RTS_UINTPTR)real32__exp, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__exp
	#define EXT_SysInternalLibreal32__exp
	#define GET_SysInternalLibreal32__exp  ERR_OK
	#define CAL_SysInternalLibreal32__exp  real32__exp
	#define CHK_SysInternalLibreal32__exp  TRUE
	#define EXP_SysInternalLibreal32__exp  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__exp", (RTS_UINTPTR)real32__exp, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__exp
	#define EXT_real32__exp
	#define GET_real32__exp(fl)  CAL_CMGETAPI( "real32__exp" ) 
	#define CAL_real32__exp  real32__exp
	#define CHK_real32__exp  TRUE
	#define EXP_real32__exp  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__exp", (RTS_UINTPTR)real32__exp, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__exp  PFREAL32__EXP pfreal32__exp;
	#define EXT_real32__exp  extern PFREAL32__EXP pfreal32__exp;
	#define GET_real32__exp(fl)  s_pfCMGetAPI2( "real32__exp", (RTS_VOID_FCTPTR *)&pfreal32__exp, (fl), 0, 0)
	#define CAL_real32__exp  pfreal32__exp
	#define CHK_real32__exp  (pfreal32__exp != NULL)
	#define EXP_real32__exp   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__exp", (RTS_UINTPTR)real32__exp, 1, 0) 
#endif


/**
 * <description>
 * <p>This function calculates the square root of a 32-bit real value.</p>
 * <p>The behaviour for input values &lt; 0.0 might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_REAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_REAL)-0.01,(RTS_IEC_REAL)0.0..RTS_IEC_REAL_MAX]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The square root of the input as 32-bit real value or NaN.</parampseudo>
 */
void CDECL CDECL_EXT real32__sqrt(real_1op_struct* p);
typedef void (CDECL * PFREAL32__SQRT) (real_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__SQRT_NOTIMPLEMENTED)
	#define USE_real32__sqrt
	#define EXT_real32__sqrt
	#define GET_real32__sqrt(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__sqrt(p0) 
	#define CHK_real32__sqrt  FALSE
	#define EXP_real32__sqrt  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__sqrt
	#define EXT_real32__sqrt
	#define GET_real32__sqrt(fl)  CAL_CMGETAPI( "real32__sqrt" ) 
	#define CAL_real32__sqrt  real32__sqrt
	#define CHK_real32__sqrt  TRUE
	#define EXP_real32__sqrt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__sqrt", (RTS_UINTPTR)real32__sqrt, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__sqrt
	#define EXT_real32__sqrt
	#define GET_real32__sqrt(fl)  CAL_CMGETAPI( "real32__sqrt" ) 
	#define CAL_real32__sqrt  real32__sqrt
	#define CHK_real32__sqrt  TRUE
	#define EXP_real32__sqrt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__sqrt", (RTS_UINTPTR)real32__sqrt, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__sqrt
	#define EXT_SysInternalLibreal32__sqrt
	#define GET_SysInternalLibreal32__sqrt  ERR_OK
	#define CAL_SysInternalLibreal32__sqrt  real32__sqrt
	#define CHK_SysInternalLibreal32__sqrt  TRUE
	#define EXP_SysInternalLibreal32__sqrt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__sqrt", (RTS_UINTPTR)real32__sqrt, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__sqrt
	#define EXT_real32__sqrt
	#define GET_real32__sqrt(fl)  CAL_CMGETAPI( "real32__sqrt" ) 
	#define CAL_real32__sqrt  real32__sqrt
	#define CHK_real32__sqrt  TRUE
	#define EXP_real32__sqrt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__sqrt", (RTS_UINTPTR)real32__sqrt, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__sqrt  PFREAL32__SQRT pfreal32__sqrt;
	#define EXT_real32__sqrt  extern PFREAL32__SQRT pfreal32__sqrt;
	#define GET_real32__sqrt(fl)  s_pfCMGetAPI2( "real32__sqrt", (RTS_VOID_FCTPTR *)&pfreal32__sqrt, (fl), 0, 0)
	#define CAL_real32__sqrt  pfreal32__sqrt
	#define CHK_real32__sqrt  (pfreal32__sqrt != NULL)
	#define EXP_real32__sqrt   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__sqrt", (RTS_UINTPTR)real32__sqrt, 1, 0) 
#endif


/**
 * <description>This function calculates the absolute value of a 32-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_REAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The absolute value of the input as 32-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real32__abs(real_1op_struct* p);
typedef void (CDECL * PFREAL32__ABS) (real_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__ABS_NOTIMPLEMENTED)
	#define USE_real32__abs
	#define EXT_real32__abs
	#define GET_real32__abs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__abs(p0) 
	#define CHK_real32__abs  FALSE
	#define EXP_real32__abs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__abs
	#define EXT_real32__abs
	#define GET_real32__abs(fl)  CAL_CMGETAPI( "real32__abs" ) 
	#define CAL_real32__abs  real32__abs
	#define CHK_real32__abs  TRUE
	#define EXP_real32__abs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__abs", (RTS_UINTPTR)real32__abs, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__abs
	#define EXT_real32__abs
	#define GET_real32__abs(fl)  CAL_CMGETAPI( "real32__abs" ) 
	#define CAL_real32__abs  real32__abs
	#define CHK_real32__abs  TRUE
	#define EXP_real32__abs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__abs", (RTS_UINTPTR)real32__abs, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__abs
	#define EXT_SysInternalLibreal32__abs
	#define GET_SysInternalLibreal32__abs  ERR_OK
	#define CAL_SysInternalLibreal32__abs  real32__abs
	#define CHK_SysInternalLibreal32__abs  TRUE
	#define EXP_SysInternalLibreal32__abs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__abs", (RTS_UINTPTR)real32__abs, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__abs
	#define EXT_real32__abs
	#define GET_real32__abs(fl)  CAL_CMGETAPI( "real32__abs" ) 
	#define CAL_real32__abs  real32__abs
	#define CHK_real32__abs  TRUE
	#define EXP_real32__abs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__abs", (RTS_UINTPTR)real32__abs, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__abs  PFREAL32__ABS pfreal32__abs;
	#define EXT_real32__abs  extern PFREAL32__ABS pfreal32__abs;
	#define GET_real32__abs(fl)  s_pfCMGetAPI2( "real32__abs", (RTS_VOID_FCTPTR *)&pfreal32__abs, (fl), 0, 0)
	#define CAL_real32__abs  pfreal32__abs
	#define CHK_real32__abs  (pfreal32__abs != NULL)
	#define EXP_real32__abs   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__abs", (RTS_UINTPTR)real32__abs, 1, 0) 
#endif


/**
 * <description>
 * <p>This function calculates the exponation of a variable with another variable.</p>
 * <p>The behaviour for input values in1 = 0.0 and in2 &lt; 0.0 might be platform dependent.</p>
 * <p>The inputs are 32-bit real values.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_REAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Base</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Exponent</parampseudo>
 * <parampseudo name="bInfinity" type="OUT">The return value is infinity</parampseudo>
 * <parampseudo name="out" type="OUT">The exponation of in1 with in2 as 32-bit real value or NaN.</parampseudo>
 */
void CDECL CDECL_EXT real32__expt(real_2op_struct* p);
typedef void (CDECL * PFREAL32__EXPT) (real_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__EXPT_NOTIMPLEMENTED)
	#define USE_real32__expt
	#define EXT_real32__expt
	#define GET_real32__expt(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__expt(p0) 
	#define CHK_real32__expt  FALSE
	#define EXP_real32__expt  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__expt
	#define EXT_real32__expt
	#define GET_real32__expt(fl)  CAL_CMGETAPI( "real32__expt" ) 
	#define CAL_real32__expt  real32__expt
	#define CHK_real32__expt  TRUE
	#define EXP_real32__expt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__expt", (RTS_UINTPTR)real32__expt, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__expt
	#define EXT_real32__expt
	#define GET_real32__expt(fl)  CAL_CMGETAPI( "real32__expt" ) 
	#define CAL_real32__expt  real32__expt
	#define CHK_real32__expt  TRUE
	#define EXP_real32__expt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__expt", (RTS_UINTPTR)real32__expt, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__expt
	#define EXT_SysInternalLibreal32__expt
	#define GET_SysInternalLibreal32__expt  ERR_OK
	#define CAL_SysInternalLibreal32__expt  real32__expt
	#define CHK_SysInternalLibreal32__expt  TRUE
	#define EXP_SysInternalLibreal32__expt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__expt", (RTS_UINTPTR)real32__expt, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__expt
	#define EXT_real32__expt
	#define GET_real32__expt(fl)  CAL_CMGETAPI( "real32__expt" ) 
	#define CAL_real32__expt  real32__expt
	#define CHK_real32__expt  TRUE
	#define EXP_real32__expt  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__expt", (RTS_UINTPTR)real32__expt, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__expt  PFREAL32__EXPT pfreal32__expt;
	#define EXT_real32__expt  extern PFREAL32__EXPT pfreal32__expt;
	#define GET_real32__expt(fl)  s_pfCMGetAPI2( "real32__expt", (RTS_VOID_FCTPTR *)&pfreal32__expt, (fl), 0, 0)
	#define CAL_real32__expt  pfreal32__expt
	#define CHK_real32__expt  (pfreal32__expt != NULL)
	#define EXP_real32__expt   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__expt", (RTS_UINTPTR)real32__expt, 1, 0) 
#endif


/**
 * <description>This function determines if two operands equal. The inputs are 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if the input values are equal, 0 if they are not equal. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT real64__eq(lreal_cmp_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__EQ_IEC) (lreal_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__EQ_NOTIMPLEMENTED)
	#define USE_real64__eq
	#define EXT_real64__eq
	#define GET_real64__eq(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__eq(p0) 
	#define CHK_real64__eq  FALSE
	#define EXP_real64__eq  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__eq
	#define EXT_real64__eq
	#define GET_real64__eq(fl)  CAL_CMGETAPI( "real64__eq" ) 
	#define CAL_real64__eq  real64__eq
	#define CHK_real64__eq  TRUE
	#define EXP_real64__eq  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__eq", (RTS_UINTPTR)real64__eq, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__eq
	#define EXT_real64__eq
	#define GET_real64__eq(fl)  CAL_CMGETAPI( "real64__eq" ) 
	#define CAL_real64__eq  real64__eq
	#define CHK_real64__eq  TRUE
	#define EXP_real64__eq  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__eq", (RTS_UINTPTR)real64__eq, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__eq
	#define EXT_SysInternalLibreal64__eq
	#define GET_SysInternalLibreal64__eq  ERR_OK
	#define CAL_SysInternalLibreal64__eq  real64__eq
	#define CHK_SysInternalLibreal64__eq  TRUE
	#define EXP_SysInternalLibreal64__eq  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__eq", (RTS_UINTPTR)real64__eq, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__eq
	#define EXT_real64__eq
	#define GET_real64__eq(fl)  CAL_CMGETAPI( "real64__eq" ) 
	#define CAL_real64__eq  real64__eq
	#define CHK_real64__eq  TRUE
	#define EXP_real64__eq  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__eq", (RTS_UINTPTR)real64__eq, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__eq  PFREAL64__EQ_IEC pfreal64__eq;
	#define EXT_real64__eq  extern PFREAL64__EQ_IEC pfreal64__eq;
	#define GET_real64__eq(fl)  s_pfCMGetAPI2( "real64__eq", (RTS_VOID_FCTPTR *)&pfreal64__eq, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__eq  pfreal64__eq
	#define CHK_real64__eq  (pfreal64__eq != NULL)
	#define EXP_real64__eq   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__eq", (RTS_UINTPTR)real64__eq, 1, 0, 0) 
#endif


/**
 * <description>This function determines if two operands are not equal. The inputs are 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if the input values are not equal, 0 if they are equal. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT real64__ne(lreal_cmp_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__NE_IEC) (lreal_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__NE_NOTIMPLEMENTED)
	#define USE_real64__ne
	#define EXT_real64__ne
	#define GET_real64__ne(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__ne(p0) 
	#define CHK_real64__ne  FALSE
	#define EXP_real64__ne  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__ne
	#define EXT_real64__ne
	#define GET_real64__ne(fl)  CAL_CMGETAPI( "real64__ne" ) 
	#define CAL_real64__ne  real64__ne
	#define CHK_real64__ne  TRUE
	#define EXP_real64__ne  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__ne", (RTS_UINTPTR)real64__ne, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__ne
	#define EXT_real64__ne
	#define GET_real64__ne(fl)  CAL_CMGETAPI( "real64__ne" ) 
	#define CAL_real64__ne  real64__ne
	#define CHK_real64__ne  TRUE
	#define EXP_real64__ne  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__ne", (RTS_UINTPTR)real64__ne, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__ne
	#define EXT_SysInternalLibreal64__ne
	#define GET_SysInternalLibreal64__ne  ERR_OK
	#define CAL_SysInternalLibreal64__ne  real64__ne
	#define CHK_SysInternalLibreal64__ne  TRUE
	#define EXP_SysInternalLibreal64__ne  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__ne", (RTS_UINTPTR)real64__ne, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__ne
	#define EXT_real64__ne
	#define GET_real64__ne(fl)  CAL_CMGETAPI( "real64__ne" ) 
	#define CAL_real64__ne  real64__ne
	#define CHK_real64__ne  TRUE
	#define EXP_real64__ne  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__ne", (RTS_UINTPTR)real64__ne, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__ne  PFREAL64__NE_IEC pfreal64__ne;
	#define EXT_real64__ne  extern PFREAL64__NE_IEC pfreal64__ne;
	#define GET_real64__ne(fl)  s_pfCMGetAPI2( "real64__ne", (RTS_VOID_FCTPTR *)&pfreal64__ne, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__ne  pfreal64__ne
	#define CHK_real64__ne  (pfreal64__ne != NULL)
	#define EXP_real64__ne   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__ne", (RTS_UINTPTR)real64__ne, 1, 0, 0) 
#endif


/**
 * <description>This function determines if an operand is lower than another. The inputs are 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is lower than in2, 0 if in1 is not lower than in2. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT real64__lt(lreal_cmp_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__LT_IEC) (lreal_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__LT_NOTIMPLEMENTED)
	#define USE_real64__lt
	#define EXT_real64__lt
	#define GET_real64__lt(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__lt(p0) 
	#define CHK_real64__lt  FALSE
	#define EXP_real64__lt  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__lt
	#define EXT_real64__lt
	#define GET_real64__lt(fl)  CAL_CMGETAPI( "real64__lt" ) 
	#define CAL_real64__lt  real64__lt
	#define CHK_real64__lt  TRUE
	#define EXP_real64__lt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__lt", (RTS_UINTPTR)real64__lt, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__lt
	#define EXT_real64__lt
	#define GET_real64__lt(fl)  CAL_CMGETAPI( "real64__lt" ) 
	#define CAL_real64__lt  real64__lt
	#define CHK_real64__lt  TRUE
	#define EXP_real64__lt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__lt", (RTS_UINTPTR)real64__lt, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__lt
	#define EXT_SysInternalLibreal64__lt
	#define GET_SysInternalLibreal64__lt  ERR_OK
	#define CAL_SysInternalLibreal64__lt  real64__lt
	#define CHK_SysInternalLibreal64__lt  TRUE
	#define EXP_SysInternalLibreal64__lt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__lt", (RTS_UINTPTR)real64__lt, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__lt
	#define EXT_real64__lt
	#define GET_real64__lt(fl)  CAL_CMGETAPI( "real64__lt" ) 
	#define CAL_real64__lt  real64__lt
	#define CHK_real64__lt  TRUE
	#define EXP_real64__lt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__lt", (RTS_UINTPTR)real64__lt, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__lt  PFREAL64__LT_IEC pfreal64__lt;
	#define EXT_real64__lt  extern PFREAL64__LT_IEC pfreal64__lt;
	#define GET_real64__lt(fl)  s_pfCMGetAPI2( "real64__lt", (RTS_VOID_FCTPTR *)&pfreal64__lt, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__lt  pfreal64__lt
	#define CHK_real64__lt  (pfreal64__lt != NULL)
	#define EXP_real64__lt   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__lt", (RTS_UINTPTR)real64__lt, 1, 0, 0) 
#endif


/**
 * <description>This function determines if an operand is lower or equal than another. The inputs are 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is lower or equal than in2, 0 if in1 is not lower or equal than in2. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT real64__le(lreal_cmp_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__LE_IEC) (lreal_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__LE_NOTIMPLEMENTED)
	#define USE_real64__le
	#define EXT_real64__le
	#define GET_real64__le(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__le(p0) 
	#define CHK_real64__le  FALSE
	#define EXP_real64__le  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__le
	#define EXT_real64__le
	#define GET_real64__le(fl)  CAL_CMGETAPI( "real64__le" ) 
	#define CAL_real64__le  real64__le
	#define CHK_real64__le  TRUE
	#define EXP_real64__le  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__le", (RTS_UINTPTR)real64__le, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__le
	#define EXT_real64__le
	#define GET_real64__le(fl)  CAL_CMGETAPI( "real64__le" ) 
	#define CAL_real64__le  real64__le
	#define CHK_real64__le  TRUE
	#define EXP_real64__le  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__le", (RTS_UINTPTR)real64__le, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__le
	#define EXT_SysInternalLibreal64__le
	#define GET_SysInternalLibreal64__le  ERR_OK
	#define CAL_SysInternalLibreal64__le  real64__le
	#define CHK_SysInternalLibreal64__le  TRUE
	#define EXP_SysInternalLibreal64__le  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__le", (RTS_UINTPTR)real64__le, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__le
	#define EXT_real64__le
	#define GET_real64__le(fl)  CAL_CMGETAPI( "real64__le" ) 
	#define CAL_real64__le  real64__le
	#define CHK_real64__le  TRUE
	#define EXP_real64__le  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__le", (RTS_UINTPTR)real64__le, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__le  PFREAL64__LE_IEC pfreal64__le;
	#define EXT_real64__le  extern PFREAL64__LE_IEC pfreal64__le;
	#define GET_real64__le(fl)  s_pfCMGetAPI2( "real64__le", (RTS_VOID_FCTPTR *)&pfreal64__le, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__le  pfreal64__le
	#define CHK_real64__le  (pfreal64__le != NULL)
	#define EXP_real64__le   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__le", (RTS_UINTPTR)real64__le, 1, 0, 0) 
#endif


/**
 * <description>This function determines if an operand is greater than another. The inputs are 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is greater than in2, 0 if in1 is not greater than in2. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT real64__gt(lreal_cmp_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__GT_IEC) (lreal_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__GT_NOTIMPLEMENTED)
	#define USE_real64__gt
	#define EXT_real64__gt
	#define GET_real64__gt(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__gt(p0) 
	#define CHK_real64__gt  FALSE
	#define EXP_real64__gt  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__gt
	#define EXT_real64__gt
	#define GET_real64__gt(fl)  CAL_CMGETAPI( "real64__gt" ) 
	#define CAL_real64__gt  real64__gt
	#define CHK_real64__gt  TRUE
	#define EXP_real64__gt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__gt", (RTS_UINTPTR)real64__gt, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__gt
	#define EXT_real64__gt
	#define GET_real64__gt(fl)  CAL_CMGETAPI( "real64__gt" ) 
	#define CAL_real64__gt  real64__gt
	#define CHK_real64__gt  TRUE
	#define EXP_real64__gt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__gt", (RTS_UINTPTR)real64__gt, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__gt
	#define EXT_SysInternalLibreal64__gt
	#define GET_SysInternalLibreal64__gt  ERR_OK
	#define CAL_SysInternalLibreal64__gt  real64__gt
	#define CHK_SysInternalLibreal64__gt  TRUE
	#define EXP_SysInternalLibreal64__gt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__gt", (RTS_UINTPTR)real64__gt, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__gt
	#define EXT_real64__gt
	#define GET_real64__gt(fl)  CAL_CMGETAPI( "real64__gt" ) 
	#define CAL_real64__gt  real64__gt
	#define CHK_real64__gt  TRUE
	#define EXP_real64__gt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__gt", (RTS_UINTPTR)real64__gt, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__gt  PFREAL64__GT_IEC pfreal64__gt;
	#define EXT_real64__gt  extern PFREAL64__GT_IEC pfreal64__gt;
	#define GET_real64__gt(fl)  s_pfCMGetAPI2( "real64__gt", (RTS_VOID_FCTPTR *)&pfreal64__gt, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__gt  pfreal64__gt
	#define CHK_real64__gt  (pfreal64__gt != NULL)
	#define EXP_real64__gt   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__gt", (RTS_UINTPTR)real64__gt, 1, 0, 0) 
#endif


/**
 * <description>This function determines if an operand is greater or equal than another. The inputs are 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is greater or equal than in2, 0 if in1 is not greater or equal than in2. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT real64__ge(lreal_cmp_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__GE_IEC) (lreal_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__GE_NOTIMPLEMENTED)
	#define USE_real64__ge
	#define EXT_real64__ge
	#define GET_real64__ge(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__ge(p0) 
	#define CHK_real64__ge  FALSE
	#define EXP_real64__ge  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__ge
	#define EXT_real64__ge
	#define GET_real64__ge(fl)  CAL_CMGETAPI( "real64__ge" ) 
	#define CAL_real64__ge  real64__ge
	#define CHK_real64__ge  TRUE
	#define EXP_real64__ge  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__ge", (RTS_UINTPTR)real64__ge, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__ge
	#define EXT_real64__ge
	#define GET_real64__ge(fl)  CAL_CMGETAPI( "real64__ge" ) 
	#define CAL_real64__ge  real64__ge
	#define CHK_real64__ge  TRUE
	#define EXP_real64__ge  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__ge", (RTS_UINTPTR)real64__ge, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__ge
	#define EXT_SysInternalLibreal64__ge
	#define GET_SysInternalLibreal64__ge  ERR_OK
	#define CAL_SysInternalLibreal64__ge  real64__ge
	#define CHK_SysInternalLibreal64__ge  TRUE
	#define EXP_SysInternalLibreal64__ge  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__ge", (RTS_UINTPTR)real64__ge, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__ge
	#define EXT_real64__ge
	#define GET_real64__ge(fl)  CAL_CMGETAPI( "real64__ge" ) 
	#define CAL_real64__ge  real64__ge
	#define CHK_real64__ge  TRUE
	#define EXP_real64__ge  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__ge", (RTS_UINTPTR)real64__ge, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__ge  PFREAL64__GE_IEC pfreal64__ge;
	#define EXT_real64__ge  extern PFREAL64__GE_IEC pfreal64__ge;
	#define GET_real64__ge(fl)  s_pfCMGetAPI2( "real64__ge", (RTS_VOID_FCTPTR *)&pfreal64__ge, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__ge  pfreal64__ge
	#define CHK_real64__ge  (pfreal64__ge != NULL)
	#define EXP_real64__ge   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__ge", (RTS_UINTPTR)real64__ge, 1, 0, 0) 
#endif


/**
 * <description>This function makes an addition of two 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">First summand</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Second summand</parampseudo>
 * <parampseudo name="bNegInfinity" type="OUT">The return value is -infinity</parampseudo>
 * <parampseudo name="bInfinity" type="OUT">The return value is infinity</parampseudo>
 * <parampseudo name="out" type="OUT">Sum of the two input values as 64-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real64__add(lreal_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__ADD_IEC) (lreal_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__ADD_NOTIMPLEMENTED)
	#define USE_real64__add
	#define EXT_real64__add
	#define GET_real64__add(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__add(p0) 
	#define CHK_real64__add  FALSE
	#define EXP_real64__add  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__add
	#define EXT_real64__add
	#define GET_real64__add(fl)  CAL_CMGETAPI( "real64__add" ) 
	#define CAL_real64__add  real64__add
	#define CHK_real64__add  TRUE
	#define EXP_real64__add  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__add", (RTS_UINTPTR)real64__add, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__add
	#define EXT_real64__add
	#define GET_real64__add(fl)  CAL_CMGETAPI( "real64__add" ) 
	#define CAL_real64__add  real64__add
	#define CHK_real64__add  TRUE
	#define EXP_real64__add  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__add", (RTS_UINTPTR)real64__add, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__add
	#define EXT_SysInternalLibreal64__add
	#define GET_SysInternalLibreal64__add  ERR_OK
	#define CAL_SysInternalLibreal64__add  real64__add
	#define CHK_SysInternalLibreal64__add  TRUE
	#define EXP_SysInternalLibreal64__add  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__add", (RTS_UINTPTR)real64__add, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__add
	#define EXT_real64__add
	#define GET_real64__add(fl)  CAL_CMGETAPI( "real64__add" ) 
	#define CAL_real64__add  real64__add
	#define CHK_real64__add  TRUE
	#define EXP_real64__add  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__add", (RTS_UINTPTR)real64__add, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__add  PFREAL64__ADD_IEC pfreal64__add;
	#define EXT_real64__add  extern PFREAL64__ADD_IEC pfreal64__add;
	#define GET_real64__add(fl)  s_pfCMGetAPI2( "real64__add", (RTS_VOID_FCTPTR *)&pfreal64__add, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__add  pfreal64__add
	#define CHK_real64__add  (pfreal64__add != NULL)
	#define EXP_real64__add   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__add", (RTS_UINTPTR)real64__add, 1, 0, 0) 
#endif


/**
 * <description>This function makes a subtraction of one variable from another one. The inputs are 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Minuend</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Subtrahend</parampseudo>
 * <parampseudo name="bNegInfinity" type="OUT">The return value is -infinity</parampseudo>
 * <parampseudo name="bInfinity" type="OUT">The return value is infinity</parampseudo>
 * <parampseudo name="out" type="OUT">Difference of the two input values as 64-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real64__sub(lreal_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__SUB_IEC) (lreal_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__SUB_NOTIMPLEMENTED)
	#define USE_real64__sub
	#define EXT_real64__sub
	#define GET_real64__sub(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__sub(p0) 
	#define CHK_real64__sub  FALSE
	#define EXP_real64__sub  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__sub
	#define EXT_real64__sub
	#define GET_real64__sub(fl)  CAL_CMGETAPI( "real64__sub" ) 
	#define CAL_real64__sub  real64__sub
	#define CHK_real64__sub  TRUE
	#define EXP_real64__sub  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__sub", (RTS_UINTPTR)real64__sub, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__sub
	#define EXT_real64__sub
	#define GET_real64__sub(fl)  CAL_CMGETAPI( "real64__sub" ) 
	#define CAL_real64__sub  real64__sub
	#define CHK_real64__sub  TRUE
	#define EXP_real64__sub  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__sub", (RTS_UINTPTR)real64__sub, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__sub
	#define EXT_SysInternalLibreal64__sub
	#define GET_SysInternalLibreal64__sub  ERR_OK
	#define CAL_SysInternalLibreal64__sub  real64__sub
	#define CHK_SysInternalLibreal64__sub  TRUE
	#define EXP_SysInternalLibreal64__sub  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__sub", (RTS_UINTPTR)real64__sub, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__sub
	#define EXT_real64__sub
	#define GET_real64__sub(fl)  CAL_CMGETAPI( "real64__sub" ) 
	#define CAL_real64__sub  real64__sub
	#define CHK_real64__sub  TRUE
	#define EXP_real64__sub  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__sub", (RTS_UINTPTR)real64__sub, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__sub  PFREAL64__SUB_IEC pfreal64__sub;
	#define EXT_real64__sub  extern PFREAL64__SUB_IEC pfreal64__sub;
	#define GET_real64__sub(fl)  s_pfCMGetAPI2( "real64__sub", (RTS_VOID_FCTPTR *)&pfreal64__sub, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__sub  pfreal64__sub
	#define CHK_real64__sub  (pfreal64__sub != NULL)
	#define EXP_real64__sub   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__sub", (RTS_UINTPTR)real64__sub, 1, 0, 0) 
#endif


/**
 * <description>This function makes a multiplication of two variables. The inputs are 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">First factor</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Second factor</parampseudo>
 * <parampseudo name="bNegInfinity" type="OUT">The return value is -infinity</parampseudo>
 * <parampseudo name="bInfinity" type="OUT">The return value is infinity</parampseudo>
 * <parampseudo name="out" type="OUT">Product of the two input values as 64-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real64__mul(lreal_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__MUL_IEC) (lreal_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__MUL_NOTIMPLEMENTED)
	#define USE_real64__mul
	#define EXT_real64__mul
	#define GET_real64__mul(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__mul(p0) 
	#define CHK_real64__mul  FALSE
	#define EXP_real64__mul  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__mul
	#define EXT_real64__mul
	#define GET_real64__mul(fl)  CAL_CMGETAPI( "real64__mul" ) 
	#define CAL_real64__mul  real64__mul
	#define CHK_real64__mul  TRUE
	#define EXP_real64__mul  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__mul", (RTS_UINTPTR)real64__mul, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__mul
	#define EXT_real64__mul
	#define GET_real64__mul(fl)  CAL_CMGETAPI( "real64__mul" ) 
	#define CAL_real64__mul  real64__mul
	#define CHK_real64__mul  TRUE
	#define EXP_real64__mul  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__mul", (RTS_UINTPTR)real64__mul, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__mul
	#define EXT_SysInternalLibreal64__mul
	#define GET_SysInternalLibreal64__mul  ERR_OK
	#define CAL_SysInternalLibreal64__mul  real64__mul
	#define CHK_SysInternalLibreal64__mul  TRUE
	#define EXP_SysInternalLibreal64__mul  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__mul", (RTS_UINTPTR)real64__mul, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__mul
	#define EXT_real64__mul
	#define GET_real64__mul(fl)  CAL_CMGETAPI( "real64__mul" ) 
	#define CAL_real64__mul  real64__mul
	#define CHK_real64__mul  TRUE
	#define EXP_real64__mul  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__mul", (RTS_UINTPTR)real64__mul, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__mul  PFREAL64__MUL_IEC pfreal64__mul;
	#define EXT_real64__mul  extern PFREAL64__MUL_IEC pfreal64__mul;
	#define GET_real64__mul(fl)  s_pfCMGetAPI2( "real64__mul", (RTS_VOID_FCTPTR *)&pfreal64__mul, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__mul  pfreal64__mul
	#define CHK_real64__mul  (pfreal64__mul != NULL)
	#define EXP_real64__mul   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__mul", (RTS_UINTPTR)real64__mul, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function makes a division of two variables. The inputs are 64-bit real values.</p>
 * <p>The behaviour for divisor = 0.0 might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_LREAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Dividend</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Divisor</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception thrown</parampseudo>
 * <parampseudo name="out" type="OUT">Quotient of the two input values as 64-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real64__div(lreal_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__DIV_IEC) (lreal_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__DIV_NOTIMPLEMENTED)
	#define USE_real64__div
	#define EXT_real64__div
	#define GET_real64__div(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__div(p0) 
	#define CHK_real64__div  FALSE
	#define EXP_real64__div  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__div
	#define EXT_real64__div
	#define GET_real64__div(fl)  CAL_CMGETAPI( "real64__div" ) 
	#define CAL_real64__div  real64__div
	#define CHK_real64__div  TRUE
	#define EXP_real64__div  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__div", (RTS_UINTPTR)real64__div, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__div
	#define EXT_real64__div
	#define GET_real64__div(fl)  CAL_CMGETAPI( "real64__div" ) 
	#define CAL_real64__div  real64__div
	#define CHK_real64__div  TRUE
	#define EXP_real64__div  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__div", (RTS_UINTPTR)real64__div, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__div
	#define EXT_SysInternalLibreal64__div
	#define GET_SysInternalLibreal64__div  ERR_OK
	#define CAL_SysInternalLibreal64__div  real64__div
	#define CHK_SysInternalLibreal64__div  TRUE
	#define EXP_SysInternalLibreal64__div  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__div", (RTS_UINTPTR)real64__div, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__div
	#define EXT_real64__div
	#define GET_real64__div(fl)  CAL_CMGETAPI( "real64__div" ) 
	#define CAL_real64__div  real64__div
	#define CHK_real64__div  TRUE
	#define EXP_real64__div  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__div", (RTS_UINTPTR)real64__div, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__div  PFREAL64__DIV_IEC pfreal64__div;
	#define EXT_real64__div  extern PFREAL64__DIV_IEC pfreal64__div;
	#define GET_real64__div(fl)  s_pfCMGetAPI2( "real64__div", (RTS_VOID_FCTPTR *)&pfreal64__div, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__div  pfreal64__div
	#define CHK_real64__div  (pfreal64__div != NULL)
	#define EXP_real64__div   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__div", (RTS_UINTPTR)real64__div, 1, 0, 0) 
#endif


/**
 * <description>This function builds the minimum of two variables. The inputs are 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">The lesser of the two values as 64-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real64__min(lreal_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__MIN_IEC) (lreal_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__MIN_NOTIMPLEMENTED)
	#define USE_real64__min
	#define EXT_real64__min
	#define GET_real64__min(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__min(p0) 
	#define CHK_real64__min  FALSE
	#define EXP_real64__min  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__min
	#define EXT_real64__min
	#define GET_real64__min(fl)  CAL_CMGETAPI( "real64__min" ) 
	#define CAL_real64__min  real64__min
	#define CHK_real64__min  TRUE
	#define EXP_real64__min  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__min", (RTS_UINTPTR)real64__min, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__min
	#define EXT_real64__min
	#define GET_real64__min(fl)  CAL_CMGETAPI( "real64__min" ) 
	#define CAL_real64__min  real64__min
	#define CHK_real64__min  TRUE
	#define EXP_real64__min  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__min", (RTS_UINTPTR)real64__min, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__min
	#define EXT_SysInternalLibreal64__min
	#define GET_SysInternalLibreal64__min  ERR_OK
	#define CAL_SysInternalLibreal64__min  real64__min
	#define CHK_SysInternalLibreal64__min  TRUE
	#define EXP_SysInternalLibreal64__min  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__min", (RTS_UINTPTR)real64__min, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__min
	#define EXT_real64__min
	#define GET_real64__min(fl)  CAL_CMGETAPI( "real64__min" ) 
	#define CAL_real64__min  real64__min
	#define CHK_real64__min  TRUE
	#define EXP_real64__min  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__min", (RTS_UINTPTR)real64__min, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__min  PFREAL64__MIN_IEC pfreal64__min;
	#define EXT_real64__min  extern PFREAL64__MIN_IEC pfreal64__min;
	#define GET_real64__min(fl)  s_pfCMGetAPI2( "real64__min", (RTS_VOID_FCTPTR *)&pfreal64__min, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__min  pfreal64__min
	#define CHK_real64__min  (pfreal64__min != NULL)
	#define EXP_real64__min   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__min", (RTS_UINTPTR)real64__min, 1, 0, 0) 
#endif


/**
 * <description>This function builds the maximum of two variables. The inputs are 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">The greater of the two values as 64-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real64__max(lreal_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__MAX_IEC) (lreal_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__MAX_NOTIMPLEMENTED)
	#define USE_real64__max
	#define EXT_real64__max
	#define GET_real64__max(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__max(p0) 
	#define CHK_real64__max  FALSE
	#define EXP_real64__max  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__max
	#define EXT_real64__max
	#define GET_real64__max(fl)  CAL_CMGETAPI( "real64__max" ) 
	#define CAL_real64__max  real64__max
	#define CHK_real64__max  TRUE
	#define EXP_real64__max  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__max", (RTS_UINTPTR)real64__max, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__max
	#define EXT_real64__max
	#define GET_real64__max(fl)  CAL_CMGETAPI( "real64__max" ) 
	#define CAL_real64__max  real64__max
	#define CHK_real64__max  TRUE
	#define EXP_real64__max  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__max", (RTS_UINTPTR)real64__max, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__max
	#define EXT_SysInternalLibreal64__max
	#define GET_SysInternalLibreal64__max  ERR_OK
	#define CAL_SysInternalLibreal64__max  real64__max
	#define CHK_SysInternalLibreal64__max  TRUE
	#define EXP_SysInternalLibreal64__max  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__max", (RTS_UINTPTR)real64__max, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__max
	#define EXT_real64__max
	#define GET_real64__max(fl)  CAL_CMGETAPI( "real64__max" ) 
	#define CAL_real64__max  real64__max
	#define CHK_real64__max  TRUE
	#define EXP_real64__max  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__max", (RTS_UINTPTR)real64__max, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__max  PFREAL64__MAX_IEC pfreal64__max;
	#define EXT_real64__max  extern PFREAL64__MAX_IEC pfreal64__max;
	#define GET_real64__max(fl)  s_pfCMGetAPI2( "real64__max", (RTS_VOID_FCTPTR *)&pfreal64__max, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__max  pfreal64__max
	#define CHK_real64__max  (pfreal64__max != NULL)
	#define EXP_real64__max   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__max", (RTS_UINTPTR)real64__max, 1, 0, 0) 
#endif


/**
 * <description>This function limits an input value to a lower and an upper bound. The inputs are 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_3OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Lower bound</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input value</parampseudo>
 * <parampseudo name="in3" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Upper bound</parampseudo>
 * <parampseudo name="out" type="OUT">in2 if in2 is in the range between in1 and in3, in1 if in2 is lower than in1, in3 if in2 is greater than in3. The result is a 64-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real64__limit(lreal_3op_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__LIMIT_IEC) (lreal_3op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__LIMIT_NOTIMPLEMENTED)
	#define USE_real64__limit
	#define EXT_real64__limit
	#define GET_real64__limit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__limit(p0) 
	#define CHK_real64__limit  FALSE
	#define EXP_real64__limit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__limit
	#define EXT_real64__limit
	#define GET_real64__limit(fl)  CAL_CMGETAPI( "real64__limit" ) 
	#define CAL_real64__limit  real64__limit
	#define CHK_real64__limit  TRUE
	#define EXP_real64__limit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__limit", (RTS_UINTPTR)real64__limit, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__limit
	#define EXT_real64__limit
	#define GET_real64__limit(fl)  CAL_CMGETAPI( "real64__limit" ) 
	#define CAL_real64__limit  real64__limit
	#define CHK_real64__limit  TRUE
	#define EXP_real64__limit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__limit", (RTS_UINTPTR)real64__limit, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__limit
	#define EXT_SysInternalLibreal64__limit
	#define GET_SysInternalLibreal64__limit  ERR_OK
	#define CAL_SysInternalLibreal64__limit  real64__limit
	#define CHK_SysInternalLibreal64__limit  TRUE
	#define EXP_SysInternalLibreal64__limit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__limit", (RTS_UINTPTR)real64__limit, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__limit
	#define EXT_real64__limit
	#define GET_real64__limit(fl)  CAL_CMGETAPI( "real64__limit" ) 
	#define CAL_real64__limit  real64__limit
	#define CHK_real64__limit  TRUE
	#define EXP_real64__limit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__limit", (RTS_UINTPTR)real64__limit, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__limit  PFREAL64__LIMIT_IEC pfreal64__limit;
	#define EXT_real64__limit  extern PFREAL64__LIMIT_IEC pfreal64__limit;
	#define GET_real64__limit(fl)  s_pfCMGetAPI2( "real64__limit", (RTS_VOID_FCTPTR *)&pfreal64__limit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__limit  pfreal64__limit
	#define CHK_real64__limit  (pfreal64__limit != NULL)
	#define EXP_real64__limit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__limit", (RTS_UINTPTR)real64__limit, 1, 0, 0) 
#endif


/**
 * <description>This function converts a 64-bit real value to a 64-bit integer value.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_TRUNC_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[ANY_MIN, ANY_MID, ANY_MAX]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The whole number portion of the input as 64-bit integer value.</parampseudo>
 */
void CDECL CDECL_EXT real64__trunc(lreal_trunc_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__TRUNC_IEC) (lreal_trunc_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__TRUNC_NOTIMPLEMENTED)
	#define USE_real64__trunc
	#define EXT_real64__trunc
	#define GET_real64__trunc(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__trunc(p0) 
	#define CHK_real64__trunc  FALSE
	#define EXP_real64__trunc  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__trunc
	#define EXT_real64__trunc
	#define GET_real64__trunc(fl)  CAL_CMGETAPI( "real64__trunc" ) 
	#define CAL_real64__trunc  real64__trunc
	#define CHK_real64__trunc  TRUE
	#define EXP_real64__trunc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__trunc", (RTS_UINTPTR)real64__trunc, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__trunc
	#define EXT_real64__trunc
	#define GET_real64__trunc(fl)  CAL_CMGETAPI( "real64__trunc" ) 
	#define CAL_real64__trunc  real64__trunc
	#define CHK_real64__trunc  TRUE
	#define EXP_real64__trunc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__trunc", (RTS_UINTPTR)real64__trunc, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__trunc
	#define EXT_SysInternalLibreal64__trunc
	#define GET_SysInternalLibreal64__trunc  ERR_OK
	#define CAL_SysInternalLibreal64__trunc  real64__trunc
	#define CHK_SysInternalLibreal64__trunc  TRUE
	#define EXP_SysInternalLibreal64__trunc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__trunc", (RTS_UINTPTR)real64__trunc, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__trunc
	#define EXT_real64__trunc
	#define GET_real64__trunc(fl)  CAL_CMGETAPI( "real64__trunc" ) 
	#define CAL_real64__trunc  real64__trunc
	#define CHK_real64__trunc  TRUE
	#define EXP_real64__trunc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__trunc", (RTS_UINTPTR)real64__trunc, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__trunc  PFREAL64__TRUNC_IEC pfreal64__trunc;
	#define EXT_real64__trunc  extern PFREAL64__TRUNC_IEC pfreal64__trunc;
	#define GET_real64__trunc(fl)  s_pfCMGetAPI2( "real64__trunc", (RTS_VOID_FCTPTR *)&pfreal64__trunc, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__trunc  pfreal64__trunc
	#define CHK_real64__trunc  (pfreal64__trunc != NULL)
	#define EXP_real64__trunc   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__trunc", (RTS_UINTPTR)real64__trunc, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function calculates the tangent of a 64-bit real value.</p>
 * <p>The behaviour for input values that are multiples of PI_HALF might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_LREAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_LREAL)-PI_HALF,(RTS_IEC_LREAL)-PI_HALF+MIN_DELTA..(RTS_IEC_LREAL)0,(RTS_IEC_LREAL)0..(RTS_IEC_LREAL)PI_HALF-MIN_DELTA,(RTS_IEC_LREAL)PI_HALF]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The tangent of the input as 64-bit real value or NaN.</parampseudo>
 */
void CDECL CDECL_EXT real64__tan(lreal_1op_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__TAN_IEC) (lreal_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__TAN_NOTIMPLEMENTED)
	#define USE_real64__tan
	#define EXT_real64__tan
	#define GET_real64__tan(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__tan(p0) 
	#define CHK_real64__tan  FALSE
	#define EXP_real64__tan  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__tan
	#define EXT_real64__tan
	#define GET_real64__tan(fl)  CAL_CMGETAPI( "real64__tan" ) 
	#define CAL_real64__tan  real64__tan
	#define CHK_real64__tan  TRUE
	#define EXP_real64__tan  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__tan", (RTS_UINTPTR)real64__tan, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__tan
	#define EXT_real64__tan
	#define GET_real64__tan(fl)  CAL_CMGETAPI( "real64__tan" ) 
	#define CAL_real64__tan  real64__tan
	#define CHK_real64__tan  TRUE
	#define EXP_real64__tan  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__tan", (RTS_UINTPTR)real64__tan, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__tan
	#define EXT_SysInternalLibreal64__tan
	#define GET_SysInternalLibreal64__tan  ERR_OK
	#define CAL_SysInternalLibreal64__tan  real64__tan
	#define CHK_SysInternalLibreal64__tan  TRUE
	#define EXP_SysInternalLibreal64__tan  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__tan", (RTS_UINTPTR)real64__tan, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__tan
	#define EXT_real64__tan
	#define GET_real64__tan(fl)  CAL_CMGETAPI( "real64__tan" ) 
	#define CAL_real64__tan  real64__tan
	#define CHK_real64__tan  TRUE
	#define EXP_real64__tan  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__tan", (RTS_UINTPTR)real64__tan, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__tan  PFREAL64__TAN_IEC pfreal64__tan;
	#define EXT_real64__tan  extern PFREAL64__TAN_IEC pfreal64__tan;
	#define GET_real64__tan(fl)  s_pfCMGetAPI2( "real64__tan", (RTS_VOID_FCTPTR *)&pfreal64__tan, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__tan  pfreal64__tan
	#define CHK_real64__tan  (pfreal64__tan != NULL)
	#define EXP_real64__tan   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__tan", (RTS_UINTPTR)real64__tan, 1, 0, 0) 
#endif


/**
 * <description>This function calculates the sine of a 64-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_LREAL)-PI,(RTS_IEC_LREAL)-PI_HALF,0,(RTS_IEC_LREAL)PI_HALF,(RTS_IEC_LREAL)PI]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The sine of the input as 64-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real64__sin(lreal_1op_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__SIN_IEC) (lreal_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__SIN_NOTIMPLEMENTED)
	#define USE_real64__sin
	#define EXT_real64__sin
	#define GET_real64__sin(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__sin(p0) 
	#define CHK_real64__sin  FALSE
	#define EXP_real64__sin  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__sin
	#define EXT_real64__sin
	#define GET_real64__sin(fl)  CAL_CMGETAPI( "real64__sin" ) 
	#define CAL_real64__sin  real64__sin
	#define CHK_real64__sin  TRUE
	#define EXP_real64__sin  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__sin", (RTS_UINTPTR)real64__sin, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__sin
	#define EXT_real64__sin
	#define GET_real64__sin(fl)  CAL_CMGETAPI( "real64__sin" ) 
	#define CAL_real64__sin  real64__sin
	#define CHK_real64__sin  TRUE
	#define EXP_real64__sin  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__sin", (RTS_UINTPTR)real64__sin, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__sin
	#define EXT_SysInternalLibreal64__sin
	#define GET_SysInternalLibreal64__sin  ERR_OK
	#define CAL_SysInternalLibreal64__sin  real64__sin
	#define CHK_SysInternalLibreal64__sin  TRUE
	#define EXP_SysInternalLibreal64__sin  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__sin", (RTS_UINTPTR)real64__sin, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__sin
	#define EXT_real64__sin
	#define GET_real64__sin(fl)  CAL_CMGETAPI( "real64__sin" ) 
	#define CAL_real64__sin  real64__sin
	#define CHK_real64__sin  TRUE
	#define EXP_real64__sin  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__sin", (RTS_UINTPTR)real64__sin, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__sin  PFREAL64__SIN_IEC pfreal64__sin;
	#define EXT_real64__sin  extern PFREAL64__SIN_IEC pfreal64__sin;
	#define GET_real64__sin(fl)  s_pfCMGetAPI2( "real64__sin", (RTS_VOID_FCTPTR *)&pfreal64__sin, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__sin  pfreal64__sin
	#define CHK_real64__sin  (pfreal64__sin != NULL)
	#define EXP_real64__sin   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__sin", (RTS_UINTPTR)real64__sin, 1, 0, 0) 
#endif


/**
 * <description>This function calculates the cosine of a 64-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_LREAL)-PI,(RTS_IEC_LREAL)-PI_HALF,0,(RTS_IEC_LREAL)PI_HALF,(RTS_IEC_LREAL)PI]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The cosine of the input as 64-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real64__cos(lreal_1op_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__COS_IEC) (lreal_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__COS_NOTIMPLEMENTED)
	#define USE_real64__cos
	#define EXT_real64__cos
	#define GET_real64__cos(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__cos(p0) 
	#define CHK_real64__cos  FALSE
	#define EXP_real64__cos  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__cos
	#define EXT_real64__cos
	#define GET_real64__cos(fl)  CAL_CMGETAPI( "real64__cos" ) 
	#define CAL_real64__cos  real64__cos
	#define CHK_real64__cos  TRUE
	#define EXP_real64__cos  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__cos", (RTS_UINTPTR)real64__cos, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__cos
	#define EXT_real64__cos
	#define GET_real64__cos(fl)  CAL_CMGETAPI( "real64__cos" ) 
	#define CAL_real64__cos  real64__cos
	#define CHK_real64__cos  TRUE
	#define EXP_real64__cos  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__cos", (RTS_UINTPTR)real64__cos, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__cos
	#define EXT_SysInternalLibreal64__cos
	#define GET_SysInternalLibreal64__cos  ERR_OK
	#define CAL_SysInternalLibreal64__cos  real64__cos
	#define CHK_SysInternalLibreal64__cos  TRUE
	#define EXP_SysInternalLibreal64__cos  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__cos", (RTS_UINTPTR)real64__cos, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__cos
	#define EXT_real64__cos
	#define GET_real64__cos(fl)  CAL_CMGETAPI( "real64__cos" ) 
	#define CAL_real64__cos  real64__cos
	#define CHK_real64__cos  TRUE
	#define EXP_real64__cos  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__cos", (RTS_UINTPTR)real64__cos, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__cos  PFREAL64__COS_IEC pfreal64__cos;
	#define EXT_real64__cos  extern PFREAL64__COS_IEC pfreal64__cos;
	#define GET_real64__cos(fl)  s_pfCMGetAPI2( "real64__cos", (RTS_VOID_FCTPTR *)&pfreal64__cos, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__cos  pfreal64__cos
	#define CHK_real64__cos  (pfreal64__cos != NULL)
	#define EXP_real64__cos   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__cos", (RTS_UINTPTR)real64__cos, 1, 0, 0) 
#endif


/**
 * <description>This function calculates the arc tangent (inverse function of tangent) of a 64-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The arc tangent of the input as 64-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real64__atan(lreal_1op_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__ATAN_IEC) (lreal_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__ATAN_NOTIMPLEMENTED)
	#define USE_real64__atan
	#define EXT_real64__atan
	#define GET_real64__atan(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__atan(p0) 
	#define CHK_real64__atan  FALSE
	#define EXP_real64__atan  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__atan
	#define EXT_real64__atan
	#define GET_real64__atan(fl)  CAL_CMGETAPI( "real64__atan" ) 
	#define CAL_real64__atan  real64__atan
	#define CHK_real64__atan  TRUE
	#define EXP_real64__atan  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__atan", (RTS_UINTPTR)real64__atan, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__atan
	#define EXT_real64__atan
	#define GET_real64__atan(fl)  CAL_CMGETAPI( "real64__atan" ) 
	#define CAL_real64__atan  real64__atan
	#define CHK_real64__atan  TRUE
	#define EXP_real64__atan  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__atan", (RTS_UINTPTR)real64__atan, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__atan
	#define EXT_SysInternalLibreal64__atan
	#define GET_SysInternalLibreal64__atan  ERR_OK
	#define CAL_SysInternalLibreal64__atan  real64__atan
	#define CHK_SysInternalLibreal64__atan  TRUE
	#define EXP_SysInternalLibreal64__atan  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__atan", (RTS_UINTPTR)real64__atan, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__atan
	#define EXT_real64__atan
	#define GET_real64__atan(fl)  CAL_CMGETAPI( "real64__atan" ) 
	#define CAL_real64__atan  real64__atan
	#define CHK_real64__atan  TRUE
	#define EXP_real64__atan  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__atan", (RTS_UINTPTR)real64__atan, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__atan  PFREAL64__ATAN_IEC pfreal64__atan;
	#define EXT_real64__atan  extern PFREAL64__ATAN_IEC pfreal64__atan;
	#define GET_real64__atan(fl)  s_pfCMGetAPI2( "real64__atan", (RTS_VOID_FCTPTR *)&pfreal64__atan, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__atan  pfreal64__atan
	#define CHK_real64__atan  (pfreal64__atan != NULL)
	#define EXP_real64__atan   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__atan", (RTS_UINTPTR)real64__atan, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function calculates the arc sine (inverse function of sine) of a 64-bit real value.</p>
 * <p>The behaviour for input values &lt; -1.0 and &gt; 1.0 might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_LREAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_LREAL)-1.01,(RTS_IEC_LREAL)-1.0..(RTS_IEC_LREAL)1.0,(RTS_IEC_LREAL)1.01]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The arc sine of the input as 64-bit real value or NaN.</parampseudo>
 */
void CDECL CDECL_EXT real64__asin(lreal_1op_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__ASIN_IEC) (lreal_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__ASIN_NOTIMPLEMENTED)
	#define USE_real64__asin
	#define EXT_real64__asin
	#define GET_real64__asin(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__asin(p0) 
	#define CHK_real64__asin  FALSE
	#define EXP_real64__asin  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__asin
	#define EXT_real64__asin
	#define GET_real64__asin(fl)  CAL_CMGETAPI( "real64__asin" ) 
	#define CAL_real64__asin  real64__asin
	#define CHK_real64__asin  TRUE
	#define EXP_real64__asin  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__asin", (RTS_UINTPTR)real64__asin, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__asin
	#define EXT_real64__asin
	#define GET_real64__asin(fl)  CAL_CMGETAPI( "real64__asin" ) 
	#define CAL_real64__asin  real64__asin
	#define CHK_real64__asin  TRUE
	#define EXP_real64__asin  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__asin", (RTS_UINTPTR)real64__asin, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__asin
	#define EXT_SysInternalLibreal64__asin
	#define GET_SysInternalLibreal64__asin  ERR_OK
	#define CAL_SysInternalLibreal64__asin  real64__asin
	#define CHK_SysInternalLibreal64__asin  TRUE
	#define EXP_SysInternalLibreal64__asin  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__asin", (RTS_UINTPTR)real64__asin, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__asin
	#define EXT_real64__asin
	#define GET_real64__asin(fl)  CAL_CMGETAPI( "real64__asin" ) 
	#define CAL_real64__asin  real64__asin
	#define CHK_real64__asin  TRUE
	#define EXP_real64__asin  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__asin", (RTS_UINTPTR)real64__asin, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__asin  PFREAL64__ASIN_IEC pfreal64__asin;
	#define EXT_real64__asin  extern PFREAL64__ASIN_IEC pfreal64__asin;
	#define GET_real64__asin(fl)  s_pfCMGetAPI2( "real64__asin", (RTS_VOID_FCTPTR *)&pfreal64__asin, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__asin  pfreal64__asin
	#define CHK_real64__asin  (pfreal64__asin != NULL)
	#define EXP_real64__asin   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__asin", (RTS_UINTPTR)real64__asin, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function calculates the arc cosine (inverse function of cosine) of a 64-bit real value.</p>
 * <p>The behaviour for input values &lt; -1.0 and &gt; 1.0 might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_LREAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_LREAL)-1.01,(RTS_IEC_LREAL)-1.0..(RTS_IEC_LREAL)1.0,(RTS_IEC_LREAL)1.01]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The arc cosine of the input as 64-bit real value or NaN.</parampseudo>
 */
void CDECL CDECL_EXT real64__acos(lreal_1op_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__ACOS_IEC) (lreal_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__ACOS_NOTIMPLEMENTED)
	#define USE_real64__acos
	#define EXT_real64__acos
	#define GET_real64__acos(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__acos(p0) 
	#define CHK_real64__acos  FALSE
	#define EXP_real64__acos  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__acos
	#define EXT_real64__acos
	#define GET_real64__acos(fl)  CAL_CMGETAPI( "real64__acos" ) 
	#define CAL_real64__acos  real64__acos
	#define CHK_real64__acos  TRUE
	#define EXP_real64__acos  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__acos", (RTS_UINTPTR)real64__acos, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__acos
	#define EXT_real64__acos
	#define GET_real64__acos(fl)  CAL_CMGETAPI( "real64__acos" ) 
	#define CAL_real64__acos  real64__acos
	#define CHK_real64__acos  TRUE
	#define EXP_real64__acos  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__acos", (RTS_UINTPTR)real64__acos, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__acos
	#define EXT_SysInternalLibreal64__acos
	#define GET_SysInternalLibreal64__acos  ERR_OK
	#define CAL_SysInternalLibreal64__acos  real64__acos
	#define CHK_SysInternalLibreal64__acos  TRUE
	#define EXP_SysInternalLibreal64__acos  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__acos", (RTS_UINTPTR)real64__acos, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__acos
	#define EXT_real64__acos
	#define GET_real64__acos(fl)  CAL_CMGETAPI( "real64__acos" ) 
	#define CAL_real64__acos  real64__acos
	#define CHK_real64__acos  TRUE
	#define EXP_real64__acos  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__acos", (RTS_UINTPTR)real64__acos, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__acos  PFREAL64__ACOS_IEC pfreal64__acos;
	#define EXT_real64__acos  extern PFREAL64__ACOS_IEC pfreal64__acos;
	#define GET_real64__acos(fl)  s_pfCMGetAPI2( "real64__acos", (RTS_VOID_FCTPTR *)&pfreal64__acos, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__acos  pfreal64__acos
	#define CHK_real64__acos  (pfreal64__acos != NULL)
	#define EXP_real64__acos   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__acos", (RTS_UINTPTR)real64__acos, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function calculates the natural logarithm of a 64-bit real value.</p>
 * <p>The behaviour for input values &lt;= 0.0 might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_LREAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[0.0,0.01..RTS_IEC_LREAL_MAX]">Input</parampseudo>
 * <parampseudo name="bNegInfinity" type="OUT">The return value is -infinity</parampseudo>
 * <parampseudo name="out" type="OUT">The natural logarithm of the input as 64-bit real value or NaN.</parampseudo>
 */
void CDECL CDECL_EXT real64__ln(lreal_1op_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__LN_IEC) (lreal_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__LN_NOTIMPLEMENTED)
	#define USE_real64__ln
	#define EXT_real64__ln
	#define GET_real64__ln(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__ln(p0) 
	#define CHK_real64__ln  FALSE
	#define EXP_real64__ln  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__ln
	#define EXT_real64__ln
	#define GET_real64__ln(fl)  CAL_CMGETAPI( "real64__ln" ) 
	#define CAL_real64__ln  real64__ln
	#define CHK_real64__ln  TRUE
	#define EXP_real64__ln  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__ln", (RTS_UINTPTR)real64__ln, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__ln
	#define EXT_real64__ln
	#define GET_real64__ln(fl)  CAL_CMGETAPI( "real64__ln" ) 
	#define CAL_real64__ln  real64__ln
	#define CHK_real64__ln  TRUE
	#define EXP_real64__ln  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__ln", (RTS_UINTPTR)real64__ln, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__ln
	#define EXT_SysInternalLibreal64__ln
	#define GET_SysInternalLibreal64__ln  ERR_OK
	#define CAL_SysInternalLibreal64__ln  real64__ln
	#define CHK_SysInternalLibreal64__ln  TRUE
	#define EXP_SysInternalLibreal64__ln  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__ln", (RTS_UINTPTR)real64__ln, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__ln
	#define EXT_real64__ln
	#define GET_real64__ln(fl)  CAL_CMGETAPI( "real64__ln" ) 
	#define CAL_real64__ln  real64__ln
	#define CHK_real64__ln  TRUE
	#define EXP_real64__ln  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__ln", (RTS_UINTPTR)real64__ln, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__ln  PFREAL64__LN_IEC pfreal64__ln;
	#define EXT_real64__ln  extern PFREAL64__LN_IEC pfreal64__ln;
	#define GET_real64__ln(fl)  s_pfCMGetAPI2( "real64__ln", (RTS_VOID_FCTPTR *)&pfreal64__ln, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__ln  pfreal64__ln
	#define CHK_real64__ln  (pfreal64__ln != NULL)
	#define EXP_real64__ln   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__ln", (RTS_UINTPTR)real64__ln, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function calculates the logarithm in Base 10 of a 64-bit real value.</p>
 * <p>The behaviour for input values &lt;= 0.0 might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_LREAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_LREAL)0.0,(RTS_IEC_LREAL)0.01..RTS_IEC_LREAL_MAX]">Input</parampseudo>
 * <parampseudo name="bNegInfinity" type="OUT">The return value is -infinity</parampseudo>
 * <parampseudo name="out" type="OUT">The logarithm in Base 10 of the input as 64-bit real value or NaN.</parampseudo>
 */
void CDECL CDECL_EXT real64__log(lreal_1op_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__LOG_IEC) (lreal_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__LOG_NOTIMPLEMENTED)
	#define USE_real64__log
	#define EXT_real64__log
	#define GET_real64__log(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__log(p0) 
	#define CHK_real64__log  FALSE
	#define EXP_real64__log  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__log
	#define EXT_real64__log
	#define GET_real64__log(fl)  CAL_CMGETAPI( "real64__log" ) 
	#define CAL_real64__log  real64__log
	#define CHK_real64__log  TRUE
	#define EXP_real64__log  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__log", (RTS_UINTPTR)real64__log, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__log
	#define EXT_real64__log
	#define GET_real64__log(fl)  CAL_CMGETAPI( "real64__log" ) 
	#define CAL_real64__log  real64__log
	#define CHK_real64__log  TRUE
	#define EXP_real64__log  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__log", (RTS_UINTPTR)real64__log, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__log
	#define EXT_SysInternalLibreal64__log
	#define GET_SysInternalLibreal64__log  ERR_OK
	#define CAL_SysInternalLibreal64__log  real64__log
	#define CHK_SysInternalLibreal64__log  TRUE
	#define EXP_SysInternalLibreal64__log  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__log", (RTS_UINTPTR)real64__log, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__log
	#define EXT_real64__log
	#define GET_real64__log(fl)  CAL_CMGETAPI( "real64__log" ) 
	#define CAL_real64__log  real64__log
	#define CHK_real64__log  TRUE
	#define EXP_real64__log  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__log", (RTS_UINTPTR)real64__log, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__log  PFREAL64__LOG_IEC pfreal64__log;
	#define EXT_real64__log  extern PFREAL64__LOG_IEC pfreal64__log;
	#define GET_real64__log(fl)  s_pfCMGetAPI2( "real64__log", (RTS_VOID_FCTPTR *)&pfreal64__log, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__log  pfreal64__log
	#define CHK_real64__log  (pfreal64__log != NULL)
	#define EXP_real64__log   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__log", (RTS_UINTPTR)real64__log, 1, 0, 0) 
#endif


/**
 * <description>This function calculates the exponential function of a 64-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input</parampseudo>
 * <parampseudo name="bInfinity" type="OUT">The return value is infinity</parampseudo>
 * <parampseudo name="out" type="OUT">The exponential function of the input as 64-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real64__exp(lreal_1op_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__EXP_IEC) (lreal_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__EXP_NOTIMPLEMENTED)
	#define USE_real64__exp
	#define EXT_real64__exp
	#define GET_real64__exp(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__exp(p0) 
	#define CHK_real64__exp  FALSE
	#define EXP_real64__exp  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__exp
	#define EXT_real64__exp
	#define GET_real64__exp(fl)  CAL_CMGETAPI( "real64__exp" ) 
	#define CAL_real64__exp  real64__exp
	#define CHK_real64__exp  TRUE
	#define EXP_real64__exp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__exp", (RTS_UINTPTR)real64__exp, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__exp
	#define EXT_real64__exp
	#define GET_real64__exp(fl)  CAL_CMGETAPI( "real64__exp" ) 
	#define CAL_real64__exp  real64__exp
	#define CHK_real64__exp  TRUE
	#define EXP_real64__exp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__exp", (RTS_UINTPTR)real64__exp, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__exp
	#define EXT_SysInternalLibreal64__exp
	#define GET_SysInternalLibreal64__exp  ERR_OK
	#define CAL_SysInternalLibreal64__exp  real64__exp
	#define CHK_SysInternalLibreal64__exp  TRUE
	#define EXP_SysInternalLibreal64__exp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__exp", (RTS_UINTPTR)real64__exp, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__exp
	#define EXT_real64__exp
	#define GET_real64__exp(fl)  CAL_CMGETAPI( "real64__exp" ) 
	#define CAL_real64__exp  real64__exp
	#define CHK_real64__exp  TRUE
	#define EXP_real64__exp  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__exp", (RTS_UINTPTR)real64__exp, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__exp  PFREAL64__EXP_IEC pfreal64__exp;
	#define EXT_real64__exp  extern PFREAL64__EXP_IEC pfreal64__exp;
	#define GET_real64__exp(fl)  s_pfCMGetAPI2( "real64__exp", (RTS_VOID_FCTPTR *)&pfreal64__exp, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__exp  pfreal64__exp
	#define CHK_real64__exp  (pfreal64__exp != NULL)
	#define EXP_real64__exp   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__exp", (RTS_UINTPTR)real64__exp, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function calculates the square root of a 64-bit real value.</p>
 * <p>The behaviour for input values &lt; 0.0 might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_LREAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_LREAL)-0.01,(RTS_IEC_LREAL)0.0..RTS_IEC_LREAL_MAX]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The square root of the input as 64-bit real value or NaN.</parampseudo>
 */
void CDECL CDECL_EXT real64__sqrt(lreal_1op_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__SQRT_IEC) (lreal_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__SQRT_NOTIMPLEMENTED)
	#define USE_real64__sqrt
	#define EXT_real64__sqrt
	#define GET_real64__sqrt(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__sqrt(p0) 
	#define CHK_real64__sqrt  FALSE
	#define EXP_real64__sqrt  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__sqrt
	#define EXT_real64__sqrt
	#define GET_real64__sqrt(fl)  CAL_CMGETAPI( "real64__sqrt" ) 
	#define CAL_real64__sqrt  real64__sqrt
	#define CHK_real64__sqrt  TRUE
	#define EXP_real64__sqrt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__sqrt", (RTS_UINTPTR)real64__sqrt, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__sqrt
	#define EXT_real64__sqrt
	#define GET_real64__sqrt(fl)  CAL_CMGETAPI( "real64__sqrt" ) 
	#define CAL_real64__sqrt  real64__sqrt
	#define CHK_real64__sqrt  TRUE
	#define EXP_real64__sqrt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__sqrt", (RTS_UINTPTR)real64__sqrt, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__sqrt
	#define EXT_SysInternalLibreal64__sqrt
	#define GET_SysInternalLibreal64__sqrt  ERR_OK
	#define CAL_SysInternalLibreal64__sqrt  real64__sqrt
	#define CHK_SysInternalLibreal64__sqrt  TRUE
	#define EXP_SysInternalLibreal64__sqrt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__sqrt", (RTS_UINTPTR)real64__sqrt, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__sqrt
	#define EXT_real64__sqrt
	#define GET_real64__sqrt(fl)  CAL_CMGETAPI( "real64__sqrt" ) 
	#define CAL_real64__sqrt  real64__sqrt
	#define CHK_real64__sqrt  TRUE
	#define EXP_real64__sqrt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__sqrt", (RTS_UINTPTR)real64__sqrt, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__sqrt  PFREAL64__SQRT_IEC pfreal64__sqrt;
	#define EXT_real64__sqrt  extern PFREAL64__SQRT_IEC pfreal64__sqrt;
	#define GET_real64__sqrt(fl)  s_pfCMGetAPI2( "real64__sqrt", (RTS_VOID_FCTPTR *)&pfreal64__sqrt, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__sqrt  pfreal64__sqrt
	#define CHK_real64__sqrt  (pfreal64__sqrt != NULL)
	#define EXP_real64__sqrt   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__sqrt", (RTS_UINTPTR)real64__sqrt, 1, 0, 0) 
#endif


/**
 * <description>This function calculates the absolute value of a 64-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The absolute value of the input as 64-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real64__abs(lreal_1op_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__ABS_IEC) (lreal_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__ABS_NOTIMPLEMENTED)
	#define USE_real64__abs
	#define EXT_real64__abs
	#define GET_real64__abs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__abs(p0) 
	#define CHK_real64__abs  FALSE
	#define EXP_real64__abs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__abs
	#define EXT_real64__abs
	#define GET_real64__abs(fl)  CAL_CMGETAPI( "real64__abs" ) 
	#define CAL_real64__abs  real64__abs
	#define CHK_real64__abs  TRUE
	#define EXP_real64__abs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__abs", (RTS_UINTPTR)real64__abs, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__abs
	#define EXT_real64__abs
	#define GET_real64__abs(fl)  CAL_CMGETAPI( "real64__abs" ) 
	#define CAL_real64__abs  real64__abs
	#define CHK_real64__abs  TRUE
	#define EXP_real64__abs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__abs", (RTS_UINTPTR)real64__abs, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__abs
	#define EXT_SysInternalLibreal64__abs
	#define GET_SysInternalLibreal64__abs  ERR_OK
	#define CAL_SysInternalLibreal64__abs  real64__abs
	#define CHK_SysInternalLibreal64__abs  TRUE
	#define EXP_SysInternalLibreal64__abs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__abs", (RTS_UINTPTR)real64__abs, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__abs
	#define EXT_real64__abs
	#define GET_real64__abs(fl)  CAL_CMGETAPI( "real64__abs" ) 
	#define CAL_real64__abs  real64__abs
	#define CHK_real64__abs  TRUE
	#define EXP_real64__abs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__abs", (RTS_UINTPTR)real64__abs, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__abs  PFREAL64__ABS_IEC pfreal64__abs;
	#define EXT_real64__abs  extern PFREAL64__ABS_IEC pfreal64__abs;
	#define GET_real64__abs(fl)  s_pfCMGetAPI2( "real64__abs", (RTS_VOID_FCTPTR *)&pfreal64__abs, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__abs  pfreal64__abs
	#define CHK_real64__abs  (pfreal64__abs != NULL)
	#define EXP_real64__abs   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__abs", (RTS_UINTPTR)real64__abs, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function calculates the exponation of a variable with another variable.</p>
 * <p>The behaviour for input values in1 = 0.0 and in2 &lt; 0.0 might be platform dependent.</p>
 * <p>The inputs are 64-bit real values.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_LREAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Base</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Exponent</parampseudo>
 * <parampseudo name="bInfinity" type="OUT">The return value is infinity</parampseudo>
 * <parampseudo name="out" type="OUT">The exponation of in1 with in2 as 64-bit real value or NaN.</parampseudo>
 */
void CDECL CDECL_EXT real64__expt(lreal_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__EXPT_IEC) (lreal_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__EXPT_NOTIMPLEMENTED)
	#define USE_real64__expt
	#define EXT_real64__expt
	#define GET_real64__expt(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__expt(p0) 
	#define CHK_real64__expt  FALSE
	#define EXP_real64__expt  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__expt
	#define EXT_real64__expt
	#define GET_real64__expt(fl)  CAL_CMGETAPI( "real64__expt" ) 
	#define CAL_real64__expt  real64__expt
	#define CHK_real64__expt  TRUE
	#define EXP_real64__expt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__expt", (RTS_UINTPTR)real64__expt, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__expt
	#define EXT_real64__expt
	#define GET_real64__expt(fl)  CAL_CMGETAPI( "real64__expt" ) 
	#define CAL_real64__expt  real64__expt
	#define CHK_real64__expt  TRUE
	#define EXP_real64__expt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__expt", (RTS_UINTPTR)real64__expt, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__expt
	#define EXT_SysInternalLibreal64__expt
	#define GET_SysInternalLibreal64__expt  ERR_OK
	#define CAL_SysInternalLibreal64__expt  real64__expt
	#define CHK_SysInternalLibreal64__expt  TRUE
	#define EXP_SysInternalLibreal64__expt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__expt", (RTS_UINTPTR)real64__expt, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__expt
	#define EXT_real64__expt
	#define GET_real64__expt(fl)  CAL_CMGETAPI( "real64__expt" ) 
	#define CAL_real64__expt  real64__expt
	#define CHK_real64__expt  TRUE
	#define EXP_real64__expt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__expt", (RTS_UINTPTR)real64__expt, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__expt  PFREAL64__EXPT_IEC pfreal64__expt;
	#define EXT_real64__expt  extern PFREAL64__EXPT_IEC pfreal64__expt;
	#define GET_real64__expt(fl)  s_pfCMGetAPI2( "real64__expt", (RTS_VOID_FCTPTR *)&pfreal64__expt, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__expt  pfreal64__expt
	#define CHK_real64__expt  (pfreal64__expt != NULL)
	#define EXP_real64__expt   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__expt", (RTS_UINTPTR)real64__expt, 1, 0, 0) 
#endif


/**
 * <description>This function makes an addition of two 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">First summand</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Second summand</parampseudo>
 * <parampseudo name="out" type="OUT">Sum of the two input values as 64-bit integer value.</parampseudo>
 */
void CDECL CDECL_EXT int64__add(lint_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFINT64__ADD_IEC) (lint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT64__ADD_NOTIMPLEMENTED)
	#define USE_int64__add
	#define EXT_int64__add
	#define GET_int64__add(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int64__add(p0) 
	#define CHK_int64__add  FALSE
	#define EXP_int64__add  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int64__add
	#define EXT_int64__add
	#define GET_int64__add(fl)  CAL_CMGETAPI( "int64__add" ) 
	#define CAL_int64__add  int64__add
	#define CHK_int64__add  TRUE
	#define EXP_int64__add  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__add", (RTS_UINTPTR)int64__add, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int64__add
	#define EXT_int64__add
	#define GET_int64__add(fl)  CAL_CMGETAPI( "int64__add" ) 
	#define CAL_int64__add  int64__add
	#define CHK_int64__add  TRUE
	#define EXP_int64__add  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__add", (RTS_UINTPTR)int64__add, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint64__add
	#define EXT_SysInternalLibint64__add
	#define GET_SysInternalLibint64__add  ERR_OK
	#define CAL_SysInternalLibint64__add  int64__add
	#define CHK_SysInternalLibint64__add  TRUE
	#define EXP_SysInternalLibint64__add  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__add", (RTS_UINTPTR)int64__add, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int64__add
	#define EXT_int64__add
	#define GET_int64__add(fl)  CAL_CMGETAPI( "int64__add" ) 
	#define CAL_int64__add  int64__add
	#define CHK_int64__add  TRUE
	#define EXP_int64__add  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__add", (RTS_UINTPTR)int64__add, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int64__add  PFINT64__ADD_IEC pfint64__add;
	#define EXT_int64__add  extern PFINT64__ADD_IEC pfint64__add;
	#define GET_int64__add(fl)  s_pfCMGetAPI2( "int64__add", (RTS_VOID_FCTPTR *)&pfint64__add, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_int64__add  pfint64__add
	#define CHK_int64__add  (pfint64__add != NULL)
	#define EXP_int64__add   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__add", (RTS_UINTPTR)int64__add, 1, 0, 0) 
#endif


/**
 * <description>This function makes a subtraction of one variable from another one. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Minuend</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Subtrahend</parampseudo>
 * <parampseudo name="out" type="OUT">Difference of the two input values as 64-bit integer value.</parampseudo>
 */
void CDECL CDECL_EXT int64__sub(lint_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFINT64__SUB_IEC) (lint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT64__SUB_NOTIMPLEMENTED)
	#define USE_int64__sub
	#define EXT_int64__sub
	#define GET_int64__sub(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int64__sub(p0) 
	#define CHK_int64__sub  FALSE
	#define EXP_int64__sub  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int64__sub
	#define EXT_int64__sub
	#define GET_int64__sub(fl)  CAL_CMGETAPI( "int64__sub" ) 
	#define CAL_int64__sub  int64__sub
	#define CHK_int64__sub  TRUE
	#define EXP_int64__sub  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__sub", (RTS_UINTPTR)int64__sub, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int64__sub
	#define EXT_int64__sub
	#define GET_int64__sub(fl)  CAL_CMGETAPI( "int64__sub" ) 
	#define CAL_int64__sub  int64__sub
	#define CHK_int64__sub  TRUE
	#define EXP_int64__sub  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__sub", (RTS_UINTPTR)int64__sub, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint64__sub
	#define EXT_SysInternalLibint64__sub
	#define GET_SysInternalLibint64__sub  ERR_OK
	#define CAL_SysInternalLibint64__sub  int64__sub
	#define CHK_SysInternalLibint64__sub  TRUE
	#define EXP_SysInternalLibint64__sub  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__sub", (RTS_UINTPTR)int64__sub, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int64__sub
	#define EXT_int64__sub
	#define GET_int64__sub(fl)  CAL_CMGETAPI( "int64__sub" ) 
	#define CAL_int64__sub  int64__sub
	#define CHK_int64__sub  TRUE
	#define EXP_int64__sub  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__sub", (RTS_UINTPTR)int64__sub, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int64__sub  PFINT64__SUB_IEC pfint64__sub;
	#define EXT_int64__sub  extern PFINT64__SUB_IEC pfint64__sub;
	#define GET_int64__sub(fl)  s_pfCMGetAPI2( "int64__sub", (RTS_VOID_FCTPTR *)&pfint64__sub, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_int64__sub  pfint64__sub
	#define CHK_int64__sub  (pfint64__sub != NULL)
	#define EXP_int64__sub   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__sub", (RTS_UINTPTR)int64__sub, 1, 0, 0) 
#endif


/**
 * <description>This function makes a multiplication of two variables. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">First factor</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Second factor</parampseudo>
 * <parampseudo name="out" type="OUT">Product of the two input values as 64-bit integer value.</parampseudo>
 */
void CDECL CDECL_EXT int64__mul(lint_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFINT64__MUL_IEC) (lint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT64__MUL_NOTIMPLEMENTED)
	#define USE_int64__mul
	#define EXT_int64__mul
	#define GET_int64__mul(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int64__mul(p0) 
	#define CHK_int64__mul  FALSE
	#define EXP_int64__mul  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int64__mul
	#define EXT_int64__mul
	#define GET_int64__mul(fl)  CAL_CMGETAPI( "int64__mul" ) 
	#define CAL_int64__mul  int64__mul
	#define CHK_int64__mul  TRUE
	#define EXP_int64__mul  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__mul", (RTS_UINTPTR)int64__mul, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int64__mul
	#define EXT_int64__mul
	#define GET_int64__mul(fl)  CAL_CMGETAPI( "int64__mul" ) 
	#define CAL_int64__mul  int64__mul
	#define CHK_int64__mul  TRUE
	#define EXP_int64__mul  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__mul", (RTS_UINTPTR)int64__mul, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint64__mul
	#define EXT_SysInternalLibint64__mul
	#define GET_SysInternalLibint64__mul  ERR_OK
	#define CAL_SysInternalLibint64__mul  int64__mul
	#define CHK_SysInternalLibint64__mul  TRUE
	#define EXP_SysInternalLibint64__mul  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__mul", (RTS_UINTPTR)int64__mul, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int64__mul
	#define EXT_int64__mul
	#define GET_int64__mul(fl)  CAL_CMGETAPI( "int64__mul" ) 
	#define CAL_int64__mul  int64__mul
	#define CHK_int64__mul  TRUE
	#define EXP_int64__mul  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__mul", (RTS_UINTPTR)int64__mul, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int64__mul  PFINT64__MUL_IEC pfint64__mul;
	#define EXT_int64__mul  extern PFINT64__MUL_IEC pfint64__mul;
	#define GET_int64__mul(fl)  s_pfCMGetAPI2( "int64__mul", (RTS_VOID_FCTPTR *)&pfint64__mul, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_int64__mul  pfint64__mul
	#define CHK_int64__mul  (pfint64__mul != NULL)
	#define EXP_int64__mul   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__mul", (RTS_UINTPTR)int64__mul, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function makes a division of two variables. The inputs are 64-bit integer values.</p>
 * <p>The behaviour for divisor = 0 might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_LINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Dividend</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Divisor</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception thrown</parampseudo>
 * <parampseudo name="out" type="OUT">Quotient of the two input values as 64-bit integer value.</parampseudo>
 */
void CDECL CDECL_EXT int64__div(lint_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFINT64__DIV_IEC) (lint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT64__DIV_NOTIMPLEMENTED)
	#define USE_int64__div
	#define EXT_int64__div
	#define GET_int64__div(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int64__div(p0) 
	#define CHK_int64__div  FALSE
	#define EXP_int64__div  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int64__div
	#define EXT_int64__div
	#define GET_int64__div(fl)  CAL_CMGETAPI( "int64__div" ) 
	#define CAL_int64__div  int64__div
	#define CHK_int64__div  TRUE
	#define EXP_int64__div  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__div", (RTS_UINTPTR)int64__div, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int64__div
	#define EXT_int64__div
	#define GET_int64__div(fl)  CAL_CMGETAPI( "int64__div" ) 
	#define CAL_int64__div  int64__div
	#define CHK_int64__div  TRUE
	#define EXP_int64__div  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__div", (RTS_UINTPTR)int64__div, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint64__div
	#define EXT_SysInternalLibint64__div
	#define GET_SysInternalLibint64__div  ERR_OK
	#define CAL_SysInternalLibint64__div  int64__div
	#define CHK_SysInternalLibint64__div  TRUE
	#define EXP_SysInternalLibint64__div  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__div", (RTS_UINTPTR)int64__div, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int64__div
	#define EXT_int64__div
	#define GET_int64__div(fl)  CAL_CMGETAPI( "int64__div" ) 
	#define CAL_int64__div  int64__div
	#define CHK_int64__div  TRUE
	#define EXP_int64__div  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__div", (RTS_UINTPTR)int64__div, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int64__div  PFINT64__DIV_IEC pfint64__div;
	#define EXT_int64__div  extern PFINT64__DIV_IEC pfint64__div;
	#define GET_int64__div(fl)  s_pfCMGetAPI2( "int64__div", (RTS_VOID_FCTPTR *)&pfint64__div, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_int64__div  pfint64__div
	#define CHK_int64__div  (pfint64__div != NULL)
	#define EXP_int64__div   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__div", (RTS_UINTPTR)int64__div, 1, 0, 0) 
#endif


/**
 * <description>This function calculates the remainder of division of one variable by another. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Dividend</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Divisor</parampseudo>
 * <parampseudo name="out" type="OUT">Remainder of division of the two input values as 64-bit integer value, or 0 if the divisor is 0.</parampseudo>
 */
void CDECL CDECL_EXT int64__mod(lint_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFINT64__MOD_IEC) (lint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT64__MOD_NOTIMPLEMENTED)
	#define USE_int64__mod
	#define EXT_int64__mod
	#define GET_int64__mod(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int64__mod(p0) 
	#define CHK_int64__mod  FALSE
	#define EXP_int64__mod  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int64__mod
	#define EXT_int64__mod
	#define GET_int64__mod(fl)  CAL_CMGETAPI( "int64__mod" ) 
	#define CAL_int64__mod  int64__mod
	#define CHK_int64__mod  TRUE
	#define EXP_int64__mod  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__mod", (RTS_UINTPTR)int64__mod, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int64__mod
	#define EXT_int64__mod
	#define GET_int64__mod(fl)  CAL_CMGETAPI( "int64__mod" ) 
	#define CAL_int64__mod  int64__mod
	#define CHK_int64__mod  TRUE
	#define EXP_int64__mod  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__mod", (RTS_UINTPTR)int64__mod, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint64__mod
	#define EXT_SysInternalLibint64__mod
	#define GET_SysInternalLibint64__mod  ERR_OK
	#define CAL_SysInternalLibint64__mod  int64__mod
	#define CHK_SysInternalLibint64__mod  TRUE
	#define EXP_SysInternalLibint64__mod  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__mod", (RTS_UINTPTR)int64__mod, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int64__mod
	#define EXT_int64__mod
	#define GET_int64__mod(fl)  CAL_CMGETAPI( "int64__mod" ) 
	#define CAL_int64__mod  int64__mod
	#define CHK_int64__mod  TRUE
	#define EXP_int64__mod  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__mod", (RTS_UINTPTR)int64__mod, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int64__mod  PFINT64__MOD_IEC pfint64__mod;
	#define EXT_int64__mod  extern PFINT64__MOD_IEC pfint64__mod;
	#define GET_int64__mod(fl)  s_pfCMGetAPI2( "int64__mod", (RTS_VOID_FCTPTR *)&pfint64__mod, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_int64__mod  pfint64__mod
	#define CHK_int64__mod  (pfint64__mod != NULL)
	#define EXP_int64__mod   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__mod", (RTS_UINTPTR)int64__mod, 1, 0, 0) 
#endif


/**
 * <description>This function calculates the absolute value of a 64-bit integer value.</description>
 * <param name="p" type="IN" range="[VALID_LINT_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[RTS_IEC_LINT_MIN,RTS_IEC_LINT_MIN+1,0,RTS_IEC_LINT_MAX/2,RTS_IEC_LINT_MAX]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The absolute value of the input as 64-bit integer value.</parampseudo>
 */
void CDECL CDECL_EXT int64__abs(lint_1op_struct* p);
typedef void (CDECL CDECL_EXT* PFINT64__ABS_IEC) (lint_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT64__ABS_NOTIMPLEMENTED)
	#define USE_int64__abs
	#define EXT_int64__abs
	#define GET_int64__abs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int64__abs(p0) 
	#define CHK_int64__abs  FALSE
	#define EXP_int64__abs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int64__abs
	#define EXT_int64__abs
	#define GET_int64__abs(fl)  CAL_CMGETAPI( "int64__abs" ) 
	#define CAL_int64__abs  int64__abs
	#define CHK_int64__abs  TRUE
	#define EXP_int64__abs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__abs", (RTS_UINTPTR)int64__abs, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int64__abs
	#define EXT_int64__abs
	#define GET_int64__abs(fl)  CAL_CMGETAPI( "int64__abs" ) 
	#define CAL_int64__abs  int64__abs
	#define CHK_int64__abs  TRUE
	#define EXP_int64__abs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__abs", (RTS_UINTPTR)int64__abs, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint64__abs
	#define EXT_SysInternalLibint64__abs
	#define GET_SysInternalLibint64__abs  ERR_OK
	#define CAL_SysInternalLibint64__abs  int64__abs
	#define CHK_SysInternalLibint64__abs  TRUE
	#define EXP_SysInternalLibint64__abs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__abs", (RTS_UINTPTR)int64__abs, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int64__abs
	#define EXT_int64__abs
	#define GET_int64__abs(fl)  CAL_CMGETAPI( "int64__abs" ) 
	#define CAL_int64__abs  int64__abs
	#define CHK_int64__abs  TRUE
	#define EXP_int64__abs  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__abs", (RTS_UINTPTR)int64__abs, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int64__abs  PFINT64__ABS_IEC pfint64__abs;
	#define EXT_int64__abs  extern PFINT64__ABS_IEC pfint64__abs;
	#define GET_int64__abs(fl)  s_pfCMGetAPI2( "int64__abs", (RTS_VOID_FCTPTR *)&pfint64__abs, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_int64__abs  pfint64__abs
	#define CHK_int64__abs  (pfint64__abs != NULL)
	#define EXP_int64__abs   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__abs", (RTS_UINTPTR)int64__abs, 1, 0, 0) 
#endif


/**
 * <description>This function builds the minimum of two variables. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">The lesser of the two values as 64-bit integer value.</parampseudo>
 */
void CDECL CDECL_EXT int64__min(lint_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFINT64__MIN_IEC) (lint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT64__MIN_NOTIMPLEMENTED)
	#define USE_int64__min
	#define EXT_int64__min
	#define GET_int64__min(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int64__min(p0) 
	#define CHK_int64__min  FALSE
	#define EXP_int64__min  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int64__min
	#define EXT_int64__min
	#define GET_int64__min(fl)  CAL_CMGETAPI( "int64__min" ) 
	#define CAL_int64__min  int64__min
	#define CHK_int64__min  TRUE
	#define EXP_int64__min  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__min", (RTS_UINTPTR)int64__min, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int64__min
	#define EXT_int64__min
	#define GET_int64__min(fl)  CAL_CMGETAPI( "int64__min" ) 
	#define CAL_int64__min  int64__min
	#define CHK_int64__min  TRUE
	#define EXP_int64__min  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__min", (RTS_UINTPTR)int64__min, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint64__min
	#define EXT_SysInternalLibint64__min
	#define GET_SysInternalLibint64__min  ERR_OK
	#define CAL_SysInternalLibint64__min  int64__min
	#define CHK_SysInternalLibint64__min  TRUE
	#define EXP_SysInternalLibint64__min  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__min", (RTS_UINTPTR)int64__min, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int64__min
	#define EXT_int64__min
	#define GET_int64__min(fl)  CAL_CMGETAPI( "int64__min" ) 
	#define CAL_int64__min  int64__min
	#define CHK_int64__min  TRUE
	#define EXP_int64__min  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__min", (RTS_UINTPTR)int64__min, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int64__min  PFINT64__MIN_IEC pfint64__min;
	#define EXT_int64__min  extern PFINT64__MIN_IEC pfint64__min;
	#define GET_int64__min(fl)  s_pfCMGetAPI2( "int64__min", (RTS_VOID_FCTPTR *)&pfint64__min, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_int64__min  pfint64__min
	#define CHK_int64__min  (pfint64__min != NULL)
	#define EXP_int64__min   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__min", (RTS_UINTPTR)int64__min, 1, 0, 0) 
#endif


/**
 * <description>This function builds the maximum of two variables. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">The greater of the two values as 64-bit integer value.</parampseudo>
 */
void CDECL CDECL_EXT int64__max(lint_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFINT64__MAX_IEC) (lint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT64__MAX_NOTIMPLEMENTED)
	#define USE_int64__max
	#define EXT_int64__max
	#define GET_int64__max(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int64__max(p0) 
	#define CHK_int64__max  FALSE
	#define EXP_int64__max  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int64__max
	#define EXT_int64__max
	#define GET_int64__max(fl)  CAL_CMGETAPI( "int64__max" ) 
	#define CAL_int64__max  int64__max
	#define CHK_int64__max  TRUE
	#define EXP_int64__max  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__max", (RTS_UINTPTR)int64__max, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int64__max
	#define EXT_int64__max
	#define GET_int64__max(fl)  CAL_CMGETAPI( "int64__max" ) 
	#define CAL_int64__max  int64__max
	#define CHK_int64__max  TRUE
	#define EXP_int64__max  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__max", (RTS_UINTPTR)int64__max, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint64__max
	#define EXT_SysInternalLibint64__max
	#define GET_SysInternalLibint64__max  ERR_OK
	#define CAL_SysInternalLibint64__max  int64__max
	#define CHK_SysInternalLibint64__max  TRUE
	#define EXP_SysInternalLibint64__max  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__max", (RTS_UINTPTR)int64__max, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int64__max
	#define EXT_int64__max
	#define GET_int64__max(fl)  CAL_CMGETAPI( "int64__max" ) 
	#define CAL_int64__max  int64__max
	#define CHK_int64__max  TRUE
	#define EXP_int64__max  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__max", (RTS_UINTPTR)int64__max, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int64__max  PFINT64__MAX_IEC pfint64__max;
	#define EXT_int64__max  extern PFINT64__MAX_IEC pfint64__max;
	#define GET_int64__max(fl)  s_pfCMGetAPI2( "int64__max", (RTS_VOID_FCTPTR *)&pfint64__max, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_int64__max  pfint64__max
	#define CHK_int64__max  (pfint64__max != NULL)
	#define EXP_int64__max   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__max", (RTS_UINTPTR)int64__max, 1, 0, 0) 
#endif


/**
 * <description>This function limits an input value to a lower and an upper bound. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_3OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Lower bound</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input value</parampseudo>
 * <parampseudo name="in3" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Upper bound</parampseudo>
 * <parampseudo name="out" type="OUT">in2 if in2 is in the range between in1 and in3, in1 if in2 is lower than in1, in3 if in2 is greater than in3. The result is a 64-bit integer value.</parampseudo>
 */
void CDECL CDECL_EXT int64__limit(lint_3op_struct* p);
typedef void (CDECL CDECL_EXT* PFINT64__LIMIT_IEC) (lint_3op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT64__LIMIT_NOTIMPLEMENTED)
	#define USE_int64__limit
	#define EXT_int64__limit
	#define GET_int64__limit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int64__limit(p0) 
	#define CHK_int64__limit  FALSE
	#define EXP_int64__limit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int64__limit
	#define EXT_int64__limit
	#define GET_int64__limit(fl)  CAL_CMGETAPI( "int64__limit" ) 
	#define CAL_int64__limit  int64__limit
	#define CHK_int64__limit  TRUE
	#define EXP_int64__limit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__limit", (RTS_UINTPTR)int64__limit, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int64__limit
	#define EXT_int64__limit
	#define GET_int64__limit(fl)  CAL_CMGETAPI( "int64__limit" ) 
	#define CAL_int64__limit  int64__limit
	#define CHK_int64__limit  TRUE
	#define EXP_int64__limit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__limit", (RTS_UINTPTR)int64__limit, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint64__limit
	#define EXT_SysInternalLibint64__limit
	#define GET_SysInternalLibint64__limit  ERR_OK
	#define CAL_SysInternalLibint64__limit  int64__limit
	#define CHK_SysInternalLibint64__limit  TRUE
	#define EXP_SysInternalLibint64__limit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__limit", (RTS_UINTPTR)int64__limit, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int64__limit
	#define EXT_int64__limit
	#define GET_int64__limit(fl)  CAL_CMGETAPI( "int64__limit" ) 
	#define CAL_int64__limit  int64__limit
	#define CHK_int64__limit  TRUE
	#define EXP_int64__limit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__limit", (RTS_UINTPTR)int64__limit, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int64__limit  PFINT64__LIMIT_IEC pfint64__limit;
	#define EXT_int64__limit  extern PFINT64__LIMIT_IEC pfint64__limit;
	#define GET_int64__limit(fl)  s_pfCMGetAPI2( "int64__limit", (RTS_VOID_FCTPTR *)&pfint64__limit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_int64__limit  pfint64__limit
	#define CHK_int64__limit  (pfint64__limit != NULL)
	#define EXP_int64__limit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__limit", (RTS_UINTPTR)int64__limit, 1, 0, 0) 
#endif


/**
 * <description>This function determines if two operands equal. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if the input values are equal, 0 if they are not equal. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT int64__eq(lint_cmp_struct* p);
typedef void (CDECL CDECL_EXT* PFINT64__EQ_IEC) (lint_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT64__EQ_NOTIMPLEMENTED)
	#define USE_int64__eq
	#define EXT_int64__eq
	#define GET_int64__eq(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int64__eq(p0) 
	#define CHK_int64__eq  FALSE
	#define EXP_int64__eq  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int64__eq
	#define EXT_int64__eq
	#define GET_int64__eq(fl)  CAL_CMGETAPI( "int64__eq" ) 
	#define CAL_int64__eq  int64__eq
	#define CHK_int64__eq  TRUE
	#define EXP_int64__eq  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__eq", (RTS_UINTPTR)int64__eq, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int64__eq
	#define EXT_int64__eq
	#define GET_int64__eq(fl)  CAL_CMGETAPI( "int64__eq" ) 
	#define CAL_int64__eq  int64__eq
	#define CHK_int64__eq  TRUE
	#define EXP_int64__eq  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__eq", (RTS_UINTPTR)int64__eq, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint64__eq
	#define EXT_SysInternalLibint64__eq
	#define GET_SysInternalLibint64__eq  ERR_OK
	#define CAL_SysInternalLibint64__eq  int64__eq
	#define CHK_SysInternalLibint64__eq  TRUE
	#define EXP_SysInternalLibint64__eq  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__eq", (RTS_UINTPTR)int64__eq, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int64__eq
	#define EXT_int64__eq
	#define GET_int64__eq(fl)  CAL_CMGETAPI( "int64__eq" ) 
	#define CAL_int64__eq  int64__eq
	#define CHK_int64__eq  TRUE
	#define EXP_int64__eq  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__eq", (RTS_UINTPTR)int64__eq, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int64__eq  PFINT64__EQ_IEC pfint64__eq;
	#define EXT_int64__eq  extern PFINT64__EQ_IEC pfint64__eq;
	#define GET_int64__eq(fl)  s_pfCMGetAPI2( "int64__eq", (RTS_VOID_FCTPTR *)&pfint64__eq, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_int64__eq  pfint64__eq
	#define CHK_int64__eq  (pfint64__eq != NULL)
	#define EXP_int64__eq   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__eq", (RTS_UINTPTR)int64__eq, 1, 0, 0) 
#endif


/**
 * <description>This function determines if two operands are not equal. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if the input values are not equal, 0 if they are equal. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT int64__ne(lint_cmp_struct* p);
typedef void (CDECL CDECL_EXT* PFINT64__NE_IEC) (lint_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT64__NE_NOTIMPLEMENTED)
	#define USE_int64__ne
	#define EXT_int64__ne
	#define GET_int64__ne(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int64__ne(p0) 
	#define CHK_int64__ne  FALSE
	#define EXP_int64__ne  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int64__ne
	#define EXT_int64__ne
	#define GET_int64__ne(fl)  CAL_CMGETAPI( "int64__ne" ) 
	#define CAL_int64__ne  int64__ne
	#define CHK_int64__ne  TRUE
	#define EXP_int64__ne  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__ne", (RTS_UINTPTR)int64__ne, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int64__ne
	#define EXT_int64__ne
	#define GET_int64__ne(fl)  CAL_CMGETAPI( "int64__ne" ) 
	#define CAL_int64__ne  int64__ne
	#define CHK_int64__ne  TRUE
	#define EXP_int64__ne  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__ne", (RTS_UINTPTR)int64__ne, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint64__ne
	#define EXT_SysInternalLibint64__ne
	#define GET_SysInternalLibint64__ne  ERR_OK
	#define CAL_SysInternalLibint64__ne  int64__ne
	#define CHK_SysInternalLibint64__ne  TRUE
	#define EXP_SysInternalLibint64__ne  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__ne", (RTS_UINTPTR)int64__ne, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int64__ne
	#define EXT_int64__ne
	#define GET_int64__ne(fl)  CAL_CMGETAPI( "int64__ne" ) 
	#define CAL_int64__ne  int64__ne
	#define CHK_int64__ne  TRUE
	#define EXP_int64__ne  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__ne", (RTS_UINTPTR)int64__ne, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int64__ne  PFINT64__NE_IEC pfint64__ne;
	#define EXT_int64__ne  extern PFINT64__NE_IEC pfint64__ne;
	#define GET_int64__ne(fl)  s_pfCMGetAPI2( "int64__ne", (RTS_VOID_FCTPTR *)&pfint64__ne, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_int64__ne  pfint64__ne
	#define CHK_int64__ne  (pfint64__ne != NULL)
	#define EXP_int64__ne   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__ne", (RTS_UINTPTR)int64__ne, 1, 0, 0) 
#endif


/**
 * <description>This function determines if an operand is lower than another. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is lower than in2, 0 if in1 is not lower than in2. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT int64__lt(lint_cmp_struct* p);
typedef void (CDECL CDECL_EXT* PFINT64__LT_IEC) (lint_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT64__LT_NOTIMPLEMENTED)
	#define USE_int64__lt
	#define EXT_int64__lt
	#define GET_int64__lt(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int64__lt(p0) 
	#define CHK_int64__lt  FALSE
	#define EXP_int64__lt  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int64__lt
	#define EXT_int64__lt
	#define GET_int64__lt(fl)  CAL_CMGETAPI( "int64__lt" ) 
	#define CAL_int64__lt  int64__lt
	#define CHK_int64__lt  TRUE
	#define EXP_int64__lt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__lt", (RTS_UINTPTR)int64__lt, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int64__lt
	#define EXT_int64__lt
	#define GET_int64__lt(fl)  CAL_CMGETAPI( "int64__lt" ) 
	#define CAL_int64__lt  int64__lt
	#define CHK_int64__lt  TRUE
	#define EXP_int64__lt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__lt", (RTS_UINTPTR)int64__lt, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint64__lt
	#define EXT_SysInternalLibint64__lt
	#define GET_SysInternalLibint64__lt  ERR_OK
	#define CAL_SysInternalLibint64__lt  int64__lt
	#define CHK_SysInternalLibint64__lt  TRUE
	#define EXP_SysInternalLibint64__lt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__lt", (RTS_UINTPTR)int64__lt, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int64__lt
	#define EXT_int64__lt
	#define GET_int64__lt(fl)  CAL_CMGETAPI( "int64__lt" ) 
	#define CAL_int64__lt  int64__lt
	#define CHK_int64__lt  TRUE
	#define EXP_int64__lt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__lt", (RTS_UINTPTR)int64__lt, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int64__lt  PFINT64__LT_IEC pfint64__lt;
	#define EXT_int64__lt  extern PFINT64__LT_IEC pfint64__lt;
	#define GET_int64__lt(fl)  s_pfCMGetAPI2( "int64__lt", (RTS_VOID_FCTPTR *)&pfint64__lt, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_int64__lt  pfint64__lt
	#define CHK_int64__lt  (pfint64__lt != NULL)
	#define EXP_int64__lt   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__lt", (RTS_UINTPTR)int64__lt, 1, 0, 0) 
#endif


/**
 * <description>This function determines if an operand is lower or equal than another. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is lower or equal than in2, 0 if in1 is not lower or equal than in2. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT int64__le(lint_cmp_struct* p);
typedef void (CDECL CDECL_EXT* PFINT64__LE_IEC) (lint_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT64__LE_NOTIMPLEMENTED)
	#define USE_int64__le
	#define EXT_int64__le
	#define GET_int64__le(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int64__le(p0) 
	#define CHK_int64__le  FALSE
	#define EXP_int64__le  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int64__le
	#define EXT_int64__le
	#define GET_int64__le(fl)  CAL_CMGETAPI( "int64__le" ) 
	#define CAL_int64__le  int64__le
	#define CHK_int64__le  TRUE
	#define EXP_int64__le  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__le", (RTS_UINTPTR)int64__le, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int64__le
	#define EXT_int64__le
	#define GET_int64__le(fl)  CAL_CMGETAPI( "int64__le" ) 
	#define CAL_int64__le  int64__le
	#define CHK_int64__le  TRUE
	#define EXP_int64__le  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__le", (RTS_UINTPTR)int64__le, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint64__le
	#define EXT_SysInternalLibint64__le
	#define GET_SysInternalLibint64__le  ERR_OK
	#define CAL_SysInternalLibint64__le  int64__le
	#define CHK_SysInternalLibint64__le  TRUE
	#define EXP_SysInternalLibint64__le  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__le", (RTS_UINTPTR)int64__le, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int64__le
	#define EXT_int64__le
	#define GET_int64__le(fl)  CAL_CMGETAPI( "int64__le" ) 
	#define CAL_int64__le  int64__le
	#define CHK_int64__le  TRUE
	#define EXP_int64__le  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__le", (RTS_UINTPTR)int64__le, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int64__le  PFINT64__LE_IEC pfint64__le;
	#define EXT_int64__le  extern PFINT64__LE_IEC pfint64__le;
	#define GET_int64__le(fl)  s_pfCMGetAPI2( "int64__le", (RTS_VOID_FCTPTR *)&pfint64__le, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_int64__le  pfint64__le
	#define CHK_int64__le  (pfint64__le != NULL)
	#define EXP_int64__le   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__le", (RTS_UINTPTR)int64__le, 1, 0, 0) 
#endif


/**
 * <description>This function determines if an operand is greater than another. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is greater than in2, 0 if in1 is not greater than in2. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT int64__gt(lint_cmp_struct* p);
typedef void (CDECL CDECL_EXT* PFINT64__GT_IEC) (lint_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT64__GT_NOTIMPLEMENTED)
	#define USE_int64__gt
	#define EXT_int64__gt
	#define GET_int64__gt(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int64__gt(p0) 
	#define CHK_int64__gt  FALSE
	#define EXP_int64__gt  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int64__gt
	#define EXT_int64__gt
	#define GET_int64__gt(fl)  CAL_CMGETAPI( "int64__gt" ) 
	#define CAL_int64__gt  int64__gt
	#define CHK_int64__gt  TRUE
	#define EXP_int64__gt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__gt", (RTS_UINTPTR)int64__gt, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int64__gt
	#define EXT_int64__gt
	#define GET_int64__gt(fl)  CAL_CMGETAPI( "int64__gt" ) 
	#define CAL_int64__gt  int64__gt
	#define CHK_int64__gt  TRUE
	#define EXP_int64__gt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__gt", (RTS_UINTPTR)int64__gt, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint64__gt
	#define EXT_SysInternalLibint64__gt
	#define GET_SysInternalLibint64__gt  ERR_OK
	#define CAL_SysInternalLibint64__gt  int64__gt
	#define CHK_SysInternalLibint64__gt  TRUE
	#define EXP_SysInternalLibint64__gt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__gt", (RTS_UINTPTR)int64__gt, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int64__gt
	#define EXT_int64__gt
	#define GET_int64__gt(fl)  CAL_CMGETAPI( "int64__gt" ) 
	#define CAL_int64__gt  int64__gt
	#define CHK_int64__gt  TRUE
	#define EXP_int64__gt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__gt", (RTS_UINTPTR)int64__gt, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int64__gt  PFINT64__GT_IEC pfint64__gt;
	#define EXT_int64__gt  extern PFINT64__GT_IEC pfint64__gt;
	#define GET_int64__gt(fl)  s_pfCMGetAPI2( "int64__gt", (RTS_VOID_FCTPTR *)&pfint64__gt, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_int64__gt  pfint64__gt
	#define CHK_int64__gt  (pfint64__gt != NULL)
	#define EXP_int64__gt   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__gt", (RTS_UINTPTR)int64__gt, 1, 0, 0) 
#endif


/**
 * <description>This function determines if an operand is greater or equal than another. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is greater or equal than in2, 0 if in1 is not greater or equal than in2. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT int64__ge(lint_cmp_struct* p);
typedef void (CDECL CDECL_EXT* PFINT64__GE_IEC) (lint_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT64__GE_NOTIMPLEMENTED)
	#define USE_int64__ge
	#define EXT_int64__ge
	#define GET_int64__ge(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int64__ge(p0) 
	#define CHK_int64__ge  FALSE
	#define EXP_int64__ge  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int64__ge
	#define EXT_int64__ge
	#define GET_int64__ge(fl)  CAL_CMGETAPI( "int64__ge" ) 
	#define CAL_int64__ge  int64__ge
	#define CHK_int64__ge  TRUE
	#define EXP_int64__ge  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__ge", (RTS_UINTPTR)int64__ge, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int64__ge
	#define EXT_int64__ge
	#define GET_int64__ge(fl)  CAL_CMGETAPI( "int64__ge" ) 
	#define CAL_int64__ge  int64__ge
	#define CHK_int64__ge  TRUE
	#define EXP_int64__ge  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__ge", (RTS_UINTPTR)int64__ge, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint64__ge
	#define EXT_SysInternalLibint64__ge
	#define GET_SysInternalLibint64__ge  ERR_OK
	#define CAL_SysInternalLibint64__ge  int64__ge
	#define CHK_SysInternalLibint64__ge  TRUE
	#define EXP_SysInternalLibint64__ge  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__ge", (RTS_UINTPTR)int64__ge, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int64__ge
	#define EXT_int64__ge
	#define GET_int64__ge(fl)  CAL_CMGETAPI( "int64__ge" ) 
	#define CAL_int64__ge  int64__ge
	#define CHK_int64__ge  TRUE
	#define EXP_int64__ge  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__ge", (RTS_UINTPTR)int64__ge, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int64__ge  PFINT64__GE_IEC pfint64__ge;
	#define EXT_int64__ge  extern PFINT64__GE_IEC pfint64__ge;
	#define GET_int64__ge(fl)  s_pfCMGetAPI2( "int64__ge", (RTS_VOID_FCTPTR *)&pfint64__ge, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_int64__ge  pfint64__ge
	#define CHK_int64__ge  (pfint64__ge != NULL)
	#define EXP_int64__ge   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__ge", (RTS_UINTPTR)int64__ge, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function makes a bitwise right-shift on a 64-bit integer value.</p>
 * <p>The the newly exposed bits will be filled with the value of the topmost bit, that is 1 for negative and 0 for positive input values.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_LINT_SHIFT_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Operand to be shifted to the right</parampseudo>
 * <parampseudo name="in2" type="IN" range="[0..63,64]">Number of bits, by which the operand gets shifted to the right</parampseudo>
 * <parampseudo name="out" type="OUT">Bitwise right-shifted 64-bit integer value.</parampseudo>
 */
void CDECL CDECL_EXT int64__shr(lint_shift_struct* p);
typedef void (CDECL CDECL_EXT* PFINT64__SHR_IEC) (lint_shift_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT64__SHR_NOTIMPLEMENTED)
	#define USE_int64__shr
	#define EXT_int64__shr
	#define GET_int64__shr(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int64__shr(p0) 
	#define CHK_int64__shr  FALSE
	#define EXP_int64__shr  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int64__shr
	#define EXT_int64__shr
	#define GET_int64__shr(fl)  CAL_CMGETAPI( "int64__shr" ) 
	#define CAL_int64__shr  int64__shr
	#define CHK_int64__shr  TRUE
	#define EXP_int64__shr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__shr", (RTS_UINTPTR)int64__shr, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int64__shr
	#define EXT_int64__shr
	#define GET_int64__shr(fl)  CAL_CMGETAPI( "int64__shr" ) 
	#define CAL_int64__shr  int64__shr
	#define CHK_int64__shr  TRUE
	#define EXP_int64__shr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__shr", (RTS_UINTPTR)int64__shr, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint64__shr
	#define EXT_SysInternalLibint64__shr
	#define GET_SysInternalLibint64__shr  ERR_OK
	#define CAL_SysInternalLibint64__shr  int64__shr
	#define CHK_SysInternalLibint64__shr  TRUE
	#define EXP_SysInternalLibint64__shr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__shr", (RTS_UINTPTR)int64__shr, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int64__shr
	#define EXT_int64__shr
	#define GET_int64__shr(fl)  CAL_CMGETAPI( "int64__shr" ) 
	#define CAL_int64__shr  int64__shr
	#define CHK_int64__shr  TRUE
	#define EXP_int64__shr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__shr", (RTS_UINTPTR)int64__shr, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int64__shr  PFINT64__SHR_IEC pfint64__shr;
	#define EXT_int64__shr  extern PFINT64__SHR_IEC pfint64__shr;
	#define GET_int64__shr(fl)  s_pfCMGetAPI2( "int64__shr", (RTS_VOID_FCTPTR *)&pfint64__shr, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_int64__shr  pfint64__shr
	#define CHK_int64__shr  (pfint64__shr != NULL)
	#define EXP_int64__shr   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__shr", (RTS_UINTPTR)int64__shr, 1, 0, 0) 
#endif


/**
 * <description>This function makes an addition of two 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">First summand</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Second summand</parampseudo>
 * <parampseudo name="out" type="OUT">Sum of the two input values as 64-bit unsigned integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint64__add(ulint_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFUINT64__ADD_IEC) (ulint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT64__ADD_NOTIMPLEMENTED)
	#define USE_uint64__add
	#define EXT_uint64__add
	#define GET_uint64__add(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint64__add(p0) 
	#define CHK_uint64__add  FALSE
	#define EXP_uint64__add  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint64__add
	#define EXT_uint64__add
	#define GET_uint64__add(fl)  CAL_CMGETAPI( "uint64__add" ) 
	#define CAL_uint64__add  uint64__add
	#define CHK_uint64__add  TRUE
	#define EXP_uint64__add  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__add", (RTS_UINTPTR)uint64__add, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint64__add
	#define EXT_uint64__add
	#define GET_uint64__add(fl)  CAL_CMGETAPI( "uint64__add" ) 
	#define CAL_uint64__add  uint64__add
	#define CHK_uint64__add  TRUE
	#define EXP_uint64__add  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__add", (RTS_UINTPTR)uint64__add, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint64__add
	#define EXT_SysInternalLibuint64__add
	#define GET_SysInternalLibuint64__add  ERR_OK
	#define CAL_SysInternalLibuint64__add  uint64__add
	#define CHK_SysInternalLibuint64__add  TRUE
	#define EXP_SysInternalLibuint64__add  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__add", (RTS_UINTPTR)uint64__add, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint64__add
	#define EXT_uint64__add
	#define GET_uint64__add(fl)  CAL_CMGETAPI( "uint64__add" ) 
	#define CAL_uint64__add  uint64__add
	#define CHK_uint64__add  TRUE
	#define EXP_uint64__add  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__add", (RTS_UINTPTR)uint64__add, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint64__add  PFUINT64__ADD_IEC pfuint64__add;
	#define EXT_uint64__add  extern PFUINT64__ADD_IEC pfuint64__add;
	#define GET_uint64__add(fl)  s_pfCMGetAPI2( "uint64__add", (RTS_VOID_FCTPTR *)&pfuint64__add, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_uint64__add  pfuint64__add
	#define CHK_uint64__add  (pfuint64__add != NULL)
	#define EXP_uint64__add   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__add", (RTS_UINTPTR)uint64__add, 1, 0, 0) 
#endif


/**
 * <description>This function makes a subtraction of one variable from another one. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Minuend</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Subtrahend</parampseudo>
 * <parampseudo name="out" type="OUT">Difference of the two input values as 64-bit unsigned integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint64__sub(ulint_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFUINT64__SUB_IEC) (ulint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT64__SUB_NOTIMPLEMENTED)
	#define USE_uint64__sub
	#define EXT_uint64__sub
	#define GET_uint64__sub(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint64__sub(p0) 
	#define CHK_uint64__sub  FALSE
	#define EXP_uint64__sub  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint64__sub
	#define EXT_uint64__sub
	#define GET_uint64__sub(fl)  CAL_CMGETAPI( "uint64__sub" ) 
	#define CAL_uint64__sub  uint64__sub
	#define CHK_uint64__sub  TRUE
	#define EXP_uint64__sub  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__sub", (RTS_UINTPTR)uint64__sub, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint64__sub
	#define EXT_uint64__sub
	#define GET_uint64__sub(fl)  CAL_CMGETAPI( "uint64__sub" ) 
	#define CAL_uint64__sub  uint64__sub
	#define CHK_uint64__sub  TRUE
	#define EXP_uint64__sub  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__sub", (RTS_UINTPTR)uint64__sub, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint64__sub
	#define EXT_SysInternalLibuint64__sub
	#define GET_SysInternalLibuint64__sub  ERR_OK
	#define CAL_SysInternalLibuint64__sub  uint64__sub
	#define CHK_SysInternalLibuint64__sub  TRUE
	#define EXP_SysInternalLibuint64__sub  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__sub", (RTS_UINTPTR)uint64__sub, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint64__sub
	#define EXT_uint64__sub
	#define GET_uint64__sub(fl)  CAL_CMGETAPI( "uint64__sub" ) 
	#define CAL_uint64__sub  uint64__sub
	#define CHK_uint64__sub  TRUE
	#define EXP_uint64__sub  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__sub", (RTS_UINTPTR)uint64__sub, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint64__sub  PFUINT64__SUB_IEC pfuint64__sub;
	#define EXT_uint64__sub  extern PFUINT64__SUB_IEC pfuint64__sub;
	#define GET_uint64__sub(fl)  s_pfCMGetAPI2( "uint64__sub", (RTS_VOID_FCTPTR *)&pfuint64__sub, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_uint64__sub  pfuint64__sub
	#define CHK_uint64__sub  (pfuint64__sub != NULL)
	#define EXP_uint64__sub   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__sub", (RTS_UINTPTR)uint64__sub, 1, 0, 0) 
#endif


/**
 * <description>This function makes a multiplication of two variables. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">First factor</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Second factor</parampseudo>
 * <parampseudo name="out" type="OUT">Product of the two input values as 64-bit unsigned integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint64__mul(ulint_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFUINT64__MUL_IEC) (ulint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT64__MUL_NOTIMPLEMENTED)
	#define USE_uint64__mul
	#define EXT_uint64__mul
	#define GET_uint64__mul(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint64__mul(p0) 
	#define CHK_uint64__mul  FALSE
	#define EXP_uint64__mul  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint64__mul
	#define EXT_uint64__mul
	#define GET_uint64__mul(fl)  CAL_CMGETAPI( "uint64__mul" ) 
	#define CAL_uint64__mul  uint64__mul
	#define CHK_uint64__mul  TRUE
	#define EXP_uint64__mul  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__mul", (RTS_UINTPTR)uint64__mul, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint64__mul
	#define EXT_uint64__mul
	#define GET_uint64__mul(fl)  CAL_CMGETAPI( "uint64__mul" ) 
	#define CAL_uint64__mul  uint64__mul
	#define CHK_uint64__mul  TRUE
	#define EXP_uint64__mul  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__mul", (RTS_UINTPTR)uint64__mul, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint64__mul
	#define EXT_SysInternalLibuint64__mul
	#define GET_SysInternalLibuint64__mul  ERR_OK
	#define CAL_SysInternalLibuint64__mul  uint64__mul
	#define CHK_SysInternalLibuint64__mul  TRUE
	#define EXP_SysInternalLibuint64__mul  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__mul", (RTS_UINTPTR)uint64__mul, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint64__mul
	#define EXT_uint64__mul
	#define GET_uint64__mul(fl)  CAL_CMGETAPI( "uint64__mul" ) 
	#define CAL_uint64__mul  uint64__mul
	#define CHK_uint64__mul  TRUE
	#define EXP_uint64__mul  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__mul", (RTS_UINTPTR)uint64__mul, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint64__mul  PFUINT64__MUL_IEC pfuint64__mul;
	#define EXT_uint64__mul  extern PFUINT64__MUL_IEC pfuint64__mul;
	#define GET_uint64__mul(fl)  s_pfCMGetAPI2( "uint64__mul", (RTS_VOID_FCTPTR *)&pfuint64__mul, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_uint64__mul  pfuint64__mul
	#define CHK_uint64__mul  (pfuint64__mul != NULL)
	#define EXP_uint64__mul   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__mul", (RTS_UINTPTR)uint64__mul, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function makes a division of two variables. The inputs are 64-bit unsigned integer values.</p>
 * <p>The behaviour for divisor = 0 might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_ULINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Dividend</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Divisor</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception thrown</parampseudo>
 * <parampseudo name="out" type="OUT">Quotient of the two input values as 64-bit unsigned integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint64__div(ulint_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFUINT64__DIV_IEC) (ulint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT64__DIV_NOTIMPLEMENTED)
	#define USE_uint64__div
	#define EXT_uint64__div
	#define GET_uint64__div(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint64__div(p0) 
	#define CHK_uint64__div  FALSE
	#define EXP_uint64__div  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint64__div
	#define EXT_uint64__div
	#define GET_uint64__div(fl)  CAL_CMGETAPI( "uint64__div" ) 
	#define CAL_uint64__div  uint64__div
	#define CHK_uint64__div  TRUE
	#define EXP_uint64__div  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__div", (RTS_UINTPTR)uint64__div, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint64__div
	#define EXT_uint64__div
	#define GET_uint64__div(fl)  CAL_CMGETAPI( "uint64__div" ) 
	#define CAL_uint64__div  uint64__div
	#define CHK_uint64__div  TRUE
	#define EXP_uint64__div  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__div", (RTS_UINTPTR)uint64__div, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint64__div
	#define EXT_SysInternalLibuint64__div
	#define GET_SysInternalLibuint64__div  ERR_OK
	#define CAL_SysInternalLibuint64__div  uint64__div
	#define CHK_SysInternalLibuint64__div  TRUE
	#define EXP_SysInternalLibuint64__div  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__div", (RTS_UINTPTR)uint64__div, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint64__div
	#define EXT_uint64__div
	#define GET_uint64__div(fl)  CAL_CMGETAPI( "uint64__div" ) 
	#define CAL_uint64__div  uint64__div
	#define CHK_uint64__div  TRUE
	#define EXP_uint64__div  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__div", (RTS_UINTPTR)uint64__div, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint64__div  PFUINT64__DIV_IEC pfuint64__div;
	#define EXT_uint64__div  extern PFUINT64__DIV_IEC pfuint64__div;
	#define GET_uint64__div(fl)  s_pfCMGetAPI2( "uint64__div", (RTS_VOID_FCTPTR *)&pfuint64__div, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_uint64__div  pfuint64__div
	#define CHK_uint64__div  (pfuint64__div != NULL)
	#define EXP_uint64__div   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__div", (RTS_UINTPTR)uint64__div, 1, 0, 0) 
#endif


/**
 * <description>This function calculates the remainder of division of one variable by another. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Dividend</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Divisor</parampseudo>
 * <parampseudo name="out" type="OUT">Remainder of division of the two input values as 64-bit unsigned integer value, or 0 if the divisor is 0.</parampseudo>
 */
void CDECL CDECL_EXT uint64__mod(ulint_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFUINT64__MOD_IEC) (ulint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT64__MOD_NOTIMPLEMENTED)
	#define USE_uint64__mod
	#define EXT_uint64__mod
	#define GET_uint64__mod(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint64__mod(p0) 
	#define CHK_uint64__mod  FALSE
	#define EXP_uint64__mod  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint64__mod
	#define EXT_uint64__mod
	#define GET_uint64__mod(fl)  CAL_CMGETAPI( "uint64__mod" ) 
	#define CAL_uint64__mod  uint64__mod
	#define CHK_uint64__mod  TRUE
	#define EXP_uint64__mod  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__mod", (RTS_UINTPTR)uint64__mod, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint64__mod
	#define EXT_uint64__mod
	#define GET_uint64__mod(fl)  CAL_CMGETAPI( "uint64__mod" ) 
	#define CAL_uint64__mod  uint64__mod
	#define CHK_uint64__mod  TRUE
	#define EXP_uint64__mod  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__mod", (RTS_UINTPTR)uint64__mod, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint64__mod
	#define EXT_SysInternalLibuint64__mod
	#define GET_SysInternalLibuint64__mod  ERR_OK
	#define CAL_SysInternalLibuint64__mod  uint64__mod
	#define CHK_SysInternalLibuint64__mod  TRUE
	#define EXP_SysInternalLibuint64__mod  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__mod", (RTS_UINTPTR)uint64__mod, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint64__mod
	#define EXT_uint64__mod
	#define GET_uint64__mod(fl)  CAL_CMGETAPI( "uint64__mod" ) 
	#define CAL_uint64__mod  uint64__mod
	#define CHK_uint64__mod  TRUE
	#define EXP_uint64__mod  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__mod", (RTS_UINTPTR)uint64__mod, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint64__mod  PFUINT64__MOD_IEC pfuint64__mod;
	#define EXT_uint64__mod  extern PFUINT64__MOD_IEC pfuint64__mod;
	#define GET_uint64__mod(fl)  s_pfCMGetAPI2( "uint64__mod", (RTS_VOID_FCTPTR *)&pfuint64__mod, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_uint64__mod  pfuint64__mod
	#define CHK_uint64__mod  (pfuint64__mod != NULL)
	#define EXP_uint64__mod   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__mod", (RTS_UINTPTR)uint64__mod, 1, 0, 0) 
#endif


/**
 * <description>This function builds the minimum of two variables. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">The lesser of the two values as 64-bit unsigned integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint64__min(ulint_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFUINT64__MIN_IEC) (ulint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT64__MIN_NOTIMPLEMENTED)
	#define USE_uint64__min
	#define EXT_uint64__min
	#define GET_uint64__min(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint64__min(p0) 
	#define CHK_uint64__min  FALSE
	#define EXP_uint64__min  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint64__min
	#define EXT_uint64__min
	#define GET_uint64__min(fl)  CAL_CMGETAPI( "uint64__min" ) 
	#define CAL_uint64__min  uint64__min
	#define CHK_uint64__min  TRUE
	#define EXP_uint64__min  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__min", (RTS_UINTPTR)uint64__min, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint64__min
	#define EXT_uint64__min
	#define GET_uint64__min(fl)  CAL_CMGETAPI( "uint64__min" ) 
	#define CAL_uint64__min  uint64__min
	#define CHK_uint64__min  TRUE
	#define EXP_uint64__min  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__min", (RTS_UINTPTR)uint64__min, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint64__min
	#define EXT_SysInternalLibuint64__min
	#define GET_SysInternalLibuint64__min  ERR_OK
	#define CAL_SysInternalLibuint64__min  uint64__min
	#define CHK_SysInternalLibuint64__min  TRUE
	#define EXP_SysInternalLibuint64__min  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__min", (RTS_UINTPTR)uint64__min, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint64__min
	#define EXT_uint64__min
	#define GET_uint64__min(fl)  CAL_CMGETAPI( "uint64__min" ) 
	#define CAL_uint64__min  uint64__min
	#define CHK_uint64__min  TRUE
	#define EXP_uint64__min  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__min", (RTS_UINTPTR)uint64__min, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint64__min  PFUINT64__MIN_IEC pfuint64__min;
	#define EXT_uint64__min  extern PFUINT64__MIN_IEC pfuint64__min;
	#define GET_uint64__min(fl)  s_pfCMGetAPI2( "uint64__min", (RTS_VOID_FCTPTR *)&pfuint64__min, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_uint64__min  pfuint64__min
	#define CHK_uint64__min  (pfuint64__min != NULL)
	#define EXP_uint64__min   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__min", (RTS_UINTPTR)uint64__min, 1, 0, 0) 
#endif


/**
 * <description>This function builds the maximum of two variables. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">The greater of the two values as 64-bit unsigned integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint64__max(ulint_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFUINT64__MAX_IEC) (ulint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT64__MAX_NOTIMPLEMENTED)
	#define USE_uint64__max
	#define EXT_uint64__max
	#define GET_uint64__max(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint64__max(p0) 
	#define CHK_uint64__max  FALSE
	#define EXP_uint64__max  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint64__max
	#define EXT_uint64__max
	#define GET_uint64__max(fl)  CAL_CMGETAPI( "uint64__max" ) 
	#define CAL_uint64__max  uint64__max
	#define CHK_uint64__max  TRUE
	#define EXP_uint64__max  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__max", (RTS_UINTPTR)uint64__max, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint64__max
	#define EXT_uint64__max
	#define GET_uint64__max(fl)  CAL_CMGETAPI( "uint64__max" ) 
	#define CAL_uint64__max  uint64__max
	#define CHK_uint64__max  TRUE
	#define EXP_uint64__max  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__max", (RTS_UINTPTR)uint64__max, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint64__max
	#define EXT_SysInternalLibuint64__max
	#define GET_SysInternalLibuint64__max  ERR_OK
	#define CAL_SysInternalLibuint64__max  uint64__max
	#define CHK_SysInternalLibuint64__max  TRUE
	#define EXP_SysInternalLibuint64__max  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__max", (RTS_UINTPTR)uint64__max, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint64__max
	#define EXT_uint64__max
	#define GET_uint64__max(fl)  CAL_CMGETAPI( "uint64__max" ) 
	#define CAL_uint64__max  uint64__max
	#define CHK_uint64__max  TRUE
	#define EXP_uint64__max  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__max", (RTS_UINTPTR)uint64__max, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint64__max  PFUINT64__MAX_IEC pfuint64__max;
	#define EXT_uint64__max  extern PFUINT64__MAX_IEC pfuint64__max;
	#define GET_uint64__max(fl)  s_pfCMGetAPI2( "uint64__max", (RTS_VOID_FCTPTR *)&pfuint64__max, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_uint64__max  pfuint64__max
	#define CHK_uint64__max  (pfuint64__max != NULL)
	#define EXP_uint64__max   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__max", (RTS_UINTPTR)uint64__max, 1, 0, 0) 
#endif


/**
 * <description>This function limits an input value to a lower and an upper bound. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_3OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Lower bound</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input value</parampseudo>
 * <parampseudo name="in3" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Upper bound</parampseudo>
 * <parampseudo name="out" type="OUT">in2 if in2 is in the range between in1 and in3, in1 if in2 is lower than in1, in3 if in2 is greater than in3. The result is a 64-bit unsigned integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint64__limit(ulint_3op_struct* p);
typedef void (CDECL CDECL_EXT* PFUINT64__LIMIT_IEC) (ulint_3op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT64__LIMIT_NOTIMPLEMENTED)
	#define USE_uint64__limit
	#define EXT_uint64__limit
	#define GET_uint64__limit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint64__limit(p0) 
	#define CHK_uint64__limit  FALSE
	#define EXP_uint64__limit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint64__limit
	#define EXT_uint64__limit
	#define GET_uint64__limit(fl)  CAL_CMGETAPI( "uint64__limit" ) 
	#define CAL_uint64__limit  uint64__limit
	#define CHK_uint64__limit  TRUE
	#define EXP_uint64__limit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__limit", (RTS_UINTPTR)uint64__limit, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint64__limit
	#define EXT_uint64__limit
	#define GET_uint64__limit(fl)  CAL_CMGETAPI( "uint64__limit" ) 
	#define CAL_uint64__limit  uint64__limit
	#define CHK_uint64__limit  TRUE
	#define EXP_uint64__limit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__limit", (RTS_UINTPTR)uint64__limit, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint64__limit
	#define EXT_SysInternalLibuint64__limit
	#define GET_SysInternalLibuint64__limit  ERR_OK
	#define CAL_SysInternalLibuint64__limit  uint64__limit
	#define CHK_SysInternalLibuint64__limit  TRUE
	#define EXP_SysInternalLibuint64__limit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__limit", (RTS_UINTPTR)uint64__limit, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint64__limit
	#define EXT_uint64__limit
	#define GET_uint64__limit(fl)  CAL_CMGETAPI( "uint64__limit" ) 
	#define CAL_uint64__limit  uint64__limit
	#define CHK_uint64__limit  TRUE
	#define EXP_uint64__limit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__limit", (RTS_UINTPTR)uint64__limit, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint64__limit  PFUINT64__LIMIT_IEC pfuint64__limit;
	#define EXT_uint64__limit  extern PFUINT64__LIMIT_IEC pfuint64__limit;
	#define GET_uint64__limit(fl)  s_pfCMGetAPI2( "uint64__limit", (RTS_VOID_FCTPTR *)&pfuint64__limit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_uint64__limit  pfuint64__limit
	#define CHK_uint64__limit  (pfuint64__limit != NULL)
	#define EXP_uint64__limit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__limit", (RTS_UINTPTR)uint64__limit, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function makes a bitwise rotation to the right of a 64-bit unsigned integer value.</p>
 * <p>The input operand will be shifted one bit position to the right n times while the bit that is furthest to the left will be reinserted from the left.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_ULINT_SHIFT_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Operand to be rotated to the right</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UINT]">Number n of bits, by which the operand gets rotated to the right</parampseudo>
 * <parampseudo name="out" type="OUT">Bitwise right rotated 64-bit unsigned integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint64__ror(ulint_shift_struct* p);
typedef void (CDECL CDECL_EXT* PFUINT64__ROR_IEC) (ulint_shift_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT64__ROR_NOTIMPLEMENTED)
	#define USE_uint64__ror
	#define EXT_uint64__ror
	#define GET_uint64__ror(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint64__ror(p0) 
	#define CHK_uint64__ror  FALSE
	#define EXP_uint64__ror  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint64__ror
	#define EXT_uint64__ror
	#define GET_uint64__ror(fl)  CAL_CMGETAPI( "uint64__ror" ) 
	#define CAL_uint64__ror  uint64__ror
	#define CHK_uint64__ror  TRUE
	#define EXP_uint64__ror  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__ror", (RTS_UINTPTR)uint64__ror, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint64__ror
	#define EXT_uint64__ror
	#define GET_uint64__ror(fl)  CAL_CMGETAPI( "uint64__ror" ) 
	#define CAL_uint64__ror  uint64__ror
	#define CHK_uint64__ror  TRUE
	#define EXP_uint64__ror  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__ror", (RTS_UINTPTR)uint64__ror, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint64__ror
	#define EXT_SysInternalLibuint64__ror
	#define GET_SysInternalLibuint64__ror  ERR_OK
	#define CAL_SysInternalLibuint64__ror  uint64__ror
	#define CHK_SysInternalLibuint64__ror  TRUE
	#define EXP_SysInternalLibuint64__ror  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__ror", (RTS_UINTPTR)uint64__ror, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint64__ror
	#define EXT_uint64__ror
	#define GET_uint64__ror(fl)  CAL_CMGETAPI( "uint64__ror" ) 
	#define CAL_uint64__ror  uint64__ror
	#define CHK_uint64__ror  TRUE
	#define EXP_uint64__ror  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__ror", (RTS_UINTPTR)uint64__ror, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint64__ror  PFUINT64__ROR_IEC pfuint64__ror;
	#define EXT_uint64__ror  extern PFUINT64__ROR_IEC pfuint64__ror;
	#define GET_uint64__ror(fl)  s_pfCMGetAPI2( "uint64__ror", (RTS_VOID_FCTPTR *)&pfuint64__ror, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_uint64__ror  pfuint64__ror
	#define CHK_uint64__ror  (pfuint64__ror != NULL)
	#define EXP_uint64__ror   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__ror", (RTS_UINTPTR)uint64__ror, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function makes a bitwise rotation to the left of a 64-bit unsigned integer value.</p>
 * <p>The input operand will be shifted one bit position to the left n times while the bit that is furthest to the right will be reinserted from the right.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_ULINT_SHIFT_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Operand to be rotated to the left</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UINT]">Number n of bits, by which the operand gets rotated to the left</parampseudo>
 * <parampseudo name="out" type="OUT">Bitwise left rotated 64-bit unsigned integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint64__rol(ulint_shift_struct* p);
typedef void (CDECL CDECL_EXT* PFUINT64__ROL_IEC) (ulint_shift_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT64__ROL_NOTIMPLEMENTED)
	#define USE_uint64__rol
	#define EXT_uint64__rol
	#define GET_uint64__rol(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint64__rol(p0) 
	#define CHK_uint64__rol  FALSE
	#define EXP_uint64__rol  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint64__rol
	#define EXT_uint64__rol
	#define GET_uint64__rol(fl)  CAL_CMGETAPI( "uint64__rol" ) 
	#define CAL_uint64__rol  uint64__rol
	#define CHK_uint64__rol  TRUE
	#define EXP_uint64__rol  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__rol", (RTS_UINTPTR)uint64__rol, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint64__rol
	#define EXT_uint64__rol
	#define GET_uint64__rol(fl)  CAL_CMGETAPI( "uint64__rol" ) 
	#define CAL_uint64__rol  uint64__rol
	#define CHK_uint64__rol  TRUE
	#define EXP_uint64__rol  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__rol", (RTS_UINTPTR)uint64__rol, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint64__rol
	#define EXT_SysInternalLibuint64__rol
	#define GET_SysInternalLibuint64__rol  ERR_OK
	#define CAL_SysInternalLibuint64__rol  uint64__rol
	#define CHK_SysInternalLibuint64__rol  TRUE
	#define EXP_SysInternalLibuint64__rol  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__rol", (RTS_UINTPTR)uint64__rol, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint64__rol
	#define EXT_uint64__rol
	#define GET_uint64__rol(fl)  CAL_CMGETAPI( "uint64__rol" ) 
	#define CAL_uint64__rol  uint64__rol
	#define CHK_uint64__rol  TRUE
	#define EXP_uint64__rol  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__rol", (RTS_UINTPTR)uint64__rol, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint64__rol  PFUINT64__ROL_IEC pfuint64__rol;
	#define EXT_uint64__rol  extern PFUINT64__ROL_IEC pfuint64__rol;
	#define GET_uint64__rol(fl)  s_pfCMGetAPI2( "uint64__rol", (RTS_VOID_FCTPTR *)&pfuint64__rol, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_uint64__rol  pfuint64__rol
	#define CHK_uint64__rol  (pfuint64__rol != NULL)
	#define EXP_uint64__rol   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__rol", (RTS_UINTPTR)uint64__rol, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function makes a bitwise left-shift on a 64-bit unsigned integer value.</p>
 * <p>The the newly exposed bits will be filled with 0.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_ULINT_SHIFT_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Operand to be shifted to the left</parampseudo>
 * <parampseudo name="in2" type="IN" range="[0..63,64]">Number of bits, by which the operand gets shifted to the left</parampseudo>
 * <parampseudo name="out" type="OUT">Bitwise left-shifted 64-bit unsigned integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint64__shl(ulint_shift_struct* p);
typedef void (CDECL CDECL_EXT* PFUINT64__SHL_IEC) (ulint_shift_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT64__SHL_NOTIMPLEMENTED)
	#define USE_uint64__shl
	#define EXT_uint64__shl
	#define GET_uint64__shl(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint64__shl(p0) 
	#define CHK_uint64__shl  FALSE
	#define EXP_uint64__shl  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint64__shl
	#define EXT_uint64__shl
	#define GET_uint64__shl(fl)  CAL_CMGETAPI( "uint64__shl" ) 
	#define CAL_uint64__shl  uint64__shl
	#define CHK_uint64__shl  TRUE
	#define EXP_uint64__shl  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__shl", (RTS_UINTPTR)uint64__shl, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint64__shl
	#define EXT_uint64__shl
	#define GET_uint64__shl(fl)  CAL_CMGETAPI( "uint64__shl" ) 
	#define CAL_uint64__shl  uint64__shl
	#define CHK_uint64__shl  TRUE
	#define EXP_uint64__shl  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__shl", (RTS_UINTPTR)uint64__shl, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint64__shl
	#define EXT_SysInternalLibuint64__shl
	#define GET_SysInternalLibuint64__shl  ERR_OK
	#define CAL_SysInternalLibuint64__shl  uint64__shl
	#define CHK_SysInternalLibuint64__shl  TRUE
	#define EXP_SysInternalLibuint64__shl  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__shl", (RTS_UINTPTR)uint64__shl, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint64__shl
	#define EXT_uint64__shl
	#define GET_uint64__shl(fl)  CAL_CMGETAPI( "uint64__shl" ) 
	#define CAL_uint64__shl  uint64__shl
	#define CHK_uint64__shl  TRUE
	#define EXP_uint64__shl  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__shl", (RTS_UINTPTR)uint64__shl, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint64__shl  PFUINT64__SHL_IEC pfuint64__shl;
	#define EXT_uint64__shl  extern PFUINT64__SHL_IEC pfuint64__shl;
	#define GET_uint64__shl(fl)  s_pfCMGetAPI2( "uint64__shl", (RTS_VOID_FCTPTR *)&pfuint64__shl, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_uint64__shl  pfuint64__shl
	#define CHK_uint64__shl  (pfuint64__shl != NULL)
	#define EXP_uint64__shl   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__shl", (RTS_UINTPTR)uint64__shl, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function makes a bitwise right-shift on a 64-bit unsigned integer value.</p>
 * <p>The the newly exposed bits will be filled with 0.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_ULINT_SHIFT_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Operand to be shifted to the right</parampseudo>
 * <parampseudo name="in2" type="IN" range="[0..63,64]">Number of bits, by which the operand gets shifted to the right</parampseudo>
 * <parampseudo name="out" type="OUT">Bitwise right-shifted 64-bit unsigned integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint64__shr(ulint_shift_struct* p);
typedef void (CDECL CDECL_EXT* PFUINT64__SHR_IEC) (ulint_shift_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT64__SHR_NOTIMPLEMENTED)
	#define USE_uint64__shr
	#define EXT_uint64__shr
	#define GET_uint64__shr(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint64__shr(p0) 
	#define CHK_uint64__shr  FALSE
	#define EXP_uint64__shr  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint64__shr
	#define EXT_uint64__shr
	#define GET_uint64__shr(fl)  CAL_CMGETAPI( "uint64__shr" ) 
	#define CAL_uint64__shr  uint64__shr
	#define CHK_uint64__shr  TRUE
	#define EXP_uint64__shr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__shr", (RTS_UINTPTR)uint64__shr, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint64__shr
	#define EXT_uint64__shr
	#define GET_uint64__shr(fl)  CAL_CMGETAPI( "uint64__shr" ) 
	#define CAL_uint64__shr  uint64__shr
	#define CHK_uint64__shr  TRUE
	#define EXP_uint64__shr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__shr", (RTS_UINTPTR)uint64__shr, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint64__shr
	#define EXT_SysInternalLibuint64__shr
	#define GET_SysInternalLibuint64__shr  ERR_OK
	#define CAL_SysInternalLibuint64__shr  uint64__shr
	#define CHK_SysInternalLibuint64__shr  TRUE
	#define EXP_SysInternalLibuint64__shr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__shr", (RTS_UINTPTR)uint64__shr, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint64__shr
	#define EXT_uint64__shr
	#define GET_uint64__shr(fl)  CAL_CMGETAPI( "uint64__shr" ) 
	#define CAL_uint64__shr  uint64__shr
	#define CHK_uint64__shr  TRUE
	#define EXP_uint64__shr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__shr", (RTS_UINTPTR)uint64__shr, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint64__shr  PFUINT64__SHR_IEC pfuint64__shr;
	#define EXT_uint64__shr  extern PFUINT64__SHR_IEC pfuint64__shr;
	#define GET_uint64__shr(fl)  s_pfCMGetAPI2( "uint64__shr", (RTS_VOID_FCTPTR *)&pfuint64__shr, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_uint64__shr  pfuint64__shr
	#define CHK_uint64__shr  (pfuint64__shr != NULL)
	#define EXP_uint64__shr   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__shr", (RTS_UINTPTR)uint64__shr, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function makes a bitwise AND of two 64-bit unsigned integer values.</p>
 * <p>If the input bits each are 1, then the resulting bit will be 1, otherwise 0.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_ULINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">Bitwise AND of the two input values as 64-bit unsigned integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint64__and(ulint_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFUINT64__AND_IEC) (ulint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT64__AND_NOTIMPLEMENTED)
	#define USE_uint64__and
	#define EXT_uint64__and
	#define GET_uint64__and(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint64__and(p0) 
	#define CHK_uint64__and  FALSE
	#define EXP_uint64__and  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint64__and
	#define EXT_uint64__and
	#define GET_uint64__and(fl)  CAL_CMGETAPI( "uint64__and" ) 
	#define CAL_uint64__and  uint64__and
	#define CHK_uint64__and  TRUE
	#define EXP_uint64__and  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__and", (RTS_UINTPTR)uint64__and, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint64__and
	#define EXT_uint64__and
	#define GET_uint64__and(fl)  CAL_CMGETAPI( "uint64__and" ) 
	#define CAL_uint64__and  uint64__and
	#define CHK_uint64__and  TRUE
	#define EXP_uint64__and  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__and", (RTS_UINTPTR)uint64__and, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint64__and
	#define EXT_SysInternalLibuint64__and
	#define GET_SysInternalLibuint64__and  ERR_OK
	#define CAL_SysInternalLibuint64__and  uint64__and
	#define CHK_SysInternalLibuint64__and  TRUE
	#define EXP_SysInternalLibuint64__and  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__and", (RTS_UINTPTR)uint64__and, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint64__and
	#define EXT_uint64__and
	#define GET_uint64__and(fl)  CAL_CMGETAPI( "uint64__and" ) 
	#define CAL_uint64__and  uint64__and
	#define CHK_uint64__and  TRUE
	#define EXP_uint64__and  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__and", (RTS_UINTPTR)uint64__and, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint64__and  PFUINT64__AND_IEC pfuint64__and;
	#define EXT_uint64__and  extern PFUINT64__AND_IEC pfuint64__and;
	#define GET_uint64__and(fl)  s_pfCMGetAPI2( "uint64__and", (RTS_VOID_FCTPTR *)&pfuint64__and, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_uint64__and  pfuint64__and
	#define CHK_uint64__and  (pfuint64__and != NULL)
	#define EXP_uint64__and   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__and", (RTS_UINTPTR)uint64__and, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function makes a bitwise OR of two 64-bit unsigned integer values.</p>
 * <p>If at least one of the input bits is 1, the resulting bit will be 1, otherwise 0.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_ULINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">Bitwise OR of the two input values as 64-bit unsigned integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint64__or(ulint_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFUINT64__OR_IEC) (ulint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT64__OR_NOTIMPLEMENTED)
	#define USE_uint64__or
	#define EXT_uint64__or
	#define GET_uint64__or(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint64__or(p0) 
	#define CHK_uint64__or  FALSE
	#define EXP_uint64__or  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint64__or
	#define EXT_uint64__or
	#define GET_uint64__or(fl)  CAL_CMGETAPI( "uint64__or" ) 
	#define CAL_uint64__or  uint64__or
	#define CHK_uint64__or  TRUE
	#define EXP_uint64__or  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__or", (RTS_UINTPTR)uint64__or, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint64__or
	#define EXT_uint64__or
	#define GET_uint64__or(fl)  CAL_CMGETAPI( "uint64__or" ) 
	#define CAL_uint64__or  uint64__or
	#define CHK_uint64__or  TRUE
	#define EXP_uint64__or  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__or", (RTS_UINTPTR)uint64__or, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint64__or
	#define EXT_SysInternalLibuint64__or
	#define GET_SysInternalLibuint64__or  ERR_OK
	#define CAL_SysInternalLibuint64__or  uint64__or
	#define CHK_SysInternalLibuint64__or  TRUE
	#define EXP_SysInternalLibuint64__or  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__or", (RTS_UINTPTR)uint64__or, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint64__or
	#define EXT_uint64__or
	#define GET_uint64__or(fl)  CAL_CMGETAPI( "uint64__or" ) 
	#define CAL_uint64__or  uint64__or
	#define CHK_uint64__or  TRUE
	#define EXP_uint64__or  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__or", (RTS_UINTPTR)uint64__or, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint64__or  PFUINT64__OR_IEC pfuint64__or;
	#define EXT_uint64__or  extern PFUINT64__OR_IEC pfuint64__or;
	#define GET_uint64__or(fl)  s_pfCMGetAPI2( "uint64__or", (RTS_VOID_FCTPTR *)&pfuint64__or, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_uint64__or  pfuint64__or
	#define CHK_uint64__or  (pfuint64__or != NULL)
	#define EXP_uint64__or   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__or", (RTS_UINTPTR)uint64__or, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function makes a bitwise XOR of two 64-bit unsigned integer values.</p>
 * <p>If only one of the input bits is 1, then the resulting bit will be 1; if both or none are 1, the resulting bit will be 0.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_ULINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">Bitwise XOR of the two input values as 64-bit unsigned integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint64__xor(ulint_2op_struct* p);
typedef void (CDECL CDECL_EXT* PFUINT64__XOR_IEC) (ulint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT64__XOR_NOTIMPLEMENTED)
	#define USE_uint64__xor
	#define EXT_uint64__xor
	#define GET_uint64__xor(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint64__xor(p0) 
	#define CHK_uint64__xor  FALSE
	#define EXP_uint64__xor  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint64__xor
	#define EXT_uint64__xor
	#define GET_uint64__xor(fl)  CAL_CMGETAPI( "uint64__xor" ) 
	#define CAL_uint64__xor  uint64__xor
	#define CHK_uint64__xor  TRUE
	#define EXP_uint64__xor  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__xor", (RTS_UINTPTR)uint64__xor, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint64__xor
	#define EXT_uint64__xor
	#define GET_uint64__xor(fl)  CAL_CMGETAPI( "uint64__xor" ) 
	#define CAL_uint64__xor  uint64__xor
	#define CHK_uint64__xor  TRUE
	#define EXP_uint64__xor  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__xor", (RTS_UINTPTR)uint64__xor, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint64__xor
	#define EXT_SysInternalLibuint64__xor
	#define GET_SysInternalLibuint64__xor  ERR_OK
	#define CAL_SysInternalLibuint64__xor  uint64__xor
	#define CHK_SysInternalLibuint64__xor  TRUE
	#define EXP_SysInternalLibuint64__xor  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__xor", (RTS_UINTPTR)uint64__xor, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint64__xor
	#define EXT_uint64__xor
	#define GET_uint64__xor(fl)  CAL_CMGETAPI( "uint64__xor" ) 
	#define CAL_uint64__xor  uint64__xor
	#define CHK_uint64__xor  TRUE
	#define EXP_uint64__xor  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__xor", (RTS_UINTPTR)uint64__xor, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint64__xor  PFUINT64__XOR_IEC pfuint64__xor;
	#define EXT_uint64__xor  extern PFUINT64__XOR_IEC pfuint64__xor;
	#define GET_uint64__xor(fl)  s_pfCMGetAPI2( "uint64__xor", (RTS_VOID_FCTPTR *)&pfuint64__xor, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_uint64__xor  pfuint64__xor
	#define CHK_uint64__xor  (pfuint64__xor != NULL)
	#define EXP_uint64__xor   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__xor", (RTS_UINTPTR)uint64__xor, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function makes a bitwise NOT of a 64-bit unsigned integer value.</p>
 * <p>The resulting bit will be 1, if the corresponding input bit is 0 and vice versa.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_ULINT_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">Bitwise NOT of the input value as 64-bit unsigned integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint64__not(ulint_1op_struct* p);
typedef void (CDECL CDECL_EXT* PFUINT64__NOT_IEC) (ulint_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT64__NOT_NOTIMPLEMENTED)
	#define USE_uint64__not
	#define EXT_uint64__not
	#define GET_uint64__not(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint64__not(p0) 
	#define CHK_uint64__not  FALSE
	#define EXP_uint64__not  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint64__not
	#define EXT_uint64__not
	#define GET_uint64__not(fl)  CAL_CMGETAPI( "uint64__not" ) 
	#define CAL_uint64__not  uint64__not
	#define CHK_uint64__not  TRUE
	#define EXP_uint64__not  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__not", (RTS_UINTPTR)uint64__not, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint64__not
	#define EXT_uint64__not
	#define GET_uint64__not(fl)  CAL_CMGETAPI( "uint64__not" ) 
	#define CAL_uint64__not  uint64__not
	#define CHK_uint64__not  TRUE
	#define EXP_uint64__not  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__not", (RTS_UINTPTR)uint64__not, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint64__not
	#define EXT_SysInternalLibuint64__not
	#define GET_SysInternalLibuint64__not  ERR_OK
	#define CAL_SysInternalLibuint64__not  uint64__not
	#define CHK_SysInternalLibuint64__not  TRUE
	#define EXP_SysInternalLibuint64__not  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__not", (RTS_UINTPTR)uint64__not, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint64__not
	#define EXT_uint64__not
	#define GET_uint64__not(fl)  CAL_CMGETAPI( "uint64__not" ) 
	#define CAL_uint64__not  uint64__not
	#define CHK_uint64__not  TRUE
	#define EXP_uint64__not  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__not", (RTS_UINTPTR)uint64__not, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint64__not  PFUINT64__NOT_IEC pfuint64__not;
	#define EXT_uint64__not  extern PFUINT64__NOT_IEC pfuint64__not;
	#define GET_uint64__not(fl)  s_pfCMGetAPI2( "uint64__not", (RTS_VOID_FCTPTR *)&pfuint64__not, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_uint64__not  pfuint64__not
	#define CHK_uint64__not  (pfuint64__not != NULL)
	#define EXP_uint64__not   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__not", (RTS_UINTPTR)uint64__not, 1, 0, 0) 
#endif


/**
 * <description>This function determines if two operands equal. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if the input values are equal, 0 if they are not equal. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint64__eq(ulint_cmp_struct* p);
typedef void (CDECL CDECL_EXT* PFUINT64__EQ_IEC) (ulint_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT64__EQ_NOTIMPLEMENTED)
	#define USE_uint64__eq
	#define EXT_uint64__eq
	#define GET_uint64__eq(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint64__eq(p0) 
	#define CHK_uint64__eq  FALSE
	#define EXP_uint64__eq  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint64__eq
	#define EXT_uint64__eq
	#define GET_uint64__eq(fl)  CAL_CMGETAPI( "uint64__eq" ) 
	#define CAL_uint64__eq  uint64__eq
	#define CHK_uint64__eq  TRUE
	#define EXP_uint64__eq  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__eq", (RTS_UINTPTR)uint64__eq, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint64__eq
	#define EXT_uint64__eq
	#define GET_uint64__eq(fl)  CAL_CMGETAPI( "uint64__eq" ) 
	#define CAL_uint64__eq  uint64__eq
	#define CHK_uint64__eq  TRUE
	#define EXP_uint64__eq  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__eq", (RTS_UINTPTR)uint64__eq, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint64__eq
	#define EXT_SysInternalLibuint64__eq
	#define GET_SysInternalLibuint64__eq  ERR_OK
	#define CAL_SysInternalLibuint64__eq  uint64__eq
	#define CHK_SysInternalLibuint64__eq  TRUE
	#define EXP_SysInternalLibuint64__eq  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__eq", (RTS_UINTPTR)uint64__eq, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint64__eq
	#define EXT_uint64__eq
	#define GET_uint64__eq(fl)  CAL_CMGETAPI( "uint64__eq" ) 
	#define CAL_uint64__eq  uint64__eq
	#define CHK_uint64__eq  TRUE
	#define EXP_uint64__eq  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__eq", (RTS_UINTPTR)uint64__eq, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint64__eq  PFUINT64__EQ_IEC pfuint64__eq;
	#define EXT_uint64__eq  extern PFUINT64__EQ_IEC pfuint64__eq;
	#define GET_uint64__eq(fl)  s_pfCMGetAPI2( "uint64__eq", (RTS_VOID_FCTPTR *)&pfuint64__eq, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_uint64__eq  pfuint64__eq
	#define CHK_uint64__eq  (pfuint64__eq != NULL)
	#define EXP_uint64__eq   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__eq", (RTS_UINTPTR)uint64__eq, 1, 0, 0) 
#endif


/**
 * <description>This function determines if two operands are not equal. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if the input values are not equal, 0 if they are equal. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint64__ne(ulint_cmp_struct* p);
typedef void (CDECL CDECL_EXT* PFUINT64__NE_IEC) (ulint_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT64__NE_NOTIMPLEMENTED)
	#define USE_uint64__ne
	#define EXT_uint64__ne
	#define GET_uint64__ne(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint64__ne(p0) 
	#define CHK_uint64__ne  FALSE
	#define EXP_uint64__ne  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint64__ne
	#define EXT_uint64__ne
	#define GET_uint64__ne(fl)  CAL_CMGETAPI( "uint64__ne" ) 
	#define CAL_uint64__ne  uint64__ne
	#define CHK_uint64__ne  TRUE
	#define EXP_uint64__ne  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__ne", (RTS_UINTPTR)uint64__ne, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint64__ne
	#define EXT_uint64__ne
	#define GET_uint64__ne(fl)  CAL_CMGETAPI( "uint64__ne" ) 
	#define CAL_uint64__ne  uint64__ne
	#define CHK_uint64__ne  TRUE
	#define EXP_uint64__ne  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__ne", (RTS_UINTPTR)uint64__ne, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint64__ne
	#define EXT_SysInternalLibuint64__ne
	#define GET_SysInternalLibuint64__ne  ERR_OK
	#define CAL_SysInternalLibuint64__ne  uint64__ne
	#define CHK_SysInternalLibuint64__ne  TRUE
	#define EXP_SysInternalLibuint64__ne  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__ne", (RTS_UINTPTR)uint64__ne, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint64__ne
	#define EXT_uint64__ne
	#define GET_uint64__ne(fl)  CAL_CMGETAPI( "uint64__ne" ) 
	#define CAL_uint64__ne  uint64__ne
	#define CHK_uint64__ne  TRUE
	#define EXP_uint64__ne  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__ne", (RTS_UINTPTR)uint64__ne, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint64__ne  PFUINT64__NE_IEC pfuint64__ne;
	#define EXT_uint64__ne  extern PFUINT64__NE_IEC pfuint64__ne;
	#define GET_uint64__ne(fl)  s_pfCMGetAPI2( "uint64__ne", (RTS_VOID_FCTPTR *)&pfuint64__ne, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_uint64__ne  pfuint64__ne
	#define CHK_uint64__ne  (pfuint64__ne != NULL)
	#define EXP_uint64__ne   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__ne", (RTS_UINTPTR)uint64__ne, 1, 0, 0) 
#endif


/**
 * <description>This function determines if an operand is lower than another. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is lower than in2, 0 if in1 is not lower than in2. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint64__lt(ulint_cmp_struct* p);
typedef void (CDECL CDECL_EXT* PFUINT64__LT_IEC) (ulint_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT64__LT_NOTIMPLEMENTED)
	#define USE_uint64__lt
	#define EXT_uint64__lt
	#define GET_uint64__lt(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint64__lt(p0) 
	#define CHK_uint64__lt  FALSE
	#define EXP_uint64__lt  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint64__lt
	#define EXT_uint64__lt
	#define GET_uint64__lt(fl)  CAL_CMGETAPI( "uint64__lt" ) 
	#define CAL_uint64__lt  uint64__lt
	#define CHK_uint64__lt  TRUE
	#define EXP_uint64__lt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__lt", (RTS_UINTPTR)uint64__lt, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint64__lt
	#define EXT_uint64__lt
	#define GET_uint64__lt(fl)  CAL_CMGETAPI( "uint64__lt" ) 
	#define CAL_uint64__lt  uint64__lt
	#define CHK_uint64__lt  TRUE
	#define EXP_uint64__lt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__lt", (RTS_UINTPTR)uint64__lt, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint64__lt
	#define EXT_SysInternalLibuint64__lt
	#define GET_SysInternalLibuint64__lt  ERR_OK
	#define CAL_SysInternalLibuint64__lt  uint64__lt
	#define CHK_SysInternalLibuint64__lt  TRUE
	#define EXP_SysInternalLibuint64__lt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__lt", (RTS_UINTPTR)uint64__lt, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint64__lt
	#define EXT_uint64__lt
	#define GET_uint64__lt(fl)  CAL_CMGETAPI( "uint64__lt" ) 
	#define CAL_uint64__lt  uint64__lt
	#define CHK_uint64__lt  TRUE
	#define EXP_uint64__lt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__lt", (RTS_UINTPTR)uint64__lt, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint64__lt  PFUINT64__LT_IEC pfuint64__lt;
	#define EXT_uint64__lt  extern PFUINT64__LT_IEC pfuint64__lt;
	#define GET_uint64__lt(fl)  s_pfCMGetAPI2( "uint64__lt", (RTS_VOID_FCTPTR *)&pfuint64__lt, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_uint64__lt  pfuint64__lt
	#define CHK_uint64__lt  (pfuint64__lt != NULL)
	#define EXP_uint64__lt   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__lt", (RTS_UINTPTR)uint64__lt, 1, 0, 0) 
#endif


/**
 * <description>This function determines if an operand is lower or equal than another. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is lower or equal than in2, 0 if in1 is not lower or equal than in2. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint64__le(ulint_cmp_struct* p);
typedef void (CDECL CDECL_EXT* PFUINT64__LE_IEC) (ulint_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT64__LE_NOTIMPLEMENTED)
	#define USE_uint64__le
	#define EXT_uint64__le
	#define GET_uint64__le(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint64__le(p0) 
	#define CHK_uint64__le  FALSE
	#define EXP_uint64__le  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint64__le
	#define EXT_uint64__le
	#define GET_uint64__le(fl)  CAL_CMGETAPI( "uint64__le" ) 
	#define CAL_uint64__le  uint64__le
	#define CHK_uint64__le  TRUE
	#define EXP_uint64__le  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__le", (RTS_UINTPTR)uint64__le, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint64__le
	#define EXT_uint64__le
	#define GET_uint64__le(fl)  CAL_CMGETAPI( "uint64__le" ) 
	#define CAL_uint64__le  uint64__le
	#define CHK_uint64__le  TRUE
	#define EXP_uint64__le  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__le", (RTS_UINTPTR)uint64__le, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint64__le
	#define EXT_SysInternalLibuint64__le
	#define GET_SysInternalLibuint64__le  ERR_OK
	#define CAL_SysInternalLibuint64__le  uint64__le
	#define CHK_SysInternalLibuint64__le  TRUE
	#define EXP_SysInternalLibuint64__le  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__le", (RTS_UINTPTR)uint64__le, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint64__le
	#define EXT_uint64__le
	#define GET_uint64__le(fl)  CAL_CMGETAPI( "uint64__le" ) 
	#define CAL_uint64__le  uint64__le
	#define CHK_uint64__le  TRUE
	#define EXP_uint64__le  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__le", (RTS_UINTPTR)uint64__le, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint64__le  PFUINT64__LE_IEC pfuint64__le;
	#define EXT_uint64__le  extern PFUINT64__LE_IEC pfuint64__le;
	#define GET_uint64__le(fl)  s_pfCMGetAPI2( "uint64__le", (RTS_VOID_FCTPTR *)&pfuint64__le, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_uint64__le  pfuint64__le
	#define CHK_uint64__le  (pfuint64__le != NULL)
	#define EXP_uint64__le   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__le", (RTS_UINTPTR)uint64__le, 1, 0, 0) 
#endif


/**
 * <description>This function determines if an operand is greater than another. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is greater than in2, 0 if in1 is not greater than in2. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint64__gt(ulint_cmp_struct* p);
typedef void (CDECL CDECL_EXT* PFUINT64__GT_IEC) (ulint_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT64__GT_NOTIMPLEMENTED)
	#define USE_uint64__gt
	#define EXT_uint64__gt
	#define GET_uint64__gt(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint64__gt(p0) 
	#define CHK_uint64__gt  FALSE
	#define EXP_uint64__gt  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint64__gt
	#define EXT_uint64__gt
	#define GET_uint64__gt(fl)  CAL_CMGETAPI( "uint64__gt" ) 
	#define CAL_uint64__gt  uint64__gt
	#define CHK_uint64__gt  TRUE
	#define EXP_uint64__gt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__gt", (RTS_UINTPTR)uint64__gt, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint64__gt
	#define EXT_uint64__gt
	#define GET_uint64__gt(fl)  CAL_CMGETAPI( "uint64__gt" ) 
	#define CAL_uint64__gt  uint64__gt
	#define CHK_uint64__gt  TRUE
	#define EXP_uint64__gt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__gt", (RTS_UINTPTR)uint64__gt, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint64__gt
	#define EXT_SysInternalLibuint64__gt
	#define GET_SysInternalLibuint64__gt  ERR_OK
	#define CAL_SysInternalLibuint64__gt  uint64__gt
	#define CHK_SysInternalLibuint64__gt  TRUE
	#define EXP_SysInternalLibuint64__gt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__gt", (RTS_UINTPTR)uint64__gt, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint64__gt
	#define EXT_uint64__gt
	#define GET_uint64__gt(fl)  CAL_CMGETAPI( "uint64__gt" ) 
	#define CAL_uint64__gt  uint64__gt
	#define CHK_uint64__gt  TRUE
	#define EXP_uint64__gt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__gt", (RTS_UINTPTR)uint64__gt, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint64__gt  PFUINT64__GT_IEC pfuint64__gt;
	#define EXT_uint64__gt  extern PFUINT64__GT_IEC pfuint64__gt;
	#define GET_uint64__gt(fl)  s_pfCMGetAPI2( "uint64__gt", (RTS_VOID_FCTPTR *)&pfuint64__gt, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_uint64__gt  pfuint64__gt
	#define CHK_uint64__gt  (pfuint64__gt != NULL)
	#define EXP_uint64__gt   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__gt", (RTS_UINTPTR)uint64__gt, 1, 0, 0) 
#endif


/**
 * <description>This function determines if an operand is greater or equal than another. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is greater or equal than in2, 0 if in1 is not greater or equal than in2. The result is a 8-bit short integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint64__ge(ulint_cmp_struct* p);
typedef void (CDECL CDECL_EXT* PFUINT64__GE_IEC) (ulint_cmp_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT64__GE_NOTIMPLEMENTED)
	#define USE_uint64__ge
	#define EXT_uint64__ge
	#define GET_uint64__ge(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint64__ge(p0) 
	#define CHK_uint64__ge  FALSE
	#define EXP_uint64__ge  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint64__ge
	#define EXT_uint64__ge
	#define GET_uint64__ge(fl)  CAL_CMGETAPI( "uint64__ge" ) 
	#define CAL_uint64__ge  uint64__ge
	#define CHK_uint64__ge  TRUE
	#define EXP_uint64__ge  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__ge", (RTS_UINTPTR)uint64__ge, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint64__ge
	#define EXT_uint64__ge
	#define GET_uint64__ge(fl)  CAL_CMGETAPI( "uint64__ge" ) 
	#define CAL_uint64__ge  uint64__ge
	#define CHK_uint64__ge  TRUE
	#define EXP_uint64__ge  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__ge", (RTS_UINTPTR)uint64__ge, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint64__ge
	#define EXT_SysInternalLibuint64__ge
	#define GET_SysInternalLibuint64__ge  ERR_OK
	#define CAL_SysInternalLibuint64__ge  uint64__ge
	#define CHK_SysInternalLibuint64__ge  TRUE
	#define EXP_SysInternalLibuint64__ge  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__ge", (RTS_UINTPTR)uint64__ge, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint64__ge
	#define EXT_uint64__ge
	#define GET_uint64__ge(fl)  CAL_CMGETAPI( "uint64__ge" ) 
	#define CAL_uint64__ge  uint64__ge
	#define CHK_uint64__ge  TRUE
	#define EXP_uint64__ge  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__ge", (RTS_UINTPTR)uint64__ge, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint64__ge  PFUINT64__GE_IEC pfuint64__ge;
	#define EXT_uint64__ge  extern PFUINT64__GE_IEC pfuint64__ge;
	#define GET_uint64__ge(fl)  s_pfCMGetAPI2( "uint64__ge", (RTS_VOID_FCTPTR *)&pfuint64__ge, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_uint64__ge  pfuint64__ge
	#define CHK_uint64__ge  (pfuint64__ge != NULL)
	#define EXP_uint64__ge   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"uint64__ge", (RTS_UINTPTR)uint64__ge, 1, 0, 0) 
#endif


/**
 * <description>This function makes a multiplication of two variables. The inputs are 32-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_DINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_DINT]">First factor</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_DINT]">Second factor</parampseudo>
 * <parampseudo name="out" type="OUT">Product of the two input values as 32-bit integer value.</parampseudo>
 */
void CDECL CDECL_EXT int32__mul(dint_2op_struct* p);
typedef void (CDECL * PFINT32__MUL) (dint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT32__MUL_NOTIMPLEMENTED)
	#define USE_int32__mul
	#define EXT_int32__mul
	#define GET_int32__mul(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int32__mul(p0) 
	#define CHK_int32__mul  FALSE
	#define EXP_int32__mul  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int32__mul
	#define EXT_int32__mul
	#define GET_int32__mul(fl)  CAL_CMGETAPI( "int32__mul" ) 
	#define CAL_int32__mul  int32__mul
	#define CHK_int32__mul  TRUE
	#define EXP_int32__mul  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__mul", (RTS_UINTPTR)int32__mul, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int32__mul
	#define EXT_int32__mul
	#define GET_int32__mul(fl)  CAL_CMGETAPI( "int32__mul" ) 
	#define CAL_int32__mul  int32__mul
	#define CHK_int32__mul  TRUE
	#define EXP_int32__mul  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__mul", (RTS_UINTPTR)int32__mul, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint32__mul
	#define EXT_SysInternalLibint32__mul
	#define GET_SysInternalLibint32__mul  ERR_OK
	#define CAL_SysInternalLibint32__mul  int32__mul
	#define CHK_SysInternalLibint32__mul  TRUE
	#define EXP_SysInternalLibint32__mul  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__mul", (RTS_UINTPTR)int32__mul, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int32__mul
	#define EXT_int32__mul
	#define GET_int32__mul(fl)  CAL_CMGETAPI( "int32__mul" ) 
	#define CAL_int32__mul  int32__mul
	#define CHK_int32__mul  TRUE
	#define EXP_int32__mul  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__mul", (RTS_UINTPTR)int32__mul, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int32__mul  PFINT32__MUL pfint32__mul;
	#define EXT_int32__mul  extern PFINT32__MUL pfint32__mul;
	#define GET_int32__mul(fl)  s_pfCMGetAPI2( "int32__mul", (RTS_VOID_FCTPTR *)&pfint32__mul, (fl), 0, 0)
	#define CAL_int32__mul  pfint32__mul
	#define CHK_int32__mul  (pfint32__mul != NULL)
	#define EXP_int32__mul   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__mul", (RTS_UINTPTR)int32__mul, 1, 0) 
#endif


/**
 * <description>This function makes a multiplication of two variables. The inputs are 32-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_UDINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UDINT]">First factor</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UDINT]">Second factor</parampseudo>
 * <parampseudo name="out" type="OUT">Product of the two input values as 32-bit unsigned integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint32__mul(udint_2op_struct* p);
typedef void (CDECL * PFUINT32__MUL) (udint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT32__MUL_NOTIMPLEMENTED)
	#define USE_uint32__mul
	#define EXT_uint32__mul
	#define GET_uint32__mul(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint32__mul(p0) 
	#define CHK_uint32__mul  FALSE
	#define EXP_uint32__mul  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint32__mul
	#define EXT_uint32__mul
	#define GET_uint32__mul(fl)  CAL_CMGETAPI( "uint32__mul" ) 
	#define CAL_uint32__mul  uint32__mul
	#define CHK_uint32__mul  TRUE
	#define EXP_uint32__mul  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__mul", (RTS_UINTPTR)uint32__mul, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint32__mul
	#define EXT_uint32__mul
	#define GET_uint32__mul(fl)  CAL_CMGETAPI( "uint32__mul" ) 
	#define CAL_uint32__mul  uint32__mul
	#define CHK_uint32__mul  TRUE
	#define EXP_uint32__mul  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__mul", (RTS_UINTPTR)uint32__mul, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint32__mul
	#define EXT_SysInternalLibuint32__mul
	#define GET_SysInternalLibuint32__mul  ERR_OK
	#define CAL_SysInternalLibuint32__mul  uint32__mul
	#define CHK_SysInternalLibuint32__mul  TRUE
	#define EXP_SysInternalLibuint32__mul  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__mul", (RTS_UINTPTR)uint32__mul, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint32__mul
	#define EXT_uint32__mul
	#define GET_uint32__mul(fl)  CAL_CMGETAPI( "uint32__mul" ) 
	#define CAL_uint32__mul  uint32__mul
	#define CHK_uint32__mul  TRUE
	#define EXP_uint32__mul  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__mul", (RTS_UINTPTR)uint32__mul, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint32__mul  PFUINT32__MUL pfuint32__mul;
	#define EXT_uint32__mul  extern PFUINT32__MUL pfuint32__mul;
	#define GET_uint32__mul(fl)  s_pfCMGetAPI2( "uint32__mul", (RTS_VOID_FCTPTR *)&pfuint32__mul, (fl), 0, 0)
	#define CAL_uint32__mul  pfuint32__mul
	#define CHK_uint32__mul  (pfuint32__mul != NULL)
	#define EXP_uint32__mul   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__mul", (RTS_UINTPTR)uint32__mul, 1, 0) 
#endif


/**
 * <description>
 * <p>This function makes a division of two variables. The inputs are 32-bit integer values.</p>
 * <p>The behaviour for divisor = 0 might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_DINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_DINT]">Dividend</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_DINT]">Divisor</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception thrown</parampseudo>
 * <parampseudo name="out" type="OUT">Quotient of the two input values as 32-bit integer value.</parampseudo>
 */
void CDECL CDECL_EXT int32__div(dint_2op_struct* p);
typedef void (CDECL * PFINT32__DIV) (dint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT32__DIV_NOTIMPLEMENTED)
	#define USE_int32__div
	#define EXT_int32__div
	#define GET_int32__div(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int32__div(p0) 
	#define CHK_int32__div  FALSE
	#define EXP_int32__div  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int32__div
	#define EXT_int32__div
	#define GET_int32__div(fl)  CAL_CMGETAPI( "int32__div" ) 
	#define CAL_int32__div  int32__div
	#define CHK_int32__div  TRUE
	#define EXP_int32__div  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__div", (RTS_UINTPTR)int32__div, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int32__div
	#define EXT_int32__div
	#define GET_int32__div(fl)  CAL_CMGETAPI( "int32__div" ) 
	#define CAL_int32__div  int32__div
	#define CHK_int32__div  TRUE
	#define EXP_int32__div  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__div", (RTS_UINTPTR)int32__div, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint32__div
	#define EXT_SysInternalLibint32__div
	#define GET_SysInternalLibint32__div  ERR_OK
	#define CAL_SysInternalLibint32__div  int32__div
	#define CHK_SysInternalLibint32__div  TRUE
	#define EXP_SysInternalLibint32__div  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__div", (RTS_UINTPTR)int32__div, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int32__div
	#define EXT_int32__div
	#define GET_int32__div(fl)  CAL_CMGETAPI( "int32__div" ) 
	#define CAL_int32__div  int32__div
	#define CHK_int32__div  TRUE
	#define EXP_int32__div  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__div", (RTS_UINTPTR)int32__div, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int32__div  PFINT32__DIV pfint32__div;
	#define EXT_int32__div  extern PFINT32__DIV pfint32__div;
	#define GET_int32__div(fl)  s_pfCMGetAPI2( "int32__div", (RTS_VOID_FCTPTR *)&pfint32__div, (fl), 0, 0)
	#define CAL_int32__div  pfint32__div
	#define CHK_int32__div  (pfint32__div != NULL)
	#define EXP_int32__div   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__div", (RTS_UINTPTR)int32__div, 1, 0) 
#endif


/**
 * <description>This function calculates the remainder of division of one variable by another. The inputs are 32-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_DINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_DINT]">Dividend</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_DINT]">Divisor</parampseudo>
 * <parampseudo name="out" type="OUT">Remainder of division of the two input values as 32-bit integer value, or 0 if the divisor is 0.</parampseudo>
 */
void CDECL CDECL_EXT int32__mod(dint_2op_struct* p);
typedef void (CDECL * PFINT32__MOD) (dint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT32__MOD_NOTIMPLEMENTED)
	#define USE_int32__mod
	#define EXT_int32__mod
	#define GET_int32__mod(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int32__mod(p0) 
	#define CHK_int32__mod  FALSE
	#define EXP_int32__mod  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int32__mod
	#define EXT_int32__mod
	#define GET_int32__mod(fl)  CAL_CMGETAPI( "int32__mod" ) 
	#define CAL_int32__mod  int32__mod
	#define CHK_int32__mod  TRUE
	#define EXP_int32__mod  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__mod", (RTS_UINTPTR)int32__mod, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int32__mod
	#define EXT_int32__mod
	#define GET_int32__mod(fl)  CAL_CMGETAPI( "int32__mod" ) 
	#define CAL_int32__mod  int32__mod
	#define CHK_int32__mod  TRUE
	#define EXP_int32__mod  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__mod", (RTS_UINTPTR)int32__mod, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint32__mod
	#define EXT_SysInternalLibint32__mod
	#define GET_SysInternalLibint32__mod  ERR_OK
	#define CAL_SysInternalLibint32__mod  int32__mod
	#define CHK_SysInternalLibint32__mod  TRUE
	#define EXP_SysInternalLibint32__mod  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__mod", (RTS_UINTPTR)int32__mod, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int32__mod
	#define EXT_int32__mod
	#define GET_int32__mod(fl)  CAL_CMGETAPI( "int32__mod" ) 
	#define CAL_int32__mod  int32__mod
	#define CHK_int32__mod  TRUE
	#define EXP_int32__mod  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__mod", (RTS_UINTPTR)int32__mod, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int32__mod  PFINT32__MOD pfint32__mod;
	#define EXT_int32__mod  extern PFINT32__MOD pfint32__mod;
	#define GET_int32__mod(fl)  s_pfCMGetAPI2( "int32__mod", (RTS_VOID_FCTPTR *)&pfint32__mod, (fl), 0, 0)
	#define CAL_int32__mod  pfint32__mod
	#define CHK_int32__mod  (pfint32__mod != NULL)
	#define EXP_int32__mod   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__mod", (RTS_UINTPTR)int32__mod, 1, 0) 
#endif


/**
 * <description>
 * <p>This function makes a division of two variables. The inputs are 32-bit unsigned integer values.</p>
 * <p>The behaviour for divisor =0 might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_UDINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UDINT]">Dividend</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UDINT]">Divisor</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception thrown</parampseudo>
 * <parampseudo name="out" type="OUT">Quotient of the two input values as 32-bit unsigned integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint32__div(udint_2op_struct* p);
typedef void (CDECL * PFUINT32__DIV) (udint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT32__DIV_NOTIMPLEMENTED)
	#define USE_uint32__div
	#define EXT_uint32__div
	#define GET_uint32__div(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint32__div(p0) 
	#define CHK_uint32__div  FALSE
	#define EXP_uint32__div  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint32__div
	#define EXT_uint32__div
	#define GET_uint32__div(fl)  CAL_CMGETAPI( "uint32__div" ) 
	#define CAL_uint32__div  uint32__div
	#define CHK_uint32__div  TRUE
	#define EXP_uint32__div  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__div", (RTS_UINTPTR)uint32__div, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint32__div
	#define EXT_uint32__div
	#define GET_uint32__div(fl)  CAL_CMGETAPI( "uint32__div" ) 
	#define CAL_uint32__div  uint32__div
	#define CHK_uint32__div  TRUE
	#define EXP_uint32__div  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__div", (RTS_UINTPTR)uint32__div, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint32__div
	#define EXT_SysInternalLibuint32__div
	#define GET_SysInternalLibuint32__div  ERR_OK
	#define CAL_SysInternalLibuint32__div  uint32__div
	#define CHK_SysInternalLibuint32__div  TRUE
	#define EXP_SysInternalLibuint32__div  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__div", (RTS_UINTPTR)uint32__div, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint32__div
	#define EXT_uint32__div
	#define GET_uint32__div(fl)  CAL_CMGETAPI( "uint32__div" ) 
	#define CAL_uint32__div  uint32__div
	#define CHK_uint32__div  TRUE
	#define EXP_uint32__div  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__div", (RTS_UINTPTR)uint32__div, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint32__div  PFUINT32__DIV pfuint32__div;
	#define EXT_uint32__div  extern PFUINT32__DIV pfuint32__div;
	#define GET_uint32__div(fl)  s_pfCMGetAPI2( "uint32__div", (RTS_VOID_FCTPTR *)&pfuint32__div, (fl), 0, 0)
	#define CAL_uint32__div  pfuint32__div
	#define CHK_uint32__div  (pfuint32__div != NULL)
	#define EXP_uint32__div   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__div", (RTS_UINTPTR)uint32__div, 1, 0) 
#endif


/**
 * <description>This function calculates the remainder of division of one variable by another. The inputs are 32-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_UDINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UDINT]">Dividend</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UDINT]">Divisor</parampseudo>
 * <parampseudo name="out" type="OUT">Remainder of division of the two input values as 32-bit unsigned integer value, or 0 if the divisor is 0.</parampseudo>
 */
void CDECL CDECL_EXT uint32__mod(udint_2op_struct* p);
typedef void (CDECL * PFUINT32__MOD) (udint_2op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT32__MOD_NOTIMPLEMENTED)
	#define USE_uint32__mod
	#define EXT_uint32__mod
	#define GET_uint32__mod(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint32__mod(p0) 
	#define CHK_uint32__mod  FALSE
	#define EXP_uint32__mod  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint32__mod
	#define EXT_uint32__mod
	#define GET_uint32__mod(fl)  CAL_CMGETAPI( "uint32__mod" ) 
	#define CAL_uint32__mod  uint32__mod
	#define CHK_uint32__mod  TRUE
	#define EXP_uint32__mod  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__mod", (RTS_UINTPTR)uint32__mod, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint32__mod
	#define EXT_uint32__mod
	#define GET_uint32__mod(fl)  CAL_CMGETAPI( "uint32__mod" ) 
	#define CAL_uint32__mod  uint32__mod
	#define CHK_uint32__mod  TRUE
	#define EXP_uint32__mod  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__mod", (RTS_UINTPTR)uint32__mod, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint32__mod
	#define EXT_SysInternalLibuint32__mod
	#define GET_SysInternalLibuint32__mod  ERR_OK
	#define CAL_SysInternalLibuint32__mod  uint32__mod
	#define CHK_SysInternalLibuint32__mod  TRUE
	#define EXP_SysInternalLibuint32__mod  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__mod", (RTS_UINTPTR)uint32__mod, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint32__mod
	#define EXT_uint32__mod
	#define GET_uint32__mod(fl)  CAL_CMGETAPI( "uint32__mod" ) 
	#define CAL_uint32__mod  uint32__mod
	#define CHK_uint32__mod  TRUE
	#define EXP_uint32__mod  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__mod", (RTS_UINTPTR)uint32__mod, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint32__mod  PFUINT32__MOD pfuint32__mod;
	#define EXT_uint32__mod  extern PFUINT32__MOD pfuint32__mod;
	#define GET_uint32__mod(fl)  s_pfCMGetAPI2( "uint32__mod", (RTS_VOID_FCTPTR *)&pfuint32__mod, (fl), 0, 0)
	#define CAL_uint32__mod  pfuint32__mod
	#define CHK_uint32__mod  (pfuint32__mod != NULL)
	#define EXP_uint32__mod   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__mod", (RTS_UINTPTR)uint32__mod, 1, 0) 
#endif


/**
 * <description>This function calculates the absolute value of a 32-bit integer value.</description>
 * <param name="p" type="IN" range="[VALID_DINT_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[RTS_IEC_DINT_MIN,RTS_IEC_DINT_MIN+1,0,RTS_IEC_DINT_MAX/2,RTS_IEC_DINT_MAX]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The absolute value of the input as 32-bit integer value.</parampseudo>
 */
void CDECL CDECL_EXT int32__abs(dint_1op_struct* p);
typedef void (CDECL * PFINT32__ABS) (dint_1op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT32__ABS_NOTIMPLEMENTED)
	#define USE_int32__abs
	#define EXT_int32__abs
	#define GET_int32__abs(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int32__abs(p0) 
	#define CHK_int32__abs  FALSE
	#define EXP_int32__abs  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int32__abs
	#define EXT_int32__abs
	#define GET_int32__abs(fl)  CAL_CMGETAPI( "int32__abs" ) 
	#define CAL_int32__abs  int32__abs
	#define CHK_int32__abs  TRUE
	#define EXP_int32__abs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__abs", (RTS_UINTPTR)int32__abs, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int32__abs
	#define EXT_int32__abs
	#define GET_int32__abs(fl)  CAL_CMGETAPI( "int32__abs" ) 
	#define CAL_int32__abs  int32__abs
	#define CHK_int32__abs  TRUE
	#define EXP_int32__abs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__abs", (RTS_UINTPTR)int32__abs, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint32__abs
	#define EXT_SysInternalLibint32__abs
	#define GET_SysInternalLibint32__abs  ERR_OK
	#define CAL_SysInternalLibint32__abs  int32__abs
	#define CHK_SysInternalLibint32__abs  TRUE
	#define EXP_SysInternalLibint32__abs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__abs", (RTS_UINTPTR)int32__abs, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int32__abs
	#define EXT_int32__abs
	#define GET_int32__abs(fl)  CAL_CMGETAPI( "int32__abs" ) 
	#define CAL_int32__abs  int32__abs
	#define CHK_int32__abs  TRUE
	#define EXP_int32__abs  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__abs", (RTS_UINTPTR)int32__abs, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int32__abs  PFINT32__ABS pfint32__abs;
	#define EXT_int32__abs  extern PFINT32__ABS pfint32__abs;
	#define GET_int32__abs(fl)  s_pfCMGetAPI2( "int32__abs", (RTS_VOID_FCTPTR *)&pfint32__abs, (fl), 0, 0)
	#define CAL_int32__abs  pfint32__abs
	#define CHK_int32__abs  (pfint32__abs != NULL)
	#define EXP_int32__abs   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__abs", (RTS_UINTPTR)int32__abs, 1, 0) 
#endif


/**
 * <description>This function limits an input value to a lower and an upper bound. The inputs are 32-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_UDINT_3OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UDINT]">Lower bound</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UDINT]">Input value</parampseudo>
 * <parampseudo name="in3" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UDINT]">Upper bound</parampseudo>
 * <parampseudo name="out" type="OUT">in2 if in2 is in the range between in1 and in3, in1 if in2 is lower than in1, in3 if in2 is greater than in3. The result is a 32-bit unsigned integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint32__limit(udint_3op_struct* p);
typedef void (CDECL * PFUINT32__LIMIT) (udint_3op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT32__LIMIT_NOTIMPLEMENTED)
	#define USE_uint32__limit
	#define EXT_uint32__limit
	#define GET_uint32__limit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint32__limit(p0) 
	#define CHK_uint32__limit  FALSE
	#define EXP_uint32__limit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint32__limit
	#define EXT_uint32__limit
	#define GET_uint32__limit(fl)  CAL_CMGETAPI( "uint32__limit" ) 
	#define CAL_uint32__limit  uint32__limit
	#define CHK_uint32__limit  TRUE
	#define EXP_uint32__limit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__limit", (RTS_UINTPTR)uint32__limit, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint32__limit
	#define EXT_uint32__limit
	#define GET_uint32__limit(fl)  CAL_CMGETAPI( "uint32__limit" ) 
	#define CAL_uint32__limit  uint32__limit
	#define CHK_uint32__limit  TRUE
	#define EXP_uint32__limit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__limit", (RTS_UINTPTR)uint32__limit, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint32__limit
	#define EXT_SysInternalLibuint32__limit
	#define GET_SysInternalLibuint32__limit  ERR_OK
	#define CAL_SysInternalLibuint32__limit  uint32__limit
	#define CHK_SysInternalLibuint32__limit  TRUE
	#define EXP_SysInternalLibuint32__limit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__limit", (RTS_UINTPTR)uint32__limit, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint32__limit
	#define EXT_uint32__limit
	#define GET_uint32__limit(fl)  CAL_CMGETAPI( "uint32__limit" ) 
	#define CAL_uint32__limit  uint32__limit
	#define CHK_uint32__limit  TRUE
	#define EXP_uint32__limit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__limit", (RTS_UINTPTR)uint32__limit, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint32__limit  PFUINT32__LIMIT pfuint32__limit;
	#define EXT_uint32__limit  extern PFUINT32__LIMIT pfuint32__limit;
	#define GET_uint32__limit(fl)  s_pfCMGetAPI2( "uint32__limit", (RTS_VOID_FCTPTR *)&pfuint32__limit, (fl), 0, 0)
	#define CAL_uint32__limit  pfuint32__limit
	#define CHK_uint32__limit  (pfuint32__limit != NULL)
	#define EXP_uint32__limit   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__limit", (RTS_UINTPTR)uint32__limit, 1, 0) 
#endif


/**
 * <description>This function limits an input value to a lower and an upper bound. The inputs are 32-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_DINT_3OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_DINT]">Lower bound</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_DINT]">Input value</parampseudo>
 * <parampseudo name="in3" type="IN" range="[RTS_RANGE_OF_RTS_IEC_DINT]">Upper bound</parampseudo>
 * <parampseudo name="out" type="OUT">in2 if in2 is in the range between in1 and in3, in1 if in2 is lower than in1, in3 if in2 is greater than in3. The result is a 32-bit integer value.</parampseudo>
 */
void CDECL CDECL_EXT int32__limit(dint_3op_struct* p);
typedef void (CDECL * PFINT32__LIMIT) (dint_3op_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT32__LIMIT_NOTIMPLEMENTED)
	#define USE_int32__limit
	#define EXT_int32__limit
	#define GET_int32__limit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int32__limit(p0) 
	#define CHK_int32__limit  FALSE
	#define EXP_int32__limit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int32__limit
	#define EXT_int32__limit
	#define GET_int32__limit(fl)  CAL_CMGETAPI( "int32__limit" ) 
	#define CAL_int32__limit  int32__limit
	#define CHK_int32__limit  TRUE
	#define EXP_int32__limit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__limit", (RTS_UINTPTR)int32__limit, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int32__limit
	#define EXT_int32__limit
	#define GET_int32__limit(fl)  CAL_CMGETAPI( "int32__limit" ) 
	#define CAL_int32__limit  int32__limit
	#define CHK_int32__limit  TRUE
	#define EXP_int32__limit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__limit", (RTS_UINTPTR)int32__limit, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint32__limit
	#define EXT_SysInternalLibint32__limit
	#define GET_SysInternalLibint32__limit  ERR_OK
	#define CAL_SysInternalLibint32__limit  int32__limit
	#define CHK_SysInternalLibint32__limit  TRUE
	#define EXP_SysInternalLibint32__limit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__limit", (RTS_UINTPTR)int32__limit, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int32__limit
	#define EXT_int32__limit
	#define GET_int32__limit(fl)  CAL_CMGETAPI( "int32__limit" ) 
	#define CAL_int32__limit  int32__limit
	#define CHK_int32__limit  TRUE
	#define EXP_int32__limit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__limit", (RTS_UINTPTR)int32__limit, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int32__limit  PFINT32__LIMIT pfint32__limit;
	#define EXT_int32__limit  extern PFINT32__LIMIT pfint32__limit;
	#define GET_int32__limit(fl)  s_pfCMGetAPI2( "int32__limit", (RTS_VOID_FCTPTR *)&pfint32__limit, (fl), 0, 0)
	#define CAL_int32__limit  pfint32__limit
	#define CHK_int32__limit  (pfint32__limit != NULL)
	#define EXP_int32__limit   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__limit", (RTS_UINTPTR)int32__limit, 1, 0) 
#endif


/**
 * <description>
 * <p>This function makes a bitwise rotation to the left of a 32-bit unsigned integer value.</p>
 * <p>The input operand will be shifted one bit position to the left n times while the bit that is furthest to the right will be reinserted from the right.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_UDINT_SHIFT_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UDINT]">Operand to be rotated to the left</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UINT]">Number n of bits, by which the operand gets rotated to the left</parampseudo>
 * <parampseudo name="out" type="OUT">Bitwise left rotated 32-bit unsigned integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint32__rol(udint_shift_struct* p);
typedef void (CDECL * PFUINT32__ROL) (udint_shift_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT32__ROL_NOTIMPLEMENTED)
	#define USE_uint32__rol
	#define EXT_uint32__rol
	#define GET_uint32__rol(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint32__rol(p0) 
	#define CHK_uint32__rol  FALSE
	#define EXP_uint32__rol  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint32__rol
	#define EXT_uint32__rol
	#define GET_uint32__rol(fl)  CAL_CMGETAPI( "uint32__rol" ) 
	#define CAL_uint32__rol  uint32__rol
	#define CHK_uint32__rol  TRUE
	#define EXP_uint32__rol  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__rol", (RTS_UINTPTR)uint32__rol, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint32__rol
	#define EXT_uint32__rol
	#define GET_uint32__rol(fl)  CAL_CMGETAPI( "uint32__rol" ) 
	#define CAL_uint32__rol  uint32__rol
	#define CHK_uint32__rol  TRUE
	#define EXP_uint32__rol  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__rol", (RTS_UINTPTR)uint32__rol, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint32__rol
	#define EXT_SysInternalLibuint32__rol
	#define GET_SysInternalLibuint32__rol  ERR_OK
	#define CAL_SysInternalLibuint32__rol  uint32__rol
	#define CHK_SysInternalLibuint32__rol  TRUE
	#define EXP_SysInternalLibuint32__rol  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__rol", (RTS_UINTPTR)uint32__rol, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint32__rol
	#define EXT_uint32__rol
	#define GET_uint32__rol(fl)  CAL_CMGETAPI( "uint32__rol" ) 
	#define CAL_uint32__rol  uint32__rol
	#define CHK_uint32__rol  TRUE
	#define EXP_uint32__rol  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__rol", (RTS_UINTPTR)uint32__rol, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint32__rol  PFUINT32__ROL pfuint32__rol;
	#define EXT_uint32__rol  extern PFUINT32__ROL pfuint32__rol;
	#define GET_uint32__rol(fl)  s_pfCMGetAPI2( "uint32__rol", (RTS_VOID_FCTPTR *)&pfuint32__rol, (fl), 0, 0)
	#define CAL_uint32__rol  pfuint32__rol
	#define CHK_uint32__rol  (pfuint32__rol != NULL)
	#define EXP_uint32__rol   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__rol", (RTS_UINTPTR)uint32__rol, 1, 0) 
#endif


/**
 * <description>
 * <p>This function makes a bitwise rotation to the right of a 32-bit unsigned integer value.</p>
 * <p>The input operand will be shifted one bit position to the right n times while the bit that is furthest to the left will be reinserted from the left.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_UDINT_SHIFT_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UDINT]">Operand to be rotated to the right</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UINT]">Number n of bits, by which the operand gets rotated to the right</parampseudo>
 * <parampseudo name="out" type="OUT">Bitwise right rotated 32-bit unsigned integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint32__ror(udint_shift_struct* p);
typedef void (CDECL * PFUINT32__ROR) (udint_shift_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT32__ROR_NOTIMPLEMENTED)
	#define USE_uint32__ror
	#define EXT_uint32__ror
	#define GET_uint32__ror(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint32__ror(p0) 
	#define CHK_uint32__ror  FALSE
	#define EXP_uint32__ror  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint32__ror
	#define EXT_uint32__ror
	#define GET_uint32__ror(fl)  CAL_CMGETAPI( "uint32__ror" ) 
	#define CAL_uint32__ror  uint32__ror
	#define CHK_uint32__ror  TRUE
	#define EXP_uint32__ror  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__ror", (RTS_UINTPTR)uint32__ror, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint32__ror
	#define EXT_uint32__ror
	#define GET_uint32__ror(fl)  CAL_CMGETAPI( "uint32__ror" ) 
	#define CAL_uint32__ror  uint32__ror
	#define CHK_uint32__ror  TRUE
	#define EXP_uint32__ror  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__ror", (RTS_UINTPTR)uint32__ror, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint32__ror
	#define EXT_SysInternalLibuint32__ror
	#define GET_SysInternalLibuint32__ror  ERR_OK
	#define CAL_SysInternalLibuint32__ror  uint32__ror
	#define CHK_SysInternalLibuint32__ror  TRUE
	#define EXP_SysInternalLibuint32__ror  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__ror", (RTS_UINTPTR)uint32__ror, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint32__ror
	#define EXT_uint32__ror
	#define GET_uint32__ror(fl)  CAL_CMGETAPI( "uint32__ror" ) 
	#define CAL_uint32__ror  uint32__ror
	#define CHK_uint32__ror  TRUE
	#define EXP_uint32__ror  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__ror", (RTS_UINTPTR)uint32__ror, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint32__ror  PFUINT32__ROR pfuint32__ror;
	#define EXT_uint32__ror  extern PFUINT32__ROR pfuint32__ror;
	#define GET_uint32__ror(fl)  s_pfCMGetAPI2( "uint32__ror", (RTS_VOID_FCTPTR *)&pfuint32__ror, (fl), 0, 0)
	#define CAL_uint32__ror  pfuint32__ror
	#define CHK_uint32__ror  (pfuint32__ror != NULL)
	#define EXP_uint32__ror   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__ror", (RTS_UINTPTR)uint32__ror, 1, 0) 
#endif


/**
 * <description>
 * <p>This function makes a bitwise left-shift on a 32-bit unsigned integer value.</p>
 * <p>The the newly exposed bits will be filled with 0.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_UDINT_SHIFT_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UDINT]">Operand to be shifted to the left</parampseudo>
 * <parampseudo name="in2" type="IN" range="[0..31,32]">Number of bits, by which the operand gets shifted to the left</parampseudo>
 * <parampseudo name="out" type="OUT">Bitwise left-shifted 32-bit unsigned integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint32__shl(udint_shift_struct* p);
typedef void (CDECL * PFUINT32__SHL) (udint_shift_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT32__SHL_NOTIMPLEMENTED)
	#define USE_uint32__shl
	#define EXT_uint32__shl
	#define GET_uint32__shl(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint32__shl(p0) 
	#define CHK_uint32__shl  FALSE
	#define EXP_uint32__shl  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint32__shl
	#define EXT_uint32__shl
	#define GET_uint32__shl(fl)  CAL_CMGETAPI( "uint32__shl" ) 
	#define CAL_uint32__shl  uint32__shl
	#define CHK_uint32__shl  TRUE
	#define EXP_uint32__shl  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__shl", (RTS_UINTPTR)uint32__shl, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint32__shl
	#define EXT_uint32__shl
	#define GET_uint32__shl(fl)  CAL_CMGETAPI( "uint32__shl" ) 
	#define CAL_uint32__shl  uint32__shl
	#define CHK_uint32__shl  TRUE
	#define EXP_uint32__shl  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__shl", (RTS_UINTPTR)uint32__shl, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint32__shl
	#define EXT_SysInternalLibuint32__shl
	#define GET_SysInternalLibuint32__shl  ERR_OK
	#define CAL_SysInternalLibuint32__shl  uint32__shl
	#define CHK_SysInternalLibuint32__shl  TRUE
	#define EXP_SysInternalLibuint32__shl  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__shl", (RTS_UINTPTR)uint32__shl, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint32__shl
	#define EXT_uint32__shl
	#define GET_uint32__shl(fl)  CAL_CMGETAPI( "uint32__shl" ) 
	#define CAL_uint32__shl  uint32__shl
	#define CHK_uint32__shl  TRUE
	#define EXP_uint32__shl  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__shl", (RTS_UINTPTR)uint32__shl, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint32__shl  PFUINT32__SHL pfuint32__shl;
	#define EXT_uint32__shl  extern PFUINT32__SHL pfuint32__shl;
	#define GET_uint32__shl(fl)  s_pfCMGetAPI2( "uint32__shl", (RTS_VOID_FCTPTR *)&pfuint32__shl, (fl), 0, 0)
	#define CAL_uint32__shl  pfuint32__shl
	#define CHK_uint32__shl  (pfuint32__shl != NULL)
	#define EXP_uint32__shl   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__shl", (RTS_UINTPTR)uint32__shl, 1, 0) 
#endif


/**
 * <description>
 * <p>This function makes a bitwise right-shift on a 32-bit unsigned integer value.</p>
 * <p>The the newly exposed bits will be filled with 0.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_UDINT_SHIFT_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UDINT]">Operand to be shifted to the right</parampseudo>
 * <parampseudo name="in2" type="IN" range="[0..31,32]">Number of bits, by which the operand gets shifted to the right</parampseudo>
 * <parampseudo name="out" type="OUT">Bitwise right-shifted 32-bit unsigned integer value.</parampseudo>
 */
void CDECL CDECL_EXT uint32__shr(udint_shift_struct* p);
typedef void (CDECL * PFUINT32__SHR) (udint_shift_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(UINT32__SHR_NOTIMPLEMENTED)
	#define USE_uint32__shr
	#define EXT_uint32__shr
	#define GET_uint32__shr(fl)  ERR_NOTIMPLEMENTED
	#define CAL_uint32__shr(p0) 
	#define CHK_uint32__shr  FALSE
	#define EXP_uint32__shr  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_uint32__shr
	#define EXT_uint32__shr
	#define GET_uint32__shr(fl)  CAL_CMGETAPI( "uint32__shr" ) 
	#define CAL_uint32__shr  uint32__shr
	#define CHK_uint32__shr  TRUE
	#define EXP_uint32__shr  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__shr", (RTS_UINTPTR)uint32__shr, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_uint32__shr
	#define EXT_uint32__shr
	#define GET_uint32__shr(fl)  CAL_CMGETAPI( "uint32__shr" ) 
	#define CAL_uint32__shr  uint32__shr
	#define CHK_uint32__shr  TRUE
	#define EXP_uint32__shr  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__shr", (RTS_UINTPTR)uint32__shr, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibuint32__shr
	#define EXT_SysInternalLibuint32__shr
	#define GET_SysInternalLibuint32__shr  ERR_OK
	#define CAL_SysInternalLibuint32__shr  uint32__shr
	#define CHK_SysInternalLibuint32__shr  TRUE
	#define EXP_SysInternalLibuint32__shr  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__shr", (RTS_UINTPTR)uint32__shr, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_uint32__shr
	#define EXT_uint32__shr
	#define GET_uint32__shr(fl)  CAL_CMGETAPI( "uint32__shr" ) 
	#define CAL_uint32__shr  uint32__shr
	#define CHK_uint32__shr  TRUE
	#define EXP_uint32__shr  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__shr", (RTS_UINTPTR)uint32__shr, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_uint32__shr  PFUINT32__SHR pfuint32__shr;
	#define EXT_uint32__shr  extern PFUINT32__SHR pfuint32__shr;
	#define GET_uint32__shr(fl)  s_pfCMGetAPI2( "uint32__shr", (RTS_VOID_FCTPTR *)&pfuint32__shr, (fl), 0, 0)
	#define CAL_uint32__shr  pfuint32__shr
	#define CHK_uint32__shr  (pfuint32__shr != NULL)
	#define EXP_uint32__shr   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"uint32__shr", (RTS_UINTPTR)uint32__shr, 1, 0) 
#endif


/**
 * <description>
 * <p>This function makes a bitwise right-shift on a 32-bit integer value.</p>
 * <p>The the newly exposed bits will be filled with the value of the topmost bit, that is 1 for negative and 0 for positive input values.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_DINT_SHIFT_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_DINT]">Operand to be shifted to the right</parampseudo>
 * <parampseudo name="in2" type="IN" range="[0..31,32]">Number of bits, by which the operand gets shifted to the right</parampseudo>
 * <parampseudo name="out" type="OUT">Bitwise right-shifted 32-bit integer value.</parampseudo>
 */
void CDECL CDECL_EXT int32__shr(dint_shift_struct* p);
typedef void (CDECL * PFINT32__SHR) (dint_shift_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT32__SHR_NOTIMPLEMENTED)
	#define USE_int32__shr
	#define EXT_int32__shr
	#define GET_int32__shr(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int32__shr(p0) 
	#define CHK_int32__shr  FALSE
	#define EXP_int32__shr  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int32__shr
	#define EXT_int32__shr
	#define GET_int32__shr(fl)  CAL_CMGETAPI( "int32__shr" ) 
	#define CAL_int32__shr  int32__shr
	#define CHK_int32__shr  TRUE
	#define EXP_int32__shr  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__shr", (RTS_UINTPTR)int32__shr, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int32__shr
	#define EXT_int32__shr
	#define GET_int32__shr(fl)  CAL_CMGETAPI( "int32__shr" ) 
	#define CAL_int32__shr  int32__shr
	#define CHK_int32__shr  TRUE
	#define EXP_int32__shr  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__shr", (RTS_UINTPTR)int32__shr, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint32__shr
	#define EXT_SysInternalLibint32__shr
	#define GET_SysInternalLibint32__shr  ERR_OK
	#define CAL_SysInternalLibint32__shr  int32__shr
	#define CHK_SysInternalLibint32__shr  TRUE
	#define EXP_SysInternalLibint32__shr  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__shr", (RTS_UINTPTR)int32__shr, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int32__shr
	#define EXT_int32__shr
	#define GET_int32__shr(fl)  CAL_CMGETAPI( "int32__shr" ) 
	#define CAL_int32__shr  int32__shr
	#define CHK_int32__shr  TRUE
	#define EXP_int32__shr  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__shr", (RTS_UINTPTR)int32__shr, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int32__shr  PFINT32__SHR pfint32__shr;
	#define EXT_int32__shr  extern PFINT32__SHR pfint32__shr;
	#define GET_int32__shr(fl)  s_pfCMGetAPI2( "int32__shr", (RTS_VOID_FCTPTR *)&pfint32__shr, (fl), 0, 0)
	#define CAL_int32__shr  pfint32__shr
	#define CHK_int32__shr  (pfint32__shr != NULL)
	#define EXP_int32__shr   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"int32__shr", (RTS_UINTPTR)int32__shr, 1, 0) 
#endif


/**
 * <description>
 * <p>This function Converts any 32-bit numeric data type to a 64-bit integer value.</p>
 * <p>Data types with less than 32 bits are allowed but the input value has to be casted to 32 bits before.</p>
 * <p>Only integer datatypes are allowed.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_ANY32_TO_INT64_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[ANY_MIN,ANY_MID,ANY_MAX]">Input data</parampseudo>
 * <parampseudo name="uiType" type="IN" range="[TYPE3_DINT,TYPE3_UDINT,TYPE3_INVALID]">Type of the input data (see TypeClass3 enumeration)</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception thrown</parampseudo>
 * <parampseudo name="out" type="OUT">Input data as 64-bit integer value.</parampseudo>
 */
void CDECL CDECL_EXT any32__to__int64(any32_to_int64_struct* p);
typedef void (CDECL CDECL_EXT* PFANY32__TO__INT64_IEC) (any32_to_int64_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(ANY32__TO__INT64_NOTIMPLEMENTED)
	#define USE_any32__to__int64
	#define EXT_any32__to__int64
	#define GET_any32__to__int64(fl)  ERR_NOTIMPLEMENTED
	#define CAL_any32__to__int64(p0) 
	#define CHK_any32__to__int64  FALSE
	#define EXP_any32__to__int64  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_any32__to__int64
	#define EXT_any32__to__int64
	#define GET_any32__to__int64(fl)  CAL_CMGETAPI( "any32__to__int64" ) 
	#define CAL_any32__to__int64  any32__to__int64
	#define CHK_any32__to__int64  TRUE
	#define EXP_any32__to__int64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"any32__to__int64", (RTS_UINTPTR)any32__to__int64, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_any32__to__int64
	#define EXT_any32__to__int64
	#define GET_any32__to__int64(fl)  CAL_CMGETAPI( "any32__to__int64" ) 
	#define CAL_any32__to__int64  any32__to__int64
	#define CHK_any32__to__int64  TRUE
	#define EXP_any32__to__int64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"any32__to__int64", (RTS_UINTPTR)any32__to__int64, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibany32__to__int64
	#define EXT_SysInternalLibany32__to__int64
	#define GET_SysInternalLibany32__to__int64  ERR_OK
	#define CAL_SysInternalLibany32__to__int64  any32__to__int64
	#define CHK_SysInternalLibany32__to__int64  TRUE
	#define EXP_SysInternalLibany32__to__int64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"any32__to__int64", (RTS_UINTPTR)any32__to__int64, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_any32__to__int64
	#define EXT_any32__to__int64
	#define GET_any32__to__int64(fl)  CAL_CMGETAPI( "any32__to__int64" ) 
	#define CAL_any32__to__int64  any32__to__int64
	#define CHK_any32__to__int64  TRUE
	#define EXP_any32__to__int64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"any32__to__int64", (RTS_UINTPTR)any32__to__int64, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_any32__to__int64  PFANY32__TO__INT64_IEC pfany32__to__int64;
	#define EXT_any32__to__int64  extern PFANY32__TO__INT64_IEC pfany32__to__int64;
	#define GET_any32__to__int64(fl)  s_pfCMGetAPI2( "any32__to__int64", (RTS_VOID_FCTPTR *)&pfany32__to__int64, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_any32__to__int64  pfany32__to__int64
	#define CHK_any32__to__int64  (pfany32__to__int64 != NULL)
	#define EXP_any32__to__int64   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"any32__to__int64", (RTS_UINTPTR)any32__to__int64, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function Converts a 64-bit integer value to any 32-bit numeric data type.</p>
 * <p>Data types with less than 32 bits are allowed but the output value is casted to 32 bits.</p>
 * <p>Only integer datatypes are allowed.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_INT64_TO_ANY32_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[ANY_MIN,ANY_MID,ANY_MAX]">Input value</parampseudo>
 * <parampseudo name="uiType" type="IN" range="[TYPE3_BOOL, TYPE3_USINT,TYPE3_SINT, TYPE3_UINT,TYPE3_INT, TYPE3_UDINT,TYPE3_DINT, TYPE3_TIMEOFDAY, TYPE3_INVALID]">Type of the output data (see TypeClass3 enumeration)</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception thrown</parampseudo>
 * <parampseudo name="out" type="OUT">Input value as 32-bit data type.</parampseudo>
 */
void CDECL CDECL_EXT int64__to__any32(int64_to_any32_struct* p);
typedef void (CDECL CDECL_EXT* PFINT64__TO__ANY32_IEC) (int64_to_any32_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT64__TO__ANY32_NOTIMPLEMENTED)
	#define USE_int64__to__any32
	#define EXT_int64__to__any32
	#define GET_int64__to__any32(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int64__to__any32(p0) 
	#define CHK_int64__to__any32  FALSE
	#define EXP_int64__to__any32  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int64__to__any32
	#define EXT_int64__to__any32
	#define GET_int64__to__any32(fl)  CAL_CMGETAPI( "int64__to__any32" ) 
	#define CAL_int64__to__any32  int64__to__any32
	#define CHK_int64__to__any32  TRUE
	#define EXP_int64__to__any32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__to__any32", (RTS_UINTPTR)int64__to__any32, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int64__to__any32
	#define EXT_int64__to__any32
	#define GET_int64__to__any32(fl)  CAL_CMGETAPI( "int64__to__any32" ) 
	#define CAL_int64__to__any32  int64__to__any32
	#define CHK_int64__to__any32  TRUE
	#define EXP_int64__to__any32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__to__any32", (RTS_UINTPTR)int64__to__any32, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint64__to__any32
	#define EXT_SysInternalLibint64__to__any32
	#define GET_SysInternalLibint64__to__any32  ERR_OK
	#define CAL_SysInternalLibint64__to__any32  int64__to__any32
	#define CHK_SysInternalLibint64__to__any32  TRUE
	#define EXP_SysInternalLibint64__to__any32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__to__any32", (RTS_UINTPTR)int64__to__any32, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int64__to__any32
	#define EXT_int64__to__any32
	#define GET_int64__to__any32(fl)  CAL_CMGETAPI( "int64__to__any32" ) 
	#define CAL_int64__to__any32  int64__to__any32
	#define CHK_int64__to__any32  TRUE
	#define EXP_int64__to__any32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__to__any32", (RTS_UINTPTR)int64__to__any32, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int64__to__any32  PFINT64__TO__ANY32_IEC pfint64__to__any32;
	#define EXT_int64__to__any32  extern PFINT64__TO__ANY32_IEC pfint64__to__any32;
	#define GET_int64__to__any32(fl)  s_pfCMGetAPI2( "int64__to__any32", (RTS_VOID_FCTPTR *)&pfint64__to__any32, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_int64__to__any32  pfint64__to__any32
	#define CHK_int64__to__any32  (pfint64__to__any32 != NULL)
	#define EXP_int64__to__any32   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__to__any32", (RTS_UINTPTR)int64__to__any32, 1, 0, 0) 
#endif


/**
 * <description>
 *	This function read a 64bit integer value atomic.
 * </description>
 * <param name="p" type="IN">Pointer to the input structure</param>
 * <parampseudo name="pSrc" type="IN">Pointer to source address to read from</parampseudo>
 * <parampseudo name="pResult" type="IN">Pointer to error code</parampseudo>
 * <parampseudo name="out" type="OUT">Read 64bit integer value.</parampseudo>
 */
void CDECL CDECL_EXT int64__atomicread(int64_atomicread_struct* p);
typedef void (CDECL CDECL_EXT* PFINT64__ATOMICREAD_IEC) (int64_atomicread_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT64__ATOMICREAD_NOTIMPLEMENTED)
	#define USE_int64__atomicread
	#define EXT_int64__atomicread
	#define GET_int64__atomicread(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int64__atomicread(p0) 
	#define CHK_int64__atomicread  FALSE
	#define EXP_int64__atomicread  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int64__atomicread
	#define EXT_int64__atomicread
	#define GET_int64__atomicread(fl)  CAL_CMGETAPI( "int64__atomicread" ) 
	#define CAL_int64__atomicread  int64__atomicread
	#define CHK_int64__atomicread  TRUE
	#define EXP_int64__atomicread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__atomicread", (RTS_UINTPTR)int64__atomicread, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int64__atomicread
	#define EXT_int64__atomicread
	#define GET_int64__atomicread(fl)  CAL_CMGETAPI( "int64__atomicread" ) 
	#define CAL_int64__atomicread  int64__atomicread
	#define CHK_int64__atomicread  TRUE
	#define EXP_int64__atomicread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__atomicread", (RTS_UINTPTR)int64__atomicread, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint64__atomicread
	#define EXT_SysInternalLibint64__atomicread
	#define GET_SysInternalLibint64__atomicread  ERR_OK
	#define CAL_SysInternalLibint64__atomicread  int64__atomicread
	#define CHK_SysInternalLibint64__atomicread  TRUE
	#define EXP_SysInternalLibint64__atomicread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__atomicread", (RTS_UINTPTR)int64__atomicread, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int64__atomicread
	#define EXT_int64__atomicread
	#define GET_int64__atomicread(fl)  CAL_CMGETAPI( "int64__atomicread" ) 
	#define CAL_int64__atomicread  int64__atomicread
	#define CHK_int64__atomicread  TRUE
	#define EXP_int64__atomicread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__atomicread", (RTS_UINTPTR)int64__atomicread, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int64__atomicread  PFINT64__ATOMICREAD_IEC pfint64__atomicread;
	#define EXT_int64__atomicread  extern PFINT64__ATOMICREAD_IEC pfint64__atomicread;
	#define GET_int64__atomicread(fl)  s_pfCMGetAPI2( "int64__atomicread", (RTS_VOID_FCTPTR *)&pfint64__atomicread, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_int64__atomicread  pfint64__atomicread
	#define CHK_int64__atomicread  (pfint64__atomicread != NULL)
	#define EXP_int64__atomicread   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__atomicread", (RTS_UINTPTR)int64__atomicread, 1, 0, 0) 
#endif


/**
 * <description>
 *	This function write a 64bit integer value atomic.
 * </description>
 * <param name="p" type="IN">Pointer to the input structure</param>
 * <parampseudo name="pDest" type="IN">Pointer to destination address to write to</parampseudo>
 * <parampseudo name="write" type="IN">Value to write</parampseudo>
 * <parampseudo name="out" type="OUT">Error code for result.</parampseudo>
 */
void CDECL CDECL_EXT int64__atomicwrite(int64_atomicwrite_struct* p);
typedef void (CDECL CDECL_EXT* PFINT64__ATOMICWRITE_IEC) (int64_atomicwrite_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(INT64__ATOMICWRITE_NOTIMPLEMENTED)
	#define USE_int64__atomicwrite
	#define EXT_int64__atomicwrite
	#define GET_int64__atomicwrite(fl)  ERR_NOTIMPLEMENTED
	#define CAL_int64__atomicwrite(p0) 
	#define CHK_int64__atomicwrite  FALSE
	#define EXP_int64__atomicwrite  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_int64__atomicwrite
	#define EXT_int64__atomicwrite
	#define GET_int64__atomicwrite(fl)  CAL_CMGETAPI( "int64__atomicwrite" ) 
	#define CAL_int64__atomicwrite  int64__atomicwrite
	#define CHK_int64__atomicwrite  TRUE
	#define EXP_int64__atomicwrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__atomicwrite", (RTS_UINTPTR)int64__atomicwrite, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_int64__atomicwrite
	#define EXT_int64__atomicwrite
	#define GET_int64__atomicwrite(fl)  CAL_CMGETAPI( "int64__atomicwrite" ) 
	#define CAL_int64__atomicwrite  int64__atomicwrite
	#define CHK_int64__atomicwrite  TRUE
	#define EXP_int64__atomicwrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__atomicwrite", (RTS_UINTPTR)int64__atomicwrite, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibint64__atomicwrite
	#define EXT_SysInternalLibint64__atomicwrite
	#define GET_SysInternalLibint64__atomicwrite  ERR_OK
	#define CAL_SysInternalLibint64__atomicwrite  int64__atomicwrite
	#define CHK_SysInternalLibint64__atomicwrite  TRUE
	#define EXP_SysInternalLibint64__atomicwrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__atomicwrite", (RTS_UINTPTR)int64__atomicwrite, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_int64__atomicwrite
	#define EXT_int64__atomicwrite
	#define GET_int64__atomicwrite(fl)  CAL_CMGETAPI( "int64__atomicwrite" ) 
	#define CAL_int64__atomicwrite  int64__atomicwrite
	#define CHK_int64__atomicwrite  TRUE
	#define EXP_int64__atomicwrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__atomicwrite", (RTS_UINTPTR)int64__atomicwrite, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_int64__atomicwrite  PFINT64__ATOMICWRITE_IEC pfint64__atomicwrite;
	#define EXT_int64__atomicwrite  extern PFINT64__ATOMICWRITE_IEC pfint64__atomicwrite;
	#define GET_int64__atomicwrite(fl)  s_pfCMGetAPI2( "int64__atomicwrite", (RTS_VOID_FCTPTR *)&pfint64__atomicwrite, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_int64__atomicwrite  pfint64__atomicwrite
	#define CHK_int64__atomicwrite  (pfint64__atomicwrite != NULL)
	#define EXP_int64__atomicwrite   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"int64__atomicwrite", (RTS_UINTPTR)int64__atomicwrite, 1, 0, 0) 
#endif



/**
 * <description>
 * <p>This function Converts a 32-bit real value to any 32-bit numeric data type.</p>
 * <p>Data types with less than 32 bits are allowed but the output value is casted to 32 bits.</p>
 * <p>Only integer datatypes are allowed.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_REAL32_TO_ANY32_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[ANY_MIN,ANY_MID,ANY_MAX]">Input value</parampseudo>
 * <parampseudo name="uiType" type="IN" range="[TYPE3_BOOL, TYPE3_USINT,TYPE3_SINT, TYPE3_UINT,TYPE3_INT, TYPE3_UDINT,TYPE3_DINT, TYPE3_TIMEOFDAY, TYPE3_INVALID]">Type of the output data (see TypeClass3 enumeration)</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception thrown</parampseudo>
 * <parampseudo name="out" type="OUT">Input value as 32-bit data type.</parampseudo>
 */
void CDECL CDECL_EXT real32__to__any32(real32_to_any32_struct* p);
typedef void (CDECL * PFREAL32__TO__ANY32) (real32_to_any32_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__TO__ANY32_NOTIMPLEMENTED)
	#define USE_real32__to__any32
	#define EXT_real32__to__any32
	#define GET_real32__to__any32(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__to__any32(p0) 
	#define CHK_real32__to__any32  FALSE
	#define EXP_real32__to__any32  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__to__any32
	#define EXT_real32__to__any32
	#define GET_real32__to__any32(fl)  CAL_CMGETAPI( "real32__to__any32" ) 
	#define CAL_real32__to__any32  real32__to__any32
	#define CHK_real32__to__any32  TRUE
	#define EXP_real32__to__any32  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__to__any32", (RTS_UINTPTR)real32__to__any32, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__to__any32
	#define EXT_real32__to__any32
	#define GET_real32__to__any32(fl)  CAL_CMGETAPI( "real32__to__any32" ) 
	#define CAL_real32__to__any32  real32__to__any32
	#define CHK_real32__to__any32  TRUE
	#define EXP_real32__to__any32  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__to__any32", (RTS_UINTPTR)real32__to__any32, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__to__any32
	#define EXT_SysInternalLibreal32__to__any32
	#define GET_SysInternalLibreal32__to__any32  ERR_OK
	#define CAL_SysInternalLibreal32__to__any32  real32__to__any32
	#define CHK_SysInternalLibreal32__to__any32  TRUE
	#define EXP_SysInternalLibreal32__to__any32  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__to__any32", (RTS_UINTPTR)real32__to__any32, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__to__any32
	#define EXT_real32__to__any32
	#define GET_real32__to__any32(fl)  CAL_CMGETAPI( "real32__to__any32" ) 
	#define CAL_real32__to__any32  real32__to__any32
	#define CHK_real32__to__any32  TRUE
	#define EXP_real32__to__any32  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__to__any32", (RTS_UINTPTR)real32__to__any32, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__to__any32  PFREAL32__TO__ANY32 pfreal32__to__any32;
	#define EXT_real32__to__any32  extern PFREAL32__TO__ANY32 pfreal32__to__any32;
	#define GET_real32__to__any32(fl)  s_pfCMGetAPI2( "real32__to__any32", (RTS_VOID_FCTPTR *)&pfreal32__to__any32, (fl), 0, 0)
	#define CAL_real32__to__any32  pfreal32__to__any32
	#define CHK_real32__to__any32  (pfreal32__to__any32 != NULL)
	#define EXP_real32__to__any32   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"real32__to__any32", (RTS_UINTPTR)real32__to__any32, 1, 0) 
#endif


/**
 * <description>
 * <p>This function Converts any 32-bit numeric data type to a 32-bit real value.</p>
 * <p>Data types with less than 32 bits are allowed but the input value has to be casted to 32 bits before.</p>
 * <p>Only integer datatypes are allowed.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_ANY32_TO_REAL32_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[ANY_MIN,ANY_MID,ANY_MAX]">Input data</parampseudo>
 * <parampseudo name="uiType" type="IN" range="[TYPE3_DINT,TYPE3_UDINT,TYPE3_INVALID]">Type of the input data (see TypeClass3 enumeration)</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception thrown</parampseudo>
 * <parampseudo name="out" type="OUT">Input data as 32-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT any32__to__real32(any32_to_real32_struct* p);
typedef void (CDECL * PFANY32__TO__REAL32) (any32_to_real32_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(ANY32__TO__REAL32_NOTIMPLEMENTED)
	#define USE_any32__to__real32
	#define EXT_any32__to__real32
	#define GET_any32__to__real32(fl)  ERR_NOTIMPLEMENTED
	#define CAL_any32__to__real32(p0) 
	#define CHK_any32__to__real32  FALSE
	#define EXP_any32__to__real32  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_any32__to__real32
	#define EXT_any32__to__real32
	#define GET_any32__to__real32(fl)  CAL_CMGETAPI( "any32__to__real32" ) 
	#define CAL_any32__to__real32  any32__to__real32
	#define CHK_any32__to__real32  TRUE
	#define EXP_any32__to__real32  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"any32__to__real32", (RTS_UINTPTR)any32__to__real32, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_any32__to__real32
	#define EXT_any32__to__real32
	#define GET_any32__to__real32(fl)  CAL_CMGETAPI( "any32__to__real32" ) 
	#define CAL_any32__to__real32  any32__to__real32
	#define CHK_any32__to__real32  TRUE
	#define EXP_any32__to__real32  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"any32__to__real32", (RTS_UINTPTR)any32__to__real32, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibany32__to__real32
	#define EXT_SysInternalLibany32__to__real32
	#define GET_SysInternalLibany32__to__real32  ERR_OK
	#define CAL_SysInternalLibany32__to__real32  any32__to__real32
	#define CHK_SysInternalLibany32__to__real32  TRUE
	#define EXP_SysInternalLibany32__to__real32  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"any32__to__real32", (RTS_UINTPTR)any32__to__real32, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_any32__to__real32
	#define EXT_any32__to__real32
	#define GET_any32__to__real32(fl)  CAL_CMGETAPI( "any32__to__real32" ) 
	#define CAL_any32__to__real32  any32__to__real32
	#define CHK_any32__to__real32  TRUE
	#define EXP_any32__to__real32  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"any32__to__real32", (RTS_UINTPTR)any32__to__real32, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_any32__to__real32  PFANY32__TO__REAL32 pfany32__to__real32;
	#define EXT_any32__to__real32  extern PFANY32__TO__REAL32 pfany32__to__real32;
	#define GET_any32__to__real32(fl)  s_pfCMGetAPI2( "any32__to__real32", (RTS_VOID_FCTPTR *)&pfany32__to__real32, (fl), 0, 0)
	#define CAL_any32__to__real32  pfany32__to__real32
	#define CHK_any32__to__real32  (pfany32__to__real32 != NULL)
	#define EXP_any32__to__real32   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"any32__to__real32", (RTS_UINTPTR)any32__to__real32, 1, 0) 
#endif


/**
 * <description>
 * <p>This function Converts a 32-bit real value to any 64-bit numeric data type.</p>
 * <p>Data types with less than 64 bits are allowed but the output value is casted to 64 bits.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_REAL32_TO_ANY64_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[ANY_MIN,ANY_MID,ANY_MAX]">Input value</parampseudo>
 * <parampseudo name="uiType" type="IN" range="[TYPE3_LINT,TYPE3_ULINT]">Type of the output data (see TypeClass3 enumeration)</parampseudo>
 * <parampseudo name="out" type="OUT">Input value as 64-bit data type.</parampseudo>
 */
void CDECL CDECL_EXT real32__to__any64(real32_to_any64_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL32__TO__ANY64_IEC) (real32_to_any64_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__TO__ANY64_NOTIMPLEMENTED)
	#define USE_real32__to__any64
	#define EXT_real32__to__any64
	#define GET_real32__to__any64(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__to__any64(p0) 
	#define CHK_real32__to__any64  FALSE
	#define EXP_real32__to__any64  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__to__any64
	#define EXT_real32__to__any64
	#define GET_real32__to__any64(fl)  CAL_CMGETAPI( "real32__to__any64" ) 
	#define CAL_real32__to__any64  real32__to__any64
	#define CHK_real32__to__any64  TRUE
	#define EXP_real32__to__any64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real32__to__any64", (RTS_UINTPTR)real32__to__any64, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__to__any64
	#define EXT_real32__to__any64
	#define GET_real32__to__any64(fl)  CAL_CMGETAPI( "real32__to__any64" ) 
	#define CAL_real32__to__any64  real32__to__any64
	#define CHK_real32__to__any64  TRUE
	#define EXP_real32__to__any64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real32__to__any64", (RTS_UINTPTR)real32__to__any64, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__to__any64
	#define EXT_SysInternalLibreal32__to__any64
	#define GET_SysInternalLibreal32__to__any64  ERR_OK
	#define CAL_SysInternalLibreal32__to__any64  real32__to__any64
	#define CHK_SysInternalLibreal32__to__any64  TRUE
	#define EXP_SysInternalLibreal32__to__any64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real32__to__any64", (RTS_UINTPTR)real32__to__any64, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__to__any64
	#define EXT_real32__to__any64
	#define GET_real32__to__any64(fl)  CAL_CMGETAPI( "real32__to__any64" ) 
	#define CAL_real32__to__any64  real32__to__any64
	#define CHK_real32__to__any64  TRUE
	#define EXP_real32__to__any64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real32__to__any64", (RTS_UINTPTR)real32__to__any64, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__to__any64  PFREAL32__TO__ANY64_IEC pfreal32__to__any64;
	#define EXT_real32__to__any64  extern PFREAL32__TO__ANY64_IEC pfreal32__to__any64;
	#define GET_real32__to__any64(fl)  s_pfCMGetAPI2( "real32__to__any64", (RTS_VOID_FCTPTR *)&pfreal32__to__any64, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real32__to__any64  pfreal32__to__any64
	#define CHK_real32__to__any64  (pfreal32__to__any64 != NULL)
	#define EXP_real32__to__any64   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real32__to__any64", (RTS_UINTPTR)real32__to__any64, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function Converts any 64-bit numeric data type to a 32-bit real value.</p>
 * <p>Data types with less than 64 bits are allowed but the input value has to be casted to 64 bits before.</p>
 * <p>Only integer datatypes are allowed.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_ANY64_TO_REAL32_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[ANY_MIN,ANY_MID,ANY_MAX]">Input data</parampseudo>
 * <parampseudo name="uiType" type="IN" range="[TYPE3_LINT,TYPE3_ULINT,TYPE3_INVALID]">Type of the input data (see TypeClass3 enumeration)</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception thrown</parampseudo>
 * <parampseudo name="out" type="OUT">Input data as 32-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT any64__to__real32(any64_to_real32_struct* p);
typedef void (CDECL CDECL_EXT* PFANY64__TO__REAL32_IEC) (any64_to_real32_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(ANY64__TO__REAL32_NOTIMPLEMENTED)
	#define USE_any64__to__real32
	#define EXT_any64__to__real32
	#define GET_any64__to__real32(fl)  ERR_NOTIMPLEMENTED
	#define CAL_any64__to__real32(p0) 
	#define CHK_any64__to__real32  FALSE
	#define EXP_any64__to__real32  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_any64__to__real32
	#define EXT_any64__to__real32
	#define GET_any64__to__real32(fl)  CAL_CMGETAPI( "any64__to__real32" ) 
	#define CAL_any64__to__real32  any64__to__real32
	#define CHK_any64__to__real32  TRUE
	#define EXP_any64__to__real32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"any64__to__real32", (RTS_UINTPTR)any64__to__real32, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_any64__to__real32
	#define EXT_any64__to__real32
	#define GET_any64__to__real32(fl)  CAL_CMGETAPI( "any64__to__real32" ) 
	#define CAL_any64__to__real32  any64__to__real32
	#define CHK_any64__to__real32  TRUE
	#define EXP_any64__to__real32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"any64__to__real32", (RTS_UINTPTR)any64__to__real32, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibany64__to__real32
	#define EXT_SysInternalLibany64__to__real32
	#define GET_SysInternalLibany64__to__real32  ERR_OK
	#define CAL_SysInternalLibany64__to__real32  any64__to__real32
	#define CHK_SysInternalLibany64__to__real32  TRUE
	#define EXP_SysInternalLibany64__to__real32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"any64__to__real32", (RTS_UINTPTR)any64__to__real32, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_any64__to__real32
	#define EXT_any64__to__real32
	#define GET_any64__to__real32(fl)  CAL_CMGETAPI( "any64__to__real32" ) 
	#define CAL_any64__to__real32  any64__to__real32
	#define CHK_any64__to__real32  TRUE
	#define EXP_any64__to__real32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"any64__to__real32", (RTS_UINTPTR)any64__to__real32, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_any64__to__real32  PFANY64__TO__REAL32_IEC pfany64__to__real32;
	#define EXT_any64__to__real32  extern PFANY64__TO__REAL32_IEC pfany64__to__real32;
	#define GET_any64__to__real32(fl)  s_pfCMGetAPI2( "any64__to__real32", (RTS_VOID_FCTPTR *)&pfany64__to__real32, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_any64__to__real32  pfany64__to__real32
	#define CHK_any64__to__real32  (pfany64__to__real32 != NULL)
	#define EXP_any64__to__real32   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"any64__to__real32", (RTS_UINTPTR)any64__to__real32, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function Converts a 64-bit real value to any 32-bit numeric data type.</p>
 * <p>Data types with less than 32 bits are allowed but the output value is casted to 32 bits.</p>
 * <p>Only integer datatypes are allowed.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_REAL64_TO_ANY32_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[ANY_MIN,ANY_MID,ANY_MAX]">Input value</parampseudo>
 * <parampseudo name="uiType" type="IN" range="[TYPE3_BOOL, TYPE3_USINT,TYPE3_SINT, TYPE3_UINT,TYPE3_INT, TYPE3_UDINT,TYPE3_DINT, TYPE3_TIMEOFDAY, TYPE3_INVALID]">Type of the output data (see TypeClass3 enumeration)</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception thrown</parampseudo>
 * <parampseudo name="out" type="OUT">Input value as 32-bit data type.</parampseudo>
 */
void CDECL CDECL_EXT real64__to__any32(real64_to_any32_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__TO__ANY32_IEC) (real64_to_any32_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__TO__ANY32_NOTIMPLEMENTED)
	#define USE_real64__to__any32
	#define EXT_real64__to__any32
	#define GET_real64__to__any32(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__to__any32(p0) 
	#define CHK_real64__to__any32  FALSE
	#define EXP_real64__to__any32  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__to__any32
	#define EXT_real64__to__any32
	#define GET_real64__to__any32(fl)  CAL_CMGETAPI( "real64__to__any32" ) 
	#define CAL_real64__to__any32  real64__to__any32
	#define CHK_real64__to__any32  TRUE
	#define EXP_real64__to__any32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__to__any32", (RTS_UINTPTR)real64__to__any32, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__to__any32
	#define EXT_real64__to__any32
	#define GET_real64__to__any32(fl)  CAL_CMGETAPI( "real64__to__any32" ) 
	#define CAL_real64__to__any32  real64__to__any32
	#define CHK_real64__to__any32  TRUE
	#define EXP_real64__to__any32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__to__any32", (RTS_UINTPTR)real64__to__any32, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__to__any32
	#define EXT_SysInternalLibreal64__to__any32
	#define GET_SysInternalLibreal64__to__any32  ERR_OK
	#define CAL_SysInternalLibreal64__to__any32  real64__to__any32
	#define CHK_SysInternalLibreal64__to__any32  TRUE
	#define EXP_SysInternalLibreal64__to__any32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__to__any32", (RTS_UINTPTR)real64__to__any32, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__to__any32
	#define EXT_real64__to__any32
	#define GET_real64__to__any32(fl)  CAL_CMGETAPI( "real64__to__any32" ) 
	#define CAL_real64__to__any32  real64__to__any32
	#define CHK_real64__to__any32  TRUE
	#define EXP_real64__to__any32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__to__any32", (RTS_UINTPTR)real64__to__any32, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__to__any32  PFREAL64__TO__ANY32_IEC pfreal64__to__any32;
	#define EXT_real64__to__any32  extern PFREAL64__TO__ANY32_IEC pfreal64__to__any32;
	#define GET_real64__to__any32(fl)  s_pfCMGetAPI2( "real64__to__any32", (RTS_VOID_FCTPTR *)&pfreal64__to__any32, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__to__any32  pfreal64__to__any32
	#define CHK_real64__to__any32  (pfreal64__to__any32 != NULL)
	#define EXP_real64__to__any32   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__to__any32", (RTS_UINTPTR)real64__to__any32, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function Converts any 32-bit numeric data type to a 64-bit real value.</p>
 * <p>Data types with less than 32 bits are allowed but the input value has to be casted to 32 bits before.</p>
 * <p>Only integer datatypes are allowed.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_ANY32_TO_REAL64_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[ANY_MIN,ANY_MID,ANY_MAX]">Input data</parampseudo>
 * <parampseudo name="uiType" type="IN" range="[TYPE3_DINT,TYPE3_UDINT,TYPE3_INVALID]">Type of the input data (see TypeClass3 enumeration)</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception thrown</parampseudo>
 * <parampseudo name="out" type="OUT">Input data as 64-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT any32__to__real64(any32_to_real64_struct* p);
typedef void (CDECL CDECL_EXT* PFANY32__TO__REAL64_IEC) (any32_to_real64_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(ANY32__TO__REAL64_NOTIMPLEMENTED)
	#define USE_any32__to__real64
	#define EXT_any32__to__real64
	#define GET_any32__to__real64(fl)  ERR_NOTIMPLEMENTED
	#define CAL_any32__to__real64(p0) 
	#define CHK_any32__to__real64  FALSE
	#define EXP_any32__to__real64  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_any32__to__real64
	#define EXT_any32__to__real64
	#define GET_any32__to__real64(fl)  CAL_CMGETAPI( "any32__to__real64" ) 
	#define CAL_any32__to__real64  any32__to__real64
	#define CHK_any32__to__real64  TRUE
	#define EXP_any32__to__real64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"any32__to__real64", (RTS_UINTPTR)any32__to__real64, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_any32__to__real64
	#define EXT_any32__to__real64
	#define GET_any32__to__real64(fl)  CAL_CMGETAPI( "any32__to__real64" ) 
	#define CAL_any32__to__real64  any32__to__real64
	#define CHK_any32__to__real64  TRUE
	#define EXP_any32__to__real64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"any32__to__real64", (RTS_UINTPTR)any32__to__real64, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibany32__to__real64
	#define EXT_SysInternalLibany32__to__real64
	#define GET_SysInternalLibany32__to__real64  ERR_OK
	#define CAL_SysInternalLibany32__to__real64  any32__to__real64
	#define CHK_SysInternalLibany32__to__real64  TRUE
	#define EXP_SysInternalLibany32__to__real64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"any32__to__real64", (RTS_UINTPTR)any32__to__real64, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_any32__to__real64
	#define EXT_any32__to__real64
	#define GET_any32__to__real64(fl)  CAL_CMGETAPI( "any32__to__real64" ) 
	#define CAL_any32__to__real64  any32__to__real64
	#define CHK_any32__to__real64  TRUE
	#define EXP_any32__to__real64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"any32__to__real64", (RTS_UINTPTR)any32__to__real64, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_any32__to__real64  PFANY32__TO__REAL64_IEC pfany32__to__real64;
	#define EXT_any32__to__real64  extern PFANY32__TO__REAL64_IEC pfany32__to__real64;
	#define GET_any32__to__real64(fl)  s_pfCMGetAPI2( "any32__to__real64", (RTS_VOID_FCTPTR *)&pfany32__to__real64, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_any32__to__real64  pfany32__to__real64
	#define CHK_any32__to__real64  (pfany32__to__real64 != NULL)
	#define EXP_any32__to__real64   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"any32__to__real64", (RTS_UINTPTR)any32__to__real64, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function Converts a 64-bit real value to any 64-bit numeric data type.</p>
 * <p>Data types with less than 64 bits are allowed but the output value is casted to 64 bits.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_REAL64_TO_ANY64_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[ANY_MIN, ANY_MID, ANY_MAX]">Input value</parampseudo>
 * <parampseudo name="uiType" type="IN" range="[TYPE3_LINT,TYPE3_ULINT]">Type of the output data (see TypeClass3 enumeration)</parampseudo>
 * <parampseudo name="out" type="OUT">Input value as 64-bit data type.</parampseudo>
 */
void CDECL CDECL_EXT real64__to__any64(real64_to_any64_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__TO__ANY64_IEC) (real64_to_any64_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__TO__ANY64_NOTIMPLEMENTED)
	#define USE_real64__to__any64
	#define EXT_real64__to__any64
	#define GET_real64__to__any64(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__to__any64(p0) 
	#define CHK_real64__to__any64  FALSE
	#define EXP_real64__to__any64  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__to__any64
	#define EXT_real64__to__any64
	#define GET_real64__to__any64(fl)  CAL_CMGETAPI( "real64__to__any64" ) 
	#define CAL_real64__to__any64  real64__to__any64
	#define CHK_real64__to__any64  TRUE
	#define EXP_real64__to__any64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__to__any64", (RTS_UINTPTR)real64__to__any64, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__to__any64
	#define EXT_real64__to__any64
	#define GET_real64__to__any64(fl)  CAL_CMGETAPI( "real64__to__any64" ) 
	#define CAL_real64__to__any64  real64__to__any64
	#define CHK_real64__to__any64  TRUE
	#define EXP_real64__to__any64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__to__any64", (RTS_UINTPTR)real64__to__any64, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__to__any64
	#define EXT_SysInternalLibreal64__to__any64
	#define GET_SysInternalLibreal64__to__any64  ERR_OK
	#define CAL_SysInternalLibreal64__to__any64  real64__to__any64
	#define CHK_SysInternalLibreal64__to__any64  TRUE
	#define EXP_SysInternalLibreal64__to__any64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__to__any64", (RTS_UINTPTR)real64__to__any64, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__to__any64
	#define EXT_real64__to__any64
	#define GET_real64__to__any64(fl)  CAL_CMGETAPI( "real64__to__any64" ) 
	#define CAL_real64__to__any64  real64__to__any64
	#define CHK_real64__to__any64  TRUE
	#define EXP_real64__to__any64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__to__any64", (RTS_UINTPTR)real64__to__any64, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__to__any64  PFREAL64__TO__ANY64_IEC pfreal64__to__any64;
	#define EXT_real64__to__any64  extern PFREAL64__TO__ANY64_IEC pfreal64__to__any64;
	#define GET_real64__to__any64(fl)  s_pfCMGetAPI2( "real64__to__any64", (RTS_VOID_FCTPTR *)&pfreal64__to__any64, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__to__any64  pfreal64__to__any64
	#define CHK_real64__to__any64  (pfreal64__to__any64 != NULL)
	#define EXP_real64__to__any64   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__to__any64", (RTS_UINTPTR)real64__to__any64, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function Converts any 64-bit numeric data type to a 64-bit real value.</p>
 * <p>Data types with less than 64 bits are allowed but the input value has to be casted to 64 bits before.</p>
 * <p>Only integer datatypes are allowed.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_ANY64_TO_REAL64_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[ANY_MIN, ANY_MID, ANY_MAX]">Input data</parampseudo>
 * <parampseudo name="uiType" type="IN" range="[TYPE3_LINT,TYPE3_ULINT,TYPE3_INVALID]">Type of the input data (see TypeClass3 enumeration)</parampseudo>
 * <parampseudo name="bException" type="OUT">Exception thrown</parampseudo>
 * <parampseudo name="out" type="OUT">Input data as 64-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT any64__to__real64(any64_to_real64_struct* p);
typedef void (CDECL CDECL_EXT* PFANY64__TO__REAL64_IEC) (any64_to_real64_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(ANY64__TO__REAL64_NOTIMPLEMENTED)
	#define USE_any64__to__real64
	#define EXT_any64__to__real64
	#define GET_any64__to__real64(fl)  ERR_NOTIMPLEMENTED
	#define CAL_any64__to__real64(p0) 
	#define CHK_any64__to__real64  FALSE
	#define EXP_any64__to__real64  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_any64__to__real64
	#define EXT_any64__to__real64
	#define GET_any64__to__real64(fl)  CAL_CMGETAPI( "any64__to__real64" ) 
	#define CAL_any64__to__real64  any64__to__real64
	#define CHK_any64__to__real64  TRUE
	#define EXP_any64__to__real64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"any64__to__real64", (RTS_UINTPTR)any64__to__real64, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_any64__to__real64
	#define EXT_any64__to__real64
	#define GET_any64__to__real64(fl)  CAL_CMGETAPI( "any64__to__real64" ) 
	#define CAL_any64__to__real64  any64__to__real64
	#define CHK_any64__to__real64  TRUE
	#define EXP_any64__to__real64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"any64__to__real64", (RTS_UINTPTR)any64__to__real64, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibany64__to__real64
	#define EXT_SysInternalLibany64__to__real64
	#define GET_SysInternalLibany64__to__real64  ERR_OK
	#define CAL_SysInternalLibany64__to__real64  any64__to__real64
	#define CHK_SysInternalLibany64__to__real64  TRUE
	#define EXP_SysInternalLibany64__to__real64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"any64__to__real64", (RTS_UINTPTR)any64__to__real64, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_any64__to__real64
	#define EXT_any64__to__real64
	#define GET_any64__to__real64(fl)  CAL_CMGETAPI( "any64__to__real64" ) 
	#define CAL_any64__to__real64  any64__to__real64
	#define CHK_any64__to__real64  TRUE
	#define EXP_any64__to__real64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"any64__to__real64", (RTS_UINTPTR)any64__to__real64, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_any64__to__real64  PFANY64__TO__REAL64_IEC pfany64__to__real64;
	#define EXT_any64__to__real64  extern PFANY64__TO__REAL64_IEC pfany64__to__real64;
	#define GET_any64__to__real64(fl)  s_pfCMGetAPI2( "any64__to__real64", (RTS_VOID_FCTPTR *)&pfany64__to__real64, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_any64__to__real64  pfany64__to__real64
	#define CHK_any64__to__real64  (pfany64__to__real64 != NULL)
	#define EXP_any64__to__real64   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"any64__to__real64", (RTS_UINTPTR)any64__to__real64, 1, 0, 0) 
#endif


/**
 * <description>This function Converts a 64-bit real value to a 32-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_REAL64_TO_REAL32_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[ANY_MIN, ANY_MID, ANY_MAX]">Input value</parampseudo>
 * <parampseudo name="out" type="OUT">Input value as 32-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real64__to__real32(real64_to_real32_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__TO__REAL32_IEC) (real64_to_real32_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__TO__REAL32_NOTIMPLEMENTED)
	#define USE_real64__to__real32
	#define EXT_real64__to__real32
	#define GET_real64__to__real32(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__to__real32(p0) 
	#define CHK_real64__to__real32  FALSE
	#define EXP_real64__to__real32  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__to__real32
	#define EXT_real64__to__real32
	#define GET_real64__to__real32(fl)  CAL_CMGETAPI( "real64__to__real32" ) 
	#define CAL_real64__to__real32  real64__to__real32
	#define CHK_real64__to__real32  TRUE
	#define EXP_real64__to__real32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__to__real32", (RTS_UINTPTR)real64__to__real32, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__to__real32
	#define EXT_real64__to__real32
	#define GET_real64__to__real32(fl)  CAL_CMGETAPI( "real64__to__real32" ) 
	#define CAL_real64__to__real32  real64__to__real32
	#define CHK_real64__to__real32  TRUE
	#define EXP_real64__to__real32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__to__real32", (RTS_UINTPTR)real64__to__real32, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__to__real32
	#define EXT_SysInternalLibreal64__to__real32
	#define GET_SysInternalLibreal64__to__real32  ERR_OK
	#define CAL_SysInternalLibreal64__to__real32  real64__to__real32
	#define CHK_SysInternalLibreal64__to__real32  TRUE
	#define EXP_SysInternalLibreal64__to__real32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__to__real32", (RTS_UINTPTR)real64__to__real32, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__to__real32
	#define EXT_real64__to__real32
	#define GET_real64__to__real32(fl)  CAL_CMGETAPI( "real64__to__real32" ) 
	#define CAL_real64__to__real32  real64__to__real32
	#define CHK_real64__to__real32  TRUE
	#define EXP_real64__to__real32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__to__real32", (RTS_UINTPTR)real64__to__real32, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__to__real32  PFREAL64__TO__REAL32_IEC pfreal64__to__real32;
	#define EXT_real64__to__real32  extern PFREAL64__TO__REAL32_IEC pfreal64__to__real32;
	#define GET_real64__to__real32(fl)  s_pfCMGetAPI2( "real64__to__real32", (RTS_VOID_FCTPTR *)&pfreal64__to__real32, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__to__real32  pfreal64__to__real32
	#define CHK_real64__to__real32  (pfreal64__to__real32 != NULL)
	#define EXP_real64__to__real32   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__to__real32", (RTS_UINTPTR)real64__to__real32, 1, 0, 0) 
#endif


/**
 * <description>This function Converts a 32-bit real value to a 64-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_REAL32_TO_REAL64_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[ANY_MIN, ANY_MID, ANY_MAX]">Input value</parampseudo>
 * <parampseudo name="out" type="OUT">Input value as 64-bit real value.</parampseudo>
 */
void CDECL CDECL_EXT real32__to__real64(real32_to_real64_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL32__TO__REAL64_IEC) (real32_to_real64_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL32__TO__REAL64_NOTIMPLEMENTED)
	#define USE_real32__to__real64
	#define EXT_real32__to__real64
	#define GET_real32__to__real64(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real32__to__real64(p0) 
	#define CHK_real32__to__real64  FALSE
	#define EXP_real32__to__real64  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real32__to__real64
	#define EXT_real32__to__real64
	#define GET_real32__to__real64(fl)  CAL_CMGETAPI( "real32__to__real64" ) 
	#define CAL_real32__to__real64  real32__to__real64
	#define CHK_real32__to__real64  TRUE
	#define EXP_real32__to__real64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real32__to__real64", (RTS_UINTPTR)real32__to__real64, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real32__to__real64
	#define EXT_real32__to__real64
	#define GET_real32__to__real64(fl)  CAL_CMGETAPI( "real32__to__real64" ) 
	#define CAL_real32__to__real64  real32__to__real64
	#define CHK_real32__to__real64  TRUE
	#define EXP_real32__to__real64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real32__to__real64", (RTS_UINTPTR)real32__to__real64, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal32__to__real64
	#define EXT_SysInternalLibreal32__to__real64
	#define GET_SysInternalLibreal32__to__real64  ERR_OK
	#define CAL_SysInternalLibreal32__to__real64  real32__to__real64
	#define CHK_SysInternalLibreal32__to__real64  TRUE
	#define EXP_SysInternalLibreal32__to__real64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real32__to__real64", (RTS_UINTPTR)real32__to__real64, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real32__to__real64
	#define EXT_real32__to__real64
	#define GET_real32__to__real64(fl)  CAL_CMGETAPI( "real32__to__real64" ) 
	#define CAL_real32__to__real64  real32__to__real64
	#define CHK_real32__to__real64  TRUE
	#define EXP_real32__to__real64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real32__to__real64", (RTS_UINTPTR)real32__to__real64, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real32__to__real64  PFREAL32__TO__REAL64_IEC pfreal32__to__real64;
	#define EXT_real32__to__real64  extern PFREAL32__TO__REAL64_IEC pfreal32__to__real64;
	#define GET_real32__to__real64(fl)  s_pfCMGetAPI2( "real32__to__real64", (RTS_VOID_FCTPTR *)&pfreal32__to__real64, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real32__to__real64  pfreal32__to__real64
	#define CHK_real32__to__real64  (pfreal32__to__real64 != NULL)
	#define EXP_real32__to__real64   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real32__to__real64", (RTS_UINTPTR)real32__to__real64, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function read a 64bit real value atomic.</p>
 * </description>
 * <param name="p" type="IN"">Pointer to the input structure</param>
 * <parampseudo name="pSrc" type="IN">Pointer to source address to read from</parampseudo>
 * <parampseudo name="pResult" type="IN">Pointer to error code</parampseudo>
 * <parampseudo name="out" type="OUT">Read 64bit integer value.</parampseudo>
 */
void CDECL CDECL_EXT real64__atomicread(real64_atomicread_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__ATOMICREAD_IEC) (real64_atomicread_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__ATOMICREAD_NOTIMPLEMENTED)
	#define USE_real64__atomicread
	#define EXT_real64__atomicread
	#define GET_real64__atomicread(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__atomicread(p0) 
	#define CHK_real64__atomicread  FALSE
	#define EXP_real64__atomicread  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__atomicread
	#define EXT_real64__atomicread
	#define GET_real64__atomicread(fl)  CAL_CMGETAPI( "real64__atomicread" ) 
	#define CAL_real64__atomicread  real64__atomicread
	#define CHK_real64__atomicread  TRUE
	#define EXP_real64__atomicread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__atomicread", (RTS_UINTPTR)real64__atomicread, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__atomicread
	#define EXT_real64__atomicread
	#define GET_real64__atomicread(fl)  CAL_CMGETAPI( "real64__atomicread" ) 
	#define CAL_real64__atomicread  real64__atomicread
	#define CHK_real64__atomicread  TRUE
	#define EXP_real64__atomicread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__atomicread", (RTS_UINTPTR)real64__atomicread, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__atomicread
	#define EXT_SysInternalLibreal64__atomicread
	#define GET_SysInternalLibreal64__atomicread  ERR_OK
	#define CAL_SysInternalLibreal64__atomicread  real64__atomicread
	#define CHK_SysInternalLibreal64__atomicread  TRUE
	#define EXP_SysInternalLibreal64__atomicread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__atomicread", (RTS_UINTPTR)real64__atomicread, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__atomicread
	#define EXT_real64__atomicread
	#define GET_real64__atomicread(fl)  CAL_CMGETAPI( "real64__atomicread" ) 
	#define CAL_real64__atomicread  real64__atomicread
	#define CHK_real64__atomicread  TRUE
	#define EXP_real64__atomicread  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__atomicread", (RTS_UINTPTR)real64__atomicread, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__atomicread  PFREAL64__ATOMICREAD_IEC pfreal64__atomicread;
	#define EXT_real64__atomicread  extern PFREAL64__ATOMICREAD_IEC pfreal64__atomicread;
	#define GET_real64__atomicread(fl)  s_pfCMGetAPI2( "real64__atomicread", (RTS_VOID_FCTPTR *)&pfreal64__atomicread, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__atomicread  pfreal64__atomicread
	#define CHK_real64__atomicread  (pfreal64__atomicread != NULL)
	#define EXP_real64__atomicread   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__atomicread", (RTS_UINTPTR)real64__atomicread, 1, 0, 0) 
#endif


/**
 * <description>
 * <p>This function write a 64bit real value atomic.</p>
 * </description>
 * <param name="p" type="IN"">Pointer to the input structure</param>
 * <parampseudo name="pDest" type="IN">Pointer to destination address to write to</parampseudo>
 * <parampseudo name="write" type="IN">Value to write</parampseudo>
 * <parampseudo name="out" type="OUT">Error code for result.</parampseudo>
 */
void CDECL CDECL_EXT real64__atomicwrite(real64_atomicwrite_struct* p);
typedef void (CDECL CDECL_EXT* PFREAL64__ATOMICWRITE_IEC) (real64_atomicwrite_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(REAL64__ATOMICWRITE_NOTIMPLEMENTED)
	#define USE_real64__atomicwrite
	#define EXT_real64__atomicwrite
	#define GET_real64__atomicwrite(fl)  ERR_NOTIMPLEMENTED
	#define CAL_real64__atomicwrite(p0) 
	#define CHK_real64__atomicwrite  FALSE
	#define EXP_real64__atomicwrite  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_real64__atomicwrite
	#define EXT_real64__atomicwrite
	#define GET_real64__atomicwrite(fl)  CAL_CMGETAPI( "real64__atomicwrite" ) 
	#define CAL_real64__atomicwrite  real64__atomicwrite
	#define CHK_real64__atomicwrite  TRUE
	#define EXP_real64__atomicwrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__atomicwrite", (RTS_UINTPTR)real64__atomicwrite, 1, 0, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_real64__atomicwrite
	#define EXT_real64__atomicwrite
	#define GET_real64__atomicwrite(fl)  CAL_CMGETAPI( "real64__atomicwrite" ) 
	#define CAL_real64__atomicwrite  real64__atomicwrite
	#define CHK_real64__atomicwrite  TRUE
	#define EXP_real64__atomicwrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__atomicwrite", (RTS_UINTPTR)real64__atomicwrite, 1, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibreal64__atomicwrite
	#define EXT_SysInternalLibreal64__atomicwrite
	#define GET_SysInternalLibreal64__atomicwrite  ERR_OK
	#define CAL_SysInternalLibreal64__atomicwrite  real64__atomicwrite
	#define CHK_SysInternalLibreal64__atomicwrite  TRUE
	#define EXP_SysInternalLibreal64__atomicwrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__atomicwrite", (RTS_UINTPTR)real64__atomicwrite, 1, 0, 0) 
#elif defined(CPLUSPLUS)
	#define USE_real64__atomicwrite
	#define EXT_real64__atomicwrite
	#define GET_real64__atomicwrite(fl)  CAL_CMGETAPI( "real64__atomicwrite" ) 
	#define CAL_real64__atomicwrite  real64__atomicwrite
	#define CHK_real64__atomicwrite  TRUE
	#define EXP_real64__atomicwrite  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__atomicwrite", (RTS_UINTPTR)real64__atomicwrite, 1, 0, 0) 
#else /* DYNAMIC_LINK */
	#define USE_real64__atomicwrite  PFREAL64__ATOMICWRITE_IEC pfreal64__atomicwrite;
	#define EXT_real64__atomicwrite  extern PFREAL64__ATOMICWRITE_IEC pfreal64__atomicwrite;
	#define GET_real64__atomicwrite(fl)  s_pfCMGetAPI2( "real64__atomicwrite", (RTS_VOID_FCTPTR *)&pfreal64__atomicwrite, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0, 0)
	#define CAL_real64__atomicwrite  pfreal64__atomicwrite
	#define CHK_real64__atomicwrite  (pfreal64__atomicwrite != NULL)
	#define EXP_real64__atomicwrite   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"real64__atomicwrite", (RTS_UINTPTR)real64__atomicwrite, 1, 0, 0) 
#endif


/**
 * <description>This function returns a monotonic rising millisecond tick. This tick can be used for timeout and relative time measurements.</description>
 * <param name="p" type="IN" range="[VALID_GET_TIME_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="out" type="OUT">millisecond tick as 32-Bit value.</parampseudo>
 */
void CDECL CDECL_EXT get__time(get_time_struct* p);
typedef void (CDECL * PFGET__TIME) (get_time_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(GET__TIME_NOTIMPLEMENTED)
	#define USE_get__time
	#define EXT_get__time
	#define GET_get__time(fl)  ERR_NOTIMPLEMENTED
	#define CAL_get__time(p0) 
	#define CHK_get__time  FALSE
	#define EXP_get__time  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_get__time
	#define EXT_get__time
	#define GET_get__time(fl)  CAL_CMGETAPI( "get__time" ) 
	#define CAL_get__time  get__time
	#define CHK_get__time  TRUE
	#define EXP_get__time  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"get__time", (RTS_UINTPTR)get__time, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_get__time
	#define EXT_get__time
	#define GET_get__time(fl)  CAL_CMGETAPI( "get__time" ) 
	#define CAL_get__time  get__time
	#define CHK_get__time  TRUE
	#define EXP_get__time  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"get__time", (RTS_UINTPTR)get__time, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibget__time
	#define EXT_SysInternalLibget__time
	#define GET_SysInternalLibget__time  ERR_OK
	#define CAL_SysInternalLibget__time  get__time
	#define CHK_SysInternalLibget__time  TRUE
	#define EXP_SysInternalLibget__time  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"get__time", (RTS_UINTPTR)get__time, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_get__time
	#define EXT_get__time
	#define GET_get__time(fl)  CAL_CMGETAPI( "get__time" ) 
	#define CAL_get__time  get__time
	#define CHK_get__time  TRUE
	#define EXP_get__time  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"get__time", (RTS_UINTPTR)get__time, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_get__time  PFGET__TIME pfget__time;
	#define EXT_get__time  extern PFGET__TIME pfget__time;
	#define GET_get__time(fl)  s_pfCMGetAPI2( "get__time", (RTS_VOID_FCTPTR *)&pfget__time, (fl), 0, 0)
	#define CAL_get__time  pfget__time
	#define CHK_get__time  (pfget__time != NULL)
	#define EXP_get__time   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"get__time", (RTS_UINTPTR)get__time, 1, 0) 
#endif


/**
 * <description>This function returns a monotonic rising nanosecond tick. This tick can be used for very high resolution time measurements.</description>
 * <param name="p" type="IN" range="[VALID_GET_LTIME_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="out" type="OUT">microsecond tick as 64-Bit value.</parampseudo>
 */
void CDECL CDECL_EXT get__ltime(get_ltime_struct* p);
typedef void (CDECL * PFGET__LTIME) (get_ltime_struct* p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(GET__LTIME_NOTIMPLEMENTED)
	#define USE_get__ltime
	#define EXT_get__ltime
	#define GET_get__ltime(fl)  ERR_NOTIMPLEMENTED
	#define CAL_get__ltime(p0) 
	#define CHK_get__ltime  FALSE
	#define EXP_get__ltime  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_get__ltime
	#define EXT_get__ltime
	#define GET_get__ltime(fl)  CAL_CMGETAPI( "get__ltime" ) 
	#define CAL_get__ltime  get__ltime
	#define CHK_get__ltime  TRUE
	#define EXP_get__ltime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"get__ltime", (RTS_UINTPTR)get__ltime, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_get__ltime
	#define EXT_get__ltime
	#define GET_get__ltime(fl)  CAL_CMGETAPI( "get__ltime" ) 
	#define CAL_get__ltime  get__ltime
	#define CHK_get__ltime  TRUE
	#define EXP_get__ltime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"get__ltime", (RTS_UINTPTR)get__ltime, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibget__ltime
	#define EXT_SysInternalLibget__ltime
	#define GET_SysInternalLibget__ltime  ERR_OK
	#define CAL_SysInternalLibget__ltime  get__ltime
	#define CHK_SysInternalLibget__ltime  TRUE
	#define EXP_SysInternalLibget__ltime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"get__ltime", (RTS_UINTPTR)get__ltime, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_get__ltime
	#define EXT_get__ltime
	#define GET_get__ltime(fl)  CAL_CMGETAPI( "get__ltime" ) 
	#define CAL_get__ltime  get__ltime
	#define CHK_get__ltime  TRUE
	#define EXP_get__ltime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"get__ltime", (RTS_UINTPTR)get__ltime, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_get__ltime  PFGET__LTIME pfget__ltime;
	#define EXT_get__ltime  extern PFGET__LTIME pfget__ltime;
	#define GET_get__ltime(fl)  s_pfCMGetAPI2( "get__ltime", (RTS_VOID_FCTPTR *)&pfget__ltime, (fl), 0, 0)
	#define CAL_get__ltime  pfget__ltime
	#define CHK_get__ltime  (pfget__ltime != NULL)
	#define EXP_get__ltime   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"get__ltime", (RTS_UINTPTR)get__ltime, 1, 0) 
#endif


/**
 * <description>Fill the buffer with a specified value. Routine is used as external library function for the plc program.</description>
 * <param name="p" type="IN">Pointer to the input structure</param>
 * <parampseudo name="out" type="OUT">Value of pDest or 0 if failed</parampseudo>
 */
void CDECL CDECL_EXT __memset(__memset_struct *p);
typedef void (CDECL CDECL_EXT* PF__MEMSET_IEC) (__memset_struct *p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(__MEMSET_NOTIMPLEMENTED)
	#define USE___memset
	#define EXT___memset
	#define GET___memset(fl)  ERR_NOTIMPLEMENTED
	#define CAL___memset(p0) 
	#define CHK___memset  FALSE
	#define EXP___memset  ERR_OK
#elif defined(STATIC_LINK)
	#define USE___memset
	#define EXT___memset
	#define GET___memset(fl)  CAL_CMGETAPI( "__memset" ) 
	#define CAL___memset  __memset
	#define CHK___memset  TRUE
	#define EXP___memset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__memset", (RTS_UINTPTR)__memset, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE___memset
	#define EXT___memset
	#define GET___memset(fl)  CAL_CMGETAPI( "__memset" ) 
	#define CAL___memset  __memset
	#define CHK___memset  TRUE
	#define EXP___memset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__memset", (RTS_UINTPTR)__memset, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLib__memset
	#define EXT_SysInternalLib__memset
	#define GET_SysInternalLib__memset  ERR_OK
	#define CAL_SysInternalLib__memset  __memset
	#define CHK_SysInternalLib__memset  TRUE
	#define EXP_SysInternalLib__memset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__memset", (RTS_UINTPTR)__memset, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE___memset
	#define EXT___memset
	#define GET___memset(fl)  CAL_CMGETAPI( "__memset" ) 
	#define CAL___memset  __memset
	#define CHK___memset  TRUE
	#define EXP___memset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__memset", (RTS_UINTPTR)__memset, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE___memset  PF__MEMSET_IEC pf__memset;
	#define EXT___memset  extern PF__MEMSET_IEC pf__memset;
	#define GET___memset(fl)  s_pfCMGetAPI2( "__memset", (RTS_VOID_FCTPTR *)&pf__memset, (fl), 0, 0)
	#define CAL___memset  pf__memset
	#define CHK___memset  (pf__memset != NULL)
	#define EXP___memset   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"__memset", (RTS_UINTPTR)__memset, 1, 0) 
#endif


/**
 * <description>A simple exception handling function</description>
 * <param name="p" type="IN">Pointer to the input structure</param>
 * <parampseudo name="out" type="OUT">ExceptionCode or 0 for noeexception</parampseudo>
 */
void CDECL CDECL_EXT trycatch(trycatch_struct *p);
typedef void (CDECL CDECL_EXT* PFTRYCATCH_IEC) (trycatch_struct *p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(TRYCATCH_NOTIMPLEMENTED)
	#define USE_trycatch
	#define EXT_trycatch
	#define GET_trycatch(fl)  ERR_NOTIMPLEMENTED
	#define CAL_trycatch(p0) 
	#define CHK_trycatch  FALSE
	#define EXP_trycatch  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_trycatch
	#define EXT_trycatch
	#define GET_trycatch(fl)  CAL_CMGETAPI( "trycatch" ) 
	#define CAL_trycatch  trycatch
	#define CHK_trycatch  TRUE
	#define EXP_trycatch  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"trycatch", (RTS_UINTPTR)trycatch, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_trycatch
	#define EXT_trycatch
	#define GET_trycatch(fl)  CAL_CMGETAPI( "trycatch" ) 
	#define CAL_trycatch  trycatch
	#define CHK_trycatch  TRUE
	#define EXP_trycatch  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"trycatch", (RTS_UINTPTR)trycatch, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibtrycatch
	#define EXT_SysInternalLibtrycatch
	#define GET_SysInternalLibtrycatch  ERR_OK
	#define CAL_SysInternalLibtrycatch  trycatch
	#define CHK_SysInternalLibtrycatch  TRUE
	#define EXP_SysInternalLibtrycatch  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"trycatch", (RTS_UINTPTR)trycatch, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_trycatch
	#define EXT_trycatch
	#define GET_trycatch(fl)  CAL_CMGETAPI( "trycatch" ) 
	#define CAL_trycatch  trycatch
	#define CHK_trycatch  TRUE
	#define EXP_trycatch  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"trycatch", (RTS_UINTPTR)trycatch, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_trycatch  PFTRYCATCH_IEC pftrycatch;
	#define EXT_trycatch  extern PFTRYCATCH_IEC pftrycatch;
	#define GET_trycatch(fl)  s_pfCMGetAPI2( "trycatch", (RTS_VOID_FCTPTR *)&pftrycatch, (fl), 0, 0)
	#define CAL_trycatch  pftrycatch
	#define CHK_trycatch  (pftrycatch != NULL)
	#define EXP_trycatch   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"trycatch", (RTS_UINTPTR)trycatch, 1, 0) 
#endif


/**
 * <description>Function to lock the actual timestamp for all IEC timers.</description>
 * <result><p>RESULT: Returns always 0</p></result>
 */
typedef struct tagsystimelock_struct
{
	RTS_IEC_TIME ulTick;				/* VAR_INPUT */	/* <param name="ulTick" type="IN">Actual tick value for the timer to lock</param> */
	RTS_IEC_TIME tTimeout;				/* VAR_INPUT */	/* <param name="tTimeout" type="IN">Timeout in milliseconds until the lock is released at least!</param> */
	RTS_IEC_WORD SysTimeLock;			/* VAR_OUTPUT */	
} systimelock_struct;

void CDECL CDECL_EXT systimelock(systimelock_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTIMELOCK_IEC) (systimelock_struct *p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(SYSTIMELOCK_NOTIMPLEMENTED)
	#define USE_systimelock
	#define EXT_systimelock
	#define GET_systimelock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systimelock(p0) 
	#define CHK_systimelock  FALSE
	#define EXP_systimelock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systimelock
	#define EXT_systimelock
	#define GET_systimelock(fl)  CAL_CMGETAPI( "systimelock" ) 
	#define CAL_systimelock  systimelock
	#define CHK_systimelock  TRUE
	#define EXP_systimelock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimelock", (RTS_UINTPTR)systimelock, 1, 0x9F97092C, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_systimelock
	#define EXT_systimelock
	#define GET_systimelock(fl)  CAL_CMGETAPI( "systimelock" ) 
	#define CAL_systimelock  systimelock
	#define CHK_systimelock  TRUE
	#define EXP_systimelock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimelock", (RTS_UINTPTR)systimelock, 1, 0x9F97092C, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibsystimelock
	#define EXT_SysInternalLibsystimelock
	#define GET_SysInternalLibsystimelock  ERR_OK
	#define CAL_SysInternalLibsystimelock  systimelock
	#define CHK_SysInternalLibsystimelock  TRUE
	#define EXP_SysInternalLibsystimelock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimelock", (RTS_UINTPTR)systimelock, 1, 0x9F97092C, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systimelock
	#define EXT_systimelock
	#define GET_systimelock(fl)  CAL_CMGETAPI( "systimelock" ) 
	#define CAL_systimelock  systimelock
	#define CHK_systimelock  TRUE
	#define EXP_systimelock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimelock", (RTS_UINTPTR)systimelock, 1, 0x9F97092C, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systimelock  PFSYSTIMELOCK_IEC pfsystimelock;
	#define EXT_systimelock  extern PFSYSTIMELOCK_IEC pfsystimelock;
	#define GET_systimelock(fl)  s_pfCMGetAPI2( "systimelock", (RTS_VOID_FCTPTR *)&pfsystimelock, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x9F97092C, 0x03050500)
	#define CAL_systimelock  pfsystimelock
	#define CHK_systimelock  (pfsystimelock != NULL)
	#define EXP_systimelock   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimelock", (RTS_UINTPTR)systimelock, 1, 0x9F97092C, 0x03050500) 
#endif


/**
 * <description>Function to set the actual timestamp for all IEC timers. Differnt to SysTimeLock, the timer continues</description>
 * <result><p>RESULT: Returns always 0</p></result>
 */
typedef struct tagsystimeset_struct
{
	RTS_IEC_TIME ulTick;				/* VAR_INPUT */	/* <param name="ulTick" type="IN">Actual tick value for the timer to set</param> */
	RTS_IEC_TIME tTimeout;				/* VAR_INPUT */	/* <param name="tTimeout" type="IN">Timeout in milliseconds until the setting is released at least!</param> */
	RTS_IEC_WORD SysTimeSet;			/* VAR_OUTPUT */	
} systimeset_struct;

void CDECL CDECL_EXT systimeset(systimeset_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTIMESET_IEC) (systimeset_struct *p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(SYSTIMESET_NOTIMPLEMENTED)
	#define USE_systimeset
	#define EXT_systimeset
	#define GET_systimeset(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systimeset(p0) 
	#define CHK_systimeset  FALSE
	#define EXP_systimeset  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systimeset
	#define EXT_systimeset
	#define GET_systimeset(fl)  CAL_CMGETAPI( "systimeset" ) 
	#define CAL_systimeset  systimeset
	#define CHK_systimeset  TRUE
	#define EXP_systimeset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimeset", (RTS_UINTPTR)systimeset, 1, 0xED35B558, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_systimeset
	#define EXT_systimeset
	#define GET_systimeset(fl)  CAL_CMGETAPI( "systimeset" ) 
	#define CAL_systimeset  systimeset
	#define CHK_systimeset  TRUE
	#define EXP_systimeset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimeset", (RTS_UINTPTR)systimeset, 1, 0xED35B558, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibsystimeset
	#define EXT_SysInternalLibsystimeset
	#define GET_SysInternalLibsystimeset  ERR_OK
	#define CAL_SysInternalLibsystimeset  systimeset
	#define CHK_SysInternalLibsystimeset  TRUE
	#define EXP_SysInternalLibsystimeset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimeset", (RTS_UINTPTR)systimeset, 1, 0xED35B558, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systimeset
	#define EXT_systimeset
	#define GET_systimeset(fl)  CAL_CMGETAPI( "systimeset" ) 
	#define CAL_systimeset  systimeset
	#define CHK_systimeset  TRUE
	#define EXP_systimeset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimeset", (RTS_UINTPTR)systimeset, 1, 0xED35B558, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systimeset  PFSYSTIMESET_IEC pfsystimeset;
	#define EXT_systimeset  extern PFSYSTIMESET_IEC pfsystimeset;
	#define GET_systimeset(fl)  s_pfCMGetAPI2( "systimeset", (RTS_VOID_FCTPTR *)&pfsystimeset, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xED35B558, 0x03050500)
	#define CAL_systimeset  pfsystimeset
	#define CHK_systimeset  (pfsystimeset != NULL)
	#define EXP_systimeset   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimeset", (RTS_UINTPTR)systimeset, 1, 0xED35B558, 0x03050500) 
#endif


/**
 * <description>Function to unlock the actual timestamp for all IEC timers.</description>
 * <result><p>RESULT: Returns always 0</p></result>
 */
typedef struct tagsystimeunlock_struct
{
	RTS_IEC_WORD SysTimeUnlock;			/* VAR_OUTPUT */	
} systimeunlock_struct;

void CDECL CDECL_EXT systimeunlock(systimeunlock_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTIMEUNLOCK_IEC) (systimeunlock_struct *p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(SYSTIMEUNLOCK_NOTIMPLEMENTED)
	#define USE_systimeunlock
	#define EXT_systimeunlock
	#define GET_systimeunlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systimeunlock(p0) 
	#define CHK_systimeunlock  FALSE
	#define EXP_systimeunlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systimeunlock
	#define EXT_systimeunlock
	#define GET_systimeunlock(fl)  CAL_CMGETAPI( "systimeunlock" ) 
	#define CAL_systimeunlock  systimeunlock
	#define CHK_systimeunlock  TRUE
	#define EXP_systimeunlock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimeunlock", (RTS_UINTPTR)systimeunlock, 1, 0x46CB8107, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_systimeunlock
	#define EXT_systimeunlock
	#define GET_systimeunlock(fl)  CAL_CMGETAPI( "systimeunlock" ) 
	#define CAL_systimeunlock  systimeunlock
	#define CHK_systimeunlock  TRUE
	#define EXP_systimeunlock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimeunlock", (RTS_UINTPTR)systimeunlock, 1, 0x46CB8107, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibsystimeunlock
	#define EXT_SysInternalLibsystimeunlock
	#define GET_SysInternalLibsystimeunlock  ERR_OK
	#define CAL_SysInternalLibsystimeunlock  systimeunlock
	#define CHK_SysInternalLibsystimeunlock  TRUE
	#define EXP_SysInternalLibsystimeunlock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimeunlock", (RTS_UINTPTR)systimeunlock, 1, 0x46CB8107, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systimeunlock
	#define EXT_systimeunlock
	#define GET_systimeunlock(fl)  CAL_CMGETAPI( "systimeunlock" ) 
	#define CAL_systimeunlock  systimeunlock
	#define CHK_systimeunlock  TRUE
	#define EXP_systimeunlock  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimeunlock", (RTS_UINTPTR)systimeunlock, 1, 0x46CB8107, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systimeunlock  PFSYSTIMEUNLOCK_IEC pfsystimeunlock;
	#define EXT_systimeunlock  extern PFSYSTIMEUNLOCK_IEC pfsystimeunlock;
	#define GET_systimeunlock(fl)  s_pfCMGetAPI2( "systimeunlock", (RTS_VOID_FCTPTR *)&pfsystimeunlock, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x46CB8107, 0x03050500)
	#define CAL_systimeunlock  pfsystimeunlock
	#define CHK_systimeunlock  (pfsystimeunlock != NULL)
	#define EXP_systimeunlock   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimeunlock", (RTS_UINTPTR)systimeunlock, 1, 0x46CB8107, 0x03050500) 
#endif


/**
 * <description>Function to un-set the actual timestamp for all IEC timers.</description>
 * <result><p>RESULT: Returns always 0</p></result>
 */
typedef struct tagsystimeunset_struct
{
	RTS_IEC_WORD SysTimeUnSet;			/* VAR_OUTPUT */	
} systimeunset_struct;

void CDECL CDECL_EXT systimeunset(systimeunset_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSTIMEUNSET_IEC) (systimeunset_struct *p);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(SYSTIMEUNSET_NOTIMPLEMENTED)
	#define USE_systimeunset
	#define EXT_systimeunset
	#define GET_systimeunset(fl)  ERR_NOTIMPLEMENTED
	#define CAL_systimeunset(p0) 
	#define CHK_systimeunset  FALSE
	#define EXP_systimeunset  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_systimeunset
	#define EXT_systimeunset
	#define GET_systimeunset(fl)  CAL_CMGETAPI( "systimeunset" ) 
	#define CAL_systimeunset  systimeunset
	#define CHK_systimeunset  TRUE
	#define EXP_systimeunset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimeunset", (RTS_UINTPTR)systimeunset, 1, 0xB274556B, 0x03050500) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_systimeunset
	#define EXT_systimeunset
	#define GET_systimeunset(fl)  CAL_CMGETAPI( "systimeunset" ) 
	#define CAL_systimeunset  systimeunset
	#define CHK_systimeunset  TRUE
	#define EXP_systimeunset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimeunset", (RTS_UINTPTR)systimeunset, 1, 0xB274556B, 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibsystimeunset
	#define EXT_SysInternalLibsystimeunset
	#define GET_SysInternalLibsystimeunset  ERR_OK
	#define CAL_SysInternalLibsystimeunset  systimeunset
	#define CHK_SysInternalLibsystimeunset  TRUE
	#define EXP_SysInternalLibsystimeunset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimeunset", (RTS_UINTPTR)systimeunset, 1, 0xB274556B, 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_systimeunset
	#define EXT_systimeunset
	#define GET_systimeunset(fl)  CAL_CMGETAPI( "systimeunset" ) 
	#define CAL_systimeunset  systimeunset
	#define CHK_systimeunset  TRUE
	#define EXP_systimeunset  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimeunset", (RTS_UINTPTR)systimeunset, 1, 0xB274556B, 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_systimeunset  PFSYSTIMEUNSET_IEC pfsystimeunset;
	#define EXT_systimeunset  extern PFSYSTIMEUNSET_IEC pfsystimeunset;
	#define GET_systimeunset(fl)  s_pfCMGetAPI2( "systimeunset", (RTS_VOID_FCTPTR *)&pfsystimeunset, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xB274556B, 0x03050500)
	#define CAL_systimeunset  pfsystimeunset
	#define CHK_systimeunset  (pfsystimeunset != NULL)
	#define EXP_systimeunset   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"systimeunset", (RTS_UINTPTR)systimeunset, 1, 0xB274556B, 0x03050500) 
#endif



/**
 * <description>systimeunlock: Use SysTimeLock.libaray</description>
 * <param name="p" type="IN" range="[VALID_SYSTIMEUNLOCK_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="SysTimeUnlock" type="OUT">Always 0</parampseudo>
 */
RTS_UI16 CDECL SysTimeUnlock(void);
typedef RTS_UI16 (CDECL * PFSYSTIMEUNLOCK) (void);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(SYSTIMEUNLOCK_NOTIMPLEMENTED)
	#define USE_SysTimeUnlock
	#define EXT_SysTimeUnlock
	#define GET_SysTimeUnlock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimeUnlock()  (RTS_UI16)ERR_NOTIMPLEMENTED
	#define CHK_SysTimeUnlock  FALSE
	#define EXP_SysTimeUnlock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimeUnlock
	#define EXT_SysTimeUnlock
	#define GET_SysTimeUnlock(fl)  CAL_CMGETAPI( "SysTimeUnlock" ) 
	#define CAL_SysTimeUnlock  SysTimeUnlock
	#define CHK_SysTimeUnlock  TRUE
	#define EXP_SysTimeUnlock  CAL_CMEXPAPI( "SysTimeUnlock" ) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_SysTimeUnlock
	#define EXT_SysTimeUnlock
	#define GET_SysTimeUnlock(fl)  CAL_CMGETAPI( "SysTimeUnlock" ) 
	#define CAL_SysTimeUnlock  SysTimeUnlock
	#define CHK_SysTimeUnlock  TRUE
	#define EXP_SysTimeUnlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimeUnlock", (RTS_UINTPTR)SysTimeUnlock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibSysTimeUnlock
	#define EXT_SysInternalLibSysTimeUnlock
	#define GET_SysInternalLibSysTimeUnlock  ERR_OK
	#define CAL_SysInternalLibSysTimeUnlock pISysInternalLib->ISysTimeUnlock
	#define CHK_SysInternalLibSysTimeUnlock (pISysInternalLib != NULL)
	#define EXP_SysInternalLibSysTimeUnlock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimeUnlock
	#define EXT_SysTimeUnlock
	#define GET_SysTimeUnlock(fl)  CAL_CMGETAPI( "SysTimeUnlock" ) 
	#define CAL_SysTimeUnlock pISysInternalLib->ISysTimeUnlock
	#define CHK_SysTimeUnlock (pISysInternalLib != NULL)
	#define EXP_SysTimeUnlock  CAL_CMEXPAPI( "SysTimeUnlock" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimeUnlock  PFSYSTIMEUNLOCK pfSysTimeUnlock;
	#define EXT_SysTimeUnlock  extern PFSYSTIMEUNLOCK pfSysTimeUnlock;
	#define GET_SysTimeUnlock(fl)  s_pfCMGetAPI2( "SysTimeUnlock", (RTS_VOID_FCTPTR *)&pfSysTimeUnlock, (fl), 0, 0)
	#define CAL_SysTimeUnlock  pfSysTimeUnlock
	#define CHK_SysTimeUnlock  (pfSysTimeUnlock != NULL)
	#define EXP_SysTimeUnlock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimeUnlock", (RTS_UINTPTR)SysTimeUnlock, 0, 0) 
#endif




/**
 * <description>systimelock: Use SysTimeLock.libaray</description>
 * <param name="p" type="IN" range="[VALID_SYSTIMELOCK_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="ulTick" type="IN" range="[RTS_RANGE_OF_RTS_IEC_TIME]">Tick</parampseudo>
 * <parampseudo name="tTimeout" type="IN" range="[RTS_RANGE_OF_RTS_IEC_TIME]">Timeout</parampseudo>
 * <parampseudo name="SysTimeLock" type="OUT">Always 0</parampseudo>
 */
RTS_UI16 CDECL SysTimeLock(RTS_UI32 ulTick, RTS_UI32 tTimeout);
typedef RTS_UI16 (CDECL * PFSYSTIMELOCK) (RTS_UI32 ulTick, RTS_UI32 tTimeout);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(SYSTIMELOCK_NOTIMPLEMENTED)
	#define USE_SysTimeLock
	#define EXT_SysTimeLock
	#define GET_SysTimeLock(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimeLock(p0,p1)  (RTS_UI16)ERR_NOTIMPLEMENTED
	#define CHK_SysTimeLock  FALSE
	#define EXP_SysTimeLock  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimeLock
	#define EXT_SysTimeLock
	#define GET_SysTimeLock(fl)  CAL_CMGETAPI( "SysTimeLock" ) 
	#define CAL_SysTimeLock  SysTimeLock
	#define CHK_SysTimeLock  TRUE
	#define EXP_SysTimeLock  CAL_CMEXPAPI( "SysTimeLock" ) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_SysTimeLock
	#define EXT_SysTimeLock
	#define GET_SysTimeLock(fl)  CAL_CMGETAPI( "SysTimeLock" ) 
	#define CAL_SysTimeLock  SysTimeLock
	#define CHK_SysTimeLock  TRUE
	#define EXP_SysTimeLock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimeLock", (RTS_UINTPTR)SysTimeLock, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibSysTimeLock
	#define EXT_SysInternalLibSysTimeLock
	#define GET_SysInternalLibSysTimeLock  ERR_OK
	#define CAL_SysInternalLibSysTimeLock pISysInternalLib->ISysTimeLock
	#define CHK_SysInternalLibSysTimeLock (pISysInternalLib != NULL)
	#define EXP_SysInternalLibSysTimeLock  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimeLock
	#define EXT_SysTimeLock
	#define GET_SysTimeLock(fl)  CAL_CMGETAPI( "SysTimeLock" ) 
	#define CAL_SysTimeLock pISysInternalLib->ISysTimeLock
	#define CHK_SysTimeLock (pISysInternalLib != NULL)
	#define EXP_SysTimeLock  CAL_CMEXPAPI( "SysTimeLock" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimeLock  PFSYSTIMELOCK pfSysTimeLock;
	#define EXT_SysTimeLock  extern PFSYSTIMELOCK pfSysTimeLock;
	#define GET_SysTimeLock(fl)  s_pfCMGetAPI2( "SysTimeLock", (RTS_VOID_FCTPTR *)&pfSysTimeLock, (fl), 0, 0)
	#define CAL_SysTimeLock  pfSysTimeLock
	#define CHK_SysTimeLock  (pfSysTimeLock != NULL)
	#define EXP_SysTimeLock  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimeLock", (RTS_UINTPTR)SysTimeLock, 0, 0) 
#endif




/**
 * <description>Function to un-set the actual timestamp for all IEC timers.</description>
 * <param name="p" type="IN" range="[VALID_SYSTIMEUNSET_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="SysTimeUnlock" type="OUT">Always 0</parampseudo>
 */
RTS_UI16 CDECL SysTimeUnSet(void);
typedef RTS_UI16 (CDECL * PFSYSTIMEUNSET) (void);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(SYSTIMEUNSET_NOTIMPLEMENTED)
	#define USE_SysTimeUnSet
	#define EXT_SysTimeUnSet
	#define GET_SysTimeUnSet(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimeUnSet()  (RTS_UI16)ERR_NOTIMPLEMENTED
	#define CHK_SysTimeUnSet  FALSE
	#define EXP_SysTimeUnSet  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimeUnSet
	#define EXT_SysTimeUnSet
	#define GET_SysTimeUnSet(fl)  CAL_CMGETAPI( "SysTimeUnSet" ) 
	#define CAL_SysTimeUnSet  SysTimeUnSet
	#define CHK_SysTimeUnSet  TRUE
	#define EXP_SysTimeUnSet  CAL_CMEXPAPI( "SysTimeUnSet" ) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_SysTimeUnSet
	#define EXT_SysTimeUnSet
	#define GET_SysTimeUnSet(fl)  CAL_CMGETAPI( "SysTimeUnSet" ) 
	#define CAL_SysTimeUnSet  SysTimeUnSet
	#define CHK_SysTimeUnSet  TRUE
	#define EXP_SysTimeUnSet  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimeUnSet", (RTS_UINTPTR)SysTimeUnSet, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibSysTimeUnSet
	#define EXT_SysInternalLibSysTimeUnSet
	#define GET_SysInternalLibSysTimeUnSet  ERR_OK
	#define CAL_SysInternalLibSysTimeUnSet pISysInternalLib->ISysTimeUnSet
	#define CHK_SysInternalLibSysTimeUnSet (pISysInternalLib != NULL)
	#define EXP_SysInternalLibSysTimeUnSet  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimeUnSet
	#define EXT_SysTimeUnSet
	#define GET_SysTimeUnSet(fl)  CAL_CMGETAPI( "SysTimeUnSet" ) 
	#define CAL_SysTimeUnSet pISysInternalLib->ISysTimeUnSet
	#define CHK_SysTimeUnSet (pISysInternalLib != NULL)
	#define EXP_SysTimeUnSet  CAL_CMEXPAPI( "SysTimeUnSet" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimeUnSet  PFSYSTIMEUNSET pfSysTimeUnSet;
	#define EXT_SysTimeUnSet  extern PFSYSTIMEUNSET pfSysTimeUnSet;
	#define GET_SysTimeUnSet(fl)  s_pfCMGetAPI2( "SysTimeUnSet", (RTS_VOID_FCTPTR *)&pfSysTimeUnSet, (fl), 0, 0)
	#define CAL_SysTimeUnSet  pfSysTimeUnSet
	#define CHK_SysTimeUnSet  (pfSysTimeUnSet != NULL)
	#define EXP_SysTimeUnSet  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimeUnSet", (RTS_UINTPTR)SysTimeUnSet, 0, 0) 
#endif




/**
 * <description>Function to set the actual timestamp for all IEC timers. Differnt to SysTimeLock, the timer continues</description>
 * <param name="p" type="IN" range="[VALID_SYSTIMESET_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="ulTick" type="IN" range="[RTS_RANGE_OF_RTS_IEC_TIME]">Tick</parampseudo>
 * <parampseudo name="tTimeout" type="IN" range="[RTS_RANGE_OF_RTS_IEC_TIME]">Timeout</parampseudo>
 * <parampseudo name="SysTimeSet" type="OUT">Always 0</parampseudo>
 */
RTS_UI16 CDECL SysTimeSet(RTS_UI32 ulTick, RTS_UI32 tTimeout);
typedef RTS_UI16 (CDECL * PFSYSTIMESET) (RTS_UI32 ulTick, RTS_UI32 tTimeout);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(SYSTIMESET_NOTIMPLEMENTED)
	#define USE_SysTimeSet
	#define EXT_SysTimeSet
	#define GET_SysTimeSet(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysTimeSet(p0,p1)  (RTS_UI16)ERR_NOTIMPLEMENTED
	#define CHK_SysTimeSet  FALSE
	#define EXP_SysTimeSet  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysTimeSet
	#define EXT_SysTimeSet
	#define GET_SysTimeSet(fl)  CAL_CMGETAPI( "SysTimeSet" ) 
	#define CAL_SysTimeSet  SysTimeSet
	#define CHK_SysTimeSet  TRUE
	#define EXP_SysTimeSet  CAL_CMEXPAPI( "SysTimeSet" ) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_SysTimeSet
	#define EXT_SysTimeSet
	#define GET_SysTimeSet(fl)  CAL_CMGETAPI( "SysTimeSet" ) 
	#define CAL_SysTimeSet  SysTimeSet
	#define CHK_SysTimeSet  TRUE
	#define EXP_SysTimeSet  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimeSet", (RTS_UINTPTR)SysTimeSet, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibSysTimeSet
	#define EXT_SysInternalLibSysTimeSet
	#define GET_SysInternalLibSysTimeSet  ERR_OK
	#define CAL_SysInternalLibSysTimeSet pISysInternalLib->ISysTimeSet
	#define CHK_SysInternalLibSysTimeSet (pISysInternalLib != NULL)
	#define EXP_SysInternalLibSysTimeSet  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysTimeSet
	#define EXT_SysTimeSet
	#define GET_SysTimeSet(fl)  CAL_CMGETAPI( "SysTimeSet" ) 
	#define CAL_SysTimeSet pISysInternalLib->ISysTimeSet
	#define CHK_SysTimeSet (pISysInternalLib != NULL)
	#define EXP_SysTimeSet  CAL_CMEXPAPI( "SysTimeSet" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysTimeSet  PFSYSTIMESET pfSysTimeSet;
	#define EXT_SysTimeSet  extern PFSYSTIMESET pfSysTimeSet;
	#define GET_SysTimeSet(fl)  s_pfCMGetAPI2( "SysTimeSet", (RTS_VOID_FCTPTR *)&pfSysTimeSet, (fl), 0, 0)
	#define CAL_SysTimeSet  pfSysTimeSet
	#define CHK_SysTimeSet  (pfSysTimeSet != NULL)
	#define EXP_SysTimeSet  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysTimeSet", (RTS_UINTPTR)SysTimeSet, 0, 0) 
#endif





/**
 * <description>Returns the size in bytes, of the specified IEC data type.</description>
 * <param name="tc" type="IN" range="[0..TYPE3_MAX_TYPE]">Pointer to the input structure</param>
 * <result>Size in Bytes of Datatype, or 0 if unspecified</result>
 */
unsigned int CDECL SysGetTypeSize(TypeClass3 tc);
typedef unsigned int (CDECL * PFSYSGETTYPESIZE) (TypeClass3 tc);
#if defined(SYSINTERNALLIB_NOTIMPLEMENTED) || defined(SYSGETTYPESIZE_NOTIMPLEMENTED)
	#define USE_SysGetTypeSize
	#define EXT_SysGetTypeSize
	#define GET_SysGetTypeSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysGetTypeSize(p0)  (unsigned int)ERR_NOTIMPLEMENTED
	#define CHK_SysGetTypeSize  FALSE
	#define EXP_SysGetTypeSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysGetTypeSize
	#define EXT_SysGetTypeSize
	#define GET_SysGetTypeSize(fl)  CAL_CMGETAPI( "SysGetTypeSize" ) 
	#define CAL_SysGetTypeSize  SysGetTypeSize
	#define CHK_SysGetTypeSize  TRUE
	#define EXP_SysGetTypeSize  CAL_CMEXPAPI( "SysGetTypeSize" ) 
#elif defined(MIXED_LINK) && !defined(SYSINTERNALLIB_EXTERNAL)
	#define USE_SysGetTypeSize
	#define EXT_SysGetTypeSize
	#define GET_SysGetTypeSize(fl)  CAL_CMGETAPI( "SysGetTypeSize" ) 
	#define CAL_SysGetTypeSize  SysGetTypeSize
	#define CHK_SysGetTypeSize  TRUE
	#define EXP_SysGetTypeSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGetTypeSize", (RTS_UINTPTR)SysGetTypeSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysInternalLibSysGetTypeSize
	#define EXT_SysInternalLibSysGetTypeSize
	#define GET_SysInternalLibSysGetTypeSize  ERR_OK
	#define CAL_SysInternalLibSysGetTypeSize pISysInternalLib->ISysGetTypeSize
	#define CHK_SysInternalLibSysGetTypeSize (pISysInternalLib != NULL)
	#define EXP_SysInternalLibSysGetTypeSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysGetTypeSize
	#define EXT_SysGetTypeSize
	#define GET_SysGetTypeSize(fl)  CAL_CMGETAPI( "SysGetTypeSize" ) 
	#define CAL_SysGetTypeSize pISysInternalLib->ISysGetTypeSize
	#define CHK_SysGetTypeSize (pISysInternalLib != NULL)
	#define EXP_SysGetTypeSize  CAL_CMEXPAPI( "SysGetTypeSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysGetTypeSize  PFSYSGETTYPESIZE pfSysGetTypeSize;
	#define EXT_SysGetTypeSize  extern PFSYSGETTYPESIZE pfSysGetTypeSize;
	#define GET_SysGetTypeSize(fl)  s_pfCMGetAPI2( "SysGetTypeSize", (RTS_VOID_FCTPTR *)&pfSysGetTypeSize, (fl), 0, 0)
	#define CAL_SysGetTypeSize  pfSysGetTypeSize
	#define CHK_SysGetTypeSize  (pfSysGetTypeSize != NULL)
	#define EXP_SysGetTypeSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysGetTypeSize", (RTS_UINTPTR)SysGetTypeSize, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSTIMEUNLOCK ISysTimeUnlock;
 	PFSYSTIMELOCK ISysTimeLock;
 	PFSYSTIMEUNSET ISysTimeUnSet;
 	PFSYSTIMESET ISysTimeSet;
 	PFSYSGETTYPESIZE ISysGetTypeSize;
 } ISysInternalLib_C;

#ifdef CPLUSPLUS
class ISysInternalLib : public IBase
{
	public:
		virtual RTS_UI16 CDECL ISysTimeUnlock(void) =0;
		virtual RTS_UI16 CDECL ISysTimeLock(RTS_UI32 ulTick, RTS_UI32 tTimeout) =0;
		virtual RTS_UI16 CDECL ISysTimeUnSet(void) =0;
		virtual RTS_UI16 CDECL ISysTimeSet(RTS_UI32 ulTick, RTS_UI32 tTimeout) =0;
		virtual unsigned int CDECL ISysGetTypeSize(TypeClass3 tc) =0;
};
	#ifndef ITF_SysInternalLib
		#define ITF_SysInternalLib static ISysInternalLib *pISysInternalLib = NULL;
	#endif
	#define EXTITF_SysInternalLib
#else	/*CPLUSPLUS*/
	typedef ISysInternalLib_C		ISysInternalLib;
	#ifndef ITF_SysInternalLib
		#define ITF_SysInternalLib
	#endif
	#define EXTITF_SysInternalLib
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSINTERNALLIBITF_H_*/
