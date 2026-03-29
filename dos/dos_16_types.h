#ifndef DOS_16_TYPES_H
#define DOS_16_TYPES_H
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>

// Add proper definitions so our OS knows what we are talking about
// Because DOS fucking sucks in modernizing to ARM64
typedef uint8_t                 byte_t;
typedef uint16_t                halfword_t;   // ARM64's "half-word"
typedef uint32_t                word_t;       // ARM64's "word"  
typedef uint64_t                doubleword_t; // ARM64's "double-word"
typedef __int128                quadword_t;   // ARM64's "quad-word"

// DOS Compatibility Mapping
#define WORD                    halfword_t   // DOS word = ARM64 halfword
#define DWORD                   word_t       // DOS dword = ARM64 word
#define QWORD                   doubleword_t // DOS qword = ARM64 doubleword

// Basic Type Definitions
typedef int                     INT;
typedef unsigned int            UINT;
typedef short                   SHORT;
typedef unsigned short          USHORT;
typedef long                    LONG;
typedef unsigned long           ULONG;
typedef void*                   HANDLE;
typedef unsigned char           BYTE;
typedef int                     HFILE;     // File handle

// ============================================
// Structures
// ============================================
typedef struct {
    int x;
    int y;
} POINT;

// Function Pointers
typedef void                    (*FARPROC)();   // No "far" on ARM64

// HUGE Pointer (No-op on ARM64)
#define huge
#define HUGE_T                  huge

// Macros you can find in so many Windows documentation books
#define HIWORD(l)               ((uint16_t)(((uint32_t)(l) >> 16) & 0xFFFF))
#define LOWORD(l)               ((uint16_t)((uint32_t)(l) & 0xFFFF))

// DOS-to-ARM64 Macro Mappings
#define SHORTPARM               INT
#define HMF                     HANDLE
#define USHORT2ULONG            USHORT
#define SHORT2ULONG             SHORT
#define BYTE2WORD               BYTE
#define MPOINT                  POINT
#define WNDPROC                 FARPROC

// Macros DOS likes to use
#define CONVERT_WORD_TO_DWORD	WORD
#define CHARACTER_PARAM         char
#define SHORT_PARAM             INT
#define VERSION                 WORD
#define HMF                     HANDLE
#define PDLLMEM                 WORD
#define CONVERT_CHAR_TO_ULONG   char
#define CONVERT_USHORT_TO_ULONG	USHORT
#define CONVERT_SHORT_TO_ULONG  SHORT
#define CONVERT_INT_TO_DWORD    INT
#define CONVERT_INT_TO_WORD     INT
#define CONVERT_BYTE_TO_WORD    BYTE
#define MOVEABLE_POINT          POINT

#define HINSTANCE               HANDLE
#define HMODULE                 HANDLE

#define WNDPROC                 FARPROC
#define PROC                    FARPROC
#define HUGE_T                  huge

#define HFILE2INT(h, flags)     (INT)(h)
#define INT2HFILE(i)            (HFILE)(i)
#define DUPHFILE(h)             (HFILE)dup((INT)(h))
#define MGLOBALPTR(p)           HIWORD((LONG)p)
#define _LOADDS
#define _EXPORT
#define MFARPROC	            FARPROC

#endif
