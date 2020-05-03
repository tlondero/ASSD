#pragma once
#include <vector>
using namespace std;

class String
{
public:
	String(int pitch_, long int fs_);
	~String();
	double getSample(void);

private:
	int pitch;
	long int fs;
	double startSample;
	int currentSample;
	double previousSample;
	vector <double> waveTable;
};

