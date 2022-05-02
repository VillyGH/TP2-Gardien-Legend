// ppoulin
// Exercice07


#include "stdafx.h"
#include "InputBasedAnimation.h"



InputBasedAnimation::InputBasedAnimation(sf::Sprite& s)
  : Animation(s, 0)
  , nextFrame(0)
{

}

void InputBasedAnimation::update(float deltaT, const Inputs& inputs)
{
  adjustNextFrame(inputs);
  Animation::update(deltaT, inputs);
}

unsigned int InputBasedAnimation::getNextFrame() const
{  
  return nextFrame;
}

float InputBasedAnimation::getPercentage() const
{
  return 0.0f;
}