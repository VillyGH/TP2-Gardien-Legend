#include "stdafx.h"
#include "ScoreBoardContentManager.h"


ScoreBoardContentManager::ScoreBoardContentManager()
{
}

bool ScoreBoardContentManager::loadContent()
{

    if (!backgroundTexture.loadFromFile("Assets\\Sprites\\Level01\\SpaceBackground.png"))
        return false;
    else
        backgroundTexture.setRepeated(true);

    if (!miscTexture.loadFromFile("Assets\\Sprites\\Level01\\NES - The Guardian Legend - Miscellaneous.bmp"))
        return false;

    if (!mainFont.loadFromFile("Assets\\Fonts\\Level01\\emulogic.ttf"))
        return false;
    if (!titleScreenTexture.loadFromFile("Assets\\Sprites\\Title\\Title.png"))
        return false;

    return true;
}

const sf::Texture& ScoreBoardContentManager::getBackgroundTexture() const
{
    return backgroundTexture;
}
const sf::Texture& ScoreBoardContentManager::getMiscTexture() const
{
    return miscTexture;
}

const sf::Font& ScoreBoardContentManager::getMainFont() const
{
    return mainFont;
}


const sf::Texture& ScoreBoardContentManager::getTitleScreenTexture() const
{
    return titleScreenTexture;
}