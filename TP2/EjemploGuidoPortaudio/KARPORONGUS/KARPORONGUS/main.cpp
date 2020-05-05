#include <vector>
#include <stdlib.h> // Random
#include"KarplusStrong.h"
#include <stdio.h>
#include <ctime>
#include <math.h>
#include "portaudio.h"
#define NUM_SECONDS (0.5)
#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (64)
#ifndef M_PI
#define M_PI (3.14159265)
#endif
#define TABLE_SIZE (1000000)
using namespace std;

typedef struct
{
	vector<double> x;
	int left_phase = 0;
	int right_phase = 0;
	char message[20];
}
paTestData;





vector<double> genSine(int N) {
	vector<double> sine;
	for (int i = 0; i< N; i++) {
		sine.push_back(sin(2 * M_PI * i / N));
	}
	return sine;
}

vector<double> genNoise(int N) {
	srand((unsigned) time(NULL));
	vector<double> noise;
	for (int i = 0; i < N; i++) {
		noise.push_back(rand() / (double)RAND_MAX);
	}
	return noise;
}


/* This routine will be called by the PortAudio engine when audio is needed.
67 ** It may called at interrupt level on some machines so don't do anything
68 ** that could mess up the system like calling malloc() or free().
69 */
static int patestCallback(const void *inputBuffer, void *outputBuffer,
                             unsigned long framesPerBuffer,
                             const PaStreamCallbackTimeInfo* timeInfo,
                             PaStreamCallbackFlags statusFlags,
                             void *userData)
 {
     paTestData *data = (paTestData*)userData;
     float *out = (float*)outputBuffer;
     unsigned long i;

     (void)timeInfo; /* Prevent unused variable warnings. */
     (void)statusFlags;
     (void)inputBuffer;

     for (i = 0; i < framesPerBuffer; i++)
     {
		 * out++ = data->x[data->left_phase];  /* left */	
		* out++ = data->x[data->right_phase];  /* right */
         data->left_phase += 1;
         if (data->left_phase >= TABLE_SIZE) data->left_phase -= TABLE_SIZE;
         data->right_phase += 1; /* higher pitch so we can distinguish left and right. */
         if (data->right_phase >= TABLE_SIZE) data->right_phase -= TABLE_SIZE;
     }
     return paContinue;
}
/*
98  * This routine is called by portaudio when playback is done.
99  */
static void StreamFinished(void* userData)
 {
    paTestData *data = (paTestData *)userData;
    printf("Stream Completed: %s\n", data->message);
}

 /*******************************************************************/
int main(void);
int main(void)
{
PaStreamParameters outputParameters;
    PaStream *stream;
	PaStream *stream2;
    PaError err;
    paTestData data,data2;

	vector<double> input = genSine(TABLE_SIZE);
	//vector<double> input(TABLE_SIZE, 0);
	//input[0] = 1;
	//vector<double> input = genNoise(TABLE_SIZE);
	KarplusStrong mykarp(input, 100, 0.5);
	mykarp.calcY();
    
	int i;
    printf("PortAudio Test: output sine wave. SR = %d, BufSize = %d\n", SAMPLE_RATE, FRAMES_PER_BUFFER);
    /* initialise sinusoidal wavetable */
	data.x = input;
	data2.x = mykarp.gety();
 
	
	err = Pa_Initialize();

    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */

  outputParameters.channelCount = 2;       /* stereo output */
     outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
   outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
   outputParameters.hostApiSpecificStreamInfo = NULL;
   // STREAM 1
    Pa_OpenStream( & stream, NULL, & outputParameters,   SAMPLE_RATE,     FRAMES_PER_BUFFER, paClipOff  , patestCallback,& data);
    Pa_StartStream(stream);
	printf("Play track of noise %d seconds.\n", NUM_SECONDS);
	Pa_Sleep(NUM_SECONDS * 1000);
	err = Pa_StopStream(stream);
	err = Pa_CloseStream(stream);
// STREAM 2
	Pa_OpenStream(&stream2, NULL, &outputParameters, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, patestCallback, &data2);
	Pa_StartStream(stream2);

  printf("Play track passed by the synth for %d seconds.\n", NUM_SECONDS);
		Pa_Sleep(NUM_SECONDS * 1000);


  err = Pa_StopStream(stream2);
  err = Pa_CloseStream(stream2);


	     Pa_Terminate();
	     printf("Test finished.\n");
	
		    return err;

}
//vector<double> genSine(int N);
//
//int main(void) {
//
//	//vector<double> delta(100,0);
//	//delta[0] = 1;
//	vector<double> mysin = genSine(100);
////	vector<double> input = mysin;
//	KarplusStrong mykarp(input,100,1);
//	mykarp.calcY();
//	//for (int i = 0; i < 20e10; i++)
//		cout << '\a';
//	cout << "Input: ";
//	for (int i = 0; i < input.size(); i++)
//		cout << input[i] << ',';
//	cout << endl;
//	cout << "Output: ";
//	for (int i = 0; i < mykarp.gety().size(); i++)
//		cout << mykarp.gety()[i] << ',';
//	while (toupper(getchar()) != 'Q');
//
//	return 1;
//}
//
//
