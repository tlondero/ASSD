#include "TromboneController.h"

TromboneController::TromboneController(){

}

SynthTrack TromboneController::sytnsynthesisTrack(Tracks TromboneTrack, bool preview) {
	SynthTrack mySynthesis;
	mySynthesis.instrumentName = TromboneTrack.instrumentName;

	//aca va un for por el cual se llama al instrumento con la duración de la nota, la velocity y la frecuencia,
	//lo que devuelve se guarda  en mySynth en los vectores de nota con la info del ton
	
	if (preview) {
		double time_first = 0;
		double time_last = 0;
		for (unsigned int note = 0; note < TromboneTrack.Notes.size(); note++) {
			if (time_last - time_first < 5) {
				MusicData noteData;
				noteData.t_on = TromboneTrack.Notes[note].t_on;                             // ESTO DE ACA ES DURACION DEBUG
				noteData.sound = this->trombone.generateNote(TromboneTrack.Notes[note].Duration + 0.5, TromboneTrack.Notes[note].frequency, TromboneTrack.Notes[note].velocity / 100.0);
				mySynthesis.track.push_back(noteData);
				if (note == 0) {
					time_first = noteData.t_on;
				}
				time_last = TromboneTrack.Notes[note].t_on + TromboneTrack.Notes[note].Duration;
			}
			else {
				break;
			}
		}
		mySynthesis.previewDuration = time_last - time_first;
	}
	else {
		for (unsigned int note = 0; note < TromboneTrack.Notes.size(); note++) {

			MusicData noteData;

			noteData.t_on = TromboneTrack.Notes[note].t_on;

			noteData.sound = this->trombone.generateNote(TromboneTrack.Notes[note].Duration, TromboneTrack.Notes[note].frequency, TromboneTrack.Notes[note].velocity / 100.0);

			mySynthesis.track.push_back(noteData);
		}
	}
	return mySynthesis;
}

TromboneController::~TromboneController(){
}
