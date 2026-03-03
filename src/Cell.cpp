/*
Cell.cpp
*/

#include "Cell.hpp"

Cell::Cell()
    : isMine(false),
      revealed(false),
      flagged(false),
      adjacentMines(0)
{}
