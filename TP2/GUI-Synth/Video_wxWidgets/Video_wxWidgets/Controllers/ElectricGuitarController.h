#pragma once
#include "../Utils/SynthTrack.h"
#include "../Instrumentos/GuitarImproved.h"
#include "../Utils/Tracks.h"
class ElectricGuitarController
{
public:
	ElectricGuitarController();
	void setParam(double rf);
	SynthTrack sytnsynthesisTrack(Tracks GuitarTrack, bool preview);
	~ElectricGuitarController();
private:
	GuitarImproved Guitar;


};

