#include "stdafx.h"
#include "Bullet.h"
#include "ContentManager.h"
#include "game.h"
#include "CharacterType.h"

const float Bullet::BULLET_SPEED = 600;
const sf::Vector2f Bullet::BULLET_SCALING_SIZE(2, 2);
const unsigned long long Bullet::TIME_TO_LIVE = 2000;

Bullet::Bullet(const sf::Vector2f& initialPosition, const sf::Vector2f& initialThrust)
	: GameObject()
{
	setPosition(initialPosition);
	move(initialThrust);
}

Bullet::Bullet(const Bullet& src)
	:GameObject(src)
{

}

bool Bullet::update(float elapsedTime, CharacterType type)
{
	switch (type)
	{
	case CharacterType::STANDARD_ENEMY:
		move(sf::Vector2f(0, BULLET_SPEED * elapsedTime));
		if (getPosition().y > Game::GAME_HEIGHT)
			return true;
		break;
	case CharacterType::BOSS:
		break;
	case CharacterType::PLAYER:
		move(sf::Vector2f(0, -BULLET_SPEED * elapsedTime));
		if (getPosition().y < 0)
			return true;
		break;
	default:
		break;
	}

	checkOutOfBounds();

	return false;
}

bool Bullet::init(const Level01ContentManager& contentManager, CharacterType type)
{
	GameObject::init(contentManager);
	setTexture(contentManager.getMainCharacterTexture());
	if (type == CharacterType::PLAYER)
		setTextureRect(sf::IntRect(265, 106, 16, 5));

	if (type == CharacterType::STANDARD_ENEMY || type == CharacterType::BOSS)
		setTextureRect(sf::IntRect(287, 106, 16, 5));
	this->rotate(90);
	this->scale(BULLET_SCALING_SIZE);
	return true;
}

void Bullet::checkOutOfBounds() {
	if (getPosition().y > Game::GAME_HEIGHT + getGlobalBounds().top * 0.5  /** && currentState != State::EXPLODING*/)
		deactivate();
}

