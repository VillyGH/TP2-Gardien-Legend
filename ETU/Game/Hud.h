#pragma once
#include "Level01ContentManager.h"
#include "game.h"
class Hud
{
public:
	Hud();
	void draw(sf::RenderWindow& window)  const;
	void initialize(const Level01ContentManager& contentManager);
	void addScoreText(const Level01ContentManager& contentManager);
	void addLifeSprite(const Level01ContentManager& contentManager);
	void addNbLivesRemainingText(const Level01ContentManager& contentManager);
	void addBonusSprite(const Level01ContentManager& contentManager);
	void addTimeRemainingBonusText(const Level01ContentManager& contentManager);
	void addPauseText(const Level01ContentManager& contentManager);

	void updateScoreText(int score);
	void updateNbLivesText(int nbLivesRemaining);
	void updateTimeRemainingBonus(int timeRemainingBonus);
	void updatePauseText();
	void updateGameInfo(int score, int nbLivesRemaining, int timeRemainingBonus);

	void removeGameInfoText();
	void removePauseText();
private:
	sf::View hudView;
	sf::Text scoreText;
	sf::Sprite lifeSprite;
	sf::Text nbLivesRemainingText;
	sf::Sprite bonusSprite;
	sf::Text timeRemainingBonusText;
	sf::Text leaderboardText;
	sf::Text pauseText;
};

