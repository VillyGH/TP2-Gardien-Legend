#pragma once
#include "stdafx.h"
#include "ContentManager.h"
class ScoreboardContentManager : public ContentManager
{
public:
	ScoreboardContentManager();
	virtual bool loadContent();

	const sf::Texture& getBackgroundTexture() const;
private:
	sf::Texture backgroundTexture;
	sf::Texture miscTexture;
	sf::Texture titleScreenTexture;
};



