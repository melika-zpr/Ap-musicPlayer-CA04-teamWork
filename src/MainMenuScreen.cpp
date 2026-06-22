#include "MainMenuScreen.h"
#include "ScreenManager.h"
#include "SettingScreen.h"
#include "PlaylistListScreen.h"
#include "NowPlayingScreen.h"
#include "BrowsePlaylistScreen.h"
#include <iostream>
#include <string>
#include <memory>

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
        screenManager->setScreen(std::make_unique<NowPlayingScreen>(screenManager, uiRenderer));
    } 
    else if (choice == "2") {
        screenManager->setScreen(std::make_unique<PlaylistListScreen>(screenManager, uiRenderer));
    } 
    else if (choice == "3") {
        screenManager->setScreen(std::make_unique<BrowsePlaylistScreen>(screenManager, uiRenderer));
    } 
    else if (choice == "4") {
        screenManager->setScreen(std::make_unique<SettingScreen>(screenManager, uiRenderer));
    } 
    else if (choice == "0") {
        // ارسال nullptr باعث خروج از حلقه run و بستن برنامه می‌شود
        screenManager->setScreen(nullptr); 
    } 
    else {
        uiRenderer->error("Invalid choice. Please try again.");
        uiRenderer->waitForEnter();
    }
}