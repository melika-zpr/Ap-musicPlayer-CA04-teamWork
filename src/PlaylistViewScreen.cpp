#include "PlaylistViewScreen.h"
#include "Player.h"
#include "Playlist.h"
#include "Song.h"
#include "UIRenderer.h"
#include "InputHandler.h"
#include <algorithm>
#include <set>
#include <iostream>

Playlist *PlaylistViewScreen::getActivePlaylist() const
{
    if (player_ == nullptr)
        return nullptr;
    return player_->getCurrentPlaylist();
}

void PlaylistViewScreen::initializeSongs(Playlist *playlist)
{
    if (playlist != nullptr)
    {
        displayedSongs_ = playlist->getSongs();
        lastPlaylist_ = playlist;
    }
}

void PlaylistViewScreen::render()
{
    Playlist *playlist = getActivePlaylist();

    if (playlist != lastPlaylist_)
    {
        initializeSongs(playlist);
        subScreen_ = PlaylistSubScreen::DEFAULT;
    }

    if (playlist == nullptr || playlist->isEmpty())
    {
        ui_->printPlaylistView("None", {});
        return;
    }

    if (subScreen_ == PlaylistSubScreen::DEFAULT)
    {
        std::vector<UIRenderer::TrackInfo> uiTracks;
        Song *currentSong = (player_ != nullptr) ? player_->getCurrentSong() : nullptr;

        for (Song *song : displayedSongs_)
        {
            if (!song)
                continue;
            UIRenderer::TrackInfo track;
            track.title = song->getTitle();
            track.artist = song->getArtist();
            track.isCurrent = (currentSong != nullptr && currentSong->getFilePath() == song->getFilePath());
            uiTracks.push_back(track);
        }

        std::string displayName = playlist->getName() + " (" + std::to_string(displayedSongs_.size()) + ")";
        ui_->printPlaylistView(displayName, uiTracks);
    }
}


ScreenType PlaylistViewScreen::handleInput() {
    Playlist* playlist = getActivePlaylist();
    if (playlist == nullptr || playlist->isEmpty()) {
        char key = input_->getNonBlockingCharKey();
        if (key == '0') return ScreenType::MAIN_MENU;
        return ScreenType::PLAYLIST_VIEW;
    }

    if (subScreen_ == PlaylistSubScreen::DEFAULT) {
        char key = input_->getNonBlockingCharKey();
        if (key == '\0') return ScreenType::PLAYLIST_VIEW;
        
        if (key == '0') {
            return ScreenType::MAIN_MENU;
        } else if (key == 's') {
            handleSortMenu(); 
        } else if (key == 'f') {
            handleFilterMenu(playlist); 
        } else if (key == '/') {
            std::string query = input_->getStringInput("\n  \033[97mEnter search query: \033[0m");
            displayedSongs_ = playlist->search(query);
            
            std::system("cls");
            this->render();
        } else if (key == 'c') {
            initializeSongs(playlist); 
            
            std::system("cls");
            this->render();
        } else  if (key == 'p') { 
            std::string numStr = input_->getStringInput("\n  \033[97mEnter track number to play: \033[0m");
            try {
                int trackNumber = std::stoi(numStr);
                int index = trackNumber - 1;
                
                if (index >= 0 && index < static_cast<int>(displayedSongs_.size()) && player_) {
                    int origIndex = playlist->indexOf(displayedSongs_[index]);
                    if (origIndex != -1) {
                        player_->stop();
                        player_->setCurrentIndex(origIndex);
                        player_->play();
                    }
                }
            } catch (...) {}
            
            std::system("cls");
            this->render();
        }
    }
    return ScreenType::PLAYLIST_VIEW;
}

void PlaylistViewScreen::handleSortMenu() {
    std::cout << "\n  \033[38;5;220mSort by:\033[0m 1.Title  2.Artist  3.Album  4.Year  5.Duration\n";
    std::cout << "  \033[38;5;244m(Add '-' for descending, e.g., '4-'. 0 to Cancel)\033[0m\n";
    
    std::string choiceStr = input_->getStringInput("\n  Sort choice: ");

    if (choiceStr == "0" || choiceStr.empty()) {
        subScreen_ = PlaylistSubScreen::DEFAULT;
        std::system("cls");
        this->render(); 
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

    std::system("cls");
    this->render();
}

void PlaylistViewScreen::handleFilterMenu(Playlist* playlist) {
    // جدول بالا می‌ماند و این منو زیر آن ظاهر می‌شود
    std::cout << "\n  \033[38;5;220mFilter by:\033[0m 1. Artist   2. Album   0. Cancel\n";
    
    std::string choiceStr = input_->getStringInput("\n  Choice: ");
    int filterType = 0;
    try { filterType = std::stoi(choiceStr); } catch(...) {}
    
    if (filterType != 1 && filterType != 2) {
        subScreen_ = PlaylistSubScreen::DEFAULT;
        std::system("cls");
        this->render();
        return;
    }

    std::set<std::string> uniqueItems;
    for (Song* song : playlist->getSongs()) {
        if (!song) continue;
        uniqueItems.insert(filterType == 1 ? song->getArtist() : song->getAlbum());
    }

    std::vector<std::string> itemsList(uniqueItems.begin(), uniqueItems.end());
    
    std::cout << "\n  \033[38;5;114mAvailable Options:\033[0m\n";
    for (size_t i = 0; i < itemsList.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << itemsList[i] << "\n";
    }

    std::string itemChoiceStr = input_->getStringInput("\n  Select option (0 to cancel): ");
    int itemChoice = 0;
    try { itemChoice = std::stoi(itemChoiceStr); } catch(...) {}

    if (itemChoice > 0 && itemChoice <= static_cast<int>(itemsList.size())) {
        std::string selected = itemsList[itemChoice - 1];
        displayedSongs_ = (filterType == 1) ? playlist->filterByArtist(selected) : playlist->filterByAlbum(selected);
    }
    subScreen_ = PlaylistSubScreen::DEFAULT;

    std::system("cls");
    this->render();
}