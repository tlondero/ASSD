#include "DrumController.h"



DrumController::DrumController(){

}
void DrumController::setParam(double rf, double prob) {
	this->drum.setParams(rf,prob);
}

SynthTrack DrumController::sytnsynthesisTrack(Tracks DrumTrack) {
	SynthTrack mySynthesis;
	mySynthesis.instrumentName = DrumTrack.instrumentName;

	for (unsigned int note = 0; note < DrumTrack.Notes.size(); note++) {
		MusicData noteData;
		noteData.t_on = DrumTrack.Notes[note].t_on;
		noteData.sound = this->drum.generateNote(DrumTrack.Notes[note].Duration, ((int)(DrumTrack.Notes[note].frequency)%100)+20, DrumTrack.Notes[note].velocity / 100.0,0.5);
		mySynthesis.track.push_back(noteData);
	}
	return mySynthesis;
}
DrumController::~DrumController()
{
}
