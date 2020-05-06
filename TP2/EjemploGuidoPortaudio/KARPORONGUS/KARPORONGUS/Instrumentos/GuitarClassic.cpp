#include "GuitarClassic.h"
#include <stdlib.h> 
#include <algorithm>
#include <ctime>
#include <random>
GuitarClassic::GuitarClassic(double rf) {
	this->rf = rf;
}

double GuitarClassic::getSample() {
	double sample = 0;
	int currentSampleNorm = this->currentSample % this->waveTable.size();
	this->waveTable[currentSampleNorm] = rf * 0.5*(this->waveTable[currentSampleNorm] + this->previousSample);
	sample = this->waveTable[currentSampleNorm];
	this->previousSample = sample;
	this->currentSample++;
	return sample;
}
vector<double> GuitarClassic::generateNote(double duration, double pitch, double Normvelocity, double cutFactor, char noiseType) {
	srand(time(NULL));
	this->waveTable.clear();
	vector<double> Guitarsound;
	if (noiseType == 'B')
		for (unsigned int i = 0; i < floor((SAMPLE_RATE / (double)pitch)-0.5); i++)
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
	for (unsigned int i = 0; i < (int)duration*SAMPLE_RATE; i++) {
		if (i < cutFactor*duration*SAMPLE_RATE) {
			Guitarsound.push_back(this->getSample());
		}
		else {
			Guitarsound.push_back(this->getSample()*cos(3.1415*(i - cutFactor * duration*SAMPLE_RATE) / ((2 * duration*SAMPLE_RATE*(1 - cutFactor)))));
		}
	}
	double max = *max_element(Guitarsound.begin(), Guitarsound.end());
	for (unsigned int i = 0; i < Guitarsound.size(); i++) {
		Guitarsound[i] = Guitarsound[i] / max;
	}
	return Guitarsound;
}
GuitarClassic::~GuitarClassic()
{
}
