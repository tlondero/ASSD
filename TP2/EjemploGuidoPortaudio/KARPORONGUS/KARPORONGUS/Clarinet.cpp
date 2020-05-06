#include "Clarinet.h"
#include <cstdlib> 
#include <algorithm>
#include <ctime>
#include <random>

Clarinet::Clarinet() {
	this->n = 2;
	this->m = 3;
	this->tau = 0.25/3;
	this->io = 2;
}

vector <double> Clarinet::generateNote(double duration, double pitch, double Normvelocity) {
	vector <double> ClarinetSound;
	double fc = pitch* (this->m);
	double fm = pitch* (this->n);

	double Idet;
	double Adet;

	double normtime = duration * SAMPLE_RATE;
	

	for (int i = 0; i < (int)duration * SAMPLE_RATE; i++) {
		Idet = (this->io) * (1 + exp(-i / (SAMPLE_RATE * (this->tau))));
		if (i < 0.2 * SAMPLE_RATE) {
			Adet = i / ( 0.2 * SAMPLE_RATE);
		}
		else if ((i >= 0.2 * SAMPLE_RATE) && (i <= 1.8 * SAMPLE_RATE)) {
			Adet = 1;
		}
		else if ((i > 1.8 * SAMPLE_RATE) && (i <= 2.2 * SAMPLE_RATE)) {
			Adet = 0.5 + cos(DOSPI * (1.25 * i / SAMPLE_RATE - 2.25))/2;
		}
		else
			Adet = 0;
		ClarinetSound.push_back( Adet*( cos( (DOSPI * fc * i / SAMPLE_RATE) + Idet * cos(DOSPI * fm * i / SAMPLE_RATE))*Normvelocity ));
	}

	double max = *max_element(ClarinetSound.begin(), ClarinetSound.end());
	for (int i = 0; i < ClarinetSound.size(); i++) {
		ClarinetSound[i] = ClarinetSound[i] / max;
	}

	return ClarinetSound;
}

Clarinet::~Clarinet() {
}

/*
CAMPANA: Fc/Fm = 2/1
A = e^-x/T
T = 2/3
I = A/2

TROMBON: 1/1
I = 3*CLARINETE
A
*/