#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "animation.hpp"

enum EntityType
{
    PLAYER,
    OBSTACLE,
    COIN,
    PLAIN
};

class Entity: public Animation
{
protected:
    sf::Vector2f movementVector;
    EntityType type = PLAIN;

public:
    Entity();
    EntityType getType();
    void setMovementVector(sf::Vector2f _movementVector);
    sf::Vector2f getMovementVector();
    virtual void sayHello();

};

#endif //ENTITY_H
