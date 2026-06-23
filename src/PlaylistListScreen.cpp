#include "PlaylistListScreen.h"
#include "Player.h"
#include "Playlist.h"
#include "ConfigManager.h"
#include "UIRenderer.h"
#include "InputHandler.h"

void PlaylistListScreen::render() {
    ui_->printHeader("Playlist List");
    
    if (playlists_ == nullptr || playlists_->empty()) {
        ui_->printMessage("  No playlists available.");
    } else {
        ui_->printPlaylistList(*playlists_);
    }
    
    ui_->printMessage("");
    ui_->printMessage("  0. Back");
    ui_->printMessage("");
    ui_->printMessage("Select a playlist: ");
}

ScreenType PlaylistListScreen::handleInput() {
    if (playlists_ == nullptr || playlists_->empty()) {
        input_->waitForKey("Press Enter to continue...");
        return ScreenType::PLAYLIST_LIST;
    }
    
    int choice = input_->getIntChoice("", 0, static_cast<int>(playlists_->size()));
    
    if (choice == 0) {
        return ScreenType::MAIN_MENU;
    }
    
    int index = choice - 1;
    if (index >= 0 && index < static_cast<int>(playlists_->size())) {
        Playlist* selected = &(*playlists_)[index];
        if (player_ != nullptr) {
            player_->stop();
            player_->loadPlaylist(selected);
            if (config_ != nullptr) {
                config_->setActivePlaylist(selected->getName());
                config_->save();
            }
        }
    }
    
    return ScreenType::PLAYLIST_LIST;
}