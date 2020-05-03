
#include <stdlib.h> // Random
#include "WavGen.h"
#include <stdio.h>
#include <ctime>
#include <math.h>
#include "portaudio.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
#include "String.h"
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
	double rf = 0.7;
	int seconds = 2;
	String mystring1(freq[0], fs);
	String mystring2(freq[3], fs);
	vector<double> GuitarSound;
	for (int i = 0; i < seconds*fs; i++) {
		GuitarSound.push_back(mystring1.getSample()+mystring2.getSample());
	}
	makeWav(2, seconds, "putardo", GuitarSound);
	return 0;
	}


