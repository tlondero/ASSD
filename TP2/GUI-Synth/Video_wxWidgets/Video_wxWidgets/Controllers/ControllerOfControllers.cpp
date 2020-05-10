#include "ControllerOfControllers.h"

ControllerOfControllers::ControllerOfControllers(){
}

vector<SynthTrack> ControllerOfControllers::sytnsynthesisProject(vector<Tracks> projectTracks, UserInput userData) {
	vector<SynthTrack> mySynthTrackVector;
	for (unsigned int track = 0; track < userData.pairTrackInst.size(); track++) {
		SynthTrack tempTrack;
		if (userData.pairTrackInst[track].TrackInstrument == "GUITAR") {
			//AGREGAR EL BOOL DE PREVIEW
			this->AGController.setParam(userData.pairTrackInst[track].params.GuitarParam_rf);
			tempTrack = this->AGController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			tempTrack.g = userData.pairTrackInst[track].g;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.treverb = userData.pairTrackInst[track].treverb;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == "ELECTRIC_GUITAR") {
			this->EGController.setParam(userData.pairTrackInst[track].params.GuitarParam_rf);
			tempTrack = this->EGController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			tempTrack.g = userData.pairTrackInst[track].g;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.treverb = userData.pairTrackInst[track].treverb;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == "BANJO") {
			tempTrack = this->BController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			tempTrack.g = userData.pairTrackInst[track].g;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.treverb = userData.pairTrackInst[track].treverb;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == "DRUM") {
			this->DController.setParam(userData.pairTrackInst[track].params.DrumParam_rf, userData.pairTrackInst[track].params.DrumProb);
			tempTrack = this->DController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			tempTrack.g = userData.pairTrackInst[track].g;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.treverb = userData.pairTrackInst[track].treverb;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == "TROMBONE") {
			tempTrack = this->TController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			tempTrack.g = userData.pairTrackInst[track].g;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.treverb = userData.pairTrackInst[track].treverb;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == "BELL") {
			tempTrack = this->bellController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber],userData.pairTrackInst[track].InstrumentPreview);
			tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			tempTrack.g = userData.pairTrackInst[track].g;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.treverb = userData.pairTrackInst[track].treverb;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == "CLARINET") {
			tempTrack = this->CController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			tempTrack.g = userData.pairTrackInst[track].g;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.treverb = userData.pairTrackInst[track].treverb;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == "ORGAN" || userData.pairTrackInst[track].TrackInstrument == "FLUTE") {
			projectTracks[userData.pairTrackInst[track].TrackNumber].userInstrumentChoice = userData.pairTrackInst[track].TrackInstrument;
			tempTrack = this->OController.sytnsynthesisTrack(projectTracks[userData.pairTrackInst[track].TrackNumber], userData.pairTrackInst[track].InstrumentPreview);
			tempTrack.effect2Apply = userData.pairTrackInst[track].effect2Apply;
			tempTrack.g = userData.pairTrackInst[track].g;
			tempTrack.M = userData.pairTrackInst[track].M;
			tempTrack.treverb = userData.pairTrackInst[track].treverb;
			mySynthTrackVector.push_back(tempTrack);
		}
		else if (userData.pairTrackInst[track].TrackInstrument == "TRUMPET") {
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
