#pragma once
#include "stdafx.h"
#include "CyclicAnimation.h"
class Level01ContentManager;
class StandardEnemyIdleAnimation :
	public CyclicAnimation
{
public:
	static const float ANIMATION_LENGTH;
	StandardEnemyIdleAnimation(sf::Sprite& s);
	virtual bool init(const Level01ContentManager& contentManager) override;
};

