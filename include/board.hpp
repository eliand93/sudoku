#pragma once
#include <iostream>
#include <string>
#include "cell.hpp"


class Board {
    private:
        Cell grid[9][9];
        bool locked[9][9];


        

    public:

        Cell& getCell(int row, int col) {
            return grid[row][col];
        }
        bool loadPuzzle(const std::string& filename);
        void displayBoard(int lastRow = -1, int lastCol = -1);
        bool checkSolution();
        bool writeToGrid(int row, int col, int num);
        void printPossibleValues(int row, int col);
        bool hasConflicts();


};

