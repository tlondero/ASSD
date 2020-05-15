#include "GuitarImproved.h"

#include <stdlib.h> 
#include <algorithm>
#include <ctime>
#include <random>

GuitarImproved::GuitarImproved()
{
}
void GuitarImproved:: setParam(double rf) {
	this->rf = rf;
}
double GuitarImproved::getSample() {
	double sample = 0;
	int currentSampleNorm = this->currentSample % this->waveTable.size();
	this->waveTable[currentSampleNorm] = rf * (this->a*this->waveTable[currentSampleNorm] +this->b* this->previousSample);
	sample = this->waveTable[currentSampleNorm];
	this->previousSample = sample;
	this->currentSample++;
	return sample;
}
vector<double> GuitarImproved::generateNote(double duration, double pitch, double Normvelocity, double cutFactor, char noiseType) {
	srand(time(NULL));
	this->waveTable.clear();
	this->b = ((double)SAMPLE_RATE/( pitch )) - (int)((double)SAMPLE_RATE / ( pitch));
	this->a = 1 - this->b;
	if (b < 0.05 || pitch<200) {
		a = 0.5;
		b = 0.5;
	}
	//a = 0.5;
	//b = 0.5;
	vector<double> Guitarsound;
	if (noiseType == 'B')
		for (unsigned int i = 0; i < floor((SAMPLE_RATE / (double)pitch) ); i++)
			waveTable.push_back(((rand() % 2) * 2 - 1)*Normvelocity);

	else if (noiseType == 'U')
		for (int i = 0; i < floor((SAMPLE_RATE / (double)pitch)); i++)
			waveTable.push_back(((rand() / (double)RAND_MAX) * 2 - 1)*Normvelocity);

	else if (noiseType == 'G') {
		std::random_device rd;
		std::mt19937 e2(rd());
		std::normal_distribution<> dist(0, 1);
		for (int i = 0; i < floor((SAMPLE_RATE / (double)pitch)); i++) {
			waveTable.push_back(dist(e2)); //Generate numbers;
		}
	}



	this->currentSample = 0;
	this->previousSample = 0;
	for (unsigned int i = 0; i < floor(duration*SAMPLE_RATE); i++) {
		if (i < cutFactor*duration*SAMPLE_RATE) {
			Guitarsound.push_back(this->getSample());
		}
		else {
			Guitarsound.push_back(this->getSample()*cos(3.1415*(i - cutFactor * duration*SAMPLE_RATE) / ((2 * duration*SAMPLE_RATE*(1 - cutFactor)))));
		}
	}
	double max = *max_element(Guitarsound.begin(), Guitarsound.end());
	for (int i = 0; i < Guitarsound.size(); i++) {
		Guitarsound[i] = Guitarsound[i] / max  *Normvelocity;
	}
	return Guitarsound;
}
GuitarImproved::~GuitarImproved()
{
}




//Guitarra electrica?
////
vector<double> GuitarImproved::generateNoteElectric(double duration, double pitch, double Normvelocity, double cutFactor, char noiseType) {
	srand(time(NULL));
	this->waveTable.clear();
	this->b = (double)( pitch / (double)SAMPLE_RATE) - (int)( pitch / (double)SAMPLE_RATE);
	this->a = 1 - this->b;
	if (b == 0 ) {
		a = 0.5;
		b = 0.5;
	}
	if (this->rf > 0.2)
		rf = 0.96;
	vector<double> Guitarsound;
	if (noiseType == 'B')
		for (unsigned int i = 0; i < floor((SAMPLE_RATE / (double)pitch) - 0.5); i++)
			waveTable.push_back(((rand() % 2) * 2 - 1)*Normvelocity);

	else if (noiseType == 'U')
		for (int i = 0; i < floor((SAMPLE_RATE / (double)pitch)); i++)
			waveTable.push_back(((rand() / (double)RAND_MAX) * 2 - 1)*Normvelocity);

	else if (noiseType == 'G') {
		std::random_device rd;
		std::mt19937 e2(rd());
		std::normal_distribution<> dist(0, 1);
		for (int i = 0; i < floor((SAMPLE_RATE / (double)pitch)); i++) {
			waveTable.push_back(dist(e2)); //Generate numbers;
		}
	}



	this->currentSample = 0;
	this->previousSample = 0;
	for (unsigned int i = 0; i < floor(duration*SAMPLE_RATE); i++) {
		if (i < cutFactor*duration*SAMPLE_RATE) {
			Guitarsound.push_back(this->getSample());
		}
		else {
			Guitarsound.push_back(this->getSample()*cos(3.1415*(i - cutFactor * duration*SAMPLE_RATE) / ((2 * duration*SAMPLE_RATE*(1 - cutFactor)))));
		}
	}
	double max = *max_element(Guitarsound.begin(), Guitarsound.end());
	for (int i = 0; i < Guitarsound.size(); i++) {
		Guitarsound[i] = Guitarsound[i] / max;
	}
	return Guitarsound;
}