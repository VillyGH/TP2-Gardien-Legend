#include "stdafx.h"
#include "Level01Scene.h"
#include "game.h"
#include "CharacterType.h"
#include "Level01ContentManager.h"
#include "Event.h"
#include "Publisher.h"
#include <iostream>
#include "GunBonus.h"

const float Level01Scene::TIME_PER_FRAME = 1.0f / (float)Game::FRAME_RATE;
const float Level01Scene::GAMEPAD_SPEEDRATIO = 40.0f;
const float Level01Scene::KEYBOARD_SPEED = 0.1f;
const float Level01Scene::MAX_NB_STANDARD_ENEMIES = 15;
const float Level01Scene::MAX_NB_BOSS_ENEMIES = 3;
const float Level01Scene::MAX_NB_BULLETS = 30;
const float Level01Scene::SPAWN_MARGIN = -50;
const float Level01Scene::COLLISION_DAMAGE = 5;
const float Level01Scene::SCORE_GAINED_ENEMY_KILLED = 1000;
const float Level01Scene::SCORE_GAINED_BOSS_KILLED = 250;

const float Level01Scene::SCORE_GAINED_BONUS = 250;
const float Level01Scene::MAX_GUN_BONUS = 5;
const float Level01Scene::MAX_LIFE_BONUS = 5;

Level01Scene::Level01Scene()
	: Scene(SceneType::TITLE_SCENE)
	, enemySpawnTimer(0)
	, timeSinceLastFire(0)
	, allEnemiesKilled(false)
	, gameEnded(false)
	, score(0)
	, nbKills(0)
	, isPaused(false)
{
}

Level01Scene::~Level01Scene()
{

}

SceneType Level01Scene::update()
{
	SceneType retval = getSceneType();
	if (!isPaused) {
		static int cptScrollBackground = 0;
		backgroundSprite.setTextureRect(sf::IntRect(0, (int)(0.5f * cptScrollBackground--), Game::GAME_WIDTH, Game::GAME_HEIGHT));

		//Update du joueur
		player.update(TIME_PER_FRAME, inputs);

		if (inputs.playFireSound && timeSinceLastFire >= player.getFireRate())
		{
			firePlayerBullet();
			player.playFireSound();
			timeSinceLastFire = 0;
		}

		timeSinceLastFire += 1.0f / (float)Game::FRAME_RATE;

		//Update des balles du joueur et les collisions
		for (Bullet& b : playerBullets)
		{
			if (b.isActive() && b.update(TIME_PER_FRAME, CharacterType::PLAYER))
				b.deactivate();

			if (b.collidesWith(boss))
			{
				b.deactivate();
				boss.onHit();
			}

			for (StandardEnemy& e : standardEnemies)
			{
				if (b.collidesWith(e))
				{
					b.deactivate();
					e.onHit(Player::PLAYER_BULLET_DAMAGE);
				}
			}
		}

		//Update des enemies et des collisions
		for (StandardEnemy& e : standardEnemies) {
			if (e.isActive())
			{
				if (e.update(TIME_PER_FRAME, inputs))
					e.deactivate();
				if (e.isFiring(TIME_PER_FRAME) && e.isActive())
					fireEnemyBullet(e);
				if (e.collidesWith(player) && !player.isImmune()) {
					e.onHit(COLLISION_DAMAGE);
					player.onHit(COLLISION_DAMAGE);
				}
			}
		}

		enemySpawnTimer += TIME_PER_FRAME;

		if (enemySpawnTimer >= StandardEnemy::STANDARD_ENEMY_SPAWN_TIME && nbKills < Boss::BOSS_SPAWN_KILL_COUNT) {

			spawnStandardEnemy();
			enemySpawnTimer = 0;
		}

		if (nbKills >= Boss::BOSS_SPAWN_KILL_COUNT && !boss.isActive()) //À changer pour un compteur de Enemies Killed
			spawnBoss();

		if (boss.isActive()) {
			boss.update(TIME_PER_FRAME, inputs, player.getPosition());
			if (boss.isFiring())
				fireBossBullet();
			for (Bullet& e : bossBullets) {
				if (e.isActive() && e.update(TIME_PER_FRAME, CharacterType::BOSS))
					e.deactivate();
			}
		}

		for (Bullet& e : enemyBullets)
		{
			if (e.isActive() && e.update(TIME_PER_FRAME, CharacterType::STANDARD_ENEMY))
				e.deactivate();
			if (e.collidesWith(player)) {
				e.deactivate();
				if (!player.isImmune())
					player.onHit(StandardEnemy::ENEMY_BULLET_DAMAGE);
			}

		}

		//Gestion des spawns enemy
		enemySpawnTimer += TIME_PER_FRAME;

		if (enemySpawnTimer >= StandardEnemy::STANDARD_ENEMY_SPAWN_TIME && nbKills < Boss::BOSS_SPAWN_KILL_COUNT) {

			spawnStandardEnemy();
			enemySpawnTimer = 0;
		}

		if (nbKills >= Boss::BOSS_SPAWN_KILL_COUNT && !boss.isActive())
			spawnBoss();

		//Update Boss et collisions avec joueur
		if (boss.isActive()) {
			boss.update(TIME_PER_FRAME, inputs, player.getPosition());
			if (boss.isFiring())
				fireBossBullet();

			if (boss.collidesWith(player))
				player.onHit(player.INITIAL_LIFE_COUNT);

			for (Bullet& e : bossBullets) {
				if (e.isActive() && e.update(TIME_PER_FRAME, CharacterType::BOSS))
					e.deactivate();
				if (e.collidesWith(player) && !player.isImmune()) {
					e.deactivate();
					player.onHit(Boss::BOSS_BULLET_DAMAGE);
				}
			}
		}

		//Update des bonus et de leur collisions
		for (GunBonus& e : gunBonus) {
			if (e.isActive())
			{
				if (e.update(TIME_PER_FRAME, inputs))
					e.deactivate();
				if (e.collidesWith(player)) {
					e.deactivate();
					e.onPickUp();
				}
			}
		}

		for (LifeBonus& e : lifeBonus) {
			if (e.isActive())
			{
				if (e.update(TIME_PER_FRAME, inputs))
					e.deactivate();
				if (e.collidesWith(player)) {
					e.deactivate();
					e.onPickUp();
				}
			}
		}


		/* playerBullets.remove_if([](const GameObject& b) {return !b.isActive(); });
		 standardEnemies.remove_if([](const GameObject& b) {return !b.isActive(); });*/
		hud.addPauseText(contentManager);
		hud.removePauseText();
		hud.updateGameInfo(score, player.getLivesRemaining(), player.getGunBonusTimer());
	} else {
		hud.updatePauseText();
	}
	if (gameEnded)
		retval = SceneType::SCOREBOARD_SCENE;

	return retval;
}


#pragma region Enemy
void Level01Scene::addNewStandardEnemies() {
	for (size_t i = 0; i < MAX_NB_STANDARD_ENEMIES; i++)
	{
		StandardEnemy enemy;
		enemy.init(contentManager);
		standardEnemies.push_back(enemy);
	}
}

bool Level01Scene::spawnStandardEnemy()
{
	for (StandardEnemy& enemy : standardEnemies) {
		if (!enemy.isActive()) {
			enemy.activate();
			enemy.setPosition((rand() % Game::GAME_WIDTH - SPAWN_MARGIN), StandardEnemy::ENEMY_SPAWN_DISTANCE);
			return false;
		}
	}
	return true;
}

bool Level01Scene::spawnBoss()
{
	boss.activate();
	return true;
}


#pragma endregion

#pragma region Bullet
void Level01Scene::fireEnemyBullet(StandardEnemy enemy)
{
		Bullet& b = getAvailableEnemyBullet();
		b.setPosition(enemy.getPosition().x - enemy.getTextureRect().width / 4, enemy.getPosition().y);
		Bullet& b2 = getAvailableEnemyBullet();
		b2.setPosition(enemy.getPosition().x + enemy.getTextureRect().width / 4, enemy.getPosition().y);
}

void Level01Scene::fireBossBullet()
{
	Bullet& b = getAvailableBossBullet();
	b.setPosition(boss.getPosition());
}

//TODO: À VALIDER
void Level01Scene::firePlayerBullet()
{
	Bullet& b = getAvailableStandardBullet();
	b.setPosition(player.getPosition().x - player.getTextureRect().width / 2, player.getPosition().y);
	Bullet& b2 = getAvailableStandardBullet();
	b2.setPosition(player.getPosition().x + player.getTextureRect().width / 2, player.getPosition().y);

	if (player.isGunBonusActive()) {
		Bullet& b3 = getAvailableStandardBullet();
		b3.setPosition(player.getPosition().x - player.getTextureRect().width, player.getPosition().y + player.getTextureRect().height);
		Bullet& b4 = getAvailableStandardBullet();
		b4.setPosition(player.getPosition().x + player.getTextureRect().width, player.getPosition().y + player.getTextureRect().height);
	}
}

Bullet& Level01Scene::getAvailableStandardBullet()
{
	for (Bullet& b : playerBullets)
	{
		if (!b.isActive())
		{
			b.activate();
			return b;
		}
	}
	Bullet newBullet;
	newBullet.init(contentManager, CharacterType::PLAYER);
	playerBullets.push_back(newBullet);

	return playerBullets.back();
}

Bullet& Level01Scene::getAvailableEnemyBullet()
{
	for (Bullet& b : enemyBullets)
	{
		if (!b.isActive())
		{
			b.activate();
			return b;
		}
	}
	addNewEnemyBullets(); //TODO: OK DE AJOUTER BEAUCOUP DE BULLET D'UN COUP? 
	return enemyBullets.back();
}

Bullet& Level01Scene::getAvailableBossBullet()
{
	for (Bullet& b : bossBullets)
	{
		if (!b.isActive())
		{
			b.activate();
			return b;
		}
	}
	addNewBossBullets();
	return bossBullets.back();
}

void Level01Scene::addNewPlayerBullets() {
	for (size_t i = 0; i < MAX_NB_BULLETS; i++)
	{
		Bullet newBullet;
		newBullet.init(contentManager, CharacterType::PLAYER);
		playerBullets.push_back(newBullet);
	}
}

void Level01Scene::addNewEnemyBullets() {
	for (size_t i = 0; i < MAX_NB_BULLETS; i++)
	{
		Bullet newBullet;
		newBullet.init(contentManager, CharacterType::STANDARD_ENEMY);
		enemyBullets.push_back(newBullet);
	}
}


void Level01Scene::addNewBossBullets() {
	for (size_t i = 0; i < MAX_NB_BULLETS; i++)
	{
		Bullet newBullet;
		newBullet.init(contentManager, CharacterType::BOSS);
		bossBullets.push_back(newBullet);
	}
}

#pragma endregion

#pragma region Bonus

void Level01Scene::addNewGunBonus() {
	for (size_t i = 0; i < MAX_GUN_BONUS; i++)
	{
		GunBonus newGunBonus;
		newGunBonus.init(contentManager);
		gunBonus.push_back(newGunBonus);
	}
}

GunBonus& Level01Scene::getAvailableGunBonus()
{
	for (GunBonus& g : gunBonus)
	{
		if (!g.isActive())
		{
			g.activate();
			return g;
		}
	}
	GunBonus newGunBonus;
	newGunBonus.init(contentManager);
	gunBonus.push_back(newGunBonus);

	return gunBonus.back();
}

void Level01Scene::addNewLifeBonus() {
	for (size_t i = 0; i < MAX_LIFE_BONUS; i++)
	{
		LifeBonus newLifeBonus;
		newLifeBonus.init(contentManager);
		lifeBonus.push_back(newLifeBonus);
	}
}

LifeBonus& Level01Scene::getAvailableLifeBonus()
{
	for (LifeBonus& b : lifeBonus)
	{
		if (!b.isActive())
		{
			b.activate();
			return b;
		}
	}
	GunBonus newGunBonus;
	newGunBonus.init(contentManager);
	gunBonus.push_back(newGunBonus);

	return lifeBonus.back();
}

#pragma endregion

void Level01Scene::draw(sf::RenderWindow& window) const
{
	window.draw(backgroundSprite);
	player.draw(window);
	boss.draw(window);

	for (const StandardEnemy& e : standardEnemies)
		e.draw(window);

	for (const Bullet& e : playerBullets)
		e.draw(window);

	for (const Bullet& e : enemyBullets)
		e.draw(window);

	for (const Bullet& e : bossBullets)
		e.draw(window);

	for (const GunBonus& e : gunBonus) 
		e.draw(window);
	
	for (const LifeBonus& e : lifeBonus) 
		e.draw(window);
	
	hud.draw(window);
}

bool Level01Scene::uninit()
{
	return true;
}

bool Level01Scene::init()
{
	timeSinceLastFire = player.getFireRate() * 3;
	inputs.reset();
	if (contentManager.loadContent() == false)
	{
		return false;
	}
	backgroundSprite.setTexture(contentManager.getBackgroundTexture());
	srand((unsigned)time(nullptr));

	//Enemies
	addNewStandardEnemies();
	addNewEnemyBullets();

	//Boss
	boss.init(contentManager);
	addNewBossBullets();

	//Bonus
	addNewGunBonus();
	addNewLifeBonus();

	//Hud
	hud.initialize(contentManager);

	//Subscribers
	Publisher::addSubscriber(*this, Event::ENEMY_KILLED);
	Publisher::addSubscriber(*this, Event::BOSS_KILLED);
	Publisher::addSubscriber(*this, Event::PLAYER_KILLED);
	Publisher::addSubscriber(*this, Event::GUN_PICKED_UP);
	Publisher::addSubscriber(*this, Event::GUN_BONUS_DROPPED);
	Publisher::addSubscriber(*this, Event::LIFE_BONUS_DROPPED);

	//Player
	addNewPlayerBullets();;
	return player.init(contentManager);
}


void Level01Scene::notify(Event event, const void* data)
{
	switch (event)
	{
	case Event::NONE:
		break;
	case Event::ENEMY_KILLED:
	{
		nbKills++;
		score += SCORE_GAINED_ENEMY_KILLED;
		break;
	}
	case Event::PLAYER_KILLED:
	{
		gameEnded = true;
		break;
	}
	case Event::GUN_BONUS_DROPPED:
	{
		const StandardEnemy* enemy = static_cast<const StandardEnemy*>(data);
		GunBonus& bonus = getAvailableGunBonus();
		bonus.setPosition(enemy->getPosition());
		break;
	}
	case Event::LIFE_BONUS_DROPPED:
	{
		const StandardEnemy* enemy = static_cast<const StandardEnemy*>(data);
		LifeBonus& bonus = getAvailableLifeBonus();
		bonus.setPosition(enemy->getPosition());
		break;
	}
	case Event::GUN_PICKED_UP:
	{
		score += SCORE_GAINED_BONUS;
		break;
	}
	case Event::LIFE_PICKED_UP:
	{
		score += SCORE_GAINED_BONUS;
		break;
	}
	case::Event::BOSS_KILLED:
	{
		score += player.getLivesRemaining();
		score += result.level01SceneResult.score = score;
		gameEnded = true;
	}
	default:
		break;
	}

}

bool Level01Scene::handleEvents(sf::RenderWindow& window)
{
	bool retval = false;
	inputs.reset();
	sf::Event event;
	while (window.pollEvent(event))
	{
		//x sur la fen�tre
		if (event.type == sf::Event::Closed)
		{
			window.close();
			retval = true;
		}
	}


	if (sf::Joystick::isConnected(0))
	{
		inputs.moveFactorX = -Inputs::eliminateVibration(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X)) / GAMEPAD_SPEEDRATIO;
		inputs.moveFactorY = -Inputs::eliminateVibration(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y)) / GAMEPAD_SPEEDRATIO;
		inputs.playFireSound = sf::Joystick::isButtonPressed(0, sf::Joystick::X);
		if (sf::Joystick::isButtonPressed(0, sf::Joystick::PovX)) {
			isPaused = !isPaused;
		}
	}
	else
	{
		inputs.moveFactorX += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ? 3.0f : 0.0f;
		inputs.moveFactorX -= sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ? 3.0f : 0.0f;
		inputs.moveFactorY -= sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ? -3.0f : 0.0f;
		inputs.moveFactorY += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ? -3.0f : 0.0f;
		inputs.playFireSound = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			isPaused = !isPaused;
		}
	}

	return retval;
}
