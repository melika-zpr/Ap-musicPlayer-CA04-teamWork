#pragma once

#include "Screen.h"
#include "ConfigManager.h"

class SettingsScreen : public Screen {
public:
    void render() override;
    ScreenType handleInput() override;
    ScreenType getType() const override { return ScreenType::SETTINGS; }
};