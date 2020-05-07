#pragma once
#include "../Utils/SynthTrack.h"
#include "../Instrumentos/Banjo.h"
#include "../Utils/Tracks.h"
class BanjoController
{
public:
	BanjoController();
	SynthTrack sytnsynthesisTrack(Tracks GuitarTrack);
	~BanjoController();
private:
	Banjo banjo;


};

