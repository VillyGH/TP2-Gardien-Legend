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
	static const float MAX_ENEMY_HEALTH;
	static const float ENEMY_BONUS_DROP_CHANCE;
	static const float GUN_BONUS_DROP_CHANCE;
	static const float LIFE_BONUS_DROP_CHANCE;
	static const float ENEMY_BULLET_DAMAGE;
	static const float ENEMY_BULLETS_PER_SHOT;
	static const float MIN_FIRING_FRAME;
	static const float MAX_FIRING_FRAME;
	static const float ENEMY_SPEED;
	static const float BULLET_SOUND_VOLUME;
	static const float DEATH_SOUND_VOLUME;


	StandardEnemy();
	StandardEnemy(const StandardEnemy& src);
	virtual bool init(const Level01ContentManager& contentManager) override;
	bool update(float deltaT, const Inputs& inputs) override;
	bool isFiring(const float deltaT);
	void onHit(float damage);
	bool checkBonusDrop() const;
	void checkOutOfBounds();

private:
	float health;
	sf::SoundBuffer deathSoundBuffer;
	sf::Sound sound;
	sf::SoundBuffer firingSoundBuffer;
	bool firedBullet;
};

