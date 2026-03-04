/*
main.cpp
*/

#include <iostream>
#include <vector>
#include <ncurses.h>

#include "Game.hpp"
#include "Renderer.hpp"
#include "Settings.hpp"

enum class AppState {
    Menu,
    PlayMenu,
    CustomGame,
    Playing,
    Settings,
    Quit
}; 

int main() {
    Settings settings;
    settings.load();
    settings.save();

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

    std::vector<std::string> menuItems = {
        "Play",
        "Settings",
        "Quit"
    };
    std::vector<std::string> playMenuItems = {
        "Easy",
        "Medium",
        "Hard",
        "Custom",
        "Back"
    };
    
    int playMenuIndex = 0;
    int menuIndex = 0;
    int customIndex = 0;
    int settingsIndex = 0;

    int cursorX = 0;
    int cursorY = 0;

    int customWidth = 20;
    int customHeight = 20;
    int customMines = 50;

    int boardWidth = settings.easy.width;
    int boardHeight = settings.easy.height;
    int mineCount = settings.easy.mines;
    bool centerGrid = settings.centerGrid;
        
    AppState state = AppState::Menu;
    Game game(boardWidth, boardHeight, mineCount);

    while (state != AppState::Quit) {
        // --- Menu State ---
        if (state == AppState::Menu){
            Renderer::drawMenu(menuItems, menuIndex);

            int ch = getch();
            switch (ch) {
                case KEY_UP:
                    if (menuIndex > 0) menuIndex--;
                    break;

                case KEY_DOWN:
                    if (menuIndex < static_cast<int>(menuItems.size()) - 1) menuIndex++;
                    break;

                case 10: // ENTER
                    if (menuIndex == 0) {
                        game = Game(boardWidth, boardHeight, mineCount);
                        cursorX = 0;
                        cursorY = 0;
                        state = AppState::PlayMenu;
                    }

                    if (menuIndex == 1) 
                        state = AppState::Settings;

                    if (menuIndex == 2)
                        state = AppState::Quit;
                    break;
                }
        }

        if (state == AppState::PlayMenu) {
            Renderer::drawMenu(playMenuItems, playMenuIndex);

            int ch = getch();
            switch (ch) {
                case KEY_UP:
                    if (playMenuIndex > 0) playMenuIndex--;
                    break;

                case KEY_DOWN:
                    if (playMenuIndex < static_cast<int>(playMenuItems.size()) - 1)
                        playMenuIndex++;
                    break;

                case 10: // ENTER
                    if (playMenuIndex == 0) { // Easy
                        boardWidth = settings.easy.width;
                        boardHeight = settings.easy.height;
                        mineCount = settings.easy.mines;
                        game = Game(boardWidth, boardHeight, mineCount);
                        cursorX = 0;
                        cursorY = 0;
                        state = AppState::Playing;
                    }

                    if (playMenuIndex == 1) { // Medium
                        boardWidth = settings.medium.width;
                        boardHeight = settings.medium.height;
                        mineCount = settings.medium.mines;
                        game = Game(boardWidth, boardHeight, mineCount);
                        cursorX = 0;
                        cursorY = 0;
                        state = AppState::Playing;
                    }

                    if (playMenuIndex == 2) { // Hard
                        if (COLS < settings.medium.width * 3)
                            centerGrid = false;
                        boardWidth = settings.hard.width;
                        boardHeight = settings.hard.height;
                        mineCount = settings.hard.mines;
                        game = Game(boardWidth, boardHeight, mineCount);
                        cursorX = 0;
                        cursorY = 0;
                        state = AppState::Playing;
                    }

                    if (playMenuIndex == 3)
                        state = AppState::CustomGame;

                    if (playMenuIndex == 4) // Back
                        state = AppState::Menu;
                    break;

                case 'q':
                    state = AppState::Menu;
                    break;
            }
        }

        // --- Game State ---
        if (state == AppState::Playing) { 
            const Board& board = game.getBoard();
            int height = board.getHeight();
            int width = board.getWidth();
            
            Renderer::drawGame(game, cursorX, cursorY, centerGrid);

            int ch = getch();
            switch (ch) {
                case 'q':
                    state = AppState::Menu;
                    break;

                case 'r':
                    if (game.getState() != GameState::Running)
                        game = Game(boardWidth, boardHeight, mineCount);
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

        // --- CustomGame State ---
        if (state == AppState::CustomGame) {
            Renderer::drawCustomGame( customWidth, customHeight, customMines,customIndex);
            
            int ch = getch();
            switch(ch) {
                case KEY_UP:
                    if (customIndex > 0) customIndex--;
                    break;

                case KEY_DOWN:
                    if (customIndex < 4) customIndex++;
                    break;

                case KEY_LEFT:
                    if (customIndex == 0 && customWidth > 5) customWidth--;
                    if (customIndex == 1 && customHeight > 5) customHeight--;
                    if (customIndex == 2 && customMines > 1) customMines--;
                    break;

                case KEY_RIGHT:
                    if (customIndex == 0) customWidth++;
                    if (customIndex == 1) customHeight++;
                    if (customIndex == 2) customMines++;
                    break;

                case 10:
                    if (customIndex == 3) {
                        boardWidth = customWidth;
                        boardHeight = customHeight;
                        mineCount = customMines;

                        game = Game(boardWidth, boardHeight, mineCount);
                        cursorX = 0;
                        cursorY = 0;

                        state = AppState::Playing;
                    }

                    if (customIndex == 4)
                        state = AppState::PlayMenu;
                    break;

                case 'q':
                    state = AppState::PlayMenu;
                    break;
            }
            if (customMines >= customWidth * customHeight)
                customMines = customWidth * customHeight - 1;
        }

        // --- Settings State ---
        if (state == AppState::Settings) {
            Renderer::drawSettings(centerGrid, settingsIndex);

            int ch = getch();
            switch (ch) {
                case KEY_UP:
                    if (settingsIndex > 0)
                        settingsIndex--;
                    break;

                case KEY_DOWN:
                    if (settingsIndex < 1)
                        settingsIndex++;
                    break;

                case 10: // ENTER
                    if (settingsIndex == 0) {
                        centerGrid = !centerGrid;
                        settings.centerGrid = centerGrid;
                        settings.save();
                    }

                    if (settingsIndex == 1) 
                        state = AppState::Menu;
                    break;

                case 'q':
                    state = AppState::Menu;
                    break;
            }
        }
    }
    

    endwin();
    return 0;
}