#include "ControllerOfControllers.h"



ControllerOfControllers::ControllerOfControllers(){
}
vector<SynthTrack> ControllerOfControllers::sytnsynthesisProject(vector<Tracks> projectTracks, UserInput userData) {
	vector<SynthTrack> mySynthTrackVector;
	for (unsigned int track = 0; track < userData.pairTrackInst.size(); track++) {
		if (userData.pairTrackInst[track].TrackInstrument == "GUITAR") {
			
			this->AGController.setParam(userData.pairTrackInst[track].params.GuitarParam_rf);
			mySynthTrackVector.push_back(this->AGController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber]));
		}
		else if (userData.pairTrackInst[track].TrackInstrument == "ELECTRIC_GUITAR") {
			this->EGController.setParam(userData.pairTrackInst[track].params.GuitarParam_rf);
			mySynthTrackVector.push_back(this->EGController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber]));
		}
		else if (userData.pairTrackInst[track].TrackInstrument == "BANJO") {
			mySynthTrackVector.push_back(this->BController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber]));
		}
		else if (userData.pairTrackInst[track].TrackInstrument == "DRUM") {
			this->DController.setParam(userData.pairTrackInst[track].params.DrumParam_rf, userData.pairTrackInst[track].params.DrumProb);
			mySynthTrackVector.push_back(this->DController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber]));
		}
		//else if (other instrument) {
		//}
	}
	return mySynthTrackVector;
}

ControllerOfControllers::~ControllerOfControllers(){
}
