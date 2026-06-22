#include "NowPlayingScreen.h"
#include "ScreenManager.h"
#include "MainMenuScreen.h"
#include <iostream>
#include <memory>

NowPlayingScreen::NowPlayingScreen(ScreenManager* sm, UIRenderer* ui)
    : screenManager(sm), uiRenderer(ui) {}

void NowPlayingScreen::render() {
    uiRenderer->clear();
    uiRenderer->nowPlayingHeader();
    uiRenderer->printCenteredMessage("(Music playback info will appear here)");
    uiRenderer->showNowPlayingMenu();
}

void NowPlayingScreen::handleInput() {
    std::string choice;
    std::cin >> choice;

    // طبق خواسته تمرین، خروج از این صفحه با حرف q است
    if (choice == "q" || choice == "0") { 
        screenManager->setScreen(std::make_unique<MainMenuScreen>(screenManager, uiRenderer));
    } 
    else {
        uiRenderer->error("Playback controls coming soon! Press 'q' to go back.");
        uiRenderer->waitForEnter();
    }
}