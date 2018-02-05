/**
 * <interfacename>CmpDynamicText</interfacename>
 * <description>
 *	Interface for the dynamic text component.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpDynamicText')

#include "CmpItf.h"

/* Hook definitions (0..10000 reserved for core components) */

/**
 * <description>Setting which decides about the path where the text files are saved. 
 * Default is the current working directory.</description>
 *
 */
#define DYNAMICTEXT_KEY_BASEPATH "TextListPath"
#define DYNAMICTEXT_KEY_TEXTLISTFILE "TextListFile"
#define DYNAMICTEXT_KEY_STARTUPLANGUAGE "StartupLanguage"
#define DYNAMICTEXT_KEY_MAX_SCAN_LINE "MaxTextListLine"
#define DYNAMICTEXT_VALUE_BASEPATH_DEFAULT "$visu$"

#ifndef DYNAMICTEXT_MAX_SCAN_LINE
	#define DYNAMICTEXT_MAX_SCAN_LINE 50000
#endif

#ifndef DYNAMICTEXT_MAX_SYMBOLS
	#define DYNAMICTEXT_MAX_SYMBOLS 10000
#endif

#ifndef DYNAMICTEXT_MAX_SYMBOLS_TEXTLISTS
#define DYNAMICTEXT_MAX_SYMBOLS_TEXTLISTS 100
#endif

typedef struct
{
	RTS_IEC_STRING pszLanguage[21];
	RTS_BOOL xOut;
} dynamictextchangelanguage_struct;

typedef struct
{
	RTS_IEC_STRING* pszPrefix;
	RTS_IEC_STRING* pszId;
	RTS_IEC_STRING* pszOut;
} dynamictextgettext_struct;

typedef struct
{
	RTS_IEC_STRING* pszPrefix;	/* TOCHECK: wstring for inputs here? */
	RTS_IEC_STRING* pszId;
	RTS_IEC_WSTRING* wszOut;
} dynamictextgettextw_struct;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description> Function to change the language of all language specific texts. </description>
 * <param name="pEntry" type="IN">Pointer to entry structure</param>
 * <result></result>
 */
DEF_API(`void', `CDECL', `dynamictextchangelanguage', `(dynamictextchangelanguage_struct *pEntry)', 1, 0)

/**
 * <description> Provides functionality to gain language specific texts from a dynamic text file </description>
 * <param name="pszPrefix" type="IN">The prefix specifier</param>
 * <param name="pszId" type="IN">The id specifier</param>
 * <param name="pszOut" type="OUT">The corresponding text</param>
 */
DEF_API(`void', `CDECL', `dynamictextgettext', `(dynamictextgettext_struct *pEntry)', 1, 0)

/**
 * <description> WString version of VisuFctGetText, for further documentation see VisuFctGetText </description>
 */
DEF_API(`void', `CDECL', `dynamictextgettextw', `(dynamictextgettextw_struct *pEntry)', 1, 0)

/**
 * <description> Provides functionality to gain default texts from a dynamic text file </description>
 * <param name="pszPrefix" type="IN">The prefix specifier</param>
 * <param name="pszId" type="IN">The id specifier</param>
 * <param name="pszOut" type="OUT">The corresponding text</param>
 */
DEF_API(`void', `CDECL', `dynamictextgetdefaulttext', `(dynamictextgettext_struct *pEntry)', 1, 0)

/**
 * <description> WString version of VisuFctGetDefaultText, for further documentation see VisuFctGetDefaultText </description>
 */
DEF_API(`void', `CDECL', `dynamictextgetdefaulttextw', `(dynamictextgettextw_struct *pEntry)', 1, 0)

/**
 * <description>This function loads the default texts from the currently registered text files.
 * as a IEC-String (char* in the runtime) </description>
 */
typedef struct tagdynamictextloaddefaulttexts_struct
{
	RTS_IEC_UDINT DynamicTextLoadDefaultTexts;	/* VAR_OUTPUT */
} dynamictextloaddefaulttexts_struct;

DEF_API(`void',`CDECL',`dynamictextloaddefaulttexts',`(dynamictextloaddefaulttexts_struct *p)',1,0xBC5AF7A3,0x3040100)

/**
 * <description>This function reloads all currently registered text files for the currently assigned language.
 * This function could be used for example when you know that a textfile was updated externally and you want
 * to reload those files.</description>
 */
typedef struct tagdynamictextreloadtexts_struct
{
	RTS_IEC_UDINT DynamicTextReloadTexts;	/* VAR_OUTPUT */
} dynamictextreloadtexts_struct;

DEF_API(`void',`CDECL',`dynamictextreloadtexts',`(dynamictextreloadtexts_struct *p)',1,0x50855C4B,0x3040100)

/**
 * <description><p>This method returns the name of the currently loaded language if there is 
 * any.</p>
 * <p>If no language is loaded (there was no call to DynamicTextChangeLanguage before), then an 
 * empty string will be returned.</p></description>
 */
typedef struct tagdynamictextgetcurrentlanguage_struct
{
	RTS_IEC_STRING DynamicTextGetCurrentLanguage[81];	/* VAR_OUTPUT */
} dynamictextgetcurrentlanguage_struct;

DEF_API(`void',`CDECL',`dynamictextgetcurrentlanguage',`(dynamictextgetcurrentlanguage_struct *p)',1,0x282B626C,0x3040100)

/**
 * This function registers a dynamic text file.
 * These registered text files are considered when load or reload is called
 * on the CmpDynamicText component.  
 */
typedef struct tagdynamictextregisterfile_struct
{
	RTS_IEC_STRING *szFile;				/* VAR_INPUT */	
	RTS_IEC_RESULT DynamicTextRegisterFile;	/* VAR_OUTPUT */	
} dynamictextregisterfile_struct;

DEF_API(`void',`CDECL',`dynamictextregisterfile',`(dynamictextregisterfile_struct *p)',1,RTSITF_GET_SIGNATURE(0x0C950958, 0),0x03050700)

/**
 * This function unregisters a dynamic text file.
 * The registered text files are considered when load or reload is called
 * on the CmpDynamicText component.  
 */
typedef struct tagdynamictextunregisterfile_struct
{
	RTS_IEC_STRING *szFile;				/* VAR_INPUT */	
	RTS_IEC_RESULT DynamicTextUnRegisterFile;	/* VAR_OUTPUT */	
} dynamictextunregisterfile_struct;

DEF_API(`void',`CDECL',`dynamictextunregisterfile',`(dynamictextunregisterfile_struct *p)',1,RTSITF_GET_SIGNATURE(0x1476C0B1, 0),0x03050700)

/**
 * This function sets an optional path where the dynamic text files
 * are searched when they are loaded or reloaded by the CmpDynamicText component. 
 */
typedef struct tagdynamictextregisterpath_struct
{
	RTS_IEC_STRING *szPath;				/* VAR_INPUT */	
	RTS_IEC_RESULT DynamicTextRegisterPath;	/* VAR_OUTPUT */	
} dynamictextregisterpath_struct;

DEF_API(`void',`CDECL',`dynamictextregisterpath',`(dynamictextregisterpath_struct *p)',1,RTSITF_GET_SIGNATURE(0x1DBE3355, 0),0x03050700)

/**
 * OBSOLETE FUNCTION: Use dynamictextchangelanguage instead
 * <description> Function to change the language of all language specific texts.</description>
 * <param name="pszLanguage" type="IN">The new language</param>
 */
DEF_API(`void', `CDECL', `visufctchangelanguage', `(dynamictextchangelanguage_struct* pParam)', 1, 0)

/**
 * OBSOLETE FUNCTION: Use dynamictextgettext instead
 * <description> Provides functionality to gain language specific texts from a dynamic text file </description>
 * <param name="pszPrefix" type="IN">The prefix specifier</param>
 * <param name="pszId" type="IN">The id specifier</param>
 * <param name="pszOut" type="OUT">The corresponding text</param>
 */
DEF_API(`void', `CDECL', `visufctgettext', `(dynamictextgettext_struct* pParam)', 1, 0)

/**
 * OBSOLETE FUNCTION: Use dynamictextgettextw instead
 * <description> WString version of VisuFctGetText, for further documentation see VisuFctGetText </description>
 */
DEF_API(`void', `CDECL', `visufctgettextw', `(dynamictextgettextw_struct* pParam)', 1, 0)

/**
 * OBSOLETE FUNCTION: Use dynamictextgetdefaulttext instead
 * <description> Provides functionality to gain default texts from a dynamic text file </description>
 * <param name="pszPrefix" type="IN">The prefix specifier</param>
 * <param name="pszId" type="IN">The id specifier</param>
 * <param name="pszOut" type="OUT">The corresponding text</param>
 */
DEF_API(`void', `CDECL', `visufctgetdefaulttext', `(dynamictextgettext_struct* pParam)', 1, 0)

/**
 * OBSOLETE FUNCTION: Use dynamictextgetdefaulttextw instead
 * <description> WString version of VisuFctGetDefaultText, for further documentation see VisuFctGetDefaultText </description>
 */
DEF_API(`void', `CDECL', `visufctgetdefaulttextw', `(dynamictextgettextw_struct* pParam)', 1, 0)


#ifdef __cplusplus
}
#endif
