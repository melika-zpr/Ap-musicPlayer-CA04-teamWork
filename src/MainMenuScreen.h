#pragma once
#include "Screen.h"
#include "UIRenderer.h"

// Forward declaration برای جلوگیری از تداخل
class ScreenManager; 

class MainMenuScreen : public Screen
{
private:
    ScreenManager* screenManager;
    UIRenderer* uiRenderer;

public:
    MainMenuScreen(ScreenManager* sm, UIRenderer* ui);
    
    void render() override;
    void handleInput() override;
};