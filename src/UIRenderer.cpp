
#include "UIRenderer.h"
#include "Song.h"
#include "Playlist.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <algorithm> 

#ifdef _WIN32
#include <windows.h>
#define CLEAR_CMD "cls"
#else
#define CLEAR_CMD "clear"
#endif

void UIRenderer::hideCursor() const {
#ifdef _WIN32
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE; 
    SetConsoleCursorInfo(consoleHandle, &info);
#else
    std::cout << "\033[?25l"; 
#endif
}

void UIRenderer::gotoxy(int x, int y) const {
#ifdef _WIN32
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    std::cout << "\033[" << (y + 1) << ";" << (x + 1) << "H"; 
#endif
}

void UIRenderer::clearScreen() const {
    gotoxy(0, 0); 
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
        int padding = (width - 2 - static_cast<int>(title.length())) / 2;
        std::cout << "\u2551";
        for (int i = 0; i < padding; i++)
            std::cout << " ";
        std::cout << title;
        for (int i = 0; i < width - 2 - padding - static_cast<int>(title.length()); i++)
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
void UIRenderer::printNowPlaying(const Song *song, float currentTime, float totalTime, bool isPaused, const std::string& mode, const std::string& playlistName) const
{
    clearScreen(); 
    std::cout << std::endl;

    const std::string RESET        = "\033[0m";
    const std::string BORDER_BLUE  = "\033[38;5;111m"; 
    const std::string TEXT_WHITE   = "\033[97m";       
    const std::string TEXT_GRAY    = "\033[38;5;244m"; 
    const std::string VALUE_GREEN  = "\033[38;5;114m"; 
    const std::string SHIT_YELLOW  = "\033[38;5;215m"; 
    const std::string DIM_FOOTER   = "\033[38;5;240m"; 

    const std::string BAR_WHITE  = "\033[97m█\033[0m";
    const std::string BAR_GREEN  = "\033[38;5;114m█\033[0m";
    const std::string BAR_GRAY   = "\033[38;5;244m█\033[0m";
    const std::string BAR_YELLOW = "\033[38;5;215m█\033[0m";

    const int INNER_WIDTH = 60; 

    auto repeatStr = [](const std::string& ch, int count) {
        std::string r;
        for (int i = 0; i < count; ++i) r += ch;
        return r;
    };

    auto visual_len = [](const std::string& str) {
        int len = 0;
        bool in_ansi = false;
        for (size_t i = 0; i < str.length(); ++i) {
            if (str[i] == '\033') { in_ansi = true; continue; }
            if (in_ansi) { if (std::isalpha(str[i])) in_ansi = false; continue; }
            unsigned char c = str[i];
            if ((c & 0xC0) != 0x80) len++;
        }
        return len;
    };

    auto printLine = [&](const std::string& content) {
        int current_vis_len = visual_len(content);
        int padding = INNER_WIDTH - current_vis_len;
        std::cout << BORDER_BLUE << "  ║" << RESET << content;
        if (padding > 0) std::cout << std::string(padding, ' ');
        std::cout << BORDER_BLUE << "║" << RESET << std::endl;
    };

    if (song == nullptr) {
        std::cout << BORDER_BLUE << "  ╔" << repeatStr("═", INNER_WIDTH) << "╗" << RESET << std::endl;
        printLine(" No song is currently playing.");
        std::cout << BORDER_BLUE << "  ╚" << repeatStr("═", INNER_WIDTH) << "╝" << RESET << std::endl;
        return;
    }

    std::cout << BORDER_BLUE << "  ╔" << repeatStr("═", INNER_WIDTH) << "╗" << RESET << std::endl;
    std::string headerText = "♫  Terminal Music Player  ♫";
    int headPad = (INNER_WIDTH - visual_len(headerText)) / 2;
    printLine(std::string(headPad, ' ') + TEXT_WHITE + headerText);

    std::cout << BORDER_BLUE << "  ╠" << repeatStr("═", INNER_WIDTH) << "╣" << RESET << std::endl;
    printLine(" " + BAR_WHITE + " " + TEXT_WHITE + "Now Playing");

    std::string titleVal = truncate(song->getTitle(), 42);
    printLine(" " + BAR_GREEN + TEXT_GRAY + " Title  : " + VALUE_GREEN + titleVal);

    std::string artistVal = truncate(song->getArtist(), 42);
    printLine(" " + BAR_GRAY + TEXT_GRAY + " Artist : " + TEXT_WHITE + artistVal);

    std::string albumVal = truncate(song->getAlbum(), 32);
    std::string yearVal = "[" + std::to_string(song->getYear()) + "]";
    std::string albumLeft = " " + BAR_GRAY + TEXT_GRAY + " Album  : " + TEXT_GRAY + albumVal;
    int albumSpaces = INNER_WIDTH - visual_len(albumLeft) - visual_len(yearVal) - 1;
    printLine(albumLeft + std::string(albumSpaces > 0 ? albumSpaces : 0, ' ') + TEXT_GRAY + yearVal + " ");

    std::string genreVal = song->getGenre().empty() ? "Unknown" : song->getGenre(); 
    printLine(" " + BAR_GRAY + TEXT_GRAY + " Genre  : " + TEXT_GRAY + genreVal);

    std::cout << BORDER_BLUE << "  ╠" << repeatStr("═", INNER_WIDTH) << "╣" << RESET << std::endl;

    std::string statusVal = isPaused ? "⏸  PAUSED " : "▶  PLAYING";
    std::string playlistVal = "Playlist: " + playlistName;
    std::string statusLeft = " " + BAR_YELLOW + " " + SHIT_YELLOW + statusVal;
    int statusSpaces = INNER_WIDTH - visual_len(statusLeft) - visual_len(playlistVal) - 1;
    printLine(statusLeft + std::string(statusSpaces > 0 ? statusSpaces : 0, ' ') + SHIT_YELLOW + playlistVal + " ");

    std::string displayMode = mode;
    if (mode == "NO_REPEAT") displayMode = "No Repeat";
    else if (mode == "REPEAT_ONE") displayMode = "Repeat One";
    else if (mode == "REPEAT_ALL") displayMode = "Repeat All";
    else if (mode == "SHUFFLE") displayMode = "Shuffle";

    std::string modeVal = "Mode: " + displayMode;

    int curMin = static_cast<int>(currentTime) / 60;
    int curSec = static_cast<int>(currentTime) % 60;
    int totMin = static_cast<int>(totalTime) / 60;
    int totSec = static_cast<int>(totalTime) % 60;
    char timeBuf[64];
    snprintf(timeBuf, sizeof(timeBuf), "Time: %02d:%02d / %02d:%02d", curMin, curSec, totMin, totSec);
    std::string timeStr = timeBuf;

    std::string modeLeft = " " + BAR_YELLOW + " " + TEXT_GRAY + modeVal;
    int modeSpaces = INNER_WIDTH - visual_len(modeLeft) - visual_len(timeStr) - 1;
    printLine(modeLeft + std::string(modeSpaces > 0 ? modeSpaces : 0, ' ') + TEXT_GRAY + timeStr + " ");

    std::cout << BORDER_BLUE << "  ╠" << repeatStr("═", INNER_WIDTH) << "╣" << RESET << std::endl;
    std::string foot1 = "[p] play/pause  [s] stop  [n] next  [b] prev";
    int f1Pad = (INNER_WIDTH - visual_len(foot1)) / 2;
    printLine(std::string(f1Pad, ' ') + DIM_FOOTER + foot1);
    std::string foot2 = "[r] \u2190 10s   [f] \u2192 10s   [q] menu";
    int f2Pad = (INNER_WIDTH - visual_len(foot2)) / 2;
    printLine(std::string(f2Pad, ' ') + DIM_FOOTER + foot2);
    std::cout << BORDER_BLUE << "  ╚" << repeatStr("═", INNER_WIDTH) << "╝" << RESET << std::endl;
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

void UIRenderer::printPlaylistList(const std::vector<PlaylistInfo>& playlists) const
{
    clearScreen(); 
    std::cout << std::endl;

    // کدهای رنگی ANSI
    const std::string RESET        = "\033[0m";
    const std::string BORDER_BLUE  = "\033[38;5;111m"; 
    const std::string TEXT_WHITE   = "\033[97m";       
    const std::string TEXT_GRAY    = "\033[38;5;244m"; 
    const std::string OPTION_NUM   = "\033[38;5;220m"; 

    const int INNER_WIDTH = 60; 

    auto repeatStr = [](const std::string& ch, int count) {
        std::string r;
        for (int i = 0; i < count; ++i) r += ch;
        return r;
    };

    auto visual_len = [](const std::string& str) {
        int len = 0;
        bool in_ansi = false;
        for (size_t i = 0; i < str.length(); ++i) {
            if (str[i] == '\033') { in_ansi = true; continue; }
            if (in_ansi) { if (std::isalpha(str[i])) in_ansi = false; continue; }
            unsigned char c = str[i];
            if ((c & 0xC0) != 0x80) len++;
        }
        return len;
    };

    auto printLine = [&](const std::string& content) {
        int current_vis_len = visual_len(content);
        int padding = INNER_WIDTH - current_vis_len;
        std::cout << BORDER_BLUE << "  ║" << RESET << content;
        if (padding > 0) std::cout << std::string(padding, ' ');
        std::cout << BORDER_BLUE << "║" << RESET << std::endl;
    };

    std::cout << BORDER_BLUE << "  ╔" << repeatStr("═", INNER_WIDTH) << "╗" << RESET << std::endl;
    std::string titleText = "Playlists";
    int titlePad = (INNER_WIDTH - visual_len(titleText)) / 2;
    printLine(std::string(titlePad, ' ') + TEXT_WHITE + titleText);
    std::cout << BORDER_BLUE << "  ╠" << repeatStr("═", INNER_WIDTH) << "╣" << RESET << std::endl;

    std::string colHeader = "  #   Name";
    std::string colSongs = "Songs";
    int colSpaces = INNER_WIDTH - visual_len(colHeader) - visual_len(colSongs) - 4;
    printLine(colHeader + std::string(colSpaces > 0 ? colSpaces : 0, ' ') + colSongs + "    ");
    std::cout << BORDER_BLUE << "  ╠" << repeatStr("═", INNER_WIDTH) << "╣" << RESET << std::endl;

    if (playlists.empty()) {
        printLine("");
        std::string emptyMsg = "No playlists available.";
        int emptyPad = (INNER_WIDTH - visual_len(emptyMsg)) / 2;
        printLine(std::string(emptyPad, ' ') + TEXT_GRAY + emptyMsg);
        printLine("");
    } else {
        for (size_t i = 0; i < playlists.size(); ++i) {
            const auto& pl = playlists[i];
            
            std::string rowColor = pl.isActive ? OPTION_NUM : TEXT_GRAY;
            
            std::string idxStr = std::to_string(i + 1);
            std::string nameStr = truncate(pl.name, 30);
            std::string leftPart = "  " + idxStr + "   " + nameStr;
            
            int leftVis = visual_len(leftPart);
            if (leftVis < 40) {
                leftPart += std::string(40 - leftVis, ' ');
            }
            
            std::string rightPart = "";
            if (pl.isActive) {
                char countBuf[32];
                snprintf(countBuf, sizeof(countBuf), "▶  %2d   [active]", pl.songCount);
                rightPart = countBuf;
            } else {
                char countBuf[32];
                snprintf(countBuf, sizeof(countBuf), "    %2d", pl.songCount);
                rightPart = countBuf;
            }
            
            std::string fullRow = rowColor + leftPart + rightPart;
            int totalVis = visual_len(fullRow);
            int finalPadding = INNER_WIDTH - totalVis - 4; 
            
            printLine(rowColor + leftPart + rightPart + std::string(finalPadding > 0 ? finalPadding : 0, ' '));
        }
    }

    std::cout << BORDER_BLUE << "  ╠" << repeatStr("═", INNER_WIDTH) << "╣" << RESET << std::endl;
    std::string footLeft = "  Enter number to switch active playlist.";
    std::string footRight = "[0] back  ";
    int footSpaces = INNER_WIDTH - visual_len(footLeft) - visual_len(footRight);
    printLine(TEXT_GRAY + footLeft + std::string(footSpaces > 0 ? footSpaces : 0, ' ') + footRight);

    std::cout << BORDER_BLUE << "  ╚" << repeatStr("═", INNER_WIDTH) << "╝" << RESET << std::endl;

    std::cout << std::endl << TEXT_WHITE << "Choice: " << RESET;
}

void UIRenderer::printMainMenu(const std::string& lastPlayedSong) const
{
    clearScreen(); 
    std::cout << std::endl;

    const std::string RESET        = "\033[0m";
    const std::string BORDER_BLUE  = "\033[38;5;111m"; 
    const std::string TEXT_WHITE   = "\033[97m";       
    const std::string TEXT_GRAY    = "\033[38;5;244m"; 
    const std::string VALUE_GREEN  = "\033[38;5;114m"; 
    const std::string OPTION_NUM   = "\033[38;5;220m";

    const int INNER_WIDTH = 60; 

    auto repeatStr = [](const std::string& ch, int count) {
        std::string r;
        for (int i = 0; i < count; ++i) r += ch;
        return r;
    };

    auto visual_len = [](const std::string& str) {
        int len = 0;
        bool in_ansi = false;
        for (size_t i = 0; i < str.length(); ++i) {
            if (str[i] == '\033') {
                in_ansi = true;
                continue;
            }
            if (in_ansi) {
                if (std::isalpha(str[i])) in_ansi = false;
                continue;
            }
            unsigned char c = str[i];
            if ((c & 0xC0) != 0x80) len++;
        }
        return len;
    };

    auto printLine = [&](const std::string& content) {
        int current_vis_len = visual_len(content);
        int padding = INNER_WIDTH - current_vis_len;
        std::cout << BORDER_BLUE << "  ║" << RESET << content;
        if (padding > 0) {
            std::cout << std::string(padding, ' ');
        }
        std::cout << BORDER_BLUE << "║" << RESET << std::endl;
    };

    std::cout << BORDER_BLUE << "  ╔" << repeatStr("═", INNER_WIDTH) << "╗" << RESET << std::endl;
    
    std::string menuTitle = "Main Menu";
    int titlePad = (INNER_WIDTH - visual_len(menuTitle)) / 2;
    printLine(std::string(titlePad, ' ') + TEXT_WHITE + menuTitle);
    
    std::cout << BORDER_BLUE << "  ╠" << repeatStr("═", INNER_WIDTH) << "╣" << RESET << std::endl;

    printLine("");

    printLine("   " + OPTION_NUM + "1." + RESET + " Now Playing");
    printLine("   " + OPTION_NUM + "2." + RESET + " View Playlists");
    printLine("   " + OPTION_NUM + "3." + RESET + " Current Playlist Tracks");
    printLine("   " + OPTION_NUM + "4." + RESET + " Settings");
    
    printLine("");
    printLine("   " + OPTION_NUM + "0." + RESET + " Exit Application");
    
    printLine("");

    std::cout << BORDER_BLUE << "  ╠" << repeatStr("═", INNER_WIDTH) << "╣" << RESET << std::endl;
    
    std::string displaySong = lastPlayedSong.empty() ? "None" : truncate(lastPlayedSong, 44);
    printLine("  " + TEXT_GRAY + "Last played: " + VALUE_GREEN + displaySong);

    std::cout << BORDER_BLUE << "  ╚" << repeatStr("═", INNER_WIDTH) << "╝" << RESET << std::endl;

    std::cout << std::endl << "  " << TEXT_WHITE << "Enter option: " << RESET;
}

void UIRenderer::printPlaylistView(const std::string& playlistName, const std::vector<TrackInfo>& tracks) const
{
    clearScreen(); 
    std::cout << std::endl;

    const std::string RESET        = "\033[0m";
    const std::string BORDER_BLUE  = "\033[38;5;111m"; 
    const std::string TEXT_WHITE   = "\033[97m";       
    const std::string TEXT_GRAY    = "\033[38;5;244m"; 
    const std::string CURRENT_GOLD = "\033[38;5;220m"; 
    const std::string TRACK_GREEN  = "\033[38;5;114m";  

    const int INNER_WIDTH = 60; 

    auto repeatStr = [](const std::string& ch, int count) {
        std::string r;
        for (int i = 0; i < count; ++i) r += ch;
        return r;
    };

    auto visual_len = [](const std::string& str) {
        int len = 0;
        bool in_ansi = false;
        for (size_t i = 0; i < str.length(); ++i) {
            if (str[i] == '\033') { in_ansi = true; continue; }
            if (in_ansi) { if (std::isalpha(str[i])) in_ansi = false; continue; }
            unsigned char c = str[i];
            if ((c & 0xC0) != 0x80) len++;
        }
        return len;
    };

    auto printLine = [&](const std::string& content) {
        int current_vis_len = visual_len(content);
        int padding = INNER_WIDTH - current_vis_len;
        std::cout << BORDER_BLUE << "  ║" << RESET << content;
        if (padding > 0) std::cout << std::string(padding, ' ');
        std::cout << BORDER_BLUE << "║" << RESET << std::endl;
    };

    std::cout << BORDER_BLUE << "  ╔" << repeatStr("═", INNER_WIDTH) << "╗" << RESET << std::endl;
    std::string titleText = "Playlist: " + (playlistName.empty() ? "None" : playlistName);
    int titlePad = (INNER_WIDTH - visual_len(titleText)) / 2;
    printLine(std::string(titlePad > 0 ? titlePad : 0, ' ') + TEXT_WHITE + titleText);
    std::cout << BORDER_BLUE << "  ╠" << repeatStr("═", INNER_WIDTH) << "╣" << RESET << std::endl;

    std::string colLeft = "  #   Title";
    std::string colRight = "Artist";
    int colSpaces = INNER_WIDTH - visual_len(colLeft) - visual_len(colRight) - 6;
    printLine(colLeft + std::string(colSpaces > 0 ? colSpaces : 0, ' ') + colRight + "      ");
    std::cout << BORDER_BLUE << "  ╠" << repeatStr("═", INNER_WIDTH) << "╣" << RESET << std::endl;

    if (tracks.empty()) {
        printLine("");
        std::string emptyMsg = "No tracks in this playlist.";
        int emptyPad = (INNER_WIDTH - visual_len(emptyMsg)) / 2;
        printLine(std::string(emptyPad, ' ') + TEXT_GRAY + emptyMsg);
        printLine("");
    } else {
        for (size_t i = 0; i < tracks.size(); ++i) {
            const auto& track = tracks[i];
            
            std::string rowColor = track.isCurrent ? CURRENT_GOLD : TEXT_GRAY;
            std::string titleColor = track.isCurrent ? CURRENT_GOLD : TRACK_GREEN;
            
            std::string prefix = track.isCurrent ? "▶ " : "  ";
            std::string idxStr = std::to_string(i + 1);
            
            std::string cleanTitle = truncate(track.title, 28);
            std::string cleanArtist = truncate(track.artist, 18);
            
            std::string leftPart = " " + prefix + idxStr;
            if (idxStr.length() == 1) leftPart += "   ";
            else leftPart += "  ";
            
            leftPart += titleColor + cleanTitle;
            
            int leftVis = visual_len(leftPart);
            std::string middleSpaces = "";
            if (leftVis < 42) {
                middleSpaces = std::string(42 - leftVis, ' ');
            }
            
            std::string fullRowContent = leftPart + middleSpaces + rowColor + cleanArtist;
            int totalVis = visual_len(fullRowContent);
            int finalPadding = INNER_WIDTH - totalVis - 2; 
            
            printLine(fullRowContent + std::string(finalPadding > 0 ? finalPadding : 0, ' '));
        }
    }

    std::cout << BORDER_BLUE << "  ╠" << repeatStr("═", INNER_WIDTH) << "╣" << RESET << std::endl;
    std::string footLeft = " [s]Sort  [f]Filter  [/]Search  [c]Clear";
    std::string footRight = "[0]Back ";
    int footSpaces = INNER_WIDTH - visual_len(footLeft) - visual_len(footRight);
    printLine(TEXT_GRAY + footLeft + std::string(footSpaces > 0 ? footSpaces : 0, ' ') + footRight);

    std::cout << BORDER_BLUE << "  ╚" << repeatStr("═", INNER_WIDTH) << "╝" << RESET << std::endl;

    std::cout << std::endl << TEXT_WHITE << "  Choice (number or command): " << RESET;
}

void UIRenderer::printSettingsView(const std::string& currentModeStr) const
{

    clearScreen(); 
    std::cout << std::endl;

    const std::string RESET        = "\033[0m";
    const std::string BORDER_BLUE  = "\033[38;5;111m"; 
    const std::string TEXT_WHITE   = "\033[97m";       
    const std::string TEXT_GRAY    = "\033[38;5;244m"; 
    const std::string OPTION_NUM   = "\033[38;5;220m"; 
    const std::string CHECK_GREEN  = "\033[38;5;114m";

    const int INNER_WIDTH = 60; 

    auto repeatStr = [](const std::string& ch, int count) {
        std::string r;
        for (int i = 0; i < count; ++i) r += ch;
        return r;
    };

    auto visual_len = [](const std::string& str) {
        int len = 0;
        bool in_ansi = false;
        for (size_t i = 0; i < str.length(); ++i) {
            if (str[i] == '\033') { in_ansi = true; continue; }
            if (in_ansi) { if (std::isalpha(str[i])) in_ansi = false; continue; }
            unsigned char c = str[i];
            if ((c & 0xC0) != 0x80) len++;
        }
        return len;
    };

    auto printLine = [&](const std::string& content) {
        int current_vis_len = visual_len(content);
        int padding = INNER_WIDTH - current_vis_len;
        std::cout << BORDER_BLUE << "  ║" << RESET << content;
        if (padding > 0) std::cout << std::string(padding, ' ');
        std::cout << BORDER_BLUE << "║" << RESET << std::endl;
    };

    auto toUpper = [](std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
    };

    std::cout << BORDER_BLUE << "  ╔" << repeatStr("═", INNER_WIDTH) << "╗" << RESET << std::endl;
    std::string titleText = "Settings - Playback Mode";
    int titlePad = (INNER_WIDTH - visual_len(titleText)) / 2;
    printLine(std::string(titlePad, ' ') + TEXT_WHITE + titleText);
    std::cout << BORDER_BLUE << "  ╠" << repeatStr("═", INNER_WIDTH) << "╣" << RESET << std::endl;

    printLine("");

    std::vector<std::pair<std::string, std::string>> modes = {
        {"1. No Repeat", "NO_REPEAT"},
        {"2. Repeat One", "REPEAT_ONE"},
        {"3. Repeat All", "REPEAT_ALL"},
        {"4. Shuffle",    "SHUFFLE"}
    };

    for (const auto& mode : modes) {
        bool isActive = (toUpper(currentModeStr) == toUpper(mode.second));
        
        std::string leftPart = "   " + OPTION_NUM + mode.first.substr(0, 2) + RESET + TEXT_WHITE + mode.first.substr(2);
        
        std::string rightPart = "";
        if (isActive) {
            rightPart = CHECK_GREEN + " [✔] active" + RESET;
        } else {
            rightPart = TEXT_GRAY + "  [ ]       " + RESET;
        }
        
        int leftVis = visual_len(leftPart);
        int rightVis = visual_len(rightPart);
        int middleSpaces = INNER_WIDTH - leftVis - rightVis - 4; 
        
        printLine(leftPart + std::string(middleSpaces > 0 ? middleSpaces : 0, ' ') + rightPart);
    }

    printLine(""); 

    std::cout << BORDER_BLUE << "  ╠" << repeatStr("═", INNER_WIDTH) << "╣" << RESET << std::endl;
    std::string footLeft = "  Select a number to change mode.";
    std::string footRight = "[0] save & back  ";
    int footSpaces = INNER_WIDTH - visual_len(footLeft) - visual_len(footRight);
    printLine(TEXT_GRAY + footLeft + std::string(footSpaces > 0 ? footSpaces : 0, ' ') + footRight);

    std::cout << BORDER_BLUE << "  ╚" << repeatStr("═", INNER_WIDTH) << "╝" << RESET << std::endl;

    std::cout << std::endl << TEXT_WHITE << "  Choice: " << RESET;
}