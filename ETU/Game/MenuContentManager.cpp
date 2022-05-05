#include "stdafx.h"
#include "MenuContentManager.h"


MenuContentManager::MenuContentManager()
{
}

bool MenuContentManager::loadContent()
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
const sf::Texture& MenuContentManager::getBackgroundTexture() const
{
    return backgroundTexture;
}
const sf::Texture& MenuContentManager::getMiscTexture() const
{
    return miscTexture;
}
const sf::Font& MenuContentManager::getMainFont() const
{
    return mainFont;
}
const sf::Texture& MenuContentManager::getTitleScreenTexture() const
{
    return titleScreenTexture;
}