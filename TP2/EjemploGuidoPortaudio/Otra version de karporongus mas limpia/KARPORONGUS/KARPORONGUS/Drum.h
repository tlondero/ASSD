#pragma once
#include <vector>

class Drum
{
public:
	Drum(int pitch_, long int fs_, double rf_,double prob_);
	~Drum();
	double getSample(void);

private:
	int pitch;
	long int fs;
	double prob;
	double startSample;
	int currentSample;
	double previousSample;
	double rf;
	std::vector <double> waveTable;
};

