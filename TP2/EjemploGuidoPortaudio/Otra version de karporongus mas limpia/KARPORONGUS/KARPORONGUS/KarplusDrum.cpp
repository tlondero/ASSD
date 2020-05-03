#include "KarplusDrum.h"
#include "Utils.h"
#include <ctime>
using namespace std;
int getrand(int b);

//// Getters
std::vector<double>  KarplusDrum::gety() {
	return this->y;
}
int KarplusDrum::getPitch() {
	return this->pitch;
}
double KarplusDrum::getDecay() {
	return this->decay;
}
std::vector<double> KarplusDrum::getInput() {
	return this->x;
}

///// Setters
void KarplusDrum::setPitch(int M) {
	this->pitch = M;
}
void KarplusDrum::setDecay(double alfa) {
	this->decay = alfa;
}
void KarplusDrum::setInput(std::vector<double> input) {
	this->y.clear();
	this->x.clear();
	this->x = input;
}
//constructor.


KarplusDrum::~KarplusDrum()
{
}


KarplusDrum::KarplusDrum(std::vector<double> input, int pitch, double decay) {
	srand((unsigned)time(NULL));
	this->pitch = pitch;
	this->decay = decay;
	this->x = input;
}

/// calculo del karplus strong
void KarplusDrum::calcY(void) {
	this->y.clear();
	this->y.push_back(x[0] / 2);
	for (int i = 1; i < this->x.size(); i++) {
		int prob = getrand((int)(this->b * 100));

		if (i < this->pitch) {
			//cuenta con y nulo
			this->y.push_back(prob*((x[i] / 2) + x[i - 1] / 2));
		}
		else if (i == this->pitch) {
			this->y.push_back(prob*(((x[i] + y[i - this->pitch] * this->decay) / 2) + (((x[i]) / 2))));
		}
		else {
			//aca hago la cuenta con y(n-l) no nulo
			this->y.push_back(prob*(((x[i] + y[i - this->pitch] * this->decay) / 2) + (((x[i] + y[i - this->pitch - 1] * this->decay) / 2))));
		}
	}
}

int getrand(int b) {
	if (rand() % 100 < b)
		return 1;
	else return -1;
}