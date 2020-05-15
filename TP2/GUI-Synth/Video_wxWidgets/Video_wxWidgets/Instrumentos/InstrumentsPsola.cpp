#include "InstrumentsPsola.h"

vector<double> SaxoPsola::generateNote(double frequency, double duration, double velocity)
{

	string note = select_note(frequency);
	string data_path = get_data_path(note);
	string wav_path = get_wav_path(note);
	vector<double> synthNote = ps.generateNote(frequency, duration, wav_path, data_path);
	//Normalizar y aplicar velocity para regular el volumen
	double maxValue = *max_element(synthNote.begin(), synthNote.end());
	vector<double> out(synthNote.size());
	transform(synthNote.begin(), synthNote.end(), synthNote.begin(), [maxValue, velocity](double nn) { return (nn * velocity) / maxValue; });

	return synthNote;
}

string SaxoPsola::select_note(double frequency)
{
	vector<double> diff(this->freqs.size());

	transform(this->freqs.begin(), this->freqs.end(), diff.begin(), [frequency](double f_a) { return abs(frequency - f_a); });
	vector<double>::iterator ptr_min = min_element(diff.begin(), diff.end());

	//min_index nos indica donde esta ubicado el minimo
	int min_index = ptr_min - diff.begin(); //Perform difference in memory position to acquire index of the smallest value

	return this->notes[min_index];
}

string SaxoPsola::get_wav_path(string note)
{
	return this->wavRelPath + note + ".wav";
}
string SaxoPsola::get_data_path(string note)
{
	return this->dataRelPath + note + ".csv";
}

//########Modern Flaute######//
vector<double> ModernFlautePsola::generateNote(double frequency, double duration, double velocity)
{

	string note = select_note(frequency);
	string data_path = get_data_path(note);
	string wav_path = get_wav_path(note);
	vector<double> synthNote = ps.generateNote(frequency, duration, wav_path, data_path);
	//Normalizar y aplicar velocity para regular el volumen
	double maxValue = *max_element(synthNote.begin(), synthNote.end());
	vector<double> out(synthNote.size());
	transform(synthNote.begin(), synthNote.end(), synthNote.begin(), [maxValue, velocity](double nn) { return (nn * velocity) / maxValue; });

	return synthNote;
}

string ModernFlautePsola::select_note(double frequency)
{
	vector<double> diff(this->freqs.size());

	transform(this->freqs.begin(), this->freqs.end(), diff.begin(), [frequency](double f_a) { return abs(frequency - f_a); });
	vector<double>::iterator ptr_min = min_element(diff.begin(), diff.end());

	//min_index nos indica donde esta ubicado el minimo
	int min_index = ptr_min - diff.begin(); //Perform difference in memory position to acquire index of the smallest value

	return this->notes[min_index];
}

string ModernFlautePsola::get_wav_path(string note)
{
	return this->wavRelPath + note + ".wav";
}
string ModernFlautePsola::get_data_path(string note)
{
	return this->dataRelPath + note + ".csv";
}
