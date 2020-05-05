#include <vector>
#include <stdlib.h> // Random
#include <stdio.h>
#include <ctime>
#include <math.h>
#include "portaudio.h"
#include "Utils.h"

int sineCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{

	/* Cast data passed through stream to the format of the local structure. */
	wave *data = (wave*)userData;

	float *out = (float*)outputBuffer;

	float y; // temp variable for output sample

	for (int i = 0; i < framesPerBuffer; i++)
	{
		y =  data->x[data->n];
		data->n += (int)data->frequency*data->x.size()*oneoversr; // increment the wave's counter
		while (data->n >= data->x.size()) data->n -= data->x.size(); // keep it in range
		*out++ = y;		/* left channel */
		*out++ = y;		/* right channel*/
	}
	return 0;
}


vector<double> genSine(int L) {
	vector<double> sine;
	for (int i = 0; i < L; i++) {
		sine.push_back(sin(TWOPI * i / L));
	}
	return sine;
}

vector<double> genNoise(int L) {

	vector<double> noise;
	for (int i = 0; i < L; i++) {
			noise.push_back(((rand()%2000-1000.0)/1000.0) * SAMPLE_RATE);
	}
	return noise;
}
