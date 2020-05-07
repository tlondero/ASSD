#include <iostream>
#include "MidiParser.h"
using namespace std;

int main(void) {
	MidiParser MyMidi;
MyMidi.addMidi("sample");

vector <Tracks>  MyTracks = MyMidi.getTracks();


	while (toupper(getchar()) != 'Q') {};
}
