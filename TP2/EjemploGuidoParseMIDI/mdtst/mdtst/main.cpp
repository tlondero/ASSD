#include <iostream>
#include "MidiParser.h"
#include <string> 

using namespace std;
int main(void) {
	MidiParser MyMidi;
	string name = "sample";
	MyMidi.addMidi(name);

vector <Tracks>  MyTracks = MyMidi.getTracks();


	while (toupper(getchar()) != 'Q') {};
}
