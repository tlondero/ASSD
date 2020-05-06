

#include "WavGen.h"
#include "General.h"
#include "Instrumentos/Banjo.h"
#include "Instrumentos/Drum.h"
#include "Instrumentos/GuitarClassic.h"
#include "Instrumentos/GuitarImproved.h"
#include "MidiParser.h"
#include "WavController.h"
#include "Utils/SynthTrack.h"
using namespace std;

int main(void) {

	MidiParser myMidi;
	if (myMidi.addMidi("sample")) {
		vector<Tracks> myTracks = myMidi.getTracks();
		int freq[6] = { 82, 130, 164, 196, 261, 330 };
		double rf = 1;
		double prob = 0.5;
		int durationNote = 3;
		double cut = 0.5;
		double volume = 1000;
		double Normvelocity = 1;
		GuitarImproved myGuitar(rf);
		vector<double> GuitarSound1 = myGuitar.generateNote(durationNote, 130, Normvelocity, cut, 'B');
		MusicData md;
		md.t_on = 0;
		md.sound = GuitarSound1;
		vector<MusicData> musicdataV;
		musicdataV.push_back(md);
		SynthTrack synthtrack;
		synthtrack.instrumentName = "Guitar";
		synthtrack.track= musicdataV;
		vector<SynthTrack> synthtrackv;
		synthtrackv.push_back(synthtrack);
		WavController myWavController(durationNote,"elpija",1000);
		myWavController.compileWav(synthtrackv);
		myWavController.makeWav();

	}
	else {
		cout << "No se encontró el archivo" << endl;
		getchar();
	}

	return 0;
}



