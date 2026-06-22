#include <iostream>
#include <thread>
#include <chrono>

#include "Player.h"
#include "MusicLibrary.h"
#include "CsvLoader.h"
#include "M3uLoader.h"


void print(Player& player)
{
    Song* s = player.getCurrentSong();

    if(s)
        std::cout
        << "Current: "
        << s->getTitle()
        << std::endl;
}


int main()
{

    MusicLibrary library;

    CsvLoader csv;

    csv.load(
        "Data/library.csv",
        library
    );


    std::vector<Playlist> playlists;

    std::vector<std::string> errors;


    M3uLoader::loadPlaylists(
        "Data/Playlists",
        library,
        playlists,
        errors
    );


    Player player;


    player.loadPlaylist(
        &playlists[0]
    );


    // =========================
    // TEST NO_REPEAT
    // =========================

    std::cout<<"\nNO_REPEAT\n";


    player.setPlaybackMode(
        PlaybackMode::NO_REPEAT
    );


    print(player);


    player.next();

    print(player);



    // =========================
    // TEST REPEAT_ALL
    // =========================


    std::cout<<"\nREPEAT_ALL\n";


    player.setPlaybackMode(
        PlaybackMode::REPEAT_ALL
    );


    for(int i=0;i<10;i++)
    {
        player.next();

        print(player);
    }



    // =========================
    // TEST SHUFFLE
    // =========================


    std::cout<<"\nSHUFFLE\n";


    player.setPlaybackMode(
        PlaybackMode::SHUFFLE
    );


    for(int i=0;i<10;i++)
    {

        player.tick();

        player.next();

        print(player);

    }


    return 0;
}