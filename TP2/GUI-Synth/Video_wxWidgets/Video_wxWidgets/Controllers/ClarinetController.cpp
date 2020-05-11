#include "ClarinetController.h"

ClarinetController::ClarinetController(){

}

SynthTrack ClarinetController::sytnsynthesisTrack(Tracks ClarinetTrack, bool preview) {
	SynthTrack mySynthesis;
	mySynthesis.instrumentName = ClarinetTrack.instrumentName;

	//aca va un for por el cual se llama al instrumento con la duración de la nota, la velocity y la frecuencia,
	//lo que devuelve se guarda  en mySynth en los vectores de nota con la info del ton
	if (preview) {
		double time_first = 0;
		double time_last = 0;
		for (unsigned int note = 0; note < ClarinetTrack.Notes.size(); note++) {
			if (time_last - time_first < 5) {
				MusicData noteData;
				noteData.t_on = ClarinetTrack.Notes[note].t_on;                             // ESTO DE ACA ES DURACION DEBUG
				noteData.sound = this->clarinet.generateNote(ClarinetTrack.Notes[note].Duration + 0.5, ClarinetTrack.Notes[note].frequency, ClarinetTrack.Notes[note].velocity / 100.0);
				mySynthesis.track.push_back(noteData);
				if (note == 0) {
					time_first = noteData.t_on;
				}
				time_last = ClarinetTrack.Notes[note].t_on + ClarinetTrack.Notes[note].Duration;
			}
			else {
				break;
			}
		}
		mySynthesis.previewDuration = time_last - time_first;
	}
	else {
		for (unsigned int note = 0; note < ClarinetTrack.Notes.size(); note++) {

			MusicData noteData;

			noteData.t_on = ClarinetTrack.Notes[note].t_on;

			noteData.sound = this->clarinet.generateNote(ClarinetTrack.Notes[note].Duration, ClarinetTrack.Notes[note].frequency, ClarinetTrack.Notes[note].velocity / 100.0);

			mySynthesis.track.push_back(noteData);
		}
	}
	return mySynthesis;
}

ClarinetController::~ClarinetController(){
}
