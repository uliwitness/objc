/*
 *	SuperCard 4.72 WASTE interface
 *	Portions Copyright 2011 Mark Lucas
 *	All rights reserved.
 *
 *  Portions Copyright (c) 1993-2003 Marco Piovanelli
 *	All Rights Reserved
 *
 *  C port by Dan Crevier
 *
 */

#pragma once

#ifndef __SuperWASTE_472__
#define __SuperWASTE_472__

//	Toolbox #includes

#include <Carbon/Carbon.h>

#define __ZERO_SPACE_INDENTING__	1
#define	__SUPPORTS_EMBEDDED_OBJECTS__	1

//	define long coordinates types (LongPt and LongRect)

#ifndef __LONGCOORDINATES__
#ifndef _LongCoords_
#define _LongCoords_

typedef struct LongPt
{
	SInt32 v;
	SInt32 h;
} LongPt;

typedef struct LongRect
{
	SInt32 top;
	SInt32 left;
	SInt32 bottom;
	SInt32 right;
} LongRect;

#endif /*_LongCoords_*/
#endif /*__LONGCOORDINATES__*/

// MPW needs topLeft and botRight defined here
#ifndef topLeft
#define topLeft(r)              			(((Point *) &(r))[0])
#endif

#ifndef botRight
#define botRight(r)             			(((Point *) &(r))[1])
#endif

// pascal-like macros for testing, setting, clearing and inverting bits
#define BTST( FLAGS, BIT )					((FLAGS) &   (1UL << (BIT)))
#define BSET( FLAGS, BIT )  				((FLAGS) |=  (1UL << (BIT)))
#define BCLR( FLAGS, BIT )  				((FLAGS) &= ~(1UL << (BIT)))
#define BCHG( FLAGS, BIT )  				((FLAGS) ^=  (1UL << (BIT)))

// pascal-like macros for shifting bits
#define BSL( A, B )							(((SInt32) (A)) << (B))
#define BSR( A, B )							(((SInt32) (A)) >> (B))

// macros used in conjunction with the styleRunPosition parameter
#define IS_LEFTMOST_RUN(RUN)				((RUN) <= leftStyleRun)
#define IS_RIGHTMOST_RUN(RUN)				(! ((RUN) & 0x01))

// make sure TARGET_API_MAC_CARBON is #defined
#ifndef TARGET_API_MAC_CARBON
#define TARGET_API_MAC_CARBON 0
#endif

#if !TARGET_API_MAC_CARBON
	#define IS_COLOR_PORT(PORT)				((((CGrafPtr)(PORT))->portVersion & 0xC000) == 0xC000)

	//	Carbon compatibility macros
	#define GetPortBitMap(PORT)				(&((PORT)->portBits))
	#define GetPortTextFont(PORT)			((PORT)->txFont)
	#define GetPortTextSize(PORT)			((PORT)->txSize)
	#define GetPortTextFace(PORT)			((PORT)->txFace)
	#define GetPortTextMode(PORT)			((PORT)->txMode)
	#define GetPortVisibleRegion(PORT, RGN)	(MacCopyRgn((PORT)->visRgn,(RGN)),(RGN))
	#define GetPortHiliteColor(PORT,RGB)	(((*(RGB)) = (*(GVarHandle)((CGrafPtr)(PORT))->grafVars)->rgbHiliteColor),(RGB))
	#define GetRegionBounds(RGN,RECT)		(((*(RECT)) = (*(RGN))->rgnBBox),(RECT))
	#define GetQDGlobalsArrow(CURS)			(((*(CURS)) = qd.arrow),(CURS))
	#define GetQDGlobalsBlack(PAT)			(((*(PAT)) = qd.black),(PAT))
	#define GetQDGlobalsGray(PAT)			(((*(PAT)) = qd.gray),(PAT))
#else
	//	when compiling for Carbon, we need Universal Headers 3.3 or newer
	#if ( UNIVERSAL_INTERFACES_VERSION < 0x0330 )
		#error "You need Universal Headers version 3.3 or newer to compile this version of WASTE for Carbon"
	#endif

	#define IS_COLOR_PORT(PORT)				true
	#define GetPortBitMap(PORT)				((BitMap*)*GetPortPixMap(PORT))
	#define StripAddress(ADDRESS)			(ADDRESS)
#endif

// other macros
#ifndef ABS
#define ABS(A) 								((A) > 0 ? (A) : -(A))
#endif
#define BLOCK_CLR(X)						_WEBlockClr(&(X), sizeof(X));

// define WASTE_VERSION is standard NumVersion format
// Notice that unlike the first two bytes, coded in BCD, the last byte is a plain unsigned integer,
// in the range 0..255, although applications like ResEdit get this wrong.
// see technote #1132: Version Territory for more details (http://devworld.apple.com/technotes/tn/tn1132.html)

#define WASTE_VERSION						0x02006003	/* 2.0b3 */

// set WASTE_SHARED_LIBRARY to 1 when building a CFM-based shared library
#ifndef WASTE_SHARED_LIBRARY
#define WASTE_SHARED_LIBRARY				0
#endif

//	make sure WASTE_SHARED_LIBRARY is false if building a non-CFM project
#if ( WASTE_SHARED_LIBRARY && ( ! TARGET_RT_MAC_CFM ) )
#error "WASTE_SHARED_LIBRARY must be 0 in a classic 68K project"
#endif

// set WASTE_DEBUG to 1 to perform various consistency checks;
// errors will be reported with DebugStr()
// WARNING: when WASTE_DEBUG is set, WEIdle() calls can be extremely time-consuming
#ifndef WASTE_DEBUG
#define WASTE_DEBUG						0
#endif

// set WASTE_OBJECTS to 0 if you don't need embedded objects
#ifndef WASTE_OBJECTS
#define	WASTE_OBJECTS					__SUPPORTS_EMBEDDED_OBJECTS__
#endif

// set WASTE_DRAG_AND_DROP to 0 to avoid compiling code for the Drag Manager
#ifndef WASTE_DRAG_AND_DROP
#define WASTE_DRAG_AND_DROP				1
#endif

// set WASTE_UNICODE to 0 to avoid compiling code for Unicode support
#ifndef WASTE_UNICODE
#define WASTE_UNICODE					TARGET_RT_MAC_CFM
#endif

// set WASTE_USE_UPPS to 0 if you don't need UPPs
#ifndef WASTE_USE_UPPS
#define WASTE_USE_UPPS					(TARGET_RT_MAC_CFM && (!TARGET_API_MAC_CARBON))
#endif

// set WASTE_NO_RO_CARET to 1 to hide the caret in read-only mode
#ifndef WASTE_NO_RO_CARET
#define WASTE_NO_RO_CARET				1
#endif

// set WASTE_IC_SUPPORT to 1 to use Dan Crevier's
// support of URL cmd-clicking through Internet Config
#ifndef WASTE_IC_SUPPORT
#define WASTE_IC_SUPPORT				0
#endif

// If WASTE_OBJECTS_ARE_GLYPHS is set to 0 (default), WEGetOffset returns kObjectEdge in
// the edge parameter when thePoint is in the middle half of an object: as a result,
// clicking in the middle of an object immediately _selects_ the object, so that a second
// click immediately following triggers the 'clik' callback (this can be handy to make
// sound objects play when they are double-clicked, for example).

// If WASTE_OBJECTS_ARE_GLYPHS is set to 1, WEGetOffset treats embedded objects
// like ordinary glyphs and never returns kObjectEdge in the edge parameter:
// as a result, clicking in the middle of an object always positions the caret either
// to the left or to the right of the object.

#ifndef WASTE_OBJECTS_ARE_GLYPHS
#define WASTE_OBJECTS_ARE_GLYPHS		0
#endif

// set WASTE_TRANSLUCENT_DRAGS to 0 to avoid compiling code for translucent drags

#ifndef WASTE_TRANSLUCENT_DRAGS
//#define WASTE_TRANSLUCENT_DRAGS			(WASTE_DRAG_AND_DROP && (TARGET_CPU_PPC || (!TARGET_RT_MAC_CFM)))
#define WASTE_TRANSLUCENT_DRAGS			0	//(WASTE_DRAG_AND_DROP && (TARGET_CPU_PPC || (!TARGET_RT_MAC_CFM)))
#endif

// set WASTE_RTF to 0 to avoid compiling the WASTE_RTF library into WASTE itself
#ifndef WASTE_RTF
#define WASTE_RTF						1
#endif
// macros for debugging

#if WASTE_DEBUG
#define WEASSERT(CONDITION, WARNING)	{ if (!(CONDITION)) DebugStr(WARNING); }
#else
#define WEASSERT(CONDITION, WARNING)
#endif

// determine if inline functions are supported

#if defined(__cplusplus) || defined(__MWERKS__)
#define INLINE inline
#else
#define INLINE static
#endif

#define TVECTOR_TEST(CFM_API)				((UInt32)(&CFM_API) != kUnresolvedCFragSymbolAddress)

// result codes
enum
{
	weCantUndoErr				=	-10015,	// undo buffer is clear (= errAECantUndo)
	weEmptySelectionErr			=	-10013,	// selection range is empty (= errAENoUserSelection)
	weUnknownObjectTypeErr		=	-9478,	// specified object type is not registered
	weObjectNotFoundErr			=	-9477,	// no object found at specified offset
	weReadOnlyErr				=	-9476,	// instance is read-only
	weTextNotFoundErr			=	-9474,	// search string not found
	weInvalidTextEncodingErr	=	-9473,	// specified text encoding is invalid or unsupported
	weDuplicateAttributeErr		=	-9472,	// one of the attribute selectors was specified more than once
	weInvalidAttributeSizeErr	=	-9471,	// attribute size is invalid
	weReadOnlyAttributeErr		=	-9470,	// attribute is read-only
	weOddByteCountErr			=	-9469,	// expected an even number of bytes
	weTooManyTabsErr			=	-9468,	// too many tabs
	weTabOrderingErr			=	-9467,	// tabs must be arranged in strict left-to-right order
	weInvalidAttributeValueErr	=	-9466,	// invalid WESelector value for attribute passed to WESetAttributes
	weNoViewErr					=	-9465,	// WASTE instance has no associated view
	weHandlerNotFoundErr		=	-1717,	// couldn't find handler for the specified type/selector pair (= errAEHandlerNotFound)
	weNotHandledErr				=	-1708,  // please use default handling (= errAEEventNotHandled)
	weNewerVersionErr			=	-1706,	// need a newer version of WASTE (= errAENewerVersion)
	weCorruptDataErr			=	-1702,	// corrupt data (= errAECorruptData)
	weProtocolErr				=	-603,	// improper call order (= protocolErr)
	weUndefinedSelectorErr		=	-50,	// unknown selector
	weNoDragErr 				= 	128		// can be returned internally by _WEDrag
};

// values for WEInstallObjectHandler handlerSelector parameter
enum
{
	weNewHandler 		= 	FOUR_CHAR_CODE('new '),
	weDisposeHandler 	= 	FOUR_CHAR_CODE('free'),
	weDrawHandler 		= 	FOUR_CHAR_CODE('draw'),
	weClickHandler 		= 	FOUR_CHAR_CODE('clik'),
	weStreamHandler		=	FOUR_CHAR_CODE('strm'),
	weHoverHandler		=	FOUR_CHAR_CODE('hovr')
};

// action kinds
enum
{
	weAKSequence		=	-1,		// action sequence (used internally)
	weAKNone			=	0,		// null action
	weAKUnspecified		=	1,		// action of unspecified nature
	weAKTyping			=	2,		// some text has been typed in
	weAKCut				=	3,		// the selection range has been cut
	weAKPaste			=	4,		// something has been pasted
	weAKClear			=	5,		// the selection range has been deleted
	weAKDrag			=	6,		// drag and drop operation
	weAKSetStyle		=	7,		// some style has been applied to a text range
	weAKSetRuler		=	8,		// some ruler has been applied to a text range
	weAKBackspace		=	9,		// text deleted by backspace
	weAKFwdDelete		=	10,		// text deleted by forward delete
	weAKCaseChange		=	11,		// case transformation
	weAKObjectChange	=	12		// an embedded object has been modified
};

// action flags
enum
{
	weAFIsRedo			=	0x0100,	// action saves edit state prior to a WEUndo call
	weAFIsSequence		=	0x0200,	// action is a sequence of actions to be treated as one

	weAFSaveText		=	0x0001,	// save text
	weAFSaveStyles		=	0x0002,	// save styles
	weAFSaveSoup		=	0x0004, // save soup
	weAFSaveRulers		=	0x0008,	// save paragraph info
	weAFSaveAll			=	0x000F,	// save all of the above
	weAFSaveObjectAttrs	=	0x0010	// save object attributes
};

// mouse actions passed to object hover handlers
enum
{
	weMouseEnter		=	0,		//	mouse has entered object frame
	weMouseWithin		=	1,		//	mouse is still within object frame
	weMouseLeave		=	2		//	mouse has exited object frame
};

// destination kinds passed to object streaming handlers
enum
{
	weToScrap			=	0,		//	called from WECopy to copy an object to the scrap
	weToDrag			=	1,		//	called from WEClick (_WESendFlavor) to copy an object to a drag
	weToSoup			=	2		//	called internally to create a private scrap (e.g., for undo/redo)
};

// horizontal alignment styles
enum
{
	weFlushLeft 		=	-2,		// flush left
	weFlushRight		=	-1,		// flush right
	weFlushDefault		=	 0,		// flush according to system direction
	weCenter			=	 1,		// centered
	weJustify			=	 2,		// fully justified
	weDecimal			=	 3		// align on decimal point (for tabs)
};

// dominant line directions
enum
{
	weDirRightToLeft	=	-1,		// right-to-left
	weDirLeftToRight	=	 0,		// left-to-right
	weDirDefault		=	 1		// according to system direction
};

// case types
enum
{
	weLowerCase			=	0,		// lowercase
	weUpperCase			=	1		// uppercase
};

#define IsRightToLeft(direction)	(((direction) == weDirRightToLeft) || (((direction) == weDirDefault) && (GetSysDirection() != 0)))

// values for the edge parameter
enum
{
	kLeadingEdge 		= 	-1,		// point is on the leading edge of a glyph
	kTrailingEdge 		= 	 0,		// point is on the trailing edge of a glyph
	kObjectEdge 		= 	 2		// point is inside an embedded object
};

// control character codes
enum
{
	kObjectMarker 		=	0x01,
	kBackspace 			=	0x08,
	kTab 				=	0x09,
	kEOL 				=	0x0D,
	kArrowLeft 			=	0x1C,
	kArrowRight 		=	0x1D,
	kArrowUp 			=	0x1E,
	kArrowDown 			=	0x1F,
	kSpace 				=  	0x20,
	kForwardDelete 		=	0x7F
};

// special Unicode codepoints (see <http://charts.unicode.org/>)
enum
{
	kUnicodeParagraphSeparator				=	0x2029,		//	U+2029 PARAGRAPH SEPARATOR
	kUnicodeObjectReplacementCharacter		=	0xFFFC,		//	U+FFFC OBJECT REPLACEMENT CHARACTER

//	byte-order marks -- these codes are often used at the beginning of a UTF-16 stream
//	to mark the stream byte order as either big-endian or little-endian
//	note that FFFE is not a valid Unicode character, but can be read as a swapped ZWNBS
	kBigEndianByteOrderMark					=	0xFEFF,		//	U+FEFF ZERO WIDTH NO BREAK SPACE
	kLittleEndianByteOrderMark				=	0xFFFE
};

// bit equates for the tsFlags field of the WETextStyle record
enum
{
	tsRightToLeft 		=	7			//	right-to-left run
};

// bit equates for the tsMoreStyles field of the WETextStyle record
/*enum
{
	tsStrikethrough		=	0			//	strikethrough
};*/
// bit equates for the tsXFace field of the WETextStyle record
enum
{
	tsStrikethrough			=	0,			//	strikethrough
	tsDoubleStrikethrough	=	1,			//	double strikethrough
	tsSmallCaps				=	2,			//	small caps
	tsAllCaps				=	3,			//	all caps
	tsAllLowercase			=	4,			//	all lowercase
	tsHidden				=	5,			//	hidden
	tsEmbossed				=	6,			//	embossed
	tsEngraved				=	7			//	engraved
};

//	underline styles (tsUnderlineStyle field of the WETextStyle record)
enum
{
	tsPlainUnderline		=	0,			//	plain underline (default)
	tsWordUnderline			=	1,			//	word underline
	tsDoubleUnderline		=	2,			//	double underline
	tsDotUnderline			=	3,			//	dot underline
	tsDashUnderline			=	4,			//	dash underline
	tsDotDashUnderline		=	5,			//	dot-dash underline
	tsDotDotDashUnderline	=	6,			//	dot-dot-dash underline
	tsThickUnderline		=	7,			//	thick underline
	tsWaveUnderline			=	8			//	wave underline
};


//	bit masks for the flags field of the WERuler record
enum
{
//	pagination masks
	kRulerKeepTogether			=	0x00000001,			//	keep lines together on the same page
	kRulerKeepWithNext			=	0x00000002,			//	keep this paragraph with the next one on the same page
	kRulerPageBreakBefore		=	0x00000004,			//	this paragraph starts a new page
	kRulerWidowOrphanControl	=	0x00000008,			//	perform window/orphan control for this paragraph (only used if the following bit is set)
	kRulerWidowOrphanOverride	=	0x00000010,			//	override document-wide window/orphan control

//	other paragraph flags
	kRulerNoLineNumbering		=	0x00000020,			//	don't number the lines of this paragraph (overrides section-wide setting)
	kRulerNoHyphenation			=	0x00000040,			//	don't hyphenate this paragraph (overrides document-wide setting)

//	line spacing masks
	kRulerAbsoluteSpacing		=	0x00001000,			//	interpret lineSpacing field as an absolute height rather than multiplier
	kRulerAtLeastSpacing		=	0x00002000,			//	never make a line shorter than its taller character
	kRulerLineSpacingMask		=	0x0000F000			//	line spacing bits
};

// bit equates for the mode parameter in WESetStyle and WEContinuousStyle
enum
{
	kModeFont 				=	0,		// change font
	kModeFace 				=	1,		// change Quickdraw styles
	kModeSize 				=	2,		// change point size
	kModeColor 				=	3,		// change color
	kModeAddSize 			=	4,		// add tsSize to existing size
	kModeToggleFace 		=	5,		// toggle continuous styles rather than setting them
	kModeReplaceFace 		=	6,		// tsFace replaces existing styles outright
	kModePreserveScript 	=	7,		// apply font to runs of same script only
	kModeExtractSubscript 	=	8,		// apply font to eligible subruns of different script
	kModeFaceMask 			= 	9,		// change Quickdraw styles; use mask

/*//	private bits for internal use
	kModeStrikethrough		=	25,		// change strikethru style
	kModeTransferMode		=	26,		// change QuickDraw text transfer mode
	kModeBackgroundColor	=	27,		// change background color
	kModeVerticalShift		=	28,		// change vertical shift
	kModeAddVerticalShift	=	29,		// add tsVerticalShift to existing value
	kModeTSMHiliteStyle		=	30,		// change TSM hilite style
	kModeObject 			= 	31		// change tsObject field*/

//	private bits for internal use
	kModeXFace				=	22,		// change additional styles
	kModeXFaceMask			=	23,		// change additional styles; use mask
	kModeLanguage			=	24,		// change language
	kModeUnderlineStyle		=	25,		// change underline style
	kModeTransferMode		=	26,		// change QuickDraw text transfer mode
	kModeBackgroundColor	=	27,		// change background color
	kModeVerticalShift		=	28,		// change vertical shift
	kModeAddVerticalShift	=	29,		// add tsVerticalShift to existing value
	kModeTSMHiliteStyle		=	30,		// change TSM hilite style
	kModeObject 			= 	31		// change tsObject field
};

// values for the mode parameter in WESetStyle and WEContinuousStyle
enum
{
	weDoFont				=	1UL << kModeFont,
	weDoFace				=	1UL << kModeFace,
	weDoSize				=	1UL << kModeSize,
	weDoColor				=	1UL << kModeColor,
	weDoAll					=	( weDoFont | weDoFace | weDoSize | weDoColor ),
	weDoAddSize				=	1UL << kModeAddSize,
	weDoToggleFace			=	1UL << kModeToggleFace,
	weDoReplaceFace			=	1UL << kModeReplaceFace,
	weDoPreserveScript		=	1UL << kModePreserveScript,
	weDoSmartFont			=	( weDoFont | weDoPreserveScript ),
	weDoExtractSubscript	=	1UL << kModeExtractSubscript,
	weDoFaceMask			=	1UL << kModeFaceMask,

//	private bits
/*	weDoStrikethrough		=	1UL << kModeStrikethrough,
	weDoTransferMode		=	1UL << kModeTransferMode,
	weDoBackgroundColor		=	1UL << kModeBackgroundColor,
	weDoVerticalShift		=	1UL << kModeVerticalShift,
	weDoAddVerticalShift	=	1UL << kModeAddVerticalShift,
	weDoTSMHiliteStyle		=	1UL << kModeTSMHiliteStyle,
	weDoObject				=	1UL << kModeObject*/

//	private bits
	weDoXFace				=	1UL << kModeXFace,
	weDoXFaceMask			=	1UL << kModeXFaceMask,
	weDoLanguage			=	1UL << kModeLanguage,
	weDoUnderlineStyle		=	1UL << kModeUnderlineStyle,
	weDoTransferMode		=	1UL << kModeTransferMode,
	weDoBackgroundColor		=	1UL << kModeBackgroundColor,
	weDoVerticalShift		=	1UL << kModeVerticalShift,
	weDoAddVerticalShift	=	1UL << kModeAddVerticalShift,
	weDoTSMHiliteStyle		=	1UL << kModeTSMHiliteStyle,
	weDoObject				=	1UL << kModeObject
	
};

// bit equates for the mode parameter in WESetRuler and WEContinuousRuler
enum
{
	kModeDirection			=	0,		// change primary direction
	kModeAlignment 			=	1,		// change alignment
	kModeLeftIndent			=	2,		// change left indent
	kModeRightIndent		=	3,		// change right indent
	kModeFirstLineIndent	=	4,		// change first line indent
	kModeLineSpacing		=	5,		// change line spacing
	kModeSpaceBefore		=	6,		// change space before
	kModeSpaceAfter			=	7,		// change space after
	kModeTabs				=	8,		// change tab array
	kModeTopBorderStyle		=	9,		// change top border style
	kModeBottomBorderStyle	=	10,		// change bottom border style
	kModeParagraphUserData		=	11,		// change paragraph user data
	kModeParagraphFlags			=	12,		// change paragraph flags
	kModeParagraphFlagsMask		=	13,		// change paragraph flags; use mask

//	additive modes
	kModeAddLeftIndent			=	16,
	kModeAddRightIndent			=	17,
	kModeAddFirstLineIndent		=	18,
	kModeAddLineSpacing			=	19,
	kModeAddSpaceBefore			=	20,
	kModeAddSpaceAfter			=	21
} ;

// values for the mode parameter in WESetRuler and WEContinuousRuler
enum
{
	weDoDirection			=	1UL << kModeDirection,
	weDoAlignment			=	1UL << kModeAlignment,
	weDoLeftIndent			=	1UL << kModeLeftIndent,
	weDoRightIndent			=	1UL << kModeRightIndent,
	weDoFirstLineIndent		=	1UL << kModeFirstLineIndent,
	weDoLineSpacing			=	1UL << kModeLineSpacing,
	weDoSpaceBefore			=	1UL << kModeSpaceBefore,
	weDoSpaceAfter			=	1UL << kModeSpaceAfter,
	weDoTabs				=	1UL << kModeTabs,
	weDoTopBorderStyle		=	1UL << kModeTopBorderStyle,
	weDoBottomBorderStyle	=	1UL << kModeBottomBorderStyle,
	weDoParagraphUserData	=	1UL << kModeParagraphUserData,
	weDoParagraphFlags		=	1UL << kModeParagraphFlags,
	weDoParagraphFlagsMask	=	1UL << kModeParagraphFlagsMask,

	weDoWholeRuler			=	( weDoDirection | weDoAlignment | weDoLeftIndent |
								weDoRightIndent | weDoFirstLineIndent | weDoLineSpacing |
								weDoSpaceBefore | weDoSpaceAfter | weDoTopBorderStyle |
								weDoBottomBorderStyle ),

	//	tabs are not implemented yet
//	weDoTabs				=	1UL << kModeTabs
//	additive modes
	weDoAddLeftIndent			=	1UL << kModeAddLeftIndent,
	weDoAddRightIndent			=	1UL << kModeAddRightIndent,
	weDoAddFirstLineIndent		=	1UL << kModeAddFirstLineIndent,
	weDoAddLineSpacing			=	1UL << kModeAddLineSpacing,
	weDoAddSpaceBefore			=	1UL << kModeAddSpaceBefore,
	weDoAddSpaceAfter			=	1UL << kModeAddSpaceAfter
} ;

//	WASTE creator
enum
{
	kWASTECreator				= FOUR_CHAR_CODE('OEDE')
} ;

//	character attribute selectors
enum
{
//	these tags are saved in style scraps and can also be passed to WEGetAttributes/WESetAttributes
	weTagFontFamily				= FOUR_CHAR_CODE('font'),	//	type = shor (FMFontFamily); TEXT (Str255) in scraps
	weTagFontSize				= FOUR_CHAR_CODE('ptsz'),	//	type = fixd
	weTagBold					= FOUR_CHAR_CODE('bold'),	//	type = bool
	weTagItalic					= FOUR_CHAR_CODE('ital'),	//	type = bool
	weTagUnderline				= FOUR_CHAR_CODE('undl'),	//	type = bool
	weTagOutline				= FOUR_CHAR_CODE('outl'),	//	type = bool
	weTagShadow					= FOUR_CHAR_CODE('shad'),	//	type = bool
	weTagCondensed				= FOUR_CHAR_CODE('cond'),	//	type = bool
	weTagExtended				= FOUR_CHAR_CODE('pexp'),	//	type = bool
	weTagStrikethrough			= FOUR_CHAR_CODE('strk'),	//	type = bool
	weTagDoubleStrikethrough	= FOUR_CHAR_CODE('dstr'),	//	type = bool
	weTagSmallCaps				= FOUR_CHAR_CODE('smcp'),	//	type = bool; == kAESmallCaps
	weTagAllCaps				= FOUR_CHAR_CODE('alcp'),	//	type = bool; == kAEAllCaps
	weTagAllLowercase			= FOUR_CHAR_CODE('lowc'),	//	type = bool; == kAELowercase
	weTagHidden					= FOUR_CHAR_CODE('hidn'),	//	type = bool; == kAEHidden
	weTagEmbossed				= FOUR_CHAR_CODE('embo'),	//	type = bool
	weTagEngraved				= FOUR_CHAR_CODE('engr'),	//	type = bool
	weTagTextColor				= FOUR_CHAR_CODE('colr'),	//	type = cRGB
	weTagBackgroundColor		= FOUR_CHAR_CODE('pbcl'),	//	type = cRGB
	weTagTransferMode			= FOUR_CHAR_CODE('pptm'),	//	type = shor
	weTagVerticalShift			= FOUR_CHAR_CODE('xshf'),	//	type = fixd
	weTagLanguage				= FOUR_CHAR_CODE('lang'),	//	type = TEXT; ISO 639-1 language code
	weTagUnderlineStyle			= FOUR_CHAR_CODE('unds'),	//	type = enum (deft/word/dubl/thck/...)

//	weTagTextEncoding is saved in style scraps and can also be passed to WEGetAttributes
	weTagTextEncoding			= FOUR_CHAR_CODE('ptxe'),	//	type = long (TextEncoding)

//	weTagPlain can be used to reset all style attributes (bold to strikethrough) at once
//	it can also be passed to WEGetAttributes and WEMatchAttributes
	weTagPlain					= FOUR_CHAR_CODE('plan'),	//	type = bool

//	the superscript and subscript tags are just a different way of manipulating the vertical shift
	weTagSuperscript			= FOUR_CHAR_CODE('spsc'),	//	type = bool
	weTagSubscript				= FOUR_CHAR_CODE('sbsc'),	//	type = bool

//	these TextEdit-compatibility tags are only valid in WEGetAttributes call
	weTagQDStyles				= FOUR_CHAR_CODE('qdst'),	//	type = Style
	weTagTETextStyle			= FOUR_CHAR_CODE('tets'),	//	type = TextStyle
	weTagRunDirection			= FOUR_CHAR_CODE('rdir'),	//	type = bool

//	meta-tags that are only legal in WESetAttributes/WESetOneAttribute calls
	weTagForceFontFamily		= FOUR_CHAR_CODE('ffnt'),	//	type = shor (FMFontFamily)
	weTagAddFontSize			= FOUR_CHAR_CODE('+siz'),	//	type = fixd
	weTagAddVerticalShift		= FOUR_CHAR_CODE('+shf'),	//	type = fixd

//	tags only used in style scraps
	weTagOriginalFontNumber		= FOUR_CHAR_CODE('fnt#'),	//	type = shor (FMFontFamily)
	weTagEmbeddedObject			= FOUR_CHAR_CODE('obj '),	//	type = any
	weTagEmbeddedObjectSize		= FOUR_CHAR_CODE('objs'),	//	type = QDpt
	
	weTagEmbeddedObjectBaseline	= FOUR_CHAR_CODE('objb'),	//	type = shor
	weTagTabIndent				= FOUR_CHAR_CODE('indt'),	//	type = fixd
	weTagTabLeader				= FOUR_CHAR_CODE('lead'),	//	type = enum (DOTS/HYPH/UNDL/...)
	weTagGroupStyle				= FOUR_CHAR_CODE('grup')	//	type = bool
} ;

//	document property tags (these are currently only used by the RTF I/O module)
enum
{
	weCreatorDocumentInfo		= FOUR_CHAR_CODE('Info'),		/*	creator for the following property tags */

	weTagDocumentTitle			= FOUR_CHAR_CODE('Titl'),
	weTagDocumentSubject		= FOUR_CHAR_CODE('Subj'),
	weTagDocumentAuthor			= FOUR_CHAR_CODE('Auth'),
	weTagDocumentManager		= FOUR_CHAR_CODE('Mngr'),
	weTagDocumentCompany		= FOUR_CHAR_CODE('Cmpy'),
	weTagDocumentCategory		= FOUR_CHAR_CODE('Ctgy'),
	weTagDocumentKeywords		= FOUR_CHAR_CODE('Keyw'),
	weTagDocumentComments		= FOUR_CHAR_CODE('Cmnt'),
	weTagDocumentOperator		= FOUR_CHAR_CODE('Oper'),
	weTagDocumentBaseAddress	= FOUR_CHAR_CODE('Hlnk'),
	weTagPageInfo				= FOUR_CHAR_CODE('Page'),
	weTagMacPrintRecord			= FOUR_CHAR_CODE('PRec')
};

//	underline styles
enum
{
	weTagUnderlineDefault		= FOUR_CHAR_CODE('deft'),
	weTagUnderlineWord			= FOUR_CHAR_CODE('word'),
	weTagUnderlineDouble		= FOUR_CHAR_CODE('dubl'),
	weTagUnderlineThick			= FOUR_CHAR_CODE('thck'),
	weTagUnderlineDash			= FOUR_CHAR_CODE('-   '),
	weTagUnderlineDot			= FOUR_CHAR_CODE('.   '),
	weTagUnderlineDotDash		= FOUR_CHAR_CODE('.-  '),
	weTagUnderlineDotDotDash	= FOUR_CHAR_CODE('..- '),
	weTagUnderlineWave			= FOUR_CHAR_CODE('wave')
} ;

//	direction tags
enum
{
	weTagDirectionDefault		= FOUR_CHAR_CODE('deft'),	//	lay bidi text according to SysDirection
	weTagDirectionLeftToRight	= FOUR_CHAR_CODE('L->R'),	//	dominant line direction is left to right
	weTagDirectionRightToLeft	= FOUR_CHAR_CODE('R->L')	//	dominant line direction is right to left
} ;

#if __SUPPORTS_WASTE21_LINEHEIGHT__
//	line spacing mode tags
enum
{
	weTagLineSpacingAbsolute	= FOUR_CHAR_CODE('abso'),	//	use absolute line spacing
	weTagLineSpacingAtLeast		= FOUR_CHAR_CODE('atle'),	//	use absolute line spacing or height of tallest character, whichever is greater
	weTagLineSpacingRelative	= FOUR_CHAR_CODE('rele')	//	relative line spacing (0.0 = single spacing; 1.0 = double spacing; etc.)
} ;
#endif

//	tab leader tags
enum
{
	weTagLeaderNone				= FOUR_CHAR_CODE('NONE'),	//	no tab leader (default)
	weTagLeaderDots				= FOUR_CHAR_CODE('DOTS'),	//	dots
	weTagLeaderHyphens			= FOUR_CHAR_CODE('HYPH'),	//	hyphens
	weTagLeaderUnderline		= FOUR_CHAR_CODE('UNDL'),	//	underline
	weTagLeaderThickLine		= FOUR_CHAR_CODE('THKL'),	//	thick line (for future use)
	weTagLeaderEqualSigns		= FOUR_CHAR_CODE('=   ')	//	equal signs
} ;

//	alignment tags
enum
{
	weTagAlignmentDefault		= FOUR_CHAR_CODE('deft'),	//	align according to SysDirection
	weTagAlignmentLeft			= FOUR_CHAR_CODE('left'),	//	flush left
	weTagAlignmentRight			= FOUR_CHAR_CODE('rght'),	//	flush right
	weTagAlignmentCenter		= FOUR_CHAR_CODE('cent'),	//	center
	weTagAlignmentFull			= FOUR_CHAR_CODE('full'),	//	justify
	weTagAlignmentDecimal		=	FOUR_CHAR_CODE('decm')	// decimal (tabs only)
} ;

//	border style tags
enum
{
	weTagBorderStyleNone		= FOUR_CHAR_CODE('NONE'),	//	no border
	weTagBorderStyleThin		= FOUR_CHAR_CODE('SLDL'),	//	thin line
	weTagBorderStyleDotted		= FOUR_CHAR_CODE('DTDL'),	//	dotted line
	weTagBorderStyleThick		= FOUR_CHAR_CODE('THKL')	//	thick line
} ;

//	paragraph attribute selectors
enum
{
	weTagDirection				= FOUR_CHAR_CODE('LDIR'),		//	type = enum (deft/L->R/R->L)
	weTagAlignment				= FOUR_CHAR_CODE('pjst'),		//	type = enum (deft/left/cent/rght/full)
	weTagLeftIndent				= FOUR_CHAR_CODE('lein'),		//	type = fixd
	weTagRightIndent			= FOUR_CHAR_CODE('riin'),		//	type = fixd
	weTagFirstLineIndent		= FOUR_CHAR_CODE('fidt'),		//	type = fixd
	weTagSpaceBefore			= FOUR_CHAR_CODE('spbe'),		//	type = fixd
	weTagSpaceAfter				= FOUR_CHAR_CODE('spaf'),		//	type = fixd
	weTagLineSpacing			= FOUR_CHAR_CODE('ledg'),		//	type = fixd
	weTagTabList				= FOUR_CHAR_CODE('tabs'),		//	type = list of TABR
	weTagTopBorder				= FOUR_CHAR_CODE('TBRD'),		//	type = enum (NONE/SLDL/DTDL/...)
	weTagBottomBorderStyle		= FOUR_CHAR_CODE('BBRD'),		//	type = enum (NONE/SLDL/DTDL/...)
	weTagParagraphUserData		= FOUR_CHAR_CODE('pusr'),		//	type = long
	weTagKeepTogether			= FOUR_CHAR_CODE('keep'),		//	type = bool
	weTagKeepWithNext			= FOUR_CHAR_CODE('kepn'),		//	type = bool
	weTagPageBreakBefore		= FOUR_CHAR_CODE('pbrb'),		//	type = bool
	weTagWidowOrphanControl		= FOUR_CHAR_CODE('wido'),		//	type = bool
	weTagWidowOrphanOverride	= FOUR_CHAR_CODE('wdov'),		//	type = bool
	weTagNoLineNumbering		= FOUR_CHAR_CODE('!ln#'),		//	type = bool
	weTagNoHyphenation			= FOUR_CHAR_CODE('!hyp'),		//	type = bool

//	meta-tags that are only legal in WESetAttributes/WESetOneAttribute calls
	weTagAddLeftIndent			= FOUR_CHAR_CODE('+lei'),		//	type = fixd
	weTagAddRightIndent			= FOUR_CHAR_CODE('+rii'),		//	type = fixd
	weTagAddFirstLineIndent		= FOUR_CHAR_CODE('+fid'),		//	type = fixd
	weTagAddSpaceBefore			= FOUR_CHAR_CODE('+spb'),		//	type = fixd
	weTagAddSpaceAfter			= FOUR_CHAR_CODE('+spa'),		//	type = fixd
	weTagAddLineSpacing			= FOUR_CHAR_CODE('+led')		//	type = fixd
} ;

//	tab property tags used in WASTE 2.0 ruler scraps
enum
{
	weTagTabPosition			= FOUR_CHAR_CODE('posn'),		//	type = fixd
	weTagTabAlignment			= FOUR_CHAR_CODE('pjst'),		//	type = enum (left/cent/rgth/alno)
	weTagTabFiller				= FOUR_CHAR_CODE('fllc'),		//	type = TEXT
	weTagTabDecimal				= FOUR_CHAR_CODE('algc')		//	type = TEXT
} ;

// values for WEFeatureFlag action parameter
enum
{
	weBitSet 			=	 1,		// enables the specified feature
	weBitClear 			=	 0,		// disables the specified feature
	weBitTest 			=	-1,		// returns the current setting of the specified feature
	weBitToggle 		=	-2		// toggles the specified feature
};

// bit equates for the flags field in the WE record
enum
{
	weFHasColorQD 			=	31,		// Color Quickdraw is available (used only in classic 68K builds)
	weFHasDragManager 		=	30,		// the Drag Manager is available (not significant in Carbon builds)
	weFHasTranslucentDrags	=	29,		// SetDragImage is available (not significant in Carbon builds)
	weFNonRoman				=	28,		// at least one non-Roman script is enabled
	weFDoubleByte			=	27,		// a double-byte script is enabled
	weFBidirectional		=	26,		// a bidirectional script is enabled
	weFCaretRight			=	25,		// set if caret was drawn for R-L keyboard script
	weFCaretVisible			=	24,		// the caret is currently visible
	weFMouseTracking		=	23,		// set internally during mouse tracking
	weFAnchorIsEnd			=	22,		// anchor offset is selEnd
	weFUseNullStyle			=	21,		// a null style is associated with the empty selection
	weFActive				=	20,		// we're active
	weFHilited				=	19,		// true if text pane is highlighted (for Drag & Drop)
	weFCanAcceptDrag		=	18,		// the drag in the text pane can be accepted
	weFDragCaretVisible		=	17,		// drag caret is currently visible
	weFDestRectChanged		=	16,		// set if scroll callback needs to be called
	weFPrinting				=	15,		// set while printing a page
	weFAccumulateUndos		=	14,		// accumulate undoable changes in a single undo sequence
	weFHasFetchFontInfo		=	13,		// FetchFontInfo is available
	weFHasCollections		=	12,		// the Collection manager is available (not significant in Carbon builds)
	weFHasSonataFontManager	=	11,		// the new Font Manager (introduced in Mac OS 9) is available
	weFRunningOSX			=	10,		// we're running OS X
	weFHasAppearance11		=	9		// version 1.1 or newer of the Appearance Manager is available
};

// bit equates for the features field in the WE record
enum
{
	weFInhibitColor			=	31,		// draw in black & white only; ignore color
	weFInhibitICSupport		=	30,		// don't process command-clicks using Internet Config
	weFNoKeyboardSync		=	29,		// inhibit keyboard/script synchronization
	weFNoAutoTabForHangingIndent	=	28,		// don't add an automatic tab stop for hanging indents
	weFMultipleUndo			=	14,		// multiple undo/redo
	weFMonoStyled			=	13,		// disallow style changes
	weFInhibitRedraw		=	12,		// don't redraw text
	weFDrawOffscreen		=	11,		// draw text offscreen for smoother visual results
	weFUseTempMem			=	10,		// use temporary memory for main data structures
	weFInhibitRecal			=	 9,		// don't recalculate line breaks and don't redraw text
	weFDragAndDrop			=	 8,		// support drag and drop
	weFIntCutAndPaste		=	 7,		// intelligent cut & paste
	weFUndo					=	 6,		// support undo/redo
	weFReadOnly				=	 5,		// disallow editing
	weFOutlineHilite		=	 2,		// frame selection range when text pane is inactive
	weFAutoScroll			=	 0		// automatically scroll text when cursor is outside pane
};

// flavor types
enum
{
	kTypeText				=	FOUR_CHAR_CODE('TEXT'),		//	raw text, with no style/encoding information
	kTypeUnicodeText		=	FOUR_CHAR_CODE('utxt'),		//	UTF-16 encoded raw text
	kTypeUTF8Text			=	FOUR_CHAR_CODE('UTF8'),		//	UTF-8 encoded raw text
	kTypeTEStyleScrap		=	FOUR_CHAR_CODE('styl'),		//	TextEdit-style style scrap
	kTypeSoup 				=	FOUR_CHAR_CODE('SOUP'),		//	embedded object information
	kTypeFontTable			=	FOUR_CHAR_CODE('FISH'),		//	font table
	kTypeStyledText			=	FOUR_CHAR_CODE('STXT'),		//	AppleScript-style styled text
	kTypeParaFormat			=	FOUR_CHAR_CODE('WEpf'),		//	WASTE 2.0 paragraph formatting information (complements the 'WEru' flavor)
	kTypeRulerScrap			=	FOUR_CHAR_CODE('WEru'),		//	WASTE 2.0 ruler scrap (complements the 'WEpf' flavor)
	kTypeCharFormat			=	FOUR_CHAR_CODE('WEcf'),		//	WASTE 2.0 character formatting info (complements the 'WEst' flavor)
	kTypeStyleScrap			=	FOUR_CHAR_CODE('WEst'),		//	WASTE 2.0 style scrap (complements the 'WEcf' flavor)
	kTypeRTF				=	FOUR_CHAR_CODE('RTF '),		//	Rich Text Format
	kTypeRTFDPackage		=	FOUR_CHAR_CODE('RTFD'),		//	RTFD (RTF with external attachments)
	kTypeStyleDocument		=	0x544564B6,					//	Style document
//	kTypePicture			=	FOUR_CHAR_CODE('PICT'),		//	Quickdraw picture
//	kTypeSound				=	FOUR_CHAR_CODE('snd '),		//	sound

	kTypeWEReference		=	FOUR_CHAR_CODE('WE* '),		//	used internally as a private drag flavor
	kTypeLineSpacing		=	FOUR_CHAR_CODE('WEls')		//	WELineSpacing structure; used in ruler scraps
};

// selectors for WEGetInfo/WESetInfo
enum
{
	weAutoScrollDelay		=	FOUR_CHAR_CODE('ausd'),
	weBusyProc				=	FOUR_CHAR_CODE('busy'),
	weBusyInterval			=	FOUR_CHAR_CODE('bzin'),
	weCharByteHook			=	FOUR_CHAR_CODE('cbyt'),
	weCharTypeHook			=	FOUR_CHAR_CODE('ctyp'),
	weCharToPixelHook		=	FOUR_CHAR_CODE('c2p '),
	weClickLoop				=	FOUR_CHAR_CODE('clik'),
	weCurrentDrag			=	FOUR_CHAR_CODE('drag'),
	weDrawTextHook			=	FOUR_CHAR_CODE('draw'),
	weDrawTSMHiliteHook		=	FOUR_CHAR_CODE('dtsm'),
	weEraseHook				=	FOUR_CHAR_CODE('eras'),
	weFontFamilyToNameHook	=	FOUR_CHAR_CODE('ff2n'),
	weFontNameToFamilyHook	=	FOUR_CHAR_CODE('fn2f'),
	weFluxProc				=	FOUR_CHAR_CODE('flux'),
	weHiddenTextProc		=	FOUR_CHAR_CODE('hidn'),
	weHiliteDropAreaHook	=	FOUR_CHAR_CODE('hidr'),
	weLineBreakHook			=	FOUR_CHAR_CODE('lbrk'),
	wePixelToCharHook		=	FOUR_CHAR_CODE('p2c '),
	wePort					=	FOUR_CHAR_CODE('port'),
	wePreTrackDragHook		=	FOUR_CHAR_CODE('ptrk'),
	wePrepareViewHook		=	FOUR_CHAR_CODE('prep'),
	weProperties			=	FOUR_CHAR_CODE('prop'),
	weRefCon				=	FOUR_CHAR_CODE('refc'),
	weScrollProc			=	FOUR_CHAR_CODE('scrl'),
	weText					=	FOUR_CHAR_CODE('text'),
	weTranslateDragHook		=	FOUR_CHAR_CODE('xdrg'),
	weTranslucencyThreshold	=	FOUR_CHAR_CODE('tluc'),
	weTSMDocumentID			=	FOUR_CHAR_CODE('tsmd'),
	weTSMPostUpdate			=	FOUR_CHAR_CODE('post'),
	weTSMPreUpdate			=	FOUR_CHAR_CODE('pre '),
	weUndoProc				=	FOUR_CHAR_CODE('undo'),
	weURLHint				=	FOUR_CHAR_CODE('urlh'),
	weWordBreakHook			=	FOUR_CHAR_CODE('wbrk')
};

// ¥¥ MDL 2/25/99 WE ¥¥
//	Added defines for flags we pass to ourselves in upper word of WERec refCon field
#define dontwrapflag 				0x0001
#define scrollbarflag 				0x0002
#define allowobjectsflag 			0x0004
#define allowrulersflag 			0x0008
#define dontwrapmask 				0x00010000
#define scrollbarmask 				0x00020000
#define allowobjectsmask 			0x00040000
#define allowrulersmask 			0x00080000

#if __ZERO_SPACE_INDENTING__
//#define autoindentflag 				0x0004
#define autoindentmask 				0x00040000
#define autoindeintinversemask 		0xFFFBFFFF
#endif

enum
{
	kWESigRUNX				=		FOUR_CHAR_CODE ( 'RUNX' ),			//	SuperCard signature
	weTagScrollBar			=		FOUR_CHAR_CODE ( 'scrl' ),
	weTagFieldMargins		=		FOUR_CHAR_CODE ( 'marg' ),
	weTagFieldType			=		FOUR_CHAR_CODE ( 'ftyp' ),
	weTagUseTabs			=		FOUR_CHAR_CODE ( 'tabs' ),
	weTagDontWrap			=		FOUR_CHAR_CODE ( 'dont' ),
	weTagScriptEditorField	=		FOUR_CHAR_CODE ( 'scri' )
};


// ¥¥

// possible values returned by WEIntelligentPaste
enum
{
	weDontAddSpaces			=	 0,
	weAddSpaceOnLeftSide	=	-1,
	weAddSpaceOnRightSide	=	 1
};

// values for WEAllocate allocFlags parameter
enum
{
	kAllocClear			=	0x00000001,	// clear handle after allocation
	kAllocTemp			=	0x00000002	// use temporary memory if available
};

// match options for WEFind
enum
{
	weFindWholeWords				=	0x00000001,	// match whole words only
	weFindCaseInsensitive			=	0x00000002,	// ignore case differences
	weFindDiacriticalInsensitive	=	0x00000004,	// ignore diacritical marks
	weFindWidthInsensitive			=	0x00000008,	// treat 1- and 2-byte version of the same character as equivalent
	weFindKanaInsensitive			=	0x00000010	// treat hiragana and katakana as equivalent
};

// put options for WEPut
enum
{
	wePutIntCutAndPaste				=	0x00000001,	// use intelligent cut & paste rules
	wePutAddToTypingSequence		=	0x00000002,	// add text to existing typing sequence instead of pushing a new action
	wePutConvertLineBreaks			=	0x00000100,	// automatically convert Windows and Unix line breaks
	wePutDetectUnicodeBOM			=	0x00000200	// automatically detect Unicode byte-order-mark
};

// stream options for WEStreamRange
enum
{
	weStreamDestinationKindMask		=	0x000000FF, // bits propagated from inStreamOptions to inDestinationKind
	weStreamIncludeObjects			=	0x00000100	// include embedded objects in 'WEst' scraps
};

// options for WEGetTextRangeAsUnicode
enum
{
	weGetAddUnicodeBOM				=	0x00000200, // prepend a Unicode byte-order mark to the UTF-16 stream
	weGetLittleEndian				=	0x00000400	// return UTF-16 text in little-endian byte-order
};

// options for WESave
enum
{
	weSaveAddResources				=	0x00000001,
	weSaveCompatibilityResources	=	0x00000002,
	weSaveLittleEndian				=	0x00000004
};

// other miscellaneous constants
enum
{
	kCaretWidth = 1,			// width of the caret, in pixels
	kMinFontSize = 1,			// minimum valid font size
	kMaxFontSize = 0x7FFF,		// maximum valid font size
	kInvalidOffset = -1, 		// used to flag an invalid or nonexistent offset
	kUnknownObjectType = -1,	// returned by _WELookupObjectType for unknown flavors
	kCurrentSelection = -1,		// used as a meta-value in some calls, like WEStreamRange
	kNullStyle = -2,			// used as a meta-value in some calls, like WEMatchAttributes
	kTextMargin = 3,			// width of border area surrounding the text (in pixels)
//	kMaxScrollDelta = 30,		// maximum scroll amount used by standard click loop
	kMaxScrollDelta = 50,		// maximum scroll amount used by standard click loop
	kAutoScrollDelay = 10,		// delay before auto-scroll starts (in ticks)
	kDefaultObjectHeight = 32,	// default height for new objects
	kDefaultObjectWidth = 32,	// default width for new objects
	kAutoOrderingSize = 32,		// size of stack-based format array used by _WESegmentLoop
	kMaxTabCount = 20,				// maximum number of tabs that can be set in a single paragraph
	kMaxLanguageTagSize = 32,		// maximum size of a language tag, including the terminating NULL
//	kMaxLanguageTagSize = 33,		// maximum size of a language tag, including the terminating NULL
	kDefaultTabWidth = 36 << 16		// default default tab width (36 pixels, or 720 twips @ 72 dpi)

};

#if PRAGMA_STRUCT_ALIGN
#pragma options align=mac68k
#endif

typedef UInt16		WEStyleMode;
typedef UInt32		WERulerMode;
typedef SInt8		WEAlignment;
typedef SInt16		WEDirection;
typedef SInt16		WECase;
typedef SInt8		WEEdge;
typedef SInt16		WEActionKind;
typedef UInt16		WEActionFlags;

// forward declarations

typedef struct WERec *WEPtr, **WEHandle;
typedef struct WEObjectDesc **WEObjectDescHandle;
typedef struct WEOHTableEntry **WEOHTableHandle;
typedef struct WEStream *WEStreamPtr;

typedef struct 
{
	Fixed				top ;
	Fixed				bottom ;
	Fixed				left ;
	Fixed				right ;
} PageMarginRec, *PageMarginRecPtr, **PageMarginRecHandle ;

typedef struct WETextStyle
{
	SInt16				tsFont;				// font family number
	Style				tsFace;				// set of Quickdraw styles
	UInt8				tsFlags;			// flags (FOR INTERNAL USE ONLY)
	SInt16				tsSize;				// font size, in integer points
	RGBColor			tsColor;			// text color
	WEObjectDescHandle	tsObject;			// embedded object reference
	SInt16				tsTSMHiliteStyle;	// hilite style for Text Services Manager underlines
	SInt16				tsVerticalShift;	// vertical shift
	RGBColor			tsBackColor;		// background color
	SInt16				tsTransferMode;		// QuickDraw text transfer mode
//	UInt32				tsMoreStyles;		// additional style bits
	UInt8				tsXFace;			// additional (non-Quickdraw) style bits
	UInt8				tsXFaceMask ;		// bit mask for setting/clearing the above bits
	UInt16				tsUnderlineStyle;	// underline style
	TextEncoding		tsEncoding;			// text encoding
	LocaleRef			tsLanguage;			// language/locale
} WETextStyle;

typedef struct WERunAttributes
{
	SInt16				runHeight;	// style run height (ascent + descent + leading)
	SInt16				runAscent;	// font ascent
	WETextStyle			runStyle;	// text style
} WERunAttributes;

typedef struct WERunInfo
{
	SInt32				runStart;	// byte offset to first character of this style run
	SInt32				runEnd;		// byte offset to first character of next style run
	WERunAttributes		runAttrs;	// run attributes
} WERunInfo;

typedef struct QDEnvironment
{
	GrafPtr				envPort;		// saved port
	PenState			envPen;			// saved pen attributes
	TextStyle			envStyle;		// saved text style
	SInt16				envTxMode;		// saved text mode
} QDEnvironment;

typedef struct WERunArrayEntry
{
	SInt32				runStart;	// offset to first character in style run
	SInt32				styleIndex;	// index into style table
} WERunArrayEntry, **WERunArrayHandle;

typedef struct WEStyleTableEntry
{
	SInt32				refCount;	// reference count
	WERunAttributes		info;		// style information
} WEStyleTableEntry, **WEStyleTableHandle;

typedef struct WETab
{
	Fixed				indent;			//	offset from left margin (in fixed points)
	WEAlignment			alignment;		//	tab alignment (left, center, right or decimal)
	char				fillChar;		//	fill character (default = 0x20, Roman space)
	char				decimal;		//	if alignment = weDecimal, the decimal point
	char				padding;		//	explicit padding
} WETab;

typedef struct WETabPriv				//	only used internally -- use WETabList in conjunction with WESetAttributes/WEGetAttributes
{
	Fixed				indent;			//	offset from left margin (in fixed points)
	WEAlignment			alignment;		//	tab alignment (left, center, right or decimal)
	UInt8				leader;			//	tab leader (character used to fill the blank space before the tab position)
} WETabPriv;

typedef struct WERuler
{
	SInt8			alignment;			//	alignment
	SInt8			direction;			//	primary line direction
	UInt8			topBorderStyle;		//	top border style
	UInt8			bottomBorderStyle;	//	bottom border style
	Fixed			leftIndent;			//	left margin (in fixed points)
	Fixed			rightIndent;		//	right margin (in fixed points)
	Fixed			firstLineIndent;	//	first line indent (in fixed points)
	Fixed			lineSpacing;		//	space between lines (0.0 = normal, 1.0 = double, etc.)
	Fixed			spaceBefore;		//	space before paragraph (in fixed points)
	Fixed			spaceAfter;			//	space after paragraph (in fixed points)
	//WETab			tabs[20];			//	tab array (not implemented yet)
	UInt16			flags;				//	line spacing flags and other paragraph flags
	UInt16			flagsMask;			//	mask for setting the above flags (except line spacing flags)
	ItemCount		tabCount;			//	tab count (0..kMaxTabCount)
	WETabPriv		tabs[kMaxTabCount];	//	tab array
	SInt32			userData;			//	available for client use
} WERuler;

typedef struct WERulerTableEntry
{
	SInt32			refCount;			// reference count
	WERuler			ruler;				// ruler
} WERulerTableEntry, **WERulerTableHandle;

typedef struct WEParaInfo
{
	SInt32			paraStart;
	SInt32			paraEnd;
	WERuler			paraRuler;
} WEParaInfo;

typedef struct WEParaArrayEntry
{
	SInt32			paraStart;			// offset to first character in paragraph run
	SInt32			rulerIndex;			// index into ruler table
} WEParaArrayEntry, **WEParaArrayHandle;


//	'styl' scrap format (used for TextEdit compatibility)

typedef struct TERunAttributes
{
	SInt16						runHeight;
	SInt16						runAscent;
	TextStyle					runTEStyle;
} TERunAttributes;

typedef struct TEStyleScrapElement
{
	SInt32						scrpStartChar;
	TERunAttributes				scrpTEAttrs;
} TEStyleScrapElement;

typedef struct TEStyleScrap
{
	SInt16						scrpNStyles;
	TEStyleScrapElement			scrpStyleTab[ kVariableLengthArray ];
} TEStyleScrap, **TEStyleScrapHandle;

//	private scrap formats (used internally for undo/redo)

typedef struct WEPrivateStyleScrapElement
{
	SInt32						scrpStartChar ;
	WETextStyle					scrpStyle;
} WEPrivateStyleScrapElement;

typedef struct WEPrivateStyleScrap
{
	SInt32						scrpNStyles;
	WEPrivateStyleScrapElement	scrpStyleTab[ kVariableLengthArray ];
} WEPrivateStyleScrap, **WEPrivateStyleScrapHandle;

typedef struct WEPrivateRulerScrapElement
{
	SInt32						scrpStartChar;
	WERuler						scrpRuler;
} WEPrivateRulerScrapElement;

typedef struct WEPrivateRulerScrap
{
	SInt32						scrpNRulers;
	WEPrivateRulerScrapElement	scrpRulerTab[ kVariableLengthArray ];
} WEPrivateRulerScrap, **WEPrivateRulerScrapHandle;

/*	the first parameter to a 'new' embedded object handler is declared as a (Point *) for compatibility */
/*	with older versions of WASTE, but is really a (WEObjectPlacement *) starting from WASTE 2.1a5 */
/*	if the value of the objectBaseline field is set to a nonzero value, WASTE will place the bottom */
/*	of the bounding rectangle of the object below (negative value) or above (positive value) the text baseline */

typedef struct WEObjectPlacement
{
	SInt16			objectHeight;		/* height of embedded object */
	SInt16			objectWidth;		/* width of embedded object */
	SInt16			objectBaseline;		/* baseline (intrinsic vertical shift) of embedded object */
} WEObjectPlacement;

typedef struct WELineRec
{
	SInt32		lineStart;			// byte offset to first character in line
	SInt32		lineOrigin;			// pixel offset from destRect.top
	SInt16		lineAscent;			// bits 0..14: maximum font ascent for this line; high bit set if first line of para
	SInt16		lineSlop;			// extra pixels needed to fill up the line
#if __ZERO_SPACE_INDENTING__
	SInt16		indentLevel;		// autoindent level in our script editor
#endif
	Fixed		lineJustAmount;		// normalized slop value, used for justification
} WELineRec, **WELineArrayHandle;

typedef struct WEAction
{
	struct WEAction **	hNext;			// used to keep a linked list of actions
	WEActionKind		actionKind;		// identifies event that caused this action to be pushed
	WEActionFlags		actionFlags;	// miscellaneous flags
	WEHandle			hOwner;			// handle to associated WE instance
	SInt32				delRangeStart;	// start of range to delete
	SInt32				delRangeLength;	// length of range to delete
	SInt32				insRangeLength;	// length of range to insert
	SInt32				hiliteStart;	// start of range to hilite
	SInt32				hiliteEnd;		// end of range to hilite
	union
	{
		struct
		{
			Handle				hText;		// handle to saved text
			Handle				hStyles;	// handle to saved styles
			Handle				hSoup;		// handle to saved soup
			Handle				hRulers;	// handle to saved paragraph formatting
		}						txt;
		struct
		{
			WEObjectDescHandle	hObject;	// handle to embedded object
			//SInt32				objSize;	// saved size of embedded object
			WEObjectPlacement	objectPlacement;	// saved placement of embedded object
		}						obj;
		struct WEAction **		seq;		// list of grouped actions to be treated as one
	} u;
} WEAction, **WEActionHandle;

typedef FourCharCode WESelector;

// view data types

typedef struct WEView
{
	struct WEView *		next ;						// used to keep a linked list of actions
	WEHandle			owner ;						// ptr to associated WE instance
	GrafPtr				port ;						// graphics port text is drawn into
	LongRect			viewRect;					// view rectangle, all drawing is clipped to this
	LongRect			destRect;					// destination rectangle
	SInt32				leftMargin;					// initial delta between left sides of view rect and dest rect
	RgnHandle			viewRgn ;					// handle to the view region
	RgnHandle			hiliteRgn;					// handle to the hilite region
	RGBColor			hiliteColor;				// paint the hilite region this color
	SInt16				bgHiliteStyle;				// background hilite style (one of weBGHiliteDefault, weBGHiliteNone, etc.)
	SInt32				refCon;						// refcon for client use
} WEView ;

/*	WELineSpacing is used in conjunction with the weTagLineSpacing attribute */
#if __SUPPORTS_WASTE21_LINEHEIGHT__
typedef struct WELineSpacing
{
	WESelector		mode;				/* one of weTagLineSpacingRelative (default), weTagLineSpacingAbsolute or weTagLineSpacingAtLeast */
	Fixed			value;				/* absolute line height or multiplier (0.0 = auto) */
} WELineSpacing;
#endif

// A WESoup record is a static description of an object embedded in the text.
// The 'SOUP' data type is just a collection of WESoup records, each followed
// by the corresponding object data.
// This data type complements the standard TEXT/styl pair.

typedef struct WESoup
{
	SInt32				soupOffset;		// insertion offset for this object
	FlavorType			soupType;		// 4-letter tag identifying object type
	SInt32				soupReserved1;	// reserved for future use; set to zero
	Size				soupDataSize;	// size of object data following this record
	//SInt32				soupSize;		// object height and width, in pixels
	WEObjectPlacement	soupPlacement;	// object placement (height, width and intrinsic baseline)
	SInt16				soupReserved2;	// reserved for future use; set to zero
} WESoup;

// printing data types

typedef SInt32 ** WEPageArrayHandle ;

typedef struct WEPrintRec
{
	WEHandle			hWE ;
	WELineArrayHandle	hLines ;
	WEPageArrayHandle	hPages ;
	SInt32				nLines ;
	SInt32				nPages ;
	Rect				pageRect ;
	SInt16				firstPageOffset;
} WEPrintRec, * WEPrintPtr, ** WEPrintHandle ;

// callback prototypes

typedef pascal Boolean (*WEClickLoopProcPtr)(WEHandle hWE);
typedef pascal void (*WEScrollProcPtr)(WEHandle hWE);
typedef pascal void (*WETSMPreUpdateProcPtr)(WEHandle hWE);
typedef pascal void (*WETSMPostUpdateProcPtr)(WEHandle hWE,
		SInt32 fixLength, SInt32 inputAreaStart, SInt32 inputAreaEnd,
		SInt32 pinRangeStart, SInt32 pinRangeEnd);
typedef pascal SInt32 (*WEHiddenTextProcPtr)(SInt32 inOffset, Boolean inForwardDelete, WEHandle hWE);
typedef pascal OSErr (*WEPreTrackDragProcPtr)(DragReference drag, WEHandle hWE);
typedef pascal OSErr (*WETranslateDragProcPtr)(DragReference drag,
		ItemReference dragItem, FlavorType requestedType, Handle putDataHere,
		SInt32 dropOffset, WEHandle hWE);
typedef pascal OSErr (*WEHiliteDropAreaProcPtr)(DragReference drag,
		Boolean hiliteFlag, WEHandle hWE);
typedef pascal OSErr (*WEFontIDToNameProcPtr)(SInt16 fontID, Str255 fontName);
typedef pascal OSErr (*WEFontNameToIDProcPtr)(ConstStr255Param fontName, SInt16 oldFontID, SInt16 *newFontID);
typedef pascal void (*WEDrawTextProcPtr)(const char * pText, SInt32 textLength, Fixed slop,
		JustStyleCode styleRunPosition, WEHandle hWE);
typedef pascal SInt32 (*WEPixelToCharProcPtr)(const char * pText, SInt32 textLength, Fixed slop,
		Fixed *pixelWidth, WEEdge *edge, JustStyleCode styleRunPosition, Fixed hPos, WEHandle hWE);
typedef pascal SInt16 (*WECharToPixelProcPtr)(const char * pText, SInt32 textLength, Fixed slop,
		SInt32 offset, SInt16 direction, JustStyleCode styleRunPosition, SInt16 hPos, WEHandle hWE);
typedef pascal StyledLineBreakCode (*WELineBreakProcPtr)(const char * pText, SInt32 textLength,
		SInt32 textStart, SInt32 textEnd, Fixed *textWidth, SInt32 *textOffset, WEHandle hWE);
typedef pascal void (*WEWordBreakProcPtr)(const char * pText, SInt16 textLength, SInt16 offset,
		WEEdge edge, OffsetTable breakOffsets, ScriptCode script, WEHandle hWE);
typedef pascal SInt16 (*WECharByteProcPtr)(const char * pText, SInt16 textOffset, ScriptCode script,
		WEHandle hWE);
typedef pascal SInt16 (*WECharTypeProcPtr)(const char * pText, SInt16 textOffset, ScriptCode script, WEHandle hWE);
typedef pascal void (*WEEraseProcPtr)(const Rect *area, WEHandle hWE);
typedef pascal void (*WEFluxProcPtr)(SInt32 offset, SInt32 delta, WEHandle hWE);
typedef pascal void (*WEDrawTSMHiliteProcPtr)(const Rect *segmentRect, SInt16 hiliteStyle, WEHandle hWE);
//typedef pascal OSErr (*WENewObjectProcPtr)(SInt32 *defaultObjectSize,
typedef pascal OSErr (*WENewObjectProcPtr)(WEObjectPlacement *objectPlacement,
		WEObjectDescHandle hObjectDesc);
typedef pascal OSErr (*WEDisposeObjectProcPtr)(WEObjectDescHandle hObjectDesc);
typedef pascal OSErr (*WEDrawObjectProcPtr)(const Rect *destRect,
		WEObjectDescHandle hObjectDesc);
// ¥¥ MDL 2-1-5 ¥¥
typedef pascal Boolean (*WEClickObjectProcPtr)(Point hitPt, EventModifiers modifiers, UInt32 clickTime,
//typedef pascal Boolean (*WEClickObjectProcPtr)(long hitPt, EventModifiers modifiers, UInt32 clickTime,
// ¥¥
		WEObjectDescHandle hObjectDesc);
typedef pascal OSErr (*WEStreamObjectProcPtr)(SInt16 destKind, FlavorType *theType, Handle *putDataHere, WEObjectDescHandle hObjectDesc);
typedef pascal OSErr (*WEHoverObjectProcPtr)(SInt16 mouseAction, Point mouseLoc, RgnHandle mouseRgn, WEObjectDescHandle hObjectDesc);
typedef pascal OSErr (*WEUndoProcPtr)(SInt16 undoEvent, WEAction * action);
typedef pascal void (*WEPrepareViewProcPtr)(WEView * view);
#if __ZERO_SPACE_INDENTING__
typedef pascal OSErr (*WEAutoIndentProcPtr)(SInt32 pinRangeStart, SInt32 pinRangeEnd, WEHandle hWE);
#endif


// UPP proc info

enum
{
	uppWEClickLoopProcInfo = kPascalStackBased
		| RESULT_SIZE(SIZE_CODE(sizeof(Boolean)))
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(WEHandle /*hWE*/))),
	uppWEScrollProcInfo = kPascalStackBased
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(WEHandle /*hWE*/))),
	uppWETSMPreUpdateProcInfo = kPascalStackBased
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(WEHandle /*hWE*/))),
	uppWETSMPostUpdateProcInfo = kPascalStackBased
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(WEHandle /*hWE*/)))
		| STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof(SInt32 /*fixLength*/)))
		| STACK_ROUTINE_PARAMETER(3,SIZE_CODE(sizeof(SInt32 /*inputAreaStart*/)))
		| STACK_ROUTINE_PARAMETER(4,SIZE_CODE(sizeof(SInt32 /*inputAreaEnd*/)))
		| STACK_ROUTINE_PARAMETER(5,SIZE_CODE(sizeof(SInt32 /*pinRangeStart*/)))
		| STACK_ROUTINE_PARAMETER(6,SIZE_CODE(sizeof(SInt32 /*pinRangeEnd*/))),
	uppWEPreTrackDragProcInfo = kPascalStackBased
		| RESULT_SIZE(SIZE_CODE(sizeof(OSErr)))
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(DragReference /*drag*/)))
		| STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof(WEHandle /*hWE*/))),
	uppWETranslateDragProcInfo = kPascalStackBased
		| RESULT_SIZE(SIZE_CODE(sizeof(OSErr)))
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(DragReference /*drag*/)))
		| STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof(ItemReference /*dragItem*/)))
		| STACK_ROUTINE_PARAMETER(3,SIZE_CODE(sizeof(FlavorType /*requestedType*/)))
		| STACK_ROUTINE_PARAMETER(4,SIZE_CODE(sizeof(Handle /*putDataHere*/)))
		| STACK_ROUTINE_PARAMETER(5,SIZE_CODE(sizeof(SInt32 /*dropOffset*/)))
		| STACK_ROUTINE_PARAMETER(6,SIZE_CODE(sizeof(WEHandle /*hWE*/))),
	uppWEHiliteDropAreaProcInfo = kPascalStackBased
		| RESULT_SIZE(SIZE_CODE(sizeof(OSErr)))
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(DragReference /*drag*/)))
		| STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof(Boolean /*hiliteFlag*/)))
		| STACK_ROUTINE_PARAMETER(3,SIZE_CODE(sizeof(WEHandle /*hWE*/))),
	uppWEFontIDToNameProcInfo = kPascalStackBased
		| RESULT_SIZE(SIZE_CODE(sizeof(OSErr)))
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(SInt16 /*fontID*/)))
		| STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof(StringPtr /*fontName*/))),
	uppWEFontNameToIDProcInfo = kPascalStackBased
		| RESULT_SIZE(SIZE_CODE(sizeof(OSErr)))
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(ConstStr255Param /*fontName*/)))
		| STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof(SInt16 /*oldFontID*/)))
		| STACK_ROUTINE_PARAMETER(3,SIZE_CODE(sizeof(SInt16 * /*newFontID*/))),
	uppWEDrawTextProcInfo = kPascalStackBased
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(const char * /*pText*/)))
		| STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof(SInt32 /*textLength*/)))
		| STACK_ROUTINE_PARAMETER(3,SIZE_CODE(sizeof(Fixed /*slop*/)))
		| STACK_ROUTINE_PARAMETER(4,SIZE_CODE(sizeof(JustStyleCode /*styleRunPosition*/)))
		| STACK_ROUTINE_PARAMETER(5,SIZE_CODE(sizeof(WEHandle /*hWE*/))),
	uppWEPixelToCharProcInfo = kPascalStackBased
		| RESULT_SIZE(SIZE_CODE(sizeof(SInt32)))
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(const char * /*pText*/)))
		| STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof(SInt32 /*textLength*/)))
		| STACK_ROUTINE_PARAMETER(3,SIZE_CODE(sizeof(Fixed /*slop*/)))
		| STACK_ROUTINE_PARAMETER(4,SIZE_CODE(sizeof(Fixed * /*pixelWidth*/)))
		| STACK_ROUTINE_PARAMETER(5,SIZE_CODE(sizeof(WEEdge * /*edge*/)))
		| STACK_ROUTINE_PARAMETER(6,SIZE_CODE(sizeof(JustStyleCode /*styleRunPosition*/)))
		| STACK_ROUTINE_PARAMETER(7,SIZE_CODE(sizeof(Fixed /*hPos*/)))
		| STACK_ROUTINE_PARAMETER(8,SIZE_CODE(sizeof(WEHandle /*hWE*/))),
	uppWECharToPixelProcInfo = kPascalStackBased
		| RESULT_SIZE(SIZE_CODE(sizeof(SInt16)))
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(const char * /*pText*/)))
		| STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof(SInt32 /*textLength*/)))
		| STACK_ROUTINE_PARAMETER(3,SIZE_CODE(sizeof(Fixed /*slop*/)))
		| STACK_ROUTINE_PARAMETER(4,SIZE_CODE(sizeof(SInt32 /*offset*/)))
		| STACK_ROUTINE_PARAMETER(5,SIZE_CODE(sizeof(SInt16 /*direction*/)))
		| STACK_ROUTINE_PARAMETER(6,SIZE_CODE(sizeof(JustStyleCode /*styleRunPosition*/)))
		| STACK_ROUTINE_PARAMETER(7,SIZE_CODE(sizeof(SInt16 /*hPos*/)))
		| STACK_ROUTINE_PARAMETER(8,SIZE_CODE(sizeof(WEHandle /*hWE*/))),
	uppWELineBreakProcInfo = kPascalStackBased
		| RESULT_SIZE(SIZE_CODE(sizeof(StyledLineBreakCode )))
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(const char * /*pText*/)))
		| STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof(SInt32 /*textLength*/)))
		| STACK_ROUTINE_PARAMETER(3,SIZE_CODE(sizeof(SInt32 /*textStart*/)))
		| STACK_ROUTINE_PARAMETER(4,SIZE_CODE(sizeof(SInt32 /*textEnd*/)))
		| STACK_ROUTINE_PARAMETER(5,SIZE_CODE(sizeof(Fixed * /*textWidth*/)))
		| STACK_ROUTINE_PARAMETER(6,SIZE_CODE(sizeof(SInt32 * /*textOffset*/)))
		| STACK_ROUTINE_PARAMETER(7,SIZE_CODE(sizeof(WEHandle /*hWE*/))),
	uppWEWordBreakProcInfo = kPascalStackBased
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(const char * /*pText*/)))
		| STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof(SInt16 /*textLength*/)))
		| STACK_ROUTINE_PARAMETER(3,SIZE_CODE(sizeof(SInt16 /*offset*/)))
		| STACK_ROUTINE_PARAMETER(4,SIZE_CODE(sizeof(WEEdge /*edge*/)))
		| STACK_ROUTINE_PARAMETER(5,SIZE_CODE(sizeof(OffsetTable * /*breakOffsets*/)))
		| STACK_ROUTINE_PARAMETER(6,SIZE_CODE(sizeof(ScriptCode /*script*/)))
		| STACK_ROUTINE_PARAMETER(7,SIZE_CODE(sizeof(WEHandle /*hWE*/))),
	uppWECharByteProcInfo = kPascalStackBased
		| RESULT_SIZE(SIZE_CODE(sizeof(SInt16 )))
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(const char * /*pText*/)))
		| STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof(SInt16 /*textOffset*/)))
		| STACK_ROUTINE_PARAMETER(3,SIZE_CODE(sizeof(ScriptCode /*script*/)))
		| STACK_ROUTINE_PARAMETER(4,SIZE_CODE(sizeof(WEHandle /*hWE*/))),
	uppWECharTypeProcInfo = kPascalStackBased
		| RESULT_SIZE(SIZE_CODE(sizeof(SInt16 )))
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(const char * /*pText*/)))
		| STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof(SInt16 /*textOffset*/)))
		| STACK_ROUTINE_PARAMETER(3,SIZE_CODE(sizeof(ScriptCode /*script*/)))
		| STACK_ROUTINE_PARAMETER(4,SIZE_CODE(sizeof(WEHandle /*hWE*/))),
	uppWEEraseProcInfo = kPascalStackBased
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(const Rect * /*area*/)))
		| STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof(WEHandle /*hWE*/))),
	uppWEFluxProcInfo = kPascalStackBased
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(SInt32 /*offset*/)))
		| STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof(SInt32 /*delta*/)))
		| STACK_ROUTINE_PARAMETER(3,SIZE_CODE(sizeof(WEHandle /*hWE*/))),
	uppWEDrawTSMHiliteProcInfo = kPascalStackBased
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(const Rect * /*segmentRect*/)))
		| STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof(SInt16 /*hiliteStyle*/)))
		| STACK_ROUTINE_PARAMETER(3,SIZE_CODE(sizeof(WEHandle /*hWE*/))),
	uppWENewObjectProcInfo = kPascalStackBased
		| RESULT_SIZE(SIZE_CODE(sizeof(OSErr)))
//		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(SInt32 * /*defaultObjectSize*/)))
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(WEObjectPlacement * /*objectPlacement*/)))
		| STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof(WEObjectDescHandle /*hObjectDesc*/))),
	uppWEDisposeObjectProcInfo = kPascalStackBased
		| RESULT_SIZE(SIZE_CODE(sizeof(OSErr)))
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(WEObjectDescHandle /*hObjectDesc*/))),
	uppWEDrawObjectProcInfo = kPascalStackBased
		| RESULT_SIZE(SIZE_CODE(sizeof(OSErr)))
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(const Rect * /*destRect*/)))
		| STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof(WEObjectDescHandle /*hObjectDesc*/))),
	uppWEClickObjectProcInfo = kPascalStackBased
		| RESULT_SIZE(SIZE_CODE(sizeof(Boolean)))
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(Point /*hitPt*/)))
		| STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof(SInt16 /*modifiers*/)))
		| STACK_ROUTINE_PARAMETER(3,SIZE_CODE(sizeof(UInt32 /*clickTime*/)))
		| STACK_ROUTINE_PARAMETER(4,SIZE_CODE(sizeof(WEObjectDescHandle /*hObjectDesc*/))),
	uppWEStreamObjectProcInfo = kPascalStackBased
		| RESULT_SIZE(SIZE_CODE(sizeof(OSErr)))
		| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(SInt16 /*destKind*/)))
		| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(FlavorType * /*theType*/)))
		| STACK_ROUTINE_PARAMETER(3, SIZE_CODE(sizeof(Handle */*putDataHere*/)))
		| STACK_ROUTINE_PARAMETER(4, SIZE_CODE(sizeof(WEObjectDescHandle /*hObjectDesc*/))),
	uppWEHoverObjectProcInfo = kPascalStackBased
		| RESULT_SIZE(SIZE_CODE(sizeof(OSErr)))
		| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(SInt16 /*mouseAction*/)))
		| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(Point /*mouseLoc*/)))
		| STACK_ROUTINE_PARAMETER(3, SIZE_CODE(sizeof(RgnHandle /*mouseRgn*/)))
		| STACK_ROUTINE_PARAMETER(4, SIZE_CODE(sizeof(WEObjectDescHandle /*hObjectDesc*/))),
	uppWEAutoIndentProcInfo = kPascalStackBased
		| STACK_ROUTINE_PARAMETER(1,SIZE_CODE(sizeof(SInt32 /*textStart*/)))
		| STACK_ROUTINE_PARAMETER(2,SIZE_CODE(sizeof(SInt32 /*textEnd*/)))
		| STACK_ROUTINE_PARAMETER(3,SIZE_CODE(sizeof(WEHandle /*hWE*/)))
};


/*	UPPs, NewÅProc macros & CallÅProc macros */

/*
	NOTE:
    For compatibility with the Pascal version, CallÅProc macros take the form:

		CallFooProc(..., userRoutine)

	instead of:

		CallFooProc(userRoutine, ...)

*/

#if WASTE_USE_UPPS

typedef UniversalProcPtr WEClickLoopUPP;
typedef UniversalProcPtr WEScrollUPP;
typedef UniversalProcPtr WETSMPreUpdateUPP;
typedef UniversalProcPtr WETSMPostUpdateUPP;
typedef UniversalProcPtr WEHiddenTextUPP;
typedef UniversalProcPtr WEPreTrackDragUPP;
typedef UniversalProcPtr WETranslateDragUPP;
typedef UniversalProcPtr WEHiliteDropAreaUPP;
typedef UniversalProcPtr WEFontIDToNameUPP;
typedef UniversalProcPtr WEFontNameToIDUPP;
typedef UniversalProcPtr WEDrawTextUPP;
typedef UniversalProcPtr WEPixelToCharUPP;
typedef UniversalProcPtr WECharToPixelUPP;
typedef UniversalProcPtr WELineBreakUPP;
typedef UniversalProcPtr WEWordBreakUPP;
typedef UniversalProcPtr WECharByteUPP;
typedef UniversalProcPtr WECharTypeUPP;
typedef UniversalProcPtr WEEraseUPP;
typedef UniversalProcPtr WEFluxUPP;
typedef UniversalProcPtr WEDrawTSMHiliteUPP;
typedef UniversalProcPtr WENewObjectUPP;
typedef UniversalProcPtr WEDisposeObjectUPP;
typedef UniversalProcPtr WEDrawObjectUPP;
typedef UniversalProcPtr WEClickObjectUPP;
typedef UniversalProcPtr WEStreamObjectUPP;
typedef UniversalProcPtr WEHoverObjectUPP;
typedef UniversalProcPtr WEUndoUPP;
#if __ZERO_SPACE_INDENTING__
typedef UniversalProcPtr WEAutoIndentUPP;
#endif

#define NewWEClickLoopProc(userRoutine) \
	(WEClickLoopUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWEClickLoopProcInfo, GetCurrentArchitecture())
#define NewWEScrollProc(userRoutine) \
	(WEScrollUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWEScrollProcInfo, GetCurrentArchitecture())
#define NewWETSMPreUpdateProc(userRoutine) \
	(WETSMPreUpdateUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWETSMPreUpdateProcInfo, GetCurrentArchitecture())
#define NewWETSMPostUpdateProc(userRoutine) \
	(WETSMPostUpdateUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWETSMPostUpdateProcInfo, GetCurrentArchitecture())
#define NewWEHiddenTextProc(userRoutine) \
	(WEHiddenTextUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWEHiddenTextProcInfo, GetCurrentArchitecture())
#define NewWEPreTrackDragProc(userRoutine) \
	(WEPreTrackDragUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWEPreTrackDragProcInfo, GetCurrentArchitecture())
#define NewWETranslateDragProc(userRoutine) \
	(WETranslateDragUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWETranslateDragProcInfo, GetCurrentArchitecture())
#define NewWEHiliteDropAreaProc(userRoutine) \
	(WEHiliteDropAreaUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWEHiliteDropAreaProcInfo, GetCurrentArchitecture())
#define NewWEFontIDToNameProc(userRoutine) \
	(WEFontIDToNameUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWEFontIDToNameProcInfo, GetCurrentArchitecture())
#define NewWEFontNameToIDProc(userRoutine) \
	(WEFontNameToIDUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWEFontNameToIDProcInfo, GetCurrentArchitecture())
#define NewWEDrawTextProc(userRoutine) \
	(WEDrawTextUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWEDrawTextProcInfo, GetCurrentArchitecture())
#define NewWEPixelToCharProc(userRoutine) \
	(WEPixelToCharUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWEPixelToCharProcInfo, GetCurrentArchitecture())
#define NewWECharToPixelProc(userRoutine) \
	(WECharToPixelUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWECharToPixelProcInfo, GetCurrentArchitecture())
#define NewWELineBreakProc(userRoutine) \
	(WELineBreakUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWELineBreakProcInfo, GetCurrentArchitecture())
#define NewWEWordBreakProc(userRoutine) \
	(WEWordBreakUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWEWordBreakProcInfo, GetCurrentArchitecture())
#define NewWECharByteProc(userRoutine) \
	(WECharByteUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWECharByteProcInfo, GetCurrentArchitecture())
#define NewWECharTypeProc(userRoutine) \
	(WECharTypeUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWECharTypeProcInfo, GetCurrentArchitecture())
#define NewWEEraseProc(userRoutine) \
	(WEEraseUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWEEraseProcInfo, GetCurrentArchitecture())
#define NewWEFluxProc(userRoutine) \
	(WEFluxUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWEFluxProcInfo, GetCurrentArchitecture())
#define NewWEDrawTSMHiliteProc(userRoutine) \
	(WEDrawTSMHiliteUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWEDrawTSMHiliteProcInfo, GetCurrentArchitecture())
#define NewWENewObjectProc(userRoutine) \
	(WENewObjectUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWENewObjectProcInfo, GetCurrentArchitecture())
#define NewWEDisposeObjectProc(userRoutine) \
	(WEDisposeObjectUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWEDisposeObjectProcInfo, GetCurrentArchitecture())
#define NewWEDrawObjectProc(userRoutine) \
	(WEDrawObjectUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWEDrawObjectProcInfo, GetCurrentArchitecture())
#define NewWEClickObjectProc(userRoutine) \
	(WEClickObjectUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWEClickObjectProcInfo, GetCurrentArchitecture())
#define NewWEStreamObjectProc(userRoutine) \
	(WEStreamObjectUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWEStreamObjectProcInfo, GetCurrentArchitecture())
#define NewWEHoverObjectProc(userRoutine) \
	(WEHoverObjectUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWEHoverObjectProcInfo, GetCurrentArchitecture())
#define NewWEUndoProc(userRoutine) \
	(WEUndoUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWEUndoProcInfo, GetCurrentArchitecture())
#define NewWEPrepareViewProc(userRoutine) \
	(WEPrepareViewUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWEPrepareViewProcInfo, GetCurrentArchitecture())
#if __ZERO_SPACE_INDENTING__
#define NewWEAutoIndentProc(userRoutine) \
	(WEAutoIndentUPP) NewRoutineDescriptor((ProcPtr) (userRoutine), uppWEAutoIndentProcInfo, GetCurrentArchitecture())
#endif

#define CallWEClickLoopProc(hWE, userRoutine) \
	CallUniversalProc((userRoutine), uppWEClickLoopProcInfo, (hWE))
#define CallWEScrollProc(hWE, userRoutine) \
	CallUniversalProc((userRoutine), uppWEScrollProcInfo, (hWE))
#define CallWETSMPreUpdateProc(hWE, userRoutine) \
	CallUniversalProc((userRoutine), uppWETSMPreUpdateProcInfo, (hWE))
#define CallWETSMPostUpdateProc(hWE, fixLength, inputAreaStart, inputAreaEnd, pinRangeStart, pinRangeEnd, userRoutine) \
	CallUniversalProc((userRoutine), uppWETSMPostUpdateProcInfo, (hWE), (fixLength), (inputAreaStart), (inputAreaEnd), (pinRangeStart), (pinRangeEnd))
#define CallWEPreTrackDragProc(drag, hWE, userRoutine) \
	CallUniversalProc((userRoutine), uppWEPreTrackDragProcInfo, (drag), (hWE))
#define CallWETranslateDragProc(drag, dragItem, requestedType, putDataHere, dropOffset, hWE, userRoutine) \
	CallUniversalProc((userRoutine), uppWETranslateDragProcInfo, (drag), (dragItem), (requestedType), (putDataHere), (dropOffset), (hWE))
#define CallWEHiliteDropAreaProc(drag, hiliteFlag, hWE, userRoutine) \
	CallUniversalProc((userRoutine), uppWEHiliteDropAreaProcInfo, (drag), (hiliteFlag), (hWE))
#define CallWEFontIDToNameProc(fontID, fontName, userRoutine) \
	CallUniversalProc((userRoutine), uppWEFontIDToNameProcInfo, (fontID), (fontName))
#define CallWEFontNameToIDProc(fontName, oldFontID, fontID, userRoutine) \
	CallUniversalProc((userRoutine), uppWEFontNameToIDProcInfo, (fontName), (oldFontID), (fontID))
#define CallWEDrawTextProc(pText, textLength, slop, styleRunPosition, hWE, userRoutine) \
	CallUniversalProc((userRoutine), uppWEDrawTextProcInfo, (pText), (textLength), (slop), (styleRunPosition), (hWE))
#define CallWEDrawTSMHiliteProc(segmentRect, hiliteStyle, hWE, userRoutine) \
	CallUniversalProc((userRoutine), uppWEEraseProcInfo, (segmentRect), (hiliteStyle), (hWE))
#define CallWEPixelToCharProc(pText, textLength, slop, pixelWidth, edge, styleRunPosition, hPos, hWE, userRoutine) \
	CallUniversalProc((userRoutine), uppWEPixelToCharProcInfo, (pText), (textLength), (slop), (pixelWidth), (edge), (styleRunPosition), (hPos), (hWE))
#define CallWECharToPixelProc(pText, textLength, slop, offset, direction, styleRunPosition, hPos, hWE, userRoutine) \
	CallUniversalProc((userRoutine), uppWECharToPixelProcInfo, (pText), (textLength), (slop), (offset), (direction), (styleRunPosition), (hPos), (hWE))
#define CallWELineBreakProc(pText, textLength, textStart, textEnd, textWidth, textOffset, hWE, userRoutine) \
	CallUniversalProc((userRoutine), uppWELineBreakProcInfo, (pText), (textLength), (textStart), (textEnd), (textWidth), (textOffset), (hWE))
#define CallWEWordBreakProc(pText, textLength, offset, edge, breakOffsets, script, hWE, userRoutine) \
	CallUniversalProc((userRoutine), uppWEWordBreakProcInfo, (pText), (textLength), (offset), (edge), (breakOffsets), (script), (hWE))
#define CallWECharByteProc(pText, textOffset, script, hWE, userRoutine) \
	CallUniversalProc((userRoutine), uppWECharByteProcInfo, (pText), (textOffset), (script), (hWE))
#define CallWECharTypeProc(pText, textOffset, script, hWE, userRoutine) \
	CallUniversalProc((userRoutine), uppWECharTypeProcInfo, (pText), (textOffset), (script), (hWE))
#define CallWEEraseProc(area, hWE, userRoutine) \
	CallUniversalProc((userRoutine), uppWEEraseProcInfo, (area), (hWE))
#define CallWEFluxProc(offset, delta, hWE, userRoutine) \
	CallUniversalProc((userRoutine), uppWEFluxProcInfo, (offset), (delta), (hWE))
#define CallWENewObjectProc(objectPlacement, hObjectDesc, userRoutine) \
	CallUniversalProc((userRoutine), uppWENewObjectProcInfo, (objectPlacement), (hObjectDesc))
#define CallWEDisposeObjectProc(hObjectDesc, userRoutine) \
	CallUniversalProc((userRoutine), uppWEDisposeObjectProcInfo, (hObjectDesc))
#define CallWEDrawObjectProc(destRect, hObjectDesc, userRoutine) \
	CallUniversalProc((userRoutine), uppWEDrawObjectProcInfo, (destRect), (hObjectDesc))
#define CallWEClickObjectProc(hitPt, modifiers, clickTime, hObjectDesc, userRoutine) \
	CallUniversalProc((userRoutine), uppWEClickObjectProcInfo, (hitPt), (modifiers), (clickTime), (hObjectDesc))
#define CallWEStreamObjectProc(destKind, theType, putDataHere, hObjectDesc, userRoutine) \
	CallUniversalProc((userRoutine), uppWEStreamObjectProcInfo, (destKind), (theType), (putDataHere), (hObjectDesc))
#define CallWEHoverObjectProc(mouseAction, mouseLoc, mouseRgn, hObjectDesc, userRoutine) \
	CallUniversalProc((userRoutine), uppWEHoverObjectProcInfo, (mouseAction), (mouseLoc), (mouseRgn), (hObjectDesc))
#if __ZERO_SPACE_INDENTING__
#define CallWEAutoIndentProc(pinRangeStart, pinRangeEnd, hWE, userRoutine) \
	CallUniversalProc((userRoutine), uppWEAutoIndentProcInfo, (pinRangeStart), (pinRangeEnd), (hWE))
#endif

#else

typedef WEClickLoopProcPtr WEClickLoopUPP;
typedef WEScrollProcPtr WEScrollUPP;
typedef WETSMPreUpdateProcPtr WETSMPreUpdateUPP;
typedef WETSMPostUpdateProcPtr WETSMPostUpdateUPP;
typedef WEHiddenTextProcPtr	WEHiddenTextUPP;
typedef WEPreTrackDragProcPtr WEPreTrackDragUPP;
typedef WETranslateDragProcPtr WETranslateDragUPP;
typedef WEHiliteDropAreaProcPtr WEHiliteDropAreaUPP;
typedef WEFontIDToNameProcPtr WEFontIDToNameUPP;
typedef WEFontNameToIDProcPtr WEFontNameToIDUPP;
typedef WEDrawTextProcPtr WEDrawTextUPP;
typedef WEPixelToCharProcPtr WEPixelToCharUPP;
typedef WECharToPixelProcPtr WECharToPixelUPP;
typedef WELineBreakProcPtr WELineBreakUPP;
typedef WEWordBreakProcPtr WEWordBreakUPP;
typedef WECharByteProcPtr WECharByteUPP;
typedef WECharTypeProcPtr WECharTypeUPP;
typedef WEEraseProcPtr WEEraseUPP;
typedef WEFluxProcPtr WEFluxUPP;
typedef WEDrawTSMHiliteProcPtr WEDrawTSMHiliteUPP;
typedef WENewObjectProcPtr WENewObjectUPP;
typedef WEDisposeObjectProcPtr WEDisposeObjectUPP;
typedef WEDrawObjectProcPtr WEDrawObjectUPP;
typedef WEClickObjectProcPtr WEClickObjectUPP;
typedef WEStreamObjectProcPtr WEStreamObjectUPP;
typedef WEHoverObjectProcPtr WEHoverObjectUPP;
typedef WEUndoProcPtr				WEUndoUPP;
typedef WEPrepareViewProcPtr		WEPrepareViewUPP;
#if __ZERO_SPACE_INDENTING__
typedef WEAutoIndentProcPtr WEAutoIndentUPP;
#endif

#define NewWEClickLoopProc(userRoutine) ((WEClickLoopUPP) (userRoutine))
#define NewWEScrollProc(userRoutine) ((WEScrollUPP) (userRoutine))
#define NewWETSMPreUpdateProc(userRoutine) ((WETSMPreUpdateUPP) (userRoutine))
#define NewWETSMPostUpdateProc(userRoutine) ((WETSMPostUpdateUPP) (userRoutine))
#define NewWEHiddenTextProc(userRoutine) ((WEHiddenTextUPP) (userRoutine))
#define NewWEPreTrackDragProc(userRoutine) ((WEPreTrackDragUPP) (userRoutine))
#define NewWETranslateDragProc(userRoutine) ((WETranslateDragUPP) (userRoutine))
#define NewWEHiliteDropAreaProc(userRoutine) ((WEHiliteDropAreaUPP) (userRoutine))
#define NewWEFontIDToNameProc(userRoutine) ((WEFontIDToNameUPP) (userRoutine))
#define NewWEFontNameToIDProc(userRoutine) ((WEFontNameToIDUPP) (userRoutine))
#define NewWEDrawTextProc(userRoutine) ((WEDrawTextUPP) (userRoutine))
#define NewWEPixelToCharProc(userRoutine) ((WEPixelToCharUPP) (userRoutine))
#define NewWECharToPixelProc(userRoutine) ((WECharToPixelUPP) (userRoutine))
#define NewWELineBreakProc(userRoutine) ((WELineBreakUPP) (userRoutine))
#define NewWEWordBreakProc(userRoutine) ((WEWordBreakUPP) (userRoutine))
#define NewWECharByteProc(userRoutine) ((WECharByteUPP) (userRoutine))
#define NewWECharTypeProc(userRoutine) ((WECharTypeUPP) (userRoutine))
#define NewWEEraseProc(userRoutine) ((WEEraseUPP) (userRoutine))
#define NewWEFluxProc(userRoutine) ((WEFluxUPP) (userRoutine))
#define NewWEDrawTSMHiliteProc(userRoutine) ((WEDrawTSMHiliteUPP) (userRoutine))
#define NewWENewObjectProc(userRoutine) ((WENewObjectUPP) (userRoutine))
#define NewWEDisposeObjectProc(userRoutine) ((WEDisposeObjectUPP) (userRoutine))
#define NewWEDrawObjectProc(userRoutine) ((WEDrawObjectUPP) (userRoutine))
#define NewWEClickObjectProc(userRoutine) ((WEClickObjectUPP) (userRoutine))
#define NewWEStreamObjectProc(userRoutine) ((WEStreamObjectUPP) (userRoutine))
#define NewWEHoverObjectProc(userRoutine) ((WEHoverObjectUPP) (userRoutine))
#define NewWEUndoProc(userRoutine)				((WEUndoUPP) (userRoutine))
#define NewWEPrepareViewProc(userRoutine)		((WEPrepareViewUPP) (userRoutine))
#if __ZERO_SPACE_INDENTING__
#define NewWEAutoIndentProc(userRoutine) ((WEAutoIndentUPP) (userRoutine))
#endif

#define CallWEClickLoopProc(hWE, userRoutine) \
	(*(userRoutine))((hWE))
#define CallWEScrollProc(hWE, userRoutine) \
	(*(userRoutine))((hWE))
#define CallWETSMPreUpdateProc(hWE, userRoutine) \
	(*(userRoutine))((hWE))
#define CallWETSMPostUpdateProc(hWE, fixLength, inputAreaStart, inputAreaEnd, pinRangeStart, pinRangeEnd, userRoutine) \
	(*(userRoutine))((hWE), (fixLength), (inputAreaStart), (inputAreaEnd), (pinRangeStart), (pinRangeEnd))
#define CallWEPreTrackDragProc(drag, hWE, userRoutine) \
	(*(userRoutine))((drag), (hWE))
#define CallWETranslateDragProc(drag, dragItem, requestedType, putDataHere, dropOffset, hWE, userRoutine) \
	(*(userRoutine))((drag), (dragItem), (requestedType), (putDataHere), (dropOffset), (hWE))
#define CallWEHiliteDropAreaProc(drag, hiliteFlag, hWE, userRoutine) \
	(*(userRoutine))((drag), (hiliteFlag), (hWE))
#define CallWEFontIDToNameProc(fontID, fontName, userRoutine) \
	(*(userRoutine))((fontID), (fontName))
#define CallWEFontNameToIDProc(fontName, oldFontID, fontID, userRoutine) \
	(*(userRoutine))((fontName), (oldFontID), (fontID))
#define CallWEDrawTextProc(pText, textLength, slop, styleRunPosition, hWE, userRoutine) \
	(*(userRoutine))((pText), (textLength), (slop), (styleRunPosition), (hWE))
#define CallWEPixelToCharProc(pText, textLength, slop, pixelWidth, edge, styleRunPosition, hPos, hWE, userRoutine) \
	(*(userRoutine))((pText), (textLength), (slop), (pixelWidth), (edge), (styleRunPosition), (hPos), (hWE))
#define CallWECharToPixelProc(pText, textLength, slop, offset, direction, styleRunPosition, hPos, hWE, userRoutine) \
	(*(userRoutine))((pText), (textLength), (slop), (offset), (direction), (styleRunPosition), (hPos), (hWE))
#define CallWELineBreakProc(pText, textLength, textStart, textEnd, textWidth, textOffset, hWE, userRoutine) \
	(*(userRoutine))((pText), (textLength), (textStart), (textEnd), (textWidth), (textOffset), (hWE))
#define CallWEWordBreakProc(pText, textLength, offset, edge, breakOffsets, script, hWE, userRoutine) \
	(*(userRoutine))((pText), (textLength), (offset), (edge), (breakOffsets), (script), (hWE))
#define CallWECharByteProc(pText, textOffset, script, hWE, userRoutine) \
	(*(userRoutine))((pText), (textOffset), (script), (hWE))
#define CallWECharTypeProc(pText, textOffset, script, hWE, userRoutine) \
	(*(userRoutine))((pText), (textOffset), (script), (hWE))
#define CallWEEraseProc(area, hWE, userRoutine) \
	(*(userRoutine))((area), (hWE))
#define CallWEFluxProc(offset, delta, hWE, userRoutine) \
	(*(userRoutine))((offset), (delta), (hWE))
#define CallWEDrawTSMHiliteProc(segmentRect, hiliteStyle, hWE, userRoutine) \
	(*(userRoutine))((segmentRect), (hiliteStyle), (hWE))
#define CallWENewObjectProc(objectPlacement, hObjectDesc, userRoutine) \
	(*(userRoutine))((objectPlacement), (hObjectDesc))
#define CallWEDisposeObjectProc(hObjectDesc, userRoutine) \
	(*(userRoutine))((hObjectDesc))
#define CallWEDrawObjectProc(destRect, hObjectDesc, userRoutine) \
	(*(userRoutine))((destRect), (hObjectDesc))
#define CallWEClickObjectProc(hitPt, modifiers, clickTime, hObjectDesc, userRoutine) \
	(*(userRoutine))((hitPt), (modifiers), (clickTime), (hObjectDesc))
#define CallWEStreamObjectProc(destKind, theType, putDataHere, hObjectDesc, userRoutine) \
	(*(userRoutine))((destKind), (theType), (putDataHere), (hObjectDesc))
#define CallWEHoverObjectProc(mouseAction, mouseLoc, mouseRgn, hObjectDesc, userRoutine) \
	(*(userRoutine))((mouseAction), (mouseLoc), (mouseRgn), (hObjectDesc))
#if __ZERO_SPACE_INDENTING__
#define CallWEAutoIndentProc(pinRangeStart, pinRangeEnd, hWE, userRoutine) \
	(*(userRoutine))((pinRangeStart), (pinRangeEnd), (hWE))
#endif

#endif

typedef Boolean (*WESegmentLoopProcPtr)
	(
		WELineRec *				pLine,
		const WERunAttributes *	pAttrs,
		const WERuler *			pRuler,
		const char *			pSegment,
		SInt32					segmentStart,
		SInt32					segmentLength,
		JustStyleCode			styleRunPosition,
		WEHandle				hWE,
		void *					callbackData
	);



typedef struct 
{
//	WindowRef					window ;					/* the window */
//	ControlRef					rootControl ;				/* its root control */
//	ControlRef					scrollBars [ 2 ] ;			/* its scroll bars */
	WEHandle	 				text ;						/* its WASTE instance */
	OSType						fileFormat ;				/* format of associated file ('TEXT', 'utxt' or 'RTF ') */
//	AliasHandle					fileAlias ;					/* alias to associated file */
//	UInt32						cleanModCount ;				/* WASTE modification count at the time the document was last saved */
	PMPrintSession				printSession ;				/* current print session */
	PMPageFormat				pageFormat ;				/* page format (only valid during printing operations) */
	PMPrintSettings				printSettings ;				/* print settings (only valid during printing operations) */
#if 0
	EventHandlerUPP				windowEventHandler ;		/* UPP to handler for windows event */
	EventHandlerRef				windowEventHandlerRef ;		/* EventHandlerRef to above */
	EventHandlerUPP				menuEventHandler ;			/* UPP to handler for menu events */
	EventHandlerRef				menuEventHandlerRef [ 5 ] ;	/* EventHandlerRef's to above */
	EventHandlerUPP				windowCommandHandler ;		/* UPP to handler for HI commands targeted to windows */
	EventHandlerRef				windowCommandHandlerRef ;	/* EventHandlerRef to above */
	EventHandlerUPP				windowTextHandler ;			/* UPP to handler for keyboard events */
	EventHandlerRef				windowTextHandlerRef ;		/* EventHandlerRef to above */
	EventHandlerUPP				mouseWheelHandler ;			/* UPP to handler for mouse wheel events */
	EventHandlerRef				mouseWheelHandlerRef ;		/* EventHandlerRef to above */
	EventHandlerUPP				servicesHandler ;			/* UPP to handler for Mac OS X Services */
	EventHandlerRef				servicesHandlerRef ;		/* EventHandlerRef to above */
	WEScrollUPP					textScroller ;				/* UPP to WASTE scroll callback */
	ControlActionUPP			barScroller ;				/* UPP to scrollbar action callback */
	DragTrackingHandlerUPP		dragTracker ;				/* UPP to drag tracking handler */
	DragReceiveHandlerUPP		dragReceiver ;				/* UPP to drag receive handler */
#endif
} Document;

typedef struct WEPrintOptions
{
	Rect			pageRect;			/* destination rectangle for printing */
	SInt16			firstPageOffset;	/* pixel height of area to be left blank at top of first page */
	char			reserved[54];		/* reserved for future use: set to zero! */
} WEPrintOptions;

/*	WETab describes a single tab stop in a paragraph */

#if 0
typedef struct WETab
{
	Fixed			tabIndent;			/* indent from the left side of the destination rectangle */
	WESelector		tabAlignment;		/* alignment (left, center, right or decimal); only left currently supported */
	WESelector		tabLeader;			/* leader */
} WETab;
#endif

/*	WETabList describes the array of tabs associated with a paragraph */

typedef struct WETabList
{
	ItemCount		tabCount;			/* actual number of valid tabs in this structure (0 to kMaxTabCount) */
	WETab			tabArray[kMaxTabCount];
} WETabList;

typedef struct OpaqueWEPrintSession *			WEPrintSession;
typedef struct OpaqueWEActionReference *		WEActionReference;


typedef struct WEFieldDescriptor
{
	UInt16				fOffset;
	UInt16				fLength;
} WEFieldDescriptor;

typedef struct WELookupTable
{
	WESelector			selector;
	WEFieldDescriptor	desc;
} WELookupTable;

typedef struct WEAttributeDesc
{
	WESelector			attrTag ;		//	four-letter selector code
	UInt8				attrSize ;		//	size of corresponding attribute values
	UInt8				attrClass ;		//	0 for character-level attributes, 1 for paragraph-level attributes
	UInt16				attrOffset ;	//	field offset from start of style/ruler
} WEAttributeDesc ;

typedef struct WEPasteLookupTable
{
	FlavorType		flavorType ;
	SInt16			nextItemOnSuccess ;
	SInt16			nextItemOnFailure ;
} WEPasteLookupTable ;

typedef struct WEUserInfoEntry
{
	WESelector			tag;
	SInt32				info;
} WEUserInfoEntry;

#if WASTE_OBJECTS

typedef struct WEOHTableEntry
{
	FlavorType			objectType;
	WENewObjectUPP		newHandler;
	WEDisposeObjectUPP	freeHandler;
	WEDrawObjectUPP		drawHandler;
	WEClickObjectUPP	clickHandler;
	WEStreamObjectUPP	streamHandler;
	WEHoverObjectUPP	hoverHandler;
	SInt32				refCon;
} WEOHTableEntry;

typedef struct WEObjectDesc
{
	WEObjectDescHandle	nextObject;			// next object in linked list
	WEObjectDescHandle  prevObject;			// previous object in linked list
	SInt32				objectOffset;		// offset of object's marker byte
	FlavorType			objectType;			// 4-letter tag identifying object type
	Handle				objectDataHandle;	// handle to object data
//	SInt32				objectSize;			// object height (hi) and width (lo), in pixels
	WEOHTableHandle		objectHTable;		// handle to object handler table
	SInt32				objectHTIndex;		// index into object handler table
	WEHandle			objectOwner;		// handle to owner WE instance
	SInt32				objectRefCon;		// free for use by object handlers
	Collection			objectProperties;	// collection of user-defined properties
	WEObjectPlacement	objectPlacement;	// object height, width and intrinsic baseline, in pixels
} WEObjectDesc;

#endif /*WASTE_OBJECTS*/

#pragma mark WERecStruct

typedef struct WERec
{
	GrafPtr						port;					// graphics port text is drawn into
	Handle						hText;					// handle to the text
	WELineArrayHandle			hLines;					// handle to the line array
	WEStyleTableHandle			hStyles;				// handle to the style table
	WERunArrayHandle			hRuns;					// handle to the style run array
	WERulerTableHandle			hRulers;				// handle to the ruler table
	WEParaArrayHandle			hParas;					// handle to the paragraph run array
	SInt32						textLength;				// length of text
	SInt32						nLines;					// number of lines
	SInt32						nStyles;				// number of unique styles in the style table
	SInt32						nRuns;					// number of style runs
	SInt32						nRulers;				// number of unique rulers in the ruler table
	SInt32						nParas;					// number of paragraph runs
	LongRect					viewRect;				// view rectangle, all drawing is clipped to this
	LongRect					destRect;				// destination rectangle
	SInt32						selStart;				// start of selection range
	SInt32						selEnd;					// end of selection range
	UInt32						flags;					// 32 bits of miscellaneous flags (private)
	UInt32						features;				// 32 bit of feature flags (public)
	UInt32						caretTime;				// time of most recent caret drawing, in ticks
	UInt32						clickTime;				// time of most recent click, in ticks
	UInt32						autoScrollDelay;		// mouse-tracking delay used when autoscrolling, in ticks
	SInt32						clickLoc;				// byte offset of most recent click
	SInt32						anchorStart;			// start offset of anchor word/line
	SInt32						anchorEnd;				// end offset of anchor word/line
	char						firstByte;				// first byte of a double-byte character
	WEEdge						clickEdge;				// edge of character hit by most recent click
	UInt16						clickCount;				// multiple click count
	GrafPtr						offscreenPort;			// offscreen graphics world
	RgnHandle					viewRgn;				// handle to the view region
	void *						refCon;					// reference value for client use
	Handle						hUserInfo;				// more junk for client use
	Collection					properties;				// collection of user-defined properties
	TSMDocumentID				tsmReference;			// reference value for the text services manager
	SInt32						tsmAreaStart;			// start of active input area (for TSM)
	SInt32						tsmAreaEnd;				// end of active input area
	DragReference				currentDrag;			// reference of drag being tracked by _WEDrag
	SInt32						dragCaretOffset;		// offset to caret displayed during a drag
	WEActionHandle				hUndoStack;				// the undo stack
	WEActionHandle				hRedoStack;				// the redo stack
	UInt32						modCount;				// modification count
	WERunAttributes				nullStyle;				// style for null selection
	WEObjectDescHandle			objectList;				// linked list of embedded objects
	WEObjectDescHandle			hoveredObject;			// object currently under the mouse
	WEOHTableHandle				hObjectHandlerTable;	// handle to object handler table for this instance
	SInt32						translucencyThreshold;	// use translucent drags unless selection area exceeds this
	StringHandle				hURLHint;				// hint string for slack URLs
	WEClickLoopUPP				clickLoop;				// click loop callback
	WEScrollUPP					scrollProc;				// scroll callback
	WETSMPreUpdateUPP			tsmPreUpdate;			// TSM pre-update callback
	WETSMPostUpdateUPP			tsmPostUpdate;			// TSM post-update callback
	WEHiddenTextUPP				hiddenTextProc;			// hidden text callback
	WEPreTrackDragUPP			preTrackDragHook;		// pre-TrackDrag hook
	WETranslateDragUPP			translateDragHook;		// drag translation hook
	WEHiliteDropAreaUPP			hiliteDropAreaHook;		// drop area highlighting hook
	WEDrawTextUPP				drawTextHook;			// hook for drawing text
	WEPixelToCharUPP			pixelToCharHook;		// hook for hit-testing
	WECharToPixelUPP			charToPixelHook;		// hook for locating glyph position
	WELineBreakUPP				lineBreakHook;			// hook for finding line breaks
	WEWordBreakUPP				wordBreakHook;			// hook for finding word breaks
	WECharByteUPP				charByteHook;			// hook for finding character byte type
	WECharTypeUPP				charTypeHook;			// hook for finding character type
	WEEraseUPP					eraseHook;				// hook for erasing background
	WEDrawTSMHiliteUPP			drawTSMHiliteHook;		// hook for drawing TSM hilites
	WEFluxUPP					fluxProc;				// flux callback
	WEUndoUPP					undoProc;				// undo callback
	WEPrepareViewUPP			prepareProc;			// prepare callback
	WEFontNameToIDUPP			fontNameToFamilyHook;	// hook for mapping font names to family numbers
	WEFontIDToNameUPP			fontFamilyToNameHook;	// hook for mapping font IDs to names
	Fixed						defaultTabWidth;		// default tab width
	SInt32						maxLineWidth;			// upper bound on the width of the widest line
} WERec;

struct SLDrawData
{
	GrafPtr			screenPort;
	GDHandle		screenDevice;
	PixMapHandle	offscreenPixels;		// offscreen pixel map
	Rect			bounds;					// bounds of offscreen buffer, in global coords
	Rect			lineRect;				// rect enclosing current line
	Rect			drawRect;				// visible portion of line rect
	Boolean			usingColor;				// true if drawing in color
	Boolean			usingOffscreen;			// true if an offscreen graphics world has been set up
	Boolean			drawingOffscreen;		// true if actually drawing to an offscreen buffer
	Boolean			doErase;				// true if line rectangle should be erased before drawing
	RgnHandle		lineHilite;				// portion of the hilite region that intersects the current line
};

struct SLCalcSlopData
{
	Fixed			totalProportion;
	SInt16			totalSlop;
};

struct SLPixelToCharData
{
	Fixed			hPos;
	Fixed			pixelWidth;
	SInt32			offset;
	WEEdge			edge;
};

struct SLCharToPixelData
{
	LongPt *		thePoint;
	SInt32			offset;
	SInt16			direction;
	Boolean			lineDir;		// is the line direction RL?
	Boolean			rightEdge;		// are we getting the right edge of the line?
};

struct SLCollectHiliteRgnData
{
	SInt32			rangeStart;
	SInt32			rangeEnd;
	SInt16			hPos;
};

struct SLCrossDirectionBoundaryData
{
	SInt32			oldOffset;		//	offset before crossing direction boundary
	SInt32			newOffset;		//	offset after crossing direction boundary
	Boolean			movingRight;	//	moving insertion point to the right?
	Boolean			isDone;
};

struct FormatOrderData
{
	SInt32			firstRun;
	WEHandle		hWE;
};

#if PRAGMA_STRUCT_ALIGN
#pragma options align=reset
#endif

#ifdef __cplusplus
extern "C" {
#endif

//	SUPERCARD-SPECIFIC ROUTINES

enum {
	sigRUNX				=		FOUR_CHAR_CODE ( 'RUNX' ),	//	SuperCard signature
	kScrollStepTag		= 		FOUR_CHAR_CODE ( 'STEP' ),	//	user tag used to save scroll step information in scrollbars
	kTabSizeTag			= 		FOUR_CHAR_CODE ( 'TSIZ' ),	//	user tag used to save indent settings for script editor
	kAutoIndentUPPTag	=		FOUR_CHAR_CODE ( 'NDNT' ),	//	user tag for auto-indenting proc
	kAutoIndentSpaceTag	=		FOUR_CHAR_CODE ( 'EMSP' ),	//	user tag for width in  points of em space in auto-indented text
	kWERecIsDirtyFlag	=		FOUR_CHAR_CODE ( 'DIRT' ),
	kWERecSpotRectFlag	=		FOUR_CHAR_CODE ( 'RECT' ),
	kTypePicture		=		FOUR_CHAR_CODE ( 'PICT' ),
	
	//	resource types, clipboard types, and file types
	kTypeFixedTab			=		FOUR_CHAR_CODE ( 'WEft' ),		//	Our special hack to store our single fixed tab size
	kTypeFont				=		FOUR_CHAR_CODE ( 'FONT' ),
	kTypePrintRecord		=		FOUR_CHAR_CODE ( 'PREC' ),
	kTypePageFormat			=		FOUR_CHAR_CODE ( 'WEpg' ),		//	Carbon PMPageFormat object
	kTypePageMargins		=		FOUR_CHAR_CODE ( 'MARG' ),		//	page margins
	kTypeSound				=		FOUR_CHAR_CODE ( 'snd ' ),
	kTypeMovie				=		FOUR_CHAR_CODE ( 'moov' ),
	kTypeOldIota			=		FOUR_CHAR_CODE ( 'iota' ),
	kTypeIota				=		FOUR_CHAR_CODE ( 'Iota' ),
	kTypeHyperLink			=		FOUR_CHAR_CODE ( 'HLnk' ),
	kTypeTextLink			=		FOUR_CHAR_CODE ( 'TLnk' ),
	kTypeImageLink			=		FOUR_CHAR_CODE ( 'ILnk' ),
	kTypeLinkAnchor			=		FOUR_CHAR_CODE ( 'ALnk' ),
	
	kTypeOwnerWindow		=		FOUR_CHAR_CODE ( 'OWNR' )
//	kQTFileType3DMF			=		FOUR_CHAR_CODE ( '3dmf' )
//	kQTFileType3DMF			=		FOUR_CHAR_CODE ( '3DMF' )

	/*//	resource types, clipboard types, and file types
	kTypeMenuColorTable		=		FOUR_CHAR_CODE ( 'mctb' ),
	kTypeDeskAccessory		=		FOUR_CHAR_CODE ( 'DRVR' ),
	kTypeDialogItemList		=		FOUR_CHAR_CODE ( 'DITL' ),
	kTypeFont				=		FOUR_CHAR_CODE ( 'FONT' ),
	kTypePicture			=		FOUR_CHAR_CODE ( 'PICT' ),
	kTypePrintRecord		=		FOUR_CHAR_CODE ( 'PREC' ),
	kTypePageFormat			=		FOUR_CHAR_CODE ( 'WEpg' ),		//	Carbon PMPageFormat object
	kTypePageMargins		=		FOUR_CHAR_CODE ( 'MARG' ),		//	page margins
	kTypeSound				=		FOUR_CHAR_CODE ( 'snd ' ),
	kTypeMovie				=		FOUR_CHAR_CODE ( 'moov' ),
//	kQTFileType3DMF			=		FOUR_CHAR_CODE ( '3dmf' )
	kQTFileType3DMF			=		FOUR_CHAR_CODE ( '3DMF' )*/
} ;

typedef struct linkData {
	UInt8	magic[4];
	Handle	data;
	Handle	url;
	Handle	type;
	Handle	name;
} linkData;

enum {
	eHyperlinkURL	= 300,
	eHyperlinkType,
	eHyperlinkImageFormat,
	eHyperlinkAnchorID
};
	
enum
{
	/* user tags used in association with WEGetUserInfo / WESetUserInfo */
	kDocumentTag					=		FOUR_CHAR_CODE ( 'docu' ),		/* reference to owner document */
	kPageFormatTag					=		kTypePageMargins
};
enum
{
	/* WASTE Demo signature */
//	sigWASTE						=		FOUR_CHAR_CODE ( 'OEDE' ),

	/* resource types, clipboard types, and file types */
	kTypeDialogItemList				=		FOUR_CHAR_CODE ( 'DITL' ),
	kPageMarginsTag					=		kTypePageMargins
} ;


#if __ZERO_SPACE_INDENTING__
short WERecalcIndents(SInt32 *startLine, SInt32 *endLine, WEHandle hWE);
short WEGetAutoIndentFlag(WEHandle we);
void SetAutoIndentFlag(WEHandle we, short onoff);
void SetAutoIndentSize(WEHandle we, short tabSize);
long GetAutoIndentSize(WEHandle we);
void SetAutoIndentSpaceWidth(WEHandle we);
long GetAutoIndentSpaceWidth(WEHandle we);
#endif



//	PUBLIC ROUTINES

// ¥¥ MDL 10-2-4 ¥¥
void WESetPreferUTXTFlag(short trueFalse);
// ¥¥

//	WEAccessors.c (public)
pascal SInt32 		WEOffsetToLine			(SInt32 offset, WEHandle hWE);
pascal SInt32 		WECountLines			(WEHandle hWE);
pascal void 		WEGetLineRange			(SInt32 lineIndex, SInt32 *lineStart, SInt32 *lineEnd, WEHandle hWE);
pascal SInt32 		WEOffsetToRun			(SInt32 offset, WEHandle hWE);
pascal SInt32 		WECountRuns				(WEHandle hWE);
pascal void 		WEGetRunRange			(SInt32 runIndex, SInt32 *runStart, SInt32 *runEnd, WEHandle hWE);
pascal Boolean 		WEGetRunDirection		(SInt32 offset, WEHandle hWE);
pascal void 		WEGetRunInfo			(SInt32 offset, WERunInfo *info, WEHandle hWE);
pascal void 		WEGetIndRunInfo			(SInt32 runIndex, WERunInfo *info, WEHandle hWE);
pascal SInt32 		WEOffsetToParaRun		(SInt32 offset, WEHandle hWE);
pascal SInt32 		WECountParaRuns			(WEHandle hWE);
pascal void 		WEGetParaRunRange		(SInt32 runIndex, SInt32 *runStart, SInt32 *runEnd, WEHandle hWE);
pascal void 		WEGetParaInfo			(SInt32 offset, WEParaInfo *info, WEHandle hWE);
pascal void 		WEGetIndParaInfo		(SInt32 runIndex, WEParaInfo *info, WEHandle hWE);
pascal void 		WESetDestRect			(const LongRect *destRect, WEHandle hWE);
pascal void 		WEGetDestRect			(LongRect *destRect, WEHandle hWE);
pascal void 		WESetViewRect			(const LongRect *viewRect, WEHandle hWE);
pascal void 		WEGetViewRect			(LongRect *viewRect, WEHandle hWE);
pascal WEAlignment 	WEGetAlignment			(WEHandle hWE);
pascal WEDirection 	WEGetDirection			(WEHandle hWE);
pascal void 		WEGetSelection			(SInt32 *selStart, SInt32 *selEnd, WEHandle hWE);
pascal SInt32 		WEGetTextLength			(WEHandle hWE);
pascal SInt32 		WEGetHeight				(SInt32 startLine, SInt32 endLine, WEHandle hWE);
pascal Handle 		WEGetText				(WEHandle hWE);
pascal SInt16 		WEGetChar				(SInt32 offset, WEHandle hWE);
pascal SInt16 		WEFeatureFlag			(SInt16 feature, SInt16 action, WEHandle hWE);
pascal UInt32 		WEVersion				(void);

//	WEAttributes.c (public)
pascal OSErr WEGetAttributes				(SInt32 offset, ItemCount attributeCount,
												const WESelector * selectorArray, void * const * valueArray,
												const ByteCount * sizeArray, WEHandle hWE);
pascal OSErr WEGetOneAttribute				(SInt32 offset, WESelector selector, void * value,
												ByteCount size, WEHandle hWE);
pascal OSErr WESetAttributes				(SInt32 rangeStart, SInt32 rangeEnd, ItemCount attributeCount,
												const WESelector * selectorArray, const void * const * valueArray,
												const ByteCount * sizeArray, WEHandle hWE);
pascal OSErr WESetOneAttribute				(SInt32 rangeStart, SInt32 rangeEnd, WESelector selector,
												const void * value, ByteCount size, WEHandle hWE);
pascal OSErr WEMatchAttributes				(SInt32 rangeStart, SInt32 rangeEnd, WESelector selector,
												ByteCount valueSize, ItemCount arraySize, const void * valueArray,
												Boolean * isPresentArray, Boolean * isContinuous, WEHandle hWE);

// From WEFieldPrinting.c
OSStatus			DoPageSetup 			(Document *inDocument);
OSStatus			DoPrint 				(Document *inDocument);


//	WEBirthDeath.c (public)
pascal OSErr 		WENew					(const LongRect *destRect, const LongRect *viewRect, UInt32 features, WEHandle *hWE);
pascal void 		WEDispose				(WEHandle hWE);
pascal OSErr 		WEUseText				(Handle text, WEHandle hWE);

//	WEDrawing.c (public)
pascal Boolean 		WEContinuousStyle		(WEStyleMode *mode, TextStyle *ts, WEHandle hWE);
pascal Boolean 		WEContinuousRuler		(WERulerMode *mode, WERuler *ruler, WEHandle hWE);

//	WEFiles.c (public)
//pascal OSStatus WESave(SInt32 rangeStart, SInt32 rangeEnd, const FSRef * fileRef, OSType fileType,
//	TextEncoding textEncoding, OptionBits flags, const WERec * pWE);
//pascal OSStatus WELoad(SInt32 rangeStart, SInt32 rangeEnd, const FSRef * fileRef, OSType * fileType,
//	TextEncoding * textEncoding, OptionBits * flags, WERec * pWE);

//	WEFind.c (public)
pascal OSErr 		WEFind(const UInt8 * inKey, SInt32 inKeyLength, TextEncoding inKeyEncoding,
							OptionBits inMatchOptions, SInt32 inRangeStart, SInt32 inRangeEnd, SInt32 * outMatchStart, SInt32 * outMatchEnd, WEHandle hWE);

//	WEFontTables.c (public)
pascal OSErr 		WEBuildFontTable		(Handle hFontTable, WEFontIDToNameUPP fontIDToNameProc, WEHandle hWE);
pascal OSErr 		WEUpdateFontTable		(Handle hFontTable, WEFontNameToIDUPP fontNameToIDProc, Boolean *wasChanged);
pascal OSErr 		WEUpdateStyleScrap		(StScrpHandle hStyles, Handle hFontTable);

//	WEHighLevelEditing.c (public)
pascal void 		WEKey					(SInt16 key, EventModifiers modifiers, WEHandle hWE);
pascal OSErr 		WEPut					(SInt32 inRangeStart, SInt32 inRangeEnd, const char * inTextPtr, ByteCount inTextLength,
												TextEncoding inTextEncoding, OptionBits inPutOptions, ItemCount inFlavorCount, 
												const FlavorType * inFlavorTypes, const Handle * inFlavorHandles, WEHandle hWE);
pascal OSErr 		WEInsert				(const char * inTextPtr, ByteCount inTextLength, Handle inTEStyleScrap,
												Handle inSoup, WEHandle hWE);
pascal OSErr 		WEInsertFormattedText	(const char * inTextPtr, ByteCount inTextLength,
												Handle inTEStyleScrap, Handle inSoup, Handle inParaFormat, Handle inRulerScrap, WEHandle hWE);
pascal OSErr 		WEInsertObject			(FlavorType objectType, Handle objectDataHandle, Point objectSize, WEHandle hWE);
pascal OSErr 		WEDelete				(WEHandle hWE);
pascal OSErr 		WECut					(WEHandle hWE);
pascal Boolean	 	WECanPaste				(WEHandle hWE);
pascal OSErr 		WEPaste					(WEHandle hWE);
pascal OSErr 		WESetStyle				(WEStyleMode mode, const TextStyle *ts, WEHandle hWE);
pascal OSErr 		WESetRuler				(WERulerMode mode, const WERuler *ruler, WEHandle hWE);
pascal OSErr 		WEChangeCase			(WECase caseType, WEHandle hWE);
pascal OSErr 		WEUseStyleScrap			(StScrpHandle hStyles, WEHandle hWE);
pascal OSErr 		WEUseSoup				(Handle hSoup, WEHandle hWE);

// ¥¥ MDL 1-24-4 ¥¥
pascal OSErr WEPasteTextMinusIndenting ( WEHandle hWE );
pascal void maketiffname(char *str, UInt32 idx);
// ¥¥

#if 0 /*TARGET_API_MAC_CARBON*/
pascal OSErr WEPutCFString ( SInt32 inRangeStart, SInt32 inRangeEnd, CFStringRef inCFString,
	OptionBits inPutOptions, WEHandle hWE);
#endif /*TARGET_API_MAC_CARBON*/

//	WEInlineInput.c (public)
pascal OSErr WEInstallTSMHandlers(void);
pascal OSErr WERemoveTSMHandlers(void);
pascal OSErr WEHandleTSMEvent(const AppleEvent *ae, AppleEvent *reply);
pascal void WEStopInlineSession(WEHandle hWE);

//	WELineLayout (public)
pascal OSErr WECalText(WEHandle hWE);
pascal void WESetAlignment(WEAlignment alignment, WEHandle hWE);
pascal void WESetDirection(WEDirection direction, WEHandle hWE);

//	WELongCoords.c (public)
pascal void WELongPointToPoint(const LongPt *lp, Point *p);
pascal void WEPointToLongPoint(Point p, LongPt *lp);
pascal void WESetLongRect(LongRect *lr, SInt32 left, SInt32 top, SInt32 right, SInt32 bottom);
pascal void WELongRectToRect(const LongRect *lr, Rect *r);
pascal void WERectToLongRect(const Rect *r, LongRect *lr);
pascal void WEOffsetLongRect(LongRect *lr, SInt32 hOffset, SInt32 vOffset);
pascal Boolean WELongPointInLongRect(const LongPt *lp, const LongRect *lr);
// ¥¥ MDL 6-1-1 ¥¥
pascal void 		WEInsetLongRect(LongRect *lr, SInt32 hOffset, SInt32 vOffset);
// ¥¥

//	WEMouse.c (public)
pascal Boolean WECanAcceptDrag(DragReference drag, WEHandle hWE);
pascal OSErr WETrackDrag(DragTrackingMessage message, DragReference drag,
									WEHandle hWE);
pascal OSErr WEReceiveDrag(DragReference drag, WEHandle hWE);
pascal Boolean WEDraggedToTrash(DragReference drag);
pascal void WEClick(Point mouseLoc, EventModifiers modifiers, UInt32 clickTime, WEHandle hWE);
pascal UInt16 WEGetClickCount(WEHandle hWE);

//	WEObjects.c (public)
pascal FlavorType WEGetObjectType(WEObjectDescHandle hObjectDesc);
pascal Handle WEGetObjectDataHandle(WEObjectDescHandle hObjectDesc);
// ¥¥ MDL 3-20-5 ¥¥
pascal void WESetObjectDataHandle(WEObjectDescHandle hObjectDesc, Handle data);
// ¥¥
pascal Point WEGetObjectSize(WEObjectDescHandle hObjectDesc);
//pascal OSErr WESetObjectSize(WEObjectDescHandle hObjectDesc, SInt32 objectSize);
pascal OSErr WESetObjectSize(WEObjectDescHandle hObjectDesc, Point inObjectSize);
pascal WEHandle WEGetObjectOwner(WEObjectDescHandle hObjectDesc);
pascal SInt32 WEGetObjectRefCon(WEObjectDescHandle hObjectDesc);
pascal void WESetObjectRefCon(WEObjectDescHandle hObjectDesc, SInt32 refCon);
pascal SInt32 WEGetObjectOffset(WEObjectDescHandle hObjectDesc);
pascal SInt16 WEGetObjectBaseline(const WEObjectDescHandle objectDesc);
pascal OSErr WESetObjectBaseline(WEObjectDescHandle objectDesc, SInt16 objectBaseline);
pascal OSErr WESetObjectPlacement(WEObjectDescHandle objectDesc, const WEObjectPlacement * objectPlacement);
pascal OSErr WEGetObjectFrame(WEObjectDescHandle hObjectDesc, LongRect * objectFrame);
pascal OSErr WEInstallObjectHandler(FlavorType objectType, WESelector handlerSelector,
				UniversalProcPtr handler, WEHandle hWE);
pascal OSErr WERemoveObjectHandler(FlavorType objectType, WESelector handlerSelector,
				UniversalProcPtr handler, WEHandle hWE);
pascal OSErr WEGetObjectHandler(FlavorType objectType, WESelector handlerSelector,
				UniversalProcPtr *handler, WEHandle hWE);
pascal OSErr WEGetObjectAtOffset(SInt32 offset, WEObjectDescHandle *hObjectDesc, WEHandle hWE);
pascal OSErr WEGetSelectedObject(WEObjectDescHandle *hObjectDesc, WEHandle hWE);
pascal SInt32 WEFindNextObject(SInt32 offset, WEObjectDescHandle *hObjectDesc, WEHandle hWE);
pascal SInt32 WEFindPreviousObject(SInt32 offset, WEObjectDescHandle *hObjectDesc, WEHandle hWE);

//pascal SInt32 WEFindPreviousObject(SInt32 offset, WEObjectDesc ** objectDesc, const WERec * pWE);
pascal OSErr WEInstallStandardObjectHandlers(FlavorType flavorType, WEHandle hWE);
pascal OSErr WERemoveStandardObjectHandlers(FlavorType flavorType, WEHandle hWE);
pascal OSStatus WEGetObjectProperty(const WEObjectDescHandle objectDesc, OSType propertyCreator, OSType propertyTag,
	ByteCount propertySize, ByteCount * actualSize, void * propertyBuffer);
pascal OSStatus WESetObjectProperty(WEObjectDescHandle objectDesc, OSType propertyCreator, OSType propertyTag,
	ByteCount propertySize, const void * propertyBuffer);
pascal OSStatus WERemoveObjectProperty(WEObjectDescHandle objectDesc, OSType propertyCreator, OSType propertyTag);


//	WEPrint.c (public)
//pascal OSErr WENewPrintSession ( const Rect * inPageRect, WEHandle inWE, Handle * outSession ) ;
//pascal OSErr WENewPrintSession ( WEPrintOptions *	inPrintOptions, WEHandle inWE, Handle * outSession ) ;
pascal OSErr WENewPrintSession (WEPrintOptions *inPrintOptions, WEHandle inWE, WEPrintHandle *outSession) ;
pascal void WEDisposePrintSession ( WEPrintHandle inSession ) ;
pascal SInt32 WECountPages ( WEPrintHandle inSession ) ;
pascal OSErr WEPrintPage ( SInt32 inPageIndex, GrafPtr inPrintPort, const Rect * inPageRect, WEPrintHandle inSession ) ;
pascal SInt32 WEGetPageHeight(SInt32 inPageIndex, WEPrintRec **inSession);

//	WEScraps.c (public)
pascal OSErr WECopyRange ( SInt32 rangeStart, SInt32 rangeEnd, Handle hText, Handle hStyles, Handle hSoup, WEHandle hWE ) ;
pascal OSErr WEStreamRange ( SInt32 rangeStart, SInt32 rangeEnd, FlavorType dataFlavor, OptionBits inStreamOptions, Handle hData, WEHandle hWE ) ;
pascal OSErr WECopy ( WEHandle hWE ) ;

//	WESelecting.c (public)
pascal SInt32 WEGetOffset(const LongPt *thePoint, WEEdge *edge, WEHandle hWE);
pascal void WEGetPoint(SInt32 offset, SInt16 direction, LongPt *thePoint, SInt16 *lineHeight, WEHandle hWE);
pascal void WEFindWord(SInt32 offset, WEEdge edge, SInt32 *wordStart, SInt32 *wordEnd, WEHandle hWE);
pascal void WEFindLine(SInt32 offset, WEEdge edge, SInt32 *lineStart, SInt32 *lineEnd, WEHandle hWE);
pascal void WEFindParagraph(SInt32 offset, WEEdge edge, SInt32 *paragraphStart, SInt32 *paragraphEnd, WEHandle hWE);
pascal SInt16 WECharByte(SInt32 offset, WEHandle hWE);
pascal SInt16 WECharType(SInt32 offset, WEHandle hWE);
pascal RgnHandle WEGetHiliteRgn(SInt32 rangeStart, SInt32 rangeEnd, WEHandle hWE);
pascal void WESetSelection(SInt32 selStart, SInt32 selEnd, WEHandle hWE);
pascal Boolean WEAdjustCursor(Point mouseLoc, RgnHandle mouseRgn, WEHandle hWE);
pascal void WEIdle(UInt32 *maxSleep, WEHandle hWE);
pascal void WEUpdate(RgnHandle updateRgn, WEHandle hWE);
pascal void WEDeactivate(WEHandle hWE);
pascal void WEActivate(WEHandle hWE);
pascal Boolean WEIsActive(WEHandle hWE);
pascal void WEScroll(SInt32 hOffset, SInt32 vOffset, WEHandle hWE);
pascal void WEPinScroll(SInt32 hOffset, SInt32 vOffset, WEHandle hWE);
pascal void WESelView(WEHandle hWE);

//	WESelectors.c (public)
pascal OSErr WEGetInfo(WESelector selector, void *info, WEHandle hWE);
pascal OSErr WESetInfo(WESelector selector, const void *info, WEHandle hWE);

//	WEUndo.c (public)
pascal OSErr WEUndo(WEHandle hWE);
pascal OSErr WERedo(WEHandle hWE);
pascal void WEClearUndo(WEHandle hWE);
pascal WEActionKind WEGetUndoInfo(Boolean *redoFlag, WEHandle hWE);
pascal WEActionKind WEGetIndUndoInfo(SInt32 undoLevel, WEHandle hWE);
pascal OSErr WEBeginAction(WEHandle hWE);
pascal OSErr WEEndAction(WEActionKind actionKind, WEHandle hWE);
pascal UInt32 WEGetModCount(WEHandle hWE);
pascal void WEResetModCount(WEHandle hWE);
pascal Boolean WEIsTyping(WEHandle hWE);

//	WEUnicode.c (public)
pascal OSErr WEGetTextRangeAsUnicode
	(
		SInt32					inRangeStart,
		SInt32					inRangeEnd,
		Handle					outUnicodeText,
		Handle					ioCharFormat,
		Handle					ioParaFormat,
		TextEncodingVariant		inEncodingVariant,
		TextEncodingFormat		inTransformationFormat,
		OptionBits				inOptions,
		WEHandle				inWE
	);

//	WEUPPs.c (public)
pascal WEClickLoopUPP NewWEClickLoopUPP ( WEClickLoopProcPtr inProcPtr ) ;
pascal WEScrollUPP NewWEScrollUPP ( WEScrollProcPtr inProcPtr ) ;
pascal WETSMPreUpdateUPP NewWETSMPreUpdateUPP ( WETSMPreUpdateProcPtr inProcPtr ) ;
pascal WETSMPostUpdateUPP NewWETSMPostUpdateUPP ( WETSMPostUpdateProcPtr inProcPtr ) ;
pascal WEPreTrackDragUPP NewWEPreTrackDragUPP ( WEPreTrackDragProcPtr inProcPtr ) ;
pascal WETranslateDragUPP NewWETranslateDragUPP ( WETranslateDragProcPtr inProcPtr ) ;
pascal WEHiliteDropAreaUPP NewWEHiliteDropAreaUPP ( WEHiliteDropAreaProcPtr inProcPtr ) ;
pascal WEFontIDToNameUPP NewWEFontIDToNameUPP ( WEFontIDToNameProcPtr inProcPtr ) ;
pascal WEFontNameToIDUPP NewWEFontNameToIDUPP ( WEFontNameToIDProcPtr inProcPtr ) ;
pascal WEDrawTextUPP NewWEDrawTextUPP ( WEDrawTextProcPtr inProcPtr ) ;
pascal WEPixelToCharUPP NewWEPixelToCharUPP ( WEPixelToCharProcPtr inProcPtr ) ;
pascal WECharToPixelUPP NewWECharToPixelUPP ( WECharToPixelProcPtr inProcPtr ) ;
pascal WELineBreakUPP NewWELineBreakUPP ( WELineBreakProcPtr inProcPtr ) ;
pascal WEWordBreakUPP NewWEWordBreakUPP ( WEWordBreakProcPtr inProcPtr ) ;
pascal WECharByteUPP NewWECharByteUPP ( WECharByteProcPtr inProcPtr ) ;
pascal WECharTypeUPP NewWECharTypeUPP ( WECharTypeProcPtr inProcPtr ) ;
pascal WEEraseUPP NewWEEraseUPP ( WEEraseProcPtr inProcPtr ) ;
pascal WEFluxUPP NewWEFluxUPP ( WEFluxProcPtr inProcPtr ) ;
pascal WEDrawTSMHiliteUPP NewWEDrawTSMHiliteUPP ( WEDrawTSMHiliteProcPtr inProcPtr ) ;
pascal WENewObjectUPP NewWENewObjectUPP ( WENewObjectProcPtr inProcPtr ) ;
pascal WEDisposeObjectUPP NewWEDisposeObjectUPP ( WEDisposeObjectProcPtr inProcPtr ) ;
pascal WEDrawObjectUPP NewWEDrawObjectUPP ( WEDrawObjectProcPtr inProcPtr ) ;
pascal WEClickObjectUPP NewWEClickObjectUPP ( WEClickObjectProcPtr inProcPtr ) ;
pascal WEStreamObjectUPP NewWEStreamObjectUPP ( WEStreamObjectProcPtr inProcPtr ) ;
pascal WEHoverObjectUPP NewWEHoverObjectUPP ( WEHoverObjectProcPtr inProcPtr ) ;
pascal WEUndoUPP NewWEUndoUPP ( WEUndoProcPtr inProcPtr ) ;
pascal WEPrepareViewUPP NewWEPrepareViewUPP ( WEPrepareViewProcPtr inProcPtr ) ;
pascal void DisposeWEClickLoopUPP ( WEClickLoopUPP inUPP ) ;
pascal void DisposeWEScrollUPP ( WEScrollUPP inUPP ) ;
pascal void DisposeWETSMPreUpdateUPP ( WETSMPreUpdateUPP inUPP ) ;
pascal void DisposeWETSMPostUpdateUPP ( WETSMPostUpdateUPP inUPP ) ;
pascal void DisposeWEPreTrackDragUPP ( WEPreTrackDragUPP inUPP ) ;
pascal void DisposeWETranslateDragUPP ( WETranslateDragUPP inUPP ) ;
pascal void DisposeWEHiliteDropAreaUPP ( WEHiliteDropAreaUPP inUPP ) ;
pascal void DisposeWEFontIDToNameUPP ( WEFontIDToNameUPP inUPP ) ;
pascal void DisposeWEFontNameToIDUPP ( WEFontNameToIDUPP inUPP ) ;
pascal void DisposeWEDrawTextUPP ( WEDrawTextUPP inUPP ) ;
pascal void DisposeWEPixelToCharUPP ( WEPixelToCharUPP inUPP ) ;
pascal void DisposeWECharToPixelUPP ( WECharToPixelUPP inUPP ) ;
pascal void DisposeWELineBreakUPP ( WELineBreakUPP inUPP ) ;
pascal void DisposeWEWordBreakUPP ( WEWordBreakUPP inUPP ) ;
pascal void DisposeWECharByteUPP ( WECharByteUPP inUPP ) ;
pascal void DisposeWECharTypeUPP ( WECharTypeUPP inUPP ) ;
pascal void DisposeWEEraseUPP ( WEEraseUPP inUPP ) ;
pascal void DisposeWEFluxUPP ( WEFluxUPP inUPP ) ;
pascal void DisposeWEDrawTSMHiliteUPP ( WEDrawTSMHiliteUPP inUPP ) ;
pascal void DisposeWENewObjectUPP ( WENewObjectUPP inUPP ) ;
pascal void DisposeWEDisposeObjectUPP ( WEDisposeObjectUPP inUPP ) ;
pascal void DisposeWEDrawObjectUPP ( WEDrawObjectUPP inUPP ) ;
pascal void DisposeWEClickObjectUPP ( WEClickObjectUPP inUPP ) ;
pascal void DisposeWEStreamObjectUPP ( WEStreamObjectUPP inUPP ) ;
pascal void DisposeWEHoverObjectUPP ( WEHoverObjectUPP inUPP ) ;
pascal Boolean InvokeWEClickLoopUPP ( WEHandle inWE, WEClickLoopUPP inUPP ) ;
pascal void InvokeWEScrollUPP ( WEHandle inWE, WEScrollUPP inUPP ) ;
pascal void InvokeWETSMPreUpdateUPP ( WEHandle inWE, WETSMPreUpdateUPP inUPP ) ;
pascal void InvokeWETSMPostUpdateUPP ( WEHandle inWE, SInt32 inFixLength, SInt32 inInputAreaStart, SInt32 inInputAreaEnd, SInt32 inPinRangeStart, SInt32 inPinRangeEnd, WETSMPostUpdateUPP inUPP ) ;
pascal OSErr InvokeWEPreTrackDragUPP ( DragReference inDrag, WEHandle inWE, WEPreTrackDragUPP inUPP ) ;
pascal OSErr InvokeWETranslateDragUPP ( DragReference inDrag, ItemReference inDragItem, FlavorType inRequestedType, Handle outData, SInt32 inDropOffset, WEHandle inWE, WETranslateDragUPP inUPP ) ;
pascal OSErr InvokeWEHiliteDropAreaUPP ( DragReference inDrag, Boolean inHiliteFlag, WEHandle inWE, WEHiliteDropAreaUPP inUPP ) ;
pascal OSErr InvokeWEFontIDToNameUPP ( SInt16 inFontID, StringPtr ioFontName, WEFontIDToNameUPP inUPP ) ;
pascal OSErr InvokeWEFontNameToIDUPP ( ConstStr255Param inFontName, SInt16 inOldFontID, SInt16 * outNewFontID, WEFontNameToIDUPP inUPP ) ;
pascal void InvokeWEDrawTextUPP ( const char * inTextPtr, SInt32 inTextLength, Fixed inSlop, JustStyleCode inStyleRunPosition, WEHandle inWE, WEDrawTextUPP inUPP ) ;
pascal void InvokeWEDrawTSMHiliteUPP ( const Rect * inSegmentRect, SInt16 inHiliteStyle, WEHandle inWE, WEDrawTSMHiliteUPP inUPP ) ;
pascal SInt32 InvokeWEPixelToCharUPP ( const char * inTextPtr, SInt32 inTextLength, Fixed inSlop, Fixed * ioPixelWidth, WEEdge * outEdge, JustStyleCode inStyleRunPosition, Fixed inHorizontalPosition, WEHandle inWE, WEPixelToCharUPP inUPP ) ;
pascal SInt16 InvokeWECharToPixelUPP ( const char * inTextPtr, SInt32 inTextLength, Fixed inSlop, SInt32 inOffset, SInt16 inDirection, JustStyleCode inStyleRunPosition, SInt16 inHorizontalPosition, WEHandle inWE, WECharToPixelUPP inUPP ) ;
pascal StyledLineBreakCode InvokeWELineBreakUPP ( const char * inTextPtr, SInt32 inTextLength, SInt32 inTextStart, SInt32 inTextEnd, Fixed * ioTextWidth, SInt32 * ioTextOffset, WEHandle inWE, WELineBreakUPP inUPP ) ;
pascal void InvokeWEWordBreakUPP ( const char * inTextPtr, SInt16 inTextLength, SInt16 inOffset, WEEdge inEdge, OffsetTable outBreakOffsets, ScriptCode inScript, WEHandle inWE, WEWordBreakUPP inUPP ) ;
pascal SInt16 InvokeWECharByteUPP ( const char * inTextPtr, SInt16 inTextOffset, ScriptCode inScript, WEHandle inWE, WECharByteUPP inUPP ) ;
pascal SInt16 InvokeWECharTypeUPP ( const char * inTextPtr, SInt16 inTextOffset, ScriptCode inScript, WEHandle inWE, WECharTypeUPP inUPP ) ;
pascal void InvokeWEEraseUPP ( const Rect * inDirtyRect, WEHandle inWE, WEEraseUPP inUPP ) ;
pascal void InvokeWEFluxUPP ( SInt32 inOffset, SInt32 inDelta, WEHandle inWE, WEFluxUPP inUPP ) ;
//pascal OSErr InvokeWENewObjectUPP ( SInt32 * outNaturalObjectSize, WEObjectDescHandle inObjectDesc, WENewObjectUPP inUPP ) ;
pascal OSErr InvokeWENewObjectUPP ( WEObjectPlacement * outNaturalObjectSize, WEObjectDescHandle inObjectDesc, WENewObjectUPP inUPP ) ;
pascal OSErr InvokeWEDisposeObjectUPP ( WEObjectDescHandle inObjectDesc, WEDisposeObjectUPP inUPP ) ;
pascal OSErr InvokeWEDrawObjectUPP ( const Rect * inDestRect, WEObjectDescHandle inObjectDesc, WEDrawObjectUPP inUPP ) ;
pascal Boolean InvokeWEClickObjectUPP ( Point inHitPoint, EventModifiers inModifiers, UInt32 inClickTime, WEObjectDescHandle inObjectDesc, WEClickObjectUPP inUPP ) ;
pascal OSErr InvokeWEStreamObjectUPP ( SInt16 inDestinationKind, FlavorType * outStreamedFlavorType, Handle *outStreamedData, WEObjectDescHandle inObjectDesc, WEStreamObjectUPP inUPP ) ;
pascal OSErr InvokeWEHoverObjectUPP ( SInt16 inMouseAction, Point inMouseLoc, RgnHandle inMouseRgn, WEObjectDescHandle inObjectDesc, WEHoverObjectUPP inUPP ) ;

//	WEUserSelectors.c (public)
pascal OSStatus WEGetProperty ( OSType propertyCreator, OSType propertyTag, ByteCount propertySize,
	ByteCount * actualSize, void * propertyBuffer, WEHandle hWE ) ;
pascal OSStatus WESetProperty ( OSType propertyCreator, OSType propertyTag, ByteCount propertySize,
	const void * propertyBuffer, WEHandle hWE ) ;
pascal OSStatus WERemoveProperty ( OSType propertyCreator, OSType propertyTag, WEHandle hWE ) ;
pascal OSErr WEGetUserInfo(WESelector tag, SInt32 *userInfo, WEHandle hWE);
pascal OSErr WESetUserInfo(WESelector tag, SInt32 userInfo, WEHandle hWE);
pascal OSErr WERemoveUserInfo(WESelector tag, WEHandle hWE);

//	WESharedLibrary.c
pascal OSErr _WECFMInitialize(const CFragInitBlock *theInitBlock);
pascal void _WECFMTerminate(void);


//	PRIVATE ROUTINES

//	These routines should be eligible to be tagged "internal" when
//	building a CFM shared library: they should never be exported
//	(listed in the .exp file) and their address should never be passed
//	to an external fragment.

#if WASTE_SHARED_LIBRARY
#pragma internal on
#endif

//	WEAccessors.c (private)
pascal SInt32 _WEPixelToLine(SInt32 vOffset, WEHandle hWE);
pascal void _WEGetIndStyle(SInt32 runIndex, WERunInfo *info, WEHandle hWE);
pascal void _WEGetIndRuler(SInt32 paraIndex, WEParaInfo *info, WEHandle hWE);
pascal Boolean _WEGetIndDirection(SInt32 runIndex, WEHandle hWE);
pascal void _WEGetExtRunInfo(SInt32 offset, WERunInfo *info, WEHandle hWE);
pascal void _WEGetExtParaInfo(SInt32 inOffset, WEParaInfo * outParaInfo, WEHandle hWE);

//	WEAttributes.c (private)
pascal Size _WEGetAttributeSize(WESelector selector);
//pascal void _WEGetTabs(WETabList * tabList, const WERuler * ruler);
//pascal OSStatus _WESetTabs(const WETabList * tabList, WERuler * ruler);
pascal OSStatus _WEGetLanguage(LocaleRef inLocale, void * outAttributeValue, ByteCount inAttributeSize);
pascal OSStatus _WESetLanguage(const void * inAttributeValue, ByteCount inAttributeSize, LocaleRef * outLocale);
#if __SUPPORTS_WASTE21_LINEHEIGHT__
pascal OSStatus _WEGetLineSpacing(const WERuler * inRuler, WELineSpacing * outLineSpacing );
pascal OSStatus _WESetLineSpacing(const WELineSpacing * inLineSpacing, WERuler * ioRuler );
#endif

//	WEBirthDeath.c (private)
extern WEDrawTextUPP		_weStdDrawTextProc;
extern WEPixelToCharUPP		_weStdPixelToCharProc;
extern WECharToPixelUPP		_weStdCharToPixelProc;
extern WELineBreakUPP		_weStdLineBreakProc;
extern WEWordBreakUPP		_weStdWordBreakProc;
extern WECharByteUPP		_weStdCharByteProc;
extern WECharTypeUPP		_weStdCharTypeProc;
extern WEClickLoopUPP		_weStdClickLoopProc;
extern WEHiliteDropAreaUPP	_weStdHiliteDropAreaProc;
extern WEEraseUPP			_weStdEraseProc;
extern WEDrawTSMHiliteUPP	_weStdDrawTSMHiliteProc;
extern WEHiddenTextUPP		_weStdHiddenTextProc;
extern const Point 			kOneToOneScaling;
pascal void _WEResetStyleTable(WEHandle hWE);
pascal void _WESetStandardHooks(WEHandle hWE);
pascal SInt16 _WEScriptToFont(ScriptCode script);

//	WEDebug.c (private)
pascal void _WESanityCheck(WEHandle hWE);

//	WEDrawing.c (private)
extern StyleRunDirectionUPP _weGetSegmentDirectionUPP;
pascal void _WEContinuousStyleRange(SInt32 rangeStart, SInt32 rangeEnd, WEStyleMode *mode, WETextStyle *ts, WEHandle hWE);
pascal void _WESynchNullStyle(WEHandle hWE);
pascal void _WESegmentLoop(SInt32 firstLine, SInt32 lastLine, WESegmentLoopProcPtr callback, void *callbackData, WEHandle hWE);
pascal void _WEDrawLines (SInt32 firstLine, SInt32 lastLine, Boolean doErase, WEHandle hWE);
#if __ZERO_SPACE_INDENTING__
pascal SInt16 _WECalcPenIndent(const WELineRec * pLine, const WERuler * pRuler, WEHandle hWE);
#else
pascal SInt16 _WECalcPenIndent(const WELineRec * pLine, const WERuler * pRuler);
#endif
pascal void _WESaveQDEnvironment(GrafPtr port, QDEnvironment *environment);
pascal void _WERestoreQDEnvironment(const QDEnvironment *environment);
pascal OSStatus _WECalcFontMetrics (WERunAttributes *targetStyle, WEPtr pWE);
pascal SInt16 _WEResolveFontDesignator(SInt16 inFontFamilyNumber);
pascal void _WECopyStyle(const WETextStyle *sourceStyle, WETextStyle *targetStyle, Style offStyles, UInt32 mode);
pascal void _WECopyRuler(const WERuler *sourceRuler, WERuler *targetRuler, WERulerMode mode);
pascal Boolean _WEOffsetInRange(SInt32 offset, WEEdge edge, SInt32 rangeStart, SInt32 rangeEnd);
pascal void _WEDrawBorder(SInt16 borderWidth, SInt16 borderStyle);

//	WEFind.c (private)
pascal void _WEInitBoyerMooreSearch(const UInt8 * inKey, SInt32 inKeyLength, const UInt8 * inMappingTable, SInt32 outSkipTable[256]);
pascal OSStatus _WEDoBoyerMooreSearch(const UInt8 * inTargetText, SInt32 inTargetTextLength, const UInt8 * inKey, SInt32 inKeyLength,
	const UInt8 * inMappingTable, const SInt32 * inSkipTable, SInt32 * outMatchStart, SInt32 * outMatchEnd);

//	WEFontTables.c (private)
pascal OSStatus _WEBuildFontTableForRange(SInt32 rangeStart, SInt32 rangeEnd, Handle hFontTable, WEFontIDToNameUPP customMapper, WEHandle hWE);
pascal OSStatus _WEMapFontName
	(
		ConstStr255Param		inFontName,
		SInt16					inOriginalFontFamilyNumber,
		TextEncoding			inFontEncoding,
		WEFontNameToIDUPP		inCustomMapper,
		SInt16 *				outResolvedFontFamilyNumber
	);

pascal OSStatus _WEFontFamilyToQDFontName
	(
		FMFontFamily			inFontFamilyNumber,
		Str255					outQDFontName,
		WEFontIDToNameUPP		inCustomMapper
	);
pascal OSStatus _WEQDFontNameToFontFamily
	(
		ConstStr255Param		inQDFontName,
		FMFontFamily			inOriginalFontFamilyNumber,
		TextEncoding			inFontEncoding,
		WEFontNameToIDUPP		inCustomMapper,
		FMFontFamily *			outResolvedFontFamilyNumber
	);

//	WEHighLevelEditing.c (private)
pascal OSStatus _WETypeChar(char theByte, WEHandle hWE);
pascal OSStatus _WEBackspace(WEHandle hWE);
pascal OSStatus _WEForwardDelete(WEHandle hWE);
pascal Boolean _WEHasScrapFlavor(FlavorType inFlavorType);
pascal OSStatus _WEGetScrapHandle(FlavorType inFlavorType, OptionBits inAllocFlags, Handle * outData);
pascal OSStatus _WESmartSetFont(SInt32 rangeStart, SInt32 rangeEnd, Boolean extractSubscript, const WETextStyle *ts, WEHandle hWE);
pascal OSStatus _WESetNullStyle(UInt32 mode, const WETextStyle * ts, WEHandle hWE);

//	WEICGlue.c (private)
//	(see WEICGlue.h)

//	WEInlineInput.c (private)
extern AEEventHandlerUPP _weUpdateActiveInputAreaHandler;
extern AEEventHandlerUPP _wePositionToOffsetHandler;
extern AEEventHandlerUPP _weOffsetToPositionHandler;
extern AEEventHandlerUPP _weGetSelectedTextHandler;
pascal OSStatus _WERegisterWithTSM(WEHandle hWE);
pascal OSStatus _WEHiliteRangeArray(TextRangeArrayHandle hTray, WEHandle hWE);

//	WELineLayout.c (private)
INLINE pascal void _WERemoveLine(SInt32 lineIndex, WEPtr pWE); // Motorola 12-Nov-97
pascal OSStatus _WEInsertLine(SInt32 lineIndex, const WELineRec *pLine, WEPtr pWE);
pascal void _WEBumpOrigin(SInt32 lineIndex, SInt32 deltaOrigin, WEPtr pWE);
pascal SInt32 _WEFindLineBreak(SInt32 lineStart, WEHandle hWE);
pascal void _WECalcHeights(SInt32 rangeStart, SInt32 rangeEnd, SInt16 *lineAscent, SInt16 *lineDescent,
		WEHandle hWE);
pascal OSStatus _WERecalBreaks(SInt32 *startLine, SInt32 *endLine, WEHandle hWE);
pascal void _WERecalSlops(SInt32 firstLine, SInt32 lastLine, WEHandle hWE);

//	WELowLevelEditing.c (private)
pascal Boolean _WEIsWordRange(SInt32 rangeStart, SInt32 rangeEnd, WEHandle hWE);
pascal Boolean _WEIsPunct(SInt32 offset, WEHandle hWE);
pascal void _WEIntelligentCut(SInt32 *rangeStart, SInt32 *rangeEnd, WEHandle hWE);
pascal SInt16 _WEIntelligentPaste(SInt32 rangeStart, SInt32 rangeEnd, WEHandle hWE);
pascal OSStatus _WEInsertStyleRun(SInt32 runIndex, SInt32 offset, SInt32 styleIndex, WEPtr pWE);
pascal void _WERemoveStyleRun(SInt32 runIndex, WEPtr pWE);
pascal void _WEChangeStyleRun(SInt32 runIndex, SInt32 newStyleIndex, Boolean keepOld, WEPtr pWE);
pascal OSStatus _WEInsertParaRun(SInt32 paraIndex, SInt32 offset, SInt32 rulerIndex, WEPtr pWE);
pascal void _WERemoveParaRun(SInt32 paraIndex, WEPtr pWE);
pascal void _WEChangeParaRun(SInt32 paraIndex, SInt32 newRulerIndex, WEPtr pWE);
pascal OSStatus _WENewStyle(const WETextStyle *ts, SInt32 *styleIndex, WEPtr pWE);
pascal OSStatus _WENewRuler(const WERuler *ruler, SInt32 *rulerIndex, WEPtr pWE);
pascal OSStatus _WERedraw(SInt32 rangeStart, SInt32 rangeEnd, WEHandle hWE);
pascal OSStatus _WESetStyleRange(SInt32 rangeStart, SInt32 rangeEnd, UInt32 mode, const WETextStyle *ts, WEHandle hWE);
pascal void _WEExtendToParaBoundaries(SInt32 *rangeStart, SInt32 *rangeEnd, WERec * pWE);
pascal void _WEExtendToLineBoundaries ( SInt32 * rangeStart, SInt32 * rangeEnd, WERec * pWE );
pascal OSStatus _WESetRulerRange(SInt32 rangeStart, SInt32 rangeEnd, WERulerMode mode,
				const WERuler *ruler, WEHandle hWE);
pascal OSStatus _WEApplyEncodingScrap(SInt32 inRangeStart, SInt32 inRangeEnd, Handle inEncodingScrap, WEHandle hWE);
pascal OSStatus _WEApplyTextEditStyleScrap(SInt32 rangeStart, SInt32 rangeEnd, StScrpHandle styleScrap, WEHandle hWE);
pascal OSStatus _WEApplyParagraphFormatting(SInt32 rangeStart, SInt32 rangeEnd, Handle hParaFormat, Handle hRulerArray, WEHandle hWE);
pascal OSStatus _WEApplyCharacterFormatting(SInt32 rangeStart, SInt32 rangeEnd, Handle hCharFormat, Handle hStyleArray, WEHandle hWE);
pascal OSStatus _WEApplySoup(SInt32 offset, Handle hSoup, WEHandle hWE);
pascal void _WEBumpStyleRunStart(SInt32 runIndex, SInt32 deltaRunStart, WEPtr pWE);
pascal void _WEBumpParaRunStart(SInt32 paraIndex, SInt32 deltaParaStart, WEPtr pWE);
pascal void _WERemoveStyleRunRange(SInt32 rangeStart, SInt32 rangeEnd, WEHandle hWE);
pascal void _WEBumpLineStart(SInt32 lineIndex, SInt32 deltaLineStart, WEPtr pWE);
pascal void _WERemoveParaRunRange(SInt32 rangeStart, SInt32 rangeEnd, WEHandle hWE);
pascal void _WERemoveLineRange(SInt32 rangeStart, SInt32 rangeEnd, WEHandle hWE);
pascal void _WEBumpObjectOffsets(SInt32 offset, SInt32 delta, WEHandle hWE);
pascal OSStatus _WEDeleteRange(SInt32 rangeStart, SInt32 rangeEnd, WEHandle hWE);
pascal OSStatus _WEInsertText(SInt32 offset, const char * textPtr, SInt32 textLength, WEHandle hWE);

//	WELongCoords (private)
pascal SInt32 _WEPinInRange(SInt32 value, SInt32 rangeStart, SInt32 rangeEnd);

//	WEMouse.c (private)
extern DragSendDataUPP _weFlavorSender;
pascal Boolean _WEIsOptionDrag(DragReference drag);
pascal Boolean _WEIsWASTEOriginatedDrag(DragReference drag, WEHandle hWE);
pascal OSStatus _WEGetFlavor(DragReference drag, ItemReference dragItem,
				FlavorType requestedType, Handle hFlavor,
				SInt32 dropOffset, WEHandle hWE);
pascal OSStatus _WEExtractFlavor(DragReference drag, ItemReference dragItem,
				FlavorType theType, OptionBits allocFlags, Handle *hFlavor,
				SInt32 dropOffset, WEHandle hWE);
pascal void _WEUpdateDragCaret(SInt32 offset, WEHandle hWE);
pascal OSStatus _WEOutlineRgn(RgnHandle solidRgn, RgnHandle * outlineRgn);
pascal OSStatus _WEMakeDragImage(GWorldPtr *imageGWorld, RgnHandle *imageRgn, WEHandle hWE);
pascal OSStatus _WEDrag(Point mouseLoc, EventModifiers modifiers, UInt32 clickTime, WEHandle hWE);
pascal OSStatus _WEReceiveDragItem(DragReference inDrag, ItemReference inDragItem,
			SInt32 inInsertionOffset, WEHandle hWE);
pascal void _WEResolveURL(EventModifiers modifiers, SInt32 urlStart, SInt32 urlEnd, WEHandle hWE);

//	WEObjects.c (private)
//extern WEOHTableHandle _weGlobalObjectHandlerTable;
extern WEOHTableHandle		_weGlobalObjectHandlerTable;
extern WENewObjectUPP		_weStdNewPictureUPP;
extern WEDrawObjectUPP		_weStdDrawPictureUPP;
extern WENewObjectUPP		_weStdNewSoundUPP;
extern WEDrawObjectUPP		_weStdDrawSoundUPP;
extern WEClickObjectUPP		_weStdClickSoundUPP;
extern WEDisposeObjectUPP	_weStdDisposeSoundUPP;
extern IconSuiteRef			_weSoundIcon;
extern SndChannel *			_weSoundChannel ;
//extern WEObjectDesc *		_weCurrentSound ;


pascal SInt32 _WELookupObjectType(FlavorType objectType, WEOHTableHandle hTable);
pascal OSStatus _WEGetIndObjectType(SInt32 index, FlavorType *objectType, WEHandle hWE);
pascal OSStatus _WENewObject(FlavorType objectType, Handle objectDataHandle, SInt32 markerOffset,
					WEHandle hWE, WEObjectDescHandle *hObjectDesc);
pascal OSStatus _WEFreeObject(WEObjectDescHandle hObjectDesc);
pascal OSStatus _WEDrawObject(WEObjectDescHandle hObjectDesc);
pascal Boolean _WEHoverObject(SInt16 mouseAction, Point mouseLoc, RgnHandle mouseRgn, WEObjectDescHandle hObjectDesc);
pascal Boolean _WEClickObject(Point hitPt, EventModifiers modifiers, UInt32 clickTime,
								WEObjectDescHandle hObjectDesc);
pascal OSStatus _WEStreamObject(SInt16 destKind, FlavorType *theType, Handle *theData,
				Boolean *canDisposeData, WEObjectDescHandle hObjectDesc);
pascal OSStatus _WEInsertObjectAtOffset(SInt32 inOffset, FlavorType inObjectType, Handle inObjectDataHandle,
	Point inObjectSize, WEHandle hWE);
	//SInt32 inObjectSize, WEHandle hWE);

#if __SUPPORTS_EMBEDDED_SOUNDS__
pascal OSStatus _WEPlaySound ( WEObjectDesc * inSoundObject ) ;
pascal void _WEStopCurrentSound ( void ) ;
pascal Boolean _WEIsSoundPlaying ( void ) ;
pascal void _WECheckSoundStatus ( Boolean inStopNow ) ;
#endif

//	WEPrint.c (private)
pascal void _WEGetPageRange ( SInt32 inPageIndex, SInt32 * outPageStart, SInt32 * outPageEnd, WEPrintHandle inSession ) ;

//	WEScraps.c (private)
pascal OSStatus _WEAddRulerToStream(const WERuler * ruler, WEStreamPtr stream );
pascal OSStatus _WEAddStyleToStream(const WETextStyle * style, WEFontIDToNameUPP customFontMapper, WEStreamPtr stream );
pascal OSStatus _WEAddObjectToStream ( SInt16 inDestinationKind, WEObjectDescHandle inObject, WEStreamPtr stream );
pascal OSStatus _WEBuildSTXT(SInt32 rangeStart, SInt32 rangeEnd, Handle hStyledTextData, WEHandle hWE);
pascal OSStatus _WEBuildSoup(SInt32 rangeStart, SInt32 rangeEnd, SInt16 destKind, Handle hSoup, WEHandle hWE);
pascal OSStatus _WEBuildRulerScrap(SInt32 rangeStart, SInt32 rangeEnd, Handle hRulerScrap, WEHandle hWE);
pascal OSStatus _WEBuildParaFormatScrap(SInt32 rangeStart, SInt32 rangeEnd, Handle hParaFormatScrap, WEHandle hWE);
pascal OSStatus _WEBuildStyleScrap(SInt32 rangeStart, SInt32 rangeEnd, OptionBits streamOptions, Handle hStyleScrap, WEHandle hWE);
pascal OSStatus _WEBuildCharFormatScrap(SInt32 rangeStart, SInt32 rangeEnd, Handle hParaFormatScrap, WEHandle hWE);
pascal OSStatus _WEPutScrapHandle(FlavorType dataFlavor, Handle dataHandle);
pascal OSStatus _WEGetUniqueStyles(SInt32 rangeStart, SInt32 rangeEnd, Handle hUniqueStyles, SInt32 * count, WEHandle hWE);
pascal OSStatus _WEGetUniqueRulers(SInt32 rangeStart, SInt32 rangeEnd, Handle hUniqueRulers, SInt32 * count, WEHandle hWE);
pascal UInt32 _WECalcTextEditStyleScrapSize(SInt32 rangeStart, SInt32 rangeEnd, WEHandle hWE);
pascal void _WEFillTextEditStyleScrap(SInt32 rangeStart, SInt32 rangeEnd, void * buffer, WEHandle hWE);
pascal OSStatus _WEParseRulerScrap(Handle hRulerScrap, Handle *hRulerArray);
pascal OSStatus _WEParseStyleScrap(Handle hStyleScrap, Handle *hStyleArray, OptionBits allocFlags, WEFontNameToIDUPP customFontMapper);
pascal void _WEForgetStyleArray(Handle * ioStyleArray);

//	WESelecting.c (private)
INLINE pascal void _WEClearHiliteBit(void); // Motorola 9-Jun-97
pascal SInt16 _WEGetContext(SInt32 offset, WEEdge edge, SInt32 *contextStart, SInt32 *contextEnd,
						WEHandle hWE);
pascal SInt16 _WEGetRestrictedContext(SInt32 offset, SInt32 *contextStart, SInt32 *contextEnd,
						WEHandle hWE);
pascal void _WEGetCaretRect(SInt32 offset, SInt16 direction, Rect *caretRect, WEHandle hWE);
pascal OSStatus _WEDrawCaret(SInt32 offset, SInt16 direction, Boolean useDualCaret, WEHandle hWE);
pascal void _WEBlinkCaret(WEHandle hWE);
pascal void _WEHiliteRange(SInt32 rangeStart, SInt32 rangeEnd, WEHandle hWE);
pascal SInt32 _WECrossDirectionBoundary(SInt32 offset, Boolean movingRight, WEHandle hWE);
pascal SInt32 _WEArrowOffset(SInt16 action, SInt32 offset, WEHandle hWE);
pascal void _WEDoArrowKey (SInt16 arrow, EventModifiers modifiers, WEHandle hWE);
pascal void _WESubtractObjectRgns(RgnHandle mouseRgn, Point portDelta, WEHandle hWE);
pascal Boolean _WEScrollIntoView (SInt32 offset, WEHandle hWE);

// WESelectors.c (private)
extern const WELookupTable _weMainSelectorTable[];
extern const WELookupTable _weObjectHandlerSelectorTable[];
extern const FlavorType _weStandardFlavors[];
extern const FlavorType _weMonoStyledFlavors[];
extern const WESelector _weStyleTags[];
extern const WESelector _weMoreStyleTags[];
extern const WESelector _weUnderlineTags[];
extern const WESelector _weAlignmentTags[];
extern const WESelector _weDirectionTags[];
extern const WESelector _weBorderStyleTags[];
extern const WEAttributeDesc _weAttributeTable[];
extern const WEPasteLookupTable _wePasteLookupTable[];
pascal void _WELookupSelector(const WELookupTable *table, WESelector selector, WEFieldDescriptor *desc);
pascal OSStatus _WEGetField(const WELookupTable *table, WESelector selector, SInt32 *info, void *structure);
pascal OSStatus _WESetField(const WELookupTable *table, WESelector selector, SInt32 *info, void *structure);

// WEUndo.c (private)
pascal OSStatus _WEBuildPrivateStyleScrap(SInt32 rangeStart, SInt32 rangeEnd, Handle hStyleScrap, WEHandle hWE);
pascal OSStatus _WEPrependStyleToPrivateStyleScrap(Handle hStyleScrap, const WETextStyle *pStyle, SInt32 offsetDelta);
pascal OSStatus _WEAppendStyleToPrivateStyleScrap(Handle hStyleScrap, const WETextStyle *pStyle, SInt32 offset);
pascal OSStatus _WEApplyPrivateStyleScrap(SInt32 rangeStart, SInt32 rangeEnd, WEPrivateStyleScrapHandle hStyleScrap, WEHandle hWE);
pascal OSStatus _WEPrependObjectToSoup(Handle hSoup, WEObjectDescHandle hObjectDesc, SInt32 offsetDelta);
pascal OSStatus _WEAppendObjectToSoup(Handle hSoup, WEObjectDescHandle hObjectDesc, SInt16 destKind, SInt32 offset);
pascal OSStatus _WEBuildPrivateRulerScrap(SInt32 rangeStart, SInt32 rangeEnd, Handle hRulerScrap, WEHandle hWE);
pascal OSStatus _WEPrependRulerToPrivateRulerScrap(Handle hRulerScrap, const WERuler *pRuler, SInt32 offsetDelta);
pascal OSStatus _WEAppendRulerToPrivateRulerScrap(Handle hRulerScrap, const WERuler *pRuler, SInt32 offset);
pascal OSStatus _WEApplyPrivateRulerScrap(SInt32 rangeStart, SInt32 rangeEnd, WEPrivateRulerScrapHandle rulerScrap, WEHandle hWE);
pascal void _WEPushAction(WEActionHandle hAction);
pascal OSStatus _WENewAction(SInt32 rangeStart, SInt32 rangeEnd, SInt32 newTextLength,
							WEActionKind actionKind, WEActionFlags actionFlags,
							WEHandle hWE, WEActionHandle *hAction);
pascal void _WEModify(SInt32 rangeStart, SInt32 rangeEnd, SInt32 newTextLength,
					WEActionKind actionKind, WEActionFlags actionFlags, WEHandle hWE);
pascal WEActionHandle _WEDisposeAction(WEActionHandle hAction);
pascal void _WEForgetAction(WEActionHandle *hAction);
pascal OSStatus _WEDoAction(WEActionHandle hAction);
pascal void _WEAdjustUndoRange(SInt32 moreBytes, WEHandle hWE);
pascal WEActionKind _WEGetTypingActionKind(WEHandle hWE);

// WEUnicode.c (private)
extern UnicodeToTextFallbackUPP _weUnicodeToTextFallbackUPP;
extern OptionBits _weUnicodeToTextFallbackFlags;
pascal ScriptCode _WEFontFamilyToScript(SInt16 inFontFamily);
pascal OSStatus _WEFontFamilyToTextEncoding(SInt16 inFontFamily, TextEncoding * outTextEncoding, const WERec * pWE);
pascal OSStatus _WETextEncodingToFontFamily(TextEncoding inEncoding, SInt16 * outFontFamily);
pascal void _WEMapCCsMacToUnicode(UniCharArrayPtr ioUnicodeText, UniCharCount iUnicodeTextLength);
pascal void _WEMapCCsUnicodeToMac(UniCharArrayPtr ioUnicodeText, UniCharCount iUnicodeTextLength);
pascal OSStatus _WESpliceRunArrays
	(
		Handle				inRunArray1,
		Handle				inRunArray2,
		Handle *			outOffsetArray
	) ;
pascal void _WERemapRunArrays
	(
		Handle				inRunArray1,
		Handle				inRunArray2,
		const ByteOffset *	inRemappedOffsets,
		ItemCount			inRemappedOffsetCount
	) ;
pascal void _WEBumpRunArray ( Handle inRunArray, SInt32 inDelta ) ;
pascal OSStatus _WEConvertTextToUnicode
	(
		const char *			inSrcTextPtr,
		UInt32					inSrcTextLength,
		TextToUnicodeInfo 		inConverter,
		OptionBits				inConverterOptions,
		Handle					ioUnicodeText,
		ByteCount *				ioUnicodeTextLength,
		const ByteOffset *		inOffsetArray,
		ByteOffset *			outRemappedOffsetArray,
		ItemCount				inOffsetCount
	) ;
pascal OSStatus _WEConvertUnicodeToMultiScriptText
	(
		ConstUniCharArrayPtr	inUnicodeTextPtr,
		UniCharCount			inUnicodeCharCount,
		Handle					outText,
		Handle					outEncodingScrap
	) ;
pascal void _WEEndianSwap(ConstUniCharArrayPtr inSrcText, UniCharArrayPtr outDstText, UniCharCount inCharCount);
pascal OSStatus _WEConvertUnicodeToText
	(
		const char *			inUnicodeTextPtr,
		ByteCount				inUnicodeTextLength,
		UnicodeToTextInfo		inConverter,
		OptionBits				inConverterOptions,
		Handle					ioConvertedText,
		ByteCount *				ioConvertedTextLength,
		const ByteOffset *		inOffsetArray,
		ByteOffset *			outRemappedOffsetArray,
		ItemCount				inOffsetCount
	) ;
pascal OSStatus _WEConvertStyledUnicode
	(
		const char *			inUnicodeTextPtr,
		ByteCount				inUnicodeTextLength,
		TextEncoding			inUnicodeEncoding,
		Handle					ioCharFormat,
		Handle					ioParaFormat,
		Handle					inStyleArray,
		Handle					outText
	) ;

// WEUtilities.c (private)
pascal void _WEForgetHandle(Handle *h);
pascal void _WEForgetUPP(UniversalProcPtr *upp);
pascal Boolean _WESetHandleLock(Handle h, Boolean lock);
pascal void _WEBlockClr(void *block, Size blockSize);
pascal Boolean _WEBlockCmp(const void *block1, const void *block2, Size blockSize);
pascal void _WEReorder(SInt32 *a, SInt32 *b);
pascal OSStatus _WEAllocate(Size blockSize, OptionBits allocFlags, Handle *h);
pascal OSStatus _WESplice(Handle h, const void *blockPtr, SInt32 blockSize, SInt32 offset);
pascal Size AEGetDescDataSize(const AEDesc *);
pascal OSErr AEGetDescData(const AEDesc *, void *, Size);
pascal OSStatus _WECopyAEDescData(const AEDesc *, Handle);
pascal OSStatus _WECreateNewRgn(RgnHandle * outRgn);
pascal void _WEForgetRgn(RgnHandle * ioRgn);

#if WASTE_SHARED_LIBRARY
#pragma internal reset
#endif

#ifdef __cplusplus
}
#endif

#endif /*__SuperWASTE__*/
