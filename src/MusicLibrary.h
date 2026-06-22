#pragma once

#include <vector>
#include <string>

#include "Song.h"

class MusicLibrary
{
private:
    std::vector<Song*> songs;

public:
    MusicLibrary();
    ~MusicLibrary();

    void addSong(Song* song);

    Song* getSong(int index) const;

    Song* findByFilePath(const std::string& filePath) const;

    std::vector<Song*> filterByArtist(const std::string& artist) const;
    std::vector<Song*> filterByAlbum(const std::string& album) const;

    const std::vector<Song*>& getSongs() const;

    int size() const;
};