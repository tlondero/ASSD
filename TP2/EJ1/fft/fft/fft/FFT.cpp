#include "FFT.h"
#include <iostream>
using namespace std;
#define PI 3.141592653589793238462643383279502884
#define THRESHOLD 10e-16

MyFFT::MyFFT() {
};
MyFFT::~MyFFT() {
};
bool MyFFT::fft(complex<double> *in, complex<double> *out, int N) {
	double nlog = std::log2(N);
	if (nlog == int(nlog)) {
		vector<complex<double>> fout;
		for (int i = 0; i < N; i++) {
			fout.push_back(in[i]);
		}
		this->fftr(fout);
		for (unsigned int i = 0; i < fout.size(); i++) {
			out[i] = fout[i];
			if (std::abs(out[i].imag()) < THRESHOLD) { out[i]._Val[1] = 0; }
			if (std::abs(out[i].real()) < THRESHOLD) { out[i]._Val[0] = 0; }
		}
		return true;
	}
	else {
		return false;
	}

};
void MyFFT::ifft(complex<double> *in, std::complex<double> *out, int N) {
};
void MyFFT::fftr(std::vector<std::complex<double>>& x) {
	if (x.size() == 1) { return; }//Caso base
	else {
		int N = x.size(); 
		vector<complex<double>> xpar;
		vector<complex<double>> ximpar;
		for (int i = 0; i < N / 2; i++) {
			xpar.push_back((x[2*i]));
			ximpar.push_back(x[2 * i + 1]);
		}
		this->fftr(xpar);
		this->fftr(ximpar);
		for (int i = 0; i < N/2; i++) {
			std::complex<double> W = exp(std::complex<double>(0, -2 *PI  * i / N)) * ximpar[i];
			x[i] = xpar[i] + W;
			x[N / 2 + i] = xpar[i] - W;
		}
	}
};
