#pragma once
#include "Level01ContentManager.h"
#include "game.h"
class Hud
{
public:
	Hud();
	void draw(sf::RenderWindow& window)  const;
	void initialize(const Level01ContentManager& contentManager);
	void addScoreText();
	void addNbKillsText();
	void addNbLivesRemainingText();
	void addPauseText();
	void addGameOverText(int score);

	void updateScoreText(int score);
	void updateNbKillsText(int nbKills);
	void updateNbLivesText(int nbLivesRemaining);
	void updatePauseText();
	void updateGameInfo(int score, int nbKills, int nbLivesRemaining);

	void removeMenuStartText();
	void removeGameInfoText();
	void removePauseText();
private:
	const ContentManager contentManager;
	sf::View hudView;
	sf::Text menuStartText;
	sf::Text scoreText;
	sf::Text nbKillsText;
	sf::Text pauseText;
	sf::Text leaderboardText;
	sf::Text nbLivesRemainingText;
};

