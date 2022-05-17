#pragma once
#include "InputBasedAnimation.h"
#include "Level01ContentManager.h"
class ShipAnimation :
	public InputBasedAnimation
{
	static const int DEFAULT_FRAME_STATE;
public:
	ShipAnimation(sf::Sprite& sprite);
	virtual bool init(const Level01ContentManager& contentManager);
	virtual void adjustNextFrame(const Inputs& inputs) override;
	int nbFrameInState;
};

