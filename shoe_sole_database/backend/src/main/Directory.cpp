#include "../include/Directory.hpp"
#include "../include/Data.hpp"

#include <filesystem>
#include <iostream>
#include <string>

bool Directory::createIMGPath() {
    std::filesystem::perms::all;
    if(!std::filesystem::exists(imgPath)) {
        std::filesystem::create_directory(imgPath);
    }

    return true;
}