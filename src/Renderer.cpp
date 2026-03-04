/*
Renderer.cpp
*/

#include <vector>
#include <string>
#include <ncurses.h>

#include "Renderer.hpp"

namespace Renderer {

void drawMenu(const std::vector<std::string>& items, int selected) {

    clear();

    std::string title = "ShellSweeper";
    mvprintw(LINES/2 - 4, (COLS - title.size())/2, "%s", title.c_str());

    for (size_t i = 0; i < items.size(); i++) {

        int y = LINES/2 + i;
        int x = (COLS - items[i].size()) / 2;

        if (i == selected)
            attron(A_REVERSE);

        mvprintw(y, x, "%s", items[i].c_str());

        if (i == selected)
            attroff(A_REVERSE);
    }

    refresh();
}


void drawGame(const Game& game, int cursorX, int cursorY, bool centerGrid) {
    clear();

    const Board& board = game.getBoard();
    int width = board.getWidth();
    int height = board.getHeight();

    int startX = 0;
    int startY = 0;

    if (centerGrid) {
        int gridWidth = width * 4;
        int gridHeight = height;

        startX = (COLS - gridWidth) / 2;
        startY = (LINES - gridHeight) / 2;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            int drawX = centerGrid ? startX + x * 4 : x * 4;
            int drawY = centerGrid ? startY + y : y;

            const Cell& cell = board.getCell(x, y);

            bool isCursor = (x == cursorX && y == cursorY);
            if (isCursor)
                attron(A_REVERSE);

            // draw box
            mvprintw(drawY, drawX, "[ ]");

            char symbol = ' ';

            if (!cell.revealed) {
                symbol = cell.flagged ? 'F' : ' ';
            }
            else if (cell.isMine) {
                symbol = 'x';
            }
            else if (cell.adjacentMines > 0) {
                symbol = '0' + cell.adjacentMines;
            }
            else {
                symbol = '.';
            }

            move(drawY, drawX + 1);

            if (cell.revealed && cell.adjacentMines > 0) {
                attron(COLOR_PAIR(cell.adjacentMines));
                addch(symbol);
                attroff(COLOR_PAIR(cell.adjacentMines));
            } else {
                addch(symbol);
            }

            if (isCursor)
                attroff(A_REVERSE);
        }
    }

    if (centerGrid)
        move(startY + height + 2, startX);
    else
        move(height + 2, 0);

    printw("Mines Remaining: %d", game.getMinesRemaining());

    if (centerGrid)
        move(startY + height + 1, startX);
    else
        move(height + 1, 0);

    if (game.getState() == GameState::Lost)
        printw("You Lost! (r = restart, q = menu)");
    else if (game.getState() == GameState::Won)
        printw("You Won! (r = restart, q = menu)");
    else
        printw("Status: Running");

    refresh();
}

void drawCustomGame(
    int customWidth,
    int customHeight,
    int customMines,
    int selectedIndex
) {

    clear();

    mvprintw(LINES/2 - 3, COLS/2 - 6, "Custom Game");

    std::vector<std::string> labels = {
        "Width",
        "Height",
        "Mines",
        "Start",
        "Back"
    };

    for (int i = 0; i < labels.size(); i++) {

        int y = LINES/2 + i;
        int x = COLS/2 - 10;

        if (i == selectedIndex)
            attron(A_REVERSE);

        if (i == 0)
            mvprintw(y, x, "Width:  %d", customWidth);

        else if (i == 1)
            mvprintw(y, x, "Height: %d", customHeight);

        else if (i == 2)
            mvprintw(y, x, "Mines:  %d", customMines);

        else
            mvprintw(y, x, "%s", labels[i].c_str());

        if (i == selectedIndex)
            attroff(A_REVERSE);
    }

    refresh();
}

void drawSettings(bool centerGrid, int selectedIndex) {

    clear();

    std::string title = "Settings";
    mvprintw(LINES/2 - 3, (COLS - title.size())/2, "%s", title.c_str());

    std::vector<std::string> items = {
        "Center Grid",
        "Back"
    };

    for (int i = 0; i < items.size(); i++) {

        int y = LINES/2 + i;
        int x = COLS/2 - 10;

        if (i == selectedIndex)
            attron(A_REVERSE);

        if (i == 0) {
            mvprintw(y, x, "Center Grid: %s", centerGrid ? "ON" : "OFF");
        }
        else {
            mvprintw(y, x, "%s", items[i].c_str());
        }

        if (i == selectedIndex)
            attroff(A_REVERSE);
    }

    refresh();
}

}