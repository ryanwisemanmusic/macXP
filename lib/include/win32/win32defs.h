#ifndef WINDOWS_WIN32DEFS_H
#define WINDOWS_WIN32DEFS_H

/* Clang compatibility for MSVC-style calling convention and declspec tokens. */
#ifndef __stdcall
#define __stdcall
#endif

#ifndef __cdecl
#define __cdecl
#endif

#ifndef __fastcall
#define __fastcall
#endif

#ifndef __forceinline
#define __forceinline inline
#endif

#ifndef __declspec
#define __declspec(x)
#endif

#ifndef UNALIGNED
#define UNALIGNED
#endif

/* Historical far/near macros used by legacy headers; make them no-ops here. */
#ifndef FAR
#define FAR
#endif

#ifndef NEAR
#define NEAR
#endif

/* Old RPC pointer annotation used in some IDL-generated headers. */
#ifndef _RPC_FAR
#define _RPC_FAR
#endif

/* Older calling-convention and socket typedef fallbacks used by legacy
   WinSock/MS extensions headers. These are guarded to avoid conflicts
   when real WinSock headers are present. */
#ifndef PASCAL
#define PASCAL __stdcall
#endif

#ifndef SOCKET
typedef unsigned int SOCKET;
#endif

#ifndef LPINT
typedef int *LPINT;
#endif

/* Wide-name helper used by headers that append a 'W' suffix for Unicode
   entrypoints. Provide a safe fallback when `windef.h` hasn't been
   included yet so constructs like `_WNAME(FuncName)(...)` parse. */
#ifndef _WNAME
#ifdef _WIN32_WCE
#define _WNAME(name) name
#else
#define _WNAME(name) name##W
#endif
#endif

/* Use a dedicated compatibility selector because we are trying to run
   Windows IRT. So because of that, it's why we are making said choices */
#ifndef WIN32_COMPAT_64
#define WIN32_COMPAT_64 1
#endif

#ifndef WIN32_COMPAT_USE_GS
#define WIN32_COMPAT_USE_GS 1
#endif

#include <stddef.h>

/* MSVC annotation/import compatibility for Clang-based macOS builds. */
#ifndef _NODISCARD
#define _NODISCARD
#endif

#ifndef _Check_return_
#define _Check_return_
#endif

#ifndef _VCRTIMP
#define _VCRTIMP
#endif

#ifndef _CRT_INSECURE_DEPRECATE_MEMORY
#define _CRT_INSECURE_DEPRECATE_MEMORY(x)
#endif

#ifndef _In_
#define _In_
#endif

#ifndef _In_reads_bytes_
#define _In_reads_bytes_(x)
#endif

#ifndef _In_reads_bytes_opt_
#define _In_reads_bytes_opt_(x)
#endif

#ifndef _Out_writes_bytes_all_
#define _Out_writes_bytes_all_(x)
#endif

#ifndef _Out_writes_bytes_all_opt_
#define _Out_writes_bytes_all_opt_(x)
#endif

#ifndef CONST
#define CONST const
#endif

#if !defined(_WINDEF_H) && !defined(_WINNT_H) && !defined(_WINNT_) && \
    !defined(WINDOWS_H) && !defined(_INC_WINDOWS)
#ifndef WINDOWS_BASE_H
#include "windows_base.h"
#endif

/* DDK headers frequently rely on BOOLEAN from winnt-style types. */
#ifndef _BOOLEAN_DEFINED
#define _BOOLEAN_DEFINED
typedef unsigned char BOOLEAN;
#endif

#ifndef USHORT
typedef unsigned short USHORT;
#endif

#ifndef ULONG
typedef unsigned long ULONG;
#endif

#ifndef LONG
typedef long LONG;
#endif

#ifndef LONGLONG
typedef long long LONGLONG;
#endif

#ifndef PLONGLONG
typedef LONGLONG *PLONGLONG;
#endif

#ifndef CCHAR
typedef char CCHAR;
#endif

#ifndef CSHORT
typedef short CSHORT;
#endif

#ifndef PUCHAR
typedef unsigned char *PUCHAR;
#endif

#ifndef PUSHORT
typedef unsigned short *PUSHORT;
#endif

#ifndef PBOOLEAN
typedef BOOLEAN *PBOOLEAN;
#endif

#ifndef PCH
typedef char *PCH;
#endif

#ifndef PCSTR
typedef const char *PCSTR;
#endif

#ifndef PCSZ
typedef const char *PCSZ;
#endif

#ifndef ULONG_PTR
typedef unsigned long ULONG_PTR;
#endif

#ifndef SIZE_T
typedef ULONG_PTR SIZE_T;
#endif

#ifndef PSIZE_T
typedef SIZE_T *PSIZE_T;
#endif

#ifndef PULONG_PTR
typedef ULONG_PTR *PULONG_PTR;
#endif

#ifndef _LIST_ENTRY_DEFINED
#define _LIST_ENTRY_DEFINED
typedef struct _LIST_ENTRY {
   struct _LIST_ENTRY *Flink;
   struct _LIST_ENTRY *Blink;
} LIST_ENTRY, *PLIST_ENTRY;
#endif

#ifndef _OBJECT_ATTRIBUTES_DEFINED
#define _OBJECT_ATTRIBUTES_DEFINED
typedef struct _OBJECT_ATTRIBUTES OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;
#endif

#ifndef _GENERIC_MAPPING_DEFINED
#define _GENERIC_MAPPING_DEFINED
typedef struct _GENERIC_MAPPING {
   ULONG GenericRead;
   ULONG GenericWrite;
   ULONG GenericExecute;
   ULONG GenericAll;
} GENERIC_MAPPING, *PGENERIC_MAPPING;
#endif

#ifndef HANDLE
typedef void *HANDLE;
#endif

#ifndef PVOID
typedef void *PVOID;
#endif

#ifndef _UNICODE_STRING_DEFINED
#define _UNICODE_STRING_DEFINED
typedef struct _UNICODE_STRING {
   USHORT Length;
   USHORT MaximumLength;
   PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;
#endif

#ifndef PCUNICODE_STRING
typedef const UNICODE_STRING *PCUNICODE_STRING;
#endif

#ifndef _ANSI_STRING_DEFINED
#define _ANSI_STRING_DEFINED
typedef struct _STRING {
   USHORT Length;
   USHORT MaximumLength;
   PCHAR Buffer;
} STRING, *PSTRING;
#endif

#ifndef PSRING
typedef PSTRING PSRING;
#endif

#ifndef PANSI_STRING
typedef PSTRING PANSI_STRING;
#endif

#ifndef PULONGLONG
typedef unsigned long long *PULONGLONG;
#endif

#ifndef PUINT
typedef UINT *PUINT;
#endif

#ifndef COLORREF
typedef DWORD COLORREF;
#endif

#ifndef _ACL_DEFINED
#define _ACL_DEFINED
typedef struct _ACL {
   UCHAR AclRevision;
   UCHAR Sbz1;
   USHORT AclSize;
   USHORT AceCount;
   USHORT Sbz2;
} ACL, *PACL;
#endif

#ifndef UUID
typedef GUID UUID;
typedef UUID *PUUID;
typedef const UUID *PCUUID;
#endif
#ifndef _POINT_DEFINED
#define _POINT_DEFINED
typedef struct tagPOINT {
   LONG x;
   LONG y;
} POINT, *PPOINT;
#endif

#ifndef _NMHDR_DEFINED
#define _NMHDR_DEFINED
typedef struct tagNMHDR {
   HWND hwndFrom;
   UINT idFrom;
   UINT code;
} NMHDR, *PNMHDR;
#endif
#ifndef _RECT_DEFINED
#define _RECT_DEFINED
typedef struct tagRECT {
   LONG left;
   LONG top;
   LONG right;
   LONG bottom;
} RECT, *PRECT, *LPRECT;
#endif

#ifndef _SYSTEMTIME_DEFINED
#define _SYSTEMTIME_DEFINED
typedef struct tagSYSTEMTIME {
   WORD wYear;
   WORD wMonth;
   WORD wDayOfWeek;
   WORD wDay;
   WORD wHour;
   WORD wMinute;
   WORD wSecond;
   WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;
#endif

#ifndef _WINDOWPOS_DEFINED
#define _WINDOWPOS_DEFINED
typedef struct tagWINDOWPOS {
   HWND hwnd;
   HWND hwndInsertAfter;
   int x;
   int y;
   int cx;
   int cy;
   UINT flags;
} WINDOWPOS, *LPWINDOWPOS;
#endif

#ifndef _HBITMAP_DEFINED
#define _HBITMAP_DEFINED
typedef HANDLE HBITMAP;
#endif

#ifndef _DLGTEMPLATE_DEFINED
#define _DLGTEMPLATE_DEFINED
typedef struct tagDLGTEMPLATE DLGTEMPLATE, *PDLGTEMPLATE;
typedef const DLGTEMPLATE *LPCDLGTEMPLATE;
#endif

#ifndef _DLGPROC_DEFINED
#define _DLGPROC_DEFINED
typedef INT_PTR (CALLBACK *DLGPROC)(HWND, UINT, WPARAM, LPARAM);
#endif

#ifndef _LPSTREAM_DEFINED
#define _LPSTREAM_DEFINED
typedef void *LPSTREAM;
#endif

#ifndef _SCROLLINFO_DEFINED
#define _SCROLLINFO_DEFINED
typedef struct tagSCROLLINFO {
   UINT cbSize;
   UINT fMask;
   int nMin;
   int nMax;
   UINT nPage;
   int nPos;
   int nTrackPos;
} SCROLLINFO, *LPSCROLLINFO;
#endif
#else
/* If some Windows header guard macros are already present we may have
   skipped the full compatibility block above. Provide a small set of
   guarded fallbacks so downstream headers like commctrl.h can parse. */
#ifndef PUINT
typedef unsigned int *PUINT;
#endif

#ifndef COLORREF
typedef unsigned long COLORREF;
#endif

#ifndef _POINT_DEFINED
#define _POINT_DEFINED
typedef struct tagPOINT { LONG x; LONG y; } POINT, *PPOINT;
#endif

#ifndef _NMHDR_DEFINED
#define _NMHDR_DEFINED
typedef struct tagNMHDR { HWND hwndFrom; UINT idFrom; UINT code; } NMHDR, *PNMHDR;
#endif

#ifndef _RECT_DEFINED
#define _RECT_DEFINED
typedef struct tagRECT { LONG left; LONG top; LONG right; LONG bottom; } RECT, *PRECT, *LPRECT;
#endif

#ifndef _SYSTEMTIME_DEFINED
#define _SYSTEMTIME_DEFINED
typedef struct tagSYSTEMTIME { WORD wYear; WORD wMonth; WORD wDayOfWeek; WORD wDay; WORD wHour; WORD wMinute; WORD wSecond; WORD wMilliseconds; } SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;
#endif

#ifndef _WINDOWPOS_DEFINED
#define _WINDOWPOS_DEFINED
typedef struct tagWINDOWPOS { HWND hwnd; HWND hwndInsertAfter; int x; int y; int cx; int cy; UINT flags; } WINDOWPOS, *LPWINDOWPOS;
#endif

#ifndef _DLGTEMPLATE_DEFINED
#define _DLGTEMPLATE_DEFINED
typedef struct tagDLGTEMPLATE DLGTEMPLATE, *PDLGTEMPLATE;
typedef const DLGTEMPLATE *LPCDLGTEMPLATE;
#endif

#ifndef _DLGPROC_DEFINED
#define _DLGPROC_DEFINED
typedef INT_PTR (CALLBACK *DLGPROC)(HWND, UINT, WPARAM, LPARAM);
#endif

#ifndef _LPSTREAM_DEFINED
#define _LPSTREAM_DEFINED
typedef void *LPSTREAM;
#endif
#endif

/* Windows anonymous aggregate compatibility used across legacy headers. */
#ifndef _ANONYMOUS_UNION
#define _ANONYMOUS_UNION
#endif

#ifndef _ANONYMOUS_STRUCT
#define _ANONYMOUS_STRUCT
#endif

#ifndef NONAMELESSUNION
#define NONAMELESSUNION 1
#endif

#ifndef DUMMYUNIONNAME
#define DUMMYUNIONNAME u
#endif

#ifndef DUMMYUNIONNAME2
#define DUMMYUNIONNAME2 u2
#endif

#ifndef DUMMYUNIONNAME3
#define DUMMYUNIONNAME3 u3
#endif

#ifndef DUMMYSTRUCTNAME
#define DUMMYSTRUCTNAME s
#endif

#ifndef DUMMYSTRUCTNAME2
#define DUMMYSTRUCTNAME2 s2
#endif

#ifndef DUMMYSTRUCTNAME3
#define DUMMYSTRUCTNAME3 s3
#endif

#if !defined(_WINDEF_H) && !defined(_WINNT_H) && !defined(_WINNT_) && \
    !defined(WINDOWS_H) && !defined(_INC_WINDOWS)
/* Forward declarations used by dbghelp and related headers on non-Windows hosts. */
typedef struct _CONTEXT CONTEXT;
typedef CONTEXT *PCONTEXT;
typedef PCONTEXT LPCONTEXT;

/* SID type declarations for security/ACL headers that depend on winnt symbols. */
typedef struct _SID SID;
typedef SID *PISID;
typedef SID *PSID;
#ifndef __ITransaction_FWD_DEFINED__
#define __ITransaction_FWD_DEFINED__
typedef struct ITransaction ITransaction;
#endif
#ifndef LPDIRECTDRAW
typedef struct IDirectDraw *LPDIRECTDRAW;
#endif

#ifndef HACCEL
typedef HANDLE HACCEL;
#endif
#endif

#if !defined(LPDIRECTDRAW) || !defined(HACCEL)
/* Ensure common typedefs are available as a final fallback. */
#ifndef LPDIRECTDRAW
typedef struct IDirectDraw *LPDIRECTDRAW;
#endif
#ifndef HACCEL
typedef HANDLE HACCEL;
#endif
#endif

/* Normalize COM interface macros to C-style declarations after include order
   so headers that use extern "C" + DECLARE_INTERFACE_ parse consistently. */
#ifdef DECLARE_INTERFACE_
#undef DECLARE_INTERFACE_
#endif
#ifdef DECLARE_INTERFACE
#undef DECLARE_INTERFACE
#endif
#ifdef STDMETHOD
#undef STDMETHOD
#endif
#ifdef STDMETHOD_
#undef STDMETHOD_
#endif
#ifdef STDMETHODV
#undef STDMETHODV
#endif
#ifdef STDMETHODV_
#undef STDMETHODV_
#endif
#ifdef THIS_
#undef THIS_
#endif
#ifdef THIS
#undef THIS
#endif
#ifdef PURE
#undef PURE
#endif

#ifndef interface
#define interface struct
#endif
#ifndef PURE
#define PURE
#endif
#ifndef THIS_
#define THIS_ INTERFACE * This,
#endif
#ifndef THIS
#define THIS INTERFACE * This
#endif
#ifndef STDMETHODVCALLTYPE
#define STDMETHODVCALLTYPE __cdecl
#endif
#ifndef STDMETHOD
#define STDMETHOD(method) HRESULT (__stdcall * method)
#endif
#ifndef STDMETHOD_
#define STDMETHOD_(type, method) type (__stdcall * method)
#endif
#ifndef STDMETHODV
#define STDMETHODV(method) HRESULT (STDMETHODVCALLTYPE * method)
#endif
#ifndef STDMETHODV_
#define STDMETHODV_(type, method) type (STDMETHODVCALLTYPE * method)
#endif
#ifndef BEGIN_INTERFACE
#define BEGIN_INTERFACE
#endif
#ifndef END_INTERFACE
#define END_INTERFACE
#endif
#ifndef DECLARE_INTERFACE
#define DECLARE_INTERFACE(iface)                                              \
   typedef interface iface {                                                  \
      struct iface##Vtbl * lpVtbl;                                            \
   } iface;                                                                   \
   typedef struct iface##Vtbl iface##Vtbl;                                    \
   struct iface##Vtbl
#endif
#ifndef DECLARE_INTERFACE_
#define DECLARE_INTERFACE_(iface, baseiface) DECLARE_INTERFACE(iface)
#endif

#endif /* WINDOWS_WIN32DEFS_H */

/* Minimal SLIST/SINGLE_LIST fallbacks so headers using SLIST types
   (e.g. winbase.h) can be parsed even when full winnt.h hasn't been
   included. These are conservative placeholders for IntelliSense. */
#ifndef _SINGLE_LIST_ENTRY_DEFINED
#define _SINGLE_LIST_ENTRY_DEFINED
typedef struct _SINGLE_LIST_ENTRY {
   struct _SINGLE_LIST_ENTRY *Next;
} SINGLE_LIST_ENTRY, *PSINGLE_LIST_ENTRY;
#endif

#ifndef _SLIST_HEADER_DEFINED
#define _SLIST_HEADER_DEFINED
typedef struct _SLIST_HEADER {
   SINGLE_LIST_ENTRY Next;
} SLIST_HEADER, *PSLIST_HEADER;
#endif

#ifndef SLIST_ENTRY
#define SLIST_ENTRY SINGLE_LIST_ENTRY
#endif
#ifndef PSLIST_ENTRY
#define PSLIST_ENTRY PSINGLE_LIST_ENTRY
#endif
