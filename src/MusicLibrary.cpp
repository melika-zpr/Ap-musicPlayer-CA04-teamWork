#include "MusicLibrary.h"

MusicLibrary::MusicLibrary() {}

MusicLibrary::~MusicLibrary() {
    for (Song* song : songs) {
        delete song; 
    }
    songs.clear();
}

void MusicLibrary::addSong(Song* song)
{
    songs.push_back(song);
}

Song* MusicLibrary::getSong(int index) const
{
    if (index < 0 || index >= static_cast<int>(songs.size()))
        return nullptr;
    
    return songs[index];
}

Song* MusicLibrary::findByFilePath(const std::string& filePath) const
{
    for (Song* song : songs)
    {
        if (song->getFilePath() == filePath)
            return song;
    }

    return nullptr;
}

std::vector<Song*> MusicLibrary::filterByArtist(const std::string& artist) const
{
    std::vector<Song*> result;

    for (Song* song : songs)
    {
        if (song->getArtist() == artist)
            result.push_back(song);
    }

    return result;
}

std::vector<Song*> MusicLibrary::filterByAlbum(const std::string& album) const
{
    std::vector<Song*> result;

    for (Song* song : songs)
    {
        if (song->getAlbum() == album)
            result.push_back(song);
    }

    return result;
}

const std::vector<Song*>& MusicLibrary::getSongs() const
{
    return songs;
}

int MusicLibrary::size() const
{
    return songs.size();
}

void MusicLibrary::clear()
{
    for (Song* song : songs)
    {
        delete song;
    }

    songs.clear();
}