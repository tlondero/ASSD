#include <vector>
#include <stdlib.h> // Random
#include"KarplusStrong.h"
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


vector<double> genSine(int N) {
	vector<double> sine;
	for (int i = 0; i < N; i++) {
		sine.push_back(sin(TWOPI * i / N));
	}
	sine.push_back(0);
	return sine;
}

vector<double> genNoise(int N, int active) {

	vector<double> noise;
	for (int i = 0; i < N; i++) {
		if (i < active)
			noise.push_back(rand() / (double)RAND_MAX);
		else
			noise.push_back(0);
	}
	noise.push_back(0);
	return noise;
}
