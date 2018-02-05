/*****************************************************************************
*
*	Copyright:		(c) 3s - Smart Software Solutions GmbH, Kempten
*	Program:		CODESYS Control for Linux
*	Component: 		main.c
*	Version:
*	Description:
******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>


#include "CmpStd.h"
#include "CMItf.h"
#include "profile.h"

#include "MainLinux.h"


/* defines */
COMPO_INIT_DECLS

/* statics and variables  */
StaticComponent SysMainComponentList[] = {
	COMPO_INIT_LIST,
	{NULL, NULL, 0}
};

#ifndef RTS_MAIN_EXTERNAL
int main(int argc, char *argv[])
{
	int res = 0;

	/* pass cmdline args to CODESYS runtime */
	PlcCheckArgs(argc, argv);

	/* register main signalhandler for CODESYS runtime */
	PlcRegisterSignalhandler();

	/* synchronous start of plc, blocks until runtime terminates */
	res = PlcStart(0);	

#if 0	
	/* example: asynchronous start of plc, returns after boot of plc */	
	res = PlcStartAsync(0);

	if(res == 0)
	{
		/* wait for commcyclethread to be started */
		while(!PlcRunning())
			sleep(1);

		/*  */
		while(PlcRunning())
		{
			printf("runtime still running\n");
			sleep(10);
		}

		/* example for shutdown if started with PlcStartAsync*/
		PlcExitAsync();

		/* wait until runtime is really terminated */
		while(PlcRunning())
		{
			printf("runtime still running\n");
			sleep(1);
		}

	}


#endif
	
#ifdef SYSTARGET_OS_QNX
	kill(getpid(), 9);
#endif
	
	return res;
}
#endif /* RTS_MAIN_EXTERNAL */

RTS_RESULT MainLoadComponent2(char *pszName, PF_COMPONENT_ENTRY* ppfComponentEntry)
{
	return ERR_FAILED;
}

