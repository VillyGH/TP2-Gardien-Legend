#include "stdafx.h"
#include "ScoreboardContentManager.h"


ScoreboardContentManager::ScoreboardContentManager()
{
}

bool ScoreboardContentManager::loadContent()
{

	if (!backgroundTexture.loadFromFile("Assets\\Sprites\\Level01\\SpaceBackground.png"))
		return false;
	else
		backgroundTexture.setRepeated(true);
	if (!mainFont.loadFromFile("Assets\\Fonts\\Level01\\emulogic.ttf"))
		return false;

	return true;
}

const sf::Texture& ScoreboardContentManager::getBackgroundTexture() const
{
	return backgroundTexture;
}

const sf::Font& ScoreboardContentManager::getMainFont() const
{
	return mainFont;
}