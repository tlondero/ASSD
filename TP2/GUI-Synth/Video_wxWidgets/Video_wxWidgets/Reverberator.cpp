#include "Reverberator.h"



Reverberator::Reverberator()
{
}

Reverberator::~Reverberator()
{
}

std::vector<double> Reverberator::applyEffect(std::vector<double> input, double T, int mix)
{

//T = 3tn/(-log|gn|) para comb paralelo

std::vector<double> g_parallel = { -0.742, -0.733, -0.715, -0.697 , -0.656};
std::vector<double> M_series = { 1051, 337 };
std::vector<double> g_series = { -0.7, -0.7 };
std::vector<double> wavVector2(input.size(), 0);
std::vector<double> temp(input.size(), 0);

std::vector<double> M_parallel = { 
									
								 };

for (int j = 0; j < M_parallel.size(); j++) {
	for (int i = 0; i < input.size(); i++) {
		if (i - M_parallel[j] > 0) {
			temp[i] = input[i] + g_parallel[j] * input[i - M_parallel[j]];
		}
		else {
			temp[i] = input[i];
		}
		wavVector2[i] += temp[i];
	}
}

for (int j = 0; j < M_series.size(); j++) {
	for (int i = 0; i < input.size(); i++) {
		if (i - M_series[j] > 0) {
			temp[i] = -1 * g_series[j] * wavVector2[i] + wavVector2[i - M_series[j]] + g_series[j] * temp[i - M_series[j]];
		}
		else {
			temp[i] = wavVector2[i];
		}
	}
	wavVector2 = temp;
}

for (int i = 0; i < input.size(); i++) {
	input[i] += mix * wavVector2[i];
}


	return std::vector<double>();
}

