#include "Guitar.h"
#include <stdlib.h> 

#include <ctime>

Guitar::Guitar(int pitch_, long int fs_,double rf_)
{
	srand(time(NULL));
	this->fs= fs_;
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
vector<double> Guitar::composeSound( double cutFactor, int duration, double delay,int TotalDuration){
	for (int i = 0; i <= (int)(delay*fs); i++) {
		Guitarsound.push_back(0);
	}
	for (int i = 0; i < duration*fs; i++) {
		if (i < cutFactor*duration*fs) {
			this->Guitarsound.push_back(this->getSample());
		}
		else{
			Guitarsound.push_back(this->getSample()*cos(3.1415*(i - cutFactor * duration*fs) / ((2 * duration*fs*(1 - cutFactor)))));
		}
	}
	for (int i = 0; i < (TotalDuration - (duration+delay))*fs; i++) {
		Guitarsound.push_back(0);
	}
	return this->Guitarsound;
}
Guitar::~Guitar()
{
}
