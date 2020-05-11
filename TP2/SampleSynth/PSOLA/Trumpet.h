#pragma once
#include <vector>
#include "Instrument.h"

#define SAMPLE_RATE 44100
#define MAX_AMP         32760
#define TWO_PI          6.283185307179586476925286766559
#include <stdlib.h> // Random
#include <stdio.h>
#include <ctime>
#include <math.h>
//#include "portaudio.h"
#include <fstream>
#include <iostream>

#define DOSPI 6.283185307179586476925286766559

using namespace std;

class Trumpet : public Instrument
{
public:
	Trumpet();
	~Trumpet();
	
	vector <double> generateNote(double duration, double pitch, double Normvelocity);

private:
	double n;
	double m;
	double io;
};