#pragma once
#include <vector>
#include <iostream>

int makeWav( int channels, double seconds, std::string name, std::vector<double> data, double volume);
//Channel en general vale 2, seconds es la duración de tu audio, name es el nombre del archivo y data es tu vector desnormalizado,
//lease n-> n/samplerate; n es el iterador