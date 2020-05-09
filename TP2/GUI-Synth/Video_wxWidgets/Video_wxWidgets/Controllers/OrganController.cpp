#include "OrganController.h"



OrganController::OrganController()
{
	this->flute.set_parameters(
		2, //Subharmonic count
		2, //Mixharmonic count
		0.1,  //Sub
		1e-10,  //Fifth
		1,  //Primary
		1e-15,  //Eighth
		1e-5,  //Twelveth
		0,  //Fifteenth
		0,  //Seventeenth
		0,  //Nineteenth
		0.01,  //Below
		0.001,  //Major Third
		0.000001,  //Perfect Fourth
		0,  //Perfect Fifth
		0.05, //Attack
		0.4,  //sustain
		0.05, ////sustain oscillation
		0.000005 //Noise factor
	);

	this->organ.set_parameters(


		2, //Subharmonic count
		3, //Mixharmonic count
		0.8,  //Sub
		0.6,  //Fifth
		0.9,  //Primary
		0.7,  //Eighth
		0.6,  //Twelveth
		0.5,  //Fifteenth
		0.4,  //Seventeenth
		0.7,  //Nineteenth
		0.6,  //Below
		0.002,  //Major Third
		0.00001,  //Perfect Fourth
		0.00005,  //Perfect Fifth
		0.05, //Attack
		0.90,  //Recovery
		0.01,
		0.002);//Noise factor
}

SynthTrack OrganController::sytnsynthesisTrack(Tracks Track) {
	SynthTrack mySynthesis;
	mySynthesis.instrumentName = Track.instrumentName;
	//aca va un for por el cual se llama a la guitarra con la duración de la nota, la velocity y la frecuencia, lo que devuelve la guitarra se guarda  en mySynth en los vectores de nota con la info del ton
	if (Track.userInstrumentChoice == "ORGAN") {
		for (unsigned int note = 0; note < Track.Notes.size(); note++) {
			MusicData noteData;
			noteData.t_on = Track.Notes[note].t_on;
			noteData.sound = this->organ.generateNote(Track.Notes[note].Duration + 0.5, Track.Notes[note].frequency, Track.Notes[note].velocity / 100.0);
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
	return mySynthesis;
}

SynthTrack OrganController::sytnsynthesisPreview(Tracks Track) {
	SynthTrack mySynthesis;
	mySynthesis.instrumentName = Track.instrumentName;
	double time_first = 0;
	//aca va un for por el cual se llama a la guitarra con la duración de la nota, la velocity y la frecuencia, lo que devuelve la guitarra se guarda  en mySynth en los vectores de nota con la info del ton
	if (Track.userInstrumentChoice == "ORGAN") {
		double extra_reverb_time = 0.5;
		double time_last = 0;
		for (unsigned int note = 0; note < Track.Notes.size(); note++) {
			if (time_last - time_first < 5) {
				MusicData noteData;
				noteData.t_on = Track.Notes[note].t_on - time_first;
				noteData.sound = this->organ.generateNote(Track.Notes[note].Duration + extra_reverb_time, Track.Notes[note].frequency, Track.Notes[note].velocity / 100.0);
				mySynthesis.track.push_back(noteData);
				if (note == 0) {
					time_first = noteData.t_on;
				}
				time_last = Track.Notes[note].t_on + Track.Notes[note].Duration + extra_reverb_time;
			}
			else {
				break;
			}
		}
		mySynthesis.previewDuration = (time_last - time_first);
	}
	if (Track.userInstrumentChoice == "FLUTE") {
		double extra_reverb_time = 0.2;
		double time_last = 0;
		for (unsigned int note = 0; note < Track.Notes.size(); note++) {
			if (time_last - time_first < 5) {
				MusicData noteData;
				noteData.t_on = Track.Notes[note].t_on - time_first;
				noteData.sound = this->flute.generateNote(Track.Notes[note].Duration + extra_reverb_time, Track.Notes[note].frequency, Track.Notes[note].velocity / 100.0);
				mySynthesis.track.push_back(noteData);
				if (note == 0) {
					time_first = noteData.t_on;
				}
				time_last = Track.Notes[note].t_on + Track.Notes[note].Duration + extra_reverb_time;
			}
			else {
				break;
			}
		}

		mySynthesis.previewDuration = time_last - time_first;
	}
	return mySynthesis;
}

OrganController::~OrganController()
{
}