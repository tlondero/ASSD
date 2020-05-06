

#include "WavGen.h"
#include "General.h"
#include "Instrumentos/Banjo.h"
#include "Instrumentos/Drum.h"
#include "Instrumentos/GuitarClassic.h"
#include "Instrumentos/GuitarImproved.h"
#include "MidiParser.h"
#include "WavController.h"
#include "Utils/SynthTrack.h"
#include "AcousticGuitarController.h"
#include "ControllerOfControllers.h"
using namespace std;

int main(void) {

	MidiParser myMidi;
	if (myMidi.addMidi("twinkle")) {

		vector<Tracks> myTracks = myMidi.getTracks();
		double duration = myMidi.getTotalDuration();
		UserInput ui;
		UserChoice uc;
		uc.params.GuitarParam_rf = 1;
		uc.TrackInstrument = "GUITAR";
		uc.TrackNumber = 0;
		ui.wavName = "twinkle";
		ui.pairTrackInst.push_back(uc);
		double rf = 1;
		vector<SynthTrack> synthtrackv;
		ControllerOfControllers myCC;
		synthtrackv=myCC.sytnsynthesisProject(myTracks, ui);
		WavController myWavController(duration,"twinkle",1000);
		myWavController.compileWav(synthtrackv);
		myWavController.makeWav();

	}
	else {
		cout << "No se encontró el archivo" << endl;
		getchar();
	}

	return 0;
}



//test de GuitarCOntroller
		//Tracks testTrack;
		//testTrack.instrumentName = "Guitar";
		//Note tstn1;
		//Note tstn2;
		//tstn1.Duration = 2;
		//tstn1.frequency = 130;
		//tstn1.t_on = 0;
		//tstn1.velocity = 100;
		//tstn2.Duration = 2;
		//tstn2.frequency = 330;
		//tstn2.t_on = 2;
		//tstn2.velocity = 100;
		//testTrack.Notes.push_back(tstn1);
		//testTrack.Notes.push_back(tstn2);
		//AcousticGuitarController myGC;
		//myGC.setParam(rf);
		//synthtrackv.push_back(myGC.sytnsynthesisTrack(testTrack));