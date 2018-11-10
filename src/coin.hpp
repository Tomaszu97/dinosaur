#ifndef COIN_H
#define COIN_H
#include "entity.hpp"

class Coin: public Entity
{
private:
    int value = 10;

public:
    Coin();
    Coin(int _value);
    int getValue();
    virtual void sayHello();
};

#endif //COIN_H

