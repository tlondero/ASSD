#pragma once
#include "../Utils/SynthTrack.h"
#include "../Instrumentos/Drum.h"
#include "../Utils/Tracks.h"
class DrumController
{
public:
	DrumController();
	SynthTrack sytnsynthesisTrack(Tracks GuitarTrack);
	void setParam(double rf, double prob);
	~DrumController();
private:
	Drum drum;


};

