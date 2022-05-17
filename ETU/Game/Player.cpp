#include "stdafx.h"
#include "Player.h"
#include "Inputs.h"
#include "game.h"
#include "ShipAnimation.h"
#include "Publisher.h"
#include "GunBonus.h"
#include "LifeBonus.h"


const float Player::PLAYER_MOVE_SPEED = 3.0f;
const float Player::INITIAL_LIFE_COUNT = 500.f;
const float Player::MAX_IMMUNE_TIME = 0.75f;
const float Player::MAX_BONUS_TIME = 3.f;
const float Player::PLAYER_BULLET_DAMAGE = 1;
const float Player::NB_FIRED_PLAYER_BULLETS = 1;
const float Player::NB_BONUS_FIRED_PLAYER_BULLETS = 2;
const float Player::NORMAL_FIRE_RATE = 0.3f;
const float Player::BONUS_FIRE_RATE = 0.2f;
const float Player::SPAWN_DISTANCE = 10.f;
const float Player::SOUND_VOLUME = 10.f;
const sf::Vector2f Player::SCALE_SIZE(2.5, 2.5);




Player::Player() :
	gunBonusTimer(0),
	gunBonusIsActive(false),
	immuneTimer(0),
	lives(0),
	fireRate(0)
{

}

bool Player::init(const Level01ContentManager& contentManager)
{
	setScale(SCALE_SIZE);
	activate();
	setPosition(Game::GAME_WIDTH / 2.f, Game::GAME_HEIGHT - 100.f);

	currentState = State::SHIP;
	Animation* shipAnimation = new ShipAnimation(*this);

	lives = INITIAL_LIFE_COUNT;
	fireRate = NORMAL_FIRE_RATE;
	firingSoundBuffer = contentManager.getEnemyGunSoundBuffer();

	sound.setMinDistance(SPAWN_DISTANCE);
	sound.setVolume(SOUND_VOLUME);

	bool retval = shipAnimation->init(contentManager);
	if (retval)
		animations[State::SHIP] = shipAnimation;

	Publisher::addSubscriber(*this, Event::GUN_PICKED_UP);
	Publisher::addSubscriber(*this, Event::LIFE_PICKED_UP);


	return retval && AnimatedGameObject::init(contentManager);
}

bool Player::update(const float deltaT, const Inputs& inputs)
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

	if (isGunBonusActive()) {
		gunBonusTimer -= deltaT;
		fireRate = BONUS_FIRE_RATE;
	}


	handleOutOfBoundsPosition();
	return AnimatedGameObject::update(deltaT, inputs);
}

void Player::playFireSound() {
	sound.setBuffer(firingSoundBuffer);
	sound.play();
}

bool Player::onHit(const float damage) {
	if (isGunBonusActive()) {
		gunBonusTimer = 0;
		return false;
	}
	else if (!isImmune()) {
		lives -= damage;
		immuneTimer = MAX_IMMUNE_TIME;

		if (lives <= 0)
			Publisher::notifySubscribers(Event::PLAYER_KILLED, this);
	}

	return true;
}

float Player::getLivesRemaining() const {
	return lives;
}

float Player::getFireRate() const {
	return fireRate;
}

float Player::getGunBonusTimer() const {
	return gunBonusTimer;
}

void Player::handleOutOfBoundsPosition()
{
	sf::Vector2f newPosition = getPosition();
	if (newPosition.x > (float)Game::GAME_WIDTH)
	{
		newPosition.x = (float)Game::GAME_WIDTH;
	}
	else if (newPosition.x < 0)
	{
		newPosition.x = 0;
	}

	if (newPosition.y > (float)Game::GAME_HEIGHT)
	{
		newPosition.y = (float)Game::GAME_HEIGHT;
	}
	else if (newPosition.y < 0)
	{
		newPosition.y = 0;
	}

	GameObject::setPosition(newPosition);
}

bool Player::isGunBonusActive() const {
	if (gunBonusTimer >= 0)
		return true;
	return false;
}

bool Player::isImmune() {
	if (immuneTimer <= 0)
		return false;
	return true;
}

void Player::notify(const Event event, const void* data)
{
	switch (event)
	{
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
