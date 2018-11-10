#include "player.hpp"

Player::Player(sf::Vector2f _startingPosition):
startingPosition(_startingPosition)
{
    type = PLAYER;
    setPosition(startingPosition);
}

void Player::addScore(int _value)
{
    score += _value;
    if(score < 0)   score = 0;
    if(score > highScore)   highScore = score;
}

int Player::getScore()
{
    return score;
}

void Player::setStartingPosition(sf::Vector2f _startingPosition)
{
    startingPosition = _startingPosition;
}

sf::Vector2f Player::getStartingPosition()
{
    return startingPosition;
}

void Player::resetScore()
{
    score = 0;
}

int Player::getHighScore()
{
    return highScore;
}

void Player::setName(std::string _name)
{
    name = _name;
}

std::string Player::getName()
{
    return name;
}

void Player::setSpinning(bool _state)
{
    spinning = _state;
}

bool Player::isSpinning()
{
    return spinning;
}

void Player::sayHello()
{
    std::cout << "Hello, I'm you! A player!" << std::endl;
}
