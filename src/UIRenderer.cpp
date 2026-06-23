#include "UIRenderer.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

namespace
{
    constexpr int WINDOW_WIDTH = 72;

    const std::string TL = "┌";
    const std::string TR = "┐";
    const std::string BL = "└";
    const std::string BR = "┘";

    const std::string LT = "├";
    const std::string RT = "┤";

    const std::string H = "─";
    const std::string V = "│";

}

// تعداد ستون‌های نمایشی یک رشته UTF-8 را برمی‌گرداند.
// کاراکترهای 3 بایتی مثل ♫ ▶ ◀ █ ░ ─ │ هر کدام 1 ستون نمایشی دارند.
static int displayWidth(const std::string& str)
{
    int width = 0;
    for (size_t i = 0; i < str.size(); )
    {
        unsigned char c = str[i];
        if (c < 0x80)        { ++width; ++i; }   // ASCII: 1 بایت، 1 ستون
        else if (c < 0xC0)   { ++i; }             // بایت ادامه‌دار: رد کن
        else if (c < 0xE0)   { ++width; i += 2; } // 2 بایتی: 1 ستون
        else if (c < 0xF0)   { ++width; i += 3; } // 3 بایتی: 1 ستون
        else                  { width += 2; i += 4; } // 4 بایتی (emoji): 2 ستون
    }
    return width;
}

static std::string repeat(const std::string& s, int count)
{
    std::string out;

    for (int i = 0; i < count; i++)
        out += s;

    return out;
}

static std::string centerText(
    const std::string& text,
    int width
)
{
    int dw = displayWidth(text);
    if (dw >= width)
        return text;

    int left  = (width - dw) / 2;
    int right =  width - dw  - left;

    return std::string(left, ' ')
        + text
        + std::string(right, ' ');
}

static std::string leftText(
    const std::string& text,
    int width
)
{
    int dw = displayWidth(text);
    if (dw >= width)
        return text;

    return text + std::string(width - dw, ' ');
}

static std::string rightText(
    const std::string& text,
    int width
)
{
    int dw = displayWidth(text);
    if (dw >= width)
        return text;

    return std::string(width - dw, ' ')
        + text;
}

enum class Align
{
    Left,
    Center,
    Right
};

static void drawRow(
    const std::string& text,
    Align align
)
{
    std::string output;

    switch (align)
    {
    case Align::Left:
        output = leftText(text, WINDOW_WIDTH);
        break;

    case Align::Center:
        output = centerText(text, WINDOW_WIDTH);
        break;

    case Align::Right:
        output = rightText(text, WINDOW_WIDTH);
        break;
    }

    std::cout
        << V
        << output
        << V
        << '\n';
}


void UIRenderer::clear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}



void UIRenderer::topBorder()
{
    std::cout
        << TL
        << repeat(H, WINDOW_WIDTH)
        << TR
        << '\n';
}



void UIRenderer::bottomBorder()
{
    std::cout
        << BL
        << repeat(H, WINDOW_WIDTH)
        << BR
        << '\n';
}



void UIRenderer::separator()
{
    std::cout
        << LT
        << repeat(H, WINDOW_WIDTH)
        << RT
        << '\n';
}



void UIRenderer::emptyLine()

{

    drawRow("", Align::Left);

}



void UIRenderer::textLine(

    const std::string& text

)

{

    drawRow(text, Align::Left);

}



void UIRenderer::centerLine(

    const std::string& text

)

{

    drawRow(text, Align::Center);

}



void UIRenderer::rightLine(

    const std::string& text

)

{

    drawRow(text, Align::Right);

}



void UIRenderer::beginWindow(
    const std::string& title
)
{
    topBorder();
    centerLine(title);
    separator();
}



void UIRenderer::endWindow()
{
    bottomBorder();
}



void UIRenderer::section(
    const std::string& title
)
{
    textLine(title);
    separator();
}



void UIRenderer::message(

    const std::string& text

)

{

    drawRow(text, Align::Left);

}



void UIRenderer::blank()
{
    emptyLine();
}



void UIRenderer::footer(
    const std::string& text
)
{
    separator();
    textLine(text);
}



std::string UIRenderer::formatDuration(
    int seconds
)
{
    int minutes = seconds / 60;
    int remain = seconds % 60;

    std::stringstream ss;

    ss
        << std::setw(2)
        << std::setfill('0')
        << minutes
        << ":"
        << std::setw(2)
        << remain;

    return ss.str();
}

// ===== END OF PART 1 =====
// Continue with Part 2

void UIRenderer::menuItem(
    int number,
    const std::string& text,
    bool selected
)
{
    std::stringstream ss;

    if (selected)
        ss << "▶ ";
    else
        ss << "  ";

    ss << number << ". " << text;

    textLine(ss.str());
}



void UIRenderer::keyValue(
    const std::string& key,
    const std::string& value
)
{
    std::stringstream ss;

    ss << std::left
       << std::setw(12)
       << key
       << ": "
       << value;

    textLine(ss.str());
}



void UIRenderer::doubleKeyValue(
    const std::string& leftKey,
    const std::string& leftValue,
    const std::string& rightKey,
    const std::string& rightValue
)
{
    std::stringstream ss;

    ss << std::left
       << std::setw(8)
       << leftKey
       << ": "
       << std::setw(20)
       << leftValue;

    ss << " ";

    ss << std::setw(8)
       << rightKey
       << ": "
       << rightValue;

    textLine(ss.str());
}



void UIRenderer::statusBar(
    const std::string& state,
    const std::string& playlist,
    const std::string& mode,
    const std::string& duration
)
{
    std::stringstream line1;
    line1 << state << "    Playlist: " << playlist;

    std::stringstream line2;
    line2 << "Mode: "
          << mode
          << "    Duration: "
          << duration;

    separator();
    textLine(line1.str());
    textLine(line2.str());
}



void UIRenderer::prompt(
    const std::string&
)
{
    std::cout << "\n> ";
}



void UIRenderer::error(
    const std::string& text
)
{
    separator();
    textLine("ERROR: " + text);
}



void UIRenderer::success(
    const std::string& text
)
{
    separator();
    textLine("SUCCESS: " + text);
}



void UIRenderer::warning(
    const std::string& text
)
{
    separator();
    textLine("WARNING: " + text);
}



void UIRenderer::nowPlayingHeader()
{
    beginWindow("♫ Terminal Music Player ♫");
    textLine("Now Playing");
    separator();
}



void UIRenderer::mainMenuHeader(
    const std::string& lastSong
)
{
    beginWindow("♫ Terminal Music Player ♫");

    if (!lastSong.empty())
    {
        textLine("Last played: " + lastSong);
        separator();
    }
}



void UIRenderer::playlistHeader(
    const std::string& playlistName,
    int songCount
)
{
    beginWindow("Browse: " + playlistName);

    std::stringstream ss;

    ss << playlistName
       << " ("
       << songCount
       << " songs)";

    textLine(ss.str());

    separator();
}



void UIRenderer::settingsHeader(
    const std::string& currentMode
)
{
    beginWindow("Settings");

    textLine("Playback Mode");

    textLine("Current: " + currentMode);

    separator();
}



void UIRenderer::playlistsHeader()
{
    beginWindow("Playlists");

    textLine("#   Name                         Songs");

    separator();
}



void UIRenderer::filterHeader(
    const std::string& playlistName
)
{
    beginWindow("Filter");

    textLine("Filter songs in: " + playlistName);

    separator();
}



void UIRenderer::searchHeader(
    const std::string& query
)
{
    beginWindow("Search");

    textLine("Search: \"" + query + "\"");

    separator();
}



void UIRenderer::waitForEnter()
{
    separator();

    centerLine("Press ENTER to continue...");

    bottomBorder();

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n'
    );

    std::cin.get();
}



// ===== END OF PART 2 =====
// Continue with Part 3

void UIRenderer::tableHeader(
    const std::vector<std::string>& headers,
    const std::vector<int>& widths
)
{
    std::stringstream row;

    row << " ";

    for (size_t i = 0; i < headers.size(); ++i)
    {
        std::string text = headers[i];

        if ((int)text.length() > widths[i])
            text = text.substr(0, widths[i]);

        row << std::left
            << std::setw(widths[i])
            << text;

        if (i != headers.size() - 1)
            row << " │ ";
    }

    textLine(row.str());

    separator();
}



void UIRenderer::tableRow(
    const std::vector<std::string>& values,
    const std::vector<int>& widths
)
{
    std::stringstream row;

    row << " ";

    for (size_t i = 0; i < values.size(); ++i)
    {
        std::string value = values[i];
        int dw = displayWidth(value);

        // اگر متن بیشتر از عرض ستون بود، کوتاه کن
        if (dw > widths[i])
        {
            // از انتها حذف کن تا displayWidth مناسب بشه
            while (displayWidth(value) > widths[i] - 3 && !value.empty())
                value.pop_back();
            value += "...";
            dw = displayWidth(value);
        }

        // padding دستی به جای setw (چون setw بایت‌محور است)
        row << value
            << std::string(widths[i] - dw, ' ');

        if (i != values.size() - 1)
            row << " │ ";
    }

    textLine(row.str());
}



void UIRenderer::songRow(
    int index,
    const Song* song,
    bool selected
)
{
    if (song == nullptr)
        return;

    std::string marker =
        selected ? "▶" : " ";

    std::stringstream number;

    number
        << marker
        << index;

    tableRow(
        {
            number.str(),
            song->getTitle(),
            song->getArtist(),
            formatDuration(song->getDurationSec())
        },
        {
            4,
            34,
            20,
            8
        }
    );
}



void UIRenderer::playlistRow(
    int index,
    const Playlist* playlist,
    bool active
)
{
    if (playlist == nullptr)
        return;

    std::stringstream songs;

    songs << playlist->size();

    std::string name =
        playlist->getName();

    if (active)
        name += "  ▶";

    tableRow(
        {
            std::to_string(index),
            name,
            songs.str()
        },
        {
            4,
            50,
            8
        }
    );
}



void UIRenderer::settingsRow(
    int index,
    const std::string& mode,
    bool active
)
{
    std::string text =
        std::to_string(index)
        + ". "
        + mode;

    if (active)
        text += "   ◀";

    textLine(text);
}



void UIRenderer::artistRow(
    int index,
    const std::string& artist,
    int songs
)
{
    std::stringstream ss;

    ss
        << index
        << ". "
        << artist
        << " ("
        << songs
        << " songs)";

    textLine(ss.str());
}



void UIRenderer::albumRow(
    int index,
    const std::string& album,
    int songs
)
{
    std::stringstream ss;

    ss
        << index
        << ". "
        << album
        << " ("
        << songs
        << " songs)";

    textLine(ss.str());
}



void UIRenderer::searchResultHeader(
    int count
)
{
    std::stringstream ss;

    ss
        << count
        << " result(s).";

    separator();

    textLine(ss.str());
}



void UIRenderer::sortHeader(
    const std::string& currentSort
)
{
    separator();

    textLine(
        "Sort: "
        + currentSort
    );
}



void UIRenderer::sortMenu()
{
    separator();

    textLine("Sort by:");

    textLine("1. Title");

    textLine("2. Artist");

    textLine("3. Album");

    textLine("4. Year");

    textLine("5. Duration");

    textLine("");

    textLine("Add '+' for descending");

    textLine("Example: 4+");
}



// ===== END OF PART 3 =====
// Continue with Part 4

void UIRenderer::controlsBar(
    const std::vector<std::string>& controls
)
{
    separator();

    std::stringstream ss;

    for (size_t i = 0; i < controls.size(); i++)
    {
        ss << "[" << controls[i] << "]";

        if (i != controls.size() - 1)
            ss << " ";
    }

    textLine(ss.str());
}



void UIRenderer::mainMenu()
{
    menuItem(1, "Now Playing");
    menuItem(2, "Playlists");
    menuItem(3, "Browse Playlist");
    menuItem(4, "Settings");

    footer("0. Quit (saves state)");
}



void UIRenderer::settingsMenu(
    const std::string& currentMode
)
{
    textLine("Playback Mode");
    separator();

    settingsRow(
        1,
        "NO_REPEAT",
        currentMode == "NO_REPEAT"
    );

    settingsRow(
        2,
        "REPEAT_ONE",
        currentMode == "REPEAT_ONE"
    );

    settingsRow(
        3,
        "REPEAT_ALL",
        currentMode == "REPEAT_ALL"
    );

    settingsRow(
        4,
        "SHUFFLE",
        currentMode == "SHUFFLE"
    );

    footer("0. Back");
}



void UIRenderer::playlistTableHeader()
{
    tableHeader(
        {
            "#",
            "Name",
            "Songs"
        },
        {
            4,
            40,
            8
        }
    );
}



void UIRenderer::songTableHeader()
{
    tableHeader(
        {
            "#",
            "Title",
            "Artist",
            "Dur"
        },
        {
            4,
            28,
            18,
            8
        }
    );
}



void UIRenderer::browseFooter()
{
    separator();

    textLine("[num] play song");

    textLine("[s] sort");

    textLine("[f] filter");

    textLine("[/] search");

    textLine("[0] back");
}



void UIRenderer::nowPlayingFooter()
{
    separator();

    textLine("[p] pause");

    textLine("[n] next");

    textLine("[b] previous");

    textLine("[s] stop");

    textLine("[q] menu");
}



void UIRenderer::filterMenu()
{
    textLine("Filter by:");

    textLine("");

    textLine("1. Artist");

    textLine("2. Album");

    footer("0. Back");
}



void UIRenderer::printCenteredMessage(
    const std::string& message
)
{
    emptyLine();

    centerLine(message);

    emptyLine();
}



void UIRenderer::printEmptyPlaylist()
{
    printCenteredMessage(
        "Playlist is empty."
    );
}



void UIRenderer::printNoResults()
{
    printCenteredMessage(
        "No matching songs found."
    );
}



void UIRenderer::printLoading(
    const std::string& text
)
{
    separator();
    textLine("Loading " + text + "...");
}



void UIRenderer::printCompleted()
{
    textLine("Done.");
}



void UIRenderer::confirmMessage(
    const std::string& message
)
{
    separator();

    centerLine(message);

    separator();
}



void UIRenderer::playbackState(
    PlayerState state
)
{
    switch (state)
    {
    case PlayerState::Playing:
        textLine("▶ PLAYING");
        break;

    case PlayerState::Paused:
        textLine("⏸ PAUSED");
        break;

    case PlayerState::Stopped:
        textLine("■ STOPPED");
        break;
    }
}



// ===== END OF PART 4 =====
// Continue with Part 5

void UIRenderer::progressBar(
    int current,
    int total,
    int width
)
{
    if (total <= 0)
        total = 1;

    int filled = current * width / total;

    std::stringstream ss;

    ss << "[";

    for (int i = 0; i < width; i++)
    {
        if (i < filled)
            ss << "█";
        else
            ss << "░";
    }

    ss << "] ";

    ss << formatDuration(current);

    ss << " / ";

    ss << formatDuration(total);

    textLine(ss.str());
}



void UIRenderer::showPlaybackInfo(
    const Song* song,
    const std::string& playlist,
    const std::string& mode,
    PlayerState state
)
{
    if (song == nullptr)
    {
        printCenteredMessage("No song selected.");
        return;
    }

    keyValue("Title", song->getTitle());

    keyValue("Artist", song->getArtist());

    keyValue(
        "Album",
        song->getAlbum()
    );

    keyValue(
        "Genre",
        song->getGenre()
    );

    separator();

    playbackState(state);

    doubleKeyValue(
        "Playlist",
        playlist,
        "Mode",
        mode
    );

    keyValue(
        "Duration",
        formatDuration(song->getDurationSec())
    );
}



void UIRenderer::showMainMenu(
    const std::string& lastSong
)
{
    clear();

    mainMenuHeader(lastSong);

    menuItem(1, "Now Playing");
    menuItem(2, "Playlists");
    menuItem(3, "Browse Playlist");
    menuItem(4, "Settings");

    footer("0. Quit (saves state)");

    endWindow();

    prompt("Choice:");
}



void UIRenderer::showPlaylistMenu()
{
    footer(
        "Enter playlist number. [0] Back"
    );

    endWindow();

    prompt("Choice:");
}



void UIRenderer::showBrowseMenu()
{
    browseFooter();

    endWindow();

    prompt("Choice:");
}



void UIRenderer::showNowPlayingMenu()
{
    nowPlayingFooter();

    endWindow();

    prompt("Choice:");
}



void UIRenderer::showSettingsMenu(
    const std::string& mode
)
{
    clear();

    settingsHeader(mode);

    settingsMenu(mode);

    endWindow();

    prompt("Choice:");
}



void UIRenderer::showFilterMenu()
{
    filterMenu();

    endWindow();

    prompt("Choice:");
}



void UIRenderer::drawTitleRow(
    const std::string& title
)
{
    separator();

    centerLine(title);

    separator();
}



void UIRenderer::drawSubTitle(
    const std::string& title
)
{
    textLine(title);
}



void UIRenderer::drawSeparator()
{
    separator();
}



void UIRenderer::newline()
{
    std::cout << '\n';
}



void UIRenderer::flush()
{
    std::cout.flush();
}



void UIRenderer::pauseScreen()
{
    waitForEnter();
}



void UIRenderer::showApplicationHeader()
{
    clear();

    beginWindow(
        "♫ Terminal Music Player ♫"
    );
}



void UIRenderer::showApplicationFooter()
{
    endWindow();
}



void UIRenderer::showExitMessage()
{
    clear();

    beginWindow(
        "♫ Terminal Music Player ♫"
    );

    blank();

    centerLine(
        "Thank you for using"
    );

    centerLine(
        "Terminal Music Player"
    );

    blank();

    endWindow();
}



// =========================
// END OF UIRenderer.cpp
// =========================