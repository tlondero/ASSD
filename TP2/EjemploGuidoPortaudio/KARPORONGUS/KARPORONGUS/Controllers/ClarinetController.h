#pragma once
#include "../Utils/SynthTrack.h"
#include "../Instrumentos/Clarinet.h"
#include "../Utils/Tracks.h"

class ClarinetController
{
public:
	ClarinetController();
	SynthTrack sytnsynthesisTrack(Tracks TromboneTrack);
	~ClarinetController();

private:
	Clarinet clarinet;
};