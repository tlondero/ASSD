#include "EcoSimple.h"
EcoSimple::EcoSimple() {

}

vector<double> EcoSimple::applyEffect(vector<double> input, double g, int M) {

    for (int i = 0; i < input.size(); i++) {
        if (i - M > 0)
            input[i] = input[i] + (-g) * input[i - M];
    }
    return input;
}
EcoSimple::~EcoSimple() {

}