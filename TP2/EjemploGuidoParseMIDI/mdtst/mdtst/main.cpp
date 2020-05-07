#include <iostream>
#include "MidiParser.h"
#include <string> 

using namespace std;
int main(void) {
	MidiParser MyMidi;
MyMidi.addMidi(string "sample");

vector <Tracks>  MyTracks = MyMidi.getTracks();


	while (toupper(getchar()) != 'Q') {};
}
