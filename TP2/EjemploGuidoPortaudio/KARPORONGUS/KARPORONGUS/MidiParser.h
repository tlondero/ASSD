#pragma once
#include "midi/MidiFile.h"
#include"Tracks.h"
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
	//Devuelve falso si no se encontr� el archivo.
	vector<Tracks> getTracks();
	//Devuelve un vector de tracks
private:
	MidiFile midiFile;
	double totalDuration;

};

