
/*================================================================================
GenericPlatform.h: Generic platform classes, mostly implemented with ANSI C++
==================================================================================*/
#pragma once


#ifdef __GNUC__
#define GE_ALIGNED(X) __attribute__ ((aligned (X)))
#define GE_PACKED(X) X __attribute__ ((packed))
#elif __ARMCC_VERSION
#define GE_ALIGNED(X) __align(X)
#define GE_PACKED(X) __packed X
#else
// VC 2005 supports this: #define IW_ALIGNED(X) __declspec(align(X))
#define GE_ALIGNED(X)
#define GE_PACKED(X) X
#endif

//---------------------------------------------------------------------
// Utility for automatically setting up the pointer-sized integer type
//---------------------------------------------------------------------

template<typename T32BITS, typename T64BITS, int PointerSize>
struct SelectIntPointerType
{
	// nothing here are is it an error if the partial specializations fail
};

template<typename T32BITS, typename T64BITS>
struct SelectIntPointerType < T32BITS, T64BITS, 8 >
{
	typedef T64BITS TIntPointer; // select the 64 bit type
};

template<typename T32BITS, typename T64BITS>
struct SelectIntPointerType < T32BITS, T64BITS, 4 >
{
	typedef T32BITS TIntPointer; // select the 64 bit type
};

/**
* Generic types for almost all compilers and platforms
**/
struct FGenericPlatformTypes
{
	// Unsigned base types.
	typedef unsigned char 		uint8;		// 8-bit  unsigned.
	typedef unsigned short int	uint16;		// 16-bit unsigned.
	typedef unsigned int		uint32;		// 32-bit unsigned.
	typedef unsigned long long	uint64;		// 64-bit unsigned.

	// Signed base types.
	typedef	signed char			int8;		// 8-bit  signed.
	typedef signed short int	int16;		// 16-bit signed.
	typedef signed int	 		int32;		// 32-bit signed.
	typedef signed long long	int64;		// 64-bit signed.

	// Character types.
	typedef char				ANSICHAR;	// An ANSI character       -                  8-bit fixed-width representation of 7-bit characters.
	typedef wchar_t				WIDECHAR;	// A wide character        - In-memory only.  ?-bit fixed-width representation of the platform's natural wide character set.  Could be different sizes on different platforms.
	typedef uint8				CHAR8;		// An 8-bit character type - In-memory only.  8-bit representation.  Should really be char8_t but making this the generic option is easier for compilers which don't fully support C++11 yet (i.e. MSVC).
	typedef uint16				CHAR16;		// A 16-bit character type - In-memory only.  16-bit representation.  Should really be char16_t but making this the generic option is easier for compilers which don't fully support C++11 yet (i.e. MSVC).
	typedef uint32				CHAR32;		// A 32-bit character type - In-memory only.  32-bit representation.  Should really be char32_t but making this the generic option is easier for compilers which don't fully support C++11 yet (i.e. MSVC).
#if IS_UNICODE
	typedef WIDECHAR			TCHAR;		// A switchable character  - In-memory only.  Either ANSICHAR or WIDECHAR, depending on a licensee's requirements.
#else
	typedef ANSICHAR			TCHAR;		// A switchable character  - In-memory only.  Either ANSICHAR or WIDECHAR, depending on a licensee's requirements.
#endif // IS_UNICODE

	typedef SelectIntPointerType<uint32, uint64, sizeof(void*)>::TIntPointer UPTRINT;	// unsigned int the same size as a pointer
	typedef SelectIntPointerType<int32, int64, sizeof(void*)>::TIntPointer PTRINT;	// signed int the same size as a pointer
	typedef UPTRINT SIZE_T;															// signed int the same size as a pointer

	typedef int32					TYPE_OF_NULL;
};
