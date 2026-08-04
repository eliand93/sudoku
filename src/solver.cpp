
#include "solver.hpp"

Solver::Solver(Board& board) : board(board) {
}


void Solver::checkColumn(int row, int col){
    // Check column
    for (int r = 0; r < 9; ++r){
        int val = board.getCell(r, col).value;
        if (val != 0 && r != row){
            board.getCell(row, col).eliminatePossibleValue(val);
        }
    }
}

void Solver::checkRow(int row, int col){
    // Check row
    for (int c = 0; c < 9; ++c){
        int val = board.getCell(row, c).value;
        if (val != 0 && c != col){
            board.getCell(row, col).eliminatePossibleValue(val);
        }
    }
}

void Solver::checkBox(int row, int col){
    // Check 3x3 box
    int boxRowStart = (row / 3) * 3;
    int boxColStart = (col / 3) * 3;
    for (int r = boxRowStart; r < boxRowStart + 3; ++r){
        for (int c = boxColStart; c < boxColStart + 3; ++c){
            int val = board.getCell(r, c).value;
            if (val != 0 && r != row && c != col){
                board.getCell(row, col).eliminatePossibleValue(val);
            }
        }   
    }
}

void Solver::checkFeasability() {
    // Check for cells without any possible values (indicating an unsolvable state)
    for (int row = 0; row < 9; ++row){
        for (int col = 0; col < 9; ++col){
            Cell& cell = board.getCell(row, col);
            if (cell.numPossibleValues == 0){
                printf("Cell (%d, %d) has no possible values. Puzzle is unsolvable.\n", row + 1, col + 1);
            }
        }
    }
}

void Solver::checkPointingPairs() {
    for (int boxRow = 0; boxRow < 3; ++boxRow) {
        for (int boxCol = 0; boxCol < 3; ++boxCol) {
            for (int num = 1; num <= 9; ++num) {
                int count = 0;
                int firstRow = -1;
                int firstCol = -1;
                bool sameRow = true;
                bool sameCol = true;

                for (int row = boxRow * 3; row < boxRow * 3 + 3; ++row){
                    for (int col = boxCol * 3; col < boxCol * 3 + 3; ++col){
                        Cell& cell = board.getCell(row, col);
                        if (cell.value == 0 && cell.possibleValues[num - 1]){
                            count++;
                            if (firstRow == -1) {
                                firstRow = row;
                                firstCol = col;
                            } else {
                                if (row != firstRow) sameRow = false;
                                if (col != firstCol) sameCol = false;
                            }
                        }
                    }
                }

                if ( count >= 2 && count <= 3) {
                    if (sameRow) {
                        for (int col = 0; col < 9; ++col) {
                            if (col < boxCol * 3 || col >= boxCol * 3 + 3) {
                                board.getCell(firstRow, col).eliminatePossibleValue(num);
                            }
                        }
                    } else if (sameCol) {
                        for (int row = 0; row < 9; ++row) {
                            if (row < boxRow * 3 || row >= boxRow * 3 + 3) {
                                board.getCell(row, firstCol).eliminatePossibleValue(num);
                            }
                        }
                    }
                }
                
            }
        }
    }
}

std::vector<int> Solver::getCellsWithTwoPossibleInRow(int row) {
    std::vector<int> cols;
    for (int col = 0; col < 9; ++col){
        Cell& cell = board.getCell(row, col);
        if (cell.value == 0 && cell.numPossibleValues == 2){
            cols.push_back(col);
        }
    }
    return cols;
}

std::vector<int> Solver::getCellsWithTwoPossibleInCol(int col) {
    std::vector<int> rows;
    for (int row = 0; row < 9; ++row){
        Cell& cell = board.getCell(row, col);
        if (cell.value == 0 && cell.numPossibleValues == 2){
            rows.push_back(row);
        }
    }
    return rows;
}

std::vector<int> Solver::getCellsWithTwoPossibleInBox(int boxRow, int boxCol) {
    std::vector<int> cells;
    for (int row = boxRow * 3; row < boxRow * 3 + 3; ++row){
        for (int col = boxCol * 3; col < boxCol * 3 + 3; ++col){
            Cell& cell = board.getCell(row, col);
            if (cell.value == 0 && cell.numPossibleValues == 2){
                cells.push_back(row * 9 + col); // Store as a single integer for simplicity
            }
        }
    }
    return cells;
}

bool Solver::samePossibleValues(const Cell& cell1, const Cell& cell2) {
    for (int i = 0; i < 9; ++i) {
        if (cell1.possibleValues[i] != cell2.possibleValues[i]) {
            return false;
        }
    }
    return true;
}

void Solver::updateNakedPairs() {
    // Implementation for updating naked pairs in rows
    for (int row = 0; row < 9; ++row){
        std::vector<int> twoPossibleCols = getCellsWithTwoPossibleInRow(row);
        for (size_t i = 0; i < twoPossibleCols.size(); ++i){
            for (size_t j = i + 1; j < twoPossibleCols.size(); ++j){
                Cell& cell1 = board.getCell(row, twoPossibleCols[i]);
                Cell& cell2 = board.getCell(row, twoPossibleCols[j]);
                if (samePossibleValues(cell1, cell2)){
                    for (int col = 0; col < 9; ++col){
                        if (col != twoPossibleCols[i] && col != twoPossibleCols[j]){
                            for (int num = 1; num <= 9; ++num){
                                if (cell1.possibleValues[num - 1]){
                                    board.getCell(row, col).eliminatePossibleValue(num);
                                }
                            }
                        }
                    }
                }
            }
        }   
    }

    // Implementation for updating naked pairs in columns
    for (int col = 0; col < 9; ++col){
        std::vector<int> twoPossibleRows;
        for (int row = 0; row < 9; ++row){
            Cell& cell = board.getCell(row, col);
            if (cell.value == 0 && cell.numPossibleValues == 2){
                twoPossibleRows.push_back(row);
            }
        }
        for (size_t i = 0; i < twoPossibleRows.size(); ++i){
            for (size_t j = i + 1; j < twoPossibleRows.size(); ++j){
                Cell& cell1 = board.getCell(twoPossibleRows[i], col);
                Cell& cell2 = board.getCell(twoPossibleRows[j], col);
                if (samePossibleValues(cell1, cell2)){
                    for (int row = 0; row < 9; ++row){
                        if (row != twoPossibleRows[i] && row != twoPossibleRows[j]){
                            for (int num = 1; num <= 9; ++num){
                                if (cell1.possibleValues[num - 1]){
                                    board.getCell(row, col).eliminatePossibleValue(num);    
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Implementation for updating naked pairs in boxes
    for (int boxRow = 0; boxRow < 3; ++boxRow){
        for (int boxCol = 0; boxCol < 3; ++boxCol){
            std::vector<int> twoPossibleCells = getCellsWithTwoPossibleInBox(boxRow, boxCol);
            for (size_t i = 0; i < twoPossibleCells.size(); ++i){
                for (size_t j = i + 1; j < twoPossibleCells.size(); ++j){
                    int row1 = twoPossibleCells[i] / 9;
                    int col1 = twoPossibleCells[i] % 9;
                    int row2 = twoPossibleCells[j] / 9;
                    int col2 = twoPossibleCells[j] % 9;
                    Cell& cell1 = board.getCell(row1, col1);
                    Cell& cell2 = board.getCell(row2, col2);
                    if (samePossibleValues(cell1, cell2)){
                        for (int row = boxRow * 3; row < boxRow * 3 + 3; ++row){
                            for (int col = boxCol * 3; col < boxCol * 3 + 3; ++col){
                                if ((row != row1 || col != col1) && (row != row2 || col != col2)){
                                    for (int num = 1; num <= 9; ++num){
                                        if (cell1.possibleValues[num - 1]){
                                            board.getCell(row, col).eliminatePossibleValue(num);
                                        }   
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Solver::updatePossibleValues() {
    for (int row = 0; row < 9; ++row){
        for (int col = 0; col < 9; ++col){
            if (board.getCell(row, col).value != 0){
                continue; // Skip filled cells
            }
            board.getCell(row, col).resetPossibleValues();
            

            checkColumn(row, col);

            checkRow(row, col);

            checkBox(row, col);

            checkFeasability();
        }
    }

    checkPointingPairs();

    
}


bool Solver::fillCellWithOnePossibleValue(){
// Check for cells with only one possible value
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            Cell& cell = board.getCell(row, col);
            if (cell.value == 0 && cell.numPossibleValues == 1) {
                for (int num = 1; num <= 9; ++num) {
                    if (cell.possibleValues[num - 1]) {
                        board.writeToGrid(row, col, num);
                        return true; // Filled one cell, return true
                    }
                }
            }
        }
    }
    return false;
}


bool Solver::numberOnePossibleValueInRow() {
    for (int row = 0; row < 9; ++row) {
        for (int num = 1; num <= 9; ++num) {
            int count = 0;
            int lastCol = -1;
            for (int col = 0; col < 9; ++col) {
                Cell& cell = board.getCell(row, col);
                if (cell.value == 0 &&cell.possibleValues[num - 1]) {
                    count++;
                    lastCol = col;
                }
            }
            if (count == 1) {
                board.writeToGrid(row, lastCol, num);
                return true;
            }

        }
    }
    return false;
}

bool Solver::numberOnePossibleValueInCol() {
    for (int col = 0; col < 9; ++col){
        for (int num = 1; num <= 9; ++num) {
            int count = 0;
            int lastRow = -1;
            for (int row = 0; row < 9; ++row) {
                Cell& cell = board.getCell(row, col);
                if (cell.value == 0 &&cell.possibleValues[num - 1]) {
                    count++;
                    lastRow = row;
                }
            }
            if (count == 1) {
                board.writeToGrid(lastRow, col, num);
                return true;
            }
        }
    }
    return false;
}

bool Solver::numberOnePossibleValueInBox() {
    for (int boxRow = 0; boxRow < 3; ++boxRow) {
        for (int boxCol = 0; boxCol < 3; ++boxCol) {

    
            for (int num = 1; num <= 9; ++num) {
                int count = 0;
                int lastRow = -1;
                int lastCol = -1;
                for (int row = boxRow * 3; row < boxRow * 3 + 3; ++row) {
                    for (int col = boxCol * 3; col < boxCol * 3 + 3; ++col) {
                        Cell& cell = board.getCell(row, col);
                        if (cell.value == 0 &&cell.possibleValues[num - 1]) {
                            count++;
                            lastRow = row;
                            lastCol = col;
                        }
                    }
                }
                if (count == 1) {
                    board.writeToGrid(lastRow, lastCol, num);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Solver::solve() {
    updatePossibleValues();
    
    if (fillCellWithOnePossibleValue() || 
        numberOnePossibleValueInRow() || 
        numberOnePossibleValueInCol() || 
        numberOnePossibleValueInBox()) {

        return true; // Filled one cell, return true
    }
    

    return false;
}

bool Solver::solveAll() {
    bool progress = true;
    while (progress) {
        progress = solve(); // Keep solving until no more progress can be made
    }

    return board.checkSolution(); // Return true if the puzzle is solved
}
