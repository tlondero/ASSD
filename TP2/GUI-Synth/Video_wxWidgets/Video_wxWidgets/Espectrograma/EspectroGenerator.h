#pragma once
#include <iostream>
using namespace std;
class EspectroGenerator
{
public:
	void generateSpectrum(string path, int nfft, int overlap, string window, double kaiserparam, double gaussianparam, double expparam); //Genera el par de plots espectograma y tiempo.
	//path-> path a tu wav  nfft-> Tamaño de la ventana (POTENCIA DE DOS). overlap-> Potencia de 2. window, 
	//TIPO DE VENTANA 
	/*
	triang
blackman
hamming
hanning
bartlett
blackmanharris
barthann
kaiser (needs beta)->kaiserparam
gaussian (needs standard deviation)->gaussianparam
exponential (needs decay scale)->expparam
rectangular
	*/
};

/*
int main(void) {
	EspectroGenerator es;
	es.generateSpectrum("twinkle.wav",256,128,"hamming",0,0,0);
}
*/