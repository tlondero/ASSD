#pragma once
//#define SAMPLE_RATE (44100.)
//#define TABLE_LENGTH 1024
//#define BUFFER_SIZE 256
//#define TWOPI (6.283185307179586)
//#define NUM_SECONDS  (0.75)
//#define FREQUENCY (620.)
//#define MAX_AMP (0.5)
#include <vector>
//#include<portaudio.h>
#include <stdlib.h> 
using namespace std;
//typedef struct {
//	float	frequency = FREQUENCY;
//	float	amplitude = MAX_AMP;;
//	float	phase = 0;
//	vector<double>	x;
//	int	n = 0;
//} wave; // data to pass to callback function
//
//const float oneoversr = 1. / SAMPLE_RATE;
//
//// This routine will be called by the PortAudio engine when audio is needed.
//int sineCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);
//vector<double> genSine(int N);
//vector<double> genNoise(int L);