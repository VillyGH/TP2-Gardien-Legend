#pragma once
#include "Scene.h"
#include "Inputs.h"
#include "Player.h"
#include "ContentManager.h"
//#include "Bullet.h"
#include "Player.h"
#include "Level01ContentManager.h"
#include "Bullet.h"
#include "EnemyType1.h"
#include <list>
#include "stdafx.h"

class Level01Scene :
	public Scene
{
public:
	static const float TIME_PER_FRAME;
	static const float GAMEPAD_SPEEDRATIO;
	static const float KEYBOARD_SPEED;
	static const float TIME_BETWEEN_FIRE;
	static const float MAX_ENEMIES;
	static const float ENEMY_SPAWN_TIME;
	static const float ENEMY_SPAWN_DISTANCE;
	static const float SPAWN_MARGIN;

public:
	Level01Scene();
	~Level01Scene();
	virtual SceneType update() override;
	void fireEnemyBullet(EnemyType1 enemy);
	Bullet& getAvailableEnemyBullet();
	EnemyType1 spawnEnemy();
	EnemyType1& getAvailableEnemy();
	virtual void draw(sf::RenderWindow& window) const override;
	virtual bool init() override;
	virtual bool uninit() override;
	virtual bool handleEvents(sf::RenderWindow& window) override;
private:
	void fireBullet(const sf::Vector2f& position);
	Inputs inputs;
	Player player;
	sf::Sprite backgroundSprite;
	Level01ContentManager contentManager;
	std::list<EnemyType1> enemies;
	//std::list<Bullet> bullets;
	std::list<Bullet> enemyBullets;
	float timeSinceLastFire;
	sf::Music music;
	float enemySpawnTimer;
};

