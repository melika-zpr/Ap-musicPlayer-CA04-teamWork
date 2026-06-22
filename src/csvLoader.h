#pragma once

#include <string>
#include <vector>
#include "Song.h"


class CsvLoader {
public:
   
    CsvLoader() = default;   

    bool load(const std::string& filePath, 
              std::vector<Song>& songs, 
              std::vector<std::string>& errorMessages);
    
   
    bool load(const std::string& filePath, std::vector<Song>& songs);
       
    static bool parseLine(const std::string& line, 
                         Song& song, 
                         std::string& errorMessage);
    
private:
   
    static std::vector<std::string> split(const std::string& str, char delimiter);
    static std::string trim(const std::string& str);
};