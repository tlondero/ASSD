#pragma once

#include <vector>
#include <algorithm>

#define SAMPLE_RATE     44100
#define TWO_PI          6.283185307179586476925286766559
#define MAX_VOLUME	32760

class Organ
{
public:
	Organ(double sub_harmonic_count, double mix_harmonic_count = 0, double sub = 1, double fifth = 0, double primary = 0, double eight = 0, double twelveth = 0, double fifteenth = 0, double seventeenth = 0, double nineteenth = 0, double below = 0, double third = 0, double fourth = 0, double perfect_fifth = 0, double a = 0.1, double r = 0.3, double s = 0.03, double noise = 0.001);
	std::vector<double> generateNote(double duration, double pitch, double volume);
	~Organ();

private:
	
	//Constantes para el cálculo de armónicos del organo
	double sub;						//Levanta la fundamental, y los armónicos crecientes de a dos
	double fifth;					//Levanta a partir del tercer armónico crecientes de a seis
	double primary;					//Levanta una octava más arriba de la fundamental con armónicos crecientes de a cuatro
	double eighth;					//Levanta otra octava más arriba con armónicos crecientes de a ocho
	double twelveth;				//Levanta otra octava más arriba con armónicos crecientes de a doce
	double fifteenth;				//Levanta otra octava más arriba con armónicos crecientes de a quince
	double seventeenth;				//Levanta otra octava más arriba con armónicos crecientes de a diecisiete
	double nineteenth;				//Levanta otra octava más arriba con armónicos crecientes de a diecinueve
	double below;					//Levanta una octava más abajo de la fundamental
	double majorThird;	//Levanta una tercera perfecta arriba de la fundamental junto a sus armónicos
	double perfectFourth;  //Levanta una cuarta perfecta arriba de la fundamental junto a sus armónicos
	double perfectFifth;	//Levanta una quinta perfecta arriba de la fundamental junto a sus armónicos

	double sub_harmonic_count;
	double mix_harmonic_count;
	
	//Armónicos del organo
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

	double a;
	double r;
	double s;
	double noise;
};