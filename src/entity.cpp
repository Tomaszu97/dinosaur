#include "entity.hpp"

Entity::Entity():
movementVector(0.f,0.f)
{
}

EntityType Entity::getType()
{
    return type;
}

void Entity::setMovementVector(sf::Vector2f _movementVector)
{
    movementVector = _movementVector;
}

sf::Vector2f Entity::getMovementVector()
{
    return movementVector;
}

void Entity::sayHello()
{
    std::cout << "Hi! I'm a generic Entity!(background image)" << std::endl;
}
