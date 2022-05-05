#include "stdafx.h"
#include "TitleSceneContentManager.h"


TitleSceneContentManager::TitleSceneContentManager()
{
}

TitleSceneContentManager& TitleSceneContentManager::getInstance()
{
    static TitleSceneContentManager instance;
    return instance;
}

bool TitleSceneContentManager::loadContent()
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
const sf::Texture& TitleSceneContentManager::getBackgroundTexture() const
{
    return backgroundTexture;
}
const sf::Texture& TitleSceneContentManager::getMiscTexture() const
{
    return miscTexture;
}
const sf::Font& TitleSceneContentManager::getMainFont() const
{
    return mainFont;
}
const sf::Texture& TitleSceneContentManager::getTitleScreenTexture() const
{
    return titleScreenTexture;
}