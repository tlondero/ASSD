#pragma once
#include <iostream>
using namespace std;
class EspectroGenerator
{	public:
	void generateSpectrum(string path, int nfft, int overlap, string window, double kaiserparam, double gaussianparam, double expparam); //Genera el par de plots espectograma y tiempo.

};

