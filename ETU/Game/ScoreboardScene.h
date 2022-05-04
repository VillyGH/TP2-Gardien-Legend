#pragma once
#include "Scene.h"
#include "ScoreboardContentManager.h"
class ScoreboardScene :
	public Scene
{
public:
	static const float TIME_PER_FRAME;
public:
	ScoreboardScene();
	~ScoreboardScene();
	virtual SceneType update() override;
	virtual void pause()override;
	virtual void unPause() override;
	virtual void draw(sf::RenderWindow& window) const override;
	virtual bool init() override;
	virtual bool uninit() override;
	virtual bool handleEvents(sf::RenderWindow& window) override;
private:
	ScoreboardContentManager contentManager;

	sf::Text leaderboardText;
	sf::Text gameOverText;
	sf::Sprite endGameImage;

	sf::Music scoreboardMusic;

	bool gameEnded;
};



