#pragma once

#include "Screen.h"

class MainMenuScreen : public Screen {
public:
    void render() override;
    ScreenType handleInput() override;
    ScreenType getType() const override { return ScreenType::MAIN_MENU; }
    
private:
    void displayLastPlayed() const;
};