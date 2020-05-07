#include "TrumpetController.h"

TrumpetController::TrumpetController(){

}

SynthTrack TrumpetController::sytnsynthesisTrack(Tracks TrumpetTrack) {
	SynthTrack mySynthesis;
	mySynthesis.instrumentName = TrumpetTrack.instrumentName;

	//aca va un for por el cual se llama al instrumento con la duración de la nota, la velocity y la frecuencia,
	//lo que devuelve se guarda  en mySynth en los vectores de nota con la info del ton
	
	for (unsigned int note = 0; note < TrumpetTrack.Notes.size(); note++) {

		MusicData noteData;

		noteData.t_on = TrumpetTrack.Notes[note].t_on;

		noteData.sound = this->trumpet.generateNote(TrumpetTrack.Notes[note].Duration, TrumpetTrack.Notes[note].frequency, TrumpetTrack.Notes[note].velocity / 100.0);

		mySynthesis.track.push_back(noteData);
	}

	return mySynthesis;
}

TrumpetController::~TrumpetController(){
}
