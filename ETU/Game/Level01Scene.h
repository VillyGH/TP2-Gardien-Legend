#pragma once
#include "Scene.h"
#include "Inputs.h"
#include "Player.h"
#include "Level01ContentManager.h"
#include "Bullet.h"
#include "StandardEnemy.h"
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
	static const float MAX_NB_ENEMIES;
	static const float MAX_NB_BULLETS;
	static const float ENEMY_SPAWN_TIME;
	static const float ENEMY_SPAWN_DISTANCE;
	static const float SPAWN_MARGIN;

public:
	// H�rit�es via Scene
	Level01Scene();
	~Level01Scene();
	virtual SceneType update() override;
	StandardEnemy spawnStandardEnemy();
	StandardEnemy spawnBossEnemy();
	StandardEnemy& getAvailableStandardEnemy();
	StandardEnemy& getAvailableBossEnemy();
	void addNewBossEnemies();
	void addNewStandardEnemies();
	void fireEnemyBullet(StandardEnemy enemy);
	void firePlayerBullet();
	Bullet& getAvailableStandardBullet();
	Bullet& getAvailableBossBullet();
	void addNewStandardBullets();
	void addNewBossBullets();
	virtual void draw(sf::RenderWindow& window) const override;
	virtual bool init() override;
	virtual bool uninit() override;
	virtual bool handleEvents(sf::RenderWindow& window) override;
private:
	Inputs inputs;
	Player player;
	sf::Sprite backgroundSprite;
	Level01ContentManager contentManager;
	std::list<StandardEnemy> standardEnemies;
	std::list<StandardEnemy> bossEnemies;
	std::list<Bullet> standardBullets;
	std::list<Bullet> bossBullets;
	float timeSinceLastFire;
	sf::Music music;
	float enemySpawnTimer;
};

