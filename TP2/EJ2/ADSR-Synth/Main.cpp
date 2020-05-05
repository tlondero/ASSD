#include <stdlib.h> // Random
#include "WavGen.h"
#include "Organ.h"
#include <stdio.h>
#include <ctime>
#include <math.h>
#include <fstream>
#include <iostream>

#define SAMPLE_RATE     44100
#define TWO_PI          6.283185307179586476925286766559
#define MAX_VOLUME	32760

int main(void) {

	//std::vector<double> harmonic_components{1, 0.668, 0.5623, 0.4466, 0.2386, 0.266, 0.1333, 0.0841, 0.0595, 6.3e-3, 5.7e-3, 3.1e-3, 2.3e-3, 2.8e-3, 1.9e-3};
	std::vector<double> harmonic_components{ 
		0.7, 0.25, 0, 0.06, 0, 0, 0, 0.02, 0.032, 0.0007
	};

	std::vector<double> undertone_components{
		0.5, 0.3, 0.075
	};

	std::vector<double> x1;
	std::vector<double> x2;
	std::vector<double> x3;
	std::vector<double> x;
	Organ my_organ(harmonic_components, undertone_components, 0.05, 0, 0.75, 0.2);

	x1 = my_organ.generateNote(0.5, 110, 10); //ay dios suena horrible
	x2 = my_organ.generateNote(0.5, 147, 10);
	x3 = my_organ.generateNote(0.5, 110, 10);

	for (int i = 0; i < x1.size(); i++) {
		x.push_back(x1[i]);
	}

	for (int i = 0; i < x2.size(); i++) {
		x.push_back(x2[i]);
	}

	for (int i = 0; i < x3.size(); i++) {
		x.push_back(x3[i]);
	}

	makeWav(2, 5, "sintest", x, 10000);

}

