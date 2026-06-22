#include "SettingScreen.h"
#include "ScreenManager.h"
#include "MainMenuScreen.h"
#include <iostream>
#include <memory>

SettingScreen::SettingScreen(ScreenManager* sm, UIRenderer* ui)
    : screenManager(sm), uiRenderer(ui), currentMode(PlaybackMode::SHUFFLE) 
{
}

void SettingScreen::render() {
    uiRenderer->showSettingsMenu(playbackModeToString(currentMode));
}

void SettingScreen::handleInput() {
    std::string choice;
    std::cin >> choice;

    if (choice == "1") {
        currentMode = PlaybackMode::NO_REPEAT;
    } 
    else if (choice == "2") {
        currentMode = PlaybackMode::REPEAT_ONE;
    } 
    else if (choice == "3") {
        currentMode = PlaybackMode::REPEAT_ALL;
    } 
    else if (choice == "4") {
        currentMode = PlaybackMode::SHUFFLE;
    } 
    else if (choice == "0") {
        // بازگشت به منوی اصلی با کلید 0
        screenManager->setScreen(std::make_unique<MainMenuScreen>(screenManager, uiRenderer));
    } 
    else {
        uiRenderer->error("Invalid choice. Please try again.");
        uiRenderer->waitForEnter();
    }
}