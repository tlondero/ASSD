#pragma once
#include <vector>
#include "Instrument.h"
#include "General.h"

#define DOSPI 6.283185307179586476925286766559

using namespace std;

class Clarinet : public Instrument
{
public:
	Clarinet();
	~Clarinet();
	
	vector <double> generateNote(double duration, double pitch, double Normvelocity);

private:
	double n;
	double m;
	double tau;
	double io;
};