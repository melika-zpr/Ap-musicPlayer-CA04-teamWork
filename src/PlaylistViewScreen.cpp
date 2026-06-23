#include "PlaylistViewScreen.h"
#include "Player.h"
#include "Playlist.h"
#include "Song.h"
#include "UIRenderer.h"
#include "InputHandler.h"
#include <algorithm>
#include <set>
#include <iostream>

Playlist* PlaylistViewScreen::getActivePlaylist() const {
    if (player_ == nullptr) return nullptr;
    return player_->getCurrentPlaylist();
}

void PlaylistViewScreen::initializeSongs(Playlist* playlist) {
    if (playlist != nullptr) {
        displayedSongs_ = playlist->getSongs();
        lastPlaylist_ = playlist;
    }
}

void PlaylistViewScreen::render() {
    Playlist* playlist = getActivePlaylist();
    
    // اگر پلی‌لیست تغییر کرده، لیست را رفرش می‌کنیم
    if (playlist != lastPlaylist_) {
        initializeSongs(playlist);
        subScreen_ = PlaylistSubScreen::DEFAULT;
    }

    // حالت خالی
    if (playlist == nullptr || playlist->isEmpty()) {
        ui_->printPlaylistView("None", {});
        return;
    }

    // رندر کردن لیست به کمک باکس هوشمند و متقارن
    if (subScreen_ == PlaylistSubScreen::DEFAULT) {
        std::vector<UIRenderer::TrackInfo> uiTracks;
        Song* currentSong = (player_ != nullptr) ? player_->getCurrentSong() : nullptr;

        for (Song* song : displayedSongs_) {
            if (!song) continue;
            UIRenderer::TrackInfo track;
            track.title = song->getTitle();
            track.artist = song->getArtist();
            track.isCurrent = (currentSong != nullptr && currentSong->getFilePath() == song->getFilePath());
            uiTracks.push_back(track);
        }
        
        // نام پلی‌لیست به همراه تعداد آهنگ‌های فیلتر شده/نمایش داده شده
        std::string displayName = playlist->getName() + " (" + std::to_string(displayedSongs_.size()) + ")";
        ui_->printPlaylistView(displayName, uiTracks);
    }
}

// توابع قدیمی displayPlaylist و displaySubMenu کاملاً حذف شدند چون رندرر هوشمند کارشان را انجام می‌دهد.

ScreenType PlaylistViewScreen::handleInput() {
    Playlist* playlist = getActivePlaylist();
    if (playlist == nullptr || playlist->isEmpty()) {
        input_->waitForKey("Press Enter to continue...");
        return ScreenType::MAIN_MENU;
    }

    if (subScreen_ == PlaylistSubScreen::DEFAULT) {
        // تغییر مهم: دریافت رشته (String) به جای کاراکتر (Char) تا بتوان اعداد دو رقمی مثل 12 را هم وارد کرد
        std::string inputStr = input_->getStringInput(""); 
        
        if (inputStr.empty()) return ScreenType::PLAYLIST_VIEW;
        
        // چک کردن دستورات (تبدیل به حروف کوچک برای راحتی کاربر)
        char cmd = std::tolower(inputStr[0]);
        if (inputStr == "0") {
            return ScreenType::MAIN_MENU;
        } else if (inputStr == "s" || cmd == 's') {
            subScreen_ = PlaylistSubScreen::SORT_MENU; 
            handleSortMenu(); 
        } else if (inputStr == "f" || cmd == 'f') {
            subScreen_ = PlaylistSubScreen::FILTER_MENU; 
            handleFilterMenu(playlist); 
        } else if (inputStr == "/" || cmd == '/') {
            std::string query = input_->getStringInput("  \033[97mSearch query: \033[0m");
            displayedSongs_ = playlist->search(query);
        } else if (inputStr == "c" || cmd == 'c') {
            initializeSongs(playlist); 
        } else {
            // منطق پخش آهنگ (پشتیبانی از اعداد چند رقمی)
            try {
                int trackNumber = std::stoi(inputStr);
                int index = trackNumber - 1;
                
                if (index >= 0 && index < static_cast<int>(displayedSongs_.size()) && player_) {
                    int origIndex = playlist->indexOf(displayedSongs_[index]);
                    if (origIndex != -1) {
                        player_->stop();
                        player_->setCurrentIndex(origIndex);
                        player_->play(); // شلیک دستور پخش!
                    }
                }
            } catch (...) {
                // اگر کاربر متن نامربوطی وارد کرد اتفاقی نمی‌افتد
            }
        }
    }
    return ScreenType::PLAYLIST_VIEW;
}

void PlaylistViewScreen::handleSortMenu() {
    // چاپ منوی راهنمای سورت در زیر جدول اصلی
    std::cout << "\n  \033[38;5;220mSort by:\033[0m 1.Title  2.Artist  3.Album  4.Year  5.Duration\n";
    std::cout << "  \033[38;5;244m(Add '-' for descending, e.g., '4-'. 0 to Cancel)\033[0m\n";
    
    std::string choiceStr = input_->getStringInput("\n  Sort choice: ");

    if (choiceStr == "0" || choiceStr.empty()) {
        subScreen_ = PlaylistSubScreen::DEFAULT;
        return;
    }

    bool descending = false;
    if (choiceStr.back() == '-') {
        descending = true;
        choiceStr.pop_back();
    }

    int choice = 0;
    try { choice = std::stoi(choiceStr); } catch (...) { choice = 0; }

    if (choice >= 1 && choice <= 5) {
        std::sort(displayedSongs_.begin(), displayedSongs_.end(), [choice, descending](Song* a, Song* b) {
            bool result = false;
            switch (choice) {
                case 1: result = a->getTitle() < b->getTitle(); break;
                case 2: result = a->getArtist() < b->getArtist(); break;
                case 3: result = a->getAlbum() < b->getAlbum(); break;
                case 4: result = a->getYear() < b->getYear(); break;
                case 5: result = a->getDurationSec() < b->getDurationSec(); break;
            }
            return descending ? !result : result;
        });
    }
    subScreen_ = PlaylistSubScreen::DEFAULT;
}

void PlaylistViewScreen::handleFilterMenu(Playlist* playlist) {
    std::cout << "\n  \033[38;5;220mFilter by:\033[0m 1. Artist   2. Album   0. Cancel\n";
    int filterType = input_->getIntChoice("\n  Choice: ", 0, 2);
    
    if (filterType == 0) {
        subScreen_ = PlaylistSubScreen::DEFAULT;
        return;
    }

    std::set<std::string> uniqueItems;
    for (Song* song : playlist->getSongs()) {
        if (!song) continue;
        uniqueItems.insert(filterType == 1 ? song->getArtist() : song->getAlbum());
    }

    std::vector<std::string> itemsList(uniqueItems.begin(), uniqueItems.end());
    std::cout << "\n  \033[38;5;114mAvailable Options:\033[0m\n";
    for (size_t i = 0; i < itemsList.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << itemsList[i] << "\n";
    }

    int itemChoice = input_->getIntChoice("\n  Select option (0 to cancel): ", 0, itemsList.size());
    if (itemChoice > 0) {
        std::string selected = itemsList[itemChoice - 1];
        displayedSongs_ = (filterType == 1) ? playlist->filterByArtist(selected) : playlist->filterByAlbum(selected);
    }
    subScreen_ = PlaylistSubScreen::DEFAULT;
}