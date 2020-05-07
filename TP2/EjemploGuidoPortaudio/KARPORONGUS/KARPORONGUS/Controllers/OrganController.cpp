#include "OrganController.h"



OrganController::OrganController()
{
	this->flute.set_parameters(
		2, //Subharmonic count
		3, //Mixharmonic count
		1,  //Sub
		1e-10,  //Fifth
		1e-4,  //Primary
		1e-15,  //Eighth
		1e-5,  //Twelveth
		0,  //Fifteenth
		0,  //Seventeenth
		0,  //Nineteenth
		0.005,  //Below
		0.001,  //Major Third
		0.000001,  //Perfect Fourth
		0,  //Perfect Fifth
		0.1, //Attack
		0.3,  //sustain
		0.03, ////sustain oscillation
		0.000005 //Noise factor
	);

	this->organ.set_parameters(

		4, //Subharmonic count
		3,		//Mixharmonic count
		0.5,  //Sub
		0.4,  //Fifth
		0.8,  //Primary
		0.6,  //Eighth
		0.5,  //Twelveth
		0.6,  //Fifteenth
		0.7,  //Seventeenth
		0.8,  //Nineteenth
		0.8,  //Below
		0.1,  //Major Third
		0,		//Perfect Fourth
		0,		//Perfect Fifth
		0.15,	//attack
		0.6,	//release
		0.00001, //sustain oscillation
		0.02
	);
}

SynthTrack OrganController::sytnsynthesisTrack(Tracks Track) {
	SynthTrack mySynthesis;
	mySynthesis.instrumentName = Track.instrumentName;
	//aca va un for por el cual se llama a la guitarra con la duración de la nota, la velocity y la frecuencia, lo que devuelve la guitarra se guarda  en mySynth en los vectores de nota con la info del ton
	if (Track.userInstrumentChoice == "ORGAN") {
		for (unsigned int note = 0; note < Track.Notes.size(); note++) {
			MusicData noteData;
			noteData.t_on = Track.Notes[note].t_on;
			noteData.sound = this->organ.generateNote(Track.Notes[note].Duration, Track.Notes[note].frequency, Track.Notes[note].velocity / 100.0);
			mySynthesis.track.push_back(noteData);
		}
	}
	if (Track.userInstrumentChoice == "FLUTE") {
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