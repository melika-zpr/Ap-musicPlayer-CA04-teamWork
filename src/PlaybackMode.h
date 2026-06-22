#pragma once
#include <string>

enum class PlaybackMode {
    NO_REPEAT,
    REPEAT_ONE,
    REPEAT_ALL,
    SHUFFLE
};

// یک تابع کمکی برای تبدیل وضعیت به استرینگ (برای نمایش در UI)
inline std::string playbackModeToString(PlaybackMode mode) {
    switch(mode) {
        case PlaybackMode::NO_REPEAT: return "NO_REPEAT";
        case PlaybackMode::REPEAT_ONE: return "REPEAT_ONE";
        case PlaybackMode::REPEAT_ALL: return "REPEAT_ALL";
        case PlaybackMode::SHUFFLE: return "SHUFFLE";
        default: return "UNKNOWN";
    }
}