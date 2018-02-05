/**
 * <interfacename>CmpTargetVisuStub</interfacename>
 * <description> 
 *	Interface for the target visu stub.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpTargetVisuStub')

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

