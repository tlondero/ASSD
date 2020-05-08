#include "BanjoController.h"



BanjoController::BanjoController(){

}


SynthTrack BanjoController::sytnsynthesisTrack(Tracks BanjoTrack,bool preview) {
	SynthTrack mySynthesis;
	mySynthesis.instrumentName = BanjoTrack.instrumentName;
	if (preview) {
		double time_first = 0;
		double time_last = 0;
		for (unsigned int note = 0; note < BanjoTrack.Notes.size(); note++) {
			if (time_last - time_first < 5) {
				MusicData noteData;
				noteData.t_on = BanjoTrack.Notes[note].t_on;                             // ESTO DE ACA ES DURACION DEBUG
				noteData.sound = this->banjo.generateNote(BanjoTrack.Notes[note].Duration + 0.5, BanjoTrack.Notes[note].frequency, BanjoTrack.Notes[note].velocity / 100.0, 0.5, 'G');
				mySynthesis.track.push_back(noteData);
				if (note == 0) {
					time_first = noteData.t_on;
				}
				time_last = BanjoTrack.Notes[note].t_on + BanjoTrack.Notes[note].Duration;
			}
			else {
				break;
			}
		}
	}
	else {
		for (unsigned int note = 0; note < BanjoTrack.Notes.size(); note++) {
			MusicData noteData;
			noteData.t_on = BanjoTrack.Notes[note].t_on;
			noteData.sound = this->banjo.generateNote(BanjoTrack.Notes[note].Duration, BanjoTrack.Notes[note].frequency, BanjoTrack.Notes[note].velocity / 100.0, 0.5, 'G');
			mySynthesis.track.push_back(noteData);
		}
	}

	return mySynthesis;
}
BanjoController::~BanjoController()
{
}
