#pragma once
#include "Screen.h"
#include "UIRenderer.h"
#include "PlaybackMode.h"

class ScreenManager;

class SettingScreen : public Screen {
private:
    ScreenManager* screenManager;
    UIRenderer* uiRenderer;
    
    // فعلاً این متغیر رو اینجا نگه می‌داریم تا وقتی ConfigManager کامل بشه
    PlaybackMode currentMode; 

public:
    SettingScreen(ScreenManager* sm, UIRenderer* ui);
    
    void render() override;
    void handleInput() override;
};