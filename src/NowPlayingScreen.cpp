#include "NowPlayingScreen.h"
#include "Player.h"
#include "Song.h"
#include "Playlist.h"
#include "ConfigManager.h"
#include "UIRenderer.h"
#include "InputHandler.h"

void NowPlayingScreen::render() {
    if (player_ == nullptr) {
        ui_->printMessage("  Error: Player not initialized.");
        return;
    }

    Song* currentSong = player_->getCurrentSong();
    
    // اگر آهنگی در حال پخش نیست
    if (currentSong == nullptr) {
        ui_->printNowPlaying(nullptr, 0.0f, 0.0f, true, "NO_REPEAT", "None");
    } else {
        // محاسبه زمان‌ها بر اساس متدهایی که در کد قبلی داشتی
        float currentTime = static_cast<float>(player_->getCurrentPosition());
        float totalTime = static_cast<float>(currentSong->getDurationSec());
        bool isPaused = (player_->getState() == PlayerState::Paused);
        
        // ارسال دقیق ۴ آرگومان مورد نیاز به رندرر
        ui_->printNowPlaying(
            currentSong, 
            currentTime, 
            totalTime, 
            isPaused, 
            ConfigManager::modeToDisplayString(config_->getPlaybackMode()), // تبدیل enum به string
            player_->getCurrentPlaylist() ? player_->getCurrentPlaylist()->getName() : "None"
        );
    }
}

ScreenType NowPlayingScreen::handleInput() {
    if (player_ == nullptr) return ScreenType::MAIN_MENU;

    char key = input_->getCharKey("");

    switch (key) {
        case 'p':
        case 'P':
            // استفاده از منطق صحیح وضعیت پخش که در کد قبلی داشتی
            if (player_->getState() == PlayerState::Playing) {
                player_->pause();
            } else if (player_->getState() == PlayerState::Paused) {
                player_->resume();
            } else {
                player_->play();
            }
            break;

        case 's':
        case 'S':
            player_->stop();
            break;

        case 'n':
        case 'N':
            player_->next();
            break;

        case 'b':
        case 'B':
            player_->previous();
            break;

        case 'f':
        case 'F':
            player_->seekForward(10); // اصلاح نام متد بر اساس کدهای قبلی شما
            break;

        case 'r':
        case 'R':
            player_->seekBackward(10); // اصلاح نام متد بر اساس کدهای قبلی شما
            break;

        case 'q':
        case 'Q':
            return ScreenType::MAIN_MENU;

        default:
            break;
    }

    return ScreenType::NOW_PLAYING;
}