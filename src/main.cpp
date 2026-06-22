#include <iostream>

#include "MusicLibrary.h"

using namespace std;

int main()
{
    MusicLibrary library;

    library.addSong(new Song(
        "Bohemian Rhapsody",
        "Queen",
        "A Night at the Opera",
        "Rock",
        1975,
        354,
        "/music/bohemian.mp3"));

    library.addSong(new Song(
        "Don't Stop Me Now",
        "Queen",
        "Jazz",
        "Rock",
        1978,
        210,
        "/music/dontstop.mp3"));

    library.addSong(new Song(
        "Hotel California",
        "Eagles",
        "Hotel California",
        "Rock",
        1977,
        391,
        "/music/hotel.mp3"));

    cout << "Total Songs: " << library.size() << endl;

    auto queenSongs = library.filterByArtist("Queen");

    cout << endl;
    cout << "Queen Songs:" << endl;

    for (Song* song : queenSongs)
    {
        cout << song->getTitle() << endl;
    }

    Song* s = library.findByFilePath("/music/hotel.mp3");

    if (s != nullptr)
    {
        cout << endl;
        cout << "Found: " << s->getTitle() << endl;
    }
}