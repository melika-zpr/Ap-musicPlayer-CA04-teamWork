#include <iostream>

#include "Song.h"
#include "Playlist.h"
#include "Player.h"

int main()
{
    Song* song1 = new Song(
        "Bohemian Rhapsody",
        "Queen",
        "A Night at the Opera",
        "Rock",
        1975,
        354,
        "queen.mp3"
    );

    Song* song2 = new Song(
        "Numb",
        "Linkin Park",
        "Meteora",
        "Rock",
        2003,
        187,
        "numb.mp3"
    );

    Song* song3 = new Song(
        "Hotel California",
        "Eagles",
        "Hotel California",
        "Rock",
        1976,
        390,
        "hotel.mp3"
    );

    Playlist playlist("Favorites");
    playlist.addSong(song1);
    playlist.addSong(song2);
    playlist.addSong(song3);

    Player player;

    if (!player.loadPlaylist(&playlist))
    {
        std::cout << "Failed to load playlist.\n";
        return 0;
    }

    std::cout << "===== PLAY =====\n";
    player.play();

    std::cout << "\n===== SEEK +30 =====\n";
    player.seekForward(30);

    std::cout << "\n===== PAUSE =====\n";
    player.pause();

    std::cout << "\n===== RESUME =====\n";
    player.resume();

    std::cout << "\n===== NEXT =====\n";
    player.next();

    std::cout << "\n===== PREVIOUS =====\n";
    player.previous();

    std::cout << "\n===== TICK (5 sec) =====\n";
    for (int i = 0; i < 5; i++)
    {
        player.tick();
    }

    std::cout << "\n===== STOP =====\n";
    player.stop();

    delete song1;
    delete song2;
    delete song3;

    return 0;
}