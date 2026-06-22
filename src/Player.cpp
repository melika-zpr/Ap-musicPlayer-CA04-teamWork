#define MINIAUDIO_IMPLEMENTATION

#include "Player.h"
#include <iostream>
#include "miniaudio.h"

Player::Player()
{
    currentPlaylist = nullptr;
    currentIndex = 0;

    state = PlayerState::Stopped;

    currentPosition = 0;
}

bool Player::loadPlaylist(Playlist* playlist)
{
    if (playlist == nullptr || playlist->size() == 0)
        return false;

    currentPlaylist = playlist;
    currentIndex = 0;

    currentPosition = 0;

    state = PlayerState::Stopped;

    return true;
}

Song* Player::getCurrentSong() const
{
    if (currentPlaylist == nullptr)
        return nullptr;

    return currentPlaylist->getSong(currentIndex);
}

void Player::play()
{
    Song* song = getCurrentSong();

    if (song == nullptr)
        return;

    currentPosition = 0;

    state = PlayerState::Playing;

    std::cout << "Playing: "
              << song->getTitle()
              << std::endl;
}

void Player::pause()
{
    if (state == PlayerState::Playing)
        state = PlayerState::Paused;
}

void Player::resume()
{
    if (state == PlayerState::Paused)
        state = PlayerState::Playing;
}

void Player::stop()
{
    state = PlayerState::Stopped;
    currentPosition = 0;
}


void Player::next()
{
    if (currentPlaylist == nullptr)
        return;

    if (currentIndex + 1 >= currentPlaylist->size())
        return;

    currentIndex++;

    play();
}

void Player::previous()
{
    if (currentPlaylist == nullptr)
        return;

    if (currentIndex == 0)
        return;

    currentIndex--;

    play();
}

void Player::tick()
{
    if (state != PlayerState::Playing)
        return;

    currentPosition++;

    if (currentPosition >= getCurrentSong()->getDurationSec())
    {
        next();
    }
}

void Player::seekForward(int seconds)
{
    Song* song = getCurrentSong();

    if (song == nullptr)
        return;

    currentPosition += seconds;

    if (currentPosition > song->getDurationSec())
        currentPosition = song->getDurationSec();
}

void Player::seekBackward(int seconds)
{
    currentPosition -= seconds;

    if (currentPosition < 0)
        currentPosition = 0;
}