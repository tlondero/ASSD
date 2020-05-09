#include "BellController.h"

BellController::BellController(){

}

SynthTrack BellController::sytnsynthesisTrack(Tracks BellTrack, bool preview) {
	SynthTrack mySynthesis;
	mySynthesis.instrumentName = BellTrack.instrumentName;

	//aca va un for por el cual se llama al instrumento con la duración de la nota, la velocity y la frecuencia,
	//lo que devuelve se guarda  en mySynth en los vectores de nota con la info del ton
	
	if (preview) {
		double time_first = 0;
		double time_last = 0;
		for (unsigned int note = 0; note < BellTrack.Notes.size(); note++) {
			if (time_last - time_first < 5) {
				MusicData noteData;
				noteData.t_on = BellTrack.Notes[note].t_on;                             // ESTO DE ACA ES DURACION DEBUG
				noteData.sound = this->bell.generateNote(BellTrack.Notes[note].Duration + 0.5, BellTrack.Notes[note].frequency, BellTrack.Notes[note].velocity / 100.0);
				mySynthesis.track.push_back(noteData);
				if (note == 0) {
					time_first = noteData.t_on;
				}
				time_last = BellTrack.Notes[note].t_on + BellTrack.Notes[note].Duration;
			}
			else {
				break;
			}
		}
		mySynthesis.previewDuration = time_last - time_first;
	}
	else {
		for (unsigned int note = 0; note < BellTrack.Notes.size(); note++) {

			MusicData noteData;

			noteData.t_on = BellTrack.Notes[note].t_on;

			noteData.sound = this->bell.generateNote(BellTrack.Notes[note].Duration, BellTrack.Notes[note].frequency, BellTrack.Notes[note].velocity / 100.0);

			mySynthesis.track.push_back(noteData);
		}
	}

	return mySynthesis;
}

BellController::~BellController(){
}
