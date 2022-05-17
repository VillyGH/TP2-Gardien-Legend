#pragma once
#include "Animation.h"
class InputBasedAnimation :
	public Animation
{
public:

	virtual void update(float deltaT, const Inputs& inputs) override;
	virtual unsigned int getNextFrame() const override;
	virtual float getPercentage() const override;
protected:
	InputBasedAnimation(sf::Sprite& s);
	virtual void adjustNextFrame(const Inputs& inputs) = 0;
	unsigned int nextFrame;
};

