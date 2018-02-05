/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/








#include "SysTarget.c"
























RTS_RESULT CDECL CSysTarget::ISysTargetGetNodeName(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength)
{
	return SysTargetGetNodeName(pwszName,pnMaxLength);
}

RTS_RESULT CDECL CSysTarget::ISysTargetGetConfiguredNodeName(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength)
{
	return SysTargetGetConfiguredNodeName(pwszName,pnMaxLength);
}

RTS_RESULT CDECL CSysTarget::ISysTargetGetType(RTS_UI32 *pulType)
{
	return SysTargetGetType(pulType);
}

RTS_RESULT CDECL CSysTarget::ISysTargetGetId(RTS_UI32 *pulTargetId)
{
	return SysTargetGetId(pulTargetId);
}

RTS_RESULT CDECL CSysTarget::ISysTargetGetVersion(RTS_UI32 *pulVersion)
{
	return SysTargetGetVersion(pulVersion);
}

RTS_RESULT CDECL CSysTarget::ISysTargetGetDeviceName(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength)
{
	return SysTargetGetDeviceName(pwszName,pnMaxLength);
}

RTS_RESULT CDECL CSysTarget::ISysTargetGetVendorName(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength)
{
	return SysTargetGetVendorName(pwszName,pnMaxLength);
}

RTS_RESULT CDECL CSysTarget::ISysTargetGetOperatingSystemId(RTS_UI32 *pulOperatingSystemId)
{
	return SysTargetGetOperatingSystemId(pulOperatingSystemId);
}

RTS_RESULT CDECL CSysTarget::ISysTargetGetProcessorId(RTS_UI32 *pulProcessorId)
{
	return SysTargetGetProcessorId(pulProcessorId);
}

RTS_RESULT CDECL CSysTarget::ISysTargetGetSerialNumber(char **ppszSerialNumber, RTS_I32 *pnMaxLen)
{
	return SysTargetGetSerialNumber(ppszSerialNumber,pnMaxLen);
}

RTS_RESULT CDECL CSysTarget::ISysTargetGetSerialNumber_Secure(char **ppszSerialNumber, RTS_I32 *pnMaxLen)
{
	return SysTargetGetSerialNumber_Secure(ppszSerialNumber,pnMaxLen);
}

RTS_RESULT CDECL CSysTarget::ISysTargetGetSignature(RTS_UI32 ulChallenge, RTS_UI32 *pulSignature)
{
	return SysTargetGetSignature(ulChallenge,pulSignature);
}

RTS_RESULT CDECL CSysTarget::ISysTargetGetDeviceMask(RTS_UI16 *pusDeviceMask)
{
	return SysTargetGetDeviceMask(pusDeviceMask);
}

RTS_RESULT CDECL CSysTarget::ISysTargetCheckIdent(SysTargetIdent *pTargetIdentReq, SysTargetIdent *pTargetIdent)
{
	return SysTargetCheckIdent(pTargetIdentReq,pTargetIdent);
}

RTS_RESULT CDECL CSysTarget::ISysTargetGetAPI(API_RESOLVE_INFO apiInfo, RTS_VOID_FCTPTR *ppfAPIFunction)
{
	return SysTargetGetAPI(apiInfo,ppfAPIFunction);
}

RTS_RESULT CDECL CSysTarget::ISysTargetSetNodeName(RTS_WCHAR *pwszName)
{
	return SysTargetSetNodeName(pwszName);
}






