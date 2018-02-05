 /**
 * <interfacename>IecVarAccess_Itfs</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _IECVARACCESS_ITFSITF_H_
#define _IECVARACCESS_ITFSITF_H_

#include "CmpStd.h"

 

 




typedef RTS_IEC_HANDLE	IBaseTreeNode;
typedef RTS_IEC_HANDLE	ITypeDesc;

#define AccessRights	ACCESSRIGHTS
#define AR_NONE			ACCESSRIGHTS_AR_NONE
#define AR_READ			ACCESSRIGHTS_AR_READ
#define AR_WRITE		ACCESSRIGHTS_AR_WRITE
#define AR_READWRITE	ACCESSRIGHTS_AR_READWRITE

#define TreeNodeType	TREENODETYPE
#define BranchNode		TREENODETYPE_BRANCHNODE
#define LeafNode		TREENODETYPE_LEAFNODE

/**
* <category>NamespaceNodeFlags macros</category>
* <description>Please use this macros to separate Application, GVL, Program, Variable or
*	ExplicitNamespace nodes (e.g. IsApplicationNode(namespaceNodeFlags) to check if it is an application node).
*  Namespace node flags are retrieved by IecVarAccGetNamespaceNodeFlags().</description>
*/
#define IsApplicationNode(namespaceNodeFlags)	((namespaceNodeFlags & NAMESPACENODEFLAGS_NODETYPEBRANCHNODE) != 0 && \
												 (namespaceNodeFlags & NAMESPACENODEFLAGS_NODETYPELEAFNODE) == 0 && \
												 (namespaceNodeFlags & NAMESPACENODEFLAGS_SIGTYPEGVL) == 0 && \
												 (namespaceNodeFlags & NAMESPACENODEFLAGS_SIGTYPEPROGRAM) == 0 &&	\
												 ((namespaceNodeFlags & NAMESPACENODEFLAGS_BRANCHNODEIMPLICITROOTNODE) != 0 || \
												  (namespaceNodeFlags & NAMESPACENODEFLAGS_BRANCHNODEAPPLICATIONNAME) != 0))

#define IsExplicitNamespaceNode(namespaceNodeFlags)	((namespaceNodeFlags & NAMESPACENODEFLAGS_NODETYPEBRANCHNODE) != 0 && \
												(namespaceNodeFlags & NAMESPACENODEFLAGS_BRANCHNODEEXPLICITNAMESPACE) != 0 && \
												(namespaceNodeFlags & NAMESPACENODEFLAGS_NODETYPELEAFNODE) == 0 && \
												(namespaceNodeFlags & NAMESPACENODEFLAGS_BRANCHNODEIMPLICITROOTNODE) == 0 && \
												(namespaceNodeFlags & NAMESPACENODEFLAGS_BRANCHNODEAPPLICATIONNAME) == 0)

#define IsGVLNode(namespaceNodeFlags)			((namespaceNodeFlags & NAMESPACENODEFLAGS_NODETYPEBRANCHNODE) != 0 && \
												 (namespaceNodeFlags & NAMESPACENODEFLAGS_NODETYPELEAFNODE) == 0 && \
												 (namespaceNodeFlags & NAMESPACENODEFLAGS_SIGTYPEGVL) != 0 && \
												 (namespaceNodeFlags & NAMESPACENODEFLAGS_SIGTYPEPROGRAM) == 0 && \
												 (namespaceNodeFlags & NAMESPACENODEFLAGS_BRANCHNODEIMPLICITROOTNODE) == 0 && \
												 (namespaceNodeFlags & NAMESPACENODEFLAGS_BRANCHNODEAPPLICATIONNAME) == 0)

#define IsProgramNode(namespaceNodeFlags)		((namespaceNodeFlags & NAMESPACENODEFLAGS_NODETYPEBRANCHNODE) != 0 && \
												 (namespaceNodeFlags & NAMESPACENODEFLAGS_NODETYPELEAFNODE) == 0 && \
												 (namespaceNodeFlags & NAMESPACENODEFLAGS_SIGTYPEGVL) == 0 && \
												 (namespaceNodeFlags & NAMESPACENODEFLAGS_SIGTYPEPROGRAM) != 0 && \
												 (namespaceNodeFlags & NAMESPACENODEFLAGS_BRANCHNODEIMPLICITROOTNODE) == 0 && \
												 (namespaceNodeFlags & NAMESPACENODEFLAGS_BRANCHNODEAPPLICATIONNAME) == 0)

#define IsVariableNode(namespaceNodeFlags)		((namespaceNodeFlags & NAMESPACENODEFLAGS_NODETYPEBRANCHNODE) == 0 && \
												 (namespaceNodeFlags & NAMESPACENODEFLAGS_NODETYPELEAFNODE) != 0 && \
												 (namespaceNodeFlags & NAMESPACENODEFLAGS_BRANCHNODEIMPLICITROOTNODE) == 0 && \
												 (namespaceNodeFlags & NAMESPACENODEFLAGS_BRANCHNODEAPPLICATIONNAME) == 0)

/**
* WARNING!
* If you pass this struct to the IecVarAccess or CmpIecVarAccess, it MUST be initialized with
* IIecVarAccess9.VarAccInitVarInfo() or IecVarAccInitVarInfo() before usage, and it MUST be
* cleaned up with IIecVarAccess9.VarAccExitVarInfo() or IecVarAccExitVarInfo(). Weird side
* effects including crashes and memory leaks will result if you do not adhere to this rule.
*/
typedef struct tagVariableInformationStruct3
{
	RTS_IEC_WORD wStructSize;
	RTS_IEC_WORD wFlags;
	RTS_IEC_XWORD dwOffset;
	RTS_IEC_BYTE byBitOffset;
	RTS_IEC_XWORD xwMonitoringOffset;
	RTS_IEC_XWORD xwMonitoringSize;
	RTS_IEC_DWORD dwArrayOfArrayNesting;
	RTS_IEC_HANDLE hBrowseInfo;
	RTS_IEC_BYTE aBrowseInfoPool[28];		/* OBSOLETE: Only for backward compatibility. Not used anymore because data is stored in hBrowseInfo pool. */
} VariableInformationStruct3;

/**
* WARNING!
* If you pass this struct to the IecVarAccess or CmpIecVarAccess, it MUST be initialized with
* IIecVarAccess9.VarAccInitVarInfo() or IecVarAccInitVarInfo() before usage, and it MUST be
* cleaned up with IIecVarAccess9.VarAccExitVarInfo() or IecVarAccExitVarInfo(). Weird side
* effects including crashes and memory leaks will result if you do not adhere to this rule.
*
* The new member wMethodMemberIndex nicely fits into an existing gap within the
* VariableInformationStruct3 struct. Depending on the architecture and global pack mode
* settings, we either have 3 bytes or 7 bytes gap. wMethodMemberIndex uses 2 bytes, thus
* a further byte is available for further use. The resulting struct size, which is also stored
* in the member wStructSize, is unchanged compared to the VariableInformationStruct3 struct.
* This allows us to implement executables without dynamic allocation in the runtime. Access
* is additionally guarded by VIF_EXECUTABLE_MEMBER.
*/
typedef struct tagVariableInformationStruct4
{
	RTS_IEC_WORD wStructSize;
	RTS_IEC_WORD wFlags;
	RTS_IEC_XWORD dwOffset;
	RTS_IEC_BYTE byBitOffset;
	RTS_IEC_WORD wMethodMemberIndex;
	RTS_IEC_XWORD xwMonitoringOffset;
	RTS_IEC_XWORD xwMonitoringSize;
	RTS_IEC_DWORD dwArrayOfArrayNesting;
	RTS_IEC_HANDLE hBrowseInfo;
	RTS_IEC_BYTE aBrowseInfoPool[28];		/* OBSOLETE: Only for backward compatibility. Not used anymore because data is stored in hBrowseInfo pool. */
} VariableInformationStruct4;

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

#ifdef __cplusplus
extern "C" {
#endif

/**
* <description>NamespaceNodeFlagsEx</description>
*/
#define NAMESPACENODEFLAGSEX_EXPORTEDEXECUTABLEVARIABLEFLAG		RTS_IEC_LWORD_C(0x800000000)	/* The variable represents an executable member. */
#define NAMESPACENODEFLAGSEX_EXPORTEDEXECUTABLEVARIABLE		RTS_IEC_LWORD_C(0x800000002)	/* The variable node represents an exported executable variable.. */
#define NAMESPACENODEFLAGSEX_NODEHASEXECUTABLECHILDREN		RTS_IEC_LWORD_C(0x200000000000)	/* This node has executable children. Some interfaces (e. g. PLCHandler) need to take special
precautions for clients which cannot cope with executable children. This flag is mainly for
optimization purposes, as it allows to skip the workarounds on nodes without executable children. */

/**
* <description>VariableInformationFlags</description>
*/
#define VIF_COMPLETE_ACCESS		RTS_IEC_WORD_C(0x1)	/* Complete access to this node, e.g. for array access */
#define VIF_DONT_MODIFY_OFFSET		RTS_IEC_WORD_C(0x2)	/* Internally used for resolving struct members */
#define VIF_BITACCESS		RTS_IEC_WORD_C(0x4)	/* A bit access is requested, e. g. for a direct address like %IX0.0 */
#define VIF_SPLIT_HUGE_VARIABLES		RTS_IEC_WORD_C(0x8)	/* Allow to read/write only a part of the requested variable */
#define VIF_CLIENT_ADDRESS_RESOLUTION		RTS_IEC_WORD_C(0x10)	/* Address/offset/size was resolved by client */
#define VIF_NATIVE_SIZE		RTS_IEC_WORD_C(0x20)	/* VarAccGetSize3() should return native size instead of (client) size */
#define VIF_EXTENDED_INFORMATION		RTS_IEC_WORD_C(0x40)	/* Obsolete, not used anymore */
#define VIF_EXECUTABLE_MEMBER		RTS_IEC_WORD_C(0x80)	/* Member is executable, since V3.5.11.0 */

/**
 * Describing the access rights of a symbol config node.
 * Those members must be in "sync" with the _3S.CoDeSys.SymbolConfigObject.SymbolAccess enum in the AP. Its values
 * must not use more than 8 bit because it's stored in a byte in the SymbolicVarsBase.library.
 */
#define ACCESSRIGHTS_AR_NONE    RTS_IEC_INT_C(0x0)	/* No access permitted. */
#define ACCESSRIGHTS_AR_READ    RTS_IEC_INT_C(0x1)	/* Read access permitted. */
#define ACCESSRIGHTS_AR_WRITE    RTS_IEC_INT_C(0x2)	/* Write access permitted. */
#define ACCESSRIGHTS_AR_READWRITE    RTS_IEC_INT_C(0x3)	/* Read and write access permitted. */
#define ACCESSRIGHTS_AR_EXECUTE    RTS_IEC_INT_C(0x8)	/* Execute access permitted (for methods, programs, functions, fb instances...) */
#define ACCESSRIGHTS_AR_READEXECUTE    RTS_IEC_INT_C(0x9)	/* Combination of read / execute. */
#define ACCESSRIGHTS_AR_WRITEEXECUTE    RTS_IEC_INT_C(0xA)	/* Combination of write / execute. */
#define ACCESSRIGHTS_AR_READWRITEEXECUTE    RTS_IEC_INT_C(0xB)	/* Combination of read / write / execute. */
/* Typed enum definition */
#define ACCESSRIGHTS    RTS_IEC_INT

/**
 * The feature flags describing the contents of the symbol tables files.
 * This enum corresponds to the runtime subset (lower 16 bit) of the enumeration 
 * _3S.CoDeSys.SymbolConfigObject.SymbolConfigContentFeatureFlags which
 * is defined in the SymbolConfigObject interface assembly in the 
 * automation platform, and has to be kept in sync with it.
 * The presence of those flags only indicates that the feature
 * has been enabled in the symbol configuration, it does not 
 * necessarily indicate that there is actually data of that type
 * within the symbol tables (e. G. a user could just have no configured
 * executables, or no comments, or the filter for attributes rejects
 * everything).
 */
#define CONTENTFEATUREFLAGS_NONE    RTS_IEC_INT_C(0x0)	/* Nothing configured. */
#define CONTENTFEATUREFLAGS_SUPPORTOPCUA    RTS_IEC_INT_C(0x1)	/* Support OPC UA features (flag supported since V3.5.8.30).

 This is required for IncludeComments, IncludeAttributes, IncludeTypeNodeAttributes and IncludeExecutables. */
#define CONTENTFEATUREFLAGS_INCLUDECOMMENTS    RTS_IEC_INT_C(0x2)	/* Include comments (flag supported since V3.5.9.0). */
#define CONTENTFEATUREFLAGS_INCLUDEATTRIBUTES    RTS_IEC_INT_C(0x4)	/* Include attributes (flag supported since V3.5.9.0). */
#define CONTENTFEATUREFLAGS_INCLUDETYPENODEATTRIBUTES    RTS_IEC_INT_C(0x8)	/* Also include comments / attributes for type nodes (flag supported since V3.5.9.0). */
#define CONTENTFEATUREFLAGS_INCLUDEEXECUTABLES    RTS_IEC_INT_C(0x10)	/* Inclusion of executable members (flag supported since V3.5.11.0, allows calling of programs, functions, FBs and methods, requires OPC UA support).

 If this flag is set, the list of available signatures may also include callables. */
/* Typed enum definition */
#define CONTENTFEATUREFLAGS    RTS_IEC_INT

/**
 * The node type of a branch node.
 * Several flags may be set concurrently.
 * Not all of the flags defined here are actually generated yet by the code generator.
 * 
 * NOTE : Due to CDS-54976 we could not add new flags here, so they've been moved to NamespaceNodeFlagsEx!
 */
#define NAMESPACENODEFLAGS_NONE    RTS_IEC_LWORD_C(0x0)	/* Uninitialized variable. */
#define NAMESPACENODEFLAGS_NODETYPEMASK    RTS_IEC_LWORD_C(0xFF)	/* The node type mask - 6 Bits for possible node types and flags */
#define NAMESPACENODEFLAGS_NODETYPEBRANCHNODE    RTS_IEC_LWORD_C(0x1)	/* This node is part of the path. It is usually combined with one of the BranchNodeInfo flags below. */
#define NAMESPACENODEFLAGS_NODETYPELEAFNODE    RTS_IEC_LWORD_C(0x2)	/* This node denotes a variable. Combine with the *VariableFlag below. */
#define NAMESPACENODEFLAGS_BRANCHNODEINFOMASK    RTS_IEC_LWORD_C(0xFF00)	/* The bits in this mask define a namespace node not directly corresponding to the POU.

 Apart from the BranchNodeImplicitRootNode flag, a branch node may have
 several of this flags set, for example, when a variable has an explicit namespace
 which equals the application name or library namespace. */
#define NAMESPACENODEFLAGS_BRANCHNODEIMPLICITROOTNODE    RTS_IEC_LWORD_C(0x100)	/* The implicit root node (not user visible except when directly using IecVarAccess)

 In some of the cases when the implicit root node only has a single child,
 it is not exported to the IecVarAccess tables. It is never exported to the XML, as
 the ;NodeList elements represents the root node there. */
#define NAMESPACENODEFLAGS_BRANCHNODEAPPLICATIONNAME    RTS_IEC_LWORD_C(0x200)	/* An application name.

  (May appear on several levels, as apps may be nested.) */
#define NAMESPACENODEFLAGS_BRANCHNODELIBRARYNAMESPACE    RTS_IEC_LWORD_C(0x400)	/* A library namespace.

  (May appear on several levels, as libraries may be nested.) */
#define NAMESPACENODEFLAGS_BRANCHNODEEXPLICITNAMESPACE    RTS_IEC_LWORD_C(0x800)	/* A path component explicitly specified via {attribute 'namespace' := 'foo.bar'} */
#define NAMESPACENODEFLAGS_BRANCHNODEMEMBERACCESS    RTS_IEC_LWORD_C(0x1000)	/* In the future, we might we allow non-top level nodes like foo.bar.baz to 
 be exported directly, probably combined with one of the flags below. */
#define NAMESPACENODEFLAGS_SIGTYPENODEMASK    RTS_IEC_LWORD_C(0xFFFF0000)	/* The bits in this mask define the type of POU which generated the current node.

 A single one of this flags will appear at a variable node telling which kind of signature this
 variable originated from. (Currently not exported to IEC.)

 One or more of this flags will appear at branch nodes which contain variable nodes, declaring
 which kind(s) of signature(s) the contained variables originated from. (Due to namespaces set
 via properties, several variables of different sources may appear belwo the same branch node.) */
#define NAMESPACENODEFLAGS_SIGTYPEGVL    RTS_IEC_LWORD_C(0x10000)	/* A global variable list */
#define NAMESPACENODEFLAGS_SIGTYPEPROGRAM    RTS_IEC_LWORD_C(0x20000)	/* A program */
#define NAMESPACENODEFLAGS_SIGTYPEFB    RTS_IEC_LWORD_C(0x40000)	/* FBs may actually export var_static, and in the future when we allow non-top-level nodes to be exported. */
#define NAMESPACENODEFLAGS_SIGTYPESTRUCT    RTS_IEC_LWORD_C(0x80000)	/* For future extension, when we allow non-top-level nodes to be exported. */
#define NAMESPACENODEFLAGS_SIGTYPEMETHOD    RTS_IEC_LWORD_C(0x100000)	/* For future extension, when we allow non-top-level nodes to be exported. */
#define NAMESPACENODEFLAGS_SIGTYPEACTION    RTS_IEC_LWORD_C(0x200000)	/* For future extension, when we allow non-top-level nodes to be exported. */
#define NAMESPACENODEFLAGS_SIGTYPEPROPERTY    RTS_IEC_LWORD_C(0x400000)	/* For future extension, when we allow non-top-level nodes to be exported. */
#define NAMESPACENODEFLAGS_SIGTYPETRANSITION    RTS_IEC_LWORD_C(0x800000)	/* For future extension, when we allow non-top-level nodes to be exported. */
#define NAMESPACENODEFLAGS_SIGTYPEFUNCTION    RTS_IEC_LWORD_C(0x1000000)	/* Functions may also define static variables which may be exportable. */
#define NAMESPACENODEFLAGS_EXPORTEDVARIABLETYPEMASK    RTS_IEC_LWORD_C(0xFF00000000)	/* Information about the type of the exported variable. */
#define NAMESPACENODEFLAGS_EXPORTEDVARIABLEFLAG    RTS_IEC_LWORD_C(0x100000000)	/* Denotes a "normal" exported variable. */
#define NAMESPACENODEFLAGS_EXPORTEDSTATICVARIABLEFLAG    RTS_IEC_LWORD_C(0x200000000)	/* The variable is a "static" variable which is exported e. G. from an FB which is used in the program. */
#define NAMESPACENODEFLAGS_EXPORTEDPROPERTYVARIABLEFLAG    RTS_IEC_LWORD_C(0x400000000)	/* The variable represents a property. */
#define NAMESPACENODEFLAGS_EXPORTEDVARIABLE    RTS_IEC_ULINT_C(0x100000002)	/* The variable node represents a normal exported variable. */
#define NAMESPACENODEFLAGS_EXPORTEDSTATICVARIABLE    RTS_IEC_ULINT_C(0x200000002)	/* The variable node represents an exported static variable. */
#define NAMESPACENODEFLAGS_EXPORTEDPROPERTYVARIABLE    RTS_IEC_ULINT_C(0x400000002)	/* The variable node represents an exported property with monitoring type 'call'. */
#define NAMESPACENODEFLAGS_NODEFLAGSMASK    RTS_IEC_LWORD_C(0xFF0000000000)	/* The node property flags mask, those bits show some special properties of the nodes. */
#define NAMESPACENODEFLAGS_NODEFLAGHIDDEN    RTS_IEC_LWORD_C(0x100000000000)	/* This node is hidden, it should not be shown while browsing using the IecVarAcces or
 CmpIecVarAccess interfaces. (It can still be found by it's node path, and queried using
 the IBaseTreeNode interfaces.)
 It is not exported to XML.
 As an implementation artifact, hidden nodes currently must always be sorted after the visible nodes.
 This must be guaranteed by naming the nodes accordingly. This is an implementation detail and may change
 in future versions. */
/* Typed enum definition */
#define NAMESPACENODEFLAGS    RTS_IEC_LWORD

/**
 * <description>Enum: TreeNodeType</description>
 */
#define TREENODETYPE_BRANCHNODE    RTS_IEC_INT_C(0x131C)	/* just some value to prevent collisions */
#define TREENODETYPE_LEAFNODE    RTS_IEC_INT_C(0x60D)	/* just some value to prevent collisions */
#define TREENODETYPE_IECVARACCLEAFNODE    RTS_IEC_INT_C(0x225E)	/* just some value to prevent collisions */
#define TREENODETYPE_DATASERVERVARACCLEAFNODE    RTS_IEC_INT_C(0x7C5)	/* just some value to prevent collisions */
/* Typed enum definition */
#define TREENODETYPE    RTS_IEC_INT

/**
 * <description>ArrayDimension</description>
 */
typedef struct tagArrayDimension
{
	RTS_IEC_DINT MinRange;		
	RTS_IEC_DINT MaxRange;		
} ArrayDimension;

/**
 * <description>EnumAttributes</description>
 */
typedef struct tagEnumAttributes
{
	RTS_IEC_WORD nNumOfAttributes;		
	RTS_IEC_STRING* **pAttributes;		
} EnumAttributes;

/**
 * <description>EnumValues</description>
 */
typedef struct tagEnumValues
{
	RTS_IEC_STRING *pValueName;		
	RTS_IEC_LWORD value;		
} EnumValues;

/**
 * <description>TypeDescArrayAsStruct</description>
 */
typedef struct tagTypeDescArrayAsStruct
{
	RTS_IEC_XWORD _dwSize;		
	RTS_IEC_XWORD _dwNativeSize;		
	RTS_IEC_INT _iDimensions;		
	ArrayDimension _Dimension[3];		
	ITypeDesc *_pIBaseTypeDesc;		
} TypeDescArrayAsStruct;

/**
 * <description>TypeDescSimpleAsStruct</description>
 */
typedef struct tagTypeDescSimpleAsStruct
{
	RTS_IEC_XWORD _dwSize;		
	RTS_IEC_XWORD _dwSwapSize;		
} TypeDescSimpleAsStruct;

/**
 * <description>TypeDescStructAsStruct</description>
 */
typedef struct tagTypeDescStructAsStruct
{
	RTS_IEC_XWORD _dwSize;		
	RTS_IEC_XWORD _dwNativeSize;		
	RTS_IEC_DINT _iComponents;		
	IBaseTreeNode **_Components;		
} TypeDescStructAsStruct;

/**
 * <description>TypeDescUnion</description>
 */
typedef union
{
	TypeDescSimpleAsStruct _simple;		
	TypeDescArrayAsStruct _array;		
	TypeDescStructAsStruct _struct;		
} TypeDescUnion;

/**
 * <description>TypeDescAsUnion</description>
 */
typedef struct tagTypeDescAsUnion
{
	RTS_IEC_INT _typeClass;		
	TypeDescUnion _union;		
} TypeDescAsUnion;

/**
 * <description>VariableInformationStruct</description>
 */
typedef struct tagVariableInformationStruct
{
	RTS_IEC_WORD wStructSize;		
	RTS_IEC_WORD wFlags;		
	RTS_IEC_XWORD dwOffset;		
	RTS_IEC_BYTE byBitOffset;		
	RTS_IEC_XWORD xwMonitoringOffset;		
} VariableInformationStruct;

/**
 * <description>VariableInformationStruct2</description>
 */
typedef struct tagVariableInformationStruct2
{
	RTS_IEC_WORD wStructSize;		
	RTS_IEC_WORD wFlags;		
	RTS_IEC_XWORD dwOffset;		
	RTS_IEC_BYTE byBitOffset;		
	RTS_IEC_XWORD xwMonitoringOffset;		
	RTS_IEC_XWORD xwMonitoringSize;		
} VariableInformationStruct2;

typedef struct
{
	void* __VFTABLEPOINTER;	/* Pointer to virtual function table */
} iiecvaraccess10_struct;

/**
 * <description>IIecVarAccess10::VarAccGetNamespaceNodeFlags</description>
 */
typedef struct tagiiecvaraccess10_varaccgetnamespacenodeflags_struct
{
	iiecvaraccess10_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_LWORD VarAccGetNamespaceNodeFlags;	/* VAR_OUTPUT, Enum: NAMESPACENODEFLAGS */
} iiecvaraccess10_varaccgetnamespacenodeflags_struct;

void CDECL VarAccGetNamespaceNodeFlags(iiecvaraccess10_varaccgetnamespacenodeflags_struct *p);
typedef void (CDECL * PFVARACCGETNAMESPACENODEFLAGS) (iiecvaraccess10_varaccgetnamespacenodeflags_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETNAMESPACENODEFLAGS_NOTIMPLEMENTED)
	#define USE_VarAccGetNamespaceNodeFlags
	#define EXT_VarAccGetNamespaceNodeFlags
	#define GET_VarAccGetNamespaceNodeFlags(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetNamespaceNodeFlags(p0)  
	#define CHK_VarAccGetNamespaceNodeFlags  FALSE
	#define EXP_VarAccGetNamespaceNodeFlags  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetNamespaceNodeFlags
	#define EXT_VarAccGetNamespaceNodeFlags
	#define GET_VarAccGetNamespaceNodeFlags(fl)  CAL_CMGETAPI( "VarAccGetNamespaceNodeFlags" ) 
	#define CAL_VarAccGetNamespaceNodeFlags  VarAccGetNamespaceNodeFlags
	#define CHK_VarAccGetNamespaceNodeFlags  TRUE
	#define EXP_VarAccGetNamespaceNodeFlags  CAL_CMEXPAPI( "VarAccGetNamespaceNodeFlags" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetNamespaceNodeFlags
	#define EXT_VarAccGetNamespaceNodeFlags
	#define GET_VarAccGetNamespaceNodeFlags(fl)  CAL_CMGETAPI( "VarAccGetNamespaceNodeFlags" ) 
	#define CAL_VarAccGetNamespaceNodeFlags  VarAccGetNamespaceNodeFlags
	#define CHK_VarAccGetNamespaceNodeFlags  TRUE
	#define EXP_VarAccGetNamespaceNodeFlags  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNamespaceNodeFlags", (RTS_UINTPTR)VarAccGetNamespaceNodeFlags, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetNamespaceNodeFlags
	#define EXT_IecVarAccess_ItfsVarAccGetNamespaceNodeFlags
	#define GET_IecVarAccess_ItfsVarAccGetNamespaceNodeFlags  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetNamespaceNodeFlags pIIecVarAccess_Itfs->IVarAccGetNamespaceNodeFlags
	#define CHK_IecVarAccess_ItfsVarAccGetNamespaceNodeFlags (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetNamespaceNodeFlags  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetNamespaceNodeFlags
	#define EXT_VarAccGetNamespaceNodeFlags
	#define GET_VarAccGetNamespaceNodeFlags(fl)  CAL_CMGETAPI( "VarAccGetNamespaceNodeFlags" ) 
	#define CAL_VarAccGetNamespaceNodeFlags pIIecVarAccess_Itfs->IVarAccGetNamespaceNodeFlags
	#define CHK_VarAccGetNamespaceNodeFlags (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetNamespaceNodeFlags  CAL_CMEXPAPI( "VarAccGetNamespaceNodeFlags" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetNamespaceNodeFlags  PFVARACCGETNAMESPACENODEFLAGS pfVarAccGetNamespaceNodeFlags;
	#define EXT_VarAccGetNamespaceNodeFlags  extern PFVARACCGETNAMESPACENODEFLAGS pfVarAccGetNamespaceNodeFlags;
	#define GET_VarAccGetNamespaceNodeFlags(fl)  s_pfCMGetAPI2( "VarAccGetNamespaceNodeFlags", (RTS_VOID_FCTPTR *)&pfVarAccGetNamespaceNodeFlags, (fl), 0, 0)
	#define CAL_VarAccGetNamespaceNodeFlags  pfVarAccGetNamespaceNodeFlags
	#define CHK_VarAccGetNamespaceNodeFlags  (pfVarAccGetNamespaceNodeFlags != NULL)
	#define EXP_VarAccGetNamespaceNodeFlags  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNamespaceNodeFlags", (RTS_UINTPTR)VarAccGetNamespaceNodeFlags, 0, 0) 
#endif




typedef struct
{
	void* __VFTABLEPOINTER;	/* Pointer to virtual function table */
} iiecvaraccess11_struct;

/**
 * <description>IIecVarAccess11::VarAccExecuteCall</description>
 */
typedef struct tagiiecvaraccess11_varaccexecutecall_struct
{
	iiecvaraccess11_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	VariableInformationStruct *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_BYTE *pArgumentBuffer;		/* VAR_INPUT */	/* buffer where the struct with the arguments is located. */
	RTS_IEC_XWORD nArgumentBufferSize;	/* VAR_INPUT */	/* size of the argument buffer */
	RTS_IEC_RESULT VarAccExecuteCall;	/* VAR_OUTPUT */	
} iiecvaraccess11_varaccexecutecall_struct;

void CDECL VarAccExecuteCall(iiecvaraccess11_varaccexecutecall_struct *p);
typedef void (CDECL * PFVARACCEXECUTECALL) (iiecvaraccess11_varaccexecutecall_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCEXECUTECALL_NOTIMPLEMENTED)
	#define USE_VarAccExecuteCall
	#define EXT_VarAccExecuteCall
	#define GET_VarAccExecuteCall(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccExecuteCall(p0)  
	#define CHK_VarAccExecuteCall  FALSE
	#define EXP_VarAccExecuteCall  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccExecuteCall
	#define EXT_VarAccExecuteCall
	#define GET_VarAccExecuteCall(fl)  CAL_CMGETAPI( "VarAccExecuteCall" ) 
	#define CAL_VarAccExecuteCall  VarAccExecuteCall
	#define CHK_VarAccExecuteCall  TRUE
	#define EXP_VarAccExecuteCall  CAL_CMEXPAPI( "VarAccExecuteCall" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccExecuteCall
	#define EXT_VarAccExecuteCall
	#define GET_VarAccExecuteCall(fl)  CAL_CMGETAPI( "VarAccExecuteCall" ) 
	#define CAL_VarAccExecuteCall  VarAccExecuteCall
	#define CHK_VarAccExecuteCall  TRUE
	#define EXP_VarAccExecuteCall  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccExecuteCall", (RTS_UINTPTR)VarAccExecuteCall, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccExecuteCall
	#define EXT_IecVarAccess_ItfsVarAccExecuteCall
	#define GET_IecVarAccess_ItfsVarAccExecuteCall  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccExecuteCall pIIecVarAccess_Itfs->IVarAccExecuteCall
	#define CHK_IecVarAccess_ItfsVarAccExecuteCall (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccExecuteCall  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccExecuteCall
	#define EXT_VarAccExecuteCall
	#define GET_VarAccExecuteCall(fl)  CAL_CMGETAPI( "VarAccExecuteCall" ) 
	#define CAL_VarAccExecuteCall pIIecVarAccess_Itfs->IVarAccExecuteCall
	#define CHK_VarAccExecuteCall (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccExecuteCall  CAL_CMEXPAPI( "VarAccExecuteCall" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccExecuteCall  PFVARACCEXECUTECALL pfVarAccExecuteCall;
	#define EXT_VarAccExecuteCall  extern PFVARACCEXECUTECALL pfVarAccExecuteCall;
	#define GET_VarAccExecuteCall(fl)  s_pfCMGetAPI2( "VarAccExecuteCall", (RTS_VOID_FCTPTR *)&pfVarAccExecuteCall, (fl), 0, 0)
	#define CAL_VarAccExecuteCall  pfVarAccExecuteCall
	#define CHK_VarAccExecuteCall  (pfVarAccExecuteCall != NULL)
	#define EXP_VarAccExecuteCall  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccExecuteCall", (RTS_UINTPTR)VarAccExecuteCall, 0, 0) 
#endif




/**
 * <description>IIecVarAccess11::VarAccGetEnumMemberAttributeList</description>
 */
typedef struct tagiiecvaraccess11_varaccgetenummemberattributelist_struct
{
	iiecvaraccess11_struct *pInstance;	/* VAR_INPUT */	
	ITypeDesc *typeDesc;				/* VAR_INPUT */	
	RTS_IEC_INT *pnNumOfEnumValues;		/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	EnumAttributes *VarAccGetEnumMemberAttributeList;	/* VAR_OUTPUT */	
} iiecvaraccess11_varaccgetenummemberattributelist_struct;

void CDECL VarAccGetEnumMemberAttributeList(iiecvaraccess11_varaccgetenummemberattributelist_struct *p);
typedef void (CDECL * PFVARACCGETENUMMEMBERATTRIBUTELIST) (iiecvaraccess11_varaccgetenummemberattributelist_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETENUMMEMBERATTRIBUTELIST_NOTIMPLEMENTED)
	#define USE_VarAccGetEnumMemberAttributeList
	#define EXT_VarAccGetEnumMemberAttributeList
	#define GET_VarAccGetEnumMemberAttributeList(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetEnumMemberAttributeList(p0)  
	#define CHK_VarAccGetEnumMemberAttributeList  FALSE
	#define EXP_VarAccGetEnumMemberAttributeList  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetEnumMemberAttributeList
	#define EXT_VarAccGetEnumMemberAttributeList
	#define GET_VarAccGetEnumMemberAttributeList(fl)  CAL_CMGETAPI( "VarAccGetEnumMemberAttributeList" ) 
	#define CAL_VarAccGetEnumMemberAttributeList  VarAccGetEnumMemberAttributeList
	#define CHK_VarAccGetEnumMemberAttributeList  TRUE
	#define EXP_VarAccGetEnumMemberAttributeList  CAL_CMEXPAPI( "VarAccGetEnumMemberAttributeList" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetEnumMemberAttributeList
	#define EXT_VarAccGetEnumMemberAttributeList
	#define GET_VarAccGetEnumMemberAttributeList(fl)  CAL_CMGETAPI( "VarAccGetEnumMemberAttributeList" ) 
	#define CAL_VarAccGetEnumMemberAttributeList  VarAccGetEnumMemberAttributeList
	#define CHK_VarAccGetEnumMemberAttributeList  TRUE
	#define EXP_VarAccGetEnumMemberAttributeList  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetEnumMemberAttributeList", (RTS_UINTPTR)VarAccGetEnumMemberAttributeList, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetEnumMemberAttributeList
	#define EXT_IecVarAccess_ItfsVarAccGetEnumMemberAttributeList
	#define GET_IecVarAccess_ItfsVarAccGetEnumMemberAttributeList  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetEnumMemberAttributeList pIIecVarAccess_Itfs->IVarAccGetEnumMemberAttributeList
	#define CHK_IecVarAccess_ItfsVarAccGetEnumMemberAttributeList (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetEnumMemberAttributeList  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetEnumMemberAttributeList
	#define EXT_VarAccGetEnumMemberAttributeList
	#define GET_VarAccGetEnumMemberAttributeList(fl)  CAL_CMGETAPI( "VarAccGetEnumMemberAttributeList" ) 
	#define CAL_VarAccGetEnumMemberAttributeList pIIecVarAccess_Itfs->IVarAccGetEnumMemberAttributeList
	#define CHK_VarAccGetEnumMemberAttributeList (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetEnumMemberAttributeList  CAL_CMEXPAPI( "VarAccGetEnumMemberAttributeList" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetEnumMemberAttributeList  PFVARACCGETENUMMEMBERATTRIBUTELIST pfVarAccGetEnumMemberAttributeList;
	#define EXT_VarAccGetEnumMemberAttributeList  extern PFVARACCGETENUMMEMBERATTRIBUTELIST pfVarAccGetEnumMemberAttributeList;
	#define GET_VarAccGetEnumMemberAttributeList(fl)  s_pfCMGetAPI2( "VarAccGetEnumMemberAttributeList", (RTS_VOID_FCTPTR *)&pfVarAccGetEnumMemberAttributeList, (fl), 0, 0)
	#define CAL_VarAccGetEnumMemberAttributeList  pfVarAccGetEnumMemberAttributeList
	#define CHK_VarAccGetEnumMemberAttributeList  (pfVarAccGetEnumMemberAttributeList != NULL)
	#define EXP_VarAccGetEnumMemberAttributeList  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetEnumMemberAttributeList", (RTS_UINTPTR)VarAccGetEnumMemberAttributeList, 0, 0) 
#endif




/**
 * <description>IIecVarAccess11::VarAccGetNumOfTypeAttributes</description>
 */
typedef struct tagiiecvaraccess11_varaccgetnumoftypeattributes_struct
{
	iiecvaraccess11_struct *pInstance;	/* VAR_INPUT */	
	ITypeDesc *typeDesc;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_WORD VarAccGetNumOfTypeAttributes;	/* VAR_OUTPUT */	
} iiecvaraccess11_varaccgetnumoftypeattributes_struct;

void CDECL VarAccGetNumOfTypeAttributes(iiecvaraccess11_varaccgetnumoftypeattributes_struct *p);
typedef void (CDECL * PFVARACCGETNUMOFTYPEATTRIBUTES) (iiecvaraccess11_varaccgetnumoftypeattributes_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETNUMOFTYPEATTRIBUTES_NOTIMPLEMENTED)
	#define USE_VarAccGetNumOfTypeAttributes
	#define EXT_VarAccGetNumOfTypeAttributes
	#define GET_VarAccGetNumOfTypeAttributes(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetNumOfTypeAttributes(p0)  
	#define CHK_VarAccGetNumOfTypeAttributes  FALSE
	#define EXP_VarAccGetNumOfTypeAttributes  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetNumOfTypeAttributes
	#define EXT_VarAccGetNumOfTypeAttributes
	#define GET_VarAccGetNumOfTypeAttributes(fl)  CAL_CMGETAPI( "VarAccGetNumOfTypeAttributes" ) 
	#define CAL_VarAccGetNumOfTypeAttributes  VarAccGetNumOfTypeAttributes
	#define CHK_VarAccGetNumOfTypeAttributes  TRUE
	#define EXP_VarAccGetNumOfTypeAttributes  CAL_CMEXPAPI( "VarAccGetNumOfTypeAttributes" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetNumOfTypeAttributes
	#define EXT_VarAccGetNumOfTypeAttributes
	#define GET_VarAccGetNumOfTypeAttributes(fl)  CAL_CMGETAPI( "VarAccGetNumOfTypeAttributes" ) 
	#define CAL_VarAccGetNumOfTypeAttributes  VarAccGetNumOfTypeAttributes
	#define CHK_VarAccGetNumOfTypeAttributes  TRUE
	#define EXP_VarAccGetNumOfTypeAttributes  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNumOfTypeAttributes", (RTS_UINTPTR)VarAccGetNumOfTypeAttributes, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetNumOfTypeAttributes
	#define EXT_IecVarAccess_ItfsVarAccGetNumOfTypeAttributes
	#define GET_IecVarAccess_ItfsVarAccGetNumOfTypeAttributes  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetNumOfTypeAttributes pIIecVarAccess_Itfs->IVarAccGetNumOfTypeAttributes
	#define CHK_IecVarAccess_ItfsVarAccGetNumOfTypeAttributes (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetNumOfTypeAttributes  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetNumOfTypeAttributes
	#define EXT_VarAccGetNumOfTypeAttributes
	#define GET_VarAccGetNumOfTypeAttributes(fl)  CAL_CMGETAPI( "VarAccGetNumOfTypeAttributes" ) 
	#define CAL_VarAccGetNumOfTypeAttributes pIIecVarAccess_Itfs->IVarAccGetNumOfTypeAttributes
	#define CHK_VarAccGetNumOfTypeAttributes (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetNumOfTypeAttributes  CAL_CMEXPAPI( "VarAccGetNumOfTypeAttributes" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetNumOfTypeAttributes  PFVARACCGETNUMOFTYPEATTRIBUTES pfVarAccGetNumOfTypeAttributes;
	#define EXT_VarAccGetNumOfTypeAttributes  extern PFVARACCGETNUMOFTYPEATTRIBUTES pfVarAccGetNumOfTypeAttributes;
	#define GET_VarAccGetNumOfTypeAttributes(fl)  s_pfCMGetAPI2( "VarAccGetNumOfTypeAttributes", (RTS_VOID_FCTPTR *)&pfVarAccGetNumOfTypeAttributes, (fl), 0, 0)
	#define CAL_VarAccGetNumOfTypeAttributes  pfVarAccGetNumOfTypeAttributes
	#define CHK_VarAccGetNumOfTypeAttributes  (pfVarAccGetNumOfTypeAttributes != NULL)
	#define EXP_VarAccGetNumOfTypeAttributes  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNumOfTypeAttributes", (RTS_UINTPTR)VarAccGetNumOfTypeAttributes, 0, 0) 
#endif




/**
 * <description>IIecVarAccess11::VarAccGetTypeAttributeByIndex</description>
 */
typedef struct tagiiecvaraccess11_varaccgettypeattributebyindex_struct
{
	iiecvaraccess11_struct *pInstance;	/* VAR_INPUT */	
	ITypeDesc *typeDesc;				/* VAR_INPUT */	
	RTS_IEC_WORD wIndex;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_STRING *VarAccGetTypeAttributeByIndex;	/* VAR_OUTPUT */	
} iiecvaraccess11_varaccgettypeattributebyindex_struct;

void CDECL VarAccGetTypeAttributeByIndex(iiecvaraccess11_varaccgettypeattributebyindex_struct *p);
typedef void (CDECL * PFVARACCGETTYPEATTRIBUTEBYINDEX) (iiecvaraccess11_varaccgettypeattributebyindex_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETTYPEATTRIBUTEBYINDEX_NOTIMPLEMENTED)
	#define USE_VarAccGetTypeAttributeByIndex
	#define EXT_VarAccGetTypeAttributeByIndex
	#define GET_VarAccGetTypeAttributeByIndex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetTypeAttributeByIndex(p0)  
	#define CHK_VarAccGetTypeAttributeByIndex  FALSE
	#define EXP_VarAccGetTypeAttributeByIndex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetTypeAttributeByIndex
	#define EXT_VarAccGetTypeAttributeByIndex
	#define GET_VarAccGetTypeAttributeByIndex(fl)  CAL_CMGETAPI( "VarAccGetTypeAttributeByIndex" ) 
	#define CAL_VarAccGetTypeAttributeByIndex  VarAccGetTypeAttributeByIndex
	#define CHK_VarAccGetTypeAttributeByIndex  TRUE
	#define EXP_VarAccGetTypeAttributeByIndex  CAL_CMEXPAPI( "VarAccGetTypeAttributeByIndex" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetTypeAttributeByIndex
	#define EXT_VarAccGetTypeAttributeByIndex
	#define GET_VarAccGetTypeAttributeByIndex(fl)  CAL_CMGETAPI( "VarAccGetTypeAttributeByIndex" ) 
	#define CAL_VarAccGetTypeAttributeByIndex  VarAccGetTypeAttributeByIndex
	#define CHK_VarAccGetTypeAttributeByIndex  TRUE
	#define EXP_VarAccGetTypeAttributeByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetTypeAttributeByIndex", (RTS_UINTPTR)VarAccGetTypeAttributeByIndex, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetTypeAttributeByIndex
	#define EXT_IecVarAccess_ItfsVarAccGetTypeAttributeByIndex
	#define GET_IecVarAccess_ItfsVarAccGetTypeAttributeByIndex  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetTypeAttributeByIndex pIIecVarAccess_Itfs->IVarAccGetTypeAttributeByIndex
	#define CHK_IecVarAccess_ItfsVarAccGetTypeAttributeByIndex (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetTypeAttributeByIndex  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetTypeAttributeByIndex
	#define EXT_VarAccGetTypeAttributeByIndex
	#define GET_VarAccGetTypeAttributeByIndex(fl)  CAL_CMGETAPI( "VarAccGetTypeAttributeByIndex" ) 
	#define CAL_VarAccGetTypeAttributeByIndex pIIecVarAccess_Itfs->IVarAccGetTypeAttributeByIndex
	#define CHK_VarAccGetTypeAttributeByIndex (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetTypeAttributeByIndex  CAL_CMEXPAPI( "VarAccGetTypeAttributeByIndex" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetTypeAttributeByIndex  PFVARACCGETTYPEATTRIBUTEBYINDEX pfVarAccGetTypeAttributeByIndex;
	#define EXT_VarAccGetTypeAttributeByIndex  extern PFVARACCGETTYPEATTRIBUTEBYINDEX pfVarAccGetTypeAttributeByIndex;
	#define GET_VarAccGetTypeAttributeByIndex(fl)  s_pfCMGetAPI2( "VarAccGetTypeAttributeByIndex", (RTS_VOID_FCTPTR *)&pfVarAccGetTypeAttributeByIndex, (fl), 0, 0)
	#define CAL_VarAccGetTypeAttributeByIndex  pfVarAccGetTypeAttributeByIndex
	#define CHK_VarAccGetTypeAttributeByIndex  (pfVarAccGetTypeAttributeByIndex != NULL)
	#define EXP_VarAccGetTypeAttributeByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetTypeAttributeByIndex", (RTS_UINTPTR)VarAccGetTypeAttributeByIndex, 0, 0) 
#endif




typedef struct
{
	void* __VFTABLEPOINTER;	/* Pointer to virtual function table */
} iiecvaraccess12_struct;

/**
 * Gets the content feature flags.
 * Return values:
 * - ERR_OK -> if pContentFeatureFlags is not 0, it will be set to the feature flags.
 * - ERR_NOTINITIALIZED -> The code generator did not set the flag value.
 */
typedef struct tagiiecvaraccess12_varaccgetcontentfeatureflags_struct
{
	iiecvaraccess12_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_INT *pContentFeatureFlags;	/* VAR_INPUT */	/* Pointer to the destination variable. May be 0 to just query whether the flags are set or not. */
	RTS_IEC_RESULT VarAccGetContentFeatureFlags;	/* VAR_OUTPUT */	
} iiecvaraccess12_varaccgetcontentfeatureflags_struct;

void CDECL VarAccGetContentFeatureFlags(iiecvaraccess12_varaccgetcontentfeatureflags_struct *p);
typedef void (CDECL * PFVARACCGETCONTENTFEATUREFLAGS) (iiecvaraccess12_varaccgetcontentfeatureflags_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETCONTENTFEATUREFLAGS_NOTIMPLEMENTED)
	#define USE_VarAccGetContentFeatureFlags
	#define EXT_VarAccGetContentFeatureFlags
	#define GET_VarAccGetContentFeatureFlags(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetContentFeatureFlags(p0)  
	#define CHK_VarAccGetContentFeatureFlags  FALSE
	#define EXP_VarAccGetContentFeatureFlags  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetContentFeatureFlags
	#define EXT_VarAccGetContentFeatureFlags
	#define GET_VarAccGetContentFeatureFlags(fl)  CAL_CMGETAPI( "VarAccGetContentFeatureFlags" ) 
	#define CAL_VarAccGetContentFeatureFlags  VarAccGetContentFeatureFlags
	#define CHK_VarAccGetContentFeatureFlags  TRUE
	#define EXP_VarAccGetContentFeatureFlags  CAL_CMEXPAPI( "VarAccGetContentFeatureFlags" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetContentFeatureFlags
	#define EXT_VarAccGetContentFeatureFlags
	#define GET_VarAccGetContentFeatureFlags(fl)  CAL_CMGETAPI( "VarAccGetContentFeatureFlags" ) 
	#define CAL_VarAccGetContentFeatureFlags  VarAccGetContentFeatureFlags
	#define CHK_VarAccGetContentFeatureFlags  TRUE
	#define EXP_VarAccGetContentFeatureFlags  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetContentFeatureFlags", (RTS_UINTPTR)VarAccGetContentFeatureFlags, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetContentFeatureFlags
	#define EXT_IecVarAccess_ItfsVarAccGetContentFeatureFlags
	#define GET_IecVarAccess_ItfsVarAccGetContentFeatureFlags  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetContentFeatureFlags pIIecVarAccess_Itfs->IVarAccGetContentFeatureFlags
	#define CHK_IecVarAccess_ItfsVarAccGetContentFeatureFlags (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetContentFeatureFlags  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetContentFeatureFlags
	#define EXT_VarAccGetContentFeatureFlags
	#define GET_VarAccGetContentFeatureFlags(fl)  CAL_CMGETAPI( "VarAccGetContentFeatureFlags" ) 
	#define CAL_VarAccGetContentFeatureFlags pIIecVarAccess_Itfs->IVarAccGetContentFeatureFlags
	#define CHK_VarAccGetContentFeatureFlags (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetContentFeatureFlags  CAL_CMEXPAPI( "VarAccGetContentFeatureFlags" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetContentFeatureFlags  PFVARACCGETCONTENTFEATUREFLAGS pfVarAccGetContentFeatureFlags;
	#define EXT_VarAccGetContentFeatureFlags  extern PFVARACCGETCONTENTFEATUREFLAGS pfVarAccGetContentFeatureFlags;
	#define GET_VarAccGetContentFeatureFlags(fl)  s_pfCMGetAPI2( "VarAccGetContentFeatureFlags", (RTS_VOID_FCTPTR *)&pfVarAccGetContentFeatureFlags, (fl), 0, 0)
	#define CAL_VarAccGetContentFeatureFlags  pfVarAccGetContentFeatureFlags
	#define CHK_VarAccGetContentFeatureFlags  (pfVarAccGetContentFeatureFlags != NULL)
	#define EXP_VarAccGetContentFeatureFlags  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetContentFeatureFlags", (RTS_UINTPTR)VarAccGetContentFeatureFlags, 0, 0) 
#endif




/**
 * <description>IIecVarAccess12::VarAccGetRange</description>
 */
typedef struct tagiiecvaraccess12_varaccgetrange_struct
{
	iiecvaraccess12_struct *pInstance;	/* VAR_INPUT */	
	ITypeDesc *typeDesc;				/* VAR_INPUT */	
	RTS_IEC_LWORD *pLower;				/* VAR_INPUT */	
	RTS_IEC_LWORD *pUpper;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_BOOL VarAccGetRange;		/* VAR_OUTPUT */	
} iiecvaraccess12_varaccgetrange_struct;

void CDECL VarAccGetRange(iiecvaraccess12_varaccgetrange_struct *p);
typedef void (CDECL * PFVARACCGETRANGE) (iiecvaraccess12_varaccgetrange_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETRANGE_NOTIMPLEMENTED)
	#define USE_VarAccGetRange
	#define EXT_VarAccGetRange
	#define GET_VarAccGetRange(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetRange(p0)  
	#define CHK_VarAccGetRange  FALSE
	#define EXP_VarAccGetRange  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetRange
	#define EXT_VarAccGetRange
	#define GET_VarAccGetRange(fl)  CAL_CMGETAPI( "VarAccGetRange" ) 
	#define CAL_VarAccGetRange  VarAccGetRange
	#define CHK_VarAccGetRange  TRUE
	#define EXP_VarAccGetRange  CAL_CMEXPAPI( "VarAccGetRange" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetRange
	#define EXT_VarAccGetRange
	#define GET_VarAccGetRange(fl)  CAL_CMGETAPI( "VarAccGetRange" ) 
	#define CAL_VarAccGetRange  VarAccGetRange
	#define CHK_VarAccGetRange  TRUE
	#define EXP_VarAccGetRange  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetRange", (RTS_UINTPTR)VarAccGetRange, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetRange
	#define EXT_IecVarAccess_ItfsVarAccGetRange
	#define GET_IecVarAccess_ItfsVarAccGetRange  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetRange pIIecVarAccess_Itfs->IVarAccGetRange
	#define CHK_IecVarAccess_ItfsVarAccGetRange (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetRange  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetRange
	#define EXT_VarAccGetRange
	#define GET_VarAccGetRange(fl)  CAL_CMGETAPI( "VarAccGetRange" ) 
	#define CAL_VarAccGetRange pIIecVarAccess_Itfs->IVarAccGetRange
	#define CHK_VarAccGetRange (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetRange  CAL_CMEXPAPI( "VarAccGetRange" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetRange  PFVARACCGETRANGE pfVarAccGetRange;
	#define EXT_VarAccGetRange  extern PFVARACCGETRANGE pfVarAccGetRange;
	#define GET_VarAccGetRange(fl)  s_pfCMGetAPI2( "VarAccGetRange", (RTS_VOID_FCTPTR *)&pfVarAccGetRange, (fl), 0, 0)
	#define CAL_VarAccGetRange  pfVarAccGetRange
	#define CHK_VarAccGetRange  (pfVarAccGetRange != NULL)
	#define EXP_VarAccGetRange  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetRange", (RTS_UINTPTR)VarAccGetRange, 0, 0) 
#endif




typedef struct
{
	void* __VFTABLEPOINTER;	/* Pointer to virtual function table */
} iiecvaraccess4_struct;

/**
 * <description>IIecVarAccess4::VarAccGetSwapSize</description>
 */
typedef struct tagiiecvaraccess4_varaccgetswapsize_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_XWORD VarAccGetSwapSize;	/* VAR_OUTPUT */	
} iiecvaraccess4_varaccgetswapsize_struct;

void CDECL VarAccGetSwapSize(iiecvaraccess4_varaccgetswapsize_struct *p);
typedef void (CDECL * PFVARACCGETSWAPSIZE) (iiecvaraccess4_varaccgetswapsize_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETSWAPSIZE_NOTIMPLEMENTED)
	#define USE_VarAccGetSwapSize
	#define EXT_VarAccGetSwapSize
	#define GET_VarAccGetSwapSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetSwapSize(p0)  
	#define CHK_VarAccGetSwapSize  FALSE
	#define EXP_VarAccGetSwapSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetSwapSize
	#define EXT_VarAccGetSwapSize
	#define GET_VarAccGetSwapSize(fl)  CAL_CMGETAPI( "VarAccGetSwapSize" ) 
	#define CAL_VarAccGetSwapSize  VarAccGetSwapSize
	#define CHK_VarAccGetSwapSize  TRUE
	#define EXP_VarAccGetSwapSize  CAL_CMEXPAPI( "VarAccGetSwapSize" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetSwapSize
	#define EXT_VarAccGetSwapSize
	#define GET_VarAccGetSwapSize(fl)  CAL_CMGETAPI( "VarAccGetSwapSize" ) 
	#define CAL_VarAccGetSwapSize  VarAccGetSwapSize
	#define CHK_VarAccGetSwapSize  TRUE
	#define EXP_VarAccGetSwapSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetSwapSize", (RTS_UINTPTR)VarAccGetSwapSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetSwapSize
	#define EXT_IecVarAccess_ItfsVarAccGetSwapSize
	#define GET_IecVarAccess_ItfsVarAccGetSwapSize  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetSwapSize pIIecVarAccess_Itfs->IVarAccGetSwapSize
	#define CHK_IecVarAccess_ItfsVarAccGetSwapSize (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetSwapSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetSwapSize
	#define EXT_VarAccGetSwapSize
	#define GET_VarAccGetSwapSize(fl)  CAL_CMGETAPI( "VarAccGetSwapSize" ) 
	#define CAL_VarAccGetSwapSize pIIecVarAccess_Itfs->IVarAccGetSwapSize
	#define CHK_VarAccGetSwapSize (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetSwapSize  CAL_CMEXPAPI( "VarAccGetSwapSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetSwapSize  PFVARACCGETSWAPSIZE pfVarAccGetSwapSize;
	#define EXT_VarAccGetSwapSize  extern PFVARACCGETSWAPSIZE pfVarAccGetSwapSize;
	#define GET_VarAccGetSwapSize(fl)  s_pfCMGetAPI2( "VarAccGetSwapSize", (RTS_VOID_FCTPTR *)&pfVarAccGetSwapSize, (fl), 0, 0)
	#define CAL_VarAccGetSwapSize  pfVarAccGetSwapSize
	#define CHK_VarAccGetSwapSize  (pfVarAccGetSwapSize != NULL)
	#define EXP_VarAccGetSwapSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetSwapSize", (RTS_UINTPTR)VarAccGetSwapSize, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccEndVariableConfiguration</description>
 */
typedef struct tagiiecvaraccess4_varaccendvariableconfiguration_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_UDINT VarAccEndVariableConfiguration;	/* VAR_OUTPUT */	
} iiecvaraccess4_varaccendvariableconfiguration_struct;

void CDECL VarAccEndVariableConfiguration(iiecvaraccess4_varaccendvariableconfiguration_struct *p);
typedef void (CDECL * PFVARACCENDVARIABLECONFIGURATION) (iiecvaraccess4_varaccendvariableconfiguration_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCENDVARIABLECONFIGURATION_NOTIMPLEMENTED)
	#define USE_VarAccEndVariableConfiguration
	#define EXT_VarAccEndVariableConfiguration
	#define GET_VarAccEndVariableConfiguration(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccEndVariableConfiguration(p0)  
	#define CHK_VarAccEndVariableConfiguration  FALSE
	#define EXP_VarAccEndVariableConfiguration  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccEndVariableConfiguration
	#define EXT_VarAccEndVariableConfiguration
	#define GET_VarAccEndVariableConfiguration(fl)  CAL_CMGETAPI( "VarAccEndVariableConfiguration" ) 
	#define CAL_VarAccEndVariableConfiguration  VarAccEndVariableConfiguration
	#define CHK_VarAccEndVariableConfiguration  TRUE
	#define EXP_VarAccEndVariableConfiguration  CAL_CMEXPAPI( "VarAccEndVariableConfiguration" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccEndVariableConfiguration
	#define EXT_VarAccEndVariableConfiguration
	#define GET_VarAccEndVariableConfiguration(fl)  CAL_CMGETAPI( "VarAccEndVariableConfiguration" ) 
	#define CAL_VarAccEndVariableConfiguration  VarAccEndVariableConfiguration
	#define CHK_VarAccEndVariableConfiguration  TRUE
	#define EXP_VarAccEndVariableConfiguration  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccEndVariableConfiguration", (RTS_UINTPTR)VarAccEndVariableConfiguration, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccEndVariableConfiguration
	#define EXT_IecVarAccess_ItfsVarAccEndVariableConfiguration
	#define GET_IecVarAccess_ItfsVarAccEndVariableConfiguration  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccEndVariableConfiguration pIIecVarAccess_Itfs->IVarAccEndVariableConfiguration
	#define CHK_IecVarAccess_ItfsVarAccEndVariableConfiguration (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccEndVariableConfiguration  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccEndVariableConfiguration
	#define EXT_VarAccEndVariableConfiguration
	#define GET_VarAccEndVariableConfiguration(fl)  CAL_CMGETAPI( "VarAccEndVariableConfiguration" ) 
	#define CAL_VarAccEndVariableConfiguration pIIecVarAccess_Itfs->IVarAccEndVariableConfiguration
	#define CHK_VarAccEndVariableConfiguration (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccEndVariableConfiguration  CAL_CMEXPAPI( "VarAccEndVariableConfiguration" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccEndVariableConfiguration  PFVARACCENDVARIABLECONFIGURATION pfVarAccEndVariableConfiguration;
	#define EXT_VarAccEndVariableConfiguration  extern PFVARACCENDVARIABLECONFIGURATION pfVarAccEndVariableConfiguration;
	#define GET_VarAccEndVariableConfiguration(fl)  s_pfCMGetAPI2( "VarAccEndVariableConfiguration", (RTS_VOID_FCTPTR *)&pfVarAccEndVariableConfiguration, (fl), 0, 0)
	#define CAL_VarAccEndVariableConfiguration  pfVarAccEndVariableConfiguration
	#define CHK_VarAccEndVariableConfiguration  (pfVarAccEndVariableConfiguration != NULL)
	#define EXP_VarAccEndVariableConfiguration  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccEndVariableConfiguration", (RTS_UINTPTR)VarAccEndVariableConfiguration, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccSwap</description>
 */
typedef struct tagiiecvaraccess4_varaccswap_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	RTS_IEC_XWORD dwSize;				/* VAR_INPUT */	
	RTS_IEC_BOOL bMotorola;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_XWORD VarAccSwap;			/* VAR_OUTPUT */	
} iiecvaraccess4_varaccswap_struct;

void CDECL VarAccSwap(iiecvaraccess4_varaccswap_struct *p);
typedef void (CDECL * PFVARACCSWAP) (iiecvaraccess4_varaccswap_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCSWAP_NOTIMPLEMENTED)
	#define USE_VarAccSwap
	#define EXT_VarAccSwap
	#define GET_VarAccSwap(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccSwap(p0)  
	#define CHK_VarAccSwap  FALSE
	#define EXP_VarAccSwap  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccSwap
	#define EXT_VarAccSwap
	#define GET_VarAccSwap(fl)  CAL_CMGETAPI( "VarAccSwap" ) 
	#define CAL_VarAccSwap  VarAccSwap
	#define CHK_VarAccSwap  TRUE
	#define EXP_VarAccSwap  CAL_CMEXPAPI( "VarAccSwap" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccSwap
	#define EXT_VarAccSwap
	#define GET_VarAccSwap(fl)  CAL_CMGETAPI( "VarAccSwap" ) 
	#define CAL_VarAccSwap  VarAccSwap
	#define CHK_VarAccSwap  TRUE
	#define EXP_VarAccSwap  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccSwap", (RTS_UINTPTR)VarAccSwap, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccSwap
	#define EXT_IecVarAccess_ItfsVarAccSwap
	#define GET_IecVarAccess_ItfsVarAccSwap  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccSwap pIIecVarAccess_Itfs->IVarAccSwap
	#define CHK_IecVarAccess_ItfsVarAccSwap (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccSwap  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccSwap
	#define EXT_VarAccSwap
	#define GET_VarAccSwap(fl)  CAL_CMGETAPI( "VarAccSwap" ) 
	#define CAL_VarAccSwap pIIecVarAccess_Itfs->IVarAccSwap
	#define CHK_VarAccSwap (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccSwap  CAL_CMEXPAPI( "VarAccSwap" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccSwap  PFVARACCSWAP pfVarAccSwap;
	#define EXT_VarAccSwap  extern PFVARACCSWAP pfVarAccSwap;
	#define GET_VarAccSwap(fl)  s_pfCMGetAPI2( "VarAccSwap", (RTS_VOID_FCTPTR *)&pfVarAccSwap, (fl), 0, 0)
	#define CAL_VarAccSwap  pfVarAccSwap
	#define CHK_VarAccSwap  (pfVarAccSwap != NULL)
	#define EXP_VarAccSwap  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccSwap", (RTS_UINTPTR)VarAccSwap, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccRemoveVariable</description>
 */
typedef struct tagiiecvaraccess4_varaccremovevariable_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_UDINT VarAccRemoveVariable;	/* VAR_OUTPUT */	
} iiecvaraccess4_varaccremovevariable_struct;

void CDECL VarAccRemoveVariable(iiecvaraccess4_varaccremovevariable_struct *p);
typedef void (CDECL * PFVARACCREMOVEVARIABLE) (iiecvaraccess4_varaccremovevariable_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCREMOVEVARIABLE_NOTIMPLEMENTED)
	#define USE_VarAccRemoveVariable
	#define EXT_VarAccRemoveVariable
	#define GET_VarAccRemoveVariable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccRemoveVariable(p0)  
	#define CHK_VarAccRemoveVariable  FALSE
	#define EXP_VarAccRemoveVariable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccRemoveVariable
	#define EXT_VarAccRemoveVariable
	#define GET_VarAccRemoveVariable(fl)  CAL_CMGETAPI( "VarAccRemoveVariable" ) 
	#define CAL_VarAccRemoveVariable  VarAccRemoveVariable
	#define CHK_VarAccRemoveVariable  TRUE
	#define EXP_VarAccRemoveVariable  CAL_CMEXPAPI( "VarAccRemoveVariable" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccRemoveVariable
	#define EXT_VarAccRemoveVariable
	#define GET_VarAccRemoveVariable(fl)  CAL_CMGETAPI( "VarAccRemoveVariable" ) 
	#define CAL_VarAccRemoveVariable  VarAccRemoveVariable
	#define CHK_VarAccRemoveVariable  TRUE
	#define EXP_VarAccRemoveVariable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccRemoveVariable", (RTS_UINTPTR)VarAccRemoveVariable, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccRemoveVariable
	#define EXT_IecVarAccess_ItfsVarAccRemoveVariable
	#define GET_IecVarAccess_ItfsVarAccRemoveVariable  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccRemoveVariable pIIecVarAccess_Itfs->IVarAccRemoveVariable
	#define CHK_IecVarAccess_ItfsVarAccRemoveVariable (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccRemoveVariable  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccRemoveVariable
	#define EXT_VarAccRemoveVariable
	#define GET_VarAccRemoveVariable(fl)  CAL_CMGETAPI( "VarAccRemoveVariable" ) 
	#define CAL_VarAccRemoveVariable pIIecVarAccess_Itfs->IVarAccRemoveVariable
	#define CHK_VarAccRemoveVariable (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccRemoveVariable  CAL_CMEXPAPI( "VarAccRemoveVariable" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccRemoveVariable  PFVARACCREMOVEVARIABLE pfVarAccRemoveVariable;
	#define EXT_VarAccRemoveVariable  extern PFVARACCREMOVEVARIABLE pfVarAccRemoveVariable;
	#define GET_VarAccRemoveVariable(fl)  s_pfCMGetAPI2( "VarAccRemoveVariable", (RTS_VOID_FCTPTR *)&pfVarAccRemoveVariable, (fl), 0, 0)
	#define CAL_VarAccRemoveVariable  pfVarAccRemoveVariable
	#define CHK_VarAccRemoveVariable  (pfVarAccRemoveVariable != NULL)
	#define EXP_VarAccRemoveVariable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccRemoveVariable", (RTS_UINTPTR)VarAccRemoveVariable, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccBrowseGetRoot</description>
 */
typedef struct tagiiecvaraccess4_varaccbrowsegetroot_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	IBaseTreeNode *VarAccBrowseGetRoot;	/* VAR_OUTPUT */	
} iiecvaraccess4_varaccbrowsegetroot_struct;

void CDECL VarAccBrowseGetRoot(iiecvaraccess4_varaccbrowsegetroot_struct *p);
typedef void (CDECL * PFVARACCBROWSEGETROOT) (iiecvaraccess4_varaccbrowsegetroot_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCBROWSEGETROOT_NOTIMPLEMENTED)
	#define USE_VarAccBrowseGetRoot
	#define EXT_VarAccBrowseGetRoot
	#define GET_VarAccBrowseGetRoot(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccBrowseGetRoot(p0)  
	#define CHK_VarAccBrowseGetRoot  FALSE
	#define EXP_VarAccBrowseGetRoot  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccBrowseGetRoot
	#define EXT_VarAccBrowseGetRoot
	#define GET_VarAccBrowseGetRoot(fl)  CAL_CMGETAPI( "VarAccBrowseGetRoot" ) 
	#define CAL_VarAccBrowseGetRoot  VarAccBrowseGetRoot
	#define CHK_VarAccBrowseGetRoot  TRUE
	#define EXP_VarAccBrowseGetRoot  CAL_CMEXPAPI( "VarAccBrowseGetRoot" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccBrowseGetRoot
	#define EXT_VarAccBrowseGetRoot
	#define GET_VarAccBrowseGetRoot(fl)  CAL_CMGETAPI( "VarAccBrowseGetRoot" ) 
	#define CAL_VarAccBrowseGetRoot  VarAccBrowseGetRoot
	#define CHK_VarAccBrowseGetRoot  TRUE
	#define EXP_VarAccBrowseGetRoot  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccBrowseGetRoot", (RTS_UINTPTR)VarAccBrowseGetRoot, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccBrowseGetRoot
	#define EXT_IecVarAccess_ItfsVarAccBrowseGetRoot
	#define GET_IecVarAccess_ItfsVarAccBrowseGetRoot  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccBrowseGetRoot pIIecVarAccess_Itfs->IVarAccBrowseGetRoot
	#define CHK_IecVarAccess_ItfsVarAccBrowseGetRoot (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccBrowseGetRoot  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccBrowseGetRoot
	#define EXT_VarAccBrowseGetRoot
	#define GET_VarAccBrowseGetRoot(fl)  CAL_CMGETAPI( "VarAccBrowseGetRoot" ) 
	#define CAL_VarAccBrowseGetRoot pIIecVarAccess_Itfs->IVarAccBrowseGetRoot
	#define CHK_VarAccBrowseGetRoot (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccBrowseGetRoot  CAL_CMEXPAPI( "VarAccBrowseGetRoot" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccBrowseGetRoot  PFVARACCBROWSEGETROOT pfVarAccBrowseGetRoot;
	#define EXT_VarAccBrowseGetRoot  extern PFVARACCBROWSEGETROOT pfVarAccBrowseGetRoot;
	#define GET_VarAccBrowseGetRoot(fl)  s_pfCMGetAPI2( "VarAccBrowseGetRoot", (RTS_VOID_FCTPTR *)&pfVarAccBrowseGetRoot, (fl), 0, 0)
	#define CAL_VarAccBrowseGetRoot  pfVarAccBrowseGetRoot
	#define CHK_VarAccBrowseGetRoot  (pfVarAccBrowseGetRoot != NULL)
	#define EXP_VarAccBrowseGetRoot  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccBrowseGetRoot", (RTS_UINTPTR)VarAccBrowseGetRoot, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccBrowseGetNext</description>
 */
typedef struct tagiiecvaraccess4_varaccbrowsegetnext_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	IBaseTreeNode *VarAccBrowseGetNext;	/* VAR_OUTPUT */	
} iiecvaraccess4_varaccbrowsegetnext_struct;

void CDECL VarAccBrowseGetNext(iiecvaraccess4_varaccbrowsegetnext_struct *p);
typedef void (CDECL * PFVARACCBROWSEGETNEXT) (iiecvaraccess4_varaccbrowsegetnext_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCBROWSEGETNEXT_NOTIMPLEMENTED)
	#define USE_VarAccBrowseGetNext
	#define EXT_VarAccBrowseGetNext
	#define GET_VarAccBrowseGetNext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccBrowseGetNext(p0)  
	#define CHK_VarAccBrowseGetNext  FALSE
	#define EXP_VarAccBrowseGetNext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccBrowseGetNext
	#define EXT_VarAccBrowseGetNext
	#define GET_VarAccBrowseGetNext(fl)  CAL_CMGETAPI( "VarAccBrowseGetNext" ) 
	#define CAL_VarAccBrowseGetNext  VarAccBrowseGetNext
	#define CHK_VarAccBrowseGetNext  TRUE
	#define EXP_VarAccBrowseGetNext  CAL_CMEXPAPI( "VarAccBrowseGetNext" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccBrowseGetNext
	#define EXT_VarAccBrowseGetNext
	#define GET_VarAccBrowseGetNext(fl)  CAL_CMGETAPI( "VarAccBrowseGetNext" ) 
	#define CAL_VarAccBrowseGetNext  VarAccBrowseGetNext
	#define CHK_VarAccBrowseGetNext  TRUE
	#define EXP_VarAccBrowseGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccBrowseGetNext", (RTS_UINTPTR)VarAccBrowseGetNext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccBrowseGetNext
	#define EXT_IecVarAccess_ItfsVarAccBrowseGetNext
	#define GET_IecVarAccess_ItfsVarAccBrowseGetNext  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccBrowseGetNext pIIecVarAccess_Itfs->IVarAccBrowseGetNext
	#define CHK_IecVarAccess_ItfsVarAccBrowseGetNext (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccBrowseGetNext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccBrowseGetNext
	#define EXT_VarAccBrowseGetNext
	#define GET_VarAccBrowseGetNext(fl)  CAL_CMGETAPI( "VarAccBrowseGetNext" ) 
	#define CAL_VarAccBrowseGetNext pIIecVarAccess_Itfs->IVarAccBrowseGetNext
	#define CHK_VarAccBrowseGetNext (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccBrowseGetNext  CAL_CMEXPAPI( "VarAccBrowseGetNext" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccBrowseGetNext  PFVARACCBROWSEGETNEXT pfVarAccBrowseGetNext;
	#define EXT_VarAccBrowseGetNext  extern PFVARACCBROWSEGETNEXT pfVarAccBrowseGetNext;
	#define GET_VarAccBrowseGetNext(fl)  s_pfCMGetAPI2( "VarAccBrowseGetNext", (RTS_VOID_FCTPTR *)&pfVarAccBrowseGetNext, (fl), 0, 0)
	#define CAL_VarAccBrowseGetNext  pfVarAccBrowseGetNext
	#define CHK_VarAccBrowseGetNext  (pfVarAccBrowseGetNext != NULL)
	#define EXP_VarAccBrowseGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccBrowseGetNext", (RTS_UINTPTR)VarAccBrowseGetNext, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccGetAccessRights</description>
 */
typedef struct tagiiecvaraccess4_varaccgetaccessrights_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_INT VarAccGetAccessRights;	/* VAR_OUTPUT, Enum: ACCESSRIGHTS */
} iiecvaraccess4_varaccgetaccessrights_struct;

void CDECL VarAccGetAccessRights(iiecvaraccess4_varaccgetaccessrights_struct *p);
typedef void (CDECL * PFVARACCGETACCESSRIGHTS) (iiecvaraccess4_varaccgetaccessrights_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETACCESSRIGHTS_NOTIMPLEMENTED)
	#define USE_VarAccGetAccessRights
	#define EXT_VarAccGetAccessRights
	#define GET_VarAccGetAccessRights(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetAccessRights(p0)  
	#define CHK_VarAccGetAccessRights  FALSE
	#define EXP_VarAccGetAccessRights  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetAccessRights
	#define EXT_VarAccGetAccessRights
	#define GET_VarAccGetAccessRights(fl)  CAL_CMGETAPI( "VarAccGetAccessRights" ) 
	#define CAL_VarAccGetAccessRights  VarAccGetAccessRights
	#define CHK_VarAccGetAccessRights  TRUE
	#define EXP_VarAccGetAccessRights  CAL_CMEXPAPI( "VarAccGetAccessRights" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetAccessRights
	#define EXT_VarAccGetAccessRights
	#define GET_VarAccGetAccessRights(fl)  CAL_CMGETAPI( "VarAccGetAccessRights" ) 
	#define CAL_VarAccGetAccessRights  VarAccGetAccessRights
	#define CHK_VarAccGetAccessRights  TRUE
	#define EXP_VarAccGetAccessRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetAccessRights", (RTS_UINTPTR)VarAccGetAccessRights, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetAccessRights
	#define EXT_IecVarAccess_ItfsVarAccGetAccessRights
	#define GET_IecVarAccess_ItfsVarAccGetAccessRights  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetAccessRights pIIecVarAccess_Itfs->IVarAccGetAccessRights
	#define CHK_IecVarAccess_ItfsVarAccGetAccessRights (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetAccessRights  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetAccessRights
	#define EXT_VarAccGetAccessRights
	#define GET_VarAccGetAccessRights(fl)  CAL_CMGETAPI( "VarAccGetAccessRights" ) 
	#define CAL_VarAccGetAccessRights pIIecVarAccess_Itfs->IVarAccGetAccessRights
	#define CHK_VarAccGetAccessRights (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetAccessRights  CAL_CMEXPAPI( "VarAccGetAccessRights" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetAccessRights  PFVARACCGETACCESSRIGHTS pfVarAccGetAccessRights;
	#define EXT_VarAccGetAccessRights  extern PFVARACCGETACCESSRIGHTS pfVarAccGetAccessRights;
	#define GET_VarAccGetAccessRights(fl)  s_pfCMGetAPI2( "VarAccGetAccessRights", (RTS_VOID_FCTPTR *)&pfVarAccGetAccessRights, (fl), 0, 0)
	#define CAL_VarAccGetAccessRights  pfVarAccGetAccessRights
	#define CHK_VarAccGetAccessRights  (pfVarAccGetAccessRights != NULL)
	#define EXP_VarAccGetAccessRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetAccessRights", (RTS_UINTPTR)VarAccGetAccessRights, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccSetValue</description>
 */
typedef struct tagiiecvaraccess4_varaccsetvalue_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pSrc;					/* VAR_INPUT */	
	RTS_IEC_XWORD dwOffset;				/* VAR_INPUT */	
	RTS_IEC_XWORD dwSize;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_XWORD VarAccSetValue;		/* VAR_OUTPUT */	
} iiecvaraccess4_varaccsetvalue_struct;

void CDECL VarAccSetValue(iiecvaraccess4_varaccsetvalue_struct *p);
typedef void (CDECL * PFVARACCSETVALUE) (iiecvaraccess4_varaccsetvalue_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCSETVALUE_NOTIMPLEMENTED)
	#define USE_VarAccSetValue
	#define EXT_VarAccSetValue
	#define GET_VarAccSetValue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccSetValue(p0)  
	#define CHK_VarAccSetValue  FALSE
	#define EXP_VarAccSetValue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccSetValue
	#define EXT_VarAccSetValue
	#define GET_VarAccSetValue(fl)  CAL_CMGETAPI( "VarAccSetValue" ) 
	#define CAL_VarAccSetValue  VarAccSetValue
	#define CHK_VarAccSetValue  TRUE
	#define EXP_VarAccSetValue  CAL_CMEXPAPI( "VarAccSetValue" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccSetValue
	#define EXT_VarAccSetValue
	#define GET_VarAccSetValue(fl)  CAL_CMGETAPI( "VarAccSetValue" ) 
	#define CAL_VarAccSetValue  VarAccSetValue
	#define CHK_VarAccSetValue  TRUE
	#define EXP_VarAccSetValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccSetValue", (RTS_UINTPTR)VarAccSetValue, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccSetValue
	#define EXT_IecVarAccess_ItfsVarAccSetValue
	#define GET_IecVarAccess_ItfsVarAccSetValue  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccSetValue pIIecVarAccess_Itfs->IVarAccSetValue
	#define CHK_IecVarAccess_ItfsVarAccSetValue (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccSetValue  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccSetValue
	#define EXT_VarAccSetValue
	#define GET_VarAccSetValue(fl)  CAL_CMGETAPI( "VarAccSetValue" ) 
	#define CAL_VarAccSetValue pIIecVarAccess_Itfs->IVarAccSetValue
	#define CHK_VarAccSetValue (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccSetValue  CAL_CMEXPAPI( "VarAccSetValue" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccSetValue  PFVARACCSETVALUE pfVarAccSetValue;
	#define EXT_VarAccSetValue  extern PFVARACCSETVALUE pfVarAccSetValue;
	#define GET_VarAccSetValue(fl)  s_pfCMGetAPI2( "VarAccSetValue", (RTS_VOID_FCTPTR *)&pfVarAccSetValue, (fl), 0, 0)
	#define CAL_VarAccSetValue  pfVarAccSetValue
	#define CHK_VarAccSetValue  (pfVarAccSetValue != NULL)
	#define EXP_VarAccSetValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccSetValue", (RTS_UINTPTR)VarAccSetValue, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccGetNodeFullPath</description>
 */
typedef struct tagiiecvaraccess4_varaccgetnodefullpath_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_STRING *pszPath;			/* VAR_INPUT */	
	RTS_IEC_DINT diMaxPath;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_DINT VarAccGetNodeFullPath;	/* VAR_OUTPUT */	
} iiecvaraccess4_varaccgetnodefullpath_struct;

void CDECL VarAccGetNodeFullPath(iiecvaraccess4_varaccgetnodefullpath_struct *p);
typedef void (CDECL * PFVARACCGETNODEFULLPATH) (iiecvaraccess4_varaccgetnodefullpath_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETNODEFULLPATH_NOTIMPLEMENTED)
	#define USE_VarAccGetNodeFullPath
	#define EXT_VarAccGetNodeFullPath
	#define GET_VarAccGetNodeFullPath(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetNodeFullPath(p0)  
	#define CHK_VarAccGetNodeFullPath  FALSE
	#define EXP_VarAccGetNodeFullPath  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetNodeFullPath
	#define EXT_VarAccGetNodeFullPath
	#define GET_VarAccGetNodeFullPath(fl)  CAL_CMGETAPI( "VarAccGetNodeFullPath" ) 
	#define CAL_VarAccGetNodeFullPath  VarAccGetNodeFullPath
	#define CHK_VarAccGetNodeFullPath  TRUE
	#define EXP_VarAccGetNodeFullPath  CAL_CMEXPAPI( "VarAccGetNodeFullPath" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetNodeFullPath
	#define EXT_VarAccGetNodeFullPath
	#define GET_VarAccGetNodeFullPath(fl)  CAL_CMGETAPI( "VarAccGetNodeFullPath" ) 
	#define CAL_VarAccGetNodeFullPath  VarAccGetNodeFullPath
	#define CHK_VarAccGetNodeFullPath  TRUE
	#define EXP_VarAccGetNodeFullPath  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNodeFullPath", (RTS_UINTPTR)VarAccGetNodeFullPath, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetNodeFullPath
	#define EXT_IecVarAccess_ItfsVarAccGetNodeFullPath
	#define GET_IecVarAccess_ItfsVarAccGetNodeFullPath  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetNodeFullPath pIIecVarAccess_Itfs->IVarAccGetNodeFullPath
	#define CHK_IecVarAccess_ItfsVarAccGetNodeFullPath (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetNodeFullPath  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetNodeFullPath
	#define EXT_VarAccGetNodeFullPath
	#define GET_VarAccGetNodeFullPath(fl)  CAL_CMGETAPI( "VarAccGetNodeFullPath" ) 
	#define CAL_VarAccGetNodeFullPath pIIecVarAccess_Itfs->IVarAccGetNodeFullPath
	#define CHK_VarAccGetNodeFullPath (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetNodeFullPath  CAL_CMEXPAPI( "VarAccGetNodeFullPath" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetNodeFullPath  PFVARACCGETNODEFULLPATH pfVarAccGetNodeFullPath;
	#define EXT_VarAccGetNodeFullPath  extern PFVARACCGETNODEFULLPATH pfVarAccGetNodeFullPath;
	#define GET_VarAccGetNodeFullPath(fl)  s_pfCMGetAPI2( "VarAccGetNodeFullPath", (RTS_VOID_FCTPTR *)&pfVarAccGetNodeFullPath, (fl), 0, 0)
	#define CAL_VarAccGetNodeFullPath  pfVarAccGetNodeFullPath
	#define CHK_VarAccGetNodeFullPath  (pfVarAccGetNodeFullPath != NULL)
	#define EXP_VarAccGetNodeFullPath  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNodeFullPath", (RTS_UINTPTR)VarAccGetNodeFullPath, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccGetTypeDesc</description>
 */
typedef struct tagiiecvaraccess4_varaccgettypedesc_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	ITypeDesc *pTypeDesc;				/* VAR_INPUT */	
	TypeDescAsUnion *pTypeDescStruct;	/* VAR_INPUT */	
	RTS_IEC_UDINT VarAccGetTypeDesc;	/* VAR_OUTPUT */	
} iiecvaraccess4_varaccgettypedesc_struct;

void CDECL VarAccGetTypeDesc(iiecvaraccess4_varaccgettypedesc_struct *p);
typedef void (CDECL * PFVARACCGETTYPEDESC) (iiecvaraccess4_varaccgettypedesc_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETTYPEDESC_NOTIMPLEMENTED)
	#define USE_VarAccGetTypeDesc
	#define EXT_VarAccGetTypeDesc
	#define GET_VarAccGetTypeDesc(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetTypeDesc(p0)  
	#define CHK_VarAccGetTypeDesc  FALSE
	#define EXP_VarAccGetTypeDesc  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetTypeDesc
	#define EXT_VarAccGetTypeDesc
	#define GET_VarAccGetTypeDesc(fl)  CAL_CMGETAPI( "VarAccGetTypeDesc" ) 
	#define CAL_VarAccGetTypeDesc  VarAccGetTypeDesc
	#define CHK_VarAccGetTypeDesc  TRUE
	#define EXP_VarAccGetTypeDesc  CAL_CMEXPAPI( "VarAccGetTypeDesc" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetTypeDesc
	#define EXT_VarAccGetTypeDesc
	#define GET_VarAccGetTypeDesc(fl)  CAL_CMGETAPI( "VarAccGetTypeDesc" ) 
	#define CAL_VarAccGetTypeDesc  VarAccGetTypeDesc
	#define CHK_VarAccGetTypeDesc  TRUE
	#define EXP_VarAccGetTypeDesc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetTypeDesc", (RTS_UINTPTR)VarAccGetTypeDesc, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetTypeDesc
	#define EXT_IecVarAccess_ItfsVarAccGetTypeDesc
	#define GET_IecVarAccess_ItfsVarAccGetTypeDesc  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetTypeDesc pIIecVarAccess_Itfs->IVarAccGetTypeDesc
	#define CHK_IecVarAccess_ItfsVarAccGetTypeDesc (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetTypeDesc  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetTypeDesc
	#define EXT_VarAccGetTypeDesc
	#define GET_VarAccGetTypeDesc(fl)  CAL_CMGETAPI( "VarAccGetTypeDesc" ) 
	#define CAL_VarAccGetTypeDesc pIIecVarAccess_Itfs->IVarAccGetTypeDesc
	#define CHK_VarAccGetTypeDesc (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetTypeDesc  CAL_CMEXPAPI( "VarAccGetTypeDesc" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetTypeDesc  PFVARACCGETTYPEDESC pfVarAccGetTypeDesc;
	#define EXT_VarAccGetTypeDesc  extern PFVARACCGETTYPEDESC pfVarAccGetTypeDesc;
	#define GET_VarAccGetTypeDesc(fl)  s_pfCMGetAPI2( "VarAccGetTypeDesc", (RTS_VOID_FCTPTR *)&pfVarAccGetTypeDesc, (fl), 0, 0)
	#define CAL_VarAccGetTypeDesc  pfVarAccGetTypeDesc
	#define CHK_VarAccGetTypeDesc  (pfVarAccGetTypeDesc != NULL)
	#define EXP_VarAccGetTypeDesc  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetTypeDesc", (RTS_UINTPTR)VarAccGetTypeDesc, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccAppendVariable</description>
 */
typedef struct tagiiecvaraccess4_varaccappendvariable_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_UDINT VarAccAppendVariable;	/* VAR_OUTPUT */	
} iiecvaraccess4_varaccappendvariable_struct;

void CDECL VarAccAppendVariable(iiecvaraccess4_varaccappendvariable_struct *p);
typedef void (CDECL * PFVARACCAPPENDVARIABLE) (iiecvaraccess4_varaccappendvariable_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCAPPENDVARIABLE_NOTIMPLEMENTED)
	#define USE_VarAccAppendVariable
	#define EXT_VarAccAppendVariable
	#define GET_VarAccAppendVariable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccAppendVariable(p0)  
	#define CHK_VarAccAppendVariable  FALSE
	#define EXP_VarAccAppendVariable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccAppendVariable
	#define EXT_VarAccAppendVariable
	#define GET_VarAccAppendVariable(fl)  CAL_CMGETAPI( "VarAccAppendVariable" ) 
	#define CAL_VarAccAppendVariable  VarAccAppendVariable
	#define CHK_VarAccAppendVariable  TRUE
	#define EXP_VarAccAppendVariable  CAL_CMEXPAPI( "VarAccAppendVariable" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccAppendVariable
	#define EXT_VarAccAppendVariable
	#define GET_VarAccAppendVariable(fl)  CAL_CMGETAPI( "VarAccAppendVariable" ) 
	#define CAL_VarAccAppendVariable  VarAccAppendVariable
	#define CHK_VarAccAppendVariable  TRUE
	#define EXP_VarAccAppendVariable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccAppendVariable", (RTS_UINTPTR)VarAccAppendVariable, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccAppendVariable
	#define EXT_IecVarAccess_ItfsVarAccAppendVariable
	#define GET_IecVarAccess_ItfsVarAccAppendVariable  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccAppendVariable pIIecVarAccess_Itfs->IVarAccAppendVariable
	#define CHK_IecVarAccess_ItfsVarAccAppendVariable (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccAppendVariable  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccAppendVariable
	#define EXT_VarAccAppendVariable
	#define GET_VarAccAppendVariable(fl)  CAL_CMGETAPI( "VarAccAppendVariable" ) 
	#define CAL_VarAccAppendVariable pIIecVarAccess_Itfs->IVarAccAppendVariable
	#define CHK_VarAccAppendVariable (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccAppendVariable  CAL_CMEXPAPI( "VarAccAppendVariable" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccAppendVariable  PFVARACCAPPENDVARIABLE pfVarAccAppendVariable;
	#define EXT_VarAccAppendVariable  extern PFVARACCAPPENDVARIABLE pfVarAccAppendVariable;
	#define GET_VarAccAppendVariable(fl)  s_pfCMGetAPI2( "VarAccAppendVariable", (RTS_VOID_FCTPTR *)&pfVarAccAppendVariable, (fl), 0, 0)
	#define CAL_VarAccAppendVariable  pfVarAccAppendVariable
	#define CHK_VarAccAppendVariable  (pfVarAccAppendVariable != NULL)
	#define EXP_VarAccAppendVariable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccAppendVariable", (RTS_UINTPTR)VarAccAppendVariable, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccGetNodeType</description>
 */
typedef struct tagiiecvaraccess4_varaccgetnodetype_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_INT VarAccGetNodeType;		/* VAR_OUTPUT, Enum: TREENODETYPE */
} iiecvaraccess4_varaccgetnodetype_struct;

void CDECL VarAccGetNodeType(iiecvaraccess4_varaccgetnodetype_struct *p);
typedef void (CDECL * PFVARACCGETNODETYPE) (iiecvaraccess4_varaccgetnodetype_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETNODETYPE_NOTIMPLEMENTED)
	#define USE_VarAccGetNodeType
	#define EXT_VarAccGetNodeType
	#define GET_VarAccGetNodeType(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetNodeType(p0)  
	#define CHK_VarAccGetNodeType  FALSE
	#define EXP_VarAccGetNodeType  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetNodeType
	#define EXT_VarAccGetNodeType
	#define GET_VarAccGetNodeType(fl)  CAL_CMGETAPI( "VarAccGetNodeType" ) 
	#define CAL_VarAccGetNodeType  VarAccGetNodeType
	#define CHK_VarAccGetNodeType  TRUE
	#define EXP_VarAccGetNodeType  CAL_CMEXPAPI( "VarAccGetNodeType" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetNodeType
	#define EXT_VarAccGetNodeType
	#define GET_VarAccGetNodeType(fl)  CAL_CMGETAPI( "VarAccGetNodeType" ) 
	#define CAL_VarAccGetNodeType  VarAccGetNodeType
	#define CHK_VarAccGetNodeType  TRUE
	#define EXP_VarAccGetNodeType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNodeType", (RTS_UINTPTR)VarAccGetNodeType, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetNodeType
	#define EXT_IecVarAccess_ItfsVarAccGetNodeType
	#define GET_IecVarAccess_ItfsVarAccGetNodeType  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetNodeType pIIecVarAccess_Itfs->IVarAccGetNodeType
	#define CHK_IecVarAccess_ItfsVarAccGetNodeType (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetNodeType  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetNodeType
	#define EXT_VarAccGetNodeType
	#define GET_VarAccGetNodeType(fl)  CAL_CMGETAPI( "VarAccGetNodeType" ) 
	#define CAL_VarAccGetNodeType pIIecVarAccess_Itfs->IVarAccGetNodeType
	#define CHK_VarAccGetNodeType (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetNodeType  CAL_CMEXPAPI( "VarAccGetNodeType" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetNodeType  PFVARACCGETNODETYPE pfVarAccGetNodeType;
	#define EXT_VarAccGetNodeType  extern PFVARACCGETNODETYPE pfVarAccGetNodeType;
	#define GET_VarAccGetNodeType(fl)  s_pfCMGetAPI2( "VarAccGetNodeType", (RTS_VOID_FCTPTR *)&pfVarAccGetNodeType, (fl), 0, 0)
	#define CAL_VarAccGetNodeType  pfVarAccGetNodeType
	#define CHK_VarAccGetNodeType  (pfVarAccGetNodeType != NULL)
	#define EXP_VarAccGetNodeType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNodeType", (RTS_UINTPTR)VarAccGetNodeType, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccBrowseDown</description>
 */
typedef struct tagiiecvaraccess4_varaccbrowsedown_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	IBaseTreeNode *VarAccBrowseDown;	/* VAR_OUTPUT */	
} iiecvaraccess4_varaccbrowsedown_struct;

void CDECL VarAccBrowseDown(iiecvaraccess4_varaccbrowsedown_struct *p);
typedef void (CDECL * PFVARACCBROWSEDOWN) (iiecvaraccess4_varaccbrowsedown_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCBROWSEDOWN_NOTIMPLEMENTED)
	#define USE_VarAccBrowseDown
	#define EXT_VarAccBrowseDown
	#define GET_VarAccBrowseDown(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccBrowseDown(p0)  
	#define CHK_VarAccBrowseDown  FALSE
	#define EXP_VarAccBrowseDown  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccBrowseDown
	#define EXT_VarAccBrowseDown
	#define GET_VarAccBrowseDown(fl)  CAL_CMGETAPI( "VarAccBrowseDown" ) 
	#define CAL_VarAccBrowseDown  VarAccBrowseDown
	#define CHK_VarAccBrowseDown  TRUE
	#define EXP_VarAccBrowseDown  CAL_CMEXPAPI( "VarAccBrowseDown" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccBrowseDown
	#define EXT_VarAccBrowseDown
	#define GET_VarAccBrowseDown(fl)  CAL_CMGETAPI( "VarAccBrowseDown" ) 
	#define CAL_VarAccBrowseDown  VarAccBrowseDown
	#define CHK_VarAccBrowseDown  TRUE
	#define EXP_VarAccBrowseDown  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccBrowseDown", (RTS_UINTPTR)VarAccBrowseDown, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccBrowseDown
	#define EXT_IecVarAccess_ItfsVarAccBrowseDown
	#define GET_IecVarAccess_ItfsVarAccBrowseDown  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccBrowseDown pIIecVarAccess_Itfs->IVarAccBrowseDown
	#define CHK_IecVarAccess_ItfsVarAccBrowseDown (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccBrowseDown  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccBrowseDown
	#define EXT_VarAccBrowseDown
	#define GET_VarAccBrowseDown(fl)  CAL_CMGETAPI( "VarAccBrowseDown" ) 
	#define CAL_VarAccBrowseDown pIIecVarAccess_Itfs->IVarAccBrowseDown
	#define CHK_VarAccBrowseDown (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccBrowseDown  CAL_CMEXPAPI( "VarAccBrowseDown" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccBrowseDown  PFVARACCBROWSEDOWN pfVarAccBrowseDown;
	#define EXT_VarAccBrowseDown  extern PFVARACCBROWSEDOWN pfVarAccBrowseDown;
	#define GET_VarAccBrowseDown(fl)  s_pfCMGetAPI2( "VarAccBrowseDown", (RTS_VOID_FCTPTR *)&pfVarAccBrowseDown, (fl), 0, 0)
	#define CAL_VarAccBrowseDown  pfVarAccBrowseDown
	#define CHK_VarAccBrowseDown  (pfVarAccBrowseDown != NULL)
	#define EXP_VarAccBrowseDown  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccBrowseDown", (RTS_UINTPTR)VarAccBrowseDown, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccGetSize</description>
 */
typedef struct tagiiecvaraccess4_varaccgetsize_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_XWORD VarAccGetSize;		/* VAR_OUTPUT */	
} iiecvaraccess4_varaccgetsize_struct;

void CDECL VarAccGetSize(iiecvaraccess4_varaccgetsize_struct *p);
typedef void (CDECL * PFVARACCGETSIZE) (iiecvaraccess4_varaccgetsize_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETSIZE_NOTIMPLEMENTED)
	#define USE_VarAccGetSize
	#define EXT_VarAccGetSize
	#define GET_VarAccGetSize(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetSize(p0)  
	#define CHK_VarAccGetSize  FALSE
	#define EXP_VarAccGetSize  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetSize
	#define EXT_VarAccGetSize
	#define GET_VarAccGetSize(fl)  CAL_CMGETAPI( "VarAccGetSize" ) 
	#define CAL_VarAccGetSize  VarAccGetSize
	#define CHK_VarAccGetSize  TRUE
	#define EXP_VarAccGetSize  CAL_CMEXPAPI( "VarAccGetSize" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetSize
	#define EXT_VarAccGetSize
	#define GET_VarAccGetSize(fl)  CAL_CMGETAPI( "VarAccGetSize" ) 
	#define CAL_VarAccGetSize  VarAccGetSize
	#define CHK_VarAccGetSize  TRUE
	#define EXP_VarAccGetSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetSize", (RTS_UINTPTR)VarAccGetSize, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetSize
	#define EXT_IecVarAccess_ItfsVarAccGetSize
	#define GET_IecVarAccess_ItfsVarAccGetSize  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetSize pIIecVarAccess_Itfs->IVarAccGetSize
	#define CHK_IecVarAccess_ItfsVarAccGetSize (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetSize  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetSize
	#define EXT_VarAccGetSize
	#define GET_VarAccGetSize(fl)  CAL_CMGETAPI( "VarAccGetSize" ) 
	#define CAL_VarAccGetSize pIIecVarAccess_Itfs->IVarAccGetSize
	#define CHK_VarAccGetSize (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetSize  CAL_CMEXPAPI( "VarAccGetSize" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetSize  PFVARACCGETSIZE pfVarAccGetSize;
	#define EXT_VarAccGetSize  extern PFVARACCGETSIZE pfVarAccGetSize;
	#define GET_VarAccGetSize(fl)  s_pfCMGetAPI2( "VarAccGetSize", (RTS_VOID_FCTPTR *)&pfVarAccGetSize, (fl), 0, 0)
	#define CAL_VarAccGetSize  pfVarAccGetSize
	#define CHK_VarAccGetSize  (pfVarAccGetSize != NULL)
	#define EXP_VarAccGetSize  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetSize", (RTS_UINTPTR)VarAccGetSize, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccGetTypeNode2</description>
 */
typedef struct tagiiecvaraccess4_varaccgettypenode2_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_XWORD dwOffset;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	ITypeDesc *VarAccGetTypeNode2;		/* VAR_OUTPUT */	
} iiecvaraccess4_varaccgettypenode2_struct;

void CDECL VarAccGetTypeNode2(iiecvaraccess4_varaccgettypenode2_struct *p);
typedef void (CDECL * PFVARACCGETTYPENODE2) (iiecvaraccess4_varaccgettypenode2_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETTYPENODE2_NOTIMPLEMENTED)
	#define USE_VarAccGetTypeNode2
	#define EXT_VarAccGetTypeNode2
	#define GET_VarAccGetTypeNode2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetTypeNode2(p0)  
	#define CHK_VarAccGetTypeNode2  FALSE
	#define EXP_VarAccGetTypeNode2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetTypeNode2
	#define EXT_VarAccGetTypeNode2
	#define GET_VarAccGetTypeNode2(fl)  CAL_CMGETAPI( "VarAccGetTypeNode2" ) 
	#define CAL_VarAccGetTypeNode2  VarAccGetTypeNode2
	#define CHK_VarAccGetTypeNode2  TRUE
	#define EXP_VarAccGetTypeNode2  CAL_CMEXPAPI( "VarAccGetTypeNode2" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetTypeNode2
	#define EXT_VarAccGetTypeNode2
	#define GET_VarAccGetTypeNode2(fl)  CAL_CMGETAPI( "VarAccGetTypeNode2" ) 
	#define CAL_VarAccGetTypeNode2  VarAccGetTypeNode2
	#define CHK_VarAccGetTypeNode2  TRUE
	#define EXP_VarAccGetTypeNode2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetTypeNode2", (RTS_UINTPTR)VarAccGetTypeNode2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetTypeNode2
	#define EXT_IecVarAccess_ItfsVarAccGetTypeNode2
	#define GET_IecVarAccess_ItfsVarAccGetTypeNode2  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetTypeNode2 pIIecVarAccess_Itfs->IVarAccGetTypeNode2
	#define CHK_IecVarAccess_ItfsVarAccGetTypeNode2 (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetTypeNode2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetTypeNode2
	#define EXT_VarAccGetTypeNode2
	#define GET_VarAccGetTypeNode2(fl)  CAL_CMGETAPI( "VarAccGetTypeNode2" ) 
	#define CAL_VarAccGetTypeNode2 pIIecVarAccess_Itfs->IVarAccGetTypeNode2
	#define CHK_VarAccGetTypeNode2 (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetTypeNode2  CAL_CMEXPAPI( "VarAccGetTypeNode2" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetTypeNode2  PFVARACCGETTYPENODE2 pfVarAccGetTypeNode2;
	#define EXT_VarAccGetTypeNode2  extern PFVARACCGETTYPENODE2 pfVarAccGetTypeNode2;
	#define GET_VarAccGetTypeNode2(fl)  s_pfCMGetAPI2( "VarAccGetTypeNode2", (RTS_VOID_FCTPTR *)&pfVarAccGetTypeNode2, (fl), 0, 0)
	#define CAL_VarAccGetTypeNode2  pfVarAccGetTypeNode2
	#define CHK_VarAccGetTypeNode2  (pfVarAccGetTypeNode2 != NULL)
	#define EXP_VarAccGetTypeNode2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetTypeNode2", (RTS_UINTPTR)VarAccGetTypeNode2, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccGetTypeNode</description>
 */
typedef struct tagiiecvaraccess4_varaccgettypenode_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	ITypeDesc *VarAccGetTypeNode;		/* VAR_OUTPUT */	
} iiecvaraccess4_varaccgettypenode_struct;

void CDECL VarAccGetTypeNode(iiecvaraccess4_varaccgettypenode_struct *p);
typedef void (CDECL * PFVARACCGETTYPENODE) (iiecvaraccess4_varaccgettypenode_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETTYPENODE_NOTIMPLEMENTED)
	#define USE_VarAccGetTypeNode
	#define EXT_VarAccGetTypeNode
	#define GET_VarAccGetTypeNode(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetTypeNode(p0)  
	#define CHK_VarAccGetTypeNode  FALSE
	#define EXP_VarAccGetTypeNode  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetTypeNode
	#define EXT_VarAccGetTypeNode
	#define GET_VarAccGetTypeNode(fl)  CAL_CMGETAPI( "VarAccGetTypeNode" ) 
	#define CAL_VarAccGetTypeNode  VarAccGetTypeNode
	#define CHK_VarAccGetTypeNode  TRUE
	#define EXP_VarAccGetTypeNode  CAL_CMEXPAPI( "VarAccGetTypeNode" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetTypeNode
	#define EXT_VarAccGetTypeNode
	#define GET_VarAccGetTypeNode(fl)  CAL_CMGETAPI( "VarAccGetTypeNode" ) 
	#define CAL_VarAccGetTypeNode  VarAccGetTypeNode
	#define CHK_VarAccGetTypeNode  TRUE
	#define EXP_VarAccGetTypeNode  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetTypeNode", (RTS_UINTPTR)VarAccGetTypeNode, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetTypeNode
	#define EXT_IecVarAccess_ItfsVarAccGetTypeNode
	#define GET_IecVarAccess_ItfsVarAccGetTypeNode  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetTypeNode pIIecVarAccess_Itfs->IVarAccGetTypeNode
	#define CHK_IecVarAccess_ItfsVarAccGetTypeNode (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetTypeNode  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetTypeNode
	#define EXT_VarAccGetTypeNode
	#define GET_VarAccGetTypeNode(fl)  CAL_CMGETAPI( "VarAccGetTypeNode" ) 
	#define CAL_VarAccGetTypeNode pIIecVarAccess_Itfs->IVarAccGetTypeNode
	#define CHK_VarAccGetTypeNode (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetTypeNode  CAL_CMEXPAPI( "VarAccGetTypeNode" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetTypeNode  PFVARACCGETTYPENODE pfVarAccGetTypeNode;
	#define EXT_VarAccGetTypeNode  extern PFVARACCGETTYPENODE pfVarAccGetTypeNode;
	#define GET_VarAccGetTypeNode(fl)  s_pfCMGetAPI2( "VarAccGetTypeNode", (RTS_VOID_FCTPTR *)&pfVarAccGetTypeNode, (fl), 0, 0)
	#define CAL_VarAccGetTypeNode  pfVarAccGetTypeNode
	#define CHK_VarAccGetTypeNode  (pfVarAccGetTypeNode != NULL)
	#define EXP_VarAccGetTypeNode  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetTypeNode", (RTS_UINTPTR)VarAccGetTypeNode, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccBeginVariableConfiguration</description>
 */
typedef struct tagiiecvaraccess4_varaccbeginvariableconfiguration_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_BOOL bBlocking;				/* VAR_INPUT */	
	RTS_IEC_UDINT VarAccBeginVariableConfiguration;	/* VAR_OUTPUT */	
} iiecvaraccess4_varaccbeginvariableconfiguration_struct;

void CDECL VarAccBeginVariableConfiguration(iiecvaraccess4_varaccbeginvariableconfiguration_struct *p);
typedef void (CDECL * PFVARACCBEGINVARIABLECONFIGURATION) (iiecvaraccess4_varaccbeginvariableconfiguration_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCBEGINVARIABLECONFIGURATION_NOTIMPLEMENTED)
	#define USE_VarAccBeginVariableConfiguration
	#define EXT_VarAccBeginVariableConfiguration
	#define GET_VarAccBeginVariableConfiguration(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccBeginVariableConfiguration(p0)  
	#define CHK_VarAccBeginVariableConfiguration  FALSE
	#define EXP_VarAccBeginVariableConfiguration  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccBeginVariableConfiguration
	#define EXT_VarAccBeginVariableConfiguration
	#define GET_VarAccBeginVariableConfiguration(fl)  CAL_CMGETAPI( "VarAccBeginVariableConfiguration" ) 
	#define CAL_VarAccBeginVariableConfiguration  VarAccBeginVariableConfiguration
	#define CHK_VarAccBeginVariableConfiguration  TRUE
	#define EXP_VarAccBeginVariableConfiguration  CAL_CMEXPAPI( "VarAccBeginVariableConfiguration" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccBeginVariableConfiguration
	#define EXT_VarAccBeginVariableConfiguration
	#define GET_VarAccBeginVariableConfiguration(fl)  CAL_CMGETAPI( "VarAccBeginVariableConfiguration" ) 
	#define CAL_VarAccBeginVariableConfiguration  VarAccBeginVariableConfiguration
	#define CHK_VarAccBeginVariableConfiguration  TRUE
	#define EXP_VarAccBeginVariableConfiguration  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccBeginVariableConfiguration", (RTS_UINTPTR)VarAccBeginVariableConfiguration, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccBeginVariableConfiguration
	#define EXT_IecVarAccess_ItfsVarAccBeginVariableConfiguration
	#define GET_IecVarAccess_ItfsVarAccBeginVariableConfiguration  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccBeginVariableConfiguration pIIecVarAccess_Itfs->IVarAccBeginVariableConfiguration
	#define CHK_IecVarAccess_ItfsVarAccBeginVariableConfiguration (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccBeginVariableConfiguration  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccBeginVariableConfiguration
	#define EXT_VarAccBeginVariableConfiguration
	#define GET_VarAccBeginVariableConfiguration(fl)  CAL_CMGETAPI( "VarAccBeginVariableConfiguration" ) 
	#define CAL_VarAccBeginVariableConfiguration pIIecVarAccess_Itfs->IVarAccBeginVariableConfiguration
	#define CHK_VarAccBeginVariableConfiguration (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccBeginVariableConfiguration  CAL_CMEXPAPI( "VarAccBeginVariableConfiguration" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccBeginVariableConfiguration  PFVARACCBEGINVARIABLECONFIGURATION pfVarAccBeginVariableConfiguration;
	#define EXT_VarAccBeginVariableConfiguration  extern PFVARACCBEGINVARIABLECONFIGURATION pfVarAccBeginVariableConfiguration;
	#define GET_VarAccBeginVariableConfiguration(fl)  s_pfCMGetAPI2( "VarAccBeginVariableConfiguration", (RTS_VOID_FCTPTR *)&pfVarAccBeginVariableConfiguration, (fl), 0, 0)
	#define CAL_VarAccBeginVariableConfiguration  pfVarAccBeginVariableConfiguration
	#define CHK_VarAccBeginVariableConfiguration  (pfVarAccBeginVariableConfiguration != NULL)
	#define EXP_VarAccBeginVariableConfiguration  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccBeginVariableConfiguration", (RTS_UINTPTR)VarAccBeginVariableConfiguration, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccGetAddress2</description>
 */
typedef struct tagiiecvaraccess4_varaccgetaddress2_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_XWORD dwOffset;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_BYTE *VarAccGetAddress2;	/* VAR_OUTPUT */	
} iiecvaraccess4_varaccgetaddress2_struct;

void CDECL VarAccGetAddress2(iiecvaraccess4_varaccgetaddress2_struct *p);
typedef void (CDECL * PFVARACCGETADDRESS2) (iiecvaraccess4_varaccgetaddress2_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETADDRESS2_NOTIMPLEMENTED)
	#define USE_VarAccGetAddress2
	#define EXT_VarAccGetAddress2
	#define GET_VarAccGetAddress2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetAddress2(p0)  
	#define CHK_VarAccGetAddress2  FALSE
	#define EXP_VarAccGetAddress2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetAddress2
	#define EXT_VarAccGetAddress2
	#define GET_VarAccGetAddress2(fl)  CAL_CMGETAPI( "VarAccGetAddress2" ) 
	#define CAL_VarAccGetAddress2  VarAccGetAddress2
	#define CHK_VarAccGetAddress2  TRUE
	#define EXP_VarAccGetAddress2  CAL_CMEXPAPI( "VarAccGetAddress2" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetAddress2
	#define EXT_VarAccGetAddress2
	#define GET_VarAccGetAddress2(fl)  CAL_CMGETAPI( "VarAccGetAddress2" ) 
	#define CAL_VarAccGetAddress2  VarAccGetAddress2
	#define CHK_VarAccGetAddress2  TRUE
	#define EXP_VarAccGetAddress2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetAddress2", (RTS_UINTPTR)VarAccGetAddress2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetAddress2
	#define EXT_IecVarAccess_ItfsVarAccGetAddress2
	#define GET_IecVarAccess_ItfsVarAccGetAddress2  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetAddress2 pIIecVarAccess_Itfs->IVarAccGetAddress2
	#define CHK_IecVarAccess_ItfsVarAccGetAddress2 (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetAddress2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetAddress2
	#define EXT_VarAccGetAddress2
	#define GET_VarAccGetAddress2(fl)  CAL_CMGETAPI( "VarAccGetAddress2" ) 
	#define CAL_VarAccGetAddress2 pIIecVarAccess_Itfs->IVarAccGetAddress2
	#define CHK_VarAccGetAddress2 (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetAddress2  CAL_CMEXPAPI( "VarAccGetAddress2" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetAddress2  PFVARACCGETADDRESS2 pfVarAccGetAddress2;
	#define EXT_VarAccGetAddress2  extern PFVARACCGETADDRESS2 pfVarAccGetAddress2;
	#define GET_VarAccGetAddress2(fl)  s_pfCMGetAPI2( "VarAccGetAddress2", (RTS_VOID_FCTPTR *)&pfVarAccGetAddress2, (fl), 0, 0)
	#define CAL_VarAccGetAddress2  pfVarAccGetAddress2
	#define CHK_VarAccGetAddress2  (pfVarAccGetAddress2 != NULL)
	#define EXP_VarAccGetAddress2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetAddress2", (RTS_UINTPTR)VarAccGetAddress2, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccSwap2</description>
 */
typedef struct tagiiecvaraccess4_varaccswap2_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	RTS_IEC_XWORD dwOffset;				/* VAR_INPUT */	
	RTS_IEC_BOOL bMotorola;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_XWORD VarAccSwap2;			/* VAR_OUTPUT */	
} iiecvaraccess4_varaccswap2_struct;

void CDECL VarAccSwap2(iiecvaraccess4_varaccswap2_struct *p);
typedef void (CDECL * PFVARACCSWAP2) (iiecvaraccess4_varaccswap2_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCSWAP2_NOTIMPLEMENTED)
	#define USE_VarAccSwap2
	#define EXT_VarAccSwap2
	#define GET_VarAccSwap2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccSwap2(p0)  
	#define CHK_VarAccSwap2  FALSE
	#define EXP_VarAccSwap2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccSwap2
	#define EXT_VarAccSwap2
	#define GET_VarAccSwap2(fl)  CAL_CMGETAPI( "VarAccSwap2" ) 
	#define CAL_VarAccSwap2  VarAccSwap2
	#define CHK_VarAccSwap2  TRUE
	#define EXP_VarAccSwap2  CAL_CMEXPAPI( "VarAccSwap2" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccSwap2
	#define EXT_VarAccSwap2
	#define GET_VarAccSwap2(fl)  CAL_CMGETAPI( "VarAccSwap2" ) 
	#define CAL_VarAccSwap2  VarAccSwap2
	#define CHK_VarAccSwap2  TRUE
	#define EXP_VarAccSwap2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccSwap2", (RTS_UINTPTR)VarAccSwap2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccSwap2
	#define EXT_IecVarAccess_ItfsVarAccSwap2
	#define GET_IecVarAccess_ItfsVarAccSwap2  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccSwap2 pIIecVarAccess_Itfs->IVarAccSwap2
	#define CHK_IecVarAccess_ItfsVarAccSwap2 (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccSwap2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccSwap2
	#define EXT_VarAccSwap2
	#define GET_VarAccSwap2(fl)  CAL_CMGETAPI( "VarAccSwap2" ) 
	#define CAL_VarAccSwap2 pIIecVarAccess_Itfs->IVarAccSwap2
	#define CHK_VarAccSwap2 (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccSwap2  CAL_CMEXPAPI( "VarAccSwap2" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccSwap2  PFVARACCSWAP2 pfVarAccSwap2;
	#define EXT_VarAccSwap2  extern PFVARACCSWAP2 pfVarAccSwap2;
	#define GET_VarAccSwap2(fl)  s_pfCMGetAPI2( "VarAccSwap2", (RTS_VOID_FCTPTR *)&pfVarAccSwap2, (fl), 0, 0)
	#define CAL_VarAccSwap2  pfVarAccSwap2
	#define CHK_VarAccSwap2  (pfVarAccSwap2 != NULL)
	#define EXP_VarAccSwap2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccSwap2", (RTS_UINTPTR)VarAccSwap2, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccBrowseUp</description>
 */
typedef struct tagiiecvaraccess4_varaccbrowseup_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	IBaseTreeNode *VarAccBrowseUp;		/* VAR_OUTPUT */	
} iiecvaraccess4_varaccbrowseup_struct;

void CDECL VarAccBrowseUp(iiecvaraccess4_varaccbrowseup_struct *p);
typedef void (CDECL * PFVARACCBROWSEUP) (iiecvaraccess4_varaccbrowseup_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCBROWSEUP_NOTIMPLEMENTED)
	#define USE_VarAccBrowseUp
	#define EXT_VarAccBrowseUp
	#define GET_VarAccBrowseUp(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccBrowseUp(p0)  
	#define CHK_VarAccBrowseUp  FALSE
	#define EXP_VarAccBrowseUp  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccBrowseUp
	#define EXT_VarAccBrowseUp
	#define GET_VarAccBrowseUp(fl)  CAL_CMGETAPI( "VarAccBrowseUp" ) 
	#define CAL_VarAccBrowseUp  VarAccBrowseUp
	#define CHK_VarAccBrowseUp  TRUE
	#define EXP_VarAccBrowseUp  CAL_CMEXPAPI( "VarAccBrowseUp" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccBrowseUp
	#define EXT_VarAccBrowseUp
	#define GET_VarAccBrowseUp(fl)  CAL_CMGETAPI( "VarAccBrowseUp" ) 
	#define CAL_VarAccBrowseUp  VarAccBrowseUp
	#define CHK_VarAccBrowseUp  TRUE
	#define EXP_VarAccBrowseUp  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccBrowseUp", (RTS_UINTPTR)VarAccBrowseUp, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccBrowseUp
	#define EXT_IecVarAccess_ItfsVarAccBrowseUp
	#define GET_IecVarAccess_ItfsVarAccBrowseUp  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccBrowseUp pIIecVarAccess_Itfs->IVarAccBrowseUp
	#define CHK_IecVarAccess_ItfsVarAccBrowseUp (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccBrowseUp  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccBrowseUp
	#define EXT_VarAccBrowseUp
	#define GET_VarAccBrowseUp(fl)  CAL_CMGETAPI( "VarAccBrowseUp" ) 
	#define CAL_VarAccBrowseUp pIIecVarAccess_Itfs->IVarAccBrowseUp
	#define CHK_VarAccBrowseUp (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccBrowseUp  CAL_CMEXPAPI( "VarAccBrowseUp" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccBrowseUp  PFVARACCBROWSEUP pfVarAccBrowseUp;
	#define EXT_VarAccBrowseUp  extern PFVARACCBROWSEUP pfVarAccBrowseUp;
	#define GET_VarAccBrowseUp(fl)  s_pfCMGetAPI2( "VarAccBrowseUp", (RTS_VOID_FCTPTR *)&pfVarAccBrowseUp, (fl), 0, 0)
	#define CAL_VarAccBrowseUp  pfVarAccBrowseUp
	#define CHK_VarAccBrowseUp  (pfVarAccBrowseUp != NULL)
	#define EXP_VarAccBrowseUp  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccBrowseUp", (RTS_UINTPTR)VarAccBrowseUp, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccGetSize2</description>
 */
typedef struct tagiiecvaraccess4_varaccgetsize2_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_XWORD dwOffset;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_XWORD VarAccGetSize2;		/* VAR_OUTPUT */	
} iiecvaraccess4_varaccgetsize2_struct;

void CDECL VarAccGetSize2(iiecvaraccess4_varaccgetsize2_struct *p);
typedef void (CDECL * PFVARACCGETSIZE2) (iiecvaraccess4_varaccgetsize2_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETSIZE2_NOTIMPLEMENTED)
	#define USE_VarAccGetSize2
	#define EXT_VarAccGetSize2
	#define GET_VarAccGetSize2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetSize2(p0)  
	#define CHK_VarAccGetSize2  FALSE
	#define EXP_VarAccGetSize2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetSize2
	#define EXT_VarAccGetSize2
	#define GET_VarAccGetSize2(fl)  CAL_CMGETAPI( "VarAccGetSize2" ) 
	#define CAL_VarAccGetSize2  VarAccGetSize2
	#define CHK_VarAccGetSize2  TRUE
	#define EXP_VarAccGetSize2  CAL_CMEXPAPI( "VarAccGetSize2" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetSize2
	#define EXT_VarAccGetSize2
	#define GET_VarAccGetSize2(fl)  CAL_CMGETAPI( "VarAccGetSize2" ) 
	#define CAL_VarAccGetSize2  VarAccGetSize2
	#define CHK_VarAccGetSize2  TRUE
	#define EXP_VarAccGetSize2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetSize2", (RTS_UINTPTR)VarAccGetSize2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetSize2
	#define EXT_IecVarAccess_ItfsVarAccGetSize2
	#define GET_IecVarAccess_ItfsVarAccGetSize2  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetSize2 pIIecVarAccess_Itfs->IVarAccGetSize2
	#define CHK_IecVarAccess_ItfsVarAccGetSize2 (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetSize2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetSize2
	#define EXT_VarAccGetSize2
	#define GET_VarAccGetSize2(fl)  CAL_CMGETAPI( "VarAccGetSize2" ) 
	#define CAL_VarAccGetSize2 pIIecVarAccess_Itfs->IVarAccGetSize2
	#define CHK_VarAccGetSize2 (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetSize2  CAL_CMEXPAPI( "VarAccGetSize2" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetSize2  PFVARACCGETSIZE2 pfVarAccGetSize2;
	#define EXT_VarAccGetSize2  extern PFVARACCGETSIZE2 pfVarAccGetSize2;
	#define GET_VarAccGetSize2(fl)  s_pfCMGetAPI2( "VarAccGetSize2", (RTS_VOID_FCTPTR *)&pfVarAccGetSize2, (fl), 0, 0)
	#define CAL_VarAccGetSize2  pfVarAccGetSize2
	#define CHK_VarAccGetSize2  (pfVarAccGetSize2 != NULL)
	#define EXP_VarAccGetSize2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetSize2", (RTS_UINTPTR)VarAccGetSize2, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccGetAddress</description>
 */
typedef struct tagiiecvaraccess4_varaccgetaddress_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_BYTE *VarAccGetAddress;		/* VAR_OUTPUT */	
} iiecvaraccess4_varaccgetaddress_struct;

void CDECL VarAccGetAddress(iiecvaraccess4_varaccgetaddress_struct *p);
typedef void (CDECL * PFVARACCGETADDRESS) (iiecvaraccess4_varaccgetaddress_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETADDRESS_NOTIMPLEMENTED)
	#define USE_VarAccGetAddress
	#define EXT_VarAccGetAddress
	#define GET_VarAccGetAddress(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetAddress(p0)  
	#define CHK_VarAccGetAddress  FALSE
	#define EXP_VarAccGetAddress  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetAddress
	#define EXT_VarAccGetAddress
	#define GET_VarAccGetAddress(fl)  CAL_CMGETAPI( "VarAccGetAddress" ) 
	#define CAL_VarAccGetAddress  VarAccGetAddress
	#define CHK_VarAccGetAddress  TRUE
	#define EXP_VarAccGetAddress  CAL_CMEXPAPI( "VarAccGetAddress" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetAddress
	#define EXT_VarAccGetAddress
	#define GET_VarAccGetAddress(fl)  CAL_CMGETAPI( "VarAccGetAddress" ) 
	#define CAL_VarAccGetAddress  VarAccGetAddress
	#define CHK_VarAccGetAddress  TRUE
	#define EXP_VarAccGetAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetAddress", (RTS_UINTPTR)VarAccGetAddress, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetAddress
	#define EXT_IecVarAccess_ItfsVarAccGetAddress
	#define GET_IecVarAccess_ItfsVarAccGetAddress  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetAddress pIIecVarAccess_Itfs->IVarAccGetAddress
	#define CHK_IecVarAccess_ItfsVarAccGetAddress (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetAddress  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetAddress
	#define EXT_VarAccGetAddress
	#define GET_VarAccGetAddress(fl)  CAL_CMGETAPI( "VarAccGetAddress" ) 
	#define CAL_VarAccGetAddress pIIecVarAccess_Itfs->IVarAccGetAddress
	#define CHK_VarAccGetAddress (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetAddress  CAL_CMEXPAPI( "VarAccGetAddress" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetAddress  PFVARACCGETADDRESS pfVarAccGetAddress;
	#define EXT_VarAccGetAddress  extern PFVARACCGETADDRESS pfVarAccGetAddress;
	#define GET_VarAccGetAddress(fl)  s_pfCMGetAPI2( "VarAccGetAddress", (RTS_VOID_FCTPTR *)&pfVarAccGetAddress, (fl), 0, 0)
	#define CAL_VarAccGetAddress  pfVarAccGetAddress
	#define CHK_VarAccGetAddress  (pfVarAccGetAddress != NULL)
	#define EXP_VarAccGetAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetAddress", (RTS_UINTPTR)VarAccGetAddress, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccGetNodeName</description>
 */
typedef struct tagiiecvaraccess4_varaccgetnodename_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_STRING *VarAccGetNodeName;	/* VAR_OUTPUT */	
} iiecvaraccess4_varaccgetnodename_struct;

void CDECL VarAccGetNodeName(iiecvaraccess4_varaccgetnodename_struct *p);
typedef void (CDECL * PFVARACCGETNODENAME) (iiecvaraccess4_varaccgetnodename_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETNODENAME_NOTIMPLEMENTED)
	#define USE_VarAccGetNodeName
	#define EXT_VarAccGetNodeName
	#define GET_VarAccGetNodeName(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetNodeName(p0)  
	#define CHK_VarAccGetNodeName  FALSE
	#define EXP_VarAccGetNodeName  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetNodeName
	#define EXT_VarAccGetNodeName
	#define GET_VarAccGetNodeName(fl)  CAL_CMGETAPI( "VarAccGetNodeName" ) 
	#define CAL_VarAccGetNodeName  VarAccGetNodeName
	#define CHK_VarAccGetNodeName  TRUE
	#define EXP_VarAccGetNodeName  CAL_CMEXPAPI( "VarAccGetNodeName" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetNodeName
	#define EXT_VarAccGetNodeName
	#define GET_VarAccGetNodeName(fl)  CAL_CMGETAPI( "VarAccGetNodeName" ) 
	#define CAL_VarAccGetNodeName  VarAccGetNodeName
	#define CHK_VarAccGetNodeName  TRUE
	#define EXP_VarAccGetNodeName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNodeName", (RTS_UINTPTR)VarAccGetNodeName, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetNodeName
	#define EXT_IecVarAccess_ItfsVarAccGetNodeName
	#define GET_IecVarAccess_ItfsVarAccGetNodeName  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetNodeName pIIecVarAccess_Itfs->IVarAccGetNodeName
	#define CHK_IecVarAccess_ItfsVarAccGetNodeName (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetNodeName  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetNodeName
	#define EXT_VarAccGetNodeName
	#define GET_VarAccGetNodeName(fl)  CAL_CMGETAPI( "VarAccGetNodeName" ) 
	#define CAL_VarAccGetNodeName pIIecVarAccess_Itfs->IVarAccGetNodeName
	#define CHK_VarAccGetNodeName (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetNodeName  CAL_CMEXPAPI( "VarAccGetNodeName" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetNodeName  PFVARACCGETNODENAME pfVarAccGetNodeName;
	#define EXT_VarAccGetNodeName  extern PFVARACCGETNODENAME pfVarAccGetNodeName;
	#define GET_VarAccGetNodeName(fl)  s_pfCMGetAPI2( "VarAccGetNodeName", (RTS_VOID_FCTPTR *)&pfVarAccGetNodeName, (fl), 0, 0)
	#define CAL_VarAccGetNodeName  pfVarAccGetNodeName
	#define CHK_VarAccGetNodeName  (pfVarAccGetNodeName != NULL)
	#define EXP_VarAccGetNodeName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNodeName", (RTS_UINTPTR)VarAccGetNodeName, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccGetValue</description>
 */
typedef struct tagiiecvaraccess4_varaccgetvalue_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pDest;				/* VAR_INPUT */	
	RTS_IEC_XWORD dwOffset;				/* VAR_INPUT */	
	RTS_IEC_XWORD dwSize;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_XWORD VarAccGetValue;		/* VAR_OUTPUT */	
} iiecvaraccess4_varaccgetvalue_struct;

void CDECL VarAccGetValue(iiecvaraccess4_varaccgetvalue_struct *p);
typedef void (CDECL * PFVARACCGETVALUE) (iiecvaraccess4_varaccgetvalue_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETVALUE_NOTIMPLEMENTED)
	#define USE_VarAccGetValue
	#define EXT_VarAccGetValue
	#define GET_VarAccGetValue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetValue(p0)  
	#define CHK_VarAccGetValue  FALSE
	#define EXP_VarAccGetValue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetValue
	#define EXT_VarAccGetValue
	#define GET_VarAccGetValue(fl)  CAL_CMGETAPI( "VarAccGetValue" ) 
	#define CAL_VarAccGetValue  VarAccGetValue
	#define CHK_VarAccGetValue  TRUE
	#define EXP_VarAccGetValue  CAL_CMEXPAPI( "VarAccGetValue" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetValue
	#define EXT_VarAccGetValue
	#define GET_VarAccGetValue(fl)  CAL_CMGETAPI( "VarAccGetValue" ) 
	#define CAL_VarAccGetValue  VarAccGetValue
	#define CHK_VarAccGetValue  TRUE
	#define EXP_VarAccGetValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetValue", (RTS_UINTPTR)VarAccGetValue, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetValue
	#define EXT_IecVarAccess_ItfsVarAccGetValue
	#define GET_IecVarAccess_ItfsVarAccGetValue  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetValue pIIecVarAccess_Itfs->IVarAccGetValue
	#define CHK_IecVarAccess_ItfsVarAccGetValue (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetValue  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetValue
	#define EXT_VarAccGetValue
	#define GET_VarAccGetValue(fl)  CAL_CMGETAPI( "VarAccGetValue" ) 
	#define CAL_VarAccGetValue pIIecVarAccess_Itfs->IVarAccGetValue
	#define CHK_VarAccGetValue (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetValue  CAL_CMEXPAPI( "VarAccGetValue" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetValue  PFVARACCGETVALUE pfVarAccGetValue;
	#define EXT_VarAccGetValue  extern PFVARACCGETVALUE pfVarAccGetValue;
	#define GET_VarAccGetValue(fl)  s_pfCMGetAPI2( "VarAccGetValue", (RTS_VOID_FCTPTR *)&pfVarAccGetValue, (fl), 0, 0)
	#define CAL_VarAccGetValue  pfVarAccGetValue
	#define CHK_VarAccGetValue  (pfVarAccGetValue != NULL)
	#define EXP_VarAccGetValue  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetValue", (RTS_UINTPTR)VarAccGetValue, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccGetNode</description>
 */
typedef struct tagiiecvaraccess4_varaccgetnode_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_STRING *pszPath;			/* VAR_INPUT */	
	RTS_IEC_XWORD *pdwOffset;			/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	IBaseTreeNode *VarAccGetNode;		/* VAR_OUTPUT */	
} iiecvaraccess4_varaccgetnode_struct;

void CDECL VarAccGetNode(iiecvaraccess4_varaccgetnode_struct *p);
typedef void (CDECL * PFVARACCGETNODE) (iiecvaraccess4_varaccgetnode_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETNODE_NOTIMPLEMENTED)
	#define USE_VarAccGetNode
	#define EXT_VarAccGetNode
	#define GET_VarAccGetNode(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetNode(p0)  
	#define CHK_VarAccGetNode  FALSE
	#define EXP_VarAccGetNode  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetNode
	#define EXT_VarAccGetNode
	#define GET_VarAccGetNode(fl)  CAL_CMGETAPI( "VarAccGetNode" ) 
	#define CAL_VarAccGetNode  VarAccGetNode
	#define CHK_VarAccGetNode  TRUE
	#define EXP_VarAccGetNode  CAL_CMEXPAPI( "VarAccGetNode" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetNode
	#define EXT_VarAccGetNode
	#define GET_VarAccGetNode(fl)  CAL_CMGETAPI( "VarAccGetNode" ) 
	#define CAL_VarAccGetNode  VarAccGetNode
	#define CHK_VarAccGetNode  TRUE
	#define EXP_VarAccGetNode  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNode", (RTS_UINTPTR)VarAccGetNode, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetNode
	#define EXT_IecVarAccess_ItfsVarAccGetNode
	#define GET_IecVarAccess_ItfsVarAccGetNode  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetNode pIIecVarAccess_Itfs->IVarAccGetNode
	#define CHK_IecVarAccess_ItfsVarAccGetNode (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetNode  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetNode
	#define EXT_VarAccGetNode
	#define GET_VarAccGetNode(fl)  CAL_CMGETAPI( "VarAccGetNode" ) 
	#define CAL_VarAccGetNode pIIecVarAccess_Itfs->IVarAccGetNode
	#define CHK_VarAccGetNode (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetNode  CAL_CMEXPAPI( "VarAccGetNode" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetNode  PFVARACCGETNODE pfVarAccGetNode;
	#define EXT_VarAccGetNode  extern PFVARACCGETNODE pfVarAccGetNode;
	#define GET_VarAccGetNode(fl)  s_pfCMGetAPI2( "VarAccGetNode", (RTS_VOID_FCTPTR *)&pfVarAccGetNode, (fl), 0, 0)
	#define CAL_VarAccGetNode  pfVarAccGetNode
	#define CHK_VarAccGetNode  (pfVarAccGetNode != NULL)
	#define EXP_VarAccGetNode  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNode", (RTS_UINTPTR)VarAccGetNode, 0, 0) 
#endif




/**
 * <description>IIecVarAccess4::VarAccGetTypeClass</description>
 */
typedef struct tagiiecvaraccess4_varaccgettypeclass_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	RTS_IEC_INT VarAccGetTypeClass;		/* VAR_OUTPUT, Enum: TYPECLASS */
} iiecvaraccess4_varaccgettypeclass_struct;

void CDECL VarAccGetTypeClass(iiecvaraccess4_varaccgettypeclass_struct *p);
typedef void (CDECL * PFVARACCGETTYPECLASS) (iiecvaraccess4_varaccgettypeclass_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETTYPECLASS_NOTIMPLEMENTED)
	#define USE_VarAccGetTypeClass
	#define EXT_VarAccGetTypeClass
	#define GET_VarAccGetTypeClass(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetTypeClass(p0)  
	#define CHK_VarAccGetTypeClass  FALSE
	#define EXP_VarAccGetTypeClass  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetTypeClass
	#define EXT_VarAccGetTypeClass
	#define GET_VarAccGetTypeClass(fl)  CAL_CMGETAPI( "VarAccGetTypeClass" ) 
	#define CAL_VarAccGetTypeClass  VarAccGetTypeClass
	#define CHK_VarAccGetTypeClass  TRUE
	#define EXP_VarAccGetTypeClass  CAL_CMEXPAPI( "VarAccGetTypeClass" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetTypeClass
	#define EXT_VarAccGetTypeClass
	#define GET_VarAccGetTypeClass(fl)  CAL_CMGETAPI( "VarAccGetTypeClass" ) 
	#define CAL_VarAccGetTypeClass  VarAccGetTypeClass
	#define CHK_VarAccGetTypeClass  TRUE
	#define EXP_VarAccGetTypeClass  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetTypeClass", (RTS_UINTPTR)VarAccGetTypeClass, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetTypeClass
	#define EXT_IecVarAccess_ItfsVarAccGetTypeClass
	#define GET_IecVarAccess_ItfsVarAccGetTypeClass  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetTypeClass pIIecVarAccess_Itfs->IVarAccGetTypeClass
	#define CHK_IecVarAccess_ItfsVarAccGetTypeClass (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetTypeClass  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetTypeClass
	#define EXT_VarAccGetTypeClass
	#define GET_VarAccGetTypeClass(fl)  CAL_CMGETAPI( "VarAccGetTypeClass" ) 
	#define CAL_VarAccGetTypeClass pIIecVarAccess_Itfs->IVarAccGetTypeClass
	#define CHK_VarAccGetTypeClass (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetTypeClass  CAL_CMEXPAPI( "VarAccGetTypeClass" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetTypeClass  PFVARACCGETTYPECLASS pfVarAccGetTypeClass;
	#define EXT_VarAccGetTypeClass  extern PFVARACCGETTYPECLASS pfVarAccGetTypeClass;
	#define GET_VarAccGetTypeClass(fl)  s_pfCMGetAPI2( "VarAccGetTypeClass", (RTS_VOID_FCTPTR *)&pfVarAccGetTypeClass, (fl), 0, 0)
	#define CAL_VarAccGetTypeClass  pfVarAccGetTypeClass
	#define CHK_VarAccGetTypeClass  (pfVarAccGetTypeClass != NULL)
	#define EXP_VarAccGetTypeClass  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetTypeClass", (RTS_UINTPTR)VarAccGetTypeClass, 0, 0) 
#endif




typedef struct
{
	void* __VFTABLEPOINTER;	/* Pointer to virtual function table */
} iiecvaraccess5_struct;

/**
 * <description>IIecVarAccess5::VarAccGetSize3</description>
 */
typedef struct tagiiecvaraccess5_varaccgetsize3_struct
{
	iiecvaraccess5_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	VariableInformationStruct *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_XWORD VarAccGetSize3;		/* VAR_OUTPUT */	
} iiecvaraccess5_varaccgetsize3_struct;

void CDECL VarAccGetSize3(iiecvaraccess5_varaccgetsize3_struct *p);
typedef void (CDECL * PFVARACCGETSIZE3) (iiecvaraccess5_varaccgetsize3_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETSIZE3_NOTIMPLEMENTED)
	#define USE_VarAccGetSize3
	#define EXT_VarAccGetSize3
	#define GET_VarAccGetSize3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetSize3(p0)  
	#define CHK_VarAccGetSize3  FALSE
	#define EXP_VarAccGetSize3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetSize3
	#define EXT_VarAccGetSize3
	#define GET_VarAccGetSize3(fl)  CAL_CMGETAPI( "VarAccGetSize3" ) 
	#define CAL_VarAccGetSize3  VarAccGetSize3
	#define CHK_VarAccGetSize3  TRUE
	#define EXP_VarAccGetSize3  CAL_CMEXPAPI( "VarAccGetSize3" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetSize3
	#define EXT_VarAccGetSize3
	#define GET_VarAccGetSize3(fl)  CAL_CMGETAPI( "VarAccGetSize3" ) 
	#define CAL_VarAccGetSize3  VarAccGetSize3
	#define CHK_VarAccGetSize3  TRUE
	#define EXP_VarAccGetSize3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetSize3", (RTS_UINTPTR)VarAccGetSize3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetSize3
	#define EXT_IecVarAccess_ItfsVarAccGetSize3
	#define GET_IecVarAccess_ItfsVarAccGetSize3  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetSize3 pIIecVarAccess_Itfs->IVarAccGetSize3
	#define CHK_IecVarAccess_ItfsVarAccGetSize3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetSize3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetSize3
	#define EXT_VarAccGetSize3
	#define GET_VarAccGetSize3(fl)  CAL_CMGETAPI( "VarAccGetSize3" ) 
	#define CAL_VarAccGetSize3 pIIecVarAccess_Itfs->IVarAccGetSize3
	#define CHK_VarAccGetSize3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetSize3  CAL_CMEXPAPI( "VarAccGetSize3" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetSize3  PFVARACCGETSIZE3 pfVarAccGetSize3;
	#define EXT_VarAccGetSize3  extern PFVARACCGETSIZE3 pfVarAccGetSize3;
	#define GET_VarAccGetSize3(fl)  s_pfCMGetAPI2( "VarAccGetSize3", (RTS_VOID_FCTPTR *)&pfVarAccGetSize3, (fl), 0, 0)
	#define CAL_VarAccGetSize3  pfVarAccGetSize3
	#define CHK_VarAccGetSize3  (pfVarAccGetSize3 != NULL)
	#define EXP_VarAccGetSize3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetSize3", (RTS_UINTPTR)VarAccGetSize3, 0, 0) 
#endif




/**
 * <description>IIecVarAccess5::VarAccGetNodeFullPath3</description>
 */
typedef struct tagiiecvaraccess5_varaccgetnodefullpath3_struct
{
	iiecvaraccess5_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	VariableInformationStruct *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_STRING *pszPath;			/* VAR_INPUT */	
	RTS_IEC_DINT diMaxPath;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_DINT VarAccGetNodeFullPath3;	/* VAR_OUTPUT */	
} iiecvaraccess5_varaccgetnodefullpath3_struct;

void CDECL VarAccGetNodeFullPath3(iiecvaraccess5_varaccgetnodefullpath3_struct *p);
typedef void (CDECL * PFVARACCGETNODEFULLPATH3) (iiecvaraccess5_varaccgetnodefullpath3_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETNODEFULLPATH3_NOTIMPLEMENTED)
	#define USE_VarAccGetNodeFullPath3
	#define EXT_VarAccGetNodeFullPath3
	#define GET_VarAccGetNodeFullPath3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetNodeFullPath3(p0)  
	#define CHK_VarAccGetNodeFullPath3  FALSE
	#define EXP_VarAccGetNodeFullPath3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetNodeFullPath3
	#define EXT_VarAccGetNodeFullPath3
	#define GET_VarAccGetNodeFullPath3(fl)  CAL_CMGETAPI( "VarAccGetNodeFullPath3" ) 
	#define CAL_VarAccGetNodeFullPath3  VarAccGetNodeFullPath3
	#define CHK_VarAccGetNodeFullPath3  TRUE
	#define EXP_VarAccGetNodeFullPath3  CAL_CMEXPAPI( "VarAccGetNodeFullPath3" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetNodeFullPath3
	#define EXT_VarAccGetNodeFullPath3
	#define GET_VarAccGetNodeFullPath3(fl)  CAL_CMGETAPI( "VarAccGetNodeFullPath3" ) 
	#define CAL_VarAccGetNodeFullPath3  VarAccGetNodeFullPath3
	#define CHK_VarAccGetNodeFullPath3  TRUE
	#define EXP_VarAccGetNodeFullPath3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNodeFullPath3", (RTS_UINTPTR)VarAccGetNodeFullPath3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetNodeFullPath3
	#define EXT_IecVarAccess_ItfsVarAccGetNodeFullPath3
	#define GET_IecVarAccess_ItfsVarAccGetNodeFullPath3  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetNodeFullPath3 pIIecVarAccess_Itfs->IVarAccGetNodeFullPath3
	#define CHK_IecVarAccess_ItfsVarAccGetNodeFullPath3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetNodeFullPath3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetNodeFullPath3
	#define EXT_VarAccGetNodeFullPath3
	#define GET_VarAccGetNodeFullPath3(fl)  CAL_CMGETAPI( "VarAccGetNodeFullPath3" ) 
	#define CAL_VarAccGetNodeFullPath3 pIIecVarAccess_Itfs->IVarAccGetNodeFullPath3
	#define CHK_VarAccGetNodeFullPath3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetNodeFullPath3  CAL_CMEXPAPI( "VarAccGetNodeFullPath3" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetNodeFullPath3  PFVARACCGETNODEFULLPATH3 pfVarAccGetNodeFullPath3;
	#define EXT_VarAccGetNodeFullPath3  extern PFVARACCGETNODEFULLPATH3 pfVarAccGetNodeFullPath3;
	#define GET_VarAccGetNodeFullPath3(fl)  s_pfCMGetAPI2( "VarAccGetNodeFullPath3", (RTS_VOID_FCTPTR *)&pfVarAccGetNodeFullPath3, (fl), 0, 0)
	#define CAL_VarAccGetNodeFullPath3  pfVarAccGetNodeFullPath3
	#define CHK_VarAccGetNodeFullPath3  (pfVarAccGetNodeFullPath3 != NULL)
	#define EXP_VarAccGetNodeFullPath3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNodeFullPath3", (RTS_UINTPTR)VarAccGetNodeFullPath3, 0, 0) 
#endif




/**
 * <description>IIecVarAccess5::VarAccSetValue3</description>
 */
typedef struct tagiiecvaraccess5_varaccsetvalue3_struct
{
	iiecvaraccess5_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	VariableInformationStruct *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_BYTE *pSrc;					/* VAR_INPUT */	
	RTS_IEC_XWORD dwSize;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_XWORD VarAccSetValue3;		/* VAR_OUTPUT */	
} iiecvaraccess5_varaccsetvalue3_struct;

void CDECL VarAccSetValue3(iiecvaraccess5_varaccsetvalue3_struct *p);
typedef void (CDECL * PFVARACCSETVALUE3) (iiecvaraccess5_varaccsetvalue3_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCSETVALUE3_NOTIMPLEMENTED)
	#define USE_VarAccSetValue3
	#define EXT_VarAccSetValue3
	#define GET_VarAccSetValue3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccSetValue3(p0)  
	#define CHK_VarAccSetValue3  FALSE
	#define EXP_VarAccSetValue3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccSetValue3
	#define EXT_VarAccSetValue3
	#define GET_VarAccSetValue3(fl)  CAL_CMGETAPI( "VarAccSetValue3" ) 
	#define CAL_VarAccSetValue3  VarAccSetValue3
	#define CHK_VarAccSetValue3  TRUE
	#define EXP_VarAccSetValue3  CAL_CMEXPAPI( "VarAccSetValue3" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccSetValue3
	#define EXT_VarAccSetValue3
	#define GET_VarAccSetValue3(fl)  CAL_CMGETAPI( "VarAccSetValue3" ) 
	#define CAL_VarAccSetValue3  VarAccSetValue3
	#define CHK_VarAccSetValue3  TRUE
	#define EXP_VarAccSetValue3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccSetValue3", (RTS_UINTPTR)VarAccSetValue3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccSetValue3
	#define EXT_IecVarAccess_ItfsVarAccSetValue3
	#define GET_IecVarAccess_ItfsVarAccSetValue3  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccSetValue3 pIIecVarAccess_Itfs->IVarAccSetValue3
	#define CHK_IecVarAccess_ItfsVarAccSetValue3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccSetValue3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccSetValue3
	#define EXT_VarAccSetValue3
	#define GET_VarAccSetValue3(fl)  CAL_CMGETAPI( "VarAccSetValue3" ) 
	#define CAL_VarAccSetValue3 pIIecVarAccess_Itfs->IVarAccSetValue3
	#define CHK_VarAccSetValue3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccSetValue3  CAL_CMEXPAPI( "VarAccSetValue3" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccSetValue3  PFVARACCSETVALUE3 pfVarAccSetValue3;
	#define EXT_VarAccSetValue3  extern PFVARACCSETVALUE3 pfVarAccSetValue3;
	#define GET_VarAccSetValue3(fl)  s_pfCMGetAPI2( "VarAccSetValue3", (RTS_VOID_FCTPTR *)&pfVarAccSetValue3, (fl), 0, 0)
	#define CAL_VarAccSetValue3  pfVarAccSetValue3
	#define CHK_VarAccSetValue3  (pfVarAccSetValue3 != NULL)
	#define EXP_VarAccSetValue3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccSetValue3", (RTS_UINTPTR)VarAccSetValue3, 0, 0) 
#endif




/**
 * <description>IIecVarAccess5::VarAccGetAddress3</description>
 */
typedef struct tagiiecvaraccess5_varaccgetaddress3_struct
{
	iiecvaraccess5_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	VariableInformationStruct *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_BYTE *VarAccGetAddress3;	/* VAR_OUTPUT */	
} iiecvaraccess5_varaccgetaddress3_struct;

void CDECL VarAccGetAddress3(iiecvaraccess5_varaccgetaddress3_struct *p);
typedef void (CDECL * PFVARACCGETADDRESS3) (iiecvaraccess5_varaccgetaddress3_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETADDRESS3_NOTIMPLEMENTED)
	#define USE_VarAccGetAddress3
	#define EXT_VarAccGetAddress3
	#define GET_VarAccGetAddress3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetAddress3(p0)  
	#define CHK_VarAccGetAddress3  FALSE
	#define EXP_VarAccGetAddress3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetAddress3
	#define EXT_VarAccGetAddress3
	#define GET_VarAccGetAddress3(fl)  CAL_CMGETAPI( "VarAccGetAddress3" ) 
	#define CAL_VarAccGetAddress3  VarAccGetAddress3
	#define CHK_VarAccGetAddress3  TRUE
	#define EXP_VarAccGetAddress3  CAL_CMEXPAPI( "VarAccGetAddress3" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetAddress3
	#define EXT_VarAccGetAddress3
	#define GET_VarAccGetAddress3(fl)  CAL_CMGETAPI( "VarAccGetAddress3" ) 
	#define CAL_VarAccGetAddress3  VarAccGetAddress3
	#define CHK_VarAccGetAddress3  TRUE
	#define EXP_VarAccGetAddress3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetAddress3", (RTS_UINTPTR)VarAccGetAddress3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetAddress3
	#define EXT_IecVarAccess_ItfsVarAccGetAddress3
	#define GET_IecVarAccess_ItfsVarAccGetAddress3  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetAddress3 pIIecVarAccess_Itfs->IVarAccGetAddress3
	#define CHK_IecVarAccess_ItfsVarAccGetAddress3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetAddress3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetAddress3
	#define EXT_VarAccGetAddress3
	#define GET_VarAccGetAddress3(fl)  CAL_CMGETAPI( "VarAccGetAddress3" ) 
	#define CAL_VarAccGetAddress3 pIIecVarAccess_Itfs->IVarAccGetAddress3
	#define CHK_VarAccGetAddress3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetAddress3  CAL_CMEXPAPI( "VarAccGetAddress3" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetAddress3  PFVARACCGETADDRESS3 pfVarAccGetAddress3;
	#define EXT_VarAccGetAddress3  extern PFVARACCGETADDRESS3 pfVarAccGetAddress3;
	#define GET_VarAccGetAddress3(fl)  s_pfCMGetAPI2( "VarAccGetAddress3", (RTS_VOID_FCTPTR *)&pfVarAccGetAddress3, (fl), 0, 0)
	#define CAL_VarAccGetAddress3  pfVarAccGetAddress3
	#define CHK_VarAccGetAddress3  (pfVarAccGetAddress3 != NULL)
	#define EXP_VarAccGetAddress3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetAddress3", (RTS_UINTPTR)VarAccGetAddress3, 0, 0) 
#endif




/**
 * <description>IIecVarAccess5::VarAccAppendVariable3</description>
 */
typedef struct tagiiecvaraccess5_varaccappendvariable3_struct
{
	iiecvaraccess5_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	VariableInformationStruct *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT VarAccAppendVariable3;	/* VAR_OUTPUT */	
} iiecvaraccess5_varaccappendvariable3_struct;

void CDECL VarAccAppendVariable3(iiecvaraccess5_varaccappendvariable3_struct *p);
typedef void (CDECL * PFVARACCAPPENDVARIABLE3) (iiecvaraccess5_varaccappendvariable3_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCAPPENDVARIABLE3_NOTIMPLEMENTED)
	#define USE_VarAccAppendVariable3
	#define EXT_VarAccAppendVariable3
	#define GET_VarAccAppendVariable3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccAppendVariable3(p0)  
	#define CHK_VarAccAppendVariable3  FALSE
	#define EXP_VarAccAppendVariable3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccAppendVariable3
	#define EXT_VarAccAppendVariable3
	#define GET_VarAccAppendVariable3(fl)  CAL_CMGETAPI( "VarAccAppendVariable3" ) 
	#define CAL_VarAccAppendVariable3  VarAccAppendVariable3
	#define CHK_VarAccAppendVariable3  TRUE
	#define EXP_VarAccAppendVariable3  CAL_CMEXPAPI( "VarAccAppendVariable3" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccAppendVariable3
	#define EXT_VarAccAppendVariable3
	#define GET_VarAccAppendVariable3(fl)  CAL_CMGETAPI( "VarAccAppendVariable3" ) 
	#define CAL_VarAccAppendVariable3  VarAccAppendVariable3
	#define CHK_VarAccAppendVariable3  TRUE
	#define EXP_VarAccAppendVariable3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccAppendVariable3", (RTS_UINTPTR)VarAccAppendVariable3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccAppendVariable3
	#define EXT_IecVarAccess_ItfsVarAccAppendVariable3
	#define GET_IecVarAccess_ItfsVarAccAppendVariable3  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccAppendVariable3 pIIecVarAccess_Itfs->IVarAccAppendVariable3
	#define CHK_IecVarAccess_ItfsVarAccAppendVariable3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccAppendVariable3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccAppendVariable3
	#define EXT_VarAccAppendVariable3
	#define GET_VarAccAppendVariable3(fl)  CAL_CMGETAPI( "VarAccAppendVariable3" ) 
	#define CAL_VarAccAppendVariable3 pIIecVarAccess_Itfs->IVarAccAppendVariable3
	#define CHK_VarAccAppendVariable3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccAppendVariable3  CAL_CMEXPAPI( "VarAccAppendVariable3" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccAppendVariable3  PFVARACCAPPENDVARIABLE3 pfVarAccAppendVariable3;
	#define EXT_VarAccAppendVariable3  extern PFVARACCAPPENDVARIABLE3 pfVarAccAppendVariable3;
	#define GET_VarAccAppendVariable3(fl)  s_pfCMGetAPI2( "VarAccAppendVariable3", (RTS_VOID_FCTPTR *)&pfVarAccAppendVariable3, (fl), 0, 0)
	#define CAL_VarAccAppendVariable3  pfVarAccAppendVariable3
	#define CHK_VarAccAppendVariable3  (pfVarAccAppendVariable3 != NULL)
	#define EXP_VarAccAppendVariable3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccAppendVariable3", (RTS_UINTPTR)VarAccAppendVariable3, 0, 0) 
#endif




/**
 * <description>IIecVarAccess5::VarAccGetValue3</description>
 */
typedef struct tagiiecvaraccess5_varaccgetvalue3_struct
{
	iiecvaraccess5_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	VariableInformationStruct *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_BYTE *pDest;				/* VAR_INPUT */	
	RTS_IEC_XWORD dwSize;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_XWORD VarAccGetValue3;		/* VAR_OUTPUT */	
} iiecvaraccess5_varaccgetvalue3_struct;

void CDECL VarAccGetValue3(iiecvaraccess5_varaccgetvalue3_struct *p);
typedef void (CDECL * PFVARACCGETVALUE3) (iiecvaraccess5_varaccgetvalue3_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETVALUE3_NOTIMPLEMENTED)
	#define USE_VarAccGetValue3
	#define EXT_VarAccGetValue3
	#define GET_VarAccGetValue3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetValue3(p0)  
	#define CHK_VarAccGetValue3  FALSE
	#define EXP_VarAccGetValue3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetValue3
	#define EXT_VarAccGetValue3
	#define GET_VarAccGetValue3(fl)  CAL_CMGETAPI( "VarAccGetValue3" ) 
	#define CAL_VarAccGetValue3  VarAccGetValue3
	#define CHK_VarAccGetValue3  TRUE
	#define EXP_VarAccGetValue3  CAL_CMEXPAPI( "VarAccGetValue3" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetValue3
	#define EXT_VarAccGetValue3
	#define GET_VarAccGetValue3(fl)  CAL_CMGETAPI( "VarAccGetValue3" ) 
	#define CAL_VarAccGetValue3  VarAccGetValue3
	#define CHK_VarAccGetValue3  TRUE
	#define EXP_VarAccGetValue3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetValue3", (RTS_UINTPTR)VarAccGetValue3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetValue3
	#define EXT_IecVarAccess_ItfsVarAccGetValue3
	#define GET_IecVarAccess_ItfsVarAccGetValue3  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetValue3 pIIecVarAccess_Itfs->IVarAccGetValue3
	#define CHK_IecVarAccess_ItfsVarAccGetValue3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetValue3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetValue3
	#define EXT_VarAccGetValue3
	#define GET_VarAccGetValue3(fl)  CAL_CMGETAPI( "VarAccGetValue3" ) 
	#define CAL_VarAccGetValue3 pIIecVarAccess_Itfs->IVarAccGetValue3
	#define CHK_VarAccGetValue3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetValue3  CAL_CMEXPAPI( "VarAccGetValue3" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetValue3  PFVARACCGETVALUE3 pfVarAccGetValue3;
	#define EXT_VarAccGetValue3  extern PFVARACCGETVALUE3 pfVarAccGetValue3;
	#define GET_VarAccGetValue3(fl)  s_pfCMGetAPI2( "VarAccGetValue3", (RTS_VOID_FCTPTR *)&pfVarAccGetValue3, (fl), 0, 0)
	#define CAL_VarAccGetValue3  pfVarAccGetValue3
	#define CHK_VarAccGetValue3  (pfVarAccGetValue3 != NULL)
	#define EXP_VarAccGetValue3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetValue3", (RTS_UINTPTR)VarAccGetValue3, 0, 0) 
#endif




/**
 * <description>IIecVarAccess5::VarAccGetNode3</description>
 */
typedef struct tagiiecvaraccess5_varaccgetnode3_struct
{
	iiecvaraccess5_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_STRING *pszPath;			/* VAR_INPUT */	
	VariableInformationStruct *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	IBaseTreeNode *VarAccGetNode3;		/* VAR_OUTPUT */	
} iiecvaraccess5_varaccgetnode3_struct;

void CDECL VarAccGetNode3(iiecvaraccess5_varaccgetnode3_struct *p);
typedef void (CDECL * PFVARACCGETNODE3) (iiecvaraccess5_varaccgetnode3_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETNODE3_NOTIMPLEMENTED)
	#define USE_VarAccGetNode3
	#define EXT_VarAccGetNode3
	#define GET_VarAccGetNode3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetNode3(p0)  
	#define CHK_VarAccGetNode3  FALSE
	#define EXP_VarAccGetNode3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetNode3
	#define EXT_VarAccGetNode3
	#define GET_VarAccGetNode3(fl)  CAL_CMGETAPI( "VarAccGetNode3" ) 
	#define CAL_VarAccGetNode3  VarAccGetNode3
	#define CHK_VarAccGetNode3  TRUE
	#define EXP_VarAccGetNode3  CAL_CMEXPAPI( "VarAccGetNode3" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetNode3
	#define EXT_VarAccGetNode3
	#define GET_VarAccGetNode3(fl)  CAL_CMGETAPI( "VarAccGetNode3" ) 
	#define CAL_VarAccGetNode3  VarAccGetNode3
	#define CHK_VarAccGetNode3  TRUE
	#define EXP_VarAccGetNode3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNode3", (RTS_UINTPTR)VarAccGetNode3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetNode3
	#define EXT_IecVarAccess_ItfsVarAccGetNode3
	#define GET_IecVarAccess_ItfsVarAccGetNode3  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetNode3 pIIecVarAccess_Itfs->IVarAccGetNode3
	#define CHK_IecVarAccess_ItfsVarAccGetNode3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetNode3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetNode3
	#define EXT_VarAccGetNode3
	#define GET_VarAccGetNode3(fl)  CAL_CMGETAPI( "VarAccGetNode3" ) 
	#define CAL_VarAccGetNode3 pIIecVarAccess_Itfs->IVarAccGetNode3
	#define CHK_VarAccGetNode3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetNode3  CAL_CMEXPAPI( "VarAccGetNode3" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetNode3  PFVARACCGETNODE3 pfVarAccGetNode3;
	#define EXT_VarAccGetNode3  extern PFVARACCGETNODE3 pfVarAccGetNode3;
	#define GET_VarAccGetNode3(fl)  s_pfCMGetAPI2( "VarAccGetNode3", (RTS_VOID_FCTPTR *)&pfVarAccGetNode3, (fl), 0, 0)
	#define CAL_VarAccGetNode3  pfVarAccGetNode3
	#define CHK_VarAccGetNode3  (pfVarAccGetNode3 != NULL)
	#define EXP_VarAccGetNode3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNode3", (RTS_UINTPTR)VarAccGetNode3, 0, 0) 
#endif




/**
 * <description>IIecVarAccess5::VarAccGetTypeNode3</description>
 */
typedef struct tagiiecvaraccess5_varaccgettypenode3_struct
{
	iiecvaraccess5_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	VariableInformationStruct *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	ITypeDesc *VarAccGetTypeNode3;		/* VAR_OUTPUT */	
} iiecvaraccess5_varaccgettypenode3_struct;

void CDECL VarAccGetTypeNode3(iiecvaraccess5_varaccgettypenode3_struct *p);
typedef void (CDECL * PFVARACCGETTYPENODE3) (iiecvaraccess5_varaccgettypenode3_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETTYPENODE3_NOTIMPLEMENTED)
	#define USE_VarAccGetTypeNode3
	#define EXT_VarAccGetTypeNode3
	#define GET_VarAccGetTypeNode3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetTypeNode3(p0)  
	#define CHK_VarAccGetTypeNode3  FALSE
	#define EXP_VarAccGetTypeNode3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetTypeNode3
	#define EXT_VarAccGetTypeNode3
	#define GET_VarAccGetTypeNode3(fl)  CAL_CMGETAPI( "VarAccGetTypeNode3" ) 
	#define CAL_VarAccGetTypeNode3  VarAccGetTypeNode3
	#define CHK_VarAccGetTypeNode3  TRUE
	#define EXP_VarAccGetTypeNode3  CAL_CMEXPAPI( "VarAccGetTypeNode3" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetTypeNode3
	#define EXT_VarAccGetTypeNode3
	#define GET_VarAccGetTypeNode3(fl)  CAL_CMGETAPI( "VarAccGetTypeNode3" ) 
	#define CAL_VarAccGetTypeNode3  VarAccGetTypeNode3
	#define CHK_VarAccGetTypeNode3  TRUE
	#define EXP_VarAccGetTypeNode3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetTypeNode3", (RTS_UINTPTR)VarAccGetTypeNode3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetTypeNode3
	#define EXT_IecVarAccess_ItfsVarAccGetTypeNode3
	#define GET_IecVarAccess_ItfsVarAccGetTypeNode3  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetTypeNode3 pIIecVarAccess_Itfs->IVarAccGetTypeNode3
	#define CHK_IecVarAccess_ItfsVarAccGetTypeNode3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetTypeNode3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetTypeNode3
	#define EXT_VarAccGetTypeNode3
	#define GET_VarAccGetTypeNode3(fl)  CAL_CMGETAPI( "VarAccGetTypeNode3" ) 
	#define CAL_VarAccGetTypeNode3 pIIecVarAccess_Itfs->IVarAccGetTypeNode3
	#define CHK_VarAccGetTypeNode3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetTypeNode3  CAL_CMEXPAPI( "VarAccGetTypeNode3" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetTypeNode3  PFVARACCGETTYPENODE3 pfVarAccGetTypeNode3;
	#define EXT_VarAccGetTypeNode3  extern PFVARACCGETTYPENODE3 pfVarAccGetTypeNode3;
	#define GET_VarAccGetTypeNode3(fl)  s_pfCMGetAPI2( "VarAccGetTypeNode3", (RTS_VOID_FCTPTR *)&pfVarAccGetTypeNode3, (fl), 0, 0)
	#define CAL_VarAccGetTypeNode3  pfVarAccGetTypeNode3
	#define CHK_VarAccGetTypeNode3  (pfVarAccGetTypeNode3 != NULL)
	#define EXP_VarAccGetTypeNode3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetTypeNode3", (RTS_UINTPTR)VarAccGetTypeNode3, 0, 0) 
#endif




/**
 * <description>IIecVarAccess5::VarAccGetTypeClass3</description>
 */
typedef struct tagiiecvaraccess5_varaccgettypeclass3_struct
{
	iiecvaraccess5_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	VariableInformationStruct *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_INT VarAccGetTypeClass3;	/* VAR_OUTPUT, Enum: TYPECLASS */
} iiecvaraccess5_varaccgettypeclass3_struct;

void CDECL VarAccGetTypeClass3(iiecvaraccess5_varaccgettypeclass3_struct *p);
typedef void (CDECL * PFVARACCGETTYPECLASS3) (iiecvaraccess5_varaccgettypeclass3_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETTYPECLASS3_NOTIMPLEMENTED)
	#define USE_VarAccGetTypeClass3
	#define EXT_VarAccGetTypeClass3
	#define GET_VarAccGetTypeClass3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetTypeClass3(p0)  
	#define CHK_VarAccGetTypeClass3  FALSE
	#define EXP_VarAccGetTypeClass3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetTypeClass3
	#define EXT_VarAccGetTypeClass3
	#define GET_VarAccGetTypeClass3(fl)  CAL_CMGETAPI( "VarAccGetTypeClass3" ) 
	#define CAL_VarAccGetTypeClass3  VarAccGetTypeClass3
	#define CHK_VarAccGetTypeClass3  TRUE
	#define EXP_VarAccGetTypeClass3  CAL_CMEXPAPI( "VarAccGetTypeClass3" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetTypeClass3
	#define EXT_VarAccGetTypeClass3
	#define GET_VarAccGetTypeClass3(fl)  CAL_CMGETAPI( "VarAccGetTypeClass3" ) 
	#define CAL_VarAccGetTypeClass3  VarAccGetTypeClass3
	#define CHK_VarAccGetTypeClass3  TRUE
	#define EXP_VarAccGetTypeClass3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetTypeClass3", (RTS_UINTPTR)VarAccGetTypeClass3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetTypeClass3
	#define EXT_IecVarAccess_ItfsVarAccGetTypeClass3
	#define GET_IecVarAccess_ItfsVarAccGetTypeClass3  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetTypeClass3 pIIecVarAccess_Itfs->IVarAccGetTypeClass3
	#define CHK_IecVarAccess_ItfsVarAccGetTypeClass3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetTypeClass3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetTypeClass3
	#define EXT_VarAccGetTypeClass3
	#define GET_VarAccGetTypeClass3(fl)  CAL_CMGETAPI( "VarAccGetTypeClass3" ) 
	#define CAL_VarAccGetTypeClass3 pIIecVarAccess_Itfs->IVarAccGetTypeClass3
	#define CHK_VarAccGetTypeClass3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetTypeClass3  CAL_CMEXPAPI( "VarAccGetTypeClass3" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetTypeClass3  PFVARACCGETTYPECLASS3 pfVarAccGetTypeClass3;
	#define EXT_VarAccGetTypeClass3  extern PFVARACCGETTYPECLASS3 pfVarAccGetTypeClass3;
	#define GET_VarAccGetTypeClass3(fl)  s_pfCMGetAPI2( "VarAccGetTypeClass3", (RTS_VOID_FCTPTR *)&pfVarAccGetTypeClass3, (fl), 0, 0)
	#define CAL_VarAccGetTypeClass3  pfVarAccGetTypeClass3
	#define CHK_VarAccGetTypeClass3  (pfVarAccGetTypeClass3 != NULL)
	#define EXP_VarAccGetTypeClass3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetTypeClass3", (RTS_UINTPTR)VarAccGetTypeClass3, 0, 0) 
#endif




/**
 * <description>IIecVarAccess5::VarAccRemoveVariable3</description>
 */
typedef struct tagiiecvaraccess5_varaccremovevariable3_struct
{
	iiecvaraccess5_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	VariableInformationStruct *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT VarAccRemoveVariable3;	/* VAR_OUTPUT */	
} iiecvaraccess5_varaccremovevariable3_struct;

void CDECL VarAccRemoveVariable3(iiecvaraccess5_varaccremovevariable3_struct *p);
typedef void (CDECL * PFVARACCREMOVEVARIABLE3) (iiecvaraccess5_varaccremovevariable3_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCREMOVEVARIABLE3_NOTIMPLEMENTED)
	#define USE_VarAccRemoveVariable3
	#define EXT_VarAccRemoveVariable3
	#define GET_VarAccRemoveVariable3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccRemoveVariable3(p0)  
	#define CHK_VarAccRemoveVariable3  FALSE
	#define EXP_VarAccRemoveVariable3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccRemoveVariable3
	#define EXT_VarAccRemoveVariable3
	#define GET_VarAccRemoveVariable3(fl)  CAL_CMGETAPI( "VarAccRemoveVariable3" ) 
	#define CAL_VarAccRemoveVariable3  VarAccRemoveVariable3
	#define CHK_VarAccRemoveVariable3  TRUE
	#define EXP_VarAccRemoveVariable3  CAL_CMEXPAPI( "VarAccRemoveVariable3" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccRemoveVariable3
	#define EXT_VarAccRemoveVariable3
	#define GET_VarAccRemoveVariable3(fl)  CAL_CMGETAPI( "VarAccRemoveVariable3" ) 
	#define CAL_VarAccRemoveVariable3  VarAccRemoveVariable3
	#define CHK_VarAccRemoveVariable3  TRUE
	#define EXP_VarAccRemoveVariable3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccRemoveVariable3", (RTS_UINTPTR)VarAccRemoveVariable3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccRemoveVariable3
	#define EXT_IecVarAccess_ItfsVarAccRemoveVariable3
	#define GET_IecVarAccess_ItfsVarAccRemoveVariable3  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccRemoveVariable3 pIIecVarAccess_Itfs->IVarAccRemoveVariable3
	#define CHK_IecVarAccess_ItfsVarAccRemoveVariable3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccRemoveVariable3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccRemoveVariable3
	#define EXT_VarAccRemoveVariable3
	#define GET_VarAccRemoveVariable3(fl)  CAL_CMGETAPI( "VarAccRemoveVariable3" ) 
	#define CAL_VarAccRemoveVariable3 pIIecVarAccess_Itfs->IVarAccRemoveVariable3
	#define CHK_VarAccRemoveVariable3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccRemoveVariable3  CAL_CMEXPAPI( "VarAccRemoveVariable3" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccRemoveVariable3  PFVARACCREMOVEVARIABLE3 pfVarAccRemoveVariable3;
	#define EXT_VarAccRemoveVariable3  extern PFVARACCREMOVEVARIABLE3 pfVarAccRemoveVariable3;
	#define GET_VarAccRemoveVariable3(fl)  s_pfCMGetAPI2( "VarAccRemoveVariable3", (RTS_VOID_FCTPTR *)&pfVarAccRemoveVariable3, (fl), 0, 0)
	#define CAL_VarAccRemoveVariable3  pfVarAccRemoveVariable3
	#define CHK_VarAccRemoveVariable3  (pfVarAccRemoveVariable3 != NULL)
	#define EXP_VarAccRemoveVariable3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccRemoveVariable3", (RTS_UINTPTR)VarAccRemoveVariable3, 0, 0) 
#endif




/**
 * <description>IIecVarAccess5::VarAccSwap3</description>
 */
typedef struct tagiiecvaraccess5_varaccswap3_struct
{
	iiecvaraccess5_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	VariableInformationStruct *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_BYTE *pData;				/* VAR_INPUT */	
	RTS_IEC_BOOL bMotorola;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_XWORD VarAccSwap3;			/* VAR_OUTPUT */	
} iiecvaraccess5_varaccswap3_struct;

void CDECL VarAccSwap3(iiecvaraccess5_varaccswap3_struct *p);
typedef void (CDECL * PFVARACCSWAP3) (iiecvaraccess5_varaccswap3_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCSWAP3_NOTIMPLEMENTED)
	#define USE_VarAccSwap3
	#define EXT_VarAccSwap3
	#define GET_VarAccSwap3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccSwap3(p0)  
	#define CHK_VarAccSwap3  FALSE
	#define EXP_VarAccSwap3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccSwap3
	#define EXT_VarAccSwap3
	#define GET_VarAccSwap3(fl)  CAL_CMGETAPI( "VarAccSwap3" ) 
	#define CAL_VarAccSwap3  VarAccSwap3
	#define CHK_VarAccSwap3  TRUE
	#define EXP_VarAccSwap3  CAL_CMEXPAPI( "VarAccSwap3" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccSwap3
	#define EXT_VarAccSwap3
	#define GET_VarAccSwap3(fl)  CAL_CMGETAPI( "VarAccSwap3" ) 
	#define CAL_VarAccSwap3  VarAccSwap3
	#define CHK_VarAccSwap3  TRUE
	#define EXP_VarAccSwap3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccSwap3", (RTS_UINTPTR)VarAccSwap3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccSwap3
	#define EXT_IecVarAccess_ItfsVarAccSwap3
	#define GET_IecVarAccess_ItfsVarAccSwap3  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccSwap3 pIIecVarAccess_Itfs->IVarAccSwap3
	#define CHK_IecVarAccess_ItfsVarAccSwap3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccSwap3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccSwap3
	#define EXT_VarAccSwap3
	#define GET_VarAccSwap3(fl)  CAL_CMGETAPI( "VarAccSwap3" ) 
	#define CAL_VarAccSwap3 pIIecVarAccess_Itfs->IVarAccSwap3
	#define CHK_VarAccSwap3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccSwap3  CAL_CMEXPAPI( "VarAccSwap3" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccSwap3  PFVARACCSWAP3 pfVarAccSwap3;
	#define EXT_VarAccSwap3  extern PFVARACCSWAP3 pfVarAccSwap3;
	#define GET_VarAccSwap3(fl)  s_pfCMGetAPI2( "VarAccSwap3", (RTS_VOID_FCTPTR *)&pfVarAccSwap3, (fl), 0, 0)
	#define CAL_VarAccSwap3  pfVarAccSwap3
	#define CHK_VarAccSwap3  (pfVarAccSwap3 != NULL)
	#define EXP_VarAccSwap3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccSwap3", (RTS_UINTPTR)VarAccSwap3, 0, 0) 
#endif




/**
 * <description>IIecVarAccess5::VarAccGetNodeName3</description>
 */
typedef struct tagiiecvaraccess5_varaccgetnodename3_struct
{
	iiecvaraccess5_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	VariableInformationStruct *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_STRING *VarAccGetNodeName3;	/* VAR_OUTPUT */	
} iiecvaraccess5_varaccgetnodename3_struct;

void CDECL VarAccGetNodeName3(iiecvaraccess5_varaccgetnodename3_struct *p);
typedef void (CDECL * PFVARACCGETNODENAME3) (iiecvaraccess5_varaccgetnodename3_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETNODENAME3_NOTIMPLEMENTED)
	#define USE_VarAccGetNodeName3
	#define EXT_VarAccGetNodeName3
	#define GET_VarAccGetNodeName3(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetNodeName3(p0)  
	#define CHK_VarAccGetNodeName3  FALSE
	#define EXP_VarAccGetNodeName3  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetNodeName3
	#define EXT_VarAccGetNodeName3
	#define GET_VarAccGetNodeName3(fl)  CAL_CMGETAPI( "VarAccGetNodeName3" ) 
	#define CAL_VarAccGetNodeName3  VarAccGetNodeName3
	#define CHK_VarAccGetNodeName3  TRUE
	#define EXP_VarAccGetNodeName3  CAL_CMEXPAPI( "VarAccGetNodeName3" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetNodeName3
	#define EXT_VarAccGetNodeName3
	#define GET_VarAccGetNodeName3(fl)  CAL_CMGETAPI( "VarAccGetNodeName3" ) 
	#define CAL_VarAccGetNodeName3  VarAccGetNodeName3
	#define CHK_VarAccGetNodeName3  TRUE
	#define EXP_VarAccGetNodeName3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNodeName3", (RTS_UINTPTR)VarAccGetNodeName3, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetNodeName3
	#define EXT_IecVarAccess_ItfsVarAccGetNodeName3
	#define GET_IecVarAccess_ItfsVarAccGetNodeName3  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetNodeName3 pIIecVarAccess_Itfs->IVarAccGetNodeName3
	#define CHK_IecVarAccess_ItfsVarAccGetNodeName3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetNodeName3  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetNodeName3
	#define EXT_VarAccGetNodeName3
	#define GET_VarAccGetNodeName3(fl)  CAL_CMGETAPI( "VarAccGetNodeName3" ) 
	#define CAL_VarAccGetNodeName3 pIIecVarAccess_Itfs->IVarAccGetNodeName3
	#define CHK_VarAccGetNodeName3 (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetNodeName3  CAL_CMEXPAPI( "VarAccGetNodeName3" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetNodeName3  PFVARACCGETNODENAME3 pfVarAccGetNodeName3;
	#define EXT_VarAccGetNodeName3  extern PFVARACCGETNODENAME3 pfVarAccGetNodeName3;
	#define GET_VarAccGetNodeName3(fl)  s_pfCMGetAPI2( "VarAccGetNodeName3", (RTS_VOID_FCTPTR *)&pfVarAccGetNodeName3, (fl), 0, 0)
	#define CAL_VarAccGetNodeName3  pfVarAccGetNodeName3
	#define CHK_VarAccGetNodeName3  (pfVarAccGetNodeName3 != NULL)
	#define EXP_VarAccGetNodeName3  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNodeName3", (RTS_UINTPTR)VarAccGetNodeName3, 0, 0) 
#endif




typedef struct
{
	void* __VFTABLEPOINTER;	/* Pointer to virtual function table */
} iiecvaraccess6_struct;

/**
 * <description>IIecVarAccess6::VarAccBrowseGetChildByIndex</description>
 */
typedef struct tagiiecvaraccess6_varaccbrowsegetchildbyindex_struct
{
	iiecvaraccess6_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_DINT diIndex;				/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	IBaseTreeNode *VarAccBrowseGetChildByIndex;	/* VAR_OUTPUT */	
} iiecvaraccess6_varaccbrowsegetchildbyindex_struct;

void CDECL VarAccBrowseGetChildByIndex(iiecvaraccess6_varaccbrowsegetchildbyindex_struct *p);
typedef void (CDECL * PFVARACCBROWSEGETCHILDBYINDEX) (iiecvaraccess6_varaccbrowsegetchildbyindex_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCBROWSEGETCHILDBYINDEX_NOTIMPLEMENTED)
	#define USE_VarAccBrowseGetChildByIndex
	#define EXT_VarAccBrowseGetChildByIndex
	#define GET_VarAccBrowseGetChildByIndex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccBrowseGetChildByIndex(p0)  
	#define CHK_VarAccBrowseGetChildByIndex  FALSE
	#define EXP_VarAccBrowseGetChildByIndex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccBrowseGetChildByIndex
	#define EXT_VarAccBrowseGetChildByIndex
	#define GET_VarAccBrowseGetChildByIndex(fl)  CAL_CMGETAPI( "VarAccBrowseGetChildByIndex" ) 
	#define CAL_VarAccBrowseGetChildByIndex  VarAccBrowseGetChildByIndex
	#define CHK_VarAccBrowseGetChildByIndex  TRUE
	#define EXP_VarAccBrowseGetChildByIndex  CAL_CMEXPAPI( "VarAccBrowseGetChildByIndex" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccBrowseGetChildByIndex
	#define EXT_VarAccBrowseGetChildByIndex
	#define GET_VarAccBrowseGetChildByIndex(fl)  CAL_CMGETAPI( "VarAccBrowseGetChildByIndex" ) 
	#define CAL_VarAccBrowseGetChildByIndex  VarAccBrowseGetChildByIndex
	#define CHK_VarAccBrowseGetChildByIndex  TRUE
	#define EXP_VarAccBrowseGetChildByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccBrowseGetChildByIndex", (RTS_UINTPTR)VarAccBrowseGetChildByIndex, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccBrowseGetChildByIndex
	#define EXT_IecVarAccess_ItfsVarAccBrowseGetChildByIndex
	#define GET_IecVarAccess_ItfsVarAccBrowseGetChildByIndex  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccBrowseGetChildByIndex pIIecVarAccess_Itfs->IVarAccBrowseGetChildByIndex
	#define CHK_IecVarAccess_ItfsVarAccBrowseGetChildByIndex (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccBrowseGetChildByIndex  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccBrowseGetChildByIndex
	#define EXT_VarAccBrowseGetChildByIndex
	#define GET_VarAccBrowseGetChildByIndex(fl)  CAL_CMGETAPI( "VarAccBrowseGetChildByIndex" ) 
	#define CAL_VarAccBrowseGetChildByIndex pIIecVarAccess_Itfs->IVarAccBrowseGetChildByIndex
	#define CHK_VarAccBrowseGetChildByIndex (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccBrowseGetChildByIndex  CAL_CMEXPAPI( "VarAccBrowseGetChildByIndex" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccBrowseGetChildByIndex  PFVARACCBROWSEGETCHILDBYINDEX pfVarAccBrowseGetChildByIndex;
	#define EXT_VarAccBrowseGetChildByIndex  extern PFVARACCBROWSEGETCHILDBYINDEX pfVarAccBrowseGetChildByIndex;
	#define GET_VarAccBrowseGetChildByIndex(fl)  s_pfCMGetAPI2( "VarAccBrowseGetChildByIndex", (RTS_VOID_FCTPTR *)&pfVarAccBrowseGetChildByIndex, (fl), 0, 0)
	#define CAL_VarAccBrowseGetChildByIndex  pfVarAccBrowseGetChildByIndex
	#define CHK_VarAccBrowseGetChildByIndex  (pfVarAccBrowseGetChildByIndex != NULL)
	#define EXP_VarAccBrowseGetChildByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccBrowseGetChildByIndex", (RTS_UINTPTR)VarAccBrowseGetChildByIndex, 0, 0) 
#endif




typedef struct
{
	void* __VFTABLEPOINTER;	/* Pointer to virtual function table */
} iiecvaraccess7_struct;

/**
 * <description>IIecVarAccess7::VarAccEnterAccess</description>
 */
typedef struct tagiiecvaraccess7_varaccenteraccess_struct
{
	iiecvaraccess7_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_RESULT VarAccEnterAccess;	/* VAR_OUTPUT */	
} iiecvaraccess7_varaccenteraccess_struct;

void CDECL VarAccEnterAccess(iiecvaraccess7_varaccenteraccess_struct *p);
typedef void (CDECL * PFVARACCENTERACCESS) (iiecvaraccess7_varaccenteraccess_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCENTERACCESS_NOTIMPLEMENTED)
	#define USE_VarAccEnterAccess
	#define EXT_VarAccEnterAccess
	#define GET_VarAccEnterAccess(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccEnterAccess(p0)  
	#define CHK_VarAccEnterAccess  FALSE
	#define EXP_VarAccEnterAccess  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccEnterAccess
	#define EXT_VarAccEnterAccess
	#define GET_VarAccEnterAccess(fl)  CAL_CMGETAPI( "VarAccEnterAccess" ) 
	#define CAL_VarAccEnterAccess  VarAccEnterAccess
	#define CHK_VarAccEnterAccess  TRUE
	#define EXP_VarAccEnterAccess  CAL_CMEXPAPI( "VarAccEnterAccess" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccEnterAccess
	#define EXT_VarAccEnterAccess
	#define GET_VarAccEnterAccess(fl)  CAL_CMGETAPI( "VarAccEnterAccess" ) 
	#define CAL_VarAccEnterAccess  VarAccEnterAccess
	#define CHK_VarAccEnterAccess  TRUE
	#define EXP_VarAccEnterAccess  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccEnterAccess", (RTS_UINTPTR)VarAccEnterAccess, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccEnterAccess
	#define EXT_IecVarAccess_ItfsVarAccEnterAccess
	#define GET_IecVarAccess_ItfsVarAccEnterAccess  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccEnterAccess pIIecVarAccess_Itfs->IVarAccEnterAccess
	#define CHK_IecVarAccess_ItfsVarAccEnterAccess (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccEnterAccess  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccEnterAccess
	#define EXT_VarAccEnterAccess
	#define GET_VarAccEnterAccess(fl)  CAL_CMGETAPI( "VarAccEnterAccess" ) 
	#define CAL_VarAccEnterAccess pIIecVarAccess_Itfs->IVarAccEnterAccess
	#define CHK_VarAccEnterAccess (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccEnterAccess  CAL_CMEXPAPI( "VarAccEnterAccess" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccEnterAccess  PFVARACCENTERACCESS pfVarAccEnterAccess;
	#define EXT_VarAccEnterAccess  extern PFVARACCENTERACCESS pfVarAccEnterAccess;
	#define GET_VarAccEnterAccess(fl)  s_pfCMGetAPI2( "VarAccEnterAccess", (RTS_VOID_FCTPTR *)&pfVarAccEnterAccess, (fl), 0, 0)
	#define CAL_VarAccEnterAccess  pfVarAccEnterAccess
	#define CHK_VarAccEnterAccess  (pfVarAccEnterAccess != NULL)
	#define EXP_VarAccEnterAccess  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccEnterAccess", (RTS_UINTPTR)VarAccEnterAccess, 0, 0) 
#endif




/**
 * <description>IIecVarAccess7::VarAccGetNumOfAttributes</description>
 */
typedef struct tagiiecvaraccess7_varaccgetnumofattributes_struct
{
	iiecvaraccess7_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_WORD VarAccGetNumOfAttributes;	/* VAR_OUTPUT */	
} iiecvaraccess7_varaccgetnumofattributes_struct;

void CDECL VarAccGetNumOfAttributes(iiecvaraccess7_varaccgetnumofattributes_struct *p);
typedef void (CDECL * PFVARACCGETNUMOFATTRIBUTES) (iiecvaraccess7_varaccgetnumofattributes_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETNUMOFATTRIBUTES_NOTIMPLEMENTED)
	#define USE_VarAccGetNumOfAttributes
	#define EXT_VarAccGetNumOfAttributes
	#define GET_VarAccGetNumOfAttributes(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetNumOfAttributes(p0)  
	#define CHK_VarAccGetNumOfAttributes  FALSE
	#define EXP_VarAccGetNumOfAttributes  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetNumOfAttributes
	#define EXT_VarAccGetNumOfAttributes
	#define GET_VarAccGetNumOfAttributes(fl)  CAL_CMGETAPI( "VarAccGetNumOfAttributes" ) 
	#define CAL_VarAccGetNumOfAttributes  VarAccGetNumOfAttributes
	#define CHK_VarAccGetNumOfAttributes  TRUE
	#define EXP_VarAccGetNumOfAttributes  CAL_CMEXPAPI( "VarAccGetNumOfAttributes" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetNumOfAttributes
	#define EXT_VarAccGetNumOfAttributes
	#define GET_VarAccGetNumOfAttributes(fl)  CAL_CMGETAPI( "VarAccGetNumOfAttributes" ) 
	#define CAL_VarAccGetNumOfAttributes  VarAccGetNumOfAttributes
	#define CHK_VarAccGetNumOfAttributes  TRUE
	#define EXP_VarAccGetNumOfAttributes  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNumOfAttributes", (RTS_UINTPTR)VarAccGetNumOfAttributes, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetNumOfAttributes
	#define EXT_IecVarAccess_ItfsVarAccGetNumOfAttributes
	#define GET_IecVarAccess_ItfsVarAccGetNumOfAttributes  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetNumOfAttributes pIIecVarAccess_Itfs->IVarAccGetNumOfAttributes
	#define CHK_IecVarAccess_ItfsVarAccGetNumOfAttributes (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetNumOfAttributes  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetNumOfAttributes
	#define EXT_VarAccGetNumOfAttributes
	#define GET_VarAccGetNumOfAttributes(fl)  CAL_CMGETAPI( "VarAccGetNumOfAttributes" ) 
	#define CAL_VarAccGetNumOfAttributes pIIecVarAccess_Itfs->IVarAccGetNumOfAttributes
	#define CHK_VarAccGetNumOfAttributes (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetNumOfAttributes  CAL_CMEXPAPI( "VarAccGetNumOfAttributes" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetNumOfAttributes  PFVARACCGETNUMOFATTRIBUTES pfVarAccGetNumOfAttributes;
	#define EXT_VarAccGetNumOfAttributes  extern PFVARACCGETNUMOFATTRIBUTES pfVarAccGetNumOfAttributes;
	#define GET_VarAccGetNumOfAttributes(fl)  s_pfCMGetAPI2( "VarAccGetNumOfAttributes", (RTS_VOID_FCTPTR *)&pfVarAccGetNumOfAttributes, (fl), 0, 0)
	#define CAL_VarAccGetNumOfAttributes  pfVarAccGetNumOfAttributes
	#define CHK_VarAccGetNumOfAttributes  (pfVarAccGetNumOfAttributes != NULL)
	#define EXP_VarAccGetNumOfAttributes  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNumOfAttributes", (RTS_UINTPTR)VarAccGetNumOfAttributes, 0, 0) 
#endif




/**
 * <description>IIecVarAccess7::VarAccGetAttributeByIndex</description>
 */
typedef struct tagiiecvaraccess7_varaccgetattributebyindex_struct
{
	iiecvaraccess7_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_WORD wIndex;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_STRING *VarAccGetAttributeByIndex;	/* VAR_OUTPUT */	
} iiecvaraccess7_varaccgetattributebyindex_struct;

void CDECL VarAccGetAttributeByIndex(iiecvaraccess7_varaccgetattributebyindex_struct *p);
typedef void (CDECL * PFVARACCGETATTRIBUTEBYINDEX) (iiecvaraccess7_varaccgetattributebyindex_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETATTRIBUTEBYINDEX_NOTIMPLEMENTED)
	#define USE_VarAccGetAttributeByIndex
	#define EXT_VarAccGetAttributeByIndex
	#define GET_VarAccGetAttributeByIndex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetAttributeByIndex(p0)  
	#define CHK_VarAccGetAttributeByIndex  FALSE
	#define EXP_VarAccGetAttributeByIndex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetAttributeByIndex
	#define EXT_VarAccGetAttributeByIndex
	#define GET_VarAccGetAttributeByIndex(fl)  CAL_CMGETAPI( "VarAccGetAttributeByIndex" ) 
	#define CAL_VarAccGetAttributeByIndex  VarAccGetAttributeByIndex
	#define CHK_VarAccGetAttributeByIndex  TRUE
	#define EXP_VarAccGetAttributeByIndex  CAL_CMEXPAPI( "VarAccGetAttributeByIndex" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetAttributeByIndex
	#define EXT_VarAccGetAttributeByIndex
	#define GET_VarAccGetAttributeByIndex(fl)  CAL_CMGETAPI( "VarAccGetAttributeByIndex" ) 
	#define CAL_VarAccGetAttributeByIndex  VarAccGetAttributeByIndex
	#define CHK_VarAccGetAttributeByIndex  TRUE
	#define EXP_VarAccGetAttributeByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetAttributeByIndex", (RTS_UINTPTR)VarAccGetAttributeByIndex, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetAttributeByIndex
	#define EXT_IecVarAccess_ItfsVarAccGetAttributeByIndex
	#define GET_IecVarAccess_ItfsVarAccGetAttributeByIndex  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetAttributeByIndex pIIecVarAccess_Itfs->IVarAccGetAttributeByIndex
	#define CHK_IecVarAccess_ItfsVarAccGetAttributeByIndex (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetAttributeByIndex  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetAttributeByIndex
	#define EXT_VarAccGetAttributeByIndex
	#define GET_VarAccGetAttributeByIndex(fl)  CAL_CMGETAPI( "VarAccGetAttributeByIndex" ) 
	#define CAL_VarAccGetAttributeByIndex pIIecVarAccess_Itfs->IVarAccGetAttributeByIndex
	#define CHK_VarAccGetAttributeByIndex (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetAttributeByIndex  CAL_CMEXPAPI( "VarAccGetAttributeByIndex" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetAttributeByIndex  PFVARACCGETATTRIBUTEBYINDEX pfVarAccGetAttributeByIndex;
	#define EXT_VarAccGetAttributeByIndex  extern PFVARACCGETATTRIBUTEBYINDEX pfVarAccGetAttributeByIndex;
	#define GET_VarAccGetAttributeByIndex(fl)  s_pfCMGetAPI2( "VarAccGetAttributeByIndex", (RTS_VOID_FCTPTR *)&pfVarAccGetAttributeByIndex, (fl), 0, 0)
	#define CAL_VarAccGetAttributeByIndex  pfVarAccGetAttributeByIndex
	#define CHK_VarAccGetAttributeByIndex  (pfVarAccGetAttributeByIndex != NULL)
	#define EXP_VarAccGetAttributeByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetAttributeByIndex", (RTS_UINTPTR)VarAccGetAttributeByIndex, 0, 0) 
#endif




/**
 * <description>IIecVarAccess7::VarAccGetNodeFlags</description>
 */
typedef struct tagiiecvaraccess7_varaccgetnodeflags_struct
{
	iiecvaraccess7_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_DWORD VarAccGetNodeFlags;	/* VAR_OUTPUT */	
} iiecvaraccess7_varaccgetnodeflags_struct;

void CDECL VarAccGetNodeFlags(iiecvaraccess7_varaccgetnodeflags_struct *p);
typedef void (CDECL * PFVARACCGETNODEFLAGS) (iiecvaraccess7_varaccgetnodeflags_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETNODEFLAGS_NOTIMPLEMENTED)
	#define USE_VarAccGetNodeFlags
	#define EXT_VarAccGetNodeFlags
	#define GET_VarAccGetNodeFlags(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetNodeFlags(p0)  
	#define CHK_VarAccGetNodeFlags  FALSE
	#define EXP_VarAccGetNodeFlags  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetNodeFlags
	#define EXT_VarAccGetNodeFlags
	#define GET_VarAccGetNodeFlags(fl)  CAL_CMGETAPI( "VarAccGetNodeFlags" ) 
	#define CAL_VarAccGetNodeFlags  VarAccGetNodeFlags
	#define CHK_VarAccGetNodeFlags  TRUE
	#define EXP_VarAccGetNodeFlags  CAL_CMEXPAPI( "VarAccGetNodeFlags" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetNodeFlags
	#define EXT_VarAccGetNodeFlags
	#define GET_VarAccGetNodeFlags(fl)  CAL_CMGETAPI( "VarAccGetNodeFlags" ) 
	#define CAL_VarAccGetNodeFlags  VarAccGetNodeFlags
	#define CHK_VarAccGetNodeFlags  TRUE
	#define EXP_VarAccGetNodeFlags  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNodeFlags", (RTS_UINTPTR)VarAccGetNodeFlags, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetNodeFlags
	#define EXT_IecVarAccess_ItfsVarAccGetNodeFlags
	#define GET_IecVarAccess_ItfsVarAccGetNodeFlags  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetNodeFlags pIIecVarAccess_Itfs->IVarAccGetNodeFlags
	#define CHK_IecVarAccess_ItfsVarAccGetNodeFlags (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetNodeFlags  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetNodeFlags
	#define EXT_VarAccGetNodeFlags
	#define GET_VarAccGetNodeFlags(fl)  CAL_CMGETAPI( "VarAccGetNodeFlags" ) 
	#define CAL_VarAccGetNodeFlags pIIecVarAccess_Itfs->IVarAccGetNodeFlags
	#define CHK_VarAccGetNodeFlags (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetNodeFlags  CAL_CMEXPAPI( "VarAccGetNodeFlags" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetNodeFlags  PFVARACCGETNODEFLAGS pfVarAccGetNodeFlags;
	#define EXT_VarAccGetNodeFlags  extern PFVARACCGETNODEFLAGS pfVarAccGetNodeFlags;
	#define GET_VarAccGetNodeFlags(fl)  s_pfCMGetAPI2( "VarAccGetNodeFlags", (RTS_VOID_FCTPTR *)&pfVarAccGetNodeFlags, (fl), 0, 0)
	#define CAL_VarAccGetNodeFlags  pfVarAccGetNodeFlags
	#define CHK_VarAccGetNodeFlags  (pfVarAccGetNodeFlags != NULL)
	#define EXP_VarAccGetNodeFlags  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNodeFlags", (RTS_UINTPTR)VarAccGetNodeFlags, 0, 0) 
#endif




/**
 * <description>IIecVarAccess7::VarAccGetNumOfTypes</description>
 */
typedef struct tagiiecvaraccess7_varaccgetnumoftypes_struct
{
	iiecvaraccess7_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_DINT VarAccGetNumOfTypes;	/* VAR_OUTPUT */	
} iiecvaraccess7_varaccgetnumoftypes_struct;

void CDECL VarAccGetNumOfTypes(iiecvaraccess7_varaccgetnumoftypes_struct *p);
typedef void (CDECL * PFVARACCGETNUMOFTYPES) (iiecvaraccess7_varaccgetnumoftypes_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETNUMOFTYPES_NOTIMPLEMENTED)
	#define USE_VarAccGetNumOfTypes
	#define EXT_VarAccGetNumOfTypes
	#define GET_VarAccGetNumOfTypes(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetNumOfTypes(p0)  
	#define CHK_VarAccGetNumOfTypes  FALSE
	#define EXP_VarAccGetNumOfTypes  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetNumOfTypes
	#define EXT_VarAccGetNumOfTypes
	#define GET_VarAccGetNumOfTypes(fl)  CAL_CMGETAPI( "VarAccGetNumOfTypes" ) 
	#define CAL_VarAccGetNumOfTypes  VarAccGetNumOfTypes
	#define CHK_VarAccGetNumOfTypes  TRUE
	#define EXP_VarAccGetNumOfTypes  CAL_CMEXPAPI( "VarAccGetNumOfTypes" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetNumOfTypes
	#define EXT_VarAccGetNumOfTypes
	#define GET_VarAccGetNumOfTypes(fl)  CAL_CMGETAPI( "VarAccGetNumOfTypes" ) 
	#define CAL_VarAccGetNumOfTypes  VarAccGetNumOfTypes
	#define CHK_VarAccGetNumOfTypes  TRUE
	#define EXP_VarAccGetNumOfTypes  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNumOfTypes", (RTS_UINTPTR)VarAccGetNumOfTypes, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetNumOfTypes
	#define EXT_IecVarAccess_ItfsVarAccGetNumOfTypes
	#define GET_IecVarAccess_ItfsVarAccGetNumOfTypes  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetNumOfTypes pIIecVarAccess_Itfs->IVarAccGetNumOfTypes
	#define CHK_IecVarAccess_ItfsVarAccGetNumOfTypes (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetNumOfTypes  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetNumOfTypes
	#define EXT_VarAccGetNumOfTypes
	#define GET_VarAccGetNumOfTypes(fl)  CAL_CMGETAPI( "VarAccGetNumOfTypes" ) 
	#define CAL_VarAccGetNumOfTypes pIIecVarAccess_Itfs->IVarAccGetNumOfTypes
	#define CHK_VarAccGetNumOfTypes (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetNumOfTypes  CAL_CMEXPAPI( "VarAccGetNumOfTypes" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetNumOfTypes  PFVARACCGETNUMOFTYPES pfVarAccGetNumOfTypes;
	#define EXT_VarAccGetNumOfTypes  extern PFVARACCGETNUMOFTYPES pfVarAccGetNumOfTypes;
	#define GET_VarAccGetNumOfTypes(fl)  s_pfCMGetAPI2( "VarAccGetNumOfTypes", (RTS_VOID_FCTPTR *)&pfVarAccGetNumOfTypes, (fl), 0, 0)
	#define CAL_VarAccGetNumOfTypes  pfVarAccGetNumOfTypes
	#define CHK_VarAccGetNumOfTypes  (pfVarAccGetNumOfTypes != NULL)
	#define EXP_VarAccGetNumOfTypes  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNumOfTypes", (RTS_UINTPTR)VarAccGetNumOfTypes, 0, 0) 
#endif




/**
 * <description>IIecVarAccess7::VarAccGetEnumValues</description>
 */
typedef struct tagiiecvaraccess7_varaccgetenumvalues_struct
{
	iiecvaraccess7_struct *pInstance;	/* VAR_INPUT */	
	ITypeDesc *typeDesc;				/* VAR_INPUT */	
	RTS_IEC_INT *pnNumOfEnumValues;		/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	EnumValues *VarAccGetEnumValues;	/* VAR_OUTPUT */	
} iiecvaraccess7_varaccgetenumvalues_struct;

void CDECL VarAccGetEnumValues(iiecvaraccess7_varaccgetenumvalues_struct *p);
typedef void (CDECL * PFVARACCGETENUMVALUES) (iiecvaraccess7_varaccgetenumvalues_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETENUMVALUES_NOTIMPLEMENTED)
	#define USE_VarAccGetEnumValues
	#define EXT_VarAccGetEnumValues
	#define GET_VarAccGetEnumValues(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetEnumValues(p0)  
	#define CHK_VarAccGetEnumValues  FALSE
	#define EXP_VarAccGetEnumValues  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetEnumValues
	#define EXT_VarAccGetEnumValues
	#define GET_VarAccGetEnumValues(fl)  CAL_CMGETAPI( "VarAccGetEnumValues" ) 
	#define CAL_VarAccGetEnumValues  VarAccGetEnumValues
	#define CHK_VarAccGetEnumValues  TRUE
	#define EXP_VarAccGetEnumValues  CAL_CMEXPAPI( "VarAccGetEnumValues" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetEnumValues
	#define EXT_VarAccGetEnumValues
	#define GET_VarAccGetEnumValues(fl)  CAL_CMGETAPI( "VarAccGetEnumValues" ) 
	#define CAL_VarAccGetEnumValues  VarAccGetEnumValues
	#define CHK_VarAccGetEnumValues  TRUE
	#define EXP_VarAccGetEnumValues  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetEnumValues", (RTS_UINTPTR)VarAccGetEnumValues, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetEnumValues
	#define EXT_IecVarAccess_ItfsVarAccGetEnumValues
	#define GET_IecVarAccess_ItfsVarAccGetEnumValues  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetEnumValues pIIecVarAccess_Itfs->IVarAccGetEnumValues
	#define CHK_IecVarAccess_ItfsVarAccGetEnumValues (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetEnumValues  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetEnumValues
	#define EXT_VarAccGetEnumValues
	#define GET_VarAccGetEnumValues(fl)  CAL_CMGETAPI( "VarAccGetEnumValues" ) 
	#define CAL_VarAccGetEnumValues pIIecVarAccess_Itfs->IVarAccGetEnumValues
	#define CHK_VarAccGetEnumValues (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetEnumValues  CAL_CMEXPAPI( "VarAccGetEnumValues" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetEnumValues  PFVARACCGETENUMVALUES pfVarAccGetEnumValues;
	#define EXT_VarAccGetEnumValues  extern PFVARACCGETENUMVALUES pfVarAccGetEnumValues;
	#define GET_VarAccGetEnumValues(fl)  s_pfCMGetAPI2( "VarAccGetEnumValues", (RTS_VOID_FCTPTR *)&pfVarAccGetEnumValues, (fl), 0, 0)
	#define CAL_VarAccGetEnumValues  pfVarAccGetEnumValues
	#define CHK_VarAccGetEnumValues  (pfVarAccGetEnumValues != NULL)
	#define EXP_VarAccGetEnumValues  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetEnumValues", (RTS_UINTPTR)VarAccGetEnumValues, 0, 0) 
#endif




/**
 * <description>IIecVarAccess7::VarAccGetTypeName</description>
 */
typedef struct tagiiecvaraccess7_varaccgettypename_struct
{
	iiecvaraccess7_struct *pInstance;	/* VAR_INPUT */	
	ITypeDesc *typeDesc;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_STRING *VarAccGetTypeName;	/* VAR_OUTPUT */	
} iiecvaraccess7_varaccgettypename_struct;

void CDECL VarAccGetTypeName(iiecvaraccess7_varaccgettypename_struct *p);
typedef void (CDECL * PFVARACCGETTYPENAME) (iiecvaraccess7_varaccgettypename_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETTYPENAME_NOTIMPLEMENTED)
	#define USE_VarAccGetTypeName
	#define EXT_VarAccGetTypeName
	#define GET_VarAccGetTypeName(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetTypeName(p0)  
	#define CHK_VarAccGetTypeName  FALSE
	#define EXP_VarAccGetTypeName  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetTypeName
	#define EXT_VarAccGetTypeName
	#define GET_VarAccGetTypeName(fl)  CAL_CMGETAPI( "VarAccGetTypeName" ) 
	#define CAL_VarAccGetTypeName  VarAccGetTypeName
	#define CHK_VarAccGetTypeName  TRUE
	#define EXP_VarAccGetTypeName  CAL_CMEXPAPI( "VarAccGetTypeName" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetTypeName
	#define EXT_VarAccGetTypeName
	#define GET_VarAccGetTypeName(fl)  CAL_CMGETAPI( "VarAccGetTypeName" ) 
	#define CAL_VarAccGetTypeName  VarAccGetTypeName
	#define CHK_VarAccGetTypeName  TRUE
	#define EXP_VarAccGetTypeName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetTypeName", (RTS_UINTPTR)VarAccGetTypeName, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetTypeName
	#define EXT_IecVarAccess_ItfsVarAccGetTypeName
	#define GET_IecVarAccess_ItfsVarAccGetTypeName  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetTypeName pIIecVarAccess_Itfs->IVarAccGetTypeName
	#define CHK_IecVarAccess_ItfsVarAccGetTypeName (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetTypeName  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetTypeName
	#define EXT_VarAccGetTypeName
	#define GET_VarAccGetTypeName(fl)  CAL_CMGETAPI( "VarAccGetTypeName" ) 
	#define CAL_VarAccGetTypeName pIIecVarAccess_Itfs->IVarAccGetTypeName
	#define CHK_VarAccGetTypeName (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetTypeName  CAL_CMEXPAPI( "VarAccGetTypeName" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetTypeName  PFVARACCGETTYPENAME pfVarAccGetTypeName;
	#define EXT_VarAccGetTypeName  extern PFVARACCGETTYPENAME pfVarAccGetTypeName;
	#define GET_VarAccGetTypeName(fl)  s_pfCMGetAPI2( "VarAccGetTypeName", (RTS_VOID_FCTPTR *)&pfVarAccGetTypeName, (fl), 0, 0)
	#define CAL_VarAccGetTypeName  pfVarAccGetTypeName
	#define CHK_VarAccGetTypeName  (pfVarAccGetTypeName != NULL)
	#define EXP_VarAccGetTypeName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetTypeName", (RTS_UINTPTR)VarAccGetTypeName, 0, 0) 
#endif




/**
 * <description>IIecVarAccess7::VarAccGetTypeNodeByIndex</description>
 */
typedef struct tagiiecvaraccess7_varaccgettypenodebyindex_struct
{
	iiecvaraccess7_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_DINT diIndex;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	ITypeDesc *VarAccGetTypeNodeByIndex;	/* VAR_OUTPUT */	
} iiecvaraccess7_varaccgettypenodebyindex_struct;

void CDECL VarAccGetTypeNodeByIndex(iiecvaraccess7_varaccgettypenodebyindex_struct *p);
typedef void (CDECL * PFVARACCGETTYPENODEBYINDEX) (iiecvaraccess7_varaccgettypenodebyindex_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETTYPENODEBYINDEX_NOTIMPLEMENTED)
	#define USE_VarAccGetTypeNodeByIndex
	#define EXT_VarAccGetTypeNodeByIndex
	#define GET_VarAccGetTypeNodeByIndex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetTypeNodeByIndex(p0)  
	#define CHK_VarAccGetTypeNodeByIndex  FALSE
	#define EXP_VarAccGetTypeNodeByIndex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetTypeNodeByIndex
	#define EXT_VarAccGetTypeNodeByIndex
	#define GET_VarAccGetTypeNodeByIndex(fl)  CAL_CMGETAPI( "VarAccGetTypeNodeByIndex" ) 
	#define CAL_VarAccGetTypeNodeByIndex  VarAccGetTypeNodeByIndex
	#define CHK_VarAccGetTypeNodeByIndex  TRUE
	#define EXP_VarAccGetTypeNodeByIndex  CAL_CMEXPAPI( "VarAccGetTypeNodeByIndex" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetTypeNodeByIndex
	#define EXT_VarAccGetTypeNodeByIndex
	#define GET_VarAccGetTypeNodeByIndex(fl)  CAL_CMGETAPI( "VarAccGetTypeNodeByIndex" ) 
	#define CAL_VarAccGetTypeNodeByIndex  VarAccGetTypeNodeByIndex
	#define CHK_VarAccGetTypeNodeByIndex  TRUE
	#define EXP_VarAccGetTypeNodeByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetTypeNodeByIndex", (RTS_UINTPTR)VarAccGetTypeNodeByIndex, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetTypeNodeByIndex
	#define EXT_IecVarAccess_ItfsVarAccGetTypeNodeByIndex
	#define GET_IecVarAccess_ItfsVarAccGetTypeNodeByIndex  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetTypeNodeByIndex pIIecVarAccess_Itfs->IVarAccGetTypeNodeByIndex
	#define CHK_IecVarAccess_ItfsVarAccGetTypeNodeByIndex (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetTypeNodeByIndex  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetTypeNodeByIndex
	#define EXT_VarAccGetTypeNodeByIndex
	#define GET_VarAccGetTypeNodeByIndex(fl)  CAL_CMGETAPI( "VarAccGetTypeNodeByIndex" ) 
	#define CAL_VarAccGetTypeNodeByIndex pIIecVarAccess_Itfs->IVarAccGetTypeNodeByIndex
	#define CHK_VarAccGetTypeNodeByIndex (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetTypeNodeByIndex  CAL_CMEXPAPI( "VarAccGetTypeNodeByIndex" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetTypeNodeByIndex  PFVARACCGETTYPENODEBYINDEX pfVarAccGetTypeNodeByIndex;
	#define EXT_VarAccGetTypeNodeByIndex  extern PFVARACCGETTYPENODEBYINDEX pfVarAccGetTypeNodeByIndex;
	#define GET_VarAccGetTypeNodeByIndex(fl)  s_pfCMGetAPI2( "VarAccGetTypeNodeByIndex", (RTS_VOID_FCTPTR *)&pfVarAccGetTypeNodeByIndex, (fl), 0, 0)
	#define CAL_VarAccGetTypeNodeByIndex  pfVarAccGetTypeNodeByIndex
	#define CHK_VarAccGetTypeNodeByIndex  (pfVarAccGetTypeNodeByIndex != NULL)
	#define EXP_VarAccGetTypeNodeByIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetTypeNodeByIndex", (RTS_UINTPTR)VarAccGetTypeNodeByIndex, 0, 0) 
#endif




/**
 * <description>IIecVarAccess7::VarAccGetTypeClassFromType</description>
 */
typedef struct tagiiecvaraccess7_varaccgettypeclassfromtype_struct
{
	iiecvaraccess7_struct *pInstance;	/* VAR_INPUT */	
	ITypeDesc *typeDesc;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwFlags;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_INT VarAccGetTypeClassFromType;	/* VAR_OUTPUT, Enum: TYPECLASS */
} iiecvaraccess7_varaccgettypeclassfromtype_struct;

void CDECL VarAccGetTypeClassFromType(iiecvaraccess7_varaccgettypeclassfromtype_struct *p);
typedef void (CDECL * PFVARACCGETTYPECLASSFROMTYPE) (iiecvaraccess7_varaccgettypeclassfromtype_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETTYPECLASSFROMTYPE_NOTIMPLEMENTED)
	#define USE_VarAccGetTypeClassFromType
	#define EXT_VarAccGetTypeClassFromType
	#define GET_VarAccGetTypeClassFromType(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetTypeClassFromType(p0)  
	#define CHK_VarAccGetTypeClassFromType  FALSE
	#define EXP_VarAccGetTypeClassFromType  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetTypeClassFromType
	#define EXT_VarAccGetTypeClassFromType
	#define GET_VarAccGetTypeClassFromType(fl)  CAL_CMGETAPI( "VarAccGetTypeClassFromType" ) 
	#define CAL_VarAccGetTypeClassFromType  VarAccGetTypeClassFromType
	#define CHK_VarAccGetTypeClassFromType  TRUE
	#define EXP_VarAccGetTypeClassFromType  CAL_CMEXPAPI( "VarAccGetTypeClassFromType" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetTypeClassFromType
	#define EXT_VarAccGetTypeClassFromType
	#define GET_VarAccGetTypeClassFromType(fl)  CAL_CMGETAPI( "VarAccGetTypeClassFromType" ) 
	#define CAL_VarAccGetTypeClassFromType  VarAccGetTypeClassFromType
	#define CHK_VarAccGetTypeClassFromType  TRUE
	#define EXP_VarAccGetTypeClassFromType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetTypeClassFromType", (RTS_UINTPTR)VarAccGetTypeClassFromType, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetTypeClassFromType
	#define EXT_IecVarAccess_ItfsVarAccGetTypeClassFromType
	#define GET_IecVarAccess_ItfsVarAccGetTypeClassFromType  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetTypeClassFromType pIIecVarAccess_Itfs->IVarAccGetTypeClassFromType
	#define CHK_IecVarAccess_ItfsVarAccGetTypeClassFromType (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetTypeClassFromType  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetTypeClassFromType
	#define EXT_VarAccGetTypeClassFromType
	#define GET_VarAccGetTypeClassFromType(fl)  CAL_CMGETAPI( "VarAccGetTypeClassFromType" ) 
	#define CAL_VarAccGetTypeClassFromType pIIecVarAccess_Itfs->IVarAccGetTypeClassFromType
	#define CHK_VarAccGetTypeClassFromType (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetTypeClassFromType  CAL_CMEXPAPI( "VarAccGetTypeClassFromType" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetTypeClassFromType  PFVARACCGETTYPECLASSFROMTYPE pfVarAccGetTypeClassFromType;
	#define EXT_VarAccGetTypeClassFromType  extern PFVARACCGETTYPECLASSFROMTYPE pfVarAccGetTypeClassFromType;
	#define GET_VarAccGetTypeClassFromType(fl)  s_pfCMGetAPI2( "VarAccGetTypeClassFromType", (RTS_VOID_FCTPTR *)&pfVarAccGetTypeClassFromType, (fl), 0, 0)
	#define CAL_VarAccGetTypeClassFromType  pfVarAccGetTypeClassFromType
	#define CHK_VarAccGetTypeClassFromType  (pfVarAccGetTypeClassFromType != NULL)
	#define EXP_VarAccGetTypeClassFromType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetTypeClassFromType", (RTS_UINTPTR)VarAccGetTypeClassFromType, 0, 0) 
#endif




/**
 * <description>IIecVarAccess7::VarAccLeaveAccess</description>
 */
typedef struct tagiiecvaraccess7_varaccleaveaccess_struct
{
	iiecvaraccess7_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_RESULT VarAccLeaveAccess;	/* VAR_OUTPUT */	
} iiecvaraccess7_varaccleaveaccess_struct;

void CDECL VarAccLeaveAccess(iiecvaraccess7_varaccleaveaccess_struct *p);
typedef void (CDECL * PFVARACCLEAVEACCESS) (iiecvaraccess7_varaccleaveaccess_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCLEAVEACCESS_NOTIMPLEMENTED)
	#define USE_VarAccLeaveAccess
	#define EXT_VarAccLeaveAccess
	#define GET_VarAccLeaveAccess(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccLeaveAccess(p0)  
	#define CHK_VarAccLeaveAccess  FALSE
	#define EXP_VarAccLeaveAccess  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccLeaveAccess
	#define EXT_VarAccLeaveAccess
	#define GET_VarAccLeaveAccess(fl)  CAL_CMGETAPI( "VarAccLeaveAccess" ) 
	#define CAL_VarAccLeaveAccess  VarAccLeaveAccess
	#define CHK_VarAccLeaveAccess  TRUE
	#define EXP_VarAccLeaveAccess  CAL_CMEXPAPI( "VarAccLeaveAccess" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccLeaveAccess
	#define EXT_VarAccLeaveAccess
	#define GET_VarAccLeaveAccess(fl)  CAL_CMGETAPI( "VarAccLeaveAccess" ) 
	#define CAL_VarAccLeaveAccess  VarAccLeaveAccess
	#define CHK_VarAccLeaveAccess  TRUE
	#define EXP_VarAccLeaveAccess  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccLeaveAccess", (RTS_UINTPTR)VarAccLeaveAccess, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccLeaveAccess
	#define EXT_IecVarAccess_ItfsVarAccLeaveAccess
	#define GET_IecVarAccess_ItfsVarAccLeaveAccess  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccLeaveAccess pIIecVarAccess_Itfs->IVarAccLeaveAccess
	#define CHK_IecVarAccess_ItfsVarAccLeaveAccess (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccLeaveAccess  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccLeaveAccess
	#define EXT_VarAccLeaveAccess
	#define GET_VarAccLeaveAccess(fl)  CAL_CMGETAPI( "VarAccLeaveAccess" ) 
	#define CAL_VarAccLeaveAccess pIIecVarAccess_Itfs->IVarAccLeaveAccess
	#define CHK_VarAccLeaveAccess (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccLeaveAccess  CAL_CMEXPAPI( "VarAccLeaveAccess" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccLeaveAccess  PFVARACCLEAVEACCESS pfVarAccLeaveAccess;
	#define EXT_VarAccLeaveAccess  extern PFVARACCLEAVEACCESS pfVarAccLeaveAccess;
	#define GET_VarAccLeaveAccess(fl)  s_pfCMGetAPI2( "VarAccLeaveAccess", (RTS_VOID_FCTPTR *)&pfVarAccLeaveAccess, (fl), 0, 0)
	#define CAL_VarAccLeaveAccess  pfVarAccLeaveAccess
	#define CHK_VarAccLeaveAccess  (pfVarAccLeaveAccess != NULL)
	#define EXP_VarAccLeaveAccess  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccLeaveAccess", (RTS_UINTPTR)VarAccLeaveAccess, 0, 0) 
#endif




typedef struct
{
	void* __VFTABLEPOINTER;	/* Pointer to virtual function table */
} iiecvaraccess8_struct;

/**
 * <description>IIecVarAccess8::VarAccGetBaseType</description>
 */
typedef struct tagiiecvaraccess8_varaccgetbasetype_struct
{
	iiecvaraccess8_struct *pInstance;	/* VAR_INPUT */	
	ITypeDesc *typeDesc;				/* VAR_INPUT */	
	ITypeDesc *VarAccGetBaseType;		/* VAR_OUTPUT */	
} iiecvaraccess8_varaccgetbasetype_struct;

void CDECL VarAccGetBaseType(iiecvaraccess8_varaccgetbasetype_struct *p);
typedef void (CDECL * PFVARACCGETBASETYPE) (iiecvaraccess8_varaccgetbasetype_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETBASETYPE_NOTIMPLEMENTED)
	#define USE_VarAccGetBaseType
	#define EXT_VarAccGetBaseType
	#define GET_VarAccGetBaseType(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetBaseType(p0)  
	#define CHK_VarAccGetBaseType  FALSE
	#define EXP_VarAccGetBaseType  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetBaseType
	#define EXT_VarAccGetBaseType
	#define GET_VarAccGetBaseType(fl)  CAL_CMGETAPI( "VarAccGetBaseType" ) 
	#define CAL_VarAccGetBaseType  VarAccGetBaseType
	#define CHK_VarAccGetBaseType  TRUE
	#define EXP_VarAccGetBaseType  CAL_CMEXPAPI( "VarAccGetBaseType" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetBaseType
	#define EXT_VarAccGetBaseType
	#define GET_VarAccGetBaseType(fl)  CAL_CMGETAPI( "VarAccGetBaseType" ) 
	#define CAL_VarAccGetBaseType  VarAccGetBaseType
	#define CHK_VarAccGetBaseType  TRUE
	#define EXP_VarAccGetBaseType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetBaseType", (RTS_UINTPTR)VarAccGetBaseType, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetBaseType
	#define EXT_IecVarAccess_ItfsVarAccGetBaseType
	#define GET_IecVarAccess_ItfsVarAccGetBaseType  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetBaseType pIIecVarAccess_Itfs->IVarAccGetBaseType
	#define CHK_IecVarAccess_ItfsVarAccGetBaseType (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetBaseType  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetBaseType
	#define EXT_VarAccGetBaseType
	#define GET_VarAccGetBaseType(fl)  CAL_CMGETAPI( "VarAccGetBaseType" ) 
	#define CAL_VarAccGetBaseType pIIecVarAccess_Itfs->IVarAccGetBaseType
	#define CHK_VarAccGetBaseType (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetBaseType  CAL_CMEXPAPI( "VarAccGetBaseType" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetBaseType  PFVARACCGETBASETYPE pfVarAccGetBaseType;
	#define EXT_VarAccGetBaseType  extern PFVARACCGETBASETYPE pfVarAccGetBaseType;
	#define GET_VarAccGetBaseType(fl)  s_pfCMGetAPI2( "VarAccGetBaseType", (RTS_VOID_FCTPTR *)&pfVarAccGetBaseType, (fl), 0, 0)
	#define CAL_VarAccGetBaseType  pfVarAccGetBaseType
	#define CHK_VarAccGetBaseType  (pfVarAccGetBaseType != NULL)
	#define EXP_VarAccGetBaseType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetBaseType", (RTS_UINTPTR)VarAccGetBaseType, 0, 0) 
#endif




/**
 * <description>IIecVarAccess8::VarAccHasBaseType</description>
 */
typedef struct tagiiecvaraccess8_varacchasbasetype_struct
{
	iiecvaraccess8_struct *pInstance;	/* VAR_INPUT */	
	ITypeDesc *typeDesc;				/* VAR_INPUT */	
	RTS_IEC_BOOL VarAccHasBaseType;		/* VAR_OUTPUT */	
} iiecvaraccess8_varacchasbasetype_struct;

void CDECL VarAccHasBaseType(iiecvaraccess8_varacchasbasetype_struct *p);
typedef void (CDECL * PFVARACCHASBASETYPE) (iiecvaraccess8_varacchasbasetype_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCHASBASETYPE_NOTIMPLEMENTED)
	#define USE_VarAccHasBaseType
	#define EXT_VarAccHasBaseType
	#define GET_VarAccHasBaseType(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccHasBaseType(p0)  
	#define CHK_VarAccHasBaseType  FALSE
	#define EXP_VarAccHasBaseType  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccHasBaseType
	#define EXT_VarAccHasBaseType
	#define GET_VarAccHasBaseType(fl)  CAL_CMGETAPI( "VarAccHasBaseType" ) 
	#define CAL_VarAccHasBaseType  VarAccHasBaseType
	#define CHK_VarAccHasBaseType  TRUE
	#define EXP_VarAccHasBaseType  CAL_CMEXPAPI( "VarAccHasBaseType" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccHasBaseType
	#define EXT_VarAccHasBaseType
	#define GET_VarAccHasBaseType(fl)  CAL_CMGETAPI( "VarAccHasBaseType" ) 
	#define CAL_VarAccHasBaseType  VarAccHasBaseType
	#define CHK_VarAccHasBaseType  TRUE
	#define EXP_VarAccHasBaseType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccHasBaseType", (RTS_UINTPTR)VarAccHasBaseType, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccHasBaseType
	#define EXT_IecVarAccess_ItfsVarAccHasBaseType
	#define GET_IecVarAccess_ItfsVarAccHasBaseType  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccHasBaseType pIIecVarAccess_Itfs->IVarAccHasBaseType
	#define CHK_IecVarAccess_ItfsVarAccHasBaseType (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccHasBaseType  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccHasBaseType
	#define EXT_VarAccHasBaseType
	#define GET_VarAccHasBaseType(fl)  CAL_CMGETAPI( "VarAccHasBaseType" ) 
	#define CAL_VarAccHasBaseType pIIecVarAccess_Itfs->IVarAccHasBaseType
	#define CHK_VarAccHasBaseType (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccHasBaseType  CAL_CMEXPAPI( "VarAccHasBaseType" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccHasBaseType  PFVARACCHASBASETYPE pfVarAccHasBaseType;
	#define EXT_VarAccHasBaseType  extern PFVARACCHASBASETYPE pfVarAccHasBaseType;
	#define GET_VarAccHasBaseType(fl)  s_pfCMGetAPI2( "VarAccHasBaseType", (RTS_VOID_FCTPTR *)&pfVarAccHasBaseType, (fl), 0, 0)
	#define CAL_VarAccHasBaseType  pfVarAccHasBaseType
	#define CHK_VarAccHasBaseType  (pfVarAccHasBaseType != NULL)
	#define EXP_VarAccHasBaseType  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccHasBaseType", (RTS_UINTPTR)VarAccHasBaseType, 0, 0) 
#endif




typedef struct
{
	void* __VFTABLEPOINTER;	/* Pointer to virtual function table */
} iiecvaraccess9_struct;

/**
 * <description>IIecVarAccess9::VarAccBrowseUp2</description>
 */
typedef struct tagiiecvaraccess9_varaccbrowseup2_struct
{
	iiecvaraccess9_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	IBaseTreeNode *VarAccBrowseUp2;		/* VAR_OUTPUT */	
} iiecvaraccess9_varaccbrowseup2_struct;

void CDECL VarAccBrowseUp2(iiecvaraccess9_varaccbrowseup2_struct *p);
typedef void (CDECL * PFVARACCBROWSEUP2) (iiecvaraccess9_varaccbrowseup2_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCBROWSEUP2_NOTIMPLEMENTED)
	#define USE_VarAccBrowseUp2
	#define EXT_VarAccBrowseUp2
	#define GET_VarAccBrowseUp2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccBrowseUp2(p0)  
	#define CHK_VarAccBrowseUp2  FALSE
	#define EXP_VarAccBrowseUp2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccBrowseUp2
	#define EXT_VarAccBrowseUp2
	#define GET_VarAccBrowseUp2(fl)  CAL_CMGETAPI( "VarAccBrowseUp2" ) 
	#define CAL_VarAccBrowseUp2  VarAccBrowseUp2
	#define CHK_VarAccBrowseUp2  TRUE
	#define EXP_VarAccBrowseUp2  CAL_CMEXPAPI( "VarAccBrowseUp2" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccBrowseUp2
	#define EXT_VarAccBrowseUp2
	#define GET_VarAccBrowseUp2(fl)  CAL_CMGETAPI( "VarAccBrowseUp2" ) 
	#define CAL_VarAccBrowseUp2  VarAccBrowseUp2
	#define CHK_VarAccBrowseUp2  TRUE
	#define EXP_VarAccBrowseUp2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccBrowseUp2", (RTS_UINTPTR)VarAccBrowseUp2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccBrowseUp2
	#define EXT_IecVarAccess_ItfsVarAccBrowseUp2
	#define GET_IecVarAccess_ItfsVarAccBrowseUp2  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccBrowseUp2 pIIecVarAccess_Itfs->IVarAccBrowseUp2
	#define CHK_IecVarAccess_ItfsVarAccBrowseUp2 (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccBrowseUp2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccBrowseUp2
	#define EXT_VarAccBrowseUp2
	#define GET_VarAccBrowseUp2(fl)  CAL_CMGETAPI( "VarAccBrowseUp2" ) 
	#define CAL_VarAccBrowseUp2 pIIecVarAccess_Itfs->IVarAccBrowseUp2
	#define CHK_VarAccBrowseUp2 (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccBrowseUp2  CAL_CMEXPAPI( "VarAccBrowseUp2" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccBrowseUp2  PFVARACCBROWSEUP2 pfVarAccBrowseUp2;
	#define EXT_VarAccBrowseUp2  extern PFVARACCBROWSEUP2 pfVarAccBrowseUp2;
	#define GET_VarAccBrowseUp2(fl)  s_pfCMGetAPI2( "VarAccBrowseUp2", (RTS_VOID_FCTPTR *)&pfVarAccBrowseUp2, (fl), 0, 0)
	#define CAL_VarAccBrowseUp2  pfVarAccBrowseUp2
	#define CHK_VarAccBrowseUp2  (pfVarAccBrowseUp2 != NULL)
	#define EXP_VarAccBrowseUp2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccBrowseUp2", (RTS_UINTPTR)VarAccBrowseUp2, 0, 0) 
#endif




/**
 * <description>IIecVarAccess9::VarAccExitVarInfo</description>
 */
typedef struct tagiiecvaraccess9_varaccexitvarinfo_struct
{
	iiecvaraccess9_struct *pInstance;	/* VAR_INPUT */	
	VariableInformationStruct2 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT VarAccExitVarInfo;	/* VAR_OUTPUT */	
} iiecvaraccess9_varaccexitvarinfo_struct;

void CDECL VarAccExitVarInfo(iiecvaraccess9_varaccexitvarinfo_struct *p);
typedef void (CDECL * PFVARACCEXITVARINFO) (iiecvaraccess9_varaccexitvarinfo_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCEXITVARINFO_NOTIMPLEMENTED)
	#define USE_VarAccExitVarInfo
	#define EXT_VarAccExitVarInfo
	#define GET_VarAccExitVarInfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccExitVarInfo(p0)  
	#define CHK_VarAccExitVarInfo  FALSE
	#define EXP_VarAccExitVarInfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccExitVarInfo
	#define EXT_VarAccExitVarInfo
	#define GET_VarAccExitVarInfo(fl)  CAL_CMGETAPI( "VarAccExitVarInfo" ) 
	#define CAL_VarAccExitVarInfo  VarAccExitVarInfo
	#define CHK_VarAccExitVarInfo  TRUE
	#define EXP_VarAccExitVarInfo  CAL_CMEXPAPI( "VarAccExitVarInfo" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccExitVarInfo
	#define EXT_VarAccExitVarInfo
	#define GET_VarAccExitVarInfo(fl)  CAL_CMGETAPI( "VarAccExitVarInfo" ) 
	#define CAL_VarAccExitVarInfo  VarAccExitVarInfo
	#define CHK_VarAccExitVarInfo  TRUE
	#define EXP_VarAccExitVarInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccExitVarInfo", (RTS_UINTPTR)VarAccExitVarInfo, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccExitVarInfo
	#define EXT_IecVarAccess_ItfsVarAccExitVarInfo
	#define GET_IecVarAccess_ItfsVarAccExitVarInfo  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccExitVarInfo pIIecVarAccess_Itfs->IVarAccExitVarInfo
	#define CHK_IecVarAccess_ItfsVarAccExitVarInfo (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccExitVarInfo  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccExitVarInfo
	#define EXT_VarAccExitVarInfo
	#define GET_VarAccExitVarInfo(fl)  CAL_CMGETAPI( "VarAccExitVarInfo" ) 
	#define CAL_VarAccExitVarInfo pIIecVarAccess_Itfs->IVarAccExitVarInfo
	#define CHK_VarAccExitVarInfo (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccExitVarInfo  CAL_CMEXPAPI( "VarAccExitVarInfo" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccExitVarInfo  PFVARACCEXITVARINFO pfVarAccExitVarInfo;
	#define EXT_VarAccExitVarInfo  extern PFVARACCEXITVARINFO pfVarAccExitVarInfo;
	#define GET_VarAccExitVarInfo(fl)  s_pfCMGetAPI2( "VarAccExitVarInfo", (RTS_VOID_FCTPTR *)&pfVarAccExitVarInfo, (fl), 0, 0)
	#define CAL_VarAccExitVarInfo  pfVarAccExitVarInfo
	#define CHK_VarAccExitVarInfo  (pfVarAccExitVarInfo != NULL)
	#define EXP_VarAccExitVarInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccExitVarInfo", (RTS_UINTPTR)VarAccExitVarInfo, 0, 0) 
#endif




/**
 * <description>IIecVarAccess9::VarAccBrowseRecursive</description>
 */
typedef struct tagiiecvaraccess9_varaccbrowserecursive_struct
{
	iiecvaraccess9_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_BYTE *pfBrowseCallback;		/* VAR_INPUT */	
	RTS_IEC_BYTE *pUserParameter;		/* VAR_INPUT */	
	RTS_IEC_RESULT VarAccBrowseRecursive;	/* VAR_OUTPUT */	
} iiecvaraccess9_varaccbrowserecursive_struct;

void CDECL VarAccBrowseRecursive(iiecvaraccess9_varaccbrowserecursive_struct *p);
typedef void (CDECL * PFVARACCBROWSERECURSIVE) (iiecvaraccess9_varaccbrowserecursive_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCBROWSERECURSIVE_NOTIMPLEMENTED)
	#define USE_VarAccBrowseRecursive
	#define EXT_VarAccBrowseRecursive
	#define GET_VarAccBrowseRecursive(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccBrowseRecursive(p0)  
	#define CHK_VarAccBrowseRecursive  FALSE
	#define EXP_VarAccBrowseRecursive  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccBrowseRecursive
	#define EXT_VarAccBrowseRecursive
	#define GET_VarAccBrowseRecursive(fl)  CAL_CMGETAPI( "VarAccBrowseRecursive" ) 
	#define CAL_VarAccBrowseRecursive  VarAccBrowseRecursive
	#define CHK_VarAccBrowseRecursive  TRUE
	#define EXP_VarAccBrowseRecursive  CAL_CMEXPAPI( "VarAccBrowseRecursive" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccBrowseRecursive
	#define EXT_VarAccBrowseRecursive
	#define GET_VarAccBrowseRecursive(fl)  CAL_CMGETAPI( "VarAccBrowseRecursive" ) 
	#define CAL_VarAccBrowseRecursive  VarAccBrowseRecursive
	#define CHK_VarAccBrowseRecursive  TRUE
	#define EXP_VarAccBrowseRecursive  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccBrowseRecursive", (RTS_UINTPTR)VarAccBrowseRecursive, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccBrowseRecursive
	#define EXT_IecVarAccess_ItfsVarAccBrowseRecursive
	#define GET_IecVarAccess_ItfsVarAccBrowseRecursive  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccBrowseRecursive pIIecVarAccess_Itfs->IVarAccBrowseRecursive
	#define CHK_IecVarAccess_ItfsVarAccBrowseRecursive (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccBrowseRecursive  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccBrowseRecursive
	#define EXT_VarAccBrowseRecursive
	#define GET_VarAccBrowseRecursive(fl)  CAL_CMGETAPI( "VarAccBrowseRecursive" ) 
	#define CAL_VarAccBrowseRecursive pIIecVarAccess_Itfs->IVarAccBrowseRecursive
	#define CHK_VarAccBrowseRecursive (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccBrowseRecursive  CAL_CMEXPAPI( "VarAccBrowseRecursive" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccBrowseRecursive  PFVARACCBROWSERECURSIVE pfVarAccBrowseRecursive;
	#define EXT_VarAccBrowseRecursive  extern PFVARACCBROWSERECURSIVE pfVarAccBrowseRecursive;
	#define GET_VarAccBrowseRecursive(fl)  s_pfCMGetAPI2( "VarAccBrowseRecursive", (RTS_VOID_FCTPTR *)&pfVarAccBrowseRecursive, (fl), 0, 0)
	#define CAL_VarAccBrowseRecursive  pfVarAccBrowseRecursive
	#define CHK_VarAccBrowseRecursive  (pfVarAccBrowseRecursive != NULL)
	#define EXP_VarAccBrowseRecursive  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccBrowseRecursive", (RTS_UINTPTR)VarAccBrowseRecursive, 0, 0) 
#endif




/**
 * <description>IIecVarAccess9::VarAccBrowseGetNext2</description>
 */
typedef struct tagiiecvaraccess9_varaccbrowsegetnext2_struct
{
	iiecvaraccess9_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	IBaseTreeNode *VarAccBrowseGetNext2;	/* VAR_OUTPUT */	
} iiecvaraccess9_varaccbrowsegetnext2_struct;

void CDECL VarAccBrowseGetNext2(iiecvaraccess9_varaccbrowsegetnext2_struct *p);
typedef void (CDECL * PFVARACCBROWSEGETNEXT2) (iiecvaraccess9_varaccbrowsegetnext2_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCBROWSEGETNEXT2_NOTIMPLEMENTED)
	#define USE_VarAccBrowseGetNext2
	#define EXT_VarAccBrowseGetNext2
	#define GET_VarAccBrowseGetNext2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccBrowseGetNext2(p0)  
	#define CHK_VarAccBrowseGetNext2  FALSE
	#define EXP_VarAccBrowseGetNext2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccBrowseGetNext2
	#define EXT_VarAccBrowseGetNext2
	#define GET_VarAccBrowseGetNext2(fl)  CAL_CMGETAPI( "VarAccBrowseGetNext2" ) 
	#define CAL_VarAccBrowseGetNext2  VarAccBrowseGetNext2
	#define CHK_VarAccBrowseGetNext2  TRUE
	#define EXP_VarAccBrowseGetNext2  CAL_CMEXPAPI( "VarAccBrowseGetNext2" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccBrowseGetNext2
	#define EXT_VarAccBrowseGetNext2
	#define GET_VarAccBrowseGetNext2(fl)  CAL_CMGETAPI( "VarAccBrowseGetNext2" ) 
	#define CAL_VarAccBrowseGetNext2  VarAccBrowseGetNext2
	#define CHK_VarAccBrowseGetNext2  TRUE
	#define EXP_VarAccBrowseGetNext2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccBrowseGetNext2", (RTS_UINTPTR)VarAccBrowseGetNext2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccBrowseGetNext2
	#define EXT_IecVarAccess_ItfsVarAccBrowseGetNext2
	#define GET_IecVarAccess_ItfsVarAccBrowseGetNext2  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccBrowseGetNext2 pIIecVarAccess_Itfs->IVarAccBrowseGetNext2
	#define CHK_IecVarAccess_ItfsVarAccBrowseGetNext2 (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccBrowseGetNext2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccBrowseGetNext2
	#define EXT_VarAccBrowseGetNext2
	#define GET_VarAccBrowseGetNext2(fl)  CAL_CMGETAPI( "VarAccBrowseGetNext2" ) 
	#define CAL_VarAccBrowseGetNext2 pIIecVarAccess_Itfs->IVarAccBrowseGetNext2
	#define CHK_VarAccBrowseGetNext2 (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccBrowseGetNext2  CAL_CMEXPAPI( "VarAccBrowseGetNext2" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccBrowseGetNext2  PFVARACCBROWSEGETNEXT2 pfVarAccBrowseGetNext2;
	#define EXT_VarAccBrowseGetNext2  extern PFVARACCBROWSEGETNEXT2 pfVarAccBrowseGetNext2;
	#define GET_VarAccBrowseGetNext2(fl)  s_pfCMGetAPI2( "VarAccBrowseGetNext2", (RTS_VOID_FCTPTR *)&pfVarAccBrowseGetNext2, (fl), 0, 0)
	#define CAL_VarAccBrowseGetNext2  pfVarAccBrowseGetNext2
	#define CHK_VarAccBrowseGetNext2  (pfVarAccBrowseGetNext2 != NULL)
	#define EXP_VarAccBrowseGetNext2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccBrowseGetNext2", (RTS_UINTPTR)VarAccBrowseGetNext2, 0, 0) 
#endif




/**
 * <description>IIecVarAccess9::VarAccGetNodeFullPath4</description>
 */
typedef struct tagiiecvaraccess9_varaccgetnodefullpath4_struct
{
	iiecvaraccess9_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_STRING *pszPath;			/* VAR_INPUT */	
	RTS_IEC_DINT diMaxPath;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_DINT VarAccGetNodeFullPath4;	/* VAR_OUTPUT */	
} iiecvaraccess9_varaccgetnodefullpath4_struct;

void CDECL VarAccGetNodeFullPath4(iiecvaraccess9_varaccgetnodefullpath4_struct *p);
typedef void (CDECL * PFVARACCGETNODEFULLPATH4) (iiecvaraccess9_varaccgetnodefullpath4_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETNODEFULLPATH4_NOTIMPLEMENTED)
	#define USE_VarAccGetNodeFullPath4
	#define EXT_VarAccGetNodeFullPath4
	#define GET_VarAccGetNodeFullPath4(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetNodeFullPath4(p0)  
	#define CHK_VarAccGetNodeFullPath4  FALSE
	#define EXP_VarAccGetNodeFullPath4  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetNodeFullPath4
	#define EXT_VarAccGetNodeFullPath4
	#define GET_VarAccGetNodeFullPath4(fl)  CAL_CMGETAPI( "VarAccGetNodeFullPath4" ) 
	#define CAL_VarAccGetNodeFullPath4  VarAccGetNodeFullPath4
	#define CHK_VarAccGetNodeFullPath4  TRUE
	#define EXP_VarAccGetNodeFullPath4  CAL_CMEXPAPI( "VarAccGetNodeFullPath4" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetNodeFullPath4
	#define EXT_VarAccGetNodeFullPath4
	#define GET_VarAccGetNodeFullPath4(fl)  CAL_CMGETAPI( "VarAccGetNodeFullPath4" ) 
	#define CAL_VarAccGetNodeFullPath4  VarAccGetNodeFullPath4
	#define CHK_VarAccGetNodeFullPath4  TRUE
	#define EXP_VarAccGetNodeFullPath4  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNodeFullPath4", (RTS_UINTPTR)VarAccGetNodeFullPath4, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetNodeFullPath4
	#define EXT_IecVarAccess_ItfsVarAccGetNodeFullPath4
	#define GET_IecVarAccess_ItfsVarAccGetNodeFullPath4  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetNodeFullPath4 pIIecVarAccess_Itfs->IVarAccGetNodeFullPath4
	#define CHK_IecVarAccess_ItfsVarAccGetNodeFullPath4 (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetNodeFullPath4  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetNodeFullPath4
	#define EXT_VarAccGetNodeFullPath4
	#define GET_VarAccGetNodeFullPath4(fl)  CAL_CMGETAPI( "VarAccGetNodeFullPath4" ) 
	#define CAL_VarAccGetNodeFullPath4 pIIecVarAccess_Itfs->IVarAccGetNodeFullPath4
	#define CHK_VarAccGetNodeFullPath4 (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetNodeFullPath4  CAL_CMEXPAPI( "VarAccGetNodeFullPath4" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetNodeFullPath4  PFVARACCGETNODEFULLPATH4 pfVarAccGetNodeFullPath4;
	#define EXT_VarAccGetNodeFullPath4  extern PFVARACCGETNODEFULLPATH4 pfVarAccGetNodeFullPath4;
	#define GET_VarAccGetNodeFullPath4(fl)  s_pfCMGetAPI2( "VarAccGetNodeFullPath4", (RTS_VOID_FCTPTR *)&pfVarAccGetNodeFullPath4, (fl), 0, 0)
	#define CAL_VarAccGetNodeFullPath4  pfVarAccGetNodeFullPath4
	#define CHK_VarAccGetNodeFullPath4  (pfVarAccGetNodeFullPath4 != NULL)
	#define EXP_VarAccGetNodeFullPath4  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNodeFullPath4", (RTS_UINTPTR)VarAccGetNodeFullPath4, 0, 0) 
#endif




/**
 * <description>IIecVarAccess9::VarAccInitVarInfo</description>
 */
typedef struct tagiiecvaraccess9_varaccinitvarinfo_struct
{
	iiecvaraccess9_struct *pInstance;	/* VAR_INPUT */	
	VariableInformationStruct2 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_UINT nSizeOfVarInfo;		/* VAR_INPUT */	
	RTS_IEC_RESULT VarAccInitVarInfo;	/* VAR_OUTPUT */	
} iiecvaraccess9_varaccinitvarinfo_struct;

void CDECL VarAccInitVarInfo(iiecvaraccess9_varaccinitvarinfo_struct *p);
typedef void (CDECL * PFVARACCINITVARINFO) (iiecvaraccess9_varaccinitvarinfo_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCINITVARINFO_NOTIMPLEMENTED)
	#define USE_VarAccInitVarInfo
	#define EXT_VarAccInitVarInfo
	#define GET_VarAccInitVarInfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccInitVarInfo(p0)  
	#define CHK_VarAccInitVarInfo  FALSE
	#define EXP_VarAccInitVarInfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccInitVarInfo
	#define EXT_VarAccInitVarInfo
	#define GET_VarAccInitVarInfo(fl)  CAL_CMGETAPI( "VarAccInitVarInfo" ) 
	#define CAL_VarAccInitVarInfo  VarAccInitVarInfo
	#define CHK_VarAccInitVarInfo  TRUE
	#define EXP_VarAccInitVarInfo  CAL_CMEXPAPI( "VarAccInitVarInfo" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccInitVarInfo
	#define EXT_VarAccInitVarInfo
	#define GET_VarAccInitVarInfo(fl)  CAL_CMGETAPI( "VarAccInitVarInfo" ) 
	#define CAL_VarAccInitVarInfo  VarAccInitVarInfo
	#define CHK_VarAccInitVarInfo  TRUE
	#define EXP_VarAccInitVarInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccInitVarInfo", (RTS_UINTPTR)VarAccInitVarInfo, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccInitVarInfo
	#define EXT_IecVarAccess_ItfsVarAccInitVarInfo
	#define GET_IecVarAccess_ItfsVarAccInitVarInfo  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccInitVarInfo pIIecVarAccess_Itfs->IVarAccInitVarInfo
	#define CHK_IecVarAccess_ItfsVarAccInitVarInfo (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccInitVarInfo  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccInitVarInfo
	#define EXT_VarAccInitVarInfo
	#define GET_VarAccInitVarInfo(fl)  CAL_CMGETAPI( "VarAccInitVarInfo" ) 
	#define CAL_VarAccInitVarInfo pIIecVarAccess_Itfs->IVarAccInitVarInfo
	#define CHK_VarAccInitVarInfo (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccInitVarInfo  CAL_CMEXPAPI( "VarAccInitVarInfo" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccInitVarInfo  PFVARACCINITVARINFO pfVarAccInitVarInfo;
	#define EXT_VarAccInitVarInfo  extern PFVARACCINITVARINFO pfVarAccInitVarInfo;
	#define GET_VarAccInitVarInfo(fl)  s_pfCMGetAPI2( "VarAccInitVarInfo", (RTS_VOID_FCTPTR *)&pfVarAccInitVarInfo, (fl), 0, 0)
	#define CAL_VarAccInitVarInfo  pfVarAccInitVarInfo
	#define CHK_VarAccInitVarInfo  (pfVarAccInitVarInfo != NULL)
	#define EXP_VarAccInitVarInfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccInitVarInfo", (RTS_UINTPTR)VarAccInitVarInfo, 0, 0) 
#endif




/**
 * <description>IIecVarAccess9::VarAccGetNode4</description>
 */
typedef struct tagiiecvaraccess9_varaccgetnode4_struct
{
	iiecvaraccess9_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_STRING *pszPath;			/* VAR_INPUT */	
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	IBaseTreeNode *VarAccGetNode4;		/* VAR_OUTPUT */	
} iiecvaraccess9_varaccgetnode4_struct;

void CDECL VarAccGetNode4(iiecvaraccess9_varaccgetnode4_struct *p);
typedef void (CDECL * PFVARACCGETNODE4) (iiecvaraccess9_varaccgetnode4_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETNODE4_NOTIMPLEMENTED)
	#define USE_VarAccGetNode4
	#define EXT_VarAccGetNode4
	#define GET_VarAccGetNode4(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetNode4(p0)  
	#define CHK_VarAccGetNode4  FALSE
	#define EXP_VarAccGetNode4  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetNode4
	#define EXT_VarAccGetNode4
	#define GET_VarAccGetNode4(fl)  CAL_CMGETAPI( "VarAccGetNode4" ) 
	#define CAL_VarAccGetNode4  VarAccGetNode4
	#define CHK_VarAccGetNode4  TRUE
	#define EXP_VarAccGetNode4  CAL_CMEXPAPI( "VarAccGetNode4" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetNode4
	#define EXT_VarAccGetNode4
	#define GET_VarAccGetNode4(fl)  CAL_CMGETAPI( "VarAccGetNode4" ) 
	#define CAL_VarAccGetNode4  VarAccGetNode4
	#define CHK_VarAccGetNode4  TRUE
	#define EXP_VarAccGetNode4  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNode4", (RTS_UINTPTR)VarAccGetNode4, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetNode4
	#define EXT_IecVarAccess_ItfsVarAccGetNode4
	#define GET_IecVarAccess_ItfsVarAccGetNode4  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetNode4 pIIecVarAccess_Itfs->IVarAccGetNode4
	#define CHK_IecVarAccess_ItfsVarAccGetNode4 (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetNode4  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetNode4
	#define EXT_VarAccGetNode4
	#define GET_VarAccGetNode4(fl)  CAL_CMGETAPI( "VarAccGetNode4" ) 
	#define CAL_VarAccGetNode4 pIIecVarAccess_Itfs->IVarAccGetNode4
	#define CHK_VarAccGetNode4 (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetNode4  CAL_CMEXPAPI( "VarAccGetNode4" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetNode4  PFVARACCGETNODE4 pfVarAccGetNode4;
	#define EXT_VarAccGetNode4  extern PFVARACCGETNODE4 pfVarAccGetNode4;
	#define GET_VarAccGetNode4(fl)  s_pfCMGetAPI2( "VarAccGetNode4", (RTS_VOID_FCTPTR *)&pfVarAccGetNode4, (fl), 0, 0)
	#define CAL_VarAccGetNode4  pfVarAccGetNode4
	#define CHK_VarAccGetNode4  (pfVarAccGetNode4 != NULL)
	#define EXP_VarAccGetNode4  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNode4", (RTS_UINTPTR)VarAccGetNode4, 0, 0) 
#endif




/**
 * Returns the client side offset of the variable within the containing struct
 * or FB when the whole container is fetched as a blob. 
 */
typedef struct tagiiecvaraccess9_varaccgetclientoffset_struct
{
	iiecvaraccess9_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_XWORD VarAccGetClientOffset;	/* VAR_OUTPUT */	
} iiecvaraccess9_varaccgetclientoffset_struct;

void CDECL VarAccGetClientOffset(iiecvaraccess9_varaccgetclientoffset_struct *p);
typedef void (CDECL * PFVARACCGETCLIENTOFFSET) (iiecvaraccess9_varaccgetclientoffset_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETCLIENTOFFSET_NOTIMPLEMENTED)
	#define USE_VarAccGetClientOffset
	#define EXT_VarAccGetClientOffset
	#define GET_VarAccGetClientOffset(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetClientOffset(p0)  
	#define CHK_VarAccGetClientOffset  FALSE
	#define EXP_VarAccGetClientOffset  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetClientOffset
	#define EXT_VarAccGetClientOffset
	#define GET_VarAccGetClientOffset(fl)  CAL_CMGETAPI( "VarAccGetClientOffset" ) 
	#define CAL_VarAccGetClientOffset  VarAccGetClientOffset
	#define CHK_VarAccGetClientOffset  TRUE
	#define EXP_VarAccGetClientOffset  CAL_CMEXPAPI( "VarAccGetClientOffset" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetClientOffset
	#define EXT_VarAccGetClientOffset
	#define GET_VarAccGetClientOffset(fl)  CAL_CMGETAPI( "VarAccGetClientOffset" ) 
	#define CAL_VarAccGetClientOffset  VarAccGetClientOffset
	#define CHK_VarAccGetClientOffset  TRUE
	#define EXP_VarAccGetClientOffset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetClientOffset", (RTS_UINTPTR)VarAccGetClientOffset, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetClientOffset
	#define EXT_IecVarAccess_ItfsVarAccGetClientOffset
	#define GET_IecVarAccess_ItfsVarAccGetClientOffset  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetClientOffset pIIecVarAccess_Itfs->IVarAccGetClientOffset
	#define CHK_IecVarAccess_ItfsVarAccGetClientOffset (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetClientOffset  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetClientOffset
	#define EXT_VarAccGetClientOffset
	#define GET_VarAccGetClientOffset(fl)  CAL_CMGETAPI( "VarAccGetClientOffset" ) 
	#define CAL_VarAccGetClientOffset pIIecVarAccess_Itfs->IVarAccGetClientOffset
	#define CHK_VarAccGetClientOffset (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetClientOffset  CAL_CMEXPAPI( "VarAccGetClientOffset" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetClientOffset  PFVARACCGETCLIENTOFFSET pfVarAccGetClientOffset;
	#define EXT_VarAccGetClientOffset  extern PFVARACCGETCLIENTOFFSET pfVarAccGetClientOffset;
	#define GET_VarAccGetClientOffset(fl)  s_pfCMGetAPI2( "VarAccGetClientOffset", (RTS_VOID_FCTPTR *)&pfVarAccGetClientOffset, (fl), 0, 0)
	#define CAL_VarAccGetClientOffset  pfVarAccGetClientOffset
	#define CHK_VarAccGetClientOffset  (pfVarAccGetClientOffset != NULL)
	#define EXP_VarAccGetClientOffset  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetClientOffset", (RTS_UINTPTR)VarAccGetClientOffset, 0, 0) 
#endif




/**
 * <description>IIecVarAccess9::VarAccBrowseDown2</description>
 */
typedef struct tagiiecvaraccess9_varaccbrowsedown2_struct
{
	iiecvaraccess9_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	IBaseTreeNode *VarAccBrowseDown2;	/* VAR_OUTPUT */	
} iiecvaraccess9_varaccbrowsedown2_struct;

void CDECL VarAccBrowseDown2(iiecvaraccess9_varaccbrowsedown2_struct *p);
typedef void (CDECL * PFVARACCBROWSEDOWN2) (iiecvaraccess9_varaccbrowsedown2_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCBROWSEDOWN2_NOTIMPLEMENTED)
	#define USE_VarAccBrowseDown2
	#define EXT_VarAccBrowseDown2
	#define GET_VarAccBrowseDown2(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccBrowseDown2(p0)  
	#define CHK_VarAccBrowseDown2  FALSE
	#define EXP_VarAccBrowseDown2  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccBrowseDown2
	#define EXT_VarAccBrowseDown2
	#define GET_VarAccBrowseDown2(fl)  CAL_CMGETAPI( "VarAccBrowseDown2" ) 
	#define CAL_VarAccBrowseDown2  VarAccBrowseDown2
	#define CHK_VarAccBrowseDown2  TRUE
	#define EXP_VarAccBrowseDown2  CAL_CMEXPAPI( "VarAccBrowseDown2" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccBrowseDown2
	#define EXT_VarAccBrowseDown2
	#define GET_VarAccBrowseDown2(fl)  CAL_CMGETAPI( "VarAccBrowseDown2" ) 
	#define CAL_VarAccBrowseDown2  VarAccBrowseDown2
	#define CHK_VarAccBrowseDown2  TRUE
	#define EXP_VarAccBrowseDown2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccBrowseDown2", (RTS_UINTPTR)VarAccBrowseDown2, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccBrowseDown2
	#define EXT_IecVarAccess_ItfsVarAccBrowseDown2
	#define GET_IecVarAccess_ItfsVarAccBrowseDown2  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccBrowseDown2 pIIecVarAccess_Itfs->IVarAccBrowseDown2
	#define CHK_IecVarAccess_ItfsVarAccBrowseDown2 (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccBrowseDown2  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccBrowseDown2
	#define EXT_VarAccBrowseDown2
	#define GET_VarAccBrowseDown2(fl)  CAL_CMGETAPI( "VarAccBrowseDown2" ) 
	#define CAL_VarAccBrowseDown2 pIIecVarAccess_Itfs->IVarAccBrowseDown2
	#define CHK_VarAccBrowseDown2 (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccBrowseDown2  CAL_CMEXPAPI( "VarAccBrowseDown2" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccBrowseDown2  PFVARACCBROWSEDOWN2 pfVarAccBrowseDown2;
	#define EXT_VarAccBrowseDown2  extern PFVARACCBROWSEDOWN2 pfVarAccBrowseDown2;
	#define GET_VarAccBrowseDown2(fl)  s_pfCMGetAPI2( "VarAccBrowseDown2", (RTS_VOID_FCTPTR *)&pfVarAccBrowseDown2, (fl), 0, 0)
	#define CAL_VarAccBrowseDown2  pfVarAccBrowseDown2
	#define CHK_VarAccBrowseDown2  (pfVarAccBrowseDown2 != NULL)
	#define EXP_VarAccBrowseDown2  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccBrowseDown2", (RTS_UINTPTR)VarAccBrowseDown2, 0, 0) 
#endif




/**
 * <description>IIecVarAccess9::VarAccGetNodeName4</description>
 */
typedef struct tagiiecvaraccess9_varaccgetnodename4_struct
{
	iiecvaraccess9_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	VariableInformationStruct3 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_STRING *pszNodeName;		/* VAR_INPUT */	
	RTS_IEC_UDINT nNodeNameLen;			/* VAR_INPUT */	
	RTS_IEC_RESULT VarAccGetNodeName4;	/* VAR_OUTPUT */	
} iiecvaraccess9_varaccgetnodename4_struct;

void CDECL VarAccGetNodeName4(iiecvaraccess9_varaccgetnodename4_struct *p);
typedef void (CDECL * PFVARACCGETNODENAME4) (iiecvaraccess9_varaccgetnodename4_struct *p);
#if defined(IECVARACCESS_ITFS_NOTIMPLEMENTED) || defined(VARACCGETNODENAME4_NOTIMPLEMENTED)
	#define USE_VarAccGetNodeName4
	#define EXT_VarAccGetNodeName4
	#define GET_VarAccGetNodeName4(fl)  ERR_NOTIMPLEMENTED
	#define CAL_VarAccGetNodeName4(p0)  
	#define CHK_VarAccGetNodeName4  FALSE
	#define EXP_VarAccGetNodeName4  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_VarAccGetNodeName4
	#define EXT_VarAccGetNodeName4
	#define GET_VarAccGetNodeName4(fl)  CAL_CMGETAPI( "VarAccGetNodeName4" ) 
	#define CAL_VarAccGetNodeName4  VarAccGetNodeName4
	#define CHK_VarAccGetNodeName4  TRUE
	#define EXP_VarAccGetNodeName4  CAL_CMEXPAPI( "VarAccGetNodeName4" ) 
#elif defined(MIXED_LINK) && !defined(IECVARACCESS_ITFS_EXTERNAL)
	#define USE_VarAccGetNodeName4
	#define EXT_VarAccGetNodeName4
	#define GET_VarAccGetNodeName4(fl)  CAL_CMGETAPI( "VarAccGetNodeName4" ) 
	#define CAL_VarAccGetNodeName4  VarAccGetNodeName4
	#define CHK_VarAccGetNodeName4  TRUE
	#define EXP_VarAccGetNodeName4  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNodeName4", (RTS_UINTPTR)VarAccGetNodeName4, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_IecVarAccess_ItfsVarAccGetNodeName4
	#define EXT_IecVarAccess_ItfsVarAccGetNodeName4
	#define GET_IecVarAccess_ItfsVarAccGetNodeName4  ERR_OK
	#define CAL_IecVarAccess_ItfsVarAccGetNodeName4 pIIecVarAccess_Itfs->IVarAccGetNodeName4
	#define CHK_IecVarAccess_ItfsVarAccGetNodeName4 (pIIecVarAccess_Itfs != NULL)
	#define EXP_IecVarAccess_ItfsVarAccGetNodeName4  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_VarAccGetNodeName4
	#define EXT_VarAccGetNodeName4
	#define GET_VarAccGetNodeName4(fl)  CAL_CMGETAPI( "VarAccGetNodeName4" ) 
	#define CAL_VarAccGetNodeName4 pIIecVarAccess_Itfs->IVarAccGetNodeName4
	#define CHK_VarAccGetNodeName4 (pIIecVarAccess_Itfs != NULL)
	#define EXP_VarAccGetNodeName4  CAL_CMEXPAPI( "VarAccGetNodeName4" ) 
#else /* DYNAMIC_LINK */
	#define USE_VarAccGetNodeName4  PFVARACCGETNODENAME4 pfVarAccGetNodeName4;
	#define EXT_VarAccGetNodeName4  extern PFVARACCGETNODENAME4 pfVarAccGetNodeName4;
	#define GET_VarAccGetNodeName4(fl)  s_pfCMGetAPI2( "VarAccGetNodeName4", (RTS_VOID_FCTPTR *)&pfVarAccGetNodeName4, (fl), 0, 0)
	#define CAL_VarAccGetNodeName4  pfVarAccGetNodeName4
	#define CHK_VarAccGetNodeName4  (pfVarAccGetNodeName4 != NULL)
	#define EXP_VarAccGetNodeName4  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"VarAccGetNodeName4", (RTS_UINTPTR)VarAccGetNodeName4, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
	PFVARACCGETNAMESPACENODEFLAGS IVarAccGetNamespaceNodeFlags;
 	PFVARACCEXECUTECALL IVarAccExecuteCall;
 	PFVARACCGETENUMMEMBERATTRIBUTELIST IVarAccGetEnumMemberAttributeList;
 	PFVARACCGETNUMOFTYPEATTRIBUTES IVarAccGetNumOfTypeAttributes;
 	PFVARACCGETTYPEATTRIBUTEBYINDEX IVarAccGetTypeAttributeByIndex;
 	PFVARACCGETCONTENTFEATUREFLAGS IVarAccGetContentFeatureFlags;
 	PFVARACCGETRANGE IVarAccGetRange;
 	PFVARACCGETSWAPSIZE IVarAccGetSwapSize;
 	PFVARACCENDVARIABLECONFIGURATION IVarAccEndVariableConfiguration;
 	PFVARACCSWAP IVarAccSwap;
 	PFVARACCREMOVEVARIABLE IVarAccRemoveVariable;
 	PFVARACCBROWSEGETROOT IVarAccBrowseGetRoot;
 	PFVARACCBROWSEGETNEXT IVarAccBrowseGetNext;
 	PFVARACCGETACCESSRIGHTS IVarAccGetAccessRights;
 	PFVARACCSETVALUE IVarAccSetValue;
 	PFVARACCGETNODEFULLPATH IVarAccGetNodeFullPath;
 	PFVARACCGETTYPEDESC IVarAccGetTypeDesc;
 	PFVARACCAPPENDVARIABLE IVarAccAppendVariable;
 	PFVARACCGETNODETYPE IVarAccGetNodeType;
 	PFVARACCBROWSEDOWN IVarAccBrowseDown;
 	PFVARACCGETSIZE IVarAccGetSize;
 	PFVARACCGETTYPENODE2 IVarAccGetTypeNode2;
 	PFVARACCGETTYPENODE IVarAccGetTypeNode;
 	PFVARACCBEGINVARIABLECONFIGURATION IVarAccBeginVariableConfiguration;
 	PFVARACCGETADDRESS2 IVarAccGetAddress2;
 	PFVARACCSWAP2 IVarAccSwap2;
 	PFVARACCBROWSEUP IVarAccBrowseUp;
 	PFVARACCGETSIZE2 IVarAccGetSize2;
 	PFVARACCGETADDRESS IVarAccGetAddress;
 	PFVARACCGETNODENAME IVarAccGetNodeName;
 	PFVARACCGETVALUE IVarAccGetValue;
 	PFVARACCGETNODE IVarAccGetNode;
 	PFVARACCGETTYPECLASS IVarAccGetTypeClass;
 	PFVARACCGETSIZE3 IVarAccGetSize3;
 	PFVARACCGETNODEFULLPATH3 IVarAccGetNodeFullPath3;
 	PFVARACCSETVALUE3 IVarAccSetValue3;
 	PFVARACCGETADDRESS3 IVarAccGetAddress3;
 	PFVARACCAPPENDVARIABLE3 IVarAccAppendVariable3;
 	PFVARACCGETVALUE3 IVarAccGetValue3;
 	PFVARACCGETNODE3 IVarAccGetNode3;
 	PFVARACCGETTYPENODE3 IVarAccGetTypeNode3;
 	PFVARACCGETTYPECLASS3 IVarAccGetTypeClass3;
 	PFVARACCREMOVEVARIABLE3 IVarAccRemoveVariable3;
 	PFVARACCSWAP3 IVarAccSwap3;
 	PFVARACCGETNODENAME3 IVarAccGetNodeName3;
 	PFVARACCBROWSEGETCHILDBYINDEX IVarAccBrowseGetChildByIndex;
 	PFVARACCENTERACCESS IVarAccEnterAccess;
 	PFVARACCGETNUMOFATTRIBUTES IVarAccGetNumOfAttributes;
 	PFVARACCGETATTRIBUTEBYINDEX IVarAccGetAttributeByIndex;
 	PFVARACCGETNODEFLAGS IVarAccGetNodeFlags;
 	PFVARACCGETNUMOFTYPES IVarAccGetNumOfTypes;
 	PFVARACCGETENUMVALUES IVarAccGetEnumValues;
 	PFVARACCGETTYPENAME IVarAccGetTypeName;
 	PFVARACCGETTYPENODEBYINDEX IVarAccGetTypeNodeByIndex;
 	PFVARACCGETTYPECLASSFROMTYPE IVarAccGetTypeClassFromType;
 	PFVARACCLEAVEACCESS IVarAccLeaveAccess;
 	PFVARACCGETBASETYPE IVarAccGetBaseType;
 	PFVARACCHASBASETYPE IVarAccHasBaseType;
 	PFVARACCBROWSEUP2 IVarAccBrowseUp2;
 	PFVARACCEXITVARINFO IVarAccExitVarInfo;
 	PFVARACCBROWSERECURSIVE IVarAccBrowseRecursive;
 	PFVARACCBROWSEGETNEXT2 IVarAccBrowseGetNext2;
 	PFVARACCGETNODEFULLPATH4 IVarAccGetNodeFullPath4;
 	PFVARACCINITVARINFO IVarAccInitVarInfo;
 	PFVARACCGETNODE4 IVarAccGetNode4;
 	PFVARACCGETCLIENTOFFSET IVarAccGetClientOffset;
 	PFVARACCBROWSEDOWN2 IVarAccBrowseDown2;
 	PFVARACCGETNODENAME4 IVarAccGetNodeName4;
 } IIecVarAccess_Itfs_C;

#ifdef CPLUSPLUS
class IIecVarAccess_Itfs : public IBase
{
	public:
		virtual void CDECL IVarAccGetNamespaceNodeFlags(iiecvaraccess10_varaccgetnamespacenodeflags_struct *p) =0;
		virtual void CDECL IVarAccExecuteCall(iiecvaraccess11_varaccexecutecall_struct *p) =0;
		virtual void CDECL IVarAccGetEnumMemberAttributeList(iiecvaraccess11_varaccgetenummemberattributelist_struct *p) =0;
		virtual void CDECL IVarAccGetNumOfTypeAttributes(iiecvaraccess11_varaccgetnumoftypeattributes_struct *p) =0;
		virtual void CDECL IVarAccGetTypeAttributeByIndex(iiecvaraccess11_varaccgettypeattributebyindex_struct *p) =0;
		virtual void CDECL IVarAccGetContentFeatureFlags(iiecvaraccess12_varaccgetcontentfeatureflags_struct *p) =0;
		virtual void CDECL IVarAccGetRange(iiecvaraccess12_varaccgetrange_struct *p) =0;
		virtual void CDECL IVarAccGetSwapSize(iiecvaraccess4_varaccgetswapsize_struct *p) =0;
		virtual void CDECL IVarAccEndVariableConfiguration(iiecvaraccess4_varaccendvariableconfiguration_struct *p) =0;
		virtual void CDECL IVarAccSwap(iiecvaraccess4_varaccswap_struct *p) =0;
		virtual void CDECL IVarAccRemoveVariable(iiecvaraccess4_varaccremovevariable_struct *p) =0;
		virtual void CDECL IVarAccBrowseGetRoot(iiecvaraccess4_varaccbrowsegetroot_struct *p) =0;
		virtual void CDECL IVarAccBrowseGetNext(iiecvaraccess4_varaccbrowsegetnext_struct *p) =0;
		virtual void CDECL IVarAccGetAccessRights(iiecvaraccess4_varaccgetaccessrights_struct *p) =0;
		virtual void CDECL IVarAccSetValue(iiecvaraccess4_varaccsetvalue_struct *p) =0;
		virtual void CDECL IVarAccGetNodeFullPath(iiecvaraccess4_varaccgetnodefullpath_struct *p) =0;
		virtual void CDECL IVarAccGetTypeDesc(iiecvaraccess4_varaccgettypedesc_struct *p) =0;
		virtual void CDECL IVarAccAppendVariable(iiecvaraccess4_varaccappendvariable_struct *p) =0;
		virtual void CDECL IVarAccGetNodeType(iiecvaraccess4_varaccgetnodetype_struct *p) =0;
		virtual void CDECL IVarAccBrowseDown(iiecvaraccess4_varaccbrowsedown_struct *p) =0;
		virtual void CDECL IVarAccGetSize(iiecvaraccess4_varaccgetsize_struct *p) =0;
		virtual void CDECL IVarAccGetTypeNode2(iiecvaraccess4_varaccgettypenode2_struct *p) =0;
		virtual void CDECL IVarAccGetTypeNode(iiecvaraccess4_varaccgettypenode_struct *p) =0;
		virtual void CDECL IVarAccBeginVariableConfiguration(iiecvaraccess4_varaccbeginvariableconfiguration_struct *p) =0;
		virtual void CDECL IVarAccGetAddress2(iiecvaraccess4_varaccgetaddress2_struct *p) =0;
		virtual void CDECL IVarAccSwap2(iiecvaraccess4_varaccswap2_struct *p) =0;
		virtual void CDECL IVarAccBrowseUp(iiecvaraccess4_varaccbrowseup_struct *p) =0;
		virtual void CDECL IVarAccGetSize2(iiecvaraccess4_varaccgetsize2_struct *p) =0;
		virtual void CDECL IVarAccGetAddress(iiecvaraccess4_varaccgetaddress_struct *p) =0;
		virtual void CDECL IVarAccGetNodeName(iiecvaraccess4_varaccgetnodename_struct *p) =0;
		virtual void CDECL IVarAccGetValue(iiecvaraccess4_varaccgetvalue_struct *p) =0;
		virtual void CDECL IVarAccGetNode(iiecvaraccess4_varaccgetnode_struct *p) =0;
		virtual void CDECL IVarAccGetTypeClass(iiecvaraccess4_varaccgettypeclass_struct *p) =0;
		virtual void CDECL IVarAccGetSize3(iiecvaraccess5_varaccgetsize3_struct *p) =0;
		virtual void CDECL IVarAccGetNodeFullPath3(iiecvaraccess5_varaccgetnodefullpath3_struct *p) =0;
		virtual void CDECL IVarAccSetValue3(iiecvaraccess5_varaccsetvalue3_struct *p) =0;
		virtual void CDECL IVarAccGetAddress3(iiecvaraccess5_varaccgetaddress3_struct *p) =0;
		virtual void CDECL IVarAccAppendVariable3(iiecvaraccess5_varaccappendvariable3_struct *p) =0;
		virtual void CDECL IVarAccGetValue3(iiecvaraccess5_varaccgetvalue3_struct *p) =0;
		virtual void CDECL IVarAccGetNode3(iiecvaraccess5_varaccgetnode3_struct *p) =0;
		virtual void CDECL IVarAccGetTypeNode3(iiecvaraccess5_varaccgettypenode3_struct *p) =0;
		virtual void CDECL IVarAccGetTypeClass3(iiecvaraccess5_varaccgettypeclass3_struct *p) =0;
		virtual void CDECL IVarAccRemoveVariable3(iiecvaraccess5_varaccremovevariable3_struct *p) =0;
		virtual void CDECL IVarAccSwap3(iiecvaraccess5_varaccswap3_struct *p) =0;
		virtual void CDECL IVarAccGetNodeName3(iiecvaraccess5_varaccgetnodename3_struct *p) =0;
		virtual void CDECL IVarAccBrowseGetChildByIndex(iiecvaraccess6_varaccbrowsegetchildbyindex_struct *p) =0;
		virtual void CDECL IVarAccEnterAccess(iiecvaraccess7_varaccenteraccess_struct *p) =0;
		virtual void CDECL IVarAccGetNumOfAttributes(iiecvaraccess7_varaccgetnumofattributes_struct *p) =0;
		virtual void CDECL IVarAccGetAttributeByIndex(iiecvaraccess7_varaccgetattributebyindex_struct *p) =0;
		virtual void CDECL IVarAccGetNodeFlags(iiecvaraccess7_varaccgetnodeflags_struct *p) =0;
		virtual void CDECL IVarAccGetNumOfTypes(iiecvaraccess7_varaccgetnumoftypes_struct *p) =0;
		virtual void CDECL IVarAccGetEnumValues(iiecvaraccess7_varaccgetenumvalues_struct *p) =0;
		virtual void CDECL IVarAccGetTypeName(iiecvaraccess7_varaccgettypename_struct *p) =0;
		virtual void CDECL IVarAccGetTypeNodeByIndex(iiecvaraccess7_varaccgettypenodebyindex_struct *p) =0;
		virtual void CDECL IVarAccGetTypeClassFromType(iiecvaraccess7_varaccgettypeclassfromtype_struct *p) =0;
		virtual void CDECL IVarAccLeaveAccess(iiecvaraccess7_varaccleaveaccess_struct *p) =0;
		virtual void CDECL IVarAccGetBaseType(iiecvaraccess8_varaccgetbasetype_struct *p) =0;
		virtual void CDECL IVarAccHasBaseType(iiecvaraccess8_varacchasbasetype_struct *p) =0;
		virtual void CDECL IVarAccBrowseUp2(iiecvaraccess9_varaccbrowseup2_struct *p) =0;
		virtual void CDECL IVarAccExitVarInfo(iiecvaraccess9_varaccexitvarinfo_struct *p) =0;
		virtual void CDECL IVarAccBrowseRecursive(iiecvaraccess9_varaccbrowserecursive_struct *p) =0;
		virtual void CDECL IVarAccBrowseGetNext2(iiecvaraccess9_varaccbrowsegetnext2_struct *p) =0;
		virtual void CDECL IVarAccGetNodeFullPath4(iiecvaraccess9_varaccgetnodefullpath4_struct *p) =0;
		virtual void CDECL IVarAccInitVarInfo(iiecvaraccess9_varaccinitvarinfo_struct *p) =0;
		virtual void CDECL IVarAccGetNode4(iiecvaraccess9_varaccgetnode4_struct *p) =0;
		virtual void CDECL IVarAccGetClientOffset(iiecvaraccess9_varaccgetclientoffset_struct *p) =0;
		virtual void CDECL IVarAccBrowseDown2(iiecvaraccess9_varaccbrowsedown2_struct *p) =0;
		virtual void CDECL IVarAccGetNodeName4(iiecvaraccess9_varaccgetnodename4_struct *p) =0;
};
	#ifndef ITF_IecVarAccess_Itfs
		#define ITF_IecVarAccess_Itfs static IIecVarAccess_Itfs *pIIecVarAccess_Itfs = NULL;
	#endif
	#define EXTITF_IecVarAccess_Itfs
#else	/*CPLUSPLUS*/
	typedef IIecVarAccess_Itfs_C		IIecVarAccess_Itfs;
	#ifndef ITF_IecVarAccess_Itfs
		#define ITF_IecVarAccess_Itfs
	#endif
	#define EXTITF_IecVarAccess_Itfs
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_IECVARACCESS_ITFSITF_H_*/
