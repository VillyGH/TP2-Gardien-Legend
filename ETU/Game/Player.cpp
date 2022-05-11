#include "stdafx.h"
#include "Player.h"
#include "Inputs.h"
#include "game.h"
#include "ShipAnimation.h"
#include "Publisher.h"
#include "GunBonus.h"


const float Player::PLAYER_MOVE_SPEED = 3.0f;
const float Player::INITIAL_LIFE_COUNT = 500;


Player::Player():
	gunBonusTimer(0),
	gunBonusIsActive(false)

{

}

bool Player::init(const Level01ContentManager& contentManager)
{
	setScale(2.5f, 2.5f);
	activate();
	setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT - 100);

	currentState = State::SHIP;
	Animation* shipAnimation = new ShipAnimation(*this);

	bool retval = shipAnimation->init(contentManager);
	if (retval)
		animations[State::SHIP] = shipAnimation;

	Publisher::addSubscriber(*this, Event::GUN_PICKED_UP);
	Publisher::addSubscriber(*this, Event::LIFE_PICKED_UP);


	return retval && AnimatedGameObject::init(contentManager);
}

bool Player::update(float deltaT, const Inputs& inputs)
{
	move(inputs.moveFactorX * -PLAYER_MOVE_SPEED, inputs.moveFactorY * -PLAYER_MOVE_SPEED);

	if(isGunBonusActive())
		gunBonusTimer -= deltaT;
	
	handleOutOfBoundsPosition();
	return AnimatedGameObject::update(deltaT, inputs);
}

bool Player::onHit() {
	if (isGunBonusActive()) {
		gunBonusTimer = 0;
	}	 
}

void Player::handleOutOfBoundsPosition()
{
	sf::Vector2f newPosition = getPosition();
	if (newPosition.x > Game::GAME_WIDTH + getGlobalBounds().width / 2.0f)
	{
		newPosition.x -= Game::GAME_WIDTH + getGlobalBounds().width;
	}
	else if (newPosition.x < -getGlobalBounds().width * 0.5f)
	{
		newPosition.x += Game::GAME_WIDTH + getGlobalBounds().width;
	}

	if (newPosition.y > Game::GAME_HEIGHT + getGlobalBounds().height / 2.0f)
	{
		newPosition.y -= Game::GAME_HEIGHT + getGlobalBounds().height;
	}
	else if (newPosition.y < -getGlobalBounds().height * 0.5f)
	{
		newPosition.y += Game::GAME_HEIGHT + getGlobalBounds().height;
	}

	GameObject::setPosition(newPosition);
}

bool Player::isGunBonusActive() {
	if (gunBonusTimer >= 0)
		return true;
	return false;
}


void Player::notify(Event event, const void* data)
{
	switch (event)
	{
	case Event::NONE:
		break;
	case Event::LIFE_PICKED_UP:
	{
		break;
	}
	case Event::GUN_PICKED_UP:
	{
		const GunBonus* bonus = static_cast<const GunBonus*>(data);
		gunBonusIsActive = true;
		gunBonusTimer = bonus->BONUS_DURATION;
		break;
	}
	}
}
