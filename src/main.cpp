#include <iostream>

#include "board.hpp"
#include "solver.hpp"


int main() {
    std::cout << "Sudoku game starting..." << std::endl << std::endl << std::endl;


    Board board;

    std::cout << std::endl << "easy, medium, hard or diabolical? ";
    std::string difficulty;
    std::getline(std::cin, difficulty);

    if (!board.loadPuzzle("puzzles/" + difficulty + ".txt")){
        return 1; // Exit if puzzle loading fails
    };

    // Main game loop
    while (true) {
        board.displayBoard();
        std::cout << std::endl << "Enter your move (row col num) or 'q' to quit: ";
        std::string input;
        std::getline(std::cin, input);

        if (input == "q") {
            break;
        }

        else if (input == "test"){
            int row, col;
            std::cout << "Enter row and column to check possible values: ";
            std::cin >> row >> col;
            std::cin.ignore(); // Clear the newline character from the input buffer
            board.printPossibleValues(row - 1, col - 1);
        }

        else if (input == "h") {
            if (board.hasConflicts()) {
                std::cout << "The current board has conflicts. Cannot solve." << std::endl;
                continue;
            }
            Solver solver(board);

            if (solver.solve()) {
                std::cout << "Filled one cell!" << std::endl;
                if (board.checkSolution()) {
                    std::cout << "Congratulations! You've solved the puzzle!" << std::endl;
                    break;
                }
            } else {
                std::cout << "No solution found." << std::endl;
            }
            continue;
        }

        else if (input == "s") {
            if (board.hasConflicts()) {
                std::cout << "The current board has conflicts. Cannot solve." << std::endl;
                continue;
            }
            Solver solver(board);

            if (solver.solveAll()) {
                board.displayBoard();
                std::cout << "Solved the puzzle!" << std::endl;
                if (board.checkSolution()) {
                    std::cout << "Congratulations! You've solved the puzzle!" << std::endl;
                    break;
                }
            } else {
                std::cout << "No solution found." << std::endl;
            }
            continue;
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