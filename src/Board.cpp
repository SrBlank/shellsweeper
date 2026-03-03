/*
Board.cpp
*/

#include "Board.hpp"
#include <iostream>
#include <random>
#include <list>

Board::Board(int width, int height, int mineCount)
    : width(width),
      height(height),
      mineCount(mineCount),
      grid(height, std::vector<Cell>(width))
{
    placeMines();
    calculateAdjacencies();
}

void Board::placeMines(){
    std::random_device rd;
    std::mt19937 gen(rd());

    int mineCounter = 0;
    std::uniform_int_distribution<> xdistrib(0, width-1);
    std::uniform_int_distribution<> ydistrib(0, height-1);

    while(mineCounter < mineCount){
        int xrand = xdistrib(gen);
        int yrand = ydistrib(gen);
        if(!grid[yrand][xrand].isMine){
            grid[yrand][xrand].isMine = true;
            mineCounter++;
        }
    }
}

void Board::calculateAdjacencies() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            if (grid[y][x].isMine)
                continue;

            int count = 0;

            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {

                    if (dx == 0 && dy == 0) continue;
                    

                    int nx = x + dx;
                    int ny = y + dy;

                    if (inBounds(nx, ny) && grid[ny][nx].isMine)
                        count++;
                }
            }

            grid[y][x].adjacentMines = count;
        }
    }
}

int Board::floodFill(int x, int y) {
    int count = 0;

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {

            if (dx == 0 && dy == 0) continue;

            int nx = x + dx;
            int ny = y + dy;

            if (!inBounds(nx, ny)) continue;
            if (grid[ny][nx].revealed) continue;
            if (grid[ny][nx].isMine) continue;

            grid[ny][nx].revealed = true;
            count++;

            if (grid[ny][nx].adjacentMines == 0)
                count += floodFill(nx, ny);
        }
    }

    return count;
}

int Board::reveal(int x, int y) {
    if (!inBounds(x, y)) return 0;
    if (grid[y][x].revealed) return 0;
    if (grid[y][x].flagged) return 0;

    grid[y][x].revealed = true;

    if (grid[y][x].isMine)
        return -1;

    int count = 1; 
    if (grid[y][x].adjacentMines == 0)
        count += floodFill(x, y);

    return count;
}

void Board::toggleFlag(int x, int y) {
    if (!inBounds(x, y)) return;

    Cell& cell = grid[y][x];

    if (cell.revealed) return;
    cell.flagged = !cell.flagged;
}

void Board::revealAllMines() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (grid[y][x].isMine) {
                grid[y][x].revealed = true;
            }
        }
    }
}

bool Board::inBounds(int x, int y) const {
    return x >= 0 && x < width &&
           y >= 0 && y < height;
}

int Board::getHeight() const {
    return height;
}

int Board::getWidth() const {
    return width;
}

int Board::getMineCount() const {
    return mineCount;
}

const Cell& Board::getCell(int x, int y) const {
    return grid[y][x];
}

void Board::printDebug() const {
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if (!grid[i][j].revealed)
                std::cout << "#";
            else if (grid[i][j].isMine)
                std::cout << "x";
            else
                std::cout << grid[i][j].adjacentMines;
        }
        std::cout << "\n";
    }
}