#include "PlaylistListScreen.h"
#include "Player.h"
#include "Playlist.h"
#include "ConfigManager.h"
#include "UIRenderer.h"
#include "InputHandler.h"
#include <vector>
#include <string>

void PlaylistListScreen::render() {
    std::vector<UIRenderer::PlaylistInfo> uiPlaylists;
    
    // پیدا کردن نام پلی‌لیست فعال فعلی از کانفیگ
    std::string activePlaylistName = "";
    if (config_ != nullptr) {
        activePlaylistName = config_->getActivePlaylist(); // فرض بر وجود متد Getter
    }

    // تبدیل ساختار داده پروژه به ساختار داده منسجم UI
    if (playlists_ != nullptr) {
        for (const auto& playlist : *playlists_) {
            UIRenderer::PlaylistInfo info;
            info.name = playlist.getName();
            
            // دریافت تعداد آهنگ‌ها (اگر نام متد در پروژه شما متفاوت است آن را اصلاح کنید، مثلاً getSongCount() )
            info.songCount = static_cast<int>(playlist.getSongs().size()); 
            
            // سنجش فعال بودن
            info.isActive = (info.name == activePlaylistName);
            
            uiPlaylists.push_back(info);
        }
    }
    
    // رندر یکپارچه جدول طلایی-خاکستری
    ui_->printPlaylistList(uiPlaylists);
}

ScreenType PlaylistListScreen::handleInput() {
    int maxChoice = (playlists_ != nullptr) ? static_cast<int>(playlists_->size()) : 0;
    int choice = input_->getIntChoice("", 0, maxChoice);
    
    if (choice == 0) {
        return ScreenType::MAIN_MENU;
    }
    
    int index = choice - 1;
    if (playlists_ != nullptr && index >= 0 && index < maxChoice) {
        Playlist* selected = &(*playlists_)[index];
        if (player_ != nullptr) {
            player_->stop();
            player_->loadPlaylist(selected);
            
            // شلیک دستور پخش! (اضافه شدن این خط باعث می‌شود آهنگ بلافاصله شروع شود)
            player_->play(); 
            
            if (config_ != nullptr) {
                config_->setActivePlaylist(selected->getName());
                config_->save();
            }
        }
    }
    
    return ScreenType::PLAYLIST_LIST;
}