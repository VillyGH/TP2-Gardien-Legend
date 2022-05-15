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

	void updateScoreText(float score);
	void updateNbLivesText(float nbLivesRemaining);
	void updateTimeRemainingBonus(float timeRemainingBonus);
	void updatePauseText();
	void updateGameInfo(float score, float nbLivesRemaining, float timeRemainingBonus);

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

