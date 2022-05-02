#pragma once
#include "stdafx.h"
class ScoreBoardContentManager
{
public:
	ScoreBoardContentManager();
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



