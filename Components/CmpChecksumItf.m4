/**
 * <interfacename>CmpChecksum</interfacename>
 * <description>
 *	Interface for the checksum utility component.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpChecksum')


/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>crc16finish</description>
 */
typedef struct tagcrc16finish_struct
{
	RTS_IEC_WORD ulCRC;					/* VAR_INPUT */	
	RTS_IEC_WORD CRC16Finish;			/* VAR_OUTPUT */	
} crc16finish_struct;

DEF_API(`void',`CDECL',`crc16finish',`(crc16finish_struct *p)',1,0x614D590C,0x03050500)

/**
 * <description>crc16init</description>
 */
typedef struct tagcrc16init_struct
{
	RTS_IEC_WORD CRC16Init;				/* VAR_OUTPUT */	
} crc16init_struct;

DEF_API(`void',`CDECL',`crc16init',`(crc16init_struct *p)',1,0xED70411E,0x03050500)

/**
 * <description>crc16update</description>
 */
typedef struct tagcrc16update_struct
{
	RTS_IEC_WORD ulCRC;					/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	RTS_IEC_XWORD ulSize;				/* VAR_INPUT */	
	RTS_IEC_WORD CRC16Update;			/* VAR_OUTPUT */	
} crc16update_struct;

DEF_API(`void',`CDECL',`crc16update',`(crc16update_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x3373C5C6),0x03050500)

/**
 * <description>crc32finish</description>
 */
typedef struct tagcrc32finish_struct
{
	RTS_IEC_DWORD ulCRC;				/* VAR_INPUT */	
	RTS_IEC_DWORD CRC32Finish;			/* VAR_OUTPUT */	
} crc32finish_struct;

DEF_API(`void',`CDECL',`crc32finish',`(crc32finish_struct *p)',1,0x4BF5AEF0,0x03050500)

/**
 * <description>crc32init</description>
 */
typedef struct tagcrc32init_struct
{
	RTS_IEC_DWORD CRC32Init;			/* VAR_OUTPUT */	
} crc32init_struct;

DEF_API(`void',`CDECL',`crc32init',`(crc32init_struct *p)',1,0x4847BC72,0x03050500)

/**
 * <description>crc32update</description>
 */
typedef struct tagcrc32update_struct
{
	RTS_IEC_DWORD ulCRC;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	RTS_IEC_XWORD ulSize;				/* VAR_INPUT */	
	RTS_IEC_DWORD CRC32Update;			/* VAR_OUTPUT */	
} crc32update_struct;

DEF_API(`void',`CDECL',`crc32update',`(crc32update_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x19CB323A),0x03050500)

/**
 * <description>crc32update2</description>
 */
typedef struct tagcrc32update2_struct
{
	RTS_IEC_DWORD ulCRC;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	RTS_IEC_XWORD ulSize;				/* VAR_INPUT */	
	RTS_IEC_DWORD CRC32Update2;			/* VAR_OUTPUT */	
} crc32update2_struct;

DEF_API(`void',`CDECL',`crc32update2',`(crc32update2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xEE853B38),0x03050500)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 *	Implementation of a 16-Bit CRC. The CRC is based on the 
 *  CCITT polynom x^16 + x^12 + x^5 + 1.
 *  Since there seem to be different opinions about "the" CCITT CRC-16,
 *  here a description of the options used in this api:
 *  - Bits are shifted in with MSB first
 *  - Input bytes are NOT reversed
 *  - The final CRC is NOT reversed
 *  - Initial value is 0xFFFF
 *  - 16 Zero-bits are implicitly appended to the end of the message
 *  - The "checkvalue" is 0xE5CC (ie. the CRC of the ASCII string '123456789')
 * </description>
 */
DEF_API(`RTS_UI16',`CDECL',`CRC16Init',`(void)')

/**
 * <description>
 *   Update the CRC with a block of data. Before the first call you have to initialize the
 *   CRC by calling CRC16Init.
 * </description>
 * <param name="usCRC" type="IN">
 *   The previous value of the crc as returned by the last call to CRC16Init or 
 *   CRC16Update.
 * </param>
 * <param name="pData" type="IN">
 *   Points at the data which should be added to the crc.
 * </param>
 * <param name="ulSize" type="IN">
 *   The number of bytes in pData.
 * </param>
 * <result>
 *   Returns the updated crc.
 * </result>
 */
DEF_API(`RTS_UI16',`CDECL',`CRC16Update',`(RTS_UI16 usCRC, const unsigned char * pData, RTS_SIZE ulSize)')

/**
 * <description>
 *   For the CRC to be valid it has to be finished after it is updated with all data.
 *   Use this as the last step during calculating your CRC.
 * </description>
 * <param name="usCRC" type="IN">
 *  The current value of the crc to be finished.
 * </param>
 * <result>
 *	 The checksum over all data passed in via CRC16Update.
 * </result>
 */
DEF_API(`RTS_UI16',`CDECL',`CRC16Finish',`(RTS_UI16 usCRC)')

/**
 * <description>Implementation of a initial 32-Bit CRC. Initial value is 0xFFFFFFFF.</description>
 * <parampseudo name="InitValue" type="IN" range="[INIT_VAL32]">Define that sets the Initial Value</parampseudo>
 * <result>Returns the initial CRC value.</result>
 */
DEF_API(`RTS_UI32',`CDECL',`CRC32Init',`(void)')

/**
 * 
 * <description>
 * <p>Obsolete: Use CRC32Update2 instead!</p>
 * <p>Update the CRC with a block of data. Before the first call you have to initialize the
 *   crc by calling CRC32Init. Must only be used, if the CRC is calculated in one step and not
 *   using several calls of CRC32Update for adding data to the CRC.</p>
 *	 <p>ATTENTION: You have to finish the CRC with the function CRC32Finish()!</p>
 * </description>
 * <param name="ulCRC" type="IN">
 *   The previous value of the crc as returned by the last call to CRC32Init.
 * </param>
 * <param name="pData" type="IN">
 *   Points at the data for which the CRC should be calculated.
 * </param>
 * <param name="ulSize" type="IN">
 *   The number of bytes in pData.
 * </param>
 * <result>
 *   Returns the updated CRC.
 * </result>
 */
DEF_API(`RTS_UI32',`CDECL',`CRC32Update',`(RTS_UI32 ulCRC, const unsigned char *pData, RTS_SIZE ulSize)')

/**
 * <description>
 * <p>Obsolete: Use CRC32Finish2 instead!</p>
 * <p>For the CRC to be valid it has to be finished after it is updated with all data.
 *   Use this as the last step during calculating your CRC.</p>
 *   <p>In opposite to the other CRC algorithms, the resulting CRC is swapped to IntelByteOrder.</p>
 * </description>
 * <param name="ulCRC" type="IN">
 *  The current value of the CRC to be finished.
 * </param>
 * <result>
 *	 The checksum over all data passed in via CRC32Update.
 * </result>
 */
DEF_API(`RTS_UI32',`CDECL',`CRC32Finish',`(RTS_UI32 ulCRC)')

/**
 * <description>
 *   Update the CRC with a block of data. Before the first call you have to initialize the
 *   CRC by calling CRC32Init.
 *	 ATTENTION: You have to finish the CRC with the function CRC32Finish2()!
 * </description>
 * <param name="ulCRC" type="IN" range="[0,VALID_CRC32]">
 *   The previous value of the CRC as returned by the last call to CRC32Init or 
 *   CRC32Update2.
 * </param>
 * <param name="pData" type="IN" range="[VALID_DATA_POINTER]">
 *   Points at the data which should be added to the CRC.
 * </param>
 * <param name="ulSize" type="IN" range="[0,VALID_CRC32SIZE]">
 *   The number of bytes in pData.
 * </param>
 * <result>
 *   Returns the updated CRC.
 * </result>
 */
DEF_API(`RTS_UI32',`CDECL',`CRC32Update2',`(RTS_UI32 ulCRC, const unsigned char *pData, RTS_SIZE ulSize)')

/**
 * <description>
 *   For the CRC to be valid it has to be finished after it is updated with all data.
 *   Use this as the last step during calculating your CRC.
 * </description>
 * <param name="ulCRC" type="IN" range="[0,VALID_CRC32]">
 *  The current value of the CRC to be finished.
 * </param>
 * <result>
 *	 The checksum over all data passed in via CRC32Update.
 * </result>
 */
DEF_API(`RTS_UI32',`CDECL',`CRC32Finish2',`(RTS_UI32 ulCRC)')

#ifdef __cplusplus
}
#endif

