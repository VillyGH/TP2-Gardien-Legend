#include "stdafx.h"
#include "GunBonus.h"
#include "Publisher.h"
#include "StandardEnemy.h"
#include "game.h"

const sf::Vector2f GunBonus::SCALING_SIZE(2, 2);
const float GunBonus::BONUS_DURATION = 5;
const float GunBonus::BONUS_POINTS = 100; 

GunBonus::GunBonus() : 
	GameObject(),
	duration(BONUS_DURATION)
{

}

bool GunBonus::init(const Level01ContentManager& contentManager)
{
	bool retval = GameObject::init(contentManager);
	setTexture(contentManager.getMiscTexture());
	setTextureRect(sf::IntRect(163, 82, 15, 15));
	setScale(SCALING_SIZE);
	soundBuffer = contentManager.getGunBonusSoundBuffer();
	return retval;
}

void GunBonus::onPickUp()
{
	Publisher::notifySubscribers(Event::GUN_PICKED_UP, this);
	sound.setBuffer(soundBuffer);
	sound.play();
}

bool GunBonus::update(float deltaT, const Inputs& inputs)
{
	move(0, StandardEnemy::ENEMY_SPEED);
	checkOutOfBounds();
	return false;
}

void GunBonus::checkOutOfBounds() {
	if (getPosition().y > Game::GAME_HEIGHT  /** && currentState != State::EXPLODING*/)
		deactivate();
}
