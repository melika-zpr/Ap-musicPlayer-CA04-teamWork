#pragma once

#include <string>
#include <vector>
#include "Playlist.h"
#include "MusicLibrary.h"


class M3uLoader {
public:
    
    static bool loadPlaylists(const std::string& directoryPath,
                              const MusicLibrary& library,
                              std::vector<Playlist>& playlists,
                              std::vector<std::string>& errorMessages);
    

    static bool loadSinglePlaylist(const std::string& filePath,
                                   const MusicLibrary& library,
                                   Playlist& playlist,
                                   std::string& errorMessage);
    
private:
   
    static bool isM3uFile(const std::string& filePath);
    static std::string getPlaylistName(const std::string& filePath);
    static std::string trim(const std::string& str);
};