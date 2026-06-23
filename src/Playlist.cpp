#include "Playlist.h"
#include <algorithm>
#include <cctype>
#include <sstream>

Playlist::Playlist(const std::string& name) 
    : name_(name) {}

Playlist::Playlist(const std::string& name, const std::vector<Song*>& songs)
    : name_(name), songs_(songs) {}

std::string Playlist::getName() const {
    return name_;
}

Song* Playlist::getSong(int index) const {
    if (index < 0 || index >= static_cast<int>(songs_.size())) {
        return nullptr;
    }
    return songs_[index];
}

int Playlist::size() const {
    return static_cast<int>(songs_.size());
}

bool Playlist::isEmpty() const {
    return songs_.empty();
}

const std::vector<Song*>& Playlist::getSongs() const {
    return songs_;
}


void Playlist::setName(const std::string& name) {
    name_ = name;
}

void Playlist::addSong(Song* song) {
    if (song != nullptr) {
        songs_.push_back(song);
    }
}

void Playlist::addSongs(const std::vector<Song*>& songs) {
    for (Song* song : songs) {
        if (song != nullptr) {
            songs_.push_back(song);
        }
    }
}

void Playlist::clear() {
    songs_.clear();  
}

bool Playlist::contains(Song* song) const {
    return std::find(songs_.begin(), songs_.end(), song) != songs_.end();
}

int Playlist::indexOf(Song* song) const {
    auto it = std::find(songs_.begin(), songs_.end(), song);
    if (it != songs_.end()) {
        return static_cast<int>(std::distance(songs_.begin(), it));
    }
    return -1;
}


std::vector<Song*> Playlist::filterByArtist(const std::string& artist) const {
    std::vector<Song*> result;
    
    for (Song* song : songs_) {
        if (song != nullptr && song->getArtist() == artist) {
            result.push_back(song);
        }
    }
    
    return result;
}

std::vector<Song*> Playlist::filterByAlbum(const std::string& album) const {
    std::vector<Song*> result;
    
    for (Song* song : songs_) {
        if (song != nullptr && song->getAlbum() == album) {
            result.push_back(song);
        }
    }
    
    return result;
}

std::vector<Song*> Playlist::search(const std::string& query) const {
    std::vector<Song*> result;
    if (query.empty()) return songs_;
    
    std::string lowerQuery = query;
    std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);
    
    for (Song* song : songs_) {
        if (song == nullptr) continue;
        
        std::string lowerTitle = song->getTitle();
        std::string lowerArtist = song->getArtist();
        std::string lowerAlbum = song->getAlbum(); 
        
        std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);
        std::transform(lowerArtist.begin(), lowerArtist.end(), lowerArtist.begin(), ::tolower);
        std::transform(lowerAlbum.begin(), lowerAlbum.end(), lowerAlbum.begin(), ::tolower);
        
        if (lowerTitle.find(lowerQuery) != std::string::npos ||
            lowerArtist.find(lowerQuery) != std::string::npos ||
            lowerAlbum.find(lowerQuery) != std::string::npos) {
            result.push_back(song);
        }
    }
    return result;
}

std::string Playlist::toString() const {
    std::ostringstream oss;
    oss << name_ << " (" << songs_.size() << " songs)";
    return oss.str();
}
