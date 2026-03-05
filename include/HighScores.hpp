/*
HighScores.hpp
*/

#pragma once
#include <string>

struct ScoreSet {
    int easy;
    int medium;
    int hard;
};

class HighScores {
public:
    HighScores();

    void load();
    void save();

    void updateEasy(int time);
    void updateMedium(int time);
    void updateHard(int time);

    ScoreSet scores;

private:
    std::string getScorePath();
};