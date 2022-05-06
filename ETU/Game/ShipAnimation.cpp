#include "stdafx.h"
#include "ShipAnimation.h"
#include "Inputs.h"

const int ShipAnimation::DEFAULT_FRAME_STATE = 24;

ShipAnimation::ShipAnimation(sf::Sprite& sprite)
    : InputBasedAnimation(sprite)
    , nbFrameInState(DEFAULT_FRAME_STATE)
{

}

bool ShipAnimation::init(const Level01ContentManager& contentManager)
{
    const sf::Texture& texture = contentManager.getMainCharacterTexture();
    frames.push_back(AnimationFrame(texture, sf::IntRect(227, 47, 14, 28)));
    frames.push_back(AnimationFrame(texture, sf::IntRect(246, 47, 18, 29)));
    frames.push_back(AnimationFrame(texture, sf::IntRect(270, 47, 22, 28)));
    frames.push_back(AnimationFrame(texture, sf::IntRect(300, 47, 18, 29)));
    frames.push_back(AnimationFrame(texture, sf::IntRect(324, 47, 14, 28)));
    return true;
}

void ShipAnimation::adjustNextFrame(const Inputs& inputs)
{
    if (inputs.moveFactorX > 0)
        nbFrameInState = std::max(nbFrameInState - 1, 0);
    else if (inputs.moveFactorX < 0)
        nbFrameInState = std::min(nbFrameInState + 1, 2 * DEFAULT_FRAME_STATE + 1);
    else
    {
        if (nbFrameInState > DEFAULT_FRAME_STATE)
            nbFrameInState--;
        else if (nbFrameInState < DEFAULT_FRAME_STATE)
            nbFrameInState++;
    }
    if (nbFrameInState > 40)
        nextFrame = 4;
    else if (nbFrameInState > 30)
        nextFrame = 3;
    else if (nbFrameInState > 20)
        nextFrame = 2;
    else if (nbFrameInState > 10)
        nextFrame = 1;
    else
        nextFrame = 0;
}

