#pragma once

#include <string>
#include <vector>

#include "Song.h"
#include "Playlist.h"
#include "Player.h"

class UIRenderer
{
public:

    UIRenderer() = default;
    ~UIRenderer() = default;

    //==========================
    // Window
    //==========================

    void clear();

    void beginWindow(const std::string& title);
    void endWindow();

    void topBorder();
    void bottomBorder();
    void separator();

    void blank();
    void emptyLine();

    void controlsBar(
    const std::vector<std::string>& controls
    );

    //==========================
    // Basic Text
    //==========================

    void textLine(const std::string& text);
    void centerLine(const std::string& text);
    void rightLine(const std::string& text);

    void message(const std::string& text);

    void print(const std::string& text);

    void line(int width = 62);

    //==========================
    // Header / Footer
    //==========================

    void showTitle(const std::string& title);

    void footer(const std::string& text);

    void section(const std::string& title);

    void drawTitleRow(const std::string& title);

    void drawSubTitle(const std::string& title);

    void drawSeparator();

    //==========================
    // Menu
    //==========================

    void menuItem(
        int number,
        const std::string& text,
        bool selected = false
    );

    void mainMenu();

    void settingsMenu(
        const std::string& currentMode
    );

    void filterMenu();

    //==========================
    // Prompt
    //==========================

    void prompt(const std::string& text);

    void waitForEnter();

    void pauseScreen();

    //==========================
    // Messages
    //==========================

    void error(const std::string& text);

    void warning(const std::string& text);

    void success(const std::string& text);

    void confirmMessage(
        const std::string& message
    );

    void printCenteredMessage(
        const std::string& message
    );

    void printEmptyPlaylist();

    void printNoResults();

    void printLoading(
        const std::string& text
    );

    void printCompleted();

    //==========================
    // Key / Value
    //==========================

    void keyValue(
        const std::string& key,
        const std::string& value
    );

    void doubleKeyValue(
        const std::string& leftKey,
        const std::string& leftValue,
        const std::string& rightKey,
        const std::string& rightValue
    );

    //==========================
    // Status
    //==========================

    void playbackState(
        PlayerState state
    );

    void statusBar(
        const std::string& state,
        const std::string& playlist,
        const std::string& mode,
        const std::string& duration
    );

    void progressBar(
        int current,
        int total,
        int width = 30
    );

    //==========================
    // Tables
    //==========================

    void tableHeader(
        const std::vector<std::string>& headers,
        const std::vector<int>& widths
    );

    void tableRow(
        const std::vector<std::string>& values,
        const std::vector<int>& widths
    );

    void songTableHeader();

    void playlistTableHeader();

    void songRow(
        int index,
        const Song* song,
        bool selected = false
    );

    void playlistRow(
        int index,
        const Playlist* playlist,
        bool active = false
    );

    void settingsRow(
        int index,
        const std::string& mode,
        bool active
    );

    void artistRow(
        int index,
        const std::string& artist,
        int songs
    );

    void albumRow(
        int index,
        const std::string& album,
        int songs
    );

    //==========================
    // Search / Sort
    //==========================

    void searchResultHeader(
        int count
    );

    void sortHeader(
        const std::string& currentSort
    );

    void sortMenu();

    //==========================
    // Predefined Headers
    //==========================

    void mainMenuHeader(
        const std::string& lastSong
    );

    void nowPlayingHeader();

    void playlistsHeader();

    void playlistHeader(
        const std::string& playlistName,
        int songCount
    );

    void settingsHeader(
        const std::string& currentMode
    );

    void filterHeader(
        const std::string& playlistName
    );

    void searchHeader(
        const std::string& query
    );

    //==========================
    // Predefined Footers
    //==========================

    void browseFooter();

    void nowPlayingFooter();

    //==========================
    // Full Screens
    //==========================

    void showMainMenu(
        const std::string& lastSong
    );

    void showPlaybackInfo(
        const Song* song,
        const std::string& playlist,
        const std::string& mode,
        PlayerState state
    );

    void showPlaylistMenu();

    void showBrowseMenu();

    void showNowPlayingMenu();

    void showSettingsMenu(
        const std::string& mode
    );

    void showFilterMenu();

    void showApplicationHeader();

    void showApplicationFooter();

    void showExitMessage();

    //==========================
    // Helpers
    //==========================

    std::string formatDuration(
        int seconds
    );

    void flush();

    void newline();
};