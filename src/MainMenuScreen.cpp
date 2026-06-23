#include "MainMenuScreen.h"
#include "Song.h"
#include "Player.h"
#include "ConfigManager.h"
#include "UIRenderer.h"
#include "InputHandler.h"
#include "ConfigManager.h" 
#include <vector>
#include <string>

void MainMenuScreen::render() {
    ui_->printHeader("Main Menu");
    ui_->printMessage("  1. Now Playing");
    ui_->printMessage("  2. View Playlists");
    ui_->printMessage("  3. Current Playlist Tracks");
    ui_->printMessage("  4. Settings");
    ui_->printMessage("  0. Exit Application");
    ui_->drawHorizontalLine("-", 50);
    displayLastPlayed();
    ui_->drawHorizontalLine("-", 50);
    ui_->printMessage("Enter option: ");
}

void MainMenuScreen::displayLastPlayed() const {
    if (config_ == nullptr) return;
    
    std::string lastSong = config_->getLastSong();
    if (!lastSong.empty()) {
        ui_->printMessage("  Last played: " + lastSong);
        ui_->printMessage("");
    }
}

ScreenType MainMenuScreen::handleInput() {
    int choice = input_->getIntChoice("", 0, 4);
    
    switch (choice) {
        case 1: return ScreenType::NOW_PLAYING;
        case 2: return ScreenType::PLAYLIST_LIST;
        case 3: return ScreenType::PLAYLIST_VIEW;
        case 4: return ScreenType::SETTINGS;
        case 0:
            if (config_ != nullptr) {
                if (player_ != nullptr && player_->getCurrentSong() != nullptr) {
                    config_->setLastSong(player_->getCurrentSong()->getFilePath());
                }
                config_->save();
            }
            return ScreenType::EXIT;
        default: return ScreenType::MAIN_MENU;
    }
}