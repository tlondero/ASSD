#include "Bell.h"
#include <cstdlib> 
#include <algorithm>
#include <ctime>
#include <random>

Bell::Bell() {
	this->n = 1;
	this->m = 2;
	this->tau = 0.5;
	this->io = 0.5;
}

vector <double> Bell::generateNote(double duration, double pitch, double Normvelocity) {
	vector <double> BellSound;
	double fc = pitch* (this->m);
	double fm = pitch* (this->n);

	double Idet;
	double Adet;
	
	for (int i = 0; i < (int)duration * SAMPLE_RATE; i++) {
		Idet = (this->io) * exp(-i / (SAMPLE_RATE * (this->tau)));
		Adet = exp(-i / (SAMPLE_RATE * (this->tau)));				
		BellSound.push_back( Adet*( cos( (DOSPI * fc * i / SAMPLE_RATE) + Idet * cos(DOSPI * fm * i / SAMPLE_RATE))*Normvelocity ));
	}

	double max = *max_element(BellSound.begin(), BellSound.end());
	for (int i = 0; i < BellSound.size(); i++) {
		BellSound[i] = BellSound[i] / max;
	}

	return BellSound;
}

Bell::~Bell() {
}