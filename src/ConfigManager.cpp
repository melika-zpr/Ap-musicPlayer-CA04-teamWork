#include "ConfigManager.h"
#include <fstream>
#include <iostream>
#include <algorithm>

ConfigManager::ConfigManager(const std::string& configPath)
    : configPath_(configPath) {
    data_["last_song"] = "";
    data_["playback_mode"] = "NO_REPEAT";
    data_["active_playlist"] = "";
    load();
    save();
}

void ConfigManager::load() {
    std::ifstream file(configPath_);
    if (!file.is_open()) {
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') {
            continue;
        }
        parseLine(line);
    }
    
    file.close();
}

void ConfigManager::save() const {
    std::ofstream file(configPath_);
    if (!file.is_open()) {
        std::cerr << "Warning: Cannot save config file: " << configPath_ << std::endl;
        return;
    }
    
    file << "# Music Player Configuration File" << std::endl;
    file << "# Generated automatically - do not edit manually" << std::endl;
    file << std::endl;
    
    for (const auto& pair : data_) {
        file << pair.first << "=" << pair.second << std::endl;
    }
    
    file.close();
}

std::string ConfigManager::getLastSong() const {
    auto it = data_.find("last_song");
    return (it != data_.end()) ? it->second : "";
}

PlaybackMode ConfigManager::getPlaybackMode() const {
    auto it = data_.find("playback_mode");
    if (it != data_.end()) {
        return stringToMode(it->second);
    }
    return PlaybackMode::NO_REPEAT;
}

std::string ConfigManager::getActivePlaylist() const {
    auto it = data_.find("active_playlist");
    return (it != data_.end()) ? it->second : "";
}

void ConfigManager::setLastSong(const std::string& filePath) {
    data_["last_song"] = filePath;
}

void ConfigManager::setPlaybackMode(PlaybackMode mode) {
    data_["playback_mode"] = modeToString(mode);
}

void ConfigManager::setActivePlaylist(const std::string& playlistName) {
    data_["active_playlist"] = playlistName;
}

std::string ConfigManager::modeToString(PlaybackMode mode) {
    switch (mode) {
        case PlaybackMode::NO_REPEAT:   return "NO_REPEAT";
        case PlaybackMode::REPEAT_ONE:  return "REPEAT_ONE";
        case PlaybackMode::REPEAT_ALL:  return "REPEAT_ALL";
        case PlaybackMode::SHUFFLE:     return "SHUFFLE";
        default:                        return "NO_REPEAT";
    }
}

PlaybackMode ConfigManager::stringToMode(const std::string& str) {
    std::string upper = str;
    std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
    
    if (upper == "NO_REPEAT")   return PlaybackMode::NO_REPEAT;
    if (upper == "REPEAT_ONE")  return PlaybackMode::REPEAT_ONE;
    if (upper == "REPEAT_ALL")  return PlaybackMode::REPEAT_ALL;
    if (upper == "SHUFFLE")     return PlaybackMode::SHUFFLE;
    
    return PlaybackMode::NO_REPEAT;
}

void ConfigManager::parseLine(const std::string& line) {
    size_t pos = line.find('=');
    if (pos == std::string::npos) {
        return;
    }
    
    std::string key = trim(line.substr(0, pos));
    std::string value = trim(line.substr(pos + 1));
    
    if (!key.empty()) {
        data_[key] = value;
    }
}

std::string ConfigManager::trim(const std::string& str) const {
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos) {
        return "";
    }
    
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(start, end - start + 1);
}

std::string ConfigManager::modeToDisplayString(PlaybackMode mode) {
    switch (mode) {
        case PlaybackMode::NO_REPEAT:   return "No Repeat";
        case PlaybackMode::REPEAT_ONE:  return "Repeat One";
        case PlaybackMode::REPEAT_ALL:  return "Repeat All";
        case PlaybackMode::SHUFFLE:     return "Shuffle";
        default:                        return "No Repeat";
    }
}