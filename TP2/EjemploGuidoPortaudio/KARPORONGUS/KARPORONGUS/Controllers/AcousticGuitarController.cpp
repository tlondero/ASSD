#include "AcousticGuitarController.h"
#include <algorithm>


AcousticGuitarController::AcousticGuitarController(){

}
void AcousticGuitarController::setParam(double rf) {
	this->Guitar.setParam(rf);
}

SynthTrack AcousticGuitarController::sytnsynthesisTrack(Tracks GuitarTrack,bool scaleFreq) {
	SynthTrack mySynthesis;
	mySynthesis.instrumentName = GuitarTrack.instrumentName;

	//aca va un for por el cual se llama a la guitarra con la duración de la nota, la velocity y la frecuencia, lo que devuelve la guitarra se guarda  en mySynth en los vectores de nota con la info del ton
	for (unsigned int note = 0; note < GuitarTrack.Notes.size(); note++) {
		MusicData noteData;
		noteData.t_on = GuitarTrack.Notes[note].t_on;                             // ESTO DE ACA ES DURACION DEBUG
		noteData.sound = this->Guitar.generateNote(GuitarTrack.Notes[note].Duration+0.5, GuitarTrack.Notes[note].frequency, GuitarTrack.Notes[note].velocity / 100.0,0.5,'G');
		mySynthesis.track.push_back(noteData);
	}
	return mySynthesis;
}
AcousticGuitarController::~AcousticGuitarController()
{
}
