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
	static const float COLLISION_DAMAGE;
	static const float ENEMY_BULLETS_PER_SHOT;
	static const float MAX_GUN_BONUS;
	static const float MAX_LIFE_BONUS;

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
	void addNewGunBonus();
	GunBonus& getAvailableGunBonus();
	virtual void draw(sf::RenderWindow& window) const override;
	virtual bool init() override;
	virtual bool uninit() override;
	virtual bool handleEvents(sf::RenderWindow& window) override;
private:
	virtual void notify(Event event, const void* data) override;

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
	float timeSinceLastFire;
	sf::Music music;
	sf::SoundBuffer enemyDeathSound;
	float enemySpawnTimer;
	bool allEnemiesKilled;
	bool gameEnded;
	int score;
	int livesRemaining;
	int nbKills;
	int timer;
	Hud hud;
	sf::Text scoreText;
	virtual void notify(Event event, const void* data) override;

};

