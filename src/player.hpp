#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "entity.hpp"

class Player: public Entity
{
private:
    int highScore = 0;
    int score = 0;
    std::string name = "DINO";
    sf::Vector2f startingPosition;
    bool spinning = 0;

public:
    Player(sf::Vector2f _startingPosition);
    void setStartingPosition(sf::Vector2f _startingPosition);
    sf::Vector2f getStartingPosition();
    void setName(std::string _name);
    std::string getName();
    void addScore(int _value);
    void resetScore();
    int getScore();
    int getHighScore();
    void setSpinning(bool _state);
    bool isSpinning();
    virtual void sayHello();
};

#endif //PLAYER_H
