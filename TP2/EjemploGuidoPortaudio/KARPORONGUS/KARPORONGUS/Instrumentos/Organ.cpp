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
	double T = duration * SAMPLE_RATE;
	double ADSR;
	double A;
	double R;
	double ADSR_freq_factor;
	std::vector<double> debug;
	int debug2 = 0;


	//For para cada posición de tiempo discreto
	for (int n = 0; n < T; n++) {

		//For para cada harmónico de sub
		for (int i = 0; i < this->sub_harmonic_count; i++) {

			//Cálculos de factores de ventana
			f = (frequency*((i + 1) + (2 * i)));
			F = f / frequency;
			ADSR_freq_factor = ((2) / (1 + (exp((-F + 1) / (10)))))*(volume + 0.51);
			A = (a*T) / ADSR_freq_factor;
			R = (r*T) / ADSR_freq_factor;

			//Cálculos de ventana
			if (n <= (A)) {
				ADSR = sin(n*TWO_PI / (4 * A));
			/*	if (i == 0) {
					debug.push_back(ADSR);
				}*/
			}
			else if (n > (A) && n <= (T - R)) {
				if ((T / SAMPLE_RATE) > 0.5) {
					ADSR = 1 + ((2 / (1 + exp(-9 * T*(n - A)))) - 1) * s * sin(TWO_PI * (n - A) * (2 / (T - R - A)));
				/*	if (i == 0) {
						debug.push_back(ADSR);
					}*/
				}
				else {
					ADSR = 1;
					/*if (i == 0) {
						debug.push_back(ADSR);
					}*/
				}
			}
			else if (n > (T - R)) {
				if ((volume >= 0.3)&&(T > 0.5)) {
					ADSR = (1 + s * sin(TWO_PI * (T - R - A) * (2 / (T - R - A)))) * cos((n - (T - R))*(TWO_PI / (4 * R))) * (1 - ((s*F*(volume + 0.1)*sin(TWO_PI * 21  * ((n - (T - R))/SAMPLE_RATE))) * (sin(TWO_PI * (1 / (4 * R) * (n - (T - R)))))));
					/*if (i == 0) {
						debug.push_back(ADSR);
					}*/
				}
				else {
					ADSR = cos((n - (T - R))*(TWO_PI / (4 * R)));
				/*	if (i == 0) {
						debug.push_back(ADSR);
					}*/
				}
			}

			//Generación de harmónicos
			if (this->sub != 0) {
				if (i == 0) {
					note.push_back(ADSR * sub_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));
				}
				else {
					note[n] += (ADSR * sub_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));
				}
			}

		}

		//Harmónicos below
				//Cálculos de ventana
		if (n <= (A)) {
			ADSR = sin(n*TWO_PI / (4 * A));
		}
		else if (n > (A) && n <= (T - R)) {
			if ((T / SAMPLE_RATE) > 0.5) {
				ADSR = 1 + ((2 / (1 + exp(-9 * T*(n - A)))) - 1) * s * sin(TWO_PI * (n - A) * (2 / (T - R - A)));
			}
			else {
				ADSR = 1;
			}
		}
		else if (n > (T - R)) {
			if ((volume >= 0.3)&&(T > 0.5)) {
				ADSR = (1 + s * sin(TWO_PI * (T - R - A) * (2 / (T - R - A)))) * cos((n - (T - R))*(TWO_PI / (4 * R))) * (1 - ((s*(1/(2*F))*(volume + 0.1)*sin(TWO_PI * 11  * ((n - (T - R))/SAMPLE_RATE))) * (sin(TWO_PI * (1 / (4 * R) * (n - (T - R)))))));
			}
			else {
				ADSR = cos((n - (T - R))*(TWO_PI / (4 * R)));
			}
		}

		if (this->below != 0) {
			note[n] += (ADSR * below * sin(TWO_PI * (frequency / 2) * (n) / SAMPLE_RATE));
			note[n] += (ADSR * below / 2 * sin(TWO_PI * (frequency / 3) * (n) / SAMPLE_RATE));
			note[n] += (ADSR * below / 3 * sin(TWO_PI * (frequency / 4) * (n) / SAMPLE_RATE));
		}


		//For para los demás armónicos
		//Armónicos quinta
		for (int i = 0; i < this->mix_harmonic_count; i++) {

			f = (frequency*((i + 3) + (6 * i)));
			F = f / frequency;
			ADSR_freq_factor = ((2) / (1 + (exp((-F + 1) / (10)))))*(volume + 0.51);
			A = (a*T) / ADSR_freq_factor;
			R = (r*T) / ADSR_freq_factor;

			if (this->fifth != 0) {


				//Cálculos de ventana
				if (n <= (A)) {
					ADSR = sin(n*TWO_PI / (4 * A));
				}
				else if (n > (A) && n <= (T - R)) {
					if ((T / SAMPLE_RATE) > 0.5) {
						ADSR = 1 + ((2 / (1 + exp(-9 * T*(n - A)))) - 1) * s * sin(TWO_PI * (n - A) * (2 / (T - R - A)));
					}
					else {
						ADSR = 1;
					}
				}
				else if (n > (T - R)) {
					if ((volume >= 0.3)&&(T > 0.5)) {
						ADSR = (1 + s * sin(TWO_PI * (T - R - A) * (2 / (T - R - A)))) * cos((n - (T - R))*(TWO_PI / (4 * R))) * (1 - ((s*F*(volume + 0.1)*sin(TWO_PI * 21  * ((n - (T - R))/SAMPLE_RATE))) * (sin(TWO_PI * (1 / (4 * R) * (n - (T - R)))))));
					}
					else {
						ADSR = cos((n - (T - R))*(TWO_PI / (4 * R)));
					}
				}

				note[n] += (fifth_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));

			}
			//primary;

			f = (frequency*((i + 2) + (4 * i)));
			F = f / frequency;
			ADSR_freq_factor = ((2) / (1 + (exp((-F + 1) / (10)))))*(volume + 0.51);
			A = (a*T) / ADSR_freq_factor;
			R = (r*T) / ADSR_freq_factor;

			if (this->primary != 0) {


				//Cálculos de ventana
				if (n <= (A)) {
					ADSR = sin(n*TWO_PI / (4 * A));
				}
				else if (n > (A) && n <= (T - R)) {
					if ((T / SAMPLE_RATE) > 0.5) {
						ADSR = 1 + ((2 / (1 + exp(-9 * T*(n - A)))) - 1) * s * sin(TWO_PI * (n - A) * (2 / (T - R - A)));
					}
					else {
						ADSR = 1;
					}
				}
				else if (n > (T - R)) {
					if ((volume >= 0.3)&&(T > 0.5)) {
						ADSR = (1 + s * sin(TWO_PI * (T - R - A) * (2 / (T - R - A)))) * cos((n - (T - R))*(TWO_PI / (4 * R))) * (1 - ((s*F*(volume + 0.1)*sin(TWO_PI * 21  * ((n - (T - R))/SAMPLE_RATE))) * (sin(TWO_PI * (1 / (4 * R) * (n - (T - R)))))));
					}
					else {
						ADSR = cos((n - (T - R))*(TWO_PI / (4 * R)));
					}
				}

				note[n] += (primary_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));

			}

			//Armónicos octava;

			f = (frequency*((i + 4) + (8 * i)));
			F = f / frequency;
			ADSR_freq_factor = ((2) / (1 + (exp((-F + 1) / (10)))))*(volume + 0.51);
			A = (a*T) / ADSR_freq_factor;
			R = (r*T) / ADSR_freq_factor;

			if (this->eighth != 0) {


				//Cálculos de ventana
				if (n <= (A)) {
					ADSR = sin(n*TWO_PI / (4 * A));
				}
				else if (n > (A) && n <= (T - R)) {
					if ((T / SAMPLE_RATE) > 0.5) {
						ADSR = 1 + ((2 / (1 + exp(-9 * T*(n - A)))) - 1) * s * sin(TWO_PI * (n - A) * (2 / (T - R - A)));
					}
					else {
						ADSR = 1;
					}
				}
				else if (n > (T - R)) {
					if ((volume >= 0.3)&&(T > 0.5)) {
						ADSR = (1 + s * sin(TWO_PI * (T - R - A) * (2 / (T - R - A)))) * cos((n - (T - R))*(TWO_PI / (4 * R))) * (1 - ((s*F*(volume + 0.1)*sin(TWO_PI * 21  * ((n - (T - R))/SAMPLE_RATE))) * (sin(TWO_PI * (1 / (4 * R) * (n - (T - R)))))));
					}
					else {
						ADSR = cos((n - (T - R))*(TWO_PI / (4 * R)));
					}
				}

				note[n] += (eighth_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));

			}

			//Armónicos duodécima;

			f = (frequency*((i + 6) + (12 * i)));
			F = f / frequency;
			ADSR_freq_factor = ((2) / (1 + (exp((-F + 1) / (10)))))*(volume + 0.51);
			A = (a*T) / ADSR_freq_factor;
			R = (r*T) / ADSR_freq_factor;

			if (this->twelveth != 0) {


				//Cálculos de ventana
				if (n <= (A)) {
					ADSR = sin(n*TWO_PI / (4 * A));
				}
				else if (n > (A) && n <= (T - R)) {
					if ((T / SAMPLE_RATE) > 0.5) {
						ADSR = 1 + ((2 / (1 + exp(-9 * T*(n - A)))) - 1) * s * sin(TWO_PI * (n - A) * (2 / (T - R - A)));
					}
					else {
						ADSR = 1;
					}
				}
				else if (n > (T - R)) {
					if ((volume >= 0.3)&&(T > 0.5)) {
						ADSR = (1 + s * sin(TWO_PI * (T - R - A) * (2 / (T - R - A)))) * cos((n - (T - R))*(TWO_PI / (4 * R))) * (1 - ((s*F*(volume + 0.1)*sin(TWO_PI * 21  * ((n - (T - R))/SAMPLE_RATE))) * (sin(TWO_PI * (1 / (4 * R) * (n - (T - R)))))));
					}
					else {
						ADSR = cos((n - (T - R))*(TWO_PI / (4 * R)));
					}
				}

				note[n] += (twelveth_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));

			}

			//Armónicos decimoquinta;

			f = (frequency*((i + 8) + (15 * i)));
			F = f / frequency;
			ADSR_freq_factor = ((2) / (1 + (exp((-F + 1) / (10)))))*(volume + 0.51);
			A = (a*T) / ADSR_freq_factor;
			R = (r*T) / ADSR_freq_factor;

			if (this->fifteenth != 0) {


				//Cálculos de ventana
				if (n <= (A)) {
					ADSR = sin(n*TWO_PI / (4 * A));
				}
				else if (n > (A) && n <= (T - R)) {
					if ((T / SAMPLE_RATE) > 0.5) {
						ADSR = 1 + ((2 / (1 + exp(-9 * T*(n - A)))) - 1) * s * sin(TWO_PI * (n - A) * (2 / (T - R - A)));
					}
					else {
						ADSR = 1;
					}
				}
				else if (n > (T - R)) {
					if ((volume >= 0.3)&&(T > 0.5)) {
						ADSR = (1 + s * sin(TWO_PI * (T - R - A) * (2 / (T - R - A)))) * cos((n - (T - R))*(TWO_PI / (4 * R))) * (1 - ((s*F*(volume + 0.1)*sin(TWO_PI * 21  * ((n - (T - R))/SAMPLE_RATE))) * (sin(TWO_PI * (1 / (4 * R) * (n - (T - R)))))));
					}
					else {
						ADSR = cos((n - (T - R))*(TWO_PI / (4 * R)));
					}
				}

				note[n] += (fifteenth_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));

			}
			
			//Armónicos decimoséptima;
			f = (frequency*((i + 9) + (17 * i)));
			F = f / frequency;
			ADSR_freq_factor = ((2) / (1 + (exp((-F + 1) / (10)))))*(volume + 0.51);
			A = (a*T) / ADSR_freq_factor;
			R = (r*T) / ADSR_freq_factor;

			if (this->seventeenth != 0) {


				//Cálculos de ventana
				if (n <= (A)) {
					ADSR = sin(n*TWO_PI / (4 * A));
				}
				else if (n > (A) && n <= (T - R)) {
					if ((T / SAMPLE_RATE) > 0.5) {
						ADSR = 1 + ((2 / (1 + exp(-9 * T*(n - A)))) - 1) * s * sin(TWO_PI * (n - A) * (2 / (T - R - A)));
					}
					else {
						ADSR = 1;
					}
				}
				else if (n > (T - R)) {
					if ((volume >= 0.3)&&(T > 0.5)) {
						ADSR = (1 + s * sin(TWO_PI * (T - R - A) * (2 / (T - R - A)))) * cos((n - (T - R))*(TWO_PI / (4 * R))) * (1 - ((s*F*(volume + 0.1)*sin(TWO_PI * 21  * ((n - (T - R))/SAMPLE_RATE))) * (sin(TWO_PI * (1 / (4 * R) * (n - (T - R)))))));
					}
					else {
						ADSR = cos((n - (T - R))*(TWO_PI / (4 * R)));
					}
				}

				note[n] += (seventeenth_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));

			}
			
			//Armónicos décimonovena;
			f = (frequency*((i + 10) + (19 * i)));
			F = f / frequency;
			ADSR_freq_factor = ((2) / (1 + (exp((-F + 1) / (10)))))*(volume + 0.51);
			A = (a*T) / ADSR_freq_factor;
			R = (r*T) / ADSR_freq_factor;

			if (this->nineteenth != 0) {


				//Cálculos de ventana
				if (n <= (A)) {
					ADSR = sin(n*TWO_PI / (4 * A));
				}
				else if (n > (A) && n <= (T - R)) {
					if ((T / SAMPLE_RATE) > 0.5) {
						ADSR = 1 + ((2 / (1 + exp(-9 * T*(n - A)))) - 1) * s * sin(TWO_PI * (n - A) * (2 / (T - R - A)));
					}
					else {
						ADSR = 1;
					}
				}
				else if (n > (T - R)) {
					if ((volume >= 0.3)&&(T > 0.5)) {
						ADSR = (1 + s * sin(TWO_PI * (T - R - A) * (2 / (T - R - A)))) * cos((n - (T - R))*(TWO_PI / (4 * R))) * (1 - ((s*F*(volume + 0.1)*sin(TWO_PI * 21  * ((n - (T - R))/SAMPLE_RATE))) * (sin(TWO_PI * (1 / (4 * R) * (n - (T - R)))))));
					}
					else {
						ADSR = cos((n - (T - R))*(TWO_PI / (4 * R)));
					}
				}

				note[n] += (nineteenth_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));

			}

			//Armónicos para la componente de tercera mayor;
			f = (major_third_frequency*((i + 1) + (2 * i)));
			F = f / frequency;
			ADSR_freq_factor = ((2) / (1 + (exp((-F + 1) / (10)))))*(volume + 0.51);
			A = (a*T) / ADSR_freq_factor;
			R = (r*T) / ADSR_freq_factor;

			if (this->majorThird != 0) {


				//Cálculos de ventana
				if (n <= (A)) {
					ADSR = sin(n*TWO_PI / (4 * A));
				}
				else if (n > (A) && n <= (T - R)) {
					if ((T / SAMPLE_RATE) > 0.5) {
						ADSR = 1 + ((2 / (1 + exp(-9 * T*(n - A)))) - 1) * s * sin(TWO_PI * (n - A) * (2 / (T - R - A)));
					}
					else {
						ADSR = 1;
					}
				}
				else if (n > (T - R)) {
					if ((volume >= 0.3)&&(T > 0.5)) {
						ADSR = (1 + s * sin(TWO_PI * (T - R - A) * (2 / (T - R - A)))) * cos((n - (T - R))*(TWO_PI / (4 * R))) * (1 - ((s*F*(volume + 0.1)*sin(TWO_PI * 21  * ((n - (T - R))/SAMPLE_RATE))) * (sin(TWO_PI * (1 / (4 * R) * (n - (T - R)))))));
					}
					else {
						ADSR = cos((n - (T - R))*(TWO_PI / (4 * R)));
					}
				}

				note[n] += (major_third_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));

			}

			//Armónicos de componente de cuarta perfecta;
			f = (perfect_fourth_frequency*((i + 1) + (2 * i)));
			F = f / frequency;
			ADSR_freq_factor = ((2) / (1 + (exp((-F + 1) / (10)))))*(volume + 0.51);
			A = (a*T) / ADSR_freq_factor;
			R = (r*T) / ADSR_freq_factor;

			if (this->perfectFourth != 0) {


				//Cálculos de ventana
				if (n <= (A)) {
					ADSR = sin(n*TWO_PI / (4 * A));
				}
				else if (n > (A) && n <= (T - R)) {
					if ((T / SAMPLE_RATE) > 0.5) {
						ADSR = 1 + ((2 / (1 + exp(-9 * T*(n - A)))) - 1) * s * sin(TWO_PI * (n - A) * (2 / (T - R - A)));
					}
					else {
						ADSR = 1;
					}
				}
				else if (n > (T - R)) {
					if ((volume >= 0.3)&&(T > 0.5)) {
						ADSR = (1 + s * sin(TWO_PI * (T - R - A) * (2 / (T - R - A)))) * cos((n - (T - R))*(TWO_PI / (4 * R))) * (1 - ((s*F*(volume + 0.1)*sin(TWO_PI * 21  * ((n - (T - R))/SAMPLE_RATE))) * (sin(TWO_PI * (1 / (4 * R) * (n - (T - R)))))));
					}
					else {
						ADSR = cos((n - (T - R))*(TWO_PI / (4 * R)));
					}
				}

				note[n] += (perfect_fourth_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));

			}

			//Armónicos de la componente de quinta perfecta;
			f = (perfect_fifth_frequency*((i + 1) + (2 * i)));
			F = f / frequency;
			ADSR_freq_factor = ((2) / (1 + (exp((-F + 1) / (10)))))*(volume + 0.51);
			A = (a*T) / ADSR_freq_factor;
			R = (r*T) / ADSR_freq_factor;

			if (this->perfectFifth != 0) {


				//Cálculos de ventana
				if (n <= (A)) {
					ADSR = sin(n*TWO_PI / (4 * A));
				}
				else if (n > (A) && n <= (T - R)) {
					if ((T / SAMPLE_RATE) > 0.5) {
						ADSR = 1 + ((2 / (1 + exp(-9 * T*(n - A)))) - 1) * s * sin(TWO_PI * (n - A) * (2 / (T - R - A)));
					}
					else {
						ADSR = 1;
					}
				}
				else if (n > (T - R)) {
					if ((volume >= 0.3)&&(T > 0.5)) {
						ADSR = (1 + s * sin(TWO_PI * (T - R - A) * (2 / (T - R - A)))) * cos((n - (T - R))*(TWO_PI / (4 * R))) * (1 - ((s*F*(volume + 0.1)*sin(TWO_PI * 21  * ((n - (T - R))/SAMPLE_RATE))) * (sin(TWO_PI * (1 / (4 * R) * (n - (T - R)))))));
					}
					else {
						ADSR = cos((n - (T - R))*(TWO_PI / (4 * R)));
					}
				}

				note[n] += (perfect_fifth_harmonics[i] * ADSR * sin(TWO_PI * f * (n) / SAMPLE_RATE));

			}
		}

		//Componente de ruido
		A = (a*T);
		R = (r*T);
		//Cálculos de ventana
		if (n <= (A)) {
			ADSR = sin(n*TWO_PI / (4 * A));
		}
		else if (n > (A) && n <= (T - R)) {
			if ((T / SAMPLE_RATE) > 0.5) {
				ADSR = 1 + ((2 / (1 + exp(-9 * T*(n - A)))) - 1) * s * sin(TWO_PI * (n - A) * (2 / (T - R - A)));
			}
			else {
				ADSR = 1;
			}
		}
		else if (n > (T - R)) {
			if ((volume >= 0.3)&&(T > 0.5)) {
				ADSR = (1 + s * sin(TWO_PI * (T - R - A) * (2 / (T - R - A)))) * cos((n - (T - R))*(TWO_PI / (4 * R))) * (1 - ((s*F*(volume + 0.1)*sin(TWO_PI * 21  * ((n - (T - R))/SAMPLE_RATE))) * (sin(TWO_PI * (1 / (4 * R) * (n - (T - R)))))));
			}
			else {
				ADSR = cos((n - (T - R))*(TWO_PI / (4 * R)));
			}
		}

		note[n] += (((rand() % 2) * 2) - 1)*this->noise*ADSR;

	}


	//std::ofstream myfile;
	//myfile.open("adsr" + std::to_string(debug2) + ".txt");
	//for (int i = 0; i < debug.size(); i++) {
	//	myfile << debug[i];
	//	if (i != debug.size() - 1) {
	//		myfile << ",";
	//	}
	//}
	//myfile.close();
	//std::cout << "ready" << std::endl;
	//debug2++;
	//getchar();


	//Normalizando la amplitud del vector a volume
	double max = *max_element(note.begin(), note.end());
	for (int i = 0; i < note.size(); i++) {
		note[i] = (note[i] / max) * volume;
	}

	return note;
}

Organ::~Organ()
{
}

