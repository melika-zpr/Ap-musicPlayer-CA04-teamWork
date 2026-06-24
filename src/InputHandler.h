#pragma once

#include <string>
#include <vector>

class InputHandler {
public:
    InputHandler() = default;
    
    int getIntChoice(const std::string& prompt = "Choice: ", 
                     int min = 0, 
                     int max = 999);
    
    std::string getStringInput(const std::string& prompt = "Enter: ");
    
    char getCharKey(const std::string& prompt = "");
    
    void waitForKey(const std::string& message = "Press Enter to continue...");
    
    bool isValidRange(int value, int min, int max) const;
    
    void clearError();
    char getNonBlockingCharKey();
    
private:
    std::string trim(const std::string& str) const;
};