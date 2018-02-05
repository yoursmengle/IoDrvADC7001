/**
 * <interfacename>test</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`IoDrvConFE')

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>myexternalfunction</description>
 */
typedef struct tagmyexternalfunction_struct
{
	RTS_IEC_INT MyExternalFunction;		/* VAR_OUTPUT */
} myexternalfunction_struct;

DEF_API(`void',`CDECL',`myexternalfunction',`(myexternalfunction_struct *p)',1,0xE1C6D757,0x3040000)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

