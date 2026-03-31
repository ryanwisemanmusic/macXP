#ifndef DIRECTX_DEFS_H
#define DIRECTX_DEFS_H

#include "win32defs.h"

#ifndef HMONITOR
typedef HANDLE HMONITOR;
#endif

#ifndef RECT
typedef struct tagRECT {
	LONG left;
	LONG top;
	LONG right;
	LONG bottom;
} RECT, *PRECT, *LPRECT;
#endif

#ifndef _PALETTEENTRY_DEFINED
#define _PALETTEENTRY_DEFINED
typedef struct tagPALETTEENTRY {
	BYTE peRed;
	BYTE peGreen;
	BYTE peBlue;
	BYTE peFlags;
} PALETTEENTRY, *LPPALETTEENTRY, *PPALETTEENTRY;
#endif

#ifndef _RGNDATAHEADER_DEFINED
#define _RGNDATAHEADER_DEFINED
typedef struct _RGNDATAHEADER {
	DWORD dwSize;
	DWORD iType;
	DWORD nCount;
	DWORD nRgnSize;
	RECT rcBound;
} RGNDATAHEADER;
#endif

#ifndef _RGNDATA_DEFINED
#define _RGNDATA_DEFINED
typedef struct _RGNDATA {
	RGNDATAHEADER rdh;
	char Buffer[1];
} RGNDATA, *PRGNDATA, *LPRGNDATA;
#endif

#endif /* DIRECTX_DEFS_H */
