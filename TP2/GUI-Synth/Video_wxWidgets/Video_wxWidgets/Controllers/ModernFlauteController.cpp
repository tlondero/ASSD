#include "ModernFlauteController.h"

ModernFlauteController::ModernFlauteController()
{
}

SynthTrack ModernFlauteController::sytnsynthesisTrack(Tracks FlauteTrack, bool preview)
{
    SynthTrack mySynthesis;
    mySynthesis.instrumentName = FlauteTrack.instrumentName;

    //aca va un for por el cual se llama al instrumento con la duraci�n de la nota, la velocity y la frecuencia,
    //lo que devuelve se guarda  en mySynth en los vectores de nota con la info del ton
    if (preview)
    {
        double time_first = 0;
        double time_last = 0;
        for (unsigned int note = 0; note < FlauteTrack.Notes.size(); note++)
        {
            if (time_last - time_first < 5)
            {
                MusicData noteData;
                noteData.t_on = FlauteTrack.Notes[note].t_on; // ESTO DE ACA ES DURACION DEBUG
                noteData.sound = this->flaute.generateNote(FlauteTrack.Notes[note].frequency, FlauteTrack.Notes[note].Duration, FlauteTrack.Notes[note].velocity / 100.0);
                mySynthesis.track.push_back(noteData);
                if (note == 0)
                {
                    time_first = noteData.t_on;
                }
                time_last = FlauteTrack.Notes[note].t_on + FlauteTrack.Notes[note].Duration;
            }
            else
            {
                break;
            }
        }
        mySynthesis.previewDuration = time_last - time_first;
    }
    else
    {
        for (unsigned int note = 0; note < FlauteTrack.Notes.size(); note++)
        {

            MusicData noteData;

            noteData.t_on = FlauteTrack.Notes[note].t_on;

            noteData.sound = this->flaute.generateNote(FlauteTrack.Notes[note].frequency, FlauteTrack.Notes[note].Duration, FlauteTrack.Notes[note].velocity / 100.0);

            mySynthesis.track.push_back(noteData);
        }
    }
    return mySynthesis;
}

ModernFlauteController::~ModernFlauteController()
{
}
