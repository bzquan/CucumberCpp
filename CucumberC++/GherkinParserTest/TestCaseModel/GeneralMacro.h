#pragma once

#include <string>

#ifndef NULL
#define NULL	0
#endif

#ifndef BOOL
#define BOOL	int
#endif

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

#ifndef UBYTE
#define UBYTE unsigned char
#endif

#ifndef USHORT
#define USHORT unsigned short
#endif

#ifndef SHORT
#define SHORT short
#endif

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef MAX_BYTE
#define MAX_BYTE 0xFF
#endif

#ifndef MAX_ULONG
#define MAX_ULONG 0xFFFFFFFF
#endif

#define STRINGIFY2(x) #x
#define STRINGIFY(x) STRINGIFY2(x)
#define PASTE2(a, b) a##b

typedef wchar_t NChar;
typedef wchar_t NCHAR;
typedef std::wstring NString;

#define MY_ASSERT(exp)\
	if (!(exp)) return;

#define MY_ASSERT2(exp, result)\
	if (!(exp)) return result;
