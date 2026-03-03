/*
Cell.hpp
*/

#pragma once

class Cell {
public:
    Cell();

    bool isMine;
    bool revealed;
    bool flagged;
    
    int adjacentMines;
};