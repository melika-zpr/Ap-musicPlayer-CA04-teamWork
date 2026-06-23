#include "PlaylistViewScreen.h"
#include "Player.h"
#include "Playlist.h"
#include "Song.h"
#include "UIRenderer.h"
#include "InputHandler.h"
#include <algorithm>
#include <set>

Playlist* PlaylistViewScreen::getActivePlaylist() const {
    if (player_ == nullptr) return nullptr;
    return player_->getCurrentPlaylist();
}

void PlaylistViewScreen::initializeSongs(Playlist* playlist) {
    if (playlist != nullptr) {
        displayedSongs_ = playlist->getSongs();
        lastPlaylist_ = playlist;
    }
}

void PlaylistViewScreen::render() {
    Playlist* playlist = getActivePlaylist();
    if (playlist != lastPlaylist_) {
        initializeSongs(playlist);
        subScreen_ = PlaylistSubScreen::DEFAULT;
    }

    if (playlist == nullptr || playlist->isEmpty()) {
        ui_->printHeader("Playlist View");
        ui_->printMessage("  No playlist selected or empty.\n\n  0. Back");
        return;
    }

    if (subScreen_ == PlaylistSubScreen::DEFAULT) {
        ui_->printHeader("Playlist View");
        displayPlaylist(displayedSongs_);
        displaySubMenu();
    }
}

void PlaylistViewScreen::displayPlaylist(const std::vector<Song*>& songs) const {
    Playlist* playlist = getActivePlaylist();
    ui_->printMessage("  Playlist: " + playlist->getName() + " (" + std::to_string(songs.size()) + " songs)");
    ui_->drawHorizontalLine("-", 45);
    ui_->printSongList(songs, 20);
}

void PlaylistViewScreen::displaySubMenu() const {
    ui_->printMessage("\n  [s] Sort  [f] Filter  [/] Search  [c] Clear Filters  [0] Back\n");
}

ScreenType PlaylistViewScreen::handleInput() {
    Playlist* playlist = getActivePlaylist();
    if (playlist == nullptr || playlist->isEmpty()) {
        input_->waitForKey("Press Enter to continue...");
        return ScreenType::MAIN_MENU;
    }

    if (subScreen_ == PlaylistSubScreen::DEFAULT) {
        char key = input_->getCharKey("");
        switch (key) {
            case '0': return ScreenType::MAIN_MENU;
            case 's': subScreen_ = PlaylistSubScreen::SORT_MENU; handleSortMenu(); break;
            case 'f': subScreen_ = PlaylistSubScreen::FILTER_MENU; handleFilterMenu(playlist); break;
            case '/': {
                std::string query = input_->getStringInput("Search query: ");
                displayedSongs_ = playlist->search(query);
                break;
            }
            case 'c': initializeSongs(playlist); break;
            default:
                if (key >= '1' && key <= '9') {
                    int index = key - '1';
                    if (index < static_cast<int>(displayedSongs_.size()) && player_) {
                        int origIndex = playlist->indexOf(displayedSongs_[index]);
                        if (origIndex != -1) {
                            player_->stop();
                            player_->setCurrentIndex(origIndex);
                            player_->play();
                        }
                    }
                }
                break;
        }
    }
    return ScreenType::PLAYLIST_VIEW;
}

void PlaylistViewScreen::handleSortMenu() {
    ui_->printMessage("\n  Sort by: 1.Title  2.Artist  3.Album  4.Year  5.Duration");
    ui_->printMessage("  Add '-' for descending (e.g., 4- for Year desc). 0 to Cancel.");
    std::string choiceStr = input_->getStringInput("\n  Sort choice: ");

    if (choiceStr == "0" || choiceStr.empty()) {
        subScreen_ = PlaylistSubScreen::DEFAULT;
        return;
    }

    bool descending = false;
    if (choiceStr.back() == '-') {
        descending = true;
        choiceStr.pop_back();
    }

    int choice = 0;
    try { choice = std::stoi(choiceStr); } catch (...) { choice = 0; }

    if (choice >= 1 && choice <= 5) {
        std::sort(displayedSongs_.begin(), displayedSongs_.end(), [choice, descending](Song* a, Song* b) {
            bool result = false;
            switch (choice) {
                case 1: result = a->getTitle() < b->getTitle(); break;
                case 2: result = a->getArtist() < b->getArtist(); break;
                case 3: result = a->getAlbum() < b->getAlbum(); break;
                case 4: result = a->getYear() < b->getYear(); break;
                case 5: result = a->getDurationSec() < b->getDurationSec(); break;
            }
            return descending ? !result : result;
        });
    }
    subScreen_ = PlaylistSubScreen::DEFAULT;
}

void PlaylistViewScreen::handleFilterMenu(Playlist* playlist) {
    int filterType = input_->getIntChoice("\n  1. By Artist  2. By Album  0. Cancel\n  Choice: ", 0, 2);
    if (filterType == 0) {
        subScreen_ = PlaylistSubScreen::DEFAULT;
        return;
    }

    std::set<std::string> uniqueItems;
    for (Song* song : playlist->getSongs()) {
        if (!song) continue;
        uniqueItems.insert(filterType == 1 ? song->getArtist() : song->getAlbum());
    }

    std::vector<std::string> itemsList(uniqueItems.begin(), uniqueItems.end());
    ui_->printMessage("\n  Available Options:");
    for (size_t i = 0; i < itemsList.size(); ++i) {
        ui_->printMessage("  " + std::to_string(i + 1) + ". " + itemsList[i]);
    }

    int itemChoice = input_->getIntChoice("\n  Select option (0 to cancel): ", 0, itemsList.size());
    if (itemChoice > 0) {
        std::string selected = itemsList[itemChoice - 1];
        displayedSongs_ = (filterType == 1) ? playlist->filterByArtist(selected) : playlist->filterByAlbum(selected);
    }
    subScreen_ = PlaylistSubScreen::DEFAULT;
}