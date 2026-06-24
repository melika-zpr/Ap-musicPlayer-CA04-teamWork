#include "MainMenuScreen.h"
#include "Player.h"
#include "ConfigManager.h"
#include "UIRenderer.h"
#include "InputHandler.h"
#include <string>

void MainMenuScreen::render()
{
    std::string lastSong = "None";
    if (config_ != nullptr)
    {
        // این همان رشته‌ای است که در فایل تنظیمات ذخیره شده
        std::string savedTitle = config_->getLastSong();
        if (!savedTitle.empty())
        {
            lastSong = savedTitle;
        }
    }
    ui_->printMainMenu(lastSong);
}

ScreenType MainMenuScreen::handleInput()
{
    int choice = input_->getIntChoice("", 0, 4);

    if (choice == -1 ) {
        return ScreenType::MAIN_MENU; 
    }


    if (choice == -2)
    {
        ui_->printMessage(" \u2716 Invalid choice. Please try again.");
        return ScreenType::MAIN_MENU;
    }
    switch (choice)
    {
    case 1:
        return ScreenType::NOW_PLAYING;
    case 2:
        return ScreenType::PLAYLIST_LIST;
    case 3:
        return ScreenType::PLAYLIST_VIEW;
    case 4:
        return ScreenType::SETTINGS;

    case 0:
        if (config_ != nullptr && player_ != nullptr && player_->getCurrentSong() != nullptr)
        {
            // تغییر از getFilePath به getTitle:
            config_->setLastSong(player_->getCurrentSong()->getTitle());
        }
        if (config_ != nullptr)
        {
            config_->save();
        }
        return ScreenType::EXIT;

    default:
        return ScreenType::MAIN_MENU;
    }
}