#pragma once

#include "GEConfig.h"

#include <string>
#include <vector>

#define SAFE_DELETE(x) if (x != NULL) { delete x; x = NULL; }
#define SAFE_DELETE_ARRAY(x) if (x != NULL) { delete [] x; x = NULL; }

typedef std::string				CGEString;
typedef std::wstring			CGEStringW;
typedef std::vector<CGEString>	CGEStringVector;
typedef std::vector<CGEStringW>	CGEStringWVector;

uint32 GEHashString(const char* str);

uint32 GEHashString(const std::string& str);

// Math
#ifndef ABS
#define ABS(a)          (((a) > 0) ? (a) : -(a))
#endif

#ifndef MAX
#define MAX(a, b)       (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b)       (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX3
#define MAX3(a, b, c)   (((a) > (b)) ? MAX(a,c) : MAX(b,c))
#endif

#ifndef MIN3
#define MIN3(a, b, c)   (((a) < (b)) ? MIN(a,c) : MIN(b,c))
#endif

uint32 GEGetScreenWidth();
uint32 GEGetScreenHeight();

/**
* Horizontal alignment values.
*/
enum GEFontAlignHor
{
	GE_FONT_ALIGN_LEFT,      //!< Text will be justified against the left-hand side of the rect
	GE_FONT_ALIGN_CENTRE,    //!< Text will be centred horizontally in the rect
	GE_FONT_ALIGN_RIGHT,     //!< Text will be justified against the right-hand side of the rect
	GE_FONT_ALIGN_PARAGRAPH, //!< Text alignment set by localisation settings (Left or Right alignment)
};

/**
* Vertical alignment values.
*/
enum GEFontAlignVer
{
	GE_FONT_ALIGN_TOP,       //!< Text will be positioned against the top of the rect
	GE_FONT_ALIGN_MIDDLE,    //!< Text will be centred vertically in the rect
	GE_FONT_ALIGN_BOTTOM,    //!< Text will be positioned against the bottom of the rect
};


#define printOpenGLError() printOglError(__FILE__,__LINE__)


typedef enum {
	EVertexShader,
	EFragmentShader,
} ShaderType;
