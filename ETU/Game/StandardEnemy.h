#pragma once
#include "AnimatedGameObject.h"
#include "Level01ContentManager.h"
#include "Subscriber.h"

class StandardEnemy :
	public AnimatedGameObject
{
public:
	static const float STANDARD_ENEMY_SPAWN_TIME;
	static const float ENEMY_SPAWN_DISTANCE;
	static const int MAX_ENEMY_HEALTH;
	static const int ENEMY_BONUS_DROP_CHANCE;
	static const int GUN_BONUS_DROP_CHANCE;
	static const int LIFE_BONUS_DROP_CHANCE;
	static const int ENEMY_BULLET_DAMAGE;
	static const int ENEMY_BULLETS_PER_SHOT;
	static const float FIRING_TIME;
	static const float MIN_FIRING_FRAME;
	static const float MAX_FIRING_FRAME;
	static const float ENEMY_SPEED;

	StandardEnemy();
	StandardEnemy(const StandardEnemy& src);
	virtual bool init(const Level01ContentManager& contentManager) override;
	bool update(float deltaT, const Inputs& inputs) override;
	bool isFiring(float deltaT);
	void onHit(float damage);
	bool checkBonusDrop();
	void checkOutOfBounds();

private:
	float health;
	sf::SoundBuffer deathSoundBuffer;
	sf::Sound sound;
	sf::SoundBuffer firingSoundBuffer;
};

