#pragma once
#include "AnimatedGameObject.h"
#include "Level01ContentManager.h"
#include "Subscriber.h"
struct Inputs;
class Player :
	public AnimatedGameObject, public Subscriber
{
public:
	virtual void notify(const Event event, const void* data) override;
public:
	static const float PLAYER_MOVE_SPEED;
	static const float INITIAL_LIFE_COUNT;
	static const float MAX_IMMUNE_TIME;
	static const float MAX_BONUS_TIME;
	static const float PLAYER_BULLET_DAMAGE;
	static const float NB_FIRED_PLAYER_BULLETS;
	static const float NB_BONUS_FIRED_PLAYER_BULLETS;
	static const float NORMAL_FIRE_RATE;
	static const float BONUS_FIRE_RATE;
	static const float SPAWN_DISTANCE;
	static const float SOUND_VOLUME;
	static const sf::Vector2f SCALE_SIZE;




	Player();
	virtual bool init(const Level01ContentManager& contentManager);
	bool isGunBonusActive() const;
	bool isImmune();
	bool update(const float deltaT, const Inputs& inputs) override;
	void playFireSound();
	bool onHit(const float damage);
	void handleOutOfBoundsPosition();
	float getFireRate() const;
	float getGunBonusTimer() const;
	float getLivesRemaining() const;
private:
	sf::Sound sound;
	sf::SoundBuffer firingSoundBuffer;
	float gunBonusTimer;
	float immuneTimer;
	bool gunBonusIsActive; 
	float lives;
	float fireRate;
};

