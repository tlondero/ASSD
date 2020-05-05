#include "Drum.h"
#include <stdlib.h> 
#include <ctime>


Drum::Drum(int pitch_, long int fs_, double rf_,double prob_)
{
	srand(time(NULL));
	this->currentSample = fs_;
	this->pitch = pitch_;
	for (int i = 0; i < floor((fs_ / (double)pitch_)); i++) {
		waveTable.push_back((rand() % 2) * 2 - 1);
	}
	this->currentSample = 0;
	this->previousSample = 0;
	this->rf = rf_;
	this->prob = prob_;
}

double Drum::getSample(void) {
	double sample = 0;
	int currentSampleNorm = this->currentSample % this->waveTable.size();
	if (rand() % 100 < this->prob * 100) {
		this->waveTable[currentSampleNorm] = 0.5*(this->waveTable[currentSampleNorm] + this->previousSample);
	}
	else {
		this->waveTable[currentSampleNorm] = -0.5*(this->waveTable[currentSampleNorm] + this->previousSample);
	}
	sample = this->waveTable[currentSampleNorm];
	this->previousSample = sample;
	this->currentSample++;
	return sample;
}
Drum::~Drum()
{
}
