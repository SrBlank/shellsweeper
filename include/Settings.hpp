/*
Settings.hpp
*/

#pragma once

#include <string>

struct Difficulty {
    int width;
    int height;
    int mines;
};

class Settings {
public:
    Settings();

    Difficulty easy;
    Difficulty medium;
    Difficulty hard;

    bool centerGrid;

    void load();
    void save();

private:
    std::string getConfigPath();
};