#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "board.hpp"

void Board::test(int x) {
    std::cout << "Testing Board class..." << x << std::endl;
}

bool Board::writeToGrid(int row, int col, int num) {


    if (row < 0 || row >= 9 || col < 0 || col >= 9) {
        return false;
    }

    if (num < 0 || num > 9) {
        return false;
    }

    if (locked[row][col]) {
        return false;
    }

    if (!locked[row][col]){
        grid[row][col].setValue(num);

    }
    return true;
}

bool Board::checkSolution() {
    // Check if the grid is completely filled
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (grid[row][col].value == 0) {
                return false;
            }
        }
    }
    
    // Check rows
    for (int row = 0; row < 9; ++row) {
        bool digits[9] = {false};
        for (int col = 0; col < 9; ++col) {
            int val = grid[row][col].value;

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
            int val = grid[row][col].value;
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
                    int val = grid[boxRow * 3 + row][boxCol * 3 + col].value;
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

bool Board::loadPuzzle(const std::string& filename) {
    // Implementation for loading puzzle

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
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
    std::string rating = chosen.substr(95,4);
    std::cout << "Puzzle with difficulty level " << rating << " loaded." << std::endl;

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {

            int val = digits[row * 9 + col] - '0';
            grid[row][col] = Cell(val);
            locked[row][col] = (val != 0);

        }
    }

    return true;
}

void Board::displayBoard(int lastRow, int lastCol) {

    std::cout << std::endl << "    1 2 3   4 5 6   7 8 9" << std::endl;
    std::cout << "  +-------+-------+-------+" << std::endl;

    for (int row = 0; row < 9; ++row) {
        std::cout << row +1 << " | ";
        for (int col = 0; col < 9; ++col) {
            int val = grid[row][col].value;
            if (val == 0) {
                std::cout << ". ";
            } else if (row == lastRow && col == lastCol) {
                std::cout << "\033[32m" << val << "\033[0m "; // grön = senaste
            } else if (locked[row][col]) {
                std::cout << "\033[37m" << val << "\033[0m "; // vit = låst
            } else {
                std::cout << "\033[34m" << val << "\033[0m "; // blå = spelaren
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

void Board::printPossibleValues(int row, int col) {
    Cell& cell = getCell(row, col);
    std::cout << "Possible values for cell (" << row + 1 << ", " << col + 1 << "): ";
    for (int i = 0; i < 9; ++i) {
        if (cell.possibleValues[i]) {
            std::cout << (i + 1) << " ";
        }
    }
    std::cout << std::endl;
}

bool Board::hasConflicts() {
    // Check rows
    for (int row = 0; row < 9; ++row) {
        bool digits[9] = {false};
        for (int col = 0; col < 9; ++col) {
            int val = grid[row][col].value;
            if (val != 0) {
                if (digits[val - 1]) {
                    return true; // Conflict found
                }
                digits[val - 1] = true;
            }
        }
    }

    // Check columns
    for (int col = 0; col < 9; ++col) {
        bool digits[9] = {false};
        for (int row = 0; row < 9; ++row) {
            int val = grid[row][col].value;
            if (val != 0) {
                if (digits[val - 1]) {
                    return true; // Conflict found
                }
                digits[val - 1] = true;
            }
        }
    }

    // Check 3x3 subgrids
    for (int boxRow = 0; boxRow < 3; ++boxRow) {
        for (int boxCol = 0; boxCol < 3; ++boxCol) {
            bool digits[9] = {false};
            for (int row = 0; row < 3; ++row) {
                for (int col = 0; col < 3; ++col) {
                    int val = grid[boxRow * 3 + row][boxCol * 3 + col].value;
                    if (val != 0) {
                        if (digits[val - 1]) {
                            return true; // Conflict found
                        }
                        digits[val - 1] = true;
                    }
                }
            }
        }
    }

    return false; // No conflicts found
}
