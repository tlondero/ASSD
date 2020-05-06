#include "Trombone.h"
#include <cstdlib> 
#include <algorithm>
#include <ctime>
#include <random>


Trombone::Trombone() {
	this->n = 2;
	this->m = 3;
	this->io = 3;
}

vector <double> Trombone::generateNote(double duration, double pitch, double Normvelocity) {
	vector <double> TromboneSound;
	double fc = pitch* (this->m);
	double fm = pitch* (this->n);

	double Idet;
	double Adet;

	double normtime = duration * SAMPLE_RATE;
	
	for (int i = 0; i < (int)duration * SAMPLE_RATE; i++) {
		
		if (i < 0.2 * normtime) {
			Idet = i * (this->io) / (0.2 * normtime);
		}
		else if ((i >= 0.2 * normtime) && (i <= 1.8 * normtime)) {
			Idet = (this->io);
		}
		else if ((i > 1.8 * normtime) && (i <= 2.2 * normtime)) {
			Idet = (0.5 + cos(DOSPI * (1.25 * i / normtime - 2.25)) / 2) * (this->io);
		}
		else
			Idet = 0;

		if (i < 0.4 * normtime) {
			Adet = i / ( 0.4 * normtime);
		}
		else if ((i >= 0.4 * normtime) && (i <= 0.7 * normtime)) {
			Adet = i * (-5/6) / normtime + 4/3;
		}
		else if ((i > 0.7 * normtime) && (i <= 1.8 * normtime)) {
			Adet = i* (-3 / 22) / normtime + 93 / 110;
		}
		else if ((i > 1.8 * normtime) && (i <= 2.2 * normtime)) {
			Adet = i * (-3 / 2) / normtime + 33 / 10;
		}
		else
			Adet = 0;

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