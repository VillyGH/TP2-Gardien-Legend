#include "stdafx.h"
#include "Player.h"
#include "Inputs.h"
#include "game.h"
#include "ShipAnimation.h"
#include "Publisher.h"
#include "GunBonus.h"
#include "LifeBonus.h"


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

	lives = INITIAL_LIFE_COUNT;
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
	if (isImmune()) {
		immuneTimer -= deltaT;
		setColor(sf::Color(255, 255, 255, 128));
	}
	else 
	{
		setColor(sf::Color(255, 255, 255, 255));
	}
		
	if(isGunBonusActive())
		gunBonusTimer -= deltaT;
	
	handleOutOfBoundsPosition();
	return AnimatedGameObject::update(deltaT, inputs);
}

void Player::fireBullet() {
	sound.setBuffer(firingSoundBuffer);
	sound.play();
}

bool Player::onHit(float damage) {
	if (isGunBonusActive()) {
		gunBonusTimer = 0;
		return false;
	}
	else if (!isImmune()) {
		lives -= damage;
		immuneTimer = MAX_IMMUNE_TIME;
		sound.setBuffer(deathSoundBuffer);
		sound.play();

		if (lives <= 0)
			Publisher::notifySubscribers(Event::PLAYER_KILLED, this);
	}

	return true;
}

float Player::getLivesRemaining() {
	return lives;
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

bool Player::isImmune() {
	if (immuneTimer <= 0)
		return false;
	return true;
}


void Player::notify(Event event, const void* data)
{
	switch (event)
	{
	case Event::NONE:
		break;
	case Event::LIFE_PICKED_UP:
	{
		const LifeBonus* bonus = static_cast<const LifeBonus*>(data);
		lives += bonus->BONUS_LIFE;
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
