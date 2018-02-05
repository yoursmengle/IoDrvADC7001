/**
 * <interfacename>CAA_Storage</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`CmpCAAStorage')

#include "CAADefines.h"
#include "CAATypes.h"

/**
* <category>Compiler switch</category>
* <description>
*    Compiler switches to enable/disable single features in the component.
* </description>
* <element name="SQLITE_OS_OTHER">The option causes SQLite to omit its built-in operating system interfaces for Unix, Windows, and OS/2. The resulting component will have the CoDeSys RTS operating system interface.</element>
* <element name="SQLITE_THREADSAFE">This option controls whether or not code is included in SQLite to enable it to operate safely in a multithreaded environment. The default is SQLITE_THREADSAFE=1 which is safe for use in a multithreaded environment. When compiled with SQLITE_THREADSAFE=0 all mutexing code is omitted and it is unsafe to use SQLite in a multithreaded program. When compiled with SQLITE_THREADSAFE=2, SQLite can be used in a multithreaded program so long as no two threads attempt to use the same database connection at the same time.</element>
*/

/**
 * <category>Settings</category>
 * <description>Setting to disable the dynamic memory allocation if the memsys5 memory allocator runs out of memory. The following
 *	values are possible at the moment:
 *		o 1: Dynamic memory allocation by using SysMemAllocData is disabled
 *		o (all other values or if this setting does not exist): Dynamic memory allocation by using SysMemAllocData is active
 * </description>
 */
#define CMPCAASTORAGE_KEY_DISABLE_DYNAMIC_MEMORY_ALLOCATION					"DisableDynamicMemoryAllocation"
#ifndef CMPCAASTORAGE_VALUE_DISABLE_DYNAMIC_MEMORY_ALLOCATION_DEFAULT
	#define CMPCAASTORAGE_VALUE_DISABLE_DYNAMIC_MEMORY_ALLOCATION_DEFAULT	0
#endif

/**
 * <category>Settings</category>
 * <description>Setting defining the number of MB the memsys5 memory allocator uses.</description>
 */
#define CMPCAASTORAGE_KEY_MEMSYS5_MEMSIZE								"Memsys5SizeInMB"
#ifndef CMPCAASTORAGE_VALUE_MEMSYS5_DEFAULT
	#define CMPCAASTORAGE_VALUE_MEMSYS5_DEFAULT							3
#endif

/**
 * <category>Settings</category>
 * <description>Setting defining the maximum page size in KB of the database pages.</description>
 */
#define CMPCAASTORAGE_KEY_MAX_PAGE_SIZE									"MaxPageSize"
#ifndef CMPCAASTORAGE_VALUE_MAX_PAGE_SIZE_DEFAULT
	#define CMPCAASTORAGE_VALUE_MAX_PAGE_SIZE_DEFAULT					(8 * 1024)
#endif

/**
 * <category>Settings</category>
 * <description>Setting defining the maximum number of threads that concurrently access the CAAStorage component.</description>
 * <remarks>We assume for the default value, that we have not more than 4 threads using CAAStorage:
 * alarm storage, visualization, the trend recording task and a user task.</remarks>
 */
#define CMPCAASTORAGE_KEY_MAX_NUM_THREADS								"MaxNumThreads"
#ifndef CMPCAASTORAGE_VALUE_MAX_NUM_THREADS_DEFAULT
	#define CMPCAASTORAGE_VALUE_MAX_NUM_THREADS_DEFAULT					4
#endif

/**
 * <category>Settings</category>
 * <description>Setting defining the size in KB of a page-cache allocation.</description>
 */
#define CMPCAASTORAGE_KEY_PAGE_CACHE_ALLOCATION_SIZE					"PageCacheAllocationSize"
#ifndef CMPCAASTORAGE_VALUE_PAGE_CACHE_ALLOCATION_SIZE_DEFAULT
	#define CMPCAASTORAGE_VALUE_PAGE_CACHE_ALLOCATION_SIZE_DEFAULT		4096
#endif

/**
 * <category>Settings</category>
 * <description>Setting defining the maximum number of available page-cache allocations.</description>
 */
#define CMPCAASTORAGE_KEY_PAGE_CACHE_ALLOCATION_COUNT					"PageCacheAllocationCount"
#ifndef CMPCAASTORAGE_VALUE_PAGE_CACHE_ALLOCATION_COUNT_DEFAULT
	#define CMPCAASTORAGE_VALUE_PAGE_CACHE_ALLOCATION_COUNT_DEFAULT		512
#endif

typedef struct sti_column_tag* STI_COLUMN;
typedef struct sti_cursor_tag* STI_CURSOR;
typedef struct sti_row_tag* STI_ROW;
typedef struct sti_savepoint_tag* STI_SAVEPOINT;
typedef struct sti_storage_tag* STI_STORAGE;
typedef struct sti_table_tag* STI_TABLE;
typedef struct sti_transaction_tag* STI_TRANSACTION;

typedef CAA_STRING RTS_IEC_ISO8601[25];
typedef CAA_LINT RTS_IEC_INT64;
typedef CAA_LREAL RTS_IEC_REAL8;
typedef CAA_STRING STO_ISO8601[25];
typedef CAA_LINT STO_INT64;
typedef CAA_LREAL STO_REAL8;


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif


/*
 * required for proper struct alignment of 64bit member with Wind River VxWorks GNU compiler
 * ( defined in vxworks <sysdefines.h>, for all other OS'es "dummy" macro )  
 */
#ifndef VXWORKS_ALIGNATTRIB
#define VXWORKS_ALIGNATTRIB
#endif

/**
 * Each value stored in the storage has one of the following types
 */
#define STO_COLUMN_TYPE_UNKNOWN    0	/* The type of value is not known */
#define STO_COLUMN_TYPE_INTEGER    1	/* The value is a signed integer, stored in 1, 2, 3, 4, 6, or 8 bytes depending on the magnitude of the value */
#define STO_COLUMN_TYPE_FLOAT    2	/* The value is a floating point value, stored as an 8-byte IEEE floating point number */
#define STO_COLUMN_TYPE_TEXT    3	/* The value is a text string, stored using the storage encoding (UTF-8, UTF-16BE or UTF-16LE) */
#define STO_COLUMN_TYPE_BLOB    4	/* The value is a blob of data, stored exactly as it was input */
#define STO_COLUMN_TYPE_NULL    5	/* The value is a NULL value */
/* Typed enum definition */
#define STO_COLUMN_TYPE    RTS_IEC_INT

/**
 * The call of the CursorMove methode can set a cursor to a specific row.
 */
#define STO_DIRECTION_FIRST    0	/* Move the cursor to the first row */
#define STO_DIRECTION_NEXT    1	/* Move the cursor to the next row */
#define STO_DIRECTION_PREVIOUS    2	/* Move the cursor to the previous row */
#define STO_DIRECTION_LAST    3	/* Move the cursor to the last row */
/* Typed enum definition */
#define STO_DIRECTION    RTS_IEC_INT

/**
 * The Unicode Standard supports some character encoding forms: e.g. UTF-16 and UTF-8
 * Each encoding form maps the Unicode code points U+0000..U+D7FF and U+E000..U+10FFFF
 * to unique code unit sequences. This storage can handle the following encoding forms.
 * The actual form can be retrieved with the StorageEncoding property of IStorage.
 */
#define STO_ENCODING_UNKNOWN    0	/* The encoding form of the storage is not known */
#define STO_ENCODING_UTF8    1	/* The Unicode encoding form UTF-8 */
#define STO_ENCODING_UTF16BE    2	/* The Unicode encoding form UTF-16 big endian */
#define STO_ENCODING_UTF16LE    3	/* The Unicode encoding form UTF-16 big endian */
/* Typed enum definition */
#define STO_ENCODING    RTS_IEC_INT

/**
 * Every error output of a methode or function returns one of these error codes.
 */
#define STO_ERROR_NO_ERROR    0	
#define STO_ERROR_FIRST_ERROR    30400	
#define STO_ERROR_TIME_OUT    30401	
#define STO_ERROR_WRONG_PARAMETER    30402	
#define STO_ERROR_POOL_NO_MEMORY    30403	
#define STO_ERROR_POOL_NO_ENTRY    30404	
#define STO_ERROR_CURSOR_EOF    30405	/* Attempted to move the cursor beyond the last row resp. before the 1st row */
#define STO_ERROR_CURSOR_SEARCH_BEFORE    30406	/* Possible return values of the ICursor.CursorSearch_* methods with the meaning, */
#define STO_ERROR_CURSOR_SEARCH_AFTER    30407	/* that the value to search for was not found and the cursor's current position */
#define STO_ERROR_NOT_IMPLEMENTED    30408	/* This return value will be used in case of not implemented functionality */
#define STO_ERROR_SQLITE_ERROR    30431	/* (1) SQL error or missing database */
#define STO_ERROR_SQLITE_INTERNAL    30432	/* (2) Internal logic error in SQLite */
#define STO_ERROR_SQLITE_PERM    30433	/* (3) Access permission denied */
#define STO_ERROR_SQLITE_ABORT    30434	/* (4) Callback routine requested an abort */
#define STO_ERROR_SQLITE_BUSY    30435	/* (5) The database file is locked */
#define STO_ERROR_SQLITE_LOCKED    30436	/* (6) A table in the database is locked */
#define STO_ERROR_SQLITE_NOMEM    30437	/* (7) A malloc() failed */
#define STO_ERROR_SQLITE_READONLY    30438	/* (8) Attempt to write a readonly database */
#define STO_ERROR_SQLITE_INTERRUPT    30439	/* (9) Operation terminated by sqlite3_interrupt() */
#define STO_ERROR_SQLITE_IOERR    30440	/* (10) Some kind of disk I/O error occurred */
#define STO_ERROR_SQLITE_CORRUPT    30441	/* (11) The database disk image is malformed */
#define STO_ERROR_SQLITE_NOTFOUND    30442	/* (12) Unknown opcode in sqlite3_file_control() */
#define STO_ERROR_SQLITE_FULL    30443	/* (13) Insertion failed because database is full */
#define STO_ERROR_SQLITE_CANTOPEN    30444	/* (14) Unable TO open the database file */
#define STO_ERROR_SQLITE_PROTOCOL    30445	/* (15) Database lock protocol error */
#define STO_ERROR_SQLITE_EMPTY    30446	/* (16) Database is empty */
#define STO_ERROR_SQLITE_SCHEMA    30447	/* (17) The database schema changed */
#define STO_ERROR_SQLITE_TOOBIG    30448	/* (18) string or blob exceeds size limit */
#define STO_ERROR_SQLITE_CONSTRAINT    30449	/* (19) Abort due to constraint violation */
#define STO_ERROR_SQLITE_MISMATCH    30450	/* (20) Data type mismatch */
#define STO_ERROR_SQLITE_MISUSE    30451	/* (21) Library used incorrectly */
#define STO_ERROR_SQLITE_NOLFS    30452	/* (22) Uses OS features NOT supported on host */
#define STO_ERROR_SQLITE_AUTH    30453	/* (23) Authorization denied */
#define STO_ERROR_SQLITE_FORMAT    30454	/* (24) Auxiliary database format error */
#define STO_ERROR_SQLITE_RANGE    30455	/* (25) 2nd parameter to sqlite3_bind out of range */
#define STO_ERROR_SQLITE_NOTADB    30456	/* (26) File opened that is not a database file */
#define STO_ERROR_SQLITE_ROW    30530	/* (100) sqlite3_step() has another row ready */
#define STO_ERROR_SQLITE_DONE    30531	/* (101) sqlite3_step() has finished executing */
#define STO_ERROR_FIRST_MF    30535	
#define STO_ERROR_LAST_ERROR    30549	
/* Typed enum definition */
#define STO_ERROR    RTS_IEC_INT

/**
 * From the point of view of a single process, a storage can be in one of five locking states
 * Use the StorageLockingState property to retreive the actual state of the storage.
 * UNLOCKED: No locks are held on the database. The database may be neither read nor written.
 * Any internally cached data is considered suspect and subject to verification against the database file before being used.
 * Other processes can read or write the database as their own locking states permit. This is the default state.
 * SHARED: The database may be read but not written. Any number of processes can hold SHARED locks at the same time, hence there can be many simultaneous readers.
 * But no other thread or process is allowed to write to the database file while one or more SHARED locks are active.
 * A RESERVED lock means that the process is planning on writing to the database file at some point in the future but that it is currently just reading from the file.
 * Only a single RESERVED lock may be active at one time, though multiple SHARED locks can coexist with a single RESERVED lock.
 * RESERVED differs from PENDING in that new SHARED locks can be acquired while there is a RESERVED lock.
 * A PENDING lock means that the process holding the lock wants to write to the database as soon as possible and is just waiting
 * on all current SHARED locks to clear so that it can get an EXCLUSIVE lock. No new SHARED locks are permitted against the database if a PENDING lock is active,
 * though existing SHARED locks are allowed to continue.
 * An EXCLUSIVE lock is needed in order to write to the database file. Only one EXCLUSIVE lock is allowed on the file and no other locks
 * of any kind are allowed to coexist with an EXCLUSIVE lock. In order to maximize concurrency, SQLite works to minimize the amount of time that EXCLUSIVE locks are held.  
 */
#define STO_LOCKING_STATE_UNLOCKED    0	/* No locks are held on the Storage */
#define STO_LOCKING_STATE_SHARED    1	/* The storage may be read but not written */
#define STO_LOCKING_STATE_RESERVED    2	/* A process is planning on writing to the database file at some point in the future but that it is currently just reading from the file */
#define STO_LOCKING_STATE_PENDING    3	/* The process holding the lock wants to write to the database as soon as possible. */
#define STO_LOCKING_STATE_EXCLUSIVE    4	/* An EXCLUSIVE lock is needed in order to write to the database file */
/* Typed enum definition */
#define STO_LOCKING_STATE    RTS_IEC_INT

/**
 * <description>Enum: STO_PROC_CMD</description>
 */
#define STO_PROC_CMD_NONE    0	
#define STO_PROC_CMD_EXECUTE    1	
#define STO_PROC_CMD_ABORT    2	
/* Typed enum definition */
#define STO_PROC_CMD    RTS_IEC_INT

/**
 * <description>Enum: STO_PROC_STATE</description>
 */
#define STO_PROC_STATE_DORMAND    0	
#define STO_PROC_STATE_BUSY    1	
#define STO_PROC_STATE_DONE    2	
#define STO_PROC_STATE_ABORTED    3	
#define STO_PROC_STATE_ERROR    4	
/* Typed enum definition */
#define STO_PROC_STATE    RTS_IEC_INT

/**
 * A Transactions can be deferred, immediate, or exclusive.
 * The default transaction behavior is deferred.
 * Deferred means that no locks are acquired on the storage until the storage is first accessed.
 * Thus with a deferred transaction, the TransactionBegin methode itself does nothing to the filesystem.
 * Locks are not acquired until the first read or write operation.
 * The first read operation against a storage creates a SHARED lock and the first write operation creates a RESERVED lock.
 * Because the acquisition of locks is deferred until they are needed, it is possible that another thread or process could create a separate transaction
 * and write to the storage after the TransactionBegin on the current thread has executed.
 * If the transaction is immediate, then RESERVED locks are acquired on the storage as soon as the TransactionBegin command is executed,
 * without waiting for the storage to be used.
 * After a TransactionBegin IMMEDIATE, no other storage connection will be able to write to the storage or do a TransactionBegin IMMEDIATE or TransactionBegin EXCLUSIVE.
 * Other processes can continue to read from the database, however.
 * An exclusive transaction causes EXCLUSIVE locks to be acquired on the storage.
 * After a TransactionBegin EXCLUSIVE, no other storage connection will be able to read the storage and no other connection will be able to write the storage
 * until the transaction is complete. 
 */
#define STO_TRANSACTION_MODE_DEFERRED    0	/* Locks are not acquired until the first read or write operation */
#define STO_TRANSACTION_MODE_IMMEDIATE    1	/* No other connection will be able to write */
#define STO_TRANSACTION_MODE_EXCLUSIVE    2	/* No other connection will be able to read or write */
/* Typed enum definition */
#define STO_TRANSACTION_MODE    RTS_IEC_INT

/**
 * This data type is the internal representation of text, that is used in CmpCAAStorage.
 * If the text from a column is retrieved this type will be returned and if the user wants
 * to set the text of a column (both for insert and update the method IRowBase.ColumnSet_TEXT
 * has to be used) or to search within a text column this type has to be passed to the database.
 *
 * - For reading the text value of a column the TEXT variable has to be converted into a STRING
 *   or into a WSTRING (using the functions |TextCopyToString| or |TextCopyToWString|).
 * - For setting the text of a column or for searching a text the functions |CreateTextFromString| 
 *   and |CreateTextFromWString| allow to create a TEXT variable.
 * - After using the TEXT the variable (that has been previously created by functions |CreateTextFromString| 
 *   or |CreateTextFromWString|) it has to be freed with function |TextFree|
 */
typedef struct tagSTO_TEXT
{
	RTS_IEC_BYTE *pbyData;
} STO_TEXT;

/**
 * This data type is not intend to instantiate
 * Please use BlobAlloc and BlobFree for handling
 */
typedef struct tagSTO_BLOB
{
	CAA_SIZE szData;
	RTS_IEC_BYTE *pbyData;
} STO_BLOB;

/**
 * The size of the storage can be calculated with this metrics
 * storage size = page size * (used pages + free pages)
 * The relationship metwen used and free pages give a messure about the fragmentation
 * After a call of StorageReorg the number of free pages should be zero.
 */
typedef struct tagSTO_METRICS
{
	CAA_SIZE szPage;
	CAA_COUNT ctUsedPages;
	CAA_COUNT ctFreePages;
} STO_METRICS;

/**
 * <description>sto_bloballoc</description>
 */
typedef struct tagsto_bloballoc_struct
{
	CAA_SIZE szData;					/* VAR_INPUT */	
	STO_BLOB *STO_BlobAlloc;			/* VAR_OUTPUT */	/* pBlob */
	CAA_ERROR eError;					/* VAR_OUTPUT */	
} sto_bloballoc_struct;

DEF_API(`void',`CDECL',`sto_bloballoc',`(sto_bloballoc_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x721BFA71),0x03050528)

/**
 * <description>sto_blobcopytodata</description>
 */
typedef struct tagsto_blobcopytodata_struct
{
	STO_BLOB *pBlob;					/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	CAA_SIZE szData;					/* VAR_INPUT */	
	CAA_ERROR STO_BlobCopyToData;		/* VAR_OUTPUT */	/* eError */
} sto_blobcopytodata_struct;

DEF_API(`void',`CDECL',`sto_blobcopytodata',`(sto_blobcopytodata_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x59171DAD),0x03050528)

/**
 * <description>sto_blobfree</description>
 */
typedef struct tagsto_blobfree_struct
{
	STO_BLOB *pBlob;					/* VAR_INPUT */	
	CAA_ERROR STO_BlobFree;				/* VAR_OUTPUT */	/* eError */
} sto_blobfree_struct;

DEF_API(`void',`CDECL',`sto_blobfree',`(sto_blobfree_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x677BB3A1),0x03050528)

/**
 * See documentation of type TEXT how to use the TEXT type.
 */
typedef struct tagsto_createtextfromstring_struct
{
	RTS_IEC_STRING *sValue;			/* VAR_IN_OUT */	
	STO_TEXT *txtValue;					/* VAR_IN_OUT */	
	CAA_ERROR STO_CreateTextFromString;	/* VAR_OUTPUT */	
} sto_createtextfromstring_struct;

DEF_API(`void',`CDECL',`sto_createtextfromstring',`(sto_createtextfromstring_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x37C64BDF),0x03050528)

/**
 * See documentation of type TEXT how to use the TEXT type.
 */
typedef struct tagsto_createtextfromwstring_struct
{
	RTS_IEC_WSTRING *wsValue;		/* VAR_IN_OUT */	
	STO_TEXT *txtValue;					/* VAR_IN_OUT */	
	CAA_ERROR STO_CreateTextFromWString;	/* VAR_OUTPUT */	
} sto_createtextfromwstring_struct;

DEF_API(`void',`CDECL',`sto_createtextfromwstring',`(sto_createtextfromwstring_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xAB9B0731),0x03050528)

/**
 * <description>sto_datacopytoblob</description>
 */
typedef struct tagsto_datacopytoblob_struct
{
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	CAA_SIZE szData;					/* VAR_INPUT */	
	STO_BLOB *pBlob;					/* VAR_INPUT */	
	CAA_ERROR STO_DataCopyToBlob;		/* VAR_OUTPUT */	/* eError */
} sto_datacopytoblob_struct;

DEF_API(`void',`CDECL',`sto_datacopytoblob',`(sto_datacopytoblob_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x8574D63E),0x03050528)

/**
 * <description>sto_dt_to_int64</description>
 */
typedef struct tagsto_dt_to_int64_struct
{
	RTS_IEC_DATE_AND_TIME dtValue;		/* VAR_INPUT */	
	CAA_ERROR STO_DT_TO_INT64;			/* VAR_OUTPUT */	
	RTS_IEC_INT64 i64Value;				/* VAR_OUTPUT */	
} sto_dt_to_int64_struct;

DEF_API(`void',`CDECL',`sto_dt_to_int64',`(sto_dt_to_int64_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x82DE9C22),0x03050528)

/**
 * <description>sto_dt_to_iso8601</description>
 */
typedef struct tagsto_dt_to_iso8601_struct
{
	RTS_IEC_DATE_AND_TIME dtValue;		/* VAR_INPUT */	
	RTS_IEC_ISO8601 *sValue;			/* VAR_IN_OUT */	
	CAA_ERROR STO_DT_TO_ISO8601;		/* VAR_OUTPUT */	
} sto_dt_to_iso8601_struct;

DEF_API(`void',`CDECL',`sto_dt_to_iso8601',`(sto_dt_to_iso8601_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x02D9A7F6),0x03050528)

/**
 * <description>sto_dt_to_real8</description>
 */
typedef struct tagsto_dt_to_real8_struct
{
	RTS_IEC_DATE_AND_TIME dtValue;		/* VAR_INPUT */	
	CAA_ERROR STO_DT_TO_REAL8;			/* VAR_OUTPUT */	
	RTS_IEC_REAL8 r8Value;				/* VAR_OUTPUT */	
} sto_dt_to_real8_struct;

DEF_API(`void',`CDECL',`sto_dt_to_real8',`(sto_dt_to_real8_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x7A40F574),0x03050528)

/**
 * <description>sto_getsupplierversion</description>
 */
typedef struct tagsto_getsupplierversion_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	RTS_IEC_WORD STO_GetSupplierVersion;	/* VAR_OUTPUT */	
} sto_getsupplierversion_struct;

DEF_API(`void',`CDECL',`sto_getsupplierversion',`(sto_getsupplierversion_struct *p)',1,0x26CD734B,0x03050528)

/**
 * <description>sto_int64_to_dt</description>
 */
typedef struct tagsto_int64_to_dt_struct
{
	RTS_IEC_INT64 i64Value;				/* VAR_INPUT */	
	CAA_ERROR STO_INT64_TO_DT;			/* VAR_OUTPUT */	
	RTS_IEC_DATE_AND_TIME dtValue;		/* VAR_OUTPUT */	
} sto_int64_to_dt_struct;

DEF_API(`void',`CDECL',`sto_int64_to_dt',`(sto_int64_to_dt_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC04F4CAE),0x03050528)

/**
 * ISO8601 string ("YYYY-MM-DD HH:MM:SS.SSS")
 */
typedef struct tagsto_int64_to_iso8601_struct
{
	RTS_IEC_INT64 i64Value;				/* VAR_INPUT */	
	RTS_IEC_ISO8601 *sValue;			/* VAR_IN_OUT */	
	CAA_ERROR STO_INT64_TO_ISO8601;		/* VAR_OUTPUT */	
} sto_int64_to_iso8601_struct;

DEF_API(`void',`CDECL',`sto_int64_to_iso8601',`(sto_int64_to_iso8601_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x5764574C),0x03050528)

/**
 * <description>sto_int64_to_localtime</description>
 */
typedef struct tagsto_int64_to_localtime_struct
{
	RTS_IEC_INT64 i64UTC;				/* VAR_INPUT */	
	CAA_ERROR STO_INT64_TO_LOCALTIME;	/* VAR_OUTPUT */	
	RTS_IEC_INT64 i64Local;				/* VAR_OUTPUT */	
} sto_int64_to_localtime_struct;

DEF_API(`void',`CDECL',`sto_int64_to_localtime',`(sto_int64_to_localtime_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x7ED9A18B),0x03050528)

/**
 * <description>sto_int64_to_ltime</description>
 */
typedef struct tagsto_int64_to_ltime_struct
{
	RTS_IEC_INT64 i64Value;				/* VAR_INPUT */	
	CAA_ERROR STO_INT64_TO_LTIME;		/* VAR_OUTPUT */	
	RTS_IEC_LTIME ltValue;				/* VAR_OUTPUT */	
} sto_int64_to_ltime_struct;

DEF_API(`void',`CDECL',`sto_int64_to_ltime',`(sto_int64_to_ltime_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x56E5A814),0x03050528)

/**
 * <description>sto_int64_to_real8</description>
 */
typedef struct tagsto_int64_to_real8_struct
{
	RTS_IEC_INT64 i64Value;				/* VAR_INPUT */	
	CAA_ERROR STO_INT64_TO_REAL8;		/* VAR_OUTPUT */	
	RTS_IEC_REAL8 r8Value;				/* VAR_OUTPUT */	
} sto_int64_to_real8_struct;

DEF_API(`void',`CDECL',`sto_int64_to_real8',`(sto_int64_to_real8_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD54A069D),0x03050528)

/**
 * <description>sto_int64_to_time</description>
 */
typedef struct tagsto_int64_to_time_struct
{
	RTS_IEC_INT64 i64Value;				/* VAR_INPUT */	
	CAA_ERROR STO_INT64_TO_TIME;		/* VAR_OUTPUT */	
	RTS_IEC_TIME tValue;				/* VAR_OUTPUT */	
} sto_int64_to_time_struct;

DEF_API(`void',`CDECL',`sto_int64_to_time',`(sto_int64_to_time_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4AF215D2),0x03050528)

/**
 * <description>sto_int64_to_utc</description>
 */
typedef struct tagsto_int64_to_utc_struct
{
	RTS_IEC_INT64 i64Local;				/* VAR_INPUT */	
	CAA_ERROR STO_INT64_TO_UTC;			/* VAR_OUTPUT */	
	RTS_IEC_INT64 i64UTC;				/* VAR_OUTPUT */	
} sto_int64_to_utc_struct;

DEF_API(`void',`CDECL',`sto_int64_to_utc',`(sto_int64_to_utc_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC06DAE79),0x03050528)

/**
 * <description>sto_iso8601_to_dt</description>
 */
typedef struct tagsto_iso8601_to_dt_struct
{
	RTS_IEC_ISO8601 *sValue;			/* VAR_IN_OUT */	
	CAA_ERROR STO_ISO8601_TO_DT;		/* VAR_OUTPUT */	
	RTS_IEC_DATE_AND_TIME dtValue;		/* VAR_OUTPUT */	
} sto_iso8601_to_dt_struct;

DEF_API(`void',`CDECL',`sto_iso8601_to_dt',`(sto_iso8601_to_dt_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB3451243),0x03050528)

/**
 * <description>sto_iso8601_to_ltime</description>
 */
typedef struct tagsto_iso8601_to_ltime_struct
{
	RTS_IEC_ISO8601 *sValue;			/* VAR_IN_OUT */	
	CAA_ERROR STO_ISO8601_TO_LTIME;		/* VAR_OUTPUT */	
	RTS_IEC_LTIME ltValue;				/* VAR_OUTPUT */	
} sto_iso8601_to_ltime_struct;

DEF_API(`void',`CDECL',`sto_iso8601_to_ltime',`(sto_iso8601_to_ltime_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF799E666),0x03050528)

/**
 * <description>sto_iso8601_to_time</description>
 */
typedef struct tagsto_iso8601_to_time_struct
{
	RTS_IEC_ISO8601 *sValue;			/* VAR_IN_OUT */	
	CAA_ERROR STO_ISO8601_TO_TIME;		/* VAR_OUTPUT */	
	RTS_IEC_TIME tValue;				/* VAR_OUTPUT */	
} sto_iso8601_to_time_struct;

DEF_API(`void',`CDECL',`sto_iso8601_to_time',`(sto_iso8601_to_time_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4BAEA34F),0x03050528)

/**
 * <description>sto_ltime_to_int64</description>
 */
typedef struct tagsto_ltime_to_int64_struct
{
	RTS_IEC_LTIME ltValue;				/* VAR_INPUT */	
	CAA_ERROR STO_LTIME_TO_INT64;		/* VAR_OUTPUT */	
	RTS_IEC_INT64 i64Value;				/* VAR_OUTPUT */	
} sto_ltime_to_int64_struct;

DEF_API(`void',`CDECL',`sto_ltime_to_int64',`(sto_ltime_to_int64_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0C7C50F6),0x03050528)

/**
 * <description>sto_ltime_to_iso8601</description>
 */
typedef struct tagsto_ltime_to_iso8601_struct
{
	RTS_IEC_LTIME ltValue;				/* VAR_INPUT */	
	RTS_IEC_ISO8601 *sValue;			/* VAR_IN_OUT */	
	CAA_ERROR STO_LTIME_TO_ISO8601;		/* VAR_OUTPUT */	
} sto_ltime_to_iso8601_struct;

DEF_API(`void',`CDECL',`sto_ltime_to_iso8601',`(sto_ltime_to_iso8601_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB4C1298B),0x03050528)

/**
 * <description>sto_ltime_to_real8</description>
 */
typedef struct tagsto_ltime_to_real8_struct
{
	RTS_IEC_LTIME ltValue;				/* VAR_INPUT */	
	CAA_ERROR STO_LTIME_TO_REAL8;		/* VAR_OUTPUT */	
	RTS_IEC_LREAL lrValue;				/* VAR_OUTPUT */	
} sto_ltime_to_real8_struct;

DEF_API(`void',`CDECL',`sto_ltime_to_real8',`(sto_ltime_to_real8_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x86C0BF51),0x03050528)

/**
 * <description>sto_real8_to_dt</description>
 */
typedef struct tagsto_real8_to_dt_struct
{
	RTS_IEC_REAL8 r8Value;				/* VAR_INPUT */	
	CAA_ERROR STO_REAL8_TO_DT;			/* VAR_OUTPUT */	
	RTS_IEC_DATE_AND_TIME dtValue;		/* VAR_OUTPUT */	
} sto_real8_to_dt_struct;

DEF_API(`void',`CDECL',`sto_real8_to_dt',`(sto_real8_to_dt_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x185C3263),0x03050528)

/**
 * <description>sto_real8_to_ltime</description>
 */
typedef struct tagsto_real8_to_ltime_struct
{
	RTS_IEC_REAL8 r8Value;				/* VAR_INPUT */	
	CAA_ERROR STO_REAL8_TO_LTIME;		/* VAR_OUTPUT */	
	RTS_IEC_LTIME ltValue;				/* VAR_OUTPUT */	
} sto_real8_to_ltime_struct;

DEF_API(`void',`CDECL',`sto_real8_to_ltime',`(sto_real8_to_ltime_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF1247EEF),0x03050528)

/**
 * <description>sto_real8_to_time</description>
 */
typedef struct tagsto_real8_to_time_struct
{
	RTS_IEC_REAL8 r8Value;				/* VAR_INPUT */	
	CAA_ERROR STO_REAL8_TO_TIME;		/* VAR_OUTPUT */	
	RTS_IEC_TIME tValue;				/* VAR_OUTPUT */	
} sto_real8_to_time_struct;

DEF_API(`void',`CDECL',`sto_real8_to_time',`(sto_real8_to_time_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x2C257042),0x03050528)

/**
 * Deletes a database. The return value contains a CmpError.ERROR value indicating
 * the success of the operation.
 */
typedef struct tagsto_deletefile_struct
{
	CAA_FILENAME *sPath;				/* VAR_IN_OUT */	/* The filename of the database to delete */
	CAA_ERROR STO_DeleteFile;			/* VAR_OUTPUT */	
} sto_deletefile_struct;

DEF_API(`void',`CDECL',`sto_deletefile',`(sto_deletefile_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x525CF376),0x03050528)

/**
 * See documentation of type TEXT how to use the TEXT type.
 */
typedef struct tagsto_textcopytostring_struct
{
	CAA_BOOL xFree;						/* VAR_INPUT */	
	STO_TEXT *txtValue;					/* VAR_IN_OUT */	
	RTS_IEC_STRING *sValue;			/* VAR_IN_OUT */	
	CAA_SIZE *szValue;					/* VAR_IN_OUT */	
	CAA_ERROR STO_TextCopyToString;		/* VAR_OUTPUT */	/* eError */
} sto_textcopytostring_struct;

DEF_API(`void',`CDECL',`sto_textcopytostring',`(sto_textcopytostring_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x77472764),0x03050528)

/**
 * See documentation of type TEXT how to use the TEXT type.
 */
typedef struct tagsto_textcopytowstring_struct
{
	CAA_BOOL xFree;						/* VAR_INPUT */	
	STO_TEXT *txtValue;					/* VAR_IN_OUT */	
	RTS_IEC_WSTRING *wsValue;		/* VAR_IN_OUT */	
	CAA_SIZE *szValue;					/* VAR_IN_OUT */	
	CAA_ERROR STO_TextCopyToWString;	/* VAR_OUTPUT */	/* eError */
} sto_textcopytowstring_struct;

DEF_API(`void',`CDECL',`sto_textcopytowstring',`(sto_textcopytowstring_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA8659036),0x03050528)

/**
 * See documentation of type TEXT how to use the TEXT type.
 */
typedef struct tagsto_textfree_struct
{
	STO_TEXT *txtValue;					/* VAR_IN_OUT */	
	CAA_ERROR STO_TextFree;				/* VAR_OUTPUT */	
} sto_textfree_struct;

DEF_API(`void',`CDECL',`sto_textfree',`(sto_textfree_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x76615FAC),0x03050528)

/**
 * <description>sto_time_to_int64</description>
 */
typedef struct tagsto_time_to_int64_struct
{
	RTS_IEC_TIME tValue;				/* VAR_INPUT */	
	CAA_ERROR STO_TIME_TO_INT64;		/* VAR_OUTPUT */	
	RTS_IEC_INT64 i64Value;				/* VAR_OUTPUT */	
} sto_time_to_int64_struct;

DEF_API(`void',`CDECL',`sto_time_to_int64',`(sto_time_to_int64_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF7F2035E),0x03050528)

/**
 * <description>sto_time_to_iso8601</description>
 */
typedef struct tagsto_time_to_iso8601_struct
{
	RTS_IEC_TIME tValue;				/* VAR_INPUT */	
	RTS_IEC_ISO8601 *sValue;			/* VAR_IN_OUT */	
	CAA_ERROR STO_TIME_TO_ISO8601;		/* VAR_OUTPUT */	
} sto_time_to_iso8601_struct;

DEF_API(`void',`CDECL',`sto_time_to_iso8601',`(sto_time_to_iso8601_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1B53667A),0x03050528)

/**
 * <description>sto_time_to_real8</description>
 */
typedef struct tagsto_time_to_real8_struct
{
	RTS_IEC_TIME tValue;				/* VAR_INPUT */	
	CAA_ERROR STO_TIME_TO_REAL8;		/* VAR_OUTPUT */	
	RTS_IEC_REAL8 r8Value;				/* VAR_OUTPUT */	
} sto_time_to_real8_struct;

DEF_API(`void',`CDECL',`sto_time_to_real8',`(sto_time_to_real8_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x9AE7381B),0x03050528)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/



/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columngetblob_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	STO_BLOB *blobValue;				/* VAR_IN_OUT */	
	RTS_IEC_INT STI_ColumnGetBLOB;		/* VAR_OUTPUT, Enum: ERROR */
	RTS_IEC_BOOL xNULL;					/* VAR_OUTPUT */	
} sti_columngetblob_struct;

DEF_API(`void',`CDECL',`sti_columngetblob',`(sti_columngetblob_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB97B2BA2),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columngetint16_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	RTS_IEC_INT STI_ColumnGetINT16;		/* VAR_OUTPUT, Enum: ERROR */
	RTS_IEC_INT iValue;					/* VAR_OUTPUT */	
	RTS_IEC_BOOL xNULL;					/* VAR_OUTPUT */	
} sti_columngetint16_struct;

DEF_API(`void',`CDECL',`sti_columngetint16',`(sti_columngetint16_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x97DC91C7),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columngetint32_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	RTS_IEC_INT STI_ColumnGetINT32;		/* VAR_OUTPUT, Enum: ERROR */
	RTS_IEC_DINT diValue;				/* VAR_OUTPUT */	
	RTS_IEC_BOOL xNULL;					/* VAR_OUTPUT */	
} sti_columngetint32_struct;

DEF_API(`void',`CDECL',`sti_columngetint32',`(sti_columngetint32_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA00093D8),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columngetint64_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	RTS_IEC_INT STI_ColumnGetINT64;		/* VAR_OUTPUT, Enum: ERROR */
	RTS_IEC_LINT liValue VXWORKS_ALIGNATTRIB;	/* VAR_OUTPUT */	
	RTS_IEC_BOOL xNULL;					/* VAR_OUTPUT */	
} sti_columngetint64_struct;

DEF_API(`void',`CDECL',`sti_columngetint64',`(sti_columngetint64_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x6F0701A6),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columngetint8_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	RTS_IEC_INT STI_ColumnGetINT8;		/* VAR_OUTPUT, Enum: ERROR */
	RTS_IEC_SINT siValue;				/* VAR_OUTPUT */	
	RTS_IEC_BOOL xNULL;					/* VAR_OUTPUT */	
} sti_columngetint8_struct;

DEF_API(`void',`CDECL',`sti_columngetint8',`(sti_columngetint8_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD764B7BA),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columngetreal4_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	RTS_IEC_INT STI_ColumnGetREAL4;		/* VAR_OUTPUT, Enum: ERROR */
	RTS_IEC_REAL rValue;				/* VAR_OUTPUT */	
	RTS_IEC_BOOL xNULL;					/* VAR_OUTPUT */	
} sti_columngetreal4_struct;

DEF_API(`void',`CDECL',`sti_columngetreal4',`(sti_columngetreal4_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x42BD9968),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columngetreal8_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	RTS_IEC_INT STI_ColumnGetREAL8;		/* VAR_OUTPUT, Enum: ERROR */
	RTS_IEC_LREAL lrValue;				/* VAR_OUTPUT */	
	RTS_IEC_BOOL xNULL;					/* VAR_OUTPUT */	
} sti_columngetreal8_struct;

DEF_API(`void',`CDECL',`sti_columngetreal8',`(sti_columngetreal8_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD317D94F),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columngettext_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	STO_TEXT *txtValue;					/* VAR_IN_OUT */	
	RTS_IEC_INT STI_ColumnGetTEXT;		/* VAR_OUTPUT, Enum: ERROR */
	RTS_IEC_BOOL xNULL;					/* VAR_OUTPUT */	
} sti_columngettext_struct;

DEF_API(`void',`CDECL',`sti_columngettext',`(sti_columngettext_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF479FDE3),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columngettype_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	RTS_IEC_INT STI_ColumnGetType;		/* VAR_OUTPUT, Enum: COLUMN_TYPE */
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_columngettype_struct;

DEF_API(`void',`CDECL',`sti_columngettype',`(sti_columngettype_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF48C90AA),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columnsetblob_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	STO_BLOB *blobValue;				/* VAR_IN_OUT */	
	RTS_IEC_INT STI_ColumnSetBLOB;		/* VAR_OUTPUT, Enum: ERROR */
} sti_columnsetblob_struct;

DEF_API(`void',`CDECL',`sti_columnsetblob',`(sti_columnsetblob_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x00CA4524),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columnsetint16_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	RTS_IEC_INT iValue;					/* VAR_INPUT */	
	RTS_IEC_INT STI_ColumnSetINT16;		/* VAR_OUTPUT, Enum: ERROR */
} sti_columnsetint16_struct;

DEF_API(`void',`CDECL',`sti_columnsetint16',`(sti_columnsetint16_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA2F90964),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columnsetint32_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	RTS_IEC_DINT diValue;				/* VAR_INPUT */	
	RTS_IEC_INT STI_ColumnSetINT32;		/* VAR_OUTPUT, Enum: ERROR */
} sti_columnsetint32_struct;

DEF_API(`void',`CDECL',`sti_columnsetint32',`(sti_columnsetint32_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD8641CB9),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columnsetint64_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	RTS_IEC_LINT liValue;				/* VAR_INPUT */	
	RTS_IEC_INT STI_ColumnSetINT64;		/* VAR_OUTPUT, Enum: ERROR */
} sti_columnsetint64_struct;

DEF_API(`void',`CDECL',`sti_columnsetint64',`(sti_columnsetint64_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x17638EC7),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columnsetint8_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	RTS_IEC_SINT siValue;				/* VAR_INPUT */	
	RTS_IEC_INT STI_ColumnSetINT8;		/* VAR_OUTPUT, Enum: ERROR */
} sti_columnsetint8_struct;

DEF_API(`void',`CDECL',`sti_columnsetint8',`(sti_columnsetint8_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x06E3E872),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columnsetnull_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	RTS_IEC_INT STI_ColumnSetNULL;		/* VAR_OUTPUT, Enum: ERROR */
} sti_columnsetnull_struct;

DEF_API(`void',`CDECL',`sti_columnsetnull',`(sti_columnsetnull_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x9543CD3B),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columnsetreal4_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	RTS_IEC_REAL rValue;				/* VAR_INPUT */	
	RTS_IEC_INT STI_ColumnSetREAL4;		/* VAR_OUTPUT, Enum: ERROR */
} sti_columnsetreal4_struct;

DEF_API(`void',`CDECL',`sti_columnsetreal4',`(sti_columnsetreal4_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x779801CB),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columnsetreal8_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	RTS_IEC_LREAL lrValue;				/* VAR_INPUT */	
	RTS_IEC_INT STI_ColumnSetREAL8;		/* VAR_OUTPUT, Enum: ERROR */
} sti_columnsetreal8_struct;

DEF_API(`void',`CDECL',`sti_columnsetreal8',`(sti_columnsetreal8_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xAB73562E),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columnsettext_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	STO_TEXT *txtValue;					/* VAR_IN_OUT */	
	RTS_IEC_INT STI_ColumnSetTEXT;		/* VAR_OUTPUT, Enum: ERROR */
} sti_columnsettext_struct;

DEF_API(`void',`CDECL',`sti_columnsettext',`(sti_columnsettext_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCEED85C7),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columnupdateblob_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	STO_BLOB *blobValue;				/* VAR_IN_OUT */	
	RTS_IEC_BOOL *xNULL;				/* VAR_IN_OUT */	
	RTS_IEC_INT STI_ColumnUpdateBLOB;	/* VAR_OUTPUT, Enum: ERROR */
} sti_columnupdateblob_struct;

DEF_API(`void',`CDECL',`sti_columnupdateblob',`(sti_columnupdateblob_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD0C54666),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columnupdateint16_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	RTS_IEC_INT *iValue;				/* VAR_IN_OUT */	
	RTS_IEC_BOOL *xNULL;				/* VAR_IN_OUT */	
	RTS_IEC_INT STI_ColumnUpdateINT16;	/* VAR_OUTPUT, Enum: ERROR */
} sti_columnupdateint16_struct;

DEF_API(`void',`CDECL',`sti_columnupdateint16',`(sti_columnupdateint16_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x8AA90839),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columnupdateint32_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	RTS_IEC_DINT *diValue;				/* VAR_IN_OUT */	
	RTS_IEC_BOOL *xNULL;				/* VAR_IN_OUT */	
	RTS_IEC_INT STI_ColumnUpdateINT32;	/* VAR_OUTPUT, Enum: ERROR */
} sti_columnupdateint32_struct;

DEF_API(`void',`CDECL',`sti_columnupdateint32',`(sti_columnupdateint32_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xAAC20335),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columnupdateint64_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	RTS_IEC_LINT *liValue;				/* VAR_IN_OUT */	
	RTS_IEC_BOOL *xNULL;				/* VAR_IN_OUT */	
	RTS_IEC_INT STI_ColumnUpdateINT64;	/* VAR_OUTPUT, Enum: ERROR */
} sti_columnupdateint64_struct;

DEF_API(`void',`CDECL',`sti_columnupdateint64',`(sti_columnupdateint64_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC95AE06D),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columnupdateint8_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	RTS_IEC_SINT *siValue;				/* VAR_IN_OUT */	
	RTS_IEC_BOOL *xNULL;				/* VAR_IN_OUT */	
	RTS_IEC_INT STI_ColumnUpdateINT8;	/* VAR_OUTPUT, Enum: ERROR */
} sti_columnupdateint8_struct;

DEF_API(`void',`CDECL',`sti_columnupdateint8',`(sti_columnupdateint8_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xDD539E10),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columnupdatereal4_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	RTS_IEC_REAL *rValue;				/* VAR_IN_OUT */	
	RTS_IEC_BOOL *xNULL;				/* VAR_IN_OUT */	
	RTS_IEC_INT STI_ColumnUpdateREAL4;	/* VAR_OUTPUT, Enum: ERROR */
} sti_columnupdatereal4_struct;

DEF_API(`void',`CDECL',`sti_columnupdatereal4',`(sti_columnupdatereal4_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCD7B75E2),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columnupdatereal8_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	RTS_IEC_LREAL *lrValue;				/* VAR_IN_OUT */	
	RTS_IEC_BOOL *xNULL;				/* VAR_IN_OUT */	
	RTS_IEC_INT STI_ColumnUpdateREAL8;	/* VAR_OUTPUT, Enum: ERROR */
} sti_columnupdatereal8_struct;

DEF_API(`void',`CDECL',`sti_columnupdatereal8',`(sti_columnupdatereal8_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1F53A007),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columnupdatetext_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	STO_TEXT *txtValue;					/* VAR_IN_OUT */	
	RTS_IEC_BOOL *xNULL;				/* VAR_IN_OUT */	
	RTS_IEC_INT STI_ColumnUpdateTEXT;	/* VAR_OUTPUT, Enum: ERROR */
} sti_columnupdatetext_struct;

DEF_API(`void',`CDECL',`sti_columnupdatetext',`(sti_columnupdatetext_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1E881E83),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorclose_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_INT STI_CursorClose;		/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorclose_struct;

DEF_API(`void',`CDECL',`sti_cursorclose',`(sti_cursorclose_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x2D38F773),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorgetcurrentrow_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_XWORD STI_CursorGetCurrentRow;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorgetcurrentrow_struct;

DEF_API(`void',`CDECL',`sti_cursorgetcurrentrow',`(sti_cursorgetcurrentrow_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x4FE7BC05),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorgetindexid_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_DWORD STI_CursorGetIndexId;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorgetindexid_struct;

DEF_API(`void',`CDECL',`sti_cursorgetindexid',`(sti_cursorgetindexid_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB8F09C86),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorgetstorage_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_XWORD STI_CursorGetStorage;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorgetstorage_struct;

DEF_API(`void',`CDECL',`sti_cursorgetstorage',`(sti_cursorgetstorage_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x834990B6),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorgettable_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_XWORD STI_CursorGetTable;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorgettable_struct;

DEF_API(`void',`CDECL',`sti_cursorgettable',`(sti_cursorgettable_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC67780F2),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorisreadonly_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_BOOL STI_CursorIsReadOnly;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorisreadonly_struct;

DEF_API(`void',`CDECL',`sti_cursorisreadonly',`(sti_cursorisreadonly_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA79C96C4),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursormove_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_INT eDirection;				/* VAR_INPUT, Enum: DIRECTION */
	RTS_IEC_INT STI_CursorMove;			/* VAR_OUTPUT, Enum: ERROR */
} sti_cursormove_struct;

DEF_API(`void',`CDECL',`sti_cursormove',`(sti_cursormove_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x3BA769E7),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursoropen_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_DWORD idIndex;				/* VAR_INPUT */	
	RTS_IEC_BOOL xReadOnly;				/* VAR_INPUT */	
	RTS_IEC_XWORD STI_CursorOpen;		/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_cursoropen_struct;

DEF_API(`void',`CDECL',`sti_cursoropen',`(sti_cursoropen_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x69069981),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorsearchint16_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_INT iValue;					/* VAR_INPUT */	
	RTS_IEC_INT STI_CursorSearchINT16;	/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorsearchint16_struct;

DEF_API(`void',`CDECL',`sti_cursorsearchint16',`(sti_cursorsearchint16_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x51EF5860),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorsearchint32_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_DINT diValue;				/* VAR_INPUT */	
	RTS_IEC_INT STI_CursorSearchINT32;	/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorsearchint32_struct;

DEF_API(`void',`CDECL',`sti_cursorsearchint32',`(sti_cursorsearchint32_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x9F9D481A),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorsearchint64_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_LINT liValue;				/* VAR_INPUT */	
	RTS_IEC_INT STI_CursorSearchINT64;	/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorsearchint64_struct;

DEF_API(`void',`CDECL',`sti_cursorsearchint64',`(sti_cursorsearchint64_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x8D041F2F),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorsearchint8_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_SINT siValue;				/* VAR_INPUT */	
	RTS_IEC_INT STI_CursorSearchINT8;	/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorsearchint8_struct;

DEF_API(`void',`CDECL',`sti_cursorsearchint8',`(sti_cursorsearchint8_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xED9DD063),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorsearchnull_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_INT STI_CursorSearchNULL;	/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorsearchnull_struct;

DEF_API(`void',`CDECL',`sti_cursorsearchnull',`(sti_cursorsearchnull_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1DC2D739),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorsearchreal4_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_REAL rValue;				/* VAR_INPUT */	
	RTS_IEC_INT STI_CursorSearchREAL4;	/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorsearchreal4_struct;

DEF_API(`void',`CDECL',`sti_cursorsearchreal4',`(sti_cursorsearchreal4_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA6FFD47D),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorsearchreal8_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_LREAL lrValue;				/* VAR_INPUT */	
	RTS_IEC_INT STI_CursorSearchREAL8;	/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorsearchreal8_struct;

DEF_API(`void',`CDECL',`sti_cursorsearchreal8',`(sti_cursorsearchreal8_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xEC458BB0),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorsearchrowid_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_DWORD idRow;				/* VAR_INPUT */	
	RTS_IEC_INT STI_CursorSearchRowId;	/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorsearchrowid_struct;

DEF_API(`void',`CDECL',`sti_cursorsearchrowid',`(sti_cursorsearchrowid_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x7E7E8E92),0x03050500)

/**
 * Replacement of function _CursorSearchRowId, that uses a LINT value instead of a CAA.IDENT value.
 */
typedef struct tagsti_cursorsearchrowid2_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_LINT idRow;					/* VAR_INPUT */	
	RTS_IEC_INT STI_CursorSearchRowId2;	/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorsearchrowid2_struct;

DEF_API(`void',`CDECL',`sti_cursorsearchrowid2',`(sti_cursorsearchrowid2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x11FC0EBB),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorsearchtext_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	STO_TEXT *txtValue;					/* VAR_IN_OUT */	
	RTS_IEC_INT STI_CursorSearchTEXT;	/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorsearchtext_struct;

DEF_API(`void',`CDECL',`sti_cursorsearchtext',`(sti_cursorsearchtext_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x877B0D88),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowclear_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_INT STI_RowClear;			/* VAR_OUTPUT, Enum: ERROR */
} sti_rowclear_struct;

DEF_API(`void',`CDECL',`sti_rowclear',`(sti_rowclear_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x063F3EDA),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowcreate_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_XWORD STI_RowCreate;		/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_rowcreate_struct;

DEF_API(`void',`CDECL',`sti_rowcreate',`(sti_rowcreate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x51A8A2C3),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowdelete_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_DWORD idRow;				/* VAR_INPUT */	
	RTS_IEC_INT STI_RowDelete;			/* VAR_OUTPUT, Enum: ERROR */
} sti_rowdelete_struct;

DEF_API(`void',`CDECL',`sti_rowdelete',`(sti_rowdelete_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x2F288537),0x03050500)

/**
 * Replacement of function _RowDelete, that uses a LINT value instead of a CAA.IDENT value.
 */
typedef struct tagsti_rowdelete2_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_LINT idRow;					/* VAR_INPUT */	
	RTS_IEC_INT STI_RowDelete2;			/* VAR_OUTPUT, Enum: ERROR */
} sti_rowdelete2_struct;

DEF_API(`void',`CDECL',`sti_rowdelete2',`(sti_rowdelete2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x308F63CF),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowduplicate_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_DWORD idRow;				/* VAR_INPUT */	
	RTS_IEC_XWORD STI_RowDuplicate;		/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_rowduplicate_struct;

DEF_API(`void',`CDECL',`sti_rowduplicate',`(sti_rowduplicate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xB9AD1D61),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowgethaschanged_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_BOOL STI_RowGetHasChanged;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_rowgethaschanged_struct;

DEF_API(`void',`CDECL',`sti_rowgethaschanged',`(sti_rowgethaschanged_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF6C794AA),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowgetid_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD STI_RowGetId;			/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_rowgetid_struct;

DEF_API(`void',`CDECL',`sti_rowgetid',`(sti_rowgetid_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x87759DEC),0x03050500)

/**
 * Replacement of function _RowGetId, that returns a LINT value instead of a CAA.IDENT value.
 */
typedef struct tagsti_rowgetid2_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_LINT STI_RowGetId2;			/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_rowgetid2_struct;

DEF_API(`void',`CDECL',`sti_rowgetid2',`(sti_rowgetid2_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x9E2F89AF),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowgetnumofcolumns_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_UXINT STI_RowGetNumOfColumns;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_rowgetnumofcolumns_struct;

DEF_API(`void',`CDECL',`sti_rowgetnumofcolumns',`(sti_rowgetnumofcolumns_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x6FB61449),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowgetstorage_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_XWORD STI_RowGetStorage;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_rowgetstorage_struct;

DEF_API(`void',`CDECL',`sti_rowgetstorage',`(sti_rowgetstorage_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0D4CCC41),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowgettable_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_XWORD STI_RowGetTable;		/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_rowgettable_struct;

DEF_API(`void',`CDECL',`sti_rowgettable',`(sti_rowgettable_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x8AE45F6C),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowinsert_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD STI_RowInsert;		/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_rowinsert_struct;

DEF_API(`void',`CDECL',`sti_rowinsert',`(sti_rowinsert_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x7C9D2E1E),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowrelease_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_INT STI_RowRelease;			/* VAR_OUTPUT, Enum: ERROR */
} sti_rowrelease_struct;

DEF_API(`void',`CDECL',`sti_rowrelease',`(sti_rowrelease_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x56095635),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowselect_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_DWORD idRow;				/* VAR_INPUT */	
	RTS_IEC_XWORD STI_RowSelect;		/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_rowselect_struct;

DEF_API(`void',`CDECL',`sti_rowselect',`(sti_rowselect_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x16DC3998),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowupdate_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_INT STI_RowUpdate;			/* VAR_OUTPUT, Enum: ERROR */
} sti_rowupdate_struct;

DEF_API(`void',`CDECL',`sti_rowupdate',`(sti_rowupdate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF8FC45F4),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_savepointgetstorage_struct
{
	RTS_IEC_XWORD hSavepoint;			/* VAR_INPUT */	
	RTS_IEC_XWORD STI_SavepointGetStorage;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_savepointgetstorage_struct;

DEF_API(`void',`CDECL',`sti_savepointgetstorage',`(sti_savepointgetstorage_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x690912D3),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_savepointgettransaction_struct
{
	RTS_IEC_XWORD hSavepoint;			/* VAR_INPUT */	
	RTS_IEC_XWORD STI_SavepointGetTransaction;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_savepointgettransaction_struct;

DEF_API(`void',`CDECL',`sti_savepointgettransaction',`(sti_savepointgettransaction_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xE3ACA44B),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_savepointrelease_struct
{
	RTS_IEC_XWORD hSavePoint;			/* VAR_INPUT */	
	RTS_IEC_INT STI_SavepointRelease;	/* VAR_OUTPUT, Enum: ERROR */
} sti_savepointrelease_struct;

DEF_API(`void',`CDECL',`sti_savepointrelease',`(sti_savepointrelease_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x8F42C66A),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_savepointrollback_struct
{
	RTS_IEC_XWORD hSavePoint;			/* VAR_INPUT */	
	RTS_IEC_INT STI_SavepointRollback;	/* VAR_OUTPUT, Enum: ERROR */
} sti_savepointrollback_struct;

DEF_API(`void',`CDECL',`sti_savepointrollback',`(sti_savepointrollback_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x931C149B),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storageclear_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_INT STI_StorageClear;		/* VAR_OUTPUT, Enum: ERROR */
} sti_storageclear_struct;

DEF_API(`void',`CDECL',`sti_storageclear',`(sti_storageclear_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x15CD03F3),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storageclose_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_INT STI_StorageClose;		/* VAR_OUTPUT, Enum: ERROR */
} sti_storageclose_struct;

DEF_API(`void',`CDECL',`sti_storageclose',`(sti_storageclose_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x168E35B2),0x03050500)

/**
 * <description>sti_storageexecutestatement</description>
 */
typedef struct tagsti_storageexecutestatement_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_STRING *sStatement;			/* VAR_IN_OUT */	
	RTS_IEC_INT sti_storageexecutestatement;	/* VAR_OUTPUT, Enum: ERROR */
} sti_storageexecutestatement_struct;

DEF_API(`void',`CDECL',`sti_storageexecutestatement',`(sti_storageexecutestatement_struct *p)',1,RTSITF_GET_SIGNATURE(0x28B52F50, 0xC3FDFD07),0x03050C00)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storagegetencoding_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_INT STI_StorageGetEncoding;	/* VAR_OUTPUT, Enum: ENCODING */
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_storagegetencoding_struct;

DEF_API(`void',`CDECL',`sti_storagegetencoding',`(sti_storagegetencoding_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xBE199139),0x03050500)

/**
 * <description>sti_storagegetindexid</description>
 */
typedef struct tagsti_storagegetindexid_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_STRING *sIndex;				/* VAR_IN_OUT */	
	RTS_IEC_STRING *sTable;				/* VAR_IN_OUT */	
	RTS_IEC_INT sti_storagegetindexid;	/* VAR_OUTPUT, Enum: ERROR */
	RTS_IEC_DWORD idIndex;				/* VAR_OUTPUT */	
} sti_storagegetindexid_struct;

DEF_API(`void',`CDECL',`sti_storagegetindexid',`(sti_storagegetindexid_struct *p)',1,RTSITF_GET_SIGNATURE(0x08A23D12, 0x227C8789),0x03050C00)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storagegetlockingstate_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_INT STI_StorageGetLockingState;	/* VAR_OUTPUT, Enum: LOCKING_STATE */
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_storagegetlockingstate_struct;

DEF_API(`void',`CDECL',`sti_storagegetlockingstate',`(sti_storagegetlockingstate_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x673B5974),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storagegetmetrics_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	STO_METRICS *mMetrics;				/* VAR_IN_OUT */	
	RTS_IEC_INT STI_StorageGetMetrics;	/* VAR_OUTPUT, Enum: ERROR */
} sti_storagegetmetrics_struct;

DEF_API(`void',`CDECL',`sti_storagegetmetrics',`(sti_storagegetmetrics_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x94B2DFD3),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storagegetnumoftables_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_UXINT STI_StorageGetNumOfTables;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_storagegetnumoftables_struct;

DEF_API(`void',`CDECL',`sti_storagegetnumoftables',`(sti_storagegetnumoftables_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x1C28D551),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storagegetpath_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_STRING *sPath;				/* VAR_IN_OUT */	
	RTS_IEC_INT STI_StorageGetPath;		/* VAR_OUTPUT, Enum: ERROR */
} sti_storagegetpath_struct;

DEF_API(`void',`CDECL',`sti_storagegetpath',`(sti_storagegetpath_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x5370063F),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storagegetschemaversion_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_DINT STI_StorageGetSchemaVersion;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_storagegetschemaversion_struct;

DEF_API(`void',`CDECL',`sti_storagegetschemaversion',`(sti_storagegetschemaversion_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0AE8BC90),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storagegetstorageversion_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_DINT STI_StorageGetStorageVersion;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_storagegetstorageversion_struct;

DEF_API(`void',`CDECL',`sti_storagegetstorageversion',`(sti_storagegetstorageversion_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x09CB4CDD),0x03050500)

/**
 * <description>sti_storagegettableid</description>
 */
typedef struct tagsti_storagegettableid_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_STRING *sTable;				/* VAR_IN_OUT */	
	RTS_IEC_INT sti_storagegettableid;	/* VAR_OUTPUT, Enum: ERROR */
	RTS_IEC_DWORD idTable;				/* VAR_OUTPUT */	
} sti_storagegettableid_struct;

DEF_API(`void',`CDECL',`sti_storagegettableid',`(sti_storagegettableid_struct *p)',1,RTSITF_GET_SIGNATURE(0xCDAB221E, 0xE7759885),0x03050C00)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storagegetuserversion_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_DINT STI_StorageGetUserVersion;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_storagegetuserversion_struct;

DEF_API(`void',`CDECL',`sti_storagegetuserversion',`(sti_storagegetuserversion_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xFBEB5D41),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storageisreadonly_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_BOOL STI_StorageIsReadOnly;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_storageisreadonly_struct;

DEF_API(`void',`CDECL',`sti_storageisreadonly',`(sti_storageisreadonly_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x05EC113C),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storageopenfile_struct
{
	RTS_IEC_STRING sPath[256];			/* VAR_INPUT */	
	RTS_IEC_BOOL xReadOnly;				/* VAR_INPUT */	
	RTS_IEC_XWORD STI_StorageOpenFile;	/* VAR_OUTPUT */	/* hStorage */
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_storageopenfile_struct;

DEF_API(`void',`CDECL',`sti_storageopenfile',`(sti_storageopenfile_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD323975E),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storagereorg_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_INT STI_StorageReorg;		/* VAR_OUTPUT, Enum: ERROR */
} sti_storagereorg_struct;

DEF_API(`void',`CDECL',`sti_storagereorg',`(sti_storagereorg_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCE724590),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_tableclear_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_INT STI_TableClear;			/* VAR_OUTPUT, Enum: ERROR */
} sti_tableclear_struct;

DEF_API(`void',`CDECL',`sti_tableclear',`(sti_tableclear_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xC53500A8),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_tableclose_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_INT STI_TableClose;			/* VAR_OUTPUT, Enum: ERROR */
} sti_tableclose_struct;

DEF_API(`void',`CDECL',`sti_tableclose',`(sti_tableclose_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x16E380EF),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_tablegetid_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_DWORD STI_TableGetId;		/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_tablegetid_struct;

DEF_API(`void',`CDECL',`sti_tablegetid',`(sti_tablegetid_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xEF20A927),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_tablegetminmaxrowids_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_INT STI_TableGetMinMaxRowIds;	/* VAR_OUTPUT, Enum: ERROR */
	RTS_IEC_LINT idRowMin;				/* VAR_OUTPUT */	
	RTS_IEC_LINT idRowMax;				/* VAR_OUTPUT */	
} sti_tablegetminmaxrowids_struct;

DEF_API(`void',`CDECL',`sti_tablegetminmaxrowids',`(sti_tablegetminmaxrowids_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0D54AAEA),0x03050900)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_tablegetnumofcolumns_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_UXINT STI_TableGetNumOfColumns;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_tablegetnumofcolumns_struct;

DEF_API(`void',`CDECL',`sti_tablegetnumofcolumns',`(sti_tablegetnumofcolumns_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x3BD52F3A),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_tablegetnumofindexes_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_UXINT STI_TableGetNumOfIndexes;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_tablegetnumofindexes_struct;

DEF_API(`void',`CDECL',`sti_tablegetnumofindexes',`(sti_tablegetnumofindexes_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x8A61B1C2),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_tablegetnumofrows_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_UXINT STI_TableGetNumOfRows;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_tablegetnumofrows_struct;

DEF_API(`void',`CDECL',`sti_tablegetnumofrows',`(sti_tablegetnumofrows_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x42EEA100),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_tablegetstorage_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_XWORD STI_TableGetStorage;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_tablegetstorage_struct;

DEF_API(`void',`CDECL',`sti_tablegetstorage',`(sti_tablegetstorage_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xA15443A1),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_tableopen_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_DWORD idTable;				/* VAR_INPUT */	
	RTS_IEC_XWORD STI_TableOpen;		/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_tableopen_struct;

DEF_API(`void',`CDECL',`sti_tableopen',`(sti_tableopen_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x97F1C519),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_transactionbegin_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_INT eMode;					/* VAR_INPUT, Enum: TRANSACTION_MODE */
	RTS_IEC_XWORD STI_TransactionBegin;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_transactionbegin_struct;

DEF_API(`void',`CDECL',`sti_transactionbegin',`(sti_transactionbegin_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xF402E0CD),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_transactioncommit_struct
{
	RTS_IEC_XWORD hTransaction;			/* VAR_INPUT */	
	RTS_IEC_INT STI_TransactionCommit;	/* VAR_OUTPUT, Enum: ERROR */
} sti_transactioncommit_struct;

DEF_API(`void',`CDECL',`sti_transactioncommit',`(sti_transactioncommit_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x89DDC223),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_transactiongetstorage_struct
{
	RTS_IEC_XWORD hTransaction;			/* VAR_INPUT */	
	RTS_IEC_XWORD STI_TransactionGetStorage;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_transactiongetstorage_struct;

DEF_API(`void',`CDECL',`sti_transactiongetstorage',`(sti_transactiongetstorage_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x38993503),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_transactionrollback_struct
{
	RTS_IEC_XWORD hTransaction;			/* VAR_INPUT */	
	RTS_IEC_INT STI_TransactionRollback;	/* VAR_OUTPUT, Enum: ERROR */
} sti_transactionrollback_struct;

DEF_API(`void',`CDECL',`sti_transactionrollback',`(sti_transactionrollback_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xD9E1C5A2),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_transactionsetsavepoint_struct
{
	RTS_IEC_XWORD hTransaction;			/* VAR_INPUT */	
	RTS_IEC_XWORD STI_TransactionSetSavepoint;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_transactionsetsavepoint_struct;

DEF_API(`void',`CDECL',`sti_transactionsetsavepoint',`(sti_transactionsetsavepoint_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x9A6EFA3F),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_utilitygetcurrentdateandtime_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_LINT STI_UtilityGetCurrentDateAndTime;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_utilitygetcurrentdateandtime_struct;

DEF_API(`void',`CDECL',`sti_utilitygetcurrentdateandtime',`(sti_utilitygetcurrentdateandtime_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x452BD59D),0x03050500)

/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_utilityrandomness_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_UXINT szSize;				/* VAR_INPUT */	
	RTS_IEC_XWORD pData;				/* VAR_INPUT */	
	RTS_IEC_INT STI_UtilityRandomness;	/* VAR_OUTPUT, Enum: ERROR */
} sti_utilityrandomness_struct;

DEF_API(`void',`CDECL',`sti_utilityrandomness',`(sti_utilityrandomness_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xCFDCFE92),0x03050500)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

DEF_ITF_API(`STO_BLOB*',`CDECL',`STO_BlobAlloc',`(CAA_SIZE szData, STO_ERROR *peError)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_BlobCopyToData',`(STO_BLOB* pBlob, CAA_BYTE* pData, CAA_SIZE szData)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_BlobFree',`(STO_BLOB* pBlob)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_DataCopyToBlob',`(CAA_BYTE* pData, CAA_SIZE szData, STO_BLOB* pBlob)')

DEF_ITF_API(`STO_ERROR',`CDECL',`STO_INT64_TO_LOCALTIME',`(STO_INT64 i64UTCValue, STO_INT64 *pi64LocalValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_INT64_TO_UTC',`(STO_INT64 i64LocalValue, STO_INT64 *pi64UTCValue)')

DEF_ITF_API(`STO_ERROR',`CDECL',`STO_DT_TO_INT64',`(CAA_DT dtValue, CAA_LINT *pliValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_DT_TO_ISO8601',`(CAA_DT dtValue, STO_ISO8601 *psValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_DT_TO_REAL8',`(CAA_DT dtValue, CAA_LREAL *plrValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_INT64_TO_DT',`(CAA_LINT liValue, CAA_DT *pdtValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_INT64_TO_ISO8601',`(CAA_LINT liValue, STO_ISO8601 *psValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_INT64_TO_LTIME',`(CAA_LINT liValue, CAA_LTIME *pltValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_INT64_TO_REAL8',`(CAA_LINT liValue, CAA_LREAL *plrValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_INT64_TO_TIME',`(CAA_LINT liValue, CAA_TIME *ptValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_ISO8601_TO_DT',`(STO_ISO8601 *psValue, CAA_DT *pdtValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_ISO8601_TO_LTIME',`(STO_ISO8601 *psValue, CAA_LTIME *pltValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_ISO8601_TO_TIME',`(STO_ISO8601 *psValue, CAA_TIME *ptValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_LTIME_TO_INT64',`(CAA_LTIME ltValue, CAA_LINT *pliValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_LTIME_TO_ISO8601',`(CAA_LTIME ltValue, STO_ISO8601 *psValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_LTIME_TO_REAL8',`(CAA_LTIME ltValue, CAA_LREAL *plrValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_REAL8_TO_DT',`(CAA_LREAL lrValue, CAA_DT *pdtValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_REAL8_TO_LTIME',`(CAA_LREAL lrValue, CAA_LTIME *pltValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_REAL8_TO_TIME',`(CAA_LREAL lrValue, CAA_TIME *ptValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_TIME_TO_INT64',`(CAA_TIME tValue, CAA_LINT *pliValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_TIME_TO_ISO8601',`(CAA_TIME tValue, STO_ISO8601 *psValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_TIME_TO_REAL8',`(CAA_TIME tValue, CAA_LREAL *plrValue)')

DEF_ITF_API(`STO_ERROR',`CDECL',`STO_CreateTextFromString',`(CAA_STRING * psValue, STO_TEXT* ptxtValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_CreateTextFromWString',`(CAA_WSTRING * pwsValue, STO_TEXT* ptxtValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_TextCopyToString',`(STO_TEXT* ptxtText, CAA_STRING * psValue, CAA_SIZE szValue, CAA_BOOL xFree)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_TextCopyToWString',`(STO_TEXT* ptxtValue, CAA_WSTRING* pwsValue, CAA_SIZE szValue, CAA_BOOL xFree)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STO_TextFree',`(STO_TEXT* ptxtValue)')

DEF_ITF_API(`CAA_WORD',`CDECL',`STO_GetSupplierVersion',`(CAA_BOOL xDummy)')

DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnGetBLOB',`(STI_ROW hRow, CAA_IDENT idColumn, STO_BLOB *pblobValue, CAA_BOOL *pxNULL)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnGetINT16',`(STI_ROW hRow, CAA_IDENT idColumn, CAA_INT *piValue, CAA_BOOL *pxNULL)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnGetINT32',`(STI_ROW hRow, CAA_IDENT idColumn, CAA_DINT *pdiValue, CAA_BOOL *pxNULL)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnGetINT64',`(STI_ROW hRow, CAA_IDENT idColumn, CAA_LINT *pliValue, CAA_BOOL *pxNULL)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnGetINT8',`(STI_ROW hRow, CAA_IDENT idColumn, CAA_SINT *psiValue, CAA_BOOL *pxNULL)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnGetREAL4',`(STI_ROW hRow, CAA_IDENT idColumn, CAA_REAL *prValue, CAA_BOOL *pxNULL)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnGetREAL8',`(STI_ROW hRow, CAA_IDENT idColumn, CAA_LREAL *plrValue, CAA_BOOL *pxNULL)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnGetTEXT',`(STI_ROW hRow, CAA_IDENT idColumn, STO_TEXT *ptxtValue, CAA_BOOL *pxNULL)')
DEF_ITF_API(`STO_COLUMN_TYPE',`CDECL',`STI_ColumnGetType',`(STI_ROW hRow, CAA_IDENT idColumn, STO_ERROR *peError)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnSetBLOB',`(STI_ROW hRow, CAA_IDENT idColumn, STO_BLOB *pblobValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnSetINT16',`(STI_ROW hRow, CAA_IDENT idColumn, CAA_INT iValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnSetINT32',`(STI_ROW hRow, CAA_IDENT idColumn, CAA_DINT diValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnSetINT64',`(STI_ROW hRow, CAA_IDENT idColumn, CAA_LINT liValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnSetINT8',`(STI_ROW hRow, CAA_IDENT idColumn, CAA_SINT siValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnSetNULL',`(STI_ROW hRow, CAA_IDENT idColumn)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnSetREAL4',`(STI_ROW hRow, CAA_IDENT idColumn, CAA_REAL rValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnSetREAL8',`(STI_ROW hRow, CAA_IDENT idColumn, CAA_LREAL lrValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnSetTEXT',`(STI_ROW hRow, CAA_IDENT idColumn, STO_TEXT *ptxtValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnUpdateBLOB',`(STI_ROW hRow, CAA_IDENT idColumn, STO_BLOB *pblobValue, CAA_BOOL *pxNULL)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnUpdateINT16',`(STI_ROW hRow, CAA_IDENT idColumn, CAA_INT *piValue, CAA_BOOL *pxNULL)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnUpdateINT32',`(STI_ROW hRow, CAA_IDENT idColumn, CAA_DINT *pdiValue, CAA_BOOL *pxNULL)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnUpdateINT64',`(STI_ROW hRow, CAA_IDENT idColumn, CAA_LINT *pliValue, CAA_BOOL *pxNULL)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnUpdateINT8',`(STI_ROW hRow, CAA_IDENT idColumn, CAA_SINT *psiValue, CAA_BOOL *pxNULL)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnUpdateREAL4',`(STI_ROW hRow, CAA_IDENT idColumn, CAA_REAL *prValue, CAA_BOOL *pxNULL)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnUpdateREAL8',`(STI_ROW hRow, CAA_IDENT idColumn, CAA_LREAL *plrValue, CAA_BOOL *pxNULL)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_ColumnUpdateTEXT',`(STI_ROW hRow, CAA_IDENT idColumn, STO_TEXT *ptxtValue, CAA_BOOL *pxNULL)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_CursorClose',`(STI_CURSOR hCursor)')
DEF_ITF_API(`STI_ROW',`CDECL',`STI_CursorGetCurrentRow',`(STI_CURSOR hCursor, STO_ERROR *peError)')
DEF_ITF_API(`CAA_IDENT',`CDECL',`STI_CursorGetIndexId',`(STI_CURSOR hCursor, STO_ERROR *peError)')
DEF_ITF_API(`STI_STORAGE',`CDECL',`STI_CursorGetStorage',`(STI_CURSOR hCursor, STO_ERROR *peError)')
DEF_ITF_API(`STI_TABLE',`CDECL',`STI_CursorGetTable',`(STI_CURSOR hCursor, STO_ERROR *peError)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`STI_CursorIsReadOnly',`(STI_CURSOR hCursor, STO_ERROR *peError)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_CursorMove',`(STI_CURSOR hCursor, STO_DIRECTION eDirection)')
DEF_ITF_API(`STI_CURSOR',`CDECL',`STI_CursorOpen',`(STI_TABLE hTable, CAA_IDENT idIndex, CAA_BOOL xReadOnly, STO_ERROR *peError)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_CursorSearchINT16',`(STI_CURSOR hCursor, CAA_INT iValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_CursorSearchINT32',`(STI_CURSOR hCursor, CAA_DINT diValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_CursorSearchINT64',`(STI_CURSOR hCursor, CAA_LINT liValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_CursorSearchINT8',`(STI_CURSOR hCursor, CAA_SINT siValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_CursorSearchNULL',`(STI_CURSOR hCursor)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_CursorSearchREAL4',`(STI_CURSOR hCursor, CAA_REAL rValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_CursorSearchREAL8',`(STI_CURSOR hCursor, CAA_LREAL lrValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_CursorSearchRowId',`(STI_CURSOR hCursor, CAA_LINT idRow)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_CursorSearchTEXT',`(STI_CURSOR hCursor, STO_TEXT *ptxtValue)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_RowClear',`(STI_ROW hRow)')
DEF_ITF_API(`STI_ROW',`CDECL',`STI_RowCreate',`(STI_TABLE hTable, STO_ERROR *peError)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_RowDelete',`(STI_TABLE hTable, CAA_LINT idRow)')
DEF_ITF_API(`STI_ROW',`CDECL',`STI_RowDuplicate',`(STI_TABLE hTable, CAA_IDENT idRow, STO_ERROR *peError)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`STI_RowGetHasChanged',`(STI_ROW hRow, STO_ERROR *peError)')
DEF_ITF_API(`CAA_LINT',`CDECL',`STI_RowGetId',`(STI_ROW hRow, STO_ERROR *peError)')
DEF_ITF_API(`CAA_COUNT',`CDECL',`STI_RowGetNumOfColumns',`(STI_ROW hRow, STO_ERROR *peError)')
DEF_ITF_API(`STI_STORAGE',`CDECL',`STI_RowGetStorage',`(STI_ROW hRow, STO_ERROR *peError)')
DEF_ITF_API(`STI_TABLE',`CDECL',`STI_RowGetTable',`(STI_ROW hRow, STO_ERROR *peError)')
DEF_ITF_API(`CAA_IDENT',`CDECL',`STI_RowInsert',`(STI_ROW hRow, STO_ERROR *peError)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_RowUpdate',`(STI_ROW hRow)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_RowRelease',`(STI_ROW hRow)')
DEF_ITF_API(`STI_ROW',`CDECL',`STI_RowSelect',`(STI_TABLE hTable, CAA_IDENT idRow, STO_ERROR *peError)')
DEF_ITF_API(`STI_STORAGE',`CDECL',`STI_SavepointGetStorage',`(STI_SAVEPOINT hSavepoint, STO_ERROR *peError)')
DEF_ITF_API(`STI_TRANSACTION',`CDECL',`STI_SavepointGetTransaction',`(STI_SAVEPOINT hSavepoint, STO_ERROR *peError)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_SavepointRelease',`(STI_SAVEPOINT hSavePoint)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_SavepointRollback',`(STI_SAVEPOINT hSavePoint)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_StorageClear',`(STI_STORAGE hStorage)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_StorageClose',`(STI_STORAGE hStorage)')
DEF_ITF_API(`STO_ENCODING',`CDECL',`STI_StorageGetEncoding',`(STI_STORAGE hStorage, STO_ERROR *peError)')
DEF_ITF_API(`STO_LOCKING_STATE',`CDECL',`STI_StorageGetLockingState',`(STI_STORAGE hStorage, STO_ERROR *peError)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_StorageGetMetrics',`(STI_STORAGE hStorage, STO_METRICS *pmMetrics)')
DEF_ITF_API(`CAA_COUNT',`CDECL',`STI_StorageGetNumOfTables',`(STI_STORAGE hStorage, STO_ERROR *peError)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_StorageGetPath',`(STI_STORAGE hStorage, CAA_FILENAME *psPath)')
DEF_ITF_API(`CAA_DINT',`CDECL',`STI_StorageGetSchemaVersion',`(STI_STORAGE hStorage, STO_ERROR *peError)')
DEF_ITF_API(`CAA_DINT',`CDECL',`STI_StorageGetStorageVersion',`(STI_STORAGE hStorage, STO_ERROR *peError)')
DEF_ITF_API(`CAA_DINT',`CDECL',`STI_StorageGetUserVersion',`(STI_STORAGE hStorage, STO_ERROR *peError)')
DEF_ITF_API(`CAA_BOOL',`CDECL',`STI_StorageIsReadOnly',`(STI_STORAGE hStorage, STO_ERROR *peError)')
DEF_ITF_API(`STI_STORAGE',`CDECL',`STI_StorageOpenFile',`(CAA_FILENAME sPath, CAA_BOOL xReadOnly, STO_ERROR *peError)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_StorageReorg',`(STI_STORAGE hStorage)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_TableClear',`(STI_TABLE hTable)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_TableClose',`(STI_TABLE hTable)')
DEF_ITF_API(`CAA_IDENT',`CDECL',`STI_TableGetId',`(STI_TABLE hTable, STO_ERROR *peError)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_TableGetMinMaxRowIds',`(STI_TABLE hTable, RTS_IEC_LINT *pliRowIdMin, RTS_IEC_LINT *pliRowIdMax)')
DEF_ITF_API(`CAA_COUNT',`CDECL',`STI_TableGetNumOfColumns',`(STI_TABLE hTable, STO_ERROR *peError)')
DEF_ITF_API(`CAA_COUNT',`CDECL',`STI_TableGetNumOfIndexes',`(STI_TABLE hTable, STO_ERROR *peError)')
DEF_ITF_API(`CAA_COUNT',`CDECL',`STI_TableGetNumOfRows',`(STI_TABLE hTable, STO_ERROR *peError)')
DEF_ITF_API(`STI_STORAGE',`CDECL',`STI_TableGetStorage',`(STI_TABLE hTable, STO_ERROR *peError)')
DEF_ITF_API(`STI_TABLE',`CDECL',`STI_TableOpen',`(STI_STORAGE hStorage, CAA_IDENT idTable, STO_ERROR *peError)')
DEF_ITF_API(`STI_TRANSACTION',`CDECL',`STI_TransactionBegin',`(STI_STORAGE hStorage, STO_TRANSACTION_MODE eMode, STO_ERROR *peError)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_TransactionCommit',`(STI_TRANSACTION hTransaction)')
DEF_ITF_API(`STI_STORAGE',`CDECL',`STI_TransactionGetStorage',`(STI_TRANSACTION hTransaction, STO_ERROR *peError)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_TransactionRollback',`(STI_TRANSACTION hTransaction)')
DEF_ITF_API(`STI_SAVEPOINT',`CDECL',`STI_TransactionSetSavepoint',`(STI_TRANSACTION hTransaction, STO_ERROR *peError)')

DEF_ITF_API(`STO_INT64',`CDECL',`STI_UtilityGetCurrentDateAndTime',`(STI_STORAGE hStorage, STO_ERROR *peError)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_UtilityRandomness',`(STI_STORAGE hStorage, CAA_SIZE szSize, CAA_PVOID pData)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_DeleteFile',`(CAA_FILENAME sPath)')

DEF_ITF_API(`STO_ERROR',`CDECL',`STI_StorageExecuteStatement',`(STI_STORAGE hStorage, RTS_IEC_STRING *sStatement)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_StorageGetTableId',`(STI_STORAGE hStorage, RTS_IEC_STRING *sTable, RTS_IEC_DWORD *pidTable)')
DEF_ITF_API(`STO_ERROR',`CDECL',`STI_StorageGetIndexId',`(STI_STORAGE hStorage, RTS_IEC_STRING *sTable, RTS_IEC_STRING *sIndex, RTS_IEC_DWORD *pidIndex)')

#ifdef __cplusplus
}
#endif
