/*
Game.cpp
*/

#include "Game.hpp"
#include <iostream>

Game::Game(int width, int height, int mineCount)
    : board(width, height, mineCount),
      state(GameState::Running),
      revealedSafeCells(0),
      totalSafeCells(width * height - mineCount),
      flagsPlaced(0),
      timerStarted(false)
{}

void Game::reveal(int x, int y) {
    if (state != GameState::Running) {
        return;
    }

    if (!timerStarted) {
        startTime = std::chrono::steady_clock::now();
        timerStarted = true;
    }

    int result = board.reveal(x, y);

    if (result == -1) {
        state = GameState::Lost;
        board.revealAllMines();
        return;
    }

    if (result > 0) {
        revealedSafeCells += result;

        if (revealedSafeCells == totalSafeCells) {
            state = GameState::Won;
        }
    }
}

void Game::toggleFlag(int x, int y) {
    if (state != GameState::Running) return;

    const Cell& cell = board.getCell(x, y);

    if (cell.revealed) return;

    if (cell.flagged)
        flagsPlaced--;
    else
        flagsPlaced++;

    board.toggleFlag(x, y);
}

int Game::getElapsedTime() const {
    if (!timerStarted)
        return 0;

    auto now = std::chrono::steady_clock::now();

    return std::chrono::duration_cast<std::chrono::seconds>(
        now - startTime
    ).count();
}

int Game::getFlagsPlaced() const {
    return flagsPlaced;
}

int Game::getMinesRemaining() const {
    return board.getMineCount() - flagsPlaced;
}

GameState Game::getState() const {
    return state;
}

const Board& Game::getBoard() const {
    return board;
}