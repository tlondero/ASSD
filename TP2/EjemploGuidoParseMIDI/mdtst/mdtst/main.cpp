#include <iostream>
#include "midi/MidiFile.h"
using namespace std;
using namespace smf;

int main(void) {
	MidiFile midifile("HB.mid");
	int tracks = midifile.getTrackCount();
	vector<string> listOfInstruments;


	for (int track = 0; track < tracks; track++) {
		for (int event = 0; event < midifile[track].size(); event++) {

			if (midifile[track][event].isTrackName()) {
				cout << "The instrument is : ";
				string a;
				for (int i = 3; i < midifile[track][event].size(); i++) {
					a.push_back(midifile[track][event][i]);
				}
				cout << a << endl;
				listOfInstruments.push_back(a);
			}
			if (midifile[track][event].isNote()) {
				if (midifile[track][event].isNoteOn()){
					cout << "Note on  "<<'\t'<<"Note : " << midifile[track][event].getKeyNumber() << '\t' << " Velocity: " << midifile[track][event].getVelocity()
						<< '\t' <<" Tick: " << midifile[track][event] .tick << endl;
					}
				else if(midifile[track][event].isNoteOff()) cout << "Note off"<< '\t'<<" Note is: " << midifile[track][event].getKeyNumber() << '\t' <<" Velocity: " << midifile[track][event].getVelocity()
					<< '\t'<<" Tick " << midifile[track][event].tick << endl;
			}
		}
	}
	cout << "List of instruments: " << endl;
	for (int i = 0; i < listOfInstruments.size(); i++) {
		cout << listOfInstruments[i] << endl;
	}


	while (toupper(getchar()) != 'Q') {};
}



//int tracks = midifile.getTrackCount();
//cout << "TPQ: " << midifile.getTicksPerQuarterNote() << endl;
//if (tracks > 1) cout << "TRACKS: " << tracks << endl;
//for (int track = 0; track < tracks; track++) {
//	if (tracks > 1) cout << "\nTrack " << track << endl;
//	cout << "Tick\tSeconds\tDur\tMessage" << endl;
//	for (int event = 0; event < midifile[track].size(); event++) {
//		cout << dec << midifile[track][event].tick;
//		cout << '\t' << dec << midifile[track][event].seconds;
//		//midifile[track][event].
//		cout << '\t';
//		if (midifile[track][event].isNoteOn())
//			cout << midifile[track][event].getDurationInSeconds();
//		cout << '\t' << hex;
//		for (int i = 0; i < midifile[track][event].size(); i++)
//			cout << (int)midifile[track][event][i] << ' ';
//		cout << endl;
//	}
//}

