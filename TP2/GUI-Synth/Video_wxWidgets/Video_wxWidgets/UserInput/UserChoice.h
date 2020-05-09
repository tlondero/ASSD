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
};