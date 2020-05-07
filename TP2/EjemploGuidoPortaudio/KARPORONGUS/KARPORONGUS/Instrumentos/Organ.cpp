#include "Organ.h"
#include <iostream>


Organ::Organ()
{
}

void Organ::set_parameters(double sub_harmonic_count, double mix_harmonic_count, double sub, double fifth, double primary, double eight, double twelveth, double fifteenth, double seventeenth, double nineteenth, double below, double third, double fourth, double perfect_fifth, double a, double r, double s, double noise)
{
	this->a = a;
	this->r = r;
	this->s = s;
	this->noise = noise;

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
		this->sub_harmonics.push_back(pow(10, (-(i) * 10 / this->sub_harmonic_count)) * sub);
	}

	for (int i = 0; i < this->mix_harmonic_count; i++) {
		this->fifth_harmonics.push_back(pow(10, (-(i) * 20 / this->mix_harmonic_count)) * fifth);
		this->primary_harmonics.push_back(pow(10, (-(i) * 10 / this->mix_harmonic_count)) * primary);
		this->eighth_harmonics.push_back(pow(10, (-(i) * 20 / this->mix_harmonic_count)) * eighth);
		this->twelveth_harmonics.push_back(pow(10, (-(i) * 20 / this->mix_harmonic_count)) * twelveth);
		this->fifteenth_harmonics.push_back(pow(10, (-(i) * 20 / this->mix_harmonic_count)) * fifteenth);
		this->seventeenth_harmonics.push_back(pow(10, (-(i) * 20 / this->mix_harmonic_count)) * seventeenth);
		this->nineteenth_harmonics.push_back(pow(10, (-(i) * 20 / this->mix_harmonic_count)) * nineteenth);
		this->below_harmonics.push_back(pow(10, (-(i) * 20 / this->mix_harmonic_count)) * below);
		this->major_third_harmonics.push_back(pow(10, (-(i) * 20 / this->mix_harmonic_count)) * third);
		this->perfect_fourth_harmonics.push_back(pow(10, (-(i) * 20 / this->mix_harmonic_count)) * fourth);
		this->perfect_fifth_harmonics.push_back(pow(10, (-(i) * 20 / this->mix_harmonic_count)) * perfect_fifth);
	}
}

std::vector<double> Organ::generateNote(double duration, double frequency, double volume)
{
	std::vector<double> note;
	double major_third_frequency = frequency * 1.25992105; //  (pow(2, (4 / 12)))
	double perfect_fifth_frequency = frequency * 1.498307077; // (pow(2, (7 / 12)))
	double perfect_fourth_frequency = frequency * 1.334839854; // (pow(2, (5 / 12)))
	double F;
	double f;
	double T = duration*SAMPLE_RATE;
	double ADSR;
	double A;
	double R;
	double ADSR_freq_factor;

	//sub;
	for (int i = 0; i < this->sub_harmonic_count; i++) {
		
		f = (frequency*((i + 1) + (2 * i)));
		F = f/frequency;
		ADSR_freq_factor = ((2) / (1 + (exp((-F + 1) / (10)))))*(volume+0.51);
		A = (a*T) / ADSR_freq_factor;
		R = (r*T) / ADSR_freq_factor;
		
		for (int n = 0; n < T; n++) {

			if (n <= (A)) {
				ADSR = sin(n*TWO_PI / (4 * A));
			}
			else if (n > (A) && n < (T-R)) {
				if ((T/SAMPLE_RATE) > 0.5) {
					ADSR = ((1-s) + s*cos(TWO_PI * (n-A) * ((frequency*SAMPLE_RATE)/(50*(T))) / (SAMPLE_RATE)));
				}
				else {
					ADSR = 1;
				}
			}
			else if (n > (T-R)){
				ADSR = cos((((double)TWO_PI) / (4 * R))*(n - (T - R)));
			}


			if (this->sub != 0) {
				if (i == 0) {
					note.push_back(ADSR * sub_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));
				}
				else {
					note[n] += (ADSR * sub_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));
				}
			}
		}
	}
	//fifth;					
	for (int i = 0; i < this->mix_harmonic_count; i++) {

		f = (frequency*((i + 3) + (6 * i)));
		F = f / frequency;
		ADSR_freq_factor = ((2) / (1 + (exp((-F + 1) / (10)))))*(volume+0.51);
		A = (a*T) / ADSR_freq_factor;
		R = (r*T) / ADSR_freq_factor;

		if (this->fifth != 0) {
			for (int n = 0; n < T; n++) {

				if (n <= (A)) {
				ADSR = sin(n*TWO_PI / (4 * A));
			}
			else if (n > (A) && n < (T-R)) {
				if ((T/SAMPLE_RATE) > 0.5) {
					ADSR = ((1-s) + s*cos(TWO_PI * (n-A) * ((frequency*SAMPLE_RATE)/(50*(T))) / (SAMPLE_RATE)));
				}
				else {
					ADSR = 1;
				}
			}
			else if (n > (T-R)){
				ADSR = cos((((double)TWO_PI) / (4 * R))*(n - (T - R)));
			}

				note[n] += (fifth_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));
			}
		}
	}
	//primary;
	for (int i = 0; i < this->mix_harmonic_count; i++) {

		f = (frequency*((i + 2) + (4 * i)));
		F = f / frequency;
		ADSR_freq_factor = ((2) / (1 + (exp((-F + 1) / (10)))))*(volume+0.51);
		A = (a*T) / ADSR_freq_factor;
		R = (r*T) / ADSR_freq_factor;

		if (this->primary != 0) {
			for (int n = 0; n < T; n++) {

				if (n <= (A)) {
					ADSR = sin(n*TWO_PI / (4 * A));
				}
				else if (n > (A) && n < (T - R)) {
					if ((T / SAMPLE_RATE) > 0.5) {
						ADSR = ((1-s) + s*cos(TWO_PI * (n - A) * ((frequency*SAMPLE_RATE) / (50 *(T))) / (SAMPLE_RATE)));
					}
					else {
						ADSR = 1;
					}
				}
				else if (n > (T - R)) {
					ADSR = cos((((double)TWO_PI) / (4 * R))*(n - (T - R)));
				}

				note[n] += (primary_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));
			}
		}
	}
	//eighth;
	for (int i = 0; i < this->mix_harmonic_count; i++) {

		f = (frequency*((i + 4) + (8 * i)));
		F = f / frequency;
		ADSR_freq_factor = ((2) / (1 + (exp((-F + 1) / (10)))))*(volume+0.51);
		A = (a*T) / ADSR_freq_factor;
		R = (r*T) / ADSR_freq_factor;

		if (this->eighth != 0) {
			for (int n = 0; n < T; n++) {

				if (n <= (A)) {
					ADSR = sin(n*TWO_PI / (4 * A));
				}
				else if (n > (A) && n < (T - R)) {
					if ((T / SAMPLE_RATE) > 0.5) {
						ADSR = ((1-s) + s*cos(TWO_PI * (n - A) * ((frequency*SAMPLE_RATE) / (50 *(T))) / (SAMPLE_RATE)));
					}
					else {
						ADSR = 1;
					}
				}
				else if (n > (T - R)) {
					ADSR = cos((((double)TWO_PI) / (4 * R))*(n - (T - R)));
				}

				note[n] += (eighth_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));
			}
		}
	}
	//twelveth;
	for (int i = 0; i < this->mix_harmonic_count; i++) {

		f = (frequency*((i + 6) + (12 * i)));
		F = f / frequency;
		ADSR_freq_factor = ((2) / (1 + (exp((-F + 1) / (10)))))*(volume+0.51);
		A = (a*T) / ADSR_freq_factor;
		R = (r*T) / ADSR_freq_factor;

		if (this->twelveth != 0) {
			for (int n = 0; n < T; n++) {

				if (n <= (A)) {
					ADSR = sin(n*TWO_PI / (4 * A));
				}
				else if (n > (A) && n < (T - R)) {
					if ((T / SAMPLE_RATE) > 0.5) {
						ADSR = ((1-s) + s*cos(TWO_PI * (n - A) * ((frequency*SAMPLE_RATE) / (50 *(T))) / (SAMPLE_RATE)));
					}
					else {
						ADSR = 1;
					}
				}
				else if (n > (T - R)) {
					ADSR = cos((((double)TWO_PI) / (4 * R))*(n - (T - R)));
				}

				note[n] += (twelveth_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));
			}
		}
	}
	//fifteenth;
	for (int i = 0; i < this->mix_harmonic_count; i++) {

		f = (frequency*((i + 8) + (15 * i)));
		F = f / frequency;
		ADSR_freq_factor = ((2) / (1 + (exp((-F + 1) / (10)))))*(volume+0.51);
		A = (a*T) / ADSR_freq_factor;
		R = (r*T) / ADSR_freq_factor;

		if (this->fifteenth != 0) {
			for (int n = 0; n < T; n++) {

				if (n <= (A)) {
					ADSR = sin(n*TWO_PI / (4 * A));
				}
				else if (n > (A) && n < (T - R)) {
					if ((T / SAMPLE_RATE) > 0.5) {
						ADSR = ((1-s) + s*cos(TWO_PI * (n - A) * ((frequency*SAMPLE_RATE) / (50 *(T))) / (SAMPLE_RATE)));
					}
					else {
						ADSR = 1;
					}
				}
				else if (n > (T - R)) {
					ADSR = cos((((double)TWO_PI) / (4 * R))*(n - (T - R)));
				}

				note[n] += (fifteenth_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));
			}
		}
	}
	//seventeenth;
	for (int i = 0; i < this->mix_harmonic_count; i++) {

		f = (frequency*((i + 9) + (17 * i)));
		F = f / frequency;
		ADSR_freq_factor = ((2) / (1 + (exp((-F + 1) / (10)))))*(volume+0.51);
		A = (a*T) / ADSR_freq_factor;
		R = (r*T) / ADSR_freq_factor;

		if (this->seventeenth != 0) {
			for (int n = 0; n < T; n++) {

				if (n <= (A)) {
					ADSR = sin(n*TWO_PI / (4 * A));
				}
				else if (n > (A) && n < (T - R)) {
					if ((T / SAMPLE_RATE) > 0.5) {
						ADSR = ((1-s) + s*cos(TWO_PI * (n - A) * ((frequency*SAMPLE_RATE) / (50 *(T))) / (SAMPLE_RATE)));
					}
					else {
						ADSR = 1;
					}
				}
				else if (n > (T - R)) {
					ADSR = cos((((double)TWO_PI) / (4 * R))*(n - (T - R)));
				}

				note[n] += (seventeenth_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));
			}
		}
	}
	//nineteenth;
	for (int i = 0; i < this->mix_harmonic_count; i++) {

		f = (frequency*((i + 10) + (19 * i)));
		F = f / frequency;
		ADSR_freq_factor = ((2) / (1 + (exp((-F + 1) / (10)))))*(volume+0.51);
		A = (a*T) / ADSR_freq_factor;
		R = (r*T) / ADSR_freq_factor;

		if (this->nineteenth != 0) {
			for (int n = 0; n < T; n++) {

				if (n <= (A)) {
					ADSR = sin(n*TWO_PI / (4 * A));
				}
				else if (n > (A) && n < (T - R)) {
					if ((T / SAMPLE_RATE) > 0.5) {
						ADSR = ((1-s) + s*cos(TWO_PI * (n - A) * ((frequency*SAMPLE_RATE) / (50 *(T))) / (SAMPLE_RATE)));
					}
					else {
						ADSR = 1;
					}
				}
				else if (n > (T - R)) {
					ADSR = cos((((double)TWO_PI) / (4 * R))*(n - (T - R)));
				}

				note[n] += (nineteenth_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));
			}
		}
	}
	//below;
	for (int n = 0; n < T; n++) {

		if (n <= (A)) {
			ADSR = sin(n*TWO_PI / (4 * A));
		}
		else if (n > (A) && n < (T - R)) {
			if ((T / SAMPLE_RATE) > 0.5) {
				ADSR = ((1-s) + s*cos(TWO_PI * (n - A) * ((frequency*SAMPLE_RATE) / (50 *(T))) / (SAMPLE_RATE)));
			}
			else {
				ADSR = 1;
			}
		}
		else if (n > (T - R)) {
			ADSR = cos((((double)TWO_PI) / (4 * R))*(n - (T - R)));
		}

		if (this->below != 0) {
			note[n] += (ADSR * below * sin(TWO_PI * (frequency / 2) * (n) / SAMPLE_RATE));
			note[n] += (ADSR * below/2 * sin(TWO_PI * (frequency / 3) * (n) / SAMPLE_RATE));
			note[n] += (ADSR * below/3 * sin(TWO_PI * (frequency / 4) * (n) / SAMPLE_RATE));
		}
	}
	//majorThirdComponent;
	for (int i = 0; i < this->mix_harmonic_count; i++) {

		f = (major_third_frequency*((i + 1) + (2 * i)));
		F = f / frequency;
		ADSR_freq_factor = ((2) / (1 + (exp((-F + 1) / (10)))))*(volume+0.51);
		A = (a*T) / ADSR_freq_factor;
		R = (r*T) / ADSR_freq_factor;

		if (this->majorThird != 0) {
			for (int n = 0; n < T; n++) {

				if (n <= (A)) {
					ADSR = sin(n*TWO_PI / (4 * A));
				}
				else if (n > (A) && n < (T - R)) {
					if ((T / SAMPLE_RATE) > 0.5) {
						ADSR = ((1-s) + s*cos(TWO_PI * (n - A) * ((frequency*SAMPLE_RATE) / (50 *(T))) / (SAMPLE_RATE)));
					}
					else {
						ADSR = 1;
					}
				}
				else if (n > (T - R)) {
					ADSR = cos((((double)TWO_PI) / (4 * R))*(n - (T - R)));
				}

				note[n] += (major_third_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));
			}
		}
	}
	//perfectFourthComponent;
	for (int i = 0; i < this->mix_harmonic_count; i++) {

		f = (perfect_fourth_frequency*((i + 1) + (2 * i)));
		F = f / frequency;
		ADSR_freq_factor = ((2) / (1 + (exp((-F + 1) / (10)))))*(volume+0.51);
		A = (a*T) / ADSR_freq_factor;
		R = (r*T) / ADSR_freq_factor;

		if (this->perfectFourth != 0) {
			for (int n = 0; n < T; n++) {

				if (n <= (A)) {
					ADSR = sin(n*TWO_PI / (4 * A));
				}
				else if (n > (A) && n < (T - R)) {
					if ((T / SAMPLE_RATE) > 0.5) {
						ADSR = ((1-s) + s*cos(TWO_PI * (n - A) * ((frequency*SAMPLE_RATE) / (50 *(T))) / (SAMPLE_RATE)));
					}
					else {
						ADSR = 1;
					}
				}
				else if (n > (T - R)) {
					ADSR = cos((((double)TWO_PI) / (4 * R))*(n - (T - R)));
				}

				note[n] += (perfect_fourth_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));
			}
		}
	}
	//perfectFifthComponent;
	for (int i = 0; i < this->mix_harmonic_count; i++) {

		f = (perfect_fifth_frequency*((i + 1) + (2 * i)));
		F = f / frequency;
		ADSR_freq_factor = ((2) / (1 + (exp((-F + 1) / (10)))))*(volume+0.51);
		A = (a*T) / ADSR_freq_factor;
		R = (r*T) / ADSR_freq_factor;

		if (this->perfectFifth != 0) {
			for (int n = 0; n < T; n++) {

				if (n <= (A)) {
					ADSR = sin(n*TWO_PI / (4 * A));
				}
				else if (n > (A) && n < (T - R)) {
					if ((T / SAMPLE_RATE) > 0.5) {
						ADSR = ((1-s) + s*cos(TWO_PI * (n - A) * ((frequency*SAMPLE_RATE) / (50 *(T))) / (SAMPLE_RATE)));
					}
					else {
						ADSR = 1;
					}
				}
				else if (n > (T - R)) {
					ADSR = cos((((double)TWO_PI) / (4 * R))*(n - (T - R)));
				}

				note[n] += (perfect_fifth_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));
			}
		}
	}

	//noise

	A = (a*T);
	R = (r*T);

	for (int n = 0; n < T; n++) {

		if (n <= (A)) {
			ADSR = sin(n*TWO_PI / (4 * A));
		}
		else if (n > (A) && n < (T - R)) {
			if ((T / SAMPLE_RATE) > 0.5) {
				ADSR = ((1 - s) + s * cos(TWO_PI * (n - A) * ((frequency*SAMPLE_RATE) / (50 * (T))) / (SAMPLE_RATE)));
			}
			else {
				ADSR = 1;
			}
		}
		else if (n > (T - R)) {
			ADSR = cos((((double)TWO_PI) / (4 * R))*(n - (T - R)));
		}

		note[n] += (((rand() % 2) * 2) - 1)*this->noise*ADSR;
	}

	double max = *max_element(note.begin(), note.end());
	for (int i = 0; i < note.size(); i++) {
		note[i] = note[i] / max;
	}

	return note;
}

Organ::~Organ()
{
}

