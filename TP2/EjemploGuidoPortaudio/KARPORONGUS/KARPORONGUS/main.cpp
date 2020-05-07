

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

	MidiParser myMidi;
	if (myMidi.addMidi("twinkle")) {
		vector<Tracks> myTracks = myMidi.getTracks();
		double duration = myMidi.getTotalDuration();
		UserInput ui;
		UserChoice uc;
		uc.params.GuitarParam_rf = 1;
		uc.TrackInstrument = "CLARINET";
		uc.TrackNumber = 0;
		ui.wavName = "TomiTwinkle";
		ui.pairTrackInst.push_back(uc);
		double rf = 1;
		vector<SynthTrack> synthtrackv;
		ControllerOfControllers myCC;
		synthtrackv=myCC.sytnsynthesisProject(myTracks, ui);
		WavController myWavController(duration,ui.wavName,1000);
		myWavController.compileWav(synthtrackv);
		myWavController.makeWav();
	}
	else {
		cout << "No se encontró el archivo" << endl;
		getchar();
	}

	return 0;
}
