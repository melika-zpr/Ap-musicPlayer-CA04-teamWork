#include "Player.h"
#include "Playlist.h"
#include "Song.h"
#include "CsvLoader.h"
#include "M3uLoader.h"
#include "MusicLibrary.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    using namespace std;
    cout << "Creating MusicLibrary..." << endl;
    MusicLibrary library;

    cout << "Loading library from CSV..." << endl;
    CsvLoader csvLoader;
    if (!csvLoader.load("Data/library.csv", library)) {
        cout << "Failed to load library from CSV" << endl;
        return 1;
    }

    cout << "Loading playlists from M3U files..." << endl;
    std::vector<Playlist> playlists;
    std::vector<std::string> errors;

    if (!M3uLoader::loadPlaylists("Data/Playlists", library, playlists, errors)) {
        cout << "Failed to load playlists" << endl;
        for (const auto& error : errors)
            cout << error << endl;
        return 1;
    }

    if (playlists.empty()) {
        cout << "No playlists loaded from M3U files" << endl;
        return 1;
    }

    cout << "Obtaining first loaded playlist..." << endl;
    Playlist* playlist = &playlists.front();

    cout << "Creating Player and loading playlist..." << endl;
    Player player;
    if (!player.loadPlaylist(playlist)) {
        cout << "Failed to load playlist" << endl;
        return 1;
    }

    cout << "Calling play()..." << endl;
    player.play();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    cout << "Calling pause()..." << endl;
    player.pause();
    std::this_thread::sleep_for(std::chrono::seconds(2));

    cout << "Calling resume()..." << endl;
    player.resume();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    cout << "Calling next()..." << endl;
    player.next();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    cout << "Calling previous()..." << endl;
    player.previous();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    cout << "Calling stop()..." << endl;
    player.stop();

    cout << "Integration test finished successfully." << endl;

    return 0;
}