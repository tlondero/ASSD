#pragma once
#include "../Utils/SynthTrack.h"
#include "../General.h"
#include "EcoSimple.h"
#include "Reverberator.h"
class EfectController
{public:
	EfectController();
	~EfectController();
	vector<SynthTrack> applyEfects(vector<SynthTrack> tracketeo);
	EcoSimple eco;
	Reverberator reverb;
};

