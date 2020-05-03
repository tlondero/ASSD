#include "KarplusStrong.h"
using namespace std;


//// Getters
std::vector<double>  KarplusStrong::gety() {
	return this->y;
}
int KarplusStrong::getPitch() {
	return this->pitch;
}
double KarplusStrong::getDecay() {
	return this->decay;
}
std::vector<double> KarplusStrong::getInput() {
	return this->x;
}

///// Setters
void KarplusStrong::setPitch(int M) {
	this->pitch = M;
}
void KarplusStrong::setDecay(double alfa) {
	this->decay = alfa;
}
void KarplusStrong::setInput(std::vector<double> input) {
	this->y.clear();
	this->x.clear();
	this->x = input;

}
//constructor.
KarplusStrong::KarplusStrong()
{
}


KarplusStrong::~KarplusStrong()
{
}


KarplusStrong::KarplusStrong(std::vector<double> input, int pitch, double decay,int TotalSamples) {
	this->pitch = pitch;
	this->decay = decay;
	this->x = input;
	this->N = TotalSamples;
}

/// calculo del karplus strong
void KarplusStrong::calcY(void) {
	this->y.clear();
	this->y.push_back(x[0] / 2);
	for (int i = 1; i < this->N; i++) {
		if (i < this->x.size()) {
			if (i < this->pitch) {
				//cuenta con y nulo
				this->y.push_back((x[i] / 2) + x[i - 1] / 2);
			}
			else if (i == this->pitch) {
				this->y.push_back(((x[i] + y[i - this->pitch] * this->decay) / 2) + (((x[i]) / 2)));
			}
			else {
				//aca hago la cuenta con y(n-l) no nulo
				this->y.push_back(((x[i] + y[i - this->pitch] * this->decay) / 2) + (((x[i] + y[i - this->pitch - 1] * this->decay) / 2)));
			}
		}
		else {
			this->y.push_back((( y[i - this->pitch] * this->decay) / 2) + (( y[i - this->pitch - 1] * this->decay) / 2));
		}
		this->y.push_back(0);

	}
}