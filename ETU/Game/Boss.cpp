#include "stdafx.h"
#include "Boss.h"
#include "Inputs.h"
#include "game.h"
//#include "EnemyType1ExplosionAnimation.h"
#include "BossIdleAnimation.h"
#include "Publisher.h"

const float Boss::BOSS_SPAWN_Y_POSITION = -15;
const float Boss::BOSS_Y_MAX_POSITION = 160;
const float Boss::BOSS_VERTICAL_SPEED = 4;
const float Boss::BOSS_HORIZONTAL_SPEED = 13;

const sf::Vector2f Boss::BOSS_SCALING_SIZE(1.5, 1.5); 
const float Boss::MAX_BOSS_HEALTH = 30;


Boss::Boss()
	 :moveAngle(0)
	, health(0)
{

}
Boss::Boss(const Boss& src)
	: AnimatedGameObject(src)
{
	init(*contentManager);
	setPosition(src.getPosition());
	if (src.isActive())
		activate();
	else
		deactivate();
}
bool Boss::init(const Level01ContentManager& contentManager)
{
	setPosition(sf::Vector2f(Game::GAME_WIDTH * 0.5f, BOSS_SPAWN_Y_POSITION));
	health = MAX_BOSS_HEALTH; 
	currentState = State::BOSS;
	Animation* idleAnimation = new BossIdleAnimation(*this);
	bool retval = idleAnimation->init(contentManager);
	if (retval)
		animations[State::BOSS] = idleAnimation;
	this->scale(BOSS_SCALING_SIZE);
	return retval && AnimatedGameObject::init(contentManager);
}

bool Boss::update(float deltaT, const Inputs& inputs, const sf::Vector2f& dest)
{
	if(getPosition().y < BOSS_Y_MAX_POSITION)
		move(sf::Vector2f(0, BOSS_VERTICAL_SPEED));
	else 
	{
		setDestination(dest);
		move(cos(moveAngle) * BOSS_HORIZONTAL_SPEED, 0);
	}

	if (getGlobalBounds().height < -getGlobalBounds().height * 0.5f /** && currentState != State::EXPLODING*/)
		setPosition(getPosition().x, 0);

	if (animations[currentState]->isOver())
		return true;
	return AnimatedGameObject::update(deltaT, inputs);
}

bool Boss::isFiring() {
	if (animations[currentState]->getNextFrame() > 2 && animations[currentState]->getNextFrame() < 10)
		return true;
	return false;
}

void Boss::setDestination(const sf::Vector2f& dest) 
{
	destination.x = dest.x;
	destination.y = dest.y;
	moveAngle = atan2f((destination.y - getPosition().y), (destination.x - getPosition().x));
}


void Boss::onHit()
 {
	health--;
	if (health <= 0) {
		Publisher::notifySubscribers(Event::BOSS_KILLED, this);
		deactivate();
	}
}