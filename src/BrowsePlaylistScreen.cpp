#include "BrowsePlaylistScreen.h"
#include "ScreenManager.h"
#include "MainMenuScreen.h"
#include <iostream>
#include <memory>

BrowsePlaylistScreen::BrowsePlaylistScreen(ScreenManager* sm, UIRenderer* ui)
    : screenManager(sm), uiRenderer(ui) {}

void BrowsePlaylistScreen::render() {
    uiRenderer->clear();
    uiRenderer->playlistHeader("All Songs (Temp)", 0); 
    uiRenderer->printCenteredMessage("(List of songs will be displayed here)");
    uiRenderer->showBrowseMenu();
}

void BrowsePlaylistScreen::handleInput() {
    std::string choice;
    std::cin >> choice;

    if (choice == "0") {
        screenManager->setScreen(std::make_unique<MainMenuScreen>(screenManager, uiRenderer));
    } 
    else {
        uiRenderer->error("Selection logic coming soon! Press '0' to go back.");
        uiRenderer->waitForEnter();
    }
}