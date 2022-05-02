#pragma once
#include "Scene.h"
#include "Inputs.h"
//#include "Player.h"
#include "ContentManager.h"
//#include "Bullet.h"
#include <list>
#include "stdafx.h"

class Level01 :
	public Scene
{
public:
	static const float TIME_PER_FRAME;
	static const float GAMEPAD_SPEEDRATIO;
	static const float KEYBOARD_SPEED;
	static const float TIME_BETWEEN_FIRE;
	static const float MAX_ENEMIES;
public:
	// Héritées via Scene
	Level01();
	~Level01();
	virtual SceneType update() override;
	virtual void draw(sf::RenderWindow& window) const override;
	virtual bool init() override;
	virtual bool uninit() override;
	virtual bool handleEvents(sf::RenderWindow& window) override;
private:
	void fireBullet(const sf::Vector2f& position);
	Inputs inputs;
	//Player player;
	sf::Sprite backgroundSprite;
	ContentManager contentManager;
	//std::list<LargeEnemy> enemies;
	//std::list<Bullet> bullets;
	float timeSinceLastFire;
};

