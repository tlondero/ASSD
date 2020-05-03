#include "Guitar.h"
#include <stdlib.h> 

#include <ctime>

Guitar::Guitar(int pitch_, long int fs_,double rf_)
{
	srand(time(NULL));
	this->currentSample = fs_;
	this->pitch = pitch_;
	for (int i = 0; i < floor((fs_ / (double)pitch_));i++) {
		waveTable.push_back((rand() % 2)*2 - 1);
	}
	this->currentSample = 0;
	this->previousSample = 0;
	this->rf = rf_;
}

double Guitar::getSample(void) {
	double sample=0;
	int currentSampleNorm = this->currentSample % this->waveTable.size();
	this->waveTable[currentSampleNorm] = 0.5*(this->waveTable[currentSampleNorm] + this->previousSample);
	sample = this->waveTable[currentSampleNorm];
	this->previousSample = sample;
	this->currentSample++;
	return sample;
}


Guitar::~Guitar()
{
}
