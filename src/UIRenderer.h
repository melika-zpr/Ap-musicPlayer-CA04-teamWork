
#pragma once

#include <string>
#include <vector>

class Song;
class Playlist;

class UIRenderer {
public:
    UIRenderer() = default;

    struct PlaylistInfo {
    std::string name;
    int songCount;
    bool isActive;
    };

    struct TrackInfo {
    std::string title;
    std::string artist;
    bool isCurrent; 
    };
    
    void clearScreen() const;
    
    void drawHorizontalLine(const std::string& ch = "-", int width = 40) const;
    void drawBorder(const std::string& title = "", int width = 40) const;
    
    void printHeader(const std::string& title) const;
    void printFooter(const std::string& options) const;
    void printMessage(const std::string& message, bool newLine = true) const;
    void printError(const std::string& error) const;
    
    void printMenu(const std::vector<std::string>& items, 
                   const std::string& prompt = "Choice: ") const;
    
    void printSongList(const std::vector<Song*>& songs, 
                       int maxDisplay = 20) const;
    
    void printPlaylistList(const std::vector<PlaylistInfo>& playlists) const;
    
    void printNowPlaying(const Song *song, float currentTime, float totalTime, bool isPaused, const std::string& mode, const std::string& playlistName) const;    void printSettings(const std::string& currentMode) const;
    void printPlaylistView(const std::string& playlistName, const std::vector<TrackInfo>& tracks) const;
    void printSettingsView(const std::string& currentModeStr) const;
    void printMainMenu(const std::string& lastPlayedSong) const;  
    void gotoxy(int x, int y) const;
    void hideCursor() const;

private:
    std::string formatDuration(int seconds) const;
    std::string truncate(const std::string& str, size_t maxLen) const;
};