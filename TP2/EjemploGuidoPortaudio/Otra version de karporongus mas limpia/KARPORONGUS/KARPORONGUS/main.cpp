
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
	int durationNote = 3;
	double cut = 1;
	double volume=800;
	double Normvelocity=1;
	Guitar myGuitar;
	vector<double> GuitarSound1 = myGuitar.composeSound(cut,durationNote,freq[5],fs,rf, Normvelocity);
	vector<double> GuitarSound2 = myGuitar.composeSound(cut, durationNote, freq[2], fs, rf, Normvelocity);
	GuitarSound1.insert(GuitarSound1.end(), GuitarSound2.begin(), GuitarSound2.end());
	makeWav(2, durationNote*2, "velocity-low", GuitarSound1,volume);
	return 0;
	}



