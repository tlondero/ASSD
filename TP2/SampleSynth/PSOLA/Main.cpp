#include "Psola.h"
#include "InstrumentsPsola.h"
using namespace std;

int main(void)
{	

	Psola s;
	string wav_path = "assets/violin/notes/A4violin.wav";
	string data_path = "assets/violin/data/A4violin.csv";
	s.generateNote(880, 5,wav_path,data_path);
	//SaxoPsola saxo;
	//vector<double> note = saxo.generateNote(1300,2,1);
}
