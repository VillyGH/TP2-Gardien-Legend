#include "stdafx.h"
#include "Boss.h"
#include "Inputs.h"
#include "game.h"
//#include "EnemyType1ExplosionAnimation.h"
#include "BossIdleAnimation.h"

//const float BOSS_SPAWN_Y_POSITION = -15;

Boss::Boss()
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
	setPosition(sf::Vector2f(Game::GAME_WIDTH * 0.5f, 50));
	currentState = State::BOSS;
	Animation* idleAnimation = new BossIdleAnimation(*this);
	bool retval = idleAnimation->init(contentManager);
	if (retval)
		animations[State::BOSS] = idleAnimation;
	//Animation* explosionAnimation = new EnemyType1ExplosionAnimation(*this);
	//retval = explosionAnimation->init(contentManager);
	//if (retval)
		//animations[State::EXPLODING] = explosionAnimation;
	return retval && AnimatedGameObject::init(contentManager);
}

bool Boss::update(float deltaT, const Inputs& inputs)
{
	move(sf::Vector2f(0, 5));
	if (getGlobalBounds().height < -getGlobalBounds().height * 0.5f /** && currentState != State::EXPLODING*/)
		setPosition(getPosition().x, 0);


	if (animations[currentState]->isOver())
		return true;
	return AnimatedGameObject::update(deltaT, inputs);
}

bool Boss::isFiring() {
	if (animations[currentState]->getNextFrame() > 11 && animations[currentState]->getNextFrame() > 13)
		return true;
	return false;
}

void Boss::onHit()
{
	//currentState = State::EXPLODING;
}