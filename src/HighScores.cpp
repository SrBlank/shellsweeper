/*
HighScores.cpp
*/

#include "HighScores.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <cstdlib>

namespace fs = std::filesystem;

HighScores::HighScores() {
    scores.easy = 9999;
    scores.medium = 9999;
    scores.hard = 9999;
}

std::string HighScores::getScorePath() {
    const char* home = getenv("HOME");
    return std::string(home) + "/.local/share/shellsweeper/highscores.json";
}

void HighScores::load() {

    std::string path = getScorePath();

    const char* home = getenv("HOME");
    fs::create_directories(std::string(home) + "/.local/share/shellsweeper");

    if (!fs::exists(path)) {
        save();
        return;
    }

    std::ifstream file(path);
    if (!file)
        return;

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    auto readValue = [&](const std::string& key) -> int {

        size_t pos = content.find(key);
        if (pos == std::string::npos)
            return -1;

        pos = content.find(":", pos);

        size_t end = content.find(",", pos);
        if (end == std::string::npos)
            end = content.find("}", pos);

        return std::stoi(content.substr(pos + 1, end - pos - 1));
    };

    int value;

    value = readValue("easy");
    if (value >= 0)
        scores.easy = value;

    value = readValue("medium");
    if (value >= 0)
        scores.medium = value;

    value = readValue("hard");
    if (value >= 0)
        scores.hard = value;
}

void HighScores::save() {
    std::string path = getScorePath();

    std::ofstream file(path);

    file << "{\n";
    file << "  \"easy\": " << scores.easy << ",\n";
    file << "  \"medium\": " << scores.medium << ",\n";
    file << "  \"hard\": " << scores.hard << "\n";
    file << "}\n";
}

void HighScores::updateEasy(int time) {
    if (time < scores.easy) {
        scores.easy = time;
        save();
    }
}

void HighScores::updateMedium(int time) {
    if (time < scores.medium) {
        scores.medium = time;
        save();
    }
}

void HighScores::updateHard(int time) {
    if (time < scores.hard) {
        scores.hard = time;
        save();
    }
}