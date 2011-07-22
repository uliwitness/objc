/*
 * —————————————————————————————————————————————————————————————————————————————————————————————————————————————
 *  IT_STDLIB.c
 *
 *	Deprecated routines to access C Standard Library functions compiled into the SuperCard runtime
 *  Copyright Mark Lucas 2010. All rights reserved.
 * —————————————————————————————————————————————————————————————————————————————————————————————————————————————
 */

#include "IT_STDLIB.h"
#include "InternalsToolbox_460.h"

typedef int (*vsprintfprocptr)(char *, const char *, va_list);
#if _USE_ROUTINE_DESCRIPTORS_
#pragma options align=mac68k
enum {
	vsprintfprocInfo = kThinkCStackBased
		 	| RESULT_SIZE(SIZE_CODE(sizeof(int)))
		 	| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(char *)))
		 	| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(const char *)))
		 	| STACK_ROUTINE_PARAMETER(3, SIZE_CODE(sizeof(va_list)))
};
#define Callvsprintf( vsprintfproc, s, fmt, arg )	\
CallUniversalProc( (UniversalProcPtr) vsprintfproc, vsprintfprocInfo, s, fmt, arg )
#else
#define Callvsprintf( vsprintfproc, s, fmt, arg )	(*(vsprintfprocptr)(vsprintfproc))( s, fmt, arg )
#endif


typedef int (*vsscanfprocptr)(char *, const char *, va_list);
#if _USE_ROUTINE_DESCRIPTORS_
#pragma options align=mac68k
enum {
	vsscanfprocInfo = kThinkCStackBased
		 	| RESULT_SIZE(SIZE_CODE(sizeof(int)))
		 	| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(char *)))
		 	| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(const char *)))
		 	| STACK_ROUTINE_PARAMETER(3, SIZE_CODE(sizeof(va_list)))
};
#define Callvsscanf( vsscanfproc, s, fmt, arg )	\
CallUniversalProc( (UniversalProcPtr) vsscanfproc, vsscanfprocInfo, s, fmt, arg )
#else
#define Callvsscanf( vsscanfproc, s, fmt, arg )	(*(vsscanfprocptr)(vsscanfproc))( s, fmt, arg )
#endif


typedef int (*atoiprocptr)(const char *);
#if _USE_ROUTINE_DESCRIPTORS_
#pragma options align=mac68k
enum {
	atoiprocInfo = kThinkCStackBased
		 	| RESULT_SIZE(SIZE_CODE(sizeof(int)))
		 	| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(const char *)))
};
#define Callatoi( atoiproc, s )	\
CallUniversalProc( (UniversalProcPtr) atoiproc, atoiprocInfo, s )
#else
#define Callatoi( atoiproc, s )	(*(atoiprocptr)(atoiproc))( s )
#endif


typedef long (*atolprocptr)(const char *);
#if _USE_ROUTINE_DESCRIPTORS_
#pragma options align=mac68k
enum {
	atolprocInfo = kThinkCStackBased
		 	| RESULT_SIZE(SIZE_CODE(sizeof(long)))
		 	| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(const char *)))
};
#define Callatol( atolproc, s )	\
CallUniversalProc( (UniversalProcPtr) atolproc, atolprocInfo, s )
#else
#define Callatol( atolproc, s )	(*(atolprocptr)(atolproc))( s )
#endif


typedef double (*atofprocptr)(const char *);
#if _USE_ROUTINE_DESCRIPTORS_
#pragma options align=mac68k
enum {
	atofprocInfo = kThinkCStackBased
		 	| RESULT_SIZE(SIZE_CODE(sizeof(double)))
		 	| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(const char *)))
};
#define Callatof( atofproc, s )	\
CallUniversalProc( (UniversalProcPtr) atofproc, atofprocInfo, s )
#else
#define Callatof( atofproc, s )	(*(atofprocptr)(atofproc))( s )
#endif


typedef size_t (*strlenprocptr)(const char *);
#if _USE_ROUTINE_DESCRIPTORS_
#pragma options align=mac68k
enum {
	strlenprocInfo = kThinkCStackBased
		 	| RESULT_SIZE(SIZE_CODE(sizeof(size_t)))
		 	| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(char *)))
};
#define Callstrlen( strlenproc, s )	\
CallUniversalProc( (UniversalProcPtr) strlenproc, strlenprocInfo, s )
#else
#define Callstrlen( strlenproc, s )	(*(strlenprocptr)(strlenproc))( s )
#endif


typedef char *(*strchrprocptr)(const char *, int);
#if _USE_ROUTINE_DESCRIPTORS_
#pragma options align=mac68k
enum {
	strchrprocInfo = kThinkCStackBased
		 	| RESULT_SIZE(SIZE_CODE(sizeof(char *)))
		 	| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(char *)))
			| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(int)))
};
#define Callstrchr( strchrproc, s, c )	\
CallUniversalProc( (UniversalProcPtr) strchrproc, strchrprocInfo, s, c )
#else
#define Callstrchr( strchrproc, s, c )	(*(strchrprocptr)(strchrproc))( s, c )
#endif


typedef char *(*strrchrprocptr)(const char *, int);
#if _USE_ROUTINE_DESCRIPTORS_
#pragma options align=mac68k
enum {
	strrchrprocInfo = kThinkCStackBased
		 	| RESULT_SIZE(SIZE_CODE(sizeof(char *)))
		 	| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(char *)))
			| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(int)))
};
#define Callstrrchr( strrchrproc, s, c )	\
CallUniversalProc( (UniversalProcPtr) strrchrproc, strrchrprocInfo, s, c )
#else
#define Callstrrchr( strrchrproc, s, c )	(*(strrchrprocptr)(strrchrproc))( s, c )
#endif


typedef char *(*strstrprocptr)(const char *, const char *);
#if _USE_ROUTINE_DESCRIPTORS_
#pragma options align=mac68k
enum {
	strstrprocInfo = kThinkCStackBased
		 	| RESULT_SIZE(SIZE_CODE(sizeof(char *)))
		 	| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(char *)))
			| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(char *)))
};
#define Callstrstr( strstrproc, s1, s2 )	\
CallUniversalProc( (UniversalProcPtr) strstrproc, strstrprocInfo, s1, s2 )
#else
#define Callstrstr( strstrproc, s1, s2 )	(*(strstrprocptr)(strstrproc))( s1, s2 )
#endif


typedef char *(*strtokprocptr)(char *, const char *);
#if _USE_ROUTINE_DESCRIPTORS_
#pragma options align=mac68k
enum {
	strtokprocInfo = kThinkCStackBased
		 	| RESULT_SIZE(SIZE_CODE(sizeof(char *)))
		 	| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(char *)))
			| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(char *)))
};
#define Callstrtok( strtokproc, s1, s2 )	\
CallUniversalProc( (UniversalProcPtr) strtokproc, strtokprocInfo, s1, s2 )
#else
#define Callstrtok( strtokproc, s1, s2 )	(*(strtokprocptr)(strtokproc))( s1, s2 )
#endif


typedef int(*strcmpprocptr)(const char *, const char *);
#if _USE_ROUTINE_DESCRIPTORS_
#pragma options align=mac68k
enum {
	strcmpprocInfo = kThinkCStackBased
		 	| RESULT_SIZE(SIZE_CODE(sizeof(int)))
		 	| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(char *)))
			| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(char *)))
};
#define Callstrcmp( strcmpproc, s1, s2 )	\
CallUniversalProc( (UniversalProcPtr) strcmpproc, strcmpprocInfo, s1, s2 )
#else
#define Callstrcmp( strcmpproc, s1, s2 )	(*(strcmpprocptr)(strcmpproc))( s1, s2 )
#endif


typedef int(*strncmpprocptr)(const char *, const char *, size_t);
#if _USE_ROUTINE_DESCRIPTORS_
#pragma options align=mac68k
enum {
	strncmpprocInfo = kThinkCStackBased
		 	| RESULT_SIZE(SIZE_CODE(sizeof(int)))
		 	| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(char *)))
			| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(char *)))
			| STACK_ROUTINE_PARAMETER(3, SIZE_CODE(sizeof(size_t)))
};
#define Callstrncmp( strncmpproc, s1, s2, n )	\
CallUniversalProc( (UniversalProcPtr) strncmpproc, strncmpprocInfo, s1, s2, n )
#else
#define Callstrncmp( strncmpproc, s1, s2, n )	(*(strncmpprocptr)(strncmpproc))( s1, s2, n )
#endif


typedef int(*memcmpprocptr)(const void *, const void *, size_t);
#if _USE_ROUTINE_DESCRIPTORS_
#pragma options align=mac68k
enum {
	memcmpprocInfo = kThinkCStackBased
		 	| RESULT_SIZE(SIZE_CODE(sizeof(int)))
		 	| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(char *)))
			| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(char *)))
			| STACK_ROUTINE_PARAMETER(3, SIZE_CODE(sizeof(size_t)))
};
#define Callmemcmp( memcmpproc, s1, s2, n )	\
CallUniversalProc( (UniversalProcPtr) memcmpproc, memcmpprocInfo, s1, s2, n )
#else
#define Callmemcmp( memcmpproc, s1, s2, n )	(*(memcmpprocptr)(memcmpproc))( s1, s2, n )
#endif


typedef char *(*strpbrkprocptr)(const char *, const char *);
#if _USE_ROUTINE_DESCRIPTORS_
#pragma options align=mac68k
enum {
	strpbrkprocInfo = kThinkCStackBased
		 	| RESULT_SIZE(SIZE_CODE(sizeof(char *)))
		 	| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(char *)))
			| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(char *)))
};
#define Callstrpbrk( strpbrkproc, s1, s2 )	\
CallUniversalProc( (UniversalProcPtr) strpbrkproc, strpbrkprocInfo, s1, s2 )
#else
#define Callstrpbrk( strpbrkproc, s1, s2 )	(*(strpbrkprocptr)(strpbrkproc))( s1, s2 )
#endif


typedef char *(*strcpyprocptr)(char *, const char *);
#if _USE_ROUTINE_DESCRIPTORS_
#pragma options align=mac68k
enum {
	strcpyprocInfo = kThinkCStackBased
		 	| RESULT_SIZE(SIZE_CODE(sizeof(char *)))
		 	| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(char *)))
	| STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(char *)))
};
#define Callstrcpy( strcpyproc, s1, s2 )	\
CallUniversalProc( (UniversalProcPtr) strcpyproc, strcpyprocInfo, s1, s2 )
#else
#define Callstrcpy( strcpyproc, s1, s2 )	(*(strcpyprocptr)(strcpyproc))( s1, s2 )
#endif


typedef double(*sinprocptr)(double);
#if _USE_ROUTINE_DESCRIPTORS_
#pragma options align=mac68k
enum {
	sinprocInfo = kThinkCStackBased
		 	| RESULT_SIZE(SIZE_CODE(sizeof(double)))
		 	| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(double)))
};
#define Callsin( sinproc, d )	\
CallUniversalProc( (UniversalProcPtr) sinproc, sinprocInfo, d )
#else
#define Callsin( sinproc, d )	(*(sinprocptr)(sinproc))( d )
#endif


typedef double(*cosprocptr)(double);
#if _USE_ROUTINE_DESCRIPTORS_
#pragma options align=mac68k
enum {
	cosprocInfo = kThinkCStackBased
		 	| RESULT_SIZE(SIZE_CODE(sizeof(double)))
		 	| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(double)))
};
#define Callcos( cosproc, d )	\
CallUniversalProc( (UniversalProcPtr) cosproc, cosprocInfo, d )
#else
#define Callcos( cosproc, d )	(*(cosprocptr)(cosproc))( d )
#endif


typedef double(*tanprocptr)(double);
#if _USE_ROUTINE_DESCRIPTORS_
#pragma options align=mac68k
enum {
	tanprocInfo = kThinkCStackBased
		 	| RESULT_SIZE(SIZE_CODE(sizeof(double)))
		 	| STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(double)))
};
#define Calltan( tanproc, d )	\
CallUniversalProc( (UniversalProcPtr) tanproc, tanprocInfo, d )
#else
#define Calltan( tanproc, d )	(*(tanprocptr)(tanproc))( d )
#endif

extern XCmdPtr	par;

double ATOF(const char *p)
{
	atofprocptr atofp;

	GetGAddr(par, vgetgaddr);
	atofp = (atofprocptr)((ProcPtr *)par->outArgs[1])[addratof];
	return Callatof(atofp, p);
}

int ATOI(const char *p)
{
	atoiprocptr atoip;

	GetGAddr(par, vgetgaddr);
	atoip = (atoiprocptr)((ProcPtr *)par->outArgs[1])[addratoi];
	return Callatoi(atoip, p);
}

long ATOL(const char *p)
{
	atolprocptr atolp;

	GetGAddr(par, vgetgaddr);
	atolp = (atolprocptr)((ProcPtr *)par->outArgs[1])[addratol];
	return Callatoi(atolp, p);
}

double COS(const double d)
{
	cosprocptr cosp;

	GetGAddr(par, vgetgaddr);
	cosp = (cosprocptr)((ProcPtr *)par->outArgs[1])[addrcos];
	return (double)Callcos(cosp, d);
}

int MEMCMP(const char *dst, const char *src, size_t n)
{
	memcmpprocptr memcmpp;

	GetGAddr(par, vgetgaddr);
	memcmpp = (memcmpprocptr)((ProcPtr *)par->outArgs[1])[addrmemcmp];
	return Callmemcmp(memcmpp, dst, src, n);
}

double SIN(const double d)
{
	sinprocptr sinp;

	GetGAddr(par, vgetgaddr);
	sinp = (sinprocptr)((ProcPtr *)par->outArgs[1])[addrsin];
	return (double)Callsin(sinp, d);
}

int SPRINTF(char *s, const char *fmt, ...)
{
	vsprintfprocptr vsprintfp;
	va_list ap;
	int len;

	GetGAddr(par, vgetgaddr);
	vsprintfp = (vsprintfprocptr)((ProcPtr *)par->outArgs[1])[addrvsprintf];
	va_start(ap, fmt);
	len = Callvsprintf(vsprintfp, s, fmt, ap);
	va_end(ap);
	return(len);
}


char *STRCHR(char *s, int c)
{
	strchrprocptr strchrp;

	GetGAddr(par, vgetgaddr);
	strchrp = (strchrprocptr)((ProcPtr *)par->outArgs[1])[addrstrchr];
	return Callstrchr(strchrp, s, c);
}

int STRCMP(char *dst, const char *src)
{
	strcmpprocptr strcmpp;

	GetGAddr(par, vgetgaddr);
	strcmpp = (strcmpprocptr)((ProcPtr *)par->outArgs[1])[addrstrcmp];
	return Callstrcmp(strcmpp, dst, src);
}

char *STRCPY(char *dst, const char *src)
{
	strcpyprocptr strcpyp;

	GetGAddr(par, vgetgaddr);
	strcpyp = (strcpyprocptr)((ProcPtr *)par->outArgs[1])[addrstrcpy];
	return Callstrcpy(strcpyp, dst, src);
}


int STRLEN(const char *s)
{
	strlenprocptr strlenp;

	GetGAddr(par, vgetgaddr);
	strlenp = (strlenprocptr)((ProcPtr *)par->outArgs[1])[addrstrlen];
	return Callstrlen(strlenp, s);
}


int STRNCMP(const char *dst, const char *src, size_t n)
{
	strncmpprocptr strncmpp;

	GetGAddr(par, vgetgaddr);
	strncmpp = (strncmpprocptr)((ProcPtr *)par->outArgs[1])[addrstrncmp];
	return Callstrncmp(strncmpp, dst, src, n);
}


char *STRPBRK(const char *s1, const char *s2)
{
	strpbrkprocptr strpbrkp;

	GetGAddr(par, vgetgaddr);
	strpbrkp = (strpbrkprocptr)((ProcPtr *)par->outArgs[1])[addrstrpbrk];
	return Callstrpbrk(strpbrkp, s1, s2);
}


char *STRRCHR(char *s, int c)
{
	strrchrprocptr strrchrp;

	GetGAddr(par, vgetgaddr);
	strrchrp = (strrchrprocptr)((ProcPtr *)par->outArgs[1])[addrstrrchr];
	return Callstrrchr(strrchrp, s, c);
}


char *STRSTR(const char *s1, const char *s2)
{
	strstrprocptr strstrp;

	GetGAddr(par, vgetgaddr);
	strstrp = (strstrprocptr)((ProcPtr *)par->outArgs[1])[addrstrstr];
	return Callstrstr(strstrp, s1, s2);
}

char *STRTOK(char *s1, const char *s2)
{
	strtokprocptr strtokp;

	GetGAddr(par, vgetgaddr);
	strtokp = (strtokprocptr)((ProcPtr *)par->outArgs[1])[addrstrtok];
	return Callstrtok(strtokp, s1, s2);
}

int SSCANF(char *s, const char *fmt, ...)
{
	vsscanfprocptr vscanfp;
	va_list ap;
	int cnt;

	GetGAddr(par, vgetgaddr);
	vscanfp = (vsscanfprocptr)((ProcPtr *)par->outArgs[1])[addrvsscanf];
	va_start(ap, fmt);
	cnt = Callvsscanf(vscanfp, s, fmt, ap);
	va_end(ap);
	return(cnt);
}

double TAN(const double d)
{
	tanprocptr tanp;

	GetGAddr(par, vgetgaddr);
	tanp = (tanprocptr)((ProcPtr *)par->outArgs[1])[addrtan];
	return Calltan(tanp, d);
}

