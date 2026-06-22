#include "UIRenderer.h"

#include <iostream>


void UIRenderer::clear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}



void UIRenderer::showTitle(
    const std::string& title
)
{
    std::cout
    << "\n========== "
    << title
    << " ==========\n";
}



void UIRenderer::print(
    const std::string& text
)
{
    std::cout
    << text
    << std::endl;
}



void UIRenderer::line()
{
    std::cout
    <<"----------------------\n";
}