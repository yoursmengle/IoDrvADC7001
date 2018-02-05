/**
 * <interfacename>CmpCrypto</interfacename>
 * <description> 
 *	<p>This interface provides access to different cryptographic algorithms:</p>
 *	<ul>
 *		<li>Symmetric ciphers</li>
 *		<li>Asymmetric ciphers</li>
 *		<li>Message digest algorithms</li>
 *		<li>Hashed message authentication codes (HMAC)</li>
 *		<li>Signature algorithms</li>
 *		<li>Random number generation</li>
 *	</ul>
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */
SET_INTERFACE_NAME(`CmpCrypto')

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Enum: RtsCryptoID</description>
 */
#define RTSCRYPTOID_AES_128_CBC    RTS_IEC_UDINT_C(0x1001)	/* Symmetric chipers */
#define RTSCRYPTOID_AES_128_CFB    RTS_IEC_UDINT_C(0x1002)	
#define RTSCRYPTOID_AES_256_CBC    RTS_IEC_UDINT_C(0x1003)	
#define RTSCRYPTOID_DES_CBC    RTS_IEC_UDINT_C(0x1004)	
#define RTSCRYPTOID_AES_256_CTR    RTS_IEC_UDINT_C(0x1005)	
#define RTSCRYPTOID_RSA    RTS_IEC_UDINT_C(0x2001)	/* Asymmetric Cipers */
#define RTSCRYPTOID_RSA_OAEP_PADDING    RTS_IEC_UDINT_C(0x2002)	
#define RTSCRYPTOID_RSA_PKCS1_V15_PADDING    RTS_IEC_UDINT_C(0x2003)	
#define RTSCRYPTOID_HASH_MD5    RTS_IEC_UDINT_C(0x3001)	/* Hash functions */
#define RTSCRYPTOID_HASH_SHA1    RTS_IEC_UDINT_C(0x3002)	
#define RTSCRYPTOID_HASH_SHA224    RTS_IEC_UDINT_C(0x3003)	
#define RTSCRYPTOID_HASH_SHA256    RTS_IEC_UDINT_C(0x3004)	
#define RTSCRYPTOID_HASH_SHA384    RTS_IEC_UDINT_C(0x3005)	
#define RTSCRYPTOID_HASH_SHA512    RTS_IEC_UDINT_C(0x3006)	
#define RTSCRYPTOID_HMAC_MD5    RTS_IEC_UDINT_C(0x4001)	/* HMAC Functions */
#define RTSCRYPTOID_HMAC_SHA1    RTS_IEC_UDINT_C(0x4002)	
#define RTSCRYPTOID_HMAC_SHA224    RTS_IEC_UDINT_C(0x4003)	
#define RTSCRYPTOID_HMAC_SHA256    RTS_IEC_UDINT_C(0x4004)	
#define RTSCRYPTOID_HMAC_SHA384    RTS_IEC_UDINT_C(0x4005)	
#define RTSCRYPTOID_HMAC_SHA512    RTS_IEC_UDINT_C(0x4006)	
#define RTSCRYPTOID_RSA_OAEP_SHA1    RTS_IEC_UDINT_C(0x5003)	/* Signature Functions */
#define RTSCRYPTOID_RSA_OAEP_SHA256    RTS_IEC_UDINT_C(0x5004)	
#define RTSCRYPTOID_RSA_PKCS1_V15_SHA1    RTS_IEC_UDINT_C(0x5001)	
#define RTSCRYPTOID_RSA_PKCS1_V15_SHA256    RTS_IEC_UDINT_C(0x5002)	
/* Typed enum definition */
#define RTSCRYPTOID    RTS_IEC_UDINT

/**
 * <description>Enum: RtsCryptoKeyType</description>
 */
#define KEYTYPE_KEY    RTS_IEC_DINT_C(0x0)	/* The key is directly available. Stored in a RTS_BYTESTRING. */
#define KEYTYPE_CERTHANDLE    RTS_IEC_DINT_C(0x1)	/* The key is identified by a handle to the certificat. Only used for asymmetric keys. */
#define KEYTYPE_CERTCONTENT    RTS_IEC_DINT_C(0x2)	/* The key is identified by the certificate context. Only used for asymmetric keys. */
/* Typed enum definition */
#define RTSCRYPTOKEYTYPE    RTS_IEC_DINT

/**
 * <description>Enum: RtsCryptoType</description>
 */
#define RTSCRYPTOTYPE_SYMMETRIC    RTS_IEC_UDINT_C(0x1000)	
#define RTSCRYPTOTYPE_ASYMMETRIC    RTS_IEC_UDINT_C(0x2000)	
#define RTSCRYPTOTYPE_HASH    RTS_IEC_UDINT_C(0x3000)	
#define RTSCRYPTOTYPE_HMAC    RTS_IEC_UDINT_C(0x4000)	
#define RTSCRYPTOTYPE_SIGNATURE    RTS_IEC_UDINT_C(0x5000)	
/* Typed enum definition */
#define RTSCRYPTOTYPE    RTS_IEC_UDINT

/**
 * This a representation of a byte string.
 */
typedef struct tagRtsByteString
{
	RTS_IEC_UDINT ui32Len;		/* Current lenght of data stored in the buffer. */
	RTS_IEC_UDINT ui32MaxLen;		/* The allocated size of the buffer. */
	RTS_IEC_BYTE *pByData;		/* Pointer to buffer */
	RTS_IEC_BOOL xDynamic;		/* Indicates if the data was allocated dynamically */
} RtsByteString;

/**
 * Storage of a crypto key.
 */
typedef union
{
	RtsByteString byteString;		/* Key is stored using the byte string. */
	RTS_IEC_HANDLE hCert;		/* Key is identified by this handle. */
} RtsCryptoKeyStorage;

/**
 * A cryptographic key.
 */
typedef struct tagRtsCryptoKey
{
	RTS_IEC_DINT keyType;		/* The type of the key. */
	RtsCryptoKeyStorage key;		/* Information of the key. Acturally only the KeyType_Key is supported. */
} RtsCryptoKey;

/**
 * Perform a asymmetric decryption using the algorithm handle.
 * :return: Result of the operation
 */
typedef struct tagcryptoasymmetricdecrypt_struct
{
	RTS_IEC_HANDLE hAlgo;				/* VAR_INPUT */	/* Handle to the algorithm. */
	RtsByteString *pCipherText;			/* VAR_INPUT */	/* Data to be decrypted */
	RtsCryptoKey privateKey;			/* VAR_INPUT */	/* Private key used to decrypt the data. */
	RtsByteString *pPlainText;			/* VAR_INPUT */	/* Decrypted data. */
	RTS_IEC_RESULT CryptoAsymmetricDecrypt;	/* VAR_OUTPUT */	
} cryptoasymmetricdecrypt_struct;

DEF_API(`void',`CDECL',`cryptoasymmetricdecrypt',`(cryptoasymmetricdecrypt_struct *p)',1,0x126B86CC,0x03050B00)

/**
 * Perform a asymmetric encryption using the algorithm handle.
 * :return: Result of the operation
 */
typedef struct tagcryptoasymmetricencrypt_struct
{
	RTS_IEC_HANDLE hAlgo;				/* VAR_INPUT */	/* Handle to the algorithm. */
	RtsByteString *pPlainText;			/* VAR_INPUT */	/* Data to be encrypted */
	RtsCryptoKey publicKey;				/* VAR_INPUT */	/* Public key used to encrypt the data. */
	RtsByteString *pCipherText;			/* VAR_INPUT */	/* Encrypted data. */
	RTS_IEC_RESULT CryptoAsymmetricEncrypt;	/* VAR_OUTPUT */	
} cryptoasymmetricencrypt_struct;

DEF_API(`void',`CDECL',`cryptoasymmetricencrypt',`(cryptoasymmetricencrypt_struct *p)',1,0xC14613D0,0x03050B00)

/**
 * Calculate the message digest of the given data.
 * :return: Result of the operation
 */
typedef struct tagcryptogeneratehash_struct
{
	RTS_IEC_HANDLE hAlgo;				/* VAR_INPUT */	/* Handle to the algorithm. */
	RtsByteString *pData;				/* VAR_INPUT */	/* Data to calculate the message digest. */
	RtsByteString *pHash;				/* VAR_INPUT */	/* Calculated message digest. */
	RTS_IEC_RESULT CryptoGenerateHash;	/* VAR_OUTPUT */	
} cryptogeneratehash_struct;

DEF_API(`void',`CDECL',`cryptogeneratehash',`(cryptogeneratehash_struct *p)',1,0x34E1A812,0x03050B00)

/**
 * Generate a number of cryptographic strong bytes.
 * :return: Function returns ERR_OK if the bytes could be generated
 */
typedef struct tagcryptogeneraterandomnumber_struct
{
	RTS_IEC_UDINT ui32NumOfRandomBytes;	/* VAR_INPUT */	/* Number of bytes needed. */
	RtsByteString *pRandom;				/* VAR_INPUT */	/* Buffer to store the bytes. */
	RTS_IEC_RESULT CryptoGenerateRandomNumber;	/* VAR_OUTPUT */	
} cryptogeneraterandomnumber_struct;

DEF_API(`void',`CDECL',`cryptogeneraterandomnumber',`(cryptogeneraterandomnumber_struct *p)',1,0xF9FC5437,0x03050B00)

/**
 * Get a handle to the algorithm using a specific ID
 * :return: Handle to the crypto algorithm
 */
typedef struct tagcryptogetalgorithmbyid_struct
{
	RTS_IEC_UDINT ui32CryptoID;			/* VAR_INPUT, Enum: RTSCRYPTOID */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Result of the operation. Can be NULL. */
	RTS_IEC_HANDLE CryptoGetAlgorithmById;	/* VAR_OUTPUT */	
} cryptogetalgorithmbyid_struct;

DEF_API(`void',`CDECL',`cryptogetalgorithmbyid',`(cryptogetalgorithmbyid_struct *p)',1,0x3D0776D3,0x03050B00)

/**
 * Get the asymmetric key size in bits.
 * :return: Size of the asymmetric key in bits
 */
typedef struct tagcryptogetasymmetrickeylength_struct
{
	RtsCryptoKey asymmetricKey;			/* VAR_INPUT */	/* Asymmetric key of intrest. */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Operation Result */
	RTS_IEC_UDINT CryptoGetAsymmetricKeyLength;	/* VAR_OUTPUT */	
} cryptogetasymmetrickeylength_struct;

DEF_API(`void',`CDECL',`cryptogetasymmetrickeylength',`(cryptogetasymmetrickeylength_struct *p)',1,0,0x03050B00)

/**
 * Get the first algorthm matching the type given. Use this with the GetNext function to iterate over algorthmes of a specific type.
 * :return: Handle to the crypto algorithm
 */
typedef struct tagcryptogetfirstalgorithm_struct
{
	RTS_IEC_UDINT ui32CryptoType;		/* VAR_INPUT, Enum: RTSCRYPTOTYPE */
	RTS_IEC_STRING *pszName;			/* VAR_INPUT */	/* Name of the algorthm. Can be NULL. */
	RTS_IEC_DINT i32MaxNameLen;			/* VAR_INPUT */	/* Maximum length of the name buffer */
	RTS_IEC_UDINT *pui32CryptoID;		/* VAR_INPUT */	/* ID of the algorithm. */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Result of the operation. Can be NULL. */
	RTS_IEC_HANDLE CryptoGetFirstAlgorithm;	/* VAR_OUTPUT */	
} cryptogetfirstalgorithm_struct;

DEF_API(`void',`CDECL',`cryptogetfirstalgorithm',`(cryptogetfirstalgorithm_struct *p)',1,0xC8A4A345,0x03050B00)

/**
 * Get the next algorthm matching the type given.
 * :return:  Handle to the crypto algorithm
 */
typedef struct tagcryptogetnextalgorithm_struct
{
	RTS_IEC_HANDLE hCrypto;				/* VAR_INPUT */	/* Handle to the last algorithem. */
	RTS_IEC_UDINT ui32CryptoType;		/* VAR_INPUT, Enum: RTSCRYPTOTYPE */
	RTS_IEC_STRING *pszName;			/* VAR_INPUT */	/* Name of the agorithm. Can be NULL. */
	RTS_IEC_DINT i32MaxNameLen;			/* VAR_INPUT */	/* Maximum length of the name buffer */
	RTS_IEC_UDINT *pui32CryptoID;		/* VAR_INPUT */	/* ID of the agorithm. */
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	/* Result of the operation. Can be NULL. */
	RTS_IEC_HANDLE CryptoGetNextAlgorithm;	/* VAR_OUTPUT */	
} cryptogetnextalgorithm_struct;

DEF_API(`void',`CDECL',`cryptogetnextalgorithm',`(cryptogetnextalgorithm_struct *p)',1,0x79EC29C8,0x03050B00)

/**
 *Generate a hashed message authentication code (HMAC) OF the given data AND key.
 * :return: Result of the operation
 */
typedef struct tagcryptohmacsign_struct
{
	RTS_IEC_HANDLE hAlgo;				/* VAR_INPUT */	/* Handle to the algorithm. */
	RtsByteString *pData;				/* VAR_INPUT */	/* Data to calculate the HMAC. */
	RtsCryptoKey key;					/* VAR_INPUT */	/* Key to be used for the HMAC calcuation */
	RtsByteString *pSignature;			/* VAR_INPUT */	/* Calculated HMAC */
	RTS_IEC_RESULT CryptoHMACSign;		/* VAR_OUTPUT */	
} cryptohmacsign_struct;

DEF_API(`void',`CDECL',`cryptohmacsign',`(cryptohmacsign_struct *p)',1,0x931A9470,0x03050B00)

/**
 * Verify a recieved hashed message authentication code (HMAC).
 * :return: Function returns ERR_OK if the HMAC is valid.
 */
typedef struct tagcryptohmacverify_struct
{
	RTS_IEC_HANDLE hAlgo;				/* VAR_INPUT */	/* Handle to the algorithm. */
	RtsByteString *pData;				/* VAR_INPUT */	/* Data to calculate the HMAC. */
	RtsCryptoKey key;					/* VAR_INPUT */	/* Key to be used for the HMAC calcuation */
	RtsByteString *pSignature;			/* VAR_INPUT */	/* Recieved HMAC */
	RTS_IEC_RESULT CryptoHMACVerify;	/* VAR_OUTPUT */	
} cryptohmacverify_struct;

DEF_API(`void',`CDECL',`cryptohmacverify',`(cryptohmacverify_struct *p)',1,0x49EEB4A9,0x03050B00)

/**
 * <description>cryptokeyexit</description>
 */
typedef struct tagcryptokeyexit_struct
{
	RtsCryptoKey *pKey;					/* VAR_INPUT */	
	RTS_IEC_RESULT CryptoKeyExit;		/* VAR_OUTPUT */	
} cryptokeyexit_struct;

DEF_API(`void',`CDECL',`cryptokeyexit',`(cryptokeyexit_struct *p)',1,0xD71ED5F3,0x03050B00)

/**
 * <description>cryptokeyinit</description>
 */
typedef struct tagcryptokeyinit_struct
{
	RtsCryptoKey *pKey;					/* VAR_INPUT */	
	RtsCryptoKeyStorage key;			/* VAR_INPUT */	
	RTS_IEC_DINT keyType;				/* VAR_INPUT, Enum: RTSCRYPTOKEYTYPE */
	RTS_IEC_RESULT CryptoKeyInit;		/* VAR_OUTPUT */	
} cryptokeyinit_struct;

DEF_API(`void',`CDECL',`cryptokeyinit',`(cryptokeyinit_struct *p)',1,0xE8E228B3,0x03050B00)

/**
 * <description>cryptortsbytestringexit</description>
 */
typedef struct tagcryptortsbytestringexit_struct
{
	RtsByteString *pByteString;			/* VAR_INPUT */	
	RTS_IEC_RESULT CryptoRtsByteStringExit;	/* VAR_OUTPUT */	
} cryptortsbytestringexit_struct;

DEF_API(`void',`CDECL',`cryptortsbytestringexit',`(cryptortsbytestringexit_struct *p)',1,0x16B297C5,0x03050B00)

/**
 * <description>cryptortsbytestringinit</description>
 */
typedef struct tagcryptortsbytestringinit_struct
{
	RtsByteString *pByteString;			/* VAR_INPUT */	
	RTS_IEC_RESULT CryptoRtsByteStringInit;	/* VAR_OUTPUT */	
} cryptortsbytestringinit_struct;

DEF_API(`void',`CDECL',`cryptortsbytestringinit',`(cryptortsbytestringinit_struct *p)',1,0xC1B4C2F9,0x03050B00)

/**
 * Sign the data using a specific message digest and the private key.
 * :return: Result of the operation.
 */
typedef struct tagcryptosignaturegenerate_struct
{
	RTS_IEC_HANDLE hAlgo;				/* VAR_INPUT */	/* Handle to the algorithm. */
	RtsByteString *pData;				/* VAR_INPUT */	/* Data to be signed. */
	RtsCryptoKey privateKey;			/* VAR_INPUT */	/* Key to be used signing. Has to be a private key. */
	RtsByteString *pSignature;			/* VAR_INPUT */	/* Calculated signature of the data. */
	RTS_IEC_RESULT CryptoSignatureGenerate;	/* VAR_OUTPUT */	
} cryptosignaturegenerate_struct;

DEF_API(`void',`CDECL',`cryptosignaturegenerate',`(cryptosignaturegenerate_struct *p)',1,0x0C2FBF80,0x03050B00)

/**
 * Verify a recieved signature
 * :return: unction returns ERR_OK if the signature is valid.
 */
typedef struct tagcryptosignatureverify_struct
{
	RTS_IEC_HANDLE hAlgo;				/* VAR_INPUT */	/* Handle to the algorithm. */
	RtsByteString *pData;				/* VAR_INPUT */	/* Data to verify. */
	RtsCryptoKey publicKey;				/* VAR_INPUT */	/* Public key of the sender. */
	RtsByteString *pSignature;			/* VAR_INPUT */	/* Received signature. */
	RTS_IEC_RESULT CryptoSignatureVerify;	/* VAR_OUTPUT */	
} cryptosignatureverify_struct;

DEF_API(`void',`CDECL',`cryptosignatureverify',`(cryptosignatureverify_struct *p)',1,0x3F425BB9,0x03050B00)

/**
 * Perform a symmetric decryption using the algorithm handle.
 * :return: Result of the operation
 */
typedef struct tagcryptosymmetricdecrypt_struct
{
	RTS_IEC_HANDLE hAlgo;				/* VAR_INPUT */	/* Handle to the algorithm. */
	RtsByteString *pCipherText;			/* VAR_INPUT */	/* Data to be decrypted */
	RtsCryptoKey key;					/* VAR_INPUT */	/* Key to decrypt the data. Has to be a KeyType_Key key. */
	RtsByteString *pInitVector;			/* VAR_INPUT */	/* Init vector of the decrypt. */
	RTS_IEC_BOOL xEnablePadding;		/* VAR_INPUT */	/* Enables padding. If this is not enabled the ciphertext length has to match a multiple of the block length. */
	RtsByteString *pPlainText;			/* VAR_INPUT */	/* Decrypted data. */
	RTS_IEC_RESULT CryptoSymmetricDecrypt;	/* VAR_OUTPUT */	
} cryptosymmetricdecrypt_struct;

DEF_API(`void',`CDECL',`cryptosymmetricdecrypt',`(cryptosymmetricdecrypt_struct *p)',1,0xF3963545,0x03050B00)

/**
 * Perform a symmetric encryption using the algorithm handle.
 * :return: Result of the operation
 */
typedef struct tagcryptosymmetricencrypt_struct
{
	RTS_IEC_HANDLE hAlgo;				/* VAR_INPUT */	/* Handle to the algorithm. */
	RtsByteString *pPlainText;			/* VAR_INPUT */	/* Data to be encrypted */
	RtsCryptoKey key;					/* VAR_INPUT */	/* Key to encrypt the data. Has to be a KeyType_Key key. */
	RtsByteString *pInitVector;			/* VAR_INPUT */	/* Init vector of the ecryption */
	RTS_IEC_BOOL xEnablePadding;		/* VAR_INPUT */	/* Enables padding. If this is not enabled the plaintext length has to match a multiple of the block length. */
	RtsByteString *pCipherText;			/* VAR_INPUT */	/* Encrypted data. */
	RTS_IEC_RESULT CryptoSymmetricEncrypt;	/* VAR_OUTPUT */	
} cryptosymmetricencrypt_struct;

DEF_API(`void',`CDECL',`cryptosymmetricencrypt',`(cryptosymmetricencrypt_struct *p)',1,0x8D659084,0x03050B00)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

/**
 * <description>Information of symmetric ciphers.</description>
 * <param name="ui32KeyLen">The length of the key id bytes.</param>
 * <param name="ui32BlockSize">Block size of the cipher in bytes.</param>
 * <param name="ui32InitVLen">Init vector size in bytes.</param>
 */
typedef struct
{
	RTS_UI32	ui32KeyLen;
	RTS_UI32	ui32BlockSize;
	RTS_UI32	ui32InitVLen;
}RtsSymmetricCipherInfo;

/**
 * <description>Information of message digests.</description>
 * <param name="ui32DigestLen">The length generated message digest in bytes..</param>
 */
typedef struct
{
	RTS_UI32	ui32DigestLen;
}RtsDigestInfo;


/**
 * <description>Information of a specific crypto algorithm.</description>
 * <param name="ui32CryptoType">Type of the algorithm. See: Crypto Types</param>
 * <param name="ui32CryptoId">ID of the algorithm.</param>
 * <param name="pszCryptoName">Name of the algorithm.</param>
 * <param name="info">algorithm specific information.</param>
 */
typedef struct
{
	RTS_UI32	ui32CryptoType;
	RTS_UI32	ui32CryptoId;
	const char*		pszCryptoName;
	union
	{
		RtsSymmetricCipherInfo symmetric;
		RtsDigestInfo digest;
		RtsDigestInfo HMAC;

	}info;
}RtsCryptoInfo;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Get a handle to the algorithm using a specific ID</description>
 * <param name="ui32CryptoID" type="IN">ID of the algorithm</param>
 * <param name="pResult" type="IN">Error code: Result of the operation. Can be NULL.</param>
 * <result>Handle to the crypto algorithm</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`CryptoGetAlgorithmById',`(RTS_UI32 ui32CryptoID, RTS_RESULT* pResult)')

/**
 * <description>Get the first algorithm matching the type given. Use this with the 
 * GetNext function to iterate over algorithmes of a specific type.</description>
 * <param name="ui32CryptoType" type="IN">Type of the algorithm. See: Crypto Types</param>
 * <param name="pszName" type="OUT">Name of the algorithm. Can be NULL.</param>
 * <param name="i32MaxNameLen" type="OUT">Maximum length of the name buffer</param>
 * <param name="pui32CryptoID" type="OUT">ID of the algorithm.</param>
 * <param name="pResult" type="IN">Error code: Result of the operation. Can be NULL.</param>
 * <result>Handle to the crypto algorithm</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`CryptoGetFirstAlgorithm',`(RTS_UI32 ui32CryptoType, char *pszName, RTS_I32 i32MaxNameLen, RTS_UI32 *pui32CryptoID, RTS_RESULT *pResult)')

/**
 * <description>Get the next algorithm matching the type given.</description>
 * <param name="hCrypto" type="IN">Handle to the last algorithm.</param>
 * <param name="ui32CryptoType" type="IN">Handle to the last algorithm.</param>
 * <param name="pszName" type="OUT">Name of the algorithm. Can be NULL.</param>
 * <param name="i32MaxNameLen" type="OUT">Maximum length of the name buffer</param>
 * <param name="pui32CryptoID" type="OUT">ID of the algorithm.</param>
 * <param name="pResult" type="IN">Error code: Result of the operation. Can be NULL.</param>
 * <result>Handle to the crypto algorithm</result>
 */
DEF_ITF_API(`RTS_HANDLE',`CDECL',`CryptoGetNextAlgorithm',`(RTS_HANDLE hCrypto, RTS_UI32 ui32CryptoType, char *pszName, RTS_I32 i32MaxNameLen, RTS_UI32 *pui32CryptoID, RTS_RESULT *pResult)')

/**
 * <description>Get information of the algorithm. Don't free or modify the CryptoInfo.</description>
 * <param name="hCrypto" type="IN">Handle to the algorithm.</param>
 * <param name="pResult" type="IN">Error code: Result of the operation. Can be NULL.</param>
 * <result>Pointer to the information structure.</result>
 */
DEF_ITF_API(`RtsCryptoInfo*',`CDECL',`CryptoGetAlgorithmInfo',`(RTS_HANDLE hCrypto, RTS_RESULT* pCryptoInfo)')

/**
 * <description>Perform a symmetric encryption using the algorithm handle.</description>
 * <param name="hAlgo" type="IN">Handle to the algorithm.</param>
 * <param name="pPlainText" type="IN">Data to be encrypted</param>
 * <param name="key" type="IN">Key to encrypt the data. Has to be a KeyType_Key key.</param>
 * <param name="pInitVector" type="IN">Init vector of the ecryption</param>
 * <param name="bEnablePadding" type="IN">Enables the padding of the algorithm. If padding is not enabled the plaintext length has to match a multiple of the cipher block length</param>
 * <param name="pCipherText" type="OUT">Encrypted data.</param>
 * <result>Error code: Result of the operation</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`CryptoSymmetricEncrypt',`(RTS_HANDLE hAlgo, RtsByteString* pPlainText, RtsCryptoKey key, RtsByteString* pInitVector, RTS_BOOL bEnablePadding, RtsByteString* pCipherText)')

/**
 * <description>Perform a symmetric decryption using the algorithm handle.</description>
 * <param name="hAlgo" type="IN">Handle to the algorithm.</param>
 * <param name="pCipherText" type="IN">Data to be decrypted</param>
 * <param name="key" type="IN">Key to decrypt the data. Has to be a KeyType_Key key.</param>
 * <param name="pInitVector" type="IN">Init vector of the decrypt.</param>
 * <param name="bEnablePadding" type="IN">Enables the padding of the algorithm. If padding is not enabled the plaintext length has to match a multiple of the cipher block length</param>
 * <param name="pCipherText" type="OUT">Decrypted data.</param>
 * <result>Error code: Result of the operation</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`CryptoSymmetricDecrypt',`(RTS_HANDLE hAlgo, RtsByteString* pCipherText, RtsCryptoKey key, RtsByteString* pInitVector, RTS_BOOL bEnablePadding, RtsByteString* pPlainText)')

/**
 * <description>Perform an asymmetric encryption using the algorithm handle.</description>
 * <param name="hAlgo" type="IN">Handle to the algorithm.</param>
 * <param name="pPlainText" type="IN">Data to be encrypted</param>
 * <param name="publicKey" type="IN">Public key used to encrypt the data. Use X509CertGetPublicKey to get the public key form an certificate.</param>
 * <param name="pCipherText" type="OUT">Encrypted data.</param>
 * <result>Error code: Result of the operation</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`CryptoAsymmetricEncrypt',`(RTS_HANDLE hAlgo, RtsByteString* pPlainText, RtsCryptoKey publicKey, RtsByteString* pCipherText)')

/**
 * <description>Perform an asymmetric decryption using the algorithm handle.</description>
 * <param name="hAlgo" type="IN">Handle to the algorithm.</param>
 * <param name="pCiperText" type="IN">Data to be decrypted</param>
 * <param name="privateKey" type="IN">Private key used to decrypt the data. Use X509CertGetPrivateKey to get the private key from an certificate.</param>
 * <param name="pCipherText" type="OUT">Decrypted data.</param>
 * <result>Error code: Result of the operation</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`CryptoAsymmetricDecrypt',`(RTS_HANDLE hAlgo, RtsByteString* pCipherText, RtsCryptoKey privateKey, RtsByteString* pPlainText)')

/**
 * <description>Get the private key size in bits.</description>
 * <param name="priavteKey" type="IN">Asymmetric key of intrest. Use X509CertGetPublicKey or X509CertGetPrivateKey to get the asymmetric key.</param>
 * <param name="pResult" type="OUT">Error code: Operation Result</param>
 * <result>Size of the private key in bits</result>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`CryptoGetAsymmetricKeyLength',`(RtsCryptoKey asymmetricKey, RTS_RESULT* pResult)')

/**
 * <description>Calculate the message digest of the given data.</description>
 * <param name="hAlgo" type="IN">Handle to the algorithm.</param>
 * <param name="pData" type="IN">Data to calculate the message digest.</param>
 * <param name="pHash" type="OUT">Calculated message digest.</param>
 * <result>Result of the operation</result>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`CryptoGenerateHash',`(RTS_HANDLE hAlgo, RtsByteString* pData, RtsByteString* pHash)')

/**
 * <description>Generate a hashed message authentication code (HMAC) of the given data and key.</description>
 * <param name="hAlgo" type="IN">Handle to the algorithm.</param>
 * <param name="pData" type="IN">Data to calculate the HMAC.</param>
 * <param name="key" type="IN">Key to be used for the HMAC calcuation</param>
 * <param name="pSignature" type="OUT">Calculated HMAC</param>
 * <result>Error code Result of the operation</result>
 **/
DEF_ITF_API(`RTS_RESULT',`CDECL',`CryptoHMACSign',`(RTS_HANDLE hAlgo, RtsByteString* pData, RtsCryptoKey key, RtsByteString* pSignature)')

/**
 * <description>Verify a recieved hashed message authentication code (HMAC).</description>
 * <param name="hAlgo" type="IN">Handle to the algorithm.</param>
 * <param name="pData" type="IN">Data to calculate the HMAC.</param>
 * <param name="key" type="IN">Key to be used for the HMAC calcuation</param>
 * <param name="pSignature" type="IN">Recieved HMAC</param>
 * <result>Error Code Function returns ERR_OK if the HMAC is valid.</result>
 **/
DEF_ITF_API(`RTS_RESULT',`CDECL',`CryptoHMACVerify',`(RTS_HANDLE hAlgo, RtsByteString* pData, RtsCryptoKey key, RtsByteString* pSignature)')

/**
 * <description>Sign the data using a specific message digest and the private key.</description>
 * <param name="hAlgo" type="IN">Handle to the algorithm.</param>
 * <param name="pData" type="IN">Data to be signed.</param>
 * <param name="privateKey" type="IN">Key to be used signing. Has to be a private key. Use X509CertGetPrivateKey to get the private key.</param>
 * <param name="pSignature" type="IN">Calculated signature of the data.</param>
 * <result>Error code: Result of the operation.</result>
 **/
DEF_ITF_API(`RTS_RESULT',`CDECL',`CryptoSignatureGenerate',`(RTS_HANDLE hAlgo, RtsByteString* pData, RtsCryptoKey privateKey, RtsByteString* pSignature)')

/**
 * <description>Verify a received signature</description>
 * <param name="hAlgo" type="IN">Handle to the algorithm.</param>
 * <param name="pData" type="IN">Data to verify.</param>
 * <param name="publicKey" type="IN">Public key of the sender. X509CertGetPublicKey to get the key.</param>
 * <param name="pSignature" type="IN">Received signature.</param>
 * <result>Error code: Function returns ERR_OK if the signature is valid.</result>
 **/
DEF_ITF_API(`RTS_RESULT',`CDECL',`CryptoSignatureVerify',`(RTS_HANDLE hAlgo, RtsByteString* pData, RtsCryptoKey publicKey, RtsByteString* pSignature)')

/**
 * <description>Generate a number of cryptographic strong bytes.</description>
 * <param name="ui32NumOfRandomBytes" type="IN">Number of bytes needed.</param>
 * <param name="pRandom" type="IN">Buffer to store the bytes.</param>
 * <result>Error code: Function returns ERR_OK if the bytes could be generated</result>
 **/
DEF_ITF_API(`RTS_RESULT',`CDECL',`CryptoGenerateRandomNumber',`(RTS_UI32 ui32NumOfRandomBytes, RtsByteString* pRandom)')

/**
 * <description>Initialize a crypto key.</description>
 * <param name="pKey" type="IN">Pointer to the key to be initialized.</param>
 * <param name="key" type="IN">Content of the key.</param>
 * <param name="type" type="IN">Type of the key.</param>
 * <result>Operation result.</result>
 **/
DEF_ITF_API(`RTS_RESULT',`CDECL',`CryptoKeyInit',`(RtsCryptoKey* pKey, RtsCryptoKeyStorage key, RTSCRYPTOKEYTYPE keyType)')

/**
 * <description>Clean up a crypto key.</description>
 * <param name="pKey" type="IN">Key to be clean up.</param>
 * <result>Operation result.</result>
 **/
DEF_ITF_API(`RTS_RESULT',`CDECL',`CryptoKeyExit',`(RtsCryptoKey* pKey)')

/**
 * <description>Initialize a byte string.</description>
 * <param name="pByteString" type="IN">Pointer to the key to be initialized.</param>
 * <result>Operation result.</result>
 **/
DEF_ITF_API(`RTS_RESULT',`CDECL',`CryptoRtsByteStringInit',`(RtsByteString* pByteString)')

/**
 * <description>Initialize a byte string.</description>
 * <param name="pByteString" type="IN">Pointer to the key to be initialized.</param>
 * <result>Operation result.</result>
 **/
DEF_ITF_API(`RTS_RESULT',`CDECL',`CryptoRtsByteStringInit2',`(RtsByteString* pByteString, RTS_UI32 ui32BufferSize, RTS_UI8* pBuffer)')

/**
 * <description>Clean up a byte string.</description>
 * <param name="pByteString" type="IN">Byte string to be clean up.</param>
 * <result>Operation result.</result>
 **/
DEF_ITF_API(`RTS_RESULT',`CDECL',`CryptoRtsByteStringExit',`(RtsByteString* pByteString)')

#ifdef __cplusplus
}
#endif
