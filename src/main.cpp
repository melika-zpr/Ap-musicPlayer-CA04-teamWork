#include "Application.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    try {
        Application app;
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "\u2716 Fatal error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}