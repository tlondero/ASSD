#pragma once
#include "../Utils/SynthTrack.h"
#include "../Instrumentos/Bell.h"
#include "../Utils/Tracks.h"

class BellController
{
public:
	BellController();
	SynthTrack sytnsynthesisTrack(Tracks BellTrack, bool preview);
	~BellController();

private:
	Bell bell;
};