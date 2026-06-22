#pragma once

#include "Screen.h"
#include "UIRenderer.h"
#include "InputHandler.h"
#include "Player.h"

class NowPlayingScreen : public Screen
{
private:
    UIRenderer& renderer;
    InputHandler& input;
    Player& player;

public:
    NowPlayingScreen(
        UIRenderer& renderer,
        InputHandler& input,
        Player& player
    );

    void render() override;

    void handleInput() override;
};