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
	static const int NB_INITIAL_PLAYERS;
	static const int MAX_NB_CHARS_INITIALS;
public:
	ScoreboardScene();
	~ScoreboardScene();
	void fillPlayerStatsWithRandomValues(PlayerStats stats[MAX_NB_PLAYERS_LEADERBOARD]);
	virtual SceneType update() override;
	virtual void draw(sf::RenderWindow& window) const override;
	virtual bool init() override;
	void setScoreText();
	void saveStats();
	bool writeToFile(const PlayerStats stats[ScoreboardScene::MAX_NB_PLAYERS_LEADERBOARD]);
	bool readFromFile(const PlayerStats stats[ScoreboardScene::MAX_NB_PLAYERS_LEADERBOARD]);
	void setInitialsText();
	void addInitialsText(const char intial);
	void removeInitialsText();
	void setLeaderboardText();
	void setGameOverText();
	void setEnterNameText();
	void changeEnterNameText();
	virtual bool uninit() override;
	virtual bool handleEvents(sf::RenderWindow& window) override;
private:
	ScoreboardContentManager contentManager;
	PlayerStats stats[MAX_NB_PLAYERS_LEADERBOARD];
	sf::Sprite backgroundSprite;
	sf::Text leaderboardText;
	sf::Text gameOverText;
	sf::Text enterNameText;
	sf::Text initialsText;
	sf::Text scoresText;
	int currentInitials;
	int scoreIndex;
	int nameIndex;
	bool lockedInScore;
	std::string newInitials;
	bool hasExited;
	bool canExit;
};



