/**
 * <interfacename>CmpSettings</interfacename>
 * <description> 
 *	Interface for the settings component. The settings component can have different backend
 *	components, to realise different sources for the settings (e.g. ini-File, hardcoded, XML, etc.).
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpSettings')

/**
 * <category>Static defines</category>
 * <description>This define can be used to call always the standard settings database.
 * </description>
 */
#ifndef STD_SETTINGS_DATABASE
	#define STD_SETTINGS_DATABASE				"CODESYSControl"
#endif
#ifndef STD_SETTINGS_DATABASE_OLD2
	#define STD_SETTINGS_DATABASE_OLD2			"CoDeSysControl"
#endif

/**
 * <category>Static defines</category>
 * <description>This define can be used to call always the standard settings database.
 * </description>
 */
#ifndef STD_SETTINGS_DATABASE_OLD
	#define STD_SETTINGS_DATABASE_OLD			"CoDeSysSP"
#endif

/**
 * <category>Static defines</category>
 * <description>Delimiter for the end of line, if a settings file is used as backend.
 * </description>
 */
#ifndef FILE_END_OF_LINE_DELIMITER
	#define FILE_END_OF_LINE_DELIMITER			"\r\n"
#endif

/**
 * <category>Static defines</category>
 * <description>Number of static setting files. Only used by CmpSettings component to handle configuration
 *	files in static data.</description>
 */
#ifndef CMPSETTINGS_NUM_OF_STATIC_FILES
	#define CMPSETTINGS_NUM_OF_STATIC_FILES		1
#endif

/**
 * <category>Static defines</category>
 * <description>Name of the master configuration file, if standard config file could not be opened</description>
 */
#ifndef CMPSETTINGS_MASTER_CONFIG
	#define CMPSETTINGS_MASTER_CONFIG			"Master.cfg"
#endif

/**
 * <category>Static defines</category>
 * <description>Name of the standard configuration file</description>
 */
#ifndef CMPSETTINGS_STD_CONFIG
	#define CMPSETTINGS_STD_CONFIG				STD_SETTINGS_DATABASE".cfg"
#endif



/**
 * <category>Settings</category>
 * <description>
 *	Setting for the settings component to specify, if the each component has its own settings database file.
 *	1: Split database files
 *	0: All settings in one database file
 * </description>
 */
#define CMPSETTINGS_KEY_INT_SPLIT_DATABASES					"SplitDatabases"
#ifndef CMPSETTINGS_KEY_INT_SPLIT_DATABASES_DEFAULT
	#define CMPSETTINGS_KEY_INT_SPLIT_DATABASES_DEFAULT		0
#endif

/**
 * <category>Settings</category>
 * <description>
 *	Setting to specify external configuration files:
 *	File reference list must be indexed, started with 0 or 1, e.g.:
 *	FileReference.0=[Configurationfile.cfg]
 *
 *	If the file does not exist, the file is created.
 *  You can specify sections, that should be created in this referenced file, by a comma separated list. e.g.:
 *	FileReference.0=[Configurationfile.cfg], CmpApp
 * </description>
 */
#define CMPSETTINGS_KEY_STRING_FILE_REFERENCE				"FileReference"
#ifndef CMPSETTINGS_KEY_STRING_FILE_REFERENCE_DEFAULT
	#define CMPSETTINGS_KEY_STRING_FILE_REFERENCE_DEFAULT	""
#endif


/**
 * <category>Static defines</category>
 * <description>Predefined objects in the runtime</description>
 */
#define USERDB_OBJECT_SETTINGS		"Device.Settings"

/**
 * <category>Static defines</category>
 * <description>Options of the parameter bCached</description>
 */
/* Value is read from cache (default) */
#define CMPSETTINGS_CACHED 0
/* Value is read from file and cache is updated for all values */
#define CMPSETTINGS_NOT_CACHED 1


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * | Function to block writing settings to database file until |SettgEndUpdate| is called! But the settings cache is updated.
 * | NOTE:
 * | - Funcion can be called nested, so only at the last call of |SettgEndUpdate|, the database is written!
 * | - Always call SettgBeginUpdate() and SettgEndUpdate() symmetric!!!
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsettgbeginupdate_struct
{
	RTS_IEC_RESULT SettgBeginUpdate;	/* VAR_OUTPUT */	
} settgbeginupdate_struct;

DEF_API(`void',`CDECL',`settgbeginupdate',`(settgbeginupdate_struct *p)',1,0x8767D13E,0x03050700)

/**
 * | Function to initiate writing settings to database file, if settings are modified after |SettgBeginUpdate| was called.
 * | NOTE:
 * | - Funcion can be called nested, so only at the last call of |SettgEndUpdate|, the database is written!
 * | - Always call |SettgBeginUpdate| and |SettgEndUpdate| symmetric!!!
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsettgendupdate_struct
{
	RTS_IEC_RESULT SettgEndUpdate;		/* VAR_OUTPUT */	
} settgendupdate_struct;

DEF_API(`void',`CDECL',`settgendupdate',`(settgendupdate_struct *p)',1,0x460858D3,0x03050700)

/**
 * | Get an integer value from settings
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsettggetintvalue_struct
{
	RTS_IEC_STRING *pszComponent;		/* VAR_INPUT */	/* Name of component */
	RTS_IEC_STRING *pszKey;				/* VAR_INPUT */	/* Name of key */
	RTS_IEC_DINT *piValue;				/* VAR_INPUT */	/* Pointer to value for result */
	RTS_IEC_DINT iDefault;				/* VAR_INPUT */	/* Default value to set, if key not found */
	RTS_IEC_DINT bCached;				/* VAR_INPUT */	/* Flag, if value should be read cached or direct from file (CMPSETTINGS_CACHED, CMPSETTINGS_NOT_CACHED) */
	RTS_IEC_RESULT SettgGetIntValue;	/* VAR_OUTPUT */	
} settggetintvalue_struct;

DEF_API(`void',`CDECL',`settggetintvalue',`(settggetintvalue_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x0065176D),0x03050700)

/**
 * | Get a string value from settings
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsettggetstringvalue_struct
{
	RTS_IEC_STRING *pszComponent;		/* VAR_INPUT */	/* Name of component */
	RTS_IEC_STRING *pszKey;				/* VAR_INPUT */	/* Name of key */
	RTS_IEC_STRING *pszValue;			/* VAR_INPUT */	/* Pointer to value for result */
	RTS_IEC_DINT *piLen;				/* VAR_INPUT */	/* Max length of string value */
	RTS_IEC_STRING *pszDefault;			/* VAR_INPUT */	/* Default value to set, if key not found */
	RTS_IEC_DINT bCached;				/* VAR_INPUT */	/* Flag, if value should be read cached or direct from file (CMPSETTINGS_CACHED, CMPSETTINGS_NOT_CACHED) */
	RTS_IEC_RESULT SettgGetStringValue;	/* VAR_OUTPUT */	
} settggetstringvalue_struct;

DEF_API(`void',`CDECL',`settggetstringvalue',`(settggetstringvalue_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x366FF6F7),0x03050700)

/**
 * | Get a WSTRING value from settings
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsettggetwstringvalue_struct
{
	RTS_IEC_STRING *pszComponent;		/* VAR_INPUT */	/* Name of component */
	RTS_IEC_STRING *pszKey;				/* VAR_INPUT */	/* Name of key */
	RTS_IEC_WSTRING *pwszValue;			/* VAR_INPUT */	/* Pointer to value for result */
	RTS_IEC_DINT *piLen;				/* VAR_INPUT */	/* Max length of string in WSTRING characters (not bytes!) */
	RTS_IEC_WSTRING *pwszDefault;		/* VAR_INPUT */	/* Default value to set, if key not found */
	RTS_IEC_DINT bCached;				/* VAR_INPUT */	/* Flag, if value should be read cached or direct from file (CMPSETTINGS_CACHED, CMPSETTINGS_NOT_CACHED) */
	RTS_IEC_RESULT SettgGetWStringValue;	/* VAR_OUTPUT */	
} settggetwstringvalue_struct;

DEF_API(`void',`CDECL',`settggetwstringvalue',`(settggetwstringvalue_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x17E6DC47),0x03050700)

/**
 * | Remove the specified key
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsettgremovekey_struct
{
	RTS_IEC_STRING *pszComponent;		/* VAR_INPUT */	/* Name of component */
	RTS_IEC_STRING *pszKey;				/* VAR_INPUT */	/* Name of key */
	RTS_IEC_RESULT SettgRemoveKey;		/* VAR_OUTPUT */	
} settgremovekey_struct;

DEF_API(`void',`CDECL',`settgremovekey',`(settgremovekey_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xBA5C250F),0x03050700)

/**
 * | Write an integer value to settings
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsettgsetintvalue_struct
{
	RTS_IEC_STRING *pszComponent;		/* VAR_INPUT */	/* Name of component */
	RTS_IEC_STRING *pszKey;				/* VAR_INPUT */	/* Name of key */
	RTS_IEC_DINT iValue;				/* VAR_INPUT */	/* Value to write */
	RTS_IEC_DINT iBase;					/* VAR_INPUT */	/* 2=Base 2, 10=Decimal values, 16=Hex values */
	RTS_IEC_RESULT SettgSetIntValue;	/* VAR_OUTPUT */	
} settgsetintvalue_struct;

DEF_API(`void',`CDECL',`settgsetintvalue',`(settgsetintvalue_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0xBC5E022C),0x03050700)

/**
 * | Write a string value to settings
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsettgsetstringvalue_struct
{
	RTS_IEC_STRING *pszComponent;		/* VAR_INPUT */	/* Name of component */
	RTS_IEC_STRING *pszKey;				/* VAR_INPUT */	/* Name of key */
	RTS_IEC_STRING *pszValue;			/* VAR_INPUT */	/* Pointer to write value */
	RTS_IEC_DINT iLen;					/* VAR_INPUT */	/* Length of string to write */
	RTS_IEC_RESULT SettgSetStringValue;	/* VAR_OUTPUT */	
} settgsetstringvalue_struct;

DEF_API(`void',`CDECL',`settgsetstringvalue',`(settgsetstringvalue_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x63FA6ABA),0x03050700)

/**
 * | Write a WSTRING value to settings
 * :return: Runtime system error code (see CmpErrors.library).
 */
typedef struct tagsettgsetwstringvalue_struct
{
	RTS_IEC_STRING *pszComponent;		/* VAR_INPUT */	/* Name of component */
	RTS_IEC_STRING *pszKey;				/* VAR_INPUT */	/* Name of key */
	RTS_IEC_WSTRING *pwszValue;			/* VAR_INPUT */	/* Pointer to write value */
	RTS_IEC_DINT iLen;					/* VAR_INPUT */	/* Length of string in WSTRING characters (not bytes!) to write */
	RTS_IEC_UDINT SettgSetWStringValue;	/* VAR_OUTPUT */	
} settgsetwstringvalue_struct;

DEF_API(`void',`CDECL',`settgsetwstringvalue',`(settgsetwstringvalue_struct *p)',1,RTSITF_GET_SIGNATURE(0, 0x61870FE4),0x03050700)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

 
/**
 * <description>Set database name for all settings</description>
 * <param name="pszName" type="IN">Name of settings file. Can be *.cfg or *.ini</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SettgSetDatabaseName', `(char *pszName)')

/**
 * <description>Get database name for all settings</description>
 * <param name="pszName" type="OUT">Name of settings file. Can be *.cfg or *.ini</param>
 * <param name="nNameLen" type="IN">Lenght of the name buffer in bytes</param>
 * <result>Error code</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SettgGetDatabaseName', `(char *pszName, RTS_SIZE nNameLen)')

/**
 * <description>Function to block writing settings to database file until SettgEndUpdate() is called! But the settings cache is updated. 
 * NOTE:
 * - Funcion can be called nested, so only at the last call of SettgEndUpdate(), the database is written!
 * - Always call SettgBeginUpdate() and SettgEndUpdate() symmetric!!!
 * </description>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Task found</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SettgBeginUpdate', `(void)')

/**
 * <description>Function to initiate writing settings to database file, if settings are modified after SettgBeginUpdate() was called.</description>
 * NOTE:
 * - Funcion can be called nested, so only at the last call of SettgEndUpdate(), the database is written!
 * - Always call SettgBeginUpdate() and SettgEndUpdate() symmetric!!!
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Database could be written</errorcode>
 * <errorcode name="RTS_RESULT" type="RTS_FAILED">Database could not be written</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PENDING">We still wait for the last call of SettgEndUpdate()</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">SettgBeginUpdate() not called before</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SettgEndUpdate', `(void)')

/**
 * <description>Internal function to get the accesscounter value which is incremented by every call of SettgBeginUpdate() and is decremented 
 *	by every call of SettgEndUpdate().
 * </description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="pResult" type="ERR_OK">Access counter can be retrieved</errorcode>
 * <result>Actual accesscounter value</result>
 */
DEF_ITF_API(`RTS_I32', `CDECL', `SettgGetAccessCounter_', `(RTS_RESULT *pResult)')

/**
 * <description>Set optional settings</description>
 * <param name="bSeparateDatabases" type="IN">If bSeparateDatabases=1, split settings file into
 *	each file per component</param>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SettgSetOptions', `(int bSplitDatabases)')

/**
 * <description>Is option set to split all settings databases into each file per component</description>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SettgIsOptionSplitDatabases', `(void)')

/**
 * <description>Get an integer value from settings</description>
 * <param name="pszComponent" type="IN">Name of component</param>
 * <param name="pszKey" type="IN">Name of key</param>
 * <param name="piValue" type="INOUT">Pointer to value for result</param>
 * <param name="iDefault" type="IN">Default value to set, if key not found</param>
 * <param name="bCached" type="IN">Flag, if value should be read cached or direct from file (CMPSETTINGS_CACHED, CMPSETTINGS_NOT_CACHED)</param>
 * <result>ERR_OK</result>
 * <result>ERR_FAILED: Key not found</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SettgGetIntValue', `(const char *pszComponent, const char *pszKey, RTS_I32 *piValue, int iDefault, int bCached)')

/**
 * <description>Write an integer value to settings</description>
 * <param name="pszComponent" type="IN">Name of component</param>
 * <param name="pszKey" type="IN">Name of key</param>
 * <param name="iValue" type="IN">Value to write</param>
 * <param name="iBase" type="IN">2=Base 2, 10=Decimal values, 16=Hex values</param>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SettgSetIntValue', `(const char *pszComponent, const char *pszKey, RTS_I32 iValue, int iBase)')

/**
 * <description>Get a string value from settings</description>
 *	The following parameter sets are typical use cases:
 *  - pszValue = NULL, piLen = NULL: Check if the setting exists (ERR_OK) or not (ERR_FAILED).
 *	- pszValue = NULL, piLen != NULL: Check if the setting exists (ERR_OK) or not (ERR_FAILED) and retrieve the needed buffer size
 *                                    to read the setting or the default value (including NUL termination).
 *  - pszValue != NULL, piLen != NULL: Read the setting (or default value). If ERR_BUFFERSIZE is returned, the buffer was too small
 *                                     regardless of whether the setting or the default value was read. Thus in this case there is
 *                                     no indication, if the setting exists or not.
 * <param name="pszComponent" type="IN">Name of component</param>
 * <param name="pszKey" type="IN">Name of key</param>
 * <param name="pszValue" type="INOUT">Pointer to value for result. Can be NULL to get the needed buffer length for the value (including the NUL ending).</param>
 * <param name="piLen" type="INOUT">Max length of string value as IN and number of copied characters excluding the NUL ending as OUT. If pszValue is NULL, then the needed buffer length is returned.</param>
 * <param name="pszDefault" type="IN">Default value to set, if key not found</param>
 * <param name="bCached" type="IN">Flag, if value should be read cached or direct from file (CMPSETTINGS_CACHED, CMPSETTINGS_NOT_CACHED)</param>
 * <result>ERR_OK</result>
 * <result>ERR_PARAMETER: Invalid parameter given</result>
 * <result>ERR_BUFFERSIZE: Buffer size is not sufficient to carry out the complete key; only a part is returned.</result>
 * <result>ERR_FAILED: Key not found</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SettgGetStringValue', `(const char *pszComponent, const char *pszKey, char *pszValue, RTS_I32 *piLen, char *pszDefault, int bCached)')

/**
 * <description>Write a string value to settings</description>
 * <param name="pszComponent" type="IN">Name of component</param>
 * <param name="pszKey" type="IN">Name of key</param>
 * <param name="pszValue" type="IN">Pointer to write value</param>
 * <param name="iLen" type="IN">Length of string to write excluding the NUL ending</param>
 * <result>ERR_OK: Success</result>
 * <result>ERR_PARAMETER: Invalid parameter given</result>
 * <result>ERR_NOTINITIALIZED: Component has not been initialized yet</result>
 * <result>ERR_NOMEMORY: Not enough memory to handle the settings cache</result> 
 * <result>ERR_NOT_SUPPORTED: Unsupported character in key value: '=', '[', ']' or control character 0x00-0x1F, 0x7F</result>
 * <result>ERR_NO_ACCESS_RIGHTS: No write access rights to corresponding settings file</result>
 * <result>ERR_FAILED: Any other reason for failure</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SettgSetStringValue', `(const char *pszComponent, const char *pszKey, char *pszValue, RTS_I32 iLen)')

/**
 * <description> 
 *  Get a WSTRING value from settings.
 *  The storage format is conform to UTF-16, that means one character consists of 2 byte values like "\ab\cd".
 *  Plain ASCII characters can also be represented in a mixed way in order to keep the readability of the string, e.g. "a\00".
 *  The value is interpreted depending on the target byteorder, e.g:
 *   - INTEL: NodeNameUnicode="T\00e\00s\00t\00"
 *   - MOTOROLA: NodeNameUnicode="\00T\00e\00s\00t"
 *  Example: The unicode character 'DEGREE CELSIUS' (U+2103) is stored as 
 *   - INTEL: "\03\21"
 *   - MOTOROLA: "\21\03"
 *	The following parameter sets are typical use cases:
 *	- pwszValue = NULL, piLen = NULL: Check if the setting exists (ERR_OK) or not (ERR_FAILED).
 *	- pwszValue = NULL, piLen != NULL: Check if the setting exists (ERR_OK) or not (ERR_FAILED) and retrieve the needed buffer size
 *                                     to read the setting or the default value (in WSTRING characters including NUL termination).
 *  - pwszValue != NULL, piLen != NULL: Read the setting (or default value). If ERR_BUFFERSIZE is returned, the buffer was too small
 *                                      regardless of whether the setting or the default value was read. Thus in this case there is
 *                                      no indication, if the setting exists or not. 
 * </description>
 * <param name="pszComponent" type="IN">Name of component</param>
 * <param name="pszKey" type="IN">Name of key</param>
 * <param name="pwszValue" type="INOUT">Pointer to value for result. Can be NULL to get the needed buffer length for the value (including the NUL ending).</param>
 * <param name="piLen" type="INOUT">Max length of buffer in WSTRING characters (not bytes!) as IN and number of copied WSTRING characters excluding the NUL ending as OUT. If pwszValue is NULL, then the needed buffer length is returned.</param>
 * <param name="pwszDefault" type="IN">Default value to set, if key not found</param>
 * <param name="bCached" type="IN">Flag, if value should be read cached or direct from file (CMPSETTINGS_CACHED, CMPSETTINGS_NOT_CACHED)</param>
 * <result>ERR_OK</result>
 * <result>ERR_PARAMETER: Invalid parameter given</result>
 * <result>ERR_BUFFERSIZE: Buffer size is not sufficient to carry out the complete setting or default value; only a part is returned.</result>
 * <result>ERR_FAILED: Key not found</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SettgGetWStringValue', `(const char *pszComponent, const char *pszKey, RTS_WCHAR *pwszValue, RTS_I32 *piLen, RTS_WCHAR *pwszDefault, int bCached)')

/**
 * <description>
 *	Write a WSTRING value to settings.
 *  The storage format is conform to UTF-16, that means one character consists of 2 byte values like "\ab\cd".
 *  Plain ASCII characters can also be represented in a mixed way in order to keep the readability of the string, e.g. "a\00".
 *  The value is interpreted depending on the target byteorder, e.g:
 *   - INTEL: NodeNameUnicode="T\00e\00s\00t\00"
 *   - MOTOROLA: NodeNameUnicode="\00T\00e\00s\00t"
 *  Example: The unicode character 'DEGREE CELSIUS' (U+2103) is stored as 
 *   - INTEL: "\03\21"
 *   - MOTOROLA: "\21\03"
 * </description>
 * <param name="pszComponent" type="IN">Name of component</param>
 * <param name="pszKey" type="IN">Name of key</param>
 * <param name="pszValue" type="IN">Pointer to write value</param>
 * <param name="iLen" type="IN">Length of string in WSTRING characters (not bytes!) to write without terminating NUL</param>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SettgSetWStringValue', `(const char *pszComponent, const char *pszKey, RTS_WCHAR *pwszValue, RTS_I32 iLen)')

/**
 * <description>Remove the specified key</description>
 * <param name="pszComponent" type="IN">Name of component</param>
 * <param name="pszKey" type="IN">Name of key</param>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SettgRemoveKey', `(const char *pszComponent, const char *pszKey)')

/**
 * <description>Clear the specified component by deleting all keys</description>
 * <param name="pszSection" type="IN">Name of the component</param>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `SettgClearComponent', `(const char *pszComponent)')

#ifdef __cplusplus
}
#endif
