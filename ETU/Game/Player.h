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
	static const int MAX_IMMUNE_TIME = 3;
	static const int MAX_BONUS_TIME = 3;
	Player();
	virtual bool init(const Level01ContentManager& contentManager);

	bool update(float deltaT, const Inputs& inputs) override;
	void fireBullet();
	bool onHit();
	void handleOutOfBoundsPosition();
private:
	sf::SoundBuffer deathSoundBuffer;
	sf::Sound sound;
	sf::SoundBuffer firingSoundBuffer;

	bool isGunBonusActive();

	float gunBonusTimer;
	bool gunBonusIsActive; 
};

