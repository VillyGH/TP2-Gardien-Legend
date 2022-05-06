#include "stdafx.h"
#include "StandardEnemy.h"
#include "Inputs.h"
#include "game.h"
//#include "EnemyType1ExplosionAnimation.h"
#include "StandardEnemyIdleAnimation.h"


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
    setPosition(sf::Vector2f(Game::GAME_WIDTH * 0.5f, Game::GAME_HEIGHT));
    currentState = State::STANDARD_ENEMY;
    Animation* idleAnimation = new StandardEnemyIdleAnimation(*this);
    bool retval = idleAnimation->init(contentManager);
    if (retval)
        animations[State::STANDARD_ENEMY] = idleAnimation;
    //Animation* explosionAnimation = new EnemyType1ExplosionAnimation(*this);
    //retval = explosionAnimation->init(contentManager);
    //if (retval)
        //animations[State::EXPLODING] = explosionAnimation;
    return retval && AnimatedGameObject::init(contentManager);
}

bool StandardEnemy::update(float deltaT, const Inputs& inputs)
{
    move(sf::Vector2f(0, 5));
    if (getGlobalBounds().height < -getGlobalBounds().height * 0.5f /** && currentState != State::EXPLODING*/)
        setPosition(sf::Vector2f((float)Game::GAME_WIDTH, getPosition().y));


    if (animations[currentState]->isOver())
        return true;
    return AnimatedGameObject::update(deltaT, inputs);
}

bool StandardEnemy::isFiring() {
    if (animations[currentState]->getNextFrame() > 11 && animations[currentState]->getNextFrame() > 13)
        return true;
    return false;
}

void StandardEnemy::onHit()
{
    //currentState = State::EXPLODING;
}