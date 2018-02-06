/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/








#include "IoDrvADC7001.c"




/* NOTE: REPLACE 0x0000 BY YOUR VENDORID */

#define CMPID_IoDrvADC7001		0x2000		/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CIoDrvADC7001	0x2000		/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_IIoDrvADC7001		0x2000		/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */









RTS_HANDLE CDECL CIoDrvADC7001::IIoDrvCreate(RTS_HANDLE hIIoDrv, CLASSID ClassId, int iId, RTS_RESULT *pResult)
{
	hIoDrvADC7001 = IoDrvCreate(hIIoDrv,ClassId,iId,pResult);
	RTS_HANDLE h = (RTS_HANDLE)QueryInterface((IBase *)(ICmpIoDrv *)this, ITFID_ICmpIoDrv, NULL);
	Release();
	return h;
}

RTS_RESULT CDECL CIoDrvADC7001::IIoDrvDelete(RTS_HANDLE hIIoDrv)
{
	RTS_RESULT Result = IoDrvDelete(hIoDrvADC7001,hIIoDrv);
	DeleteInstance((IBase *)(ICmpIoDrv *)this);
	return Result;
}

RTS_RESULT CDECL CIoDrvADC7001::IIoDrvGetInfo(IoDrvInfo **ppIoDrv)
{
	return IoDrvGetInfo(hIoDrvADC7001,ppIoDrv);
}

RTS_RESULT CDECL CIoDrvADC7001::IIoDrvGetModuleDiagnosis(IoConfigConnector *pConnector)
{
	return IoDrvGetModuleDiagnosis(hIoDrvADC7001,pConnector);
}

RTS_RESULT CDECL CIoDrvADC7001::IIoDrvIdentify(IoConfigConnector *pConnector)
{
	return IoDrvIdentify(hIoDrvADC7001,pConnector);
}

RTS_RESULT CDECL CIoDrvADC7001::IIoDrvReadInputs(IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	return IoDrvReadInputs(hIoDrvADC7001,pConnectorMapList,nCount);
}

RTS_RESULT CDECL CIoDrvADC7001::IIoDrvScanModules(IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount)
{
	return IoDrvScanModules(hIoDrvADC7001,pConnector,ppConnectorList,pnCount);
}

RTS_RESULT CDECL CIoDrvADC7001::IIoDrvStartBusCycle(IoConfigConnector *pConnector)
{
	return IoDrvStartBusCycle(hIoDrvADC7001,pConnector);
}

RTS_RESULT CDECL CIoDrvADC7001::IIoDrvUpdateConfiguration(IoConfigConnector *pConnectorList, int nCount)
{
	return IoDrvUpdateConfiguration(hIoDrvADC7001,pConnectorList,nCount);
}

RTS_RESULT CDECL CIoDrvADC7001::IIoDrvUpdateMapping(IoConfigTaskMap *pTaskMapList, int nCount)
{
	return IoDrvUpdateMapping(hIoDrvADC7001,pTaskMapList,nCount);
}

RTS_RESULT CDECL CIoDrvADC7001::IIoDrvWatchdogTrigger(IoConfigConnector *pConnector)
{
	return IoDrvWatchdogTrigger(hIoDrvADC7001,pConnector);
}

RTS_RESULT CDECL CIoDrvADC7001::IIoDrvWriteOutputs(IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	return IoDrvWriteOutputs(hIoDrvADC7001,pConnectorMapList,nCount);
}





RTS_RESULT CDECL CIoDrvADC7001::IIoDrvReadParameter(IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	return IoDrvReadParameter(hIoDrvADC7001,pConnector,pParameter,pData,ulBitSize,ulBitOffset);
}

RTS_RESULT CDECL CIoDrvADC7001::IIoDrvWriteParameter(IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	return IoDrvWriteParameter(hIoDrvADC7001,pConnector,pParameter,pData,ulBitSize,ulBitOffset);
}







