#include "EspectroGenerator.h"
using namespace std;
#include <string>
#include "../General.h"

//Input: .wav file path
//Returns: nothing
// An image with the name mywav.png. The name comes from the given file! e.g:\Path\mywav.wav
void EspectroGenerator::generateSpectrum(string path, int nfft,int overlap, string window,double kaiserparam,double gaussianparam,double expparam)
{
	string newWindow;
	if (window == WindowsList[0]) {
		newWindow = "triang";
	}
	else if (window == WindowsList[1]) {
		newWindow = "blackman";
	}
	else if (window == WindowsList[2]) {
		newWindow = "hanning";
	}
	else if (window == WindowsList[3]) {
		newWindow = "hamming";
	}
	else if (window == WindowsList[4]) {
		newWindow = "bartlett";
	}
	else if (window == WindowsList[5]) {
		newWindow = "blackmanharris";
	}
	else if (window == WindowsList[6]) {
		newWindow = "barthann";
	}
	else if (window == WindowsList[7]) {
		newWindow = "rectangular";
	}
	else if (window == WindowsList[8]) {
		newWindow = "gaussian";
	}
	else if (window == WindowsList[9]) {
		newWindow = "exponential";
	}
	else {
		newWindow = "kaiser";
	}

	string command = "start pythonw Espectrograma\\main.py ";
	command += path +" "+ to_string(nfft) + " " + to_string(overlap) + " " + newWindow + " " + to_string(kaiserparam) + " " + to_string(gaussianparam) +" "+ to_string(expparam);
	const char *commandPtr = command.c_str();
	system(commandPtr); //Invoke python to compute plots
}