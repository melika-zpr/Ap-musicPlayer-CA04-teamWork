#include "InputHandler.h"
#include <iostream>
#include <limits>
#include <algorithm>

#ifdef _WIN32
#include <conio.h>
#endif

char InputHandler::getNonBlockingCharKey() {
#ifdef _WIN32
    if (_kbhit()) {
        char key = static_cast<char>(_getch());
        return std::tolower(key); 
    }
#endif

    return '\0'; 
}

int InputHandler::getIntChoice(const std::string& prompt, int min, int max) {
    char key = getNonBlockingCharKey();
    
    if (key == '\0') {
        return -1; 
    }
    
    if (key == '0') {
        return 0;
    }
    
    if (key >= '1' && key <= '9') {
        int choice = key - '0';
        if (choice >= min && choice <= max) {
            return choice;
        }
    }
    
    
    return -2; 
}

std::string InputHandler::getStringInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    
    #ifdef _WIN32
    while (_kbhit()) {
        _getch();
    }
    #endif
    std::cin.clear();
    std::getline(std::cin, input);
    input = trim(input);
    return input;
}

char InputHandler::getCharKey(const std::string& prompt) {
    if (!prompt.empty()) {
        std::cout << prompt;
    }
    
    char key;
    std::cin >> key;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    return std::tolower(key);
}

void InputHandler::waitForKey(const std::string& message) {
    std::cout << message;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

bool InputHandler::isValidRange(int value, int min, int max) const {
    return (value >= min && value <= max);
}

void InputHandler::clearError() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string InputHandler::trim(const std::string& str) const {
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos) {
        return "";
    }
    
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(start, end - start + 1);
}

