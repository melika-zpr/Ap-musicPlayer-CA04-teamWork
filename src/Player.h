#pragma once

#include "Playlist.h"
#include "miniaudio.h"

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

    // Sound Implementation
    ma_engine engine;
    ma_sound sound;

    bool engineInitialized;
    bool soundLoaded;

public:
    Player();
    ~Player();

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