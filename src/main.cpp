#include "UIRenderer.h"
#include "InputHandler.h"

#include <iostream>


int main()
{

    std::cout 
    << "===== UIRenderer Test =====\n\n";


    UIRenderer ui;


    ui.clear();


    ui.showTitle(
        "Terminal Music Player"
    );


    ui.line();


    ui.print(
        "1. Now Playing"
    );

    ui.print(
        "2. Playlists"
    );

    ui.print(
        "3. Settings"
    );


    ui.line();


    std::cout
    << "\n===== InputHandler Test =====\n\n";


    InputHandler input;


    ui.print(
        "Enter menu number:"
    );


    int choice =
        input.getInt();



    std::cout
    << "Selected: "
    << choice
    << std::endl;



    ui.print(
        "UI tools working successfully"
    );


    return 0;
}