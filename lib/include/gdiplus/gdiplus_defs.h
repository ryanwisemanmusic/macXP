// Contributor: Ryan Wiseman <ryanwisemanmusic@gmail.com>

/* 
These are the required definitions needed for gdiplus to be macOS compliant
on ARM64. This is one of the most intense libraries in terms of how much
code was required to make this work. Essentially, the process was going through
each file one by one, sorting out said differences, and then making sure
my newest edits didn't break the file previously. 

Now, we use a defs file as a common point of checking whether or not things
conflict.

As a note, many of the functions you see in these headers have never been
defined. They do exist, but I do not care to source you on exactly how 
to find these original ones.

Also, our typedef structs often mean that if you want to invoke things 
related to lets say MatrixOrder, you will have to static cast. So, make
sure that you properly keep that in mind.
*/

#ifndef __GDIPLUS_DEFS_H
#define __GDIPLUS_DEFS_H

#include <stddef.h>
#ifdef __cplusplus
#include <new>
#endif

// WINGDIPAPI macro - unsure if this creates any conflicts so far but whatever
#ifndef WINGDIPAPI
#define WINGDIPAPI
#endif

// Additional types/aliases we need to define else the program hates us lol
#ifndef __GDIPLUS_BASIC_TYPES_DEFINED
#define __GDIPLUS_BASIC_TYPES_DEFINED
typedef int INT;
typedef float REAL; // GDI+ uses float for REAL
typedef int BOOL;
#endif

// Anything important required for GpStatus
#ifndef __GDIPLUS_GPSTATUS_DEFINED
#define __GDIPLUS_GPSTATUS_DEFINED
typedef enum GpStatus {
	Ok = 0,
	GenericError = 1,
	InvalidParameter = 2,
	OutOfMemory = 3,
	ObjectBusy = 4,
	InsufficientBuffer = 5,
	NotImplemented = 6
} GpStatus;
#endif

// Double check this that I haven't created a big problem
#ifndef FontFamilyNotFound
#define FontFamilyNotFound GenericError
#endif

#ifdef __cplusplus
typedef GpStatus Status;
#endif

#ifndef __GDIPLUS_BRUSHTYPE_DEFINED
#define __GDIPLUS_BRUSHTYPE_DEFINED
typedef enum BrushType {
	BrushTypeSolidColor = 0,
	BrushTypeHatch = 1,
	BrushTypeTexture = 2
} BrushType;
#endif

#ifndef __GDIPLUS_ARGB_DEFINED
#define __GDIPLUS_ARGB_DEFINED
typedef unsigned int ARGB;
#endif

#ifndef __GDIPLUS_COLOR_FALLBACK_DEFINED
#define __GDIPLUS_COLOR_FALLBACK_DEFINED

// Feel free to modify these if needed given I've yet to majorly test this library
struct Color {
	ARGB Value;
	Color(): Value(0) {}
	Color(ARGB v): Value(v) {}
	ARGB GetValue() const { return Value; }
	void SetValue(ARGB v) { Value = v; }
};
#endif

#ifndef __GDIPLUS_BRUSH_FWD_DEFINED
#define __GDIPLUS_BRUSH_FWD_DEFINED
typedef struct GpBrush GpBrush;
typedef struct GpBrush GpHatch;
#endif

#ifndef __GDIPLUS_COMMON_FORWARD_TYPES
#define __GDIPLUS_COMMON_FORWARD_TYPES

typedef struct GpBitmap GpBitmap;
typedef struct GpGraphics GpGraphics;
typedef struct GpCustomLineCap GpAdjustableArrowCap;
typedef unsigned int PixelFormat;

// I cannot tell you if this Assembly address is correct. 
// Treat this as a placeholder and source the true address yourself if needed
#ifndef PixelFormat32bppARGB
#define PixelFormat32bppARGB 0x26200A
#endif

typedef struct GpPen GpPen;
typedef struct GpPath GpPath;
typedef struct GpRegion GpRegion;
typedef struct IStream IStream;
typedef struct WmfPlaceableFileHeader WmfPlaceableFileHeader;
typedef struct GpPathGradient GpPathGradient;
typedef struct GpPathIterator GpPathIterator;

typedef struct GpCustomLineCap GpCustomLineCap;
#ifndef __GDIPLUS_LINECAP_DEFINED
#define __GDIPLUS_LINECAP_DEFINED

#ifdef __cplusplus
typedef enum LineCap GpLineCap;
#else
typedef enum GpLineCap {
	LineCapFlat = 0,
	LineCapSquare = 1,
	LineCapRound = 2
} GpLineCap;
#endif
#endif

// Important for DirectDraw, creates the fast-foward needed
#ifndef __IDIRECTDRAW_SURFACE7_FWD_DEFINED
#define __IDIRECTDRAW_SURFACE7_FWD_DEFINED
typedef struct IDirectDrawSurface7 IDirectDrawSurface7;
#endif

// You can change these if needed, esp if you are doing error checking
#ifndef __GDIPLUS_DASHSTYLE_DEFINED
#define __GDIPLUS_DASHSTYLE_DEFINED
typedef enum GpDashStyle {
	DashStyleSolid = 0,
	DashStyleDash = 1,
	DashStyleDot = 2,
	DashStyleDashDot = 3,
	DashStyleDashDotDot = 4
} GpDashStyle;
#endif


typedef struct GpMetafile GpMetafile;
typedef struct GpStringFormat GpStringFormat;
typedef int (*EnumerateMetafileProc)(void*);
typedef int (*DrawImageAbort)(void*);
#endif

#ifndef __GDIPLUS_FLAT_HELPERS_DEFINED
#define __GDIPLUS_FLAT_HELPERS_DEFINED
// If this is not const then it's Microsoft's own fuckery in action
#ifndef GDIPCONST
#define GDIPCONST const
#endif

// Ah yes recurive defining
typedef struct BitmapData BitmapData;

typedef enum DitherType { DitherTypeNone = 0 } DitherType;
typedef enum PaletteType { PaletteTypeCustom = 0 } PaletteType;

typedef struct ColorPalette {
	 INT Flags;
	 INT Count;
	 ARGB *Entries;
} ColorPalette;

typedef struct CGpEffect CGpEffect;
typedef struct GpCachedBitmap GpCachedBitmap;
#endif

#ifndef __GDIPLUS_ADDITIONAL_FORWARD_TYPES
#define __GDIPLUS_ADDITIONAL_FORWARD_TYPES
typedef struct GpRect GpRect;
typedef struct GpRectF GpRectF;
typedef struct GpFont GpFont;
typedef struct GpFontFamily GpFontFamily;
typedef struct GpFontCollection GpFontCollection;

// May need changing to different values. If something is off when
// you reference this, consult things here
typedef enum Unit {
	UnitWorld = 0,
	UnitPixel = 2,
	UnitPoint = 3,
	UnitInch = 4
} Unit;

#ifndef __GDIPLUS_GPUNIT_DEFINED
#define __GDIPLUS_GPUNIT_DEFINED
typedef Unit GpUnit;
#endif

typedef enum GpFlushIntention {
	GpFlushIntentionFlush = 0
} GpFlushIntention;

typedef int (*GdiplusAbort)(void*);

typedef enum GpCoordinateSpace {
	CoordinateSpaceWorld = 0,
	CoordinateSpacePage = 1,
	CoordinateSpaceDevice = 2
} GpCoordinateSpace;

#ifndef __GDIPLUS_FILLMODE_DEFINED
#define __GDIPLUS_FILLMODE_DEFINED
#ifdef __cplusplus
typedef enum FillMode {
	FillModeAlternate = 0,
	FillModeWinding = 1
} FillMode;
typedef FillMode GpFillMode;
#else
typedef enum GpFillMode {
	FillModeAlternate = 0,
	FillModeWinding = 1
} GpFillMode;
#endif
#endif
#endif

#ifndef __GDIPLUS_HATCHSTYLE_DEFINED
#define __GDIPLUS_HATCHSTYLE_DEFINED
typedef enum HatchStyle {
	HatchStyleHorizontal = 0,
	HatchStyleVertical = 1,
	HatchStyleForwardDiagonal = 2
} HatchStyle;
#endif

#ifndef __GDIPLUS_ENUM_ALIASES_DEFINED
#define __GDIPLUS_ENUM_ALIASES_DEFINED
typedef HatchStyle GpHatchStyle;
typedef BrushType GpBrushType;
typedef WrapMode GpWrapMode;
#endif

#ifndef __GDIPLUS_POINT_TYPES_DEFINED
#define __GDIPLUS_POINT_TYPES_DEFINED

// This could be the biggest point of conflict:
// you can modify this to lowercase x and y if needbe
typedef struct Point { INT X; INT Y; } Point;
#ifdef __cplusplus
class PointF {
public:
	REAL X; REAL Y;
	PointF(): X(0.0f), Y(0.0f) {}
	PointF(REAL x, REAL y): X(x), Y(y) {}
};
#else
typedef struct PointF { REAL X; REAL Y; } PointF;
#endif
#ifdef __cplusplus
class Size {
public:
	INT Width; INT Height;
	Size(): Width(0), Height(0) {}
	Size(INT w, INT h): Width(w), Height(h) {}
};
class SizeF {
public:
	REAL Width; REAL Height;
	SizeF(): Width(0.0f), Height(0.0f) {}
	SizeF(REAL w, REAL h): Width(w), Height(h) {}
};
#else
typedef struct Size { INT Width; INT Height; } Size;
typedef struct SizeF { REAL Width; REAL Height; } SizeF;
#endif

typedef Point GpPoint;
typedef PointF GpPointF;
typedef Size GpSize;
typedef SizeF GpSizeF;
#endif

#ifndef __GDIPLUS_RECTS_F_DEFINED
#define __GDIPLUS_RECTS_F_DEFINED
#ifdef __cplusplus

// Please make sure this class isn't fucking you over if things go wrong here.
// Remember, when it comes to trying to replicate anything Win32 API, unless
// you are able to check under the hood regarding the processes, it is a shot
// in the dark
class RectF {
public:
	REAL X; REAL Y; REAL Width; REAL Height;
	RectF(): X(0.0f), Y(0.0f), Width(0.0f), Height(0.0f) {}
	RectF(REAL x, REAL y, REAL w, REAL h): X(x), Y(y), Width(w), Height(h) {}
	RectF(const PointF &p, const SizeF &s): X(p.X), Y(p.Y), Width(s.Width), Height(s.Height) {}
	void GetSize(SizeF *out) const { if (out) { out->Width = Width; out->Height = Height; } }
};
#else
typedef struct RectF { REAL X; REAL Y; REAL Width; REAL Height; } RectF;
#endif
#endif

#ifndef __GDIPLUS_LINEARGRADIENTMODE_DEFINED
#define __GDIPLUS_LINEARGRADIENTMODE_DEFINED
typedef enum LinearGradientMode {
	LinearGradientModeHorizontal = 0,
	LinearGradientModeVertical = 1,
	LinearGradientModeForwardDiagonal = 2,
	LinearGradientModeBackwardDiagonal = 3
} LinearGradientMode;
#endif

#ifndef __GDIPLUS_RECT_DEFINED
#define __GDIPLUS_RECT_DEFINED
#ifdef __cplusplus
class Rect {
public:
	INT X; INT Y; INT Width; INT Height;
	Rect(): X(0), Y(0), Width(0), Height(0) {}
	Rect(INT x, INT y, INT w, INT h): X(x), Y(y), Width(w), Height(h) {}
	Rect(const Point &p, const Size &s): X(p.X), Y(p.Y), Width(s.Width), Height(s.Height) {}
};
#else
typedef struct Rect { INT X; INT Y; INT Width; INT Height; } Rect;
#endif
#endif

#ifndef __GDIPLUS_RECT_ALIASES_DEFINED
#define __GDIPLUS_RECT_ALIASES_DEFINED
typedef Rect GpRect;
typedef RectF GpRectF;
#endif

#ifndef __GDIPLUS_WRAPMODE_DEFINED
#define __GDIPLUS_WRAPMODE_DEFINED
typedef enum WrapMode {
	WrapModeTile = 0,
	WrapModeTileFlipX = 1,
	WrapModeTileFlipY = 2,
	WrapModeTileFlipXY = 3
} WrapMode;
#endif

#ifndef __GDIPLUS_GPLINEGRADIENT_DEFINED
#define __GDIPLUS_GPLINEGRADIENT_DEFINED
typedef struct GpBrush GpLineGradient;
#endif

#ifndef __GDIPLUS_GPMATRIX_DEFINED
#define __GDIPLUS_GPMATRIX_DEFINED
typedef struct GpMatrix GpMatrix;
#endif

#ifdef __cplusplus
#ifndef __GDIPLUS_MATRIX_WRAPPER_DEFINED
#define __GDIPLUS_MATRIX_WRAPPER_DEFINED
typedef enum MatrixOrder {
	MatrixOrderPrepend = 0,
	MatrixOrderAppend = 1
} MatrixOrder;

class Matrix {
public:
	GpMatrix *nativeMatrix;
	Matrix(): nativeMatrix(NULL) {}
};
#endif
#endif

// MatrixOrder prefers GpMatrixOrder in cases
// In environments where you envoke stuff related to this, you may be
// required to static cast directly to this GpMatrix Order
#ifndef __GDIPLUS_GPMATRIXORDER_DEFINED
#define __GDIPLUS_GPMATRIXORDER_DEFINED
typedef MatrixOrder GpMatrixOrder;
#endif

// Same situation as comment above
#ifndef __GDIPLUS_CONCRETE_TYPES_DEFINED
#define __GDIPLUS_CONCRETE_TYPES_DEFINED
typedef struct GpBrush GpSolidFill;
typedef struct GpBrush GpTexture;
typedef struct GpImage GpImage;
#endif

/* Minimal Image wrapper used by TextureBrush */
#ifdef __cplusplus
#ifndef __GDIPLUS_IMAGE_WRAPPER_DEFINED
#define __GDIPLUS_IMAGE_WRAPPER_DEFINED
class Image {
public:
	GpImage *nativeImage;
	mutable Status lastStatus;

	Image(): nativeImage(NULL), lastStatus(Ok) {}
	Image(GpImage *img, Status status): nativeImage(img), lastStatus(status) {}
	virtual ~Image() {}

	Status updateStatus(Status newStatus) const
	{
		if (newStatus != Ok) lastStatus = newStatus;
		return newStatus;
	}

	Status GetLastStatus() const
	{
		Status result = lastStatus;
		lastStatus = Ok;
		return result;
	}
};
#endif

#ifndef __GDIPLUS_IMAGEATTR_DEFINED
#define __GDIPLUS_IMAGEATTR_DEFINED
typedef struct GpImageAttributes GpImageAttributes;
#ifdef __cplusplus
class ImageAttributes {
public:
	GpImageAttributes *nativeImageAttributes;
	ImageAttributes(): nativeImageAttributes(NULL) {}
};
#endif
#endif
#endif

#ifdef __cplusplus

#ifndef __GDIPLUS_BASE_DEFINED
#define __GDIPLUS_BASE_DEFINED
class GdiplusBase {
public:
	virtual ~GdiplusBase() {}
protected:
	GdiplusBase() {}
};
#endif

// Checking my work, is your friend
#ifndef __GDIPLUS_WRAPPER_CLASS_FORWARDS
#define __GDIPLUS_WRAPPER_CLASS_FORWARDS
class Pen { public: GpPen *nativePen; Pen(): nativePen(NULL) {} };
class CachedBitmap { public: GpCachedBitmap *nativeCachedBitmap; CachedBitmap(): nativeCachedBitmap(NULL) {} };
class Graphics { public: GpGraphics *nativeGraphics; Graphics(): nativeGraphics(NULL) {} };
class Brush {
public:
	GpBrush *nativeBrush;
	mutable Status lastStatus;

	Brush(): nativeBrush(NULL), lastStatus(Ok) {}
	Brush(GpBrush *b, Status status): nativeBrush(b), lastStatus(status) {}
	virtual ~Brush() { DllExports::GdipDeleteBrush(nativeBrush); }

	Status updateStatus(Status newStatus) const
	{
		if (newStatus != Ok) lastStatus = newStatus;
		return newStatus;
	}
	Status GetLastStatus() const
	{
		Status result = lastStatus;
		lastStatus = Ok;
		return result;
	}
};

class GraphicsPath { public: GpPath *nativePath; GraphicsPath(): nativePath(NULL), lastStatus(Ok) {}
	Status updateStatus(Status newStatus) const
	{
		if (newStatus != Ok) lastStatus = newStatus;
		return newStatus;
	}
	__inline__ BOOL IsVisible(const Point &point, const Graphics *g) const;
	__inline__ BOOL IsOutlineVisible(REAL x, REAL y, const Pen *pen, const Graphics *g) const;
	__inline__ BOOL IsOutlineVisible(INT x, INT y, const Pen *pen, const Graphics *g) const;
	__inline__ BOOL IsOutlineVisible(const PointF &point, const Pen *pen, const Graphics *g) const;
	__inline__ BOOL IsOutlineVisible(const Point &point, const Pen *pen, const Graphics *g) const;
	__inline__ BOOL IsVisible(REAL x, REAL y, const Graphics *g) const;
	__inline__ BOOL IsVisible(INT x, INT y, const Graphics *g) const;
	__inline__ BOOL IsVisible(const PointF &point, const Graphics *g) const;
private:
	mutable Status lastStatus;
};

// Substantiating what I think PathData could contain. It's enough to make
// Intellisense shut the fuck up
class PathData {
public:
	INT Count;
	PointF *Points;
	BYTE *Types;
	PathData(): Count(0), Points(NULL), Types(NULL) {}
	__inline__ Status AllocateArrays(INT capacity);
	__inline__ VOID FreeArrays();
};

class CustomLineCap {
public:
	// Your ass cannot reference LineCap here or else Intellisense cries
	// Do NOT even try
	CustomLineCap(): nativeCustomLineCap(NULL), lastStatus(Ok) {}
	CustomLineCap(GpCustomLineCap *customLineCap, Status status):
		nativeCustomLineCap(customLineCap), lastStatus(status) {}
	virtual ~CustomLineCap() { DllExports::GdipDeleteCustomLineCap(nativeCustomLineCap); }

	Status updateStatus(Status newStatus) const
	{
		if (newStatus != Ok) lastStatus = newStatus;
		return newStatus;
	}

	GpCustomLineCap *nativeCustomLineCap;
	mutable Status lastStatus;
};

class Font { public: GpFont *nativeFont; Font(): nativeFont(NULL) {} };
class StringFormat { public: GpStringFormat *nativeStringFormat; StringFormat(): nativeStringFormat(NULL) {} };
class Metafile { public: GpMetafile *nativeImage; Metafile(): nativeImage(NULL) {} };
class Region { public: GpRegion *nativeRegion; Region(): nativeRegion(NULL) {} };
#endif
#endif

#ifndef __GDIPLUS_IMAGE_META_PLACEHOLDERS
#define __GDIPLUS_IMAGE_META_PLACEHOLDERS

// Basic types
#ifndef UINT
typedef unsigned int UINT;
#endif
#ifndef BYTE
typedef unsigned char BYTE;
#endif
#ifndef PROPID
typedef unsigned int PROPID;
#endif

typedef enum GpLineJoin {
	GpLineJoinMiter = 0,
	GpLineJoinBevel = 1,
	GpLineJoinRound = 2
} GpLineJoin;

typedef struct GpPathData {
	INT Count;
	PointF *Points;
	BYTE *Types;
} GpPathData;

typedef enum GpDashCap {
	GpDashCapFlat = 0,
	GpDashCapRound = 1,
	GpDashCapTriangle = 2
} GpDashCap;

typedef enum GpPenAlignment {
	GpPenAlignmentCenter = 0,
	GpPenAlignmentInset = 1
} GpPenAlignment;

typedef enum GpPenType {
	GpPenTypeUnknown = 0,
	GpPenTypeSolidColor = 1,
	GpPenTypeHatchFill = 2,
	GpPenTypeTextureFill = 3,
	GpPenTypePathGradient = 4
} GpPenType;

typedef struct CharacterRange { INT First; INT Length; } CharacterRange;

typedef struct EncoderParameters { UINT Count; void *Param; } EncoderParameters;
typedef int (*GetThumbnailImageAbort)(void*);
typedef void (*DebugEventProc)(const WCHAR *message);
typedef enum RotateFlipType { RotateNoneFlipNone = 0, Rotate90FlipNone = 1 } RotateFlipType;
typedef struct PropertyItem { PROPID id; UINT length; void *value; } PropertyItem;
typedef struct ImageItemData { UINT id; UINT size; void *data; } ImageItemData;
typedef struct ImageCodecInfo ImageCodecInfo;
typedef struct MetafileHeader MetafileHeader;

#endif

// All the exhaustive DLL related code that is required. 
// There is SO MUCH required for the gdiplus library
// Given that also macOS uses .exp, there may need to be a bridge written
#ifdef __cplusplus
#ifndef __GDIPLUS_DLL_EXPORTS_STUBS
#define __GDIPLUS_DLL_EXPORTS_STUBS
namespace DllExports { extern "C" {
inline GpStatus GdipDeleteBrush(GpBrush*) { return Ok; }
inline GpStatus GdipGetBrushType(GpBrush* /*brush*/, BrushType* bt) { if (bt) *bt = BrushTypeSolidColor; return Ok; }
inline GpStatus GdipCreateHatchBrush(HatchStyle /*style*/, ARGB /*fg*/, ARGB /*bg*/, GpHatch** /*out*/) { return NotImplemented; }
inline GpStatus GdipCloneBrush(GpBrush* /*brush*/, GpBrush** /*out*/) { return NotImplemented; }
inline GpStatus GdipGetHatchBackgroundColor(GpHatch* /*hatch*/, ARGB* /*out*/) { return NotImplemented; }
inline GpStatus GdipGetHatchStyle(GpHatch* /*hatch*/, HatchStyle* /*out*/) { return NotImplemented; }
inline GpStatus GdipCreateLineBrush(const PointF* /*p1*/, const PointF* /*p2*/, ARGB /*c1*/, ARGB /*c2*/, WrapMode /*w*/, GpLineGradient** /*out*/) { return NotImplemented; }
inline GpStatus GdipCreateLineBrushI(const Point* /*p1*/, const Point* /*p2*/, ARGB /*c1*/, ARGB /*c2*/, WrapMode /*w*/, GpLineGradient** /*out*/) { return NotImplemented; }
inline GpStatus GdipGetHatchForegroundColor(GpHatch* /*hatch*/, ARGB* /*out*/) { return NotImplemented; }

inline GpStatus GdipCreateLineBrushFromRect(const RectF* /*rect*/, ARGB /*c1*/, ARGB /*c2*/, int /*mode*/, WrapMode /*w*/, GpLineGradient** /*out*/) { return NotImplemented; }
inline GpStatus GdipCreateLineBrushFromRectI(const Rect* /*rect*/, ARGB /*c1*/, ARGB /*c2*/, int /*mode*/, WrapMode /*w*/, GpLineGradient** /*out*/) { return NotImplemented; }
inline GpStatus GdipCreateLineBrushFromRectWithAngle(const RectF* /*rect*/, ARGB /*c1*/, ARGB /*c2*/, REAL /*angle*/, BOOL /*scalable*/, WrapMode /*w*/, GpLineGradient** /*out*/) { return NotImplemented; }
inline GpStatus GdipCreateLineBrushFromRectWithAngleI(const Rect* /*rect*/, ARGB /*c1*/, ARGB /*c2*/, REAL /*angle*/, BOOL /*scalable*/, WrapMode /*w*/, GpLineGradient** /*out*/) { return NotImplemented; }

inline GpStatus GdipGetLineBlend(GpLineGradient* /*g*/, REAL* /*blendFactors*/, REAL* /*blendPositions*/, INT /*count*/) { return NotImplemented; }
inline GpStatus GdipGetLineBlendCount(GpLineGradient* /*g*/, INT* /*count*/) { return NotImplemented; }
inline GpStatus GdipGetLineGammaCorrection(GpLineGradient* /*g*/, BOOL* /*useGamma*/) { return NotImplemented; }
inline GpStatus GdipGetLinePresetBlendCount(GpLineGradient* /*g*/, INT* /*count*/) { return NotImplemented; }
inline GpStatus GdipGetLineColors(GpLineGradient* /*g*/, ARGB* /*colors*/) { return NotImplemented; }
inline GpStatus GdipGetLineRect(GpLineGradient* /*g*/, RectF* /*rect*/) { return NotImplemented; }
inline GpStatus GdipGetLineRectI(GpLineGradient* /*g*/, Rect* /*rect*/) { return NotImplemented; }
inline GpStatus GdipGetLineTransform(GpLineGradient* /*g*/, GpMatrix* /*matrix*/) { return NotImplemented; }
inline GpStatus GdipGetLineWrapMode(GpLineGradient* /*g*/, WrapMode* /*mode*/) { return NotImplemented; }
inline GpStatus GdipGetLinePresetBlend(GpLineGradient* /*g*/, ARGB* /*presetArgb*/, REAL* /*blendPositions*/, INT /*count*/) { return NotImplemented; }
inline GpStatus GdipMultiplyLineTransform(GpLineGradient* /*g*/, GpMatrix* /*matrix*/, GpMatrixOrder /*order*/) { return NotImplemented; }
inline GpStatus GdipResetLineTransform(GpLineGradient* /*g*/) { return NotImplemented; }
inline GpStatus GdipRotateLineTransform(GpLineGradient* /*g*/, REAL /*angle*/, GpMatrixOrder /*order*/) { return NotImplemented; }
inline GpStatus GdipScaleLineTransform(GpLineGradient* /*g*/, REAL /*sx*/, REAL /*sy*/, GpMatrixOrder /*order*/) { return NotImplemented; }
inline GpStatus GdipSetLineBlend(GpLineGradient* /*g*/, const REAL* /*blendFactors*/, const REAL* /*blendPositions*/, INT /*count*/) { return NotImplemented; }
inline GpStatus GdipSetLineSigmaBlend(GpLineGradient* /*g*/, REAL /*focus*/, REAL /*scale*/) { return NotImplemented; }
inline GpStatus GdipSetLineLinearBlend(GpLineGradient* /*g*/, REAL /*focus*/, REAL /*scale*/) { return NotImplemented; }
inline GpStatus GdipSetLineGammaCorrection(GpLineGradient* /*g*/, BOOL /*useGamma*/) { return NotImplemented; }
inline GpStatus GdipSetLinePresetBlend(GpLineGradient* /*g*/, ARGB* /*presetArgb*/, const REAL* /*blendPositions*/, INT /*count*/) { return NotImplemented; }
inline GpStatus GdipSetLineColors(GpLineGradient* /*g*/, ARGB /*color1*/, ARGB /*color2*/) { return NotImplemented; }
inline GpStatus GdipSetLineTransform(GpLineGradient* /*g*/, GpMatrix* /*matrix*/) { return NotImplemented; }
inline GpStatus GdipSetLineWrapMode(GpLineGradient* /*g*/, WrapMode /*mode*/) { return NotImplemented; }
inline GpStatus GdipTranslateLineTransform(GpLineGradient* /*g*/, REAL /*dx*/, REAL /*dy*/, GpMatrixOrder /*order*/) { return NotImplemented; }

inline GpStatus GdipCreateSolidFill(ARGB /*color*/, GpSolidFill** /*out*/) { return NotImplemented; }
inline GpStatus GdipGetSolidFillColor(GpSolidFill* /*solid*/, ARGB* /*out*/) { return NotImplemented; }

inline GpStatus GdipDeleteCustomLineCap(GpCustomLineCap*) { return Ok; }

inline GpStatus GdipCreateTexture(GpImage* /*image*/, WrapMode /*wrapMode*/, GpTexture** /*out*/) { return NotImplemented; }
inline GpStatus GdipCreateTexture2(GpImage* /*image*/, WrapMode /*wrapMode*/, REAL /*dstX*/, REAL /*dstY*/, REAL /*dstWidth*/, REAL /*dstHeight*/, GpTexture** /*out*/) { return NotImplemented; }
inline GpStatus GdipCreateTexture2I(GpImage* /*image*/, WrapMode /*wrapMode*/, INT /*dstX*/, INT /*dstY*/, INT /*dstWidth*/, INT /*dstHeight*/, GpTexture** /*out*/) { return NotImplemented; }
inline GpStatus GdipCreateTextureIA(GpImage* /*image*/, GpImageAttributes* /*attr*/, REAL /*dstX*/, REAL /*dstY*/, REAL /*dstWidth*/, REAL /*dstHeight*/, GpTexture** /*out*/) { return NotImplemented; }
inline GpStatus GdipCreateTextureIAI(GpImage* /*image*/, GpImageAttributes* /*attr*/, INT /*dstX*/, INT /*dstY*/, INT /*dstWidth*/, INT /*dstHeight*/, GpTexture** /*out*/) { return NotImplemented; }
inline GpStatus GdipSetSolidFillColor(GpSolidFill* /*solid*/, ARGB /*color*/) { return NotImplemented; }

inline GpStatus GdipGetTextureTransform(GpTexture* /*texture*/, GpMatrix* /*matrix*/) { return NotImplemented; }
inline GpStatus GdipGetTextureWrapMode(GpTexture* /*texture*/, WrapMode* /*mode*/) { return NotImplemented; }
inline GpStatus GdipMultiplyTextureTransform(GpTexture* /*texture*/, GpMatrix* /*matrix*/, GpMatrixOrder /*order*/) { return NotImplemented; }
inline GpStatus GdipResetTextureTransform(GpTexture* /*texture*/) { return NotImplemented; }
inline GpStatus GdipRotateTextureTransform(GpTexture* /*texture*/, REAL /*angle*/, GpMatrixOrder /*order*/) { return NotImplemented; }
inline GpStatus GdipScaleTextureTransform(GpTexture* /*texture*/, REAL /*sx*/, REAL /*sy*/, GpMatrixOrder /*order*/) { return NotImplemented; }
inline GpStatus GdipSetTextureTransform(GpTexture* /*texture*/, GpMatrix* /*matrix*/) { return NotImplemented; }
inline GpStatus GdipSetTextureWrapMode(GpTexture* /*texture*/, WrapMode /*mode*/) { return NotImplemented; }
inline GpStatus GdipTranslateTextureTransform(GpTexture* /*texture*/, REAL /*dx*/, REAL /*dy*/, GpMatrixOrder /*order*/) { return NotImplemented; }
} /* extern "C" */
} /* namespace DllExports */
#endif
#endif

#endif /* __GDIPLUS_DEFS_H */

