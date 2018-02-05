/**
 * <interfacename>CmpMgrUtilsHash</interfacename>
 * <description>
 *	Interface for the implementation of a hash table with a linked list of hash entries to handle collisions.
 *
 *	Usage:
 *		 1. Creating a hash table using of static memory [recommended]:
 *
 *			 CMUtlHashTable s_hashTable;
 *			 #define MY_NUM_OF_HASHENTRIES	10
 *			 RTS_UI8 s_hashTableBuffer[MEMPOOLHASH_GET_HASHTABLE_LEN( MY_NUM_OF_HASHENTRIES )];
 *
 *			 // Create hash table
 *			 RTS_RESULT result = CAL_CMUtlHashCreate2(&s_hashTable, MY_NUM_OF_HASHENTRIES, s_hashTableBuffer, COMPONENT_NAME);
 *
 *		 2. Creating a hash table using of dynamic memory:
 *
 *			 CMUtlHashTable s_hashTable;
 *			 #define MY_NUM_OF_HASHENTRIES	10
 *
 *			 // Create hash table
 *			 RTS_RESULT result = CAL_CMUtlHashCreate2(&s_hashTable, MY_NUM_OF_HASHENTRIES, s_hashTableBuffer, COMPONENT_NAME);
 *
 * 
 *		 // Delete hash table
 *		 CAL_CMUtlHashDelete(&s_hashTable);
 *
 *		 // Insert hash entry to the hash table
 *		 void *pBlock = ...; // Pointer to memory block to insert
 *		 result = CAL_CMUtlHashInsert(&s_hashTable, "MyKey", strlen("MyKey") + 1, FALSE, pBlock);
 * 
 *		 // Insert new static hash entry to the hash table, which is filled with the parameters
 *		 static CMUtlHashEntry s_newEntry;
 *		 result = CAL_CMUtlHashInsert2(&s_hashTable, &s_newEntry, "MyKey", strlen("MyKey") + 1, FALSE, pBlock);
 *
 *		 // Remove hash entry specified by key
 *		 CAL_CMUtlHashRemove(&s_hashTable, &s_newEntry);	
 *
 *		 // Remove hash entry specified by entry
 *		 CAL_CMUtlHashRemove2(&s_hashTable, "MyKey", strlen("MyKey") + 1);	
 *
 *		 // Search a hash entry
 *		 RTS_RESULT result;
 *		 CMUtlHashEntry *pEntry = CAL_CMUtlHashSearch(&s_hashTable, "MyKey", strlen("MyKey") + 1, &result);
 *		 void *pBlock = pEntry->pData;				
 *
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CMUtilsHash')


/**
 * <category>Hash flag handling macros</category>
 * <element name="CMUTLHASH_SET_FLAG_KEY">Macro to set hash key type flags</element>
 * <element name="CMUTLHASH_GET_FLAG_KEY">Macro to get hash key type flags</element>
 */
#define CMUTLHASH_SET_FLAG_KEY(flags, keytype)	(flags = ((flags & 0xFFFFFF00) | keytype))
#define CMUTLHASH_GET_FLAG_KEY(flags)			(flags & 0x000000FF)

/**
 * <category>Hash entry flags</category>
 * <element name="CMUTLHASH_FLAG_KEY_INTEGER">Key type flag to specify a hash key as an integer</element>
 * <element name="CMUTLHASH_FLAG_KEY_STRING">Key type flag to specify a hash key as a string</element>
 * <element name="CMUTLHASH_FLAG_ALLOC_KEY">Flag to specify that the key is allocated dynamic from heap</element>
 * <element name="CMUTLHASH_FLAG_ALLOC_ENTRY">Flag to specify that the hash entry is allocated dynamic from heap</element>
 */
#define CMUTLHASH_FLAG_KEY_INTEGER				0x00000001
#define CMUTLHASH_FLAG_KEY_STRING				0x00000002

#define CMUTLHASH_FLAG_ALLOC_KEY				0x00000100
#define CMUTLHASH_FLAG_ALLOC_ENTRY				0x00000200

/**
 * <category>Hash table flags</category>
 * <element name="CMUTLHASH_FLAG_KEY_INTEGER">Key type flag to specify a hash key as an integer</element>
 * <element name="CMUTLHASH_FLAG_KEY_STRING">Key type flag to specify a hash key as a string</element>
 * <element name="CMUTLHASH_FLAG_ALLOC_KEY">Flag to specify that the key is allocated dynamic from heap</element>
 * <element name="CMUTLHASH_FLAG_ALLOC_ENTRY">Flag to specify that the hash entry is allocated dynamic from heap</element>
 */
#define CMUTLHASHTABLE_FLAG_ALLOC_TABLE			0x00000001


/**
 * <category>Hash key</category>
 * <description>
 *	Key value of a hash entry. Can be an integer or string key.
 * </description>
 * <element name="keyLen" type="IN">Key length in bytes</element>
 * <element name="integer" type="IN">Integer key is stored</element>
 * <element name="pString" type="IN">Pointer to string key</element>
 */
typedef struct CMUtlHaskKey_
{
	RTS_SIZE keyLen;
	union
	{
		RTS_SIZE integer;
		RTS_UI8 *pString;
	} type;
} CMUtlHaskKey;

/**
 * <category>Hash entry</category>
 * <description>
 *	Single hash entry of the hash table.
 * </description>
 * <element name="pData" type="IN">Pointer to data to store in hash entry</element>
 * <element name="key" type="IN">Corresponding unique key</element>
 * <element name="pNext" type="IN">Pointer to next element in linked list of the same hash entry (hash table collisions)</element>
 * <element name="flags" type="IN">Flags of the hash entry. See category "Hash entry flags" for details.</element>
 * <element name="_alignmentDummy" type="IN">Don't use. 8 byte alignment dummy.</element>
 */
typedef struct CMUtlHashEntry_
{
	void *pData;
	CMUtlHaskKey key;
	struct CMUtlHashEntry_ *pNext;
	RTS_UI32 flags;
	RTS_UI32 _alignmentDummy;
} CMUtlHashEntry;

/**
 * <category>Hash table</category>
 * <description>
 *	All entries of the hash table object are created and initialized in the CMUtlHashCreate() call!
 * </description>
 * <element name="hSync" type="IN">Handle to a synchronization object</element>
 * <element name="ppTable" type="IN">Pointer to the hash table buffer. Length must be (sNumHashEntries * sizeof(RTS_UI8 *))</element>
 * <element name="sNumHashEntries" type="IN">Lenght of the hash table respectively the number of elements that can be stored in the hash table without any collision</element>
 * <element name="pszComponentName" type="IN">Pointer to component name of the caller (which is generated typically in the macro COMPONENT_NAME)</element>
 * <element name="flagsTable" type="IN">Flags of the hash table. See category "Hash table flags" for details.</element>
 */
typedef struct CMUtlHashTable_
{
	RTS_HANDLE hSync;
	CMUtlHashEntry **ppTable;
	RTS_SIZE sNumHashEntries;
	char *pszComponentName; 
	RTS_UI32 flagsTable;	   
} CMUtlHashTable;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 *  Function to create a hash table.
 * </description>
 * <param name="pHashTable" type="INOUT">Pointer to a hash table object, which is filled by this function call!</param>
 * <param name="sNumHashEntries" type="IN">Lenght of the hash table respectively the number of elements that can be stored in the hash table without any collision.
 *		NOTE:
 *		Hash table is allocated on heap via SysMemAllocData() within this function. If you would like to provide a static memory for the hash table. Use CMUtlHashCreate2() instead!
 *      The number of available hash entries should be a prime number to get a nice spreading.
 * </param>
 * <param name="pszComponentName" type="IN">Pointer to component name of the caller (which is generated typically in the macro COMPONENT_NAME)</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Hash table could be created</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Invalid pointer or sHashTableLen is 0</errorcode> 
 * <errorcode name="RTS_RESULT Result" type="ERR_NOMEMORY">No memory to create the hash table</errorcode> 
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlHashCreate', `(CMUtlHashTable *pHashTable, RTS_SIZE sNumHashEntries, char *pszComponentName)')

/**
 * <description>
 *  Function to create a hash table with a specified hash buffer.
 * </description>
 * <param name="pHashTable" type="INOUT">Pointer to a hash table object, which is filled by this function</param>
 * <param name="sNumHashEntries" type="IN">Lenght of the hash table respectively the number of elements that can be stored in the hash table without any collision</param>
 * <param name="pHashTableBuffer" type="IN">Pointer to the hash table (can be static memory). Length must be (sNumHashEntries * sizeof(RTS_UI8 *))!.
 *		NOTE:
 *		If pHashTableBuffer = NULL. the hash table will be allocated on heap via SysMemAllocData() within this function.
 *      The number of available hash entries should be a prime number to get a nice spreading.
 * </param>
 * <param name="pszComponentName" type="IN">Pointer to component name of the caller (which is generated typically in the macro COMPONENT_NAME)</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Hash table could be created</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Invalid pointer or sHashTableLen is 0</errorcode> 
 * <errorcode name="RTS_RESULT Result" type="ERR_NOMEMORY">No memory to create the hash table</errorcode> 
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlHashCreate2', `(CMUtlHashTable *pHashTable, RTS_SIZE sNumHashEntries, RTS_UI8 *pHashTableBuffer, char *pszComponentName)')

/**
 * <description>
 *  Function to delete a hash table.
 * </description>
 * <param name="pHashTable" type="IN">Pointer to a hash table filled by CMUtlHashCreate() or CMUtlHashCreate2()</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Hash table could be deleted</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Invalid hash table pointer </errorcode> 
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Hash table could not be deleted</errorcode> 
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlHashDelete', `(CMUtlHashTable *pHashTable)')

/**
 * <description>
 *  Function to insert a new hash entry. New hash entry (CMUtlHashEntry) is allocated from heap via SysMemAllocData().
 *  Note: If the size of the key is equal or lower the register size of the architecture the key is directly used as hash.
 * </description>
 * <param name="pHashTable" type="IN">Pointer to a hash table filled by CMUtlHashCreate() or CMUtlHashCreate2()</param>
 * <param name="pKey" type="IN">Corresponding unique key. Can be an integer or string key.</param>
 * <param name="keyLen" type="IN">Key length in bytes</param>
 * <param name="bCopyKey" type="IN">Is only relevant for String key: TRUE=Key is allocated and coppied, FALSE=Only a reference to the key is hold!</param>
 * <param name="pData" type="IN">Pointer to data to store in hash entry</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Hash entry could be inserted</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Invalid hash table pointer</errorcode> 
 * <errorcode name="RTS_RESULT Result" type="ERR_NOMEMORY">Hash entry failed to insert because of insufficient memory</errorcode> 
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Hash entry failed to insert</errorcode> 
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlHashInsert', `(CMUtlHashTable *pHashTable, RTS_UI8 *pKey, RTS_SIZE keyLen, RTS_BOOL bCopyKey, void *pData)')

/**
 * <description>
 *  Function to insert a new hash entry.
 *  Note: If the size of the key is equal or lower the register size of the architecture the key is directly used as hash.
 * </description>
 * <param name="pHashTable" type="IN">Pointer to a hash table filled by CMUtlHashCreate() or CMUtlHashCreate2()</param>
 * <param name="pNewEntry" type="IN">Pointer to a new the hash entry memory object to be added in the hash table. Can be static memory. 
 *		If the pointer is NULL, a new hash entry (CMUtlHashEntry) is allocated from heap via SysMemAllocData().</param>
 * <param name="pKey" type="IN">Corresponding unique key. Can be an integer or string key.</param>
 * <param name="keyLen" type="IN">Key length in bytes</param>
 * <param name="bCopyKey" type="IN">Is only relevant for String key: TRUE=Key is allocated and coppied, FALSE=Only a reference to the key is hold!</param>
 * <param name="pData" type="IN">Pointer to data to store in hash entry</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Hash entry could be inserted</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Invalid hash table pointer</errorcode> 
 * <errorcode name="RTS_RESULT Result" type="ERR_NOMEMORY">Hash entry failed to insert because of insufficient memory</errorcode> 
 * <errorcode name="RTS_RESULT Result" type="ERR_FAILED">Hash entry failed to insert</errorcode> 
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlHashInsert2', `(CMUtlHashTable *pHashTable, CMUtlHashEntry *pNewEntry, RTS_UI8 *pKey, RTS_SIZE keyLen, RTS_BOOL bCopyKey, void *pData)')

/**
 * <description>
 *  Function to remove a hash entry specified by its entry pointer.
 * </description>
 * <param name="pHashTable" type="IN">Pointer to a hash table filled by CMUtlHashCreate() or CMUtlHashCreate2()</param>
 * <param name="pEntry" type="IN">Pointer to the hash entry retrieved by CMUtlHashSearch</param> 
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Hash entry could be removed</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Invalid hash table pointer or hash entry</errorcode> 
 * <errorcode name="RTS_RESULT Result" type="ERR_NO_OBJECT">Unknown hash entry</errorcode> 
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlHashRemove', `(CMUtlHashTable *pHashTable, CMUtlHashEntry *pEntry)')

/**
 * <description>
 *  Function to remove a hash entry specified by its key.
 * </description>
 * <param name="pHashTable" type="IN">Pointer to a hash table filled by CMUtlHashCreate() or CMUtlHashCreate2()</param>
 * <param name="pKey" type="IN">Corresponding unique key. Can be an integer or string key.</param>
 * <param name="keyLen" type="IN">Key length in bytes</param>
 * <errorcode name="RTS_RESULT Result" type="ERR_OK">Hash entry could be removed</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Invalid hash table pointer or hash entry</errorcode> 
 * <errorcode name="RTS_RESULT Result" type="ERR_NO_OBJECT">Unknown hash entry</errorcode> 
 * <result>error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `CMUtlHashRemove2', `(CMUtlHashTable *pHashTable, RTS_UI8 *pKey, RTS_SIZE keyLen)')

/**
 * <description>
 *  Function to search for an entry in the hash table. 
 *  Note: If the size of the key is equal or lower the register size of the architecture the key is directly used as hash.
 * </description>
 * <param name="pHashTable" type="IN">Pointer to a hash table object, which is filled by this function</param>
 * <param name="pKey" type="IN">Pointer to the key value toi search for the entry</param> 
 * <param name="keyLen" type="IN">Lenght of the key. If the key is a string, additionally the NUL termination character must be _included_ in the keylen!</param> 
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Hash entry could be found</errorcode>
 * <errorcode name="RTS_RESULT Result" type="ERR_PARAMETER">Invalid hash table pointer or pointer to key</errorcode> 
 * <errorcode name="RTS_RESULT pResult" type="ERR_NO_OBJECT">No hash entry matching to the key found</errorcode>
 * <result>Pointer to the hash entry or NULL if not found</result>
 */
DEF_ITF_API(`CMUtlHashEntry *', `CDECL', `CMUtlHashSearch', `(CMUtlHashTable *pHashTable, RTS_UI8 *pKey, RTS_SIZE keyLen, RTS_RESULT *pResult)')

#ifdef __cplusplus
}
#endif
