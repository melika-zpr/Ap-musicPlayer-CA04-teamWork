#include "UIRenderer.h"
#include "Song.h"
#include "Playlist.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

#ifdef _WIN32
    #define CLEAR_CMD "cls"
#else
    #define CLEAR_CMD "clear"
#endif

void UIRenderer::clearScreen() const {
    std::system(CLEAR_CMD);
}

void UIRenderer::drawHorizontalLine(char ch, int width) const {
    for (int i = 0; i < width; i++) {
        std::cout << ch;
    }
    std::cout << std::endl;
}

void UIRenderer::drawBorder(const std::string& title, int width) const {
    std::cout << "╔";
    for (int i = 0; i < width - 2; i++) std::cout << "═";
    std::cout << "╗" << std::endl;
    
    if (!title.empty()) {
        int padding = (width - 2 - title.length()) / 2;
        std::cout << "║";
        for (int i = 0; i < padding; i++) std::cout << " ";
        std::cout << title;
        for (int i = 0; i < width - 2 - padding - title.length(); i++) std::cout << " ";
        std::cout << "║" << std::endl;
        
        std::cout << "╠";
        for (int i = 0; i < width - 2; i++) std::cout << "═";
        std::cout << "╣" << std::endl;
    }
}

void UIRenderer::printHeader(const std::string& title) const {
    clearScreen();
    std::cout << std::endl;
    drawBorder(title, 50);
    std::cout << std::endl;
}

void UIRenderer::printFooter(const std::string& options) const {
    std::cout << std::endl;
    drawHorizontalLine('-', 50);
    std::cout << options << std::endl;
    std::cout << std::endl;
}

void UIRenderer::printMessage(const std::string& message, bool newLine) const {
    if (newLine) {
        std::cout << message << std::endl;
    } else {
        std::cout << message;
    }
}

void UIRenderer::printError(const std::string& error) const {
    std::cout << "❌ " << error << std::endl;
}

void UIRenderer::printMenu(const std::vector<std::string>& items, 
                           const std::string& prompt) const {
    for (size_t i = 0; i < items.size(); i++) {
        std::cout << "  " << (i + 1) << ". " << items[i] << std::endl;
    }
    std::cout << std::endl;
    std::cout << "  0. Back" << std::endl;
    std::cout << std::endl;
    std::cout << prompt;
}

void UIRenderer::printSongList(const std::vector<Song*>& songs, int maxDisplay) const {
    if (songs.empty()) {
        printMessage("  (empty)");
        return;
    }
    
    int count = 0;
    for (size_t i = 0; i < songs.size() && i < static_cast<size_t>(maxDisplay); i++) {
        if (songs[i]) {
            std::cout << "  " << std::setw(3) << std::right << (i + 1) << ". "
                      << std::setw(30) << std::left << truncate(songs[i]->getTitle(), 28)
                      << " - " << std::setw(20) << std::left << truncate(songs[i]->getArtist(), 18)
                      << " (" << formatDuration(songs[i]->getDurationSec()) << ")" << std::endl;
            count++;
        }
    }
    
    if (static_cast<int>(songs.size()) > maxDisplay) {
        std::cout << "  ... and " << (songs.size() - maxDisplay) << " more" << std::endl;
    }
}

void UIRenderer::printPlaylistList(const std::vector<Playlist>& playlists) const {
    if (playlists.empty()) {
        printMessage("  No playlists available.");
        return;
    }
    
    for (size_t i = 0; i < playlists.size(); i++) {
        std::cout << "  " << (i + 1) << ". " 
                  << playlists[i].getName() 
                  << " (" << playlists[i].size() << " songs)" << std::endl;
    }
}

void UIRenderer::printNowPlaying(const Song* song, float currentTime, float totalTime) const {
    if (song == nullptr) {
        printMessage("  No song is currently playing.");
        return;
    }
    
    std::cout << std::endl;
    std::cout << "  🎵 " << song->getTitle() << std::endl;
    std::cout << "  Artist: " << song->getArtist() << std::endl;
    std::cout << "  Album: " << song->getAlbum() << std::endl;
    std::cout << "  Duration: " << formatDuration(song->getDurationSec()) << std::endl;
    std::cout << std::endl;
    
    int currentMin = static_cast<int>(currentTime) / 60;
    int currentSec = static_cast<int>(currentTime) % 60;
    int totalMin = static_cast<int>(totalTime) / 60;
    int totalSec = static_cast<int>(totalTime) % 60;
    
    std::cout << "  Time: " << std::setw(2) << std::setfill('0') << currentMin << ":"
              << std::setw(2) << std::setfill('0') << currentSec << " / "
              << std::setw(2) << std::setfill('0') << totalMin << ":"
              << std::setw(2) << std::setfill('0') << totalSec << std::endl;
}

void UIRenderer::printSettings(const std::string& currentMode) const {
    std::cout << "  Playback Mode (current: " << currentMode << ")" << std::endl;
    drawHorizontalLine('-', 45);
    std::cout << std::endl;
    std::cout << "  1. NO_REPEAT  - play in order, stop at end" << std::endl;
    std::cout << "  2. REPEAT_ONE - repeat current song forever" << std::endl;
    std::cout << "  3. REPEAT_ALL - loop whole playlist" << std::endl;
    std::cout << "  4. SHUFFLE    - random order";
    if (currentMode == "SHUFFLE") {
        std::cout << " ◀ (active)";
    }
    std::cout << std::endl;
}

std::string UIRenderer::formatDuration(int seconds) const {
    int min = seconds / 60;
    int sec = seconds % 60;
    
    std::string result;
    result += (min < 10 ? "0" : "") + std::to_string(min);
    result += ":";
    result += (sec < 10 ? "0" : "") + std::to_string(sec);
    return result;
}

std::string UIRenderer::truncate(const std::string& str, size_t maxLen) const {
    if (str.length() <= maxLen) {
        return str;
    }
    return str.substr(0, maxLen - 3) + "...";
}