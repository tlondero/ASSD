#include "util.h"
#include <ctime>
#include <iostream>
#include <complex>
const int N = 4096;
using namespace std;
void randvect(void){
	srand(time(NULL));
	complex<double> vec[N];
	for (int i = 0; i < N; i++) {
		vec[i]._Val[0] = double(int(rand() % 100));
		vec[i]._Val[1] = 0;
	}
	cout << "{";
	for (int i = 0; i < N-1; i++) {
		cout << "{" << vec[i].real() << "," << vec[i].imag() << "}" << ",";
	}
	cout << "{" << vec[N-1].real() << "," << vec[N-1].imag() << "}" << "";
	cout << "}";
}
