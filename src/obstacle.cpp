#include "obstacle.hpp"

Obstacle::Obstacle()
{
    type = OBSTACLE;
}

void Obstacle::sayHello()
{
    std::cout << "Hi! I'm a cactus!" << std::endl;
}
