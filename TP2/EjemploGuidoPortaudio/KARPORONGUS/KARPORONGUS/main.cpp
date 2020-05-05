
#include <stdlib.h> // Random
#include "WavGen.h"
#include <stdio.h>
#include <ctime>
#include <math.h>
#include "portaudio.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
#include "Guitar.h"
#include "Drum.h"

#include "General.h"
#define MAX_AMP         32760
#define TWO_PI          6.283185307179586476925286766559

using namespace std;

int main(void) {
	int freq[6] = { 82, 130, 164, 196, 261, 330 };
	double rf = 0.9;
	double prob = 0.5;
	int durationNote = 3;
	double cut = 1;
	double volume = 1000;
	double Normvelocity = 1;
	Drum myGuitar(rf,prob);
	vector<double> GuitarSound1 = myGuitar.generateNote(durationNote,40, Normvelocity, cut);
	makeWav(2, durationNote, "RuidoUniforme", GuitarSound1, volume);
	//GuitarSound1 = myGuitar.generateNote(durationNote, freq[3], Normvelocity, cut);
	//makeWav(2, durationNote, "RuidoBinario", GuitarSound1, volume);
	//GuitarSound1 = myGuitar.generateNote(durationNote, freq[5], Normvelocity, cut);
	//makeWav(2, durationNote, "RuidoGausiano", GuitarSound1, volume);
	return 0;
}



