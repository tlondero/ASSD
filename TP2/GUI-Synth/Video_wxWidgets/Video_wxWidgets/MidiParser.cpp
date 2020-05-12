#include "MidiParser.h"
#include <iostream>
#include <algorithm>
using namespace std;
using namespace smf;

MidiParser::MidiParser()
{

}
vector<vector<Tracks>> MidiParser::getTracks() {
	vector<double> toff;
	vector<double> tofft;
	midiFile.doTimeAnalysis();
	midiFile.linkNotePairs();
	int tracks = midiFile.getTrackCount();
	vector<vector<Tracks>> trackVector;
	double tmax = TMAX;
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
				if (midiFile[track][event].getDurationInSeconds() != 0) { //REVISAR
					if (midiFile[track][event].isNoteOn()) {
						actualNote.t_on = midiFile[track][event].seconds;
						actualNote.Duration = midiFile[track][event].getDurationInSeconds();
						actualNote.velocity = midiFile[track][event].getVelocity();
						actualNote.frequency = pow(2, (midiFile[track][event].getKeyNumber() - 69.0) / 12.0) * 440;
						actualTrack.Notes.push_back(actualNote);
						toff.push_back(actualNote.t_on + actualNote.Duration);

					}
				}
			}

		}
		//if (strcmp(actualTrack.instrumentName.c_str(), "") && (actualTrack.Notes.size() >= 1))
			//trackVector.push_back(actualTrack);
		/*else*/ 
		if (actualTrack.Notes.size() >= 1) {
			if(actualTrack.instrumentName == "")
			actualTrack.instrumentName="UNKNOWN";
			//trackVector.push_back(actualTrack);
			
				


			vector<Tracks> partialTracks;
			double tcorr = 0;
			double icorr = 0;
			bool break_j = false;
			for (int j = 0;;) {
				Tracks tempTrack;
				Note tempNote;
				partialTracks.push_back(tempTrack);
				partialTracks[j].instrumentName = actualTrack.instrumentName;
				partialTracks[j].userInstrumentChoice = actualTrack.userInstrumentChoice;
				for (int i = icorr; i < actualTrack.Notes.size(); i++) {
					if (actualTrack.Notes[i].t_on - tcorr > tmax) {
						tcorr += tmax;
						j++;
						icorr = i;     //ME FUI A BUSCAR ALGO DE COMER, GUIDO CREO QUE ROMPI TODAS LAS REGLAS DE PROGRA 1
						break;			//PORFIS FIJATE SI LO QUE HICE ESTA BIEN.
					}

					tempNote.Duration = actualTrack.Notes[i].Duration;
					tempNote.frequency = actualTrack.Notes[i].frequency;
					tempNote.t_on = actualTrack.Notes[i].t_on - tcorr;
					tempNote.velocity = actualTrack.Notes[i].velocity;
					partialTracks[j].Notes.push_back(tempNote);
					if (i == (actualTrack.Notes.size() - 1)) {
						break_j = true;
					}

				}

				if (break_j) {
					break;
				}
			}
			

			trackVector.push_back(partialTracks);
		}
	}

	vector<vector<Tracks>> ordenado;

	for (int subTrack = 0; subTrack < trackVector[0].size(); subTrack++) {
		vector<Tracks> sub_ordenado;
		for (int instrumento = 0; instrumento < trackVector.size(); instrumento++) {
			sub_ordenado.push_back(trackVector[instrumento][subTrack]);
		}
		ordenado.push_back(sub_ordenado);
	}
	vector<double> temptoff;
	vector<double> maxToff;
	for (unsigned int subtrack=0; subtrack < ordenado.size();subtrack++) {
		for (unsigned int instrument = 0; instrument < ordenado[subtrack].size(); instrument++)
			for (unsigned int i = 0; i < ordenado[subtrack][instrument].Notes.size(); i++)
				temptoff.push_back(ordenado[subtrack][instrument].Notes[i].t_on + ordenado[subtrack][instrument].Notes[i].Duration);
		maxToff.push_back(*max_element(temptoff.begin(), temptoff.end()));
	}

	this->subDurations = maxToff;
	if (toff.size() > 0)
		this->totalDuration = *max_element(toff.begin(), toff.end());
	else
		this->totalDuration = 0;

	return ordenado;

}

double MidiParser::getSubDuration(int i) {
	return this->subDurations[i];
}
bool MidiParser::addMidi(std::string filename) {
	this->midiFile = MidiFile(filename);
	return this->midiFile.status();
}
MidiParser::~MidiParser()
{
}
double MidiParser::getTotalDuration(void) {
	return this->totalDuration;
}