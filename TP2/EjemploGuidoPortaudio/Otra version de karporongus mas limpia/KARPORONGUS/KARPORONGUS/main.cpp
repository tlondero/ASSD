
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

#
#define SAMPLE_RATE     44100
#define MAX_AMP         32760
#define TWO_PI          6.283185307179586476925286766559

using namespace std;
namespace little_endian_io
{
	template <typename Word>
	std::ostream& write_word(std::ostream& outs, Word value, unsigned size = sizeof(Word))
	{
		for (; size; --size, value >>= 8)
			outs.put(static_cast <char> (value & 0xFF));
		return outs;
	}
}
using namespace little_endian_io;

int main(void) {
	int freq[6] = { 82, 130, 164, 196, 261, 330 };
	int fs = 44100;
	double rf = 1;
	double prob =  0.5;
	int wavDuration = 180;
	int durationNote = 60;
	double delay =0 ;
	double cut = 0.3;
	double volume=800;
	Guitar myGuitar(freq[1], fs,rf);
	Guitar myGuitar2(freq[3], fs, rf);
	Drum myDrum(freq[3],fs,rf,prob);
	vector<double> DrumSound;
	vector<double> GuitarSound1 =myGuitar.composeSound(cut, durationNote,delay, wavDuration);
	vector<double> GuitarSound2 = myGuitar2.composeSound(cut, durationNote, 1, wavDuration);
	vector<double> GuitarSound;
	for (int i = 0; i < GuitarSound1.size(); i++) {
		GuitarSound.push_back(GuitarSound1[i] + GuitarSound2[i]);
	}
	makeWav(2, wavDuration, "prueba", GuitarSound,volume);
	return 0;
	}



