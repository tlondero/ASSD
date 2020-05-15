#pragma once
#include "Psola.h"
class SaxoPsola
{
public:
	vector<double> generateNote(double frequency, double duration, double velocity);

private:
	Psola ps;
	string select_note(double frequency);
	string wavRelPath = "assets/saxofono/Notes/";
	string dataRelPath = "assets/saxofono/data/";

	// vector<string> notes = {"A4", "A5", "A6", "Asharp3", "Asharp4", "Asharp5",
	// 						"Asharp6", "G4", "G5", "G6", "Gsharp4", "Gsharp5",
	// 						"Gsharp6", "B5"};
	// vector<int> freqs = {395, 1575, 1627, 629, 417, 1666, 1682, 352, 701, 1410, 1114, 743, 1488, 2653};

	vector<string> notes = {"A4"};
	vector<int> freqs = {395};

	string get_data_path(string note);
	string get_wav_path(string note);
};

//Begin Modern Flaute
class ModernFlautePsola
{
public:
	vector<double> generateNote(double frequency, double duration, double velocity);

private:
	Psola ps;
	string select_note(double frequency);
	string wavRelPath = "assets/flautaModernB/Notes/";
	string dataRelPath = "assets/flautaModernB/data/";

	vector<string> notes = {"G6"}; //{"B3"};
	vector<int> freqs = {532};//{250};

	string get_data_path(string note);
	string get_wav_path(string note);
};