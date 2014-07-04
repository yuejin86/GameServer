#ifndef _COMMON_H
#define _COMMON_H

#include <stdlib.h>
#include <signal.h>


typedef signed char     int8;
typedef unsigned char	uint8;
typedef short           int16;
typedef unsigned short  uint16;
typedef int             int32;
typedef unsigned int    uint32;

#ifdef _MSC_EXTENSIONS
typedef __int64             int64;
typedef unsigned __int64    uint64;
#elif ! defined(_MSC_VER)
typedef int64_t             int64;
typedef uint64_t            uint64;
#else
typedef long long           int64;
typedef unsigned long long  uint64;
#endif

typedef float           float32;
typedef double          float64;

#endif