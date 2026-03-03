/*
main.cpp
*/

#include <iostream>
#include <ncurses.h>

#include "Game.hpp"

int main() {
    Game game(8, 8, 10);

    int cursorX = 0;
    int cursorY = 0;

    // --- ncurses setup ---
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();

    init_pair(1, COLOR_BLUE,    COLOR_BLACK);
    init_pair(2, COLOR_GREEN,   COLOR_BLACK);
    init_pair(3, COLOR_RED,     COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW,  COLOR_BLACK);
    init_pair(6, COLOR_CYAN,    COLOR_BLACK);
    init_pair(7, COLOR_WHITE,   COLOR_BLACK);
    init_pair(8, COLOR_WHITE,   COLOR_BLACK);
    
    bool running = true;

    while (running) {
        clear();

        const Board& board = game.getBoard();
        int width = board.getWidth();
        int height = board.getHeight();

        // --- Render Board ---
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {

                move(y, x * 3);

                bool isCursor = (x == cursorX && y == cursorY);
                if (isCursor) {
                    attron(A_REVERSE);
                }

                const Cell& cell = board.getCell(x, y);

                if (!cell.revealed) {
                    if (cell.flagged)
                        addch('F');
                    else
                        addch('#');
                }
                else if (cell.isMine) {
                    addch('x');
                } 
                else {
                    int n = cell.adjacentMines;
                    if (n > 0) {
                        attron(COLOR_PAIR(n));
                        addch('0' + n);
                        attroff(COLOR_PAIR(n));
                    } else {
                        addch('.');
                    }
                }

                if (isCursor) {
                    attroff(A_REVERSE);
                }
            }
        }

        move(height + 2, 0);
        printw("Mines Remaining: %d", game.getMinesRemaining());

        // --- Render Status ---
        move(height + 1, 0);

        if (game.getState() == GameState::Lost) {
            printw("Status: Lost (press q)");
        } 
        else if (game.getState() == GameState::Won) {
            printw("Status: Won! (press q)");
        } 
        else {
            printw("Status: Running");
        }

        refresh();

        int ch = getch();

        switch (ch) {
            case 'q':
                running = false;
                break;

            case KEY_UP:
                if (cursorY > 0) cursorY--;
                break;

            case KEY_DOWN:
                if (cursorY < height - 1) cursorY++;
                break;

            case KEY_LEFT:
                if (cursorX > 0) cursorX--;
                break;

            case KEY_RIGHT:
                if (cursorX < width - 1) cursorX++;
                break;

            case ' ':
                game.reveal(cursorX, cursorY);
                break;

            case 'f':
                game.toggleFlag(cursorX, cursorY);
                break;
        }
    }

    endwin();
    return 0;
}