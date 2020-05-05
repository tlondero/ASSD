#include "Organ.h"
#include <iostream>


Organ::Organ(std::vector<double> harmonic_content, std::vector<double> undertone_content, double A = 0.05, double D = 0, double S = 0.75, double R = 0.2)
{
	this->harmonic_content = harmonic_content;
	this->undertone_content = undertone_content;
	this->A = A;
	this->D = D;
	this->S = S;
	this->R = R;
	this->harmonic_normalization_factor = ;
}

std::vector<double> Organ::generateNote(double duration, double frequency, double volume)
{
	std::vector<double> note;
	double perfect_third_frequency;

	for (int n = 0; n < SAMPLE_RATE*duration; n++) {

		//sub;						
		for (int i = 0; n < sub_harmonics.size(); i++) {
			if (i = 0) {
				note.push_back(sub_harmonics[i] * sin(TWO_PI * (frequency*((i + 1) + (2 * i))) * (n / SAMPLE_RATE)));
			}
			note[n] += (sub_harmonics[i] * sin(TWO_PI * (frequency*((i + 1) + (2 * i))) * (n / SAMPLE_RATE)));
		}

		//fifth;					
		for (int i = 0; n < fifth_harmonics.size(); i++) {
			note[n] += (fifth_harmonics[i] * sin(TWO_PI * (frequency*((i + 3) + (6 * i))) * (n / SAMPLE_RATE)));
		}

		//primary;
		for (int i = 0; n < primary_harmonics.size(); i++) {
			note[n] += (primary_harmonics[i] * sin(TWO_PI * (frequency*((i + 2) + (4 * i))) * (n / SAMPLE_RATE)));
		}

		//eighth;
		for (int i = 0; n < eighth_harmonics.size(); i++) {
			note[n] += (eighth_harmonics[i] * sin(TWO_PI * (frequency*((i + 4) + (8 * i))) * (n / SAMPLE_RATE)));
		}

		//twelveth;
		for (int i = 0; n < twelveth_harmonics.size(); i++) {
			note[n] += (twelveth_harmonics[i] * sin(TWO_PI * (frequency*((i + 6) + (12 * i))) * (n / SAMPLE_RATE)));
		}

		//fifteenth;
		for (int i = 0; n < fifteenth_harmonics.size(); i++) {
			note[n] += (fifteenth_harmonics[i] * sin(TWO_PI * (frequency*((i + 8) + (15 * i))) * (n / SAMPLE_RATE)));
		}

		//seventeenth;
		for (int i = 0; n < seventeenth_harmonics.size(); i++) {
			note[n] += (seventeenth_harmonics[i] * sin(TWO_PI * (frequency*((i + 9) + (17 * i))) * (n / SAMPLE_RATE)));
		}

		//nineteenth;
		for (int i = 0; n < nineteenth_harmonics.size(); i++) {
			note[n] += (nineteenth_harmonics[i] * sin(TWO_PI * (frequency*((i + 10) + (19 * i))) * (n / SAMPLE_RATE)));
		}

		//below;
		note[n] += (below * sin(TWO_PI * (frequency/2) * (n / SAMPLE_RATE)));
		
		//perfectThirdComponent;


		
		//perfectFourthComponent;
		
		//perfectFifthComponent;

	}


	for (int i = 0; i < this->harmonic_content.size(); i++) { //falta implementar ADSR
		if (this->undertone_content.size() > i) {
			harmonic_normalization_factor += harmonic_content[i] + undertone_content[i];
		for (int n = 0; n < SAMPLE_RATE*duration; n++) {
			note[n] += harmonic_content[i] * sin(TWO_PI*(frequency/SAMPLE_RATE)*(i+1) * n);
			note[n] += undertone_content[i] * sin(TWO_PI*(frequency / (SAMPLE_RATE * (i + 2))) * n);
			}
		}
		else {
			harmonic_normalization_factor += harmonic_content[i];
			for (int n = 0; n < SAMPLE_RATE*duration; n++) {
				note[n] += harmonic_content[i] * sin(TWO_PI*(frequency / SAMPLE_RATE)*(i + 1) * n);
			}
		}
	}

	return note;
}

Organ::~Organ()
{
}

