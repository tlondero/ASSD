#pragma once
#include <string>
#include <vector>
using namespace std;
#include "InstParams.h"
class UserChoice
{
public:
	UserChoice();
	~UserChoice();
	int TrackNumber;
	string TrackInstrument;
	bool InstrumentPreview = false;
	InstParams params;
	string effect2Apply;
//Parametros efectos.
	double D=0.9;
	double M=0;
	double T=0;
};