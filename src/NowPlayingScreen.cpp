#include "NowPlayingScreen.h"
#include "Player.h"
#include "Song.h"
#include "UIRenderer.h"
#include "InputHandler.h"

void NowPlayingScreen::render() {
    ui_->printHeader("Now Playing");
    
    if (player_ == nullptr) {
        ui_->printError("Player not initialized!");
        return;
    }
    
    Song* currentSong = player_->getCurrentSong();
    if (currentSong == nullptr) {
        ui_->printMessage("  No song is currently playing.");
        ui_->printMessage("");
        ui_->printMessage("  Select a playlist and press play.");
        ui_->printMessage("");
    } else {
        float currentTime = static_cast<float>(player_->getCurrentPosition());
        float totalTime = static_cast<float>(currentSong->getDurationSec());
        
        ui_->printNowPlaying(currentSong, currentTime, totalTime, player_->getState() == PlayerState::Paused);
        
        std::string status;
        switch (player_->getState()) {
            case PlayerState::Playing: status = "▶ Playing"; break;
            case PlayerState::Paused:  status = "⏸ Paused"; break;
            case PlayerState::Stopped: status = "⏹ Stopped"; break;
        }
        ui_->printMessage("  Status: " + status);
        ui_->printMessage("");
    }
    
    ui_->drawHorizontalLine("-", 50);
    ui_->printMessage("  [p] Play/Pause/Resume  [s] Stop  [n] Next  [b] Previous");
    ui_->printMessage("  [f] Forward 10s        [r] Backward 10s  [q] Back to Menu");
    ui_->drawHorizontalLine("-", 50);
}

ScreenType NowPlayingScreen::handleInput() {
    char key = input_->getCharKey("");
    if (player_ == nullptr) return ScreenType::NOW_PLAYING;
    
    switch (key) {
        case 'p':
            if (player_->getState() == PlayerState::Playing) {
                player_->pause();
            } else if (player_->getState() == PlayerState::Paused) {
                player_->resume();
            } else {
                player_->play();
            }
            break;
        case 's':
            player_->stop();
            break;
        case 'n':
            player_->next();
            break;
        case 'b':
            player_->previous();
            break;
        case 'f':
            player_->seekForward(10);
            break;
        case 'r':
            player_->seekBackward(10);
            break;
        case 'q':
            return ScreenType::MAIN_MENU;
        default:
            break;
    }
    return ScreenType::NOW_PLAYING;
}