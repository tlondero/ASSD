#pragma once

#include <vector>

#define SAMPLE_RATE     44100
#define TWO_PI          6.283185307179586476925286766559
#define MAX_VOLUME	32760

class Organ
{
public:
	Organ(std::vector<double>harmonic_content, std::vector<double>undertone_content, double A, double D, double S, double R);
	std::vector<double> generateNote(double duration, double pitch, double volume);
	~Organ();

private:
	
	//Componentes armónicas del organo
	double sub;						//Levanta la fundamental, y los armónicos crecientes de a dos
	double fifth;					//Levanta a partir del tercer armónico crecientes de a seis
	double primary;					//Levanta una octava más arriba de la fundamental con armónicos crecientes de a cuatro
	double eighth;					//Levanta otra octava más arriba con armónicos crecientes de a ocho
	double twelveth;				//Levanta otra octava más arriba con armónicos crecientes de a doce
	double fifteenth;				//Levanta otra octava más arriba con armónicos crecientes de a quince
	double seventeenth;				//Levanta otra octava más arriba con armónicos crecientes de a diecisiete
	double nineteenth;				//Levanta otra octava más arriba con armónicos crecientes de a diecinueve
	double below;					//Levanta una octava más abajo de la fundamental
	double perfectThirdComponent;	//Levanta una tercera perfecta arriba de la fundamental junto a sus armónicos
	double perfectFourthComponent;  //Levanta una cuarta perfecta arriba de la fundamental junto a sus armónicos
	double perfectFifthComponent;	//Levanta una quinta perfecta arriba de la fundamental junto a sus armónicos
	
	double A; //Attack
	double D; //Delay
	double R; //Recovery
	double S; //Sustain

};