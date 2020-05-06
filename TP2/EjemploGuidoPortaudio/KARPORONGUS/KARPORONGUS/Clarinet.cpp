#include "Clarinet.h"
#include <cstdlib> 
#include <algorithm>
#include <ctime>
#include <random>

Clarinet::Clarinet() {
	this->n = 2;
	this->m = 3;
	this->tau = 0.1/3;
	this->io = 2;
}

vector <double> Clarinet::generateNote(double duration, double pitch, double Normvelocity) {
	vector <double> ClarinetSound;
	double fc = pitch* (this->m);
	double fm = pitch* (this->n);

	double Idet;
	double Adet;

	int normtime = (int) duration * SAMPLE_RATE;

	for (int i = 0; i < (int)duration * SAMPLE_RATE; i++) {
	
		Idet = (this->io) * (1 + exp(-i / (normtime * (this->tau))) );
				
		if (i*11 < normtime) {
			Adet = i * 11 / normtime;
		}
		else if ((i * 11 >= normtime) && (i * 11 <= (9) * normtime)) {
			Adet = 1;
		}
		else {
			Adet = 0.5 + cos( (PI*11/2) * i / normtime - (9*PI/2) ) / 2 ;
		}

		ClarinetSound.push_back(Normvelocity*Adet*( cos( (DOSPI * fc * i / normtime) + Idet * cos(DOSPI * fm * i / normtime) ) ) );
	}

	double max = *max_element(ClarinetSound.begin(), ClarinetSound.end());
	for (int i = 0; i < ClarinetSound.size(); i++) {
		ClarinetSound[i] = ClarinetSound[i] / max;
	}

	return ClarinetSound;
}

Clarinet::~Clarinet() {
}