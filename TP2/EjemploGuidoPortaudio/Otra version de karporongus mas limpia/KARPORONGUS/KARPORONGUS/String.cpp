#include "String.h"
#include <stdlib.h> 
#include <ctime>

String::String(int pitch_, long int fs_)
{
	srand(time(NULL));
	this->currentSample = fs_;
	this->pitch = pitch_;
	for (int i = 0; i < floor((fs_ / (double)pitch_));i++) {
		waveTable.push_back((rand() % 2)*2 - 1);
	}
	this->currentSample = 0;
	this->previousSample = 0;
}

double String::getSample(void) {
	double sample;
	if (this->currentSample > this->startSample) {
		int currentSampleNorm = this->currentSample % this->waveTable.size();
		this->waveTable[currentSampleNorm] = 0.5*(this->waveTable[currentSampleNorm] + this->previousSample);
		sample = this->waveTable[currentSampleNorm];
		this->previousSample = sample;
		this->currentSample++;
	}
	else {
		this->currentSample++;
		sample = 0;
	}
	return sample;
}


String::~String()
{
}
