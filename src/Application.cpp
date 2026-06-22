#include "Application.h"
#include "MainMenuScreen.h"
#include <memory>

void Application::init() {
    // فعلاً خالیه. بعداً خوندن فایل‌های CSV و M3U رو اینجا میاریم.
}

void Application::run() {
    // صفحه اول برنامه رو روی MainMenu تنظیم می‌کنیم
    screenManager.setScreen(std::make_unique<MainMenuScreen>(&screenManager, &uiRenderer));
    
    // اجرای حلقه اصلی برنامه که تو ScreenManager نوشتی
    screenManager.run();
}

void Application::shutdown() {
    // پیام خروج رو چاپ می‌کنیم
    uiRenderer.showExitMessage();
}