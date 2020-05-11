#pragma once
#include "../Utils/SynthTrack.h"
#include "../Instrumentos/GuitarImproved.h"
#include "../Utils/Tracks.h"
class AcousticGuitarController
{
public:
	AcousticGuitarController();
	void setParam(double rf);
	SynthTrack sytnsynthesisTrack(Tracks GuitarTrack, bool preview);
	~AcousticGuitarController();
private:
	GuitarImproved Guitar;
};

