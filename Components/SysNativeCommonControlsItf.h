 
	
	
#ifndef _SYSNATIVECOMMONCONTROLSITF_H_
#define _SYSNATIVECOMMONCONTROLSITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"

/**
 * <category>Static defines</category>
 * <description>Number of static SysNativeControlCustom instances</description>
 */
#ifndef NUM_OF_STATIC_CUSTOM_CONTROLS
	#define NUM_OF_STATIC_CUSTOM_CONTROLS	4
#endif

/**
 * <category>Settings</category>
 * <description>Setting defining whether on certain platforms (e.g. Linux/QT) plugins displaying
 * special web content are enabled (value 1) or not (value 0). For security reasons plugins are
 * disabled by default.
 * </description>
 */
#define SYSNATIVECOMMONCONTROLS_KEY_PLUGINS_ENABLED						"PluginsEnabled"
#ifndef SYSNATIVECOMMONCONTROLS_KEY_PLUGINS_ENABLED_DEFAULT
	#define SYSNATIVECOMMONCONTROLS_KEY_PLUGINS_ENABLED_DEFAULT			0
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
} ISysNativeCommonControls_C;

#ifdef CPLUSPLUS
class ISysNativeCommonControls : public IBase
{
	public:
};
	#ifndef ITF_SysNativeCommonControls
		#define ITF_SysNativeCommonControls static ISysNativeCommonControls *pISysNativeCommonControls = NULL;
	#endif
	#define EXTITF_SysNativeCommonControls
#else	/*CPLUSPLUS*/
	typedef ISysNativeCommonControls_C		ISysNativeCommonControls;
	#ifndef ITF_SysNativeCommonControls
		#define ITF_SysNativeCommonControls
	#endif
	#define EXTITF_SysNativeCommonControls
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSNATIVECOMMONCONTROLSITF_H_*/
