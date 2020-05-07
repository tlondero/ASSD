#include "OrganController.h"



OrganController::OrganController()
{
}

SynthTrack OrganController::sytnsynthesisTrack(Tracks Track) {
	SynthTrack mySynthesis;
	mySynthesis.instrumentName = Track.instrumentName;
	//aca va un for por el cual se llama a la guitarra con la duración de la nota, la velocity y la frecuencia, lo que devuelve la guitarra se guarda  en mySynth en los vectores de nota con la info del ton
	if (Track.instrumentName == "organ") {
		for (unsigned int note = 0; note < Track.Notes.size(); note++) {
			MusicData noteData;
			noteData.t_on = Track.Notes[note].t_on;
			noteData.sound = this->organ.generateNote(Track.Notes[note].Duration, Track.Notes[note].frequency, Track.Notes[note].velocity / 100.0);
			mySynthesis.track.push_back(noteData);
		}
	}
	if (Track.instrumentName == "flute") {
		for (unsigned int note = 0; note < Track.Notes.size(); note++) {
			MusicData noteData;
			noteData.t_on = Track.Notes[note].t_on;
			noteData.sound = this->flute.generateNote(Track.Notes[note].Duration, Track.Notes[note].frequency, Track.Notes[note].velocity / 100.0);
			mySynthesis.track.push_back(noteData);
		}
	}
//	if (Track.instrumentName == "") {
//
//	}
	return mySynthesis;
}

OrganController::~OrganController()
{
}