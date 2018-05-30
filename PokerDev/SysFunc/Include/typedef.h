
#pragma once
#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__



#ifdef	WIN32
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <WinSock2.h>
#include <Windows.h>

typedef unsigned int	UINT;
typedef unsigned long	DWORD;
typedef unsigned char	BYTE;
typedef unsigned char	Byte;
typedef unsigned char   byte;
typedef short			SHORT;
typedef float			FLOAT;
typedef short			int2; 
typedef int             int4;
typedef unsigned short	uint2;
typedef unsigned int	uint4;
typedef long			long4;
typedef long long		long8;
typedef long long       int64_t;
typedef unsigned long	ulong4;
typedef unsigned long long ulong8;
typedef unsigned char   u_char;
typedef unsigned short  u_short;
typedef unsigned int    u_int;
typedef unsigned long   u_long;
typedef char CHAR;

#else

#include <stdlib.h>
//namespace AGFrameWorkTypes{
    
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef CONST
#define CONST const
#endif

//----------------------------
typedef unsigned char	byte;
typedef unsigned char	BYTE;
typedef long long       __int64;
typedef short			int2;
typedef int             int4;
typedef unsigned short	uint2;
typedef unsigned int	uint4;
typedef long			long4;
typedef long long		long8;
typedef unsigned long	ulong4;
typedef unsigned long long ulong8;
typedef	unsigned int		u_int;
//----------------------------

typedef char TCHAR;
typedef char CHAR;
typedef const  char* LPCSTR; 
typedef const char* LPSTR;
typedef const char* LPCTSTR;
typedef signed char     BOOL;
typedef long LONG;
typedef unsigned long u_long;
typedef void* LPVOID;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef unsigned char Byte;
typedef unsigned char   byte;
typedef short SHORT;
typedef float FLOAT;

typedef unsigned int LRESULT;
typedef unsigned int WPARAM;
typedef unsigned long LPARAM;
typedef unsigned short WORD;
typedef unsigned long long DWORD_PTR;
typedef UINT UINT_PTR;


//typedef short			int2;
//typedef int				int4;
typedef unsigned short	uint2;
typedef unsigned int	uint4;
    
    //typedef long			long4;
typedef long long		long8;
typedef unsigned long	ulong4;
typedef unsigned long long ulong8;
    typedef unsigned int    u_int;
    

#ifndef MATX_PATH
    
    #define MAX_PATH          260
    
#endif
    
#ifndef __64int__
#define __int64 long long
#endif
    
#ifndef CONST
#define CONST               const
#endif
    
#define MAKEWORD(a, b)      ((WORD)(((BYTE)((DWORD_PTR)(a) & 0xff)) | ((WORD)((BYTE)((DWORD_PTR)(b) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)((DWORD_PTR)(a) & 0xffff)) | ((DWORD)((WORD)((DWORD_PTR)(b) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)((DWORD_PTR)(l) & 0xffff))
#define HIWORD(l)           ((WORD)((DWORD_PTR)(l) >> 16))
#define LOBYTE(w)           ((BYTE)((DWORD_PTR)(w) & 0xff))
#define HIBYTE(w)           ((BYTE)((DWORD_PTR)(w) >> 8))

#endif


//typedef CHAR TPATH[260];
    

//////////////////////////////////////////////////////////////////////////
// 获取格式化字符串
extern char* GetFormatString(const char* lpFormat, ...);

////////////////////////////////////////////////////////////////////////////
// 写日志
extern void WriteLog(UINT nStyle, LPCSTR lpszFormat, ...);


#ifndef WIN32

extern unsigned long GetTickCount();

#endif

//using namespace AGFrameWorkTypes;

#endif
