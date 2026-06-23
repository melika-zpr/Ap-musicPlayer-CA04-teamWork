#pragma once

#include "Screen.h"

class PlaylistListScreen : public Screen {
public:
    void render() override;
    ScreenType handleInput() override;
    ScreenType getType() const override { return ScreenType::PLAYLIST_LIST; }
};