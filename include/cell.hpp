#pragma once

class Cell {
    public:
        int value;
        bool possibleValues[9]; // possible values from 1 to 9
        int numPossibleValues; // number of possible values

        Cell() : value(0), numPossibleValues(9) {
            for (int i = 0; i < 9; ++i) {
                possibleValues[i] = true;
            }
        }

        Cell(int val) : value(val), numPossibleValues(9) {
            for (int i = 0; i < 9; ++i) {
                possibleValues[i] = true;
            }


            if (val != 0){
                for (int i = 0; i < 9; ++i) {
                    if (val != i + 1){
                    eliminatePossibleValue(i + 1);
                    }
                }
            }

        }

        void eliminatePossibleValue(int val);
        void setValue(int val);
        void resetPossibleValues();


        
};