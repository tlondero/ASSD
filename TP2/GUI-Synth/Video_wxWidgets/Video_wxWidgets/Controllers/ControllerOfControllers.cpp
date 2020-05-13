#include "ControllerOfControllers.h"

ControllerOfControllers::ControllerOfControllers() {
}

vector<SynthTrack> ControllerOfControllers::sytnsynthesisProject(vector<Tracks> projectTracks, UserInput userData) {
	vector<SynthTrack> mySynthTrackVector;
	
	for (unsigned int track = 0; track < userData.pairTrackInst.size(); track++) {
		SynthTrack tempTrack;
		string noteborres = userData.finalEfect;
		if (userData.pairTrackInst[track].TrackInstrument == InstrumentList[0]) {
			//AGREGAR EL BOOL DE PREVIEW
			this->AGController.setParam(userData.pairTrackInst[track].params.GuitarParam_rf);
			tempTrack = this->AGController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			if (!userData.pairTrackInst[track].effect2Apply.empty()) {
				tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			}
			if (!userData.finalEfect.empty())
				tempTrack.effect2Apply = noteborres;
			tempTrack.T = userData.pairTrackInst[track].T;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.D = userData.pairTrackInst[track].D;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == InstrumentList[9]) {
			this->EGController.setParam(userData.pairTrackInst[track].params.GuitarParam_rf);
			tempTrack = this->EGController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			if (!userData.pairTrackInst[track].effect2Apply.empty()) {
				tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			}
			if (!userData.finalEfect.empty())
				tempTrack.effect2Apply = noteborres;
			tempTrack.T = userData.pairTrackInst[track].T;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.D = userData.pairTrackInst[track].D;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == InstrumentList[8]) {
			tempTrack = this->BController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			if (!userData.pairTrackInst[track].effect2Apply.empty()) {
				tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			}
			if (!userData.finalEfect.empty())
				tempTrack.effect2Apply = noteborres;
			tempTrack.T = userData.pairTrackInst[track].T;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.D = userData.pairTrackInst[track].D;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == InstrumentList[7]) {
			this->DController.setParam(userData.pairTrackInst[track].params.DrumParam_rf, userData.pairTrackInst[track].params.DrumProb);
			tempTrack = this->DController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			if (!userData.pairTrackInst[track].effect2Apply.empty()) {
				tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			}
			if (!userData.finalEfect.empty())
				tempTrack.effect2Apply = noteborres;
			tempTrack.T = userData.pairTrackInst[track].T;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.D = userData.pairTrackInst[track].D;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == InstrumentList[5]) {
			tempTrack = this->TController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			if (!userData.pairTrackInst[track].effect2Apply.empty()) {
				tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			}
			if (!userData.finalEfect.empty())
				tempTrack.effect2Apply = noteborres;
			tempTrack.T = userData.pairTrackInst[track].T;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.D = userData.pairTrackInst[track].D;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == InstrumentList[3]) {
			tempTrack = this->bellController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			if (!userData.pairTrackInst[track].effect2Apply.empty()) {
				tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			}
			if (!userData.finalEfect.empty())
				tempTrack.effect2Apply = noteborres;
			tempTrack.T = userData.pairTrackInst[track].T;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.D = userData.pairTrackInst[track].D;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == InstrumentList[4]) {
			tempTrack = this->CController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			if (!userData.pairTrackInst[track].effect2Apply.empty()) {
				tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			}
			if (!userData.finalEfect.empty())
				tempTrack.effect2Apply = noteborres;
			tempTrack.T = userData.pairTrackInst[track].T;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.D = userData.pairTrackInst[track].D;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == InstrumentList[1] || userData.pairTrackInst[track].TrackInstrument == InstrumentList[2]) {
			projectTracks[userData.pairTrackInst[track].TrackNumber].userInstrumentChoice = userData.pairTrackInst[track].TrackInstrument;
			if (userData.pairTrackInst[track].TrackInstrument == InstrumentList[1]) {
				this->OController.set_organ_param(userData.pairTrackInst[track].params.A, userData.pairTrackInst[track].params.R, userData.pairTrackInst[track].params.S);
			}
			else {
				this->OController.set_flute_param(userData.pairTrackInst[track].params.A, userData.pairTrackInst[track].params.R, userData.pairTrackInst[track].params.S);
			}
			tempTrack = this->OController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			if (!userData.pairTrackInst[track].effect2Apply.empty()) {
				tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			}
			if (!userData.finalEfect.empty())
				tempTrack.effect2Apply = noteborres;
			tempTrack.T = userData.pairTrackInst[track].T;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.D = userData.pairTrackInst[track].D;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == InstrumentList[6]) {
			tempTrack = this->TrumpController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			if (!userData.pairTrackInst[track].effect2Apply.empty()) {
				tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			}
			if (!userData.finalEfect.empty())
				tempTrack.effect2Apply = noteborres;
			tempTrack.T = userData.pairTrackInst[track].T;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.D = userData.pairTrackInst[track].D;
			mySynthTrackVector.push_back(tempTrack);
		}
		//else if (other instrument) {
		//}		
	}

	mySynthTrackVector = this->EController.applyEfects(mySynthTrackVector);

	return mySynthTrackVector;
}


ControllerOfControllers::~ControllerOfControllers() {

}
