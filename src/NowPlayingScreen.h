#pragma once

#include "Screen.h"

class NowPlayingScreen : public Screen {
public:
    void render() override;
    ScreenType handleInput() override;
    ScreenType getType() const override { return ScreenType::NOW_PLAYING; }
};