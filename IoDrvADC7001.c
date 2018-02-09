/*****************************************************************************
*
*	Copyright:		3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		Test component
*	Version:
*	Description:
******************************************************************************/
#ifndef STATICITF_DEF
	#define STATICITF_DEF	static
#endif

#include "CmpStd.h"
#include "IoDrvADC7001Dep.h"
#include "axio/IoDrvInc.h"

USE_STMT

typedef struct
{
#ifndef CPLUSPLUS
	IBase_C Base;
	ICmpIoDrv_C IoDrv;
	ICmpIoDrvParameter_C IoDrvParameter;
#endif
	IBase *pIBase;
	ICmpIoDrv *pIoDrv;
	ICmpIoDrvParameter *pIoDrvParameter;
	IoDrvInfo Info;
} IoDrvSimple;

#ifndef CPLUSPLUS

DECLARE_ADDREF
DECLARE_RELEASE
DECLARE_QUERYINTERFACE

#endif

static IBase *s_pIBase;

#ifndef RTS_COMPACT_MICRO

DLL_DECL int CDECL ComponentEntry(INIT_STRUCT *pInitStruct)
/*	Used to exchange function pointers between component manager and components.
	Called at startup for each component.
	pInitStruct:			IN	Pointer to structure with:
		pfExportFunctions	OUT Pointer to function that exports component functions
		pfImportFunctions	OUT Pointer to function that imports functions from other components
		pfGetVersion		OUT Pointer to function to get component version
		pfRegisterAPI		IN	Pointer to component mangager function to register a api function
		pfGetAPI			IN	Pointer to component mangager function to get a api function
		pfCallHook			IN	Pointer to component mangager function to call a hook function
	Return					ERR_OK if library could be initialized, else error code
*/
{
	pInitStruct->CmpId = COMPONENT_ID;
	pInitStruct->pfExportFunctions = ExportFunctions;
	pInitStruct->pfImportFunctions = ImportFunctions;
	pInitStruct->pfGetVersion = CmpGetVersion;
	pInitStruct->pfHookFunction = HookFunction;
	pInitStruct->pfCreateInstance = CreateInstance;
	pInitStruct->pfDeleteInstance = DeleteInstance;

	s_pfCMRegisterAPI = pInitStruct->pfCMRegisterAPI;
	s_pfCMRegisterAPI2 = pInitStruct->pfCMRegisterAPI2;
	s_pfCMGetAPI = pInitStruct->pfCMGetAPI;
	s_pfCMGetAPI2 = pInitStruct->pfCMGetAPI2;
	s_pfCMCallHook = pInitStruct->pfCMCallHook;
	s_pfCMRegisterClass = pInitStruct->pfCMRegisterClass;
	s_pfCMCreateInstance = pInitStruct->pfCMCreateInstance;

	if (pInitStruct->pfCMRegisterClass != NULL)
		pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CIoDrvADC7001);

	return ERR_OK;
}

#endif

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
#ifdef CPLUSPLUS
	if (cid == CLASSID_CIoDrvADC7001)
	{
		CIoDrvSimple *pCIoDrvSimple = static_cast<CIoDrvSimple *>(new CIoDrvSimple());
		IBase *pIBase = (IBase *)pCIoDrvSimple->QueryInterface(pCIoDrvSimple, ITFID_IBase, pResult);
		RTS_SETRESULT(pResult, ERR_OK);
		return pIBase;
	}
#else
	if (cid == CLASSID_CIoDrvADC7001)
	{
		IoDrvSimple *pIoDrvSimple = (IoDrvSimple *)CAL_SysMemAllocData(COMPONENT_NAME, sizeof(IoDrvSimple), NULL);
		if (pIoDrvSimple != NULL)
		{
			IBase *pI = &pIoDrvSimple->Base;
			pIoDrvSimple->pIBase = &pIoDrvSimple->Base;
			pI->bIEC = 0;
			pI->AddRef = AddRef;
			pI->Release = Release;
			pI->QueryInterface = QueryInterface;
			pI->iRefCount++;
			RTS_SETRESULT(pResult, ERR_OK);
			return pI;
		}
		else
		{
			RTS_SETRESULT(pResult, ERR_NOMEMORY);
			return NULL;
		}
	}
#endif
	RTS_SETRESULT(pResult, ERR_FAILED);
	return NULL;
}

static RTS_RESULT CDECL DeleteInstance(IBase *pIBase)
{
#ifdef CPLUSPLUS
	pIBase->Release();
	return ERR_OK;
#else
	pIBase->iRefCount--;
	CAL_SysMemFreeData(COMPONENT_NAME, pIBase);
	return ERR_OK;
#endif
}

#if !defined(CPLUSPLUS)
IMPLEMENT_ADDREF
IMPLEMENT_RELEASE

static void *CDECL QueryInterface(IBase *pBase, ITFID iid, RTS_RESULT *pResult)
{
	if (iid == ITFID_IBase)
	{
		/* Every interface has as first element a pointer to the IBase interface. So it doesn't matter, which interface
		   is used to get the IBase pointer */
		ICmpIoDrv *pI = (ICmpIoDrv *)pBase;
		pI->pBase->iRefCount++;
		RTS_SETRESULT(pResult, ERR_OK);
		return pI->pBase;
	}
	if (iid == ITFID_ICmpIoDrv)
	{
		IoDrvSimple *pC = (IoDrvSimple *)pBase;
		pC->IoDrv.pBase = pBase;
		pC->IoDrv.IIoDrvCreate = IoDrvCreate;
		pC->IoDrv.IIoDrvDelete = IoDrvDelete;
		pC->IoDrv.IIoDrvGetInfo = IoDrvGetInfo;
		pC->IoDrv.IIoDrvUpdateConfiguration = IoDrvUpdateConfiguration;
		pC->IoDrv.IIoDrvUpdateMapping = IoDrvUpdateMapping;
		pC->IoDrv.IIoDrvReadInputs = IoDrvReadInputs;
		pC->IoDrv.IIoDrvWriteOutputs = IoDrvWriteOutputs;
		pC->IoDrv.IIoDrvStartBusCycle = IoDrvStartBusCycle;
		pC->IoDrv.IIoDrvScanModules = IoDrvScanModules;
		pC->IoDrv.IIoDrvGetModuleDiagnosis = IoDrvGetModuleDiagnosis;
		pC->pIoDrv = &pC->IoDrv;
		pC->Base.iRefCount++;
		RTS_SETRESULT(pResult, ERR_OK);
		return &pC->IoDrv;
	}
	if (iid == ITFID_ICmpIoDrvParameter)
	{
		IoDrvSimple *pC = (IoDrvSimple *)pBase;
		pC->IoDrvParameter.pBase = pBase;
		pC->IoDrvParameter.IIoDrvReadParameter = IoDrvReadParameter;
		pC->IoDrvParameter.IIoDrvWriteParameter = IoDrvWriteParameter;
		pC->pIoDrvParameter = &pC->IoDrvParameter;
		pC->Base.iRefCount++;
		RTS_SETRESULT(pResult, ERR_OK);
		return &pC->IoDrvParameter;
	}
	RTS_SETRESULT(pResult, ERR_FAILED);
	return NULL;
}
#endif

#ifndef RTS_COMPACT_MICRO

static int CDECL ExportFunctions(void)
/*	Export function pointers as api */
{
	/* Macro to export functions */
	EXPORT_STMT;
	return ERR_OK;
}

static int CDECL ImportFunctions(void)
/*	Get function pointers of other components */
{
	/* Macro to import functions */
	IMPORT_STMT;
	return ERR_OK;
}

static RTS_UI32 CDECL CmpGetVersion(void)
{
	return CMP_VERSION;
}

#endif

/* Example for a Hook function */
static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
	switch (ulHook)
	{
		case CH_INIT_SYSTEM:
			break;
		case CH_INIT:
			break;
		case CH_INIT2:
		{
			RTS_HANDLE hIoDrv = 0;
			void *pTmp;

			/* first instance */
			pTmp = CAL_IoDrvCreate(hIoDrv, CLASSID_CIoDrvADC7001, 0, NULL);
			s_pIBase = (IBase *)pTmp;
			CAL_IoMgrRegisterInstance(s_pIBase, NULL);
			break;
		}		
		case CH_INIT3:
			iosInit();   //zhoujh added 20161115
			break;
		case CH_INIT_TASKS:
			break;
		case CH_INIT_COMM:
			break;

		/* Cyclic */
		case CH_COMM_CYCLE:
			break;

#ifndef RTS_COMPACT_MICRO
		case CH_EXIT_COMM:
			break;
		case CH_EXIT_TASKS:
			break;
		case CH_EXIT3:
			break;
		case CH_EXIT2:
			break;
		case CH_EXIT:
		{
			/* Delete instance */
			ICmpIoDrv *pI;
			
			CAL_IoMgrUnregisterInstance(s_pIBase);
			pI = (ICmpIoDrv *)s_pIBase->QueryInterface(s_pIBase, ITFID_ICmpIoDrv, NULL);
			s_pIBase->Release(s_pIBase);
			CAL_IoDrvDelete((RTS_HANDLE)pI, (RTS_HANDLE)pI);
			DeleteInstance(s_pIBase);

			EXIT_STMT;
			break;
		}
		case CH_EXIT_SYSTEM:
			break;
#endif

		default:
			break;
	}
	return ERR_OK;
}

/**
 * My External Function
 */
void CDECL CDECL_EXT myexternalfunction(myexternalfunction_struct *p) {

}

/**
 * Implementation of the IoDrv Interface
 */

static unsigned long s_ulyIO[MAX_DRIVERS][MAX_CHANNELS];

STATICITF RTS_HANDLE CDECL IoDrvCreate(RTS_HANDLE hIIoDrv, CLASSID ClassId, int iId, RTS_RESULT *pResult)
{

	IoDrvInfo *pInfo;
	IoDrvSimple *pIoDrvSimple;

	RTS_SETRESULT(pResult, ERR_OK);

	/* Only one instance allowed */
	if (iId > 0) {
		RTS_SETRESULT(pResult, ERR_NOMEMORY);
		return RTS_INVALID_HANDLE;
	}

#ifdef CPLUSPLUS
	pIoDrvSimple = (IoDrvSimple *)CAL_SysMemAllocData(COMPONENT_NAME, sizeof(IoDrvSimple), NULL);
	pIoDrvSimple->pIBase = (IBase *)hIIoDrv;	
	pIoDrvSimple->pIoDrv = (ICmpIoDrv *)pIoDrvSimple->pIBase->QueryInterface(pIoDrvSimple->pIBase, ITFID_ICmpIoDrv, NULL);
	pIoDrvSimple->pIoDrvParameter = (ICmpIoDrvParameter *)pIoDrvSimple->pIBase->QueryInterface(pIoDrvSimple->pIBase, ITFID_ICmpIoDrvParameter, NULL);
	pIoDrvSimple->pIBase->Release(pIoDrvSimple->pIBase);
	pIoDrvSimple->pIBase->Release(pIoDrvSimple->pIBase);
	pInfo = &pIoDrvSimple->Info;
#else
	pIoDrvSimple = (IoDrvSimple *)hIIoDrv;
	pIoDrvSimple->IoDrv.pBase = &pIoDrvSimple->Base;
	pIoDrvSimple->IoDrvParameter.pBase = &pIoDrvSimple->Base;
	pInfo = &pIoDrvSimple->Info;
#endif

	pInfo->wId = (RTS_IEC_WORD)iId;
	pInfo->wModuleType = 40100;
	pInfo->hSpecific = (RTS_IEC_HANDLE)s_ulyIO[iId];
	pInfo->dwVersion = CMP_VERSION;

	strcpy(pInfo->szDriverName, "MyCard");
	strcpy(pInfo->szDeviceName, "MyCard");
	strcpy(pInfo->szVendorName, "MyCompany");
	strcpy(pInfo->szFirmwareVersion, "Rev. 3.5.8.11");
	return (RTS_HANDLE)pInfo;
}

STATICITF RTS_RESULT CDECL IoDrvDelete(RTS_HANDLE hIoDrv, RTS_HANDLE hIIoDrv)
{
#ifdef CPLUSPLUS
	IoDrvSimple *pIoDrvSimple = (IoDrvSimple *)((unsigned char *)hIoDrv - sizeof(IoDrvSimple) + sizeof(IoDrvInfo));
	CAL_SysMemFreeData(COMPONENT_NAME, pIoDrvSimple);
#endif
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvGetInfo(RTS_HANDLE hIoDrv, IoDrvInfo **ppInfo)
{
	if (ppInfo == NULL || hIoDrv == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	*ppInfo = (IoDrvInfo *)hIoDrv;
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvUpdateConfiguration(RTS_HANDLE hIoDrv, IoConfigConnector *pConnectorList, int nCount)
{
	IoConfigConnector *pConnector = CAL_IoMgrConfigGetFirstConnector(pConnectorList, &nCount, 40100);
	IoDrvSimple *pIoDrvSimple = (IoDrvSimple *)((unsigned char *)hIoDrv - sizeof(IoDrvSimple) + sizeof(IoDrvInfo));
	IBase *pIBase = pIoDrvSimple->pIBase;
	/*ICmpIoDrv *pIIoDrv = pIoDrvSimple->pIoDrv;*/

	while (pConnector != NULL)
	{
		IoDrvInfo *pInfo;
		IoConfigParameter *pParameter;
		IoConfigConnector *pChild;
		char *pszVendorName = NULL;
		char *pszDeviceName = NULL;
		unsigned char *pTestParameter;

		IoDrvGetInfo(hIoDrv, &pInfo);

		/* The connector type 40100 is not unique, so additional info must be investigated to detect our own device.
		   Here for example, two parameters with the vendorname and the devicename are used. */
		pParameter = CAL_IoMgrConfigGetParameter(pConnector, 393218);
		if (pParameter != NULL && pParameter->dwFlags & PVF_POINTER)
			pszVendorName = (char *)pParameter->dwValue;
		pParameter = CAL_IoMgrConfigGetParameter(pConnector, 393219);
		if (pParameter != NULL && pParameter->dwFlags & PVF_POINTER)
			pszDeviceName = (char *)pParameter->dwValue;

		/* If the connector is still occupied by another driver instance, skip this connector */
		if (pConnector->hIoDrv == 0 &&
			pszVendorName != NULL && strcmp(pszVendorName, pInfo->szVendorName) == 0 &&
			pszDeviceName != NULL && strcmp(pszDeviceName, pInfo->szDeviceName) == 0)
		{
			int i;

			/* Our driver instance must be registered at this connector to:
			- occupy this connector (that no other driver instance will use this connector)
			- to mark, that the conector is supported by a driver
			- for the IoMgr to be able to direct access the driver of this connector
			Always the pointer to the IBase interface must be written in the IO-driver handle of the connector! */
			pConnector->hIoDrv = (RTS_IEC_HANDLE)pIBase;

			/* If the father is our input connector, you have to register the driver in this connector too
			to mark, that this connector is ours */
			if (pConnector->pFather != NULL && pConnector->pFather->wType == CT_PCI_MASTER)
				pConnector->pFather->hIoDrv = (RTS_IEC_HANDLE)pIBase;

			/* Set the property, that bit consistency is provided by the driver! */
			CAL_IoMgrSetDriverProperties(pIBase, DRVPROP_CONSISTENCY);

			/* If the connector has childs, they can be handled here */
			pChild = CAL_IoMgrConfigGetFirstChild(pConnector, &nCount, pConnector);
			while (pChild != NULL)
			{
				/* With this code you can go through all child connectors of the father pConnector */

				/* Example: This is the access to a parameter of the child connector */
				pParameter = CAL_IoMgrConfigGetParameter(pChild, 4711);
				
				pChild = CAL_IoMgrConfigGetNextChild(pChild, &nCount, pConnector);
			}
			
			pParameter = CAL_IoMgrConfigGetParameter(pConnector, 393220);	/* test parameter */
			if (pParameter != NULL)
			{
				if (pParameter->dwFlags & PVF_POINTER)
					pTestParameter = (unsigned char *)pParameter->dwValue;
			}

			/* inputs */
			for(i=0; i < MAX_IN; i++) {
				pParameter = CAL_IoMgrConfigGetParameter(pConnector, 1000 + i);
				if (pParameter != NULL) {
					pParameter->dwDriverSpecific = (RTS_IEC_BYTE *)&s_ulyIO[0][i];
					//s_ulyIO[0][i] = i+1;
				} else {
					break;
				}

			}
			
			/* outputs */
			for(i = 0; i < MAX_OUT; i++) {
				pParameter = CAL_IoMgrConfigGetParameter(pConnector, 2000 + i);
				if (pParameter != NULL)
					pParameter->dwDriverSpecific = (RTS_IEC_BYTE *)&s_ulyIO[0][MAX_IN+i];
				else
					break;
			}

			/* The diagnosis bits are set here to mark, that everything is OK
			   or an error occurred on this connector (in this case set the corresponding error flags
			   or remove some valid flags).
			   */
			CAL_IoMgrConfigSetDiagnosis(pConnector, CF_DRIVER_AVAILABLE | CF_CONNECTOR_FOUND | CF_CONNECTOR_CONFIGURED | CF_CONNECTOR_ACTIVE);
			if (pConnector->pFather != NULL)
				CAL_IoMgrConfigSetDiagnosis(pConnector->pFather, CF_DRIVER_AVAILABLE | CF_CONNECTOR_FOUND | CF_CONNECTOR_CONFIGURED | CF_CONNECTOR_ACTIVE);

			/* If a very serious error occurred during IoDrvUpdateConfiguration, the driver can return ERR_EXCEPTION
			   to generate an exception on the corresponding IO-application:
			   return ERR_EXCEPTION; */

			/* If an error occurred during IoDrvUpdateConfiguration, the driver can return ERR_FAILED
			   to generate a logger entry on the corresponding IO-application with the error code.
			   But this has no further consequence:
			   return ERR_FAILED; */
			break;
		}
		pConnector = CAL_IoMgrConfigGetNextConnector(pConnector, &nCount, 40100);
	}
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvUpdateMapping(RTS_HANDLE hIoDrv, IoConfigTaskMap *pTaskMapList, int nCount)
{
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvReadInputs(RTS_HANDLE hIoDrv, IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	int i;
	unsigned long j;

	if (pConnectorMapList == NULL)
		return ERR_PARAMETER;
	
	//input  AI
	read_all_AIs();
	for(i=0; i< MAX_AI_NUM; i++) {
		s_ulyIO[0][BASE_AI+i] = g_all_AIs[i];
	}

	//input DI
	read_all_DIs();
	for(i=0; i<MAX_DI_NUM;i++) {
		s_ulyIO[0][BASE_DI +i] = g_all_DIs[i];
	}

	//input PI   
	read_all_PIs();
	for(i=0; i<MAX_PI_NUM;i++) {   
		s_ulyIO[0][BASE_PI +i] = g_all_PIs[i];
	}
	
	for (i=0; i<nCount; i++)
	{
		for (j=0; j<pConnectorMapList[i].dwNumOfChannels; j++)
		{
			CAL_IoMgrCopyInputLE(&(pConnectorMapList[i].pChannelMapList[j]), (char *)pConnectorMapList[i].pChannelMapList[j].pParameter->dwDriverSpecific);
		}
	}
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvWriteOutputs(RTS_HANDLE hIoDrv, IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	int i;
	unsigned long j;

	if (pConnectorMapList == NULL)
		return ERR_PARAMETER;

	for (i=0; i<nCount; i++)
	{
		for (j=0; j<pConnectorMapList[i].dwNumOfChannels; j++)
		{
			CAL_IoMgrCopyOutputLE(&(pConnectorMapList[i].pChannelMapList[j]), (char *)pConnectorMapList[i].pChannelMapList[j].pParameter->dwDriverSpecific);
		}
	}

	//output AO
	for(i=0; i<MAX_AO_NUM;i++) {    //MAX_AO_NUM  == 0
		 g_all_AOs[i] = s_ulyIO[0][BASE_AO +i] ;
	}
	write_all_AOs();
	
	//output DO
	for(i=0; i<MAX_DO_NUM;i++) {
		 g_all_DOs[i] = s_ulyIO[0][BASE_DO +i] ;
	}
	write_all_DOs();
	
	//output PWM
	for(i=0; i<MAX_PWM_NUM;i++) {
		 g_all_PWMs[i] = s_ulyIO[0][BASE_PWM +i] ;
	}
	write_all_PWMs();

	//output LED
	for(i=0; i<MAX_LED_NUM;i++) {
		 g_all_LEDs[i] = s_ulyIO[0][BASE_LED +i] ;
	}
	write_all_LEDs();
	
	return ERR_OK;
}

/*
input
	AI   	0~31     	32
	DI	32~55	24
	PI	56~63	8

output 
	AO	64~79	16
	DO	80~111	32
	PWM	112~127 16

*/

STATICITF RTS_RESULT CDECL IoDrvStartBusCycle(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)
{
	return IoDrvGetModuleDiagnosis(hIoDrv, pConnector);
}

STATICITF RTS_RESULT CDECL IoDrvScanModules(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount)
{
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvGetModuleDiagnosis(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)
{
	/* Example for IO-error:
	IoDrvInfo *pInfo = (IoDrvInfo *)hIoDrv;
	if (IoError)
		IoMgrConfigSetDiagnosis(pConnector, CF_CONNECTOR_ERROR);
	else
		IoMgrConfigResetDiagnosis(pConnector, CF_CONNECTOR_ERROR);
	*/
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvIdentify(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)
{
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvWatchdogTrigger(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)
{
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvReadParameter(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	if (pParameter == NULL)
		return ERR_PARAMETER;
	
	memcpy(pData, (unsigned char *)pParameter->dwValue, ulBitSize / 8);
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvWriteParameter(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	if (pParameter == NULL)
		return ERR_PARAMETER;

	memcpy((unsigned char *)pParameter->dwValue, pData, ulBitSize / 8);
	return ERR_OK;
}

