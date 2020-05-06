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

	std::vector<double> x1;
	std::vector<double> x2;
	std::vector<double> x3;
	std::vector<double> x;

	Organ my_organ(
		
		1, //Subharmonic count
		0, //Mixharmonic count
		5,  //Sub
		0,  //Fifth
		0,  //Primary
		0,  //Eighth
		0,  //Twelveth
		0,  //Fifteenth
		0,  //Seventeenth
		0,  //Nineteenth
		0,  //Below
		0,  //Major Third
		0,  //Perfect Fourth
		0); //Perfect Fifth

	x1 = my_organ.generateNote(0.1, 110, 10);
	//x2 = my_organ.generateNote(0.1, 98, 10);
	//x3 = my_organ.generateNote(2.2, 110, 10);

	for (int i = 0; i < x1.size(); i++) {
		x.push_back(x1[i]);
	}

	/*for (int i = 0; i < x2.size(); i++) {
		x.push_back(x2[i]);
	}

	for (int i = 0; i < x3.size(); i++) {
		x.push_back(x3[i]);
	}	*/

	makeWav(2, 4, "sintest", x, 10000);

}

