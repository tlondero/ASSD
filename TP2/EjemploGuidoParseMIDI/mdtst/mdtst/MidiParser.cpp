#include "MidiParser.h"
#include <iostream>
using namespace std;
using namespace smf;

MidiParser::MidiParser()
{

}
vector<Tracks> MidiParser::getTracks() {
	midiFile.doTimeAnalysis();
	midiFile.linkNotePairs();
	int tracks = midiFile.getTrackCount();
	vector<Tracks> trackVector;
	for (int track = 0; track < tracks; track++) {
		Tracks actualTrack;
		for (int event = 0; event < midiFile[track].size(); event++) {
			Note actualNote;
			if (midiFile[track][event].isTrackName()) {
				string a;
				for (int i = 3; i < midiFile[track][event].size(); i++) {
					a.push_back(midiFile[track][event][i]);
				}
				actualTrack.instrumentName = a;
			}
			if (midiFile[track][event].isNote()) {
				if (midiFile[track][event].isNoteOn()) {
					actualNote.t_on = midiFile[track][event].seconds;
					actualNote.Duration = midiFile[track][event].getDurationInSeconds();
					actualNote.velocity = midiFile[track][event].getVelocity();
					actualNote.frequency =pow(2, (midiFile[track][event].getKeyNumber() - 69.0) / 12.0) * 440;
					actualTrack.Notes.push_back(actualNote);
				}
			}
			
		}
		if(strcmp(actualTrack.instrumentName.c_str(),"") )
			trackVector.push_back(actualTrack);
	}
	return trackVector;
}
bool MidiParser::addMidi(std::string filename) {
	this->midiFile = MidiFile(filename +".mid");
	return this->midiFile.status();
}
MidiParser::~MidiParser()
{
}
