#include "stdafx.h"
#include "LifeBonus.h"
#include "Publisher.h"
#include "StandardEnemy.h"
#include "game.h"

const sf::Vector2f LifeBonus::SCALING_SIZE(4, 4);
const float LifeBonus::BONUS_LIFE = 50;
const float LifeBonus::BONUS_POINTS = 100;

LifeBonus::LifeBonus() :
	GameObject(),
	life(BONUS_LIFE)
{

}

bool LifeBonus::init(const Level01ContentManager& contentManager)
{
	bool retval = GameObject::init(contentManager);
	setTexture(contentManager.getMiscTexture());
	setTextureRect(sf::IntRect(315, 108, 10, 10));
	setScale(SCALING_SIZE);
	soundBuffer = contentManager.getHealthSoundBuffer();
	return retval;
}

void LifeBonus::onPickUp()
{
	Publisher::notifySubscribers(Event::LIFE_PICKED_UP, this);
	sound.setBuffer(soundBuffer);
	sound.play();
}

bool LifeBonus::update(float deltaT, const Inputs& inputs)
{
	move(0, StandardEnemy::ENEMY_SPEED);
	checkOutOfBounds();
	return false;
}

void LifeBonus::checkOutOfBounds() {
	if (getPosition().y > Game::GAME_HEIGHT  /** && currentState != State::EXPLODING*/)
		deactivate();
}
