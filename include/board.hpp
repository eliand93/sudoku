#pragma once
#include <string>

class Board {
    private:
        int grid[9][9];
        bool locked[9][9];
        int solution[9][9];
        

    public:
        void loadPuzzle(const std::string& filename, int puzzleNumber);
        void displayBoard();
        bool checkSolution();
        bool isValidMove(int row, int col, int num);
        bool writeToGrid(int row, int col, int num);

};

