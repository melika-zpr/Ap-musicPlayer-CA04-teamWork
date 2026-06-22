#include "InputHandler.h"
#include <iostream>
#include <limits>
#include <algorithm>

int InputHandler::getIntChoice(const std::string& prompt, int min, int max) {
    int choice;
    bool valid = false;
    
    while (!valid) {
        std::cout << prompt;
        std::cin >> choice;
        
        if (std::cin.fail()) {
            clearError();
            std::cout << "❌ Invalid input. Please enter a number." << std::endl;
            continue;
        }
        
        if (isValidRange(choice, min, max)) {
            valid = true;
        } else {
            std::cout << "❌ Invalid choice. Please enter a number between " 
                      << min << " and " << max << "." << std::endl;
        }
    }
    
    return choice;
}

std::string InputHandler::getStringInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
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