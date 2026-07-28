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
