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
        void checkFeasability(int row, int col);
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

        void eliminatePossibleValueInRow(int row, int num, int excludeCol);
        void eliminatePossibleValueInCol(int col, int num, int excludeRow);
        std::vector<int> getPossibleRowsForNumInCol(int num, int col);
        std::vector<int> getPossibleColsForNumInRow(int num, int row);
        std::vector<int> getPossibleLocationsForNumInBox(int num, int boxRow, int boxCol);
        void updateHiddenPairs();
        
};