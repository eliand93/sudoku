#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "board.hpp"

bool Board::writeToGrid(int row, int col, int num) {
    if (row < 0 || row >= 9 || col < 0 || col >= 9) {
        return false;
    }

    if (num < 1 || num > 9) {
        return false;
    }

    if (locked[row][col]) {
        return false;
    }

    grid[row][col] = num;
    return true;
}

bool Board::checkSolution() {
    // Check if the grid is completely filled
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (grid[row][col] == 0) {
                return false;
            }
        }
    }
    
    // Check rows
    for (int row = 0; row < 9; ++row) {
        bool digits[9] = {false};
        for (int col = 0; col < 9; ++col) {
            int val = grid[row][col];

            if (digits[val - 1]) {
                return false;
            }
            digits[val - 1] = true;
        }
    }

    // Check columns
    for (int col = 0; col < 9; ++col) {
        bool digits[9] = {false};
        for (int row = 0; row < 9; ++row) {
            int val = grid[row][col];
            if (digits[val - 1]) {
                return false;
            }
            digits[val - 1] = true;
        }
    }

    // check 3x3 subgrids
    for (int boxRow = 0; boxRow < 3; ++boxRow) {
        for (int boxCol = 0; boxCol < 3; ++boxCol) {
            bool digits[9] = {false};
            for (int row = 0; row < 3; ++row) {
                for (int col = 0; col < 3; ++col) {
                    int val = grid[boxRow * 3 + row][boxCol * 3 + col];
                    if (digits[val - 1]) {
                        return false;
                    }
                    digits[val - 1] = true;
                }
            }
        }
    }

    return true;

}

void Board::loadPuzzle(const std::string& filename) {
    // Implementation for loading puzzle

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    srand(time(nullptr));
    std::string chosen;
    std::string line;
    int count = 0;

    while (std::getline(file, line)) {
        count++;
        if (rand() % count == 0) {
            chosen = line;
        }
        
    }

    //parse 81 numbers (skip 12 bytes hash and 1 space)
    std::string digits = chosen.substr(13, 81);

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {

            int val = digits[row * 9 + col] - '0';
            grid[row][col] = val;
            locked[row][col] = (val != 0);

        }
    }
}

void Board::displayBoard() {

    std::cout << std::endl << "    1 2 3   4 5 6   7 8 9" << std::endl;
    std::cout << "  +-------+-------+-------+" << std::endl;

    for (int row = 0; row < 9; ++row) {
        std::cout << row +1 << " | ";
        for (int col = 0; col < 9; ++col) {
            int val = grid[row][col];
            if (val == 0) {
                std::cout << ". ";
            } else {
                std::cout << val << " ";
            }
            
            if ((col + 1) % 3 == 0 && col != 8) {
                std::cout << "| ";
            }

        }
        std::cout << "| "<< std::endl;

        if ((row + 1) % 3 == 0 && row != 8) {
            std::cout << "  +-------+-------+-------+" << std::endl;
        }
    }

    std::cout << "  +-------+-------+-------+" << std::endl;
}

