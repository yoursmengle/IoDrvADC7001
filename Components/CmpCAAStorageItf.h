 /**
 * <interfacename>CAA_Storage</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _CMPCAASTORAGEITF_H_
#define _CMPCAASTORAGEITF_H_

#include "CmpStd.h"

 

 




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
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

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

void CDECL CDECL_EXT sto_bloballoc(sto_bloballoc_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_BLOBALLOC_IEC) (sto_bloballoc_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_BLOBALLOC_NOTIMPLEMENTED)
	#define USE_sto_bloballoc
	#define EXT_sto_bloballoc
	#define GET_sto_bloballoc(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_bloballoc(p0) 
	#define CHK_sto_bloballoc  FALSE
	#define EXP_sto_bloballoc  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_bloballoc
	#define EXT_sto_bloballoc
	#define GET_sto_bloballoc(fl)  CAL_CMGETAPI( "sto_bloballoc" ) 
	#define CAL_sto_bloballoc  sto_bloballoc
	#define CHK_sto_bloballoc  TRUE
	#define EXP_sto_bloballoc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_bloballoc", (RTS_UINTPTR)sto_bloballoc, 1, RTSITF_GET_SIGNATURE(0, 0x721BFA71), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_bloballoc
	#define EXT_sto_bloballoc
	#define GET_sto_bloballoc(fl)  CAL_CMGETAPI( "sto_bloballoc" ) 
	#define CAL_sto_bloballoc  sto_bloballoc
	#define CHK_sto_bloballoc  TRUE
	#define EXP_sto_bloballoc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_bloballoc", (RTS_UINTPTR)sto_bloballoc, 1, RTSITF_GET_SIGNATURE(0, 0x721BFA71), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_bloballoc
	#define EXT_CmpCAAStoragesto_bloballoc
	#define GET_CmpCAAStoragesto_bloballoc  ERR_OK
	#define CAL_CmpCAAStoragesto_bloballoc  sto_bloballoc
	#define CHK_CmpCAAStoragesto_bloballoc  TRUE
	#define EXP_CmpCAAStoragesto_bloballoc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_bloballoc", (RTS_UINTPTR)sto_bloballoc, 1, RTSITF_GET_SIGNATURE(0, 0x721BFA71), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_bloballoc
	#define EXT_sto_bloballoc
	#define GET_sto_bloballoc(fl)  CAL_CMGETAPI( "sto_bloballoc" ) 
	#define CAL_sto_bloballoc  sto_bloballoc
	#define CHK_sto_bloballoc  TRUE
	#define EXP_sto_bloballoc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_bloballoc", (RTS_UINTPTR)sto_bloballoc, 1, RTSITF_GET_SIGNATURE(0, 0x721BFA71), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_bloballoc  PFSTO_BLOBALLOC_IEC pfsto_bloballoc;
	#define EXT_sto_bloballoc  extern PFSTO_BLOBALLOC_IEC pfsto_bloballoc;
	#define GET_sto_bloballoc(fl)  s_pfCMGetAPI2( "sto_bloballoc", (RTS_VOID_FCTPTR *)&pfsto_bloballoc, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x721BFA71), 0x03050528)
	#define CAL_sto_bloballoc  pfsto_bloballoc
	#define CHK_sto_bloballoc  (pfsto_bloballoc != NULL)
	#define EXP_sto_bloballoc   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_bloballoc", (RTS_UINTPTR)sto_bloballoc, 1, RTSITF_GET_SIGNATURE(0, 0x721BFA71), 0x03050528) 
#endif


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

void CDECL CDECL_EXT sto_blobcopytodata(sto_blobcopytodata_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_BLOBCOPYTODATA_IEC) (sto_blobcopytodata_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_BLOBCOPYTODATA_NOTIMPLEMENTED)
	#define USE_sto_blobcopytodata
	#define EXT_sto_blobcopytodata
	#define GET_sto_blobcopytodata(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_blobcopytodata(p0) 
	#define CHK_sto_blobcopytodata  FALSE
	#define EXP_sto_blobcopytodata  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_blobcopytodata
	#define EXT_sto_blobcopytodata
	#define GET_sto_blobcopytodata(fl)  CAL_CMGETAPI( "sto_blobcopytodata" ) 
	#define CAL_sto_blobcopytodata  sto_blobcopytodata
	#define CHK_sto_blobcopytodata  TRUE
	#define EXP_sto_blobcopytodata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_blobcopytodata", (RTS_UINTPTR)sto_blobcopytodata, 1, RTSITF_GET_SIGNATURE(0, 0x59171DAD), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_blobcopytodata
	#define EXT_sto_blobcopytodata
	#define GET_sto_blobcopytodata(fl)  CAL_CMGETAPI( "sto_blobcopytodata" ) 
	#define CAL_sto_blobcopytodata  sto_blobcopytodata
	#define CHK_sto_blobcopytodata  TRUE
	#define EXP_sto_blobcopytodata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_blobcopytodata", (RTS_UINTPTR)sto_blobcopytodata, 1, RTSITF_GET_SIGNATURE(0, 0x59171DAD), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_blobcopytodata
	#define EXT_CmpCAAStoragesto_blobcopytodata
	#define GET_CmpCAAStoragesto_blobcopytodata  ERR_OK
	#define CAL_CmpCAAStoragesto_blobcopytodata  sto_blobcopytodata
	#define CHK_CmpCAAStoragesto_blobcopytodata  TRUE
	#define EXP_CmpCAAStoragesto_blobcopytodata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_blobcopytodata", (RTS_UINTPTR)sto_blobcopytodata, 1, RTSITF_GET_SIGNATURE(0, 0x59171DAD), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_blobcopytodata
	#define EXT_sto_blobcopytodata
	#define GET_sto_blobcopytodata(fl)  CAL_CMGETAPI( "sto_blobcopytodata" ) 
	#define CAL_sto_blobcopytodata  sto_blobcopytodata
	#define CHK_sto_blobcopytodata  TRUE
	#define EXP_sto_blobcopytodata  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_blobcopytodata", (RTS_UINTPTR)sto_blobcopytodata, 1, RTSITF_GET_SIGNATURE(0, 0x59171DAD), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_blobcopytodata  PFSTO_BLOBCOPYTODATA_IEC pfsto_blobcopytodata;
	#define EXT_sto_blobcopytodata  extern PFSTO_BLOBCOPYTODATA_IEC pfsto_blobcopytodata;
	#define GET_sto_blobcopytodata(fl)  s_pfCMGetAPI2( "sto_blobcopytodata", (RTS_VOID_FCTPTR *)&pfsto_blobcopytodata, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x59171DAD), 0x03050528)
	#define CAL_sto_blobcopytodata  pfsto_blobcopytodata
	#define CHK_sto_blobcopytodata  (pfsto_blobcopytodata != NULL)
	#define EXP_sto_blobcopytodata   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_blobcopytodata", (RTS_UINTPTR)sto_blobcopytodata, 1, RTSITF_GET_SIGNATURE(0, 0x59171DAD), 0x03050528) 
#endif


/**
 * <description>sto_blobfree</description>
 */
typedef struct tagsto_blobfree_struct
{
	STO_BLOB *pBlob;					/* VAR_INPUT */	
	CAA_ERROR STO_BlobFree;				/* VAR_OUTPUT */	/* eError */
} sto_blobfree_struct;

void CDECL CDECL_EXT sto_blobfree(sto_blobfree_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_BLOBFREE_IEC) (sto_blobfree_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_BLOBFREE_NOTIMPLEMENTED)
	#define USE_sto_blobfree
	#define EXT_sto_blobfree
	#define GET_sto_blobfree(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_blobfree(p0) 
	#define CHK_sto_blobfree  FALSE
	#define EXP_sto_blobfree  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_blobfree
	#define EXT_sto_blobfree
	#define GET_sto_blobfree(fl)  CAL_CMGETAPI( "sto_blobfree" ) 
	#define CAL_sto_blobfree  sto_blobfree
	#define CHK_sto_blobfree  TRUE
	#define EXP_sto_blobfree  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_blobfree", (RTS_UINTPTR)sto_blobfree, 1, RTSITF_GET_SIGNATURE(0, 0x677BB3A1), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_blobfree
	#define EXT_sto_blobfree
	#define GET_sto_blobfree(fl)  CAL_CMGETAPI( "sto_blobfree" ) 
	#define CAL_sto_blobfree  sto_blobfree
	#define CHK_sto_blobfree  TRUE
	#define EXP_sto_blobfree  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_blobfree", (RTS_UINTPTR)sto_blobfree, 1, RTSITF_GET_SIGNATURE(0, 0x677BB3A1), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_blobfree
	#define EXT_CmpCAAStoragesto_blobfree
	#define GET_CmpCAAStoragesto_blobfree  ERR_OK
	#define CAL_CmpCAAStoragesto_blobfree  sto_blobfree
	#define CHK_CmpCAAStoragesto_blobfree  TRUE
	#define EXP_CmpCAAStoragesto_blobfree  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_blobfree", (RTS_UINTPTR)sto_blobfree, 1, RTSITF_GET_SIGNATURE(0, 0x677BB3A1), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_blobfree
	#define EXT_sto_blobfree
	#define GET_sto_blobfree(fl)  CAL_CMGETAPI( "sto_blobfree" ) 
	#define CAL_sto_blobfree  sto_blobfree
	#define CHK_sto_blobfree  TRUE
	#define EXP_sto_blobfree  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_blobfree", (RTS_UINTPTR)sto_blobfree, 1, RTSITF_GET_SIGNATURE(0, 0x677BB3A1), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_blobfree  PFSTO_BLOBFREE_IEC pfsto_blobfree;
	#define EXT_sto_blobfree  extern PFSTO_BLOBFREE_IEC pfsto_blobfree;
	#define GET_sto_blobfree(fl)  s_pfCMGetAPI2( "sto_blobfree", (RTS_VOID_FCTPTR *)&pfsto_blobfree, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x677BB3A1), 0x03050528)
	#define CAL_sto_blobfree  pfsto_blobfree
	#define CHK_sto_blobfree  (pfsto_blobfree != NULL)
	#define EXP_sto_blobfree   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_blobfree", (RTS_UINTPTR)sto_blobfree, 1, RTSITF_GET_SIGNATURE(0, 0x677BB3A1), 0x03050528) 
#endif


/**
 * See documentation of type TEXT how to use the TEXT type.
 */
typedef struct tagsto_createtextfromstring_struct
{
	RTS_IEC_STRING *sValue;			/* VAR_IN_OUT */	
	STO_TEXT *txtValue;					/* VAR_IN_OUT */	
	CAA_ERROR STO_CreateTextFromString;	/* VAR_OUTPUT */	
} sto_createtextfromstring_struct;

void CDECL CDECL_EXT sto_createtextfromstring(sto_createtextfromstring_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_CREATETEXTFROMSTRING_IEC) (sto_createtextfromstring_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_CREATETEXTFROMSTRING_NOTIMPLEMENTED)
	#define USE_sto_createtextfromstring
	#define EXT_sto_createtextfromstring
	#define GET_sto_createtextfromstring(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_createtextfromstring(p0) 
	#define CHK_sto_createtextfromstring  FALSE
	#define EXP_sto_createtextfromstring  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_createtextfromstring
	#define EXT_sto_createtextfromstring
	#define GET_sto_createtextfromstring(fl)  CAL_CMGETAPI( "sto_createtextfromstring" ) 
	#define CAL_sto_createtextfromstring  sto_createtextfromstring
	#define CHK_sto_createtextfromstring  TRUE
	#define EXP_sto_createtextfromstring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_createtextfromstring", (RTS_UINTPTR)sto_createtextfromstring, 1, RTSITF_GET_SIGNATURE(0, 0x37C64BDF), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_createtextfromstring
	#define EXT_sto_createtextfromstring
	#define GET_sto_createtextfromstring(fl)  CAL_CMGETAPI( "sto_createtextfromstring" ) 
	#define CAL_sto_createtextfromstring  sto_createtextfromstring
	#define CHK_sto_createtextfromstring  TRUE
	#define EXP_sto_createtextfromstring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_createtextfromstring", (RTS_UINTPTR)sto_createtextfromstring, 1, RTSITF_GET_SIGNATURE(0, 0x37C64BDF), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_createtextfromstring
	#define EXT_CmpCAAStoragesto_createtextfromstring
	#define GET_CmpCAAStoragesto_createtextfromstring  ERR_OK
	#define CAL_CmpCAAStoragesto_createtextfromstring  sto_createtextfromstring
	#define CHK_CmpCAAStoragesto_createtextfromstring  TRUE
	#define EXP_CmpCAAStoragesto_createtextfromstring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_createtextfromstring", (RTS_UINTPTR)sto_createtextfromstring, 1, RTSITF_GET_SIGNATURE(0, 0x37C64BDF), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_createtextfromstring
	#define EXT_sto_createtextfromstring
	#define GET_sto_createtextfromstring(fl)  CAL_CMGETAPI( "sto_createtextfromstring" ) 
	#define CAL_sto_createtextfromstring  sto_createtextfromstring
	#define CHK_sto_createtextfromstring  TRUE
	#define EXP_sto_createtextfromstring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_createtextfromstring", (RTS_UINTPTR)sto_createtextfromstring, 1, RTSITF_GET_SIGNATURE(0, 0x37C64BDF), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_createtextfromstring  PFSTO_CREATETEXTFROMSTRING_IEC pfsto_createtextfromstring;
	#define EXT_sto_createtextfromstring  extern PFSTO_CREATETEXTFROMSTRING_IEC pfsto_createtextfromstring;
	#define GET_sto_createtextfromstring(fl)  s_pfCMGetAPI2( "sto_createtextfromstring", (RTS_VOID_FCTPTR *)&pfsto_createtextfromstring, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x37C64BDF), 0x03050528)
	#define CAL_sto_createtextfromstring  pfsto_createtextfromstring
	#define CHK_sto_createtextfromstring  (pfsto_createtextfromstring != NULL)
	#define EXP_sto_createtextfromstring   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_createtextfromstring", (RTS_UINTPTR)sto_createtextfromstring, 1, RTSITF_GET_SIGNATURE(0, 0x37C64BDF), 0x03050528) 
#endif


/**
 * See documentation of type TEXT how to use the TEXT type.
 */
typedef struct tagsto_createtextfromwstring_struct
{
	RTS_IEC_WSTRING *wsValue;		/* VAR_IN_OUT */	
	STO_TEXT *txtValue;					/* VAR_IN_OUT */	
	CAA_ERROR STO_CreateTextFromWString;	/* VAR_OUTPUT */	
} sto_createtextfromwstring_struct;

void CDECL CDECL_EXT sto_createtextfromwstring(sto_createtextfromwstring_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_CREATETEXTFROMWSTRING_IEC) (sto_createtextfromwstring_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_CREATETEXTFROMWSTRING_NOTIMPLEMENTED)
	#define USE_sto_createtextfromwstring
	#define EXT_sto_createtextfromwstring
	#define GET_sto_createtextfromwstring(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_createtextfromwstring(p0) 
	#define CHK_sto_createtextfromwstring  FALSE
	#define EXP_sto_createtextfromwstring  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_createtextfromwstring
	#define EXT_sto_createtextfromwstring
	#define GET_sto_createtextfromwstring(fl)  CAL_CMGETAPI( "sto_createtextfromwstring" ) 
	#define CAL_sto_createtextfromwstring  sto_createtextfromwstring
	#define CHK_sto_createtextfromwstring  TRUE
	#define EXP_sto_createtextfromwstring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_createtextfromwstring", (RTS_UINTPTR)sto_createtextfromwstring, 1, RTSITF_GET_SIGNATURE(0, 0xAB9B0731), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_createtextfromwstring
	#define EXT_sto_createtextfromwstring
	#define GET_sto_createtextfromwstring(fl)  CAL_CMGETAPI( "sto_createtextfromwstring" ) 
	#define CAL_sto_createtextfromwstring  sto_createtextfromwstring
	#define CHK_sto_createtextfromwstring  TRUE
	#define EXP_sto_createtextfromwstring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_createtextfromwstring", (RTS_UINTPTR)sto_createtextfromwstring, 1, RTSITF_GET_SIGNATURE(0, 0xAB9B0731), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_createtextfromwstring
	#define EXT_CmpCAAStoragesto_createtextfromwstring
	#define GET_CmpCAAStoragesto_createtextfromwstring  ERR_OK
	#define CAL_CmpCAAStoragesto_createtextfromwstring  sto_createtextfromwstring
	#define CHK_CmpCAAStoragesto_createtextfromwstring  TRUE
	#define EXP_CmpCAAStoragesto_createtextfromwstring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_createtextfromwstring", (RTS_UINTPTR)sto_createtextfromwstring, 1, RTSITF_GET_SIGNATURE(0, 0xAB9B0731), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_createtextfromwstring
	#define EXT_sto_createtextfromwstring
	#define GET_sto_createtextfromwstring(fl)  CAL_CMGETAPI( "sto_createtextfromwstring" ) 
	#define CAL_sto_createtextfromwstring  sto_createtextfromwstring
	#define CHK_sto_createtextfromwstring  TRUE
	#define EXP_sto_createtextfromwstring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_createtextfromwstring", (RTS_UINTPTR)sto_createtextfromwstring, 1, RTSITF_GET_SIGNATURE(0, 0xAB9B0731), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_createtextfromwstring  PFSTO_CREATETEXTFROMWSTRING_IEC pfsto_createtextfromwstring;
	#define EXT_sto_createtextfromwstring  extern PFSTO_CREATETEXTFROMWSTRING_IEC pfsto_createtextfromwstring;
	#define GET_sto_createtextfromwstring(fl)  s_pfCMGetAPI2( "sto_createtextfromwstring", (RTS_VOID_FCTPTR *)&pfsto_createtextfromwstring, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xAB9B0731), 0x03050528)
	#define CAL_sto_createtextfromwstring  pfsto_createtextfromwstring
	#define CHK_sto_createtextfromwstring  (pfsto_createtextfromwstring != NULL)
	#define EXP_sto_createtextfromwstring   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_createtextfromwstring", (RTS_UINTPTR)sto_createtextfromwstring, 1, RTSITF_GET_SIGNATURE(0, 0xAB9B0731), 0x03050528) 
#endif


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

void CDECL CDECL_EXT sto_datacopytoblob(sto_datacopytoblob_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_DATACOPYTOBLOB_IEC) (sto_datacopytoblob_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_DATACOPYTOBLOB_NOTIMPLEMENTED)
	#define USE_sto_datacopytoblob
	#define EXT_sto_datacopytoblob
	#define GET_sto_datacopytoblob(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_datacopytoblob(p0) 
	#define CHK_sto_datacopytoblob  FALSE
	#define EXP_sto_datacopytoblob  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_datacopytoblob
	#define EXT_sto_datacopytoblob
	#define GET_sto_datacopytoblob(fl)  CAL_CMGETAPI( "sto_datacopytoblob" ) 
	#define CAL_sto_datacopytoblob  sto_datacopytoblob
	#define CHK_sto_datacopytoblob  TRUE
	#define EXP_sto_datacopytoblob  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_datacopytoblob", (RTS_UINTPTR)sto_datacopytoblob, 1, RTSITF_GET_SIGNATURE(0, 0x8574D63E), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_datacopytoblob
	#define EXT_sto_datacopytoblob
	#define GET_sto_datacopytoblob(fl)  CAL_CMGETAPI( "sto_datacopytoblob" ) 
	#define CAL_sto_datacopytoblob  sto_datacopytoblob
	#define CHK_sto_datacopytoblob  TRUE
	#define EXP_sto_datacopytoblob  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_datacopytoblob", (RTS_UINTPTR)sto_datacopytoblob, 1, RTSITF_GET_SIGNATURE(0, 0x8574D63E), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_datacopytoblob
	#define EXT_CmpCAAStoragesto_datacopytoblob
	#define GET_CmpCAAStoragesto_datacopytoblob  ERR_OK
	#define CAL_CmpCAAStoragesto_datacopytoblob  sto_datacopytoblob
	#define CHK_CmpCAAStoragesto_datacopytoblob  TRUE
	#define EXP_CmpCAAStoragesto_datacopytoblob  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_datacopytoblob", (RTS_UINTPTR)sto_datacopytoblob, 1, RTSITF_GET_SIGNATURE(0, 0x8574D63E), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_datacopytoblob
	#define EXT_sto_datacopytoblob
	#define GET_sto_datacopytoblob(fl)  CAL_CMGETAPI( "sto_datacopytoblob" ) 
	#define CAL_sto_datacopytoblob  sto_datacopytoblob
	#define CHK_sto_datacopytoblob  TRUE
	#define EXP_sto_datacopytoblob  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_datacopytoblob", (RTS_UINTPTR)sto_datacopytoblob, 1, RTSITF_GET_SIGNATURE(0, 0x8574D63E), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_datacopytoblob  PFSTO_DATACOPYTOBLOB_IEC pfsto_datacopytoblob;
	#define EXT_sto_datacopytoblob  extern PFSTO_DATACOPYTOBLOB_IEC pfsto_datacopytoblob;
	#define GET_sto_datacopytoblob(fl)  s_pfCMGetAPI2( "sto_datacopytoblob", (RTS_VOID_FCTPTR *)&pfsto_datacopytoblob, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x8574D63E), 0x03050528)
	#define CAL_sto_datacopytoblob  pfsto_datacopytoblob
	#define CHK_sto_datacopytoblob  (pfsto_datacopytoblob != NULL)
	#define EXP_sto_datacopytoblob   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_datacopytoblob", (RTS_UINTPTR)sto_datacopytoblob, 1, RTSITF_GET_SIGNATURE(0, 0x8574D63E), 0x03050528) 
#endif


/**
 * <description>sto_dt_to_int64</description>
 */
typedef struct tagsto_dt_to_int64_struct
{
	RTS_IEC_DATE_AND_TIME dtValue;		/* VAR_INPUT */	
	CAA_ERROR STO_DT_TO_INT64;			/* VAR_OUTPUT */	
	RTS_IEC_INT64 i64Value;				/* VAR_OUTPUT */	
} sto_dt_to_int64_struct;

void CDECL CDECL_EXT sto_dt_to_int64(sto_dt_to_int64_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_DT_TO_INT64_IEC) (sto_dt_to_int64_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_DT_TO_INT64_NOTIMPLEMENTED)
	#define USE_sto_dt_to_int64
	#define EXT_sto_dt_to_int64
	#define GET_sto_dt_to_int64(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_dt_to_int64(p0) 
	#define CHK_sto_dt_to_int64  FALSE
	#define EXP_sto_dt_to_int64  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_dt_to_int64
	#define EXT_sto_dt_to_int64
	#define GET_sto_dt_to_int64(fl)  CAL_CMGETAPI( "sto_dt_to_int64" ) 
	#define CAL_sto_dt_to_int64  sto_dt_to_int64
	#define CHK_sto_dt_to_int64  TRUE
	#define EXP_sto_dt_to_int64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_dt_to_int64", (RTS_UINTPTR)sto_dt_to_int64, 1, RTSITF_GET_SIGNATURE(0, 0x82DE9C22), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_dt_to_int64
	#define EXT_sto_dt_to_int64
	#define GET_sto_dt_to_int64(fl)  CAL_CMGETAPI( "sto_dt_to_int64" ) 
	#define CAL_sto_dt_to_int64  sto_dt_to_int64
	#define CHK_sto_dt_to_int64  TRUE
	#define EXP_sto_dt_to_int64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_dt_to_int64", (RTS_UINTPTR)sto_dt_to_int64, 1, RTSITF_GET_SIGNATURE(0, 0x82DE9C22), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_dt_to_int64
	#define EXT_CmpCAAStoragesto_dt_to_int64
	#define GET_CmpCAAStoragesto_dt_to_int64  ERR_OK
	#define CAL_CmpCAAStoragesto_dt_to_int64  sto_dt_to_int64
	#define CHK_CmpCAAStoragesto_dt_to_int64  TRUE
	#define EXP_CmpCAAStoragesto_dt_to_int64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_dt_to_int64", (RTS_UINTPTR)sto_dt_to_int64, 1, RTSITF_GET_SIGNATURE(0, 0x82DE9C22), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_dt_to_int64
	#define EXT_sto_dt_to_int64
	#define GET_sto_dt_to_int64(fl)  CAL_CMGETAPI( "sto_dt_to_int64" ) 
	#define CAL_sto_dt_to_int64  sto_dt_to_int64
	#define CHK_sto_dt_to_int64  TRUE
	#define EXP_sto_dt_to_int64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_dt_to_int64", (RTS_UINTPTR)sto_dt_to_int64, 1, RTSITF_GET_SIGNATURE(0, 0x82DE9C22), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_dt_to_int64  PFSTO_DT_TO_INT64_IEC pfsto_dt_to_int64;
	#define EXT_sto_dt_to_int64  extern PFSTO_DT_TO_INT64_IEC pfsto_dt_to_int64;
	#define GET_sto_dt_to_int64(fl)  s_pfCMGetAPI2( "sto_dt_to_int64", (RTS_VOID_FCTPTR *)&pfsto_dt_to_int64, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x82DE9C22), 0x03050528)
	#define CAL_sto_dt_to_int64  pfsto_dt_to_int64
	#define CHK_sto_dt_to_int64  (pfsto_dt_to_int64 != NULL)
	#define EXP_sto_dt_to_int64   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_dt_to_int64", (RTS_UINTPTR)sto_dt_to_int64, 1, RTSITF_GET_SIGNATURE(0, 0x82DE9C22), 0x03050528) 
#endif


/**
 * <description>sto_dt_to_iso8601</description>
 */
typedef struct tagsto_dt_to_iso8601_struct
{
	RTS_IEC_DATE_AND_TIME dtValue;		/* VAR_INPUT */	
	RTS_IEC_ISO8601 *sValue;			/* VAR_IN_OUT */	
	CAA_ERROR STO_DT_TO_ISO8601;		/* VAR_OUTPUT */	
} sto_dt_to_iso8601_struct;

void CDECL CDECL_EXT sto_dt_to_iso8601(sto_dt_to_iso8601_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_DT_TO_ISO8601_IEC) (sto_dt_to_iso8601_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_DT_TO_ISO8601_NOTIMPLEMENTED)
	#define USE_sto_dt_to_iso8601
	#define EXT_sto_dt_to_iso8601
	#define GET_sto_dt_to_iso8601(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_dt_to_iso8601(p0) 
	#define CHK_sto_dt_to_iso8601  FALSE
	#define EXP_sto_dt_to_iso8601  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_dt_to_iso8601
	#define EXT_sto_dt_to_iso8601
	#define GET_sto_dt_to_iso8601(fl)  CAL_CMGETAPI( "sto_dt_to_iso8601" ) 
	#define CAL_sto_dt_to_iso8601  sto_dt_to_iso8601
	#define CHK_sto_dt_to_iso8601  TRUE
	#define EXP_sto_dt_to_iso8601  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_dt_to_iso8601", (RTS_UINTPTR)sto_dt_to_iso8601, 1, RTSITF_GET_SIGNATURE(0, 0x02D9A7F6), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_dt_to_iso8601
	#define EXT_sto_dt_to_iso8601
	#define GET_sto_dt_to_iso8601(fl)  CAL_CMGETAPI( "sto_dt_to_iso8601" ) 
	#define CAL_sto_dt_to_iso8601  sto_dt_to_iso8601
	#define CHK_sto_dt_to_iso8601  TRUE
	#define EXP_sto_dt_to_iso8601  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_dt_to_iso8601", (RTS_UINTPTR)sto_dt_to_iso8601, 1, RTSITF_GET_SIGNATURE(0, 0x02D9A7F6), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_dt_to_iso8601
	#define EXT_CmpCAAStoragesto_dt_to_iso8601
	#define GET_CmpCAAStoragesto_dt_to_iso8601  ERR_OK
	#define CAL_CmpCAAStoragesto_dt_to_iso8601  sto_dt_to_iso8601
	#define CHK_CmpCAAStoragesto_dt_to_iso8601  TRUE
	#define EXP_CmpCAAStoragesto_dt_to_iso8601  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_dt_to_iso8601", (RTS_UINTPTR)sto_dt_to_iso8601, 1, RTSITF_GET_SIGNATURE(0, 0x02D9A7F6), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_dt_to_iso8601
	#define EXT_sto_dt_to_iso8601
	#define GET_sto_dt_to_iso8601(fl)  CAL_CMGETAPI( "sto_dt_to_iso8601" ) 
	#define CAL_sto_dt_to_iso8601  sto_dt_to_iso8601
	#define CHK_sto_dt_to_iso8601  TRUE
	#define EXP_sto_dt_to_iso8601  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_dt_to_iso8601", (RTS_UINTPTR)sto_dt_to_iso8601, 1, RTSITF_GET_SIGNATURE(0, 0x02D9A7F6), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_dt_to_iso8601  PFSTO_DT_TO_ISO8601_IEC pfsto_dt_to_iso8601;
	#define EXT_sto_dt_to_iso8601  extern PFSTO_DT_TO_ISO8601_IEC pfsto_dt_to_iso8601;
	#define GET_sto_dt_to_iso8601(fl)  s_pfCMGetAPI2( "sto_dt_to_iso8601", (RTS_VOID_FCTPTR *)&pfsto_dt_to_iso8601, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x02D9A7F6), 0x03050528)
	#define CAL_sto_dt_to_iso8601  pfsto_dt_to_iso8601
	#define CHK_sto_dt_to_iso8601  (pfsto_dt_to_iso8601 != NULL)
	#define EXP_sto_dt_to_iso8601   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_dt_to_iso8601", (RTS_UINTPTR)sto_dt_to_iso8601, 1, RTSITF_GET_SIGNATURE(0, 0x02D9A7F6), 0x03050528) 
#endif


/**
 * <description>sto_dt_to_real8</description>
 */
typedef struct tagsto_dt_to_real8_struct
{
	RTS_IEC_DATE_AND_TIME dtValue;		/* VAR_INPUT */	
	CAA_ERROR STO_DT_TO_REAL8;			/* VAR_OUTPUT */	
	RTS_IEC_REAL8 r8Value;				/* VAR_OUTPUT */	
} sto_dt_to_real8_struct;

void CDECL CDECL_EXT sto_dt_to_real8(sto_dt_to_real8_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_DT_TO_REAL8_IEC) (sto_dt_to_real8_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_DT_TO_REAL8_NOTIMPLEMENTED)
	#define USE_sto_dt_to_real8
	#define EXT_sto_dt_to_real8
	#define GET_sto_dt_to_real8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_dt_to_real8(p0) 
	#define CHK_sto_dt_to_real8  FALSE
	#define EXP_sto_dt_to_real8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_dt_to_real8
	#define EXT_sto_dt_to_real8
	#define GET_sto_dt_to_real8(fl)  CAL_CMGETAPI( "sto_dt_to_real8" ) 
	#define CAL_sto_dt_to_real8  sto_dt_to_real8
	#define CHK_sto_dt_to_real8  TRUE
	#define EXP_sto_dt_to_real8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_dt_to_real8", (RTS_UINTPTR)sto_dt_to_real8, 1, RTSITF_GET_SIGNATURE(0, 0x7A40F574), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_dt_to_real8
	#define EXT_sto_dt_to_real8
	#define GET_sto_dt_to_real8(fl)  CAL_CMGETAPI( "sto_dt_to_real8" ) 
	#define CAL_sto_dt_to_real8  sto_dt_to_real8
	#define CHK_sto_dt_to_real8  TRUE
	#define EXP_sto_dt_to_real8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_dt_to_real8", (RTS_UINTPTR)sto_dt_to_real8, 1, RTSITF_GET_SIGNATURE(0, 0x7A40F574), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_dt_to_real8
	#define EXT_CmpCAAStoragesto_dt_to_real8
	#define GET_CmpCAAStoragesto_dt_to_real8  ERR_OK
	#define CAL_CmpCAAStoragesto_dt_to_real8  sto_dt_to_real8
	#define CHK_CmpCAAStoragesto_dt_to_real8  TRUE
	#define EXP_CmpCAAStoragesto_dt_to_real8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_dt_to_real8", (RTS_UINTPTR)sto_dt_to_real8, 1, RTSITF_GET_SIGNATURE(0, 0x7A40F574), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_dt_to_real8
	#define EXT_sto_dt_to_real8
	#define GET_sto_dt_to_real8(fl)  CAL_CMGETAPI( "sto_dt_to_real8" ) 
	#define CAL_sto_dt_to_real8  sto_dt_to_real8
	#define CHK_sto_dt_to_real8  TRUE
	#define EXP_sto_dt_to_real8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_dt_to_real8", (RTS_UINTPTR)sto_dt_to_real8, 1, RTSITF_GET_SIGNATURE(0, 0x7A40F574), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_dt_to_real8  PFSTO_DT_TO_REAL8_IEC pfsto_dt_to_real8;
	#define EXT_sto_dt_to_real8  extern PFSTO_DT_TO_REAL8_IEC pfsto_dt_to_real8;
	#define GET_sto_dt_to_real8(fl)  s_pfCMGetAPI2( "sto_dt_to_real8", (RTS_VOID_FCTPTR *)&pfsto_dt_to_real8, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x7A40F574), 0x03050528)
	#define CAL_sto_dt_to_real8  pfsto_dt_to_real8
	#define CHK_sto_dt_to_real8  (pfsto_dt_to_real8 != NULL)
	#define EXP_sto_dt_to_real8   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_dt_to_real8", (RTS_UINTPTR)sto_dt_to_real8, 1, RTSITF_GET_SIGNATURE(0, 0x7A40F574), 0x03050528) 
#endif


/**
 * <description>sto_getsupplierversion</description>
 */
typedef struct tagsto_getsupplierversion_struct
{
	CAA_BOOL xDummy;					/* VAR_INPUT */	
	RTS_IEC_WORD STO_GetSupplierVersion;	/* VAR_OUTPUT */	
} sto_getsupplierversion_struct;

void CDECL CDECL_EXT sto_getsupplierversion(sto_getsupplierversion_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_GETSUPPLIERVERSION_IEC) (sto_getsupplierversion_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_sto_getsupplierversion
	#define EXT_sto_getsupplierversion
	#define GET_sto_getsupplierversion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_getsupplierversion(p0) 
	#define CHK_sto_getsupplierversion  FALSE
	#define EXP_sto_getsupplierversion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_getsupplierversion
	#define EXT_sto_getsupplierversion
	#define GET_sto_getsupplierversion(fl)  CAL_CMGETAPI( "sto_getsupplierversion" ) 
	#define CAL_sto_getsupplierversion  sto_getsupplierversion
	#define CHK_sto_getsupplierversion  TRUE
	#define EXP_sto_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_getsupplierversion", (RTS_UINTPTR)sto_getsupplierversion, 1, 0x26CD734B, 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_getsupplierversion
	#define EXT_sto_getsupplierversion
	#define GET_sto_getsupplierversion(fl)  CAL_CMGETAPI( "sto_getsupplierversion" ) 
	#define CAL_sto_getsupplierversion  sto_getsupplierversion
	#define CHK_sto_getsupplierversion  TRUE
	#define EXP_sto_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_getsupplierversion", (RTS_UINTPTR)sto_getsupplierversion, 1, 0x26CD734B, 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_getsupplierversion
	#define EXT_CmpCAAStoragesto_getsupplierversion
	#define GET_CmpCAAStoragesto_getsupplierversion  ERR_OK
	#define CAL_CmpCAAStoragesto_getsupplierversion  sto_getsupplierversion
	#define CHK_CmpCAAStoragesto_getsupplierversion  TRUE
	#define EXP_CmpCAAStoragesto_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_getsupplierversion", (RTS_UINTPTR)sto_getsupplierversion, 1, 0x26CD734B, 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_getsupplierversion
	#define EXT_sto_getsupplierversion
	#define GET_sto_getsupplierversion(fl)  CAL_CMGETAPI( "sto_getsupplierversion" ) 
	#define CAL_sto_getsupplierversion  sto_getsupplierversion
	#define CHK_sto_getsupplierversion  TRUE
	#define EXP_sto_getsupplierversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_getsupplierversion", (RTS_UINTPTR)sto_getsupplierversion, 1, 0x26CD734B, 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_getsupplierversion  PFSTO_GETSUPPLIERVERSION_IEC pfsto_getsupplierversion;
	#define EXT_sto_getsupplierversion  extern PFSTO_GETSUPPLIERVERSION_IEC pfsto_getsupplierversion;
	#define GET_sto_getsupplierversion(fl)  s_pfCMGetAPI2( "sto_getsupplierversion", (RTS_VOID_FCTPTR *)&pfsto_getsupplierversion, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x26CD734B, 0x03050528)
	#define CAL_sto_getsupplierversion  pfsto_getsupplierversion
	#define CHK_sto_getsupplierversion  (pfsto_getsupplierversion != NULL)
	#define EXP_sto_getsupplierversion   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_getsupplierversion", (RTS_UINTPTR)sto_getsupplierversion, 1, 0x26CD734B, 0x03050528) 
#endif


/**
 * <description>sto_int64_to_dt</description>
 */
typedef struct tagsto_int64_to_dt_struct
{
	RTS_IEC_INT64 i64Value;				/* VAR_INPUT */	
	CAA_ERROR STO_INT64_TO_DT;			/* VAR_OUTPUT */	
	RTS_IEC_DATE_AND_TIME dtValue;		/* VAR_OUTPUT */	
} sto_int64_to_dt_struct;

void CDECL CDECL_EXT sto_int64_to_dt(sto_int64_to_dt_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_INT64_TO_DT_IEC) (sto_int64_to_dt_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_INT64_TO_DT_NOTIMPLEMENTED)
	#define USE_sto_int64_to_dt
	#define EXT_sto_int64_to_dt
	#define GET_sto_int64_to_dt(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_int64_to_dt(p0) 
	#define CHK_sto_int64_to_dt  FALSE
	#define EXP_sto_int64_to_dt  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_int64_to_dt
	#define EXT_sto_int64_to_dt
	#define GET_sto_int64_to_dt(fl)  CAL_CMGETAPI( "sto_int64_to_dt" ) 
	#define CAL_sto_int64_to_dt  sto_int64_to_dt
	#define CHK_sto_int64_to_dt  TRUE
	#define EXP_sto_int64_to_dt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_dt", (RTS_UINTPTR)sto_int64_to_dt, 1, RTSITF_GET_SIGNATURE(0, 0xC04F4CAE), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_int64_to_dt
	#define EXT_sto_int64_to_dt
	#define GET_sto_int64_to_dt(fl)  CAL_CMGETAPI( "sto_int64_to_dt" ) 
	#define CAL_sto_int64_to_dt  sto_int64_to_dt
	#define CHK_sto_int64_to_dt  TRUE
	#define EXP_sto_int64_to_dt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_dt", (RTS_UINTPTR)sto_int64_to_dt, 1, RTSITF_GET_SIGNATURE(0, 0xC04F4CAE), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_int64_to_dt
	#define EXT_CmpCAAStoragesto_int64_to_dt
	#define GET_CmpCAAStoragesto_int64_to_dt  ERR_OK
	#define CAL_CmpCAAStoragesto_int64_to_dt  sto_int64_to_dt
	#define CHK_CmpCAAStoragesto_int64_to_dt  TRUE
	#define EXP_CmpCAAStoragesto_int64_to_dt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_dt", (RTS_UINTPTR)sto_int64_to_dt, 1, RTSITF_GET_SIGNATURE(0, 0xC04F4CAE), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_int64_to_dt
	#define EXT_sto_int64_to_dt
	#define GET_sto_int64_to_dt(fl)  CAL_CMGETAPI( "sto_int64_to_dt" ) 
	#define CAL_sto_int64_to_dt  sto_int64_to_dt
	#define CHK_sto_int64_to_dt  TRUE
	#define EXP_sto_int64_to_dt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_dt", (RTS_UINTPTR)sto_int64_to_dt, 1, RTSITF_GET_SIGNATURE(0, 0xC04F4CAE), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_int64_to_dt  PFSTO_INT64_TO_DT_IEC pfsto_int64_to_dt;
	#define EXT_sto_int64_to_dt  extern PFSTO_INT64_TO_DT_IEC pfsto_int64_to_dt;
	#define GET_sto_int64_to_dt(fl)  s_pfCMGetAPI2( "sto_int64_to_dt", (RTS_VOID_FCTPTR *)&pfsto_int64_to_dt, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xC04F4CAE), 0x03050528)
	#define CAL_sto_int64_to_dt  pfsto_int64_to_dt
	#define CHK_sto_int64_to_dt  (pfsto_int64_to_dt != NULL)
	#define EXP_sto_int64_to_dt   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_dt", (RTS_UINTPTR)sto_int64_to_dt, 1, RTSITF_GET_SIGNATURE(0, 0xC04F4CAE), 0x03050528) 
#endif


/**
 * ISO8601 string ("YYYY-MM-DD HH:MM:SS.SSS")
 */
typedef struct tagsto_int64_to_iso8601_struct
{
	RTS_IEC_INT64 i64Value;				/* VAR_INPUT */	
	RTS_IEC_ISO8601 *sValue;			/* VAR_IN_OUT */	
	CAA_ERROR STO_INT64_TO_ISO8601;		/* VAR_OUTPUT */	
} sto_int64_to_iso8601_struct;

void CDECL CDECL_EXT sto_int64_to_iso8601(sto_int64_to_iso8601_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_INT64_TO_ISO8601_IEC) (sto_int64_to_iso8601_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_INT64_TO_ISO8601_NOTIMPLEMENTED)
	#define USE_sto_int64_to_iso8601
	#define EXT_sto_int64_to_iso8601
	#define GET_sto_int64_to_iso8601(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_int64_to_iso8601(p0) 
	#define CHK_sto_int64_to_iso8601  FALSE
	#define EXP_sto_int64_to_iso8601  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_int64_to_iso8601
	#define EXT_sto_int64_to_iso8601
	#define GET_sto_int64_to_iso8601(fl)  CAL_CMGETAPI( "sto_int64_to_iso8601" ) 
	#define CAL_sto_int64_to_iso8601  sto_int64_to_iso8601
	#define CHK_sto_int64_to_iso8601  TRUE
	#define EXP_sto_int64_to_iso8601  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_iso8601", (RTS_UINTPTR)sto_int64_to_iso8601, 1, RTSITF_GET_SIGNATURE(0, 0x5764574C), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_int64_to_iso8601
	#define EXT_sto_int64_to_iso8601
	#define GET_sto_int64_to_iso8601(fl)  CAL_CMGETAPI( "sto_int64_to_iso8601" ) 
	#define CAL_sto_int64_to_iso8601  sto_int64_to_iso8601
	#define CHK_sto_int64_to_iso8601  TRUE
	#define EXP_sto_int64_to_iso8601  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_iso8601", (RTS_UINTPTR)sto_int64_to_iso8601, 1, RTSITF_GET_SIGNATURE(0, 0x5764574C), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_int64_to_iso8601
	#define EXT_CmpCAAStoragesto_int64_to_iso8601
	#define GET_CmpCAAStoragesto_int64_to_iso8601  ERR_OK
	#define CAL_CmpCAAStoragesto_int64_to_iso8601  sto_int64_to_iso8601
	#define CHK_CmpCAAStoragesto_int64_to_iso8601  TRUE
	#define EXP_CmpCAAStoragesto_int64_to_iso8601  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_iso8601", (RTS_UINTPTR)sto_int64_to_iso8601, 1, RTSITF_GET_SIGNATURE(0, 0x5764574C), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_int64_to_iso8601
	#define EXT_sto_int64_to_iso8601
	#define GET_sto_int64_to_iso8601(fl)  CAL_CMGETAPI( "sto_int64_to_iso8601" ) 
	#define CAL_sto_int64_to_iso8601  sto_int64_to_iso8601
	#define CHK_sto_int64_to_iso8601  TRUE
	#define EXP_sto_int64_to_iso8601  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_iso8601", (RTS_UINTPTR)sto_int64_to_iso8601, 1, RTSITF_GET_SIGNATURE(0, 0x5764574C), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_int64_to_iso8601  PFSTO_INT64_TO_ISO8601_IEC pfsto_int64_to_iso8601;
	#define EXT_sto_int64_to_iso8601  extern PFSTO_INT64_TO_ISO8601_IEC pfsto_int64_to_iso8601;
	#define GET_sto_int64_to_iso8601(fl)  s_pfCMGetAPI2( "sto_int64_to_iso8601", (RTS_VOID_FCTPTR *)&pfsto_int64_to_iso8601, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x5764574C), 0x03050528)
	#define CAL_sto_int64_to_iso8601  pfsto_int64_to_iso8601
	#define CHK_sto_int64_to_iso8601  (pfsto_int64_to_iso8601 != NULL)
	#define EXP_sto_int64_to_iso8601   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_iso8601", (RTS_UINTPTR)sto_int64_to_iso8601, 1, RTSITF_GET_SIGNATURE(0, 0x5764574C), 0x03050528) 
#endif


/**
 * <description>sto_int64_to_localtime</description>
 */
typedef struct tagsto_int64_to_localtime_struct
{
	RTS_IEC_INT64 i64UTC;				/* VAR_INPUT */	
	CAA_ERROR STO_INT64_TO_LOCALTIME;	/* VAR_OUTPUT */	
	RTS_IEC_INT64 i64Local;				/* VAR_OUTPUT */	
} sto_int64_to_localtime_struct;

void CDECL CDECL_EXT sto_int64_to_localtime(sto_int64_to_localtime_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_INT64_TO_LOCALTIME_IEC) (sto_int64_to_localtime_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_INT64_TO_LOCALTIME_NOTIMPLEMENTED)
	#define USE_sto_int64_to_localtime
	#define EXT_sto_int64_to_localtime
	#define GET_sto_int64_to_localtime(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_int64_to_localtime(p0) 
	#define CHK_sto_int64_to_localtime  FALSE
	#define EXP_sto_int64_to_localtime  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_int64_to_localtime
	#define EXT_sto_int64_to_localtime
	#define GET_sto_int64_to_localtime(fl)  CAL_CMGETAPI( "sto_int64_to_localtime" ) 
	#define CAL_sto_int64_to_localtime  sto_int64_to_localtime
	#define CHK_sto_int64_to_localtime  TRUE
	#define EXP_sto_int64_to_localtime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_localtime", (RTS_UINTPTR)sto_int64_to_localtime, 1, RTSITF_GET_SIGNATURE(0, 0x7ED9A18B), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_int64_to_localtime
	#define EXT_sto_int64_to_localtime
	#define GET_sto_int64_to_localtime(fl)  CAL_CMGETAPI( "sto_int64_to_localtime" ) 
	#define CAL_sto_int64_to_localtime  sto_int64_to_localtime
	#define CHK_sto_int64_to_localtime  TRUE
	#define EXP_sto_int64_to_localtime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_localtime", (RTS_UINTPTR)sto_int64_to_localtime, 1, RTSITF_GET_SIGNATURE(0, 0x7ED9A18B), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_int64_to_localtime
	#define EXT_CmpCAAStoragesto_int64_to_localtime
	#define GET_CmpCAAStoragesto_int64_to_localtime  ERR_OK
	#define CAL_CmpCAAStoragesto_int64_to_localtime  sto_int64_to_localtime
	#define CHK_CmpCAAStoragesto_int64_to_localtime  TRUE
	#define EXP_CmpCAAStoragesto_int64_to_localtime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_localtime", (RTS_UINTPTR)sto_int64_to_localtime, 1, RTSITF_GET_SIGNATURE(0, 0x7ED9A18B), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_int64_to_localtime
	#define EXT_sto_int64_to_localtime
	#define GET_sto_int64_to_localtime(fl)  CAL_CMGETAPI( "sto_int64_to_localtime" ) 
	#define CAL_sto_int64_to_localtime  sto_int64_to_localtime
	#define CHK_sto_int64_to_localtime  TRUE
	#define EXP_sto_int64_to_localtime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_localtime", (RTS_UINTPTR)sto_int64_to_localtime, 1, RTSITF_GET_SIGNATURE(0, 0x7ED9A18B), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_int64_to_localtime  PFSTO_INT64_TO_LOCALTIME_IEC pfsto_int64_to_localtime;
	#define EXT_sto_int64_to_localtime  extern PFSTO_INT64_TO_LOCALTIME_IEC pfsto_int64_to_localtime;
	#define GET_sto_int64_to_localtime(fl)  s_pfCMGetAPI2( "sto_int64_to_localtime", (RTS_VOID_FCTPTR *)&pfsto_int64_to_localtime, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x7ED9A18B), 0x03050528)
	#define CAL_sto_int64_to_localtime  pfsto_int64_to_localtime
	#define CHK_sto_int64_to_localtime  (pfsto_int64_to_localtime != NULL)
	#define EXP_sto_int64_to_localtime   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_localtime", (RTS_UINTPTR)sto_int64_to_localtime, 1, RTSITF_GET_SIGNATURE(0, 0x7ED9A18B), 0x03050528) 
#endif


/**
 * <description>sto_int64_to_ltime</description>
 */
typedef struct tagsto_int64_to_ltime_struct
{
	RTS_IEC_INT64 i64Value;				/* VAR_INPUT */	
	CAA_ERROR STO_INT64_TO_LTIME;		/* VAR_OUTPUT */	
	RTS_IEC_LTIME ltValue;				/* VAR_OUTPUT */	
} sto_int64_to_ltime_struct;

void CDECL CDECL_EXT sto_int64_to_ltime(sto_int64_to_ltime_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_INT64_TO_LTIME_IEC) (sto_int64_to_ltime_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_INT64_TO_LTIME_NOTIMPLEMENTED)
	#define USE_sto_int64_to_ltime
	#define EXT_sto_int64_to_ltime
	#define GET_sto_int64_to_ltime(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_int64_to_ltime(p0) 
	#define CHK_sto_int64_to_ltime  FALSE
	#define EXP_sto_int64_to_ltime  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_int64_to_ltime
	#define EXT_sto_int64_to_ltime
	#define GET_sto_int64_to_ltime(fl)  CAL_CMGETAPI( "sto_int64_to_ltime" ) 
	#define CAL_sto_int64_to_ltime  sto_int64_to_ltime
	#define CHK_sto_int64_to_ltime  TRUE
	#define EXP_sto_int64_to_ltime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_ltime", (RTS_UINTPTR)sto_int64_to_ltime, 1, RTSITF_GET_SIGNATURE(0, 0x56E5A814), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_int64_to_ltime
	#define EXT_sto_int64_to_ltime
	#define GET_sto_int64_to_ltime(fl)  CAL_CMGETAPI( "sto_int64_to_ltime" ) 
	#define CAL_sto_int64_to_ltime  sto_int64_to_ltime
	#define CHK_sto_int64_to_ltime  TRUE
	#define EXP_sto_int64_to_ltime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_ltime", (RTS_UINTPTR)sto_int64_to_ltime, 1, RTSITF_GET_SIGNATURE(0, 0x56E5A814), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_int64_to_ltime
	#define EXT_CmpCAAStoragesto_int64_to_ltime
	#define GET_CmpCAAStoragesto_int64_to_ltime  ERR_OK
	#define CAL_CmpCAAStoragesto_int64_to_ltime  sto_int64_to_ltime
	#define CHK_CmpCAAStoragesto_int64_to_ltime  TRUE
	#define EXP_CmpCAAStoragesto_int64_to_ltime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_ltime", (RTS_UINTPTR)sto_int64_to_ltime, 1, RTSITF_GET_SIGNATURE(0, 0x56E5A814), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_int64_to_ltime
	#define EXT_sto_int64_to_ltime
	#define GET_sto_int64_to_ltime(fl)  CAL_CMGETAPI( "sto_int64_to_ltime" ) 
	#define CAL_sto_int64_to_ltime  sto_int64_to_ltime
	#define CHK_sto_int64_to_ltime  TRUE
	#define EXP_sto_int64_to_ltime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_ltime", (RTS_UINTPTR)sto_int64_to_ltime, 1, RTSITF_GET_SIGNATURE(0, 0x56E5A814), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_int64_to_ltime  PFSTO_INT64_TO_LTIME_IEC pfsto_int64_to_ltime;
	#define EXT_sto_int64_to_ltime  extern PFSTO_INT64_TO_LTIME_IEC pfsto_int64_to_ltime;
	#define GET_sto_int64_to_ltime(fl)  s_pfCMGetAPI2( "sto_int64_to_ltime", (RTS_VOID_FCTPTR *)&pfsto_int64_to_ltime, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x56E5A814), 0x03050528)
	#define CAL_sto_int64_to_ltime  pfsto_int64_to_ltime
	#define CHK_sto_int64_to_ltime  (pfsto_int64_to_ltime != NULL)
	#define EXP_sto_int64_to_ltime   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_ltime", (RTS_UINTPTR)sto_int64_to_ltime, 1, RTSITF_GET_SIGNATURE(0, 0x56E5A814), 0x03050528) 
#endif


/**
 * <description>sto_int64_to_real8</description>
 */
typedef struct tagsto_int64_to_real8_struct
{
	RTS_IEC_INT64 i64Value;				/* VAR_INPUT */	
	CAA_ERROR STO_INT64_TO_REAL8;		/* VAR_OUTPUT */	
	RTS_IEC_REAL8 r8Value;				/* VAR_OUTPUT */	
} sto_int64_to_real8_struct;

void CDECL CDECL_EXT sto_int64_to_real8(sto_int64_to_real8_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_INT64_TO_REAL8_IEC) (sto_int64_to_real8_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_INT64_TO_REAL8_NOTIMPLEMENTED)
	#define USE_sto_int64_to_real8
	#define EXT_sto_int64_to_real8
	#define GET_sto_int64_to_real8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_int64_to_real8(p0) 
	#define CHK_sto_int64_to_real8  FALSE
	#define EXP_sto_int64_to_real8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_int64_to_real8
	#define EXT_sto_int64_to_real8
	#define GET_sto_int64_to_real8(fl)  CAL_CMGETAPI( "sto_int64_to_real8" ) 
	#define CAL_sto_int64_to_real8  sto_int64_to_real8
	#define CHK_sto_int64_to_real8  TRUE
	#define EXP_sto_int64_to_real8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_real8", (RTS_UINTPTR)sto_int64_to_real8, 1, RTSITF_GET_SIGNATURE(0, 0xD54A069D), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_int64_to_real8
	#define EXT_sto_int64_to_real8
	#define GET_sto_int64_to_real8(fl)  CAL_CMGETAPI( "sto_int64_to_real8" ) 
	#define CAL_sto_int64_to_real8  sto_int64_to_real8
	#define CHK_sto_int64_to_real8  TRUE
	#define EXP_sto_int64_to_real8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_real8", (RTS_UINTPTR)sto_int64_to_real8, 1, RTSITF_GET_SIGNATURE(0, 0xD54A069D), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_int64_to_real8
	#define EXT_CmpCAAStoragesto_int64_to_real8
	#define GET_CmpCAAStoragesto_int64_to_real8  ERR_OK
	#define CAL_CmpCAAStoragesto_int64_to_real8  sto_int64_to_real8
	#define CHK_CmpCAAStoragesto_int64_to_real8  TRUE
	#define EXP_CmpCAAStoragesto_int64_to_real8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_real8", (RTS_UINTPTR)sto_int64_to_real8, 1, RTSITF_GET_SIGNATURE(0, 0xD54A069D), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_int64_to_real8
	#define EXT_sto_int64_to_real8
	#define GET_sto_int64_to_real8(fl)  CAL_CMGETAPI( "sto_int64_to_real8" ) 
	#define CAL_sto_int64_to_real8  sto_int64_to_real8
	#define CHK_sto_int64_to_real8  TRUE
	#define EXP_sto_int64_to_real8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_real8", (RTS_UINTPTR)sto_int64_to_real8, 1, RTSITF_GET_SIGNATURE(0, 0xD54A069D), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_int64_to_real8  PFSTO_INT64_TO_REAL8_IEC pfsto_int64_to_real8;
	#define EXT_sto_int64_to_real8  extern PFSTO_INT64_TO_REAL8_IEC pfsto_int64_to_real8;
	#define GET_sto_int64_to_real8(fl)  s_pfCMGetAPI2( "sto_int64_to_real8", (RTS_VOID_FCTPTR *)&pfsto_int64_to_real8, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xD54A069D), 0x03050528)
	#define CAL_sto_int64_to_real8  pfsto_int64_to_real8
	#define CHK_sto_int64_to_real8  (pfsto_int64_to_real8 != NULL)
	#define EXP_sto_int64_to_real8   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_real8", (RTS_UINTPTR)sto_int64_to_real8, 1, RTSITF_GET_SIGNATURE(0, 0xD54A069D), 0x03050528) 
#endif


/**
 * <description>sto_int64_to_time</description>
 */
typedef struct tagsto_int64_to_time_struct
{
	RTS_IEC_INT64 i64Value;				/* VAR_INPUT */	
	CAA_ERROR STO_INT64_TO_TIME;		/* VAR_OUTPUT */	
	RTS_IEC_TIME tValue;				/* VAR_OUTPUT */	
} sto_int64_to_time_struct;

void CDECL CDECL_EXT sto_int64_to_time(sto_int64_to_time_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_INT64_TO_TIME_IEC) (sto_int64_to_time_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_INT64_TO_TIME_NOTIMPLEMENTED)
	#define USE_sto_int64_to_time
	#define EXT_sto_int64_to_time
	#define GET_sto_int64_to_time(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_int64_to_time(p0) 
	#define CHK_sto_int64_to_time  FALSE
	#define EXP_sto_int64_to_time  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_int64_to_time
	#define EXT_sto_int64_to_time
	#define GET_sto_int64_to_time(fl)  CAL_CMGETAPI( "sto_int64_to_time" ) 
	#define CAL_sto_int64_to_time  sto_int64_to_time
	#define CHK_sto_int64_to_time  TRUE
	#define EXP_sto_int64_to_time  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_time", (RTS_UINTPTR)sto_int64_to_time, 1, RTSITF_GET_SIGNATURE(0, 0x4AF215D2), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_int64_to_time
	#define EXT_sto_int64_to_time
	#define GET_sto_int64_to_time(fl)  CAL_CMGETAPI( "sto_int64_to_time" ) 
	#define CAL_sto_int64_to_time  sto_int64_to_time
	#define CHK_sto_int64_to_time  TRUE
	#define EXP_sto_int64_to_time  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_time", (RTS_UINTPTR)sto_int64_to_time, 1, RTSITF_GET_SIGNATURE(0, 0x4AF215D2), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_int64_to_time
	#define EXT_CmpCAAStoragesto_int64_to_time
	#define GET_CmpCAAStoragesto_int64_to_time  ERR_OK
	#define CAL_CmpCAAStoragesto_int64_to_time  sto_int64_to_time
	#define CHK_CmpCAAStoragesto_int64_to_time  TRUE
	#define EXP_CmpCAAStoragesto_int64_to_time  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_time", (RTS_UINTPTR)sto_int64_to_time, 1, RTSITF_GET_SIGNATURE(0, 0x4AF215D2), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_int64_to_time
	#define EXT_sto_int64_to_time
	#define GET_sto_int64_to_time(fl)  CAL_CMGETAPI( "sto_int64_to_time" ) 
	#define CAL_sto_int64_to_time  sto_int64_to_time
	#define CHK_sto_int64_to_time  TRUE
	#define EXP_sto_int64_to_time  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_time", (RTS_UINTPTR)sto_int64_to_time, 1, RTSITF_GET_SIGNATURE(0, 0x4AF215D2), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_int64_to_time  PFSTO_INT64_TO_TIME_IEC pfsto_int64_to_time;
	#define EXT_sto_int64_to_time  extern PFSTO_INT64_TO_TIME_IEC pfsto_int64_to_time;
	#define GET_sto_int64_to_time(fl)  s_pfCMGetAPI2( "sto_int64_to_time", (RTS_VOID_FCTPTR *)&pfsto_int64_to_time, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x4AF215D2), 0x03050528)
	#define CAL_sto_int64_to_time  pfsto_int64_to_time
	#define CHK_sto_int64_to_time  (pfsto_int64_to_time != NULL)
	#define EXP_sto_int64_to_time   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_time", (RTS_UINTPTR)sto_int64_to_time, 1, RTSITF_GET_SIGNATURE(0, 0x4AF215D2), 0x03050528) 
#endif


/**
 * <description>sto_int64_to_utc</description>
 */
typedef struct tagsto_int64_to_utc_struct
{
	RTS_IEC_INT64 i64Local;				/* VAR_INPUT */	
	CAA_ERROR STO_INT64_TO_UTC;			/* VAR_OUTPUT */	
	RTS_IEC_INT64 i64UTC;				/* VAR_OUTPUT */	
} sto_int64_to_utc_struct;

void CDECL CDECL_EXT sto_int64_to_utc(sto_int64_to_utc_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_INT64_TO_UTC_IEC) (sto_int64_to_utc_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_INT64_TO_UTC_NOTIMPLEMENTED)
	#define USE_sto_int64_to_utc
	#define EXT_sto_int64_to_utc
	#define GET_sto_int64_to_utc(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_int64_to_utc(p0) 
	#define CHK_sto_int64_to_utc  FALSE
	#define EXP_sto_int64_to_utc  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_int64_to_utc
	#define EXT_sto_int64_to_utc
	#define GET_sto_int64_to_utc(fl)  CAL_CMGETAPI( "sto_int64_to_utc" ) 
	#define CAL_sto_int64_to_utc  sto_int64_to_utc
	#define CHK_sto_int64_to_utc  TRUE
	#define EXP_sto_int64_to_utc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_utc", (RTS_UINTPTR)sto_int64_to_utc, 1, RTSITF_GET_SIGNATURE(0, 0xC06DAE79), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_int64_to_utc
	#define EXT_sto_int64_to_utc
	#define GET_sto_int64_to_utc(fl)  CAL_CMGETAPI( "sto_int64_to_utc" ) 
	#define CAL_sto_int64_to_utc  sto_int64_to_utc
	#define CHK_sto_int64_to_utc  TRUE
	#define EXP_sto_int64_to_utc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_utc", (RTS_UINTPTR)sto_int64_to_utc, 1, RTSITF_GET_SIGNATURE(0, 0xC06DAE79), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_int64_to_utc
	#define EXT_CmpCAAStoragesto_int64_to_utc
	#define GET_CmpCAAStoragesto_int64_to_utc  ERR_OK
	#define CAL_CmpCAAStoragesto_int64_to_utc  sto_int64_to_utc
	#define CHK_CmpCAAStoragesto_int64_to_utc  TRUE
	#define EXP_CmpCAAStoragesto_int64_to_utc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_utc", (RTS_UINTPTR)sto_int64_to_utc, 1, RTSITF_GET_SIGNATURE(0, 0xC06DAE79), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_int64_to_utc
	#define EXT_sto_int64_to_utc
	#define GET_sto_int64_to_utc(fl)  CAL_CMGETAPI( "sto_int64_to_utc" ) 
	#define CAL_sto_int64_to_utc  sto_int64_to_utc
	#define CHK_sto_int64_to_utc  TRUE
	#define EXP_sto_int64_to_utc  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_utc", (RTS_UINTPTR)sto_int64_to_utc, 1, RTSITF_GET_SIGNATURE(0, 0xC06DAE79), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_int64_to_utc  PFSTO_INT64_TO_UTC_IEC pfsto_int64_to_utc;
	#define EXT_sto_int64_to_utc  extern PFSTO_INT64_TO_UTC_IEC pfsto_int64_to_utc;
	#define GET_sto_int64_to_utc(fl)  s_pfCMGetAPI2( "sto_int64_to_utc", (RTS_VOID_FCTPTR *)&pfsto_int64_to_utc, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xC06DAE79), 0x03050528)
	#define CAL_sto_int64_to_utc  pfsto_int64_to_utc
	#define CHK_sto_int64_to_utc  (pfsto_int64_to_utc != NULL)
	#define EXP_sto_int64_to_utc   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_int64_to_utc", (RTS_UINTPTR)sto_int64_to_utc, 1, RTSITF_GET_SIGNATURE(0, 0xC06DAE79), 0x03050528) 
#endif


/**
 * <description>sto_iso8601_to_dt</description>
 */
typedef struct tagsto_iso8601_to_dt_struct
{
	RTS_IEC_ISO8601 *sValue;			/* VAR_IN_OUT */	
	CAA_ERROR STO_ISO8601_TO_DT;		/* VAR_OUTPUT */	
	RTS_IEC_DATE_AND_TIME dtValue;		/* VAR_OUTPUT */	
} sto_iso8601_to_dt_struct;

void CDECL CDECL_EXT sto_iso8601_to_dt(sto_iso8601_to_dt_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_ISO8601_TO_DT_IEC) (sto_iso8601_to_dt_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_ISO8601_TO_DT_NOTIMPLEMENTED)
	#define USE_sto_iso8601_to_dt
	#define EXT_sto_iso8601_to_dt
	#define GET_sto_iso8601_to_dt(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_iso8601_to_dt(p0) 
	#define CHK_sto_iso8601_to_dt  FALSE
	#define EXP_sto_iso8601_to_dt  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_iso8601_to_dt
	#define EXT_sto_iso8601_to_dt
	#define GET_sto_iso8601_to_dt(fl)  CAL_CMGETAPI( "sto_iso8601_to_dt" ) 
	#define CAL_sto_iso8601_to_dt  sto_iso8601_to_dt
	#define CHK_sto_iso8601_to_dt  TRUE
	#define EXP_sto_iso8601_to_dt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_iso8601_to_dt", (RTS_UINTPTR)sto_iso8601_to_dt, 1, RTSITF_GET_SIGNATURE(0, 0xB3451243), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_iso8601_to_dt
	#define EXT_sto_iso8601_to_dt
	#define GET_sto_iso8601_to_dt(fl)  CAL_CMGETAPI( "sto_iso8601_to_dt" ) 
	#define CAL_sto_iso8601_to_dt  sto_iso8601_to_dt
	#define CHK_sto_iso8601_to_dt  TRUE
	#define EXP_sto_iso8601_to_dt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_iso8601_to_dt", (RTS_UINTPTR)sto_iso8601_to_dt, 1, RTSITF_GET_SIGNATURE(0, 0xB3451243), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_iso8601_to_dt
	#define EXT_CmpCAAStoragesto_iso8601_to_dt
	#define GET_CmpCAAStoragesto_iso8601_to_dt  ERR_OK
	#define CAL_CmpCAAStoragesto_iso8601_to_dt  sto_iso8601_to_dt
	#define CHK_CmpCAAStoragesto_iso8601_to_dt  TRUE
	#define EXP_CmpCAAStoragesto_iso8601_to_dt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_iso8601_to_dt", (RTS_UINTPTR)sto_iso8601_to_dt, 1, RTSITF_GET_SIGNATURE(0, 0xB3451243), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_iso8601_to_dt
	#define EXT_sto_iso8601_to_dt
	#define GET_sto_iso8601_to_dt(fl)  CAL_CMGETAPI( "sto_iso8601_to_dt" ) 
	#define CAL_sto_iso8601_to_dt  sto_iso8601_to_dt
	#define CHK_sto_iso8601_to_dt  TRUE
	#define EXP_sto_iso8601_to_dt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_iso8601_to_dt", (RTS_UINTPTR)sto_iso8601_to_dt, 1, RTSITF_GET_SIGNATURE(0, 0xB3451243), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_iso8601_to_dt  PFSTO_ISO8601_TO_DT_IEC pfsto_iso8601_to_dt;
	#define EXT_sto_iso8601_to_dt  extern PFSTO_ISO8601_TO_DT_IEC pfsto_iso8601_to_dt;
	#define GET_sto_iso8601_to_dt(fl)  s_pfCMGetAPI2( "sto_iso8601_to_dt", (RTS_VOID_FCTPTR *)&pfsto_iso8601_to_dt, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xB3451243), 0x03050528)
	#define CAL_sto_iso8601_to_dt  pfsto_iso8601_to_dt
	#define CHK_sto_iso8601_to_dt  (pfsto_iso8601_to_dt != NULL)
	#define EXP_sto_iso8601_to_dt   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_iso8601_to_dt", (RTS_UINTPTR)sto_iso8601_to_dt, 1, RTSITF_GET_SIGNATURE(0, 0xB3451243), 0x03050528) 
#endif


/**
 * <description>sto_iso8601_to_ltime</description>
 */
typedef struct tagsto_iso8601_to_ltime_struct
{
	RTS_IEC_ISO8601 *sValue;			/* VAR_IN_OUT */	
	CAA_ERROR STO_ISO8601_TO_LTIME;		/* VAR_OUTPUT */	
	RTS_IEC_LTIME ltValue;				/* VAR_OUTPUT */	
} sto_iso8601_to_ltime_struct;

void CDECL CDECL_EXT sto_iso8601_to_ltime(sto_iso8601_to_ltime_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_ISO8601_TO_LTIME_IEC) (sto_iso8601_to_ltime_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_ISO8601_TO_LTIME_NOTIMPLEMENTED)
	#define USE_sto_iso8601_to_ltime
	#define EXT_sto_iso8601_to_ltime
	#define GET_sto_iso8601_to_ltime(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_iso8601_to_ltime(p0) 
	#define CHK_sto_iso8601_to_ltime  FALSE
	#define EXP_sto_iso8601_to_ltime  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_iso8601_to_ltime
	#define EXT_sto_iso8601_to_ltime
	#define GET_sto_iso8601_to_ltime(fl)  CAL_CMGETAPI( "sto_iso8601_to_ltime" ) 
	#define CAL_sto_iso8601_to_ltime  sto_iso8601_to_ltime
	#define CHK_sto_iso8601_to_ltime  TRUE
	#define EXP_sto_iso8601_to_ltime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_iso8601_to_ltime", (RTS_UINTPTR)sto_iso8601_to_ltime, 1, RTSITF_GET_SIGNATURE(0, 0xF799E666), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_iso8601_to_ltime
	#define EXT_sto_iso8601_to_ltime
	#define GET_sto_iso8601_to_ltime(fl)  CAL_CMGETAPI( "sto_iso8601_to_ltime" ) 
	#define CAL_sto_iso8601_to_ltime  sto_iso8601_to_ltime
	#define CHK_sto_iso8601_to_ltime  TRUE
	#define EXP_sto_iso8601_to_ltime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_iso8601_to_ltime", (RTS_UINTPTR)sto_iso8601_to_ltime, 1, RTSITF_GET_SIGNATURE(0, 0xF799E666), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_iso8601_to_ltime
	#define EXT_CmpCAAStoragesto_iso8601_to_ltime
	#define GET_CmpCAAStoragesto_iso8601_to_ltime  ERR_OK
	#define CAL_CmpCAAStoragesto_iso8601_to_ltime  sto_iso8601_to_ltime
	#define CHK_CmpCAAStoragesto_iso8601_to_ltime  TRUE
	#define EXP_CmpCAAStoragesto_iso8601_to_ltime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_iso8601_to_ltime", (RTS_UINTPTR)sto_iso8601_to_ltime, 1, RTSITF_GET_SIGNATURE(0, 0xF799E666), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_iso8601_to_ltime
	#define EXT_sto_iso8601_to_ltime
	#define GET_sto_iso8601_to_ltime(fl)  CAL_CMGETAPI( "sto_iso8601_to_ltime" ) 
	#define CAL_sto_iso8601_to_ltime  sto_iso8601_to_ltime
	#define CHK_sto_iso8601_to_ltime  TRUE
	#define EXP_sto_iso8601_to_ltime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_iso8601_to_ltime", (RTS_UINTPTR)sto_iso8601_to_ltime, 1, RTSITF_GET_SIGNATURE(0, 0xF799E666), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_iso8601_to_ltime  PFSTO_ISO8601_TO_LTIME_IEC pfsto_iso8601_to_ltime;
	#define EXT_sto_iso8601_to_ltime  extern PFSTO_ISO8601_TO_LTIME_IEC pfsto_iso8601_to_ltime;
	#define GET_sto_iso8601_to_ltime(fl)  s_pfCMGetAPI2( "sto_iso8601_to_ltime", (RTS_VOID_FCTPTR *)&pfsto_iso8601_to_ltime, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xF799E666), 0x03050528)
	#define CAL_sto_iso8601_to_ltime  pfsto_iso8601_to_ltime
	#define CHK_sto_iso8601_to_ltime  (pfsto_iso8601_to_ltime != NULL)
	#define EXP_sto_iso8601_to_ltime   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_iso8601_to_ltime", (RTS_UINTPTR)sto_iso8601_to_ltime, 1, RTSITF_GET_SIGNATURE(0, 0xF799E666), 0x03050528) 
#endif


/**
 * <description>sto_iso8601_to_time</description>
 */
typedef struct tagsto_iso8601_to_time_struct
{
	RTS_IEC_ISO8601 *sValue;			/* VAR_IN_OUT */	
	CAA_ERROR STO_ISO8601_TO_TIME;		/* VAR_OUTPUT */	
	RTS_IEC_TIME tValue;				/* VAR_OUTPUT */	
} sto_iso8601_to_time_struct;

void CDECL CDECL_EXT sto_iso8601_to_time(sto_iso8601_to_time_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_ISO8601_TO_TIME_IEC) (sto_iso8601_to_time_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_ISO8601_TO_TIME_NOTIMPLEMENTED)
	#define USE_sto_iso8601_to_time
	#define EXT_sto_iso8601_to_time
	#define GET_sto_iso8601_to_time(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_iso8601_to_time(p0) 
	#define CHK_sto_iso8601_to_time  FALSE
	#define EXP_sto_iso8601_to_time  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_iso8601_to_time
	#define EXT_sto_iso8601_to_time
	#define GET_sto_iso8601_to_time(fl)  CAL_CMGETAPI( "sto_iso8601_to_time" ) 
	#define CAL_sto_iso8601_to_time  sto_iso8601_to_time
	#define CHK_sto_iso8601_to_time  TRUE
	#define EXP_sto_iso8601_to_time  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_iso8601_to_time", (RTS_UINTPTR)sto_iso8601_to_time, 1, RTSITF_GET_SIGNATURE(0, 0x4BAEA34F), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_iso8601_to_time
	#define EXT_sto_iso8601_to_time
	#define GET_sto_iso8601_to_time(fl)  CAL_CMGETAPI( "sto_iso8601_to_time" ) 
	#define CAL_sto_iso8601_to_time  sto_iso8601_to_time
	#define CHK_sto_iso8601_to_time  TRUE
	#define EXP_sto_iso8601_to_time  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_iso8601_to_time", (RTS_UINTPTR)sto_iso8601_to_time, 1, RTSITF_GET_SIGNATURE(0, 0x4BAEA34F), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_iso8601_to_time
	#define EXT_CmpCAAStoragesto_iso8601_to_time
	#define GET_CmpCAAStoragesto_iso8601_to_time  ERR_OK
	#define CAL_CmpCAAStoragesto_iso8601_to_time  sto_iso8601_to_time
	#define CHK_CmpCAAStoragesto_iso8601_to_time  TRUE
	#define EXP_CmpCAAStoragesto_iso8601_to_time  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_iso8601_to_time", (RTS_UINTPTR)sto_iso8601_to_time, 1, RTSITF_GET_SIGNATURE(0, 0x4BAEA34F), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_iso8601_to_time
	#define EXT_sto_iso8601_to_time
	#define GET_sto_iso8601_to_time(fl)  CAL_CMGETAPI( "sto_iso8601_to_time" ) 
	#define CAL_sto_iso8601_to_time  sto_iso8601_to_time
	#define CHK_sto_iso8601_to_time  TRUE
	#define EXP_sto_iso8601_to_time  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_iso8601_to_time", (RTS_UINTPTR)sto_iso8601_to_time, 1, RTSITF_GET_SIGNATURE(0, 0x4BAEA34F), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_iso8601_to_time  PFSTO_ISO8601_TO_TIME_IEC pfsto_iso8601_to_time;
	#define EXT_sto_iso8601_to_time  extern PFSTO_ISO8601_TO_TIME_IEC pfsto_iso8601_to_time;
	#define GET_sto_iso8601_to_time(fl)  s_pfCMGetAPI2( "sto_iso8601_to_time", (RTS_VOID_FCTPTR *)&pfsto_iso8601_to_time, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x4BAEA34F), 0x03050528)
	#define CAL_sto_iso8601_to_time  pfsto_iso8601_to_time
	#define CHK_sto_iso8601_to_time  (pfsto_iso8601_to_time != NULL)
	#define EXP_sto_iso8601_to_time   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_iso8601_to_time", (RTS_UINTPTR)sto_iso8601_to_time, 1, RTSITF_GET_SIGNATURE(0, 0x4BAEA34F), 0x03050528) 
#endif


/**
 * <description>sto_ltime_to_int64</description>
 */
typedef struct tagsto_ltime_to_int64_struct
{
	RTS_IEC_LTIME ltValue;				/* VAR_INPUT */	
	CAA_ERROR STO_LTIME_TO_INT64;		/* VAR_OUTPUT */	
	RTS_IEC_INT64 i64Value;				/* VAR_OUTPUT */	
} sto_ltime_to_int64_struct;

void CDECL CDECL_EXT sto_ltime_to_int64(sto_ltime_to_int64_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_LTIME_TO_INT64_IEC) (sto_ltime_to_int64_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_LTIME_TO_INT64_NOTIMPLEMENTED)
	#define USE_sto_ltime_to_int64
	#define EXT_sto_ltime_to_int64
	#define GET_sto_ltime_to_int64(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_ltime_to_int64(p0) 
	#define CHK_sto_ltime_to_int64  FALSE
	#define EXP_sto_ltime_to_int64  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_ltime_to_int64
	#define EXT_sto_ltime_to_int64
	#define GET_sto_ltime_to_int64(fl)  CAL_CMGETAPI( "sto_ltime_to_int64" ) 
	#define CAL_sto_ltime_to_int64  sto_ltime_to_int64
	#define CHK_sto_ltime_to_int64  TRUE
	#define EXP_sto_ltime_to_int64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_ltime_to_int64", (RTS_UINTPTR)sto_ltime_to_int64, 1, RTSITF_GET_SIGNATURE(0, 0x0C7C50F6), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_ltime_to_int64
	#define EXT_sto_ltime_to_int64
	#define GET_sto_ltime_to_int64(fl)  CAL_CMGETAPI( "sto_ltime_to_int64" ) 
	#define CAL_sto_ltime_to_int64  sto_ltime_to_int64
	#define CHK_sto_ltime_to_int64  TRUE
	#define EXP_sto_ltime_to_int64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_ltime_to_int64", (RTS_UINTPTR)sto_ltime_to_int64, 1, RTSITF_GET_SIGNATURE(0, 0x0C7C50F6), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_ltime_to_int64
	#define EXT_CmpCAAStoragesto_ltime_to_int64
	#define GET_CmpCAAStoragesto_ltime_to_int64  ERR_OK
	#define CAL_CmpCAAStoragesto_ltime_to_int64  sto_ltime_to_int64
	#define CHK_CmpCAAStoragesto_ltime_to_int64  TRUE
	#define EXP_CmpCAAStoragesto_ltime_to_int64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_ltime_to_int64", (RTS_UINTPTR)sto_ltime_to_int64, 1, RTSITF_GET_SIGNATURE(0, 0x0C7C50F6), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_ltime_to_int64
	#define EXT_sto_ltime_to_int64
	#define GET_sto_ltime_to_int64(fl)  CAL_CMGETAPI( "sto_ltime_to_int64" ) 
	#define CAL_sto_ltime_to_int64  sto_ltime_to_int64
	#define CHK_sto_ltime_to_int64  TRUE
	#define EXP_sto_ltime_to_int64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_ltime_to_int64", (RTS_UINTPTR)sto_ltime_to_int64, 1, RTSITF_GET_SIGNATURE(0, 0x0C7C50F6), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_ltime_to_int64  PFSTO_LTIME_TO_INT64_IEC pfsto_ltime_to_int64;
	#define EXT_sto_ltime_to_int64  extern PFSTO_LTIME_TO_INT64_IEC pfsto_ltime_to_int64;
	#define GET_sto_ltime_to_int64(fl)  s_pfCMGetAPI2( "sto_ltime_to_int64", (RTS_VOID_FCTPTR *)&pfsto_ltime_to_int64, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x0C7C50F6), 0x03050528)
	#define CAL_sto_ltime_to_int64  pfsto_ltime_to_int64
	#define CHK_sto_ltime_to_int64  (pfsto_ltime_to_int64 != NULL)
	#define EXP_sto_ltime_to_int64   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_ltime_to_int64", (RTS_UINTPTR)sto_ltime_to_int64, 1, RTSITF_GET_SIGNATURE(0, 0x0C7C50F6), 0x03050528) 
#endif


/**
 * <description>sto_ltime_to_iso8601</description>
 */
typedef struct tagsto_ltime_to_iso8601_struct
{
	RTS_IEC_LTIME ltValue;				/* VAR_INPUT */	
	RTS_IEC_ISO8601 *sValue;			/* VAR_IN_OUT */	
	CAA_ERROR STO_LTIME_TO_ISO8601;		/* VAR_OUTPUT */	
} sto_ltime_to_iso8601_struct;

void CDECL CDECL_EXT sto_ltime_to_iso8601(sto_ltime_to_iso8601_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_LTIME_TO_ISO8601_IEC) (sto_ltime_to_iso8601_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_LTIME_TO_ISO8601_NOTIMPLEMENTED)
	#define USE_sto_ltime_to_iso8601
	#define EXT_sto_ltime_to_iso8601
	#define GET_sto_ltime_to_iso8601(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_ltime_to_iso8601(p0) 
	#define CHK_sto_ltime_to_iso8601  FALSE
	#define EXP_sto_ltime_to_iso8601  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_ltime_to_iso8601
	#define EXT_sto_ltime_to_iso8601
	#define GET_sto_ltime_to_iso8601(fl)  CAL_CMGETAPI( "sto_ltime_to_iso8601" ) 
	#define CAL_sto_ltime_to_iso8601  sto_ltime_to_iso8601
	#define CHK_sto_ltime_to_iso8601  TRUE
	#define EXP_sto_ltime_to_iso8601  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_ltime_to_iso8601", (RTS_UINTPTR)sto_ltime_to_iso8601, 1, RTSITF_GET_SIGNATURE(0, 0xB4C1298B), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_ltime_to_iso8601
	#define EXT_sto_ltime_to_iso8601
	#define GET_sto_ltime_to_iso8601(fl)  CAL_CMGETAPI( "sto_ltime_to_iso8601" ) 
	#define CAL_sto_ltime_to_iso8601  sto_ltime_to_iso8601
	#define CHK_sto_ltime_to_iso8601  TRUE
	#define EXP_sto_ltime_to_iso8601  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_ltime_to_iso8601", (RTS_UINTPTR)sto_ltime_to_iso8601, 1, RTSITF_GET_SIGNATURE(0, 0xB4C1298B), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_ltime_to_iso8601
	#define EXT_CmpCAAStoragesto_ltime_to_iso8601
	#define GET_CmpCAAStoragesto_ltime_to_iso8601  ERR_OK
	#define CAL_CmpCAAStoragesto_ltime_to_iso8601  sto_ltime_to_iso8601
	#define CHK_CmpCAAStoragesto_ltime_to_iso8601  TRUE
	#define EXP_CmpCAAStoragesto_ltime_to_iso8601  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_ltime_to_iso8601", (RTS_UINTPTR)sto_ltime_to_iso8601, 1, RTSITF_GET_SIGNATURE(0, 0xB4C1298B), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_ltime_to_iso8601
	#define EXT_sto_ltime_to_iso8601
	#define GET_sto_ltime_to_iso8601(fl)  CAL_CMGETAPI( "sto_ltime_to_iso8601" ) 
	#define CAL_sto_ltime_to_iso8601  sto_ltime_to_iso8601
	#define CHK_sto_ltime_to_iso8601  TRUE
	#define EXP_sto_ltime_to_iso8601  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_ltime_to_iso8601", (RTS_UINTPTR)sto_ltime_to_iso8601, 1, RTSITF_GET_SIGNATURE(0, 0xB4C1298B), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_ltime_to_iso8601  PFSTO_LTIME_TO_ISO8601_IEC pfsto_ltime_to_iso8601;
	#define EXT_sto_ltime_to_iso8601  extern PFSTO_LTIME_TO_ISO8601_IEC pfsto_ltime_to_iso8601;
	#define GET_sto_ltime_to_iso8601(fl)  s_pfCMGetAPI2( "sto_ltime_to_iso8601", (RTS_VOID_FCTPTR *)&pfsto_ltime_to_iso8601, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xB4C1298B), 0x03050528)
	#define CAL_sto_ltime_to_iso8601  pfsto_ltime_to_iso8601
	#define CHK_sto_ltime_to_iso8601  (pfsto_ltime_to_iso8601 != NULL)
	#define EXP_sto_ltime_to_iso8601   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_ltime_to_iso8601", (RTS_UINTPTR)sto_ltime_to_iso8601, 1, RTSITF_GET_SIGNATURE(0, 0xB4C1298B), 0x03050528) 
#endif


/**
 * <description>sto_ltime_to_real8</description>
 */
typedef struct tagsto_ltime_to_real8_struct
{
	RTS_IEC_LTIME ltValue;				/* VAR_INPUT */	
	CAA_ERROR STO_LTIME_TO_REAL8;		/* VAR_OUTPUT */	
	RTS_IEC_LREAL lrValue;				/* VAR_OUTPUT */	
} sto_ltime_to_real8_struct;

void CDECL CDECL_EXT sto_ltime_to_real8(sto_ltime_to_real8_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_LTIME_TO_REAL8_IEC) (sto_ltime_to_real8_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_LTIME_TO_REAL8_NOTIMPLEMENTED)
	#define USE_sto_ltime_to_real8
	#define EXT_sto_ltime_to_real8
	#define GET_sto_ltime_to_real8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_ltime_to_real8(p0) 
	#define CHK_sto_ltime_to_real8  FALSE
	#define EXP_sto_ltime_to_real8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_ltime_to_real8
	#define EXT_sto_ltime_to_real8
	#define GET_sto_ltime_to_real8(fl)  CAL_CMGETAPI( "sto_ltime_to_real8" ) 
	#define CAL_sto_ltime_to_real8  sto_ltime_to_real8
	#define CHK_sto_ltime_to_real8  TRUE
	#define EXP_sto_ltime_to_real8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_ltime_to_real8", (RTS_UINTPTR)sto_ltime_to_real8, 1, RTSITF_GET_SIGNATURE(0, 0x86C0BF51), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_ltime_to_real8
	#define EXT_sto_ltime_to_real8
	#define GET_sto_ltime_to_real8(fl)  CAL_CMGETAPI( "sto_ltime_to_real8" ) 
	#define CAL_sto_ltime_to_real8  sto_ltime_to_real8
	#define CHK_sto_ltime_to_real8  TRUE
	#define EXP_sto_ltime_to_real8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_ltime_to_real8", (RTS_UINTPTR)sto_ltime_to_real8, 1, RTSITF_GET_SIGNATURE(0, 0x86C0BF51), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_ltime_to_real8
	#define EXT_CmpCAAStoragesto_ltime_to_real8
	#define GET_CmpCAAStoragesto_ltime_to_real8  ERR_OK
	#define CAL_CmpCAAStoragesto_ltime_to_real8  sto_ltime_to_real8
	#define CHK_CmpCAAStoragesto_ltime_to_real8  TRUE
	#define EXP_CmpCAAStoragesto_ltime_to_real8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_ltime_to_real8", (RTS_UINTPTR)sto_ltime_to_real8, 1, RTSITF_GET_SIGNATURE(0, 0x86C0BF51), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_ltime_to_real8
	#define EXT_sto_ltime_to_real8
	#define GET_sto_ltime_to_real8(fl)  CAL_CMGETAPI( "sto_ltime_to_real8" ) 
	#define CAL_sto_ltime_to_real8  sto_ltime_to_real8
	#define CHK_sto_ltime_to_real8  TRUE
	#define EXP_sto_ltime_to_real8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_ltime_to_real8", (RTS_UINTPTR)sto_ltime_to_real8, 1, RTSITF_GET_SIGNATURE(0, 0x86C0BF51), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_ltime_to_real8  PFSTO_LTIME_TO_REAL8_IEC pfsto_ltime_to_real8;
	#define EXT_sto_ltime_to_real8  extern PFSTO_LTIME_TO_REAL8_IEC pfsto_ltime_to_real8;
	#define GET_sto_ltime_to_real8(fl)  s_pfCMGetAPI2( "sto_ltime_to_real8", (RTS_VOID_FCTPTR *)&pfsto_ltime_to_real8, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x86C0BF51), 0x03050528)
	#define CAL_sto_ltime_to_real8  pfsto_ltime_to_real8
	#define CHK_sto_ltime_to_real8  (pfsto_ltime_to_real8 != NULL)
	#define EXP_sto_ltime_to_real8   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_ltime_to_real8", (RTS_UINTPTR)sto_ltime_to_real8, 1, RTSITF_GET_SIGNATURE(0, 0x86C0BF51), 0x03050528) 
#endif


/**
 * <description>sto_real8_to_dt</description>
 */
typedef struct tagsto_real8_to_dt_struct
{
	RTS_IEC_REAL8 r8Value;				/* VAR_INPUT */	
	CAA_ERROR STO_REAL8_TO_DT;			/* VAR_OUTPUT */	
	RTS_IEC_DATE_AND_TIME dtValue;		/* VAR_OUTPUT */	
} sto_real8_to_dt_struct;

void CDECL CDECL_EXT sto_real8_to_dt(sto_real8_to_dt_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_REAL8_TO_DT_IEC) (sto_real8_to_dt_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_REAL8_TO_DT_NOTIMPLEMENTED)
	#define USE_sto_real8_to_dt
	#define EXT_sto_real8_to_dt
	#define GET_sto_real8_to_dt(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_real8_to_dt(p0) 
	#define CHK_sto_real8_to_dt  FALSE
	#define EXP_sto_real8_to_dt  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_real8_to_dt
	#define EXT_sto_real8_to_dt
	#define GET_sto_real8_to_dt(fl)  CAL_CMGETAPI( "sto_real8_to_dt" ) 
	#define CAL_sto_real8_to_dt  sto_real8_to_dt
	#define CHK_sto_real8_to_dt  TRUE
	#define EXP_sto_real8_to_dt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_real8_to_dt", (RTS_UINTPTR)sto_real8_to_dt, 1, RTSITF_GET_SIGNATURE(0, 0x185C3263), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_real8_to_dt
	#define EXT_sto_real8_to_dt
	#define GET_sto_real8_to_dt(fl)  CAL_CMGETAPI( "sto_real8_to_dt" ) 
	#define CAL_sto_real8_to_dt  sto_real8_to_dt
	#define CHK_sto_real8_to_dt  TRUE
	#define EXP_sto_real8_to_dt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_real8_to_dt", (RTS_UINTPTR)sto_real8_to_dt, 1, RTSITF_GET_SIGNATURE(0, 0x185C3263), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_real8_to_dt
	#define EXT_CmpCAAStoragesto_real8_to_dt
	#define GET_CmpCAAStoragesto_real8_to_dt  ERR_OK
	#define CAL_CmpCAAStoragesto_real8_to_dt  sto_real8_to_dt
	#define CHK_CmpCAAStoragesto_real8_to_dt  TRUE
	#define EXP_CmpCAAStoragesto_real8_to_dt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_real8_to_dt", (RTS_UINTPTR)sto_real8_to_dt, 1, RTSITF_GET_SIGNATURE(0, 0x185C3263), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_real8_to_dt
	#define EXT_sto_real8_to_dt
	#define GET_sto_real8_to_dt(fl)  CAL_CMGETAPI( "sto_real8_to_dt" ) 
	#define CAL_sto_real8_to_dt  sto_real8_to_dt
	#define CHK_sto_real8_to_dt  TRUE
	#define EXP_sto_real8_to_dt  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_real8_to_dt", (RTS_UINTPTR)sto_real8_to_dt, 1, RTSITF_GET_SIGNATURE(0, 0x185C3263), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_real8_to_dt  PFSTO_REAL8_TO_DT_IEC pfsto_real8_to_dt;
	#define EXT_sto_real8_to_dt  extern PFSTO_REAL8_TO_DT_IEC pfsto_real8_to_dt;
	#define GET_sto_real8_to_dt(fl)  s_pfCMGetAPI2( "sto_real8_to_dt", (RTS_VOID_FCTPTR *)&pfsto_real8_to_dt, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x185C3263), 0x03050528)
	#define CAL_sto_real8_to_dt  pfsto_real8_to_dt
	#define CHK_sto_real8_to_dt  (pfsto_real8_to_dt != NULL)
	#define EXP_sto_real8_to_dt   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_real8_to_dt", (RTS_UINTPTR)sto_real8_to_dt, 1, RTSITF_GET_SIGNATURE(0, 0x185C3263), 0x03050528) 
#endif


/**
 * <description>sto_real8_to_ltime</description>
 */
typedef struct tagsto_real8_to_ltime_struct
{
	RTS_IEC_REAL8 r8Value;				/* VAR_INPUT */	
	CAA_ERROR STO_REAL8_TO_LTIME;		/* VAR_OUTPUT */	
	RTS_IEC_LTIME ltValue;				/* VAR_OUTPUT */	
} sto_real8_to_ltime_struct;

void CDECL CDECL_EXT sto_real8_to_ltime(sto_real8_to_ltime_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_REAL8_TO_LTIME_IEC) (sto_real8_to_ltime_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_REAL8_TO_LTIME_NOTIMPLEMENTED)
	#define USE_sto_real8_to_ltime
	#define EXT_sto_real8_to_ltime
	#define GET_sto_real8_to_ltime(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_real8_to_ltime(p0) 
	#define CHK_sto_real8_to_ltime  FALSE
	#define EXP_sto_real8_to_ltime  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_real8_to_ltime
	#define EXT_sto_real8_to_ltime
	#define GET_sto_real8_to_ltime(fl)  CAL_CMGETAPI( "sto_real8_to_ltime" ) 
	#define CAL_sto_real8_to_ltime  sto_real8_to_ltime
	#define CHK_sto_real8_to_ltime  TRUE
	#define EXP_sto_real8_to_ltime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_real8_to_ltime", (RTS_UINTPTR)sto_real8_to_ltime, 1, RTSITF_GET_SIGNATURE(0, 0xF1247EEF), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_real8_to_ltime
	#define EXT_sto_real8_to_ltime
	#define GET_sto_real8_to_ltime(fl)  CAL_CMGETAPI( "sto_real8_to_ltime" ) 
	#define CAL_sto_real8_to_ltime  sto_real8_to_ltime
	#define CHK_sto_real8_to_ltime  TRUE
	#define EXP_sto_real8_to_ltime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_real8_to_ltime", (RTS_UINTPTR)sto_real8_to_ltime, 1, RTSITF_GET_SIGNATURE(0, 0xF1247EEF), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_real8_to_ltime
	#define EXT_CmpCAAStoragesto_real8_to_ltime
	#define GET_CmpCAAStoragesto_real8_to_ltime  ERR_OK
	#define CAL_CmpCAAStoragesto_real8_to_ltime  sto_real8_to_ltime
	#define CHK_CmpCAAStoragesto_real8_to_ltime  TRUE
	#define EXP_CmpCAAStoragesto_real8_to_ltime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_real8_to_ltime", (RTS_UINTPTR)sto_real8_to_ltime, 1, RTSITF_GET_SIGNATURE(0, 0xF1247EEF), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_real8_to_ltime
	#define EXT_sto_real8_to_ltime
	#define GET_sto_real8_to_ltime(fl)  CAL_CMGETAPI( "sto_real8_to_ltime" ) 
	#define CAL_sto_real8_to_ltime  sto_real8_to_ltime
	#define CHK_sto_real8_to_ltime  TRUE
	#define EXP_sto_real8_to_ltime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_real8_to_ltime", (RTS_UINTPTR)sto_real8_to_ltime, 1, RTSITF_GET_SIGNATURE(0, 0xF1247EEF), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_real8_to_ltime  PFSTO_REAL8_TO_LTIME_IEC pfsto_real8_to_ltime;
	#define EXT_sto_real8_to_ltime  extern PFSTO_REAL8_TO_LTIME_IEC pfsto_real8_to_ltime;
	#define GET_sto_real8_to_ltime(fl)  s_pfCMGetAPI2( "sto_real8_to_ltime", (RTS_VOID_FCTPTR *)&pfsto_real8_to_ltime, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xF1247EEF), 0x03050528)
	#define CAL_sto_real8_to_ltime  pfsto_real8_to_ltime
	#define CHK_sto_real8_to_ltime  (pfsto_real8_to_ltime != NULL)
	#define EXP_sto_real8_to_ltime   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_real8_to_ltime", (RTS_UINTPTR)sto_real8_to_ltime, 1, RTSITF_GET_SIGNATURE(0, 0xF1247EEF), 0x03050528) 
#endif


/**
 * <description>sto_real8_to_time</description>
 */
typedef struct tagsto_real8_to_time_struct
{
	RTS_IEC_REAL8 r8Value;				/* VAR_INPUT */	
	CAA_ERROR STO_REAL8_TO_TIME;		/* VAR_OUTPUT */	
	RTS_IEC_TIME tValue;				/* VAR_OUTPUT */	
} sto_real8_to_time_struct;

void CDECL CDECL_EXT sto_real8_to_time(sto_real8_to_time_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_REAL8_TO_TIME_IEC) (sto_real8_to_time_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_REAL8_TO_TIME_NOTIMPLEMENTED)
	#define USE_sto_real8_to_time
	#define EXT_sto_real8_to_time
	#define GET_sto_real8_to_time(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_real8_to_time(p0) 
	#define CHK_sto_real8_to_time  FALSE
	#define EXP_sto_real8_to_time  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_real8_to_time
	#define EXT_sto_real8_to_time
	#define GET_sto_real8_to_time(fl)  CAL_CMGETAPI( "sto_real8_to_time" ) 
	#define CAL_sto_real8_to_time  sto_real8_to_time
	#define CHK_sto_real8_to_time  TRUE
	#define EXP_sto_real8_to_time  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_real8_to_time", (RTS_UINTPTR)sto_real8_to_time, 1, RTSITF_GET_SIGNATURE(0, 0x2C257042), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_real8_to_time
	#define EXT_sto_real8_to_time
	#define GET_sto_real8_to_time(fl)  CAL_CMGETAPI( "sto_real8_to_time" ) 
	#define CAL_sto_real8_to_time  sto_real8_to_time
	#define CHK_sto_real8_to_time  TRUE
	#define EXP_sto_real8_to_time  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_real8_to_time", (RTS_UINTPTR)sto_real8_to_time, 1, RTSITF_GET_SIGNATURE(0, 0x2C257042), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_real8_to_time
	#define EXT_CmpCAAStoragesto_real8_to_time
	#define GET_CmpCAAStoragesto_real8_to_time  ERR_OK
	#define CAL_CmpCAAStoragesto_real8_to_time  sto_real8_to_time
	#define CHK_CmpCAAStoragesto_real8_to_time  TRUE
	#define EXP_CmpCAAStoragesto_real8_to_time  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_real8_to_time", (RTS_UINTPTR)sto_real8_to_time, 1, RTSITF_GET_SIGNATURE(0, 0x2C257042), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_real8_to_time
	#define EXT_sto_real8_to_time
	#define GET_sto_real8_to_time(fl)  CAL_CMGETAPI( "sto_real8_to_time" ) 
	#define CAL_sto_real8_to_time  sto_real8_to_time
	#define CHK_sto_real8_to_time  TRUE
	#define EXP_sto_real8_to_time  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_real8_to_time", (RTS_UINTPTR)sto_real8_to_time, 1, RTSITF_GET_SIGNATURE(0, 0x2C257042), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_real8_to_time  PFSTO_REAL8_TO_TIME_IEC pfsto_real8_to_time;
	#define EXT_sto_real8_to_time  extern PFSTO_REAL8_TO_TIME_IEC pfsto_real8_to_time;
	#define GET_sto_real8_to_time(fl)  s_pfCMGetAPI2( "sto_real8_to_time", (RTS_VOID_FCTPTR *)&pfsto_real8_to_time, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x2C257042), 0x03050528)
	#define CAL_sto_real8_to_time  pfsto_real8_to_time
	#define CHK_sto_real8_to_time  (pfsto_real8_to_time != NULL)
	#define EXP_sto_real8_to_time   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_real8_to_time", (RTS_UINTPTR)sto_real8_to_time, 1, RTSITF_GET_SIGNATURE(0, 0x2C257042), 0x03050528) 
#endif


/**
 * Deletes a database. The return value contains a CmpError.ERROR value indicating
 * the success of the operation.
 */
typedef struct tagsto_deletefile_struct
{
	CAA_FILENAME *sPath;				/* VAR_IN_OUT */	/* The filename of the database to delete */
	CAA_ERROR STO_DeleteFile;			/* VAR_OUTPUT */	
} sto_deletefile_struct;

void CDECL CDECL_EXT sto_deletefile(sto_deletefile_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_DELETEFILE_IEC) (sto_deletefile_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_DELETEFILE_NOTIMPLEMENTED)
	#define USE_sto_deletefile
	#define EXT_sto_deletefile
	#define GET_sto_deletefile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_deletefile(p0) 
	#define CHK_sto_deletefile  FALSE
	#define EXP_sto_deletefile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_deletefile
	#define EXT_sto_deletefile
	#define GET_sto_deletefile(fl)  CAL_CMGETAPI( "sto_deletefile" ) 
	#define CAL_sto_deletefile  sto_deletefile
	#define CHK_sto_deletefile  TRUE
	#define EXP_sto_deletefile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_deletefile", (RTS_UINTPTR)sto_deletefile, 1, RTSITF_GET_SIGNATURE(0, 0x525CF376), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_deletefile
	#define EXT_sto_deletefile
	#define GET_sto_deletefile(fl)  CAL_CMGETAPI( "sto_deletefile" ) 
	#define CAL_sto_deletefile  sto_deletefile
	#define CHK_sto_deletefile  TRUE
	#define EXP_sto_deletefile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_deletefile", (RTS_UINTPTR)sto_deletefile, 1, RTSITF_GET_SIGNATURE(0, 0x525CF376), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_deletefile
	#define EXT_CmpCAAStoragesto_deletefile
	#define GET_CmpCAAStoragesto_deletefile  ERR_OK
	#define CAL_CmpCAAStoragesto_deletefile  sto_deletefile
	#define CHK_CmpCAAStoragesto_deletefile  TRUE
	#define EXP_CmpCAAStoragesto_deletefile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_deletefile", (RTS_UINTPTR)sto_deletefile, 1, RTSITF_GET_SIGNATURE(0, 0x525CF376), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_deletefile
	#define EXT_sto_deletefile
	#define GET_sto_deletefile(fl)  CAL_CMGETAPI( "sto_deletefile" ) 
	#define CAL_sto_deletefile  sto_deletefile
	#define CHK_sto_deletefile  TRUE
	#define EXP_sto_deletefile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_deletefile", (RTS_UINTPTR)sto_deletefile, 1, RTSITF_GET_SIGNATURE(0, 0x525CF376), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_deletefile  PFSTO_DELETEFILE_IEC pfsto_deletefile;
	#define EXT_sto_deletefile  extern PFSTO_DELETEFILE_IEC pfsto_deletefile;
	#define GET_sto_deletefile(fl)  s_pfCMGetAPI2( "sto_deletefile", (RTS_VOID_FCTPTR *)&pfsto_deletefile, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x525CF376), 0x03050528)
	#define CAL_sto_deletefile  pfsto_deletefile
	#define CHK_sto_deletefile  (pfsto_deletefile != NULL)
	#define EXP_sto_deletefile   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_deletefile", (RTS_UINTPTR)sto_deletefile, 1, RTSITF_GET_SIGNATURE(0, 0x525CF376), 0x03050528) 
#endif


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

void CDECL CDECL_EXT sto_textcopytostring(sto_textcopytostring_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_TEXTCOPYTOSTRING_IEC) (sto_textcopytostring_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_TEXTCOPYTOSTRING_NOTIMPLEMENTED)
	#define USE_sto_textcopytostring
	#define EXT_sto_textcopytostring
	#define GET_sto_textcopytostring(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_textcopytostring(p0) 
	#define CHK_sto_textcopytostring  FALSE
	#define EXP_sto_textcopytostring  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_textcopytostring
	#define EXT_sto_textcopytostring
	#define GET_sto_textcopytostring(fl)  CAL_CMGETAPI( "sto_textcopytostring" ) 
	#define CAL_sto_textcopytostring  sto_textcopytostring
	#define CHK_sto_textcopytostring  TRUE
	#define EXP_sto_textcopytostring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_textcopytostring", (RTS_UINTPTR)sto_textcopytostring, 1, RTSITF_GET_SIGNATURE(0, 0x77472764), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_textcopytostring
	#define EXT_sto_textcopytostring
	#define GET_sto_textcopytostring(fl)  CAL_CMGETAPI( "sto_textcopytostring" ) 
	#define CAL_sto_textcopytostring  sto_textcopytostring
	#define CHK_sto_textcopytostring  TRUE
	#define EXP_sto_textcopytostring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_textcopytostring", (RTS_UINTPTR)sto_textcopytostring, 1, RTSITF_GET_SIGNATURE(0, 0x77472764), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_textcopytostring
	#define EXT_CmpCAAStoragesto_textcopytostring
	#define GET_CmpCAAStoragesto_textcopytostring  ERR_OK
	#define CAL_CmpCAAStoragesto_textcopytostring  sto_textcopytostring
	#define CHK_CmpCAAStoragesto_textcopytostring  TRUE
	#define EXP_CmpCAAStoragesto_textcopytostring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_textcopytostring", (RTS_UINTPTR)sto_textcopytostring, 1, RTSITF_GET_SIGNATURE(0, 0x77472764), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_textcopytostring
	#define EXT_sto_textcopytostring
	#define GET_sto_textcopytostring(fl)  CAL_CMGETAPI( "sto_textcopytostring" ) 
	#define CAL_sto_textcopytostring  sto_textcopytostring
	#define CHK_sto_textcopytostring  TRUE
	#define EXP_sto_textcopytostring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_textcopytostring", (RTS_UINTPTR)sto_textcopytostring, 1, RTSITF_GET_SIGNATURE(0, 0x77472764), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_textcopytostring  PFSTO_TEXTCOPYTOSTRING_IEC pfsto_textcopytostring;
	#define EXT_sto_textcopytostring  extern PFSTO_TEXTCOPYTOSTRING_IEC pfsto_textcopytostring;
	#define GET_sto_textcopytostring(fl)  s_pfCMGetAPI2( "sto_textcopytostring", (RTS_VOID_FCTPTR *)&pfsto_textcopytostring, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x77472764), 0x03050528)
	#define CAL_sto_textcopytostring  pfsto_textcopytostring
	#define CHK_sto_textcopytostring  (pfsto_textcopytostring != NULL)
	#define EXP_sto_textcopytostring   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_textcopytostring", (RTS_UINTPTR)sto_textcopytostring, 1, RTSITF_GET_SIGNATURE(0, 0x77472764), 0x03050528) 
#endif


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

void CDECL CDECL_EXT sto_textcopytowstring(sto_textcopytowstring_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_TEXTCOPYTOWSTRING_IEC) (sto_textcopytowstring_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_TEXTCOPYTOWSTRING_NOTIMPLEMENTED)
	#define USE_sto_textcopytowstring
	#define EXT_sto_textcopytowstring
	#define GET_sto_textcopytowstring(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_textcopytowstring(p0) 
	#define CHK_sto_textcopytowstring  FALSE
	#define EXP_sto_textcopytowstring  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_textcopytowstring
	#define EXT_sto_textcopytowstring
	#define GET_sto_textcopytowstring(fl)  CAL_CMGETAPI( "sto_textcopytowstring" ) 
	#define CAL_sto_textcopytowstring  sto_textcopytowstring
	#define CHK_sto_textcopytowstring  TRUE
	#define EXP_sto_textcopytowstring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_textcopytowstring", (RTS_UINTPTR)sto_textcopytowstring, 1, RTSITF_GET_SIGNATURE(0, 0xA8659036), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_textcopytowstring
	#define EXT_sto_textcopytowstring
	#define GET_sto_textcopytowstring(fl)  CAL_CMGETAPI( "sto_textcopytowstring" ) 
	#define CAL_sto_textcopytowstring  sto_textcopytowstring
	#define CHK_sto_textcopytowstring  TRUE
	#define EXP_sto_textcopytowstring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_textcopytowstring", (RTS_UINTPTR)sto_textcopytowstring, 1, RTSITF_GET_SIGNATURE(0, 0xA8659036), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_textcopytowstring
	#define EXT_CmpCAAStoragesto_textcopytowstring
	#define GET_CmpCAAStoragesto_textcopytowstring  ERR_OK
	#define CAL_CmpCAAStoragesto_textcopytowstring  sto_textcopytowstring
	#define CHK_CmpCAAStoragesto_textcopytowstring  TRUE
	#define EXP_CmpCAAStoragesto_textcopytowstring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_textcopytowstring", (RTS_UINTPTR)sto_textcopytowstring, 1, RTSITF_GET_SIGNATURE(0, 0xA8659036), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_textcopytowstring
	#define EXT_sto_textcopytowstring
	#define GET_sto_textcopytowstring(fl)  CAL_CMGETAPI( "sto_textcopytowstring" ) 
	#define CAL_sto_textcopytowstring  sto_textcopytowstring
	#define CHK_sto_textcopytowstring  TRUE
	#define EXP_sto_textcopytowstring  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_textcopytowstring", (RTS_UINTPTR)sto_textcopytowstring, 1, RTSITF_GET_SIGNATURE(0, 0xA8659036), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_textcopytowstring  PFSTO_TEXTCOPYTOWSTRING_IEC pfsto_textcopytowstring;
	#define EXT_sto_textcopytowstring  extern PFSTO_TEXTCOPYTOWSTRING_IEC pfsto_textcopytowstring;
	#define GET_sto_textcopytowstring(fl)  s_pfCMGetAPI2( "sto_textcopytowstring", (RTS_VOID_FCTPTR *)&pfsto_textcopytowstring, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA8659036), 0x03050528)
	#define CAL_sto_textcopytowstring  pfsto_textcopytowstring
	#define CHK_sto_textcopytowstring  (pfsto_textcopytowstring != NULL)
	#define EXP_sto_textcopytowstring   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_textcopytowstring", (RTS_UINTPTR)sto_textcopytowstring, 1, RTSITF_GET_SIGNATURE(0, 0xA8659036), 0x03050528) 
#endif


/**
 * See documentation of type TEXT how to use the TEXT type.
 */
typedef struct tagsto_textfree_struct
{
	STO_TEXT *txtValue;					/* VAR_IN_OUT */	
	CAA_ERROR STO_TextFree;				/* VAR_OUTPUT */	
} sto_textfree_struct;

void CDECL CDECL_EXT sto_textfree(sto_textfree_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_TEXTFREE_IEC) (sto_textfree_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_TEXTFREE_NOTIMPLEMENTED)
	#define USE_sto_textfree
	#define EXT_sto_textfree
	#define GET_sto_textfree(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_textfree(p0) 
	#define CHK_sto_textfree  FALSE
	#define EXP_sto_textfree  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_textfree
	#define EXT_sto_textfree
	#define GET_sto_textfree(fl)  CAL_CMGETAPI( "sto_textfree" ) 
	#define CAL_sto_textfree  sto_textfree
	#define CHK_sto_textfree  TRUE
	#define EXP_sto_textfree  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_textfree", (RTS_UINTPTR)sto_textfree, 1, RTSITF_GET_SIGNATURE(0, 0x76615FAC), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_textfree
	#define EXT_sto_textfree
	#define GET_sto_textfree(fl)  CAL_CMGETAPI( "sto_textfree" ) 
	#define CAL_sto_textfree  sto_textfree
	#define CHK_sto_textfree  TRUE
	#define EXP_sto_textfree  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_textfree", (RTS_UINTPTR)sto_textfree, 1, RTSITF_GET_SIGNATURE(0, 0x76615FAC), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_textfree
	#define EXT_CmpCAAStoragesto_textfree
	#define GET_CmpCAAStoragesto_textfree  ERR_OK
	#define CAL_CmpCAAStoragesto_textfree  sto_textfree
	#define CHK_CmpCAAStoragesto_textfree  TRUE
	#define EXP_CmpCAAStoragesto_textfree  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_textfree", (RTS_UINTPTR)sto_textfree, 1, RTSITF_GET_SIGNATURE(0, 0x76615FAC), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_textfree
	#define EXT_sto_textfree
	#define GET_sto_textfree(fl)  CAL_CMGETAPI( "sto_textfree" ) 
	#define CAL_sto_textfree  sto_textfree
	#define CHK_sto_textfree  TRUE
	#define EXP_sto_textfree  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_textfree", (RTS_UINTPTR)sto_textfree, 1, RTSITF_GET_SIGNATURE(0, 0x76615FAC), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_textfree  PFSTO_TEXTFREE_IEC pfsto_textfree;
	#define EXT_sto_textfree  extern PFSTO_TEXTFREE_IEC pfsto_textfree;
	#define GET_sto_textfree(fl)  s_pfCMGetAPI2( "sto_textfree", (RTS_VOID_FCTPTR *)&pfsto_textfree, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x76615FAC), 0x03050528)
	#define CAL_sto_textfree  pfsto_textfree
	#define CHK_sto_textfree  (pfsto_textfree != NULL)
	#define EXP_sto_textfree   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_textfree", (RTS_UINTPTR)sto_textfree, 1, RTSITF_GET_SIGNATURE(0, 0x76615FAC), 0x03050528) 
#endif


/**
 * <description>sto_time_to_int64</description>
 */
typedef struct tagsto_time_to_int64_struct
{
	RTS_IEC_TIME tValue;				/* VAR_INPUT */	
	CAA_ERROR STO_TIME_TO_INT64;		/* VAR_OUTPUT */	
	RTS_IEC_INT64 i64Value;				/* VAR_OUTPUT */	
} sto_time_to_int64_struct;

void CDECL CDECL_EXT sto_time_to_int64(sto_time_to_int64_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_TIME_TO_INT64_IEC) (sto_time_to_int64_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_TIME_TO_INT64_NOTIMPLEMENTED)
	#define USE_sto_time_to_int64
	#define EXT_sto_time_to_int64
	#define GET_sto_time_to_int64(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_time_to_int64(p0) 
	#define CHK_sto_time_to_int64  FALSE
	#define EXP_sto_time_to_int64  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_time_to_int64
	#define EXT_sto_time_to_int64
	#define GET_sto_time_to_int64(fl)  CAL_CMGETAPI( "sto_time_to_int64" ) 
	#define CAL_sto_time_to_int64  sto_time_to_int64
	#define CHK_sto_time_to_int64  TRUE
	#define EXP_sto_time_to_int64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_time_to_int64", (RTS_UINTPTR)sto_time_to_int64, 1, RTSITF_GET_SIGNATURE(0, 0xF7F2035E), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_time_to_int64
	#define EXT_sto_time_to_int64
	#define GET_sto_time_to_int64(fl)  CAL_CMGETAPI( "sto_time_to_int64" ) 
	#define CAL_sto_time_to_int64  sto_time_to_int64
	#define CHK_sto_time_to_int64  TRUE
	#define EXP_sto_time_to_int64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_time_to_int64", (RTS_UINTPTR)sto_time_to_int64, 1, RTSITF_GET_SIGNATURE(0, 0xF7F2035E), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_time_to_int64
	#define EXT_CmpCAAStoragesto_time_to_int64
	#define GET_CmpCAAStoragesto_time_to_int64  ERR_OK
	#define CAL_CmpCAAStoragesto_time_to_int64  sto_time_to_int64
	#define CHK_CmpCAAStoragesto_time_to_int64  TRUE
	#define EXP_CmpCAAStoragesto_time_to_int64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_time_to_int64", (RTS_UINTPTR)sto_time_to_int64, 1, RTSITF_GET_SIGNATURE(0, 0xF7F2035E), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_time_to_int64
	#define EXT_sto_time_to_int64
	#define GET_sto_time_to_int64(fl)  CAL_CMGETAPI( "sto_time_to_int64" ) 
	#define CAL_sto_time_to_int64  sto_time_to_int64
	#define CHK_sto_time_to_int64  TRUE
	#define EXP_sto_time_to_int64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_time_to_int64", (RTS_UINTPTR)sto_time_to_int64, 1, RTSITF_GET_SIGNATURE(0, 0xF7F2035E), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_time_to_int64  PFSTO_TIME_TO_INT64_IEC pfsto_time_to_int64;
	#define EXT_sto_time_to_int64  extern PFSTO_TIME_TO_INT64_IEC pfsto_time_to_int64;
	#define GET_sto_time_to_int64(fl)  s_pfCMGetAPI2( "sto_time_to_int64", (RTS_VOID_FCTPTR *)&pfsto_time_to_int64, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xF7F2035E), 0x03050528)
	#define CAL_sto_time_to_int64  pfsto_time_to_int64
	#define CHK_sto_time_to_int64  (pfsto_time_to_int64 != NULL)
	#define EXP_sto_time_to_int64   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_time_to_int64", (RTS_UINTPTR)sto_time_to_int64, 1, RTSITF_GET_SIGNATURE(0, 0xF7F2035E), 0x03050528) 
#endif


/**
 * <description>sto_time_to_iso8601</description>
 */
typedef struct tagsto_time_to_iso8601_struct
{
	RTS_IEC_TIME tValue;				/* VAR_INPUT */	
	RTS_IEC_ISO8601 *sValue;			/* VAR_IN_OUT */	
	CAA_ERROR STO_TIME_TO_ISO8601;		/* VAR_OUTPUT */	
} sto_time_to_iso8601_struct;

void CDECL CDECL_EXT sto_time_to_iso8601(sto_time_to_iso8601_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_TIME_TO_ISO8601_IEC) (sto_time_to_iso8601_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_TIME_TO_ISO8601_NOTIMPLEMENTED)
	#define USE_sto_time_to_iso8601
	#define EXT_sto_time_to_iso8601
	#define GET_sto_time_to_iso8601(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_time_to_iso8601(p0) 
	#define CHK_sto_time_to_iso8601  FALSE
	#define EXP_sto_time_to_iso8601  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_time_to_iso8601
	#define EXT_sto_time_to_iso8601
	#define GET_sto_time_to_iso8601(fl)  CAL_CMGETAPI( "sto_time_to_iso8601" ) 
	#define CAL_sto_time_to_iso8601  sto_time_to_iso8601
	#define CHK_sto_time_to_iso8601  TRUE
	#define EXP_sto_time_to_iso8601  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_time_to_iso8601", (RTS_UINTPTR)sto_time_to_iso8601, 1, RTSITF_GET_SIGNATURE(0, 0x1B53667A), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_time_to_iso8601
	#define EXT_sto_time_to_iso8601
	#define GET_sto_time_to_iso8601(fl)  CAL_CMGETAPI( "sto_time_to_iso8601" ) 
	#define CAL_sto_time_to_iso8601  sto_time_to_iso8601
	#define CHK_sto_time_to_iso8601  TRUE
	#define EXP_sto_time_to_iso8601  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_time_to_iso8601", (RTS_UINTPTR)sto_time_to_iso8601, 1, RTSITF_GET_SIGNATURE(0, 0x1B53667A), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_time_to_iso8601
	#define EXT_CmpCAAStoragesto_time_to_iso8601
	#define GET_CmpCAAStoragesto_time_to_iso8601  ERR_OK
	#define CAL_CmpCAAStoragesto_time_to_iso8601  sto_time_to_iso8601
	#define CHK_CmpCAAStoragesto_time_to_iso8601  TRUE
	#define EXP_CmpCAAStoragesto_time_to_iso8601  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_time_to_iso8601", (RTS_UINTPTR)sto_time_to_iso8601, 1, RTSITF_GET_SIGNATURE(0, 0x1B53667A), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_time_to_iso8601
	#define EXT_sto_time_to_iso8601
	#define GET_sto_time_to_iso8601(fl)  CAL_CMGETAPI( "sto_time_to_iso8601" ) 
	#define CAL_sto_time_to_iso8601  sto_time_to_iso8601
	#define CHK_sto_time_to_iso8601  TRUE
	#define EXP_sto_time_to_iso8601  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_time_to_iso8601", (RTS_UINTPTR)sto_time_to_iso8601, 1, RTSITF_GET_SIGNATURE(0, 0x1B53667A), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_time_to_iso8601  PFSTO_TIME_TO_ISO8601_IEC pfsto_time_to_iso8601;
	#define EXT_sto_time_to_iso8601  extern PFSTO_TIME_TO_ISO8601_IEC pfsto_time_to_iso8601;
	#define GET_sto_time_to_iso8601(fl)  s_pfCMGetAPI2( "sto_time_to_iso8601", (RTS_VOID_FCTPTR *)&pfsto_time_to_iso8601, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x1B53667A), 0x03050528)
	#define CAL_sto_time_to_iso8601  pfsto_time_to_iso8601
	#define CHK_sto_time_to_iso8601  (pfsto_time_to_iso8601 != NULL)
	#define EXP_sto_time_to_iso8601   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_time_to_iso8601", (RTS_UINTPTR)sto_time_to_iso8601, 1, RTSITF_GET_SIGNATURE(0, 0x1B53667A), 0x03050528) 
#endif


/**
 * <description>sto_time_to_real8</description>
 */
typedef struct tagsto_time_to_real8_struct
{
	RTS_IEC_TIME tValue;				/* VAR_INPUT */	
	CAA_ERROR STO_TIME_TO_REAL8;		/* VAR_OUTPUT */	
	RTS_IEC_REAL8 r8Value;				/* VAR_OUTPUT */	
} sto_time_to_real8_struct;

void CDECL CDECL_EXT sto_time_to_real8(sto_time_to_real8_struct *p);
typedef void (CDECL CDECL_EXT* PFSTO_TIME_TO_REAL8_IEC) (sto_time_to_real8_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_TIME_TO_REAL8_NOTIMPLEMENTED)
	#define USE_sto_time_to_real8
	#define EXT_sto_time_to_real8
	#define GET_sto_time_to_real8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sto_time_to_real8(p0) 
	#define CHK_sto_time_to_real8  FALSE
	#define EXP_sto_time_to_real8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sto_time_to_real8
	#define EXT_sto_time_to_real8
	#define GET_sto_time_to_real8(fl)  CAL_CMGETAPI( "sto_time_to_real8" ) 
	#define CAL_sto_time_to_real8  sto_time_to_real8
	#define CHK_sto_time_to_real8  TRUE
	#define EXP_sto_time_to_real8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_time_to_real8", (RTS_UINTPTR)sto_time_to_real8, 1, RTSITF_GET_SIGNATURE(0, 0x9AE7381B), 0x03050528) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sto_time_to_real8
	#define EXT_sto_time_to_real8
	#define GET_sto_time_to_real8(fl)  CAL_CMGETAPI( "sto_time_to_real8" ) 
	#define CAL_sto_time_to_real8  sto_time_to_real8
	#define CHK_sto_time_to_real8  TRUE
	#define EXP_sto_time_to_real8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_time_to_real8", (RTS_UINTPTR)sto_time_to_real8, 1, RTSITF_GET_SIGNATURE(0, 0x9AE7381B), 0x03050528) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesto_time_to_real8
	#define EXT_CmpCAAStoragesto_time_to_real8
	#define GET_CmpCAAStoragesto_time_to_real8  ERR_OK
	#define CAL_CmpCAAStoragesto_time_to_real8  sto_time_to_real8
	#define CHK_CmpCAAStoragesto_time_to_real8  TRUE
	#define EXP_CmpCAAStoragesto_time_to_real8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_time_to_real8", (RTS_UINTPTR)sto_time_to_real8, 1, RTSITF_GET_SIGNATURE(0, 0x9AE7381B), 0x03050528) 
#elif defined(CPLUSPLUS)
	#define USE_sto_time_to_real8
	#define EXT_sto_time_to_real8
	#define GET_sto_time_to_real8(fl)  CAL_CMGETAPI( "sto_time_to_real8" ) 
	#define CAL_sto_time_to_real8  sto_time_to_real8
	#define CHK_sto_time_to_real8  TRUE
	#define EXP_sto_time_to_real8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_time_to_real8", (RTS_UINTPTR)sto_time_to_real8, 1, RTSITF_GET_SIGNATURE(0, 0x9AE7381B), 0x03050528) 
#else /* DYNAMIC_LINK */
	#define USE_sto_time_to_real8  PFSTO_TIME_TO_REAL8_IEC pfsto_time_to_real8;
	#define EXT_sto_time_to_real8  extern PFSTO_TIME_TO_REAL8_IEC pfsto_time_to_real8;
	#define GET_sto_time_to_real8(fl)  s_pfCMGetAPI2( "sto_time_to_real8", (RTS_VOID_FCTPTR *)&pfsto_time_to_real8, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x9AE7381B), 0x03050528)
	#define CAL_sto_time_to_real8  pfsto_time_to_real8
	#define CHK_sto_time_to_real8  (pfsto_time_to_real8 != NULL)
	#define EXP_sto_time_to_real8   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sto_time_to_real8", (RTS_UINTPTR)sto_time_to_real8, 1, RTSITF_GET_SIGNATURE(0, 0x9AE7381B), 0x03050528) 
#endif


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

void CDECL CDECL_EXT sti_columngetblob(sti_columngetblob_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNGETBLOB_IEC) (sti_columngetblob_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNGETBLOB_NOTIMPLEMENTED)
	#define USE_sti_columngetblob
	#define EXT_sti_columngetblob
	#define GET_sti_columngetblob(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columngetblob(p0) 
	#define CHK_sti_columngetblob  FALSE
	#define EXP_sti_columngetblob  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columngetblob
	#define EXT_sti_columngetblob
	#define GET_sti_columngetblob(fl)  CAL_CMGETAPI( "sti_columngetblob" ) 
	#define CAL_sti_columngetblob  sti_columngetblob
	#define CHK_sti_columngetblob  TRUE
	#define EXP_sti_columngetblob  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetblob", (RTS_UINTPTR)sti_columngetblob, 1, RTSITF_GET_SIGNATURE(0, 0xB97B2BA2), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columngetblob
	#define EXT_sti_columngetblob
	#define GET_sti_columngetblob(fl)  CAL_CMGETAPI( "sti_columngetblob" ) 
	#define CAL_sti_columngetblob  sti_columngetblob
	#define CHK_sti_columngetblob  TRUE
	#define EXP_sti_columngetblob  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetblob", (RTS_UINTPTR)sti_columngetblob, 1, RTSITF_GET_SIGNATURE(0, 0xB97B2BA2), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columngetblob
	#define EXT_CmpCAAStoragesti_columngetblob
	#define GET_CmpCAAStoragesti_columngetblob  ERR_OK
	#define CAL_CmpCAAStoragesti_columngetblob  sti_columngetblob
	#define CHK_CmpCAAStoragesti_columngetblob  TRUE
	#define EXP_CmpCAAStoragesti_columngetblob  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetblob", (RTS_UINTPTR)sti_columngetblob, 1, RTSITF_GET_SIGNATURE(0, 0xB97B2BA2), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columngetblob
	#define EXT_sti_columngetblob
	#define GET_sti_columngetblob(fl)  CAL_CMGETAPI( "sti_columngetblob" ) 
	#define CAL_sti_columngetblob  sti_columngetblob
	#define CHK_sti_columngetblob  TRUE
	#define EXP_sti_columngetblob  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetblob", (RTS_UINTPTR)sti_columngetblob, 1, RTSITF_GET_SIGNATURE(0, 0xB97B2BA2), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columngetblob  PFSTI_COLUMNGETBLOB_IEC pfsti_columngetblob;
	#define EXT_sti_columngetblob  extern PFSTI_COLUMNGETBLOB_IEC pfsti_columngetblob;
	#define GET_sti_columngetblob(fl)  s_pfCMGetAPI2( "sti_columngetblob", (RTS_VOID_FCTPTR *)&pfsti_columngetblob, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xB97B2BA2), 0x03050500)
	#define CAL_sti_columngetblob  pfsti_columngetblob
	#define CHK_sti_columngetblob  (pfsti_columngetblob != NULL)
	#define EXP_sti_columngetblob   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetblob", (RTS_UINTPTR)sti_columngetblob, 1, RTSITF_GET_SIGNATURE(0, 0xB97B2BA2), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columngetint16(sti_columngetint16_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNGETINT16_IEC) (sti_columngetint16_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNGETINT16_NOTIMPLEMENTED)
	#define USE_sti_columngetint16
	#define EXT_sti_columngetint16
	#define GET_sti_columngetint16(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columngetint16(p0) 
	#define CHK_sti_columngetint16  FALSE
	#define EXP_sti_columngetint16  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columngetint16
	#define EXT_sti_columngetint16
	#define GET_sti_columngetint16(fl)  CAL_CMGETAPI( "sti_columngetint16" ) 
	#define CAL_sti_columngetint16  sti_columngetint16
	#define CHK_sti_columngetint16  TRUE
	#define EXP_sti_columngetint16  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetint16", (RTS_UINTPTR)sti_columngetint16, 1, RTSITF_GET_SIGNATURE(0, 0x97DC91C7), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columngetint16
	#define EXT_sti_columngetint16
	#define GET_sti_columngetint16(fl)  CAL_CMGETAPI( "sti_columngetint16" ) 
	#define CAL_sti_columngetint16  sti_columngetint16
	#define CHK_sti_columngetint16  TRUE
	#define EXP_sti_columngetint16  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetint16", (RTS_UINTPTR)sti_columngetint16, 1, RTSITF_GET_SIGNATURE(0, 0x97DC91C7), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columngetint16
	#define EXT_CmpCAAStoragesti_columngetint16
	#define GET_CmpCAAStoragesti_columngetint16  ERR_OK
	#define CAL_CmpCAAStoragesti_columngetint16  sti_columngetint16
	#define CHK_CmpCAAStoragesti_columngetint16  TRUE
	#define EXP_CmpCAAStoragesti_columngetint16  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetint16", (RTS_UINTPTR)sti_columngetint16, 1, RTSITF_GET_SIGNATURE(0, 0x97DC91C7), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columngetint16
	#define EXT_sti_columngetint16
	#define GET_sti_columngetint16(fl)  CAL_CMGETAPI( "sti_columngetint16" ) 
	#define CAL_sti_columngetint16  sti_columngetint16
	#define CHK_sti_columngetint16  TRUE
	#define EXP_sti_columngetint16  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetint16", (RTS_UINTPTR)sti_columngetint16, 1, RTSITF_GET_SIGNATURE(0, 0x97DC91C7), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columngetint16  PFSTI_COLUMNGETINT16_IEC pfsti_columngetint16;
	#define EXT_sti_columngetint16  extern PFSTI_COLUMNGETINT16_IEC pfsti_columngetint16;
	#define GET_sti_columngetint16(fl)  s_pfCMGetAPI2( "sti_columngetint16", (RTS_VOID_FCTPTR *)&pfsti_columngetint16, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x97DC91C7), 0x03050500)
	#define CAL_sti_columngetint16  pfsti_columngetint16
	#define CHK_sti_columngetint16  (pfsti_columngetint16 != NULL)
	#define EXP_sti_columngetint16   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetint16", (RTS_UINTPTR)sti_columngetint16, 1, RTSITF_GET_SIGNATURE(0, 0x97DC91C7), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columngetint32(sti_columngetint32_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNGETINT32_IEC) (sti_columngetint32_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNGETINT32_NOTIMPLEMENTED)
	#define USE_sti_columngetint32
	#define EXT_sti_columngetint32
	#define GET_sti_columngetint32(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columngetint32(p0) 
	#define CHK_sti_columngetint32  FALSE
	#define EXP_sti_columngetint32  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columngetint32
	#define EXT_sti_columngetint32
	#define GET_sti_columngetint32(fl)  CAL_CMGETAPI( "sti_columngetint32" ) 
	#define CAL_sti_columngetint32  sti_columngetint32
	#define CHK_sti_columngetint32  TRUE
	#define EXP_sti_columngetint32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetint32", (RTS_UINTPTR)sti_columngetint32, 1, RTSITF_GET_SIGNATURE(0, 0xA00093D8), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columngetint32
	#define EXT_sti_columngetint32
	#define GET_sti_columngetint32(fl)  CAL_CMGETAPI( "sti_columngetint32" ) 
	#define CAL_sti_columngetint32  sti_columngetint32
	#define CHK_sti_columngetint32  TRUE
	#define EXP_sti_columngetint32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetint32", (RTS_UINTPTR)sti_columngetint32, 1, RTSITF_GET_SIGNATURE(0, 0xA00093D8), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columngetint32
	#define EXT_CmpCAAStoragesti_columngetint32
	#define GET_CmpCAAStoragesti_columngetint32  ERR_OK
	#define CAL_CmpCAAStoragesti_columngetint32  sti_columngetint32
	#define CHK_CmpCAAStoragesti_columngetint32  TRUE
	#define EXP_CmpCAAStoragesti_columngetint32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetint32", (RTS_UINTPTR)sti_columngetint32, 1, RTSITF_GET_SIGNATURE(0, 0xA00093D8), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columngetint32
	#define EXT_sti_columngetint32
	#define GET_sti_columngetint32(fl)  CAL_CMGETAPI( "sti_columngetint32" ) 
	#define CAL_sti_columngetint32  sti_columngetint32
	#define CHK_sti_columngetint32  TRUE
	#define EXP_sti_columngetint32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetint32", (RTS_UINTPTR)sti_columngetint32, 1, RTSITF_GET_SIGNATURE(0, 0xA00093D8), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columngetint32  PFSTI_COLUMNGETINT32_IEC pfsti_columngetint32;
	#define EXT_sti_columngetint32  extern PFSTI_COLUMNGETINT32_IEC pfsti_columngetint32;
	#define GET_sti_columngetint32(fl)  s_pfCMGetAPI2( "sti_columngetint32", (RTS_VOID_FCTPTR *)&pfsti_columngetint32, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA00093D8), 0x03050500)
	#define CAL_sti_columngetint32  pfsti_columngetint32
	#define CHK_sti_columngetint32  (pfsti_columngetint32 != NULL)
	#define EXP_sti_columngetint32   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetint32", (RTS_UINTPTR)sti_columngetint32, 1, RTSITF_GET_SIGNATURE(0, 0xA00093D8), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columngetint64(sti_columngetint64_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNGETINT64_IEC) (sti_columngetint64_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNGETINT64_NOTIMPLEMENTED)
	#define USE_sti_columngetint64
	#define EXT_sti_columngetint64
	#define GET_sti_columngetint64(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columngetint64(p0) 
	#define CHK_sti_columngetint64  FALSE
	#define EXP_sti_columngetint64  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columngetint64
	#define EXT_sti_columngetint64
	#define GET_sti_columngetint64(fl)  CAL_CMGETAPI( "sti_columngetint64" ) 
	#define CAL_sti_columngetint64  sti_columngetint64
	#define CHK_sti_columngetint64  TRUE
	#define EXP_sti_columngetint64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetint64", (RTS_UINTPTR)sti_columngetint64, 1, RTSITF_GET_SIGNATURE(0, 0x6F0701A6), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columngetint64
	#define EXT_sti_columngetint64
	#define GET_sti_columngetint64(fl)  CAL_CMGETAPI( "sti_columngetint64" ) 
	#define CAL_sti_columngetint64  sti_columngetint64
	#define CHK_sti_columngetint64  TRUE
	#define EXP_sti_columngetint64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetint64", (RTS_UINTPTR)sti_columngetint64, 1, RTSITF_GET_SIGNATURE(0, 0x6F0701A6), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columngetint64
	#define EXT_CmpCAAStoragesti_columngetint64
	#define GET_CmpCAAStoragesti_columngetint64  ERR_OK
	#define CAL_CmpCAAStoragesti_columngetint64  sti_columngetint64
	#define CHK_CmpCAAStoragesti_columngetint64  TRUE
	#define EXP_CmpCAAStoragesti_columngetint64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetint64", (RTS_UINTPTR)sti_columngetint64, 1, RTSITF_GET_SIGNATURE(0, 0x6F0701A6), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columngetint64
	#define EXT_sti_columngetint64
	#define GET_sti_columngetint64(fl)  CAL_CMGETAPI( "sti_columngetint64" ) 
	#define CAL_sti_columngetint64  sti_columngetint64
	#define CHK_sti_columngetint64  TRUE
	#define EXP_sti_columngetint64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetint64", (RTS_UINTPTR)sti_columngetint64, 1, RTSITF_GET_SIGNATURE(0, 0x6F0701A6), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columngetint64  PFSTI_COLUMNGETINT64_IEC pfsti_columngetint64;
	#define EXT_sti_columngetint64  extern PFSTI_COLUMNGETINT64_IEC pfsti_columngetint64;
	#define GET_sti_columngetint64(fl)  s_pfCMGetAPI2( "sti_columngetint64", (RTS_VOID_FCTPTR *)&pfsti_columngetint64, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x6F0701A6), 0x03050500)
	#define CAL_sti_columngetint64  pfsti_columngetint64
	#define CHK_sti_columngetint64  (pfsti_columngetint64 != NULL)
	#define EXP_sti_columngetint64   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetint64", (RTS_UINTPTR)sti_columngetint64, 1, RTSITF_GET_SIGNATURE(0, 0x6F0701A6), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columngetint8(sti_columngetint8_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNGETINT8_IEC) (sti_columngetint8_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNGETINT8_NOTIMPLEMENTED)
	#define USE_sti_columngetint8
	#define EXT_sti_columngetint8
	#define GET_sti_columngetint8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columngetint8(p0) 
	#define CHK_sti_columngetint8  FALSE
	#define EXP_sti_columngetint8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columngetint8
	#define EXT_sti_columngetint8
	#define GET_sti_columngetint8(fl)  CAL_CMGETAPI( "sti_columngetint8" ) 
	#define CAL_sti_columngetint8  sti_columngetint8
	#define CHK_sti_columngetint8  TRUE
	#define EXP_sti_columngetint8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetint8", (RTS_UINTPTR)sti_columngetint8, 1, RTSITF_GET_SIGNATURE(0, 0xD764B7BA), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columngetint8
	#define EXT_sti_columngetint8
	#define GET_sti_columngetint8(fl)  CAL_CMGETAPI( "sti_columngetint8" ) 
	#define CAL_sti_columngetint8  sti_columngetint8
	#define CHK_sti_columngetint8  TRUE
	#define EXP_sti_columngetint8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetint8", (RTS_UINTPTR)sti_columngetint8, 1, RTSITF_GET_SIGNATURE(0, 0xD764B7BA), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columngetint8
	#define EXT_CmpCAAStoragesti_columngetint8
	#define GET_CmpCAAStoragesti_columngetint8  ERR_OK
	#define CAL_CmpCAAStoragesti_columngetint8  sti_columngetint8
	#define CHK_CmpCAAStoragesti_columngetint8  TRUE
	#define EXP_CmpCAAStoragesti_columngetint8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetint8", (RTS_UINTPTR)sti_columngetint8, 1, RTSITF_GET_SIGNATURE(0, 0xD764B7BA), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columngetint8
	#define EXT_sti_columngetint8
	#define GET_sti_columngetint8(fl)  CAL_CMGETAPI( "sti_columngetint8" ) 
	#define CAL_sti_columngetint8  sti_columngetint8
	#define CHK_sti_columngetint8  TRUE
	#define EXP_sti_columngetint8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetint8", (RTS_UINTPTR)sti_columngetint8, 1, RTSITF_GET_SIGNATURE(0, 0xD764B7BA), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columngetint8  PFSTI_COLUMNGETINT8_IEC pfsti_columngetint8;
	#define EXT_sti_columngetint8  extern PFSTI_COLUMNGETINT8_IEC pfsti_columngetint8;
	#define GET_sti_columngetint8(fl)  s_pfCMGetAPI2( "sti_columngetint8", (RTS_VOID_FCTPTR *)&pfsti_columngetint8, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xD764B7BA), 0x03050500)
	#define CAL_sti_columngetint8  pfsti_columngetint8
	#define CHK_sti_columngetint8  (pfsti_columngetint8 != NULL)
	#define EXP_sti_columngetint8   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetint8", (RTS_UINTPTR)sti_columngetint8, 1, RTSITF_GET_SIGNATURE(0, 0xD764B7BA), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columngetreal4(sti_columngetreal4_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNGETREAL4_IEC) (sti_columngetreal4_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNGETREAL4_NOTIMPLEMENTED)
	#define USE_sti_columngetreal4
	#define EXT_sti_columngetreal4
	#define GET_sti_columngetreal4(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columngetreal4(p0) 
	#define CHK_sti_columngetreal4  FALSE
	#define EXP_sti_columngetreal4  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columngetreal4
	#define EXT_sti_columngetreal4
	#define GET_sti_columngetreal4(fl)  CAL_CMGETAPI( "sti_columngetreal4" ) 
	#define CAL_sti_columngetreal4  sti_columngetreal4
	#define CHK_sti_columngetreal4  TRUE
	#define EXP_sti_columngetreal4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetreal4", (RTS_UINTPTR)sti_columngetreal4, 1, RTSITF_GET_SIGNATURE(0, 0x42BD9968), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columngetreal4
	#define EXT_sti_columngetreal4
	#define GET_sti_columngetreal4(fl)  CAL_CMGETAPI( "sti_columngetreal4" ) 
	#define CAL_sti_columngetreal4  sti_columngetreal4
	#define CHK_sti_columngetreal4  TRUE
	#define EXP_sti_columngetreal4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetreal4", (RTS_UINTPTR)sti_columngetreal4, 1, RTSITF_GET_SIGNATURE(0, 0x42BD9968), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columngetreal4
	#define EXT_CmpCAAStoragesti_columngetreal4
	#define GET_CmpCAAStoragesti_columngetreal4  ERR_OK
	#define CAL_CmpCAAStoragesti_columngetreal4  sti_columngetreal4
	#define CHK_CmpCAAStoragesti_columngetreal4  TRUE
	#define EXP_CmpCAAStoragesti_columngetreal4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetreal4", (RTS_UINTPTR)sti_columngetreal4, 1, RTSITF_GET_SIGNATURE(0, 0x42BD9968), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columngetreal4
	#define EXT_sti_columngetreal4
	#define GET_sti_columngetreal4(fl)  CAL_CMGETAPI( "sti_columngetreal4" ) 
	#define CAL_sti_columngetreal4  sti_columngetreal4
	#define CHK_sti_columngetreal4  TRUE
	#define EXP_sti_columngetreal4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetreal4", (RTS_UINTPTR)sti_columngetreal4, 1, RTSITF_GET_SIGNATURE(0, 0x42BD9968), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columngetreal4  PFSTI_COLUMNGETREAL4_IEC pfsti_columngetreal4;
	#define EXT_sti_columngetreal4  extern PFSTI_COLUMNGETREAL4_IEC pfsti_columngetreal4;
	#define GET_sti_columngetreal4(fl)  s_pfCMGetAPI2( "sti_columngetreal4", (RTS_VOID_FCTPTR *)&pfsti_columngetreal4, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x42BD9968), 0x03050500)
	#define CAL_sti_columngetreal4  pfsti_columngetreal4
	#define CHK_sti_columngetreal4  (pfsti_columngetreal4 != NULL)
	#define EXP_sti_columngetreal4   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetreal4", (RTS_UINTPTR)sti_columngetreal4, 1, RTSITF_GET_SIGNATURE(0, 0x42BD9968), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columngetreal8(sti_columngetreal8_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNGETREAL8_IEC) (sti_columngetreal8_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNGETREAL8_NOTIMPLEMENTED)
	#define USE_sti_columngetreal8
	#define EXT_sti_columngetreal8
	#define GET_sti_columngetreal8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columngetreal8(p0) 
	#define CHK_sti_columngetreal8  FALSE
	#define EXP_sti_columngetreal8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columngetreal8
	#define EXT_sti_columngetreal8
	#define GET_sti_columngetreal8(fl)  CAL_CMGETAPI( "sti_columngetreal8" ) 
	#define CAL_sti_columngetreal8  sti_columngetreal8
	#define CHK_sti_columngetreal8  TRUE
	#define EXP_sti_columngetreal8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetreal8", (RTS_UINTPTR)sti_columngetreal8, 1, RTSITF_GET_SIGNATURE(0, 0xD317D94F), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columngetreal8
	#define EXT_sti_columngetreal8
	#define GET_sti_columngetreal8(fl)  CAL_CMGETAPI( "sti_columngetreal8" ) 
	#define CAL_sti_columngetreal8  sti_columngetreal8
	#define CHK_sti_columngetreal8  TRUE
	#define EXP_sti_columngetreal8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetreal8", (RTS_UINTPTR)sti_columngetreal8, 1, RTSITF_GET_SIGNATURE(0, 0xD317D94F), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columngetreal8
	#define EXT_CmpCAAStoragesti_columngetreal8
	#define GET_CmpCAAStoragesti_columngetreal8  ERR_OK
	#define CAL_CmpCAAStoragesti_columngetreal8  sti_columngetreal8
	#define CHK_CmpCAAStoragesti_columngetreal8  TRUE
	#define EXP_CmpCAAStoragesti_columngetreal8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetreal8", (RTS_UINTPTR)sti_columngetreal8, 1, RTSITF_GET_SIGNATURE(0, 0xD317D94F), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columngetreal8
	#define EXT_sti_columngetreal8
	#define GET_sti_columngetreal8(fl)  CAL_CMGETAPI( "sti_columngetreal8" ) 
	#define CAL_sti_columngetreal8  sti_columngetreal8
	#define CHK_sti_columngetreal8  TRUE
	#define EXP_sti_columngetreal8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetreal8", (RTS_UINTPTR)sti_columngetreal8, 1, RTSITF_GET_SIGNATURE(0, 0xD317D94F), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columngetreal8  PFSTI_COLUMNGETREAL8_IEC pfsti_columngetreal8;
	#define EXT_sti_columngetreal8  extern PFSTI_COLUMNGETREAL8_IEC pfsti_columngetreal8;
	#define GET_sti_columngetreal8(fl)  s_pfCMGetAPI2( "sti_columngetreal8", (RTS_VOID_FCTPTR *)&pfsti_columngetreal8, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xD317D94F), 0x03050500)
	#define CAL_sti_columngetreal8  pfsti_columngetreal8
	#define CHK_sti_columngetreal8  (pfsti_columngetreal8 != NULL)
	#define EXP_sti_columngetreal8   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngetreal8", (RTS_UINTPTR)sti_columngetreal8, 1, RTSITF_GET_SIGNATURE(0, 0xD317D94F), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columngettext(sti_columngettext_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNGETTEXT_IEC) (sti_columngettext_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNGETTEXT_NOTIMPLEMENTED)
	#define USE_sti_columngettext
	#define EXT_sti_columngettext
	#define GET_sti_columngettext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columngettext(p0) 
	#define CHK_sti_columngettext  FALSE
	#define EXP_sti_columngettext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columngettext
	#define EXT_sti_columngettext
	#define GET_sti_columngettext(fl)  CAL_CMGETAPI( "sti_columngettext" ) 
	#define CAL_sti_columngettext  sti_columngettext
	#define CHK_sti_columngettext  TRUE
	#define EXP_sti_columngettext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngettext", (RTS_UINTPTR)sti_columngettext, 1, RTSITF_GET_SIGNATURE(0, 0xF479FDE3), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columngettext
	#define EXT_sti_columngettext
	#define GET_sti_columngettext(fl)  CAL_CMGETAPI( "sti_columngettext" ) 
	#define CAL_sti_columngettext  sti_columngettext
	#define CHK_sti_columngettext  TRUE
	#define EXP_sti_columngettext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngettext", (RTS_UINTPTR)sti_columngettext, 1, RTSITF_GET_SIGNATURE(0, 0xF479FDE3), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columngettext
	#define EXT_CmpCAAStoragesti_columngettext
	#define GET_CmpCAAStoragesti_columngettext  ERR_OK
	#define CAL_CmpCAAStoragesti_columngettext  sti_columngettext
	#define CHK_CmpCAAStoragesti_columngettext  TRUE
	#define EXP_CmpCAAStoragesti_columngettext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngettext", (RTS_UINTPTR)sti_columngettext, 1, RTSITF_GET_SIGNATURE(0, 0xF479FDE3), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columngettext
	#define EXT_sti_columngettext
	#define GET_sti_columngettext(fl)  CAL_CMGETAPI( "sti_columngettext" ) 
	#define CAL_sti_columngettext  sti_columngettext
	#define CHK_sti_columngettext  TRUE
	#define EXP_sti_columngettext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngettext", (RTS_UINTPTR)sti_columngettext, 1, RTSITF_GET_SIGNATURE(0, 0xF479FDE3), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columngettext  PFSTI_COLUMNGETTEXT_IEC pfsti_columngettext;
	#define EXT_sti_columngettext  extern PFSTI_COLUMNGETTEXT_IEC pfsti_columngettext;
	#define GET_sti_columngettext(fl)  s_pfCMGetAPI2( "sti_columngettext", (RTS_VOID_FCTPTR *)&pfsti_columngettext, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xF479FDE3), 0x03050500)
	#define CAL_sti_columngettext  pfsti_columngettext
	#define CHK_sti_columngettext  (pfsti_columngettext != NULL)
	#define EXP_sti_columngettext   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngettext", (RTS_UINTPTR)sti_columngettext, 1, RTSITF_GET_SIGNATURE(0, 0xF479FDE3), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columngettype(sti_columngettype_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNGETTYPE_IEC) (sti_columngettype_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNGETTYPE_NOTIMPLEMENTED)
	#define USE_sti_columngettype
	#define EXT_sti_columngettype
	#define GET_sti_columngettype(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columngettype(p0) 
	#define CHK_sti_columngettype  FALSE
	#define EXP_sti_columngettype  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columngettype
	#define EXT_sti_columngettype
	#define GET_sti_columngettype(fl)  CAL_CMGETAPI( "sti_columngettype" ) 
	#define CAL_sti_columngettype  sti_columngettype
	#define CHK_sti_columngettype  TRUE
	#define EXP_sti_columngettype  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngettype", (RTS_UINTPTR)sti_columngettype, 1, RTSITF_GET_SIGNATURE(0, 0xF48C90AA), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columngettype
	#define EXT_sti_columngettype
	#define GET_sti_columngettype(fl)  CAL_CMGETAPI( "sti_columngettype" ) 
	#define CAL_sti_columngettype  sti_columngettype
	#define CHK_sti_columngettype  TRUE
	#define EXP_sti_columngettype  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngettype", (RTS_UINTPTR)sti_columngettype, 1, RTSITF_GET_SIGNATURE(0, 0xF48C90AA), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columngettype
	#define EXT_CmpCAAStoragesti_columngettype
	#define GET_CmpCAAStoragesti_columngettype  ERR_OK
	#define CAL_CmpCAAStoragesti_columngettype  sti_columngettype
	#define CHK_CmpCAAStoragesti_columngettype  TRUE
	#define EXP_CmpCAAStoragesti_columngettype  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngettype", (RTS_UINTPTR)sti_columngettype, 1, RTSITF_GET_SIGNATURE(0, 0xF48C90AA), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columngettype
	#define EXT_sti_columngettype
	#define GET_sti_columngettype(fl)  CAL_CMGETAPI( "sti_columngettype" ) 
	#define CAL_sti_columngettype  sti_columngettype
	#define CHK_sti_columngettype  TRUE
	#define EXP_sti_columngettype  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngettype", (RTS_UINTPTR)sti_columngettype, 1, RTSITF_GET_SIGNATURE(0, 0xF48C90AA), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columngettype  PFSTI_COLUMNGETTYPE_IEC pfsti_columngettype;
	#define EXT_sti_columngettype  extern PFSTI_COLUMNGETTYPE_IEC pfsti_columngettype;
	#define GET_sti_columngettype(fl)  s_pfCMGetAPI2( "sti_columngettype", (RTS_VOID_FCTPTR *)&pfsti_columngettype, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xF48C90AA), 0x03050500)
	#define CAL_sti_columngettype  pfsti_columngettype
	#define CHK_sti_columngettype  (pfsti_columngettype != NULL)
	#define EXP_sti_columngettype   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columngettype", (RTS_UINTPTR)sti_columngettype, 1, RTSITF_GET_SIGNATURE(0, 0xF48C90AA), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columnsetblob(sti_columnsetblob_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNSETBLOB_IEC) (sti_columnsetblob_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNSETBLOB_NOTIMPLEMENTED)
	#define USE_sti_columnsetblob
	#define EXT_sti_columnsetblob
	#define GET_sti_columnsetblob(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columnsetblob(p0) 
	#define CHK_sti_columnsetblob  FALSE
	#define EXP_sti_columnsetblob  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columnsetblob
	#define EXT_sti_columnsetblob
	#define GET_sti_columnsetblob(fl)  CAL_CMGETAPI( "sti_columnsetblob" ) 
	#define CAL_sti_columnsetblob  sti_columnsetblob
	#define CHK_sti_columnsetblob  TRUE
	#define EXP_sti_columnsetblob  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetblob", (RTS_UINTPTR)sti_columnsetblob, 1, RTSITF_GET_SIGNATURE(0, 0x00CA4524), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columnsetblob
	#define EXT_sti_columnsetblob
	#define GET_sti_columnsetblob(fl)  CAL_CMGETAPI( "sti_columnsetblob" ) 
	#define CAL_sti_columnsetblob  sti_columnsetblob
	#define CHK_sti_columnsetblob  TRUE
	#define EXP_sti_columnsetblob  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetblob", (RTS_UINTPTR)sti_columnsetblob, 1, RTSITF_GET_SIGNATURE(0, 0x00CA4524), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columnsetblob
	#define EXT_CmpCAAStoragesti_columnsetblob
	#define GET_CmpCAAStoragesti_columnsetblob  ERR_OK
	#define CAL_CmpCAAStoragesti_columnsetblob  sti_columnsetblob
	#define CHK_CmpCAAStoragesti_columnsetblob  TRUE
	#define EXP_CmpCAAStoragesti_columnsetblob  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetblob", (RTS_UINTPTR)sti_columnsetblob, 1, RTSITF_GET_SIGNATURE(0, 0x00CA4524), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columnsetblob
	#define EXT_sti_columnsetblob
	#define GET_sti_columnsetblob(fl)  CAL_CMGETAPI( "sti_columnsetblob" ) 
	#define CAL_sti_columnsetblob  sti_columnsetblob
	#define CHK_sti_columnsetblob  TRUE
	#define EXP_sti_columnsetblob  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetblob", (RTS_UINTPTR)sti_columnsetblob, 1, RTSITF_GET_SIGNATURE(0, 0x00CA4524), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columnsetblob  PFSTI_COLUMNSETBLOB_IEC pfsti_columnsetblob;
	#define EXT_sti_columnsetblob  extern PFSTI_COLUMNSETBLOB_IEC pfsti_columnsetblob;
	#define GET_sti_columnsetblob(fl)  s_pfCMGetAPI2( "sti_columnsetblob", (RTS_VOID_FCTPTR *)&pfsti_columnsetblob, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x00CA4524), 0x03050500)
	#define CAL_sti_columnsetblob  pfsti_columnsetblob
	#define CHK_sti_columnsetblob  (pfsti_columnsetblob != NULL)
	#define EXP_sti_columnsetblob   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetblob", (RTS_UINTPTR)sti_columnsetblob, 1, RTSITF_GET_SIGNATURE(0, 0x00CA4524), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columnsetint16(sti_columnsetint16_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNSETINT16_IEC) (sti_columnsetint16_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNSETINT16_NOTIMPLEMENTED)
	#define USE_sti_columnsetint16
	#define EXT_sti_columnsetint16
	#define GET_sti_columnsetint16(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columnsetint16(p0) 
	#define CHK_sti_columnsetint16  FALSE
	#define EXP_sti_columnsetint16  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columnsetint16
	#define EXT_sti_columnsetint16
	#define GET_sti_columnsetint16(fl)  CAL_CMGETAPI( "sti_columnsetint16" ) 
	#define CAL_sti_columnsetint16  sti_columnsetint16
	#define CHK_sti_columnsetint16  TRUE
	#define EXP_sti_columnsetint16  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetint16", (RTS_UINTPTR)sti_columnsetint16, 1, RTSITF_GET_SIGNATURE(0, 0xA2F90964), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columnsetint16
	#define EXT_sti_columnsetint16
	#define GET_sti_columnsetint16(fl)  CAL_CMGETAPI( "sti_columnsetint16" ) 
	#define CAL_sti_columnsetint16  sti_columnsetint16
	#define CHK_sti_columnsetint16  TRUE
	#define EXP_sti_columnsetint16  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetint16", (RTS_UINTPTR)sti_columnsetint16, 1, RTSITF_GET_SIGNATURE(0, 0xA2F90964), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columnsetint16
	#define EXT_CmpCAAStoragesti_columnsetint16
	#define GET_CmpCAAStoragesti_columnsetint16  ERR_OK
	#define CAL_CmpCAAStoragesti_columnsetint16  sti_columnsetint16
	#define CHK_CmpCAAStoragesti_columnsetint16  TRUE
	#define EXP_CmpCAAStoragesti_columnsetint16  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetint16", (RTS_UINTPTR)sti_columnsetint16, 1, RTSITF_GET_SIGNATURE(0, 0xA2F90964), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columnsetint16
	#define EXT_sti_columnsetint16
	#define GET_sti_columnsetint16(fl)  CAL_CMGETAPI( "sti_columnsetint16" ) 
	#define CAL_sti_columnsetint16  sti_columnsetint16
	#define CHK_sti_columnsetint16  TRUE
	#define EXP_sti_columnsetint16  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetint16", (RTS_UINTPTR)sti_columnsetint16, 1, RTSITF_GET_SIGNATURE(0, 0xA2F90964), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columnsetint16  PFSTI_COLUMNSETINT16_IEC pfsti_columnsetint16;
	#define EXT_sti_columnsetint16  extern PFSTI_COLUMNSETINT16_IEC pfsti_columnsetint16;
	#define GET_sti_columnsetint16(fl)  s_pfCMGetAPI2( "sti_columnsetint16", (RTS_VOID_FCTPTR *)&pfsti_columnsetint16, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA2F90964), 0x03050500)
	#define CAL_sti_columnsetint16  pfsti_columnsetint16
	#define CHK_sti_columnsetint16  (pfsti_columnsetint16 != NULL)
	#define EXP_sti_columnsetint16   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetint16", (RTS_UINTPTR)sti_columnsetint16, 1, RTSITF_GET_SIGNATURE(0, 0xA2F90964), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columnsetint32(sti_columnsetint32_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNSETINT32_IEC) (sti_columnsetint32_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNSETINT32_NOTIMPLEMENTED)
	#define USE_sti_columnsetint32
	#define EXT_sti_columnsetint32
	#define GET_sti_columnsetint32(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columnsetint32(p0) 
	#define CHK_sti_columnsetint32  FALSE
	#define EXP_sti_columnsetint32  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columnsetint32
	#define EXT_sti_columnsetint32
	#define GET_sti_columnsetint32(fl)  CAL_CMGETAPI( "sti_columnsetint32" ) 
	#define CAL_sti_columnsetint32  sti_columnsetint32
	#define CHK_sti_columnsetint32  TRUE
	#define EXP_sti_columnsetint32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetint32", (RTS_UINTPTR)sti_columnsetint32, 1, RTSITF_GET_SIGNATURE(0, 0xD8641CB9), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columnsetint32
	#define EXT_sti_columnsetint32
	#define GET_sti_columnsetint32(fl)  CAL_CMGETAPI( "sti_columnsetint32" ) 
	#define CAL_sti_columnsetint32  sti_columnsetint32
	#define CHK_sti_columnsetint32  TRUE
	#define EXP_sti_columnsetint32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetint32", (RTS_UINTPTR)sti_columnsetint32, 1, RTSITF_GET_SIGNATURE(0, 0xD8641CB9), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columnsetint32
	#define EXT_CmpCAAStoragesti_columnsetint32
	#define GET_CmpCAAStoragesti_columnsetint32  ERR_OK
	#define CAL_CmpCAAStoragesti_columnsetint32  sti_columnsetint32
	#define CHK_CmpCAAStoragesti_columnsetint32  TRUE
	#define EXP_CmpCAAStoragesti_columnsetint32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetint32", (RTS_UINTPTR)sti_columnsetint32, 1, RTSITF_GET_SIGNATURE(0, 0xD8641CB9), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columnsetint32
	#define EXT_sti_columnsetint32
	#define GET_sti_columnsetint32(fl)  CAL_CMGETAPI( "sti_columnsetint32" ) 
	#define CAL_sti_columnsetint32  sti_columnsetint32
	#define CHK_sti_columnsetint32  TRUE
	#define EXP_sti_columnsetint32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetint32", (RTS_UINTPTR)sti_columnsetint32, 1, RTSITF_GET_SIGNATURE(0, 0xD8641CB9), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columnsetint32  PFSTI_COLUMNSETINT32_IEC pfsti_columnsetint32;
	#define EXT_sti_columnsetint32  extern PFSTI_COLUMNSETINT32_IEC pfsti_columnsetint32;
	#define GET_sti_columnsetint32(fl)  s_pfCMGetAPI2( "sti_columnsetint32", (RTS_VOID_FCTPTR *)&pfsti_columnsetint32, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xD8641CB9), 0x03050500)
	#define CAL_sti_columnsetint32  pfsti_columnsetint32
	#define CHK_sti_columnsetint32  (pfsti_columnsetint32 != NULL)
	#define EXP_sti_columnsetint32   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetint32", (RTS_UINTPTR)sti_columnsetint32, 1, RTSITF_GET_SIGNATURE(0, 0xD8641CB9), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columnsetint64(sti_columnsetint64_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNSETINT64_IEC) (sti_columnsetint64_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNSETINT64_NOTIMPLEMENTED)
	#define USE_sti_columnsetint64
	#define EXT_sti_columnsetint64
	#define GET_sti_columnsetint64(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columnsetint64(p0) 
	#define CHK_sti_columnsetint64  FALSE
	#define EXP_sti_columnsetint64  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columnsetint64
	#define EXT_sti_columnsetint64
	#define GET_sti_columnsetint64(fl)  CAL_CMGETAPI( "sti_columnsetint64" ) 
	#define CAL_sti_columnsetint64  sti_columnsetint64
	#define CHK_sti_columnsetint64  TRUE
	#define EXP_sti_columnsetint64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetint64", (RTS_UINTPTR)sti_columnsetint64, 1, RTSITF_GET_SIGNATURE(0, 0x17638EC7), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columnsetint64
	#define EXT_sti_columnsetint64
	#define GET_sti_columnsetint64(fl)  CAL_CMGETAPI( "sti_columnsetint64" ) 
	#define CAL_sti_columnsetint64  sti_columnsetint64
	#define CHK_sti_columnsetint64  TRUE
	#define EXP_sti_columnsetint64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetint64", (RTS_UINTPTR)sti_columnsetint64, 1, RTSITF_GET_SIGNATURE(0, 0x17638EC7), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columnsetint64
	#define EXT_CmpCAAStoragesti_columnsetint64
	#define GET_CmpCAAStoragesti_columnsetint64  ERR_OK
	#define CAL_CmpCAAStoragesti_columnsetint64  sti_columnsetint64
	#define CHK_CmpCAAStoragesti_columnsetint64  TRUE
	#define EXP_CmpCAAStoragesti_columnsetint64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetint64", (RTS_UINTPTR)sti_columnsetint64, 1, RTSITF_GET_SIGNATURE(0, 0x17638EC7), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columnsetint64
	#define EXT_sti_columnsetint64
	#define GET_sti_columnsetint64(fl)  CAL_CMGETAPI( "sti_columnsetint64" ) 
	#define CAL_sti_columnsetint64  sti_columnsetint64
	#define CHK_sti_columnsetint64  TRUE
	#define EXP_sti_columnsetint64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetint64", (RTS_UINTPTR)sti_columnsetint64, 1, RTSITF_GET_SIGNATURE(0, 0x17638EC7), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columnsetint64  PFSTI_COLUMNSETINT64_IEC pfsti_columnsetint64;
	#define EXT_sti_columnsetint64  extern PFSTI_COLUMNSETINT64_IEC pfsti_columnsetint64;
	#define GET_sti_columnsetint64(fl)  s_pfCMGetAPI2( "sti_columnsetint64", (RTS_VOID_FCTPTR *)&pfsti_columnsetint64, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x17638EC7), 0x03050500)
	#define CAL_sti_columnsetint64  pfsti_columnsetint64
	#define CHK_sti_columnsetint64  (pfsti_columnsetint64 != NULL)
	#define EXP_sti_columnsetint64   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetint64", (RTS_UINTPTR)sti_columnsetint64, 1, RTSITF_GET_SIGNATURE(0, 0x17638EC7), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columnsetint8(sti_columnsetint8_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNSETINT8_IEC) (sti_columnsetint8_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNSETINT8_NOTIMPLEMENTED)
	#define USE_sti_columnsetint8
	#define EXT_sti_columnsetint8
	#define GET_sti_columnsetint8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columnsetint8(p0) 
	#define CHK_sti_columnsetint8  FALSE
	#define EXP_sti_columnsetint8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columnsetint8
	#define EXT_sti_columnsetint8
	#define GET_sti_columnsetint8(fl)  CAL_CMGETAPI( "sti_columnsetint8" ) 
	#define CAL_sti_columnsetint8  sti_columnsetint8
	#define CHK_sti_columnsetint8  TRUE
	#define EXP_sti_columnsetint8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetint8", (RTS_UINTPTR)sti_columnsetint8, 1, RTSITF_GET_SIGNATURE(0, 0x06E3E872), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columnsetint8
	#define EXT_sti_columnsetint8
	#define GET_sti_columnsetint8(fl)  CAL_CMGETAPI( "sti_columnsetint8" ) 
	#define CAL_sti_columnsetint8  sti_columnsetint8
	#define CHK_sti_columnsetint8  TRUE
	#define EXP_sti_columnsetint8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetint8", (RTS_UINTPTR)sti_columnsetint8, 1, RTSITF_GET_SIGNATURE(0, 0x06E3E872), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columnsetint8
	#define EXT_CmpCAAStoragesti_columnsetint8
	#define GET_CmpCAAStoragesti_columnsetint8  ERR_OK
	#define CAL_CmpCAAStoragesti_columnsetint8  sti_columnsetint8
	#define CHK_CmpCAAStoragesti_columnsetint8  TRUE
	#define EXP_CmpCAAStoragesti_columnsetint8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetint8", (RTS_UINTPTR)sti_columnsetint8, 1, RTSITF_GET_SIGNATURE(0, 0x06E3E872), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columnsetint8
	#define EXT_sti_columnsetint8
	#define GET_sti_columnsetint8(fl)  CAL_CMGETAPI( "sti_columnsetint8" ) 
	#define CAL_sti_columnsetint8  sti_columnsetint8
	#define CHK_sti_columnsetint8  TRUE
	#define EXP_sti_columnsetint8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetint8", (RTS_UINTPTR)sti_columnsetint8, 1, RTSITF_GET_SIGNATURE(0, 0x06E3E872), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columnsetint8  PFSTI_COLUMNSETINT8_IEC pfsti_columnsetint8;
	#define EXT_sti_columnsetint8  extern PFSTI_COLUMNSETINT8_IEC pfsti_columnsetint8;
	#define GET_sti_columnsetint8(fl)  s_pfCMGetAPI2( "sti_columnsetint8", (RTS_VOID_FCTPTR *)&pfsti_columnsetint8, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x06E3E872), 0x03050500)
	#define CAL_sti_columnsetint8  pfsti_columnsetint8
	#define CHK_sti_columnsetint8  (pfsti_columnsetint8 != NULL)
	#define EXP_sti_columnsetint8   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetint8", (RTS_UINTPTR)sti_columnsetint8, 1, RTSITF_GET_SIGNATURE(0, 0x06E3E872), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_columnsetnull_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD idColumn;				/* VAR_INPUT */	
	RTS_IEC_INT STI_ColumnSetNULL;		/* VAR_OUTPUT, Enum: ERROR */
} sti_columnsetnull_struct;

void CDECL CDECL_EXT sti_columnsetnull(sti_columnsetnull_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNSETNULL_IEC) (sti_columnsetnull_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNSETNULL_NOTIMPLEMENTED)
	#define USE_sti_columnsetnull
	#define EXT_sti_columnsetnull
	#define GET_sti_columnsetnull(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columnsetnull(p0) 
	#define CHK_sti_columnsetnull  FALSE
	#define EXP_sti_columnsetnull  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columnsetnull
	#define EXT_sti_columnsetnull
	#define GET_sti_columnsetnull(fl)  CAL_CMGETAPI( "sti_columnsetnull" ) 
	#define CAL_sti_columnsetnull  sti_columnsetnull
	#define CHK_sti_columnsetnull  TRUE
	#define EXP_sti_columnsetnull  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetnull", (RTS_UINTPTR)sti_columnsetnull, 1, RTSITF_GET_SIGNATURE(0, 0x9543CD3B), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columnsetnull
	#define EXT_sti_columnsetnull
	#define GET_sti_columnsetnull(fl)  CAL_CMGETAPI( "sti_columnsetnull" ) 
	#define CAL_sti_columnsetnull  sti_columnsetnull
	#define CHK_sti_columnsetnull  TRUE
	#define EXP_sti_columnsetnull  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetnull", (RTS_UINTPTR)sti_columnsetnull, 1, RTSITF_GET_SIGNATURE(0, 0x9543CD3B), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columnsetnull
	#define EXT_CmpCAAStoragesti_columnsetnull
	#define GET_CmpCAAStoragesti_columnsetnull  ERR_OK
	#define CAL_CmpCAAStoragesti_columnsetnull  sti_columnsetnull
	#define CHK_CmpCAAStoragesti_columnsetnull  TRUE
	#define EXP_CmpCAAStoragesti_columnsetnull  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetnull", (RTS_UINTPTR)sti_columnsetnull, 1, RTSITF_GET_SIGNATURE(0, 0x9543CD3B), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columnsetnull
	#define EXT_sti_columnsetnull
	#define GET_sti_columnsetnull(fl)  CAL_CMGETAPI( "sti_columnsetnull" ) 
	#define CAL_sti_columnsetnull  sti_columnsetnull
	#define CHK_sti_columnsetnull  TRUE
	#define EXP_sti_columnsetnull  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetnull", (RTS_UINTPTR)sti_columnsetnull, 1, RTSITF_GET_SIGNATURE(0, 0x9543CD3B), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columnsetnull  PFSTI_COLUMNSETNULL_IEC pfsti_columnsetnull;
	#define EXT_sti_columnsetnull  extern PFSTI_COLUMNSETNULL_IEC pfsti_columnsetnull;
	#define GET_sti_columnsetnull(fl)  s_pfCMGetAPI2( "sti_columnsetnull", (RTS_VOID_FCTPTR *)&pfsti_columnsetnull, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x9543CD3B), 0x03050500)
	#define CAL_sti_columnsetnull  pfsti_columnsetnull
	#define CHK_sti_columnsetnull  (pfsti_columnsetnull != NULL)
	#define EXP_sti_columnsetnull   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetnull", (RTS_UINTPTR)sti_columnsetnull, 1, RTSITF_GET_SIGNATURE(0, 0x9543CD3B), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columnsetreal4(sti_columnsetreal4_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNSETREAL4_IEC) (sti_columnsetreal4_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNSETREAL4_NOTIMPLEMENTED)
	#define USE_sti_columnsetreal4
	#define EXT_sti_columnsetreal4
	#define GET_sti_columnsetreal4(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columnsetreal4(p0) 
	#define CHK_sti_columnsetreal4  FALSE
	#define EXP_sti_columnsetreal4  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columnsetreal4
	#define EXT_sti_columnsetreal4
	#define GET_sti_columnsetreal4(fl)  CAL_CMGETAPI( "sti_columnsetreal4" ) 
	#define CAL_sti_columnsetreal4  sti_columnsetreal4
	#define CHK_sti_columnsetreal4  TRUE
	#define EXP_sti_columnsetreal4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetreal4", (RTS_UINTPTR)sti_columnsetreal4, 1, RTSITF_GET_SIGNATURE(0, 0x779801CB), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columnsetreal4
	#define EXT_sti_columnsetreal4
	#define GET_sti_columnsetreal4(fl)  CAL_CMGETAPI( "sti_columnsetreal4" ) 
	#define CAL_sti_columnsetreal4  sti_columnsetreal4
	#define CHK_sti_columnsetreal4  TRUE
	#define EXP_sti_columnsetreal4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetreal4", (RTS_UINTPTR)sti_columnsetreal4, 1, RTSITF_GET_SIGNATURE(0, 0x779801CB), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columnsetreal4
	#define EXT_CmpCAAStoragesti_columnsetreal4
	#define GET_CmpCAAStoragesti_columnsetreal4  ERR_OK
	#define CAL_CmpCAAStoragesti_columnsetreal4  sti_columnsetreal4
	#define CHK_CmpCAAStoragesti_columnsetreal4  TRUE
	#define EXP_CmpCAAStoragesti_columnsetreal4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetreal4", (RTS_UINTPTR)sti_columnsetreal4, 1, RTSITF_GET_SIGNATURE(0, 0x779801CB), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columnsetreal4
	#define EXT_sti_columnsetreal4
	#define GET_sti_columnsetreal4(fl)  CAL_CMGETAPI( "sti_columnsetreal4" ) 
	#define CAL_sti_columnsetreal4  sti_columnsetreal4
	#define CHK_sti_columnsetreal4  TRUE
	#define EXP_sti_columnsetreal4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetreal4", (RTS_UINTPTR)sti_columnsetreal4, 1, RTSITF_GET_SIGNATURE(0, 0x779801CB), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columnsetreal4  PFSTI_COLUMNSETREAL4_IEC pfsti_columnsetreal4;
	#define EXT_sti_columnsetreal4  extern PFSTI_COLUMNSETREAL4_IEC pfsti_columnsetreal4;
	#define GET_sti_columnsetreal4(fl)  s_pfCMGetAPI2( "sti_columnsetreal4", (RTS_VOID_FCTPTR *)&pfsti_columnsetreal4, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x779801CB), 0x03050500)
	#define CAL_sti_columnsetreal4  pfsti_columnsetreal4
	#define CHK_sti_columnsetreal4  (pfsti_columnsetreal4 != NULL)
	#define EXP_sti_columnsetreal4   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetreal4", (RTS_UINTPTR)sti_columnsetreal4, 1, RTSITF_GET_SIGNATURE(0, 0x779801CB), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columnsetreal8(sti_columnsetreal8_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNSETREAL8_IEC) (sti_columnsetreal8_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNSETREAL8_NOTIMPLEMENTED)
	#define USE_sti_columnsetreal8
	#define EXT_sti_columnsetreal8
	#define GET_sti_columnsetreal8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columnsetreal8(p0) 
	#define CHK_sti_columnsetreal8  FALSE
	#define EXP_sti_columnsetreal8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columnsetreal8
	#define EXT_sti_columnsetreal8
	#define GET_sti_columnsetreal8(fl)  CAL_CMGETAPI( "sti_columnsetreal8" ) 
	#define CAL_sti_columnsetreal8  sti_columnsetreal8
	#define CHK_sti_columnsetreal8  TRUE
	#define EXP_sti_columnsetreal8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetreal8", (RTS_UINTPTR)sti_columnsetreal8, 1, RTSITF_GET_SIGNATURE(0, 0xAB73562E), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columnsetreal8
	#define EXT_sti_columnsetreal8
	#define GET_sti_columnsetreal8(fl)  CAL_CMGETAPI( "sti_columnsetreal8" ) 
	#define CAL_sti_columnsetreal8  sti_columnsetreal8
	#define CHK_sti_columnsetreal8  TRUE
	#define EXP_sti_columnsetreal8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetreal8", (RTS_UINTPTR)sti_columnsetreal8, 1, RTSITF_GET_SIGNATURE(0, 0xAB73562E), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columnsetreal8
	#define EXT_CmpCAAStoragesti_columnsetreal8
	#define GET_CmpCAAStoragesti_columnsetreal8  ERR_OK
	#define CAL_CmpCAAStoragesti_columnsetreal8  sti_columnsetreal8
	#define CHK_CmpCAAStoragesti_columnsetreal8  TRUE
	#define EXP_CmpCAAStoragesti_columnsetreal8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetreal8", (RTS_UINTPTR)sti_columnsetreal8, 1, RTSITF_GET_SIGNATURE(0, 0xAB73562E), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columnsetreal8
	#define EXT_sti_columnsetreal8
	#define GET_sti_columnsetreal8(fl)  CAL_CMGETAPI( "sti_columnsetreal8" ) 
	#define CAL_sti_columnsetreal8  sti_columnsetreal8
	#define CHK_sti_columnsetreal8  TRUE
	#define EXP_sti_columnsetreal8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetreal8", (RTS_UINTPTR)sti_columnsetreal8, 1, RTSITF_GET_SIGNATURE(0, 0xAB73562E), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columnsetreal8  PFSTI_COLUMNSETREAL8_IEC pfsti_columnsetreal8;
	#define EXT_sti_columnsetreal8  extern PFSTI_COLUMNSETREAL8_IEC pfsti_columnsetreal8;
	#define GET_sti_columnsetreal8(fl)  s_pfCMGetAPI2( "sti_columnsetreal8", (RTS_VOID_FCTPTR *)&pfsti_columnsetreal8, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xAB73562E), 0x03050500)
	#define CAL_sti_columnsetreal8  pfsti_columnsetreal8
	#define CHK_sti_columnsetreal8  (pfsti_columnsetreal8 != NULL)
	#define EXP_sti_columnsetreal8   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsetreal8", (RTS_UINTPTR)sti_columnsetreal8, 1, RTSITF_GET_SIGNATURE(0, 0xAB73562E), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columnsettext(sti_columnsettext_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNSETTEXT_IEC) (sti_columnsettext_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNSETTEXT_NOTIMPLEMENTED)
	#define USE_sti_columnsettext
	#define EXT_sti_columnsettext
	#define GET_sti_columnsettext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columnsettext(p0) 
	#define CHK_sti_columnsettext  FALSE
	#define EXP_sti_columnsettext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columnsettext
	#define EXT_sti_columnsettext
	#define GET_sti_columnsettext(fl)  CAL_CMGETAPI( "sti_columnsettext" ) 
	#define CAL_sti_columnsettext  sti_columnsettext
	#define CHK_sti_columnsettext  TRUE
	#define EXP_sti_columnsettext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsettext", (RTS_UINTPTR)sti_columnsettext, 1, RTSITF_GET_SIGNATURE(0, 0xCEED85C7), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columnsettext
	#define EXT_sti_columnsettext
	#define GET_sti_columnsettext(fl)  CAL_CMGETAPI( "sti_columnsettext" ) 
	#define CAL_sti_columnsettext  sti_columnsettext
	#define CHK_sti_columnsettext  TRUE
	#define EXP_sti_columnsettext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsettext", (RTS_UINTPTR)sti_columnsettext, 1, RTSITF_GET_SIGNATURE(0, 0xCEED85C7), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columnsettext
	#define EXT_CmpCAAStoragesti_columnsettext
	#define GET_CmpCAAStoragesti_columnsettext  ERR_OK
	#define CAL_CmpCAAStoragesti_columnsettext  sti_columnsettext
	#define CHK_CmpCAAStoragesti_columnsettext  TRUE
	#define EXP_CmpCAAStoragesti_columnsettext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsettext", (RTS_UINTPTR)sti_columnsettext, 1, RTSITF_GET_SIGNATURE(0, 0xCEED85C7), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columnsettext
	#define EXT_sti_columnsettext
	#define GET_sti_columnsettext(fl)  CAL_CMGETAPI( "sti_columnsettext" ) 
	#define CAL_sti_columnsettext  sti_columnsettext
	#define CHK_sti_columnsettext  TRUE
	#define EXP_sti_columnsettext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsettext", (RTS_UINTPTR)sti_columnsettext, 1, RTSITF_GET_SIGNATURE(0, 0xCEED85C7), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columnsettext  PFSTI_COLUMNSETTEXT_IEC pfsti_columnsettext;
	#define EXT_sti_columnsettext  extern PFSTI_COLUMNSETTEXT_IEC pfsti_columnsettext;
	#define GET_sti_columnsettext(fl)  s_pfCMGetAPI2( "sti_columnsettext", (RTS_VOID_FCTPTR *)&pfsti_columnsettext, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xCEED85C7), 0x03050500)
	#define CAL_sti_columnsettext  pfsti_columnsettext
	#define CHK_sti_columnsettext  (pfsti_columnsettext != NULL)
	#define EXP_sti_columnsettext   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnsettext", (RTS_UINTPTR)sti_columnsettext, 1, RTSITF_GET_SIGNATURE(0, 0xCEED85C7), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columnupdateblob(sti_columnupdateblob_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNUPDATEBLOB_IEC) (sti_columnupdateblob_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNUPDATEBLOB_NOTIMPLEMENTED)
	#define USE_sti_columnupdateblob
	#define EXT_sti_columnupdateblob
	#define GET_sti_columnupdateblob(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columnupdateblob(p0) 
	#define CHK_sti_columnupdateblob  FALSE
	#define EXP_sti_columnupdateblob  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columnupdateblob
	#define EXT_sti_columnupdateblob
	#define GET_sti_columnupdateblob(fl)  CAL_CMGETAPI( "sti_columnupdateblob" ) 
	#define CAL_sti_columnupdateblob  sti_columnupdateblob
	#define CHK_sti_columnupdateblob  TRUE
	#define EXP_sti_columnupdateblob  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateblob", (RTS_UINTPTR)sti_columnupdateblob, 1, RTSITF_GET_SIGNATURE(0, 0xD0C54666), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columnupdateblob
	#define EXT_sti_columnupdateblob
	#define GET_sti_columnupdateblob(fl)  CAL_CMGETAPI( "sti_columnupdateblob" ) 
	#define CAL_sti_columnupdateblob  sti_columnupdateblob
	#define CHK_sti_columnupdateblob  TRUE
	#define EXP_sti_columnupdateblob  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateblob", (RTS_UINTPTR)sti_columnupdateblob, 1, RTSITF_GET_SIGNATURE(0, 0xD0C54666), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columnupdateblob
	#define EXT_CmpCAAStoragesti_columnupdateblob
	#define GET_CmpCAAStoragesti_columnupdateblob  ERR_OK
	#define CAL_CmpCAAStoragesti_columnupdateblob  sti_columnupdateblob
	#define CHK_CmpCAAStoragesti_columnupdateblob  TRUE
	#define EXP_CmpCAAStoragesti_columnupdateblob  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateblob", (RTS_UINTPTR)sti_columnupdateblob, 1, RTSITF_GET_SIGNATURE(0, 0xD0C54666), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columnupdateblob
	#define EXT_sti_columnupdateblob
	#define GET_sti_columnupdateblob(fl)  CAL_CMGETAPI( "sti_columnupdateblob" ) 
	#define CAL_sti_columnupdateblob  sti_columnupdateblob
	#define CHK_sti_columnupdateblob  TRUE
	#define EXP_sti_columnupdateblob  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateblob", (RTS_UINTPTR)sti_columnupdateblob, 1, RTSITF_GET_SIGNATURE(0, 0xD0C54666), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columnupdateblob  PFSTI_COLUMNUPDATEBLOB_IEC pfsti_columnupdateblob;
	#define EXT_sti_columnupdateblob  extern PFSTI_COLUMNUPDATEBLOB_IEC pfsti_columnupdateblob;
	#define GET_sti_columnupdateblob(fl)  s_pfCMGetAPI2( "sti_columnupdateblob", (RTS_VOID_FCTPTR *)&pfsti_columnupdateblob, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xD0C54666), 0x03050500)
	#define CAL_sti_columnupdateblob  pfsti_columnupdateblob
	#define CHK_sti_columnupdateblob  (pfsti_columnupdateblob != NULL)
	#define EXP_sti_columnupdateblob   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateblob", (RTS_UINTPTR)sti_columnupdateblob, 1, RTSITF_GET_SIGNATURE(0, 0xD0C54666), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columnupdateint16(sti_columnupdateint16_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNUPDATEINT16_IEC) (sti_columnupdateint16_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNUPDATEINT16_NOTIMPLEMENTED)
	#define USE_sti_columnupdateint16
	#define EXT_sti_columnupdateint16
	#define GET_sti_columnupdateint16(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columnupdateint16(p0) 
	#define CHK_sti_columnupdateint16  FALSE
	#define EXP_sti_columnupdateint16  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columnupdateint16
	#define EXT_sti_columnupdateint16
	#define GET_sti_columnupdateint16(fl)  CAL_CMGETAPI( "sti_columnupdateint16" ) 
	#define CAL_sti_columnupdateint16  sti_columnupdateint16
	#define CHK_sti_columnupdateint16  TRUE
	#define EXP_sti_columnupdateint16  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateint16", (RTS_UINTPTR)sti_columnupdateint16, 1, RTSITF_GET_SIGNATURE(0, 0x8AA90839), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columnupdateint16
	#define EXT_sti_columnupdateint16
	#define GET_sti_columnupdateint16(fl)  CAL_CMGETAPI( "sti_columnupdateint16" ) 
	#define CAL_sti_columnupdateint16  sti_columnupdateint16
	#define CHK_sti_columnupdateint16  TRUE
	#define EXP_sti_columnupdateint16  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateint16", (RTS_UINTPTR)sti_columnupdateint16, 1, RTSITF_GET_SIGNATURE(0, 0x8AA90839), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columnupdateint16
	#define EXT_CmpCAAStoragesti_columnupdateint16
	#define GET_CmpCAAStoragesti_columnupdateint16  ERR_OK
	#define CAL_CmpCAAStoragesti_columnupdateint16  sti_columnupdateint16
	#define CHK_CmpCAAStoragesti_columnupdateint16  TRUE
	#define EXP_CmpCAAStoragesti_columnupdateint16  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateint16", (RTS_UINTPTR)sti_columnupdateint16, 1, RTSITF_GET_SIGNATURE(0, 0x8AA90839), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columnupdateint16
	#define EXT_sti_columnupdateint16
	#define GET_sti_columnupdateint16(fl)  CAL_CMGETAPI( "sti_columnupdateint16" ) 
	#define CAL_sti_columnupdateint16  sti_columnupdateint16
	#define CHK_sti_columnupdateint16  TRUE
	#define EXP_sti_columnupdateint16  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateint16", (RTS_UINTPTR)sti_columnupdateint16, 1, RTSITF_GET_SIGNATURE(0, 0x8AA90839), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columnupdateint16  PFSTI_COLUMNUPDATEINT16_IEC pfsti_columnupdateint16;
	#define EXT_sti_columnupdateint16  extern PFSTI_COLUMNUPDATEINT16_IEC pfsti_columnupdateint16;
	#define GET_sti_columnupdateint16(fl)  s_pfCMGetAPI2( "sti_columnupdateint16", (RTS_VOID_FCTPTR *)&pfsti_columnupdateint16, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x8AA90839), 0x03050500)
	#define CAL_sti_columnupdateint16  pfsti_columnupdateint16
	#define CHK_sti_columnupdateint16  (pfsti_columnupdateint16 != NULL)
	#define EXP_sti_columnupdateint16   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateint16", (RTS_UINTPTR)sti_columnupdateint16, 1, RTSITF_GET_SIGNATURE(0, 0x8AA90839), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columnupdateint32(sti_columnupdateint32_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNUPDATEINT32_IEC) (sti_columnupdateint32_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNUPDATEINT32_NOTIMPLEMENTED)
	#define USE_sti_columnupdateint32
	#define EXT_sti_columnupdateint32
	#define GET_sti_columnupdateint32(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columnupdateint32(p0) 
	#define CHK_sti_columnupdateint32  FALSE
	#define EXP_sti_columnupdateint32  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columnupdateint32
	#define EXT_sti_columnupdateint32
	#define GET_sti_columnupdateint32(fl)  CAL_CMGETAPI( "sti_columnupdateint32" ) 
	#define CAL_sti_columnupdateint32  sti_columnupdateint32
	#define CHK_sti_columnupdateint32  TRUE
	#define EXP_sti_columnupdateint32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateint32", (RTS_UINTPTR)sti_columnupdateint32, 1, RTSITF_GET_SIGNATURE(0, 0xAAC20335), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columnupdateint32
	#define EXT_sti_columnupdateint32
	#define GET_sti_columnupdateint32(fl)  CAL_CMGETAPI( "sti_columnupdateint32" ) 
	#define CAL_sti_columnupdateint32  sti_columnupdateint32
	#define CHK_sti_columnupdateint32  TRUE
	#define EXP_sti_columnupdateint32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateint32", (RTS_UINTPTR)sti_columnupdateint32, 1, RTSITF_GET_SIGNATURE(0, 0xAAC20335), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columnupdateint32
	#define EXT_CmpCAAStoragesti_columnupdateint32
	#define GET_CmpCAAStoragesti_columnupdateint32  ERR_OK
	#define CAL_CmpCAAStoragesti_columnupdateint32  sti_columnupdateint32
	#define CHK_CmpCAAStoragesti_columnupdateint32  TRUE
	#define EXP_CmpCAAStoragesti_columnupdateint32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateint32", (RTS_UINTPTR)sti_columnupdateint32, 1, RTSITF_GET_SIGNATURE(0, 0xAAC20335), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columnupdateint32
	#define EXT_sti_columnupdateint32
	#define GET_sti_columnupdateint32(fl)  CAL_CMGETAPI( "sti_columnupdateint32" ) 
	#define CAL_sti_columnupdateint32  sti_columnupdateint32
	#define CHK_sti_columnupdateint32  TRUE
	#define EXP_sti_columnupdateint32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateint32", (RTS_UINTPTR)sti_columnupdateint32, 1, RTSITF_GET_SIGNATURE(0, 0xAAC20335), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columnupdateint32  PFSTI_COLUMNUPDATEINT32_IEC pfsti_columnupdateint32;
	#define EXT_sti_columnupdateint32  extern PFSTI_COLUMNUPDATEINT32_IEC pfsti_columnupdateint32;
	#define GET_sti_columnupdateint32(fl)  s_pfCMGetAPI2( "sti_columnupdateint32", (RTS_VOID_FCTPTR *)&pfsti_columnupdateint32, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xAAC20335), 0x03050500)
	#define CAL_sti_columnupdateint32  pfsti_columnupdateint32
	#define CHK_sti_columnupdateint32  (pfsti_columnupdateint32 != NULL)
	#define EXP_sti_columnupdateint32   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateint32", (RTS_UINTPTR)sti_columnupdateint32, 1, RTSITF_GET_SIGNATURE(0, 0xAAC20335), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columnupdateint64(sti_columnupdateint64_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNUPDATEINT64_IEC) (sti_columnupdateint64_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNUPDATEINT64_NOTIMPLEMENTED)
	#define USE_sti_columnupdateint64
	#define EXT_sti_columnupdateint64
	#define GET_sti_columnupdateint64(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columnupdateint64(p0) 
	#define CHK_sti_columnupdateint64  FALSE
	#define EXP_sti_columnupdateint64  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columnupdateint64
	#define EXT_sti_columnupdateint64
	#define GET_sti_columnupdateint64(fl)  CAL_CMGETAPI( "sti_columnupdateint64" ) 
	#define CAL_sti_columnupdateint64  sti_columnupdateint64
	#define CHK_sti_columnupdateint64  TRUE
	#define EXP_sti_columnupdateint64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateint64", (RTS_UINTPTR)sti_columnupdateint64, 1, RTSITF_GET_SIGNATURE(0, 0xC95AE06D), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columnupdateint64
	#define EXT_sti_columnupdateint64
	#define GET_sti_columnupdateint64(fl)  CAL_CMGETAPI( "sti_columnupdateint64" ) 
	#define CAL_sti_columnupdateint64  sti_columnupdateint64
	#define CHK_sti_columnupdateint64  TRUE
	#define EXP_sti_columnupdateint64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateint64", (RTS_UINTPTR)sti_columnupdateint64, 1, RTSITF_GET_SIGNATURE(0, 0xC95AE06D), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columnupdateint64
	#define EXT_CmpCAAStoragesti_columnupdateint64
	#define GET_CmpCAAStoragesti_columnupdateint64  ERR_OK
	#define CAL_CmpCAAStoragesti_columnupdateint64  sti_columnupdateint64
	#define CHK_CmpCAAStoragesti_columnupdateint64  TRUE
	#define EXP_CmpCAAStoragesti_columnupdateint64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateint64", (RTS_UINTPTR)sti_columnupdateint64, 1, RTSITF_GET_SIGNATURE(0, 0xC95AE06D), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columnupdateint64
	#define EXT_sti_columnupdateint64
	#define GET_sti_columnupdateint64(fl)  CAL_CMGETAPI( "sti_columnupdateint64" ) 
	#define CAL_sti_columnupdateint64  sti_columnupdateint64
	#define CHK_sti_columnupdateint64  TRUE
	#define EXP_sti_columnupdateint64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateint64", (RTS_UINTPTR)sti_columnupdateint64, 1, RTSITF_GET_SIGNATURE(0, 0xC95AE06D), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columnupdateint64  PFSTI_COLUMNUPDATEINT64_IEC pfsti_columnupdateint64;
	#define EXT_sti_columnupdateint64  extern PFSTI_COLUMNUPDATEINT64_IEC pfsti_columnupdateint64;
	#define GET_sti_columnupdateint64(fl)  s_pfCMGetAPI2( "sti_columnupdateint64", (RTS_VOID_FCTPTR *)&pfsti_columnupdateint64, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xC95AE06D), 0x03050500)
	#define CAL_sti_columnupdateint64  pfsti_columnupdateint64
	#define CHK_sti_columnupdateint64  (pfsti_columnupdateint64 != NULL)
	#define EXP_sti_columnupdateint64   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateint64", (RTS_UINTPTR)sti_columnupdateint64, 1, RTSITF_GET_SIGNATURE(0, 0xC95AE06D), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columnupdateint8(sti_columnupdateint8_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNUPDATEINT8_IEC) (sti_columnupdateint8_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNUPDATEINT8_NOTIMPLEMENTED)
	#define USE_sti_columnupdateint8
	#define EXT_sti_columnupdateint8
	#define GET_sti_columnupdateint8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columnupdateint8(p0) 
	#define CHK_sti_columnupdateint8  FALSE
	#define EXP_sti_columnupdateint8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columnupdateint8
	#define EXT_sti_columnupdateint8
	#define GET_sti_columnupdateint8(fl)  CAL_CMGETAPI( "sti_columnupdateint8" ) 
	#define CAL_sti_columnupdateint8  sti_columnupdateint8
	#define CHK_sti_columnupdateint8  TRUE
	#define EXP_sti_columnupdateint8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateint8", (RTS_UINTPTR)sti_columnupdateint8, 1, RTSITF_GET_SIGNATURE(0, 0xDD539E10), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columnupdateint8
	#define EXT_sti_columnupdateint8
	#define GET_sti_columnupdateint8(fl)  CAL_CMGETAPI( "sti_columnupdateint8" ) 
	#define CAL_sti_columnupdateint8  sti_columnupdateint8
	#define CHK_sti_columnupdateint8  TRUE
	#define EXP_sti_columnupdateint8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateint8", (RTS_UINTPTR)sti_columnupdateint8, 1, RTSITF_GET_SIGNATURE(0, 0xDD539E10), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columnupdateint8
	#define EXT_CmpCAAStoragesti_columnupdateint8
	#define GET_CmpCAAStoragesti_columnupdateint8  ERR_OK
	#define CAL_CmpCAAStoragesti_columnupdateint8  sti_columnupdateint8
	#define CHK_CmpCAAStoragesti_columnupdateint8  TRUE
	#define EXP_CmpCAAStoragesti_columnupdateint8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateint8", (RTS_UINTPTR)sti_columnupdateint8, 1, RTSITF_GET_SIGNATURE(0, 0xDD539E10), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columnupdateint8
	#define EXT_sti_columnupdateint8
	#define GET_sti_columnupdateint8(fl)  CAL_CMGETAPI( "sti_columnupdateint8" ) 
	#define CAL_sti_columnupdateint8  sti_columnupdateint8
	#define CHK_sti_columnupdateint8  TRUE
	#define EXP_sti_columnupdateint8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateint8", (RTS_UINTPTR)sti_columnupdateint8, 1, RTSITF_GET_SIGNATURE(0, 0xDD539E10), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columnupdateint8  PFSTI_COLUMNUPDATEINT8_IEC pfsti_columnupdateint8;
	#define EXT_sti_columnupdateint8  extern PFSTI_COLUMNUPDATEINT8_IEC pfsti_columnupdateint8;
	#define GET_sti_columnupdateint8(fl)  s_pfCMGetAPI2( "sti_columnupdateint8", (RTS_VOID_FCTPTR *)&pfsti_columnupdateint8, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xDD539E10), 0x03050500)
	#define CAL_sti_columnupdateint8  pfsti_columnupdateint8
	#define CHK_sti_columnupdateint8  (pfsti_columnupdateint8 != NULL)
	#define EXP_sti_columnupdateint8   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdateint8", (RTS_UINTPTR)sti_columnupdateint8, 1, RTSITF_GET_SIGNATURE(0, 0xDD539E10), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columnupdatereal4(sti_columnupdatereal4_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNUPDATEREAL4_IEC) (sti_columnupdatereal4_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNUPDATEREAL4_NOTIMPLEMENTED)
	#define USE_sti_columnupdatereal4
	#define EXT_sti_columnupdatereal4
	#define GET_sti_columnupdatereal4(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columnupdatereal4(p0) 
	#define CHK_sti_columnupdatereal4  FALSE
	#define EXP_sti_columnupdatereal4  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columnupdatereal4
	#define EXT_sti_columnupdatereal4
	#define GET_sti_columnupdatereal4(fl)  CAL_CMGETAPI( "sti_columnupdatereal4" ) 
	#define CAL_sti_columnupdatereal4  sti_columnupdatereal4
	#define CHK_sti_columnupdatereal4  TRUE
	#define EXP_sti_columnupdatereal4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdatereal4", (RTS_UINTPTR)sti_columnupdatereal4, 1, RTSITF_GET_SIGNATURE(0, 0xCD7B75E2), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columnupdatereal4
	#define EXT_sti_columnupdatereal4
	#define GET_sti_columnupdatereal4(fl)  CAL_CMGETAPI( "sti_columnupdatereal4" ) 
	#define CAL_sti_columnupdatereal4  sti_columnupdatereal4
	#define CHK_sti_columnupdatereal4  TRUE
	#define EXP_sti_columnupdatereal4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdatereal4", (RTS_UINTPTR)sti_columnupdatereal4, 1, RTSITF_GET_SIGNATURE(0, 0xCD7B75E2), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columnupdatereal4
	#define EXT_CmpCAAStoragesti_columnupdatereal4
	#define GET_CmpCAAStoragesti_columnupdatereal4  ERR_OK
	#define CAL_CmpCAAStoragesti_columnupdatereal4  sti_columnupdatereal4
	#define CHK_CmpCAAStoragesti_columnupdatereal4  TRUE
	#define EXP_CmpCAAStoragesti_columnupdatereal4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdatereal4", (RTS_UINTPTR)sti_columnupdatereal4, 1, RTSITF_GET_SIGNATURE(0, 0xCD7B75E2), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columnupdatereal4
	#define EXT_sti_columnupdatereal4
	#define GET_sti_columnupdatereal4(fl)  CAL_CMGETAPI( "sti_columnupdatereal4" ) 
	#define CAL_sti_columnupdatereal4  sti_columnupdatereal4
	#define CHK_sti_columnupdatereal4  TRUE
	#define EXP_sti_columnupdatereal4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdatereal4", (RTS_UINTPTR)sti_columnupdatereal4, 1, RTSITF_GET_SIGNATURE(0, 0xCD7B75E2), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columnupdatereal4  PFSTI_COLUMNUPDATEREAL4_IEC pfsti_columnupdatereal4;
	#define EXT_sti_columnupdatereal4  extern PFSTI_COLUMNUPDATEREAL4_IEC pfsti_columnupdatereal4;
	#define GET_sti_columnupdatereal4(fl)  s_pfCMGetAPI2( "sti_columnupdatereal4", (RTS_VOID_FCTPTR *)&pfsti_columnupdatereal4, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xCD7B75E2), 0x03050500)
	#define CAL_sti_columnupdatereal4  pfsti_columnupdatereal4
	#define CHK_sti_columnupdatereal4  (pfsti_columnupdatereal4 != NULL)
	#define EXP_sti_columnupdatereal4   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdatereal4", (RTS_UINTPTR)sti_columnupdatereal4, 1, RTSITF_GET_SIGNATURE(0, 0xCD7B75E2), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columnupdatereal8(sti_columnupdatereal8_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNUPDATEREAL8_IEC) (sti_columnupdatereal8_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNUPDATEREAL8_NOTIMPLEMENTED)
	#define USE_sti_columnupdatereal8
	#define EXT_sti_columnupdatereal8
	#define GET_sti_columnupdatereal8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columnupdatereal8(p0) 
	#define CHK_sti_columnupdatereal8  FALSE
	#define EXP_sti_columnupdatereal8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columnupdatereal8
	#define EXT_sti_columnupdatereal8
	#define GET_sti_columnupdatereal8(fl)  CAL_CMGETAPI( "sti_columnupdatereal8" ) 
	#define CAL_sti_columnupdatereal8  sti_columnupdatereal8
	#define CHK_sti_columnupdatereal8  TRUE
	#define EXP_sti_columnupdatereal8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdatereal8", (RTS_UINTPTR)sti_columnupdatereal8, 1, RTSITF_GET_SIGNATURE(0, 0x1F53A007), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columnupdatereal8
	#define EXT_sti_columnupdatereal8
	#define GET_sti_columnupdatereal8(fl)  CAL_CMGETAPI( "sti_columnupdatereal8" ) 
	#define CAL_sti_columnupdatereal8  sti_columnupdatereal8
	#define CHK_sti_columnupdatereal8  TRUE
	#define EXP_sti_columnupdatereal8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdatereal8", (RTS_UINTPTR)sti_columnupdatereal8, 1, RTSITF_GET_SIGNATURE(0, 0x1F53A007), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columnupdatereal8
	#define EXT_CmpCAAStoragesti_columnupdatereal8
	#define GET_CmpCAAStoragesti_columnupdatereal8  ERR_OK
	#define CAL_CmpCAAStoragesti_columnupdatereal8  sti_columnupdatereal8
	#define CHK_CmpCAAStoragesti_columnupdatereal8  TRUE
	#define EXP_CmpCAAStoragesti_columnupdatereal8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdatereal8", (RTS_UINTPTR)sti_columnupdatereal8, 1, RTSITF_GET_SIGNATURE(0, 0x1F53A007), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columnupdatereal8
	#define EXT_sti_columnupdatereal8
	#define GET_sti_columnupdatereal8(fl)  CAL_CMGETAPI( "sti_columnupdatereal8" ) 
	#define CAL_sti_columnupdatereal8  sti_columnupdatereal8
	#define CHK_sti_columnupdatereal8  TRUE
	#define EXP_sti_columnupdatereal8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdatereal8", (RTS_UINTPTR)sti_columnupdatereal8, 1, RTSITF_GET_SIGNATURE(0, 0x1F53A007), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columnupdatereal8  PFSTI_COLUMNUPDATEREAL8_IEC pfsti_columnupdatereal8;
	#define EXT_sti_columnupdatereal8  extern PFSTI_COLUMNUPDATEREAL8_IEC pfsti_columnupdatereal8;
	#define GET_sti_columnupdatereal8(fl)  s_pfCMGetAPI2( "sti_columnupdatereal8", (RTS_VOID_FCTPTR *)&pfsti_columnupdatereal8, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x1F53A007), 0x03050500)
	#define CAL_sti_columnupdatereal8  pfsti_columnupdatereal8
	#define CHK_sti_columnupdatereal8  (pfsti_columnupdatereal8 != NULL)
	#define EXP_sti_columnupdatereal8   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdatereal8", (RTS_UINTPTR)sti_columnupdatereal8, 1, RTSITF_GET_SIGNATURE(0, 0x1F53A007), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_columnupdatetext(sti_columnupdatetext_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_COLUMNUPDATETEXT_IEC) (sti_columnupdatetext_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNUPDATETEXT_NOTIMPLEMENTED)
	#define USE_sti_columnupdatetext
	#define EXT_sti_columnupdatetext
	#define GET_sti_columnupdatetext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_columnupdatetext(p0) 
	#define CHK_sti_columnupdatetext  FALSE
	#define EXP_sti_columnupdatetext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_columnupdatetext
	#define EXT_sti_columnupdatetext
	#define GET_sti_columnupdatetext(fl)  CAL_CMGETAPI( "sti_columnupdatetext" ) 
	#define CAL_sti_columnupdatetext  sti_columnupdatetext
	#define CHK_sti_columnupdatetext  TRUE
	#define EXP_sti_columnupdatetext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdatetext", (RTS_UINTPTR)sti_columnupdatetext, 1, RTSITF_GET_SIGNATURE(0, 0x1E881E83), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_columnupdatetext
	#define EXT_sti_columnupdatetext
	#define GET_sti_columnupdatetext(fl)  CAL_CMGETAPI( "sti_columnupdatetext" ) 
	#define CAL_sti_columnupdatetext  sti_columnupdatetext
	#define CHK_sti_columnupdatetext  TRUE
	#define EXP_sti_columnupdatetext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdatetext", (RTS_UINTPTR)sti_columnupdatetext, 1, RTSITF_GET_SIGNATURE(0, 0x1E881E83), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_columnupdatetext
	#define EXT_CmpCAAStoragesti_columnupdatetext
	#define GET_CmpCAAStoragesti_columnupdatetext  ERR_OK
	#define CAL_CmpCAAStoragesti_columnupdatetext  sti_columnupdatetext
	#define CHK_CmpCAAStoragesti_columnupdatetext  TRUE
	#define EXP_CmpCAAStoragesti_columnupdatetext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdatetext", (RTS_UINTPTR)sti_columnupdatetext, 1, RTSITF_GET_SIGNATURE(0, 0x1E881E83), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_columnupdatetext
	#define EXT_sti_columnupdatetext
	#define GET_sti_columnupdatetext(fl)  CAL_CMGETAPI( "sti_columnupdatetext" ) 
	#define CAL_sti_columnupdatetext  sti_columnupdatetext
	#define CHK_sti_columnupdatetext  TRUE
	#define EXP_sti_columnupdatetext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdatetext", (RTS_UINTPTR)sti_columnupdatetext, 1, RTSITF_GET_SIGNATURE(0, 0x1E881E83), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_columnupdatetext  PFSTI_COLUMNUPDATETEXT_IEC pfsti_columnupdatetext;
	#define EXT_sti_columnupdatetext  extern PFSTI_COLUMNUPDATETEXT_IEC pfsti_columnupdatetext;
	#define GET_sti_columnupdatetext(fl)  s_pfCMGetAPI2( "sti_columnupdatetext", (RTS_VOID_FCTPTR *)&pfsti_columnupdatetext, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x1E881E83), 0x03050500)
	#define CAL_sti_columnupdatetext  pfsti_columnupdatetext
	#define CHK_sti_columnupdatetext  (pfsti_columnupdatetext != NULL)
	#define EXP_sti_columnupdatetext   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_columnupdatetext", (RTS_UINTPTR)sti_columnupdatetext, 1, RTSITF_GET_SIGNATURE(0, 0x1E881E83), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorclose_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_INT STI_CursorClose;		/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorclose_struct;

void CDECL CDECL_EXT sti_cursorclose(sti_cursorclose_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_CURSORCLOSE_IEC) (sti_cursorclose_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORCLOSE_NOTIMPLEMENTED)
	#define USE_sti_cursorclose
	#define EXT_sti_cursorclose
	#define GET_sti_cursorclose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_cursorclose(p0) 
	#define CHK_sti_cursorclose  FALSE
	#define EXP_sti_cursorclose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_cursorclose
	#define EXT_sti_cursorclose
	#define GET_sti_cursorclose(fl)  CAL_CMGETAPI( "sti_cursorclose" ) 
	#define CAL_sti_cursorclose  sti_cursorclose
	#define CHK_sti_cursorclose  TRUE
	#define EXP_sti_cursorclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorclose", (RTS_UINTPTR)sti_cursorclose, 1, RTSITF_GET_SIGNATURE(0, 0x2D38F773), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_cursorclose
	#define EXT_sti_cursorclose
	#define GET_sti_cursorclose(fl)  CAL_CMGETAPI( "sti_cursorclose" ) 
	#define CAL_sti_cursorclose  sti_cursorclose
	#define CHK_sti_cursorclose  TRUE
	#define EXP_sti_cursorclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorclose", (RTS_UINTPTR)sti_cursorclose, 1, RTSITF_GET_SIGNATURE(0, 0x2D38F773), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_cursorclose
	#define EXT_CmpCAAStoragesti_cursorclose
	#define GET_CmpCAAStoragesti_cursorclose  ERR_OK
	#define CAL_CmpCAAStoragesti_cursorclose  sti_cursorclose
	#define CHK_CmpCAAStoragesti_cursorclose  TRUE
	#define EXP_CmpCAAStoragesti_cursorclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorclose", (RTS_UINTPTR)sti_cursorclose, 1, RTSITF_GET_SIGNATURE(0, 0x2D38F773), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_cursorclose
	#define EXT_sti_cursorclose
	#define GET_sti_cursorclose(fl)  CAL_CMGETAPI( "sti_cursorclose" ) 
	#define CAL_sti_cursorclose  sti_cursorclose
	#define CHK_sti_cursorclose  TRUE
	#define EXP_sti_cursorclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorclose", (RTS_UINTPTR)sti_cursorclose, 1, RTSITF_GET_SIGNATURE(0, 0x2D38F773), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_cursorclose  PFSTI_CURSORCLOSE_IEC pfsti_cursorclose;
	#define EXT_sti_cursorclose  extern PFSTI_CURSORCLOSE_IEC pfsti_cursorclose;
	#define GET_sti_cursorclose(fl)  s_pfCMGetAPI2( "sti_cursorclose", (RTS_VOID_FCTPTR *)&pfsti_cursorclose, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x2D38F773), 0x03050500)
	#define CAL_sti_cursorclose  pfsti_cursorclose
	#define CHK_sti_cursorclose  (pfsti_cursorclose != NULL)
	#define EXP_sti_cursorclose   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorclose", (RTS_UINTPTR)sti_cursorclose, 1, RTSITF_GET_SIGNATURE(0, 0x2D38F773), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorgetcurrentrow_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_XWORD STI_CursorGetCurrentRow;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorgetcurrentrow_struct;

void CDECL CDECL_EXT sti_cursorgetcurrentrow(sti_cursorgetcurrentrow_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_CURSORGETCURRENTROW_IEC) (sti_cursorgetcurrentrow_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORGETCURRENTROW_NOTIMPLEMENTED)
	#define USE_sti_cursorgetcurrentrow
	#define EXT_sti_cursorgetcurrentrow
	#define GET_sti_cursorgetcurrentrow(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_cursorgetcurrentrow(p0) 
	#define CHK_sti_cursorgetcurrentrow  FALSE
	#define EXP_sti_cursorgetcurrentrow  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_cursorgetcurrentrow
	#define EXT_sti_cursorgetcurrentrow
	#define GET_sti_cursorgetcurrentrow(fl)  CAL_CMGETAPI( "sti_cursorgetcurrentrow" ) 
	#define CAL_sti_cursorgetcurrentrow  sti_cursorgetcurrentrow
	#define CHK_sti_cursorgetcurrentrow  TRUE
	#define EXP_sti_cursorgetcurrentrow  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorgetcurrentrow", (RTS_UINTPTR)sti_cursorgetcurrentrow, 1, RTSITF_GET_SIGNATURE(0, 0x4FE7BC05), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_cursorgetcurrentrow
	#define EXT_sti_cursorgetcurrentrow
	#define GET_sti_cursorgetcurrentrow(fl)  CAL_CMGETAPI( "sti_cursorgetcurrentrow" ) 
	#define CAL_sti_cursorgetcurrentrow  sti_cursorgetcurrentrow
	#define CHK_sti_cursorgetcurrentrow  TRUE
	#define EXP_sti_cursorgetcurrentrow  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorgetcurrentrow", (RTS_UINTPTR)sti_cursorgetcurrentrow, 1, RTSITF_GET_SIGNATURE(0, 0x4FE7BC05), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_cursorgetcurrentrow
	#define EXT_CmpCAAStoragesti_cursorgetcurrentrow
	#define GET_CmpCAAStoragesti_cursorgetcurrentrow  ERR_OK
	#define CAL_CmpCAAStoragesti_cursorgetcurrentrow  sti_cursorgetcurrentrow
	#define CHK_CmpCAAStoragesti_cursorgetcurrentrow  TRUE
	#define EXP_CmpCAAStoragesti_cursorgetcurrentrow  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorgetcurrentrow", (RTS_UINTPTR)sti_cursorgetcurrentrow, 1, RTSITF_GET_SIGNATURE(0, 0x4FE7BC05), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_cursorgetcurrentrow
	#define EXT_sti_cursorgetcurrentrow
	#define GET_sti_cursorgetcurrentrow(fl)  CAL_CMGETAPI( "sti_cursorgetcurrentrow" ) 
	#define CAL_sti_cursorgetcurrentrow  sti_cursorgetcurrentrow
	#define CHK_sti_cursorgetcurrentrow  TRUE
	#define EXP_sti_cursorgetcurrentrow  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorgetcurrentrow", (RTS_UINTPTR)sti_cursorgetcurrentrow, 1, RTSITF_GET_SIGNATURE(0, 0x4FE7BC05), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_cursorgetcurrentrow  PFSTI_CURSORGETCURRENTROW_IEC pfsti_cursorgetcurrentrow;
	#define EXT_sti_cursorgetcurrentrow  extern PFSTI_CURSORGETCURRENTROW_IEC pfsti_cursorgetcurrentrow;
	#define GET_sti_cursorgetcurrentrow(fl)  s_pfCMGetAPI2( "sti_cursorgetcurrentrow", (RTS_VOID_FCTPTR *)&pfsti_cursorgetcurrentrow, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x4FE7BC05), 0x03050500)
	#define CAL_sti_cursorgetcurrentrow  pfsti_cursorgetcurrentrow
	#define CHK_sti_cursorgetcurrentrow  (pfsti_cursorgetcurrentrow != NULL)
	#define EXP_sti_cursorgetcurrentrow   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorgetcurrentrow", (RTS_UINTPTR)sti_cursorgetcurrentrow, 1, RTSITF_GET_SIGNATURE(0, 0x4FE7BC05), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorgetindexid_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_DWORD STI_CursorGetIndexId;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorgetindexid_struct;

void CDECL CDECL_EXT sti_cursorgetindexid(sti_cursorgetindexid_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_CURSORGETINDEXID_IEC) (sti_cursorgetindexid_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORGETINDEXID_NOTIMPLEMENTED)
	#define USE_sti_cursorgetindexid
	#define EXT_sti_cursorgetindexid
	#define GET_sti_cursorgetindexid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_cursorgetindexid(p0) 
	#define CHK_sti_cursorgetindexid  FALSE
	#define EXP_sti_cursorgetindexid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_cursorgetindexid
	#define EXT_sti_cursorgetindexid
	#define GET_sti_cursorgetindexid(fl)  CAL_CMGETAPI( "sti_cursorgetindexid" ) 
	#define CAL_sti_cursorgetindexid  sti_cursorgetindexid
	#define CHK_sti_cursorgetindexid  TRUE
	#define EXP_sti_cursorgetindexid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorgetindexid", (RTS_UINTPTR)sti_cursorgetindexid, 1, RTSITF_GET_SIGNATURE(0, 0xB8F09C86), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_cursorgetindexid
	#define EXT_sti_cursorgetindexid
	#define GET_sti_cursorgetindexid(fl)  CAL_CMGETAPI( "sti_cursorgetindexid" ) 
	#define CAL_sti_cursorgetindexid  sti_cursorgetindexid
	#define CHK_sti_cursorgetindexid  TRUE
	#define EXP_sti_cursorgetindexid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorgetindexid", (RTS_UINTPTR)sti_cursorgetindexid, 1, RTSITF_GET_SIGNATURE(0, 0xB8F09C86), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_cursorgetindexid
	#define EXT_CmpCAAStoragesti_cursorgetindexid
	#define GET_CmpCAAStoragesti_cursorgetindexid  ERR_OK
	#define CAL_CmpCAAStoragesti_cursorgetindexid  sti_cursorgetindexid
	#define CHK_CmpCAAStoragesti_cursorgetindexid  TRUE
	#define EXP_CmpCAAStoragesti_cursorgetindexid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorgetindexid", (RTS_UINTPTR)sti_cursorgetindexid, 1, RTSITF_GET_SIGNATURE(0, 0xB8F09C86), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_cursorgetindexid
	#define EXT_sti_cursorgetindexid
	#define GET_sti_cursorgetindexid(fl)  CAL_CMGETAPI( "sti_cursorgetindexid" ) 
	#define CAL_sti_cursorgetindexid  sti_cursorgetindexid
	#define CHK_sti_cursorgetindexid  TRUE
	#define EXP_sti_cursorgetindexid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorgetindexid", (RTS_UINTPTR)sti_cursorgetindexid, 1, RTSITF_GET_SIGNATURE(0, 0xB8F09C86), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_cursorgetindexid  PFSTI_CURSORGETINDEXID_IEC pfsti_cursorgetindexid;
	#define EXT_sti_cursorgetindexid  extern PFSTI_CURSORGETINDEXID_IEC pfsti_cursorgetindexid;
	#define GET_sti_cursorgetindexid(fl)  s_pfCMGetAPI2( "sti_cursorgetindexid", (RTS_VOID_FCTPTR *)&pfsti_cursorgetindexid, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xB8F09C86), 0x03050500)
	#define CAL_sti_cursorgetindexid  pfsti_cursorgetindexid
	#define CHK_sti_cursorgetindexid  (pfsti_cursorgetindexid != NULL)
	#define EXP_sti_cursorgetindexid   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorgetindexid", (RTS_UINTPTR)sti_cursorgetindexid, 1, RTSITF_GET_SIGNATURE(0, 0xB8F09C86), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorgetstorage_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_XWORD STI_CursorGetStorage;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorgetstorage_struct;

void CDECL CDECL_EXT sti_cursorgetstorage(sti_cursorgetstorage_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_CURSORGETSTORAGE_IEC) (sti_cursorgetstorage_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORGETSTORAGE_NOTIMPLEMENTED)
	#define USE_sti_cursorgetstorage
	#define EXT_sti_cursorgetstorage
	#define GET_sti_cursorgetstorage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_cursorgetstorage(p0) 
	#define CHK_sti_cursorgetstorage  FALSE
	#define EXP_sti_cursorgetstorage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_cursorgetstorage
	#define EXT_sti_cursorgetstorage
	#define GET_sti_cursorgetstorage(fl)  CAL_CMGETAPI( "sti_cursorgetstorage" ) 
	#define CAL_sti_cursorgetstorage  sti_cursorgetstorage
	#define CHK_sti_cursorgetstorage  TRUE
	#define EXP_sti_cursorgetstorage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorgetstorage", (RTS_UINTPTR)sti_cursorgetstorage, 1, RTSITF_GET_SIGNATURE(0, 0x834990B6), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_cursorgetstorage
	#define EXT_sti_cursorgetstorage
	#define GET_sti_cursorgetstorage(fl)  CAL_CMGETAPI( "sti_cursorgetstorage" ) 
	#define CAL_sti_cursorgetstorage  sti_cursorgetstorage
	#define CHK_sti_cursorgetstorage  TRUE
	#define EXP_sti_cursorgetstorage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorgetstorage", (RTS_UINTPTR)sti_cursorgetstorage, 1, RTSITF_GET_SIGNATURE(0, 0x834990B6), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_cursorgetstorage
	#define EXT_CmpCAAStoragesti_cursorgetstorage
	#define GET_CmpCAAStoragesti_cursorgetstorage  ERR_OK
	#define CAL_CmpCAAStoragesti_cursorgetstorage  sti_cursorgetstorage
	#define CHK_CmpCAAStoragesti_cursorgetstorage  TRUE
	#define EXP_CmpCAAStoragesti_cursorgetstorage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorgetstorage", (RTS_UINTPTR)sti_cursorgetstorage, 1, RTSITF_GET_SIGNATURE(0, 0x834990B6), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_cursorgetstorage
	#define EXT_sti_cursorgetstorage
	#define GET_sti_cursorgetstorage(fl)  CAL_CMGETAPI( "sti_cursorgetstorage" ) 
	#define CAL_sti_cursorgetstorage  sti_cursorgetstorage
	#define CHK_sti_cursorgetstorage  TRUE
	#define EXP_sti_cursorgetstorage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorgetstorage", (RTS_UINTPTR)sti_cursorgetstorage, 1, RTSITF_GET_SIGNATURE(0, 0x834990B6), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_cursorgetstorage  PFSTI_CURSORGETSTORAGE_IEC pfsti_cursorgetstorage;
	#define EXT_sti_cursorgetstorage  extern PFSTI_CURSORGETSTORAGE_IEC pfsti_cursorgetstorage;
	#define GET_sti_cursorgetstorage(fl)  s_pfCMGetAPI2( "sti_cursorgetstorage", (RTS_VOID_FCTPTR *)&pfsti_cursorgetstorage, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x834990B6), 0x03050500)
	#define CAL_sti_cursorgetstorage  pfsti_cursorgetstorage
	#define CHK_sti_cursorgetstorage  (pfsti_cursorgetstorage != NULL)
	#define EXP_sti_cursorgetstorage   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorgetstorage", (RTS_UINTPTR)sti_cursorgetstorage, 1, RTSITF_GET_SIGNATURE(0, 0x834990B6), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorgettable_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_XWORD STI_CursorGetTable;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorgettable_struct;

void CDECL CDECL_EXT sti_cursorgettable(sti_cursorgettable_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_CURSORGETTABLE_IEC) (sti_cursorgettable_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORGETTABLE_NOTIMPLEMENTED)
	#define USE_sti_cursorgettable
	#define EXT_sti_cursorgettable
	#define GET_sti_cursorgettable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_cursorgettable(p0) 
	#define CHK_sti_cursorgettable  FALSE
	#define EXP_sti_cursorgettable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_cursorgettable
	#define EXT_sti_cursorgettable
	#define GET_sti_cursorgettable(fl)  CAL_CMGETAPI( "sti_cursorgettable" ) 
	#define CAL_sti_cursorgettable  sti_cursorgettable
	#define CHK_sti_cursorgettable  TRUE
	#define EXP_sti_cursorgettable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorgettable", (RTS_UINTPTR)sti_cursorgettable, 1, RTSITF_GET_SIGNATURE(0, 0xC67780F2), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_cursorgettable
	#define EXT_sti_cursorgettable
	#define GET_sti_cursorgettable(fl)  CAL_CMGETAPI( "sti_cursorgettable" ) 
	#define CAL_sti_cursorgettable  sti_cursorgettable
	#define CHK_sti_cursorgettable  TRUE
	#define EXP_sti_cursorgettable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorgettable", (RTS_UINTPTR)sti_cursorgettable, 1, RTSITF_GET_SIGNATURE(0, 0xC67780F2), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_cursorgettable
	#define EXT_CmpCAAStoragesti_cursorgettable
	#define GET_CmpCAAStoragesti_cursorgettable  ERR_OK
	#define CAL_CmpCAAStoragesti_cursorgettable  sti_cursorgettable
	#define CHK_CmpCAAStoragesti_cursorgettable  TRUE
	#define EXP_CmpCAAStoragesti_cursorgettable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorgettable", (RTS_UINTPTR)sti_cursorgettable, 1, RTSITF_GET_SIGNATURE(0, 0xC67780F2), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_cursorgettable
	#define EXT_sti_cursorgettable
	#define GET_sti_cursorgettable(fl)  CAL_CMGETAPI( "sti_cursorgettable" ) 
	#define CAL_sti_cursorgettable  sti_cursorgettable
	#define CHK_sti_cursorgettable  TRUE
	#define EXP_sti_cursorgettable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorgettable", (RTS_UINTPTR)sti_cursorgettable, 1, RTSITF_GET_SIGNATURE(0, 0xC67780F2), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_cursorgettable  PFSTI_CURSORGETTABLE_IEC pfsti_cursorgettable;
	#define EXT_sti_cursorgettable  extern PFSTI_CURSORGETTABLE_IEC pfsti_cursorgettable;
	#define GET_sti_cursorgettable(fl)  s_pfCMGetAPI2( "sti_cursorgettable", (RTS_VOID_FCTPTR *)&pfsti_cursorgettable, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xC67780F2), 0x03050500)
	#define CAL_sti_cursorgettable  pfsti_cursorgettable
	#define CHK_sti_cursorgettable  (pfsti_cursorgettable != NULL)
	#define EXP_sti_cursorgettable   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorgettable", (RTS_UINTPTR)sti_cursorgettable, 1, RTSITF_GET_SIGNATURE(0, 0xC67780F2), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorisreadonly_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_BOOL STI_CursorIsReadOnly;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorisreadonly_struct;

void CDECL CDECL_EXT sti_cursorisreadonly(sti_cursorisreadonly_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_CURSORISREADONLY_IEC) (sti_cursorisreadonly_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORISREADONLY_NOTIMPLEMENTED)
	#define USE_sti_cursorisreadonly
	#define EXT_sti_cursorisreadonly
	#define GET_sti_cursorisreadonly(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_cursorisreadonly(p0) 
	#define CHK_sti_cursorisreadonly  FALSE
	#define EXP_sti_cursorisreadonly  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_cursorisreadonly
	#define EXT_sti_cursorisreadonly
	#define GET_sti_cursorisreadonly(fl)  CAL_CMGETAPI( "sti_cursorisreadonly" ) 
	#define CAL_sti_cursorisreadonly  sti_cursorisreadonly
	#define CHK_sti_cursorisreadonly  TRUE
	#define EXP_sti_cursorisreadonly  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorisreadonly", (RTS_UINTPTR)sti_cursorisreadonly, 1, RTSITF_GET_SIGNATURE(0, 0xA79C96C4), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_cursorisreadonly
	#define EXT_sti_cursorisreadonly
	#define GET_sti_cursorisreadonly(fl)  CAL_CMGETAPI( "sti_cursorisreadonly" ) 
	#define CAL_sti_cursorisreadonly  sti_cursorisreadonly
	#define CHK_sti_cursorisreadonly  TRUE
	#define EXP_sti_cursorisreadonly  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorisreadonly", (RTS_UINTPTR)sti_cursorisreadonly, 1, RTSITF_GET_SIGNATURE(0, 0xA79C96C4), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_cursorisreadonly
	#define EXT_CmpCAAStoragesti_cursorisreadonly
	#define GET_CmpCAAStoragesti_cursorisreadonly  ERR_OK
	#define CAL_CmpCAAStoragesti_cursorisreadonly  sti_cursorisreadonly
	#define CHK_CmpCAAStoragesti_cursorisreadonly  TRUE
	#define EXP_CmpCAAStoragesti_cursorisreadonly  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorisreadonly", (RTS_UINTPTR)sti_cursorisreadonly, 1, RTSITF_GET_SIGNATURE(0, 0xA79C96C4), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_cursorisreadonly
	#define EXT_sti_cursorisreadonly
	#define GET_sti_cursorisreadonly(fl)  CAL_CMGETAPI( "sti_cursorisreadonly" ) 
	#define CAL_sti_cursorisreadonly  sti_cursorisreadonly
	#define CHK_sti_cursorisreadonly  TRUE
	#define EXP_sti_cursorisreadonly  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorisreadonly", (RTS_UINTPTR)sti_cursorisreadonly, 1, RTSITF_GET_SIGNATURE(0, 0xA79C96C4), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_cursorisreadonly  PFSTI_CURSORISREADONLY_IEC pfsti_cursorisreadonly;
	#define EXT_sti_cursorisreadonly  extern PFSTI_CURSORISREADONLY_IEC pfsti_cursorisreadonly;
	#define GET_sti_cursorisreadonly(fl)  s_pfCMGetAPI2( "sti_cursorisreadonly", (RTS_VOID_FCTPTR *)&pfsti_cursorisreadonly, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA79C96C4), 0x03050500)
	#define CAL_sti_cursorisreadonly  pfsti_cursorisreadonly
	#define CHK_sti_cursorisreadonly  (pfsti_cursorisreadonly != NULL)
	#define EXP_sti_cursorisreadonly   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorisreadonly", (RTS_UINTPTR)sti_cursorisreadonly, 1, RTSITF_GET_SIGNATURE(0, 0xA79C96C4), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursormove_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_INT eDirection;				/* VAR_INPUT, Enum: DIRECTION */
	RTS_IEC_INT STI_CursorMove;			/* VAR_OUTPUT, Enum: ERROR */
} sti_cursormove_struct;

void CDECL CDECL_EXT sti_cursormove(sti_cursormove_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_CURSORMOVE_IEC) (sti_cursormove_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORMOVE_NOTIMPLEMENTED)
	#define USE_sti_cursormove
	#define EXT_sti_cursormove
	#define GET_sti_cursormove(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_cursormove(p0) 
	#define CHK_sti_cursormove  FALSE
	#define EXP_sti_cursormove  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_cursormove
	#define EXT_sti_cursormove
	#define GET_sti_cursormove(fl)  CAL_CMGETAPI( "sti_cursormove" ) 
	#define CAL_sti_cursormove  sti_cursormove
	#define CHK_sti_cursormove  TRUE
	#define EXP_sti_cursormove  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursormove", (RTS_UINTPTR)sti_cursormove, 1, RTSITF_GET_SIGNATURE(0, 0x3BA769E7), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_cursormove
	#define EXT_sti_cursormove
	#define GET_sti_cursormove(fl)  CAL_CMGETAPI( "sti_cursormove" ) 
	#define CAL_sti_cursormove  sti_cursormove
	#define CHK_sti_cursormove  TRUE
	#define EXP_sti_cursormove  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursormove", (RTS_UINTPTR)sti_cursormove, 1, RTSITF_GET_SIGNATURE(0, 0x3BA769E7), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_cursormove
	#define EXT_CmpCAAStoragesti_cursormove
	#define GET_CmpCAAStoragesti_cursormove  ERR_OK
	#define CAL_CmpCAAStoragesti_cursormove  sti_cursormove
	#define CHK_CmpCAAStoragesti_cursormove  TRUE
	#define EXP_CmpCAAStoragesti_cursormove  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursormove", (RTS_UINTPTR)sti_cursormove, 1, RTSITF_GET_SIGNATURE(0, 0x3BA769E7), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_cursormove
	#define EXT_sti_cursormove
	#define GET_sti_cursormove(fl)  CAL_CMGETAPI( "sti_cursormove" ) 
	#define CAL_sti_cursormove  sti_cursormove
	#define CHK_sti_cursormove  TRUE
	#define EXP_sti_cursormove  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursormove", (RTS_UINTPTR)sti_cursormove, 1, RTSITF_GET_SIGNATURE(0, 0x3BA769E7), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_cursormove  PFSTI_CURSORMOVE_IEC pfsti_cursormove;
	#define EXT_sti_cursormove  extern PFSTI_CURSORMOVE_IEC pfsti_cursormove;
	#define GET_sti_cursormove(fl)  s_pfCMGetAPI2( "sti_cursormove", (RTS_VOID_FCTPTR *)&pfsti_cursormove, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x3BA769E7), 0x03050500)
	#define CAL_sti_cursormove  pfsti_cursormove
	#define CHK_sti_cursormove  (pfsti_cursormove != NULL)
	#define EXP_sti_cursormove   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursormove", (RTS_UINTPTR)sti_cursormove, 1, RTSITF_GET_SIGNATURE(0, 0x3BA769E7), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_cursoropen(sti_cursoropen_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_CURSOROPEN_IEC) (sti_cursoropen_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSOROPEN_NOTIMPLEMENTED)
	#define USE_sti_cursoropen
	#define EXT_sti_cursoropen
	#define GET_sti_cursoropen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_cursoropen(p0) 
	#define CHK_sti_cursoropen  FALSE
	#define EXP_sti_cursoropen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_cursoropen
	#define EXT_sti_cursoropen
	#define GET_sti_cursoropen(fl)  CAL_CMGETAPI( "sti_cursoropen" ) 
	#define CAL_sti_cursoropen  sti_cursoropen
	#define CHK_sti_cursoropen  TRUE
	#define EXP_sti_cursoropen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursoropen", (RTS_UINTPTR)sti_cursoropen, 1, RTSITF_GET_SIGNATURE(0, 0x69069981), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_cursoropen
	#define EXT_sti_cursoropen
	#define GET_sti_cursoropen(fl)  CAL_CMGETAPI( "sti_cursoropen" ) 
	#define CAL_sti_cursoropen  sti_cursoropen
	#define CHK_sti_cursoropen  TRUE
	#define EXP_sti_cursoropen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursoropen", (RTS_UINTPTR)sti_cursoropen, 1, RTSITF_GET_SIGNATURE(0, 0x69069981), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_cursoropen
	#define EXT_CmpCAAStoragesti_cursoropen
	#define GET_CmpCAAStoragesti_cursoropen  ERR_OK
	#define CAL_CmpCAAStoragesti_cursoropen  sti_cursoropen
	#define CHK_CmpCAAStoragesti_cursoropen  TRUE
	#define EXP_CmpCAAStoragesti_cursoropen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursoropen", (RTS_UINTPTR)sti_cursoropen, 1, RTSITF_GET_SIGNATURE(0, 0x69069981), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_cursoropen
	#define EXT_sti_cursoropen
	#define GET_sti_cursoropen(fl)  CAL_CMGETAPI( "sti_cursoropen" ) 
	#define CAL_sti_cursoropen  sti_cursoropen
	#define CHK_sti_cursoropen  TRUE
	#define EXP_sti_cursoropen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursoropen", (RTS_UINTPTR)sti_cursoropen, 1, RTSITF_GET_SIGNATURE(0, 0x69069981), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_cursoropen  PFSTI_CURSOROPEN_IEC pfsti_cursoropen;
	#define EXT_sti_cursoropen  extern PFSTI_CURSOROPEN_IEC pfsti_cursoropen;
	#define GET_sti_cursoropen(fl)  s_pfCMGetAPI2( "sti_cursoropen", (RTS_VOID_FCTPTR *)&pfsti_cursoropen, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x69069981), 0x03050500)
	#define CAL_sti_cursoropen  pfsti_cursoropen
	#define CHK_sti_cursoropen  (pfsti_cursoropen != NULL)
	#define EXP_sti_cursoropen   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursoropen", (RTS_UINTPTR)sti_cursoropen, 1, RTSITF_GET_SIGNATURE(0, 0x69069981), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorsearchint16_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_INT iValue;					/* VAR_INPUT */	
	RTS_IEC_INT STI_CursorSearchINT16;	/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorsearchint16_struct;

void CDECL CDECL_EXT sti_cursorsearchint16(sti_cursorsearchint16_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_CURSORSEARCHINT16_IEC) (sti_cursorsearchint16_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORSEARCHINT16_NOTIMPLEMENTED)
	#define USE_sti_cursorsearchint16
	#define EXT_sti_cursorsearchint16
	#define GET_sti_cursorsearchint16(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_cursorsearchint16(p0) 
	#define CHK_sti_cursorsearchint16  FALSE
	#define EXP_sti_cursorsearchint16  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_cursorsearchint16
	#define EXT_sti_cursorsearchint16
	#define GET_sti_cursorsearchint16(fl)  CAL_CMGETAPI( "sti_cursorsearchint16" ) 
	#define CAL_sti_cursorsearchint16  sti_cursorsearchint16
	#define CHK_sti_cursorsearchint16  TRUE
	#define EXP_sti_cursorsearchint16  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchint16", (RTS_UINTPTR)sti_cursorsearchint16, 1, RTSITF_GET_SIGNATURE(0, 0x51EF5860), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_cursorsearchint16
	#define EXT_sti_cursorsearchint16
	#define GET_sti_cursorsearchint16(fl)  CAL_CMGETAPI( "sti_cursorsearchint16" ) 
	#define CAL_sti_cursorsearchint16  sti_cursorsearchint16
	#define CHK_sti_cursorsearchint16  TRUE
	#define EXP_sti_cursorsearchint16  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchint16", (RTS_UINTPTR)sti_cursorsearchint16, 1, RTSITF_GET_SIGNATURE(0, 0x51EF5860), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_cursorsearchint16
	#define EXT_CmpCAAStoragesti_cursorsearchint16
	#define GET_CmpCAAStoragesti_cursorsearchint16  ERR_OK
	#define CAL_CmpCAAStoragesti_cursorsearchint16  sti_cursorsearchint16
	#define CHK_CmpCAAStoragesti_cursorsearchint16  TRUE
	#define EXP_CmpCAAStoragesti_cursorsearchint16  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchint16", (RTS_UINTPTR)sti_cursorsearchint16, 1, RTSITF_GET_SIGNATURE(0, 0x51EF5860), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_cursorsearchint16
	#define EXT_sti_cursorsearchint16
	#define GET_sti_cursorsearchint16(fl)  CAL_CMGETAPI( "sti_cursorsearchint16" ) 
	#define CAL_sti_cursorsearchint16  sti_cursorsearchint16
	#define CHK_sti_cursorsearchint16  TRUE
	#define EXP_sti_cursorsearchint16  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchint16", (RTS_UINTPTR)sti_cursorsearchint16, 1, RTSITF_GET_SIGNATURE(0, 0x51EF5860), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_cursorsearchint16  PFSTI_CURSORSEARCHINT16_IEC pfsti_cursorsearchint16;
	#define EXT_sti_cursorsearchint16  extern PFSTI_CURSORSEARCHINT16_IEC pfsti_cursorsearchint16;
	#define GET_sti_cursorsearchint16(fl)  s_pfCMGetAPI2( "sti_cursorsearchint16", (RTS_VOID_FCTPTR *)&pfsti_cursorsearchint16, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x51EF5860), 0x03050500)
	#define CAL_sti_cursorsearchint16  pfsti_cursorsearchint16
	#define CHK_sti_cursorsearchint16  (pfsti_cursorsearchint16 != NULL)
	#define EXP_sti_cursorsearchint16   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchint16", (RTS_UINTPTR)sti_cursorsearchint16, 1, RTSITF_GET_SIGNATURE(0, 0x51EF5860), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorsearchint32_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_DINT diValue;				/* VAR_INPUT */	
	RTS_IEC_INT STI_CursorSearchINT32;	/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorsearchint32_struct;

void CDECL CDECL_EXT sti_cursorsearchint32(sti_cursorsearchint32_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_CURSORSEARCHINT32_IEC) (sti_cursorsearchint32_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORSEARCHINT32_NOTIMPLEMENTED)
	#define USE_sti_cursorsearchint32
	#define EXT_sti_cursorsearchint32
	#define GET_sti_cursorsearchint32(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_cursorsearchint32(p0) 
	#define CHK_sti_cursorsearchint32  FALSE
	#define EXP_sti_cursorsearchint32  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_cursorsearchint32
	#define EXT_sti_cursorsearchint32
	#define GET_sti_cursorsearchint32(fl)  CAL_CMGETAPI( "sti_cursorsearchint32" ) 
	#define CAL_sti_cursorsearchint32  sti_cursorsearchint32
	#define CHK_sti_cursorsearchint32  TRUE
	#define EXP_sti_cursorsearchint32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchint32", (RTS_UINTPTR)sti_cursorsearchint32, 1, RTSITF_GET_SIGNATURE(0, 0x9F9D481A), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_cursorsearchint32
	#define EXT_sti_cursorsearchint32
	#define GET_sti_cursorsearchint32(fl)  CAL_CMGETAPI( "sti_cursorsearchint32" ) 
	#define CAL_sti_cursorsearchint32  sti_cursorsearchint32
	#define CHK_sti_cursorsearchint32  TRUE
	#define EXP_sti_cursorsearchint32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchint32", (RTS_UINTPTR)sti_cursorsearchint32, 1, RTSITF_GET_SIGNATURE(0, 0x9F9D481A), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_cursorsearchint32
	#define EXT_CmpCAAStoragesti_cursorsearchint32
	#define GET_CmpCAAStoragesti_cursorsearchint32  ERR_OK
	#define CAL_CmpCAAStoragesti_cursorsearchint32  sti_cursorsearchint32
	#define CHK_CmpCAAStoragesti_cursorsearchint32  TRUE
	#define EXP_CmpCAAStoragesti_cursorsearchint32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchint32", (RTS_UINTPTR)sti_cursorsearchint32, 1, RTSITF_GET_SIGNATURE(0, 0x9F9D481A), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_cursorsearchint32
	#define EXT_sti_cursorsearchint32
	#define GET_sti_cursorsearchint32(fl)  CAL_CMGETAPI( "sti_cursorsearchint32" ) 
	#define CAL_sti_cursorsearchint32  sti_cursorsearchint32
	#define CHK_sti_cursorsearchint32  TRUE
	#define EXP_sti_cursorsearchint32  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchint32", (RTS_UINTPTR)sti_cursorsearchint32, 1, RTSITF_GET_SIGNATURE(0, 0x9F9D481A), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_cursorsearchint32  PFSTI_CURSORSEARCHINT32_IEC pfsti_cursorsearchint32;
	#define EXT_sti_cursorsearchint32  extern PFSTI_CURSORSEARCHINT32_IEC pfsti_cursorsearchint32;
	#define GET_sti_cursorsearchint32(fl)  s_pfCMGetAPI2( "sti_cursorsearchint32", (RTS_VOID_FCTPTR *)&pfsti_cursorsearchint32, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x9F9D481A), 0x03050500)
	#define CAL_sti_cursorsearchint32  pfsti_cursorsearchint32
	#define CHK_sti_cursorsearchint32  (pfsti_cursorsearchint32 != NULL)
	#define EXP_sti_cursorsearchint32   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchint32", (RTS_UINTPTR)sti_cursorsearchint32, 1, RTSITF_GET_SIGNATURE(0, 0x9F9D481A), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorsearchint64_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_LINT liValue;				/* VAR_INPUT */	
	RTS_IEC_INT STI_CursorSearchINT64;	/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorsearchint64_struct;

void CDECL CDECL_EXT sti_cursorsearchint64(sti_cursorsearchint64_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_CURSORSEARCHINT64_IEC) (sti_cursorsearchint64_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORSEARCHINT64_NOTIMPLEMENTED)
	#define USE_sti_cursorsearchint64
	#define EXT_sti_cursorsearchint64
	#define GET_sti_cursorsearchint64(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_cursorsearchint64(p0) 
	#define CHK_sti_cursorsearchint64  FALSE
	#define EXP_sti_cursorsearchint64  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_cursorsearchint64
	#define EXT_sti_cursorsearchint64
	#define GET_sti_cursorsearchint64(fl)  CAL_CMGETAPI( "sti_cursorsearchint64" ) 
	#define CAL_sti_cursorsearchint64  sti_cursorsearchint64
	#define CHK_sti_cursorsearchint64  TRUE
	#define EXP_sti_cursorsearchint64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchint64", (RTS_UINTPTR)sti_cursorsearchint64, 1, RTSITF_GET_SIGNATURE(0, 0x8D041F2F), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_cursorsearchint64
	#define EXT_sti_cursorsearchint64
	#define GET_sti_cursorsearchint64(fl)  CAL_CMGETAPI( "sti_cursorsearchint64" ) 
	#define CAL_sti_cursorsearchint64  sti_cursorsearchint64
	#define CHK_sti_cursorsearchint64  TRUE
	#define EXP_sti_cursorsearchint64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchint64", (RTS_UINTPTR)sti_cursorsearchint64, 1, RTSITF_GET_SIGNATURE(0, 0x8D041F2F), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_cursorsearchint64
	#define EXT_CmpCAAStoragesti_cursorsearchint64
	#define GET_CmpCAAStoragesti_cursorsearchint64  ERR_OK
	#define CAL_CmpCAAStoragesti_cursorsearchint64  sti_cursorsearchint64
	#define CHK_CmpCAAStoragesti_cursorsearchint64  TRUE
	#define EXP_CmpCAAStoragesti_cursorsearchint64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchint64", (RTS_UINTPTR)sti_cursorsearchint64, 1, RTSITF_GET_SIGNATURE(0, 0x8D041F2F), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_cursorsearchint64
	#define EXT_sti_cursorsearchint64
	#define GET_sti_cursorsearchint64(fl)  CAL_CMGETAPI( "sti_cursorsearchint64" ) 
	#define CAL_sti_cursorsearchint64  sti_cursorsearchint64
	#define CHK_sti_cursorsearchint64  TRUE
	#define EXP_sti_cursorsearchint64  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchint64", (RTS_UINTPTR)sti_cursorsearchint64, 1, RTSITF_GET_SIGNATURE(0, 0x8D041F2F), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_cursorsearchint64  PFSTI_CURSORSEARCHINT64_IEC pfsti_cursorsearchint64;
	#define EXT_sti_cursorsearchint64  extern PFSTI_CURSORSEARCHINT64_IEC pfsti_cursorsearchint64;
	#define GET_sti_cursorsearchint64(fl)  s_pfCMGetAPI2( "sti_cursorsearchint64", (RTS_VOID_FCTPTR *)&pfsti_cursorsearchint64, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x8D041F2F), 0x03050500)
	#define CAL_sti_cursorsearchint64  pfsti_cursorsearchint64
	#define CHK_sti_cursorsearchint64  (pfsti_cursorsearchint64 != NULL)
	#define EXP_sti_cursorsearchint64   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchint64", (RTS_UINTPTR)sti_cursorsearchint64, 1, RTSITF_GET_SIGNATURE(0, 0x8D041F2F), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorsearchint8_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_SINT siValue;				/* VAR_INPUT */	
	RTS_IEC_INT STI_CursorSearchINT8;	/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorsearchint8_struct;

void CDECL CDECL_EXT sti_cursorsearchint8(sti_cursorsearchint8_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_CURSORSEARCHINT8_IEC) (sti_cursorsearchint8_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORSEARCHINT8_NOTIMPLEMENTED)
	#define USE_sti_cursorsearchint8
	#define EXT_sti_cursorsearchint8
	#define GET_sti_cursorsearchint8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_cursorsearchint8(p0) 
	#define CHK_sti_cursorsearchint8  FALSE
	#define EXP_sti_cursorsearchint8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_cursorsearchint8
	#define EXT_sti_cursorsearchint8
	#define GET_sti_cursorsearchint8(fl)  CAL_CMGETAPI( "sti_cursorsearchint8" ) 
	#define CAL_sti_cursorsearchint8  sti_cursorsearchint8
	#define CHK_sti_cursorsearchint8  TRUE
	#define EXP_sti_cursorsearchint8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchint8", (RTS_UINTPTR)sti_cursorsearchint8, 1, RTSITF_GET_SIGNATURE(0, 0xED9DD063), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_cursorsearchint8
	#define EXT_sti_cursorsearchint8
	#define GET_sti_cursorsearchint8(fl)  CAL_CMGETAPI( "sti_cursorsearchint8" ) 
	#define CAL_sti_cursorsearchint8  sti_cursorsearchint8
	#define CHK_sti_cursorsearchint8  TRUE
	#define EXP_sti_cursorsearchint8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchint8", (RTS_UINTPTR)sti_cursorsearchint8, 1, RTSITF_GET_SIGNATURE(0, 0xED9DD063), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_cursorsearchint8
	#define EXT_CmpCAAStoragesti_cursorsearchint8
	#define GET_CmpCAAStoragesti_cursorsearchint8  ERR_OK
	#define CAL_CmpCAAStoragesti_cursorsearchint8  sti_cursorsearchint8
	#define CHK_CmpCAAStoragesti_cursorsearchint8  TRUE
	#define EXP_CmpCAAStoragesti_cursorsearchint8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchint8", (RTS_UINTPTR)sti_cursorsearchint8, 1, RTSITF_GET_SIGNATURE(0, 0xED9DD063), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_cursorsearchint8
	#define EXT_sti_cursorsearchint8
	#define GET_sti_cursorsearchint8(fl)  CAL_CMGETAPI( "sti_cursorsearchint8" ) 
	#define CAL_sti_cursorsearchint8  sti_cursorsearchint8
	#define CHK_sti_cursorsearchint8  TRUE
	#define EXP_sti_cursorsearchint8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchint8", (RTS_UINTPTR)sti_cursorsearchint8, 1, RTSITF_GET_SIGNATURE(0, 0xED9DD063), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_cursorsearchint8  PFSTI_CURSORSEARCHINT8_IEC pfsti_cursorsearchint8;
	#define EXT_sti_cursorsearchint8  extern PFSTI_CURSORSEARCHINT8_IEC pfsti_cursorsearchint8;
	#define GET_sti_cursorsearchint8(fl)  s_pfCMGetAPI2( "sti_cursorsearchint8", (RTS_VOID_FCTPTR *)&pfsti_cursorsearchint8, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xED9DD063), 0x03050500)
	#define CAL_sti_cursorsearchint8  pfsti_cursorsearchint8
	#define CHK_sti_cursorsearchint8  (pfsti_cursorsearchint8 != NULL)
	#define EXP_sti_cursorsearchint8   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchint8", (RTS_UINTPTR)sti_cursorsearchint8, 1, RTSITF_GET_SIGNATURE(0, 0xED9DD063), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorsearchnull_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_INT STI_CursorSearchNULL;	/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorsearchnull_struct;

void CDECL CDECL_EXT sti_cursorsearchnull(sti_cursorsearchnull_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_CURSORSEARCHNULL_IEC) (sti_cursorsearchnull_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORSEARCHNULL_NOTIMPLEMENTED)
	#define USE_sti_cursorsearchnull
	#define EXT_sti_cursorsearchnull
	#define GET_sti_cursorsearchnull(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_cursorsearchnull(p0) 
	#define CHK_sti_cursorsearchnull  FALSE
	#define EXP_sti_cursorsearchnull  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_cursorsearchnull
	#define EXT_sti_cursorsearchnull
	#define GET_sti_cursorsearchnull(fl)  CAL_CMGETAPI( "sti_cursorsearchnull" ) 
	#define CAL_sti_cursorsearchnull  sti_cursorsearchnull
	#define CHK_sti_cursorsearchnull  TRUE
	#define EXP_sti_cursorsearchnull  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchnull", (RTS_UINTPTR)sti_cursorsearchnull, 1, RTSITF_GET_SIGNATURE(0, 0x1DC2D739), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_cursorsearchnull
	#define EXT_sti_cursorsearchnull
	#define GET_sti_cursorsearchnull(fl)  CAL_CMGETAPI( "sti_cursorsearchnull" ) 
	#define CAL_sti_cursorsearchnull  sti_cursorsearchnull
	#define CHK_sti_cursorsearchnull  TRUE
	#define EXP_sti_cursorsearchnull  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchnull", (RTS_UINTPTR)sti_cursorsearchnull, 1, RTSITF_GET_SIGNATURE(0, 0x1DC2D739), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_cursorsearchnull
	#define EXT_CmpCAAStoragesti_cursorsearchnull
	#define GET_CmpCAAStoragesti_cursorsearchnull  ERR_OK
	#define CAL_CmpCAAStoragesti_cursorsearchnull  sti_cursorsearchnull
	#define CHK_CmpCAAStoragesti_cursorsearchnull  TRUE
	#define EXP_CmpCAAStoragesti_cursorsearchnull  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchnull", (RTS_UINTPTR)sti_cursorsearchnull, 1, RTSITF_GET_SIGNATURE(0, 0x1DC2D739), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_cursorsearchnull
	#define EXT_sti_cursorsearchnull
	#define GET_sti_cursorsearchnull(fl)  CAL_CMGETAPI( "sti_cursorsearchnull" ) 
	#define CAL_sti_cursorsearchnull  sti_cursorsearchnull
	#define CHK_sti_cursorsearchnull  TRUE
	#define EXP_sti_cursorsearchnull  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchnull", (RTS_UINTPTR)sti_cursorsearchnull, 1, RTSITF_GET_SIGNATURE(0, 0x1DC2D739), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_cursorsearchnull  PFSTI_CURSORSEARCHNULL_IEC pfsti_cursorsearchnull;
	#define EXT_sti_cursorsearchnull  extern PFSTI_CURSORSEARCHNULL_IEC pfsti_cursorsearchnull;
	#define GET_sti_cursorsearchnull(fl)  s_pfCMGetAPI2( "sti_cursorsearchnull", (RTS_VOID_FCTPTR *)&pfsti_cursorsearchnull, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x1DC2D739), 0x03050500)
	#define CAL_sti_cursorsearchnull  pfsti_cursorsearchnull
	#define CHK_sti_cursorsearchnull  (pfsti_cursorsearchnull != NULL)
	#define EXP_sti_cursorsearchnull   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchnull", (RTS_UINTPTR)sti_cursorsearchnull, 1, RTSITF_GET_SIGNATURE(0, 0x1DC2D739), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorsearchreal4_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_REAL rValue;				/* VAR_INPUT */	
	RTS_IEC_INT STI_CursorSearchREAL4;	/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorsearchreal4_struct;

void CDECL CDECL_EXT sti_cursorsearchreal4(sti_cursorsearchreal4_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_CURSORSEARCHREAL4_IEC) (sti_cursorsearchreal4_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORSEARCHREAL4_NOTIMPLEMENTED)
	#define USE_sti_cursorsearchreal4
	#define EXT_sti_cursorsearchreal4
	#define GET_sti_cursorsearchreal4(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_cursorsearchreal4(p0) 
	#define CHK_sti_cursorsearchreal4  FALSE
	#define EXP_sti_cursorsearchreal4  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_cursorsearchreal4
	#define EXT_sti_cursorsearchreal4
	#define GET_sti_cursorsearchreal4(fl)  CAL_CMGETAPI( "sti_cursorsearchreal4" ) 
	#define CAL_sti_cursorsearchreal4  sti_cursorsearchreal4
	#define CHK_sti_cursorsearchreal4  TRUE
	#define EXP_sti_cursorsearchreal4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchreal4", (RTS_UINTPTR)sti_cursorsearchreal4, 1, RTSITF_GET_SIGNATURE(0, 0xA6FFD47D), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_cursorsearchreal4
	#define EXT_sti_cursorsearchreal4
	#define GET_sti_cursorsearchreal4(fl)  CAL_CMGETAPI( "sti_cursorsearchreal4" ) 
	#define CAL_sti_cursorsearchreal4  sti_cursorsearchreal4
	#define CHK_sti_cursorsearchreal4  TRUE
	#define EXP_sti_cursorsearchreal4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchreal4", (RTS_UINTPTR)sti_cursorsearchreal4, 1, RTSITF_GET_SIGNATURE(0, 0xA6FFD47D), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_cursorsearchreal4
	#define EXT_CmpCAAStoragesti_cursorsearchreal4
	#define GET_CmpCAAStoragesti_cursorsearchreal4  ERR_OK
	#define CAL_CmpCAAStoragesti_cursorsearchreal4  sti_cursorsearchreal4
	#define CHK_CmpCAAStoragesti_cursorsearchreal4  TRUE
	#define EXP_CmpCAAStoragesti_cursorsearchreal4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchreal4", (RTS_UINTPTR)sti_cursorsearchreal4, 1, RTSITF_GET_SIGNATURE(0, 0xA6FFD47D), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_cursorsearchreal4
	#define EXT_sti_cursorsearchreal4
	#define GET_sti_cursorsearchreal4(fl)  CAL_CMGETAPI( "sti_cursorsearchreal4" ) 
	#define CAL_sti_cursorsearchreal4  sti_cursorsearchreal4
	#define CHK_sti_cursorsearchreal4  TRUE
	#define EXP_sti_cursorsearchreal4  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchreal4", (RTS_UINTPTR)sti_cursorsearchreal4, 1, RTSITF_GET_SIGNATURE(0, 0xA6FFD47D), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_cursorsearchreal4  PFSTI_CURSORSEARCHREAL4_IEC pfsti_cursorsearchreal4;
	#define EXT_sti_cursorsearchreal4  extern PFSTI_CURSORSEARCHREAL4_IEC pfsti_cursorsearchreal4;
	#define GET_sti_cursorsearchreal4(fl)  s_pfCMGetAPI2( "sti_cursorsearchreal4", (RTS_VOID_FCTPTR *)&pfsti_cursorsearchreal4, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA6FFD47D), 0x03050500)
	#define CAL_sti_cursorsearchreal4  pfsti_cursorsearchreal4
	#define CHK_sti_cursorsearchreal4  (pfsti_cursorsearchreal4 != NULL)
	#define EXP_sti_cursorsearchreal4   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchreal4", (RTS_UINTPTR)sti_cursorsearchreal4, 1, RTSITF_GET_SIGNATURE(0, 0xA6FFD47D), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorsearchreal8_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_LREAL lrValue;				/* VAR_INPUT */	
	RTS_IEC_INT STI_CursorSearchREAL8;	/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorsearchreal8_struct;

void CDECL CDECL_EXT sti_cursorsearchreal8(sti_cursorsearchreal8_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_CURSORSEARCHREAL8_IEC) (sti_cursorsearchreal8_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORSEARCHREAL8_NOTIMPLEMENTED)
	#define USE_sti_cursorsearchreal8
	#define EXT_sti_cursorsearchreal8
	#define GET_sti_cursorsearchreal8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_cursorsearchreal8(p0) 
	#define CHK_sti_cursorsearchreal8  FALSE
	#define EXP_sti_cursorsearchreal8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_cursorsearchreal8
	#define EXT_sti_cursorsearchreal8
	#define GET_sti_cursorsearchreal8(fl)  CAL_CMGETAPI( "sti_cursorsearchreal8" ) 
	#define CAL_sti_cursorsearchreal8  sti_cursorsearchreal8
	#define CHK_sti_cursorsearchreal8  TRUE
	#define EXP_sti_cursorsearchreal8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchreal8", (RTS_UINTPTR)sti_cursorsearchreal8, 1, RTSITF_GET_SIGNATURE(0, 0xEC458BB0), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_cursorsearchreal8
	#define EXT_sti_cursorsearchreal8
	#define GET_sti_cursorsearchreal8(fl)  CAL_CMGETAPI( "sti_cursorsearchreal8" ) 
	#define CAL_sti_cursorsearchreal8  sti_cursorsearchreal8
	#define CHK_sti_cursorsearchreal8  TRUE
	#define EXP_sti_cursorsearchreal8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchreal8", (RTS_UINTPTR)sti_cursorsearchreal8, 1, RTSITF_GET_SIGNATURE(0, 0xEC458BB0), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_cursorsearchreal8
	#define EXT_CmpCAAStoragesti_cursorsearchreal8
	#define GET_CmpCAAStoragesti_cursorsearchreal8  ERR_OK
	#define CAL_CmpCAAStoragesti_cursorsearchreal8  sti_cursorsearchreal8
	#define CHK_CmpCAAStoragesti_cursorsearchreal8  TRUE
	#define EXP_CmpCAAStoragesti_cursorsearchreal8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchreal8", (RTS_UINTPTR)sti_cursorsearchreal8, 1, RTSITF_GET_SIGNATURE(0, 0xEC458BB0), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_cursorsearchreal8
	#define EXT_sti_cursorsearchreal8
	#define GET_sti_cursorsearchreal8(fl)  CAL_CMGETAPI( "sti_cursorsearchreal8" ) 
	#define CAL_sti_cursorsearchreal8  sti_cursorsearchreal8
	#define CHK_sti_cursorsearchreal8  TRUE
	#define EXP_sti_cursorsearchreal8  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchreal8", (RTS_UINTPTR)sti_cursorsearchreal8, 1, RTSITF_GET_SIGNATURE(0, 0xEC458BB0), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_cursorsearchreal8  PFSTI_CURSORSEARCHREAL8_IEC pfsti_cursorsearchreal8;
	#define EXT_sti_cursorsearchreal8  extern PFSTI_CURSORSEARCHREAL8_IEC pfsti_cursorsearchreal8;
	#define GET_sti_cursorsearchreal8(fl)  s_pfCMGetAPI2( "sti_cursorsearchreal8", (RTS_VOID_FCTPTR *)&pfsti_cursorsearchreal8, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xEC458BB0), 0x03050500)
	#define CAL_sti_cursorsearchreal8  pfsti_cursorsearchreal8
	#define CHK_sti_cursorsearchreal8  (pfsti_cursorsearchreal8 != NULL)
	#define EXP_sti_cursorsearchreal8   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchreal8", (RTS_UINTPTR)sti_cursorsearchreal8, 1, RTSITF_GET_SIGNATURE(0, 0xEC458BB0), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorsearchrowid_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_DWORD idRow;				/* VAR_INPUT */	
	RTS_IEC_INT STI_CursorSearchRowId;	/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorsearchrowid_struct;

void CDECL CDECL_EXT sti_cursorsearchrowid(sti_cursorsearchrowid_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_CURSORSEARCHROWID_IEC) (sti_cursorsearchrowid_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORSEARCHROWID_NOTIMPLEMENTED)
	#define USE_sti_cursorsearchrowid
	#define EXT_sti_cursorsearchrowid
	#define GET_sti_cursorsearchrowid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_cursorsearchrowid(p0) 
	#define CHK_sti_cursorsearchrowid  FALSE
	#define EXP_sti_cursorsearchrowid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_cursorsearchrowid
	#define EXT_sti_cursorsearchrowid
	#define GET_sti_cursorsearchrowid(fl)  CAL_CMGETAPI( "sti_cursorsearchrowid" ) 
	#define CAL_sti_cursorsearchrowid  sti_cursorsearchrowid
	#define CHK_sti_cursorsearchrowid  TRUE
	#define EXP_sti_cursorsearchrowid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchrowid", (RTS_UINTPTR)sti_cursorsearchrowid, 1, RTSITF_GET_SIGNATURE(0, 0x7E7E8E92), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_cursorsearchrowid
	#define EXT_sti_cursorsearchrowid
	#define GET_sti_cursorsearchrowid(fl)  CAL_CMGETAPI( "sti_cursorsearchrowid" ) 
	#define CAL_sti_cursorsearchrowid  sti_cursorsearchrowid
	#define CHK_sti_cursorsearchrowid  TRUE
	#define EXP_sti_cursorsearchrowid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchrowid", (RTS_UINTPTR)sti_cursorsearchrowid, 1, RTSITF_GET_SIGNATURE(0, 0x7E7E8E92), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_cursorsearchrowid
	#define EXT_CmpCAAStoragesti_cursorsearchrowid
	#define GET_CmpCAAStoragesti_cursorsearchrowid  ERR_OK
	#define CAL_CmpCAAStoragesti_cursorsearchrowid  sti_cursorsearchrowid
	#define CHK_CmpCAAStoragesti_cursorsearchrowid  TRUE
	#define EXP_CmpCAAStoragesti_cursorsearchrowid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchrowid", (RTS_UINTPTR)sti_cursorsearchrowid, 1, RTSITF_GET_SIGNATURE(0, 0x7E7E8E92), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_cursorsearchrowid
	#define EXT_sti_cursorsearchrowid
	#define GET_sti_cursorsearchrowid(fl)  CAL_CMGETAPI( "sti_cursorsearchrowid" ) 
	#define CAL_sti_cursorsearchrowid  sti_cursorsearchrowid
	#define CHK_sti_cursorsearchrowid  TRUE
	#define EXP_sti_cursorsearchrowid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchrowid", (RTS_UINTPTR)sti_cursorsearchrowid, 1, RTSITF_GET_SIGNATURE(0, 0x7E7E8E92), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_cursorsearchrowid  PFSTI_CURSORSEARCHROWID_IEC pfsti_cursorsearchrowid;
	#define EXT_sti_cursorsearchrowid  extern PFSTI_CURSORSEARCHROWID_IEC pfsti_cursorsearchrowid;
	#define GET_sti_cursorsearchrowid(fl)  s_pfCMGetAPI2( "sti_cursorsearchrowid", (RTS_VOID_FCTPTR *)&pfsti_cursorsearchrowid, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x7E7E8E92), 0x03050500)
	#define CAL_sti_cursorsearchrowid  pfsti_cursorsearchrowid
	#define CHK_sti_cursorsearchrowid  (pfsti_cursorsearchrowid != NULL)
	#define EXP_sti_cursorsearchrowid   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchrowid", (RTS_UINTPTR)sti_cursorsearchrowid, 1, RTSITF_GET_SIGNATURE(0, 0x7E7E8E92), 0x03050500) 
#endif


/**
 * Replacement of function _CursorSearchRowId, that uses a LINT value instead of a CAA.IDENT value.
 */
typedef struct tagsti_cursorsearchrowid2_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	RTS_IEC_LINT idRow;					/* VAR_INPUT */	
	RTS_IEC_INT STI_CursorSearchRowId2;	/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorsearchrowid2_struct;

void CDECL CDECL_EXT sti_cursorsearchrowid2(sti_cursorsearchrowid2_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_CURSORSEARCHROWID2_IEC) (sti_cursorsearchrowid2_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORSEARCHROWID2_NOTIMPLEMENTED)
	#define USE_sti_cursorsearchrowid2
	#define EXT_sti_cursorsearchrowid2
	#define GET_sti_cursorsearchrowid2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_cursorsearchrowid2(p0) 
	#define CHK_sti_cursorsearchrowid2  FALSE
	#define EXP_sti_cursorsearchrowid2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_cursorsearchrowid2
	#define EXT_sti_cursorsearchrowid2
	#define GET_sti_cursorsearchrowid2(fl)  CAL_CMGETAPI( "sti_cursorsearchrowid2" ) 
	#define CAL_sti_cursorsearchrowid2  sti_cursorsearchrowid2
	#define CHK_sti_cursorsearchrowid2  TRUE
	#define EXP_sti_cursorsearchrowid2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchrowid2", (RTS_UINTPTR)sti_cursorsearchrowid2, 1, RTSITF_GET_SIGNATURE(0, 0x11FC0EBB), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_cursorsearchrowid2
	#define EXT_sti_cursorsearchrowid2
	#define GET_sti_cursorsearchrowid2(fl)  CAL_CMGETAPI( "sti_cursorsearchrowid2" ) 
	#define CAL_sti_cursorsearchrowid2  sti_cursorsearchrowid2
	#define CHK_sti_cursorsearchrowid2  TRUE
	#define EXP_sti_cursorsearchrowid2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchrowid2", (RTS_UINTPTR)sti_cursorsearchrowid2, 1, RTSITF_GET_SIGNATURE(0, 0x11FC0EBB), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_cursorsearchrowid2
	#define EXT_CmpCAAStoragesti_cursorsearchrowid2
	#define GET_CmpCAAStoragesti_cursorsearchrowid2  ERR_OK
	#define CAL_CmpCAAStoragesti_cursorsearchrowid2  sti_cursorsearchrowid2
	#define CHK_CmpCAAStoragesti_cursorsearchrowid2  TRUE
	#define EXP_CmpCAAStoragesti_cursorsearchrowid2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchrowid2", (RTS_UINTPTR)sti_cursorsearchrowid2, 1, RTSITF_GET_SIGNATURE(0, 0x11FC0EBB), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_cursorsearchrowid2
	#define EXT_sti_cursorsearchrowid2
	#define GET_sti_cursorsearchrowid2(fl)  CAL_CMGETAPI( "sti_cursorsearchrowid2" ) 
	#define CAL_sti_cursorsearchrowid2  sti_cursorsearchrowid2
	#define CHK_sti_cursorsearchrowid2  TRUE
	#define EXP_sti_cursorsearchrowid2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchrowid2", (RTS_UINTPTR)sti_cursorsearchrowid2, 1, RTSITF_GET_SIGNATURE(0, 0x11FC0EBB), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_cursorsearchrowid2  PFSTI_CURSORSEARCHROWID2_IEC pfsti_cursorsearchrowid2;
	#define EXT_sti_cursorsearchrowid2  extern PFSTI_CURSORSEARCHROWID2_IEC pfsti_cursorsearchrowid2;
	#define GET_sti_cursorsearchrowid2(fl)  s_pfCMGetAPI2( "sti_cursorsearchrowid2", (RTS_VOID_FCTPTR *)&pfsti_cursorsearchrowid2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x11FC0EBB), 0x03050500)
	#define CAL_sti_cursorsearchrowid2  pfsti_cursorsearchrowid2
	#define CHK_sti_cursorsearchrowid2  (pfsti_cursorsearchrowid2 != NULL)
	#define EXP_sti_cursorsearchrowid2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchrowid2", (RTS_UINTPTR)sti_cursorsearchrowid2, 1, RTSITF_GET_SIGNATURE(0, 0x11FC0EBB), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_cursorsearchtext_struct
{
	RTS_IEC_XWORD hCursor;				/* VAR_INPUT */	
	STO_TEXT *txtValue;					/* VAR_IN_OUT */	
	RTS_IEC_INT STI_CursorSearchTEXT;	/* VAR_OUTPUT, Enum: ERROR */
} sti_cursorsearchtext_struct;

void CDECL CDECL_EXT sti_cursorsearchtext(sti_cursorsearchtext_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_CURSORSEARCHTEXT_IEC) (sti_cursorsearchtext_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORSEARCHTEXT_NOTIMPLEMENTED)
	#define USE_sti_cursorsearchtext
	#define EXT_sti_cursorsearchtext
	#define GET_sti_cursorsearchtext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_cursorsearchtext(p0) 
	#define CHK_sti_cursorsearchtext  FALSE
	#define EXP_sti_cursorsearchtext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_cursorsearchtext
	#define EXT_sti_cursorsearchtext
	#define GET_sti_cursorsearchtext(fl)  CAL_CMGETAPI( "sti_cursorsearchtext" ) 
	#define CAL_sti_cursorsearchtext  sti_cursorsearchtext
	#define CHK_sti_cursorsearchtext  TRUE
	#define EXP_sti_cursorsearchtext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchtext", (RTS_UINTPTR)sti_cursorsearchtext, 1, RTSITF_GET_SIGNATURE(0, 0x877B0D88), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_cursorsearchtext
	#define EXT_sti_cursorsearchtext
	#define GET_sti_cursorsearchtext(fl)  CAL_CMGETAPI( "sti_cursorsearchtext" ) 
	#define CAL_sti_cursorsearchtext  sti_cursorsearchtext
	#define CHK_sti_cursorsearchtext  TRUE
	#define EXP_sti_cursorsearchtext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchtext", (RTS_UINTPTR)sti_cursorsearchtext, 1, RTSITF_GET_SIGNATURE(0, 0x877B0D88), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_cursorsearchtext
	#define EXT_CmpCAAStoragesti_cursorsearchtext
	#define GET_CmpCAAStoragesti_cursorsearchtext  ERR_OK
	#define CAL_CmpCAAStoragesti_cursorsearchtext  sti_cursorsearchtext
	#define CHK_CmpCAAStoragesti_cursorsearchtext  TRUE
	#define EXP_CmpCAAStoragesti_cursorsearchtext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchtext", (RTS_UINTPTR)sti_cursorsearchtext, 1, RTSITF_GET_SIGNATURE(0, 0x877B0D88), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_cursorsearchtext
	#define EXT_sti_cursorsearchtext
	#define GET_sti_cursorsearchtext(fl)  CAL_CMGETAPI( "sti_cursorsearchtext" ) 
	#define CAL_sti_cursorsearchtext  sti_cursorsearchtext
	#define CHK_sti_cursorsearchtext  TRUE
	#define EXP_sti_cursorsearchtext  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchtext", (RTS_UINTPTR)sti_cursorsearchtext, 1, RTSITF_GET_SIGNATURE(0, 0x877B0D88), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_cursorsearchtext  PFSTI_CURSORSEARCHTEXT_IEC pfsti_cursorsearchtext;
	#define EXT_sti_cursorsearchtext  extern PFSTI_CURSORSEARCHTEXT_IEC pfsti_cursorsearchtext;
	#define GET_sti_cursorsearchtext(fl)  s_pfCMGetAPI2( "sti_cursorsearchtext", (RTS_VOID_FCTPTR *)&pfsti_cursorsearchtext, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x877B0D88), 0x03050500)
	#define CAL_sti_cursorsearchtext  pfsti_cursorsearchtext
	#define CHK_sti_cursorsearchtext  (pfsti_cursorsearchtext != NULL)
	#define EXP_sti_cursorsearchtext   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_cursorsearchtext", (RTS_UINTPTR)sti_cursorsearchtext, 1, RTSITF_GET_SIGNATURE(0, 0x877B0D88), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowclear_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_INT STI_RowClear;			/* VAR_OUTPUT, Enum: ERROR */
} sti_rowclear_struct;

void CDECL CDECL_EXT sti_rowclear(sti_rowclear_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_ROWCLEAR_IEC) (sti_rowclear_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWCLEAR_NOTIMPLEMENTED)
	#define USE_sti_rowclear
	#define EXT_sti_rowclear
	#define GET_sti_rowclear(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_rowclear(p0) 
	#define CHK_sti_rowclear  FALSE
	#define EXP_sti_rowclear  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_rowclear
	#define EXT_sti_rowclear
	#define GET_sti_rowclear(fl)  CAL_CMGETAPI( "sti_rowclear" ) 
	#define CAL_sti_rowclear  sti_rowclear
	#define CHK_sti_rowclear  TRUE
	#define EXP_sti_rowclear  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowclear", (RTS_UINTPTR)sti_rowclear, 1, RTSITF_GET_SIGNATURE(0, 0x063F3EDA), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_rowclear
	#define EXT_sti_rowclear
	#define GET_sti_rowclear(fl)  CAL_CMGETAPI( "sti_rowclear" ) 
	#define CAL_sti_rowclear  sti_rowclear
	#define CHK_sti_rowclear  TRUE
	#define EXP_sti_rowclear  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowclear", (RTS_UINTPTR)sti_rowclear, 1, RTSITF_GET_SIGNATURE(0, 0x063F3EDA), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_rowclear
	#define EXT_CmpCAAStoragesti_rowclear
	#define GET_CmpCAAStoragesti_rowclear  ERR_OK
	#define CAL_CmpCAAStoragesti_rowclear  sti_rowclear
	#define CHK_CmpCAAStoragesti_rowclear  TRUE
	#define EXP_CmpCAAStoragesti_rowclear  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowclear", (RTS_UINTPTR)sti_rowclear, 1, RTSITF_GET_SIGNATURE(0, 0x063F3EDA), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_rowclear
	#define EXT_sti_rowclear
	#define GET_sti_rowclear(fl)  CAL_CMGETAPI( "sti_rowclear" ) 
	#define CAL_sti_rowclear  sti_rowclear
	#define CHK_sti_rowclear  TRUE
	#define EXP_sti_rowclear  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowclear", (RTS_UINTPTR)sti_rowclear, 1, RTSITF_GET_SIGNATURE(0, 0x063F3EDA), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_rowclear  PFSTI_ROWCLEAR_IEC pfsti_rowclear;
	#define EXT_sti_rowclear  extern PFSTI_ROWCLEAR_IEC pfsti_rowclear;
	#define GET_sti_rowclear(fl)  s_pfCMGetAPI2( "sti_rowclear", (RTS_VOID_FCTPTR *)&pfsti_rowclear, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x063F3EDA), 0x03050500)
	#define CAL_sti_rowclear  pfsti_rowclear
	#define CHK_sti_rowclear  (pfsti_rowclear != NULL)
	#define EXP_sti_rowclear   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowclear", (RTS_UINTPTR)sti_rowclear, 1, RTSITF_GET_SIGNATURE(0, 0x063F3EDA), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowcreate_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_XWORD STI_RowCreate;		/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_rowcreate_struct;

void CDECL CDECL_EXT sti_rowcreate(sti_rowcreate_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_ROWCREATE_IEC) (sti_rowcreate_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWCREATE_NOTIMPLEMENTED)
	#define USE_sti_rowcreate
	#define EXT_sti_rowcreate
	#define GET_sti_rowcreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_rowcreate(p0) 
	#define CHK_sti_rowcreate  FALSE
	#define EXP_sti_rowcreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_rowcreate
	#define EXT_sti_rowcreate
	#define GET_sti_rowcreate(fl)  CAL_CMGETAPI( "sti_rowcreate" ) 
	#define CAL_sti_rowcreate  sti_rowcreate
	#define CHK_sti_rowcreate  TRUE
	#define EXP_sti_rowcreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowcreate", (RTS_UINTPTR)sti_rowcreate, 1, RTSITF_GET_SIGNATURE(0, 0x51A8A2C3), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_rowcreate
	#define EXT_sti_rowcreate
	#define GET_sti_rowcreate(fl)  CAL_CMGETAPI( "sti_rowcreate" ) 
	#define CAL_sti_rowcreate  sti_rowcreate
	#define CHK_sti_rowcreate  TRUE
	#define EXP_sti_rowcreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowcreate", (RTS_UINTPTR)sti_rowcreate, 1, RTSITF_GET_SIGNATURE(0, 0x51A8A2C3), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_rowcreate
	#define EXT_CmpCAAStoragesti_rowcreate
	#define GET_CmpCAAStoragesti_rowcreate  ERR_OK
	#define CAL_CmpCAAStoragesti_rowcreate  sti_rowcreate
	#define CHK_CmpCAAStoragesti_rowcreate  TRUE
	#define EXP_CmpCAAStoragesti_rowcreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowcreate", (RTS_UINTPTR)sti_rowcreate, 1, RTSITF_GET_SIGNATURE(0, 0x51A8A2C3), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_rowcreate
	#define EXT_sti_rowcreate
	#define GET_sti_rowcreate(fl)  CAL_CMGETAPI( "sti_rowcreate" ) 
	#define CAL_sti_rowcreate  sti_rowcreate
	#define CHK_sti_rowcreate  TRUE
	#define EXP_sti_rowcreate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowcreate", (RTS_UINTPTR)sti_rowcreate, 1, RTSITF_GET_SIGNATURE(0, 0x51A8A2C3), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_rowcreate  PFSTI_ROWCREATE_IEC pfsti_rowcreate;
	#define EXT_sti_rowcreate  extern PFSTI_ROWCREATE_IEC pfsti_rowcreate;
	#define GET_sti_rowcreate(fl)  s_pfCMGetAPI2( "sti_rowcreate", (RTS_VOID_FCTPTR *)&pfsti_rowcreate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x51A8A2C3), 0x03050500)
	#define CAL_sti_rowcreate  pfsti_rowcreate
	#define CHK_sti_rowcreate  (pfsti_rowcreate != NULL)
	#define EXP_sti_rowcreate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowcreate", (RTS_UINTPTR)sti_rowcreate, 1, RTSITF_GET_SIGNATURE(0, 0x51A8A2C3), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowdelete_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_DWORD idRow;				/* VAR_INPUT */	
	RTS_IEC_INT STI_RowDelete;			/* VAR_OUTPUT, Enum: ERROR */
} sti_rowdelete_struct;

void CDECL CDECL_EXT sti_rowdelete(sti_rowdelete_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_ROWDELETE_IEC) (sti_rowdelete_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWDELETE_NOTIMPLEMENTED)
	#define USE_sti_rowdelete
	#define EXT_sti_rowdelete
	#define GET_sti_rowdelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_rowdelete(p0) 
	#define CHK_sti_rowdelete  FALSE
	#define EXP_sti_rowdelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_rowdelete
	#define EXT_sti_rowdelete
	#define GET_sti_rowdelete(fl)  CAL_CMGETAPI( "sti_rowdelete" ) 
	#define CAL_sti_rowdelete  sti_rowdelete
	#define CHK_sti_rowdelete  TRUE
	#define EXP_sti_rowdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowdelete", (RTS_UINTPTR)sti_rowdelete, 1, RTSITF_GET_SIGNATURE(0, 0x2F288537), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_rowdelete
	#define EXT_sti_rowdelete
	#define GET_sti_rowdelete(fl)  CAL_CMGETAPI( "sti_rowdelete" ) 
	#define CAL_sti_rowdelete  sti_rowdelete
	#define CHK_sti_rowdelete  TRUE
	#define EXP_sti_rowdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowdelete", (RTS_UINTPTR)sti_rowdelete, 1, RTSITF_GET_SIGNATURE(0, 0x2F288537), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_rowdelete
	#define EXT_CmpCAAStoragesti_rowdelete
	#define GET_CmpCAAStoragesti_rowdelete  ERR_OK
	#define CAL_CmpCAAStoragesti_rowdelete  sti_rowdelete
	#define CHK_CmpCAAStoragesti_rowdelete  TRUE
	#define EXP_CmpCAAStoragesti_rowdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowdelete", (RTS_UINTPTR)sti_rowdelete, 1, RTSITF_GET_SIGNATURE(0, 0x2F288537), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_rowdelete
	#define EXT_sti_rowdelete
	#define GET_sti_rowdelete(fl)  CAL_CMGETAPI( "sti_rowdelete" ) 
	#define CAL_sti_rowdelete  sti_rowdelete
	#define CHK_sti_rowdelete  TRUE
	#define EXP_sti_rowdelete  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowdelete", (RTS_UINTPTR)sti_rowdelete, 1, RTSITF_GET_SIGNATURE(0, 0x2F288537), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_rowdelete  PFSTI_ROWDELETE_IEC pfsti_rowdelete;
	#define EXT_sti_rowdelete  extern PFSTI_ROWDELETE_IEC pfsti_rowdelete;
	#define GET_sti_rowdelete(fl)  s_pfCMGetAPI2( "sti_rowdelete", (RTS_VOID_FCTPTR *)&pfsti_rowdelete, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x2F288537), 0x03050500)
	#define CAL_sti_rowdelete  pfsti_rowdelete
	#define CHK_sti_rowdelete  (pfsti_rowdelete != NULL)
	#define EXP_sti_rowdelete   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowdelete", (RTS_UINTPTR)sti_rowdelete, 1, RTSITF_GET_SIGNATURE(0, 0x2F288537), 0x03050500) 
#endif


/**
 * Replacement of function _RowDelete, that uses a LINT value instead of a CAA.IDENT value.
 */
typedef struct tagsti_rowdelete2_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_LINT idRow;					/* VAR_INPUT */	
	RTS_IEC_INT STI_RowDelete2;			/* VAR_OUTPUT, Enum: ERROR */
} sti_rowdelete2_struct;

void CDECL CDECL_EXT sti_rowdelete2(sti_rowdelete2_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_ROWDELETE2_IEC) (sti_rowdelete2_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWDELETE2_NOTIMPLEMENTED)
	#define USE_sti_rowdelete2
	#define EXT_sti_rowdelete2
	#define GET_sti_rowdelete2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_rowdelete2(p0) 
	#define CHK_sti_rowdelete2  FALSE
	#define EXP_sti_rowdelete2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_rowdelete2
	#define EXT_sti_rowdelete2
	#define GET_sti_rowdelete2(fl)  CAL_CMGETAPI( "sti_rowdelete2" ) 
	#define CAL_sti_rowdelete2  sti_rowdelete2
	#define CHK_sti_rowdelete2  TRUE
	#define EXP_sti_rowdelete2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowdelete2", (RTS_UINTPTR)sti_rowdelete2, 1, RTSITF_GET_SIGNATURE(0, 0x308F63CF), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_rowdelete2
	#define EXT_sti_rowdelete2
	#define GET_sti_rowdelete2(fl)  CAL_CMGETAPI( "sti_rowdelete2" ) 
	#define CAL_sti_rowdelete2  sti_rowdelete2
	#define CHK_sti_rowdelete2  TRUE
	#define EXP_sti_rowdelete2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowdelete2", (RTS_UINTPTR)sti_rowdelete2, 1, RTSITF_GET_SIGNATURE(0, 0x308F63CF), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_rowdelete2
	#define EXT_CmpCAAStoragesti_rowdelete2
	#define GET_CmpCAAStoragesti_rowdelete2  ERR_OK
	#define CAL_CmpCAAStoragesti_rowdelete2  sti_rowdelete2
	#define CHK_CmpCAAStoragesti_rowdelete2  TRUE
	#define EXP_CmpCAAStoragesti_rowdelete2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowdelete2", (RTS_UINTPTR)sti_rowdelete2, 1, RTSITF_GET_SIGNATURE(0, 0x308F63CF), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_rowdelete2
	#define EXT_sti_rowdelete2
	#define GET_sti_rowdelete2(fl)  CAL_CMGETAPI( "sti_rowdelete2" ) 
	#define CAL_sti_rowdelete2  sti_rowdelete2
	#define CHK_sti_rowdelete2  TRUE
	#define EXP_sti_rowdelete2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowdelete2", (RTS_UINTPTR)sti_rowdelete2, 1, RTSITF_GET_SIGNATURE(0, 0x308F63CF), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_rowdelete2  PFSTI_ROWDELETE2_IEC pfsti_rowdelete2;
	#define EXT_sti_rowdelete2  extern PFSTI_ROWDELETE2_IEC pfsti_rowdelete2;
	#define GET_sti_rowdelete2(fl)  s_pfCMGetAPI2( "sti_rowdelete2", (RTS_VOID_FCTPTR *)&pfsti_rowdelete2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x308F63CF), 0x03050500)
	#define CAL_sti_rowdelete2  pfsti_rowdelete2
	#define CHK_sti_rowdelete2  (pfsti_rowdelete2 != NULL)
	#define EXP_sti_rowdelete2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowdelete2", (RTS_UINTPTR)sti_rowdelete2, 1, RTSITF_GET_SIGNATURE(0, 0x308F63CF), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_rowduplicate(sti_rowduplicate_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_ROWDUPLICATE_IEC) (sti_rowduplicate_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWDUPLICATE_NOTIMPLEMENTED)
	#define USE_sti_rowduplicate
	#define EXT_sti_rowduplicate
	#define GET_sti_rowduplicate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_rowduplicate(p0) 
	#define CHK_sti_rowduplicate  FALSE
	#define EXP_sti_rowduplicate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_rowduplicate
	#define EXT_sti_rowduplicate
	#define GET_sti_rowduplicate(fl)  CAL_CMGETAPI( "sti_rowduplicate" ) 
	#define CAL_sti_rowduplicate  sti_rowduplicate
	#define CHK_sti_rowduplicate  TRUE
	#define EXP_sti_rowduplicate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowduplicate", (RTS_UINTPTR)sti_rowduplicate, 1, RTSITF_GET_SIGNATURE(0, 0xB9AD1D61), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_rowduplicate
	#define EXT_sti_rowduplicate
	#define GET_sti_rowduplicate(fl)  CAL_CMGETAPI( "sti_rowduplicate" ) 
	#define CAL_sti_rowduplicate  sti_rowduplicate
	#define CHK_sti_rowduplicate  TRUE
	#define EXP_sti_rowduplicate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowduplicate", (RTS_UINTPTR)sti_rowduplicate, 1, RTSITF_GET_SIGNATURE(0, 0xB9AD1D61), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_rowduplicate
	#define EXT_CmpCAAStoragesti_rowduplicate
	#define GET_CmpCAAStoragesti_rowduplicate  ERR_OK
	#define CAL_CmpCAAStoragesti_rowduplicate  sti_rowduplicate
	#define CHK_CmpCAAStoragesti_rowduplicate  TRUE
	#define EXP_CmpCAAStoragesti_rowduplicate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowduplicate", (RTS_UINTPTR)sti_rowduplicate, 1, RTSITF_GET_SIGNATURE(0, 0xB9AD1D61), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_rowduplicate
	#define EXT_sti_rowduplicate
	#define GET_sti_rowduplicate(fl)  CAL_CMGETAPI( "sti_rowduplicate" ) 
	#define CAL_sti_rowduplicate  sti_rowduplicate
	#define CHK_sti_rowduplicate  TRUE
	#define EXP_sti_rowduplicate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowduplicate", (RTS_UINTPTR)sti_rowduplicate, 1, RTSITF_GET_SIGNATURE(0, 0xB9AD1D61), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_rowduplicate  PFSTI_ROWDUPLICATE_IEC pfsti_rowduplicate;
	#define EXT_sti_rowduplicate  extern PFSTI_ROWDUPLICATE_IEC pfsti_rowduplicate;
	#define GET_sti_rowduplicate(fl)  s_pfCMGetAPI2( "sti_rowduplicate", (RTS_VOID_FCTPTR *)&pfsti_rowduplicate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xB9AD1D61), 0x03050500)
	#define CAL_sti_rowduplicate  pfsti_rowduplicate
	#define CHK_sti_rowduplicate  (pfsti_rowduplicate != NULL)
	#define EXP_sti_rowduplicate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowduplicate", (RTS_UINTPTR)sti_rowduplicate, 1, RTSITF_GET_SIGNATURE(0, 0xB9AD1D61), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowgethaschanged_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_BOOL STI_RowGetHasChanged;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_rowgethaschanged_struct;

void CDECL CDECL_EXT sti_rowgethaschanged(sti_rowgethaschanged_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_ROWGETHASCHANGED_IEC) (sti_rowgethaschanged_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWGETHASCHANGED_NOTIMPLEMENTED)
	#define USE_sti_rowgethaschanged
	#define EXT_sti_rowgethaschanged
	#define GET_sti_rowgethaschanged(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_rowgethaschanged(p0) 
	#define CHK_sti_rowgethaschanged  FALSE
	#define EXP_sti_rowgethaschanged  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_rowgethaschanged
	#define EXT_sti_rowgethaschanged
	#define GET_sti_rowgethaschanged(fl)  CAL_CMGETAPI( "sti_rowgethaschanged" ) 
	#define CAL_sti_rowgethaschanged  sti_rowgethaschanged
	#define CHK_sti_rowgethaschanged  TRUE
	#define EXP_sti_rowgethaschanged  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgethaschanged", (RTS_UINTPTR)sti_rowgethaschanged, 1, RTSITF_GET_SIGNATURE(0, 0xF6C794AA), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_rowgethaschanged
	#define EXT_sti_rowgethaschanged
	#define GET_sti_rowgethaschanged(fl)  CAL_CMGETAPI( "sti_rowgethaschanged" ) 
	#define CAL_sti_rowgethaschanged  sti_rowgethaschanged
	#define CHK_sti_rowgethaschanged  TRUE
	#define EXP_sti_rowgethaschanged  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgethaschanged", (RTS_UINTPTR)sti_rowgethaschanged, 1, RTSITF_GET_SIGNATURE(0, 0xF6C794AA), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_rowgethaschanged
	#define EXT_CmpCAAStoragesti_rowgethaschanged
	#define GET_CmpCAAStoragesti_rowgethaschanged  ERR_OK
	#define CAL_CmpCAAStoragesti_rowgethaschanged  sti_rowgethaschanged
	#define CHK_CmpCAAStoragesti_rowgethaschanged  TRUE
	#define EXP_CmpCAAStoragesti_rowgethaschanged  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgethaschanged", (RTS_UINTPTR)sti_rowgethaschanged, 1, RTSITF_GET_SIGNATURE(0, 0xF6C794AA), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_rowgethaschanged
	#define EXT_sti_rowgethaschanged
	#define GET_sti_rowgethaschanged(fl)  CAL_CMGETAPI( "sti_rowgethaschanged" ) 
	#define CAL_sti_rowgethaschanged  sti_rowgethaschanged
	#define CHK_sti_rowgethaschanged  TRUE
	#define EXP_sti_rowgethaschanged  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgethaschanged", (RTS_UINTPTR)sti_rowgethaschanged, 1, RTSITF_GET_SIGNATURE(0, 0xF6C794AA), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_rowgethaschanged  PFSTI_ROWGETHASCHANGED_IEC pfsti_rowgethaschanged;
	#define EXT_sti_rowgethaschanged  extern PFSTI_ROWGETHASCHANGED_IEC pfsti_rowgethaschanged;
	#define GET_sti_rowgethaschanged(fl)  s_pfCMGetAPI2( "sti_rowgethaschanged", (RTS_VOID_FCTPTR *)&pfsti_rowgethaschanged, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xF6C794AA), 0x03050500)
	#define CAL_sti_rowgethaschanged  pfsti_rowgethaschanged
	#define CHK_sti_rowgethaschanged  (pfsti_rowgethaschanged != NULL)
	#define EXP_sti_rowgethaschanged   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgethaschanged", (RTS_UINTPTR)sti_rowgethaschanged, 1, RTSITF_GET_SIGNATURE(0, 0xF6C794AA), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowgetid_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD STI_RowGetId;			/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_rowgetid_struct;

void CDECL CDECL_EXT sti_rowgetid(sti_rowgetid_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_ROWGETID_IEC) (sti_rowgetid_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWGETID_NOTIMPLEMENTED)
	#define USE_sti_rowgetid
	#define EXT_sti_rowgetid
	#define GET_sti_rowgetid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_rowgetid(p0) 
	#define CHK_sti_rowgetid  FALSE
	#define EXP_sti_rowgetid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_rowgetid
	#define EXT_sti_rowgetid
	#define GET_sti_rowgetid(fl)  CAL_CMGETAPI( "sti_rowgetid" ) 
	#define CAL_sti_rowgetid  sti_rowgetid
	#define CHK_sti_rowgetid  TRUE
	#define EXP_sti_rowgetid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgetid", (RTS_UINTPTR)sti_rowgetid, 1, RTSITF_GET_SIGNATURE(0, 0x87759DEC), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_rowgetid
	#define EXT_sti_rowgetid
	#define GET_sti_rowgetid(fl)  CAL_CMGETAPI( "sti_rowgetid" ) 
	#define CAL_sti_rowgetid  sti_rowgetid
	#define CHK_sti_rowgetid  TRUE
	#define EXP_sti_rowgetid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgetid", (RTS_UINTPTR)sti_rowgetid, 1, RTSITF_GET_SIGNATURE(0, 0x87759DEC), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_rowgetid
	#define EXT_CmpCAAStoragesti_rowgetid
	#define GET_CmpCAAStoragesti_rowgetid  ERR_OK
	#define CAL_CmpCAAStoragesti_rowgetid  sti_rowgetid
	#define CHK_CmpCAAStoragesti_rowgetid  TRUE
	#define EXP_CmpCAAStoragesti_rowgetid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgetid", (RTS_UINTPTR)sti_rowgetid, 1, RTSITF_GET_SIGNATURE(0, 0x87759DEC), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_rowgetid
	#define EXT_sti_rowgetid
	#define GET_sti_rowgetid(fl)  CAL_CMGETAPI( "sti_rowgetid" ) 
	#define CAL_sti_rowgetid  sti_rowgetid
	#define CHK_sti_rowgetid  TRUE
	#define EXP_sti_rowgetid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgetid", (RTS_UINTPTR)sti_rowgetid, 1, RTSITF_GET_SIGNATURE(0, 0x87759DEC), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_rowgetid  PFSTI_ROWGETID_IEC pfsti_rowgetid;
	#define EXT_sti_rowgetid  extern PFSTI_ROWGETID_IEC pfsti_rowgetid;
	#define GET_sti_rowgetid(fl)  s_pfCMGetAPI2( "sti_rowgetid", (RTS_VOID_FCTPTR *)&pfsti_rowgetid, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x87759DEC), 0x03050500)
	#define CAL_sti_rowgetid  pfsti_rowgetid
	#define CHK_sti_rowgetid  (pfsti_rowgetid != NULL)
	#define EXP_sti_rowgetid   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgetid", (RTS_UINTPTR)sti_rowgetid, 1, RTSITF_GET_SIGNATURE(0, 0x87759DEC), 0x03050500) 
#endif


/**
 * Replacement of function _RowGetId, that returns a LINT value instead of a CAA.IDENT value.
 */
typedef struct tagsti_rowgetid2_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_LINT STI_RowGetId2;			/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_rowgetid2_struct;

void CDECL CDECL_EXT sti_rowgetid2(sti_rowgetid2_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_ROWGETID2_IEC) (sti_rowgetid2_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWGETID2_NOTIMPLEMENTED)
	#define USE_sti_rowgetid2
	#define EXT_sti_rowgetid2
	#define GET_sti_rowgetid2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_rowgetid2(p0) 
	#define CHK_sti_rowgetid2  FALSE
	#define EXP_sti_rowgetid2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_rowgetid2
	#define EXT_sti_rowgetid2
	#define GET_sti_rowgetid2(fl)  CAL_CMGETAPI( "sti_rowgetid2" ) 
	#define CAL_sti_rowgetid2  sti_rowgetid2
	#define CHK_sti_rowgetid2  TRUE
	#define EXP_sti_rowgetid2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgetid2", (RTS_UINTPTR)sti_rowgetid2, 1, RTSITF_GET_SIGNATURE(0, 0x9E2F89AF), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_rowgetid2
	#define EXT_sti_rowgetid2
	#define GET_sti_rowgetid2(fl)  CAL_CMGETAPI( "sti_rowgetid2" ) 
	#define CAL_sti_rowgetid2  sti_rowgetid2
	#define CHK_sti_rowgetid2  TRUE
	#define EXP_sti_rowgetid2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgetid2", (RTS_UINTPTR)sti_rowgetid2, 1, RTSITF_GET_SIGNATURE(0, 0x9E2F89AF), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_rowgetid2
	#define EXT_CmpCAAStoragesti_rowgetid2
	#define GET_CmpCAAStoragesti_rowgetid2  ERR_OK
	#define CAL_CmpCAAStoragesti_rowgetid2  sti_rowgetid2
	#define CHK_CmpCAAStoragesti_rowgetid2  TRUE
	#define EXP_CmpCAAStoragesti_rowgetid2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgetid2", (RTS_UINTPTR)sti_rowgetid2, 1, RTSITF_GET_SIGNATURE(0, 0x9E2F89AF), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_rowgetid2
	#define EXT_sti_rowgetid2
	#define GET_sti_rowgetid2(fl)  CAL_CMGETAPI( "sti_rowgetid2" ) 
	#define CAL_sti_rowgetid2  sti_rowgetid2
	#define CHK_sti_rowgetid2  TRUE
	#define EXP_sti_rowgetid2  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgetid2", (RTS_UINTPTR)sti_rowgetid2, 1, RTSITF_GET_SIGNATURE(0, 0x9E2F89AF), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_rowgetid2  PFSTI_ROWGETID2_IEC pfsti_rowgetid2;
	#define EXT_sti_rowgetid2  extern PFSTI_ROWGETID2_IEC pfsti_rowgetid2;
	#define GET_sti_rowgetid2(fl)  s_pfCMGetAPI2( "sti_rowgetid2", (RTS_VOID_FCTPTR *)&pfsti_rowgetid2, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x9E2F89AF), 0x03050500)
	#define CAL_sti_rowgetid2  pfsti_rowgetid2
	#define CHK_sti_rowgetid2  (pfsti_rowgetid2 != NULL)
	#define EXP_sti_rowgetid2   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgetid2", (RTS_UINTPTR)sti_rowgetid2, 1, RTSITF_GET_SIGNATURE(0, 0x9E2F89AF), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowgetnumofcolumns_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_UXINT STI_RowGetNumOfColumns;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_rowgetnumofcolumns_struct;

void CDECL CDECL_EXT sti_rowgetnumofcolumns(sti_rowgetnumofcolumns_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_ROWGETNUMOFCOLUMNS_IEC) (sti_rowgetnumofcolumns_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWGETNUMOFCOLUMNS_NOTIMPLEMENTED)
	#define USE_sti_rowgetnumofcolumns
	#define EXT_sti_rowgetnumofcolumns
	#define GET_sti_rowgetnumofcolumns(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_rowgetnumofcolumns(p0) 
	#define CHK_sti_rowgetnumofcolumns  FALSE
	#define EXP_sti_rowgetnumofcolumns  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_rowgetnumofcolumns
	#define EXT_sti_rowgetnumofcolumns
	#define GET_sti_rowgetnumofcolumns(fl)  CAL_CMGETAPI( "sti_rowgetnumofcolumns" ) 
	#define CAL_sti_rowgetnumofcolumns  sti_rowgetnumofcolumns
	#define CHK_sti_rowgetnumofcolumns  TRUE
	#define EXP_sti_rowgetnumofcolumns  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgetnumofcolumns", (RTS_UINTPTR)sti_rowgetnumofcolumns, 1, RTSITF_GET_SIGNATURE(0, 0x6FB61449), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_rowgetnumofcolumns
	#define EXT_sti_rowgetnumofcolumns
	#define GET_sti_rowgetnumofcolumns(fl)  CAL_CMGETAPI( "sti_rowgetnumofcolumns" ) 
	#define CAL_sti_rowgetnumofcolumns  sti_rowgetnumofcolumns
	#define CHK_sti_rowgetnumofcolumns  TRUE
	#define EXP_sti_rowgetnumofcolumns  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgetnumofcolumns", (RTS_UINTPTR)sti_rowgetnumofcolumns, 1, RTSITF_GET_SIGNATURE(0, 0x6FB61449), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_rowgetnumofcolumns
	#define EXT_CmpCAAStoragesti_rowgetnumofcolumns
	#define GET_CmpCAAStoragesti_rowgetnumofcolumns  ERR_OK
	#define CAL_CmpCAAStoragesti_rowgetnumofcolumns  sti_rowgetnumofcolumns
	#define CHK_CmpCAAStoragesti_rowgetnumofcolumns  TRUE
	#define EXP_CmpCAAStoragesti_rowgetnumofcolumns  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgetnumofcolumns", (RTS_UINTPTR)sti_rowgetnumofcolumns, 1, RTSITF_GET_SIGNATURE(0, 0x6FB61449), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_rowgetnumofcolumns
	#define EXT_sti_rowgetnumofcolumns
	#define GET_sti_rowgetnumofcolumns(fl)  CAL_CMGETAPI( "sti_rowgetnumofcolumns" ) 
	#define CAL_sti_rowgetnumofcolumns  sti_rowgetnumofcolumns
	#define CHK_sti_rowgetnumofcolumns  TRUE
	#define EXP_sti_rowgetnumofcolumns  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgetnumofcolumns", (RTS_UINTPTR)sti_rowgetnumofcolumns, 1, RTSITF_GET_SIGNATURE(0, 0x6FB61449), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_rowgetnumofcolumns  PFSTI_ROWGETNUMOFCOLUMNS_IEC pfsti_rowgetnumofcolumns;
	#define EXT_sti_rowgetnumofcolumns  extern PFSTI_ROWGETNUMOFCOLUMNS_IEC pfsti_rowgetnumofcolumns;
	#define GET_sti_rowgetnumofcolumns(fl)  s_pfCMGetAPI2( "sti_rowgetnumofcolumns", (RTS_VOID_FCTPTR *)&pfsti_rowgetnumofcolumns, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x6FB61449), 0x03050500)
	#define CAL_sti_rowgetnumofcolumns  pfsti_rowgetnumofcolumns
	#define CHK_sti_rowgetnumofcolumns  (pfsti_rowgetnumofcolumns != NULL)
	#define EXP_sti_rowgetnumofcolumns   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgetnumofcolumns", (RTS_UINTPTR)sti_rowgetnumofcolumns, 1, RTSITF_GET_SIGNATURE(0, 0x6FB61449), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowgetstorage_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_XWORD STI_RowGetStorage;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_rowgetstorage_struct;

void CDECL CDECL_EXT sti_rowgetstorage(sti_rowgetstorage_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_ROWGETSTORAGE_IEC) (sti_rowgetstorage_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWGETSTORAGE_NOTIMPLEMENTED)
	#define USE_sti_rowgetstorage
	#define EXT_sti_rowgetstorage
	#define GET_sti_rowgetstorage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_rowgetstorage(p0) 
	#define CHK_sti_rowgetstorage  FALSE
	#define EXP_sti_rowgetstorage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_rowgetstorage
	#define EXT_sti_rowgetstorage
	#define GET_sti_rowgetstorage(fl)  CAL_CMGETAPI( "sti_rowgetstorage" ) 
	#define CAL_sti_rowgetstorage  sti_rowgetstorage
	#define CHK_sti_rowgetstorage  TRUE
	#define EXP_sti_rowgetstorage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgetstorage", (RTS_UINTPTR)sti_rowgetstorage, 1, RTSITF_GET_SIGNATURE(0, 0x0D4CCC41), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_rowgetstorage
	#define EXT_sti_rowgetstorage
	#define GET_sti_rowgetstorage(fl)  CAL_CMGETAPI( "sti_rowgetstorage" ) 
	#define CAL_sti_rowgetstorage  sti_rowgetstorage
	#define CHK_sti_rowgetstorage  TRUE
	#define EXP_sti_rowgetstorage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgetstorage", (RTS_UINTPTR)sti_rowgetstorage, 1, RTSITF_GET_SIGNATURE(0, 0x0D4CCC41), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_rowgetstorage
	#define EXT_CmpCAAStoragesti_rowgetstorage
	#define GET_CmpCAAStoragesti_rowgetstorage  ERR_OK
	#define CAL_CmpCAAStoragesti_rowgetstorage  sti_rowgetstorage
	#define CHK_CmpCAAStoragesti_rowgetstorage  TRUE
	#define EXP_CmpCAAStoragesti_rowgetstorage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgetstorage", (RTS_UINTPTR)sti_rowgetstorage, 1, RTSITF_GET_SIGNATURE(0, 0x0D4CCC41), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_rowgetstorage
	#define EXT_sti_rowgetstorage
	#define GET_sti_rowgetstorage(fl)  CAL_CMGETAPI( "sti_rowgetstorage" ) 
	#define CAL_sti_rowgetstorage  sti_rowgetstorage
	#define CHK_sti_rowgetstorage  TRUE
	#define EXP_sti_rowgetstorage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgetstorage", (RTS_UINTPTR)sti_rowgetstorage, 1, RTSITF_GET_SIGNATURE(0, 0x0D4CCC41), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_rowgetstorage  PFSTI_ROWGETSTORAGE_IEC pfsti_rowgetstorage;
	#define EXT_sti_rowgetstorage  extern PFSTI_ROWGETSTORAGE_IEC pfsti_rowgetstorage;
	#define GET_sti_rowgetstorage(fl)  s_pfCMGetAPI2( "sti_rowgetstorage", (RTS_VOID_FCTPTR *)&pfsti_rowgetstorage, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x0D4CCC41), 0x03050500)
	#define CAL_sti_rowgetstorage  pfsti_rowgetstorage
	#define CHK_sti_rowgetstorage  (pfsti_rowgetstorage != NULL)
	#define EXP_sti_rowgetstorage   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgetstorage", (RTS_UINTPTR)sti_rowgetstorage, 1, RTSITF_GET_SIGNATURE(0, 0x0D4CCC41), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowgettable_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_XWORD STI_RowGetTable;		/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_rowgettable_struct;

void CDECL CDECL_EXT sti_rowgettable(sti_rowgettable_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_ROWGETTABLE_IEC) (sti_rowgettable_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWGETTABLE_NOTIMPLEMENTED)
	#define USE_sti_rowgettable
	#define EXT_sti_rowgettable
	#define GET_sti_rowgettable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_rowgettable(p0) 
	#define CHK_sti_rowgettable  FALSE
	#define EXP_sti_rowgettable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_rowgettable
	#define EXT_sti_rowgettable
	#define GET_sti_rowgettable(fl)  CAL_CMGETAPI( "sti_rowgettable" ) 
	#define CAL_sti_rowgettable  sti_rowgettable
	#define CHK_sti_rowgettable  TRUE
	#define EXP_sti_rowgettable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgettable", (RTS_UINTPTR)sti_rowgettable, 1, RTSITF_GET_SIGNATURE(0, 0x8AE45F6C), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_rowgettable
	#define EXT_sti_rowgettable
	#define GET_sti_rowgettable(fl)  CAL_CMGETAPI( "sti_rowgettable" ) 
	#define CAL_sti_rowgettable  sti_rowgettable
	#define CHK_sti_rowgettable  TRUE
	#define EXP_sti_rowgettable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgettable", (RTS_UINTPTR)sti_rowgettable, 1, RTSITF_GET_SIGNATURE(0, 0x8AE45F6C), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_rowgettable
	#define EXT_CmpCAAStoragesti_rowgettable
	#define GET_CmpCAAStoragesti_rowgettable  ERR_OK
	#define CAL_CmpCAAStoragesti_rowgettable  sti_rowgettable
	#define CHK_CmpCAAStoragesti_rowgettable  TRUE
	#define EXP_CmpCAAStoragesti_rowgettable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgettable", (RTS_UINTPTR)sti_rowgettable, 1, RTSITF_GET_SIGNATURE(0, 0x8AE45F6C), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_rowgettable
	#define EXT_sti_rowgettable
	#define GET_sti_rowgettable(fl)  CAL_CMGETAPI( "sti_rowgettable" ) 
	#define CAL_sti_rowgettable  sti_rowgettable
	#define CHK_sti_rowgettable  TRUE
	#define EXP_sti_rowgettable  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgettable", (RTS_UINTPTR)sti_rowgettable, 1, RTSITF_GET_SIGNATURE(0, 0x8AE45F6C), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_rowgettable  PFSTI_ROWGETTABLE_IEC pfsti_rowgettable;
	#define EXT_sti_rowgettable  extern PFSTI_ROWGETTABLE_IEC pfsti_rowgettable;
	#define GET_sti_rowgettable(fl)  s_pfCMGetAPI2( "sti_rowgettable", (RTS_VOID_FCTPTR *)&pfsti_rowgettable, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x8AE45F6C), 0x03050500)
	#define CAL_sti_rowgettable  pfsti_rowgettable
	#define CHK_sti_rowgettable  (pfsti_rowgettable != NULL)
	#define EXP_sti_rowgettable   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowgettable", (RTS_UINTPTR)sti_rowgettable, 1, RTSITF_GET_SIGNATURE(0, 0x8AE45F6C), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowinsert_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_DWORD STI_RowInsert;		/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_rowinsert_struct;

void CDECL CDECL_EXT sti_rowinsert(sti_rowinsert_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_ROWINSERT_IEC) (sti_rowinsert_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWINSERT_NOTIMPLEMENTED)
	#define USE_sti_rowinsert
	#define EXT_sti_rowinsert
	#define GET_sti_rowinsert(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_rowinsert(p0) 
	#define CHK_sti_rowinsert  FALSE
	#define EXP_sti_rowinsert  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_rowinsert
	#define EXT_sti_rowinsert
	#define GET_sti_rowinsert(fl)  CAL_CMGETAPI( "sti_rowinsert" ) 
	#define CAL_sti_rowinsert  sti_rowinsert
	#define CHK_sti_rowinsert  TRUE
	#define EXP_sti_rowinsert  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowinsert", (RTS_UINTPTR)sti_rowinsert, 1, RTSITF_GET_SIGNATURE(0, 0x7C9D2E1E), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_rowinsert
	#define EXT_sti_rowinsert
	#define GET_sti_rowinsert(fl)  CAL_CMGETAPI( "sti_rowinsert" ) 
	#define CAL_sti_rowinsert  sti_rowinsert
	#define CHK_sti_rowinsert  TRUE
	#define EXP_sti_rowinsert  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowinsert", (RTS_UINTPTR)sti_rowinsert, 1, RTSITF_GET_SIGNATURE(0, 0x7C9D2E1E), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_rowinsert
	#define EXT_CmpCAAStoragesti_rowinsert
	#define GET_CmpCAAStoragesti_rowinsert  ERR_OK
	#define CAL_CmpCAAStoragesti_rowinsert  sti_rowinsert
	#define CHK_CmpCAAStoragesti_rowinsert  TRUE
	#define EXP_CmpCAAStoragesti_rowinsert  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowinsert", (RTS_UINTPTR)sti_rowinsert, 1, RTSITF_GET_SIGNATURE(0, 0x7C9D2E1E), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_rowinsert
	#define EXT_sti_rowinsert
	#define GET_sti_rowinsert(fl)  CAL_CMGETAPI( "sti_rowinsert" ) 
	#define CAL_sti_rowinsert  sti_rowinsert
	#define CHK_sti_rowinsert  TRUE
	#define EXP_sti_rowinsert  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowinsert", (RTS_UINTPTR)sti_rowinsert, 1, RTSITF_GET_SIGNATURE(0, 0x7C9D2E1E), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_rowinsert  PFSTI_ROWINSERT_IEC pfsti_rowinsert;
	#define EXT_sti_rowinsert  extern PFSTI_ROWINSERT_IEC pfsti_rowinsert;
	#define GET_sti_rowinsert(fl)  s_pfCMGetAPI2( "sti_rowinsert", (RTS_VOID_FCTPTR *)&pfsti_rowinsert, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x7C9D2E1E), 0x03050500)
	#define CAL_sti_rowinsert  pfsti_rowinsert
	#define CHK_sti_rowinsert  (pfsti_rowinsert != NULL)
	#define EXP_sti_rowinsert   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowinsert", (RTS_UINTPTR)sti_rowinsert, 1, RTSITF_GET_SIGNATURE(0, 0x7C9D2E1E), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowrelease_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_INT STI_RowRelease;			/* VAR_OUTPUT, Enum: ERROR */
} sti_rowrelease_struct;

void CDECL CDECL_EXT sti_rowrelease(sti_rowrelease_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_ROWRELEASE_IEC) (sti_rowrelease_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWRELEASE_NOTIMPLEMENTED)
	#define USE_sti_rowrelease
	#define EXT_sti_rowrelease
	#define GET_sti_rowrelease(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_rowrelease(p0) 
	#define CHK_sti_rowrelease  FALSE
	#define EXP_sti_rowrelease  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_rowrelease
	#define EXT_sti_rowrelease
	#define GET_sti_rowrelease(fl)  CAL_CMGETAPI( "sti_rowrelease" ) 
	#define CAL_sti_rowrelease  sti_rowrelease
	#define CHK_sti_rowrelease  TRUE
	#define EXP_sti_rowrelease  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowrelease", (RTS_UINTPTR)sti_rowrelease, 1, RTSITF_GET_SIGNATURE(0, 0x56095635), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_rowrelease
	#define EXT_sti_rowrelease
	#define GET_sti_rowrelease(fl)  CAL_CMGETAPI( "sti_rowrelease" ) 
	#define CAL_sti_rowrelease  sti_rowrelease
	#define CHK_sti_rowrelease  TRUE
	#define EXP_sti_rowrelease  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowrelease", (RTS_UINTPTR)sti_rowrelease, 1, RTSITF_GET_SIGNATURE(0, 0x56095635), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_rowrelease
	#define EXT_CmpCAAStoragesti_rowrelease
	#define GET_CmpCAAStoragesti_rowrelease  ERR_OK
	#define CAL_CmpCAAStoragesti_rowrelease  sti_rowrelease
	#define CHK_CmpCAAStoragesti_rowrelease  TRUE
	#define EXP_CmpCAAStoragesti_rowrelease  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowrelease", (RTS_UINTPTR)sti_rowrelease, 1, RTSITF_GET_SIGNATURE(0, 0x56095635), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_rowrelease
	#define EXT_sti_rowrelease
	#define GET_sti_rowrelease(fl)  CAL_CMGETAPI( "sti_rowrelease" ) 
	#define CAL_sti_rowrelease  sti_rowrelease
	#define CHK_sti_rowrelease  TRUE
	#define EXP_sti_rowrelease  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowrelease", (RTS_UINTPTR)sti_rowrelease, 1, RTSITF_GET_SIGNATURE(0, 0x56095635), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_rowrelease  PFSTI_ROWRELEASE_IEC pfsti_rowrelease;
	#define EXT_sti_rowrelease  extern PFSTI_ROWRELEASE_IEC pfsti_rowrelease;
	#define GET_sti_rowrelease(fl)  s_pfCMGetAPI2( "sti_rowrelease", (RTS_VOID_FCTPTR *)&pfsti_rowrelease, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x56095635), 0x03050500)
	#define CAL_sti_rowrelease  pfsti_rowrelease
	#define CHK_sti_rowrelease  (pfsti_rowrelease != NULL)
	#define EXP_sti_rowrelease   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowrelease", (RTS_UINTPTR)sti_rowrelease, 1, RTSITF_GET_SIGNATURE(0, 0x56095635), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_rowselect(sti_rowselect_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_ROWSELECT_IEC) (sti_rowselect_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWSELECT_NOTIMPLEMENTED)
	#define USE_sti_rowselect
	#define EXT_sti_rowselect
	#define GET_sti_rowselect(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_rowselect(p0) 
	#define CHK_sti_rowselect  FALSE
	#define EXP_sti_rowselect  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_rowselect
	#define EXT_sti_rowselect
	#define GET_sti_rowselect(fl)  CAL_CMGETAPI( "sti_rowselect" ) 
	#define CAL_sti_rowselect  sti_rowselect
	#define CHK_sti_rowselect  TRUE
	#define EXP_sti_rowselect  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowselect", (RTS_UINTPTR)sti_rowselect, 1, RTSITF_GET_SIGNATURE(0, 0x16DC3998), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_rowselect
	#define EXT_sti_rowselect
	#define GET_sti_rowselect(fl)  CAL_CMGETAPI( "sti_rowselect" ) 
	#define CAL_sti_rowselect  sti_rowselect
	#define CHK_sti_rowselect  TRUE
	#define EXP_sti_rowselect  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowselect", (RTS_UINTPTR)sti_rowselect, 1, RTSITF_GET_SIGNATURE(0, 0x16DC3998), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_rowselect
	#define EXT_CmpCAAStoragesti_rowselect
	#define GET_CmpCAAStoragesti_rowselect  ERR_OK
	#define CAL_CmpCAAStoragesti_rowselect  sti_rowselect
	#define CHK_CmpCAAStoragesti_rowselect  TRUE
	#define EXP_CmpCAAStoragesti_rowselect  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowselect", (RTS_UINTPTR)sti_rowselect, 1, RTSITF_GET_SIGNATURE(0, 0x16DC3998), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_rowselect
	#define EXT_sti_rowselect
	#define GET_sti_rowselect(fl)  CAL_CMGETAPI( "sti_rowselect" ) 
	#define CAL_sti_rowselect  sti_rowselect
	#define CHK_sti_rowselect  TRUE
	#define EXP_sti_rowselect  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowselect", (RTS_UINTPTR)sti_rowselect, 1, RTSITF_GET_SIGNATURE(0, 0x16DC3998), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_rowselect  PFSTI_ROWSELECT_IEC pfsti_rowselect;
	#define EXT_sti_rowselect  extern PFSTI_ROWSELECT_IEC pfsti_rowselect;
	#define GET_sti_rowselect(fl)  s_pfCMGetAPI2( "sti_rowselect", (RTS_VOID_FCTPTR *)&pfsti_rowselect, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x16DC3998), 0x03050500)
	#define CAL_sti_rowselect  pfsti_rowselect
	#define CHK_sti_rowselect  (pfsti_rowselect != NULL)
	#define EXP_sti_rowselect   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowselect", (RTS_UINTPTR)sti_rowselect, 1, RTSITF_GET_SIGNATURE(0, 0x16DC3998), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_rowupdate_struct
{
	RTS_IEC_XWORD hRow;					/* VAR_INPUT */	
	RTS_IEC_INT STI_RowUpdate;			/* VAR_OUTPUT, Enum: ERROR */
} sti_rowupdate_struct;

void CDECL CDECL_EXT sti_rowupdate(sti_rowupdate_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_ROWUPDATE_IEC) (sti_rowupdate_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWUPDATE_NOTIMPLEMENTED)
	#define USE_sti_rowupdate
	#define EXT_sti_rowupdate
	#define GET_sti_rowupdate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_rowupdate(p0) 
	#define CHK_sti_rowupdate  FALSE
	#define EXP_sti_rowupdate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_rowupdate
	#define EXT_sti_rowupdate
	#define GET_sti_rowupdate(fl)  CAL_CMGETAPI( "sti_rowupdate" ) 
	#define CAL_sti_rowupdate  sti_rowupdate
	#define CHK_sti_rowupdate  TRUE
	#define EXP_sti_rowupdate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowupdate", (RTS_UINTPTR)sti_rowupdate, 1, RTSITF_GET_SIGNATURE(0, 0xF8FC45F4), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_rowupdate
	#define EXT_sti_rowupdate
	#define GET_sti_rowupdate(fl)  CAL_CMGETAPI( "sti_rowupdate" ) 
	#define CAL_sti_rowupdate  sti_rowupdate
	#define CHK_sti_rowupdate  TRUE
	#define EXP_sti_rowupdate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowupdate", (RTS_UINTPTR)sti_rowupdate, 1, RTSITF_GET_SIGNATURE(0, 0xF8FC45F4), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_rowupdate
	#define EXT_CmpCAAStoragesti_rowupdate
	#define GET_CmpCAAStoragesti_rowupdate  ERR_OK
	#define CAL_CmpCAAStoragesti_rowupdate  sti_rowupdate
	#define CHK_CmpCAAStoragesti_rowupdate  TRUE
	#define EXP_CmpCAAStoragesti_rowupdate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowupdate", (RTS_UINTPTR)sti_rowupdate, 1, RTSITF_GET_SIGNATURE(0, 0xF8FC45F4), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_rowupdate
	#define EXT_sti_rowupdate
	#define GET_sti_rowupdate(fl)  CAL_CMGETAPI( "sti_rowupdate" ) 
	#define CAL_sti_rowupdate  sti_rowupdate
	#define CHK_sti_rowupdate  TRUE
	#define EXP_sti_rowupdate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowupdate", (RTS_UINTPTR)sti_rowupdate, 1, RTSITF_GET_SIGNATURE(0, 0xF8FC45F4), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_rowupdate  PFSTI_ROWUPDATE_IEC pfsti_rowupdate;
	#define EXT_sti_rowupdate  extern PFSTI_ROWUPDATE_IEC pfsti_rowupdate;
	#define GET_sti_rowupdate(fl)  s_pfCMGetAPI2( "sti_rowupdate", (RTS_VOID_FCTPTR *)&pfsti_rowupdate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xF8FC45F4), 0x03050500)
	#define CAL_sti_rowupdate  pfsti_rowupdate
	#define CHK_sti_rowupdate  (pfsti_rowupdate != NULL)
	#define EXP_sti_rowupdate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_rowupdate", (RTS_UINTPTR)sti_rowupdate, 1, RTSITF_GET_SIGNATURE(0, 0xF8FC45F4), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_savepointgetstorage_struct
{
	RTS_IEC_XWORD hSavepoint;			/* VAR_INPUT */	
	RTS_IEC_XWORD STI_SavepointGetStorage;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_savepointgetstorage_struct;

void CDECL CDECL_EXT sti_savepointgetstorage(sti_savepointgetstorage_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_SAVEPOINTGETSTORAGE_IEC) (sti_savepointgetstorage_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_SAVEPOINTGETSTORAGE_NOTIMPLEMENTED)
	#define USE_sti_savepointgetstorage
	#define EXT_sti_savepointgetstorage
	#define GET_sti_savepointgetstorage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_savepointgetstorage(p0) 
	#define CHK_sti_savepointgetstorage  FALSE
	#define EXP_sti_savepointgetstorage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_savepointgetstorage
	#define EXT_sti_savepointgetstorage
	#define GET_sti_savepointgetstorage(fl)  CAL_CMGETAPI( "sti_savepointgetstorage" ) 
	#define CAL_sti_savepointgetstorage  sti_savepointgetstorage
	#define CHK_sti_savepointgetstorage  TRUE
	#define EXP_sti_savepointgetstorage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_savepointgetstorage", (RTS_UINTPTR)sti_savepointgetstorage, 1, RTSITF_GET_SIGNATURE(0, 0x690912D3), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_savepointgetstorage
	#define EXT_sti_savepointgetstorage
	#define GET_sti_savepointgetstorage(fl)  CAL_CMGETAPI( "sti_savepointgetstorage" ) 
	#define CAL_sti_savepointgetstorage  sti_savepointgetstorage
	#define CHK_sti_savepointgetstorage  TRUE
	#define EXP_sti_savepointgetstorage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_savepointgetstorage", (RTS_UINTPTR)sti_savepointgetstorage, 1, RTSITF_GET_SIGNATURE(0, 0x690912D3), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_savepointgetstorage
	#define EXT_CmpCAAStoragesti_savepointgetstorage
	#define GET_CmpCAAStoragesti_savepointgetstorage  ERR_OK
	#define CAL_CmpCAAStoragesti_savepointgetstorage  sti_savepointgetstorage
	#define CHK_CmpCAAStoragesti_savepointgetstorage  TRUE
	#define EXP_CmpCAAStoragesti_savepointgetstorage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_savepointgetstorage", (RTS_UINTPTR)sti_savepointgetstorage, 1, RTSITF_GET_SIGNATURE(0, 0x690912D3), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_savepointgetstorage
	#define EXT_sti_savepointgetstorage
	#define GET_sti_savepointgetstorage(fl)  CAL_CMGETAPI( "sti_savepointgetstorage" ) 
	#define CAL_sti_savepointgetstorage  sti_savepointgetstorage
	#define CHK_sti_savepointgetstorage  TRUE
	#define EXP_sti_savepointgetstorage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_savepointgetstorage", (RTS_UINTPTR)sti_savepointgetstorage, 1, RTSITF_GET_SIGNATURE(0, 0x690912D3), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_savepointgetstorage  PFSTI_SAVEPOINTGETSTORAGE_IEC pfsti_savepointgetstorage;
	#define EXT_sti_savepointgetstorage  extern PFSTI_SAVEPOINTGETSTORAGE_IEC pfsti_savepointgetstorage;
	#define GET_sti_savepointgetstorage(fl)  s_pfCMGetAPI2( "sti_savepointgetstorage", (RTS_VOID_FCTPTR *)&pfsti_savepointgetstorage, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x690912D3), 0x03050500)
	#define CAL_sti_savepointgetstorage  pfsti_savepointgetstorage
	#define CHK_sti_savepointgetstorage  (pfsti_savepointgetstorage != NULL)
	#define EXP_sti_savepointgetstorage   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_savepointgetstorage", (RTS_UINTPTR)sti_savepointgetstorage, 1, RTSITF_GET_SIGNATURE(0, 0x690912D3), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_savepointgettransaction_struct
{
	RTS_IEC_XWORD hSavepoint;			/* VAR_INPUT */	
	RTS_IEC_XWORD STI_SavepointGetTransaction;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_savepointgettransaction_struct;

void CDECL CDECL_EXT sti_savepointgettransaction(sti_savepointgettransaction_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_SAVEPOINTGETTRANSACTION_IEC) (sti_savepointgettransaction_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_SAVEPOINTGETTRANSACTION_NOTIMPLEMENTED)
	#define USE_sti_savepointgettransaction
	#define EXT_sti_savepointgettransaction
	#define GET_sti_savepointgettransaction(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_savepointgettransaction(p0) 
	#define CHK_sti_savepointgettransaction  FALSE
	#define EXP_sti_savepointgettransaction  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_savepointgettransaction
	#define EXT_sti_savepointgettransaction
	#define GET_sti_savepointgettransaction(fl)  CAL_CMGETAPI( "sti_savepointgettransaction" ) 
	#define CAL_sti_savepointgettransaction  sti_savepointgettransaction
	#define CHK_sti_savepointgettransaction  TRUE
	#define EXP_sti_savepointgettransaction  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_savepointgettransaction", (RTS_UINTPTR)sti_savepointgettransaction, 1, RTSITF_GET_SIGNATURE(0, 0xE3ACA44B), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_savepointgettransaction
	#define EXT_sti_savepointgettransaction
	#define GET_sti_savepointgettransaction(fl)  CAL_CMGETAPI( "sti_savepointgettransaction" ) 
	#define CAL_sti_savepointgettransaction  sti_savepointgettransaction
	#define CHK_sti_savepointgettransaction  TRUE
	#define EXP_sti_savepointgettransaction  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_savepointgettransaction", (RTS_UINTPTR)sti_savepointgettransaction, 1, RTSITF_GET_SIGNATURE(0, 0xE3ACA44B), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_savepointgettransaction
	#define EXT_CmpCAAStoragesti_savepointgettransaction
	#define GET_CmpCAAStoragesti_savepointgettransaction  ERR_OK
	#define CAL_CmpCAAStoragesti_savepointgettransaction  sti_savepointgettransaction
	#define CHK_CmpCAAStoragesti_savepointgettransaction  TRUE
	#define EXP_CmpCAAStoragesti_savepointgettransaction  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_savepointgettransaction", (RTS_UINTPTR)sti_savepointgettransaction, 1, RTSITF_GET_SIGNATURE(0, 0xE3ACA44B), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_savepointgettransaction
	#define EXT_sti_savepointgettransaction
	#define GET_sti_savepointgettransaction(fl)  CAL_CMGETAPI( "sti_savepointgettransaction" ) 
	#define CAL_sti_savepointgettransaction  sti_savepointgettransaction
	#define CHK_sti_savepointgettransaction  TRUE
	#define EXP_sti_savepointgettransaction  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_savepointgettransaction", (RTS_UINTPTR)sti_savepointgettransaction, 1, RTSITF_GET_SIGNATURE(0, 0xE3ACA44B), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_savepointgettransaction  PFSTI_SAVEPOINTGETTRANSACTION_IEC pfsti_savepointgettransaction;
	#define EXT_sti_savepointgettransaction  extern PFSTI_SAVEPOINTGETTRANSACTION_IEC pfsti_savepointgettransaction;
	#define GET_sti_savepointgettransaction(fl)  s_pfCMGetAPI2( "sti_savepointgettransaction", (RTS_VOID_FCTPTR *)&pfsti_savepointgettransaction, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xE3ACA44B), 0x03050500)
	#define CAL_sti_savepointgettransaction  pfsti_savepointgettransaction
	#define CHK_sti_savepointgettransaction  (pfsti_savepointgettransaction != NULL)
	#define EXP_sti_savepointgettransaction   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_savepointgettransaction", (RTS_UINTPTR)sti_savepointgettransaction, 1, RTSITF_GET_SIGNATURE(0, 0xE3ACA44B), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_savepointrelease_struct
{
	RTS_IEC_XWORD hSavePoint;			/* VAR_INPUT */	
	RTS_IEC_INT STI_SavepointRelease;	/* VAR_OUTPUT, Enum: ERROR */
} sti_savepointrelease_struct;

void CDECL CDECL_EXT sti_savepointrelease(sti_savepointrelease_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_SAVEPOINTRELEASE_IEC) (sti_savepointrelease_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_SAVEPOINTRELEASE_NOTIMPLEMENTED)
	#define USE_sti_savepointrelease
	#define EXT_sti_savepointrelease
	#define GET_sti_savepointrelease(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_savepointrelease(p0) 
	#define CHK_sti_savepointrelease  FALSE
	#define EXP_sti_savepointrelease  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_savepointrelease
	#define EXT_sti_savepointrelease
	#define GET_sti_savepointrelease(fl)  CAL_CMGETAPI( "sti_savepointrelease" ) 
	#define CAL_sti_savepointrelease  sti_savepointrelease
	#define CHK_sti_savepointrelease  TRUE
	#define EXP_sti_savepointrelease  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_savepointrelease", (RTS_UINTPTR)sti_savepointrelease, 1, RTSITF_GET_SIGNATURE(0, 0x8F42C66A), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_savepointrelease
	#define EXT_sti_savepointrelease
	#define GET_sti_savepointrelease(fl)  CAL_CMGETAPI( "sti_savepointrelease" ) 
	#define CAL_sti_savepointrelease  sti_savepointrelease
	#define CHK_sti_savepointrelease  TRUE
	#define EXP_sti_savepointrelease  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_savepointrelease", (RTS_UINTPTR)sti_savepointrelease, 1, RTSITF_GET_SIGNATURE(0, 0x8F42C66A), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_savepointrelease
	#define EXT_CmpCAAStoragesti_savepointrelease
	#define GET_CmpCAAStoragesti_savepointrelease  ERR_OK
	#define CAL_CmpCAAStoragesti_savepointrelease  sti_savepointrelease
	#define CHK_CmpCAAStoragesti_savepointrelease  TRUE
	#define EXP_CmpCAAStoragesti_savepointrelease  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_savepointrelease", (RTS_UINTPTR)sti_savepointrelease, 1, RTSITF_GET_SIGNATURE(0, 0x8F42C66A), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_savepointrelease
	#define EXT_sti_savepointrelease
	#define GET_sti_savepointrelease(fl)  CAL_CMGETAPI( "sti_savepointrelease" ) 
	#define CAL_sti_savepointrelease  sti_savepointrelease
	#define CHK_sti_savepointrelease  TRUE
	#define EXP_sti_savepointrelease  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_savepointrelease", (RTS_UINTPTR)sti_savepointrelease, 1, RTSITF_GET_SIGNATURE(0, 0x8F42C66A), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_savepointrelease  PFSTI_SAVEPOINTRELEASE_IEC pfsti_savepointrelease;
	#define EXT_sti_savepointrelease  extern PFSTI_SAVEPOINTRELEASE_IEC pfsti_savepointrelease;
	#define GET_sti_savepointrelease(fl)  s_pfCMGetAPI2( "sti_savepointrelease", (RTS_VOID_FCTPTR *)&pfsti_savepointrelease, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x8F42C66A), 0x03050500)
	#define CAL_sti_savepointrelease  pfsti_savepointrelease
	#define CHK_sti_savepointrelease  (pfsti_savepointrelease != NULL)
	#define EXP_sti_savepointrelease   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_savepointrelease", (RTS_UINTPTR)sti_savepointrelease, 1, RTSITF_GET_SIGNATURE(0, 0x8F42C66A), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_savepointrollback_struct
{
	RTS_IEC_XWORD hSavePoint;			/* VAR_INPUT */	
	RTS_IEC_INT STI_SavepointRollback;	/* VAR_OUTPUT, Enum: ERROR */
} sti_savepointrollback_struct;

void CDECL CDECL_EXT sti_savepointrollback(sti_savepointrollback_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_SAVEPOINTROLLBACK_IEC) (sti_savepointrollback_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_SAVEPOINTROLLBACK_NOTIMPLEMENTED)
	#define USE_sti_savepointrollback
	#define EXT_sti_savepointrollback
	#define GET_sti_savepointrollback(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_savepointrollback(p0) 
	#define CHK_sti_savepointrollback  FALSE
	#define EXP_sti_savepointrollback  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_savepointrollback
	#define EXT_sti_savepointrollback
	#define GET_sti_savepointrollback(fl)  CAL_CMGETAPI( "sti_savepointrollback" ) 
	#define CAL_sti_savepointrollback  sti_savepointrollback
	#define CHK_sti_savepointrollback  TRUE
	#define EXP_sti_savepointrollback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_savepointrollback", (RTS_UINTPTR)sti_savepointrollback, 1, RTSITF_GET_SIGNATURE(0, 0x931C149B), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_savepointrollback
	#define EXT_sti_savepointrollback
	#define GET_sti_savepointrollback(fl)  CAL_CMGETAPI( "sti_savepointrollback" ) 
	#define CAL_sti_savepointrollback  sti_savepointrollback
	#define CHK_sti_savepointrollback  TRUE
	#define EXP_sti_savepointrollback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_savepointrollback", (RTS_UINTPTR)sti_savepointrollback, 1, RTSITF_GET_SIGNATURE(0, 0x931C149B), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_savepointrollback
	#define EXT_CmpCAAStoragesti_savepointrollback
	#define GET_CmpCAAStoragesti_savepointrollback  ERR_OK
	#define CAL_CmpCAAStoragesti_savepointrollback  sti_savepointrollback
	#define CHK_CmpCAAStoragesti_savepointrollback  TRUE
	#define EXP_CmpCAAStoragesti_savepointrollback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_savepointrollback", (RTS_UINTPTR)sti_savepointrollback, 1, RTSITF_GET_SIGNATURE(0, 0x931C149B), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_savepointrollback
	#define EXT_sti_savepointrollback
	#define GET_sti_savepointrollback(fl)  CAL_CMGETAPI( "sti_savepointrollback" ) 
	#define CAL_sti_savepointrollback  sti_savepointrollback
	#define CHK_sti_savepointrollback  TRUE
	#define EXP_sti_savepointrollback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_savepointrollback", (RTS_UINTPTR)sti_savepointrollback, 1, RTSITF_GET_SIGNATURE(0, 0x931C149B), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_savepointrollback  PFSTI_SAVEPOINTROLLBACK_IEC pfsti_savepointrollback;
	#define EXT_sti_savepointrollback  extern PFSTI_SAVEPOINTROLLBACK_IEC pfsti_savepointrollback;
	#define GET_sti_savepointrollback(fl)  s_pfCMGetAPI2( "sti_savepointrollback", (RTS_VOID_FCTPTR *)&pfsti_savepointrollback, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x931C149B), 0x03050500)
	#define CAL_sti_savepointrollback  pfsti_savepointrollback
	#define CHK_sti_savepointrollback  (pfsti_savepointrollback != NULL)
	#define EXP_sti_savepointrollback   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_savepointrollback", (RTS_UINTPTR)sti_savepointrollback, 1, RTSITF_GET_SIGNATURE(0, 0x931C149B), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storageclear_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_INT STI_StorageClear;		/* VAR_OUTPUT, Enum: ERROR */
} sti_storageclear_struct;

void CDECL CDECL_EXT sti_storageclear(sti_storageclear_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_STORAGECLEAR_IEC) (sti_storageclear_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGECLEAR_NOTIMPLEMENTED)
	#define USE_sti_storageclear
	#define EXT_sti_storageclear
	#define GET_sti_storageclear(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_storageclear(p0) 
	#define CHK_sti_storageclear  FALSE
	#define EXP_sti_storageclear  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_storageclear
	#define EXT_sti_storageclear
	#define GET_sti_storageclear(fl)  CAL_CMGETAPI( "sti_storageclear" ) 
	#define CAL_sti_storageclear  sti_storageclear
	#define CHK_sti_storageclear  TRUE
	#define EXP_sti_storageclear  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageclear", (RTS_UINTPTR)sti_storageclear, 1, RTSITF_GET_SIGNATURE(0, 0x15CD03F3), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_storageclear
	#define EXT_sti_storageclear
	#define GET_sti_storageclear(fl)  CAL_CMGETAPI( "sti_storageclear" ) 
	#define CAL_sti_storageclear  sti_storageclear
	#define CHK_sti_storageclear  TRUE
	#define EXP_sti_storageclear  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageclear", (RTS_UINTPTR)sti_storageclear, 1, RTSITF_GET_SIGNATURE(0, 0x15CD03F3), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_storageclear
	#define EXT_CmpCAAStoragesti_storageclear
	#define GET_CmpCAAStoragesti_storageclear  ERR_OK
	#define CAL_CmpCAAStoragesti_storageclear  sti_storageclear
	#define CHK_CmpCAAStoragesti_storageclear  TRUE
	#define EXP_CmpCAAStoragesti_storageclear  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageclear", (RTS_UINTPTR)sti_storageclear, 1, RTSITF_GET_SIGNATURE(0, 0x15CD03F3), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_storageclear
	#define EXT_sti_storageclear
	#define GET_sti_storageclear(fl)  CAL_CMGETAPI( "sti_storageclear" ) 
	#define CAL_sti_storageclear  sti_storageclear
	#define CHK_sti_storageclear  TRUE
	#define EXP_sti_storageclear  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageclear", (RTS_UINTPTR)sti_storageclear, 1, RTSITF_GET_SIGNATURE(0, 0x15CD03F3), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_storageclear  PFSTI_STORAGECLEAR_IEC pfsti_storageclear;
	#define EXT_sti_storageclear  extern PFSTI_STORAGECLEAR_IEC pfsti_storageclear;
	#define GET_sti_storageclear(fl)  s_pfCMGetAPI2( "sti_storageclear", (RTS_VOID_FCTPTR *)&pfsti_storageclear, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x15CD03F3), 0x03050500)
	#define CAL_sti_storageclear  pfsti_storageclear
	#define CHK_sti_storageclear  (pfsti_storageclear != NULL)
	#define EXP_sti_storageclear   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageclear", (RTS_UINTPTR)sti_storageclear, 1, RTSITF_GET_SIGNATURE(0, 0x15CD03F3), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storageclose_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_INT STI_StorageClose;		/* VAR_OUTPUT, Enum: ERROR */
} sti_storageclose_struct;

void CDECL CDECL_EXT sti_storageclose(sti_storageclose_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_STORAGECLOSE_IEC) (sti_storageclose_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGECLOSE_NOTIMPLEMENTED)
	#define USE_sti_storageclose
	#define EXT_sti_storageclose
	#define GET_sti_storageclose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_storageclose(p0) 
	#define CHK_sti_storageclose  FALSE
	#define EXP_sti_storageclose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_storageclose
	#define EXT_sti_storageclose
	#define GET_sti_storageclose(fl)  CAL_CMGETAPI( "sti_storageclose" ) 
	#define CAL_sti_storageclose  sti_storageclose
	#define CHK_sti_storageclose  TRUE
	#define EXP_sti_storageclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageclose", (RTS_UINTPTR)sti_storageclose, 1, RTSITF_GET_SIGNATURE(0, 0x168E35B2), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_storageclose
	#define EXT_sti_storageclose
	#define GET_sti_storageclose(fl)  CAL_CMGETAPI( "sti_storageclose" ) 
	#define CAL_sti_storageclose  sti_storageclose
	#define CHK_sti_storageclose  TRUE
	#define EXP_sti_storageclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageclose", (RTS_UINTPTR)sti_storageclose, 1, RTSITF_GET_SIGNATURE(0, 0x168E35B2), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_storageclose
	#define EXT_CmpCAAStoragesti_storageclose
	#define GET_CmpCAAStoragesti_storageclose  ERR_OK
	#define CAL_CmpCAAStoragesti_storageclose  sti_storageclose
	#define CHK_CmpCAAStoragesti_storageclose  TRUE
	#define EXP_CmpCAAStoragesti_storageclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageclose", (RTS_UINTPTR)sti_storageclose, 1, RTSITF_GET_SIGNATURE(0, 0x168E35B2), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_storageclose
	#define EXT_sti_storageclose
	#define GET_sti_storageclose(fl)  CAL_CMGETAPI( "sti_storageclose" ) 
	#define CAL_sti_storageclose  sti_storageclose
	#define CHK_sti_storageclose  TRUE
	#define EXP_sti_storageclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageclose", (RTS_UINTPTR)sti_storageclose, 1, RTSITF_GET_SIGNATURE(0, 0x168E35B2), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_storageclose  PFSTI_STORAGECLOSE_IEC pfsti_storageclose;
	#define EXT_sti_storageclose  extern PFSTI_STORAGECLOSE_IEC pfsti_storageclose;
	#define GET_sti_storageclose(fl)  s_pfCMGetAPI2( "sti_storageclose", (RTS_VOID_FCTPTR *)&pfsti_storageclose, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x168E35B2), 0x03050500)
	#define CAL_sti_storageclose  pfsti_storageclose
	#define CHK_sti_storageclose  (pfsti_storageclose != NULL)
	#define EXP_sti_storageclose   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageclose", (RTS_UINTPTR)sti_storageclose, 1, RTSITF_GET_SIGNATURE(0, 0x168E35B2), 0x03050500) 
#endif


/**
 * <description>sti_storageexecutestatement</description>
 */
typedef struct tagsti_storageexecutestatement_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_STRING *sStatement;			/* VAR_IN_OUT */	
	RTS_IEC_INT sti_storageexecutestatement;	/* VAR_OUTPUT, Enum: ERROR */
} sti_storageexecutestatement_struct;

void CDECL CDECL_EXT sti_storageexecutestatement(sti_storageexecutestatement_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_STORAGEEXECUTESTATEMENT_IEC) (sti_storageexecutestatement_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEEXECUTESTATEMENT_NOTIMPLEMENTED)
	#define USE_sti_storageexecutestatement
	#define EXT_sti_storageexecutestatement
	#define GET_sti_storageexecutestatement(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_storageexecutestatement(p0) 
	#define CHK_sti_storageexecutestatement  FALSE
	#define EXP_sti_storageexecutestatement  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_storageexecutestatement
	#define EXT_sti_storageexecutestatement
	#define GET_sti_storageexecutestatement(fl)  CAL_CMGETAPI( "sti_storageexecutestatement" ) 
	#define CAL_sti_storageexecutestatement  sti_storageexecutestatement
	#define CHK_sti_storageexecutestatement  TRUE
	#define EXP_sti_storageexecutestatement  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageexecutestatement", (RTS_UINTPTR)sti_storageexecutestatement, 1, RTSITF_GET_SIGNATURE(0x28B52F50, 0xC3FDFD07), 0x03050C00) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_storageexecutestatement
	#define EXT_sti_storageexecutestatement
	#define GET_sti_storageexecutestatement(fl)  CAL_CMGETAPI( "sti_storageexecutestatement" ) 
	#define CAL_sti_storageexecutestatement  sti_storageexecutestatement
	#define CHK_sti_storageexecutestatement  TRUE
	#define EXP_sti_storageexecutestatement  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageexecutestatement", (RTS_UINTPTR)sti_storageexecutestatement, 1, RTSITF_GET_SIGNATURE(0x28B52F50, 0xC3FDFD07), 0x03050C00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_storageexecutestatement
	#define EXT_CmpCAAStoragesti_storageexecutestatement
	#define GET_CmpCAAStoragesti_storageexecutestatement  ERR_OK
	#define CAL_CmpCAAStoragesti_storageexecutestatement  sti_storageexecutestatement
	#define CHK_CmpCAAStoragesti_storageexecutestatement  TRUE
	#define EXP_CmpCAAStoragesti_storageexecutestatement  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageexecutestatement", (RTS_UINTPTR)sti_storageexecutestatement, 1, RTSITF_GET_SIGNATURE(0x28B52F50, 0xC3FDFD07), 0x03050C00) 
#elif defined(CPLUSPLUS)
	#define USE_sti_storageexecutestatement
	#define EXT_sti_storageexecutestatement
	#define GET_sti_storageexecutestatement(fl)  CAL_CMGETAPI( "sti_storageexecutestatement" ) 
	#define CAL_sti_storageexecutestatement  sti_storageexecutestatement
	#define CHK_sti_storageexecutestatement  TRUE
	#define EXP_sti_storageexecutestatement  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageexecutestatement", (RTS_UINTPTR)sti_storageexecutestatement, 1, RTSITF_GET_SIGNATURE(0x28B52F50, 0xC3FDFD07), 0x03050C00) 
#else /* DYNAMIC_LINK */
	#define USE_sti_storageexecutestatement  PFSTI_STORAGEEXECUTESTATEMENT_IEC pfsti_storageexecutestatement;
	#define EXT_sti_storageexecutestatement  extern PFSTI_STORAGEEXECUTESTATEMENT_IEC pfsti_storageexecutestatement;
	#define GET_sti_storageexecutestatement(fl)  s_pfCMGetAPI2( "sti_storageexecutestatement", (RTS_VOID_FCTPTR *)&pfsti_storageexecutestatement, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0x28B52F50, 0xC3FDFD07), 0x03050C00)
	#define CAL_sti_storageexecutestatement  pfsti_storageexecutestatement
	#define CHK_sti_storageexecutestatement  (pfsti_storageexecutestatement != NULL)
	#define EXP_sti_storageexecutestatement   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageexecutestatement", (RTS_UINTPTR)sti_storageexecutestatement, 1, RTSITF_GET_SIGNATURE(0x28B52F50, 0xC3FDFD07), 0x03050C00) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storagegetencoding_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_INT STI_StorageGetEncoding;	/* VAR_OUTPUT, Enum: ENCODING */
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_storagegetencoding_struct;

void CDECL CDECL_EXT sti_storagegetencoding(sti_storagegetencoding_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_STORAGEGETENCODING_IEC) (sti_storagegetencoding_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEGETENCODING_NOTIMPLEMENTED)
	#define USE_sti_storagegetencoding
	#define EXT_sti_storagegetencoding
	#define GET_sti_storagegetencoding(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_storagegetencoding(p0) 
	#define CHK_sti_storagegetencoding  FALSE
	#define EXP_sti_storagegetencoding  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_storagegetencoding
	#define EXT_sti_storagegetencoding
	#define GET_sti_storagegetencoding(fl)  CAL_CMGETAPI( "sti_storagegetencoding" ) 
	#define CAL_sti_storagegetencoding  sti_storagegetencoding
	#define CHK_sti_storagegetencoding  TRUE
	#define EXP_sti_storagegetencoding  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetencoding", (RTS_UINTPTR)sti_storagegetencoding, 1, RTSITF_GET_SIGNATURE(0, 0xBE199139), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_storagegetencoding
	#define EXT_sti_storagegetencoding
	#define GET_sti_storagegetencoding(fl)  CAL_CMGETAPI( "sti_storagegetencoding" ) 
	#define CAL_sti_storagegetencoding  sti_storagegetencoding
	#define CHK_sti_storagegetencoding  TRUE
	#define EXP_sti_storagegetencoding  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetencoding", (RTS_UINTPTR)sti_storagegetencoding, 1, RTSITF_GET_SIGNATURE(0, 0xBE199139), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_storagegetencoding
	#define EXT_CmpCAAStoragesti_storagegetencoding
	#define GET_CmpCAAStoragesti_storagegetencoding  ERR_OK
	#define CAL_CmpCAAStoragesti_storagegetencoding  sti_storagegetencoding
	#define CHK_CmpCAAStoragesti_storagegetencoding  TRUE
	#define EXP_CmpCAAStoragesti_storagegetencoding  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetencoding", (RTS_UINTPTR)sti_storagegetencoding, 1, RTSITF_GET_SIGNATURE(0, 0xBE199139), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_storagegetencoding
	#define EXT_sti_storagegetencoding
	#define GET_sti_storagegetencoding(fl)  CAL_CMGETAPI( "sti_storagegetencoding" ) 
	#define CAL_sti_storagegetencoding  sti_storagegetencoding
	#define CHK_sti_storagegetencoding  TRUE
	#define EXP_sti_storagegetencoding  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetencoding", (RTS_UINTPTR)sti_storagegetencoding, 1, RTSITF_GET_SIGNATURE(0, 0xBE199139), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_storagegetencoding  PFSTI_STORAGEGETENCODING_IEC pfsti_storagegetencoding;
	#define EXT_sti_storagegetencoding  extern PFSTI_STORAGEGETENCODING_IEC pfsti_storagegetencoding;
	#define GET_sti_storagegetencoding(fl)  s_pfCMGetAPI2( "sti_storagegetencoding", (RTS_VOID_FCTPTR *)&pfsti_storagegetencoding, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xBE199139), 0x03050500)
	#define CAL_sti_storagegetencoding  pfsti_storagegetencoding
	#define CHK_sti_storagegetencoding  (pfsti_storagegetencoding != NULL)
	#define EXP_sti_storagegetencoding   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetencoding", (RTS_UINTPTR)sti_storagegetencoding, 1, RTSITF_GET_SIGNATURE(0, 0xBE199139), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_storagegetindexid(sti_storagegetindexid_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_STORAGEGETINDEXID_IEC) (sti_storagegetindexid_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEGETINDEXID_NOTIMPLEMENTED)
	#define USE_sti_storagegetindexid
	#define EXT_sti_storagegetindexid
	#define GET_sti_storagegetindexid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_storagegetindexid(p0) 
	#define CHK_sti_storagegetindexid  FALSE
	#define EXP_sti_storagegetindexid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_storagegetindexid
	#define EXT_sti_storagegetindexid
	#define GET_sti_storagegetindexid(fl)  CAL_CMGETAPI( "sti_storagegetindexid" ) 
	#define CAL_sti_storagegetindexid  sti_storagegetindexid
	#define CHK_sti_storagegetindexid  TRUE
	#define EXP_sti_storagegetindexid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetindexid", (RTS_UINTPTR)sti_storagegetindexid, 1, RTSITF_GET_SIGNATURE(0x08A23D12, 0x227C8789), 0x03050C00) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_storagegetindexid
	#define EXT_sti_storagegetindexid
	#define GET_sti_storagegetindexid(fl)  CAL_CMGETAPI( "sti_storagegetindexid" ) 
	#define CAL_sti_storagegetindexid  sti_storagegetindexid
	#define CHK_sti_storagegetindexid  TRUE
	#define EXP_sti_storagegetindexid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetindexid", (RTS_UINTPTR)sti_storagegetindexid, 1, RTSITF_GET_SIGNATURE(0x08A23D12, 0x227C8789), 0x03050C00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_storagegetindexid
	#define EXT_CmpCAAStoragesti_storagegetindexid
	#define GET_CmpCAAStoragesti_storagegetindexid  ERR_OK
	#define CAL_CmpCAAStoragesti_storagegetindexid  sti_storagegetindexid
	#define CHK_CmpCAAStoragesti_storagegetindexid  TRUE
	#define EXP_CmpCAAStoragesti_storagegetindexid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetindexid", (RTS_UINTPTR)sti_storagegetindexid, 1, RTSITF_GET_SIGNATURE(0x08A23D12, 0x227C8789), 0x03050C00) 
#elif defined(CPLUSPLUS)
	#define USE_sti_storagegetindexid
	#define EXT_sti_storagegetindexid
	#define GET_sti_storagegetindexid(fl)  CAL_CMGETAPI( "sti_storagegetindexid" ) 
	#define CAL_sti_storagegetindexid  sti_storagegetindexid
	#define CHK_sti_storagegetindexid  TRUE
	#define EXP_sti_storagegetindexid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetindexid", (RTS_UINTPTR)sti_storagegetindexid, 1, RTSITF_GET_SIGNATURE(0x08A23D12, 0x227C8789), 0x03050C00) 
#else /* DYNAMIC_LINK */
	#define USE_sti_storagegetindexid  PFSTI_STORAGEGETINDEXID_IEC pfsti_storagegetindexid;
	#define EXT_sti_storagegetindexid  extern PFSTI_STORAGEGETINDEXID_IEC pfsti_storagegetindexid;
	#define GET_sti_storagegetindexid(fl)  s_pfCMGetAPI2( "sti_storagegetindexid", (RTS_VOID_FCTPTR *)&pfsti_storagegetindexid, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0x08A23D12, 0x227C8789), 0x03050C00)
	#define CAL_sti_storagegetindexid  pfsti_storagegetindexid
	#define CHK_sti_storagegetindexid  (pfsti_storagegetindexid != NULL)
	#define EXP_sti_storagegetindexid   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetindexid", (RTS_UINTPTR)sti_storagegetindexid, 1, RTSITF_GET_SIGNATURE(0x08A23D12, 0x227C8789), 0x03050C00) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storagegetlockingstate_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_INT STI_StorageGetLockingState;	/* VAR_OUTPUT, Enum: LOCKING_STATE */
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_storagegetlockingstate_struct;

void CDECL CDECL_EXT sti_storagegetlockingstate(sti_storagegetlockingstate_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_STORAGEGETLOCKINGSTATE_IEC) (sti_storagegetlockingstate_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEGETLOCKINGSTATE_NOTIMPLEMENTED)
	#define USE_sti_storagegetlockingstate
	#define EXT_sti_storagegetlockingstate
	#define GET_sti_storagegetlockingstate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_storagegetlockingstate(p0) 
	#define CHK_sti_storagegetlockingstate  FALSE
	#define EXP_sti_storagegetlockingstate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_storagegetlockingstate
	#define EXT_sti_storagegetlockingstate
	#define GET_sti_storagegetlockingstate(fl)  CAL_CMGETAPI( "sti_storagegetlockingstate" ) 
	#define CAL_sti_storagegetlockingstate  sti_storagegetlockingstate
	#define CHK_sti_storagegetlockingstate  TRUE
	#define EXP_sti_storagegetlockingstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetlockingstate", (RTS_UINTPTR)sti_storagegetlockingstate, 1, RTSITF_GET_SIGNATURE(0, 0x673B5974), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_storagegetlockingstate
	#define EXT_sti_storagegetlockingstate
	#define GET_sti_storagegetlockingstate(fl)  CAL_CMGETAPI( "sti_storagegetlockingstate" ) 
	#define CAL_sti_storagegetlockingstate  sti_storagegetlockingstate
	#define CHK_sti_storagegetlockingstate  TRUE
	#define EXP_sti_storagegetlockingstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetlockingstate", (RTS_UINTPTR)sti_storagegetlockingstate, 1, RTSITF_GET_SIGNATURE(0, 0x673B5974), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_storagegetlockingstate
	#define EXT_CmpCAAStoragesti_storagegetlockingstate
	#define GET_CmpCAAStoragesti_storagegetlockingstate  ERR_OK
	#define CAL_CmpCAAStoragesti_storagegetlockingstate  sti_storagegetlockingstate
	#define CHK_CmpCAAStoragesti_storagegetlockingstate  TRUE
	#define EXP_CmpCAAStoragesti_storagegetlockingstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetlockingstate", (RTS_UINTPTR)sti_storagegetlockingstate, 1, RTSITF_GET_SIGNATURE(0, 0x673B5974), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_storagegetlockingstate
	#define EXT_sti_storagegetlockingstate
	#define GET_sti_storagegetlockingstate(fl)  CAL_CMGETAPI( "sti_storagegetlockingstate" ) 
	#define CAL_sti_storagegetlockingstate  sti_storagegetlockingstate
	#define CHK_sti_storagegetlockingstate  TRUE
	#define EXP_sti_storagegetlockingstate  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetlockingstate", (RTS_UINTPTR)sti_storagegetlockingstate, 1, RTSITF_GET_SIGNATURE(0, 0x673B5974), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_storagegetlockingstate  PFSTI_STORAGEGETLOCKINGSTATE_IEC pfsti_storagegetlockingstate;
	#define EXT_sti_storagegetlockingstate  extern PFSTI_STORAGEGETLOCKINGSTATE_IEC pfsti_storagegetlockingstate;
	#define GET_sti_storagegetlockingstate(fl)  s_pfCMGetAPI2( "sti_storagegetlockingstate", (RTS_VOID_FCTPTR *)&pfsti_storagegetlockingstate, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x673B5974), 0x03050500)
	#define CAL_sti_storagegetlockingstate  pfsti_storagegetlockingstate
	#define CHK_sti_storagegetlockingstate  (pfsti_storagegetlockingstate != NULL)
	#define EXP_sti_storagegetlockingstate   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetlockingstate", (RTS_UINTPTR)sti_storagegetlockingstate, 1, RTSITF_GET_SIGNATURE(0, 0x673B5974), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storagegetmetrics_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	STO_METRICS *mMetrics;				/* VAR_IN_OUT */	
	RTS_IEC_INT STI_StorageGetMetrics;	/* VAR_OUTPUT, Enum: ERROR */
} sti_storagegetmetrics_struct;

void CDECL CDECL_EXT sti_storagegetmetrics(sti_storagegetmetrics_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_STORAGEGETMETRICS_IEC) (sti_storagegetmetrics_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEGETMETRICS_NOTIMPLEMENTED)
	#define USE_sti_storagegetmetrics
	#define EXT_sti_storagegetmetrics
	#define GET_sti_storagegetmetrics(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_storagegetmetrics(p0) 
	#define CHK_sti_storagegetmetrics  FALSE
	#define EXP_sti_storagegetmetrics  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_storagegetmetrics
	#define EXT_sti_storagegetmetrics
	#define GET_sti_storagegetmetrics(fl)  CAL_CMGETAPI( "sti_storagegetmetrics" ) 
	#define CAL_sti_storagegetmetrics  sti_storagegetmetrics
	#define CHK_sti_storagegetmetrics  TRUE
	#define EXP_sti_storagegetmetrics  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetmetrics", (RTS_UINTPTR)sti_storagegetmetrics, 1, RTSITF_GET_SIGNATURE(0, 0x94B2DFD3), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_storagegetmetrics
	#define EXT_sti_storagegetmetrics
	#define GET_sti_storagegetmetrics(fl)  CAL_CMGETAPI( "sti_storagegetmetrics" ) 
	#define CAL_sti_storagegetmetrics  sti_storagegetmetrics
	#define CHK_sti_storagegetmetrics  TRUE
	#define EXP_sti_storagegetmetrics  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetmetrics", (RTS_UINTPTR)sti_storagegetmetrics, 1, RTSITF_GET_SIGNATURE(0, 0x94B2DFD3), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_storagegetmetrics
	#define EXT_CmpCAAStoragesti_storagegetmetrics
	#define GET_CmpCAAStoragesti_storagegetmetrics  ERR_OK
	#define CAL_CmpCAAStoragesti_storagegetmetrics  sti_storagegetmetrics
	#define CHK_CmpCAAStoragesti_storagegetmetrics  TRUE
	#define EXP_CmpCAAStoragesti_storagegetmetrics  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetmetrics", (RTS_UINTPTR)sti_storagegetmetrics, 1, RTSITF_GET_SIGNATURE(0, 0x94B2DFD3), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_storagegetmetrics
	#define EXT_sti_storagegetmetrics
	#define GET_sti_storagegetmetrics(fl)  CAL_CMGETAPI( "sti_storagegetmetrics" ) 
	#define CAL_sti_storagegetmetrics  sti_storagegetmetrics
	#define CHK_sti_storagegetmetrics  TRUE
	#define EXP_sti_storagegetmetrics  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetmetrics", (RTS_UINTPTR)sti_storagegetmetrics, 1, RTSITF_GET_SIGNATURE(0, 0x94B2DFD3), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_storagegetmetrics  PFSTI_STORAGEGETMETRICS_IEC pfsti_storagegetmetrics;
	#define EXT_sti_storagegetmetrics  extern PFSTI_STORAGEGETMETRICS_IEC pfsti_storagegetmetrics;
	#define GET_sti_storagegetmetrics(fl)  s_pfCMGetAPI2( "sti_storagegetmetrics", (RTS_VOID_FCTPTR *)&pfsti_storagegetmetrics, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x94B2DFD3), 0x03050500)
	#define CAL_sti_storagegetmetrics  pfsti_storagegetmetrics
	#define CHK_sti_storagegetmetrics  (pfsti_storagegetmetrics != NULL)
	#define EXP_sti_storagegetmetrics   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetmetrics", (RTS_UINTPTR)sti_storagegetmetrics, 1, RTSITF_GET_SIGNATURE(0, 0x94B2DFD3), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storagegetnumoftables_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_UXINT STI_StorageGetNumOfTables;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_storagegetnumoftables_struct;

void CDECL CDECL_EXT sti_storagegetnumoftables(sti_storagegetnumoftables_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_STORAGEGETNUMOFTABLES_IEC) (sti_storagegetnumoftables_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEGETNUMOFTABLES_NOTIMPLEMENTED)
	#define USE_sti_storagegetnumoftables
	#define EXT_sti_storagegetnumoftables
	#define GET_sti_storagegetnumoftables(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_storagegetnumoftables(p0) 
	#define CHK_sti_storagegetnumoftables  FALSE
	#define EXP_sti_storagegetnumoftables  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_storagegetnumoftables
	#define EXT_sti_storagegetnumoftables
	#define GET_sti_storagegetnumoftables(fl)  CAL_CMGETAPI( "sti_storagegetnumoftables" ) 
	#define CAL_sti_storagegetnumoftables  sti_storagegetnumoftables
	#define CHK_sti_storagegetnumoftables  TRUE
	#define EXP_sti_storagegetnumoftables  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetnumoftables", (RTS_UINTPTR)sti_storagegetnumoftables, 1, RTSITF_GET_SIGNATURE(0, 0x1C28D551), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_storagegetnumoftables
	#define EXT_sti_storagegetnumoftables
	#define GET_sti_storagegetnumoftables(fl)  CAL_CMGETAPI( "sti_storagegetnumoftables" ) 
	#define CAL_sti_storagegetnumoftables  sti_storagegetnumoftables
	#define CHK_sti_storagegetnumoftables  TRUE
	#define EXP_sti_storagegetnumoftables  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetnumoftables", (RTS_UINTPTR)sti_storagegetnumoftables, 1, RTSITF_GET_SIGNATURE(0, 0x1C28D551), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_storagegetnumoftables
	#define EXT_CmpCAAStoragesti_storagegetnumoftables
	#define GET_CmpCAAStoragesti_storagegetnumoftables  ERR_OK
	#define CAL_CmpCAAStoragesti_storagegetnumoftables  sti_storagegetnumoftables
	#define CHK_CmpCAAStoragesti_storagegetnumoftables  TRUE
	#define EXP_CmpCAAStoragesti_storagegetnumoftables  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetnumoftables", (RTS_UINTPTR)sti_storagegetnumoftables, 1, RTSITF_GET_SIGNATURE(0, 0x1C28D551), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_storagegetnumoftables
	#define EXT_sti_storagegetnumoftables
	#define GET_sti_storagegetnumoftables(fl)  CAL_CMGETAPI( "sti_storagegetnumoftables" ) 
	#define CAL_sti_storagegetnumoftables  sti_storagegetnumoftables
	#define CHK_sti_storagegetnumoftables  TRUE
	#define EXP_sti_storagegetnumoftables  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetnumoftables", (RTS_UINTPTR)sti_storagegetnumoftables, 1, RTSITF_GET_SIGNATURE(0, 0x1C28D551), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_storagegetnumoftables  PFSTI_STORAGEGETNUMOFTABLES_IEC pfsti_storagegetnumoftables;
	#define EXT_sti_storagegetnumoftables  extern PFSTI_STORAGEGETNUMOFTABLES_IEC pfsti_storagegetnumoftables;
	#define GET_sti_storagegetnumoftables(fl)  s_pfCMGetAPI2( "sti_storagegetnumoftables", (RTS_VOID_FCTPTR *)&pfsti_storagegetnumoftables, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x1C28D551), 0x03050500)
	#define CAL_sti_storagegetnumoftables  pfsti_storagegetnumoftables
	#define CHK_sti_storagegetnumoftables  (pfsti_storagegetnumoftables != NULL)
	#define EXP_sti_storagegetnumoftables   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetnumoftables", (RTS_UINTPTR)sti_storagegetnumoftables, 1, RTSITF_GET_SIGNATURE(0, 0x1C28D551), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storagegetpath_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_STRING *sPath;				/* VAR_IN_OUT */	
	RTS_IEC_INT STI_StorageGetPath;		/* VAR_OUTPUT, Enum: ERROR */
} sti_storagegetpath_struct;

void CDECL CDECL_EXT sti_storagegetpath(sti_storagegetpath_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_STORAGEGETPATH_IEC) (sti_storagegetpath_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEGETPATH_NOTIMPLEMENTED)
	#define USE_sti_storagegetpath
	#define EXT_sti_storagegetpath
	#define GET_sti_storagegetpath(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_storagegetpath(p0) 
	#define CHK_sti_storagegetpath  FALSE
	#define EXP_sti_storagegetpath  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_storagegetpath
	#define EXT_sti_storagegetpath
	#define GET_sti_storagegetpath(fl)  CAL_CMGETAPI( "sti_storagegetpath" ) 
	#define CAL_sti_storagegetpath  sti_storagegetpath
	#define CHK_sti_storagegetpath  TRUE
	#define EXP_sti_storagegetpath  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetpath", (RTS_UINTPTR)sti_storagegetpath, 1, RTSITF_GET_SIGNATURE(0, 0x5370063F), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_storagegetpath
	#define EXT_sti_storagegetpath
	#define GET_sti_storagegetpath(fl)  CAL_CMGETAPI( "sti_storagegetpath" ) 
	#define CAL_sti_storagegetpath  sti_storagegetpath
	#define CHK_sti_storagegetpath  TRUE
	#define EXP_sti_storagegetpath  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetpath", (RTS_UINTPTR)sti_storagegetpath, 1, RTSITF_GET_SIGNATURE(0, 0x5370063F), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_storagegetpath
	#define EXT_CmpCAAStoragesti_storagegetpath
	#define GET_CmpCAAStoragesti_storagegetpath  ERR_OK
	#define CAL_CmpCAAStoragesti_storagegetpath  sti_storagegetpath
	#define CHK_CmpCAAStoragesti_storagegetpath  TRUE
	#define EXP_CmpCAAStoragesti_storagegetpath  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetpath", (RTS_UINTPTR)sti_storagegetpath, 1, RTSITF_GET_SIGNATURE(0, 0x5370063F), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_storagegetpath
	#define EXT_sti_storagegetpath
	#define GET_sti_storagegetpath(fl)  CAL_CMGETAPI( "sti_storagegetpath" ) 
	#define CAL_sti_storagegetpath  sti_storagegetpath
	#define CHK_sti_storagegetpath  TRUE
	#define EXP_sti_storagegetpath  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetpath", (RTS_UINTPTR)sti_storagegetpath, 1, RTSITF_GET_SIGNATURE(0, 0x5370063F), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_storagegetpath  PFSTI_STORAGEGETPATH_IEC pfsti_storagegetpath;
	#define EXT_sti_storagegetpath  extern PFSTI_STORAGEGETPATH_IEC pfsti_storagegetpath;
	#define GET_sti_storagegetpath(fl)  s_pfCMGetAPI2( "sti_storagegetpath", (RTS_VOID_FCTPTR *)&pfsti_storagegetpath, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x5370063F), 0x03050500)
	#define CAL_sti_storagegetpath  pfsti_storagegetpath
	#define CHK_sti_storagegetpath  (pfsti_storagegetpath != NULL)
	#define EXP_sti_storagegetpath   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetpath", (RTS_UINTPTR)sti_storagegetpath, 1, RTSITF_GET_SIGNATURE(0, 0x5370063F), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storagegetschemaversion_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_DINT STI_StorageGetSchemaVersion;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_storagegetschemaversion_struct;

void CDECL CDECL_EXT sti_storagegetschemaversion(sti_storagegetschemaversion_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_STORAGEGETSCHEMAVERSION_IEC) (sti_storagegetschemaversion_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEGETSCHEMAVERSION_NOTIMPLEMENTED)
	#define USE_sti_storagegetschemaversion
	#define EXT_sti_storagegetschemaversion
	#define GET_sti_storagegetschemaversion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_storagegetschemaversion(p0) 
	#define CHK_sti_storagegetschemaversion  FALSE
	#define EXP_sti_storagegetschemaversion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_storagegetschemaversion
	#define EXT_sti_storagegetschemaversion
	#define GET_sti_storagegetschemaversion(fl)  CAL_CMGETAPI( "sti_storagegetschemaversion" ) 
	#define CAL_sti_storagegetschemaversion  sti_storagegetschemaversion
	#define CHK_sti_storagegetschemaversion  TRUE
	#define EXP_sti_storagegetschemaversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetschemaversion", (RTS_UINTPTR)sti_storagegetschemaversion, 1, RTSITF_GET_SIGNATURE(0, 0x0AE8BC90), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_storagegetschemaversion
	#define EXT_sti_storagegetschemaversion
	#define GET_sti_storagegetschemaversion(fl)  CAL_CMGETAPI( "sti_storagegetschemaversion" ) 
	#define CAL_sti_storagegetschemaversion  sti_storagegetschemaversion
	#define CHK_sti_storagegetschemaversion  TRUE
	#define EXP_sti_storagegetschemaversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetschemaversion", (RTS_UINTPTR)sti_storagegetschemaversion, 1, RTSITF_GET_SIGNATURE(0, 0x0AE8BC90), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_storagegetschemaversion
	#define EXT_CmpCAAStoragesti_storagegetschemaversion
	#define GET_CmpCAAStoragesti_storagegetschemaversion  ERR_OK
	#define CAL_CmpCAAStoragesti_storagegetschemaversion  sti_storagegetschemaversion
	#define CHK_CmpCAAStoragesti_storagegetschemaversion  TRUE
	#define EXP_CmpCAAStoragesti_storagegetschemaversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetschemaversion", (RTS_UINTPTR)sti_storagegetschemaversion, 1, RTSITF_GET_SIGNATURE(0, 0x0AE8BC90), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_storagegetschemaversion
	#define EXT_sti_storagegetschemaversion
	#define GET_sti_storagegetschemaversion(fl)  CAL_CMGETAPI( "sti_storagegetschemaversion" ) 
	#define CAL_sti_storagegetschemaversion  sti_storagegetschemaversion
	#define CHK_sti_storagegetschemaversion  TRUE
	#define EXP_sti_storagegetschemaversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetschemaversion", (RTS_UINTPTR)sti_storagegetschemaversion, 1, RTSITF_GET_SIGNATURE(0, 0x0AE8BC90), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_storagegetschemaversion  PFSTI_STORAGEGETSCHEMAVERSION_IEC pfsti_storagegetschemaversion;
	#define EXT_sti_storagegetschemaversion  extern PFSTI_STORAGEGETSCHEMAVERSION_IEC pfsti_storagegetschemaversion;
	#define GET_sti_storagegetschemaversion(fl)  s_pfCMGetAPI2( "sti_storagegetschemaversion", (RTS_VOID_FCTPTR *)&pfsti_storagegetschemaversion, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x0AE8BC90), 0x03050500)
	#define CAL_sti_storagegetschemaversion  pfsti_storagegetschemaversion
	#define CHK_sti_storagegetschemaversion  (pfsti_storagegetschemaversion != NULL)
	#define EXP_sti_storagegetschemaversion   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetschemaversion", (RTS_UINTPTR)sti_storagegetschemaversion, 1, RTSITF_GET_SIGNATURE(0, 0x0AE8BC90), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storagegetstorageversion_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_DINT STI_StorageGetStorageVersion;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_storagegetstorageversion_struct;

void CDECL CDECL_EXT sti_storagegetstorageversion(sti_storagegetstorageversion_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_STORAGEGETSTORAGEVERSION_IEC) (sti_storagegetstorageversion_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEGETSTORAGEVERSION_NOTIMPLEMENTED)
	#define USE_sti_storagegetstorageversion
	#define EXT_sti_storagegetstorageversion
	#define GET_sti_storagegetstorageversion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_storagegetstorageversion(p0) 
	#define CHK_sti_storagegetstorageversion  FALSE
	#define EXP_sti_storagegetstorageversion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_storagegetstorageversion
	#define EXT_sti_storagegetstorageversion
	#define GET_sti_storagegetstorageversion(fl)  CAL_CMGETAPI( "sti_storagegetstorageversion" ) 
	#define CAL_sti_storagegetstorageversion  sti_storagegetstorageversion
	#define CHK_sti_storagegetstorageversion  TRUE
	#define EXP_sti_storagegetstorageversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetstorageversion", (RTS_UINTPTR)sti_storagegetstorageversion, 1, RTSITF_GET_SIGNATURE(0, 0x09CB4CDD), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_storagegetstorageversion
	#define EXT_sti_storagegetstorageversion
	#define GET_sti_storagegetstorageversion(fl)  CAL_CMGETAPI( "sti_storagegetstorageversion" ) 
	#define CAL_sti_storagegetstorageversion  sti_storagegetstorageversion
	#define CHK_sti_storagegetstorageversion  TRUE
	#define EXP_sti_storagegetstorageversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetstorageversion", (RTS_UINTPTR)sti_storagegetstorageversion, 1, RTSITF_GET_SIGNATURE(0, 0x09CB4CDD), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_storagegetstorageversion
	#define EXT_CmpCAAStoragesti_storagegetstorageversion
	#define GET_CmpCAAStoragesti_storagegetstorageversion  ERR_OK
	#define CAL_CmpCAAStoragesti_storagegetstorageversion  sti_storagegetstorageversion
	#define CHK_CmpCAAStoragesti_storagegetstorageversion  TRUE
	#define EXP_CmpCAAStoragesti_storagegetstorageversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetstorageversion", (RTS_UINTPTR)sti_storagegetstorageversion, 1, RTSITF_GET_SIGNATURE(0, 0x09CB4CDD), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_storagegetstorageversion
	#define EXT_sti_storagegetstorageversion
	#define GET_sti_storagegetstorageversion(fl)  CAL_CMGETAPI( "sti_storagegetstorageversion" ) 
	#define CAL_sti_storagegetstorageversion  sti_storagegetstorageversion
	#define CHK_sti_storagegetstorageversion  TRUE
	#define EXP_sti_storagegetstorageversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetstorageversion", (RTS_UINTPTR)sti_storagegetstorageversion, 1, RTSITF_GET_SIGNATURE(0, 0x09CB4CDD), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_storagegetstorageversion  PFSTI_STORAGEGETSTORAGEVERSION_IEC pfsti_storagegetstorageversion;
	#define EXT_sti_storagegetstorageversion  extern PFSTI_STORAGEGETSTORAGEVERSION_IEC pfsti_storagegetstorageversion;
	#define GET_sti_storagegetstorageversion(fl)  s_pfCMGetAPI2( "sti_storagegetstorageversion", (RTS_VOID_FCTPTR *)&pfsti_storagegetstorageversion, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x09CB4CDD), 0x03050500)
	#define CAL_sti_storagegetstorageversion  pfsti_storagegetstorageversion
	#define CHK_sti_storagegetstorageversion  (pfsti_storagegetstorageversion != NULL)
	#define EXP_sti_storagegetstorageversion   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetstorageversion", (RTS_UINTPTR)sti_storagegetstorageversion, 1, RTSITF_GET_SIGNATURE(0, 0x09CB4CDD), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_storagegettableid(sti_storagegettableid_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_STORAGEGETTABLEID_IEC) (sti_storagegettableid_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEGETTABLEID_NOTIMPLEMENTED)
	#define USE_sti_storagegettableid
	#define EXT_sti_storagegettableid
	#define GET_sti_storagegettableid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_storagegettableid(p0) 
	#define CHK_sti_storagegettableid  FALSE
	#define EXP_sti_storagegettableid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_storagegettableid
	#define EXT_sti_storagegettableid
	#define GET_sti_storagegettableid(fl)  CAL_CMGETAPI( "sti_storagegettableid" ) 
	#define CAL_sti_storagegettableid  sti_storagegettableid
	#define CHK_sti_storagegettableid  TRUE
	#define EXP_sti_storagegettableid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegettableid", (RTS_UINTPTR)sti_storagegettableid, 1, RTSITF_GET_SIGNATURE(0xCDAB221E, 0xE7759885), 0x03050C00) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_storagegettableid
	#define EXT_sti_storagegettableid
	#define GET_sti_storagegettableid(fl)  CAL_CMGETAPI( "sti_storagegettableid" ) 
	#define CAL_sti_storagegettableid  sti_storagegettableid
	#define CHK_sti_storagegettableid  TRUE
	#define EXP_sti_storagegettableid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegettableid", (RTS_UINTPTR)sti_storagegettableid, 1, RTSITF_GET_SIGNATURE(0xCDAB221E, 0xE7759885), 0x03050C00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_storagegettableid
	#define EXT_CmpCAAStoragesti_storagegettableid
	#define GET_CmpCAAStoragesti_storagegettableid  ERR_OK
	#define CAL_CmpCAAStoragesti_storagegettableid  sti_storagegettableid
	#define CHK_CmpCAAStoragesti_storagegettableid  TRUE
	#define EXP_CmpCAAStoragesti_storagegettableid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegettableid", (RTS_UINTPTR)sti_storagegettableid, 1, RTSITF_GET_SIGNATURE(0xCDAB221E, 0xE7759885), 0x03050C00) 
#elif defined(CPLUSPLUS)
	#define USE_sti_storagegettableid
	#define EXT_sti_storagegettableid
	#define GET_sti_storagegettableid(fl)  CAL_CMGETAPI( "sti_storagegettableid" ) 
	#define CAL_sti_storagegettableid  sti_storagegettableid
	#define CHK_sti_storagegettableid  TRUE
	#define EXP_sti_storagegettableid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegettableid", (RTS_UINTPTR)sti_storagegettableid, 1, RTSITF_GET_SIGNATURE(0xCDAB221E, 0xE7759885), 0x03050C00) 
#else /* DYNAMIC_LINK */
	#define USE_sti_storagegettableid  PFSTI_STORAGEGETTABLEID_IEC pfsti_storagegettableid;
	#define EXT_sti_storagegettableid  extern PFSTI_STORAGEGETTABLEID_IEC pfsti_storagegettableid;
	#define GET_sti_storagegettableid(fl)  s_pfCMGetAPI2( "sti_storagegettableid", (RTS_VOID_FCTPTR *)&pfsti_storagegettableid, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0xCDAB221E, 0xE7759885), 0x03050C00)
	#define CAL_sti_storagegettableid  pfsti_storagegettableid
	#define CHK_sti_storagegettableid  (pfsti_storagegettableid != NULL)
	#define EXP_sti_storagegettableid   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegettableid", (RTS_UINTPTR)sti_storagegettableid, 1, RTSITF_GET_SIGNATURE(0xCDAB221E, 0xE7759885), 0x03050C00) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storagegetuserversion_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_DINT STI_StorageGetUserVersion;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_storagegetuserversion_struct;

void CDECL CDECL_EXT sti_storagegetuserversion(sti_storagegetuserversion_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_STORAGEGETUSERVERSION_IEC) (sti_storagegetuserversion_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEGETUSERVERSION_NOTIMPLEMENTED)
	#define USE_sti_storagegetuserversion
	#define EXT_sti_storagegetuserversion
	#define GET_sti_storagegetuserversion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_storagegetuserversion(p0) 
	#define CHK_sti_storagegetuserversion  FALSE
	#define EXP_sti_storagegetuserversion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_storagegetuserversion
	#define EXT_sti_storagegetuserversion
	#define GET_sti_storagegetuserversion(fl)  CAL_CMGETAPI( "sti_storagegetuserversion" ) 
	#define CAL_sti_storagegetuserversion  sti_storagegetuserversion
	#define CHK_sti_storagegetuserversion  TRUE
	#define EXP_sti_storagegetuserversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetuserversion", (RTS_UINTPTR)sti_storagegetuserversion, 1, RTSITF_GET_SIGNATURE(0, 0xFBEB5D41), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_storagegetuserversion
	#define EXT_sti_storagegetuserversion
	#define GET_sti_storagegetuserversion(fl)  CAL_CMGETAPI( "sti_storagegetuserversion" ) 
	#define CAL_sti_storagegetuserversion  sti_storagegetuserversion
	#define CHK_sti_storagegetuserversion  TRUE
	#define EXP_sti_storagegetuserversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetuserversion", (RTS_UINTPTR)sti_storagegetuserversion, 1, RTSITF_GET_SIGNATURE(0, 0xFBEB5D41), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_storagegetuserversion
	#define EXT_CmpCAAStoragesti_storagegetuserversion
	#define GET_CmpCAAStoragesti_storagegetuserversion  ERR_OK
	#define CAL_CmpCAAStoragesti_storagegetuserversion  sti_storagegetuserversion
	#define CHK_CmpCAAStoragesti_storagegetuserversion  TRUE
	#define EXP_CmpCAAStoragesti_storagegetuserversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetuserversion", (RTS_UINTPTR)sti_storagegetuserversion, 1, RTSITF_GET_SIGNATURE(0, 0xFBEB5D41), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_storagegetuserversion
	#define EXT_sti_storagegetuserversion
	#define GET_sti_storagegetuserversion(fl)  CAL_CMGETAPI( "sti_storagegetuserversion" ) 
	#define CAL_sti_storagegetuserversion  sti_storagegetuserversion
	#define CHK_sti_storagegetuserversion  TRUE
	#define EXP_sti_storagegetuserversion  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetuserversion", (RTS_UINTPTR)sti_storagegetuserversion, 1, RTSITF_GET_SIGNATURE(0, 0xFBEB5D41), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_storagegetuserversion  PFSTI_STORAGEGETUSERVERSION_IEC pfsti_storagegetuserversion;
	#define EXT_sti_storagegetuserversion  extern PFSTI_STORAGEGETUSERVERSION_IEC pfsti_storagegetuserversion;
	#define GET_sti_storagegetuserversion(fl)  s_pfCMGetAPI2( "sti_storagegetuserversion", (RTS_VOID_FCTPTR *)&pfsti_storagegetuserversion, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xFBEB5D41), 0x03050500)
	#define CAL_sti_storagegetuserversion  pfsti_storagegetuserversion
	#define CHK_sti_storagegetuserversion  (pfsti_storagegetuserversion != NULL)
	#define EXP_sti_storagegetuserversion   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagegetuserversion", (RTS_UINTPTR)sti_storagegetuserversion, 1, RTSITF_GET_SIGNATURE(0, 0xFBEB5D41), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storageisreadonly_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_BOOL STI_StorageIsReadOnly;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_storageisreadonly_struct;

void CDECL CDECL_EXT sti_storageisreadonly(sti_storageisreadonly_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_STORAGEISREADONLY_IEC) (sti_storageisreadonly_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEISREADONLY_NOTIMPLEMENTED)
	#define USE_sti_storageisreadonly
	#define EXT_sti_storageisreadonly
	#define GET_sti_storageisreadonly(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_storageisreadonly(p0) 
	#define CHK_sti_storageisreadonly  FALSE
	#define EXP_sti_storageisreadonly  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_storageisreadonly
	#define EXT_sti_storageisreadonly
	#define GET_sti_storageisreadonly(fl)  CAL_CMGETAPI( "sti_storageisreadonly" ) 
	#define CAL_sti_storageisreadonly  sti_storageisreadonly
	#define CHK_sti_storageisreadonly  TRUE
	#define EXP_sti_storageisreadonly  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageisreadonly", (RTS_UINTPTR)sti_storageisreadonly, 1, RTSITF_GET_SIGNATURE(0, 0x05EC113C), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_storageisreadonly
	#define EXT_sti_storageisreadonly
	#define GET_sti_storageisreadonly(fl)  CAL_CMGETAPI( "sti_storageisreadonly" ) 
	#define CAL_sti_storageisreadonly  sti_storageisreadonly
	#define CHK_sti_storageisreadonly  TRUE
	#define EXP_sti_storageisreadonly  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageisreadonly", (RTS_UINTPTR)sti_storageisreadonly, 1, RTSITF_GET_SIGNATURE(0, 0x05EC113C), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_storageisreadonly
	#define EXT_CmpCAAStoragesti_storageisreadonly
	#define GET_CmpCAAStoragesti_storageisreadonly  ERR_OK
	#define CAL_CmpCAAStoragesti_storageisreadonly  sti_storageisreadonly
	#define CHK_CmpCAAStoragesti_storageisreadonly  TRUE
	#define EXP_CmpCAAStoragesti_storageisreadonly  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageisreadonly", (RTS_UINTPTR)sti_storageisreadonly, 1, RTSITF_GET_SIGNATURE(0, 0x05EC113C), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_storageisreadonly
	#define EXT_sti_storageisreadonly
	#define GET_sti_storageisreadonly(fl)  CAL_CMGETAPI( "sti_storageisreadonly" ) 
	#define CAL_sti_storageisreadonly  sti_storageisreadonly
	#define CHK_sti_storageisreadonly  TRUE
	#define EXP_sti_storageisreadonly  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageisreadonly", (RTS_UINTPTR)sti_storageisreadonly, 1, RTSITF_GET_SIGNATURE(0, 0x05EC113C), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_storageisreadonly  PFSTI_STORAGEISREADONLY_IEC pfsti_storageisreadonly;
	#define EXT_sti_storageisreadonly  extern PFSTI_STORAGEISREADONLY_IEC pfsti_storageisreadonly;
	#define GET_sti_storageisreadonly(fl)  s_pfCMGetAPI2( "sti_storageisreadonly", (RTS_VOID_FCTPTR *)&pfsti_storageisreadonly, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x05EC113C), 0x03050500)
	#define CAL_sti_storageisreadonly  pfsti_storageisreadonly
	#define CHK_sti_storageisreadonly  (pfsti_storageisreadonly != NULL)
	#define EXP_sti_storageisreadonly   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageisreadonly", (RTS_UINTPTR)sti_storageisreadonly, 1, RTSITF_GET_SIGNATURE(0, 0x05EC113C), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_storageopenfile(sti_storageopenfile_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_STORAGEOPENFILE_IEC) (sti_storageopenfile_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEOPENFILE_NOTIMPLEMENTED)
	#define USE_sti_storageopenfile
	#define EXT_sti_storageopenfile
	#define GET_sti_storageopenfile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_storageopenfile(p0) 
	#define CHK_sti_storageopenfile  FALSE
	#define EXP_sti_storageopenfile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_storageopenfile
	#define EXT_sti_storageopenfile
	#define GET_sti_storageopenfile(fl)  CAL_CMGETAPI( "sti_storageopenfile" ) 
	#define CAL_sti_storageopenfile  sti_storageopenfile
	#define CHK_sti_storageopenfile  TRUE
	#define EXP_sti_storageopenfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageopenfile", (RTS_UINTPTR)sti_storageopenfile, 1, RTSITF_GET_SIGNATURE(0, 0xD323975E), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_storageopenfile
	#define EXT_sti_storageopenfile
	#define GET_sti_storageopenfile(fl)  CAL_CMGETAPI( "sti_storageopenfile" ) 
	#define CAL_sti_storageopenfile  sti_storageopenfile
	#define CHK_sti_storageopenfile  TRUE
	#define EXP_sti_storageopenfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageopenfile", (RTS_UINTPTR)sti_storageopenfile, 1, RTSITF_GET_SIGNATURE(0, 0xD323975E), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_storageopenfile
	#define EXT_CmpCAAStoragesti_storageopenfile
	#define GET_CmpCAAStoragesti_storageopenfile  ERR_OK
	#define CAL_CmpCAAStoragesti_storageopenfile  sti_storageopenfile
	#define CHK_CmpCAAStoragesti_storageopenfile  TRUE
	#define EXP_CmpCAAStoragesti_storageopenfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageopenfile", (RTS_UINTPTR)sti_storageopenfile, 1, RTSITF_GET_SIGNATURE(0, 0xD323975E), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_storageopenfile
	#define EXT_sti_storageopenfile
	#define GET_sti_storageopenfile(fl)  CAL_CMGETAPI( "sti_storageopenfile" ) 
	#define CAL_sti_storageopenfile  sti_storageopenfile
	#define CHK_sti_storageopenfile  TRUE
	#define EXP_sti_storageopenfile  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageopenfile", (RTS_UINTPTR)sti_storageopenfile, 1, RTSITF_GET_SIGNATURE(0, 0xD323975E), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_storageopenfile  PFSTI_STORAGEOPENFILE_IEC pfsti_storageopenfile;
	#define EXT_sti_storageopenfile  extern PFSTI_STORAGEOPENFILE_IEC pfsti_storageopenfile;
	#define GET_sti_storageopenfile(fl)  s_pfCMGetAPI2( "sti_storageopenfile", (RTS_VOID_FCTPTR *)&pfsti_storageopenfile, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xD323975E), 0x03050500)
	#define CAL_sti_storageopenfile  pfsti_storageopenfile
	#define CHK_sti_storageopenfile  (pfsti_storageopenfile != NULL)
	#define EXP_sti_storageopenfile   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storageopenfile", (RTS_UINTPTR)sti_storageopenfile, 1, RTSITF_GET_SIGNATURE(0, 0xD323975E), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_storagereorg_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_INT STI_StorageReorg;		/* VAR_OUTPUT, Enum: ERROR */
} sti_storagereorg_struct;

void CDECL CDECL_EXT sti_storagereorg(sti_storagereorg_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_STORAGEREORG_IEC) (sti_storagereorg_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEREORG_NOTIMPLEMENTED)
	#define USE_sti_storagereorg
	#define EXT_sti_storagereorg
	#define GET_sti_storagereorg(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_storagereorg(p0) 
	#define CHK_sti_storagereorg  FALSE
	#define EXP_sti_storagereorg  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_storagereorg
	#define EXT_sti_storagereorg
	#define GET_sti_storagereorg(fl)  CAL_CMGETAPI( "sti_storagereorg" ) 
	#define CAL_sti_storagereorg  sti_storagereorg
	#define CHK_sti_storagereorg  TRUE
	#define EXP_sti_storagereorg  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagereorg", (RTS_UINTPTR)sti_storagereorg, 1, RTSITF_GET_SIGNATURE(0, 0xCE724590), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_storagereorg
	#define EXT_sti_storagereorg
	#define GET_sti_storagereorg(fl)  CAL_CMGETAPI( "sti_storagereorg" ) 
	#define CAL_sti_storagereorg  sti_storagereorg
	#define CHK_sti_storagereorg  TRUE
	#define EXP_sti_storagereorg  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagereorg", (RTS_UINTPTR)sti_storagereorg, 1, RTSITF_GET_SIGNATURE(0, 0xCE724590), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_storagereorg
	#define EXT_CmpCAAStoragesti_storagereorg
	#define GET_CmpCAAStoragesti_storagereorg  ERR_OK
	#define CAL_CmpCAAStoragesti_storagereorg  sti_storagereorg
	#define CHK_CmpCAAStoragesti_storagereorg  TRUE
	#define EXP_CmpCAAStoragesti_storagereorg  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagereorg", (RTS_UINTPTR)sti_storagereorg, 1, RTSITF_GET_SIGNATURE(0, 0xCE724590), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_storagereorg
	#define EXT_sti_storagereorg
	#define GET_sti_storagereorg(fl)  CAL_CMGETAPI( "sti_storagereorg" ) 
	#define CAL_sti_storagereorg  sti_storagereorg
	#define CHK_sti_storagereorg  TRUE
	#define EXP_sti_storagereorg  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagereorg", (RTS_UINTPTR)sti_storagereorg, 1, RTSITF_GET_SIGNATURE(0, 0xCE724590), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_storagereorg  PFSTI_STORAGEREORG_IEC pfsti_storagereorg;
	#define EXT_sti_storagereorg  extern PFSTI_STORAGEREORG_IEC pfsti_storagereorg;
	#define GET_sti_storagereorg(fl)  s_pfCMGetAPI2( "sti_storagereorg", (RTS_VOID_FCTPTR *)&pfsti_storagereorg, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xCE724590), 0x03050500)
	#define CAL_sti_storagereorg  pfsti_storagereorg
	#define CHK_sti_storagereorg  (pfsti_storagereorg != NULL)
	#define EXP_sti_storagereorg   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_storagereorg", (RTS_UINTPTR)sti_storagereorg, 1, RTSITF_GET_SIGNATURE(0, 0xCE724590), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_tableclear_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_INT STI_TableClear;			/* VAR_OUTPUT, Enum: ERROR */
} sti_tableclear_struct;

void CDECL CDECL_EXT sti_tableclear(sti_tableclear_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_TABLECLEAR_IEC) (sti_tableclear_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TABLECLEAR_NOTIMPLEMENTED)
	#define USE_sti_tableclear
	#define EXT_sti_tableclear
	#define GET_sti_tableclear(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_tableclear(p0) 
	#define CHK_sti_tableclear  FALSE
	#define EXP_sti_tableclear  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_tableclear
	#define EXT_sti_tableclear
	#define GET_sti_tableclear(fl)  CAL_CMGETAPI( "sti_tableclear" ) 
	#define CAL_sti_tableclear  sti_tableclear
	#define CHK_sti_tableclear  TRUE
	#define EXP_sti_tableclear  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tableclear", (RTS_UINTPTR)sti_tableclear, 1, RTSITF_GET_SIGNATURE(0, 0xC53500A8), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_tableclear
	#define EXT_sti_tableclear
	#define GET_sti_tableclear(fl)  CAL_CMGETAPI( "sti_tableclear" ) 
	#define CAL_sti_tableclear  sti_tableclear
	#define CHK_sti_tableclear  TRUE
	#define EXP_sti_tableclear  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tableclear", (RTS_UINTPTR)sti_tableclear, 1, RTSITF_GET_SIGNATURE(0, 0xC53500A8), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_tableclear
	#define EXT_CmpCAAStoragesti_tableclear
	#define GET_CmpCAAStoragesti_tableclear  ERR_OK
	#define CAL_CmpCAAStoragesti_tableclear  sti_tableclear
	#define CHK_CmpCAAStoragesti_tableclear  TRUE
	#define EXP_CmpCAAStoragesti_tableclear  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tableclear", (RTS_UINTPTR)sti_tableclear, 1, RTSITF_GET_SIGNATURE(0, 0xC53500A8), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_tableclear
	#define EXT_sti_tableclear
	#define GET_sti_tableclear(fl)  CAL_CMGETAPI( "sti_tableclear" ) 
	#define CAL_sti_tableclear  sti_tableclear
	#define CHK_sti_tableclear  TRUE
	#define EXP_sti_tableclear  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tableclear", (RTS_UINTPTR)sti_tableclear, 1, RTSITF_GET_SIGNATURE(0, 0xC53500A8), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_tableclear  PFSTI_TABLECLEAR_IEC pfsti_tableclear;
	#define EXT_sti_tableclear  extern PFSTI_TABLECLEAR_IEC pfsti_tableclear;
	#define GET_sti_tableclear(fl)  s_pfCMGetAPI2( "sti_tableclear", (RTS_VOID_FCTPTR *)&pfsti_tableclear, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xC53500A8), 0x03050500)
	#define CAL_sti_tableclear  pfsti_tableclear
	#define CHK_sti_tableclear  (pfsti_tableclear != NULL)
	#define EXP_sti_tableclear   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tableclear", (RTS_UINTPTR)sti_tableclear, 1, RTSITF_GET_SIGNATURE(0, 0xC53500A8), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_tableclose_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_INT STI_TableClose;			/* VAR_OUTPUT, Enum: ERROR */
} sti_tableclose_struct;

void CDECL CDECL_EXT sti_tableclose(sti_tableclose_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_TABLECLOSE_IEC) (sti_tableclose_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TABLECLOSE_NOTIMPLEMENTED)
	#define USE_sti_tableclose
	#define EXT_sti_tableclose
	#define GET_sti_tableclose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_tableclose(p0) 
	#define CHK_sti_tableclose  FALSE
	#define EXP_sti_tableclose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_tableclose
	#define EXT_sti_tableclose
	#define GET_sti_tableclose(fl)  CAL_CMGETAPI( "sti_tableclose" ) 
	#define CAL_sti_tableclose  sti_tableclose
	#define CHK_sti_tableclose  TRUE
	#define EXP_sti_tableclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tableclose", (RTS_UINTPTR)sti_tableclose, 1, RTSITF_GET_SIGNATURE(0, 0x16E380EF), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_tableclose
	#define EXT_sti_tableclose
	#define GET_sti_tableclose(fl)  CAL_CMGETAPI( "sti_tableclose" ) 
	#define CAL_sti_tableclose  sti_tableclose
	#define CHK_sti_tableclose  TRUE
	#define EXP_sti_tableclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tableclose", (RTS_UINTPTR)sti_tableclose, 1, RTSITF_GET_SIGNATURE(0, 0x16E380EF), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_tableclose
	#define EXT_CmpCAAStoragesti_tableclose
	#define GET_CmpCAAStoragesti_tableclose  ERR_OK
	#define CAL_CmpCAAStoragesti_tableclose  sti_tableclose
	#define CHK_CmpCAAStoragesti_tableclose  TRUE
	#define EXP_CmpCAAStoragesti_tableclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tableclose", (RTS_UINTPTR)sti_tableclose, 1, RTSITF_GET_SIGNATURE(0, 0x16E380EF), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_tableclose
	#define EXT_sti_tableclose
	#define GET_sti_tableclose(fl)  CAL_CMGETAPI( "sti_tableclose" ) 
	#define CAL_sti_tableclose  sti_tableclose
	#define CHK_sti_tableclose  TRUE
	#define EXP_sti_tableclose  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tableclose", (RTS_UINTPTR)sti_tableclose, 1, RTSITF_GET_SIGNATURE(0, 0x16E380EF), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_tableclose  PFSTI_TABLECLOSE_IEC pfsti_tableclose;
	#define EXT_sti_tableclose  extern PFSTI_TABLECLOSE_IEC pfsti_tableclose;
	#define GET_sti_tableclose(fl)  s_pfCMGetAPI2( "sti_tableclose", (RTS_VOID_FCTPTR *)&pfsti_tableclose, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x16E380EF), 0x03050500)
	#define CAL_sti_tableclose  pfsti_tableclose
	#define CHK_sti_tableclose  (pfsti_tableclose != NULL)
	#define EXP_sti_tableclose   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tableclose", (RTS_UINTPTR)sti_tableclose, 1, RTSITF_GET_SIGNATURE(0, 0x16E380EF), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_tablegetid_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_DWORD STI_TableGetId;		/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_tablegetid_struct;

void CDECL CDECL_EXT sti_tablegetid(sti_tablegetid_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_TABLEGETID_IEC) (sti_tablegetid_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TABLEGETID_NOTIMPLEMENTED)
	#define USE_sti_tablegetid
	#define EXT_sti_tablegetid
	#define GET_sti_tablegetid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_tablegetid(p0) 
	#define CHK_sti_tablegetid  FALSE
	#define EXP_sti_tablegetid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_tablegetid
	#define EXT_sti_tablegetid
	#define GET_sti_tablegetid(fl)  CAL_CMGETAPI( "sti_tablegetid" ) 
	#define CAL_sti_tablegetid  sti_tablegetid
	#define CHK_sti_tablegetid  TRUE
	#define EXP_sti_tablegetid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetid", (RTS_UINTPTR)sti_tablegetid, 1, RTSITF_GET_SIGNATURE(0, 0xEF20A927), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_tablegetid
	#define EXT_sti_tablegetid
	#define GET_sti_tablegetid(fl)  CAL_CMGETAPI( "sti_tablegetid" ) 
	#define CAL_sti_tablegetid  sti_tablegetid
	#define CHK_sti_tablegetid  TRUE
	#define EXP_sti_tablegetid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetid", (RTS_UINTPTR)sti_tablegetid, 1, RTSITF_GET_SIGNATURE(0, 0xEF20A927), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_tablegetid
	#define EXT_CmpCAAStoragesti_tablegetid
	#define GET_CmpCAAStoragesti_tablegetid  ERR_OK
	#define CAL_CmpCAAStoragesti_tablegetid  sti_tablegetid
	#define CHK_CmpCAAStoragesti_tablegetid  TRUE
	#define EXP_CmpCAAStoragesti_tablegetid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetid", (RTS_UINTPTR)sti_tablegetid, 1, RTSITF_GET_SIGNATURE(0, 0xEF20A927), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_tablegetid
	#define EXT_sti_tablegetid
	#define GET_sti_tablegetid(fl)  CAL_CMGETAPI( "sti_tablegetid" ) 
	#define CAL_sti_tablegetid  sti_tablegetid
	#define CHK_sti_tablegetid  TRUE
	#define EXP_sti_tablegetid  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetid", (RTS_UINTPTR)sti_tablegetid, 1, RTSITF_GET_SIGNATURE(0, 0xEF20A927), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_tablegetid  PFSTI_TABLEGETID_IEC pfsti_tablegetid;
	#define EXT_sti_tablegetid  extern PFSTI_TABLEGETID_IEC pfsti_tablegetid;
	#define GET_sti_tablegetid(fl)  s_pfCMGetAPI2( "sti_tablegetid", (RTS_VOID_FCTPTR *)&pfsti_tablegetid, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xEF20A927), 0x03050500)
	#define CAL_sti_tablegetid  pfsti_tablegetid
	#define CHK_sti_tablegetid  (pfsti_tablegetid != NULL)
	#define EXP_sti_tablegetid   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetid", (RTS_UINTPTR)sti_tablegetid, 1, RTSITF_GET_SIGNATURE(0, 0xEF20A927), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_tablegetminmaxrowids(sti_tablegetminmaxrowids_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_TABLEGETMINMAXROWIDS_IEC) (sti_tablegetminmaxrowids_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TABLEGETMINMAXROWIDS_NOTIMPLEMENTED)
	#define USE_sti_tablegetminmaxrowids
	#define EXT_sti_tablegetminmaxrowids
	#define GET_sti_tablegetminmaxrowids(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_tablegetminmaxrowids(p0) 
	#define CHK_sti_tablegetminmaxrowids  FALSE
	#define EXP_sti_tablegetminmaxrowids  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_tablegetminmaxrowids
	#define EXT_sti_tablegetminmaxrowids
	#define GET_sti_tablegetminmaxrowids(fl)  CAL_CMGETAPI( "sti_tablegetminmaxrowids" ) 
	#define CAL_sti_tablegetminmaxrowids  sti_tablegetminmaxrowids
	#define CHK_sti_tablegetminmaxrowids  TRUE
	#define EXP_sti_tablegetminmaxrowids  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetminmaxrowids", (RTS_UINTPTR)sti_tablegetminmaxrowids, 1, RTSITF_GET_SIGNATURE(0, 0x0D54AAEA), 0x03050900) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_tablegetminmaxrowids
	#define EXT_sti_tablegetminmaxrowids
	#define GET_sti_tablegetminmaxrowids(fl)  CAL_CMGETAPI( "sti_tablegetminmaxrowids" ) 
	#define CAL_sti_tablegetminmaxrowids  sti_tablegetminmaxrowids
	#define CHK_sti_tablegetminmaxrowids  TRUE
	#define EXP_sti_tablegetminmaxrowids  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetminmaxrowids", (RTS_UINTPTR)sti_tablegetminmaxrowids, 1, RTSITF_GET_SIGNATURE(0, 0x0D54AAEA), 0x03050900) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_tablegetminmaxrowids
	#define EXT_CmpCAAStoragesti_tablegetminmaxrowids
	#define GET_CmpCAAStoragesti_tablegetminmaxrowids  ERR_OK
	#define CAL_CmpCAAStoragesti_tablegetminmaxrowids  sti_tablegetminmaxrowids
	#define CHK_CmpCAAStoragesti_tablegetminmaxrowids  TRUE
	#define EXP_CmpCAAStoragesti_tablegetminmaxrowids  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetminmaxrowids", (RTS_UINTPTR)sti_tablegetminmaxrowids, 1, RTSITF_GET_SIGNATURE(0, 0x0D54AAEA), 0x03050900) 
#elif defined(CPLUSPLUS)
	#define USE_sti_tablegetminmaxrowids
	#define EXT_sti_tablegetminmaxrowids
	#define GET_sti_tablegetminmaxrowids(fl)  CAL_CMGETAPI( "sti_tablegetminmaxrowids" ) 
	#define CAL_sti_tablegetminmaxrowids  sti_tablegetminmaxrowids
	#define CHK_sti_tablegetminmaxrowids  TRUE
	#define EXP_sti_tablegetminmaxrowids  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetminmaxrowids", (RTS_UINTPTR)sti_tablegetminmaxrowids, 1, RTSITF_GET_SIGNATURE(0, 0x0D54AAEA), 0x03050900) 
#else /* DYNAMIC_LINK */
	#define USE_sti_tablegetminmaxrowids  PFSTI_TABLEGETMINMAXROWIDS_IEC pfsti_tablegetminmaxrowids;
	#define EXT_sti_tablegetminmaxrowids  extern PFSTI_TABLEGETMINMAXROWIDS_IEC pfsti_tablegetminmaxrowids;
	#define GET_sti_tablegetminmaxrowids(fl)  s_pfCMGetAPI2( "sti_tablegetminmaxrowids", (RTS_VOID_FCTPTR *)&pfsti_tablegetminmaxrowids, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x0D54AAEA), 0x03050900)
	#define CAL_sti_tablegetminmaxrowids  pfsti_tablegetminmaxrowids
	#define CHK_sti_tablegetminmaxrowids  (pfsti_tablegetminmaxrowids != NULL)
	#define EXP_sti_tablegetminmaxrowids   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetminmaxrowids", (RTS_UINTPTR)sti_tablegetminmaxrowids, 1, RTSITF_GET_SIGNATURE(0, 0x0D54AAEA), 0x03050900) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_tablegetnumofcolumns_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_UXINT STI_TableGetNumOfColumns;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_tablegetnumofcolumns_struct;

void CDECL CDECL_EXT sti_tablegetnumofcolumns(sti_tablegetnumofcolumns_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_TABLEGETNUMOFCOLUMNS_IEC) (sti_tablegetnumofcolumns_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TABLEGETNUMOFCOLUMNS_NOTIMPLEMENTED)
	#define USE_sti_tablegetnumofcolumns
	#define EXT_sti_tablegetnumofcolumns
	#define GET_sti_tablegetnumofcolumns(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_tablegetnumofcolumns(p0) 
	#define CHK_sti_tablegetnumofcolumns  FALSE
	#define EXP_sti_tablegetnumofcolumns  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_tablegetnumofcolumns
	#define EXT_sti_tablegetnumofcolumns
	#define GET_sti_tablegetnumofcolumns(fl)  CAL_CMGETAPI( "sti_tablegetnumofcolumns" ) 
	#define CAL_sti_tablegetnumofcolumns  sti_tablegetnumofcolumns
	#define CHK_sti_tablegetnumofcolumns  TRUE
	#define EXP_sti_tablegetnumofcolumns  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetnumofcolumns", (RTS_UINTPTR)sti_tablegetnumofcolumns, 1, RTSITF_GET_SIGNATURE(0, 0x3BD52F3A), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_tablegetnumofcolumns
	#define EXT_sti_tablegetnumofcolumns
	#define GET_sti_tablegetnumofcolumns(fl)  CAL_CMGETAPI( "sti_tablegetnumofcolumns" ) 
	#define CAL_sti_tablegetnumofcolumns  sti_tablegetnumofcolumns
	#define CHK_sti_tablegetnumofcolumns  TRUE
	#define EXP_sti_tablegetnumofcolumns  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetnumofcolumns", (RTS_UINTPTR)sti_tablegetnumofcolumns, 1, RTSITF_GET_SIGNATURE(0, 0x3BD52F3A), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_tablegetnumofcolumns
	#define EXT_CmpCAAStoragesti_tablegetnumofcolumns
	#define GET_CmpCAAStoragesti_tablegetnumofcolumns  ERR_OK
	#define CAL_CmpCAAStoragesti_tablegetnumofcolumns  sti_tablegetnumofcolumns
	#define CHK_CmpCAAStoragesti_tablegetnumofcolumns  TRUE
	#define EXP_CmpCAAStoragesti_tablegetnumofcolumns  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetnumofcolumns", (RTS_UINTPTR)sti_tablegetnumofcolumns, 1, RTSITF_GET_SIGNATURE(0, 0x3BD52F3A), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_tablegetnumofcolumns
	#define EXT_sti_tablegetnumofcolumns
	#define GET_sti_tablegetnumofcolumns(fl)  CAL_CMGETAPI( "sti_tablegetnumofcolumns" ) 
	#define CAL_sti_tablegetnumofcolumns  sti_tablegetnumofcolumns
	#define CHK_sti_tablegetnumofcolumns  TRUE
	#define EXP_sti_tablegetnumofcolumns  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetnumofcolumns", (RTS_UINTPTR)sti_tablegetnumofcolumns, 1, RTSITF_GET_SIGNATURE(0, 0x3BD52F3A), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_tablegetnumofcolumns  PFSTI_TABLEGETNUMOFCOLUMNS_IEC pfsti_tablegetnumofcolumns;
	#define EXT_sti_tablegetnumofcolumns  extern PFSTI_TABLEGETNUMOFCOLUMNS_IEC pfsti_tablegetnumofcolumns;
	#define GET_sti_tablegetnumofcolumns(fl)  s_pfCMGetAPI2( "sti_tablegetnumofcolumns", (RTS_VOID_FCTPTR *)&pfsti_tablegetnumofcolumns, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x3BD52F3A), 0x03050500)
	#define CAL_sti_tablegetnumofcolumns  pfsti_tablegetnumofcolumns
	#define CHK_sti_tablegetnumofcolumns  (pfsti_tablegetnumofcolumns != NULL)
	#define EXP_sti_tablegetnumofcolumns   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetnumofcolumns", (RTS_UINTPTR)sti_tablegetnumofcolumns, 1, RTSITF_GET_SIGNATURE(0, 0x3BD52F3A), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_tablegetnumofindexes_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_UXINT STI_TableGetNumOfIndexes;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_tablegetnumofindexes_struct;

void CDECL CDECL_EXT sti_tablegetnumofindexes(sti_tablegetnumofindexes_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_TABLEGETNUMOFINDEXES_IEC) (sti_tablegetnumofindexes_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TABLEGETNUMOFINDEXES_NOTIMPLEMENTED)
	#define USE_sti_tablegetnumofindexes
	#define EXT_sti_tablegetnumofindexes
	#define GET_sti_tablegetnumofindexes(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_tablegetnumofindexes(p0) 
	#define CHK_sti_tablegetnumofindexes  FALSE
	#define EXP_sti_tablegetnumofindexes  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_tablegetnumofindexes
	#define EXT_sti_tablegetnumofindexes
	#define GET_sti_tablegetnumofindexes(fl)  CAL_CMGETAPI( "sti_tablegetnumofindexes" ) 
	#define CAL_sti_tablegetnumofindexes  sti_tablegetnumofindexes
	#define CHK_sti_tablegetnumofindexes  TRUE
	#define EXP_sti_tablegetnumofindexes  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetnumofindexes", (RTS_UINTPTR)sti_tablegetnumofindexes, 1, RTSITF_GET_SIGNATURE(0, 0x8A61B1C2), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_tablegetnumofindexes
	#define EXT_sti_tablegetnumofindexes
	#define GET_sti_tablegetnumofindexes(fl)  CAL_CMGETAPI( "sti_tablegetnumofindexes" ) 
	#define CAL_sti_tablegetnumofindexes  sti_tablegetnumofindexes
	#define CHK_sti_tablegetnumofindexes  TRUE
	#define EXP_sti_tablegetnumofindexes  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetnumofindexes", (RTS_UINTPTR)sti_tablegetnumofindexes, 1, RTSITF_GET_SIGNATURE(0, 0x8A61B1C2), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_tablegetnumofindexes
	#define EXT_CmpCAAStoragesti_tablegetnumofindexes
	#define GET_CmpCAAStoragesti_tablegetnumofindexes  ERR_OK
	#define CAL_CmpCAAStoragesti_tablegetnumofindexes  sti_tablegetnumofindexes
	#define CHK_CmpCAAStoragesti_tablegetnumofindexes  TRUE
	#define EXP_CmpCAAStoragesti_tablegetnumofindexes  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetnumofindexes", (RTS_UINTPTR)sti_tablegetnumofindexes, 1, RTSITF_GET_SIGNATURE(0, 0x8A61B1C2), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_tablegetnumofindexes
	#define EXT_sti_tablegetnumofindexes
	#define GET_sti_tablegetnumofindexes(fl)  CAL_CMGETAPI( "sti_tablegetnumofindexes" ) 
	#define CAL_sti_tablegetnumofindexes  sti_tablegetnumofindexes
	#define CHK_sti_tablegetnumofindexes  TRUE
	#define EXP_sti_tablegetnumofindexes  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetnumofindexes", (RTS_UINTPTR)sti_tablegetnumofindexes, 1, RTSITF_GET_SIGNATURE(0, 0x8A61B1C2), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_tablegetnumofindexes  PFSTI_TABLEGETNUMOFINDEXES_IEC pfsti_tablegetnumofindexes;
	#define EXT_sti_tablegetnumofindexes  extern PFSTI_TABLEGETNUMOFINDEXES_IEC pfsti_tablegetnumofindexes;
	#define GET_sti_tablegetnumofindexes(fl)  s_pfCMGetAPI2( "sti_tablegetnumofindexes", (RTS_VOID_FCTPTR *)&pfsti_tablegetnumofindexes, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x8A61B1C2), 0x03050500)
	#define CAL_sti_tablegetnumofindexes  pfsti_tablegetnumofindexes
	#define CHK_sti_tablegetnumofindexes  (pfsti_tablegetnumofindexes != NULL)
	#define EXP_sti_tablegetnumofindexes   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetnumofindexes", (RTS_UINTPTR)sti_tablegetnumofindexes, 1, RTSITF_GET_SIGNATURE(0, 0x8A61B1C2), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_tablegetnumofrows_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_UXINT STI_TableGetNumOfRows;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_tablegetnumofrows_struct;

void CDECL CDECL_EXT sti_tablegetnumofrows(sti_tablegetnumofrows_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_TABLEGETNUMOFROWS_IEC) (sti_tablegetnumofrows_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TABLEGETNUMOFROWS_NOTIMPLEMENTED)
	#define USE_sti_tablegetnumofrows
	#define EXT_sti_tablegetnumofrows
	#define GET_sti_tablegetnumofrows(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_tablegetnumofrows(p0) 
	#define CHK_sti_tablegetnumofrows  FALSE
	#define EXP_sti_tablegetnumofrows  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_tablegetnumofrows
	#define EXT_sti_tablegetnumofrows
	#define GET_sti_tablegetnumofrows(fl)  CAL_CMGETAPI( "sti_tablegetnumofrows" ) 
	#define CAL_sti_tablegetnumofrows  sti_tablegetnumofrows
	#define CHK_sti_tablegetnumofrows  TRUE
	#define EXP_sti_tablegetnumofrows  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetnumofrows", (RTS_UINTPTR)sti_tablegetnumofrows, 1, RTSITF_GET_SIGNATURE(0, 0x42EEA100), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_tablegetnumofrows
	#define EXT_sti_tablegetnumofrows
	#define GET_sti_tablegetnumofrows(fl)  CAL_CMGETAPI( "sti_tablegetnumofrows" ) 
	#define CAL_sti_tablegetnumofrows  sti_tablegetnumofrows
	#define CHK_sti_tablegetnumofrows  TRUE
	#define EXP_sti_tablegetnumofrows  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetnumofrows", (RTS_UINTPTR)sti_tablegetnumofrows, 1, RTSITF_GET_SIGNATURE(0, 0x42EEA100), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_tablegetnumofrows
	#define EXT_CmpCAAStoragesti_tablegetnumofrows
	#define GET_CmpCAAStoragesti_tablegetnumofrows  ERR_OK
	#define CAL_CmpCAAStoragesti_tablegetnumofrows  sti_tablegetnumofrows
	#define CHK_CmpCAAStoragesti_tablegetnumofrows  TRUE
	#define EXP_CmpCAAStoragesti_tablegetnumofrows  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetnumofrows", (RTS_UINTPTR)sti_tablegetnumofrows, 1, RTSITF_GET_SIGNATURE(0, 0x42EEA100), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_tablegetnumofrows
	#define EXT_sti_tablegetnumofrows
	#define GET_sti_tablegetnumofrows(fl)  CAL_CMGETAPI( "sti_tablegetnumofrows" ) 
	#define CAL_sti_tablegetnumofrows  sti_tablegetnumofrows
	#define CHK_sti_tablegetnumofrows  TRUE
	#define EXP_sti_tablegetnumofrows  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetnumofrows", (RTS_UINTPTR)sti_tablegetnumofrows, 1, RTSITF_GET_SIGNATURE(0, 0x42EEA100), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_tablegetnumofrows  PFSTI_TABLEGETNUMOFROWS_IEC pfsti_tablegetnumofrows;
	#define EXT_sti_tablegetnumofrows  extern PFSTI_TABLEGETNUMOFROWS_IEC pfsti_tablegetnumofrows;
	#define GET_sti_tablegetnumofrows(fl)  s_pfCMGetAPI2( "sti_tablegetnumofrows", (RTS_VOID_FCTPTR *)&pfsti_tablegetnumofrows, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x42EEA100), 0x03050500)
	#define CAL_sti_tablegetnumofrows  pfsti_tablegetnumofrows
	#define CHK_sti_tablegetnumofrows  (pfsti_tablegetnumofrows != NULL)
	#define EXP_sti_tablegetnumofrows   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetnumofrows", (RTS_UINTPTR)sti_tablegetnumofrows, 1, RTSITF_GET_SIGNATURE(0, 0x42EEA100), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_tablegetstorage_struct
{
	RTS_IEC_XWORD hTable;				/* VAR_INPUT */	
	RTS_IEC_XWORD STI_TableGetStorage;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_tablegetstorage_struct;

void CDECL CDECL_EXT sti_tablegetstorage(sti_tablegetstorage_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_TABLEGETSTORAGE_IEC) (sti_tablegetstorage_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TABLEGETSTORAGE_NOTIMPLEMENTED)
	#define USE_sti_tablegetstorage
	#define EXT_sti_tablegetstorage
	#define GET_sti_tablegetstorage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_tablegetstorage(p0) 
	#define CHK_sti_tablegetstorage  FALSE
	#define EXP_sti_tablegetstorage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_tablegetstorage
	#define EXT_sti_tablegetstorage
	#define GET_sti_tablegetstorage(fl)  CAL_CMGETAPI( "sti_tablegetstorage" ) 
	#define CAL_sti_tablegetstorage  sti_tablegetstorage
	#define CHK_sti_tablegetstorage  TRUE
	#define EXP_sti_tablegetstorage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetstorage", (RTS_UINTPTR)sti_tablegetstorage, 1, RTSITF_GET_SIGNATURE(0, 0xA15443A1), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_tablegetstorage
	#define EXT_sti_tablegetstorage
	#define GET_sti_tablegetstorage(fl)  CAL_CMGETAPI( "sti_tablegetstorage" ) 
	#define CAL_sti_tablegetstorage  sti_tablegetstorage
	#define CHK_sti_tablegetstorage  TRUE
	#define EXP_sti_tablegetstorage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetstorage", (RTS_UINTPTR)sti_tablegetstorage, 1, RTSITF_GET_SIGNATURE(0, 0xA15443A1), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_tablegetstorage
	#define EXT_CmpCAAStoragesti_tablegetstorage
	#define GET_CmpCAAStoragesti_tablegetstorage  ERR_OK
	#define CAL_CmpCAAStoragesti_tablegetstorage  sti_tablegetstorage
	#define CHK_CmpCAAStoragesti_tablegetstorage  TRUE
	#define EXP_CmpCAAStoragesti_tablegetstorage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetstorage", (RTS_UINTPTR)sti_tablegetstorage, 1, RTSITF_GET_SIGNATURE(0, 0xA15443A1), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_tablegetstorage
	#define EXT_sti_tablegetstorage
	#define GET_sti_tablegetstorage(fl)  CAL_CMGETAPI( "sti_tablegetstorage" ) 
	#define CAL_sti_tablegetstorage  sti_tablegetstorage
	#define CHK_sti_tablegetstorage  TRUE
	#define EXP_sti_tablegetstorage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetstorage", (RTS_UINTPTR)sti_tablegetstorage, 1, RTSITF_GET_SIGNATURE(0, 0xA15443A1), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_tablegetstorage  PFSTI_TABLEGETSTORAGE_IEC pfsti_tablegetstorage;
	#define EXT_sti_tablegetstorage  extern PFSTI_TABLEGETSTORAGE_IEC pfsti_tablegetstorage;
	#define GET_sti_tablegetstorage(fl)  s_pfCMGetAPI2( "sti_tablegetstorage", (RTS_VOID_FCTPTR *)&pfsti_tablegetstorage, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xA15443A1), 0x03050500)
	#define CAL_sti_tablegetstorage  pfsti_tablegetstorage
	#define CHK_sti_tablegetstorage  (pfsti_tablegetstorage != NULL)
	#define EXP_sti_tablegetstorage   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tablegetstorage", (RTS_UINTPTR)sti_tablegetstorage, 1, RTSITF_GET_SIGNATURE(0, 0xA15443A1), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_tableopen(sti_tableopen_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_TABLEOPEN_IEC) (sti_tableopen_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TABLEOPEN_NOTIMPLEMENTED)
	#define USE_sti_tableopen
	#define EXT_sti_tableopen
	#define GET_sti_tableopen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_tableopen(p0) 
	#define CHK_sti_tableopen  FALSE
	#define EXP_sti_tableopen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_tableopen
	#define EXT_sti_tableopen
	#define GET_sti_tableopen(fl)  CAL_CMGETAPI( "sti_tableopen" ) 
	#define CAL_sti_tableopen  sti_tableopen
	#define CHK_sti_tableopen  TRUE
	#define EXP_sti_tableopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tableopen", (RTS_UINTPTR)sti_tableopen, 1, RTSITF_GET_SIGNATURE(0, 0x97F1C519), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_tableopen
	#define EXT_sti_tableopen
	#define GET_sti_tableopen(fl)  CAL_CMGETAPI( "sti_tableopen" ) 
	#define CAL_sti_tableopen  sti_tableopen
	#define CHK_sti_tableopen  TRUE
	#define EXP_sti_tableopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tableopen", (RTS_UINTPTR)sti_tableopen, 1, RTSITF_GET_SIGNATURE(0, 0x97F1C519), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_tableopen
	#define EXT_CmpCAAStoragesti_tableopen
	#define GET_CmpCAAStoragesti_tableopen  ERR_OK
	#define CAL_CmpCAAStoragesti_tableopen  sti_tableopen
	#define CHK_CmpCAAStoragesti_tableopen  TRUE
	#define EXP_CmpCAAStoragesti_tableopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tableopen", (RTS_UINTPTR)sti_tableopen, 1, RTSITF_GET_SIGNATURE(0, 0x97F1C519), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_tableopen
	#define EXT_sti_tableopen
	#define GET_sti_tableopen(fl)  CAL_CMGETAPI( "sti_tableopen" ) 
	#define CAL_sti_tableopen  sti_tableopen
	#define CHK_sti_tableopen  TRUE
	#define EXP_sti_tableopen  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tableopen", (RTS_UINTPTR)sti_tableopen, 1, RTSITF_GET_SIGNATURE(0, 0x97F1C519), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_tableopen  PFSTI_TABLEOPEN_IEC pfsti_tableopen;
	#define EXT_sti_tableopen  extern PFSTI_TABLEOPEN_IEC pfsti_tableopen;
	#define GET_sti_tableopen(fl)  s_pfCMGetAPI2( "sti_tableopen", (RTS_VOID_FCTPTR *)&pfsti_tableopen, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x97F1C519), 0x03050500)
	#define CAL_sti_tableopen  pfsti_tableopen
	#define CHK_sti_tableopen  (pfsti_tableopen != NULL)
	#define EXP_sti_tableopen   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_tableopen", (RTS_UINTPTR)sti_tableopen, 1, RTSITF_GET_SIGNATURE(0, 0x97F1C519), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_transactionbegin(sti_transactionbegin_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_TRANSACTIONBEGIN_IEC) (sti_transactionbegin_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TRANSACTIONBEGIN_NOTIMPLEMENTED)
	#define USE_sti_transactionbegin
	#define EXT_sti_transactionbegin
	#define GET_sti_transactionbegin(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_transactionbegin(p0) 
	#define CHK_sti_transactionbegin  FALSE
	#define EXP_sti_transactionbegin  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_transactionbegin
	#define EXT_sti_transactionbegin
	#define GET_sti_transactionbegin(fl)  CAL_CMGETAPI( "sti_transactionbegin" ) 
	#define CAL_sti_transactionbegin  sti_transactionbegin
	#define CHK_sti_transactionbegin  TRUE
	#define EXP_sti_transactionbegin  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactionbegin", (RTS_UINTPTR)sti_transactionbegin, 1, RTSITF_GET_SIGNATURE(0, 0xF402E0CD), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_transactionbegin
	#define EXT_sti_transactionbegin
	#define GET_sti_transactionbegin(fl)  CAL_CMGETAPI( "sti_transactionbegin" ) 
	#define CAL_sti_transactionbegin  sti_transactionbegin
	#define CHK_sti_transactionbegin  TRUE
	#define EXP_sti_transactionbegin  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactionbegin", (RTS_UINTPTR)sti_transactionbegin, 1, RTSITF_GET_SIGNATURE(0, 0xF402E0CD), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_transactionbegin
	#define EXT_CmpCAAStoragesti_transactionbegin
	#define GET_CmpCAAStoragesti_transactionbegin  ERR_OK
	#define CAL_CmpCAAStoragesti_transactionbegin  sti_transactionbegin
	#define CHK_CmpCAAStoragesti_transactionbegin  TRUE
	#define EXP_CmpCAAStoragesti_transactionbegin  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactionbegin", (RTS_UINTPTR)sti_transactionbegin, 1, RTSITF_GET_SIGNATURE(0, 0xF402E0CD), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_transactionbegin
	#define EXT_sti_transactionbegin
	#define GET_sti_transactionbegin(fl)  CAL_CMGETAPI( "sti_transactionbegin" ) 
	#define CAL_sti_transactionbegin  sti_transactionbegin
	#define CHK_sti_transactionbegin  TRUE
	#define EXP_sti_transactionbegin  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactionbegin", (RTS_UINTPTR)sti_transactionbegin, 1, RTSITF_GET_SIGNATURE(0, 0xF402E0CD), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_transactionbegin  PFSTI_TRANSACTIONBEGIN_IEC pfsti_transactionbegin;
	#define EXT_sti_transactionbegin  extern PFSTI_TRANSACTIONBEGIN_IEC pfsti_transactionbegin;
	#define GET_sti_transactionbegin(fl)  s_pfCMGetAPI2( "sti_transactionbegin", (RTS_VOID_FCTPTR *)&pfsti_transactionbegin, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xF402E0CD), 0x03050500)
	#define CAL_sti_transactionbegin  pfsti_transactionbegin
	#define CHK_sti_transactionbegin  (pfsti_transactionbegin != NULL)
	#define EXP_sti_transactionbegin   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactionbegin", (RTS_UINTPTR)sti_transactionbegin, 1, RTSITF_GET_SIGNATURE(0, 0xF402E0CD), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_transactioncommit_struct
{
	RTS_IEC_XWORD hTransaction;			/* VAR_INPUT */	
	RTS_IEC_INT STI_TransactionCommit;	/* VAR_OUTPUT, Enum: ERROR */
} sti_transactioncommit_struct;

void CDECL CDECL_EXT sti_transactioncommit(sti_transactioncommit_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_TRANSACTIONCOMMIT_IEC) (sti_transactioncommit_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TRANSACTIONCOMMIT_NOTIMPLEMENTED)
	#define USE_sti_transactioncommit
	#define EXT_sti_transactioncommit
	#define GET_sti_transactioncommit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_transactioncommit(p0) 
	#define CHK_sti_transactioncommit  FALSE
	#define EXP_sti_transactioncommit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_transactioncommit
	#define EXT_sti_transactioncommit
	#define GET_sti_transactioncommit(fl)  CAL_CMGETAPI( "sti_transactioncommit" ) 
	#define CAL_sti_transactioncommit  sti_transactioncommit
	#define CHK_sti_transactioncommit  TRUE
	#define EXP_sti_transactioncommit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactioncommit", (RTS_UINTPTR)sti_transactioncommit, 1, RTSITF_GET_SIGNATURE(0, 0x89DDC223), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_transactioncommit
	#define EXT_sti_transactioncommit
	#define GET_sti_transactioncommit(fl)  CAL_CMGETAPI( "sti_transactioncommit" ) 
	#define CAL_sti_transactioncommit  sti_transactioncommit
	#define CHK_sti_transactioncommit  TRUE
	#define EXP_sti_transactioncommit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactioncommit", (RTS_UINTPTR)sti_transactioncommit, 1, RTSITF_GET_SIGNATURE(0, 0x89DDC223), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_transactioncommit
	#define EXT_CmpCAAStoragesti_transactioncommit
	#define GET_CmpCAAStoragesti_transactioncommit  ERR_OK
	#define CAL_CmpCAAStoragesti_transactioncommit  sti_transactioncommit
	#define CHK_CmpCAAStoragesti_transactioncommit  TRUE
	#define EXP_CmpCAAStoragesti_transactioncommit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactioncommit", (RTS_UINTPTR)sti_transactioncommit, 1, RTSITF_GET_SIGNATURE(0, 0x89DDC223), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_transactioncommit
	#define EXT_sti_transactioncommit
	#define GET_sti_transactioncommit(fl)  CAL_CMGETAPI( "sti_transactioncommit" ) 
	#define CAL_sti_transactioncommit  sti_transactioncommit
	#define CHK_sti_transactioncommit  TRUE
	#define EXP_sti_transactioncommit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactioncommit", (RTS_UINTPTR)sti_transactioncommit, 1, RTSITF_GET_SIGNATURE(0, 0x89DDC223), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_transactioncommit  PFSTI_TRANSACTIONCOMMIT_IEC pfsti_transactioncommit;
	#define EXT_sti_transactioncommit  extern PFSTI_TRANSACTIONCOMMIT_IEC pfsti_transactioncommit;
	#define GET_sti_transactioncommit(fl)  s_pfCMGetAPI2( "sti_transactioncommit", (RTS_VOID_FCTPTR *)&pfsti_transactioncommit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x89DDC223), 0x03050500)
	#define CAL_sti_transactioncommit  pfsti_transactioncommit
	#define CHK_sti_transactioncommit  (pfsti_transactioncommit != NULL)
	#define EXP_sti_transactioncommit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactioncommit", (RTS_UINTPTR)sti_transactioncommit, 1, RTSITF_GET_SIGNATURE(0, 0x89DDC223), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_transactiongetstorage_struct
{
	RTS_IEC_XWORD hTransaction;			/* VAR_INPUT */	
	RTS_IEC_XWORD STI_TransactionGetStorage;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_transactiongetstorage_struct;

void CDECL CDECL_EXT sti_transactiongetstorage(sti_transactiongetstorage_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_TRANSACTIONGETSTORAGE_IEC) (sti_transactiongetstorage_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TRANSACTIONGETSTORAGE_NOTIMPLEMENTED)
	#define USE_sti_transactiongetstorage
	#define EXT_sti_transactiongetstorage
	#define GET_sti_transactiongetstorage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_transactiongetstorage(p0) 
	#define CHK_sti_transactiongetstorage  FALSE
	#define EXP_sti_transactiongetstorage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_transactiongetstorage
	#define EXT_sti_transactiongetstorage
	#define GET_sti_transactiongetstorage(fl)  CAL_CMGETAPI( "sti_transactiongetstorage" ) 
	#define CAL_sti_transactiongetstorage  sti_transactiongetstorage
	#define CHK_sti_transactiongetstorage  TRUE
	#define EXP_sti_transactiongetstorage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactiongetstorage", (RTS_UINTPTR)sti_transactiongetstorage, 1, RTSITF_GET_SIGNATURE(0, 0x38993503), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_transactiongetstorage
	#define EXT_sti_transactiongetstorage
	#define GET_sti_transactiongetstorage(fl)  CAL_CMGETAPI( "sti_transactiongetstorage" ) 
	#define CAL_sti_transactiongetstorage  sti_transactiongetstorage
	#define CHK_sti_transactiongetstorage  TRUE
	#define EXP_sti_transactiongetstorage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactiongetstorage", (RTS_UINTPTR)sti_transactiongetstorage, 1, RTSITF_GET_SIGNATURE(0, 0x38993503), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_transactiongetstorage
	#define EXT_CmpCAAStoragesti_transactiongetstorage
	#define GET_CmpCAAStoragesti_transactiongetstorage  ERR_OK
	#define CAL_CmpCAAStoragesti_transactiongetstorage  sti_transactiongetstorage
	#define CHK_CmpCAAStoragesti_transactiongetstorage  TRUE
	#define EXP_CmpCAAStoragesti_transactiongetstorage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactiongetstorage", (RTS_UINTPTR)sti_transactiongetstorage, 1, RTSITF_GET_SIGNATURE(0, 0x38993503), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_transactiongetstorage
	#define EXT_sti_transactiongetstorage
	#define GET_sti_transactiongetstorage(fl)  CAL_CMGETAPI( "sti_transactiongetstorage" ) 
	#define CAL_sti_transactiongetstorage  sti_transactiongetstorage
	#define CHK_sti_transactiongetstorage  TRUE
	#define EXP_sti_transactiongetstorage  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactiongetstorage", (RTS_UINTPTR)sti_transactiongetstorage, 1, RTSITF_GET_SIGNATURE(0, 0x38993503), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_transactiongetstorage  PFSTI_TRANSACTIONGETSTORAGE_IEC pfsti_transactiongetstorage;
	#define EXT_sti_transactiongetstorage  extern PFSTI_TRANSACTIONGETSTORAGE_IEC pfsti_transactiongetstorage;
	#define GET_sti_transactiongetstorage(fl)  s_pfCMGetAPI2( "sti_transactiongetstorage", (RTS_VOID_FCTPTR *)&pfsti_transactiongetstorage, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x38993503), 0x03050500)
	#define CAL_sti_transactiongetstorage  pfsti_transactiongetstorage
	#define CHK_sti_transactiongetstorage  (pfsti_transactiongetstorage != NULL)
	#define EXP_sti_transactiongetstorage   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactiongetstorage", (RTS_UINTPTR)sti_transactiongetstorage, 1, RTSITF_GET_SIGNATURE(0, 0x38993503), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_transactionrollback_struct
{
	RTS_IEC_XWORD hTransaction;			/* VAR_INPUT */	
	RTS_IEC_INT STI_TransactionRollback;	/* VAR_OUTPUT, Enum: ERROR */
} sti_transactionrollback_struct;

void CDECL CDECL_EXT sti_transactionrollback(sti_transactionrollback_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_TRANSACTIONROLLBACK_IEC) (sti_transactionrollback_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TRANSACTIONROLLBACK_NOTIMPLEMENTED)
	#define USE_sti_transactionrollback
	#define EXT_sti_transactionrollback
	#define GET_sti_transactionrollback(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_transactionrollback(p0) 
	#define CHK_sti_transactionrollback  FALSE
	#define EXP_sti_transactionrollback  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_transactionrollback
	#define EXT_sti_transactionrollback
	#define GET_sti_transactionrollback(fl)  CAL_CMGETAPI( "sti_transactionrollback" ) 
	#define CAL_sti_transactionrollback  sti_transactionrollback
	#define CHK_sti_transactionrollback  TRUE
	#define EXP_sti_transactionrollback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactionrollback", (RTS_UINTPTR)sti_transactionrollback, 1, RTSITF_GET_SIGNATURE(0, 0xD9E1C5A2), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_transactionrollback
	#define EXT_sti_transactionrollback
	#define GET_sti_transactionrollback(fl)  CAL_CMGETAPI( "sti_transactionrollback" ) 
	#define CAL_sti_transactionrollback  sti_transactionrollback
	#define CHK_sti_transactionrollback  TRUE
	#define EXP_sti_transactionrollback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactionrollback", (RTS_UINTPTR)sti_transactionrollback, 1, RTSITF_GET_SIGNATURE(0, 0xD9E1C5A2), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_transactionrollback
	#define EXT_CmpCAAStoragesti_transactionrollback
	#define GET_CmpCAAStoragesti_transactionrollback  ERR_OK
	#define CAL_CmpCAAStoragesti_transactionrollback  sti_transactionrollback
	#define CHK_CmpCAAStoragesti_transactionrollback  TRUE
	#define EXP_CmpCAAStoragesti_transactionrollback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactionrollback", (RTS_UINTPTR)sti_transactionrollback, 1, RTSITF_GET_SIGNATURE(0, 0xD9E1C5A2), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_transactionrollback
	#define EXT_sti_transactionrollback
	#define GET_sti_transactionrollback(fl)  CAL_CMGETAPI( "sti_transactionrollback" ) 
	#define CAL_sti_transactionrollback  sti_transactionrollback
	#define CHK_sti_transactionrollback  TRUE
	#define EXP_sti_transactionrollback  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactionrollback", (RTS_UINTPTR)sti_transactionrollback, 1, RTSITF_GET_SIGNATURE(0, 0xD9E1C5A2), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_transactionrollback  PFSTI_TRANSACTIONROLLBACK_IEC pfsti_transactionrollback;
	#define EXT_sti_transactionrollback  extern PFSTI_TRANSACTIONROLLBACK_IEC pfsti_transactionrollback;
	#define GET_sti_transactionrollback(fl)  s_pfCMGetAPI2( "sti_transactionrollback", (RTS_VOID_FCTPTR *)&pfsti_transactionrollback, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xD9E1C5A2), 0x03050500)
	#define CAL_sti_transactionrollback  pfsti_transactionrollback
	#define CHK_sti_transactionrollback  (pfsti_transactionrollback != NULL)
	#define EXP_sti_transactionrollback   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactionrollback", (RTS_UINTPTR)sti_transactionrollback, 1, RTSITF_GET_SIGNATURE(0, 0xD9E1C5A2), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_transactionsetsavepoint_struct
{
	RTS_IEC_XWORD hTransaction;			/* VAR_INPUT */	
	RTS_IEC_XWORD STI_TransactionSetSavepoint;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_transactionsetsavepoint_struct;

void CDECL CDECL_EXT sti_transactionsetsavepoint(sti_transactionsetsavepoint_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_TRANSACTIONSETSAVEPOINT_IEC) (sti_transactionsetsavepoint_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TRANSACTIONSETSAVEPOINT_NOTIMPLEMENTED)
	#define USE_sti_transactionsetsavepoint
	#define EXT_sti_transactionsetsavepoint
	#define GET_sti_transactionsetsavepoint(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_transactionsetsavepoint(p0) 
	#define CHK_sti_transactionsetsavepoint  FALSE
	#define EXP_sti_transactionsetsavepoint  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_transactionsetsavepoint
	#define EXT_sti_transactionsetsavepoint
	#define GET_sti_transactionsetsavepoint(fl)  CAL_CMGETAPI( "sti_transactionsetsavepoint" ) 
	#define CAL_sti_transactionsetsavepoint  sti_transactionsetsavepoint
	#define CHK_sti_transactionsetsavepoint  TRUE
	#define EXP_sti_transactionsetsavepoint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactionsetsavepoint", (RTS_UINTPTR)sti_transactionsetsavepoint, 1, RTSITF_GET_SIGNATURE(0, 0x9A6EFA3F), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_transactionsetsavepoint
	#define EXT_sti_transactionsetsavepoint
	#define GET_sti_transactionsetsavepoint(fl)  CAL_CMGETAPI( "sti_transactionsetsavepoint" ) 
	#define CAL_sti_transactionsetsavepoint  sti_transactionsetsavepoint
	#define CHK_sti_transactionsetsavepoint  TRUE
	#define EXP_sti_transactionsetsavepoint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactionsetsavepoint", (RTS_UINTPTR)sti_transactionsetsavepoint, 1, RTSITF_GET_SIGNATURE(0, 0x9A6EFA3F), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_transactionsetsavepoint
	#define EXT_CmpCAAStoragesti_transactionsetsavepoint
	#define GET_CmpCAAStoragesti_transactionsetsavepoint  ERR_OK
	#define CAL_CmpCAAStoragesti_transactionsetsavepoint  sti_transactionsetsavepoint
	#define CHK_CmpCAAStoragesti_transactionsetsavepoint  TRUE
	#define EXP_CmpCAAStoragesti_transactionsetsavepoint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactionsetsavepoint", (RTS_UINTPTR)sti_transactionsetsavepoint, 1, RTSITF_GET_SIGNATURE(0, 0x9A6EFA3F), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_transactionsetsavepoint
	#define EXT_sti_transactionsetsavepoint
	#define GET_sti_transactionsetsavepoint(fl)  CAL_CMGETAPI( "sti_transactionsetsavepoint" ) 
	#define CAL_sti_transactionsetsavepoint  sti_transactionsetsavepoint
	#define CHK_sti_transactionsetsavepoint  TRUE
	#define EXP_sti_transactionsetsavepoint  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactionsetsavepoint", (RTS_UINTPTR)sti_transactionsetsavepoint, 1, RTSITF_GET_SIGNATURE(0, 0x9A6EFA3F), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_transactionsetsavepoint  PFSTI_TRANSACTIONSETSAVEPOINT_IEC pfsti_transactionsetsavepoint;
	#define EXT_sti_transactionsetsavepoint  extern PFSTI_TRANSACTIONSETSAVEPOINT_IEC pfsti_transactionsetsavepoint;
	#define GET_sti_transactionsetsavepoint(fl)  s_pfCMGetAPI2( "sti_transactionsetsavepoint", (RTS_VOID_FCTPTR *)&pfsti_transactionsetsavepoint, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x9A6EFA3F), 0x03050500)
	#define CAL_sti_transactionsetsavepoint  pfsti_transactionsetsavepoint
	#define CHK_sti_transactionsetsavepoint  (pfsti_transactionsetsavepoint != NULL)
	#define EXP_sti_transactionsetsavepoint   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_transactionsetsavepoint", (RTS_UINTPTR)sti_transactionsetsavepoint, 1, RTSITF_GET_SIGNATURE(0, 0x9A6EFA3F), 0x03050500) 
#endif


/**
 * = SignatureFlag.SimulationExternal = link even in simulation mode
 */
typedef struct tagsti_utilitygetcurrentdateandtime_struct
{
	RTS_IEC_XWORD hStorage;				/* VAR_INPUT */	
	RTS_IEC_LINT STI_UtilityGetCurrentDateAndTime;	/* VAR_OUTPUT */	
	RTS_IEC_INT eError;					/* VAR_OUTPUT, Enum: ERROR */
} sti_utilitygetcurrentdateandtime_struct;

void CDECL CDECL_EXT sti_utilitygetcurrentdateandtime(sti_utilitygetcurrentdateandtime_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_UTILITYGETCURRENTDATEANDTIME_IEC) (sti_utilitygetcurrentdateandtime_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_UTILITYGETCURRENTDATEANDTIME_NOTIMPLEMENTED)
	#define USE_sti_utilitygetcurrentdateandtime
	#define EXT_sti_utilitygetcurrentdateandtime
	#define GET_sti_utilitygetcurrentdateandtime(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_utilitygetcurrentdateandtime(p0) 
	#define CHK_sti_utilitygetcurrentdateandtime  FALSE
	#define EXP_sti_utilitygetcurrentdateandtime  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_utilitygetcurrentdateandtime
	#define EXT_sti_utilitygetcurrentdateandtime
	#define GET_sti_utilitygetcurrentdateandtime(fl)  CAL_CMGETAPI( "sti_utilitygetcurrentdateandtime" ) 
	#define CAL_sti_utilitygetcurrentdateandtime  sti_utilitygetcurrentdateandtime
	#define CHK_sti_utilitygetcurrentdateandtime  TRUE
	#define EXP_sti_utilitygetcurrentdateandtime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_utilitygetcurrentdateandtime", (RTS_UINTPTR)sti_utilitygetcurrentdateandtime, 1, RTSITF_GET_SIGNATURE(0, 0x452BD59D), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_utilitygetcurrentdateandtime
	#define EXT_sti_utilitygetcurrentdateandtime
	#define GET_sti_utilitygetcurrentdateandtime(fl)  CAL_CMGETAPI( "sti_utilitygetcurrentdateandtime" ) 
	#define CAL_sti_utilitygetcurrentdateandtime  sti_utilitygetcurrentdateandtime
	#define CHK_sti_utilitygetcurrentdateandtime  TRUE
	#define EXP_sti_utilitygetcurrentdateandtime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_utilitygetcurrentdateandtime", (RTS_UINTPTR)sti_utilitygetcurrentdateandtime, 1, RTSITF_GET_SIGNATURE(0, 0x452BD59D), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_utilitygetcurrentdateandtime
	#define EXT_CmpCAAStoragesti_utilitygetcurrentdateandtime
	#define GET_CmpCAAStoragesti_utilitygetcurrentdateandtime  ERR_OK
	#define CAL_CmpCAAStoragesti_utilitygetcurrentdateandtime  sti_utilitygetcurrentdateandtime
	#define CHK_CmpCAAStoragesti_utilitygetcurrentdateandtime  TRUE
	#define EXP_CmpCAAStoragesti_utilitygetcurrentdateandtime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_utilitygetcurrentdateandtime", (RTS_UINTPTR)sti_utilitygetcurrentdateandtime, 1, RTSITF_GET_SIGNATURE(0, 0x452BD59D), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_utilitygetcurrentdateandtime
	#define EXT_sti_utilitygetcurrentdateandtime
	#define GET_sti_utilitygetcurrentdateandtime(fl)  CAL_CMGETAPI( "sti_utilitygetcurrentdateandtime" ) 
	#define CAL_sti_utilitygetcurrentdateandtime  sti_utilitygetcurrentdateandtime
	#define CHK_sti_utilitygetcurrentdateandtime  TRUE
	#define EXP_sti_utilitygetcurrentdateandtime  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_utilitygetcurrentdateandtime", (RTS_UINTPTR)sti_utilitygetcurrentdateandtime, 1, RTSITF_GET_SIGNATURE(0, 0x452BD59D), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_utilitygetcurrentdateandtime  PFSTI_UTILITYGETCURRENTDATEANDTIME_IEC pfsti_utilitygetcurrentdateandtime;
	#define EXT_sti_utilitygetcurrentdateandtime  extern PFSTI_UTILITYGETCURRENTDATEANDTIME_IEC pfsti_utilitygetcurrentdateandtime;
	#define GET_sti_utilitygetcurrentdateandtime(fl)  s_pfCMGetAPI2( "sti_utilitygetcurrentdateandtime", (RTS_VOID_FCTPTR *)&pfsti_utilitygetcurrentdateandtime, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0x452BD59D), 0x03050500)
	#define CAL_sti_utilitygetcurrentdateandtime  pfsti_utilitygetcurrentdateandtime
	#define CHK_sti_utilitygetcurrentdateandtime  (pfsti_utilitygetcurrentdateandtime != NULL)
	#define EXP_sti_utilitygetcurrentdateandtime   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_utilitygetcurrentdateandtime", (RTS_UINTPTR)sti_utilitygetcurrentdateandtime, 1, RTSITF_GET_SIGNATURE(0, 0x452BD59D), 0x03050500) 
#endif


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

void CDECL CDECL_EXT sti_utilityrandomness(sti_utilityrandomness_struct *p);
typedef void (CDECL CDECL_EXT* PFSTI_UTILITYRANDOMNESS_IEC) (sti_utilityrandomness_struct *p);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_UTILITYRANDOMNESS_NOTIMPLEMENTED)
	#define USE_sti_utilityrandomness
	#define EXT_sti_utilityrandomness
	#define GET_sti_utilityrandomness(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sti_utilityrandomness(p0) 
	#define CHK_sti_utilityrandomness  FALSE
	#define EXP_sti_utilityrandomness  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sti_utilityrandomness
	#define EXT_sti_utilityrandomness
	#define GET_sti_utilityrandomness(fl)  CAL_CMGETAPI( "sti_utilityrandomness" ) 
	#define CAL_sti_utilityrandomness  sti_utilityrandomness
	#define CHK_sti_utilityrandomness  TRUE
	#define EXP_sti_utilityrandomness  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_utilityrandomness", (RTS_UINTPTR)sti_utilityrandomness, 1, RTSITF_GET_SIGNATURE(0, 0xCFDCFE92), 0x03050500) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_sti_utilityrandomness
	#define EXT_sti_utilityrandomness
	#define GET_sti_utilityrandomness(fl)  CAL_CMGETAPI( "sti_utilityrandomness" ) 
	#define CAL_sti_utilityrandomness  sti_utilityrandomness
	#define CHK_sti_utilityrandomness  TRUE
	#define EXP_sti_utilityrandomness  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_utilityrandomness", (RTS_UINTPTR)sti_utilityrandomness, 1, RTSITF_GET_SIGNATURE(0, 0xCFDCFE92), 0x03050500) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStoragesti_utilityrandomness
	#define EXT_CmpCAAStoragesti_utilityrandomness
	#define GET_CmpCAAStoragesti_utilityrandomness  ERR_OK
	#define CAL_CmpCAAStoragesti_utilityrandomness  sti_utilityrandomness
	#define CHK_CmpCAAStoragesti_utilityrandomness  TRUE
	#define EXP_CmpCAAStoragesti_utilityrandomness  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_utilityrandomness", (RTS_UINTPTR)sti_utilityrandomness, 1, RTSITF_GET_SIGNATURE(0, 0xCFDCFE92), 0x03050500) 
#elif defined(CPLUSPLUS)
	#define USE_sti_utilityrandomness
	#define EXT_sti_utilityrandomness
	#define GET_sti_utilityrandomness(fl)  CAL_CMGETAPI( "sti_utilityrandomness" ) 
	#define CAL_sti_utilityrandomness  sti_utilityrandomness
	#define CHK_sti_utilityrandomness  TRUE
	#define EXP_sti_utilityrandomness  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_utilityrandomness", (RTS_UINTPTR)sti_utilityrandomness, 1, RTSITF_GET_SIGNATURE(0, 0xCFDCFE92), 0x03050500) 
#else /* DYNAMIC_LINK */
	#define USE_sti_utilityrandomness  PFSTI_UTILITYRANDOMNESS_IEC pfsti_utilityrandomness;
	#define EXT_sti_utilityrandomness  extern PFSTI_UTILITYRANDOMNESS_IEC pfsti_utilityrandomness;
	#define GET_sti_utilityrandomness(fl)  s_pfCMGetAPI2( "sti_utilityrandomness", (RTS_VOID_FCTPTR *)&pfsti_utilityrandomness, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0, 0xCFDCFE92), 0x03050500)
	#define CAL_sti_utilityrandomness  pfsti_utilityrandomness
	#define CHK_sti_utilityrandomness  (pfsti_utilityrandomness != NULL)
	#define EXP_sti_utilityrandomness   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sti_utilityrandomness", (RTS_UINTPTR)sti_utilityrandomness, 1, RTSITF_GET_SIGNATURE(0, 0xCFDCFE92), 0x03050500) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

STO_BLOB* CDECL STO_BlobAlloc(CAA_SIZE szData, STO_ERROR *peError);
typedef STO_BLOB* (CDECL * PFSTO_BLOBALLOC) (CAA_SIZE szData, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_BLOBALLOC_NOTIMPLEMENTED)
	#define USE_STO_BlobAlloc
	#define EXT_STO_BlobAlloc
	#define GET_STO_BlobAlloc(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_BlobAlloc(p0,p1)  (STO_BLOB*)ERR_NOTIMPLEMENTED
	#define CHK_STO_BlobAlloc  FALSE
	#define EXP_STO_BlobAlloc  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_BlobAlloc
	#define EXT_STO_BlobAlloc
	#define GET_STO_BlobAlloc(fl)  CAL_CMGETAPI( "STO_BlobAlloc" ) 
	#define CAL_STO_BlobAlloc  STO_BlobAlloc
	#define CHK_STO_BlobAlloc  TRUE
	#define EXP_STO_BlobAlloc  CAL_CMEXPAPI( "STO_BlobAlloc" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_BlobAlloc
	#define EXT_STO_BlobAlloc
	#define GET_STO_BlobAlloc(fl)  CAL_CMGETAPI( "STO_BlobAlloc" ) 
	#define CAL_STO_BlobAlloc  STO_BlobAlloc
	#define CHK_STO_BlobAlloc  TRUE
	#define EXP_STO_BlobAlloc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_BlobAlloc", (RTS_UINTPTR)STO_BlobAlloc, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_BlobAlloc
	#define EXT_CmpCAAStorageSTO_BlobAlloc
	#define GET_CmpCAAStorageSTO_BlobAlloc  ERR_OK
	#define CAL_CmpCAAStorageSTO_BlobAlloc pICmpCAAStorage->ISTO_BlobAlloc
	#define CHK_CmpCAAStorageSTO_BlobAlloc (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_BlobAlloc  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_BlobAlloc
	#define EXT_STO_BlobAlloc
	#define GET_STO_BlobAlloc(fl)  CAL_CMGETAPI( "STO_BlobAlloc" ) 
	#define CAL_STO_BlobAlloc pICmpCAAStorage->ISTO_BlobAlloc
	#define CHK_STO_BlobAlloc (pICmpCAAStorage != NULL)
	#define EXP_STO_BlobAlloc  CAL_CMEXPAPI( "STO_BlobAlloc" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_BlobAlloc  PFSTO_BLOBALLOC pfSTO_BlobAlloc;
	#define EXT_STO_BlobAlloc  extern PFSTO_BLOBALLOC pfSTO_BlobAlloc;
	#define GET_STO_BlobAlloc(fl)  s_pfCMGetAPI2( "STO_BlobAlloc", (RTS_VOID_FCTPTR *)&pfSTO_BlobAlloc, (fl), 0, 0)
	#define CAL_STO_BlobAlloc  pfSTO_BlobAlloc
	#define CHK_STO_BlobAlloc  (pfSTO_BlobAlloc != NULL)
	#define EXP_STO_BlobAlloc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_BlobAlloc", (RTS_UINTPTR)STO_BlobAlloc, 0, 0) 
#endif



STO_ERROR CDECL STO_BlobCopyToData(STO_BLOB* pBlob, CAA_BYTE* pData, CAA_SIZE szData);
typedef STO_ERROR (CDECL * PFSTO_BLOBCOPYTODATA) (STO_BLOB* pBlob, CAA_BYTE* pData, CAA_SIZE szData);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_BLOBCOPYTODATA_NOTIMPLEMENTED)
	#define USE_STO_BlobCopyToData
	#define EXT_STO_BlobCopyToData
	#define GET_STO_BlobCopyToData(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_BlobCopyToData(p0,p1,p2)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_BlobCopyToData  FALSE
	#define EXP_STO_BlobCopyToData  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_BlobCopyToData
	#define EXT_STO_BlobCopyToData
	#define GET_STO_BlobCopyToData(fl)  CAL_CMGETAPI( "STO_BlobCopyToData" ) 
	#define CAL_STO_BlobCopyToData  STO_BlobCopyToData
	#define CHK_STO_BlobCopyToData  TRUE
	#define EXP_STO_BlobCopyToData  CAL_CMEXPAPI( "STO_BlobCopyToData" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_BlobCopyToData
	#define EXT_STO_BlobCopyToData
	#define GET_STO_BlobCopyToData(fl)  CAL_CMGETAPI( "STO_BlobCopyToData" ) 
	#define CAL_STO_BlobCopyToData  STO_BlobCopyToData
	#define CHK_STO_BlobCopyToData  TRUE
	#define EXP_STO_BlobCopyToData  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_BlobCopyToData", (RTS_UINTPTR)STO_BlobCopyToData, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_BlobCopyToData
	#define EXT_CmpCAAStorageSTO_BlobCopyToData
	#define GET_CmpCAAStorageSTO_BlobCopyToData  ERR_OK
	#define CAL_CmpCAAStorageSTO_BlobCopyToData pICmpCAAStorage->ISTO_BlobCopyToData
	#define CHK_CmpCAAStorageSTO_BlobCopyToData (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_BlobCopyToData  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_BlobCopyToData
	#define EXT_STO_BlobCopyToData
	#define GET_STO_BlobCopyToData(fl)  CAL_CMGETAPI( "STO_BlobCopyToData" ) 
	#define CAL_STO_BlobCopyToData pICmpCAAStorage->ISTO_BlobCopyToData
	#define CHK_STO_BlobCopyToData (pICmpCAAStorage != NULL)
	#define EXP_STO_BlobCopyToData  CAL_CMEXPAPI( "STO_BlobCopyToData" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_BlobCopyToData  PFSTO_BLOBCOPYTODATA pfSTO_BlobCopyToData;
	#define EXT_STO_BlobCopyToData  extern PFSTO_BLOBCOPYTODATA pfSTO_BlobCopyToData;
	#define GET_STO_BlobCopyToData(fl)  s_pfCMGetAPI2( "STO_BlobCopyToData", (RTS_VOID_FCTPTR *)&pfSTO_BlobCopyToData, (fl), 0, 0)
	#define CAL_STO_BlobCopyToData  pfSTO_BlobCopyToData
	#define CHK_STO_BlobCopyToData  (pfSTO_BlobCopyToData != NULL)
	#define EXP_STO_BlobCopyToData  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_BlobCopyToData", (RTS_UINTPTR)STO_BlobCopyToData, 0, 0) 
#endif



STO_ERROR CDECL STO_BlobFree(STO_BLOB* pBlob);
typedef STO_ERROR (CDECL * PFSTO_BLOBFREE) (STO_BLOB* pBlob);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_BLOBFREE_NOTIMPLEMENTED)
	#define USE_STO_BlobFree
	#define EXT_STO_BlobFree
	#define GET_STO_BlobFree(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_BlobFree(p0)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_BlobFree  FALSE
	#define EXP_STO_BlobFree  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_BlobFree
	#define EXT_STO_BlobFree
	#define GET_STO_BlobFree(fl)  CAL_CMGETAPI( "STO_BlobFree" ) 
	#define CAL_STO_BlobFree  STO_BlobFree
	#define CHK_STO_BlobFree  TRUE
	#define EXP_STO_BlobFree  CAL_CMEXPAPI( "STO_BlobFree" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_BlobFree
	#define EXT_STO_BlobFree
	#define GET_STO_BlobFree(fl)  CAL_CMGETAPI( "STO_BlobFree" ) 
	#define CAL_STO_BlobFree  STO_BlobFree
	#define CHK_STO_BlobFree  TRUE
	#define EXP_STO_BlobFree  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_BlobFree", (RTS_UINTPTR)STO_BlobFree, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_BlobFree
	#define EXT_CmpCAAStorageSTO_BlobFree
	#define GET_CmpCAAStorageSTO_BlobFree  ERR_OK
	#define CAL_CmpCAAStorageSTO_BlobFree pICmpCAAStorage->ISTO_BlobFree
	#define CHK_CmpCAAStorageSTO_BlobFree (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_BlobFree  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_BlobFree
	#define EXT_STO_BlobFree
	#define GET_STO_BlobFree(fl)  CAL_CMGETAPI( "STO_BlobFree" ) 
	#define CAL_STO_BlobFree pICmpCAAStorage->ISTO_BlobFree
	#define CHK_STO_BlobFree (pICmpCAAStorage != NULL)
	#define EXP_STO_BlobFree  CAL_CMEXPAPI( "STO_BlobFree" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_BlobFree  PFSTO_BLOBFREE pfSTO_BlobFree;
	#define EXT_STO_BlobFree  extern PFSTO_BLOBFREE pfSTO_BlobFree;
	#define GET_STO_BlobFree(fl)  s_pfCMGetAPI2( "STO_BlobFree", (RTS_VOID_FCTPTR *)&pfSTO_BlobFree, (fl), 0, 0)
	#define CAL_STO_BlobFree  pfSTO_BlobFree
	#define CHK_STO_BlobFree  (pfSTO_BlobFree != NULL)
	#define EXP_STO_BlobFree  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_BlobFree", (RTS_UINTPTR)STO_BlobFree, 0, 0) 
#endif



STO_ERROR CDECL STO_DataCopyToBlob(CAA_BYTE* pData, CAA_SIZE szData, STO_BLOB* pBlob);
typedef STO_ERROR (CDECL * PFSTO_DATACOPYTOBLOB) (CAA_BYTE* pData, CAA_SIZE szData, STO_BLOB* pBlob);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_DATACOPYTOBLOB_NOTIMPLEMENTED)
	#define USE_STO_DataCopyToBlob
	#define EXT_STO_DataCopyToBlob
	#define GET_STO_DataCopyToBlob(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_DataCopyToBlob(p0,p1,p2)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_DataCopyToBlob  FALSE
	#define EXP_STO_DataCopyToBlob  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_DataCopyToBlob
	#define EXT_STO_DataCopyToBlob
	#define GET_STO_DataCopyToBlob(fl)  CAL_CMGETAPI( "STO_DataCopyToBlob" ) 
	#define CAL_STO_DataCopyToBlob  STO_DataCopyToBlob
	#define CHK_STO_DataCopyToBlob  TRUE
	#define EXP_STO_DataCopyToBlob  CAL_CMEXPAPI( "STO_DataCopyToBlob" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_DataCopyToBlob
	#define EXT_STO_DataCopyToBlob
	#define GET_STO_DataCopyToBlob(fl)  CAL_CMGETAPI( "STO_DataCopyToBlob" ) 
	#define CAL_STO_DataCopyToBlob  STO_DataCopyToBlob
	#define CHK_STO_DataCopyToBlob  TRUE
	#define EXP_STO_DataCopyToBlob  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_DataCopyToBlob", (RTS_UINTPTR)STO_DataCopyToBlob, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_DataCopyToBlob
	#define EXT_CmpCAAStorageSTO_DataCopyToBlob
	#define GET_CmpCAAStorageSTO_DataCopyToBlob  ERR_OK
	#define CAL_CmpCAAStorageSTO_DataCopyToBlob pICmpCAAStorage->ISTO_DataCopyToBlob
	#define CHK_CmpCAAStorageSTO_DataCopyToBlob (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_DataCopyToBlob  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_DataCopyToBlob
	#define EXT_STO_DataCopyToBlob
	#define GET_STO_DataCopyToBlob(fl)  CAL_CMGETAPI( "STO_DataCopyToBlob" ) 
	#define CAL_STO_DataCopyToBlob pICmpCAAStorage->ISTO_DataCopyToBlob
	#define CHK_STO_DataCopyToBlob (pICmpCAAStorage != NULL)
	#define EXP_STO_DataCopyToBlob  CAL_CMEXPAPI( "STO_DataCopyToBlob" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_DataCopyToBlob  PFSTO_DATACOPYTOBLOB pfSTO_DataCopyToBlob;
	#define EXT_STO_DataCopyToBlob  extern PFSTO_DATACOPYTOBLOB pfSTO_DataCopyToBlob;
	#define GET_STO_DataCopyToBlob(fl)  s_pfCMGetAPI2( "STO_DataCopyToBlob", (RTS_VOID_FCTPTR *)&pfSTO_DataCopyToBlob, (fl), 0, 0)
	#define CAL_STO_DataCopyToBlob  pfSTO_DataCopyToBlob
	#define CHK_STO_DataCopyToBlob  (pfSTO_DataCopyToBlob != NULL)
	#define EXP_STO_DataCopyToBlob  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_DataCopyToBlob", (RTS_UINTPTR)STO_DataCopyToBlob, 0, 0) 
#endif




STO_ERROR CDECL STO_INT64_TO_LOCALTIME(STO_INT64 i64UTCValue, STO_INT64 *pi64LocalValue);
typedef STO_ERROR (CDECL * PFSTO_INT64_TO_LOCALTIME) (STO_INT64 i64UTCValue, STO_INT64 *pi64LocalValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_INT64_TO_LOCALTIME_NOTIMPLEMENTED)
	#define USE_STO_INT64_TO_LOCALTIME
	#define EXT_STO_INT64_TO_LOCALTIME
	#define GET_STO_INT64_TO_LOCALTIME(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_INT64_TO_LOCALTIME(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_INT64_TO_LOCALTIME  FALSE
	#define EXP_STO_INT64_TO_LOCALTIME  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_INT64_TO_LOCALTIME
	#define EXT_STO_INT64_TO_LOCALTIME
	#define GET_STO_INT64_TO_LOCALTIME(fl)  CAL_CMGETAPI( "STO_INT64_TO_LOCALTIME" ) 
	#define CAL_STO_INT64_TO_LOCALTIME  STO_INT64_TO_LOCALTIME
	#define CHK_STO_INT64_TO_LOCALTIME  TRUE
	#define EXP_STO_INT64_TO_LOCALTIME  CAL_CMEXPAPI( "STO_INT64_TO_LOCALTIME" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_INT64_TO_LOCALTIME
	#define EXT_STO_INT64_TO_LOCALTIME
	#define GET_STO_INT64_TO_LOCALTIME(fl)  CAL_CMGETAPI( "STO_INT64_TO_LOCALTIME" ) 
	#define CAL_STO_INT64_TO_LOCALTIME  STO_INT64_TO_LOCALTIME
	#define CHK_STO_INT64_TO_LOCALTIME  TRUE
	#define EXP_STO_INT64_TO_LOCALTIME  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_INT64_TO_LOCALTIME", (RTS_UINTPTR)STO_INT64_TO_LOCALTIME, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_INT64_TO_LOCALTIME
	#define EXT_CmpCAAStorageSTO_INT64_TO_LOCALTIME
	#define GET_CmpCAAStorageSTO_INT64_TO_LOCALTIME  ERR_OK
	#define CAL_CmpCAAStorageSTO_INT64_TO_LOCALTIME pICmpCAAStorage->ISTO_INT64_TO_LOCALTIME
	#define CHK_CmpCAAStorageSTO_INT64_TO_LOCALTIME (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_INT64_TO_LOCALTIME  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_INT64_TO_LOCALTIME
	#define EXT_STO_INT64_TO_LOCALTIME
	#define GET_STO_INT64_TO_LOCALTIME(fl)  CAL_CMGETAPI( "STO_INT64_TO_LOCALTIME" ) 
	#define CAL_STO_INT64_TO_LOCALTIME pICmpCAAStorage->ISTO_INT64_TO_LOCALTIME
	#define CHK_STO_INT64_TO_LOCALTIME (pICmpCAAStorage != NULL)
	#define EXP_STO_INT64_TO_LOCALTIME  CAL_CMEXPAPI( "STO_INT64_TO_LOCALTIME" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_INT64_TO_LOCALTIME  PFSTO_INT64_TO_LOCALTIME pfSTO_INT64_TO_LOCALTIME;
	#define EXT_STO_INT64_TO_LOCALTIME  extern PFSTO_INT64_TO_LOCALTIME pfSTO_INT64_TO_LOCALTIME;
	#define GET_STO_INT64_TO_LOCALTIME(fl)  s_pfCMGetAPI2( "STO_INT64_TO_LOCALTIME", (RTS_VOID_FCTPTR *)&pfSTO_INT64_TO_LOCALTIME, (fl), 0, 0)
	#define CAL_STO_INT64_TO_LOCALTIME  pfSTO_INT64_TO_LOCALTIME
	#define CHK_STO_INT64_TO_LOCALTIME  (pfSTO_INT64_TO_LOCALTIME != NULL)
	#define EXP_STO_INT64_TO_LOCALTIME  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_INT64_TO_LOCALTIME", (RTS_UINTPTR)STO_INT64_TO_LOCALTIME, 0, 0) 
#endif



STO_ERROR CDECL STO_INT64_TO_UTC(STO_INT64 i64LocalValue, STO_INT64 *pi64UTCValue);
typedef STO_ERROR (CDECL * PFSTO_INT64_TO_UTC) (STO_INT64 i64LocalValue, STO_INT64 *pi64UTCValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_INT64_TO_UTC_NOTIMPLEMENTED)
	#define USE_STO_INT64_TO_UTC
	#define EXT_STO_INT64_TO_UTC
	#define GET_STO_INT64_TO_UTC(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_INT64_TO_UTC(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_INT64_TO_UTC  FALSE
	#define EXP_STO_INT64_TO_UTC  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_INT64_TO_UTC
	#define EXT_STO_INT64_TO_UTC
	#define GET_STO_INT64_TO_UTC(fl)  CAL_CMGETAPI( "STO_INT64_TO_UTC" ) 
	#define CAL_STO_INT64_TO_UTC  STO_INT64_TO_UTC
	#define CHK_STO_INT64_TO_UTC  TRUE
	#define EXP_STO_INT64_TO_UTC  CAL_CMEXPAPI( "STO_INT64_TO_UTC" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_INT64_TO_UTC
	#define EXT_STO_INT64_TO_UTC
	#define GET_STO_INT64_TO_UTC(fl)  CAL_CMGETAPI( "STO_INT64_TO_UTC" ) 
	#define CAL_STO_INT64_TO_UTC  STO_INT64_TO_UTC
	#define CHK_STO_INT64_TO_UTC  TRUE
	#define EXP_STO_INT64_TO_UTC  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_INT64_TO_UTC", (RTS_UINTPTR)STO_INT64_TO_UTC, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_INT64_TO_UTC
	#define EXT_CmpCAAStorageSTO_INT64_TO_UTC
	#define GET_CmpCAAStorageSTO_INT64_TO_UTC  ERR_OK
	#define CAL_CmpCAAStorageSTO_INT64_TO_UTC pICmpCAAStorage->ISTO_INT64_TO_UTC
	#define CHK_CmpCAAStorageSTO_INT64_TO_UTC (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_INT64_TO_UTC  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_INT64_TO_UTC
	#define EXT_STO_INT64_TO_UTC
	#define GET_STO_INT64_TO_UTC(fl)  CAL_CMGETAPI( "STO_INT64_TO_UTC" ) 
	#define CAL_STO_INT64_TO_UTC pICmpCAAStorage->ISTO_INT64_TO_UTC
	#define CHK_STO_INT64_TO_UTC (pICmpCAAStorage != NULL)
	#define EXP_STO_INT64_TO_UTC  CAL_CMEXPAPI( "STO_INT64_TO_UTC" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_INT64_TO_UTC  PFSTO_INT64_TO_UTC pfSTO_INT64_TO_UTC;
	#define EXT_STO_INT64_TO_UTC  extern PFSTO_INT64_TO_UTC pfSTO_INT64_TO_UTC;
	#define GET_STO_INT64_TO_UTC(fl)  s_pfCMGetAPI2( "STO_INT64_TO_UTC", (RTS_VOID_FCTPTR *)&pfSTO_INT64_TO_UTC, (fl), 0, 0)
	#define CAL_STO_INT64_TO_UTC  pfSTO_INT64_TO_UTC
	#define CHK_STO_INT64_TO_UTC  (pfSTO_INT64_TO_UTC != NULL)
	#define EXP_STO_INT64_TO_UTC  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_INT64_TO_UTC", (RTS_UINTPTR)STO_INT64_TO_UTC, 0, 0) 
#endif




STO_ERROR CDECL STO_DT_TO_INT64(CAA_DT dtValue, CAA_LINT *pliValue);
typedef STO_ERROR (CDECL * PFSTO_DT_TO_INT64) (CAA_DT dtValue, CAA_LINT *pliValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_DT_TO_INT64_NOTIMPLEMENTED)
	#define USE_STO_DT_TO_INT64
	#define EXT_STO_DT_TO_INT64
	#define GET_STO_DT_TO_INT64(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_DT_TO_INT64(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_DT_TO_INT64  FALSE
	#define EXP_STO_DT_TO_INT64  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_DT_TO_INT64
	#define EXT_STO_DT_TO_INT64
	#define GET_STO_DT_TO_INT64(fl)  CAL_CMGETAPI( "STO_DT_TO_INT64" ) 
	#define CAL_STO_DT_TO_INT64  STO_DT_TO_INT64
	#define CHK_STO_DT_TO_INT64  TRUE
	#define EXP_STO_DT_TO_INT64  CAL_CMEXPAPI( "STO_DT_TO_INT64" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_DT_TO_INT64
	#define EXT_STO_DT_TO_INT64
	#define GET_STO_DT_TO_INT64(fl)  CAL_CMGETAPI( "STO_DT_TO_INT64" ) 
	#define CAL_STO_DT_TO_INT64  STO_DT_TO_INT64
	#define CHK_STO_DT_TO_INT64  TRUE
	#define EXP_STO_DT_TO_INT64  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_DT_TO_INT64", (RTS_UINTPTR)STO_DT_TO_INT64, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_DT_TO_INT64
	#define EXT_CmpCAAStorageSTO_DT_TO_INT64
	#define GET_CmpCAAStorageSTO_DT_TO_INT64  ERR_OK
	#define CAL_CmpCAAStorageSTO_DT_TO_INT64 pICmpCAAStorage->ISTO_DT_TO_INT64
	#define CHK_CmpCAAStorageSTO_DT_TO_INT64 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_DT_TO_INT64  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_DT_TO_INT64
	#define EXT_STO_DT_TO_INT64
	#define GET_STO_DT_TO_INT64(fl)  CAL_CMGETAPI( "STO_DT_TO_INT64" ) 
	#define CAL_STO_DT_TO_INT64 pICmpCAAStorage->ISTO_DT_TO_INT64
	#define CHK_STO_DT_TO_INT64 (pICmpCAAStorage != NULL)
	#define EXP_STO_DT_TO_INT64  CAL_CMEXPAPI( "STO_DT_TO_INT64" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_DT_TO_INT64  PFSTO_DT_TO_INT64 pfSTO_DT_TO_INT64;
	#define EXT_STO_DT_TO_INT64  extern PFSTO_DT_TO_INT64 pfSTO_DT_TO_INT64;
	#define GET_STO_DT_TO_INT64(fl)  s_pfCMGetAPI2( "STO_DT_TO_INT64", (RTS_VOID_FCTPTR *)&pfSTO_DT_TO_INT64, (fl), 0, 0)
	#define CAL_STO_DT_TO_INT64  pfSTO_DT_TO_INT64
	#define CHK_STO_DT_TO_INT64  (pfSTO_DT_TO_INT64 != NULL)
	#define EXP_STO_DT_TO_INT64  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_DT_TO_INT64", (RTS_UINTPTR)STO_DT_TO_INT64, 0, 0) 
#endif



STO_ERROR CDECL STO_DT_TO_ISO8601(CAA_DT dtValue, STO_ISO8601 *psValue);
typedef STO_ERROR (CDECL * PFSTO_DT_TO_ISO8601) (CAA_DT dtValue, STO_ISO8601 *psValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_DT_TO_ISO8601_NOTIMPLEMENTED)
	#define USE_STO_DT_TO_ISO8601
	#define EXT_STO_DT_TO_ISO8601
	#define GET_STO_DT_TO_ISO8601(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_DT_TO_ISO8601(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_DT_TO_ISO8601  FALSE
	#define EXP_STO_DT_TO_ISO8601  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_DT_TO_ISO8601
	#define EXT_STO_DT_TO_ISO8601
	#define GET_STO_DT_TO_ISO8601(fl)  CAL_CMGETAPI( "STO_DT_TO_ISO8601" ) 
	#define CAL_STO_DT_TO_ISO8601  STO_DT_TO_ISO8601
	#define CHK_STO_DT_TO_ISO8601  TRUE
	#define EXP_STO_DT_TO_ISO8601  CAL_CMEXPAPI( "STO_DT_TO_ISO8601" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_DT_TO_ISO8601
	#define EXT_STO_DT_TO_ISO8601
	#define GET_STO_DT_TO_ISO8601(fl)  CAL_CMGETAPI( "STO_DT_TO_ISO8601" ) 
	#define CAL_STO_DT_TO_ISO8601  STO_DT_TO_ISO8601
	#define CHK_STO_DT_TO_ISO8601  TRUE
	#define EXP_STO_DT_TO_ISO8601  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_DT_TO_ISO8601", (RTS_UINTPTR)STO_DT_TO_ISO8601, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_DT_TO_ISO8601
	#define EXT_CmpCAAStorageSTO_DT_TO_ISO8601
	#define GET_CmpCAAStorageSTO_DT_TO_ISO8601  ERR_OK
	#define CAL_CmpCAAStorageSTO_DT_TO_ISO8601 pICmpCAAStorage->ISTO_DT_TO_ISO8601
	#define CHK_CmpCAAStorageSTO_DT_TO_ISO8601 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_DT_TO_ISO8601  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_DT_TO_ISO8601
	#define EXT_STO_DT_TO_ISO8601
	#define GET_STO_DT_TO_ISO8601(fl)  CAL_CMGETAPI( "STO_DT_TO_ISO8601" ) 
	#define CAL_STO_DT_TO_ISO8601 pICmpCAAStorage->ISTO_DT_TO_ISO8601
	#define CHK_STO_DT_TO_ISO8601 (pICmpCAAStorage != NULL)
	#define EXP_STO_DT_TO_ISO8601  CAL_CMEXPAPI( "STO_DT_TO_ISO8601" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_DT_TO_ISO8601  PFSTO_DT_TO_ISO8601 pfSTO_DT_TO_ISO8601;
	#define EXT_STO_DT_TO_ISO8601  extern PFSTO_DT_TO_ISO8601 pfSTO_DT_TO_ISO8601;
	#define GET_STO_DT_TO_ISO8601(fl)  s_pfCMGetAPI2( "STO_DT_TO_ISO8601", (RTS_VOID_FCTPTR *)&pfSTO_DT_TO_ISO8601, (fl), 0, 0)
	#define CAL_STO_DT_TO_ISO8601  pfSTO_DT_TO_ISO8601
	#define CHK_STO_DT_TO_ISO8601  (pfSTO_DT_TO_ISO8601 != NULL)
	#define EXP_STO_DT_TO_ISO8601  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_DT_TO_ISO8601", (RTS_UINTPTR)STO_DT_TO_ISO8601, 0, 0) 
#endif



STO_ERROR CDECL STO_DT_TO_REAL8(CAA_DT dtValue, CAA_LREAL *plrValue);
typedef STO_ERROR (CDECL * PFSTO_DT_TO_REAL8) (CAA_DT dtValue, CAA_LREAL *plrValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_DT_TO_REAL8_NOTIMPLEMENTED)
	#define USE_STO_DT_TO_REAL8
	#define EXT_STO_DT_TO_REAL8
	#define GET_STO_DT_TO_REAL8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_DT_TO_REAL8(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_DT_TO_REAL8  FALSE
	#define EXP_STO_DT_TO_REAL8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_DT_TO_REAL8
	#define EXT_STO_DT_TO_REAL8
	#define GET_STO_DT_TO_REAL8(fl)  CAL_CMGETAPI( "STO_DT_TO_REAL8" ) 
	#define CAL_STO_DT_TO_REAL8  STO_DT_TO_REAL8
	#define CHK_STO_DT_TO_REAL8  TRUE
	#define EXP_STO_DT_TO_REAL8  CAL_CMEXPAPI( "STO_DT_TO_REAL8" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_DT_TO_REAL8
	#define EXT_STO_DT_TO_REAL8
	#define GET_STO_DT_TO_REAL8(fl)  CAL_CMGETAPI( "STO_DT_TO_REAL8" ) 
	#define CAL_STO_DT_TO_REAL8  STO_DT_TO_REAL8
	#define CHK_STO_DT_TO_REAL8  TRUE
	#define EXP_STO_DT_TO_REAL8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_DT_TO_REAL8", (RTS_UINTPTR)STO_DT_TO_REAL8, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_DT_TO_REAL8
	#define EXT_CmpCAAStorageSTO_DT_TO_REAL8
	#define GET_CmpCAAStorageSTO_DT_TO_REAL8  ERR_OK
	#define CAL_CmpCAAStorageSTO_DT_TO_REAL8 pICmpCAAStorage->ISTO_DT_TO_REAL8
	#define CHK_CmpCAAStorageSTO_DT_TO_REAL8 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_DT_TO_REAL8  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_DT_TO_REAL8
	#define EXT_STO_DT_TO_REAL8
	#define GET_STO_DT_TO_REAL8(fl)  CAL_CMGETAPI( "STO_DT_TO_REAL8" ) 
	#define CAL_STO_DT_TO_REAL8 pICmpCAAStorage->ISTO_DT_TO_REAL8
	#define CHK_STO_DT_TO_REAL8 (pICmpCAAStorage != NULL)
	#define EXP_STO_DT_TO_REAL8  CAL_CMEXPAPI( "STO_DT_TO_REAL8" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_DT_TO_REAL8  PFSTO_DT_TO_REAL8 pfSTO_DT_TO_REAL8;
	#define EXT_STO_DT_TO_REAL8  extern PFSTO_DT_TO_REAL8 pfSTO_DT_TO_REAL8;
	#define GET_STO_DT_TO_REAL8(fl)  s_pfCMGetAPI2( "STO_DT_TO_REAL8", (RTS_VOID_FCTPTR *)&pfSTO_DT_TO_REAL8, (fl), 0, 0)
	#define CAL_STO_DT_TO_REAL8  pfSTO_DT_TO_REAL8
	#define CHK_STO_DT_TO_REAL8  (pfSTO_DT_TO_REAL8 != NULL)
	#define EXP_STO_DT_TO_REAL8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_DT_TO_REAL8", (RTS_UINTPTR)STO_DT_TO_REAL8, 0, 0) 
#endif



STO_ERROR CDECL STO_INT64_TO_DT(CAA_LINT liValue, CAA_DT *pdtValue);
typedef STO_ERROR (CDECL * PFSTO_INT64_TO_DT) (CAA_LINT liValue, CAA_DT *pdtValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_INT64_TO_DT_NOTIMPLEMENTED)
	#define USE_STO_INT64_TO_DT
	#define EXT_STO_INT64_TO_DT
	#define GET_STO_INT64_TO_DT(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_INT64_TO_DT(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_INT64_TO_DT  FALSE
	#define EXP_STO_INT64_TO_DT  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_INT64_TO_DT
	#define EXT_STO_INT64_TO_DT
	#define GET_STO_INT64_TO_DT(fl)  CAL_CMGETAPI( "STO_INT64_TO_DT" ) 
	#define CAL_STO_INT64_TO_DT  STO_INT64_TO_DT
	#define CHK_STO_INT64_TO_DT  TRUE
	#define EXP_STO_INT64_TO_DT  CAL_CMEXPAPI( "STO_INT64_TO_DT" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_INT64_TO_DT
	#define EXT_STO_INT64_TO_DT
	#define GET_STO_INT64_TO_DT(fl)  CAL_CMGETAPI( "STO_INT64_TO_DT" ) 
	#define CAL_STO_INT64_TO_DT  STO_INT64_TO_DT
	#define CHK_STO_INT64_TO_DT  TRUE
	#define EXP_STO_INT64_TO_DT  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_INT64_TO_DT", (RTS_UINTPTR)STO_INT64_TO_DT, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_INT64_TO_DT
	#define EXT_CmpCAAStorageSTO_INT64_TO_DT
	#define GET_CmpCAAStorageSTO_INT64_TO_DT  ERR_OK
	#define CAL_CmpCAAStorageSTO_INT64_TO_DT pICmpCAAStorage->ISTO_INT64_TO_DT
	#define CHK_CmpCAAStorageSTO_INT64_TO_DT (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_INT64_TO_DT  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_INT64_TO_DT
	#define EXT_STO_INT64_TO_DT
	#define GET_STO_INT64_TO_DT(fl)  CAL_CMGETAPI( "STO_INT64_TO_DT" ) 
	#define CAL_STO_INT64_TO_DT pICmpCAAStorage->ISTO_INT64_TO_DT
	#define CHK_STO_INT64_TO_DT (pICmpCAAStorage != NULL)
	#define EXP_STO_INT64_TO_DT  CAL_CMEXPAPI( "STO_INT64_TO_DT" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_INT64_TO_DT  PFSTO_INT64_TO_DT pfSTO_INT64_TO_DT;
	#define EXT_STO_INT64_TO_DT  extern PFSTO_INT64_TO_DT pfSTO_INT64_TO_DT;
	#define GET_STO_INT64_TO_DT(fl)  s_pfCMGetAPI2( "STO_INT64_TO_DT", (RTS_VOID_FCTPTR *)&pfSTO_INT64_TO_DT, (fl), 0, 0)
	#define CAL_STO_INT64_TO_DT  pfSTO_INT64_TO_DT
	#define CHK_STO_INT64_TO_DT  (pfSTO_INT64_TO_DT != NULL)
	#define EXP_STO_INT64_TO_DT  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_INT64_TO_DT", (RTS_UINTPTR)STO_INT64_TO_DT, 0, 0) 
#endif



STO_ERROR CDECL STO_INT64_TO_ISO8601(CAA_LINT liValue, STO_ISO8601 *psValue);
typedef STO_ERROR (CDECL * PFSTO_INT64_TO_ISO8601) (CAA_LINT liValue, STO_ISO8601 *psValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_INT64_TO_ISO8601_NOTIMPLEMENTED)
	#define USE_STO_INT64_TO_ISO8601
	#define EXT_STO_INT64_TO_ISO8601
	#define GET_STO_INT64_TO_ISO8601(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_INT64_TO_ISO8601(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_INT64_TO_ISO8601  FALSE
	#define EXP_STO_INT64_TO_ISO8601  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_INT64_TO_ISO8601
	#define EXT_STO_INT64_TO_ISO8601
	#define GET_STO_INT64_TO_ISO8601(fl)  CAL_CMGETAPI( "STO_INT64_TO_ISO8601" ) 
	#define CAL_STO_INT64_TO_ISO8601  STO_INT64_TO_ISO8601
	#define CHK_STO_INT64_TO_ISO8601  TRUE
	#define EXP_STO_INT64_TO_ISO8601  CAL_CMEXPAPI( "STO_INT64_TO_ISO8601" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_INT64_TO_ISO8601
	#define EXT_STO_INT64_TO_ISO8601
	#define GET_STO_INT64_TO_ISO8601(fl)  CAL_CMGETAPI( "STO_INT64_TO_ISO8601" ) 
	#define CAL_STO_INT64_TO_ISO8601  STO_INT64_TO_ISO8601
	#define CHK_STO_INT64_TO_ISO8601  TRUE
	#define EXP_STO_INT64_TO_ISO8601  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_INT64_TO_ISO8601", (RTS_UINTPTR)STO_INT64_TO_ISO8601, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_INT64_TO_ISO8601
	#define EXT_CmpCAAStorageSTO_INT64_TO_ISO8601
	#define GET_CmpCAAStorageSTO_INT64_TO_ISO8601  ERR_OK
	#define CAL_CmpCAAStorageSTO_INT64_TO_ISO8601 pICmpCAAStorage->ISTO_INT64_TO_ISO8601
	#define CHK_CmpCAAStorageSTO_INT64_TO_ISO8601 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_INT64_TO_ISO8601  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_INT64_TO_ISO8601
	#define EXT_STO_INT64_TO_ISO8601
	#define GET_STO_INT64_TO_ISO8601(fl)  CAL_CMGETAPI( "STO_INT64_TO_ISO8601" ) 
	#define CAL_STO_INT64_TO_ISO8601 pICmpCAAStorage->ISTO_INT64_TO_ISO8601
	#define CHK_STO_INT64_TO_ISO8601 (pICmpCAAStorage != NULL)
	#define EXP_STO_INT64_TO_ISO8601  CAL_CMEXPAPI( "STO_INT64_TO_ISO8601" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_INT64_TO_ISO8601  PFSTO_INT64_TO_ISO8601 pfSTO_INT64_TO_ISO8601;
	#define EXT_STO_INT64_TO_ISO8601  extern PFSTO_INT64_TO_ISO8601 pfSTO_INT64_TO_ISO8601;
	#define GET_STO_INT64_TO_ISO8601(fl)  s_pfCMGetAPI2( "STO_INT64_TO_ISO8601", (RTS_VOID_FCTPTR *)&pfSTO_INT64_TO_ISO8601, (fl), 0, 0)
	#define CAL_STO_INT64_TO_ISO8601  pfSTO_INT64_TO_ISO8601
	#define CHK_STO_INT64_TO_ISO8601  (pfSTO_INT64_TO_ISO8601 != NULL)
	#define EXP_STO_INT64_TO_ISO8601  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_INT64_TO_ISO8601", (RTS_UINTPTR)STO_INT64_TO_ISO8601, 0, 0) 
#endif



STO_ERROR CDECL STO_INT64_TO_LTIME(CAA_LINT liValue, CAA_LTIME *pltValue);
typedef STO_ERROR (CDECL * PFSTO_INT64_TO_LTIME) (CAA_LINT liValue, CAA_LTIME *pltValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_INT64_TO_LTIME_NOTIMPLEMENTED)
	#define USE_STO_INT64_TO_LTIME
	#define EXT_STO_INT64_TO_LTIME
	#define GET_STO_INT64_TO_LTIME(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_INT64_TO_LTIME(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_INT64_TO_LTIME  FALSE
	#define EXP_STO_INT64_TO_LTIME  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_INT64_TO_LTIME
	#define EXT_STO_INT64_TO_LTIME
	#define GET_STO_INT64_TO_LTIME(fl)  CAL_CMGETAPI( "STO_INT64_TO_LTIME" ) 
	#define CAL_STO_INT64_TO_LTIME  STO_INT64_TO_LTIME
	#define CHK_STO_INT64_TO_LTIME  TRUE
	#define EXP_STO_INT64_TO_LTIME  CAL_CMEXPAPI( "STO_INT64_TO_LTIME" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_INT64_TO_LTIME
	#define EXT_STO_INT64_TO_LTIME
	#define GET_STO_INT64_TO_LTIME(fl)  CAL_CMGETAPI( "STO_INT64_TO_LTIME" ) 
	#define CAL_STO_INT64_TO_LTIME  STO_INT64_TO_LTIME
	#define CHK_STO_INT64_TO_LTIME  TRUE
	#define EXP_STO_INT64_TO_LTIME  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_INT64_TO_LTIME", (RTS_UINTPTR)STO_INT64_TO_LTIME, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_INT64_TO_LTIME
	#define EXT_CmpCAAStorageSTO_INT64_TO_LTIME
	#define GET_CmpCAAStorageSTO_INT64_TO_LTIME  ERR_OK
	#define CAL_CmpCAAStorageSTO_INT64_TO_LTIME pICmpCAAStorage->ISTO_INT64_TO_LTIME
	#define CHK_CmpCAAStorageSTO_INT64_TO_LTIME (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_INT64_TO_LTIME  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_INT64_TO_LTIME
	#define EXT_STO_INT64_TO_LTIME
	#define GET_STO_INT64_TO_LTIME(fl)  CAL_CMGETAPI( "STO_INT64_TO_LTIME" ) 
	#define CAL_STO_INT64_TO_LTIME pICmpCAAStorage->ISTO_INT64_TO_LTIME
	#define CHK_STO_INT64_TO_LTIME (pICmpCAAStorage != NULL)
	#define EXP_STO_INT64_TO_LTIME  CAL_CMEXPAPI( "STO_INT64_TO_LTIME" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_INT64_TO_LTIME  PFSTO_INT64_TO_LTIME pfSTO_INT64_TO_LTIME;
	#define EXT_STO_INT64_TO_LTIME  extern PFSTO_INT64_TO_LTIME pfSTO_INT64_TO_LTIME;
	#define GET_STO_INT64_TO_LTIME(fl)  s_pfCMGetAPI2( "STO_INT64_TO_LTIME", (RTS_VOID_FCTPTR *)&pfSTO_INT64_TO_LTIME, (fl), 0, 0)
	#define CAL_STO_INT64_TO_LTIME  pfSTO_INT64_TO_LTIME
	#define CHK_STO_INT64_TO_LTIME  (pfSTO_INT64_TO_LTIME != NULL)
	#define EXP_STO_INT64_TO_LTIME  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_INT64_TO_LTIME", (RTS_UINTPTR)STO_INT64_TO_LTIME, 0, 0) 
#endif



STO_ERROR CDECL STO_INT64_TO_REAL8(CAA_LINT liValue, CAA_LREAL *plrValue);
typedef STO_ERROR (CDECL * PFSTO_INT64_TO_REAL8) (CAA_LINT liValue, CAA_LREAL *plrValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_INT64_TO_REAL8_NOTIMPLEMENTED)
	#define USE_STO_INT64_TO_REAL8
	#define EXT_STO_INT64_TO_REAL8
	#define GET_STO_INT64_TO_REAL8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_INT64_TO_REAL8(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_INT64_TO_REAL8  FALSE
	#define EXP_STO_INT64_TO_REAL8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_INT64_TO_REAL8
	#define EXT_STO_INT64_TO_REAL8
	#define GET_STO_INT64_TO_REAL8(fl)  CAL_CMGETAPI( "STO_INT64_TO_REAL8" ) 
	#define CAL_STO_INT64_TO_REAL8  STO_INT64_TO_REAL8
	#define CHK_STO_INT64_TO_REAL8  TRUE
	#define EXP_STO_INT64_TO_REAL8  CAL_CMEXPAPI( "STO_INT64_TO_REAL8" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_INT64_TO_REAL8
	#define EXT_STO_INT64_TO_REAL8
	#define GET_STO_INT64_TO_REAL8(fl)  CAL_CMGETAPI( "STO_INT64_TO_REAL8" ) 
	#define CAL_STO_INT64_TO_REAL8  STO_INT64_TO_REAL8
	#define CHK_STO_INT64_TO_REAL8  TRUE
	#define EXP_STO_INT64_TO_REAL8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_INT64_TO_REAL8", (RTS_UINTPTR)STO_INT64_TO_REAL8, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_INT64_TO_REAL8
	#define EXT_CmpCAAStorageSTO_INT64_TO_REAL8
	#define GET_CmpCAAStorageSTO_INT64_TO_REAL8  ERR_OK
	#define CAL_CmpCAAStorageSTO_INT64_TO_REAL8 pICmpCAAStorage->ISTO_INT64_TO_REAL8
	#define CHK_CmpCAAStorageSTO_INT64_TO_REAL8 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_INT64_TO_REAL8  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_INT64_TO_REAL8
	#define EXT_STO_INT64_TO_REAL8
	#define GET_STO_INT64_TO_REAL8(fl)  CAL_CMGETAPI( "STO_INT64_TO_REAL8" ) 
	#define CAL_STO_INT64_TO_REAL8 pICmpCAAStorage->ISTO_INT64_TO_REAL8
	#define CHK_STO_INT64_TO_REAL8 (pICmpCAAStorage != NULL)
	#define EXP_STO_INT64_TO_REAL8  CAL_CMEXPAPI( "STO_INT64_TO_REAL8" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_INT64_TO_REAL8  PFSTO_INT64_TO_REAL8 pfSTO_INT64_TO_REAL8;
	#define EXT_STO_INT64_TO_REAL8  extern PFSTO_INT64_TO_REAL8 pfSTO_INT64_TO_REAL8;
	#define GET_STO_INT64_TO_REAL8(fl)  s_pfCMGetAPI2( "STO_INT64_TO_REAL8", (RTS_VOID_FCTPTR *)&pfSTO_INT64_TO_REAL8, (fl), 0, 0)
	#define CAL_STO_INT64_TO_REAL8  pfSTO_INT64_TO_REAL8
	#define CHK_STO_INT64_TO_REAL8  (pfSTO_INT64_TO_REAL8 != NULL)
	#define EXP_STO_INT64_TO_REAL8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_INT64_TO_REAL8", (RTS_UINTPTR)STO_INT64_TO_REAL8, 0, 0) 
#endif



STO_ERROR CDECL STO_INT64_TO_TIME(CAA_LINT liValue, CAA_TIME *ptValue);
typedef STO_ERROR (CDECL * PFSTO_INT64_TO_TIME) (CAA_LINT liValue, CAA_TIME *ptValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_INT64_TO_TIME_NOTIMPLEMENTED)
	#define USE_STO_INT64_TO_TIME
	#define EXT_STO_INT64_TO_TIME
	#define GET_STO_INT64_TO_TIME(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_INT64_TO_TIME(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_INT64_TO_TIME  FALSE
	#define EXP_STO_INT64_TO_TIME  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_INT64_TO_TIME
	#define EXT_STO_INT64_TO_TIME
	#define GET_STO_INT64_TO_TIME(fl)  CAL_CMGETAPI( "STO_INT64_TO_TIME" ) 
	#define CAL_STO_INT64_TO_TIME  STO_INT64_TO_TIME
	#define CHK_STO_INT64_TO_TIME  TRUE
	#define EXP_STO_INT64_TO_TIME  CAL_CMEXPAPI( "STO_INT64_TO_TIME" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_INT64_TO_TIME
	#define EXT_STO_INT64_TO_TIME
	#define GET_STO_INT64_TO_TIME(fl)  CAL_CMGETAPI( "STO_INT64_TO_TIME" ) 
	#define CAL_STO_INT64_TO_TIME  STO_INT64_TO_TIME
	#define CHK_STO_INT64_TO_TIME  TRUE
	#define EXP_STO_INT64_TO_TIME  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_INT64_TO_TIME", (RTS_UINTPTR)STO_INT64_TO_TIME, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_INT64_TO_TIME
	#define EXT_CmpCAAStorageSTO_INT64_TO_TIME
	#define GET_CmpCAAStorageSTO_INT64_TO_TIME  ERR_OK
	#define CAL_CmpCAAStorageSTO_INT64_TO_TIME pICmpCAAStorage->ISTO_INT64_TO_TIME
	#define CHK_CmpCAAStorageSTO_INT64_TO_TIME (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_INT64_TO_TIME  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_INT64_TO_TIME
	#define EXT_STO_INT64_TO_TIME
	#define GET_STO_INT64_TO_TIME(fl)  CAL_CMGETAPI( "STO_INT64_TO_TIME" ) 
	#define CAL_STO_INT64_TO_TIME pICmpCAAStorage->ISTO_INT64_TO_TIME
	#define CHK_STO_INT64_TO_TIME (pICmpCAAStorage != NULL)
	#define EXP_STO_INT64_TO_TIME  CAL_CMEXPAPI( "STO_INT64_TO_TIME" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_INT64_TO_TIME  PFSTO_INT64_TO_TIME pfSTO_INT64_TO_TIME;
	#define EXT_STO_INT64_TO_TIME  extern PFSTO_INT64_TO_TIME pfSTO_INT64_TO_TIME;
	#define GET_STO_INT64_TO_TIME(fl)  s_pfCMGetAPI2( "STO_INT64_TO_TIME", (RTS_VOID_FCTPTR *)&pfSTO_INT64_TO_TIME, (fl), 0, 0)
	#define CAL_STO_INT64_TO_TIME  pfSTO_INT64_TO_TIME
	#define CHK_STO_INT64_TO_TIME  (pfSTO_INT64_TO_TIME != NULL)
	#define EXP_STO_INT64_TO_TIME  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_INT64_TO_TIME", (RTS_UINTPTR)STO_INT64_TO_TIME, 0, 0) 
#endif



STO_ERROR CDECL STO_ISO8601_TO_DT(STO_ISO8601 *psValue, CAA_DT *pdtValue);
typedef STO_ERROR (CDECL * PFSTO_ISO8601_TO_DT) (STO_ISO8601 *psValue, CAA_DT *pdtValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_ISO8601_TO_DT_NOTIMPLEMENTED)
	#define USE_STO_ISO8601_TO_DT
	#define EXT_STO_ISO8601_TO_DT
	#define GET_STO_ISO8601_TO_DT(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_ISO8601_TO_DT(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_ISO8601_TO_DT  FALSE
	#define EXP_STO_ISO8601_TO_DT  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_ISO8601_TO_DT
	#define EXT_STO_ISO8601_TO_DT
	#define GET_STO_ISO8601_TO_DT(fl)  CAL_CMGETAPI( "STO_ISO8601_TO_DT" ) 
	#define CAL_STO_ISO8601_TO_DT  STO_ISO8601_TO_DT
	#define CHK_STO_ISO8601_TO_DT  TRUE
	#define EXP_STO_ISO8601_TO_DT  CAL_CMEXPAPI( "STO_ISO8601_TO_DT" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_ISO8601_TO_DT
	#define EXT_STO_ISO8601_TO_DT
	#define GET_STO_ISO8601_TO_DT(fl)  CAL_CMGETAPI( "STO_ISO8601_TO_DT" ) 
	#define CAL_STO_ISO8601_TO_DT  STO_ISO8601_TO_DT
	#define CHK_STO_ISO8601_TO_DT  TRUE
	#define EXP_STO_ISO8601_TO_DT  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_ISO8601_TO_DT", (RTS_UINTPTR)STO_ISO8601_TO_DT, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_ISO8601_TO_DT
	#define EXT_CmpCAAStorageSTO_ISO8601_TO_DT
	#define GET_CmpCAAStorageSTO_ISO8601_TO_DT  ERR_OK
	#define CAL_CmpCAAStorageSTO_ISO8601_TO_DT pICmpCAAStorage->ISTO_ISO8601_TO_DT
	#define CHK_CmpCAAStorageSTO_ISO8601_TO_DT (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_ISO8601_TO_DT  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_ISO8601_TO_DT
	#define EXT_STO_ISO8601_TO_DT
	#define GET_STO_ISO8601_TO_DT(fl)  CAL_CMGETAPI( "STO_ISO8601_TO_DT" ) 
	#define CAL_STO_ISO8601_TO_DT pICmpCAAStorage->ISTO_ISO8601_TO_DT
	#define CHK_STO_ISO8601_TO_DT (pICmpCAAStorage != NULL)
	#define EXP_STO_ISO8601_TO_DT  CAL_CMEXPAPI( "STO_ISO8601_TO_DT" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_ISO8601_TO_DT  PFSTO_ISO8601_TO_DT pfSTO_ISO8601_TO_DT;
	#define EXT_STO_ISO8601_TO_DT  extern PFSTO_ISO8601_TO_DT pfSTO_ISO8601_TO_DT;
	#define GET_STO_ISO8601_TO_DT(fl)  s_pfCMGetAPI2( "STO_ISO8601_TO_DT", (RTS_VOID_FCTPTR *)&pfSTO_ISO8601_TO_DT, (fl), 0, 0)
	#define CAL_STO_ISO8601_TO_DT  pfSTO_ISO8601_TO_DT
	#define CHK_STO_ISO8601_TO_DT  (pfSTO_ISO8601_TO_DT != NULL)
	#define EXP_STO_ISO8601_TO_DT  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_ISO8601_TO_DT", (RTS_UINTPTR)STO_ISO8601_TO_DT, 0, 0) 
#endif



STO_ERROR CDECL STO_ISO8601_TO_LTIME(STO_ISO8601 *psValue, CAA_LTIME *pltValue);
typedef STO_ERROR (CDECL * PFSTO_ISO8601_TO_LTIME) (STO_ISO8601 *psValue, CAA_LTIME *pltValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_ISO8601_TO_LTIME_NOTIMPLEMENTED)
	#define USE_STO_ISO8601_TO_LTIME
	#define EXT_STO_ISO8601_TO_LTIME
	#define GET_STO_ISO8601_TO_LTIME(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_ISO8601_TO_LTIME(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_ISO8601_TO_LTIME  FALSE
	#define EXP_STO_ISO8601_TO_LTIME  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_ISO8601_TO_LTIME
	#define EXT_STO_ISO8601_TO_LTIME
	#define GET_STO_ISO8601_TO_LTIME(fl)  CAL_CMGETAPI( "STO_ISO8601_TO_LTIME" ) 
	#define CAL_STO_ISO8601_TO_LTIME  STO_ISO8601_TO_LTIME
	#define CHK_STO_ISO8601_TO_LTIME  TRUE
	#define EXP_STO_ISO8601_TO_LTIME  CAL_CMEXPAPI( "STO_ISO8601_TO_LTIME" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_ISO8601_TO_LTIME
	#define EXT_STO_ISO8601_TO_LTIME
	#define GET_STO_ISO8601_TO_LTIME(fl)  CAL_CMGETAPI( "STO_ISO8601_TO_LTIME" ) 
	#define CAL_STO_ISO8601_TO_LTIME  STO_ISO8601_TO_LTIME
	#define CHK_STO_ISO8601_TO_LTIME  TRUE
	#define EXP_STO_ISO8601_TO_LTIME  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_ISO8601_TO_LTIME", (RTS_UINTPTR)STO_ISO8601_TO_LTIME, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_ISO8601_TO_LTIME
	#define EXT_CmpCAAStorageSTO_ISO8601_TO_LTIME
	#define GET_CmpCAAStorageSTO_ISO8601_TO_LTIME  ERR_OK
	#define CAL_CmpCAAStorageSTO_ISO8601_TO_LTIME pICmpCAAStorage->ISTO_ISO8601_TO_LTIME
	#define CHK_CmpCAAStorageSTO_ISO8601_TO_LTIME (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_ISO8601_TO_LTIME  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_ISO8601_TO_LTIME
	#define EXT_STO_ISO8601_TO_LTIME
	#define GET_STO_ISO8601_TO_LTIME(fl)  CAL_CMGETAPI( "STO_ISO8601_TO_LTIME" ) 
	#define CAL_STO_ISO8601_TO_LTIME pICmpCAAStorage->ISTO_ISO8601_TO_LTIME
	#define CHK_STO_ISO8601_TO_LTIME (pICmpCAAStorage != NULL)
	#define EXP_STO_ISO8601_TO_LTIME  CAL_CMEXPAPI( "STO_ISO8601_TO_LTIME" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_ISO8601_TO_LTIME  PFSTO_ISO8601_TO_LTIME pfSTO_ISO8601_TO_LTIME;
	#define EXT_STO_ISO8601_TO_LTIME  extern PFSTO_ISO8601_TO_LTIME pfSTO_ISO8601_TO_LTIME;
	#define GET_STO_ISO8601_TO_LTIME(fl)  s_pfCMGetAPI2( "STO_ISO8601_TO_LTIME", (RTS_VOID_FCTPTR *)&pfSTO_ISO8601_TO_LTIME, (fl), 0, 0)
	#define CAL_STO_ISO8601_TO_LTIME  pfSTO_ISO8601_TO_LTIME
	#define CHK_STO_ISO8601_TO_LTIME  (pfSTO_ISO8601_TO_LTIME != NULL)
	#define EXP_STO_ISO8601_TO_LTIME  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_ISO8601_TO_LTIME", (RTS_UINTPTR)STO_ISO8601_TO_LTIME, 0, 0) 
#endif



STO_ERROR CDECL STO_ISO8601_TO_TIME(STO_ISO8601 *psValue, CAA_TIME *ptValue);
typedef STO_ERROR (CDECL * PFSTO_ISO8601_TO_TIME) (STO_ISO8601 *psValue, CAA_TIME *ptValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_ISO8601_TO_TIME_NOTIMPLEMENTED)
	#define USE_STO_ISO8601_TO_TIME
	#define EXT_STO_ISO8601_TO_TIME
	#define GET_STO_ISO8601_TO_TIME(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_ISO8601_TO_TIME(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_ISO8601_TO_TIME  FALSE
	#define EXP_STO_ISO8601_TO_TIME  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_ISO8601_TO_TIME
	#define EXT_STO_ISO8601_TO_TIME
	#define GET_STO_ISO8601_TO_TIME(fl)  CAL_CMGETAPI( "STO_ISO8601_TO_TIME" ) 
	#define CAL_STO_ISO8601_TO_TIME  STO_ISO8601_TO_TIME
	#define CHK_STO_ISO8601_TO_TIME  TRUE
	#define EXP_STO_ISO8601_TO_TIME  CAL_CMEXPAPI( "STO_ISO8601_TO_TIME" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_ISO8601_TO_TIME
	#define EXT_STO_ISO8601_TO_TIME
	#define GET_STO_ISO8601_TO_TIME(fl)  CAL_CMGETAPI( "STO_ISO8601_TO_TIME" ) 
	#define CAL_STO_ISO8601_TO_TIME  STO_ISO8601_TO_TIME
	#define CHK_STO_ISO8601_TO_TIME  TRUE
	#define EXP_STO_ISO8601_TO_TIME  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_ISO8601_TO_TIME", (RTS_UINTPTR)STO_ISO8601_TO_TIME, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_ISO8601_TO_TIME
	#define EXT_CmpCAAStorageSTO_ISO8601_TO_TIME
	#define GET_CmpCAAStorageSTO_ISO8601_TO_TIME  ERR_OK
	#define CAL_CmpCAAStorageSTO_ISO8601_TO_TIME pICmpCAAStorage->ISTO_ISO8601_TO_TIME
	#define CHK_CmpCAAStorageSTO_ISO8601_TO_TIME (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_ISO8601_TO_TIME  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_ISO8601_TO_TIME
	#define EXT_STO_ISO8601_TO_TIME
	#define GET_STO_ISO8601_TO_TIME(fl)  CAL_CMGETAPI( "STO_ISO8601_TO_TIME" ) 
	#define CAL_STO_ISO8601_TO_TIME pICmpCAAStorage->ISTO_ISO8601_TO_TIME
	#define CHK_STO_ISO8601_TO_TIME (pICmpCAAStorage != NULL)
	#define EXP_STO_ISO8601_TO_TIME  CAL_CMEXPAPI( "STO_ISO8601_TO_TIME" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_ISO8601_TO_TIME  PFSTO_ISO8601_TO_TIME pfSTO_ISO8601_TO_TIME;
	#define EXT_STO_ISO8601_TO_TIME  extern PFSTO_ISO8601_TO_TIME pfSTO_ISO8601_TO_TIME;
	#define GET_STO_ISO8601_TO_TIME(fl)  s_pfCMGetAPI2( "STO_ISO8601_TO_TIME", (RTS_VOID_FCTPTR *)&pfSTO_ISO8601_TO_TIME, (fl), 0, 0)
	#define CAL_STO_ISO8601_TO_TIME  pfSTO_ISO8601_TO_TIME
	#define CHK_STO_ISO8601_TO_TIME  (pfSTO_ISO8601_TO_TIME != NULL)
	#define EXP_STO_ISO8601_TO_TIME  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_ISO8601_TO_TIME", (RTS_UINTPTR)STO_ISO8601_TO_TIME, 0, 0) 
#endif



STO_ERROR CDECL STO_LTIME_TO_INT64(CAA_LTIME ltValue, CAA_LINT *pliValue);
typedef STO_ERROR (CDECL * PFSTO_LTIME_TO_INT64) (CAA_LTIME ltValue, CAA_LINT *pliValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_LTIME_TO_INT64_NOTIMPLEMENTED)
	#define USE_STO_LTIME_TO_INT64
	#define EXT_STO_LTIME_TO_INT64
	#define GET_STO_LTIME_TO_INT64(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_LTIME_TO_INT64(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_LTIME_TO_INT64  FALSE
	#define EXP_STO_LTIME_TO_INT64  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_LTIME_TO_INT64
	#define EXT_STO_LTIME_TO_INT64
	#define GET_STO_LTIME_TO_INT64(fl)  CAL_CMGETAPI( "STO_LTIME_TO_INT64" ) 
	#define CAL_STO_LTIME_TO_INT64  STO_LTIME_TO_INT64
	#define CHK_STO_LTIME_TO_INT64  TRUE
	#define EXP_STO_LTIME_TO_INT64  CAL_CMEXPAPI( "STO_LTIME_TO_INT64" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_LTIME_TO_INT64
	#define EXT_STO_LTIME_TO_INT64
	#define GET_STO_LTIME_TO_INT64(fl)  CAL_CMGETAPI( "STO_LTIME_TO_INT64" ) 
	#define CAL_STO_LTIME_TO_INT64  STO_LTIME_TO_INT64
	#define CHK_STO_LTIME_TO_INT64  TRUE
	#define EXP_STO_LTIME_TO_INT64  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_LTIME_TO_INT64", (RTS_UINTPTR)STO_LTIME_TO_INT64, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_LTIME_TO_INT64
	#define EXT_CmpCAAStorageSTO_LTIME_TO_INT64
	#define GET_CmpCAAStorageSTO_LTIME_TO_INT64  ERR_OK
	#define CAL_CmpCAAStorageSTO_LTIME_TO_INT64 pICmpCAAStorage->ISTO_LTIME_TO_INT64
	#define CHK_CmpCAAStorageSTO_LTIME_TO_INT64 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_LTIME_TO_INT64  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_LTIME_TO_INT64
	#define EXT_STO_LTIME_TO_INT64
	#define GET_STO_LTIME_TO_INT64(fl)  CAL_CMGETAPI( "STO_LTIME_TO_INT64" ) 
	#define CAL_STO_LTIME_TO_INT64 pICmpCAAStorage->ISTO_LTIME_TO_INT64
	#define CHK_STO_LTIME_TO_INT64 (pICmpCAAStorage != NULL)
	#define EXP_STO_LTIME_TO_INT64  CAL_CMEXPAPI( "STO_LTIME_TO_INT64" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_LTIME_TO_INT64  PFSTO_LTIME_TO_INT64 pfSTO_LTIME_TO_INT64;
	#define EXT_STO_LTIME_TO_INT64  extern PFSTO_LTIME_TO_INT64 pfSTO_LTIME_TO_INT64;
	#define GET_STO_LTIME_TO_INT64(fl)  s_pfCMGetAPI2( "STO_LTIME_TO_INT64", (RTS_VOID_FCTPTR *)&pfSTO_LTIME_TO_INT64, (fl), 0, 0)
	#define CAL_STO_LTIME_TO_INT64  pfSTO_LTIME_TO_INT64
	#define CHK_STO_LTIME_TO_INT64  (pfSTO_LTIME_TO_INT64 != NULL)
	#define EXP_STO_LTIME_TO_INT64  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_LTIME_TO_INT64", (RTS_UINTPTR)STO_LTIME_TO_INT64, 0, 0) 
#endif



STO_ERROR CDECL STO_LTIME_TO_ISO8601(CAA_LTIME ltValue, STO_ISO8601 *psValue);
typedef STO_ERROR (CDECL * PFSTO_LTIME_TO_ISO8601) (CAA_LTIME ltValue, STO_ISO8601 *psValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_LTIME_TO_ISO8601_NOTIMPLEMENTED)
	#define USE_STO_LTIME_TO_ISO8601
	#define EXT_STO_LTIME_TO_ISO8601
	#define GET_STO_LTIME_TO_ISO8601(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_LTIME_TO_ISO8601(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_LTIME_TO_ISO8601  FALSE
	#define EXP_STO_LTIME_TO_ISO8601  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_LTIME_TO_ISO8601
	#define EXT_STO_LTIME_TO_ISO8601
	#define GET_STO_LTIME_TO_ISO8601(fl)  CAL_CMGETAPI( "STO_LTIME_TO_ISO8601" ) 
	#define CAL_STO_LTIME_TO_ISO8601  STO_LTIME_TO_ISO8601
	#define CHK_STO_LTIME_TO_ISO8601  TRUE
	#define EXP_STO_LTIME_TO_ISO8601  CAL_CMEXPAPI( "STO_LTIME_TO_ISO8601" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_LTIME_TO_ISO8601
	#define EXT_STO_LTIME_TO_ISO8601
	#define GET_STO_LTIME_TO_ISO8601(fl)  CAL_CMGETAPI( "STO_LTIME_TO_ISO8601" ) 
	#define CAL_STO_LTIME_TO_ISO8601  STO_LTIME_TO_ISO8601
	#define CHK_STO_LTIME_TO_ISO8601  TRUE
	#define EXP_STO_LTIME_TO_ISO8601  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_LTIME_TO_ISO8601", (RTS_UINTPTR)STO_LTIME_TO_ISO8601, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_LTIME_TO_ISO8601
	#define EXT_CmpCAAStorageSTO_LTIME_TO_ISO8601
	#define GET_CmpCAAStorageSTO_LTIME_TO_ISO8601  ERR_OK
	#define CAL_CmpCAAStorageSTO_LTIME_TO_ISO8601 pICmpCAAStorage->ISTO_LTIME_TO_ISO8601
	#define CHK_CmpCAAStorageSTO_LTIME_TO_ISO8601 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_LTIME_TO_ISO8601  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_LTIME_TO_ISO8601
	#define EXT_STO_LTIME_TO_ISO8601
	#define GET_STO_LTIME_TO_ISO8601(fl)  CAL_CMGETAPI( "STO_LTIME_TO_ISO8601" ) 
	#define CAL_STO_LTIME_TO_ISO8601 pICmpCAAStorage->ISTO_LTIME_TO_ISO8601
	#define CHK_STO_LTIME_TO_ISO8601 (pICmpCAAStorage != NULL)
	#define EXP_STO_LTIME_TO_ISO8601  CAL_CMEXPAPI( "STO_LTIME_TO_ISO8601" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_LTIME_TO_ISO8601  PFSTO_LTIME_TO_ISO8601 pfSTO_LTIME_TO_ISO8601;
	#define EXT_STO_LTIME_TO_ISO8601  extern PFSTO_LTIME_TO_ISO8601 pfSTO_LTIME_TO_ISO8601;
	#define GET_STO_LTIME_TO_ISO8601(fl)  s_pfCMGetAPI2( "STO_LTIME_TO_ISO8601", (RTS_VOID_FCTPTR *)&pfSTO_LTIME_TO_ISO8601, (fl), 0, 0)
	#define CAL_STO_LTIME_TO_ISO8601  pfSTO_LTIME_TO_ISO8601
	#define CHK_STO_LTIME_TO_ISO8601  (pfSTO_LTIME_TO_ISO8601 != NULL)
	#define EXP_STO_LTIME_TO_ISO8601  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_LTIME_TO_ISO8601", (RTS_UINTPTR)STO_LTIME_TO_ISO8601, 0, 0) 
#endif



STO_ERROR CDECL STO_LTIME_TO_REAL8(CAA_LTIME ltValue, CAA_LREAL *plrValue);
typedef STO_ERROR (CDECL * PFSTO_LTIME_TO_REAL8) (CAA_LTIME ltValue, CAA_LREAL *plrValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_LTIME_TO_REAL8_NOTIMPLEMENTED)
	#define USE_STO_LTIME_TO_REAL8
	#define EXT_STO_LTIME_TO_REAL8
	#define GET_STO_LTIME_TO_REAL8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_LTIME_TO_REAL8(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_LTIME_TO_REAL8  FALSE
	#define EXP_STO_LTIME_TO_REAL8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_LTIME_TO_REAL8
	#define EXT_STO_LTIME_TO_REAL8
	#define GET_STO_LTIME_TO_REAL8(fl)  CAL_CMGETAPI( "STO_LTIME_TO_REAL8" ) 
	#define CAL_STO_LTIME_TO_REAL8  STO_LTIME_TO_REAL8
	#define CHK_STO_LTIME_TO_REAL8  TRUE
	#define EXP_STO_LTIME_TO_REAL8  CAL_CMEXPAPI( "STO_LTIME_TO_REAL8" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_LTIME_TO_REAL8
	#define EXT_STO_LTIME_TO_REAL8
	#define GET_STO_LTIME_TO_REAL8(fl)  CAL_CMGETAPI( "STO_LTIME_TO_REAL8" ) 
	#define CAL_STO_LTIME_TO_REAL8  STO_LTIME_TO_REAL8
	#define CHK_STO_LTIME_TO_REAL8  TRUE
	#define EXP_STO_LTIME_TO_REAL8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_LTIME_TO_REAL8", (RTS_UINTPTR)STO_LTIME_TO_REAL8, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_LTIME_TO_REAL8
	#define EXT_CmpCAAStorageSTO_LTIME_TO_REAL8
	#define GET_CmpCAAStorageSTO_LTIME_TO_REAL8  ERR_OK
	#define CAL_CmpCAAStorageSTO_LTIME_TO_REAL8 pICmpCAAStorage->ISTO_LTIME_TO_REAL8
	#define CHK_CmpCAAStorageSTO_LTIME_TO_REAL8 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_LTIME_TO_REAL8  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_LTIME_TO_REAL8
	#define EXT_STO_LTIME_TO_REAL8
	#define GET_STO_LTIME_TO_REAL8(fl)  CAL_CMGETAPI( "STO_LTIME_TO_REAL8" ) 
	#define CAL_STO_LTIME_TO_REAL8 pICmpCAAStorage->ISTO_LTIME_TO_REAL8
	#define CHK_STO_LTIME_TO_REAL8 (pICmpCAAStorage != NULL)
	#define EXP_STO_LTIME_TO_REAL8  CAL_CMEXPAPI( "STO_LTIME_TO_REAL8" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_LTIME_TO_REAL8  PFSTO_LTIME_TO_REAL8 pfSTO_LTIME_TO_REAL8;
	#define EXT_STO_LTIME_TO_REAL8  extern PFSTO_LTIME_TO_REAL8 pfSTO_LTIME_TO_REAL8;
	#define GET_STO_LTIME_TO_REAL8(fl)  s_pfCMGetAPI2( "STO_LTIME_TO_REAL8", (RTS_VOID_FCTPTR *)&pfSTO_LTIME_TO_REAL8, (fl), 0, 0)
	#define CAL_STO_LTIME_TO_REAL8  pfSTO_LTIME_TO_REAL8
	#define CHK_STO_LTIME_TO_REAL8  (pfSTO_LTIME_TO_REAL8 != NULL)
	#define EXP_STO_LTIME_TO_REAL8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_LTIME_TO_REAL8", (RTS_UINTPTR)STO_LTIME_TO_REAL8, 0, 0) 
#endif



STO_ERROR CDECL STO_REAL8_TO_DT(CAA_LREAL lrValue, CAA_DT *pdtValue);
typedef STO_ERROR (CDECL * PFSTO_REAL8_TO_DT) (CAA_LREAL lrValue, CAA_DT *pdtValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_REAL8_TO_DT_NOTIMPLEMENTED)
	#define USE_STO_REAL8_TO_DT
	#define EXT_STO_REAL8_TO_DT
	#define GET_STO_REAL8_TO_DT(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_REAL8_TO_DT(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_REAL8_TO_DT  FALSE
	#define EXP_STO_REAL8_TO_DT  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_REAL8_TO_DT
	#define EXT_STO_REAL8_TO_DT
	#define GET_STO_REAL8_TO_DT(fl)  CAL_CMGETAPI( "STO_REAL8_TO_DT" ) 
	#define CAL_STO_REAL8_TO_DT  STO_REAL8_TO_DT
	#define CHK_STO_REAL8_TO_DT  TRUE
	#define EXP_STO_REAL8_TO_DT  CAL_CMEXPAPI( "STO_REAL8_TO_DT" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_REAL8_TO_DT
	#define EXT_STO_REAL8_TO_DT
	#define GET_STO_REAL8_TO_DT(fl)  CAL_CMGETAPI( "STO_REAL8_TO_DT" ) 
	#define CAL_STO_REAL8_TO_DT  STO_REAL8_TO_DT
	#define CHK_STO_REAL8_TO_DT  TRUE
	#define EXP_STO_REAL8_TO_DT  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_REAL8_TO_DT", (RTS_UINTPTR)STO_REAL8_TO_DT, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_REAL8_TO_DT
	#define EXT_CmpCAAStorageSTO_REAL8_TO_DT
	#define GET_CmpCAAStorageSTO_REAL8_TO_DT  ERR_OK
	#define CAL_CmpCAAStorageSTO_REAL8_TO_DT pICmpCAAStorage->ISTO_REAL8_TO_DT
	#define CHK_CmpCAAStorageSTO_REAL8_TO_DT (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_REAL8_TO_DT  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_REAL8_TO_DT
	#define EXT_STO_REAL8_TO_DT
	#define GET_STO_REAL8_TO_DT(fl)  CAL_CMGETAPI( "STO_REAL8_TO_DT" ) 
	#define CAL_STO_REAL8_TO_DT pICmpCAAStorage->ISTO_REAL8_TO_DT
	#define CHK_STO_REAL8_TO_DT (pICmpCAAStorage != NULL)
	#define EXP_STO_REAL8_TO_DT  CAL_CMEXPAPI( "STO_REAL8_TO_DT" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_REAL8_TO_DT  PFSTO_REAL8_TO_DT pfSTO_REAL8_TO_DT;
	#define EXT_STO_REAL8_TO_DT  extern PFSTO_REAL8_TO_DT pfSTO_REAL8_TO_DT;
	#define GET_STO_REAL8_TO_DT(fl)  s_pfCMGetAPI2( "STO_REAL8_TO_DT", (RTS_VOID_FCTPTR *)&pfSTO_REAL8_TO_DT, (fl), 0, 0)
	#define CAL_STO_REAL8_TO_DT  pfSTO_REAL8_TO_DT
	#define CHK_STO_REAL8_TO_DT  (pfSTO_REAL8_TO_DT != NULL)
	#define EXP_STO_REAL8_TO_DT  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_REAL8_TO_DT", (RTS_UINTPTR)STO_REAL8_TO_DT, 0, 0) 
#endif



STO_ERROR CDECL STO_REAL8_TO_LTIME(CAA_LREAL lrValue, CAA_LTIME *pltValue);
typedef STO_ERROR (CDECL * PFSTO_REAL8_TO_LTIME) (CAA_LREAL lrValue, CAA_LTIME *pltValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_REAL8_TO_LTIME_NOTIMPLEMENTED)
	#define USE_STO_REAL8_TO_LTIME
	#define EXT_STO_REAL8_TO_LTIME
	#define GET_STO_REAL8_TO_LTIME(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_REAL8_TO_LTIME(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_REAL8_TO_LTIME  FALSE
	#define EXP_STO_REAL8_TO_LTIME  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_REAL8_TO_LTIME
	#define EXT_STO_REAL8_TO_LTIME
	#define GET_STO_REAL8_TO_LTIME(fl)  CAL_CMGETAPI( "STO_REAL8_TO_LTIME" ) 
	#define CAL_STO_REAL8_TO_LTIME  STO_REAL8_TO_LTIME
	#define CHK_STO_REAL8_TO_LTIME  TRUE
	#define EXP_STO_REAL8_TO_LTIME  CAL_CMEXPAPI( "STO_REAL8_TO_LTIME" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_REAL8_TO_LTIME
	#define EXT_STO_REAL8_TO_LTIME
	#define GET_STO_REAL8_TO_LTIME(fl)  CAL_CMGETAPI( "STO_REAL8_TO_LTIME" ) 
	#define CAL_STO_REAL8_TO_LTIME  STO_REAL8_TO_LTIME
	#define CHK_STO_REAL8_TO_LTIME  TRUE
	#define EXP_STO_REAL8_TO_LTIME  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_REAL8_TO_LTIME", (RTS_UINTPTR)STO_REAL8_TO_LTIME, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_REAL8_TO_LTIME
	#define EXT_CmpCAAStorageSTO_REAL8_TO_LTIME
	#define GET_CmpCAAStorageSTO_REAL8_TO_LTIME  ERR_OK
	#define CAL_CmpCAAStorageSTO_REAL8_TO_LTIME pICmpCAAStorage->ISTO_REAL8_TO_LTIME
	#define CHK_CmpCAAStorageSTO_REAL8_TO_LTIME (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_REAL8_TO_LTIME  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_REAL8_TO_LTIME
	#define EXT_STO_REAL8_TO_LTIME
	#define GET_STO_REAL8_TO_LTIME(fl)  CAL_CMGETAPI( "STO_REAL8_TO_LTIME" ) 
	#define CAL_STO_REAL8_TO_LTIME pICmpCAAStorage->ISTO_REAL8_TO_LTIME
	#define CHK_STO_REAL8_TO_LTIME (pICmpCAAStorage != NULL)
	#define EXP_STO_REAL8_TO_LTIME  CAL_CMEXPAPI( "STO_REAL8_TO_LTIME" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_REAL8_TO_LTIME  PFSTO_REAL8_TO_LTIME pfSTO_REAL8_TO_LTIME;
	#define EXT_STO_REAL8_TO_LTIME  extern PFSTO_REAL8_TO_LTIME pfSTO_REAL8_TO_LTIME;
	#define GET_STO_REAL8_TO_LTIME(fl)  s_pfCMGetAPI2( "STO_REAL8_TO_LTIME", (RTS_VOID_FCTPTR *)&pfSTO_REAL8_TO_LTIME, (fl), 0, 0)
	#define CAL_STO_REAL8_TO_LTIME  pfSTO_REAL8_TO_LTIME
	#define CHK_STO_REAL8_TO_LTIME  (pfSTO_REAL8_TO_LTIME != NULL)
	#define EXP_STO_REAL8_TO_LTIME  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_REAL8_TO_LTIME", (RTS_UINTPTR)STO_REAL8_TO_LTIME, 0, 0) 
#endif



STO_ERROR CDECL STO_REAL8_TO_TIME(CAA_LREAL lrValue, CAA_TIME *ptValue);
typedef STO_ERROR (CDECL * PFSTO_REAL8_TO_TIME) (CAA_LREAL lrValue, CAA_TIME *ptValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_REAL8_TO_TIME_NOTIMPLEMENTED)
	#define USE_STO_REAL8_TO_TIME
	#define EXT_STO_REAL8_TO_TIME
	#define GET_STO_REAL8_TO_TIME(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_REAL8_TO_TIME(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_REAL8_TO_TIME  FALSE
	#define EXP_STO_REAL8_TO_TIME  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_REAL8_TO_TIME
	#define EXT_STO_REAL8_TO_TIME
	#define GET_STO_REAL8_TO_TIME(fl)  CAL_CMGETAPI( "STO_REAL8_TO_TIME" ) 
	#define CAL_STO_REAL8_TO_TIME  STO_REAL8_TO_TIME
	#define CHK_STO_REAL8_TO_TIME  TRUE
	#define EXP_STO_REAL8_TO_TIME  CAL_CMEXPAPI( "STO_REAL8_TO_TIME" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_REAL8_TO_TIME
	#define EXT_STO_REAL8_TO_TIME
	#define GET_STO_REAL8_TO_TIME(fl)  CAL_CMGETAPI( "STO_REAL8_TO_TIME" ) 
	#define CAL_STO_REAL8_TO_TIME  STO_REAL8_TO_TIME
	#define CHK_STO_REAL8_TO_TIME  TRUE
	#define EXP_STO_REAL8_TO_TIME  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_REAL8_TO_TIME", (RTS_UINTPTR)STO_REAL8_TO_TIME, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_REAL8_TO_TIME
	#define EXT_CmpCAAStorageSTO_REAL8_TO_TIME
	#define GET_CmpCAAStorageSTO_REAL8_TO_TIME  ERR_OK
	#define CAL_CmpCAAStorageSTO_REAL8_TO_TIME pICmpCAAStorage->ISTO_REAL8_TO_TIME
	#define CHK_CmpCAAStorageSTO_REAL8_TO_TIME (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_REAL8_TO_TIME  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_REAL8_TO_TIME
	#define EXT_STO_REAL8_TO_TIME
	#define GET_STO_REAL8_TO_TIME(fl)  CAL_CMGETAPI( "STO_REAL8_TO_TIME" ) 
	#define CAL_STO_REAL8_TO_TIME pICmpCAAStorage->ISTO_REAL8_TO_TIME
	#define CHK_STO_REAL8_TO_TIME (pICmpCAAStorage != NULL)
	#define EXP_STO_REAL8_TO_TIME  CAL_CMEXPAPI( "STO_REAL8_TO_TIME" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_REAL8_TO_TIME  PFSTO_REAL8_TO_TIME pfSTO_REAL8_TO_TIME;
	#define EXT_STO_REAL8_TO_TIME  extern PFSTO_REAL8_TO_TIME pfSTO_REAL8_TO_TIME;
	#define GET_STO_REAL8_TO_TIME(fl)  s_pfCMGetAPI2( "STO_REAL8_TO_TIME", (RTS_VOID_FCTPTR *)&pfSTO_REAL8_TO_TIME, (fl), 0, 0)
	#define CAL_STO_REAL8_TO_TIME  pfSTO_REAL8_TO_TIME
	#define CHK_STO_REAL8_TO_TIME  (pfSTO_REAL8_TO_TIME != NULL)
	#define EXP_STO_REAL8_TO_TIME  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_REAL8_TO_TIME", (RTS_UINTPTR)STO_REAL8_TO_TIME, 0, 0) 
#endif



STO_ERROR CDECL STO_TIME_TO_INT64(CAA_TIME tValue, CAA_LINT *pliValue);
typedef STO_ERROR (CDECL * PFSTO_TIME_TO_INT64) (CAA_TIME tValue, CAA_LINT *pliValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_TIME_TO_INT64_NOTIMPLEMENTED)
	#define USE_STO_TIME_TO_INT64
	#define EXT_STO_TIME_TO_INT64
	#define GET_STO_TIME_TO_INT64(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_TIME_TO_INT64(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_TIME_TO_INT64  FALSE
	#define EXP_STO_TIME_TO_INT64  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_TIME_TO_INT64
	#define EXT_STO_TIME_TO_INT64
	#define GET_STO_TIME_TO_INT64(fl)  CAL_CMGETAPI( "STO_TIME_TO_INT64" ) 
	#define CAL_STO_TIME_TO_INT64  STO_TIME_TO_INT64
	#define CHK_STO_TIME_TO_INT64  TRUE
	#define EXP_STO_TIME_TO_INT64  CAL_CMEXPAPI( "STO_TIME_TO_INT64" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_TIME_TO_INT64
	#define EXT_STO_TIME_TO_INT64
	#define GET_STO_TIME_TO_INT64(fl)  CAL_CMGETAPI( "STO_TIME_TO_INT64" ) 
	#define CAL_STO_TIME_TO_INT64  STO_TIME_TO_INT64
	#define CHK_STO_TIME_TO_INT64  TRUE
	#define EXP_STO_TIME_TO_INT64  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_TIME_TO_INT64", (RTS_UINTPTR)STO_TIME_TO_INT64, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_TIME_TO_INT64
	#define EXT_CmpCAAStorageSTO_TIME_TO_INT64
	#define GET_CmpCAAStorageSTO_TIME_TO_INT64  ERR_OK
	#define CAL_CmpCAAStorageSTO_TIME_TO_INT64 pICmpCAAStorage->ISTO_TIME_TO_INT64
	#define CHK_CmpCAAStorageSTO_TIME_TO_INT64 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_TIME_TO_INT64  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_TIME_TO_INT64
	#define EXT_STO_TIME_TO_INT64
	#define GET_STO_TIME_TO_INT64(fl)  CAL_CMGETAPI( "STO_TIME_TO_INT64" ) 
	#define CAL_STO_TIME_TO_INT64 pICmpCAAStorage->ISTO_TIME_TO_INT64
	#define CHK_STO_TIME_TO_INT64 (pICmpCAAStorage != NULL)
	#define EXP_STO_TIME_TO_INT64  CAL_CMEXPAPI( "STO_TIME_TO_INT64" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_TIME_TO_INT64  PFSTO_TIME_TO_INT64 pfSTO_TIME_TO_INT64;
	#define EXT_STO_TIME_TO_INT64  extern PFSTO_TIME_TO_INT64 pfSTO_TIME_TO_INT64;
	#define GET_STO_TIME_TO_INT64(fl)  s_pfCMGetAPI2( "STO_TIME_TO_INT64", (RTS_VOID_FCTPTR *)&pfSTO_TIME_TO_INT64, (fl), 0, 0)
	#define CAL_STO_TIME_TO_INT64  pfSTO_TIME_TO_INT64
	#define CHK_STO_TIME_TO_INT64  (pfSTO_TIME_TO_INT64 != NULL)
	#define EXP_STO_TIME_TO_INT64  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_TIME_TO_INT64", (RTS_UINTPTR)STO_TIME_TO_INT64, 0, 0) 
#endif



STO_ERROR CDECL STO_TIME_TO_ISO8601(CAA_TIME tValue, STO_ISO8601 *psValue);
typedef STO_ERROR (CDECL * PFSTO_TIME_TO_ISO8601) (CAA_TIME tValue, STO_ISO8601 *psValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_TIME_TO_ISO8601_NOTIMPLEMENTED)
	#define USE_STO_TIME_TO_ISO8601
	#define EXT_STO_TIME_TO_ISO8601
	#define GET_STO_TIME_TO_ISO8601(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_TIME_TO_ISO8601(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_TIME_TO_ISO8601  FALSE
	#define EXP_STO_TIME_TO_ISO8601  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_TIME_TO_ISO8601
	#define EXT_STO_TIME_TO_ISO8601
	#define GET_STO_TIME_TO_ISO8601(fl)  CAL_CMGETAPI( "STO_TIME_TO_ISO8601" ) 
	#define CAL_STO_TIME_TO_ISO8601  STO_TIME_TO_ISO8601
	#define CHK_STO_TIME_TO_ISO8601  TRUE
	#define EXP_STO_TIME_TO_ISO8601  CAL_CMEXPAPI( "STO_TIME_TO_ISO8601" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_TIME_TO_ISO8601
	#define EXT_STO_TIME_TO_ISO8601
	#define GET_STO_TIME_TO_ISO8601(fl)  CAL_CMGETAPI( "STO_TIME_TO_ISO8601" ) 
	#define CAL_STO_TIME_TO_ISO8601  STO_TIME_TO_ISO8601
	#define CHK_STO_TIME_TO_ISO8601  TRUE
	#define EXP_STO_TIME_TO_ISO8601  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_TIME_TO_ISO8601", (RTS_UINTPTR)STO_TIME_TO_ISO8601, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_TIME_TO_ISO8601
	#define EXT_CmpCAAStorageSTO_TIME_TO_ISO8601
	#define GET_CmpCAAStorageSTO_TIME_TO_ISO8601  ERR_OK
	#define CAL_CmpCAAStorageSTO_TIME_TO_ISO8601 pICmpCAAStorage->ISTO_TIME_TO_ISO8601
	#define CHK_CmpCAAStorageSTO_TIME_TO_ISO8601 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_TIME_TO_ISO8601  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_TIME_TO_ISO8601
	#define EXT_STO_TIME_TO_ISO8601
	#define GET_STO_TIME_TO_ISO8601(fl)  CAL_CMGETAPI( "STO_TIME_TO_ISO8601" ) 
	#define CAL_STO_TIME_TO_ISO8601 pICmpCAAStorage->ISTO_TIME_TO_ISO8601
	#define CHK_STO_TIME_TO_ISO8601 (pICmpCAAStorage != NULL)
	#define EXP_STO_TIME_TO_ISO8601  CAL_CMEXPAPI( "STO_TIME_TO_ISO8601" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_TIME_TO_ISO8601  PFSTO_TIME_TO_ISO8601 pfSTO_TIME_TO_ISO8601;
	#define EXT_STO_TIME_TO_ISO8601  extern PFSTO_TIME_TO_ISO8601 pfSTO_TIME_TO_ISO8601;
	#define GET_STO_TIME_TO_ISO8601(fl)  s_pfCMGetAPI2( "STO_TIME_TO_ISO8601", (RTS_VOID_FCTPTR *)&pfSTO_TIME_TO_ISO8601, (fl), 0, 0)
	#define CAL_STO_TIME_TO_ISO8601  pfSTO_TIME_TO_ISO8601
	#define CHK_STO_TIME_TO_ISO8601  (pfSTO_TIME_TO_ISO8601 != NULL)
	#define EXP_STO_TIME_TO_ISO8601  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_TIME_TO_ISO8601", (RTS_UINTPTR)STO_TIME_TO_ISO8601, 0, 0) 
#endif



STO_ERROR CDECL STO_TIME_TO_REAL8(CAA_TIME tValue, CAA_LREAL *plrValue);
typedef STO_ERROR (CDECL * PFSTO_TIME_TO_REAL8) (CAA_TIME tValue, CAA_LREAL *plrValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_TIME_TO_REAL8_NOTIMPLEMENTED)
	#define USE_STO_TIME_TO_REAL8
	#define EXT_STO_TIME_TO_REAL8
	#define GET_STO_TIME_TO_REAL8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_TIME_TO_REAL8(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_TIME_TO_REAL8  FALSE
	#define EXP_STO_TIME_TO_REAL8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_TIME_TO_REAL8
	#define EXT_STO_TIME_TO_REAL8
	#define GET_STO_TIME_TO_REAL8(fl)  CAL_CMGETAPI( "STO_TIME_TO_REAL8" ) 
	#define CAL_STO_TIME_TO_REAL8  STO_TIME_TO_REAL8
	#define CHK_STO_TIME_TO_REAL8  TRUE
	#define EXP_STO_TIME_TO_REAL8  CAL_CMEXPAPI( "STO_TIME_TO_REAL8" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_TIME_TO_REAL8
	#define EXT_STO_TIME_TO_REAL8
	#define GET_STO_TIME_TO_REAL8(fl)  CAL_CMGETAPI( "STO_TIME_TO_REAL8" ) 
	#define CAL_STO_TIME_TO_REAL8  STO_TIME_TO_REAL8
	#define CHK_STO_TIME_TO_REAL8  TRUE
	#define EXP_STO_TIME_TO_REAL8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_TIME_TO_REAL8", (RTS_UINTPTR)STO_TIME_TO_REAL8, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_TIME_TO_REAL8
	#define EXT_CmpCAAStorageSTO_TIME_TO_REAL8
	#define GET_CmpCAAStorageSTO_TIME_TO_REAL8  ERR_OK
	#define CAL_CmpCAAStorageSTO_TIME_TO_REAL8 pICmpCAAStorage->ISTO_TIME_TO_REAL8
	#define CHK_CmpCAAStorageSTO_TIME_TO_REAL8 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_TIME_TO_REAL8  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_TIME_TO_REAL8
	#define EXT_STO_TIME_TO_REAL8
	#define GET_STO_TIME_TO_REAL8(fl)  CAL_CMGETAPI( "STO_TIME_TO_REAL8" ) 
	#define CAL_STO_TIME_TO_REAL8 pICmpCAAStorage->ISTO_TIME_TO_REAL8
	#define CHK_STO_TIME_TO_REAL8 (pICmpCAAStorage != NULL)
	#define EXP_STO_TIME_TO_REAL8  CAL_CMEXPAPI( "STO_TIME_TO_REAL8" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_TIME_TO_REAL8  PFSTO_TIME_TO_REAL8 pfSTO_TIME_TO_REAL8;
	#define EXT_STO_TIME_TO_REAL8  extern PFSTO_TIME_TO_REAL8 pfSTO_TIME_TO_REAL8;
	#define GET_STO_TIME_TO_REAL8(fl)  s_pfCMGetAPI2( "STO_TIME_TO_REAL8", (RTS_VOID_FCTPTR *)&pfSTO_TIME_TO_REAL8, (fl), 0, 0)
	#define CAL_STO_TIME_TO_REAL8  pfSTO_TIME_TO_REAL8
	#define CHK_STO_TIME_TO_REAL8  (pfSTO_TIME_TO_REAL8 != NULL)
	#define EXP_STO_TIME_TO_REAL8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_TIME_TO_REAL8", (RTS_UINTPTR)STO_TIME_TO_REAL8, 0, 0) 
#endif




STO_ERROR CDECL STO_CreateTextFromString(CAA_STRING * psValue, STO_TEXT* ptxtValue);
typedef STO_ERROR (CDECL * PFSTO_CREATETEXTFROMSTRING) (CAA_STRING * psValue, STO_TEXT* ptxtValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_CREATETEXTFROMSTRING_NOTIMPLEMENTED)
	#define USE_STO_CreateTextFromString
	#define EXT_STO_CreateTextFromString
	#define GET_STO_CreateTextFromString(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_CreateTextFromString(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_CreateTextFromString  FALSE
	#define EXP_STO_CreateTextFromString  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_CreateTextFromString
	#define EXT_STO_CreateTextFromString
	#define GET_STO_CreateTextFromString(fl)  CAL_CMGETAPI( "STO_CreateTextFromString" ) 
	#define CAL_STO_CreateTextFromString  STO_CreateTextFromString
	#define CHK_STO_CreateTextFromString  TRUE
	#define EXP_STO_CreateTextFromString  CAL_CMEXPAPI( "STO_CreateTextFromString" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_CreateTextFromString
	#define EXT_STO_CreateTextFromString
	#define GET_STO_CreateTextFromString(fl)  CAL_CMGETAPI( "STO_CreateTextFromString" ) 
	#define CAL_STO_CreateTextFromString  STO_CreateTextFromString
	#define CHK_STO_CreateTextFromString  TRUE
	#define EXP_STO_CreateTextFromString  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_CreateTextFromString", (RTS_UINTPTR)STO_CreateTextFromString, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_CreateTextFromString
	#define EXT_CmpCAAStorageSTO_CreateTextFromString
	#define GET_CmpCAAStorageSTO_CreateTextFromString  ERR_OK
	#define CAL_CmpCAAStorageSTO_CreateTextFromString pICmpCAAStorage->ISTO_CreateTextFromString
	#define CHK_CmpCAAStorageSTO_CreateTextFromString (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_CreateTextFromString  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_CreateTextFromString
	#define EXT_STO_CreateTextFromString
	#define GET_STO_CreateTextFromString(fl)  CAL_CMGETAPI( "STO_CreateTextFromString" ) 
	#define CAL_STO_CreateTextFromString pICmpCAAStorage->ISTO_CreateTextFromString
	#define CHK_STO_CreateTextFromString (pICmpCAAStorage != NULL)
	#define EXP_STO_CreateTextFromString  CAL_CMEXPAPI( "STO_CreateTextFromString" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_CreateTextFromString  PFSTO_CREATETEXTFROMSTRING pfSTO_CreateTextFromString;
	#define EXT_STO_CreateTextFromString  extern PFSTO_CREATETEXTFROMSTRING pfSTO_CreateTextFromString;
	#define GET_STO_CreateTextFromString(fl)  s_pfCMGetAPI2( "STO_CreateTextFromString", (RTS_VOID_FCTPTR *)&pfSTO_CreateTextFromString, (fl), 0, 0)
	#define CAL_STO_CreateTextFromString  pfSTO_CreateTextFromString
	#define CHK_STO_CreateTextFromString  (pfSTO_CreateTextFromString != NULL)
	#define EXP_STO_CreateTextFromString  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_CreateTextFromString", (RTS_UINTPTR)STO_CreateTextFromString, 0, 0) 
#endif



STO_ERROR CDECL STO_CreateTextFromWString(CAA_WSTRING * pwsValue, STO_TEXT* ptxtValue);
typedef STO_ERROR (CDECL * PFSTO_CREATETEXTFROMWSTRING) (CAA_WSTRING * pwsValue, STO_TEXT* ptxtValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_CREATETEXTFROMWSTRING_NOTIMPLEMENTED)
	#define USE_STO_CreateTextFromWString
	#define EXT_STO_CreateTextFromWString
	#define GET_STO_CreateTextFromWString(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_CreateTextFromWString(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_CreateTextFromWString  FALSE
	#define EXP_STO_CreateTextFromWString  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_CreateTextFromWString
	#define EXT_STO_CreateTextFromWString
	#define GET_STO_CreateTextFromWString(fl)  CAL_CMGETAPI( "STO_CreateTextFromWString" ) 
	#define CAL_STO_CreateTextFromWString  STO_CreateTextFromWString
	#define CHK_STO_CreateTextFromWString  TRUE
	#define EXP_STO_CreateTextFromWString  CAL_CMEXPAPI( "STO_CreateTextFromWString" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_CreateTextFromWString
	#define EXT_STO_CreateTextFromWString
	#define GET_STO_CreateTextFromWString(fl)  CAL_CMGETAPI( "STO_CreateTextFromWString" ) 
	#define CAL_STO_CreateTextFromWString  STO_CreateTextFromWString
	#define CHK_STO_CreateTextFromWString  TRUE
	#define EXP_STO_CreateTextFromWString  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_CreateTextFromWString", (RTS_UINTPTR)STO_CreateTextFromWString, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_CreateTextFromWString
	#define EXT_CmpCAAStorageSTO_CreateTextFromWString
	#define GET_CmpCAAStorageSTO_CreateTextFromWString  ERR_OK
	#define CAL_CmpCAAStorageSTO_CreateTextFromWString pICmpCAAStorage->ISTO_CreateTextFromWString
	#define CHK_CmpCAAStorageSTO_CreateTextFromWString (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_CreateTextFromWString  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_CreateTextFromWString
	#define EXT_STO_CreateTextFromWString
	#define GET_STO_CreateTextFromWString(fl)  CAL_CMGETAPI( "STO_CreateTextFromWString" ) 
	#define CAL_STO_CreateTextFromWString pICmpCAAStorage->ISTO_CreateTextFromWString
	#define CHK_STO_CreateTextFromWString (pICmpCAAStorage != NULL)
	#define EXP_STO_CreateTextFromWString  CAL_CMEXPAPI( "STO_CreateTextFromWString" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_CreateTextFromWString  PFSTO_CREATETEXTFROMWSTRING pfSTO_CreateTextFromWString;
	#define EXT_STO_CreateTextFromWString  extern PFSTO_CREATETEXTFROMWSTRING pfSTO_CreateTextFromWString;
	#define GET_STO_CreateTextFromWString(fl)  s_pfCMGetAPI2( "STO_CreateTextFromWString", (RTS_VOID_FCTPTR *)&pfSTO_CreateTextFromWString, (fl), 0, 0)
	#define CAL_STO_CreateTextFromWString  pfSTO_CreateTextFromWString
	#define CHK_STO_CreateTextFromWString  (pfSTO_CreateTextFromWString != NULL)
	#define EXP_STO_CreateTextFromWString  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_CreateTextFromWString", (RTS_UINTPTR)STO_CreateTextFromWString, 0, 0) 
#endif



STO_ERROR CDECL STO_TextCopyToString(STO_TEXT* ptxtText, CAA_STRING * psValue, CAA_SIZE szValue, CAA_BOOL xFree);
typedef STO_ERROR (CDECL * PFSTO_TEXTCOPYTOSTRING) (STO_TEXT* ptxtText, CAA_STRING * psValue, CAA_SIZE szValue, CAA_BOOL xFree);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_TEXTCOPYTOSTRING_NOTIMPLEMENTED)
	#define USE_STO_TextCopyToString
	#define EXT_STO_TextCopyToString
	#define GET_STO_TextCopyToString(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_TextCopyToString(p0,p1,p2,p3)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_TextCopyToString  FALSE
	#define EXP_STO_TextCopyToString  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_TextCopyToString
	#define EXT_STO_TextCopyToString
	#define GET_STO_TextCopyToString(fl)  CAL_CMGETAPI( "STO_TextCopyToString" ) 
	#define CAL_STO_TextCopyToString  STO_TextCopyToString
	#define CHK_STO_TextCopyToString  TRUE
	#define EXP_STO_TextCopyToString  CAL_CMEXPAPI( "STO_TextCopyToString" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_TextCopyToString
	#define EXT_STO_TextCopyToString
	#define GET_STO_TextCopyToString(fl)  CAL_CMGETAPI( "STO_TextCopyToString" ) 
	#define CAL_STO_TextCopyToString  STO_TextCopyToString
	#define CHK_STO_TextCopyToString  TRUE
	#define EXP_STO_TextCopyToString  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_TextCopyToString", (RTS_UINTPTR)STO_TextCopyToString, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_TextCopyToString
	#define EXT_CmpCAAStorageSTO_TextCopyToString
	#define GET_CmpCAAStorageSTO_TextCopyToString  ERR_OK
	#define CAL_CmpCAAStorageSTO_TextCopyToString pICmpCAAStorage->ISTO_TextCopyToString
	#define CHK_CmpCAAStorageSTO_TextCopyToString (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_TextCopyToString  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_TextCopyToString
	#define EXT_STO_TextCopyToString
	#define GET_STO_TextCopyToString(fl)  CAL_CMGETAPI( "STO_TextCopyToString" ) 
	#define CAL_STO_TextCopyToString pICmpCAAStorage->ISTO_TextCopyToString
	#define CHK_STO_TextCopyToString (pICmpCAAStorage != NULL)
	#define EXP_STO_TextCopyToString  CAL_CMEXPAPI( "STO_TextCopyToString" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_TextCopyToString  PFSTO_TEXTCOPYTOSTRING pfSTO_TextCopyToString;
	#define EXT_STO_TextCopyToString  extern PFSTO_TEXTCOPYTOSTRING pfSTO_TextCopyToString;
	#define GET_STO_TextCopyToString(fl)  s_pfCMGetAPI2( "STO_TextCopyToString", (RTS_VOID_FCTPTR *)&pfSTO_TextCopyToString, (fl), 0, 0)
	#define CAL_STO_TextCopyToString  pfSTO_TextCopyToString
	#define CHK_STO_TextCopyToString  (pfSTO_TextCopyToString != NULL)
	#define EXP_STO_TextCopyToString  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_TextCopyToString", (RTS_UINTPTR)STO_TextCopyToString, 0, 0) 
#endif



STO_ERROR CDECL STO_TextCopyToWString(STO_TEXT* ptxtValue, CAA_WSTRING* pwsValue, CAA_SIZE szValue, CAA_BOOL xFree);
typedef STO_ERROR (CDECL * PFSTO_TEXTCOPYTOWSTRING) (STO_TEXT* ptxtValue, CAA_WSTRING* pwsValue, CAA_SIZE szValue, CAA_BOOL xFree);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_TEXTCOPYTOWSTRING_NOTIMPLEMENTED)
	#define USE_STO_TextCopyToWString
	#define EXT_STO_TextCopyToWString
	#define GET_STO_TextCopyToWString(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_TextCopyToWString(p0,p1,p2,p3)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_TextCopyToWString  FALSE
	#define EXP_STO_TextCopyToWString  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_TextCopyToWString
	#define EXT_STO_TextCopyToWString
	#define GET_STO_TextCopyToWString(fl)  CAL_CMGETAPI( "STO_TextCopyToWString" ) 
	#define CAL_STO_TextCopyToWString  STO_TextCopyToWString
	#define CHK_STO_TextCopyToWString  TRUE
	#define EXP_STO_TextCopyToWString  CAL_CMEXPAPI( "STO_TextCopyToWString" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_TextCopyToWString
	#define EXT_STO_TextCopyToWString
	#define GET_STO_TextCopyToWString(fl)  CAL_CMGETAPI( "STO_TextCopyToWString" ) 
	#define CAL_STO_TextCopyToWString  STO_TextCopyToWString
	#define CHK_STO_TextCopyToWString  TRUE
	#define EXP_STO_TextCopyToWString  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_TextCopyToWString", (RTS_UINTPTR)STO_TextCopyToWString, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_TextCopyToWString
	#define EXT_CmpCAAStorageSTO_TextCopyToWString
	#define GET_CmpCAAStorageSTO_TextCopyToWString  ERR_OK
	#define CAL_CmpCAAStorageSTO_TextCopyToWString pICmpCAAStorage->ISTO_TextCopyToWString
	#define CHK_CmpCAAStorageSTO_TextCopyToWString (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_TextCopyToWString  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_TextCopyToWString
	#define EXT_STO_TextCopyToWString
	#define GET_STO_TextCopyToWString(fl)  CAL_CMGETAPI( "STO_TextCopyToWString" ) 
	#define CAL_STO_TextCopyToWString pICmpCAAStorage->ISTO_TextCopyToWString
	#define CHK_STO_TextCopyToWString (pICmpCAAStorage != NULL)
	#define EXP_STO_TextCopyToWString  CAL_CMEXPAPI( "STO_TextCopyToWString" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_TextCopyToWString  PFSTO_TEXTCOPYTOWSTRING pfSTO_TextCopyToWString;
	#define EXT_STO_TextCopyToWString  extern PFSTO_TEXTCOPYTOWSTRING pfSTO_TextCopyToWString;
	#define GET_STO_TextCopyToWString(fl)  s_pfCMGetAPI2( "STO_TextCopyToWString", (RTS_VOID_FCTPTR *)&pfSTO_TextCopyToWString, (fl), 0, 0)
	#define CAL_STO_TextCopyToWString  pfSTO_TextCopyToWString
	#define CHK_STO_TextCopyToWString  (pfSTO_TextCopyToWString != NULL)
	#define EXP_STO_TextCopyToWString  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_TextCopyToWString", (RTS_UINTPTR)STO_TextCopyToWString, 0, 0) 
#endif



STO_ERROR CDECL STO_TextFree(STO_TEXT* ptxtValue);
typedef STO_ERROR (CDECL * PFSTO_TEXTFREE) (STO_TEXT* ptxtValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_TEXTFREE_NOTIMPLEMENTED)
	#define USE_STO_TextFree
	#define EXT_STO_TextFree
	#define GET_STO_TextFree(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_TextFree(p0)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STO_TextFree  FALSE
	#define EXP_STO_TextFree  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_TextFree
	#define EXT_STO_TextFree
	#define GET_STO_TextFree(fl)  CAL_CMGETAPI( "STO_TextFree" ) 
	#define CAL_STO_TextFree  STO_TextFree
	#define CHK_STO_TextFree  TRUE
	#define EXP_STO_TextFree  CAL_CMEXPAPI( "STO_TextFree" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_TextFree
	#define EXT_STO_TextFree
	#define GET_STO_TextFree(fl)  CAL_CMGETAPI( "STO_TextFree" ) 
	#define CAL_STO_TextFree  STO_TextFree
	#define CHK_STO_TextFree  TRUE
	#define EXP_STO_TextFree  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_TextFree", (RTS_UINTPTR)STO_TextFree, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_TextFree
	#define EXT_CmpCAAStorageSTO_TextFree
	#define GET_CmpCAAStorageSTO_TextFree  ERR_OK
	#define CAL_CmpCAAStorageSTO_TextFree pICmpCAAStorage->ISTO_TextFree
	#define CHK_CmpCAAStorageSTO_TextFree (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_TextFree  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_TextFree
	#define EXT_STO_TextFree
	#define GET_STO_TextFree(fl)  CAL_CMGETAPI( "STO_TextFree" ) 
	#define CAL_STO_TextFree pICmpCAAStorage->ISTO_TextFree
	#define CHK_STO_TextFree (pICmpCAAStorage != NULL)
	#define EXP_STO_TextFree  CAL_CMEXPAPI( "STO_TextFree" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_TextFree  PFSTO_TEXTFREE pfSTO_TextFree;
	#define EXT_STO_TextFree  extern PFSTO_TEXTFREE pfSTO_TextFree;
	#define GET_STO_TextFree(fl)  s_pfCMGetAPI2( "STO_TextFree", (RTS_VOID_FCTPTR *)&pfSTO_TextFree, (fl), 0, 0)
	#define CAL_STO_TextFree  pfSTO_TextFree
	#define CHK_STO_TextFree  (pfSTO_TextFree != NULL)
	#define EXP_STO_TextFree  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_TextFree", (RTS_UINTPTR)STO_TextFree, 0, 0) 
#endif




CAA_WORD CDECL STO_GetSupplierVersion(CAA_BOOL xDummy);
typedef CAA_WORD (CDECL * PFSTO_GETSUPPLIERVERSION) (CAA_BOOL xDummy);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STO_GETSUPPLIERVERSION_NOTIMPLEMENTED)
	#define USE_STO_GetSupplierVersion
	#define EXT_STO_GetSupplierVersion
	#define GET_STO_GetSupplierVersion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STO_GetSupplierVersion(p0)  (CAA_WORD)ERR_NOTIMPLEMENTED
	#define CHK_STO_GetSupplierVersion  FALSE
	#define EXP_STO_GetSupplierVersion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STO_GetSupplierVersion
	#define EXT_STO_GetSupplierVersion
	#define GET_STO_GetSupplierVersion(fl)  CAL_CMGETAPI( "STO_GetSupplierVersion" ) 
	#define CAL_STO_GetSupplierVersion  STO_GetSupplierVersion
	#define CHK_STO_GetSupplierVersion  TRUE
	#define EXP_STO_GetSupplierVersion  CAL_CMEXPAPI( "STO_GetSupplierVersion" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STO_GetSupplierVersion
	#define EXT_STO_GetSupplierVersion
	#define GET_STO_GetSupplierVersion(fl)  CAL_CMGETAPI( "STO_GetSupplierVersion" ) 
	#define CAL_STO_GetSupplierVersion  STO_GetSupplierVersion
	#define CHK_STO_GetSupplierVersion  TRUE
	#define EXP_STO_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_GetSupplierVersion", (RTS_UINTPTR)STO_GetSupplierVersion, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTO_GetSupplierVersion
	#define EXT_CmpCAAStorageSTO_GetSupplierVersion
	#define GET_CmpCAAStorageSTO_GetSupplierVersion  ERR_OK
	#define CAL_CmpCAAStorageSTO_GetSupplierVersion pICmpCAAStorage->ISTO_GetSupplierVersion
	#define CHK_CmpCAAStorageSTO_GetSupplierVersion (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTO_GetSupplierVersion  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STO_GetSupplierVersion
	#define EXT_STO_GetSupplierVersion
	#define GET_STO_GetSupplierVersion(fl)  CAL_CMGETAPI( "STO_GetSupplierVersion" ) 
	#define CAL_STO_GetSupplierVersion pICmpCAAStorage->ISTO_GetSupplierVersion
	#define CHK_STO_GetSupplierVersion (pICmpCAAStorage != NULL)
	#define EXP_STO_GetSupplierVersion  CAL_CMEXPAPI( "STO_GetSupplierVersion" ) 
#else /* DYNAMIC_LINK */
	#define USE_STO_GetSupplierVersion  PFSTO_GETSUPPLIERVERSION pfSTO_GetSupplierVersion;
	#define EXT_STO_GetSupplierVersion  extern PFSTO_GETSUPPLIERVERSION pfSTO_GetSupplierVersion;
	#define GET_STO_GetSupplierVersion(fl)  s_pfCMGetAPI2( "STO_GetSupplierVersion", (RTS_VOID_FCTPTR *)&pfSTO_GetSupplierVersion, (fl), 0, 0)
	#define CAL_STO_GetSupplierVersion  pfSTO_GetSupplierVersion
	#define CHK_STO_GetSupplierVersion  (pfSTO_GetSupplierVersion != NULL)
	#define EXP_STO_GetSupplierVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STO_GetSupplierVersion", (RTS_UINTPTR)STO_GetSupplierVersion, 0, 0) 
#endif




STO_ERROR CDECL STI_ColumnGetBLOB(STI_ROW hRow, CAA_IDENT idColumn, STO_BLOB *pblobValue, CAA_BOOL *pxNULL);
typedef STO_ERROR (CDECL * PFSTI_COLUMNGETBLOB) (STI_ROW hRow, CAA_IDENT idColumn, STO_BLOB *pblobValue, CAA_BOOL *pxNULL);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNGETBLOB_NOTIMPLEMENTED)
	#define USE_STI_ColumnGetBLOB
	#define EXT_STI_ColumnGetBLOB
	#define GET_STI_ColumnGetBLOB(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnGetBLOB(p0,p1,p2,p3)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnGetBLOB  FALSE
	#define EXP_STI_ColumnGetBLOB  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnGetBLOB
	#define EXT_STI_ColumnGetBLOB
	#define GET_STI_ColumnGetBLOB(fl)  CAL_CMGETAPI( "STI_ColumnGetBLOB" ) 
	#define CAL_STI_ColumnGetBLOB  STI_ColumnGetBLOB
	#define CHK_STI_ColumnGetBLOB  TRUE
	#define EXP_STI_ColumnGetBLOB  CAL_CMEXPAPI( "STI_ColumnGetBLOB" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnGetBLOB
	#define EXT_STI_ColumnGetBLOB
	#define GET_STI_ColumnGetBLOB(fl)  CAL_CMGETAPI( "STI_ColumnGetBLOB" ) 
	#define CAL_STI_ColumnGetBLOB  STI_ColumnGetBLOB
	#define CHK_STI_ColumnGetBLOB  TRUE
	#define EXP_STI_ColumnGetBLOB  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnGetBLOB", (RTS_UINTPTR)STI_ColumnGetBLOB, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnGetBLOB
	#define EXT_CmpCAAStorageSTI_ColumnGetBLOB
	#define GET_CmpCAAStorageSTI_ColumnGetBLOB  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnGetBLOB pICmpCAAStorage->ISTI_ColumnGetBLOB
	#define CHK_CmpCAAStorageSTI_ColumnGetBLOB (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnGetBLOB  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnGetBLOB
	#define EXT_STI_ColumnGetBLOB
	#define GET_STI_ColumnGetBLOB(fl)  CAL_CMGETAPI( "STI_ColumnGetBLOB" ) 
	#define CAL_STI_ColumnGetBLOB pICmpCAAStorage->ISTI_ColumnGetBLOB
	#define CHK_STI_ColumnGetBLOB (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnGetBLOB  CAL_CMEXPAPI( "STI_ColumnGetBLOB" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnGetBLOB  PFSTI_COLUMNGETBLOB pfSTI_ColumnGetBLOB;
	#define EXT_STI_ColumnGetBLOB  extern PFSTI_COLUMNGETBLOB pfSTI_ColumnGetBLOB;
	#define GET_STI_ColumnGetBLOB(fl)  s_pfCMGetAPI2( "STI_ColumnGetBLOB", (RTS_VOID_FCTPTR *)&pfSTI_ColumnGetBLOB, (fl), 0, 0)
	#define CAL_STI_ColumnGetBLOB  pfSTI_ColumnGetBLOB
	#define CHK_STI_ColumnGetBLOB  (pfSTI_ColumnGetBLOB != NULL)
	#define EXP_STI_ColumnGetBLOB  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnGetBLOB", (RTS_UINTPTR)STI_ColumnGetBLOB, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnGetINT16(STI_ROW hRow, CAA_IDENT idColumn, CAA_INT *piValue, CAA_BOOL *pxNULL);
typedef STO_ERROR (CDECL * PFSTI_COLUMNGETINT16) (STI_ROW hRow, CAA_IDENT idColumn, CAA_INT *piValue, CAA_BOOL *pxNULL);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNGETINT16_NOTIMPLEMENTED)
	#define USE_STI_ColumnGetINT16
	#define EXT_STI_ColumnGetINT16
	#define GET_STI_ColumnGetINT16(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnGetINT16(p0,p1,p2,p3)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnGetINT16  FALSE
	#define EXP_STI_ColumnGetINT16  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnGetINT16
	#define EXT_STI_ColumnGetINT16
	#define GET_STI_ColumnGetINT16(fl)  CAL_CMGETAPI( "STI_ColumnGetINT16" ) 
	#define CAL_STI_ColumnGetINT16  STI_ColumnGetINT16
	#define CHK_STI_ColumnGetINT16  TRUE
	#define EXP_STI_ColumnGetINT16  CAL_CMEXPAPI( "STI_ColumnGetINT16" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnGetINT16
	#define EXT_STI_ColumnGetINT16
	#define GET_STI_ColumnGetINT16(fl)  CAL_CMGETAPI( "STI_ColumnGetINT16" ) 
	#define CAL_STI_ColumnGetINT16  STI_ColumnGetINT16
	#define CHK_STI_ColumnGetINT16  TRUE
	#define EXP_STI_ColumnGetINT16  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnGetINT16", (RTS_UINTPTR)STI_ColumnGetINT16, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnGetINT16
	#define EXT_CmpCAAStorageSTI_ColumnGetINT16
	#define GET_CmpCAAStorageSTI_ColumnGetINT16  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnGetINT16 pICmpCAAStorage->ISTI_ColumnGetINT16
	#define CHK_CmpCAAStorageSTI_ColumnGetINT16 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnGetINT16  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnGetINT16
	#define EXT_STI_ColumnGetINT16
	#define GET_STI_ColumnGetINT16(fl)  CAL_CMGETAPI( "STI_ColumnGetINT16" ) 
	#define CAL_STI_ColumnGetINT16 pICmpCAAStorage->ISTI_ColumnGetINT16
	#define CHK_STI_ColumnGetINT16 (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnGetINT16  CAL_CMEXPAPI( "STI_ColumnGetINT16" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnGetINT16  PFSTI_COLUMNGETINT16 pfSTI_ColumnGetINT16;
	#define EXT_STI_ColumnGetINT16  extern PFSTI_COLUMNGETINT16 pfSTI_ColumnGetINT16;
	#define GET_STI_ColumnGetINT16(fl)  s_pfCMGetAPI2( "STI_ColumnGetINT16", (RTS_VOID_FCTPTR *)&pfSTI_ColumnGetINT16, (fl), 0, 0)
	#define CAL_STI_ColumnGetINT16  pfSTI_ColumnGetINT16
	#define CHK_STI_ColumnGetINT16  (pfSTI_ColumnGetINT16 != NULL)
	#define EXP_STI_ColumnGetINT16  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnGetINT16", (RTS_UINTPTR)STI_ColumnGetINT16, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnGetINT32(STI_ROW hRow, CAA_IDENT idColumn, CAA_DINT *pdiValue, CAA_BOOL *pxNULL);
typedef STO_ERROR (CDECL * PFSTI_COLUMNGETINT32) (STI_ROW hRow, CAA_IDENT idColumn, CAA_DINT *pdiValue, CAA_BOOL *pxNULL);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNGETINT32_NOTIMPLEMENTED)
	#define USE_STI_ColumnGetINT32
	#define EXT_STI_ColumnGetINT32
	#define GET_STI_ColumnGetINT32(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnGetINT32(p0,p1,p2,p3)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnGetINT32  FALSE
	#define EXP_STI_ColumnGetINT32  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnGetINT32
	#define EXT_STI_ColumnGetINT32
	#define GET_STI_ColumnGetINT32(fl)  CAL_CMGETAPI( "STI_ColumnGetINT32" ) 
	#define CAL_STI_ColumnGetINT32  STI_ColumnGetINT32
	#define CHK_STI_ColumnGetINT32  TRUE
	#define EXP_STI_ColumnGetINT32  CAL_CMEXPAPI( "STI_ColumnGetINT32" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnGetINT32
	#define EXT_STI_ColumnGetINT32
	#define GET_STI_ColumnGetINT32(fl)  CAL_CMGETAPI( "STI_ColumnGetINT32" ) 
	#define CAL_STI_ColumnGetINT32  STI_ColumnGetINT32
	#define CHK_STI_ColumnGetINT32  TRUE
	#define EXP_STI_ColumnGetINT32  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnGetINT32", (RTS_UINTPTR)STI_ColumnGetINT32, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnGetINT32
	#define EXT_CmpCAAStorageSTI_ColumnGetINT32
	#define GET_CmpCAAStorageSTI_ColumnGetINT32  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnGetINT32 pICmpCAAStorage->ISTI_ColumnGetINT32
	#define CHK_CmpCAAStorageSTI_ColumnGetINT32 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnGetINT32  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnGetINT32
	#define EXT_STI_ColumnGetINT32
	#define GET_STI_ColumnGetINT32(fl)  CAL_CMGETAPI( "STI_ColumnGetINT32" ) 
	#define CAL_STI_ColumnGetINT32 pICmpCAAStorage->ISTI_ColumnGetINT32
	#define CHK_STI_ColumnGetINT32 (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnGetINT32  CAL_CMEXPAPI( "STI_ColumnGetINT32" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnGetINT32  PFSTI_COLUMNGETINT32 pfSTI_ColumnGetINT32;
	#define EXT_STI_ColumnGetINT32  extern PFSTI_COLUMNGETINT32 pfSTI_ColumnGetINT32;
	#define GET_STI_ColumnGetINT32(fl)  s_pfCMGetAPI2( "STI_ColumnGetINT32", (RTS_VOID_FCTPTR *)&pfSTI_ColumnGetINT32, (fl), 0, 0)
	#define CAL_STI_ColumnGetINT32  pfSTI_ColumnGetINT32
	#define CHK_STI_ColumnGetINT32  (pfSTI_ColumnGetINT32 != NULL)
	#define EXP_STI_ColumnGetINT32  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnGetINT32", (RTS_UINTPTR)STI_ColumnGetINT32, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnGetINT64(STI_ROW hRow, CAA_IDENT idColumn, CAA_LINT *pliValue, CAA_BOOL *pxNULL);
typedef STO_ERROR (CDECL * PFSTI_COLUMNGETINT64) (STI_ROW hRow, CAA_IDENT idColumn, CAA_LINT *pliValue, CAA_BOOL *pxNULL);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNGETINT64_NOTIMPLEMENTED)
	#define USE_STI_ColumnGetINT64
	#define EXT_STI_ColumnGetINT64
	#define GET_STI_ColumnGetINT64(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnGetINT64(p0,p1,p2,p3)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnGetINT64  FALSE
	#define EXP_STI_ColumnGetINT64  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnGetINT64
	#define EXT_STI_ColumnGetINT64
	#define GET_STI_ColumnGetINT64(fl)  CAL_CMGETAPI( "STI_ColumnGetINT64" ) 
	#define CAL_STI_ColumnGetINT64  STI_ColumnGetINT64
	#define CHK_STI_ColumnGetINT64  TRUE
	#define EXP_STI_ColumnGetINT64  CAL_CMEXPAPI( "STI_ColumnGetINT64" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnGetINT64
	#define EXT_STI_ColumnGetINT64
	#define GET_STI_ColumnGetINT64(fl)  CAL_CMGETAPI( "STI_ColumnGetINT64" ) 
	#define CAL_STI_ColumnGetINT64  STI_ColumnGetINT64
	#define CHK_STI_ColumnGetINT64  TRUE
	#define EXP_STI_ColumnGetINT64  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnGetINT64", (RTS_UINTPTR)STI_ColumnGetINT64, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnGetINT64
	#define EXT_CmpCAAStorageSTI_ColumnGetINT64
	#define GET_CmpCAAStorageSTI_ColumnGetINT64  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnGetINT64 pICmpCAAStorage->ISTI_ColumnGetINT64
	#define CHK_CmpCAAStorageSTI_ColumnGetINT64 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnGetINT64  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnGetINT64
	#define EXT_STI_ColumnGetINT64
	#define GET_STI_ColumnGetINT64(fl)  CAL_CMGETAPI( "STI_ColumnGetINT64" ) 
	#define CAL_STI_ColumnGetINT64 pICmpCAAStorage->ISTI_ColumnGetINT64
	#define CHK_STI_ColumnGetINT64 (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnGetINT64  CAL_CMEXPAPI( "STI_ColumnGetINT64" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnGetINT64  PFSTI_COLUMNGETINT64 pfSTI_ColumnGetINT64;
	#define EXT_STI_ColumnGetINT64  extern PFSTI_COLUMNGETINT64 pfSTI_ColumnGetINT64;
	#define GET_STI_ColumnGetINT64(fl)  s_pfCMGetAPI2( "STI_ColumnGetINT64", (RTS_VOID_FCTPTR *)&pfSTI_ColumnGetINT64, (fl), 0, 0)
	#define CAL_STI_ColumnGetINT64  pfSTI_ColumnGetINT64
	#define CHK_STI_ColumnGetINT64  (pfSTI_ColumnGetINT64 != NULL)
	#define EXP_STI_ColumnGetINT64  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnGetINT64", (RTS_UINTPTR)STI_ColumnGetINT64, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnGetINT8(STI_ROW hRow, CAA_IDENT idColumn, CAA_SINT *psiValue, CAA_BOOL *pxNULL);
typedef STO_ERROR (CDECL * PFSTI_COLUMNGETINT8) (STI_ROW hRow, CAA_IDENT idColumn, CAA_SINT *psiValue, CAA_BOOL *pxNULL);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNGETINT8_NOTIMPLEMENTED)
	#define USE_STI_ColumnGetINT8
	#define EXT_STI_ColumnGetINT8
	#define GET_STI_ColumnGetINT8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnGetINT8(p0,p1,p2,p3)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnGetINT8  FALSE
	#define EXP_STI_ColumnGetINT8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnGetINT8
	#define EXT_STI_ColumnGetINT8
	#define GET_STI_ColumnGetINT8(fl)  CAL_CMGETAPI( "STI_ColumnGetINT8" ) 
	#define CAL_STI_ColumnGetINT8  STI_ColumnGetINT8
	#define CHK_STI_ColumnGetINT8  TRUE
	#define EXP_STI_ColumnGetINT8  CAL_CMEXPAPI( "STI_ColumnGetINT8" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnGetINT8
	#define EXT_STI_ColumnGetINT8
	#define GET_STI_ColumnGetINT8(fl)  CAL_CMGETAPI( "STI_ColumnGetINT8" ) 
	#define CAL_STI_ColumnGetINT8  STI_ColumnGetINT8
	#define CHK_STI_ColumnGetINT8  TRUE
	#define EXP_STI_ColumnGetINT8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnGetINT8", (RTS_UINTPTR)STI_ColumnGetINT8, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnGetINT8
	#define EXT_CmpCAAStorageSTI_ColumnGetINT8
	#define GET_CmpCAAStorageSTI_ColumnGetINT8  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnGetINT8 pICmpCAAStorage->ISTI_ColumnGetINT8
	#define CHK_CmpCAAStorageSTI_ColumnGetINT8 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnGetINT8  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnGetINT8
	#define EXT_STI_ColumnGetINT8
	#define GET_STI_ColumnGetINT8(fl)  CAL_CMGETAPI( "STI_ColumnGetINT8" ) 
	#define CAL_STI_ColumnGetINT8 pICmpCAAStorage->ISTI_ColumnGetINT8
	#define CHK_STI_ColumnGetINT8 (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnGetINT8  CAL_CMEXPAPI( "STI_ColumnGetINT8" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnGetINT8  PFSTI_COLUMNGETINT8 pfSTI_ColumnGetINT8;
	#define EXT_STI_ColumnGetINT8  extern PFSTI_COLUMNGETINT8 pfSTI_ColumnGetINT8;
	#define GET_STI_ColumnGetINT8(fl)  s_pfCMGetAPI2( "STI_ColumnGetINT8", (RTS_VOID_FCTPTR *)&pfSTI_ColumnGetINT8, (fl), 0, 0)
	#define CAL_STI_ColumnGetINT8  pfSTI_ColumnGetINT8
	#define CHK_STI_ColumnGetINT8  (pfSTI_ColumnGetINT8 != NULL)
	#define EXP_STI_ColumnGetINT8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnGetINT8", (RTS_UINTPTR)STI_ColumnGetINT8, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnGetREAL4(STI_ROW hRow, CAA_IDENT idColumn, CAA_REAL *prValue, CAA_BOOL *pxNULL);
typedef STO_ERROR (CDECL * PFSTI_COLUMNGETREAL4) (STI_ROW hRow, CAA_IDENT idColumn, CAA_REAL *prValue, CAA_BOOL *pxNULL);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNGETREAL4_NOTIMPLEMENTED)
	#define USE_STI_ColumnGetREAL4
	#define EXT_STI_ColumnGetREAL4
	#define GET_STI_ColumnGetREAL4(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnGetREAL4(p0,p1,p2,p3)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnGetREAL4  FALSE
	#define EXP_STI_ColumnGetREAL4  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnGetREAL4
	#define EXT_STI_ColumnGetREAL4
	#define GET_STI_ColumnGetREAL4(fl)  CAL_CMGETAPI( "STI_ColumnGetREAL4" ) 
	#define CAL_STI_ColumnGetREAL4  STI_ColumnGetREAL4
	#define CHK_STI_ColumnGetREAL4  TRUE
	#define EXP_STI_ColumnGetREAL4  CAL_CMEXPAPI( "STI_ColumnGetREAL4" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnGetREAL4
	#define EXT_STI_ColumnGetREAL4
	#define GET_STI_ColumnGetREAL4(fl)  CAL_CMGETAPI( "STI_ColumnGetREAL4" ) 
	#define CAL_STI_ColumnGetREAL4  STI_ColumnGetREAL4
	#define CHK_STI_ColumnGetREAL4  TRUE
	#define EXP_STI_ColumnGetREAL4  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnGetREAL4", (RTS_UINTPTR)STI_ColumnGetREAL4, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnGetREAL4
	#define EXT_CmpCAAStorageSTI_ColumnGetREAL4
	#define GET_CmpCAAStorageSTI_ColumnGetREAL4  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnGetREAL4 pICmpCAAStorage->ISTI_ColumnGetREAL4
	#define CHK_CmpCAAStorageSTI_ColumnGetREAL4 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnGetREAL4  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnGetREAL4
	#define EXT_STI_ColumnGetREAL4
	#define GET_STI_ColumnGetREAL4(fl)  CAL_CMGETAPI( "STI_ColumnGetREAL4" ) 
	#define CAL_STI_ColumnGetREAL4 pICmpCAAStorage->ISTI_ColumnGetREAL4
	#define CHK_STI_ColumnGetREAL4 (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnGetREAL4  CAL_CMEXPAPI( "STI_ColumnGetREAL4" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnGetREAL4  PFSTI_COLUMNGETREAL4 pfSTI_ColumnGetREAL4;
	#define EXT_STI_ColumnGetREAL4  extern PFSTI_COLUMNGETREAL4 pfSTI_ColumnGetREAL4;
	#define GET_STI_ColumnGetREAL4(fl)  s_pfCMGetAPI2( "STI_ColumnGetREAL4", (RTS_VOID_FCTPTR *)&pfSTI_ColumnGetREAL4, (fl), 0, 0)
	#define CAL_STI_ColumnGetREAL4  pfSTI_ColumnGetREAL4
	#define CHK_STI_ColumnGetREAL4  (pfSTI_ColumnGetREAL4 != NULL)
	#define EXP_STI_ColumnGetREAL4  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnGetREAL4", (RTS_UINTPTR)STI_ColumnGetREAL4, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnGetREAL8(STI_ROW hRow, CAA_IDENT idColumn, CAA_LREAL *plrValue, CAA_BOOL *pxNULL);
typedef STO_ERROR (CDECL * PFSTI_COLUMNGETREAL8) (STI_ROW hRow, CAA_IDENT idColumn, CAA_LREAL *plrValue, CAA_BOOL *pxNULL);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNGETREAL8_NOTIMPLEMENTED)
	#define USE_STI_ColumnGetREAL8
	#define EXT_STI_ColumnGetREAL8
	#define GET_STI_ColumnGetREAL8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnGetREAL8(p0,p1,p2,p3)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnGetREAL8  FALSE
	#define EXP_STI_ColumnGetREAL8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnGetREAL8
	#define EXT_STI_ColumnGetREAL8
	#define GET_STI_ColumnGetREAL8(fl)  CAL_CMGETAPI( "STI_ColumnGetREAL8" ) 
	#define CAL_STI_ColumnGetREAL8  STI_ColumnGetREAL8
	#define CHK_STI_ColumnGetREAL8  TRUE
	#define EXP_STI_ColumnGetREAL8  CAL_CMEXPAPI( "STI_ColumnGetREAL8" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnGetREAL8
	#define EXT_STI_ColumnGetREAL8
	#define GET_STI_ColumnGetREAL8(fl)  CAL_CMGETAPI( "STI_ColumnGetREAL8" ) 
	#define CAL_STI_ColumnGetREAL8  STI_ColumnGetREAL8
	#define CHK_STI_ColumnGetREAL8  TRUE
	#define EXP_STI_ColumnGetREAL8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnGetREAL8", (RTS_UINTPTR)STI_ColumnGetREAL8, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnGetREAL8
	#define EXT_CmpCAAStorageSTI_ColumnGetREAL8
	#define GET_CmpCAAStorageSTI_ColumnGetREAL8  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnGetREAL8 pICmpCAAStorage->ISTI_ColumnGetREAL8
	#define CHK_CmpCAAStorageSTI_ColumnGetREAL8 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnGetREAL8  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnGetREAL8
	#define EXT_STI_ColumnGetREAL8
	#define GET_STI_ColumnGetREAL8(fl)  CAL_CMGETAPI( "STI_ColumnGetREAL8" ) 
	#define CAL_STI_ColumnGetREAL8 pICmpCAAStorage->ISTI_ColumnGetREAL8
	#define CHK_STI_ColumnGetREAL8 (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnGetREAL8  CAL_CMEXPAPI( "STI_ColumnGetREAL8" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnGetREAL8  PFSTI_COLUMNGETREAL8 pfSTI_ColumnGetREAL8;
	#define EXT_STI_ColumnGetREAL8  extern PFSTI_COLUMNGETREAL8 pfSTI_ColumnGetREAL8;
	#define GET_STI_ColumnGetREAL8(fl)  s_pfCMGetAPI2( "STI_ColumnGetREAL8", (RTS_VOID_FCTPTR *)&pfSTI_ColumnGetREAL8, (fl), 0, 0)
	#define CAL_STI_ColumnGetREAL8  pfSTI_ColumnGetREAL8
	#define CHK_STI_ColumnGetREAL8  (pfSTI_ColumnGetREAL8 != NULL)
	#define EXP_STI_ColumnGetREAL8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnGetREAL8", (RTS_UINTPTR)STI_ColumnGetREAL8, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnGetTEXT(STI_ROW hRow, CAA_IDENT idColumn, STO_TEXT *ptxtValue, CAA_BOOL *pxNULL);
typedef STO_ERROR (CDECL * PFSTI_COLUMNGETTEXT) (STI_ROW hRow, CAA_IDENT idColumn, STO_TEXT *ptxtValue, CAA_BOOL *pxNULL);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNGETTEXT_NOTIMPLEMENTED)
	#define USE_STI_ColumnGetTEXT
	#define EXT_STI_ColumnGetTEXT
	#define GET_STI_ColumnGetTEXT(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnGetTEXT(p0,p1,p2,p3)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnGetTEXT  FALSE
	#define EXP_STI_ColumnGetTEXT  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnGetTEXT
	#define EXT_STI_ColumnGetTEXT
	#define GET_STI_ColumnGetTEXT(fl)  CAL_CMGETAPI( "STI_ColumnGetTEXT" ) 
	#define CAL_STI_ColumnGetTEXT  STI_ColumnGetTEXT
	#define CHK_STI_ColumnGetTEXT  TRUE
	#define EXP_STI_ColumnGetTEXT  CAL_CMEXPAPI( "STI_ColumnGetTEXT" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnGetTEXT
	#define EXT_STI_ColumnGetTEXT
	#define GET_STI_ColumnGetTEXT(fl)  CAL_CMGETAPI( "STI_ColumnGetTEXT" ) 
	#define CAL_STI_ColumnGetTEXT  STI_ColumnGetTEXT
	#define CHK_STI_ColumnGetTEXT  TRUE
	#define EXP_STI_ColumnGetTEXT  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnGetTEXT", (RTS_UINTPTR)STI_ColumnGetTEXT, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnGetTEXT
	#define EXT_CmpCAAStorageSTI_ColumnGetTEXT
	#define GET_CmpCAAStorageSTI_ColumnGetTEXT  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnGetTEXT pICmpCAAStorage->ISTI_ColumnGetTEXT
	#define CHK_CmpCAAStorageSTI_ColumnGetTEXT (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnGetTEXT  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnGetTEXT
	#define EXT_STI_ColumnGetTEXT
	#define GET_STI_ColumnGetTEXT(fl)  CAL_CMGETAPI( "STI_ColumnGetTEXT" ) 
	#define CAL_STI_ColumnGetTEXT pICmpCAAStorage->ISTI_ColumnGetTEXT
	#define CHK_STI_ColumnGetTEXT (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnGetTEXT  CAL_CMEXPAPI( "STI_ColumnGetTEXT" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnGetTEXT  PFSTI_COLUMNGETTEXT pfSTI_ColumnGetTEXT;
	#define EXT_STI_ColumnGetTEXT  extern PFSTI_COLUMNGETTEXT pfSTI_ColumnGetTEXT;
	#define GET_STI_ColumnGetTEXT(fl)  s_pfCMGetAPI2( "STI_ColumnGetTEXT", (RTS_VOID_FCTPTR *)&pfSTI_ColumnGetTEXT, (fl), 0, 0)
	#define CAL_STI_ColumnGetTEXT  pfSTI_ColumnGetTEXT
	#define CHK_STI_ColumnGetTEXT  (pfSTI_ColumnGetTEXT != NULL)
	#define EXP_STI_ColumnGetTEXT  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnGetTEXT", (RTS_UINTPTR)STI_ColumnGetTEXT, 0, 0) 
#endif



STO_COLUMN_TYPE CDECL STI_ColumnGetType(STI_ROW hRow, CAA_IDENT idColumn, STO_ERROR *peError);
typedef STO_COLUMN_TYPE (CDECL * PFSTI_COLUMNGETTYPE) (STI_ROW hRow, CAA_IDENT idColumn, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNGETTYPE_NOTIMPLEMENTED)
	#define USE_STI_ColumnGetType
	#define EXT_STI_ColumnGetType
	#define GET_STI_ColumnGetType(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnGetType(p0,p1,p2)  (STO_COLUMN_TYPE)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnGetType  FALSE
	#define EXP_STI_ColumnGetType  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnGetType
	#define EXT_STI_ColumnGetType
	#define GET_STI_ColumnGetType(fl)  CAL_CMGETAPI( "STI_ColumnGetType" ) 
	#define CAL_STI_ColumnGetType  STI_ColumnGetType
	#define CHK_STI_ColumnGetType  TRUE
	#define EXP_STI_ColumnGetType  CAL_CMEXPAPI( "STI_ColumnGetType" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnGetType
	#define EXT_STI_ColumnGetType
	#define GET_STI_ColumnGetType(fl)  CAL_CMGETAPI( "STI_ColumnGetType" ) 
	#define CAL_STI_ColumnGetType  STI_ColumnGetType
	#define CHK_STI_ColumnGetType  TRUE
	#define EXP_STI_ColumnGetType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnGetType", (RTS_UINTPTR)STI_ColumnGetType, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnGetType
	#define EXT_CmpCAAStorageSTI_ColumnGetType
	#define GET_CmpCAAStorageSTI_ColumnGetType  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnGetType pICmpCAAStorage->ISTI_ColumnGetType
	#define CHK_CmpCAAStorageSTI_ColumnGetType (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnGetType  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnGetType
	#define EXT_STI_ColumnGetType
	#define GET_STI_ColumnGetType(fl)  CAL_CMGETAPI( "STI_ColumnGetType" ) 
	#define CAL_STI_ColumnGetType pICmpCAAStorage->ISTI_ColumnGetType
	#define CHK_STI_ColumnGetType (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnGetType  CAL_CMEXPAPI( "STI_ColumnGetType" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnGetType  PFSTI_COLUMNGETTYPE pfSTI_ColumnGetType;
	#define EXT_STI_ColumnGetType  extern PFSTI_COLUMNGETTYPE pfSTI_ColumnGetType;
	#define GET_STI_ColumnGetType(fl)  s_pfCMGetAPI2( "STI_ColumnGetType", (RTS_VOID_FCTPTR *)&pfSTI_ColumnGetType, (fl), 0, 0)
	#define CAL_STI_ColumnGetType  pfSTI_ColumnGetType
	#define CHK_STI_ColumnGetType  (pfSTI_ColumnGetType != NULL)
	#define EXP_STI_ColumnGetType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnGetType", (RTS_UINTPTR)STI_ColumnGetType, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnSetBLOB(STI_ROW hRow, CAA_IDENT idColumn, STO_BLOB *pblobValue);
typedef STO_ERROR (CDECL * PFSTI_COLUMNSETBLOB) (STI_ROW hRow, CAA_IDENT idColumn, STO_BLOB *pblobValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNSETBLOB_NOTIMPLEMENTED)
	#define USE_STI_ColumnSetBLOB
	#define EXT_STI_ColumnSetBLOB
	#define GET_STI_ColumnSetBLOB(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnSetBLOB(p0,p1,p2)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnSetBLOB  FALSE
	#define EXP_STI_ColumnSetBLOB  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnSetBLOB
	#define EXT_STI_ColumnSetBLOB
	#define GET_STI_ColumnSetBLOB(fl)  CAL_CMGETAPI( "STI_ColumnSetBLOB" ) 
	#define CAL_STI_ColumnSetBLOB  STI_ColumnSetBLOB
	#define CHK_STI_ColumnSetBLOB  TRUE
	#define EXP_STI_ColumnSetBLOB  CAL_CMEXPAPI( "STI_ColumnSetBLOB" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnSetBLOB
	#define EXT_STI_ColumnSetBLOB
	#define GET_STI_ColumnSetBLOB(fl)  CAL_CMGETAPI( "STI_ColumnSetBLOB" ) 
	#define CAL_STI_ColumnSetBLOB  STI_ColumnSetBLOB
	#define CHK_STI_ColumnSetBLOB  TRUE
	#define EXP_STI_ColumnSetBLOB  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnSetBLOB", (RTS_UINTPTR)STI_ColumnSetBLOB, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnSetBLOB
	#define EXT_CmpCAAStorageSTI_ColumnSetBLOB
	#define GET_CmpCAAStorageSTI_ColumnSetBLOB  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnSetBLOB pICmpCAAStorage->ISTI_ColumnSetBLOB
	#define CHK_CmpCAAStorageSTI_ColumnSetBLOB (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnSetBLOB  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnSetBLOB
	#define EXT_STI_ColumnSetBLOB
	#define GET_STI_ColumnSetBLOB(fl)  CAL_CMGETAPI( "STI_ColumnSetBLOB" ) 
	#define CAL_STI_ColumnSetBLOB pICmpCAAStorage->ISTI_ColumnSetBLOB
	#define CHK_STI_ColumnSetBLOB (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnSetBLOB  CAL_CMEXPAPI( "STI_ColumnSetBLOB" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnSetBLOB  PFSTI_COLUMNSETBLOB pfSTI_ColumnSetBLOB;
	#define EXT_STI_ColumnSetBLOB  extern PFSTI_COLUMNSETBLOB pfSTI_ColumnSetBLOB;
	#define GET_STI_ColumnSetBLOB(fl)  s_pfCMGetAPI2( "STI_ColumnSetBLOB", (RTS_VOID_FCTPTR *)&pfSTI_ColumnSetBLOB, (fl), 0, 0)
	#define CAL_STI_ColumnSetBLOB  pfSTI_ColumnSetBLOB
	#define CHK_STI_ColumnSetBLOB  (pfSTI_ColumnSetBLOB != NULL)
	#define EXP_STI_ColumnSetBLOB  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnSetBLOB", (RTS_UINTPTR)STI_ColumnSetBLOB, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnSetINT16(STI_ROW hRow, CAA_IDENT idColumn, CAA_INT iValue);
typedef STO_ERROR (CDECL * PFSTI_COLUMNSETINT16) (STI_ROW hRow, CAA_IDENT idColumn, CAA_INT iValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNSETINT16_NOTIMPLEMENTED)
	#define USE_STI_ColumnSetINT16
	#define EXT_STI_ColumnSetINT16
	#define GET_STI_ColumnSetINT16(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnSetINT16(p0,p1,p2)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnSetINT16  FALSE
	#define EXP_STI_ColumnSetINT16  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnSetINT16
	#define EXT_STI_ColumnSetINT16
	#define GET_STI_ColumnSetINT16(fl)  CAL_CMGETAPI( "STI_ColumnSetINT16" ) 
	#define CAL_STI_ColumnSetINT16  STI_ColumnSetINT16
	#define CHK_STI_ColumnSetINT16  TRUE
	#define EXP_STI_ColumnSetINT16  CAL_CMEXPAPI( "STI_ColumnSetINT16" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnSetINT16
	#define EXT_STI_ColumnSetINT16
	#define GET_STI_ColumnSetINT16(fl)  CAL_CMGETAPI( "STI_ColumnSetINT16" ) 
	#define CAL_STI_ColumnSetINT16  STI_ColumnSetINT16
	#define CHK_STI_ColumnSetINT16  TRUE
	#define EXP_STI_ColumnSetINT16  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnSetINT16", (RTS_UINTPTR)STI_ColumnSetINT16, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnSetINT16
	#define EXT_CmpCAAStorageSTI_ColumnSetINT16
	#define GET_CmpCAAStorageSTI_ColumnSetINT16  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnSetINT16 pICmpCAAStorage->ISTI_ColumnSetINT16
	#define CHK_CmpCAAStorageSTI_ColumnSetINT16 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnSetINT16  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnSetINT16
	#define EXT_STI_ColumnSetINT16
	#define GET_STI_ColumnSetINT16(fl)  CAL_CMGETAPI( "STI_ColumnSetINT16" ) 
	#define CAL_STI_ColumnSetINT16 pICmpCAAStorage->ISTI_ColumnSetINT16
	#define CHK_STI_ColumnSetINT16 (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnSetINT16  CAL_CMEXPAPI( "STI_ColumnSetINT16" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnSetINT16  PFSTI_COLUMNSETINT16 pfSTI_ColumnSetINT16;
	#define EXT_STI_ColumnSetINT16  extern PFSTI_COLUMNSETINT16 pfSTI_ColumnSetINT16;
	#define GET_STI_ColumnSetINT16(fl)  s_pfCMGetAPI2( "STI_ColumnSetINT16", (RTS_VOID_FCTPTR *)&pfSTI_ColumnSetINT16, (fl), 0, 0)
	#define CAL_STI_ColumnSetINT16  pfSTI_ColumnSetINT16
	#define CHK_STI_ColumnSetINT16  (pfSTI_ColumnSetINT16 != NULL)
	#define EXP_STI_ColumnSetINT16  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnSetINT16", (RTS_UINTPTR)STI_ColumnSetINT16, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnSetINT32(STI_ROW hRow, CAA_IDENT idColumn, CAA_DINT diValue);
typedef STO_ERROR (CDECL * PFSTI_COLUMNSETINT32) (STI_ROW hRow, CAA_IDENT idColumn, CAA_DINT diValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNSETINT32_NOTIMPLEMENTED)
	#define USE_STI_ColumnSetINT32
	#define EXT_STI_ColumnSetINT32
	#define GET_STI_ColumnSetINT32(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnSetINT32(p0,p1,p2)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnSetINT32  FALSE
	#define EXP_STI_ColumnSetINT32  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnSetINT32
	#define EXT_STI_ColumnSetINT32
	#define GET_STI_ColumnSetINT32(fl)  CAL_CMGETAPI( "STI_ColumnSetINT32" ) 
	#define CAL_STI_ColumnSetINT32  STI_ColumnSetINT32
	#define CHK_STI_ColumnSetINT32  TRUE
	#define EXP_STI_ColumnSetINT32  CAL_CMEXPAPI( "STI_ColumnSetINT32" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnSetINT32
	#define EXT_STI_ColumnSetINT32
	#define GET_STI_ColumnSetINT32(fl)  CAL_CMGETAPI( "STI_ColumnSetINT32" ) 
	#define CAL_STI_ColumnSetINT32  STI_ColumnSetINT32
	#define CHK_STI_ColumnSetINT32  TRUE
	#define EXP_STI_ColumnSetINT32  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnSetINT32", (RTS_UINTPTR)STI_ColumnSetINT32, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnSetINT32
	#define EXT_CmpCAAStorageSTI_ColumnSetINT32
	#define GET_CmpCAAStorageSTI_ColumnSetINT32  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnSetINT32 pICmpCAAStorage->ISTI_ColumnSetINT32
	#define CHK_CmpCAAStorageSTI_ColumnSetINT32 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnSetINT32  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnSetINT32
	#define EXT_STI_ColumnSetINT32
	#define GET_STI_ColumnSetINT32(fl)  CAL_CMGETAPI( "STI_ColumnSetINT32" ) 
	#define CAL_STI_ColumnSetINT32 pICmpCAAStorage->ISTI_ColumnSetINT32
	#define CHK_STI_ColumnSetINT32 (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnSetINT32  CAL_CMEXPAPI( "STI_ColumnSetINT32" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnSetINT32  PFSTI_COLUMNSETINT32 pfSTI_ColumnSetINT32;
	#define EXT_STI_ColumnSetINT32  extern PFSTI_COLUMNSETINT32 pfSTI_ColumnSetINT32;
	#define GET_STI_ColumnSetINT32(fl)  s_pfCMGetAPI2( "STI_ColumnSetINT32", (RTS_VOID_FCTPTR *)&pfSTI_ColumnSetINT32, (fl), 0, 0)
	#define CAL_STI_ColumnSetINT32  pfSTI_ColumnSetINT32
	#define CHK_STI_ColumnSetINT32  (pfSTI_ColumnSetINT32 != NULL)
	#define EXP_STI_ColumnSetINT32  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnSetINT32", (RTS_UINTPTR)STI_ColumnSetINT32, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnSetINT64(STI_ROW hRow, CAA_IDENT idColumn, CAA_LINT liValue);
typedef STO_ERROR (CDECL * PFSTI_COLUMNSETINT64) (STI_ROW hRow, CAA_IDENT idColumn, CAA_LINT liValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNSETINT64_NOTIMPLEMENTED)
	#define USE_STI_ColumnSetINT64
	#define EXT_STI_ColumnSetINT64
	#define GET_STI_ColumnSetINT64(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnSetINT64(p0,p1,p2)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnSetINT64  FALSE
	#define EXP_STI_ColumnSetINT64  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnSetINT64
	#define EXT_STI_ColumnSetINT64
	#define GET_STI_ColumnSetINT64(fl)  CAL_CMGETAPI( "STI_ColumnSetINT64" ) 
	#define CAL_STI_ColumnSetINT64  STI_ColumnSetINT64
	#define CHK_STI_ColumnSetINT64  TRUE
	#define EXP_STI_ColumnSetINT64  CAL_CMEXPAPI( "STI_ColumnSetINT64" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnSetINT64
	#define EXT_STI_ColumnSetINT64
	#define GET_STI_ColumnSetINT64(fl)  CAL_CMGETAPI( "STI_ColumnSetINT64" ) 
	#define CAL_STI_ColumnSetINT64  STI_ColumnSetINT64
	#define CHK_STI_ColumnSetINT64  TRUE
	#define EXP_STI_ColumnSetINT64  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnSetINT64", (RTS_UINTPTR)STI_ColumnSetINT64, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnSetINT64
	#define EXT_CmpCAAStorageSTI_ColumnSetINT64
	#define GET_CmpCAAStorageSTI_ColumnSetINT64  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnSetINT64 pICmpCAAStorage->ISTI_ColumnSetINT64
	#define CHK_CmpCAAStorageSTI_ColumnSetINT64 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnSetINT64  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnSetINT64
	#define EXT_STI_ColumnSetINT64
	#define GET_STI_ColumnSetINT64(fl)  CAL_CMGETAPI( "STI_ColumnSetINT64" ) 
	#define CAL_STI_ColumnSetINT64 pICmpCAAStorage->ISTI_ColumnSetINT64
	#define CHK_STI_ColumnSetINT64 (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnSetINT64  CAL_CMEXPAPI( "STI_ColumnSetINT64" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnSetINT64  PFSTI_COLUMNSETINT64 pfSTI_ColumnSetINT64;
	#define EXT_STI_ColumnSetINT64  extern PFSTI_COLUMNSETINT64 pfSTI_ColumnSetINT64;
	#define GET_STI_ColumnSetINT64(fl)  s_pfCMGetAPI2( "STI_ColumnSetINT64", (RTS_VOID_FCTPTR *)&pfSTI_ColumnSetINT64, (fl), 0, 0)
	#define CAL_STI_ColumnSetINT64  pfSTI_ColumnSetINT64
	#define CHK_STI_ColumnSetINT64  (pfSTI_ColumnSetINT64 != NULL)
	#define EXP_STI_ColumnSetINT64  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnSetINT64", (RTS_UINTPTR)STI_ColumnSetINT64, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnSetINT8(STI_ROW hRow, CAA_IDENT idColumn, CAA_SINT siValue);
typedef STO_ERROR (CDECL * PFSTI_COLUMNSETINT8) (STI_ROW hRow, CAA_IDENT idColumn, CAA_SINT siValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNSETINT8_NOTIMPLEMENTED)
	#define USE_STI_ColumnSetINT8
	#define EXT_STI_ColumnSetINT8
	#define GET_STI_ColumnSetINT8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnSetINT8(p0,p1,p2)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnSetINT8  FALSE
	#define EXP_STI_ColumnSetINT8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnSetINT8
	#define EXT_STI_ColumnSetINT8
	#define GET_STI_ColumnSetINT8(fl)  CAL_CMGETAPI( "STI_ColumnSetINT8" ) 
	#define CAL_STI_ColumnSetINT8  STI_ColumnSetINT8
	#define CHK_STI_ColumnSetINT8  TRUE
	#define EXP_STI_ColumnSetINT8  CAL_CMEXPAPI( "STI_ColumnSetINT8" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnSetINT8
	#define EXT_STI_ColumnSetINT8
	#define GET_STI_ColumnSetINT8(fl)  CAL_CMGETAPI( "STI_ColumnSetINT8" ) 
	#define CAL_STI_ColumnSetINT8  STI_ColumnSetINT8
	#define CHK_STI_ColumnSetINT8  TRUE
	#define EXP_STI_ColumnSetINT8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnSetINT8", (RTS_UINTPTR)STI_ColumnSetINT8, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnSetINT8
	#define EXT_CmpCAAStorageSTI_ColumnSetINT8
	#define GET_CmpCAAStorageSTI_ColumnSetINT8  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnSetINT8 pICmpCAAStorage->ISTI_ColumnSetINT8
	#define CHK_CmpCAAStorageSTI_ColumnSetINT8 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnSetINT8  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnSetINT8
	#define EXT_STI_ColumnSetINT8
	#define GET_STI_ColumnSetINT8(fl)  CAL_CMGETAPI( "STI_ColumnSetINT8" ) 
	#define CAL_STI_ColumnSetINT8 pICmpCAAStorage->ISTI_ColumnSetINT8
	#define CHK_STI_ColumnSetINT8 (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnSetINT8  CAL_CMEXPAPI( "STI_ColumnSetINT8" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnSetINT8  PFSTI_COLUMNSETINT8 pfSTI_ColumnSetINT8;
	#define EXT_STI_ColumnSetINT8  extern PFSTI_COLUMNSETINT8 pfSTI_ColumnSetINT8;
	#define GET_STI_ColumnSetINT8(fl)  s_pfCMGetAPI2( "STI_ColumnSetINT8", (RTS_VOID_FCTPTR *)&pfSTI_ColumnSetINT8, (fl), 0, 0)
	#define CAL_STI_ColumnSetINT8  pfSTI_ColumnSetINT8
	#define CHK_STI_ColumnSetINT8  (pfSTI_ColumnSetINT8 != NULL)
	#define EXP_STI_ColumnSetINT8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnSetINT8", (RTS_UINTPTR)STI_ColumnSetINT8, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnSetNULL(STI_ROW hRow, CAA_IDENT idColumn);
typedef STO_ERROR (CDECL * PFSTI_COLUMNSETNULL) (STI_ROW hRow, CAA_IDENT idColumn);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNSETNULL_NOTIMPLEMENTED)
	#define USE_STI_ColumnSetNULL
	#define EXT_STI_ColumnSetNULL
	#define GET_STI_ColumnSetNULL(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnSetNULL(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnSetNULL  FALSE
	#define EXP_STI_ColumnSetNULL  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnSetNULL
	#define EXT_STI_ColumnSetNULL
	#define GET_STI_ColumnSetNULL(fl)  CAL_CMGETAPI( "STI_ColumnSetNULL" ) 
	#define CAL_STI_ColumnSetNULL  STI_ColumnSetNULL
	#define CHK_STI_ColumnSetNULL  TRUE
	#define EXP_STI_ColumnSetNULL  CAL_CMEXPAPI( "STI_ColumnSetNULL" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnSetNULL
	#define EXT_STI_ColumnSetNULL
	#define GET_STI_ColumnSetNULL(fl)  CAL_CMGETAPI( "STI_ColumnSetNULL" ) 
	#define CAL_STI_ColumnSetNULL  STI_ColumnSetNULL
	#define CHK_STI_ColumnSetNULL  TRUE
	#define EXP_STI_ColumnSetNULL  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnSetNULL", (RTS_UINTPTR)STI_ColumnSetNULL, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnSetNULL
	#define EXT_CmpCAAStorageSTI_ColumnSetNULL
	#define GET_CmpCAAStorageSTI_ColumnSetNULL  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnSetNULL pICmpCAAStorage->ISTI_ColumnSetNULL
	#define CHK_CmpCAAStorageSTI_ColumnSetNULL (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnSetNULL  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnSetNULL
	#define EXT_STI_ColumnSetNULL
	#define GET_STI_ColumnSetNULL(fl)  CAL_CMGETAPI( "STI_ColumnSetNULL" ) 
	#define CAL_STI_ColumnSetNULL pICmpCAAStorage->ISTI_ColumnSetNULL
	#define CHK_STI_ColumnSetNULL (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnSetNULL  CAL_CMEXPAPI( "STI_ColumnSetNULL" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnSetNULL  PFSTI_COLUMNSETNULL pfSTI_ColumnSetNULL;
	#define EXT_STI_ColumnSetNULL  extern PFSTI_COLUMNSETNULL pfSTI_ColumnSetNULL;
	#define GET_STI_ColumnSetNULL(fl)  s_pfCMGetAPI2( "STI_ColumnSetNULL", (RTS_VOID_FCTPTR *)&pfSTI_ColumnSetNULL, (fl), 0, 0)
	#define CAL_STI_ColumnSetNULL  pfSTI_ColumnSetNULL
	#define CHK_STI_ColumnSetNULL  (pfSTI_ColumnSetNULL != NULL)
	#define EXP_STI_ColumnSetNULL  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnSetNULL", (RTS_UINTPTR)STI_ColumnSetNULL, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnSetREAL4(STI_ROW hRow, CAA_IDENT idColumn, CAA_REAL rValue);
typedef STO_ERROR (CDECL * PFSTI_COLUMNSETREAL4) (STI_ROW hRow, CAA_IDENT idColumn, CAA_REAL rValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNSETREAL4_NOTIMPLEMENTED)
	#define USE_STI_ColumnSetREAL4
	#define EXT_STI_ColumnSetREAL4
	#define GET_STI_ColumnSetREAL4(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnSetREAL4(p0,p1,p2)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnSetREAL4  FALSE
	#define EXP_STI_ColumnSetREAL4  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnSetREAL4
	#define EXT_STI_ColumnSetREAL4
	#define GET_STI_ColumnSetREAL4(fl)  CAL_CMGETAPI( "STI_ColumnSetREAL4" ) 
	#define CAL_STI_ColumnSetREAL4  STI_ColumnSetREAL4
	#define CHK_STI_ColumnSetREAL4  TRUE
	#define EXP_STI_ColumnSetREAL4  CAL_CMEXPAPI( "STI_ColumnSetREAL4" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnSetREAL4
	#define EXT_STI_ColumnSetREAL4
	#define GET_STI_ColumnSetREAL4(fl)  CAL_CMGETAPI( "STI_ColumnSetREAL4" ) 
	#define CAL_STI_ColumnSetREAL4  STI_ColumnSetREAL4
	#define CHK_STI_ColumnSetREAL4  TRUE
	#define EXP_STI_ColumnSetREAL4  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnSetREAL4", (RTS_UINTPTR)STI_ColumnSetREAL4, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnSetREAL4
	#define EXT_CmpCAAStorageSTI_ColumnSetREAL4
	#define GET_CmpCAAStorageSTI_ColumnSetREAL4  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnSetREAL4 pICmpCAAStorage->ISTI_ColumnSetREAL4
	#define CHK_CmpCAAStorageSTI_ColumnSetREAL4 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnSetREAL4  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnSetREAL4
	#define EXT_STI_ColumnSetREAL4
	#define GET_STI_ColumnSetREAL4(fl)  CAL_CMGETAPI( "STI_ColumnSetREAL4" ) 
	#define CAL_STI_ColumnSetREAL4 pICmpCAAStorage->ISTI_ColumnSetREAL4
	#define CHK_STI_ColumnSetREAL4 (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnSetREAL4  CAL_CMEXPAPI( "STI_ColumnSetREAL4" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnSetREAL4  PFSTI_COLUMNSETREAL4 pfSTI_ColumnSetREAL4;
	#define EXT_STI_ColumnSetREAL4  extern PFSTI_COLUMNSETREAL4 pfSTI_ColumnSetREAL4;
	#define GET_STI_ColumnSetREAL4(fl)  s_pfCMGetAPI2( "STI_ColumnSetREAL4", (RTS_VOID_FCTPTR *)&pfSTI_ColumnSetREAL4, (fl), 0, 0)
	#define CAL_STI_ColumnSetREAL4  pfSTI_ColumnSetREAL4
	#define CHK_STI_ColumnSetREAL4  (pfSTI_ColumnSetREAL4 != NULL)
	#define EXP_STI_ColumnSetREAL4  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnSetREAL4", (RTS_UINTPTR)STI_ColumnSetREAL4, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnSetREAL8(STI_ROW hRow, CAA_IDENT idColumn, CAA_LREAL lrValue);
typedef STO_ERROR (CDECL * PFSTI_COLUMNSETREAL8) (STI_ROW hRow, CAA_IDENT idColumn, CAA_LREAL lrValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNSETREAL8_NOTIMPLEMENTED)
	#define USE_STI_ColumnSetREAL8
	#define EXT_STI_ColumnSetREAL8
	#define GET_STI_ColumnSetREAL8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnSetREAL8(p0,p1,p2)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnSetREAL8  FALSE
	#define EXP_STI_ColumnSetREAL8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnSetREAL8
	#define EXT_STI_ColumnSetREAL8
	#define GET_STI_ColumnSetREAL8(fl)  CAL_CMGETAPI( "STI_ColumnSetREAL8" ) 
	#define CAL_STI_ColumnSetREAL8  STI_ColumnSetREAL8
	#define CHK_STI_ColumnSetREAL8  TRUE
	#define EXP_STI_ColumnSetREAL8  CAL_CMEXPAPI( "STI_ColumnSetREAL8" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnSetREAL8
	#define EXT_STI_ColumnSetREAL8
	#define GET_STI_ColumnSetREAL8(fl)  CAL_CMGETAPI( "STI_ColumnSetREAL8" ) 
	#define CAL_STI_ColumnSetREAL8  STI_ColumnSetREAL8
	#define CHK_STI_ColumnSetREAL8  TRUE
	#define EXP_STI_ColumnSetREAL8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnSetREAL8", (RTS_UINTPTR)STI_ColumnSetREAL8, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnSetREAL8
	#define EXT_CmpCAAStorageSTI_ColumnSetREAL8
	#define GET_CmpCAAStorageSTI_ColumnSetREAL8  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnSetREAL8 pICmpCAAStorage->ISTI_ColumnSetREAL8
	#define CHK_CmpCAAStorageSTI_ColumnSetREAL8 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnSetREAL8  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnSetREAL8
	#define EXT_STI_ColumnSetREAL8
	#define GET_STI_ColumnSetREAL8(fl)  CAL_CMGETAPI( "STI_ColumnSetREAL8" ) 
	#define CAL_STI_ColumnSetREAL8 pICmpCAAStorage->ISTI_ColumnSetREAL8
	#define CHK_STI_ColumnSetREAL8 (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnSetREAL8  CAL_CMEXPAPI( "STI_ColumnSetREAL8" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnSetREAL8  PFSTI_COLUMNSETREAL8 pfSTI_ColumnSetREAL8;
	#define EXT_STI_ColumnSetREAL8  extern PFSTI_COLUMNSETREAL8 pfSTI_ColumnSetREAL8;
	#define GET_STI_ColumnSetREAL8(fl)  s_pfCMGetAPI2( "STI_ColumnSetREAL8", (RTS_VOID_FCTPTR *)&pfSTI_ColumnSetREAL8, (fl), 0, 0)
	#define CAL_STI_ColumnSetREAL8  pfSTI_ColumnSetREAL8
	#define CHK_STI_ColumnSetREAL8  (pfSTI_ColumnSetREAL8 != NULL)
	#define EXP_STI_ColumnSetREAL8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnSetREAL8", (RTS_UINTPTR)STI_ColumnSetREAL8, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnSetTEXT(STI_ROW hRow, CAA_IDENT idColumn, STO_TEXT *ptxtValue);
typedef STO_ERROR (CDECL * PFSTI_COLUMNSETTEXT) (STI_ROW hRow, CAA_IDENT idColumn, STO_TEXT *ptxtValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNSETTEXT_NOTIMPLEMENTED)
	#define USE_STI_ColumnSetTEXT
	#define EXT_STI_ColumnSetTEXT
	#define GET_STI_ColumnSetTEXT(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnSetTEXT(p0,p1,p2)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnSetTEXT  FALSE
	#define EXP_STI_ColumnSetTEXT  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnSetTEXT
	#define EXT_STI_ColumnSetTEXT
	#define GET_STI_ColumnSetTEXT(fl)  CAL_CMGETAPI( "STI_ColumnSetTEXT" ) 
	#define CAL_STI_ColumnSetTEXT  STI_ColumnSetTEXT
	#define CHK_STI_ColumnSetTEXT  TRUE
	#define EXP_STI_ColumnSetTEXT  CAL_CMEXPAPI( "STI_ColumnSetTEXT" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnSetTEXT
	#define EXT_STI_ColumnSetTEXT
	#define GET_STI_ColumnSetTEXT(fl)  CAL_CMGETAPI( "STI_ColumnSetTEXT" ) 
	#define CAL_STI_ColumnSetTEXT  STI_ColumnSetTEXT
	#define CHK_STI_ColumnSetTEXT  TRUE
	#define EXP_STI_ColumnSetTEXT  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnSetTEXT", (RTS_UINTPTR)STI_ColumnSetTEXT, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnSetTEXT
	#define EXT_CmpCAAStorageSTI_ColumnSetTEXT
	#define GET_CmpCAAStorageSTI_ColumnSetTEXT  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnSetTEXT pICmpCAAStorage->ISTI_ColumnSetTEXT
	#define CHK_CmpCAAStorageSTI_ColumnSetTEXT (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnSetTEXT  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnSetTEXT
	#define EXT_STI_ColumnSetTEXT
	#define GET_STI_ColumnSetTEXT(fl)  CAL_CMGETAPI( "STI_ColumnSetTEXT" ) 
	#define CAL_STI_ColumnSetTEXT pICmpCAAStorage->ISTI_ColumnSetTEXT
	#define CHK_STI_ColumnSetTEXT (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnSetTEXT  CAL_CMEXPAPI( "STI_ColumnSetTEXT" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnSetTEXT  PFSTI_COLUMNSETTEXT pfSTI_ColumnSetTEXT;
	#define EXT_STI_ColumnSetTEXT  extern PFSTI_COLUMNSETTEXT pfSTI_ColumnSetTEXT;
	#define GET_STI_ColumnSetTEXT(fl)  s_pfCMGetAPI2( "STI_ColumnSetTEXT", (RTS_VOID_FCTPTR *)&pfSTI_ColumnSetTEXT, (fl), 0, 0)
	#define CAL_STI_ColumnSetTEXT  pfSTI_ColumnSetTEXT
	#define CHK_STI_ColumnSetTEXT  (pfSTI_ColumnSetTEXT != NULL)
	#define EXP_STI_ColumnSetTEXT  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnSetTEXT", (RTS_UINTPTR)STI_ColumnSetTEXT, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnUpdateBLOB(STI_ROW hRow, CAA_IDENT idColumn, STO_BLOB *pblobValue, CAA_BOOL *pxNULL);
typedef STO_ERROR (CDECL * PFSTI_COLUMNUPDATEBLOB) (STI_ROW hRow, CAA_IDENT idColumn, STO_BLOB *pblobValue, CAA_BOOL *pxNULL);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNUPDATEBLOB_NOTIMPLEMENTED)
	#define USE_STI_ColumnUpdateBLOB
	#define EXT_STI_ColumnUpdateBLOB
	#define GET_STI_ColumnUpdateBLOB(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnUpdateBLOB(p0,p1,p2,p3)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnUpdateBLOB  FALSE
	#define EXP_STI_ColumnUpdateBLOB  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnUpdateBLOB
	#define EXT_STI_ColumnUpdateBLOB
	#define GET_STI_ColumnUpdateBLOB(fl)  CAL_CMGETAPI( "STI_ColumnUpdateBLOB" ) 
	#define CAL_STI_ColumnUpdateBLOB  STI_ColumnUpdateBLOB
	#define CHK_STI_ColumnUpdateBLOB  TRUE
	#define EXP_STI_ColumnUpdateBLOB  CAL_CMEXPAPI( "STI_ColumnUpdateBLOB" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnUpdateBLOB
	#define EXT_STI_ColumnUpdateBLOB
	#define GET_STI_ColumnUpdateBLOB(fl)  CAL_CMGETAPI( "STI_ColumnUpdateBLOB" ) 
	#define CAL_STI_ColumnUpdateBLOB  STI_ColumnUpdateBLOB
	#define CHK_STI_ColumnUpdateBLOB  TRUE
	#define EXP_STI_ColumnUpdateBLOB  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnUpdateBLOB", (RTS_UINTPTR)STI_ColumnUpdateBLOB, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnUpdateBLOB
	#define EXT_CmpCAAStorageSTI_ColumnUpdateBLOB
	#define GET_CmpCAAStorageSTI_ColumnUpdateBLOB  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnUpdateBLOB pICmpCAAStorage->ISTI_ColumnUpdateBLOB
	#define CHK_CmpCAAStorageSTI_ColumnUpdateBLOB (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnUpdateBLOB  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnUpdateBLOB
	#define EXT_STI_ColumnUpdateBLOB
	#define GET_STI_ColumnUpdateBLOB(fl)  CAL_CMGETAPI( "STI_ColumnUpdateBLOB" ) 
	#define CAL_STI_ColumnUpdateBLOB pICmpCAAStorage->ISTI_ColumnUpdateBLOB
	#define CHK_STI_ColumnUpdateBLOB (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnUpdateBLOB  CAL_CMEXPAPI( "STI_ColumnUpdateBLOB" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnUpdateBLOB  PFSTI_COLUMNUPDATEBLOB pfSTI_ColumnUpdateBLOB;
	#define EXT_STI_ColumnUpdateBLOB  extern PFSTI_COLUMNUPDATEBLOB pfSTI_ColumnUpdateBLOB;
	#define GET_STI_ColumnUpdateBLOB(fl)  s_pfCMGetAPI2( "STI_ColumnUpdateBLOB", (RTS_VOID_FCTPTR *)&pfSTI_ColumnUpdateBLOB, (fl), 0, 0)
	#define CAL_STI_ColumnUpdateBLOB  pfSTI_ColumnUpdateBLOB
	#define CHK_STI_ColumnUpdateBLOB  (pfSTI_ColumnUpdateBLOB != NULL)
	#define EXP_STI_ColumnUpdateBLOB  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnUpdateBLOB", (RTS_UINTPTR)STI_ColumnUpdateBLOB, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnUpdateINT16(STI_ROW hRow, CAA_IDENT idColumn, CAA_INT *piValue, CAA_BOOL *pxNULL);
typedef STO_ERROR (CDECL * PFSTI_COLUMNUPDATEINT16) (STI_ROW hRow, CAA_IDENT idColumn, CAA_INT *piValue, CAA_BOOL *pxNULL);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNUPDATEINT16_NOTIMPLEMENTED)
	#define USE_STI_ColumnUpdateINT16
	#define EXT_STI_ColumnUpdateINT16
	#define GET_STI_ColumnUpdateINT16(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnUpdateINT16(p0,p1,p2,p3)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnUpdateINT16  FALSE
	#define EXP_STI_ColumnUpdateINT16  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnUpdateINT16
	#define EXT_STI_ColumnUpdateINT16
	#define GET_STI_ColumnUpdateINT16(fl)  CAL_CMGETAPI( "STI_ColumnUpdateINT16" ) 
	#define CAL_STI_ColumnUpdateINT16  STI_ColumnUpdateINT16
	#define CHK_STI_ColumnUpdateINT16  TRUE
	#define EXP_STI_ColumnUpdateINT16  CAL_CMEXPAPI( "STI_ColumnUpdateINT16" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnUpdateINT16
	#define EXT_STI_ColumnUpdateINT16
	#define GET_STI_ColumnUpdateINT16(fl)  CAL_CMGETAPI( "STI_ColumnUpdateINT16" ) 
	#define CAL_STI_ColumnUpdateINT16  STI_ColumnUpdateINT16
	#define CHK_STI_ColumnUpdateINT16  TRUE
	#define EXP_STI_ColumnUpdateINT16  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnUpdateINT16", (RTS_UINTPTR)STI_ColumnUpdateINT16, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnUpdateINT16
	#define EXT_CmpCAAStorageSTI_ColumnUpdateINT16
	#define GET_CmpCAAStorageSTI_ColumnUpdateINT16  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnUpdateINT16 pICmpCAAStorage->ISTI_ColumnUpdateINT16
	#define CHK_CmpCAAStorageSTI_ColumnUpdateINT16 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnUpdateINT16  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnUpdateINT16
	#define EXT_STI_ColumnUpdateINT16
	#define GET_STI_ColumnUpdateINT16(fl)  CAL_CMGETAPI( "STI_ColumnUpdateINT16" ) 
	#define CAL_STI_ColumnUpdateINT16 pICmpCAAStorage->ISTI_ColumnUpdateINT16
	#define CHK_STI_ColumnUpdateINT16 (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnUpdateINT16  CAL_CMEXPAPI( "STI_ColumnUpdateINT16" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnUpdateINT16  PFSTI_COLUMNUPDATEINT16 pfSTI_ColumnUpdateINT16;
	#define EXT_STI_ColumnUpdateINT16  extern PFSTI_COLUMNUPDATEINT16 pfSTI_ColumnUpdateINT16;
	#define GET_STI_ColumnUpdateINT16(fl)  s_pfCMGetAPI2( "STI_ColumnUpdateINT16", (RTS_VOID_FCTPTR *)&pfSTI_ColumnUpdateINT16, (fl), 0, 0)
	#define CAL_STI_ColumnUpdateINT16  pfSTI_ColumnUpdateINT16
	#define CHK_STI_ColumnUpdateINT16  (pfSTI_ColumnUpdateINT16 != NULL)
	#define EXP_STI_ColumnUpdateINT16  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnUpdateINT16", (RTS_UINTPTR)STI_ColumnUpdateINT16, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnUpdateINT32(STI_ROW hRow, CAA_IDENT idColumn, CAA_DINT *pdiValue, CAA_BOOL *pxNULL);
typedef STO_ERROR (CDECL * PFSTI_COLUMNUPDATEINT32) (STI_ROW hRow, CAA_IDENT idColumn, CAA_DINT *pdiValue, CAA_BOOL *pxNULL);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNUPDATEINT32_NOTIMPLEMENTED)
	#define USE_STI_ColumnUpdateINT32
	#define EXT_STI_ColumnUpdateINT32
	#define GET_STI_ColumnUpdateINT32(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnUpdateINT32(p0,p1,p2,p3)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnUpdateINT32  FALSE
	#define EXP_STI_ColumnUpdateINT32  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnUpdateINT32
	#define EXT_STI_ColumnUpdateINT32
	#define GET_STI_ColumnUpdateINT32(fl)  CAL_CMGETAPI( "STI_ColumnUpdateINT32" ) 
	#define CAL_STI_ColumnUpdateINT32  STI_ColumnUpdateINT32
	#define CHK_STI_ColumnUpdateINT32  TRUE
	#define EXP_STI_ColumnUpdateINT32  CAL_CMEXPAPI( "STI_ColumnUpdateINT32" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnUpdateINT32
	#define EXT_STI_ColumnUpdateINT32
	#define GET_STI_ColumnUpdateINT32(fl)  CAL_CMGETAPI( "STI_ColumnUpdateINT32" ) 
	#define CAL_STI_ColumnUpdateINT32  STI_ColumnUpdateINT32
	#define CHK_STI_ColumnUpdateINT32  TRUE
	#define EXP_STI_ColumnUpdateINT32  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnUpdateINT32", (RTS_UINTPTR)STI_ColumnUpdateINT32, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnUpdateINT32
	#define EXT_CmpCAAStorageSTI_ColumnUpdateINT32
	#define GET_CmpCAAStorageSTI_ColumnUpdateINT32  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnUpdateINT32 pICmpCAAStorage->ISTI_ColumnUpdateINT32
	#define CHK_CmpCAAStorageSTI_ColumnUpdateINT32 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnUpdateINT32  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnUpdateINT32
	#define EXT_STI_ColumnUpdateINT32
	#define GET_STI_ColumnUpdateINT32(fl)  CAL_CMGETAPI( "STI_ColumnUpdateINT32" ) 
	#define CAL_STI_ColumnUpdateINT32 pICmpCAAStorage->ISTI_ColumnUpdateINT32
	#define CHK_STI_ColumnUpdateINT32 (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnUpdateINT32  CAL_CMEXPAPI( "STI_ColumnUpdateINT32" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnUpdateINT32  PFSTI_COLUMNUPDATEINT32 pfSTI_ColumnUpdateINT32;
	#define EXT_STI_ColumnUpdateINT32  extern PFSTI_COLUMNUPDATEINT32 pfSTI_ColumnUpdateINT32;
	#define GET_STI_ColumnUpdateINT32(fl)  s_pfCMGetAPI2( "STI_ColumnUpdateINT32", (RTS_VOID_FCTPTR *)&pfSTI_ColumnUpdateINT32, (fl), 0, 0)
	#define CAL_STI_ColumnUpdateINT32  pfSTI_ColumnUpdateINT32
	#define CHK_STI_ColumnUpdateINT32  (pfSTI_ColumnUpdateINT32 != NULL)
	#define EXP_STI_ColumnUpdateINT32  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnUpdateINT32", (RTS_UINTPTR)STI_ColumnUpdateINT32, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnUpdateINT64(STI_ROW hRow, CAA_IDENT idColumn, CAA_LINT *pliValue, CAA_BOOL *pxNULL);
typedef STO_ERROR (CDECL * PFSTI_COLUMNUPDATEINT64) (STI_ROW hRow, CAA_IDENT idColumn, CAA_LINT *pliValue, CAA_BOOL *pxNULL);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNUPDATEINT64_NOTIMPLEMENTED)
	#define USE_STI_ColumnUpdateINT64
	#define EXT_STI_ColumnUpdateINT64
	#define GET_STI_ColumnUpdateINT64(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnUpdateINT64(p0,p1,p2,p3)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnUpdateINT64  FALSE
	#define EXP_STI_ColumnUpdateINT64  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnUpdateINT64
	#define EXT_STI_ColumnUpdateINT64
	#define GET_STI_ColumnUpdateINT64(fl)  CAL_CMGETAPI( "STI_ColumnUpdateINT64" ) 
	#define CAL_STI_ColumnUpdateINT64  STI_ColumnUpdateINT64
	#define CHK_STI_ColumnUpdateINT64  TRUE
	#define EXP_STI_ColumnUpdateINT64  CAL_CMEXPAPI( "STI_ColumnUpdateINT64" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnUpdateINT64
	#define EXT_STI_ColumnUpdateINT64
	#define GET_STI_ColumnUpdateINT64(fl)  CAL_CMGETAPI( "STI_ColumnUpdateINT64" ) 
	#define CAL_STI_ColumnUpdateINT64  STI_ColumnUpdateINT64
	#define CHK_STI_ColumnUpdateINT64  TRUE
	#define EXP_STI_ColumnUpdateINT64  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnUpdateINT64", (RTS_UINTPTR)STI_ColumnUpdateINT64, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnUpdateINT64
	#define EXT_CmpCAAStorageSTI_ColumnUpdateINT64
	#define GET_CmpCAAStorageSTI_ColumnUpdateINT64  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnUpdateINT64 pICmpCAAStorage->ISTI_ColumnUpdateINT64
	#define CHK_CmpCAAStorageSTI_ColumnUpdateINT64 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnUpdateINT64  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnUpdateINT64
	#define EXT_STI_ColumnUpdateINT64
	#define GET_STI_ColumnUpdateINT64(fl)  CAL_CMGETAPI( "STI_ColumnUpdateINT64" ) 
	#define CAL_STI_ColumnUpdateINT64 pICmpCAAStorage->ISTI_ColumnUpdateINT64
	#define CHK_STI_ColumnUpdateINT64 (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnUpdateINT64  CAL_CMEXPAPI( "STI_ColumnUpdateINT64" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnUpdateINT64  PFSTI_COLUMNUPDATEINT64 pfSTI_ColumnUpdateINT64;
	#define EXT_STI_ColumnUpdateINT64  extern PFSTI_COLUMNUPDATEINT64 pfSTI_ColumnUpdateINT64;
	#define GET_STI_ColumnUpdateINT64(fl)  s_pfCMGetAPI2( "STI_ColumnUpdateINT64", (RTS_VOID_FCTPTR *)&pfSTI_ColumnUpdateINT64, (fl), 0, 0)
	#define CAL_STI_ColumnUpdateINT64  pfSTI_ColumnUpdateINT64
	#define CHK_STI_ColumnUpdateINT64  (pfSTI_ColumnUpdateINT64 != NULL)
	#define EXP_STI_ColumnUpdateINT64  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnUpdateINT64", (RTS_UINTPTR)STI_ColumnUpdateINT64, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnUpdateINT8(STI_ROW hRow, CAA_IDENT idColumn, CAA_SINT *psiValue, CAA_BOOL *pxNULL);
typedef STO_ERROR (CDECL * PFSTI_COLUMNUPDATEINT8) (STI_ROW hRow, CAA_IDENT idColumn, CAA_SINT *psiValue, CAA_BOOL *pxNULL);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNUPDATEINT8_NOTIMPLEMENTED)
	#define USE_STI_ColumnUpdateINT8
	#define EXT_STI_ColumnUpdateINT8
	#define GET_STI_ColumnUpdateINT8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnUpdateINT8(p0,p1,p2,p3)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnUpdateINT8  FALSE
	#define EXP_STI_ColumnUpdateINT8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnUpdateINT8
	#define EXT_STI_ColumnUpdateINT8
	#define GET_STI_ColumnUpdateINT8(fl)  CAL_CMGETAPI( "STI_ColumnUpdateINT8" ) 
	#define CAL_STI_ColumnUpdateINT8  STI_ColumnUpdateINT8
	#define CHK_STI_ColumnUpdateINT8  TRUE
	#define EXP_STI_ColumnUpdateINT8  CAL_CMEXPAPI( "STI_ColumnUpdateINT8" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnUpdateINT8
	#define EXT_STI_ColumnUpdateINT8
	#define GET_STI_ColumnUpdateINT8(fl)  CAL_CMGETAPI( "STI_ColumnUpdateINT8" ) 
	#define CAL_STI_ColumnUpdateINT8  STI_ColumnUpdateINT8
	#define CHK_STI_ColumnUpdateINT8  TRUE
	#define EXP_STI_ColumnUpdateINT8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnUpdateINT8", (RTS_UINTPTR)STI_ColumnUpdateINT8, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnUpdateINT8
	#define EXT_CmpCAAStorageSTI_ColumnUpdateINT8
	#define GET_CmpCAAStorageSTI_ColumnUpdateINT8  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnUpdateINT8 pICmpCAAStorage->ISTI_ColumnUpdateINT8
	#define CHK_CmpCAAStorageSTI_ColumnUpdateINT8 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnUpdateINT8  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnUpdateINT8
	#define EXT_STI_ColumnUpdateINT8
	#define GET_STI_ColumnUpdateINT8(fl)  CAL_CMGETAPI( "STI_ColumnUpdateINT8" ) 
	#define CAL_STI_ColumnUpdateINT8 pICmpCAAStorage->ISTI_ColumnUpdateINT8
	#define CHK_STI_ColumnUpdateINT8 (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnUpdateINT8  CAL_CMEXPAPI( "STI_ColumnUpdateINT8" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnUpdateINT8  PFSTI_COLUMNUPDATEINT8 pfSTI_ColumnUpdateINT8;
	#define EXT_STI_ColumnUpdateINT8  extern PFSTI_COLUMNUPDATEINT8 pfSTI_ColumnUpdateINT8;
	#define GET_STI_ColumnUpdateINT8(fl)  s_pfCMGetAPI2( "STI_ColumnUpdateINT8", (RTS_VOID_FCTPTR *)&pfSTI_ColumnUpdateINT8, (fl), 0, 0)
	#define CAL_STI_ColumnUpdateINT8  pfSTI_ColumnUpdateINT8
	#define CHK_STI_ColumnUpdateINT8  (pfSTI_ColumnUpdateINT8 != NULL)
	#define EXP_STI_ColumnUpdateINT8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnUpdateINT8", (RTS_UINTPTR)STI_ColumnUpdateINT8, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnUpdateREAL4(STI_ROW hRow, CAA_IDENT idColumn, CAA_REAL *prValue, CAA_BOOL *pxNULL);
typedef STO_ERROR (CDECL * PFSTI_COLUMNUPDATEREAL4) (STI_ROW hRow, CAA_IDENT idColumn, CAA_REAL *prValue, CAA_BOOL *pxNULL);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNUPDATEREAL4_NOTIMPLEMENTED)
	#define USE_STI_ColumnUpdateREAL4
	#define EXT_STI_ColumnUpdateREAL4
	#define GET_STI_ColumnUpdateREAL4(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnUpdateREAL4(p0,p1,p2,p3)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnUpdateREAL4  FALSE
	#define EXP_STI_ColumnUpdateREAL4  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnUpdateREAL4
	#define EXT_STI_ColumnUpdateREAL4
	#define GET_STI_ColumnUpdateREAL4(fl)  CAL_CMGETAPI( "STI_ColumnUpdateREAL4" ) 
	#define CAL_STI_ColumnUpdateREAL4  STI_ColumnUpdateREAL4
	#define CHK_STI_ColumnUpdateREAL4  TRUE
	#define EXP_STI_ColumnUpdateREAL4  CAL_CMEXPAPI( "STI_ColumnUpdateREAL4" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnUpdateREAL4
	#define EXT_STI_ColumnUpdateREAL4
	#define GET_STI_ColumnUpdateREAL4(fl)  CAL_CMGETAPI( "STI_ColumnUpdateREAL4" ) 
	#define CAL_STI_ColumnUpdateREAL4  STI_ColumnUpdateREAL4
	#define CHK_STI_ColumnUpdateREAL4  TRUE
	#define EXP_STI_ColumnUpdateREAL4  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnUpdateREAL4", (RTS_UINTPTR)STI_ColumnUpdateREAL4, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnUpdateREAL4
	#define EXT_CmpCAAStorageSTI_ColumnUpdateREAL4
	#define GET_CmpCAAStorageSTI_ColumnUpdateREAL4  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnUpdateREAL4 pICmpCAAStorage->ISTI_ColumnUpdateREAL4
	#define CHK_CmpCAAStorageSTI_ColumnUpdateREAL4 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnUpdateREAL4  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnUpdateREAL4
	#define EXT_STI_ColumnUpdateREAL4
	#define GET_STI_ColumnUpdateREAL4(fl)  CAL_CMGETAPI( "STI_ColumnUpdateREAL4" ) 
	#define CAL_STI_ColumnUpdateREAL4 pICmpCAAStorage->ISTI_ColumnUpdateREAL4
	#define CHK_STI_ColumnUpdateREAL4 (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnUpdateREAL4  CAL_CMEXPAPI( "STI_ColumnUpdateREAL4" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnUpdateREAL4  PFSTI_COLUMNUPDATEREAL4 pfSTI_ColumnUpdateREAL4;
	#define EXT_STI_ColumnUpdateREAL4  extern PFSTI_COLUMNUPDATEREAL4 pfSTI_ColumnUpdateREAL4;
	#define GET_STI_ColumnUpdateREAL4(fl)  s_pfCMGetAPI2( "STI_ColumnUpdateREAL4", (RTS_VOID_FCTPTR *)&pfSTI_ColumnUpdateREAL4, (fl), 0, 0)
	#define CAL_STI_ColumnUpdateREAL4  pfSTI_ColumnUpdateREAL4
	#define CHK_STI_ColumnUpdateREAL4  (pfSTI_ColumnUpdateREAL4 != NULL)
	#define EXP_STI_ColumnUpdateREAL4  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnUpdateREAL4", (RTS_UINTPTR)STI_ColumnUpdateREAL4, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnUpdateREAL8(STI_ROW hRow, CAA_IDENT idColumn, CAA_LREAL *plrValue, CAA_BOOL *pxNULL);
typedef STO_ERROR (CDECL * PFSTI_COLUMNUPDATEREAL8) (STI_ROW hRow, CAA_IDENT idColumn, CAA_LREAL *plrValue, CAA_BOOL *pxNULL);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNUPDATEREAL8_NOTIMPLEMENTED)
	#define USE_STI_ColumnUpdateREAL8
	#define EXT_STI_ColumnUpdateREAL8
	#define GET_STI_ColumnUpdateREAL8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnUpdateREAL8(p0,p1,p2,p3)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnUpdateREAL8  FALSE
	#define EXP_STI_ColumnUpdateREAL8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnUpdateREAL8
	#define EXT_STI_ColumnUpdateREAL8
	#define GET_STI_ColumnUpdateREAL8(fl)  CAL_CMGETAPI( "STI_ColumnUpdateREAL8" ) 
	#define CAL_STI_ColumnUpdateREAL8  STI_ColumnUpdateREAL8
	#define CHK_STI_ColumnUpdateREAL8  TRUE
	#define EXP_STI_ColumnUpdateREAL8  CAL_CMEXPAPI( "STI_ColumnUpdateREAL8" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnUpdateREAL8
	#define EXT_STI_ColumnUpdateREAL8
	#define GET_STI_ColumnUpdateREAL8(fl)  CAL_CMGETAPI( "STI_ColumnUpdateREAL8" ) 
	#define CAL_STI_ColumnUpdateREAL8  STI_ColumnUpdateREAL8
	#define CHK_STI_ColumnUpdateREAL8  TRUE
	#define EXP_STI_ColumnUpdateREAL8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnUpdateREAL8", (RTS_UINTPTR)STI_ColumnUpdateREAL8, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnUpdateREAL8
	#define EXT_CmpCAAStorageSTI_ColumnUpdateREAL8
	#define GET_CmpCAAStorageSTI_ColumnUpdateREAL8  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnUpdateREAL8 pICmpCAAStorage->ISTI_ColumnUpdateREAL8
	#define CHK_CmpCAAStorageSTI_ColumnUpdateREAL8 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnUpdateREAL8  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnUpdateREAL8
	#define EXT_STI_ColumnUpdateREAL8
	#define GET_STI_ColumnUpdateREAL8(fl)  CAL_CMGETAPI( "STI_ColumnUpdateREAL8" ) 
	#define CAL_STI_ColumnUpdateREAL8 pICmpCAAStorage->ISTI_ColumnUpdateREAL8
	#define CHK_STI_ColumnUpdateREAL8 (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnUpdateREAL8  CAL_CMEXPAPI( "STI_ColumnUpdateREAL8" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnUpdateREAL8  PFSTI_COLUMNUPDATEREAL8 pfSTI_ColumnUpdateREAL8;
	#define EXT_STI_ColumnUpdateREAL8  extern PFSTI_COLUMNUPDATEREAL8 pfSTI_ColumnUpdateREAL8;
	#define GET_STI_ColumnUpdateREAL8(fl)  s_pfCMGetAPI2( "STI_ColumnUpdateREAL8", (RTS_VOID_FCTPTR *)&pfSTI_ColumnUpdateREAL8, (fl), 0, 0)
	#define CAL_STI_ColumnUpdateREAL8  pfSTI_ColumnUpdateREAL8
	#define CHK_STI_ColumnUpdateREAL8  (pfSTI_ColumnUpdateREAL8 != NULL)
	#define EXP_STI_ColumnUpdateREAL8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnUpdateREAL8", (RTS_UINTPTR)STI_ColumnUpdateREAL8, 0, 0) 
#endif



STO_ERROR CDECL STI_ColumnUpdateTEXT(STI_ROW hRow, CAA_IDENT idColumn, STO_TEXT *ptxtValue, CAA_BOOL *pxNULL);
typedef STO_ERROR (CDECL * PFSTI_COLUMNUPDATETEXT) (STI_ROW hRow, CAA_IDENT idColumn, STO_TEXT *ptxtValue, CAA_BOOL *pxNULL);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_COLUMNUPDATETEXT_NOTIMPLEMENTED)
	#define USE_STI_ColumnUpdateTEXT
	#define EXT_STI_ColumnUpdateTEXT
	#define GET_STI_ColumnUpdateTEXT(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_ColumnUpdateTEXT(p0,p1,p2,p3)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_ColumnUpdateTEXT  FALSE
	#define EXP_STI_ColumnUpdateTEXT  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_ColumnUpdateTEXT
	#define EXT_STI_ColumnUpdateTEXT
	#define GET_STI_ColumnUpdateTEXT(fl)  CAL_CMGETAPI( "STI_ColumnUpdateTEXT" ) 
	#define CAL_STI_ColumnUpdateTEXT  STI_ColumnUpdateTEXT
	#define CHK_STI_ColumnUpdateTEXT  TRUE
	#define EXP_STI_ColumnUpdateTEXT  CAL_CMEXPAPI( "STI_ColumnUpdateTEXT" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_ColumnUpdateTEXT
	#define EXT_STI_ColumnUpdateTEXT
	#define GET_STI_ColumnUpdateTEXT(fl)  CAL_CMGETAPI( "STI_ColumnUpdateTEXT" ) 
	#define CAL_STI_ColumnUpdateTEXT  STI_ColumnUpdateTEXT
	#define CHK_STI_ColumnUpdateTEXT  TRUE
	#define EXP_STI_ColumnUpdateTEXT  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnUpdateTEXT", (RTS_UINTPTR)STI_ColumnUpdateTEXT, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_ColumnUpdateTEXT
	#define EXT_CmpCAAStorageSTI_ColumnUpdateTEXT
	#define GET_CmpCAAStorageSTI_ColumnUpdateTEXT  ERR_OK
	#define CAL_CmpCAAStorageSTI_ColumnUpdateTEXT pICmpCAAStorage->ISTI_ColumnUpdateTEXT
	#define CHK_CmpCAAStorageSTI_ColumnUpdateTEXT (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_ColumnUpdateTEXT  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_ColumnUpdateTEXT
	#define EXT_STI_ColumnUpdateTEXT
	#define GET_STI_ColumnUpdateTEXT(fl)  CAL_CMGETAPI( "STI_ColumnUpdateTEXT" ) 
	#define CAL_STI_ColumnUpdateTEXT pICmpCAAStorage->ISTI_ColumnUpdateTEXT
	#define CHK_STI_ColumnUpdateTEXT (pICmpCAAStorage != NULL)
	#define EXP_STI_ColumnUpdateTEXT  CAL_CMEXPAPI( "STI_ColumnUpdateTEXT" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_ColumnUpdateTEXT  PFSTI_COLUMNUPDATETEXT pfSTI_ColumnUpdateTEXT;
	#define EXT_STI_ColumnUpdateTEXT  extern PFSTI_COLUMNUPDATETEXT pfSTI_ColumnUpdateTEXT;
	#define GET_STI_ColumnUpdateTEXT(fl)  s_pfCMGetAPI2( "STI_ColumnUpdateTEXT", (RTS_VOID_FCTPTR *)&pfSTI_ColumnUpdateTEXT, (fl), 0, 0)
	#define CAL_STI_ColumnUpdateTEXT  pfSTI_ColumnUpdateTEXT
	#define CHK_STI_ColumnUpdateTEXT  (pfSTI_ColumnUpdateTEXT != NULL)
	#define EXP_STI_ColumnUpdateTEXT  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_ColumnUpdateTEXT", (RTS_UINTPTR)STI_ColumnUpdateTEXT, 0, 0) 
#endif



STO_ERROR CDECL STI_CursorClose(STI_CURSOR hCursor);
typedef STO_ERROR (CDECL * PFSTI_CURSORCLOSE) (STI_CURSOR hCursor);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORCLOSE_NOTIMPLEMENTED)
	#define USE_STI_CursorClose
	#define EXT_STI_CursorClose
	#define GET_STI_CursorClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_CursorClose(p0)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_CursorClose  FALSE
	#define EXP_STI_CursorClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_CursorClose
	#define EXT_STI_CursorClose
	#define GET_STI_CursorClose(fl)  CAL_CMGETAPI( "STI_CursorClose" ) 
	#define CAL_STI_CursorClose  STI_CursorClose
	#define CHK_STI_CursorClose  TRUE
	#define EXP_STI_CursorClose  CAL_CMEXPAPI( "STI_CursorClose" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_CursorClose
	#define EXT_STI_CursorClose
	#define GET_STI_CursorClose(fl)  CAL_CMGETAPI( "STI_CursorClose" ) 
	#define CAL_STI_CursorClose  STI_CursorClose
	#define CHK_STI_CursorClose  TRUE
	#define EXP_STI_CursorClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorClose", (RTS_UINTPTR)STI_CursorClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_CursorClose
	#define EXT_CmpCAAStorageSTI_CursorClose
	#define GET_CmpCAAStorageSTI_CursorClose  ERR_OK
	#define CAL_CmpCAAStorageSTI_CursorClose pICmpCAAStorage->ISTI_CursorClose
	#define CHK_CmpCAAStorageSTI_CursorClose (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_CursorClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_CursorClose
	#define EXT_STI_CursorClose
	#define GET_STI_CursorClose(fl)  CAL_CMGETAPI( "STI_CursorClose" ) 
	#define CAL_STI_CursorClose pICmpCAAStorage->ISTI_CursorClose
	#define CHK_STI_CursorClose (pICmpCAAStorage != NULL)
	#define EXP_STI_CursorClose  CAL_CMEXPAPI( "STI_CursorClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_CursorClose  PFSTI_CURSORCLOSE pfSTI_CursorClose;
	#define EXT_STI_CursorClose  extern PFSTI_CURSORCLOSE pfSTI_CursorClose;
	#define GET_STI_CursorClose(fl)  s_pfCMGetAPI2( "STI_CursorClose", (RTS_VOID_FCTPTR *)&pfSTI_CursorClose, (fl), 0, 0)
	#define CAL_STI_CursorClose  pfSTI_CursorClose
	#define CHK_STI_CursorClose  (pfSTI_CursorClose != NULL)
	#define EXP_STI_CursorClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorClose", (RTS_UINTPTR)STI_CursorClose, 0, 0) 
#endif



STI_ROW CDECL STI_CursorGetCurrentRow(STI_CURSOR hCursor, STO_ERROR *peError);
typedef STI_ROW (CDECL * PFSTI_CURSORGETCURRENTROW) (STI_CURSOR hCursor, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORGETCURRENTROW_NOTIMPLEMENTED)
	#define USE_STI_CursorGetCurrentRow
	#define EXT_STI_CursorGetCurrentRow
	#define GET_STI_CursorGetCurrentRow(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_CursorGetCurrentRow(p0,p1)  (STI_ROW)ERR_NOTIMPLEMENTED
	#define CHK_STI_CursorGetCurrentRow  FALSE
	#define EXP_STI_CursorGetCurrentRow  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_CursorGetCurrentRow
	#define EXT_STI_CursorGetCurrentRow
	#define GET_STI_CursorGetCurrentRow(fl)  CAL_CMGETAPI( "STI_CursorGetCurrentRow" ) 
	#define CAL_STI_CursorGetCurrentRow  STI_CursorGetCurrentRow
	#define CHK_STI_CursorGetCurrentRow  TRUE
	#define EXP_STI_CursorGetCurrentRow  CAL_CMEXPAPI( "STI_CursorGetCurrentRow" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_CursorGetCurrentRow
	#define EXT_STI_CursorGetCurrentRow
	#define GET_STI_CursorGetCurrentRow(fl)  CAL_CMGETAPI( "STI_CursorGetCurrentRow" ) 
	#define CAL_STI_CursorGetCurrentRow  STI_CursorGetCurrentRow
	#define CHK_STI_CursorGetCurrentRow  TRUE
	#define EXP_STI_CursorGetCurrentRow  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorGetCurrentRow", (RTS_UINTPTR)STI_CursorGetCurrentRow, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_CursorGetCurrentRow
	#define EXT_CmpCAAStorageSTI_CursorGetCurrentRow
	#define GET_CmpCAAStorageSTI_CursorGetCurrentRow  ERR_OK
	#define CAL_CmpCAAStorageSTI_CursorGetCurrentRow pICmpCAAStorage->ISTI_CursorGetCurrentRow
	#define CHK_CmpCAAStorageSTI_CursorGetCurrentRow (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_CursorGetCurrentRow  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_CursorGetCurrentRow
	#define EXT_STI_CursorGetCurrentRow
	#define GET_STI_CursorGetCurrentRow(fl)  CAL_CMGETAPI( "STI_CursorGetCurrentRow" ) 
	#define CAL_STI_CursorGetCurrentRow pICmpCAAStorage->ISTI_CursorGetCurrentRow
	#define CHK_STI_CursorGetCurrentRow (pICmpCAAStorage != NULL)
	#define EXP_STI_CursorGetCurrentRow  CAL_CMEXPAPI( "STI_CursorGetCurrentRow" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_CursorGetCurrentRow  PFSTI_CURSORGETCURRENTROW pfSTI_CursorGetCurrentRow;
	#define EXT_STI_CursorGetCurrentRow  extern PFSTI_CURSORGETCURRENTROW pfSTI_CursorGetCurrentRow;
	#define GET_STI_CursorGetCurrentRow(fl)  s_pfCMGetAPI2( "STI_CursorGetCurrentRow", (RTS_VOID_FCTPTR *)&pfSTI_CursorGetCurrentRow, (fl), 0, 0)
	#define CAL_STI_CursorGetCurrentRow  pfSTI_CursorGetCurrentRow
	#define CHK_STI_CursorGetCurrentRow  (pfSTI_CursorGetCurrentRow != NULL)
	#define EXP_STI_CursorGetCurrentRow  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorGetCurrentRow", (RTS_UINTPTR)STI_CursorGetCurrentRow, 0, 0) 
#endif



CAA_IDENT CDECL STI_CursorGetIndexId(STI_CURSOR hCursor, STO_ERROR *peError);
typedef CAA_IDENT (CDECL * PFSTI_CURSORGETINDEXID) (STI_CURSOR hCursor, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORGETINDEXID_NOTIMPLEMENTED)
	#define USE_STI_CursorGetIndexId
	#define EXT_STI_CursorGetIndexId
	#define GET_STI_CursorGetIndexId(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_CursorGetIndexId(p0,p1)  (CAA_IDENT)ERR_NOTIMPLEMENTED
	#define CHK_STI_CursorGetIndexId  FALSE
	#define EXP_STI_CursorGetIndexId  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_CursorGetIndexId
	#define EXT_STI_CursorGetIndexId
	#define GET_STI_CursorGetIndexId(fl)  CAL_CMGETAPI( "STI_CursorGetIndexId" ) 
	#define CAL_STI_CursorGetIndexId  STI_CursorGetIndexId
	#define CHK_STI_CursorGetIndexId  TRUE
	#define EXP_STI_CursorGetIndexId  CAL_CMEXPAPI( "STI_CursorGetIndexId" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_CursorGetIndexId
	#define EXT_STI_CursorGetIndexId
	#define GET_STI_CursorGetIndexId(fl)  CAL_CMGETAPI( "STI_CursorGetIndexId" ) 
	#define CAL_STI_CursorGetIndexId  STI_CursorGetIndexId
	#define CHK_STI_CursorGetIndexId  TRUE
	#define EXP_STI_CursorGetIndexId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorGetIndexId", (RTS_UINTPTR)STI_CursorGetIndexId, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_CursorGetIndexId
	#define EXT_CmpCAAStorageSTI_CursorGetIndexId
	#define GET_CmpCAAStorageSTI_CursorGetIndexId  ERR_OK
	#define CAL_CmpCAAStorageSTI_CursorGetIndexId pICmpCAAStorage->ISTI_CursorGetIndexId
	#define CHK_CmpCAAStorageSTI_CursorGetIndexId (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_CursorGetIndexId  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_CursorGetIndexId
	#define EXT_STI_CursorGetIndexId
	#define GET_STI_CursorGetIndexId(fl)  CAL_CMGETAPI( "STI_CursorGetIndexId" ) 
	#define CAL_STI_CursorGetIndexId pICmpCAAStorage->ISTI_CursorGetIndexId
	#define CHK_STI_CursorGetIndexId (pICmpCAAStorage != NULL)
	#define EXP_STI_CursorGetIndexId  CAL_CMEXPAPI( "STI_CursorGetIndexId" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_CursorGetIndexId  PFSTI_CURSORGETINDEXID pfSTI_CursorGetIndexId;
	#define EXT_STI_CursorGetIndexId  extern PFSTI_CURSORGETINDEXID pfSTI_CursorGetIndexId;
	#define GET_STI_CursorGetIndexId(fl)  s_pfCMGetAPI2( "STI_CursorGetIndexId", (RTS_VOID_FCTPTR *)&pfSTI_CursorGetIndexId, (fl), 0, 0)
	#define CAL_STI_CursorGetIndexId  pfSTI_CursorGetIndexId
	#define CHK_STI_CursorGetIndexId  (pfSTI_CursorGetIndexId != NULL)
	#define EXP_STI_CursorGetIndexId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorGetIndexId", (RTS_UINTPTR)STI_CursorGetIndexId, 0, 0) 
#endif



STI_STORAGE CDECL STI_CursorGetStorage(STI_CURSOR hCursor, STO_ERROR *peError);
typedef STI_STORAGE (CDECL * PFSTI_CURSORGETSTORAGE) (STI_CURSOR hCursor, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORGETSTORAGE_NOTIMPLEMENTED)
	#define USE_STI_CursorGetStorage
	#define EXT_STI_CursorGetStorage
	#define GET_STI_CursorGetStorage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_CursorGetStorage(p0,p1)  (STI_STORAGE)ERR_NOTIMPLEMENTED
	#define CHK_STI_CursorGetStorage  FALSE
	#define EXP_STI_CursorGetStorage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_CursorGetStorage
	#define EXT_STI_CursorGetStorage
	#define GET_STI_CursorGetStorage(fl)  CAL_CMGETAPI( "STI_CursorGetStorage" ) 
	#define CAL_STI_CursorGetStorage  STI_CursorGetStorage
	#define CHK_STI_CursorGetStorage  TRUE
	#define EXP_STI_CursorGetStorage  CAL_CMEXPAPI( "STI_CursorGetStorage" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_CursorGetStorage
	#define EXT_STI_CursorGetStorage
	#define GET_STI_CursorGetStorage(fl)  CAL_CMGETAPI( "STI_CursorGetStorage" ) 
	#define CAL_STI_CursorGetStorage  STI_CursorGetStorage
	#define CHK_STI_CursorGetStorage  TRUE
	#define EXP_STI_CursorGetStorage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorGetStorage", (RTS_UINTPTR)STI_CursorGetStorage, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_CursorGetStorage
	#define EXT_CmpCAAStorageSTI_CursorGetStorage
	#define GET_CmpCAAStorageSTI_CursorGetStorage  ERR_OK
	#define CAL_CmpCAAStorageSTI_CursorGetStorage pICmpCAAStorage->ISTI_CursorGetStorage
	#define CHK_CmpCAAStorageSTI_CursorGetStorage (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_CursorGetStorage  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_CursorGetStorage
	#define EXT_STI_CursorGetStorage
	#define GET_STI_CursorGetStorage(fl)  CAL_CMGETAPI( "STI_CursorGetStorage" ) 
	#define CAL_STI_CursorGetStorage pICmpCAAStorage->ISTI_CursorGetStorage
	#define CHK_STI_CursorGetStorage (pICmpCAAStorage != NULL)
	#define EXP_STI_CursorGetStorage  CAL_CMEXPAPI( "STI_CursorGetStorage" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_CursorGetStorage  PFSTI_CURSORGETSTORAGE pfSTI_CursorGetStorage;
	#define EXT_STI_CursorGetStorage  extern PFSTI_CURSORGETSTORAGE pfSTI_CursorGetStorage;
	#define GET_STI_CursorGetStorage(fl)  s_pfCMGetAPI2( "STI_CursorGetStorage", (RTS_VOID_FCTPTR *)&pfSTI_CursorGetStorage, (fl), 0, 0)
	#define CAL_STI_CursorGetStorage  pfSTI_CursorGetStorage
	#define CHK_STI_CursorGetStorage  (pfSTI_CursorGetStorage != NULL)
	#define EXP_STI_CursorGetStorage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorGetStorage", (RTS_UINTPTR)STI_CursorGetStorage, 0, 0) 
#endif



STI_TABLE CDECL STI_CursorGetTable(STI_CURSOR hCursor, STO_ERROR *peError);
typedef STI_TABLE (CDECL * PFSTI_CURSORGETTABLE) (STI_CURSOR hCursor, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORGETTABLE_NOTIMPLEMENTED)
	#define USE_STI_CursorGetTable
	#define EXT_STI_CursorGetTable
	#define GET_STI_CursorGetTable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_CursorGetTable(p0,p1)  (STI_TABLE)ERR_NOTIMPLEMENTED
	#define CHK_STI_CursorGetTable  FALSE
	#define EXP_STI_CursorGetTable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_CursorGetTable
	#define EXT_STI_CursorGetTable
	#define GET_STI_CursorGetTable(fl)  CAL_CMGETAPI( "STI_CursorGetTable" ) 
	#define CAL_STI_CursorGetTable  STI_CursorGetTable
	#define CHK_STI_CursorGetTable  TRUE
	#define EXP_STI_CursorGetTable  CAL_CMEXPAPI( "STI_CursorGetTable" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_CursorGetTable
	#define EXT_STI_CursorGetTable
	#define GET_STI_CursorGetTable(fl)  CAL_CMGETAPI( "STI_CursorGetTable" ) 
	#define CAL_STI_CursorGetTable  STI_CursorGetTable
	#define CHK_STI_CursorGetTable  TRUE
	#define EXP_STI_CursorGetTable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorGetTable", (RTS_UINTPTR)STI_CursorGetTable, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_CursorGetTable
	#define EXT_CmpCAAStorageSTI_CursorGetTable
	#define GET_CmpCAAStorageSTI_CursorGetTable  ERR_OK
	#define CAL_CmpCAAStorageSTI_CursorGetTable pICmpCAAStorage->ISTI_CursorGetTable
	#define CHK_CmpCAAStorageSTI_CursorGetTable (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_CursorGetTable  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_CursorGetTable
	#define EXT_STI_CursorGetTable
	#define GET_STI_CursorGetTable(fl)  CAL_CMGETAPI( "STI_CursorGetTable" ) 
	#define CAL_STI_CursorGetTable pICmpCAAStorage->ISTI_CursorGetTable
	#define CHK_STI_CursorGetTable (pICmpCAAStorage != NULL)
	#define EXP_STI_CursorGetTable  CAL_CMEXPAPI( "STI_CursorGetTable" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_CursorGetTable  PFSTI_CURSORGETTABLE pfSTI_CursorGetTable;
	#define EXT_STI_CursorGetTable  extern PFSTI_CURSORGETTABLE pfSTI_CursorGetTable;
	#define GET_STI_CursorGetTable(fl)  s_pfCMGetAPI2( "STI_CursorGetTable", (RTS_VOID_FCTPTR *)&pfSTI_CursorGetTable, (fl), 0, 0)
	#define CAL_STI_CursorGetTable  pfSTI_CursorGetTable
	#define CHK_STI_CursorGetTable  (pfSTI_CursorGetTable != NULL)
	#define EXP_STI_CursorGetTable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorGetTable", (RTS_UINTPTR)STI_CursorGetTable, 0, 0) 
#endif



CAA_BOOL CDECL STI_CursorIsReadOnly(STI_CURSOR hCursor, STO_ERROR *peError);
typedef CAA_BOOL (CDECL * PFSTI_CURSORISREADONLY) (STI_CURSOR hCursor, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORISREADONLY_NOTIMPLEMENTED)
	#define USE_STI_CursorIsReadOnly
	#define EXT_STI_CursorIsReadOnly
	#define GET_STI_CursorIsReadOnly(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_CursorIsReadOnly(p0,p1)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_STI_CursorIsReadOnly  FALSE
	#define EXP_STI_CursorIsReadOnly  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_CursorIsReadOnly
	#define EXT_STI_CursorIsReadOnly
	#define GET_STI_CursorIsReadOnly(fl)  CAL_CMGETAPI( "STI_CursorIsReadOnly" ) 
	#define CAL_STI_CursorIsReadOnly  STI_CursorIsReadOnly
	#define CHK_STI_CursorIsReadOnly  TRUE
	#define EXP_STI_CursorIsReadOnly  CAL_CMEXPAPI( "STI_CursorIsReadOnly" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_CursorIsReadOnly
	#define EXT_STI_CursorIsReadOnly
	#define GET_STI_CursorIsReadOnly(fl)  CAL_CMGETAPI( "STI_CursorIsReadOnly" ) 
	#define CAL_STI_CursorIsReadOnly  STI_CursorIsReadOnly
	#define CHK_STI_CursorIsReadOnly  TRUE
	#define EXP_STI_CursorIsReadOnly  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorIsReadOnly", (RTS_UINTPTR)STI_CursorIsReadOnly, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_CursorIsReadOnly
	#define EXT_CmpCAAStorageSTI_CursorIsReadOnly
	#define GET_CmpCAAStorageSTI_CursorIsReadOnly  ERR_OK
	#define CAL_CmpCAAStorageSTI_CursorIsReadOnly pICmpCAAStorage->ISTI_CursorIsReadOnly
	#define CHK_CmpCAAStorageSTI_CursorIsReadOnly (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_CursorIsReadOnly  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_CursorIsReadOnly
	#define EXT_STI_CursorIsReadOnly
	#define GET_STI_CursorIsReadOnly(fl)  CAL_CMGETAPI( "STI_CursorIsReadOnly" ) 
	#define CAL_STI_CursorIsReadOnly pICmpCAAStorage->ISTI_CursorIsReadOnly
	#define CHK_STI_CursorIsReadOnly (pICmpCAAStorage != NULL)
	#define EXP_STI_CursorIsReadOnly  CAL_CMEXPAPI( "STI_CursorIsReadOnly" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_CursorIsReadOnly  PFSTI_CURSORISREADONLY pfSTI_CursorIsReadOnly;
	#define EXT_STI_CursorIsReadOnly  extern PFSTI_CURSORISREADONLY pfSTI_CursorIsReadOnly;
	#define GET_STI_CursorIsReadOnly(fl)  s_pfCMGetAPI2( "STI_CursorIsReadOnly", (RTS_VOID_FCTPTR *)&pfSTI_CursorIsReadOnly, (fl), 0, 0)
	#define CAL_STI_CursorIsReadOnly  pfSTI_CursorIsReadOnly
	#define CHK_STI_CursorIsReadOnly  (pfSTI_CursorIsReadOnly != NULL)
	#define EXP_STI_CursorIsReadOnly  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorIsReadOnly", (RTS_UINTPTR)STI_CursorIsReadOnly, 0, 0) 
#endif



STO_ERROR CDECL STI_CursorMove(STI_CURSOR hCursor, STO_DIRECTION eDirection);
typedef STO_ERROR (CDECL * PFSTI_CURSORMOVE) (STI_CURSOR hCursor, STO_DIRECTION eDirection);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORMOVE_NOTIMPLEMENTED)
	#define USE_STI_CursorMove
	#define EXT_STI_CursorMove
	#define GET_STI_CursorMove(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_CursorMove(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_CursorMove  FALSE
	#define EXP_STI_CursorMove  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_CursorMove
	#define EXT_STI_CursorMove
	#define GET_STI_CursorMove(fl)  CAL_CMGETAPI( "STI_CursorMove" ) 
	#define CAL_STI_CursorMove  STI_CursorMove
	#define CHK_STI_CursorMove  TRUE
	#define EXP_STI_CursorMove  CAL_CMEXPAPI( "STI_CursorMove" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_CursorMove
	#define EXT_STI_CursorMove
	#define GET_STI_CursorMove(fl)  CAL_CMGETAPI( "STI_CursorMove" ) 
	#define CAL_STI_CursorMove  STI_CursorMove
	#define CHK_STI_CursorMove  TRUE
	#define EXP_STI_CursorMove  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorMove", (RTS_UINTPTR)STI_CursorMove, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_CursorMove
	#define EXT_CmpCAAStorageSTI_CursorMove
	#define GET_CmpCAAStorageSTI_CursorMove  ERR_OK
	#define CAL_CmpCAAStorageSTI_CursorMove pICmpCAAStorage->ISTI_CursorMove
	#define CHK_CmpCAAStorageSTI_CursorMove (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_CursorMove  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_CursorMove
	#define EXT_STI_CursorMove
	#define GET_STI_CursorMove(fl)  CAL_CMGETAPI( "STI_CursorMove" ) 
	#define CAL_STI_CursorMove pICmpCAAStorage->ISTI_CursorMove
	#define CHK_STI_CursorMove (pICmpCAAStorage != NULL)
	#define EXP_STI_CursorMove  CAL_CMEXPAPI( "STI_CursorMove" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_CursorMove  PFSTI_CURSORMOVE pfSTI_CursorMove;
	#define EXT_STI_CursorMove  extern PFSTI_CURSORMOVE pfSTI_CursorMove;
	#define GET_STI_CursorMove(fl)  s_pfCMGetAPI2( "STI_CursorMove", (RTS_VOID_FCTPTR *)&pfSTI_CursorMove, (fl), 0, 0)
	#define CAL_STI_CursorMove  pfSTI_CursorMove
	#define CHK_STI_CursorMove  (pfSTI_CursorMove != NULL)
	#define EXP_STI_CursorMove  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorMove", (RTS_UINTPTR)STI_CursorMove, 0, 0) 
#endif



STI_CURSOR CDECL STI_CursorOpen(STI_TABLE hTable, CAA_IDENT idIndex, CAA_BOOL xReadOnly, STO_ERROR *peError);
typedef STI_CURSOR (CDECL * PFSTI_CURSOROPEN) (STI_TABLE hTable, CAA_IDENT idIndex, CAA_BOOL xReadOnly, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSOROPEN_NOTIMPLEMENTED)
	#define USE_STI_CursorOpen
	#define EXT_STI_CursorOpen
	#define GET_STI_CursorOpen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_CursorOpen(p0,p1,p2,p3)  (STI_CURSOR)ERR_NOTIMPLEMENTED
	#define CHK_STI_CursorOpen  FALSE
	#define EXP_STI_CursorOpen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_CursorOpen
	#define EXT_STI_CursorOpen
	#define GET_STI_CursorOpen(fl)  CAL_CMGETAPI( "STI_CursorOpen" ) 
	#define CAL_STI_CursorOpen  STI_CursorOpen
	#define CHK_STI_CursorOpen  TRUE
	#define EXP_STI_CursorOpen  CAL_CMEXPAPI( "STI_CursorOpen" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_CursorOpen
	#define EXT_STI_CursorOpen
	#define GET_STI_CursorOpen(fl)  CAL_CMGETAPI( "STI_CursorOpen" ) 
	#define CAL_STI_CursorOpen  STI_CursorOpen
	#define CHK_STI_CursorOpen  TRUE
	#define EXP_STI_CursorOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorOpen", (RTS_UINTPTR)STI_CursorOpen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_CursorOpen
	#define EXT_CmpCAAStorageSTI_CursorOpen
	#define GET_CmpCAAStorageSTI_CursorOpen  ERR_OK
	#define CAL_CmpCAAStorageSTI_CursorOpen pICmpCAAStorage->ISTI_CursorOpen
	#define CHK_CmpCAAStorageSTI_CursorOpen (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_CursorOpen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_CursorOpen
	#define EXT_STI_CursorOpen
	#define GET_STI_CursorOpen(fl)  CAL_CMGETAPI( "STI_CursorOpen" ) 
	#define CAL_STI_CursorOpen pICmpCAAStorage->ISTI_CursorOpen
	#define CHK_STI_CursorOpen (pICmpCAAStorage != NULL)
	#define EXP_STI_CursorOpen  CAL_CMEXPAPI( "STI_CursorOpen" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_CursorOpen  PFSTI_CURSOROPEN pfSTI_CursorOpen;
	#define EXT_STI_CursorOpen  extern PFSTI_CURSOROPEN pfSTI_CursorOpen;
	#define GET_STI_CursorOpen(fl)  s_pfCMGetAPI2( "STI_CursorOpen", (RTS_VOID_FCTPTR *)&pfSTI_CursorOpen, (fl), 0, 0)
	#define CAL_STI_CursorOpen  pfSTI_CursorOpen
	#define CHK_STI_CursorOpen  (pfSTI_CursorOpen != NULL)
	#define EXP_STI_CursorOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorOpen", (RTS_UINTPTR)STI_CursorOpen, 0, 0) 
#endif



STO_ERROR CDECL STI_CursorSearchINT16(STI_CURSOR hCursor, CAA_INT iValue);
typedef STO_ERROR (CDECL * PFSTI_CURSORSEARCHINT16) (STI_CURSOR hCursor, CAA_INT iValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORSEARCHINT16_NOTIMPLEMENTED)
	#define USE_STI_CursorSearchINT16
	#define EXT_STI_CursorSearchINT16
	#define GET_STI_CursorSearchINT16(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_CursorSearchINT16(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_CursorSearchINT16  FALSE
	#define EXP_STI_CursorSearchINT16  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_CursorSearchINT16
	#define EXT_STI_CursorSearchINT16
	#define GET_STI_CursorSearchINT16(fl)  CAL_CMGETAPI( "STI_CursorSearchINT16" ) 
	#define CAL_STI_CursorSearchINT16  STI_CursorSearchINT16
	#define CHK_STI_CursorSearchINT16  TRUE
	#define EXP_STI_CursorSearchINT16  CAL_CMEXPAPI( "STI_CursorSearchINT16" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_CursorSearchINT16
	#define EXT_STI_CursorSearchINT16
	#define GET_STI_CursorSearchINT16(fl)  CAL_CMGETAPI( "STI_CursorSearchINT16" ) 
	#define CAL_STI_CursorSearchINT16  STI_CursorSearchINT16
	#define CHK_STI_CursorSearchINT16  TRUE
	#define EXP_STI_CursorSearchINT16  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorSearchINT16", (RTS_UINTPTR)STI_CursorSearchINT16, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_CursorSearchINT16
	#define EXT_CmpCAAStorageSTI_CursorSearchINT16
	#define GET_CmpCAAStorageSTI_CursorSearchINT16  ERR_OK
	#define CAL_CmpCAAStorageSTI_CursorSearchINT16 pICmpCAAStorage->ISTI_CursorSearchINT16
	#define CHK_CmpCAAStorageSTI_CursorSearchINT16 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_CursorSearchINT16  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_CursorSearchINT16
	#define EXT_STI_CursorSearchINT16
	#define GET_STI_CursorSearchINT16(fl)  CAL_CMGETAPI( "STI_CursorSearchINT16" ) 
	#define CAL_STI_CursorSearchINT16 pICmpCAAStorage->ISTI_CursorSearchINT16
	#define CHK_STI_CursorSearchINT16 (pICmpCAAStorage != NULL)
	#define EXP_STI_CursorSearchINT16  CAL_CMEXPAPI( "STI_CursorSearchINT16" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_CursorSearchINT16  PFSTI_CURSORSEARCHINT16 pfSTI_CursorSearchINT16;
	#define EXT_STI_CursorSearchINT16  extern PFSTI_CURSORSEARCHINT16 pfSTI_CursorSearchINT16;
	#define GET_STI_CursorSearchINT16(fl)  s_pfCMGetAPI2( "STI_CursorSearchINT16", (RTS_VOID_FCTPTR *)&pfSTI_CursorSearchINT16, (fl), 0, 0)
	#define CAL_STI_CursorSearchINT16  pfSTI_CursorSearchINT16
	#define CHK_STI_CursorSearchINT16  (pfSTI_CursorSearchINT16 != NULL)
	#define EXP_STI_CursorSearchINT16  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorSearchINT16", (RTS_UINTPTR)STI_CursorSearchINT16, 0, 0) 
#endif



STO_ERROR CDECL STI_CursorSearchINT32(STI_CURSOR hCursor, CAA_DINT diValue);
typedef STO_ERROR (CDECL * PFSTI_CURSORSEARCHINT32) (STI_CURSOR hCursor, CAA_DINT diValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORSEARCHINT32_NOTIMPLEMENTED)
	#define USE_STI_CursorSearchINT32
	#define EXT_STI_CursorSearchINT32
	#define GET_STI_CursorSearchINT32(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_CursorSearchINT32(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_CursorSearchINT32  FALSE
	#define EXP_STI_CursorSearchINT32  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_CursorSearchINT32
	#define EXT_STI_CursorSearchINT32
	#define GET_STI_CursorSearchINT32(fl)  CAL_CMGETAPI( "STI_CursorSearchINT32" ) 
	#define CAL_STI_CursorSearchINT32  STI_CursorSearchINT32
	#define CHK_STI_CursorSearchINT32  TRUE
	#define EXP_STI_CursorSearchINT32  CAL_CMEXPAPI( "STI_CursorSearchINT32" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_CursorSearchINT32
	#define EXT_STI_CursorSearchINT32
	#define GET_STI_CursorSearchINT32(fl)  CAL_CMGETAPI( "STI_CursorSearchINT32" ) 
	#define CAL_STI_CursorSearchINT32  STI_CursorSearchINT32
	#define CHK_STI_CursorSearchINT32  TRUE
	#define EXP_STI_CursorSearchINT32  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorSearchINT32", (RTS_UINTPTR)STI_CursorSearchINT32, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_CursorSearchINT32
	#define EXT_CmpCAAStorageSTI_CursorSearchINT32
	#define GET_CmpCAAStorageSTI_CursorSearchINT32  ERR_OK
	#define CAL_CmpCAAStorageSTI_CursorSearchINT32 pICmpCAAStorage->ISTI_CursorSearchINT32
	#define CHK_CmpCAAStorageSTI_CursorSearchINT32 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_CursorSearchINT32  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_CursorSearchINT32
	#define EXT_STI_CursorSearchINT32
	#define GET_STI_CursorSearchINT32(fl)  CAL_CMGETAPI( "STI_CursorSearchINT32" ) 
	#define CAL_STI_CursorSearchINT32 pICmpCAAStorage->ISTI_CursorSearchINT32
	#define CHK_STI_CursorSearchINT32 (pICmpCAAStorage != NULL)
	#define EXP_STI_CursorSearchINT32  CAL_CMEXPAPI( "STI_CursorSearchINT32" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_CursorSearchINT32  PFSTI_CURSORSEARCHINT32 pfSTI_CursorSearchINT32;
	#define EXT_STI_CursorSearchINT32  extern PFSTI_CURSORSEARCHINT32 pfSTI_CursorSearchINT32;
	#define GET_STI_CursorSearchINT32(fl)  s_pfCMGetAPI2( "STI_CursorSearchINT32", (RTS_VOID_FCTPTR *)&pfSTI_CursorSearchINT32, (fl), 0, 0)
	#define CAL_STI_CursorSearchINT32  pfSTI_CursorSearchINT32
	#define CHK_STI_CursorSearchINT32  (pfSTI_CursorSearchINT32 != NULL)
	#define EXP_STI_CursorSearchINT32  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorSearchINT32", (RTS_UINTPTR)STI_CursorSearchINT32, 0, 0) 
#endif



STO_ERROR CDECL STI_CursorSearchINT64(STI_CURSOR hCursor, CAA_LINT liValue);
typedef STO_ERROR (CDECL * PFSTI_CURSORSEARCHINT64) (STI_CURSOR hCursor, CAA_LINT liValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORSEARCHINT64_NOTIMPLEMENTED)
	#define USE_STI_CursorSearchINT64
	#define EXT_STI_CursorSearchINT64
	#define GET_STI_CursorSearchINT64(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_CursorSearchINT64(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_CursorSearchINT64  FALSE
	#define EXP_STI_CursorSearchINT64  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_CursorSearchINT64
	#define EXT_STI_CursorSearchINT64
	#define GET_STI_CursorSearchINT64(fl)  CAL_CMGETAPI( "STI_CursorSearchINT64" ) 
	#define CAL_STI_CursorSearchINT64  STI_CursorSearchINT64
	#define CHK_STI_CursorSearchINT64  TRUE
	#define EXP_STI_CursorSearchINT64  CAL_CMEXPAPI( "STI_CursorSearchINT64" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_CursorSearchINT64
	#define EXT_STI_CursorSearchINT64
	#define GET_STI_CursorSearchINT64(fl)  CAL_CMGETAPI( "STI_CursorSearchINT64" ) 
	#define CAL_STI_CursorSearchINT64  STI_CursorSearchINT64
	#define CHK_STI_CursorSearchINT64  TRUE
	#define EXP_STI_CursorSearchINT64  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorSearchINT64", (RTS_UINTPTR)STI_CursorSearchINT64, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_CursorSearchINT64
	#define EXT_CmpCAAStorageSTI_CursorSearchINT64
	#define GET_CmpCAAStorageSTI_CursorSearchINT64  ERR_OK
	#define CAL_CmpCAAStorageSTI_CursorSearchINT64 pICmpCAAStorage->ISTI_CursorSearchINT64
	#define CHK_CmpCAAStorageSTI_CursorSearchINT64 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_CursorSearchINT64  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_CursorSearchINT64
	#define EXT_STI_CursorSearchINT64
	#define GET_STI_CursorSearchINT64(fl)  CAL_CMGETAPI( "STI_CursorSearchINT64" ) 
	#define CAL_STI_CursorSearchINT64 pICmpCAAStorage->ISTI_CursorSearchINT64
	#define CHK_STI_CursorSearchINT64 (pICmpCAAStorage != NULL)
	#define EXP_STI_CursorSearchINT64  CAL_CMEXPAPI( "STI_CursorSearchINT64" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_CursorSearchINT64  PFSTI_CURSORSEARCHINT64 pfSTI_CursorSearchINT64;
	#define EXT_STI_CursorSearchINT64  extern PFSTI_CURSORSEARCHINT64 pfSTI_CursorSearchINT64;
	#define GET_STI_CursorSearchINT64(fl)  s_pfCMGetAPI2( "STI_CursorSearchINT64", (RTS_VOID_FCTPTR *)&pfSTI_CursorSearchINT64, (fl), 0, 0)
	#define CAL_STI_CursorSearchINT64  pfSTI_CursorSearchINT64
	#define CHK_STI_CursorSearchINT64  (pfSTI_CursorSearchINT64 != NULL)
	#define EXP_STI_CursorSearchINT64  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorSearchINT64", (RTS_UINTPTR)STI_CursorSearchINT64, 0, 0) 
#endif



STO_ERROR CDECL STI_CursorSearchINT8(STI_CURSOR hCursor, CAA_SINT siValue);
typedef STO_ERROR (CDECL * PFSTI_CURSORSEARCHINT8) (STI_CURSOR hCursor, CAA_SINT siValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORSEARCHINT8_NOTIMPLEMENTED)
	#define USE_STI_CursorSearchINT8
	#define EXT_STI_CursorSearchINT8
	#define GET_STI_CursorSearchINT8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_CursorSearchINT8(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_CursorSearchINT8  FALSE
	#define EXP_STI_CursorSearchINT8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_CursorSearchINT8
	#define EXT_STI_CursorSearchINT8
	#define GET_STI_CursorSearchINT8(fl)  CAL_CMGETAPI( "STI_CursorSearchINT8" ) 
	#define CAL_STI_CursorSearchINT8  STI_CursorSearchINT8
	#define CHK_STI_CursorSearchINT8  TRUE
	#define EXP_STI_CursorSearchINT8  CAL_CMEXPAPI( "STI_CursorSearchINT8" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_CursorSearchINT8
	#define EXT_STI_CursorSearchINT8
	#define GET_STI_CursorSearchINT8(fl)  CAL_CMGETAPI( "STI_CursorSearchINT8" ) 
	#define CAL_STI_CursorSearchINT8  STI_CursorSearchINT8
	#define CHK_STI_CursorSearchINT8  TRUE
	#define EXP_STI_CursorSearchINT8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorSearchINT8", (RTS_UINTPTR)STI_CursorSearchINT8, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_CursorSearchINT8
	#define EXT_CmpCAAStorageSTI_CursorSearchINT8
	#define GET_CmpCAAStorageSTI_CursorSearchINT8  ERR_OK
	#define CAL_CmpCAAStorageSTI_CursorSearchINT8 pICmpCAAStorage->ISTI_CursorSearchINT8
	#define CHK_CmpCAAStorageSTI_CursorSearchINT8 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_CursorSearchINT8  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_CursorSearchINT8
	#define EXT_STI_CursorSearchINT8
	#define GET_STI_CursorSearchINT8(fl)  CAL_CMGETAPI( "STI_CursorSearchINT8" ) 
	#define CAL_STI_CursorSearchINT8 pICmpCAAStorage->ISTI_CursorSearchINT8
	#define CHK_STI_CursorSearchINT8 (pICmpCAAStorage != NULL)
	#define EXP_STI_CursorSearchINT8  CAL_CMEXPAPI( "STI_CursorSearchINT8" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_CursorSearchINT8  PFSTI_CURSORSEARCHINT8 pfSTI_CursorSearchINT8;
	#define EXT_STI_CursorSearchINT8  extern PFSTI_CURSORSEARCHINT8 pfSTI_CursorSearchINT8;
	#define GET_STI_CursorSearchINT8(fl)  s_pfCMGetAPI2( "STI_CursorSearchINT8", (RTS_VOID_FCTPTR *)&pfSTI_CursorSearchINT8, (fl), 0, 0)
	#define CAL_STI_CursorSearchINT8  pfSTI_CursorSearchINT8
	#define CHK_STI_CursorSearchINT8  (pfSTI_CursorSearchINT8 != NULL)
	#define EXP_STI_CursorSearchINT8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorSearchINT8", (RTS_UINTPTR)STI_CursorSearchINT8, 0, 0) 
#endif



STO_ERROR CDECL STI_CursorSearchNULL(STI_CURSOR hCursor);
typedef STO_ERROR (CDECL * PFSTI_CURSORSEARCHNULL) (STI_CURSOR hCursor);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORSEARCHNULL_NOTIMPLEMENTED)
	#define USE_STI_CursorSearchNULL
	#define EXT_STI_CursorSearchNULL
	#define GET_STI_CursorSearchNULL(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_CursorSearchNULL(p0)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_CursorSearchNULL  FALSE
	#define EXP_STI_CursorSearchNULL  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_CursorSearchNULL
	#define EXT_STI_CursorSearchNULL
	#define GET_STI_CursorSearchNULL(fl)  CAL_CMGETAPI( "STI_CursorSearchNULL" ) 
	#define CAL_STI_CursorSearchNULL  STI_CursorSearchNULL
	#define CHK_STI_CursorSearchNULL  TRUE
	#define EXP_STI_CursorSearchNULL  CAL_CMEXPAPI( "STI_CursorSearchNULL" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_CursorSearchNULL
	#define EXT_STI_CursorSearchNULL
	#define GET_STI_CursorSearchNULL(fl)  CAL_CMGETAPI( "STI_CursorSearchNULL" ) 
	#define CAL_STI_CursorSearchNULL  STI_CursorSearchNULL
	#define CHK_STI_CursorSearchNULL  TRUE
	#define EXP_STI_CursorSearchNULL  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorSearchNULL", (RTS_UINTPTR)STI_CursorSearchNULL, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_CursorSearchNULL
	#define EXT_CmpCAAStorageSTI_CursorSearchNULL
	#define GET_CmpCAAStorageSTI_CursorSearchNULL  ERR_OK
	#define CAL_CmpCAAStorageSTI_CursorSearchNULL pICmpCAAStorage->ISTI_CursorSearchNULL
	#define CHK_CmpCAAStorageSTI_CursorSearchNULL (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_CursorSearchNULL  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_CursorSearchNULL
	#define EXT_STI_CursorSearchNULL
	#define GET_STI_CursorSearchNULL(fl)  CAL_CMGETAPI( "STI_CursorSearchNULL" ) 
	#define CAL_STI_CursorSearchNULL pICmpCAAStorage->ISTI_CursorSearchNULL
	#define CHK_STI_CursorSearchNULL (pICmpCAAStorage != NULL)
	#define EXP_STI_CursorSearchNULL  CAL_CMEXPAPI( "STI_CursorSearchNULL" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_CursorSearchNULL  PFSTI_CURSORSEARCHNULL pfSTI_CursorSearchNULL;
	#define EXT_STI_CursorSearchNULL  extern PFSTI_CURSORSEARCHNULL pfSTI_CursorSearchNULL;
	#define GET_STI_CursorSearchNULL(fl)  s_pfCMGetAPI2( "STI_CursorSearchNULL", (RTS_VOID_FCTPTR *)&pfSTI_CursorSearchNULL, (fl), 0, 0)
	#define CAL_STI_CursorSearchNULL  pfSTI_CursorSearchNULL
	#define CHK_STI_CursorSearchNULL  (pfSTI_CursorSearchNULL != NULL)
	#define EXP_STI_CursorSearchNULL  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorSearchNULL", (RTS_UINTPTR)STI_CursorSearchNULL, 0, 0) 
#endif



STO_ERROR CDECL STI_CursorSearchREAL4(STI_CURSOR hCursor, CAA_REAL rValue);
typedef STO_ERROR (CDECL * PFSTI_CURSORSEARCHREAL4) (STI_CURSOR hCursor, CAA_REAL rValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORSEARCHREAL4_NOTIMPLEMENTED)
	#define USE_STI_CursorSearchREAL4
	#define EXT_STI_CursorSearchREAL4
	#define GET_STI_CursorSearchREAL4(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_CursorSearchREAL4(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_CursorSearchREAL4  FALSE
	#define EXP_STI_CursorSearchREAL4  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_CursorSearchREAL4
	#define EXT_STI_CursorSearchREAL4
	#define GET_STI_CursorSearchREAL4(fl)  CAL_CMGETAPI( "STI_CursorSearchREAL4" ) 
	#define CAL_STI_CursorSearchREAL4  STI_CursorSearchREAL4
	#define CHK_STI_CursorSearchREAL4  TRUE
	#define EXP_STI_CursorSearchREAL4  CAL_CMEXPAPI( "STI_CursorSearchREAL4" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_CursorSearchREAL4
	#define EXT_STI_CursorSearchREAL4
	#define GET_STI_CursorSearchREAL4(fl)  CAL_CMGETAPI( "STI_CursorSearchREAL4" ) 
	#define CAL_STI_CursorSearchREAL4  STI_CursorSearchREAL4
	#define CHK_STI_CursorSearchREAL4  TRUE
	#define EXP_STI_CursorSearchREAL4  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorSearchREAL4", (RTS_UINTPTR)STI_CursorSearchREAL4, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_CursorSearchREAL4
	#define EXT_CmpCAAStorageSTI_CursorSearchREAL4
	#define GET_CmpCAAStorageSTI_CursorSearchREAL4  ERR_OK
	#define CAL_CmpCAAStorageSTI_CursorSearchREAL4 pICmpCAAStorage->ISTI_CursorSearchREAL4
	#define CHK_CmpCAAStorageSTI_CursorSearchREAL4 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_CursorSearchREAL4  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_CursorSearchREAL4
	#define EXT_STI_CursorSearchREAL4
	#define GET_STI_CursorSearchREAL4(fl)  CAL_CMGETAPI( "STI_CursorSearchREAL4" ) 
	#define CAL_STI_CursorSearchREAL4 pICmpCAAStorage->ISTI_CursorSearchREAL4
	#define CHK_STI_CursorSearchREAL4 (pICmpCAAStorage != NULL)
	#define EXP_STI_CursorSearchREAL4  CAL_CMEXPAPI( "STI_CursorSearchREAL4" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_CursorSearchREAL4  PFSTI_CURSORSEARCHREAL4 pfSTI_CursorSearchREAL4;
	#define EXT_STI_CursorSearchREAL4  extern PFSTI_CURSORSEARCHREAL4 pfSTI_CursorSearchREAL4;
	#define GET_STI_CursorSearchREAL4(fl)  s_pfCMGetAPI2( "STI_CursorSearchREAL4", (RTS_VOID_FCTPTR *)&pfSTI_CursorSearchREAL4, (fl), 0, 0)
	#define CAL_STI_CursorSearchREAL4  pfSTI_CursorSearchREAL4
	#define CHK_STI_CursorSearchREAL4  (pfSTI_CursorSearchREAL4 != NULL)
	#define EXP_STI_CursorSearchREAL4  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorSearchREAL4", (RTS_UINTPTR)STI_CursorSearchREAL4, 0, 0) 
#endif



STO_ERROR CDECL STI_CursorSearchREAL8(STI_CURSOR hCursor, CAA_LREAL lrValue);
typedef STO_ERROR (CDECL * PFSTI_CURSORSEARCHREAL8) (STI_CURSOR hCursor, CAA_LREAL lrValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORSEARCHREAL8_NOTIMPLEMENTED)
	#define USE_STI_CursorSearchREAL8
	#define EXT_STI_CursorSearchREAL8
	#define GET_STI_CursorSearchREAL8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_CursorSearchREAL8(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_CursorSearchREAL8  FALSE
	#define EXP_STI_CursorSearchREAL8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_CursorSearchREAL8
	#define EXT_STI_CursorSearchREAL8
	#define GET_STI_CursorSearchREAL8(fl)  CAL_CMGETAPI( "STI_CursorSearchREAL8" ) 
	#define CAL_STI_CursorSearchREAL8  STI_CursorSearchREAL8
	#define CHK_STI_CursorSearchREAL8  TRUE
	#define EXP_STI_CursorSearchREAL8  CAL_CMEXPAPI( "STI_CursorSearchREAL8" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_CursorSearchREAL8
	#define EXT_STI_CursorSearchREAL8
	#define GET_STI_CursorSearchREAL8(fl)  CAL_CMGETAPI( "STI_CursorSearchREAL8" ) 
	#define CAL_STI_CursorSearchREAL8  STI_CursorSearchREAL8
	#define CHK_STI_CursorSearchREAL8  TRUE
	#define EXP_STI_CursorSearchREAL8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorSearchREAL8", (RTS_UINTPTR)STI_CursorSearchREAL8, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_CursorSearchREAL8
	#define EXT_CmpCAAStorageSTI_CursorSearchREAL8
	#define GET_CmpCAAStorageSTI_CursorSearchREAL8  ERR_OK
	#define CAL_CmpCAAStorageSTI_CursorSearchREAL8 pICmpCAAStorage->ISTI_CursorSearchREAL8
	#define CHK_CmpCAAStorageSTI_CursorSearchREAL8 (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_CursorSearchREAL8  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_CursorSearchREAL8
	#define EXT_STI_CursorSearchREAL8
	#define GET_STI_CursorSearchREAL8(fl)  CAL_CMGETAPI( "STI_CursorSearchREAL8" ) 
	#define CAL_STI_CursorSearchREAL8 pICmpCAAStorage->ISTI_CursorSearchREAL8
	#define CHK_STI_CursorSearchREAL8 (pICmpCAAStorage != NULL)
	#define EXP_STI_CursorSearchREAL8  CAL_CMEXPAPI( "STI_CursorSearchREAL8" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_CursorSearchREAL8  PFSTI_CURSORSEARCHREAL8 pfSTI_CursorSearchREAL8;
	#define EXT_STI_CursorSearchREAL8  extern PFSTI_CURSORSEARCHREAL8 pfSTI_CursorSearchREAL8;
	#define GET_STI_CursorSearchREAL8(fl)  s_pfCMGetAPI2( "STI_CursorSearchREAL8", (RTS_VOID_FCTPTR *)&pfSTI_CursorSearchREAL8, (fl), 0, 0)
	#define CAL_STI_CursorSearchREAL8  pfSTI_CursorSearchREAL8
	#define CHK_STI_CursorSearchREAL8  (pfSTI_CursorSearchREAL8 != NULL)
	#define EXP_STI_CursorSearchREAL8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorSearchREAL8", (RTS_UINTPTR)STI_CursorSearchREAL8, 0, 0) 
#endif



STO_ERROR CDECL STI_CursorSearchRowId(STI_CURSOR hCursor, CAA_LINT idRow);
typedef STO_ERROR (CDECL * PFSTI_CURSORSEARCHROWID) (STI_CURSOR hCursor, CAA_LINT idRow);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORSEARCHROWID_NOTIMPLEMENTED)
	#define USE_STI_CursorSearchRowId
	#define EXT_STI_CursorSearchRowId
	#define GET_STI_CursorSearchRowId(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_CursorSearchRowId(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_CursorSearchRowId  FALSE
	#define EXP_STI_CursorSearchRowId  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_CursorSearchRowId
	#define EXT_STI_CursorSearchRowId
	#define GET_STI_CursorSearchRowId(fl)  CAL_CMGETAPI( "STI_CursorSearchRowId" ) 
	#define CAL_STI_CursorSearchRowId  STI_CursorSearchRowId
	#define CHK_STI_CursorSearchRowId  TRUE
	#define EXP_STI_CursorSearchRowId  CAL_CMEXPAPI( "STI_CursorSearchRowId" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_CursorSearchRowId
	#define EXT_STI_CursorSearchRowId
	#define GET_STI_CursorSearchRowId(fl)  CAL_CMGETAPI( "STI_CursorSearchRowId" ) 
	#define CAL_STI_CursorSearchRowId  STI_CursorSearchRowId
	#define CHK_STI_CursorSearchRowId  TRUE
	#define EXP_STI_CursorSearchRowId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorSearchRowId", (RTS_UINTPTR)STI_CursorSearchRowId, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_CursorSearchRowId
	#define EXT_CmpCAAStorageSTI_CursorSearchRowId
	#define GET_CmpCAAStorageSTI_CursorSearchRowId  ERR_OK
	#define CAL_CmpCAAStorageSTI_CursorSearchRowId pICmpCAAStorage->ISTI_CursorSearchRowId
	#define CHK_CmpCAAStorageSTI_CursorSearchRowId (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_CursorSearchRowId  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_CursorSearchRowId
	#define EXT_STI_CursorSearchRowId
	#define GET_STI_CursorSearchRowId(fl)  CAL_CMGETAPI( "STI_CursorSearchRowId" ) 
	#define CAL_STI_CursorSearchRowId pICmpCAAStorage->ISTI_CursorSearchRowId
	#define CHK_STI_CursorSearchRowId (pICmpCAAStorage != NULL)
	#define EXP_STI_CursorSearchRowId  CAL_CMEXPAPI( "STI_CursorSearchRowId" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_CursorSearchRowId  PFSTI_CURSORSEARCHROWID pfSTI_CursorSearchRowId;
	#define EXT_STI_CursorSearchRowId  extern PFSTI_CURSORSEARCHROWID pfSTI_CursorSearchRowId;
	#define GET_STI_CursorSearchRowId(fl)  s_pfCMGetAPI2( "STI_CursorSearchRowId", (RTS_VOID_FCTPTR *)&pfSTI_CursorSearchRowId, (fl), 0, 0)
	#define CAL_STI_CursorSearchRowId  pfSTI_CursorSearchRowId
	#define CHK_STI_CursorSearchRowId  (pfSTI_CursorSearchRowId != NULL)
	#define EXP_STI_CursorSearchRowId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorSearchRowId", (RTS_UINTPTR)STI_CursorSearchRowId, 0, 0) 
#endif



STO_ERROR CDECL STI_CursorSearchTEXT(STI_CURSOR hCursor, STO_TEXT *ptxtValue);
typedef STO_ERROR (CDECL * PFSTI_CURSORSEARCHTEXT) (STI_CURSOR hCursor, STO_TEXT *ptxtValue);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_CURSORSEARCHTEXT_NOTIMPLEMENTED)
	#define USE_STI_CursorSearchTEXT
	#define EXT_STI_CursorSearchTEXT
	#define GET_STI_CursorSearchTEXT(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_CursorSearchTEXT(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_CursorSearchTEXT  FALSE
	#define EXP_STI_CursorSearchTEXT  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_CursorSearchTEXT
	#define EXT_STI_CursorSearchTEXT
	#define GET_STI_CursorSearchTEXT(fl)  CAL_CMGETAPI( "STI_CursorSearchTEXT" ) 
	#define CAL_STI_CursorSearchTEXT  STI_CursorSearchTEXT
	#define CHK_STI_CursorSearchTEXT  TRUE
	#define EXP_STI_CursorSearchTEXT  CAL_CMEXPAPI( "STI_CursorSearchTEXT" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_CursorSearchTEXT
	#define EXT_STI_CursorSearchTEXT
	#define GET_STI_CursorSearchTEXT(fl)  CAL_CMGETAPI( "STI_CursorSearchTEXT" ) 
	#define CAL_STI_CursorSearchTEXT  STI_CursorSearchTEXT
	#define CHK_STI_CursorSearchTEXT  TRUE
	#define EXP_STI_CursorSearchTEXT  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorSearchTEXT", (RTS_UINTPTR)STI_CursorSearchTEXT, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_CursorSearchTEXT
	#define EXT_CmpCAAStorageSTI_CursorSearchTEXT
	#define GET_CmpCAAStorageSTI_CursorSearchTEXT  ERR_OK
	#define CAL_CmpCAAStorageSTI_CursorSearchTEXT pICmpCAAStorage->ISTI_CursorSearchTEXT
	#define CHK_CmpCAAStorageSTI_CursorSearchTEXT (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_CursorSearchTEXT  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_CursorSearchTEXT
	#define EXT_STI_CursorSearchTEXT
	#define GET_STI_CursorSearchTEXT(fl)  CAL_CMGETAPI( "STI_CursorSearchTEXT" ) 
	#define CAL_STI_CursorSearchTEXT pICmpCAAStorage->ISTI_CursorSearchTEXT
	#define CHK_STI_CursorSearchTEXT (pICmpCAAStorage != NULL)
	#define EXP_STI_CursorSearchTEXT  CAL_CMEXPAPI( "STI_CursorSearchTEXT" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_CursorSearchTEXT  PFSTI_CURSORSEARCHTEXT pfSTI_CursorSearchTEXT;
	#define EXT_STI_CursorSearchTEXT  extern PFSTI_CURSORSEARCHTEXT pfSTI_CursorSearchTEXT;
	#define GET_STI_CursorSearchTEXT(fl)  s_pfCMGetAPI2( "STI_CursorSearchTEXT", (RTS_VOID_FCTPTR *)&pfSTI_CursorSearchTEXT, (fl), 0, 0)
	#define CAL_STI_CursorSearchTEXT  pfSTI_CursorSearchTEXT
	#define CHK_STI_CursorSearchTEXT  (pfSTI_CursorSearchTEXT != NULL)
	#define EXP_STI_CursorSearchTEXT  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_CursorSearchTEXT", (RTS_UINTPTR)STI_CursorSearchTEXT, 0, 0) 
#endif



STO_ERROR CDECL STI_RowClear(STI_ROW hRow);
typedef STO_ERROR (CDECL * PFSTI_ROWCLEAR) (STI_ROW hRow);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWCLEAR_NOTIMPLEMENTED)
	#define USE_STI_RowClear
	#define EXT_STI_RowClear
	#define GET_STI_RowClear(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_RowClear(p0)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_RowClear  FALSE
	#define EXP_STI_RowClear  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_RowClear
	#define EXT_STI_RowClear
	#define GET_STI_RowClear(fl)  CAL_CMGETAPI( "STI_RowClear" ) 
	#define CAL_STI_RowClear  STI_RowClear
	#define CHK_STI_RowClear  TRUE
	#define EXP_STI_RowClear  CAL_CMEXPAPI( "STI_RowClear" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_RowClear
	#define EXT_STI_RowClear
	#define GET_STI_RowClear(fl)  CAL_CMGETAPI( "STI_RowClear" ) 
	#define CAL_STI_RowClear  STI_RowClear
	#define CHK_STI_RowClear  TRUE
	#define EXP_STI_RowClear  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowClear", (RTS_UINTPTR)STI_RowClear, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_RowClear
	#define EXT_CmpCAAStorageSTI_RowClear
	#define GET_CmpCAAStorageSTI_RowClear  ERR_OK
	#define CAL_CmpCAAStorageSTI_RowClear pICmpCAAStorage->ISTI_RowClear
	#define CHK_CmpCAAStorageSTI_RowClear (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_RowClear  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_RowClear
	#define EXT_STI_RowClear
	#define GET_STI_RowClear(fl)  CAL_CMGETAPI( "STI_RowClear" ) 
	#define CAL_STI_RowClear pICmpCAAStorage->ISTI_RowClear
	#define CHK_STI_RowClear (pICmpCAAStorage != NULL)
	#define EXP_STI_RowClear  CAL_CMEXPAPI( "STI_RowClear" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_RowClear  PFSTI_ROWCLEAR pfSTI_RowClear;
	#define EXT_STI_RowClear  extern PFSTI_ROWCLEAR pfSTI_RowClear;
	#define GET_STI_RowClear(fl)  s_pfCMGetAPI2( "STI_RowClear", (RTS_VOID_FCTPTR *)&pfSTI_RowClear, (fl), 0, 0)
	#define CAL_STI_RowClear  pfSTI_RowClear
	#define CHK_STI_RowClear  (pfSTI_RowClear != NULL)
	#define EXP_STI_RowClear  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowClear", (RTS_UINTPTR)STI_RowClear, 0, 0) 
#endif



STI_ROW CDECL STI_RowCreate(STI_TABLE hTable, STO_ERROR *peError);
typedef STI_ROW (CDECL * PFSTI_ROWCREATE) (STI_TABLE hTable, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWCREATE_NOTIMPLEMENTED)
	#define USE_STI_RowCreate
	#define EXT_STI_RowCreate
	#define GET_STI_RowCreate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_RowCreate(p0,p1)  (STI_ROW)ERR_NOTIMPLEMENTED
	#define CHK_STI_RowCreate  FALSE
	#define EXP_STI_RowCreate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_RowCreate
	#define EXT_STI_RowCreate
	#define GET_STI_RowCreate(fl)  CAL_CMGETAPI( "STI_RowCreate" ) 
	#define CAL_STI_RowCreate  STI_RowCreate
	#define CHK_STI_RowCreate  TRUE
	#define EXP_STI_RowCreate  CAL_CMEXPAPI( "STI_RowCreate" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_RowCreate
	#define EXT_STI_RowCreate
	#define GET_STI_RowCreate(fl)  CAL_CMGETAPI( "STI_RowCreate" ) 
	#define CAL_STI_RowCreate  STI_RowCreate
	#define CHK_STI_RowCreate  TRUE
	#define EXP_STI_RowCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowCreate", (RTS_UINTPTR)STI_RowCreate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_RowCreate
	#define EXT_CmpCAAStorageSTI_RowCreate
	#define GET_CmpCAAStorageSTI_RowCreate  ERR_OK
	#define CAL_CmpCAAStorageSTI_RowCreate pICmpCAAStorage->ISTI_RowCreate
	#define CHK_CmpCAAStorageSTI_RowCreate (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_RowCreate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_RowCreate
	#define EXT_STI_RowCreate
	#define GET_STI_RowCreate(fl)  CAL_CMGETAPI( "STI_RowCreate" ) 
	#define CAL_STI_RowCreate pICmpCAAStorage->ISTI_RowCreate
	#define CHK_STI_RowCreate (pICmpCAAStorage != NULL)
	#define EXP_STI_RowCreate  CAL_CMEXPAPI( "STI_RowCreate" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_RowCreate  PFSTI_ROWCREATE pfSTI_RowCreate;
	#define EXT_STI_RowCreate  extern PFSTI_ROWCREATE pfSTI_RowCreate;
	#define GET_STI_RowCreate(fl)  s_pfCMGetAPI2( "STI_RowCreate", (RTS_VOID_FCTPTR *)&pfSTI_RowCreate, (fl), 0, 0)
	#define CAL_STI_RowCreate  pfSTI_RowCreate
	#define CHK_STI_RowCreate  (pfSTI_RowCreate != NULL)
	#define EXP_STI_RowCreate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowCreate", (RTS_UINTPTR)STI_RowCreate, 0, 0) 
#endif



STO_ERROR CDECL STI_RowDelete(STI_TABLE hTable, CAA_LINT idRow);
typedef STO_ERROR (CDECL * PFSTI_ROWDELETE) (STI_TABLE hTable, CAA_LINT idRow);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWDELETE_NOTIMPLEMENTED)
	#define USE_STI_RowDelete
	#define EXT_STI_RowDelete
	#define GET_STI_RowDelete(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_RowDelete(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_RowDelete  FALSE
	#define EXP_STI_RowDelete  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_RowDelete
	#define EXT_STI_RowDelete
	#define GET_STI_RowDelete(fl)  CAL_CMGETAPI( "STI_RowDelete" ) 
	#define CAL_STI_RowDelete  STI_RowDelete
	#define CHK_STI_RowDelete  TRUE
	#define EXP_STI_RowDelete  CAL_CMEXPAPI( "STI_RowDelete" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_RowDelete
	#define EXT_STI_RowDelete
	#define GET_STI_RowDelete(fl)  CAL_CMGETAPI( "STI_RowDelete" ) 
	#define CAL_STI_RowDelete  STI_RowDelete
	#define CHK_STI_RowDelete  TRUE
	#define EXP_STI_RowDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowDelete", (RTS_UINTPTR)STI_RowDelete, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_RowDelete
	#define EXT_CmpCAAStorageSTI_RowDelete
	#define GET_CmpCAAStorageSTI_RowDelete  ERR_OK
	#define CAL_CmpCAAStorageSTI_RowDelete pICmpCAAStorage->ISTI_RowDelete
	#define CHK_CmpCAAStorageSTI_RowDelete (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_RowDelete  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_RowDelete
	#define EXT_STI_RowDelete
	#define GET_STI_RowDelete(fl)  CAL_CMGETAPI( "STI_RowDelete" ) 
	#define CAL_STI_RowDelete pICmpCAAStorage->ISTI_RowDelete
	#define CHK_STI_RowDelete (pICmpCAAStorage != NULL)
	#define EXP_STI_RowDelete  CAL_CMEXPAPI( "STI_RowDelete" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_RowDelete  PFSTI_ROWDELETE pfSTI_RowDelete;
	#define EXT_STI_RowDelete  extern PFSTI_ROWDELETE pfSTI_RowDelete;
	#define GET_STI_RowDelete(fl)  s_pfCMGetAPI2( "STI_RowDelete", (RTS_VOID_FCTPTR *)&pfSTI_RowDelete, (fl), 0, 0)
	#define CAL_STI_RowDelete  pfSTI_RowDelete
	#define CHK_STI_RowDelete  (pfSTI_RowDelete != NULL)
	#define EXP_STI_RowDelete  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowDelete", (RTS_UINTPTR)STI_RowDelete, 0, 0) 
#endif



STI_ROW CDECL STI_RowDuplicate(STI_TABLE hTable, CAA_IDENT idRow, STO_ERROR *peError);
typedef STI_ROW (CDECL * PFSTI_ROWDUPLICATE) (STI_TABLE hTable, CAA_IDENT idRow, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWDUPLICATE_NOTIMPLEMENTED)
	#define USE_STI_RowDuplicate
	#define EXT_STI_RowDuplicate
	#define GET_STI_RowDuplicate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_RowDuplicate(p0,p1,p2)  (STI_ROW)ERR_NOTIMPLEMENTED
	#define CHK_STI_RowDuplicate  FALSE
	#define EXP_STI_RowDuplicate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_RowDuplicate
	#define EXT_STI_RowDuplicate
	#define GET_STI_RowDuplicate(fl)  CAL_CMGETAPI( "STI_RowDuplicate" ) 
	#define CAL_STI_RowDuplicate  STI_RowDuplicate
	#define CHK_STI_RowDuplicate  TRUE
	#define EXP_STI_RowDuplicate  CAL_CMEXPAPI( "STI_RowDuplicate" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_RowDuplicate
	#define EXT_STI_RowDuplicate
	#define GET_STI_RowDuplicate(fl)  CAL_CMGETAPI( "STI_RowDuplicate" ) 
	#define CAL_STI_RowDuplicate  STI_RowDuplicate
	#define CHK_STI_RowDuplicate  TRUE
	#define EXP_STI_RowDuplicate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowDuplicate", (RTS_UINTPTR)STI_RowDuplicate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_RowDuplicate
	#define EXT_CmpCAAStorageSTI_RowDuplicate
	#define GET_CmpCAAStorageSTI_RowDuplicate  ERR_OK
	#define CAL_CmpCAAStorageSTI_RowDuplicate pICmpCAAStorage->ISTI_RowDuplicate
	#define CHK_CmpCAAStorageSTI_RowDuplicate (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_RowDuplicate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_RowDuplicate
	#define EXT_STI_RowDuplicate
	#define GET_STI_RowDuplicate(fl)  CAL_CMGETAPI( "STI_RowDuplicate" ) 
	#define CAL_STI_RowDuplicate pICmpCAAStorage->ISTI_RowDuplicate
	#define CHK_STI_RowDuplicate (pICmpCAAStorage != NULL)
	#define EXP_STI_RowDuplicate  CAL_CMEXPAPI( "STI_RowDuplicate" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_RowDuplicate  PFSTI_ROWDUPLICATE pfSTI_RowDuplicate;
	#define EXT_STI_RowDuplicate  extern PFSTI_ROWDUPLICATE pfSTI_RowDuplicate;
	#define GET_STI_RowDuplicate(fl)  s_pfCMGetAPI2( "STI_RowDuplicate", (RTS_VOID_FCTPTR *)&pfSTI_RowDuplicate, (fl), 0, 0)
	#define CAL_STI_RowDuplicate  pfSTI_RowDuplicate
	#define CHK_STI_RowDuplicate  (pfSTI_RowDuplicate != NULL)
	#define EXP_STI_RowDuplicate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowDuplicate", (RTS_UINTPTR)STI_RowDuplicate, 0, 0) 
#endif



CAA_BOOL CDECL STI_RowGetHasChanged(STI_ROW hRow, STO_ERROR *peError);
typedef CAA_BOOL (CDECL * PFSTI_ROWGETHASCHANGED) (STI_ROW hRow, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWGETHASCHANGED_NOTIMPLEMENTED)
	#define USE_STI_RowGetHasChanged
	#define EXT_STI_RowGetHasChanged
	#define GET_STI_RowGetHasChanged(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_RowGetHasChanged(p0,p1)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_STI_RowGetHasChanged  FALSE
	#define EXP_STI_RowGetHasChanged  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_RowGetHasChanged
	#define EXT_STI_RowGetHasChanged
	#define GET_STI_RowGetHasChanged(fl)  CAL_CMGETAPI( "STI_RowGetHasChanged" ) 
	#define CAL_STI_RowGetHasChanged  STI_RowGetHasChanged
	#define CHK_STI_RowGetHasChanged  TRUE
	#define EXP_STI_RowGetHasChanged  CAL_CMEXPAPI( "STI_RowGetHasChanged" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_RowGetHasChanged
	#define EXT_STI_RowGetHasChanged
	#define GET_STI_RowGetHasChanged(fl)  CAL_CMGETAPI( "STI_RowGetHasChanged" ) 
	#define CAL_STI_RowGetHasChanged  STI_RowGetHasChanged
	#define CHK_STI_RowGetHasChanged  TRUE
	#define EXP_STI_RowGetHasChanged  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowGetHasChanged", (RTS_UINTPTR)STI_RowGetHasChanged, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_RowGetHasChanged
	#define EXT_CmpCAAStorageSTI_RowGetHasChanged
	#define GET_CmpCAAStorageSTI_RowGetHasChanged  ERR_OK
	#define CAL_CmpCAAStorageSTI_RowGetHasChanged pICmpCAAStorage->ISTI_RowGetHasChanged
	#define CHK_CmpCAAStorageSTI_RowGetHasChanged (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_RowGetHasChanged  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_RowGetHasChanged
	#define EXT_STI_RowGetHasChanged
	#define GET_STI_RowGetHasChanged(fl)  CAL_CMGETAPI( "STI_RowGetHasChanged" ) 
	#define CAL_STI_RowGetHasChanged pICmpCAAStorage->ISTI_RowGetHasChanged
	#define CHK_STI_RowGetHasChanged (pICmpCAAStorage != NULL)
	#define EXP_STI_RowGetHasChanged  CAL_CMEXPAPI( "STI_RowGetHasChanged" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_RowGetHasChanged  PFSTI_ROWGETHASCHANGED pfSTI_RowGetHasChanged;
	#define EXT_STI_RowGetHasChanged  extern PFSTI_ROWGETHASCHANGED pfSTI_RowGetHasChanged;
	#define GET_STI_RowGetHasChanged(fl)  s_pfCMGetAPI2( "STI_RowGetHasChanged", (RTS_VOID_FCTPTR *)&pfSTI_RowGetHasChanged, (fl), 0, 0)
	#define CAL_STI_RowGetHasChanged  pfSTI_RowGetHasChanged
	#define CHK_STI_RowGetHasChanged  (pfSTI_RowGetHasChanged != NULL)
	#define EXP_STI_RowGetHasChanged  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowGetHasChanged", (RTS_UINTPTR)STI_RowGetHasChanged, 0, 0) 
#endif



CAA_LINT CDECL STI_RowGetId(STI_ROW hRow, STO_ERROR *peError);
typedef CAA_LINT (CDECL * PFSTI_ROWGETID) (STI_ROW hRow, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWGETID_NOTIMPLEMENTED)
	#define USE_STI_RowGetId
	#define EXT_STI_RowGetId
	#define GET_STI_RowGetId(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_RowGetId(p0,p1)  (CAA_LINT)ERR_NOTIMPLEMENTED
	#define CHK_STI_RowGetId  FALSE
	#define EXP_STI_RowGetId  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_RowGetId
	#define EXT_STI_RowGetId
	#define GET_STI_RowGetId(fl)  CAL_CMGETAPI( "STI_RowGetId" ) 
	#define CAL_STI_RowGetId  STI_RowGetId
	#define CHK_STI_RowGetId  TRUE
	#define EXP_STI_RowGetId  CAL_CMEXPAPI( "STI_RowGetId" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_RowGetId
	#define EXT_STI_RowGetId
	#define GET_STI_RowGetId(fl)  CAL_CMGETAPI( "STI_RowGetId" ) 
	#define CAL_STI_RowGetId  STI_RowGetId
	#define CHK_STI_RowGetId  TRUE
	#define EXP_STI_RowGetId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowGetId", (RTS_UINTPTR)STI_RowGetId, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_RowGetId
	#define EXT_CmpCAAStorageSTI_RowGetId
	#define GET_CmpCAAStorageSTI_RowGetId  ERR_OK
	#define CAL_CmpCAAStorageSTI_RowGetId pICmpCAAStorage->ISTI_RowGetId
	#define CHK_CmpCAAStorageSTI_RowGetId (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_RowGetId  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_RowGetId
	#define EXT_STI_RowGetId
	#define GET_STI_RowGetId(fl)  CAL_CMGETAPI( "STI_RowGetId" ) 
	#define CAL_STI_RowGetId pICmpCAAStorage->ISTI_RowGetId
	#define CHK_STI_RowGetId (pICmpCAAStorage != NULL)
	#define EXP_STI_RowGetId  CAL_CMEXPAPI( "STI_RowGetId" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_RowGetId  PFSTI_ROWGETID pfSTI_RowGetId;
	#define EXT_STI_RowGetId  extern PFSTI_ROWGETID pfSTI_RowGetId;
	#define GET_STI_RowGetId(fl)  s_pfCMGetAPI2( "STI_RowGetId", (RTS_VOID_FCTPTR *)&pfSTI_RowGetId, (fl), 0, 0)
	#define CAL_STI_RowGetId  pfSTI_RowGetId
	#define CHK_STI_RowGetId  (pfSTI_RowGetId != NULL)
	#define EXP_STI_RowGetId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowGetId", (RTS_UINTPTR)STI_RowGetId, 0, 0) 
#endif



CAA_COUNT CDECL STI_RowGetNumOfColumns(STI_ROW hRow, STO_ERROR *peError);
typedef CAA_COUNT (CDECL * PFSTI_ROWGETNUMOFCOLUMNS) (STI_ROW hRow, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWGETNUMOFCOLUMNS_NOTIMPLEMENTED)
	#define USE_STI_RowGetNumOfColumns
	#define EXT_STI_RowGetNumOfColumns
	#define GET_STI_RowGetNumOfColumns(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_RowGetNumOfColumns(p0,p1)  (CAA_COUNT)ERR_NOTIMPLEMENTED
	#define CHK_STI_RowGetNumOfColumns  FALSE
	#define EXP_STI_RowGetNumOfColumns  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_RowGetNumOfColumns
	#define EXT_STI_RowGetNumOfColumns
	#define GET_STI_RowGetNumOfColumns(fl)  CAL_CMGETAPI( "STI_RowGetNumOfColumns" ) 
	#define CAL_STI_RowGetNumOfColumns  STI_RowGetNumOfColumns
	#define CHK_STI_RowGetNumOfColumns  TRUE
	#define EXP_STI_RowGetNumOfColumns  CAL_CMEXPAPI( "STI_RowGetNumOfColumns" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_RowGetNumOfColumns
	#define EXT_STI_RowGetNumOfColumns
	#define GET_STI_RowGetNumOfColumns(fl)  CAL_CMGETAPI( "STI_RowGetNumOfColumns" ) 
	#define CAL_STI_RowGetNumOfColumns  STI_RowGetNumOfColumns
	#define CHK_STI_RowGetNumOfColumns  TRUE
	#define EXP_STI_RowGetNumOfColumns  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowGetNumOfColumns", (RTS_UINTPTR)STI_RowGetNumOfColumns, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_RowGetNumOfColumns
	#define EXT_CmpCAAStorageSTI_RowGetNumOfColumns
	#define GET_CmpCAAStorageSTI_RowGetNumOfColumns  ERR_OK
	#define CAL_CmpCAAStorageSTI_RowGetNumOfColumns pICmpCAAStorage->ISTI_RowGetNumOfColumns
	#define CHK_CmpCAAStorageSTI_RowGetNumOfColumns (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_RowGetNumOfColumns  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_RowGetNumOfColumns
	#define EXT_STI_RowGetNumOfColumns
	#define GET_STI_RowGetNumOfColumns(fl)  CAL_CMGETAPI( "STI_RowGetNumOfColumns" ) 
	#define CAL_STI_RowGetNumOfColumns pICmpCAAStorage->ISTI_RowGetNumOfColumns
	#define CHK_STI_RowGetNumOfColumns (pICmpCAAStorage != NULL)
	#define EXP_STI_RowGetNumOfColumns  CAL_CMEXPAPI( "STI_RowGetNumOfColumns" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_RowGetNumOfColumns  PFSTI_ROWGETNUMOFCOLUMNS pfSTI_RowGetNumOfColumns;
	#define EXT_STI_RowGetNumOfColumns  extern PFSTI_ROWGETNUMOFCOLUMNS pfSTI_RowGetNumOfColumns;
	#define GET_STI_RowGetNumOfColumns(fl)  s_pfCMGetAPI2( "STI_RowGetNumOfColumns", (RTS_VOID_FCTPTR *)&pfSTI_RowGetNumOfColumns, (fl), 0, 0)
	#define CAL_STI_RowGetNumOfColumns  pfSTI_RowGetNumOfColumns
	#define CHK_STI_RowGetNumOfColumns  (pfSTI_RowGetNumOfColumns != NULL)
	#define EXP_STI_RowGetNumOfColumns  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowGetNumOfColumns", (RTS_UINTPTR)STI_RowGetNumOfColumns, 0, 0) 
#endif



STI_STORAGE CDECL STI_RowGetStorage(STI_ROW hRow, STO_ERROR *peError);
typedef STI_STORAGE (CDECL * PFSTI_ROWGETSTORAGE) (STI_ROW hRow, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWGETSTORAGE_NOTIMPLEMENTED)
	#define USE_STI_RowGetStorage
	#define EXT_STI_RowGetStorage
	#define GET_STI_RowGetStorage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_RowGetStorage(p0,p1)  (STI_STORAGE)ERR_NOTIMPLEMENTED
	#define CHK_STI_RowGetStorage  FALSE
	#define EXP_STI_RowGetStorage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_RowGetStorage
	#define EXT_STI_RowGetStorage
	#define GET_STI_RowGetStorage(fl)  CAL_CMGETAPI( "STI_RowGetStorage" ) 
	#define CAL_STI_RowGetStorage  STI_RowGetStorage
	#define CHK_STI_RowGetStorage  TRUE
	#define EXP_STI_RowGetStorage  CAL_CMEXPAPI( "STI_RowGetStorage" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_RowGetStorage
	#define EXT_STI_RowGetStorage
	#define GET_STI_RowGetStorage(fl)  CAL_CMGETAPI( "STI_RowGetStorage" ) 
	#define CAL_STI_RowGetStorage  STI_RowGetStorage
	#define CHK_STI_RowGetStorage  TRUE
	#define EXP_STI_RowGetStorage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowGetStorage", (RTS_UINTPTR)STI_RowGetStorage, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_RowGetStorage
	#define EXT_CmpCAAStorageSTI_RowGetStorage
	#define GET_CmpCAAStorageSTI_RowGetStorage  ERR_OK
	#define CAL_CmpCAAStorageSTI_RowGetStorage pICmpCAAStorage->ISTI_RowGetStorage
	#define CHK_CmpCAAStorageSTI_RowGetStorage (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_RowGetStorage  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_RowGetStorage
	#define EXT_STI_RowGetStorage
	#define GET_STI_RowGetStorage(fl)  CAL_CMGETAPI( "STI_RowGetStorage" ) 
	#define CAL_STI_RowGetStorage pICmpCAAStorage->ISTI_RowGetStorage
	#define CHK_STI_RowGetStorage (pICmpCAAStorage != NULL)
	#define EXP_STI_RowGetStorage  CAL_CMEXPAPI( "STI_RowGetStorage" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_RowGetStorage  PFSTI_ROWGETSTORAGE pfSTI_RowGetStorage;
	#define EXT_STI_RowGetStorage  extern PFSTI_ROWGETSTORAGE pfSTI_RowGetStorage;
	#define GET_STI_RowGetStorage(fl)  s_pfCMGetAPI2( "STI_RowGetStorage", (RTS_VOID_FCTPTR *)&pfSTI_RowGetStorage, (fl), 0, 0)
	#define CAL_STI_RowGetStorage  pfSTI_RowGetStorage
	#define CHK_STI_RowGetStorage  (pfSTI_RowGetStorage != NULL)
	#define EXP_STI_RowGetStorage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowGetStorage", (RTS_UINTPTR)STI_RowGetStorage, 0, 0) 
#endif



STI_TABLE CDECL STI_RowGetTable(STI_ROW hRow, STO_ERROR *peError);
typedef STI_TABLE (CDECL * PFSTI_ROWGETTABLE) (STI_ROW hRow, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWGETTABLE_NOTIMPLEMENTED)
	#define USE_STI_RowGetTable
	#define EXT_STI_RowGetTable
	#define GET_STI_RowGetTable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_RowGetTable(p0,p1)  (STI_TABLE)ERR_NOTIMPLEMENTED
	#define CHK_STI_RowGetTable  FALSE
	#define EXP_STI_RowGetTable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_RowGetTable
	#define EXT_STI_RowGetTable
	#define GET_STI_RowGetTable(fl)  CAL_CMGETAPI( "STI_RowGetTable" ) 
	#define CAL_STI_RowGetTable  STI_RowGetTable
	#define CHK_STI_RowGetTable  TRUE
	#define EXP_STI_RowGetTable  CAL_CMEXPAPI( "STI_RowGetTable" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_RowGetTable
	#define EXT_STI_RowGetTable
	#define GET_STI_RowGetTable(fl)  CAL_CMGETAPI( "STI_RowGetTable" ) 
	#define CAL_STI_RowGetTable  STI_RowGetTable
	#define CHK_STI_RowGetTable  TRUE
	#define EXP_STI_RowGetTable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowGetTable", (RTS_UINTPTR)STI_RowGetTable, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_RowGetTable
	#define EXT_CmpCAAStorageSTI_RowGetTable
	#define GET_CmpCAAStorageSTI_RowGetTable  ERR_OK
	#define CAL_CmpCAAStorageSTI_RowGetTable pICmpCAAStorage->ISTI_RowGetTable
	#define CHK_CmpCAAStorageSTI_RowGetTable (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_RowGetTable  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_RowGetTable
	#define EXT_STI_RowGetTable
	#define GET_STI_RowGetTable(fl)  CAL_CMGETAPI( "STI_RowGetTable" ) 
	#define CAL_STI_RowGetTable pICmpCAAStorage->ISTI_RowGetTable
	#define CHK_STI_RowGetTable (pICmpCAAStorage != NULL)
	#define EXP_STI_RowGetTable  CAL_CMEXPAPI( "STI_RowGetTable" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_RowGetTable  PFSTI_ROWGETTABLE pfSTI_RowGetTable;
	#define EXT_STI_RowGetTable  extern PFSTI_ROWGETTABLE pfSTI_RowGetTable;
	#define GET_STI_RowGetTable(fl)  s_pfCMGetAPI2( "STI_RowGetTable", (RTS_VOID_FCTPTR *)&pfSTI_RowGetTable, (fl), 0, 0)
	#define CAL_STI_RowGetTable  pfSTI_RowGetTable
	#define CHK_STI_RowGetTable  (pfSTI_RowGetTable != NULL)
	#define EXP_STI_RowGetTable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowGetTable", (RTS_UINTPTR)STI_RowGetTable, 0, 0) 
#endif



CAA_IDENT CDECL STI_RowInsert(STI_ROW hRow, STO_ERROR *peError);
typedef CAA_IDENT (CDECL * PFSTI_ROWINSERT) (STI_ROW hRow, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWINSERT_NOTIMPLEMENTED)
	#define USE_STI_RowInsert
	#define EXT_STI_RowInsert
	#define GET_STI_RowInsert(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_RowInsert(p0,p1)  (CAA_IDENT)ERR_NOTIMPLEMENTED
	#define CHK_STI_RowInsert  FALSE
	#define EXP_STI_RowInsert  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_RowInsert
	#define EXT_STI_RowInsert
	#define GET_STI_RowInsert(fl)  CAL_CMGETAPI( "STI_RowInsert" ) 
	#define CAL_STI_RowInsert  STI_RowInsert
	#define CHK_STI_RowInsert  TRUE
	#define EXP_STI_RowInsert  CAL_CMEXPAPI( "STI_RowInsert" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_RowInsert
	#define EXT_STI_RowInsert
	#define GET_STI_RowInsert(fl)  CAL_CMGETAPI( "STI_RowInsert" ) 
	#define CAL_STI_RowInsert  STI_RowInsert
	#define CHK_STI_RowInsert  TRUE
	#define EXP_STI_RowInsert  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowInsert", (RTS_UINTPTR)STI_RowInsert, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_RowInsert
	#define EXT_CmpCAAStorageSTI_RowInsert
	#define GET_CmpCAAStorageSTI_RowInsert  ERR_OK
	#define CAL_CmpCAAStorageSTI_RowInsert pICmpCAAStorage->ISTI_RowInsert
	#define CHK_CmpCAAStorageSTI_RowInsert (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_RowInsert  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_RowInsert
	#define EXT_STI_RowInsert
	#define GET_STI_RowInsert(fl)  CAL_CMGETAPI( "STI_RowInsert" ) 
	#define CAL_STI_RowInsert pICmpCAAStorage->ISTI_RowInsert
	#define CHK_STI_RowInsert (pICmpCAAStorage != NULL)
	#define EXP_STI_RowInsert  CAL_CMEXPAPI( "STI_RowInsert" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_RowInsert  PFSTI_ROWINSERT pfSTI_RowInsert;
	#define EXT_STI_RowInsert  extern PFSTI_ROWINSERT pfSTI_RowInsert;
	#define GET_STI_RowInsert(fl)  s_pfCMGetAPI2( "STI_RowInsert", (RTS_VOID_FCTPTR *)&pfSTI_RowInsert, (fl), 0, 0)
	#define CAL_STI_RowInsert  pfSTI_RowInsert
	#define CHK_STI_RowInsert  (pfSTI_RowInsert != NULL)
	#define EXP_STI_RowInsert  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowInsert", (RTS_UINTPTR)STI_RowInsert, 0, 0) 
#endif



STO_ERROR CDECL STI_RowUpdate(STI_ROW hRow);
typedef STO_ERROR (CDECL * PFSTI_ROWUPDATE) (STI_ROW hRow);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWUPDATE_NOTIMPLEMENTED)
	#define USE_STI_RowUpdate
	#define EXT_STI_RowUpdate
	#define GET_STI_RowUpdate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_RowUpdate(p0)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_RowUpdate  FALSE
	#define EXP_STI_RowUpdate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_RowUpdate
	#define EXT_STI_RowUpdate
	#define GET_STI_RowUpdate(fl)  CAL_CMGETAPI( "STI_RowUpdate" ) 
	#define CAL_STI_RowUpdate  STI_RowUpdate
	#define CHK_STI_RowUpdate  TRUE
	#define EXP_STI_RowUpdate  CAL_CMEXPAPI( "STI_RowUpdate" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_RowUpdate
	#define EXT_STI_RowUpdate
	#define GET_STI_RowUpdate(fl)  CAL_CMGETAPI( "STI_RowUpdate" ) 
	#define CAL_STI_RowUpdate  STI_RowUpdate
	#define CHK_STI_RowUpdate  TRUE
	#define EXP_STI_RowUpdate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowUpdate", (RTS_UINTPTR)STI_RowUpdate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_RowUpdate
	#define EXT_CmpCAAStorageSTI_RowUpdate
	#define GET_CmpCAAStorageSTI_RowUpdate  ERR_OK
	#define CAL_CmpCAAStorageSTI_RowUpdate pICmpCAAStorage->ISTI_RowUpdate
	#define CHK_CmpCAAStorageSTI_RowUpdate (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_RowUpdate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_RowUpdate
	#define EXT_STI_RowUpdate
	#define GET_STI_RowUpdate(fl)  CAL_CMGETAPI( "STI_RowUpdate" ) 
	#define CAL_STI_RowUpdate pICmpCAAStorage->ISTI_RowUpdate
	#define CHK_STI_RowUpdate (pICmpCAAStorage != NULL)
	#define EXP_STI_RowUpdate  CAL_CMEXPAPI( "STI_RowUpdate" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_RowUpdate  PFSTI_ROWUPDATE pfSTI_RowUpdate;
	#define EXT_STI_RowUpdate  extern PFSTI_ROWUPDATE pfSTI_RowUpdate;
	#define GET_STI_RowUpdate(fl)  s_pfCMGetAPI2( "STI_RowUpdate", (RTS_VOID_FCTPTR *)&pfSTI_RowUpdate, (fl), 0, 0)
	#define CAL_STI_RowUpdate  pfSTI_RowUpdate
	#define CHK_STI_RowUpdate  (pfSTI_RowUpdate != NULL)
	#define EXP_STI_RowUpdate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowUpdate", (RTS_UINTPTR)STI_RowUpdate, 0, 0) 
#endif



STO_ERROR CDECL STI_RowRelease(STI_ROW hRow);
typedef STO_ERROR (CDECL * PFSTI_ROWRELEASE) (STI_ROW hRow);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWRELEASE_NOTIMPLEMENTED)
	#define USE_STI_RowRelease
	#define EXT_STI_RowRelease
	#define GET_STI_RowRelease(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_RowRelease(p0)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_RowRelease  FALSE
	#define EXP_STI_RowRelease  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_RowRelease
	#define EXT_STI_RowRelease
	#define GET_STI_RowRelease(fl)  CAL_CMGETAPI( "STI_RowRelease" ) 
	#define CAL_STI_RowRelease  STI_RowRelease
	#define CHK_STI_RowRelease  TRUE
	#define EXP_STI_RowRelease  CAL_CMEXPAPI( "STI_RowRelease" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_RowRelease
	#define EXT_STI_RowRelease
	#define GET_STI_RowRelease(fl)  CAL_CMGETAPI( "STI_RowRelease" ) 
	#define CAL_STI_RowRelease  STI_RowRelease
	#define CHK_STI_RowRelease  TRUE
	#define EXP_STI_RowRelease  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowRelease", (RTS_UINTPTR)STI_RowRelease, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_RowRelease
	#define EXT_CmpCAAStorageSTI_RowRelease
	#define GET_CmpCAAStorageSTI_RowRelease  ERR_OK
	#define CAL_CmpCAAStorageSTI_RowRelease pICmpCAAStorage->ISTI_RowRelease
	#define CHK_CmpCAAStorageSTI_RowRelease (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_RowRelease  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_RowRelease
	#define EXT_STI_RowRelease
	#define GET_STI_RowRelease(fl)  CAL_CMGETAPI( "STI_RowRelease" ) 
	#define CAL_STI_RowRelease pICmpCAAStorage->ISTI_RowRelease
	#define CHK_STI_RowRelease (pICmpCAAStorage != NULL)
	#define EXP_STI_RowRelease  CAL_CMEXPAPI( "STI_RowRelease" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_RowRelease  PFSTI_ROWRELEASE pfSTI_RowRelease;
	#define EXT_STI_RowRelease  extern PFSTI_ROWRELEASE pfSTI_RowRelease;
	#define GET_STI_RowRelease(fl)  s_pfCMGetAPI2( "STI_RowRelease", (RTS_VOID_FCTPTR *)&pfSTI_RowRelease, (fl), 0, 0)
	#define CAL_STI_RowRelease  pfSTI_RowRelease
	#define CHK_STI_RowRelease  (pfSTI_RowRelease != NULL)
	#define EXP_STI_RowRelease  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowRelease", (RTS_UINTPTR)STI_RowRelease, 0, 0) 
#endif



STI_ROW CDECL STI_RowSelect(STI_TABLE hTable, CAA_IDENT idRow, STO_ERROR *peError);
typedef STI_ROW (CDECL * PFSTI_ROWSELECT) (STI_TABLE hTable, CAA_IDENT idRow, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_ROWSELECT_NOTIMPLEMENTED)
	#define USE_STI_RowSelect
	#define EXT_STI_RowSelect
	#define GET_STI_RowSelect(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_RowSelect(p0,p1,p2)  (STI_ROW)ERR_NOTIMPLEMENTED
	#define CHK_STI_RowSelect  FALSE
	#define EXP_STI_RowSelect  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_RowSelect
	#define EXT_STI_RowSelect
	#define GET_STI_RowSelect(fl)  CAL_CMGETAPI( "STI_RowSelect" ) 
	#define CAL_STI_RowSelect  STI_RowSelect
	#define CHK_STI_RowSelect  TRUE
	#define EXP_STI_RowSelect  CAL_CMEXPAPI( "STI_RowSelect" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_RowSelect
	#define EXT_STI_RowSelect
	#define GET_STI_RowSelect(fl)  CAL_CMGETAPI( "STI_RowSelect" ) 
	#define CAL_STI_RowSelect  STI_RowSelect
	#define CHK_STI_RowSelect  TRUE
	#define EXP_STI_RowSelect  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowSelect", (RTS_UINTPTR)STI_RowSelect, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_RowSelect
	#define EXT_CmpCAAStorageSTI_RowSelect
	#define GET_CmpCAAStorageSTI_RowSelect  ERR_OK
	#define CAL_CmpCAAStorageSTI_RowSelect pICmpCAAStorage->ISTI_RowSelect
	#define CHK_CmpCAAStorageSTI_RowSelect (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_RowSelect  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_RowSelect
	#define EXT_STI_RowSelect
	#define GET_STI_RowSelect(fl)  CAL_CMGETAPI( "STI_RowSelect" ) 
	#define CAL_STI_RowSelect pICmpCAAStorage->ISTI_RowSelect
	#define CHK_STI_RowSelect (pICmpCAAStorage != NULL)
	#define EXP_STI_RowSelect  CAL_CMEXPAPI( "STI_RowSelect" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_RowSelect  PFSTI_ROWSELECT pfSTI_RowSelect;
	#define EXT_STI_RowSelect  extern PFSTI_ROWSELECT pfSTI_RowSelect;
	#define GET_STI_RowSelect(fl)  s_pfCMGetAPI2( "STI_RowSelect", (RTS_VOID_FCTPTR *)&pfSTI_RowSelect, (fl), 0, 0)
	#define CAL_STI_RowSelect  pfSTI_RowSelect
	#define CHK_STI_RowSelect  (pfSTI_RowSelect != NULL)
	#define EXP_STI_RowSelect  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_RowSelect", (RTS_UINTPTR)STI_RowSelect, 0, 0) 
#endif



STI_STORAGE CDECL STI_SavepointGetStorage(STI_SAVEPOINT hSavepoint, STO_ERROR *peError);
typedef STI_STORAGE (CDECL * PFSTI_SAVEPOINTGETSTORAGE) (STI_SAVEPOINT hSavepoint, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_SAVEPOINTGETSTORAGE_NOTIMPLEMENTED)
	#define USE_STI_SavepointGetStorage
	#define EXT_STI_SavepointGetStorage
	#define GET_STI_SavepointGetStorage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_SavepointGetStorage(p0,p1)  (STI_STORAGE)ERR_NOTIMPLEMENTED
	#define CHK_STI_SavepointGetStorage  FALSE
	#define EXP_STI_SavepointGetStorage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_SavepointGetStorage
	#define EXT_STI_SavepointGetStorage
	#define GET_STI_SavepointGetStorage(fl)  CAL_CMGETAPI( "STI_SavepointGetStorage" ) 
	#define CAL_STI_SavepointGetStorage  STI_SavepointGetStorage
	#define CHK_STI_SavepointGetStorage  TRUE
	#define EXP_STI_SavepointGetStorage  CAL_CMEXPAPI( "STI_SavepointGetStorage" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_SavepointGetStorage
	#define EXT_STI_SavepointGetStorage
	#define GET_STI_SavepointGetStorage(fl)  CAL_CMGETAPI( "STI_SavepointGetStorage" ) 
	#define CAL_STI_SavepointGetStorage  STI_SavepointGetStorage
	#define CHK_STI_SavepointGetStorage  TRUE
	#define EXP_STI_SavepointGetStorage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_SavepointGetStorage", (RTS_UINTPTR)STI_SavepointGetStorage, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_SavepointGetStorage
	#define EXT_CmpCAAStorageSTI_SavepointGetStorage
	#define GET_CmpCAAStorageSTI_SavepointGetStorage  ERR_OK
	#define CAL_CmpCAAStorageSTI_SavepointGetStorage pICmpCAAStorage->ISTI_SavepointGetStorage
	#define CHK_CmpCAAStorageSTI_SavepointGetStorage (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_SavepointGetStorage  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_SavepointGetStorage
	#define EXT_STI_SavepointGetStorage
	#define GET_STI_SavepointGetStorage(fl)  CAL_CMGETAPI( "STI_SavepointGetStorage" ) 
	#define CAL_STI_SavepointGetStorage pICmpCAAStorage->ISTI_SavepointGetStorage
	#define CHK_STI_SavepointGetStorage (pICmpCAAStorage != NULL)
	#define EXP_STI_SavepointGetStorage  CAL_CMEXPAPI( "STI_SavepointGetStorage" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_SavepointGetStorage  PFSTI_SAVEPOINTGETSTORAGE pfSTI_SavepointGetStorage;
	#define EXT_STI_SavepointGetStorage  extern PFSTI_SAVEPOINTGETSTORAGE pfSTI_SavepointGetStorage;
	#define GET_STI_SavepointGetStorage(fl)  s_pfCMGetAPI2( "STI_SavepointGetStorage", (RTS_VOID_FCTPTR *)&pfSTI_SavepointGetStorage, (fl), 0, 0)
	#define CAL_STI_SavepointGetStorage  pfSTI_SavepointGetStorage
	#define CHK_STI_SavepointGetStorage  (pfSTI_SavepointGetStorage != NULL)
	#define EXP_STI_SavepointGetStorage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_SavepointGetStorage", (RTS_UINTPTR)STI_SavepointGetStorage, 0, 0) 
#endif



STI_TRANSACTION CDECL STI_SavepointGetTransaction(STI_SAVEPOINT hSavepoint, STO_ERROR *peError);
typedef STI_TRANSACTION (CDECL * PFSTI_SAVEPOINTGETTRANSACTION) (STI_SAVEPOINT hSavepoint, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_SAVEPOINTGETTRANSACTION_NOTIMPLEMENTED)
	#define USE_STI_SavepointGetTransaction
	#define EXT_STI_SavepointGetTransaction
	#define GET_STI_SavepointGetTransaction(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_SavepointGetTransaction(p0,p1)  (STI_TRANSACTION)ERR_NOTIMPLEMENTED
	#define CHK_STI_SavepointGetTransaction  FALSE
	#define EXP_STI_SavepointGetTransaction  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_SavepointGetTransaction
	#define EXT_STI_SavepointGetTransaction
	#define GET_STI_SavepointGetTransaction(fl)  CAL_CMGETAPI( "STI_SavepointGetTransaction" ) 
	#define CAL_STI_SavepointGetTransaction  STI_SavepointGetTransaction
	#define CHK_STI_SavepointGetTransaction  TRUE
	#define EXP_STI_SavepointGetTransaction  CAL_CMEXPAPI( "STI_SavepointGetTransaction" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_SavepointGetTransaction
	#define EXT_STI_SavepointGetTransaction
	#define GET_STI_SavepointGetTransaction(fl)  CAL_CMGETAPI( "STI_SavepointGetTransaction" ) 
	#define CAL_STI_SavepointGetTransaction  STI_SavepointGetTransaction
	#define CHK_STI_SavepointGetTransaction  TRUE
	#define EXP_STI_SavepointGetTransaction  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_SavepointGetTransaction", (RTS_UINTPTR)STI_SavepointGetTransaction, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_SavepointGetTransaction
	#define EXT_CmpCAAStorageSTI_SavepointGetTransaction
	#define GET_CmpCAAStorageSTI_SavepointGetTransaction  ERR_OK
	#define CAL_CmpCAAStorageSTI_SavepointGetTransaction pICmpCAAStorage->ISTI_SavepointGetTransaction
	#define CHK_CmpCAAStorageSTI_SavepointGetTransaction (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_SavepointGetTransaction  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_SavepointGetTransaction
	#define EXT_STI_SavepointGetTransaction
	#define GET_STI_SavepointGetTransaction(fl)  CAL_CMGETAPI( "STI_SavepointGetTransaction" ) 
	#define CAL_STI_SavepointGetTransaction pICmpCAAStorage->ISTI_SavepointGetTransaction
	#define CHK_STI_SavepointGetTransaction (pICmpCAAStorage != NULL)
	#define EXP_STI_SavepointGetTransaction  CAL_CMEXPAPI( "STI_SavepointGetTransaction" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_SavepointGetTransaction  PFSTI_SAVEPOINTGETTRANSACTION pfSTI_SavepointGetTransaction;
	#define EXT_STI_SavepointGetTransaction  extern PFSTI_SAVEPOINTGETTRANSACTION pfSTI_SavepointGetTransaction;
	#define GET_STI_SavepointGetTransaction(fl)  s_pfCMGetAPI2( "STI_SavepointGetTransaction", (RTS_VOID_FCTPTR *)&pfSTI_SavepointGetTransaction, (fl), 0, 0)
	#define CAL_STI_SavepointGetTransaction  pfSTI_SavepointGetTransaction
	#define CHK_STI_SavepointGetTransaction  (pfSTI_SavepointGetTransaction != NULL)
	#define EXP_STI_SavepointGetTransaction  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_SavepointGetTransaction", (RTS_UINTPTR)STI_SavepointGetTransaction, 0, 0) 
#endif



STO_ERROR CDECL STI_SavepointRelease(STI_SAVEPOINT hSavePoint);
typedef STO_ERROR (CDECL * PFSTI_SAVEPOINTRELEASE) (STI_SAVEPOINT hSavePoint);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_SAVEPOINTRELEASE_NOTIMPLEMENTED)
	#define USE_STI_SavepointRelease
	#define EXT_STI_SavepointRelease
	#define GET_STI_SavepointRelease(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_SavepointRelease(p0)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_SavepointRelease  FALSE
	#define EXP_STI_SavepointRelease  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_SavepointRelease
	#define EXT_STI_SavepointRelease
	#define GET_STI_SavepointRelease(fl)  CAL_CMGETAPI( "STI_SavepointRelease" ) 
	#define CAL_STI_SavepointRelease  STI_SavepointRelease
	#define CHK_STI_SavepointRelease  TRUE
	#define EXP_STI_SavepointRelease  CAL_CMEXPAPI( "STI_SavepointRelease" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_SavepointRelease
	#define EXT_STI_SavepointRelease
	#define GET_STI_SavepointRelease(fl)  CAL_CMGETAPI( "STI_SavepointRelease" ) 
	#define CAL_STI_SavepointRelease  STI_SavepointRelease
	#define CHK_STI_SavepointRelease  TRUE
	#define EXP_STI_SavepointRelease  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_SavepointRelease", (RTS_UINTPTR)STI_SavepointRelease, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_SavepointRelease
	#define EXT_CmpCAAStorageSTI_SavepointRelease
	#define GET_CmpCAAStorageSTI_SavepointRelease  ERR_OK
	#define CAL_CmpCAAStorageSTI_SavepointRelease pICmpCAAStorage->ISTI_SavepointRelease
	#define CHK_CmpCAAStorageSTI_SavepointRelease (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_SavepointRelease  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_SavepointRelease
	#define EXT_STI_SavepointRelease
	#define GET_STI_SavepointRelease(fl)  CAL_CMGETAPI( "STI_SavepointRelease" ) 
	#define CAL_STI_SavepointRelease pICmpCAAStorage->ISTI_SavepointRelease
	#define CHK_STI_SavepointRelease (pICmpCAAStorage != NULL)
	#define EXP_STI_SavepointRelease  CAL_CMEXPAPI( "STI_SavepointRelease" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_SavepointRelease  PFSTI_SAVEPOINTRELEASE pfSTI_SavepointRelease;
	#define EXT_STI_SavepointRelease  extern PFSTI_SAVEPOINTRELEASE pfSTI_SavepointRelease;
	#define GET_STI_SavepointRelease(fl)  s_pfCMGetAPI2( "STI_SavepointRelease", (RTS_VOID_FCTPTR *)&pfSTI_SavepointRelease, (fl), 0, 0)
	#define CAL_STI_SavepointRelease  pfSTI_SavepointRelease
	#define CHK_STI_SavepointRelease  (pfSTI_SavepointRelease != NULL)
	#define EXP_STI_SavepointRelease  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_SavepointRelease", (RTS_UINTPTR)STI_SavepointRelease, 0, 0) 
#endif



STO_ERROR CDECL STI_SavepointRollback(STI_SAVEPOINT hSavePoint);
typedef STO_ERROR (CDECL * PFSTI_SAVEPOINTROLLBACK) (STI_SAVEPOINT hSavePoint);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_SAVEPOINTROLLBACK_NOTIMPLEMENTED)
	#define USE_STI_SavepointRollback
	#define EXT_STI_SavepointRollback
	#define GET_STI_SavepointRollback(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_SavepointRollback(p0)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_SavepointRollback  FALSE
	#define EXP_STI_SavepointRollback  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_SavepointRollback
	#define EXT_STI_SavepointRollback
	#define GET_STI_SavepointRollback(fl)  CAL_CMGETAPI( "STI_SavepointRollback" ) 
	#define CAL_STI_SavepointRollback  STI_SavepointRollback
	#define CHK_STI_SavepointRollback  TRUE
	#define EXP_STI_SavepointRollback  CAL_CMEXPAPI( "STI_SavepointRollback" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_SavepointRollback
	#define EXT_STI_SavepointRollback
	#define GET_STI_SavepointRollback(fl)  CAL_CMGETAPI( "STI_SavepointRollback" ) 
	#define CAL_STI_SavepointRollback  STI_SavepointRollback
	#define CHK_STI_SavepointRollback  TRUE
	#define EXP_STI_SavepointRollback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_SavepointRollback", (RTS_UINTPTR)STI_SavepointRollback, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_SavepointRollback
	#define EXT_CmpCAAStorageSTI_SavepointRollback
	#define GET_CmpCAAStorageSTI_SavepointRollback  ERR_OK
	#define CAL_CmpCAAStorageSTI_SavepointRollback pICmpCAAStorage->ISTI_SavepointRollback
	#define CHK_CmpCAAStorageSTI_SavepointRollback (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_SavepointRollback  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_SavepointRollback
	#define EXT_STI_SavepointRollback
	#define GET_STI_SavepointRollback(fl)  CAL_CMGETAPI( "STI_SavepointRollback" ) 
	#define CAL_STI_SavepointRollback pICmpCAAStorage->ISTI_SavepointRollback
	#define CHK_STI_SavepointRollback (pICmpCAAStorage != NULL)
	#define EXP_STI_SavepointRollback  CAL_CMEXPAPI( "STI_SavepointRollback" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_SavepointRollback  PFSTI_SAVEPOINTROLLBACK pfSTI_SavepointRollback;
	#define EXT_STI_SavepointRollback  extern PFSTI_SAVEPOINTROLLBACK pfSTI_SavepointRollback;
	#define GET_STI_SavepointRollback(fl)  s_pfCMGetAPI2( "STI_SavepointRollback", (RTS_VOID_FCTPTR *)&pfSTI_SavepointRollback, (fl), 0, 0)
	#define CAL_STI_SavepointRollback  pfSTI_SavepointRollback
	#define CHK_STI_SavepointRollback  (pfSTI_SavepointRollback != NULL)
	#define EXP_STI_SavepointRollback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_SavepointRollback", (RTS_UINTPTR)STI_SavepointRollback, 0, 0) 
#endif



STO_ERROR CDECL STI_StorageClear(STI_STORAGE hStorage);
typedef STO_ERROR (CDECL * PFSTI_STORAGECLEAR) (STI_STORAGE hStorage);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGECLEAR_NOTIMPLEMENTED)
	#define USE_STI_StorageClear
	#define EXT_STI_StorageClear
	#define GET_STI_StorageClear(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_StorageClear(p0)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_StorageClear  FALSE
	#define EXP_STI_StorageClear  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_StorageClear
	#define EXT_STI_StorageClear
	#define GET_STI_StorageClear(fl)  CAL_CMGETAPI( "STI_StorageClear" ) 
	#define CAL_STI_StorageClear  STI_StorageClear
	#define CHK_STI_StorageClear  TRUE
	#define EXP_STI_StorageClear  CAL_CMEXPAPI( "STI_StorageClear" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_StorageClear
	#define EXT_STI_StorageClear
	#define GET_STI_StorageClear(fl)  CAL_CMGETAPI( "STI_StorageClear" ) 
	#define CAL_STI_StorageClear  STI_StorageClear
	#define CHK_STI_StorageClear  TRUE
	#define EXP_STI_StorageClear  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageClear", (RTS_UINTPTR)STI_StorageClear, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_StorageClear
	#define EXT_CmpCAAStorageSTI_StorageClear
	#define GET_CmpCAAStorageSTI_StorageClear  ERR_OK
	#define CAL_CmpCAAStorageSTI_StorageClear pICmpCAAStorage->ISTI_StorageClear
	#define CHK_CmpCAAStorageSTI_StorageClear (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_StorageClear  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_StorageClear
	#define EXT_STI_StorageClear
	#define GET_STI_StorageClear(fl)  CAL_CMGETAPI( "STI_StorageClear" ) 
	#define CAL_STI_StorageClear pICmpCAAStorage->ISTI_StorageClear
	#define CHK_STI_StorageClear (pICmpCAAStorage != NULL)
	#define EXP_STI_StorageClear  CAL_CMEXPAPI( "STI_StorageClear" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_StorageClear  PFSTI_STORAGECLEAR pfSTI_StorageClear;
	#define EXT_STI_StorageClear  extern PFSTI_STORAGECLEAR pfSTI_StorageClear;
	#define GET_STI_StorageClear(fl)  s_pfCMGetAPI2( "STI_StorageClear", (RTS_VOID_FCTPTR *)&pfSTI_StorageClear, (fl), 0, 0)
	#define CAL_STI_StorageClear  pfSTI_StorageClear
	#define CHK_STI_StorageClear  (pfSTI_StorageClear != NULL)
	#define EXP_STI_StorageClear  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageClear", (RTS_UINTPTR)STI_StorageClear, 0, 0) 
#endif



STO_ERROR CDECL STI_StorageClose(STI_STORAGE hStorage);
typedef STO_ERROR (CDECL * PFSTI_STORAGECLOSE) (STI_STORAGE hStorage);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGECLOSE_NOTIMPLEMENTED)
	#define USE_STI_StorageClose
	#define EXT_STI_StorageClose
	#define GET_STI_StorageClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_StorageClose(p0)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_StorageClose  FALSE
	#define EXP_STI_StorageClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_StorageClose
	#define EXT_STI_StorageClose
	#define GET_STI_StorageClose(fl)  CAL_CMGETAPI( "STI_StorageClose" ) 
	#define CAL_STI_StorageClose  STI_StorageClose
	#define CHK_STI_StorageClose  TRUE
	#define EXP_STI_StorageClose  CAL_CMEXPAPI( "STI_StorageClose" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_StorageClose
	#define EXT_STI_StorageClose
	#define GET_STI_StorageClose(fl)  CAL_CMGETAPI( "STI_StorageClose" ) 
	#define CAL_STI_StorageClose  STI_StorageClose
	#define CHK_STI_StorageClose  TRUE
	#define EXP_STI_StorageClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageClose", (RTS_UINTPTR)STI_StorageClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_StorageClose
	#define EXT_CmpCAAStorageSTI_StorageClose
	#define GET_CmpCAAStorageSTI_StorageClose  ERR_OK
	#define CAL_CmpCAAStorageSTI_StorageClose pICmpCAAStorage->ISTI_StorageClose
	#define CHK_CmpCAAStorageSTI_StorageClose (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_StorageClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_StorageClose
	#define EXT_STI_StorageClose
	#define GET_STI_StorageClose(fl)  CAL_CMGETAPI( "STI_StorageClose" ) 
	#define CAL_STI_StorageClose pICmpCAAStorage->ISTI_StorageClose
	#define CHK_STI_StorageClose (pICmpCAAStorage != NULL)
	#define EXP_STI_StorageClose  CAL_CMEXPAPI( "STI_StorageClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_StorageClose  PFSTI_STORAGECLOSE pfSTI_StorageClose;
	#define EXT_STI_StorageClose  extern PFSTI_STORAGECLOSE pfSTI_StorageClose;
	#define GET_STI_StorageClose(fl)  s_pfCMGetAPI2( "STI_StorageClose", (RTS_VOID_FCTPTR *)&pfSTI_StorageClose, (fl), 0, 0)
	#define CAL_STI_StorageClose  pfSTI_StorageClose
	#define CHK_STI_StorageClose  (pfSTI_StorageClose != NULL)
	#define EXP_STI_StorageClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageClose", (RTS_UINTPTR)STI_StorageClose, 0, 0) 
#endif



STO_ENCODING CDECL STI_StorageGetEncoding(STI_STORAGE hStorage, STO_ERROR *peError);
typedef STO_ENCODING (CDECL * PFSTI_STORAGEGETENCODING) (STI_STORAGE hStorage, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEGETENCODING_NOTIMPLEMENTED)
	#define USE_STI_StorageGetEncoding
	#define EXT_STI_StorageGetEncoding
	#define GET_STI_StorageGetEncoding(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_StorageGetEncoding(p0,p1)  (STO_ENCODING)ERR_NOTIMPLEMENTED
	#define CHK_STI_StorageGetEncoding  FALSE
	#define EXP_STI_StorageGetEncoding  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_StorageGetEncoding
	#define EXT_STI_StorageGetEncoding
	#define GET_STI_StorageGetEncoding(fl)  CAL_CMGETAPI( "STI_StorageGetEncoding" ) 
	#define CAL_STI_StorageGetEncoding  STI_StorageGetEncoding
	#define CHK_STI_StorageGetEncoding  TRUE
	#define EXP_STI_StorageGetEncoding  CAL_CMEXPAPI( "STI_StorageGetEncoding" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_StorageGetEncoding
	#define EXT_STI_StorageGetEncoding
	#define GET_STI_StorageGetEncoding(fl)  CAL_CMGETAPI( "STI_StorageGetEncoding" ) 
	#define CAL_STI_StorageGetEncoding  STI_StorageGetEncoding
	#define CHK_STI_StorageGetEncoding  TRUE
	#define EXP_STI_StorageGetEncoding  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageGetEncoding", (RTS_UINTPTR)STI_StorageGetEncoding, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_StorageGetEncoding
	#define EXT_CmpCAAStorageSTI_StorageGetEncoding
	#define GET_CmpCAAStorageSTI_StorageGetEncoding  ERR_OK
	#define CAL_CmpCAAStorageSTI_StorageGetEncoding pICmpCAAStorage->ISTI_StorageGetEncoding
	#define CHK_CmpCAAStorageSTI_StorageGetEncoding (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_StorageGetEncoding  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_StorageGetEncoding
	#define EXT_STI_StorageGetEncoding
	#define GET_STI_StorageGetEncoding(fl)  CAL_CMGETAPI( "STI_StorageGetEncoding" ) 
	#define CAL_STI_StorageGetEncoding pICmpCAAStorage->ISTI_StorageGetEncoding
	#define CHK_STI_StorageGetEncoding (pICmpCAAStorage != NULL)
	#define EXP_STI_StorageGetEncoding  CAL_CMEXPAPI( "STI_StorageGetEncoding" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_StorageGetEncoding  PFSTI_STORAGEGETENCODING pfSTI_StorageGetEncoding;
	#define EXT_STI_StorageGetEncoding  extern PFSTI_STORAGEGETENCODING pfSTI_StorageGetEncoding;
	#define GET_STI_StorageGetEncoding(fl)  s_pfCMGetAPI2( "STI_StorageGetEncoding", (RTS_VOID_FCTPTR *)&pfSTI_StorageGetEncoding, (fl), 0, 0)
	#define CAL_STI_StorageGetEncoding  pfSTI_StorageGetEncoding
	#define CHK_STI_StorageGetEncoding  (pfSTI_StorageGetEncoding != NULL)
	#define EXP_STI_StorageGetEncoding  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageGetEncoding", (RTS_UINTPTR)STI_StorageGetEncoding, 0, 0) 
#endif



STO_LOCKING_STATE CDECL STI_StorageGetLockingState(STI_STORAGE hStorage, STO_ERROR *peError);
typedef STO_LOCKING_STATE (CDECL * PFSTI_STORAGEGETLOCKINGSTATE) (STI_STORAGE hStorage, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEGETLOCKINGSTATE_NOTIMPLEMENTED)
	#define USE_STI_StorageGetLockingState
	#define EXT_STI_StorageGetLockingState
	#define GET_STI_StorageGetLockingState(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_StorageGetLockingState(p0,p1)  (STO_LOCKING_STATE)ERR_NOTIMPLEMENTED
	#define CHK_STI_StorageGetLockingState  FALSE
	#define EXP_STI_StorageGetLockingState  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_StorageGetLockingState
	#define EXT_STI_StorageGetLockingState
	#define GET_STI_StorageGetLockingState(fl)  CAL_CMGETAPI( "STI_StorageGetLockingState" ) 
	#define CAL_STI_StorageGetLockingState  STI_StorageGetLockingState
	#define CHK_STI_StorageGetLockingState  TRUE
	#define EXP_STI_StorageGetLockingState  CAL_CMEXPAPI( "STI_StorageGetLockingState" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_StorageGetLockingState
	#define EXT_STI_StorageGetLockingState
	#define GET_STI_StorageGetLockingState(fl)  CAL_CMGETAPI( "STI_StorageGetLockingState" ) 
	#define CAL_STI_StorageGetLockingState  STI_StorageGetLockingState
	#define CHK_STI_StorageGetLockingState  TRUE
	#define EXP_STI_StorageGetLockingState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageGetLockingState", (RTS_UINTPTR)STI_StorageGetLockingState, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_StorageGetLockingState
	#define EXT_CmpCAAStorageSTI_StorageGetLockingState
	#define GET_CmpCAAStorageSTI_StorageGetLockingState  ERR_OK
	#define CAL_CmpCAAStorageSTI_StorageGetLockingState pICmpCAAStorage->ISTI_StorageGetLockingState
	#define CHK_CmpCAAStorageSTI_StorageGetLockingState (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_StorageGetLockingState  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_StorageGetLockingState
	#define EXT_STI_StorageGetLockingState
	#define GET_STI_StorageGetLockingState(fl)  CAL_CMGETAPI( "STI_StorageGetLockingState" ) 
	#define CAL_STI_StorageGetLockingState pICmpCAAStorage->ISTI_StorageGetLockingState
	#define CHK_STI_StorageGetLockingState (pICmpCAAStorage != NULL)
	#define EXP_STI_StorageGetLockingState  CAL_CMEXPAPI( "STI_StorageGetLockingState" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_StorageGetLockingState  PFSTI_STORAGEGETLOCKINGSTATE pfSTI_StorageGetLockingState;
	#define EXT_STI_StorageGetLockingState  extern PFSTI_STORAGEGETLOCKINGSTATE pfSTI_StorageGetLockingState;
	#define GET_STI_StorageGetLockingState(fl)  s_pfCMGetAPI2( "STI_StorageGetLockingState", (RTS_VOID_FCTPTR *)&pfSTI_StorageGetLockingState, (fl), 0, 0)
	#define CAL_STI_StorageGetLockingState  pfSTI_StorageGetLockingState
	#define CHK_STI_StorageGetLockingState  (pfSTI_StorageGetLockingState != NULL)
	#define EXP_STI_StorageGetLockingState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageGetLockingState", (RTS_UINTPTR)STI_StorageGetLockingState, 0, 0) 
#endif



STO_ERROR CDECL STI_StorageGetMetrics(STI_STORAGE hStorage, STO_METRICS *pmMetrics);
typedef STO_ERROR (CDECL * PFSTI_STORAGEGETMETRICS) (STI_STORAGE hStorage, STO_METRICS *pmMetrics);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEGETMETRICS_NOTIMPLEMENTED)
	#define USE_STI_StorageGetMetrics
	#define EXT_STI_StorageGetMetrics
	#define GET_STI_StorageGetMetrics(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_StorageGetMetrics(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_StorageGetMetrics  FALSE
	#define EXP_STI_StorageGetMetrics  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_StorageGetMetrics
	#define EXT_STI_StorageGetMetrics
	#define GET_STI_StorageGetMetrics(fl)  CAL_CMGETAPI( "STI_StorageGetMetrics" ) 
	#define CAL_STI_StorageGetMetrics  STI_StorageGetMetrics
	#define CHK_STI_StorageGetMetrics  TRUE
	#define EXP_STI_StorageGetMetrics  CAL_CMEXPAPI( "STI_StorageGetMetrics" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_StorageGetMetrics
	#define EXT_STI_StorageGetMetrics
	#define GET_STI_StorageGetMetrics(fl)  CAL_CMGETAPI( "STI_StorageGetMetrics" ) 
	#define CAL_STI_StorageGetMetrics  STI_StorageGetMetrics
	#define CHK_STI_StorageGetMetrics  TRUE
	#define EXP_STI_StorageGetMetrics  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageGetMetrics", (RTS_UINTPTR)STI_StorageGetMetrics, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_StorageGetMetrics
	#define EXT_CmpCAAStorageSTI_StorageGetMetrics
	#define GET_CmpCAAStorageSTI_StorageGetMetrics  ERR_OK
	#define CAL_CmpCAAStorageSTI_StorageGetMetrics pICmpCAAStorage->ISTI_StorageGetMetrics
	#define CHK_CmpCAAStorageSTI_StorageGetMetrics (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_StorageGetMetrics  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_StorageGetMetrics
	#define EXT_STI_StorageGetMetrics
	#define GET_STI_StorageGetMetrics(fl)  CAL_CMGETAPI( "STI_StorageGetMetrics" ) 
	#define CAL_STI_StorageGetMetrics pICmpCAAStorage->ISTI_StorageGetMetrics
	#define CHK_STI_StorageGetMetrics (pICmpCAAStorage != NULL)
	#define EXP_STI_StorageGetMetrics  CAL_CMEXPAPI( "STI_StorageGetMetrics" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_StorageGetMetrics  PFSTI_STORAGEGETMETRICS pfSTI_StorageGetMetrics;
	#define EXT_STI_StorageGetMetrics  extern PFSTI_STORAGEGETMETRICS pfSTI_StorageGetMetrics;
	#define GET_STI_StorageGetMetrics(fl)  s_pfCMGetAPI2( "STI_StorageGetMetrics", (RTS_VOID_FCTPTR *)&pfSTI_StorageGetMetrics, (fl), 0, 0)
	#define CAL_STI_StorageGetMetrics  pfSTI_StorageGetMetrics
	#define CHK_STI_StorageGetMetrics  (pfSTI_StorageGetMetrics != NULL)
	#define EXP_STI_StorageGetMetrics  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageGetMetrics", (RTS_UINTPTR)STI_StorageGetMetrics, 0, 0) 
#endif



CAA_COUNT CDECL STI_StorageGetNumOfTables(STI_STORAGE hStorage, STO_ERROR *peError);
typedef CAA_COUNT (CDECL * PFSTI_STORAGEGETNUMOFTABLES) (STI_STORAGE hStorage, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEGETNUMOFTABLES_NOTIMPLEMENTED)
	#define USE_STI_StorageGetNumOfTables
	#define EXT_STI_StorageGetNumOfTables
	#define GET_STI_StorageGetNumOfTables(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_StorageGetNumOfTables(p0,p1)  (CAA_COUNT)ERR_NOTIMPLEMENTED
	#define CHK_STI_StorageGetNumOfTables  FALSE
	#define EXP_STI_StorageGetNumOfTables  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_StorageGetNumOfTables
	#define EXT_STI_StorageGetNumOfTables
	#define GET_STI_StorageGetNumOfTables(fl)  CAL_CMGETAPI( "STI_StorageGetNumOfTables" ) 
	#define CAL_STI_StorageGetNumOfTables  STI_StorageGetNumOfTables
	#define CHK_STI_StorageGetNumOfTables  TRUE
	#define EXP_STI_StorageGetNumOfTables  CAL_CMEXPAPI( "STI_StorageGetNumOfTables" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_StorageGetNumOfTables
	#define EXT_STI_StorageGetNumOfTables
	#define GET_STI_StorageGetNumOfTables(fl)  CAL_CMGETAPI( "STI_StorageGetNumOfTables" ) 
	#define CAL_STI_StorageGetNumOfTables  STI_StorageGetNumOfTables
	#define CHK_STI_StorageGetNumOfTables  TRUE
	#define EXP_STI_StorageGetNumOfTables  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageGetNumOfTables", (RTS_UINTPTR)STI_StorageGetNumOfTables, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_StorageGetNumOfTables
	#define EXT_CmpCAAStorageSTI_StorageGetNumOfTables
	#define GET_CmpCAAStorageSTI_StorageGetNumOfTables  ERR_OK
	#define CAL_CmpCAAStorageSTI_StorageGetNumOfTables pICmpCAAStorage->ISTI_StorageGetNumOfTables
	#define CHK_CmpCAAStorageSTI_StorageGetNumOfTables (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_StorageGetNumOfTables  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_StorageGetNumOfTables
	#define EXT_STI_StorageGetNumOfTables
	#define GET_STI_StorageGetNumOfTables(fl)  CAL_CMGETAPI( "STI_StorageGetNumOfTables" ) 
	#define CAL_STI_StorageGetNumOfTables pICmpCAAStorage->ISTI_StorageGetNumOfTables
	#define CHK_STI_StorageGetNumOfTables (pICmpCAAStorage != NULL)
	#define EXP_STI_StorageGetNumOfTables  CAL_CMEXPAPI( "STI_StorageGetNumOfTables" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_StorageGetNumOfTables  PFSTI_STORAGEGETNUMOFTABLES pfSTI_StorageGetNumOfTables;
	#define EXT_STI_StorageGetNumOfTables  extern PFSTI_STORAGEGETNUMOFTABLES pfSTI_StorageGetNumOfTables;
	#define GET_STI_StorageGetNumOfTables(fl)  s_pfCMGetAPI2( "STI_StorageGetNumOfTables", (RTS_VOID_FCTPTR *)&pfSTI_StorageGetNumOfTables, (fl), 0, 0)
	#define CAL_STI_StorageGetNumOfTables  pfSTI_StorageGetNumOfTables
	#define CHK_STI_StorageGetNumOfTables  (pfSTI_StorageGetNumOfTables != NULL)
	#define EXP_STI_StorageGetNumOfTables  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageGetNumOfTables", (RTS_UINTPTR)STI_StorageGetNumOfTables, 0, 0) 
#endif



STO_ERROR CDECL STI_StorageGetPath(STI_STORAGE hStorage, CAA_FILENAME *psPath);
typedef STO_ERROR (CDECL * PFSTI_STORAGEGETPATH) (STI_STORAGE hStorage, CAA_FILENAME *psPath);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEGETPATH_NOTIMPLEMENTED)
	#define USE_STI_StorageGetPath
	#define EXT_STI_StorageGetPath
	#define GET_STI_StorageGetPath(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_StorageGetPath(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_StorageGetPath  FALSE
	#define EXP_STI_StorageGetPath  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_StorageGetPath
	#define EXT_STI_StorageGetPath
	#define GET_STI_StorageGetPath(fl)  CAL_CMGETAPI( "STI_StorageGetPath" ) 
	#define CAL_STI_StorageGetPath  STI_StorageGetPath
	#define CHK_STI_StorageGetPath  TRUE
	#define EXP_STI_StorageGetPath  CAL_CMEXPAPI( "STI_StorageGetPath" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_StorageGetPath
	#define EXT_STI_StorageGetPath
	#define GET_STI_StorageGetPath(fl)  CAL_CMGETAPI( "STI_StorageGetPath" ) 
	#define CAL_STI_StorageGetPath  STI_StorageGetPath
	#define CHK_STI_StorageGetPath  TRUE
	#define EXP_STI_StorageGetPath  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageGetPath", (RTS_UINTPTR)STI_StorageGetPath, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_StorageGetPath
	#define EXT_CmpCAAStorageSTI_StorageGetPath
	#define GET_CmpCAAStorageSTI_StorageGetPath  ERR_OK
	#define CAL_CmpCAAStorageSTI_StorageGetPath pICmpCAAStorage->ISTI_StorageGetPath
	#define CHK_CmpCAAStorageSTI_StorageGetPath (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_StorageGetPath  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_StorageGetPath
	#define EXT_STI_StorageGetPath
	#define GET_STI_StorageGetPath(fl)  CAL_CMGETAPI( "STI_StorageGetPath" ) 
	#define CAL_STI_StorageGetPath pICmpCAAStorage->ISTI_StorageGetPath
	#define CHK_STI_StorageGetPath (pICmpCAAStorage != NULL)
	#define EXP_STI_StorageGetPath  CAL_CMEXPAPI( "STI_StorageGetPath" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_StorageGetPath  PFSTI_STORAGEGETPATH pfSTI_StorageGetPath;
	#define EXT_STI_StorageGetPath  extern PFSTI_STORAGEGETPATH pfSTI_StorageGetPath;
	#define GET_STI_StorageGetPath(fl)  s_pfCMGetAPI2( "STI_StorageGetPath", (RTS_VOID_FCTPTR *)&pfSTI_StorageGetPath, (fl), 0, 0)
	#define CAL_STI_StorageGetPath  pfSTI_StorageGetPath
	#define CHK_STI_StorageGetPath  (pfSTI_StorageGetPath != NULL)
	#define EXP_STI_StorageGetPath  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageGetPath", (RTS_UINTPTR)STI_StorageGetPath, 0, 0) 
#endif



CAA_DINT CDECL STI_StorageGetSchemaVersion(STI_STORAGE hStorage, STO_ERROR *peError);
typedef CAA_DINT (CDECL * PFSTI_STORAGEGETSCHEMAVERSION) (STI_STORAGE hStorage, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEGETSCHEMAVERSION_NOTIMPLEMENTED)
	#define USE_STI_StorageGetSchemaVersion
	#define EXT_STI_StorageGetSchemaVersion
	#define GET_STI_StorageGetSchemaVersion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_StorageGetSchemaVersion(p0,p1)  (CAA_DINT)ERR_NOTIMPLEMENTED
	#define CHK_STI_StorageGetSchemaVersion  FALSE
	#define EXP_STI_StorageGetSchemaVersion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_StorageGetSchemaVersion
	#define EXT_STI_StorageGetSchemaVersion
	#define GET_STI_StorageGetSchemaVersion(fl)  CAL_CMGETAPI( "STI_StorageGetSchemaVersion" ) 
	#define CAL_STI_StorageGetSchemaVersion  STI_StorageGetSchemaVersion
	#define CHK_STI_StorageGetSchemaVersion  TRUE
	#define EXP_STI_StorageGetSchemaVersion  CAL_CMEXPAPI( "STI_StorageGetSchemaVersion" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_StorageGetSchemaVersion
	#define EXT_STI_StorageGetSchemaVersion
	#define GET_STI_StorageGetSchemaVersion(fl)  CAL_CMGETAPI( "STI_StorageGetSchemaVersion" ) 
	#define CAL_STI_StorageGetSchemaVersion  STI_StorageGetSchemaVersion
	#define CHK_STI_StorageGetSchemaVersion  TRUE
	#define EXP_STI_StorageGetSchemaVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageGetSchemaVersion", (RTS_UINTPTR)STI_StorageGetSchemaVersion, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_StorageGetSchemaVersion
	#define EXT_CmpCAAStorageSTI_StorageGetSchemaVersion
	#define GET_CmpCAAStorageSTI_StorageGetSchemaVersion  ERR_OK
	#define CAL_CmpCAAStorageSTI_StorageGetSchemaVersion pICmpCAAStorage->ISTI_StorageGetSchemaVersion
	#define CHK_CmpCAAStorageSTI_StorageGetSchemaVersion (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_StorageGetSchemaVersion  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_StorageGetSchemaVersion
	#define EXT_STI_StorageGetSchemaVersion
	#define GET_STI_StorageGetSchemaVersion(fl)  CAL_CMGETAPI( "STI_StorageGetSchemaVersion" ) 
	#define CAL_STI_StorageGetSchemaVersion pICmpCAAStorage->ISTI_StorageGetSchemaVersion
	#define CHK_STI_StorageGetSchemaVersion (pICmpCAAStorage != NULL)
	#define EXP_STI_StorageGetSchemaVersion  CAL_CMEXPAPI( "STI_StorageGetSchemaVersion" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_StorageGetSchemaVersion  PFSTI_STORAGEGETSCHEMAVERSION pfSTI_StorageGetSchemaVersion;
	#define EXT_STI_StorageGetSchemaVersion  extern PFSTI_STORAGEGETSCHEMAVERSION pfSTI_StorageGetSchemaVersion;
	#define GET_STI_StorageGetSchemaVersion(fl)  s_pfCMGetAPI2( "STI_StorageGetSchemaVersion", (RTS_VOID_FCTPTR *)&pfSTI_StorageGetSchemaVersion, (fl), 0, 0)
	#define CAL_STI_StorageGetSchemaVersion  pfSTI_StorageGetSchemaVersion
	#define CHK_STI_StorageGetSchemaVersion  (pfSTI_StorageGetSchemaVersion != NULL)
	#define EXP_STI_StorageGetSchemaVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageGetSchemaVersion", (RTS_UINTPTR)STI_StorageGetSchemaVersion, 0, 0) 
#endif



CAA_DINT CDECL STI_StorageGetStorageVersion(STI_STORAGE hStorage, STO_ERROR *peError);
typedef CAA_DINT (CDECL * PFSTI_STORAGEGETSTORAGEVERSION) (STI_STORAGE hStorage, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEGETSTORAGEVERSION_NOTIMPLEMENTED)
	#define USE_STI_StorageGetStorageVersion
	#define EXT_STI_StorageGetStorageVersion
	#define GET_STI_StorageGetStorageVersion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_StorageGetStorageVersion(p0,p1)  (CAA_DINT)ERR_NOTIMPLEMENTED
	#define CHK_STI_StorageGetStorageVersion  FALSE
	#define EXP_STI_StorageGetStorageVersion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_StorageGetStorageVersion
	#define EXT_STI_StorageGetStorageVersion
	#define GET_STI_StorageGetStorageVersion(fl)  CAL_CMGETAPI( "STI_StorageGetStorageVersion" ) 
	#define CAL_STI_StorageGetStorageVersion  STI_StorageGetStorageVersion
	#define CHK_STI_StorageGetStorageVersion  TRUE
	#define EXP_STI_StorageGetStorageVersion  CAL_CMEXPAPI( "STI_StorageGetStorageVersion" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_StorageGetStorageVersion
	#define EXT_STI_StorageGetStorageVersion
	#define GET_STI_StorageGetStorageVersion(fl)  CAL_CMGETAPI( "STI_StorageGetStorageVersion" ) 
	#define CAL_STI_StorageGetStorageVersion  STI_StorageGetStorageVersion
	#define CHK_STI_StorageGetStorageVersion  TRUE
	#define EXP_STI_StorageGetStorageVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageGetStorageVersion", (RTS_UINTPTR)STI_StorageGetStorageVersion, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_StorageGetStorageVersion
	#define EXT_CmpCAAStorageSTI_StorageGetStorageVersion
	#define GET_CmpCAAStorageSTI_StorageGetStorageVersion  ERR_OK
	#define CAL_CmpCAAStorageSTI_StorageGetStorageVersion pICmpCAAStorage->ISTI_StorageGetStorageVersion
	#define CHK_CmpCAAStorageSTI_StorageGetStorageVersion (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_StorageGetStorageVersion  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_StorageGetStorageVersion
	#define EXT_STI_StorageGetStorageVersion
	#define GET_STI_StorageGetStorageVersion(fl)  CAL_CMGETAPI( "STI_StorageGetStorageVersion" ) 
	#define CAL_STI_StorageGetStorageVersion pICmpCAAStorage->ISTI_StorageGetStorageVersion
	#define CHK_STI_StorageGetStorageVersion (pICmpCAAStorage != NULL)
	#define EXP_STI_StorageGetStorageVersion  CAL_CMEXPAPI( "STI_StorageGetStorageVersion" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_StorageGetStorageVersion  PFSTI_STORAGEGETSTORAGEVERSION pfSTI_StorageGetStorageVersion;
	#define EXT_STI_StorageGetStorageVersion  extern PFSTI_STORAGEGETSTORAGEVERSION pfSTI_StorageGetStorageVersion;
	#define GET_STI_StorageGetStorageVersion(fl)  s_pfCMGetAPI2( "STI_StorageGetStorageVersion", (RTS_VOID_FCTPTR *)&pfSTI_StorageGetStorageVersion, (fl), 0, 0)
	#define CAL_STI_StorageGetStorageVersion  pfSTI_StorageGetStorageVersion
	#define CHK_STI_StorageGetStorageVersion  (pfSTI_StorageGetStorageVersion != NULL)
	#define EXP_STI_StorageGetStorageVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageGetStorageVersion", (RTS_UINTPTR)STI_StorageGetStorageVersion, 0, 0) 
#endif



CAA_DINT CDECL STI_StorageGetUserVersion(STI_STORAGE hStorage, STO_ERROR *peError);
typedef CAA_DINT (CDECL * PFSTI_STORAGEGETUSERVERSION) (STI_STORAGE hStorage, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEGETUSERVERSION_NOTIMPLEMENTED)
	#define USE_STI_StorageGetUserVersion
	#define EXT_STI_StorageGetUserVersion
	#define GET_STI_StorageGetUserVersion(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_StorageGetUserVersion(p0,p1)  (CAA_DINT)ERR_NOTIMPLEMENTED
	#define CHK_STI_StorageGetUserVersion  FALSE
	#define EXP_STI_StorageGetUserVersion  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_StorageGetUserVersion
	#define EXT_STI_StorageGetUserVersion
	#define GET_STI_StorageGetUserVersion(fl)  CAL_CMGETAPI( "STI_StorageGetUserVersion" ) 
	#define CAL_STI_StorageGetUserVersion  STI_StorageGetUserVersion
	#define CHK_STI_StorageGetUserVersion  TRUE
	#define EXP_STI_StorageGetUserVersion  CAL_CMEXPAPI( "STI_StorageGetUserVersion" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_StorageGetUserVersion
	#define EXT_STI_StorageGetUserVersion
	#define GET_STI_StorageGetUserVersion(fl)  CAL_CMGETAPI( "STI_StorageGetUserVersion" ) 
	#define CAL_STI_StorageGetUserVersion  STI_StorageGetUserVersion
	#define CHK_STI_StorageGetUserVersion  TRUE
	#define EXP_STI_StorageGetUserVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageGetUserVersion", (RTS_UINTPTR)STI_StorageGetUserVersion, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_StorageGetUserVersion
	#define EXT_CmpCAAStorageSTI_StorageGetUserVersion
	#define GET_CmpCAAStorageSTI_StorageGetUserVersion  ERR_OK
	#define CAL_CmpCAAStorageSTI_StorageGetUserVersion pICmpCAAStorage->ISTI_StorageGetUserVersion
	#define CHK_CmpCAAStorageSTI_StorageGetUserVersion (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_StorageGetUserVersion  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_StorageGetUserVersion
	#define EXT_STI_StorageGetUserVersion
	#define GET_STI_StorageGetUserVersion(fl)  CAL_CMGETAPI( "STI_StorageGetUserVersion" ) 
	#define CAL_STI_StorageGetUserVersion pICmpCAAStorage->ISTI_StorageGetUserVersion
	#define CHK_STI_StorageGetUserVersion (pICmpCAAStorage != NULL)
	#define EXP_STI_StorageGetUserVersion  CAL_CMEXPAPI( "STI_StorageGetUserVersion" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_StorageGetUserVersion  PFSTI_STORAGEGETUSERVERSION pfSTI_StorageGetUserVersion;
	#define EXT_STI_StorageGetUserVersion  extern PFSTI_STORAGEGETUSERVERSION pfSTI_StorageGetUserVersion;
	#define GET_STI_StorageGetUserVersion(fl)  s_pfCMGetAPI2( "STI_StorageGetUserVersion", (RTS_VOID_FCTPTR *)&pfSTI_StorageGetUserVersion, (fl), 0, 0)
	#define CAL_STI_StorageGetUserVersion  pfSTI_StorageGetUserVersion
	#define CHK_STI_StorageGetUserVersion  (pfSTI_StorageGetUserVersion != NULL)
	#define EXP_STI_StorageGetUserVersion  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageGetUserVersion", (RTS_UINTPTR)STI_StorageGetUserVersion, 0, 0) 
#endif



CAA_BOOL CDECL STI_StorageIsReadOnly(STI_STORAGE hStorage, STO_ERROR *peError);
typedef CAA_BOOL (CDECL * PFSTI_STORAGEISREADONLY) (STI_STORAGE hStorage, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEISREADONLY_NOTIMPLEMENTED)
	#define USE_STI_StorageIsReadOnly
	#define EXT_STI_StorageIsReadOnly
	#define GET_STI_StorageIsReadOnly(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_StorageIsReadOnly(p0,p1)  (CAA_BOOL)ERR_NOTIMPLEMENTED
	#define CHK_STI_StorageIsReadOnly  FALSE
	#define EXP_STI_StorageIsReadOnly  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_StorageIsReadOnly
	#define EXT_STI_StorageIsReadOnly
	#define GET_STI_StorageIsReadOnly(fl)  CAL_CMGETAPI( "STI_StorageIsReadOnly" ) 
	#define CAL_STI_StorageIsReadOnly  STI_StorageIsReadOnly
	#define CHK_STI_StorageIsReadOnly  TRUE
	#define EXP_STI_StorageIsReadOnly  CAL_CMEXPAPI( "STI_StorageIsReadOnly" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_StorageIsReadOnly
	#define EXT_STI_StorageIsReadOnly
	#define GET_STI_StorageIsReadOnly(fl)  CAL_CMGETAPI( "STI_StorageIsReadOnly" ) 
	#define CAL_STI_StorageIsReadOnly  STI_StorageIsReadOnly
	#define CHK_STI_StorageIsReadOnly  TRUE
	#define EXP_STI_StorageIsReadOnly  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageIsReadOnly", (RTS_UINTPTR)STI_StorageIsReadOnly, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_StorageIsReadOnly
	#define EXT_CmpCAAStorageSTI_StorageIsReadOnly
	#define GET_CmpCAAStorageSTI_StorageIsReadOnly  ERR_OK
	#define CAL_CmpCAAStorageSTI_StorageIsReadOnly pICmpCAAStorage->ISTI_StorageIsReadOnly
	#define CHK_CmpCAAStorageSTI_StorageIsReadOnly (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_StorageIsReadOnly  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_StorageIsReadOnly
	#define EXT_STI_StorageIsReadOnly
	#define GET_STI_StorageIsReadOnly(fl)  CAL_CMGETAPI( "STI_StorageIsReadOnly" ) 
	#define CAL_STI_StorageIsReadOnly pICmpCAAStorage->ISTI_StorageIsReadOnly
	#define CHK_STI_StorageIsReadOnly (pICmpCAAStorage != NULL)
	#define EXP_STI_StorageIsReadOnly  CAL_CMEXPAPI( "STI_StorageIsReadOnly" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_StorageIsReadOnly  PFSTI_STORAGEISREADONLY pfSTI_StorageIsReadOnly;
	#define EXT_STI_StorageIsReadOnly  extern PFSTI_STORAGEISREADONLY pfSTI_StorageIsReadOnly;
	#define GET_STI_StorageIsReadOnly(fl)  s_pfCMGetAPI2( "STI_StorageIsReadOnly", (RTS_VOID_FCTPTR *)&pfSTI_StorageIsReadOnly, (fl), 0, 0)
	#define CAL_STI_StorageIsReadOnly  pfSTI_StorageIsReadOnly
	#define CHK_STI_StorageIsReadOnly  (pfSTI_StorageIsReadOnly != NULL)
	#define EXP_STI_StorageIsReadOnly  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageIsReadOnly", (RTS_UINTPTR)STI_StorageIsReadOnly, 0, 0) 
#endif



STI_STORAGE CDECL STI_StorageOpenFile(CAA_FILENAME sPath, CAA_BOOL xReadOnly, STO_ERROR *peError);
typedef STI_STORAGE (CDECL * PFSTI_STORAGEOPENFILE) (CAA_FILENAME sPath, CAA_BOOL xReadOnly, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEOPENFILE_NOTIMPLEMENTED)
	#define USE_STI_StorageOpenFile
	#define EXT_STI_StorageOpenFile
	#define GET_STI_StorageOpenFile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_StorageOpenFile(p0,p1,p2)  (STI_STORAGE)ERR_NOTIMPLEMENTED
	#define CHK_STI_StorageOpenFile  FALSE
	#define EXP_STI_StorageOpenFile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_StorageOpenFile
	#define EXT_STI_StorageOpenFile
	#define GET_STI_StorageOpenFile(fl)  CAL_CMGETAPI( "STI_StorageOpenFile" ) 
	#define CAL_STI_StorageOpenFile  STI_StorageOpenFile
	#define CHK_STI_StorageOpenFile  TRUE
	#define EXP_STI_StorageOpenFile  CAL_CMEXPAPI( "STI_StorageOpenFile" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_StorageOpenFile
	#define EXT_STI_StorageOpenFile
	#define GET_STI_StorageOpenFile(fl)  CAL_CMGETAPI( "STI_StorageOpenFile" ) 
	#define CAL_STI_StorageOpenFile  STI_StorageOpenFile
	#define CHK_STI_StorageOpenFile  TRUE
	#define EXP_STI_StorageOpenFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageOpenFile", (RTS_UINTPTR)STI_StorageOpenFile, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_StorageOpenFile
	#define EXT_CmpCAAStorageSTI_StorageOpenFile
	#define GET_CmpCAAStorageSTI_StorageOpenFile  ERR_OK
	#define CAL_CmpCAAStorageSTI_StorageOpenFile pICmpCAAStorage->ISTI_StorageOpenFile
	#define CHK_CmpCAAStorageSTI_StorageOpenFile (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_StorageOpenFile  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_StorageOpenFile
	#define EXT_STI_StorageOpenFile
	#define GET_STI_StorageOpenFile(fl)  CAL_CMGETAPI( "STI_StorageOpenFile" ) 
	#define CAL_STI_StorageOpenFile pICmpCAAStorage->ISTI_StorageOpenFile
	#define CHK_STI_StorageOpenFile (pICmpCAAStorage != NULL)
	#define EXP_STI_StorageOpenFile  CAL_CMEXPAPI( "STI_StorageOpenFile" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_StorageOpenFile  PFSTI_STORAGEOPENFILE pfSTI_StorageOpenFile;
	#define EXT_STI_StorageOpenFile  extern PFSTI_STORAGEOPENFILE pfSTI_StorageOpenFile;
	#define GET_STI_StorageOpenFile(fl)  s_pfCMGetAPI2( "STI_StorageOpenFile", (RTS_VOID_FCTPTR *)&pfSTI_StorageOpenFile, (fl), 0, 0)
	#define CAL_STI_StorageOpenFile  pfSTI_StorageOpenFile
	#define CHK_STI_StorageOpenFile  (pfSTI_StorageOpenFile != NULL)
	#define EXP_STI_StorageOpenFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageOpenFile", (RTS_UINTPTR)STI_StorageOpenFile, 0, 0) 
#endif



STO_ERROR CDECL STI_StorageReorg(STI_STORAGE hStorage);
typedef STO_ERROR (CDECL * PFSTI_STORAGEREORG) (STI_STORAGE hStorage);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEREORG_NOTIMPLEMENTED)
	#define USE_STI_StorageReorg
	#define EXT_STI_StorageReorg
	#define GET_STI_StorageReorg(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_StorageReorg(p0)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_StorageReorg  FALSE
	#define EXP_STI_StorageReorg  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_StorageReorg
	#define EXT_STI_StorageReorg
	#define GET_STI_StorageReorg(fl)  CAL_CMGETAPI( "STI_StorageReorg" ) 
	#define CAL_STI_StorageReorg  STI_StorageReorg
	#define CHK_STI_StorageReorg  TRUE
	#define EXP_STI_StorageReorg  CAL_CMEXPAPI( "STI_StorageReorg" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_StorageReorg
	#define EXT_STI_StorageReorg
	#define GET_STI_StorageReorg(fl)  CAL_CMGETAPI( "STI_StorageReorg" ) 
	#define CAL_STI_StorageReorg  STI_StorageReorg
	#define CHK_STI_StorageReorg  TRUE
	#define EXP_STI_StorageReorg  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageReorg", (RTS_UINTPTR)STI_StorageReorg, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_StorageReorg
	#define EXT_CmpCAAStorageSTI_StorageReorg
	#define GET_CmpCAAStorageSTI_StorageReorg  ERR_OK
	#define CAL_CmpCAAStorageSTI_StorageReorg pICmpCAAStorage->ISTI_StorageReorg
	#define CHK_CmpCAAStorageSTI_StorageReorg (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_StorageReorg  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_StorageReorg
	#define EXT_STI_StorageReorg
	#define GET_STI_StorageReorg(fl)  CAL_CMGETAPI( "STI_StorageReorg" ) 
	#define CAL_STI_StorageReorg pICmpCAAStorage->ISTI_StorageReorg
	#define CHK_STI_StorageReorg (pICmpCAAStorage != NULL)
	#define EXP_STI_StorageReorg  CAL_CMEXPAPI( "STI_StorageReorg" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_StorageReorg  PFSTI_STORAGEREORG pfSTI_StorageReorg;
	#define EXT_STI_StorageReorg  extern PFSTI_STORAGEREORG pfSTI_StorageReorg;
	#define GET_STI_StorageReorg(fl)  s_pfCMGetAPI2( "STI_StorageReorg", (RTS_VOID_FCTPTR *)&pfSTI_StorageReorg, (fl), 0, 0)
	#define CAL_STI_StorageReorg  pfSTI_StorageReorg
	#define CHK_STI_StorageReorg  (pfSTI_StorageReorg != NULL)
	#define EXP_STI_StorageReorg  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageReorg", (RTS_UINTPTR)STI_StorageReorg, 0, 0) 
#endif



STO_ERROR CDECL STI_TableClear(STI_TABLE hTable);
typedef STO_ERROR (CDECL * PFSTI_TABLECLEAR) (STI_TABLE hTable);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TABLECLEAR_NOTIMPLEMENTED)
	#define USE_STI_TableClear
	#define EXT_STI_TableClear
	#define GET_STI_TableClear(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_TableClear(p0)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_TableClear  FALSE
	#define EXP_STI_TableClear  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_TableClear
	#define EXT_STI_TableClear
	#define GET_STI_TableClear(fl)  CAL_CMGETAPI( "STI_TableClear" ) 
	#define CAL_STI_TableClear  STI_TableClear
	#define CHK_STI_TableClear  TRUE
	#define EXP_STI_TableClear  CAL_CMEXPAPI( "STI_TableClear" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_TableClear
	#define EXT_STI_TableClear
	#define GET_STI_TableClear(fl)  CAL_CMGETAPI( "STI_TableClear" ) 
	#define CAL_STI_TableClear  STI_TableClear
	#define CHK_STI_TableClear  TRUE
	#define EXP_STI_TableClear  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TableClear", (RTS_UINTPTR)STI_TableClear, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_TableClear
	#define EXT_CmpCAAStorageSTI_TableClear
	#define GET_CmpCAAStorageSTI_TableClear  ERR_OK
	#define CAL_CmpCAAStorageSTI_TableClear pICmpCAAStorage->ISTI_TableClear
	#define CHK_CmpCAAStorageSTI_TableClear (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_TableClear  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_TableClear
	#define EXT_STI_TableClear
	#define GET_STI_TableClear(fl)  CAL_CMGETAPI( "STI_TableClear" ) 
	#define CAL_STI_TableClear pICmpCAAStorage->ISTI_TableClear
	#define CHK_STI_TableClear (pICmpCAAStorage != NULL)
	#define EXP_STI_TableClear  CAL_CMEXPAPI( "STI_TableClear" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_TableClear  PFSTI_TABLECLEAR pfSTI_TableClear;
	#define EXT_STI_TableClear  extern PFSTI_TABLECLEAR pfSTI_TableClear;
	#define GET_STI_TableClear(fl)  s_pfCMGetAPI2( "STI_TableClear", (RTS_VOID_FCTPTR *)&pfSTI_TableClear, (fl), 0, 0)
	#define CAL_STI_TableClear  pfSTI_TableClear
	#define CHK_STI_TableClear  (pfSTI_TableClear != NULL)
	#define EXP_STI_TableClear  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TableClear", (RTS_UINTPTR)STI_TableClear, 0, 0) 
#endif



STO_ERROR CDECL STI_TableClose(STI_TABLE hTable);
typedef STO_ERROR (CDECL * PFSTI_TABLECLOSE) (STI_TABLE hTable);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TABLECLOSE_NOTIMPLEMENTED)
	#define USE_STI_TableClose
	#define EXT_STI_TableClose
	#define GET_STI_TableClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_TableClose(p0)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_TableClose  FALSE
	#define EXP_STI_TableClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_TableClose
	#define EXT_STI_TableClose
	#define GET_STI_TableClose(fl)  CAL_CMGETAPI( "STI_TableClose" ) 
	#define CAL_STI_TableClose  STI_TableClose
	#define CHK_STI_TableClose  TRUE
	#define EXP_STI_TableClose  CAL_CMEXPAPI( "STI_TableClose" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_TableClose
	#define EXT_STI_TableClose
	#define GET_STI_TableClose(fl)  CAL_CMGETAPI( "STI_TableClose" ) 
	#define CAL_STI_TableClose  STI_TableClose
	#define CHK_STI_TableClose  TRUE
	#define EXP_STI_TableClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TableClose", (RTS_UINTPTR)STI_TableClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_TableClose
	#define EXT_CmpCAAStorageSTI_TableClose
	#define GET_CmpCAAStorageSTI_TableClose  ERR_OK
	#define CAL_CmpCAAStorageSTI_TableClose pICmpCAAStorage->ISTI_TableClose
	#define CHK_CmpCAAStorageSTI_TableClose (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_TableClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_TableClose
	#define EXT_STI_TableClose
	#define GET_STI_TableClose(fl)  CAL_CMGETAPI( "STI_TableClose" ) 
	#define CAL_STI_TableClose pICmpCAAStorage->ISTI_TableClose
	#define CHK_STI_TableClose (pICmpCAAStorage != NULL)
	#define EXP_STI_TableClose  CAL_CMEXPAPI( "STI_TableClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_TableClose  PFSTI_TABLECLOSE pfSTI_TableClose;
	#define EXT_STI_TableClose  extern PFSTI_TABLECLOSE pfSTI_TableClose;
	#define GET_STI_TableClose(fl)  s_pfCMGetAPI2( "STI_TableClose", (RTS_VOID_FCTPTR *)&pfSTI_TableClose, (fl), 0, 0)
	#define CAL_STI_TableClose  pfSTI_TableClose
	#define CHK_STI_TableClose  (pfSTI_TableClose != NULL)
	#define EXP_STI_TableClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TableClose", (RTS_UINTPTR)STI_TableClose, 0, 0) 
#endif



CAA_IDENT CDECL STI_TableGetId(STI_TABLE hTable, STO_ERROR *peError);
typedef CAA_IDENT (CDECL * PFSTI_TABLEGETID) (STI_TABLE hTable, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TABLEGETID_NOTIMPLEMENTED)
	#define USE_STI_TableGetId
	#define EXT_STI_TableGetId
	#define GET_STI_TableGetId(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_TableGetId(p0,p1)  (CAA_IDENT)ERR_NOTIMPLEMENTED
	#define CHK_STI_TableGetId  FALSE
	#define EXP_STI_TableGetId  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_TableGetId
	#define EXT_STI_TableGetId
	#define GET_STI_TableGetId(fl)  CAL_CMGETAPI( "STI_TableGetId" ) 
	#define CAL_STI_TableGetId  STI_TableGetId
	#define CHK_STI_TableGetId  TRUE
	#define EXP_STI_TableGetId  CAL_CMEXPAPI( "STI_TableGetId" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_TableGetId
	#define EXT_STI_TableGetId
	#define GET_STI_TableGetId(fl)  CAL_CMGETAPI( "STI_TableGetId" ) 
	#define CAL_STI_TableGetId  STI_TableGetId
	#define CHK_STI_TableGetId  TRUE
	#define EXP_STI_TableGetId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TableGetId", (RTS_UINTPTR)STI_TableGetId, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_TableGetId
	#define EXT_CmpCAAStorageSTI_TableGetId
	#define GET_CmpCAAStorageSTI_TableGetId  ERR_OK
	#define CAL_CmpCAAStorageSTI_TableGetId pICmpCAAStorage->ISTI_TableGetId
	#define CHK_CmpCAAStorageSTI_TableGetId (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_TableGetId  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_TableGetId
	#define EXT_STI_TableGetId
	#define GET_STI_TableGetId(fl)  CAL_CMGETAPI( "STI_TableGetId" ) 
	#define CAL_STI_TableGetId pICmpCAAStorage->ISTI_TableGetId
	#define CHK_STI_TableGetId (pICmpCAAStorage != NULL)
	#define EXP_STI_TableGetId  CAL_CMEXPAPI( "STI_TableGetId" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_TableGetId  PFSTI_TABLEGETID pfSTI_TableGetId;
	#define EXT_STI_TableGetId  extern PFSTI_TABLEGETID pfSTI_TableGetId;
	#define GET_STI_TableGetId(fl)  s_pfCMGetAPI2( "STI_TableGetId", (RTS_VOID_FCTPTR *)&pfSTI_TableGetId, (fl), 0, 0)
	#define CAL_STI_TableGetId  pfSTI_TableGetId
	#define CHK_STI_TableGetId  (pfSTI_TableGetId != NULL)
	#define EXP_STI_TableGetId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TableGetId", (RTS_UINTPTR)STI_TableGetId, 0, 0) 
#endif



STO_ERROR CDECL STI_TableGetMinMaxRowIds(STI_TABLE hTable, RTS_IEC_LINT *pliRowIdMin, RTS_IEC_LINT *pliRowIdMax);
typedef STO_ERROR (CDECL * PFSTI_TABLEGETMINMAXROWIDS) (STI_TABLE hTable, RTS_IEC_LINT *pliRowIdMin, RTS_IEC_LINT *pliRowIdMax);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TABLEGETMINMAXROWIDS_NOTIMPLEMENTED)
	#define USE_STI_TableGetMinMaxRowIds
	#define EXT_STI_TableGetMinMaxRowIds
	#define GET_STI_TableGetMinMaxRowIds(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_TableGetMinMaxRowIds(p0,p1,p2)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_TableGetMinMaxRowIds  FALSE
	#define EXP_STI_TableGetMinMaxRowIds  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_TableGetMinMaxRowIds
	#define EXT_STI_TableGetMinMaxRowIds
	#define GET_STI_TableGetMinMaxRowIds(fl)  CAL_CMGETAPI( "STI_TableGetMinMaxRowIds" ) 
	#define CAL_STI_TableGetMinMaxRowIds  STI_TableGetMinMaxRowIds
	#define CHK_STI_TableGetMinMaxRowIds  TRUE
	#define EXP_STI_TableGetMinMaxRowIds  CAL_CMEXPAPI( "STI_TableGetMinMaxRowIds" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_TableGetMinMaxRowIds
	#define EXT_STI_TableGetMinMaxRowIds
	#define GET_STI_TableGetMinMaxRowIds(fl)  CAL_CMGETAPI( "STI_TableGetMinMaxRowIds" ) 
	#define CAL_STI_TableGetMinMaxRowIds  STI_TableGetMinMaxRowIds
	#define CHK_STI_TableGetMinMaxRowIds  TRUE
	#define EXP_STI_TableGetMinMaxRowIds  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TableGetMinMaxRowIds", (RTS_UINTPTR)STI_TableGetMinMaxRowIds, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_TableGetMinMaxRowIds
	#define EXT_CmpCAAStorageSTI_TableGetMinMaxRowIds
	#define GET_CmpCAAStorageSTI_TableGetMinMaxRowIds  ERR_OK
	#define CAL_CmpCAAStorageSTI_TableGetMinMaxRowIds pICmpCAAStorage->ISTI_TableGetMinMaxRowIds
	#define CHK_CmpCAAStorageSTI_TableGetMinMaxRowIds (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_TableGetMinMaxRowIds  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_TableGetMinMaxRowIds
	#define EXT_STI_TableGetMinMaxRowIds
	#define GET_STI_TableGetMinMaxRowIds(fl)  CAL_CMGETAPI( "STI_TableGetMinMaxRowIds" ) 
	#define CAL_STI_TableGetMinMaxRowIds pICmpCAAStorage->ISTI_TableGetMinMaxRowIds
	#define CHK_STI_TableGetMinMaxRowIds (pICmpCAAStorage != NULL)
	#define EXP_STI_TableGetMinMaxRowIds  CAL_CMEXPAPI( "STI_TableGetMinMaxRowIds" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_TableGetMinMaxRowIds  PFSTI_TABLEGETMINMAXROWIDS pfSTI_TableGetMinMaxRowIds;
	#define EXT_STI_TableGetMinMaxRowIds  extern PFSTI_TABLEGETMINMAXROWIDS pfSTI_TableGetMinMaxRowIds;
	#define GET_STI_TableGetMinMaxRowIds(fl)  s_pfCMGetAPI2( "STI_TableGetMinMaxRowIds", (RTS_VOID_FCTPTR *)&pfSTI_TableGetMinMaxRowIds, (fl), 0, 0)
	#define CAL_STI_TableGetMinMaxRowIds  pfSTI_TableGetMinMaxRowIds
	#define CHK_STI_TableGetMinMaxRowIds  (pfSTI_TableGetMinMaxRowIds != NULL)
	#define EXP_STI_TableGetMinMaxRowIds  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TableGetMinMaxRowIds", (RTS_UINTPTR)STI_TableGetMinMaxRowIds, 0, 0) 
#endif



CAA_COUNT CDECL STI_TableGetNumOfColumns(STI_TABLE hTable, STO_ERROR *peError);
typedef CAA_COUNT (CDECL * PFSTI_TABLEGETNUMOFCOLUMNS) (STI_TABLE hTable, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TABLEGETNUMOFCOLUMNS_NOTIMPLEMENTED)
	#define USE_STI_TableGetNumOfColumns
	#define EXT_STI_TableGetNumOfColumns
	#define GET_STI_TableGetNumOfColumns(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_TableGetNumOfColumns(p0,p1)  (CAA_COUNT)ERR_NOTIMPLEMENTED
	#define CHK_STI_TableGetNumOfColumns  FALSE
	#define EXP_STI_TableGetNumOfColumns  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_TableGetNumOfColumns
	#define EXT_STI_TableGetNumOfColumns
	#define GET_STI_TableGetNumOfColumns(fl)  CAL_CMGETAPI( "STI_TableGetNumOfColumns" ) 
	#define CAL_STI_TableGetNumOfColumns  STI_TableGetNumOfColumns
	#define CHK_STI_TableGetNumOfColumns  TRUE
	#define EXP_STI_TableGetNumOfColumns  CAL_CMEXPAPI( "STI_TableGetNumOfColumns" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_TableGetNumOfColumns
	#define EXT_STI_TableGetNumOfColumns
	#define GET_STI_TableGetNumOfColumns(fl)  CAL_CMGETAPI( "STI_TableGetNumOfColumns" ) 
	#define CAL_STI_TableGetNumOfColumns  STI_TableGetNumOfColumns
	#define CHK_STI_TableGetNumOfColumns  TRUE
	#define EXP_STI_TableGetNumOfColumns  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TableGetNumOfColumns", (RTS_UINTPTR)STI_TableGetNumOfColumns, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_TableGetNumOfColumns
	#define EXT_CmpCAAStorageSTI_TableGetNumOfColumns
	#define GET_CmpCAAStorageSTI_TableGetNumOfColumns  ERR_OK
	#define CAL_CmpCAAStorageSTI_TableGetNumOfColumns pICmpCAAStorage->ISTI_TableGetNumOfColumns
	#define CHK_CmpCAAStorageSTI_TableGetNumOfColumns (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_TableGetNumOfColumns  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_TableGetNumOfColumns
	#define EXT_STI_TableGetNumOfColumns
	#define GET_STI_TableGetNumOfColumns(fl)  CAL_CMGETAPI( "STI_TableGetNumOfColumns" ) 
	#define CAL_STI_TableGetNumOfColumns pICmpCAAStorage->ISTI_TableGetNumOfColumns
	#define CHK_STI_TableGetNumOfColumns (pICmpCAAStorage != NULL)
	#define EXP_STI_TableGetNumOfColumns  CAL_CMEXPAPI( "STI_TableGetNumOfColumns" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_TableGetNumOfColumns  PFSTI_TABLEGETNUMOFCOLUMNS pfSTI_TableGetNumOfColumns;
	#define EXT_STI_TableGetNumOfColumns  extern PFSTI_TABLEGETNUMOFCOLUMNS pfSTI_TableGetNumOfColumns;
	#define GET_STI_TableGetNumOfColumns(fl)  s_pfCMGetAPI2( "STI_TableGetNumOfColumns", (RTS_VOID_FCTPTR *)&pfSTI_TableGetNumOfColumns, (fl), 0, 0)
	#define CAL_STI_TableGetNumOfColumns  pfSTI_TableGetNumOfColumns
	#define CHK_STI_TableGetNumOfColumns  (pfSTI_TableGetNumOfColumns != NULL)
	#define EXP_STI_TableGetNumOfColumns  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TableGetNumOfColumns", (RTS_UINTPTR)STI_TableGetNumOfColumns, 0, 0) 
#endif



CAA_COUNT CDECL STI_TableGetNumOfIndexes(STI_TABLE hTable, STO_ERROR *peError);
typedef CAA_COUNT (CDECL * PFSTI_TABLEGETNUMOFINDEXES) (STI_TABLE hTable, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TABLEGETNUMOFINDEXES_NOTIMPLEMENTED)
	#define USE_STI_TableGetNumOfIndexes
	#define EXT_STI_TableGetNumOfIndexes
	#define GET_STI_TableGetNumOfIndexes(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_TableGetNumOfIndexes(p0,p1)  (CAA_COUNT)ERR_NOTIMPLEMENTED
	#define CHK_STI_TableGetNumOfIndexes  FALSE
	#define EXP_STI_TableGetNumOfIndexes  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_TableGetNumOfIndexes
	#define EXT_STI_TableGetNumOfIndexes
	#define GET_STI_TableGetNumOfIndexes(fl)  CAL_CMGETAPI( "STI_TableGetNumOfIndexes" ) 
	#define CAL_STI_TableGetNumOfIndexes  STI_TableGetNumOfIndexes
	#define CHK_STI_TableGetNumOfIndexes  TRUE
	#define EXP_STI_TableGetNumOfIndexes  CAL_CMEXPAPI( "STI_TableGetNumOfIndexes" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_TableGetNumOfIndexes
	#define EXT_STI_TableGetNumOfIndexes
	#define GET_STI_TableGetNumOfIndexes(fl)  CAL_CMGETAPI( "STI_TableGetNumOfIndexes" ) 
	#define CAL_STI_TableGetNumOfIndexes  STI_TableGetNumOfIndexes
	#define CHK_STI_TableGetNumOfIndexes  TRUE
	#define EXP_STI_TableGetNumOfIndexes  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TableGetNumOfIndexes", (RTS_UINTPTR)STI_TableGetNumOfIndexes, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_TableGetNumOfIndexes
	#define EXT_CmpCAAStorageSTI_TableGetNumOfIndexes
	#define GET_CmpCAAStorageSTI_TableGetNumOfIndexes  ERR_OK
	#define CAL_CmpCAAStorageSTI_TableGetNumOfIndexes pICmpCAAStorage->ISTI_TableGetNumOfIndexes
	#define CHK_CmpCAAStorageSTI_TableGetNumOfIndexes (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_TableGetNumOfIndexes  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_TableGetNumOfIndexes
	#define EXT_STI_TableGetNumOfIndexes
	#define GET_STI_TableGetNumOfIndexes(fl)  CAL_CMGETAPI( "STI_TableGetNumOfIndexes" ) 
	#define CAL_STI_TableGetNumOfIndexes pICmpCAAStorage->ISTI_TableGetNumOfIndexes
	#define CHK_STI_TableGetNumOfIndexes (pICmpCAAStorage != NULL)
	#define EXP_STI_TableGetNumOfIndexes  CAL_CMEXPAPI( "STI_TableGetNumOfIndexes" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_TableGetNumOfIndexes  PFSTI_TABLEGETNUMOFINDEXES pfSTI_TableGetNumOfIndexes;
	#define EXT_STI_TableGetNumOfIndexes  extern PFSTI_TABLEGETNUMOFINDEXES pfSTI_TableGetNumOfIndexes;
	#define GET_STI_TableGetNumOfIndexes(fl)  s_pfCMGetAPI2( "STI_TableGetNumOfIndexes", (RTS_VOID_FCTPTR *)&pfSTI_TableGetNumOfIndexes, (fl), 0, 0)
	#define CAL_STI_TableGetNumOfIndexes  pfSTI_TableGetNumOfIndexes
	#define CHK_STI_TableGetNumOfIndexes  (pfSTI_TableGetNumOfIndexes != NULL)
	#define EXP_STI_TableGetNumOfIndexes  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TableGetNumOfIndexes", (RTS_UINTPTR)STI_TableGetNumOfIndexes, 0, 0) 
#endif



CAA_COUNT CDECL STI_TableGetNumOfRows(STI_TABLE hTable, STO_ERROR *peError);
typedef CAA_COUNT (CDECL * PFSTI_TABLEGETNUMOFROWS) (STI_TABLE hTable, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TABLEGETNUMOFROWS_NOTIMPLEMENTED)
	#define USE_STI_TableGetNumOfRows
	#define EXT_STI_TableGetNumOfRows
	#define GET_STI_TableGetNumOfRows(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_TableGetNumOfRows(p0,p1)  (CAA_COUNT)ERR_NOTIMPLEMENTED
	#define CHK_STI_TableGetNumOfRows  FALSE
	#define EXP_STI_TableGetNumOfRows  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_TableGetNumOfRows
	#define EXT_STI_TableGetNumOfRows
	#define GET_STI_TableGetNumOfRows(fl)  CAL_CMGETAPI( "STI_TableGetNumOfRows" ) 
	#define CAL_STI_TableGetNumOfRows  STI_TableGetNumOfRows
	#define CHK_STI_TableGetNumOfRows  TRUE
	#define EXP_STI_TableGetNumOfRows  CAL_CMEXPAPI( "STI_TableGetNumOfRows" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_TableGetNumOfRows
	#define EXT_STI_TableGetNumOfRows
	#define GET_STI_TableGetNumOfRows(fl)  CAL_CMGETAPI( "STI_TableGetNumOfRows" ) 
	#define CAL_STI_TableGetNumOfRows  STI_TableGetNumOfRows
	#define CHK_STI_TableGetNumOfRows  TRUE
	#define EXP_STI_TableGetNumOfRows  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TableGetNumOfRows", (RTS_UINTPTR)STI_TableGetNumOfRows, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_TableGetNumOfRows
	#define EXT_CmpCAAStorageSTI_TableGetNumOfRows
	#define GET_CmpCAAStorageSTI_TableGetNumOfRows  ERR_OK
	#define CAL_CmpCAAStorageSTI_TableGetNumOfRows pICmpCAAStorage->ISTI_TableGetNumOfRows
	#define CHK_CmpCAAStorageSTI_TableGetNumOfRows (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_TableGetNumOfRows  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_TableGetNumOfRows
	#define EXT_STI_TableGetNumOfRows
	#define GET_STI_TableGetNumOfRows(fl)  CAL_CMGETAPI( "STI_TableGetNumOfRows" ) 
	#define CAL_STI_TableGetNumOfRows pICmpCAAStorage->ISTI_TableGetNumOfRows
	#define CHK_STI_TableGetNumOfRows (pICmpCAAStorage != NULL)
	#define EXP_STI_TableGetNumOfRows  CAL_CMEXPAPI( "STI_TableGetNumOfRows" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_TableGetNumOfRows  PFSTI_TABLEGETNUMOFROWS pfSTI_TableGetNumOfRows;
	#define EXT_STI_TableGetNumOfRows  extern PFSTI_TABLEGETNUMOFROWS pfSTI_TableGetNumOfRows;
	#define GET_STI_TableGetNumOfRows(fl)  s_pfCMGetAPI2( "STI_TableGetNumOfRows", (RTS_VOID_FCTPTR *)&pfSTI_TableGetNumOfRows, (fl), 0, 0)
	#define CAL_STI_TableGetNumOfRows  pfSTI_TableGetNumOfRows
	#define CHK_STI_TableGetNumOfRows  (pfSTI_TableGetNumOfRows != NULL)
	#define EXP_STI_TableGetNumOfRows  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TableGetNumOfRows", (RTS_UINTPTR)STI_TableGetNumOfRows, 0, 0) 
#endif



STI_STORAGE CDECL STI_TableGetStorage(STI_TABLE hTable, STO_ERROR *peError);
typedef STI_STORAGE (CDECL * PFSTI_TABLEGETSTORAGE) (STI_TABLE hTable, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TABLEGETSTORAGE_NOTIMPLEMENTED)
	#define USE_STI_TableGetStorage
	#define EXT_STI_TableGetStorage
	#define GET_STI_TableGetStorage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_TableGetStorage(p0,p1)  (STI_STORAGE)ERR_NOTIMPLEMENTED
	#define CHK_STI_TableGetStorage  FALSE
	#define EXP_STI_TableGetStorage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_TableGetStorage
	#define EXT_STI_TableGetStorage
	#define GET_STI_TableGetStorage(fl)  CAL_CMGETAPI( "STI_TableGetStorage" ) 
	#define CAL_STI_TableGetStorage  STI_TableGetStorage
	#define CHK_STI_TableGetStorage  TRUE
	#define EXP_STI_TableGetStorage  CAL_CMEXPAPI( "STI_TableGetStorage" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_TableGetStorage
	#define EXT_STI_TableGetStorage
	#define GET_STI_TableGetStorage(fl)  CAL_CMGETAPI( "STI_TableGetStorage" ) 
	#define CAL_STI_TableGetStorage  STI_TableGetStorage
	#define CHK_STI_TableGetStorage  TRUE
	#define EXP_STI_TableGetStorage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TableGetStorage", (RTS_UINTPTR)STI_TableGetStorage, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_TableGetStorage
	#define EXT_CmpCAAStorageSTI_TableGetStorage
	#define GET_CmpCAAStorageSTI_TableGetStorage  ERR_OK
	#define CAL_CmpCAAStorageSTI_TableGetStorage pICmpCAAStorage->ISTI_TableGetStorage
	#define CHK_CmpCAAStorageSTI_TableGetStorage (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_TableGetStorage  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_TableGetStorage
	#define EXT_STI_TableGetStorage
	#define GET_STI_TableGetStorage(fl)  CAL_CMGETAPI( "STI_TableGetStorage" ) 
	#define CAL_STI_TableGetStorage pICmpCAAStorage->ISTI_TableGetStorage
	#define CHK_STI_TableGetStorage (pICmpCAAStorage != NULL)
	#define EXP_STI_TableGetStorage  CAL_CMEXPAPI( "STI_TableGetStorage" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_TableGetStorage  PFSTI_TABLEGETSTORAGE pfSTI_TableGetStorage;
	#define EXT_STI_TableGetStorage  extern PFSTI_TABLEGETSTORAGE pfSTI_TableGetStorage;
	#define GET_STI_TableGetStorage(fl)  s_pfCMGetAPI2( "STI_TableGetStorage", (RTS_VOID_FCTPTR *)&pfSTI_TableGetStorage, (fl), 0, 0)
	#define CAL_STI_TableGetStorage  pfSTI_TableGetStorage
	#define CHK_STI_TableGetStorage  (pfSTI_TableGetStorage != NULL)
	#define EXP_STI_TableGetStorage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TableGetStorage", (RTS_UINTPTR)STI_TableGetStorage, 0, 0) 
#endif



STI_TABLE CDECL STI_TableOpen(STI_STORAGE hStorage, CAA_IDENT idTable, STO_ERROR *peError);
typedef STI_TABLE (CDECL * PFSTI_TABLEOPEN) (STI_STORAGE hStorage, CAA_IDENT idTable, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TABLEOPEN_NOTIMPLEMENTED)
	#define USE_STI_TableOpen
	#define EXT_STI_TableOpen
	#define GET_STI_TableOpen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_TableOpen(p0,p1,p2)  (STI_TABLE)ERR_NOTIMPLEMENTED
	#define CHK_STI_TableOpen  FALSE
	#define EXP_STI_TableOpen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_TableOpen
	#define EXT_STI_TableOpen
	#define GET_STI_TableOpen(fl)  CAL_CMGETAPI( "STI_TableOpen" ) 
	#define CAL_STI_TableOpen  STI_TableOpen
	#define CHK_STI_TableOpen  TRUE
	#define EXP_STI_TableOpen  CAL_CMEXPAPI( "STI_TableOpen" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_TableOpen
	#define EXT_STI_TableOpen
	#define GET_STI_TableOpen(fl)  CAL_CMGETAPI( "STI_TableOpen" ) 
	#define CAL_STI_TableOpen  STI_TableOpen
	#define CHK_STI_TableOpen  TRUE
	#define EXP_STI_TableOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TableOpen", (RTS_UINTPTR)STI_TableOpen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_TableOpen
	#define EXT_CmpCAAStorageSTI_TableOpen
	#define GET_CmpCAAStorageSTI_TableOpen  ERR_OK
	#define CAL_CmpCAAStorageSTI_TableOpen pICmpCAAStorage->ISTI_TableOpen
	#define CHK_CmpCAAStorageSTI_TableOpen (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_TableOpen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_TableOpen
	#define EXT_STI_TableOpen
	#define GET_STI_TableOpen(fl)  CAL_CMGETAPI( "STI_TableOpen" ) 
	#define CAL_STI_TableOpen pICmpCAAStorage->ISTI_TableOpen
	#define CHK_STI_TableOpen (pICmpCAAStorage != NULL)
	#define EXP_STI_TableOpen  CAL_CMEXPAPI( "STI_TableOpen" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_TableOpen  PFSTI_TABLEOPEN pfSTI_TableOpen;
	#define EXT_STI_TableOpen  extern PFSTI_TABLEOPEN pfSTI_TableOpen;
	#define GET_STI_TableOpen(fl)  s_pfCMGetAPI2( "STI_TableOpen", (RTS_VOID_FCTPTR *)&pfSTI_TableOpen, (fl), 0, 0)
	#define CAL_STI_TableOpen  pfSTI_TableOpen
	#define CHK_STI_TableOpen  (pfSTI_TableOpen != NULL)
	#define EXP_STI_TableOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TableOpen", (RTS_UINTPTR)STI_TableOpen, 0, 0) 
#endif



STI_TRANSACTION CDECL STI_TransactionBegin(STI_STORAGE hStorage, STO_TRANSACTION_MODE eMode, STO_ERROR *peError);
typedef STI_TRANSACTION (CDECL * PFSTI_TRANSACTIONBEGIN) (STI_STORAGE hStorage, STO_TRANSACTION_MODE eMode, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TRANSACTIONBEGIN_NOTIMPLEMENTED)
	#define USE_STI_TransactionBegin
	#define EXT_STI_TransactionBegin
	#define GET_STI_TransactionBegin(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_TransactionBegin(p0,p1,p2)  (STI_TRANSACTION)ERR_NOTIMPLEMENTED
	#define CHK_STI_TransactionBegin  FALSE
	#define EXP_STI_TransactionBegin  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_TransactionBegin
	#define EXT_STI_TransactionBegin
	#define GET_STI_TransactionBegin(fl)  CAL_CMGETAPI( "STI_TransactionBegin" ) 
	#define CAL_STI_TransactionBegin  STI_TransactionBegin
	#define CHK_STI_TransactionBegin  TRUE
	#define EXP_STI_TransactionBegin  CAL_CMEXPAPI( "STI_TransactionBegin" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_TransactionBegin
	#define EXT_STI_TransactionBegin
	#define GET_STI_TransactionBegin(fl)  CAL_CMGETAPI( "STI_TransactionBegin" ) 
	#define CAL_STI_TransactionBegin  STI_TransactionBegin
	#define CHK_STI_TransactionBegin  TRUE
	#define EXP_STI_TransactionBegin  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TransactionBegin", (RTS_UINTPTR)STI_TransactionBegin, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_TransactionBegin
	#define EXT_CmpCAAStorageSTI_TransactionBegin
	#define GET_CmpCAAStorageSTI_TransactionBegin  ERR_OK
	#define CAL_CmpCAAStorageSTI_TransactionBegin pICmpCAAStorage->ISTI_TransactionBegin
	#define CHK_CmpCAAStorageSTI_TransactionBegin (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_TransactionBegin  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_TransactionBegin
	#define EXT_STI_TransactionBegin
	#define GET_STI_TransactionBegin(fl)  CAL_CMGETAPI( "STI_TransactionBegin" ) 
	#define CAL_STI_TransactionBegin pICmpCAAStorage->ISTI_TransactionBegin
	#define CHK_STI_TransactionBegin (pICmpCAAStorage != NULL)
	#define EXP_STI_TransactionBegin  CAL_CMEXPAPI( "STI_TransactionBegin" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_TransactionBegin  PFSTI_TRANSACTIONBEGIN pfSTI_TransactionBegin;
	#define EXT_STI_TransactionBegin  extern PFSTI_TRANSACTIONBEGIN pfSTI_TransactionBegin;
	#define GET_STI_TransactionBegin(fl)  s_pfCMGetAPI2( "STI_TransactionBegin", (RTS_VOID_FCTPTR *)&pfSTI_TransactionBegin, (fl), 0, 0)
	#define CAL_STI_TransactionBegin  pfSTI_TransactionBegin
	#define CHK_STI_TransactionBegin  (pfSTI_TransactionBegin != NULL)
	#define EXP_STI_TransactionBegin  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TransactionBegin", (RTS_UINTPTR)STI_TransactionBegin, 0, 0) 
#endif



STO_ERROR CDECL STI_TransactionCommit(STI_TRANSACTION hTransaction);
typedef STO_ERROR (CDECL * PFSTI_TRANSACTIONCOMMIT) (STI_TRANSACTION hTransaction);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TRANSACTIONCOMMIT_NOTIMPLEMENTED)
	#define USE_STI_TransactionCommit
	#define EXT_STI_TransactionCommit
	#define GET_STI_TransactionCommit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_TransactionCommit(p0)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_TransactionCommit  FALSE
	#define EXP_STI_TransactionCommit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_TransactionCommit
	#define EXT_STI_TransactionCommit
	#define GET_STI_TransactionCommit(fl)  CAL_CMGETAPI( "STI_TransactionCommit" ) 
	#define CAL_STI_TransactionCommit  STI_TransactionCommit
	#define CHK_STI_TransactionCommit  TRUE
	#define EXP_STI_TransactionCommit  CAL_CMEXPAPI( "STI_TransactionCommit" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_TransactionCommit
	#define EXT_STI_TransactionCommit
	#define GET_STI_TransactionCommit(fl)  CAL_CMGETAPI( "STI_TransactionCommit" ) 
	#define CAL_STI_TransactionCommit  STI_TransactionCommit
	#define CHK_STI_TransactionCommit  TRUE
	#define EXP_STI_TransactionCommit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TransactionCommit", (RTS_UINTPTR)STI_TransactionCommit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_TransactionCommit
	#define EXT_CmpCAAStorageSTI_TransactionCommit
	#define GET_CmpCAAStorageSTI_TransactionCommit  ERR_OK
	#define CAL_CmpCAAStorageSTI_TransactionCommit pICmpCAAStorage->ISTI_TransactionCommit
	#define CHK_CmpCAAStorageSTI_TransactionCommit (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_TransactionCommit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_TransactionCommit
	#define EXT_STI_TransactionCommit
	#define GET_STI_TransactionCommit(fl)  CAL_CMGETAPI( "STI_TransactionCommit" ) 
	#define CAL_STI_TransactionCommit pICmpCAAStorage->ISTI_TransactionCommit
	#define CHK_STI_TransactionCommit (pICmpCAAStorage != NULL)
	#define EXP_STI_TransactionCommit  CAL_CMEXPAPI( "STI_TransactionCommit" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_TransactionCommit  PFSTI_TRANSACTIONCOMMIT pfSTI_TransactionCommit;
	#define EXT_STI_TransactionCommit  extern PFSTI_TRANSACTIONCOMMIT pfSTI_TransactionCommit;
	#define GET_STI_TransactionCommit(fl)  s_pfCMGetAPI2( "STI_TransactionCommit", (RTS_VOID_FCTPTR *)&pfSTI_TransactionCommit, (fl), 0, 0)
	#define CAL_STI_TransactionCommit  pfSTI_TransactionCommit
	#define CHK_STI_TransactionCommit  (pfSTI_TransactionCommit != NULL)
	#define EXP_STI_TransactionCommit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TransactionCommit", (RTS_UINTPTR)STI_TransactionCommit, 0, 0) 
#endif



STI_STORAGE CDECL STI_TransactionGetStorage(STI_TRANSACTION hTransaction, STO_ERROR *peError);
typedef STI_STORAGE (CDECL * PFSTI_TRANSACTIONGETSTORAGE) (STI_TRANSACTION hTransaction, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TRANSACTIONGETSTORAGE_NOTIMPLEMENTED)
	#define USE_STI_TransactionGetStorage
	#define EXT_STI_TransactionGetStorage
	#define GET_STI_TransactionGetStorage(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_TransactionGetStorage(p0,p1)  (STI_STORAGE)ERR_NOTIMPLEMENTED
	#define CHK_STI_TransactionGetStorage  FALSE
	#define EXP_STI_TransactionGetStorage  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_TransactionGetStorage
	#define EXT_STI_TransactionGetStorage
	#define GET_STI_TransactionGetStorage(fl)  CAL_CMGETAPI( "STI_TransactionGetStorage" ) 
	#define CAL_STI_TransactionGetStorage  STI_TransactionGetStorage
	#define CHK_STI_TransactionGetStorage  TRUE
	#define EXP_STI_TransactionGetStorage  CAL_CMEXPAPI( "STI_TransactionGetStorage" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_TransactionGetStorage
	#define EXT_STI_TransactionGetStorage
	#define GET_STI_TransactionGetStorage(fl)  CAL_CMGETAPI( "STI_TransactionGetStorage" ) 
	#define CAL_STI_TransactionGetStorage  STI_TransactionGetStorage
	#define CHK_STI_TransactionGetStorage  TRUE
	#define EXP_STI_TransactionGetStorage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TransactionGetStorage", (RTS_UINTPTR)STI_TransactionGetStorage, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_TransactionGetStorage
	#define EXT_CmpCAAStorageSTI_TransactionGetStorage
	#define GET_CmpCAAStorageSTI_TransactionGetStorage  ERR_OK
	#define CAL_CmpCAAStorageSTI_TransactionGetStorage pICmpCAAStorage->ISTI_TransactionGetStorage
	#define CHK_CmpCAAStorageSTI_TransactionGetStorage (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_TransactionGetStorage  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_TransactionGetStorage
	#define EXT_STI_TransactionGetStorage
	#define GET_STI_TransactionGetStorage(fl)  CAL_CMGETAPI( "STI_TransactionGetStorage" ) 
	#define CAL_STI_TransactionGetStorage pICmpCAAStorage->ISTI_TransactionGetStorage
	#define CHK_STI_TransactionGetStorage (pICmpCAAStorage != NULL)
	#define EXP_STI_TransactionGetStorage  CAL_CMEXPAPI( "STI_TransactionGetStorage" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_TransactionGetStorage  PFSTI_TRANSACTIONGETSTORAGE pfSTI_TransactionGetStorage;
	#define EXT_STI_TransactionGetStorage  extern PFSTI_TRANSACTIONGETSTORAGE pfSTI_TransactionGetStorage;
	#define GET_STI_TransactionGetStorage(fl)  s_pfCMGetAPI2( "STI_TransactionGetStorage", (RTS_VOID_FCTPTR *)&pfSTI_TransactionGetStorage, (fl), 0, 0)
	#define CAL_STI_TransactionGetStorage  pfSTI_TransactionGetStorage
	#define CHK_STI_TransactionGetStorage  (pfSTI_TransactionGetStorage != NULL)
	#define EXP_STI_TransactionGetStorage  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TransactionGetStorage", (RTS_UINTPTR)STI_TransactionGetStorage, 0, 0) 
#endif



STO_ERROR CDECL STI_TransactionRollback(STI_TRANSACTION hTransaction);
typedef STO_ERROR (CDECL * PFSTI_TRANSACTIONROLLBACK) (STI_TRANSACTION hTransaction);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TRANSACTIONROLLBACK_NOTIMPLEMENTED)
	#define USE_STI_TransactionRollback
	#define EXT_STI_TransactionRollback
	#define GET_STI_TransactionRollback(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_TransactionRollback(p0)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_TransactionRollback  FALSE
	#define EXP_STI_TransactionRollback  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_TransactionRollback
	#define EXT_STI_TransactionRollback
	#define GET_STI_TransactionRollback(fl)  CAL_CMGETAPI( "STI_TransactionRollback" ) 
	#define CAL_STI_TransactionRollback  STI_TransactionRollback
	#define CHK_STI_TransactionRollback  TRUE
	#define EXP_STI_TransactionRollback  CAL_CMEXPAPI( "STI_TransactionRollback" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_TransactionRollback
	#define EXT_STI_TransactionRollback
	#define GET_STI_TransactionRollback(fl)  CAL_CMGETAPI( "STI_TransactionRollback" ) 
	#define CAL_STI_TransactionRollback  STI_TransactionRollback
	#define CHK_STI_TransactionRollback  TRUE
	#define EXP_STI_TransactionRollback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TransactionRollback", (RTS_UINTPTR)STI_TransactionRollback, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_TransactionRollback
	#define EXT_CmpCAAStorageSTI_TransactionRollback
	#define GET_CmpCAAStorageSTI_TransactionRollback  ERR_OK
	#define CAL_CmpCAAStorageSTI_TransactionRollback pICmpCAAStorage->ISTI_TransactionRollback
	#define CHK_CmpCAAStorageSTI_TransactionRollback (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_TransactionRollback  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_TransactionRollback
	#define EXT_STI_TransactionRollback
	#define GET_STI_TransactionRollback(fl)  CAL_CMGETAPI( "STI_TransactionRollback" ) 
	#define CAL_STI_TransactionRollback pICmpCAAStorage->ISTI_TransactionRollback
	#define CHK_STI_TransactionRollback (pICmpCAAStorage != NULL)
	#define EXP_STI_TransactionRollback  CAL_CMEXPAPI( "STI_TransactionRollback" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_TransactionRollback  PFSTI_TRANSACTIONROLLBACK pfSTI_TransactionRollback;
	#define EXT_STI_TransactionRollback  extern PFSTI_TRANSACTIONROLLBACK pfSTI_TransactionRollback;
	#define GET_STI_TransactionRollback(fl)  s_pfCMGetAPI2( "STI_TransactionRollback", (RTS_VOID_FCTPTR *)&pfSTI_TransactionRollback, (fl), 0, 0)
	#define CAL_STI_TransactionRollback  pfSTI_TransactionRollback
	#define CHK_STI_TransactionRollback  (pfSTI_TransactionRollback != NULL)
	#define EXP_STI_TransactionRollback  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TransactionRollback", (RTS_UINTPTR)STI_TransactionRollback, 0, 0) 
#endif



STI_SAVEPOINT CDECL STI_TransactionSetSavepoint(STI_TRANSACTION hTransaction, STO_ERROR *peError);
typedef STI_SAVEPOINT (CDECL * PFSTI_TRANSACTIONSETSAVEPOINT) (STI_TRANSACTION hTransaction, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_TRANSACTIONSETSAVEPOINT_NOTIMPLEMENTED)
	#define USE_STI_TransactionSetSavepoint
	#define EXT_STI_TransactionSetSavepoint
	#define GET_STI_TransactionSetSavepoint(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_TransactionSetSavepoint(p0,p1)  (STI_SAVEPOINT)ERR_NOTIMPLEMENTED
	#define CHK_STI_TransactionSetSavepoint  FALSE
	#define EXP_STI_TransactionSetSavepoint  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_TransactionSetSavepoint
	#define EXT_STI_TransactionSetSavepoint
	#define GET_STI_TransactionSetSavepoint(fl)  CAL_CMGETAPI( "STI_TransactionSetSavepoint" ) 
	#define CAL_STI_TransactionSetSavepoint  STI_TransactionSetSavepoint
	#define CHK_STI_TransactionSetSavepoint  TRUE
	#define EXP_STI_TransactionSetSavepoint  CAL_CMEXPAPI( "STI_TransactionSetSavepoint" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_TransactionSetSavepoint
	#define EXT_STI_TransactionSetSavepoint
	#define GET_STI_TransactionSetSavepoint(fl)  CAL_CMGETAPI( "STI_TransactionSetSavepoint" ) 
	#define CAL_STI_TransactionSetSavepoint  STI_TransactionSetSavepoint
	#define CHK_STI_TransactionSetSavepoint  TRUE
	#define EXP_STI_TransactionSetSavepoint  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TransactionSetSavepoint", (RTS_UINTPTR)STI_TransactionSetSavepoint, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_TransactionSetSavepoint
	#define EXT_CmpCAAStorageSTI_TransactionSetSavepoint
	#define GET_CmpCAAStorageSTI_TransactionSetSavepoint  ERR_OK
	#define CAL_CmpCAAStorageSTI_TransactionSetSavepoint pICmpCAAStorage->ISTI_TransactionSetSavepoint
	#define CHK_CmpCAAStorageSTI_TransactionSetSavepoint (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_TransactionSetSavepoint  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_TransactionSetSavepoint
	#define EXT_STI_TransactionSetSavepoint
	#define GET_STI_TransactionSetSavepoint(fl)  CAL_CMGETAPI( "STI_TransactionSetSavepoint" ) 
	#define CAL_STI_TransactionSetSavepoint pICmpCAAStorage->ISTI_TransactionSetSavepoint
	#define CHK_STI_TransactionSetSavepoint (pICmpCAAStorage != NULL)
	#define EXP_STI_TransactionSetSavepoint  CAL_CMEXPAPI( "STI_TransactionSetSavepoint" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_TransactionSetSavepoint  PFSTI_TRANSACTIONSETSAVEPOINT pfSTI_TransactionSetSavepoint;
	#define EXT_STI_TransactionSetSavepoint  extern PFSTI_TRANSACTIONSETSAVEPOINT pfSTI_TransactionSetSavepoint;
	#define GET_STI_TransactionSetSavepoint(fl)  s_pfCMGetAPI2( "STI_TransactionSetSavepoint", (RTS_VOID_FCTPTR *)&pfSTI_TransactionSetSavepoint, (fl), 0, 0)
	#define CAL_STI_TransactionSetSavepoint  pfSTI_TransactionSetSavepoint
	#define CHK_STI_TransactionSetSavepoint  (pfSTI_TransactionSetSavepoint != NULL)
	#define EXP_STI_TransactionSetSavepoint  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_TransactionSetSavepoint", (RTS_UINTPTR)STI_TransactionSetSavepoint, 0, 0) 
#endif




STO_INT64 CDECL STI_UtilityGetCurrentDateAndTime(STI_STORAGE hStorage, STO_ERROR *peError);
typedef STO_INT64 (CDECL * PFSTI_UTILITYGETCURRENTDATEANDTIME) (STI_STORAGE hStorage, STO_ERROR *peError);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_UTILITYGETCURRENTDATEANDTIME_NOTIMPLEMENTED)
	#define USE_STI_UtilityGetCurrentDateAndTime
	#define EXT_STI_UtilityGetCurrentDateAndTime
	#define GET_STI_UtilityGetCurrentDateAndTime(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_UtilityGetCurrentDateAndTime(p0,p1)  (STO_INT64)ERR_NOTIMPLEMENTED
	#define CHK_STI_UtilityGetCurrentDateAndTime  FALSE
	#define EXP_STI_UtilityGetCurrentDateAndTime  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_UtilityGetCurrentDateAndTime
	#define EXT_STI_UtilityGetCurrentDateAndTime
	#define GET_STI_UtilityGetCurrentDateAndTime(fl)  CAL_CMGETAPI( "STI_UtilityGetCurrentDateAndTime" ) 
	#define CAL_STI_UtilityGetCurrentDateAndTime  STI_UtilityGetCurrentDateAndTime
	#define CHK_STI_UtilityGetCurrentDateAndTime  TRUE
	#define EXP_STI_UtilityGetCurrentDateAndTime  CAL_CMEXPAPI( "STI_UtilityGetCurrentDateAndTime" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_UtilityGetCurrentDateAndTime
	#define EXT_STI_UtilityGetCurrentDateAndTime
	#define GET_STI_UtilityGetCurrentDateAndTime(fl)  CAL_CMGETAPI( "STI_UtilityGetCurrentDateAndTime" ) 
	#define CAL_STI_UtilityGetCurrentDateAndTime  STI_UtilityGetCurrentDateAndTime
	#define CHK_STI_UtilityGetCurrentDateAndTime  TRUE
	#define EXP_STI_UtilityGetCurrentDateAndTime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_UtilityGetCurrentDateAndTime", (RTS_UINTPTR)STI_UtilityGetCurrentDateAndTime, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_UtilityGetCurrentDateAndTime
	#define EXT_CmpCAAStorageSTI_UtilityGetCurrentDateAndTime
	#define GET_CmpCAAStorageSTI_UtilityGetCurrentDateAndTime  ERR_OK
	#define CAL_CmpCAAStorageSTI_UtilityGetCurrentDateAndTime pICmpCAAStorage->ISTI_UtilityGetCurrentDateAndTime
	#define CHK_CmpCAAStorageSTI_UtilityGetCurrentDateAndTime (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_UtilityGetCurrentDateAndTime  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_UtilityGetCurrentDateAndTime
	#define EXT_STI_UtilityGetCurrentDateAndTime
	#define GET_STI_UtilityGetCurrentDateAndTime(fl)  CAL_CMGETAPI( "STI_UtilityGetCurrentDateAndTime" ) 
	#define CAL_STI_UtilityGetCurrentDateAndTime pICmpCAAStorage->ISTI_UtilityGetCurrentDateAndTime
	#define CHK_STI_UtilityGetCurrentDateAndTime (pICmpCAAStorage != NULL)
	#define EXP_STI_UtilityGetCurrentDateAndTime  CAL_CMEXPAPI( "STI_UtilityGetCurrentDateAndTime" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_UtilityGetCurrentDateAndTime  PFSTI_UTILITYGETCURRENTDATEANDTIME pfSTI_UtilityGetCurrentDateAndTime;
	#define EXT_STI_UtilityGetCurrentDateAndTime  extern PFSTI_UTILITYGETCURRENTDATEANDTIME pfSTI_UtilityGetCurrentDateAndTime;
	#define GET_STI_UtilityGetCurrentDateAndTime(fl)  s_pfCMGetAPI2( "STI_UtilityGetCurrentDateAndTime", (RTS_VOID_FCTPTR *)&pfSTI_UtilityGetCurrentDateAndTime, (fl), 0, 0)
	#define CAL_STI_UtilityGetCurrentDateAndTime  pfSTI_UtilityGetCurrentDateAndTime
	#define CHK_STI_UtilityGetCurrentDateAndTime  (pfSTI_UtilityGetCurrentDateAndTime != NULL)
	#define EXP_STI_UtilityGetCurrentDateAndTime  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_UtilityGetCurrentDateAndTime", (RTS_UINTPTR)STI_UtilityGetCurrentDateAndTime, 0, 0) 
#endif



STO_ERROR CDECL STI_UtilityRandomness(STI_STORAGE hStorage, CAA_SIZE szSize, CAA_PVOID pData);
typedef STO_ERROR (CDECL * PFSTI_UTILITYRANDOMNESS) (STI_STORAGE hStorage, CAA_SIZE szSize, CAA_PVOID pData);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_UTILITYRANDOMNESS_NOTIMPLEMENTED)
	#define USE_STI_UtilityRandomness
	#define EXT_STI_UtilityRandomness
	#define GET_STI_UtilityRandomness(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_UtilityRandomness(p0,p1,p2)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_UtilityRandomness  FALSE
	#define EXP_STI_UtilityRandomness  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_UtilityRandomness
	#define EXT_STI_UtilityRandomness
	#define GET_STI_UtilityRandomness(fl)  CAL_CMGETAPI( "STI_UtilityRandomness" ) 
	#define CAL_STI_UtilityRandomness  STI_UtilityRandomness
	#define CHK_STI_UtilityRandomness  TRUE
	#define EXP_STI_UtilityRandomness  CAL_CMEXPAPI( "STI_UtilityRandomness" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_UtilityRandomness
	#define EXT_STI_UtilityRandomness
	#define GET_STI_UtilityRandomness(fl)  CAL_CMGETAPI( "STI_UtilityRandomness" ) 
	#define CAL_STI_UtilityRandomness  STI_UtilityRandomness
	#define CHK_STI_UtilityRandomness  TRUE
	#define EXP_STI_UtilityRandomness  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_UtilityRandomness", (RTS_UINTPTR)STI_UtilityRandomness, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_UtilityRandomness
	#define EXT_CmpCAAStorageSTI_UtilityRandomness
	#define GET_CmpCAAStorageSTI_UtilityRandomness  ERR_OK
	#define CAL_CmpCAAStorageSTI_UtilityRandomness pICmpCAAStorage->ISTI_UtilityRandomness
	#define CHK_CmpCAAStorageSTI_UtilityRandomness (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_UtilityRandomness  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_UtilityRandomness
	#define EXT_STI_UtilityRandomness
	#define GET_STI_UtilityRandomness(fl)  CAL_CMGETAPI( "STI_UtilityRandomness" ) 
	#define CAL_STI_UtilityRandomness pICmpCAAStorage->ISTI_UtilityRandomness
	#define CHK_STI_UtilityRandomness (pICmpCAAStorage != NULL)
	#define EXP_STI_UtilityRandomness  CAL_CMEXPAPI( "STI_UtilityRandomness" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_UtilityRandomness  PFSTI_UTILITYRANDOMNESS pfSTI_UtilityRandomness;
	#define EXT_STI_UtilityRandomness  extern PFSTI_UTILITYRANDOMNESS pfSTI_UtilityRandomness;
	#define GET_STI_UtilityRandomness(fl)  s_pfCMGetAPI2( "STI_UtilityRandomness", (RTS_VOID_FCTPTR *)&pfSTI_UtilityRandomness, (fl), 0, 0)
	#define CAL_STI_UtilityRandomness  pfSTI_UtilityRandomness
	#define CHK_STI_UtilityRandomness  (pfSTI_UtilityRandomness != NULL)
	#define EXP_STI_UtilityRandomness  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_UtilityRandomness", (RTS_UINTPTR)STI_UtilityRandomness, 0, 0) 
#endif



STO_ERROR CDECL STI_DeleteFile(CAA_FILENAME sPath);
typedef STO_ERROR (CDECL * PFSTI_DELETEFILE) (CAA_FILENAME sPath);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_DELETEFILE_NOTIMPLEMENTED)
	#define USE_STI_DeleteFile
	#define EXT_STI_DeleteFile
	#define GET_STI_DeleteFile(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_DeleteFile(p0)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_DeleteFile  FALSE
	#define EXP_STI_DeleteFile  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_DeleteFile
	#define EXT_STI_DeleteFile
	#define GET_STI_DeleteFile(fl)  CAL_CMGETAPI( "STI_DeleteFile" ) 
	#define CAL_STI_DeleteFile  STI_DeleteFile
	#define CHK_STI_DeleteFile  TRUE
	#define EXP_STI_DeleteFile  CAL_CMEXPAPI( "STI_DeleteFile" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_DeleteFile
	#define EXT_STI_DeleteFile
	#define GET_STI_DeleteFile(fl)  CAL_CMGETAPI( "STI_DeleteFile" ) 
	#define CAL_STI_DeleteFile  STI_DeleteFile
	#define CHK_STI_DeleteFile  TRUE
	#define EXP_STI_DeleteFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_DeleteFile", (RTS_UINTPTR)STI_DeleteFile, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_DeleteFile
	#define EXT_CmpCAAStorageSTI_DeleteFile
	#define GET_CmpCAAStorageSTI_DeleteFile  ERR_OK
	#define CAL_CmpCAAStorageSTI_DeleteFile pICmpCAAStorage->ISTI_DeleteFile
	#define CHK_CmpCAAStorageSTI_DeleteFile (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_DeleteFile  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_DeleteFile
	#define EXT_STI_DeleteFile
	#define GET_STI_DeleteFile(fl)  CAL_CMGETAPI( "STI_DeleteFile" ) 
	#define CAL_STI_DeleteFile pICmpCAAStorage->ISTI_DeleteFile
	#define CHK_STI_DeleteFile (pICmpCAAStorage != NULL)
	#define EXP_STI_DeleteFile  CAL_CMEXPAPI( "STI_DeleteFile" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_DeleteFile  PFSTI_DELETEFILE pfSTI_DeleteFile;
	#define EXT_STI_DeleteFile  extern PFSTI_DELETEFILE pfSTI_DeleteFile;
	#define GET_STI_DeleteFile(fl)  s_pfCMGetAPI2( "STI_DeleteFile", (RTS_VOID_FCTPTR *)&pfSTI_DeleteFile, (fl), 0, 0)
	#define CAL_STI_DeleteFile  pfSTI_DeleteFile
	#define CHK_STI_DeleteFile  (pfSTI_DeleteFile != NULL)
	#define EXP_STI_DeleteFile  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_DeleteFile", (RTS_UINTPTR)STI_DeleteFile, 0, 0) 
#endif




STO_ERROR CDECL STI_StorageExecuteStatement(STI_STORAGE hStorage, RTS_IEC_STRING *sStatement);
typedef STO_ERROR (CDECL * PFSTI_STORAGEEXECUTESTATEMENT) (STI_STORAGE hStorage, RTS_IEC_STRING *sStatement);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEEXECUTESTATEMENT_NOTIMPLEMENTED)
	#define USE_STI_StorageExecuteStatement
	#define EXT_STI_StorageExecuteStatement
	#define GET_STI_StorageExecuteStatement(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_StorageExecuteStatement(p0,p1)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_StorageExecuteStatement  FALSE
	#define EXP_STI_StorageExecuteStatement  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_StorageExecuteStatement
	#define EXT_STI_StorageExecuteStatement
	#define GET_STI_StorageExecuteStatement(fl)  CAL_CMGETAPI( "STI_StorageExecuteStatement" ) 
	#define CAL_STI_StorageExecuteStatement  STI_StorageExecuteStatement
	#define CHK_STI_StorageExecuteStatement  TRUE
	#define EXP_STI_StorageExecuteStatement  CAL_CMEXPAPI( "STI_StorageExecuteStatement" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_StorageExecuteStatement
	#define EXT_STI_StorageExecuteStatement
	#define GET_STI_StorageExecuteStatement(fl)  CAL_CMGETAPI( "STI_StorageExecuteStatement" ) 
	#define CAL_STI_StorageExecuteStatement  STI_StorageExecuteStatement
	#define CHK_STI_StorageExecuteStatement  TRUE
	#define EXP_STI_StorageExecuteStatement  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageExecuteStatement", (RTS_UINTPTR)STI_StorageExecuteStatement, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_StorageExecuteStatement
	#define EXT_CmpCAAStorageSTI_StorageExecuteStatement
	#define GET_CmpCAAStorageSTI_StorageExecuteStatement  ERR_OK
	#define CAL_CmpCAAStorageSTI_StorageExecuteStatement pICmpCAAStorage->ISTI_StorageExecuteStatement
	#define CHK_CmpCAAStorageSTI_StorageExecuteStatement (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_StorageExecuteStatement  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_StorageExecuteStatement
	#define EXT_STI_StorageExecuteStatement
	#define GET_STI_StorageExecuteStatement(fl)  CAL_CMGETAPI( "STI_StorageExecuteStatement" ) 
	#define CAL_STI_StorageExecuteStatement pICmpCAAStorage->ISTI_StorageExecuteStatement
	#define CHK_STI_StorageExecuteStatement (pICmpCAAStorage != NULL)
	#define EXP_STI_StorageExecuteStatement  CAL_CMEXPAPI( "STI_StorageExecuteStatement" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_StorageExecuteStatement  PFSTI_STORAGEEXECUTESTATEMENT pfSTI_StorageExecuteStatement;
	#define EXT_STI_StorageExecuteStatement  extern PFSTI_STORAGEEXECUTESTATEMENT pfSTI_StorageExecuteStatement;
	#define GET_STI_StorageExecuteStatement(fl)  s_pfCMGetAPI2( "STI_StorageExecuteStatement", (RTS_VOID_FCTPTR *)&pfSTI_StorageExecuteStatement, (fl), 0, 0)
	#define CAL_STI_StorageExecuteStatement  pfSTI_StorageExecuteStatement
	#define CHK_STI_StorageExecuteStatement  (pfSTI_StorageExecuteStatement != NULL)
	#define EXP_STI_StorageExecuteStatement  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageExecuteStatement", (RTS_UINTPTR)STI_StorageExecuteStatement, 0, 0) 
#endif



STO_ERROR CDECL STI_StorageGetTableId(STI_STORAGE hStorage, RTS_IEC_STRING *sTable, RTS_IEC_DWORD *pidTable);
typedef STO_ERROR (CDECL * PFSTI_STORAGEGETTABLEID) (STI_STORAGE hStorage, RTS_IEC_STRING *sTable, RTS_IEC_DWORD *pidTable);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEGETTABLEID_NOTIMPLEMENTED)
	#define USE_STI_StorageGetTableId
	#define EXT_STI_StorageGetTableId
	#define GET_STI_StorageGetTableId(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_StorageGetTableId(p0,p1,p2)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_StorageGetTableId  FALSE
	#define EXP_STI_StorageGetTableId  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_StorageGetTableId
	#define EXT_STI_StorageGetTableId
	#define GET_STI_StorageGetTableId(fl)  CAL_CMGETAPI( "STI_StorageGetTableId" ) 
	#define CAL_STI_StorageGetTableId  STI_StorageGetTableId
	#define CHK_STI_StorageGetTableId  TRUE
	#define EXP_STI_StorageGetTableId  CAL_CMEXPAPI( "STI_StorageGetTableId" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_StorageGetTableId
	#define EXT_STI_StorageGetTableId
	#define GET_STI_StorageGetTableId(fl)  CAL_CMGETAPI( "STI_StorageGetTableId" ) 
	#define CAL_STI_StorageGetTableId  STI_StorageGetTableId
	#define CHK_STI_StorageGetTableId  TRUE
	#define EXP_STI_StorageGetTableId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageGetTableId", (RTS_UINTPTR)STI_StorageGetTableId, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_StorageGetTableId
	#define EXT_CmpCAAStorageSTI_StorageGetTableId
	#define GET_CmpCAAStorageSTI_StorageGetTableId  ERR_OK
	#define CAL_CmpCAAStorageSTI_StorageGetTableId pICmpCAAStorage->ISTI_StorageGetTableId
	#define CHK_CmpCAAStorageSTI_StorageGetTableId (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_StorageGetTableId  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_StorageGetTableId
	#define EXT_STI_StorageGetTableId
	#define GET_STI_StorageGetTableId(fl)  CAL_CMGETAPI( "STI_StorageGetTableId" ) 
	#define CAL_STI_StorageGetTableId pICmpCAAStorage->ISTI_StorageGetTableId
	#define CHK_STI_StorageGetTableId (pICmpCAAStorage != NULL)
	#define EXP_STI_StorageGetTableId  CAL_CMEXPAPI( "STI_StorageGetTableId" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_StorageGetTableId  PFSTI_STORAGEGETTABLEID pfSTI_StorageGetTableId;
	#define EXT_STI_StorageGetTableId  extern PFSTI_STORAGEGETTABLEID pfSTI_StorageGetTableId;
	#define GET_STI_StorageGetTableId(fl)  s_pfCMGetAPI2( "STI_StorageGetTableId", (RTS_VOID_FCTPTR *)&pfSTI_StorageGetTableId, (fl), 0, 0)
	#define CAL_STI_StorageGetTableId  pfSTI_StorageGetTableId
	#define CHK_STI_StorageGetTableId  (pfSTI_StorageGetTableId != NULL)
	#define EXP_STI_StorageGetTableId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageGetTableId", (RTS_UINTPTR)STI_StorageGetTableId, 0, 0) 
#endif



STO_ERROR CDECL STI_StorageGetIndexId(STI_STORAGE hStorage, RTS_IEC_STRING *sTable, RTS_IEC_STRING *sIndex, RTS_IEC_DWORD *pidIndex);
typedef STO_ERROR (CDECL * PFSTI_STORAGEGETINDEXID) (STI_STORAGE hStorage, RTS_IEC_STRING *sTable, RTS_IEC_STRING *sIndex, RTS_IEC_DWORD *pidIndex);
#if defined(CMPCAASTORAGE_NOTIMPLEMENTED) || defined(STI_STORAGEGETINDEXID_NOTIMPLEMENTED)
	#define USE_STI_StorageGetIndexId
	#define EXT_STI_StorageGetIndexId
	#define GET_STI_StorageGetIndexId(fl)  ERR_NOTIMPLEMENTED
	#define CAL_STI_StorageGetIndexId(p0,p1,p2,p3)  (STO_ERROR)ERR_NOTIMPLEMENTED
	#define CHK_STI_StorageGetIndexId  FALSE
	#define EXP_STI_StorageGetIndexId  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_STI_StorageGetIndexId
	#define EXT_STI_StorageGetIndexId
	#define GET_STI_StorageGetIndexId(fl)  CAL_CMGETAPI( "STI_StorageGetIndexId" ) 
	#define CAL_STI_StorageGetIndexId  STI_StorageGetIndexId
	#define CHK_STI_StorageGetIndexId  TRUE
	#define EXP_STI_StorageGetIndexId  CAL_CMEXPAPI( "STI_StorageGetIndexId" ) 
#elif defined(MIXED_LINK) && !defined(CMPCAASTORAGE_EXTERNAL)
	#define USE_STI_StorageGetIndexId
	#define EXT_STI_StorageGetIndexId
	#define GET_STI_StorageGetIndexId(fl)  CAL_CMGETAPI( "STI_StorageGetIndexId" ) 
	#define CAL_STI_StorageGetIndexId  STI_StorageGetIndexId
	#define CHK_STI_StorageGetIndexId  TRUE
	#define EXP_STI_StorageGetIndexId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageGetIndexId", (RTS_UINTPTR)STI_StorageGetIndexId, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpCAAStorageSTI_StorageGetIndexId
	#define EXT_CmpCAAStorageSTI_StorageGetIndexId
	#define GET_CmpCAAStorageSTI_StorageGetIndexId  ERR_OK
	#define CAL_CmpCAAStorageSTI_StorageGetIndexId pICmpCAAStorage->ISTI_StorageGetIndexId
	#define CHK_CmpCAAStorageSTI_StorageGetIndexId (pICmpCAAStorage != NULL)
	#define EXP_CmpCAAStorageSTI_StorageGetIndexId  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_STI_StorageGetIndexId
	#define EXT_STI_StorageGetIndexId
	#define GET_STI_StorageGetIndexId(fl)  CAL_CMGETAPI( "STI_StorageGetIndexId" ) 
	#define CAL_STI_StorageGetIndexId pICmpCAAStorage->ISTI_StorageGetIndexId
	#define CHK_STI_StorageGetIndexId (pICmpCAAStorage != NULL)
	#define EXP_STI_StorageGetIndexId  CAL_CMEXPAPI( "STI_StorageGetIndexId" ) 
#else /* DYNAMIC_LINK */
	#define USE_STI_StorageGetIndexId  PFSTI_STORAGEGETINDEXID pfSTI_StorageGetIndexId;
	#define EXT_STI_StorageGetIndexId  extern PFSTI_STORAGEGETINDEXID pfSTI_StorageGetIndexId;
	#define GET_STI_StorageGetIndexId(fl)  s_pfCMGetAPI2( "STI_StorageGetIndexId", (RTS_VOID_FCTPTR *)&pfSTI_StorageGetIndexId, (fl), 0, 0)
	#define CAL_STI_StorageGetIndexId  pfSTI_StorageGetIndexId
	#define CHK_STI_StorageGetIndexId  (pfSTI_StorageGetIndexId != NULL)
	#define EXP_STI_StorageGetIndexId  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"STI_StorageGetIndexId", (RTS_UINTPTR)STI_StorageGetIndexId, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSTO_BLOBALLOC ISTO_BlobAlloc;
 	PFSTO_BLOBCOPYTODATA ISTO_BlobCopyToData;
 	PFSTO_BLOBFREE ISTO_BlobFree;
 	PFSTO_DATACOPYTOBLOB ISTO_DataCopyToBlob;
 	PFSTO_INT64_TO_LOCALTIME ISTO_INT64_TO_LOCALTIME;
 	PFSTO_INT64_TO_UTC ISTO_INT64_TO_UTC;
 	PFSTO_DT_TO_INT64 ISTO_DT_TO_INT64;
 	PFSTO_DT_TO_ISO8601 ISTO_DT_TO_ISO8601;
 	PFSTO_DT_TO_REAL8 ISTO_DT_TO_REAL8;
 	PFSTO_INT64_TO_DT ISTO_INT64_TO_DT;
 	PFSTO_INT64_TO_ISO8601 ISTO_INT64_TO_ISO8601;
 	PFSTO_INT64_TO_LTIME ISTO_INT64_TO_LTIME;
 	PFSTO_INT64_TO_REAL8 ISTO_INT64_TO_REAL8;
 	PFSTO_INT64_TO_TIME ISTO_INT64_TO_TIME;
 	PFSTO_ISO8601_TO_DT ISTO_ISO8601_TO_DT;
 	PFSTO_ISO8601_TO_LTIME ISTO_ISO8601_TO_LTIME;
 	PFSTO_ISO8601_TO_TIME ISTO_ISO8601_TO_TIME;
 	PFSTO_LTIME_TO_INT64 ISTO_LTIME_TO_INT64;
 	PFSTO_LTIME_TO_ISO8601 ISTO_LTIME_TO_ISO8601;
 	PFSTO_LTIME_TO_REAL8 ISTO_LTIME_TO_REAL8;
 	PFSTO_REAL8_TO_DT ISTO_REAL8_TO_DT;
 	PFSTO_REAL8_TO_LTIME ISTO_REAL8_TO_LTIME;
 	PFSTO_REAL8_TO_TIME ISTO_REAL8_TO_TIME;
 	PFSTO_TIME_TO_INT64 ISTO_TIME_TO_INT64;
 	PFSTO_TIME_TO_ISO8601 ISTO_TIME_TO_ISO8601;
 	PFSTO_TIME_TO_REAL8 ISTO_TIME_TO_REAL8;
 	PFSTO_CREATETEXTFROMSTRING ISTO_CreateTextFromString;
 	PFSTO_CREATETEXTFROMWSTRING ISTO_CreateTextFromWString;
 	PFSTO_TEXTCOPYTOSTRING ISTO_TextCopyToString;
 	PFSTO_TEXTCOPYTOWSTRING ISTO_TextCopyToWString;
 	PFSTO_TEXTFREE ISTO_TextFree;
 	PFSTO_GETSUPPLIERVERSION ISTO_GetSupplierVersion;
 	PFSTI_COLUMNGETBLOB ISTI_ColumnGetBLOB;
 	PFSTI_COLUMNGETINT16 ISTI_ColumnGetINT16;
 	PFSTI_COLUMNGETINT32 ISTI_ColumnGetINT32;
 	PFSTI_COLUMNGETINT64 ISTI_ColumnGetINT64;
 	PFSTI_COLUMNGETINT8 ISTI_ColumnGetINT8;
 	PFSTI_COLUMNGETREAL4 ISTI_ColumnGetREAL4;
 	PFSTI_COLUMNGETREAL8 ISTI_ColumnGetREAL8;
 	PFSTI_COLUMNGETTEXT ISTI_ColumnGetTEXT;
 	PFSTI_COLUMNGETTYPE ISTI_ColumnGetType;
 	PFSTI_COLUMNSETBLOB ISTI_ColumnSetBLOB;
 	PFSTI_COLUMNSETINT16 ISTI_ColumnSetINT16;
 	PFSTI_COLUMNSETINT32 ISTI_ColumnSetINT32;
 	PFSTI_COLUMNSETINT64 ISTI_ColumnSetINT64;
 	PFSTI_COLUMNSETINT8 ISTI_ColumnSetINT8;
 	PFSTI_COLUMNSETNULL ISTI_ColumnSetNULL;
 	PFSTI_COLUMNSETREAL4 ISTI_ColumnSetREAL4;
 	PFSTI_COLUMNSETREAL8 ISTI_ColumnSetREAL8;
 	PFSTI_COLUMNSETTEXT ISTI_ColumnSetTEXT;
 	PFSTI_COLUMNUPDATEBLOB ISTI_ColumnUpdateBLOB;
 	PFSTI_COLUMNUPDATEINT16 ISTI_ColumnUpdateINT16;
 	PFSTI_COLUMNUPDATEINT32 ISTI_ColumnUpdateINT32;
 	PFSTI_COLUMNUPDATEINT64 ISTI_ColumnUpdateINT64;
 	PFSTI_COLUMNUPDATEINT8 ISTI_ColumnUpdateINT8;
 	PFSTI_COLUMNUPDATEREAL4 ISTI_ColumnUpdateREAL4;
 	PFSTI_COLUMNUPDATEREAL8 ISTI_ColumnUpdateREAL8;
 	PFSTI_COLUMNUPDATETEXT ISTI_ColumnUpdateTEXT;
 	PFSTI_CURSORCLOSE ISTI_CursorClose;
 	PFSTI_CURSORGETCURRENTROW ISTI_CursorGetCurrentRow;
 	PFSTI_CURSORGETINDEXID ISTI_CursorGetIndexId;
 	PFSTI_CURSORGETSTORAGE ISTI_CursorGetStorage;
 	PFSTI_CURSORGETTABLE ISTI_CursorGetTable;
 	PFSTI_CURSORISREADONLY ISTI_CursorIsReadOnly;
 	PFSTI_CURSORMOVE ISTI_CursorMove;
 	PFSTI_CURSOROPEN ISTI_CursorOpen;
 	PFSTI_CURSORSEARCHINT16 ISTI_CursorSearchINT16;
 	PFSTI_CURSORSEARCHINT32 ISTI_CursorSearchINT32;
 	PFSTI_CURSORSEARCHINT64 ISTI_CursorSearchINT64;
 	PFSTI_CURSORSEARCHINT8 ISTI_CursorSearchINT8;
 	PFSTI_CURSORSEARCHNULL ISTI_CursorSearchNULL;
 	PFSTI_CURSORSEARCHREAL4 ISTI_CursorSearchREAL4;
 	PFSTI_CURSORSEARCHREAL8 ISTI_CursorSearchREAL8;
 	PFSTI_CURSORSEARCHROWID ISTI_CursorSearchRowId;
 	PFSTI_CURSORSEARCHTEXT ISTI_CursorSearchTEXT;
 	PFSTI_ROWCLEAR ISTI_RowClear;
 	PFSTI_ROWCREATE ISTI_RowCreate;
 	PFSTI_ROWDELETE ISTI_RowDelete;
 	PFSTI_ROWDUPLICATE ISTI_RowDuplicate;
 	PFSTI_ROWGETHASCHANGED ISTI_RowGetHasChanged;
 	PFSTI_ROWGETID ISTI_RowGetId;
 	PFSTI_ROWGETNUMOFCOLUMNS ISTI_RowGetNumOfColumns;
 	PFSTI_ROWGETSTORAGE ISTI_RowGetStorage;
 	PFSTI_ROWGETTABLE ISTI_RowGetTable;
 	PFSTI_ROWINSERT ISTI_RowInsert;
 	PFSTI_ROWUPDATE ISTI_RowUpdate;
 	PFSTI_ROWRELEASE ISTI_RowRelease;
 	PFSTI_ROWSELECT ISTI_RowSelect;
 	PFSTI_SAVEPOINTGETSTORAGE ISTI_SavepointGetStorage;
 	PFSTI_SAVEPOINTGETTRANSACTION ISTI_SavepointGetTransaction;
 	PFSTI_SAVEPOINTRELEASE ISTI_SavepointRelease;
 	PFSTI_SAVEPOINTROLLBACK ISTI_SavepointRollback;
 	PFSTI_STORAGECLEAR ISTI_StorageClear;
 	PFSTI_STORAGECLOSE ISTI_StorageClose;
 	PFSTI_STORAGEGETENCODING ISTI_StorageGetEncoding;
 	PFSTI_STORAGEGETLOCKINGSTATE ISTI_StorageGetLockingState;
 	PFSTI_STORAGEGETMETRICS ISTI_StorageGetMetrics;
 	PFSTI_STORAGEGETNUMOFTABLES ISTI_StorageGetNumOfTables;
 	PFSTI_STORAGEGETPATH ISTI_StorageGetPath;
 	PFSTI_STORAGEGETSCHEMAVERSION ISTI_StorageGetSchemaVersion;
 	PFSTI_STORAGEGETSTORAGEVERSION ISTI_StorageGetStorageVersion;
 	PFSTI_STORAGEGETUSERVERSION ISTI_StorageGetUserVersion;
 	PFSTI_STORAGEISREADONLY ISTI_StorageIsReadOnly;
 	PFSTI_STORAGEOPENFILE ISTI_StorageOpenFile;
 	PFSTI_STORAGEREORG ISTI_StorageReorg;
 	PFSTI_TABLECLEAR ISTI_TableClear;
 	PFSTI_TABLECLOSE ISTI_TableClose;
 	PFSTI_TABLEGETID ISTI_TableGetId;
 	PFSTI_TABLEGETMINMAXROWIDS ISTI_TableGetMinMaxRowIds;
 	PFSTI_TABLEGETNUMOFCOLUMNS ISTI_TableGetNumOfColumns;
 	PFSTI_TABLEGETNUMOFINDEXES ISTI_TableGetNumOfIndexes;
 	PFSTI_TABLEGETNUMOFROWS ISTI_TableGetNumOfRows;
 	PFSTI_TABLEGETSTORAGE ISTI_TableGetStorage;
 	PFSTI_TABLEOPEN ISTI_TableOpen;
 	PFSTI_TRANSACTIONBEGIN ISTI_TransactionBegin;
 	PFSTI_TRANSACTIONCOMMIT ISTI_TransactionCommit;
 	PFSTI_TRANSACTIONGETSTORAGE ISTI_TransactionGetStorage;
 	PFSTI_TRANSACTIONROLLBACK ISTI_TransactionRollback;
 	PFSTI_TRANSACTIONSETSAVEPOINT ISTI_TransactionSetSavepoint;
 	PFSTI_UTILITYGETCURRENTDATEANDTIME ISTI_UtilityGetCurrentDateAndTime;
 	PFSTI_UTILITYRANDOMNESS ISTI_UtilityRandomness;
 	PFSTI_DELETEFILE ISTI_DeleteFile;
 	PFSTI_STORAGEEXECUTESTATEMENT ISTI_StorageExecuteStatement;
 	PFSTI_STORAGEGETTABLEID ISTI_StorageGetTableId;
 	PFSTI_STORAGEGETINDEXID ISTI_StorageGetIndexId;
 } ICmpCAAStorage_C;

#ifdef CPLUSPLUS
class ICmpCAAStorage : public IBase
{
	public:
		virtual STO_BLOB* CDECL ISTO_BlobAlloc(CAA_SIZE szData, STO_ERROR *peError) =0;
		virtual STO_ERROR CDECL ISTO_BlobCopyToData(STO_BLOB* pBlob, CAA_BYTE* pData, CAA_SIZE szData) =0;
		virtual STO_ERROR CDECL ISTO_BlobFree(STO_BLOB* pBlob) =0;
		virtual STO_ERROR CDECL ISTO_DataCopyToBlob(CAA_BYTE* pData, CAA_SIZE szData, STO_BLOB* pBlob) =0;
		virtual STO_ERROR CDECL ISTO_INT64_TO_LOCALTIME(STO_INT64 i64UTCValue, STO_INT64 *pi64LocalValue) =0;
		virtual STO_ERROR CDECL ISTO_INT64_TO_UTC(STO_INT64 i64LocalValue, STO_INT64 *pi64UTCValue) =0;
		virtual STO_ERROR CDECL ISTO_DT_TO_INT64(CAA_DT dtValue, CAA_LINT *pliValue) =0;
		virtual STO_ERROR CDECL ISTO_DT_TO_ISO8601(CAA_DT dtValue, STO_ISO8601 *psValue) =0;
		virtual STO_ERROR CDECL ISTO_DT_TO_REAL8(CAA_DT dtValue, CAA_LREAL *plrValue) =0;
		virtual STO_ERROR CDECL ISTO_INT64_TO_DT(CAA_LINT liValue, CAA_DT *pdtValue) =0;
		virtual STO_ERROR CDECL ISTO_INT64_TO_ISO8601(CAA_LINT liValue, STO_ISO8601 *psValue) =0;
		virtual STO_ERROR CDECL ISTO_INT64_TO_LTIME(CAA_LINT liValue, CAA_LTIME *pltValue) =0;
		virtual STO_ERROR CDECL ISTO_INT64_TO_REAL8(CAA_LINT liValue, CAA_LREAL *plrValue) =0;
		virtual STO_ERROR CDECL ISTO_INT64_TO_TIME(CAA_LINT liValue, CAA_TIME *ptValue) =0;
		virtual STO_ERROR CDECL ISTO_ISO8601_TO_DT(STO_ISO8601 *psValue, CAA_DT *pdtValue) =0;
		virtual STO_ERROR CDECL ISTO_ISO8601_TO_LTIME(STO_ISO8601 *psValue, CAA_LTIME *pltValue) =0;
		virtual STO_ERROR CDECL ISTO_ISO8601_TO_TIME(STO_ISO8601 *psValue, CAA_TIME *ptValue) =0;
		virtual STO_ERROR CDECL ISTO_LTIME_TO_INT64(CAA_LTIME ltValue, CAA_LINT *pliValue) =0;
		virtual STO_ERROR CDECL ISTO_LTIME_TO_ISO8601(CAA_LTIME ltValue, STO_ISO8601 *psValue) =0;
		virtual STO_ERROR CDECL ISTO_LTIME_TO_REAL8(CAA_LTIME ltValue, CAA_LREAL *plrValue) =0;
		virtual STO_ERROR CDECL ISTO_REAL8_TO_DT(CAA_LREAL lrValue, CAA_DT *pdtValue) =0;
		virtual STO_ERROR CDECL ISTO_REAL8_TO_LTIME(CAA_LREAL lrValue, CAA_LTIME *pltValue) =0;
		virtual STO_ERROR CDECL ISTO_REAL8_TO_TIME(CAA_LREAL lrValue, CAA_TIME *ptValue) =0;
		virtual STO_ERROR CDECL ISTO_TIME_TO_INT64(CAA_TIME tValue, CAA_LINT *pliValue) =0;
		virtual STO_ERROR CDECL ISTO_TIME_TO_ISO8601(CAA_TIME tValue, STO_ISO8601 *psValue) =0;
		virtual STO_ERROR CDECL ISTO_TIME_TO_REAL8(CAA_TIME tValue, CAA_LREAL *plrValue) =0;
		virtual STO_ERROR CDECL ISTO_CreateTextFromString(CAA_STRING * psValue, STO_TEXT* ptxtValue) =0;
		virtual STO_ERROR CDECL ISTO_CreateTextFromWString(CAA_WSTRING * pwsValue, STO_TEXT* ptxtValue) =0;
		virtual STO_ERROR CDECL ISTO_TextCopyToString(STO_TEXT* ptxtText, CAA_STRING * psValue, CAA_SIZE szValue, CAA_BOOL xFree) =0;
		virtual STO_ERROR CDECL ISTO_TextCopyToWString(STO_TEXT* ptxtValue, CAA_WSTRING* pwsValue, CAA_SIZE szValue, CAA_BOOL xFree) =0;
		virtual STO_ERROR CDECL ISTO_TextFree(STO_TEXT* ptxtValue) =0;
		virtual CAA_WORD CDECL ISTO_GetSupplierVersion(CAA_BOOL xDummy) =0;
		virtual STO_ERROR CDECL ISTI_ColumnGetBLOB(STI_ROW hRow, CAA_IDENT idColumn, STO_BLOB *pblobValue, CAA_BOOL *pxNULL) =0;
		virtual STO_ERROR CDECL ISTI_ColumnGetINT16(STI_ROW hRow, CAA_IDENT idColumn, CAA_INT *piValue, CAA_BOOL *pxNULL) =0;
		virtual STO_ERROR CDECL ISTI_ColumnGetINT32(STI_ROW hRow, CAA_IDENT idColumn, CAA_DINT *pdiValue, CAA_BOOL *pxNULL) =0;
		virtual STO_ERROR CDECL ISTI_ColumnGetINT64(STI_ROW hRow, CAA_IDENT idColumn, CAA_LINT *pliValue, CAA_BOOL *pxNULL) =0;
		virtual STO_ERROR CDECL ISTI_ColumnGetINT8(STI_ROW hRow, CAA_IDENT idColumn, CAA_SINT *psiValue, CAA_BOOL *pxNULL) =0;
		virtual STO_ERROR CDECL ISTI_ColumnGetREAL4(STI_ROW hRow, CAA_IDENT idColumn, CAA_REAL *prValue, CAA_BOOL *pxNULL) =0;
		virtual STO_ERROR CDECL ISTI_ColumnGetREAL8(STI_ROW hRow, CAA_IDENT idColumn, CAA_LREAL *plrValue, CAA_BOOL *pxNULL) =0;
		virtual STO_ERROR CDECL ISTI_ColumnGetTEXT(STI_ROW hRow, CAA_IDENT idColumn, STO_TEXT *ptxtValue, CAA_BOOL *pxNULL) =0;
		virtual STO_COLUMN_TYPE CDECL ISTI_ColumnGetType(STI_ROW hRow, CAA_IDENT idColumn, STO_ERROR *peError) =0;
		virtual STO_ERROR CDECL ISTI_ColumnSetBLOB(STI_ROW hRow, CAA_IDENT idColumn, STO_BLOB *pblobValue) =0;
		virtual STO_ERROR CDECL ISTI_ColumnSetINT16(STI_ROW hRow, CAA_IDENT idColumn, CAA_INT iValue) =0;
		virtual STO_ERROR CDECL ISTI_ColumnSetINT32(STI_ROW hRow, CAA_IDENT idColumn, CAA_DINT diValue) =0;
		virtual STO_ERROR CDECL ISTI_ColumnSetINT64(STI_ROW hRow, CAA_IDENT idColumn, CAA_LINT liValue) =0;
		virtual STO_ERROR CDECL ISTI_ColumnSetINT8(STI_ROW hRow, CAA_IDENT idColumn, CAA_SINT siValue) =0;
		virtual STO_ERROR CDECL ISTI_ColumnSetNULL(STI_ROW hRow, CAA_IDENT idColumn) =0;
		virtual STO_ERROR CDECL ISTI_ColumnSetREAL4(STI_ROW hRow, CAA_IDENT idColumn, CAA_REAL rValue) =0;
		virtual STO_ERROR CDECL ISTI_ColumnSetREAL8(STI_ROW hRow, CAA_IDENT idColumn, CAA_LREAL lrValue) =0;
		virtual STO_ERROR CDECL ISTI_ColumnSetTEXT(STI_ROW hRow, CAA_IDENT idColumn, STO_TEXT *ptxtValue) =0;
		virtual STO_ERROR CDECL ISTI_ColumnUpdateBLOB(STI_ROW hRow, CAA_IDENT idColumn, STO_BLOB *pblobValue, CAA_BOOL *pxNULL) =0;
		virtual STO_ERROR CDECL ISTI_ColumnUpdateINT16(STI_ROW hRow, CAA_IDENT idColumn, CAA_INT *piValue, CAA_BOOL *pxNULL) =0;
		virtual STO_ERROR CDECL ISTI_ColumnUpdateINT32(STI_ROW hRow, CAA_IDENT idColumn, CAA_DINT *pdiValue, CAA_BOOL *pxNULL) =0;
		virtual STO_ERROR CDECL ISTI_ColumnUpdateINT64(STI_ROW hRow, CAA_IDENT idColumn, CAA_LINT *pliValue, CAA_BOOL *pxNULL) =0;
		virtual STO_ERROR CDECL ISTI_ColumnUpdateINT8(STI_ROW hRow, CAA_IDENT idColumn, CAA_SINT *psiValue, CAA_BOOL *pxNULL) =0;
		virtual STO_ERROR CDECL ISTI_ColumnUpdateREAL4(STI_ROW hRow, CAA_IDENT idColumn, CAA_REAL *prValue, CAA_BOOL *pxNULL) =0;
		virtual STO_ERROR CDECL ISTI_ColumnUpdateREAL8(STI_ROW hRow, CAA_IDENT idColumn, CAA_LREAL *plrValue, CAA_BOOL *pxNULL) =0;
		virtual STO_ERROR CDECL ISTI_ColumnUpdateTEXT(STI_ROW hRow, CAA_IDENT idColumn, STO_TEXT *ptxtValue, CAA_BOOL *pxNULL) =0;
		virtual STO_ERROR CDECL ISTI_CursorClose(STI_CURSOR hCursor) =0;
		virtual STI_ROW CDECL ISTI_CursorGetCurrentRow(STI_CURSOR hCursor, STO_ERROR *peError) =0;
		virtual CAA_IDENT CDECL ISTI_CursorGetIndexId(STI_CURSOR hCursor, STO_ERROR *peError) =0;
		virtual STI_STORAGE CDECL ISTI_CursorGetStorage(STI_CURSOR hCursor, STO_ERROR *peError) =0;
		virtual STI_TABLE CDECL ISTI_CursorGetTable(STI_CURSOR hCursor, STO_ERROR *peError) =0;
		virtual CAA_BOOL CDECL ISTI_CursorIsReadOnly(STI_CURSOR hCursor, STO_ERROR *peError) =0;
		virtual STO_ERROR CDECL ISTI_CursorMove(STI_CURSOR hCursor, STO_DIRECTION eDirection) =0;
		virtual STI_CURSOR CDECL ISTI_CursorOpen(STI_TABLE hTable, CAA_IDENT idIndex, CAA_BOOL xReadOnly, STO_ERROR *peError) =0;
		virtual STO_ERROR CDECL ISTI_CursorSearchINT16(STI_CURSOR hCursor, CAA_INT iValue) =0;
		virtual STO_ERROR CDECL ISTI_CursorSearchINT32(STI_CURSOR hCursor, CAA_DINT diValue) =0;
		virtual STO_ERROR CDECL ISTI_CursorSearchINT64(STI_CURSOR hCursor, CAA_LINT liValue) =0;
		virtual STO_ERROR CDECL ISTI_CursorSearchINT8(STI_CURSOR hCursor, CAA_SINT siValue) =0;
		virtual STO_ERROR CDECL ISTI_CursorSearchNULL(STI_CURSOR hCursor) =0;
		virtual STO_ERROR CDECL ISTI_CursorSearchREAL4(STI_CURSOR hCursor, CAA_REAL rValue) =0;
		virtual STO_ERROR CDECL ISTI_CursorSearchREAL8(STI_CURSOR hCursor, CAA_LREAL lrValue) =0;
		virtual STO_ERROR CDECL ISTI_CursorSearchRowId(STI_CURSOR hCursor, CAA_LINT idRow) =0;
		virtual STO_ERROR CDECL ISTI_CursorSearchTEXT(STI_CURSOR hCursor, STO_TEXT *ptxtValue) =0;
		virtual STO_ERROR CDECL ISTI_RowClear(STI_ROW hRow) =0;
		virtual STI_ROW CDECL ISTI_RowCreate(STI_TABLE hTable, STO_ERROR *peError) =0;
		virtual STO_ERROR CDECL ISTI_RowDelete(STI_TABLE hTable, CAA_LINT idRow) =0;
		virtual STI_ROW CDECL ISTI_RowDuplicate(STI_TABLE hTable, CAA_IDENT idRow, STO_ERROR *peError) =0;
		virtual CAA_BOOL CDECL ISTI_RowGetHasChanged(STI_ROW hRow, STO_ERROR *peError) =0;
		virtual CAA_LINT CDECL ISTI_RowGetId(STI_ROW hRow, STO_ERROR *peError) =0;
		virtual CAA_COUNT CDECL ISTI_RowGetNumOfColumns(STI_ROW hRow, STO_ERROR *peError) =0;
		virtual STI_STORAGE CDECL ISTI_RowGetStorage(STI_ROW hRow, STO_ERROR *peError) =0;
		virtual STI_TABLE CDECL ISTI_RowGetTable(STI_ROW hRow, STO_ERROR *peError) =0;
		virtual CAA_IDENT CDECL ISTI_RowInsert(STI_ROW hRow, STO_ERROR *peError) =0;
		virtual STO_ERROR CDECL ISTI_RowUpdate(STI_ROW hRow) =0;
		virtual STO_ERROR CDECL ISTI_RowRelease(STI_ROW hRow) =0;
		virtual STI_ROW CDECL ISTI_RowSelect(STI_TABLE hTable, CAA_IDENT idRow, STO_ERROR *peError) =0;
		virtual STI_STORAGE CDECL ISTI_SavepointGetStorage(STI_SAVEPOINT hSavepoint, STO_ERROR *peError) =0;
		virtual STI_TRANSACTION CDECL ISTI_SavepointGetTransaction(STI_SAVEPOINT hSavepoint, STO_ERROR *peError) =0;
		virtual STO_ERROR CDECL ISTI_SavepointRelease(STI_SAVEPOINT hSavePoint) =0;
		virtual STO_ERROR CDECL ISTI_SavepointRollback(STI_SAVEPOINT hSavePoint) =0;
		virtual STO_ERROR CDECL ISTI_StorageClear(STI_STORAGE hStorage) =0;
		virtual STO_ERROR CDECL ISTI_StorageClose(STI_STORAGE hStorage) =0;
		virtual STO_ENCODING CDECL ISTI_StorageGetEncoding(STI_STORAGE hStorage, STO_ERROR *peError) =0;
		virtual STO_LOCKING_STATE CDECL ISTI_StorageGetLockingState(STI_STORAGE hStorage, STO_ERROR *peError) =0;
		virtual STO_ERROR CDECL ISTI_StorageGetMetrics(STI_STORAGE hStorage, STO_METRICS *pmMetrics) =0;
		virtual CAA_COUNT CDECL ISTI_StorageGetNumOfTables(STI_STORAGE hStorage, STO_ERROR *peError) =0;
		virtual STO_ERROR CDECL ISTI_StorageGetPath(STI_STORAGE hStorage, CAA_FILENAME *psPath) =0;
		virtual CAA_DINT CDECL ISTI_StorageGetSchemaVersion(STI_STORAGE hStorage, STO_ERROR *peError) =0;
		virtual CAA_DINT CDECL ISTI_StorageGetStorageVersion(STI_STORAGE hStorage, STO_ERROR *peError) =0;
		virtual CAA_DINT CDECL ISTI_StorageGetUserVersion(STI_STORAGE hStorage, STO_ERROR *peError) =0;
		virtual CAA_BOOL CDECL ISTI_StorageIsReadOnly(STI_STORAGE hStorage, STO_ERROR *peError) =0;
		virtual STI_STORAGE CDECL ISTI_StorageOpenFile(CAA_FILENAME sPath, CAA_BOOL xReadOnly, STO_ERROR *peError) =0;
		virtual STO_ERROR CDECL ISTI_StorageReorg(STI_STORAGE hStorage) =0;
		virtual STO_ERROR CDECL ISTI_TableClear(STI_TABLE hTable) =0;
		virtual STO_ERROR CDECL ISTI_TableClose(STI_TABLE hTable) =0;
		virtual CAA_IDENT CDECL ISTI_TableGetId(STI_TABLE hTable, STO_ERROR *peError) =0;
		virtual STO_ERROR CDECL ISTI_TableGetMinMaxRowIds(STI_TABLE hTable, RTS_IEC_LINT *pliRowIdMin, RTS_IEC_LINT *pliRowIdMax) =0;
		virtual CAA_COUNT CDECL ISTI_TableGetNumOfColumns(STI_TABLE hTable, STO_ERROR *peError) =0;
		virtual CAA_COUNT CDECL ISTI_TableGetNumOfIndexes(STI_TABLE hTable, STO_ERROR *peError) =0;
		virtual CAA_COUNT CDECL ISTI_TableGetNumOfRows(STI_TABLE hTable, STO_ERROR *peError) =0;
		virtual STI_STORAGE CDECL ISTI_TableGetStorage(STI_TABLE hTable, STO_ERROR *peError) =0;
		virtual STI_TABLE CDECL ISTI_TableOpen(STI_STORAGE hStorage, CAA_IDENT idTable, STO_ERROR *peError) =0;
		virtual STI_TRANSACTION CDECL ISTI_TransactionBegin(STI_STORAGE hStorage, STO_TRANSACTION_MODE eMode, STO_ERROR *peError) =0;
		virtual STO_ERROR CDECL ISTI_TransactionCommit(STI_TRANSACTION hTransaction) =0;
		virtual STI_STORAGE CDECL ISTI_TransactionGetStorage(STI_TRANSACTION hTransaction, STO_ERROR *peError) =0;
		virtual STO_ERROR CDECL ISTI_TransactionRollback(STI_TRANSACTION hTransaction) =0;
		virtual STI_SAVEPOINT CDECL ISTI_TransactionSetSavepoint(STI_TRANSACTION hTransaction, STO_ERROR *peError) =0;
		virtual STO_INT64 CDECL ISTI_UtilityGetCurrentDateAndTime(STI_STORAGE hStorage, STO_ERROR *peError) =0;
		virtual STO_ERROR CDECL ISTI_UtilityRandomness(STI_STORAGE hStorage, CAA_SIZE szSize, CAA_PVOID pData) =0;
		virtual STO_ERROR CDECL ISTI_DeleteFile(CAA_FILENAME sPath) =0;
		virtual STO_ERROR CDECL ISTI_StorageExecuteStatement(STI_STORAGE hStorage, RTS_IEC_STRING *sStatement) =0;
		virtual STO_ERROR CDECL ISTI_StorageGetTableId(STI_STORAGE hStorage, RTS_IEC_STRING *sTable, RTS_IEC_DWORD *pidTable) =0;
		virtual STO_ERROR CDECL ISTI_StorageGetIndexId(STI_STORAGE hStorage, RTS_IEC_STRING *sTable, RTS_IEC_STRING *sIndex, RTS_IEC_DWORD *pidIndex) =0;
};
	#ifndef ITF_CmpCAAStorage
		#define ITF_CmpCAAStorage static ICmpCAAStorage *pICmpCAAStorage = NULL;
	#endif
	#define EXTITF_CmpCAAStorage
#else	/*CPLUSPLUS*/
	typedef ICmpCAAStorage_C		ICmpCAAStorage;
	#ifndef ITF_CmpCAAStorage
		#define ITF_CmpCAAStorage
	#endif
	#define EXTITF_CmpCAAStorage
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCAASTORAGEITF_H_*/
