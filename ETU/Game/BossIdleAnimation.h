#pragma once
#include "stdafx.h"
#include "CyclicAnimation.h"
class Level01ContentManager;
class BossIdleAnimation :
    public CyclicAnimation
{
    static const float ANIMATION_LENGTH;
public:
    BossIdleAnimation(sf::Sprite& s);
    virtual bool init(const Level01ContentManager& contentManager) override;
};

