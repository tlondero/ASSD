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
	std::vector<double> x4;
	std::vector<double> x5;
	std::vector<double> x11;
	std::vector<double> x22;
	std::vector<double> x33;
	std::vector<double> x;
	double duration = 4;
	//Organ my_organ(
	//	
	//	4, //Subharmonic count
	//	3, //Mixharmonic count
	//	0.5,  //Sub
	//	0.4,  //Fifth
	//	0.8,  //Primary
	//	0.6,  //Eighth
	//	0.5,  //Twelveth
	//	0.6,  //Fifteenth
	//	0.7,  //Seventeenth
	//	0.8,  //Nineteenth
	//	0.6,  //Below
	//	0.1,  //Major Third
	//	0,  //Perfect Fourth
	//	0, 0.2, 0.5, 0.001); //Perfect Fifth

	Organ my_organ(

		2, //Subharmonic count
		3, //Mixharmonic count
		1,  //Sub
		1e-10,  //Fifth
		1e-4,  //Primary
		1e-15,  //Eighth
		1e-5,  //Twelveth
		0,  //Fifteenth
		0,  //Seventeenth
		0,  //Nineteenth
		0.005,  //Below
		0.001,  //Major Third
		0.000001,  //Perfect Fourth
		0,  //Perfect Fifth
		0.1, //Attack
		0.3,  //Recovery
		0.000005);//Noise factor

	x1 = my_organ.generateNote(duration/10, 330, 10);
	x2 = my_organ.generateNote(duration/10, 370.4, 10);
	x3 = my_organ.generateNote(duration/10, 415.78, 10);
	x4 = my_organ.generateNote(duration / 10, 370.4, 10);
	x5 = my_organ.generateNote(duration - (4*duration/10), 330, 10);

	/*x11 = my_organ.generateNote(0.15, 220, 10);
	x22 = my_organ.generateNote(0.15, 196, 10);
	x33 = my_organ.generateNote(2.2, 220, 10);*/

	for (int i = 0; i < x1.size(); i++) {
		x.push_back(x1[i]);//+x11[i]);
	}

	for (int i = 0; i < x2.size(); i++) {
		x.push_back(x2[i]);//+x22[i]);
	}

	for (int i = 0; i < x3.size(); i++) {
		x.push_back(x3[i]);// +x33[i]);
	}	

	for (int i = 0; i < x4.size(); i++) {
		x.push_back(x4[i]);//+x22[i]);
	}

	for (int i = 0; i < x5.size(); i++) {
		x.push_back(x5[i]);// +x33[i]);
	}


	makeWav(2, duration, "test", x, 20000);

	std::ofstream myfile;
	myfile.open("sintest.txt");
	for (int i = 0; i < x.size(); i++) {
		myfile << x[i];
		if (i != x.size() - 1) {
			myfile << ",";
		}
	}
	myfile.close();

}
