#pragma once
#include "AnimatedGameObject.h"
#include "Level01ContentManager.h"
#include "Subscriber.h"
struct Inputs;
class Player :
	public AnimatedGameObject, public Subscriber
{
public:
	virtual void notify(Event event, const void* data) override;
public:
	static const float PLAYER_MOVE_SPEED;
	static const int INITIAL_LIFE_COUNT;
	static const float MAX_IMMUNE_TIME;
	static const float MAX_BONUS_TIME;
	static const float NORMAL_FIRE_RATE;
	static const float BONUS_FIRE_RATE;

	Player();
	virtual bool init(const Level01ContentManager& contentManager);
	bool isGunBonusActive();
	bool isImmune();
	bool update(float deltaT, const Inputs& inputs) override;
	void fireBullet();
	bool onHit(float damage);
	void handleOutOfBoundsPosition();
	float getFireRate();
	float getGunBonusTimer();
	float getLivesRemaining();
private:
	sf::SoundBuffer deathSoundBuffer;
	sf::Sound sound;
	sf::SoundBuffer firingSoundBuffer;
	float gunBonusTimer;
	float immuneTimer;
	bool gunBonusIsActive; 
	float lives;
	float fireRate;
};

