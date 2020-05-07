#include "ClarinetController.h"

ClarinetController::ClarinetController(){

}

SynthTrack ClarinetController::sytnsynthesisTrack(Tracks ClarinetTrack) {
	SynthTrack mySynthesis;
	mySynthesis.instrumentName = ClarinetTrack.instrumentName;

	//aca va un for por el cual se llama al instrumento con la duración de la nota, la velocity y la frecuencia,
	//lo que devuelve se guarda  en mySynth en los vectores de nota con la info del ton
	
	for (unsigned int note = 0; note < ClarinetTrack.Notes.size(); note++) {

		MusicData noteData;

		noteData.t_on = ClarinetTrack.Notes[note].t_on;

		noteData.sound = this->clarinet.generateNote(ClarinetTrack.Notes[note].Duration, ClarinetTrack.Notes[note].frequency, ClarinetTrack.Notes[note].velocity / 100.0);

		mySynthesis.track.push_back(noteData);
	}

	return mySynthesis;
}

ClarinetController::~ClarinetController(){
}
