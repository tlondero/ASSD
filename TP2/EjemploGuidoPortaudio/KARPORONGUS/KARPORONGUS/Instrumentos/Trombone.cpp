#include "Trombone.h"
#include <cstdlib> 
#include <algorithm>
#include <ctime>
#include <random>


Trombone::Trombone() {
	this->n = 1;
	this->m = 1;
	this->io = 3;
}

vector <double> Trombone::generateNote(double duration, double pitch, double Normvelocity) {
	vector <double> TromboneSound;
	double fc = 0.5*pitch* (this->m);
	double fm = 0.5*pitch* (this->n);

	double Idet;
	double Adet;

	double normtime = floor(duration * SAMPLE_RATE);
	
	for (int i = 0; i < floor(duration * SAMPLE_RATE); i++) {
		
		if (i * 11 < normtime) {
			Idet = (this->io) * i * 11 / normtime;
		}
		else if ((i * 11 >= normtime) && (i * 11 <= 9 * normtime)) {
			Idet = (this->io) * 1;
		}
		else {
			Idet = (this->io) * (0.5 + cos((PI * 11 / 2) * i / normtime - (9 * PI / 2)) / 2);
		}

		if (i < 2 * normtime / 11) {
			Adet = i * 11.0 / ( 2 * normtime);
		}
		else if ((i >= 2 * normtime / 11) && (i <= 7 * normtime / 22)) {
			Adet = i * (-11.0/(6 * normtime)) + 4.0/3;
		}
		else if ((i > 7 * normtime / 22) && (i < 9 * normtime / 11)) {
			Adet = i * (-3.0 / (10 * normtime)) + 93.0 / 110;
		}
		else if ((i >= 9 * normtime / 11) && (i <= normtime)) {
			Adet = i * (-33.0 / (10.0 * normtime)) + 33.0 / 10;
		}		
		else {
			Adet = 0;
		}

		TromboneSound.push_back( Adet*( cos( (DOSPI * fc * i / SAMPLE_RATE) + Idet * cos(DOSPI * fm * i / SAMPLE_RATE))*Normvelocity ));
	}

	double max = *max_element(TromboneSound.begin(), TromboneSound.end());
	for (int i = 0; i < TromboneSound.size(); i++) {
		TromboneSound[i] = TromboneSound[i] / max;
	}

	return TromboneSound;
}

Trombone::~Trombone() {
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