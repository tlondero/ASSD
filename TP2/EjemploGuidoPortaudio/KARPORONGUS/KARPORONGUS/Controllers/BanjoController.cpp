#include "BanjoController.h"



BanjoController::BanjoController(){

}


SynthTrack BanjoController::sytnsynthesisTrack(Tracks BanjoTrack) {
	SynthTrack mySynthesis;
	mySynthesis.instrumentName = BanjoTrack.instrumentName;

	for (unsigned int note = 0; note < BanjoTrack.Notes.size(); note++) {
		MusicData noteData;
		noteData.t_on = BanjoTrack.Notes[note].t_on;
		noteData.sound = this->banjo.generateNote(BanjoTrack.Notes[note].Duration, BanjoTrack.Notes[note].frequency, BanjoTrack.Notes[note].velocity / 100.0,0.5,'G');
		mySynthesis.track.push_back(noteData);
	}
	return mySynthesis;
}
BanjoController::~BanjoController()
{
}
