/**
 *  <name>Component Template</name>
 *  <description> 
 *  An example on how to implement a component.
 *  This component does no usefull work and it exports no functions
 *  which are intended to be used for anything. Use at your own risk.
 *  </description>
 *  <copyright>
 *  (c) 2003-2016 3S-Smart Software Solutions
 *  </copyright>
 */
SET_COMPONENT_NAME(`IoDrvConFE')
COMPONENT_SOURCES(`IoDrvConFE.c')

COMPONENT_VERSION(`0x0305080A')

/* NOTE: REPLACE 0x0000 BY YOUR VENDORID */
COMPONENT_VENDORID(`0x1688')				

#define CMPID_IoDrvConFE		0x2000		/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CIoDrvConFE	0x2000		/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_IIoDrvConFE		0x2000		/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */

CATEGORY(`Customer')

IMPLEMENT_ITF(`IoDrvConFEItf.m4',`CmpIoDrvItf.m4',`CmpIoDrvParameterItf.m4')

USE_ITF(`CmpIoMgrItf.m4')
USE_ITF(`SysMemItf.m4')
USE_ITF(`SysCpuHandlingItf.m4')

REQUIRED_IMPORTS(
IoMgrRegisterInstance,
IoMgrUnregisterInstance,
IoMgrConfigGetParameter,
IoMgrConfigGetFirstConnector,
IoMgrConfigGetNextConnector,
IoMgrConfigGetFirstChild,
IoMgrConfigGetNextChild,
IoMgrConfigGetParameterValueWord,
IoMgrConfigSetDiagnosis,
IoMgrConfigResetDiagnosis,
IoMgrSetDriverProperties,
IoDrvCreate,
IoDrvDelete,
SysMemAllocData,
SysMemFreeData,
SysCpuTestAndSet,
SysCpuTestAndReset,
IoMgrCopyInputLE,
IoMgrCopyOutputLE)

