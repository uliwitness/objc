#ifndef __internalstoolbox__
#define __internalstoolbox__
//	SuperCard 4.72 Internals Toolbox .h file
//	Prototypes for all IT routines
//	Copyright 2011 Mark Lucas
//	All rights reserved worldwide.

#ifdef _USE_ROUTINE_DESCRIPTORS_
#undef _USE_ROUTINE_DESCRIPTORS_
#endif

#define _USE_ROUTINE_DESCRIPTORS_ 0

#include "SuperXCmd.h"
#include "SuperWASTE_472.h"
#include "commonExt_472.h"
#include <stdarg.h>


#include <Movies.h>
//#include <Printing.h>

	//	An SCErr is returned by a all Internals Toolbox routines.

typedef short SCErr;

#pragma options align = mac68k

	//	These are the equates for error codes returned by 
	//	those Internals Toolbox routines that return an SCErr.

enum errNum {
	isOK = 0,					//	no error
	noSuchObject = -10000,		//	specified object not found
	noSuchCard = -9999,			//	specified card not found
	noSuchBkgnd = -9998,		//	specified background not found
	noSuchCdBg = -9997,			//	specified card or background not found
	noSuchWind = -9996,			//	specified window not found
	noSuchMenu = -9995,			//	specified menu not found
	noSuchProj = -9994,			//	specified project not found
	badReadType = -9993,		//	invalid card, bkgnd, window, or file type
	badObjType = -9992,			//	invalid object type
	badSpotType = -9991,		//	invalid graphic type
	windNotOpen = -9990,		//	specified window is not currently open
	badRefHdl = -9989,			//	invalid or nil object reference handle
	badIndRange = -9988,		//	supplied index number out of range
	noActiveFld = -9987,		//	no currently active field
	noScript = -9986,			//	specified object has no script
	noSharedFile = -9985,		//	SharedFile project not found
	noSuchStar = -9984,			//	specified project resource not found
	notInColor = -9983,			//	application not running under 8-bit color
	noMemory = -9982,			//	out of memory
	emptyRect = -9981,			//	specified rectangle is empty
	badAddStar = -9980,			//	failed to add new project resource
	badVersion = -9979,			//	invalid SuperCard version
	badMakeSpec = -9978,		//	FSMakeFSSpec failed; spec may be valid
	badNewAlias = -9977,		//	NewAlias failed
	noPictureData = -9976,		//	draw rect graphic has no pictureData
	badObjectInfo = -9975,		//	ObjectInfoHandle is of invalid size
	badObjKind = -9974,			//	ObjectInfo record contains bad object kind
	badObjSelect = -9973,		//	ObjectInfo record contains bad object select mode
	badObjColor = -9972,		//	ObjectInfo record contains bad object color index
	badObjPenSize = -9971,		//	ObjectInfo record contains bad object pen size
	badObjMode = -9970,			//	ObjectInfo record contains bad object transfer mode
	badObjShadow = -9969,		//	ObjectInfo record contains bad object shadow size
	badProcConst = -9968,		//	invalid procedure pointer indentifier
	cantReplace = -9967,		//	a project resource by that name and type exists
	badProcID = -9966,			//	invalid procedure pointer identifier
	badSetStarID = -9965,		//	failed to assign new ID to project resource
	badDataHandle = -9964,		//	attempt to assign invalid data
	badRezID = -9963,			//	attempt to assign invalid resource ID
	cantSetOpenField = -9962,	//	can't set TEHandle of open field
	notByReference = -9961,		//	can't get path of embedded pictureData
	noPictureInfo = -9960,		//	draw graphic has no pictureInfo
	noClutInUse = -9959,		//	no clut currently assigned
	expiredBeta = -9958,		//	Internals Toolbox beta version has expired
	onlyWASTE = -9957,			//	Operation only valid for WASTE flds 
	onlyTextEdit = -9956,		//	Operation only valid for non-WASTE flds 
	badPixel = -9955,			//	Specified pixel is out of range 
	badContextInfo = -9954,		//	ContextInfoHandle handle not allocated
	missingPPCToolbox = -9953,	//	Program to Program Communication not supported on this system
	badSetStarName = -9952,		//	failed to assign new name to project resource
	notInThisVersion = -9951,	//	action is not supported in the host version of SuperCard
	objectNotInContext = -9950,	//	the target object is not in context (i.e., not in an open window)
	badImageType = -9949,		// 	Can't import that image type
	badImageData = -9948,		// 	Encountered an error importing that particular image
	badParamData = -9947,		// 	Invalid parameter passed to call
	unknownErr = -9946			// 	Encountered an unspecified error

};

	//	These are the equates for object types as
	//	used by the CreateObject and ObjectInfo routines.

enum objType {
	typRect = 100,
	typRound,
	typOval,
	typLine,
	typPolygon,
	typBitMap,
	typText,
	typArc,
	typGroup,
	
	typRectBtn = 200,
	typRoundRectBtn,
	typPolygonBtn,
	typRadioBtn,
	typCheckboxBtn,
	typBevelBtn,				// 5
	typPopupBtn,
	typCircularBtn,
	typSliderBtn = 209,
	typTabsBtn,					// 10
	typImageWellBtn,
	typDisclosureBtn,
	typScrollBarBtn,
	typProgressBarBtn,
	typIndeterminateBarBtn,		// 15
	typRelevanceBarBtn,
	typLittleArrowsBtn,
	typChasingArrowsBtn,
	typDisclosureTriangleBtn,
	typPrimaryGroupBtn,			// 20
	typSecondaryGroupBtn,
	typPopupArrowBtn,
	typPlacardBtn,
	typSeparatorBtn = 228,
	typSegmentedBtn = 230,		// 30
	
	typField = 300,
	typScrollField,
	typList,
	typScrollList
};


#ifndef maxstring
#define maxstring 256
#endif

	//	These are the equates for object kinds as
	//	used by the CreateObject and ObjectInfo routines.

enum objKind {
	kindGraphic,
	kindButton,
	kindField
};

	//	These are the equates for object selection
	//	modes as used by the CreateObject and ObjectInfo routines.

enum objSelectMode {
	selNone,
	selRegular,
	selPolygon,
	selLine,
	selRotate,
	selArc
};

	// A union in the ObjectInfo struct below holds different info depending on
	// whether the object is a 'clossic' SC spot or a new SC4 control-based spot
	
typedef struct {
	Pattern fillPat;
	Pattern penPat;
} classic;

typedef struct {
	short value;
	short min;
	short max;
	short view;
	UInt8 type;
	UInt8 ticks;
	UInt16 variant;
	ControlRef control;
} control;

	//	This ObjectInfo structure is used by the ObjectInfo routines.

struct ObjectInfo {
	short kind;							//	kind of object (objKind enums)
	short type;							//	type of object (objType enums)
	long id;							//	id of object
	short select;						//	selection mode of object (objSelect enums)
	short fillFore;						//	clut index for foreground fill color
	short fillBack;						//	clut index for background fill color
	short penFore;						//	clut index for foreground pen color
	short penBack;						//	clut index for background pen color
	short penWidth;						//	pixel width of pen
	short penHeight;					//	pixel height of pen
	short mode;							//	object transfer mode
	short shadow;						//	pixel size of shadow
	short textFont;						//	valid for buttons only; title font number
	short textSize;						//	valid for buttons only; title font size
	short textFace;						//	valid for buttons only; title font style
	short textJust;						//	valid for buttons only; title justification
	long icon;							//	valid for buttons only; icon resource id
	union {
		classic sc3;
		control sc4;
	} rev;
	unsigned short visible : 1;			//	visible object propety
	unsigned short showName : 1;		//	showName object property
	unsigned short showFill : 1;		//	showFill object property
	unsigned short showPen : 1;			//	showPen object property
	unsigned short locked : 1;			//	locked object property
	unsigned short autoHilite : 1;		//	valid for buttons only; autoHilite button property
	unsigned short disabled : 1;		//	valid for buttons only; disabled button property
	unsigned short hilite : 1;			//	valid for buttons only; hilite button property
	unsigned short autoWidth : 1;		//	valid for buttons only; autoWidth button property
	unsigned short popArrow : 1;		//	valid for buttons only; popArrow button property
	unsigned short lockText : 1;		//	valid for fields only; lockText field property
	unsigned short showLines : 1;		//	valid for fields only; showLines field property
	unsigned short wideMargins : 1;		//	valid for fields only; wideMargins field property
	unsigned short autoTab : 1;			//	valid for fields only; autoTab field property
	unsigned short dontWrap : 1;		//	valid for fields only; dontWrap field property
	unsigned short dontSearch : 1;		//	valid for fields only; dontSearch field property
	unsigned short allowDrag : 1;		//	allowDrag property of object
	unsigned short allowDrop : 1;		//	allowDrop property of object
	unsigned short mixedValue : 1;		//	mixedValue property of object
	unsigned short oldFashioned : 1;	//	oldFashioned property of object
	unsigned short useWASTE : 1;		//	valid for fields and text grcs only; useWASTE property of object
	unsigned short isControl : 1;		//	is object a new control-based btn?
	unsigned short autoBackground : 1;	//	autoBackground object property
	unsigned short showFrame : 1;		//	valid for fields only; showfldframe field property
	unsigned short autoDim : 1;			//	autoDim object property
	unsigned short focusHilite : 1;		//	focusHilite object property
	unsigned short allowObjects : 1;	//	valid for fields only; allowObjects field property
	unsigned short allowTabs : 1;		//	valid for fields only; allowTabs field property
	Rect bounds;						//  local rect of object
	Handle name;						//  object name 0->none
};

typedef struct ObjectInfo ObjectInfo;
typedef ObjectInfo *ObjectInfoPtr;
typedef ObjectInfoPtr *ObjectInfoHandle;

	//	The ScriptInfo record is used with the SCIT routines
	//	that get and set object script attributes.

struct ScriptInfo {
	short textFont;		//	font number
	short textSize;		//	point size
	short tabWidth;		//	character tab width
	long insert;		//	insertion point offset
	long scroll;		//	pixel scroll value
};

typedef struct ScriptInfo ScriptInfo;
typedef ScriptInfo *ScriptInfoPtr;

#ifndef __commonprivate__
//#ifndef __windtypes
//#define __windtypes
// Window style information
enum windtype {
	typereg,
	typebars,
	typecurve,
	typedlog,
	typeplain,
	typeshad,
	typepal,
	typemove,
	typecustom,
	typecustompal,
	typecustomove
};
#endif	//ndef __windtypes

	//	This ContextInfo structure is used by the ContextInfo routines.
	
enum {
	eCardObject,
	eBackObject,
	eCard,
	eBkgnd,
	eWindow,
	eProject
};

struct ContextInfo {
	long windtype;
	long objectNum;
	long objectID;
	long objectPart;
	long objectKind;
	long objectType;
	short objectSelect;
	long cardNum;
	long cardID;
	long backID;
	long windNum;
	long windID;
	short windStyle;
	short windOpen;
	short windVisible;
	short editBG;
	Point backSize;
	Point windScroll;
	Rect windRect;
	unsigned char objectName[256];
	unsigned char cardName[256];
	unsigned char backName[256];
	unsigned char windName[256];
	unsigned char projectName[256];
	unsigned char projectPath[2048];
};

typedef struct ContextInfo ContextInfo;
typedef ContextInfo *ContextInfoPtr;
typedef ContextInfoPtr *ContextInfoHandle;


	//	The BrushesHandle contains the data for all 64 brush shapes
	//	within a given project.  Used by the GetBrushes function.

typedef short Brush[16];

struct Brushes {
	Brush theBrushes[64];
};

typedef struct Brushes Brushes;
typedef Brushes *BrushesPtr;
typedef BrushesPtr *BrushesHandle;

	//	The PatternsHandle contains the data for all 64 patterns
	//	within a given project.  Used by the GetPatterns function.

struct Patterns {
	Pattern thePats[64];
};

typedef struct Patterns Patterns;
typedef Patterns *PatternsPtr;
typedef PatternsPtr *PatternsHandle;

	//	The MovieInfo record is used with the GetIndMovieInfo function
	//	to obtain data regarding an asynchronous QuickTime movie.

typedef struct {
	long instance;			//	QTVRInstance instance;
	short allowqtvrmsgs;
	short swingtrans;
	long swingspeed;
	long swingdir;
} qtvr;

typedef struct {
	short			initial;
	short			playflag;
	short			refnum;
	WindowPtr		window;
	Movie 			movie;
	MovieController controller;
	qtvr 			qtvrinfo;
	Rect 			bounds;
	FSSpec 			fileSpec;
	Fixed 			speed;
	RgnHandle 		clipRgn;
	QTCallBack		callback;
	TimeValue		calltime;
	short			allowcallbacks;
} MovieInfo, *MovieInfoPtr;

typedef struct {
	long			fStorageMode;				// how we are storing
	Rect			fImageRect;
	Rect			fSourceRect;
	Rect			fDestRect;
	long			flags;						
	long			flagmask;					
	long			fAspectMode;				// this is fit or fill
	short			spare1;
	RGBColor		fOpColor;					// the blitting op color, use the grapic mode
	float			fZoom;						// basic zoom -- not used
	short			spare2;						
	float			fMag;						// for the magnifying glass
	short			spare3;
	Point			fOffset;					// delta away from the natural center -- not used
	short			spare4;					
	short			spare5;
	short			spare6;
	Rect			unpinnedestrect;
	Rect			unpinnedsourcerect;
	long			spare7;
	long			spare8;
	long			spare9;
	long			spare10;
} PictureDataInfo, *PDInfoPtr, **PDInfoHandle;

typedef enum {
	eCLIP,
	eFIT,
	eFILL,
	eRESET,
	eCENTER,
	eREPEAT
} eGraphType ;

typedef enum {
	eEmbedded,
	eUsepath
} eSourceType;

enum CurFieldRecType {
	eTextEditRec = 0,
	eWasteRec
};

enum eFieldType {
	eUnknownType = 0,
	eTextOnlyField,
	eAllowObjectsField
};

typedef struct {
	unsigned char *scan;
	long hor;
	long ver;
	short count;
	short usetext;
	Handle selhand;
	unsigned char rep1[maxstring];
	unsigned char rep2[maxstring];
	unsigned char with[maxstring];
	unsigned char flags;
} asklistparms, *asklistparmsptr;

enum {
	answernone,
	answerfile,
	answerfolder
};

/* Typedefs 					*/
typedef enum {
	eHANDLEDATA= 1,
	eBITDATA,
	eFROMPOINTERDATA,
	eBADATA
} pictType;

typedef struct {
	GWorldPtr		fTheBuffer;
	Rect			fBounds;
	short			fDepth;
	PixMapHandle	fThePixMap;
	short			fRowBytes;
} OffScreenBuffer, **OffScreenBuffHandle;

typedef struct {
	pictType			type;
	Rect				bounds;
	Handle 				name;
	PicHandle 			thepict;
	OffScreenBuffer		theBuff;
	long time;
} pict;


#pragma options align = reset


#define pictOriginChanged 		0x00000001
#define pictOpColorvalid 		0x00000002
#define pictZoomValid	 		0x00000004
#define pictMagValid	 		0x00000008
#define pictSrcOffsetValid	 	0x00000010
#define pictSrcOffsetRectValid	0x00000020
#define pictSourceRectValid	 	0x00000040
#define pictDestRectValid	 	0x00000080
#define pictStorageValid	 	0x00000100
#define pictAspectValid	 		0x00000200

#define pictDontCache 			0x00010000
#define pictDestRectLocked	 	0x00020000
#define pictSrcRectLocked	 	0x00040000

#if TARGET_API_MAC_CARBON
#define vgetgaddr 2
#else
#define vgetgaddr 1
#endif

#define vers30 30
#define vers35 35
#define vers36 36
#define vers361 361
#define vers40 40
#define vers45 45
#define vers46 46
#define vers47 47


/* --------------------------------------------------------------------------------------------------------------------------------------------------------------

//	Prototypes for the Internals Toolbox routines. These don't actually do anything, they're just here for you to copy from...

SCErr AddProjStar				(XCmdPtr par, StringPtr descriptString, Handle theData, StringPtr theName, ResType theType, Boolean replace, long *newID);
SCErr AddProjStarLong			(XCmdPtr par, Handle descriptString, Handle theData, StringPtr theName, ResType theType, Boolean replace, long *newID);
SCErr AddProjStarByIDLong		(XCmdPtr par, Handle descriptString, Handle theData, StringPtr theName, ResType theType, long theID, Boolean replace);
SCErr AddSFStar					(XCmdPtr par, Handle theData, StringPtr theName, ResType theType, Boolean replace, long *newID);
SCErr Answer					(XCmdPtr par, unsigned char *prompt, unsigned char *p1, unsigned char *p2, unsigned char *p3, short *answer);
SCErr AnswerFile				(XCmdPtr par, unsigned char *prompt, unsigned char *type1, unsigned char *type2, unsigned char *type3, unsigned char *result, short *vRefNum, long *parID);
SCErr AnswerFileLong			(XCmdPtr par, unsigned char *prompt, unsigned char *type1, unsigned char *type2, unsigned char *type3, unsigned char *ext1, unsigned char *ext2, unsigned char *ext3, Handle *result, short *vRefNum, long *parID);
SCErr AnswerFolder				(XCmdPtr par, unsigned char *prompt, unsigned char *result, short *vRefNum, long *parID);
SCErr AnswerFolderLong			(XCmdPtr par, unsigned char *prompt, Handle *result, short *vRefNum, long *parID);
SCErr AnswerProgram				(XCmdPtr par, unsigned char *prompt, unsigned char *type, unsigned char *result);
SCErr Ask						(XCmdPtr par, unsigned char *prompt, unsigned char *defaultstr, unsigned char *enterdata, short passwd, short *answer);
SCErr AskFile					(XCmdPtr par, unsigned char *prompt, unsigned char *defaultstr, unsigned char *path, short *result, short *vRefNum, long *parID);
SCErr AskFileLong				(XCmdPtr par, unsigned char *prompt, unsigned char *defaultstr, Handle *path, short *result, short *vRefNum, long *parID);
SCErr AskList					(XCmdPtr par, asklistparmsptr lp, Handle *result, short *answer);
SCErr CountMovies				(XCmdPtr par, long *numMovies);
SCErr CountObjects				(XCmdPtr par, StringPtr descriptString, short *numObjects);
SCErr CountObjectsLong			(XCmdPtr par, Handle descriptString, short *numObjects);
SCErr CountProjStars			(XCmdPtr par, StringPtr descriptString, long *numStars);
SCErr CountProjStarsLong		(XCmdPtr par, Handle descriptString, long *numStars);
SCErr CountSFStars				(XCmdPtr par, long *numStars);
SCErr CreateDrawReg				(XCmdPtr par, StringPtr descriptString, short theType, Rect *theRect, Point point1, Point point2, Handle theData);
SCErr CreateDrawRegLong			(XCmdPtr par, Handle descriptString, short theType, Rect *theRect, Point point1, Point point2, Handle theData);
SCErr CreateObject				(XCmdPtr par, StringPtr descriptString, short theKind, short theType, Rect *theRect, Point point1, Point point2, Handle theData);
SCErr CreateObjectLong			(XCmdPtr par, Handle descriptString, short theKind, short theType, Rect *theRect, Point point1, Point point2, Handle theData);
SCErr DelProjStarByID			(XCmdPtr par, StringPtr descriptString, long theID, ResType theType);
SCErr DelProjStarByIDLong		(XCmdPtr par, Handle descriptString, long theID, ResType theType);
SCErr DelProjStarByName			(XCmdPtr par, StringPtr descriptString, StringPtr theName, ResType theType);
SCErr DelProjStarByNameLong		(XCmdPtr par, Handle descriptString, StringPtr theName, ResType theType);
SCErr DelSFStarByID				(XCmdPtr par, long theID, ResType theType);

SCErr DelSFStarByName			(XCmdPtr par, StringPtr theName, ResType theType);
SCErr DrawCard					(XCmdPtr par, StringPtr descriptString);
SCErr DrawCardLong				(XCmdPtr par, Handle descriptString);
SCErr DrawObject				(XCmdPtr par, StringPtr descriptString);
SCErr DrawObjectLong			(XCmdPtr par, Handle descriptString);
SCErr DrawObjectByIndex			(XCmdPtr par, StringPtr descriptString, short index);
SCErr DrawObjectByIndexLong		(XCmdPtr par, Handle descriptString, short index);
SCErr DrawObjects				(XCmdPtr par, StringPtr descriptString);
SCErr DrawObjectsLong			(XCmdPtr par, Handle descriptString);
SCErr GetApplResRef				(XCmdPtr par, short *resRef);
SCErr GetApplVolRef				(XCmdPtr par, short *volRef);
SCErr GetBackClut				(XCmdPtr par, StringPtr descriptString, CTabHandle *theClut);
SCErr GetBackClutLong			(XCmdPtr par, Handle descriptString, CTabHandle *theClut);
SCErr GetBackTolerance			(XCmdPtr par, StringPtr descriptString, short *tolerance);
SCErr GetBackToleranceLong		(XCmdPtr par, Handle descriptString, short *tolerance);
SCErr GetBits					(XCmdPtr par, StringPtr descriptString, PixInfoPtr theInfo);
SCErr GetBitsLong				(XCmdPtr par, Handle descriptString, PixInfoPtr theInfo);
SCErr GetBrushes				(XCmdPtr par, StringPtr descriptString, BrushesHandle *theBrushes);
SCErr GetBrushesLong			(XCmdPtr par, Handle descriptString, BrushesHandle *theBrushes);
SCErr GetCardClut				(XCmdPtr par, StringPtr descriptString, CTabHandle *theClut);
SCErr GetCardClutLong			(XCmdPtr par, Handle descriptString, CTabHandle *theClut);
SCErr GetCardTolerance			(XCmdPtr par, StringPtr descriptString, short *tolerance);
SCErr GetCardToleranceLong		(XCmdPtr par, Handle descriptString, short *tolerance);

SCErr GetContextInfo			(XCmdPtr par, StringPtr descrip, ContextInfoHandle *infohand);
SCErr GetContextInfoLong		(XCmdPtr par, Handle descrip, ContextInfoHandle *infohand);
SCErr GetCurCTabHandle			(XCmdPtr par, CTabHandle *theClut);
SCErr GetCurEventRec			(XCmdPtr par, EventRecord *eventRec);
SCErr GetCurPrintRec			(XCmdPtr par, THPrint *printRec);
SCErr GetCurWEHandle			(XCmdPtr par, WEHandle *editHand);
SCErr GetFindRect				(XCmdPtr par, Rect *theRect);
SCErr GetGlobals				(XCmdPtr par, globptr *);
SCErr GetIndMovieInfo			(XCmdPtr par, long index, MovieInfo *theMovie);
SCErr GetLinePoints				(XCmdPtr par, StringPtr descriptString, Point *startPoint, Point *endPoint);
SCErr GetLinePointsLong			(XCmdPtr par, Handle descriptString, Point *startPoint, Point *endPoint);
SCErr GetListHandle				(XCmdPtr par, StringPtr descriptString, ListHandle *theList);
SCErr GetListHandleLong			(XCmdPtr par, Handle descriptString, ListHandle *theList);
SCErr GetMsgHandle				(XCmdPtr par, Handle *texthand);
SCErr GetMsgResultStr			(XCmdPtr par, StringPtr theString);

SCErr GetMsgTEHandle			(XCmdPtr par, TEHandle *editHand);
SCErr GetMsgWindowPtr			(XCmdPtr par, WindowPtr *theWindow);
SCErr GetObjectData				(XCmdPtr par, StringPtr descriptString, Handle *dataHand);
SCErr GetObjectDataLong			(XCmdPtr par, Handle descriptString, Handle *dataHand);
SCErr GetObjectInfo				(XCmdPtr par, StringPtr descriptString, ObjectInfoHandle *infoHand);
SCErr GetObjectInfoLong			(XCmdPtr par, Handle descriptString, ObjectInfoHandle *infoHand);
SCErr GetObjectInfoByIndex		(XCmdPtr par, StringPtr descrip, short index, ObjectInfoHandle *infohand);
SCErr GetObjectInfoByIndexLong	(XCmdPtr par, Handle descrip, short index, ObjectInfoHandle *infohand);
SCErr GetObjectScript			(XCmdPtr par, StringPtr descriptString, Handle *scriptHand);
SCErr GetObjectScriptLong		(XCmdPtr par, Handle descriptString, Handle *scriptHand);
SCErr GetPaintInfo				(XCmdPtr par, StringPtr descrip, PixInfoPtr theInfo);
SCErr GetPaintInfoLong			(XCmdPtr par, Handle descrip, PixInfoPtr theInfo);
SCErr GetPaintPixel				(XCmdPtr par, StringPtr descriptString, Point pt, short *color);
SCErr GetPaintPixelLong			(XCmdPtr par, Handle descriptString, Point pt, short *color);
SCErr GetPatterns				(XCmdPtr par, StringPtr descriptString, PatternsHandle *thePatterns);
SCErr GetPatternsLong			(XCmdPtr par, Handle descriptString, PatternsHandle *thePatterns);
SCErr GetPictureData			(XCmdPtr par, StringPtr descriptString, PicHandle *thePicture);
SCErr GetPictureDataLong		(XCmdPtr par, Handle descriptString, PicHandle *thePicture, Boolean noCopy);
SCErr GetPictureDataBuffer		(XCmdPtr par, Handle descriptString, pict *);
SCErr GetPictureInfo			(XCmdPtr par, StringPtr descriptString, PDInfoHandle *infoHand);
SCErr GetPictureInfoLong		(XCmdPtr par, Handle descriptString, PDInfoHandle *infoHand);
SCErr GetPictureMode			(XCmdPtr par, StringPtr descriptString, long *mode);
SCErr GetPictureModeLong		(XCmdPtr par, Handle descriptString, long *mode);
SCErr GetPicturePath			(XCmdPtr par, StringPtr descriptString, StringPtr path);
SCErr GetPicturePathLong		(XCmdPtr par, Handle descriptString, Handle *path);
SCErr GetPolyHandle				(XCmdPtr par, StringPtr descriptString, PolyHandle *thePoly);
SCErr GetPolyHandleLong			(XCmdPtr par, Handle descriptString, PolyHandle *thePoly);
SCErr GetPouchVolRef			(XCmdPtr par, short *volRef);

SCErr GetPrivateNum				(XCmdPtr par, StringPtr descriptString, long *theNum);
SCErr GetPrivateNumLong			(XCmdPtr par, Handle descriptString, long *theNum);
SCErr GetProjAlias				(XCmdPtr par, StringPtr descriptString, AliasHandle *theAlias);
SCErr GetProjAliasLong			(XCmdPtr par, Handle descriptString, AliasHandle *theAlias);
SCErr GetProjFSSpec				(XCmdPtr par, StringPtr descriptString, FSSpec *theSpec);
SCErr GetProjFSSpecLong			(XCmdPtr par, Handle descriptString, FSSpec *theSpec);
SCErr GetProjResRef				(XCmdPtr par, StringPtr descriptString, short *resRef);
SCErr GetProjResRefLong			(XCmdPtr par, Handle descriptString, short *resRef);
SCErr GetProjStarByID			(XCmdPtr par, StringPtr descriptString, long theID, ResType theType, Handle *dataHand);
SCErr GetProjStarByIDLong		(XCmdPtr par, Handle descriptString, long theID, ResType theType, Handle *dataHand);
SCErr GetProjStarByName			(XCmdPtr par, StringPtr descriptString, StringPtr theName, ResType theType, Handle *dataHand);
SCErr GetProjStarByNameLong		(XCmdPtr par, Handle descriptString, StringPtr theName, ResType theType, Handle *dataHand);
SCErr GetProjStarInfoByID		(XCmdPtr par, StringPtr descriptString, long theID, ResType theType, StarInfo *theInfo);
SCErr GetProjStarInfoByIDLong	(XCmdPtr par, Handle descriptString, long theID, ResType theType, StarInfo *theInfo);
SCErr GetProjStarInfoByName		(XCmdPtr par, StringPtr descriptString, StringPtr theName, ResType theType, StarInfo *theInfo);
SCErr GetProjStarInfoByNameLong	(XCmdPtr par, Handle descriptString, StringPtr theName, ResType theType, StarInfo *theInfo);
SCErr GetProjStarInfoByNum		(XCmdPtr par, StringPtr descriptString, long thenum, StarInfo *theinfo);
SCErr GetProjStarInfoByNumLong	(XCmdPtr par, Handle descriptString, long thenum, StarInfo *theinfo);
SCErr GetProjVolRef				(XCmdPtr par, StringPtr descriptString, short *volRef);
SCErr GetProjVolRefLong			(XCmdPtr par, Handle descriptString, short *volRef);

SCErr GetScriptAttrs			(XCmdPtr par, StringPtr descriptString, ScriptInfo *theInfo);
SCErr GetScriptAttrsLong		(XCmdPtr par, Handle descriptString, ScriptInfo *theInfo);
SCErr GetSFResRef				(XCmdPtr par, short *resRef);
SCErr GetSFStarByID				(XCmdPtr par, long theID, ResType theType, Handle *dataHand);
SCErr GetSFStarByName			(XCmdPtr par, StringPtr theName, ResType theType, Handle *dataHand);
SCErr GetSFStarInfoByID			(XCmdPtr par, long theid, ResType thetype, StarInfo *theinfo);
SCErr GetSFStarInfoByName		(XCmdPtr par, StringPtr theName, ResType thetype, StarInfo *theinfo);
SCErr GetSFStarInfoByNum		(XCmdPtr par, long thenum, StarInfo *theinfo);
SCErr GetStdLibProcPtr			(XCmdPtr par, long procid, ProcPtr *theproc);
//SCErr GetTEHandle				(XCmdPtr par, StringPtr descriptString, TEHandle *editHand);
SCErr GetUIWEHandle				(XCmdPtr par, StringPtr descriptString, WEHandle *editHand);
SCErr GetUIWEHandleLong			(XCmdPtr par, Handle descriptString, WEHandle *editHand);
SCErr GetWEHandle				(XCmdPtr par, StringPtr descriptString, WEHandle *editHand);
SCErr GetWEHandleLong			(XCmdPtr par, Handle descriptString, WEHandle *editHand);
SCErr GetWindowID				(XCmdPtr par, WindowPtr thewindow, StringPtr descrip);
SCErr GetWindowIDLong			(XCmdPtr par, WindowPtr thewindow, Handle *descrip);
SCErr GetWindowPtr				(XCmdPtr par, StringPtr descriptString, WindowPtr *theWindow);
SCErr GetWindowPtrLong			(XCmdPtr par, Handle descriptString, WindowPtr *theWindow);
SCErr ImageCurCard				(XCmdPtr par, GWorldPtr *theworld, RgnHandle *theVisRgn);
SCErr ImageFileToPICT			(XCmdPtr par, StringPtr path, PicHandle *thePict);
SCErr ImageFileToPICTLong		(XCmdPtr par, Handle path, PicHandle *thePict);

SCErr IndentScript				(XCmdPtr par, Handle *theScript, long *startSel, long *endSel, short tabWidth);
SCErr IndexToObject				(XCmdPtr par, StringPtr descriptString, short index, StringPtr objectStr);
SCErr IndexToObjectLong			(XCmdPtr par, Handle descriptString, short index, Handle *objectStr);
SCErr IndexToObjectID			(XCmdPtr par, StringPtr descrip, short index, StringPtr objectstring);
SCErr IndexToObjectIDLong		(XCmdPtr par, Handle descrip, short index, Handle *objectstring);
OSErr IsDFResourceFile			(XCmdPtr par, Handle path, Boolean *isDFRezFile);
SCErr InStandalone				(XCmdPtr par, Boolean *isStand);
SCErr IsOpenField				(XCmdPtr par, StringPtr descriptString, Boolean *isOpen);
SCErr IsOpenFieldLong			(XCmdPtr par, Handle descriptString, Boolean *isOpen);
OSErr IsProjectFile				(XCmdPtr par, Handle path, Boolean *isProjFile);
OSErr IsRFResourceFile			(XCmdPtr par, Handle path, Boolean *isRFRezFile);
SCErr IsStandalone				(XCmdPtr par, StringPtr descriptString, Boolean *isStand);
SCErr IsStandaloneLong			(XCmdPtr par, Handle descriptString, Boolean *isStand);
SCErr MakeMenuHandle			(XCmdPtr par, StringPtr descriptString, MenuHandle *theMenu, short theID);
SCErr MakeMenuHandleLong		(XCmdPtr par, Handle descriptString, MenuHandle *theMenu, short theID);
SCErr MakeThumbnail				(XCmdPtr par, StringPtr descriptString, Boolean contentOnly, Boolean ignoreBars, long scale, PicHandle *thePict);
SCErr MakeThumbnailLong			(XCmdPtr par, Handle descriptString, Boolean contentOnly, Boolean ignoreBars, long scale, PicHandle *thePict);
SCErr NoMemory					(XCmdPtr par, long needed, Boolean *result);
SCErr ObjectToIndex				(XCmdPtr par, StringPtr descriptString, short *index);
SCErr ObjectToIndexLong			(XCmdPtr par, Handle descriptString, short *index);
SCErr PackText					(XCmdPtr par, Handle *textHand, TEHandle editHand);
SCErr ParamIsByReference		(XCmdPtr par, short index, Boolean *result);
SCErr PtInObject				(XCmdPtr par, StringPtr descriptString, Point thePoint, Boolean *result);
SCErr PtInObjectLong			(XCmdPtr par, Handle descriptString, Point thePoint, Boolean *result);
SCErr SetBackTolerance			(XCmdPtr par, StringPtr descriptString, short tolerance);
SCErr SetBackToleranceLong		(XCmdPtr par, Handle descriptString, short tolerance);
SCErr SetBits					(XCmdPtr par, StringPtr descriptString, PixInfoPtr theInfo);
SCErr SetBitsLong				(XCmdPtr par, Handle descriptString, PixInfoPtr theInfo);
SCErr SetBrushes				(XCmdPtr par, StringPtr descriptString, BrushesHandle theBrushes);
SCErr SetBrushesLong			(XCmdPtr par, Handle descriptString, BrushesHandle theBrushes);

SCErr SetCardTolerance			(XCmdPtr par, StringPtr descriptString, short tolerance);
SCErr SetCardToleranceLong		(XCmdPtr par, Handle descriptString, short tolerance);
SCErr SetLinePoints				(XCmdPtr par, StringPtr descrip, Point startpt, Point endpt, short redraw);
SCErr SetLinePointsLong			(XCmdPtr par, Handle descrip, Point startpt, Point endpt, short redraw);
SCErr SetMsgResultStr			(XCmdPtr par, StringPtr theString);
SCErr SetObjectData				(XCmdPtr par, StringPtr descriptString, Handle dataHand);
SCErr SetObjectDataLong			(XCmdPtr par, Handle descriptString, Handle dataHand);
SCErr SetObjectInfo				(XCmdPtr par, StringPtr descriptString, ObjectInfoHandle infoHand, short redraw);
SCErr SetObjectInfoLong			(XCmdPtr par, Handle descriptString, ObjectInfoHandle infoHand, short redraw);
SCErr SetObjectInfoByIndex		(XCmdPtr par, StringPtr descrip, short index, ObjectInfoHandle infohand, short redraw);
SCErr SetObjectInfoByIndexLong	(XCmdPtr par, Handle descrip, short index, ObjectInfoHandle infohand, short redraw);
SCErr SetObjectScript			(XCmdPtr par, StringPtr descriptString, Handle scriptHand);
SCErr SetObjectScriptLong		(XCmdPtr par, Handle descriptString, Handle scriptHand);
SCErr SetPaintPixel				(XCmdPtr par, StringPtr descriptString, Point pt, short color, short redraw);
SCErr SetPaintPixelLong			(XCmdPtr par, Handle descriptString, Point pt, short color, short redraw);
SCErr SetPatterns				(XCmdPtr par, StringPtr descriptString, PatternsHandle thePatterns);
SCErr SetPatternsLong			(XCmdPtr par, Handle descriptString, PatternsHandle thePatterns);
SCErr SetPictureData			(XCmdPtr par, StringPtr descrip, Handle theData, Boolean embedded, short redraw);
SCErr SetPictureDataLong		(XCmdPtr par, Handle descrip, Handle theData, Boolean embedded, short redraw);
SCErr SetPictureInfo			(XCmdPtr par, StringPtr descrip, PDInfoHandle infoHand, short redraw);
SCErr SetPictureInfoLong		(XCmdPtr par, Handle descrip, PDInfoHandle infoHand, short redraw);
SCErr SetPolyHandle				(XCmdPtr par, StringPtr descriptString, PolyHandle thePoly, short redraw);
SCErr SetPolyHandleLong			(XCmdPtr par, Handle descriptString, PolyHandle thePoly, short redraw);
SCErr SetPrivateNum				(XCmdPtr par, StringPtr descriptString, long theNum);
SCErr SetPrivateNumLong			(XCmdPtr par, Handle descriptString, long theNum);
SCErr SetProjStarID				(XCmdPtr par, StringPtr descriptString, long theID, ResType theType, long newID, Boolean replace);
SCErr SetProjStarIDLong			(XCmdPtr par, Handle descriptString, long theID, ResType theType, long newID, Boolean replace);
SCErr SetProjStarName			(XCmdPtr par, StringPtr descriptString, long theID, ResType theType, StringPtr newName);
SCErr SetProjStarNameLong		(XCmdPtr par, Handle descriptString, long theID, ResType theType, StringPtr newName);
SCErr SetScriptAttrs			(XCmdPtr par, StringPtr descriptString, ScriptInfo *theInfo);
SCErr SetScriptAttrsLong		(XCmdPtr par, Handle descriptString, ScriptInfo *theInfo);
SCErr SetSFStarID				(XCmdPtr par, long theID, ResType theType, long newID, Boolean replace);
SCErr SetSFStarName				(XCmdPtr par, long theID, ResType theType, StringPtr newName);
SCErr SetSuppressionFlag		(XCmdPtr par, Boolean suppress);
//SCErr SetTEHandle				(XCmdPtr par, StringPtr descriptString, TEHandle editHand);
SCErr SetWEHandle				(XCmdPtr par, StringPtr descriptString, WEHandle editHand);
SCErr SetWEHandleLong			(XCmdPtr par, Handle descriptString, WEHandle editHand);
SCErr TouchCurWEHandle			(XCmdPtr par);
SCErr TouchUIWEHandle			(XCmdPtr par, StringPtr descrip, short writethrough);
SCErr TouchUIWEHandleLong		(XCmdPtr par, Handle descrip, short writethrough);
SCErr UnPackText				(XCmdPtr par, Handle textHand, TEHandle *editHand, Rect *dest, Rect *view, long dontWrap);
SCErr UpdateWindow				(XCmdPtr par, StringPtr descrip, Rect *area);
SCErr UpdateWindowLong			(XCmdPtr par, Handle descrip, Rect *area);


SCErr weActivate				(XCmdPtr par, WEHandle we);
short weAllowsObjects			(XCmdPtr par, WEHandle we);
SCErr weBuildFontTable			(XCmdPtr par, WEHandle we, Handle hFontTable, WEFontIDToNameUPP fontIDToNameProc);
SCErr weCalText					(XCmdPtr par, WEHandle we);
SCErr weCanPaste				(XCmdPtr par, WEHandle we, Boolean *canPaste);
SCErr weCharByte				(XCmdPtr par, WEHandle we, long offset, short *byte);
SCErr weCharType				(XCmdPtr par, WEHandle we, long offset, short *type);
SCErr weClick					(XCmdPtr par, WEHandle we, Point mouseLoc, EventModifiers modifiers, unsigned long clickTime);
SCErr weContinuousStyle			(XCmdPtr par, WEHandle we, WEStyleMode *mode, TextStyle *ts);
SCErr weCopy					(XCmdPtr par, WEHandle we);
SCErr weCopyFieldToField		(XCmdPtr par, WEHandle weSRC, SInt32 srcBegin, SInt32 srcEnd, WEHandle weDST, SInt32 dstBegin, SInt32 dstEnd);
SCErr weCopyRange				(XCmdPtr par, WEHandle we, SInt32 rangeStart, SInt32 rangeEnd, Handle hText, Handle hStyles, Handle hSoup);
SCErr weCountLines				(XCmdPtr par, WEHandle we, long *numLines);
SCErr weCut						(XCmdPtr par, WEHandle we);
SCErr weDelete					(XCmdPtr par, WEHandle we);
SCErr weDeactivate				(XCmdPtr par, WEHandle we);
SCErr weDispose					(XCmdPtr par, WEHandle we);
SCErr weFindLine				(XCmdPtr par, WEHandle we, long offset, WEEdge edge, long *startChar, long *endChar);
SCErr weFindParagraph			(XCmdPtr par, WEHandle we, long offset, WEEdge edge, long *startChar, long *endChar);
SCErr weFindWord				(XCmdPtr par, WEHandle we, long offset, WEEdge edge, long *startChar, long *endChar);
SCErr weGetChar					(XCmdPtr par, WEHandle we, long offset, SInt16 *c);
SCErr weGetHeight				(XCmdPtr par, WEHandle we, long startChar, long endChar, long *height);
SCErr weGetMargins				(XCmdPtr par, WEHandle we, Rect *margins);
SCErr weGetObjectAtOffset		(XCmdPtr par, WEHandle we, const SInt32 offset, WEObjectDescHandle *inObjectDesc);
SCErr weGetObjectBaseline		(XCmdPtr par, WEObjectDescHandle inObjectDesc, SInt16 *baseline);
SCErr weGetObjectByID			(XCmdPtr par, WEHandle we, const SInt32 ID, WEObjectDescHandle *inObjectDesc);
SCErr weGetObjectByIndex		(XCmdPtr par, WEHandle we, const SInt32 index, WEObjectDescHandle *inObjectDesc);
SCErr weGetObjectByName			(XCmdPtr par, WEHandle we, const Handle name, WEObjectDescHandle *inObjectDesc);
SCErr weGetObjectCount			(XCmdPtr par, WEHandle we, SInt32 *count);
SCErr weGetObjectFrame			(XCmdPtr par, WEObjectDescHandle inObjectDesc, LongRect *frame);
SCErr weGetObjectID				(XCmdPtr par, WEObjectDescHandle inObjectDesc, SInt32 *ID);
SCErr weGetObjectImage			(XCmdPtr par, WEObjectDescHandle inObjectDesc, PicHandle *thePict);
SCErr weGetObjectName			(XCmdPtr par, WEObjectDescHandle inObjectDesc, Handle *name);
SCErr weGetObjectOwner			(XCmdPtr par, WEObjectDescHandle inObjectDesc, WEHandle *we);
SCErr weGetObjectProperty		(XCmdPtr par, WEObjectDescHandle inObjectDesc, OSType owner, OSType tag, Handle *data);
SCErr weGetObjectRefCon			(XCmdPtr par, WEObjectDescHandle inObjectDesc, SInt32 *refcon);
SCErr weGetObjectType			(XCmdPtr par, WEObjectDescHandle inObjectDesc, FlavorType *type);
SCErr weGetOffset				(XCmdPtr par, WEHandle we, const LongPt *thePoint, WEEdge *edge, long *offset);
SCErr weGetPoint				(XCmdPtr par, WEHandle we, long offset, SInt16 direction, LongPt *thePoint, SInt16 *lineHeight);
SCErr weGetSelection			(XCmdPtr par, WEHandle we, long *startChar, long *endChar);
SCErr weGetText					(XCmdPtr par, WEHandle we, Handle *text);
SCErr weGetTextLength			(XCmdPtr par, WEHandle we, long *length);
SCErr weInsert					(XCmdPtr par, WEHandle we, Ptr textPtr, long textLength, StScrpHandle hStyles, Handle hSoup);
SCErr weInsertFormattedText		(XCmdPtr par, WEHandle we, Ptr textPtr, long textLength, StScrpHandle hStyles, Handle hSoup, Handle hParaFormat, Handle hRulerScrap);
SCErr weInsertObject			(XCmdPtr par, WEHandle we, const FlavorType flavor, const Handle data, const Point size);
SCErr weIsActive				(XCmdPtr par, WEHandle we, Boolean *isActive);
SCErr weKey						(XCmdPtr par, WEHandle we, SInt16 key, EventModifiers modifiers);
SCErr weNew						(XCmdPtr par, WEHandle *we, const LongRect *destRect, const LongRect *viewRect, UInt32 features);
SCErr weOffsetToLine			(XCmdPtr par, WEHandle we, long offset, long *line);
SCErr wePaste					(XCmdPtr par, WEHandle we);
SCErr wePut						(XCmdPtr par, WEHandle we, long start, long end, const char *inTextPtr, ByteCount inTextLength, 
										TextEncoding inTextEncoding, OptionBits inPutOptions, ItemCount inFlavorCount,
										const FlavorType *inFlavorTypes, const Handle *inFlavorHandles);
SCErr weRemoveObjectProperty	(XCmdPtr par, WEObjectDescHandle inObjectDesc, OSType owner, OSType tag);
SCErr weScroll					(XCmdPtr par, WEHandle we, long scrollh, long scrollv);
SCErr weSelView					(XCmdPtr par, WEHandle we);
SCErr weSetObjectBaseline		(XCmdPtr par, WEObjectDescHandle inObjectDesc, SInt16 baseline);
SCErr weSetObjectImage			(XCmdPtr par, WEObjectDescHandle inObjectDesc, PicHandle hPic, short constrain);
SCErr weSetObjectName			(XCmdPtr par, WEObjectDescHandle inObjectDesc, Handle name);
SCErr weSetObjectPlacement		(XCmdPtr par, WEObjectDescHandle inObjectDesc, WEObjectPlacement *placement);
SCErr weSetObjectProperty		(XCmdPtr par, WEObjectDescHandle inObjectDesc, OSType owner, OSType tag, Handle data);
SCErr weSetObjectRefCon			(XCmdPtr par, WEObjectDescHandle inObjectDesc, SInt32 refcon);
SCErr weSetSelection			(XCmdPtr par, WEHandle we, long startChar, long endChar);
SCErr weSetStyle				(XCmdPtr par, WEHandle we, WEStyleMode mode, const TextStyle *ts);
SCErr weStreamRange				(XCmdPtr par, WEHandle we, long rangeStart, long rangeEnd, FlavorType dataFlavor, OptionBits inStreamOptions, Handle hData);
SCErr weUpdate					(XCmdPtr par, WEHandle we, RgnHandle updateRgn);
SCErr weUpdateFontTable			(XCmdPtr par, Handle hFontTable, WEFontNameToIDUPP fontNameToIDProc, Boolean *wasChanged);
SCErr weUpdateStyleScrap		(XCmdPtr par, StScrpHandle hStyles, Handle hFontTable);
SCErr weUseStyleScrap			(XCmdPtr par, WEHandle we, StScrpHandle hStyles);
SCErr weUseText					(XCmdPtr par, WEHandle we, Handle text);
SCErr weVersion					(XCmdPtr par, long *version);
SCErr weGetInfo					(XCmdPtr par, WEHandle we, WESelector selector, void *info);
SCErr weSetInfo					(XCmdPtr par, WEHandle we, WESelector selector, void *info);
SCErr weSetDestRect				(XCmdPtr par, WEHandle we, LongRect *r);
SCErr weSetViewRect				(XCmdPtr par, WEHandle we, LongRect *r);
SCErr weFeatureFlag				(XCmdPtr par, WEHandle we, SInt16 feature, SInt16 action);
SCErr weSetAlignment			(XCmdPtr par, WEHandle we, WEAlignment alignment);
SCErr WEPackText				(XCmdPtr par, Handle *dataHand, WEHandle thedit);
SCErr WEUnPackText				(XCmdPtr par, Handle dataHand, WEHandle *thedit, LongRect *dest, LongRect *view, long dontWrap);

double ATOF						(XCmdPtr par, const char *p);
int ATOI						(XCmdPtr par, const char *p);
long ATOL						(XCmdPtr par, const char *p);
double COS						(XCmdPtr par, const double d);
int MEMCMP						(XCmdPtr par, const char *dst, const char *src, size_t n);
double SIN						(XCmdPtr par, const double d);
int SPRINTF						(XCmdPtr par, char *s, const char *fmt, ...);
int STRCMP						(XCmdPtr par, char *dst, const char *src);
char *STRCHR					(XCmdPtr par, char *s, int c);
char *STRCPY					(XCmdPtr par, char *dst, const char *src);
int STRLEN						(XCmdPtr par, const char *s);
int STRNCMP						(XCmdPtr par, const char *dst, const char *src, size_t n);
char *STRPBRK					(XCmdPtr par, const char *s1, const char *s2);
char *STRRCHR					(XCmdPtr par, char *s, int c);
char *STRSTR					(XCmdPtr par, const char *s1, const char *s2);
char *STRTOK					(XCmdPtr par, char *s1, const char *s2);
int SSCANF						(XCmdPtr par, char *s, const char *fmt, ...);
double TAN						(XCmdPtr par, const double d);


-------------------------------------------------------------------------------------------------------------------------------------------------------------- */ 


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	AddProjStar
 *
 *	Add a new star (i.e., data-fork) resource to a particular project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'. After this call ends, the data handle still belongs
 *	to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr AddProjStar
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString, 			//	<--	Project to add star resource to
	Handle theData, 					//	<--	Data to put in new resource
	StringPtr theName, 					//	<--	Name to use for new resource
	ResType theType, 					//	<-- Four byte type code for new resource
	Boolean replace, 					//	<--	Replace any existing resource with same name?
	long *newID							//	--> Receives resource ID of newly created star
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	AddProjStarLong
 *
 *	Add a new star (i.e., data-fork) resource to a particular project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'. After this call ends, the data handle still belongs
 *	to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr AddProjStarLong
(
 XCmdPtr par, 						//	<--	Parameter block pointer
 Handle descriptString,				//	<--	Project to add star resource to
 Handle theData, 					//	<--	Data to put in new resource
 StringPtr theName, 					//	<--	Name to use for new resource
 ResType theType, 					//	<-- Four byte type code for new resource
 Boolean replace, 					//	<--	Replace any existing resource with same name?
 long *newID							//	--> Receives resource ID of newly created star
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	AddProjStarByIDLong
 *
 *	Add a new star (i.e., data-fork) resource to a particular project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'. After this call ends, the data handle still belongs
 *	to you, and it is up to you to dispose of it.
 *
 *	Note that this callback differs from AddProjStarLong both in that it
 *	lets you assign a specific ID for the new resource, and in what is
 *	considers a collision with existing resources. AddProjStarLong
 *	removes resources with the same type and NAME if replace is true,
 *	but AddProjStarByIDLong removes those with the same type and ID.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr AddProjStarByIDLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Project to add star resource to
	Handle theData, 					//	<--	Data to put in new resource
	StringPtr theName,					//	<--	Name to use for new resource
	ResType theType, 					//	<-- Four byte type code for new resource
	long theID,							//	<-- Resource ID for newly created star
	Boolean replace 					//	<--	Replace any existing resource with same name?
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	AddSFStar
 *
 *	Add a new star (i.e., data-fork) resource to the SharedFile project,
 *	After this call ends, the data handle still belongs to you, and it is
 *	up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr AddSFStar
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle theData, 					//	<--	Data to put in new resource
	StringPtr theName, 					//	<--	Name to use for new resource
	ResType theType, 					//	<-- Four character type code for new resource
	Boolean replace, 					//	<--	Replace any existing resource with same name?
	long *newID							//	--> Receives resource ID of newly created star
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	Answer
 *
 *	Invoke the SuperCard answer command
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr Answer
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	unsigned char *prompt, 				//	<--	Prompt to display in dialog
	unsigned char *p1, 					//	<--	Name of option one (or nil)
	unsigned char *p2, 					//	<-- Name of option two (or nil)
	unsigned char *p3, 					//	<--	Name of option three (or nil)
	short *answer						//	--> Receives number of chosen button
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	AnswerFile
 *
 *	Invoke the SuperCard answer file command
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr AnswerFile
(
	 XCmdPtr par,						//	<--	Parameter block pointer
	 unsigned char *prompt, 			//	<--	Prompt to display in dialog
	 unsigned char *type1,				//	<--	First file type (or empty string)
	 unsigned char *type2,				//	<-- Second file type (or empty string)
	 unsigned char *type3,				//	<--	Third file type (or empty string)
	 unsigned char *result, 			//	-->	Receives path to file
	 short *vRefNum,					//	--> Receives vRefNum of chosen file
	 long *parID						//	--> Receives parID of chosen file
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	AnswerFileLong
 *
 *	Invoke the SuperCard answer file command with long filename support
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr AnswerFileLong
(
	XCmdPtr par,						//	<--	Parameter block pointer
	unsigned char *prompt,				//	<--	Prompt to display in dialog
	unsigned char *type1,				//	<--	First file type (or empty string)
	unsigned char *type2,				//	<-- Second file type (or empty string)
	unsigned char *type3,				//	<--	Third file type (or empty string)
	unsigned char *ext1,				//	<--	First file extension (or empty string)
	unsigned char *ext2,				//	<-- Second file extension (or empty string)
	unsigned char *ext3,				//	<--	Third file extension (or empty string)
	Handle *result,						//	-->	Receives path to chosen file
	short *vRefNum,						//	--> Receives vRefNum of chosen file
	long *parID							//	--> Receives parID of chosen file
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	AnswerFolder
 *
 *	Invoke the SuperCard answer folder command
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr AnswerFolder
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	unsigned char *prompt, 				//	<--	Prompt to display in answer dialog
	unsigned char *result, 				//	-->	Receives path to folder
	short *vRefNum,						//	--> Receives vRefNum of chosen folder
	long *dirID							//	--> Receives dirID of chosen folder
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	AnswerFolderLong
 *
 *	Invoke the SuperCard answer folder command with long filename support
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr AnswerFolderLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	unsigned char *prompt, 				//	<--	Prompt to display in answer dialog
	Handle *result,						//	-->	Receives path to folder
	short *vRefNum,						//	--> Receives vRefNum of chosen folder
	long *dirID							//	--> Receives dirID of chosen folder
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	AnswerProgram
 *
 *	Invoke the SuperCard answer folder command
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr AnswerProgram
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	unsigned char *prompt, 				//	<--	Prompt to display in dialog
	unsigned char *type, 				//	<--	Program type (or empty string)
	unsigned char *result 				//	-->	Receives net address of target app
);

/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	Ask
 *
 *	Invoke the SuperCard ask command
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr Ask
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	unsigned char *prompt, 				//	<--	Prompt to display in answer dialog
	unsigned char *defaultstr, 			//	<--	Default response to display in dialog
	unsigned char *enterdata, 			//	<-- Actual response from dialog
	short passwd,						//	<-- Passing true makes it work like ask password
	short *answer						//	--> Receives number of chosen button
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	AskFile
 *
 *	Invoke the SuperCard ask file command
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr AskFile
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	unsigned char *prompt, 				//	<--	Prompt to display in answer dialog
	unsigned char *defaultstr, 			//	<--	Default response to display in dialog
	unsigned char *path,				//	--> Receives path to chosen file
	short *answer,						//	--> Receives number of chosen button
	short *vRefNum,						//	--> Receives vRefNum of chosen file
	long *parID							//	--> Receives parID of chosen file
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	AskFileLong
 *
 *	Invoke the SuperCard ask file command with long filename support
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr AskFileLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	unsigned char *prompt, 				//	<--	Prompt to display in answer dialog
	unsigned char *defaultstr, 			//	<--	Default response to display in dialog
	Handle *path,						//	--> Receives path to chosen file
	short *answer,						//	--> Receives number of chosen button
	short *vRefNum,						//	--> Receives vRefNum of chosen file
	long *parID							//	--> Receives parID of chosen file
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	AskList
 *
 *	Invoke the SuperCard ask list command
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr AskList
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	asklistparmsptr theparms, 			//	<--	Ptr to parameter block which controls dialog
	Handle *result, 					//	-->	Pre-allocated handle to receive result
	short *answer						//	--> Receives number of chosen button
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	CountMovies
 *
 *	Count the number of async movies currently open
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr CountMovies
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	long *numMovies 					//	--> Receives number of open async movies
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	CountObjects
 *
 *	Count the number of objects on the specified card or bkgnd
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr CountObjects
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString, 			//	<--	Card or bkgnd to count objects on
	short *numObjects					//	--> Receives the number of objects
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	CountObjectsLong
 *
 *	Count the number of objects on the specified card or bkgnd
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr CountObjectsLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Card or bkgnd to count objects on
	short *numObjects					//	--> Receives the number of objects
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	CountProjStars
 *
 *	Count the number of star resources in the specified project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr CountProjStars
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString, 			//	<--	Project to count star resources in
	long *numStars						//	--> Receives the number of star resources
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	CountProjStarsLong
 *
 *	Count the number of star resources in the specified project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr CountProjStarsLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Project to count star resources in
	long *numStars						//	--> Receives the number of star resources
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	CountSFStars
 *
 *	Count the number of star resources in the SharedFile project
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr CountSFStars
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	long *numStars						//	--> Receives the number of star resources
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	CreateObject
 *
 *	Create a new SuperCard object. Note that the parameters to this call
 *	are not all used in every object type, and that their meanings vary.
 *	
 *	descriptString refers to the card or bkgnd on which you want to create 
 *	a new object.
 *
 *	theKind refers to the three main SC object classes (kindGraphic, 
														*	kindButton, kindField).
 *
 *	theType refers to a variant of the kind (e.g., typRect, typRound, 
											 *	typOval, typLine, typPolygon, typBitMap, typText, typArc).
 *
 *	Most objects require a rect, but not lines or polygons (either btns or
															*	grcs), so for those you pass nil in param #5.
 *
 *	Points are required for lines, and point1 is also used for the angle
 *	data (pass 'startAngle,arcAngle').
 *
 *	The final param is used only for polygons (either btns or grcs), for
 *	fields and text graphics. and for paint graphics. For polygon objects
 *	it holds the PolyHandle you want to use. For fields and text grcs it 
 *	holds the text in a special 'packed' format which SC uses internally.
 *	You can obtain a pointer to the internal packtext function and use it 
 *	to generate this format yourself. The advantage of this form is that
 *	style and text info are all wrapped up in a single neat package that
 *	doesn't have lots of pieces dangling off it like a TERec does (which
																   *	obviously makes it easier to store). For paint objects, pass a handle
 *	to the raw bitmap data (such as obtained via GetBits).
 *
 *	This function is a superset of CreateDrawReg, which is obsolete 
 *	amd has been eliminated.
 *
 *	Note that after this operation theData still belongs to you, and it
 *	is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr CreateObject
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString, 			//	<--	Card or bkgnd to create object on
	short theKind,						//	<-- Kind code of new object
	short theType,						//	<-- Type code of new object 
	Rect *theRect,						//	<--	Rect of new object (for lines and polygons, pass nil instead)
	Point point1, 						//	<--	Used only for lines and arcs (for arcs, pass 'startAngle,arcAngle')
	Point point2,  						//	<--	Used only for end point of lines
	Handle theData 						//	<--	For polygons pass PolyHandle, for flds pass packed text
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	CreateObjectLong
 *
 *	Create a new SuperCard object. Note that the parameters to this call
 *	are not all used in every object type, and that their meanings vary.
 *	
 *	descriptString refers to the card or bkgnd on which you want to create 
 *	a new object.
 *
 *	theKind refers to the three main SC object classes (kindGraphic, 
														*	kindButton, kindField).
 *
 *	theType refers to a variant of the kind (e.g., typRect, typRound, 
											 *	typOval, typLine, typPolygon, typBitMap, typText, typArc).
 *
 *	Most objects require a rect, but not lines or polygons (either btns or
															*	grcs), so for those you pass nil in param #5.
 *
 *	Points are required for lines, and point1 is also used for the angle
 *	data (pass 'startAngle,arcAngle').
 *
 *	The final param is used only for polygons (either btns or grcs), for
 *	fields and text graphics. and for paint graphics. For polygon objects
 *	it holds the PolyHandle you want to use. For fields and text grcs it 
 *	holds the text in a special 'packed' format which SC uses internally.
 *	You can obtain a pointer to the internal packtext function and use it 
 *	to generate this format yourself. The advantage of this form is that
 *	style and text info are all wrapped up in a single neat package that
 *	doesn't have lots of pieces dangling off it like a TERec does (which
																   *	obviously makes it easier to store). For paint objects, pass a handle
 *	to the raw bitmap data (such as obtained via GetBits).
 *
 *	This function is a superset of CreateDrawReg, which is obsolete 
 *	amd has been eliminated.
 *
 *	Note that after this operation theData still belongs to you, and it
 *	is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr CreateObjectLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Card or bkgnd to create object on
	short theKind,						//	<-- Kind code of new object
	short theType,						//	<-- Type code of new object 
	Rect *theRect,						//	<--	Rect of new object (for lines and polygons, pass nil instead)
	Point point1, 						//	<--	Used only for lines and arcs (for arcs, pass 'startAngle,arcAngle')
	Point point2,  						//	<--	Used only for end point of lines
	Handle theData 						//	<--	For polygons pass PolyHandle, for flds pass packed text
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	DelProjStarByID
 *
 *	Delete a star resource by ID from the specified project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr DelProjStarByID
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString, 			//	<--	Project to delete star resource from
	long theID,							//	<--	ID number of the star resource to remove
	ResType theType						//	<--	Four byte type code for the resource
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	DelProjStarByIDLong
 *
 *	Delete a star resource by ID from the specified project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr DelProjStarByIDLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Project to delete star resource from
	long theID,							//	<--	ID number of the star resource to remove
	ResType theType						//	<--	Four byte type code for the resource
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	DelProjStarByName
 *
 *	Delete a star resource by name from the specified project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr DelProjStarByName
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString, 			//	<--	Project to delete star resource from
	StringPtr theName,					//	<--	Name of the star resource to remove
	ResType theType						//	<--	Four byte type code for the resource
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	DelProjStarByNameLong
 *
 *	Delete a star resource by name from the specified project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr DelProjStarByNameLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Project to delete star resource from
	StringPtr theName,					//	<--	Name of the star resource to remove
	ResType theType						//	<--	Four byte type code for the resource
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	DelSFStarByID
 *
 *	Delete a star resource by ID from the SharedFile project.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr DelSFStarByID
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	long theID,							//	<--	ID number of the star resource to remove
	ResType theType						//	<--	Four byte type code for the resource
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	DelSFStarByName
 *
 *	Delete a star resource by name from the SharedFile project.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr DelSFStarByName
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr theName,					//	<--	Name of the star resource to remove
	ResType theType						//	<--	Four byte type code for the resource
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	DrawCard
 *
 *	Draw the specified SuperCard Card in the current port. Allows an entire 
 *	card and bkgnd to be rendered in vector form via a single callback.
 *	Note that this routine automatically sets up the proper color table.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr DrawCard
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString			//	<--	Card to draw
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	DrawCardLong
 *
 *	Draw the specified SuperCard Card in the current port. Allows an entire 
 *	card and bkgnd to be rendered in vector form via a single callback.
 *	Note that this routine automatically sets up the proper color table.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr DrawCardLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString				//	<--	Card to draw
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	DrawObject
 *
 *	Draw the specified SuperCard object in the current port.
 *	Note that this routine automatically sets up the proper color table.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr DrawObject
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString			//	<--	Object to draw
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	DrawObjectLong
 *
 *	Draw the specified SuperCard object in the current port.
 *	Note that this routine automatically sets up the proper color table.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr DrawObjectLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString				//	<--	Object to draw
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	DrawObjectByIndex
 *
 *	Draw the specified SuperCard object in the current port.
 *	Note that this routine automatically sets up the proper color table.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr DrawObjectByIndex
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Cd or bkgnd to draw objects of
	short index
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	DrawObjectByIndexLong
 *
 *	Draw the specified SuperCard object in the current port.
 *	Note that this routine automatically sets up the proper color table.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr DrawObjectByIndexLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Cd or bkgnd to draw objects of
	short index
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	DrawObjects
 *
 *	Draw all SuperCard objects on a card or bkgnd in the current port.
 *	Note that this routine automatically sets up the proper color table.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr DrawObjects
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString			//	<--	Cd or bkgnd to draw objects of
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	DrawObjectsLong
 *
 *	Draw all SuperCard objects on a card or bkgnd in the current port.
 *	Note that this routine automatically sets up the proper color table.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr DrawObjectsLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString				//	<--	Cd or bkgnd to draw objects of
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetApplResRef
 *
 *	Get the resource reference of the SuperCard application (or of the
 *	SharedFile, if in a standalone).
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetApplResRef
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	short *resRef						//	-->	Receives reference number of application
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetApplVolRef
 *
 *	Get the volume reference of the SuperCard application (or of the
 *	SharedFile, if in a standalone).
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetApplVolRef
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	short *volRef						//	-->	Receives reference number of application
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetBackClut
 *
 *	Get a copy of the clut of the specified bkgnd. Note that this clut 
 *	belongs to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetBackClut
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Background to get the clut of
	CTabHandle *theClut					//	-->	Receives clut handle
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetBackClutLong
 *
 *	Get a copy of the clut of the specified bkgnd. Note that this clut 
 *	belongs to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetBackClutLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Background to get the clut of
	CTabHandle *theClut					//	-->	Receives clut handle
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetBackTolerance
 *
 *	Get the color tolerance of the specified bkgnd. Returns an integral 
 *	value between 0 and 5, inclusive.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetBackTolerance
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Background to get the tolerance setting of
	short *tolerance					//	-->	Receives tolerance code
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetBackToleranceLong
 *
 *	Get the color tolerance of the specified bkgnd. Returns an integral 
 *	value between 0 and 5, inclusive.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetBackToleranceLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Background to get the tolerance setting of
	short *tolerance					//	-->	Receives tolerance code
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetBits
 *
 *	Get a copy of the bitmap data from the specified paint graphic. Note  
 *	that this data now belongs to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetBits
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Object to get the bits of
	PixInfoPtr theInfo					//	-->	Pointer to PixInfo struct
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetBitsLong
 *
 *	Get a copy of the bitmap data from the specified paint graphic. Note  
 *	that this data now belongs to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetBitsLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object to get the bits of
	PixInfoPtr theInfo					//	-->	Pointer to PixInfo struct
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetBrushes
 *
 *	Get a copy of the brushes from the specified project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'. This data now belongs to you, and it is up to you 
 *	to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetBrushes
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Project to get brushes from
	BrushesHandle *theBrushes			//	-->	Receives brushes data
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetBrushesLong
 *
 *	Get a copy of the brushes from the specified project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'. This data now belongs to you, and it is up to you 
 *	to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetBrushesLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Project to get brushes from
	BrushesHandle *theBrushes			//	-->	Receives brushes data
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetCardClut
 *
 *	Get a copy of the clut of the specified card. Note that this clut 
 *	belongs to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetCardClut
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Card to get the clut of
	CTabHandle *theClut					//	-->	Receives clut handle
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetCardClutLong
 *
 *	Get a copy of the clut of the specified card. Note that this clut 
 *	belongs to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetCardClutLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Card to get the clut of
	CTabHandle *theClut					//	-->	Receives clut handle
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetCardTolerance
 *
 *	Get the color tolerance of the specified card. Returns an integral 
 *	value between 0 and 5, inclusive.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetCardTolerance
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Card to get the clut of
	short *tolerance					//	-->	Receives tolerance code
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetCardToleranceLong
 *
 *	Get the color tolerance of the specified card. Returns an integral 
 *	value between 0 and 5, inclusive.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetCardToleranceLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Card to get the clut of
	short *tolerance					//	-->	Receives tolerance code
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetContextInfo
 *
 *	Get an ContextInfo struct for the specified object. Note that the
 *	ContextInfoHandle belongs to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetContextInfo
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Object get ContextInfo structure for
	ContextInfoHandle *infoHand			//	-->	Receives ContextInfo structure
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetContextInfoLong
 *
 *	Get an ContextInfo struct for the specified object. Note that the
 *	ContextInfoHandle belongs to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetContextInfoLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object get ContextInfo structure for
	ContextInfoHandle *infoHand			//	-->	Receives ContextInfo structure
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetCurCTabHandle
 *
 *	Get handle to the clut which is currently in use. Note that this clut
 *	DOES NOT belong to you, and you MUST NOT dispose of it!
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetCurCTabHandle
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	CTabHandle *theClut					//	-->	Receives clut handle
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetCurEventRec
 *
 *	Get pointer to the event record which SC is currently reacting to.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetCurEventRec
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	EventRecord *eventRec				//	-->	Receives pointer to event record
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetCurPrintRec
 *
 *	Get pointer to the print record which SC is currently using. Note that 
 *	this TPrint DOES NOT belong to you, and you MUST NOT dispose of it!
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetCurPrintRec
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	THPrint *printRec					//	-->	Receives pointer to print record
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetCurWEHandle
 *
 *	Get the TE/WEHandle of the currently open field (if any). To tell SC you
 *	have changed this rec, use TouchCurTEHandle. Note that this TE/WEHandle
 *	DOES NOT belong to you, and you MUST NOT dispose of it! 
 
 *	Neither should you dispose the text handle within, or SC's own internal 
 *	reference will be left dangling, and your project could be damaged. To
 *	change an open field's text, you must store your altered version in the
 *	ORIGINAL text handle you find in the structure (TextEdit and WASTE both
 *	supply safe routines for this, or you can do it yourself with PtrToXHand). 
 *
 *	Because open TextEdit and WASTE records 'hot-bunk' in the same field in 
 *	SC's main globals block, the handle this call returns may contain either
 *	structure. The value returned in the last param will indicate which form
 *	you've received, so you'll know which set of routines to use on it.
 *
 *	Because SuperCard uses a slightly modified form of WASTE, you should
 *	NOT use the regular WASTE routines on 'WASTE' recs you get back from SC!
 *	To be safe, you should use the 'we' calls in this library instead.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetCurWEHandle
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	WEHandle *editHand					//	-->	Receives WEHandle of open field
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetFindRect
 *
 *	Get the rect of the foundChunk.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetFindRect
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Rect *theRect						//	-->	Receives rect of foundChunk
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetGlobals
 *
 *	Get pointer to SuperCard's main globals block. Note that this block
 *	DOES NOT belong to you, and you MUST NOT dispose of it!
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetGlobals
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	globptr *gp							//	-->	Receives pointer to mainglobals block
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetIndMovieInfo
 *
 *	Get a MovieInfo struct for the nth movie in the queue of async movies.
 *	Note: to count movies in this queue, use CountMovies(). Note that the
 *	index is zero-based.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetIndMovieInfo
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	long index, 						//	<--	Index of movie you want (zero-based)
	MovieInfo *theMovie					//	-->	Receives MovieInfo structure
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetLinePoints
 *
 *	Get endpoints of the specified line graphic.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetLinePoints
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Card Line get the points of
	Point *startPoint, 					//	-->	Receives start point of line
	Point *endPoint 					//	-->	Receives end point of line
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetLinePointsLong
 *
 *	Get endpoints of the specified line graphic.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetLinePointsLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Card Line get the points of
	Point *startPoint, 					//	-->	Receives start point of line
	Point *endPoint 					//	-->	Receives end point of line
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetListHandle
 *
 *	Get the ListHandle associated with a specified List or ScrollingList 
 *	field. Note that this ListHandle DOES NOT belong to you, and you 
 *	MUST NOT dispose of it!
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetListHandle
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	List or ScrollingList field get ListHandle of
	ListHandle *theList 				//	-->	Receives ListHandle associated with field
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetListHandleLong
 *
 *	Get the ListHandle associated with a specified List or ScrollingList 
 *	field. Note that this ListHandle DOES NOT belong to you, and you 
 *	MUST NOT dispose of it!
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetListHandleLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	List or ScrollingList field get ListHandle of
	ListHandle *theList 				//	-->	Receives ListHandle associated with field
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetMsgHandle
 *
 *	Get the Handle the message shown in the editable area of msg box. Note
 *	that this handle DOES NOT belong to you, and you MUST NOT dispose of it!
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetMsgHandle
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle *editHand					//	-->	Receives Handle of text shown in editable area of msg box
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetMsgResultStr
 *
 *	Get a copy of the text displayed in result area of msg box.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetMsgResultStr
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr theString					//	-->	Receives copy of text in result area of msg box
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetMsgTEHandle
 *
 *	Get the TEHandle for the result area of the msg box. Note that this 
 *	TEHandle DOES NOT belong to you, and you MUST NOT dispose of it!
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetMsgTEHandle
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	TEHandle *editHand					//	-->	Receives TEHandle of result area of msg box
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetMsgWindowPtr
 *
 *	Get the WindowPtr for the msg box.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetMsgWindowPtr
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	WindowPtr *theWindow				//	-->	Receives WindowPtr of msg box
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetObjectData
 *
 *	Gets the 'raw' data (if any) for the specified object. The form and 
 *	meaning of dataHand depend on the type of object specified. Only some 
 *	types of objects have this auxiliary data (polygons graphics and buttons,  
 *	paint objects, fields, and text graphics). The purpose of this is to let   
 *	you use other pre-existing objects as 'templates' to derive the associated 
 *	content of new objects from, or to set the content of pre-existing items.
 *	Note that dataHand belongs to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetObjectData
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Object get ObjectInfo structure for
	Handle *dataHand					//	-->	Receives raw object data
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetObjectDataLong
 *
 *	Gets the 'raw' data (if any) for the specified object. The form and 
 *	meaning of dataHand depend on the type of object specified. Only some 
 *	types of objects have this auxiliary data (polygons graphics and buttons,  
 *	paint objects, fields, and text graphics). The purpose of this is to let   
 *	you use other pre-existing objects as 'templates' to derive the associated 
 *	content of new objects from, or to set the content of pre-existing items.
 *	Note that dataHand belongs to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetObjectDataLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object get ObjectInfo structure for
	Handle *dataHand					//	-->	Receives raw object data
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetObjectInfo
 *
 *	Get an ObjectInfo struct for the specified object. Note that the
 *	ObjectInfoHandle belongs to you, and it is up to you to dispose of it.
 *	Don't forget to dispose the name handle (if any) first!
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetObjectInfo
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Object get ObjectInfo structure for
	ObjectInfoHandle *infoHand			//	-->	Receives ObjectInfo structure
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetObjectInfoLong
 *
 *	Get an ObjectInfo struct for the specified object. Note that the
 *	ObjectInfoHandle belongs to you, and it is up to you to dispose of it.
 *	Don't forget to dispose the name handle (if any) first!
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetObjectInfoLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object get ObjectInfo structure for
	ObjectInfoHandle *infoHand			//	-->	Receives ObjectInfo structure
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetObjectInfoByIndex
 *
 *	Get an ObjectInfo struct for the Nth object. Note that the index is
 *	zero-based.  The ObjectInfoHandle belongs to you, and it is up to you to
 *	dispose of it. Don't forget to dispose the name handle (if any) first!
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetObjectInfoByIndex
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Cd or bkgnd object is on
	short index,						//	<--	Zero-based object index
	ObjectInfoHandle *infoHand			//	-->	Receives ObjectInfo structure
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetObjectInfoByIndexLong
 *
 *	Get an ObjectInfo struct for the Nth object. Note that the index is
 *	zero-based.  The ObjectInfoHandle belongs to you, and it is up to you to
 *	dispose of it. Don't forget to dispose the name handle (if any) first!
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetObjectInfoByIndexLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Cd or bkgnd object is on
	short index,						//	<--	Zero-based object index
	ObjectInfoHandle *infoHand			//	-->	Receives ObjectInfo structure
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetObjectScript
 *
 *	Get the script of the specified SuperCard object.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetObjectScript
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString, 			//	<--	Object to get ScriptInfo record for
	Handle *theScript					//	-->	Receives script of specified object
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetObjectScriptLong
 *
 *	Get the script of the specified SuperCard object.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetObjectScriptLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object to get ScriptInfo record for
	Handle *theScript					//	-->	Receives script of specified object
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetPaintInfo
 *
 *	Get the bit depth and other info about the specified bitmap (i.e., 
 *	paint) graphic. Result is a PixInfo record just like what GetBits 
 *	returns, but the handles (if not empty) are actual references to the
 *	structures SC is using, not copies. This means you MUST NOT dispose
 *	of them when you are done! If the object is not in an open window,
 *	the data and clut handles will be nil.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetPaintInfo
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString, 			//	<--	Paint object to get depth of
	PixInfoPtr theInfo					//	-->	Pointer to PixInfo struct
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetPaintInfoLong
 *
 *	Get the bit depth and other info about the specified bitmap (i.e., 
 *	paint) graphic. Result is a PixInfo record just like what GetBits 
 *	returns, but the handles (if not empty) are actual references to the
 *	structures SC is using, not copies. This means you MUST NOT dispose
 *	of them when you are done! If the object is not in an open window,
 *	the data and clut handles will be nil.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetPaintInfoLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Paint object to get depth of
	PixInfoPtr theInfo					//	-->	Pointer to PixInfo struct
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetPaintPixel
 *
 *	Get the color of a pixel in the bitmap data from the specified paint  
 *	graphic. Note that the returned value = 0..255 for color and 0..1 for B&W.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetPaintPixel
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Object to get a pixel in
	Point pt, 							//	<--	Pixel within grc to get color of
	short *color						//	-->	Receives color of pixel
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetPaintPixelLong
 *
 *	Get the color of a pixel in the bitmap data from the specified paint  
 *	graphic. Note that the returned value = 0..255 for color and 0..1 for B&W.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetPaintPixelLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object to get a pixel in
	Point pt, 							//	<--	Pixel within grc to get color of
	short *color						//	-->	Receives color of pixel
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetPatterns
 *
 *	Get the patterns from the specified project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'. This pattern data belongs to you, and it is up to
 *	you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetPatterns
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Project to get patterns from
	PatternsHandle *thePatterns			//	-->	Receives patterns data
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetPatternsLong
 *
 *	Get the patterns from the specified project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'. This pattern data belongs to you, and it is up to
 *	you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetPatternsLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Project to get patterns from
	PatternsHandle *thePatterns			//	-->	Receives patterns data
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetPictureData
 *
 *	Get the pictureData from the specified object. This data data belongs 
 *	to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetPictureData
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Object to get pictureData from
	PicHandle *thePicture				//	-->	Receives pictureData
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetPictureDataLong
 *
 *	Get the pictureData from the specified object. This data belongs 
 *	to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
//SCErr GetPictureDataLong
//(
//	XCmdPtr par, 						//	<--	Parameter block pointer
//	Handle descriptString,				//	<--	Object to get pictureData from
//	PicHandle *thePicture,				//	-->	Receives pictureData
//	Boolean noCopy						//  <-- Return a copy (defaults to false)
//);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetPictureDataLong
 *
 *	Get the pictureData from the specified object. 
 *	
 *	If you pass false in noCopy, then the returned data belongs 
 *	to you, and it is up to you to dispose of it.
 *
 *	If you pass true in noCopy, then the call will succeed ONLY if the 
 *	object of interest is currently in scope, and the returned data
 *	belongs to SuperCard and you must NOT dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetPictureDataLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object to get pictureData from
	PicHandle *thePicture,				//	-->	Receives pictureData
	Boolean noCopy						//  <-- Return a copy (defaults to false)
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetPictureDataBuffer
 *
 *	Get the internal buffer SuperCard uses to cache pictureData from 
 *	the specified object at runtime. 
 *	
 *	This the call will succeed ONLY if the object of interest is currently
 *	in scope. The returned data belongs to SuperCard, and you must 
 *	NOT dispose of it!
 *
 *	Pass the address of a pict structure in param three, and if the object
 *	is in scope and has cached pictureData, the struct will be filled in
 *	with the appropriate data.
 *
 *	DANGER!!! This callback allows you to access internal SuperCard data
 *	structures which are subject to change without notice! Should these
 *	structures change, externals which use this callback may fail or
 *	even crash SuperCard. Also when the referenced object goes out of
 *	scope these structures wil be disposed of 'out from under you', and
 *	if you try to access them you will crash. That means it's not a good 
 *	idea to try to hang onto them for long (even across other callbacks).
 *
 *	¥¥¥ DON'T SAY YOU WEREN'T WARNED!!! ¥¥¥
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetPictureDataBuffer
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object to get pictureData from
	pict *theBuffer						//	-->	Receives pict buffer info
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetPictureInfo
 *
 *	Get a pictureInfo structure for the specified object. This data data  
 *	belongs to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetPictureInfo
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Object to get pictureInfo from
	PDInfoHandle *infoHand				//	-->	Receives pictureInfo
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetPictureInfoLong
 *
 *	Get a pictureInfo structure for the specified object. This data data  
 *	belongs to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetPictureInfoLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object to get pictureInfo from
	PDInfoHandle *infoHand				//	-->	Receives pictureInfo
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetPictureMode
 *
 *	Get the pictureData 'mode' (embedded = 0, reference = 1) for the 
 *	specified graphic object.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetPictureMode
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Object to get picture mode of
	long *mode							//	-->	Receives mode code (embedded = 0, reference = 1)
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetPictureModeLong
 *
 *	Get the pictureData 'mode' (embedded = 0, reference = 1) for the 
 *	specified graphic object.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetPictureModeLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object to get picture mode of
	long *mode							//	-->	Receives mode code (embedded = 0, reference = 1)
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetPicturePath
 *
 *	Get the pictureData file path for 'by reference' pictureData object.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetPicturePath
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Object to get picture path of
	StringPtr path						//	-->	Receives reference file path
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetPicturePathLong
 *
 *	Get the pictureData file path for 'by reference' pictureData object.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetPicturePathLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object to get picture path of
	Handle *path						//	-->	Receives reference file path
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetPolyHandle
 *
 *	Get a copy of the polyHandle for the specified polygon object. Note that
 *	this PolyHandle belongs to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetPolyHandle
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Object to get PolyHandle from
	PolyHandle *thePoly					//	-->	Receives PolyHandle
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetPolyHandleLong
 *
 *	Get a copy of the polyHandle for the specified polygon object. Note that
 *	this PolyHandle belongs to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetPolyHandleLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object to get PolyHandle from
	PolyHandle *thePoly					//	-->	Receives PolyHandle
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetPouchVolRef
 *
 *	Get the volume reference of the SuperCard Pouch folder.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetPouchVolRef
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	short *volRef						//	-->	Receives reference number of SC Pouch
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetPrivateNum
 *
 *	Get the 'private number' stored in the specified SuperCard project.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetPrivateNum
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Project to get private number from
	long *theNum						//	--> Receives the private number
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetPrivateNumLong
 *
 *	Get the 'private number' stored in the specified SuperCard project.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetPrivateNumLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Project to get private number from
	long *theNum						//	--> Receives the private number
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetProjAlias
 *
 *	Get an alias to the specified SuperCard project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'. This AliasHandle belongs to you, and it is up to
 *	you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetProjAlias
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Project to get alias of
	AliasHandle *theAlias				//	--> Receives the alias
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetProjAliasLong
 *
 *	Get an alias to the specified SuperCard project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'. This AliasHandle belongs to you, and it is up to
 *	you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetProjAliasLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Project to get alias of
	AliasHandle *theAlias				//	--> Receives the alias
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetProjFSSpec
 *
 *	Get an FSSpec to the specified SuperCard project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetProjFSSpec
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Project to get FSSpec to
	FSSpec *theSpec						//	--> Receives the FSSpec
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetProjFSSpecLong
 *
 *	Get an FSSpec to the specified SuperCard project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetProjFSSpecLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Project to get FSSpec to
	FSSpec *theSpec						//	--> Receives the FSSpec
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetProjResRef
 *
 *	Get resource fork reference number for the specified SuperCard project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetProjResRef
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Project to get resource fork ref of
	short *resRef						//	--> Receives the resource fork ref
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetProjResRefLong
 *
 *	Get resource fork reference number for the specified SuperCard project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetProjResRefLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Project to get resource fork ref of
	short *resRef						//	--> Receives the resource fork ref
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetProjStarByID
 *
 *	Get a copy of a a star resource by ID from the specified project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'. dataHand belongs to you, and it is up to you to
 *	dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetProjStarByID
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString, 			//	<--	Project to get star resource from
	long theID,							//	<--	ID number of the star resource to get
	ResType theType,					//	<--	Four byte type code for the resource
	Handle *dataHand					//	-->	Receives data from star resource
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetProjStarByIDLong
 *
 *	Get a copy of a a star resource by ID from the specified project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'. dataHand belongs to you, and it is up to you to
 *	dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetProjStarByIDLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Project to get star resource from
	long theID,							//	<--	ID number of the star resource to get
	ResType theType,					//	<--	Four byte type code for the resource
	Handle *dataHand					//	-->	Receives data from star resource
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetProjStarByName
 *
 *	Get a copy of a star resource by name from the specified project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'.  dataHand belongs to you, and it is up to you to
 *	dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetProjStarByName
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString, 			//	<--	Project to get star resource from
	StringPtr theName,					//	<--	Name of the star resource to get
	ResType theType,					//	<--	Four byte type code for the resource
	Handle *dataHand					//	-->	Receives data from star resource
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetProjStarByNameLong
 *
 *	Get a copy of a star resource by name from the specified project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'.  dataHand belongs to you, and it is up to you to
 *	dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetProjStarByNameLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Project to get star resource from
	StringPtr theName,					//	<--	Name of the star resource to get
	ResType theType,					//	<--	Four byte type code for the resource
	Handle *dataHand					//	-->	Receives data from star resource
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetProjStarInfoByID
 *
 *	Get a starInfo structure for the star resource (specified by ID)
 *	from the specified project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetProjStarInfoByID
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString, 			//	<--	Project to get star resource from
	long theID,							//	<--	ID number of the star resource to get
	ResType theType,					//	<--	Four byte type code for the resource
	StarInfo *theInfo					//	-->	Receives starInfo struct
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetProjStarInfoByIDLong
 *
 *	Get a starInfo structure for the star resource (specified by ID)
 *	from the specified project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetProjStarInfoByIDLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Project to get star resource from
	long theID,							//	<--	ID number of the star resource to get
	ResType theType,					//	<--	Four byte type code for the resource
	StarInfo *theInfo					//	-->	Receives starInfo struct
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetProjStarInfoByName
 *
 *	Get a starInfo structure for the star resource (specified by ID)
 *	from the specified project.
 *
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetProjStarInfoByName
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString, 			//	<--	Project to get starInfo structure for
	StringPtr theName,					//	<--	Name of the star resource to get starInfo structure for
	ResType theType,					//	<--	Four byte type code for the resource
	StarInfo *theInfo					//	-->	Receives starInfo struct
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetProjStarInfoByNameLong
 *
 *	Get a starInfo structure for the star resource (specified by ID)
 *	from the specified project.
 *
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetProjStarInfoByNameLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Project to get starInfo structure for
	StringPtr theName,					//	<--	Name of the star resource to get starInfo structure for
	ResType theType,					//	<--	Four byte type code for the resource
	StarInfo *theInfo					//	-->	Receives starInfo struct
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetProjStarInfoByNum
 *
 *	Get a starInfo structure for the star resource (specified by number)
 *	from the specified project. Note that you must preload theInfo->theType
 *	with either nil (to get the Nth resource of any type) or with a resource
 *	type code (to get the Nth resource within a particular type).
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetProjStarInfoByNum
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString, 			//	<--	Project to get starInfo for
	long thenum,						//	<--	Number of the star resource to get starInfo of
	StarInfo *theInfo					//	<->	Receives starInfo struct (also specifies type)
);

/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetProjStarInfoByNumLong
 *
 *	Get a starInfo structure for the star resource (specified by number)
 *	from the specified project. Note that you must preload theInfo->theType
 *	with either nil (to get the Nth resource of any type) or with a resource
 *	type code (to get the Nth resource within a particular type).
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetProjStarInfoByNumLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Project to get starInfo for
	long thenum,						//	<--	Number of the star resource to get starInfo of
	StarInfo *theInfo					//	<->	Receives starInfo struct (also specifies type)
);

/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetProjVolRef
 *
 *	Get the volume reference of the specified SuperCard project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetProjVolRef
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString, 			//	<--	Project to get volume reference for
	short *volRef						//	-->	Receives reference number of SC Pouch
);

/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetProjVolRefLong
 *
 *	Get the volume reference of the specified SuperCard project.
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetProjVolRefLong
(
	 XCmdPtr par, 						//	<--	Parameter block pointer
	 Handle descriptString, 			//	<--	Project to get volume reference for
	 short *volRef						//	-->	Receives reference number of SC Pouch
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetScriptAttrs
 *
 *	Get a ScriptInfo record for the specified SuperCard object.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetScriptAttrs
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString, 			//	<--	Object to get ScriptInfo record for
	ScriptInfo *theInfo					//	-->	Receives ScriptInfo record for specified object
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetScriptAttrsLong
 *
 *	Get a ScriptInfo record for the specified SuperCard object.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetScriptAttrsLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object to get ScriptInfo record for
	ScriptInfo *theInfo					//	-->	Receives ScriptInfo record for specified object
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetSFResRef
 *
 *	Get resource fork reference number for the SharedFile project.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetSFResRef
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	short *resRef						//	--> Receives the resource fork ref
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetSFStarByID
 *
 *	Get a star resource by ID from the currently active SharedFile project.
 *	dataHand belongs to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetSFStarByID
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	long theID,							//	<--	ID number of the star resource to get
	ResType theType,					//	<--	Four byte type code for the resource
	Handle *dataHand					//	-->	Receives data from star resource
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetSFStarByName
 *
 *	Get a star resource by name from the currently active SharedFile project.
 *	dataHand belongs to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetSFStarByName
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr theName,					//	<--	Name of the star resource to get
	ResType theType,					//	<--	Four byte type code for the resource
	Handle *dataHand					//	-->	Receives data from star resource
);

/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetSFStarInfoByID
 *
 *	Get a StarInfo structure for the star resource (specified by ID)
 *	from the currently active SharedFile project.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetSFStarInfoByID
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	long theID,							//	<--	ID number of the star resource to get StarInfo for
	ResType theType,					//	<--	Four byte type code for the resource
	StarInfo *theInfo					//	-->	Receives StarInfo struct
);

/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetSFStarInfoByName
 *
 *	Get a starInfo structure for the star resource (specified by theName)
 *	from the currently active SharedFile project.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetSFStarInfoByName
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr theName,					//	<--	Name of the star resource to get starInfo structure for
	ResType theType,					//	<--	Four byte type code for the resource
	StarInfo *theInfo					//	-->	Receives starInfo struct
);

/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetSFStarInfoByNum
 *
 *	Get a starInfo structure for the Nth star resource in the currently
 *	active SharedFile project. Note that you must preload theInfo->theType
 *	with either nil (to get the Nth resource of any type) or with a resource
 *	type code (to get the Nth resource within a particular type).
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetSFStarInfoByNum
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	long theNum,						//	<--	Number of the star resource to get
	StarInfo *theInfo					//	-->	Receives starInfo struct
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetStdLibProcPtr
 *
 *	Get a ProcPtr to the specified Standard Libraries routine.
 *	For a list of the procID codes, see the enum at the top of this file.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr GetStdLibProcPtr
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	long procid, 						//	<--	prociID of the desored routine
	ProcPtr *theproc					//	-->	Receives ProcPtr to specified library routine
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetTEHandle
 *
 *	Get a TEhandle for the specified field.  Note that this TEHandle
 *	belongs to you, and it is up to you to dispose of it. This function 
 *	the 'last-saved' version of a field's contents. When if a field is 
 *	open the current TEHandle can be obtained using GetCurTEHandle.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

/*SCErr GetTEHandle
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString, 			//	<--	Object to get TEHandle for
	TEHandle *editHand					//	-->	Receives TEHandle
);*/


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetWEHandle
 *
 *	Get a WEhandle for the specified field.  Note that this WEHandle
 *	belongs to you, and it is up to you to dispose of it. This function 
 *	the 'last-saved' version of a field's contents. When if a field is 
 *	open the current TE/WEHandle can be obtained using GetCurTEHandle.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetWEHandle
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString, 			//	<--	Object to get WEHandle for
	WEHandle *editHand					//	-->	Receives WEHandle
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetWEHandleLong
 *
 *	Get a WEhandle for the specified field.  Note that this WEHandle
 *	belongs to you, and it is up to you to dispose of it. This function 
 *	the 'last-saved' version of a field's contents. When if a field is 
 *	open the current TE/WEHandle can be obtained using GetCurTEHandle.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetWEHandleLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object to get WEHandle for
	WEHandle *editHand					//	-->	Receives WEHandle
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetUIWEHandle
 *
 *	Get the UI WEhandle for the specified field.  Note that this WEHandle
 *	does NOT belong to you, and you must NOT dispose of it. This function 
 *	returns the displayed version of a field's contents. When if a field is 
 *	open the current TE/WEHandle can be obtained using GetCurTEHandle.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetUIWEHandle
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString, 			//	<--	Object to get WEHandle for
	WEHandle *editHand					//	-->	Receives WEHandle
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetUIWEHandleLong
 *
 *	Get the UI WEhandle for the specified field.  Note that this WEHandle
 *	does NOT belong to you, and you must NOT dispose of it. This function 
 *	returns the displayed version of a field's contents. When if a field is 
 *	open the current TE/WEHandle can be obtained using GetCurTEHandle.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetUIWEHandleLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object to get WEHandle for
	WEHandle *editHand					//	-->	Receives WEHandle
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetWindowID
 *
 *	Get a long ID from the WindowPtr of a SuperCard window. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetWindowID
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	WindowPtr theWindow,				//	<--	WindowPtr to get long id of
	StringPtr descriptString 			//	-->	Receives long ID of window
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetWindowIDLong
 *
 *	Get a long ID from the WindowPtr of a SuperCard window. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetWindowIDLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	WindowPtr theWindow,				//	<--	WindowPtr to get long id of
	Handle *descriptString				//	-->	Receives long ID of window
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetWindowPtr
 *
 *	Get a WindowPtr for the specified SuperCard window. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetWindowPtr
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString, 			//	<--	Window to get WindowPtr for
	WindowPtr *theWindow				//	-->	Receives WindowPtr
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	GetWindowPtrLong
 *
 *	Get a WindowPtr for the specified SuperCard window. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr GetWindowPtrLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Window to get WindowPtr for
	WindowPtr *theWindow				//	-->	Receives WindowPtr
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	ImageCurCard
 *
 *	Image the specified region of the current card in SC's offscreen GWorld,
 *	and return a pointer to it. SC also creates theVisRgn, but it belongs
 *	to you and it is up to you to dispose of it. You MUST NOT dispose of 
 *	the GWorld!
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr ImageCurCard
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	GWorldPtr *theworld, 				//	<--	GWorldPtr to world to image card into
	RgnHandle *theVisRgn				//	<--	Clip region
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	ImageFileToPICT
 *
 *	Use SC's internal import routines to convert an image file to PICT.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr ImageFileToPICT
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr path, 					//	<--	Path to image file QT can import
	PicHandle *thePict					//	<--	Pointer to PicHandle to receive PICT
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	ImageFileToPICTLong
 *
 *	Use SC's internal import routines to convert an image file to PICT.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr ImageFileToPICTLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle path,						//	<--	Path to image file QT can import
	PicHandle *thePict					//	<--	Pointer to PicHandle to receive PICT
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	IndentScript
 *
 *	Indent the supplied text as a SuperCard script. Note that you pass the
 *	start and end of the selection to this routine, which updates them based
 *	on the formatted version of the script.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr IndentScript
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle *theScript, 					//	<->	Script text
	long *startSel, 					//	<-> Start of selection
	long *endSel,						//	<-> End of selection
	short tabWidth						//	<--	Width to use for indenting
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	IndexToObject
 *
 *	Given cd/bg descriptor and an index, return the long name. Note that
 *	the index is zero-based.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr IndexToObject
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Card or Bkgnd to look on
	short index,						//	<--	Index to convert to object descriptor
	StringPtr objectStr					//	-->	Receives long name of object
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	IndexToObjectLong
 *
 *	Given cd/bg descriptor and an index, return the long name. Note that
 *	the index is zero-based.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr IndexToObjectLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Card or Bkgnd to look on
	short index,						//	<--	Index to convert to object descriptor
	Handle *objectStr					//	-->	Receives long name of object
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	IndexToObjectID
 *
 *	Given cd/bg descriptor and an index, return the long ID. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr IndexToObjectID
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Card or Bkgnd to look on
	short index,						//	<--	Index to convert to object descriptor
	StringPtr objectStr					//	-->	Receives long ID of object
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	IndexToObjectIDLong
 *
 *	Given cd/bg descriptor and an index, return the long ID. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr IndexToObjectIDLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Card or Bkgnd to look on
	short index,						//	<--	Index to convert to object descriptor
	Handle *objectStr					//	-->	Receives long ID of object
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	InStandalone
 *
 *	Determines whether the active copy of SuperCard is a standalone. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr InStandalone
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Boolean *inStand					//	-->	Receives true if running in a standalone
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	IsDFResourceFile
 *
 *	Tests whether a specified path points to a file with resources stored
 *	in the data fork (as is typically the case inside bundles). 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

OSErr IsDFResourceFile
(
	XCmdPtr par,
	Handle path,
	Boolean *isDFRezFile
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	IsOpenField
 *
 *	Determines whether a specified object is the currently open field. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr IsOpenField
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Field we are interested in
	Boolean *isOpen						//	-->	Receives true if field is a open
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	IsOpenFieldLong
 *
 *	Determines whether a specified object is the currently open field. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr IsOpenFieldLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Field we are interested in
	Boolean *isOpen						//	-->	Receives true if field is a open
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	IsProjectFile
 *
 *	Tests whether a specified path points to a valid SuperCard project. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

OSErr IsProjectFile
(
	XCmdPtr par,
	Handle path,
	Boolean *isProjFile
 );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	IsRFResourceFile
 *
 *	Tests whether a specified path points to a file with a resource fork. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

OSErr IsRFResourceFile
(
	XCmdPtr par,
	Handle path,
	Boolean *isRFRezFile
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	IsStandalone
 *
 *	Determines whether a specified project is a SuperCard standalone. 
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr IsStandalone
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Project we are interested in
	Boolean *isStand					//	-->	Receives true if project is a standalone
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	IsStandaloneLong
 *
 *	Determines whether a specified project is a SuperCard standalone. 
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr IsStandaloneLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Project we are interested in
	Boolean *isStand					//	-->	Receives true if project is a standalone
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	MakeMenuHandle
 *
 *	Create a menu record from the specified SuperCard menu. The MenuHandle
 *	belongs to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr MakeMenuHandle
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Menu to build MenuHandle from
	MenuHandle *theMenu,				//	-->	Receives new MenuHandle
	short theID							//	<--	MenuID to use for new menu
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	MakeMenuHandleLong
 *
 *	Create a menu record from the specified SuperCard menu. The MenuHandle
 *	belongs to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr MakeMenuHandleLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Menu to build MenuHandle from
	MenuHandle *theMenu,				//	-->	Receives new MenuHandle
	short theID							//	<--	MenuID to use for new menu
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	MakeThumbnail
 *
 *	Create a thumbnail image of a specified card or bkgnd. The PicHandle
 *	belongs to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr MakeThumbnail
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Card or bkgnd to build thumbnail image of
	Boolean contentOnly,				//	<--	Pass true to include just window contents
	Boolean ignoreBars,					//	<--	Pass true to shrink image to omit scrollbars (if any)
	long scale,							//	<--	Scale percentage to use (100 = actual size)
	PicHandle *thePict					//	-->	Receives thumbnail image
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	MakeThumbnailLong
 *
 *	Create a thumbnail image of a specified card or bkgnd. The PicHandle
 *	belongs to you, and it is up to you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr MakeThumbnailLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Card or bkgnd to build thumbnail image of
	Boolean contentOnly,				//	<--	Pass true to include just window contents
	Boolean ignoreBars,					//	<--	Pass true to shrink image to omit scrollbars (if any)
	long scale,							//	<--	Scale percentage to use (100 = actual size)
	PicHandle *thePict					//	-->	Receives thumbnail image
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	NoMemory
 *
 *	Pre-flight a specified amount of memory (calling SC's garbage-collection
 *	routines as required); equivalent to hasMemory(). Obsolete under OS X.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr NoMemory
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	long needed, 						//	<--	Amount of memory you want to preflight
	Boolean *result						//	-->	Receives true if memory is available
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	ObjectToIndex
 *
 *	Given an object descriptor, return an object index. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr ObjectToIndex
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Object to get index of
	short *index						//	-->	Receives index of object
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	ObjectToIndexLong
 *
 *	Given an object descriptor, return an object index. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr ObjectToIndexLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,			//	<--	Object to get index of
	short *index						//	-->	Receives index of object
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	packreserve
 *
 *	Convert RGBColor into SC's packed internal format. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

void packreserve
(
	RGBColor *thecolor, 				//	<--	Color in standard RGB format
	long *thelong						//	-->	Receives packed form of color
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	PackText
 *
 *	Convert a TEHandle into SC's packed internal format. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr PackText
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle *textHand,					//	-->	Receives packed form of text
	TEHandle editHand					//	<--	TEHandle to pack
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	WEPackText
 *
 *	Convert a WEHandle into SC's packed internal format. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr WEPackText
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle *textHand,					//	-->	Receives packed form of text
	WEHandle editHand					//	<--	WEHandle to pack
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	PtInObject
 *
 *	Given an object descriptor and a point, return whether point is in object. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr PtInObject
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString, 			//	<--	Object to do hit-testing on
	Point thePoint, 					//	<--	Point to test
	Boolean *result						//	-->	Receives true if point is in object
);

/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	PtInObjectLong
 *
 *	Given an object descriptor and a point, return whether point is in object. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr PtInObjectLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object to do hit-testing on
	Point thePoint, 					//	<--	Point to test
	Boolean *result						//	-->	Receives true if point is in object
);

/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	ParamIsByReference
 *
 *	Given its zero-based index, test whether a parameter was passed by reference. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr ParamIsByReference
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	short index, 						//	<--	Parameter index to do test
	Boolean *result						//	-->	Receives true if by reference
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetBackTolerance
 *
 *	Set the color matching tolerance for a specified bkgnd. Tolerances 
 *	must be an integral value between 0 and 5, inclusive. Values outside  
 *	this range will be pinned to the minimum or maximum.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetBackTolerance
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Bkgnd to set color tolerance of
	short tolerance						//	<--	Value to set tolerance to
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetBackToleranceLong
 *
 *	Set the color matching tolerance for a specified bkgnd. Tolerances 
 *	must be an integral value between 0 and 5, inclusive. Values outside  
 *	this range will be pinned to the minimum or maximum.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetBackToleranceLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Bkgnd to set color tolerance of
	short tolerance						//	<--	Value to set tolerance to
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetPaintPixel
 *
 *	Set the color of a pixel in the bitmap data from the specified paint  
 *	graphic. Note that the color must be 0..255 for color and 0..1 for B&W.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr SetPaintPixel
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Object to set a pixel in
	Point pt, 							//	<--	Pixel within grc to set color of
	short color,						//	<--	New color of pixel
	short redraw						//	<-- Force update afterwards?
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetPaintPixelLong
 *
 *	Set the color of a pixel in the bitmap data from the specified paint  
 *	graphic. Note that the color must be 0..255 for color and 0..1 for B&W.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr SetPaintPixelLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object to set a pixel in
	Point pt, 							//	<--	Pixel within grc to set color of
	short color,						//	<--	New color of pixel
	short redraw						//	<-- Force update afterwards?
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetBits
 *
 *	Set the bitmap data from the specified paint graphic. After the call
 *	the PixInfo and image data still belong to you, and it is up to you
 *	to dispose of them.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr SetBits
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Object to get the bits of
	PixInfoPtr theInfo					//	<--	Pointer to PixInfo struct
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetBitsLong
 *
 *	Set the bitmap data from the specified paint graphic. After the call
 *	the PixInfo and image data still belong to you, and it is up to you
 *	to dispose of them.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr SetBitsLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object to get the bits of
	PixInfoPtr theInfo					//	<--	Pointer to PixInfo struct
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetBrushes
 *
 *	Set the brushes of a specified project. 
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'. After this call the brush handle DOES NOT belong
 *	to you, and you MUST NOT dispose of it!
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetBrushes
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Project to set brushes of
	BrushesHandle theBrushes			//	<--	Brush data to use
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetBrushesLong
 *
 *	Set the brushes of a specified project. 
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'. After this call the brush handle DOES NOT belong
 *	to you, and you MUST NOT dispose of it!
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetBrushesLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Project to set brushes of
	BrushesHandle theBrushes			//	<--	Brush data to use
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetCardTolerance
 *
 *	Set the color matching tolerance for a specified card. Tolerances 
 *	must be an integral value between 0 and 5, inclusive. Values outside  
 *	this range will be pinned to the minimum or maximum.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetCardTolerance
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Card to set color tolerance of
	short tolerance						//	<--	Value to set tolerance to
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetCardToleranceLong
 *
 *	Set the color matching tolerance for a specified card. Tolerances 
 *	must be an integral value between 0 and 5, inclusive. Values outside  
 *	this range will be pinned to the minimum or maximum.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetCardToleranceLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,			//	<--	Card to set color tolerance of
	short tolerance						//	<--	Value to set tolerance to
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetLinePoints
 *
 *	Set endpoints of the specified line graphic.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr SetLinePoints
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Card Line get the points of
	Point startPoint, 					//	<--	New start point of line
	Point endPoint, 					//	<--	New end point of line
	short redraw						//	<-- Force update afterwards?
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetLinePointsLong
 *
 *	Set endpoints of the specified line graphic.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr SetLinePointsLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Card Line get the points of
	Point startPoint, 					//	<--	New start point of line
	Point endPoint, 					//	<--	New end point of line
	short redraw						//	<-- Force update afterwards?
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetMsgResultStr
 *
 *	Set the text displayed in result area of msg box. Note that this call
 *	does not actually open the msg box, which if required is easily done
 *	using a text callback: SendCardMessage(par, "\pshow msg");
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr SetMsgResultStr
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr theString					//	<--	Text to display in result area of msg box
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetObjectData
 *
 *	Sets the 'raw' data (if any) for the specified object. The form and 
 *	of dataHand depend on the type of object specified. Only some types of
 *	objects have this auxiliary data (polygons grcaphis and buttons, paint 
 *	objects, fields, and text graphics). The purpose of this is to let you  
 *	use other pre-existing objects as 'templates' to derive the associated 
 *	content of new objects from, or to set the content of pre-existing items.
 *	Note that after this operation dataHand DOES NOT belong to you, and so
 * 	you MUST NOT dispose of it!
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr SetObjectData
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Object get ObjectInfo structure for
	Handle dataHand						//	<--	Raw object data
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetObjectDataLong
 *
 *	Sets the 'raw' data (if any) for the specified object. The form and 
 *	of dataHand depend on the type of object specified. Only some types of
 *	objects have this auxiliary data (polygons grcaphis and buttons, paint 
 *	objects, fields, and text graphics). The purpose of this is to let you  
 *	use other pre-existing objects as 'templates' to derive the associated 
 *	content of new objects from, or to set the content of pre-existing items.
 *	Note that after this operation dataHand DOES NOT belong to you, and so
 * 	you MUST NOT dispose of it!
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr SetObjectDataLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object get ObjectInfo structure for
	Handle dataHand						//	<--	Raw object data
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetObjectInfo
 *
 *	Set the properties of a specified object based on the values in a 
 *	supplied ScriptInfo structure. After this call ObjectInfoHandle still
 *	belongs to you, and it is up to you to dispose of it. Don't forget to
 *	dispose of the name handle (if any) first!
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetObjectInfo
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Object to set properties of
	ObjectInfoHandle infoHand,			//	<--	ScriptInfo to get values from
	short redraw						//	<-- Force update afterwards?
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetObjectInfoLong
 *
 *	Set the properties of a specified object based on the values in a 
 *	supplied ScriptInfo structure. After this call ObjectInfoHandle still
 *	belongs to you, and it is up to you to dispose of it. Don't forget to
 *	dispose of the name handle (if any) first!
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetObjectInfoLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object to set properties of
	ObjectInfoHandle infoHand,			//	<--	ScriptInfo to get values from
	short redraw						//	<-- Force update afterwards?
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetObjectInfoByIndex
 *
 *	Get an ObjectInfo struct for the Nth object. Note that the index is
 *	zero-based. After this call ObjectInfoHandle still belongs to you, and
 *	it is up to you to dispose of it. Don't forget to dispose of the name 
 *	handle (if any) first!
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr SetObjectInfoByIndex
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Cd or bkgnd object is on
	short index,						//	<--	Zero-based object index
	ObjectInfoHandle infoHand,			//	<--	ObjectInfo structure
	short redraw						//	<-- Force update afterwards?
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetObjectInfoByIndexLong
 *
 *	Get an ObjectInfo struct for the Nth object. Note that the index is
 *	zero-based. After this call ObjectInfoHandle still belongs to you, and
 *	it is up to you to dispose of it. Don't forget to dispose of the name 
 *	handle (if any) first!
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr SetObjectInfoByIndexLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Cd or bkgnd object is on
	short index,						//	<--	Zero-based object index
	ObjectInfoHandle infoHand,			//	<--	ObjectInfo structure
	short redraw						//	<-- Force update afterwards?
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetObjectScript
 *
 *	Set the script of a specified oobject. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetObjectScript
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Script to set attributes of
	Handle theScript					//	<--	New script for object
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetObjectScriptLong
 *
 *	Set the script of a specified oobject. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetObjectScriptLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Script to set attributes of
	Handle theScript					//	<--	New script for object
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetPatterns
 *
 *	Set the patterns of a specified project. 
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'. After this call thePatterns still belongs to you,
 *	and it is up to you to dispose of it. Don't forget to dispose of the 
 *	name handle (if any) first!
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetPatterns
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Project to set patterns of
	PatternsHandle thePatterns			//	<--	Patterns data to use
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetPatternsLong
 *
 *	Set the patterns of a specified project. 
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'. After this call thePatterns still belongs to you,
 *	and it is up to you to dispose of it. Don't forget to dispose of the 
 *	name handle (if any) first!
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetPatternsLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Project to set patterns of
	PatternsHandle thePatterns			//	<--	Patterns data to use
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetPictureData
 *
 *	Set the pictureData of the specified object. To set embedded pictureData 
 *	you pass a PicHandle (cast as a Handle) in param #3 and pass TRUE in 
 *	param #4. To set pictureData by reference, pass the path in a Handle in
 *	param #3, and pass FALSE in param #4. After this call completes, the 
 *	data handle DOES NOT belong to you, and you MUST NOT dispose of it! Note
 *	that this also means you must not pass an XCMD parameter handle directly
 *	to this function, but instead you must pass a COPY of the parameter 
 *	handle (so that when SC disposes of the param block, the reference will
 *	not become invalid).
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr SetPictureData
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Object to set pictureData of
	Handle theData,						//	<--	Picture data or path
	Boolean embedded,					//	<--	TRUE if Picture data, FALSE if path
	short redraw						//	<-- Force update afterwards?
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetPictureDataLong
 *
 *	Set the pictureData of the specified object. To set embedded pictureData 
 *	you pass a PicHandle (cast as a Handle) in param #3 and pass TRUE in 
 *	param #4. To set pictureData by reference, pass the path in a Handle in
 *	param #3, and pass FALSE in param #4. After this call completes, the 
 *	data handle DOES NOT belong to you, and you MUST NOT dispose of it! Note
 *	that this also means you must not pass an XCMD parameter handle directly
 *	to this function, but instead you must pass a COPY of the parameter 
 *	handle (so that when SC disposes of the param block, the reference will
 *	not become invalid).
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr SetPictureDataLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object to set pictureData of
	Handle theData,						//	<--	Picture data or path
	Boolean embedded,					//	<--	TRUE if Picture data, FALSE if path
	short redraw						//	<-- Force update afterwards?
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetPictureInfo
 *
 *	Set the pictureInfo of the specified object. After this call completes, 
 *	theInfo DOES NOT belong to you, and you MUST NOT dispose of it! 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr SetPictureInfo
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Object to set pictureInfo of
	PDInfoHandle theInfo,				//	<--	Picture info handle
	short redraw						//	<-- Force update afterwards?
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetPictureInfoLong
 *
 *	Set the pictureInfo of the specified object. After this call completes, 
 *	theInfo DOES NOT belong to you, and you MUST NOT dispose of it! 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr SetPictureInfoLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object to set pictureInfo of
	PDInfoHandle theInfo,				//	<--	Picture info handle
	short redraw						//	<-- Force update afterwards?
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetPolyHandle
 *
 *	Set the polyHandle for the specified polygon object. Note that after
 *	this call ends the PolyHandle still belongs to you, and it is up to
 *	you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr SetPolyHandle
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Object to get PolyHandle from
	PolyHandle thePoly,					//	<--	PolyHandle with new data
	short redraw						//	<-- Force update afterwards?
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetPolyHandleLong
 *
 *	Set the polyHandle for the specified polygon object. Note that after
 *	this call ends the PolyHandle still belongs to you, and it is up to
 *	you to dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */
 
SCErr SetPolyHandleLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object to get PolyHandle from
	PolyHandle thePoly,					//	<--	PolyHandle with new data
	short redraw						//	<-- Force update afterwards?
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetPrivateNum
 *
 *	Store a value in the PrivateNum field of a specified project. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetPrivateNum	
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Project to set PrivateNum of
	long theNum							//	<--	Value to store in PrivateNum
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetPrivateNumLong
 *
 *	Store a value in the PrivateNum field of a specified project. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetPrivateNumLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Project to set PrivateNum of
	long theNum							//	<--	Value to store in PrivateNum
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetProjStarID
 *
 *	Set the ID of a specified star resource in a specified project. 
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetProjStarID
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Project to set star ID in
	long theID,							//	<--	Current ID of resource to set ID of
	ResType theType,					//	<--	Four byte type code of the resource
	long newID,							//	<--	New ID for resource
	Boolean replace						//	<--	Pass true to overwrite any existing resource with same ID
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetProjStarIDLong
 *
 *	Set the ID of a specified star resource in a specified project. 
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetProjStarIDLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Project to set star ID in
	long theID,							//	<--	Current ID of resource to set ID of
	ResType theType,					//	<--	Four byte type code of the resource
	long newID,							//	<--	New ID for resource
	Boolean replace						//	<--	Pass true to overwrite any existing resource with same ID
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetProjStarName
 *
 *	Set the name of a specified star resource in a specified project. 
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetProjStarName
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Project to set star ID in
	long theID,							//	<--	Current ID of resource to set ID of
	ResType theType,					//	<--	Four byte type code of the resource
	StringPtr newName					//	<--	New name for resource
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetProjStarNameLong
 *
 *	Set the name of a specified star resource in a specified project. 
 *	Note that descriptString must be in the form of a project descriptor
 *	(e.g., 'this project' or 'project "RAM Disk:test"'). A path string
 *	is not a valid project descriptor - it must be quoted and preceded by
 *	the word 'project'
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetProjStarNameLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Project to set star ID in
	long theID,							//	<--	Current ID of resource to set ID of
	ResType theType,					//	<--	Four byte type code of the resource
	StringPtr newName					//	<--	New name for resource
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetScriptAttrs
 *
 *	Set the formatting attributes (textFont, textSize, and tab width) of a 
 *	specified script in a specified project. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetScriptAttrs
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Script to set attributes of
	ScriptInfo *theInfo					//	<--	ScriptInfo struct to get new values from
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetScriptAttrsLong
 *
 *	Set the formatting attributes (textFont, textSize, and tab width) of a 
 *	specified script in a specified project. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetScriptAttrsLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Script to set attributes of
	ScriptInfo *theInfo					//	<--	ScriptInfo struct to get new values from
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetSFStarID
 *
 *	Set the ID of a specified star resource in the SharedFile project. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetSFStarID
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	long theID,							//	<--	Current ID of resource to set ID of
	ResType theType,					//	<--	Four byte type code of the resource
	long newID,							//	<--	New ID for resource
	Boolean replace						//	<--	Pass true to overwrite any existing resource with same ID
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetSFStarName
 *
 *	Set the name of a specified star resource in the SharedFile project. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetSFStarName
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	long theID,							//	<--	Current ID of resource to set ID of
	ResType theType,					//	<--	Four byte type code of the resource
	StringPtr newName					//	<--	New name for resource
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetSuppressionFlag
 *
 *	Turn SuperCard's Page Setup and Print dialogs on or off. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetSuppressionFlag
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Boolean suppress					//	<--	Pass true to suppress dialogs when printing
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetTEHandle
 *
 *	Set the contents of a field to data in a supplied TEHandle. After this
 *	call ends, the TEHandle still belongs to you, and it is up to you to
 *	dispose of it. If a field is open, you cannot replace its TERec; instead 
 *	you must use GetCurTEHandle to get the TERec in use for editing it, then 
 *	call TouchCurTEHandle() to tell SuperCard you have changed it. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

/*SCErr SetTEHandle
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Object to replace TERec of
	TEHandle editHand					//	<--	TEHandle to get new text and style info from
);*/


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetWEHandle
 *
 *	Set the contents of a field to data in a supplied WEHandle. Note that
 *	if a field is open, you cannot replace its TE/WERec; instead you must
 *	use GetCurTEHandle to get the TE/WERec in use for editing it, then call
 *	TouchCurTEHandle() to tell SuperCard you have changed it. After this
 *	call ends, the WEHandle still belongs to you, and it is up to you to
 *	dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetWEHandle
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Object to replace WERec of
	WEHandle editHand					//	<--	WEHandle to get new text and style info from
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	SetWEHandleLong
 *
 *	Set the contents of a field to data in a supplied WEHandle. Note that
 *	if a field is open, you cannot replace its TE/WERec; instead you must
 *	use GetCurTEHandle to get the TE/WERec in use for editing it, then call
 *	TouchCurTEHandle() to tell SuperCard you have changed it. After this
 *	call ends, the WEHandle still belongs to you, and it is up to you to
 *	dispose of it.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr SetWEHandleLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object to replace WERec of
	WEHandle editHand					//	<--	WEHandle to get new text and style info from
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	TouchCurWEHandle
 *
 *	Tell SuperCard you have changed the contents of the open field by
 *	tweaking the current TEHandle. Unless you use this routine, you cannot
 *	guarantee that such changes will be saved (it would depend on
 *	whether SC thinks the field is dirty for some other reason)
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr TouchCurWEHandle
(
	XCmdPtr par 						//	<--	Parameter block pointer
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	TouchUIWEHandle
 *
 *	Tell SuperCard you have changed the contents of a field's display WERec.
 *	Unless you use this routine, you cannot guarantee that such changes will
 *	be saved (it would depend on whether SC thinks the field is dirty for
 *	some other reason)
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr TouchUIWEHandle
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr descriptString,			//	<--	Object to touch WERec of
	short writethrough					//	<--	Write changes back to file now?
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	TouchUIWEHandleLong
 *
 *	Tell SuperCard you have changed the contents of a field's display WERec.
 *	Unless you use this routine, you cannot guarantee that such changes will
 *	be saved (it would depend on whether SC thinks the field is dirty for
 *	some other reason)
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr TouchUIWEHandleLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle descriptString,				//	<--	Object to touch WERec of
	short writethrough					//	<--	Write changes back to file now?
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	unpackreserve
 *
 *	Convert SC's packed internal color format for monostyle TERecs 
 *	into an RGBColor. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

void  unpackreserve
(
	long *thelong, 						//	<--	SC's internal 'packed' color
	RGBColor *thecolor					//	-->	Receives unpacked color
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	UnPackText
 *
 *	Convert SC's packed internal text format into a TEHandle. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr UnPackText
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle textHand,					//	<--	SC's internal 'packed' form of text
	TEHandle *editHand,					//	-->	Receives TEHandle with unpacked text
	Rect *dest,							//	<--	destRect for new TERec
	Rect *view,							//	<--	viewRect for new TERec
	long dontWrap						//	<--	dontWrap flag for new TERec
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	WEUnPackText
 *
 *	Convert SC's packed internal text format into a WEHandle. 
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr WEUnPackText
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle textHand,					//	<--	SC's internal 'packed' form of text
	WEHandle *editHand,					//	-->	Receives WEHandle with unpacked text
	LongRect *dest,						//	<--	destRect for new WERec
	LongRect *view,						//	<--	viewRect for new WERec
	long dontWrap						//	<--	dontWrap flag for new TERec
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	UpdateWindow
 *
 *	Force SC to redraw all or part of a window. Note that for your 
 *	convenience UpdateWindow accepts not just window names, but also any
 *	valid bkgnd, card, or object descriptor. This means you don't need to
 *	do any funny business to reduce a descriptor of a modified object to
 *	a descriptor of the window it resides in. Instead you can simply pass
 *	whatever kind of descriptor you have, and UpdateWindow will figure out
 *	which window the bkgnd, card or object is in for you automatically.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr UpdateWindow
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	StringPtr wdDesc,					//	<--	The window to update
	Rect *area							//	<--	Rectangle within wd to update, or nil
);


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	UpdateWindowLong
 *
 *	Force SC to redraw all or part of a window. Note that for your 
 *	convenience UpdateWindow accepts not just window names, but also any
 *	valid bkgnd, card, or object descriptor. This means you don't need to
 *	do any funny business to reduce a descriptor of a modified object to
 *	a descriptor of the window it resides in. Instead you can simply pass
 *	whatever kind of descriptor you have, and UpdateWindow will figure out
 *	which window the bkgnd, card or object is in for you automatically.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

SCErr UpdateWindowLong
(
	XCmdPtr par, 						//	<--	Parameter block pointer
	Handle wdDesc,						//	<--	The window to update
	Rect *area							//	<--	Rectangle within wd to update, or nil
);


SCErr weActivate				(XCmdPtr par, WEHandle we);
short weAllowsObjects			(XCmdPtr par, WEHandle we);
SCErr weBuildFontTable			(XCmdPtr par, WEHandle we, Handle hFontTable, WEFontIDToNameUPP fontIDToNameProc);
SCErr weCalText					(XCmdPtr par, WEHandle we);
SCErr weCanPaste				(XCmdPtr par, WEHandle we, Boolean *canPaste);
SCErr weCharByte				(XCmdPtr par, WEHandle we, long offset, short *byte);
SCErr weCharType				(XCmdPtr par, WEHandle we, long offset, short *type);
SCErr weClick					(XCmdPtr par, WEHandle we, Point mouseLoc, EventModifiers modifiers, unsigned long clickTime);
SCErr weContinuousRuler			(XCmdPtr par, WEHandle we, WERulerMode *mode, WERuler *ruler, Boolean *tf);
SCErr weContinuousStyle			(XCmdPtr par, WEHandle we, WEStyleMode *mode, TextStyle *ts, Boolean *tf);
SCErr weCopy					(XCmdPtr par, WEHandle we);
SCErr weCopyFieldToField		(XCmdPtr par, WEHandle weSRC, SInt32 srcBegin, SInt32 srcEnd, WEHandle weDST, SInt32 dstBegin, SInt32 dstEnd);
SCErr weCopyRange				(XCmdPtr par, WEHandle we, SInt32 rangeStart, SInt32 rangeEnd, Handle hText, Handle hStyles, Handle hSoup);
SCErr weCountLines				(XCmdPtr par, WEHandle we, long *numLines);
SCErr weCut						(XCmdPtr par, WEHandle we);
SCErr weDelete					(XCmdPtr par, WEHandle we);
SCErr weDeactivate				(XCmdPtr par, WEHandle we);
SCErr weDispose					(XCmdPtr par, WEHandle we);
SCErr weFindLine				(XCmdPtr par, WEHandle we, long offset, WEEdge edge, long *startChar, long *endChar);
SCErr weFindParagraph			(XCmdPtr par, WEHandle we, long offset, WEEdge edge, long *startChar, long *endChar);
SCErr weFindWord				(XCmdPtr par, WEHandle we, long offset, WEEdge edge, long *startChar, long *endChar);
SCErr weGetChar					(XCmdPtr par, WEHandle we, long offset, SInt16 *c);
SCErr weGetHeight				(XCmdPtr par, WEHandle we, long startChar, long endChar, long *height);
SCErr weGetMargins				(XCmdPtr par, WEHandle we, Rect *margins);
SCErr weGetObjectAtOffset		(XCmdPtr par, WEHandle we, const SInt32 offset, WEObjectDescHandle *inObjectDesc);
SCErr weGetObjectBaseline		(XCmdPtr par, WEObjectDescHandle inObjectDesc, SInt16 *baseline);
SCErr weGetObjectByID			(XCmdPtr par, WEHandle we, const SInt32 ID, WEObjectDescHandle *inObjectDesc);
SCErr weGetObjectByIndex		(XCmdPtr par, WEHandle we, const SInt32 index, WEObjectDescHandle *inObjectDesc);
SCErr weGetObjectByName			(XCmdPtr par, WEHandle we, const Handle name, WEObjectDescHandle *inObjectDesc);
SCErr weGetObjectFrame			(XCmdPtr par, WEObjectDescHandle inObjectDesc, LongRect *);
SCErr weGetObjectCount			(XCmdPtr par, WEHandle we, SInt32 *count);
SCErr weGetObjectID				(XCmdPtr par, WEObjectDescHandle inObjectDesc, SInt32 *);
SCErr weGetObjectImage			(XCmdPtr par, WEObjectDescHandle inObjectDesc, PicHandle *);
SCErr weGetObjectName			(XCmdPtr par, WEObjectDescHandle inObjectDesc, Handle *name);
SCErr weGetObjectOwner			(XCmdPtr par, WEObjectDescHandle inObjectDesc, WEHandle *we);
SCErr weGetObjectProperty		(XCmdPtr par, WEObjectDescHandle inObjectDesc, OSType owner, OSType tag, Handle *data);
SCErr weGetObjectRefCon			(XCmdPtr par, WEObjectDescHandle inObjectDesc, SInt32 *refcon);
SCErr weGetObjectType			(XCmdPtr par, WEObjectDescHandle inObjectDesc, FlavorType *type);
SCErr weGetOffset				(XCmdPtr par, WEHandle we, const LongPt *thePoint, WEEdge *edge, long *offset);
SCErr weGetOneAttribute			(XCmdPtr par, WEHandle we, SInt32 offset, WESelector selector, void * value, ByteCount size, OSErr *err);
SCErr weGetPoint				(XCmdPtr par, WEHandle we, long offset, SInt16 direction, LongPt *thePoint, SInt16 *lineHeight);
SCErr weGetSelection			(XCmdPtr par, WEHandle we, long *startChar, long *endChar);
SCErr weGetText					(XCmdPtr par, WEHandle we, Handle *text);
SCErr weGetTextLength			(XCmdPtr par, WEHandle we, long *length);
SCErr weInsert					(XCmdPtr par, WEHandle we, Ptr textPtr, long textLength, StScrpHandle hStyles, Handle hSoup);
SCErr weInsertFormattedText		(XCmdPtr par, WEHandle we, Ptr textPtr, long textLength, StScrpHandle hStyles, Handle hSoup, Handle hParaFormat, Handle hRulerScrap);
SCErr weInsertObject			(XCmdPtr par, WEHandle we, const FlavorType flavor, const Handle data, const Point size);
SCErr weIsActive				(XCmdPtr par, WEHandle we, Boolean *isActive);
SCErr weKey						(XCmdPtr par, WEHandle we, SInt16 key, EventModifiers modifiers);
SCErr weNew						(XCmdPtr par, WEHandle *we, const LongRect *destRect, const LongRect *viewRect, UInt32 features);
SCErr weOffsetToLine			(XCmdPtr par, WEHandle we, long offset, long *line);
SCErr weOffsetToParaRun			(XCmdPtr par, WEHandle we, long offset, long *index);
SCErr wePaste					(XCmdPtr par, WEHandle we);
SCErr wePut						(XCmdPtr par, WEHandle we, long start, long end, const char *inTextPtr, ByteCount inTextLength, 
										TextEncoding inTextEncoding, OptionBits inPutOptions, ItemCount inFlavorCount,
										const FlavorType * inFlavorTypes, const Handle *inFlavorHandles);
SCErr weRemoveObjectProperty	(XCmdPtr par, WEObjectDescHandle inObjectDesc, OSType owner, OSType tag);
SCErr weScroll					(XCmdPtr par, WEHandle we, long scrollh, long scrollv);
SCErr weSelView					(XCmdPtr par, WEHandle we);
SCErr weSetObjectBaseline		(XCmdPtr par, WEObjectDescHandle inObjectDesc, SInt16 baseline);
SCErr weSetObjectImage			(XCmdPtr par, WEObjectDescHandle inObjectDesc, PicHandle hPic, short constrain);
SCErr weSetObjectName			(XCmdPtr par, WEObjectDescHandle inObjectDesc, Handle name);
SCErr weSetObjectPlacement		(XCmdPtr par, WEObjectDescHandle inObjectDesc, WEObjectPlacement *placement);
SCErr weSetObjectProperty		(XCmdPtr par, WEObjectDescHandle inObjectDesc, OSType owner, OSType tag, Handle data);
SCErr weSetObjectRefCon			(XCmdPtr par, WEObjectDescHandle inObjectDesc, SInt32 refcon);
SCErr weSetSelection			(XCmdPtr par, WEHandle we, long startChar, long endChar);
SCErr weSetStyle				(XCmdPtr par, WEHandle we, WEStyleMode mode, const TextStyle *ts);
SCErr weStreamRange				(XCmdPtr par, WEHandle we, long rangeStart, long rangeEnd, FlavorType dataFlavor, OptionBits inStreamOptions, Handle hData);
SCErr weUpdate					(XCmdPtr par, WEHandle we, RgnHandle updateRgn);
SCErr weUpdateFontTable			(XCmdPtr par, Handle hFontTable, WEFontNameToIDUPP fontNameToIDProc, Boolean *wasChanged);
SCErr weUpdateStyleScrap		(XCmdPtr par, StScrpHandle hStyles, Handle hFontTable);
SCErr weUseStyleScrap			(XCmdPtr par, WEHandle we, StScrpHandle hStyles);
SCErr weUseText					(XCmdPtr par, WEHandle we, Handle text);
SCErr weVersion					(XCmdPtr par, long *version);
SCErr weGetInfo					(XCmdPtr par, WEHandle we, WESelector selector, void *info);
SCErr weSetInfo					(XCmdPtr par, WEHandle we, WESelector selector, void *info);
SCErr weSetDestRect				(XCmdPtr par, WEHandle we, LongRect *r);
SCErr weSetViewRect				(XCmdPtr par, WEHandle we, LongRect *r);
SCErr weFeatureFlag				(XCmdPtr par, WEHandle we, SInt16 feature, SInt16 action);
SCErr weSetAlignment			(XCmdPtr par, WEHandle we, WEAlignment selector);

void GetGAddr(XCmdPtr, long);

#endif