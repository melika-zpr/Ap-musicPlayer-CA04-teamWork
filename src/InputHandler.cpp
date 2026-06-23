#include "InputHandler.h"

#include <iostream>


int InputHandler::getInt()
{
    int value;


    while(!(std::cin >> value))
    {
        std::cin.clear();

        std::cin.ignore(
            10000,
            '\n'
        );


        std::cout
        <<"Invalid input. Try again: ";
    }


    return value;
}



std::string InputHandler::getString()
{
    std::string text;

    std::cin.ignore();

    std::getline(
        std::cin,
        text
    );


    return text;
}



char InputHandler::getChar()
{
    char c;

    std::cin >> c;

    return c;
}