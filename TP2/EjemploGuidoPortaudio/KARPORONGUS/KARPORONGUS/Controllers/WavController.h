#pragma once
#include "../Utils/SynthTrack.h"
#include <algorithm>
#include "../General.h"
#include <string>
class WavController
{
public:
	WavController(double duration_,string wavName_,double volume_);
	~WavController();
	void compileWav(vector<SynthTrack> allTracks);
	void makeWav();
	double volume;
private:
	vector<double> wavVector;
	string wavName;
	double duration;

};

