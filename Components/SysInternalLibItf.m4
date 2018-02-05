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

SET_INTERFACE_NAME(`SysInternalLib')

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
DEF_API(`void',`CDECL',`__memcopy',`(__memcopy_struct* p)',1)

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
DEF_API(`void',`CDECL',`__stringcompare',`(__stringcompare_struct* p)',1)

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
DEF_API(`void',`CDECL',`__wstringcompare',`(__wstringcompare_struct* p)',1)

/**
 * <description>This function determines if two operands equal. The inputs are 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if the input values are equal, 0 if they are not equal. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__eq',`(real_cmp_struct* p)',1)

/**
 * <description>This function determines if two operands are not equal. The inputs are 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if the input values are not equal, 0 if they are equal. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__ne',`(real_cmp_struct* p)',1)

/**
 * <description>This function determines if an operand is lower than another. The inputs are 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is lower than in2, 0 if in1 is not lower than in2. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__lt',`(real_cmp_struct* p)',1)

/**
 * <description>This function determines if an operand is lower or equal than another. The inputs are 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is lower or equal than in2, 0 if in1 is not lower or equal than in2. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__le',`(real_cmp_struct* p)',1)

/**
 * <description>This function determines if an operand is greater than another. The inputs are 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is greater than in2, 0 if in1 is not greater than in2. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__gt',`(real_cmp_struct* p)',1)

/**
 * <description>This function determines if an operand is greater or equal than another. The inputs are 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is greater or equal than in2, 0 if in1 is not greater or equal than in2. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__ge',`(real_cmp_struct* p)',1)

/**
 * <description>This function makes an addition of two 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">First summand</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Second summand</parampseudo>
 * <parampseudo name="bNegInfinity" type="OUT">The return value is -infinity</parampseudo>
 * <parampseudo name="bInfinity" type="OUT">The return value is infinity</parampseudo>
 * <parampseudo name="out" type="OUT">Sum of the two input values as 32-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__add',`(real_2op_struct* p)',1)

/**
 * <description>This function makes a subtraction of one variable from another one. The inputs are 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Minuend</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Subtrahend</parampseudo>
 * <parampseudo name="bNegInfinity" type="OUT">The return value is -infinity</parampseudo>
 * <parampseudo name="bInfinity" type="OUT">The return value is infinity</parampseudo>
 * <parampseudo name="out" type="OUT">Difference of the two input values as 32-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__sub',`(real_2op_struct* p)',1)

/**
 * <description>This function makes a multiplication of two variables. The inputs are 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">First factor</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Second factor</parampseudo>
 * <parampseudo name="bNegInfinity" type="OUT">The return value is -infinity</parampseudo>
 * <parampseudo name="bInfinity" type="OUT">The return value is infinity</parampseudo>
 * <parampseudo name="out" type="OUT">Product of the two input values as 32-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__mul',`(real_2op_struct* p)',1)

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
DEF_API(`void',`CDECL',`real32__div',`(real_2op_struct* p)',1)

/**
 * <description>This function builds the minimum of two variables. The inputs are 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">The lesser of the two values as 32-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__min',`(real_2op_struct* p)',1)

/**
 * <description>This function builds the maximum of two variables. The inputs are 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">The greater of the two values as 32-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__max',`(real_2op_struct* p)',1)

/**
 * <description>This function limits an input value to a lower and an upper bound. The inputs are 32-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_REAL_3OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Lower bound</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input value</parampseudo>
 * <parampseudo name="in3" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Upper bound</parampseudo>
 * <parampseudo name="out" type="OUT">in2 if in2 is in the range between in1 and in3, in1 if in2 is lower than in1, in3 if in2 is greater than in3. The result is a 32-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__limit',`(real_3op_struct* p)',1)

/**
 * <description>This function converts a 32-bit real value to a 32-bit integer value.</description>
 * <param name="p" type="IN" range="[VALID_REAL_TRUNC_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[ANY_MIN, ANY_MID, ANY_MAX]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The whole number portion of the input as 32-bit integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__trunc',`(real_trunc_struct* p)',1)

/**
 * <description>
 * <p>This function calculates the tangent of a 32-bit real value.</p>
 * <p>The behaviour for input values that are multiples of PI_HALF might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_REAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_REAL)-PI_HALF,(RTS_IEC_REAL)-PI_HALF+MIN_DELTA..(RTS_IEC_REAL)0,(RTS_IEC_REAL)0..(RTS_IEC_REAL)PI_HALF-MIN_DELTA,(RTS_IEC_REAL)PI_HALF]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The tangent of the input as 32-bit real value or NaN.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__tan',`(real_1op_struct* p)',1)

/**
 * <description>This function calculates the sine of a 32-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_REAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_REAL)-PI,(RTS_IEC_REAL)-PI_HALF,0,(RTS_IEC_REAL)PI_HALF,(RTS_IEC_REAL)PI]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The sine of the input as 32-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__sin',`(real_1op_struct* p)',1)

/**
 * <description>This function calculates the cosine of a 32-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_REAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_REAL)-PI,(RTS_IEC_REAL)-PI_HALF,0,(RTS_IEC_REAL)PI_HALF,(RTS_IEC_REAL)PI]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The cosine of the input as 32-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__cos',`(real_1op_struct* p)',1)

/**
 * <description>This function calculates the arc tangent (inverse function of tangent) of a 32-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_REAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The arc tangent of the input as 32-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__atan',`(real_1op_struct* p)',1)

/**
 * <description>
 * <p>This function calculates the arc sine (inverse function of sine) of a 32-bit real value.</p>
 * <p>The behaviour for input values &lt; -1.0 and &gt; 1.0 might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_REAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_REAL)-1.01,(RTS_IEC_REAL)-1.0..(RTS_IEC_REAL)1.0,(RTS_IEC_REAL)1.01]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The arc sine of the input as 32-bit real value or NaN.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__asin',`(real_1op_struct* p)',1)

/**
 * <description>
 * <p>This function calculates the arc cosine (inverse function of cosine) of a 32-bit real value.</p>
 * <p>The behaviour for input values &lt; -1.0 and &gt; 1.0 might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_REAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_REAL)-1.01,(RTS_IEC_REAL)-1.0..(RTS_IEC_REAL)1.0,(RTS_IEC_REAL)1.01]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The arc cosine of the input as 32-bit real value or NaN.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__acos',`(real_1op_struct* p)',1)

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
DEF_API(`void',`CDECL',`real32__ln',`(real_1op_struct* p)',1)

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
DEF_API(`void',`CDECL',`real32__log',`(real_1op_struct* p)',1)

/**
 * <description>This function calculates the exponential function of a 32-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_REAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input</parampseudo>
 * <parampseudo name="bInfinity" type="OUT">The return value is infinity</parampseudo>
 * <parampseudo name="out" type="OUT">The exponential function of the input as 32-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__exp',`(real_1op_struct* p)',1)

/**
 * <description>
 * <p>This function calculates the square root of a 32-bit real value.</p>
 * <p>The behaviour for input values &lt; 0.0 might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_REAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_REAL)-0.01,(RTS_IEC_REAL)0.0..RTS_IEC_REAL_MAX]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The square root of the input as 32-bit real value or NaN.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__sqrt',`(real_1op_struct* p)',1)

/**
 * <description>This function calculates the absolute value of a 32-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_REAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[RTS_RANGE_OF_RTS_IEC_REAL]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The absolute value of the input as 32-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__abs',`(real_1op_struct* p)',1)

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
DEF_API(`void',`CDECL',`real32__expt',`(real_2op_struct* p)',1)

/**
 * <description>This function determines if two operands equal. The inputs are 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if the input values are equal, 0 if they are not equal. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__eq',`(lreal_cmp_struct* p)',1,0,0,1)

/**
 * <description>This function determines if two operands are not equal. The inputs are 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if the input values are not equal, 0 if they are equal. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__ne',`(lreal_cmp_struct* p)',1,0,0,1)

/**
 * <description>This function determines if an operand is lower than another. The inputs are 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is lower than in2, 0 if in1 is not lower than in2. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__lt',`(lreal_cmp_struct* p)',1,0,0,1)

/**
 * <description>This function determines if an operand is lower or equal than another. The inputs are 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is lower or equal than in2, 0 if in1 is not lower or equal than in2. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__le',`(lreal_cmp_struct* p)',1,0,0,1)

/**
 * <description>This function determines if an operand is greater than another. The inputs are 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is greater than in2, 0 if in1 is not greater than in2. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__gt',`(lreal_cmp_struct* p)',1,0,0,1)

/**
 * <description>This function determines if an operand is greater or equal than another. The inputs are 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is greater or equal than in2, 0 if in1 is not greater or equal than in2. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__ge',`(lreal_cmp_struct* p)',1,0,0,1)

/**
 * <description>This function makes an addition of two 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">First summand</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Second summand</parampseudo>
 * <parampseudo name="bNegInfinity" type="OUT">The return value is -infinity</parampseudo>
 * <parampseudo name="bInfinity" type="OUT">The return value is infinity</parampseudo>
 * <parampseudo name="out" type="OUT">Sum of the two input values as 64-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__add',`(lreal_2op_struct* p)',1,0,0,1)

/**
 * <description>This function makes a subtraction of one variable from another one. The inputs are 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Minuend</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Subtrahend</parampseudo>
 * <parampseudo name="bNegInfinity" type="OUT">The return value is -infinity</parampseudo>
 * <parampseudo name="bInfinity" type="OUT">The return value is infinity</parampseudo>
 * <parampseudo name="out" type="OUT">Difference of the two input values as 64-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__sub',`(lreal_2op_struct* p)',1,0,0,1)

/**
 * <description>This function makes a multiplication of two variables. The inputs are 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">First factor</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Second factor</parampseudo>
 * <parampseudo name="bNegInfinity" type="OUT">The return value is -infinity</parampseudo>
 * <parampseudo name="bInfinity" type="OUT">The return value is infinity</parampseudo>
 * <parampseudo name="out" type="OUT">Product of the two input values as 64-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__mul',`(lreal_2op_struct* p)',1,0,0,1)

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
DEF_API(`void',`CDECL',`real64__div',`(lreal_2op_struct* p)',1,0,0,1)

/**
 * <description>This function builds the minimum of two variables. The inputs are 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">The lesser of the two values as 64-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__min',`(lreal_2op_struct* p)',1,0,0,1)

/**
 * <description>This function builds the maximum of two variables. The inputs are 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">The greater of the two values as 64-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__max',`(lreal_2op_struct* p)',1,0,0,1)

/**
 * <description>This function limits an input value to a lower and an upper bound. The inputs are 64-bit real values.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_3OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Lower bound</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input value</parampseudo>
 * <parampseudo name="in3" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Upper bound</parampseudo>
 * <parampseudo name="out" type="OUT">in2 if in2 is in the range between in1 and in3, in1 if in2 is lower than in1, in3 if in2 is greater than in3. The result is a 64-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__limit',`(lreal_3op_struct* p)',1,0,0,1)

/**
 * <description>This function converts a 64-bit real value to a 64-bit integer value.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_TRUNC_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[ANY_MIN, ANY_MID, ANY_MAX]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The whole number portion of the input as 64-bit integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__trunc',`(lreal_trunc_struct* p)',1,0,0,1)

/**
 * <description>
 * <p>This function calculates the tangent of a 64-bit real value.</p>
 * <p>The behaviour for input values that are multiples of PI_HALF might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_LREAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_LREAL)-PI_HALF,(RTS_IEC_LREAL)-PI_HALF+MIN_DELTA..(RTS_IEC_LREAL)0,(RTS_IEC_LREAL)0..(RTS_IEC_LREAL)PI_HALF-MIN_DELTA,(RTS_IEC_LREAL)PI_HALF]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The tangent of the input as 64-bit real value or NaN.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__tan',`(lreal_1op_struct* p)',1,0,0,1)

/**
 * <description>This function calculates the sine of a 64-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_LREAL)-PI,(RTS_IEC_LREAL)-PI_HALF,0,(RTS_IEC_LREAL)PI_HALF,(RTS_IEC_LREAL)PI]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The sine of the input as 64-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__sin',`(lreal_1op_struct* p)',1,0,0,1)

/**
 * <description>This function calculates the cosine of a 64-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_LREAL)-PI,(RTS_IEC_LREAL)-PI_HALF,0,(RTS_IEC_LREAL)PI_HALF,(RTS_IEC_LREAL)PI]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The cosine of the input as 64-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__cos',`(lreal_1op_struct* p)',1,0,0,1)

/**
 * <description>This function calculates the arc tangent (inverse function of tangent) of a 64-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The arc tangent of the input as 64-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__atan',`(lreal_1op_struct* p)',1,0,0,1)

/**
 * <description>
 * <p>This function calculates the arc sine (inverse function of sine) of a 64-bit real value.</p>
 * <p>The behaviour for input values &lt; -1.0 and &gt; 1.0 might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_LREAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_LREAL)-1.01,(RTS_IEC_LREAL)-1.0..(RTS_IEC_LREAL)1.0,(RTS_IEC_LREAL)1.01]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The arc sine of the input as 64-bit real value or NaN.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__asin',`(lreal_1op_struct* p)',1,0,0,1)

/**
 * <description>
 * <p>This function calculates the arc cosine (inverse function of cosine) of a 64-bit real value.</p>
 * <p>The behaviour for input values &lt; -1.0 and &gt; 1.0 might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_LREAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_LREAL)-1.01,(RTS_IEC_LREAL)-1.0..(RTS_IEC_LREAL)1.0,(RTS_IEC_LREAL)1.01]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The arc cosine of the input as 64-bit real value or NaN.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__acos',`(lreal_1op_struct* p)',1,0,0,1)

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
DEF_API(`void',`CDECL',`real64__ln',`(lreal_1op_struct* p)',1,0,0,1)

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
DEF_API(`void',`CDECL',`real64__log',`(lreal_1op_struct* p)',1,0,0,1)

/**
 * <description>This function calculates the exponential function of a 64-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input</parampseudo>
 * <parampseudo name="bInfinity" type="OUT">The return value is infinity</parampseudo>
 * <parampseudo name="out" type="OUT">The exponential function of the input as 64-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__exp',`(lreal_1op_struct* p)',1,0,0,1)

/**
 * <description>
 * <p>This function calculates the square root of a 64-bit real value.</p>
 * <p>The behaviour for input values &lt; 0.0 might be platform dependent.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_LREAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[(RTS_IEC_LREAL)-0.01,(RTS_IEC_LREAL)0.0..RTS_IEC_LREAL_MAX]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The square root of the input as 64-bit real value or NaN.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__sqrt',`(lreal_1op_struct* p)',1,0,0,1)

/**
 * <description>This function calculates the absolute value of a 64-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_LREAL_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LREAL]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The absolute value of the input as 64-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__abs',`(lreal_1op_struct* p)',1,0,0,1)

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
DEF_API(`void',`CDECL',`real64__expt',`(lreal_2op_struct* p)',1,0,0,1)

/**
 * <description>This function makes an addition of two 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">First summand</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Second summand</parampseudo>
 * <parampseudo name="out" type="OUT">Sum of the two input values as 64-bit integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`int64__add',`(lint_2op_struct* p)',1,0,0,1)

/**
 * <description>This function makes a subtraction of one variable from another one. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Minuend</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Subtrahend</parampseudo>
 * <parampseudo name="out" type="OUT">Difference of the two input values as 64-bit integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`int64__sub',`(lint_2op_struct* p)',1,0,0,1)

/**
 * <description>This function makes a multiplication of two variables. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">First factor</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Second factor</parampseudo>
 * <parampseudo name="out" type="OUT">Product of the two input values as 64-bit integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`int64__mul',`(lint_2op_struct* p)',1,0,0,1)

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
DEF_API(`void',`CDECL',`int64__div',`(lint_2op_struct* p)',1,0,0,1)

/**
 * <description>This function calculates the remainder of division of one variable by another. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Dividend</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Divisor</parampseudo>
 * <parampseudo name="out" type="OUT">Remainder of division of the two input values as 64-bit integer value, or 0 if the divisor is 0.</parampseudo>
 */
DEF_API(`void',`CDECL',`int64__mod',`(lint_2op_struct* p)',1,0,0,1)

/**
 * <description>This function calculates the absolute value of a 64-bit integer value.</description>
 * <param name="p" type="IN" range="[VALID_LINT_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[RTS_IEC_LINT_MIN,RTS_IEC_LINT_MIN+1,0,RTS_IEC_LINT_MAX/2,RTS_IEC_LINT_MAX]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The absolute value of the input as 64-bit integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`int64__abs',`(lint_1op_struct* p)',1,0,0,1)

/**
 * <description>This function builds the minimum of two variables. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">The lesser of the two values as 64-bit integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`int64__min',`(lint_2op_struct* p)',1,0,0,1)

/**
 * <description>This function builds the maximum of two variables. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">The greater of the two values as 64-bit integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`int64__max',`(lint_2op_struct* p)',1,0,0,1)

/**
 * <description>This function limits an input value to a lower and an upper bound. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_3OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Lower bound</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input value</parampseudo>
 * <parampseudo name="in3" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Upper bound</parampseudo>
 * <parampseudo name="out" type="OUT">in2 if in2 is in the range between in1 and in3, in1 if in2 is lower than in1, in3 if in2 is greater than in3. The result is a 64-bit integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`int64__limit',`(lint_3op_struct* p)',1,0,0,1)

/**
 * <description>This function determines if two operands equal. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if the input values are equal, 0 if they are not equal. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`int64__eq',`(lint_cmp_struct* p)',1,0,0,1)

/**
 * <description>This function determines if two operands are not equal. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if the input values are not equal, 0 if they are equal. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`int64__ne',`(lint_cmp_struct* p)',1,0,0,1)

/**
 * <description>This function determines if an operand is lower than another. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is lower than in2, 0 if in1 is not lower than in2. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`int64__lt',`(lint_cmp_struct* p)',1,0,0,1)

/**
 * <description>This function determines if an operand is lower or equal than another. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is lower or equal than in2, 0 if in1 is not lower or equal than in2. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`int64__le',`(lint_cmp_struct* p)',1,0,0,1)

/**
 * <description>This function determines if an operand is greater than another. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is greater than in2, 0 if in1 is not greater than in2. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`int64__gt',`(lint_cmp_struct* p)',1,0,0,1)

/**
 * <description>This function determines if an operand is greater or equal than another. The inputs are 64-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_LINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_LINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is greater or equal than in2, 0 if in1 is not greater or equal than in2. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`int64__ge',`(lint_cmp_struct* p)',1,0,0,1)

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
DEF_API(`void',`CDECL',`int64__shr',`(lint_shift_struct* p)',1,0,0,1)

/**
 * <description>This function makes an addition of two 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">First summand</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Second summand</parampseudo>
 * <parampseudo name="out" type="OUT">Sum of the two input values as 64-bit unsigned integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`uint64__add',`(ulint_2op_struct* p)',1,0,0,1)

/**
 * <description>This function makes a subtraction of one variable from another one. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Minuend</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Subtrahend</parampseudo>
 * <parampseudo name="out" type="OUT">Difference of the two input values as 64-bit unsigned integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`uint64__sub',`(ulint_2op_struct* p)',1,0,0,1)

/**
 * <description>This function makes a multiplication of two variables. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">First factor</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Second factor</parampseudo>
 * <parampseudo name="out" type="OUT">Product of the two input values as 64-bit unsigned integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`uint64__mul',`(ulint_2op_struct* p)',1,0,0,1)

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
DEF_API(`void',`CDECL',`uint64__div',`(ulint_2op_struct* p)',1,0,0,1)

/**
 * <description>This function calculates the remainder of division of one variable by another. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Dividend</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Divisor</parampseudo>
 * <parampseudo name="out" type="OUT">Remainder of division of the two input values as 64-bit unsigned integer value, or 0 if the divisor is 0.</parampseudo>
 */
DEF_API(`void',`CDECL',`uint64__mod',`(ulint_2op_struct* p)',1,0,0,1)

/**
 * <description>This function builds the minimum of two variables. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">The lesser of the two values as 64-bit unsigned integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`uint64__min',`(ulint_2op_struct* p)',1,0,0,1)

/**
 * <description>This function builds the maximum of two variables. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">The greater of the two values as 64-bit unsigned integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`uint64__max',`(ulint_2op_struct* p)',1,0,0,1)

/**
 * <description>This function limits an input value to a lower and an upper bound. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_3OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Lower bound</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input value</parampseudo>
 * <parampseudo name="in3" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Upper bound</parampseudo>
 * <parampseudo name="out" type="OUT">in2 if in2 is in the range between in1 and in3, in1 if in2 is lower than in1, in3 if in2 is greater than in3. The result is a 64-bit unsigned integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`uint64__limit',`(ulint_3op_struct* p)',1,0,0,1)

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
DEF_API(`void',`CDECL',`uint64__ror',`(ulint_shift_struct* p)',1,0,0,1)

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
DEF_API(`void',`CDECL',`uint64__rol',`(ulint_shift_struct* p)',1,0,0,1)

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
DEF_API(`void',`CDECL',`uint64__shl',`(ulint_shift_struct* p)',1,0,0,1)

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
DEF_API(`void',`CDECL',`uint64__shr',`(ulint_shift_struct* p)',1,0,0,1)

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
DEF_API(`void',`CDECL',`uint64__and',`(ulint_2op_struct* p)',1,0,0,1)

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
DEF_API(`void',`CDECL',`uint64__or',`(ulint_2op_struct* p)',1,0,0,1)

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
DEF_API(`void',`CDECL',`uint64__xor',`(ulint_2op_struct* p)',1,0,0,1)

/**
 * <description>
 * <p>This function makes a bitwise NOT of a 64-bit unsigned integer value.</p>
 * <p>The resulting bit will be 1, if the corresponding input bit is 0 and vice versa.</p>
 * </description>
 * <param name="p" type="IN" range="[VALID_ULINT_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">Bitwise NOT of the input value as 64-bit unsigned integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`uint64__not',`(ulint_1op_struct* p)',1,0,0,1)

/**
 * <description>This function determines if two operands equal. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if the input values are equal, 0 if they are not equal. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`uint64__eq',`(ulint_cmp_struct* p)',1,0,0,1)

/**
 * <description>This function determines if two operands are not equal. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if the input values are not equal, 0 if they are equal. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`uint64__ne',`(ulint_cmp_struct* p)',1,0,0,1)

/**
 * <description>This function determines if an operand is lower than another. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is lower than in2, 0 if in1 is not lower than in2. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`uint64__lt',`(ulint_cmp_struct* p)',1,0,0,1)

/**
 * <description>This function determines if an operand is lower or equal than another. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is lower or equal than in2, 0 if in1 is not lower or equal than in2. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`uint64__le',`(ulint_cmp_struct* p)',1,0,0,1)

/**
 * <description>This function determines if an operand is greater than another. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is greater than in2, 0 if in1 is not greater than in2. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`uint64__gt',`(ulint_cmp_struct* p)',1,0,0,1)

/**
 * <description>This function determines if an operand is greater or equal than another. The inputs are 64-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_ULINT_CMP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 1</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_ULINT]">Input 2</parampseudo>
 * <parampseudo name="out" type="OUT">1 if in1 is greater or equal than in2, 0 if in1 is not greater or equal than in2. The result is a 8-bit short integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`uint64__ge',`(ulint_cmp_struct* p)',1,0,0,1)

/**
 * <description>This function makes a multiplication of two variables. The inputs are 32-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_DINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_DINT]">First factor</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_DINT]">Second factor</parampseudo>
 * <parampseudo name="out" type="OUT">Product of the two input values as 32-bit integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`int32__mul',`(dint_2op_struct* p)',1)

/**
 * <description>This function makes a multiplication of two variables. The inputs are 32-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_UDINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UDINT]">First factor</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UDINT]">Second factor</parampseudo>
 * <parampseudo name="out" type="OUT">Product of the two input values as 32-bit unsigned integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`uint32__mul',`(udint_2op_struct* p)',1)

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
DEF_API(`void',`CDECL',`int32__div',`(dint_2op_struct* p)',1)

/**
 * <description>This function calculates the remainder of division of one variable by another. The inputs are 32-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_DINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_DINT]">Dividend</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_DINT]">Divisor</parampseudo>
 * <parampseudo name="out" type="OUT">Remainder of division of the two input values as 32-bit integer value, or 0 if the divisor is 0.</parampseudo>
 */
DEF_API(`void',`CDECL',`int32__mod',`(dint_2op_struct* p)',1)

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
DEF_API(`void',`CDECL',`uint32__div',`(udint_2op_struct* p)',1)

/**
 * <description>This function calculates the remainder of division of one variable by another. The inputs are 32-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_UDINT_2OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UDINT]">Dividend</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UDINT]">Divisor</parampseudo>
 * <parampseudo name="out" type="OUT">Remainder of division of the two input values as 32-bit unsigned integer value, or 0 if the divisor is 0.</parampseudo>
 */
DEF_API(`void',`CDECL',`uint32__mod',`(udint_2op_struct* p)',1)

/**
 * <description>This function calculates the absolute value of a 32-bit integer value.</description>
 * <param name="p" type="IN" range="[VALID_DINT_1OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[RTS_IEC_DINT_MIN,RTS_IEC_DINT_MIN+1,0,RTS_IEC_DINT_MAX/2,RTS_IEC_DINT_MAX]">Input</parampseudo>
 * <parampseudo name="out" type="OUT">The absolute value of the input as 32-bit integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`int32__abs',`(dint_1op_struct* p)',1)

/**
 * <description>This function limits an input value to a lower and an upper bound. The inputs are 32-bit unsigned integer values.</description>
 * <param name="p" type="IN" range="[VALID_UDINT_3OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UDINT]">Lower bound</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UDINT]">Input value</parampseudo>
 * <parampseudo name="in3" type="IN" range="[RTS_RANGE_OF_RTS_IEC_UDINT]">Upper bound</parampseudo>
 * <parampseudo name="out" type="OUT">in2 if in2 is in the range between in1 and in3, in1 if in2 is lower than in1, in3 if in2 is greater than in3. The result is a 32-bit unsigned integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`uint32__limit',`(udint_3op_struct* p)',1)

/**
 * <description>This function limits an input value to a lower and an upper bound. The inputs are 32-bit integer values.</description>
 * <param name="p" type="IN" range="[VALID_DINT_3OP_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in1" type="IN" range="[RTS_RANGE_OF_RTS_IEC_DINT]">Lower bound</parampseudo>
 * <parampseudo name="in2" type="IN" range="[RTS_RANGE_OF_RTS_IEC_DINT]">Input value</parampseudo>
 * <parampseudo name="in3" type="IN" range="[RTS_RANGE_OF_RTS_IEC_DINT]">Upper bound</parampseudo>
 * <parampseudo name="out" type="OUT">in2 if in2 is in the range between in1 and in3, in1 if in2 is lower than in1, in3 if in2 is greater than in3. The result is a 32-bit integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`int32__limit',`(dint_3op_struct* p)',1)

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
DEF_API(`void',`CDECL',`uint32__rol',`(udint_shift_struct* p)',1)

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
DEF_API(`void',`CDECL',`uint32__ror',`(udint_shift_struct* p)',1)

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
DEF_API(`void',`CDECL',`uint32__shl',`(udint_shift_struct* p)',1)

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
DEF_API(`void',`CDECL',`uint32__shr',`(udint_shift_struct* p)',1)

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
DEF_API(`void',`CDECL',`int32__shr',`(dint_shift_struct* p)',1)

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
DEF_API(`void',`CDECL',`any32__to__int64',`(any32_to_int64_struct* p)',1,0,0,1)

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
DEF_API(`void',`CDECL',`int64__to__any32',`(int64_to_any32_struct* p)',1,0,0,1)

/**
 * <description>
 *	This function read a 64bit integer value atomic.
 * </description>
 * <param name="p" type="IN">Pointer to the input structure</param>
 * <parampseudo name="pSrc" type="IN">Pointer to source address to read from</parampseudo>
 * <parampseudo name="pResult" type="IN">Pointer to error code</parampseudo>
 * <parampseudo name="out" type="OUT">Read 64bit integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`int64__atomicread',`(int64_atomicread_struct* p)',1,0,0,1)

/**
 * <description>
 *	This function write a 64bit integer value atomic.
 * </description>
 * <param name="p" type="IN">Pointer to the input structure</param>
 * <parampseudo name="pDest" type="IN">Pointer to destination address to write to</parampseudo>
 * <parampseudo name="write" type="IN">Value to write</parampseudo>
 * <parampseudo name="out" type="OUT">Error code for result.</parampseudo>
 */
DEF_API(`void',`CDECL',`int64__atomicwrite',`(int64_atomicwrite_struct* p)',1,0,0,1)


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
DEF_API(`void',`CDECL',`real32__to__any32',`(real32_to_any32_struct* p)',1)

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
DEF_API(`void',`CDECL',`any32__to__real32',`(any32_to_real32_struct* p)',1)

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
DEF_API(`void',`CDECL',`real32__to__any64',`(real32_to_any64_struct* p)',1,0,0,1)

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
DEF_API(`void',`CDECL',`any64__to__real32',`(any64_to_real32_struct* p)',1,0,0,1)

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
DEF_API(`void',`CDECL',`real64__to__any32',`(real64_to_any32_struct* p)',1,0,0,1)

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
DEF_API(`void',`CDECL',`any32__to__real64',`(any32_to_real64_struct* p)',1,0,0,1)

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
DEF_API(`void',`CDECL',`real64__to__any64',`(real64_to_any64_struct* p)',1,0,0,1)

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
DEF_API(`void',`CDECL',`any64__to__real64',`(any64_to_real64_struct* p)',1,0,0,1)

/**
 * <description>This function Converts a 64-bit real value to a 32-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_REAL64_TO_REAL32_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[ANY_MIN, ANY_MID, ANY_MAX]">Input value</parampseudo>
 * <parampseudo name="out" type="OUT">Input value as 32-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__to__real32',`(real64_to_real32_struct* p)',1,0,0,1)

/**
 * <description>This function Converts a 32-bit real value to a 64-bit real value.</description>
 * <param name="p" type="IN" range="[VALID_REAL32_TO_REAL64_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="in" type="IN" range="[ANY_MIN, ANY_MID, ANY_MAX]">Input value</parampseudo>
 * <parampseudo name="out" type="OUT">Input value as 64-bit real value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real32__to__real64',`(real32_to_real64_struct* p)',1,0,0,1)

/**
 * <description>
 * <p>This function read a 64bit real value atomic.</p>
 * </description>
 * <param name="p" type="IN"">Pointer to the input structure</param>
 * <parampseudo name="pSrc" type="IN">Pointer to source address to read from</parampseudo>
 * <parampseudo name="pResult" type="IN">Pointer to error code</parampseudo>
 * <parampseudo name="out" type="OUT">Read 64bit integer value.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__atomicread',`(real64_atomicread_struct* p)',1,0,0,1)

/**
 * <description>
 * <p>This function write a 64bit real value atomic.</p>
 * </description>
 * <param name="p" type="IN"">Pointer to the input structure</param>
 * <parampseudo name="pDest" type="IN">Pointer to destination address to write to</parampseudo>
 * <parampseudo name="write" type="IN">Value to write</parampseudo>
 * <parampseudo name="out" type="OUT">Error code for result.</parampseudo>
 */
DEF_API(`void',`CDECL',`real64__atomicwrite',`(real64_atomicwrite_struct* p)',1,0,0,1)

/**
 * <description>This function returns a monotonic rising millisecond tick. This tick can be used for timeout and relative time measurements.</description>
 * <param name="p" type="IN" range="[VALID_GET_TIME_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="out" type="OUT">millisecond tick as 32-Bit value.</parampseudo>
 */
DEF_API(`void',`CDECL',`get__time',`(get_time_struct* p)',1)

/**
 * <description>This function returns a monotonic rising nanosecond tick. This tick can be used for very high resolution time measurements.</description>
 * <param name="p" type="IN" range="[VALID_GET_LTIME_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="out" type="OUT">microsecond tick as 64-Bit value.</parampseudo>
 */
DEF_API(`void',`CDECL',`get__ltime',`(get_ltime_struct* p)',1)

/**
 * <description>Fill the buffer with a specified value. Routine is used as external library function for the plc program.</description>
 * <param name="p" type="IN">Pointer to the input structure</param>
 * <parampseudo name="out" type="OUT">Value of pDest or 0 if failed</parampseudo>
 */
DEF_API(`void',`CDECL',`__memset',`(__memset_struct *p)',1,0)

/**
 * <description>A simple exception handling function</description>
 * <param name="p" type="IN">Pointer to the input structure</param>
 * <parampseudo name="out" type="OUT">ExceptionCode or 0 for noeexception</parampseudo>
 */
DEF_API(`void',`CDECL',`trycatch',`(trycatch_struct *p)',1,0)

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

DEF_API(`void',`CDECL',`systimelock',`(systimelock_struct *p)',1,0x9F97092C,0x03050500)

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

DEF_API(`void',`CDECL',`systimeset',`(systimeset_struct *p)',1,0xED35B558,0x03050500)

/**
 * <description>Function to unlock the actual timestamp for all IEC timers.</description>
 * <result><p>RESULT: Returns always 0</p></result>
 */
typedef struct tagsystimeunlock_struct
{
	RTS_IEC_WORD SysTimeUnlock;			/* VAR_OUTPUT */	
} systimeunlock_struct;

DEF_API(`void',`CDECL',`systimeunlock',`(systimeunlock_struct *p)',1,0x46CB8107,0x03050500)

/**
 * <description>Function to un-set the actual timestamp for all IEC timers.</description>
 * <result><p>RESULT: Returns always 0</p></result>
 */
typedef struct tagsystimeunset_struct
{
	RTS_IEC_WORD SysTimeUnSet;			/* VAR_OUTPUT */	
} systimeunset_struct;

DEF_API(`void',`CDECL',`systimeunset',`(systimeunset_struct *p)',1,0xB274556B,0x03050500)


/**
 * <description>systimeunlock: Use SysTimeLock.libaray</description>
 * <param name="p" type="IN" range="[VALID_SYSTIMEUNLOCK_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="SysTimeUnlock" type="OUT">Always 0</parampseudo>
 */
DEF_ITF_API(`RTS_UI16',`CDECL',`SysTimeUnlock',`(void)')

/**
 * <description>systimelock: Use SysTimeLock.libaray</description>
 * <param name="p" type="IN" range="[VALID_SYSTIMELOCK_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="ulTick" type="IN" range="[RTS_RANGE_OF_RTS_IEC_TIME]">Tick</parampseudo>
 * <parampseudo name="tTimeout" type="IN" range="[RTS_RANGE_OF_RTS_IEC_TIME]">Timeout</parampseudo>
 * <parampseudo name="SysTimeLock" type="OUT">Always 0</parampseudo>
 */
DEF_ITF_API(`RTS_UI16',`CDECL',`SysTimeLock',`(RTS_UI32 ulTick, RTS_UI32 tTimeout)')

/**
 * <description>Function to un-set the actual timestamp for all IEC timers.</description>
 * <param name="p" type="IN" range="[VALID_SYSTIMEUNSET_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="SysTimeUnlock" type="OUT">Always 0</parampseudo>
 */
DEF_ITF_API(`RTS_UI16',`CDECL',`SysTimeUnSet',`(void)')

/**
 * <description>Function to set the actual timestamp for all IEC timers. Differnt to SysTimeLock, the timer continues</description>
 * <param name="p" type="IN" range="[VALID_SYSTIMESET_STRUCT]">Pointer to the input structure</param>
 * <parampseudo name="ulTick" type="IN" range="[RTS_RANGE_OF_RTS_IEC_TIME]">Tick</parampseudo>
 * <parampseudo name="tTimeout" type="IN" range="[RTS_RANGE_OF_RTS_IEC_TIME]">Timeout</parampseudo>
 * <parampseudo name="SysTimeSet" type="OUT">Always 0</parampseudo>
 */
DEF_ITF_API(`RTS_UI16',`CDECL',`SysTimeSet',`(RTS_UI32 ulTick, RTS_UI32 tTimeout)')


/**
 * <description>Returns the size in bytes, of the specified IEC data type.</description>
 * <param name="tc" type="IN" range="[0..TYPE3_MAX_TYPE]">Pointer to the input structure</param>
 * <result>Size in Bytes of Datatype, or 0 if unspecified</result>
 */
DEF_ITF_API(`unsigned int',`CDECL',`SysGetTypeSize',`(TypeClass3 tc)')

#ifdef __cplusplus
}
#endif
