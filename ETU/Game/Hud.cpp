#include "stdafx.h"
#include "Hud.h"
#include <iostream>

Hud::Hud()
{

}

void Hud::initialize(const Level01ContentManager& contentManager)
{
	addScoreText();
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
	leaderboardText.setFont(contentManager.getMainFont());
	leaderboardText.setCharacterSize(64);
	leaderboardText.setFillColor(sf::Color(42, 2, 2, 255));
	leaderboardText.setPosition(Game::GAME_WIDTH / 2.0f - leaderboardText.getLocalBounds().width / 2.0f, Game::GAME_HEIGHT / 2.0f - leaderboardText.getLocalBounds().height / 2.0f);
	leaderboardText.setString(gameOverString);
}


// Mise � jour du texte

void Hud::updateScoreText(int score)
{
	const std::string scoreString = "Score : " + std::to_string(score);
	scoreText.setString(scoreString);
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

void Hud::updateGameInfo(int score, int nbLivesRemaining)
{
	updateScoreText(score);
	updateNbLivesText(nbLivesRemaining);
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


void Hud::draw(sf::RenderWindow& window)  const
{
	window.draw(scoreText);
	window.draw(nbLivesRemainingText);
	window.draw(pauseText);
	window.draw(leaderboardText);
}