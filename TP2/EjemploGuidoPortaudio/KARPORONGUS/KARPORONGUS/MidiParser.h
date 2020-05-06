#pragma once
#include "midi/MidiFile.h"
#include"utils\Tracks.h"
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
	vector<Tracks> getTracks();
	//Devuelve un vector de tracks
	double getTotalDuration(void);
private:
	MidiFile midiFile;
	double totalDuration;

};

