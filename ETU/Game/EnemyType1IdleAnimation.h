#pragma once
#include "stdafx.h"
#include "CyclicAnimation.h"
class Level01ContentManager;
class EnemyType1IdleAnimation :
    public CyclicAnimation
{
    static const float ANIMATION_LENGTH;
public:
    EnemyType1IdleAnimation(sf::Sprite& s);
    virtual bool init(const Level01ContentManager& contentManager) override;  
};

