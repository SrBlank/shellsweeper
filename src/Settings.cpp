/*
Settings.cpp
*/

#include <filesystem>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "Settings.hpp"

namespace fs = std::filesystem;

Settings::Settings() {
    easy = {9, 9, 10};
    medium = {16, 16, 40};
    hard = {30, 16, 99};

    centerGrid = true;
}

std::string Settings::getConfigPath() {
    const char* home = getenv("HOME");
    return std::string(home) + "/.config/shellsweeper/config.json";
}

void Settings::load() {

    std::string path = getConfigPath();

    const char* home = getenv("HOME");
    fs::create_directories(std::string(home) + "/.config/shellsweeper");

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
        if (pos == std::string::npos) return -1;

        pos = content.find(":", pos);
        size_t end = content.find(",", pos);
        return std::stoi(content.substr(pos + 1, end - pos - 1));
    };

    int w,h,m;

    w = readValue("easy_width");
    h = readValue("easy_height");
    m = readValue("easy_mines");
    if (w>0 && h>0 && m>0) easy = {w,h,m};

    w = readValue("medium_width");
    h = readValue("medium_height");
    m = readValue("medium_mines");
    if (w>0 && h>0 && m>0) medium = {w,h,m};

    w = readValue("hard_width");
    h = readValue("hard_height");
    m = readValue("hard_mines");
    if (w>0 && h>0 && m>0) hard = {w,h,m};

    int cg = readValue("centerGrid");
    if (cg >= 0)
        centerGrid = cg;
}

void Settings::save() {

    std::string path = getConfigPath();

    std::ofstream file(path);

    file << "{\n";

    file << "  \"easy_width\": "   << easy.width  << ",\n";
    file << "  \"easy_height\": "  << easy.height << ",\n";
    file << "  \"easy_mines\": "   << easy.mines  << ",\n";

    file << "  \"medium_width\": "  << medium.width  << ",\n";
    file << "  \"medium_height\": " << medium.height << ",\n";
    file << "  \"medium_mines\": "  << medium.mines  << ",\n";

    file << "  \"hard_width\": "  << hard.width  << ",\n";
    file << "  \"hard_height\": " << hard.height << ",\n";
    file << "  \"hard_mines\": "  << hard.mines  << ",\n";

    file << "  \"centerGrid\": " << centerGrid << "\n";

    file << "}\n";
}