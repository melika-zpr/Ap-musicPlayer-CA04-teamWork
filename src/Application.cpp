#include "Application.h"

#include "CsvLoader.h"
#include "M3uLoader.h"
#include "ConfigManager.h"
#include "Player.h"
#include "MusicLibrary.h"
#include "Playlist.h"
#include "Song.h"
#include "UIRenderer.h"
#include "InputHandler.h"
#include "MainMenuScreen.h"
#include "NowPlayingScreen.h"
#include "PlaylistListScreen.h"
#include "PlaylistViewScreen.h"
#include "SettingsScreen.h"

#include <iostream>

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_MS(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP_MS(ms) usleep((ms) * 1000)
#endif


Application::Application() {
    // مخفی کردن کرسر در همان ابتدای اجرای برنامه
    ui_.hideCursor(); 
    // پاکسازی واقعی صفحه فقط برای بار اول
    std::system("cls");
    
    config_.load();
    loadData();
    setupScreens();

    player_.setPlaybackMode(config_.getPlaybackMode());
    
    changeScreen(ScreenType::MAIN_MENU);
}

Application::~Application() {
    if (player_.getCurrentSong() != nullptr) {
        config_.setLastSong(player_.getCurrentSong()->getTitle());
    }
    config_.setPlaybackMode(player_.getPlaybackMode());
    if (player_.getCurrentPlaylist() != nullptr) {
        config_.setActivePlaylist(player_.getCurrentPlaylist()->getName());
    }
    config_.save();
}

void Application::loadData() {
    CsvLoader csvLoader;
    std::vector<std::string> errors;
    
    if (csvLoader.load("Data/library.csv", library_, errors)) {
        std::cout << "[App] Loaded " << library_.size() << " songs from CSV." << std::endl;
    } else {
        std::cerr << "[App] Failed to load CSV." << std::endl;
    }
    
    M3uLoader::loadPlaylists("Data/Playlists", library_, playlists_, errors);
    
    std::string activeName = config_.getActivePlaylist();
    Playlist* targetPlaylist = nullptr;

    for (auto& playlist : playlists_) {
        if (playlist.getName() == activeName) {
            targetPlaylist = &playlist;
            break;
        }
    }
    // اگر پلی‌لیست ذخیره‌شده معتبر نبود یا پیدا نشد، به عنوان بک‌آپ اولین پلی‌لیست را لود کن
    if (targetPlaylist == nullptr && !playlists_.empty()) {
        targetPlaylist = &playlists_[0];
    }
    
    // بارگذاری نهایی پلی‌لیست در پلیر و هماهنگ‌سازی آهنگ ذخیره شده
    if (targetPlaylist != nullptr) {
        player_.loadPlaylist(targetPlaylist);
        
        // اصلاح بزرگ دوم: پیدا کردن دقیق آخرین آهنگ پخش شده در این پلی‌لیست
        std::string lastSongTitle = config_.getLastSong();
        if (!lastSongTitle.empty()) {
            const auto& songs = targetPlaylist->getSongs();
            for (size_t i = 0; i < songs.size(); ++i) {
                if (songs[i] && songs[i]->getTitle() == lastSongTitle) {
                    player_.setCurrentIndex(static_cast<int>(i));
                    player_.stop(); // آهنگ روی پلیر آماده قرار می‌گیرد اما خودکار پخش نمی‌شود تا کاربر دکمه بزند
                    break;
                }
            }
        }
    }
}

void Application::setupScreens() {
    mainMenuScreen_.setPlayer(&player_);
    mainMenuScreen_.setConfigManager(&config_);
    mainMenuScreen_.setPlaylists(&playlists_);
    mainMenuScreen_.setUIRenderer(&ui_);
    mainMenuScreen_.setInputHandler(&input_);
    
    nowPlayingScreen_.setPlayer(&player_);
    nowPlayingScreen_.setConfigManager(&config_);
    nowPlayingScreen_.setPlaylists(&playlists_);
    nowPlayingScreen_.setUIRenderer(&ui_);
    nowPlayingScreen_.setInputHandler(&input_);
    
    playlistListScreen_.setPlayer(&player_);
    playlistListScreen_.setConfigManager(&config_);
    playlistListScreen_.setPlaylists(&playlists_);
    playlistListScreen_.setUIRenderer(&ui_);
    playlistListScreen_.setInputHandler(&input_);
    
    playlistViewScreen_.setPlayer(&player_);
    playlistViewScreen_.setConfigManager(&config_);
    playlistViewScreen_.setPlaylists(&playlists_);
    playlistViewScreen_.setUIRenderer(&ui_);
    playlistViewScreen_.setInputHandler(&input_);
    
    settingsScreen_.setPlayer(&player_);
    settingsScreen_.setConfigManager(&config_);
    settingsScreen_.setPlaylists(&playlists_);
    settingsScreen_.setUIRenderer(&ui_);
    settingsScreen_.setInputHandler(&input_);
}

void Application::changeScreen(ScreenType type) {
    switch (type) {
        case ScreenType::MAIN_MENU:
            currentScreen_ = &mainMenuScreen_;
            break;
        case ScreenType::NOW_PLAYING:
            currentScreen_ = &nowPlayingScreen_;
            break;
        case ScreenType::PLAYLIST_LIST:
            currentScreen_ = &playlistListScreen_;
            break;
        case ScreenType::PLAYLIST_VIEW:
            currentScreen_ = &playlistViewScreen_;
            break;
        case ScreenType::SETTINGS:
            currentScreen_ = &settingsScreen_;
            break;
        case ScreenType::EXIT:
            currentScreen_ = nullptr;
            isRunning_ = false;
            break;
        default:
            currentScreen_ = nullptr;
            break;
    }
}

void Application::run() {
    ScreenType lastScreen = ScreenType::EXIT;
    int lastPosition = -1;
    PlayerState lastState = PlayerState::Stopped;

    ui_.hideCursor();

    while (isRunning_ && currentScreen_ != nullptr) {
        // ۱. همیشه موزیک پلیر را آپدیت کن تا آهنگ بعدی خودکار پخش شود
        player_.tick();

        // ۲. بررسی تغییرات برای جلوگیری از رندر بی‌جهت
        bool screenChanged = (currentScreen_->getType() != lastScreen);
        int currentPosition = player_.getCurrentPosition();
        PlayerState currentState = player_.getState();
        bool playerChanged = (currentPosition != lastPosition || currentState != lastState);

        // ۱. حل مشکل روی هم افتادن: اگر صفحه عوض شد، کل بافر ترمینال را پاک کن
        if (screenChanged) {
            #ifdef _WIN32
            std::system("cls");
            #else
            std::system("clear");
            #endif
        }

        // ۳. رندر هوشمند: فقط وقتی صفحه عوض شده یا (در صفحه پخش) ثانیه/وضعیت تغییر کرده باشد
        if (screenChanged || (currentScreen_->getType() == ScreenType::NOW_PLAYING && playerChanged)) {
            currentScreen_->render();
            
            // ذخیره وضعیت فعلی برای مقایسه در دور بعدی
            lastScreen = currentScreen_->getType();
            lastPosition = currentPosition;
            lastState = currentState;
        }

        // ۴. دریافت ورودی 
        ScreenType next = currentScreen_->handleInput();
        if (next != currentScreen_->getType()) {
            changeScreen(next);
        }

        // ۵. استراحت حلقه
        SLEEP_MS(100);
    }
    config_.save();
}