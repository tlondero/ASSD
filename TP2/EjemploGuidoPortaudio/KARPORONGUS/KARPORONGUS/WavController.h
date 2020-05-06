#pragma once
#include "Utils/SynthTrack.h"
#include "General.h"
#include <string>
class WavController
{
public:
	WavController(double duration_,string wavName_);
	~WavController();
	void compileWav(vector<SynthTrack> allTracks);
	void makeWav();
private:
	vector<double> wavVector;
	string wavName;
	double duration;

};

