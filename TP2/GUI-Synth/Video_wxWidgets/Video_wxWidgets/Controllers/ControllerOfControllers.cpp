#include "ControllerOfControllers.h"

ControllerOfControllers::ControllerOfControllers(){
}

vector<SynthTrack> ControllerOfControllers::sytnsynthesisProject(vector<Tracks> projectTracks, UserInput userData) {
	vector<SynthTrack> mySynthTrackVector;
	for (unsigned int track = 0; track < userData.pairTrackInst.size(); track++) {
		SynthTrack tempTrack;
		if (userData.pairTrackInst[track].TrackInstrument == InstrumentList[0]) {
			//AGREGAR EL BOOL DE PREVIEW
			this->AGController.setParam(userData.pairTrackInst[track].params.GuitarParam_rf);
			tempTrack = this->AGController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			tempTrack.g = userData.pairTrackInst[track].g;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.treverb = userData.pairTrackInst[track].treverb;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == InstrumentList[9]) {
			this->EGController.setParam(userData.pairTrackInst[track].params.GuitarParam_rf);
			tempTrack = this->EGController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			tempTrack.g = userData.pairTrackInst[track].g;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.treverb = userData.pairTrackInst[track].treverb;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == InstrumentList[8]) {
			tempTrack = this->BController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			tempTrack.g = userData.pairTrackInst[track].g;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.treverb = userData.pairTrackInst[track].treverb;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == InstrumentList[7]) {
			this->DController.setParam(userData.pairTrackInst[track].params.DrumParam_rf, userData.pairTrackInst[track].params.DrumProb);
			tempTrack = this->DController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			tempTrack.g = userData.pairTrackInst[track].g;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.treverb = userData.pairTrackInst[track].treverb;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == InstrumentList[5]) {
			tempTrack = this->TController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			tempTrack.g = userData.pairTrackInst[track].g;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.treverb = userData.pairTrackInst[track].treverb;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == InstrumentList[3]) {
			tempTrack = this->bellController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber],userData.pairTrackInst[track].InstrumentPreview);
			tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			tempTrack.g = userData.pairTrackInst[track].g;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.treverb = userData.pairTrackInst[track].treverb;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == InstrumentList[4]) {
			tempTrack = this->CController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			tempTrack.g = userData.pairTrackInst[track].g;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.treverb = userData.pairTrackInst[track].treverb;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == InstrumentList[1] || userData.pairTrackInst[track].TrackInstrument == InstrumentList[2]) {
			projectTracks[userData.pairTrackInst[track].TrackNumber].userInstrumentChoice = userData.pairTrackInst[track].TrackInstrument;
			tempTrack = this->OController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			tempTrack.g = userData.pairTrackInst[track].g;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.treverb = userData.pairTrackInst[track].treverb;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == InstrumentList[6]) {
			tempTrack = this->TrumpController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			tempTrack.g = userData.pairTrackInst[track].g;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.treverb = userData.pairTrackInst[track].treverb;
			mySynthTrackVector.push_back(tempTrack);
		}
		//else if (other instrument) {
		//}
	}
	mySynthTrackVector = this->EController.applyEfects(mySynthTrackVector);

	return mySynthTrackVector;
}


ControllerOfControllers::~ControllerOfControllers(){
}
