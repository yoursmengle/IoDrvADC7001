 /**
 * <interfacename>CmpTargetVisuStub</interfacename>
 * <description> 
 *	Interface for the target visu stub.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPTARGETVISUSTUBITF_H_
#define _CMPTARGETVISUSTUBITF_H_

#include "CmpStd.h"

 

 




/**
 * <category>Settings</category>
 * <description>Setting that decides about the path of the program that will start the process containing the targetvisualization.
 * </description>
 */
#define CMPTARGETVISUSTUB_KEY_TARGETVISUPROCESS_PROGRAM				"Program"
#define CMPTARGETVISUSTUB_KEY_TARGETVISUPROCESS_PROGRAM_DEFAULT		"codesyscontrolservice.exe"

/**
 * <category>Settings</category>
 * <description>Setting that decides about the path of the commandline used as parameter to start the program
 *	containing the targetvisualization.
 * </description>
 */
#define CMPTARGETVISUSTUB_KEY_TARGETVISUPROCESS_CMDLINE				"CommandLine"
#define CMPTARGETVISUSTUB_KEY_TARGETVISUPROCESS_CMDLINE_DEFAULT		"-r targetvisuextern.cfg"

/**
 * <category>Settings</category>
 * <description>Setting that decides about the rate at which the targetvisu checks for updates of the
 * content of the display. This value in ms is no realtime value, so there can be quite some jitter on this value.
 * IMPORTANT: The according visuhandlerstub must have configured the same basename ! </description>
 */
#define CMPTARGETVISUSTUB_KEY_TARGETVISUPROCESS_IPCBASENAME				"IpcBasename"
#define CMPTARGETVISUSTUB_KEY_TARGETVISUPROCESS_IPCBASENAME_DEFAULT		"Ipc__Targetvisu__"

/**
 * <category>Settings</category>
 * <description>Setting that decides about the timeout that is used for single ipccalls </description>
 */
#define CMPTARGETVISUSTUB_KEY_IPCTIMEOUT							"IpcTimeoutMs"
#define CMPTARGETVISUSTUB_KEY_IPCTIMEOUT_DEFAULT					500




typedef struct
{
	IBase_C *pBase;
} ICmpTargetVisuStub_C;

#ifdef CPLUSPLUS
class ICmpTargetVisuStub : public IBase
{
	public:
};
	#ifndef ITF_CmpTargetVisuStub
		#define ITF_CmpTargetVisuStub static ICmpTargetVisuStub *pICmpTargetVisuStub = NULL;
	#endif
	#define EXTITF_CmpTargetVisuStub
#else	/*CPLUSPLUS*/
	typedef ICmpTargetVisuStub_C		ICmpTargetVisuStub;
	#ifndef ITF_CmpTargetVisuStub
		#define ITF_CmpTargetVisuStub
	#endif
	#define EXTITF_CmpTargetVisuStub
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPTARGETVISUSTUBITF_H_*/
