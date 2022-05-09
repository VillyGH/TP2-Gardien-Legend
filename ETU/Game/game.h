#pragma once
#include "stdafx.h"
#include "Inputs.h"
#include "SceneType.h"


class TitleScene;
class Level01Scene;
class ScoreboardScene;
class Scene;
class Game
{
	typedef TitleScene InitialScene;
public:
	static const unsigned int FRAME_RATE;
	static const unsigned int GAME_WIDTH;
	static const unsigned int GAME_HEIGHT;

public:
	Game(std::string windowName);
	void run();

private:
	bool update();
	void draw(sf::RenderWindow& window) const;
	bool init();
	bool uninit();
	bool handleEvents();

	std::string gameName;
	sf::RenderWindow window;

	// Gestion des scènes
	Scene* getNextScene(SceneType type) const;
	bool popScene(bool initScene = true);
	bool pushScene(Scene* newScene);
	std::stack<Scene*> scenes;
};

