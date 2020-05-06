#pragma once
#include <vector>
#include "Instrument.h"
#include "../General.h"

#define DOSPI	6.283185307179586476925286766559
#define PI		DOSPI/2

using namespace std;

class Bell : public Instrument
{
public:
	Bell();
	~Bell();
	
	vector <double> generateNote(double duration, double pitch, double Normvelocity);

private:
	double n;
	double m;
	double tau;
	double io;
};