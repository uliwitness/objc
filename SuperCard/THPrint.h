//	SuperCard 4.72 THPrint.h file
//	Obsolete Print Manager data structures SuperCard still understands
//	Copyright Apple Inc
//	All rights reserved worldwide.
#ifndef __THPRINT_H__
#define __THPRINT_H__

#if __GNUC__ 

#pragma options align = mac68k


/*  The maximum allowed size of a fAddress in PPCXTIAddress */
/*enum {
  kMaxPPCXTIAddress             = 95
};*/

struct SysEnvRec {
	short               environsVersion;
	short               machineType;
	short               systemVersion;
	short               processor;
	Boolean             hasFPU;
	Boolean             hasColorQD;
	short               keyBoardType;
	short               atDrvrVersNum;
	short               sysVRefNum;
};
typedef struct SysEnvRec                SysEnvRec;

struct GrafPort {
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
                                              /*StyleField occupies 16-bits, but only first 8-bits are used*/
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
typedef struct GrafPort                 GrafPort;

struct TPrPort {
  GrafPort            gPort;                  /*The Printer's graf port.*/
  QDProcs             gProcs;                 /*..and its procs*/
  long                lGParam1;               /*16 bytes for private parameter storage.*/
  long                lGParam2;
  long                lGParam3;
  long                lGParam4;
  Boolean             fOurPtr;                /*Whether the PrPort allocation was done by us.*/
  Boolean             fOurBits;               /*Whether the BitMap allocation was done by us.*/
};
typedef struct TPrPort                  TPrPort;
typedef TPrPort *                       TPPrPort;

typedef SInt8 TFeed;
typedef SInt8 TScan;
typedef TPPrPort                        TPPrPortRef;
/* Printing Graf Port. All printer imaging, whether spooling, banding, etc, happens "thru" a GrafPort.
  This is the "PrPeek" record. */
struct TPrInfo {
  short               iDev;                   /*Font mgr/QuickDraw device code*/
  short               iVRes;                  /*Resolution of device, in device coordinates*/
  short               iHRes;                  /*..note: V before H => compatable with Point.*/
  Rect                rPage;                  /*The page (printable) rectangle in device coordinates.*/
};
typedef struct TPrInfo                  TPrInfo;
typedef TPrInfo *                       TPPrInfo;
/* Print Info Record: The parameters needed for page composition. */
struct TPrStl {
  short               wDev;
  short               iPageV;
  short               iPageH;
  SInt8               bPort;
  TFeed               feed;
};
typedef struct TPrStl                   TPrStl;
typedef TPrStl *                        TPPrStl;
struct TPrXInfo {
  short               iRowBytes;
  short               iBandV;
  short               iBandH;
  short               iDevBytes;
  short               iBands;
  SInt8               bPatScale;
  SInt8               bUlThick;
  SInt8               bUlOffset;
  SInt8               bUlShadow;
  TScan               scan;
  SInt8               bXInfoX;
};
typedef struct TPrXInfo                 TPrXInfo;
typedef TPrXInfo *                      TPPrXInfo;
struct TPrJob {
  short               iFstPage;					/*Page Range.*/
  short               iLstPage;
  short               iCopies;					/*No. copies.*/
  SInt8               bJDocLoop;				/*The Doc style: Draft, Spool, .., and ..*/
  Boolean             fFromUsr;					/*Printing from an User's App (not PrApp) flag*/
  //PrIdleUPP           pIdleProc;              /*The Proc called while waiting on IO etc.*/
  void *           pIdleProc;					/*The Proc called while waiting on IO etc.*/
  StringPtr           pFileName;				/*Spool File Name: NIL for default.*/
  short               iFileVol;					/*Spool File vol, set to 0 initially*/
  SInt8               bFileVers;				/*Spool File version, set to 0 initially*/
  SInt8               bJobX;					/*An eXtra byte.*/
};
typedef struct TPrJob                   TPrJob;
typedef TPrJob *                        TPPrJob;
/* Print Job: Print "form" for a single print request. */
struct TPrint {
  short               iPrVersion;             /*(2) Printing software version*/
  TPrInfo             prInfo;                 /*(14) the PrInfo data associated with the current style.*/
  Rect                rPaper;                 /*(8) The paper rectangle [offset from rPage]*/
  TPrStl              prStl;                  /*(8)  This print request's style.*/
  TPrInfo             prInfoPT;               /*(14)  Print Time Imaging metrics*/
  TPrXInfo            prXInfo;                /*(16)  Print-time (expanded) Print info record.*/
  TPrJob              prJob;                  /*(20) The Print Job request (82)  Total of the above; 120-82 = 38 bytes needed to fill 120*/
  short               printX[19];             /*Spare to fill to 120 bytes!*/
};
typedef struct TPrint                   TPrint;
typedef TPrint *                        TPPrint;
typedef TPPrint *                       THPrint;

#pragma options align = reset

#endif	__GNUC__

#endif //#ifndef __THPRINT_H_
