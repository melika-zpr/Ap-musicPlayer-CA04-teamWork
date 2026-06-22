#pragma once

#include <string>


class UIRenderer
{

public:

    void clear();


    void showTitle(
        const std::string& title
    );


    void print(
        const std::string& text
    );


    void line();

};