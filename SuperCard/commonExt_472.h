//	SuperCard 4.72 commonExt.h file
//	Typedefs and other definitions for IT routines
//	Copyright 2011 Mark Lucas
//	All rights reserved worldwide.

#ifndef __commonEXT472
#define __commonEXT472
//This file contains those structures that are common to the product and XCmd routines

// Dummy declarations of internal structures

#include "SuperWASTE_472.h"
#include "THPrint.h"
#include "QuickTimeMusic.h"

typedef Handle moovhand, picthand;
typedef struct {
	long xx[2];
}urlque, actionque;

#define vers30 30
#define vers35 35
#define vers36 36
#define vers361 361
#define vers40 40
#define vers45 45
#define vers46 46
#define vers462 462
#define vers463 463
#define vers464 464
#define vers47 47

#pragma options align=power

typedef struct {
	FSVolumeRefNum vRefNum;
	short islocked;
	Str255 name;
} volqueitem;

typedef struct eventqueitem {
	EventRecord event;
	struct eventqueitem *nextevent;
} eventqueitem, *eventptr;

#pragma options align=mac68k

#ifndef __convertproj__
#ifndef __commonprivate__

typedef Ptr pathptr, moleptr, prefptr, readptr, spotptr;
typedef Handle pathand, varshand, spothand, backhand, hierhand, headhand, brushand, levlhand, deskhand, itemhand, menuhand, linehand;
typedef Handle sayshand, filmhand, soundhand, libhand, windhand, cardhand, prefhand;

//#ifndef __idlerhand
//#define __idlerhand
//typedef Handle idlerhand;
//#endif	// ndef __idlerhand

#ifndef __idlerhand
#define __idlerhand
typedef struct {
	ControlHandle		control;
	UInt32				flags;
	Rect				savebounds;
	short				savevis;
	short				objectype;
} idleitem, *idelitemptr, **idleitemhand;

typedef struct {
	WindowRef			window;
	idleitemhand		busycontrols;
} idler, *idlerptr, **idlerhand;
#endif //ndef __idlerhand

typedef struct {
	Ptr a;
	Handle b;
	Handle c;
	long d;
	long e;
	long f;
	Handle g;
	long h;
	long i;
	long j;	
	Handle k;
	Handle l;
	CTabHandle m;
	long n;
	long o;
	Handle p;
	Handle q;
	CTabHandle r;
	WindowRef s;
	ControlHandle t;
	ControlHandle u;
	long v;
	long w;
	short x;
	short y;
	Ptr z;
	short aa;
	short ab;
	short ac;
} desk;

typedef struct {
	void *a;
	void *b;
	long c;
	long d;
	long e;
	void *f;
	void *g;
	void *h;
	long i;
	short j;
	short k;
} line;

typedef struct {
	linehand menuset;
	short numlines;
} menublock;

#endif 	// ndef __commonprivate__
#endif	// ndef __convertproj__

typedef struct {
	short	vRefNum;
	long	dirID;
	long	cnt;
} dirqitem, *dirqptr, **dirqhand;

struct myGrafPort {
  short               device;                 /* not available in Carbon*/
  BitMap              portBits;               /* in Carbon use GetPortBitMapForCopyBits or IsPortColor*/
  Rect                portRect;               /* in Carbon use Get/SetPortBounds*/
  RgnHandle           visRgn;                 /* in Carbon use Get/SetPortVisibleRegion*/
  RgnHandle           clipRgn;                /* in Carbon use Get/SetPortClipRegion*/
  Pattern             bkPat;                  /* not available in Carbon all GrafPorts are CGrafPorts*/
  Pattern             fillPat;                /* not available in Carbon all GrafPorts are CGrafPorts*/
  Point               pnLoc;                  /* in Carbon use GetPortPenLocation or MoveTo*/
  Point               pnSize;                 /* in Carbon use Get/SetPortPenSize*/
  short               pnMode;                 /* in Carbon use Get/SetPortPenMode*/
  Pattern             pnPat;                  /* not available in Carbon all GrafPorts are CGrafPorts*/
  short               pnVis;                  /* in Carbon use GetPortPenVisibility or Show/HidePen*/
  short               txFont;                 /* in Carbon use GetPortTextFont or TextFont*/
  StyleField          txFace;                 /* in Carbon use GetPortTextFace or TextFace*/
                                              /* StyleField occupies 16-bits, but only first 8-bits are used*/
  short               txMode;                 /* in Carbon use GetPortTextMode or TextMode*/
  short               txSize;                 /* in Carbon use GetPortTextSize or TextSize*/
  Fixed               spExtra;                /* in Carbon use GetPortSpExtra or SpaceExtra*/
  long                fgColor;                /* not available in Carbon */
  long                bkColor;                /* not available in Carbon*/
  short               colrBit;                /* not available in Carbon*/
  short               patStretch;             /* not available in Carbon*/
  Handle              picSave;                /* in Carbon use IsPortPictureBeingDefined*/
  Handle              rgnSave;                /* not available in Carbon*/
  Handle              polySave;               /* not available in Carbon*/
  QDProcsPtr          grafProcs;              /* not available in Carbon all GrafPorts are CGrafPorts*/
};
typedef struct myGrafPort                 myGrafPort;
typedef myGrafPort *                      myGrafPtr;

/*		The table contains a list of key words and tokens						*/	

typedef struct {
	unsigned char *text;
	short token;
} table;


#ifndef __idlerhand
#define __idlerhand
typedef struct {
	ControlHandle		control;
	UInt32				flags;
	Rect				savebounds;
	short				savevis;
	short				objectype;
} idleitem, *idleitemptr, **idleitemhand;

typedef struct {
	WindowRef			window;
	idleitemhand		busycontrols;
} idler, *idlerptr, **idlerhand;
#endif //ndef __idlerhand

// This is the structure of the elements in our queue of open scripting component connections
typedef struct {
	OSAID		id;
	Str63		name;
} scriptqitem, *scriptqptr, **scriptqhand;

typedef struct {
	ComponentInstance	theComponent;
	scriptqhand			theScripts;
	Str63				theComponentName;
} compqitem, *compqptr, **compqhand;

//typedef struct {
//	OSType 		tag;
//	UInt32 		id;
//	OSType 		type;
//	Handle		data;
//	Handle		name;
//	Handle		script;
//	Handle		altdata;
//	Handle	 	properties;
//} iota, *iotaptr, **iotahand;


#define maskmode -1

#include <palettes.h>

#define maxstring 256
#define maxtext maxstring - 1

#define menudull 1
#define itemdull 1
#define itemline 2
#define itemcheck 4
#define itembold 8
#define itemitalic 16
#define itemunderline 32
#define itemoutline 64
#define itemshadow 128
#define itemshiftkey 256
#define itemoptionkey 512
#define itemcontrolkey 1024

#define shortstring 32
#define shortext (shortstring - 1)
typedef unsigned char fredstr[shortstring];

#pragma options align=mac68k

/*			main vars		*/

typedef struct {

	short				barvis;				// keep this one at top of list for xcmds
	short				goback;
	short				currentmenuset; 	// used to be offrow, unused in 3.0
	short				startup;
	short				oldepth;
	short				applref;
	short				homeref;
	short				barstate;
	short				appcolor;
	short				numhiers;
	short				numdesks;
	short				plugin;				
	short				oldcount;
	long				creator;
	short				hidewindow;
	short				barheight;
	short				therepeat;
	short				themole;
	Rect				dragrect;
	Rect				growrect;
	long				filler;
	short				switchedout;
	pathptr				linkptr;
	pathptr				homeptr;
	hierhand			hierque;
	deskhand			deskque;
	long				spare;
	THPrint				printrec;
	headhand			homehead;
	Handle				fakescript;
	MenuRef 			deskmenu;
	EventRecord			myevent;
	SysEnvRec			myenviron;
	brushand			globrushes;
	pathand				globpatterns;
	CTabHandle			globcolors;
	short				sysvol, applvol, prefvol;
	myGrafPort			oldsrcport, oldselport, oldmskport;
	PaletteHandle		workpalette, defpalette;

	/*			talk vars				*/

	short				allowpalettes;
	short				allowdebug;
	short				trapflags;
	short				grid;
	short				pbrush;
	short				penpat;
	short				fillpat;
	short				penfore;
	short				penback;
	short				showpen;
	short				showfill;
	short				fillfore;
	short				fillback;
	short				multiple;
	short				centered;
	short				penwidth;
	short				penheight;
	short				polysides;
	short				multispace;

	short				powerkeys;
	short				userlevel;
	short				dragspeed;
	short				editmenus;
	short				lockmenus;
	short				textarrows;
	short				lockrecent;
	short				lockcursor;
	long				nextime;
	long				idleticks;
	short				remapcolor;
	short				createpaint;
	short				blindtyping;
	short				editscripts;
	short				lockmessages;
	short				allowinterrupts;
	short				allowkeyinfield;
	short				allowfieldredraw;
	levlhand			levels;
	short				numlevels;

	short				textsize;
	short				textfont;
	short				textalign;
	short				textstyle;
	short				textheight;


	long 				unique;
	short 				bailcard;			/*	card data changed, bail pending messages	*/
	short 				bailspot;			/*	spot data changed, bail pending messages	*/
	short 				unquoted;
	short 				erroroff;
	short 				toplevel;
	short 				itemdel;
	short 				worddel;
	short 				linedel;
	short 				blocklevel;
	desk 				currdesk;
	short 				usermodify;
	Point 				clickloc;
	Handle 				errorobj;
	varshand 			globvars;
	Handle 				theformat;
	Handle 				filetype;
	Handle 				foundline, foundtext, foundchunk, foundfield;
	Handle 				thetarget, theresult, pushstack, backstack, forthstack;
	Rect 				findrect;

	WindowRef 			myfindwindow;
	short 				mousoff;
	spothand 			moushand;
	WindowRef 			mouswind;
	short 				bmaplock;
	short 				pastecode;
	long 				sourcesize;
	Point 				textpoint;
	Pattern 			lastglide;
	short 				newselect, sourcecolor;
	Rect 				selectrect, sourcerect;
	myGrafPort 			oldwrkport;
	Handle 				sourcebits, selectbits, maskbits, workbits;
	TEHandle 			textbits;

	short 				printinit;
	short 				ver10;
	moleptr 			moleblock;
	short 				quotebreak;
	short 				willprint;

	short 				graphoff;
	WEHandle 			graphteh;
	spothand			graphand;
	WindowRef 			graphwind;
	short 				interrupt;
	WindowRef 			stagewindow;
	short 				allowmodal;
	short 				dohistory;
	short 				allowtooltips;
	Handle 				messagetext;
	short 				allowemptypaint;
	short				allowdoubleclick;

	long 				serialcontrol;

	/*			message vars				*/

	short 				lastreturn;
	TEHandle 			mesrecord;
	WindowRef 			meswind;
	unsigned char 		mestring[maxstring];

	/*			script vars					*/

	short 				scrivalid;
	Handle 				scriundo;

	/*			edit vars					*/

	short 				fieldel;
	short 				fieldoff;
	long 				fieldid;
	short 				fieldlock;
	pathptr 			fieldpath;
	WEHandle 			fieldteh;
	spothand 			fieldhand;
	WindowRef 			fieldwind;
	CTabHandle 			fieldclut;
	short 				lasson;
	short 				texton;
	short 				bmapdel;
	short 				bmapoff;
	long 				bmapid;
	short 				selecton;
	pathptr 			bmapath;
	spothand 			bmaphand;
	WindowRef 			bmapwind;
	CTabHandle 			bmapclut;
	short 				cardon;
	spothand 			spotclip;
	CTabHandle 			spotclut;
	short 				ver15;

	/* 1.6 global additions */

	Pattern 			newgray;
	short 				soundvolume;
	short 				helpballoons;
	short 				lockerrordialogs;
	Handle 				foundwindow;
	short 				tracedisabled;
	short 				ver16;

	/* 1.7 global additions */

	short 				quicktimeinit;
	moovhand 			moovque;
	short 				numoovs;
	short 				theswitch;
	short 				movieidle;
	Handle 				globhand;
	short 				hastextospeech;
	sayshand 			saysque;
	short 				numsays;
	filmhand 			filmque;
	soundhand 			soundque;
	Rect 				limitbounds;
	Handle 				clickline, clicktext, clickchunk;
	short 				showgroups;
	short 				explicitvars;
	short 				internationalcompare;
	short 				hasplayfile;
	short 				ver17;

	/* 2.5 global additions */
	prefhand			prefdata;
	NumVersion 			soundversion;
	short				bufferDepth;
	short 				multiEffect;
	picthand 			pictque;
	short 				ver25;	

	/* 3.0 global additions */

	urlque 				urlist; 			// URL support
	actionque 			actionlist; 		// Jetstream
	long 				urlstreamsize; 		// Jetstream
	long 				urlstreamrate; 		// Jetstream
	short 				urlstreammode; 		// Jetstream
	long 				urltimeout; 		// Jetstream
	Ptr 				currinstance; 		// Jetstream
	Ptr 				activeinstance;		// Jetstream
	short 				inscript;			// CyberDog Thread Sync
	short 				pouchvol;
	short 				ver30;

	/* 3.5 global additions */

	short				allowdragndrop;			// Is Drag and Drop enabled?
	short				allowmousewithin;		// Is mouseWithin enabled?
	short				allowmousemessages;		// Are mouse tracking messages enabled?
	short				allowqtvrmessages;		// Are QTVR event intercepts enabled?
	short				modernlook;				// Use Appearance Manager?
	menublock			*menusets;				// Reference to menusets variable in menuRT
	MenuRef 			*fontmenu;				// Pointer to cached font menu in menuRT.c
	short				fontmenublessed;		// Have we set the font menu to WYSIWIG already?
	Handle				dragobject;				// The SC object (if any) from which a drag was initiated
	DragReference		dragreference;			// Drag reference of the current drag (if any)
	short				hasdragmgr;				// Is the Drag Mgr available on this system?
	short				hasappearancemgr;		// Is the Appearance Mgr available on this system?
	compqhand			openscriptcomponents;	// List of script components we have an open connection to
	short				wysiwygfontmenu;		// Show fonts in own face in Font menu under modernLook?
	long				aetimeout;				// How long until Apple Events time out?
	short 				showfocusrects;			// Show focus ring around open field under modernLook?
	short				bailoutofdrag;			// Did this pointer tool drag become a D&D operation?
	short				scrolling;				// Are we currently scrolling a field (so mainglobs.fieldteh is suspect)?
	SRRecognitionSystem recogsys;
	SRRecognizer 		recognizer;
	short				allowrecog;
	short				listening;
	short				hasqtvr;
	short				haspeechrecog;
	short				cdrefnum;
	short				thecatch;
	short				allowdragexport;
	Handle 				jumpblock;				// Handle to resource with address of this block (to give defprocs access)
	short 				ver35;

	/* 3.6 global additions */

	ProcPtr 			*globalprocs;			// Address of XCMD callback procs table
	CursHandle 			defaultcursor;			// Settable default browse cursor
	CursHandle 			currentcursor;			// Settable object-level cursor
	short 				allowobjectcursors;		// Use object-level cursors?
	UniversalProcPtr 	*proctable;				// Address of master procs table
	short 				allowtsm;				// Flag to control use of Text Services Manager
	short 				allowlistenmodes;		// Permits or denies SuperCard speech recog from using system listening modes
	short 				dontlimitwds;			// Permits or denies making windows bigger than their current bkgnd
	short 				allowfavoriteflavors;	// Permits or denies dropping unknown data types/file types
	short 				hastsm;					// Is Text Services Manager present?
	short 				hastsmte;				// Is Text Services Manager present?
	short 				allowinlineinput;		// Switches between inline input and input window
	short 				savedfontforce;			// Found value of script manager smFontForce global, restore when we quit...
	void 				*tsdocumentid;			// Our dummy TSM document, which allows TSM components to work properly when no fld is open
	short 				ver36;

	/* 3.61 global additions */

	long 				bgsleeptime;			// How long we will yield cpu to other processes when we're in bkgnd
	long 				fgsleeptime;			// How long we will yield cpu to other processes when we're in foregnd

	void 				*qd;					// Not applicable under Carbon

	long 				maxcachedhiers;			// Max # of cached scripts
	long 				maxcachedvirs;			// Max # of cached object per virque
	long 				maxcachedpicts;			// Max # of cached PICTs
	short 				ISA;					// Instruction set architecture of SuperCard application
	short 				player;					// Is SuperCard application just the player?
	short 				trial;					// Is SuperCard application just the trial version?
	short 				ver361;

	/* 3.62 global additions */

	short 				donthidepalettes;
	short 				ver362;

	/* 3.63 global additions */

	short 				deferupdates;			// Do we need to defer update handling? (We do from resume messages)
	table 				***hashtable;			// Hash table for tokenization
	Handle 				rbe;
	unsigned long 		rbec;
	MenuRef 			popupmenu;
	short 				ver363;

	/* 4.0 global additions */

	short				carbonx;				// Are we running under Carbon on OS X.x?
	long 				sysdir;
	long 				appldir;
	long 				prefdir;
	long 				pouchdir;
	PMPrintSession		printSession;
	PMPageFormat		pageFormat;
	PMPrintSettings		printSettings;
	dirqhand 			dirque;					// This replaces the working directory queue in SC's search hierarchy
	ScrapRef 			oldscrapref;			// Holds previous ScrapRef value (so we can tell if scrap has changed)
	long 				transtep;
	long 				trandelay;
	long 				scrollbarsize;
	DialogRef 			debugwindow;
	DialogRef 			scriptwindow;
	DialogRef 			upropwindow;
	ControlRef 			trackcontrol;
	spothand 			drawhand;
	short 				drawoff;
	short 				ineffect;
	long 				curstime;
	short 				cursinterval;
	short 				allowtransitions;
	Point 				transitionloc;
	TMTask 				cursortask;
	UInt32 				thebusy;
	short				hashelpmenu;
	short 				needtoresume;
	short				changingwdstyle;
	short				sanewindowlayering;
	short				openbothforks;
	short				autoresize;
	short				drawingroup;
	short				resuming;
	short				flushtwice;
	short				trackabort;
	ProcPtr 			*carbonprocs;
	CGrafPtr 			srcport, selport, mskport, wrkport;
	ProcPtr 			*cmds;
	ProcPtr 			*funcs;
	void				*clientcontext;		// actually an OTClientContextPtr
	short				blockpolytool;
	short				allowautoflavors;
	WindowRef			oldabove;
	WindowGroupRef		mastergroup;
	WindowRef			sndialog;
	Point				draworigin;
	idlerhand			idlers;

	IconRef				genericdocicon;
	UInt16				current_sc_version;
	UInt16				spare2;
	long				unused[2];
	WindowRef			dragtargetwd;
	QDRegionBitsRef		draghilitebits;
	RgnHandle			draghilitergn;
	short				dragmessage;
	short				targetwdhasdesk;
	void				*targetwdesk;
	
	long				progressticks;
	UInt32				iconrefcode;
	UInt32				draftloop;
	PMDestinationType	destinationtype;
	CFStringRef			destinationformat;
	CFURLRef			destinationlocation;
	unsigned long		printflags;
	unsigned char		printjobname[maxstring];
	Handle				printlabel;
	short				updatecursor;
	short				compilingosascript;
	short				runningosascript;
	short				localdelims;
	void 				*qdswaptextflags;
	FSSpec				applspec;
	FSSpec				homespec;
	FSSpec				pouchspec;
	MenuRef				*windowsmenu;
	void				*sigmfp;
	unsigned long		killproperties;
	short				validateuserprops;
	short				reshowfloaters;
	AppleEvent	 		suspendedEvt;
	QHdrPtr				freelist;
	AEDesc 				defaultLocation;
	short				pastestyleinfo;
	short				globscriptsize;
	short				globscriptabsize;
	short				useglobscriptfont;
	short				dirtydrawing;
	Point				origwdsize;
	Point				origbgsize;
	EventLoopTimerRef	idletimer;
	EventHandlerRef		maineventref;
	EventHandlerRef		controltexthandleref;
	short				ineventloop;
	short				exportingcard;
	short 				ver40;

	/* 4.1 global additions */

	Handle				validgraphicfiletypes;
	ProcessSerialNumber	ourPSN;
	short				gotfirstresume;
	short				ignoretranloc;
	short				acceptuserinput;
	
	short				tempvol;
	short				homevol;
	short				desktopvol;
	short				documentsvol;
	short				soundsvol;
	short				picturesvol;
	short				moviesvol;
	long				tempdir;
	long				homedir;
	long				desktopdir;
	long				documentsdir;
	long				soundsdir;
	long				picturesdir;
	long				moviesdir;
	ProcPtr 			*xcarbonprocs;
	UniversalProcPtr 	*xproctable;
	short 				lockupdates;
	short				offscreendepth;
	short				offscreenrowbytes;
	short				offscreenpixmapusecount;
	Rect				offscreenbounds;
	GWorldPtr			offscreengworld;
	PixMapHandle		offscreenpixmap;
	Ptr					offscreenpixbaseaddr;
	short				offscreenlocked;
	short 				ver41;
	
	/* 4.5 global additions */

	PMIdleUPP			printidleUPP;
	MenuRef				dockmenu;
	line				dockmenuline;
	UInt32				context;
	short				unresponsive;
	short				decimalchar;
	NumberParts			partstable;
	DialogRef 			filterwindow;
	long				longquicktimeversion;
	short				quicktimeversion;
	CQDProcs			saveprocs;
	short				drawnorect;
	short				drawnorgn;
	short				hascontextualmenus;
	short				contextclick;
	long 				obsolete_erroroff;
	short 				tabsize;
	short 				disallowcancelkeys;
	
	EventHandlerCallRef nextHandler;			// These three items hold info about the current CarbonEvent (if any)
	EventRef 			theEvent;
	void				*userData;
	
	UInt32				objectnumber;			// These items are used to pass info about clicks on embedded fld objects
	short				objectabort;
	short				objectclick;
	
	long				dialingTime;
	UInt32				closePortTime;
	long				driverRefNum;			// Holds driver refNum under 8 - 9, modem fileDesc under X
	UInt32 				batchprintflags;		// When this is non-zero, that indicates a batch print session is open
	short 				saveprintinit;

	spothand			objectspots;
	short				objectoffset;
	WindowRef			objectwindow;

	Handle				globscriptfont;
	AppleEvent			*appleEvent;
	short 				paletteAlpha;

	long 				bgscriptime;			// How often we will yield cpu to other processes when we're running script in bkgnd
	long 				fgscriptime;			// How often we will yield cpu to other processes when we're running script in foregnd
	
	Document			fieldprintdocument;
	EventRef			myeventref;
	UInt8				heartbeat;
	UInt8				clipisup;
	UInt8				timetodraw;
	UInt8				moviestask;
	RgnHandle			mouseRgn; 
	short				CocoaInited;
	short				xrayvision;
	Handle				spellcheck;
	float				rtfSizeScaleFactor;
	long				spare3[18];
	
	CFStringRef			cfnamekey;
	
	short				fieldscrollstep;
	short				cardscrollstep;
	
	NoteAllocator		myNoteAllocator;
	MusicComponent		tunemusicomponent;
	TunePlayer 			frontuneplayer;
	TunePlayer 			backtuneplayer;
	OSType				tunesynthtype;
	
	short 				stageWindowAlpha;
	short				flushispending;
	short				proportionalscrolling;
	short 				ver45;
	
	short				idlecontrols;

	short 				pasting;
	short				capturingcard;
	readptr				trackread;

	short				processingdrop;
	short				dropaction;

	UInt32				lastclicktime;
	short				qdquartzpicts;
	short				hasaltivec;
	short 				ver45a;
	
	/* 4.51 global additions */

	long							translucentdragthreshold;
	short							translucentdragopacity;
	
	short 							ver451;
	
	/* 4.52 global additions */

	void *							task_info;
	void *							task_self;
	void *							vm_region;
	void *							deallocate_port;
	
	short							dontcheckmem;
	short 							pixDepth;
	short							showhidenavextension;	
	short							autoflush;	
	short 							ver452;
	
	/* 4.6 global additions */

	ProcPtr							*cfmprocs;
	
	int								argc;
	char							**argv;
	short 							allowlaunchargs;
	
	short							donterasewithmetal;
	CQDProcs						metalprocs;
	
#if __USE_CLOCKS__
	WindowRef						currclockwind;
	spothand						currclockhand;
	long							currclockoff;
	ControlPartCode					currclockpart;
#endif __USE_CLOCKS__
	
	Handle							volque;
	eventqueitem *					eventquehead;
	eventqueitem *					eventquetail;
	UInt32							lockcount;
	CFBundleRef						appbundle;
	short							fakeclick;
	
	short 							ver46;
	
	Handle							hardware_profiler_info;
	CFDataRef						hardware_profiler_xml;
	
	//	QDRectUPP						originalrectproc;
	
	short 							allowdeletecardmessages;
	short 							ver462;
	
	short 							printingafield;
	short 							handlevalidationactive;
	short							updateinsertedscripts;
	short							dummy;
	
	void							**switcher;
	void							**track;
	UInt32							stackmax;
	void							*xinfo;
	Handle							ignoredkeys;
	short							dontcliptowd;
	
	short 							ver463;
	
	Handle							deadaway;
	Handle							deadxaway;
	Rect							capturect;
	short							inexternal;
	short 							ver464;
	
	Handle							validgraphicfilextensions;
	short 							ver47;
	
	short							changingback;
	short 							ver471;	
	
	// variable size globals
	char 				overloadhandler[1];
	char 				overloadfunction[1];

} mainglobs, *globptr;



// Index offsets to internal procedures
enum {
	// sprintf original index
	addrsprintf,
	// internal application procedures
	addraddvir,
	addrgetvir,
	addrchangevir,
	addrputvir,
	addrdeletevir,
	addrnamevir,
	addrsavevir,
	addrnomemory,
	addrstupidtextvector,
	addrimagedit,
	addrindent,
	addrdrawspot,
	addrptinspot,
	addrcreatedrawrect,
	addrcreatedrawline,
	addrcreatedrawpoly,
	addrcreatedrawfree,
	addrcreatedrawarc,
	addrcreatebutrect,
	addrcreatebutpoly,
	addrcreatefieldrect,
	addrcreatedrawtext,
	addropenvir,
	addrclosevir,
	addrrevertvir,
	addrtestvir,
	addrsizevir,
	addrclearvir,
	addrislocked,
	addrnodiskspace,
	addrcreatestar,
	addrdeletestar,
	addropenstar,
	addrclosestar,
	addrcompactstar,
	addrflushstar,
	addrtotalstar,
	addrsizestar,
	addrgetstar,
	addrnamestar,
	addrsavestar,
	addraddstar,
	addrdelstar,
	// new internal application procedures for 3.0
	addrdestview,
	addrbackspot,
	addrgetdepth,
	addrpacktext,
	addrdrawread,
	addrreadisfield,
	addrputdownfield,
	addrpictospot,
	addrdumpspot,
	// standard library functions
	addrmalloc,
	addrcalloc,
	addrrealloc,
	addrfree,
	addratof,
	addrstrtod,
	addratoi,
	addratol,
	addrstrtol,
	addrstrtoul,
	addrbsearch,
	addrsscanf,
	addracos,
	addrasin,
	addratan,
	addratan2,
	addrcos,
	addrsin,
	addrtan,
	addrcosh,
	addrsinh,
	addrtanh,
	addrexp,
	addrfrexp,
	addrldexp,
	addrlog,
	addrlog10,
	addrmodf,
	addrpow,
	addrsqrt,
	addrceil,
	addrfabs,
	addrfloor,
	addrfmod,
	addrqsort,
	addrrand,
	addrsrand,
	addrclock,
	addrdifftime,
	addrmktime,
	addrtime,
	addrasctime,
	addrctime,
	addrgmtime,
	addrstrftime,
	
	// new internal procs for SC3.5
	addrfiltericon,
	addriconscroll,
	addrfilterprop,
	addrupropscroll,
	addrautotext,
	addrdumpfield,
	addrgetpicture,
	addrmapspot,
	addrcalcspot,
	addrdrawedit,
	addrloadlist,
	addrsetpicture,

	// new internal procs for SC3.6
	addrweautotext,
	addrwestupidtextvector,
	addrwepacktext,
	
	// new internal procs for SC3.61
	addrwenew,
	addrwedispose,
	addrweupdate,
	addrwecaltext,
	addrweusetext,
	addrweactivate,
	addrwedeactivate,
	addrwegetselect,
	addrwesetselect,
	addrwekey,
	addrweinsert,
	addrwesetstyle,
	addrwecut,
	addrwecopy,
	addrwecopyrange,
	addrwepaste,
	addrwecanpaste,
	addrwedelete,
	addrweusestylscrap,
	addrweoffsetoline,
	addrwegetoffset,
	addrwegetpoint,
	addrwescroll,
	addrweselview,
	addrwegetheight,
	addrwegetext,
	addrwegetextlength,
	addrwegetchar,
	addrwecountlines,
	addrwecontinuoustyle,
	addrweversion,
	addrwebuildfontable,
	addrweupdatefontable,
	addrweupdatescrap,
	addrwefindword,
	addrwefindline,
	addrwefindpgph,
	addrwecharbyte,
	addrwechartype,
	addrweclick,
	addrweisactive,
	addrvsprintf,
	addrvsscanf,
	addrxrunanswer,
	addrrunask,
	addrxrunlist,
	addrxrunanswerfile,
	addrxrunanswerfolder,
	addrgetpath,
	addrxrunanswerprogram,
	addrimportimage,
	addrgetcachepicture,
	addrlowdefine,
	addrlowuserprop,
	addrlowuserpropidx,
	addrlowuserprophand,
	addrlowsetuserprop,
	addrlowsetuserpropidx,
	addrobjectcursor,
	addrproputil,
	addrproputilidx,
	addrprophandutil,
	addrprophandutilidx,
	addrpropuserutil,
	addrmodproperty,
	addrmodpropertidx,
	addrlowmovepicture,
	addrshufflepicture,
	addrshuffleuprops,
	addrdefineprop,
	addrsetgroup,
	addrsetungroup,
	addrstringtodouble,
	addrdoubletostring,
	addrfindrez,
	addrlowrez,
	addrsendxrtnevent,
	addrkillpictbuffer,
	addrstringtotoken,
	addrupdatewindow,
	addrredraw,
	addrmesdialog,
	addrwegetinfo,
	addrwesetinfo,
	addrwesetdestrect,
	addrwesetviewrect,
	addrpack,
	addrunpack,
	addrgetsize,
	addridlecontrols,
	addrbwmatchproc,
	addrdontactivateproc,
	addrhandleupdateproc,
	addrwidget,
	addrwedonterase,
	addrsanitycheckedrectproc,
	addrdetachsuiteproc,
	addrdonteraserectproc,
	addrdonterasergnproc,
	addrldestview,
	addrwefeatureflag,
	addrwesetalignment,

	addrclipup,
	addrclipdown,
	addrfixbar,
	addrrectbar,
	addrgetinterior,

	addrscrihandlemousewheelproc,
	addrapphandlemousewheelproc,
	addrhandlemousemoveproc,
	addrhandlemousedragproc,
	addrhandlemousewheelproc,
	
	addrDockMenuHandlerProc,
	addrautoindentproc,
	addrfilterfilter,
	addrCollapseExpandWindowProc,
	addrwestupidertextproc,
	addrwenewpacktextproc,
	addrwegetdirtyflagproc,
	addrwesetdirtyflagproc,
	addrputdownspotwerecproc,
	
	addrmylistdefinition,
	addrwestreamrange,
	addrweput,
	
	addrweinsertobject,
	addrwegetobjectatoffset,
	addrwegetselectedobject,
	addrwegetobjectoffset,
	addrwegetobjectrefcon,
	addrwesetobjectrefcon,
	addrwegetobjectproperty,
	addrwesetobjectproperty,
	addrweremoveobjectproperty,
	addrwegetobjectframe,
	addrwegetobjectbaseline,
	addrwesetobjectbaseline,
	addrwegetobjectsize,
	addrwesetobjectsize,
	addrwesetobjectplacement,
	addrwegetobjectowner,
	addrwegetobjectype,
	addrwefindnextobject,
	addrwefindpreviousobject,
	addrwegetobjectdatahandle,
	
	addrwegetproperty,
	addrwesetproperty,
	addrweremoveproperty,
	
	addrwegetuserinfo,
	addrwesetuserinfo,
	addrweremoveuserinfo,
	
	addrwesetobjectdatahandle,
	addrwegetobjectbyindex,

	// more standard library functions
	addrstrtok,
	addrstrlen,
	addrstrcmp,
	addrstrncmp,
	addrmemcmp,
	addrstrchr,
	addrstrrchr,
	addrstrstr,
	addrstrcpy,
	addrstrpbrk,
	
	addrweinsertformattedtext,
	addrimportimagelong,
	addrverifystar,
	addrupdateword,
	
	addrwecontinuousruler,
	addrwegetoneattribute,
	addrweoffsetopararun,
	addrfindpictbuffer,
	addrgetpictag,
	
	addrxgetpathlong,
	addrxrunanswerfilelong,	

	lastglobalproc
};


// Handy string macros
#define pstr(string) "\p"string
#define upstr(string) ((unsigned char *)pstr(string))


// Transition data type
typedef struct {
	PixMapPtr	fCurrentScreen;
	PixMapPtr	fNextScreen;
	PixMapPtr	fBuffer;
	Rect		fTheBounds;
	short 		fSpeed;
	short		fSelector;
	short		fTotal_Steps;
	float		fCurrent_Step;
	short		fInfo_needsbuffer;
	short		fError;
} VisEffect;

#pragma options align=reset

#endif	// ndef __commonEXT47
