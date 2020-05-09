#pragma once
#include "../Utils/SynthTrack.h"
#include "../Instrumentos/Bell.h"
#include "../Utils/Tracks.h"

class BellController
{
public:
	BellController();
	SynthTrack sytnsynthesisTrack(Tracks BellTrack);
	~BellController();

private:
	Bell bell;
};