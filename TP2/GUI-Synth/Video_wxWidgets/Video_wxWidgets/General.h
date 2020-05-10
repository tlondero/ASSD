#pragma once
#include <stdlib.h> // Random
#include <stdio.h>
#include <ctime>
#include <math.h>
#include "portaudio.h"
#include <fstream>
#include <iostream>

#define SAMPLE_RATE		44100
#define MAX_AMP         32760
#define TWO_PI          6.283185307179586476925286766559
#define NUM_CHANNELS	2
#define BITS_PER_SAMPLE 16	//sino 8... sino 32... PROBAR HASTA QUE DE