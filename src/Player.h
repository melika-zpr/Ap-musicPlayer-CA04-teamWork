#pragma once

#include "Playlist.h"
#include "PlaybackMode.h"
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
    PlaybackMode playbackMode;

    // Sound Implementation
    ma_engine engine;
    ma_sound sound;

    bool engineInitialized;
    bool soundLoaded;

public:
    Player();
    ~Player();

    Playlist* getCurrentPlaylist() const { return currentPlaylist; }
    void setCurrentIndex(int index) {
        if (currentPlaylist && index >= 0 && index < currentPlaylist->size()) {
            currentIndex = index;
        }
    }


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
    void setPlaybackMode(PlaybackMode mode);
    PlaybackMode getPlaybackMode() const;

    int getCurrentPosition() const;
    int getDuration() const;
};