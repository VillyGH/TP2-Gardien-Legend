#pragma once
#include "InputBasedAnimation.h"
class ShipAnimation :
    public InputBasedAnimation
{
    static const int DEFAULT_FRAME_STATE;
public:
    ShipAnimation(sf::Sprite& sprite);
    virtual bool init(const ContentManager& contentManager) override;
    virtual void adjustNextFrame(const Inputs& inputs) override;
    int nbFrameInState;
};

