#pragma once
#include "Scene.h"
#include "ScoreboardContentManager.h"
#include "PlayerStats.h"
#include "game.h"
#include <stdlib.h>
#include <fstream>
class ScoreboardScene :
	public Scene
{
public:
	static const float TIME_PER_FRAME;
	static const std::string PATH_TO_BIN_FILE;
	static const int MAX_NB_PLAYERS_LEADERBOARD = 5;
public:
	ScoreboardScene();
	~ScoreboardScene();
	virtual SceneType update() override;
	virtual void pause()override;
	virtual void unPause() override;
	virtual void draw(sf::RenderWindow& window) const override;
	virtual bool init() override;
	void setScoreText();
	void saveStats(std::string initials);
	bool writeToFile(const PlayerStats stats[ScoreboardScene::MAX_NB_PLAYERS_LEADERBOARD]);
	bool readFromFile(PlayerStats stats[ScoreboardScene::MAX_NB_PLAYERS_LEADERBOARD]);
	void setInitialsText();
	void addInitialsText(char intial);
	void removeInitialsText();
	void setLeaderboardText();
	void setGameOverText();
	virtual bool uninit() override;
	virtual bool handleEvents(sf::RenderWindow& window) override;
private:
	ScoreboardContentManager contentManager;

	sf::Text leaderboardText;
	sf::Text gameOverText;
	sf::Text initialsText;
	sf::Text scoresText;
	sf::Sprite endGameImage;

	PlayerStats stats[MAX_NB_PLAYERS_LEADERBOARD];

	bool hasExited;
};



