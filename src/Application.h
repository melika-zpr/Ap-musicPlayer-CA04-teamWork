#pragma once

#include <vector>

#include "ScreenManager.h"
#include "UIRenderer.h"
#include "InputHandler.h"

#include "Player.h"
#include "ConfigManager.h"
#include "MusicLibrary.h"
#include "Playlist.h"

class Application {
private:
    void loadData();

    ScreenManager screenManager;

    MusicLibrary library_;
    std::vector<Playlist> playlists_;

    Player player_;
    ConfigManager config_;

    UIRenderer uiRenderer;
    InputHandler input_;

public:
    Application();
    ~Application();

    void init();
    void run();
    void shutdown();
};