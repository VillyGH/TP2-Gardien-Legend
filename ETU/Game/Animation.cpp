#include "stdafx.h"
#include "Animation.h"

Animation::Animation(sf::Sprite& s , float length)
  : sprite(s)
  , lengthInSeconds(length)
  , timeInCurrentState(0)
{

}

void Animation::reset()
{
  timeInCurrentState=0;
}

bool Animation::isOver() const 
{
  return getTimeInCurrentState() >= lengthInSeconds;
}

void Animation::update(float deltaT, const Inputs& inputs)
{
  sprite.setTexture(frames[getNextFrame()].getTexture());
  sprite.setTextureRect(frames[getNextFrame()].getRectangle());
  sprite.setOrigin(sf::Vector2f((float)frames[getNextFrame()].getRectangle().width*0.5f, (float)frames[getNextFrame()].getRectangle().height * 0.5f));
}

float Animation::getTimeInCurrentState() const
{
  return timeInCurrentState;
}