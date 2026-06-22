#include <thread>
#include <chrono>
#include "Player.h"
#include "Playlist.h"
#include "Song.h"
#include "CsvLoader.h"
#include "M3uLoader.h"
#include "MusicLibrary.h"
#include <iostream>

int main() {
    std::cout << "Starting Player integration test..." << std::endl;

    std::cout << "Creating MusicLibrary..." << std::endl;
    MusicLibrary library;

    std::cout << "Loading CSV library..." << std::endl;
    CsvLoader csvLoader;
    if (!csvLoader.load("Data/library.csv", library)) {
        std::cerr << "Failed to load library from Data/library.csv." << std::endl;
        return 1;
    }

    std::vector<Playlist> playlists;
    std::vector<std::string> errors;

    std::cout << "Loading playlists..." << std::endl;
    if (!M3uLoader::loadPlaylists("Data/Playlists", library, playlists, errors)) {
        std::cerr << "Failed to load playlists." << std::endl;
        for (const auto& err : errors) {
            std::cerr << err << std::endl;
        }
        return 1;
    }
    if (playlists.empty()) {
        std::cerr << "No playlists loaded." << std::endl;
        return 1;
    }

    std::cout << "Creating Player..." << std::endl;
    Player player;
    std::cout << "Loading first playlist..." << std::endl;
    if (!player.loadPlaylist(&playlists.front())) {
        std::cerr << "Failed to load playlist into player." << std::endl;
        return 1;
    }

    std::cout << "Setting playback mode to NO_REPEAT..." << std::endl;
    player.setPlaybackMode(PlaybackMode::NO_REPEAT);

    std::cout << "Playing..." << std::endl;
    player.play();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "Pausing..." << std::endl;
    player.pause();
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "Resuming..." << std::endl;
    player.resume();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "Seeking forward 10 seconds..." << std::endl;
    player.seekForward(10);
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << "Seeking backward 5 seconds..." << std::endl;
    player.seekBackward(5);
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << "Skipping to next song..." << std::endl;
    player.next();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "Returning to previous song..." << std::endl;
    player.previous();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "Stopping playback..." << std::endl;
    player.stop();

    std::cout << "Player integration test completed successfully." << std::endl;
    return 0;
}