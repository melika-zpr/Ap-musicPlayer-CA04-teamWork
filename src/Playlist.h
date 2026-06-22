#pragma once

#include <string>
#include <vector>
#include "Song.h"


class Playlist {
private:
    std::string name_;             
    std::vector<Song*> songs_;     

public:

    Playlist() = default;
    Playlist(const std::string& name);
    Playlist(const std::string& name, const std::vector<Song*>& songs);
   
    std::string getName() const;
    Song* getSong(int index) const;
    
    int size() const;
    bool isEmpty() const;
   
    const std::vector<Song*>& getSongs() const;
   
    void setName(const std::string& name);
   
    void addSong(Song* song);
    
    void addSongs(const std::vector<Song*>& songs);
   
    void clear();
  
    bool contains(Song* song) const;
    
    int indexOf(Song* song) const;
    
    std::vector<Song*> filterByArtist(const std::string& artist) const;
    
    std::vector<Song*> filterByAlbum(const std::string& album) const;
    
    std::vector<Song*> search(const std::string& query) const;
    
    std::string toString() const;
};