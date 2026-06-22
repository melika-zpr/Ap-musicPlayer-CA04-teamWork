#pragma once

#include <string>
#include <vector>

#include "Song.h"
#include "MusicLibrary.h"

class CsvLoader
{
public:
    CsvLoader() = default;

    bool load(const std::string& filePath,
              MusicLibrary& library,
              std::vector<std::string>& errorMessages);

    bool load(const std::string& filePath,
              MusicLibrary& library);

    static bool parseLine(const std::string& line,
                          Song& song,
                          std::string& errorMessage);

private:
    static std::vector<std::string> split(const std::string& str, char delimiter);
    static std::string trim(const std::string& str);
};