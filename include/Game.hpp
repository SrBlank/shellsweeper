/*
Game.hpp
*/

#pragma once

#include "Board.hpp"

enum class GameState {
    Running,
    Won,
    Lost
};

class Game {
public:
    Game(int width, int height, int mineCount);

    void reveal(int x, int y);
    void toggleFlag(int x, int y);

    int getFlagsPlaced() const;
    int getMinesRemaining() const;

    GameState getState() const;
    const Board& getBoard() const;
private:
    Board board;
    GameState state;

    int revealedSafeCells;
    int totalSafeCells;
    int flagsPlaced;
};