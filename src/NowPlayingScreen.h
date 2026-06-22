#pragma once
#include "Screen.h"
#include "UIRenderer.h"

class ScreenManager;

class NowPlayingScreen : public Screen {
private:
    ScreenManager* screenManager;
    UIRenderer* uiRenderer;

public:
    NowPlayingScreen(ScreenManager* sm, UIRenderer* ui);
    
    void render() override;
    void handleInput() override;
};