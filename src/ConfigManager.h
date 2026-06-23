#pragma once

#include <string>
#include <map>
#include "PlaybackMode.h" 


class ConfigManager {
public:
    ConfigManager(const std::string& configPath = "settings.cfg");
    
    void load();
    void save() const;
    
    std::string getLastSong() const;
    PlaybackMode getPlaybackMode() const;
    std::string getActivePlaylist() const;
    
    void setLastSong(const std::string& filePath);
    void setPlaybackMode(PlaybackMode mode);
    void setActivePlaylist(const std::string& playlistName);
    
    static std::string modeToString(PlaybackMode mode);
    static PlaybackMode stringToMode(const std::string& str);
    static std::string modeToDisplayString(PlaybackMode mode);
    
private:
    std::string configPath_;
    std::map<std::string, std::string> data_;
    
    void parseLine(const std::string& line);
    std::string trim(const std::string& str) const;
};