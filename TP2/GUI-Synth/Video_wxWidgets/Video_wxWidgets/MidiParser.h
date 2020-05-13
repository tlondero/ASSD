#pragma once
#include "midi/MidiFile.h"
#include "utils\Tracks.h"
#include "General.h"
#include <string>
#include <vector>

using namespace std;
using namespace smf;
class MidiParser
{
public:
	MidiParser();
	~MidiParser();
	bool addMidi(std::string filename);
	//Devuelve falso si no se encontró el archivo.
	vector<vector<Tracks>> getTracks();
	//Devuelve un vector de tracks
	double getTotalDuration(void);
	double getSubDuration(int i);
private:
	MidiFile midiFile;
	double totalDuration;
	vector<double> subDurations;

};

