#pragma once
#include "../Utils/SynthTrack.h"
#include "../Utils/Tracks.h"
#include "../Instrumentos/Organ.h"

class OrganController
{
public:
	OrganController();
	SynthTrack sytnsynthesisTrack(Tracks Track);
	~OrganController();
private:
	Organ organ;
	Organ flute;
};

