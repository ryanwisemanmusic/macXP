#if defined(__APPLE__) && (defined(__aarch64__) || defined(__arm64__))
#ifndef WINDOWS_WIN32DEFS_H
#define WINDOWS_WIN32DEFS_H

/* Clang compatibility for MSVC-style calling convention and declspec tokens. */
#ifndef __stdcall
#define __stdcall
#endif

#ifndef __cdecl
#define __cdecl
#endif

#ifndef __forceinline
#define __forceinline inline
#endif

#ifndef __declspec
#define __declspec(x)
#endif

/* Use a dedicated compatibility selector because we are trying to run
   Windows IRT. So because of that, it's why we are making said choices */
#ifndef WIN32_COMPAT_64
#define WIN32_COMPAT_64 1
#endif

#ifndef WIN32_COMPAT_USE_GS
#define WIN32_COMPAT_USE_GS 1
#endif

#ifndef WINDOWS_BASE_H
#include "windows_base.h"
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

/* Forward declarations used by dbghelp and related headers on non-Windows hosts. */
typedef struct _CONTEXT CONTEXT;
typedef CONTEXT *PCONTEXT;
typedef PCONTEXT LPCONTEXT;

#endif /* WINDOWS_WIN32DEFS_H */
#endif

