#pragma once
#include "stdafx.h"
#include "ContentManager.h"
class MenuContentManager : ContentManager
{
public:
	MenuContentManager();
	virtual bool loadContent();

	const sf::Texture& getBackgroundTexture() const;
	const sf::Texture& getMiscTexture() const;
	const sf::Texture& getTitleScreenTexture() const;
	const sf::Font& getMainFont() const;
private:
	sf::Texture backgroundTexture;
	sf::Texture miscTexture;
	sf::Texture titleScreenTexture;
	sf::Font mainFont;
};