

#include "WavGen.h"
#include "General.h"
#include "Utils.h"


#include "Instrumentos/Banjo.h"
#include "Instrumentos/Drum.h"
#include "Instrumentos/GuitarClassic.h"
#include "Instrumentos/GuitarImproved.h"
#include "MidiParser.h"

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
		makeWav(2, durationNote, "Guitar", GuitarSound1, volume);
	}
	else {
		cout << "No se encontró el archivo" << endl;
		getchar();
	}

	return 0;
}



