#pragma once
class Hud
{
public:
	Hud();
	void draw(sf::RenderWindow& window)  const;
	void initialize(const ContentManager& contentManager);
	void addMenuStartText();
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
	const ContentManager contentManager
	sf::View hudView;
	sf::Text menuStartText;
	sf::Text scoreText;
	sf::Text nbKillsText;
	sf::Text pauseText;
	sf::Text gameOverText;
	sf::Text nbLivesRemainingText;
};

