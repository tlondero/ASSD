#include <vector>
#include <iostream>
#include <algorithm>
#include"FFT.h"
using namespace std;

void main(void) {
	complex<double> in[8] = { {1, 0},{2, 0},{0,0},{2,0},{1,0},{3,0},{1,0},{3,0} };
	complex<double> out[8];
	int N = 8;
	MyFFT mfft;
	mfft.fft(&(in[0]), &(out[0]),N);
	cout << "Input:" << endl;
	for (int i = 0; i < N; i++) {
		cout << in[i];
	}
	cout << endl << "FFT:" << endl;
	for (int i = 0; i < N; i++) {
		cout << out[i];
	}

}
