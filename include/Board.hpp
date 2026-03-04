/*
Board.hpp
*/

#pragma once

#include <vector>
#include "Cell.hpp"

class Board {
public:
    Board(int width, int height, int mineCount);
    
    int reveal(int x, int y);
    void revealAllMines();
    void toggleFlag(int x, int y);

    int getWidth() const;
    int getHeight() const;
    int getMineCount() const;
    const Cell& getCell(int x, int y) const;
    
    void printDebug() const;
private:
    int width;
    int height;
    int mineCount;

    std::vector<std::vector<Cell>> grid;
    
    int floodFill(int x, int y);
    void placeMines();
    void calculateAdjacencies();
    bool inBounds(int x, int y) const;
};