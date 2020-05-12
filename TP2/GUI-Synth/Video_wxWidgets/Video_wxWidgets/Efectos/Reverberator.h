#pragma once
#include "../General.h"
#include <vector>
class Reverberator
{
public:
	Reverberator();
	~Reverberator();
	std::vector<double> applyEffect(std::vector<double> input, double T, double mix);
};

