#include "stdafx.h"
#include "StandardEnemy.h"
#include "Inputs.h"
#include "game.h"
//#include "EnemyType1ExplosionAnimation.h"
#include "StandardEnemyIdleAnimation.h"
#include "Publisher.h"

const float StandardEnemy::MAX_ENEMY_HEALTH = 5;
const int StandardEnemy::ENEMY_BONUS_DROP_CHANCE = 10; 
const float StandardEnemy::FIRING_TIME = StandardEnemyIdleAnimation::ANIMATION_LENGTH / 2;
const float StandardEnemy::MIN_FIRING_FRAME = 15;
const float StandardEnemy::MAX_FIRING_FRAME = 16;
const float StandardEnemy::ENEMY_SPEED = 5;

StandardEnemy::StandardEnemy()
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
	deathSoundBuffer = contentManager.getEnemyKilledSoundBuffer();
	firingSoundBuffer = contentManager.getEnemyGunSoundBuffer();
	health = MAX_ENEMY_HEALTH;
	Animation* idleAnimation = new StandardEnemyIdleAnimation(*this);
	bool retval = idleAnimation->init(contentManager);
	if (retval)
		animations[State::STANDARD_ENEMY] = idleAnimation;

	return retval && AnimatedGameObject::init(contentManager);
}

bool StandardEnemy::update(float deltaT, const Inputs& inputs)
{
	move(sf::Vector2f(0, 5));

	checkOutOfBounds();

	if (animations[currentState]->isOver())
		return true;
	return AnimatedGameObject::update(deltaT, inputs);
}

bool StandardEnemy::isFiring(float deltaT) {
	
	bool retval = false; 
	float time = animations[currentState]->getTimeInCurrentState();
	float nextFrame = animations[currentState]->getNextFrame();

	if (nextFrame >= MIN_FIRING_FRAME && nextFrame <= MAX_FIRING_FRAME) {
		retval = true;
	}

	if (time >= FIRING_TIME - deltaT && time <= FIRING_TIME) {
		sound.setBuffer(firingSoundBuffer);
		sound.play();
	}

	return retval;
}

void StandardEnemy::onHit(float damage)
{
	health -= damage;
	if (health <= 0) {
		Publisher::notifySubscribers(Event::ENEMY_KILLED, this);
		checkBonusDrop();
		sound.setBuffer(deathSoundBuffer);
		sound.play();
		deactivate();
	}
}

bool StandardEnemy::checkBonusDrop() 
{
	if (1 + (std::rand() % (ENEMY_BONUS_DROP_CHANCE - 1 + 1)) > 0) {
		Publisher::notifySubscribers(Event::GUN_BONUS_DROPPED, this);
		return true;
	}
	else if (1 + (std::rand() % (10 - 1 + 1)) > 7)
	{
		Publisher::notifySubscribers(Event::LIFE_BONUS_DROPPED, this);
		return true;
	}
	return false; 
}

void StandardEnemy::checkOutOfBounds() {
	if (getPosition().y > Game::GAME_HEIGHT  /** && currentState != State::EXPLODING*/)
		setPosition((getPosition().x), 0);
}



