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
		//else if (other instrument) {
		//}
	}
	return mySynthTrackVector;
}

ControllerOfControllers::~ControllerOfControllers(){
}
