#include "stdafx.h"
#include "StandardEnemy.h"
#include "Inputs.h"
#include "game.h"
#include "StandardEnemyIdleAnimation.h"
#include "Publisher.h"

const float StandardEnemy::STANDARD_ENEMY_SPAWN_TIME = 1.f;
const float StandardEnemy::ENEMY_SPAWN_DISTANCE = 15.f;
const float StandardEnemy::MAX_ENEMY_HEALTH = 5.f;
const float StandardEnemy::ENEMY_BONUS_DROP_CHANCE = 20.f;
const float StandardEnemy::ENEMY_BULLET_DAMAGE = 25.f;
const float StandardEnemy::ENEMY_BULLETS_PER_SHOT = 2.f;
const float StandardEnemy::MIN_FIRING_FRAME = 15.f;
const float StandardEnemy::MAX_FIRING_FRAME = 16.f;
const float StandardEnemy::ENEMY_SPEED = 5.f;
const float StandardEnemy::BULLET_SOUND_VOLUME = 6.f;
const float StandardEnemy::DEATH_SOUND_VOLUME = 20.f;

StandardEnemy::StandardEnemy()
	: health(0)
	, firedBullet(false)
{

}
StandardEnemy::StandardEnemy(const StandardEnemy& src)
	: AnimatedGameObject(src)
{
	init(*contentManager);
	setPosition(src.getPosition());
	if (src.isActive())
		activate();
	else
		deactivate();
}
bool StandardEnemy::init(const Level01ContentManager& contentManager)
{
	currentState = State::STANDARD_ENEMY;
	health = MAX_ENEMY_HEALTH;
	deathSoundBuffer = contentManager.getEnemyKilledSoundBuffer();
	firingSoundBuffer = contentManager.getEnemyGunSoundBuffer();
	Animation* idleAnimation = new StandardEnemyIdleAnimation(*this);
	bool retval = idleAnimation->init(contentManager);
	if (retval)
		animations[State::STANDARD_ENEMY] = idleAnimation;

	return retval && AnimatedGameObject::init(contentManager);
}

bool StandardEnemy::update(float deltaT, const Inputs& inputs)
{
	move(sf::Vector2f(0, ENEMY_SPEED));

	checkOutOfBounds();

	if (animations[currentState]->isOver())
		return true;
	return AnimatedGameObject::update(deltaT, inputs);
}

bool StandardEnemy::isFiring(float deltaT)
{
	bool retval = false;
	unsigned int nextFrame = animations[currentState]->getNextFrame();
	if (nextFrame >= MIN_FIRING_FRAME && nextFrame <= MAX_FIRING_FRAME) {
		retval = true;
		if (!firedBullet) {
			sound.setBuffer(firingSoundBuffer);
			sound.setVolume(BULLET_SOUND_VOLUME);
			sound.play();
			firedBullet = true;
		}
	}
	else {
		firedBullet = false;
	}
	return retval;
}

void StandardEnemy::onHit(const float damage)
{
	health -= damage;
	if (health <= 0) {
		Publisher::notifySubscribers(Event::ENEMY_KILLED, this);
		checkBonusDrop();
		sound.setBuffer(deathSoundBuffer);
		sound.play();
		sound.setVolume(DEATH_SOUND_VOLUME);
		deactivate();
		health = MAX_ENEMY_HEALTH;
	}
}

bool StandardEnemy::checkBonusDrop() const
{
	if (1 + (std::rand() % (100 - 1 + 1)) <= ENEMY_BONUS_DROP_CHANCE) {
		Publisher::notifySubscribers(Event::GUN_BONUS_DROPPED, this);
		return true;
	}
	else if (1 + (std::rand() % (100 - 1 + 1)) <= ENEMY_BONUS_DROP_CHANCE)
	{
		Publisher::notifySubscribers(Event::LIFE_BONUS_DROPPED, this);
		return true;
	}
	return false;
}

void StandardEnemy::checkOutOfBounds() {
	if (getPosition().y > Game::GAME_HEIGHT)
		setPosition((getPosition().x), 0);
}