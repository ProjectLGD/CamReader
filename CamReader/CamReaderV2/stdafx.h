// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <stdint.h>
#if defined(__APPLE__) || defined(__linux__)
typedef int16_t _int16; // want avans gebruikt types die niet in stdint.h zijn gedefined..
#endif

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>


#include <opencv2/opencv.hpp>

#include "avansvisionlib.h"

#include "genetic-algo/DNA.hpp"
#include "genetic-algo/Population.hpp"
#include "genetic-algo/Vec3.h"
#include "genetic-algo/Citizen.hpp"

#include "dot.h"
#include "Rocket.h" // need to know about DNA


// TODO: reference additional headers your program requires here
