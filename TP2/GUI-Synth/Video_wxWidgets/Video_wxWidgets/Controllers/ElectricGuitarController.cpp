#include "ElectricGuitarController.h"



ElectricGuitarController::ElectricGuitarController(){

}
void ElectricGuitarController::setParam(double rf) {
	this->Guitar.setParam(rf);
}

SynthTrack ElectricGuitarController::sytnsynthesisTrack(Tracks GuitarTrack, bool preview) {
	SynthTrack mySynthesis;
	mySynthesis.instrumentName = GuitarTrack.instrumentName;
	//aca va un for por el cual se llama a la guitarra con la duración de la nota, la velocity y la frecuencia, lo que devuelve la guitarra se guarda  en mySynth en los vectores de nota con la info del ton
	if (preview) {
		double time_first = 0;
		double time_last = 0;
		for (unsigned int note = 0; note < GuitarTrack.Notes.size(); note++) {
			if (time_last - time_first < 5) {
				MusicData noteData;
				noteData.t_on = GuitarTrack.Notes[note].t_on;                             // ESTO DE ACA ES DURACION DEBUG
				noteData.sound = this->Guitar.generateNoteElectric(GuitarTrack.Notes[note].Duration + 0.5, GuitarTrack.Notes[note].frequency, GuitarTrack.Notes[note].velocity / 100.0, 0.5, 'G');
				mySynthesis.track.push_back(noteData);
				if (note == 0) {
					time_first = noteData.t_on;
				}
				time_last = GuitarTrack.Notes[note].t_on + GuitarTrack.Notes[note].Duration;
			}
			else {
				break;
			}
		}
		mySynthesis.previewDuration = time_last - time_first;
	}
	else {
		for (unsigned int note = 0; note < GuitarTrack.Notes.size(); note++) {

			MusicData noteData;
			noteData.t_on = GuitarTrack.Notes[note].t_on;
			noteData.sound = this->Guitar.generateNoteElectric(GuitarTrack.Notes[note].Duration, GuitarTrack.Notes[note].frequency, GuitarTrack.Notes[note].velocity / 100.0, 0.5, 'G');
			mySynthesis.track.push_back(noteData);
		}
	}

	return mySynthesis;
}
ElectricGuitarController::~ElectricGuitarController()
{
}
