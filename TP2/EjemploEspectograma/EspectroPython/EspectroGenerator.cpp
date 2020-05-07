#include "EspectroGenerator.h"
//Input: .wav file path
//Returns: nothing
// An image with the name mywav.png. The name comes from the given file! e.g:\Path\mywav.wav
void EspectroGenerator::generateSpectrum(string path)
{
	string command = "python main.py ";
	command += path;
	const char *commandPtr = command.c_str();
	system(commandPtr); //Invoke python to compute plots
}

