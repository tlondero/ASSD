#include "EspectroGenerator.h"
using namespace std;
#include <string>
//Input: .wav file path
//Returns: nothing
// An image with the name mywav.png. The name comes from the given file! e.g:\Path\mywav.wav
void EspectroGenerator::generateSpectrum(string path, int nfft,int overlap, string window,double kaiserparam,double gaussianparam,double expparam)
{
	string command = "python Espectrograma\\main.py ";
	command += path +" "+ to_string(nfft) + " " + to_string(overlap) + " " + window + " " + to_string(kaiserparam) + " " + to_string(gaussianparam) +" "+ to_string(expparam);
	const char *commandPtr = command.c_str();
	system(commandPtr); //Invoke python to compute plots
}

