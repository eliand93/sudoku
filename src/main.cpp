#include <iostream>

#include "board.hpp"


int main() {
    std::cout << "Sudoku game starting..." << std::endl << std::endl << std::endl;


    Board board;
    board.loadPuzzle("puzzles/easy.txt");

    while (true) {
        board.displayBoard();
        std::cout << std::endl << "Enter your move (row col num) or 'q' to quit: ";
        std::string input;
        std::getline(std::cin, input);

        if (input == "q") {
            break;
        }

        int row, col, num;
        if (sscanf(input.c_str(), "%d %d %d", &row, &col, &num) == 3) {
            if (!board.writeToGrid(row - 1, col - 1, num)) {
                std::cout << "Invalid move (locked cell).Try again." << std::endl;
            } else {
                if (board.checkSolution()) {
                    std::cout << "Congratulations! You've solved the puzzle!" << std::endl;
                    break;
                }
            }
        } else {
            std::cout << "Invalid input format. Please enter row, column, and number separated by spaces." << std::endl;
        }
    }



    return 0;
}