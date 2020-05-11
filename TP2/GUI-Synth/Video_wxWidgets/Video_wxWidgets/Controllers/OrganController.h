#pragma once
#include "../Utils/SynthTrack.h"
#include "../Utils/Tracks.h"
#include "../Instrumentos/Organ.h"
#include "../General.h"

class OrganController
{
public:
	OrganController();
	SynthTrack sytnsynthesisTrack(Tracks Track, bool preview);
	~OrganController();
private:
	Organ organ;
	Organ flute;
};

