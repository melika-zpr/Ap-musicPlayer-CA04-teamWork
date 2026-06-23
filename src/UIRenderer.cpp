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
    (void)currentTime; // جلوگیری از وارنینگ کامپایلر

    clearScreen(); 
    std::cout << std::endl;

    // کدهای رنگی ANSI برای استایل‌دهی سنترال
    const std::string RESET        = "\033[0m";
    const std::string BORDER_BLUE  = "\033[38;5;111m"; // آبی مرزها
    const std::string TEXT_WHITE   = "\033[97m";       // سفید درخشان
    const std::string TEXT_GRAY    = "\033[38;5;244m"; // خاکستری لیبل‌ها
    const std::string VALUE_GREEN  = "\033[38;5;114m"; // سبز عنوان آهنگ
    const std::string SHIT_YELLOW  = "\033[38;5;215m"; // زرد وضعیت
    const std::string DIM_FOOTER   = "\033[38;5;240m"; // خاکستری تیره راهنما

    // بلوک‌های رنگی فقط برای سمت چپ (سمت راست کاملاً حذف شد)
    const std::string BAR_WHITE  = "\033[97m█\033[0m";
    const std::string BAR_GREEN  = "\033[38;5;114m█\033[0m";
    const std::string BAR_GRAY   = "\033[38;5;244m█\033[0m";
    const std::string BAR_YELLOW = "\033[38;5;215m█\033[0m";

    const int INNER_WIDTH = 60; // عرض ثابت داخل باکس

    // تابع کمکی برای تکرار خطوط جدول
    auto repeatStr = [](const std::string& ch, int count) {
        std::string r;
        for (int i = 0; i < count; ++i) r += ch;
        return r;
    };

    // تابع هوشمند برای محاسبه طول واقعی بصری (حذف افکت‌های ANSI و شمارش درست UTF-8)
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
            // شمارش بایت‌های اصلی UTF-8
            unsigned char c = str[i];
            if ((c & 0xC0) != 0x80) len++;
        }
        return len;
    };

    // همرنگ‌ساز و ترازکننده خودکار دیواره سمت راست جدول
    auto printLine = [&](const std::string& content) {
        int current_vis_len = visual_len(content);
        int padding = INNER_WIDTH - current_vis_len;
        std::cout << BORDER_BLUE << "  ║" << RESET << content;
        if (padding > 0) {
            std::cout << std::string(padding, ' ');
        }
        std::cout << BORDER_BLUE << "║" << RESET << std::endl;
    };

    if (song == nullptr) {
        std::cout << BORDER_BLUE << "  ╔" << repeatStr("═", INNER_WIDTH) << "╗" << RESET << std::endl;
        printLine(" No song is currently playing.");
        std::cout << BORDER_BLUE << "  ╚" << repeatStr("═", INNER_WIDTH) << "╝" << RESET << std::endl;
        return;
    }

    // 1. هدر اصلی بازیکن
    std::cout << BORDER_BLUE << "  ╔" << repeatStr("═", INNER_WIDTH) << "╗" << RESET << std::endl;
    
    std::string headerText = "♫  Terminal Music Player  ♫";
    int headPad = (INNER_WIDTH - visual_len(headerText)) / 2;
    std::string headerContent = std::string(headPad, ' ') + TEXT_WHITE + headerText;
    printLine(headerContent);

    // 2. بخش جزئیات آهنگ (Now Playing)
    std::cout << BORDER_BLUE << "  ╠" << repeatStr("═", INNER_WIDTH) << "╣" << RESET << std::endl;

    // ردیف Now Playing
    printLine(" " + BAR_WHITE + " " + TEXT_WHITE + "Now Playing");

    // ردیف Title (سبز)
    std::string titleVal = truncate(song->getTitle(), 42);
    printLine(" " + BAR_GREEN + TEXT_GRAY + " Title  : " + VALUE_GREEN + titleVal);

    // ردیف Artist
    std::string artistVal = truncate(song->getArtist(), 42);
    printLine(" " + BAR_GRAY + TEXT_GRAY + " Artist : " + TEXT_WHITE + artistVal);

    // ردیف Album + Year (تراز شده در راست)
    std::string albumVal = truncate(song->getAlbum(), 32);
    std::string yearVal = "[1975]"; 
    std::string albumLeft = " " + BAR_GRAY + TEXT_GRAY + " Album  : " + TEXT_GRAY + albumVal;
    int albumSpaces = INNER_WIDTH - visual_len(albumLeft) - visual_len(yearVal) - 1;
    std::string albumContent = albumLeft + std::string(albumSpaces > 0 ? albumSpaces : 0, ' ') + TEXT_GRAY + yearVal + " ";
    printLine(albumContent);

    // ردیف Genre
    std::string genreVal = "Rock"; 
    printLine(" " + BAR_GRAY + TEXT_GRAY + " Genre  : " + TEXT_GRAY + genreVal);

    // 3. بخش وضعیت پخش (Playing Status)
    std::cout << BORDER_BLUE << "  ╠" << repeatStr("═", INNER_WIDTH) << "╣" << RESET << std::endl;

    // ردیف وضعیت + نام پلی‌لیست
    std::string statusVal = "▶  PLAYING";
    std::string playlistVal = "Playlist: rock_hits"; 
    std::string statusLeft = " " + BAR_YELLOW + " " + SHIT_YELLOW + statusVal;
    int statusSpaces = INNER_WIDTH - visual_len(statusLeft) - visual_len(playlistVal) - 1;
    std::string statusContent = statusLeft + std::string(statusSpaces > 0 ? statusSpaces : 0, ' ') + SHIT_YELLOW + playlistVal + " ";
    printLine(statusContent);

    // ردیف Mode + Duration واقعی
    std::string modeVal = "Mode: SHUFFLE";
    int totMin = static_cast<int>(totalTime) / 60;
    int totSec = static_cast<int>(totalTime) % 60;
    char durationBuf[32];
    snprintf(durationBuf, sizeof(durationBuf), "Duration: %02d:%02d", totMin, totSec);
    std::string durationStr = durationBuf;

    std::string modeLeft = " " + BAR_YELLOW + " " + TEXT_GRAY + modeVal;
    int modeSpaces = INNER_WIDTH - visual_len(modeLeft) - visual_len(durationStr) - 1;
    std::string modeContent = modeLeft + std::string(modeSpaces > 0 ? modeSpaces : 0, ' ') + TEXT_GRAY + durationStr + " ";
    printLine(modeContent);

    // 4. فوتر میانبرها (تراز شده دو خطی برای جا شدن f و r)
    std::cout << BORDER_BLUE << "  ╠" << repeatStr("═", INNER_WIDTH) << "╣" << RESET << std::endl;

    std::string foot1 = "[p] play/pause  [s] stop  [n] next  [b] prev";
    int f1Pad = (INNER_WIDTH - visual_len(foot1)) / 2;
    std::string foot1Content = std::string(f1Pad, ' ') + DIM_FOOTER + foot1;
    printLine(foot1Content);

    std::string foot2 = "[f] fwd 10s   [r] bwd 10s   [q] menu";
    int f2Pad = (INNER_WIDTH - visual_len(foot2)) / 2;
    std::string foot2Content = std::string(f2Pad, ' ') + DIM_FOOTER + foot2;
    printLine(foot2Content);

    // بستن باکس
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