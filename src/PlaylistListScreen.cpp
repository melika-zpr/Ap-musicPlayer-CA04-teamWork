#include "PlaylistListScreen.h"
#include "ScreenManager.h"
#include "MainMenuScreen.h"
#include <iostream>
#include <memory>

PlaylistListScreen::PlaylistListScreen(ScreenManager* sm, UIRenderer* ui)
    : screenManager(sm), uiRenderer(ui) 
{
}

void PlaylistListScreen::render() {
    uiRenderer->playlistsHeader();
    
    // یک متن موقت تا زمانی که فایل‌های m3u رو لود کنیم
    uiRenderer->textLine(" (Playlists will be loaded here from Data/Playlists) ");
    
    uiRenderer->showPlaylistMenu();
}

void PlaylistListScreen::handleInput() {
    std::string choice;
    std::cin >> choice;

    if (choice == "0") {
        // بازگشت به منوی اصلی
        screenManager->setScreen(std::make_unique<MainMenuScreen>(screenManager, uiRenderer));
    } 
    else {
        uiRenderer->error("Playlist selection logic coming soon! Press 0 to go back.");
        uiRenderer->waitForEnter();
    }
}