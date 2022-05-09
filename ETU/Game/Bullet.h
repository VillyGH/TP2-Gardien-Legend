#pragma once
#include "GameObject.h"
#include "Level01ContentManager.h"
#include "CharacterType.h"
class Bullet : public GameObject
{
	static const float BULLET_SPEED;
	static const sf::Vector2f BULLET_SCALING_SIZE;
	static const unsigned long long TIME_TO_LIVE;
public:
	Bullet(const sf::Vector2f& initialPosition = sf::Vector2f(0, 0), const sf::Vector2f& initialThrust = sf::Vector2f(0, 0));
	Bullet(const Bullet& src);
	virtual bool init(const Level01ContentManager& manager, CharacterType type);
	void checkOutOfBounds();
	bool update(float elapsedTime, CharacterType type);

private:
	Bullet& operator=(const Bullet& rhs);
	sf::Texture texture; 
};

