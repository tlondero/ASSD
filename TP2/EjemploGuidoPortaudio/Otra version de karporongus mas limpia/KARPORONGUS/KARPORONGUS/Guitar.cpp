#include "Guitar.h"
#include <stdlib.h> 

#include <ctime>

Guitar::Guitar(){
}

double Guitar::getSample(double rf) {
	double sample=0;
	int currentSampleNorm = this->currentSample % this->waveTable.size();
	this->waveTable[currentSampleNorm] = rf*0.5*(this->waveTable[currentSampleNorm] + this->previousSample);
	sample = this->waveTable[currentSampleNorm];
	this->previousSample = sample;
	this->currentSample++;
	return sample;
}
vector<double> Guitar::composeSound( double cutFactor, int duration,int pitch, int SampleRate,double rf, double Normvelocity){
	srand(time(NULL));
	this->waveTable.clear();
	this->Guitarsound.clear();
	for (int i = 0; i < floor((SampleRate / (double)pitch)); i++) {
		waveTable.push_back(((rand() % 2) * 2 - 1)*Normvelocity);
	}
	this->currentSample = 0;
	this->previousSample = 0;
	for (int i = 0; i < duration*SampleRate; i++) {
		if (i < cutFactor*duration*SampleRate) {
			this->Guitarsound.push_back(this->getSample(rf));
		}
		else{
			Guitarsound.push_back(this->getSample(rf)*cos(3.1415*(i - cutFactor * duration*SampleRate) / ((2 * duration*SampleRate*(1 - cutFactor)))));
		}
}
	return this->Guitarsound;
}
Guitar::~Guitar()
{
}
