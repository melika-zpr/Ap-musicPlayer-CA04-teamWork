#pragma once
#include "Screen.h"
#include "Song.h" 
#include <vector>

enum class PlaylistSubScreen { DEFAULT, SORT_MENU, FILTER_MENU };

class PlaylistViewScreen : public Screen {
public:
    void render() override;
    ScreenType handleInput() override;
    ScreenType getType() const override { return ScreenType::PLAYLIST_VIEW; }
    
private:
    Playlist* getActivePlaylist() const;
    void displayPlaylist(const std::vector<Song*>& songs) const;
    void displaySubMenu() const;

    void handleSortMenu();
    void handleFilterMenu(Playlist* playlist);
    void initializeSongs(Playlist* playlist);

    PlaylistSubScreen subScreen_ = PlaylistSubScreen::DEFAULT;
    std::vector<Song*> displayedSongs_;
    Playlist* lastPlaylist_ = nullptr;
};