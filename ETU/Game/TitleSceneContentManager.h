#pragma once
#include "stdafx.h"
class TitleSceneContentManager
{
public:
	virtual bool loadContent();
	const sf::Texture& getBackgroundTexture() const;
	const sf::Texture& getMiscTexture() const;
	const sf::Texture& getTitleScreenTexture() const;
	const sf::Font& getMainFont() const;

	static TitleSceneContentManager& getInstance();

private:
	TitleSceneContentManager();

	sf::Texture backgroundTexture;
	sf::Texture miscTexture;
	sf::Texture titleScreenTexture;
	sf::Font mainFont;
};



