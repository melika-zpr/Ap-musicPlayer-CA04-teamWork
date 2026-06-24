#include "PlaylistListScreen.h"
#include "Player.h"
#include "Playlist.h"
#include "ConfigManager.h"
#include "UIRenderer.h"
#include "InputHandler.h"
#include <vector>
#include <string>

void PlaylistListScreen::render()
{
    std::vector<UIRenderer::PlaylistInfo> uiPlaylists;

    std::string activePlaylistName = "";
    if (config_ != nullptr)
    {
        activePlaylistName = config_->getActivePlaylist();
    }

    if (playlists_ != nullptr)
    {
        for (const auto &playlist : *playlists_)
        {
            UIRenderer::PlaylistInfo info;
            info.name = playlist.getName();

            info.songCount = static_cast<int>(playlist.getSongs().size());

            info.isActive = (info.name == activePlaylistName);

            uiPlaylists.push_back(info);
        }
    }

    ui_->printPlaylistList(uiPlaylists);
}

ScreenType PlaylistListScreen::handleInput()
{
    int maxChoice = (playlists_ != nullptr) ? static_cast<int>(playlists_->size()) : 0;
    int choice = input_->getIntChoice("", 0, maxChoice);

    if (choice == -1)
    {
        return ScreenType::PLAYLIST_LIST;
    }

    if (choice == -2)
    {
        ui_->printMessage(" \u2716 Invalid choice. Please try again.");
        return ScreenType::PLAYLIST_LIST;
    }

    if (choice == 0)
    {
        return ScreenType::MAIN_MENU;
    }

    int index = choice - 1;
    if (playlists_ != nullptr && index >= 0 && index < maxChoice)
    {
        Playlist *selected = &(*playlists_)[index];
        if (player_ != nullptr)
        {
            player_->stop();
            player_->loadPlaylist(selected);

            //player_->play();

            if (config_ != nullptr)
            {
                config_->setActivePlaylist(selected->getName());
                config_->save();
            }
        }
    }
    this->render();
    return ScreenType::PLAYLIST_LIST;
}