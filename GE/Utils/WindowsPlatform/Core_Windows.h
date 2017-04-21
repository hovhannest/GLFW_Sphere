#pragma once

#include <assert.h>

#include "GenericPlatform/GenericPlatform.h"

struct FWindowsPlatformTypes : public FGenericPlatformTypes
{
	/************************************************************************/
	/*                      Data types                                      */
	/************************************************************************/
	// Standard types
	typedef __int8					int8;
	typedef unsigned __int8			uint8;

	typedef __int16					int16;
	typedef unsigned __int16		uint16;

	typedef __int32					int32;
	typedef unsigned __int32		uint32;

	typedef __int64					int64;
	typedef unsigned __int64		uint64;

#if WIN64
	typedef unsigned __int64	uint_ptr;
	typedef unsigned __int64	handle;
#else
	typedef unsigned __int32	uint_ptr;
	typedef unsigned __int32	handle;
#endif
};


typedef FWindowsPlatformTypes FPlatformTypes;

#define MAX_PATH				PATH_MAX

#define FORCEINLINE inline
#define FORCEINLINE_DEBUGGABLE inline

// Base defines, must define these for the platform, there are no defaults
#define PLATFORM_DESKTOP					0
#if defined (_WIN64)
#define PLATFORM_64BITS						1
#else
#define PLATFORM_64BITS						0
#endif

#define FORCEINLINE inline
#define FORCEINLINE_DEBUGGABLE inline