#include "Application.h"

int main() {
    Application app;
    
    app.init();
    app.run();
    app.shutdown();
    
    return 0;
}