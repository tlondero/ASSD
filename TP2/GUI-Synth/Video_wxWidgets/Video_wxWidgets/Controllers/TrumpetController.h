#pragma once
#include "../Utils/SynthTrack.h"
#include "../Instrumentos/Trumpet.h"
#include "../Utils/Tracks.h"

class TrumpetController
{
public:
	TrumpetController();
	SynthTrack sytnsynthesisTrack(Tracks TrumpetTrack);
	~TrumpetController();

private:
	Trumpet trumpet;
};