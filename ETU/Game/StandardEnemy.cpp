#include "stdafx.h"
#include "StandardEnemy.h"
#include "Inputs.h"
#include "game.h"
//#include "EnemyType1ExplosionAnimation.h"
#include "StandardEnemyIdleAnimation.h"
#include "Publisher.h"

const float StandardEnemy::MAX_ENEMY_HEALTH = 5;

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

bool StandardEnemy::isFiring() {
	if (animations[currentState]->getNextFrame() > 11 && animations[currentState]->getNextFrame() > 13)
		//sound.setBuffer(firingSoundBuffer);
		//sound.play();
		return true;
	return false;
}

void StandardEnemy::onHit(float damage)
{
	health -= damage;
	if (health <= 0) {
		Publisher::notifySubscribers(Event::ENEMY_KILLED, this);
		sound.setBuffer(deathSoundBuffer);
		sound.play();
		deactivate();
	}

}

void StandardEnemy::checkOutOfBounds() {
	if (getPosition().y > Game::GAME_HEIGHT  /** && currentState != State::EXPLODING*/)
		setPosition((getPosition().x), 0);
}

