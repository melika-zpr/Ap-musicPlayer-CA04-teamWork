#include "CsvLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

bool CsvLoader::load(const std::string& filePath, 
                     std::vector<Song>& songs, 
                     std::vector<std::string>& errorMessages) {
   
    songs.clear();
    errorMessages.clear();
    
    std::ifstream file(filePath);
    if (!file.is_open()) {
        errorMessages.push_back("Cannot open file: " + filePath);
        return false;
    }
    
    std::string line;
    int lineNumber = 0;
    bool hasHeader = true;
    
    while (std::getline(file, line)) {
        lineNumber++;
        
        line = trim(line);
        
        if (line.empty()) {
            continue;
        }
        
        if (hasHeader && lineNumber == 1) {
            if (line.find("title") != std::string::npos || 
                line.find("Title") != std::string::npos) {
                continue;
            }
            hasHeader = false;
        }
        
        Song song;
        std::string errorMessage;
        
        if (parseLine(line, song, errorMessage)) {
            if (song.isValid()) {
                songs.push_back(song);
            } else {
                errorMessages.push_back("Line " + std::to_string(lineNumber) + 
                                      ": Invalid song data (missing required fields)");
            }
        } else {
            errorMessages.push_back("Line " + std::to_string(lineNumber) + 
                                  ": " + errorMessage);
        }
    }
    
    file.close();
    
    return !songs.empty();
}

bool CsvLoader::load(const std::string& filePath, std::vector<Song>& songs) {
    std::vector<std::string> errorMessages;
    return load(filePath, songs, errorMessages);
}

bool CsvLoader::parseLine(const std::string& line, 
                         Song& song, 
                         std::string& errorMessage) {
    errorMessage.clear();
    
    std::vector<std::string> fields = split(line, ',');
    
    if (fields.size() != 7) {
        errorMessage = "Expected 7 fields, got " + std::to_string(fields.size());
        return false;
    }
    
    try {
        std::string title = trim(fields[0]);
        std::string artist = trim(fields[1]);
        std::string album = trim(fields[2]);
        std::string genre = trim(fields[3]);
        
        std::string yearStr = trim(fields[4]);
        int year = 0;
        if (!yearStr.empty()) {
            year = std::stoi(yearStr);
        }
        
        std::string durationStr = trim(fields[5]);
        int durationSec = 0;
        if (!durationStr.empty()) {
            durationSec = std::stoi(durationStr);
        }
        
        std::string filePath = trim(fields[6]);
        
        song = Song(title, artist, album, genre, year, durationSec, filePath);
        
        if (!song.isValid()) {
            errorMessage = "Invalid song data";
            return false;
        }
        
        return true;
        
    } catch (const std::invalid_argument& e) {
        errorMessage = "Invalid number format: " + std::string(e.what());
        return false;
    } catch (const std::out_of_range& e) {
        errorMessage = "Number out of range: " + std::string(e.what());
        return false;
    } catch (const std::exception& e) {
        errorMessage = "Unexpected error: " + std::string(e.what());
        return false;
    }
}


std::vector<std::string> CsvLoader::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

std::string CsvLoader::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos) {
        return "";  
    }
    
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    
    return str.substr(start, end - start + 1);
}