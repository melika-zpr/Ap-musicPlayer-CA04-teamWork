#pragma once
#include "ScreenManager.h"
#include "UIRenderer.h"

class Application {
private:
    ScreenManager screenManager;
    UIRenderer uiRenderer;

public:
    Application() = default;
    
    void init();
    void run();
    void shutdown();
};