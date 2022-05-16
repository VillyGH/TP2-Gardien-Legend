#include "stdafx.h"
#include "Hud.h"
#include <iostream>

Hud::Hud()
{

}

void Hud::initialize(const Level01ContentManager& contentManager)
{
	addScoreText(contentManager);
	addLifeSprite(contentManager);
	addNbLivesRemainingText(contentManager);
	addBonusSprite(contentManager);
	addTimeRemainingBonusText(contentManager);
	addPauseText(contentManager);
}

// Ajout de texte

void Hud::addScoreText(const Level01ContentManager& contentManager)
{
	scoreText.setFont(contentManager.getMainFont());
	scoreText.setCharacterSize(22);
	scoreText.setFillColor(sf::Color::Cyan);
	scoreText.setPosition(scoreText.getLocalBounds().width / 2.0f, Game::GAME_HEIGHT - 50.f);
}

void Hud::addLifeSprite(const Level01ContentManager& contentManager)
{
	lifeSprite.setTexture(contentManager.getMiscTexture());
	lifeSprite.setTextureRect(sf::IntRect(228, 63, 12, 11));
	lifeSprite.setScale(3.0f, 3.0f);
	lifeSprite.setPosition(scoreText.getPosition().x + 350, scoreText.getPosition().y - 5);
}

void Hud::addNbLivesRemainingText(const Level01ContentManager& contentManager)
{
	nbLivesRemainingText.setFont(contentManager.getMainFont());
	nbLivesRemainingText.setCharacterSize(22);
	nbLivesRemainingText.setFillColor(sf::Color::Cyan);
	nbLivesRemainingText.setPosition(lifeSprite.getPosition().x + 50, scoreText.getPosition().y);
}

void Hud::addBonusSprite(const Level01ContentManager& contentManager)
{
	bonusSprite.setTexture(contentManager.getMiscTexture()); 
	bonusSprite.setTextureRect(sf::IntRect(248, 104, 16, 16));
	bonusSprite.setScale(2.5f, 2.5f);
	bonusSprite.setPosition(nbLivesRemainingText.getPosition().x + 150, lifeSprite.getPosition().y);
}

void Hud::addTimeRemainingBonusText(const Level01ContentManager& contentManager)
{
	timeRemainingBonusText.setFont(contentManager.getMainFont());
	timeRemainingBonusText.setCharacterSize(22);
	timeRemainingBonusText.setFillColor(sf::Color::Cyan);
	timeRemainingBonusText.setPosition(bonusSprite.getPosition().x + 50, scoreText.getPosition().y);
}

void Hud::addPauseText(const Level01ContentManager& contentManager)
{
	pauseText.setFont(contentManager.getMainFont());
	pauseText.setCharacterSize(28);
	pauseText.setFillColor(sf::Color::Cyan);
	pauseText.setPosition(Game::GAME_WIDTH / 2.0f - pauseText.getLocalBounds().width / 2.0f, Game::GAME_HEIGHT / 2.0f - pauseText.getLocalBounds().height / 2.0f);
}


// Mise à jour du texte

void Hud::updateScoreText(float score)
{
	const std::string scoreString = "Score : " + std::to_string(int(score));
	scoreText.setString(scoreString);
}

void Hud::updateNbLivesText(float nbLivesRemaining)
{
	//nbLivesRemainingText.setPosition(Game::GAME_WIDTH - nbLivesRemainingText.getLocalBounds().width, nbLivesRemainingText.getLocalBounds().height / 2.0f);
	nbLivesRemainingText.setString(std::to_string((int)nbLivesRemaining));
}

void Hud::updateTimeRemainingBonus(float timeRemainingBonus)
{
	//timeRemainingBonusText.setPosition(Game::GAME_WIDTH - nbLivesRemainingText.getLocalBounds().width, nbLivesRemainingText.getLocalBounds().height / 2.0f);
	timeRemainingBonusText.setString(std::to_string((int)timeRemainingBonus));
}

void Hud::updatePauseText()
{
	const std::string pauseString = "Pause";
	pauseText.setString(pauseString);
}

void Hud::updateGameInfo(float score, float nbLivesRemaining, float timeRemainingBonus)
{
	updateScoreText(score);
	updateNbLivesText(nbLivesRemaining);
	updateTimeRemainingBonus(timeRemainingBonus);
}

// Reset du texte

void Hud::removeGameInfoText()
{
	scoreText.setString("");
	nbLivesRemainingText.setString("");
}

void Hud::removePauseText()
{
	pauseText.setString("");
}


void Hud::draw(sf::RenderWindow& window) const
{
	window.draw(scoreText);
	window.draw(lifeSprite);
	window.draw(nbLivesRemainingText);
	window.draw(bonusSprite);
	window.draw(timeRemainingBonusText);
	window.draw(pauseText);
	window.draw(leaderboardText);
}