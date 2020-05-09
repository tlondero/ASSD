#pragma once
#include "../Utils/SynthTrack.h"
#include "../Instrumentos/Trombone.h"
#include "../Utils/Tracks.h"

class TromboneController
{
public:
	TromboneController();
	SynthTrack sytnsynthesisTrack(Tracks TromboneTrack, bool preview);
	~TromboneController();

private:
	Trombone trombone;
};