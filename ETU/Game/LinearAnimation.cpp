#include "stdafx.h"
#include "LinearAnimation.h"


LinearAnimation::LinearAnimation(sf::Sprite& s, float length, bool repeated)
	: Animation(s, length)
{
	this->repeated = repeated;
}

void LinearAnimation::update(float deltaT, const Inputs& inputs)
{
	timeInCurrentState += deltaT;
	if (timeInCurrentState >= lengthInSeconds)
		if (repeated)
			timeInCurrentState = 0;
	Animation::update(deltaT, inputs);
}

unsigned int LinearAnimation::getNextFrame() const
{
	if (isOver())
		return frames.size() - 1;
	float retval = (float)frames.size() * timeInCurrentState / lengthInSeconds;
	return (unsigned int)(retval);
}

float LinearAnimation::getPercentage() const
{
	return (float)getNextFrame() / (float)frames.size();
}