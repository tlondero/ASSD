#pragma once
#include "../Utils/SynthTrack.h"
#include "../Instrumentos/InstrumentsPsola.h"
#include "../Utils/Tracks.h"

class ModernFlauteController
{
public:
    ModernFlauteController();
    SynthTrack sytnsynthesisTrack(Tracks FlauteTrack, bool preview);
    ~ModernFlauteController();

private:
    ModernFlautePsola flaute;
};