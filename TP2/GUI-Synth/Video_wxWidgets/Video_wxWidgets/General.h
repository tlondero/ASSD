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

//INSTRUMENTOS
#define PREVIEW_DURATION		6
#define NUMBER_OF_INSTRUMETS	10
const std::string  InstrumentList[NUMBER_OF_INSTRUMETS] = { "GUITAR", "ORGAN", "FLUTE", "BELL", "CLARINET", "TROMBONE", "TRUMPET", "DRUM", "BANJO", "ELECTRIC_GUITAR" };

//VENTANAS
#define NUMBER_OF_WINDOWS		11
const std::string  WindowsList[NUMBER_OF_WINDOWS] = { "triang", "blackman", "hanning", "hamming", "bartlett", "blackmanharris", "barthann", "rectangular", "gaussian", "exponential", "kaiser" };