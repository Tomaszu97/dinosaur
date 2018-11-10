#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <math.h>

class Animation : public sf::Sprite
{
private:
    int animationCounter = 0;
    int animationCounterRange = 0;
    int animationTrack = 0;
    int animationTrackRange = 0;

public:
    Animation();
    void setAnimationGrid(int _animationCounterRange, int _animationTrackRange);
    void updateAnimation();
    void changeTrack(int trackNumber);

};

#endif // ANIMATION_H
