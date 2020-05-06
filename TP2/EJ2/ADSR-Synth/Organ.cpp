#include "Organ.h"
#include <iostream>


Organ::Organ(double sub_harmonic_count, double mix_harmonic_count, double sub, double fifth, double primary, double eight, double twelveth, double fifteenth, double seventeenth, double nineteenth, double below, double third, double fourth, double perfect_fifth, double A, double D, double S, double R)
{
	this->sub = sub;
	this->fifth = fifth;
	this->primary = primary;
	this->eighth = eighth;
	this->twelveth = twelveth;
	this->fifteenth = fifteenth;
	this->seventeenth = seventeenth;
	this->nineteenth = nineteenth;
	this->below = below;
	this->majorThird = third;
	this->perfectFourth = fourth;
	this->perfectFifth = perfect_fifth;

	this->sub_harmonic_count = sub_harmonic_count;
	this->mix_harmonic_count = mix_harmonic_count;

	for (int i = 0; i < this->sub_harmonic_count; i++) {
		this->sub_harmonics.push_back(pow(10, (-(i) * 20 / this->sub_harmonic_count)) * sub);
	}

	for (int i = 0; i < this->mix_harmonic_count; i++) {
		this->fifth_harmonics.push_back(pow(10, (-(i) * 100 / this->mix_harmonic_count)) * fifth);
		this->primary_harmonics.push_back(pow(10, (-(i)  * 100 / this->mix_harmonic_count)) * primary);
		this->eighth_harmonics.push_back(pow(10, (-(i)  * 100 / this->mix_harmonic_count)) * eighth);
		this->twelveth_harmonics.push_back(pow(10, (-(i)  * 100 / this->mix_harmonic_count)) * twelveth);
		this->fifteenth_harmonics.push_back(pow(10, (-(i)  * 100 / this->mix_harmonic_count)) * fifteenth);
		this->seventeenth_harmonics.push_back(pow(10, (-(i)  * 100 / this->mix_harmonic_count)) * seventeenth);
		this->nineteenth_harmonics.push_back(pow(10, (-(i)  * 100 / this->mix_harmonic_count)) * nineteenth);
		this->below_harmonics.push_back(pow(10, (-(i)  * 100 / this->mix_harmonic_count)) * below);
		this->major_third_harmonics.push_back(pow(10, (-(i)  * 100 / this->mix_harmonic_count)) * third);
		this->perfect_fourth_harmonics.push_back(pow(10, (-(i)  * 100 / this->mix_harmonic_count)) * fourth);
		this->perfect_fifth_harmonics.push_back(pow(10, (-(i)  * 100 / this->mix_harmonic_count)) * perfect_fifth);
	}

}

std::vector<double> Organ::generateNote(double duration, double frequency, double volume)
{
	std::vector<double> note;
	double major_third_frequency = frequency * 1.25992105; //  (pow(2, (4 / 12)))
	double perfect_fifth_frequency = frequency * 1.498307077; // (pow(2, (7 / 12)))
	double perfect_fourth_frequency = frequency * 1.334839854; // (pow(2, (5 / 12)))

	//sub;
	for (int i = 0; i < this->sub_harmonic_count; i++) {
		for (int n = 0; n < duration*SAMPLE_RATE; n++) {
			if (this->sub != 0) {
				if (i == 0) {
					note.push_back(sub_harmonics[i] * sin(TWO_PI * (frequency*((i + 1) + (2 * i))) * (n) / SAMPLE_RATE));
				}
				else {
					note[n] += (sub_harmonics[i] * sin(TWO_PI * (frequency*((i + 1) + (2 * i))) * (n) / SAMPLE_RATE));
				}
			}
		}
	}
	//fifth;					
	for (int i = 0; i < this->mix_harmonic_count; i++) {
		if (this->fifth != 0) {
			for (int n = 0; n < duration*SAMPLE_RATE; n++) {
				note[n] += (fifth_harmonics[i] * sin(TWO_PI * (frequency*((i + 3) + (6 * i))) * (n) / SAMPLE_RATE));
			}
		}
	}
	//primary;
	for (int i = 0; i < this->mix_harmonic_count; i++) {
		if (this->primary != 0) {
			for (int n = 0; n < duration*SAMPLE_RATE; n++) {
				note[n] += (primary_harmonics[i] * sin(TWO_PI * (frequency*((i + 2) + (4 * i))) * (n) / SAMPLE_RATE));
			}
		}
	}
	//eighth;
	for (int i = 0; i < this->mix_harmonic_count; i++) {
		if (this->eighth != 0) {
			for (int n = 0; n < duration*SAMPLE_RATE; n++) {
				note[n] += (eighth_harmonics[i] * sin(TWO_PI * (frequency*((i + 4) + (8 * i))) * (n) / SAMPLE_RATE));
			}
		}
	}
	//twelveth;
	for (int i = 0; i < this->mix_harmonic_count; i++) {
		if (this->twelveth != 0) {
			for (int n = 0; n < duration*SAMPLE_RATE; n++) {
				note[n] += (twelveth_harmonics[i] * sin(TWO_PI * (frequency*((i + 6) + (12 * i))) * (n) / SAMPLE_RATE));
			}
		}
	}
	//fifteenth;
	for (int i = 0; i < this->mix_harmonic_count; i++) {
		if (this->fifteenth != 0) {
			for (int n = 0; n < duration*SAMPLE_RATE; n++) {
				note[n] += (fifteenth_harmonics[i] * sin(TWO_PI * (frequency*((i + 8) + (15 * i))) * (n) / SAMPLE_RATE));
			}
		}
	}
	//seventeenth;
	for (int i = 0; i < this->mix_harmonic_count; i++) {
		if (this->seventeenth != 0) {
			for (int n = 0; n < duration*SAMPLE_RATE; n++) {
				note[n] += (seventeenth_harmonics[i] * sin(TWO_PI * (frequency*((i + 9) + (17 * i))) * (n) / SAMPLE_RATE));
			}
		}
	}
	//nineteenth;
	for (int i = 0; i < this->mix_harmonic_count; i++) {
		if (this->nineteenth != 0) {
			for (int n = 0; n < duration*SAMPLE_RATE; n++) {
				note[n] += (nineteenth_harmonics[i] * sin(TWO_PI * (frequency*((i + 10) + (19 * i))) * (n) / SAMPLE_RATE));
			}
		}
	}
	//below;
	for (int n = 0; n < duration*SAMPLE_RATE; n++) {
		if (this->below != 0) {
			note[n] += (below * sin(TWO_PI * (frequency / 2) * (n) / SAMPLE_RATE));
			note[n] += (below/2 * sin(TWO_PI * (frequency / 3) * (n) / SAMPLE_RATE));
			note[n] += (below/3 * sin(TWO_PI * (frequency / 4) * (n) / SAMPLE_RATE));
		}
	}
	//majorThirdComponent;
	for (int i = 0; i < this->mix_harmonic_count; i++) {
		if (this->majorThird != 0) {
			for (int n = 0; n < duration*SAMPLE_RATE; n++) {
				note[n] += (major_third_harmonics[i] * sin(TWO_PI * (major_third_frequency*((i + 1) + (2 * i))) * (n) / SAMPLE_RATE));
			}
		}
	}
	//perfectFourthComponent;
	for (int i = 0; i < this->mix_harmonic_count; i++) {
		if (this->perfectFourth != 0) {
			for (int n = 0; n < duration*SAMPLE_RATE; n++) {
				note[n] += (perfect_fourth_harmonics[i] * sin(TWO_PI * (perfect_fourth_frequency*((i + 1) + (2 * i))) * (n) / SAMPLE_RATE));
			}
		}
	}
	//perfectFifthComponent;
	for (int i = 0; i < this->mix_harmonic_count; i++) {
		if (this->perfectFifth != 0) {
			for (int n = 0; n < duration*SAMPLE_RATE; n++) {
				note[n] += (perfect_fifth_harmonics[i] * sin(TWO_PI * (perfect_fifth_frequency*((i + 1) + (2 * i))) * (n) / SAMPLE_RATE));
			}
		}
	}

	//noise
	double noise_factor = 0.002;
	for (int n = 0; n < duration*SAMPLE_RATE; n++) {
		note[n] += (((rand() % 2) * 2) - 1)*noise_factor;
	}

	//double max = *max_element(note.begin(), note.end());
	//for (int i = 0; i < note.size(); i++) {
	//	note[i] = note[i] / max;
	//}

	return note;
}

Organ::~Organ()
{
}

