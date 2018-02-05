/**
 * <interfacename>IecVarAccess_Itfs</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`IecVarAccess_Itfs')

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
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

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

DEF_ITF_API(`void',`CDECL',`VarAccGetNamespaceNodeFlags',`(iiecvaraccess10_varaccgetnamespacenodeflags_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccExecuteCall',`(iiecvaraccess11_varaccexecutecall_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetEnumMemberAttributeList',`(iiecvaraccess11_varaccgetenummemberattributelist_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetNumOfTypeAttributes',`(iiecvaraccess11_varaccgetnumoftypeattributes_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetTypeAttributeByIndex',`(iiecvaraccess11_varaccgettypeattributebyindex_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetContentFeatureFlags',`(iiecvaraccess12_varaccgetcontentfeatureflags_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetRange',`(iiecvaraccess12_varaccgetrange_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetSwapSize',`(iiecvaraccess4_varaccgetswapsize_struct *p)')

/**
 * <description>IIecVarAccess4::VarAccEndVariableConfiguration</description>
 */
typedef struct tagiiecvaraccess4_varaccendvariableconfiguration_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_UDINT VarAccEndVariableConfiguration;	/* VAR_OUTPUT */	
} iiecvaraccess4_varaccendvariableconfiguration_struct;

DEF_ITF_API(`void',`CDECL',`VarAccEndVariableConfiguration',`(iiecvaraccess4_varaccendvariableconfiguration_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccSwap',`(iiecvaraccess4_varaccswap_struct *p)')

/**
 * <description>IIecVarAccess4::VarAccRemoveVariable</description>
 */
typedef struct tagiiecvaraccess4_varaccremovevariable_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_UDINT VarAccRemoveVariable;	/* VAR_OUTPUT */	
} iiecvaraccess4_varaccremovevariable_struct;

DEF_ITF_API(`void',`CDECL',`VarAccRemoveVariable',`(iiecvaraccess4_varaccremovevariable_struct *p)')

/**
 * <description>IIecVarAccess4::VarAccBrowseGetRoot</description>
 */
typedef struct tagiiecvaraccess4_varaccbrowsegetroot_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_UDINT *pResult;				/* VAR_INPUT */	
	IBaseTreeNode *VarAccBrowseGetRoot;	/* VAR_OUTPUT */	
} iiecvaraccess4_varaccbrowsegetroot_struct;

DEF_ITF_API(`void',`CDECL',`VarAccBrowseGetRoot',`(iiecvaraccess4_varaccbrowsegetroot_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccBrowseGetNext',`(iiecvaraccess4_varaccbrowsegetnext_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetAccessRights',`(iiecvaraccess4_varaccgetaccessrights_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccSetValue',`(iiecvaraccess4_varaccsetvalue_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetNodeFullPath',`(iiecvaraccess4_varaccgetnodefullpath_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetTypeDesc',`(iiecvaraccess4_varaccgettypedesc_struct *p)')

/**
 * <description>IIecVarAccess4::VarAccAppendVariable</description>
 */
typedef struct tagiiecvaraccess4_varaccappendvariable_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	IBaseTreeNode *pNode;				/* VAR_INPUT */	
	RTS_IEC_UDINT VarAccAppendVariable;	/* VAR_OUTPUT */	
} iiecvaraccess4_varaccappendvariable_struct;

DEF_ITF_API(`void',`CDECL',`VarAccAppendVariable',`(iiecvaraccess4_varaccappendvariable_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetNodeType',`(iiecvaraccess4_varaccgetnodetype_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccBrowseDown',`(iiecvaraccess4_varaccbrowsedown_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetSize',`(iiecvaraccess4_varaccgetsize_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetTypeNode2',`(iiecvaraccess4_varaccgettypenode2_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetTypeNode',`(iiecvaraccess4_varaccgettypenode_struct *p)')

/**
 * <description>IIecVarAccess4::VarAccBeginVariableConfiguration</description>
 */
typedef struct tagiiecvaraccess4_varaccbeginvariableconfiguration_struct
{
	iiecvaraccess4_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_BOOL bBlocking;				/* VAR_INPUT */	
	RTS_IEC_UDINT VarAccBeginVariableConfiguration;	/* VAR_OUTPUT */	
} iiecvaraccess4_varaccbeginvariableconfiguration_struct;

DEF_ITF_API(`void',`CDECL',`VarAccBeginVariableConfiguration',`(iiecvaraccess4_varaccbeginvariableconfiguration_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetAddress2',`(iiecvaraccess4_varaccgetaddress2_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccSwap2',`(iiecvaraccess4_varaccswap2_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccBrowseUp',`(iiecvaraccess4_varaccbrowseup_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetSize2',`(iiecvaraccess4_varaccgetsize2_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetAddress',`(iiecvaraccess4_varaccgetaddress_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetNodeName',`(iiecvaraccess4_varaccgetnodename_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetValue',`(iiecvaraccess4_varaccgetvalue_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetNode',`(iiecvaraccess4_varaccgetnode_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetTypeClass',`(iiecvaraccess4_varaccgettypeclass_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetSize3',`(iiecvaraccess5_varaccgetsize3_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetNodeFullPath3',`(iiecvaraccess5_varaccgetnodefullpath3_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccSetValue3',`(iiecvaraccess5_varaccsetvalue3_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetAddress3',`(iiecvaraccess5_varaccgetaddress3_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccAppendVariable3',`(iiecvaraccess5_varaccappendvariable3_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetValue3',`(iiecvaraccess5_varaccgetvalue3_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetNode3',`(iiecvaraccess5_varaccgetnode3_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetTypeNode3',`(iiecvaraccess5_varaccgettypenode3_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetTypeClass3',`(iiecvaraccess5_varaccgettypeclass3_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccRemoveVariable3',`(iiecvaraccess5_varaccremovevariable3_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccSwap3',`(iiecvaraccess5_varaccswap3_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetNodeName3',`(iiecvaraccess5_varaccgetnodename3_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccBrowseGetChildByIndex',`(iiecvaraccess6_varaccbrowsegetchildbyindex_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccEnterAccess',`(iiecvaraccess7_varaccenteraccess_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetNumOfAttributes',`(iiecvaraccess7_varaccgetnumofattributes_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetAttributeByIndex',`(iiecvaraccess7_varaccgetattributebyindex_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetNodeFlags',`(iiecvaraccess7_varaccgetnodeflags_struct *p)')

/**
 * <description>IIecVarAccess7::VarAccGetNumOfTypes</description>
 */
typedef struct tagiiecvaraccess7_varaccgetnumoftypes_struct
{
	iiecvaraccess7_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_RESULT *pResult;			/* VAR_INPUT */	
	RTS_IEC_DINT VarAccGetNumOfTypes;	/* VAR_OUTPUT */	
} iiecvaraccess7_varaccgetnumoftypes_struct;

DEF_ITF_API(`void',`CDECL',`VarAccGetNumOfTypes',`(iiecvaraccess7_varaccgetnumoftypes_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetEnumValues',`(iiecvaraccess7_varaccgetenumvalues_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetTypeName',`(iiecvaraccess7_varaccgettypename_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetTypeNodeByIndex',`(iiecvaraccess7_varaccgettypenodebyindex_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetTypeClassFromType',`(iiecvaraccess7_varaccgettypeclassfromtype_struct *p)')

/**
 * <description>IIecVarAccess7::VarAccLeaveAccess</description>
 */
typedef struct tagiiecvaraccess7_varaccleaveaccess_struct
{
	iiecvaraccess7_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_RESULT VarAccLeaveAccess;	/* VAR_OUTPUT */	
} iiecvaraccess7_varaccleaveaccess_struct;

DEF_ITF_API(`void',`CDECL',`VarAccLeaveAccess',`(iiecvaraccess7_varaccleaveaccess_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetBaseType',`(iiecvaraccess8_varaccgetbasetype_struct *p)')

/**
 * <description>IIecVarAccess8::VarAccHasBaseType</description>
 */
typedef struct tagiiecvaraccess8_varacchasbasetype_struct
{
	iiecvaraccess8_struct *pInstance;	/* VAR_INPUT */	
	ITypeDesc *typeDesc;				/* VAR_INPUT */	
	RTS_IEC_BOOL VarAccHasBaseType;		/* VAR_OUTPUT */	
} iiecvaraccess8_varacchasbasetype_struct;

DEF_ITF_API(`void',`CDECL',`VarAccHasBaseType',`(iiecvaraccess8_varacchasbasetype_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccBrowseUp2',`(iiecvaraccess9_varaccbrowseup2_struct *p)')

/**
 * <description>IIecVarAccess9::VarAccExitVarInfo</description>
 */
typedef struct tagiiecvaraccess9_varaccexitvarinfo_struct
{
	iiecvaraccess9_struct *pInstance;	/* VAR_INPUT */	
	VariableInformationStruct2 *pVariableInformation;	/* VAR_INPUT */	
	RTS_IEC_RESULT VarAccExitVarInfo;	/* VAR_OUTPUT */	
} iiecvaraccess9_varaccexitvarinfo_struct;

DEF_ITF_API(`void',`CDECL',`VarAccExitVarInfo',`(iiecvaraccess9_varaccexitvarinfo_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccBrowseRecursive',`(iiecvaraccess9_varaccbrowserecursive_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccBrowseGetNext2',`(iiecvaraccess9_varaccbrowsegetnext2_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetNodeFullPath4',`(iiecvaraccess9_varaccgetnodefullpath4_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccInitVarInfo',`(iiecvaraccess9_varaccinitvarinfo_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetNode4',`(iiecvaraccess9_varaccgetnode4_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetClientOffset',`(iiecvaraccess9_varaccgetclientoffset_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccBrowseDown2',`(iiecvaraccess9_varaccbrowsedown2_struct *p)')

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

DEF_ITF_API(`void',`CDECL',`VarAccGetNodeName4',`(iiecvaraccess9_varaccgetnodename4_struct *p)')

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

