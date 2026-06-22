#pragma once
#include "Screen.h"
#include "UIRenderer.h"

class ScreenManager;

class BrowsePlaylistScreen : public Screen {
private:
    ScreenManager* screenManager;
    UIRenderer* uiRenderer;

public:
    BrowsePlaylistScreen(ScreenManager* sm, UIRenderer* ui);
    
    void render() override;
    void handleInput() override;
};