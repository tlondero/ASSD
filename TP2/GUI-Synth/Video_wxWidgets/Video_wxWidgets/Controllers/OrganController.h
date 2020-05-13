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
	void set_organ_param(double a, double r, double s);
	void set_flute_param(double a, double r, double s);
	~OrganController();
private:
	Organ organ;
	Organ flute;
};

