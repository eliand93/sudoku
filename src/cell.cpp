#include "cell.hpp"

void Cell::eliminatePossibleValue(int val) {
    if (val > 0 && val <= 9 && possibleValues[val - 1]) {
            possibleValues[val - 1] = false;
            numPossibleValues--;
    }
}

void Cell::setValue(int val) {
    if (val > 0 && val <= 9) {
        value = val;
        for (int i = 0; i < 9; ++i) {
            possibleValues[i] = false;
        }
        possibleValues[val - 1] = true;
        numPossibleValues = 1;
    }
}

void Cell::resetPossibleValues() {
    for (int i = 0; i < 9; ++i) {
        possibleValues[i] = true;
    }
    numPossibleValues = 9;
}