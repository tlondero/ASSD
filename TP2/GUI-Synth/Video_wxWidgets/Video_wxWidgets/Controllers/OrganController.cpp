#include "OrganController.h"



OrganController::OrganController()
{
}

SynthTrack OrganController::sytnsynthesisTrack(Tracks Track, bool preview) {
	SynthTrack mySynthesis;
	if (!preview) {
		mySynthesis.instrumentName = Track.instrumentName;
		//aca va un for por el cual se llama a la guitarra con la duración de la nota, la velocity y la frecuencia, lo que devuelve la guitarra se guarda  en mySynth en los vectores de nota con la info del ton
		if (Track.userInstrumentChoice == InstrumentList[1]) {
			for (unsigned int note = 0; note < Track.Notes.size(); note++) {
				MusicData noteData;
				noteData.t_on = Track.Notes[note].t_on;
				noteData.sound = this->organ.generateNote(Track.Notes[note].Duration + 0.5, Track.Notes[note].frequency, Track.Notes[note].velocity / 100.0);
				mySynthesis.track.push_back(noteData);
			}
		}
		if (Track.userInstrumentChoice == InstrumentList[2]) {
			for (unsigned int note = 0; note < Track.Notes.size(); note++) {
				MusicData noteData;
				noteData.t_on = Track.Notes[note].t_on;
				noteData.sound = this->flute.generateNote(Track.Notes[note].Duration, Track.Notes[note].frequency, Track.Notes[note].velocity / 100.0);
				mySynthesis.track.push_back(noteData);
			}
		}
	}
	else {
		mySynthesis.instrumentName = Track.instrumentName;
		double time_first = 0;
		//aca va un for por el cual se llama a la guitarra con la duración de la nota, la velocity y la frecuencia, lo que devuelve la guitarra se guarda  en mySynth en los vectores de nota con la info del ton
		if (Track.userInstrumentChoice == "ORGAN") {
			double time_last = 0;
			for (unsigned int note = 0; note < Track.Notes.size(); note++) {
				if (time_last - time_first < 5) {
					MusicData noteData;
					noteData.t_on = Track.Notes[note].t_on - time_first;
					noteData.sound = this->organ.generateNote(Track.Notes[note].Duration, Track.Notes[note].frequency, Track.Notes[note].velocity / 100.0);
					mySynthesis.track.push_back(noteData);
					if (note == 0) {
						time_first = noteData.t_on;
					}
					time_last = Track.Notes[note].t_on + Track.Notes[note].Duration;
				}
				else {
					break;
				}
			}
			mySynthesis.previewDuration = (time_last - time_first);
		}
		if (Track.userInstrumentChoice == "FLUTE") {
			double time_last = 0;
			for (unsigned int note = 0; note < Track.Notes.size(); note++) {
				if (time_last - time_first < 5) {
					MusicData noteData;
					noteData.t_on = Track.Notes[note].t_on - time_first;
					noteData.sound = this->flute.generateNote(Track.Notes[note].Duration, Track.Notes[note].frequency, Track.Notes[note].velocity / 100.0);
					mySynthesis.track.push_back(noteData);
					if (note == 0) {
						time_first = noteData.t_on;
					}
					time_last = Track.Notes[note].t_on + Track.Notes[note].Duration;
				}
				else {
					break;
				}
			}

			mySynthesis.previewDuration = time_last - time_first;
		}
	}
	return mySynthesis;
}

void OrganController::set_organ_param(double a, double s, double r)
{
	this->organ.set_parameters(

		2, //Subharmonic count
		3, //Mixharmonic count
		0.8,  //Sub
		0.6,  //Fifth
		0.9,  //Primary
		0.7,  //Eighth
		0.6,  //Twelveth
		0.5,  //Fifteenth
		0.5,  //Seventeenth
		0.7,  //Nineteenth
		0.8,  //Below
		0.002,  //Major Third
		0.00001,  //Perfect Fourth
		0.00005,  //Perfect Fifth
		a, //Attack
		r,  //Recovery
		s,
		0.002);//Noise factor
	
}

void OrganController::set_flute_param(double a, double s, double r)
{
	this->flute.set_parameters(

		2, //Subharmonic count
		2, //Mixharmonic count
		0.3,  //Sub
		0.001,  //Fifth
		0.6,  //Primary
		0.001,  //Eighth
		0.002,  //Twelveth
		0.1,  //Fifteenth
		0,  //Seventeenth
		0,  //Nineteenth
		0.001,  //Below
		0.0001,  //Major Third
		0.0001,  //Perfect Fourth
		0.001,  //Perfect Fifth
		a, //Attack
		r,  //sustain
		s, //realeasr
		0.001 //Noise factor

	);
}

OrganController::~OrganController()
{
}