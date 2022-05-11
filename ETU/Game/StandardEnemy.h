#pragma once
#include "AnimatedGameObject.h"
#include "Level01ContentManager.h"
#include "Subscriber.h"

class StandardEnemy :
	public AnimatedGameObject
{
public:
	static const float MAX_ENEMY_HEALTH;
	static const int ENEMY_BONUS_DROP_CHANCE;
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

