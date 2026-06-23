#pragma once

#include <string>
#include <vector>

class Player;
class ConfigManager;
class Playlist;
class UIRenderer;
class InputHandler;

enum class ScreenType {
    MAIN_MENU,
    NOW_PLAYING,
    PLAYLIST_LIST,
    PLAYLIST_VIEW,
    SETTINGS,
    EXIT
};

class Screen {
public:
    virtual ~Screen() = default;
    
    virtual void render() = 0;
    virtual ScreenType handleInput() = 0;
    virtual ScreenType getType() const = 0;
    
    void setPlayer(Player* player) { player_ = player; }
    void setConfigManager(ConfigManager* config) { config_ = config; }
    void setPlaylists(std::vector<Playlist>* playlists) { playlists_ = playlists; }
    void setUIRenderer(UIRenderer* ui) { ui_ = ui; }
    void setInputHandler(InputHandler* input) { input_ = input; }
    
protected:
    Player* player_ = nullptr;
    ConfigManager* config_ = nullptr;
    std::vector<Playlist>* playlists_ = nullptr;
    UIRenderer* ui_ = nullptr;
    InputHandler* input_ = nullptr;
};