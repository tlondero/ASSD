#include "Psola.h"
#include "InstrumentsPsola.h"
using namespace std;

int main(void)
{	

	Psola s;
	string wav_path = "assets/saxofono/Notes/A4.wav";
	string data_path = "assets/saxofono/data/A4.csv";
	s.generateNote(2000, 1.2,wav_path,data_path);
	//SaxoPsola saxo;
	//vector<double> note = saxo.generateNote(1300,2,1);
}
