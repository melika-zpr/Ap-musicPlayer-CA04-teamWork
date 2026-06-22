#pragma once
#include "Screen.h"
#include <memory>

class ScreenManager
{
private:
    std::unique_ptr<Screen> currentScreen;

public:
    ScreenManager() = default;

    // دریافت مالکیت صفحه جدید
    void setScreen(std::unique_ptr<Screen> screen);

    void run();
};