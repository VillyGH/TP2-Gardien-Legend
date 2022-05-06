#include "stdafx.h"
#include "Player.h"
#include "Inputs.h"
#include "game.h"
#include "ContentManager.h"
#include "ShipAnimation.h"

const float Player::PLAYER_MOVE_SPEED = 5.0f;

Player::Player()
{

}

bool Player::init(const ContentManager& contentManager)
{
	setScale(2.5f, 2.5f);
    activate();
	setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT - 100);

    currentState = State::SHIP;
    Animation* shipAnimation = new ShipAnimation(*this);

    bool retval = shipAnimation->init(contentManager);
    if (retval)
        animations[State::SHIP] = shipAnimation;

    return retval && AnimatedGameObject::init(contentManager);
}

bool Player::update(float deltaT, const Inputs& inputs)
{
	move(inputs.moveFactorX *- PLAYER_MOVE_SPEED, inputs.moveFactorY *- PLAYER_MOVE_SPEED);

	handleOutOfBoundsPosition();
	return AnimatedGameObject::update(deltaT, inputs);
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
