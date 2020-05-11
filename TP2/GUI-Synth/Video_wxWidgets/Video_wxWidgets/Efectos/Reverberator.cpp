#include "Reverberator.h"



Reverberator::Reverberator()
{
}

Reverberator::~Reverberator()
{
}

std::vector<double> Reverberator::applyEffect(std::vector<double> input, double T, int mix)
{

//T = 3tn/(-log|gn|) para comb paralelo del paper de Schröder, asimismo resto de los valores fueron sacados del paper.

std::vector<double> M_series = { 1051, 337 };
std::vector<double> g_series = { -0.7, -0.7 };
std::vector<double> M_parallel = { 0.108820861, 0.113356009, 0.1224263038, 0.1315419501 , 0.1408843537 };
std::vector<double> g_parallel;

for (int i = 0; i < T * SAMPLE_RATE; i++) {
	input.push_back(0);
}

std::vector<double> wavVector2(input.size(), 0);
std::vector<double> temp(input.size(), 0);

for (int i = 0; i < M_parallel.size(); i++) {
	g_parallel.push_back(-1*pow(10, (-3*M_parallel[i])/(T)));
}

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


	return input;
}

