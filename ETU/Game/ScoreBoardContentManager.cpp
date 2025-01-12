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
	ContentManager::loadContent();

	return true;
}

const sf::Texture& ScoreboardContentManager::getBackgroundTexture() const
{
	return backgroundTexture;
}