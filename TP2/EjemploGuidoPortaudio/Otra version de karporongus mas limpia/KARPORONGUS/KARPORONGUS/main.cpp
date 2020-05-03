
#include <stdlib.h> // Random
#include"KarplusStrong.h"
#include "KarplusDrum.h"
#include <stdio.h>
#include <ctime>
#include <math.h>
#include "portaudio.h"
#include "Utils.h"
#include <iostream>
using namespace std;



int main(void) {

		PaStream *stream;
		PaError err;
		wave wave2,wavekarp,wavekarpdrum; // my data structure
		//vector<double> input = genSine(TABLE_LENGTH); // wavetable with final interpolation point
		vector<double> input(TABLE_LENGTH, 0);
		input[0] = 1;
		printf("PortAudio: Sine Wave, %.2f Hz.\n", FREQUENCY);

		// Initialize data for use by callback.

		wave2.x = input;

		int retardo = 1;
		double decay = 0.9;
		KarplusStrong mykarp(input, retardo, decay, TABLE_LENGTH*10);
		mykarp.calcY();
		wavekarp.x = mykarp.gety();


		// Initialize library before making any other calls.
		err = Pa_Initialize();
		if (err != paNoError) goto error;

		// Open an audio I/O stream.
		err = Pa_OpenDefaultStream(
			&stream,
			0,              /* no input channels */
			2,              /* stereo output */
			paFloat32,      /* 32 bit floating point output */
			SAMPLE_RATE,
			BUFFER_SIZE,            /* frames per buffer */
			sineCallback,
			&wave2);
		if (err != paNoError) goto error;

		Pa_StartStream(stream);
			Pa_Sleep(NUM_SECONDS*1000.);
			Pa_StopStream(stream);


		if (err != paNoError) goto error;

		err = Pa_CloseStream(stream);
		if (err != paNoError) goto error;

		err = Pa_OpenDefaultStream(
			&stream,
			0,              /* no input channels */
			2,              /* stereo output */
			paFloat32,      /* 32 bit floating point output */
			SAMPLE_RATE,
			BUFFER_SIZE,            /* frames per buffer */
			sineCallback,
			&wavekarp);

			Pa_StartStream(stream);
			Pa_Sleep(NUM_SECONDS*1000.);
			Pa_StopStream(stream);

		err = Pa_CloseStream(stream);

		Pa_Terminate();
		printf("Finished.\n");

		return err;

	error:
		Pa_Terminate();
		fprintf(stderr, "An error occured while using the portaudio stream.\n");
		fprintf(stderr, "Error number: %d\n", err);
		fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
		return err;
	}