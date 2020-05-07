#pragma once
#include "../Utils/SynthTrack.h"
#include "../Instrumentos/GuitarImproved.h"
#include "../Utils/Tracks.h"
class ElectricGuitarController
{
public:
	ElectricGuitarController();
	void setParam(double rf);
	SynthTrack sytnsynthesisTrack(Tracks GuitarTrack);
	~ElectricGuitarController();
private:
	GuitarImproved Guitar;


};

