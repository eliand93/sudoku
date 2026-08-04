#pragma once

#include <vector>
#include "board.hpp"


 class Solver {
    private:
        Board& board;

    public:
        Solver(Board& board);
        void updatePossibleValues();
        void checkColumn(int row, int col);
        void checkRow(int row, int col);
        void checkBox(int row, int col);
        void checkFeasability();
        void checkPointingPairs();
        bool solve();
        bool solveAll();

        bool fillCellWithOnePossibleValue();
        bool numberOnePossibleValueInRow();
        bool numberOnePossibleValueInCol();
        bool numberOnePossibleValueInBox();

        std::vector<int> getCellsWithTwoPossibleInRow(int row);
        std::vector<int> getCellsWithTwoPossibleInCol(int col);
        void updateNakedPairs();
        std::vector<int> getCellsWithTwoPossibleInBox(int boxRow, int boxCol);
        bool samePossibleValues(const Cell& cell1, const Cell& cell2);
        
};