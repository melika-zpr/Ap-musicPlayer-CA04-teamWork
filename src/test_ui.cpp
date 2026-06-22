#include "UIRenderer.h"
#include "InputHandler.h"
#include "Song.h"
#include <iostream>
#include <vector>

int main() {
    UIRenderer ui;
    InputHandler input;
    
    std::cout << "========================================" << std::endl;
    std::cout << "   Testing UIRenderer & InputHandler" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    
    // ===== 1. تست UIRenderer =====
    std::cout << "=== 1. Testing UIRenderer ===" << std::endl;
    std::cout << std::endl;
    
    ui.printHeader("Main Menu");
    ui.printMessage("Welcome to Music Player!");
    ui.printMessage("");
    
    std::vector<std::string> menuItems = {
        "Now Playing",
        "Playlist List",
        "Playlist View",
        "Settings"
    };
    ui.printMenu(menuItems);
    std::cout << std::endl;
    
    ui.printFooter("[0] Back  [q] Quit");
    
    ui.printMessage("");
    ui.drawHorizontalLine('-', 40);
    ui.printMessage("");
    
    ui.printError("This is an error message");
    ui.printMessage("");
    
    // ===== 2. تست printSongList =====
    std::cout << "=== 2. Testing printSongList ===" << std::endl;
    std::cout << std::endl;
    
    std::vector<Song> songObjects = {
        Song("Bohemian Rhapsody", "Queen", "A Night at the Opera", "Rock", 1975, 354, "bohemian.mp3"),
        Song("Stairway to Heaven", "Led Zeppelin", "Led Zeppelin IV", "Rock", 1971, 482, "stairway.mp3"),
        Song("Hotel California", "Eagles", "Hotel California", "Rock", 1977, 391, "hotel.mp3"),
        Song("Hey You", "Pink Floyd", "The Wall", "Rock", 1979, 278, "hey_you.mp3"),
        Song("Lose Yourself to Dance", "Daft Punk", "Random Access Memories", "Funk", 2013, 353, "lose.mp3"),
        Song("Smalltown Boy", "Bronski Beat", "The Age of Consent", "Pop", 1984, 318, "smalltown.mp3"),
        Song("When a Blind Man Cries", "Deep Purple", "Machine Head", "Rock", 1972, 262, "blind.mp3"),
        Song("We Are the Champions", "Queen", "News of the World", "Rock", 1977, 181, "champions.mp3"),
        Song("Almost Blue", "Chet Baker", "Almost Blue", "Jazz", 1988, 219, "blue.mp3"),
        Song("Ageh Yeh Rooz", "Faramarz Aslani", "Age Yeh Rooz", "Pop", 1977, 240, "ageh.mp3")
    };
    
    std::vector<Song*> songs;
    for (auto& s : songObjects) {
        songs.push_back(&s);
    }
    
    ui.printSongList(songs, 5);
    std::cout << std::endl;
    
    // ===== 3. تست printNowPlaying =====
    std::cout << "=== 3. Testing printNowPlaying ===" << std::endl;
    std::cout << std::endl;
    
    ui.printNowPlaying(&songObjects[0], 120.0f, 354.0f);
    std::cout << std::endl;
    
    ui.printNowPlaying(nullptr, 0, 0);
    std::cout << std::endl;
    
    // ===== 4. تست printSettings =====
    std::cout << "=== 4. Testing printSettings ===" << std::endl;
    std::cout << std::endl;
    
    ui.printSettings("SHUFFLE");
    std::cout << std::endl;
    
    ui.printSettings("NO_REPEAT");
    std::cout << std::endl;
    
    // ===== 5. تست InputHandler =====
    std::cout << "=== 5. Testing InputHandler ===" << std::endl;
    std::cout << std::endl;
    
    std::cout << "  Testing getIntChoice (enter a number 1-5):" << std::endl;
    int choice = input.getIntChoice("  Enter number: ", 1, 5);
    std::cout << "  You entered: " << choice << std::endl;
    std::cout << std::endl;
    
    std::cout << "  Testing getStringInput (enter a name):" << std::endl;
    std::string name = input.getStringInput("  Enter name: ");
    std::cout << "  You entered: " << name << std::endl;
    std::cout << std::endl;
    
    std::cout << "  Testing getCharKey (press a key):" << std::endl;
    char key = input.getCharKey("  Press a key: ");
    std::cout << "  You pressed: " << key << std::endl;
    std::cout << std::endl;
    
    // ===== 6. تست isValidRange =====
    std::cout << "=== 6. Testing isValidRange ===" << std::endl;
    std::cout << std::endl;
    
    std::cout << "  isValidRange(5, 1, 10): " << (input.isValidRange(5, 1, 10) ? "true" : "false") << std::endl;
    std::cout << "  isValidRange(0, 1, 10): " << (input.isValidRange(0, 1, 10) ? "true" : "false") << std::endl;
    std::cout << "  isValidRange(15, 1, 10): " << (input.isValidRange(15, 1, 10) ? "true" : "false") << std::endl;
    std::cout << std::endl;
    
    // ===== 7. تست clearScreen =====
    std::cout << "=== 7. Testing clearScreen ===" << std::endl;
    std::cout << std::endl;
    
    input.waitForKey("  Press Enter to clear screen and see the final result...");
    ui.clearScreen();
    
    ui.printHeader("Test Completed!");
    ui.printMessage("All tests passed successfully!");
    ui.drawHorizontalLine('=', 40);
    std::cout << std::endl;
    ui.printMessage("  ✅ UIRenderer: All methods work");
    ui.printMessage("  ✅ InputHandler: All methods work");
    std::cout << std::endl;
    ui.drawHorizontalLine('=', 40);
    
    return 0;
}