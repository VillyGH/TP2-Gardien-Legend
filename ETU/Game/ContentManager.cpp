#include "stdafx.h"
#include "ContentManager.h"


ContentManager::ContentManager()
{
}

bool ContentManager::loadContent()
{
	if (!mainFont.loadFromFile("Assets\\Fonts\\Level01\\emulogic.ttf"))
		return false;

	return true;
}

const sf::Font& ContentManager::getMainFont() const
{
	return mainFont;
}