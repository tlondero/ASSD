#pragma once
#include "../Utils/SynthTrack.h"
#include "../Instrumentos/InstrumentsPsola.h"
#include "../Utils/Tracks.h"

class SaxoPsolaController
{
public:
    SaxoPsolaController();
    SynthTrack sytnsynthesisTrack(Tracks TrumpetTrack, bool preview);
    ~SaxoPsolaController();

private:
    SaxoPsola saxo;
};