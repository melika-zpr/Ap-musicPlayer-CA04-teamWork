#include "ScreenManager.h"

void ScreenManager::setScreen(std::unique_ptr<Screen> screen)
{
    // حافظه صفحه قبلی خودکار آزاد شده و صفحه جدید جایگزین می‌شود
    currentScreen = std::move(screen);
}

void ScreenManager::run()
{
    // تا زمانی که صفحه‌ای وجود دارد، حلقه ادامه پیدا می‌کند
    while (currentScreen)
    {
        currentScreen->render();
        currentScreen->handleInput();
    }
}