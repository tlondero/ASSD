#pragma once

#include <vector>

#define SAMPLE_RATE     44100
#define TWO_PI          6.283185307179586476925286766559
#define MAX_VOLUME	32760

class Organ
{
public:
	Organ(double sub, double fifth, double primary, double eight, double twelveth, double fifteenth, double seventeenth, double nineteenth, double below, double third, double fourth, double perfect_fifth, int sub_harmonic_count, int mix_harmonic_count, double A = 0.05, double D = 0, double S = 0.75, double R = 0.2);
	std::vector<double> generateNote(double duration, double pitch, double volume);
	~Organ();

private:
	
	//Constantes para el c�lculo de arm�nicos del organo
	double sub;						//Levanta la fundamental, y los arm�nicos crecientes de a dos
	double fifth;					//Levanta a partir del tercer arm�nico crecientes de a seis
	double primary;					//Levanta una octava m�s arriba de la fundamental con arm�nicos crecientes de a cuatro
	double eighth;					//Levanta otra octava m�s arriba con arm�nicos crecientes de a ocho
	double twelveth;				//Levanta otra octava m�s arriba con arm�nicos crecientes de a doce
	double fifteenth;				//Levanta otra octava m�s arriba con arm�nicos crecientes de a quince
	double seventeenth;				//Levanta otra octava m�s arriba con arm�nicos crecientes de a diecisiete
	double nineteenth;				//Levanta otra octava m�s arriba con arm�nicos crecientes de a diecinueve
	double below;					//Levanta una octava m�s abajo de la fundamental
	double majorThird;	//Levanta una tercera perfecta arriba de la fundamental junto a sus arm�nicos
	double perfectFourth;  //Levanta una cuarta perfecta arriba de la fundamental junto a sus arm�nicos
	double perfectFifth;	//Levanta una quinta perfecta arriba de la fundamental junto a sus arm�nicos

	int sub_harmonic_count;
	int mix_harmonic_count;
	
	//Arm�nicos del organo
	std::vector<double> sub_harmonics;
	std::vector<double> fifth_harmonics;
	std::vector<double> primary_harmonics;
	std::vector<double> eighth_harmonics;
	std::vector<double> twelveth_harmonics;
	std::vector<double> fifteenth_harmonics;
	std::vector<double> seventeenth_harmonics;
	std::vector<double> nineteenth_harmonics;
	std::vector<double> below_harmonics;
	std::vector<double> major_third_harmonics;
	std::vector<double> perfect_fourth_harmonics;
	std::vector<double> perfect_fifth_harmonics;

};