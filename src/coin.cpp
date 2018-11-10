#include "coin.hpp"

Coin::Coin()
{
    type = COIN;
}

Coin::Coin(int _value):
value(_value)
{
    type = COIN;
}

int Coin::getValue()
{
    return value;
}

void Coin::sayHello()
{
    std::cout << "Hello! I'm a coin!" << std::endl;
}
