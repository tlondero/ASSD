#include "Trumpet.h"
#include <cstdlib> 
#include <algorithm>
#include <ctime>
#include <random>

Trumpet::Trumpet() {
	this->n = 1;
	this->m = 1;
	this->io = 10;
}

vector <double> Trumpet::generateNote(double duration, double pitch, double Normvelocity) {
	vector <double> TrumpetSound;
	double fc = pitch* (this->m);
	double fm = pitch* (this->n);

	double Idet;
	double Adet;

	double normtime = duration * SAMPLE_RATE;
	

	for (int i = 0; i < (int)duration * SAMPLE_RATE; i++) {

		if (i < 2 * normtime / 11) {
			Idet = (this->io) * (i * 11.0 / (2 * normtime));
		}
		else if ((i >= 2 * normtime / 11) && (i <= 7 * normtime / 22)) {
			Idet = (this->io) * (i * (-11.0 / (6 * normtime)) + 4.0 / 3);
		}
		else if ((i > 7 * normtime / 22) && (i < 9 * normtime / 11)) {
			Idet = (this->io) * (i * (-3.0 / (10 * normtime)) + 93.0 / 110);
		}
		else if ((i >= 9 * normtime / 11) && (i <= normtime)) {
			Idet = (this->io) * (i * (-33.0 / (10.0 * normtime)) + 33.0 / 10);
		}
		else {
			Idet = 0;
		}

		if (i < 2 * normtime / 11) {
			Adet = i * 11.0 / (2 * normtime);
		}
		else if ((i >= 2 * normtime / 11) && (i <= 7 * normtime / 22)) {
			Adet = i * (-11.0 / (6 * normtime)) + 4.0 / 3;
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
		TrumpetSound.push_back( Adet*( cos( (DOSPI * fc * i / SAMPLE_RATE) + Idet * cos(DOSPI * fm * i / SAMPLE_RATE))*Normvelocity ));
	}

	double max = *max_element(TrumpetSound.begin(), TrumpetSound.end());
	for (int i = 0; i < TrumpetSound.size(); i++) {
		TrumpetSound[i] = TrumpetSound[i] / max;
	}

	return TrumpetSound;
}

Trumpet::~Trumpet() {
}