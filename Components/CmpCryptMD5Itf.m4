SET_INTERFACE_NAME(`CmpCryptMD5')

#include "CmpItf.h"

/**
 * <category>Static defines</category>
 * <description>MD5 key length</description>
 */
#define	CRYPTMD5_KEY_LENGTH					33

#ifdef __cplusplus
extern "C" {
#endif

DEF_ITF_API(`RTS_RESULT',`CDECL',`CryptMD5Calculate',`(const unsigned char* pchInput, int nInputLength, char* pcResult, int iResultLen)')

#ifdef __cplusplus
}
#endif
