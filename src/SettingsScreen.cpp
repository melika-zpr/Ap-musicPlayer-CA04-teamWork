#include "SettingsScreen.h"
#include "Player.h"
#include "ConfigManager.h"
#include "UIRenderer.h"
#include "InputHandler.h"
#include <string>

void SettingsScreen::render()
{
    if (config_ == nullptr)
    {
        ui_->printMessage("  Error: ConfigManager not initialized!");
        return;
    }

    PlaybackMode currentMode = config_->getPlaybackMode();
    std::string currentModeStr = ConfigManager::modeToString(currentMode);

    ui_->printSettingsView(currentModeStr);
}

ScreenType SettingsScreen::handleInput()
{
    if (config_ == nullptr)
        return ScreenType::SETTINGS;

    int choice = input_->getIntChoice("", 0, 4);

    if (choice == -2)
    {
        ui_->printMessage(" \u2716 Invalid choice. Please try again.");
        return ScreenType::SETTINGS;
    }

    if (choice == 0)
    {
        config_->save();
        return ScreenType::MAIN_MENU;
    }

    PlaybackMode newMode;
    switch (choice)
    {
    case 1:
        newMode = PlaybackMode::NO_REPEAT;
        break;
    case 2:
        newMode = PlaybackMode::REPEAT_ONE;
        break;
    case 3:
        newMode = PlaybackMode::REPEAT_ALL;
        break;
    case 4:
        newMode = PlaybackMode::SHUFFLE;
        break;
    default:
        return ScreenType::SETTINGS;
    }

    config_->setPlaybackMode(newMode);
    config_->save();

    if (player_ != nullptr)
    {
        player_->setPlaybackMode(newMode);
    }
    
    this->render();
    return ScreenType::SETTINGS; 
}