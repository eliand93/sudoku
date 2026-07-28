#pragma once
#include <iostream>
#include <string>

class Board {
    private:
        int grid[9][9];
        bool locked[9][9];

        

    public:
        void loadPuzzle(const std::string& filename);
        void displayBoard();
        bool checkSolution();
        bool writeToGrid(int row, int col, int num);


};

