//	SuperCard 4.72 xrtnRT.h file
//	Typedefs and other definitions for XRtn routines
//	Copyright 2011 Solutions Etcetera and Mark Lucas
//	All rights reserved worldwide.
#ifndef __xrtnRT__

#define __xrtnRT__

//#ifdef __powerc__ 
//	#pragma pointers_in_D0
//#endif

/* the structure of a XRTN routine. It is in two parts, a scriptentry and an evententry.
These two routines are called from either the script engine or the getevent mechanism.
Your code will have a general structure like this:

#include "x.h"
#include "z.h"

evententry()
								// Macro "evententry" contains the "{"
	initcallbacks(); 			// MUST be called before any callback
	event = GetEvent();
	what = GetEventRecordPtr()->what;
	window = GetEventWindow();
	refcon = GetEventRefcon();	// these defines pull values from the argument list AND can
								// only be called from this procedure!
	...
	restorecallbacks();			// restores global pointer to original value
	return(process_the_event); 	// if false, let SuperCard do its normal event routine.
							   	// if true, it has already been taken care of.
}


scriptentry()
								// Macro "scriptentry" contains the "{"
	initcallbacks();			// MUST be called before any callback
	...
	restorecallbacks();			// restores global pointer to original value
}

*/

	//	These are the equates for error codes returned by 
	//	those Internals Toolbox routines that return an SCErr.

/*enum errNum {
	isOK = 0,					//	no error
	noSuchObject = -10000,		//	specified object non-existent
	noSuchCard = -9999,			//	specified card non-existent
	noSuchBkgnd = -9998,		//	specified background non-existent
	noSuchCdBg = -9997,			//	specified card or background non-existent
	noSuchWind = -9996,			//	specified window non-existent
	noSuchMenu = -9995,			//	specified menu non-existent
	noSuchProj = -9994,			//	specified project non-existent
	badReadType = -9993,		//	invalid card, bkgnd, window, or file type
	badObjType = -9992,			//	invalid object type
	badSpotType = -9991,		//	invalid graphic type
	windNotOpen = -9990,		//	specified window is not currently open
	badRefHdl = -9989,			//	invalid or nil object reference handle
	badIndRange = -9988,		//	supplied index number out of range
	noActiveFld = -9987,		//	no currently active field
	noScript = -9986,			//	specified object has no script
	noSharedFile = -9985,		//	SharedFile project non-existent
	noSuchStar = -9984,			//	specified project resource non-existent
	notInColor = -9983,			//	application not running under 8-bit color
	noMemory = -9982,			//	out of memory
	emptyRect = -9981,			//	specified rectangle is empty
	badAddStar = -9980,			//	failed to add new project resource
	badVersion = -9979,			//	invalid SuperCard version
	badMakeSpec = -9978,		//	FSMakeFSSpec failed; spec may be valid
	badNewAlias = -9977,		//	NewAlias failed
	noPictureData = -9976,		//	draw graphic has no pictureData
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
	noClutInUse = -9959			//	no clut currently assigned
};*/

#define unloadflag 2	

#define __SUPPORTS_LONG_FILENAMES__	1

#pragma options align = mac68k

enum {				// the callback procedure list
	HNewWin,
	HShowWin,
	HHideWin,
	HMoveWin,
	HSizeWin,
	HCloseWin,
	HSetWinPosition,
	HGetWinPosition,
	HShowHidePalettes,
	HGetWindowPtr,
	
	HSetReturnValString,
	HSetReturnValHandle,
	HAskSC,
	HAnswerSC,
	HGetFrontMostWindInfo,
	HRegisterEvent,
	HUnRegisterEvent,
	HPostXRTNEvent,
	HSendMessage,
	HHasMemory,
	HFormatString,
	HDecodeString,
	HDecodeParam,
	
	HEvalExpHandle,
	HEvalExpString,
	HEvalExpDouble,
	HEvalExpLong,
	
	HGetGlobalHandle,
	HGetGlobalString,
	HGetGlobalDouble,
	HGetGlobalLong,
	
	HSetGlobalHandle,
	HSetGlobalString,
	HSetGlobalDouble,
	HSetGlobalLong,
	
	HGetParamHandle,
	HGetParamString,
	HGetParamDouble,
	HGetParamLong,
	HGetParamLength,
	
	HGetFieldHandle,
	HGetFieldString,
	HSetFieldHandle,
	HSetFieldString,

// ** MDL 12/6/98 **
	HShowHideSCPalettes,
	HGetSCWindowPtr,
	HGetFieldTEHandle,
	HSetFieldTEHandle,
	HGetCurTEHandle,
	HTouchCurTEHandle,
	HGetRead,
	HPutRead,
	HGetGAddr,
// **
#if __SUPPORTS_LONG_FILENAMES__
	HGetReadLong,
	HEvalLongExpHandle,
	HEvalLongExpString,
	HEvalLongExpDouble,
	HEvalLongExpLong,
	HSendMessageLong,
	HGetFieldHandleLong,
	HGetFieldStringLong,
	HSetFieldHandleLong,
	HSetFieldStringLong,
#endif __SUPPORTS_LONG_FILENAMES__

	HGetSCWindowID,
		
	maxprocs
};

enum {				// the events that can be passed to the XRTN
	xcontentEvent = 2000,
	xnullEvent,    // any time waitnextevent returns false
	xdragEvent,
	xgrowEvent,
//	xcloseEvent,
	xcloseboxEvent,
	xzoominEvent,
	xzoomoutEvent,
	xactivateEvent,
	xupdateEvent,
	xappleEvent,
	xdiskEvent,
	xresumeEvent,
	xsuspendEvent,
	xkeyEvent,
	xautoKeyEvent,
	xuniversalEvent, // any time waitnextevent returns true
	xmouseWithinEvent,
	//xgoawayEvent,
	xshutdownEvent,
	xcutEvent,
	xcopyEvent,
	xpasteEvent,
	xundoEvent,
	xclearEvent,
// ¥¥ MDL 10/20/00 ¥¥
// Let xrtns register for the new undo event
	xredoEvent,
// ¥¥
// ¥¥ MDL 10-26-00 ¥¥
// New callbacks added to allow xrtns to intercept menu events.
// The first callback is sent whenever SuperCard rebuilds the menu bar.
// The second callback is sent prior to calling MenuClick, MenuKey, or MenuEvent.
// Note that this doesn't necessarily indicate a menu drop will occur (we can't 
// really know that in advance), just that we should prepare for one if we need to.
// The third callback comes after a menu hit has occurred, giving the xrtn a
// chance to intercept the itemSelect prior to script processing
	xbuildMenuBarEvent,
	xdrawMenuBarEvent,
	xprePopUpMenuEvent,
	xpreMenuEvent,
	xpostMenuEvent,
// ¥¥
// ¥¥ MDL 10-29-00 ¥¥
// Let xrtns register for the new init and dump events
	xinitEvent,
	xdumpEvent,
// ¥¥ 
// ¥¥ MDL 10-31-00 ¥¥
// Let xrtns register separately for the collapse control and proxy icon click events
	xcollapseEvent,
	xproxyIconClickEvent,
// ¥¥ 
	xclicklistEvent,		// Sent prior to calling clickList
	xupdatebrowserEvent,	// We did something we know will require a refresh of an object browser

	eventMax
};



typedef struct {			// the data structure passed in. ALL fields private to SuperCard.
	short flags;
	short type;
	long argcount;
	Handle args;
	Handle vars;
	Ptr returndata;
	Ptr scripthier;
	Ptr origination;
	Ptr path;
	UniversalProcPtr *theprocs;
} xrtn, *xrtnptr;


typedef struct {
	short layer;
	short position;
	Rect  bounds;
	WindowPtr window;
	Boolean found;
	Boolean visible;
	unsigned char objectID[256];
} InfoRec;



enum {
	wantlong,
	wantdouble,
	wantstring,
	wanthandle
};

// ** MDL 12/7/98 **
enum wdClass {
	eXWds,
	eSWds,
	eAllWds
};
// **

#if ! intesting
//#include <setupA4.h>
int main(xrtnptr callbackaddr);

#define scriptentry() \
	xrtnptr xrtn_addr;\
	UniversalProcPtr post_addr;\
	int main(xrtnptr callbackaddr) \
	{\
	xrtnptr savexrtn;


#define evententry() \
	xrtnptr xrtn_addr; \
	UniversalProcPtr post_addr;\
	static short events(long event_event, EventRecord *event_record, WindowPtr event_window, long event_refcon, xrtnptr callbackaddr) \
	{\
	xrtnptr savexrtn;

#endif


#define ucp(x) (unsigned char *)"\p"x
#define stdpalette (32)*16				// procid for SuperCard's palette WDEF
#define refer(x) if (0) sizeof(x);

#if TARGET_API_MAC_CARBON
#define versgetgaddr	2
#else
#define versgetgaddr	1
#endif
#define versgetread		3
#define versgetreadlong	4
#define versputread		3
#define versrequest		-1

//                      Callback Routines

// Macro defined
#define GetEvent() (event_event)				// these get the event params from the 
#define GetEventRecordPtr() (event_record)		// argument list for evententry()
#define GetEventWindow() (event_window)
#define GetEventRefcon() (event_refcon)

#define initcallbacks() \
	savexrtn = xrtn_addr; \
	xrtn_addr = callbackaddr; \
	post_addr = xrtn_addr->theprocs[HPostXRTNEvent];

#define restorecallbacks()  \
	xrtn_addr = savexrtn;

#define GetParamCount() xrtn_addr->argcount		 // returns the argument count from script entry
#define UnloadXRTN() (xrtn_addr->flags |= unloadflag)	 // flags SuperCard to remove XRTN from heap
												 // also removes all events registered
extern xrtnptr xrtn_addr;

/*-----------------------------------------------------------------------------------------
	window NewWin(bounds, name,  visible,  procid,  close,  ispalette)
			: create a new window
window		<-:windowptr of created window
bounds 		->:the bounding box of the new window
name		->:name of new window
visible 	->:true show it 
procid		->:the procid of the window, stdpalette is SuperCards palette proc 
close		->:true have close box
ispalette	->:true put in palette list
*/

typedef WindowPtr (*TNewWin)(Rect *bounds, unsigned char *name, Boolean visible, short procid, Boolean close, Boolean ispalette);
#define NewWin(bounds, name,  visible,  procid,  close,  ispalette) (*(TNewWin)xrtn_addr->theprocs[HNewWin])(bounds, name,  visible,  procid,  close,  ispalette);

/*-----------------------------------------------------------------------------------------
	ShowWin(window)
			: show a window
window		->:the window pointer
*/

typedef void (*TShowWin)(WindowPtr);
#define ShowWin(window) (*(TShowWin)xrtn_addr->theprocs[HShowWin])(window)

/*-----------------------------------------------------------------------------------------
	HideWin(window)
			: hide a window
window		->:the window pointer
*/

typedef void (*THideWin)(WindowPtr);
#define HideWin(window) (*(THideWin)xrtn_addr->theprocs[HHideWin])(window)

/*-----------------------------------------------------------------------------------------
	MoveWin(window, loc, center)
			:move a window, center window to loc or topleft to loc
window		->:the window pointer
loc			->:where to move it
center		->:true use window's center, false use window's topleft
*/

typedef void (*TMoveWin)(WindowPtr, Point, Boolean);
#define MoveWin(window, loc, center) (*(TMoveWin)xrtn_addr->theprocs[HMoveWin])(window, loc, center)

/*-----------------------------------------------------------------------------------------
	SizeWin(window, width, height, center)
			:resize a window, center window to loc or topleft to loc
window		->:the window pointer
width		->:new width of window
height		->:new height of window
center		->:true use window's center, false use window's topleft
*/

typedef void (*TSizeWin)(WindowPtr, short, short, Boolean);
#define SizeWin(window, width, height, center) (*(TSizeWin)xrtn_addr->theprocs[HSizeWin])(window, width, height, center)

/*-----------------------------------------------------------------------------------------
	CloseWin(window)
			: close a window
window		->:the window pointer
*/

typedef void (*TCloseWin)(WindowPtr);
#define CloseWin(window) (*(TCloseWin)xrtn_addr->theprocs[HCloseWin])(window)

/*-----------------------------------------------------------------------------------------
	SetReturnValString(string)
			:return function result from string
string		->:string containing return value
*/

typedef void (*TSetReturnValString)(unsigned char *, xrtnptr);
#define SetReturnValString(string) (*(TSetReturnValString)xrtn_addr->theprocs[HSetReturnValString])(string, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	SetReturnValHandle(hand)
			:return function result from handle
hand		->:handle containing return value
*/

typedef void (*TSetReturnValHandle)(Handle, xrtnptr);
#define SetReturnValHandle(hand) (*(TSetReturnValHandle)xrtn_addr->theprocs[HSetReturnValHandle])(hand, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	RegisterEvent(event, identifier, ref)
			:inform SuperCard what events you want to see.
event		->:the event code of interest
identifier	->:the system will identify by window, PostXRTNEvent can have arbitrary identifier, 0 = dont care
ref			->:value to be passed to routine
*/

typedef short (*TEventProc)(long event, EventRecord *eventrecord, WindowPtr, long, xrtnptr);
typedef void (*TRegisterEvent)(long event, WindowPtr window, long ref, TEventProc, xrtnptr);
#define RegisterEvent(event, window, ref) (*(TRegisterEvent)xrtn_addr->theprocs[HRegisterEvent])(event, window, ref, (TEventProc)events, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	result UnRegisterEvent(event, window)
			:inform SuperCard what events you dont want to see.
result		<-:true found at least one to remove
event		->:the event code of interest
identifier	->:from what identifier, 0 = delete all of type event
*/

typedef short (*TUnRegisterEvent)(long event, WindowPtr window);
#define UnRegisterEvent(event, window) (*(TUnRegisterEvent)xrtn_addr->theprocs[HUnRegisterEvent])(event, window)


/*-----------------------------------------------------------------------------------------
		   PostXRTNEvent(event, identifier, refcon)
			:place an event request in a queue, will call evententry later to process it
event		->:any event number
identifier	->:identifier to get event, or 0 = dont care
refcon		->:value to be passed to routine
*/

typedef void (*TPostXRTNEvent)(long, long, long);
#define PostXRTNEvent(event, identifier, refcon)  (*(TPostXRTNEvent)post_addr)(event, identifier, refcon)

/*-----------------------------------------------------------------------------------------
	result GetParamLong(which)
			:return which argument as a long value
result		<-:long containing value
which		->:argument number, 0 is first one
*/

typedef long (*TGetParamLong)(short which, xrtnptr);
#define GetParamLong(which)  (*(TGetParamLong)xrtn_addr->theprocs[HGetParamLong])(which, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	result GetParamDouble(which)
			:return which argument as a double value
result		<-:double containing value
which		->:argument number, 0 is first one
*/

typedef double (*TGetParamDouble)(short which, xrtnptr);
#define GetParamDouble(which)  (*(TGetParamDouble)xrtn_addr->theprocs[HGetParamDouble])(which, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	GetParamString(which, string)
			:return which argument as a string
which		->:argument number, 0 is first one
string		<-:string to place result in. Make room for possible 256 characters

*/

typedef void (*TGetParamString)(unsigned short which, unsigned char *, xrtnptr);
#define GetParamString(which, string)  (*(TGetParamString)xrtn_addr->theprocs[HGetParamString])(which, string, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	result GetParamHandle(which)
			:return which argument as a handle
result		<-:handle containing value
which		->:argument number, 0 is first one
*/

typedef Handle (*TGetParamHandle)(short which, xrtnptr);
#define GetParamHandle(which)  (*(TGetParamHandle)xrtn_addr->theprocs[HGetParamHandle])(which, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	result GetParamLength(which)
			:return length of argument as character count
result		<-:long containing value
which		->:argument number, 0 is first one
*/

typedef long (*TGetParamLength)(short which, xrtnptr);
#define GetParamLength(which)  (*(TGetParamLength)xrtn_addr->theprocs[HGetParamLength])(which, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	result AskSC(prompt, defaultstr, enterdata)
			:use the "ask" dialog
result		<-:button hit by user
prompt		->:prompt string
defaultstr	->:string placed into edit field
enterdata	->:data typed by user returned to you
*/

typedef short (*TAskSC)(unsigned char * prompt, unsigned char * defaultstr, unsigned char * enterdata);
#define AskSC(prompt, defaultstr, enterdata)  (*(TAskSC)xrtn_addr->theprocs[HAskSC])(prompt, defaultstr, enterdata)

/*-----------------------------------------------------------------------------------------
	result AnswerSC(prompt, p1, p2, p3)
			:use the "ask" dialog
result		<-:button hit by user
prompt		->:prompt string
p1-p3		->:strings assigned to buttons of dialog
*/

typedef short (*TAnswerSC)(unsigned char *prompt, unsigned char *p1, unsigned char *p2, unsigned char *p3);
#define AnswerSC(prompt, p1, p2, p3)  (*(TAnswerSC)xrtn_addr->theprocs[HAnswerSC])(prompt, p1, p2, p3)

/*-----------------------------------------------------------------------------------------
	GetFrontMostWindInfo(rec, palette)
			:get rect of top window
rec			<-:info of top window, see inforec structure
palette		->:false is dont look at palettes
*/

typedef void (*TGetFrontMostWindInfo)(InfoRec *, Boolean);
#define GetFrontMostWindInfo(rect, palette)  (*(TGetFrontMostWindInfo)xrtn_addr->theprocs[HGetFrontMostWindInfo])(rect, palette)

/*-----------------------------------------------------------------------------------------
	SetWinPosition(window, position)
			:set window position in list
window		->:window pointer of window to move
position	->:0 is frontmost, positive is bring closer, negative is move away
*/

typedef void (*TSetWinPosition)(WindowPtr, short);
#define SetWinPosition(window, position)  (*(TSetWinPosition)xrtn_addr->theprocs[HSetWinPosition])(window, position)

/*-----------------------------------------------------------------------------------------
	GetWinPosition(window, position, layer)
			:set window position in list
window		->:window pointer of window of interest
position	<-:0 is frontmost, positive is farther away
layer		<-:true is palette
*/

typedef void (*TGetWinPosition)(WindowPtr, short *, short *);
#define GetWinPosition(window, position, layer)  (*(TGetWinPosition)xrtn_addr->theprocs[HGetWinPosition])(window, position, layer)

/*-----------------------------------------------------------------------------------------
	ShowHidePalettes(what)
			:hide or show XRTN palettes
what		->:true = show palettes
*/

typedef void (*TShowHidePalettes)(short);
#define ShowHidePalettes(what)  (*(TShowHidePalettes)xrtn_addr->theprocs[HShowHidePalettes])(what)

/*-----------------------------------------------------------------------------------------
	ShowHideSCPalettes(what)
			:hide or show SuperCard palettes
 what		->:true = show palettes
 */

typedef void (*TShowHideSCPalettes)(short);
#define ShowHideSCPalettes(what)  (*(TShowHideSCPalettes)xrtn_addr->theprocs[HShowHideSCPalettes])(what)

/*-----------------------------------------------------------------------------------------
	WindowPtr	GetWindowPtr(windname)
			:retrieve window pointer of xrtn window
 windname	->:name of window to find
 */

typedef WindowPtr (*TGetWindowPtr)(unsigned char *);
#define GetWindowPtr(windname)  (*(TGetWindowPtr)xrtn_addr->theprocs[HGetWindowPtr])(windname)

/*-----------------------------------------------------------------------------------------
	WindowPtr	GetSCWindowPtr(windname)
			:retrieve window pointer of SuperCard window
 windname	->:name of window to find
 */

typedef WindowPtr (*TGetSCWindowPtr)(unsigned char *);
#define GetSCWindowPtr(windname)  (*(TGetSCWindowPtr)xrtn_addr->theprocs[HGetSCWindowPtr])(windname)

/*-----------------------------------------------------------------------------------------
 result GetSCWindowID(window, descriptor)
 :get a read on a specified SC object
 result		<-:scripterror code, 0 is ok
 window		->:WidnowRef to get descriptor for
 descriptor		<-:Handle * to receive descriptor
 */

typedef short (*TGetSCWindowID)(WindowRef, Handle *, xrtnptr);
#define GetSCWindowID(window, descriptor)  (*(TGetSCWindowID)xrtn_addr->theprocs[HGetSCWindowID])(window, descriptor, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	result SendMessage(message, destination)
	:send a message to the destination
	result		<-:scripterror code, 0 is ok
	message		->:text message
	destination	->:target to send to, 0 is current card
	*/

typedef short (*TSendMessage)(unsigned char *, unsigned char *, xrtnptr);
#define SendMessage(message, destination)  (*(TSendMessage)xrtn_addr->theprocs[HSendMessage])(message, destination, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	result SendMessageLong(message, destination)
	:send a message to the destination
	result		<-:scripterror code, 0 is ok
	message		->:text message
	destination	->:target to send to, 0 is current card
	*/

#if __SUPPORTS_LONG_FILENAMES__
typedef short (*TSendMessageLong)(Handle, Handle, xrtnptr);
#define SendMessageLong(message, destination)  (*(TSendMessageLong)xrtn_addr->theprocs[HSendMessageLong])(message, destination, xrtn_addr)
#endif __SUPPORTS_LONG_FILENAMES__

/*-----------------------------------------------------------------------------------------
	result HasMemory(amount)
			:request amount of memory to be gotten from heap, dont allocate it
result		<-:true has enough
amount		->:requested amount
*/

typedef Boolean (*THasMemory)(long);
#define HasMemory(amount)  (*(THasMemory)xrtn_addr->theprocs[HHasMemory])(amount)

/*-----------------------------------------------------------------------------------------
		 FormatString(output, control, ar1, ar2, ar3, ar4, ar5, ar6)
			:build a text string similar to sprintf
output		<-:resulting Pascal string
control		->:control string using same format as sprintf
ar1 - ar6	->:variable inputs 
*/

typedef void (*TFormatString)(unsigned char *output, unsigned char *control, long ar1, long ar2, long ar3, long ar4, long ar5, long ar6);
#define FormatString(output, control, ar1, ar2, ar3, ar4, ar5, ar6)  (*(TFormatString)xrtn_addr->theprocs[HFormatString])(output, control, ar1, ar2, ar3, ar4, ar5, ar6)

/*-----------------------------------------------------------------------------------------
	result	DecodeString(search, list)
			:find search string within input list and return index of it
result		<-:index of match, -1 if not found
search		->:Pascal search word to match on
list		->:Pascal list of words, return delimited 
*/

typedef short (*TDecodeString)(unsigned char *search, unsigned char *list);
#define DecodeString(search, list)  (*(TDecodeString)xrtn_addr->theprocs[HDecodeString])(search, list)

/*-----------------------------------------------------------------------------------------
	result	DecodeParam(search, list)
			:find search string within input list and return index of it
result		<-:index of match, -1 if not found
search		->:script argument to match on
list		->:Pascal list of words, return delimited 
*/

typedef short (*TDecodeParam)(short search, unsigned char *list, xrtnptr);
#define DecodeParam(search, list)  (*(TDecodeParam)xrtn_addr->theprocs[HDecodeParam])(search, list, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	result EvalExpHandle(message, destination)
			:evaluate an expression into a handle
result		<-:scripterror code, 0 is ok
message		->:text string to evaluate
destination	<-:address of handle, SuperCard will create the new handle
*/

typedef short (*TEvalExpHandle)(unsigned char *, Handle *, xrtnptr);
#define EvalExpHandle(message, destination)  (*(TEvalExpHandle)xrtn_addr->theprocs[HEvalExpHandle])(message, destination, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	result EvalExpString(message, destination)
			:evaluate an expression into a string
result		<-:scripterror code, 0 is ok
message		->:text string to evaluate
destination	<-:string to place result in. Make room for possible 256 characters
*/

typedef short (*TEvalExpString)(unsigned char *, unsigned char *, xrtnptr);
#define EvalExpString(message, destination)  (*(TEvalExpString)xrtn_addr->theprocs[HEvalExpString])(message, destination, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	result EvalExpLong(message, destination)
			:evaluate an expression into a long
result		<-:scripterror code, 0 is ok
message		->:text string to evaluate
destination	<-:address of long to place result in
*/

typedef short (*TEvalExpLong)(unsigned char *, long *, xrtnptr);
#define EvalExpLong(message, destination)  (*(TEvalExpLong)xrtn_addr->theprocs[HEvalExpLong])(message, destination, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	result EvalExpDouble(message, destination)
			:evaluate an expression into a double
result		<-:scripterror code, 0 is ok
message		->:text string to evaluate
destination	<-:address of double to place result in
*/

typedef short (*TEvalExpDouble)(unsigned char *, double *, xrtnptr);
#define EvalExpDouble(message, destination)  (*(TEvalExpDouble)xrtn_addr->theprocs[HEvalExpDouble])(message, destination, xrtn_addr)

#if __SUPPORTS_LONG_FILENAMES__
/*-----------------------------------------------------------------------------------------
	result EvalLongExpHandle(message, destination)
	:evaluate an expression into a handle
	result		<-:scripterror code, 0 is ok
	message		->:text string to evaluate
	destination	<-:address of handle, SuperCard will create the new handle
	*/

typedef short (*TEvalLongExpHandle)(Handle, Handle *, xrtnptr);
#define EvalLongExpHandle(message, destination)  (*(TEvalLongExpHandle)xrtn_addr->theprocs[HEvalLongExpHandle])(message, destination, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	result EvalLongExpString(message, destination)
	:evaluate an expression into a string
	result		<-:scripterror code, 0 is ok
	message		->:text string to evaluate
	destination	<-:string to place result in. Make room for possible 256 characters
	*/

typedef short (*TEvalLongExpString)(Handle, unsigned char *, xrtnptr);
#define EvalLongExpString(message, destination)  (*(TEvalLongExpString)xrtn_addr->theprocs[HEvalLongExpString])(message, destination, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	result EvalLongExpLong(message, destination)
	:evaluate an expression into a long
	result		<-:scripterror code, 0 is ok
	message		->:text string to evaluate
	destination	<-:address of long to place result in
	*/

typedef short (*TEvalLongExpLong)(Handle, long *, xrtnptr);
#define EvalLongExpLong(message, destination)  (*(TEvalLongExpLong)xrtn_addr->theprocs[HEvalLongExpLong])(message, destination, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	result EvalLongExpDouble(message, destination)
	:evaluate an expression into a double
	result		<-:scripterror code, 0 is ok
	message		->:text string to evaluate
	destination	<-:address of double to place result in
	*/

typedef short (*TEvalLongExpDouble)(Handle, double *, xrtnptr);
#define EvalLongExpDouble(message, destination)  (*(TEvalLongExpDouble)xrtn_addr->theprocs[HEvalLongExpDouble])(message, destination, xrtn_addr)

#endif __SUPPORTS_LONG_FILENAMES__

/*-----------------------------------------------------------------------------------------
	result GetGlobalHandle(message, destination)
			:evaluate a global into a handle
result		<-:scripterror code, 0 is ok
message		->:name of global to evaluate
destination	<-:address of handle, SuperCard will create the new handle
*/

typedef short (*TGetGlobalHandle)(unsigned char *, Handle *);
#define GetGlobalHandle(message, destination)  (*(TGetGlobalHandle)xrtn_addr->theprocs[HGetGlobalHandle])(message, destination)

/*-----------------------------------------------------------------------------------------
	result GetGlobalString(message, destination)
			:evaluate a global into a string
result		<-:scripterror code, 0 is ok
message		->:name of global to evaluate
destination	<-:string to place result in. Make room for possible 256 characters
*/

typedef short (*TGetGlobalString)(unsigned char *, unsigned char *);
#define GetGlobalString(message, destination)  (*(TGetGlobalString)xrtn_addr->theprocs[HGetGlobalString])(message, destination)

/*-----------------------------------------------------------------------------------------
	result GetGlobalDouble(message, destination)
			:evaluate an global into a double
result		<-:scripterror code, 0 is ok
message		->:name of global to evaluate
destination	<-:address of double to put result in
*/

typedef short (*TGetGlobalDouble)(unsigned char *, double *);
#define GetGlobalDouble(message, destination)  (*(TGetGlobalDouble)xrtn_addr->theprocs[HGetGlobalDouble])(message, destination)

/*-----------------------------------------------------------------------------------------
	result GetGlobalLong(message, destination)
			:evaluate an global into a long
result		<-:scripterror code, 0 is ok
message		->:name of global to evaluate
destination	<-:address of long to put result in
*/

typedef short (*TGetGlobalLong)(unsigned char *, long *);
#define GetGlobalLong(message, destination)  (*(TGetGlobalLong)xrtn_addr->theprocs[HGetGlobalLong])(message, destination)


/*-----------------------------------------------------------------------------------------
	result SetGlobalHandle(message, source)
			:set a global from a handle
result		<-:scripterror code, 0 is ok
message		->:name of global to change
source		->:handle containing new value
*/

typedef short (*TSetGlobalHandle)(unsigned char *, Handle);
#define SetGlobalHandle(message, source)  (*(TSetGlobalHandle)xrtn_addr->theprocs[HSetGlobalHandle])(message, source)

/*-----------------------------------------------------------------------------------------
	result SetGlobalString(message, source)
			:set a global from a string
result		<-:scripterror code, 0 is ok
message		->:name of global to change
source		->:string containing new value
*/

typedef short (*TSetGlobalString)(unsigned char *, unsigned char *);
#define SetGlobalString(message, source)  (*(TSetGlobalString)xrtn_addr->theprocs[HSetGlobalString])(message, source)

/*-----------------------------------------------------------------------------------------
	result SetGlobalDouble(message, source)
			:set a global from a double
result		<-:scripterror code, 0 is ok
message		->:name of global to change
source		->:double containing new value
*/

typedef short (*TSetGlobalDouble)(unsigned char *, double);
#define SetGlobalDouble(message, source)  (*(TSetGlobalDouble)xrtn_addr->theprocs[HSetGlobalDouble])(message, source)

/*-----------------------------------------------------------------------------------------
	result SetGlobalLong(message, source)
			:set a global from a long
result		<-:scripterror code, 0 is ok
message		->:name of global to change
source		->:long containing new value
*/

typedef short (*TSetGlobalLong)(unsigned char *, long);
#define SetGlobalLong(message, source)  (*(TSetGlobalLong)xrtn_addr->theprocs[HSetGlobalLong])(message, source)


/*-----------------------------------------------------------------------------------------
	result GetFieldHandle(message, destination)
			:evaluate a field into a handle
result		<-:scripterror code, 0 is ok
message		->:name of field
destination	<-:address of handle, SuperCard will create the new handle
*/

typedef short (*TGetFieldHandle)(unsigned char *, Handle *, xrtnptr);
#define GetFieldHandle(message, destination)  (*(TGetFieldHandle)xrtn_addr->theprocs[HGetFieldHandle])(message, destination, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	result GetFieldString(message, destination)
			:evaluate a field into a string
result		<-:scripterror code, 0 is ok
message		->:name of field
destination	<-:string to place result in. Make room for possible 256 characters
*/

typedef short (*TGetFieldString)(unsigned char *, unsigned char *, xrtnptr);
#define GetFieldString(message, destination)  (*(TGetFieldString)xrtn_addr->theprocs[HGetFieldString])(message, destination, xrtn_addr)


/*-----------------------------------------------------------------------------------------
	result SetFieldHandle(message, source)
			:set a field from a handle
result		<-:scripterror code, 0 is ok
message		->:name of field to change
source		->:handle containing new value
*/

typedef short (*TSetFieldHandle)(unsigned char *, Handle, xrtnptr);
#define SetFieldHandle(message, source)  (*(TSetFieldHandle)xrtn_addr->theprocs[HSetFieldHandle])(message, source, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	result SetFieldString(message, source)
			:set a field from a string
result		<-:scripterror code, 0 is ok
message		->:name of field to change
source		->:string containing new value
*/

typedef short (*TSetFieldString)(unsigned char *, unsigned char *, xrtnptr);
#define SetFieldString(message, source)  (*(TSetFieldString)xrtn_addr->theprocs[HSetFieldString])(message, source, xrtn_addr)


// ** MDL 12/6/98 **

/*-----------------------------------------------------------------------------------------
	result GetFieldTEHandle(message, destination)
			:evaluate a field into a TEHandle
result		<-:scripterror code, 0 is ok
message		->:name of field
destination	<-:address of TEHandle, SuperCard will create the new TEHandle
*/

typedef short (*TGetFieldTEHandle)(unsigned char *, TEHandle *, xrtnptr);
#define GetFieldTEHandle(message, destination)  (*(TGetFieldTEHandle)xrtn_addr->theprocs[HGetFieldTEHandle])(message, destination, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	result SetFieldTEHandle(message, source)
			:set a field from a TEHandle
result		<-:scripterror code, 0 is ok
message		->:name of field to change
source		->:TEHandle containing new text
*/

typedef short (*TSetFieldTEHandle)(unsigned char *, TEHandle, xrtnptr);
#define SetFieldTEHandle(message, source)  (*(TSetFieldTEHandle)xrtn_addr->theprocs[HSetFieldTEHandle])(message, source, xrtn_addr)

#if __SUPPORTS_LONG_FILENAMES__
/*-----------------------------------------------------------------------------------------
	result GetFieldHandleLong(message, destination)
	:evaluate a field into a handle
	result		<-:scripterror code, 0 is ok
	message		->:name of field
	destination	<-:address of handle, SuperCard will create the new handle
	*/

typedef short (*TGetFieldHandleLong)(Handle, Handle *, xrtnptr);
#define GetFieldHandleLong(message, destination)  (*(TGetFieldHandleLong)xrtn_addr->theprocs[HGetFieldHandleLong])(message, destination, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	result GetFieldStringLong(message, destination)
	:evaluate a field into a string
	result		<-:scripterror code, 0 is ok
	message		->:name of field
	destination	<-:string to place result in. Make room for possible 256 characters
	*/

typedef short (*TGetFieldStringLong)(Handle, unsigned char *, xrtnptr);
#define GetFieldStringLong(message, destination)  (*(TGetFieldStringLong)xrtn_addr->theprocs[HGetFieldStringLong])(message, destination, xrtn_addr)


/*-----------------------------------------------------------------------------------------
	result SetFieldHandleLong(message, source)
	:set a field from a handle
	result		<-:scripterror code, 0 is ok
	message		->:name of field to change
	source		->:handle containing new value
	*/

typedef short (*TSetFieldHandleLong)(Handle, Handle, xrtnptr);
#define SetFieldHandleLong(message, source)  (*(TSetFieldHandleLong)xrtn_addr->theprocs[HSetFieldHandleLong])(message, source, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	result SetFieldStringLong(message, source)
	:set a field from a string
	result		<-:scripterror code, 0 is ok
	message		->:name of field to change
	source		->:string containing new value
	*/

typedef short (*TSetFieldStringLong)(Handle, unsigned char *, xrtnptr);
#define SetFieldStringLong(message, source)  (*(TSetFieldStringLong)xrtn_addr->theprocs[HSetFieldStringLong])(message, source, xrtn_addr)


// ** MDL 12/6/98 **

/*-----------------------------------------------------------------------------------------
	result GetFieldTEHandleLong(message, destination)
	:evaluate a field into a TEHandle
	result		<-:scripterror code, 0 is ok
	message		->:name of field
	destination	<-:address of TEHandle, SuperCard will create the new TEHandle
	*/

typedef short (*TGetFieldTEHandleLong)(Handle, TEHandle *, xrtnptr);
#define GetFieldTEHandleLong(message, destination)  (*(TGetFieldTEHandleLong)xrtn_addr->theprocs[HGetFieldTEHandleLong])(message, destination, xrtn_addr)

/*-----------------------------------------------------------------------------------------
	result SetFieldTEHandleLong(message, source)
	:set a field from a TEHandle
	result		<-:scripterror code, 0 is ok
	message		->:name of field to change
	source		->:TEHandle containing new text
	*/

typedef short (*TSetFieldTEHandleLong)(Handle, TEHandle, xrtnptr);
#define SetFieldTEHandleLong(message, source)  (*(TSetFieldTEHandleLong)xrtn_addr->theprocs[HSetFieldTEHandleLong])(message, source, xrtn_addr)
#endif __SUPPORTS_LONG_FILENAMES__

/*-----------------------------------------------------------------------------------------
	result GetCurTEHandle(destination)
			:Get the TEHandle for the currently open field (if any)
result		<-:scripterror code, 0 is ok
destination	<-:address of TEHandle, SuperCard owns the TEHandle
*/

typedef short (*TGetCurTEHandle)(TEHandle *, xrtnptr);
#define GetCurTEHandle(destination)  (*(TGetCurTEHandle)xrtn_addr->theprocs[HGetCurTEHandle])(destination, xrtn_addr)


/*-----------------------------------------------------------------------------------------
	result TouchCurTEHandle()
			:Tell SC you have changed the contents of the CurTEHandle
result		<-:scripterror code, 0 is ok
*/

typedef short (*TTouchCurTEHandle)(xrtnptr);
#define TouchCurTEHandle()  (*(TTouchCurTEHandle)xrtn_addr->theprocs[HTouchCurTEHandle])(xrtn_addr)


/*-----------------------------------------------------------------------------------------
	result GetRead(message, source)
			:get a read on a specified SC object
result		<-:scripterror code, 0 is ok
message		->:name of object to get read on
source		<-:readptr to receive read of object
*/

typedef short (*TGetRead)(unsigned char *, void *, xrtnptr);
#define GetRead(message, destination)  (*(TGetRead)xrtn_addr->theprocs[HGetRead])(message, destination, xrtn_addr)


#if __SUPPORTS_LONG_FILENAMES__
/*-----------------------------------------------------------------------------------------
	result GetReadLong(message, source)
			:get a read on a specified SC object
result		<-:scripterror code, 0 is ok
message		->:name of object to get read on
source		<-:readptr to receive read of object
*/

typedef short (*TGetReadLong)(Handle, void *, xrtnptr);
#define GetReadLong(message, destination)  (*(TGetReadLong)xrtn_addr->theprocs[HGetReadLong])(message, destination, xrtn_addr)

#endif __SUPPORTS_LONG_FILENAMES__


/*-----------------------------------------------------------------------------------------
	result PutRead(source)
			:write back a read to a SuperCard object
result		<-:scripterror code, 0 is ok
source		->:readptr to outstanding read
*/

typedef short (*TPutRead)(void *, xrtnptr);
#define PutRead(source)  (*(TPutRead)xrtn_addr->theprocs[HPutRead])(source, xrtn_addr)


/*-----------------------------------------------------------------------------------------
	GetGAddr(request, reply, procs, vars)
			:get the addresses of the SC mainglobs block, the SuperTalk global vars block, 
				and the XCMD internal routine callback procs table
request		->:request code (versrequest or versgetgaddr)
reply		<-:version code (if versrequest) or mainglobals * (if versgetgaddr)
procs		<-:table of global procs (if versgetgaddr)
vars		<-:handle to global variables (if versgetgaddr)
*/

typedef void (*TGetGAddr)(long, long *, long *, long *, xrtnptr);
#define GetGAddr(request, reply, procs, vars)  (*(TGetGAddr)xrtn_addr->theprocs[HGetGAddr])(request, reply, procs, vars, xrtn_addr)

#pragma options align = reset

// **
#endif		// ndef __xrtnRT__
