#include "EcoSimple.h"
EcoSimple::EcoSimple() {

}

vector<double> EcoSimple::applyEffect(vector<double> input, double T, double D) {

    for (int i = 0; i < 2.8 * T * SAMPLE_RATE; i++) {
        input.push_back(0);
    }

    std::vector<double> output(input.size(), 0);

    int m = T * SAMPLE_RATE * (-1 * log10(abs(D)) / 3.0);

    for (int i = 0; i < input.size(); i++) {
        if (i - m > 0)
        output[i] = (-1) * D * input[i] + input[i - m] + D * output[i - m];
    }
    return output;
}

EcoSimple::~EcoSimple() {

}