#include "Psola.h"

//Psola constructor 
//Input:
//Path: sample note path. Must .wav extension
Psola::Psola(const char* path)
{
	//cout << "Hola" << endl;
	sample.load(path);

}

//Psola constructor 
//Input:
//Path: sample note path. Must .wav extension
//verbose: bool type. If true prints .wav summary
Psola::Psola(const char* path, bool verbose)
{
	sample.load(path);
	if (verbose)
		sample.printSummary();

}


vector<double> Psola::generateNote(double new_duration, double new_frequency)
{

	//The First step is finding out the fundamental frequency 
	double f0 = 440; //Hz Assume constant pitch
	double pitch_period = 1 / f0; //Periodo fundamental <--
	double sample_rate = sample.getSampleRate();
	
	double original_duration = sample.getLengthInSeconds();
	long int num_samples = sample.getNumSamplesPerChannel();
	vector<double> input_signal = sample.samples[0];
	//Time stretching factor
	double alpha = new_duration / original_duration;

	//Pitch shifting factor
	double beta = new_frequency / f0;

	//Load pitch marks
	vector<int> p_marks = load_pitm("a4_peaks.csv");
	vector<int> pitch_periods(p_marks.size());
	for (int i = 0; i < p_marks.size(); i++) {
		if (i == 0)
			pitch_periods[0] = p_marks[0];
		else{
			pitch_periods[i] = p_marks[i] - p_marks[i - 1];
		}
			
	}

	//Remove first pitch mark
	if (p_marks[0] < pitch_periods[0]) {
		p_marks.erase(p_marks.begin());
		pitch_periods.erase(pitch_periods.begin());
	}

	if (p_marks.back() + pitch_periods.back() > sample.getNumSamplesPerChannel())
	{
		p_marks.pop_back();
	}
	else {
		pitch_periods.push_back(pitch_periods.back());
	}

	//Output length
	int output_length = ceil(num_samples * alpha);															

	//Create output vector
	vector<double> outputSignal(output_length);

	//Calculo del primer pitch mark en el nuevo espacio
	double tk = pitch_periods[0] + 1.0;

	while (round(tk) < output_length) {
		//¿Cual pitch mark del espacio original esta más cerca del nuevo pitch mark el espacio de llegada?
		vector<double> new_pitch_space(p_marks.size());
		//Los ti son las ubicaciones temporales de los pitch marks originales y tk es el nuevo pitch mark
		transform(p_marks.begin(), p_marks.end(), new_pitch_space.begin(), [alpha, tk](double ti) {return abs(ti * alpha - tk); });
		vector<double>::iterator ptr_min = min_element(new_pitch_space.begin(), new_pitch_space.end());

		//min_index nos indica donde esta ubicado el pitchmark
		int min_index = ptr_min - new_pitch_space.begin(); //Perform difference in memory position to acquire index of the smallest value
		double pit = pitch_periods[min_index]; //P(ti) 

		//Una vez obtenida la posición del pitch mark puedo tomar el bloque correspondiente y solaparlo con mi vector de salida
		//Este bloque for itera sobre la ST signal tomada del vector de muestras original
		vector<double> hanning_window = this->hanningN(2 * pit + 1);
		vector<double> windowed_segment(2 * pit + 1);
		vector<double> overllaped_segment(2 * pit + 1);


		for (int i = p_marks[min_index] - pit, h = 0; i < p_marks[min_index] + pit; i++, h++) {
			overllaped_segment[h] = input_signal[i] * hanning_window[h];
		}
		cout << "termine" << endl;


		int inicio_overlapp = round(tk) - pit;
		int fin_overlapp = round(tk) + pit;
		//¿Podemos solaparlo?

		if (fin_overlapp > output_length)
			break;
		//Sino procedemos a solapar y sumar
		for (int s = inicio_overlapp,i=0; s < fin_overlapp; s++,i++) {
			if(s < 0)
			{
				continue;
			}
			if (s > outputSignal.size()) {
				break;
			}
			outputSignal[s] += overllaped_segment[i];
		}

		tk = tk + pitch_periods[min_index] / beta;
		cout << tk << endl;
	}

	//record output
	AudioFile<double> output_note;
	output_note.setNumChannels(1);
	output_note.samples[0] = outputSignal;
	output_note.setSampleRate(sample.getSampleRate());
	output_note.save("out1.wav");

	return outputSignal;
}

//Prints the first N samples from the loaded wav file
void Psola::samplePrint(int N)
{
	for (int n = 0; n < N; n++)
		cout << sample.samples[0][n] << " ";
}

vector<int> Psola::load_pitm(const char* path)
{
	vector<int> data_points;

	ifstream myPitchMarks;
	myPitchMarks.open(path);
	while (myPitchMarks.good()) {
		string line;
		string empty("");
		getline(myPitchMarks, line, '\n');
		if (line != empty)
			data_points.push_back(stoi(line));
	}
	return data_points;
}

vector<double> Psola::hanningN(int N)
{
	vector<double> window;
	for (int n = 0; n <= N; n++) {
		window.push_back(pow(sin((PI * n) / N), 2.0));
	}
	return window;
}

double Psola::getSampleDuration()
{
	return sample.getLengthInSeconds();
}

