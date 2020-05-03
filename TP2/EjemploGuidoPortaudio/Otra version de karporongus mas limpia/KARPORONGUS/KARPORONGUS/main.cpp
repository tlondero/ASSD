
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
using namespace std;

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
	int seconds = 10;
	double volume=800;
	Guitar myGuitar(freq[1], fs,rf);
	vector<double> GuitarSound;
	Drum myDrum(freq[3],fs,rf,prob);
	vector<double> DrumSound;
	for (int i = 0; i < seconds*fs/2; i++) {
		GuitarSound.push_back(myGuitar.getSample());
	}
	makeWav(2, seconds, "prueba", GuitarSound,volume);
	return 0;
	}



