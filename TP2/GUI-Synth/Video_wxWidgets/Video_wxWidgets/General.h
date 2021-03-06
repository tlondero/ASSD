#pragma once
#include <stdlib.h> // Random
#include <stdio.h>
#include <ctime>
#include <math.h>
#include <fstream>
#include <iostream>

#define SAMPLE_RATE 44100
#define MAX_AMP 32760
#define TWO_PI 6.283185307179586476925286766559
#define NUM_CHANNELS 2
#define TMAX 5.0

//INSTRUMENTOS
#define PREVIEW_DURATION 7
#define NUMBER_OF_INSTRUMETS 12
const std::string InstrumentList[NUMBER_OF_INSTRUMETS] = {"Guitar", "Organ", "Flute", "Bell", "Clarinet", "Trombone", "Trumpet", "Drum", "Banjo", "Electric Guitar", "Saxophone", "Modern Flute"};

//VENTANAS
#define NUMBER_OF_WINDOWS 11
const std::string WindowsList[NUMBER_OF_WINDOWS] = {"Triangular", "Blackman", "Hanning", "Hamming", "Bartlett", "Blackmanharris", "Barthann", "Rectangular", "Gaussian", "Exponential", "Kaiser"};

//EFECTOS
#define NUMBER_OF_EFF 2
const std::string EffList[NUMBER_OF_EFF] = {"Eco", "Reverberation"};

