#include "Application.h"

#include "CsvLoader.h"
#include "M3uLoader.h"
#include "ConfigManager.h"
#include "Player.h"
#include "MusicLibrary.h"
#include "Playlist.h"
#include "Song.h"
#include "UIRenderer.h"
#include "InputHandler.h"
#include "MainMenuScreen.h"
#include "NowPlayingScreen.h"
#include "PlaylistListScreen.h"
#include "PlaylistViewScreen.h"
#include "SettingsScreen.h"

#include <iostream>

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_MS(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP_MS(ms) usleep((ms) * 1000)
#endif


Application::Application() {
    loadData();
    setupScreens();
    
    if (!playlists_.empty()) {
        player_.loadPlaylist(&playlists_[0]);
    }
    
    config_.load();
    player_.setPlaybackMode(config_.getPlaybackMode());
    
    changeScreen(ScreenType::MAIN_MENU);
}

Application::~Application() {
    if (player_.getCurrentSong() != nullptr) {
        config_.setLastSong(player_.getCurrentSong()->getTitle());
    }
    config_.setPlaybackMode(player_.getPlaybackMode());
    if (player_.getCurrentPlaylist() != nullptr) {
        config_.setActivePlaylist(player_.getCurrentPlaylist()->getName());
    }
    config_.save();
}

void Application::loadData() {
    CsvLoader csvLoader;
    std::vector<std::string> errors;
    
    if (csvLoader.load("Data/library.csv", library_, errors)) {
        std::cout << "[App] Loaded " << library_.size() << " songs from CSV." << std::endl;
    } else {
        std::cerr << "[App] Failed to load CSV." << std::endl;
    }
    
    M3uLoader::loadPlaylists("Data/Playlists", library_, playlists_, errors);
    
    std::string activeName = config_.getActivePlaylist();
    for (auto& playlist : playlists_) {
        if (playlist.getName() == activeName) {
            player_.loadPlaylist(&playlist);
            break;
        }
    }
}

void Application::setupScreens() {
    mainMenuScreen_.setPlayer(&player_);
    mainMenuScreen_.setConfigManager(&config_);
    mainMenuScreen_.setPlaylists(&playlists_);
    mainMenuScreen_.setUIRenderer(&ui_);
    mainMenuScreen_.setInputHandler(&input_);
    
    nowPlayingScreen_.setPlayer(&player_);
    nowPlayingScreen_.setConfigManager(&config_);
    nowPlayingScreen_.setPlaylists(&playlists_);
    nowPlayingScreen_.setUIRenderer(&ui_);
    nowPlayingScreen_.setInputHandler(&input_);
    
    playlistListScreen_.setPlayer(&player_);
    playlistListScreen_.setConfigManager(&config_);
    playlistListScreen_.setPlaylists(&playlists_);
    playlistListScreen_.setUIRenderer(&ui_);
    playlistListScreen_.setInputHandler(&input_);
    
    playlistViewScreen_.setPlayer(&player_);
    playlistViewScreen_.setConfigManager(&config_);
    playlistViewScreen_.setPlaylists(&playlists_);
    playlistViewScreen_.setUIRenderer(&ui_);
    playlistViewScreen_.setInputHandler(&input_);
    
    settingsScreen_.setPlayer(&player_);
    settingsScreen_.setConfigManager(&config_);
    settingsScreen_.setPlaylists(&playlists_);
    settingsScreen_.setUIRenderer(&ui_);
    settingsScreen_.setInputHandler(&input_);
}

void Application::changeScreen(ScreenType type) {
    switch (type) {
        case ScreenType::MAIN_MENU:
            currentScreen_ = &mainMenuScreen_;
            break;
        case ScreenType::NOW_PLAYING:
            currentScreen_ = &nowPlayingScreen_;
            break;
        case ScreenType::PLAYLIST_LIST:
            currentScreen_ = &playlistListScreen_;
            break;
        case ScreenType::PLAYLIST_VIEW:
            currentScreen_ = &playlistViewScreen_;
            break;
        case ScreenType::SETTINGS:
            currentScreen_ = &settingsScreen_;
            break;
        case ScreenType::EXIT:
            currentScreen_ = nullptr;
            isRunning_ = false;
            break;
        default:
            currentScreen_ = nullptr;
            break;
    }
}

void Application::run() {
    while (isRunning_ && currentScreen_ != nullptr) {
        player_.tick();
        currentScreen_->render();
        ScreenType next = currentScreen_->handleInput();
        if (next != currentScreen_->getType()) {
            changeScreen(next);
        }
        SLEEP_MS(100);
    }
    config_.save();
}