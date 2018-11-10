#include "button.hpp"

Button::Button(sf::RenderWindow &_window, sf::Keyboard::Key _bindKey)
{
    window = &_window;
    bindKey = _bindKey;
}

bool Button::isClicked()
{
    ///bind key check

    if(sf::Keyboard::isKeyPressed(bindKey))
    {
        previousKeyState = 1;
    }
    else
    {
        if(previousKeyState == 1)
        {
            previousKeyState = 0;
            return 1;
        }
    }

    ///falling edge detection
    if(getGlobalBounds().contains((float)sf::Mouse::getPosition(*window).x, (float)sf::Mouse::getPosition(*window).y))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            previousClickState = 1;
            return 0;
        }
        else
        {
            if(previousClickState == 1)
            {
                previousClickState =  0;
                return 1;
            }
            else return 0;
        }
    }

    else
    {
        previousClickState = 0;
        return 0;
    }
}

