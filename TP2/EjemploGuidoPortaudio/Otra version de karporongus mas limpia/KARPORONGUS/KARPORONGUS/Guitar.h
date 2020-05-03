#pragma once
#include <vector>
using namespace std;

class Guitar
{
public:
	Guitar(int pitch_, long int fs_,double rf_);
	~Guitar();
	vector<double> composeSound(double cutFactor,int duration,double delay, int TotalDuration);

	double getSample(void);

private:
	int pitch;
	long int fs;
	double startSample;
	int currentSample;
	double previousSample;
	double rf;
	vector <double> waveTable;
	vector<double> Guitarsound;
};

