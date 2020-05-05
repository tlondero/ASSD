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

	std::vector<double> harmonic_components{1, 0.668, 0.5623, 0.4466, 0.2386, 0.266, 0.1333, 0.0841, 0.0595, 6.3e-3, 5.7e-3, 3.1e-3, 2.3e-3, 2.8e-3, 1.9e-3};
	std::vector<double> x;
	Organ my_organ(harmonic_components, 0.05, 0, 0.75, 0.2);

	x = my_organ.generateNote(5, 220, 10); //ay dios suena horrible

	makeWav(2, 5, "sintest", x, 10000);

}

