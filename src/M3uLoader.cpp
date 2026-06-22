#include "M3uLoader.h"
#include "Playlist.h"
#include "MusicLibrary.h"
#include "Song.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstring>

#ifdef _WIN32
    #include <windows.h>
    #include <dirent.h> 
#else
    #include <dirent.h>
    #include <sys/stat.h>
#endif


static bool isDirectory(const std::string& path) {
#ifdef _WIN32
    DWORD attr = GetFileAttributesA(path.c_str());
    return (attr != INVALID_FILE_ATTRIBUTES) && (attr & FILE_ATTRIBUTE_DIRECTORY);
#else
    struct stat statbuf;
    if (stat(path.c_str(), &statbuf) != 0)
        return false;
    return S_ISDIR(statbuf.st_mode);
#endif
}

static bool fileExists(const std::string& path) {
#ifdef _WIN32
    DWORD attr = GetFileAttributesA(path.c_str());
    return (attr != INVALID_FILE_ATTRIBUTES);
#else
    struct stat statbuf;
    return (stat(path.c_str(), &statbuf) == 0);
#endif
}


bool M3uLoader::loadPlaylists(const std::string& directoryPath,
                              const MusicLibrary& library,
                              std::vector<Playlist>& playlists,
                              std::vector<std::string>& errorMessages) {
    playlists.clear();
    errorMessages.clear();
    
    if (!isDirectory(directoryPath)) {
        errorMessages.push_back("Directory does not exist: " + directoryPath);
        return false;
    }
    
    int loadedCount = 0;
    
    DIR* dir = opendir(directoryPath.c_str());
    if (dir == nullptr) {
        errorMessages.push_back("Cannot open directory: " + directoryPath);
        return false;
    }
    
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        std::string fileName = entry->d_name;
        std::string fullPath = directoryPath + "/" + fileName;
        
        if (isM3uFile(fileName)) {
            Playlist playlist;
            std::string errorMessage;
            
            if (loadSinglePlaylist(fullPath, library, playlist, errorMessage)) {
                playlists.push_back(playlist);
                loadedCount++;
            } else {
                errorMessages.push_back("Failed to load " + fullPath + ": " + errorMessage);
            }
        }
    }
    
    closedir(dir);
    
    return loadedCount > 0;
}

bool M3uLoader::loadSinglePlaylist(const std::string& filePath,
                                   const MusicLibrary& library,
                                   Playlist& playlist,
                                   std::string& errorMessage) {
    errorMessage.clear();
    
    if (!fileExists(filePath)) {
        errorMessage = "File does not exist: " + filePath;
        return false;
    }
    
    std::ifstream file(filePath);
    if (!file.is_open()) {
        errorMessage = "Cannot open file: " + filePath;
        return false;
    }
    
    std::string playlistName = getPlaylistName(filePath);
    playlist.setName(playlistName);
    
    std::string line;
    int loadedSongs = 0;
    
    while (std::getline(file, line)) {
        line = trim(line);
        
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        Song* song = library.findByFilePath(line);
        
        if (song != nullptr) {
            playlist.addSong(song);
            loadedSongs++;
        }
    }
    
    file.close();
    
    if (loadedSongs == 0) {
        errorMessage = "No valid songs found in " + filePath;
        return false;
    }
    
    return true;
}

bool M3uLoader::isM3uFile(const std::string& filePath) {
    std::string lowerPath = filePath;
    std::transform(lowerPath.begin(), lowerPath.end(), lowerPath.begin(), ::tolower);
    
    return lowerPath.size() >= 4 && lowerPath.substr(lowerPath.size() - 4) == ".m3u";
}

std::string M3uLoader::getPlaylistName(const std::string& filePath) {
    size_t lastSlash = filePath.find_last_of("/\\");
    std::string filename = (lastSlash != std::string::npos) ? 
                           filePath.substr(lastSlash + 1) : filePath;
    
    size_t lastDot = filename.find_last_of('.');
    if (lastDot != std::string::npos) {
        filename = filename.substr(0, lastDot);
    }
    
    if (filename.empty()) {
        filename = "unknown";
    }
    
    return filename;
}

std::string M3uLoader::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos) {
        return "";
    }
    
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(start, end - start + 1);
}