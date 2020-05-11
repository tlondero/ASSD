#pragma once
#include <vector>
#include<math.h>
const double PI = 3.141592653589793238460;

using namespace std;
//Generate a Hanning window ALAS Hann Window of length N+1, N cand be even or odd;
vector <double> hanningN(int N) {
	vector<double> window;
	for (int n = 0; n <= N; n++)
		window.push_back(pow(sin((PI * n) / N),2.0));
	return window;
}