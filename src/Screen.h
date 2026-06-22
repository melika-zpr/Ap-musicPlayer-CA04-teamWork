// Screen.h

#pragma once

class Screen
{

public:
    virtual ~Screen(){}
    virtual void render() = 0;
    virtual void handleInput() = 0;
};