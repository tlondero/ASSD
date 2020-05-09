#include "DrumController.h"



DrumController::DrumController(){

}
void DrumController::setParam(double rf, double prob) {
	this->drum.setParams(rf,prob);
}

SynthTrack DrumController::sytnsynthesisTrack(Tracks DrumTrack,bool preview) {
	SynthTrack mySynthesis;
	mySynthesis.instrumentName = DrumTrack.instrumentName;
	if (preview) {
		double time_first = 0;
		double time_last = 0;
		for (unsigned int note = 0; note < DrumTrack.Notes.size(); note++) {
			if (time_last - time_first < 5) {
				MusicData noteData;
				noteData.t_on = DrumTrack.Notes[note].t_on;                             // ESTO DE ACA ES DURACION DEBUG
				noteData.sound = this->drum.generateNote(DrumTrack.Notes[note].Duration + 0.5, DrumTrack.Notes[note].frequency, DrumTrack.Notes[note].velocity / 100.0, 0.5);
				mySynthesis.track.push_back(noteData);
				if (note == 0) {
					time_first = noteData.t_on;
				}
				time_last = DrumTrack.Notes[note].t_on + DrumTrack.Notes[note].Duration;
			}
			else {
				break;
			}
		}
	}
	else {
		for (unsigned int note = 0; note < DrumTrack.Notes.size(); note++) {
			MusicData noteData;
			noteData.t_on = DrumTrack.Notes[note].t_on;
			noteData.sound = this->drum.generateNote(DrumTrack.Notes[note].Duration, ((int)(DrumTrack.Notes[note].frequency) % 100) + 20, DrumTrack.Notes[note].velocity / 100.0, 0.5);
			mySynthesis.track.push_back(noteData);
		}
	}

	return mySynthesis;
}
DrumController::~DrumController()
{
}
