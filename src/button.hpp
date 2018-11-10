#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Button: public sf::Sprite
{
public:
    Button(sf::RenderWindow &_window, sf::Keyboard::Key _bindKey = sf::Keyboard::Key::Unknown);
    bool isClicked();

private:
    bool previousClickState = 0;
    bool previousKeyState = 0;
    sf::RenderWindow *window;
    sf::Keyboard::Key bindKey;
};

#endif // BUTTON_H
