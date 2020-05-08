#pragma once
#include <string>
#include <vector>
#include "MusicData.h"
using namespace std;
class SynthTrack
{
public:
	SynthTrack();
	~SynthTrack();
	string instrumentName;
	vector<MusicData> track;
	double previewDuration;
};

