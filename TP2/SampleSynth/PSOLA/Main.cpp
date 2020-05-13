#include "Psola.h"
#include "InstrumentsPsola.h"
using namespace std;

int main(void)
{	

	//Psola s("assets/saxofono/Notes/A4.wav",true);
	//s.generateNote(3,450);
	SaxoPsola saxo;
	vector<double> note = saxo.generateNote(1300,2,1);
}
