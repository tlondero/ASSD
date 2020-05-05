#include "Drum.h"
#include <stdlib.h> 
#include <ctime>
#include "General.h"
using namespace std;
Drum::Drum( double rf_,double prob_)
{

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
vector<double> Drum::generateNote(double duration, double pitch, double Normvelocity, double cutFactor) {
	srand(time(NULL));
	this->waveTable.clear();
	vector<double> DrumSound;
	for (int i = 0; i < floor((SAMPLE_RATE / (double)pitch)); i++) {
		waveTable.push_back(((rand() % 2) * 2 - 1)*Normvelocity);
	}
	this->currentSample = 0;
	this->previousSample = 0;
	for (int i = 0; i < (int)duration*SAMPLE_RATE; i++) {
		if (i < cutFactor*duration*SAMPLE_RATE) {
			DrumSound.push_back(this->getSample());
		}
		else {
			DrumSound.push_back(this->getSample()*cos(3.1415*(i - cutFactor * duration*SAMPLE_RATE) / ((2 * duration*SAMPLE_RATE*(1 - cutFactor)))));
		}
	}

	return DrumSound;
}