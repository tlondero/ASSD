#pragma once

#include <cmath>
#include <complex>
#include <vector>

class MyFFT {
public:
	MyFFT();
	~MyFFT();
	bool fft(std::complex<double> *in, std::complex<double> *out,int N);
	void ifft(std::complex<double> *in, std::complex<double> *out, int N);
private:
	void fftr(std::vector<std::complex<double>>& x);
};

