#include "Organ.h"
#include <iostream>


Organ::Organ(std::vector<double> harmonic_content, double A = 0.05, double D = 0, double S = 0.75, double R = 0.2)
{
	this->harmonic_content = harmonic_content;
	this->A = A;
	this->D = D;
	this->S = S;
	this->R = R;
}

std::vector<double> Organ::generateNote(double duration, double frequency, double volume)
{
	std::vector<double> note;
	std::vector<double> F;

	for (int n = 0; n < SAMPLE_RATE*duration; n++) {
		note.push_back(0);
	}
	
	for (int i = 0; i < this->harmonic_content.size(); i++) { //falta implementar ADSR
		for (int n = 0; n < SAMPLE_RATE*duration; n++) {
			note[n] += harmonic_content[i] * volume * sin(TWO_PI*(frequency/SAMPLE_RATE)*(i+1) * n);
		}
	}
	
	return note;
}

Organ::~Organ()
{
}

