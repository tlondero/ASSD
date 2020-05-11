#include "EspectroGenerator.h"

int main(void) {
	EspectroGenerator es;
	//es.generateSpectrum("Trombone.wav"); //Como esta en la misma carpeta le pasamos el nombre del archivo
	es.generateSpectrum("twinkle.wav",256,128,"blackman",0,0,0);
}