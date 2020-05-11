#pragma once
#include "../General.h"
#include <vector>
using namespace std;
class EcoSimple
{
public:
	EcoSimple();
	~EcoSimple();
	vector<double> applyEffect(vector<double> input, double T, double D);
	//g va entre 0 y 1  POSITIVO, el cambio de singo lo hago adentro,Valor tipico 0.7
	//M es le retardo. valor tipico 10000
};

