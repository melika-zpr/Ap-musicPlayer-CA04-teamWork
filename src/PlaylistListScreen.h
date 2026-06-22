#pragma once
#include "Screen.h"
#include "UIRenderer.h"

class ScreenManager;

class PlaylistListScreen : public Screen {
private:
    ScreenManager* screenManager;
    UIRenderer* uiRenderer;

public:
    PlaylistListScreen(ScreenManager* sm, UIRenderer* ui);
    
    void render() override;
    void handleInput() override;
};