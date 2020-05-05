#pragma once

#include <vector>

#define SAMPLE_RATE     44100
#define TWO_PI          6.283185307179586476925286766559
#define MAX_VOLUME	32760

class Organ
{
public:
	Organ(std::vector<double>harmonic_content, double A, double D, double S, double R);
	std::vector<double> generateNote(double duration, double pitch, double volume);
	~Organ();

private:
	std::vector<double>harmonic_content; //Vector con los armónicos del órgano normalizados con el primer armónico con valor 1.
	double A; //Attack
	double D; //Delay
	double R; //Recovery
	double S; //Sustain

};