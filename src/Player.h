#pragma once

#include "Playlist.h"

enum class PlayerState
{
    Stopped,
    Playing,
    Paused
};

class Player
{
private:
    Playlist* currentPlaylist;
    int currentIndex;

    PlayerState state;

    int currentPosition;   

public:
    Player();

    bool loadPlaylist(Playlist* playlist);

    void play();
    void pause();
    void resume();
    void stop();

    void next();
    void previous();

    void seekForward(int seconds = 10);
    void seekBackward(int seconds = 10);

    void tick();

    Song* getCurrentSong() const;

    PlayerState getState() const;

    int getCurrentPosition() const;
    int getDuration() const;
};