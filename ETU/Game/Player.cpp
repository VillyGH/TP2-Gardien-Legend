#include "stdafx.h"
#include "Player.h"
#include "Inputs.h"
#include "game.h"
#include "ShipAnimation.h"
#include "Publisher.h"
#include "GunBonus.h"


const float Player::PLAYER_MOVE_SPEED = 3.0f;
const int Player::INITIAL_LIFE_COUNT = 500;
const float Player::MAX_IMMUNE_TIME = 3.f;
const float Player::MAX_BONUS_TIME = 3.f;


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

	deathSoundBuffer = contentManager.getEnemyKilledSoundBuffer();
	firingSoundBuffer = contentManager.getEnemyGunSoundBuffer();

	sound.setMinDistance(10);
	sound.setVolume(10);

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
	/*
	if (isImmuneMode()) {
		timeInImmune += elapsedTime;
		setColor(sf::Color(255, 255, 255, 128));
	}
	else if (isBonusMode()) {
		timeInBonus += elapsedTime;
		setColor(sf::Color::Yellow);
	}
	else {
		setColor(sf::Color(255, 255, 255, 255));
	}
		
	if (timeInImmune >= MAX_IMMUNE_TIME) {
		timeInImmune = 0;
		setImmuneMode(false);
	}

	if (timeInBonus >= MAX_BONUS_TIME) {
		timeInBonus = 0;
		setBonusMode(false);
	}

	}*/

	if(isGunBonusActive())
		gunBonusTimer -= deltaT;
	
	handleOutOfBoundsPosition();
	return AnimatedGameObject::update(deltaT, inputs);
}

void Player::fireBullet() {
	sound.setBuffer(firingSoundBuffer);
	sound.play();
}

bool Player::onHit() {
	if (isGunBonusActive()) {
		gunBonusTimer = 0;
	}
	return true;
}

void Player::handleOutOfBoundsPosition()
{
	sf::Vector2f newPosition = getPosition();
	if (newPosition.x > Game::GAME_WIDTH)
	{
		newPosition.x = Game::GAME_WIDTH;
	}
	else if (newPosition.x < 0)
	{
		newPosition.x = 0;
	}

	if (newPosition.y > Game::GAME_HEIGHT)
	{
		newPosition.y = Game::GAME_HEIGHT;
	}
	else if (newPosition.y < 0)
	{
		newPosition.y = 0;
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
