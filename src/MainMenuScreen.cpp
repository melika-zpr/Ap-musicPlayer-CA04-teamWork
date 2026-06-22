#include "MainMenuScreen.h"
#include "ScreenManager.h"
#include "SettingScreen.h"
#include "PlaylistListScreen.h"

#include <memory>
#include <iostream>
#include <string>

MainMenuScreen::MainMenuScreen(ScreenManager* sm, UIRenderer* ui)
    : screenManager(sm), uiRenderer(ui)
{
}

void MainMenuScreen::render()
{
    // فعلا یک رشته ثابت می‌فرستیم. بعداً این رو از ConfigManager می‌خونیم
    uiRenderer->showMainMenu("Queen - Bohemian Rhapsody"); 
}

void MainMenuScreen::handleInput()
{
    std::string choice;
    std::cin >> choice;

    if (choice == "1") {
        // TODO: رفتن به NowPlayingScreen
    } 
    else if (choice == "2") {
        screenManager->setScreen(std::make_unique<PlaylistListScreen>(screenManager, uiRenderer));
    } 
    else if (choice == "3") {
        // TODO: رفتن به BrowsePlaylistScreen
    } 
    else if (choice == "4") {
        screenManager->setScreen(std::make_unique<SettingScreen>(screenManager, uiRenderer));
    } 
    else if (choice == "0") {
        // ارسال nullptr باعث خروج از حلقه run و بستن برنامه می‌شود
        screenManager->setScreen(nullptr); 
    } 
    else {
        // استفاده از توابع مدیریت خطای خودت
        uiRenderer->error("Invalid choice. Please try again.");
        uiRenderer->waitForEnter();
    }
}