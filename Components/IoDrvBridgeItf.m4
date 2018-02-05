/**
 * <interfacename>IoDrvBridge</interfacename>
 * <description>IoDrvBridge interface.</description>
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`IoDrvBridge')

/**
 * <category>Static defines</category>
 * <description>Maximum mapped elements</description>
 */
#ifndef NUM_OF_MAPPED_COPIED_ELEMENTS
    #define NUM_OF_MAPPED_COPIED_ELEMENTS	150
#endif

/**
 * <category>Static defines</category>
 * <description>Maximum num of drivers</description>
 */
#ifndef NUM_OF_DRIVER_ELEMENTS
	#define NUM_OF_DRIVER_ELEMENTS	10
#endif

/**
 * <category>Static defines</category>
 * <description>Maximum size of copied IO configuration buffer</description>
 */
#ifndef COPIED_IO_CONFIG_SIZE
	#define COPIED_IO_CONFIG_SIZE	0x4000
#endif

/**
 * <category>Static defines</category>
 * <description>Alignment of copied IO configuration buffer</description>
 */
#ifndef COPIED_IO_CONFIG_ALIGNMENT
	#define COPIED_IO_CONFIG_ALIGNMENT	4
#endif

/**
 * <category>Static defines</category>
 * <description>Period of connector flags update in ms</description>
 */
#ifndef IODRVBRIDGE_CONNECTOR_FLAGS_UPDATE_PERIOD
	#define IODRVBRIDGE_CONNECTOR_FLAGS_UPDATE_PERIOD	2000
#endif

/**
 * <category>Static defines</category>
 * <description>
 *	List of supported safe IO drivers
 *	CANOpenSafety: wModuleType = 0x15
 * </description>
 */
#ifndef SUPPORTED_SAFE_IODRIVERS_LIST
	#define SUPPORTED_SAFE_IODRIVERS_LIST \
			CT_CANOPEN_SAFETY, \
			CT_CANOPEN_SAFETY_SLAVE, \
			0
#endif

/**
 * <SIL2/>
 * <category>Typedef</category>
 * <description><p>SIL2 life counter for safe comm cycle hook</p>
 * </description>
 */
#ifdef RTS_SIL2
extern RTS_UI32 g_RTS_SIL2_Cycle_LifeCounter_IoDrvUnsafeBridge;
#endif

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

