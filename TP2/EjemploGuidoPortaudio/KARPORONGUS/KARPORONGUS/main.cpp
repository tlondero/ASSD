

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
	if (myMidi.addMidi("bach_tocatta_fugue_d_minor")) {
		vector<Tracks> myTracks = myMidi.getTracks();
		double duration = myMidi.getTotalDuration();
		UserInput ui;
		UserChoice uc;
		uc.params.GuitarParam_rf = 1;
		uc.TrackInstrument = "ORGAN";
		uc.TrackNumber = 0;
		myTracks[uc.TrackNumber].userInstrumentChoice = uc.TrackInstrument;
		ui.wavName = "test_alan";
		ui.pairTrackInst.push_back(uc);
		double rf = 1;
		vector<SynthTrack> synthtrackv;
		ControllerOfControllers myCC;
		synthtrackv=myCC.sytnsynthesisProject(myTracks, ui);

		////////////////////////////////////////////////////////////////debug
		/*std::cout << "Writing debug file.." << std::endl;

		std::ofstream myfile;
		myfile.open("sintest.txt");

		for (int i = 0; i < synthtrackv[0].track.size(); i++) {
			for (int n = 0; n < synthtrackv[0].track[i].sound.size(); n++) {
				myfile << synthtrackv[0].track[i].sound[n];
				if ((i != synthtrackv[0].track.size() - 1) && (n != synthtrackv[0].track[i].sound.size() - 1)) {
					myfile << ",";
				}
			}
		}
		myfile.close();
		std::cout << "File written, press enter." << std::endl;
		getchar();*/
		//////////////////////////////////////////////////////////////////////

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
