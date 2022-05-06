#include "stdafx.h"
#include "EnemyType1.h"
#include "Inputs.h"
#include "game.h"
//#include "EnemyType1ExplosionAnimation.h"
#include "EnemyType1IdleAnimation.h"


EnemyType1::EnemyType1()
{

}
EnemyType1::EnemyType1(const EnemyType1& src)
    : AnimatedGameObject(src)
{
    init(*contentManager);
    setPosition(src.getPosition());
    if (src.isActive())
        activate();
    else
        deactivate();
}
bool EnemyType1::init(const Level01ContentManager& contentManager)
{
    setPosition(sf::Vector2f(Game::GAME_WIDTH * 0.5f, Game::GAME_HEIGHT));
    currentState = State::STANDARD_ENEMY;
    Animation* idleAnimation = new EnemyType1IdleAnimation(*this);
    bool retval = idleAnimation->init(contentManager);
    if (retval)
        animations[State::STANDARD_ENEMY] = idleAnimation;
    //Animation* explosionAnimation = new EnemyType1ExplosionAnimation(*this);
    //retval = explosionAnimation->init(contentManager);
    //if (retval)
        //animations[State::EXPLODING] = explosionAnimation;
    return retval && AnimatedGameObject::init(contentManager);
}

bool EnemyType1::update(float deltaT, const Inputs& inputs)
{
    move(sf::Vector2f(0, 5));
    if (getGlobalBounds().height < -getGlobalBounds().height * 0.5f /** && currentState != State::EXPLODING*/)
        setPosition(sf::Vector2f((float)Game::GAME_WIDTH, getPosition().y));


    if (animations[currentState]->isOver())
        return true;
    return AnimatedGameObject::update(deltaT, inputs);
}

bool EnemyType1::isFiring() {
    if (animations[currentState]->getNextFrame() > 11 && animations[currentState]->getNextFrame() > 13)
        return true;
    return false;
}

void EnemyType1::onHit()
{
    //currentState = State::EXPLODING;
}