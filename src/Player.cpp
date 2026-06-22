#define MINIAUDIO_IMPLEMENTATION

#include "Player.h"
#include <iostream>
#include <random>
#include "miniaudio.h"

Player::Player()
    : currentPlaylist(nullptr),
      currentIndex(0),
      state(PlayerState::Stopped),
      playbackMode(PlaybackMode::NO_REPEAT),
      engineInitialized(false),
      soundLoaded(false)
{
    ma_result result = ma_engine_init(nullptr, &engine);
    if (result != MA_SUCCESS)
    {
        std::cerr << "Failed to initialize audio engine.\n";
        return;
    }
    engineInitialized = true;
}

Player::~Player()
{
    if (soundLoaded)
    {
        ma_sound_uninit(&sound);
        soundLoaded = false;
    }
    if (engineInitialized)
    {
        ma_engine_uninit(&engine);
        engineInitialized = false;
    }
}

static bool loadSound(ma_engine* engine,
                      ma_sound* sound,
                      const std::string& path)

{

    return ma_sound_init_from_file(
               engine,
               path.c_str(),
               0,
               nullptr,
               nullptr,
               sound) == MA_SUCCESS;

}

bool Player::loadPlaylist(Playlist* playlist)
{
    if (playlist == nullptr || playlist->size() == 0)
        return false;

    if (soundLoaded)
    {
        stop();
        ma_sound_uninit(&sound);
        soundLoaded = false;
    }

    currentPlaylist = playlist;
    currentIndex = 0;

    state = PlayerState::Stopped;

    return true;
}

Song* Player::getCurrentSong() const
{
    if (currentPlaylist == nullptr)
        return nullptr;

    return currentPlaylist->getSong(currentIndex);
}

void Player::setPlaybackMode(PlaybackMode mode)
{
    playbackMode = mode;
}

PlaybackMode Player::getPlaybackMode() const
{
    return playbackMode;
}

void Player::play()
{
    if (!currentPlaylist)
        return;

    if (!engineInitialized)
        return;

    Song* song = getCurrentSong();

    if (!song)
        return;

    if (soundLoaded)
    {
        ma_sound_uninit(&sound);
        soundLoaded = false;
    }

    if (!loadSound(&engine, &sound, song->getFilePath()))
    {
        std::cerr << "Cannot load audio file.\n";
        if (currentPlaylist && currentIndex + 1 < currentPlaylist->size())
        {
            ++currentIndex;
            play();
        }
        return;
    }

    soundLoaded = true;

    if (ma_sound_start(&sound) != MA_SUCCESS)
    {
        std::cerr << "Failed to start playback.\n";
        ma_sound_uninit(&sound);
        soundLoaded = false;
        return;
    }

    state = PlayerState::Playing;
}

void Player::pause()
{
    if (!soundLoaded)
        return;

    ma_sound_stop(&sound);

    state = PlayerState::Paused;
}

void Player::resume()
{
    if (!soundLoaded)
        return;

    ma_sound_start(&sound);

    state = PlayerState::Playing;
}

void Player::stop()
{
    if (!soundLoaded)
        return;

    ma_sound_stop(&sound);

    ma_sound_seek_to_pcm_frame(&sound, 0);

    state = PlayerState::Stopped;
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
    if (!soundLoaded)
        return;

    if (state != PlayerState::Playing)
        return;

    if (!ma_sound_at_end(&sound))
        return;

    switch (playbackMode)
    {
    case PlaybackMode::NO_REPEAT:
        if (currentIndex + 1 < currentPlaylist->size())
        {
            next();
        }
        else
        {
            stop();
        }
        break;

    case PlaybackMode::REPEAT_ONE:
        play();
        break;

    case PlaybackMode::REPEAT_ALL:
        if (currentIndex + 1 < currentPlaylist->size())
        {
            next();
        }
        else
        {
            currentIndex = 0;
            play();
        }
        break;

    case PlaybackMode::SHUFFLE:
    {
        if (currentPlaylist->size() == 0)
            return;

        static std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(0, currentPlaylist->size() - 1);
        currentIndex = dist(rng);
        play();
        break;
    }
    }
}

void Player::seekForward(int seconds)
{
    if (!soundLoaded)
        return;

    ma_uint64 cursor;
    ma_uint64 length;

    ma_sound_get_cursor_in_pcm_frames(&sound, &cursor);
    ma_sound_get_length_in_pcm_frames(&sound, &length);

    ma_uint32 sampleRate = ma_engine_get_sample_rate(&engine);

    ma_uint64 newFrame = cursor + static_cast<ma_uint64>(seconds) * sampleRate;

    if (newFrame > length)
        newFrame = length;

    ma_sound_seek_to_pcm_frame(&sound, newFrame);
}

void Player::seekBackward(int seconds)
{
    if (!soundLoaded)
        return;

    ma_uint64 cursor;

    ma_sound_get_cursor_in_pcm_frames(&sound, &cursor);

    ma_uint32 sampleRate = ma_engine_get_sample_rate(&engine);

    ma_int64 newFrame =
        static_cast<ma_int64>(cursor) -
        static_cast<ma_int64>(seconds) * sampleRate;

    if (newFrame < 0)
        newFrame = 0;

    ma_sound_seek_to_pcm_frame(&sound, static_cast<ma_uint64>(newFrame));
}

int Player::getCurrentPosition() const
{
    if (!soundLoaded)
        return 0;

    ma_uint64 frames = 0;
    ma_sound_get_cursor_in_pcm_frames(const_cast<ma_sound*>(&sound), &frames);

    return static_cast<int>(frames / ma_engine_get_sample_rate(const_cast<ma_engine*>(&engine)));
}