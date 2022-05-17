#pragma once
#include "Scene.h"
#include "Inputs.h"
#include "Player.h"
#include "Level01ContentManager.h"
#include "Bullet.h"
#include "StandardEnemy.h"
#include <list>
#include "stdafx.h"
#include "Boss.h"
#include "Subscriber.h"
#include "Hud.h"
#include "GunBonus.h"
#include "LifeBonus.h"

class Level01Scene :
	public Scene, public Subscriber
{

public:
	static const float TIME_PER_FRAME;
	static const float GAMEPAD_SPEEDRATIO;
	static const float KEYBOARD_SPEED;
	static const float MAX_NB_STANDARD_ENEMIES;
	static const float MAX_NB_BOSS_ENEMIES;
	static const float MAX_NB_BULLETS;
	static const float SPAWN_MARGIN;
	static const float SCORE_GAINED_ENEMY_KILLED;
	static const float SCORE_GAINED_BOSS_KILLED;
	static const float LIFE_SCORE_MULTIPLIER;
	static const float TIME_SCORE_MULTIPLIER;
	static const float SCORE_GAINED_BONUS;
	static const float COLLISION_DAMAGE;
	static const float MAX_GUN_BONUS;
	static const float MAX_LIFE_BONUS;

public:
	Level01Scene();
	~Level01Scene();
	virtual SceneType update() override;
	bool spawnStandardEnemy();
	bool spawnBoss();
	void addNewStandardEnemies();
	void fireEnemyBullet(const StandardEnemy enemy);
	void fireBossBullet();
	void firePlayerBullet();
	Bullet& getAvailableStandardBullet();
	Bullet& getAvailableEnemyBullet();
	Bullet& getAvailableBossBullet();
	void addNewPlayerBullets();
	void addNewEnemyBullets();
	void addNewBossBullets();
	void addNewGunBonus();
	GunBonus& getAvailableGunBonus();
	void addNewLifeBonus();
	LifeBonus& getAvailableLifeBonus();
	virtual void draw(sf::RenderWindow& window) const override;
	virtual bool init() override;
	virtual bool uninit() override;
	virtual bool handleEvents(sf::RenderWindow& window) override;
private:

	sf::View view;
	Inputs inputs;
	Player player;
	Boss boss;
	sf::Sprite backgroundSprite;
	Level01ContentManager contentManager;
	std::list<StandardEnemy> standardEnemies;
	std::list<Bullet> playerBullets;
	std::list<Bullet> enemyBullets;
	std::list<Bullet> bossBullets;
	std::list<GunBonus> gunBonus;
	std::list<LifeBonus> lifeBonus;

	float gameTime;
	float timeSinceLastFire;
	sf::Music music;
	float enemySpawnTimer;
	bool gameEnded;
	bool scoreBoardCalled;
	float score;
	int nbKills;
	Hud hud;
	sf::Text scoreText;
	bool isPaused;

	virtual void notify(Event event, const void* data) override;
};

