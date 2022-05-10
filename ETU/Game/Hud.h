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
	void addNbLivesRemainingText();
	void addPauseText();
	void addGameOverText(int score);

	void updateScoreText(int score);
	void updateNbLivesText(int nbLivesRemaining);
	void updatePauseText();
	void updateGameInfo(int score, int nbLivesRemaining);

	void removeGameInfoText();
	void removePauseText();
private:
	const ContentManager contentManager;
	sf::View hudView;
	sf::Text scoreText;
	sf::Text pauseText;
	sf::Text leaderboardText;
	sf::Text nbLivesRemainingText;
};

