
#include <stdlib.h> // Random
#include"KarplusStrong.h"
#include "KarplusDrum.h"
#include <stdio.h>
#include <ctime>
#include <math.h>
#include "portaudio.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
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

		PaStream *stream;
		PaError err;
		wave wave2,wavekarp,wavekarpdrum; // my data structure
		//vector<double> input = genSine(TABLE_LENGTH); // wavetable with final interpolation point
		//vector<double> input(50, 0);
		//input[0] = 1;
		vector<double> input = genNoise(50,500);
		printf("PortAudio: Sine Wave, %.2f Hz.\n", FREQUENCY);

		// Initialize data for use by callback.

		wave2.x = input;

		int retardo = 10;
		double decay = 0.5;
		KarplusStrong mykarp(input, retardo, decay, 10000);
		mykarp.calcY();
		wavekarp.x = mykarp.gety();
		ofstream f("El-pijas.wav", ios::binary);
		int sample_rate = SAMPLE_RATE;

		// Write the file headers
		f << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
		write_word(f, 16, 4);  // no extension data
		write_word(f, 1, 2);  // PCM - integer samples
		write_word(f, 2, 2);  // two channels (stereo file)

		write_word(f, sample_rate, 4); //write_word(f, 44100, 4);  // samples per second (Hz)
		write_word(f, sample_rate * (2) * 2, 4); //write_word(f, 176400, 4);  // (Sample Rate * BitsPerSample * Channels) / 8

		write_word(f, 4, 2);  // data block size (size of two integer samples, one for each channel, in bytes)
		write_word(f, 16, 2);  // number of bits per sample (use a multiple of 8)

		// Write the data chunk header
		size_t data_chunk_pos = f.tellp();
		f << "data----";  // (chunk size to be filled in later)

		// Write the audio samples
		// (We'll generate a single C4 note with a sine wave, fading from left to right)
		constexpr double two_pi = TWO_PI;
		constexpr double max_amplitude = MAX_AMP;  // "volume"

		int N = sample_rate * 3;  // total number of samples
		for (int n = 0; n < N; n++)
		{
			double amplitude = (double)n / N * max_amplitude;
			double value = wavekarp.x[n*500 / sample_rate];
			write_word(f, (int)(amplitude * value), 2);
			write_word(f, (int)((max_amplitude - amplitude) * value), 2);
		}

		// (We'll need the final file size to fix the chunk sizes above)
		size_t file_length = f.tellp();

		// Fix the data chunk header to contain the data size
		f.seekp(data_chunk_pos + 4);
		write_word(f, file_length - data_chunk_pos + 8);

		// Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
		f.seekp(0 + 4);
		write_word(f, file_length - 8, 4);

		return 0;
		
	//	// Initialize library before making any other calls.
	//	err = Pa_Initialize();
	//	if (err != paNoError) goto error;

	//	// Open an audio I/O stream.
	//	err = Pa_OpenDefaultStream(
	//		&stream,
	//		0,              /* no input channels */
	//		2,              /* stereo output */
	//		paFloat32,      /* 32 bit floating point output */
	//		SAMPLE_RATE,
	//		BUFFER_SIZE,            /* frames per buffer */
	//		sineCallback,
	//		&wave2);
	//	if (err != paNoError) goto error;

	//	Pa_StartStream(stream);
	//		Pa_Sleep(NUM_SECONDS*1000.);
	//		Pa_StopStream(stream);


	//	if (err != paNoError) goto error;

	//	err = Pa_CloseStream(stream);
	//	if (err != paNoError) goto error;

	//	err = Pa_OpenDefaultStream(
	//		&stream,
	//		0,              /* no input channels */
	//		2,              /* stereo output */
	//		paFloat32,      /* 32 bit floating point output */
	//		SAMPLE_RATE,
	//		BUFFER_SIZE,            /* frames per buffer */
	//		sineCallback,
	//		&wavekarp);

	//		Pa_StartStream(stream);
	//		Pa_Sleep(NUM_SECONDS*1000.);
	//		Pa_StopStream(stream);

	//	err = Pa_CloseStream(stream);

	//	Pa_Terminate();
	//	printf("Finished.\n");

	//	return err;

	//error:
	//	Pa_Terminate();
	//	fprintf(stderr, "An error occured while using the portaudio stream.\n");
	//	fprintf(stderr, "Error number: %d\n", err);
	//	fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
	//	return err;
	}


