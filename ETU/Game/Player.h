#pragma once
#include "AnimatedGameObject.h"
#include "Level01ContentManager.h"
struct Inputs;
class Player :
	public AnimatedGameObject
{

public:
	static const float PLAYER_MOVE_SPEED;
	static const int INITIAL_LIFE_COUNT;
	Player();
	virtual bool init(const Level01ContentManager& contentManager);

	bool update(float deltaT, const Inputs& inputs) override;
	void fireBullet();
	void handleOutOfBoundsPosition();
private:
	sf::SoundBuffer deathSoundBuffer;
	sf::Sound sound;
	sf::SoundBuffer firingSoundBuffer;
};

