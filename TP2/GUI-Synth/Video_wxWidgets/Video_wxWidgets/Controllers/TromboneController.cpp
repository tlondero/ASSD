#include "TromboneController.h"

TromboneController::TromboneController(){

}

SynthTrack TromboneController::sytnsynthesisTrack(Tracks TromboneTrack) {
	SynthTrack mySynthesis;
	mySynthesis.instrumentName = TromboneTrack.instrumentName;

	//aca va un for por el cual se llama al instrumento con la duración de la nota, la velocity y la frecuencia,
	//lo que devuelve se guarda  en mySynth en los vectores de nota con la info del ton
	
	for (unsigned int note = 0; note < TromboneTrack.Notes.size(); note++) {

		MusicData noteData;

		noteData.t_on = TromboneTrack.Notes[note].t_on;

		noteData.sound = this->trombone.generateNote(TromboneTrack.Notes[note].Duration, TromboneTrack.Notes[note].frequency, TromboneTrack.Notes[note].velocity / 100.0);

		mySynthesis.track.push_back(noteData);
	}

	return mySynthesis;
}

TromboneController::~TromboneController(){
}
