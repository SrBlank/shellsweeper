/*
Renderer.hpp
*/

#pragma once

#include <vector>
#include <string>

#include "Game.hpp"

namespace Renderer {

void drawMenu(
    const std::vector<std::string>& items,
    int selected
);

void drawGame(
    const Game& game,
    int cursorX,
    int cursorY,
    bool centerGrid
);

void drawCustomGame(
    int width,
    int height,
    int mines,
    int selectedIndex
);

void drawSettings(
    bool centerGrid, 
    int selectedIndex
);

}