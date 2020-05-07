#pragma once
#include <vector>
#include "Instrument.h"
#include "../General.h"

#define DOSPI 6.283185307179586476925286766559

using namespace std;

class Trumpet : public Instrument
{
public:
	Trumpet();
	~Trumpet();
	
	vector <double> generateNote(double duration, double pitch, double Normvelocity);

private:
	double n;
	double m;
	double io;
};