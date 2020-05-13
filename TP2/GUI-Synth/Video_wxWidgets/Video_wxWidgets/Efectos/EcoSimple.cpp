#include "EcoSimple.h"
EcoSimple::EcoSimple() {

}

vector<double> EcoSimple::applyEffect(vector<double> input, double T, double D) {

    for (int i = 0; i < ((3*T)/((-1)*log10(abs(D)))) * SAMPLE_RATE; i++) {
        input.push_back(0);
    }

   int m = floor(T * SAMPLE_RATE);

    for (int i = 0; i < input.size(); i++) {
        if (i - m > 0) {
            input[i] = input[i] + D * input[i - m];
        }
    }
    return input;
}

EcoSimple::~EcoSimple() {

}