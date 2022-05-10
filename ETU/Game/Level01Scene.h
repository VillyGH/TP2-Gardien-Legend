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

class Level01Scene :
	public Scene, public Subscriber
{

public:
	static const float TIME_PER_FRAME;
	static const float GAMEPAD_SPEEDRATIO;
	static const float KEYBOARD_SPEED;
	static const float TIME_BETWEEN_FIRE;
	static const float MAX_NB_STANDARD_ENEMIES;
	static const float MAX_NB_BOSS_ENEMIES;
	static const float MAX_NB_BULLETS;
	static const float STANDARD_ENEMY_SPAWN_TIME;
	static const float BOSS_ENEMY_SPAWN_TIME;
	static const float ENEMY_SPAWN_DISTANCE;
	static const float SPAWN_MARGIN;
	static const float PLAYER_BULLET_DAMAGE;
	static const float NB_FIRED_PLAYER_BULLETS;
	static const float NB_BONUS_FIRED_PLAYER_BULLETS;
	static const float BOSS_SPAWN_KILL_COUNT;
	static const float SCORE_GAINED_ENEMY_KILLED;

public:
	Level01Scene();
	~Level01Scene();
	virtual SceneType update() override;
	bool spawnStandardEnemy();
	bool spawnBoss();
	StandardEnemy& getAvailableStandardEnemy();
	StandardEnemy& getAvailableBossEnemy();
	void addNewBossEnemies();
	void addNewStandardEnemies();
	void fireEnemyBullet(StandardEnemy enemy);
	void fireBossBullet();
	void firePlayerBullet();
	Bullet& getAvailableStandardBullet();
	Bullet& getAvailableEnemyBullet();
	Bullet& getAvailableBossBullet();
	void addNewPlayerBullets();
	void addNewEnemyBullets();
	void addNewBossBullets();
	virtual void draw(sf::RenderWindow& window) const override;
	virtual bool init() override;
	virtual bool uninit() override;
	virtual bool handleEvents(sf::RenderWindow& window) override;
private:
	sf::View view;
	Inputs inputs;
	Player player;
	Boss boss;
	Hud hud;
	sf::Sprite backgroundSprite;
	Level01ContentManager contentManager;
	std::list<StandardEnemy> standardEnemies;
	std::list<Bullet> playerBullets;
	std::list<Bullet> enemyBullets;
	std::list<Bullet> bossBullets;
	float timeSinceLastFire;
	sf::Music music;
	sf::SoundBuffer enemyDeathSound;
	float enemySpawnTimer;
	bool allEnemiesKilled;
	bool gameEnded;
	int score;
	int livesRemaining;
	int bonusTime;
	int nbKills;
	int timer;
	Hud hud;
	bool gameEnded; 
	virtual void notify(Event event, const void* data) override;

};

