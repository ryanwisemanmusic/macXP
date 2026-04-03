/*
 * gdiplusbase.h
 *
 * GDI+ base class
 *
 * This file is part of the w32api package.
 *
 * Contributors:
 *   Created by Markus Koenig <markus@stber-koenig.de>
 *
 * THIS SOFTWARE IS NOT COPYRIGHTED
 *
 * This source code is offered for use in the public domain. You may
 * use, modify or distribute it freely.
 *
 * This code is distributed in the hope that it will be useful but
 * WITHOUT ANY WARRANTY. ALL WARRANTIES, EXPRESS OR IMPLIED ARE HEREBY
 * DISCLAIMED. This includes but is not limited to warranties of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef __GDIPLUS_BASE_H
#define __GDIPLUS_BASE_H
#if __GNUC__ >=3
#pragma GCC system_header
#endif

#ifndef __cplusplus
#error "A C++ compiler is required to include gdiplusbase.h."
#endif

#include "gdiplus_defs.h"
/* Ensure `size_t` is available for operator new; some toolchains
	require <cstddef> in C++ mode. Also forward-declare the minimal
	DllExports allocation routines so `DllExports::GdipAlloc`/`GdipFree`
	can be referenced here before the full flat API declarations appear
	later in the headers. */
#ifdef __cplusplus
#include <cstddef>
#include <cstdlib>
using std::size_t;
namespace DllExports {
inline void* GdipAlloc(size_t size) { return std::malloc(size); }
inline void GdipFree(void *mem) { std::free(mem); }
}
#endif

class GdiplusBase
{
public:
	static void* operator new(size_t in_size)
	{
		return DllExports::GdipAlloc(in_size);
	}
	static void* operator new[](size_t in_size)
	{
		return DllExports::GdipAlloc(in_size);
	}
	static void operator delete(void *in_pVoid)
	{
		DllExports::GdipFree(in_pVoid);
	}
	static void operator delete[](void *in_pVoid)
	{
		DllExports::GdipFree(in_pVoid);
	}
};

#endif /* __GDIPLUS_BASE_H */
