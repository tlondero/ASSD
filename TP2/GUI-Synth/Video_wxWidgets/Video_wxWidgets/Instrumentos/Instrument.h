#pragma once
#include <vector>

class Instrument
{
public:
	Instrument();
	~Instrument();
	std::vector<double> generateNote(double duration, double pitch, double velocity);
};

