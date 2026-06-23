#include "SettingsScreen.h"
#include "Player.h"
#include "ConfigManager.h"
#include "UIRenderer.h"
#include "InputHandler.h"

void SettingsScreen::render() {
    ui_->printHeader("Settings");
    
    if (config_ == nullptr) {
        ui_->printError("ConfigManager not initialized!");
        return;
    }
    
    PlaybackMode currentMode = config_->getPlaybackMode();
    ui_->printSettings(ConfigManager::modeToString(currentMode));
    ui_->printMessage("");
    ui_->printMessage("  0. Back (changes saved automatically)");
    ui_->printMessage("");
}

ScreenType SettingsScreen::handleInput() {
    if (config_ == nullptr) return ScreenType::SETTINGS;
    
    int choice = input_->getIntChoice("", 0, 4);
    
    if (choice == 0) {
        config_->save();
        return ScreenType::MAIN_MENU;
    }
    
    PlaybackMode newMode;
    switch (choice) {
        case 1: newMode = PlaybackMode::NO_REPEAT; break;
        case 2: newMode = PlaybackMode::REPEAT_ONE; break;
        case 3: newMode = PlaybackMode::REPEAT_ALL; break;
        case 4: newMode = PlaybackMode::SHUFFLE; break;
        default: return ScreenType::SETTINGS;
    }
    
    config_->setPlaybackMode(newMode);
    config_->save();
    
    if (player_ != nullptr) {
        player_->setPlaybackMode(newMode);
    }
    
    return ScreenType::SETTINGS;
}