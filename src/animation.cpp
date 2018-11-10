#include "animation.hpp"
#include <iostream>

Animation::Animation()
{

}

void Animation::setAnimationGrid(int _animationCounterRange, int _animationTrackRange)
{
    animationCounterRange = _animationCounterRange;
    animationTrackRange = _animationTrackRange;

    sf::IntRect temp;
    temp.left = 0;
    temp.top = 0;
    temp.width = (int)floor(getTexture()->getSize().x / animationCounterRange);
    temp.height = (int)floor(getTexture()->getSize().y / animationTrackRange);

    setTextureRect(temp);
    setOrigin(getLocalBounds().width/2, getLocalBounds().height/2);
}



void Animation::updateAnimation()
{
    animationCounter++;
    if(animationCounter >= animationCounterRange)   animationCounter = 0;

    sf::IntRect temp = getTextureRect();
    temp.left = temp.width * animationCounter;
    temp.top = temp.height * animationTrack;

    setTextureRect(temp);
    setOrigin(getLocalBounds().width/2, getLocalBounds().height/2);

}

void Animation::changeTrack(int trackNumber)
{
    if(trackNumber < animationTrackRange && trackNumber >= 0)  animationTrack = trackNumber;
}
