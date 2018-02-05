 /**
 * <interfacename>SysFramebuffer</interfacename>
 * <description> 
 *	SysFramebuffer interface. This interface could be implemented by different components.
 * </description>
 *
 * <copyright>(c) 2003-2017 3S-Smart Software Solutions</copyright>
 */

	
	
#ifndef _SYSFRAMEBUFFERITF_H_
#define _SYSFRAMEBUFFERITF_H_

#include "CmpStd.h"

 

 




#include <CmpStd.h>
#include <SysGraphicBase.h>

/* Settings for SysFramebuffer */
/* --------------------------- */


/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Color palette options
 * This is the size of the color conversion buffer. This value is used in indexed color
 * modes for optimizing the mapping of colors to their indices in the color palette.
 * The value must be a power of 2 and maximal 256! 
 * <description>
 */
#ifndef FB_PAL_CONV_BUFFER_SIZE
#define FB_PAL_CONV_BUFFER_SIZE				16
#endif					

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 * Platform native register type
 * This define is used to choose optimized implementations of graphical algorithms.
 * The following values are possible at the moment:
 *	- FB_PLATFORM_16_LE:		16bit little endian, e.g. Infineon XC16x series
 *	- FB_PLATFORM_16_BE:		16bit big endian
 *	- FB_PLATFORM_32_LE:		32bit little endian, e.g. x86 series
 *	- FB_PLATFORM_32_BE:		32bit big endian, e.g. Motorola/Freescale PowerPC series
 *	- FB_PLATFORM_INDEPENDENT:	working on every platform but maybe not the optimal performance will be achieved
 * <description> 
*/
#ifndef FB_PLATFORM
#define FB_PLATFORM							FB_PLATFORM_32_LE	
#endif	

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 * Arithmetic function approximation options
 * In order to run smothely even on small embedded systems, you might switch
 * to approximative functions instead of fully accurate functions.
 * WARNING: Different algorithms will implement approximation differently.
 * Some algorithms might lack drawing precision when approximation is used and some others
 * won't work at all!
 * <description> 
 */
#ifndef FB_USE_SQRT
#define	FB_USE_SQRT							FB_YES		/* default FB_NO		//use square root function or use an approximation? */
#endif

#ifndef FB_USE_FLOAT
#define FB_USE_FLOAT						FB_NO		/* default FB_NO		//use float values or avoid them (e.g. by alternative algorithms) */
#endif

#ifndef FB_USE_MOD
#define FB_USE_MOD							FB_NO		/* default FB_NO		//use native modulo operator? */
#endif


/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 * Font selection
 * The framebuffer driver is able to either use precompiled bitmap fonts with fixed character set and size
 * or to load a TrueType font file and render it. this setting decides if bitmap fonts are used or TrueType
 * rendering instead.
 * REMARK: Truetype fonts are not yet implemented so setting this define to TRUE will yield compile errors!
 * <description> 
 */
#ifndef FB_FONT_TRUETYPE
#define FB_FONT_TRUETYPE					FB_NO		/* default FB_NO; must be FB_NO because TrueType fonts are not implemented yet */
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 * Unittesting of Video drivers.
 * When the following setting is activated, then the currently active video driver will be tested automatically 
 * when a frame buffer device context is created. The default value is FB_NO.
 * REMARK: This setting should only be activated for explicit testing during development because these tests take quite a while!
 * <description> 
 */
#ifndef FB_TEST_VIDEODRIVER
#define FB_TEST_VIDEODRIVER					FB_NO		/* default FB_NO */
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 *	Possibility to override some of the generic function implementations for specific algorithms. 
 *	It is possible to activate the following defines and then the standard implementation of the according function will be omitted.
 *	Of course in such a situation, there must be a function with the same signature linked into the component.
 *	Set this define to FB_YES when you want to provide a customized implementation of the function _FBBlitUnclipped
 * <description>
 */

#ifndef FB_OVERRIDES_BITBLT
#define FB_OVERRIDES_BITBLT					FB_NO		/* default FB_NO*/
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 * Set this define to FB_YES when you want to provide a customized implementation of the function _FBStretchBlitUnclipped
 * <description>
 */
#ifndef FB_OVERRIDES_STRETCHBLT
#define FB_OVERRIDES_STRETCHBLT		        FB_NO		/* default FB_NO */
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 * Memory optimization
 * Set this define to FB_YES when you have to support large unicode fonts. The result of this setting will be that
 * the storage format of fonts is increased to a possible font bitmap size of 2^32 instead of 2^16. If this define is not set, then
 * two bytes less will be stored for each character in a font.
 * The define is only necessary when you have fonts with more than 65535 bytes of bitmap data.
 * <description>
 */
#ifndef FB_SUPPORTS_LARGE_UNICODEFONTS
#define FB_SUPPORTS_LARGE_UNICODEFONTS		FB_YES		/* default FB_NO*/
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 * Clipping
 * This define sets the clipping mode of the visualization. This mode affects the performance of drawing!
 * One of the following values can be assigned:
 *	FB_CLIP_PIXELBASED:			The clipping is done when accessing a single pixel (thus within the video driver). This is the most exact way of clipping but pretty slow for drawing pixel based elements (images, polygons, text).
 *	FB_CLIP_ALGORITHMIC			Cliping is realized in the platform independent drawing algorithms. This mode is not yet implemented.
 *	FB_CLIP_WHOLEPRIMITIVES		Clipping is done by checking whether a whole primitive (image, polygon...) can be drawn. If it leaves the current clipping region, then the whole primitive is clipped away.
 *								This is a fast clipping implementation but not very exact, ie. elements can disappear even if only some pixels should be clipped away.
 * This define is required. Otherwise compile errors will occur.
 * <description>
 */
#ifndef FB_CLIP_MODE
#define FB_CLIP_MODE			      		FB_CLIP_PIXELBASED
#endif

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 * This define can be set to FB_YES when you want to combine a non pixelbased clipping mode with the pixelbased clipping.
 * Setting this value to FB_YES will reduce the performance.
 * This setting is optional. The default value is FB_NO
 * <description>
 */
#ifndef FB_CLIP_FORCE_PIXELBASED
#define FB_CLIP_FORCE_PIXELBASED			FB_NO	
#endif

/* Pixel format;
 * 
 * the selection of the pixel format is done by simply defining FB_PF in the system specific header file 
 * SysGraphicFramebufferCfg.h according to the available framebuffer device. The according VideoDriver must
 * be linked into this component of course.
 */

#define FB_PF_INDEXED_COLOR_1		1	/* packed pixels:	[11111111]	         					- 2 indexed FBPaletteEntries */
#define FB_PF_INDEXED_COLOR_2		2	/* packed pixels:	[2 2 2 2 ]	         					- 4 indexed FBPaletteEntries */
#define FB_PF_INDEXED_COLOR_4		3	/* packed pixels:	[4   4   ]	         					- 16 indexed FBPaletteEntries */
#define FB_PF_INDEXED_COLOR_8		4	/* packed pixels:	[8       ]	         					- 256 indexed FBPaletteEntries */
#define FB_PF_DIRECT_COLOR_8		5	/* Direct Color:		[RRRGGGBB]	         					- 8 reds, 8 greens, 4 blues */
#define FB_PF_DIRECT_COLOR_15		6	/* High Color 15bpp:	[ RRRRRGG|GGGBBBBB]  					- 32 reds, 32 greens, 32 blues */
#define FB_PF_DIRECT_COLOR_16		7	/* High Color 16bpp:	[RRRRRGGG|GGGBBBBB]  					- 32 reds, 64 greens, 32 blues */
#define FB_PF_DIRECT_COLOR_24		8	/* True Color 24bpp:	[RRRRRRRR|GGGGGGGG|BBBBBBBB]			- 256 reds, 256 greens, 256 blues */
#define FB_PF_DIRECT_COLOR_32		9	/* True Color 32bpp;	[AAAAAAAA|RRRRRRRR|GGGGGGGG|BBBBBBBB]	- 256 alpha channels, 256 reds, 256 greens, 256 blues */
#define FB_PF_DIRECT_COLOR_32_RGB	10	/* True Color 32bpp:	[        |RRRRRRRR|GGGGGGGG|BBBBBBBB]	- 256 reds, 256 greens, 256 blues, 1 byte ignored */

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>
 * Definition of the pixel format. It is required to set this define to one of the following predefined values according
 * to the pixel format of the concrete framebuffer.
 *
 *	- FB_PF_INDEXED_COLOR_1		(Not yet implemented)	packed pixels:		[11111111]	      2 indexed FBPaletteEntries
 *	- FB_PF_INDEXED_COLOR_2		(Not yet implemented)	packed pixels:		[2 2 2 2 ]	      4 indexed FBPaletteEntries
 *	- FB_PF_INDEXED_COLOR_4		(Not yet implemented)	packed pixels:		[4   4   ]	      16 indexed FBPaletteEntries
 *	- FB_PF_INDEXED_COLOR_8			packed pixels:		[8       ]	         			256 indexed FBPaletteEntries
 *	- FB_PF_DIRECT_COLOR_8			Direct Color:		[RRRGGGBB						8 reds, 8 greens, 4 blues
 *	- FB_PF_DIRECT_COLOR_15			High Color 15bpp:	[ RRRRRGG|GGGBBBBB]  			32 reds, 32 greens, 32 blues
 *	- FB_PF_DIRECT_COLOR_16			High Color 16bpp:	[RRRRRGGG|GGGBBBBB]  			32 reds, 64 greens, 32 blues
 *	- FB_PF_DIRECT_COLOR_24			True Color 24bpp:	[RRRRRRRR|GGGGGGGG|BBBBBBBB]	256 reds, 256 greens, 256 blues
 *	- FB_PF_DIRECT_COLOR_32			True Color 32bpp;	[AAAAAAAA|RRRRRRRR|GGGGGGGG|BBBBBBBB]	256 alpha channels, 256 reds, 256 greens, 256 blues
 *	- FB_PF_DIRECT_COLOR_32_RGB		True Color 32bpp:	[        |RRRRRRRR|GGGGGGGG|BBBBBBBB]	256 reds, 256 greens, 256 blues, 1 byte ignored
 * <description>
 */
#ifndef FB_PF
#define FB_PF								FB_PF_DIRECT_COLOR_24
#endif 

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>
 * Framebuffer definitions
 * FB_NUM_FONTS: number of font types in the static font list, default: 2
 * FB_SIZE_X / FB_SIZE_Y: framebuffer size
 * FB_BITS_PER_PIXEL: bits per pixel
 * FB_BYTES_PER_PIXEL: bytes per pixel
 * <description>
 */
#ifndef FB_NUM_FONTS
#define FB_NUM_FONTS						12
#endif

#ifndef FB_SIZE_X
#define FB_SIZE_X							640
#endif

#ifndef FB_SIZE_Y
#define FB_SIZE_Y							480
#endif

#ifndef FB_BYTES_PER_PIXEL
#define FB_BYTES_PER_PIXEL				   ((FB_BITS_PER_PIXEL+7)/8)
#endif

/**
 * Font styles
 * The are taken from the SysGrpahicFramebuffer.h file as part of CoDeSys;
 */
#if (FB_SUPPORTS_LARGE_UNICODEFONTS == FB_YES)
	#define FB_CHAR_BMPOFFSET RTS_UI32
#else
	#define FB_CHAR_BMPOFFSET RTS_UI16
#endif

/**
 * Define the Pixel-Type, based on the choosen pixel format
 */
 
typedef struct
{
	RTS_UI8	btBlue;
	RTS_UI8	btGreen;
	RTS_UI8	btRed;
} FBPixel_24;

#if (FB_PF == FB_PF_INDEXED_COLOR_1) || \
	(FB_PF == FB_PF_INDEXED_COLOR_2) || \
	(FB_PF == FB_PF_INDEXED_COLOR_4)
	/* TODO Packed Pixels implementation */
	/* to support these formats, the according video drivers have to be realized and the algorithms 
		for loading images and blitting them have to be adapted at least */
	#error Pixel formats < 8 bit are not yet implemented!
#elif (FB_PF == FB_PF_INDEXED_COLOR_8) || \
	(FB_PF == FB_PF_DIRECT_COLOR_8)
	typedef RTS_UI8 FBPixel;					/* 1bpp, 2bpp, 4bpp, 8bpp have size of 1 byte */
#elif (FB_PF == FB_PF_DIRECT_COLOR_15) || \
	(FB_PF == FB_PF_DIRECT_COLOR_16)
	typedef RTS_UI16 FBPixel;					/* 15bpp, 16bpp have size of 2 bytes */
#elif (FB_PF == FB_PF_DIRECT_COLOR_24)
	typedef FBPixel_24 FBPixel;					/* 24bpp, have size of 3 bytes */
#elif (FB_PF == FB_PF_DIRECT_COLOR_32) || \
	(FB_PF == FB_PF_DIRECT_COLOR_32_RGB)
	typedef RTS_UI32 FBPixel;					/* 32bpp have size of 4 bytes */
#else
	#error No Pixel format defined
#endif

#if (FB_PF == FB_PF_INDEXED_COLOR_1) || \
	(FB_PF == FB_PF_INDEXED_COLOR_2) || \
	(FB_PF == FB_PF_INDEXED_COLOR_4)
	/* TODO Packed Pixels implementation */
	/* to support these formats, the according video drivers have to be realized and the algorithms 
		for loading images and blitting them have to be adapted at least */
	#error Pixel formats < 8 bit are not yet implemented!
#elif (FB_PF == FB_PF_INDEXED_COLOR_8) || \
	(FB_PF == FB_PF_DIRECT_COLOR_8)
	#define	FB_BITS_PER_PIXEL 				8			
#elif (FB_PF == FB_PF_DIRECT_COLOR_15) 
	#define FB_BITS_PER_PIXEL				15
#elif (FB_PF == FB_PF_DIRECT_COLOR_16)
	#define FB_BITS_PER_PIXEL				16
#elif (FB_PF == FB_PF_DIRECT_COLOR_24)
	#define FB_BITS_PER_PIXEL				24
#elif (FB_PF == FB_PF_DIRECT_COLOR_32) || \
	(FB_PF == FB_PF_DIRECT_COLOR_32_RGB)
	#define FB_BITS_PER_PIXEL				36
#else
	#error No Pixel format defined
#endif

/* some values, needed to read the fontdownloadfile */
#define MAGICNUMBER_FONTFILE				64266447  /* Ascii: FbFt (FramebufferFont)*/
#define FILEFORMAT_FONTFILE					0	/* for a possible change of the fileformat */
/* ids of the differnt sections in the file */
#define CHARACTERDATA_ID					1
#define CHARACTERDESC_ID					3
#define FONTAREA_ID							8
#define FONTINFO_ID							10

/**
 * <description>
 * Font Character Descriptor;
 * describes where a specific character can be found in the Font bitmap;
 * characters are stored byte-aligned within the bitmap. See this encoded "2":
 * 
 *     byte42     byte43	---> usOffset		= 42, as byte 42 is the first used byte
 * 	[ 00000000 | 00000000 ]			
 * -
 * 0  00011110   00000000	---> ucWidth		= 10 Pixels (= 10Bit)
 * 0  01100001   10000000  
 * 0  11000000   11000000
 * 0  00000001   10000000  
 * -
 * 0  00000110   00000000  
 * 0  00011100   00000000  
 * 0  11111111   11000000  	---> ucHeight		= 7 Pixels (= 7 Bit)
 * 0  00000000   00000000	---> ucBaseline		= 1 Pixel (= 1 Bit)
 * -
 * </description>
 */
typedef struct FBFontCharStruct
{
	RTS_UI8				ucHeight;			/* height of the character in pixels (=bit in the font bitmap) */
	RTS_UI8				ucWidth;			/* width of the character in pixels (=bit in the font bitmap) */
	RTS_UI8				ucLength;			/* width of the character in bytes ( 1 + (cWidth / 8) ) */
	RTS_UI8				ucBaseline;			/* number of pixels to add from baseline up to the actual character */
	FB_CHAR_BMPOFFSET	usOffset;			/* adress-offset of the first byte that belongs to the character within the FBFont::pBitmap */
} FBFontChar;

/**
 * <description>
 * Font Character Area;
 * A font may be splitted into continouos areas; each area is a run of character-codes.
 * 
 * Example: An area for ASCII will reach from 
 * FirstChar	= 0x0000		to
 * LastChar		= 0x007F.
 * 
 * If it is the first area in aChars and pBitmap,
 * usOffset		= 0x0000;
 * 
 * Another example: Assuming that a second area contains Unicode braille-characters:
 * FirstChar	= 0x2800
 * LastChar		= 0x28FF
 * usOffset		= 0x0080		<---- 	this is the the number of characters encoded before the first braille-character;
 * 										in this case it is 0x0080 which is the number of ASCII characters
 * 
 * </description>
 */
typedef struct
{
	RTS_WCHAR		FirstChar;		/* character-code of the first character in this area */
	RTS_WCHAR		LastChar;		/* character-code of the last character in this area */
	RTS_UI16		usOffset;		/* index-offset of the FirstChar within FBFont::aChars; to be substracted from a character-code */
} FBFontArea;

/**
 * <description>
 * Font;
 * A font is basically a bit-pattern-bitmap containing all characters the font can display.
 * Every character is described by a FBFontChar structure. A single FBFontChar index is being
 * accessed by simply passing the caracter-code of a character (e.g. ASCII, ANSI, Unicode) to
 * _FBDrawFontChar(). The code will be passed right through to aChars as index. Previously it
 * will be checked against area boundaries within aCharAreas and decremented by an appropiate
 * index offset if necessary. In this way one bitmap is allowed to contain multiple runs of
 * character-codes. One might use this to load different subsets of the Unicode planes into one
 * bitmap. Note that within such bitmap the characters alsways have to be ordered by their
 * ascending character-codes.
 * 
 * </description>
 */
typedef struct
{
	/* descriptive variables */
	char*			stName;					/* name of the font */
	RTS_UI8			ucSize;					/* size of the font */
	RTS_UI8			ucStyleFlags;			/* font styles, eg. bold, italic, underlined, striked out; defined above */

	/* data variables	 */
	RTS_UI8*		pBitmap;				/* bit-pattern containing all the font's characters; this is *not* a windows bitmap */
	FBFontChar*		aChars;					/* array with all character descriptors */
	RTS_UI16		usNumberOfChars;		/* number of characters contained in the font */
	FBFontArea*		aCharAreas;				/* divides aChars and consequently pBitmap in continuous areas; example see above */
	RTS_UI16		ucNumberOfCharAreas;	/* number of FBFontAreas contained in aCharAreas */
	RTS_UI8			ucRealHeight;			/* maximum vertical space ever used by a character from baseline to the topmost */
	RTS_BOOL		dynamicallyLoaded;		/* true for fonts, that are downloaded by the application */
	char*			stFontToReplace;		/* name of the font, which has to be replaced by this font. This value is added manually to the fontfile and is not generated by the FramebufferFontGen */
} FBFont;

/* structure to read the downloaded font file: defines the content of the sections */
typedef struct
{
       RTS_UI32 startOffset;
       RTS_UI32 sectionSize;
       RTS_UI32 sectionId;
} FontFile_TOCEntry;

/* structure to read the downloaded font file: first information, that will be expected in the file */
typedef struct
{
       RTS_UI32 magicNumber;             /* to quickly check we have a font file or something completely different */
       RTS_UI16 fileFormat;              /* number identifiing the content of the file */
       RTS_UI16 numSections;
       FontFile_TOCEntry sections[1];     /* an array of section information, see above, for the number have a look at numSections */
} FontFile_Header;

/* section with fontinfo */
typedef struct
{
       char fontName[80];                /* at the moment the visu supports only ANSI font names, 79 chars should be enough */
       RTS_UI8 ucSize;
       RTS_UI8 ucStyleFlags;
       RTS_UI8 ucRealHeight;
       RTS_UI8 dummy;
} FontFile_Sect_FontInfo;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Init routines for OS specific modules</description>
 * <param name="pInit" type="IN">Init Struct for OS specific modules</param>
 * <result>Result of Initialisation.</result>
 */
RTS_RESULT CDECL SysFramebufferOSInit(INIT_STRUCT *pInit);
/**
 * <description>Hook Function for OS specific modules</description>
 * <param name="ulHook" type="IN">Hook Type for OS specific modules</param>
 * <param name="ulParam1" type="IN">First Hook Parameter for OS specific modules</param>
 * <param name="ulParam2" type="IN">Second Hook Parameter for OS specific modules</param>
 * <result>Result of OS Hook.</result>
 */
RTS_RESULT CDECL SysFramebufferOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);
/**
 * <description>Device initiate function for frame buffer</description>
 * <result>Result of device initialization</result>
 */
RTS_RESULT CDECL SysFramebufferDeviceInit(void);
typedef RTS_RESULT (CDECL * PFSYSFRAMEBUFFERDEVICEINIT) (void);
#if defined(SYSFRAMEBUFFER_NOTIMPLEMENTED) || defined(SYSFRAMEBUFFERDEVICEINIT_NOTIMPLEMENTED)
	#define USE_SysFramebufferDeviceInit
	#define EXT_SysFramebufferDeviceInit
	#define GET_SysFramebufferDeviceInit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFramebufferDeviceInit()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysFramebufferDeviceInit  FALSE
	#define EXP_SysFramebufferDeviceInit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFramebufferDeviceInit
	#define EXT_SysFramebufferDeviceInit
	#define GET_SysFramebufferDeviceInit(fl)  CAL_CMGETAPI( "SysFramebufferDeviceInit" ) 
	#define CAL_SysFramebufferDeviceInit  SysFramebufferDeviceInit
	#define CHK_SysFramebufferDeviceInit  TRUE
	#define EXP_SysFramebufferDeviceInit  CAL_CMEXPAPI( "SysFramebufferDeviceInit" ) 
#elif defined(MIXED_LINK) && !defined(SYSFRAMEBUFFER_EXTERNAL)
	#define USE_SysFramebufferDeviceInit
	#define EXT_SysFramebufferDeviceInit
	#define GET_SysFramebufferDeviceInit(fl)  CAL_CMGETAPI( "SysFramebufferDeviceInit" ) 
	#define CAL_SysFramebufferDeviceInit  SysFramebufferDeviceInit
	#define CHK_SysFramebufferDeviceInit  TRUE
	#define EXP_SysFramebufferDeviceInit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFramebufferDeviceInit", (RTS_UINTPTR)SysFramebufferDeviceInit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFramebufferSysFramebufferDeviceInit
	#define EXT_SysFramebufferSysFramebufferDeviceInit
	#define GET_SysFramebufferSysFramebufferDeviceInit  ERR_OK
	#define CAL_SysFramebufferSysFramebufferDeviceInit pISysFramebuffer->ISysFramebufferDeviceInit
	#define CHK_SysFramebufferSysFramebufferDeviceInit (pISysFramebuffer != NULL)
	#define EXP_SysFramebufferSysFramebufferDeviceInit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFramebufferDeviceInit
	#define EXT_SysFramebufferDeviceInit
	#define GET_SysFramebufferDeviceInit(fl)  CAL_CMGETAPI( "SysFramebufferDeviceInit" ) 
	#define CAL_SysFramebufferDeviceInit pISysFramebuffer->ISysFramebufferDeviceInit
	#define CHK_SysFramebufferDeviceInit (pISysFramebuffer != NULL)
	#define EXP_SysFramebufferDeviceInit  CAL_CMEXPAPI( "SysFramebufferDeviceInit" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFramebufferDeviceInit  PFSYSFRAMEBUFFERDEVICEINIT pfSysFramebufferDeviceInit;
	#define EXT_SysFramebufferDeviceInit  extern PFSYSFRAMEBUFFERDEVICEINIT pfSysFramebufferDeviceInit;
	#define GET_SysFramebufferDeviceInit(fl)  s_pfCMGetAPI2( "SysFramebufferDeviceInit", (RTS_VOID_FCTPTR *)&pfSysFramebufferDeviceInit, (fl), 0, 0)
	#define CAL_SysFramebufferDeviceInit  pfSysFramebufferDeviceInit
	#define CHK_SysFramebufferDeviceInit  (pfSysFramebufferDeviceInit != NULL)
	#define EXP_SysFramebufferDeviceInit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFramebufferDeviceInit", (RTS_UINTPTR)SysFramebufferDeviceInit, 0, 0) 
#endif



/**
 * <description>Routine before writing to frame buffer</description>
 * <result>error code</result>
 * <error code name="RTS_RESULT" type="ERR_OK">frame buffer can be written</error code>
 * <error code name="RTS_RESULT" type="ERR_PENDING">buffer busy</error code>
 */
RTS_RESULT CDECL SysFramebufferBeginPaint(void);
typedef RTS_RESULT (CDECL * PFSYSFRAMEBUFFERBEGINPAINT) (void);
#if defined(SYSFRAMEBUFFER_NOTIMPLEMENTED) || defined(SYSFRAMEBUFFERBEGINPAINT_NOTIMPLEMENTED)
	#define USE_SysFramebufferBeginPaint
	#define EXT_SysFramebufferBeginPaint
	#define GET_SysFramebufferBeginPaint(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFramebufferBeginPaint()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysFramebufferBeginPaint  FALSE
	#define EXP_SysFramebufferBeginPaint  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFramebufferBeginPaint
	#define EXT_SysFramebufferBeginPaint
	#define GET_SysFramebufferBeginPaint(fl)  CAL_CMGETAPI( "SysFramebufferBeginPaint" ) 
	#define CAL_SysFramebufferBeginPaint  SysFramebufferBeginPaint
	#define CHK_SysFramebufferBeginPaint  TRUE
	#define EXP_SysFramebufferBeginPaint  CAL_CMEXPAPI( "SysFramebufferBeginPaint" ) 
#elif defined(MIXED_LINK) && !defined(SYSFRAMEBUFFER_EXTERNAL)
	#define USE_SysFramebufferBeginPaint
	#define EXT_SysFramebufferBeginPaint
	#define GET_SysFramebufferBeginPaint(fl)  CAL_CMGETAPI( "SysFramebufferBeginPaint" ) 
	#define CAL_SysFramebufferBeginPaint  SysFramebufferBeginPaint
	#define CHK_SysFramebufferBeginPaint  TRUE
	#define EXP_SysFramebufferBeginPaint  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFramebufferBeginPaint", (RTS_UINTPTR)SysFramebufferBeginPaint, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFramebufferSysFramebufferBeginPaint
	#define EXT_SysFramebufferSysFramebufferBeginPaint
	#define GET_SysFramebufferSysFramebufferBeginPaint  ERR_OK
	#define CAL_SysFramebufferSysFramebufferBeginPaint pISysFramebuffer->ISysFramebufferBeginPaint
	#define CHK_SysFramebufferSysFramebufferBeginPaint (pISysFramebuffer != NULL)
	#define EXP_SysFramebufferSysFramebufferBeginPaint  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFramebufferBeginPaint
	#define EXT_SysFramebufferBeginPaint
	#define GET_SysFramebufferBeginPaint(fl)  CAL_CMGETAPI( "SysFramebufferBeginPaint" ) 
	#define CAL_SysFramebufferBeginPaint pISysFramebuffer->ISysFramebufferBeginPaint
	#define CHK_SysFramebufferBeginPaint (pISysFramebuffer != NULL)
	#define EXP_SysFramebufferBeginPaint  CAL_CMEXPAPI( "SysFramebufferBeginPaint" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFramebufferBeginPaint  PFSYSFRAMEBUFFERBEGINPAINT pfSysFramebufferBeginPaint;
	#define EXT_SysFramebufferBeginPaint  extern PFSYSFRAMEBUFFERBEGINPAINT pfSysFramebufferBeginPaint;
	#define GET_SysFramebufferBeginPaint(fl)  s_pfCMGetAPI2( "SysFramebufferBeginPaint", (RTS_VOID_FCTPTR *)&pfSysFramebufferBeginPaint, (fl), 0, 0)
	#define CAL_SysFramebufferBeginPaint  pfSysFramebufferBeginPaint
	#define CHK_SysFramebufferBeginPaint  (pfSysFramebufferBeginPaint != NULL)
	#define EXP_SysFramebufferBeginPaint  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFramebufferBeginPaint", (RTS_UINTPTR)SysFramebufferBeginPaint, 0, 0) 
#endif



/**
 * <description>Routine after writing to frame buffer</description>
 * <result>error code</result>
 * <error code name="RTS_RESULT" type="ERR_OK">frame buffer can be written</error code>
 * <error code name="RTS_RESULT" type="ERR_PENDING">buffer busy</error code>
 */
RTS_RESULT CDECL SysFramebufferEndPaint(void);
typedef RTS_RESULT (CDECL * PFSYSFRAMEBUFFERENDPAINT) (void);
#if defined(SYSFRAMEBUFFER_NOTIMPLEMENTED) || defined(SYSFRAMEBUFFERENDPAINT_NOTIMPLEMENTED)
	#define USE_SysFramebufferEndPaint
	#define EXT_SysFramebufferEndPaint
	#define GET_SysFramebufferEndPaint(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFramebufferEndPaint()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysFramebufferEndPaint  FALSE
	#define EXP_SysFramebufferEndPaint  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFramebufferEndPaint
	#define EXT_SysFramebufferEndPaint
	#define GET_SysFramebufferEndPaint(fl)  CAL_CMGETAPI( "SysFramebufferEndPaint" ) 
	#define CAL_SysFramebufferEndPaint  SysFramebufferEndPaint
	#define CHK_SysFramebufferEndPaint  TRUE
	#define EXP_SysFramebufferEndPaint  CAL_CMEXPAPI( "SysFramebufferEndPaint" ) 
#elif defined(MIXED_LINK) && !defined(SYSFRAMEBUFFER_EXTERNAL)
	#define USE_SysFramebufferEndPaint
	#define EXT_SysFramebufferEndPaint
	#define GET_SysFramebufferEndPaint(fl)  CAL_CMGETAPI( "SysFramebufferEndPaint" ) 
	#define CAL_SysFramebufferEndPaint  SysFramebufferEndPaint
	#define CHK_SysFramebufferEndPaint  TRUE
	#define EXP_SysFramebufferEndPaint  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFramebufferEndPaint", (RTS_UINTPTR)SysFramebufferEndPaint, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFramebufferSysFramebufferEndPaint
	#define EXT_SysFramebufferSysFramebufferEndPaint
	#define GET_SysFramebufferSysFramebufferEndPaint  ERR_OK
	#define CAL_SysFramebufferSysFramebufferEndPaint pISysFramebuffer->ISysFramebufferEndPaint
	#define CHK_SysFramebufferSysFramebufferEndPaint (pISysFramebuffer != NULL)
	#define EXP_SysFramebufferSysFramebufferEndPaint  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFramebufferEndPaint
	#define EXT_SysFramebufferEndPaint
	#define GET_SysFramebufferEndPaint(fl)  CAL_CMGETAPI( "SysFramebufferEndPaint" ) 
	#define CAL_SysFramebufferEndPaint pISysFramebuffer->ISysFramebufferEndPaint
	#define CHK_SysFramebufferEndPaint (pISysFramebuffer != NULL)
	#define EXP_SysFramebufferEndPaint  CAL_CMEXPAPI( "SysFramebufferEndPaint" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFramebufferEndPaint  PFSYSFRAMEBUFFERENDPAINT pfSysFramebufferEndPaint;
	#define EXT_SysFramebufferEndPaint  extern PFSYSFRAMEBUFFERENDPAINT pfSysFramebufferEndPaint;
	#define GET_SysFramebufferEndPaint(fl)  s_pfCMGetAPI2( "SysFramebufferEndPaint", (RTS_VOID_FCTPTR *)&pfSysFramebufferEndPaint, (fl), 0, 0)
	#define CAL_SysFramebufferEndPaint  pfSysFramebufferEndPaint
	#define CHK_SysFramebufferEndPaint  (pfSysFramebufferEndPaint != NULL)
	#define EXP_SysFramebufferEndPaint  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFramebufferEndPaint", (RTS_UINTPTR)SysFramebufferEndPaint, 0, 0) 
#endif



/**
 * <description>Routine to flush frame buffer</description>
 * <result>error code</result>
 * <error code name="RTS_RESULT" type="ERR_OK">frame buffer can be written</error code>
 * <error code name="RTS_RESULT" type="ERR_FAILED">buffer flush failed</error code>
 */
RTS_RESULT CDECL SysFramebufferFlush(RTS_Rectangle* aInvalidate, RTS_UI32 uiNumRects);
typedef RTS_RESULT (CDECL * PFSYSFRAMEBUFFERFLUSH) (RTS_Rectangle* aInvalidate, RTS_UI32 uiNumRects);
#if defined(SYSFRAMEBUFFER_NOTIMPLEMENTED) || defined(SYSFRAMEBUFFERFLUSH_NOTIMPLEMENTED)
	#define USE_SysFramebufferFlush
	#define EXT_SysFramebufferFlush
	#define GET_SysFramebufferFlush(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFramebufferFlush(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysFramebufferFlush  FALSE
	#define EXP_SysFramebufferFlush  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFramebufferFlush
	#define EXT_SysFramebufferFlush
	#define GET_SysFramebufferFlush(fl)  CAL_CMGETAPI( "SysFramebufferFlush" ) 
	#define CAL_SysFramebufferFlush  SysFramebufferFlush
	#define CHK_SysFramebufferFlush  TRUE
	#define EXP_SysFramebufferFlush  CAL_CMEXPAPI( "SysFramebufferFlush" ) 
#elif defined(MIXED_LINK) && !defined(SYSFRAMEBUFFER_EXTERNAL)
	#define USE_SysFramebufferFlush
	#define EXT_SysFramebufferFlush
	#define GET_SysFramebufferFlush(fl)  CAL_CMGETAPI( "SysFramebufferFlush" ) 
	#define CAL_SysFramebufferFlush  SysFramebufferFlush
	#define CHK_SysFramebufferFlush  TRUE
	#define EXP_SysFramebufferFlush  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFramebufferFlush", (RTS_UINTPTR)SysFramebufferFlush, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFramebufferSysFramebufferFlush
	#define EXT_SysFramebufferSysFramebufferFlush
	#define GET_SysFramebufferSysFramebufferFlush  ERR_OK
	#define CAL_SysFramebufferSysFramebufferFlush pISysFramebuffer->ISysFramebufferFlush
	#define CHK_SysFramebufferSysFramebufferFlush (pISysFramebuffer != NULL)
	#define EXP_SysFramebufferSysFramebufferFlush  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFramebufferFlush
	#define EXT_SysFramebufferFlush
	#define GET_SysFramebufferFlush(fl)  CAL_CMGETAPI( "SysFramebufferFlush" ) 
	#define CAL_SysFramebufferFlush pISysFramebuffer->ISysFramebufferFlush
	#define CHK_SysFramebufferFlush (pISysFramebuffer != NULL)
	#define EXP_SysFramebufferFlush  CAL_CMEXPAPI( "SysFramebufferFlush" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFramebufferFlush  PFSYSFRAMEBUFFERFLUSH pfSysFramebufferFlush;
	#define EXT_SysFramebufferFlush  extern PFSYSFRAMEBUFFERFLUSH pfSysFramebufferFlush;
	#define GET_SysFramebufferFlush(fl)  s_pfCMGetAPI2( "SysFramebufferFlush", (RTS_VOID_FCTPTR *)&pfSysFramebufferFlush, (fl), 0, 0)
	#define CAL_SysFramebufferFlush  pfSysFramebufferFlush
	#define CHK_SysFramebufferFlush  (pfSysFramebufferFlush != NULL)
	#define EXP_SysFramebufferFlush  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFramebufferFlush", (RTS_UINTPTR)SysFramebufferFlush, 0, 0) 
#endif



/**
 * <description>Routine to get the address of the current active frame buffer before writing</description>
 * <result>error code</result>
 * <error code name="RTS_RESULT" type="ERR_PARAMETER"> address pointer is null</error code>
 * <error code name="RTS_RESULT" type="ERR_OK">address aquried successfully</error code>
 * <error code name="RTS_RESULT" type="ERR_FAILED">active frame buffer not found</error code>
 */
RTS_RESULT CDECL SysFramebufferGetCurrentAddress(FBPixel **pAddress);
typedef RTS_RESULT (CDECL * PFSYSFRAMEBUFFERGETCURRENTADDRESS) (FBPixel **pAddress);
#if defined(SYSFRAMEBUFFER_NOTIMPLEMENTED) || defined(SYSFRAMEBUFFERGETCURRENTADDRESS_NOTIMPLEMENTED)
	#define USE_SysFramebufferGetCurrentAddress
	#define EXT_SysFramebufferGetCurrentAddress
	#define GET_SysFramebufferGetCurrentAddress(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFramebufferGetCurrentAddress(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysFramebufferGetCurrentAddress  FALSE
	#define EXP_SysFramebufferGetCurrentAddress  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFramebufferGetCurrentAddress
	#define EXT_SysFramebufferGetCurrentAddress
	#define GET_SysFramebufferGetCurrentAddress(fl)  CAL_CMGETAPI( "SysFramebufferGetCurrentAddress" ) 
	#define CAL_SysFramebufferGetCurrentAddress  SysFramebufferGetCurrentAddress
	#define CHK_SysFramebufferGetCurrentAddress  TRUE
	#define EXP_SysFramebufferGetCurrentAddress  CAL_CMEXPAPI( "SysFramebufferGetCurrentAddress" ) 
#elif defined(MIXED_LINK) && !defined(SYSFRAMEBUFFER_EXTERNAL)
	#define USE_SysFramebufferGetCurrentAddress
	#define EXT_SysFramebufferGetCurrentAddress
	#define GET_SysFramebufferGetCurrentAddress(fl)  CAL_CMGETAPI( "SysFramebufferGetCurrentAddress" ) 
	#define CAL_SysFramebufferGetCurrentAddress  SysFramebufferGetCurrentAddress
	#define CHK_SysFramebufferGetCurrentAddress  TRUE
	#define EXP_SysFramebufferGetCurrentAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFramebufferGetCurrentAddress", (RTS_UINTPTR)SysFramebufferGetCurrentAddress, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFramebufferSysFramebufferGetCurrentAddress
	#define EXT_SysFramebufferSysFramebufferGetCurrentAddress
	#define GET_SysFramebufferSysFramebufferGetCurrentAddress  ERR_OK
	#define CAL_SysFramebufferSysFramebufferGetCurrentAddress pISysFramebuffer->ISysFramebufferGetCurrentAddress
	#define CHK_SysFramebufferSysFramebufferGetCurrentAddress (pISysFramebuffer != NULL)
	#define EXP_SysFramebufferSysFramebufferGetCurrentAddress  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFramebufferGetCurrentAddress
	#define EXT_SysFramebufferGetCurrentAddress
	#define GET_SysFramebufferGetCurrentAddress(fl)  CAL_CMGETAPI( "SysFramebufferGetCurrentAddress" ) 
	#define CAL_SysFramebufferGetCurrentAddress pISysFramebuffer->ISysFramebufferGetCurrentAddress
	#define CHK_SysFramebufferGetCurrentAddress (pISysFramebuffer != NULL)
	#define EXP_SysFramebufferGetCurrentAddress  CAL_CMEXPAPI( "SysFramebufferGetCurrentAddress" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFramebufferGetCurrentAddress  PFSYSFRAMEBUFFERGETCURRENTADDRESS pfSysFramebufferGetCurrentAddress;
	#define EXT_SysFramebufferGetCurrentAddress  extern PFSYSFRAMEBUFFERGETCURRENTADDRESS pfSysFramebufferGetCurrentAddress;
	#define GET_SysFramebufferGetCurrentAddress(fl)  s_pfCMGetAPI2( "SysFramebufferGetCurrentAddress", (RTS_VOID_FCTPTR *)&pfSysFramebufferGetCurrentAddress, (fl), 0, 0)
	#define CAL_SysFramebufferGetCurrentAddress  pfSysFramebufferGetCurrentAddress
	#define CHK_SysFramebufferGetCurrentAddress  (pfSysFramebufferGetCurrentAddress != NULL)
	#define EXP_SysFramebufferGetCurrentAddress  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFramebufferGetCurrentAddress", (RTS_UINTPTR)SysFramebufferGetCurrentAddress, 0, 0) 
#endif



/**
 * <description>Get the proposal of a color palette, but return a completely new one, which matches the palette of the device. </description>
 * <result>error code</result>
 * <error code name="RTS_RESULT" type="ERR_OK">palette assigned successfully or no user defined palette</error code>
 * <error code name="RTS_RESULT" type="ERR_FAILED">palette assigned failed</error code>
 */
RTS_RESULT CDECL SysFramebufferEnableColorPalette8(RTS_UI8 *pPalette);
typedef RTS_RESULT (CDECL * PFSYSFRAMEBUFFERENABLECOLORPALETTE8) (RTS_UI8 *pPalette);
#if defined(SYSFRAMEBUFFER_NOTIMPLEMENTED) || defined(SYSFRAMEBUFFERENABLECOLORPALETTE8_NOTIMPLEMENTED)
	#define USE_SysFramebufferEnableColorPalette8
	#define EXT_SysFramebufferEnableColorPalette8
	#define GET_SysFramebufferEnableColorPalette8(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFramebufferEnableColorPalette8(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysFramebufferEnableColorPalette8  FALSE
	#define EXP_SysFramebufferEnableColorPalette8  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFramebufferEnableColorPalette8
	#define EXT_SysFramebufferEnableColorPalette8
	#define GET_SysFramebufferEnableColorPalette8(fl)  CAL_CMGETAPI( "SysFramebufferEnableColorPalette8" ) 
	#define CAL_SysFramebufferEnableColorPalette8  SysFramebufferEnableColorPalette8
	#define CHK_SysFramebufferEnableColorPalette8  TRUE
	#define EXP_SysFramebufferEnableColorPalette8  CAL_CMEXPAPI( "SysFramebufferEnableColorPalette8" ) 
#elif defined(MIXED_LINK) && !defined(SYSFRAMEBUFFER_EXTERNAL)
	#define USE_SysFramebufferEnableColorPalette8
	#define EXT_SysFramebufferEnableColorPalette8
	#define GET_SysFramebufferEnableColorPalette8(fl)  CAL_CMGETAPI( "SysFramebufferEnableColorPalette8" ) 
	#define CAL_SysFramebufferEnableColorPalette8  SysFramebufferEnableColorPalette8
	#define CHK_SysFramebufferEnableColorPalette8  TRUE
	#define EXP_SysFramebufferEnableColorPalette8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFramebufferEnableColorPalette8", (RTS_UINTPTR)SysFramebufferEnableColorPalette8, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFramebufferSysFramebufferEnableColorPalette8
	#define EXT_SysFramebufferSysFramebufferEnableColorPalette8
	#define GET_SysFramebufferSysFramebufferEnableColorPalette8  ERR_OK
	#define CAL_SysFramebufferSysFramebufferEnableColorPalette8 pISysFramebuffer->ISysFramebufferEnableColorPalette8
	#define CHK_SysFramebufferSysFramebufferEnableColorPalette8 (pISysFramebuffer != NULL)
	#define EXP_SysFramebufferSysFramebufferEnableColorPalette8  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFramebufferEnableColorPalette8
	#define EXT_SysFramebufferEnableColorPalette8
	#define GET_SysFramebufferEnableColorPalette8(fl)  CAL_CMGETAPI( "SysFramebufferEnableColorPalette8" ) 
	#define CAL_SysFramebufferEnableColorPalette8 pISysFramebuffer->ISysFramebufferEnableColorPalette8
	#define CHK_SysFramebufferEnableColorPalette8 (pISysFramebuffer != NULL)
	#define EXP_SysFramebufferEnableColorPalette8  CAL_CMEXPAPI( "SysFramebufferEnableColorPalette8" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFramebufferEnableColorPalette8  PFSYSFRAMEBUFFERENABLECOLORPALETTE8 pfSysFramebufferEnableColorPalette8;
	#define EXT_SysFramebufferEnableColorPalette8  extern PFSYSFRAMEBUFFERENABLECOLORPALETTE8 pfSysFramebufferEnableColorPalette8;
	#define GET_SysFramebufferEnableColorPalette8(fl)  s_pfCMGetAPI2( "SysFramebufferEnableColorPalette8", (RTS_VOID_FCTPTR *)&pfSysFramebufferEnableColorPalette8, (fl), 0, 0)
	#define CAL_SysFramebufferEnableColorPalette8  pfSysFramebufferEnableColorPalette8
	#define CHK_SysFramebufferEnableColorPalette8  (pfSysFramebufferEnableColorPalette8 != NULL)
	#define EXP_SysFramebufferEnableColorPalette8  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFramebufferEnableColorPalette8", (RTS_UINTPTR)SysFramebufferEnableColorPalette8, 0, 0) 
#endif



/**
 * <description>For all systems without a filesystem and without truetype fonts, this function is used to return the best matching font on the system</description>
 * <result>runtime handle</result>
 */
RTS_HANDLE CDECL SysFramebufferGetFontList(void);
typedef RTS_HANDLE (CDECL * PFSYSFRAMEBUFFERGETFONTLIST) (void);
#if defined(SYSFRAMEBUFFER_NOTIMPLEMENTED) || defined(SYSFRAMEBUFFERGETFONTLIST_NOTIMPLEMENTED)
	#define USE_SysFramebufferGetFontList
	#define EXT_SysFramebufferGetFontList
	#define GET_SysFramebufferGetFontList(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFramebufferGetFontList()  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_SysFramebufferGetFontList  FALSE
	#define EXP_SysFramebufferGetFontList  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFramebufferGetFontList
	#define EXT_SysFramebufferGetFontList
	#define GET_SysFramebufferGetFontList(fl)  CAL_CMGETAPI( "SysFramebufferGetFontList" ) 
	#define CAL_SysFramebufferGetFontList  SysFramebufferGetFontList
	#define CHK_SysFramebufferGetFontList  TRUE
	#define EXP_SysFramebufferGetFontList  CAL_CMEXPAPI( "SysFramebufferGetFontList" ) 
#elif defined(MIXED_LINK) && !defined(SYSFRAMEBUFFER_EXTERNAL)
	#define USE_SysFramebufferGetFontList
	#define EXT_SysFramebufferGetFontList
	#define GET_SysFramebufferGetFontList(fl)  CAL_CMGETAPI( "SysFramebufferGetFontList" ) 
	#define CAL_SysFramebufferGetFontList  SysFramebufferGetFontList
	#define CHK_SysFramebufferGetFontList  TRUE
	#define EXP_SysFramebufferGetFontList  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFramebufferGetFontList", (RTS_UINTPTR)SysFramebufferGetFontList, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFramebufferSysFramebufferGetFontList
	#define EXT_SysFramebufferSysFramebufferGetFontList
	#define GET_SysFramebufferSysFramebufferGetFontList  ERR_OK
	#define CAL_SysFramebufferSysFramebufferGetFontList pISysFramebuffer->ISysFramebufferGetFontList
	#define CHK_SysFramebufferSysFramebufferGetFontList (pISysFramebuffer != NULL)
	#define EXP_SysFramebufferSysFramebufferGetFontList  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFramebufferGetFontList
	#define EXT_SysFramebufferGetFontList
	#define GET_SysFramebufferGetFontList(fl)  CAL_CMGETAPI( "SysFramebufferGetFontList" ) 
	#define CAL_SysFramebufferGetFontList pISysFramebuffer->ISysFramebufferGetFontList
	#define CHK_SysFramebufferGetFontList (pISysFramebuffer != NULL)
	#define EXP_SysFramebufferGetFontList  CAL_CMEXPAPI( "SysFramebufferGetFontList" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFramebufferGetFontList  PFSYSFRAMEBUFFERGETFONTLIST pfSysFramebufferGetFontList;
	#define EXT_SysFramebufferGetFontList  extern PFSYSFRAMEBUFFERGETFONTLIST pfSysFramebufferGetFontList;
	#define GET_SysFramebufferGetFontList(fl)  s_pfCMGetAPI2( "SysFramebufferGetFontList", (RTS_VOID_FCTPTR *)&pfSysFramebufferGetFontList, (fl), 0, 0)
	#define CAL_SysFramebufferGetFontList  pfSysFramebufferGetFontList
	#define CHK_SysFramebufferGetFontList  (pfSysFramebufferGetFontList != NULL)
	#define EXP_SysFramebufferGetFontList  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFramebufferGetFontList", (RTS_UINTPTR)SysFramebufferGetFontList, 0, 0) 
#endif



/**
 * <description>In case that no static font list was return, use this function to get dynamic fonts</description>
 * <result>runtime handle</result>
 */
RTS_RESULT CDECL SysFramebufferGetFont(FBFont** ppFont, char* pszFontName, RTS_UI8 ucFontSize, RTS_UI32 uiFlags);
typedef RTS_RESULT (CDECL * PFSYSFRAMEBUFFERGETFONT) (FBFont** ppFont, char* pszFontName, RTS_UI8 ucFontSize, RTS_UI32 uiFlags);
#if defined(SYSFRAMEBUFFER_NOTIMPLEMENTED) || defined(SYSFRAMEBUFFERGETFONT_NOTIMPLEMENTED)
	#define USE_SysFramebufferGetFont
	#define EXT_SysFramebufferGetFont
	#define GET_SysFramebufferGetFont(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysFramebufferGetFont(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysFramebufferGetFont  FALSE
	#define EXP_SysFramebufferGetFont  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysFramebufferGetFont
	#define EXT_SysFramebufferGetFont
	#define GET_SysFramebufferGetFont(fl)  CAL_CMGETAPI( "SysFramebufferGetFont" ) 
	#define CAL_SysFramebufferGetFont  SysFramebufferGetFont
	#define CHK_SysFramebufferGetFont  TRUE
	#define EXP_SysFramebufferGetFont  CAL_CMEXPAPI( "SysFramebufferGetFont" ) 
#elif defined(MIXED_LINK) && !defined(SYSFRAMEBUFFER_EXTERNAL)
	#define USE_SysFramebufferGetFont
	#define EXT_SysFramebufferGetFont
	#define GET_SysFramebufferGetFont(fl)  CAL_CMGETAPI( "SysFramebufferGetFont" ) 
	#define CAL_SysFramebufferGetFont  SysFramebufferGetFont
	#define CHK_SysFramebufferGetFont  TRUE
	#define EXP_SysFramebufferGetFont  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFramebufferGetFont", (RTS_UINTPTR)SysFramebufferGetFont, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysFramebufferSysFramebufferGetFont
	#define EXT_SysFramebufferSysFramebufferGetFont
	#define GET_SysFramebufferSysFramebufferGetFont  ERR_OK
	#define CAL_SysFramebufferSysFramebufferGetFont pISysFramebuffer->ISysFramebufferGetFont
	#define CHK_SysFramebufferSysFramebufferGetFont (pISysFramebuffer != NULL)
	#define EXP_SysFramebufferSysFramebufferGetFont  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysFramebufferGetFont
	#define EXT_SysFramebufferGetFont
	#define GET_SysFramebufferGetFont(fl)  CAL_CMGETAPI( "SysFramebufferGetFont" ) 
	#define CAL_SysFramebufferGetFont pISysFramebuffer->ISysFramebufferGetFont
	#define CHK_SysFramebufferGetFont (pISysFramebuffer != NULL)
	#define EXP_SysFramebufferGetFont  CAL_CMEXPAPI( "SysFramebufferGetFont" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysFramebufferGetFont  PFSYSFRAMEBUFFERGETFONT pfSysFramebufferGetFont;
	#define EXT_SysFramebufferGetFont  extern PFSYSFRAMEBUFFERGETFONT pfSysFramebufferGetFont;
	#define GET_SysFramebufferGetFont(fl)  s_pfCMGetAPI2( "SysFramebufferGetFont", (RTS_VOID_FCTPTR *)&pfSysFramebufferGetFont, (fl), 0, 0)
	#define CAL_SysFramebufferGetFont  pfSysFramebufferGetFont
	#define CHK_SysFramebufferGetFont  (pfSysFramebufferGetFont != NULL)
	#define EXP_SysFramebufferGetFont  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysFramebufferGetFont", (RTS_UINTPTR)SysFramebufferGetFont, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFSYSFRAMEBUFFERDEVICEINIT ISysFramebufferDeviceInit;
 	PFSYSFRAMEBUFFERBEGINPAINT ISysFramebufferBeginPaint;
 	PFSYSFRAMEBUFFERENDPAINT ISysFramebufferEndPaint;
 	PFSYSFRAMEBUFFERFLUSH ISysFramebufferFlush;
 	PFSYSFRAMEBUFFERGETCURRENTADDRESS ISysFramebufferGetCurrentAddress;
 	PFSYSFRAMEBUFFERENABLECOLORPALETTE8 ISysFramebufferEnableColorPalette8;
 	PFSYSFRAMEBUFFERGETFONTLIST ISysFramebufferGetFontList;
 	PFSYSFRAMEBUFFERGETFONT ISysFramebufferGetFont;
 } ISysFramebuffer_C;

#ifdef CPLUSPLUS
class ISysFramebuffer : public IBase
{
	public:
		virtual RTS_RESULT CDECL ISysFramebufferDeviceInit(void) =0;
		virtual RTS_RESULT CDECL ISysFramebufferBeginPaint(void) =0;
		virtual RTS_RESULT CDECL ISysFramebufferEndPaint(void) =0;
		virtual RTS_RESULT CDECL ISysFramebufferFlush(RTS_Rectangle* aInvalidate, RTS_UI32 uiNumRects) =0;
		virtual RTS_RESULT CDECL ISysFramebufferGetCurrentAddress(FBPixel **pAddress) =0;
		virtual RTS_RESULT CDECL ISysFramebufferEnableColorPalette8(RTS_UI8 *pPalette) =0;
		virtual RTS_HANDLE CDECL ISysFramebufferGetFontList(void) =0;
		virtual RTS_RESULT CDECL ISysFramebufferGetFont(FBFont** ppFont, char* pszFontName, RTS_UI8 ucFontSize, RTS_UI32 uiFlags) =0;
};
	#ifndef ITF_SysFramebuffer
		#define ITF_SysFramebuffer static ISysFramebuffer *pISysFramebuffer = NULL;
	#endif
	#define EXTITF_SysFramebuffer
#else	/*CPLUSPLUS*/
	typedef ISysFramebuffer_C		ISysFramebuffer;
	#ifndef ITF_SysFramebuffer
		#define ITF_SysFramebuffer
	#endif
	#define EXTITF_SysFramebuffer
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSFRAMEBUFFERITF_H_*/
