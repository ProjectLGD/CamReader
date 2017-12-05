// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <stdint.h>
#if defined(__APPLE__) || defined(__linux__)
typedef int16_t _int16; // want avans gebruikt types die niet in stdint.h zijn gedefined..
#endif

#include "targetver.h"

#include <stdio.h>
//#include <tchar.h>


#include <opencv2/opencv.hpp>

#include "avansvisionlib.h"


// TODO: reference additional headers your program requires here
