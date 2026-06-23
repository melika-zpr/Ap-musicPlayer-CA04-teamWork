#pragma once

#include "Player.h"
#include "ConfigManager.h"
#include "MusicLibrary.h"
#include "Playlist.h"
#include "UIRenderer.h"
#include "InputHandler.h"
#include "MainMenuScreen.h"
#include "NowPlayingScreen.h"
#include "PlaylistListScreen.h"
#include "PlaylistViewScreen.h"
#include "SettingsScreen.h"
#include <vector>

class Application {
public:
    Application();
    ~Application();
    
    void run();
    
private:
    void loadData();
    void setupScreens();
    void changeScreen(ScreenType type);
    
    MusicLibrary library_;
    std::vector<Playlist> playlists_;
    
    Player player_;
    ConfigManager config_;
    UIRenderer ui_;
    InputHandler input_;
    
    MainMenuScreen mainMenuScreen_;
    NowPlayingScreen nowPlayingScreen_;
    PlaylistListScreen playlistListScreen_;
    PlaylistViewScreen playlistViewScreen_;
    SettingsScreen settingsScreen_;
    
    Screen* currentScreen_ = nullptr;
    bool isRunning_ = true;
};