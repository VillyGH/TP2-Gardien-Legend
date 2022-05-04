#include "stdafx.h"
#include "Hud.h"
#include "ContentManager.h"
#include "game.h"
#include <iostream>

Hud::Hud()
{

}

void Hud::initialize(const ContentManager& contentManager)
{
	hudView = sf::View(sf::FloatRect(0, 0, (float)Game::GAME_WIDTH, (float)Game::GAME_HEIGHT));
	addMenuStartText();
	addScoreText();
	addNbKillsText();
	addNbLivesRemainingText();
	addPauseText();
}

// Ajout de texte



void Hud::addScoreText()
{
	scoreText.setFont(contentManager.getMainFont());
	scoreText.setCharacterSize(16);
	scoreText.setFillColor(sf::Color::Cyan);
	scoreText.setPosition(scoreText.getLocalBounds().width, scoreText.getLocalBounds().height);
}

void Hud::addNbKillsText()
{
	nbKillsText.setFont(contentManager.getMainFont());
	nbKillsText.setCharacterSize(16);
	nbKillsText.setFillColor(sf::Color::Cyan);
}

void Hud::addNbLivesRemainingText()
{
	nbLivesRemainingText.setFont(contentManager.getMainFont());
	nbLivesRemainingText.setCharacterSize(16);
	nbLivesRemainingText.setFillColor(sf::Color::Cyan);
}

void Hud::addPauseText()
{
	pauseText.setFont(contentManager.getMainFont());
	pauseText.setCharacterSize(24);
	pauseText.setFillColor(sf::Color::Cyan);
	pauseText.setPosition(Game::GAME_WIDTH / 2.0f - pauseText.getLocalBounds().width / 2.0f, Game::GAME_HEIGHT / 2.0f - pauseText.getLocalBounds().height / 2.0f);
}

void Hud::addGameOverText(int score)
{
	const std::string gameOverString = "Game Over ! Votre score : " + std::to_string(score);
	gameOverText.setFont(contentManager.getMainFont());
	gameOverText.setCharacterSize(64);
	gameOverText.setFillColor(sf::Color(42,2,2,255));
	gameOverText.setPosition(Game::GAME_WIDTH / 2.0f - gameOverText.getLocalBounds().width / 2.0f, Game::GAME_HEIGHT / 2.0f - gameOverText.getLocalBounds().height / 2.0f);
	gameOverText.setString(gameOverString);
}


// Mise à jour du texte

void Hud::updateScoreText(int score) 
{
	const std::string scoreString = "Score : " + std::to_string(score);
	scoreText.setString(scoreString);
}

void Hud::updateNbKillsText(int numberKills)
{
	const std::string numberKillsString = "Kills : " + std::to_string(numberKills);
	nbKillsText.setString(numberKillsString);
	nbKillsText.setPosition(0, nbKillsText.getLocalBounds().height + scoreText.getLocalBounds().height);
}

void Hud::updateNbLivesText(int nbLivesRemaining)
{
	nbLivesRemainingText.setPosition(Game::GAME_WIDTH - nbLivesRemainingText.getLocalBounds().width, nbLivesRemainingText.getLocalBounds().height / 2.0f);
	const std::string nbLivesRemainingString = "Vies restantes : " + std::to_string(nbLivesRemaining);
	nbLivesRemainingText.setString(nbLivesRemainingString);
}

void Hud::updatePauseText()
{
	const std::string pauseString = "Pause";
	pauseText.setString(pauseString);
}

void Hud::updateGameInfo(int score, int nbKills, int nbLivesRemaining) 
{
	updateScoreText(score);
	updateNbKillsText(nbKills);
	updateNbLivesText(nbLivesRemaining);
}


// Reset du texte

void Hud::removeMenuStartText()
{
	menuStartText.setString("");
}

void Hud::removeGameInfoText()
{
	scoreText.setString("");
	nbKillsText.setString("");
	nbLivesRemainingText.setString("");
}

void Hud::removePauseText()
{
	pauseText.setString("");
}


void Hud::draw(sf::RenderWindow& window)  const
{
  window.setView(hudView);
  window.draw(menuStartText);
  window.draw(scoreText);
  window.draw(nbKillsText);
  window.draw(nbLivesRemainingText);
  window.draw(pauseText);
  window.draw(gameOverText);
}