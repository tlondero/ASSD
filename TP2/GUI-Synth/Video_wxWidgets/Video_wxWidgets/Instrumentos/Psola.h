#pragma once
#include "../Controllers/dependecies/AudioFile.h"
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <math.h>
#include <fstream>

#define SAMPLE_RATE 44100
#define MAX_AMP 32760

const double PI_ = 3.141592653589793238460;

using namespace std;
class Data
{
public:
	void set_f0(int f0);
	void set_pm(vector<int> pitch_marks);

	vector<int> get_pm(void);
	int get_f0(void);

private:
	int f0;
	vector<int> pitch_marks;
};

class Psola
{
public:
	Psola();
	Psola(const char *path, bool verbose);
	Psola(const char *path);

	vector<double> generateNote(double new_frequency, double new_duration, string wav_path, string data_path);
	//vector<double> synthMidi(vector<double, double>);

	void samplePrint(int N);

	AudioFile<double> sample;

	Data load_data(const char *path);

private:
	vector<double> hanningN(int N);
	double getSampleDuration();

	//Input (order matters):
	//s1: first input vector
	//s2: second input vector
	//N: integer, ammount of overlapping samples
	template <class T, class U>
	vector<T> overlap(vector<T> s1, vector<U> s2, int N)
	{
		int L1 = s1.size();
		int L2 = s2.size();
		int outputL = L1 + L2 - N;

		vector<T> output(outputL);

		//First non-overlapping segment
		for (int i = 0; i < L1 - N; i++)
		{
			output[i] = s1[i];
		}
		//Overlapped segment
		for (int x = L1 - N, y = 0; x < L1; x++, y++)
		{
			output[x] = s1[x] + s2[y];
		}

		//Last non-overlapping segment
		for (int k = N, m = L1; k < L2; k++, m++)
		{
			output[m] = s2[k];
		}

		cout << "result" << endl;
		for (int counter = 0; counter < output.size(); counter++)
		{
			cout << output[counter] << " ";
		}

		return output;
	}
};
