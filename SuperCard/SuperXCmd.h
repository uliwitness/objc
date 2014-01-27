//*************************************************************************************
//
//	SuperXCmd.h  
//	
//  Use this instead of HyperXCmd.h
//
//*************************************************************************************

#ifndef _SuperXCmdH_
#define _SuperXCmdH_

#include <Carbon/Carbon.h>

#pragma pack(push, 2)

typedef struct XCmdBlock {
	short		paramCount;		// 0
	Handle		params[16];		// 2
	Handle		returnValue;	// 66
	Boolean		passFlag;		// 70
	SignedByte  filler1;		// 71
	Ptr			entryPoint;		// 72
	short		request;		// 76
	short		result;			// 78
	long		inArgs[8];		// 80
	long		outArgs[4];		// 112
} XCmdBlock, *XCmdPtr;

typedef struct PixInfo {
	Handle theData;
	CTabHandle theTable;
	Rect bounds;
	short colorFlag;
	short rowBytes;
	short penMode;
} PixInfo, *PixInfoPtr;

typedef struct StarInfo {
	long theType;
	long theSize;
	long theID;
	long index;
	Str255 theName;
} StarInfo, *StarInfoPtr;


#define 	xresSucc			0
#define 	xresFail			1
#define 	xresNotImp			2

#define 	xreqSendCardMessage	1
#define 	xreqEvalExpr		2
#define 	xreqStringLength	3
#define 	xreqStringMatch		4
#define 	xreqSendHCMessage	5
#define 	xreqZeroBytes		6
#define 	xreqPasToZero		7
#define 	xreqZeroToPas		8
#define 	xreqStrToLong		9
#define 	xreqStrToNum		10
#define 	xreqStrToBool		11
#define 	xreqStrToExt		12
#define 	xreqLongToStr 		13
#define 	xreqNumToStr		14
#define 	xreqNumToHex		15
#define 	xreqBoolToStr		16
#define 	xreqExtToStr		17
#define 	xreqGetGlobal		18
#define 	xreqSetGlobal		19
#define 	xreqGetFieldByName	20
#define 	xreqGetFieldByNum	21
#define 	xreqGetFieldByID	22
#define 	xreqSetFieldByName	23
#define 	xreqSetFieldByNum	24
#define 	xreqSetFieldByID	25
#define 	xreqStringEqual		26
#define 	xreqReturnToPas		27
#define 	xreqScanToReturn	28
#define 	xreqScanToZero		39 

#define     xreqInstallPData	4503
#define     xreqInstallPDataLong	4505

#define 	xreqPixByName		5000
#define 	xreqPixByID			5001
#define 	xreqPixByNum		5002
#define 	xreqAddStar			5003
#define 	xreqGetStarByName	5004
#define 	xreqGetStarByID		5005
#define 	xreqDelStarByName	5006
#define 	xreqDelStarByID		5007
#define 	xreqAltStarByName	5008
#define 	xreqAltStarByID		5009
#define 	xreqCountStars		5010
#define 	xreqGetStarInfo		5011
#define 	xreqSendError		5012

#define 	xreqSetStarID		5013
#define 	xreqDefUProp		5014
#define 	xreqUnDefUProp		5015
#define 	xreqGetUProp		5016
#define 	xreqSetUProp		5017
#define		xreqCountUProps		5018
#define 	xreqGetUPropIdx		5019
#define 	xreqSetUPropIdx		5020
#define		xreqUPropNameToIdx	5021
#define		xreqUPropIdxToName	5022
#define		xreqSetStarName		5023
#define 	xreqDefUPropLong		5024
#define 	xreqUnDefUPropLong		5025
#define 	xreqGetUPropLong		5026
#define 	xreqSetUPropLong		5027
#define		xreqCountUPropsLong		5028
#define 	xreqGetUPropIdxLong		5029
#define 	xreqSetUPropIdxLong		5030
#define		xreqUPropNameToIdxLong	5031
#define		xreqUPropIdxToNameLong	5032


#define		xreqSendCardLongMessage		5500
#define		xreqSendHCLongMessage		5501
#define		xreqEvalLongExpr			5502

//********************************************************************************

typedef pascal void (*CallbackProcPtr)(void);

#define CallSCBack( xpb )	(*((CallbackProcPtr) (xpb)->entryPoint))()


//еееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееееее
// The Original HyperCard Callbacks, including a few that got left out
// in SuperCard's support for the HyperCard callbacks.

pascal void 	SendCardMessage	(XCmdPtr paramPtr, StringPtr msg);
pascal void		SendHCMessage	(XCmdPtr paramPtr, StringPtr msg);
pascal Handle 	EvalExpr		(XCmdPtr paramPtr, StringPtr expr);
pascal long 	StringLength	(XCmdPtr paramPtr, StringPtr strPtr);
pascal Ptr 		StringMatch		(XCmdPtr paramPtr, StringPtr pattern, Ptr target);
pascal void 	ZeroBytes		(XCmdPtr paramPtr, Ptr dstPtr, long longCount);
pascal Handle 	PasToZero		(XCmdPtr paramPtr, StringPtr pasStr);
pascal void 	ZeroToPas		(XCmdPtr paramPtr, char *zeroStr, StringPtr pasStr);

pascal Handle 	GetGlobal		(XCmdPtr paramPtr, StringPtr globName);
pascal void 	SetGlobal		(XCmdPtr paramPtr, StringPtr globName, Handle globValue);
pascal Handle 	GetFieldByName	(XCmdPtr paramPtr, Boolean cdFlag, StringPtr fieldName);
pascal Handle 	GetFieldByNum	(XCmdPtr paramPtr, Boolean cdFlag, short fieldNum);
pascal Handle 	GetFieldByID	(XCmdPtr paramPtr, Boolean cdFlag, short fieldID);
pascal void 	SetFieldByName	(XCmdPtr paramPtr, Boolean cdFlag, StringPtr fieldName, Handle fieldVal);
pascal void 	SetFieldByNum	(XCmdPtr paramPtr, Boolean cdFlag, short fieldNum, Handle fieldVal);
pascal void 	SetFieldByID	(XCmdPtr paramPtr, Boolean cdFlag, short fieldID, Handle fieldVal);
pascal Boolean 	StringEqual		(XCmdPtr paramPtr, StringPtr str1, StringPtr str2);
pascal void 	ReturnToPas		(XCmdPtr paramPtr, Ptr zeroStr, StringPtr pasStr);
pascal void 	ScanToReturn	(XCmdPtr paramPtr, Ptr *scanHndl);
pascal void 	ScanToZero		(XCmdPtr paramPtr, Ptr *scanHndl);

pascal long 	StrToLong		(XCmdPtr paramPtr, StringPtr strPtr);
pascal long 	StrToNum		(XCmdPtr paramPtr, StringPtr str);
pascal Boolean 	StrToBool		(XCmdPtr paramPtr, StringPtr str);
pascal Float80	StrToExt		(XCmdPtr paramPtr, StringPtr str);

pascal void 	LongToStr		(XCmdPtr paramPtr, long posNum, StringPtr mystr);
pascal void 	NumToStr		(XCmdPtr paramPtr, long num, StringPtr mystr);
pascal void 	NumToHex		(XCmdPtr paramPtr, long num, short nDigits, StringPtr mystr);
pascal void 	BoolToStr		(XCmdPtr paramPtr, Boolean abool, StringPtr mystr);
pascal void 	ExtToStr		(XCmdPtr paramPtr, Float80 myext, StringPtr mystr);


//****************************************************************************************
// SuperCard's additional callbacks

void 		InstallPData		(XCmdPtr paramPtr, StringPtr theObjectName, PicHandle thePicture );
void 		SendError			(XCmdPtr paramPtr, short theError);

PixInfoPtr 	GetPixByName		(XCmdPtr paramPtr, Boolean cardGraphicFlag, StringPtr graphicName);
PixInfoPtr 	GetPixByNum			(XCmdPtr paramPtr, Boolean cardGraphicFlag, short graphicNum);
PixInfoPtr 	GetPixByID			(XCmdPtr paramPtr, Boolean cardGraphicFlag, long graphicID);
Handle 		GetStarByName		(XCmdPtr paramPtr, StringPtr theName, ResType theType);
Handle 		GetStarByID			(XCmdPtr paramPtr, long theID, ResType theType);
void 		DelStarByID			(XCmdPtr paramPtr, long theID, ResType theType);
void 		DelStarByName		(XCmdPtr paramPtr, StringPtr theName, ResType theType);
void 		AltStarByName		(XCmdPtr paramPtr, StringPtr theName, ResType theType, Handle theData);
void		AltStarByID			(XCmdPtr paramPtr, long theID, ResType theType, Handle theData);
long 		AddStar				(XCmdPtr paramPtr, Handle theData, StringPtr theName, ResType theType);

long 		CountStars			(XCmdPtr paramPtr);
StarInfoPtr GetStarInfo			(XCmdPtr paramPtr, long index, ResType theType);
void		SetStarID			(XCmdPtr paramPtr, long oldID, ResType theType, long newID);
void		SetStarName			(XCmdPtr paramPtr, long theID, ResType theType, StringPtr newName);

// propData Handles you pass to these callbacks are copied by SuperCard; the originals still belong to you.
void 		DefineUserProperty			(XCmdPtr paramPtr, StringPtr objectDescrip, StringPtr propName);
void 		UnDefineUserProperty		(XCmdPtr paramPtr, StringPtr objectDescrip, StringPtr propName);
void 		GetUserPropByName			(XCmdPtr paramPtr, StringPtr objectDescrip, StringPtr propName, Handle *propData);
void 		SetUserPropByName			(XCmdPtr paramPtr, StringPtr objectDescrip, StringPtr propName, Handle propData);
void 		UserPropNameToIndex			(XCmdPtr paramPtr, StringPtr objectDescrip, StringPtr propName, long *index);
void		CountUserProps				(XCmdPtr paramPtr, StringPtr objectDescrip, long *count);
void 		GetUserPropByIndex			(XCmdPtr paramPtr, StringPtr objectDescrip, long index, Handle *propData);
void 		SetUserPropByIndex			(XCmdPtr paramPtr, StringPtr objectDescrip, long index, Handle propData);
void		UserPropIndexToName			(XCmdPtr paramPtr, StringPtr objectDescrip, long index, StringPtr propName);

// NOTE! These long form callbacks are available only in SuperCard 4.7 and above.
pascal void 	SendCardMessageLong			(XCmdPtr paramPtr, Handle msg);
pascal void		SendHCMessageLong			(XCmdPtr paramPtr, Handle msg);
pascal Handle 	EvalExprLong				(XCmdPtr paramPtr, Handle expr);
void			InstallPDataLong			(XCmdPtr paramPtr, Handle theObjectName, PicHandle thePicture );
void			DefineUserPropertyLong		(XCmdPtr paramPtr, Handle objectDescrip, StringPtr propName);
void			UnDefineUserPropertyLong	(XCmdPtr paramPtr, Handle objectDescrip, StringPtr propName);
void			GetUserPropByNameLong		(XCmdPtr paramPtr, Handle objectDescrip, StringPtr propName, Handle *propData);
void			SetUserPropByNameLong		(XCmdPtr paramPtr, Handle objectDescrip, StringPtr propName, Handle propData);
void			UserPropNameToIndexLong		(XCmdPtr paramPtr, Handle objectDescrip, StringPtr propName, long *index);
void			CountUserPropsLong			(XCmdPtr paramPtr, Handle objectDescrip, long *count);
void			GetUserPropByIndexLong		(XCmdPtr paramPtr, Handle objectDescrip, long index, Handle *propData);
void			SetUserPropByIndexLong		(XCmdPtr paramPtr, Handle objectDescrip, long index, Handle propData);
void			UserPropIndexToNameLong		(XCmdPtr paramPtr, Handle objectDescrip, long index, StringPtr propName);

#pragma pack(pop)

#endif	// #ifndef _SuperXCmdH_
