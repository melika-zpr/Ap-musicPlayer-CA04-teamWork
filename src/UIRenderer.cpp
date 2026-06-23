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

void UIRenderer::clearScreen() const
{
    std::system(CLEAR_CMD);
}

void UIRenderer::drawHorizontalLine(const std::string &ch, int width) const
{
    for (int i = 0; i < width; i++)
    {
        std::cout << ch;
    }
    std::cout << std::endl;
}

void UIRenderer::drawBorder(const std::string &title, int width) const
{
    std::cout << "\u2554";
    for (int i = 0; i < width - 2; i++)
        std::cout << "\u2550";
    std::cout << "\u2557" << std::endl;

    if (!title.empty())
    {
        int padding = (width - 2 - title.length()) / 2;
        std::cout << "\u2551";
        for (int i = 0; i < padding; i++)
            std::cout << " ";
        std::cout << title;
        for (int i = 0; i < width - 2 - padding - title.length(); i++)
            std::cout << " ";
        std::cout << "\u2551" << std::endl;

        std::cout << "\u2560";
        for (int i = 0; i < width - 2; i++)
            std::cout << "\u2550";
        std::cout << "\u2563" << std::endl;
    }
}

void UIRenderer::printHeader(const std::string &title) const
{
    clearScreen();
    std::cout << std::endl;
    drawBorder(title, 50);
    std::cout << std::endl;
}

void UIRenderer::printFooter(const std::string &options) const
{
    std::cout << std::endl;
    drawHorizontalLine("\u2500", 50);
    std::cout << options << std::endl;
    std::cout << std::endl;
}

void UIRenderer::printMessage(const std::string &message, bool newLine) const
{
    if (newLine)
    {
        std::cout << message << std::endl;
    }
    else
    {
        std::cout << message;
    }
}

void UIRenderer::printError(const std::string &error) const
{
    std::cout << "\u2716 " << error << std::endl;
}

void UIRenderer::printMenu(const std::vector<std::string> &items,
                           const std::string &prompt) const
{
    for (size_t i = 0; i < items.size(); i++)
    {
        std::cout << "  " << (i + 1) << ". " << items[i] << std::endl;
    }
    std::cout << std::endl;
    std::cout << "  0. Back" << std::endl;
    std::cout << std::endl;
    std::cout << prompt;
}

void UIRenderer::printSongList(const std::vector<Song *> &songs, int maxDisplay) const
{
    if (songs.empty())
    {
        printMessage("  (empty)");
        return;
    }

    const int idWidth = 5;
    const int titleWidth = 22;
    const int artistWidth = 16;
    const int albumWidth = 16;
    const int durationWidth = 10;

    std::cout << "  \u250C";
    for (int i = 0; i < idWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u252C";
    for (int i = 0; i < titleWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u252C";
    for (int i = 0; i < artistWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u252C";
    for (int i = 0; i < albumWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u252C";
    for (int i = 0; i < durationWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u2510" << std::endl;

    std::cout << "  \u2502"
              << std::left << std::setfill(' ') << std::setw(idWidth) << "  #" << "\u2502"
              << std::setw(titleWidth) << " Title" << "\u2502"
              << std::setw(artistWidth) << " Artist" << "\u2502"
              << std::setw(albumWidth) << " Album" << "\u2502"
              << std::setw(durationWidth) << " Duration" << "\u2502" << std::endl;

    std::cout << "  \u251C";
    for (int i = 0; i < idWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u253C";
    for (int i = 0; i < titleWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u253C";
    for (int i = 0; i < artistWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u253C";
    for (int i = 0; i < albumWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u253C";
    for (int i = 0; i < durationWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u2524" << std::endl;

    int count = 0;
    for (size_t i = 0; i < songs.size() && count < maxDisplay; ++i)
    {
        if (songs[i] == nullptr)
            continue;
        count++;

        std::cout << "  \u2502"
                  << std::right << std::setw(idWidth - 2) << count << "  \u2502"
                  << std::left << std::setw(titleWidth) << (" " + truncate(songs[i]->getTitle(), titleWidth - 2)) << "\u2502"
                  << std::setw(artistWidth) << (" " + truncate(songs[i]->getArtist(), artistWidth - 2)) << "\u2502"
                  << std::setw(albumWidth) << (" " + truncate(songs[i]->getAlbum(), albumWidth - 2)) << "\u2502"
                  << std::setw(durationWidth) << ("  " + songs[i]->getFormattedDuration()) << "\u2502" << std::endl;
    }

    std::cout << "  \u2514";
    for (int i = 0; i < idWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u2534";
    for (int i = 0; i < titleWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u2534";
    for (int i = 0; i < artistWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u2534";
    for (int i = 0; i < albumWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u2534";
    for (int i = 0; i < durationWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u2518" << std::endl;
}

void UIRenderer::printPlaylistList(const std::vector<Playlist> &playlists) const
{
    if (playlists.empty())
    {
        printMessage("  No playlists available.");
        return;
    }

    const int idWidth = 5;
    const int nameWidth = 30;
    const int countWidth = 15;

    std::cout << "  \u250C";
    for (int i = 0; i < idWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u252C";
    for (int i = 0; i < nameWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u252C";
    for (int i = 0; i < countWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u2510" << std::endl;

    std::cout << "  \u2502"
              << std::left << std::setfill(' ') << std::setw(idWidth) << "  #" << "\u2502"
              << std::setw(nameWidth) << " Playlist Name" << "\u2502"
              << std::setw(countWidth) << " Total Songs" << "\u2502" << std::endl;

    std::cout << "  \u251C";
    for (int i = 0; i < idWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u253C";
    for (int i = 0; i < nameWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u253C";
    for (int i = 0; i < countWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u2524" << std::endl;

    for (size_t i = 0; i < playlists.size(); ++i)
    {
        std::cout << "  \u2502"
                  << std::right << std::setw(idWidth - 2) << (i + 1) << "  \u2502"
                  << std::left << std::setw(nameWidth) << (" " + truncate(playlists[i].getName(), nameWidth - 2)) << "\u2502"
                  << std::right << std::setw(countWidth - 3) << playlists[i].size() << "   \u2502" << std::endl;
    }

    std::cout << "  \u2514";
    for (int i = 0; i < idWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u2534";
    for (int i = 0; i < nameWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u2534";
    for (int i = 0; i < countWidth; ++i)
        std::cout << "\u2500";
    std::cout << "\u2518" << std::endl;
}

void UIRenderer::printNowPlaying(const Song *song, float currentTime, float totalTime) const
{
    if (song == nullptr)
    {
        printMessage("  No song is currently playing.");
        return;
    }

    std::cout << std::endl;
    std::cout << "  \u266B " << song->getTitle() << std::endl;
    std::cout << "  Artist: " << song->getArtist() << std::endl;
    std::cout << "  Album: " << song->getAlbum() << std::endl;
    std::cout << "  Duration: " << formatDuration(song->getDurationSec()) << std::endl;
    std::cout << std::endl;

    int currentMin = static_cast<int>(currentTime) / 60;
    int currentSec = static_cast<int>(currentTime) % 60;
    int totalMin = static_cast<int>(totalTime) / 60;
    int totalSec = static_cast<int>(totalTime) % 60;

    std::cout << "  Time: "
              << std::right << std::setw(2) << std::setfill('0') << currentMin << ":"
              << std::right << std::setw(2) << std::setfill('0') << currentSec << " / "
              << std::right << std::setw(2) << std::setfill('0') << totalMin << ":"
              << std::right << std::setw(2) << std::setfill('0') << totalSec
              << std::setfill(' ') << std::left << std::endl;
              
}

void UIRenderer::printSettings(const std::string &currentMode) const
{
    std::cout << "  Playback Mode (current: " << currentMode << ")" << std::endl;
    drawHorizontalLine("\u2500", 45);
    std::cout << std::endl;
    std::cout << "  1. NO_REPEAT  - play in order, stop at end" << std::endl;
    std::cout << "  2. REPEAT_ONE - repeat current song forever" << std::endl;
    std::cout << "  3. REPEAT_ALL - loop whole playlist" << std::endl;
    std::cout << "  4. SHUFFLE    - random order";
    if (currentMode == "SHUFFLE")
    {
        std::cout << " \u25C0 (active)";
    }
    std::cout << std::endl;
}

std::string UIRenderer::formatDuration(int seconds) const
{
    int min = seconds / 60;
    int sec = seconds % 60;

    std::string result;
    result += (min < 10 ? "0" : "") + std::to_string(min);
    result += ":";
    result += (sec < 10 ? "0" : "") + std::to_string(sec);
    return result;
}

std::string UIRenderer::truncate(const std::string &str, size_t maxLen) const
{
    if (str.length() <= maxLen)
    {
        return str;
    }
    return str.substr(0, maxLen - 3) + "...";
}