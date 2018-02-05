/*****************************************************************************
*
*	Copyright:		(c) 3s - Smart Software Solutions GmbH, Kempten
*	Program:		CODESYS Control for Linux
*	Component: 		MainLinux.h
*	Version:
*	Description:    Header for MainLinux.c
******************************************************************************/
#ifndef __MAIN_LINUX_H__
#define __MAIN_LINUX_H__


/* synchronous start of plc, 
   executes plc, control returns after shutdown of plc
   parameter pszConfigFile (optional): filename of plc configuration file to use
   returns 0 if plc was executed successfully
   returns -1 if plc could not be started or was not running successfully
*/
int PlcStart(char *pszConfigFile);


/* asynchronous start of plc, 
   starts plc, control returns and runs plc in own thread (commcyclethread)
   parameter pszConfigFile (optional): filename of plc configuration file to use
   returns 0 if plc could be started successfully
   returns -1 if plc could not be started successfully
 */
int PlcStartAsync(char *pszConfigFile);

/* asynchronous status of plc commcyclethread
   returns 1 while plc is running
   returns 0 when plc is shutting down
 */
int PlcRunning(void);

/* asynchronous stop of plc 
   send command to plc to shutdown gracefully
   returns 0 when plc stop could be set
   returns -1 when plc stop could not be set
 */
int PlcExitAsync(void);

/* pass cmd line args to runtime 
   plc parses command line arguments
   call binary with "--help" for usage
 */
void PlcCheckArgs(int argc, char *argv[]);

/* signalhandling 
   register internal signalhandling in plc
   should be called before PlcStart/PlcStartAsync
 */
void PlcRegisterSignalhandler(void);


#endif /*__MAIN_LINUX_H__*/
