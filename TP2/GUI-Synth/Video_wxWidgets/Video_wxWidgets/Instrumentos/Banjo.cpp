#include "Banjo.h"
using namespace std;
#include <ctime>
#include <random>
#include <algorithm>
Banjo::Banjo(){
}

double Banjo::getSample(){
	double sample = 0;
	int currentSampleNorm = this->currentSample % this->waveTable.size();
	this->waveTable[currentSampleNorm] = rf * (this->a*this->waveTable[currentSampleNorm] + this->b* this->previousSample);
	sample = this->waveTable[currentSampleNorm];
	this->previousSample = sample;
	this->currentSample++;
	return sample;
}
vector<double> Banjo::generateNote(double duration, double pitch, double Normvelocity, double cutFactor, char noiseType) {
	srand(time(NULL));
	this->waveTable.clear();
	this->b = ((double)SAMPLE_RATE / (pitch)) - (int)((double)SAMPLE_RATE / (pitch));
	this->a = 1 - this->b;
	if (b == 0 || pitch < 400) {
		a = 0.5;
		b = 0.5;
	}
	rf = 0.96;
	vector<double> Banjosound;
	if (noiseType == 'B')
		for (int i = 0; i < floor((SAMPLE_RATE / (double)pitch)); i++)
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
	for (int i = 0; i < floor(duration*SAMPLE_RATE); i++) {
		if (i < cutFactor*duration*SAMPLE_RATE) {
			Banjosound.push_back(this->getSample());
		}
		else {
			Banjosound.push_back(this->getSample()*cos(3.1415*(i - cutFactor * duration*SAMPLE_RATE) / ((2 * duration*SAMPLE_RATE*(1 - cutFactor)))));
		}
	}
	double max = *max_element(Banjosound.begin(), Banjosound.end());
	for (int i = 0; i < Banjosound.size(); i++) {
		Banjosound[i] = Banjosound[i] / max;
	}
	return Banjosound;
}

Banjo::~Banjo()
{
}
