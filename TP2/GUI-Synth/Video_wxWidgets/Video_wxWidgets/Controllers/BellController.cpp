#include "BellController.h"

BellController::BellController(){

}

SynthTrack BellController::sytnsynthesisTrack(Tracks BellTrack) {
	SynthTrack mySynthesis;
	mySynthesis.instrumentName = BellTrack.instrumentName;

	//aca va un for por el cual se llama al instrumento con la duración de la nota, la velocity y la frecuencia,
	//lo que devuelve se guarda  en mySynth en los vectores de nota con la info del ton
	
	for (unsigned int note = 0; note < BellTrack.Notes.size(); note++) {

		MusicData noteData;

		noteData.t_on = BellTrack.Notes[note].t_on;

		noteData.sound = this->bell.generateNote(BellTrack.Notes[note].Duration, BellTrack.Notes[note].frequency, BellTrack.Notes[note].velocity / 100.0);

		mySynthesis.track.push_back(noteData);
	}

	return mySynthesis;
}

BellController::~BellController(){
}
