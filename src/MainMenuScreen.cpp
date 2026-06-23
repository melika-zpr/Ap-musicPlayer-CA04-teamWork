#include "MainMenuScreen.h"
#include "Song.h"
#include "Player.h"
#include "ConfigManager.h"
#include "UIRenderer.h"
#include "InputHandler.h"
#include <vector>
#include <string>

void MainMenuScreen::render() {
    // ۱. ابتدا نام آخرین آهنگ پخش شده را از کانفیگ می‌گیریم
    std::string lastSong = "";
    if (config_ != nullptr) {
        lastSong = config_->getLastSong();
    }
    
    // ۲. حالا کل باکس منو را به صورت کاملاً تراز شده و رنگی رندر می‌کنیم
    ui_->printMainMenu(lastSong);
}

void MainMenuScreen::displayLastPlayed() const {
    // این متد دیگر نیازی به چاپ چیزی ندارد، چون وظیفه آن را متد printMainMenu به بهترین شکل انجام می‌دهد.
    // می‌توانید بدنه آن را خالی بگذارید یا در صورت تمایل آن را از فایل هدر و اینجا کاملاً حذف کنید.
}

ScreenType MainMenuScreen::handleInput() {
    // دریافت انتخاب کاربر (بدون چاپ پرامپت تکراری، چون در printMainMenu چاپ شده است)
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