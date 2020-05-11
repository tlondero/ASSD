

#include "General.h"
#include "Instrumentos/Banjo.h"
#include "Instrumentos/Drum.h"
#include "Instrumentos/GuitarClassic.h"
#include "Instrumentos/GuitarImproved.h"
#include "MidiParser.h"
#include "Controllers/WavController.h"
#include "Utils/SynthTrack.h"
#include "Controllers/AcousticGuitarController.h"
#include "Controllers/ControllerOfControllers.h"
using namespace std;

int main(void) {

	//HACER CONTROL-F Y BUSCAR "REVISAR" CAMBIE COSAS QUE NO SE SI ESTAN BIEN SDS
	//-alan


	MidiParser myMidi;
	srand(std::time(0));
	if (myMidi.addMidi("P4th_Pa4th_Pd4th.mid")) {
		vector<Tracks> myTracks = myMidi.getTracks();
		double duration = myMidi.getTotalDuration() + 1;
		ControllerOfControllers myCC;
		WavController myWavController;
		UserInput ui;
		UserChoice uc;
		double rf = 1;

		//Síntesis preview
		uc.TrackInstrument = "ORGAN";
		uc.InstrumentPreview = true;
		ui.wavName = "preview" + uc.TrackInstrument;
		uc.params.GuitarParam_rf = 1;
		uc.TrackNumber = 0;
		myTracks[uc.TrackNumber].userInstrumentChoice = uc.TrackInstrument;
		ui.pairTrackInst.push_back(uc);
		vector<SynthTrack> synthtrack_preview;
		synthtrack_preview = myCC.sytnsynthesisProject(myTracks, ui);
		myWavController.compileWav(synthtrack_preview, myMidi.getTotalDuration()+1, ui.wavName, 20000);
		myWavController.makeWav();
		ui.pairTrackInst.clear();

		//Síntesis total
		//uc.params.GuitarParam_rf = 1;

		//uc.TrackInstrument = "ORGAN";
		//uc.TrackNumber = 0;
		//myTracks[uc.TrackNumber].userInstrumentChoice = uc.TrackInstrument;
		//ui.wavName = "twinkle";
		//ui.pairTrackInst.push_back(uc);
		//vector<SynthTrack> synthtrackv;
		//synthtrackv=myCC.sytnsynthesisProject(myTracks, ui);
		//myWavController.compileWav(synthtrackv, duration+1, ui.wavName, 1000);
		//myWavController.makeWav();
		//ui.pairTrackInst.clear();
	}
	else {
		cout << "No se encontró el archivo" << endl;
		getchar();
	}

	return 0;
}
