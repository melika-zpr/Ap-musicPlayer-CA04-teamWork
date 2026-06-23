#include "SettingsScreen.h"
#include "Player.h"
#include "ConfigManager.h"
#include "UIRenderer.h"
#include "InputHandler.h"
#include <string>

void SettingsScreen::render() {
    if (config_ == nullptr) {
        // استفاده از باکس خطای رندرر به جای چاپ ساده متنی
        ui_->printMessage("  Error: ConfigManager not initialized!");
        return;
    }
    
    // گرفتن حالت پخش فعلی به صورت رشته (مثل "Shuffle" یا "Repeat One")
    PlaybackMode currentMode = config_->getPlaybackMode();
    std::string currentModeStr = ConfigManager::modeToString(currentMode);
    
    // ارسال به رندرر باکس‌ساز جدید
    ui_->printSettingsView(currentModeStr);
}

ScreenType SettingsScreen::handleInput() {
    if (config_ == nullptr) return ScreenType::SETTINGS;
    
    // دریافت انتخاب کاربر بدون چاپ متن اضافه (چون پرامپت را خود باکس چاپ کرده است)
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
    
    // اعمال تنظیمات جدید روی کانفیگ و ذخیره‌سازی آن
    config_->setPlaybackMode(newMode);
    config_->save();
    
    // اعمال همزمان روی موتور پلیر
    if (player_ != nullptr) {
        player_->setPlaybackMode(newMode);
    }
    
    return ScreenType::SETTINGS; // ماندن در صفحه تنظیمات جهت مشاهده آپدیت تیک سبز رنگ گزینه‌ها
}